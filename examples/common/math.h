/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __MATH_H__
#define __MATH_H__

#define _USE_MATH_DEFINES
#include <math.h>

inline void vec3Add(float* __restrict _result, const float* __restrict _a, const float* __restrict _b)
{
	_result[0] = _a[0] + _b[0];
	_result[1] = _a[1] + _b[1];
	_result[2] = _a[2] + _b[2];
}

inline void vec3Sub(float* __restrict _result, const float* __restrict _a, const float* __restrict _b)
{
	_result[0] = _a[0] - _b[0];
	_result[1] = _a[1] - _b[1];
	_result[2] = _a[2] - _b[2];
}

inline void vec3Mul(float* __restrict _result, const float* __restrict _a, const float* __restrict _b)
{
	_result[0] = _a[0] * _b[0];
	_result[1] = _a[1] * _b[1];
	_result[2] = _a[2] * _b[2];
}

inline float vec3Dot(const float* __restrict _a, const float* __restrict _b)
{
	return _a[0]*_b[0] + _a[1]*_b[1] + _a[2]*_b[2];
}

inline void vec3Cross(float* __restrict _result, const float* __restrict _a, const float* __restrict _b)
{
	_result[0] = _a[1]*_b[2] - _a[2]*_b[1];
	_result[1] = _a[2]*_b[0] - _a[0]*_b[2];
	_result[2] = _a[0]*_b[1] - _a[1]*_b[0];
}

inline void vec3Norm(float* __restrict _result, const float* __restrict _a)
{
	float scale = 1.0f/sqrtf(vec3Dot(_a, _a) );
	_result[0] = _a[0] * scale;
	_result[1] = _a[1] * scale;
	_result[2] = _a[2] * scale;
}

inline void mtxIdentity(float* _result)
{
	memset(_result, 0, sizeof(float)*16);
	_result[0] = _result[5] = _result[10] = _result[15] = 1.0f;
}

inline void mtxLookAt(float* __restrict _result, const float* __restrict _eye, const float* __restrict _at)
{
	float tmp[4];
	vec3Sub(tmp, _at, _eye);

	float view[4];
	vec3Norm(view, tmp);

	float up[3] = { 0.0f, 1.0f, 0.0f };
	vec3Cross(tmp, up, view);

	float right[4];
	vec3Norm(right, tmp);

	vec3Cross(up, view, right);

	memset(_result, 0, sizeof(float)*16);
	_result[ 0] = right[0];
	_result[ 1] = up[0];
	_result[ 2] = view[0];

	_result[ 4] = right[1];
	_result[ 5] = up[1];
	_result[ 6] = view[1];

	_result[ 8] = right[2];
	_result[ 9] = up[2];
	_result[10] = view[2];

	_result[12] = -vec3Dot(right, _eye);
	_result[13] = -vec3Dot(up, _eye);
	_result[14] = -vec3Dot(view, _eye);
	_result[15] = 1.0f;
}

inline void mtxProj(float* _result, float _fovy, float _aspect, float _near, float _far)
{
	float height = 1.0f/tanf(_fovy*( (float)M_PI/180.0f)*0.5f);
	float width = height * 1.0f/_aspect;
	float aa = _far/(_far-_near);
	float bb = -_near * aa;

	memset(_result, 0, sizeof(float)*16);
	_result[0] = width;
	_result[5] = height;
	_result[10] = aa;
	_result[11] = 1.0f;
	_result[14] = bb;
}

void mtxRotateXY(float* _result, float _ax, float _ay)
{
	float sinx = sinf(_ax);
	float cosx = cosf(_ax);
	float siny = sinf(_ay);
	float cosy = cosf(_ay);

	memset(_result, 0, sizeof(float)*16);
	_result[ 0] = cosy;
	_result[ 2] = -siny;
	_result[ 4] = -sinx * siny;
	_result[ 5] = cosx;
	_result[ 6] = -sinx * cosy;
	_result[ 8] = cosx * siny;
	_result[ 9] = sinx;
	_result[10] = cosx * cosy;
	_result[15] = 1.0f;
}

#endif // __MATH_H__
