/*
 * Copyright 2014 Stanlo Slasinski. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

uniform vec4 u_params[3];

#define threadGroupUpdateSize 512

#define u_timeStep          u_params[0].x
#define u_dispatchSize      floatBitsToUint(u_params[0].y)
#define u_gravity           u_params[0].z
#define u_damping           u_params[0].w

#define u_particleIntensity u_params[1].x
#define u_particleSize      u_params[1].y
#define u_baseSeed          floatBitsToUint(u_params[1].z)
#define u_particlePower     u_params[1].w

#define u_initialSpeed      u_params[2].x
#define u_initialShape      floatBitsToUint(u_params[2].y)
#define u_maxAcceleration   u_params[2].z
