/*
 * Copyright 2011-2022 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

/*
 *
 * AUTO GENERATED FROM IDL! DO NOT EDIT! (source : $source)
 *
 * More info about IDL:
 * https://gist.github.com/bkaradzic/05a1c86a6dd57bf86e2d828878e88dc2#bgfx-is-switching-to-idl-to-generate-api
 *
 */

#define BGFX_C99_ENUM_CHECK(_enum, _c99enumcount) \
	BX_STATIC_ASSERT(_enum::Count == _enum::Enum(_c99enumcount) )

BGFX_C99_ENUM_CHECK(bgfx::Fatal,                BGFX_FATAL_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::RendererType,         BGFX_RENDERER_TYPE_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::Attrib,               BGFX_ATTRIB_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::AttribType,           BGFX_ATTRIB_TYPE_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::TextureFormat,        BGFX_TEXTURE_FORMAT_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::UniformType,          BGFX_UNIFORM_TYPE_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::BackbufferRatio,      BGFX_BACKBUFFER_RATIO_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::OcclusionQueryResult, BGFX_OCCLUSION_QUERY_RESULT_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::Topology,             BGFX_TOPOLOGY_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::TopologyConvert,      BGFX_TOPOLOGY_CONVERT_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::RenderFrame,          BGFX_RENDER_FRAME_COUNT);

#undef BGFX_C99_ENUM_CHECK

#define BGFX_C99_STRUCT_SIZE_CHECK(_cppstruct, _c99struct) \
	BX_STATIC_ASSERT(sizeof(_cppstruct) == sizeof(_c99struct) )

BGFX_C99_STRUCT_SIZE_CHECK(bgfx::Memory,                bgfx_memory_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::Transform,             bgfx_transform_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::Stats,                 bgfx_stats_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::VertexLayout,          bgfx_vertex_layout_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::TransientIndexBuffer,  bgfx_transient_index_buffer_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::TransientVertexBuffer, bgfx_transient_vertex_buffer_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::InstanceDataBuffer,    bgfx_instance_data_buffer_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::TextureInfo,           bgfx_texture_info_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::UniformInfo,           bgfx_uniform_info_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::Attachment,            bgfx_attachment_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::Caps::GPU,             bgfx_caps_gpu_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::Caps::Limits,          bgfx_caps_limits_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::Caps,                  bgfx_caps_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::PlatformData,          bgfx_platform_data_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::InternalData,          bgfx_internal_data_t);

#undef BGFX_C99_STRUCT_SIZE_CHECK

$c99

/* user define functions */
BGFX_C_API void bgfx_init_ctor(bgfx_init_t* _init)
{
	BX_PLACEMENT_NEW(_init, bgfx::Init);

}

BGFX_C_API bool bgfx_init(const bgfx_init_t * _init)
{
	bgfx_init_t init =*_init;

	if (init.callback != NULL)
	{
		static bgfx::CallbackC99 s_callback;
		s_callback.m_interface = init.callback;
		init.callback = reinterpret_cast<bgfx_callback_interface_t*>(&s_callback);
	}

	if (init.allocator != NULL)
	{
		static bgfx::AllocatorC99 s_allocator;
		s_allocator.m_interface = init.allocator;
		init.allocator = reinterpret_cast<bgfx_allocator_interface_t*>(&s_allocator);
	}

	union { const bgfx_init_t* c; const bgfx::Init* cpp; } in;
	in.c = &init;

	return bgfx::init(*in.cpp);

}

/**/
BGFX_C_API bgfx_interface_vtbl_t* bgfx_get_interface(uint32_t _version)
{
	if (_version == BGFX_API_VERSION)
	{
		static bgfx_interface_vtbl_t s_bgfx_interface =
		{
			$interface_import
		};

		return &s_bgfx_interface;
	}

	return NULL;
}
