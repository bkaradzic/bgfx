namespace ImGui
{
	void ColorWheel(const char* _text, float* _rgba, float _size)
	{
		(void)_size;
		ColorEdit4(_text
			, _rgba, 0
			| ImGuiColorEditFlags_PickerHueWheel
			| ImGuiColorEditFlags_Float
			);
	}

	inline void decodeRgba(float* _dst, const uint32_t* _src)
	{
		uint8_t* src = (uint8_t*)_src;
		_dst[0] = float(src[0] / 255.0f);
		_dst[1] = float(src[1] / 255.0f);
		_dst[2] = float(src[2] / 255.0f);
		_dst[3] = float(src[3] / 255.0f);
	}

	inline void encodeRgba(uint32_t* _dst, const float* _src)
	{
		uint8_t* dst = (uint8_t*)_dst;
		dst[0] = uint8_t(_src[0] * 255.0);
		dst[1] = uint8_t(_src[1] * 255.0);
		dst[2] = uint8_t(_src[2] * 255.0);
		dst[3] = uint8_t(_src[3] * 255.0);
	}

	void ColorWheel(const char* _text, uint32_t* _rgba, float _size)
	{
		float rgba[4];
		decodeRgba(rgba, _rgba);
		ColorWheel(_text, rgba, _size);
		encodeRgba(_rgba, rgba);
	}

} // namespace ImGui
