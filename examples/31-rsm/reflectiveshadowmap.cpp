/*
 * Copyright 2016 Joseph Cherlin. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "camera.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"
#include <bx/rng.h>

/*
 * Intro
 * =====
 *
 * RSM (reflective shadow map) is a technique for global illumination.
 * It is similar to shadow map.  It piggybacks on the shadow map, in fact.
 *
 * RSM is compatible with any type of lighting which can handle handle
 * a lot of point lights.  This sample happens to use a deferred renderer,
 * but other types would work.
 *
 * Overview:
 *
 *  - Draw into G-Buffer
 *  - Draw Shadow Map (with RSM piggybacked on)
 *  - Populate light buffer
 *  - Deferred "combine" pass.
 *
 * Details
 * =======
 *
 * ## G-Buffer
 *
 * Typical G-Buffer with normals, color, depth.
 *
 * ## RSM
 *
 * A typical shadow map, except it also outputs to a "RSM" buffer.
 * The RSM contains the color of the item drawn, as well as a scalar value which represents
 * how much light would bounce off of the surface if it were hit with light from the origin
 * of the shadow map.
 *
 * ## Light Buffer
 *
 * We draw a lot of spheres into the light buffer.  These spheres are called VPL (virtual
 * point lights).  VPLs represent bounced light, and let us eliminate the classic "ambient"
 * term.  Instead of us supplying their world space position in a transform matrix,
 * VPLs gain their position from the shadow map from step 2, using an unprojection.  They gain
 * their color from the RSM.  You could also store their position in a buffer while drawing shadows,
 * I'm just using depth to keep the sample smaller.
 *
 * ## Deferred combine
 *
 * Typical combine used in almost any sort of deferred renderer.
 *
 * References
 * ==========
 *
 * http: *www.bpeers.com/blog/?itemid=517
 *
 */

// Render passes
#define RENDER_PASS_GBUFFER      0  // GBuffer for normals and albedo
#define RENDER_PASS_SHADOW_MAP   1  // Draw into the shadow map (RSM and regular shadow map at same time)
#define RENDER_PASS_LIGHT_BUFFER 2  // Light buffer for point lights
#define RENDER_PASS_COMBINE      3  // Directional light and final result

// Gbuffer has multiple render targets
#define GBUFFER_RT_NORMAL 0
#define GBUFFER_RT_COLOR  1
#define GBUFFER_RT_DEPTH  2

// Shadow map has multiple render targets
#define SHADOW_RT_RSM   0        // In this algorithm, shadows write lighting info as well.
#define SHADOW_RT_DEPTH 1        // Shadow maps always write a depth

// Random meshes we draw
#define MODEL_COUNT 222  // In this demo, a model is a mesh plus a transform and a color

#define SHADOW_MAP_DIM 512
#define LIGHT_DIST 10.0f

static const char * s_meshPaths[] =
{
	"meshes/cube.bin",
	"meshes/orb.bin",
	"meshes/column.bin",
	"meshes/bunny.bin",
	"meshes/tree.bin",
	"meshes/hollowcube.bin"
};

static const float s_meshScale[] =
{
	0.25f,
	0.5f,
	0.05f,
	0.5f,
	0.05f,
	0.05f
};

// Vertex decl for our screen space quad (used in deferred rendering)
struct PosTexCoord0Vertex
{
	float m_x;
	float m_y;
	float m_z;
	float m_u;
	float m_v;

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.end();
	}

	static bgfx::VertexDecl ms_decl;
};
bgfx::VertexDecl PosTexCoord0Vertex::ms_decl;

// Utility function to draw a screen space quad for deferred rendering
void screenSpaceQuad(float _textureWidth, float _textureHeight, float _texelHalf, bool _originBottomLeft, float _width = 1.0f, float _height = 1.0f)
{
	if (3 == bgfx::getAvailTransientVertexBuffer(3, PosTexCoord0Vertex::ms_decl) )
	{
		bgfx::TransientVertexBuffer vb;
		bgfx::allocTransientVertexBuffer(&vb, 3, PosTexCoord0Vertex::ms_decl);
		PosTexCoord0Vertex* vertex = (PosTexCoord0Vertex*)vb.data;

		const float minx = -_width;
		const float maxx =  _width;
		const float miny = 0.0f;
		const float maxy = _height*2.0f;

		const float texelHalfW = _texelHalf/_textureWidth;
		const float texelHalfH = _texelHalf/_textureHeight;
		const float minu = -1.0f + texelHalfW;
		const float maxu =  1.0f + texelHalfH;

		const float zz = 0.0f;

		float minv = texelHalfH;
		float maxv = 2.0f + texelHalfH;

		if (_originBottomLeft)
		{
			float temp = minv;
			minv = maxv;
			maxv = temp;

			minv -= 1.0f;
			maxv -= 1.0f;
		}

		vertex[0].m_x = minx;
		vertex[0].m_y = miny;
		vertex[0].m_z = zz;
		vertex[0].m_u = minu;
		vertex[0].m_v = minv;

		vertex[1].m_x = maxx;
		vertex[1].m_y = miny;
		vertex[1].m_z = zz;
		vertex[1].m_u = maxu;
		vertex[1].m_v = minv;

		vertex[2].m_x = maxx;
		vertex[2].m_y = maxy;
		vertex[2].m_z = zz;
		vertex[2].m_u = maxu;
		vertex[2].m_v = maxv;

		bgfx::setVertexBuffer(&vb);
	}
}

class ExampleRSM : public entry::AppI
{
public:
	ExampleRSM()
		: m_reading(0)
		, m_currFrame(UINT32_MAX)
		, m_cameraSpin(false)
		, m_lightElevation(35.0f)
		, m_lightAzimuth(215.0f)
		, m_rsmAmount(0.25f)
		, m_vplRadius(3.0f)
		, m_texelHalf(0.0f)
	{
	}

	void init(int _argc, char** _argv) BX_OVERRIDE
	{
		Args args(_argc, _argv);

		m_width  = 1280;
		m_height = 720;
		m_debug  = BGFX_DEBUG_TEXT;
		m_reset  = BGFX_RESET_VSYNC;

		bgfx::init(args.m_type, args.m_pciId);

		bgfx::reset(m_width, m_height, m_reset);

		// Enable debug text.
		bgfx::setDebug(m_debug);

		// Labeling for renderdoc captures, etc
		bgfx::setViewName(RENDER_PASS_GBUFFER,      "gbuffer"     );
		bgfx::setViewName(RENDER_PASS_SHADOW_MAP,   "shadow map"  );
		bgfx::setViewName(RENDER_PASS_LIGHT_BUFFER, "light buffer");
		bgfx::setViewName(RENDER_PASS_COMBINE,      "post combine");

		// Set up screen clears
		bgfx::setViewClear(RENDER_PASS_GBUFFER
				, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
				, 0
				, 1.0f
				, 0
				);

		bgfx::setViewClear(RENDER_PASS_LIGHT_BUFFER
				, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
				, 0
				, 1.0f
				, 0
				);

		bgfx::setViewClear(RENDER_PASS_SHADOW_MAP
				, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
				, 0
				, 1.0f
				, 0
				);

		// Create uniforms
		u_tint          = bgfx::createUniform("u_tint",          bgfx::UniformType::Vec4);  // Tint for when you click on items
		u_lightDir      = bgfx::createUniform("u_lightDir",      bgfx::UniformType::Vec4);  // Single directional light for entire scene
		u_sphereInfo    = bgfx::createUniform("u_sphereInfo",    bgfx::UniformType::Vec4);  // Info for RSM
		u_invMvp        = bgfx::createUniform("u_invMvp",        bgfx::UniformType::Mat4);  // Matrix needed in light buffer
		u_invMvpShadow  = bgfx::createUniform("u_invMvpShadow",  bgfx::UniformType::Mat4);  // Matrix needed in light buffer
		u_lightMtx      = bgfx::createUniform("u_lightMtx",      bgfx::UniformType::Mat4);  // Matrix needed to use shadow map (world to shadow space)
		u_shadowDimsInv = bgfx::createUniform("u_shadowDimsInv", bgfx::UniformType::Vec4);  // Used in PCF
		u_rsmAmount     = bgfx::createUniform("u_rsmAmount",     bgfx::UniformType::Vec4);  // How much RSM to use vs directional light

		// Create texture sampler uniforms (used when we bind textures)
		s_normal    = bgfx::createUniform("s_normal",    bgfx::UniformType::Int1);  // Normal gbuffer
		s_depth     = bgfx::createUniform("s_depth",     bgfx::UniformType::Int1);  // Normal gbuffer
		s_color     = bgfx::createUniform("s_color",     bgfx::UniformType::Int1);  // Color (albedo) gbuffer
		s_light     = bgfx::createUniform("s_light",     bgfx::UniformType::Int1);  // Light buffer
		s_shadowMap = bgfx::createUniform("s_shadowMap", bgfx::UniformType::Int1);  // Shadow map
		s_rsm       = bgfx::createUniform("s_rsm",       bgfx::UniformType::Int1);  // Reflective shadow map

		// Create program from shaders.
		m_gbufferProgram = loadProgram("vs_rsm_gbuffer", "fs_rsm_gbuffer");  // Gbuffer
		m_shadowProgram  = loadProgram("vs_rsm_shadow",  "fs_rsm_shadow"  ); // Drawing shadow map
		m_lightProgram   = loadProgram("vs_rsm_lbuffer", "fs_rsm_lbuffer");  // Light buffer
		m_combineProgram = loadProgram("vs_rsm_combine", "fs_rsm_combine");  // Combiner

		// Load some meshes
		for (uint32_t ii = 0; ii < BX_COUNTOF(s_meshPaths); ++ii)
		{
			m_meshes[ii] = meshLoad(s_meshPaths[ii]);
		}

		// Randomly create some models
		bx::RngMwc mwc;  // Random number generator
		for (uint32_t ii = 0; ii < BX_COUNTOF(m_models); ++ii)
		{
			Model& model = m_models[ii];

			uint32_t rr = mwc.gen() % 256;
			uint32_t gg = mwc.gen() % 256;
			uint32_t bb = mwc.gen() % 256;
			model.mesh = 1+mwc.gen()%(BX_COUNTOF(s_meshPaths)-1);
			model.color[0] = rr/255.0f;
			model.color[1] = gg/255.0f;
			model.color[2] = bb/255.0f;
			model.color[3] = 1.0f;
			model.position[0] = (((mwc.gen() % 256)) - 128.0f)/20.0f;
			model.position[1] = 0;
			model.position[2] = (((mwc.gen() % 256)) - 128.0f)/20.0f;
		}

		// Load ground.  We'll just use the cube since I don't have a ground model right now
		m_ground = meshLoad("meshes/cube.bin");

		// Light sphere
		m_lightSphere = meshLoad("meshes/unit_sphere.bin");

		const uint32_t samplerFlags = 0
			| BGFX_TEXTURE_RT
			| BGFX_TEXTURE_MIN_POINT
			| BGFX_TEXTURE_MAG_POINT
			| BGFX_TEXTURE_MIP_POINT
			| BGFX_TEXTURE_U_CLAMP
			| BGFX_TEXTURE_V_CLAMP
			;

		// Make gbuffer and related textures
		m_gbufferTex[GBUFFER_RT_NORMAL] = bgfx::createTexture2D(bgfx::BackbufferRatio::Equal, false, 1, bgfx::TextureFormat::BGRA8, samplerFlags);
		m_gbufferTex[GBUFFER_RT_COLOR]  = bgfx::createTexture2D(bgfx::BackbufferRatio::Equal, false, 1, bgfx::TextureFormat::BGRA8, samplerFlags);
		m_gbufferTex[GBUFFER_RT_DEPTH]  = bgfx::createTexture2D(bgfx::BackbufferRatio::Equal, false, 1, bgfx::TextureFormat::D24,   samplerFlags);
		m_gbuffer = bgfx::createFrameBuffer(BX_COUNTOF(m_gbufferTex), m_gbufferTex, true);

		// Make light buffer
		m_lightBufferTex = bgfx::createTexture2D(bgfx::BackbufferRatio::Equal, false, 1, bgfx::TextureFormat::BGRA8, samplerFlags);
		bgfx::TextureHandle lightBufferRTs[] =  {
			m_lightBufferTex
		};
		m_lightBuffer = bgfx::createFrameBuffer(BX_COUNTOF(lightBufferRTs), lightBufferRTs, true);

		// Make shadow buffer
		const uint32_t rsmFlags = 0
			| BGFX_TEXTURE_RT
			| BGFX_TEXTURE_MIN_POINT
			| BGFX_TEXTURE_MAG_POINT
			| BGFX_TEXTURE_MIP_POINT
			| BGFX_TEXTURE_U_CLAMP
			| BGFX_TEXTURE_V_CLAMP
			;

		// Reflective shadow map
		m_shadowBufferTex[SHADOW_RT_RSM] = bgfx::createTexture2D(
				  SHADOW_MAP_DIM
				, SHADOW_MAP_DIM
				, false
				, 1
				, bgfx::TextureFormat::BGRA8,
				rsmFlags
				);

		// Typical shadow map
		m_shadowBufferTex[SHADOW_RT_DEPTH] = bgfx::createTexture2D(
				  SHADOW_MAP_DIM
				, SHADOW_MAP_DIM
				, false
				, 1
				, bgfx::TextureFormat::D16,
				BGFX_TEXTURE_RT/* | BGFX_TEXTURE_COMPARE_LEQUAL*/
				);  // Note I'm not setting BGFX_TEXTURE_COMPARE_LEQUAL.  Why?
		// Normally a PCF shadow map such as this requires a compare.  However, this sample also
		// reads from this texture in the lighting pass, and only uses the PCF capabilites in the
		// combine pass, so the flag is disabled by default.

		m_shadowBuffer = bgfx::createFrameBuffer(BX_COUNTOF(m_shadowBufferTex), m_shadowBufferTex, true);

		// Vertex decl
		PosTexCoord0Vertex::init();

		// Init camera
		cameraCreate();
		float camPos[] = {0.0f, 1.5f, 0.0f};
		cameraSetPosition(camPos);
		cameraSetVerticalAngle(-0.3f);

		// Init directional light
		updateLightDir();

		// Get renderer capabilities info.
		m_caps = bgfx::getCaps();
		const bgfx::RendererType::Enum renderer = bgfx::getRendererType();
		m_texelHalf = bgfx::RendererType::Direct3D9 == renderer ? 0.5f : 0.0f;

		imguiCreate();
	}

	int shutdown() BX_OVERRIDE
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(s_meshPaths); ++ii)
		{
			meshUnload(m_meshes[ii]);
		}

		meshUnload(m_ground);
		meshUnload(m_lightSphere);

		// Cleanup.
		bgfx::destroyProgram(m_gbufferProgram);
		bgfx::destroyProgram(m_lightProgram);
		bgfx::destroyProgram(m_combineProgram);
		bgfx::destroyProgram(m_shadowProgram);

		bgfx::destroyUniform(u_tint);
		bgfx::destroyUniform(u_lightDir);
		bgfx::destroyUniform(u_sphereInfo);
		bgfx::destroyUniform(u_invMvp);
		bgfx::destroyUniform(u_invMvpShadow);
		bgfx::destroyUniform(u_lightMtx);
		bgfx::destroyUniform(u_shadowDimsInv);
		bgfx::destroyUniform(u_rsmAmount);
		bgfx::destroyUniform(s_normal);
		bgfx::destroyUniform(s_depth);
		bgfx::destroyUniform(s_light);
		bgfx::destroyUniform(s_color);
		bgfx::destroyUniform(s_shadowMap);
		bgfx::destroyUniform(s_rsm);

		bgfx::destroyFrameBuffer(m_gbuffer);
		bgfx::destroyFrameBuffer(m_lightBuffer);
		bgfx::destroyFrameBuffer(m_shadowBuffer);

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_gbufferTex); ++ii)
		{
			bgfx::destroyTexture(m_gbufferTex[ii]);
		}

		bgfx::destroyTexture(m_lightBufferTex);
		for (uint32_t ii = 0; ii < BX_COUNTOF(m_shadowBufferTex); ++ii)
		{
			bgfx::destroyTexture(m_shadowBufferTex[ii]);
		}

		cameraDestroy();

		imguiDestroy();

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	bool update() BX_OVERRIDE
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			// Update frame timer
			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency());
			const double toMs = 1000.0 / freq;
			const float deltaTime = float(frameTime/freq);

			// Use debug font to print information about this example.
			bgfx::dbgTextClear();
			bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/31-rsm");
			bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Global Illumination with Reflective Shadow Map.");
			bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

			// Update camera
			cameraUpdate(deltaTime*0.15f, m_mouseState);

			// Set up matrices for gbuffer
			float view[16];
			cameraGetViewMtx(view);

			float proj[16];
			bx::mtxProj(proj, 60.0f, float(m_width)/float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);

			bgfx::setViewRect(RENDER_PASS_GBUFFER, 0, 0, uint16_t(m_width), uint16_t(m_height));
			bgfx::setViewTransform(RENDER_PASS_GBUFFER, view, proj);
			// Make sure when we draw it goes into gbuffer and not backbuffer
			bgfx::setViewFrameBuffer(RENDER_PASS_GBUFFER, m_gbuffer);
			// Draw everything into g-buffer
			drawAllModels(RENDER_PASS_GBUFFER, m_gbufferProgram);

			// Draw shadow map

			// Set up transforms for shadow map
			float smView[16], smProj[16], lightEye[3], lightAt[3];
			lightEye[0] = m_lightDir[0]*LIGHT_DIST;
			lightEye[1] = m_lightDir[1]*LIGHT_DIST;
			lightEye[2] = m_lightDir[2]*LIGHT_DIST;

			lightAt[0] = 0.0f;
			lightAt[1] = 0.0f;
			lightAt[2] = 0.0f;

			bx::mtxLookAt(smView, lightEye, lightAt);
			const float area = 10.0f;
			bgfx::RendererType::Enum renderer = bgfx::getRendererType();
			bool flipV = false
				|| renderer == bgfx::RendererType::OpenGL
				|| renderer == bgfx::RendererType::OpenGLES
				;
			bx::mtxOrtho(smProj, -area, area, -area, area, -100.0f, 100.0f, 0.0f, flipV);
			bgfx::setViewTransform(RENDER_PASS_SHADOW_MAP, smView, smProj);
			bgfx::setViewFrameBuffer(RENDER_PASS_SHADOW_MAP, m_shadowBuffer);
			bgfx::setViewRect(RENDER_PASS_SHADOW_MAP, 0, 0, SHADOW_MAP_DIM, SHADOW_MAP_DIM);

			drawAllModels(RENDER_PASS_SHADOW_MAP, m_shadowProgram);

			// Next draw light buffer

			// Set up matrices for light buffer
			bgfx::setViewRect(RENDER_PASS_LIGHT_BUFFER, 0, 0, uint16_t(m_width), uint16_t(m_height));
			bgfx::setViewTransform(RENDER_PASS_LIGHT_BUFFER, view, proj);  // Notice, same view and proj as gbuffer
			// Set drawing into light buffer
			bgfx::setViewFrameBuffer(RENDER_PASS_LIGHT_BUFFER, m_lightBuffer);

			// Inverse view projection is needed in shader so set that up
			float vp[16], invMvp[16];
			bx::mtxMul(vp, view, proj);
			bx::mtxInverse(invMvp, vp);

			// Light matrix used in combine pass and inverse used in light pass
			float lightMtx[16]; // World space to light space (shadow map space)
			bx::mtxMul(lightMtx, smView, smProj);
			float invMvpShadow[16];
			bx::mtxInverse(invMvpShadow, lightMtx);

			// Draw some lights (these should really be instanced but for this example they aren't...)
			const unsigned MAX_SPHERE = 32;
			for (uint32_t i = 0; i < MAX_SPHERE; i++)
			{
				for (uint32_t j = 0; j < MAX_SPHERE; j++)
				{
					// These are used in the fragment shader
					bgfx::setTexture(0, s_normal, bgfx::getTexture(m_gbuffer, GBUFFER_RT_NORMAL) );  // Normal for lighting calculations
					bgfx::setTexture(1, s_depth,  bgfx::getTexture(m_gbuffer, GBUFFER_RT_DEPTH) );   // Depth to reconstruct world position

					// Thse are used in the vert shader
					bgfx::setTexture(2, s_shadowMap, bgfx::getTexture(m_shadowBuffer, SHADOW_RT_DEPTH) );  // Used to place sphere
					bgfx::setTexture(3, s_rsm,       bgfx::getTexture(m_shadowBuffer, SHADOW_RT_RSM) );    // Used to scale/color sphere

					bgfx::setUniform(u_invMvp, invMvp);
					bgfx::setUniform(u_invMvpShadow, invMvpShadow);
					float sphereInfo[4];
					sphereInfo[0] = ((float)i/(MAX_SPHERE-1));
					sphereInfo[1] = ((float)j/(MAX_SPHERE-1));
					sphereInfo[2] = m_vplRadius;
					sphereInfo[3] = 0.0;  // Unused
					bgfx::setUniform(u_sphereInfo, sphereInfo);

					const uint64_t lightDrawState = 0
						| BGFX_STATE_RGB_WRITE
						| BGFX_STATE_BLEND_ADD   // <===  Overlapping lights contribute more
						| BGFX_STATE_ALPHA_WRITE
						| BGFX_STATE_CULL_CW     // <===  If we go into the lights, there will be problems, so we draw the far back face.
						;

					meshSubmit(
							m_lightSphere,
							RENDER_PASS_LIGHT_BUFFER,
							m_lightProgram,
							NULL,
							lightDrawState
							);
				}
			}

			// Draw combine pass

			// Texture inputs for combine pass
			bgfx::setTexture(0, s_normal,    bgfx::getTexture(m_gbuffer, GBUFFER_RT_NORMAL) );
			bgfx::setTexture(1, s_color,     bgfx::getTexture(m_gbuffer, GBUFFER_RT_COLOR) );
			bgfx::setTexture(2, s_light,     bgfx::getTexture(m_lightBuffer, 0) );
			bgfx::setTexture(3, s_depth,     bgfx::getTexture(m_gbuffer, GBUFFER_RT_DEPTH) );
			bgfx::setTexture(4, s_shadowMap, bgfx::getTexture(m_shadowBuffer, SHADOW_RT_DEPTH)
				, BGFX_TEXTURE_COMPARE_LEQUAL
				);

			// Uniforms for combine pass

			bgfx::setUniform(u_lightDir, m_lightDir);
			bgfx::setUniform(u_invMvp, invMvp);
			bgfx::setUniform(u_lightMtx, lightMtx);
			const float invDim[4] = {1.0f/SHADOW_MAP_DIM, 0.0f, 0.0f, 0.0f};
			bgfx::setUniform(u_shadowDimsInv, invDim);
			float rsmAmount[4] = {m_rsmAmount,m_rsmAmount,m_rsmAmount,m_rsmAmount};
			bgfx::setUniform(u_rsmAmount, rsmAmount);

			// Set up state for combine pass
			// point of this is to avoid doing depth test, which is in the default state
			bgfx::setState(0
					| BGFX_STATE_RGB_WRITE
					| BGFX_STATE_ALPHA_WRITE
					);

			// Set up transform matrix for fullscreen quad
			float orthoProj[16];
			bx::mtxOrtho(orthoProj, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 100.0f);
			bgfx::setViewTransform(RENDER_PASS_COMBINE,   NULL, orthoProj);
			bgfx::setViewRect(RENDER_PASS_COMBINE, 0, 0, m_width, m_height);
			// Bind vertex buffer and draw quad
			screenSpaceQuad( (float)m_width, (float)m_height, m_texelHalf, m_caps->originBottomLeft);
			bgfx::submit(RENDER_PASS_COMBINE, m_combineProgram);

			// Draw UI
			imguiBeginFrame(m_mouseState.m_mx
					, m_mouseState.m_my
					, (m_mouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0)
					| (m_mouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0)
					| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
					, m_mouseState.m_mz
					, m_width
					, m_height
					);

			imguiBeginArea("RSM:", 10, 100, 300, 400);

			imguiSlider("rsm amount", m_rsmAmount, 0.0f, 0.7f, 0.01f);
			imguiSlider("vpl radius", m_vplRadius, 0.25f, 20.0f, 0.1f);
			imguiSlider("light azimuth", m_lightAzimuth, 0.0f, 360.0f, 0.01f);
			imguiSlider("light elevation", m_lightElevation, 35.0f, 90.0f, 0.01f);

			imguiEndArea();
			imguiEndFrame();

			updateLightDir();

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			m_currFrame = bgfx::frame();

			return true;
		}

		return false;
	}

	void drawAllModels(uint8_t _pass, bgfx::ProgramHandle _program)
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(m_models); ++ii)
		{
			const Model& model = m_models[ii];

			// Set up transform matrix for each model
			float scale = s_meshScale[model.mesh];
			float mtx[16];
			bx::mtxSRT(mtx
					, scale
					, scale
					, scale
					, 0.0f
					, 0.0f
					, 0.0f
					, model.position[0]
					, model.position[1]
					, model.position[2]
					);

			// Submit mesh to gbuffer
			bgfx::setUniform(u_tint, model.color);
			meshSubmit(m_meshes[model.mesh], _pass, _program, mtx);
		}

		// Draw ground
		const float white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		bgfx::setUniform(u_tint, white);
		float mtxScale[16];
		float scale = 10.0;
		bx::mtxScale(mtxScale
				, scale
				, scale
				, scale
				);
		float mtxTrans[16];
		bx::mtxTranslate(mtxTrans
				, 0.0f
				, -10.0f
				, 0.0f
				);
		float mtx[16];
		bx::mtxMul(mtx, mtxScale, mtxTrans);
		meshSubmit(m_ground, _pass, _program, mtx);
	}

	void updateLightDir()
	{
		float el = m_lightElevation * (bx::pi/180.0f);
		float az = m_lightAzimuth   * (bx::pi/180.0f);
		m_lightDir[0] = bx::fcos(el)*bx::fcos(az);
		m_lightDir[2] = bx::fcos(el)*bx::fsin(az);
		m_lightDir[1] = bx::fsin(el);
		m_lightDir[3] = 0.0f;
	}

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

	entry::MouseState m_mouseState;

	Mesh* m_ground;
	Mesh* m_lightSphere; // Unit sphere

	// Resource handles
	bgfx::ProgramHandle m_gbufferProgram;
	bgfx::ProgramHandle m_shadowProgram;
	bgfx::ProgramHandle m_lightProgram;
	bgfx::ProgramHandle m_combineProgram;
	bgfx::FrameBufferHandle m_gbuffer;
	bgfx::FrameBufferHandle m_lightBuffer;
	bgfx::FrameBufferHandle m_shadowBuffer;

	// Shader uniforms
	bgfx::UniformHandle u_tint;
	bgfx::UniformHandle u_invMvp;
	bgfx::UniformHandle u_invMvpShadow;
	bgfx::UniformHandle u_lightMtx;
	bgfx::UniformHandle u_lightDir;
	bgfx::UniformHandle u_sphereInfo;
	bgfx::UniformHandle u_shadowDimsInv;
	bgfx::UniformHandle u_rsmAmount;

	// Uniforms to identify texture samples
	bgfx::UniformHandle s_normal;
	bgfx::UniformHandle s_depth;
	bgfx::UniformHandle s_color;
	bgfx::UniformHandle s_light;
	bgfx::UniformHandle s_shadowMap;
	bgfx::UniformHandle s_rsm;

	// Various render targets
	bgfx::TextureHandle m_gbufferTex[3];
	bgfx::TextureHandle m_lightBufferTex;
	bgfx::TextureHandle m_shadowBufferTex[2];

	const bgfx::Caps* m_caps;

	struct Model
	{
		uint32_t mesh; // Index of mesh in m_meshes
		float color[4];
		float position[3];
	};

	Model m_models[MODEL_COUNT];
	Mesh * m_meshes[BX_COUNTOF(s_meshPaths)];

	uint32_t m_reading;
	uint32_t m_currFrame;

	// UI
	bool m_cameraSpin;

	// Light position;
	float m_lightDir[4];
	float m_lightElevation;
	float m_lightAzimuth;

	float m_rsmAmount; // Amount of rsm
	float m_vplRadius; // Radius of virtual point light

	float m_texelHalf;
};

ENTRY_IMPLEMENT_MAIN(ExampleRSM);
