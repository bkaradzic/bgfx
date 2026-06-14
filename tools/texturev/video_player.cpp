/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "video_player.h"

#include <bx/allocator.h>
#include <bx/bx.h>
#include <bx/math.h>
#include <bx/timer.h>
#include <bx/debug.h>
#include <bx/file.h>

#include <entry/entry.h>

#include <tinystl/vector.h>
namespace stl = tinystl;

BX_PRAGMA_DIAGNOSTIC_PUSH();
BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4127) // warning C4127: conditional expression is constant
BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4244) // warning C4244: '=': conversion, possible loss of data
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wshadow")
#include "l-smash/lsmash.h"
BX_PRAGMA_DIAGNOSTIC_POP();

#include <h264/h264.h>

struct VideoPlayer::Impl
{
	bgfx::VideoCodec::Enum codec = bgfx::VideoCodec::Count;
	uint8_t  chroma   = 1;
	uint8_t  bitDepth = 8;
	uint8_t  profile  = 0;
	uint8_t  level    = 0;
	uint16_t width    = 0;
	uint16_t height   = 0;
	uint8_t  maxDpbSlots         = 0;
	uint8_t  maxActiveReferences = 0;
	stl::vector<uint8_t> parameterSets;

	lsmash_root_t*           root         = NULL;
	lsmash_file_parameters_t fp           = {};
	bool                     fpOpened     = false;
	uint32_t                 trackId      = 0;
	uint32_t                 lengthSize   = 4;

	stl::vector<uint8_t>     annexBScratch;

	struct Frame
	{
		uint64_t ptsUs;
		bool     isKeyframe;
	};

	stl::vector<Frame> frames;

	~Impl()
	{
		if (NULL != root)
		{
			lsmash_destroy_root(root);
			root = NULL;
		}

		if (fpOpened)
		{
			lsmash_close_file(&fp);
			fpOpened = false;
		}
	}
};

namespace
{
	const uint32_t kMaxSubmitPerCall = 1;
	const int64_t  kLookaheadUs      = 2 * 1000000;
	const int64_t  kSkipStepUs       = 8 * 1000000;
	const float    kRateStepFactor   = 1.25892541f;
	const float    kRateMin          = 0.1f;
	const float    kRateMax          = 100.0f;

	void avccToAnnexB(stl::vector<uint8_t>& _out, const uint8_t* _in, uint32_t _size, uint32_t _lengthSize)
	{
		uint32_t pos = 0;

		while (pos + _lengthSize <= _size)
		{
			uint32_t naluLen = 0;

			for (uint32_t ii = 0; ii < _lengthSize; ++ii)
			{
				naluLen = (naluLen << 8) | _in[pos + ii];
			}

			pos += _lengthSize;

			if (pos + naluLen > _size)
			{
				break;
			}

			_out.push_back(0);
			_out.push_back(0);
			_out.push_back(1);
			_out.insert(_out.end(), _in + pos, _in + pos + naluLen);

			pos += naluLen;
		}
	}

	uint32_t appendNalAsAnnexB(stl::vector<uint8_t>& _out, const uint8_t* _nal, uint32_t _nalLen)
	{
		if (NULL == _nal
		||  0 == _nalLen)
		{
			return 0;
		}

		_out.push_back(0);
		_out.push_back(0);
		_out.push_back(1);
		_out.insert(_out.end(), _nal, _nal + _nalLen);

		return 1;
	}

	void stripEmulationPrevention(stl::vector<uint8_t>& _dst, const uint8_t* _src, uint32_t _size)
	{
		_dst.clear();
		_dst.reserve(_size);

		uint32_t zeros = 0;

		for (uint32_t ii = 0; ii < _size; ++ii)
		{
			if (zeros >= 2
			&&  0x03 == _src[ii])
			{
				zeros = 0;
				continue;
			}

			zeros = (0 == _src[ii]) ? zeros + 1 : 0;
			_dst.push_back(_src[ii]);
		}
	}

	bool parseAvcC(VideoPlayer::Impl& _video, const uint8_t* _data, uint32_t _size, uint32_t& _lengthSize)
	{
		const uint32_t kBoxHeaderSize = 8;

		if (NULL == _data
		||  _size < kBoxHeaderSize + 7)
		{
			return false;
		}

		uint32_t pos = kBoxHeaderSize;
		++pos;

		const uint8_t  profileIdc = _data[pos++];
		++pos;

		const uint8_t levelIdc  = _data[pos++];
		_lengthSize             = uint32_t(_data[pos++] & 0x03) + 1;
		const uint32_t numSps   = uint32_t(_data[pos++] & 0x1f);

		_video.profile  = profileIdc;
		_video.level    = levelIdc;
		_video.chroma   = 0;
		_video.bitDepth = 8;

		bool spsParsed = false;
		stl::vector<uint8_t> rbsp;

		for (uint32_t ii = 0; ii < numSps; ++ii)
		{
			if (pos + 2 > _size)
			{
				return false;
			}

			const uint32_t nalLen = (uint32_t(_data[pos]) << 8) | uint32_t(_data[pos + 1]);
			pos += 2;

			if (pos + nalLen > _size)
			{
				return false;
			}

			appendNalAsAnnexB(_video.parameterSets, _data + pos, nalLen);

			if (!spsParsed
			&&  nalLen >= 1)
			{
				stripEmulationPrevention(rbsp, _data + pos, nalLen);

				h264::Bitstream bs;
				bs.init(rbsp.data(), rbsp.size() );

				h264::NALHeader nal;

				if (h264::read_nal_header(&nal, &bs)
				&&  h264::NAL_UNIT_TYPE_SPS == nal.type)
				{
					h264::SPS sps = {};
					h264::read_sps(&sps, &bs);

					_video.chroma =
						  3 == sps.chroma_format_idc ? 4
						: 2 == sps.chroma_format_idc ? 2
						:                              0
						;

					_video.bitDepth = uint8_t(sps.bit_depth_luma_minus8 + 8);
					spsParsed = true;
				}
			}

			pos += nalLen;
		}

		if (pos + 1 > _size)
		{
			return false;
		}

		const uint32_t numPps = _data[pos++];

		for (uint32_t ii = 0; ii < numPps; ++ii)
		{
			if (pos + 2 > _size)
			{
				return false;
			}

			const uint32_t nalLen = (uint32_t(_data[pos]) << 8) | uint32_t(_data[pos + 1]);
			pos += 2;

			if (pos + nalLen > _size)
			{
				return false;
			}

			appendNalAsAnnexB(_video.parameterSets, _data + pos, nalLen);
			pos += nalLen;
		}

		return true;
	}

	bool parseHvcC(VideoPlayer::Impl& _video, const uint8_t* _data, uint32_t _size, uint32_t& _lengthSize)
	{
		const uint32_t kBoxHeaderSize = 8;

		if (NULL == _data
		||  _size < kBoxHeaderSize + 23)
		{
			return false;
		}

		uint32_t pos = kBoxHeaderSize;
		++pos;

		const uint8_t profileByte = _data[pos++];
		const uint8_t profileIdc  = profileByte & 0x1f;
		pos += 10;

		const uint8_t levelIdc = _data[pos++];
		pos += 3;

		const uint8_t chromaFormat = _data[pos++] & 0x03;
		const uint8_t bitDepthLuma = uint8_t( (_data[pos++] & 0x07) + 8);
		pos += 3;

		const uint8_t lengthSizeByte = _data[pos++];
		_lengthSize = uint32_t(lengthSizeByte & 0x03) + 1;

		if (pos + 1 > _size)
		{
			return false;
		}

		const uint32_t numArrays = _data[pos++];

		_video.profile = profileIdc;
		_video.level   = levelIdc;
		_video.chroma  =
			  3 == chromaFormat ? 4
			: 2 == chromaFormat ? 2
			:                     0
			;
		_video.bitDepth = bitDepthLuma;

		stl::vector<uint8_t> vps;
		stl::vector<uint8_t> sps;
		stl::vector<uint8_t> pps;

		for (uint32_t aa = 0; aa < numArrays; ++aa)
		{
			if (pos + 3 > _size)
			{
				return false;
			}

			const uint8_t  arrayHdr    = _data[pos++];
			const uint8_t  nalUnitType = arrayHdr & 0x3f;
			const uint32_t numNalus    = (uint32_t(_data[pos]) << 8) | uint32_t(_data[pos + 1]);
			pos += 2;

			stl::vector<uint8_t>* dst = NULL;

			switch (nalUnitType)
			{
				case 32: dst = &vps; break;
				case 33: dst = &sps; break;
				case 34: dst = &pps; break;
				default:             break;
			}

			for (uint32_t nn = 0; nn < numNalus; ++nn)
			{
				if (pos + 2 > _size)
				{
					return false;
				}

				const uint32_t nalLen = (uint32_t(_data[pos]) << 8) | uint32_t(_data[pos + 1]);
				pos += 2;

				if (pos + nalLen > _size)
				{
					return false;
				}

				if (NULL != dst)
				{
					appendNalAsAnnexB(*dst, _data + pos, nalLen);
				}

				pos += nalLen;
			}
		}

		_video.parameterSets.insert(_video.parameterSets.end(), vps.begin(), vps.end() );
		_video.parameterSets.insert(_video.parameterSets.end(), sps.begin(), sps.end() );
		_video.parameterSets.insert(_video.parameterSets.end(), pps.begin(), pps.end() );

		return true;
	}

	bool loadVideoFile(VideoPlayer::Impl& _video, const char* _path)
	{
		lsmash_root_t* root = lsmash_create_root();

		if (NULL == root)
		{
			return false;
		}

		lsmash_file_parameters_t fp = {};

		if (lsmash_open_file(_path, 1, &fp) < 0)
		{
			lsmash_destroy_root(root);
			return false;
		}

		lsmash_file_t* fh = lsmash_set_file(root, &fp);

		if (NULL == fh)
		{
			lsmash_close_file(&fp);
			lsmash_destroy_root(root);

			return false;
		}

		if (lsmash_read_file(fh, &fp) < 0)
		{
			lsmash_close_file(&fp);
			lsmash_destroy_root(root);

			return false;
		}

		lsmash_movie_parameters_t mp;
		lsmash_initialize_movie_parameters(&mp);

		if (lsmash_get_movie_parameters(root, &mp) < 0)
		{
			lsmash_close_file(&fp);
			lsmash_destroy_root(root);

			return false;
		}

		uint32_t trackId = 0;
		lsmash_media_parameters_t md;

		for (uint32_t ii = 0; ii < mp.number_of_tracks; ++ii)
		{
			const uint32_t tid = lsmash_get_track_ID(root, ii + 1);
			if (0 == tid)
			{
				continue;
			}

			lsmash_initialize_media_parameters(&md);

			if (lsmash_get_media_parameters(root, tid, &md) < 0)
			{
				continue;
			}

			if (md.handler_type == ISOM_MEDIA_HANDLER_TYPE_VIDEO_TRACK)
			{
				trackId = tid;
				break;
			}
		}

		if (0 == trackId)
		{
			lsmash_close_file(&fp);
			lsmash_destroy_root(root);
			return false;
		}

		lsmash_summary_t* sum = lsmash_get_summary(root, trackId, 1);

		if (NULL == sum)
		{
			lsmash_close_file(&fp);
			lsmash_destroy_root(root);

			return false;
		}

		if (lsmash_check_codec_type_identical(sum->sample_type, ISOM_CODEC_TYPE_AVC1_VIDEO)
		||  lsmash_check_codec_type_identical(sum->sample_type, ISOM_CODEC_TYPE_AVC3_VIDEO)
		   )
		{
			_video.codec = bgfx::VideoCodec::H264;
		}
		else if (lsmash_check_codec_type_identical(sum->sample_type, ISOM_CODEC_TYPE_HVC1_VIDEO) )
		{
			_video.codec = bgfx::VideoCodec::H265;
		}
		else
		{
			lsmash_cleanup_summary(sum);
			lsmash_close_file(&fp);
			lsmash_destroy_root(root);

			return false;
		}

		const lsmash_video_summary_t* vsum = (const lsmash_video_summary_t*)sum;
		_video.width  = uint16_t(vsum->width);
		_video.height = uint16_t(vsum->height);

		_video.parameterSets.clear();
		uint32_t lengthSize = 4;

		if (_video.codec == bgfx::VideoCodec::H264)
		{
			for (uint32_t ii = 0; ; ++ii)
			{
				lsmash_codec_specific_t* cs = lsmash_get_codec_specific_data(sum, ii + 1);

				if (NULL == cs)
				{
					break;
				}

				if (cs->type != LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_H264)
				{
					continue;
				}

				lsmash_codec_specific_t* csRaw = (cs->format == LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED)
					? cs
					: lsmash_convert_codec_specific_format(cs, LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED)
					;

				if (NULL == csRaw)
				{
					continue;
				}

				parseAvcC(_video, csRaw->data.unstructured, csRaw->size, lengthSize);

				if (csRaw != cs)
				{
					lsmash_destroy_codec_specific_data(csRaw);
				}

				break;
			}
		}

		if (_video.codec == bgfx::VideoCodec::H265)
		{
			for (uint32_t ii = 0; ; ++ii)
			{
				lsmash_codec_specific_t* cs = lsmash_get_codec_specific_data(sum, ii + 1);

				if (NULL == cs)
				{
					break;
				}

				if (cs->type != LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_HEVC)
				{
					continue;
				}

				lsmash_codec_specific_t* csRaw = (cs->format == LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED)
					? cs
					: lsmash_convert_codec_specific_format(cs, LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED)
					;

				if (NULL == csRaw)
				{
					continue;
				}

				parseHvcC(_video, csRaw->data.unstructured, csRaw->size, lengthSize);

				if (csRaw != cs)
				{
					lsmash_destroy_codec_specific_data(csRaw);
				}

				break;
			}
		}

		_video.maxDpbSlots         = 16;
		_video.maxActiveReferences = 4;

		if (lsmash_construct_timeline(root, trackId) < 0)
		{
			lsmash_cleanup_summary(sum);
			lsmash_close_file(&fp);
			lsmash_destroy_root(root);

			return false;
		}

		const uint32_t timescale  = bx::max<uint32_t>(md.timescale, 1);
		const uint32_t numSamples = lsmash_get_sample_count_in_media_timeline(root, trackId);

		_video.frames.reserve(numSamples);
		for (uint32_t ii = 0; ii < numSamples; ++ii)
		{
			lsmash_sample_t s = {};

			if (0 != lsmash_get_sample_info_from_media_timeline(root, trackId, ii + 1, &s) )
			{
				break;
			}

			VideoPlayer::Impl::Frame frame = {};
			frame.ptsUs      = s.cts * 1000000ull / timescale;
			frame.isKeyframe = 0 != (s.prop.ra_flags & ISOM_SAMPLE_RANDOM_ACCESS_FLAG_SYNC);

			_video.frames.push_back(frame);
		}

		lsmash_cleanup_summary(sum);

		if (_video.frames.empty() )
		{
			lsmash_close_file(&fp);
			lsmash_destroy_root(root);

			return false;
		}

		_video.root       = root;
		_video.fp         = fp;
		_video.fpOpened   = true;
		_video.trackId    = trackId;
		_video.lengthSize = lengthSize;

		return true;
	}

} // namespace

VideoPlayer::VideoPlayer()
	: m_impl(NULL)
	, m_isOpen(false)
	, m_hasError(false)
	, m_paused(false)
	, m_pendingSet(false)
	, m_width(0)
	, m_height(0)
	, m_durationUs(0)
	, m_playbackTimeUs(0)
	, m_lastTickHpc(0)
	, m_nextAuToSubmit(0)
	, m_lastSetIdr(UINT32_MAX)
	, m_playbackRate(1.0f)
	, m_aMarkerUs(-1)
	, m_bMarkerUs(-1)
	, m_videoTexture(BGFX_INVALID_HANDLE)
{
}

VideoPlayer::~VideoPlayer()
{
	close();
}

bool VideoPlayer::isVideoExt(const bx::StringView& _ext)
{
	return 0 == bx::strCmpI(_ext, "mp4")
		|| 0 == bx::strCmpI(_ext, "m4v")
		;
}

bool VideoPlayer::open(const char* _filePath)
{
	close();

	m_impl = BX_NEW(entry::getAllocator(), Impl);

	if (NULL == m_impl)
	{
		m_hasError = true;
		return false;
	}

	if (!loadVideoFile(*m_impl, _filePath) )
	{
		bx::deleteObject(entry::getAllocator(), m_impl);
		m_impl = NULL;
		m_hasError = true;

		return false;
	}

	m_width  = m_impl->width;
	m_height = m_impl->height;

	const bgfx::Caps* caps = bgfx::getCaps();
	const uint32_t codecCaps = caps->codecs[m_impl->codec];

	const bool codecAvailable = true
		&& 0 != (caps->supported & BGFX_CAPS_VIDEO_DECODE)
		&& 0 != (codecCaps       & BGFX_CAPS_VIDEO_CODEC_BIT_8)
		&& 0 != (codecCaps       & BGFX_CAPS_VIDEO_CODEC_CHROMA_420)
		;
	const bool targetSupported = 0 != (caps->formats[bgfx::TextureFormat::BGRA8] & BGFX_CAPS_FORMAT_TEXTURE_VIDEO_DECODE_DST);
	const bool codecValid = bgfx::isVideoCodecValid(
		  m_impl->codec
		, m_impl->chroma
		, m_impl->bitDepth
		, m_impl->width
		, m_impl->height
		, m_impl->maxDpbSlots
		, m_impl->maxActiveReferences
		);

	if (!codecAvailable
	||  !targetSupported
	||  !codecValid)
	{
		bx::deleteObject(entry::getAllocator(), m_impl);
		m_impl = NULL;
		m_hasError = true;
		return false;
	}

	const uint32_t psSize    = uint32_t(m_impl->parameterSets.size() );
	const uint32_t totalSize = uint32_t(sizeof(bgfx::VideoDecoderInit) ) + psSize;

	const bgfx::Memory* mem = bgfx::alloc(totalSize);

	bgfx::VideoDecoderInit* decInit = (bgfx::VideoDecoderInit*)mem->data;
	decInit->magic             = BX_MAKEFOURCC('V', 'D', 'I', 0x0);
	decInit->codec             = m_impl->codec;
	decInit->parameterSets     = mem->data + sizeof(bgfx::VideoDecoderInit);
	decInit->parameterSetsSize = psSize;
	decInit->flags             = 0;
	decInit->cachedAuBytes     = 0;

	bx::memCopy(
		  mem->data + sizeof(bgfx::VideoDecoderInit)
		, m_impl->parameterSets.data()
		, psSize
		);

	m_videoTexture = bgfx::createTexture2D(
		  m_width
		, m_height
		, false
		, 1
		, bgfx::TextureFormat::BGRA8
		, BGFX_SAMPLER_U_CLAMP
		| BGFX_SAMPLER_V_CLAMP
		, mem
		);

	if (!bgfx::isValid(m_videoTexture) )
	{
		bx::deleteObject(entry::getAllocator(), m_impl);
		m_impl     = NULL;
		m_hasError = true;

		return false;
	}

	m_durationUs     = m_impl->frames.back().ptsUs;
	m_playbackTimeUs = 0;
	m_lastTickHpc    = bx::getHPCounter();
	m_nextAuToSubmit = 0;
	m_lastSetIdr     = UINT32_MAX;
	m_playbackRate   = 1.0f;
	m_paused         = false;
	m_pendingSet     = false;
	m_aMarkerUs      = -1;
	m_bMarkerUs      = -1;
	m_isOpen         = true;
	m_hasError       = false;

	submitAccessUnitsUpTo(kLookaheadUs);

	return true;
}

void VideoPlayer::close()
{
	if (bgfx::isValid(m_videoTexture) )
	{
		bgfx::destroy(m_videoTexture);
		m_videoTexture = BGFX_INVALID_HANDLE;
	}

	if (NULL != m_impl)
	{
		bx::deleteObject(entry::getAllocator(), m_impl);
		m_impl = NULL;
	}

	m_isOpen         = false;
	m_hasError       = false;
	m_paused         = false;
	m_pendingSet     = false;
	m_width          = 0;
	m_height         = 0;
	m_durationUs     = 0;
	m_playbackTimeUs = 0;
	m_nextAuToSubmit = 0;
	m_lastSetIdr     = UINT32_MAX;
	m_playbackRate   = 1.0f;
	m_aMarkerUs      = -1;
	m_bMarkerUs      = -1;
}

bgfx::VideoCodec::Enum VideoPlayer::codec() const
{
	return NULL != m_impl ? m_impl->codec : bgfx::VideoCodec::Count;
}

uint32_t VideoPlayer::findIdrAtOrBefore(uint64_t _ptsUs) const
{
	if (NULL == m_impl
	||  m_impl->frames.empty() )
	{
		return 0;
	}

	uint32_t lastIdr = 0;

	for (uint32_t ii = 0; ii < uint32_t(m_impl->frames.size() ); ++ii)
	{
		if (m_impl->frames[ii].ptsUs > _ptsUs)
		{
			break;
		}

		if (m_impl->frames[ii].isKeyframe)
		{
			lastIdr = ii;
		}
	}

	return lastIdr;
}

uint32_t VideoPlayer::findIdrAtOrAfter(uint64_t _ptsUs) const
{
	if (NULL == m_impl
	||  m_impl->frames.empty() )
	{
		return 0;
	}

	const uint32_t numFrames = uint32_t(m_impl->frames.size() );

	for (uint32_t ii = 0; ii < numFrames; ++ii)
	{
		if (m_impl->frames[ii].ptsUs >= _ptsUs
		&&  m_impl->frames[ii].isKeyframe)
		{
			return ii;
		}
	}

	return numFrames;
}

uint32_t VideoPlayer::findFrameAtOrBefore(uint64_t _ptsUs) const
{
	if (NULL == m_impl
	||  m_impl->frames.empty() )
	{
		return 0;
	}

	const uint32_t numFrames = uint32_t(m_impl->frames.size() );
	uint32_t       result    = 0;

	for (uint32_t ii = 0; ii < numFrames; ++ii)
	{
		if (m_impl->frames[ii].ptsUs > _ptsUs)
		{
			break;
		}

		result = ii;
	}

	return result;
}

void VideoPlayer::submitDecodeFrame(uint32_t _index, bool _setPosition)
{
	const VideoPlayer::Impl::Frame& f = m_impl->frames[_index];

	lsmash_sample_t* s = lsmash_get_sample_from_media_timeline(
		  m_impl->root
		, m_impl->trackId
		, _index + 1
		);

	if (NULL == s)
	{
		return;
	}

	struct Payload
	{
		bgfx::VideoDecoderFrame frame;
		bgfx::VideoDecoderAu    au;
	};

	stl::vector<uint8_t>& scratch = m_impl->annexBScratch;
	scratch.clear();
	avccToAnnexB(scratch, s->data, s->length, m_impl->lengthSize);
	const uint32_t bitstreamSize = uint32_t(scratch.size() );
	const uint32_t totalSize     = uint32_t(sizeof(Payload) ) + bitstreamSize;

	const bgfx::Memory* mem = bgfx::alloc(totalSize);
	Payload* dstPayload     = (Payload*)mem->data;
	uint8_t* dstBitstream   = (uint8_t*)(dstPayload + 1);

	bx::memCopy(dstBitstream, scratch.data(), bitstreamSize);

	dstPayload->au.size                  = bitstreamSize;
	dstPayload->au.ptsUs                 = int64_t(f.ptsUs);
	dstPayload->frame.magic              = BX_MAKEFOURCC('V', 'D', 'F', 0x0);
	dstPayload->frame.bitstream          = dstBitstream;
	dstPayload->frame.aus                = &dstPayload->au;
	dstPayload->frame.numAus             = 1;
	dstPayload->frame.presentationTimeUs = 0;
	dstPayload->frame.flags              = _setPosition
		? BGFX_VIDEO_DECODE_FRAME_SET
		: BGFX_VIDEO_DECODE_FRAME_NONE
		;

	bgfx::updateTexture2D(
		  m_videoTexture
		, 0
		, 0
		, 0, 0
		, m_width
		, m_height
		, mem
		);

	lsmash_delete_sample(s);
}

void VideoPlayer::submitAccessUnitsUpTo(int64_t _untilPtsUs)
{
	if (NULL == m_impl)
	{
		return;
	}

	uint32_t submitted = 0;

	while (m_nextAuToSubmit < uint32_t(m_impl->frames.size() )
		&& int64_t(m_impl->frames[m_nextAuToSubmit].ptsUs) <= _untilPtsUs
		&& submitted < kMaxSubmitPerCall)
	{
		submitDecodeFrame(m_nextAuToSubmit, m_pendingSet);
		m_pendingSet = false;
		++m_nextAuToSubmit;
		++submitted;
	}
}

void VideoPlayer::submitPresentationTick(int64_t _presentationTimeUs)
{
	bgfx::VideoDecoderFrame desc = {};
	desc.magic              = BX_MAKEFOURCC('V', 'D', 'F', 0x0);
	desc.bitstream          = NULL;
	desc.aus                = NULL;
	desc.numAus             = 0;
	desc.presentationTimeUs = _presentationTimeUs;
	desc.flags              = BGFX_VIDEO_DECODE_FRAME_NONE;

	bgfx::updateTexture2D(
		  m_videoTexture
		, 0
		, 0
		, 0, 0
		, m_width
		, m_height
		, bgfx::copy(&desc, sizeof(desc) )
		);
}

void VideoPlayer::tick()
{
	if (!m_isOpen)
	{
		return;
	}

	const int64_t nowHpc   = bx::getHPCounter();
	const int64_t deltaHpc = nowHpc - m_lastTickHpc;
	m_lastTickHpc = nowHpc;

	if (!m_paused)
	{
		m_lastSetIdr = UINT32_MAX;

		const uint64_t deltaUs = uint64_t(double(deltaHpc) * 1000000.0 * double(m_playbackRate) / double(bx::getHPFrequency() ) );
		m_playbackTimeUs += deltaUs;

		if (m_aMarkerUs >= 0
		&&  m_bMarkerUs >  m_aMarkerUs
		&&  int64_t(m_playbackTimeUs) >= m_bMarkerUs)
		{
			seekTo(uint64_t(m_aMarkerUs) );
		}
		else if (m_playbackTimeUs > m_durationUs)
		{
			seekTo(m_aMarkerUs >= 0 ? uint64_t(m_aMarkerUs) : 0);
		}
	}

	submitPresentationTick(int64_t(m_playbackTimeUs) );
	submitAccessUnitsUpTo(int64_t(m_playbackTimeUs) + kLookaheadUs);
}

void VideoPlayer::seekTo(uint64_t _targetUs)
{
	if (!m_isOpen
	||  NULL == m_impl)
	{
		return;
	}

	const uint64_t target = bx::min(_targetUs, m_durationUs);

	const uint32_t idr         = findIdrAtOrBefore(target);
	const uint32_t targetFrame = findFrameAtOrBefore(target);
	const bool     needReprime =
		   targetFrame < m_nextAuToSubmit
		|| idr         > m_nextAuToSubmit
		;

	if (needReprime
	&&  idr != m_lastSetIdr)
	{
		m_nextAuToSubmit = idr;
		m_pendingSet     = true;
		m_lastSetIdr     = idr;
	}

	m_playbackTimeUs = m_paused
		? target
		: m_impl->frames[idr].ptsUs
		;
	m_lastTickHpc    = bx::getHPCounter();
}

void VideoPlayer::seekRelative(int64_t _deltaUs)
{
	if (!m_isOpen
	||  NULL == m_impl)
	{
		return;
	}

	m_lastSetIdr = UINT32_MAX;

	int64_t target = int64_t(m_playbackTimeUs) + _deltaUs;

	int64_t lo = 0;
	int64_t hi = int64_t(m_durationUs);

	if (m_aMarkerUs >= 0
	&&  m_bMarkerUs > m_aMarkerUs)
	{
		lo = m_aMarkerUs;
		hi = m_bMarkerUs;
	}

	if (_deltaUs > 0
	&&  target > hi)
	{
		seekTo(uint64_t(lo) );
		return;
	}

	target = bx::clamp(target, lo, hi);

	if (_deltaUs > 0)
	{
		const uint32_t idrBefore    = findIdrAtOrBefore(uint64_t(target) );
		const uint64_t idrBeforePts = m_impl->frames[idrBefore].ptsUs;

		if (idrBeforePts <= m_playbackTimeUs)
		{
			const uint32_t numFrames = uint32_t(m_impl->frames.size() );
			const uint32_t idrAfter  = findIdrAtOrAfter(m_playbackTimeUs + 1);

			if (idrAfter < numFrames)
			{
				m_nextAuToSubmit = idrAfter;
				m_pendingSet     = true;
				m_lastSetIdr     = idrAfter;
				m_playbackTimeUs = m_impl->frames[idrAfter].ptsUs;
				m_lastTickHpc    = bx::getHPCounter();
				return;
			}

			return;
		}
	}

	seekTo(uint64_t(target) );
}

void VideoPlayer::restart()
{
	if (!m_isOpen)
	{
		return;
	}

	m_lastSetIdr = UINT32_MAX;
	seekTo(m_aMarkerUs >= 0 ? uint64_t(m_aMarkerUs) : 0);
}

void VideoPlayer::togglePause()
{
	if (!m_isOpen)
	{
		return;
	}

	m_paused = !m_paused;

	m_lastTickHpc = bx::getHPCounter();
}

void VideoPlayer::rateUp()
{
	if (!m_isOpen)
	{
		return;
	}

	m_playbackRate = bx::min(m_playbackRate * kRateStepFactor, kRateMax);
}

void VideoPlayer::rateDown()
{
	if (!m_isOpen)
	{
		return;
	}

	m_playbackRate = bx::max(m_playbackRate / kRateStepFactor, kRateMin);
}

void VideoPlayer::cycleAbMarker()
{
	if (!m_isOpen)
	{
		return;
	}

	if (m_aMarkerUs < 0)
	{
		m_aMarkerUs = int64_t(m_playbackTimeUs);
		m_bMarkerUs = -1;
	}
	else if (m_bMarkerUs < 0)
	{
		int64_t b = int64_t(m_playbackTimeUs);

		if (b < m_aMarkerUs)
		{
			m_bMarkerUs = m_aMarkerUs;
			m_aMarkerUs = b;
		}
		else
		{
			m_bMarkerUs = b;
		}
	}
	else
	{
		m_aMarkerUs = -1;
		m_bMarkerUs = -1;
	}
}
