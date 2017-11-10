/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "imgui/imgui.h"
#include "entry/entry.h"
#include "entry/cmd.h"
#include <bx/string.h>
#include <bx/timer.h>
#include <bx/math.h>

static bool bar(float _width, float _maxWidth, float _height, const ImVec4& _color)
{
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

	ImGui::Button("", ImVec2(_width, _height) );
	itemHovered |= ImGui::IsItemHovered();

	ImGui::SameLine();
	ImGui::InvisibleButton("", ImVec2(_maxWidth-_width, _height) );
	itemHovered |= ImGui::IsItemHovered();

	ImGui::PopStyleVar(2);
	ImGui::PopStyleColor(3);

	return itemHovered;
}

void showExampleDialog(entry::AppI* _app, const char* _errorText)
{
	char temp[1024];
	bx::snprintf(temp, BX_COUNTOF(temp), "Example: %s", _app->getName() );

	ImGui::SetNextWindowPos(
		  ImVec2(10.0f, 50.0f)
		, ImGuiSetCond_FirstUseEver
		);
	ImGui::Begin(temp
		, NULL
		, ImVec2(256.0f, 200.0f)
		);

	ImGui::TextWrapped("%s", _app->getDescription() );
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
		const char** items = (const char**)alloca(num*sizeof(void*) );

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

		ImGui::PopStyleVar();
	}

#if 0
	{
		bgfx::RendererType::Enum supportedRenderers[bgfx::RendererType::Count];
		uint8_t num = bgfx::getSupportedRenderers(BX_COUNTOF(supportedRenderers), supportedRenderers);

		const bgfx::Caps* caps = bgfx::getCaps();

		const char* items[bgfx::RendererType::Count];

		int32_t current = 0;
		for (uint8_t ii = 0; ii < num; ++ii)
		{
			items[ii] = bgfx::getRendererName(supportedRenderers[ii]);
			if (supportedRenderers[ii] == caps->rendererType)
			{
				current = ii;
			}
		}

		if (ImGui::Combo("Renderer", &current, items, num) )
		{
			cmdExec("app restart");
		}

		num = caps->numGPUs;
		if (0 != num)
		{
			current = 0;
			for (uint8_t ii = 0; ii < num; ++ii)
			{
				const bgfx::Caps::GPU& gpu = caps->gpu[ii];

				items[ii] = gpu.vendorId == BGFX_PCI_ID_AMD    ? "AMD"
						  : gpu.vendorId == BGFX_PCI_ID_INTEL  ? "Intel"
						  : gpu.vendorId == BGFX_PCI_ID_NVIDIA ? "nVidia"
						  : "Unknown?"
						  ;

				if (caps->vendorId == gpu.vendorId
				&&  caps->deviceId == gpu.deviceId)
				{
					current = ii;
				}
			}

			if (ImGui::Combo("GPU", &current, items, num) )
			{
				cmdExec("app restart");
			}
		}
	}
#endif // 0

	const bgfx::Stats* stats = bgfx::getStats();
	const double toMsCpu = 1000.0/stats->cpuTimerFreq;
	const double toMsGpu = 1000.0/stats->gpuTimerFreq;
	ImGui::Text("Frame %0.3f"
		, double(stats->cpuTimeFrame)*toMsCpu
		);

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

	if (0 != stats->numViews)
	{
		if (ImGui::CollapsingHeader(ICON_FA_CLOCK_O " Profiler") )
		{
			if (ImGui::BeginChild("##view_profiler", ImVec2(0.0f, 0.0f) ) )
			{
				ImGui::PushFont(ImGui::Font::Mono);

				ImVec4 cpuColor(0.5f, 1.0f, 0.5f, 1.0f);
				ImVec4 gpuColor(0.5f, 0.5f, 1.0f, 1.0f);

				const float itemHeight = ImGui::GetTextLineHeightWithSpacing();
				const float itemHeightWithSpacing = ImGui::GetItemsLineHeightWithSpacing();
				const double toCpuMs = 1000.0/double(stats->cpuTimerFreq);
				const double toGpuMs = 1000.0/double(stats->gpuTimerFreq);
				const float  scale   = 3.0f;

				if (ImGui::ListBoxHeader("Encoders", ImVec2(ImGui::GetWindowWidth(), stats->numEncoders*itemHeightWithSpacing) ) )
				{
					ImGuiListClipper clipper(stats->numEncoders, itemHeight);

					while (clipper.Step() )
					{
						for (int32_t pos = clipper.DisplayStart; pos < clipper.DisplayEnd; ++pos)
						{
							const bgfx::EncoderStats& encoderStats = stats->encoderStats[pos];

							ImGui::Text("%3d", pos);
							ImGui::SameLine(64.0f);

							const float maxWidth = 30.0f*scale;
							const float cpuMs    = float( (encoderStats.cpuTimeEnd-encoderStats.cpuTimeBegin)*toCpuMs);
							const float cpuWidth = bx::fclamp(cpuMs*scale, 1.0f, maxWidth);

							if (bar(cpuWidth, maxWidth, itemHeight, cpuColor) )
							{
								ImGui::SetTooltip("Encoder %d, CPU: %f [ms]"
									, pos
									, cpuMs
									);
							}
						}
					}

					ImGui::ListBoxFooter();
				}

				ImGui::Separator();

				if (ImGui::ListBoxHeader("Views", ImVec2(ImGui::GetWindowWidth(), stats->numViews*itemHeightWithSpacing) ) )
				{
					ImGuiListClipper clipper(stats->numViews, itemHeight);

					while (clipper.Step() )
					{
						for (int32_t pos = clipper.DisplayStart; pos < clipper.DisplayEnd; ++pos)
						{
							const bgfx::ViewStats& viewStats = stats->viewStats[pos];

							ImGui::Text("%3d %3d %s", pos, viewStats.view, viewStats.name);

							const float maxWidth = 30.0f*scale;
							const float cpuWidth = bx::fclamp(float(viewStats.cpuTimeElapsed*toCpuMs)*scale, 1.0f, maxWidth);
							const float gpuWidth = bx::fclamp(float(viewStats.gpuTimeElapsed*toGpuMs)*scale, 1.0f, maxWidth);

							ImGui::SameLine(64.0f);

							if (bar(cpuWidth, maxWidth, itemHeight, cpuColor) )
							{
								ImGui::SetTooltip("View %d \"%s\", CPU: %f [ms]"
									, pos
									, viewStats.name
									, viewStats.cpuTimeElapsed*toCpuMs
									);
							}

							ImGui::SameLine();
							if (bar(gpuWidth, maxWidth, itemHeight, gpuColor) )
							{
								ImGui::SetTooltip("View: %d \"%s\", GPU: %f [ms]"
									, pos
									, viewStats.name
									, viewStats.gpuTimeElapsed*toGpuMs
									);
							}
						}
					}

					ImGui::ListBoxFooter();
				}

				ImGui::PopFont();
			}

			ImGui::EndChild();
		}
	}

	ImGui::End();
}
