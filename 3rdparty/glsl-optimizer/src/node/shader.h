#ifndef SHADER_H
#define SHADER_H

#include "compiler.h"

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

	static v8::Handle<v8::Value> New(const v8::Arguments& args);
	static v8::Handle<v8::Value> Dispose(const v8::Arguments& args);

	static v8::Handle<v8::Value> Compiled(const v8::Arguments& args);
	static v8::Handle<v8::Value> Output(const v8::Arguments& args);
	static v8::Handle<v8::Value> RawOutput(const v8::Arguments& args);
	static v8::Handle<v8::Value> Log(const v8::Arguments& args);
};

#endif
