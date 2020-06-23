/*
 * Copyright 2019-2019 Attila Kocsis. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"

#include <bgfx/bgfx.h>

#include <bx/commandline.h>
#include <bx/easing.h>
#include <bx/file.h>
#include <bx/math.h>
#include <bx/os.h>
#include <bx/settings.h>

#include <entry/entry.h>
#include <entry/input.h>
#include <entry/cmd.h>
#include <entry/dialog.h>
#include <imgui/imgui.h>
#include <debugdraw/debugdraw.h>
#include <bgfx_utils.h>

#include <tinystl/allocator.h>
#include <tinystl/vector.h>
namespace stl = tinystl;
#include <string>
#include <algorithm>

#include <bgfx/embedded_shader.h>

#include "vs_mesh.bin.h"
#include "fs_mesh.bin.h"

#define SCENE_VIEW_ID 0

#define BGFX_GEOMETRYV_VERSION_MAJOR 1
#define BGFX_GEOMETRYV_VERSION_MINOR 0

static const bgfx::EmbeddedShader s_embeddedShaders[] =
{
	BGFX_EMBEDDED_SHADER(vs_mesh),
	BGFX_EMBEDDED_SHADER(fs_mesh),

	BGFX_EMBEDDED_SHADER_END()
};

static const char* s_attribShortNames[] =
{
	"P",   // Position
	"N",   // Normal
	"T",   // Tangent
	"B",   // Bitangent
	"C0",  // Color0
	"C1",  // Color1
	"C2",  // Color2
	"C3",  // Color3
	"I",   // Indices
	"W",   // Weight
	"TC0", // TexCoord0
	"TC1", // TexCoord1
	"TC2", // TexCoord2
	"TC3", // TexCoord3
	"TC4", // TexCoord4
	"TC5", // TexCoord5
	"TC6", // TexCoord6
	"TC7", // TexCoord7
};
BX_STATIC_ASSERT(BX_COUNTOF(s_attribShortNames) == bgfx::Attrib::Count);


static const char* s_supportedExt[] =
{
	"bin",
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

static const InputBinding s_bindingApp[] =
{
	{ entry::Key::KeyQ, entry::Modifier::None,  1, NULL, "exit"                },
	{ entry::Key::KeyF, entry::Modifier::None,  1, NULL, "graphics fullscreen" },

	INPUT_BINDING_END
};

const char* s_resetCmd =
	"view dolly\n"
	"view orbit\n"
	;

static const InputBinding s_bindingView[] =
{
	{ entry::Key::Esc,       entry::Modifier::None,       1, NULL, "exit"                    },

	{ entry::Key::Key1,      entry::Modifier::None,       1, NULL, "view dolly"              },

	{ entry::Key::Key0,      entry::Modifier::None,       1, NULL, s_resetCmd                },
	{ entry::Key::Plus,      entry::Modifier::None,       1, NULL, "view dolly +0.1"          },
	{ entry::Key::Minus,     entry::Modifier::None,       1, NULL, "view dolly -0.1"          },

	{ entry::Key::KeyW,      entry::Modifier::None,       1, NULL, "view orbit y -0.1"         },
	{ entry::Key::KeyS,      entry::Modifier::None,       1, NULL, "view orbit y +0.1"         },
	{ entry::Key::KeyA,      entry::Modifier::None,       1, NULL, "view orbit x +0.1"         },
	{ entry::Key::KeyD,      entry::Modifier::None,       1, NULL, "view orbit x -0.1"         },

	{ entry::Key::Up,        entry::Modifier::None,       1, NULL, "view file-up"            },
	{ entry::Key::Down,      entry::Modifier::None,       1, NULL, "view file-down"          },

	{ entry::Key::KeyI,      entry::Modifier::None,       1, NULL, "view info"               },

	{ entry::Key::KeyH,      entry::Modifier::None,       1, NULL, "view help"               },

	{ entry::Key::Return,    entry::Modifier::None,       1, NULL, "view files"              },

	{ entry::Key::Space,     entry::Modifier::None,       1, NULL, "view geo\n"              },

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
	"Bgfx geometry (bin) | *.bin\n"
	;

struct Camera
{
	Camera()
	{
		init(bx::Vec3(0.0f,0.0f,0.0f), 2.0f, 0.01f, 100.0f);
	}

	void init(const bx::Vec3& _center, float _distance, float _near, float _far)
	{
		m_target.curr = _center;
		m_target.dest = _center;

		m_pos.curr = _center;
		m_pos.curr.z += _distance;
		m_pos.dest = _center;
		m_pos.dest.z += _distance;

		m_orbit[0] = 0.0f;
		m_orbit[1] = 0.0f;

		m_near = _near;
		m_far  = _far;
	}

	void mtxLookAt(float* _outViewMtx)
	{
		bx::mtxLookAt(_outViewMtx, m_pos.curr, m_target.curr);
	}

	void orbit(float _dx, float _dy)
	{
		m_orbit[0] += _dx;
		m_orbit[1] += _dy;
	}

	void distance(float _z)
	{
		_z = bx::clamp(_z, m_near, m_far);

		bx::Vec3 toTarget     = bx::sub(m_target.dest, m_pos.dest);
		bx::Vec3 toTargetNorm = bx::normalize(toTarget);

		m_pos.dest = bx::mad(toTargetNorm, -_z, m_target.dest);
	}

	void dolly(float _dz)
	{
		const bx::Vec3 toTarget     = bx::sub(m_target.dest, m_pos.dest);
		const float toTargetLen     = bx::length(toTarget);
		const float invToTargetLen  = 1.0f / (toTargetLen + bx::kFloatMin);
		const bx::Vec3 toTargetNorm = bx::mul(toTarget, invToTargetLen);

		float delta  = toTargetLen * _dz;
		float newLen = toTargetLen - delta;

		if ( (m_near  < newLen || _dz < 0.0f)
			&&   (newLen < m_far   || _dz > 0.0f) )
		{
			m_pos.dest = bx::mad(toTargetNorm, delta, m_pos.dest);
		}
	}

	void consumeOrbit(float _amount)
	{
		float consume[2];
		consume[0] = m_orbit[0] * _amount;
		consume[1] = m_orbit[1] * _amount;
		m_orbit[0] -= consume[0];
		m_orbit[1] -= consume[1];

		const bx::Vec3 toPos     = bx::sub(m_pos.curr, m_target.curr);
		const float toPosLen     = bx::length(toPos);
		const float invToPosLen  = 1.0f / (toPosLen + bx::kFloatMin);
		const bx::Vec3 toPosNorm = bx::mul(toPos, invToPosLen);

		float ll[2];
		bx::toLatLong(&ll[0], &ll[1], toPosNorm);
		ll[0] += consume[0];
		ll[1] -= consume[1];
		ll[1]  = bx::clamp(ll[1], 0.02f, 0.98f);

		const bx::Vec3 tmp  = bx::fromLatLong(ll[0], ll[1]);
		const bx::Vec3 diff = bx::mul(bx::sub(tmp, toPosNorm), toPosLen);

		m_pos.curr = bx::add(m_pos.curr, diff);
		m_pos.dest = bx::add(m_pos.dest, diff);
	}

	void update(float _dt)
	{
		const float amount = bx::min(_dt / 0.12f, 1.0f);

		consumeOrbit(amount);

		m_target.curr = bx::lerp(m_target.curr, m_target.dest, amount);
		m_pos.curr    = bx::lerp(m_pos.curr,    m_pos.dest,    amount);
	}

	struct Interp3f
	{
		bx::Vec3 curr;
		bx::Vec3 dest;
	};

	Interp3f m_target;
	Interp3f m_pos;
	float m_orbit[2];
	float m_near, m_far;
};

struct Mouse
{
	Mouse()
	{
		m_dx = 0.0f;
		m_dy = 0.0f;
		m_prevMx = 0.0f;
		m_prevMx = 0.0f;
		m_scroll = 0;
		m_scrollPrev = 0;
	}

	void update(float _mx, float _my, int32_t _mz, uint32_t _width, uint32_t _height)
	{
		const float widthf  = float(int32_t(_width));
		const float heightf = float(int32_t(_height));

		// Delta movement.
		m_dx = float(_mx - m_prevMx)/widthf;
		m_dy = float(_my - m_prevMy)/heightf;

		m_prevMx = _mx;
		m_prevMy = _my;

		// Scroll.
		m_scroll = _mz - m_scrollPrev;
		m_scrollPrev = _mz;
	}

	float m_dx; // Screen space.
	float m_dy;
	float m_prevMx;
	float m_prevMy;
	int32_t m_scroll;
	int32_t m_scrollPrev;
};

struct View
{
	View()
		: m_fileIndex(0)
		, m_width(1280)
		, m_height(720)
		, m_help(false)
		, m_about(false)
		, m_info(false)
		, m_files(false)
		, m_axes(false)
		, m_meshCenter(0.0f,0.0f,0.0f)
		, m_meshRadius(1.0f)
		, m_idleTimer(0.0f)
	{
		load();
	}

	~View()
	{
	}
	int32_t cmd(int32_t _argc, char const* const* _argv)
	{
		if (_argc >= 2)
		{
			if (0 == bx::strCmp(_argv[1], "file-up") )
			{
				m_fileIndex = bx::uint32_satsub(m_fileIndex, 1);
			}
			else if (0 == bx::strCmp(_argv[1], "file-down") )
			{
				uint32_t numFiles = bx::uint32_satsub(uint32_t(m_fileList.size() ), 1);
				++m_fileIndex;
				m_fileIndex = bx::uint32_min(m_fileIndex, numFiles);
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
			else if (0 == bx::strCmp(_argv[1], "dolly") )
			{
				if (_argc >= 3)
				{
					float dolly;
					bx::fromString(&dolly, _argv[2]);

					if (_argv[2][0] == '+'
						||  _argv[2][0] == '-')
					{
						m_camera.dolly(dolly);
						m_idleTimer = 0.0f;
					}
				}
				else
				{
					m_camera.distance(m_meshRadius * 2.0f);
				}
			}
			else if (0 == bx::strCmp(_argv[1], "orbit") )
			{
				if (_argc >= 4)
				{
					int axis = (_argv[2][0] == 'x' ? 0 : 1);
					float orbit[2] = { 0.0f, 0.0f};
					bx::fromString(&orbit[axis], _argv[3]);

					m_camera.orbit(orbit[0], orbit[1]);
					m_idleTimer = 0.0f;
				}
				else
				{
					m_camera.m_target.dest = m_meshCenter;

					m_camera.m_pos.dest = m_meshCenter;
					m_camera.m_pos.dest.z -= m_meshRadius * 2.0f;

					m_camera.m_orbit[0] = 0.0f;
					m_camera.m_orbit[1] = 0.0f;
				}
			}
			else if (0 == bx::strCmp(_argv[1], "axes") )
			{
				m_axes ^= true;
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
		filePath.join(".config/bgfx/geometryv.ini");

		bx::Settings settings(entry::getAllocator() );

		bx::FileReader reader;
		if (bx::open(&reader, filePath) )
		{
			bx::read(&reader, settings);
			bx::close(&reader);

			if (!bx::fromString(&m_width, settings.get("view/width") ) )
			{
				m_width = 1280;
			}

			if (!bx::fromString(&m_height, settings.get("view/height") ) )
			{
				m_height = 720;
			}
		}
	}

	void save()
	{
		bx::FilePath filePath(bx::Dir::Home);
		filePath.join(".config/bgfx/geometryv.ini");

		if (bx::makeAll(filePath.getPath() ) )
		{
			bx::Settings settings(entry::getAllocator() );

			char tmp[256];

			bx::toString(tmp, sizeof(tmp), m_width);
			settings.set("view/width", tmp);

			bx::toString(tmp, sizeof(tmp), m_height);
			settings.set("view/height", tmp);

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

	uint32_t m_fileIndex;
	uint32_t m_width;
	uint32_t m_height;
	bool     m_help;
	bool     m_about;
	bool     m_info;
	bool     m_files;
	bool 	 m_axes;

	Camera	m_camera;
	Mouse   m_mouse;
	bx::Vec3 m_meshCenter;
	float	 m_meshRadius;
	float	 m_idleTimer;

};

int cmdView(CmdContext* /*_context*/, void* _userData, int _argc, char const* const* _argv)
{
	View* view = static_cast<View*>(_userData);
	return view->cmd(_argc, _argv);
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
		if (isActive() )
		{
			const double freq = double(bx::getHPFrequency() );
			int64_t now = bx::getHPCounter();
			float time = (float)(double(now - offset) / freq);
			float lerp = bx::clamp(time, 0.0f, duration) / duration;
			return lerpT(from, to, easeT(lerp) );
		}

		return to;
	}

	bool isActive() const
	{
		const double freq = double(bx::getHPFrequency() );
		int64_t now = bx::getHPCounter();
		float time = (float)(double(now - offset) / freq);
		float lerp = bx::clamp(time, 0.0f, duration) / duration;
		return lerp < 1.0f;
	}
};

typedef InterpolatorT<bx::lerp, bx::easeInOutQuad> Interpolator;

void keyBindingHelp(const char* _bindings, const char* _description)
{
	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), _bindings);
	ImGui::SameLine(140);
	ImGui::Text(_description);
}

void help(const char* _error = NULL)
{
	if (NULL != _error)
	{
		bx::printf("Error:\n%s\n\n", _error);
	}

	bx::printf(
		  "geometryv, bgfx geometry viewer tool, version %d.%d.%d.\n"
		  "Copyright 2019-2019 Attila Kocsis. All rights reserved.\n"
		  "License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause\n\n"
		, BGFX_GEOMETRYV_VERSION_MAJOR
		, BGFX_GEOMETRYV_VERSION_MINOR
		, BGFX_API_VERSION
		);

	bx::printf(
		  "Usage: geometryv <file path>\n"
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
			  "geometryv, bgfx geometry viewer tool, version %d.%d.%d.\n"
			, BGFX_GEOMETRYV_VERSION_MAJOR
			, BGFX_GEOMETRYV_VERSION_MINOR
			, BGFX_API_VERSION
			);
		return bx::kExitSuccess;
	}

	if (cmdLine.hasArg('h', "help") )
	{
		help();
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
	init.resolution.width = view.m_width;
	init.resolution.width = view.m_height;
	init.resolution.reset = 0
		| BGFX_RESET_VSYNC
		| BGFX_RESET_MSAA_X16
		;

	bgfx::init(init);

	// Set view 0 clear state.
	bgfx::setViewClear(SCENE_VIEW_ID
		, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
		, 0x000000ff
		, 1.0f
		, 0
		);

	imguiCreate();

	ddInit();

	const bgfx::Caps* caps = bgfx::getCaps();
	bgfx::RendererType::Enum type = caps->rendererType;

	bgfx::ShaderHandle vsMesh      = bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_mesh");
	bgfx::ShaderHandle fsMesh      = bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_mesh");

	bgfx::ProgramHandle meshProgram = bgfx::createProgram(
		  vsMesh
		, fsMesh
		, true
		);

	float speed = 0.37f;
	float time  = 0.0f;

	Interpolator menuFade(5.0f);

	auto anyActive = [&]() -> bool
	{
		return false
			|| ImGui::MouseOverArea()
			|| menuFade.isActive()
			;
	};

	const char* filePath = _argc < 2 ? "" : _argv[1];

	std::string path = filePath;
	{
		bx::FilePath fp(filePath);
		view.updateFileList(fp);
	}

	int exitcode = bx::kExitSuccess;
	Mesh* mesh = NULL;

	{
		uint32_t fileIndex = 0;

		entry::WindowState windowState;
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
							, "geometryv: Open File"
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

					bool axes = view.m_axes;
					if (ImGui::MenuItem("XYZ Axes", NULL, &axes) )
					{
						cmdExec("view axes");
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
						, view.m_fileList[view.m_fileIndex].c_str()
						);
				}

				ImGui::EndMainMenuBar();
			}

			ImGui::PopStyleVar(2);

			static bool help = false;
			static bool about = false;

			view.m_mouse.update(float(mouseState.m_mx), float(mouseState.m_my), mouseState.m_mz, view.m_width, view.m_height);
			if (!overArea)
			{
				if (mouseState.m_buttons[entry::MouseButton::Left])
				{
					view.m_idleTimer = 0.0f;
					view.m_camera.orbit(view.m_mouse.m_dx, view.m_mouse.m_dy);
				}
				else if (mouseState.m_buttons[entry::MouseButton::Right])
				{
					view.m_idleTimer = 0.0f;
					view.m_camera.dolly(view.m_mouse.m_dx + view.m_mouse.m_dy);
				}
				else if (0 != view.m_mouse.m_scroll)
				{
					view.m_idleTimer = 0.0f;
					view.m_camera.dolly(float(view.m_mouse.m_scroll)*0.1f);
				}
			}

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
					  ImVec2(450.0f, 320.0f)
					, ImGuiCond_FirstUseEver
					);

				if (ImGui::Begin("Info", &view.m_info) )
				{
					if (ImGui::BeginChild("##info", ImVec2(0.0f, 0.0f) ) )
					{
						if (NULL == mesh)
						{
							ImGui::Text("Geometry is not loaded.");
						}
						else
						{
							char layout[128] = {0};
							for(int32_t attrib = bgfx::Attrib::Position; attrib < bgfx::Attrib::Count; attrib++)
							{
								if ( mesh->m_layout.has(bgfx::Attrib::Enum(attrib)) )
									bx::strCat(layout, sizeof(layout), s_attribShortNames[attrib]);
							}

							ImGui::Text("Name: %s %s", view.m_fileList[view.m_fileIndex].c_str(), layout);

							ImGui::Indent();
							for (GroupArray::const_iterator itGroup = mesh->m_groups.begin(), itGroupEnd = mesh->m_groups.end(); itGroup != itGroupEnd; ++itGroup)
							{
								ImGui::Text("Group v %d i %d c %.2f %.2f %.2f r %.2f", itGroup->m_numVertices, itGroup->m_numIndices,
											itGroup->m_sphere.center.x, itGroup->m_sphere.center.y, itGroup->m_sphere.center.z,
											itGroup->m_sphere.radius);
								ImGui::Indent();
								for (PrimitiveArray::const_iterator itPrim = itGroup->m_prims.begin(), itPrimEnd = itGroup->m_prims.end(); itPrim != itPrimEnd; ++itPrim)
								{
									ImGui::Text("Primitive v %d i %d c %.2f %.2f %.2f r %.2f", itPrim->m_numVertices, itPrim->m_numIndices,
												itPrim->m_sphere.center.x, itPrim->m_sphere.center.y, itPrim->m_sphere.center.z,
												itPrim->m_sphere.radius);
								}
								ImGui::Unindent();
							}
							ImGui::Unindent();

							ImGui::Separator();
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
						if (ImGui::ListBoxHeader("##empty", ImVec2(0.0f, listHeight) ) )
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

							ImGuiListClipper clipper(itemCount, itemHeight);

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

							clipper.End();

							ImGui::ListBoxFooter();
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
					"geometryv, bgfx geometry viewer tool " ICON_KI_WRENCH ", version %d.%d.%d.\n"
					"Copyright 2019-2019 Attila Kocsis. All rights reserved.\n"
					"License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause\n"
					, BGFX_GEOMETRYV_VERSION_MAJOR
					, BGFX_GEOMETRYV_VERSION_MINOR
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
				keyBindingHelp("i", "Toggle info screen.");
				keyBindingHelp("f", "Toggle full-screen.");
				ImGui::NextLine();

				keyBindingHelp("LMB+drag",		  "Orbit.");
				keyBindingHelp("W/A/S/D",		  "Orbit.");
				keyBindingHelp("RMB+drag or MW",  "Dolly.");
				keyBindingHelp("=/-", "Dolly.");
				keyBindingHelp("0",   "Reset.");
				keyBindingHelp("1",   "Fit to window.");
				ImGui::NextLine();

				keyBindingHelp("up",   "Previous geometry.");
				keyBindingHelp("down", "Next geometry.");
				ImGui::NextLine();

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

			if ( (NULL == mesh || view.m_fileIndex != fileIndex)
			&&  0 != view.m_fileList.size() )
			{
				if (NULL != mesh )
				{
					meshUnload(mesh);
				}

				fileIndex = view.m_fileIndex;

				bx::FilePath fp = view.m_path;
				fp.join(view.m_fileList[view.m_fileIndex].c_str() );

				mesh = meshLoad(fp.getCPtr());

				std::string title;
				if (NULL != mesh )
				{
					uint32_t numPrimitives = 0;
					uint32_t numVertices = 0;
					uint32_t numIndices = 0;
					Aabb boundingBox = {};

					for (GroupArray::const_iterator it = mesh->m_groups.begin(), itEnd = mesh->m_groups.end(); it != itEnd; ++it)
					{
						if ( it == mesh->m_groups.begin())
						{
							boundingBox = it->m_aabb;
						}
						else
						{
							aabbExpand(boundingBox, it->m_aabb.min);
							aabbExpand(boundingBox, it->m_aabb.max);
						}

						numPrimitives += (uint32_t)it->m_prims.size();
						numVertices += (uint32_t)it->m_numVertices;
						numIndices += (uint32_t)it->m_numIndices;
					}

					bx::stringPrintf(
						  title
						, "%s (g %d, p %d, v %d, i %d)"
						, fp.getCPtr()
						, mesh->m_groups.size()
						, numPrimitives
						, numVertices
						, numIndices
						);

					view.m_meshCenter = getCenter(boundingBox);
					view.m_meshRadius = bx::length(getExtents(boundingBox));

					view.m_camera.init( view.m_meshCenter, view.m_meshRadius * 2.0f, 0.01f, view.m_meshRadius * 10.0f);
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
			const float deltaTime = float(frameTime/freq);

			time += (float)(frameTime*speed/freq);

			// Update camera.
			float viewMatrix[16];
			view.m_camera.update(deltaTime);
			view.m_camera.mtxLookAt(viewMatrix);

			float projMatrix[16];
			const float aspect = float(view.m_width)/float(view.m_height);
			bx::mtxProj(projMatrix, 60.0f, aspect, 0.01f, 1000.0f, caps->homogeneousDepth);

			bgfx::setViewTransform(SCENE_VIEW_ID, viewMatrix, projMatrix);
			bgfx::setViewRect(SCENE_VIEW_ID, 0, 0, uint16_t(view.m_width), uint16_t(view.m_height) );

			bgfx::touch(SCENE_VIEW_ID);

			if ( view.m_axes )
			{
				DebugDrawEncoder dde;
				dde.begin(SCENE_VIEW_ID);
				dde.drawAxis(0.0f, 0.0f, 0.0f);
				dde.drawGrid(Axis::Y, {0.0f, 0.0f, 0.0f});
				dde.end();
			}

			bgfx::dbgTextClear();

			float orientation[16];
			bx::mtxIdentity(orientation);
			bgfx::setTransform(orientation);

			float mtx[16];
			bx::mtxIdentity(mtx);

			if (NULL != mesh)
			{
				meshSubmit(mesh
					, SCENE_VIEW_ID
					, meshProgram
					, mtx);
			}

			bgfx::frame();

			// Slow down when nothing is animating...
			if (view.m_idleTimer > 2.0f
			&&  !anyActive() )
			{
				bx::sleep(100);
			}

			view.m_idleTimer += deltaTime;
		}
	}

	if (NULL != mesh )
	{
		meshUnload(mesh);
	}

	bgfx::destroy(meshProgram);

	ddShutdown();

	imguiDestroy();

	bgfx::shutdown();

	return exitcode;
}
