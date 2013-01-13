#include <cstdlib>

#include "filter.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

using namespace v8;
using namespace node;

static Persistent<FunctionTemplate> constructor_template;

void NodeFilter::Initialize (Handle<Object> target) {
	HandleScope scope;

	Local<FunctionTemplate> t = FunctionTemplate::New(New);
	constructor_template = Persistent<FunctionTemplate>::New(t);
	constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
	constructor_template->SetClassName(String::NewSymbol("Filter"));

	NODE_SET_PROTOTYPE_METHOD(constructor_template, "clearHistory", ClearHistory);
	NODE_SET_PROTOTYPE_METHOD(constructor_template, "filter", Filter);

	target->Set(String::NewSymbol("Filter"), constructor_template->GetFunction());
}

NodeFilter::NodeFilter (float *bb, int bbSize, float *aa, int aaSize) :
	b (bb),
	bSize (bbSize),
	a (aa),
	aSize (aaSize)
{
	bHist = (float *) malloc(bSize * sizeof(float));

	if (aSize) {
		aHist = (float *) malloc(aSize * sizeof(float));
	} else {
		aHist = NULL;
	}

	clearHistory();

	b[0] = 1.0;
}

void NodeFilter::clearHistory () {
	for (int k=0; k < bSize; k++) {
		bHist[k] = 0.0;
	}

	for (int k=0; k < aSize; k++) {
		aHist[k] = 0.0;
	}
}

Handle<Value> NodeFilter::New (const Arguments &args) {
	HandleScope scope;

	if (!args[0]->IsNumber()) {
		return ThrowException(Exception::TypeError(String::New("Not supported")));
	}

	int bSize = args[0]->Int32Value();
	int aSize = args[1]->IsNumber() ? args[1]->Int32Value() : 0;

	if (bSize < 1 || aSize < 0) {
		return ThrowException(Exception::TypeError(String::New("Not supported")));
	}

	/* inline this stuff, otherwise you get neutered float32arrays */
	Local<Function> float32_array_constructor;
	Local<Object> global = Context::GetCurrent()->Global();
	Local<Value> val = global->Get(String::New("Float32Array"));
	assert(!val.IsEmpty() && "type not found: Float32Array");
	assert(val->IsFunction() && "not a constructor: Float32Array");
	float32_array_constructor = Local<Function>::New(val.As<Function>());

	Local<Value> bbSize = Integer::NewFromUnsigned(bSize);
	Local<Value> aaSize = Integer::NewFromUnsigned(aSize);
	Local<Object> bValue = float32_array_constructor->NewInstance(1, &bbSize);
	Local<Object> aValue = float32_array_constructor->NewInstance(1, &aaSize);

	Float32Array b(bValue);
	Float32Array a(aValue);

	NodeFilter *nodefilter = new NodeFilter(b.data, b.length, a.data, a.length);

	args.This()->Set(String::NewSymbol("b"), bValue,
		static_cast<PropertyAttribute>(ReadOnly|DontDelete));
	args.This()->Set(String::NewSymbol("a"), aValue,
		static_cast<PropertyAttribute>(ReadOnly|DontDelete));

	nodefilter->Wrap(args.This());

	return args.This();
}

Handle<Value> NodeFilter::Filter (const Arguments &args) {
	HandleScope scope;
	NodeFilter *nf = ObjectWrap::Unwrap<NodeFilter>(args.This());

	float *b = nf->b;
	int bSize = nf->bSize;

	float *a = nf->a;
	int aSize = nf->aSize;

	Float32Array dst(args[0]);
	Float32Array x(args[1]);

	float *bHist = nf->bHist;
	float *aHist = nf->aHist;

	/* history part */

	int bHistRunIn = bSize - 1;
	int aHistRunIn = aSize;
	int k;

	for (k=0; (bHistRunIn || aHistRunIn) && k < x.length; k++) {
		int m, noHistLen;

		/* FIR */
		noHistLen = bSize - bHistRunIn;
		if (bHistRunIn) bHistRunIn--;
		float res = b[0] * x[k];

		for (m=1; m < noHistLen; m++) {
			res += b[m] * x[k - m];
		}

		for (; m < bSize; m++) {
			res += b[m] * bHist[m - noHistLen];
		}

		/* IIR */
		noHistLen = aSize - aHistRunIn;
		if (aHistRunIn) aHistRunIn--;

		for (m=0; m < noHistLen; m++) {
			res -= a[m] * dst[k - 1 - m];
		}

		for (; m < aSize; m++) {
			res -= a[m] * aHist[m - noHistLen];
		}
		
		dst[k] = res;
	}

	/* perform history-free part */
	if (bSize == 3 && aSize == 2) {
		/* Optimized special case: Biquad Filter */
		float b0 = b[0], b1 = b[1], b2 = b[2], a1 = a[0], a2 = a[1];
		float x0 = x[k - 1], x1 = x[k - 2], x2;
		float y0 = dst[k - 1], y1 = dst[k - 2], y2;

		for (; k < x.length; k++) {
			x2 = x1;
			x1 = x0;
			x0 = x[k];
			y2 = y1;
			y1 = y0;
			y0 = b0 * x0 + b1 * x1 + b2 * x2 - a1 * y1 - a2 * y2;

			dst[k] = y0;
		}
	} else {
		/* generic case */
		for (; k < x.length; k++) {
			/* FIR */
			float res = b[0] * x[k];

			for (int m=1; m < bSize; m++) {
				res += b[m] * x[k - m];
			}

			/* IIR */
			for (int m=0; m < aSize; m++) {
				res -= a[m] * dst[k - 1 - m];
			}

			dst[k] = res;
		}
	}

	/* update history state */
	int histCopy;

	/* FIR */
	histCopy = MIN(bSize - 1, x.length);
	for (k = bSize - 2; k >= histCopy; k--) {
		bHist[k] = bHist[k - histCopy];
	}
	for (k = 0; k < histCopy; k++) {
		bHist[k] = x[x.length - 1 - k];
	}

	/* IIR */
	histCopy = MIN(aSize, dst.length);
	for (k = aSize - 1; k >= histCopy; k--) {
		aHist[k] = aHist[k - histCopy];
	}
	for (k=0; k < histCopy; k++) {
		aHist[k] = dst[x.length - 1 - k];
	}
	
	return Undefined();
}

Handle<Value> NodeFilter::ClearHistory (const Arguments &args) {
	HandleScope scope;
	NodeFilter *nf = ObjectWrap::Unwrap<NodeFilter>(args.This());

	nf->clearHistory();

	return Undefined();
}
