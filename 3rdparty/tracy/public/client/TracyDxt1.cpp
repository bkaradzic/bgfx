#include "TracyDxt1.hpp"
#include "../common/TracyForceInline.hpp"

#include <assert.h>
#include <stdint.h>
#include <string.h>

#ifdef __ARM_NEON
#  include <arm_neon.h>
#endif

#if defined __AVX__ && !defined __SSE4_1__
#  define __SSE4_1__
#endif

#if defined __SSE4_1__ || defined __AVX2__
#  ifdef _MSC_VER
#    include <intrin.h>
#  else
#    include <x86intrin.h>
#    ifndef _mm256_cvtsi256_si32
#      define _mm256_cvtsi256_si32( v ) ( _mm_cvtsi128_si32( _mm256_castsi256_si128( v ) ) )
#    endif
#  endif
#endif

namespace tracy
{

static inline uint16_t to565( uint8_t r, uint8_t g, uint8_t b )
{
    return ( ( r & 0xF8 ) << 8 ) | ( ( g & 0xFC ) << 3 ) | ( b >> 3 );
}

static inline uint16_t to565( uint32_t c )
{
    return
        ( ( c & 0xF80000 ) >> 19 ) |
        ( ( c & 0x00FC00 ) >> 5 ) |
        ( ( c & 0x0000F8 ) << 8 );
}

static const uint16_t DivTable[255*3+1] = {
    0xffff, 0xffff, 0xffff, 0xffff, 0xcccc, 0xaaaa, 0x9249, 0x8000, 0x71c7, 0x6666, 0x5d17, 0x5555, 0x4ec4, 0x4924, 0x4444, 0x4000,
    0x3c3c, 0x38e3, 0x35e5, 0x3333, 0x30c3, 0x2e8b, 0x2c85, 0x2aaa, 0x28f5, 0x2762, 0x25ed, 0x2492, 0x234f, 0x2222, 0x2108, 0x2000,
    0x1f07, 0x1e1e, 0x1d41, 0x1c71, 0x1bac, 0x1af2, 0x1a41, 0x1999, 0x18f9, 0x1861, 0x17d0, 0x1745, 0x16c1, 0x1642, 0x15c9, 0x1555,
    0x14e5, 0x147a, 0x1414, 0x13b1, 0x1352, 0x12f6, 0x129e, 0x1249, 0x11f7, 0x11a7, 0x115b, 0x1111, 0x10c9, 0x1084, 0x1041, 0x1000,
    0x0fc0, 0x0f83, 0x0f48, 0x0f0f, 0x0ed7, 0x0ea0, 0x0e6c, 0x0e38, 0x0e07, 0x0dd6, 0x0da7, 0x0d79, 0x0d4c, 0x0d20, 0x0cf6, 0x0ccc,
    0x0ca4, 0x0c7c, 0x0c56, 0x0c30, 0x0c0c, 0x0be8, 0x0bc5, 0x0ba2, 0x0b81, 0x0b60, 0x0b40, 0x0b21, 0x0b02, 0x0ae4, 0x0ac7, 0x0aaa,
    0x0a8e, 0x0a72, 0x0a57, 0x0a3d, 0x0a23, 0x0a0a, 0x09f1, 0x09d8, 0x09c0, 0x09a9, 0x0991, 0x097b, 0x0964, 0x094f, 0x0939, 0x0924,
    0x090f, 0x08fb, 0x08e7, 0x08d3, 0x08c0, 0x08ad, 0x089a, 0x0888, 0x0876, 0x0864, 0x0853, 0x0842, 0x0831, 0x0820, 0x0810, 0x0800,
    0x07f0, 0x07e0, 0x07d1, 0x07c1, 0x07b3, 0x07a4, 0x0795, 0x0787, 0x0779, 0x076b, 0x075d, 0x0750, 0x0743, 0x0736, 0x0729, 0x071c,
    0x070f, 0x0703, 0x06f7, 0x06eb, 0x06df, 0x06d3, 0x06c8, 0x06bc, 0x06b1, 0x06a6, 0x069b, 0x0690, 0x0685, 0x067b, 0x0670, 0x0666,
    0x065c, 0x0652, 0x0648, 0x063e, 0x0634, 0x062b, 0x0621, 0x0618, 0x060f, 0x0606, 0x05fd, 0x05f4, 0x05eb, 0x05e2, 0x05d9, 0x05d1,
    0x05c9, 0x05c0, 0x05b8, 0x05b0, 0x05a8, 0x05a0, 0x0598, 0x0590, 0x0588, 0x0581, 0x0579, 0x0572, 0x056b, 0x0563, 0x055c, 0x0555,
    0x054e, 0x0547, 0x0540, 0x0539, 0x0532, 0x052b, 0x0525, 0x051e, 0x0518, 0x0511, 0x050b, 0x0505, 0x04fe, 0x04f8, 0x04f2, 0x04ec,
    0x04e6, 0x04e0, 0x04da, 0x04d4, 0x04ce, 0x04c8, 0x04c3, 0x04bd, 0x04b8, 0x04b2, 0x04ad, 0x04a7, 0x04a2, 0x049c, 0x0497, 0x0492,
    0x048d, 0x0487, 0x0482, 0x047d, 0x0478, 0x0473, 0x046e, 0x0469, 0x0465, 0x0460, 0x045b, 0x0456, 0x0452, 0x044d, 0x0448, 0x0444,
    0x043f, 0x043b, 0x0436, 0x0432, 0x042d, 0x0429, 0x0425, 0x0421, 0x041c, 0x0418, 0x0414, 0x0410, 0x040c, 0x0408, 0x0404, 0x0400,
    0x03fc, 0x03f8, 0x03f4, 0x03f0, 0x03ec, 0x03e8, 0x03e4, 0x03e0, 0x03dd, 0x03d9, 0x03d5, 0x03d2, 0x03ce, 0x03ca, 0x03c7, 0x03c3,
    0x03c0, 0x03bc, 0x03b9, 0x03b5, 0x03b2, 0x03ae, 0x03ab, 0x03a8, 0x03a4, 0x03a1, 0x039e, 0x039b, 0x0397, 0x0394, 0x0391, 0x038e,
    0x038b, 0x0387, 0x0384, 0x0381, 0x037e, 0x037b, 0x0378, 0x0375, 0x0372, 0x036f, 0x036c, 0x0369, 0x0366, 0x0364, 0x0361, 0x035e,
    0x035b, 0x0358, 0x0355, 0x0353, 0x0350, 0x034d, 0x034a, 0x0348, 0x0345, 0x0342, 0x0340, 0x033d, 0x033a, 0x0338, 0x0335, 0x0333,
    0x0330, 0x032e, 0x032b, 0x0329, 0x0326, 0x0324, 0x0321, 0x031f, 0x031c, 0x031a, 0x0317, 0x0315, 0x0313, 0x0310, 0x030e, 0x030c,
    0x0309, 0x0307, 0x0305, 0x0303, 0x0300, 0x02fe, 0x02fc, 0x02fa, 0x02f7, 0x02f5, 0x02f3, 0x02f1, 0x02ef, 0x02ec, 0x02ea, 0x02e8,
    0x02e6, 0x02e4, 0x02e2, 0x02e0, 0x02de, 0x02dc, 0x02da, 0x02d8, 0x02d6, 0x02d4, 0x02d2, 0x02d0, 0x02ce, 0x02cc, 0x02ca, 0x02c8,
    0x02c6, 0x02c4, 0x02c2, 0x02c0, 0x02be, 0x02bc, 0x02bb, 0x02b9, 0x02b7, 0x02b5, 0x02b3, 0x02b1, 0x02b0, 0x02ae, 0x02ac, 0x02aa,
    0x02a8, 0x02a7, 0x02a5, 0x02a3, 0x02a1, 0x02a0, 0x029e, 0x029c, 0x029b, 0x0299, 0x0297, 0x0295, 0x0294, 0x0292, 0x0291, 0x028f,
    0x028d, 0x028c, 0x028a, 0x0288, 0x0287, 0x0285, 0x0284, 0x0282, 0x0280, 0x027f, 0x027d, 0x027c, 0x027a, 0x0279, 0x0277, 0x0276,
    0x0274, 0x0273, 0x0271, 0x0270, 0x026e, 0x026d, 0x026b, 0x026a, 0x0268, 0x0267, 0x0265, 0x0264, 0x0263, 0x0261, 0x0260, 0x025e,
    0x025d, 0x025c, 0x025a, 0x0259, 0x0257, 0x0256, 0x0255, 0x0253, 0x0252, 0x0251, 0x024f, 0x024e, 0x024d, 0x024b, 0x024a, 0x0249,
    0x0247, 0x0246, 0x0245, 0x0243, 0x0242, 0x0241, 0x0240, 0x023e, 0x023d, 0x023c, 0x023b, 0x0239, 0x0238, 0x0237, 0x0236, 0x0234,
    0x0233, 0x0232, 0x0231, 0x0230, 0x022e, 0x022d, 0x022c, 0x022b, 0x022a, 0x0229, 0x0227, 0x0226, 0x0225, 0x0224, 0x0223, 0x0222,
    0x0220, 0x021f, 0x021e, 0x021d, 0x021c, 0x021b, 0x021a, 0x0219, 0x0218, 0x0216, 0x0215, 0x0214, 0x0213, 0x0212, 0x0211, 0x0210,
    0x020f, 0x020e, 0x020d, 0x020c, 0x020b, 0x020a, 0x0209, 0x0208, 0x0207, 0x0206, 0x0205, 0x0204, 0x0203, 0x0202, 0x0201, 0x0200,
    0x01ff, 0x01fe, 0x01fd, 0x01fc, 0x01fb, 0x01fa, 0x01f9, 0x01f8, 0x01f7, 0x01f6, 0x01f5, 0x01f4, 0x01f3, 0x01f2, 0x01f1, 0x01f0,
    0x01ef, 0x01ee, 0x01ed, 0x01ec, 0x01eb, 0x01ea, 0x01e9, 0x01e9, 0x01e8, 0x01e7, 0x01e6, 0x01e5, 0x01e4, 0x01e3, 0x01e2, 0x01e1,
    0x01e0, 0x01e0, 0x01df, 0x01de, 0x01dd, 0x01dc, 0x01db, 0x01da, 0x01da, 0x01d9, 0x01d8, 0x01d7, 0x01d6, 0x01d5, 0x01d4, 0x01d4,
    0x01d3, 0x01d2, 0x01d1, 0x01d0, 0x01cf, 0x01cf, 0x01ce, 0x01cd, 0x01cc, 0x01cb, 0x01cb, 0x01ca, 0x01c9, 0x01c8, 0x01c7, 0x01c7,
    0x01c6, 0x01c5, 0x01c4, 0x01c3, 0x01c3, 0x01c2, 0x01c1, 0x01c0, 0x01c0, 0x01bf, 0x01be, 0x01bd, 0x01bd, 0x01bc, 0x01bb, 0x01ba,
    0x01ba, 0x01b9, 0x01b8, 0x01b7, 0x01b7, 0x01b6, 0x01b5, 0x01b4, 0x01b4, 0x01b3, 0x01b2, 0x01b2, 0x01b1, 0x01b0, 0x01af, 0x01af,
    0x01ae, 0x01ad, 0x01ad, 0x01ac, 0x01ab, 0x01aa, 0x01aa, 0x01a9, 0x01a8, 0x01a8, 0x01a7, 0x01a6, 0x01a6, 0x01a5, 0x01a4, 0x01a4,
    0x01a3, 0x01a2, 0x01a2, 0x01a1, 0x01a0, 0x01a0, 0x019f, 0x019e, 0x019e, 0x019d, 0x019c, 0x019c, 0x019b, 0x019a, 0x019a, 0x0199,
    0x0198, 0x0198, 0x0197, 0x0197, 0x0196, 0x0195, 0x0195, 0x0194, 0x0193, 0x0193, 0x0192, 0x0192, 0x0191, 0x0190, 0x0190, 0x018f,
    0x018f, 0x018e, 0x018d, 0x018d, 0x018c, 0x018b, 0x018b, 0x018a, 0x018a, 0x0189, 0x0189, 0x0188, 0x0187, 0x0187, 0x0186, 0x0186,
    0x0185, 0x0184, 0x0184, 0x0183, 0x0183, 0x0182, 0x0182, 0x0181, 0x0180, 0x0180, 0x017f, 0x017f, 0x017e, 0x017e, 0x017d, 0x017d,
    0x017c, 0x017b, 0x017b, 0x017a, 0x017a, 0x0179, 0x0179, 0x0178, 0x0178, 0x0177, 0x0177, 0x0176, 0x0175, 0x0175, 0x0174, 0x0174,
    0x0173, 0x0173, 0x0172, 0x0172, 0x0171, 0x0171, 0x0170, 0x0170, 0x016f, 0x016f, 0x016e, 0x016e, 0x016d, 0x016d, 0x016c, 0x016c,
    0x016b, 0x016b, 0x016a, 0x016a, 0x0169, 0x0169, 0x0168, 0x0168, 0x0167, 0x0167, 0x0166, 0x0166, 0x0165, 0x0165, 0x0164, 0x0164,
    0x0163, 0x0163, 0x0162, 0x0162, 0x0161, 0x0161, 0x0160, 0x0160, 0x015f, 0x015f, 0x015e, 0x015e, 0x015d, 0x015d, 0x015d, 0x015c,
    0x015c, 0x015b, 0x015b, 0x015a, 0x015a, 0x0159, 0x0159, 0x0158, 0x0158, 0x0158, 0x0157, 0x0157, 0x0156, 0x0156
};

#if defined __ARM_NEON && defined __aarch64__
static const uint16_t DivTableNEON[255*3+1] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x1c71, 0x1af2, 0x1999, 0x1861, 0x1745, 0x1642, 0x1555, 0x147a, 0x13b1, 0x12f6, 0x1249, 0x11a7, 0x1111, 0x1084, 0x1000,
    0x0f83, 0x0f0f, 0x0ea0, 0x0e38, 0x0dd6, 0x0d79, 0x0d20, 0x0ccc, 0x0c7c, 0x0c30, 0x0be8, 0x0ba2, 0x0b60, 0x0b21, 0x0ae4, 0x0aaa,
    0x0a72, 0x0a3d, 0x0a0a, 0x09d8, 0x09a9, 0x097b, 0x094f, 0x0924, 0x08fb, 0x08d3, 0x08ad, 0x0888, 0x0864, 0x0842, 0x0820, 0x0800,
    0x07e0, 0x07c1, 0x07a4, 0x0787, 0x076b, 0x0750, 0x0736, 0x071c, 0x0703, 0x06eb, 0x06d3, 0x06bc, 0x06a6, 0x0690, 0x067b, 0x0666,
    0x0652, 0x063e, 0x062b, 0x0618, 0x0606, 0x05f4, 0x05e2, 0x05d1, 0x05c0, 0x05b0, 0x05a0, 0x0590, 0x0581, 0x0572, 0x0563, 0x0555,
    0x0547, 0x0539, 0x052b, 0x051e, 0x0511, 0x0505, 0x04f8, 0x04ec, 0x04e0, 0x04d4, 0x04c8, 0x04bd, 0x04b2, 0x04a7, 0x049c, 0x0492,
    0x0487, 0x047d, 0x0473, 0x0469, 0x0460, 0x0456, 0x044d, 0x0444, 0x043b, 0x0432, 0x0429, 0x0421, 0x0418, 0x0410, 0x0408, 0x0400,
    0x03f8, 0x03f0, 0x03e8, 0x03e0, 0x03d9, 0x03d2, 0x03ca, 0x03c3, 0x03bc, 0x03b5, 0x03ae, 0x03a8, 0x03a1, 0x039b, 0x0394, 0x038e,
    0x0387, 0x0381, 0x037b, 0x0375, 0x036f, 0x0369, 0x0364, 0x035e, 0x0358, 0x0353, 0x034d, 0x0348, 0x0342, 0x033d, 0x0338, 0x0333,
    0x032e, 0x0329, 0x0324, 0x031f, 0x031a, 0x0315, 0x0310, 0x030c, 0x0307, 0x0303, 0x02fe, 0x02fa, 0x02f5, 0x02f1, 0x02ec, 0x02e8,
    0x02e4, 0x02e0, 0x02dc, 0x02d8, 0x02d4, 0x02d0, 0x02cc, 0x02c8, 0x02c4, 0x02c0, 0x02bc, 0x02b9, 0x02b5, 0x02b1, 0x02ae, 0x02aa,
    0x02a7, 0x02a3, 0x02a0, 0x029c, 0x0299, 0x0295, 0x0292, 0x028f, 0x028c, 0x0288, 0x0285, 0x0282, 0x027f, 0x027c, 0x0279, 0x0276,
    0x0273, 0x0270, 0x026d, 0x026a, 0x0267, 0x0264, 0x0261, 0x025e, 0x025c, 0x0259, 0x0256, 0x0253, 0x0251, 0x024e, 0x024b, 0x0249,
    0x0246, 0x0243, 0x0241, 0x023e, 0x023c, 0x0239, 0x0237, 0x0234, 0x0232, 0x0230, 0x022d, 0x022b, 0x0229, 0x0226, 0x0224, 0x0222,
    0x021f, 0x021d, 0x021b, 0x0219, 0x0216, 0x0214, 0x0212, 0x0210, 0x020e, 0x020c, 0x020a, 0x0208, 0x0206, 0x0204, 0x0202, 0x0200,
    0x01fe, 0x01fc, 0x01fa, 0x01f8, 0x01f6, 0x01f4, 0x01f2, 0x01f0, 0x01ee, 0x01ec, 0x01ea, 0x01e9, 0x01e7, 0x01e5, 0x01e3, 0x01e1,
    0x01e0, 0x01de, 0x01dc, 0x01da, 0x01d9, 0x01d7, 0x01d5, 0x01d4, 0x01d2, 0x01d0, 0x01cf, 0x01cd, 0x01cb, 0x01ca, 0x01c8, 0x01c7,
    0x01c5, 0x01c3, 0x01c2, 0x01c0, 0x01bf, 0x01bd, 0x01bc, 0x01ba, 0x01b9, 0x01b7, 0x01b6, 0x01b4, 0x01b3, 0x01b2, 0x01b0, 0x01af,
    0x01ad, 0x01ac, 0x01aa, 0x01a9, 0x01a8, 0x01a6, 0x01a5, 0x01a4, 0x01a2, 0x01a1, 0x01a0, 0x019e, 0x019d, 0x019c, 0x019a, 0x0199,
    0x0198, 0x0197, 0x0195, 0x0194, 0x0193, 0x0192, 0x0190, 0x018f, 0x018e, 0x018d, 0x018b, 0x018a, 0x0189, 0x0188, 0x0187, 0x0186,
    0x0184, 0x0183, 0x0182, 0x0181, 0x0180, 0x017f, 0x017e, 0x017d, 0x017b, 0x017a, 0x0179, 0x0178, 0x0177, 0x0176, 0x0175, 0x0174,
    0x0173, 0x0172, 0x0171, 0x0170, 0x016f, 0x016e, 0x016d, 0x016c, 0x016b, 0x016a, 0x0169, 0x0168, 0x0167, 0x0166, 0x0165, 0x0164,
    0x0163, 0x0162, 0x0161, 0x0160, 0x015f, 0x015e, 0x015d, 0x015c, 0x015b, 0x015a, 0x0159, 0x0158, 0x0158, 0x0157, 0x0156, 0x0155,
    0x0154, 0x0153, 0x0152, 0x0151, 0x0150, 0x0150, 0x014f, 0x014e, 0x014d, 0x014c, 0x014b, 0x014a, 0x014a, 0x0149, 0x0148, 0x0147,
    0x0146, 0x0146, 0x0145, 0x0144, 0x0143, 0x0142, 0x0142, 0x0141, 0x0140, 0x013f, 0x013e, 0x013e, 0x013d, 0x013c, 0x013b, 0x013b,
    0x013a, 0x0139, 0x0138, 0x0138, 0x0137, 0x0136, 0x0135, 0x0135, 0x0134, 0x0133, 0x0132, 0x0132, 0x0131, 0x0130, 0x0130, 0x012f,
    0x012e, 0x012e, 0x012d, 0x012c, 0x012b, 0x012b, 0x012a, 0x0129, 0x0129, 0x0128, 0x0127, 0x0127, 0x0126, 0x0125, 0x0125, 0x0124,
    0x0123, 0x0123, 0x0122, 0x0121, 0x0121, 0x0120, 0x0120, 0x011f, 0x011e, 0x011e, 0x011d, 0x011c, 0x011c, 0x011b, 0x011b, 0x011a,
    0x0119, 0x0119, 0x0118, 0x0118, 0x0117, 0x0116, 0x0116, 0x0115, 0x0115, 0x0114, 0x0113, 0x0113, 0x0112, 0x0112, 0x0111, 0x0111,
    0x0110, 0x010f, 0x010f, 0x010e, 0x010e, 0x010d, 0x010d, 0x010c, 0x010c, 0x010b, 0x010a, 0x010a, 0x0109, 0x0109, 0x0108, 0x0108,
    0x0107, 0x0107, 0x0106, 0x0106, 0x0105, 0x0105, 0x0104, 0x0104, 0x0103, 0x0103, 0x0102, 0x0102, 0x0101, 0x0101, 0x0100, 0x0100,
    0x00ff, 0x00ff, 0x00fe, 0x00fe, 0x00fd, 0x00fd, 0x00fc, 0x00fc, 0x00fb, 0x00fb, 0x00fa, 0x00fa, 0x00f9, 0x00f9, 0x00f8, 0x00f8,
    0x00f7, 0x00f7, 0x00f6, 0x00f6, 0x00f5, 0x00f5, 0x00f4, 0x00f4, 0x00f4, 0x00f3, 0x00f3, 0x00f2, 0x00f2, 0x00f1, 0x00f1, 0x00f0,
    0x00f0, 0x00f0, 0x00ef, 0x00ef, 0x00ee, 0x00ee, 0x00ed, 0x00ed, 0x00ed, 0x00ec, 0x00ec, 0x00eb, 0x00eb, 0x00ea, 0x00ea, 0x00ea,
    0x00e9, 0x00e9, 0x00e8, 0x00e8, 0x00e7, 0x00e7, 0x00e7, 0x00e6, 0x00e6, 0x00e5, 0x00e5, 0x00e5, 0x00e4, 0x00e4, 0x00e3, 0x00e3,
    0x00e3, 0x00e2, 0x00e2, 0x00e1, 0x00e1, 0x00e1, 0x00e0, 0x00e0, 0x00e0, 0x00df, 0x00df, 0x00de, 0x00de, 0x00de, 0x00dd, 0x00dd,
    0x00dd, 0x00dc, 0x00dc, 0x00db, 0x00db, 0x00db, 0x00da, 0x00da, 0x00da, 0x00d9, 0x00d9, 0x00d9, 0x00d8, 0x00d8, 0x00d7, 0x00d7,
    0x00d7, 0x00d6, 0x00d6, 0x00d6, 0x00d5, 0x00d5, 0x00d5, 0x00d4, 0x00d4, 0x00d4, 0x00d3, 0x00d3, 0x00d3, 0x00d2, 0x00d2, 0x00d2,
    0x00d1, 0x00d1, 0x00d1, 0x00d0, 0x00d0, 0x00d0, 0x00cf, 0x00cf, 0x00cf, 0x00ce, 0x00ce, 0x00ce, 0x00cd, 0x00cd, 0x00cd, 0x00cc,
    0x00cc, 0x00cc, 0x00cb, 0x00cb, 0x00cb, 0x00ca, 0x00ca, 0x00ca, 0x00c9, 0x00c9, 0x00c9, 0x00c9, 0x00c8, 0x00c8, 0x00c8, 0x00c7,
    0x00c7, 0x00c7, 0x00c6, 0x00c6, 0x00c6, 0x00c5, 0x00c5, 0x00c5, 0x00c5, 0x00c4, 0x00c4, 0x00c4, 0x00c3, 0x00c3, 0x00c3, 0x00c3,
    0x00c2, 0x00c2, 0x00c2, 0x00c1, 0x00c1, 0x00c1, 0x00c1, 0x00c0, 0x00c0, 0x00c0, 0x00bf, 0x00bf, 0x00bf, 0x00bf, 0x00be, 0x00be,
    0x00be, 0x00bd, 0x00bd, 0x00bd, 0x00bd, 0x00bc, 0x00bc, 0x00bc, 0x00bc, 0x00bb, 0x00bb, 0x00bb, 0x00ba, 0x00ba, 0x00ba, 0x00ba,
    0x00b9, 0x00b9, 0x00b9, 0x00b9, 0x00b8, 0x00b8, 0x00b8, 0x00b8, 0x00b7, 0x00b7, 0x00b7, 0x00b7, 0x00b6, 0x00b6, 0x00b6, 0x00b6,
    0x00b5, 0x00b5, 0x00b5, 0x00b5, 0x00b4, 0x00b4, 0x00b4, 0x00b4, 0x00b3, 0x00b3, 0x00b3, 0x00b3, 0x00b2, 0x00b2, 0x00b2, 0x00b2,
    0x00b1, 0x00b1, 0x00b1, 0x00b1, 0x00b0, 0x00b0, 0x00b0, 0x00b0, 0x00af, 0x00af, 0x00af, 0x00af, 0x00ae, 0x00ae, 0x00ae, 0x00ae,
    0x00ae, 0x00ad, 0x00ad, 0x00ad, 0x00ad, 0x00ac, 0x00ac, 0x00ac, 0x00ac, 0x00ac, 0x00ab, 0x00ab, 0x00ab, 0x00ab,
};
#endif


static tracy_force_inline uint64_t ProcessRGB( const uint8_t* src )
{
#ifdef __SSE4_1__
    __m128i px0 = _mm_loadu_si128(((__m128i*)src) + 0);
    __m128i px1 = _mm_loadu_si128(((__m128i*)src) + 1);
    __m128i px2 = _mm_loadu_si128(((__m128i*)src) + 2);
    __m128i px3 = _mm_loadu_si128(((__m128i*)src) + 3);

    __m128i smask = _mm_set1_epi32( 0xF8FCF8 );
    __m128i sd0 = _mm_and_si128( px0, smask );
    __m128i sd1 = _mm_and_si128( px1, smask );
    __m128i sd2 = _mm_and_si128( px2, smask );
    __m128i sd3 = _mm_and_si128( px3, smask );

    __m128i sc = _mm_shuffle_epi32(sd0, _MM_SHUFFLE(0, 0, 0, 0));

    __m128i sc0 = _mm_cmpeq_epi8(sd0, sc);
    __m128i sc1 = _mm_cmpeq_epi8(sd1, sc);
    __m128i sc2 = _mm_cmpeq_epi8(sd2, sc);
    __m128i sc3 = _mm_cmpeq_epi8(sd3, sc);

    __m128i sm0 = _mm_and_si128(sc0, sc1);
    __m128i sm1 = _mm_and_si128(sc2, sc3);
    __m128i sm = _mm_and_si128(sm0, sm1);

    if( _mm_testc_si128(sm, _mm_set1_epi32(-1)) )
    {
        return uint64_t( to565( src[0], src[1], src[2] ) ) << 16;
    }

    __m128i amask = _mm_set1_epi32( 0xFFFFFF );
    px0 = _mm_and_si128( px0, amask );
    px1 = _mm_and_si128( px1, amask );
    px2 = _mm_and_si128( px2, amask );
    px3 = _mm_and_si128( px3, amask );

    __m128i min0 = _mm_min_epu8( px0, px1 );
    __m128i min1 = _mm_min_epu8( px2, px3 );
    __m128i min2 = _mm_min_epu8( min0, min1 );

    __m128i max0 = _mm_max_epu8( px0, px1 );
    __m128i max1 = _mm_max_epu8( px2, px3 );
    __m128i max2 = _mm_max_epu8( max0, max1 );

    __m128i min3 = _mm_shuffle_epi32( min2, _MM_SHUFFLE( 2, 3, 0, 1 ) );
    __m128i max3 = _mm_shuffle_epi32( max2, _MM_SHUFFLE( 2, 3, 0, 1 ) );
    __m128i min4 = _mm_min_epu8( min2, min3 );
    __m128i max4 = _mm_max_epu8( max2, max3 );

    __m128i min5 = _mm_shuffle_epi32( min4, _MM_SHUFFLE( 0, 0, 2, 2 ) );
    __m128i max5 = _mm_shuffle_epi32( max4, _MM_SHUFFLE( 0, 0, 2, 2 ) );
    __m128i rmin = _mm_min_epu8( min4, min5 );
    __m128i rmax = _mm_max_epu8( max4, max5 );

    __m128i range1 = _mm_subs_epu8( rmax, rmin );
    __m128i range2 = _mm_sad_epu8( rmax, rmin );

    uint32_t vrange = _mm_cvtsi128_si32( range2 ) >> 1;
    __m128i range = _mm_set1_epi16( DivTable[vrange] );

    __m128i inset1 = _mm_srli_epi16( range1, 4 );
    __m128i inset = _mm_and_si128( inset1, _mm_set1_epi8( 0xF ) );
    __m128i min = _mm_adds_epu8( rmin, inset );
    __m128i max = _mm_subs_epu8( rmax, inset );

    __m128i c0 = _mm_subs_epu8( px0, rmin );
    __m128i c1 = _mm_subs_epu8( px1, rmin );
    __m128i c2 = _mm_subs_epu8( px2, rmin );
    __m128i c3 = _mm_subs_epu8( px3, rmin );

    __m128i is0 = _mm_maddubs_epi16( c0, _mm_set1_epi8( 1 ) );
    __m128i is1 = _mm_maddubs_epi16( c1, _mm_set1_epi8( 1 ) );
    __m128i is2 = _mm_maddubs_epi16( c2, _mm_set1_epi8( 1 ) );
    __m128i is3 = _mm_maddubs_epi16( c3, _mm_set1_epi8( 1 ) );

    __m128i s0 = _mm_hadd_epi16( is0, is1 );
    __m128i s1 = _mm_hadd_epi16( is2, is3 );

    __m128i m0 = _mm_mulhi_epu16( s0, range );
    __m128i m1 = _mm_mulhi_epu16( s1, range );

    __m128i p0 = _mm_packus_epi16( m0, m1 );

    __m128i p1 = _mm_or_si128( _mm_srai_epi32( p0, 6 ), _mm_srai_epi32( p0, 12 ) );
    __m128i p2 = _mm_or_si128( _mm_srai_epi32( p0, 18 ), p0 );
    __m128i p3 = _mm_or_si128( p1, p2 );
    __m128i p =_mm_shuffle_epi8( p3, _mm_set1_epi32( 0x0C080400 ) );

    uint32_t vmin = _mm_cvtsi128_si32( min );
    uint32_t vmax = _mm_cvtsi128_si32( max );
    uint32_t vp = _mm_cvtsi128_si32( p );

    return uint64_t( ( uint64_t( to565( vmin ) ) << 16 ) | to565( vmax ) | ( uint64_t( vp ) << 32 ) );
#elif defined __ARM_NEON
#  ifdef __aarch64__
    uint8x16x4_t px = vld4q_u8( src );

    uint8x16_t lr = px.val[0];
    uint8x16_t lg = px.val[1];
    uint8x16_t lb = px.val[2];

    uint8_t rmaxr = vmaxvq_u8( lr );
    uint8_t rmaxg = vmaxvq_u8( lg );
    uint8_t rmaxb = vmaxvq_u8( lb );

    uint8_t rminr = vminvq_u8( lr );
    uint8_t rming = vminvq_u8( lg );
    uint8_t rminb = vminvq_u8( lb );

    int rr = rmaxr - rminr;
    int rg = rmaxg - rming;
    int rb = rmaxb - rminb;

    int vrange1 = rr + rg + rb;
    uint16_t vrange2 = DivTableNEON[vrange1];

    uint8_t insetr = rr >> 4;
    uint8_t insetg = rg >> 4;
    uint8_t insetb = rb >> 4;

    uint8_t minr = rminr + insetr;
    uint8_t ming = rming + insetg;
    uint8_t minb = rminb + insetb;

    uint8_t maxr = rmaxr - insetr;
    uint8_t maxg = rmaxg - insetg;
    uint8_t maxb = rmaxb - insetb;

    uint8x16_t cr = vsubq_u8( lr, vdupq_n_u8( rminr ) );
    uint8x16_t cg = vsubq_u8( lg, vdupq_n_u8( rming ) );
    uint8x16_t cb = vsubq_u8( lb, vdupq_n_u8( rminb ) );

    uint16x8_t is0l = vaddl_u8( vget_low_u8( cr ), vget_low_u8( cg ) );
    uint16x8_t is0h = vaddl_u8( vget_high_u8( cr ), vget_high_u8( cg ) );
    uint16x8_t is1l = vaddw_u8( is0l, vget_low_u8( cb ) );
    uint16x8_t is1h = vaddw_u8( is0h, vget_high_u8( cb ) );

    int16x8_t range = vdupq_n_s16( vrange2 );
    uint16x8_t m0 = vreinterpretq_u16_s16( vqdmulhq_s16( vreinterpretq_s16_u16( is1l ), range ) );
    uint16x8_t m1 = vreinterpretq_u16_s16( vqdmulhq_s16( vreinterpretq_s16_u16( is1h ), range ) );

    uint8x8_t p00 = vmovn_u16( m0 );
    uint8x8_t p01 = vmovn_u16( m1 );
    uint8x16_t p0 = vcombine_u8( p00, p01 );

    uint32x4_t p1 = vaddq_u32( vshrq_n_u32( vreinterpretq_u32_u8( p0 ), 6 ), vshrq_n_u32( vreinterpretq_u32_u8( p0 ), 12 ) );
    uint32x4_t p2 = vaddq_u32( vshrq_n_u32( vreinterpretq_u32_u8( p0 ), 18 ), vreinterpretq_u32_u8( p0 ) );
    uint32x4_t p3 = vaddq_u32( p1, p2 );

    uint16x4x2_t p4 = vuzp_u16( vget_low_u16( vreinterpretq_u16_u32( p3 ) ), vget_high_u16( vreinterpretq_u16_u32( p3 ) ) );
    uint8x8x2_t p = vuzp_u8( vreinterpret_u8_u16( p4.val[0] ), vreinterpret_u8_u16( p4.val[0] ) );

    uint32_t vp;
    vst1_lane_u32( &vp, vreinterpret_u32_u8( p.val[0] ), 0 );

    return uint64_t( ( uint64_t( to565( minr, ming, minb ) ) << 16 ) | to565( maxr, maxg, maxb ) | ( uint64_t( vp ) << 32 ) );
#  else
    uint32x4_t px0 = vld1q_u32( (uint32_t*)src );
    uint32x4_t px1 = vld1q_u32( (uint32_t*)src + 4 );
    uint32x4_t px2 = vld1q_u32( (uint32_t*)src + 8 );
    uint32x4_t px3 = vld1q_u32( (uint32_t*)src + 12 );

    uint32x4_t smask = vdupq_n_u32( 0xF8FCF8 );
    uint32x4_t sd0 = vandq_u32( smask, px0 );
    uint32x4_t sd1 = vandq_u32( smask, px1 );
    uint32x4_t sd2 = vandq_u32( smask, px2 );
    uint32x4_t sd3 = vandq_u32( smask, px3 );

    uint32x4_t sc = vdupq_n_u32( sd0[0] );

    uint32x4_t sc0 = vceqq_u32( sd0, sc );
    uint32x4_t sc1 = vceqq_u32( sd1, sc );
    uint32x4_t sc2 = vceqq_u32( sd2, sc );
    uint32x4_t sc3 = vceqq_u32( sd3, sc );

    uint32x4_t sm0 = vandq_u32( sc0, sc1 );
    uint32x4_t sm1 = vandq_u32( sc2, sc3 );
    int64x2_t sm = vreinterpretq_s64_u32( vandq_u32( sm0, sm1 ) );

    if( sm[0] == -1 && sm[1] == -1 )
    {
        return uint64_t( to565( src[0], src[1], src[2] ) ) << 16;
    }

    uint32x4_t mask = vdupq_n_u32( 0xFFFFFF );
    uint8x16_t l0 = vreinterpretq_u8_u32( vandq_u32( mask, px0 ) );
    uint8x16_t l1 = vreinterpretq_u8_u32( vandq_u32( mask, px1 ) );
    uint8x16_t l2 = vreinterpretq_u8_u32( vandq_u32( mask, px2 ) );
    uint8x16_t l3 = vreinterpretq_u8_u32( vandq_u32( mask, px3 ) );

    uint8x16_t min0 = vminq_u8( l0, l1 );
    uint8x16_t min1 = vminq_u8( l2, l3 );
    uint8x16_t min2 = vminq_u8( min0, min1 );

    uint8x16_t max0 = vmaxq_u8( l0, l1 );
    uint8x16_t max1 = vmaxq_u8( l2, l3 );
    uint8x16_t max2 = vmaxq_u8( max0, max1 );

    uint8x16_t min3 = vreinterpretq_u8_u32( vrev64q_u32( vreinterpretq_u32_u8( min2 ) ) );
    uint8x16_t max3 = vreinterpretq_u8_u32( vrev64q_u32( vreinterpretq_u32_u8( max2 ) ) );

    uint8x16_t min4 = vminq_u8( min2, min3 );
    uint8x16_t max4 = vmaxq_u8( max2, max3 );

    uint8x16_t min5 = vcombine_u8( vget_high_u8( min4 ), vget_low_u8( min4 ) );
    uint8x16_t max5 = vcombine_u8( vget_high_u8( max4 ), vget_low_u8( max4 ) );

    uint8x16_t rmin = vminq_u8( min4, min5 );
    uint8x16_t rmax = vmaxq_u8( max4, max5 );

    uint8x16_t range1 = vsubq_u8( rmax, rmin );
    uint8x8_t range2 = vget_low_u8( range1 );
    uint8x8x2_t range3 = vzip_u8( range2, vdup_n_u8( 0 ) );
    uint16x4_t range4 = vreinterpret_u16_u8( range3.val[0] );

    uint16_t vrange1;
    uint16x4_t range5 = vpadd_u16( range4, range4 );
    uint16x4_t range6 = vpadd_u16( range5, range5 );
    vst1_lane_u16( &vrange1, range6, 0 );

    uint32_t vrange2 = ( 2 << 16 ) / uint32_t( vrange1 + 1 );
    uint16x8_t range = vdupq_n_u16( vrange2 );

    uint8x16_t inset = vshrq_n_u8( range1, 4 );
    uint8x16_t min = vaddq_u8( rmin, inset );
    uint8x16_t max = vsubq_u8( rmax, inset );

    uint8x16_t c0 = vsubq_u8( l0, rmin );
    uint8x16_t c1 = vsubq_u8( l1, rmin );
    uint8x16_t c2 = vsubq_u8( l2, rmin );
    uint8x16_t c3 = vsubq_u8( l3, rmin );

    uint16x8_t is0 = vpaddlq_u8( c0 );
    uint16x8_t is1 = vpaddlq_u8( c1 );
    uint16x8_t is2 = vpaddlq_u8( c2 );
    uint16x8_t is3 = vpaddlq_u8( c3 );

    uint16x4_t is4 = vpadd_u16( vget_low_u16( is0 ), vget_high_u16( is0 ) );
    uint16x4_t is5 = vpadd_u16( vget_low_u16( is1 ), vget_high_u16( is1 ) );
    uint16x4_t is6 = vpadd_u16( vget_low_u16( is2 ), vget_high_u16( is2 ) );
    uint16x4_t is7 = vpadd_u16( vget_low_u16( is3 ), vget_high_u16( is3 ) );

    uint16x8_t s0 = vcombine_u16( is4, is5 );
    uint16x8_t s1 = vcombine_u16( is6, is7 );

    uint16x8_t m0 = vreinterpretq_u16_s16( vqdmulhq_s16( vreinterpretq_s16_u16( s0 ), vreinterpretq_s16_u16( range ) ) );
    uint16x8_t m1 = vreinterpretq_u16_s16( vqdmulhq_s16( vreinterpretq_s16_u16( s1 ), vreinterpretq_s16_u16( range ) ) );

    uint8x8_t p00 = vmovn_u16( m0 );
    uint8x8_t p01 = vmovn_u16( m1 );
    uint8x16_t p0 = vcombine_u8( p00, p01 );

    uint32x4_t p1 = vaddq_u32( vshrq_n_u32( vreinterpretq_u32_u8( p0 ), 6 ), vshrq_n_u32( vreinterpretq_u32_u8( p0 ), 12 ) );
    uint32x4_t p2 = vaddq_u32( vshrq_n_u32( vreinterpretq_u32_u8( p0 ), 18 ), vreinterpretq_u32_u8( p0 ) );
    uint32x4_t p3 = vaddq_u32( p1, p2 );

    uint16x4x2_t p4 = vuzp_u16( vget_low_u16( vreinterpretq_u16_u32( p3 ) ), vget_high_u16( vreinterpretq_u16_u32( p3 ) ) );
    uint8x8x2_t p = vuzp_u8( vreinterpret_u8_u16( p4.val[0] ), vreinterpret_u8_u16( p4.val[0] ) );

    uint32_t vmin, vmax, vp;
    vst1q_lane_u32( &vmin, vreinterpretq_u32_u8( min ), 0 );
    vst1q_lane_u32( &vmax, vreinterpretq_u32_u8( max ), 0 );
    vst1_lane_u32( &vp, vreinterpret_u32_u8( p.val[0] ), 0 );

    return uint64_t( ( uint64_t( to565( vmin ) ) << 16 ) | to565( vmax ) | ( uint64_t( vp ) << 32 ) );
#  endif
#else
    uint32_t ref;
    memcpy( &ref, src, 4 );
    uint32_t refMask = ref & 0xF8FCF8;
    auto stmp = src + 4;
    for( int i=1; i<16; i++ )
    {
        uint32_t px;
        memcpy( &px, stmp, 4 );
        if( ( px & 0xF8FCF8 ) != refMask ) break;
        stmp += 4;
    }
    if( stmp == src + 64 )
    {
        return uint64_t( to565( ref ) ) << 16;
    }

    uint8_t min[3] = { src[0], src[1], src[2] };
    uint8_t max[3] = { src[0], src[1], src[2] };
    auto tmp = src + 4;
    for( int i=1; i<16; i++ )
    {
        for( int j=0; j<3; j++ )
        {
            if( tmp[j] < min[j] ) min[j] = tmp[j];
            else if( tmp[j] > max[j] ) max[j] = tmp[j];
        }
        tmp += 4;
    }

    const uint32_t range = DivTable[max[0] - min[0] + max[1] - min[1] + max[2] - min[2]];
    const uint32_t rmin = min[0] + min[1] + min[2];
    for( int i=0; i<3; i++ )
    {
        const uint8_t inset = ( max[i] - min[i] ) >> 4;
        min[i] += inset;
        max[i] -= inset;
    }

    uint32_t data = 0;
    for( int i=0; i<16; i++ )
    {
        const uint32_t c = src[0] + src[1] + src[2] - rmin;
        const uint8_t idx = ( c * range ) >> 16;
        data |= idx << (i*2);
        src += 4;
    }

    return uint64_t( ( uint64_t( to565( min[0], min[1], min[2] ) ) << 16 ) | to565( max[0], max[1], max[2] ) | ( uint64_t( data ) << 32 ) );
#endif
}

#ifdef __AVX2__
static tracy_force_inline void ProcessRGB_AVX( const uint8_t* src, char*& dst )
{
    __m256i px0 = _mm256_loadu_si256(((__m256i*)src) + 0);
    __m256i px1 = _mm256_loadu_si256(((__m256i*)src) + 1);
    __m256i px2 = _mm256_loadu_si256(((__m256i*)src) + 2);
    __m256i px3 = _mm256_loadu_si256(((__m256i*)src) + 3);

    __m256i smask = _mm256_set1_epi32( 0xF8FCF8 );
    __m256i sd0 = _mm256_and_si256( px0, smask );
    __m256i sd1 = _mm256_and_si256( px1, smask );
    __m256i sd2 = _mm256_and_si256( px2, smask );
    __m256i sd3 = _mm256_and_si256( px3, smask );

    __m256i sc = _mm256_shuffle_epi32(sd0, _MM_SHUFFLE(0, 0, 0, 0));

    __m256i sc0 = _mm256_cmpeq_epi8( sd0, sc );
    __m256i sc1 = _mm256_cmpeq_epi8( sd1, sc );
    __m256i sc2 = _mm256_cmpeq_epi8( sd2, sc );
    __m256i sc3 = _mm256_cmpeq_epi8( sd3, sc );

    __m256i sm0 = _mm256_and_si256( sc0, sc1 );
    __m256i sm1 = _mm256_and_si256( sc2, sc3 );
    __m256i sm = _mm256_and_si256( sm0, sm1 );

    const int64_t solid0 = 1 - _mm_testc_si128( _mm256_castsi256_si128( sm ), _mm_set1_epi32( -1 ) );
    const int64_t solid1 = 1 - _mm_testc_si128( _mm256_extracti128_si256( sm, 1 ), _mm_set1_epi32( -1 ) );

    if( solid0 + solid1 == 0 )
    {
        const auto c0 = uint64_t( to565( src[0], src[1], src[2] ) ) << 16;
        const auto c1 = uint64_t( to565( src[16], src[17], src[18] ) ) << 16;
        memcpy( dst, &c0, 8 );
        memcpy( dst+8, &c1, 8 );
        dst += 16;
        return;
    }

    __m256i amask = _mm256_set1_epi32( 0xFFFFFF );
    px0 = _mm256_and_si256( px0, amask );
    px1 = _mm256_and_si256( px1, amask );
    px2 = _mm256_and_si256( px2, amask );
    px3 = _mm256_and_si256( px3, amask );

    __m256i min0 = _mm256_min_epu8( px0, px1 );
    __m256i min1 = _mm256_min_epu8( px2, px3 );
    __m256i min2 = _mm256_min_epu8( min0, min1 );

    __m256i max0 = _mm256_max_epu8( px0, px1 );
    __m256i max1 = _mm256_max_epu8( px2, px3 );
    __m256i max2 = _mm256_max_epu8( max0, max1 );

    __m256i min3 = _mm256_shuffle_epi32( min2, _MM_SHUFFLE( 2, 3, 0, 1 ) );
    __m256i max3 = _mm256_shuffle_epi32( max2, _MM_SHUFFLE( 2, 3, 0, 1 ) );
    __m256i min4 = _mm256_min_epu8( min2, min3 );
    __m256i max4 = _mm256_max_epu8( max2, max3 );

    __m256i min5 = _mm256_shuffle_epi32( min4, _MM_SHUFFLE( 0, 0, 2, 2 ) );
    __m256i max5 = _mm256_shuffle_epi32( max4, _MM_SHUFFLE( 0, 0, 2, 2 ) );
    __m256i rmin = _mm256_min_epu8( min4, min5 );
    __m256i rmax = _mm256_max_epu8( max4, max5 );

    __m256i range1 = _mm256_subs_epu8( rmax, rmin );
    __m256i range2 = _mm256_sad_epu8( rmax, rmin );

    uint16_t vrange0 = DivTable[_mm256_cvtsi256_si32( range2 ) >> 1];
    uint16_t vrange1 = DivTable[_mm256_extract_epi16( range2, 8 ) >> 1];
    __m256i range00 = _mm256_set1_epi16( vrange0 );
    __m256i range = _mm256_inserti128_si256( range00, _mm_set1_epi16( vrange1 ), 1 );

    __m256i inset1 = _mm256_srli_epi16( range1, 4 );
    __m256i inset = _mm256_and_si256( inset1, _mm256_set1_epi8( 0xF ) );
    __m256i min = _mm256_adds_epu8( rmin, inset );
    __m256i max = _mm256_subs_epu8( rmax, inset );

    __m256i c0 = _mm256_subs_epu8( px0, rmin );
    __m256i c1 = _mm256_subs_epu8( px1, rmin );
    __m256i c2 = _mm256_subs_epu8( px2, rmin );
    __m256i c3 = _mm256_subs_epu8( px3, rmin );

    __m256i is0 = _mm256_maddubs_epi16( c0, _mm256_set1_epi8( 1 ) );
    __m256i is1 = _mm256_maddubs_epi16( c1, _mm256_set1_epi8( 1 ) );
    __m256i is2 = _mm256_maddubs_epi16( c2, _mm256_set1_epi8( 1 ) );
    __m256i is3 = _mm256_maddubs_epi16( c3, _mm256_set1_epi8( 1 ) );

    __m256i s0 = _mm256_hadd_epi16( is0, is1 );
    __m256i s1 = _mm256_hadd_epi16( is2, is3 );

    __m256i m0 = _mm256_mulhi_epu16( s0, range );
    __m256i m1 = _mm256_mulhi_epu16( s1, range );

    __m256i p0 = _mm256_packus_epi16( m0, m1 );

    __m256i p1 = _mm256_or_si256( _mm256_srai_epi32( p0, 6 ), _mm256_srai_epi32( p0, 12 ) );
    __m256i p2 = _mm256_or_si256( _mm256_srai_epi32( p0, 18 ), p0 );
    __m256i p3 = _mm256_or_si256( p1, p2 );
    __m256i p =_mm256_shuffle_epi8( p3, _mm256_set1_epi32( 0x0C080400 ) );

    __m256i mm0 = _mm256_unpacklo_epi8( _mm256_setzero_si256(), min );
    __m256i mm1 = _mm256_unpacklo_epi8( _mm256_setzero_si256(), max );
    __m256i mm2 = _mm256_unpacklo_epi64( mm1, mm0 );
    __m256i mmr = _mm256_slli_epi64( _mm256_srli_epi64( mm2, 11 ), 11 );
    __m256i mmg = _mm256_slli_epi64( _mm256_srli_epi64( mm2, 26 ), 5 );
    __m256i mmb = _mm256_srli_epi64( _mm256_slli_epi64( mm2, 16 ), 59 );
    __m256i mm3 = _mm256_or_si256( mmr, mmg );
    __m256i mm4 = _mm256_or_si256( mm3, mmb );
    __m256i mm5 = _mm256_shuffle_epi8( mm4, _mm256_set1_epi32( 0x09080100 ) );

    __m256i d0 = _mm256_unpacklo_epi32( mm5, p );
    __m256i d1 = _mm256_permute4x64_epi64( d0, _MM_SHUFFLE( 3, 2, 2, 0 ) );
    __m128i d2 = _mm256_castsi256_si128( d1 );

    __m128i mask = _mm_set_epi64x( 0xFFFF0000 | -solid1, 0xFFFF0000 | -solid0 );
    __m128i d3 = _mm_and_si128( d2, mask );
    _mm_storeu_si128( (__m128i*)dst, d3 );
    dst += 16;
}
#endif

void CompressImageDxt1( const char* src, char* dst, int w, int h )
{
    assert( (w % 4) == 0 && (h % 4) == 0 );

#ifdef __AVX2__
    if( w%8 == 0 )
    {
        uint32_t buf[8*4];
        int i = 0;

        auto blocks = w * h / 32;
        do
        {
            auto tmp = (char*)buf;
            memcpy( tmp,        src,          8*4 );
            memcpy( tmp + 8*4,  src + w * 4,  8*4 );
            memcpy( tmp + 16*4, src + w * 8,  8*4 );
            memcpy( tmp + 24*4, src + w * 12, 8*4 );
            src += 8*4;
            if( ++i == w/8 )
            {
                src += w * 3 * 4;
                i = 0;
            }

            ProcessRGB_AVX( (uint8_t*)buf, dst );
        }
        while( --blocks );
    }
    else
#endif
    {
        uint32_t buf[4*4];
        int i = 0;

        auto ptr = dst;
        auto blocks = w * h / 16;
        do
        {
            auto tmp = (char*)buf;
            memcpy( tmp,        src,          4*4 );
            memcpy( tmp + 4*4,  src + w * 4,  4*4 );
            memcpy( tmp + 8*4,  src + w * 8,  4*4 );
            memcpy( tmp + 12*4, src + w * 12, 4*4 );
            src += 4*4;
            if( ++i == w/4 )
            {
                src += w * 3 * 4;
                i = 0;
            }

            const auto c = ProcessRGB( (uint8_t*)buf );
            memcpy( ptr, &c, sizeof( uint64_t ) );
            ptr += sizeof( uint64_t );
        }
        while( --blocks );
    }
}

}
