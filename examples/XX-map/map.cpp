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
	float m_z;
	float m_u;
	float m_v;

	static void init(){
	ms_decl
		.begin()
		.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
		.end();
    }
	static bgfx::VertexDecl ms_decl;
};
bgfx::VertexDecl PosUvVertex::ms_decl;


// Sprite Vertex; 4 of these are added for each sprite
struct SpriteVertex
{
    float m_x;     // sprite world x,y
    float m_y;
    float m_ox;    // corner offset from world X,Y
    float m_oy;
    float m_u;     // sprite sheet texture u,v
    float m_v;
    float m_a;     // radians of rotation angle

    SpriteVertex(float x, float y, float ox, float oy, float u, float v, float a) :
        m_x(x), m_y(y), m_ox(ox), m_oy(oy), m_u(u), m_v(v), m_a(a) { }

    static void init(){
    ms_decl
        .begin()
        .add(bgfx::Attrib::Position,  4, bgfx::AttribType::Float)
        .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Normal, 1, bgfx::AttribType::Float)
        .end();
    }
    static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl SpriteVertex::ms_decl;


class ExampleCubes : public entry::AppI
{
	void init(int _argc, char** _argv) BX_OVERRIDE
	{
		Args args(_argc, _argv);

		m_width  = mBaseWidth/2;
		m_height = mBaseHeight/2;
		m_debug  = BGFX_DEBUG_TEXT;
		m_reset  = BGFX_RESET_VSYNC;

        m_adjustCorners = (bgfx::getRendererType() == bgfx::RendererType::Direct3D9);

        // HARD CODE TO OPENGL
		bgfx::init(bgfx::RendererType::OpenGL, args.m_pciId);
		bgfx::reset(m_width, m_height, m_reset);

		bgfx::setDebug(m_debug);

        // Create an index buffer which defines which SpriteVertex's
        // are used to make the 2 triangles for each sprite
        const int MAX_SPRITES = 10;
		PosUvVertex::init();
		SpriteVertex::init();
        static uint16_t sIndices[MAX_SPRITES * 6];
        for (uint16_t i=0; i < MAX_SPRITES; ++i)
        {
            // * 6 because each sprite has 2 triangles => 6 indices
            // * 4 because each sprite is made up of 4 SpriteVertex's
            // - Corner 0,1,2 (BottomLeft, TopLeft, TopRight) for tri1
            sIndices[i*6 +0] = i*4 +0;
            sIndices[i*6 +1] = i*4 +1;
            sIndices[i*6 +2] = i*4 +2;
            // - Corner 2,1,3 (TopRight, BottomLeft, BottomRight) for tri2
            sIndices[i*6 +3] = i*4 +2;
            sIndices[i*6 +4] = i*4 +1;
            sIndices[i*6 +5] = i*4 +3;
        }
        m_spriteIBH = bgfx::createIndexBuffer(
                bgfx::makeRef(sIndices, MAX_SPRITES*6*sizeof(uint16_t))
                );

		m_spriteProgram = loadProgram("sprite_vs", "sprite_fs");
		m_textureProgram = loadProgram("texture_vs", "texture_fs");

        m_texUniform = bgfx::createUniform("s_texColor", bgfx::UniformType::Int1);

        const uint32_t nearestRTT = 0
            | BGFX_TEXTURE_RT
            | BGFX_TEXTURE_MIN_POINT
            | BGFX_TEXTURE_MAG_POINT
            | BGFX_TEXTURE_MIP_POINT
            ;
        // Create the large map texture that we render part of
        m_mapTexture = loadTexture("textures/map.png", nearestRTT);
        // Create the sprite sheet texture that we render sprites from
        m_spriteSheetTexture = loadTexture("textures/sprite-sheet.png", nearestRTT);
        // Create the off-screen texture that the map and sprites are rendered too
        m_offscreenTexture = bgfx::createTexture2D(mBaseWidth, mBaseHeight, false, 1, bgfx::TextureFormat::RGBA8, nearestRTT, nullptr);

        // Create the FBO to render to the off-screen texture
        m_FBO = bgfx::createFrameBuffer(1, &m_offscreenTexture);
	}

	virtual int shutdown() BX_OVERRIDE
	{
		// Cleanup.
		bgfx::destroyIndexBuffer(m_spriteIBH);
		bgfx::destroyProgram(m_spriteProgram);
		bgfx::destroyProgram(m_textureProgram);
        bgfx::destroyFrameBuffer(m_FBO);
        bgfx::destroyUniform(m_texUniform);
        bgfx::destroyTexture(m_mapTexture);
        bgfx::destroyTexture(m_spriteSheetTexture);
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

    // View IDs for rendering the Map, Sprites and final screen image
    enum { MAP_VID=10, SPRITE_VID=11, SCREEN_VID=12 };

    const uint16_t mBaseWidth = 1024;
    const uint16_t mBaseHeight = 1024;
    const int SPRITE_WIDTH = 64;
    const int SPRITE_HEIGHT = 64;
    const int SPRITE_SHEET_WIDTH = 1024;
    const int SPRITE_SHEET_HEIGHT = 768;
    const int MAP_TEXTURE_WIDTH = 2048;
    const int MAP_TEXTURE_HEIGHT = 2048;
    const int MAP_TEXTURE_X = 0;
    const int MAP_TEXTURE_Y = 0;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;
	bool m_adjustCorners;
	bgfx::IndexBufferHandle m_spriteIBH;
	bgfx::ProgramHandle m_spriteProgram;
	bgfx::ProgramHandle m_textureProgram;
    bgfx::TextureHandle m_mapTexture;
    bgfx::TextureHandle m_spriteSheetTexture;
    bgfx::TextureHandle m_offscreenTexture;
    bgfx::UniformHandle m_texUniform;
    bgfx::FrameBufferHandle m_FBO;

    void render()
    {
        const bgfx::Caps* caps = bgfx::getCaps();
        // Render map to the texture attached to the FBO
        {
            float proj[16];
            bgfx::setViewFrameBuffer(MAP_VID, m_FBO);
            bx::mtxOrtho(proj, float(-mBaseWidth/2), float(mBaseWidth/2), float(-mBaseHeight/2), float(mBaseHeight/2), -1.0f, 100.0f, 0.0f, caps->homogeneousDepth);
            bgfx::setViewTransform(MAP_VID, NULL, proj);
            bgfx::setViewRect(MAP_VID, 0, 0, uint16_t(mBaseWidth), uint16_t(mBaseHeight) );
            mapTextureQuad(mBaseWidth, mBaseHeight);

            bgfx::setTexture(0, m_texUniform, m_mapTexture);
            bgfx::setState(0
                    | BGFX_STATE_RGB_WRITE
                    | BGFX_STATE_ALPHA_WRITE
                    | BGFX_STATE_PT_TRISTRIP
                    );
            bgfx::submit(MAP_VID, m_textureProgram);
        }

        // Render Sprite(s) to the texture attached to the FBO
        if (inputGetKeyState(entry::Key::Space))
        {
            bgfx::TransientVertexBuffer vb;
            int worldCenterX = 2000;
            int worldCenterY = 3000;
            // Just hard-code 3 fake sprites
            unsigned int numSprites = 3;
            if (4*numSprites == bgfx::getAvailTransientVertexBuffer(4*numSprites, SpriteVertex::ms_decl) )
            {
                bgfx::allocTransientVertexBuffer(&vb, 4*numSprites, SpriteVertex::ms_decl);
                auto pSpriteData = (SpriteVertex*) vb.data;
                static float dy = 0;
                for (unsigned int i=0; i < numSprites; ++i)
                {
                    const float widthRatio = float(SPRITE_WIDTH) / float(SPRITE_SHEET_WIDTH);
                    const float heightRatio = float(SPRITE_HEIGHT) / float(SPRITE_SHEET_HEIGHT);
                    const float halfWidth = SPRITE_WIDTH * 0.5f;
                    const float halfHeight = SPRITE_HEIGHT * 0.5f;

                    // Hardcode sprite to screen coord 300,100 plus an offset (0,0 = center)
                    const float sx = float(worldCenterX + 300 +i*20);
                    const float sy = float(worldCenterY + 100 +i*20+dy);
                    const float tx = 0;
                    const float ty = 0;
                    const float cx = tx + widthRatio;
                    const float cy = ty + heightRatio;
                    const float a = 0;
                    const float s = 1;
                    *pSpriteData++ = SpriteVertex(sx,sy, -halfWidth*s,  halfHeight*s, tx, cy, a );
                    *pSpriteData++ = SpriteVertex(sx,sy, -halfWidth*s, -halfHeight*s, tx, ty, a );
                    *pSpriteData++ = SpriteVertex(sx,sy,  halfWidth*s,  halfHeight*s, cx, cy, a );
                    *pSpriteData++ = SpriteVertex(sx,sy,  halfWidth*s, -halfHeight*s, cx, ty, a );
                }
                // hack to make sprites move
                dy += 1.0f;
                if (dy > 50.0f) dy = 0;
            }
            else
            {
                std::cout << "FAILED TO ALLOCATE VB\n";
                exit(1);
            }

            // Use the sprite shader, index buffer and vertex buffer to render sprites to the FBO
            float proj[16];
            bgfx::setViewFrameBuffer(SPRITE_VID, m_FBO);
            // - Sprites are translated by worldCenterX/Y in shader
            bx::mtxOrtho(proj, float(worldCenterX-mBaseWidth/2), float(worldCenterX+mBaseWidth/2),
                               float(worldCenterY-mBaseHeight/2), float(worldCenterY+mBaseHeight/2),
                               -1.0f, 100.0f, 0.0f, caps->homogeneousDepth);
            bgfx::setViewTransform(SPRITE_VID, NULL, proj);
            bgfx::setViewRect(SPRITE_VID, 0, 0, uint16_t(mBaseWidth), uint16_t(mBaseHeight) );
            bgfx::setVertexBuffer(0, &vb);
            bgfx::setIndexBuffer( m_spriteIBH, 0, numSprites*6);
            bgfx::setTexture(0, m_texUniform,  m_spriteSheetTexture);
            bgfx::setState(0
                    | BGFX_STATE_RGB_WRITE
                    | BGFX_STATE_ALPHA_WRITE
                    | BGFX_STATE_BLEND_NORMAL
                    );
            bgfx::submit(SPRITE_VID, m_spriteProgram);
        }
        //
        // Render final texure from FBO to screen
        //
        {
            float proj[16];
            bx::mtxOrtho(proj, -float(m_width/2), float(m_width/2), -float(m_height/2), float(m_height/2), -1.0f, 100.0f, 0.0f, caps->homogeneousDepth);
            bgfx::setViewTransform(SCREEN_VID, NULL, proj);
            bgfx::setViewRect(SCREEN_VID, 0, 0, uint16_t(m_width), uint16_t(m_height) );
            screenTextureQuad(m_width, m_height);

            bgfx::setTexture(0, m_texUniform,  bgfx::getTexture(m_FBO));
            bgfx::setState(0
                    | BGFX_STATE_RGB_WRITE
                    | BGFX_STATE_ALPHA_WRITE
                    | BGFX_STATE_PT_TRISTRIP
                    );
            bgfx::submit(SCREEN_VID, m_textureProgram);
        }
    }

    // Create a centered tri-strip quad (WxH) textured with the entire texture
    void screenTextureQuad(int w, int h)
    {
        if (4 == bgfx::getAvailTransientVertexBuffer(4, PosUvVertex::ms_decl) )
        {
            bgfx::TransientVertexBuffer vb;
            bgfx::allocTransientVertexBuffer(&vb, 4, PosUvVertex::ms_decl);

            const float htx = (m_adjustCorners ? 0.5f/w : 0.0f);
            const float hty = (m_adjustCorners ? 0.5f/h : 0.0f);
            const float hw = w/2.0f;
            const float hh = h/2.0f;
            float quad[4*(3*2)] = {
                -hw,  hh, 0 ,  htx,   1-hty  ,
                -hw, -hh, 0 ,  htx,   hty    ,
                 hw,  hh, 0 ,  1-htx, 1-hty  ,
                 hw, -hh, 0 ,  1-htx, hty     };
            memcpy(vb.data, quad, sizeof(quad));
            bgfx::setVertexBuffer(0, &vb);
        }
    }

    // Create a centered tri-stip quad (width x height) to display a portion of the
    // map texture.
    void mapTextureQuad(int width, int height)
    {
        if (4 == bgfx::getAvailTransientVertexBuffer(4, PosUvVertex::ms_decl) )
        {
            bgfx::TransientVertexBuffer vb;
            bgfx::allocTransientVertexBuffer(&vb, 4, PosUvVertex::ms_decl);

            const float tw = float(MAP_TEXTURE_WIDTH);                     // Texture width
            const float th = float(MAP_TEXTURE_HEIGHT);                    // Texture height
            const float ax = (m_adjustCorners ? 0.5f/tw : 0.0f);
            const float ay = (m_adjustCorners ? 0.5f/th : 0.0f);
            const float tx = MAP_TEXTURE_X + (((tw-width)/2)/tw);   // Texture coord (bottom left)
            const float ty = MAP_TEXTURE_Y + (((th-height)/2)/th);  // Texture coord (bottom left)
            const float cx = tx+width/tw;                           // Texture coord (corner)
            const float cy = ty+height/th;                          // Texture coord (corner)
            const float hw = float(width/2);
            const float hh = float(height/2);
            float quad[4*(3+2)] = {
                -hw,  hh, 0 ,  tx+ax,  cy-ay,
                -hw, -hh, 0 ,  tx+ax,  ty+ay,
                 hw,  hh, 0 ,  cx-ax,  cy-ay,
                 hw, -hh, 0 ,  cx-ax,  ty+ay
            };
            memcpy(vb.data, &quad[0], sizeof(quad));

            bgfx::setVertexBuffer(0, &vb);
        }
    }
};

ENTRY_IMPLEMENT_MAIN(ExampleCubes);
