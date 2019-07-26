#include "../src/meshoptimizer.h"
#include "fast_obj.h"

#include <algorithm>
#include <functional>
#include <vector>

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>

const int kCacheSizeMax = 16;
const int kValenceMax = 8;

namespace meshopt
{
extern thread_local float kVertexScoreTableCache[1 + kCacheSizeMax];
extern thread_local float kVertexScoreTableLive[1 + kValenceMax];
} // namespace meshopt

struct { int cache, warp, triangle; } profiles[] =
{
	{14, 64, 128}, // AMD GCN
	{32, 32, 32},  // NVidia Pascal
	// { 16, 32, 32 }, // NVidia Kepler, Maxwell
	// { 128, 0, 0 }, // Intel
};

const int Profile_Count = sizeof(profiles) / sizeof(profiles[0]);

struct pcg32_random_t
{
	uint64_t state;
	uint64_t inc;
};

#define PCG32_INITIALIZER { 0x853c49e6748fea9bULL, 0xda3e39cb94b95bdbULL }

uint32_t pcg32_random_r(pcg32_random_t* rng)
{
	uint64_t oldstate = rng->state;
	// Advance internal state
	rng->state = oldstate * 6364136223846793005ULL + (rng->inc | 1);
	// Calculate output function (XSH RR), uses old state for max ILP
	uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
	uint32_t rot = oldstate >> 59u;
	return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

pcg32_random_t rngstate = PCG32_INITIALIZER;

float rand01()
{
	return pcg32_random_r(&rngstate) / float(1ull << 32);
}

uint32_t rand32()
{
	return pcg32_random_r(&rngstate);
}

struct State
{
	float cache[kCacheSizeMax];
	float live[kValenceMax];
	float fitness;
};

struct Mesh
{
	size_t vertex_count;
	std::vector<unsigned int> indices;

	float atvr_base[Profile_Count];
};

Mesh gridmesh(unsigned int N)
{
	Mesh result;

	result.vertex_count = (N + 1) * (N + 1);
	result.indices.reserve(N * N * 6);

	for (unsigned int y = 0; y < N; ++y)
		for (unsigned int x = 0; x < N; ++x)
		{
			result.indices.push_back((y + 0) * (N + 1) + (x + 0));
			result.indices.push_back((y + 0) * (N + 1) + (x + 1));
			result.indices.push_back((y + 1) * (N + 1) + (x + 0));

			result.indices.push_back((y + 1) * (N + 1) + (x + 0));
			result.indices.push_back((y + 0) * (N + 1) + (x + 1));
			result.indices.push_back((y + 1) * (N + 1) + (x + 1));
		}

	return result;
}

Mesh objmesh(const char* path)
{
	fastObjMesh* obj = fast_obj_read(path);
	if (!obj)
	{
		printf("Error loading %s: file not found\n", path);
		return Mesh();
	}

	size_t total_indices = 0;

	for (unsigned int i = 0; i < obj->face_count; ++i)
		total_indices += 3 * (obj->face_vertices[i] - 2);

	struct Vertex
	{
		float px, py, pz;
		float nx, ny, nz;
		float tx, ty;
	};

	std::vector<Vertex> vertices(total_indices);

	size_t vertex_offset = 0;
	size_t index_offset = 0;

	for (unsigned int i = 0; i < obj->face_count; ++i)
	{
		for (unsigned int j = 0; j < obj->face_vertices[i]; ++j)
		{
			fastObjIndex gi = obj->indices[index_offset + j];

			Vertex v =
			    {
			        obj->positions[gi.p * 3 + 0],
			        obj->positions[gi.p * 3 + 1],
			        obj->positions[gi.p * 3 + 2],
			        obj->normals[gi.n * 3 + 0],
			        obj->normals[gi.n * 3 + 1],
			        obj->normals[gi.n * 3 + 2],
			        obj->texcoords[gi.t * 2 + 0],
			        obj->texcoords[gi.t * 2 + 1],
			    };

			// triangulate polygon on the fly; offset-3 is always the first polygon vertex
			if (j >= 3)
			{
				vertices[vertex_offset + 0] = vertices[vertex_offset - 3];
				vertices[vertex_offset + 1] = vertices[vertex_offset - 1];
				vertex_offset += 2;
			}

			vertices[vertex_offset] = v;
			vertex_offset++;
		}

		index_offset += obj->face_vertices[i];
	}

	fast_obj_destroy(obj);

	Mesh result;

	std::vector<unsigned int> remap(total_indices);

	size_t total_vertices = meshopt_generateVertexRemap(&remap[0], NULL, total_indices, &vertices[0], total_indices, sizeof(Vertex));

	result.indices.resize(total_indices);
	meshopt_remapIndexBuffer(&result.indices[0], NULL, total_indices, &remap[0]);

	result.vertex_count = total_vertices;

	return result;
}

void compute_atvr(const State& state, const Mesh& mesh, float result[Profile_Count])
{
	memcpy(meshopt::kVertexScoreTableCache + 1, state.cache, kCacheSizeMax * sizeof(float));
	memcpy(meshopt::kVertexScoreTableLive + 1, state.live, kValenceMax * sizeof(float));

	std::vector<unsigned int> indices(mesh.indices.size());

	meshopt_optimizeVertexCache(&indices[0], &mesh.indices[0], mesh.indices.size(), mesh.vertex_count);

	for (int profile = 0; profile < Profile_Count; ++profile)
		result[profile] = meshopt_analyzeVertexCache(&indices[0], indices.size(), mesh.vertex_count, profiles[profile].cache, profiles[profile].warp, profiles[profile].triangle).atvr;
}

float fitness_score(const State& state, const std::vector<Mesh>& meshes)
{
	float result = 0;
	float count = 0;

	for (auto& mesh : meshes)
	{
		float atvr[Profile_Count];
		compute_atvr(state, mesh, atvr);

		for (int profile = 0; profile < Profile_Count; ++profile)
		{
			result += mesh.atvr_base[profile] / atvr[profile];
			count += 1;
		}
	}

	return result / count;
}

std::vector<State> gen0(size_t count, const std::vector<Mesh>& meshes)
{
	std::vector<State> result;

	for (size_t i = 0; i < count; ++i)
	{
		State state = {};

		for (int j = 0; j < kCacheSizeMax; ++j)
			state.cache[j] = rand01();

		for (int j = 0; j < kValenceMax; ++j)
			state.live[j] = rand01();

		state.fitness = fitness_score(state, meshes);

		result.push_back(state);
	}

	return result;
}

// https://en.wikipedia.org/wiki/Differential_evolution
// Good Parameters for Differential Evolution. Magnus Erik Hvass Pedersen, 2010
std::pair<State, float> genN(std::vector<State>& seed, const std::vector<Mesh>& meshes, float crossover = 0.8803f, float weight = 0.4717f)
{
	std::vector<State> result(seed.size());

	for (size_t i = 0; i < seed.size(); ++i)
	{
		for (;;)
		{
			int a = rand32() % seed.size();
			int b = rand32() % seed.size();
			int c = rand32() % seed.size();

			if (a == b || a == c || b == c || a == int(i) || b == int(i) || c == int(i))
				continue;

			int rc = rand32() % kCacheSizeMax;
			int rl = rand32() % kValenceMax;

			for (int j = 0; j < kCacheSizeMax; ++j)
			{
				float r = rand01();

				if (r < crossover || j == rc)
					result[i].cache[j] = std::max(0.f, std::min(1.f, seed[a].cache[j] + weight * (seed[b].cache[j] - seed[c].cache[j])));
				else
					result[i].cache[j] = seed[i].cache[j];
			}

			for (int j = 0; j < kValenceMax; ++j)
			{
				float r = rand01();

				if (r < crossover || j == rl)
					result[i].live[j] = std::max(0.f, std::min(1.f, seed[a].live[j] + weight * (seed[b].live[j] - seed[c].live[j])));
				else
					result[i].live[j] = seed[i].live[j];
			}

			break;
		}
	}

	#pragma omp parallel for
	for (size_t i = 0; i < seed.size(); ++i)
	{
		result[i].fitness = fitness_score(result[i], meshes);
	}

	State best = {};
	float bestfit = 0;

	for (size_t i = 0; i < seed.size(); ++i)
	{
		if (result[i].fitness > seed[i].fitness)
			seed[i] = result[i];

		if (seed[i].fitness > bestfit)
		{
			best = seed[i];
			bestfit = seed[i].fitness;
		}
	}

	return std::make_pair(best, bestfit);
}

bool load_state(const char* path, std::vector<State>& result)
{
	FILE* file = fopen(path, "rb");
	if (!file)
		return false;

	State state;

	result.clear();

	while (fread(&state, sizeof(State), 1, file) == 1)
		result.push_back(state);

	fclose(file);

	return true;
}

bool save_state(const char* path, const std::vector<State>& result)
{
	FILE* file = fopen(path, "wb");
	if (!file)
		return false;

	for (auto& state : result)
	{
		if (fwrite(&state, sizeof(State), 1, file) != 1)
		{
			fclose(file);
			return false;
		}
	}

	return fclose(file) == 0;
}

void dump_state(const State& state)
{
	printf("cache:");
	for (int i = 0; i < kCacheSizeMax; ++i)
	{
		printf(" %.3f", state.cache[i]);
	}
	printf("\n");

	printf("live:");
	for (int i = 0; i < kValenceMax; ++i)
	{
		printf(" %.3f", state.live[i]);
	}
	printf("\n");
}

int main(int argc, char** argv)
{
	bool annealing = false;

	State baseline;
	memcpy(baseline.cache, meshopt::kVertexScoreTableCache + 1, kCacheSizeMax * sizeof(float));
	memcpy(baseline.live, meshopt::kVertexScoreTableLive + 1, kValenceMax * sizeof(float));

	std::vector<Mesh> meshes;

	meshes.push_back(gridmesh(50));

	for (int i = 1; i < argc; ++i)
		meshes.push_back(objmesh(argv[i]));

	size_t total_triangles = 0;

	for (auto& mesh : meshes)
	{
		compute_atvr(baseline, mesh, mesh.atvr_base);

		total_triangles += mesh.indices.size() / 3;
	}

	std::vector<State> pop;
	size_t gen = 0;

	if (load_state("mutator.state", pop))
	{
		printf("Loaded %d state vectors\n", int(pop.size()));
	}
	else
	{
		pop = gen0(95, meshes);
	}

	printf("%d meshes, %.1fM triangles\n", int(meshes.size()), double(total_triangles) / 1e6);

	float atvr_0[Profile_Count];
	float atvr_N[Profile_Count];
	compute_atvr(baseline, meshes[0], atvr_0);
	compute_atvr(baseline, meshes.back(), atvr_N);

	printf("baseline: grid %f %f %s %f %f\n", atvr_0[0], atvr_0[1], argv[argc - 1], atvr_N[0], atvr_N[1]);

	for (;;)
	{
		auto best = genN(pop, meshes);
		gen++;

		compute_atvr(best.first, meshes[0], atvr_0);
		compute_atvr(best.first, meshes.back(), atvr_N);

		printf("%d: fitness %f; grid %f %f %s %f %f\n", int(gen), best.second, atvr_0[0], atvr_0[1], argv[argc - 1], atvr_N[0], atvr_N[1]);

		if (gen % 100 == 0)
		{
			char buf[128];
			sprintf(buf, "gcloud logging write vcache-log \"fitness %f; grid %f %f %s %f %f\"", best.second, atvr_0[0], atvr_0[1], argv[argc - 1], atvr_N[0], atvr_N[1]);
			int rc = system(buf);
			(void)rc;
		}

		dump_state(best.first);

		if (save_state("mutator.state-temp", pop) && rename("mutator.state-temp", "mutator.state") == 0)
		{
		}
		else
		{
			printf("ERROR: Can't save state\n");
		}
	}
}
