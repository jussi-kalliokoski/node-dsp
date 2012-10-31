#include <math.h>
#include <algorithm>

#include "dsp.h"
#include "common.h"

using namespace v8;
using namespace node;
using namespace std;

extern "C" void init (v8::Handle<v8::Object> target) {
	v8::HandleScope scope;

	NodeDSP::Initialize(target);
}


void NodeDSP::Initialize (Handle<Object> target) {
	HandleScope scope;

	SetMethod(target, "add", Add);
	SetMethod(target, "abs", Abs);
//	SetMethod(target, "absCplx", AbsCplx);
	SetMethod(target, "acos", Acos);
	SetMethod(target, "add", Add);
	SetMethod(target, "asin", Asin);
	SetMethod(target, "atan", Atan);
	SetMethod(target, "atan2", Atan2);
	SetMethod(target, "ceil", Ceil);
//	SetMethod(target, "clamp", Clamp);
	SetMethod(target, "cos", Cos);
	SetMethod(target, "div", Div);
	SetMethod(target, "divCplx", DivCplx);
	SetMethod(target, "exp", Exp);
	SetMethod(target, "floor", Floor);
	SetMethod(target, "fract", Fract);
	SetMethod(target, "log", Log);
	SetMethod(target, "madd", Madd);
	SetMethod(target, "max", Max);
	SetMethod(target, "min", Min);
	SetMethod(target, "mul", Mul);
	SetMethod(target, "mulCplx", MulCplx);
//	SetMethod(target, "pack", Pack);
	SetMethod(target, "pow", Pow);
//	SetMethod(target, "ramp", Ramp);
//	SetMethod(target, "random", Random);
	SetMethod(target, "round", Round);
//	SetMethod(target, "sampleCubic", SampleCubic);
//	SetMethod(target, "sampleLinear", SampleLinear);
	SetMethod(target, "sign", Sign);
	SetMethod(target, "sin", Sin);
	SetMethod(target, "sqrt", Sqrt);
	SetMethod(target, "sub", Sub);
	SetMethod(target, "sum", Sum);
	SetMethod(target, "tan", Tan);
//	SetMethod(target, "unpack", Unpack);
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

Handle<Value> NodeDSP::MulCplx (const Arguments &args) {
	HandleScope scope;

	getFloat32Array(args[0]->ToObject(), dstReal, ldstr);
	getFloat32Array(args[1]->ToObject(), dstImag, ldsti);
	getFloat32Array(args[2]->ToObject(), xReal, lxr);
	getFloat32Array(args[3]->ToObject(), xImag, lxi);
	getFloat32Array(args[4]->ToObject(), yReal, lyr);
	getFloat32Array(args[5]->ToObject(), yImag, lyi);

	if (
		dstReal == NULL ||
		dstImag == NULL ||
		xReal == NULL ||
		xImag == NULL
	) return INVALID_ARGUMENTS_ERROR;

	if (yReal == NULL || yImag == NULL) {
		if (!args[4]->IsNumber()) return INVALID_ARGUMENTS_ERROR;
		if (!args[5]->IsNumber()) return INVALID_ARGUMENTS_ERROR;

		float yr = args[4]->NumberValue();
		float yi = args[5]->NumberValue();
		int l = min(ldstr, min(ldsti, min(lxr, lxi)));

		for (int i=0; i<l; i++) {
			float x_r = xReal[i];
			dstReal[i] = x_r * yr - xImag[i] * yi;
			dstImag[i] = x_r * yi + xImag[i] * yr;
		}
	} else {
		int l = min(ldstr, min(ldsti, min(lxr, min(lxi, min(lyr, lyi)))));

		for (int i=0; i<l; i++) {
			float x_r = xReal[i];
			float y_r = yReal[i];
			dstReal[i] = x_r * y_r - xImag[i] * yImag[i];
			dstImag[i] = x_r * yImag[i] + xImag[i] * y_r;
		}
	}

	return Undefined();
}

/* FIXME: Fix this as the spec is fixed */
Handle<Value> NodeDSP::DivCplx (const Arguments &args) {
	HandleScope scope;

	getFloat32Array(args[0]->ToObject(), dstReal, ldstr);
	getFloat32Array(args[1]->ToObject(), dstImag, ldsti);
	getFloat32Array(args[2]->ToObject(), xReal, lxr);
	getFloat32Array(args[3]->ToObject(), xImag, lxi);
	getFloat32Array(args[4]->ToObject(), yReal, lyr);
	getFloat32Array(args[5]->ToObject(), yImag, lyi);

	if (
		dstReal == NULL ||
		dstImag == NULL ||
		xReal == NULL ||
		xImag == NULL
	) return INVALID_ARGUMENTS_ERROR;

	if (yReal == NULL || yImag == NULL) {
		if (!args[4]->IsNumber()) return INVALID_ARGUMENTS_ERROR;
		if (!args[5]->IsNumber()) return INVALID_ARGUMENTS_ERROR;

		float yr = args[4]->NumberValue();
		float yi = args[5]->NumberValue();
		int l = min(ldstr, min(ldsti, min(lxr, lxi)));

		for (int i=0; i<l; i++) {
			float denom = yr * yr + yi * yi;
			float x_r = xReal[i];
			dstReal[i] = (x_r * yr + xImag[i] * yi) / denom;
			dstImag[i] = (xImag[i] * yr - x_r * yi) / denom;
		}
	} else {
		int l = min(ldstr, min(ldsti, min(lxr, min(lxi, min(lyr, lyi)))));

		for (int i=0; i<l; i++) {
			float denom = yReal[i] * yReal[i] + yImag[i] * yImag[i];
			float x_r = xReal[i];
			float y_r = yReal[i];
			dstReal[i] = (x_r * y_r + xImag[i] * yImag[i]) / denom;
			dstImag[i] = (x_r * yImag[i] - xImag[i] * y_r) / denom;
		}
	}

	return Undefined();
}
