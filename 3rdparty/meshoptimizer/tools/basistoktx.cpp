#include <stdexcept>
#include <string>
#include <vector>

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "basisu_format.h"
#include "khr_df.h"
#include "ktx2_format.h"

template <typename T>
static void read(const std::string& data, size_t offset, T& result)
{
	if (offset + sizeof(T) > data.size())
		throw std::out_of_range("read");

	memcpy(&result, &data[offset], sizeof(T));
}

template <typename T>
static void write(std::string& data, const T& value)
{
	data.append(reinterpret_cast<const char*>(&value), sizeof(value));
}

template <typename T>
static void write(std::string& data, size_t offset, const T& value)
{
	if (offset + sizeof(T) > data.size())
		throw std::out_of_range("write");

	memcpy(&data[offset], &value, sizeof(T));
}

static void createDfd(std::vector<uint32_t>& result, int channels, bool srgb)
{
	assert(channels <= 4);

	int descriptor_size = KHR_DF_WORD_SAMPLESTART + channels * KHR_DF_WORD_SAMPLEWORDS;

	result.clear();
	result.resize(1 + descriptor_size);

	result[0] = (1 + descriptor_size) * sizeof(uint32_t);

	uint32_t* dfd = &result[1];

	KHR_DFDSETVAL(dfd, VENDORID, KHR_DF_VENDORID_KHRONOS);
	KHR_DFDSETVAL(dfd, DESCRIPTORTYPE, KHR_DF_KHR_DESCRIPTORTYPE_BASICFORMAT);
	KHR_DFDSETVAL(dfd, VERSIONNUMBER, KHR_DF_VERSIONNUMBER_1_3);
	KHR_DFDSETVAL(dfd, DESCRIPTORBLOCKSIZE, descriptor_size * sizeof(uint32_t));
	KHR_DFDSETVAL(dfd, MODEL, KHR_DF_MODEL_RGBSDA);
	KHR_DFDSETVAL(dfd, PRIMARIES, KHR_DF_PRIMARIES_BT709);
	KHR_DFDSETVAL(dfd, TRANSFER, srgb ? KHR_DF_TRANSFER_SRGB : KHR_DF_TRANSFER_LINEAR);
	KHR_DFDSETVAL(dfd, FLAGS, KHR_DF_FLAG_ALPHA_STRAIGHT);

	static const khr_df_model_channels_e channel_enums[] = {
	    KHR_DF_CHANNEL_RGBSDA_R,
	    KHR_DF_CHANNEL_RGBSDA_G,
	    KHR_DF_CHANNEL_RGBSDA_B,
	    KHR_DF_CHANNEL_RGBSDA_A,
	};

	for (int i = 0; i < channels; ++i)
	{
		KHR_DFDSETSVAL(dfd, i, CHANNELID, channel_enums[i]);
	}
}

std::string basisToKtx(const std::string& basis, bool srgb)
{
	std::string ktx;

	basist::basis_file_header basis_header;
	read(basis, 0, basis_header);

	assert(basis_header.m_sig == basist::basis_file_header::cBASISSigValue);

	assert(basis_header.m_total_slices > 0);
	assert(basis_header.m_total_images == 1);

	assert(basis_header.m_format == 0);
	assert(basis_header.m_flags & basist::cBASISHeaderFlagETC1S);
	assert(!(basis_header.m_flags & basist::cBASISHeaderFlagYFlipped));
	assert(basis_header.m_tex_type == basist::cBASISTexType2D);

	bool has_alpha = (basis_header.m_flags & basist::cBASISHeaderFlagHasAlphaSlices) != 0;

	std::vector<basist::basis_slice_desc> slices(basis_header.m_total_slices);

	for (size_t i = 0; i < basis_header.m_total_slices; ++i)
		read(basis, basis_header.m_slice_desc_file_ofs + i * sizeof(basist::basis_slice_desc), slices[i]);

	assert(slices[0].m_level_index == 0);
	uint32_t width = slices[0].m_orig_width;
	uint32_t height = slices[0].m_orig_height;
	uint32_t levels = has_alpha ? uint32_t(slices.size()) / 2 : uint32_t(slices.size());

	KTX_header2 ktx_header = {KTX2_IDENTIFIER_REF};
	ktx_header.typeSize = 1;
	ktx_header.pixelWidth = width;
	ktx_header.pixelHeight = height;
	ktx_header.layerCount = 0;
	ktx_header.faceCount = 1;
	ktx_header.levelCount = levels;
	ktx_header.supercompressionScheme = KTX_SUPERCOMPRESSION_BASIS;

	size_t header_size = sizeof(KTX_header2) + levels * sizeof(ktxLevelIndexEntry);

	std::vector<uint32_t> dfd;
	createDfd(dfd, has_alpha ? 4 : 3, srgb);

	const char* kvp_data[][2] = {
	    {"KTXwriter", "gltfpack"},
	};

	std::string kvp;

	for (size_t i = 0; i < sizeof(kvp_data) / sizeof(kvp_data[0]); ++i)
	{
		const char* key = kvp_data[i][0];
		const char* value = kvp_data[i][1];

		write(kvp, uint32_t(strlen(key) + strlen(value) + 2));
		kvp += key;
		kvp += '\0';
		kvp += value;
		kvp += '\0';

		if (i + 1 != kvp.size())
			kvp.resize((kvp.size() + 3) & ~3);
	}

	size_t kvp_size = kvp.size();
	size_t dfd_size = dfd.size() * sizeof(uint32_t);

	size_t bgd_size =
	    sizeof(ktxBasisGlobalHeader) + sizeof(ktxBasisSliceDesc) * levels +
	    basis_header.m_endpoint_cb_file_size + basis_header.m_selector_cb_file_size + basis_header.m_tables_file_size;

	ktx_header.dataFormatDescriptor.byteOffset = uint32_t(header_size);
	ktx_header.dataFormatDescriptor.byteLength = uint32_t(dfd_size);

	ktx_header.keyValueData.byteOffset = uint32_t(header_size + dfd_size);
	ktx_header.keyValueData.byteLength = uint32_t(kvp_size);

	ktx_header.supercompressionGlobalData.byteOffset = (header_size + dfd_size + kvp_size + 7) & ~7;
	ktx_header.supercompressionGlobalData.byteLength = bgd_size;

	// KTX2 header
	write(ktx, ktx_header);

	size_t ktx_level_offset = ktx.size();

	for (size_t i = 0; i < levels; ++i)
	{
		ktxLevelIndexEntry le = {}; // This will be patched later
		write(ktx, le);
	}

	// data format descriptor
	for (size_t i = 0; i < dfd.size(); ++i)
		write(ktx, dfd[i]);

	// key/value pair data
	ktx += kvp;
	ktx.resize((ktx.size() + 7) & ~7);

	// supercompression global data
	ktxBasisGlobalHeader sgd_header = {};
	sgd_header.globalFlags = basis_header.m_flags;
	sgd_header.endpointCount = uint16_t(basis_header.m_total_endpoints);
	sgd_header.selectorCount = uint16_t(basis_header.m_total_selectors);
	sgd_header.endpointsByteLength = basis_header.m_endpoint_cb_file_size;
	sgd_header.selectorsByteLength = basis_header.m_selector_cb_file_size;
	sgd_header.tablesByteLength = basis_header.m_tables_file_size;
	sgd_header.extendedByteLength = basis_header.m_extended_file_size;

	write(ktx, sgd_header);

	size_t sgd_level_offset = ktx.size();

	for (size_t i = 0; i < levels; ++i)
	{
		ktxBasisSliceDesc sgd_slice = {}; // This will be patched later
		write(ktx, sgd_slice);
	}

	ktx.append(basis.substr(basis_header.m_endpoint_cb_file_ofs, basis_header.m_endpoint_cb_file_size));
	ktx.append(basis.substr(basis_header.m_selector_cb_file_ofs, basis_header.m_selector_cb_file_size));
	ktx.append(basis.substr(basis_header.m_tables_file_ofs, basis_header.m_tables_file_size));
	ktx.append(basis.substr(basis_header.m_extended_file_ofs, basis_header.m_extended_file_size));

	ktx.resize((ktx.size() + 7) & ~7);

	// mip levels
	for (size_t i = 0; i < levels; ++i)
	{
		size_t slice_index = (levels - i - 1) * (has_alpha + 1);
		const basist::basis_slice_desc& slice = slices[slice_index];
		const basist::basis_slice_desc* slice_alpha = has_alpha ? &slices[slice_index + 1] : 0;

		assert(slice.m_image_index == 0);
		assert(slice.m_level_index == levels - i - 1);

		size_t file_offset = ktx.size();

		ktx.append(basis.substr(slice.m_file_ofs, slice.m_file_size));

		if (slice_alpha)
			ktx.append(basis.substr(slice_alpha->m_file_ofs, slice_alpha->m_file_size));

		ktxLevelIndexEntry le = {};
		le.byteOffset = file_offset;
		le.byteLength = ktx.size() - file_offset;
		le.uncompressedByteLength = 0;

		write(ktx, ktx_level_offset + i * sizeof(ktxLevelIndexEntry), le);

		ktxBasisSliceDesc sgd_slice = {};
		sgd_slice.sliceByteOffset = 0;
		sgd_slice.sliceByteLength = slice.m_file_size;

		if (slice_alpha)
		{
			sgd_slice.alphaSliceByteOffset = slice.m_file_size;
			sgd_slice.alphaSliceByteLength = slice_alpha->m_file_size;
		}

		write(ktx, sgd_level_offset + i * sizeof(ktxBasisSliceDesc), sgd_slice);

		if (i + 1 != levels)
			ktx.resize((ktx.size() + 7) & ~7);
	}

	return ktx;
}

#ifdef STANDALONE
bool readFile(const char* path, std::string& data)
{
	FILE* file = fopen(path, "rb");
	if (!file)
		return false;

	fseek(file, 0, SEEK_END);
	long length = ftell(file);
	fseek(file, 0, SEEK_SET);

	if (length <= 0)
	{
		fclose(file);
		return false;
	}

	data.resize(length);
	size_t result = fread(&data[0], 1, data.size(), file);
	fclose(file);

	return result == data.size();
}

bool writeFile(const char* path, const std::string& data)
{
	FILE* file = fopen(path, "wb");
	if (!file)
		return false;

	size_t result = fwrite(&data[0], 1, data.size(), file);
	fclose(file);

	return result == data.size();
}

int main(int argc, const char** argv)
{
	if (argc < 2)
		return 1;

	std::string basis;
	if (!readFile(argv[1], basis))
		return 1;

	std::string ktx = basisToKtx(basis, true);

	if (!writeFile(argv[2], ktx))
		return 1;

	return 0;
}
#endif