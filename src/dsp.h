#ifndef NODE_DSP_MAIN_H
#define NODE_DSP_MAIN_H

#include <node.h>

class NodeDSP : public node::ObjectWrap {
public:
	static void Initialize (v8::Handle<v8::Object> target);

	static v8::Handle<v8::Value> Abs (const v8::Arguments &args);
	static v8::Handle<v8::Value> AbsCplx (const v8::Arguments &args);
	static v8::Handle<v8::Value> Acos (const v8::Arguments &args);
	static v8::Handle<v8::Value> Add (const v8::Arguments &args);
	static v8::Handle<v8::Value> Asin (const v8::Arguments &args);
	static v8::Handle<v8::Value> Atan (const v8::Arguments &args);
	static v8::Handle<v8::Value> Atan2 (const v8::Arguments &args);
	static v8::Handle<v8::Value> Ceil (const v8::Arguments &args);
	static v8::Handle<v8::Value> Clamp (const v8::Arguments &args);
	static v8::Handle<v8::Value> Cos (const v8::Arguments &args);
	static v8::Handle<v8::Value> Div (const v8::Arguments &args);
	static v8::Handle<v8::Value> DivCplx (const v8::Arguments &args);
	static v8::Handle<v8::Value> Exp (const v8::Arguments &args);
	static v8::Handle<v8::Value> Floor (const v8::Arguments &args);
	static v8::Handle<v8::Value> Fract (const v8::Arguments &args);
	static v8::Handle<v8::Value> Log (const v8::Arguments &args);
	static v8::Handle<v8::Value> Madd (const v8::Arguments &args);
	static v8::Handle<v8::Value> Max (const v8::Arguments &args);
	static v8::Handle<v8::Value> Min (const v8::Arguments &args);
	static v8::Handle<v8::Value> Mul (const v8::Arguments &args);
	static v8::Handle<v8::Value> MulCplx (const v8::Arguments &args);
	static v8::Handle<v8::Value> Pack (const v8::Arguments &args);
	static v8::Handle<v8::Value> Pow (const v8::Arguments &args);
	static v8::Handle<v8::Value> Ramp (const v8::Arguments &args);
	static v8::Handle<v8::Value> Random (const v8::Arguments &args);
	static v8::Handle<v8::Value> Round (const v8::Arguments &args);
	static v8::Handle<v8::Value> SampleCubic (const v8::Arguments &args);
	static v8::Handle<v8::Value> SampleLinear (const v8::Arguments &args);
	static v8::Handle<v8::Value> Sign (const v8::Arguments &args);
	static v8::Handle<v8::Value> Sin (const v8::Arguments &args);
	static v8::Handle<v8::Value> Sqrt (const v8::Arguments &args);
	static v8::Handle<v8::Value> Sub (const v8::Arguments &args);
	static v8::Handle<v8::Value> Sum (const v8::Arguments &args);
	static v8::Handle<v8::Value> Tan (const v8::Arguments &args);
	static v8::Handle<v8::Value> Unpack (const v8::Arguments &args);
};

#endif
