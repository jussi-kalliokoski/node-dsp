#ifndef NODE_DSP_COMMON_H
#define NODE_DSP_COMMON_H

#define sign(x) (x != x ? x : x < 0.0 || x == -0.0 ? -1.0 : 1.0)
#define modulo(x, y) (x - floor(x / y) * y)
#define fract(x) (modulo(x, 1))

#define MIN2(x, y) (min(x.length, y.length))
#define MIN3(x, y, z) (min(x.length, min(y.length, z.length)))
#define MIN4(x, y, z, q) (min(x.length, min(y.length, min(z.length, q.length))))

#define INVALID_ARGUMENTS_ERROR ThrowException(Exception::Error(String::New("Invalid arguments.")))
#define OVERLAP_ERROR ThrowException(Exception::Error(String::New("Source overlaps destination.")))

#define DSP_METHOD_ACCUMULATOR(name, defaultReturn, algo) Handle<Value> NodeDSP::name (const Arguments &args) {\
	HandleScope scope;\
\
	Float32Array src(args[0]->ToObject());\
\
	if (!src.IsValid()) return INVALID_ARGUMENTS_ERROR;\
\
	if (!src.length) return Number::New(defaultReturn);\
\
	float v = src[0];\
\
	for (int i=1; i<src.length; i++) {\
		v = algo;\
	}\
\
	return Number::New(v);\
}

#define DSP_METHOD_1(name, algo) Handle<Value> NodeDSP::name (const Arguments &args) {\
	HandleScope scope;\
\
	Float32Array dst(args[0]->ToObject());\
	Float32Array x(args[1]->ToObject());\
\
	if (args.Length() == 1) {\
		x.set(dst);\
	} else if (dst.Overlaps(x)) return OVERLAP_ERROR;\
\
	if (\
		!dst.IsValid() ||\
		!x.IsValid()\
	) return INVALID_ARGUMENTS_ERROR;\
\
	int l = MIN2(dst, x);\
\
	for (int i=0; i<l; i++) {\
		dst[i] = algo;\
	}\
\
	return Undefined();\
}

#define DSP_METHOD_2(name, algo) Handle<Value> NodeDSP::name (const Arguments &args) {\
	HandleScope scope;\
\
	Float32Array dst(args[0]->ToObject());\
	Float32Array x(args[1]->ToObject());\
	Float32Array y(args[2]->ToObject());\
\
	if (args.Length() == 2) {\
		y.set(x);\
		x.set(dst);\
	} else if (dst.Overlaps(x)) return OVERLAP_ERROR;\
	if (dst.Overlaps(y)) return OVERLAP_ERROR;\
\
	if (\
		!dst.IsValid() ||\
		!x.IsValid() ||\
		!y.IsValid()\
	) return INVALID_ARGUMENTS_ERROR;\
\
	int l = MIN3(dst, x, y);\
\
	for (int i=0; i<l; i++) {\
		dst[i] = algo;\
	}\
\
	return Undefined();\
}

#define DSP_METHOD_2_OVERLOADING(name, algo1, algo2) Handle<Value> NodeDSP::name (const Arguments &args) {\
	HandleScope scope;\
\
	int n = 0;\
	Float32Array dst(args[n++]->ToObject());\
	Float32Array x(args[n++]->ToObject());\
	Float32Array y(args[n++]->ToObject());\
\
	if (args.Length() == 2) {\
		y.set(x);\
		x.set(dst);\
		n--;\
	} else if (dst.Overlaps(x)) return OVERLAP_ERROR;\
	if (dst.Overlaps(y)) return OVERLAP_ERROR;\
\
	if (!dst.IsValid() || !x.IsValid()) return INVALID_ARGUMENTS_ERROR;\
\
	if (!y.IsValid()) {\
		if (!args[n-1]->IsNumber()) return INVALID_ARGUMENTS_ERROR;\
\
		float yy = args[n-1]->NumberValue();\
		int l = MIN2(dst, x);\
\
		for (int i=0; i<l; i++) {\
			dst[i] = algo1;\
		}\
	} else {\
		int l = MIN3(dst, x, y);\
\
		for (int i=0; i<l; i++) {\
			dst[i] = algo2;\
		}\
	}\
\
	return Undefined();\
}

#define DSP_METHOD_3_OVERLOADING(name, algo1, algo2) Handle<Value> NodeDSP::name (const Arguments &args) {\
	HandleScope scope;\
\
	int n = 0;\
	Float32Array dst(args[n++]->ToObject());\
	Float32Array x(args[n++]->ToObject());\
	Float32Array y(args[n++]->ToObject());\
	Float32Array z(args[n++]->ToObject());\
\
	if (args.Length() == 3) {\
		z.set(y);\
		y.set(x);\
		x.set(dst);\
		n--;\
	} else if (dst.Overlaps(x)) return OVERLAP_ERROR;\
	if (dst.Overlaps(y)) return OVERLAP_ERROR;\
	if (dst.Overlaps(z)) return OVERLAP_ERROR;\
\
	if (\
		!dst.IsValid() ||\
		!x.IsValid() ||\
		!y.IsValid()\
	) return INVALID_ARGUMENTS_ERROR;\
\
	if (!z.IsValid()) {\
		if (!args[n-1]->IsNumber()) return INVALID_ARGUMENTS_ERROR;\
\
		float zz = args[n-1]->NumberValue();\
		int l = MIN3(dst, x, y);\
\
		for (int i=0; i<l; i++) {\
			dst[i] = algo1;\
		}\
	} else {\
		int l = min(MIN2(dst, x), MIN2(y, z));\
\
		for (int i=0; i<l; i++) {\
			dst[i] = algo2;\
		}\
	}\
\
	return Undefined();\
}

#define DSP_METHOD_CPLX_2_OVERLOADING(name, algo1, algo2) Handle<Value> NodeDSP::name (const Arguments &args) {\
	HandleScope scope;\
\
	int n = 0;\
	Float32Array dstReal(args[n++]->ToObject());\
	Float32Array dstImag(args[n++]->ToObject());\
	Float32Array xReal(args[n++]->ToObject());\
	Float32Array xImag(args[n++]->ToObject());\
	Float32Array yReal(args[n++]->ToObject());\
	Float32Array yImag(args[n++]->ToObject());\
\
	if (args.Length() == 4) {\
		yReal.set(xReal);\
		yImag.set(xImag);\
		xReal.set(dstReal);\
		xImag.set(dstImag);\
		n -= 2;\
	} else if (\
		dstReal.Overlaps(xReal) ||\
		dstImag.Overlaps(xImag) ||\
		dstReal.Overlaps(xImag) ||\
		dstImag.Overlaps(xReal)\
	) return OVERLAP_ERROR;\
	if (\
		dstReal.Overlaps(yReal) ||\
		dstImag.Overlaps(yImag) ||\
		dstReal.Overlaps(yImag) ||\
		dstImag.Overlaps(yReal)\
	) return OVERLAP_ERROR;\
\
	if (\
		!dstReal.IsValid() ||\
		!dstImag.IsValid() ||\
		!xReal.IsValid() ||\
		!xImag.IsValid()\
	) return INVALID_ARGUMENTS_ERROR;\
\
	if (!yReal.IsValid() || !yImag.IsValid()) {\
		if (!args[n-2]->IsNumber()) return INVALID_ARGUMENTS_ERROR;\
		if (!args[n-1]->IsNumber()) return INVALID_ARGUMENTS_ERROR;\
\
		float yr = args[n-2]->NumberValue();\
		float yi = args[n-1]->NumberValue();\
		int l = min(MIN2(dstReal, dstImag), MIN2(xReal, xImag));\
\
		for (int i=0; i<l; i++) {\
			float x_r = xReal[i];\
			algo1\
		}\
	} else {\
		int l = min(MIN3(dstReal, dstImag, xReal),\
			MIN3(xImag, yReal, yImag));\
\
		for (int i=0; i<l; i++) {\
			float x_r = xReal[i];\
			float y_r = yReal[i];\
			algo2\
		}\
	}\
\
	return Undefined();\
}

#define DSP_METHOD_OP(name, op) DSP_METHOD_2_OVERLOADING(name, x[i] op yy, x[i] op y[i])
#define DSP_METHOD_ALG(name, method) DSP_METHOD_1(name, method(x[i]))

#endif
