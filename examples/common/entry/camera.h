/*
 * Copyright 2013 Dario Manesku. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#define CAMERA_KEY_UP    UINT8_C(0x1)
#define CAMERA_KEY_DOWN  UINT8_C(0x2)
#define CAMERA_KEY_LEFT  UINT8_C(0x4)
#define CAMERA_KEY_RIGHT UINT8_C(0x8)

///
void cameraSetPosition(float* _pos);

///
void cameraSetHorizontalAngle(float _horizontalAngle);

///
void cameraSetVerticalAngle(float _verticalAngle);

///
void cameraSetMouseState(uint32_t _mx, uint32_t _my, bool _down, bool _move);

///
void cameraSetKeyState(uint8_t _key, bool _down);

///
void cameraGetViewMtx(float* _viewMtx);

///
void cameraGetPosition(float* _pos);

///
void cameraGetAt(float* _at);

///
void cameraUpdate(float _deltaTime = 0.0f);
