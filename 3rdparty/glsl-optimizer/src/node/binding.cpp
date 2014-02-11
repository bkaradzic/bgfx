#include <node.h>
#include "shader.h"

using namespace v8;

void InitAll(Handle<Object> exports)
{
	// Export constants
	exports->Set(String::NewSymbol("VERTEX_SHADER"), Int32::New(kGlslOptShaderVertex), ReadOnly);
	exports->Set(String::NewSymbol("FRAGMENT_SHADER"), Int32::New(kGlslOptShaderFragment), ReadOnly);

	// Export classes
	Compiler::Init(exports);
	Shader::Init(exports);
}

NODE_MODULE(glslOptimizer, InitAll);
