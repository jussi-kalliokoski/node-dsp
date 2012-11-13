#include <node.h>

#include "float32array.h"

using namespace v8;

Float32Array::Float32Array (v8::Local<v8::Object> obj) {
	if (obj->GetIndexedPropertiesExternalArrayDataType() != kExternalFloatArray) {
		data = NULL;
	} else {
		length = obj->GetIndexedPropertiesExternalArrayDataLength();
		data = static_cast<float*>(
			obj->GetIndexedPropertiesExternalArrayData()
		);
	}
}
