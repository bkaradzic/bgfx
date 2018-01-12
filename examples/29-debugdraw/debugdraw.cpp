/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"
#include <entry/cmd.h>
#include <entry/input.h>
#include <debugdraw/debugdraw.h>
#include "camera.h"
#include "imgui/imgui.h"

#include <bx/uint32_t.h>

namespace
{

static DdVertex s_bunnyVertices[] =
{
	{   25.0883,  -44.2788, 31.0055   },
	{  0.945623,   53.5504, -24.6146  },
	{  -0.94455,  -14.3443, -16.8223  },
	{  -20.1103,  -48.6664, 12.6763   },
	{  -1.60652,  -26.3165, -24.5424  },
	{  -30.6284,  -53.6299, 14.7666   },
	{   1.69145,  -43.8075, -15.2065  },
	{  -20.5139,   21.0521, -5.40868  },
	{  -13.9518,   53.6299, -39.1193  },
	{  -21.7912,   48.7801, -42.0995  },
	{  -26.8408,   23.6537, -17.7324  },
	{  -23.1196,   33.9692, 4.91483   },
	{  -12.3236,  -41.6303, 31.8324   },
	{   27.6427,  -5.05034, -11.3201  },
	{   32.2565,   1.30521, 30.2671   },
	{   47.2723,  -27.0974, 11.1774   },
	{    33.598,   10.5888, 7.95916   },
	{  -13.2898,   12.6234, 5.55953   },
	{  -32.7364,   19.0648, -10.5736  },
	{  -32.7536,   31.4158, -1.40712  },
	{  -25.3672,   30.2874, -12.4682  },
	{    32.921,  -36.8408, -12.0254  },
	{  -37.7251,  -33.8989, 0.378443  },
	{  -35.6341, -0.246891, -9.25165  },
	{  -16.7041,  -50.0254, -15.6177  },
	{   24.6604,  -53.5319, -11.1059  },
	{  -7.77574,  -53.5719, -16.6655  },
	{   20.6241,   13.3489, 0.376349  },
	{  -44.2889,   29.5222, 18.7918   },
	{   18.5805,   16.3651, 12.6351   },
	{  -23.7853,   31.7598, -6.54093  },
	{   24.7518,  -53.5075, 2.14984   },
	{  -45.7912,  -17.6301, 21.1198   },
	{   51.8403,  -33.1847, 24.3337   },
	{  -47.5343,  -4.32792, 4.06232   },
	{  -50.6832,   -12.442, 11.0994   },
	{  -49.5132,   19.2782, 3.17559   },
	{  -39.4881,   29.0208, -6.70431  },
	{  -52.7286,   1.23232, 9.74872   },
	{    26.505,  -16.1297, -17.0487  },
	{   -25.367,   20.0473, -8.44282  },
	{  -24.5797,  -10.3143, -18.3154  },
	{  -28.6707,   6.12074, 27.8025   },
	{  -16.9868,   22.6819, 1.37408   },
	{  -37.2678,   23.9443, -9.4945   },
	{  -24.8562,   21.3763, 18.8847   },
	{  -47.1879,    3.8542, -4.74621  },
	{   38.0706,  -7.33673, -7.6099   },
	{  -34.8833,  -3.57074, 26.4838   },
	{   12.3797,   5.46782, 32.9762   },
	{  -31.5974,   -22.956, 30.5827   },
	{  -6.80953,    48.055, -18.5116  },
	{    6.3474,  -15.1622, -24.4726  },
	{  -25.5733,   25.2452, -34.4736  },
	{  -23.8955,   31.8323, -40.8696  },
	{  -11.8622,   38.2304, -43.3125  },
	{  -20.4918,   41.2409, -3.11271  },
	{   24.9806,  -8.53455, 37.2862   },
	{  -52.8935,    5.3376, 28.246    },
	{    34.106,  -41.7941, 30.962    },
	{  -1.26914,   35.6664, -18.7177  },
	{  -0.13048,   44.7288, -28.7163  },
	{   2.47929,  0.678165, -14.6892  },
	{  -31.8649,  -14.2299, 32.2998   },
	{   -19.774,   30.8258, 5.77293   },
	{   49.8059,   -37.125, 4.97284   },
	{  -28.0581,   -26.439, -14.8316  },
	{  -9.12066,  -27.3987, -12.8592  },
	{  -13.8752,  -29.9821, 32.5962   },
	{   -6.6222,  -10.9884, 33.5007   },
	{  -21.2664,  -53.6089, -3.49195  },
	{ -0.628672,   52.8093, -9.88088  },
	{   8.02417,   51.8956, -21.5834  },
	{  -44.6547,   11.9973, 34.7897   },
	{  -7.55466,   37.9035, -0.574101 },
	{   52.8252,  -27.1986, 11.6429   },
	{ -0.934591,   9.81861, 0.512566  },
	{  -3.01043,   5.70605, 22.0954   },
	{  -34.6337,   44.5964, -31.1713  },
	{  -26.9017,   35.1991, -32.4307  },
	{   15.9884,  -8.92223, -14.7411  },
	{  -22.8337,   -43.458, 26.7274   },
	{  -31.9864,  -47.0243, 9.36972   },
	{  -36.9436,   24.1866, 29.2521   },
	{  -26.5411,   29.6549, 21.2867   },
	{   33.7644,  -24.1886, -13.8513  },
	{  -2.44749,  -17.0148, 41.6617   },
	{   -38.364,  -13.9823, -12.5705  },
	{  -10.2972,  -51.6584, 38.935    },
	{   1.28109,  -43.4943, 36.6288   },
	{  -19.7784,  -44.0413, -4.23994  },
	{   37.0944,  -53.5479, 27.6467   },
	{   24.9642,  -37.1722, 35.7038   },
	{   37.5851,   5.64874, 21.6702   },
	{  -17.4738,  -53.5734, 30.0664   },
	{  -8.93088,   45.3429, -34.4441  },
	{  -17.7111,   -6.5723, 29.5162   },
	{   44.0059,  -17.4408, -5.08686  },
	{  -46.2534,  -22.6115, 0.702059  },
	{   43.9321,  -33.8575, 4.31819   },
	{   41.6762,  -7.37115, 27.6798   },
	{   8.20276,  -42.0948, -18.0893  },
	{   26.2678,  -44.6777, -10.6835  },
	{    17.709,   13.1542, 25.1769   },
	{  -35.9897,   3.92007, 35.8198   },
	{  -23.9323,  -37.3142, -2.39396  },
	{   5.19169,   46.8851, -28.7587  },
	{  -37.3072,  -35.0484, 16.9719   },
	{   45.0639,  -28.5255, 22.3465   },
	{  -34.4175,   35.5861, -21.7562  },
	{   9.32684,  -12.6655, 42.189    },
	{   1.00938,  -31.7694, 43.1914   },
	{  -45.4666,  -3.71104, 19.2248   },
	{  -28.7999,  -50.8481, 31.5232   },
	{   35.2212,  -45.9047, 0.199736  },
	{      40.3,  -53.5889, 7.47622   },
	{   29.0515,    5.1074, -10.002   },
	{   13.4336,   4.84341, -9.72327  },
	{   11.0617,   -26.245, -24.9471  },
	{  -35.6056,  -51.2531, 0.436527  },
	{  -10.6863,   34.7374, -36.7452  },
	{  -51.7652,   27.4957, 7.79363   },
	{  -50.1898,    18.379, 26.3763   },
	{  -49.6836,  -1.32722, 26.2828   },
	{   19.0363,  -16.9114, 41.8511   },
	{   32.7141,   -21.501, 36.0025   },
	{   12.5418,  -28.4244, 43.3125   },
	{  -19.5634,   42.6328, -27.0687  },
	{  -16.1942,   6.55011, 19.4066   },
	{   46.9886,  -18.8482, 22.1332   },
	{   45.9697,  -3.76781, 4.10111   },
	{  -28.2912,   51.3277, -35.1815  },
	{  -40.2796,  -27.7518, 22.8684   },
	{  -22.7984,  -38.9977, 22.158    },
	{   54.0614,  -35.6096, 12.694    },
	{   44.2064,  -53.6029, 18.8679   },
	{    19.789,   -29.517, -19.6094  },
	{  -34.3769,   34.8566, 9.92517   },
	{  -23.7518,  -45.0319, 8.71282   },
	{  -12.7978,   3.55087, -13.7108  },
	{  -54.0614,   8.83831, 8.91353   },
	{   16.2986,  -53.5717, 34.065    },
	{  -36.6243,  -53.5079, 24.6495   },
	{   16.5794,  -48.5747, 35.5681   },
	{  -32.3263,   41.4526, -18.7388  },
	{  -18.8488,   9.62627, -8.81052  },
	{   5.35849,   36.3616, -12.9346  },
	{   6.19167,    34.497, -17.965   },
};

static const uint16_t s_bunnyTriList[] =
{
	 80,   2,  52,
	  0, 143,  92,
	 51,   1,  71,
	 96, 128,  77,
	 67,   2,  41,
	 85,  39,  52,
	 58, 123,  38,
	 99,  21, 114,
	 55,   9,  54,
	136, 102,  21,
	  3, 133,  81,
	101, 136,   4,
	  5,  82,   3,
	  6,  90,  24,
	  7,  40, 145,
	 33,  75, 134,
	 55,   8,   9,
	 10,  40,  20,
	 46, 140,  38,
	 74,  64,  11,
	 89,  88,  12,
	147,  60,   7,
	 47, 116,  13,
	 59, 129, 108,
	147,  72, 106,
	 33, 108,  75,
	100,  57,  14,
	129, 130,  15,
	 32,  35, 112,
	 16,  29,  27,
	107,  98, 132,
	130, 116,  47,
	 17,  43,   7,
	 54,  44,  53,
	 46,  34,  23,
	 87,  41,  23,
	 40,  10,  18,
	  8, 131,   9,
	 11,  19,  56,
	 11, 137,  19,
	 19,  20,  30,
	 28, 121, 137,
	122, 140,  36,
	 15, 130,  97,
	 28,  84,  83,
	114,  21, 102,
	 87,  98,  22,
	 41, 145,  23,
	133,  68,  12,
	 90,  70,  24,
	 31,  25,  26,
	 98,  34,  35,
	 16,  27, 116,
	 28,  83, 122,
	 29, 103,  77,
	 40,  30,  20,
	 14,  49, 103,
	 31,  26, 142,
	 78,   9, 131,
	 80,  62,   2,
	  6,  67, 105,
	 32,  48,  63,
	 60,  30,   7,
	 33, 135,  91,
	116, 130,  16,
	 47,  13,  39,
	 70, 119,   5,
	 24,  26,   6,
	102,  25,  31,
	103,  49,  77,
	 16, 130,  93,
	125, 126, 124,
	111,  86, 110,
	  4,  52,   2,
	 87,  34,  98,
	  4,   6, 101,
	 29,  76,  27,
	112,  35,  34,
	  6,   4,  67,
	 72,   1, 106,
	 26,  24,  70,
	 36,  37, 121,
	 81, 113, 142,
	 44, 109,  37,
	122,  58,  38,
	 96,  48, 128,
	 71,  11,  56,
	 73, 122,  83,
	 52,  39,  80,
	 40,  18, 145,
	 82,   5, 119,
	 10,  20, 120,
	139, 145,  41,
	  3, 142,   5,
	 76, 117,  27,
	 95, 120,  20,
	104,  45,  42,
	128,  43,  17,
	 44,  37,  36,
	128,  45,  64,
	143, 111, 126,
	 34,  46,  38,
	 97, 130,  47,
	142,  91, 115,
	114,  31, 115,
	125, 100, 129,
	 48,  96,  63,
	 62,  41,   2,
	 69,  77,  49,
	133,  50,  68,
	 60,  51,  30,
	  4, 118,  52,
	 53,  55,  54,
	 95,   8,  55,
	121,  37,  19,
	 65,  75,  99,
	 51,  56,  30,
	 14,  57, 110,
	 58, 122,  73,
	 59,  92, 125,
	 42,  45, 128,
	 49,  14, 110,
	 60, 147,  61,
	 76,  62, 117,
	 69,  49,  86,
	 26,   5, 142,
	 46,  44,  36,
	 63,  50, 132,
	128,  64,  43,
	 75, 108,  15,
	134,  75,  65,
	 68,  69,  86,
	 62,  76, 145,
	142, 141,  91,
	 67,  66, 105,
	 69,  68,  96,
	119,  70,  90,
	 33,  91, 108,
	136, 118,   4,
	 56,  51,  71,
	  1,  72,  71,
	 23,  18,  44,
	104, 123,  73,
	106,   1,  61,
	 86, 111,  68,
	 83,  45, 104,
	 30,  56,  19,
	 15,  97,  99,
	 71,  74,  11,
	 15,  99,  75,
	 25, 102,   6,
	 12,  94,  81,
	135,  33, 134,
	138, 133,   3,
	 76,  29,  77,
	 94,  88, 141,
	115,  31, 142,
	 36, 121, 122,
	  4,   2,  67,
	  9,  78,  79,
	137, 121,  19,
	 69,  96,  77,
	 13,  62,  80,
	  8, 127, 131,
	143, 141,  89,
	133,  12,  81,
	 82, 119, 138,
	 45,  83,  84,
	 21,  85, 136,
	126, 110, 124,
	 86,  49, 110,
	 13, 116, 117,
	 22,  66,  87,
	141,  88,  89,
	 64,  45,  84,
	 79,  78, 109,
	 26,  70,   5,
	 14,  93, 100,
	 68,  50,  63,
	 90, 105, 138,
	141,   0,  91,
	105,  90,   6,
	  0,  92,  59,
	 17, 145,  76,
	 29,  93, 103,
	113,  81,  94,
	 39,  85,  47,
	132,  35,  32,
	128,  48,  42,
	 93,  29,  16,
	145,  18,  23,
	108, 129,  15,
	 32, 112,  48,
	 66,  41,  87,
	120,  95,  55,
	 96,  68,  63,
	 85,  99,  97,
	 18,  53,  44,
	 22,  98, 107,
	 98,  35, 132,
	 95, 127,   8,
	137,  64,  84,
	 18,  10,  53,
	 21,  99,  85,
	 54,  79,  44,
	100,  93, 130,
	142,   3,  81,
	102, 101,   6,
	 93,  14, 103,
	 42,  48, 104,
	 87,  23,  34,
	 66,  22, 105,
	106,  61, 147,
	 72,  74,  71,
	109, 144,  37,
	115,  65,  99,
	107, 132, 133,
	 94,  12,  88,
	108,  91,  59,
	 43,  64,  74,
	109,  78, 144,
	 43, 147,   7,
	 91, 135, 115,
	111, 110, 126,
	 38, 112,  34,
	142, 113,  94,
	 54,   9,  79,
	120,  53,  10,
	138,   3,  82,
	114, 102,  31,
	134,  65, 115,
	105,  22, 107,
	125, 129,  59,
	 37, 144,  19,
	 17,  76,  77,
	 89,  12, 111,
	 41,  66,  67,
	 13, 117,  62,
	116,  27, 117,
	136,  52, 118,
	 51,  60,  61,
	138, 119,  90,
	 53, 120,  55,
	 68, 111,  12,
	122, 121,  28,
	123,  58,  73,
	110,  57, 124,
	 47,  85,  97,
	 44,  79, 109,
	126, 125,  92,
	 43,  74, 146,
	 20,  19, 127,
	128,  17,  77,
	 72, 146,  74,
	115,  99, 114,
	140, 122,  38,
	133, 105, 107,
	129, 100, 130,
	131, 144,  78,
	 95,  20, 127,
	123,  48, 112,
	102, 136, 101,
	 89, 111, 143,
	 28, 137,  84,
	133, 132,  50,
	125,  57, 100,
	 38, 123, 112,
	124,  57, 125,
	135, 134, 115,
	 23,  44,  46,
	136,  85,  52,
	 41,  62, 139,
	137,  11,  64,
	104,  48, 123,
	133, 138, 105,
	145, 139,  62,
	 25,   6,  26,
	  7,  30,  40,
	 46,  36, 140,
	141, 143,   0,
	132,  32,  63,
	 83, 104,  73,
	 19, 144, 127,
	142,  94, 141,
	 39,  13,  80,
	 92, 143, 126,
	127, 144, 131,
	 51,  61,   1,
	 91,   0,  59,
	 17,   7, 145,
	 43, 146, 147,
	146,  72, 147,
};

void imageCheckerboard(void* _dst, uint32_t _width, uint32_t _height, uint32_t _step, uint32_t _0, uint32_t _1)
{
	uint32_t* dst = (uint32_t*)_dst;
	for (uint32_t yy = 0; yy < _height; ++yy)
	{
		for (uint32_t xx = 0; xx < _width; ++xx)
		{
			uint32_t abgr = ( (xx/_step)&1) ^ ( (yy/_step)&1) ? _1 : _0;
			*dst++ = abgr;
		}
	}
}

class ExampleDebugDraw : public entry::AppI
{
public:
	ExampleDebugDraw(const char* _name, const char* _description)
		: entry::AppI(_name, _description)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		Args args(_argc, _argv);

		m_width  = _width;
		m_height = _height;
		m_debug  = BGFX_DEBUG_NONE;
		m_reset  = BGFX_RESET_VSYNC | BGFX_RESET_MSAA_X16;

		bgfx::init(args.m_type, args.m_pciId);
		bgfx::reset(m_width, m_height, m_reset);

		// Enable m_debug text.
		bgfx::setDebug(m_debug);

		// Set view 0 clear state.
		bgfx::setViewClear(0
				, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
				, 0x303030ff
				, 1.0f
				, 0
				);

		m_timeOffset = bx::getHPCounter();

		cameraCreate();

		const float initialPos[3] = { 0.0f, 2.0f, -12.0f };
		cameraSetPosition(initialPos);
		cameraSetVerticalAngle(0.0f);

		ddInit();

		uint8_t data[32*32*4];
		imageCheckerboard(data, 32, 32, 4, 0xff808080, 0xffc0c0c0);

		m_sprite = ddCreateSprite(32, 32, data);
		m_bunny  = ddCreateGeometry(
			  BX_COUNTOF(s_bunnyVertices)
			, s_bunnyVertices
			, BX_COUNTOF(s_bunnyTriList)
			, s_bunnyTriList
			);

		imguiCreate();
	}

	virtual int shutdown() override
	{
		imguiDestroy();

		ddDestroy(m_bunny);
		ddDestroy(m_sprite);

		ddShutdown();

		cameraDestroy();

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	template<typename Ty>
	bool intersect(const Ray& _ray, const Ty& _shape)
	{
		Hit hit;
		if (::intersect(_ray, _shape, &hit) )
		{
			ddPush();

			ddSetWireframe(false);

			ddSetColor(0xff0000ff);

			float tmp[3];
			bx::vec3Mul(tmp, hit.m_normal, 0.7f);

			float end[3];
			bx::vec3Add(end, hit.m_pos, tmp);

			ddDrawCone(hit.m_pos, end, 0.1f);

			ddPop();

			return true;
		}

		return false;
	}

	bool update() override
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			imguiBeginFrame(
				   m_mouseState.m_mx
				,  m_mouseState.m_my
				, (m_mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT   : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT  : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
				,  m_mouseState.m_mz
				, uint16_t(m_width)
				, uint16_t(m_height)
				);

			showExampleDialog(this);

			imguiEndFrame();

			int64_t now = bx::getHPCounter() - m_timeOffset;
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency() );
			const float deltaTime = float(frameTime/freq);

			// Update camera.
			cameraUpdate(deltaTime, m_mouseState);

			float view[16];
			cameraGetViewMtx(view);

			float proj[16];

			// Set view and projection matrix for view 0.
			const bgfx::HMD* hmd = bgfx::getHMD();
			if (NULL != hmd && 0 != (hmd->flags & BGFX_HMD_RENDERING) )
			{
				float eye[3];
				cameraGetPosition(eye);
				bx::mtxQuatTranslationHMD(view, hmd->eye[0].rotation, eye);
				bgfx::setViewTransform(0, view, hmd->eye[0].projection, BGFX_VIEW_STEREO, hmd->eye[1].projection);
				bgfx::setViewRect(0, 0, 0, hmd->width, hmd->height);
			}
			else
			{
				bx::mtxProj(proj, 60.0f, float(m_width)/float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);

				bgfx::setViewTransform(0, view, proj);
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );
			}

			float mtxVp[16];
			bx::mtxMul(mtxVp, view, proj);

			float mtxInvVp[16];
			bx::mtxInverse(mtxInvVp, mtxVp);

			float zero[3] = {};
			float eye[] = { 5.0f, 10.0f, 5.0f };
			bx::mtxLookAt(view, eye, zero);
			bx::mtxProj(proj, 45.0f, float(m_width)/float(m_height), 1.0f, 15.0f, bgfx::getCaps()->homogeneousDepth);
			bx::mtxMul(mtxVp, view, proj);

			Ray ray = makeRay(
				   (float(m_mouseState.m_mx)/float(m_width)  * 2.0f - 1.0f)
				, -(float(m_mouseState.m_my)/float(m_height) * 2.0f - 1.0f)
				, mtxInvVp
				);

			const uint32_t selected = 0xff80ffff;

			ddBegin(0);
			ddDrawAxis(0.0f, 0.0f, 0.0f);

			ddPush();
				Aabb aabb =
				{
					{  5.0f, 1.0f, 1.0f },
					{ 10.0f, 5.0f, 5.0f },
				};
				ddSetWireframe(true);
				ddSetColor(intersect(ray, aabb) ? selected : 0xff00ff00);
				ddDraw(aabb);
			ddPop();

			float time = float(now/freq);

			Obb obb;
			bx::mtxRotateX(obb.m_mtx, time);
			ddSetWireframe(true);
			ddSetColor(intersect(ray, obb) ? selected : 0xffffffff);
			ddDraw(obb);

			bx::mtxSRT(obb.m_mtx, 1.0f, 1.0f, 1.0f, time*0.23f, time, 0.0f, 3.0f, 0.0f, 0.0f);

			ddPush();
				toAabb(aabb, obb);
				ddSetWireframe(true);
				ddSetColor(0xff0000ff);
				ddDraw(aabb);
			ddPop();

			ddSetWireframe(false);
			ddSetColor(intersect(ray, obb) ? selected : 0xffffffff);
			ddDraw(obb);

			ddSetColor(0xffffffff);

			ddPush();
			{
				float bunny[16];
				bx::mtxSRT(bunny, 0.03f, 0.03f, 0.03f, 0.0f, 0.0f, 0.0f, -3.0f, 0.0f, 0.0f);

				ddSetTransform(bunny);
				ddSetWireframe(bx::fmod(time, 2.0f) > 1.0f);
				ddDraw(m_bunny);
			}
			ddPop();

			ddSetTranslate(0.0f, -2.0f, 0.0f);
			ddDrawGrid(Axis::Y, zero, 20, 1.0f);
			ddSetTransform(NULL);

			ddDrawFrustum(mtxVp);

			ddPush();
				Sphere sphere = { { 0.0f, 5.0f, 0.0f }, 1.0f };
				ddSetColor(intersect(ray, sphere) ? selected : 0xfff0c0ff);
				ddSetWireframe(true);
				ddSetLod(3);
				ddDraw(sphere);
				ddSetWireframe(false);

				sphere.m_center[0] = -2.0f;
				ddSetColor(intersect(ray, sphere) ? selected : 0xc0ffc0ff);
				ddSetLod(2);
				ddDraw(sphere);

				sphere.m_center[0] = -4.0f;
				ddSetColor(intersect(ray, sphere) ? selected : 0xa0f0ffff);
				ddSetLod(1);
				ddDraw(sphere);

				sphere.m_center[0] = -6.0f;
				ddSetColor(intersect(ray, sphere) ? selected : 0xffc0ff00);
				ddSetLod(0);
				ddDraw(sphere);
			ddPop();

			ddSetColor(0xffffffff);

			ddPush();
			{
				float normal[3] = {  0.0f, 0.0f, 1.0f };
				float center[3] = { -8.0f, 0.0f, 0.0f };
				ddPush();
					ddSetStipple(true, 1.0f, time*0.1f);
					ddSetColor(0xff0000ff);
					ddDrawCircle(normal, center, 1.0f, 0.5f + bx::fsin(time*10.0f) );
				ddPop();

				ddSetSpin(time);
				ddDrawQuad(m_sprite, normal, center, 2.0f);
			}
			ddPop();

			ddPush();
				ddSetStipple(true, 1.0f, -time*0.1f);
				ddDrawCircle(Axis::Z, -8.0f, 0.0f, 0.0f, 1.25f, 2.0f);
			ddPop();

			ddPush();
				ddSetLod(UINT8_MAX);

				ddPush();
					ddSetSpin(time*0.3f);
					{
						Cone cone =
						{
							{ -11.0f, 4.0f,  0.0f },
							{ -13.0f, 6.0f,  1.0f },
							1.0f
						};

						Cylinder cylinder =
						{
							{  -9.0f, 2.0f, -1.0f },
							{ -11.0f, 4.0f,  0.0f },
							0.5f
						};

						ddSetColor(false
							|| intersect(ray, cone)
							|| intersect(ray, cylinder)
							? selected
							: 0xffffffff
							);

						ddDraw(cone);
						ddDraw(cylinder);
					}
				ddPop();

				{
					ddSetLod(0);
					Capsule capsule =
					{
						{  0.0f, 7.0f, 0.0f },
						{ -6.0f, 7.0f, 0.0f },
						0.5f
					};
					ddSetColor(intersect(ray, capsule) ? selected : 0xffffffff);
					ddDraw(capsule);
				}
			ddPop();

			ddPush();

				float mtx[16];
				bx::mtxSRT(mtx
					, 1.0f, 1.0f, 1.0f
					, 0.0f, time, time*0.53f
					, -10.0f, 1.0f, 10.0f
					);

				Cylinder cylinder =
				{
					{ -10.0f, 1.0f, 10.0f },
					{ 0.0f, 0.0f, 0.0f },
					1.0f
				};

				float up[3] = { 0.0f, 4.0f, 0.0f };
				bx::vec3MulMtx(cylinder.m_end, up, mtx);
				ddSetColor(intersect(ray, cylinder) ? selected : 0xffffffff);
				ddDraw(cylinder);

				ddPush();
					toAabb(aabb, cylinder);
					ddSetWireframe(true);
					ddSetColor(0xff0000ff);
					ddDraw(aabb);
				ddPop();

			ddPop();

			ddDrawOrb(-11.0f, 0.0f, 0.0f, 1.0f);

			ddEnd();

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();

			return true;
		}

		return false;
	}

	entry::MouseState m_mouseState;

	SpriteHandle   m_sprite;
	GeometryHandle m_bunny;

	int64_t m_timeOffset;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(ExampleDebugDraw, "29-debugdraw", "Debug draw.");
