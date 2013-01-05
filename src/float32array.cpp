#include <node.h>

#include "float32array.h"

using namespace v8;

Float32Array::Float32Array (Local<Object> obj) :
	data(NULL),
	length(0)
{
	init(obj);
}

Float32Array::Float32Array (Local<Value> val) :
	data(NULL),
	length(0)
{
	if (!val->IsObject()) return;
	init(val->ToObject());
}

Local<Object> Float32Array::New (int length) {
	HandleScope scope;

	Local<Function> float32_array_constructor;
	Local<Object> global = Context::GetCurrent()->Global();
	Local<Value> val = global->Get(String::New("Float32Array"));
	assert(!val.IsEmpty() && "type not found: Float32Array");
	assert(val->IsFunction() && "not a constructor: Float32Array");
	float32_array_constructor = Local<Function>::New(val.As<Function>());

	Local<Value> size = Integer::NewFromUnsigned(length);
	Local<Object> array = float32_array_constructor->NewInstance(1, &size);

	return array;
}

void Float32Array::init (Local<Object> obj) {
	if (
		obj->GetIndexedPropertiesExternalArrayDataType() != kExternalFloatArray
	) return;

	length = obj->GetIndexedPropertiesExternalArrayDataLength();
	data = static_cast<float*>(
		obj->GetIndexedPropertiesExternalArrayData()
	);
}
