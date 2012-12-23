#ifndef NODE_DSP_FILTER_H
#define NODE_DSP_FILTER_H

#include <node.h>
#include "float32array.h"

class NodeFilter : public node::ObjectWrap {
public:
	static void Initialize (v8::Handle<v8::Object> target);

	NodeFilter (float *bb, int bbSize, float *aa, int aaSize);

	static v8::Handle<v8::Value> New (const v8::Arguments &args);

	static v8::Handle<v8::Value> Filter (const v8::Arguments &args);
	static v8::Handle<v8::Value> ClearHistory (const v8::Arguments &args);

	void clearHistory ();

	float *b;
	int bSize;

	float *a;
	int aSize;

	float *bHist;
	float *aHist;
};

#endif
