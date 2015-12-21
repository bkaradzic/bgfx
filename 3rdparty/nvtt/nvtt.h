#ifndef NVTT_H
#define NVTT_H

#include <stdint.h>

namespace nvtt
{
void compressBC6H(const void* _input, uint32_t _width, uint32_t _height, uint32_t _stride, void* _output);
void compressBC7(const void* _input, uint32_t _width, uint32_t _height, uint32_t _stride, void* _output);

} // namespace nvtt

#endif // NVTT_H
