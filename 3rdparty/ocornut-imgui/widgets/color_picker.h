namespace ImGui
{
	bool ColorPicker4(float* col, bool show_alpha);
	bool ColorPicker3(float col[3]);

	inline bool ColorEdit4(const char* label, uint32_t* _rgba, bool show_alpha = true)
	{
		uint8_t* rgba = (uint8_t*)_rgba;
		float col[4] =
		{
			rgba[0]/255.0f,
			rgba[1]/255.0f,
			rgba[2]/255.0f,
			rgba[3]/255.0f,
		};
		bool result = ColorEdit4(label, col, show_alpha);
		rgba[0] = uint8_t(col[0]*255.0f);
		rgba[1] = uint8_t(col[1]*255.0f);
		rgba[2] = uint8_t(col[2]*255.0f);
		rgba[3] = uint8_t(col[3]*255.0f);
		return result;
	}

} // namespace ImGui
