/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx/bgfx.h>
#include <bx/commandline.h>

///
struct Args
{
	static constexpr bx::CommandLineOption s_rendererOptions[] =
	{
		{ '\0', "gl",    0, NULL, "Force OpenGL renderer."             },
		{ '\0', "vk",    0, NULL, "Force Vulkan renderer."             },
		{ '\0', "wgpu",  0, NULL, "Force WebGPU renderer."             },
		{ '\0', "noop",  0, NULL, "Force no-op renderer."              },
		{ '\0', "d3d11", 0, NULL, "Force Direct3D 11 renderer."        },
		{ '\0', "d3d12", 0, NULL, "Force Direct3D 12 renderer."        },
		{ '\0', "mtl",   0, NULL, "Force Metal renderer. (macOS only)" },
	};

	static constexpr bx::CommandLineOption s_vendorOptions[] =
	{
		{ '\0', "amd",       0, NULL, "Prefer AMD GPU."             },
		{ '\0', "apple",     0, NULL, "Prefer Apple GPU."           },
		{ '\0', "arm",       0, NULL, "Prefer ARM GPU."             },
		{ '\0', "intel",     0, NULL, "Prefer Intel GPU."           },
		{ '\0', "nvidia",    0, NULL, "Prefer NVIDIA GPU."          },
		{ '\0', "microsoft", 0, NULL, "Prefer Microsoft GPU."       },
		{ '\0', "sw",        0, NULL, "Prefer software rasterizer." },
	};

	Args(int _argc, const char* const* _argv)
		: m_type(bgfx::RendererType::Count)
		, m_pciId(BGFX_PCI_ID_NONE)
	{
		bx::CommandLine cmdLine(_argc, (const char**)_argv, s_rendererOptions, BX_COUNTOF(s_rendererOptions) );

		if (cmdLine.hasArg("gl") )
		{
			m_type = bgfx::RendererType::OpenGL;
		}
		else if (cmdLine.hasArg("vk") )
		{
			m_type = bgfx::RendererType::Vulkan;
		}
		else if (cmdLine.hasArg("wgpu") )
		{
			m_type = bgfx::RendererType::WebGPU;
		}
		else if (cmdLine.hasArg("noop") )
		{
			m_type = bgfx::RendererType::Noop;
		}
		else if (cmdLine.hasArg("d3d11") )
		{
			m_type = bgfx::RendererType::Direct3D11;
		}
		else if (cmdLine.hasArg("d3d12") )
		{
			m_type = bgfx::RendererType::Direct3D12;
		}
		else if (BX_ENABLED(BX_PLATFORM_OSX) )
		{
			if (cmdLine.hasArg("mtl") )
			{
				m_type = bgfx::RendererType::Metal;
			}
		}

		bx::CommandLine vendorCmdLine(_argc, (const char**)_argv, s_vendorOptions, BX_COUNTOF(s_vendorOptions) );

		if (vendorCmdLine.hasArg("amd") )
		{
			m_pciId = BGFX_PCI_ID_AMD;
		}
		else if (vendorCmdLine.hasArg("apple") )
		{
			m_pciId = BGFX_PCI_ID_APPLE;
		}
		else if (vendorCmdLine.hasArg("arm") )
		{
			m_pciId = BGFX_PCI_ID_ARM;
		}
		else if (vendorCmdLine.hasArg("intel") )
		{
			m_pciId = BGFX_PCI_ID_INTEL;
		}
		else if (vendorCmdLine.hasArg("nvidia") )
		{
			m_pciId = BGFX_PCI_ID_NVIDIA;
		}
		else if (vendorCmdLine.hasArg("microsoft") )
		{
			m_pciId = BGFX_PCI_ID_MICROSOFT;
		}
		else if (vendorCmdLine.hasArg("sw") )
		{
			m_pciId = BGFX_PCI_ID_SOFTWARE_RASTERIZER;
		}
	}

	bgfx::RendererType::Enum m_type;
	uint16_t m_pciId;
};
