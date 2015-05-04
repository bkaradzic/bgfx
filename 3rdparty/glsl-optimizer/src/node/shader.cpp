#include "shader.h"
#include <nan.h>

using namespace v8;
using namespace node;

Persistent<Function> Shader::constructor;

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
	NanScope();

	// Prepare constructor template
	Local<FunctionTemplate> tpl = NanNew<FunctionTemplate>(New);
	tpl->SetClassName(NanNew<String>("Shader"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	NanSetPrototypeTemplate(tpl, "dispose", NanNew<FunctionTemplate>(Dispose));
	NanSetPrototypeTemplate(tpl, "compiled", NanNew<FunctionTemplate>(Compiled));
	NanSetPrototypeTemplate(tpl, "output", NanNew<FunctionTemplate>(Output));
	NanSetPrototypeTemplate(tpl, "rawOutput", NanNew<FunctionTemplate>(RawOutput));
	NanSetPrototypeTemplate(tpl, "log", NanNew<FunctionTemplate>(Log));

	// Export the class
	NanAssignPersistent<Function>(constructor, tpl->GetFunction());
	exports->Set(NanNew<String>("Shader"), tpl->GetFunction());
}

//----------------------------------------------------------------------

Handle<Value> Shader::New(const Arguments& args)
{
	NanScope();

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
	NanThrowError("Invalid arguments");
}

//----------------------------------------------------------------------

NAN_METHOD(Shader::Dispose)
{
	NanScope();

	Shader* obj = ObjectWrap::Unwrap<Shader>(args.This());
	obj->release();

	NanReturnUndefined();
}

//----------------------------------------------------------------------

NAN_METHOD(Shader::Compiled)
{
	NanScope();

	Shader* obj = ObjectWrap::Unwrap<Shader>(args.This());

	NanReturnValue(NanNew<Boolean>(obj->isCompiled()));
}

//----------------------------------------------------------------------

NAN_METHOD(Shader::Output)
{
	NanScope();

	Shader* obj = ObjectWrap::Unwrap<Shader>(args.This());

	NanReturnValue(NanNew<String>(obj->getOutput()));
}

//----------------------------------------------------------------------

NAN_METHOD(Shader::RawOutput)
{
	NanScope();

	Shader* obj = ObjectWrap::Unwrap<Shader>(args.This());

	NanReturnValue(NanNew<String>(obj->getRawOutput()));
}

//----------------------------------------------------------------------

NAN_METHOD(Shader::Log)
{
	NanScope();

	Shader* obj = ObjectWrap::Unwrap<Shader>(args.This());

	NanReturnValue(NanNew<String>(obj->getLog()));
}
