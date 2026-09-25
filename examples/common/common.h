/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
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
		m_current = bx::getNow();
		m_start   = m_current;
		m_last    = m_current;
	}

	///
	void frame()
	{
		const bx::Ticks step = entry::getFixedTimeStep();

		m_last    = m_current;
		m_current = bx::Ticks(bx::InitZero) == step
			? bx::getNow()
			: m_current + step
			;
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
