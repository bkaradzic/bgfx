namespace ImGui
{
	#define PI 3.14159265358979323846264338327f

	inline float fclamp(float a, float _min, float _max) 
	{ 
		return a < _min ? _min : (a > _max ? _max : a);
	}
	inline float fclamp01(float _a)
	{ 
		return fclamp(_a, 0.0f, 1.0f);
	}

	inline float fmin(float _a, float _b)
	{
		return _a < _b ? _a : _b;
	}

	inline float fmin3(float _a, float _b, float _c)
	{
		return fmin(_a, fmin(_b, _c) );
	}

	static float hue(float h, float m1, float m2)
	{
		if (h < 0) h += 1;
		if (h > 1) h -= 1;
		if (h < 1.0f/6.0f)
			return m1 + (m2 - m1) * h * 6.0f;
		else if (h < 3.0f/6.0f)
			return m2;
		else if (h < 4.0f/6.0f)
			return m1 + (m2 - m1) * (2.0f/3.0f - h) * 6.0f;
		return m1;
	}

	static void ColorConvertHSLtoRGB(float h, float s, float l, float& out_r, float& out_g, float& out_b)
	{
		float m1, m2;
		h = fmodf(h, 1.0f);
		if (h < 0.0f) h += 1.0f;
		s = fclamp01(s);
		l = fclamp01(l);
		m2 = l <= 0.5f ? (l * (1 + s)) : (l + s - l * s);
		m1 = 2 * l - m2;
		out_r = fclamp01(hue(h + 1.0f/3.0f, m1, m2));
		out_g = fclamp01(hue(h, m1, m2));
		out_b = fclamp01(hue(h - 1.0f/3.0f, m1, m2));
	}

	inline float vec2Dot(const float* __restrict _a, const float* __restrict _b)
	{
		return _a[0]*_b[0] + _a[1]*_b[1];
	}

	static void barycentric(float& _u, float& _v, float& _w
		, float _ax, float _ay
		, float _bx, float _by
		, float _cx, float _cy
		, float _px, float _py
		)
	{
		const float v0[2] = { _bx - _ax, _by - _ay };
		const float v1[2] = { _cx - _ax, _cy - _ay };
		const float v2[2] = { _px - _ax, _py - _ay };
		const float d00 = vec2Dot(v0, v0);
		const float d01 = vec2Dot(v0, v1);
		const float d11 = vec2Dot(v1, v1);
		const float d20 = vec2Dot(v2, v0);
		const float d21 = vec2Dot(v2, v1);
		const float denom = d00 * d11 - d01 * d01;
		_v = (d11 * d20 - d01 * d21) / denom;
		_w = (d00 * d21 - d01 * d20) / denom;
		_u = 1.0f - _v - _w;
	}

	static float sign(float px, float py, float ax, float ay, float bx, float by)
	{
		return (px - bx) * (ay - by) - (ax - bx) * (py - by);
	}

	static bool pointInTriangle(float px, float py, float ax, float ay, float bx, float by, float cx, float cy)
	{
		const bool b1 = sign(px, py, ax, ay, bx, by) < 0.0f;
		const bool b2 = sign(px, py, bx, by, cx, cy) < 0.0f;
		const bool b3 = sign(px, py, cx, cy, ax, ay) < 0.0f;

		return ( (b1 == b2) && (b2 == b3) );
	}

	static void closestPointOnLine(float& ox, float &oy, float px, float py, float ax, float ay, float bx, float by)
	{
		float dx = px - ax;
		float dy = py - ay;

		float lx = bx - ax;
		float ly = by - ay;

		float len = sqrtf(lx*lx+ly*ly);

		// Normalize.
		float invLen = 1.0f/len;
		lx*=invLen;
		ly*=invLen;

		float dot = (dx*lx + dy*ly);

		if (dot < 0.0f)
		{
			ox = ax;
			oy = ay;
		}
		else if (dot > len)
		{
			ox = bx;
			oy = by;
		}
		else
		{
			ox = ax + lx*dot;
			oy = ay + ly*dot;
		}
	}

	static void closestPointOnTriangle(float& ox, float &oy, float px, float py, float ax, float ay, float bx, float by, float cx, float cy)
	{
		float abx, aby;
		float bcx, bcy;
		float cax, cay;
		closestPointOnLine(abx, aby, px, py, ax, ay, bx, by);
		closestPointOnLine(bcx, bcy, px, py, bx, by, cx, cy);
		closestPointOnLine(cax, cay, px, py, cx, cy, ax, ay);

		const float pabx = px - abx;
		const float paby = py - aby;
		const float pbcx = px - bcx;
		const float pbcy = py - bcy;
		const float pcax = px - cax;
		const float pcay = py - cay;

		const float lab = sqrtf(pabx*pabx+paby*paby);
		const float lbc = sqrtf(pbcx*pbcx+pbcy*pbcy);
		const float lca = sqrtf(pcax*pcax+pcay*pcay);

		const float m = fmin3(lab, lbc, lca);
		if (m == lab)
		{
			ox = abx;
			oy = aby;
		}
		else if (m == lbc)
		{
			ox = bcx;
			oy = bcy;
		}
		else// if (m == lca).
		{
			ox = cax;
			oy = cay;
		}
	}


	void ColorWheel(float _rgb[3], float _size)
	{
		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems)
			return;

		ImGuiContext& g = *GImGui;
		ImGuiStyle& style = ImGui::GetStyle();
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		const float w = GetContentRegionAvailWidth();

		const ImGuiID wheelId = window->GetID("wheel");
		const ImGuiID triangleId = window->GetID("triangle");

		const float width = w * _size;
		const float xx = window->DC.CursorPos.x + w*0.5f;
		const float yy = window->DC.CursorPos.y + width*0.5f;
		const float center[2] = { xx, yy };

		const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(width, width + style.FramePadding.y*2.0f));

		ItemSize(frame_bb, style.FramePadding.y);

		const float ro = width*0.5f - 5.0f; // radiusOuter.
		const float rd = _size * 25.0f; // radiusDelta.
		const float ri = ro - rd; // radiusInner.
		const float aeps = 0.5f / ro; // Half a pixel arc length in radians (2pi cancels out).
		const float cmx = g.IO.MousePos.x - center[0];
		const float cmy = g.IO.MousePos.y - center[1];

		const float aa[2] = { ri - 6.0f, 0.0f }; // Hue point.
		const float bb[2] = { cosf(-120.0f/180.0f*PI) * aa[0], sinf(-120.0f/180.0f*PI) * aa[0] }; // Black point.
		const float cc[2] = { cosf( 120.0f/180.0f*PI) * aa[0], sinf( 120.0f/180.0f*PI) * aa[0] }; // White point.

		const float ca[2] = { aa[0] - cc[0], aa[1] - cc[1] };
		const float lenCa = sqrtf(ca[0]*ca[0]+ca[1]*ca[1]);
		const float invLenCa = 1.0f/lenCa;
		const float dirCa[2] = { ca[0]*invLenCa, ca[1]*invLenCa };

		float sel[2];

		float hsv[3];
		ColorConvertRGBtoHSV(_rgb[0], _rgb[1], _rgb[2], hsv[0], hsv[1], hsv[2]);

		if (g.IO.MouseClicked[0])
		{
			const float len = sqrtf(cmx*cmx + cmy*cmy);
			if (len > ri)
			{
				if (len < ro)
				{
					SetActiveID(wheelId, window);
				}
			}
			else
			{
				SetActiveID(triangleId, window);
			}
		}

		if (g.IO.MouseReleased[0]
		&& (g.ActiveId == wheelId || g.ActiveId == triangleId ) )
		{
			ClearActiveID();
		}

		// Set hue.
		if (g.IO.MouseDown[0]
		&&  g.ActiveId == wheelId )
		{
			hsv[0] = atan2f(cmy, cmx)/PI*0.5f;
			if (hsv[0] < 0.0f)
			{
				hsv[0]+=1.0f;
			}
		}

		if (g.IO.MouseDown[0]
		&&  g.ActiveId == triangleId )
		{
			float an = -hsv[0]*PI*2.0f;
			float tmx = (cmx*cosf(an)-cmy*sinf(an) );
			float tmy = (cmx*sinf(an)+cmy*cosf(an) );

			if (pointInTriangle(tmx, tmy, aa[0], aa[1], bb[0], bb[1], cc[0], cc[1]) )
			{
				sel[0] = tmx;
				sel[1] = tmy;
			}
			else
			{
				closestPointOnTriangle(sel[0], sel[1], tmx, tmy, aa[0], aa[1], bb[0], bb[1], cc[0], cc[1]);
			}
		}
		else
		{
			/*
			 *                  bb (black)
			 *                  /\
			 *                 /  \
			 *                /    \
			 *               /      \
			 *              /        \
			 *             /    .sel  \
			 *            /            \
			 *  cc(white)/____.ss_______\aa (hue)
			 */
			const float ss[2] =
			{
				cc[0] + dirCa[0]*lenCa*hsv[1],
				cc[1] + dirCa[1]*lenCa*hsv[1],
			};

			const float sb[2] = { bb[0]-ss[0], bb[1]-ss[1] };
			const float lenSb = sqrtf(sb[0]*sb[0]+sb[1]*sb[1]);
			const float invLenSb = 1.0f/lenSb;
			const float dirSb[2] = { sb[0]*invLenSb, sb[1]*invLenSb };

			sel[0] = cc[0] + dirCa[0]*lenCa*hsv[1] + dirSb[0]*lenSb*(1.0f - hsv[2]);
			sel[1] = cc[1] + dirCa[1]*lenCa*hsv[1] + dirSb[1]*lenSb*(1.0f - hsv[2]);
		}

		float uu, vv, ww;
		barycentric(uu, vv, ww
				  , aa[0],  aa[1]
				  , bb[0],  bb[1]
				  , cc[0],  cc[1]
				  , sel[0], sel[1]
				  );

		const float val = fclamp(1.0f-vv, 0.0001f, 1.0f);
		const float sat = fclamp(uu/val,  0.0001f, 1.0f);

		ColorConvertHSVtoRGB(hsv[0], sat, val, _rgb[0],  _rgb[1], _rgb[2]);

		// Draw widget.
		{
			float saturation = 1.0f;
			uint8_t alpha0 = 255;
			uint8_t alpha1 = 192;

			draw_list->PathClear();

			// Circle.
			for (uint32_t ii = 0; ii < 360; ii++)
			{
				const float a0 = float(ii)/360.0f      * 2.0f*PI - aeps;
				const float a1 = float(ii+1.0f)/360.0f * 2.0f*PI + aeps;
				draw_list->PathArcTo(ImVec2(center[0],center[1]), ri, a0, a1, 1);
				draw_list->PathArcTo(ImVec2(center[0],center[1]), ro, a1, a0, 1);

				ImVec4 color;
				ColorConvertHSLtoRGB(a0/PI*0.5f,saturation,0.55f, color.x, color.y, color.z);
				color.w = alpha0 * 255.0f;
				draw_list->PathFillConvex(ImGui::ColorConvertFloat4ToU32(color));
			}

			// Circle stroke.
			draw_list->AddCircle(ImVec2(center[0],center[1]), ri-0.5f, IM_COL32(0,0,0,64), 90);
			draw_list->AddCircle(ImVec2(center[0],center[1]), ro+0.5f, IM_COL32(0,0,0,64), 90);

			{
				float angleh = hsv[0]*PI*2.0f;
				float cosh = cosf(angleh);
				float sinh = sinf(angleh);
				ImVec2 points[4] = { { ri-1.0f, -3.0f } , { ri+rd+2.0f, -3.0f } ,  { ri+rd+2.0f, 3.0f } ,  { ri-1.0f, 3.0f } };

				//rotate points
				for(uint8_t ii = 0; ii<IM_ARRAYSIZE(points);++ii)
				{
					ImVec2 p = points[ii];
					points[ii].x = center[0] + cosh * p.x - sinh * p.y;
					points[ii].y = center[1] + sinh * p.x + cosh * p.y;
				}

				// Hue selector drop shadow.
				draw_list->AddPolyline(points,IM_ARRAYSIZE(points), IM_COL32(0,0,0,128), true, 3.0f, true);

				// Hue selector.
				draw_list->AddPolyline(points,IM_ARRAYSIZE(points), IM_COL32(255,255,255,alpha1), true, 2.0f, true);

				// Center triangle.
				points[0] = ImVec2(aa[0], aa[1]);
				points[1] = ImVec2(bb[0], bb[1]);
				points[2] = ImVec2(cc[0], cc[1]);

				//rotate points
				for(uint8_t ii = 0; ii<3;++ii)
				{
					ImVec2 p = points[ii];
					points[ii].x = center[0] + cosh * p.x - sinh * p.y;
					points[ii].y = center[1] + sinh * p.x + cosh * p.y;
				}

				draw_list->AddPolyline(points,3, IM_COL32(0,0,0,64), true, 1.0f, true);

				ImVec4 color;
				ColorConvertHSLtoRGB(hsv[0],saturation,0.5f, color.x, color.y, color.z);
				color.w = 255.0f;

				const ImVec2 uv = GImGui->FontTexUvWhitePixel;
				draw_list->PrimReserve(3, 3);
				draw_list->PrimWriteIdx((ImDrawIdx)(draw_list->_VtxCurrentIdx)); 
				draw_list->PrimWriteIdx((ImDrawIdx)(draw_list->_VtxCurrentIdx+1)); 
				draw_list->PrimWriteIdx((ImDrawIdx)(draw_list->_VtxCurrentIdx+2));
				draw_list->PrimWriteVtx(points[0], uv, ImGui::ColorConvertFloat4ToU32(color));
				draw_list->PrimWriteVtx(points[1], uv, IM_COL32(0,0,0,alpha0));
				draw_list->PrimWriteVtx(points[2], uv, IM_COL32(255,255,255,alpha0));

				ImVec2 psel = { center[0] + cosh * sel[0] - sinh * sel[1], center[1] + sinh * sel[0] + cosh * sel[1] };

				// Color selector drop shadow.
				draw_list->AddCircle(psel, 5.0f, IM_COL32(0, 0, 0, 64), 16, 4.0f);

				// Color selector.
				draw_list->AddCircle(psel, 5.0f, IM_COL32(255, 255, 255,alpha1), 16, 2.0f);
			}
		}
	}

	void ColorWheel(const char* _text, float* _rgba, float _size)
	{
		char buf[512];
		ImFormatString(buf, IM_ARRAYSIZE(buf), "%s [R %-2.2f G %-2.2f B %-2.2f A %-2.2f]##%s"
			, _text
			, _rgba[0]
			, _rgba[1]
			, _rgba[2]
			, _rgba[3]
			, _text
			);

		if (CollapsingHeader(buf, ImGuiTreeNodeFlags_DefaultOpen) )
		{
			ImGui::PushID(_text);
			ColorWheel(_rgba, _size);
			SliderFloat("Alpha", &_rgba[3], 0.0f, 1.0f);
			ImGui::PopID();
		}
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
