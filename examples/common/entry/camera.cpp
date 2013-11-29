/*
 * Copyright 2013 Dario Manesku. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bx/timer.h>
#include "../fpumath.h"
#include "camera.h"

struct Camera
{
	struct MouseCoords
	{
		int32_t m_mx;
		int32_t m_my;
	};

	Camera()
	{
		reset();
	}

	void reset()
	{
		m_mouseNow.m_mx = 0;
		m_mouseNow.m_my = 0;
		m_mouseLast.m_mx = 0;
		m_mouseLast.m_my = 0;
		m_eye[0] = 0.0f;
		m_eye[1] = 0.0f;
		m_eye[2] = -35.0f;
		m_at[0] = 0.0f;
		m_at[1] = 0.0f;
		m_at[2] = -1.0f;
		m_up[0] = 0.0f;
		m_up[1] = 1.0f;
		m_up[2] = 0.0f;
		m_horizontalAngle = 0.01f;
		m_verticalAngle = 0.0f;
		m_mouseSpeed = 0.0020f;
		m_moveSpeed = 30.0f;
		m_keys = 0;
		m_mouseDown = false;
	}

	void setMouseState(uint32_t _mx, uint32_t _my, bool _down, bool _move)
	{
		if (_down)
		{
			m_mouseDown = true;
			m_mouseLast.m_mx = _mx;
			m_mouseLast.m_my = _my;
			m_mouseNow.m_mx = _mx;
			m_mouseNow.m_my = _my;
		}

		if (!_down && !_move)
		{
			m_mouseDown = false;
		}

		if (m_mouseDown && _move)
		{
			m_mouseNow.m_mx = _mx;
			m_mouseNow.m_my = _my;
		}
	}

	void setKeyState(uint8_t _key, bool _down)
	{
		m_keys &= ~_key;
		m_keys |= _down ? _key : 0;
	}

	void update(float _deltaTime)
	{
		if (m_mouseDown)
		{
			int32_t deltaX = m_mouseNow.m_mx - m_mouseLast.m_mx;
			int32_t deltaY = m_mouseNow.m_my - m_mouseLast.m_my;

			m_horizontalAngle += m_mouseSpeed * float(deltaX);
			m_verticalAngle   -= m_mouseSpeed * float(deltaY);

			m_mouseLast.m_mx = m_mouseNow.m_mx;
			m_mouseLast.m_my = m_mouseNow.m_my;
		}

		float direction[3] =
		{
			cosf(m_verticalAngle) * sinf(m_horizontalAngle),
			sinf(m_verticalAngle),
			cosf(m_verticalAngle) * cosf(m_horizontalAngle),
		};

		float right[3] =
		{
			sinf(m_horizontalAngle - float(M_PI)/2.0f),
			0,
			cosf(m_horizontalAngle - float(M_PI)/2.0f),
		};

		if (m_keys & CAMERA_KEY_UP)
		{
			// m_eye += direction * _deltaTime * m_moveSpeed
			float tmpRhs[3];
			float tmpPos[3];
			memcpy(tmpPos, m_eye, sizeof(float)*3);
			vec3Mul(tmpRhs, direction, _deltaTime * m_moveSpeed);
			vec3Add(m_eye, tmpPos, tmpRhs);
			setKeyState(CAMERA_KEY_UP, false);
		}

		if (m_keys & CAMERA_KEY_DOWN)
		{
			// m_eye -= direction * _deltaTime * m_moveSpeed
			float tmpRhs[3];
			float tmpPos[3];
			memcpy(tmpPos, m_eye, sizeof(float)*3);
			vec3Mul(tmpRhs, direction, _deltaTime * m_moveSpeed);
			vec3Sub(m_eye, tmpPos, tmpRhs);
			setKeyState(CAMERA_KEY_DOWN, false);
		}

		if (m_keys & CAMERA_KEY_LEFT)
		{
			// m_eye += right * _deltaTime * m_moveSpeed
			float tmpRhs[3];
			float tmpPos[3];
			memcpy(tmpPos, m_eye, sizeof(float)*3);
			vec3Mul(tmpRhs, right, _deltaTime * m_moveSpeed);
			vec3Add(m_eye, tmpPos, tmpRhs);
			setKeyState(CAMERA_KEY_LEFT, false);
		}

		if (m_keys & CAMERA_KEY_RIGHT)
		{
			// m_eye -= right * _deltaTime * m_moveSpeed
			float tmpRhs[3];
			float tmpPos[3];
			memcpy(tmpPos, m_eye, sizeof(float)*3);
			vec3Mul(tmpRhs, right, _deltaTime * m_moveSpeed);
			vec3Sub(m_eye, tmpPos, tmpRhs);
			setKeyState(CAMERA_KEY_RIGHT, false);
		}

		vec3Add(m_at, m_eye, direction);
		vec3Cross(m_up, right, direction);
	}

	void getViewMtx(float* _viewMtx)
	{
		mtxLookAt(_viewMtx, m_eye, m_at, m_up);
	}

	void setPosition(float* _pos)
	{
		memcpy(m_eye, _pos, sizeof(float)*3);
	}

	void setVerticalAngle(float _verticalAngle)
	{
		m_verticalAngle = _verticalAngle;
	}
	
	void setHorizontalAngle(float _horizontalAngle)
	{
		m_horizontalAngle = _horizontalAngle;
	}

	MouseCoords m_mouseNow, m_mouseLast;
	float m_eye[3];
	float m_at[3];
	float m_up[3];
	float m_horizontalAngle;
	float m_verticalAngle;
	float m_mouseSpeed;
	float m_moveSpeed;
	uint8_t m_keys;
	bool m_mouseDown;
};

static Camera s_camera;

void cameraSetPosition(float* _pos)
{
	s_camera.setPosition(_pos);
}

void cameraSetHorizontalAngle(float _horizontalAngle)
{
	s_camera.setHorizontalAngle(_horizontalAngle);
}

void cameraSetVerticalAngle(float _verticalAngle)
{
	s_camera.setVerticalAngle(_verticalAngle);
}

void cameraSetMouseState(uint32_t _mx, uint32_t _my, bool _down, bool _move)
{
	s_camera.setMouseState(_mx, _my, _down, _move);
}

void cameraSetKeyState(uint8_t _key, bool _down)
{
	s_camera.setKeyState(_key, _down);
}

void cameraGetViewMtx(float* _viewMtx)
{
	s_camera.getViewMtx(_viewMtx);
}

void cameraGetPosition(float* _pos)
{
	memcpy(_pos, s_camera.m_eye, 3*sizeof(float));
}

void cameraGetAt(float* _at)
{
	memcpy(_at, s_camera.m_at, 3*sizeof(float));
}

void cameraUpdate(float _deltaTime)
{
	s_camera.update(_deltaTime);
}
