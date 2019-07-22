bool frustumCullingTest(mat4 mvp, vec3 bmin, vec3 bmax);

struct Frustum
{
	vec4 planes[6];
};

/**
 * Extract Frustum Planes from MVP Matrix
 *
 * Based on "Fast Extraction of Viewing Frustum Planes from the World-
 * View-Projection Matrix", by Gil Gribb and Klaus Hartmann.
 * This procedure computes the planes of the frustum and normalizes
 * them.
 */
void loadFrustum(out Frustum f, mat4 mvp)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			f.planes[i*2+j].x = mtxGetElement(mvp, 0, 3) + (j == 0 ? mtxGetElement(mvp, 0, i) : -mtxGetElement(mvp, 0, i));
			f.planes[i*2+j].y = mtxGetElement(mvp, 1, 3) + (j == 0 ? mtxGetElement(mvp, 1, i) : -mtxGetElement(mvp, 1, i));
			f.planes[i*2+j].z = mtxGetElement(mvp, 2, 3) + (j == 0 ? mtxGetElement(mvp, 2, i) : -mtxGetElement(mvp, 2, i));
			f.planes[i*2+j].w = mtxGetElement(mvp, 3, 3) + (j == 0 ? mtxGetElement(mvp, 3, i) : -mtxGetElement(mvp, 3, i));
			f.planes[i*2+j]*= length(f.planes[i*2+j].xyz);
		}
	}
}

/**
 * Negative Vertex of an AABB
 *
 * This procedure computes the negative vertex of an AABB
 * given a normal.
 * See the View Frustum Culling tutorial @ LightHouse3D.com
 * http://www.lighthouse3d.com/tutorials/view-frustum-culling/geometric-approach-testing-boxes-ii/
 */
vec3 negativeVertex(vec3 bmin, vec3 bmax, vec3 n)
{
	bvec3 b = greaterThan(n, vec3(0.0, 0.0, 0.0));
	return mix(bmin, bmax, b);
}

/**
 * Frustum-AABB Culling Test
 *
 * This procedure returns true if the AABB is either inside, or in
 * intersection with the frustum, and false otherwise.
 * The test is based on the View Frustum Culling tutorial @ LightHouse3D.com
 * http://www.lighthouse3d.com/tutorials/view-frustum-culling/geometric-approach-testing-boxes-ii/
 */
bool frustumCullingTest(mat4 mvp, vec3 bmin, vec3 bmax)
{
	float a = 1.0f;
	Frustum f;

	loadFrustum(f, mvp);
	for (int i = 0; i < 6 && a >= 0.0f; ++i)
	{
		vec3 n = negativeVertex(bmin, bmax, f.planes[i].xyz);
		a = dot(vec4(n, 1.0f), f.planes[i]);
	}

	return (a >= 0.0);
}
