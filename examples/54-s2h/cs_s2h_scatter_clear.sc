#include "bgfx_compute.sh"

IMAGE2D_WO(s_scatterColor, rgba8, 0);
uniform vec4 u_s2hScatterSize;

NUM_THREADS(8, 8, 1)
void main()
{
	ivec2 pixel = ivec2(gl_GlobalInvocationID.xy);
	if (pixel.x < int(u_s2hScatterSize.x) && pixel.y < int(u_s2hScatterSize.y) )
	{
		imageStore(s_scatterColor, pixel, vec4(0.40, 0.70, 0.40, 1.0) );
	}
}
