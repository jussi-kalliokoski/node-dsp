#ifndef NODE_DSP_FFT_H
#define NODE_DSP_FFT_H

#include <node.h>
#include "float32array.h"
#include "kiss_fft/kiss_fft.h"
#include "kiss_fft/kiss_fftr.h"

class NodeFFT : public node::ObjectWrap {
public:
	static void Initialize (v8::Handle<v8::Object> target);

	NodeFFT ();

	static v8::Handle<v8::Value> New (const v8::Arguments &args);

	static v8::Handle<v8::Value> GetSize (v8::Local<v8::String> property, const v8::AccessorInfo &info);
	static void SetSize (v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::AccessorInfo &info);

	static v8::Handle<v8::Value> Forward (const v8::Arguments &args);
	static v8::Handle<v8::Value> Inverse (const v8::Arguments &args);
	static v8::Handle<v8::Value> ForwardCplx (const v8::Arguments &args);
	static v8::Handle<v8::Value> InverseCplx (const v8::Arguments &args);

	int reset (int ssize);

	int size;
	kiss_fft_cfg kiss_state_cplx;
	kiss_fft_cfg kiss_state_cplx_i;
	kiss_fftr_cfg kiss_state_real;
	kiss_fftr_cfg kiss_state_real_i;
	kiss_fft_cpx *temp_cplx_i;
	kiss_fft_cpx *temp_cplx_o;
};

#endif
