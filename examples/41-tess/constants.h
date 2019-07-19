#pragma once

#include "common.h"


const char* shader_options[] = {
	"Normal",
	"Diffuse"
};

////Instanced patch geometry at various subdiv levels////

//gpuSubd == 0
const float verticesL0[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f
};

const uint32_t indexesL0[] = { 0u, 1u, 2u };

//gpuSubd == 1
const float verticesL1[] = {
    0.0f, 1.0f,
    0.5f, 0.5f,
    0.0f, 0.5f,
    0.0f, 0.0f,
    0.5f, 0.0f,
    1.0f, 0.0f
};
const uint32_t indexesL1[] = {
    1u, 0u, 2u,
    1u, 2u, 3u,
    1u, 3u, 4u,
    1u, 4u, 5u
};

//gpuSubd == 2
const float verticesL2[] = {
    0.25f, 0.75f,
    0.0f, 1.0f,
    0.0f, 0.75f,
    0.0f, 0.5f,
    0.25f, 0.5f,
    0.5f, 0.5f,

    0.25f, 0.25f,
    0.0f, 0.25f,
    0.0f, 0.0f,
    0.25f, 0.0f,
    0.5f, 0.0f,
    0.5f, 0.25f,
    0.75f, 0.25f,
    0.75f, 0.0f,
    1.0f, 0.0f        //14
};
const uint32_t indexesL2[] = {
    0u, 1u, 2u,
    0u, 2u, 3u,
    0u, 3u, 4u,
    0u, 4u, 5u,

    6u, 5u, 4u,
    6u, 4u, 3u,
    6u, 3u, 7u,
    6u, 7u, 8u,

    6u, 8u, 9u,
    6u, 9u, 10u,
    6u, 10u, 11u,
    6u, 11u, 5u,

    12u, 5u, 11u,
    12u, 11u, 10u,
    12u, 10u, 13u,
    12u, 13u, 14u
};

//gpuSubd == 3
const float verticesL3[] = {
    0.25f*0.5f, 0.75f*0.5f + 0.5f,
    0.0f*0.5f, 1.0f*0.5f + 0.5f,
    0.0f*0.5f, 0.75f*0.5f + 0.5f,
    0.0f*0.5f , 0.5f*0.5f + 0.5f,
    0.25f*0.5f, 0.5f*0.5f + 0.5f,
    0.5f*0.5f, 0.5f*0.5f + 0.5f,
    0.25f*0.5f, 0.25f*0.5f + 0.5f,
    0.0f*0.5f, 0.25f*0.5f + 0.5f,
    0.0f*0.5f, 0.0f*0.5f + 0.5f,
    0.25f*0.5f, 0.0f*0.5f + 0.5f,
    0.5f*0.5f, 0.0f*0.5f + 0.5f,
    0.5f*0.5f, 0.25f*0.5f + 0.5f,
    0.75f*0.5f, 0.25f*0.5f + 0.5f,
    0.75f*0.5f, 0.0f*0.5f + 0.5f,
    1.0f*0.5f, 0.0f*0.5f + 0.5f,        //14

    0.375f, 0.375f,
    0.25f, 0.375f,
    0.25f, 0.25f,
    0.375f, 0.25f,
    0.5f, 0.25f,
    0.5f, 0.375f,    //20

    0.125f, 0.375f,
    0.0f, 0.375f,
    0.0f, 0.25f,
    0.125f, 0.25f,    //24

    0.125f, 0.125f,
    0.0f, 0.125f,
    0.0f, 0.0f,
    0.125f, 0.0f,
    0.25f, 0.0f,
    0.25f, 0.125f,    //30

    0.375f, 0.125f,
    0.375f, 0.0f,
    0.5f, 0.0f,
    0.5f, 0.125f,    //34

    0.625f, 0.375f,
    0.625f, 0.25f,
    0.75f, 0.25f,    //37

    0.625f, 0.125f,
    0.625f, 0.0f,
    0.75f, 0.0f,
    0.75f, 0.125f,    //41

    0.875f, 0.125f,
    0.875f, 0.0f,
    1.0f, 0.0f    //44
};
const uint32_t indexesL3[] = {
    0u, 1u, 2u,
    0u, 2u, 3u,
    0u, 3u, 4u,
    0u, 4u, 5u,

    6u, 5u, 4u,
    6u, 4u, 3u,
    6u, 3u, 7u,
    6u, 7u, 8u,

    6u, 8u, 9u,
    6u, 9u, 10u,
    6u, 10u, 11u,
    6u, 11u, 5u,

    12u, 5u, 11u,
    12u, 11u, 10u,
    12u, 10u, 13u,
    12u, 13u, 14u,        //End fo first big triangle

    15u, 14u, 13u,
    15u, 13u, 10u,
    15u, 10u, 16u,
    15u, 16u, 17u,
    15u, 17u, 18u,
    15u, 18u, 19u,
    15u, 19u, 20u,
    15u, 20u, 14u,

    21u, 10u, 9u,
    21u, 9u, 8u,
    21u, 8u, 22u,
    21u, 22u, 23u,
    21u, 23u, 24u,
    21u, 24u, 17u,
    21u, 17u, 16u,
    21u, 16u, 10u,

    25u, 17u, 24u,
    25u, 24u, 23u,
    25u, 23u, 26u,
    25u, 26u, 27u,
    25u, 27u, 28u,
    25u, 28u, 29u,
    25u, 29u, 30u,
    25u, 30u, 17u,

    31u, 19u, 18u,
    31u, 18u, 17u,
    31u, 17u, 30u,
    31u, 30u, 29u,
    31u, 29u, 32u,
    31u, 32u, 33u,
    31u, 33u, 34u,
    31u, 34u, 19u,

    35u, 14u, 20u,
    35u, 20u, 19u,
    35u, 19u, 36u,
    35u, 36u, 37u,

    38u, 37u, 36u,
    38u, 36u, 19u,
    38u, 19u, 34u,
    38u, 34u, 33u,
    38u, 33u, 39u,
    38u, 39u, 40u,
    38u, 40u, 41u,
    38u, 41u, 37u,

    42u, 37u, 41u,
    42u, 41u, 40u,
    42u, 40u, 43u,
    42u, 43u, 44u
};
