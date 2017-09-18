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
		, ImGuiWindowFlags_AlwaysAutoResize
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
	ImGui::Text("CPU %0.3f"
		, double(stats->cpuTimeEnd-stats->cpuTimeBegin)/stats->cpuTimerFreq*1000.0
		);

	ImGui::Text("GPU %0.3f (latency: %d)"
		, double(stats->gpuTimeEnd-stats->gpuTimeBegin)/stats->gpuTimerFreq*1000.0
		, stats->maxGpuLatency
		);

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

				if (ImGui::ListBoxHeader("##empty", ImVec2(ImGui::GetWindowWidth(), stats->numViews*itemHeight) ) )
				{
					ImGuiListClipper clipper(stats->numViews, itemHeight);

					const double toCpuMs = 1000.0/stats->cpuTimerFreq;
					const double toGpuMs = 1000.0/stats->gpuTimerFreq;
					const float  scale   = 3.0f;

					while (clipper.Step() )
					{
						for (int32_t pos = clipper.DisplayStart; pos < clipper.DisplayEnd; ++pos)
						{
							const bgfx::ViewStats& viewStats = stats->viewStats[pos];

							ImGui::Text("%3d %3d %s", pos, viewStats.view, viewStats.name);
							ImGui::SameLine(64.0f);

							ImGui::PushStyleColor(ImGuiCol_Button,        cpuColor);
							ImGui::PushStyleColor(ImGuiCol_ButtonHovered, cpuColor);
							ImGui::PushStyleColor(ImGuiCol_ButtonActive,  cpuColor);

							const float maxWidth = 30.0f*scale;
							const float cpuWidth = bx::fclamp(float(viewStats.cpuTimeElapsed*toCpuMs)*scale, 1.0f, maxWidth);
							const float gpuWidth = bx::fclamp(float(viewStats.gpuTimeElapsed*toGpuMs)*scale, 1.0f, maxWidth);

							ImGui::Button("", ImVec2(cpuWidth, itemHeight) );
							if (ImGui::IsItemHovered() )
							{
								ImGui::SetTooltip("CPU: %f [ms]", viewStats.cpuTimeElapsed*toCpuMs);
							}
							ImGui::PopStyleColor(3);
							ImGui::SameLine();

							ImGui::InvisibleButton("", ImVec2(maxWidth-cpuWidth, itemHeight) );
							ImGui::SameLine();

							ImGui::PushStyleColor(ImGuiCol_Button,        gpuColor);
							ImGui::PushStyleColor(ImGuiCol_ButtonHovered, gpuColor);
							ImGui::PushStyleColor(ImGuiCol_ButtonActive,  gpuColor);
							ImGui::Button("", ImVec2(gpuWidth, itemHeight) );
							if (ImGui::IsItemHovered() )
							{
								ImGui::SetTooltip("GPU: %f [ms]", viewStats.gpuTimeElapsed*toGpuMs);
							}
							ImGui::PopStyleColor(3);
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
