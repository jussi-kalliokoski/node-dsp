#include <node.h>

#include "dsp.h"
#include "filter.h"
#include "fft.h"

void init (v8::Handle<v8::Object> target) {
	v8::HandleScope scope;

	NodeDSP::Initialize(target);
	NodeFilter::Initialize(target);
	NodeFFT::Initialize(target);
}

NODE_MODULE(node_dsp, init)
