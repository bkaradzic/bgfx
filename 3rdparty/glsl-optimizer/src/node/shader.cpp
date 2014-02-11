#include "shader.h"

using namespace v8;
using namespace node;

//----------------------------------------------------------------------

Shader::Shader(Compiler* compiler, int type, const char* source)
{
	if (compiler)
	{
		_binding = glslopt_optimize(compiler->getBinding(), (glslopt_shader_type)type, source, 0);
		_compiled = glslopt_get_status(_binding);
	}
	else
	{
		_binding = 0;
		_compiled = false;
	}
}

//----------------------------------------------------------------------

Shader::~Shader()
{
	release();
}

//----------------------------------------------------------------------

void Shader::release()
{
	if (_binding)
	{
		glslopt_shader_delete(_binding);
		_binding = 0;
		_compiled = false;
	}
}

//----------------------------------------------------------------------

const char* Shader::getOutput() const
{
	return (_compiled) ? glslopt_get_output(_binding) : "";
}

//----------------------------------------------------------------------

const char* Shader::getRawOutput() const
{
	return (_compiled) ? glslopt_get_raw_output(_binding) : "";
}

//----------------------------------------------------------------------

const char* Shader::getLog() const
{
	return (_compiled) ? glslopt_get_log(_binding) : "";
}

//----------------------------------------------------------------------

void Shader::Init(Handle<Object> exports)
{
	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->SetClassName(String::NewSymbol("Shader"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	SetPrototypeMethod(tpl, "dispose", Dispose);
	SetPrototypeMethod(tpl, "compiled", Compiled);
	SetPrototypeMethod(tpl, "output", Output);
	SetPrototypeMethod(tpl, "rawOutput", RawOutput);
	SetPrototypeMethod(tpl, "log", Log);

	// Export the class
	Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
	exports->Set(String::NewSymbol("Shader"), constructor);
}

//----------------------------------------------------------------------

Handle<Value> Shader::New(const Arguments& args)
{
	HandleScope scope;

	if (args.Length() == 3)
	{
		// Check the first parameter (compiler)
		Local<Value> args0 = args[0];

		if (args0->IsObject())
		{
			// Check the second parameter (shader type)
			Local<Value> args1 = args[1];

			if (args1->IsInt32())
			{
				// Check the third parameter (source code)
				Local<Value> args2 = args[2];

				if (args2->IsString())
				{
					Compiler* compiler = ObjectWrap::Unwrap<Compiler>(args0->ToObject());
					int type = args1->Int32Value();
					String::Utf8Value sourceCode(args2->ToString());
	
					Shader* obj = new Shader(compiler, type, *sourceCode);
					obj->Wrap(args.This());

					return args.This();
				}
			}
		}
	}

	// Couldn't create the Shader
	return ThrowException(String::New("Invalid arguments"));
}

//----------------------------------------------------------------------

Handle<Value> Shader::Dispose(const Arguments& args)
{
	HandleScope scope;

	Shader* obj = ObjectWrap::Unwrap<Shader>(args.This());
	obj->release();

	return scope.Close(Undefined());
}

//----------------------------------------------------------------------

Handle<Value> Shader::Compiled(const Arguments& args)
{
	HandleScope scope;

	Shader* obj = ObjectWrap::Unwrap<Shader>(args.This());

	return scope.Close(Boolean::New(obj->isCompiled()));
}

//----------------------------------------------------------------------

Handle<Value> Shader::Output(const Arguments& args)
{
	HandleScope scope;

	Shader* obj = ObjectWrap::Unwrap<Shader>(args.This());

	return scope.Close(String::New(obj->getOutput()));
}

//----------------------------------------------------------------------

Handle<Value> Shader::RawOutput(const Arguments& args)
{
	HandleScope scope;

	Shader* obj = ObjectWrap::Unwrap<Shader>(args.This());

	return scope.Close(String::New(obj->getRawOutput()));
}

//----------------------------------------------------------------------

Handle<Value> Shader::Log(const Arguments& args)
{
	HandleScope scope;

	Shader* obj = ObjectWrap::Unwrap<Shader>(args.This());

	return scope.Close(String::New(obj->getLog()));
}
