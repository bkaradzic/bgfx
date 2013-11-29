/*
 * Copyright 2013 Dario Manesku. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

static const uint8_t CAMERA_KEY_UP    = 1u << 1;
static const uint8_t CAMERA_KEY_DOWN  = 1u << 2;
static const uint8_t CAMERA_KEY_LEFT  = 1u << 3;
static const uint8_t CAMERA_KEY_RIGHT = 1u << 4;

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
