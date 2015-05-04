#include "compiler.h"

using namespace v8;
using namespace node;


Persistent<Function> Compiler::constructor;

//----------------------------------------------------------------------

Compiler::Compiler(glslopt_target target)
{
	_binding = glslopt_initialize(target);
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
	NanScope();

	// Prepare constructor template
	Local<FunctionTemplate> tpl = NanNew<FunctionTemplate>(New);
	
	tpl->SetClassName(NanNew<String>("Compiler"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	NanSetPrototypeTemplate(tpl, "dispose", NanNew<FunctionTemplate>(Dispose));

	// Export the class
	NanAssignPersistent<Function>(constructor, tpl->GetFunction());
	exports->Set(NanNew<String>("Compiler"), tpl->GetFunction());
}

//----------------------------------------------------------------------

NAN_METHOD(Compiler::New)
{
	NanScope();

	if (args.IsConstructCall()) {
		glslopt_target target = kGlslTargetOpenGL;
		if (args[0]->IsInt32()) 
			target = (glslopt_target)args[0]->Int32Value();
		else if (args[0]->IsBoolean())
			target = (glslopt_target)( (int)args[0]->BooleanValue() );

		Compiler* obj = new Compiler(target);
		obj->Wrap(args.This());
		NanReturnValue(args.This());
	} else {
		Local<Function> cons = NanNew<Function>(constructor);
		NanReturnValue(cons->NewInstance());
	}
}

//----------------------------------------------------------------------

NAN_METHOD(Compiler::Dispose)
{
	NanScope();

	Compiler* obj = ObjectWrap::Unwrap<Compiler>(args.This());
	obj->release();

	NanReturnUndefined();
}
