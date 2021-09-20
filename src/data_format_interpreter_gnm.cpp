/********************************************************
*   (c) Mojang. All rights reserved                     *
*   (c) Microsoft. All rights reserved.                 *
*********************************************************/
#ifdef __ORBIS__

#include "data_format_interpreter_gnm.h"
#include "bgfx_p.h"

#include <math.h>
#include <algorithm>
#include <gnm/error.h>

struct SurfaceFormatInfo
{
	sce::Gnm::SurfaceFormat m_format;
	uint8_t m_reserved[4];
	uint64_t m_channels;
	uint64_t m_bitsPerElement;
	uint64_t m_bits[4];
	void (*m_encoder)(const SurfaceFormatInfo* __restrict info, uint32_t* __restrict dest, const DataFormatInterpreter::Reg32* __restrict src, const sce::Gnm::DataFormat dataFormat);
	void (*m_decoder)(const SurfaceFormatInfo* __restrict info, DataFormatInterpreter::Reg32* __restrict dest, const uint32_t* __restrict src, const sce::Gnm::DataFormat dataFormat);
	uint64_t m_offset[4];
	double m_ooMaxUnormValue[4];
	double m_ooMaxSnormValue[4];
	inline uint32_t maxUnormValue(uint32_t channel) const { return (uint64_t(1) << (m_bits[channel] - 0)) - 1; }
	inline uint32_t maxSnormValue(uint32_t channel) const { return (uint64_t(1) << (m_bits[channel] - 1)) - 1; }
	inline  int32_t minSnormValue(uint32_t channel) const { return -maxSnormValue(channel) - 1; }
};

//Floating point utils
namespace
{
	union f32
	{
		enum { kBias = 127 };
		struct
		{
			uint32_t m_mantissa : 23;
			uint32_t m_exponent : 8;
			uint32_t m_sign : 1;
		} bits;
		uint32_t u;
		float f;
	};

	uint32_t packBits(uint32_t value, uint32_t offset, uint32_t count, uint32_t field)
	{
		const uint32_t mask = ((1 << count) - 1) << offset;
		return (value & ~mask) | ((field << offset) & mask);
	}

	uint32_t unpackBits(uint32_t value, uint32_t offset, uint32_t count)
	{
		return (value >> offset) & ((1 << count) - 1);
	}

	/*
	uint32_t expandIntegerFraction(uint32_t value, uint32_t oldBits, uint32_t newBits)
	{
	const uint32_t shift = (newBits - oldBits);
	uint32_t result = value << shift;
	result |= result >> (oldBits* 1);
	result |= result >> (oldBits* 2);
	result |= result >> (oldBits* 4);
	result |= result >> (oldBits* 8);
	result |= result >> (oldBits*16);
	return result;
	}
	*/
}

uint32_t DataFormatInterpreter::packFloat(float value, uint32_t signBits, uint32_t exponentBits, uint32_t mantissaBits)
{
	if (signBits == 0)
		value = std::max(0.f, value);
	f32 in;
	in.f = value;
	const int32_t maxExponent = (1 << exponentBits) - 1;
	const uint32_t bias = maxExponent >> 1;
	const uint32_t sign = in.bits.m_sign;
	uint32_t mantissa = in.bits.m_mantissa >> (23 - mantissaBits);
	int32_t exponent;
	switch (in.bits.m_exponent)
	{
	case 0x00:
		exponent = 0;
		break;
	case 0xFF:
		exponent = maxExponent;
		break;
	default:
		exponent = in.bits.m_exponent - 127 + bias;
		if (exponent < 1)
		{
			exponent = 1;
			mantissa = 0;
		}
		if (exponent > maxExponent - 1)
		{
			exponent = maxExponent - 1;
			mantissa = (1 << 23) - 1;
		}
	}
	uint32_t result = 0;
	result = packBits(result, 0, mantissaBits, mantissa);
	result = packBits(result, mantissaBits, exponentBits, exponent);
	result = packBits(result, mantissaBits + exponentBits, signBits, sign);
	return result;
}

float DataFormatInterpreter::unpackFloat(uint32_t value, uint32_t signBits, uint32_t exponentBits, uint32_t mantissaBits)
{
	f32 out;
	const uint32_t maxExponent = (1 << exponentBits) - 1;
	const uint32_t bias = maxExponent >> 1;
	const uint32_t mantissa = unpackBits(value, 0, mantissaBits);
	const uint32_t exponent = unpackBits(value, mantissaBits, exponentBits);
	const uint32_t sign = unpackBits(value, mantissaBits + exponentBits, signBits);
	out.bits.m_mantissa = mantissa << (23 - mantissaBits);
	out.bits.m_exponent = (exponent == 0) ? 0 : (exponent == maxExponent) ? 0xFF : exponent - bias + 127;
	out.bits.m_sign = sign;
	return out.f;
}

int32_t DataFormatInterpreter::convertFloatToInt(float value)
{
	return static_cast<int32_t>(floorf(value + 0.5f));
}

uint32_t DataFormatInterpreter::convertFloatToUint(float value)
{
	return static_cast<uint32_t>(floorf(value + 0.5f));
}

uint32_t DataFormatInterpreter::floatToFloat10(float value)
{
	return packFloat(value, 0, 5, 5);
}

uint32_t DataFormatInterpreter::floatToFloat11(float value)
{
	return packFloat(value, 0, 5, 6);
}

uint32_t DataFormatInterpreter::floatToFloat16(float value)
{
	return packFloat(value, 1, 5, 10);
}

uint32_t DataFormatInterpreter::floatToFloat32(float value)
{
	return packFloat(value, 1, 8, 23);
}

float DataFormatInterpreter::float10ToFloat(uint32_t value)
{
	return unpackFloat(value, 0, 5, 5);
}

float DataFormatInterpreter::float11ToFloat(uint32_t value)
{
	return unpackFloat(value, 0, 5, 6);
}

float DataFormatInterpreter::float16ToFloat(uint32_t value)
{
	return unpackFloat(value, 1, 5, 10);
}

float DataFormatInterpreter::float32ToFloat(uint32_t value)
{
	return unpackFloat(value, 1, 8, 23);
}

//End of floating point utils

struct FloatInfo
{
	uint8_t m_signBits;
	uint8_t m_exponentBits;
	uint8_t m_mantissaBits;
};

static const FloatInfo floatInfo[] =
{
	{}, // 0
	{}, // 1
	{}, // 2
	{}, // 3
	{}, // 4
	{}, // 5
	{}, // 6
	{}, // 7
	{}, // 8
	{}, // 9
	{0, 5, 5}, // 10
	{0, 5, 6}, // 11
	{}, // 12
	{}, // 13
	{}, // 14
	{}, // 15
	{1, 5, 10}, // 16
	{}, // 17
	{}, // 18
	{}, // 19
	{}, // 20
	{}, // 21
	{}, // 22
	{}, // 23
	{}, // 24
	{}, // 25
	{}, // 26
	{}, // 27
	{}, // 28
	{}, // 29
	{}, // 30
	{}, // 31
	{1, 8, 23}, // 32
};

namespace
{
	inline double linear2sRgb(double linear)
	{
		return (linear <= 0.00313066844250063) ? linear * 12.92 : 1.055 * pow(linear, 1 / 2.4) - 0.055;
	}

	inline double sRgb2Linear(double sRgb)
	{
		return (sRgb <= 0.0404482362771082) ? sRgb / 12.92 : pow((sRgb + 0.055) / 1.055, 2.4);
	}

	inline double clamp(double a, double lo, double hi)
	{
		return fmax(lo, fmin(hi, a));
	}

	inline uint32_t decodeU(uint32_t value, const SurfaceFormatInfo* __restrict info, uint32_t channel) // zero-extend a <=32 unsigned integer to 32 bits.
	{
		SCE_GNM_UNUSED(info);
		SCE_GNM_UNUSED(channel);
		return value;
	}

	inline int32_t decodeS(uint32_t value, const SurfaceFormatInfo* __restrict info, uint32_t channel) // sign-extend a <=32 signed integer to 32 bits.
	{
		if (value & info->minSnormValue(channel)) // if the sign bit is on
			value |= ~info->maxUnormValue(channel); // extend it to the top of the integer
		return value;
	}

	inline int32_t decodeUB(uint32_t value, const SurfaceFormatInfo* __restrict info, uint32_t channel) // bias a <=32 unsigned integer to signed, then sign-extend to 32 bits.
	{
		return value + info->minSnormValue(channel);
	}

	inline uint32_t encodeU(uint32_t value, const SurfaceFormatInfo* __restrict info, uint32_t channel) // encode a 32 bit unsigned integer to <=32 bits.
	{
		return value & info->maxUnormValue(channel);
	}

	inline uint32_t encodeS(int32_t value, const SurfaceFormatInfo* __restrict info, uint32_t channel) // encode a 32 bit signed integer to <=32 bits.
	{
		return value & info->maxUnormValue(channel);
	}

	inline uint32_t encodeUB(int32_t value, const SurfaceFormatInfo* __restrict info, uint32_t channel) // encode a 32 bit signed integer to <=32 bits, then bias to unsigned.
	{
		return (value - info->minSnormValue(channel)) & info->maxUnormValue(channel);
	}

	inline int32_t roundDoubleToInt(double value)
	{
		return static_cast<int32_t>(floor(value + 0.5));
	}

	inline uint32_t roundDoubleToUint(double value)
	{
		return static_cast<uint32_t>(floor(value + 0.5));
	}

	void encodeTextureChannelSharedExponent(uint32_t* __restrict dest, const DataFormatInterpreter::Reg32* __restrict source, const SurfaceFormatInfo* __restrict info)
	{
		DataFormatInterpreter::Reg32 temp[3] = { source[0], source[1], source[2] };
		const int32_t sharedExponent = std::max(temp[0].bits.m_exponent, std::max(temp[1].bits.m_exponent, temp[2].bits.m_exponent)) - 127;
		temp[0].bits.m_exponent = temp[0].bits.m_exponent ? std::max(0, std::min(255, temp[0].bits.m_exponent - 127 + (static_cast<uint8_t>(info->m_bits[0]) - 1) - sharedExponent + 127)) : 0;
		temp[1].bits.m_exponent = temp[1].bits.m_exponent ? std::max(0, std::min(255, temp[1].bits.m_exponent - 127 + (static_cast<uint8_t>(info->m_bits[1]) - 1) - sharedExponent + 127)) : 0;
		temp[2].bits.m_exponent = temp[2].bits.m_exponent ? std::max(0, std::min(255, temp[2].bits.m_exponent - 127 + (static_cast<uint8_t>(info->m_bits[2]) - 1) - sharedExponent + 127)) : 0;
		dest[0] = std::max(int32_t(0), std::min(int32_t(info->maxUnormValue(0)), roundDoubleToInt(temp[0].f)));
		dest[1] = std::max(int32_t(0), std::min(int32_t(info->maxUnormValue(1)), roundDoubleToInt(temp[1].f)));
		dest[2] = std::max(int32_t(0), std::min(int32_t(info->maxUnormValue(2)), roundDoubleToInt(temp[2].f)));
		const int32_t minExponent = -info->maxSnormValue(3);
		const int32_t maxExponent = info->maxSnormValue(3) + 1;
		dest[3] = std::max(minExponent, std::min(maxExponent, sharedExponent)) - minExponent;
	}

	void decodeTextureChannelSharedExponent(DataFormatInterpreter::Reg32* __restrict dest, const uint32_t* __restrict source, const SurfaceFormatInfo* __restrict info)
	{
		const int32_t sharedExponent = source[3] - info->maxSnormValue(3);
		dest[0].f = source[0] * pow(2, sharedExponent - info->m_bits[0] + 1);
		dest[1].f = source[1] * pow(2, sharedExponent - info->m_bits[1] + 1);
		dest[2].f = source[2] * pow(2, sharedExponent - info->m_bits[2] + 1);
		dest[3].f = 0.f;
	}

	void decodeTextureChannelsUNorm(DataFormatInterpreter::Reg32* __restrict dest, const uint32_t* __restrict value, const SurfaceFormatInfo* __restrict info)
	{
		dest[0].f = decodeU(value[0], info, 0) * info->m_ooMaxUnormValue[0];
		dest[1].f = decodeU(value[1], info, 1) * info->m_ooMaxUnormValue[1];
		dest[2].f = decodeU(value[2], info, 2) * info->m_ooMaxUnormValue[2];
		dest[3].f = decodeU(value[3], info, 3) * info->m_ooMaxUnormValue[3];
	}

	void decodeTextureChannelsSNorm(DataFormatInterpreter::Reg32* __restrict dest, const uint32_t* __restrict value, const SurfaceFormatInfo* __restrict info)
	{
		dest[0].f = fmax(-1.0, decodeS(value[0], info, 0) * info->m_ooMaxSnormValue[0]);
		dest[1].f = fmax(-1.0, decodeS(value[1], info, 1) * info->m_ooMaxSnormValue[1]);
		dest[2].f = fmax(-1.0, decodeS(value[2], info, 2) * info->m_ooMaxSnormValue[2]);
		dest[3].f = fmax(-1.0, decodeS(value[3], info, 3) * info->m_ooMaxSnormValue[3]);
	}

	void decodeTextureChannelsUScaled(DataFormatInterpreter::Reg32* __restrict dest, const uint32_t* __restrict value, const SurfaceFormatInfo* __restrict info)
	{
		dest[0].f = decodeU(value[0], info, 0);
		dest[1].f = decodeU(value[1], info, 1);
		dest[2].f = decodeU(value[2], info, 2);
		dest[3].f = decodeU(value[3], info, 3);
	}

	void decodeTextureChannelsSScaled(DataFormatInterpreter::Reg32* __restrict dest, const uint32_t* __restrict value, const SurfaceFormatInfo* __restrict info)
	{
		dest[0].f = decodeS(value[0], info, 0);
		dest[1].f = decodeS(value[1], info, 1);
		dest[2].f = decodeS(value[2], info, 2);
		dest[3].f = decodeS(value[3], info, 3);
	}

	void decodeTextureChannelsUInt(DataFormatInterpreter::Reg32* __restrict dest, const uint32_t* __restrict value, const SurfaceFormatInfo* __restrict info)
	{
		dest[0].u = decodeU(value[0], info, 0);
		dest[1].u = decodeU(value[1], info, 1);
		dest[2].u = decodeU(value[2], info, 2);
		dest[3].u = decodeU(value[3], info, 3);
	}

	void decodeTextureChannelsSInt(DataFormatInterpreter::Reg32* __restrict dest, const uint32_t* __restrict value, const SurfaceFormatInfo* __restrict info)
	{
		dest[0].i = decodeS(value[0], info, 0);
		dest[1].i = decodeS(value[1], info, 1);
		dest[2].i = decodeS(value[2], info, 2);
		dest[3].i = decodeS(value[3], info, 3);
	}

	void decodeTextureChannelsSNormNoZero(DataFormatInterpreter::Reg32* __restrict dest, const uint32_t* __restrict value, const SurfaceFormatInfo* __restrict info)
	{
		dest[0].f = ((decodeS(value[0], info, 0) - info->minSnormValue(0)) * info->m_ooMaxUnormValue[0]) * 2.0 - 1.0;
		dest[1].f = ((decodeS(value[1], info, 1) - info->minSnormValue(1)) * info->m_ooMaxUnormValue[1]) * 2.0 - 1.0;
		dest[2].f = ((decodeS(value[2], info, 2) - info->minSnormValue(2)) * info->m_ooMaxUnormValue[2]) * 2.0 - 1.0;
		dest[3].f = ((decodeS(value[3], info, 3) - info->minSnormValue(3)) * info->m_ooMaxUnormValue[3]) * 2.0 - 1.0;
	}

	void decodeTextureChannelsFloat(DataFormatInterpreter::Reg32* __restrict dest, const uint32_t* __restrict value, const SurfaceFormatInfo* __restrict info)
	{
		dest[0].f = DataFormatInterpreter::unpackFloat(value[0], floatInfo[info->m_bits[0]].m_signBits, floatInfo[info->m_bits[0]].m_exponentBits, floatInfo[info->m_bits[0]].m_mantissaBits);
		dest[1].f = DataFormatInterpreter::unpackFloat(value[1], floatInfo[info->m_bits[1]].m_signBits, floatInfo[info->m_bits[1]].m_exponentBits, floatInfo[info->m_bits[1]].m_mantissaBits);
		dest[2].f = DataFormatInterpreter::unpackFloat(value[2], floatInfo[info->m_bits[2]].m_signBits, floatInfo[info->m_bits[2]].m_exponentBits, floatInfo[info->m_bits[2]].m_mantissaBits);
		dest[3].f = DataFormatInterpreter::unpackFloat(value[3], floatInfo[info->m_bits[3]].m_signBits, floatInfo[info->m_bits[3]].m_exponentBits, floatInfo[info->m_bits[3]].m_mantissaBits);
	}

	void decodeTextureChannelsSrgb(DataFormatInterpreter::Reg32* __restrict dest, const uint32_t* __restrict value, const SurfaceFormatInfo* __restrict info)
	{
		dest[0].f = sRgb2Linear(decodeU(value[0], info, 0) * info->m_ooMaxUnormValue[0]);
		dest[1].f = sRgb2Linear(decodeU(value[1], info, 1) * info->m_ooMaxUnormValue[1]);
		dest[2].f = sRgb2Linear(decodeU(value[2], info, 2) * info->m_ooMaxUnormValue[2]);
		dest[3].f = decodeU(value[3], info, 3) * info->m_ooMaxUnormValue[3];
	}

	void decodeTextureChannelsUBNorm(DataFormatInterpreter::Reg32* __restrict dest, const uint32_t* __restrict value, const SurfaceFormatInfo* __restrict info)
	{
		dest[0].f = fmax(-1.0, decodeUB(value[0], info, 0) * info->m_ooMaxSnormValue[0]);
		dest[1].f = fmax(-1.0, decodeUB(value[1], info, 1) * info->m_ooMaxSnormValue[1]);
		dest[2].f = fmax(-1.0, decodeUB(value[2], info, 2) * info->m_ooMaxSnormValue[2]);
		dest[3].f = fmax(-1.0, decodeUB(value[3], info, 3) * info->m_ooMaxSnormValue[3]);
	}

	void decodeTextureChannelsUBNormNoZero(DataFormatInterpreter::Reg32* __restrict dest, const uint32_t* __restrict value, const SurfaceFormatInfo* __restrict info)
	{
		dest[0].f = ((decodeUB(value[0], info, 0) - info->minSnormValue(0)) * info->m_ooMaxUnormValue[0]) * 2.0 - 1.0;
		dest[1].f = ((decodeUB(value[1], info, 1) - info->minSnormValue(1)) * info->m_ooMaxUnormValue[1]) * 2.0 - 1.0;
		dest[2].f = ((decodeUB(value[2], info, 2) - info->minSnormValue(2)) * info->m_ooMaxUnormValue[2]) * 2.0 - 1.0;
		dest[3].f = ((decodeUB(value[3], info, 3) - info->minSnormValue(3)) * info->m_ooMaxUnormValue[3]) * 2.0 - 1.0;
	}

	void decodeTextureChannelsUBInt(DataFormatInterpreter::Reg32* __restrict dest, const uint32_t* __restrict value, const SurfaceFormatInfo* __restrict info)
	{
		dest[0].i = decodeUB(value[0], info, 0);
		dest[1].i = decodeUB(value[1], info, 1);
		dest[2].i = decodeUB(value[2], info, 2);
		dest[3].i = decodeUB(value[3], info, 3);
	}

	void decodeTextureChannelsUBScaled(DataFormatInterpreter::Reg32* __restrict dest, const uint32_t* __restrict value, const SurfaceFormatInfo* __restrict info)
	{
		dest[0].f = decodeUB(value[0], info, 0);
		dest[1].f = decodeUB(value[1], info, 1);
		dest[2].f = decodeUB(value[2], info, 2);
		dest[3].f = decodeUB(value[3], info, 3);
	}
}

typedef void (*DecoderFunction)(DataFormatInterpreter::Reg32* __restrict dest, const uint32_t* __restrict value, const SurfaceFormatInfo* __restrict info);
static const DecoderFunction decoderFunction[] =
{
	decodeTextureChannelsUNorm,
	decodeTextureChannelsSNorm,
	decodeTextureChannelsUScaled,
	decodeTextureChannelsSScaled,
	decodeTextureChannelsUInt,
	decodeTextureChannelsSInt,
	decodeTextureChannelsSNormNoZero,
	decodeTextureChannelsFloat,
	0,
	decodeTextureChannelsSrgb,
	decodeTextureChannelsUBNorm,
	decodeTextureChannelsUBNormNoZero,
	decodeTextureChannelsUBInt,
	decodeTextureChannelsUBScaled,
};

namespace
{
	void decodeTextureChannels(DataFormatInterpreter::Reg32* __restrict dest, const uint32_t* __restrict value, const SurfaceFormatInfo* __restrict info, const sce::Gnm::TextureChannelType textureChannelType)
	{
		BX_ASSERT(textureChannelType < sizeof(decoderFunction) / sizeof(decoderFunction[0]), "textureChannelType %d overflow of decoderFunction array", textureChannelType);
		BX_ASSERT(decoderFunction[textureChannelType] != 0, "decoderFunction[%d] is null function", textureChannelType);
		decoderFunction[textureChannelType](dest, value, info);
	}

	void encodeTextureChannelsUNorm(uint32_t* __restrict dest, const DataFormatInterpreter::Reg32* __restrict value, const SurfaceFormatInfo* __restrict info)
	{
		dest[0] = encodeU(roundDoubleToUint(clamp((double)value[0].f, 0.0, 1.0) * info->maxUnormValue(0)), info, 0);
		dest[1] = encodeU(roundDoubleToUint(clamp((double)value[1].f, 0.0, 1.0) * info->maxUnormValue(1)), info, 1);
		dest[2] = encodeU(roundDoubleToUint(clamp((double)value[2].f, 0.0, 1.0) * info->maxUnormValue(2)), info, 2);
		dest[3] = encodeU(roundDoubleToUint(clamp((double)value[3].f, 0.0, 1.0) * info->maxUnormValue(3)), info, 3);
	}

	void encodeTextureChannelsSNorm(uint32_t* __restrict dest, const DataFormatInterpreter::Reg32* __restrict value, const SurfaceFormatInfo* __restrict info)
	{
		dest[0] = encodeS(roundDoubleToInt(clamp((double)value[0].f, -1.0, 1.0) * info->maxSnormValue(0)), info, 0);
		dest[1] = encodeS(roundDoubleToInt(clamp((double)value[1].f, -1.0, 1.0) * info->maxSnormValue(1)), info, 1);
		dest[2] = encodeS(roundDoubleToInt(clamp((double)value[2].f, -1.0, 1.0) * info->maxSnormValue(2)), info, 2);
		dest[3] = encodeS(roundDoubleToInt(clamp((double)value[3].f, -1.0, 1.0) * info->maxSnormValue(3)), info, 3);
	}

	void encodeTextureChannelsUScaled(uint32_t* __restrict dest, const DataFormatInterpreter::Reg32* __restrict value, const SurfaceFormatInfo* __restrict info)
	{
		dest[0] = encodeU(roundDoubleToUint(clamp((double)value[0].f, 0.0, (double)info->maxUnormValue(0))), info, 0);
		dest[1] = encodeU(roundDoubleToUint(clamp((double)value[1].f, 0.0, (double)info->maxUnormValue(1))), info, 1);
		dest[2] = encodeU(roundDoubleToUint(clamp((double)value[2].f, 0.0, (double)info->maxUnormValue(2))), info, 2);
		dest[3] = encodeU(roundDoubleToUint(clamp((double)value[3].f, 0.0, (double)info->maxUnormValue(3))), info, 3);
	}

	void encodeTextureChannelsSScaled(uint32_t* __restrict dest, const DataFormatInterpreter::Reg32* __restrict value, const SurfaceFormatInfo* __restrict info)
	{
		dest[0] = encodeS(roundDoubleToInt(clamp((double)value[0].f, (double)info->minSnormValue(0), (double)info->maxSnormValue(0))), info, 0);
		dest[1] = encodeS(roundDoubleToInt(clamp((double)value[1].f, (double)info->minSnormValue(1), (double)info->maxSnormValue(1))), info, 1);
		dest[2] = encodeS(roundDoubleToInt(clamp((double)value[2].f, (double)info->minSnormValue(2), (double)info->maxSnormValue(2))), info, 2);
		dest[3] = encodeS(roundDoubleToInt(clamp((double)value[3].f, (double)info->minSnormValue(3), (double)info->maxSnormValue(3))), info, 3);
	}

	void encodeTextureChannelsUInt(uint32_t* __restrict dest, const DataFormatInterpreter::Reg32* __restrict value, const SurfaceFormatInfo* __restrict info)
	{
		dest[0] = encodeU(std::min(value[0].u, info->maxUnormValue(0)), info, 0);
		dest[1] = encodeU(std::min(value[1].u, info->maxUnormValue(1)), info, 1);
		dest[2] = encodeU(std::min(value[2].u, info->maxUnormValue(2)), info, 2);
		dest[3] = encodeU(std::min(value[3].u, info->maxUnormValue(3)), info, 3);
	}

	void encodeTextureChannelsSInt(uint32_t* __restrict dest, const DataFormatInterpreter::Reg32* __restrict value, const SurfaceFormatInfo* __restrict info)
	{
		dest[0] = encodeS(clamp((double)value[0].i, (double)info->minSnormValue(0), (double)info->maxSnormValue(0)), info, 0);
		dest[1] = encodeS(clamp((double)value[1].i, (double)info->minSnormValue(1), (double)info->maxSnormValue(1)), info, 1);
		dest[2] = encodeS(clamp((double)value[2].i, (double)info->minSnormValue(2), (double)info->maxSnormValue(2)), info, 2);
		dest[3] = encodeS(clamp((double)value[3].i, (double)info->minSnormValue(3), (double)info->maxSnormValue(3)), info, 3);
	}

	void encodeTextureChannelsSNormNoZero(uint32_t* __restrict dest, const DataFormatInterpreter::Reg32* __restrict value, const SurfaceFormatInfo* __restrict info)
	{
		dest[0] = encodeS(roundDoubleToInt((clamp((double)value[0].f, -1.0, 1.0) * 0.5 + 0.5) * info->maxUnormValue(0) + info->minSnormValue(0)), info, 0);
		dest[1] = encodeS(roundDoubleToInt((clamp((double)value[1].f, -1.0, 1.0) * 0.5 + 0.5) * info->maxUnormValue(1) + info->minSnormValue(1)), info, 1);
		dest[2] = encodeS(roundDoubleToInt((clamp((double)value[2].f, -1.0, 1.0) * 0.5 + 0.5) * info->maxUnormValue(2) + info->minSnormValue(2)), info, 2);
		dest[3] = encodeS(roundDoubleToInt((clamp((double)value[3].f, -1.0, 1.0) * 0.5 + 0.5) * info->maxUnormValue(3) + info->minSnormValue(3)), info, 3);
	}

	void encodeTextureChannelsFloat(uint32_t* __restrict dest, const DataFormatInterpreter::Reg32* __restrict value, const SurfaceFormatInfo* __restrict info)
	{
		dest[0] = DataFormatInterpreter::packFloat(value[0].f, floatInfo[info->m_bits[0]].m_signBits, floatInfo[info->m_bits[0]].m_exponentBits, floatInfo[info->m_bits[0]].m_mantissaBits);
		dest[1] = DataFormatInterpreter::packFloat(value[1].f, floatInfo[info->m_bits[1]].m_signBits, floatInfo[info->m_bits[1]].m_exponentBits, floatInfo[info->m_bits[1]].m_mantissaBits);
		dest[2] = DataFormatInterpreter::packFloat(value[2].f, floatInfo[info->m_bits[2]].m_signBits, floatInfo[info->m_bits[2]].m_exponentBits, floatInfo[info->m_bits[2]].m_mantissaBits);
		dest[3] = DataFormatInterpreter::packFloat(value[3].f, floatInfo[info->m_bits[3]].m_signBits, floatInfo[info->m_bits[3]].m_exponentBits, floatInfo[info->m_bits[3]].m_mantissaBits);
	}

	void encodeTextureChannelsSrgb(uint32_t* __restrict dest, const DataFormatInterpreter::Reg32* __restrict value, const SurfaceFormatInfo* __restrict info)
	{
		dest[0] = encodeU(roundDoubleToUint(linear2sRgb(clamp((double)value[0].f, 0.0, 1.0)) * info->maxUnormValue(0)), info, 0);
		dest[1] = encodeU(roundDoubleToUint(linear2sRgb(clamp((double)value[1].f, 0.0, 1.0)) * info->maxUnormValue(1)), info, 1);
		dest[2] = encodeU(roundDoubleToUint(linear2sRgb(clamp((double)value[2].f, 0.0, 1.0)) * info->maxUnormValue(2)), info, 2);
		dest[3] = encodeU(roundDoubleToUint(clamp((double)value[3].f, 0.0, 1.0) * info->maxUnormValue(3)), info, 3);
	}

	void encodeTextureChannelsUBNorm(uint32_t* __restrict dest, const DataFormatInterpreter::Reg32* __restrict value, const SurfaceFormatInfo* __restrict info)
	{
		dest[0] = encodeUB(roundDoubleToInt(clamp((double)value[0].f, -1.0, 1.0) * info->maxSnormValue(0)), info, 0);
		dest[1] = encodeUB(roundDoubleToInt(clamp((double)value[1].f, -1.0, 1.0) * info->maxSnormValue(1)), info, 1);
		dest[2] = encodeUB(roundDoubleToInt(clamp((double)value[2].f, -1.0, 1.0) * info->maxSnormValue(2)), info, 2);
		dest[3] = encodeUB(roundDoubleToInt(clamp((double)value[3].f, -1.0, 1.0) * info->maxSnormValue(3)), info, 3);
	}

	void encodeTextureChannelsUBNormNoZero(uint32_t* __restrict dest, const DataFormatInterpreter::Reg32* __restrict value, const SurfaceFormatInfo* __restrict info)
	{
		dest[0] = encodeUB(roundDoubleToInt((clamp((double)value[0].f, -1.0, 1.0) * 0.5 + 0.5) * info->maxUnormValue(0) + info->minSnormValue(0)), info, 0);
		dest[1] = encodeUB(roundDoubleToInt((clamp((double)value[1].f, -1.0, 1.0) * 0.5 + 0.5) * info->maxUnormValue(1) + info->minSnormValue(1)), info, 1);
		dest[2] = encodeUB(roundDoubleToInt((clamp((double)value[2].f, -1.0, 1.0) * 0.5 + 0.5) * info->maxUnormValue(2) + info->minSnormValue(2)), info, 2);
		dest[3] = encodeUB(roundDoubleToInt((clamp((double)value[3].f, -1.0, 1.0) * 0.5 + 0.5) * info->maxUnormValue(3) + info->minSnormValue(3)), info, 3);
	}

	void encodeTextureChannelsUBInt(uint32_t* __restrict dest, const DataFormatInterpreter::Reg32* __restrict value, const SurfaceFormatInfo* __restrict info)
	{
		dest[0] = encodeUB(clamp((double)value[0].i, (double)info->minSnormValue(0), (double)info->maxSnormValue(0)), info, 0);
		dest[1] = encodeUB(clamp((double)value[1].i, (double)info->minSnormValue(1), (double)info->maxSnormValue(1)), info, 1);
		dest[2] = encodeUB(clamp((double)value[2].i, (double)info->minSnormValue(2), (double)info->maxSnormValue(2)), info, 2);
		dest[3] = encodeUB(clamp((double)value[3].i, (double)info->minSnormValue(3), (double)info->maxSnormValue(3)), info, 3);
	}

	void encodeTextureChannelsUBScaled(uint32_t* __restrict dest, const DataFormatInterpreter::Reg32* __restrict value, const SurfaceFormatInfo* __restrict info)
	{
		dest[0] = encodeUB(roundDoubleToInt(clamp((double)value[0].f, (double)info->minSnormValue(0), (double)info->maxSnormValue(0))), info, 0);
		dest[1] = encodeUB(roundDoubleToInt(clamp((double)value[1].f, (double)info->minSnormValue(1), (double)info->maxSnormValue(1))), info, 1);
		dest[2] = encodeUB(roundDoubleToInt(clamp((double)value[2].f, (double)info->minSnormValue(2), (double)info->maxSnormValue(2))), info, 2);
		dest[3] = encodeUB(roundDoubleToInt(clamp((double)value[3].f, (double)info->minSnormValue(3), (double)info->maxSnormValue(3))), info, 3);
	}
}

typedef void (*EncoderFunction)(uint32_t* __restrict dest, const DataFormatInterpreter::Reg32* __restrict value, const SurfaceFormatInfo* __restrict info);
static const EncoderFunction encoderFunction[] =
{
	encodeTextureChannelsUNorm,
	encodeTextureChannelsSNorm,
	encodeTextureChannelsUScaled,
	encodeTextureChannelsSScaled,
	encodeTextureChannelsUInt,
	encodeTextureChannelsSInt,
	encodeTextureChannelsSNormNoZero,
	encodeTextureChannelsFloat,
	0,
	encodeTextureChannelsSrgb,
	encodeTextureChannelsUBNorm,
	encodeTextureChannelsUBNormNoZero,
	encodeTextureChannelsUBInt,
	encodeTextureChannelsUBScaled,
};

namespace
{
	void encodeTextureChannels(uint32_t* __restrict dest, const DataFormatInterpreter::Reg32* __restrict value, const SurfaceFormatInfo* __restrict info, const sce::Gnm::TextureChannelType textureChannelType)
	{
		BX_ASSERT(textureChannelType < sizeof(encoderFunction) / sizeof(encoderFunction[0]), "textureChannelType %d overflow of array encoderFunction", textureChannelType);
		BX_ASSERT(encoderFunction[textureChannelType] != 0, "encoderFunction[%d] is null function", textureChannelType);
		encoderFunction[textureChannelType](dest, value, info);
	}

	void swizzleRegs(DataFormatInterpreter::Reg32* __restrict dest, const DataFormatInterpreter::Reg32* __restrict src, const sce::Gnm::DataFormat dataFormat)
	{
		const float swizzle[] = { 0.f, 1.f, 0.f, 0.f, src[0].f, src[1].f, src[2].f, src[3].f };
		dest[0].f = swizzle[dataFormat.getChannel(0)];
		dest[1].f = swizzle[dataFormat.getChannel(1)];
		dest[2].f = swizzle[dataFormat.getChannel(2)];
		dest[3].f = swizzle[dataFormat.getChannel(3)];
	}

	void packBitfields(uint32_t* __restrict dest, const uint32_t* __restrict src, const SurfaceFormatInfo* __restrict info)
	{
		dest[0] = dest[1] = dest[2] = dest[3] = 0;
		dest[info->m_offset[0] / 32] |= src[0] << (info->m_offset[0] % 32);
		dest[info->m_offset[1] / 32] |= src[1] << (info->m_offset[1] % 32);
		dest[info->m_offset[2] / 32] |= src[2] << (info->m_offset[2] % 32);
		dest[info->m_offset[3] / 32] |= src[3] << (info->m_offset[3] % 32);
	}

	void unpackBitfields(uint32_t* __restrict dest, const uint32_t* __restrict src, const SurfaceFormatInfo* __restrict info)
	{
		dest[0] = (src[info->m_offset[0] / 32] >> (info->m_offset[0] % 32)) & info->maxUnormValue(0);
		dest[1] = (src[info->m_offset[1] / 32] >> (info->m_offset[1] % 32)) & info->maxUnormValue(1);
		dest[2] = (src[info->m_offset[2] / 32] >> (info->m_offset[2] % 32)) & info->maxUnormValue(2);
		dest[3] = (src[info->m_offset[3] / 32] >> (info->m_offset[3] % 32)) & info->maxUnormValue(3);
	}

	void broadcastElement(uint32_t* __restrict dest, const SurfaceFormatInfo* __restrict info)
	{
		switch (info->m_bitsPerElement)
		{
		case 8:
			dest[0] |= dest[0] << 8;
		case 16:
			dest[0] |= dest[0] << 16;
		default:
			break;
		}
	}

	void simpleEncoder(const SurfaceFormatInfo* __restrict info, uint32_t* __restrict dest, const DataFormatInterpreter::Reg32* __restrict src, const sce::Gnm::DataFormat dataFormat)
	{
		DataFormatInterpreter::Reg32 tempSrc[4];
		uint32_t tempDest[4];

		swizzleRegs(tempSrc, src, dataFormat);
		encodeTextureChannels(tempDest, tempSrc, info, dataFormat.getTextureChannelType());
		packBitfields(dest, tempDest, info);
		broadcastElement(dest, info);
	}

	void simpleDecoder(const SurfaceFormatInfo* __restrict info, DataFormatInterpreter::Reg32* __restrict dest, const uint32_t* src, const sce::Gnm::DataFormat dataFormat)
	{
		uint32_t tempSrc[4];
		DataFormatInterpreter::Reg32 tempDest[4];

		unpackBitfields(tempSrc, src, info);
		decodeTextureChannels(tempDest, tempSrc, info, dataFormat.getTextureChannelType());
		swizzleRegs(dest, tempDest, dataFormat);
	}

	void sharedExponentEncoder(const SurfaceFormatInfo* __restrict info, uint32_t* __restrict dest, const DataFormatInterpreter::Reg32* __restrict src, const sce::Gnm::DataFormat dataFormat)
	{
		DataFormatInterpreter::Reg32 tempSrc[4];
		uint32_t tempDest[4];

		swizzleRegs(tempSrc, src, dataFormat);
		encodeTextureChannelSharedExponent(tempDest, tempSrc, info);
		packBitfields(dest, tempDest, info);
		broadcastElement(dest, info);
	}

	void sharedExponentDecoder(const SurfaceFormatInfo* __restrict info, DataFormatInterpreter::Reg32* __restrict dest, const uint32_t* src, const sce::Gnm::DataFormat dataFormat)
	{
		uint32_t tempSrc[4];
		DataFormatInterpreter::Reg32 tempDest[4];

		unpackBitfields(tempSrc, src, info);
		decodeTextureChannelSharedExponent(tempDest, tempSrc, info);
		swizzleRegs(dest, tempDest, dataFormat);
	}

	void sharedChromaEncoder(const SurfaceFormatInfo* __restrict info, uint32_t* __restrict dest, const DataFormatInterpreter::Reg32* __restrict src, const sce::Gnm::DataFormat dataFormat)
	{
		DataFormatInterpreter::Reg32 tempSrc[4];
		uint32_t tempDest[4];

		swizzleRegs(tempSrc, src, dataFormat);
		encodeTextureChannels(tempDest, tempSrc, info, dataFormat.getTextureChannelType());
		packBitfields(dest, tempDest, info);
		switch (info->m_format)
		{
		case sce::Gnm::kSurfaceFormatBG_RG:
			dest[0] = ((dest[0] & 0xFFFFFF) << 8) | (((dest[0] >> 8) & 0xFF));
			break;
		case sce::Gnm::kSurfaceFormatGB_GR:
			dest[0] = ((dest[0] & 0xFFFFFF)) | (((dest[0] >> 8) & 0xFF) << 24);
			break;
		default:
			break;
		}
		broadcastElement(dest, info);
	}

	void sharedChromaDecoder(const SurfaceFormatInfo* __restrict info, DataFormatInterpreter::Reg32* __restrict dest, const uint32_t* src, const sce::Gnm::DataFormat dataFormat)
	{
		uint32_t tempSrc[4];
		DataFormatInterpreter::Reg32 tempDest[4];

		unpackBitfields(tempSrc, src, info);
		decodeTextureChannels(tempDest, tempSrc, info, dataFormat.getTextureChannelType());
		swizzleRegs(dest, tempDest, dataFormat);
	}
}

#define NONZERO(X) ((X) ? 1 : 0)
#define SILENCE_DIVIDE_BY_ZERO_WARNING(X) ((X) ? (X) : 1)
#define MAXUNORM(X) ((uint64_t(1) << (X))-1)
#define MAXSNORM(X) (MAXUNORM(X) >> 1)
#define OOMAXUNORM(X) (1.0 / SILENCE_DIVIDE_BY_ZERO_WARNING(MAXUNORM(X)))
#define OOMAXSNORM(X) (1.0 / SILENCE_DIVIDE_BY_ZERO_WARNING(MAXSNORM(X)))
#define DEFINE_SURFACEFORMATINFO(S,X,Y,Z,W,E,D) \
	{(S), {}, NONZERO(X)+NONZERO(Y)+NONZERO(Z)+NONZERO(W), (X)+(Y)+(Z)+(W), {(X), (Y), (Z), (W)}, (E), (D), {0, (X), (X)+(Y), (X)+(Y)+(Z)}, {OOMAXUNORM(X), OOMAXUNORM(Y), OOMAXUNORM(Z), OOMAXUNORM(W)}, {OOMAXSNORM(X), OOMAXSNORM(Y), OOMAXSNORM(Z), OOMAXSNORM(W)}}

static const SurfaceFormatInfo g_surfaceFormatInfo[] =
{
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormatInvalid    ,  0,  0,  0,  0, simpleEncoder, simpleDecoder),
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormat8          ,  8,  0,  0,  0, simpleEncoder, simpleDecoder),
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormat16         , 16,  0,  0,  0, simpleEncoder, simpleDecoder),
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormat8_8        ,  8,  8,  0,  0, simpleEncoder, simpleDecoder),
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormat32         , 32,  0,  0,  0, simpleEncoder, simpleDecoder),
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormat16_16      , 16, 16,  0,  0, simpleEncoder, simpleDecoder),
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormat10_11_11   , 11, 11, 10,  0, simpleEncoder, simpleDecoder),
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormat11_11_10   , 10, 11, 11,  0, simpleEncoder, simpleDecoder),
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormat10_10_10_2 ,  2, 10, 10, 10, simpleEncoder, simpleDecoder),
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormat2_10_10_10 , 10, 10, 10,  2, simpleEncoder, simpleDecoder),
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormat8_8_8_8    ,  8,  8,  8,  8, simpleEncoder, simpleDecoder),
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormat32_32      , 32, 32,  0,  0, simpleEncoder, simpleDecoder),
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormat16_16_16_16, 16, 16, 16, 16, simpleEncoder, simpleDecoder),
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormat32_32_32   , 32, 32, 32,  0, simpleEncoder, simpleDecoder),
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormat32_32_32_32, 32, 32, 32, 32, simpleEncoder, simpleDecoder),
	{},
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormat5_6_5      ,  5,  6,  5,  0, simpleEncoder, simpleDecoder),
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormat1_5_5_5    ,  5,  5,  5,  1, simpleEncoder, simpleDecoder),
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormat5_5_5_1    ,  1,  5,  5,  5, simpleEncoder, simpleDecoder),
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormat4_4_4_4    ,  4,  4,  4,  4, simpleEncoder, simpleDecoder),
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormat8_24       , 24,  8,  0,  0, simpleEncoder, simpleDecoder),
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormat24_8       ,  8, 24,  0,  0, simpleEncoder, simpleDecoder),
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormatGB_GR      ,  8,  8,  8,  8, sharedChromaEncoder, sharedChromaDecoder),
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormatBG_RG      ,  8,  8,  8,  8, sharedChromaEncoder, sharedChromaDecoder),
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormat5_9_9_9    ,  9,  9,  9,  5, sharedExponentEncoder, sharedExponentDecoder),
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormat4_4        ,  4,  4,  0,  0, simpleEncoder, simpleDecoder),
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormat6_5_5      ,  5,  5,  6,  0, simpleEncoder, simpleDecoder),
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormat1          ,  1,  0,  0,  0, simpleEncoder, simpleDecoder),
	DEFINE_SURFACEFORMATINFO(sce::Gnm::kSurfaceFormat1Reversed  ,  1,  0,  0,  0, simpleEncoder, simpleDecoder),
};

void DataFormatInterpreter::dataFormatEncoder(uint32_t* __restrict dest, uint32_t* __restrict destDwords, const DataFormatInterpreter::Reg32* __restrict src, const sce::Gnm::DataFormat dataFormat)
{
	sce::Gnm::SurfaceFormat surfaceFormat = dataFormat.getSurfaceFormat();
	BX_ASSERT(surfaceFormat < sizeof(g_surfaceFormatInfo) / sizeof(g_surfaceFormatInfo[0]), "surfaceFormat %d overflow array g_surfaceFormatInfo");
	const SurfaceFormatInfo* info = &g_surfaceFormatInfo[surfaceFormat];
	BX_ASSERT(info->m_format == surfaceFormat, "Expected info->m_format %d == surfaceFormat %d", info->m_format, surfaceFormat);

	info->m_encoder(info, dest, src, dataFormat);
	*destDwords = info->m_bitsPerElement <= 32 ? 1 : info->m_bitsPerElement / 32;
}

void DataFormatInterpreter::dataFormatDecoder(DataFormatInterpreter::Reg32* __restrict dest, const uint32_t* __restrict src, const sce::Gnm::DataFormat dataFormat)
{
	sce::Gnm::SurfaceFormat surfaceFormat = dataFormat.getSurfaceFormat();
	BX_ASSERT(surfaceFormat < sizeof(g_surfaceFormatInfo) / sizeof(g_surfaceFormatInfo[0]), "decode surfaceFormat %d overflow array g_surfaceFormatInfo");
	const SurfaceFormatInfo* info = &g_surfaceFormatInfo[surfaceFormat];
	BX_ASSERT(info->m_format == surfaceFormat, "decode Expected info->m_format %d == surfaceFormat %d", info->m_format, surfaceFormat);

	info->m_decoder(info, dest, src, dataFormat);
}

#endif //__ORBIS__
