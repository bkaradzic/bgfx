#ifndef INDEX_BUFFER_COMPRESSION_FORMAT_H__
#define INDEX_BUFFER_COMPRESSION_FORMAT_H__
#pragma once

enum IndexBufferCompressionFormat
{
	// Per indice encoding - handles degenerates, but has worse compression/decompression speed and compression.
	IBCF_PER_INDICE_1 = 0,

	// Per triangle encoding - better compression/speed, does not handle degenerates.
	IBCF_PER_TRIANGLE_1 = 1
};

#endif // -- INDEX_BUFFER_COMPRESSION_FORMAT_H__