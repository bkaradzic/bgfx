/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef TEXTUREV_VIDEO_PLAYER_H_HEADER_GUARD
#define TEXTUREV_VIDEO_PLAYER_H_HEADER_GUARD

#include <bgfx/bgfx.h>
#include <bx/string.h>

class VideoPlayer
{
public:
	VideoPlayer();
	~VideoPlayer();

	static bool isVideoExt(const bx::StringView& _ext);

	bool open(const char* _filePath);
	void close();

	bool isOpen()       const { return m_isOpen; }
	bool hasError()     const { return m_hasError; }
	uint16_t width()    const { return m_width; }
	uint16_t height()   const { return m_height; }
	bgfx::TextureHandle texture() const { return m_videoTexture; }

	void tick();

	bool isActive() const { return m_isOpen && !m_paused; }

	void seekRelative(int64_t _deltaUs);
	void seekTo(uint64_t _targetUs);

	void restart();

	void togglePause();

	void rateUp();
	void rateDown();

	void cycleAbMarker();

	uint64_t durationUs()     const { return m_durationUs; }
	uint64_t playbackTimeUs() const { return m_playbackTimeUs; }
	float    playbackRate()   const { return m_playbackRate; }
	bool     isPaused()       const { return m_paused; }

	int64_t  aMarkerUs()  const { return m_aMarkerUs; }
	int64_t  bMarkerUs()  const { return m_bMarkerUs; }
	bool     hasAMarker() const { return m_aMarkerUs >= 0; }
	bool     hasBMarker() const { return m_bMarkerUs >= 0; }

	bgfx::VideoCodec::Enum codec() const;

	struct Impl;

private:
	void submitAccessUnitsUpTo(int64_t _untilPtsUs);
	void submitPresentationTick(int64_t _presentationTimeUs);
	void submitDecodeFrame(uint32_t _index, bool _setPosition);

	uint32_t findIdrAtOrBefore(uint64_t _ptsUs) const;
	uint32_t findIdrAtOrAfter(uint64_t _ptsUs) const;

	uint32_t findFrameAtOrBefore(uint64_t _ptsUs) const;

	Impl* m_impl;
	bool  m_isOpen;
	bool  m_hasError;
	bool  m_paused;
	bool  m_pendingSet;

	uint16_t m_width;
	uint16_t m_height;

	uint64_t m_durationUs;
	uint64_t m_playbackTimeUs;
	int64_t  m_lastTickHpc;
	uint32_t m_nextAuToSubmit;

	uint32_t m_lastSetIdr;
	float    m_playbackRate;

	int64_t  m_aMarkerUs;
	int64_t  m_bMarkerUs;

	bgfx::TextureHandle m_videoTexture;
};

#endif // TEXTUREV_VIDEO_PLAYER_H_HEADER_GUARD
