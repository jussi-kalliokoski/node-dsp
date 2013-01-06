#include "fft.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

using namespace v8;
using namespace node;

static Persistent<FunctionTemplate> fft_constructor_template;

void NodeFFT::Initialize (Handle<Object> target) {
	HandleScope scope;

	Local<FunctionTemplate> t = FunctionTemplate::New(New);
	fft_constructor_template = Persistent<FunctionTemplate>::New(t);
	fft_constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
	fft_constructor_template->SetClassName(String::NewSymbol("FFT"));

	NODE_SET_PROTOTYPE_METHOD(fft_constructor_template, "forward", Forward);
	NODE_SET_PROTOTYPE_METHOD(fft_constructor_template, "forwardCplx", ForwardCplx);
	NODE_SET_PROTOTYPE_METHOD(fft_constructor_template, "inverse", Forward);
	NODE_SET_PROTOTYPE_METHOD(fft_constructor_template, "inverseCplx", InverseCplx);

	target->Set(String::NewSymbol("FFT"), fft_constructor_template->GetFunction());
}

NodeFFT::NodeFFT () {}

int NodeFFT::reset (int ssize) {
	if (ssize < 1) return 0;

	size = ssize;

	/* even N optimization */
	if (!(size % 2)) {
		kiss_state_real = kiss_fftr_alloc(size, 0, NULL, NULL);
		kiss_state_real_i = kiss_fftr_alloc(size, 1, NULL, NULL);
	} else {
		kiss_state_real = NULL;
		kiss_state_real_i = NULL;
	}

	kiss_state_cplx = kiss_fft_alloc(size, 0, NULL, NULL);
	kiss_state_cplx_i = kiss_fft_alloc(size, 1, NULL, NULL);

	kiss_fft_cpx temp_cpxi[size];
	/* pad to 6 to avoid segfaults with kiss_fft, see issue #2 */
	kiss_fft_cpx temp_cpxo[size < 6 ? 6 : size];
	temp_cplx_i = temp_cpxi;
	temp_cplx_o = temp_cpxo;

	return 1;
}

Handle<Value> NodeFFT::New (const Arguments &args) {
	HandleScope scope;

	int size = 256;

	if (args[0]->IsNumber()) {
		size = args[0]->Int32Value();
	}

	if (size < 1) {
		return ThrowException(Exception::TypeError(String::New("Not supported")));
	}

	NodeFFT *nodefft = new NodeFFT();
	nodefft->reset(size);

	args.This()->SetAccessor(String::New("size"), GetSize, SetSize);

	nodefft->Wrap(args.This());

	return args.This();
}

Handle<Value> NodeFFT::GetSize (Local<String> property, const AccessorInfo &info) {
	NodeFFT *nfft = ObjectWrap::Unwrap<NodeFFT>(info.This());

	return Integer::New(nfft->size);
}

void NodeFFT::SetSize (Local<String> property, Local<Value> value, const AccessorInfo &info) {
	NodeFFT *nfft = ObjectWrap::Unwrap<NodeFFT>(info.This());

	if (!nfft->reset(value->Uint32Value())) {
		/* TODO: Throw an error somehow */
	}
}

Handle<Value> NodeFFT::Forward (const Arguments &args) {
	HandleScope scope;

	NodeFFT *nfft = ObjectWrap::Unwrap<NodeFFT>(args.This());

	int size = nfft->size;

	Float32Array dstReal(args[0]);
	Float32Array dstImag(args[1]);
	Float32Array x(args[2]);

	kiss_fft_cpx *dout = nfft->temp_cplx_o;

	/* if odd N */
	if (size % 2) {
		kiss_fft_cpx *din = nfft->temp_cplx_i;

		for (int i=0; i<size; i++) {
			din[i].r = x[i];
			din[i].i = 0;
		}

		kiss_fft(nfft->kiss_state_cplx, din, dout);
	} else {
		kiss_fft_scalar *din = x.data;

		kiss_fftr(nfft->kiss_state_real, din, dout);
	}

	for (int i=0; i<size; i++) {
		dstReal[i] = dout[i].r;
		dstImag[i] = dout[i].i;
	}

	return Undefined();
}

Handle<Value> NodeFFT::Inverse (const Arguments &args) {
	HandleScope scope;

	NodeFFT *nfft = ObjectWrap::Unwrap<NodeFFT>(args.This());

	int size = nfft->size;

	Float32Array dst(args[0]);
	Float32Array xReal(args[1]);
	Float32Array xImag(args[2]);

	kiss_fft_cpx *din = nfft->temp_cplx_i;
	kiss_fft_scalar *dout = dst.data;

	for (int i=0; i<size; i++) {
		din[i].r = xReal[i];
		din[i].i = xImag[i];
	}

	kiss_fftri(nfft->kiss_state_real_i, din, dout);

	return Undefined();
}

Handle<Value> NodeFFT::ForwardCplx (const Arguments &args) {
	HandleScope scope;

	NodeFFT *nfft = ObjectWrap::Unwrap<NodeFFT>(args.This());

	int size = nfft->size;

	Float32Array dstReal(args[0]);
	Float32Array dstImag(args[1]);
	Float32Array xReal(args[2]);
	Float32Array xImag(args[3]);

	kiss_fft_cpx *din = nfft->temp_cplx_i;
	kiss_fft_cpx *dout = nfft->temp_cplx_o;

	for (int i=0; i<size; i++) {
		din[i].r = xReal[i];
		din[i].i = xImag[i];
	}

	kiss_fft(nfft->kiss_state_cplx, din, dout);

	for (int i=0; i<size; i++) {
		dstReal[i] = dout[i].r;
		dstImag[i] = dout[i].i;
	}

	return Undefined();
}

Handle<Value> NodeFFT::InverseCplx (const Arguments &args) {
	HandleScope scope;

	NodeFFT *nfft = ObjectWrap::Unwrap<NodeFFT>(args.This());

	int size = nfft->size;

	Float32Array dstReal(args[0]);
	Float32Array dstImag(args[1]);
	Float32Array xReal(args[2]);
	Float32Array xImag(args[3]);

	kiss_fft_cpx *din = nfft->temp_cplx_i;
	kiss_fft_cpx *dout = nfft->temp_cplx_o;

	for (int i=0; i<size; i++) {
		din[i].r = xReal[i];
		din[i].i = xImag[i];
	}

	kiss_fft(nfft->kiss_state_cplx_i, din, dout);

	for (int i=0; i<size; i++) {
		dstReal[i] = dout[i].r;
		dstImag[i] = dout[i].i;
	}

	return Undefined();
}
