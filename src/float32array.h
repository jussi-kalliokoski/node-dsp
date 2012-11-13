#ifndef NODE_DSP_FLOAT32ARRAY
#define NODE_DSP_FLOAT32ARRAY

#include <node.h>

class Float32Array {
public:
	float *data;
	int length;

	Float32Array (v8::Local<v8::Object> obj);

	float& operator[] (int index) { return data[index]; };

	int IsValid () { return data != NULL; };

	int Overlaps (const Float32Array that) {
		return
			(data >= that.data &&
			data < that.data + that.length) ||
			(that.data >= data &&
			that.data < data + length)
		;
	};
};

#endif
