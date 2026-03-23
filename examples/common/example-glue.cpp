/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "imgui/imgui.h"
#include "entry/entry.h"
#include "entry/cmd.h"
#include "entry/dialog.h"
#include <bx/string.h>
#include <bx/timer.h>
#include <bx/math.h>

struct SampleData
{
	static constexpr uint32_t kNumSamples = 100;

	SampleData()
	{
		reset();
	}

	void reset()
	{
		m_offset = 0;
		bx::memSet(m_values, 0, sizeof(m_values) );

		m_min = 0.0f;
		m_max = 0.0f;
		m_avg = 0.0f;
	}

	void pushSample(float value)
	{
		m_values[m_offset] = value;
		m_offset = (m_offset+1) % kNumSamples;

		float min = bx::max<float>();
		float max = bx::min<float>();
		float avg = 0.0f;

		for (uint32_t ii = 0; ii < kNumSamples; ++ii)
		{
			const float val = m_values[ii];
			min  = bx::min(min, val);
			max  = bx::max(max, val);
			avg += val;
		}

		m_min = min;
		m_max = max;
		m_avg = avg / kNumSamples;
	}

	int32_t m_offset;
	float m_values[kNumSamples];

	float m_min;
	float m_max;
	float m_avg;
};

static SampleData s_frameTime;

static bool bar(const char* _name, float _width, float _maxWidth, float _height, const ImVec4& _color)
{
	ImGui::PushID(_name);

	const ImGuiStyle& style = ImGui::GetStyle();

	ImVec4 hoveredColor(
		  _color.x + _color.x*0.1f
		, _color.y + _color.y*0.1f
		, _color.z + _color.z*0.1f
		, _color.w + _color.w*0.1f
		);

	ImGui::PushStyleColor(ImGuiCol_Button,        _color);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hoveredColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive,  _color);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, style.ItemSpacing.y) );

	bool itemHovered = false;

	ImGui::Button("##button", ImVec2(_width, _height) );
	itemHovered |= ImGui::IsItemHovered();

	ImGui::SameLine();
	ImGui::InvisibleButton("##invisible_button", ImVec2(bx::max(1.0f, _maxWidth-_width), _height) );
	itemHovered |= ImGui::IsItemHovered();

	ImGui::PopStyleVar(2);
	ImGui::PopStyleColor(3);

	ImGui::PopID();

	return itemHovered;
}

static constexpr ImVec4 kResourceColor(0.5f, 0.5f, 0.5f, 1.0f);

static void resourceBar(const char* _name, const char* _tooltip, uint32_t _num, uint32_t _max, float _maxWidth, float _height)
{
	ImGui::PushID(_name);

	bool itemHovered = false;

	ImGui::Text("%s: %4d / %4d", _name, _num, _max);
	itemHovered |= ImGui::IsItemHovered();
	ImGui::SameLine();

	const float percentage = float(_num)/float(_max);

	itemHovered |= bar("Resource", bx::max(1.0f, percentage * _maxWidth), _maxWidth, _height, kResourceColor);
	ImGui::SameLine();

	ImGui::Text("%5.2f%%", percentage*100.0f);

	if (itemHovered)
	{
		ImGui::SetTooltip("%s %5.2f%%"
			, _tooltip
			, percentage*100.0f
			);
	}

	ImGui::PopID();
}

static bool s_showStats = false;

static const char* getRendererArg(bgfx::RendererType::Enum _type)
{
	switch (_type)
	{
	case bgfx::RendererType::Direct3D11: return "--d3d11";
	case bgfx::RendererType::Direct3D12: return "--d3d12";
	case bgfx::RendererType::Metal:      return "--mtl";
	case bgfx::RendererType::OpenGL:     return "--gl";
	case bgfx::RendererType::Vulkan:     return "--vk";
	case bgfx::RendererType::WebGPU:     return "--wgpu";
	case bgfx::RendererType::Noop:       return "--noop";
	default: break;
	}

	return "";
}

static const char* getPciIdArg(uint16_t _pciId)
{
	switch (_pciId)
	{
	case BGFX_PCI_ID_SOFTWARE_RASTERIZER: return "--sw";
	case BGFX_PCI_ID_AMD:                 return "--amd";
	case BGFX_PCI_ID_APPLE:               return "--apple";
	case BGFX_PCI_ID_ARM:                 return "--arm";
	case BGFX_PCI_ID_INTEL:               return "--intel";
	case BGFX_PCI_ID_NVIDIA:              return "--nvidia";
	case BGFX_PCI_ID_MICROSOFT:           return "--microsoft";
	default: break;
	}

	return "";
}

static const char* getPciIdName(uint16_t _pciId)
{
	switch (_pciId)
	{
	case BGFX_PCI_ID_AMD:                 return "AMD";
	case BGFX_PCI_ID_APPLE:               return "Apple";
	case BGFX_PCI_ID_ARM:                 return "ARM";
	case BGFX_PCI_ID_INTEL:               return "Intel";
	case BGFX_PCI_ID_MICROSOFT:           return "Microsoft";
	case BGFX_PCI_ID_NVIDIA:              return "nVidia";
	case BGFX_PCI_ID_SOFTWARE_RASTERIZER: return "Software Rasterizer";
	default: break;
	}

	return "?";
}

void showExampleDialog(entry::AppI* _app, const char* _errorText)
{
	char temp[1024];
	bx::snprintf(temp, BX_COUNTOF(temp), "Example: %s", _app->getName() );

	ImGui::SetNextWindowPos(
		  ImVec2(10.0f, 50.0f)
		, ImGuiCond_FirstUseEver
		);
	ImGui::SetNextWindowSize(
		  ImVec2(300.0f, 0.0f)
		, ImGuiCond_Always
		);

	ImGui::Begin(temp);

	ImGui::TextWrapped("%s", _app->getDescription() );

	bx::StringView url = _app->getUrl();
	if (!url.isEmpty() )
	{
		ImGui::SameLine();
		if (ImGui::SmallButton(ICON_FA_LINK) )
		{
			openUrl(url);
		}
		else if (ImGui::IsItemHovered() )
		{
			ImGui::SetTooltip("Documentation: %.*s", url.getLength(), url.getPtr() );
		}
	}

	ImGui::Separator();

	if (NULL != _errorText)
	{
		const int64_t now  = bx::getHPCounter();
		const int64_t freq = bx::getHPFrequency();
		const float   time = float(now%freq)/float(freq);

		bool blink = time > 0.5f;

		ImGui::PushStyleColor(ImGuiCol_Text
			, blink
			? ImVec4(1.0, 0.0, 0.0, 1.0)
			: ImVec4(1.0, 1.0, 1.0, 1.0)
			);
		ImGui::TextWrapped("%s", _errorText);
		ImGui::Separator();
		ImGui::PopStyleColor();
	}

	{
		uint32_t num = entry::getNumApps();
		const char** items = (const char**)BX_STACK_ALLOC(num*sizeof(void*) );

		uint32_t ii = 0;
		int32_t current = 0;
		for (entry::AppI* app = entry::getFirstApp(); NULL != app; app = app->getNext() )
		{
			if (app == _app)
			{
				current = ii;
			}

			items[ii++] = app->getName();
		}

		if (1 < num
		&&  ImGui::Combo("Example", &current, items, num) )
		{
			char command[1024];
			bx::snprintf(command, BX_COUNTOF(command), "app restart %s", items[current]);
			cmdExec(command);
		}

		const bgfx::Caps* caps = bgfx::getCaps();
		if (0 != (caps->supported & BGFX_CAPS_GRAPHICS_DEBUGGER) )
		{
			ImGui::SameLine();
			ImGui::Text(ICON_FA_SNOWFLAKE_O);
		}

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(3.0f, 3.0f) );

		if (ImGui::Button(ICON_FA_REPEAT " Restart" ) )
		{
			cmdExec("app restart");
		}

		if (1 < entry::getNumApps() )
		{
			ImGui::SameLine();
			if (ImGui::Button(ICON_KI_PREVIOUS " Prev") )
			{
				cmdExec("app restart prev");
			}

			ImGui::SameLine();
			if (ImGui::Button(ICON_KI_NEXT " Next") )
			{
				cmdExec("app restart next");
			}
		}

		ImGui::SameLine();
		if (ImGui::Button(ICON_KI_EXIT " Exit") )
		{
			cmdExec("exit");
		}

		ImGui::SameLine();
		s_showStats ^= ImGui::Button(ICON_FA_BAR_CHART);

		ImGui::PopStyleVar();
	}

	const bgfx::Caps* caps = bgfx::getCaps();

	static bool s_rendererHeaderOpen = false;

	char rendererHeader[64];
	if (s_rendererHeaderOpen)
	{
		bx::strCopy(rendererHeader, BX_COUNTOF(rendererHeader), "Choose Renderer / GPU###gpu-choice");
	}
	else
	{
		bx::snprintf(
			  rendererHeader
			, BX_COUNTOF(rendererHeader)
			, "Renderer: %s / %s###gpu-choice"
			, bgfx::getRendererName(bgfx::getRendererType() )
			, getPciIdName(caps->vendorId)
			);
	}

	s_rendererHeaderOpen = ImGui::CollapsingHeader(rendererHeader);
	if (s_rendererHeaderOpen)
	{
		bgfx::RendererType::Enum supportedRenderers[bgfx::RendererType::Count];
		const uint8_t num = bgfx::getSupportedRenderers(BX_COUNTOF(supportedRenderers), supportedRenderers);

		const char* items[bgfx::RendererType::Count];

		uint8_t filteredNum = 0;
		bgfx::RendererType::Enum filteredRenderers[bgfx::RendererType::Count];
		int32_t current = 0;
		for (uint8_t ii = 0; ii < num; ++ii)
		{
			if (bgfx::RendererType::Noop == supportedRenderers[ii])
			{
				continue;
			}

			filteredRenderers[filteredNum] = supportedRenderers[ii];
			items[filteredNum] = bgfx::getRendererName(supportedRenderers[ii]);
			if (supportedRenderers[ii] == caps->rendererType)
			{
				current = filteredNum;
			}
			++filteredNum;
		}

		const float labelWidth = ImGui::CalcTextSize("Renderer ").x + 10.0f;

		const char* newRendererArg = NULL;
		const char* newPciIdArg    = NULL;

		ImGui::TextUnformatted("Renderer"); ImGui::SameLine(labelWidth);
		ImGui::PushItemWidth(-1);
		if (ImGui::Combo("##Renderer", &current, items, filteredNum) )
		{
			newRendererArg = getRendererArg(filteredRenderers[current]);
		}

		const uint8_t numGPUs = caps->numGPUs;
		ImGui::BeginDisabled(0 == numGPUs);
		{
			static char unknownVendor[BX_COUNTOF(bgfx::Caps::gpu)][16];
			current = 0;
			for (uint8_t ii = 0; ii < numGPUs; ++ii)
			{
				const bgfx::Caps::GPU& gpu = caps->gpu[ii];

				switch (gpu.vendorId)
				{
				case BGFX_PCI_ID_AMD:                 items[ii] = "AMD";                 break;
				case BGFX_PCI_ID_APPLE:               items[ii] = "Apple";               break;
				case BGFX_PCI_ID_INTEL:               items[ii] = "Intel";               break;
				case BGFX_PCI_ID_NVIDIA:              items[ii] = "nVidia";              break;
				case BGFX_PCI_ID_MICROSOFT:           items[ii] = "Microsoft";           break;
				case BGFX_PCI_ID_ARM:                 items[ii] = "ARM";                 break;
				case BGFX_PCI_ID_SOFTWARE_RASTERIZER: items[ii] = "Software Rasterizer"; break;
				default:
					bx::snprintf(unknownVendor[ii], BX_COUNTOF(unknownVendor[ii]), "0x%04x", gpu.vendorId);
					items[ii] = unknownVendor[ii];
					break;
				}

				if (caps->vendorId == gpu.vendorId
				&&  caps->deviceId == gpu.deviceId)
				{
					current = ii;
				}
			}

			ImGui::TextUnformatted("GPU"); ImGui::SameLine(labelWidth);
			if (ImGui::Combo("##GPU", &current, items, numGPUs) )
			{
				newPciIdArg = getPciIdArg(caps->gpu[current].vendorId);
			}
		}
		ImGui::EndDisabled();

		ImGui::PopItemWidth();

		if (NULL != newRendererArg
		||  NULL != newPciIdArg)
		{
			const char* rendererArg = NULL != newRendererArg ? newRendererArg : getRendererArg(caps->rendererType);
			const char* pciIdArg    = NULL != newPciIdArg    ? newPciIdArg    : getPciIdArg(caps->vendorId);

			char args[64];
			bx::snprintf(args, BX_COUNTOF(args), "%s %s", rendererArg, pciIdArg);

			entry::setRestartArgs(args);
			cmdExec("app restart");
		}

		ImGui::Separator();
	}

	const bgfx::Stats* stats = bgfx::getStats();
	const double toMsCpu = 1000.0/stats->cpuTimerFreq;
	const double toMsGpu = 1000.0/stats->gpuTimerFreq;
	const double frameMs = double(stats->cpuTimeFrame)*toMsCpu;

	s_frameTime.pushSample(float(frameMs) );

	char frameTextOverlay[256];
	bx::snprintf(frameTextOverlay, BX_COUNTOF(frameTextOverlay), "%s%.3fms, %s%.3fms\nAvg: %.3fms, %.1f FPS"
		, ICON_FA_ARROW_DOWN
		, s_frameTime.m_min
		, ICON_FA_ARROW_UP
		, s_frameTime.m_max
		, s_frameTime.m_avg
		, 1000.0f/s_frameTime.m_avg
		);

	ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImColor(0.0f, 0.5f, 0.15f, 1.0f).Value);
	ImGui::PlotHistogram("Frame"
		, s_frameTime.m_values
		, SampleData::kNumSamples
		, s_frameTime.m_offset
		, frameTextOverlay
		, 0.0f
		, 60.0f
		, ImVec2(0.0f, 45.0f)
		);
	ImGui::PopStyleColor();

	ImGui::Text("Submit CPU %0.3f, GPU %0.3f (L: %d)"
		, double(stats->cpuTimeEnd - stats->cpuTimeBegin)*toMsCpu
		, double(stats->gpuTimeEnd - stats->gpuTimeBegin)*toMsGpu
		, stats->maxGpuLatency
		);

	if (-INT64_MAX != stats->gpuMemoryUsed)
	{
		char tmp0[64];
		bx::prettify(tmp0, BX_COUNTOF(tmp0), stats->gpuMemoryUsed);

		char tmp1[64];
		bx::prettify(tmp1, BX_COUNTOF(tmp1), stats->gpuMemoryMax);

		ImGui::Text("GPU mem: %s / %s", tmp0, tmp1);
	}

	if (s_showStats)
	{
		ImGui::SetNextWindowSize(
			  ImVec2(300.0f, 500.0f)
			, ImGuiCond_FirstUseEver
			);

		if (ImGui::Begin(ICON_FA_BAR_CHART " Stats", &s_showStats) )
		{
			if (ImGui::CollapsingHeader(ICON_FA_PUZZLE_PIECE " Resources") )
			{
				const float itemHeight = ImGui::GetTextLineHeightWithSpacing();
				const float maxWidth   = 90.0f;

				ImGui::PushFont(ImGui::Font::Mono);
				ImGui::Text("Res: Num  / Max");
				resourceBar("DIB", "Dynamic index buffers",  stats->numDynamicIndexBuffers,  caps->limits.maxDynamicIndexBuffers,  maxWidth, itemHeight);
				resourceBar("DVB", "Dynamic vertex buffers", stats->numDynamicVertexBuffers, caps->limits.maxDynamicVertexBuffers, maxWidth, itemHeight);
				resourceBar(" FB", "Frame buffers",          stats->numFrameBuffers,         caps->limits.maxFrameBuffers,         maxWidth, itemHeight);
				resourceBar(" IB", "Index buffers",          stats->numIndexBuffers,         caps->limits.maxIndexBuffers,         maxWidth, itemHeight);
				resourceBar(" OQ", "Occlusion queries",      stats->numOcclusionQueries,     caps->limits.maxOcclusionQueries,     maxWidth, itemHeight);
				resourceBar("  P", "Programs",               stats->numPrograms,             caps->limits.maxPrograms,             maxWidth, itemHeight);
				resourceBar("  S", "Shaders",                stats->numShaders,              caps->limits.maxShaders,              maxWidth, itemHeight);
				resourceBar("  T", "Textures",               stats->numTextures,             caps->limits.maxTextures,             maxWidth, itemHeight);
				resourceBar("  U", "Uniforms",               stats->numUniforms,             caps->limits.maxUniforms,             maxWidth, itemHeight);
				resourceBar(" VB", "Vertex buffers",         stats->numVertexBuffers,        caps->limits.maxVertexBuffers,        maxWidth, itemHeight);
				resourceBar(" VL", "Vertex layouts",         stats->numVertexLayouts,        caps->limits.maxVertexLayouts,        maxWidth, itemHeight);
				ImGui::PopFont();
			}

			if (ImGui::CollapsingHeader(ICON_FA_CLOCK_O " Profiler") )
			{
				if (0 == stats->numViews)
				{
					ImGui::Text("Profiler is not enabled.");
				}
				else
				{
					if (ImGui::BeginChild("##view_profiler", ImVec2(0.0f, 0.0f) ) )
					{
						ImGui::PushFont(ImGui::Font::Mono);

						ImVec4 cpuColor(0.5f, 1.0f, 0.5f, 1.0f);
						ImVec4 gpuColor(0.5f, 0.5f, 1.0f, 1.0f);

						const float itemHeight = ImGui::GetTextLineHeightWithSpacing();
						const float itemHeightWithSpacing = ImGui::GetFrameHeightWithSpacing();
						const double toCpuMs = 1000.0/double(stats->cpuTimerFreq);
						const double toGpuMs = 1000.0/double(stats->gpuTimerFreq);
						const float  scale   = 3.0f;

						if (ImGui::BeginListBox("Encoders", ImVec2(ImGui::GetWindowWidth(), stats->numEncoders*itemHeightWithSpacing) ) )
						{
							ImGuiListClipper clipper;
							clipper.Begin(stats->numEncoders, itemHeight);

							while (clipper.Step() )
							{
								for (int32_t pos = clipper.DisplayStart; pos < clipper.DisplayEnd; ++pos)
								{
									const bgfx::EncoderStats& encoderStats = stats->encoderStats[pos];

									ImGui::Text("%3d", pos);
									ImGui::SameLine(64.0f);

									const float maxWidth = 30.0f*scale;
									const float cpuMs    = float( (encoderStats.cpuTimeEnd-encoderStats.cpuTimeBegin)*toCpuMs);
									const float cpuWidth = bx::clamp(cpuMs*scale, 1.0f, maxWidth);

									if (bar("CPU", cpuWidth, maxWidth, itemHeight, cpuColor))
									{
										ImGui::SetTooltip("Encoder %d, CPU: %f [ms]"
											, pos
											, cpuMs
											);
									}
								}
							}

							ImGui::EndListBox();
						}

						ImGui::Separator();

						if (ImGui::BeginListBox("Views", ImVec2(ImGui::GetWindowWidth(), stats->numViews*itemHeightWithSpacing) ) )
						{
							ImGuiListClipper clipper;
							clipper.Begin(stats->numViews, itemHeight);

							while (clipper.Step() )
							{
								for (int32_t pos = clipper.DisplayStart; pos < clipper.DisplayEnd; ++pos)
								{
									const bgfx::ViewStats& viewStats = stats->viewStats[pos];

									ImGui::Text("%3d %3d %s", pos, viewStats.view, viewStats.name);

									const float maxWidth = 30.0f*scale;
									const float cpuTimeElapsed = float((viewStats.cpuTimeEnd - viewStats.cpuTimeBegin) * toCpuMs);
									const float gpuTimeElapsed = float((viewStats.gpuTimeEnd - viewStats.gpuTimeBegin) * toGpuMs);
									const float cpuWidth = bx::clamp(cpuTimeElapsed*scale, 1.0f, maxWidth);
									const float gpuWidth = bx::clamp(gpuTimeElapsed*scale, 1.0f, maxWidth);

									ImGui::SameLine(64.0f);

									ImGui::PushID(viewStats.name);

									if (bar("CPU", cpuWidth, maxWidth, itemHeight, cpuColor))
									{
										ImGui::SetTooltip("View %d \"%s\", CPU: %f [ms]"
											, pos
											, viewStats.name
											, cpuTimeElapsed
											);
									}

									ImGui::SameLine();
									if (bar("GPU", gpuWidth, maxWidth, itemHeight, gpuColor) )
									{
										ImGui::SetTooltip("View: %d \"%s\", GPU: %f [ms]"
											, pos
											, viewStats.name
											, gpuTimeElapsed
											);
									}

									ImGui::PopID();
								}
							}

							ImGui::EndListBox();
						}

						ImGui::PopFont();
					}

					ImGui::EndChild();
				}
			}
		}
		ImGui::End();
	}

	ImGui::End();
}
