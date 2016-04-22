/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "common.h"
#include <bgfx/bgfx.h>
#include <bx/os.h>
#include <bx/string.h>
#include <bx/uint32_t.h>
#include <dirent.h>
#include <entry/entry.h>
#include <entry/input.h>
#include <entry/cmd.h>
#include <bgfx_utils.h>

#include "vs_texture.bin.h"
#include "fs_texture.bin.h"
#include "vs_texture_cube.bin.h"
#include "fs_texture_cube.bin.h"

#include <bx/crtimpl.h>

struct Binding
{
	enum Enum
	{
		App,
		Dir,
		View,

		Count
	};
};

static const InputBinding s_bindingApp[] =
{
	{ entry::Key::Esc,       entry::Modifier::None,       1, NULL, "exit"           },

	INPUT_BINDING_END
};

static const InputBinding s_bindingDir[] =
{
	{ entry::Key::Up,        entry::Modifier::None,       1, NULL, "dir up"         },
	{ entry::Key::Down,      entry::Modifier::None,       1, NULL, "dir down"       },
	{ entry::Key::PageUp,    entry::Modifier::None,       1, NULL, "dir up"         },
	{ entry::Key::PageDown,  entry::Modifier::None,       1, NULL, "dir down"       },
	{ entry::Key::Left,      entry::Modifier::None,       1, NULL, "dir back"       },
	{ entry::Key::Backspace, entry::Modifier::None,       1, NULL, "dir back"       },
	{ entry::Key::Right,     entry::Modifier::None,       1, NULL, "dir enter"      },
	{ entry::Key::Return,    entry::Modifier::None,       1, NULL, "dir enter"      },

	INPUT_BINDING_END
};

static const InputBinding s_bindingView[] =
{
	{ entry::Key::Comma,     entry::Modifier::None,       1, NULL, "view mip prev"  },
	{ entry::Key::Period,    entry::Modifier::None,       1, NULL, "view mip next"  },
	{ entry::Key::Comma,     entry::Modifier::LeftShift,  1, NULL, "view mip"       },
	{ entry::Key::Comma,     entry::Modifier::RightShift, 1, NULL, "view mip"       },

	{ entry::Key::Slash,     entry::Modifier::None,       1, NULL, "view filter"    },

	{ entry::Key::Key0,      entry::Modifier::None,       1, NULL, "view zoom 1.0"  },
	{ entry::Key::Plus,      entry::Modifier::None,       1, NULL, "view zoom +0.1" },
	{ entry::Key::Minus,     entry::Modifier::None,       1, NULL, "view zoom -0.1" },

	INPUT_BINDING_END
};

static const char* s_bindingName[] =
{
	"App",
	"Dir",
	"View",
};
BX_STATIC_ASSERT(Binding::Count == BX_COUNTOF(s_bindingName) );

static const InputBinding* s_binding[] =
{
	s_bindingApp,
	s_bindingDir,
	s_bindingView,
};
BX_STATIC_ASSERT(Binding::Count == BX_COUNTOF(s_binding) );

struct View
{
	View()
		: m_scaleFn(0)
		, m_mip(0)
		, m_zoom(1.0f)
		, m_filter(true)
	{
	}

	~View()
	{
	}
	int32_t cmd(int32_t _argc, char const* const* _argv)
	{
		if (_argc >= 2)
		{
			if (0 == strcmp(_argv[1], "mip") )
			{
				if (_argc >= 3)
				{
					uint32_t mip = m_mip;
					if (0 == strcmp(_argv[2], "next") )
					{
						++mip;
					}
					else if (0 == strcmp(_argv[2], "prev") )
					{
						--mip;
					}
					else if (0 == strcmp(_argv[2], "last") )
					{
						mip = INT32_MAX;
					}
					else
					{
						mip = atoi(_argv[2]);
					}

					m_mip = bx::uint32_iclamp(mip, 0, m_info.numMips-1);
				}
				else
				{
					m_mip = 0;
				}
			}
			else if (0 == strcmp(_argv[1], "zoom") )
			{
				if (_argc >= 3)
				{
					float zoom = (float)atof(_argv[2]);

					if (_argv[2][0] == '+'
					||  _argv[2][0] == '-')
					{
						m_zoom += zoom;
					}
					else
					{
						m_zoom = zoom;
					}

					m_zoom = bx::fclamp(m_zoom, 0.001f, 10.0f);
				}
				else
				{
					m_zoom = 1.0f;
				}
			}
			else if (0 == strcmp(_argv[1], "filter") )
			{
				if (_argc >= 3)
				{
					m_filter = bx::toBool(_argv[2]);
				}
				else
				{
					m_filter ^= true;
				}
			}
		}

		return 0;
	}

	bgfx::TextureInfo m_info;
	uint32_t m_scaleFn;
	uint32_t m_mip;
	float    m_zoom;
	bool     m_filter;
};

int cmdView(CmdContext* /*_context*/, void* _userData, int _argc, char const* const* _argv)
{
	View* view = static_cast<View*>(_userData);
	return view->cmd(_argc, _argv);
}

struct PosUvColorVertex
{
	float m_x;
	float m_y;
	float m_u;
	float m_v;
	uint32_t m_abgr;

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position,  2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0,    4, bgfx::AttribType::Uint8, true)
			.end();
	}

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosUvColorVertex::ms_decl;

bool screenQuad(int32_t _x, int32_t _y, int32_t _width, uint32_t _height, bool _originBottomLeft = false)
{
	if (bgfx::checkAvailTransientVertexBuffer(6, PosUvColorVertex::ms_decl) )
	{
		bgfx::TransientVertexBuffer vb;
		bgfx::allocTransientVertexBuffer(&vb, 6, PosUvColorVertex::ms_decl);
		PosUvColorVertex* vertex = (PosUvColorVertex*)vb.data;

		const float widthf  = float(_width);
		const float heightf = float(_height);

		const float minx = float(_x);
		const float miny = float(_y);
		const float maxx = minx+widthf;
		const float maxy = miny+heightf;

		float m_halfTexel = 0.0f;

		const float texelHalfW = m_halfTexel/widthf;
		const float texelHalfH = m_halfTexel/heightf;
		const float minu = texelHalfW;
		const float maxu = 1.0f - texelHalfW;
		const float minv = _originBottomLeft ? texelHalfH+1.0f : texelHalfH     ;
		const float maxv = _originBottomLeft ? texelHalfH      : texelHalfH+1.0f;

		vertex[0].m_x = minx;
		vertex[0].m_y = miny;
		vertex[0].m_u = minu;
		vertex[0].m_v = minv;

		vertex[1].m_x = maxx;
		vertex[1].m_y = miny;
		vertex[1].m_u = maxu;
		vertex[1].m_v = minv;

		vertex[2].m_x = maxx;
		vertex[2].m_y = maxy;
		vertex[2].m_u = maxu;
		vertex[2].m_v = maxv;

		vertex[3].m_x = maxx;
		vertex[3].m_y = maxy;
		vertex[3].m_u = maxu;
		vertex[3].m_v = maxv;

		vertex[4].m_x = minx;
		vertex[4].m_y = maxy;
		vertex[4].m_u = minu;
		vertex[4].m_v = maxv;

		vertex[5].m_x = minx;
		vertex[5].m_y = miny;
		vertex[5].m_u = minu;
		vertex[5].m_v = minv;

		vertex[0].m_abgr = UINT32_MAX;
		vertex[1].m_abgr = UINT32_MAX;
		vertex[2].m_abgr = UINT32_MAX;
		vertex[3].m_abgr = UINT32_MAX;
		vertex[4].m_abgr = UINT32_MAX;
		vertex[5].m_abgr = UINT32_MAX;

		bgfx::setVertexBuffer(&vb);

		return true;
	}

	return false;
}

struct Interpolator
{
	float from;
	float to;
	float duration;
	int64_t offset;

	Interpolator(float _value)
	{
		reset(_value);
	}

	void reset(float _value)
	{
		from     = _value;
		to       = _value;
		duration = 0.0;
		offset   = bx::getHPCounter();
	}

	void set(float _value, float _duration)
	{
		if (_value != to)
		{
			from     = getValue();
			to       = _value;
			duration = _duration;
			offset   = bx::getHPCounter();
		}
	}

	float getValue()
	{

		if (duration > 0.0)
		{
			const double freq = double(bx::getHPFrequency() );
			int64_t now = bx::getHPCounter();
			float time = (float)(double(now - offset) / freq);
			float lerp = bx::fclamp(time, 0.0, duration) / duration;
			return bx::flerp(from, to, lerp);
		}

		return to;
	}
};

void help(const char* _error = NULL)
{
	if (NULL != _error)
	{
		fprintf(stderr, "Error:\n%s\n\n", _error);
	}

	fprintf(stderr
		, "texturev, bgfx texture viewer tool\n"
		  "Copyright 2011-2016 Branimir Karadzic. All rights reserved.\n"
		  "License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause\n\n"
		);

	fprintf(stderr
		, "Usage: texturev <file path>\n"
		  "\n"
		  "For additional information, see https://github.com/bkaradzic/bgfx\n"
		);
}

int _main_(int _argc, char** _argv)
{
	if (2 > _argc)
	{
		help("File path is not specified.");
		return EXIT_FAILURE;
	}

	uint32_t width  = 1280;
	uint32_t height = 720;
	uint32_t debug  = BGFX_DEBUG_TEXT;
	uint32_t reset  = BGFX_RESET_VSYNC;

	inputAddBindings(s_bindingName[Binding::App],  s_binding[Binding::App]);
	inputAddBindings(s_bindingName[Binding::Dir],  s_binding[Binding::Dir]);
	inputAddBindings(s_bindingName[Binding::View], s_binding[Binding::View]);

	View view;
	cmdAdd("view", cmdView, &view);

	bgfx::init();
	bgfx::reset(width, height, reset);

	// Set view 0 clear state.
	bgfx::setViewClear(0
		, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
		, 0x101010ff
		, 1.0f
		, 0
		);

	PosUvColorVertex::init();

	const bgfx::Memory* vs_texture;
	const bgfx::Memory* fs_texture;
	const bgfx::Memory* vs_texture_cube;
	const bgfx::Memory* fs_texture_cube;

	switch (bgfx::getRendererType())
	{
	case bgfx::RendererType::Direct3D9:
		vs_texture      = bgfx::makeRef(vs_texture_dx9,      sizeof(vs_texture_dx9) );
		fs_texture      = bgfx::makeRef(fs_texture_dx9,      sizeof(fs_texture_dx9) );
		vs_texture_cube = bgfx::makeRef(vs_texture_cube_dx9, sizeof(vs_texture_cube_dx9) );
		fs_texture_cube = bgfx::makeRef(fs_texture_cube_dx9, sizeof(fs_texture_cube_dx9) );
		break;

	case bgfx::RendererType::Direct3D11:
	case bgfx::RendererType::Direct3D12:
		vs_texture      = bgfx::makeRef(vs_texture_dx11,      sizeof(vs_texture_dx11) );
		fs_texture      = bgfx::makeRef(fs_texture_dx11,      sizeof(fs_texture_dx11) );
		vs_texture_cube = bgfx::makeRef(vs_texture_cube_dx11, sizeof(vs_texture_cube_dx11) );
		fs_texture_cube = bgfx::makeRef(fs_texture_cube_dx11, sizeof(fs_texture_cube_dx11) );
		break;

	default:
		vs_texture      = bgfx::makeRef(vs_texture_glsl,      sizeof(vs_texture_glsl) );
		fs_texture      = bgfx::makeRef(fs_texture_glsl,      sizeof(fs_texture_glsl) );
		vs_texture_cube = bgfx::makeRef(vs_texture_cube_glsl, sizeof(vs_texture_cube_glsl) );
		fs_texture_cube = bgfx::makeRef(fs_texture_cube_glsl, sizeof(fs_texture_cube_glsl) );
		break;
	}

	bgfx::ProgramHandle textureProgram = bgfx::createProgram(
			  bgfx::createShader(vs_texture)
			, bgfx::createShader(fs_texture)
			, true
			);

	bgfx::ProgramHandle textureCubeProgram = bgfx::createProgram(
			  bgfx::createShader(vs_texture_cube)
			, bgfx::createShader(fs_texture_cube)
			, true
			);

	bgfx::UniformHandle s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Int1);
	bgfx::UniformHandle u_mtx      = bgfx::createUniform("u_mtx",      bgfx::UniformType::Mat4);
	bgfx::UniformHandle u_params   = bgfx::createUniform("u_params",   bgfx::UniformType::Vec4);

	bgfx::TextureHandle texture = BGFX_INVALID_HANDLE;
	float speed = 0.37f;
	float time  = 0.0f;

	Interpolator mip(0.0);
	Interpolator zoom(1.0);
	Interpolator scale(1.0);

	texture = loadTexture(_argv[1]
			, 0
			| BGFX_TEXTURE_U_CLAMP
			| BGFX_TEXTURE_V_CLAMP
			| BGFX_TEXTURE_W_CLAMP
			, 0
			, &view.m_info
			);

	int exitcode = EXIT_SUCCESS;

	if (!bgfx::isValid(texture) )
	{
		fprintf(stderr, "Unable to load '%s' texture.\n", _argv[1]);
		exitcode = EXIT_FAILURE;
	}
	else
	{
		entry::MouseState mouseState;
		while (!entry::processEvents(width, height, debug, reset, &mouseState) )
		{
			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency() );

			time += (float)(frameTime*speed/freq);

			float ortho[16];
			bx::mtxOrtho(ortho, 0.0f, (float)width, (float)height, 0.0f, 0.0f, 1000.0f);
			bgfx::setViewTransform(0, NULL, ortho);
			bgfx::setViewRect(0, 0, 0, width, height);
			bgfx::touch(0);

			bgfx::dbgTextClear();

			scale.set(bx::fmin( float(width)  / float(view.m_info.width)
						, float(height) / float(view.m_info.height)
						)
					, 0.1f
					);
			zoom.set(view.m_zoom, 0.25);

			float ss = scale.getValue() * zoom.getValue();

			screenQuad( int(width  - view.m_info.width  * ss)/2
					, int(height - view.m_info.height * ss)/2
					, int(view.m_info.width  * ss)
					, int(view.m_info.height * ss)
					);

			float mtx[16];
			bx::mtxRotateXY(mtx, 0.0f, time);
			bgfx::setUniform(u_mtx, mtx);

			mip.set( float(view.m_mip), 0.5f);

			float params[4] = { mip.getValue(), 0.0f, 0.0f, 0.0f };
			bgfx::setUniform(u_params, params);

			bgfx::setTexture(0
					, s_texColor
					, texture
					, view.m_filter
					? BGFX_TEXTURE_NONE
					: 0
					| BGFX_TEXTURE_MIN_POINT
					| BGFX_TEXTURE_MIP_POINT
					| BGFX_TEXTURE_MAG_POINT
					);
			bgfx::setState(0
					| BGFX_STATE_RGB_WRITE
					| BGFX_STATE_ALPHA_WRITE
					);
			bgfx::submit(0, view.m_info.cubeMap ? textureCubeProgram : textureProgram);

			bgfx::frame();
		}
	}

	if (bgfx::isValid(texture) )
	{
		bgfx::destroyTexture(texture);
	}
	bgfx::destroyUniform(s_texColor);
	bgfx::destroyUniform(u_mtx);
	bgfx::destroyUniform(u_params);
	bgfx::destroyProgram(textureProgram);
	bgfx::destroyProgram(textureCubeProgram);

	bgfx::shutdown();

	return exitcode;
}
