/*
 * Copyright 2018 Kostas Anagnostou. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

/*
 * Reference(s):
 * - Experiments in GPU-based occlusion culling
 *   https://web.archive.org/web/20180920045301/https://interplayoflight.wordpress.com/2017/11/15/experiments-in-gpu-based-occlusion-culling/
 * - Experiments in GPU-based occlusion culling part 2: MultiDrawIndirect and mesh lodding
 *   https://web.archive.org/web/20180920045332/https://interplayoflight.wordpress.com/2018/01/15/experiments-in-gpu-based-occlusion-culling-part-2-multidrawindirect-and-mesh-lodding/
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

namespace
{

#define RENDER_PASS_HIZ_ID            0
#define RENDER_PASS_HIZ_DOWNSCALE_ID  1
#define RENDER_PASS_OCCLUDE_PROPS_ID  2
#define RENDER_PASS_COMPACT_STREAM_ID 3
#define RENDER_PASS_MAIN_ID           4

struct Camera
{
	Camera()
	{
		reset();
	}

	void reset()
	{
		m_target.curr = { 0.0f, 0.0f, 0.0f };
		m_target.dest = { 0.0f, 0.0f, 0.0f };

		m_pos.curr = { 55.0f, 20.0f, 65.0f };
		m_pos.dest = { 55.0f, 20.0f, 65.0f };

		m_orbit[0] = 0.0f;
		m_orbit[1] = 0.0f;
	}

	void mtxLookAt(float* _outViewMtx)
	{
		bx::mtxLookAt(_outViewMtx, m_pos.curr, m_target.curr);
	}

	void orbit(float _dx, float _dy)
	{
		m_orbit[0] += _dx;
		m_orbit[1] += _dy;
	}

	void dolly(float _dz)
	{
		const float cnear = 1.0f;
		const float cfar  = 100.0f;

		const bx::Vec3 toTarget     = bx::sub(m_target.dest, m_pos.dest);
		const float toTargetLen     = bx::length(toTarget);
		const float invToTargetLen  = 1.0f / (toTargetLen + bx::kFloatMin);
		const bx::Vec3 toTargetNorm = bx::mul(toTarget, invToTargetLen);

		float delta  = toTargetLen * _dz;
		float newLen = toTargetLen + delta;
		if ( (cnear  < newLen || _dz < 0.0f)
		&&   (newLen < cfar   || _dz > 0.0f) )
		{
			m_pos.dest = bx::mad(toTargetNorm, delta, m_pos.dest);
		}
	}

	void consumeOrbit(float _amount)
	{
		float consume[2];
		consume[0] = m_orbit[0] * _amount;
		consume[1] = m_orbit[1] * _amount;
		m_orbit[0] -= consume[0];
		m_orbit[1] -= consume[1];

		const bx::Vec3 toPos     = bx::sub(m_pos.curr, m_target.curr);
		const float toPosLen     = bx::length(toPos);
		const float invToPosLen  = 1.0f / (toPosLen + bx::kFloatMin);
		const bx::Vec3 toPosNorm = bx::mul(toPos, invToPosLen);

		float ll[2];
		bx::toLatLong(&ll[0], &ll[1], toPosNorm);
		ll[0] += consume[0];
		ll[1] -= consume[1];
		ll[1]  = bx::clamp(ll[1], 0.02f, 0.98f);

		const bx::Vec3 tmp  = bx::fromLatLong(ll[0], ll[1]);
		const bx::Vec3 diff = bx::mul(bx::sub(tmp, toPosNorm), toPosLen);

		m_pos.curr = bx::add(m_pos.curr, diff);
		m_pos.dest = bx::add(m_pos.dest, diff);
	}

	void update(float _dt)
	{
		const float amount = bx::min(_dt / 0.12f, 1.0f);

		consumeOrbit(amount);

		m_target.curr = bx::lerp(m_target.curr, m_target.dest, amount);
		m_pos.curr    = bx::lerp(m_pos.curr,    m_pos.dest,    amount);
	}

	void envViewMtx(float* _mtx)
	{
		const bx::Vec3 toTarget     = bx::sub(m_target.curr, m_pos.curr);
		const float toTargetLen     = bx::length(toTarget);
		const float invToTargetLen  = 1.0f / (toTargetLen + bx::kFloatMin);
		const bx::Vec3 toTargetNorm = bx::mul(toTarget, invToTargetLen);

		const bx::Vec3 right = bx::normalize(bx::cross({ 0.0f, 1.0f, 0.0f }, toTargetNorm) );
		const bx::Vec3 up    = bx::normalize(bx::cross(toTargetNorm, right) );

		_mtx[ 0] = right.x;
		_mtx[ 1] = right.y;
		_mtx[ 2] = right.z;
		_mtx[ 3] = 0.0f;
		_mtx[ 4] = up.x;
		_mtx[ 5] = up.y;
		_mtx[ 6] = up.z;
		_mtx[ 7] = 0.0f;
		_mtx[ 8] = toTargetNorm.x;
		_mtx[ 9] = toTargetNorm.y;
		_mtx[10] = toTargetNorm.z;
		_mtx[11] = 0.0f;
		_mtx[12] = 0.0f;
		_mtx[13] = 0.0f;
		_mtx[14] = 0.0f;
		_mtx[15] = 1.0f;
	}

	struct Interp3f
	{
		bx::Vec3 curr;
		bx::Vec3 dest;
	};

	Interp3f m_target;
	Interp3f m_pos;
	float m_orbit[2];
};

struct Mouse
{
	Mouse()
		: m_dx(0.0f)
		, m_dy(0.0f)
		, m_prevMx(0.0f)
		, m_prevMy(0.0f)
		, m_scroll(0)
		, m_scrollPrev(0)
	{
	}

	void update(float _mx, float _my, int32_t _mz, uint32_t _width, uint32_t _height)
	{
		const float widthf = float(int32_t(_width));
		const float heightf = float(int32_t(_height));

		// Delta movement.
		m_dx = float(_mx - m_prevMx) / widthf;
		m_dy = float(_my - m_prevMy) / heightf;

		m_prevMx = _mx;
		m_prevMy = _my;

		// Scroll.
		m_scroll = _mz - m_scrollPrev;
		m_scrollPrev = _mz;
	}

	float m_dx; // Screen space.
	float m_dy;
	float m_prevMx;
	float m_prevMy;
	int32_t m_scroll;
	int32_t m_scrollPrev;
};

struct PosVertex
{
	float m_x;
	float m_y;
	float m_z;

	static void init()
	{
		ms_layout
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.end();
	};

	static bgfx::VertexLayout ms_layout;
};

bgfx::VertexLayout PosVertex::ms_layout;

static PosVertex s_cubeVertices[8] =
{
	{-0.5f,  0.5f,  0.5f},
	{ 0.5f,  0.5f,  0.5f},
	{-0.5f, -0.5f,  0.5f},
	{ 0.5f, -0.5f,  0.5f},
	{-0.5f,  0.5f, -0.5f},
	{ 0.5f,  0.5f, -0.5f},
	{-0.5f, -0.5f, -0.5f},
	{ 0.5f, -0.5f, -0.5f},
};

static const uint16_t s_cubeIndices[36] =
{
	0, 1, 2, // 0
	1, 3, 2,
	4, 6, 5, // 2
	5, 6, 7,
	0, 2, 4, // 4
	4, 2, 6,
	1, 5, 3, // 6
	5, 7, 3,
	0, 4, 1, // 8
	4, 5, 1,
	2, 3, 6, // 10
	6, 3, 7,
};

struct RenderPass
{
	enum Enum
	{
		Occlusion = 1 << 0,
		MainPass = 1 << 1,
		All = Occlusion | MainPass
	};
};

// All the per-instance data we store
struct InstanceData
{
	float m_world[16];
	float m_bboxMin[4];
	float m_bboxMax[4];
};

//A description of each prop
struct Prop
{
	PosVertex*	m_vertices;
	uint16_t*	m_indices;
	InstanceData* m_instances;
	bgfx::VertexBufferHandle m_vertexbufferHandle;
	bgfx::IndexBufferHandle  m_indexbufferHandle;
	uint16_t	m_noofVertices;
	uint16_t	m_noofIndices;
	uint16_t	m_noofInstances;
	uint16_t	m_materialID;
	RenderPass::Enum m_renderPass;
};

//A simplistic material, comprised of a color only
struct Material
{
	float m_color[4];
};

inline void setVector4(float* dest, float x, float y, float z, float w)
{
	dest[0] = x;
	dest[1] = y;
	dest[2] = z;
	dest[3] = w;
}

//Sets up a prop
void createCubeMesh(Prop& prop)
{
	prop.m_noofVertices = 8;
	prop.m_noofIndices = 36;
	prop.m_vertices = new PosVertex[prop.m_noofVertices];
	prop.m_indices = new uint16_t[prop.m_noofIndices];

	bx::memCopy(prop.m_vertices, s_cubeVertices, prop.m_noofVertices * PosVertex::ms_layout.getStride());
	bx::memCopy(prop.m_indices, s_cubeIndices, prop.m_noofIndices * sizeof(uint16_t));

	prop.m_vertexbufferHandle = bgfx::createVertexBuffer(
		bgfx::makeRef(prop.m_vertices, prop.m_noofVertices * PosVertex::ms_layout.getStride()),
		PosVertex::ms_layout);

	prop.m_indexbufferHandle = bgfx::createIndexBuffer(bgfx::makeRef(prop.m_indices, prop.m_noofIndices * sizeof(uint16_t)));
}

//returns a random number between 0 and 1
float rand01()
{
	return rand() / (float)RAND_MAX;
}

class GPUDrivenRendering : public entry::AppI
{
public:
	GPUDrivenRendering(const char* _name, const char* _description, const char* _url)
		: entry::AppI(_name, _description, _url)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		Args args(_argc, _argv);

		m_width  = _width;
		m_height = _height;

		//find largest pow of two dims less than backbuffer size
		m_hiZwidth  = (uint32_t)bx::pow(2.0f, bx::floor(bx::log2(float(m_width ) ) ) );
		m_hiZheight = (uint32_t)bx::pow(2.0f, bx::floor(bx::log2(float(m_height) ) ) );

		m_debug  = BGFX_DEBUG_TEXT;
		m_reset  = BGFX_RESET_VSYNC;

		bgfx::Init init;
		init.type     = args.m_type;
		init.vendorId = args.m_pciId;
		init.resolution.width  = m_width;
		init.resolution.height = m_height;
		init.resolution.reset  = m_reset;
		bgfx::init(init);

		// Enable debug text.
		bgfx::setDebug(m_debug);

		// Create uniforms and samplers.
		u_inputRTSize       = bgfx::createUniform("u_inputRTSize",       bgfx::UniformType::Vec4);
		u_cullingConfig     = bgfx::createUniform("u_cullingConfig",     bgfx::UniformType::Vec4);
		u_color             = bgfx::createUniform("u_color",             bgfx::UniformType::Vec4, 32);
		s_texOcclusionDepth = bgfx::createUniform("s_texOcclusionDepth", bgfx::UniformType::Sampler);

		//create props
		{
			m_totalInstancesCount = 0;

			// Create vertex stream declaration.
			PosVertex::init();

			m_noofProps = 0;

			m_props = new Prop[s_maxNoofProps];

			//first create space for some materials
			m_materials = new Material[s_maxNoofProps];
			m_noofMaterials = 0;

			//add a ground plane
			{
				Prop& prop = m_props[m_noofProps++];

				prop.m_renderPass = RenderPass::MainPass;

				createCubeMesh(prop);

				prop.m_noofInstances = 1;
				prop.m_instances = new InstanceData[prop.m_noofInstances];

				bx::mtxSRT(prop.m_instances->m_world
					, 100.0f, 0.1f, 100.0f
					, 0.0f, 0.0f, 0.0f
					, 0.0f, 0.0f, 0.0f
				);

				float temp[4];
				setVector4(temp, -0.5f, -0.5f, -0.5f, 1.0f);
				bx::vec4MulMtx(prop.m_instances->m_bboxMin, temp, prop.m_instances->m_world);

				setVector4(temp, 0.5f, 0.5f, 0.5f, 1.0f);
				bx::vec4MulMtx(prop.m_instances->m_bboxMax, temp, prop.m_instances->m_world);

				prop.m_materialID = m_noofMaterials;
				setVector4(m_materials[prop.m_materialID].m_color, 0.0f, 0.6f, 0.0f, 1.0f);
				m_noofMaterials++;

				m_totalInstancesCount += prop.m_noofInstances;
			}

			//add a few instances of the occluding mesh
			{
				Prop& prop = m_props[m_noofProps++];

				prop.m_renderPass = RenderPass::All;

				//create prop
				createCubeMesh(prop);

				//add a few instances of the wall mesh
				prop.m_noofInstances = 25;
				prop.m_instances = new InstanceData[prop.m_noofInstances];
				for (int i = 0; i < prop.m_noofInstances; i++)
				{
					//calculate world position
					bx::mtxSRT(prop.m_instances[i].m_world
						, 40.0f, 10.0f, 0.1f
						, 0.0f, ( rand01() * 120.0f - 60.0f) * 3.1459f / 180.0f, 0.0f
						, rand01() * 100.0f - 50.0f, 5.0f, rand01() * 100.0f - 50.0f
					);

					//calculate bounding box and transform to world space
					float temp[4];
					setVector4(temp, -0.5f, -0.5f, -0.5f, 1.0f);
					bx::vec4MulMtx(prop.m_instances[i].m_bboxMin, temp, prop.m_instances[i].m_world );

					setVector4(temp, 0.5f, 0.5f, 0.5f, 1.0f);
					bx::vec4MulMtx(prop.m_instances[i].m_bboxMax, temp, prop.m_instances[i].m_world );
				}

				//set the material ID. Will be used in the shader to select the material
				prop.m_materialID = m_noofMaterials;

				//add a "material" for this prop
				setVector4(m_materials[prop.m_materialID].m_color, 0.0f, 0.0f, 1.0f, 0.0f);
				m_noofMaterials++;

				m_totalInstancesCount += prop.m_noofInstances;
			}

			//add a few "regular" props
			{
				//add cubes
				{
					Prop& prop = m_props[m_noofProps++];

					prop.m_renderPass = RenderPass::MainPass;

					createCubeMesh(prop);

					prop.m_noofInstances = 200;
					prop.m_instances = new InstanceData[prop.m_noofInstances];
					for (int i = 0; i < prop.m_noofInstances; i++)
					{
						bx::mtxSRT(prop.m_instances[i].m_world
							, 2.0f, 2.0f, 2.0f
							, 0.0f, 0.0f, 0.0f
							, rand01() * 100.0f - 50.0f, 1.0f, rand01() * 100.0f - 50.0f
						);

						float temp[4];
						setVector4(temp, -0.5f, -0.5f, -0.5f, 1.0f);
						bx::vec4MulMtx(prop.m_instances[i].m_bboxMin, temp, prop.m_instances[i].m_world);

						setVector4(temp, 0.5f, 0.5f, 0.5f, 1.0f);
						bx::vec4MulMtx(prop.m_instances[i].m_bboxMax, temp, prop.m_instances[i].m_world);
					}

					prop.m_materialID = m_noofMaterials;
					setVector4(m_materials[prop.m_materialID].m_color, 1.0f, 1.0f, 0.0f, 1.0f);
					m_noofMaterials++;

					m_totalInstancesCount += prop.m_noofInstances;
				}

				//add some more cubes
				{
					Prop& prop = m_props[m_noofProps++];

					prop.m_renderPass = RenderPass::MainPass;

					createCubeMesh(prop);

					prop.m_noofInstances = 300;
					prop.m_instances = new InstanceData[prop.m_noofInstances];
					for (int i = 0; i < prop.m_noofInstances; i++)
					{
						bx::mtxSRT(prop.m_instances[i].m_world
							, 2.0f, 4.0f, 2.0f
							, 0.0f, 0.0f, 0.0f
							, rand01() * 100.0f - 50.0f, 2.0f, rand01() * 100.0f - 50.0f
						);

						float temp[4];
						setVector4(temp, -0.5f, -0.5f, -0.5f, 1.0f);
						bx::vec4MulMtx(prop.m_instances[i].m_bboxMin, temp, prop.m_instances[i].m_world );

						setVector4(temp, 0.5f, 0.5f, 0.5f, 1.0f);
						bx::vec4MulMtx(prop.m_instances[i].m_bboxMax, temp, prop.m_instances[i].m_world);
					}

					prop.m_materialID = m_noofMaterials;
					setVector4(m_materials[prop.m_materialID].m_color, 1.0f, 0.0f, 0.0f, 1.0f);
					m_noofMaterials++;

					m_totalInstancesCount += prop.m_noofInstances;
				}
			}
		}

		//Setup Occlusion pass
		{
			const uint64_t tsFlags = 0
				| BGFX_TEXTURE_RT
				| BGFX_SAMPLER_MIN_POINT
				| BGFX_SAMPLER_MAG_POINT
				| BGFX_SAMPLER_MIP_POINT
				| BGFX_SAMPLER_U_CLAMP
				| BGFX_SAMPLER_V_CLAMP
				;

			// Create buffers for the HiZ pass
			m_hiZDepthBuffer = bgfx::createFrameBuffer(uint16_t(m_hiZwidth), uint16_t(m_hiZheight), bgfx::TextureFormat::D32, tsFlags);

			bgfx::TextureHandle buffer = bgfx::createTexture2D(uint16_t(m_hiZwidth), uint16_t(m_hiZheight), true, 1, bgfx::TextureFormat::R32F, BGFX_TEXTURE_COMPUTE_WRITE | tsFlags);
			m_hiZBuffer = bgfx::createFrameBuffer(1, &buffer, true);

			//how many mip will the Hi Z buffer have?
			m_noofHiZMips = (uint8_t)(1 + bx::floor(bx::log2(float(bx::max(m_hiZwidth, m_hiZheight) ) ) ) );

			// Setup compute shader buffers

			//The compute shader will write how many unoccluded instances per drawcall there are here
			m_drawcallInstanceCounts = bgfx::createDynamicIndexBuffer(s_maxNoofProps, BGFX_BUFFER_INDEX32 | BGFX_BUFFER_COMPUTE_READ_WRITE);

			//the compute shader will write the result of the occlusion test for each instance here
			m_instancePredicates = bgfx::createDynamicIndexBuffer(s_maxNoofInstances, BGFX_BUFFER_COMPUTE_READ_WRITE);

			//bounding box for each instance, will be fed to the compute shader to calculate occlusion
			{
				bgfx::VertexLayout computeVertexLayout;
				computeVertexLayout.begin()
					.add(bgfx::Attrib::TexCoord0, 4, bgfx::AttribType::Float)
					.end();

				//initialise the buffer with the bounding boxes of all instances
				const int sizeOfBuffer = 2 * 4 * m_totalInstancesCount;
				float* boundingBoxes = new float[sizeOfBuffer];

				float* data = boundingBoxes;
				for (uint16_t i = 0; i < m_noofProps; i++)
				{
					Prop& prop = m_props[i];

					const uint32_t numInstances = prop.m_noofInstances;

					for (uint32_t j = 0; j < numInstances; j++)
					{
						bx::memCopy(data, prop.m_instances[j].m_bboxMin, 3 * sizeof(float));
						data[3] = (float)i; // store the drawcall ID here to avoid creating a separate buffer
						data += 4;

						bx::memCopy(data, prop.m_instances[j].m_bboxMax, 3 * sizeof(float));
						data += 4;
					}
				}

				const bgfx::Memory* mem = bgfx::makeRef(boundingBoxes, sizeof(float) * sizeOfBuffer);

				m_instanceBoundingBoxes = bgfx::createDynamicVertexBuffer(mem, computeVertexLayout, BGFX_BUFFER_COMPUTE_READ);
			}

			//pre and post occlusion culling instance data buffers
			{
				bgfx::VertexLayout instanceBufferVertexLayout;
				instanceBufferVertexLayout.begin()
					.add(bgfx::Attrib::TexCoord0, 4, bgfx::AttribType::Float)
					.add(bgfx::Attrib::TexCoord1, 4, bgfx::AttribType::Float)
					.add(bgfx::Attrib::TexCoord2, 4, bgfx::AttribType::Float)
					.add(bgfx::Attrib::TexCoord3, 4, bgfx::AttribType::Float)
					.end();

				//initialise the buffer with data for all instances
				//Currently we only store a world matrix (16 floats)
				const int sizeOfBuffer = 16 * m_totalInstancesCount;
				float* instanceData = new float[sizeOfBuffer];

				float* data = instanceData;
				for (uint16_t ii = 0; ii < m_noofProps; ++ii)
				{
					Prop& prop = m_props[ii];

					const uint32_t numInstances = prop.m_noofInstances;

					for (uint32_t jj = 0; jj < numInstances; ++jj)
					{
						bx::memCopy(data, prop.m_instances[jj].m_world, 16 * sizeof(float) );
						data[3] = float(ii); // store the drawcall ID here to avoid creating a separate buffer
						data += 16;
					}
				}

				const bgfx::Memory* mem = bgfx::makeRef(instanceData, sizeof(float) * sizeOfBuffer);

				//pre occlusion buffer
				m_instanceBuffer = bgfx::createVertexBuffer(mem, instanceBufferVertexLayout, BGFX_BUFFER_COMPUTE_READ);

				//post occlusion buffer
				m_culledInstanceBuffer = bgfx::createDynamicVertexBuffer(4 * m_totalInstancesCount, instanceBufferVertexLayout, BGFX_BUFFER_COMPUTE_WRITE);
			}

			//we use one "drawcall" per prop to render all its instances
			m_indirectBuffer = bgfx::createIndirectBuffer(m_noofProps);

			// Create programs from shaders for occlusion pass.
			m_programOcclusionPass    = loadProgram("vs_gdr_render_occlusion", NULL);
			m_programCopyZ            = loadProgram("cs_gdr_copy_z", NULL);
			m_programDownscaleHiZ     = loadProgram("cs_gdr_downscale_hi_z", NULL);
			m_programOccludeProps     = loadProgram("cs_gdr_occlude_props", NULL);
			m_programStreamCompaction = loadProgram("cs_gdr_stream_compaction", NULL);

			// Set view RENDER_PASS_HIZ_ID clear state.
			bgfx::setViewClear(RENDER_PASS_HIZ_ID
				, BGFX_CLEAR_DEPTH
				, 0x0
				, 1.0f
				, 0
			);
		}

		// Setup Main pass
		{
			// Set view 0 clear state.
			bgfx::setViewClear(RENDER_PASS_MAIN_ID
				, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
				, 0x303030ff
				, 1.0f
				, 0
			);

			// Create program from shaders.
			m_programMainPass = loadProgram("vs_gdr_instanced_indirect_rendering", "fs_gdr_instanced_indirect_rendering");
		}

		// Create static vertex buffer for all props.

		// Calculate how many vertices/indices the master buffers will need.
		uint16_t totalNoofVertices = 0;
		uint16_t totalNoofIndices = 0;
		for (uint16_t i = 0; i < m_noofProps; i++)
		{
			Prop& prop = m_props[i];

			totalNoofVertices += prop.m_noofVertices;
			totalNoofIndices += prop.m_noofIndices;
		}

		// CPU data to fill the master buffers
		m_allPropVerticesDataCPU = new PosVertex[totalNoofVertices];
		m_allPropIndicesDataCPU = new uint16_t[totalNoofIndices];
		m_indirectBufferDataCPU = new uint32_t[m_noofProps * 3];

		// Copy data over to the master buffers
		PosVertex* propVerticesData = m_allPropVerticesDataCPU;
		uint16_t* propIndicesData = m_allPropIndicesDataCPU;

		uint16_t vertexBufferOffset = 0;
		uint16_t indexBufferOffset = 0;

		for (uint16_t i = 0; i < m_noofProps; i++)
		{
			Prop& prop = m_props[i];

			bx::memCopy(propVerticesData, prop.m_vertices, prop.m_noofVertices * sizeof(PosVertex));
			bx::memCopy(propIndicesData, prop.m_indices, prop.m_noofIndices * sizeof(uint16_t));

			propVerticesData += prop.m_noofVertices;
			propIndicesData += prop.m_noofIndices;

			m_indirectBufferDataCPU[ i * 3 ] = prop.m_noofIndices;
			m_indirectBufferDataCPU[ i * 3 + 1] = indexBufferOffset;
			m_indirectBufferDataCPU[ i * 3 + 2] = vertexBufferOffset;

			indexBufferOffset += prop.m_noofIndices;
			vertexBufferOffset += prop.m_noofVertices;
		}

		// Create master vertex buffer
		m_allPropsVertexbufferHandle = bgfx::createVertexBuffer(
					  bgfx::makeRef(m_allPropVerticesDataCPU, totalNoofVertices * PosVertex::ms_layout.getStride())
					, PosVertex::ms_layout
					);

		// Create master index buffer.
		m_allPropsIndexbufferHandle = bgfx::createIndexBuffer(
					bgfx::makeRef(m_allPropIndicesDataCPU, totalNoofIndices * sizeof(uint16_t) )
					);

		// Create buffer with const drawcall data which will be copied to the indirect buffer later.
		m_indirectBufferData = bgfx::createIndexBuffer(
			bgfx::makeRef(m_indirectBufferDataCPU, m_noofProps * 3 * sizeof(uint32_t)),
			BGFX_BUFFER_COMPUTE_READ | BGFX_BUFFER_INDEX32
		);

		m_timeOffset = bx::getHPCounter();

		m_useIndirect = true;
		m_firstFrame = true;

		imguiCreate();
	}

	int shutdown() override
	{
		imguiDestroy();

		// Cleanup.

		bgfx::destroy(m_programMainPass);
		bgfx::destroy(m_programOcclusionPass);
		bgfx::destroy(m_programCopyZ);
		bgfx::destroy(m_programDownscaleHiZ);
		bgfx::destroy(m_programOccludeProps);
		bgfx::destroy(m_programStreamCompaction);

		for (uint16_t i = 0; i < m_noofProps; i++)
		{
			Prop& prop = m_props[i];

			bgfx::destroy(prop.m_indexbufferHandle);
			bgfx::destroy(prop.m_vertexbufferHandle);

			delete[] prop.m_indices;
			delete[] prop.m_vertices;
			delete[] prop.m_instances;
		}

		delete[] m_props;

		bgfx::destroy(m_hiZDepthBuffer);
		bgfx::destroy(m_hiZBuffer);
		bgfx::destroy(m_indirectBuffer);
		bgfx::destroy(m_indirectBufferData);
		bgfx::destroy(m_instanceBoundingBoxes);
		bgfx::destroy(m_drawcallInstanceCounts);
		bgfx::destroy(m_instancePredicates);
		bgfx::destroy(m_instanceBuffer);
		bgfx::destroy(m_culledInstanceBuffer);

		bgfx::destroy(m_allPropsVertexbufferHandle);
		bgfx::destroy(m_allPropsIndexbufferHandle);

		bgfx::destroy(s_texOcclusionDepth);
		bgfx::destroy(u_inputRTSize);
		bgfx::destroy(u_cullingConfig);
		bgfx::destroy(u_color);

		delete[] m_allPropVerticesDataCPU;
		delete[] m_allPropIndicesDataCPU;
		delete[] m_indirectBufferDataCPU;

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	//renders the occluders to a depth buffer
	void renderOcclusionBufferPass()
	{
		// Setup the occlusion pass projection
		bx::mtxProj(m_occlusionProj, 60.0f, float(m_hiZwidth) / float(m_hiZheight), 0.1f, 500.0f, bgfx::getCaps()->homogeneousDepth);

		bgfx::setViewTransform(RENDER_PASS_HIZ_ID, m_mainView, m_occlusionProj);

		bgfx::setViewFrameBuffer(RENDER_PASS_HIZ_ID, m_hiZDepthBuffer);
		bgfx::setViewRect(RENDER_PASS_HIZ_ID, 0, 0, uint16_t(m_hiZwidth), uint16_t(m_hiZheight));

		const uint16_t instanceStride = sizeof(InstanceData);

		// render all instances of the occluder meshes
		for (uint16_t i = 0; i < m_noofProps; i++)
		{
			Prop& prop = m_props[i];

			if (prop.m_renderPass & RenderPass::Occlusion)
			{
				const uint32_t numInstances = prop.m_noofInstances;

				// render instances to the occlusion buffer
				if (numInstances == bgfx::getAvailInstanceDataBuffer(numInstances, instanceStride))
				{
					bgfx::InstanceDataBuffer instanceBuffer;

					bgfx::allocInstanceDataBuffer(&instanceBuffer, numInstances, instanceStride);

					InstanceData *data = (InstanceData *) instanceBuffer.data;

					for (uint32_t j = 0; j < numInstances; j++)
					{
						//we only need the world matrix for the occlusion pass
						bx::memCopy(data->m_world, prop.m_instances[j].m_world, sizeof(data->m_world));
						data++;
					}

					// Set vertex and index buffer.
					bgfx::setVertexBuffer(0, prop.m_vertexbufferHandle);
					bgfx::setIndexBuffer(prop.m_indexbufferHandle);

					// Set instance data buffer.
					bgfx::setInstanceDataBuffer(&instanceBuffer);

					// Set render states.
					bgfx::setState(BGFX_STATE_DEFAULT);

					// Submit primitive for rendering to view.
					bgfx::submit(RENDER_PASS_HIZ_ID, m_programOcclusionPass);
				}
			}
		}
	}

	// downscale the occluder depth buffer to create a mipmap chain
	void renderDownscalePass()
	{
		uint32_t width = m_hiZwidth;
		uint32_t height = m_hiZheight;

		// copy mip zero over to the hi Z buffer.
		// We can't currently use blit as it requires same format and CopyResource is not exposed.
		{
			float inputRendertargetSize[4] = { (float)width, (float)height, 0.0f, 0.0f };
			bgfx::setUniform(u_inputRTSize, inputRendertargetSize);

			bgfx::setTexture(0, s_texOcclusionDepth, getTexture(m_hiZDepthBuffer, 0));
			bgfx::setImage(1, getTexture(m_hiZBuffer,      0), 0, bgfx::Access::Write);

			bgfx::dispatch(RENDER_PASS_HIZ_DOWNSCALE_ID, m_programCopyZ, width/16, height/16);
		}

		for (uint8_t lod = 1; lod < m_noofHiZMips; ++lod)
		{
			float inputRendertargetSize[4] = { (float)width, (float)height, 2.0f, 2.0f };
			bgfx::setUniform(u_inputRTSize, inputRendertargetSize);

			// down scale mip 1 onwards
			width /= 2;
			height /= 2;

			bgfx::setImage(0, getTexture(m_hiZBuffer, 0), lod - 1, bgfx::Access::Read);
			bgfx::setImage(1, getTexture(m_hiZBuffer, 0), lod,     bgfx::Access::Write);

			bgfx::dispatch(RENDER_PASS_HIZ_DOWNSCALE_ID, m_programDownscaleHiZ, width/16, height/16);
		}
	}

	// perform the occlusion using the mip chain
	void renderOccludePropsPass()
	{
		// run the computer shader to determine visibility of each instance
		bgfx::setTexture(0, s_texOcclusionDepth, bgfx::getTexture(m_hiZBuffer, 0) );

		bgfx::setBuffer(1, m_instanceBoundingBoxes,  bgfx::Access::Read);
		bgfx::setBuffer(2, m_drawcallInstanceCounts, bgfx::Access::ReadWrite);
		bgfx::setBuffer(3, m_instancePredicates,     bgfx::Access::Write);

		float inputRendertargetSize[4] = { (float)m_hiZwidth, (float)m_hiZheight, 1.0f/ m_hiZwidth, 1.0f/ m_hiZheight };
		bgfx::setUniform(u_inputRTSize, inputRendertargetSize);

		// store a rounded-up, power of two instance count for the stream compaction step
		float noofInstancesPowOf2 = bx::pow(2.0f, bx::floor(bx::log(m_totalInstancesCount) / bx::log(2.0f) ) + 1.0f);

		float cullingConfig[4] =
		{
			(float)m_totalInstancesCount,
			noofInstancesPowOf2,
			(float)m_noofHiZMips,
			(float)m_noofProps
		};
		bgfx::setUniform(u_cullingConfig, cullingConfig);

		//set the view/projection transforms so that the compute shader can receive the viewProjection matrix automagically
		bgfx::setViewTransform(RENDER_PASS_OCCLUDE_PROPS_ID, m_mainView, m_occlusionProj);

		uint16_t groupX = bx::max<uint16_t>(m_totalInstancesCount / 64 + 1, 1);

		bgfx::dispatch(RENDER_PASS_OCCLUDE_PROPS_ID, m_programOccludeProps, groupX, 1, 1);

		// perform stream compaction to remove occluded instances

		// the per drawcall data that is constant (noof indices/vertices and offsets to vertex/index buffers)
	 	bgfx::setBuffer(0, m_indirectBufferData, bgfx::Access::Read);
		// instance data for all instances (pre culling)
		bgfx::setBuffer(1, m_instanceBuffer, bgfx::Access::Read);
		// per instance visibility (output of culling pass)
		bgfx::setBuffer(2, m_instancePredicates, bgfx::Access::Read);

		// how many instances per drawcall
		bgfx::setBuffer(3, m_drawcallInstanceCounts, bgfx::Access::ReadWrite);
		// drawcall data that will drive drawIndirect
		bgfx::setBuffer(4, m_indirectBuffer, bgfx::Access::ReadWrite);
		// culled instance data
		bgfx::setBuffer(5, m_culledInstanceBuffer, bgfx::Access::Write);

		bgfx::setUniform(u_cullingConfig, cullingConfig);

		bgfx::dispatch(RENDER_PASS_COMPACT_STREAM_ID, m_programStreamCompaction, 1, 1, 1);

	}

	// render the unoccluded props to the screen
	void renderMainPass()
	{
		// Set view and projection matrix for view 0.
		{
			bgfx::setViewTransform(RENDER_PASS_MAIN_ID, m_mainView, m_mainProj);

			// Set view 0 default viewport.
			bgfx::setViewRect(RENDER_PASS_MAIN_ID, 0, 0, uint16_t(m_width), uint16_t(m_height));
		}

		// Set render states.
		bgfx::setState(BGFX_STATE_DEFAULT);

		const uint16_t instanceStride = sizeof(InstanceData);

		// Set "material" data (currently a color only)
		bgfx::setUniform(u_color, &m_materials[0].m_color, m_noofMaterials);

		// We can't use indirect drawing for the first frame because the content of m_drawcallInstanceCounts
		// is initially undefined.
		if (m_useIndirect && !m_firstFrame)
		{
			// Set vertex and index buffer.
			bgfx::setVertexBuffer(0, m_allPropsVertexbufferHandle);
			bgfx::setIndexBuffer( m_allPropsIndexbufferHandle);

			// Set instance data buffer.
			bgfx::setInstanceDataBuffer(m_culledInstanceBuffer,  0,  m_totalInstancesCount );

			bgfx::submit(RENDER_PASS_MAIN_ID, m_programMainPass, m_indirectBuffer, 0, m_noofProps);
		}
		else
		{
			// render all props using regular instancing
			for (uint16_t ii = 0; ii < m_noofProps; ++ii)
			{
				Prop& prop = m_props[ii];

				if (prop.m_renderPass & RenderPass::MainPass)
				{
					const uint32_t numInstances = prop.m_noofInstances;

					if (numInstances == bgfx::getAvailInstanceDataBuffer(numInstances, instanceStride))
					{
						bgfx::InstanceDataBuffer instanceBuffer;

						bgfx::allocInstanceDataBuffer(&instanceBuffer, numInstances, instanceStride);

						InstanceData *data = (InstanceData *)instanceBuffer.data;

						for (uint32_t jj = 0; jj < numInstances; ++jj)
						{
							//copy world matrix
							bx::memCopy(data->m_world, prop.m_instances[jj].m_world, sizeof(data->m_world) );
							//pack the material ID into the world transform
							data->m_world[3] = float(prop.m_materialID);
							data++;
						}

						// Set vertex and index buffer.
						bgfx::setVertexBuffer(0, prop.m_vertexbufferHandle);
						bgfx::setIndexBuffer(prop.m_indexbufferHandle);

						// Set instance data buffer.
						bgfx::setInstanceDataBuffer(&instanceBuffer);

						bgfx::submit(RENDER_PASS_MAIN_ID, m_programMainPass);
					}
				}
			}
		}
		m_firstFrame = false;
	}

	bool update() override
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			imguiBeginFrame(m_mouseState.m_mx
				,  m_mouseState.m_my
				, (m_mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT   : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT  : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
				,  m_mouseState.m_mz
				, uint16_t(m_width)
				, uint16_t(m_height)
				);

			showExampleDialog(this);

			ImGui::SetNextWindowPos(
				ImVec2(m_width - m_width / 5.0f - 10.0f, 10.0f)
				, ImGuiCond_FirstUseEver
			);
			ImGui::SetNextWindowSize(
				ImVec2(m_width / 5.0f, m_height / 6.0f)
				, ImGuiCond_FirstUseEver
			);
			ImGui::Begin("Settings"
				, NULL
				, 0
			);
			ImGui::Checkbox("Use Draw Indirect", &m_useIndirect);

			ImGui::End();

			imguiEndFrame();

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);

			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency());
			const float deltaTimeSec = float(double(frameTime) / freq);

			// Camera.
			const bool mouseOverGui = ImGui::MouseOverArea();
			m_mouse.update(float(m_mouseState.m_mx), float(m_mouseState.m_my), m_mouseState.m_mz, m_width, m_height);
			if (!mouseOverGui)
			{
				if (m_mouseState.m_buttons[entry::MouseButton::Left])
				{
					m_camera.orbit(m_mouse.m_dx, m_mouse.m_dy);
				}
				else if (m_mouseState.m_buttons[entry::MouseButton::Right])
				{
					m_camera.dolly(m_mouse.m_dx + m_mouse.m_dy);
				}
				else if (0 != m_mouse.m_scroll)
				{
					m_camera.dolly(float(m_mouse.m_scroll)*0.05f);
				}
			}

			m_camera.update(deltaTimeSec);

			// Get renderer capabilities info.
			const bgfx::Caps* caps = bgfx::getCaps();

			// Check if instancing is supported.
			if (0 == (BGFX_CAPS_INSTANCING & caps->supported) )
			{
				// When instancing is not supported by GPU, implement alternative
				// code path that doesn't use instancing.
				float time = (float)((bx::getHPCounter() - m_timeOffset) / double(bx::getHPFrequency()));
				bool blink = uint32_t(time*3.0f)&1;
				bgfx::dbgTextPrintf(0, 0, blink ? 0x1f : 0x01, " Instancing is not supported by GPU. ");
			}
			else
			{
				// calculate main view and project matrices as they are typically reused between passes.
				m_camera.mtxLookAt(m_mainView);
				bx::mtxProj(m_mainProj, 60.0f, float(m_width) / float(m_height), 0.1f, 500.0f, bgfx::getCaps()->homogeneousDepth);

				//submit drawcalls for all passes
				renderOcclusionBufferPass();

				renderDownscalePass();

				renderOccludePropsPass();

				renderMainPass();
			}

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();

			return true;
		}

		return false;
	}

	entry::MouseState m_mouseState;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_hiZwidth;
	uint32_t m_hiZheight;
	uint32_t m_debug;
	uint32_t m_reset;

	float m_mainView[16];
	float m_mainProj[16];
	float m_occlusionProj[16];

	bgfx::ProgramHandle m_programMainPass;
	bgfx::ProgramHandle m_programOcclusionPass;
	bgfx::ProgramHandle m_programCopyZ;
	bgfx::ProgramHandle m_programDownscaleHiZ;
	bgfx::ProgramHandle m_programOccludeProps;
	bgfx::ProgramHandle m_programStreamCompaction;

	bgfx::FrameBufferHandle m_hiZDepthBuffer;
	bgfx::FrameBufferHandle m_hiZBuffer;
	bgfx::IndirectBufferHandle m_indirectBuffer;

	bgfx::VertexBufferHandle m_allPropsVertexbufferHandle;
	bgfx::IndexBufferHandle  m_allPropsIndexbufferHandle;
	bgfx::IndexBufferHandle m_indirectBufferData;

	PosVertex* m_allPropVerticesDataCPU;
	uint16_t* m_allPropIndicesDataCPU;
	uint32_t* m_indirectBufferDataCPU;

	bgfx::DynamicVertexBufferHandle m_instanceBoundingBoxes;
	bgfx::DynamicIndexBufferHandle m_drawcallInstanceCounts;
	bgfx::DynamicIndexBufferHandle m_instancePredicates;
	bgfx::VertexBufferHandle m_instanceBuffer;
	bgfx::DynamicVertexBufferHandle m_culledInstanceBuffer;

	bgfx::UniformHandle s_texOcclusionDepth;
	bgfx::UniformHandle u_inputRTSize;
	bgfx::UniformHandle u_cullingConfig;
	bgfx::UniformHandle u_color;

	Prop*	m_props;
	Material* m_materials;
	uint16_t m_noofProps;
	uint16_t m_noofMaterials;
	uint16_t m_totalInstancesCount;

	static const uint16_t s_maxNoofProps = 10;

	static const uint16_t s_maxNoofInstances = 2048;

	int64_t m_timeOffset;

	uint8_t m_noofHiZMips;

	bool m_useIndirect;
	bool m_firstFrame;

	Camera m_camera;
	Mouse m_mouse;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  GPUDrivenRendering
	, "37-gpudrivenrendering"
	, "GPU-Driven Rendering."
	, "https://bkaradzic.github.io/bgfx/examples.html#gpudrivenrendering"
	);
