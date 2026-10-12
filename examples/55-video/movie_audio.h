#ifndef MOVIE_AUDIO_H_HEADER_GUARD
#define MOVIE_AUDIO_H_HEADER_GUARD

#include <stdint.h>

class MovieAudio
{
public:
	MovieAudio();
	~MovieAudio();
	MovieAudio(const MovieAudio&) = delete;
	MovieAudio& operator=(const MovieAudio&) = delete;

	bool open(const char* _path);
	void close();
	void setPaused(bool _paused);
	bool seek(uint64_t _timeUs);
	bool tick();
	bool isOpen() const;
	bool finished() const;
	uint64_t positionUs() const;

private:
	struct Impl;
	Impl* m_impl;
};

#endif