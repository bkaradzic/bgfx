/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
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
	{   25.0883f,  -44.2788f,   31.0055f },
	{  0.945623f,   53.5504f,  -24.6146f },
	{  -0.94455f,  -14.3443f,  -16.8223f },
	{  -20.1103f,  -48.6664f,   12.6763f },
	{  -1.60652f,  -26.3165f,  -24.5424f },
	{  -30.6284f,  -53.6299f,   14.7666f },
	{   1.69145f,  -43.8075f,  -15.2065f },
	{  -20.5139f,   21.0521f,  -5.40868f },
	{  -13.9518f,   53.6299f,  -39.1193f },
	{  -21.7912f,   48.7801f,  -42.0995f },
	{  -26.8408f,   23.6537f,  -17.7324f },
	{  -23.1196f,   33.9692f,   4.91483f },
	{  -12.3236f,  -41.6303f,   31.8324f },
	{   27.6427f,  -5.05034f,  -11.3201f },
	{   32.2565f,   1.30521f,   30.2671f },
	{   47.2723f,  -27.0974f,   11.1774f },
	{    33.598f,   10.5888f,   7.95916f },
	{  -13.2898f,   12.6234f,   5.55953f },
	{  -32.7364f,   19.0648f,  -10.5736f },
	{  -32.7536f,   31.4158f,  -1.40712f },
	{  -25.3672f,   30.2874f,  -12.4682f },
	{    32.921f,  -36.8408f,  -12.0254f },
	{  -37.7251f,  -33.8989f,  0.378443f },
	{  -35.6341f, -0.246891f,  -9.25165f },
	{  -16.7041f,  -50.0254f,  -15.6177f },
	{   24.6604f,  -53.5319f,  -11.1059f },
	{  -7.77574f,  -53.5719f,  -16.6655f },
	{   20.6241f,   13.3489f,  0.376349f },
	{  -44.2889f,   29.5222f,   18.7918f },
	{   18.5805f,   16.3651f,   12.6351f },
	{  -23.7853f,   31.7598f,  -6.54093f },
	{   24.7518f,  -53.5075f,   2.14984f },
	{  -45.7912f,  -17.6301f,   21.1198f },
	{   51.8403f,  -33.1847f,   24.3337f },
	{  -47.5343f,  -4.32792f,   4.06232f },
	{  -50.6832f,   -12.442f,   11.0994f },
	{  -49.5132f,   19.2782f,   3.17559f },
	{  -39.4881f,   29.0208f,  -6.70431f },
	{  -52.7286f,   1.23232f,   9.74872f },
	{    26.505f,  -16.1297f,  -17.0487f },
	{   -25.367f,   20.0473f,  -8.44282f },
	{  -24.5797f,  -10.3143f,  -18.3154f },
	{  -28.6707f,   6.12074f,   27.8025f },
	{  -16.9868f,   22.6819f,   1.37408f },
	{  -37.2678f,   23.9443f,   -9.4945f },
	{  -24.8562f,   21.3763f,   18.8847f },
	{  -47.1879f,    3.8542f,  -4.74621f },
	{   38.0706f,  -7.33673f,   -7.6099f },
	{  -34.8833f,  -3.57074f,   26.4838f },
	{   12.3797f,   5.46782f,   32.9762f },
	{  -31.5974f,   -22.956f,   30.5827f },
	{  -6.80953f,    48.055f,  -18.5116f },
	{    6.3474f,  -15.1622f,  -24.4726f },
	{  -25.5733f,   25.2452f,  -34.4736f },
	{  -23.8955f,   31.8323f,  -40.8696f },
	{  -11.8622f,   38.2304f,  -43.3125f },
	{  -20.4918f,   41.2409f,  -3.11271f },
	{   24.9806f,  -8.53455f,   37.2862f },
	{  -52.8935f,    5.3376f,    28.246f },
	{    34.106f,  -41.7941f,    30.962f },
	{  -1.26914f,   35.6664f,  -18.7177f },
	{  -0.13048f,   44.7288f,  -28.7163f },
	{   2.47929f,  0.678165f,  -14.6892f },
	{  -31.8649f,  -14.2299f,   32.2998f },
	{   -19.774f,   30.8258f,   5.77293f },
	{   49.8059f,   -37.125f,   4.97284f },
	{  -28.0581f,   -26.439f,  -14.8316f },
	{  -9.12066f,  -27.3987f,  -12.8592f },
	{  -13.8752f,  -29.9821f,   32.5962f },
	{   -6.6222f,  -10.9884f,   33.5007f },
	{  -21.2664f,  -53.6089f,  -3.49195f },
	{ -0.628672f,   52.8093f,  -9.88088f },
	{   8.02417f,   51.8956f,  -21.5834f },
	{  -44.6547f,   11.9973f,   34.7897f },
	{  -7.55466f,   37.9035f, -0.574101f },
	{   52.8252f,  -27.1986f,   11.6429f },
	{ -0.934591f,   9.81861f,  0.512566f },
	{  -3.01043f,   5.70605f,   22.0954f },
	{  -34.6337f,   44.5964f,  -31.1713f },
	{  -26.9017f,   35.1991f,  -32.4307f },
	{   15.9884f,  -8.92223f,  -14.7411f },
	{  -22.8337f,   -43.458f,   26.7274f },
	{  -31.9864f,  -47.0243f,   9.36972f },
	{  -36.9436f,   24.1866f,   29.2521f },
	{  -26.5411f,   29.6549f,   21.2867f },
	{   33.7644f,  -24.1886f,  -13.8513f },
	{  -2.44749f,  -17.0148f,   41.6617f },
	{   -38.364f,  -13.9823f,  -12.5705f },
	{  -10.2972f,  -51.6584f,    38.935f },
	{   1.28109f,  -43.4943f,   36.6288f },
	{  -19.7784f,  -44.0413f,  -4.23994f },
	{   37.0944f,  -53.5479f,   27.6467f },
	{   24.9642f,  -37.1722f,   35.7038f },
	{   37.5851f,   5.64874f,   21.6702f },
	{  -17.4738f,  -53.5734f,   30.0664f },
	{  -8.93088f,   45.3429f,  -34.4441f },
	{  -17.7111f,   -6.5723f,   29.5162f },
	{   44.0059f,  -17.4408f,  -5.08686f },
	{  -46.2534f,  -22.6115f,  0.702059f },
	{   43.9321f,  -33.8575f,   4.31819f },
	{   41.6762f,  -7.37115f,   27.6798f },
	{   8.20276f,  -42.0948f,  -18.0893f },
	{   26.2678f,  -44.6777f,  -10.6835f },
	{    17.709f,   13.1542f,   25.1769f },
	{  -35.9897f,   3.92007f,   35.8198f },
	{  -23.9323f,  -37.3142f,  -2.39396f },
	{   5.19169f,   46.8851f,  -28.7587f },
	{  -37.3072f,  -35.0484f,   16.9719f },
	{   45.0639f,  -28.5255f,   22.3465f },
	{  -34.4175f,   35.5861f,  -21.7562f },
	{   9.32684f,  -12.6655f,    42.189f },
	{   1.00938f,  -31.7694f,   43.1914f },
	{  -45.4666f,  -3.71104f,   19.2248f },
	{  -28.7999f,  -50.8481f,   31.5232f },
	{   35.2212f,  -45.9047f,  0.199736f },
	{      40.3f,  -53.5889f,   7.47622f },
	{   29.0515f,    5.1074f,   -10.002f },
	{   13.4336f,   4.84341f,  -9.72327f },
	{   11.0617f,   -26.245f,  -24.9471f },
	{  -35.6056f,  -51.2531f,  0.436527f },
	{  -10.6863f,   34.7374f,  -36.7452f },
	{  -51.7652f,   27.4957f,   7.79363f },
	{  -50.1898f,    18.379f,   26.3763f },
	{  -49.6836f,  -1.32722f,   26.2828f },
	{   19.0363f,  -16.9114f,   41.8511f },
	{   32.7141f,   -21.501f,   36.0025f },
	{   12.5418f,  -28.4244f,   43.3125f },
	{  -19.5634f,   42.6328f,  -27.0687f },
	{  -16.1942f,   6.55011f,   19.4066f },
	{   46.9886f,  -18.8482f,   22.1332f },
	{   45.9697f,  -3.76781f,   4.10111f },
	{  -28.2912f,   51.3277f,  -35.1815f },
	{  -40.2796f,  -27.7518f,   22.8684f },
	{  -22.7984f,  -38.9977f,    22.158f },
	{   54.0614f,  -35.6096f,    12.694f },
	{   44.2064f,  -53.6029f,   18.8679f },
	{    19.789f,   -29.517f,  -19.6094f },
	{  -34.3769f,   34.8566f,   9.92517f },
	{  -23.7518f,  -45.0319f,   8.71282f },
	{  -12.7978f,   3.55087f,  -13.7108f },
	{  -54.0614f,   8.83831f,   8.91353f },
	{   16.2986f,  -53.5717f,    34.065f },
	{  -36.6243f,  -53.5079f,   24.6495f },
	{   16.5794f,  -48.5747f,   35.5681f },
	{  -32.3263f,   41.4526f,  -18.7388f },
	{  -18.8488f,   9.62627f,  -8.81052f },
	{   5.35849f,   36.3616f,  -12.9346f },
	{   6.19167f,    34.497f,   -17.965f },
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

struct Shape
{
	struct Type
	{
		enum Enum
		{
			Sphere,
			Aabb,
			Triangle,
			Capsule,
			Plane,
			Disk,
			Obb,
			Cone,
			Cylinder,

			Count
		};
	};

	Shape() : type(uint8_t(Type::Count) ) {}
	Shape(const Aabb     & _a) : type(uint8_t(Type::Aabb    ) ) { bx::memCopy(data, &_a, sizeof(_a) ); }
	Shape(const Capsule  & _a) : type(uint8_t(Type::Capsule ) ) { bx::memCopy(data, &_a, sizeof(_a) ); }
	Shape(const Cone     & _a) : type(uint8_t(Type::Cone    ) ) { bx::memCopy(data, &_a, sizeof(_a) ); }
	Shape(const Cylinder & _a) : type(uint8_t(Type::Cylinder) ) { bx::memCopy(data, &_a, sizeof(_a) ); }
	Shape(const Disk     & _a) : type(uint8_t(Type::Disk    ) ) { bx::memCopy(data, &_a, sizeof(_a) ); }
	Shape(const Obb      & _a) : type(uint8_t(Type::Obb     ) ) { bx::memCopy(data, &_a, sizeof(_a) ); }
	Shape(const bx::Plane& _a) : type(uint8_t(Type::Plane   ) ) { bx::memCopy(data, &_a, sizeof(_a) ); }
	Shape(const Sphere   & _a) : type(uint8_t(Type::Sphere  ) ) { bx::memCopy(data, &_a, sizeof(_a) ); }
	Shape(const Triangle & _a) : type(uint8_t(Type::Triangle) ) { bx::memCopy(data, &_a, sizeof(_a) ); }

	uint8_t data[64];
	uint8_t type;
};

#define OVERLAP(_shapeType)                                                                                      \
	bool overlap(const _shapeType& _shapeA, const Shape& _shapeB)                                                \
	{                                                                                                            \
		switch (_shapeB.type)                                                                                    \
		{                                                                                                        \
		case Shape::Type::Aabb:     return ::overlap(_shapeA, *reinterpret_cast<const Aabb     *>(_shapeB.data) ); \
		case Shape::Type::Capsule:  return ::overlap(_shapeA, *reinterpret_cast<const Capsule  *>(_shapeB.data) ); \
		case Shape::Type::Cone:     return ::overlap(_shapeA, *reinterpret_cast<const Cone     *>(_shapeB.data) ); \
		case Shape::Type::Cylinder: return ::overlap(_shapeA, *reinterpret_cast<const Cylinder *>(_shapeB.data) ); \
		case Shape::Type::Disk:     return ::overlap(_shapeA, *reinterpret_cast<const Disk     *>(_shapeB.data) ); \
		case Shape::Type::Obb:      return ::overlap(_shapeA, *reinterpret_cast<const Obb      *>(_shapeB.data) ); \
		case Shape::Type::Plane:    return ::overlap(_shapeA, *reinterpret_cast<const bx::Plane*>(_shapeB.data) ); \
		case Shape::Type::Sphere:   return ::overlap(_shapeA, *reinterpret_cast<const Sphere   *>(_shapeB.data) ); \
		case Shape::Type::Triangle: return ::overlap(_shapeA, *reinterpret_cast<const Triangle *>(_shapeB.data) ); \
		}                                                                                                        \
		return false;                                                                                            \
	}

OVERLAP(Aabb);
OVERLAP(Capsule);
OVERLAP(Cone);
OVERLAP(Cylinder);
OVERLAP(Disk);
OVERLAP(Obb);
OVERLAP(bx::Plane);
OVERLAP(Sphere);
OVERLAP(Triangle);

#undef OVERLAP

void initA(Shape& _outShape, Shape::Type::Enum _type, bx::Vec3 _pos)
{
	switch (_type)
	{
	case Shape::Type::Aabb:
		{
			Aabb aabb;
			toAabb(aabb, _pos, { 0.5f, 0.5f, 0.5f });
			_outShape = Shape(aabb);
		}
		break;

	case Shape::Type::Capsule:
		_outShape = Shape(Capsule
		{
			{ bx::add(_pos, {0.0f, -1.0f, 0.0f}) },
			{ bx::add(_pos, {0.0f,  1.0f, 0.0f}) },
			0.5f,
		});
		break;

	case Shape::Type::Cone:
		_outShape = Shape(Cone
		{
			{ bx::add(_pos, {0.0f, -1.0f, 0.0f}) },
			{ bx::add(_pos, {0.0f,  1.0f, 0.0f}) },
			0.5f,
		});
		break;

	case Shape::Type::Cylinder:
		_outShape = Shape(Cylinder
		{
			{ bx::add(_pos, {0.0f, -1.0f, 0.0f}) },
			{ bx::add(_pos, {0.0f,  1.0f, 0.0f}) },
			0.5f,
		});
		break;

	case Shape::Type::Disk:
		_outShape = Shape(Disk
		{
			_pos,
			bx::normalize(bx::Vec3{0.0f, 1.0f, 1.0f}),
			0.5f,
		});
		break;

	case Shape::Type::Obb:
		{
			Obb obb;
			bx::mtxSRT(obb.mtx
				, 0.25f
				, 1.0f
				, 0.25f
				, bx::toRad(50.0f)
				, bx::toRad(15.0f)
				, bx::toRad(45.0f)
				, _pos.x
				, _pos.y
				, _pos.z
				);
			_outShape = Shape(obb);
		}
		break;

	case Shape::Type::Sphere:
		_outShape = Shape(Sphere{_pos, 0.5f});
		break;

	case Shape::Type::Plane:
		{
			bx::Plane plane;
			bx::calcPlane(plane, bx::normalize(bx::Vec3{0.0f, 1.0f, 1.0f}), _pos);
			_outShape = Shape(plane);
		}
		break;

	case Shape::Type::Triangle:
		_outShape = Shape(Triangle
			{
				{ bx::add(_pos, {-0.4f,  0.0f, -0.4f}) },
				{ bx::add(_pos, { 0.0f, -0.3f,  0.5f}) },
				{ bx::add(_pos, { 0.0f,  0.5f,  0.3f}) },
			});
		break;

	default: break;
	}
}

void initB(Shape& _outShape, Shape::Type::Enum _type, bx::Vec3 _pos)
{
	switch (_type)
	{
	case Shape::Type::Aabb:
		{
			Aabb aabb;
			toAabb(aabb, _pos, { 0.5f, 0.5f, 0.5f });
			_outShape = Shape(aabb);
		}
		break;

	case Shape::Type::Capsule:
		_outShape = Shape(Capsule
		{
			{ bx::add(_pos, {0.0f, -1.0f, 0.1f}) },
			{ bx::add(_pos, {0.0f,  1.0f, 0.0f}) },
			0.2f,
		});
		break;

	case Shape::Type::Cone:
		_outShape = Shape(Cone
		{
			{ bx::add(_pos, {0.0f, -1.0f, 0.1f}) },
			{ bx::add(_pos, {0.0f,  1.0f, 0.0f}) },
			0.2f,
		});
		break;

	case Shape::Type::Cylinder:
		_outShape = Shape(Cylinder
		{
			{ bx::add(_pos, {0.0f, -1.0f, 0.1f}) },
			{ bx::add(_pos, {0.0f,  1.0f, 0.0f}) },
			0.2f,
		});
		break;

	case Shape::Type::Disk:
		_outShape = Shape(Disk
		{
			_pos,
			bx::normalize(bx::Vec3{1.0f, 1.0f, 0.0f}),
			0.5f,
		});
		break;

	case Shape::Type::Obb:
		{
			Obb obb;
			bx::mtxSRT(obb.mtx
				, 1.0f
				, 0.25f
				, 0.25f
				, bx::toRad(10.0f)
				, bx::toRad(30.0f)
				, bx::toRad(70.0f)
				, _pos.x
				, _pos.y
				, _pos.z
				);
			_outShape = Shape(obb);
		}
		break;

	case Shape::Type::Plane:
		{
			bx::Plane plane;
			bx::calcPlane(plane, bx::normalize(bx::Vec3{1.0f, 1.0f, 0.0f}), _pos);
			_outShape = Shape(plane);
		}
		break;

	case Shape::Type::Sphere:
		_outShape = Shape(Sphere{_pos, 0.5f});
		break;

	case Shape::Type::Triangle:
		_outShape = Shape(Triangle
			{
				{ bx::add(_pos, {-0.4f,  0.0f, -0.4f}) },
				{ bx::add(_pos, {-0.5f, -0.3f,  0.0f}) },
				{ bx::add(_pos, { 0.3f,  0.5f,  0.0f}) },
			});
		break;

	default: break;
	}
}

int32_t overlap(const Shape& _shapeA, const Shape& _shapeB)
{
	switch (_shapeA.type)
	{
	case Shape::Type::Aabb:     return overlap(*reinterpret_cast<const Aabb     *>(_shapeA.data), _shapeB);
	case Shape::Type::Capsule:  return overlap(*reinterpret_cast<const Capsule  *>(_shapeA.data), _shapeB);
	case Shape::Type::Cone:     return overlap(*reinterpret_cast<const Cone     *>(_shapeA.data), _shapeB);
	case Shape::Type::Cylinder: return overlap(*reinterpret_cast<const Cylinder *>(_shapeA.data), _shapeB);
	case Shape::Type::Disk:     return overlap(*reinterpret_cast<const Disk     *>(_shapeA.data), _shapeB);
	case Shape::Type::Obb:      return overlap(*reinterpret_cast<const Obb      *>(_shapeA.data), _shapeB);
	case Shape::Type::Plane:    return overlap(*reinterpret_cast<const bx::Plane*>(_shapeA.data), _shapeB);
	case Shape::Type::Sphere:   return overlap(*reinterpret_cast<const Sphere   *>(_shapeA.data), _shapeB);
	case Shape::Type::Triangle: return overlap(*reinterpret_cast<const Triangle *>(_shapeA.data), _shapeB);
	}

	return 2;
}

void draw(DebugDrawEncoder& _dde, const Shape& _shape, const bx::Vec3 _pos)
{
	switch (_shape.type)
	{
	case Shape::Type::Aabb:     _dde.draw    (*reinterpret_cast<const Aabb     *>(_shape.data) ); break;
	case Shape::Type::Capsule:  _dde.draw    (*reinterpret_cast<const Capsule  *>(_shape.data) ); break;
	case Shape::Type::Cone:     _dde.draw    (*reinterpret_cast<const Cone     *>(_shape.data) ); break;
	case Shape::Type::Cylinder: _dde.draw    (*reinterpret_cast<const Cylinder *>(_shape.data) ); break;
	case Shape::Type::Disk:     _dde.draw    (*reinterpret_cast<const Disk     *>(_shape.data) ); break;
	case Shape::Type::Obb:      _dde.draw    (*reinterpret_cast<const Obb      *>(_shape.data) ); break;
	case Shape::Type::Plane:  { _dde.drawGrid( reinterpret_cast<const bx::Plane*>(_shape.data)->normal, _pos, 9, 0.3f); } break;
	case Shape::Type::Sphere:   _dde.draw    (*reinterpret_cast<const Sphere   *>(_shape.data) ); break;
	case Shape::Type::Triangle: _dde.draw    (*reinterpret_cast<const Triangle *>(_shape.data) ); break;
	}
}

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
    ExampleDebugDraw(const char* _name, const char* _description, const char* _url)
        : entry::AppI(_name, _description, _url)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		Args args(_argc, _argv);

		m_width  = _width;
		m_height = _height;
		m_debug  = BGFX_DEBUG_NONE;
		m_reset  = BGFX_RESET_VSYNC | BGFX_RESET_MSAA_X16;

		bgfx::Init init;
		init.type     = args.m_type;
		init.vendorId = args.m_pciId;
		init.resolution.width  = m_width;
		init.resolution.height = m_height;
		init.resolution.reset  = m_reset;
		bgfx::init(init);

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

		cameraSetPosition({ 0.0f, 2.0f, -12.0f });
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
	bool intersect(DebugDrawEncoder* _dde, const Ray& _ray, const Ty& _shape)
	{
		Hit hit;
		if (::intersect(_ray, _shape, &hit) )
		{
			_dde->push();

			_dde->setWireframe(false);

			_dde->setColor(0xff0000ff);

			_dde->drawCone(hit.pos, bx::mad(hit.plane.normal, 0.7f, hit.pos), 0.1f);

			_dde->pop();

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

			ImGui::SetNextWindowPos(
				  ImVec2(m_width - m_width / 5.0f - 10.0f, 10.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::SetNextWindowSize(
				  ImVec2(m_width / 5.0f, m_height / 3.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::Begin("Settings"
				, NULL
				, 0
				);

			static float amplitudeMul = 0.0f;
			ImGui::SliderFloat("Amplitude", &amplitudeMul, 0.0f, 1.0f);

			static float timeScale = 1.0f;
			ImGui::SliderFloat("T scale", &timeScale, -1.0f, 1.0f);

			ImGui::End();

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
			{
				bx::mtxProj(proj, 60.0f, float(m_width)/float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);

				bgfx::setViewTransform(0, view, proj);
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );
			}

			float mtxVp[16];
			bx::mtxMul(mtxVp, view, proj);

			float mtxInvVp[16];
			bx::mtxInverse(mtxInvVp, mtxVp);

			const bx::Vec3 at  = { 0.0f,  0.0f, 0.0f };
			const bx::Vec3 eye = { 5.0f, 10.0f, 5.0f };
			bx::mtxLookAt(view, eye, at);
			bx::mtxProj(proj, 45.0f, float(m_width)/float(m_height), 1.0f, 15.0f, bgfx::getCaps()->homogeneousDepth);
			bx::mtxMul(mtxVp, view, proj);

			Ray ray = makeRay(
				   (float(m_mouseState.m_mx)/float(m_width)  * 2.0f - 1.0f)
				, -(float(m_mouseState.m_my)/float(m_height) * 2.0f - 1.0f)
				, mtxInvVp
				);

			constexpr uint32_t kSelected = 0xff80ffff;
			constexpr uint32_t kOverlapA = 0xff0000ff;
			constexpr uint32_t kOverlapB = 0xff8080ff;

			DebugDrawEncoder dde;

			dde.begin(0);
			dde.drawAxis(0.0f, 0.0f, 0.0f);

			dde.push();
				Aabb aabb =
				{
					{  5.0f, 1.0f, 1.0f },
					{ 10.0f, 5.0f, 5.0f },
				};
				dde.setWireframe(true);
				dde.setColor(intersect(&dde, ray, aabb) ? kSelected : 0xff00ff00);
				dde.draw(aabb);
			dde.pop();

			static float time = 0.0f;
			time += deltaTime*timeScale;

			Obb obb;
			bx::mtxRotateX(obb.mtx, time);
			dde.setWireframe(true);
			dde.setColor(intersect(&dde, ray, obb) ? kSelected : 0xffffffff);
			dde.draw(obb);

			bx::mtxSRT(obb.mtx, 1.0f, 1.0f, 1.0f, time*0.23f, time, 0.0f, 3.0f, 0.0f, 0.0f);

			dde.push();
				toAabb(aabb, obb);
				dde.setWireframe(true);
				dde.setColor(0xff0000ff);
				dde.draw(aabb);
			dde.pop();

			dde.setWireframe(false);
			dde.setColor(intersect(&dde, ray, obb) ? kSelected : 0xffffffff);
			dde.draw(obb);

			dde.setColor(0xffffffff);

			dde.push();
			{
				float bunny[16];
				bx::mtxSRT(bunny, 0.03f, 0.03f, 0.03f, 0.0f, 0.0f, 0.0f, -3.0f, 0.0f, 0.0f);

				dde.setTransform(bunny);
				const bool wireframe = bx::mod(time, 2.0f) > 1.0f;
				dde.setWireframe(wireframe);
				dde.setColor(wireframe ? 0xffff00ff : 0xff00ff00);
				dde.draw(m_bunny);
				dde.setTransform(NULL);
			}
			dde.pop();

			{
				const bx::Vec3 normal = { 0.0f,  1.0f, 0.0f };
				const bx::Vec3 pos    = { 0.0f, -2.0f, 0.0f };

				bx::Plane plane;
				bx::calcPlane(plane, normal, pos);

				dde.setColor(false
					|| intersect(&dde, ray, plane)
					? kSelected
					: 0xffffffff
					);

				dde.drawGrid(Axis::Y, pos, 128, 1.0f);
			}

			dde.drawFrustum(mtxVp);

			dde.push();
				Sphere sphere = { { 0.0f, 5.0f, 0.0f }, 1.0f };
				dde.setColor(intersect(&dde, ray, sphere) ? kSelected : 0xfff0c0ff);
				dde.setWireframe(true);
				dde.setLod(3);
				dde.draw(sphere);
				dde.setWireframe(false);

				sphere.center.x = -2.0f;
				dde.setColor(intersect(&dde, ray, sphere) ? kSelected : 0xc0ffc0ff);
				dde.setLod(2);
				dde.draw(sphere);

				sphere.center.x = -4.0f;
				dde.setColor(intersect(&dde, ray, sphere) ? kSelected : 0xa0f0ffff);
				dde.setLod(1);
				dde.draw(sphere);

				sphere.center.x = -6.0f;
				dde.setColor(intersect(&dde, ray, sphere) ? kSelected : 0xffc0ff00);
				dde.setLod(0);
				dde.draw(sphere);
			dde.pop();

			dde.setColor(0xffffffff);

			dde.push();
			{
				const bx::Vec3 normal = {  0.0f, 0.0f, 1.0f };
				const bx::Vec3 center = { -8.0f, 0.0f, 0.0f };
				dde.push();
					dde.setStipple(true, 1.0f, time*0.1f);
					dde.setColor(0xff0000ff);
					dde.drawCircle(normal, center, 1.0f, 0.5f + bx::sin(time*10.0f) );
				dde.pop();

				dde.setSpin(time);
				dde.drawQuad(m_sprite, normal, center, 2.0f);
			}
			dde.pop();

			dde.push();
				dde.setStipple(true, 1.0f, -time*0.1f);
				dde.drawCircle(Axis::Z, -8.0f, 0.0f, 0.0f, 1.25f, 2.0f);
			dde.pop();

			dde.push();
				dde.setLod(UINT8_MAX);

				dde.push();
					dde.setSpin(time*0.3f);
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

						dde.setColor(false
							|| intersect(&dde, ray, cone)
							|| intersect(&dde, ray, cylinder)
							? kSelected
							: 0xffffffff
							);

						dde.draw(cone);
						dde.draw(cylinder);
					}
				dde.pop();

				{
					dde.setLod(0);
					Capsule capsule =
					{
						{  0.0f, 7.0f, 0.0f },
						{ -6.0f, 7.0f, 0.0f },
						0.5f
					};
					dde.setColor(intersect(&dde, ray, capsule) ? kSelected : 0xffffffff);
					dde.draw(capsule);
				}
			dde.pop();

			dde.push();

				float mtx[16];
				bx::mtxSRT(mtx
					, 1.0f, 1.0f, 1.0f
					, 0.0f, time, time*0.53f
					, -10.0f, 1.0f, 10.0f
					);

				Cylinder cylinder =
				{
					{ -10.0f, 1.0f, 10.0f },
					{   0.0f, 0.0f,  0.0f },
					1.0f
				};

				cylinder.end = bx::mul({ 0.0f, 4.0f, 0.0f }, mtx);
				dde.setColor(intersect(&dde, ray, cylinder) ? kSelected : 0xffffffff);
				dde.draw(cylinder);

				dde.push();
					toAabb(aabb, cylinder);
					dde.setWireframe(true);
					dde.setColor(0xff0000ff);
					dde.draw(aabb);
				dde.pop();

			dde.pop();

			dde.drawOrb(-11.0f, 0.0f, 0.0f, 1.0f);

			dde.push();
				{
					constexpr uint32_t colorA[] =
					{
						0xffffffff,
						kOverlapA,
						0xff666666,
						0xff6666ff,
					};

					constexpr uint32_t colorB[] =
					{
						0xffffffff,
						kOverlapB,
						0xff888888,
						0xff8888ff,
					};

					constexpr float kStep = 3.0f;

					bx::Vec3 posA =
					{
						-4.5f*kStep,
						 1.0f,
						20.0f,
					};

					for (uint32_t ii = 0; ii < Shape::Type::Count; ++ii)
					{
						const bx::Vec3 posB = bx::add(posA,
						{
							amplitudeMul*bx::sin(time*0.39f) * 1.03f,
							amplitudeMul*bx::cos(time*0.79f) * 1.03f,
							amplitudeMul*bx::cos(time)       * 1.03f,
						});

						for (uint32_t jj = 0; jj < Shape::Type::Count; ++jj)
						{
							const bx::Vec3 pa = bx::add(posA, {jj*kStep, 0.0f, 0.0f});
							const bx::Vec3 pb = bx::add(posB, {jj*kStep, 0.0f, 0.0f});

							Shape shapeA, shapeB;
							initA(shapeA, Shape::Type::Enum(ii), pa);
							initB(shapeB, Shape::Type::Enum(jj), pb);

							int32_t olp = overlap(shapeA, shapeB);

							dde.setColor(colorA[olp]);
							dde.setWireframe(false);
							draw(dde, shapeA, pa);

							dde.setColor(colorB[olp]);
							dde.setWireframe(true);
							draw(dde, shapeB, pb);
						}

						posA = bx::add(posA, {0.0f, 0.0f, kStep});
					}
				}

			dde.pop();

			dde.end();

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

ENTRY_IMPLEMENT_MAIN(
	  ExampleDebugDraw
	, "29-debugdraw"
	, "Debug draw."
	, "https://bkaradzic.github.io/bgfx/examples.html#debugdraw"
	);
