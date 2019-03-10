/*
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

/*
 *
 * AUTO GENERATED! DO NOT EDIT!
 *
 */

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
