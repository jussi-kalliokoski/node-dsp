#include <math.h>
#include <algorithm>
#include <time.h>

#include "dsp.h"
#include "common.h"
#include "float32array.h"

using namespace v8;
using namespace node;
using namespace std;

void NodeDSP::Initialize (Handle<Object> target) {
	HandleScope scope;

	srand((unsigned) time(0));

	Handle<Object> dsp = Object::New();

	SetMethod(dsp, "add", Add);
	SetMethod(dsp, "abs", Abs);
	SetMethod(dsp, "absCplx", AbsCplx);
	SetMethod(dsp, "acos", Acos);
	SetMethod(dsp, "add", Add);
	SetMethod(dsp, "asin", Asin);
	SetMethod(dsp, "atan", Atan);
	SetMethod(dsp, "atan2", Atan2);
	SetMethod(dsp, "ceil", Ceil);
//	SetMethod(dsp, "clamp", Clamp);
	SetMethod(dsp, "cos", Cos);
	SetMethod(dsp, "div", Div);
	SetMethod(dsp, "divCplx", DivCplx);
	SetMethod(dsp, "exp", Exp);
	SetMethod(dsp, "floor", Floor);
	SetMethod(dsp, "fract", Fract);
	SetMethod(dsp, "log", Log);
	SetMethod(dsp, "madd", Madd);
	SetMethod(dsp, "max", Max);
	SetMethod(dsp, "min", Min);
	SetMethod(dsp, "mul", Mul);
	SetMethod(dsp, "mulCplx", MulCplx);
//	SetMethod(dsp, "pack", Pack);
	SetMethod(dsp, "pow", Pow);
	SetMethod(dsp, "ramp", Ramp);
	SetMethod(dsp, "random", Random);
	SetMethod(dsp, "round", Round);
//	SetMethod(dsp, "sampleCubic", SampleCubic);
//	SetMethod(dsp, "sampleLinear", SampleLinear);
	SetMethod(dsp, "sign", Sign);
	SetMethod(dsp, "sin", Sin);
	SetMethod(dsp, "sqrt", Sqrt);
	SetMethod(dsp, "sub", Sub);
	SetMethod(dsp, "sum", Sum);
	SetMethod(dsp, "tan", Tan);
//	SetMethod(dsp, "unpack", Unpack);

	target->Set(String::NewSymbol("DSP"), dsp);
}

DSP_METHOD_OP(Add, +)
DSP_METHOD_OP(Sub, -)
DSP_METHOD_OP(Mul, *)
DSP_METHOD_OP(Div, /)
DSP_METHOD_3_OVERLOADING(Madd, x[i] + y[i] * zz, x[i] + y[i] * z[i])

DSP_METHOD_ALG(Sin, sin)
DSP_METHOD_ALG(Cos, cos)
DSP_METHOD_ALG(Tan, tan)
DSP_METHOD_ALG(Asin, asin)
DSP_METHOD_ALG(Acos, acos)
DSP_METHOD_ALG(Atan, atan)
DSP_METHOD_2(Atan2, atan2(x[i], y[i]))

DSP_METHOD_1(Sign, sign(x[i]))
DSP_METHOD_1(Fract, fract(x[i]))
DSP_METHOD_ALG(Abs, fabs)
DSP_METHOD_ALG(Ceil, ceil)
DSP_METHOD_ALG(Floor, floor)
DSP_METHOD_ALG(Round, round)

DSP_METHOD_ALG(Sqrt, sqrt)
DSP_METHOD_2_OVERLOADING(Pow, pow(x[i], yy), pow(x[i], y[i]))

DSP_METHOD_ALG(Exp, exp)
DSP_METHOD_ALG(Log, log)

DSP_METHOD_ACCUMULATOR(Sum, 0.0, src[i] + v)
DSP_METHOD_ACCUMULATOR(Max, 1.0/0.0, max(src[i], v))
DSP_METHOD_ACCUMULATOR(Min, 1.0/0.0, min(src[i], v))

DSP_METHOD_CPLX_2_OVERLOADING(MulCplx,
	dstReal[i] = x_r * yr - xImag[i] * yi;
	dstImag[i] = x_r * yi + xImag[i] * yr;
,
	dstReal[i] = x_r * y_r - xImag[i] * yImag[i];
	dstImag[i] = x_r * yImag[i] + xImag[i] * y_r;
)

DSP_METHOD_CPLX_2_OVERLOADING(DivCplx,
	float denom = yr * yr + yi * yi;
	dstReal[i] = (x_r * yr + xImag[i] * yi) / denom;
	dstImag[i] = (x_r * yi - xImag[i] * yr) / denom;
,
	float denom = y_r * y_r + yImag[i] * yImag[i];
	dstReal[i] = (x_r * y_r + xImag[i] * yImag[i]) / denom;
	dstImag[i] = (x_r * yImag[i] - xImag[i] * y_r) / denom;
)

DSP_METHOD_2(AbsCplx, sqrt(pow(x[i], 2) + pow(y[i], 2)))

Handle<Value> NodeDSP::Ramp (const Arguments &args) {
	HandleScope scope;

	Float32Array dst(args[0]->ToObject());

	if (
		!dst.IsValid() ||
		!args[1]->IsNumber() ||
		!args[2]->IsNumber()
	) return INVALID_ARGUMENTS_ERROR;

	double first = args[1]->NumberValue();
	double last = args[2]->NumberValue();

	for (int i=0; i<dst.length; i++) {
		dst[i] = first + i * ((last - first) / (dst.length - 1));
	}

	return Undefined();
}

Handle<Value> NodeDSP::Random (const Arguments &args) {
	HandleScope scope;

	Float32Array dst(args[0]->ToObject());

	if (!dst.IsValid()) return INVALID_ARGUMENTS_ERROR;

	double low = args[1]->IsNumber() ? args[1]->NumberValue() : 0.0;
	double high = args[2]->IsNumber() ? args[2]->NumberValue() : 1.0;

	for (int i=0; i<dst.length; i++) {
		dst[i] = low + (float) rand() / ((float) RAND_MAX / (high - low));
	}

	return Undefined();
}

Handle<Value> NodeDSP::Clamp (const Arguments &args) {
	HandleScope scope;

	int n = 0;
	Float32Array dst(args[n++]->ToObject());
	Float32Array x(args[n++]->ToObject());

	if (args.Length() == 3) {
		x.set(dst);
		n--;
	} else if (dst.Overlaps(x)) return OVERLAP_ERROR;

	if (
		!dst.IsValid() ||
		!x.IsValid() ||
		!args[n+0]->IsNumber() ||
		!args[n+1]->IsNumber()
	) return INVALID_ARGUMENTS_ERROR;

	float minArg = args[n+0]->NumberValue();
	float maxArg = args[n+1]->NumberValue();

	int l = MIN2(dst, x);

	for (int i=0; i<l; i++) {
		dst[i] = clamp(x[i], minArg, maxArg);
	}

	return Undefined();
}
