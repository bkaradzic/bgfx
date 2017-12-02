// https://github.com/ocornut/imgui/issues/346#issuecomment-171961296
// [src] https://github.com/ocornut/imgui/issues/346

namespace ImGui
{
	bool ColorPicker4(float* col, bool show_alpha)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		// Setup
		ImVec2 picker_pos = ImGui::GetCursorScreenPos();
		ImVec2 sv_picker_size = ImVec2(256.0f, 256.0f);                             // Saturation/Value picking box
		float bars_width = ImGui::GetFontSize() + style.FramePadding.y*2.0f;  // Width of Hue/Alpha picking bars (using Framepadding.y to match the ColorButton sides)
		float bar0_pos_x = picker_pos.x + sv_picker_size.x + style.ItemInnerSpacing.x;
		float bar1_pos_x = bar0_pos_x + bars_width + style.ItemInnerSpacing.x;

		float H,S,V;
		ImGui::ColorConvertRGBtoHSV(col[0], col[1], col[2], H, S, V);

		// Color matrix logic
		bool value_changed = false, hsv_changed = false;
		ImGui::BeginGroup();
		ImGui::InvisibleButton("sv", sv_picker_size);
		if (ImGui::IsItemActive())
		{
			S = ImSaturate((io.MousePos.x - picker_pos.x) / (sv_picker_size.x-1));
			V = 1.0f - ImSaturate((io.MousePos.y - picker_pos.y) / (sv_picker_size.y-1));
			value_changed = hsv_changed = true;
		}

		// Hue bar logic
		ImGui::SetCursorScreenPos(ImVec2(bar0_pos_x, picker_pos.y));
		ImGui::InvisibleButton("hue", ImVec2(bars_width, sv_picker_size.y));
		if (ImGui::IsItemActive())
		{
			H = ImSaturate((io.MousePos.y - picker_pos.y) / (sv_picker_size.y-1));
			value_changed = hsv_changed = true;
		}

		// Alpha bar logic
		if (show_alpha)
		{
			ImGui::SetCursorScreenPos(ImVec2(bar1_pos_x, picker_pos.y));
			ImGui::InvisibleButton("alpha", ImVec2(bars_width, sv_picker_size.y));
			if (ImGui::IsItemActive())
			{
				col[3] = 1.0f - ImSaturate((io.MousePos.y - picker_pos.y) / (sv_picker_size.y-1));
				value_changed = true;
			}
		}

		// Convert back to RGB
		if (hsv_changed)
			ImGui::ColorConvertHSVtoRGB(H >= 1.0f ? H - 10 * 1e-6f : H, S > 0.0f ? S : 10*1e-6f, V > 0.0f ? V : 1e-6f, col[0], col[1], col[2]);

		// R,G,B or H,S,V color editor
		ImGui::PushItemWidth((show_alpha ? bar1_pos_x : bar0_pos_x) + bars_width - picker_pos.x);
		value_changed |= show_alpha ? ImGui::ColorEdit4("##edit", col) : ImGui::ColorEdit3("##edit", col);
		ImGui::PopItemWidth();

		// Try to cancel hue wrap (after ColorEdit), if any
		if (value_changed)
		{
			float new_H, new_S, new_V;
			ImGui::ColorConvertRGBtoHSV(col[0], col[1], col[2], new_H, new_S, new_V);
			if (new_H <= 0 && H > 0) 
			{
				if (new_V <= 0 && V != new_V)
					ImGui::ColorConvertHSVtoRGB(H, S, new_V <= 0 ? V * 0.5f : new_V, col[0], col[1], col[2]);
				else if (new_S <= 0)
					ImGui::ColorConvertHSVtoRGB(H, new_S <= 0 ? S * 0.5f : new_S, new_V, col[0], col[1], col[2]);
			}
		}

		// Render hue bar
		ImU32 hue_colors[] = { IM_COL32(255,0,0,255), IM_COL32(255,255,0,255), IM_COL32(0,255,0,255), IM_COL32(0,255,255,255), IM_COL32(0,0,255,255), IM_COL32(255,0,255,255), IM_COL32(255,0,0,255) };
		for (int i = 0; i < 6; ++i)
		{
			draw_list->AddRectFilledMultiColor(
					ImVec2(bar0_pos_x, picker_pos.y + i * (sv_picker_size.y / 6)),
					ImVec2(bar0_pos_x + bars_width, picker_pos.y + (i + 1) * (sv_picker_size.y / 6)),
					hue_colors[i], hue_colors[i], hue_colors[i + 1], hue_colors[i + 1]);
		}
		float bar0_line_y = (float)(int)(picker_pos.y + H * sv_picker_size.y + 0.5f);
		draw_list->AddLine(ImVec2(bar0_pos_x - 1, bar0_line_y), ImVec2(bar0_pos_x + bars_width + 1, bar0_line_y), IM_COL32_WHITE);

		// Render alpha bar
		if (show_alpha)
		{
			float alpha = ImSaturate(col[3]);
			float bar1_line_y = (float)(int)(picker_pos.y + (1.0f-alpha) * sv_picker_size.y + 0.5f);
			draw_list->AddRectFilledMultiColor(ImVec2(bar1_pos_x, picker_pos.y), ImVec2(bar1_pos_x + bars_width, picker_pos.y + sv_picker_size.y), IM_COL32_WHITE, IM_COL32_WHITE, IM_COL32_BLACK, IM_COL32_BLACK);
			draw_list->AddLine(ImVec2(bar1_pos_x - 1, bar1_line_y), ImVec2(bar1_pos_x + bars_width + 1, bar1_line_y), IM_COL32_WHITE);
		}

		// Render color matrix
		ImVec4 hue_color_f(1, 1, 1, 1);
		ImGui::ColorConvertHSVtoRGB(H, 1, 1, hue_color_f.x, hue_color_f.y, hue_color_f.z);
		ImU32 hue_color32 = ImGui::ColorConvertFloat4ToU32(hue_color_f);
		draw_list->AddRectFilledMultiColor(picker_pos, picker_pos + sv_picker_size, IM_COL32_WHITE, hue_color32, hue_color32, IM_COL32_WHITE);
		draw_list->AddRectFilledMultiColor(picker_pos, picker_pos + sv_picker_size, IM_COL32_BLACK_TRANS, IM_COL32_BLACK_TRANS, IM_COL32_BLACK, IM_COL32_BLACK);

		// Render cross-hair
		const float CROSSHAIR_SIZE = 7.0f;
		ImVec2 p((float)(int)(picker_pos.x + S * sv_picker_size.x + 0.5f), (float)(int)(picker_pos.y + (1 - V) * sv_picker_size.y + 0.5f));
		draw_list->AddLine(ImVec2(p.x - CROSSHAIR_SIZE, p.y), ImVec2(p.x - 2, p.y), IM_COL32_WHITE);
		draw_list->AddLine(ImVec2(p.x + CROSSHAIR_SIZE, p.y), ImVec2(p.x + 2, p.y), IM_COL32_WHITE);
		draw_list->AddLine(ImVec2(p.x, p.y + CROSSHAIR_SIZE), ImVec2(p.x, p.y + 2), IM_COL32_WHITE);
		draw_list->AddLine(ImVec2(p.x, p.y - CROSSHAIR_SIZE), ImVec2(p.x, p.y - 2), IM_COL32_WHITE);
		ImGui::EndGroup();

		return value_changed;
	}

	bool ColorPicker3(float col[3])
	{
		return ColorPicker4(col, false);
	}

} // namespace ImGui
