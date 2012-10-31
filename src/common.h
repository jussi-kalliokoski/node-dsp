#ifndef NODE_DSP_COMMON_H
#define NODE_DSP_COMMON_H

#define sign(x) (x != x ? x : x < 0.0 || x == -0.0 ? -1.0 : 1.0)
#define modulo(x, y) (x - floor(x / y) * y)
#define fract(x) (modulo(x, 1))

#define getFloat32Array(srcName, dstName, lengthName) float *dstName; int lengthName = 0; {\
	Local<Object> obj = srcName;\
	if (obj->GetIndexedPropertiesExternalArrayDataType() != kExternalFloatArray) dstName = NULL;\
	else { lengthName = obj->GetIndexedPropertiesExternalArrayDataLength();\
	dstName = static_cast<float*>(obj->GetIndexedPropertiesExternalArrayData());}}

#define check_malloc(varname, vartype)\
	vartype *varname;\
	varname = (vartype*) malloc(sizeof(*varname));\
	if (varname == NULL)

#define INVALID_ARGUMENTS_ERROR ThrowException(Exception::Error(String::New("Invalid arguments.")))

#define DSP_METHOD_ACCUMULATOR(name, defaultReturn, algo) Handle<Value> NodeDSP::name (const Arguments &args) {\
	HandleScope scope;\
\
	getFloat32Array(args[0]->ToObject(), src, l);\
\
	if (src == NULL) return INVALID_ARGUMENTS_ERROR;\
\
	if (!l) return Number::New(defaultReturn);\
\
	float v = src[0];\
\
	for (int i=1; i<l; i++) {\
		v = algo;\
	}\
\
	return Number::New(v);\
}

#define DSP_METHOD_1(name, algo) Handle<Value> NodeDSP::name (const Arguments &args) {\
	HandleScope scope;\
\
	getFloat32Array(args[0]->ToObject(), dst, ldst);\
	getFloat32Array(args[1]->ToObject(), x, lx);\
\
	if (dst == NULL || x == NULL) return INVALID_ARGUMENTS_ERROR;\
\
	int l = min(ldst, lx);\
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
	getFloat32Array(args[0]->ToObject(), dst, ldst);\
	getFloat32Array(args[1]->ToObject(), x, lx);\
	getFloat32Array(args[2]->ToObject(), y, ly);\
\
	if (dst == NULL || x == NULL || y == NULL) return INVALID_ARGUMENTS_ERROR;\
\
	int l = min(ldst, min(lx, ly));\
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
	getFloat32Array(args[0]->ToObject(), dst, ldst);\
	getFloat32Array(args[1]->ToObject(), x, lx);\
	getFloat32Array(args[2]->ToObject(), y, ly);\
\
	if (dst == NULL || x == NULL) return INVALID_ARGUMENTS_ERROR;\
\
	if (y == NULL) {\
		if (!args[2]->IsNumber()) return INVALID_ARGUMENTS_ERROR;\
\
		float yy = args[2]->NumberValue();\
		int l = min(ldst, lx);\
\
		for (int i=0; i<l; i++) {\
			dst[i] = algo1;\
		}\
	} else {\
		int l = min(ldst, min(lx, ly));\
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
	getFloat32Array(args[0]->ToObject(), dst, ldst);\
	getFloat32Array(args[1]->ToObject(), x, lx);\
	getFloat32Array(args[2]->ToObject(), y, ly);\
	getFloat32Array(args[3]->ToObject(), z, lz);\
\
	if (dst == NULL || x == NULL || y == NULL) return INVALID_ARGUMENTS_ERROR;\
\
	if (y == NULL) {\
		if (!args[3]->IsNumber()) return INVALID_ARGUMENTS_ERROR;\
\
		float zz = args[3]->NumberValue();\
		int l = min(ldst, min(lx, ly));\
\
		for (int i=0; i<l; i++) {\
			dst[i] = algo1;\
		}\
	} else {\
		int l = min(ldst, min(lx, min(ly, lz)));\
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
	getFloat32Array(args[0]->ToObject(), dstReal, ldstr);\
	getFloat32Array(args[1]->ToObject(), dstImag, ldsti);\
	getFloat32Array(args[2]->ToObject(), xReal, lxr);\
	getFloat32Array(args[3]->ToObject(), xImag, lxi);\
	getFloat32Array(args[4]->ToObject(), yReal, lyr);\
	getFloat32Array(args[5]->ToObject(), yImag, lyi);\
\
	if (\
		dstReal == NULL || dstImag == NULL\
		xReal == NULL || xImag == NULL\
	) return INVALID_ARGUMENTS_ERROR;\
\
	if (yReal == NULL || yImag == NULL) {\
		if (!args[4]->IsNumber()) return INVALID_ARGUMENTS_ERROR;\
		if (!args[5]->IsNumber()) return INVALID_ARGUMENTS_ERROR;\
\
		float yr = args[4]->NumberValue();\
		float yi = args[5]->NumberValue();\
		int l = min(ldstr, min(ldsti, min(lxr, lxi)));\
\
		for (int i=0; i<l; i++) algo1\
	} else {\
		int l = min(ldstr, min(ldsti, min(lxr, min(lxi, min(lyr, lyi)))));\
\
		for (int i=0; i<l; i++) algo2\
	}\
\
	return Undefined();\
}

#define DSP_METHOD_OP(name, op) DSP_METHOD_2_OVERLOADING(name, x[i] op yy, x[i] op y[i])
#define DSP_METHOD_ALG(name, method) DSP_METHOD_1(name, method(x[i]))

#endif
