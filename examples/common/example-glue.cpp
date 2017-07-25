/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "imgui/imgui.h"
#include "entry/entry.h"
#include "entry/cmd.h"
#include <bx/string.h>
#include <bx/timer.h>

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

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(3.0f, 3.0f) );

		if (ImGui::Button(ICON_FA_REPEAT " Restart" ) )
		{
			cmdExec("app restart");
		}

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

	ImGui::End();
}
