/*
 *  Progressive Mesh type Polygon Reduction Algorithm
 *
 *    Original version by Stan Melax (c) 1998
 *    C version by Cloud Wu (c) 2020
 *
 *  The function ProgressiveMesh() takes a model in an "indexed face
 *  set" sort of way.  i.e. Array of vertices and Array of triangles.
 *  The function then does the polygon reduction algorithm
 *  internally and reduces the model all the way down to 0
 *  vertices and then returns the order in which the
 *  vertices are collapsed and to which neighbor each vertex
 *  is collapsed to.  More specifically the returned "permutation"
 *  indicates how to reorder your vertices so you can render
 *  an object by using the first n vertices (for the n
 *  vertex version).  After permuting your vertices, the
 *  map Array indicates to which vertex each vertex is collapsed to.
 */

/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Stan Melax
 * Copyright (c) 2020 Cloud Wu
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <assert.h>
#include <math.h>
#include <stdlib.h>

#define ARRAY_SIZE 16

struct triangle {
	int vertex[3];		// the 3 points (id) that make this tri
	float normal[3];	// unit vector othogonal to this face
};

struct array {
	int n;
	int cap;
	int *buffer;
	int tmp[ARRAY_SIZE];
};

struct vertex {
	float position[3];		// location of point in euclidean space
	int id;					// place of vertex in original Array
	struct array neighbor;	// adjacent vertices
	struct array face;		// adjacent triangles
	float objdist;			// cached cost of collapsing edge
	int collapse;			// candidate vertex (id) for collapse
};

struct mesh {
	int n_face;
	int n_vertex;
	struct vertex *v;
	struct triangle *t;
};

// vec3 math

static inline void
vec3_sub(const float v0[3], const float v1[3], float v[3]) {
	v[0] = v0[0] - v1[0];
	v[1] = v0[1] - v1[1];
	v[2] = v0[2] - v1[2];
}

static inline void
vec3_cross(const float a[3], const float b[3], float v[3]) {
	v[0] = a[1]*b[2] - a[2]*b[1];
	v[1] = a[2]*b[0] - a[0]*b[2];
	v[2] = a[0]*b[1] - a[1]*b[0];
}

static inline float
vec3_dot(const float a[3], const float b[3]) {
	return a[0]*b[0] + a[1]*b[1] + a[2] * b[2];
}

static inline float
vec3_length(const float v[3]) {
	return sqrtf(vec3_dot(v,v));
}

static inline void
vec3_normalize(float v[3]) {
	const float invLen = 1.0f/vec3_length(v);
	v[0] *= invLen;
	v[1] *= invLen;
	v[2] *= invLen;
}

// array

static void
array_init(struct array *a) {
	a->n = 0;
	a->cap = ARRAY_SIZE;
	a->buffer = a->tmp;
}

static void
array_deinit(struct array *a) {
	if (a->buffer != a->tmp) {
		free(a->buffer);
		a->buffer = a->tmp;
		a->cap = ARRAY_SIZE;
		a->n = 0;
	}
}

static inline int
array_index(struct array *a, int idx) {
	return a->buffer[idx];
}

static void
array_push(struct array *a, int v) {
	if (a->n >= a->cap) {
		int *old = a->buffer;
		a->buffer = (int *)malloc(a->cap * 2 * sizeof(int));
		int i;
		for (i=0;i<a->n;i++) {
			a->buffer[i] = old[i];
		}
		if (old != a->tmp)
			free(old);
	}
	a->buffer[a->n++] = v;
}

static inline void
array_remove_index(struct array *a, int idx) {
	a->buffer[idx] = a->buffer[--a->n];
}

static void
array_remove(struct array *a, int v) {
	int i;
	for (i=0; i<a->n; i++) {
		if (a->buffer[i] == v) {
			array_remove_index(a, i);
			return;
		}
	}
}

static inline struct vertex *
Vertex(struct mesh *M, int id) {
	return &M->v[id];
}

static inline struct triangle *
Triangle(struct mesh *M, int id) {
	return &M->t[id];
}

static inline struct triangle *
Face(struct mesh *M, struct vertex *v, int idx) {
	return Triangle(M, array_index(&v->face, idx));
}

static void
AddVertex(struct mesh *M, const float v[3]) {
	int id = M->n_vertex++;
	struct vertex * tmp = Vertex(M, id);
	tmp->position[0] = v[0];
	tmp->position[1] = v[1];
	tmp->position[2] = v[2];
	tmp->id = id;
	array_init(&tmp->neighbor);
	array_init(&tmp->face);
	tmp->objdist = 0;
	tmp->collapse = -1;
}

static void
RemoveVertex(struct mesh *M, int id) {
	struct vertex * v = Vertex(M, id);
	assert(v->id == id);
	assert(v->face.n == 0);
	int i;
	for (i=0;i<v->face.n;i++) {
		struct vertex * nv = Vertex(M, array_index(&v->face, i));
		array_remove(&nv->neighbor, id);
	}
	v->id = -1;	// invalid vertex id
	array_deinit(&v->neighbor);
	array_deinit(&v->face);
}

static void
ComputeNormal(struct mesh *M, struct triangle *t) {
	struct vertex * v0 = Vertex(M, t->vertex[0]);
	struct vertex * v1 = Vertex(M, t->vertex[1]);
	struct vertex * v2 = Vertex(M, t->vertex[2]);
	float a[3], b[3];
	vec3_sub(v1->position, v0->position, a);
	vec3_sub(v2->position, v1->position, b);
	vec3_cross(a,b, t->normal);
	vec3_normalize(t->normal);
}

static void
AddNeighbor(struct mesh *M, int vid, int id) {
	struct vertex *v = Vertex(M, vid);
	int i;
	for (i=0;i<v->neighbor.n;i++) {
		if (array_index(&v->neighbor,i) == id)
			return;
	}
	array_push(&v->neighbor, id);
}

#include <stdio.h>

static void
AddTriangle(struct mesh *M, const int v[3]) {
	int v0 = v[0];
	int v1 = v[1];
	int v2 = v[2];
	if (v0 == v1 || v0 == v2 || v1 == v2)
		return;
	assert(v0 < M->n_vertex);
	assert(v1 < M->n_vertex);
	assert(v2 < M->n_vertex);
	int id = M->n_face++;
	struct triangle * tmp = Triangle(M, id);
	tmp->vertex[0] = v0;
	tmp->vertex[1] = v1;
	tmp->vertex[2] = v2;
	ComputeNormal(M, tmp);

	int i;
	for(i=0;i<3;i++) {
		struct vertex *obj = Vertex(M, v[i]);
		array_push(&obj->face, id);
	}

	AddNeighbor(M, v0, v1);
	AddNeighbor(M, v0, v2);
	AddNeighbor(M, v1, v0);
	AddNeighbor(M, v1, v2);
	AddNeighbor(M, v2, v0);
	AddNeighbor(M, v2, v1);
}

static int
HasVertex(struct triangle * t, int vid) {
	return (t->vertex[0] == vid || t->vertex[1] == vid || t->vertex[2] == vid);
}

static void
RemoveIfNonNeighbor_(struct mesh *M, struct vertex *v, int id) {
	int i,j;
	for (i=0;i<v->neighbor.n;i++) {
		if (array_index(&v->neighbor, i) == id) {
			for (j=0;j<v->face.n;j++) {
				if (HasVertex(Face(M, v, j), id))
					return;
			}
			// remove from neighbors
			array_remove_index(&v->neighbor, i);
			return;
		}
	}
}

static void
RemoveIfNonNeighbor(struct mesh *M, struct vertex *v0, struct vertex *v1) {
	if (v0 == NULL || v1 == NULL)
		return;
	RemoveIfNonNeighbor_(M, v0, v1->id);
	RemoveIfNonNeighbor_(M, v1, v0->id);
}

static void
RemoveTriangle(struct mesh *M, int id) {
	struct triangle * face = Triangle(M, id);
	struct vertex * v[3];
	int i;
	for (i=0;i<3;i++) {
		v[i] = Vertex(M, face->vertex[i]);
		if (v[i]->id < 0)
			v[i] = NULL;
		else {
			array_remove(&v[i]->face, id);
		}
	}
	RemoveIfNonNeighbor(M, v[0], v[1]);
	RemoveIfNonNeighbor(M, v[1], v[2]);
	RemoveIfNonNeighbor(M, v[2], v[0]);
}

static void
ReplaceVertex(struct mesh *M, int faceid, int oldid, int newid) {
	struct triangle * face = Triangle(M, faceid);
	assert(oldid >=0 && newid >= 0);
	assert(HasVertex(face, oldid));
	assert(!HasVertex(face, newid));
	if(oldid==face->vertex[0]){
		face->vertex[0]=newid;
	} else if(oldid==face->vertex[1]){
		face->vertex[1]=newid;
	} else {
		face->vertex[2]=newid;
	}
	struct vertex *vold = Vertex(M, oldid);
	struct vertex *vnew = Vertex(M, newid);

	array_remove(&vold->face, faceid);
	array_push(&vnew->face, faceid);

	int i;
	for (i = 0; i<3; i++) {
		struct vertex *v = Vertex(M, face->vertex[i]);
		RemoveIfNonNeighbor(M, vold, v);
	}

	AddNeighbor(M, face->vertex[0], face->vertex[1]);
	AddNeighbor(M, face->vertex[0], face->vertex[2]);
	AddNeighbor(M, face->vertex[1], face->vertex[0]);
	AddNeighbor(M, face->vertex[1], face->vertex[2]);
	AddNeighbor(M, face->vertex[2], face->vertex[0]);
	AddNeighbor(M, face->vertex[2], face->vertex[1]);

	ComputeNormal(M, face);
}

static void
mesh_init(struct mesh *M, int vert_n, int tri_n) {
	M->n_face = 0;
	M->n_vertex = 0;
	M->v = (struct vertex *)malloc(vert_n * sizeof(struct vertex));
	M->t = (struct triangle *)malloc(tri_n * sizeof(struct triangle));
}

static void
mesh_deinit(struct mesh *M) {
	free(M->v);
	free(M->t);
}

static float
ComputeEdgeCollapseCost(struct mesh *M, struct vertex *u, int vid) {
	// if we collapse edge uv by moving u to v then how
	// much different will the model change, i.e. how much "error".
	// Texture, vertex normal, and border vertex code was removed
	// to keep this demo as simple as possible.
	// The method of determining cost was designed in order
	// to exploit small and coplanar regions for
	// effective polygon reduction.
	// Is is possible to add some checks here to see if "folds"
	// would be generated.  i.e. normal of a remaining face gets
	// flipped.  I never seemed to run into this problem and
	// therefore never added code to detect this case.
	struct vertex *v = Vertex(M, vid);
	float tmp[3];
	vec3_sub(v->position, u->position, tmp);
	float edgelength = vec3_length(tmp);
	float curvature=0;

	// find the "sides" triangles that are on the edge uv
	struct array sides;
	array_init(&sides);
	int i,j;
	for (i = 0; i<u->face.n; i++) {
		if (HasVertex(Face(M, u, i), vid)) {
			array_push(&sides, array_index(&u->face, i));
		}
	}
	// use the triangle facing most away from the sides
	// to determine our curvature term
	for (i = 0; i<u->face.n; i++) {
		float mincurv=1; // curve for face i and closer side to it
		for (j = 0; j<sides.n; j++) {
			float dotprod = vec3_dot(Triangle(M, array_index(&u->face, i))->normal,
				Triangle(M, array_index(&sides,j))->normal);	  // use dot product of face normals.
			float t = (1-dotprod)/2.0f;
			if (t < mincurv) {
				mincurv = t;
			}
		}
		if (mincurv > curvature)
			curvature = mincurv;
	}
	array_deinit(&sides);
	// the more coplanar the lower the curvature term
	return edgelength * curvature;
}

static void
ComputeEdgeCostAtVertex(struct mesh *M, struct vertex *v) {
	// compute the edge collapse cost for all edges that start
	// from vertex v.  Since we are only interested in reducing
	// the object by selecting the min cost edge at each step, we
	// only cache the cost of the least cost edge at this vertex
	// (in member variable collapse) as well as the value of the
	// cost (in member variable objdist).
	if (v->neighbor.n == 0) {
		// v doesn't have neighbors so it costs nothing to collapse
		v->collapse=-1;
		v->objdist=-0.01f;
		return;
	}
	v->objdist = 1000000;
	v->collapse=-1;
	// search all neighboring edges for "least cost" edge
	int i;
	for (i = 0; i<v->neighbor.n; i++) {
		float dist;
		dist = ComputeEdgeCollapseCost(M, v, array_index(&v->neighbor, i));
		if(dist<v->objdist) {
			v->collapse=array_index(&v->neighbor, i);	// candidate for edge collapse
			v->objdist=dist;					// cost of the collapse
		}
	}
}

static void
ComputeAllEdgeCollapseCosts(struct mesh *M) {
	// For all the edges, compute the difference it would make
	// to the model if it was collapsed.  The least of these
	// per vertex is cached in each vertex object.
	int i;
	for (i = 0; i<M->n_vertex; i++) {
		ComputeEdgeCostAtVertex(M, Vertex(M, i));
	}
}

static void
Collapse(struct mesh *M, int uid, int vid) {
	// Collapse the edge uv by moving vertex u onto v
	// Actually remove tris on uv, then update tris that
	// have u to have v, and then remove u.
	struct vertex *u = Vertex(M, uid);
	if(vid < 0) {
		// u is a vertex all by itself so just delete it
		RemoveVertex(M, uid);
		return;
	}

	struct array tmp;
	array_init(&tmp);
	int i;
	// make tmp a Array of all the neighbors of u
	for (i = 0; i<u->neighbor.n; i++) {
		array_push(&tmp, array_index(&u->neighbor, i));
	}

	// delete triangles on edge uv:
	{
		i = u->face.n;
		while (i--) {
			if (HasVertex(Face(M, u, i), vid)) {
				RemoveTriangle(M, array_index(&u->face, i));
			}
		}
	}
	// update remaining triangles to have v instead of u
	{
		i = u->face.n;
		while (i--) {
			ReplaceVertex(M, array_index(&u->face, i), uid, vid);
		}
	}
	RemoveVertex(M, uid);
	// recompute the edge collapse costs for neighboring vertices
	for (i = 0; i<tmp.n; i++) {
		ComputeEdgeCostAtVertex(M, Vertex(M, array_index(&tmp, i)));
	}
	array_deinit(&tmp);
}

static struct vertex *
MinimumCostEdge(struct mesh *M) {
	// Find the edge that when collapsed will affect model the least.
	// This funtion actually returns a Vertex, the second vertex
	// of the edge (collapse candidate) is stored in the vertex data.
	// Serious optimization opportunity here: this function currently
	// does a sequential search through an unsorted Array :-(
	// Our algorithm could be O(n*lg(n)) instead of O(n*n)
	int i;
	struct vertex *mn = NULL;
	for (i = 0; i<M->n_vertex; i++) {
		struct vertex *v = Vertex(M, i);
		if (v->id >=0) {
			if (mn == NULL || v->objdist < mn->objdist) {
				mn = v;
			}
		}
	}
	return mn;
}

void
ProgressiveMesh(int vert_n, int vert_stride, const float *v, int tri_n, const int *tri, int *map, int *permutation) {
	struct mesh M;
	mesh_init(&M, vert_n, tri_n);

	// put input data into our data structures M
	int i;
	const char * tmp = (const char *)v;
	for (i=0;i<vert_n;i++) {
		AddVertex(&M, (const float *) tmp);
		tmp += vert_stride;
	}

	for (i=0;i<tri_n;i++) {
		AddTriangle(&M, &tri[i*3]);
	}

	ComputeAllEdgeCollapseCosts(&M); // cache all edge collapse costs

	for (i = vert_n-1; i>=0; i--) {
		// get the next vertex to collapse
		struct vertex *mn = MinimumCostEdge(&M);
		// keep track of this vertex, i.e. the collapse ordering
		permutation[mn->id] = i;
		// keep track of vertex to which we collapse to
		map[i] = mn->collapse;
		// Collapse this edge
		Collapse(&M, mn->id, mn->collapse);
	}

	// reorder the map Array based on the collapse ordering
	for (i = 0; i<vert_n; i++) {
		map[i] = (map[i]==-1)?0:permutation[map[i]];
	}
	// The caller of this function should reorder their vertices
	// according to the returned "permutation".

	mesh_deinit(&M);
}
