/*
 * Copyright 2011-2025 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx/bgfx.h>
#include <bx/commandline.h>

///
struct Args
{
	Args(int _argc, const char* const* _argv)
		: m_type(bgfx::RendererType::Count)
		, m_pciId(BGFX_PCI_ID_NONE)
	{
		bx::CommandLine cmdLine(_argc, (const char**)_argv);

		if (cmdLine.hasArg("gl") )
		{
			m_type = bgfx::RendererType::OpenGL;
		}
		else if (cmdLine.hasArg("vk") )
		{
			m_type = bgfx::RendererType::Vulkan;
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

		if (cmdLine.hasArg("amd") )
		{
			m_pciId = BGFX_PCI_ID_AMD;
		}
		else if (cmdLine.hasArg("nvidia") )
		{
			m_pciId = BGFX_PCI_ID_NVIDIA;
		}
		else if (cmdLine.hasArg("intel") )
		{
			m_pciId = BGFX_PCI_ID_INTEL;
		}
		else if (cmdLine.hasArg("sw") )
		{
			m_pciId = BGFX_PCI_ID_SOFTWARE_RASTERIZER;
		}
	}

	bgfx::RendererType::Enum m_type;
	uint16_t m_pciId;
};
