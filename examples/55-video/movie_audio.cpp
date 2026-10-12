#include "movie_audio.h"

#include <bx/bx.h>
#include <bx/allocator.h>
#include "entry/entry.h"

#if BX_PLATFORM_WINDOWS
#include <windows.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <xaudio2.h>
#include <wrl/client.h>
#include <vector>

using Microsoft::WRL::ComPtr;

static HRESULT createXAudio2(IXAudio2** _engine)
{
#if defined(__MINGW32__)
	typedef HRESULT (WINAPI *XAudio2CreateFn)(IXAudio2**, UINT32, XAUDIO2_PROCESSOR);
	static HMODULE module = LoadLibraryW(L"xaudio2_9.dll");
	if (NULL == module)
	{
		return E_FAIL;
	}
	XAudio2CreateFn create = reinterpret_cast<XAudio2CreateFn>(GetProcAddress(module, "XAudio2Create") );
	return NULL != create ? create(_engine, 0, XAUDIO2_DEFAULT_PROCESSOR) : E_FAIL;
#else
	return XAudio2Create(_engine, 0, XAUDIO2_DEFAULT_PROCESSOR);
#endif
}

struct MovieAudio::Impl
{
	ComPtr<IMFSourceReader> reader;
	ComPtr<IXAudio2> engine;
	IXAudio2MasteringVoice* master = NULL;
	IXAudio2SourceVoice* voice = NULL;
	WAVEFORMATEX* format = NULL;
	std::vector<uint8_t> buffers[32];
	uint32_t nextBuffer = 0;
	uint64_t originUs = 0;
	uint64_t submittedSamples = 0;
	bool comStarted = false;
	bool mfStarted = false;
	bool paused = false;
	bool eof = false;
	bool firstSample = true;

	~Impl()
	{
		if (NULL != voice)
		{
			voice->DestroyVoice();
		}
		if (NULL != master)
		{
			master->DestroyVoice();
		}
		engine.Reset();
		reader.Reset();
		CoTaskMemFree(format);
		if (mfStarted)
		{
			MFShutdown();
		}
		if (comStarted)
		{
			CoUninitialize();
		}
	}

	bool fill()
	{
		for (uint32_t attempt = 0; !eof && attempt < 64; ++attempt)
		{
			XAUDIO2_VOICE_STATE state;
			voice->GetState(&state, XAUDIO2_VOICE_NOSAMPLESPLAYED);
			if (state.BuffersQueued >= BX_COUNTOF(buffers) )
			{
				break;
			}

			DWORD flags = 0;
			LONGLONG timestamp = 0;
			ComPtr<IMFSample> sample;
			if (FAILED(reader->ReadSample(DWORD(MF_SOURCE_READER_FIRST_AUDIO_STREAM), 0, NULL, &flags, &timestamp, &sample) )
			||  0 != (flags & (MF_SOURCE_READERF_ERROR | MF_SOURCE_READERF_CURRENTMEDIATYPECHANGED) ) )
			{
				return false;
			}
			eof = 0 != (flags & MF_SOURCE_READERF_ENDOFSTREAM);
			if (!sample)
			{
				continue;
			}

			ComPtr<IMFMediaBuffer> buffer;
			if (FAILED(sample->ConvertToContiguousBuffer(&buffer) ) )
			{
				return false;
			}
			BYTE* data = NULL;
			DWORD length = 0;
			if (FAILED(buffer->Lock(&data, NULL, &length) ) )
			{
				return false;
			}
			buffers[nextBuffer].assign(data, data + length);
			buffer->Unlock();
			if (0 == length)
			{
				continue;
			}
			if (firstSample)
			{
				originUs = timestamp > 0 ? uint64_t(timestamp / 10) : 0;
				firstSample = false;
			}

			XAUDIO2_BUFFER output = {};
			output.AudioBytes = length;
			output.pAudioData = buffers[nextBuffer].data();
			output.Flags = eof ? XAUDIO2_END_OF_STREAM : 0;
			if (FAILED(voice->SubmitSourceBuffer(&output) ) )
			{
				return false;
			}
			submittedSamples += length / format->nBlockAlign;
			nextBuffer = (nextBuffer + 1) % BX_COUNTOF(buffers);
		}
		return true;
	}
};
#else
struct MovieAudio::Impl {};
#endif

MovieAudio::MovieAudio()
	: m_impl(NULL)
{
}

MovieAudio::~MovieAudio()
{
	close();
}

bool MovieAudio::open(const char* _path)
{
	close();
#if BX_PLATFORM_WINDOWS
	m_impl = BX_NEW(entry::getAllocator(), Impl);
	const HRESULT comResult = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	m_impl->comStarted = SUCCEEDED(comResult);
	if ((FAILED(comResult) && RPC_E_CHANGED_MODE != comResult)
	||  FAILED(MFStartup(MF_VERSION) ) )
	{
		close();
		return false;
	}
	m_impl->mfStarted = true;
	const int length = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, _path, -1, NULL, 0);
	if (length <= 0)
	{
		close();
		return false;
	}
	std::vector<wchar_t> path(size_t(length), L'\0');
	MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, _path, -1, path.data(), length);
	ComPtr<IMFMediaType> type;
	UINT32 formatSize = 0;
	if (FAILED(MFCreateSourceReaderFromURL(path.data(), NULL, &m_impl->reader) )
	||  FAILED(m_impl->reader->SetStreamSelection(DWORD(MF_SOURCE_READER_ALL_STREAMS), FALSE) )
	||  FAILED(m_impl->reader->SetStreamSelection(DWORD(MF_SOURCE_READER_FIRST_AUDIO_STREAM), TRUE) )
	||  FAILED(MFCreateMediaType(&type) )
	||  FAILED(type->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio) )
	||  FAILED(type->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM) )
	||  FAILED(m_impl->reader->SetCurrentMediaType(DWORD(MF_SOURCE_READER_FIRST_AUDIO_STREAM), NULL, type.Get() ) )
	||  FAILED(m_impl->reader->GetCurrentMediaType(DWORD(MF_SOURCE_READER_FIRST_AUDIO_STREAM), type.ReleaseAndGetAddressOf() ) )
	||  FAILED(MFCreateWaveFormatExFromMFMediaType(type.Get(), &m_impl->format, &formatSize) )
	||  FAILED(createXAudio2(&m_impl->engine) )
	||  FAILED(m_impl->engine->CreateMasteringVoice(&m_impl->master) )
	||  FAILED(m_impl->engine->CreateSourceVoice(&m_impl->voice, m_impl->format) )
	||  !m_impl->fill()
	||  FAILED(m_impl->voice->Start() ) )
	{
		close();
		return false;
	}
	return true;
#else
	BX_UNUSED(_path);
	return false;
#endif
}

void MovieAudio::close()
{
	if (NULL != m_impl)
	{
		bx::deleteObject(entry::getAllocator(), m_impl);
		m_impl = NULL;
	}
}

bool MovieAudio::isOpen() const
{
	return NULL != m_impl;
}

void MovieAudio::setPaused(bool _paused)
{
#if BX_PLATFORM_WINDOWS
	if (isOpen() )
	{
		m_impl->paused = _paused;
		if (_paused)
		{
			m_impl->voice->Stop();
		}
		else
		{
			m_impl->voice->Start();
		}
	}
#else
	BX_UNUSED(_paused);
#endif
}

bool MovieAudio::seek(uint64_t _timeUs)
{
#if BX_PLATFORM_WINDOWS
	if (!isOpen() )
	{
		return false;
	}
	m_impl->voice->DestroyVoice();
	m_impl->voice = NULL;
	PROPVARIANT position = {};
	position.vt = VT_I8;
	position.hVal.QuadPart = LONGLONG(_timeUs * 10);
	m_impl->nextBuffer = 0;
	m_impl->originUs = _timeUs;
	m_impl->submittedSamples = 0;
	m_impl->firstSample = true;
	m_impl->eof = false;
	const GUID nullGuid = {};
	if (FAILED(m_impl->reader->SetCurrentPosition(nullGuid, position) )
	||  FAILED(m_impl->engine->CreateSourceVoice(&m_impl->voice, m_impl->format) )
	||  !m_impl->fill()
	||  (!m_impl->paused && FAILED(m_impl->voice->Start() ) ) )
	{
		close();
		return false;
	}
	return true;
#else
	BX_UNUSED(_timeUs);
	return false;
#endif
}

bool MovieAudio::tick()
{
#if BX_PLATFORM_WINDOWS
	return isOpen() && m_impl->fill();
#else
	return false;
#endif
}

bool MovieAudio::finished() const
{
#if BX_PLATFORM_WINDOWS
	if (isOpen() && m_impl->eof)
	{
		XAUDIO2_VOICE_STATE state;
		m_impl->voice->GetState(&state, XAUDIO2_VOICE_NOSAMPLESPLAYED);
		return 0 == state.BuffersQueued;
	}
#endif
	return false;
}

uint64_t MovieAudio::positionUs() const
{
#if BX_PLATFORM_WINDOWS
	if (isOpen() )
	{
		XAUDIO2_VOICE_STATE state;
		m_impl->voice->GetState(&state);
		const uint64_t samples = m_impl->eof && 0 == state.BuffersQueued
			? m_impl->submittedSamples
			: state.SamplesPlayed;
		return m_impl->originUs + samples * 1000000 / m_impl->format->nSamplesPerSec;
	}
#endif
	return 0;
}