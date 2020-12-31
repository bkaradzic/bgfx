
uniform vec4 u_params[2];


#define u_DmapFactor u_params[0].x
#define u_LodFactor u_params[0].y
#define u_cull u_params[0].z
#define u_freeze u_params[0].w
#define u_gpu_subd  int(u_params[1].x)


#define COMPUTE_THREAD_COUNT 32u
#define UPDATE_INDIRECT_VALUE_DIVIDE 32u


