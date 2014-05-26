/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

// FPU math lib

#ifndef FPU_MATH_H_HEADER_GUARD
#define FPU_MATH_H_HEADER_GUARD

#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>

#if BX_COMPILER_MSVC
inline float fminf(float _a, float _b)
{
	return _a < _b ? _a : _b;
}

inline float fmaxf(float _a, float _b)
{
	return _a > _b ? _a : _b;
}
#endif // BX_COMPILER_MSVC

inline float toRad(float _deg)
{
	return _deg * float(M_PI / 180.0);
}

inline float toDeg(float _rad)
{
	return _rad * float(180.0 / M_PI);
}

inline float fclamp(float _a, float _min, float _max)
{
	return fminf(fmaxf(_a, _min), _max);
}

inline float fsaturate(float _a)
{
	return fclamp(_a, 0.0f, 1.0f);
}

inline float flerp(float _a, float _b, float _t)
{
	return _a + (_b - _a) * _t;
}

inline float fsign(float _a)
{
	return _a < 0.0f ? -1.0f : 1.0f;
}

inline void vec3Move(float* __restrict _result, const float* __restrict _a)
{
	_result[0] = _a[0];
	_result[1] = _a[1];
	_result[2] = _a[2];
}

inline void vec3Abs(float* __restrict _result, const float* __restrict _a)
{
	_result[0] = fabsf(_a[0]);
	_result[1] = fabsf(_a[1]);
	_result[2] = fabsf(_a[2]);
}

inline void vec3Neg(float* __restrict _result, const float* __restrict _a)
{
	_result[0] = -_a[0];
	_result[1] = -_a[1];
	_result[2] = -_a[2];
}

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

inline void vec3Mul(float* __restrict _result, const float* __restrict _a, float _b)
{
	_result[0] = _a[0] * _b;
	_result[1] = _a[1] * _b;
	_result[2] = _a[2] * _b;
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

inline float vec3Length(const float* _a)
{
	return sqrtf(vec3Dot(_a, _a) );
}

inline float vec3Norm(float* __restrict _result, const float* __restrict _a)
{
	const float len = vec3Length(_a);
	const float invLen = 1.0f/len;
	_result[0] = _a[0] * invLen;
	_result[1] = _a[1] * invLen;
	_result[2] = _a[2] * invLen;
	return len;
}

inline void mtxIdentity(float* _result)
{
	memset(_result, 0, sizeof(float)*16);
	_result[0] = _result[5] = _result[10] = _result[15] = 1.0f;
}

inline void mtxTranslate(float* _result, float _tx, float _ty, float _tz)
{
	mtxIdentity(_result);
	_result[12] = _tx;
	_result[13] = _ty;
	_result[14] = _tz;
}

inline void mtxScale(float* _result, float _sx, float _sy, float _sz)
{
	memset(_result, 0, sizeof(float) * 16);
	_result[0]  = _sx;
	_result[5]  = _sy;
	_result[10] = _sz;
	_result[15] = 1.0f;
}

inline void mtxLookAt(float* __restrict _result, const float* __restrict _eye, const float* __restrict _at, const float* __restrict _up = NULL)
{
	float tmp[4];
	vec3Sub(tmp, _at, _eye);

	float view[4];
	vec3Norm(view, tmp);

	float up[3] = { 0.0f, 1.0f, 0.0f };
	if (NULL != _up)
	{
		up[0] = _up[0];
		up[1] = _up[1];
		up[2] = _up[2];
	}
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
	const float height = 1.0f/tanf(_fovy*( (float)M_PI/180.0f)*0.5f);
	const float width = height * 1.0f/_aspect;
	const float aa = _far/(_far-_near);
	const float bb = -_near * aa;

	memset(_result, 0, sizeof(float)*16);
	_result[0] = width;
	_result[5] = height;
	_result[10] = aa;
	_result[11] = 1.0f;
	_result[14] = bb;
}

inline void mtxOrtho(float* _result, float _left, float _right, float _bottom, float _top, float _near, float _far)
{
	const float aa = 2.0f/(_right - _left);
	const float bb = 2.0f/(_top - _bottom);
	const float cc = 1.0f/(_far - _near);
	const float dd = (_left + _right)/(_left - _right);
	const float ee = (_top + _bottom)/(_bottom - _top);
	const float ff = _near / (_near - _far);

	memset(_result, 0, sizeof(float)*16);
	_result[0] = aa;
	_result[5] = bb;
	_result[10] = cc;
	_result[12] = dd;
	_result[13] = ee;
	_result[14] = ff;
	_result[15] = 1.0f;
}

inline void mtxRotateX(float* _result, float _ax)
{
	const float sx = sinf(_ax);
	const float cx = cosf(_ax);

	memset(_result, 0, sizeof(float)*16);
	_result[ 0] = 1.0f;
	_result[ 5] = cx;
	_result[ 6] = -sx;
	_result[ 9] = sx;
	_result[10] = cx;
	_result[15] = 1.0f;
}

inline void mtxRotateY(float* _result, float _ay)
{
	const float sy = sinf(_ay);
	const float cy = cosf(_ay);

	memset(_result, 0, sizeof(float)*16);
	_result[ 0] = cy;
	_result[ 2] = sy;
	_result[ 5] = 1.0f;
	_result[ 8] = -sy;
	_result[10] = cy;
	_result[15] = 1.0f;
}

inline void mtxRotateZ(float* _result, float _az)
{
	const float sz = sinf(_az);
	const float cz = cosf(_az);

	memset(_result, 0, sizeof(float)*16);
	_result[ 0] = cz;
	_result[ 1] = -sz;
	_result[ 4] = sz;
	_result[ 5] = cz;
	_result[10] = 1.0f;
	_result[15] = 1.0f;
}

inline void mtxRotateXY(float* _result, float _ax, float _ay)
{
	const float sx = sinf(_ax);
	const float cx = cosf(_ax);
	const float sy = sinf(_ay);
	const float cy = cosf(_ay);

	memset(_result, 0, sizeof(float)*16);
	_result[ 0] = cy;
	_result[ 2] = sy;
	_result[ 4] = sx*sy;
	_result[ 5] = cx;
	_result[ 6] = -sx*cy;
	_result[ 8] = -cx*sy;
	_result[ 9] = sx;
	_result[10] = cx*cy;
	_result[15] = 1.0f;
}

inline void mtxRotateXYZ(float* _result, float _ax, float _ay, float _az)
{
	const float sx = sinf(_ax);
	const float cx = cosf(_ax);
	const float sy = sinf(_ay);
	const float cy = cosf(_ay);
	const float sz = sinf(_az);
	const float cz = cosf(_az);

	memset(_result, 0, sizeof(float)*16);
	_result[ 0] = cy*cz;
	_result[ 1] = -cy*sz;
	_result[ 2] = sy;
	_result[ 4] = cz*sx*sy + cx*sz;
	_result[ 5] = cx*cz - sx*sy*sz;
	_result[ 6] = -cy*sx;
	_result[ 8] = -cx*cz*sy + sx*sz;
	_result[ 9] = cz*sx + cx*sy*sz;
	_result[10] = cx*cy;
	_result[15] = 1.0f;
}

inline void mtxRotateZYX(float* _result, float _ax, float _ay, float _az)
{
	const float sx = sinf(_ax);
	const float cx = cosf(_ax);
	const float sy = sinf(_ay);
	const float cy = cosf(_ay);
	const float sz = sinf(_az);
	const float cz = cosf(_az);

	memset(_result, 0, sizeof(float)*16);
	_result[ 0] = cy*cz;
	_result[ 1] = cz*sx*sy-cx*sz;
	_result[ 2] = cx*cz*sy+sx*sz;
	_result[ 4] = cy*sz;
	_result[ 5] = cx*cz + sx*sy*sz;
	_result[ 6] = -cz*sx + cx*sy*sz;
	_result[ 8] = -sy;
	_result[ 9] = cy*sx;
	_result[10] = cx*cy;
	_result[15] = 1.0f;
};

inline void mtxSRT(float* _result, float _sx, float _sy, float _sz, float _ax, float _ay, float _az, float _tx, float _ty, float _tz)
{
	const float sx = sinf(_ax);
	const float cx = cosf(_ax);
	const float sy = sinf(_ay);
	const float cy = cosf(_ay);
	const float sz = sinf(_az);
	const float cz = cosf(_az);

	const float sxsz = sx*sz;
	const float cycz = cy*cz;

	_result[ 0] = _sx * (cycz - sxsz*sy);
	_result[ 1] = _sx * -cx*sz;
	_result[ 2] = _sx * (cz*sy + cy*sxsz);
	_result[ 3] = 0.0f;

	_result[ 4] = _sy * (cz*sx*sy + cy*sz);
	_result[ 5] = _sy * cx*cz;
	_result[ 6] = _sy * (sy*sz -cycz*sx);
	_result[ 7] = 0.0f;

	_result[ 8] = _sz * -cx*sy;
	_result[ 9] = _sz * sx;
	_result[10] = _sz * cx*cy;
	_result[11] = 0.0f;

	_result[12] = _tx;
	_result[13] = _ty;
	_result[14] = _tz;
	_result[15] = 1.0f;
}

inline void vec3MulMtx(float* __restrict _result, const float* __restrict _vec, const float* __restrict _mat)
{
	_result[0] = _vec[0] * _mat[ 0] + _vec[1] * _mat[4] + _vec[2] * _mat[ 8] + _mat[12];
	_result[1] = _vec[0] * _mat[ 1] + _vec[1] * _mat[5] + _vec[2] * _mat[ 9] + _mat[13];
	_result[2] = _vec[0] * _mat[ 2] + _vec[1] * _mat[6] + _vec[2] * _mat[10] + _mat[14];
}

inline void vec3MulMtxH(float* __restrict _result, const float* __restrict _vec, const float* __restrict _mat)
{
	float xx = _vec[0] * _mat[ 0] + _vec[1] * _mat[4] + _vec[2] * _mat[ 8] + _mat[12];
	float yy = _vec[0] * _mat[ 1] + _vec[1] * _mat[5] + _vec[2] * _mat[ 9] + _mat[13];
	float zz = _vec[0] * _mat[ 2] + _vec[1] * _mat[6] + _vec[2] * _mat[10] + _mat[14];
	float ww = _vec[0] * _mat[ 3] + _vec[1] * _mat[7] + _vec[2] * _mat[11] + _mat[15];
	float invW = fsign(ww)/ww;
	_result[0] = xx*invW;
	_result[1] = yy*invW;
	_result[2] = zz*invW;
}

inline void vec4MulMtx(float* __restrict _result, const float* __restrict _vec, const float* __restrict _mat)
{
	_result[0] = _vec[0] * _mat[ 0] + _vec[1] * _mat[4] + _vec[2] * _mat[ 8] + _vec[3] * _mat[12];
	_result[1] = _vec[0] * _mat[ 1] + _vec[1] * _mat[5] + _vec[2] * _mat[ 9] + _vec[3] * _mat[13];
	_result[2] = _vec[0] * _mat[ 2] + _vec[1] * _mat[6] + _vec[2] * _mat[10] + _vec[3] * _mat[14];
	_result[3] = _vec[0] * _mat[ 3] + _vec[1] * _mat[7] + _vec[2] * _mat[11] + _vec[3] * _mat[15];
}

inline void mtxMul(float* __restrict _result, const float* __restrict _a, const float* __restrict _b)
{
	vec4MulMtx(&_result[ 0], &_a[ 0], _b);
	vec4MulMtx(&_result[ 4], &_a[ 4], _b);
	vec4MulMtx(&_result[ 8], &_a[ 8], _b);
	vec4MulMtx(&_result[12], &_a[12], _b);
}

inline void mtxTranspose(float* __restrict _result, const float* __restrict _a)
{
	_result[ 0] = _a[ 0];
	_result[ 4] = _a[ 1];
	_result[ 8] = _a[ 2];
	_result[12] = _a[ 3];
	_result[ 1] = _a[ 4];
	_result[ 5] = _a[ 5];
	_result[ 9] = _a[ 6];
	_result[13] = _a[ 7];
	_result[ 2] = _a[ 8];
	_result[ 6] = _a[ 9];
	_result[10] = _a[10];
	_result[14] = _a[11];
	_result[ 3] = _a[12];
	_result[ 7] = _a[13];
	_result[11] = _a[14];
	_result[15] = _a[15];
}

inline void mtx3Inverse(float* __restrict _result, const float* __restrict _a)
{
	float xx = _a[0];
	float xy = _a[1];
	float xz = _a[2];
	float yx = _a[3];
	float yy = _a[4];
	float yz = _a[5];
	float zx = _a[6];
	float zy = _a[7];
	float zz = _a[8];

	float det = 0.0f;
	det += xx * (yy*zz - yz*zy);
	det -= xy * (yx*zz - yz*zx);
	det += xz * (yx*zy - yy*zx);

	float invDet = 1.0f/det;

	_result[0] = +(yy*zz - yz*zy) * invDet;
	_result[1] = -(xy*zz - xz*zy) * invDet;
	_result[2] = +(xy*yz - xz*yy) * invDet;

	_result[3] = -(yx*zz - yz*zx) * invDet;
	_result[4] = +(xx*zz - xz*zx) * invDet;
	_result[5] = -(xx*yz - xz*yx) * invDet;

	_result[6] = +(yx*zy - yy*zx) * invDet;
	_result[7] = -(xx*zy - xy*zx) * invDet;
	_result[8] = +(xx*yy - xy*yx) * invDet;
}

inline void mtxInverse(float* __restrict _result, const float* __restrict _a)
{
	float xx = _a[ 0];
	float xy = _a[ 1];
	float xz = _a[ 2];
	float xw = _a[ 3];
	float yx = _a[ 4];
	float yy = _a[ 5];
	float yz = _a[ 6];
	float yw = _a[ 7];
	float zx = _a[ 8];
	float zy = _a[ 9];
	float zz = _a[10];
	float zw = _a[11];
	float wx = _a[12];
	float wy = _a[13];
	float wz = _a[14];
	float ww = _a[15];

	float det = 0.0f;
	det += xx * (yy*(zz*ww - zw*wz) - yz*(zy*ww - zw*wy) + yw*(zy*wz - zz*wy) );
	det -= xy * (yx*(zz*ww - zw*wz) - yz*(zx*ww - zw*wx) + yw*(zx*wz - zz*wx) );
	det += xz * (yx*(zy*ww - zw*wy) - yy*(zx*ww - zw*wx) + yw*(zx*wy - zy*wx) );
	det -= xw * (yx*(zy*wz - zz*wy) - yy*(zx*wz - zz*wx) + yz*(zx*wy - zy*wx) );

	float invDet = 1.0f/det;

	_result[ 0] = +(yy*(zz*ww - wz*zw) - yz*(zy*ww - wy*zw) + yw*(zy*wz - wy*zz) ) * invDet;
	_result[ 1] = -(xy*(zz*ww - wz*zw) - xz*(zy*ww - wy*zw) + xw*(zy*wz - wy*zz) ) * invDet;
	_result[ 2] = +(xy*(yz*ww - wz*yw) - xz*(yy*ww - wy*yw) + xw*(yy*wz - wy*yz) ) * invDet;
	_result[ 3] = -(xy*(yz*zw - zz*yw) - xz*(yy*zw - zy*yw) + xw*(yy*zz - zy*yz) ) * invDet;
				  
	_result[ 4] = -(yx*(zz*ww - wz*zw) - yz*(zx*ww - wx*zw) + yw*(zx*wz - wx*zz) ) * invDet;
	_result[ 5] = +(xx*(zz*ww - wz*zw) - xz*(zx*ww - wx*zw) + xw*(zx*wz - wx*zz) ) * invDet;
	_result[ 6] = -(xx*(yz*ww - wz*yw) - xz*(yx*ww - wx*yw) + xw*(yx*wz - wx*yz) ) * invDet;
	_result[ 7] = +(xx*(yz*zw - zz*yw) - xz*(yx*zw - zx*yw) + xw*(yx*zz - zx*yz) ) * invDet;
				  
	_result[ 8] = +(yx*(zy*ww - wy*zw) - yy*(zx*ww - wx*zw) + yw*(zx*wy - wx*zy) ) * invDet;
	_result[ 9] = -(xx*(zy*ww - wy*zw) - xy*(zx*ww - wx*zw) + xw*(zx*wy - wx*zy) ) * invDet;
	_result[10] = +(xx*(yy*ww - wy*yw) - xy*(yx*ww - wx*yw) + xw*(yx*wy - wx*yy) ) * invDet;
	_result[11] = -(xx*(yy*zw - zy*yw) - xy*(yx*zw - zx*yw) + xw*(yx*zy - zx*yy) ) * invDet;
				  
	_result[12] = -(yx*(zy*wz - wy*zz) - yy*(zx*wz - wx*zz) + yz*(zx*wy - wx*zy) ) * invDet;
	_result[13] = +(xx*(zy*wz - wy*zz) - xy*(zx*wz - wx*zz) + xz*(zx*wy - wx*zy) ) * invDet;
	_result[14] = -(xx*(yy*wz - wy*yz) - xy*(yx*wz - wx*yz) + xz*(yx*wy - wx*yy) ) * invDet;
	_result[15] = +(xx*(yy*zz - zy*yz) - xy*(yx*zz - zx*yz) + xz*(yx*zy - zx*yy) ) * invDet;
}

/// Convert LH to RH projection matrix and vice versa.
inline void mtxProjFlipHandedness(float* __restrict _dst, const float* __restrict _src)
{
	_dst[ 0] = -_src[ 0];
	_dst[ 1] = -_src[ 1];
	_dst[ 2] = -_src[ 2];
	_dst[ 3] = -_src[ 3];
	_dst[ 4] =  _src[ 4];
	_dst[ 5] =  _src[ 5];
	_dst[ 6] =  _src[ 6];
	_dst[ 7] =  _src[ 7];
	_dst[ 8] = -_src[ 8];
	_dst[ 9] = -_src[ 9];
	_dst[10] = -_src[10];
	_dst[11] = -_src[11];
	_dst[12] =  _src[12];
	_dst[13] =  _src[13];
	_dst[14] =  _src[14];
	_dst[15] =  _src[15];
}

/// Convert LH to RH view matrix and vice versa.
inline void mtxViewFlipHandedness(float* __restrict _dst, const float* __restrict _src)
{
	_dst[ 0] = -_src[ 0];
	_dst[ 1] =  _src[ 1];
	_dst[ 2] = -_src[ 2];
	_dst[ 3] =  _src[ 3];
	_dst[ 4] = -_src[ 4];
	_dst[ 5] =  _src[ 5];
	_dst[ 6] = -_src[ 6];
	_dst[ 7] =  _src[ 7];
	_dst[ 8] = -_src[ 8];
	_dst[ 9] =  _src[ 9];
	_dst[10] = -_src[10];
	_dst[11] =  _src[11];
	_dst[12] = -_src[12];
	_dst[13] =  _src[13];
	_dst[14] = -_src[14];
	_dst[15] =  _src[15];
}

inline void calcNormal(float _result[3], float _va[3], float _vb[3], float _vc[3])
{
	float ba[3];
	vec3Sub(ba, _vb, _va);

	float ca[3];
	vec3Sub(ca, _vc, _va);

	float baxca[3];
	vec3Cross(baxca, ba, ca);

	vec3Norm(_result, baxca);
}

inline void calcPlane(float _result[4], float _va[3], float _vb[3], float _vc[3])
{
	float normal[3];
	calcNormal(normal, _va, _vb, _vc);

	_result[0] = normal[0];
	_result[1] = normal[1];
	_result[2] = normal[2];
	_result[3] = -vec3Dot(normal, _va);
}

#endif // FPU_MATH_H_HEADER_GUARD
