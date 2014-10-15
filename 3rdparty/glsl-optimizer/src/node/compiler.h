#ifndef COMPILER_H
#define COMPILER_H

#include <node.h>
#include <nan.h>
#include <glsl_optimizer.h>

class Compiler : public node::ObjectWrap {
public:
	static void Init(v8::Handle<v8::Object> exports);

	inline glslopt_ctx* getBinding() const { return _binding; }

	void release();

private:
	Compiler(glslopt_target target);
	~Compiler();

	glslopt_ctx* _binding;

	static NAN_METHOD(New);
	static NAN_METHOD(Dispose);
	static v8::Persistent<v8::Function> constructor;
};

#endif
