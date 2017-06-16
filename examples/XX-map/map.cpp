/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */
#include <iostream>
#include <fstream>
#include <cstring>

#include "common.h"
#include "bgfx_utils.h"
#include "string.h"
#include "entry/input.h"

    enum {
        TGA_BGRA=2,
        TGA_GREY=3,
        TGA_BGRA_RLE=10,
        TGA_GRAY_RLE=11
    };
    typedef struct {
        unsigned char m_idLen;
        unsigned char m_colorMapType;
        unsigned char m_imageType;
        unsigned char m_colorMapIndexLSB, m_colorMapIndexMSB;
        unsigned char m_colorMapLengthLSB, m_colorMapLengthMSB;
        unsigned char m_colorMapSize;
        unsigned char m_xOriginLSB, m_xOriginMSB;
        unsigned char m_yOriginLSB, m_yOriginMSB;
        unsigned char m_widthLSB, m_widthMSB;
        unsigned char m_heightLSB, m_heightMSB;
        unsigned char m_pixelDepth;
        unsigned char m_attrBits;
    } TGAHeader;


static unsigned char* swapPixelData(const unsigned char* pPixelData,
                           const unsigned int width,
                           const unsigned int height,
                           const unsigned int pixelDepth)
{
    // Copy the data swapping RGB(A) to BGR(A)
    // (or vice versa) if needed
    const unsigned int l_bytesPerPixel = pixelDepth/8;
    const unsigned long l_imageSize = width * height * l_bytesPerPixel;
    unsigned char* l_pNewPixels = new unsigned char[ l_imageSize ];
    unsigned char* l_pCurPixel = l_pNewPixels;

    for (unsigned int i=0; i < width * height; ++i)
    {
        static unsigned int l_copyOffsets[4][4] = {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }, // 16 bit pixel depth not supported
            { 2, 1, 0, 3 },
            { 2, 1, 0, 3 }
        };
        for (unsigned int j=0; j < l_bytesPerPixel; ++j)
        {
            unsigned int l_offset = l_copyOffsets[l_bytesPerPixel-1][j];
            *l_pCurPixel++ = pPixelData[i*l_bytesPerPixel + l_offset];
        }
    }
    return l_pNewPixels;
}

static bool saveTGA(const char* pFilename,
             const unsigned int width,
             const unsigned int height,
             const unsigned int pixelDepth,
             const unsigned char* pPixelData)
{
    std::ofstream l_ofs(pFilename, std::ofstream::binary);
    if (! pFilename || ! l_ofs)
    {
        return false;
    }

    unsigned char l_imageType;
    switch (pixelDepth)
    {
    case 8:  l_imageType = TGA_GREY; break;
    case 24:
    case 32: l_imageType = TGA_BGRA; break;
    default: return false;
    }
    unsigned char* l_pNewPixels;
    l_pNewPixels = swapPixelData(pPixelData, width, height, pixelDepth);

    // Create the Header
    // -Macro to put a word in LSB,MSB format
#define LSB_MSB(val) static_cast<unsigned char>((val)&0xff), static_cast<unsigned char>(((val)&0xff00)>>8)
    TGAHeader l_tgaHdr = {
        0,                   // ID Len
        0,                   // No Color Map
        l_imageType,
        LSB_MSB(0),          // Color map index
        LSB_MSB(0),          // Color map len
        0,                   // Color map size
        LSB_MSB(0),          // X origin
        LSB_MSB(0),          // Y origin
        LSB_MSB(width),
        LSB_MSB(height),
        static_cast<unsigned char>(pixelDepth),
        8                    // Attr bit (Alpha?)
    };

    l_ofs.put(l_tgaHdr.m_idLen);
    l_ofs.put(l_tgaHdr.m_colorMapType);
    l_ofs.put(l_tgaHdr.m_imageType);
    l_ofs.put(l_tgaHdr.m_colorMapIndexLSB);
    l_ofs.put(l_tgaHdr.m_colorMapIndexMSB);
    l_ofs.put(l_tgaHdr.m_colorMapLengthLSB);
    l_ofs.put(l_tgaHdr.m_colorMapLengthMSB);
    l_ofs.put(l_tgaHdr.m_colorMapSize);
    l_ofs.put(l_tgaHdr.m_xOriginLSB);
    l_ofs.put(l_tgaHdr.m_xOriginMSB);
    l_ofs.put(l_tgaHdr.m_yOriginLSB);
    l_ofs.put(l_tgaHdr.m_yOriginMSB);
    l_ofs.put(l_tgaHdr.m_widthLSB);
    l_ofs.put(l_tgaHdr.m_widthMSB);
    l_ofs.put(l_tgaHdr.m_heightLSB);
    l_ofs.put(l_tgaHdr.m_heightMSB);
    l_ofs.put(l_tgaHdr.m_pixelDepth);
    l_ofs.put(l_tgaHdr.m_attrBits);

    // Write the pixels
    l_ofs.write(reinterpret_cast<char*>(l_pNewPixels), (width * height * (pixelDepth/8)));
    delete[] l_pNewPixels;

    l_ofs.close();
    return (! l_ofs) ? false : true;
}


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

		bgfx::init(args.m_type, args.m_pciId);
		bgfx::reset(m_width, m_height, m_reset);

		bgfx::setDebug(m_debug);

        // Create an index buffer which defines which SpriteVertex's
        // are used to make the 2 triangles for each sprite
#define MAX_SPRITES 1000
		PosUvVertex::init();
		SpriteVertex::init();
        static uint16_t sIndices[MAX_SPRITES * 6];
        for (int i=0; i < MAX_SPRITES; ++i)
        {
            // * 6 because each sprite has 2 triangles => 6 indices
            // * 4 because each sprite is made up of 4 SpriteVertex's
            sIndices[i*6 +0] = i*4 +0;
            sIndices[i*6 +1] = i*4 +1;
            sIndices[i*6 +2] = i*4 +2;

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

    enum { MAP_VID=0, SPRITE_VID=1, SCREEN_VID=2 };

    const int mBaseWidth = 1024;
    const int mBaseHeight = 1024;
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
            bx::mtxOrtho(proj, -mBaseWidth/2, mBaseWidth/2, -mBaseHeight/2, mBaseHeight/2, -1.0f, 100.0f, 0.0f, caps->homogeneousDepth);
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
        // Press 'M' to save offcreen texture with MAP
        {
            static bool pressed = false;
            if (!pressed && inputGetKeyState(entry::Key::KeyM))
            {
                pressed = true;
                unsigned char* pData = new unsigned char[mBaseWidth * mBaseHeight * 4 ];
                unsigned int frame = bgfx::readTexture(m_offscreenTexture, pData);
                while (bgfx::frame() < frame)
                {
                }
                saveTGA("MAP.tga", mBaseWidth, mBaseHeight, 32, pData);
                delete[] pData;
            }
            else
            if (pressed && !inputGetKeyState(entry::Key::KeyM))
            {
                pressed = false;
            }
        }

        // Render Sprite(s) to the texture attached to the FBO
        {

            // Just hard code a single sprite (4 SpriteVertex's) into the transient VB
            bgfx::TransientVertexBuffer vb;
            int worldCenterX = 2000;
            int worldCenterY = 3000;
            unsigned int numSprites = 1;
            if (4*numSprites == bgfx::getAvailTransientVertexBuffer(4*numSprites, SpriteVertex::ms_decl) )
            {
                bgfx::allocTransientVertexBuffer(&vb, 4*numSprites, SpriteVertex::ms_decl);
                auto pSpriteData = (SpriteVertex*) vb.data;
                for (unsigned int i=0; i < numSprites; ++i)
                {
                    const float widthRatio = float(SPRITE_WIDTH) / float(SPRITE_SHEET_WIDTH);
                    const float heightRatio = float(SPRITE_HEIGHT) / float(SPRITE_SHEET_HEIGHT);
                    const float halfWidth = SPRITE_WIDTH * 0.5f;
                    const float halfHeight = SPRITE_HEIGHT * 0.5f;

                    // Hardcode sprite to screen coord 300,100 (0,0 = center)
                    const float sx = worldCenterX + 300;
                    const float sy = worldCenterY + 100;
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
            }

            float proj[16];
            bgfx::setViewFrameBuffer(SPRITE_VID, m_FBO);
            // Sprites are translated by worldCenterX/Y
            bx::mtxOrtho(proj, worldCenterX-mBaseWidth/2, worldCenterX+mBaseWidth/2,
                               worldCenterY-mBaseHeight/2, worldCenterY+mBaseHeight/2,
                               -1.0f, 100.0f, 0.0f, caps->homogeneousDepth);
            bgfx::setViewTransform(SPRITE_VID, NULL, proj);
            bgfx::setViewRect(SPRITE_VID, 0, 0, uint16_t(mBaseWidth), uint16_t(mBaseHeight) );
            bgfx::setVertexBuffer(0, &vb);
            bgfx::setIndexBuffer( m_spriteIBH );
            bgfx::setTexture(0, m_texUniform,  m_spriteSheetTexture);
            bgfx::setState(0
                    | BGFX_STATE_RGB_WRITE
                    | BGFX_STATE_ALPHA_WRITE
                    | BGFX_STATE_BLEND_NORMAL
                    );
            bgfx::submit(SPRITE_VID, m_spriteProgram);
        }
        // Press 'S' to save offcreen texture with MAP+SPRITES
        {
            static bool pressed = false;
            if (!pressed && inputGetKeyState(entry::Key::KeyS))
            {
                pressed = true;
                unsigned char* pData = new unsigned char[mBaseWidth * mBaseHeight * 4 ];
                unsigned int frame = bgfx::readTexture(m_offscreenTexture, pData);
                while (bgfx::frame() < frame)
                {
                }
                saveTGA("MAP_and_SPR.tga", mBaseWidth, mBaseHeight, 32, pData);
                delete[] pData;
            }
            else
            if (pressed && !inputGetKeyState(entry::Key::KeyS))
            {
                pressed = false;
            }
        }
        //
        // Render final texure from FBO to screen
        //
        {
            float proj[16];
            bx::mtxOrtho(proj, -m_width/2, m_width/2, -m_height/2, m_height/2, -1.0f, 100.0f, 0.0f, caps->homogeneousDepth);
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
    // 2048x2048 map texture.
    void mapTextureQuad(int width, int height)
    {
        if (4 == bgfx::getAvailTransientVertexBuffer(4, PosUvVertex::ms_decl) )
        {
            bgfx::TransientVertexBuffer vb;
            bgfx::allocTransientVertexBuffer(&vb, 4, PosUvVertex::ms_decl);

            const float tw = MAP_TEXTURE_WIDTH;                     // Texture width
            const float th = MAP_TEXTURE_HEIGHT;                    // Texture height
            const float ax = (m_adjustCorners ? 0.5f/tw : 0.0f);
            const float ay = (m_adjustCorners ? 0.5f/th : 0.0f);
            const float tx = MAP_TEXTURE_X + (((tw-width)/2)/tw);   // Texture coord (bottom left)
            const float ty = MAP_TEXTURE_Y + (((th-height)/2)/th);  // Texture coord (bottom left)
            const float cx = tx+width/tw;                           // Texture coord (corner)
            const float cy = ty+height/th;                          // Texture coord (corner)
            const float hw = width/2;
            const float hh = height/2;
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
