/*
 * Copyright 2011-2025 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef COMMON_H_HEADER_GUARD
#define COMMON_H_HEADER_GUARD

#include <bx/timer.h>
#include <bx/math.h>

#include "entry/entry.h"

struct FrameTime
{
	///
	FrameTime()
		: m_start(bx::InitNone)
		, m_last(bx::InitNone)
		, m_current(bx::getNow() )
	{
		reset();
	}

	///
	void reset()
	{
		m_start = m_current;
		frame();
	}

	///
	void frame()
	{
		m_last    = m_current;
		m_current = bx::getNow();
	}

	///
	bx::Ticks getDeltaTime() const
	{
		return m_current - m_last;
	}

	///
	bx::Ticks getDurationTime() const
	{
		return m_current - m_start;
	}

	bx::Ticks m_start;
	bx::Ticks m_last;
	bx::Ticks m_current;
};

#endif // COMMON_H_HEADER_GUARD
