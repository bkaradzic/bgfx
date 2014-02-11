#ifndef COMPILER_H
#define COMPILER_H

#include <node.h>
#include <glsl_optimizer.h>

class Compiler : public node::ObjectWrap {
public:
	static void Init(v8::Handle<v8::Object> exports);

	inline glslopt_ctx* getBinding() const { return _binding; }

	void release();

private:
	Compiler(bool essl);
	~Compiler();

	glslopt_ctx* _binding;

	static v8::Handle<v8::Value> New(const v8::Arguments& args);
	static v8::Handle<v8::Value> Dispose(const v8::Arguments& args);
};

#endif
