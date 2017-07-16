/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */
#include <iostream>

#include "common.h"
#include "bgfx_utils.h"
#include "string.h"
#include "entry/input.h"

// Position and texture UV vertex
struct PosUvVertex
{
    float m_x;
    float m_y;
    float m_u;
    float m_v;

    static void init()
    {
        ms_decl
            .begin()
            .add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
            .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
            .end();
    }

    static bgfx::VertexDecl ms_decl;
};
bgfx::VertexDecl PosUvVertex::ms_decl;

// 2D pos, RGB color
struct PosRGBVertex
{
	float m_x;
	float m_y;
	float m_r;
	float m_g;
	float m_b;

    PosRGBVertex(float x, float y, float r, float g, float b) :
        m_x(x), m_y(y), m_r(r), m_g(g), m_b(b) { }

	static void init(){
	ms_decl
		.begin()
		.add(bgfx::Attrib::Position,  2, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 3, bgfx::AttribType::Float)
		.end();
    }
	static bgfx::VertexDecl ms_decl;
};
bgfx::VertexDecl PosRGBVertex::ms_decl;


// 2D pos, RGB color, XY scale
struct PosRGBScaleVertex
{
    float m_x;
    float m_y;
    float m_r;
    float m_g;
    float m_b;
    float m_scale;
 
    PosRGBScaleVertex(float x, float y, float r, float g, float b, float s) :
        m_x(x), m_y(y), m_r(r), m_g(g), m_b(b), m_scale(s) { }

    static void init(){
    ms_decl
        .begin()
        .add(bgfx::Attrib::Position,  2, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Color0,    3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::TexCoord0, 1, bgfx::AttribType::Float)
        .end();
    }
    static bgfx::VertexDecl ms_decl;
};
bgfx::VertexDecl PosRGBScaleVertex::ms_decl;


class ExampleCubes : public entry::AppI
{
	void init(int _argc, char** _argv) BX_OVERRIDE
	{
		Args args(_argc, _argv);

		m_width  = mBaseWidth/2;
		m_height = mBaseHeight/2;
		m_debug  = BGFX_DEBUG_TEXT;
		m_reset  = BGFX_RESET_VSYNC;

        // HARD CODE TO OPENGL
		bgfx::init(bgfx::RendererType::OpenGL, args.m_pciId);
		bgfx::reset(m_width, m_height, m_reset);

		bgfx::setDebug(m_debug);
        PosUvVertex::init();
        PosRGBVertex::init();
        PosRGBScaleVertex::init();

        m_box1Program = loadProgram("vs_box1", "fs_box1");
        m_box2Program = loadProgram("vs_box2", "fs_box2");
        m_textureProgram = loadProgram("vs_texture", "fs_texture");

        m_texUniform = bgfx::createUniform("s_texColor", bgfx::UniformType::Int1);

        const uint32_t nearestRTT = 0
            | BGFX_TEXTURE_RT
            | BGFX_TEXTURE_MIN_POINT
            | BGFX_TEXTURE_MAG_POINT
            | BGFX_TEXTURE_MIP_POINT
            ;
        // Create the off-screen texture that 2 boxes are rendered to
        m_offscreenTexture = bgfx::createTexture2D(mBaseWidth, mBaseHeight, false, 1, bgfx::TextureFormat::RGBA8, nearestRTT, nullptr);

        // Create the FBO to render to the off-screen texture
        m_FBO = bgfx::createFrameBuffer(1, &m_offscreenTexture);

        bgfx::setViewClear(BOX1_VID
            , BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
            , 0x303030ff
            , 1.0f
            , 0
        );
    }

	virtual int shutdown() BX_OVERRIDE
	{
		// Cleanup.
        bgfx::destroyProgram(m_box1Program);
        bgfx::destroyProgram(m_box2Program);
        bgfx::destroyProgram(m_textureProgram);
        bgfx::destroyFrameBuffer(m_FBO);
        bgfx::destroyTexture(m_offscreenTexture);

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	bool update() BX_OVERRIDE
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset) )
		{
            render();

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();

			return true;
		}

		return false;
	}

    // View IDs for rendering
    enum { BOX1_VID=10, BOX2_VID=11, SCREEN_VID=12 };

    const uint16_t mBaseWidth = 1024;
    const uint16_t mBaseHeight = 1024;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;
    bgfx::ProgramHandle m_box1Program;
    bgfx::ProgramHandle m_box2Program;
    bgfx::ProgramHandle m_textureProgram;
    bgfx::TextureHandle m_offscreenTexture;
    bgfx::UniformHandle m_texUniform;
    bgfx::FrameBufferHandle m_FBO;

    void render()
    {
        const bgfx::Caps* caps = bgfx::getCaps();
        // Draw a RED box (200x200) in the middle of the texture attached to the FBO
        {
            float proj[16];
            bgfx::setViewFrameBuffer(BOX1_VID, m_FBO);
            bx::mtxOrtho(proj, float(-mBaseWidth / 2), float(mBaseWidth / 2), float(-mBaseHeight / 2), float(mBaseHeight / 2), -1.0f, 100.0f, 0.0f, caps->homogeneousDepth);
            bgfx::setViewTransform(BOX1_VID, NULL, proj);
            bgfx::setViewRect(BOX1_VID, 0, 0, uint16_t(mBaseWidth), uint16_t(mBaseHeight));

            if (4 == bgfx::getAvailTransientVertexBuffer(4, PosRGBVertex::ms_decl))
            {
                bgfx::TransientVertexBuffer vb;
                bgfx::allocTransientVertexBuffer(&vb, 4, PosRGBVertex::ms_decl);
                auto pBox1Data = (PosRGBVertex*)vb.data;
                //                             <pos>         <rgb>      
                *pBox1Data++ = PosRGBVertex(-100,  100, 1.0f, 0.0f, 0.0f);
                *pBox1Data++ = PosRGBVertex(-100, -100, 1.0f, 0.0f, 0.0f);
                *pBox1Data++ = PosRGBVertex( 100,  100, 1.0f, 0.0f, 0.0f);
                *pBox1Data++ = PosRGBVertex( 100, -100, 1.0f, 0.0f, 0.0f);
                bgfx::setVertexBuffer(0, &vb);
            }

            bgfx::setState(0
                | BGFX_STATE_RGB_WRITE
                | BGFX_STATE_ALPHA_WRITE
                | BGFX_STATE_PT_TRISTRIP
            );
            bgfx::submit(BOX1_VID, m_box1Program);
        }

        if (!inputGetKeyState(entry::Key::Space))
        {
            // Draw a GREEN scaled box (200x200) in the middle of the texture attached to the FBO
            {
                float proj[16];
                bgfx::setViewFrameBuffer(BOX2_VID, m_FBO);
                bx::mtxOrtho(proj, float(-mBaseWidth / 2), float(mBaseWidth / 2), float(-mBaseHeight / 2), float(mBaseHeight / 2), -1.0f, 100.0f, 0.0f, caps->homogeneousDepth);
                bgfx::setViewTransform(BOX2_VID, NULL, proj);
                bgfx::setViewRect(BOX2_VID, 0, 0, uint16_t(mBaseWidth), uint16_t(mBaseHeight));

                if (4 == bgfx::getAvailTransientVertexBuffer(4, PosRGBScaleVertex::ms_decl))
                {
                    bgfx::TransientVertexBuffer vb;
                    bgfx::allocTransientVertexBuffer(&vb, 4, PosRGBScaleVertex::ms_decl);
                    auto pBox2Data = (PosRGBScaleVertex*)vb.data;

                    static float s = 0.0f;
                    s += 0.01f;
                    if (s > 2.0f) s = 0.0f;     // Reset scale once reach x2

                    //                                 <pos>         <rgb>      <scale>
                    *pBox2Data++ = PosRGBScaleVertex(-100,  100, 0.0f, 1.0f, 0.0f, s);
                    *pBox2Data++ = PosRGBScaleVertex(-100, -100, 0.0f, 1.0f, 0.0f, s);
                    *pBox2Data++ = PosRGBScaleVertex( 100,  100, 0.0f, 1.0f, 0.0f, s);
                    *pBox2Data++ = PosRGBScaleVertex( 100, -100, 0.0f, 1.0f, 0.0f, s);
                    bgfx::setVertexBuffer(0, &vb);
                }

                bgfx::setState(0
                    | BGFX_STATE_RGB_WRITE
                    | BGFX_STATE_ALPHA_WRITE
                    | BGFX_STATE_PT_TRISTRIP
                );
                bgfx::submit(BOX2_VID, m_box2Program);
            }
        }
        //
        // Render final texure from FBO to screen
        //
        {
            float proj[16];
            bx::mtxOrtho(proj, -float(m_width/2), float(m_width/2), -float(m_height/2), float(m_height/2), -1.0f, 100.0f, 0.0f, caps->homogeneousDepth);
            bgfx::setViewTransform(SCREEN_VID, NULL, proj);
            bgfx::setViewRect(SCREEN_VID, 0, 0, uint16_t(m_width), uint16_t(m_height) );
            if (4 == bgfx::getAvailTransientVertexBuffer(4, PosUvVertex::ms_decl))
            {
                bgfx::TransientVertexBuffer vb;
                bgfx::allocTransientVertexBuffer(&vb, 4, PosUvVertex::ms_decl);

                const float hw = mBaseWidth / 2.0f;
                const float hh = mBaseHeight / 2.0f;
                float quadUV[4 * (2+2)] = {
                    -hw,  hh ,  0.0f,  1.0f  ,
                    -hw, -hh ,  0.0f,  0.0f  ,
                    hw,  hh ,  1.0f,   1.0f  ,
                    hw, -hh ,  1.0f,   0.0f };
                memcpy(vb.data, quadUV, sizeof(quadUV));
                bgfx::setVertexBuffer(0, &vb);
            }

            bgfx::setTexture(0, m_texUniform,  bgfx::getTexture(m_FBO));
            bgfx::setState(0
                    | BGFX_STATE_RGB_WRITE
                    | BGFX_STATE_ALPHA_WRITE
                    | BGFX_STATE_PT_TRISTRIP
                    );
            bgfx::submit(SCREEN_VID, m_textureProgram);
        }
    }
};

ENTRY_IMPLEMENT_MAIN(ExampleCubes);
