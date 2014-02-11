#include "compiler.h"

using namespace v8;
using namespace node;

//----------------------------------------------------------------------

Compiler::Compiler(bool essl)
{
	_binding = glslopt_initialize(essl);
}

//----------------------------------------------------------------------

Compiler::~Compiler()
{
	release();
}

//----------------------------------------------------------------------

void Compiler::release()
{
	if (_binding)
	{
		glslopt_cleanup(_binding);

		_binding = 0;
	}
}

//----------------------------------------------------------------------

void Compiler::Init(Handle<Object> exports)
{
	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->SetClassName(String::NewSymbol("Compiler"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	SetPrototypeMethod(tpl, "dispose", Dispose);

	// Export the class
	Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
	exports->Set(String::NewSymbol("Compiler"), constructor);
}

//----------------------------------------------------------------------

Handle<Value> Compiler::New(const Arguments& args)
{
	HandleScope scope;

	bool essl = args[0]->IsUndefined() ? true : args[0]->BooleanValue();

	Compiler* obj = new Compiler(essl);

	obj->Wrap(args.This());

	return args.This();
}

//----------------------------------------------------------------------

Handle<Value> Compiler::Dispose(const Arguments& args)
{
	HandleScope scope;

	Compiler* obj = ObjectWrap::Unwrap<Compiler>(args.This());
	obj->release();

	return scope.Close(Undefined());
}
