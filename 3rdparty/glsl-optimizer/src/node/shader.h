#ifndef SHADER_H
#define SHADER_H

#include "compiler.h"
#include <node.h>
#include <nan.h>
#include <glsl_optimizer.h>

class Shader : public node::ObjectWrap {
public:
	static void Init(v8::Handle<v8::Object> exports);

	inline bool isCompiled() const { return _compiled; }
	const char* getOutput() const;
	const char* getRawOutput() const;
	const char* getLog() const;

	void release();

private:
	Shader(Compiler* compiler, int type, const char* source);
	~Shader();

	glslopt_shader* _binding;
	bool _compiled;

	static NAN_METHOD(New);
	static NAN_METHOD(Dispose);

	static NAN_METHOD(Compiled);
	static NAN_METHOD(Output);
	static NAN_METHOD(RawOutput);
	static NAN_METHOD(Log);
	static v8::Persistent<v8::Function> constructor;
};

#endif
