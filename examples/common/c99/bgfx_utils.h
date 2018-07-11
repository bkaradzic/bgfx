#ifndef BGFX_UTILS_C99_H
#define BGFX_UTILS_C99_H
#include <bgfx/c99/bgfx.h>
#include <stdio.h>
#include <string.h>

void freeMem(bgfx_memory_t *block);

bgfx_memory_t *loadMem(const char *_fn);

static bgfx_shader_handle_t loadShader(const char* _name);

bgfx_program_handle_t loadProgram(const char* _vsName, const char* _fsName);

#ifdef BGFX_UTILS_C99_IMPLEMENTATION
#ifndef BGFX_UTILS_C99_IMPLEMENTATION_ONCE
#define BGFX_UTILS_C99_IMPLEMENTATION_ONCE

void freeMem(bgfx_memory_t *block) {
	if(block!=NULL) {
		if(block->data!=NULL) {
			free(block->data);
		}
		free(block);
	}
}

bgfx_memory_t *loadMem(const char *_fn) {
	bgfx_memory_t *block=NULL;
	FILE *file=fopen(_fn,"rb");
	if(file==NULL) {
		printf("Failed to load '%s', exiting...\n",_fn);
		exit(EXIT_FAILURE);
	}
	fseek(file,0,SEEK_END);
	if(ftell(file)==0) {
		printf("'%s' is zero-length, exiting...\n",_fn);
		exit(EXIT_FAILURE);
	}
	block=(bgfx_memory_t*)malloc(sizeof(bgfx_memory_t));
	block->size=ftell(file);
	fseek(file,0,SEEK_SET);
	block->data=(uint8_t*)malloc(block->size);
	if(fread(block->data,1,block->size,file)!=block->size) {
		printf("Failed to read '%s', exiting...\n",_fn);
		exit(EXIT_FAILURE);
	}
	fclose(file);
	return block;
}

bgfx_shader_handle_t loadShader(const char* _name) {
	char filePath[512];

	const char* shaderPath = "???";

	switch (bgfx_get_renderer_type() )
	{
		case BGFX_RENDERER_TYPE_NOOP:
		case BGFX_RENDERER_TYPE_DIRECT3D9:  shaderPath = "shaders/dx9/";   break;
		case BGFX_RENDERER_TYPE_DIRECT3D11:
		case BGFX_RENDERER_TYPE_DIRECT3D12: shaderPath = "shaders/dx11/";  break;
		case BGFX_RENDERER_TYPE_GNM:        shaderPath = "shaders/pssl/";  break;
		case BGFX_RENDERER_TYPE_METAL:      shaderPath = "shaders/metal/"; break;
		case BGFX_RENDERER_TYPE_OPENGL:     shaderPath = "shaders/glsl/";  break;
		case BGFX_RENDERER_TYPE_OPENGLES:   shaderPath = "shaders/essl/";  break;
		case BGFX_RENDERER_TYPE_VULKAN:     shaderPath = "shaders/spirv/"; break;

		case BGFX_RENDERER_TYPE_COUNT:
			printf("You should not be here!\n");
			exit(EXIT_FAILURE);
			break;
	}

	strcpy(filePath, shaderPath);
	strcat(filePath, _name);
	strcat(filePath, ".bin");

	bgfx_memory_t *fileData=loadMem(filePath);
	bgfx_shader_handle_t handle = bgfx_create_shader(fileData);
	bgfx_set_shader_name(handle, filePath, INT32_MAX);

	return handle;
}

bgfx_program_handle_t loadProgram(const char* _vsName, const char* _fsName) {
	bgfx_shader_handle_t vsh = loadShader(_vsName);
	bgfx_shader_handle_t fsh = BGFX_INVALID_HANDLE;
	if (NULL != _fsName)
	{
		fsh = loadShader(_fsName);
	}

	return bgfx_create_program(vsh, fsh, true /* destroy shaders when program is destroyed */);
}
#endif // BGFX_UTILS_C99_IMPLEMENTATION_ONCE
#endif // BGFX_UTILS_C99_IMPLEMENTATION
#endif // BGFX_UTILS_C99_H
