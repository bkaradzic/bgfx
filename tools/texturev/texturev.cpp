/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"

#include <bgfx/bgfx.h>

#include <bx/commandline.h>
#include <bx/easing.h>
#include <bx/file.h>
#include <bx/filepath.h>
#include <bx/math.h>
#include <bx/os.h>
#include <bx/process.h>
#include <bx/settings.h>
#include <bx/uint32_t.h>

#include <entry/entry.h>
#include <entry/input.h>
#include <entry/cmd.h>
#include <entry/dialog.h>
#include <imgui/imgui.h>
#include <bgfx_utils.h>

#include <tinystl/allocator.h>
#include <tinystl/vector.h>
namespace stl = tinystl;
#include <string>
#include <algorithm>

#include <bimg/decode.h>

#include <bgfx/embedded_shader.h>

#include "vs_texture.bin.h"
#include "vs_texture_cube.bin.h"

#include "fs_texture.bin.h"
#include "fs_texture_array.bin.h"
#include "fs_texture_cube.bin.h"
#include "fs_texture_cube2.bin.h"
#include "fs_texture_sdf.bin.h"
#include "fs_texture_msdf.bin.h"
#include "fs_texture_3d.bin.h"

#define BACKGROUND_VIEW_ID 0
#define IMAGE_VIEW_ID      1

#define BGFX_TEXTUREV_VERSION_MAJOR 1
#define BGFX_TEXTUREV_VERSION_MINOR 1

const float kEvMin = -10.0f;
const float kEvMax =  20.0f;

static const bgfx::EmbeddedShader s_embeddedShaders[] =
{
	BGFX_EMBEDDED_SHADER(vs_texture),
	BGFX_EMBEDDED_SHADER(fs_texture),
	BGFX_EMBEDDED_SHADER(fs_texture_array),
	BGFX_EMBEDDED_SHADER(vs_texture_cube),
	BGFX_EMBEDDED_SHADER(fs_texture_cube),
	BGFX_EMBEDDED_SHADER(fs_texture_cube2),
	BGFX_EMBEDDED_SHADER(fs_texture_sdf),
	BGFX_EMBEDDED_SHADER(fs_texture_msdf),
	BGFX_EMBEDDED_SHADER(fs_texture_3d),

	BGFX_EMBEDDED_SHADER_END()
};

static const char* s_supportedExt[] =
{
	"bmp",
	"dds",
	"exr",
	"gif",
	"gnf",
	"jpg",
	"jpeg",
	"hdr",
	"ktx",
	"pgm",
	"png",
	"ppm",
	"psd",
	"pvr",
	"tga",
};

struct Binding
{
	enum Enum
	{
		App,
		View,
		Help,
		About,

		Count
	};
};

struct Geometry
{
	enum Enum
	{
		Quad,
		Cross,
		Hexagon,

		Count
	};
};

struct Output
{
	enum Enum
	{
		sRGB,
		scRGB,
		HDR10,

		Count
	};
};

static const InputBinding s_bindingApp[] =
{
	{ entry::Key::KeyQ, entry::Modifier::None,  1, NULL, "exit"                },
	{ entry::Key::KeyF, entry::Modifier::None,  1, NULL, "graphics fullscreen" },

	INPUT_BINDING_END
};

const char* s_resetCmd =
	"view zoom 1.0\n"
	"view rotate 0\n"
	"view cubemap\n"
	"view pan\n"
	"view ev\n"
	;

static const InputBinding s_bindingView[] =
{
	{ entry::Key::Esc,       entry::Modifier::None,       1, NULL, "exit"                    },

	{ entry::Key::Comma,     entry::Modifier::None,       1, NULL, "view mip prev"           },
	{ entry::Key::Period,    entry::Modifier::None,       1, NULL, "view mip next"           },
	{ entry::Key::Comma,     entry::Modifier::LeftShift,  1, NULL, "view mip"                },
	{ entry::Key::Comma,     entry::Modifier::RightShift, 1, NULL, "view mip"                },

	{ entry::Key::Slash,     entry::Modifier::None,       1, NULL, "view filter"             },

	{ entry::Key::Key1,      entry::Modifier::None,       1, NULL, "view zoom 1.0\n"
	                                                               "view fit\n"              },

	{ entry::Key::Key0,      entry::Modifier::None,       1, NULL, s_resetCmd                },
	{ entry::Key::Plus,      entry::Modifier::None,       1, NULL, "view zoom +0.1"          },
	{ entry::Key::Minus,     entry::Modifier::None,       1, NULL, "view zoom -0.1"          },

	{ entry::Key::KeyZ,      entry::Modifier::None,       1, NULL, "view rotate -90"         },
	{ entry::Key::KeyZ,      entry::Modifier::LeftShift,  1, NULL, "view rotate +90"         },

	{ entry::Key::Up,        entry::Modifier::None,       1, NULL, "view pan\n"
	                                                               "view file-up"            },
	{ entry::Key::Down,      entry::Modifier::None,       1, NULL, "view pan\n"
	                                                               "view file-down"          },
	{ entry::Key::PageUp,    entry::Modifier::None,       1, NULL, "view pan\n"
	                                                               "view file-pgup"          },
	{ entry::Key::PageDown,  entry::Modifier::None,       1, NULL, "view pan\n"
	                                                               "view file-pgdown"        },

	{ entry::Key::Left,      entry::Modifier::None,       1, NULL, "view layer prev"         },
	{ entry::Key::Right,     entry::Modifier::None,       1, NULL, "view layer next"         },

	{ entry::Key::KeyR,      entry::Modifier::None,       1, NULL, "view rgb r"              },
	{ entry::Key::KeyG,      entry::Modifier::None,       1, NULL, "view rgb g"              },
	{ entry::Key::KeyB,      entry::Modifier::None,       1, NULL, "view rgb b"              },
	{ entry::Key::KeyA,      entry::Modifier::None,       1, NULL, "view rgb a"              },

	{ entry::Key::KeyI,      entry::Modifier::None,       1, NULL, "view info"               },

	{ entry::Key::KeyH,      entry::Modifier::None,       1, NULL, "view help"               },

	{ entry::Key::Return,    entry::Modifier::None,       1, NULL, "view files"              },

	{ entry::Key::KeyS,      entry::Modifier::None,       1, NULL, "view sdf"                },

	{ entry::Key::Space,     entry::Modifier::None,       1, NULL, "view geo\n"
	                                                               "view pan\n"              },

	INPUT_BINDING_END
};

static const InputBinding s_bindingHelp[] =
{
	{ entry::Key::Esc,  entry::Modifier::None,  1, NULL, "view help" },
	{ entry::Key::KeyH, entry::Modifier::None,  1, NULL, "view help" },
	INPUT_BINDING_END
};

static const InputBinding s_bindingAbout[] =
{
	{ entry::Key::Esc,  entry::Modifier::None,  1, NULL, "view about" },
	INPUT_BINDING_END
};

static const char* s_bindingName[] =
{
	"App",
	"View",
	"Help",
	"About",
};
BX_STATIC_ASSERT(Binding::Count == BX_COUNTOF(s_bindingName) );

static const InputBinding* s_binding[] =
{
	s_bindingApp,
	s_bindingView,
	s_bindingHelp,
	s_bindingAbout,
};
BX_STATIC_ASSERT(Binding::Count == BX_COUNTOF(s_binding) );

static const char* s_filter = ""
	"All Image Formats (bmp, dds, exr, gif, gnf, jpg, jpeg, hdr, ktx, pgm, png, ppm, psd, pvr, tga) | *.bmp *.dds *.exr *.gif *.gnf *.jpg *.jpeg *.hdr *.ktx *.pgm *.png *.ppm *.psd *.pvr *.tga\n"
	"Windows Bitmap (bmp) | *.bmp\n"
	"Direct Draw Surface (dds) | *.dds\n"
	"OpenEXR (exr) | *.exr\n"
	"Graphics Interchange Format (gif) | *.gif\n"
	"JPEG Interchange Format (jpg, jpeg) | *.jpg *.jpeg\n"
	"Radiance RGBE (hdr) | *.hdr\n"
	"Khronos Texture (ktx) | *.ktx\n"
	"Portable Graymap/Pixmap Format (pgm, ppm) | *.pgm *.ppm\n"
	"Portable Network Graphics (png) | *.png\n"
	"Photoshop Document (psd) | *.psd\n"
	"PowerVR (pvr) | *.pvr\n"
	"Truevision TGA (tga) | *.tga\n"
	;

#if BX_PLATFORM_WINDOWS

extern "C" void*    __stdcall GetModuleHandleA(const char* _moduleName);
extern "C" uint32_t __stdcall GetModuleFileNameA(void* _module, char* _outFilePath, uint32_t _size);

#endif // BX_PLATFORM_WINDOWS

struct RendererTypeRemap
{
	bx::StringView           name;
	bgfx::RendererType::Enum type;
};

static RendererTypeRemap s_rendererTypeRemap[] =
{
	{ "gl",    bgfx::RendererType::OpenGL     },
	{ "d3d11", bgfx::RendererType::Direct3D11 },
	{ "d3d11", bgfx::RendererType::Direct3D12 },
	{ "vk",    bgfx::RendererType::Vulkan     },
	{ "mtl",   bgfx::RendererType::Metal      },
};

struct View
{
	View()
		: m_rendererType(bgfx::RendererType::Count)
		, m_cubeMapGeo(Geometry::Quad)
		, m_outputFormat(Output::sRGB)
		, m_fileIndex(0)
		, m_scaleFn(0)
		, m_mip(0)
		, m_layer(0)
		, m_abgr(UINT32_MAX)
		, m_ev(0.0f)
		, m_evMin(kEvMin)
		, m_evMax(kEvMax)
		, m_posx(0.0f)
		, m_posy(0.0f)
		, m_angx(0.0f)
		, m_angy(0.0f)
		, m_zoom(1.0f)
		, m_angle(0.0f)
		, m_orientation(0.0f)
		, m_flipH(0.0f)
		, m_flipV(0.0f)
		, m_transitionTime(1.0f)
		, m_width(1280)
		, m_height(720)
		, m_filter(true)
		, m_fit(true)
		, m_alpha(false)
		, m_help(false)
		, m_about(false)
		, m_info(false)
		, m_files(false)
		, m_sdf(false)
		, m_inLinear(false)
	{
		load();

		m_textureInfo.format = bgfx::TextureFormat::Count;
	}

	~View()
	{
	}
	int32_t cmd(int32_t _argc, char const* const* _argv)
	{
		if (_argc >= 2)
		{
			if (0 == bx::strCmp(_argv[1], "mip") )
			{
				if (_argc >= 3)
				{
					uint32_t mip = m_mip;
					if (0 == bx::strCmp(_argv[2], "next") )
					{
						++mip;
					}
					else if (0 == bx::strCmp(_argv[2], "prev") )
					{
						--mip;
					}
					else if (0 == bx::strCmp(_argv[2], "last") )
					{
						mip = INT32_MAX;
					}
					else
					{
						bx::fromString(&mip, _argv[2]);
					}

					m_mip = bx::uint32_iclamp(mip, 0, m_textureInfo.numMips-1);
				}
				else
				{
					m_mip = 0;
				}
			}
			else if (0 == bx::strCmp(_argv[1], "layer") )
			{
				if (_argc >= 3)
				{
					uint32_t layer = m_layer;
					if (0 == bx::strCmp(_argv[2], "next") )
					{
						++layer;
					}
					else if (0 == bx::strCmp(_argv[2], "prev") )
					{
						--layer;
					}
					else if (0 == bx::strCmp(_argv[2], "last") )
					{
						layer = INT32_MAX;
					}
					else
					{
						bx::fromString(&layer, _argv[2]);
					}

					m_layer = bx::uint32_iclamp(layer, 0, m_textureInfo.numLayers-1);
				}
				else
				{
					m_layer = 0;
				}
			}
			else if (0 == bx::strCmp(_argv[1], "ev") )
			{
				if (_argc >= 3)
				{
					float ev = m_ev;
					bx::fromString(&ev, _argv[2]);

					m_ev = bx::clamp(ev, kEvMin, kEvMax);
				}
				else
				{
					m_ev = 0.0f;
				}
			}
			else if (0 == bx::strCmp(_argv[1], "pan") )
			{
				if (_argc >= 3)
				{
					if (_argc >= 4)
					{
						float yy;
						bx::fromString(&yy, _argv[3]);
						if (_argv[3][0] == '+'
						||  _argv[3][0] == '-')
						{
							m_posy += yy;
						}
						else
						{
							m_posy = yy;
						}
					}

					float xx;
					bx::fromString(&xx, _argv[2]);
					if (_argv[2][0] == '+'
					||  _argv[2][0] == '-')
					{
						m_posx += xx;
					}
					else
					{
						m_posx = xx;
					}
				}
				else
				{
					m_posx = 0.0f;
					m_posy = 0.0f;
				}
			}
			else if (0 == bx::strCmp(_argv[1], "cubemap") )
			{
				if (_argc >= 3)
				{
					if (_argc >= 4)
					{
						float yy;
						bx::fromString(&yy, _argv[3]);
						if (_argv[3][0] == '+'
						||  _argv[3][0] == '-')
						{
							m_angy += bx::toRad(yy);
						}
						else
						{
							m_angy = bx::toRad(yy);
						}
					}

					float xx;
					bx::fromString(&xx, _argv[2]);
					if (_argv[2][0] == '+'
					||  _argv[2][0] == '-')
					{
						m_angx += bx::toRad(xx);
					}
					else
					{
						m_angx = bx::toRad(xx);
					}
				}
				else
				{
					m_angx = 0.0f;
					m_angy = 0.0f;
				}
			}
			else if (0 == bx::strCmp(_argv[1], "zoom") )
			{
				if (_argc >= 3)
				{
					float zoom;
					bx::fromString(&zoom, _argv[2]);

					if (_argv[2][0] == '+'
					||  _argv[2][0] == '-')
					{
						m_zoom += zoom;
					}
					else
					{
						m_zoom = zoom;
					}

					m_zoom = bx::clamp(m_zoom, 0.01f, 10.0f);
				}
				else
				{
					m_zoom = 1.0f;
				}
			}
			else if (0 == bx::strCmp(_argv[1], "rotate") )
			{
				if (_argc >= 3)
				{
					float angle;
					bx::fromString(&angle, _argv[2]);

					if (_argv[2][0] == '+'
					||  _argv[2][0] == '-')
					{
						m_angle += bx::toRad(angle);
					}
					else
					{
						m_angle = bx::toRad(angle);
					}

					m_angle = bx::wrap(m_angle, bx::kPi*2.0f);
				}
				else
				{
					m_angle = 0.0f;
				}
			}
			else if (0 == bx::strCmp(_argv[1], "orientation") )
			{
				if (_argc >= 3)
				{
					float* dst = NULL;
					char axis = bx::toLower(_argv[2][0]);
					switch (axis)
					{
					case 'x': dst = &m_flipV;       break;
					case 'y': dst = &m_flipH;       break;
					case 'z': dst = &m_orientation; break;
					default:  break;
					}

					if (NULL != dst)
					{
						if (_argc >= 4)
						{
							float angle;
							bx::fromString(&angle, _argv[3]);
							*dst = bx::toRad(angle);
						}
						else
						{
							*dst = 0.0f;
						}
					}
				}
				else
				{
					m_flipH = 0.0f;
					m_flipV = 0.0f;
					m_orientation = 0.0f;
				}
			}
			else if (0 == bx::strCmp(_argv[1], "transition") )
			{
				if (_argc >= 3)
				{
					float time;
					bx::fromString(&time, _argv[2]);
					m_transitionTime = bx::clamp(time, 0.0f, 5.0f);
				}
				else
				{
					m_transitionTime = 1.0f;
				}
			}
			else if (0 == bx::strCmp(_argv[1], "filter") )
			{
				if (_argc >= 3)
				{
					bx::fromString(&m_filter, _argv[2]);
				}
				else
				{
					m_filter ^= true;
				}
			}
			else if (0 == bx::strCmp(_argv[1], "fit") )
			{
				if (_argc >= 3)
				{
					bx::fromString(&m_fit, _argv[2]);
				}
				else
				{
					m_fit ^= true;
				}
			}
			else if (0 == bx::strCmp(_argv[1], "file-up") )
			{
				m_fileIndex = bx::uint32_satsub(m_fileIndex, 1);
			}
			else if (0 == bx::strCmp(_argv[1], "file-down") )
			{
				uint32_t numFiles = bx::uint32_satsub(uint32_t(m_fileList.size() ), 1);
				++m_fileIndex;
				m_fileIndex = bx::uint32_min(m_fileIndex, numFiles);
			}
			else if (0 == bx::strCmp(_argv[1], "rgb") )
			{
				if (_argc >= 3)
				{
					if (_argv[2][0] == 'r')
					{
						m_abgr ^= 0x000000ff;
					}
					else if (_argv[2][0] == 'g')
					{
						m_abgr ^= 0x0000ff00;
					}
					else if (_argv[2][0] == 'b')
					{
						m_abgr ^= 0x00ff0000;
					}
					else if (_argv[2][0] == 'a')
					{
						m_alpha ^= true;
					}
				}
				else
				{
					m_abgr  = UINT32_MAX;
					m_alpha = false;
				}
			}
			else if (0 == bx::strCmp(_argv[1], "sdf") )
			{
				m_sdf ^= true;
			}
			else if (0 == bx::strCmp(_argv[1], "geo") )
			{
				if (_argc >= 3)
				{
					if (bx::toLower(_argv[2][0]) == 'c')
					{
						m_cubeMapGeo = Geometry::Cross;
					}
					else if (bx::toLower(_argv[2][0]) == 'h')
					{
						m_cubeMapGeo = Geometry::Hexagon;
					}
					else
					{
						m_cubeMapGeo = Geometry::Quad;
					}
				}
				else
				{
					m_cubeMapGeo = Geometry::Enum( (m_cubeMapGeo + 1) % Geometry::Count);
				}
			}
			else if (0 == bx::strCmp(_argv[1], "output") )
			{
				Output::Enum outputPrev = m_outputFormat;
				if (_argc >= 3)
				{
					if (0 == bx::strCmp(_argv[2], "srgb") )
					{
						m_outputFormat = Output::sRGB;
					}
					else if (0 == bx::strCmp(_argv[2], "scrgb") )
					{
						m_outputFormat = Output::scRGB;
					}
					else if (0 == bx::strCmp(_argv[2], "hdr10") )
					{
						m_outputFormat = Output::HDR10;
					}
				}
				else
				{
					m_outputFormat = Output::Enum( (m_outputFormat + 1) % Output::Count);
				}

				if (outputPrev != m_outputFormat)
				{
				    bgfx::TextureFormat::Enum format = bgfx::TextureFormat::RGBA8;
					uint32_t formatFlag = 0;
					if (Output::scRGB == m_outputFormat)
					{
						format = bgfx::TextureFormat::RGBA16F;
					}
					else if (Output::HDR10 == m_outputFormat)
					{
						format = bgfx::TextureFormat::RGB10A2;
						formatFlag = BGFX_RESET_HDR10;
					}

					bgfx::reset(m_width, m_height, BGFX_RESET_VSYNC | formatFlag, format);
				}
			}
			else if (0 == bx::strCmp(_argv[1], "help") )
			{
				m_help ^= true;
			}
			else if (0 == bx::strCmp(_argv[1], "about") )
			{
				m_about ^= true;
			}
			else if (0 == bx::strCmp(_argv[1], "save") )
			{
				save();
			}
			else if (0 == bx::strCmp(_argv[1], "info") )
			{
				m_info ^= true;
			}
			else if (0 == bx::strCmp(_argv[1], "files") )
			{
				m_files ^= true;
			}
		}

		return 0;
	}

	static bool sortNameAscending(const std::string& _lhs, const std::string& _rhs)
	{
		return 0 > bx::strCmpV(_lhs.c_str(), _rhs.c_str() );
	}

	void updateFileList(const bx::FilePath& _filePath)
	{
		bx::DirectoryReader dr;

		if (bx::open(&dr, _filePath) )
		{
			m_path = _filePath;
		}
		else if (bx::open(&dr, _filePath.getPath() ) )
		{
			m_path = _filePath.getPath();
		}
		else
		{
			DBG("File path `%s` not found.", _filePath.getCPtr() );
			return;
		}

		bx::Error err;

		m_fileList.clear();

		while (err.isOk() )
		{
			bx::FileInfo fi;
			bx::read(&dr, fi, &err);

			if (err.isOk()
			&&  bx::FileType::File == fi.type)
			{
				bx::StringView ext = fi.filePath.getExt();

				if (!ext.isEmpty() )
				{
					ext.set(ext.getPtr()+1, ext.getTerm() );

					bool supported = false;
					for (uint32_t ii = 0; ii < BX_COUNTOF(s_supportedExt); ++ii)
					{
						const bx::StringView supportedExt(s_supportedExt[ii]);

						if (0 == bx::strCmpI(bx::max(ext.getPtr(), ext.getTerm() - supportedExt.getLength() ), supportedExt) )
						{
							supported = true;
							break;
						}
					}

					if (supported)
					{
						const bx::StringView fileName = fi.filePath.getFileName();
						m_fileList.push_back(std::string(fileName.getPtr(), fileName.getTerm() ) );
					}
				}
			}
		}

		bx::close(&dr);

		std::sort(m_fileList.begin(), m_fileList.end(), sortNameAscending);

		m_fileIndex = 0;
		uint32_t idx = 0;

		const bx::StringView fileName = _filePath.getFileName();

		for (FileList::const_iterator it = m_fileList.begin(); it != m_fileList.end(); ++it, ++idx)
		{
			if (0 == bx::strCmpI(it->c_str(), fileName) )
			{
				// If it is case-insensitive match then might be correct one, but keep
				// searching.
				m_fileIndex = idx;

				if (0 == bx::strCmp(it->c_str(), fileName) )
				{
					// If it is exact match we're done.
					break;
				}
			}
		}
	}

	void load()
	{
		bx::FilePath filePath(bx::Dir::Home);
		filePath.join(".config/bgfx/texturev.ini");

		bx::Settings settings(entry::getAllocator() );

		bx::FileReader reader;
		if (bx::open(&reader, filePath) )
		{
			bx::read(&reader, settings);
			bx::close(&reader);

			if (!bx::fromString(&m_transitionTime, settings.get("view/transition") ) )
			{
				m_transitionTime = 1.0f;
			}

			if (!bx::fromString(&m_width, settings.get("view/width") ) )
			{
				m_width = 1280;
			}

			if (!bx::fromString(&m_height, settings.get("view/height") ) )
			{
				m_height = 720;
			}

			m_rendererType = getType(settings.get("view/renderer") );
		}
	}

	void save()
	{
		bx::FilePath filePath(bx::Dir::Home);
		filePath.join(".config/bgfx/texturev.ini");

		if (bx::makeAll(filePath.getPath() ) )
		{
			bx::Settings settings(entry::getAllocator() );

			char tmp[256];
			bx::toString(tmp, sizeof(tmp), m_transitionTime);
			settings.set("view/transition", tmp);

			bx::toString(tmp, sizeof(tmp), m_width);
			settings.set("view/width", tmp);

			bx::toString(tmp, sizeof(tmp), m_height);
			settings.set("view/height", tmp);

			if (m_rendererType != bgfx::RendererType::Count)
			{
				settings.set("view/renderer", getName(m_rendererType) );
			}

			bx::FileWriter writer;
			if (bx::open(&writer, filePath) )
			{
				bx::write(&writer, settings);
				bx::close(&writer);
			}
		}
	}

	bx::FilePath m_path;

	typedef stl::vector<std::string> FileList;
	FileList m_fileList;

	bgfx::RendererType::Enum m_rendererType;
	bgfx::TextureInfo m_textureInfo;
	Geometry::Enum m_cubeMapGeo;
	Output::Enum m_outputFormat;
	uint32_t m_fileIndex;
	uint32_t m_scaleFn;
	uint32_t m_mip;
	uint32_t m_layer;
	uint32_t m_abgr;
	float    m_ev;
	float    m_evMin;
	float    m_evMax;
	float    m_posx;
	float    m_posy;
	float    m_angx;
	float    m_angy;
	float    m_zoom;
	float    m_angle;
	float    m_orientation;
	float    m_flipH;
	float    m_flipV;
	float    m_transitionTime;
	uint32_t m_width;
	uint32_t m_height;
	bool     m_filter;
	bool     m_fit;
	bool     m_alpha;
	bool     m_help;
	bool     m_about;
	bool     m_info;
	bool     m_files;
	bool     m_sdf;
	bool     m_inLinear;
};

int cmdView(CmdContext* /*_context*/, void* _userData, int _argc, char const* const* _argv)
{
	View* view = static_cast<View*>(_userData);
	return view->cmd(_argc, _argv);
}

struct PosUvwColorVertex
{
	float m_x;
	float m_y;
	float m_u;
	float m_v;
	float m_w;
	uint32_t m_abgr;

	static void init()
	{
		ms_layout
			.begin()
			.add(bgfx::Attrib::Position,  2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0,    4, bgfx::AttribType::Uint8, true)
			.end();
	}

	void set(float _x, float _y, float _u, float _v, float _w, uint32_t _abgr)
	{
		m_x = _x;
		m_y = _y;
		m_u = _u;
		m_v = _v;
		m_w = _w;
		m_abgr = _abgr;
	}

	static bgfx::VertexLayout ms_layout;
};

bgfx::VertexLayout PosUvwColorVertex::ms_layout;

static uint32_t addQuad(uint16_t* _indices, uint16_t _idx0, uint16_t _idx1, uint16_t _idx2, uint16_t _idx3)
{
	_indices[0] = _idx0;
	_indices[1] = _idx3;
	_indices[2] = _idx1;

	_indices[3] = _idx1;
	_indices[4] = _idx3;
	_indices[5] = _idx2;

	return 6;
}

void setGeometry(
	  Geometry::Enum _type
	, int32_t  _x
	, int32_t  _y
	, uint32_t _width
	, uint32_t _height
	, uint32_t _abgr
	, float _maxu = 1.0f
	, float _maxv = 1.0f
	)
{
	if (Geometry::Quad == _type)
	{
		if (6 == bgfx::getAvailTransientVertexBuffer(6, PosUvwColorVertex::ms_layout) )
		{
			bgfx::TransientVertexBuffer vb;
			bgfx::allocTransientVertexBuffer(&vb, 6, PosUvwColorVertex::ms_layout);
			PosUvwColorVertex* vertex = (PosUvwColorVertex*)vb.data;

			const float widthf  = float(_width);
			const float heightf = float(_height);

			const float minx = float(_x);
			const float miny = float(_y);
			const float maxx = minx+widthf;
			const float maxy = miny+heightf;

			const float minu = 0.0f;
			const float maxu = _maxu;
			const float minv = 0.0f;
			const float maxv = _maxv;

			vertex->set(minx, miny, minu, minv, 0.0f, _abgr); ++vertex;
			vertex->set(maxx, miny, maxu, minv, 0.0f, _abgr); ++vertex;
			vertex->set(maxx, maxy, maxu, maxv, 0.0f, _abgr); ++vertex;

			vertex->set(maxx, maxy, maxu, maxv, 0.0f, _abgr); ++vertex;
			vertex->set(minx, maxy, minu, maxv, 0.0f, _abgr); ++vertex;
			vertex->set(minx, miny, minu, minv, 0.0f, _abgr); ++vertex;

			bgfx::setVertexBuffer(0, &vb);
		}
	}
	else
	{
		const uint32_t numVertices = 14;
		const uint32_t numIndices  = 36;
		if (checkAvailTransientBuffers(numVertices, PosUvwColorVertex::ms_layout, numIndices) )
		{
			bgfx::TransientVertexBuffer tvb;
			bgfx::allocTransientVertexBuffer(&tvb, numVertices, PosUvwColorVertex::ms_layout);

			bgfx::TransientIndexBuffer tib;
			bgfx::allocTransientIndexBuffer(&tib, numIndices);

			PosUvwColorVertex* vertex = (PosUvwColorVertex*)tvb.data;
			uint16_t* indices = (uint16_t*)tib.data;

			if (Geometry::Cross == _type)
			{
				const float sx = _width /1.5f;
				const float sy = _height/1.5f;
				const float px = float(_x)-sx/4.0f;
				const float py = float(_y);

				vertex->set(0.0f*sx+px, 0.5f*sy+py, -1.0f,  1.0f, -1.0f, _abgr); ++vertex;
				vertex->set(0.0f*sx+px, 1.0f*sy+py, -1.0f, -1.0f, -1.0f, _abgr); ++vertex;

				vertex->set(0.5f*sx+px, 0.0f*sy+py, -1.0f,  1.0f, -1.0f, _abgr); ++vertex;
				vertex->set(0.5f*sx+px, 0.5f*sy+py, -1.0f,  1.0f,  1.0f, _abgr); ++vertex;
				vertex->set(0.5f*sx+px, 1.0f*sy+py, -1.0f, -1.0f,  1.0f, _abgr); ++vertex;
				vertex->set(0.5f*sx+px, 1.5f*sy+py, -1.0f, -1.0f, -1.0f, _abgr); ++vertex;

				vertex->set(1.0f*sx+px, 0.0f*sy+py,  1.0f,  1.0f, -1.0f, _abgr); ++vertex;
				vertex->set(1.0f*sx+px, 0.5f*sy+py,  1.0f,  1.0f,  1.0f, _abgr); ++vertex;
				vertex->set(1.0f*sx+px, 1.0f*sy+py,  1.0f, -1.0f,  1.0f, _abgr); ++vertex;
				vertex->set(1.0f*sx+px, 1.5f*sy+py,  1.0f, -1.0f, -1.0f, _abgr); ++vertex;

				vertex->set(1.5f*sx+px, 0.5f*sy+py,  1.0f,  1.0f, -1.0f, _abgr); ++vertex;
				vertex->set(1.5f*sx+px, 1.0f*sy+py,  1.0f, -1.0f, -1.0f, _abgr); ++vertex;

				vertex->set(2.0f*sx+px, 0.5f*sy+py, -1.0f,  1.0f, -1.0f, _abgr); ++vertex;
				vertex->set(2.0f*sx+px, 1.0f*sy+py, -1.0f, -1.0f, -1.0f, _abgr); ++vertex;

				indices += addQuad(indices,  0,  3,  4,  1);
				indices += addQuad(indices,  2,  6,  7,  3);
				indices += addQuad(indices,  3,  7,  8,  4);
				indices += addQuad(indices,  4,  8,  9,  5);
				indices += addQuad(indices,  7, 10, 11,  8);
				indices += addQuad(indices, 10, 12, 13, 11);
			}
			else
			{
				const float sx = float(_width);
				const float sy = float(_height);
				const float px = float(_x) - sx/2.0f;
				const float py = float(_y);

				vertex->set(0.0f*sx+px, 0.25f*sy+py, -1.0f,  1.0f, -1.0f, _abgr); ++vertex;
				vertex->set(0.0f*sx+px, 0.75f*sy+py, -1.0f, -1.0f, -1.0f, _abgr); ++vertex;

				vertex->set(0.5f*sx+px, 0.00f*sy+py, -1.0f,  1.0f,  1.0f, _abgr); ++vertex;
				vertex->set(0.5f*sx+px, 0.50f*sy+py, -1.0f, -1.0f,  1.0f, _abgr); ++vertex;
				vertex->set(0.5f*sx+px, 1.00f*sy+py,  1.0f, -1.0f, -1.0f, _abgr); ++vertex;

				vertex->set(1.0f*sx+px, 0.25f*sy+py,  1.0f,  1.0f,  1.0f, _abgr); ++vertex;
				vertex->set(1.0f*sx+px, 0.75f*sy+py,  1.0f, -1.0f,  1.0f, _abgr); ++vertex;

				vertex->set(1.0f*sx+px, 0.25f*sy+py,  1.0f,  1.0f,  1.0f, _abgr); ++vertex;
				vertex->set(1.0f*sx+px, 0.75f*sy+py,  1.0f, -1.0f,  1.0f, _abgr); ++vertex;

				vertex->set(1.5f*sx+px, 0.00f*sy+py, -1.0f,  1.0f,  1.0f, _abgr); ++vertex;
				vertex->set(1.5f*sx+px, 0.50f*sy+py,  1.0f,  1.0f, -1.0f, _abgr); ++vertex;
				vertex->set(1.5f*sx+px, 1.00f*sy+py,  1.0f, -1.0f, -1.0f, _abgr); ++vertex;

				vertex->set(2.0f*sx+px, 0.25f*sy+py, -1.0f,  1.0f, -1.0f, _abgr); ++vertex;
				vertex->set(2.0f*sx+px, 0.75f*sy+py, -1.0f, -1.0f, -1.0f, _abgr); ++vertex;

				indices += addQuad(indices,  0,  2,  3,  1);
				indices += addQuad(indices,  1,  3,  6,  4);
				indices += addQuad(indices,  2,  5,  6,  3);
				indices += addQuad(indices,  7,  9, 12, 10);
				indices += addQuad(indices,  7, 10, 11,  8);
				indices += addQuad(indices, 10, 12, 13, 11);
			}

			bgfx::setVertexBuffer(0, &tvb);
			bgfx::setIndexBuffer(&tib);
		}
	}
}

template<bx::LerpFn lerpT, bx::EaseFn easeT>
struct InterpolatorT
{
	float from;
	float to;
	float duration;
	int64_t offset;

	InterpolatorT(float _value)
	{
		reset(_value);
	}

	void reset(float _value)
	{
		from     = _value;
		to       = _value;
		duration = 0.0f;
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
		if (isActive() )
		{
			const double freq = double(bx::getHPFrequency() );
			int64_t now = bx::getHPCounter();
			float time = (float)(double(now - offset) / freq);
			float lerp = duration != 0.0f ? bx::clamp(time, 0.0f, duration) / duration : 0.0f;
			return lerpT(from, to, easeT(lerp) );
		}

		return to;
	}

	bool isActive() const
	{
		if (0.0f < duration)
		{
			const double freq = double(bx::getHPFrequency() );
			int64_t now = bx::getHPCounter();
			float time = (float)(double(now - offset) / freq);
			float lerp = bx::clamp(time, 0.0f, duration) / duration;
			return lerp < 1.0f;
		}

		return false;
	}
};

typedef InterpolatorT<bx::lerp,      bx::easeInOutQuad>  Interpolator;
typedef InterpolatorT<bx::angleLerp, bx::easeInOutCubic> InterpolatorAngle;
typedef InterpolatorT<bx::lerp,      bx::easeLinear>     InterpolatorLinear;

void keyBindingHelp(const char* _bindings, const char* _description)
{
	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", _bindings);
	ImGui::SameLine(100);
	ImGui::Text("%s", _description);
}

void associate()
{
#if BX_PLATFORM_WINDOWS
	std::string str;

	char exec[bx::kMaxFilePath];
	GetModuleFileNameA(GetModuleHandleA(NULL), exec, sizeof(exec) );

	std::string strExec = bx::replaceAll<std::string>(exec, "\\", "\\\\");

	std::string value;
	bx::stringPrintf(value, "@=\"\\\"%s\\\" \\\"%%1\\\"\"\r\n\r\n", strExec.c_str() );

	str += "Windows Registry Editor Version 5.00\r\n\r\n";

	str += "[HKEY_CLASSES_ROOT\\texturev\\shell\\open\\command]\r\n";
	str += value;

	str += "[HKEY_CLASSES_ROOT\\Applications\\texturev.exe\\shell\\open\\command]\r\n";
	str += value;

	for (uint32_t ii = 0; ii < BX_COUNTOF(s_supportedExt); ++ii)
	{
		const char* ext = s_supportedExt[ii];

		bx::stringPrintf(str, "[-HKEY_CLASSES_ROOT\\.%s]\r\n\r\n", ext);
		bx::stringPrintf(str, "[-HKEY_CURRENT_USER\\Software\\Classes\\.%s]\r\n\r\n", ext);

		bx::stringPrintf(str, "[HKEY_CLASSES_ROOT\\.%s]\r\n@=\"texturev\"\r\n\r\n", ext);
		bx::stringPrintf(str, "[HKEY_CURRENT_USER\\Software\\Classes\\.%s]\r\n@=\"texturev\"\r\n\r\n", ext);
	}

	bx::FilePath filePath(bx::Dir::Temp);
	filePath.join("texture.reg");

	bx::FileWriter writer;
	bx::Error err;
	if (bx::open(&writer, filePath, false, &err) )
	{
		bx::write(&writer, str.c_str(), uint32_t(str.length()), &err);
		bx::close(&writer);

		if (err.isOk() )
		{
			std::string cmd;
			bx::stringPrintf(cmd, "/s %s", filePath.getCPtr() );

			bx::ProcessReader reader;
			if (bx::open(&reader, "regedit.exe", cmd.c_str(), &err) )
			{
				bx::close(&reader);
			}
		}
	}
#elif BX_PLATFORM_LINUX
	std::string str;
	str += "#/bin/bash\n\n";

	for (uint32_t ii = 0; ii < BX_COUNTOF(s_supportedExt); ++ii)
	{
		const char* ext = s_supportedExt[ii];
		bx::stringPrintf(str, "xdg-mime default texturev.desktop image/%s\n", ext);
	}

	bx::stringPrintf(str, "xdg-mime default texturev.desktop image/x-dds\n");

	str += "\n";

	bx::FileWriter writer;
	bx::Error err;
	if (bx::open(&writer, "/tmp/texturev.sh", false, &err) )
	{
		bx::write(&writer, str.c_str(), uint32_t(str.length()), &err);
		bx::close(&writer);

		if (err.isOk() )
		{
			bx::ProcessReader reader;
			if (bx::open(&reader, "/bin/bash", "/tmp/texturev.sh", &err) )
			{
				bx::close(&reader);
			}
		}
	}
#endif // BX_PLATFORM_WINDOWS
}

void help(const char* _error = NULL)
{
	if (NULL != _error)
	{
		bx::printf("Error:\n%s\n\n", _error);
	}

	bx::printf(
		  "texturev, bgfx texture viewer tool, version %d.%d.%d.\n"
		  "Copyright 2011-2021 Branimir Karadzic. All rights reserved.\n"
		  "License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause\n\n"
		, BGFX_TEXTUREV_VERSION_MAJOR
		, BGFX_TEXTUREV_VERSION_MINOR
		, BGFX_API_VERSION
		);

	bx::printf(
		  "Usage: texturev <file path>\n"
		  "\n"
		  "Supported input file types:\n"
		  );

	for (uint32_t ii = 0; ii < BX_COUNTOF(s_supportedExt); ++ii)
	{
		bx::printf("    *.%s\n", s_supportedExt[ii]);
	}

	bx::printf(
		  "\n"
		  "Options:\n"
		  "  -h, --help               Help.\n"
		  "  -v, --version            Version information only.\n"
		  "      --associate          Associate file extensions with texturev.\n"
		  "\n"
		  "For additional information, see https://github.com/bkaradzic/bgfx\n"
		);
}

int _main_(int _argc, char** _argv)
{
	bx::CommandLine cmdLine(_argc, _argv);

	if (cmdLine.hasArg('v', "version") )
	{
		bx::printf(
			  "texturev, bgfx texture viewer tool, version %d.%d.%d.\n"
			, BGFX_TEXTUREV_VERSION_MAJOR
			, BGFX_TEXTUREV_VERSION_MINOR
			, BGFX_API_VERSION
			);
		return bx::kExitSuccess;
	}

	if (cmdLine.hasArg('h', "help") )
	{
		help();
		return bx::kExitFailure;
	}
	else if (cmdLine.hasArg("associate") )
	{
		associate();
		return bx::kExitFailure;
	}

	uint32_t debug = BGFX_DEBUG_TEXT;

	inputAddBindings(s_bindingName[Binding::App],  s_binding[Binding::App]);
	inputAddBindings(s_bindingName[Binding::View], s_binding[Binding::View]);

	View view;
	cmdAdd("view", cmdView, &view);

	entry::setWindowFlags(entry::WindowHandle{0}, ENTRY_WINDOW_FLAG_ASPECT_RATIO, false);
	entry::setWindowSize(entry::WindowHandle{0}, view.m_width, view.m_height);

	bgfx::Init init;
	init.type = view.m_rendererType;
	init.resolution.width  = view.m_width;
	init.resolution.height = view.m_height;
	init.resolution.reset  = BGFX_RESET_VSYNC;

	bgfx::init(init);

	// Set view 0 clear state.
	bgfx::setViewClear(BACKGROUND_VIEW_ID
		, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
		, 0x000000ff
		, 1.0f
		, 0
		);

	imguiCreate();

	PosUvwColorVertex::init();

	const bgfx::Caps* caps = bgfx::getCaps();
	bgfx::RendererType::Enum type = caps->rendererType;

	bgfx::UniformHandle s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);
	bgfx::UniformHandle u_mtx      = bgfx::createUniform("u_mtx",      bgfx::UniformType::Mat4);
	bgfx::UniformHandle u_params0  = bgfx::createUniform("u_params0",  bgfx::UniformType::Vec4);
	bgfx::UniformHandle u_params1  = bgfx::createUniform("u_params1",  bgfx::UniformType::Vec4);

	bgfx::ShaderHandle vsTexture      = bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_texture");
	bgfx::ShaderHandle fsTexture      = bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_texture");
	bgfx::ShaderHandle fsTextureArray = bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_texture_array");

	bgfx::ProgramHandle textureProgram = bgfx::createProgram(
		  vsTexture
		, fsTexture
		, true
		);

	bgfx::ProgramHandle textureArrayProgram = bgfx::createProgram(
		  vsTexture
		, bgfx::isValid(fsTextureArray)
		? fsTextureArray
		: fsTexture
		, true
		);

	bgfx::ProgramHandle textureCubeProgram = bgfx::createProgram(
		  bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_texture_cube")
		, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_texture_cube")
		, true
		);

	bgfx::ProgramHandle textureCube2Program = bgfx::createProgram(
		  vsTexture
		, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_texture_cube2")
		, true
		);

	bgfx::ProgramHandle textureSdfProgram = bgfx::createProgram(
		  vsTexture
		, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_texture_sdf")
		, true
		);

	bgfx::ProgramHandle textureMsdfProgram = bgfx::createProgram(
		  vsTexture
		, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_texture_msdf")
		, true
		);

	bgfx::ProgramHandle texture3DProgram = bgfx::createProgram(
		  vsTexture
		, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_texture_3d")
		, true
		);

	const uint32_t checkerBoardSize = 64;
	bgfx::TextureHandle checkerBoard;
	{
		const bgfx::Memory* mem = bgfx::alloc(checkerBoardSize*checkerBoardSize*4);
		bimg::imageCheckerboard(mem->data, checkerBoardSize, checkerBoardSize, 8, 0xff8e8e8e, 0xff5d5d5d);
		checkerBoard = bgfx::createTexture2D(checkerBoardSize, checkerBoardSize, false, 1
			, bgfx::TextureFormat::BGRA8
			, 0
			| BGFX_SAMPLER_MIN_POINT
			| BGFX_SAMPLER_MIP_POINT
			| BGFX_SAMPLER_MAG_POINT
			, mem
			);
	}

	float speed = 0.37f;
	float time  = 0.0f;

	Interpolator menuFade(5.0f);
	Interpolator mip(0.0f);
	Interpolator layer(0.0f);
	InterpolatorLinear ev(0.0f);
	Interpolator zoom(1.0f);
	Interpolator scale(1.0f);
	Interpolator posx(0.0f);
	Interpolator posy(0.0f);
	InterpolatorAngle angle(0.0f);
	InterpolatorAngle angx(0.0f);
	InterpolatorAngle angy(0.0f);

	auto anyActive = [&]() -> bool
	{
		return false
			|| ImGui::MouseOverArea()
			|| menuFade.isActive()
			|| mip.isActive()
			|| layer.isActive()
			|| ev.isActive()
			|| zoom.isActive()
			|| scale.isActive()
			|| posx.isActive()
			|| posy.isActive()
			|| angle.isActive()
			|| angx.isActive()
			|| angy.isActive()
			;
	};

	const char* filePath = _argc < 2 ? "" : _argv[1];

	std::string path = filePath;
	{
		bx::FilePath fp(filePath);
		view.updateFileList(fp);
	}

	int exitcode = bx::kExitSuccess;
	bgfx::TextureHandle texture = BGFX_INVALID_HANDLE;

	{
		uint32_t fileIndex = 0;
		bool dragging = false;

		entry::WindowState windowState;
		entry::MouseState mouseStatePrev;
		while (!entry::processWindowEvents(windowState, debug, init.resolution.reset) )
		{
			const entry::MouseState& mouseState = windowState.m_mouse;
			view.m_width  = windowState.m_width;
			view.m_height = windowState.m_height;

			if (!windowState.m_dropFile.isEmpty() )
			{
				view.updateFileList(windowState.m_dropFile);
				windowState.m_dropFile.clear();
			}

			imguiBeginFrame(mouseState.m_mx
				,  mouseState.m_my
				, (mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT   : 0)
				| (mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT  : 0)
				| (mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
				,  mouseState.m_mz
				,  uint16_t(view.m_width)
				,  uint16_t(view.m_height)
				);

			bool modalWindow = view.m_help || view.m_about;
			bool overArea = false
				|| ImGui::GetMousePos().y <= ImGui::GetTextLineHeightWithSpacing()
				|| ImGui::MouseOverArea()
				;
			overArea &= !modalWindow;

			if (overArea)
			{
				menuFade.set(5.0f, 0.25f);
			}
			else if (modalWindow)
			{
				menuFade.reset(0.0f);
			}
			else
			{
				menuFade.set(0.0f, 2.0f);
			}

			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, bx::clamp(menuFade.getValue(), 0.0f, 1.0f) );
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);

			if (ImGui::BeginMainMenuBar() )
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("Open File") )
					{
						bx::FilePath tmp = view.m_path;
						if (openFileSelectionDialog(
							  tmp
							, FileSelectionDialogType::Open
							, "texturev: Open File"
							, s_filter
							) )
						{
							view.updateFileList(tmp);
						}
					}

					if (ImGui::MenuItem("Show File List", NULL, view.m_files) )
					{
						cmdExec("view files");
					}

					ImGui::Separator();
					if (ImGui::MenuItem("Exit") )
					{
						cmdExec("exit");
					}

					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("View") )
				{
					if (ImGui::MenuItem("Info", NULL, view.m_info) )
					{
						cmdExec("view info");
					}

					if (ImGui::MenuItem("Reset") )
					{
						cmdExec(s_resetCmd);
					}

					ImGui::Separator();
					bool filter = view.m_filter;
					if (ImGui::MenuItem("Filter", NULL, &filter) )
					{
						cmdExec("view filter");
					}

					bool animate = 0.0f < view.m_transitionTime;
					if (ImGui::MenuItem("Animate", NULL, &animate) )
					{
						cmdExec("view transition %f", animate ? 1.0f : 0.0f);
					}

					if (ImGui::BeginMenu("Cubemap", view.m_textureInfo.cubeMap) )
					{
						if (ImGui::MenuItem("Quad", NULL, Geometry::Quad == view.m_cubeMapGeo) )
						{
							cmdExec("view geo quad");
						}

						if (ImGui::MenuItem("Cross", NULL, Geometry::Cross == view.m_cubeMapGeo) )
						{
							cmdExec("view geo cross");
						}

						if (ImGui::MenuItem("Hexagon", NULL, Geometry::Hexagon == view.m_cubeMapGeo) )
						{
							cmdExec("view geo hexagon");
						}

						ImGui::EndMenu();
					}

					if (ImGui::BeginMenu("Output") )
					{
						const bool hdrCap = (bgfx::getCaps()->supported & BGFX_CAPS_HDR10);

						if (ImGui::MenuItem("sRGB", NULL, Output::sRGB == view.m_outputFormat) )
						{
							cmdExec("view output srgb");
						}

						if (hdrCap)
						{
							if (ImGui::MenuItem("scRGB", NULL, Output::scRGB == view.m_outputFormat) )
							{
								cmdExec("view output scrgb");
							}

							if (ImGui::MenuItem("HDR10", NULL, Output::HDR10 == view.m_outputFormat) )
							{
								cmdExec("view output hdr10");
							}
						}

						ImGui::EndMenu();
					}

					bool sdf = view.m_sdf;
					if (ImGui::MenuItem("SDF", NULL, &sdf) )
					{
						cmdExec("view sdf");
					}

					bool rr = 0 != (view.m_abgr & 0x000000ff);
					if (ImGui::MenuItem("R", NULL, &rr) )
					{
						cmdExec("view rgb r");
					}

					bool gg = 0 != (view.m_abgr & 0x0000ff00);
					if (ImGui::MenuItem("G", NULL, &gg) )
					{
						cmdExec("view rgb g");
					}

					bool bb = 0 != (view.m_abgr & 0x00ff0000);
					if (ImGui::MenuItem("B", NULL, &bb) )
					{
						cmdExec("view rgb b");
					}

					bool alpha = view.m_alpha;
					if (ImGui::MenuItem("Checkerboard", NULL, &alpha) )
					{
						cmdExec("view rgb a");
					}

					ImGui::Separator();

					if (ImGui::MenuItem("Save Options") )
					{
						cmdExec("view save");
					}

					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Help") )
				{
					if (ImGui::MenuItem("View Help") )
					{
						cmdExec("view help");
					}

					ImGui::Separator();
					if (ImGui::MenuItem("About") )
					{
						cmdExec("view about");
					}

					ImGui::EndMenu();
				}

				if (0 != view.m_fileList.size() )
				{
					ImGui::Separator();
					ImGui::TextColored(
						  ImVec4(0.0f, 1.0f, 1.0f, 1.0f)
						, "%s"
						, view.m_fileList[view.m_fileIndex].c_str()
						);

					ImGui::Separator();
					const char* name = "";
					if (view.m_textureInfo.cubeMap)
					{
						name = " CubeMap";
					}
					else if (1 < view.m_textureInfo.depth)
					{
						name = " 3D";
						view.m_textureInfo.numLayers = view.m_textureInfo.depth;
					}
					else if (1 < view.m_textureInfo.numLayers)
					{
						name = " 2D Array";
					}

					ImGui::Text("%d x %d%s, mips: %d, layers %d, %s"
						, view.m_textureInfo.width
						, view.m_textureInfo.height
						, name
						, view.m_textureInfo.numMips
						, view.m_textureInfo.numLayers
						, bimg::getName(bimg::TextureFormat::Enum(view.m_textureInfo.format) )
						);
				}

				ImGui::EndMainMenuBar();
			}

			ImGui::PopStyleVar(2);

			static bool help = false;
			static bool about = false;
			static bool mouseDelta = false;
			if (!mouseDelta)
			{
				mouseStatePrev = mouseState;
				mouseDelta = true;
			}

			int32_t zoomDelta = overArea ? 0 : mouseState.m_mz - mouseStatePrev.m_mz;
			if (zoomDelta != 0)
			{
				char exec[64];
				bx::snprintf(exec, BX_COUNTOF(exec), "view zoom %+f", -zoomDelta*0.1f);
				cmdExec(exec);
			}

			const float xDelta = float(mouseStatePrev.m_mx - mouseState.m_mx);
			const float yDelta = float(mouseStatePrev.m_my - mouseState.m_my);

			if (!overArea
			&&  !help
			&&  mouseState.m_buttons[entry::MouseButton::Left] != mouseStatePrev.m_buttons[entry::MouseButton::Left])
			{
				dragging = !!mouseState.m_buttons[entry::MouseButton::Left];
			}

			if (dragging)
			{
				if (view.m_textureInfo.cubeMap
				&&  Geometry::Quad == view.m_cubeMapGeo)
				{
					char exec[64];
					bx::snprintf(exec, BX_COUNTOF(exec), "view cubemap %+f %+f", -yDelta, -xDelta);
					cmdExec(exec);
				}
				else
				{
					char exec[64];
					bx::snprintf(exec, BX_COUNTOF(exec), "view pan %+f %+f", xDelta, yDelta);
					cmdExec(exec);
				}
			}

			mouseStatePrev = mouseState;

			if (help != view.m_help)
			{
				if (!help)
				{
					ImGui::OpenPopup("Help");
					inputRemoveBindings(s_bindingName[Binding::View]);
					inputAddBindings(s_bindingName[Binding::Help], s_binding[Binding::Help]);
				}
				else
				{
					inputRemoveBindings(s_bindingName[Binding::Help]);
					inputAddBindings(s_bindingName[Binding::View], s_binding[Binding::View]);
				}

				help = view.m_help;
			}

			if (about != view.m_about)
			{
				if (!about)
				{
					ImGui::OpenPopup("About");
					inputRemoveBindings(s_bindingName[Binding::View]);
					inputAddBindings(s_bindingName[Binding::About], s_binding[Binding::About]);
				}
				else
				{
					inputRemoveBindings(s_bindingName[Binding::About]);
					inputAddBindings(s_bindingName[Binding::View], s_binding[Binding::View]);
				}

				about = view.m_about;
			}

			if (view.m_info)
			{
				ImGui::SetNextWindowSize(
					  ImVec2(300.0f, 320.0f)
					, ImGuiCond_FirstUseEver
					);

				if (ImGui::Begin("Info", &view.m_info) )
				{
					if (ImGui::BeginChild("##info", ImVec2(0.0f, 0.0f) ) )
					{
						if (!bgfx::isValid(texture) )
						{
							ImGui::Text("Texture is not loaded.");
						}
						else
						{
							ImGui::Text("Name: %s", view.m_fileList[view.m_fileIndex].c_str() );

							ImGui::Text("Dimensions: %d x %d"
								, view.m_textureInfo.width
								, view.m_textureInfo.height
								);

							ImGui::Text("Format: %s"
								, bimg::getName(bimg::TextureFormat::Enum(view.m_textureInfo.format) )
								);

							uint32_t numLayers = view.m_textureInfo.numLayers;
							if (1 < view.m_textureInfo.depth)
							{
								numLayers = bx::max(1, view.m_textureInfo.depth >> view.m_mip);
							}
							view.m_layer = bx::clamp<int32_t>(view.m_layer, 0, numLayers - 1);
							ImGui::SliderInt("Layer", (int32_t*)&view.m_layer, 0, numLayers - 1);
							ImGui::SliderInt("Mip",   (int32_t*)&view.m_mip,   0, view.m_textureInfo.numMips - 1);

							ImGui::Separator();

							ImGui::Checkbox("Input linear", &view.m_inLinear);
							ImGui::RangeSliderFloat("EV range", &view.m_evMin, &view.m_evMax, kEvMin, kEvMax);
							ImGui::SliderFloat("EV", &view.m_ev, view.m_evMin, view.m_evMax);

							ImGui::Separator();

							ImGui::Checkbox("Fit to window", &view.m_fit);
							ImGui::SliderFloat("Scale", &view.m_zoom, 0.01f, 10.0f);
						}

						ImGui::EndChild();
					}

				}

				ImGui::End();
			}

			if (view.m_files)
			{
				char temp[bx::kMaxFilePath];
				bx::snprintf(temp, BX_COUNTOF(temp), "%s##File", view.m_path.getCPtr() );

				ImGui::SetNextWindowSize(
					  ImVec2(400.0f, 400.0f)
					, ImGuiCond_FirstUseEver
					);

				if (ImGui::Begin(temp, &view.m_files) )
				{
					if (ImGui::BeginChild("##file_list", ImVec2(0.0f, 0.0f) ) )
					{
						ImGui::PushFont(ImGui::Font::Mono);
						const float itemHeight = ImGui::GetTextLineHeightWithSpacing();
						const float listHeight =
							  bx::max(1.0f, bx::floor(ImGui::GetWindowHeight()/itemHeight) )
							* itemHeight
							;

						ImGui::PushItemWidth(-1);
						if (ImGui::BeginListBox("##empty", ImVec2(0.0f, listHeight) ) )
						{
							const int32_t itemCount = int32_t(view.m_fileList.size() );

							int32_t start, end;
							ImGui::CalcListClipping(itemCount, itemHeight, &start, &end);

							const int32_t index = int32_t(view.m_fileIndex);
							if (index <= start)
							{
								ImGui::SetScrollY(ImGui::GetScrollY() - (start-index+1)*itemHeight);
							}
							else if (index >= end)
							{
								ImGui::SetScrollY(ImGui::GetScrollY() + (index-end+1)*itemHeight);
							}

							ImGuiListClipper clipper;
							clipper.Begin(itemCount, itemHeight);

							while (clipper.Step() )
							{
								for (int32_t pos = clipper.DisplayStart; pos < clipper.DisplayEnd; ++pos)
								{
									ImGui::PushID(pos);

									bool isSelected = uint32_t(pos) == view.m_fileIndex;
									if (ImGui::Selectable(view.m_fileList[pos].c_str(), &isSelected) )
									{
										view.m_fileIndex = pos;
									}

									ImGui::PopID();
								}
							}

							clipper.End();

							ImGui::EndListBox();
						}

						ImGui::PopFont();
						ImGui::EndChild();
					}
				}

				ImGui::End();
			}

			if (ImGui::BeginPopupModal("About", &view.m_about, ImGuiWindowFlags_AlwaysAutoResize) )
			{
				ImGui::SetWindowFontScale(1.0f);

				ImGui::Text(
					"texturev, bgfx texture viewer tool " ICON_KI_WRENCH ", version %d.%d.%d.\n"
					"Copyright 2011-2021 Branimir Karadzic. All rights reserved.\n"
					"License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause\n"
					, BGFX_TEXTUREV_VERSION_MAJOR
					, BGFX_TEXTUREV_VERSION_MINOR
					, BGFX_API_VERSION
					);

				ImGui::Dummy(ImVec2(0.0f, 0.0f) );
				ImGui::SameLine(ImGui::GetWindowWidth() - 136.0f);
				if (ImGui::Button("Close", ImVec2(128.0f, 0.0f) )
				|| !view.m_about)
				{
					view.m_about = false;
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}

			if (ImGui::BeginPopupModal("Help", &view.m_help, ImGuiWindowFlags_AlwaysAutoResize) )
			{
				ImGui::SetWindowFontScale(1.0f);

				ImGui::Text("Key bindings:\n\n");

				ImGui::PushFont(ImGui::Font::Mono);
				keyBindingHelp("ESC", "Exit.");
				keyBindingHelp("h", "Toggle help screen.");
				keyBindingHelp("f", "Toggle full-screen.");
				ImGui::NextLine();

				keyBindingHelp("LMB+drag",  "Pan.");
				keyBindingHelp("=/- or MW", "Zoom in/out.");
				keyBindingHelp("z/Z",       "Rotate.");
				keyBindingHelp("0",         "Reset.");
				keyBindingHelp("1",         "Fit to window.");
				ImGui::NextLine();

				keyBindingHelp("<",       "Reset MIP level.");
				keyBindingHelp(",/,",     "MIP level up/down.");
				keyBindingHelp("/",       "Toggle linear/point texture sampling.");
				keyBindingHelp("[space]", "Change cubemap mode.");
				ImGui::NextLine();

				keyBindingHelp("left",  "Previous layer in texture array.");
				keyBindingHelp("right", "Next layer in texture array.");
				ImGui::NextLine();

				keyBindingHelp("up",   "Previous texture.");
				keyBindingHelp("down", "Next texture.");
				ImGui::NextLine();

				keyBindingHelp("r/g/b", "Toggle R, G, or B color channel.");
				keyBindingHelp("a",     "Toggle alpha blending.");
				ImGui::NextLine();

				keyBindingHelp("s", "Toggle Multi-channel SDF rendering");
				ImGui::NextLine();

				ImGui::PopFont();

				ImGui::Dummy(ImVec2(0.0f, 0.0f) );
				ImGui::SameLine(ImGui::GetWindowWidth() - 136.0f);
				if (ImGui::Button("Close", ImVec2(128.0f, 0.0f) )
				|| !view.m_help)
				{
					view.m_help = false;
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}

			imguiEndFrame();

			if ( (!bgfx::isValid(texture) || view.m_fileIndex != fileIndex)
			&&  0 != view.m_fileList.size() )
			{
				if (bgfx::isValid(texture) )
				{
					bgfx::destroy(texture);
				}

				fileIndex = view.m_fileIndex;

				bx::FilePath fp = view.m_path;
				fp.join(view.m_fileList[view.m_fileIndex].c_str() );

				bimg::Orientation::Enum orientation;
				texture = loadTexture(fp.getCPtr()
					, 0
					| BGFX_SAMPLER_U_CLAMP
					| BGFX_SAMPLER_V_CLAMP
					| BGFX_SAMPLER_W_CLAMP
					, 0
					, &view.m_textureInfo
					, &orientation
					);

				bimg::TextureFormat::Enum format = bimg::TextureFormat::Enum(view.m_textureInfo.format);

				if (format < bimg::TextureFormat::Count)
				{
					view.m_inLinear = bimg::isFloat(format);

					switch (orientation)
					{
					default:
					case bimg::Orientation::R0:        cmdExec("view orientation\nview orientation z    0"); break;
					case bimg::Orientation::R90:       cmdExec("view orientation\nview orientation z  -90"); break;
					case bimg::Orientation::R180:      cmdExec("view orientation\nview orientation z -180"); break;
					case bimg::Orientation::R270:      cmdExec("view orientation\nview orientation z -270"); break;
					case bimg::Orientation::HFlip:     cmdExec("view orientation\nview orientation x -180"); break;
					case bimg::Orientation::HFlipR90:  cmdExec("view orientation\nview orientation z  -90\nview orientation x -180");  break;
					case bimg::Orientation::HFlipR270: cmdExec("view orientation\nview orientation z -270\nview orientation x -180"); break;
					case bimg::Orientation::VFlip:     cmdExec("view orientation\nview orientation y -180"); break;
					}
				}

				std::string title;
				if (isValid(texture) )
				{
					const char* name = "";
					if (view.m_textureInfo.cubeMap)
					{
						name = " CubeMap";
					}
					else if (1 < view.m_textureInfo.depth)
					{
						name = " 3D";
						view.m_textureInfo.numLayers = view.m_textureInfo.depth;
					}
					else if (1 < view.m_textureInfo.numLayers)
					{
						name = " 2D Array";
					}

					bx::stringPrintf(title, "%s (%d x %d%s, mips: %d, layers %d, %s)"
						, fp.getCPtr()
						, view.m_textureInfo.width
						, view.m_textureInfo.height
						, name
						, view.m_textureInfo.numMips
						, view.m_textureInfo.numLayers
						, bimg::getName(bimg::TextureFormat::Enum(view.m_textureInfo.format) )
						);
				}
				else
				{
					bx::stringPrintf(title, "Failed to load %s!", filePath);
				}

				entry::WindowHandle handle = { 0 };
				entry::setWindowTitle(handle, title.c_str() );
			}

			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency() );

			time += (float)(frameTime*speed/freq);

			float transitionTime = dragging ? 0.0f : 0.25f*view.m_transitionTime;

			posx.set(view.m_posx, transitionTime);
			posy.set(view.m_posy, transitionTime);

			float ortho[16];

			bx::mtxOrtho(
				  ortho
				, 0.0f
				, float(view.m_width)
				, float(view.m_height)
				, 0.0f
				, 0.0f
				, 1000.0f
				, 0.0f
				, caps->homogeneousDepth
				);
			bgfx::setViewTransform(BACKGROUND_VIEW_ID, NULL, ortho);
			bgfx::setViewRect(BACKGROUND_VIEW_ID, 0, 0, uint16_t(view.m_width), uint16_t(view.m_height) );

			setGeometry(Geometry::Quad
				, 0
				, 0
				, view.m_width
				, view.m_height
				, view.m_alpha || !bgfx::isValid(texture) ? UINT32_MAX : 0
				, float(view.m_width )/float(checkerBoardSize)
				, float(view.m_height)/float(checkerBoardSize)
				);
			bgfx::setTexture(0
				, s_texColor
				, checkerBoard
				);
			bgfx::setState(0
				| BGFX_STATE_WRITE_RGB
				| BGFX_STATE_WRITE_A
				);
			bgfx::submit(BACKGROUND_VIEW_ID
				, textureProgram
				);

			float px = posx.getValue();
			float py = posy.getValue();
			bx::mtxOrtho(
				  ortho
				, px-view.m_width/2.0f
				, px+view.m_width/2.0f
				, py+view.m_height/2.0f
				, py-view.m_height/2.0f
				, -10.0f
				,  10.0f
				, 0.0f
				, caps->homogeneousDepth
				);
			bgfx::setViewTransform(IMAGE_VIEW_ID, NULL, ortho);
			bgfx::setViewRect(IMAGE_VIEW_ID, 0, 0, uint16_t(view.m_width), uint16_t(view.m_height) );

			bgfx::dbgTextClear();

			float orientation[16];
			bx::mtxRotateXYZ(orientation, view.m_flipH, view.m_flipV, angle.getValue()+view.m_orientation);

			if (view.m_fit)
			{
				const bx::Vec3 wh = { float(view.m_textureInfo.width), float(view.m_textureInfo.height), 0.0f };
				const bx::Vec3 result = bx::round(bx::abs(bx::mul(wh, orientation) ) );

				scale.set(bx::min(float(view.m_width)  / result.x
					,             float(view.m_height) / result.y)
					, 0.1f*view.m_transitionTime
					);
			}
			else
			{
				scale.set(1.0f, 0.1f*view.m_transitionTime);
			}

			zoom.set(view.m_zoom, transitionTime);
			angle.set(view.m_angle, transitionTime);
			angx.set(view.m_angx, transitionTime);
			angy.set(view.m_angy, transitionTime);

			float ss = scale.getValue()
				* zoom.getValue()
				;

			setGeometry(view.m_textureInfo.cubeMap ? view.m_cubeMapGeo : Geometry::Quad
				, -int(view.m_textureInfo.width  * ss)/2
				, -int(view.m_textureInfo.height * ss)/2
				,  int(view.m_textureInfo.width  * ss)
				,  int(view.m_textureInfo.height * ss)
				, view.m_abgr
				);

			bgfx::setTransform(orientation);

			float mtx[16];
			bx::mtxRotateXY(mtx, angx.getValue(), angy.getValue() );
			bgfx::setUniform(u_mtx, mtx);

			mip.set(float(view.m_mip), 0.5f*view.m_transitionTime);
			layer.set(float(view.m_layer), 0.25f*view.m_transitionTime);
			ev.set(view.m_ev, 0.5f*view.m_transitionTime);

			float params[4] = { mip.getValue(), layer.getValue(), view.m_inLinear ? 1.0f : 0.0f, ev.getValue() };
			if (1 < view.m_textureInfo.depth)
			{
				params[1] = layer.getValue()/float(bx::max(1, view.m_textureInfo.depth >> view.m_mip) );
			}

			bgfx::setUniform(u_params0, params);

			float params1[4] = { float(view.m_outputFormat), 80.0f, 0.0, 0.0f };
			bgfx::setUniform(u_params1, params1);

			const uint32_t textureFlags = 0
				| BGFX_SAMPLER_U_CLAMP
				| BGFX_SAMPLER_V_CLAMP
				| BGFX_SAMPLER_W_CLAMP
				| (view.m_filter ? 0 : 0
				| BGFX_SAMPLER_MIN_POINT
				| BGFX_SAMPLER_MIP_POINT
				| BGFX_SAMPLER_MAG_POINT
				  )
				;

			bgfx::setTexture(0
				, s_texColor
				, texture
				, textureFlags
				);
			bgfx::setState(0
				| BGFX_STATE_WRITE_RGB
				| BGFX_STATE_WRITE_A
				| (view.m_alpha ? BGFX_STATE_BLEND_ALPHA : BGFX_STATE_NONE)
				);

			bgfx:: ProgramHandle program = textureProgram;
			if (1 < view.m_textureInfo.depth)
			{
				program = texture3DProgram;
			}
			else if (view.m_textureInfo.cubeMap)
			{
				program = Geometry::Quad == view.m_cubeMapGeo
					? textureCubeProgram
					: textureCube2Program
					;
			}
			else if (1 < view.m_textureInfo.numLayers)
			{
				program = textureArrayProgram;
			}
			else if (view.m_sdf)
			{
				if (8 < bimg::getBitsPerPixel(bimg::TextureFormat::Enum(view.m_textureInfo.format) ) )
				{
					program = textureMsdfProgram;
				}
				else
				{
					program = textureSdfProgram;
				}
			}

			if (bgfx::isValid(texture) )
			{
				bgfx::submit(IMAGE_VIEW_ID, program);
			}
			else
			{
				bgfx::discard();
			}

			bgfx::frame();

			// Slow down when nothing is animating...
			if (!dragging
			&&  !anyActive() )
			{
				bx::sleep(100);
			}
		}
	}

	if (bgfx::isValid(texture) )
	{
		bgfx::destroy(texture);
	}

	bgfx::destroy(checkerBoard);
	bgfx::destroy(s_texColor);
	bgfx::destroy(u_mtx);
	bgfx::destroy(u_params0);
	bgfx::destroy(u_params1);
	bgfx::destroy(textureProgram);
	bgfx::destroy(textureArrayProgram);
	bgfx::destroy(textureCubeProgram);
	bgfx::destroy(textureCube2Program);
	bgfx::destroy(textureSdfProgram);
	bgfx::destroy(textureMsdfProgram);
	bgfx::destroy(texture3DProgram);

	imguiDestroy();

	bgfx::shutdown();

	return exitcode;
}
