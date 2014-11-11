
// based on code from  Brian Luczkiewicz
// https://github.com/blucz/Vector

#include "vectordisplay.h"

#include "bgfx_utils.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>
#include <malloc.h>
#include <assert.h>

#include <bx/fpumath.h>

//Config stuff
const int cMaxNumberVertices = 20000;

const int cMaxDecaySteps         = 60;
const int cDefaultDecaySteps     = 5;
const float cDefaultDecayValue         = 0.8f;
const float cDefaultInitialDecay = 0.04f;
const float cDefaultDrawOffsetX      = 0.0f;
const float cDefaultDrawOffsetY      = 0.0f;
const float cDefaultDrawScale         = 1.0f;
const float cDefaultBrightness    = 1.0f;   

//internal config
const int cTextureSize = 64;
const int cHalfTextureSize = cTextureSize / 2;

#define min(x,y) ((x) < (y) ? (x) : (y))
#define max(x,y) ((x) > (y) ? (x) : (y))

struct PosColorUvVertex {
    float m_x;
    float m_y;
    float m_z;
    float m_u;
    float m_v;
    uint32_t m_abgr;
    static void init() {
        ms_decl
            .begin()
            .add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Color0,    4, bgfx::AttribType::Uint8, true)
            .end();
    }
    static bgfx::VertexDecl ms_decl;
};
bgfx::VertexDecl PosColorUvVertex::ms_decl;

void VectorDisplay::setup(float inp_width, float inp_height, int view) {
    PosColorUvVertex::init();

    mDecayValue = cDefaultDecayValue;
    setDrawColor(1.0f, 1.0f, 1.0f, 1.0f);

    mScreenWidth    = inp_width;
    mScreenHeight   = inp_height;
    mGlowWidth      = mScreenWidth  / 3.0;
    mGlowHeight     = mScreenHeight / 3.0;
    mInitialDecay   = cDefaultInitialDecay;

    mDrawOffsetX    = cDefaultDrawOffsetX;
    mDrawOffsetY    = cDefaultDrawOffsetY;
    mDrawScale      = cDefaultDrawScale;
    mBrightness     = cDefaultBrightness;

    setDefaultThickness();

    setDecaySteps(cDefaultDecaySteps);

    mView = view;

    mDrawToScreenShader = loadProgram("vs_fb", "fs_fb");
    fb_uniform_alpha = bgfx::createUniform("u_alpha", bgfx::UniformType::Uniform1f);

    mBlurShader = loadProgram("vs_fb", "fs_blur");
    blur_uniform_scale = bgfx::createUniform("u_scale", bgfx::UniformType::Uniform2fv);
    blur_uniform_alpha = bgfx::createUniform("u_alpha", bgfx::UniformType::Uniform1f);
    blur_uniform_mult = bgfx::createUniform("u_mult", bgfx::UniformType::Uniform1f);

    mBlitShader = loadProgram("vs_fb", "fs_blit");

    //generate uniforms for sampler
    u_tex1 = bgfx::createUniform("u_tex1", bgfx::UniformType::Uniform1iv);

    genLinetex();

    bgfx::setViewClear(view, BGFX_CLEAR_COLOR_BIT|BGFX_CLEAR_DEPTH_BIT, 0x000000ff, 1.0f, 0);

    setupResDependent();
}

void VectorDisplay::resize(float width, float height) {
    teardownResDependent();
    mScreenWidth = width;
    mScreenHeight = height;
    mGlowWidth = width   / 3.0;
    mGlowHeight = height / 3.0;
    setupResDependent();
}

void VectorDisplay::teardown() {
    teardownResDependent();

    bgfx::destroyProgram(mDrawToScreenShader);
    bgfx::destroyUniform(fb_uniform_alpha);
    bgfx::destroyTexture(mLineTexId);
    bgfx::destroyUniform(u_linetexid);

    bgfx::destroyProgram(mBlurShader);
    bgfx::destroyUniform(blur_uniform_scale);
    bgfx::destroyUniform(blur_uniform_alpha);
    bgfx::destroyUniform(blur_uniform_mult);

    bgfx::destroyUniform(u_tex1);

    bgfx::destroyProgram(mBlitShader);
}

void VectorDisplay::beginFrame() {
    mPoints.clear();
}

void VectorDisplay::endFrame() {
    float proj[16];
    float ident[16];
    bx::mtxIdentity(ident);

    bx::mtxOrtho(proj, 0.0f, (float)mScreenWidth, (float)mScreenHeight, 0.0f, 0.0f, 1000.0f);

    bgfx::setViewRect(mView, 0, 0, mScreenWidth, mScreenHeight);
    bgfx::setViewFrameBuffer(mView, mSceneFrameBuffer);              //render all geometry to this framebuffer
    bgfx::setViewTransform(mView, NULL, proj);

    // advance step
    mCurrentDrawStep = (mCurrentDrawStep + 1) % mNumberDecaySteps;

    assert(mPoints.size() < cMaxNumberVertices);

    bgfx::updateDynamicVertexBuffer(mVertexBuffers[mCurrentDrawStep], bgfx::copy(mPoints.data(), mPoints.size()*sizeof(point_t)));
    mVertexBuffersSize[mCurrentDrawStep] = mPoints.size();

    //if the index buffer is cleared from the last "submit"-call everything is fine, but if not
    //we clear it here again just to be sure it's not set... (the same for the Transform)
    bgfx::IndexBufferHandle ib;
    ib.idx = bgfx::invalidHandle;
    bgfx::setIndexBuffer(ib);

    bgfx::setTransform(ident);

    for(int loopvar = 0; loopvar < mNumberDecaySteps; loopvar++) {
        int stepi = mNumberDecaySteps - loopvar - 1;
        int i = (mCurrentDrawStep + mNumberDecaySteps - stepi) % mNumberDecaySteps;

        if (mVertexBuffersSize[i] != 0) {                //only draw if something is in the buffer
            float alpha;
            if (stepi == 0) {
                alpha = 1.0f;
            } else if (stepi == 1) {
                alpha = mInitialDecay;
            } else {
                alpha = pow(mDecayValue, stepi-1) * mInitialDecay;
            }
            bgfx::setUniform(fb_uniform_alpha, &alpha);

            bgfx::setTexture(0, u_linetexid, mLineTexId);
            bgfx::setProgram(mDrawToScreenShader);

            bgfx::setVertexBuffer(mVertexBuffers[i], mVertexBuffersSize[i]);  //expicitly feed vertex number!

            bgfx::setState( BGFX_STATE_RGB_WRITE 
                          | BGFX_STATE_ALPHA_WRITE 
                          | BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_DST_ALPHA)
                          | BGFX_STATE_BLEND_EQUATION_SEPARATE(0x0, BGFX_STATE_BLEND_EQUATION_MAX)                  //0x0 means ADD!
                          );

            bgfx::setViewName(mView, "RenderVectorDisplay");
            bgfx::submit(mView);
        }
    }

    int viewCounter = mView+1;

    float glow_iter_mult = 1.05 + ((mBrightness - 1.0) / 5.0);
    float glow_fin_mult  = 1.25 + ((mBrightness - 1.0) / 2.0);

    bx::mtxOrtho(proj, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 100.0f);

    if(mBrightness > 0) {
        float alpha = 1.0f;
        bgfx::setUniform(blur_uniform_alpha, &alpha);
        bgfx::setUniform(blur_uniform_mult, &glow_iter_mult);

        bgfx::setTexture(0, u_tex1, mSceneFrameBuffer);

        int npasses = (int)(mBrightness*4);
        for (int pass = 0; pass < npasses; pass++) {
            // render the glow1 texture to the glow0 buffer with horizontal blur

            bgfx::setViewFrameBuffer(viewCounter, mGlow0FrameBuffer);            //first glow pass
            bgfx::setViewRect(viewCounter, 0, 0, mGlowWidth, mGlowHeight);
            bgfx::setState( BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
            float scale[2];
            scale[0] = 1.0f/mGlowWidth;
            scale[1] = 0.0f;
            bgfx::setUniform(blur_uniform_scale, &scale);
            bgfx::setProgram(mBlurShader);

            bgfx::setViewTransform(viewCounter, NULL, proj);
            screenSpaceQuad(mGlowWidth, mGlowHeight);
            bgfx::setViewName(viewCounter, "BlendPassA");
            bgfx::submit(viewCounter);

            viewCounter++;

            bgfx::setViewFrameBuffer(viewCounter, mGlow1FrameBuffer);            //second glow pass
            bgfx::setViewRect(viewCounter, 0, 0, mGlowWidth, mGlowHeight);
            bgfx::setTexture(0, u_tex1, mGlow0FrameBuffer);
            bgfx::setProgram(mBlurShader);

            bgfx::setViewTransform(viewCounter, NULL, proj);
            screenSpaceQuad(mGlowWidth, mGlowHeight);

            bgfx::setUniform(blur_uniform_alpha, &alpha);
            bgfx::setUniform(blur_uniform_mult, &glow_iter_mult);
            scale[0] = 0.0f;
            scale[1] = 1.0f/mGlowHeight;
            bgfx::setUniform(blur_uniform_scale, &scale);

            bgfx::setState( BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);

            bgfx::setViewName(viewCounter, "BlendPassB");
            bgfx::submit(viewCounter);

            viewCounter++;

            //set for next iteration
            bgfx::setTexture(0, u_tex1, mGlow1FrameBuffer);
        }
    }

    //now do last pass, combination of blur and normal buffer to screen
    bgfx::setViewTransform(viewCounter, NULL, proj);
    bgfx::setViewRect(viewCounter, 0, 0, mScreenWidth, mScreenHeight);
    bgfx::setTexture(0, u_tex1, mSceneFrameBuffer);
    bgfx::setProgram(mBlitShader);
    bgfx::setState( BGFX_STATE_RGB_WRITE 
                  | BGFX_STATE_ALPHA_WRITE 
                  | BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE, BGFX_STATE_BLEND_ONE)
                  );

    float tempOne = 1.0f;    
    bgfx::setUniform(blur_uniform_alpha, &tempOne);
    bgfx::setUniform(blur_uniform_mult, &tempOne);
    bgfx::setViewName(viewCounter, "BlendVectorToDisplay");
    screenSpaceQuad(mScreenWidth, mScreenHeight);
    bgfx::submit(viewCounter);
    viewCounter++;

    if(mBrightness > 0) {
        // blend in the glow
        bgfx::setViewTransform(viewCounter, NULL, proj);
        bgfx::setViewRect(viewCounter, 0, 0, mScreenWidth, mScreenHeight);
        bgfx::setTexture(0, u_tex1, mGlow1FrameBuffer);
        bgfx::setProgram(mBlitShader);
        bgfx::setState( BGFX_STATE_RGB_WRITE 
                      | BGFX_STATE_ALPHA_WRITE 
                      | BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE, BGFX_STATE_BLEND_ONE)
                      );
        bgfx::setUniform(blur_uniform_mult, &glow_fin_mult);
        bgfx::setViewName(viewCounter, "BlendBlurToDisplay");
        screenSpaceQuad(mScreenWidth, mScreenHeight);
        bgfx::submit(viewCounter);
        viewCounter++;
    }
}

void VectorDisplay::beginDraw(float x, float y) {
    if (mPendingPoints.size() != 0) {
        assert(!"begin draw on already filled buffer!");
    }

    pending_point_t point;
    point.x = x * mDrawScale + mDrawOffsetX;
    point.y = y * mDrawScale + mDrawOffsetY;
    mPendingPoints.push_back(point);
}

void VectorDisplay::drawTo(float x, float y) {
    pending_point_t point;
    point.x = x * mDrawScale + mDrawOffsetX;
    point.y = y * mDrawScale + mDrawOffsetY;
    mPendingPoints.push_back(point);
}

void VectorDisplay::endDraw() {
    if (mPendingPoints.size() < 2) {
        mPendingPoints.clear();
        return;
    }

    // from the list of points, build a list of lines
    int     nlines = mPendingPoints.size()-1;
    line_t *lines  = (line_t*)alloca(nlines * sizeof(line_t));

    float t = effectiveThickness();
    int i;
    int  first_last_same = abs(mPendingPoints[0].x - mPendingPoints[mPendingPoints.size()-1].x) < 0.1 &&
                           abs(mPendingPoints[0].y - mPendingPoints[mPendingPoints.size()-1].y) < 0.1;

    // compute basics
    for (i = 1; i < mPendingPoints.size(); i++) {
        line_t *line = &lines[i-1];
        line->is_first = i == 1;
        line->is_last  = i == nlines;

        // precomputed info for current line
        line->x0    = mPendingPoints[i-1].x;
        line->y0    = mPendingPoints[i-1].y;
        line->x1    = mPendingPoints[i].x;
        line->y1    = mPendingPoints[i].y;
        line->a     = atan2(line->y1 - line->y0, line->x1 - line->x0);              // angle from positive x axis, increasing ccw, [-pi, pi]
        line->sin_a = sin(line->a);
        line->cos_a = cos(line->a);
        line->len   = sqrt((line->x1-line->x0)*(line->x1-line->x0) + (line->y1-line->y0)*(line->y1-line->y0));

        // figure out what connections we have
        line->has_prev = (!line->is_first || (line->is_first && first_last_same));
        line->has_next = (!line->is_last  || (line->is_last  && first_last_same));

        // initialize thicknesses/shortens to default values
        line->tl0 = line->tl1 = line->tr0 = line->tr1 = t;
        line->s0 = line->s1 = 0.0;
    }

    // compute adjustments for connected line segments
    for (i = 0; i < nlines; i++) {
        line_t *line  = &lines[i], *pline = &lines[(nlines+i-1)%nlines];

        if (line->has_prev) {
            float pa2a       = normalizef(pline->a -  line->a);
            float a2pa       = normalizef( line->a - pline->a);
            float maxshorten = min(line->len, pline->len) / 2.0;

            if (min(a2pa, pa2a) <= (M_PI / 2 + FLT_EPSILON)) {
                if (a2pa < pa2a) {
                    float shorten = t * sin(a2pa/2) / cos(a2pa/2);
                    float a       = (M_PI - a2pa) / 2;
                    if (shorten > maxshorten) {
                        line->s0  = pline->s1  = maxshorten;
                        line->tr0 = pline->tr1 = maxshorten * sin(a) / cos(a);
                    } else {
                        line->s0 = pline->s1 = shorten;
                    }
                    //vector_display_debugf("ad =  %f, shorten by %f (len=%f), rthickness %f (from %f)", a, line->s0, line->len, line->tr0, t);
                } else {
                    float shorten = t * sin(pa2a/2) / cos(pa2a/2);
                    float a       = (M_PI - pa2a) / 2;
                    if (shorten > maxshorten) {
                        line->s0  = pline->s1  = maxshorten;
                        line->tl0 = pline->tl1 = maxshorten * sin(a) / cos(a);
                    } else {
                        line->s0 = pline->s1 = shorten;
                    }
                    //vector_display_debugf("ad =  %f, shorten by %f (len=%f), rthickness by %f (from %f)", a, line->s0, line->len, line->tl0, t);
                }
            } else {
                line->has_prev  = 0;
            }
        }

        if(!line->has_prev) 
            pline->has_next = 0;
    }

    // compute line geometry
    for (i = 0; i < nlines; i++) {
        line_t *line  = &lines[i];

        // shorten lines if needed
        line->x0 = line->x0 + line->s0 * line->cos_a; 
        line->y0 = line->y0 + line->s0 * line->sin_a;
        line->x1 = line->x1 - line->s1 * line->cos_a;
        line->y1 = line->y1 - line->s1 * line->sin_a;

        // compute initial values for left,right,leftcenter,rightcenter points
        line->xl0 = line->x0 + line->tl0 * line->sin_a; 
        line->yl0 = line->y0 - line->tl0 * line->cos_a;
        line->xr0 = line->x0 - line->tr0 * line->sin_a; 
        line->yr0 = line->y0 + line->tr0 * line->cos_a;
        line->xl1 = line->x1 + line->tl1 * line->sin_a; 
        line->yl1 = line->y1 - line->tl1 * line->cos_a;
        line->xr1 = line->x1 - line->tr1 * line->sin_a; 
        line->yr1 = line->y1 + line->tr1 * line->cos_a;

        // compute tips
        line->xlt0 = line->xl0 - t * line->cos_a;
        line->ylt0 = line->yl0 - t * line->sin_a;
        line->xrt0 = line->xr0 - t * line->cos_a; 
        line->yrt0 = line->yr0 - t * line->sin_a;
        line->xlt1 = line->xl1 + t * line->cos_a; 
        line->ylt1 = line->yl1 + t * line->sin_a;
        line->xrt1 = line->xr1 + t * line->cos_a; 
        line->yrt1 = line->yr1 + t * line->sin_a;
    }

    // draw the lines
    drawLines(lines, nlines);
    mPendingPoints.clear();
}


void VectorDisplay::drawLine(float x0, float y0, float x1, float y1) {
    beginDraw(x0, y0);
    drawTo(x1, y1);
    endDraw();
}

void VectorDisplay::drawBox(float x, float y, float w, float h) {
    beginDraw(x, y);
    drawTo(x + w, y);
    drawTo(x + w, y + h);
    drawTo(x, y + h);
    drawTo(x, y);
    endDraw();
}

void VectorDisplay::drawCircle(float x, float y, float radius, float steps) {
    float edgeangle = 0.0f;
    float angadjust = 0.0f;

    float step = M_PI * 2 / steps;

    beginDraw(x + radius * sin(edgeangle + angadjust),
              y - radius * cos(edgeangle + angadjust));
    for (edgeangle = 0; edgeangle < 2 * M_PI - 0.001; edgeangle += step) {
        drawTo(x + radius * sin(edgeangle + step - angadjust),
               y - radius * cos(edgeangle + step - angadjust));
    }
    endDraw();

}

void VectorDisplay::drawWheel(float angle, float x, float y, float radius) {
    float spokeradius = radius - 2.0f;
    // draw spokes
    drawLine(x + spokeradius * sin(angle),
             y - spokeradius * cos(angle),
             x - spokeradius * sin(angle),
             y + spokeradius * cos(angle));
    drawLine(x + spokeradius * sin(angle + M_PI / 4.0f),
             y - spokeradius * cos(angle + M_PI / 4.0f),
             x - spokeradius * sin(angle + M_PI / 4.0f),
             y + spokeradius * cos(angle + M_PI / 4.0f));
    drawLine(x + spokeradius * sin(angle + M_PI / 2.0f),
             y - spokeradius * cos(angle + M_PI / 2.0f),
             x - spokeradius * sin(angle + M_PI / 2.0f),
             y + spokeradius * cos(angle + M_PI / 2.0f));
    drawLine(x + spokeradius * sin(angle + 3.0f * M_PI / 4.0f),
             y - spokeradius * cos(angle + 3.0f * M_PI / 4.0f),
             x - spokeradius * sin(angle + 3.0f * M_PI / 4.0f),
             y + spokeradius * cos(angle + 3.0f * M_PI / 4.0f));

    float edgeangle = 0.0f;
    float angadjust = 0.0f;

    beginDraw(x + radius * sin(angle + edgeangle + angadjust),
              y - radius * cos(angle + edgeangle + angadjust));
    for (edgeangle = 0; edgeangle < 2 * M_PI - 0.001; edgeangle += M_PI/4.0f) {
        drawTo(x + radius * sin(angle + edgeangle + M_PI / 4.0f - angadjust),
               y - radius * cos(angle + edgeangle + M_PI / 4.0f - angadjust));
    }
    endDraw();
}


float VectorDisplay::effectiveThickness() {
    if (mCustomThicknessEnabled) {
        return mThickness * mDrawScale / 2;
    } else {
        // this makes thickness=16 at 2048x1536
        float v = (0.01 * (mScreenWidth + mScreenHeight) / 2.0) * mDrawScale / 2;
        return max(v, 6);
    }
}

void VectorDisplay::setTransform(float offset_x, float offset_y, float scale) {
    mDrawOffsetX = offset_x;
    mDrawOffsetY = offset_y;
    mDrawScale    = scale;
}


int VectorDisplay::setInitialDecay(float initial_decay) {
    if (initial_decay < 0.0f || initial_decay >= 1.0f) 
        return -1;
    mInitialDecay = initial_decay;
    return 0;
}

int VectorDisplay::setThickness(float thickness) {
    if (thickness <= 0) 
        return -1;
    mCustomThicknessEnabled = true;
    mThickness = thickness;
    return 0;
}

void VectorDisplay::setDefaultThickness() {
    mCustomThicknessEnabled = false;
}

void VectorDisplay::setDrawColor(float r, float g, float b, float a) {
    mDrawColorR = r * 255;
    mDrawColorG = g * 255;
    mDrawColorB = b * 255;
    mDrawColorA = a * 255;
}

void VectorDisplay::appendTexpoint(float x, float y, float u, float v) {
    point_t point;
    point.x = x;
    point.y = y;
    point.z = 0.0;
    point.color = (mDrawColorA<<24) | (mDrawColorB<<16) | (mDrawColorG<<8) | mDrawColorR;
    point.u = u / cTextureSize;
    point.v = 1.0f - v / cTextureSize;
    mPoints.push_back(point);
}

float VectorDisplay::normalizef(float a) {
    while (a > 2*M_PI + FLT_EPSILON) 
        a -= 2*M_PI;
    while (a < 0 - FLT_EPSILON)      
        a += 2*M_PI;
    return a;
}

void VectorDisplay::drawFan(float cx, float cy, float pa, float a, float t, float s, float e) {
    float *angles;
    int    nsteps;
    float  pa2a = normalizef(a - pa);
    float  a2pa = normalizef(pa - a);

    int i;
    if (a2pa < pa2a) {
        t = -t;
        nsteps = max(1, round(a2pa / (M_PI / 8)));
        angles = (float*)alloca(sizeof(float) * (nsteps + 1));
        for (i = 0; i <= nsteps; i++)
            angles[i] = a + i * a2pa / nsteps;
    } else {
        nsteps = max(1, round(pa2a / (M_PI / 8)));
        angles = (float*)alloca(sizeof(float) * (nsteps + 1));
        for (i = 0; i <= nsteps; i++)
            angles[i] = pa + i * pa2a / nsteps;
    }

    for (i = 1; i <= nsteps; i++) {
        appendTexpoint(cx + t * sin(angles[i-1]), cy - t * cos(angles[i-1]), e, cHalfTextureSize);
        appendTexpoint(cx, cy,                                               s, cHalfTextureSize);
        appendTexpoint(cx + t * sin(angles[i]),   cy - t * cos(angles[i]),   e, cHalfTextureSize);
    }
}

void VectorDisplay::drawLines(line_t *lines, int nlines) {
    int    i;
    float t = effectiveThickness();

    for (i = 0; i < nlines; i++) {
        line_t *line  = &lines[i], *pline = &lines[(nlines+i-1)%nlines];

        if (line->has_prev) {   // draw fan for connection to previous
            float  pa2a = normalizef(pline->a -  line->a);
            float  a2pa = normalizef( line->a - pline->a);
            if (a2pa < pa2a) {  // inside of fan on right
                drawFan(line->xr0, line->yr0, pline->a, line->a, line->tl0 + line->tr0, cHalfTextureSize + (line->tr0 / t * cHalfTextureSize), 0);
            } else {            // inside of fan on left
                drawFan(line->xl0, line->yl0, pline->a, line->a, line->tl0 + line->tr0, cHalfTextureSize - (line->tl0 / t * cHalfTextureSize), cTextureSize);
            }
        }

        float tl0 = cHalfTextureSize - (line->tl0 / t) * cHalfTextureSize;
        float tl1 = cHalfTextureSize - (line->tl1 / t) * cHalfTextureSize;

        float tr0 = cHalfTextureSize + (line->tr0 / t) * cHalfTextureSize;
        float tr1 = cHalfTextureSize + (line->tr1 / t) * cHalfTextureSize;

        appendTexpoint(line->xr0,  line->yr0,  tr0, cHalfTextureSize);
        appendTexpoint(line->xr1,  line->yr1,  tr1, cHalfTextureSize);
        appendTexpoint(line->xl1,  line->yl1,  tl1, cHalfTextureSize);
        appendTexpoint(line->xl0,  line->yl0,  tl0, cHalfTextureSize);
        appendTexpoint(line->xr0,  line->yr0,  tr0, cHalfTextureSize);
        appendTexpoint(line->xl1,  line->yl1,  tl1, cHalfTextureSize);

        if (!line->has_prev) { // draw startcap
            appendTexpoint(line->xl0,  line->yl0,  tl0, cHalfTextureSize);
            appendTexpoint(line->xlt0, line->ylt0, tl0, 0.0f);
            appendTexpoint(line->xr0,  line->yr0,  tr0, cHalfTextureSize);
            appendTexpoint(line->xr0,  line->yr0,  tr0, cHalfTextureSize);
            appendTexpoint(line->xlt0, line->ylt0, tl0, 0.0f);
            appendTexpoint(line->xrt0, line->yrt0, tr0, 0.0f);
        }

        if (!line->has_next) { // draw endcap
            appendTexpoint(line->xlt1, line->ylt1, tl1, 0.0f);
            appendTexpoint(line->xl1,  line->yl1,  tl1, cHalfTextureSize);
            appendTexpoint(line->xr1,  line->yr1,  tr1, cHalfTextureSize);
            appendTexpoint(line->xlt1, line->ylt1, tl1, 0.0f);
            appendTexpoint(line->xr1,  line->yr1,  tr1, cHalfTextureSize);
            appendTexpoint(line->xrt1, line->yrt1, tr1, 0.0f);
        }
    }
}

int VectorDisplay::setDecaySteps(int steps) {
    if (steps < 0 || steps > cMaxDecaySteps) 
        return -1;

    mNumberDecaySteps = steps;

    if(mVertexBuffers.size() != 0) {
        for(int i=0; i<mVertexBuffers.size(); ++i) {
            destroyDynamicVertexBuffer(mVertexBuffers[i]);
        }
        mVertexBuffers.clear();
        mVertexBuffersSize.clear();
    }

    for(int i=0; i<mNumberDecaySteps; ++i) {
        mVertexBuffers.push_back( bgfx::createDynamicVertexBuffer(cMaxNumberVertices, PosColorUvVertex::ms_decl));
        mVertexBuffersSize.push_back(0);
    }
    return 0;
}

int VectorDisplay::setDecay(float decay) {
    if (decay < 0.0f || decay >= 1.0f) 
        return -1;
    mDecayValue = decay;
    return 0;
}

void VectorDisplay::setBrightness(float brightness) {
    mBrightness = brightness;
}

void VectorDisplay::getSize(float *out_width, float *out_height) {
    *out_width = mScreenWidth;
    *out_height = mScreenHeight;
}

void VectorDisplay::screenSpaceQuad(float textureWidth, float textureHeight, float width, float height) {
    if (bgfx::checkAvailTransientVertexBuffer(3, PosColorUvVertex::ms_decl) )     {
        bgfx::TransientVertexBuffer vb;
        bgfx::allocTransientVertexBuffer(&vb, 3, PosColorUvVertex::ms_decl);
        PosColorUvVertex* vertex = (PosColorUvVertex*)vb.data;

        const float zz = 0.0f;

        const float minx = -width;
        const float maxx =  width;
        const float miny = 0.0f;
        const float maxy = height*2.0f;

        const float texelHalfW = mTexelHalf/textureWidth;
        const float texelHalfH = mTexelHalf/textureHeight;
        const float minu = -1.0f + texelHalfW;
        const float maxu =  1.0f + texelHalfW;

        float minv = texelHalfH;
        float maxv = 2.0f + texelHalfH;

        if (mOriginBottomLeft)
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
        vertex[0].m_abgr = 0xffffffff;
        vertex[0].m_u = minu;
        vertex[0].m_v = minv;

        vertex[1].m_x = maxx;
        vertex[1].m_y = miny;
        vertex[1].m_z = zz;
        vertex[1].m_abgr = 0xffffffff;
        vertex[1].m_u = maxu;
        vertex[1].m_v = minv;

        vertex[2].m_x = maxx;
        vertex[2].m_y = maxy;
        vertex[2].m_z = zz;
        vertex[2].m_abgr = 0xffffffff;
        vertex[2].m_u = maxu;
        vertex[2].m_v = maxv;

        bgfx::setVertexBuffer(&vb);
    }
}


void VectorDisplay::setupResDependent() {
    const uint32_t samplerFlags = BGFX_TEXTURE_RT
                                | BGFX_TEXTURE_MIN_POINT
                                | BGFX_TEXTURE_MAG_POINT
                                | BGFX_TEXTURE_MIP_POINT
                                | BGFX_TEXTURE_U_CLAMP
                                | BGFX_TEXTURE_V_CLAMP
        ; 
    mSceneFrameBuffer = bgfx::createFrameBuffer(mScreenWidth, mScreenHeight, bgfx::TextureFormat::BGRA8, samplerFlags);

    mGlowWidth  = mScreenWidth  / 3.0;
    mGlowHeight = mScreenHeight / 3.0;

    mGlow0FrameBuffer = bgfx::createFrameBuffer(mGlowWidth, mGlowHeight, bgfx::TextureFormat::BGRA8, samplerFlags);
    mGlow1FrameBuffer = bgfx::createFrameBuffer(mGlowWidth, mGlowHeight, bgfx::TextureFormat::BGRA8, samplerFlags);
}

void VectorDisplay::teardownResDependent() {
    bgfx::destroyFrameBuffer(mSceneFrameBuffer);
    bgfx::destroyFrameBuffer(mGlow0FrameBuffer);
    bgfx::destroyFrameBuffer(mGlow1FrameBuffer);
}

void VectorDisplay::genLinetex() {                                  // generate the texture
    const bgfx::Memory* mem = bgfx::alloc(cTextureSize*cTextureSize*4);
    unsigned char *texbuf = (unsigned char*)mem->data;

    memset(texbuf, 0xff, mem->size);
    int x,y;
    for (x = 0; x < cTextureSize; x++) {
        for (y = 0; y < cTextureSize; y++) {
            float distance = sqrt((float)((x-cHalfTextureSize)*(x-cHalfTextureSize) + (y-cHalfTextureSize)*(y-cHalfTextureSize))) / (float)cHalfTextureSize;

            if (distance > 1.0)
                distance = 1.0;

            float line = pow(16, -2 * distance);
            float glow = pow(2,  -4 * distance) / 10.0;
            glow = 0;
            float val  = max(0, min(1, line + glow));                  // clamp

            texbuf[(x + y * cTextureSize) * 4 + 0] = 0xff;
            texbuf[(x + y * cTextureSize) * 4 + 1] = 0xff;
            texbuf[(x + y * cTextureSize) * 4 + 2] = 0xff;
            texbuf[(x + y * cTextureSize) * 4 + 3] = (unsigned char)(val*0xff);
        }
    }

    int flags = BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP|BGFX_TEXTURE_MIN_POINT|BGFX_TEXTURE_MAG_POINT;

    mLineTexId = bgfx::createTexture2D(cTextureSize, cTextureSize, 1, bgfx::TextureFormat::BGRA8, flags, mem);
    u_linetexid = bgfx::createUniform("u_linetexid",   bgfx::UniformType::Uniform1iv); 
}

static int simplex[95][112] = {
    0,16, /* Ascii 32 */
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8,10, /* Ascii 33 */
    5,21, 5, 7,-1,-1, 5, 2, 4, 1, 5, 0, 6, 1, 5, 2,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    5,16, /* Ascii 34 */
    4,21, 4,14,-1,-1,12,21,12,14,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   11,21, /* Ascii 35 */
   11,25, 4,-7,-1,-1,17,25,10,-7,-1,-1, 4,12,18,12,-1,-1, 3, 6,17, 6,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   26,20, /* Ascii 36 */
    8,25, 8,-4,-1,-1,12,25,12,-4,-1,-1,17,18,15,20,12,21, 8,21, 5,20, 3,
   18, 3,16, 4,14, 5,13, 7,12,13,10,15, 9,16, 8,17, 6,17, 3,15, 1,12, 0,
    8, 0, 5, 1, 3, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   31,24, /* Ascii 37 */
   21,21, 3, 0,-1,-1, 8,21,10,19,10,17, 9,15, 7,14, 5,14, 3,16, 3,18, 4,
   20, 6,21, 8,21,10,20,13,19,16,19,19,20,21,21,-1,-1,17, 7,15, 6,14, 4,
   14, 2,16, 0,18, 0,20, 1,21, 3,21, 5,19, 7,17, 7,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   34,26, /* Ascii 38 */
   23,12,23,13,22,14,21,14,20,13,19,11,17, 6,15, 3,13, 1,11, 0, 7, 0, 5,
    1, 4, 2, 3, 4, 3, 6, 4, 8, 5, 9,12,13,13,14,14,16,14,18,13,20,11,21,
    9,20, 8,18, 8,16, 9,13,11,10,16, 3,18, 1,20, 0,22, 0,23, 1,23, 2,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    7,10, /* Ascii 39 */
    5,19, 4,20, 5,21, 6,20, 6,18, 5,16, 4,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   10,14, /* Ascii 40 */
   11,25, 9,23, 7,20, 5,16, 4,11, 4, 7, 5, 2, 7,-2, 9,-5,11,-7,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   10,14, /* Ascii 41 */
    3,25, 5,23, 7,20, 9,16,10,11,10, 7, 9, 2, 7,-2, 5,-5, 3,-7,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8,16, /* Ascii 42 */
    8,21, 8, 9,-1,-1, 3,18,13,12,-1,-1,13,18, 3,12,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    5,26, /* Ascii 43 */
   13,18,13, 0,-1,-1, 4, 9,22, 9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8,10, /* Ascii 44 */
    6, 1, 5, 0, 4, 1, 5, 2, 6, 1, 6,-1, 5,-3, 4,-4,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    2,26, /* Ascii 45 */
    4, 9,22, 9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    5,10, /* Ascii 46 */
    5, 2, 4, 1, 5, 0, 6, 1, 5, 2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    2,22, /* Ascii 47 */
   20,25, 2,-7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   17,20, /* Ascii 48 */
    9,21, 6,20, 4,17, 3,12, 3, 9, 4, 4, 6, 1, 9, 0,11, 0,14, 1,16, 4,17,
    9,17,12,16,17,14,20,11,21, 9,21,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    4,20, /* Ascii 49 */
    6,17, 8,18,11,21,11, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   14,20, /* Ascii 50 */
    4,16, 4,17, 5,19, 6,20, 8,21,12,21,14,20,15,19,16,17,16,15,15,13,13,
   10, 3, 0,17, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   15,20, /* Ascii 51 */
    5,21,16,21,10,13,13,13,15,12,16,11,17, 8,17, 6,16, 3,14, 1,11, 0, 8,
    0, 5, 1, 4, 2, 3, 4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    6,20, /* Ascii 52 */
   13,21, 3, 7,18, 7,-1,-1,13,21,13, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   17,20, /* Ascii 53 */
   15,21, 5,21, 4,12, 5,13, 8,14,11,14,14,13,16,11,17, 8,17, 6,16, 3,14,
    1,11, 0, 8, 0, 5, 1, 4, 2, 3, 4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   23,20, /* Ascii 54 */
   16,18,15,20,12,21,10,21, 7,20, 5,17, 4,12, 4, 7, 5, 3, 7, 1,10, 0,11,
    0,14, 1,16, 3,17, 6,17, 7,16,10,14,12,11,13,10,13, 7,12, 5,10, 4, 7,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    5,20, /* Ascii 55 */
   17,21, 7, 0,-1,-1, 3,21,17,21,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   29,20, /* Ascii 56 */
    8,21, 5,20, 4,18, 4,16, 5,14, 7,13,11,12,14,11,16, 9,17, 7,17, 4,16,
    2,15, 1,12, 0, 8, 0, 5, 1, 4, 2, 3, 4, 3, 7, 4, 9, 6,11, 9,12,13,13,
   15,14,16,16,16,18,15,20,12,21, 8,21,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   23,20, /* Ascii 57 */
   16,14,15,11,13, 9,10, 8, 9, 8, 6, 9, 4,11, 3,14, 3,15, 4,18, 6,20, 9,
   21,10,21,13,20,15,18,16,14,16, 9,15, 4,13, 1,10, 0, 8, 0, 5, 1, 4, 3,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   11,10, /* Ascii 58 */
    5,14, 4,13, 5,12, 6,13, 5,14,-1,-1, 5, 2, 4, 1, 5, 0, 6, 1, 5, 2,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   14,10, /* Ascii 59 */
    5,14, 4,13, 5,12, 6,13, 5,14,-1,-1, 6, 1, 5, 0, 4, 1, 5, 2, 6, 1, 6,
   -1, 5,-3, 4,-4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    3,24, /* Ascii 60 */
   20,18, 4, 9,20, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    5,26, /* Ascii 61 */
    4,12,22,12,-1,-1, 4, 6,22, 6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    3,24, /* Ascii 62 */
    4,18,20, 9, 4, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   20,18, /* Ascii 63 */
    3,16, 3,17, 4,19, 5,20, 7,21,11,21,13,20,14,19,15,17,15,15,14,13,13,
   12, 9,10, 9, 7,-1,-1, 9, 2, 8, 1, 9, 0,10, 1, 9, 2,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   55,27, /* Ascii 64 */
   18,13,17,15,15,16,12,16,10,15, 9,14, 8,11, 8, 8, 9, 6,11, 5,14, 5,16,
    6,17, 8,-1,-1,12,16,10,14, 9,11, 9, 8,10, 6,11, 5,-1,-1,18,16,17, 8,
   17, 6,19, 5,21, 5,23, 7,24,10,24,12,23,15,22,17,20,19,18,20,15,21,12,
   21, 9,20, 7,19, 5,17, 4,15, 3,12, 3, 9, 4, 6, 5, 4, 7, 2, 9, 1,12, 0,
   15, 0,18, 1,20, 2,21, 3,-1,-1,19,16,18, 8,18, 6,19, 5,
    8,18, /* Ascii 65 */
    9,21, 1, 0,-1,-1, 9,21,17, 0,-1,-1, 4, 7,14, 7,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   23,21, /* Ascii 66 */
    4,21, 4, 0,-1,-1, 4,21,13,21,16,20,17,19,18,17,18,15,17,13,16,12,13,
   11,-1,-1, 4,11,13,11,16,10,17, 9,18, 7,18, 4,17, 2,16, 1,13, 0, 4, 0,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   18,21, /* Ascii 67 */
   18,16,17,18,15,20,13,21, 9,21, 7,20, 5,18, 4,16, 3,13, 3, 8, 4, 5, 5,
    3, 7, 1, 9, 0,13, 0,15, 1,17, 3,18, 5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   15,21, /* Ascii 68 */
    4,21, 4, 0,-1,-1, 4,21,11,21,14,20,16,18,17,16,18,13,18, 8,17, 5,16,
    3,14, 1,11, 0, 4, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   11,19, /* Ascii 69 */
    4,21, 4, 0,-1,-1, 4,21,17,21,-1,-1, 4,11,12,11,-1,-1, 4, 0,17, 0,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8,18, /* Ascii 70 */
    4,21, 4, 0,-1,-1, 4,21,17,21,-1,-1, 4,11,12,11,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   22,21, /* Ascii 71 */
   18,16,17,18,15,20,13,21, 9,21, 7,20, 5,18, 4,16, 3,13, 3, 8, 4, 5, 5,
    3, 7, 1, 9, 0,13, 0,15, 1,17, 3,18, 5,18, 8,-1,-1,13, 8,18, 8,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8,22, /* Ascii 72 */
    4,21, 4, 0,-1,-1,18,21,18, 0,-1,-1, 4,11,18,11,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    2, 8, /* Ascii 73 */
    4,21, 4, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   10,16, /* Ascii 74 */
   12,21,12, 5,11, 2,10, 1, 8, 0, 6, 0, 4, 1, 3, 2, 2, 5, 2, 7,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8,21, /* Ascii 75 */
    4,21, 4, 0,-1,-1,18,21, 4, 7,-1,-1, 9,12,18, 0,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    5,17, /* Ascii 76 */
    4,21, 4, 0,-1,-1, 4, 0,16, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   11,24, /* Ascii 77 */
    4,21, 4, 0,-1,-1, 4,21,12, 0,-1,-1,20,21,12, 0,-1,-1,20,21,20, 0,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8,22, /* Ascii 78 */
    4,21, 4, 0,-1,-1, 4,21,18, 0,-1,-1,18,21,18, 0,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   21,22, /* Ascii 79 */
    9,21, 7,20, 5,18, 4,16, 3,13, 3, 8, 4, 5, 5, 3, 7, 1, 9, 0,13, 0,15,
    1,17, 3,18, 5,19, 8,19,13,18,16,17,18,15,20,13,21, 9,21,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   13,21, /* Ascii 80 */
    4,21, 4, 0,-1,-1, 4,21,13,21,16,20,17,19,18,17,18,14,17,12,16,11,13,
   10, 4,10,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   24,22, /* Ascii 81 */
    9,21, 7,20, 5,18, 4,16, 3,13, 3, 8, 4, 5, 5, 3, 7, 1, 9, 0,13, 0,15,
    1,17, 3,18, 5,19, 8,19,13,18,16,17,18,15,20,13,21, 9,21,-1,-1,12, 4,
   18,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   16,21, /* Ascii 82 */
    4,21, 4, 0,-1,-1, 4,21,13,21,16,20,17,19,18,17,18,15,17,13,16,12,13,
   11, 4,11,-1,-1,11,11,18, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   20,20, /* Ascii 83 */
   17,18,15,20,12,21, 8,21, 5,20, 3,18, 3,16, 4,14, 5,13, 7,12,13,10,15,
    9,16, 8,17, 6,17, 3,15, 1,12, 0, 8, 0, 5, 1, 3, 3,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    5,16, /* Ascii 84 */
    8,21, 8, 0,-1,-1, 1,21,15,21,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   10,22, /* Ascii 85 */
    4,21, 4, 6, 5, 3, 7, 1,10, 0,12, 0,15, 1,17, 3,18, 6,18,21,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    5,18, /* Ascii 86 */
    1,21, 9, 0,-1,-1,17,21, 9, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   11,24, /* Ascii 87 */
    2,21, 7, 0,-1,-1,12,21, 7, 0,-1,-1,12,21,17, 0,-1,-1,22,21,17, 0,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    5,20, /* Ascii 88 */
    3,21,17, 0,-1,-1,17,21, 3, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    6,18, /* Ascii 89 */
    1,21, 9,11, 9, 0,-1,-1,17,21, 9,11,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8,20, /* Ascii 90 */
   17,21, 3, 0,-1,-1, 3,21,17,21,-1,-1, 3, 0,17, 0,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   11,14, /* Ascii 91 */
    4,25, 4,-7,-1,-1, 5,25, 5,-7,-1,-1, 4,25,11,25,-1,-1, 4,-7,11,-7,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    2,14, /* Ascii 92 */
    0,21,14,-3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   11,14, /* Ascii 93 */
    9,25, 9,-7,-1,-1,10,25,10,-7,-1,-1, 3,25,10,25,-1,-1, 3,-7,10,-7,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   10,16, /* Ascii 94 */
    6,15, 8,18,10,15,-1,-1, 3,12, 8,17,13,12,-1,-1, 8,17, 8, 0,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    2,16, /* Ascii 95 */
    0,-2,16,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    7,10, /* Ascii 96 */
    6,21, 5,20, 4,18, 4,16, 5,15, 6,16, 5,17,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   17,19, /* Ascii 97 */
   15,14,15, 0,-1,-1,15,11,13,13,11,14, 8,14, 6,13, 4,11, 3, 8, 3, 6, 4,
    3, 6, 1, 8, 0,11, 0,13, 1,15, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   17,19, /* Ascii 98 */
    4,21, 4, 0,-1,-1, 4,11, 6,13, 8,14,11,14,13,13,15,11,16, 8,16, 6,15,
    3,13, 1,11, 0, 8, 0, 6, 1, 4, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   14,18, /* Ascii 99 */
   15,11,13,13,11,14, 8,14, 6,13, 4,11, 3, 8, 3, 6, 4, 3, 6, 1, 8, 0,11,
    0,13, 1,15, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   17,19, /* Ascii 100 */
   15,21,15, 0,-1,-1,15,11,13,13,11,14, 8,14, 6,13, 4,11, 3, 8, 3, 6, 4,
    3, 6, 1, 8, 0,11, 0,13, 1,15, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   17,18, /* Ascii 101 */
    3, 8,15, 8,15,10,14,12,13,13,11,14, 8,14, 6,13, 4,11, 3, 8, 3, 6, 4,
    3, 6, 1, 8, 0,11, 0,13, 1,15, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8,12, /* Ascii 102 */
   10,21, 8,21, 6,20, 5,17, 5, 0,-1,-1, 2,14, 9,14,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   22,19, /* Ascii 103 */
   15,14,15,-2,14,-5,13,-6,11,-7, 8,-7, 6,-6,-1,-1,15,11,13,13,11,14, 8,
   14, 6,13, 4,11, 3, 8, 3, 6, 4, 3, 6, 1, 8, 0,11, 0,13, 1,15, 3,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   10,19, /* Ascii 104 */
    4,21, 4, 0,-1,-1, 4,10, 7,13, 9,14,12,14,14,13,15,10,15, 0,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8, 8, /* Ascii 105 */
    3,21, 4,20, 5,21, 4,22, 3,21,-1,-1, 4,14, 4, 0,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   11,10, /* Ascii 106 */
    5,21, 6,20, 7,21, 6,22, 5,21,-1,-1, 6,14, 6,-3, 5,-6, 3,-7, 1,-7,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8,17, /* Ascii 107 */
    4,21, 4, 0,-1,-1,14,14, 4, 4,-1,-1, 8, 8,15, 0,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    2, 8, /* Ascii 108 */
    4,21, 4, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   18,30, /* Ascii 109 */
    4,14, 4, 0,-1,-1, 4,10, 7,13, 9,14,12,14,14,13,15,10,15, 0,-1,-1,15,
   10,18,13,20,14,23,14,25,13,26,10,26, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   10,19, /* Ascii 110 */
    4,14, 4, 0,-1,-1, 4,10, 7,13, 9,14,12,14,14,13,15,10,15, 0,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   17,19, /* Ascii 111 */
    8,14, 6,13, 4,11, 3, 8, 3, 6, 4, 3, 6, 1, 8, 0,11, 0,13, 1,15, 3,16,
    6,16, 8,15,11,13,13,11,14, 8,14,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   17,19, /* Ascii 112 */
    4,14, 4,-7,-1,-1, 4,11, 6,13, 8,14,11,14,13,13,15,11,16, 8,16, 6,15,
    3,13, 1,11, 0, 8, 0, 6, 1, 4, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   17,19, /* Ascii 113 */
   15,14,15,-7,-1,-1,15,11,13,13,11,14, 8,14, 6,13, 4,11, 3, 8, 3, 6, 4,
    3, 6, 1, 8, 0,11, 0,13, 1,15, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8,13, /* Ascii 114 */
    4,14, 4, 0,-1,-1, 4, 8, 5,11, 7,13, 9,14,12,14,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   17,17, /* Ascii 115 */
   14,11,13,13,10,14, 7,14, 4,13, 3,11, 4, 9, 6, 8,11, 7,13, 6,14, 4,14,
    3,13, 1,10, 0, 7, 0, 4, 1, 3, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8,12, /* Ascii 116 */
    5,21, 5, 4, 6, 1, 8, 0,10, 0,-1,-1, 2,14, 9,14,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   10,19, /* Ascii 117 */
    4,14, 4, 4, 5, 1, 7, 0,10, 0,12, 1,15, 4,-1,-1,15,14,15, 0,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    5,16, /* Ascii 118 */
    2,14, 8, 0,-1,-1,14,14, 8, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   11,22, /* Ascii 119 */
    3,14, 7, 0,-1,-1,11,14, 7, 0,-1,-1,11,14,15, 0,-1,-1,19,14,15, 0,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    5,17, /* Ascii 120 */
    3,14,14, 0,-1,-1,14,14, 3, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    9,16, /* Ascii 121 */
    2,14, 8, 0,-1,-1,14,14, 8, 0, 6,-4, 4,-6, 2,-7, 1,-7,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    8,17, /* Ascii 122 */
   14,14, 3, 0,-1,-1, 3,14,14,14,-1,-1, 3, 0,14, 0,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   39,14, /* Ascii 123 */
    9,25, 7,24, 6,23, 5,21, 5,19, 6,17, 7,16, 8,14, 8,12, 6,10,-1,-1, 7,
   24, 6,22, 6,20, 7,18, 8,17, 9,15, 9,13, 8,11, 4, 9, 8, 7, 9, 5, 9, 3,
    8, 1, 7, 0, 6,-2, 6,-4, 7,-6,-1,-1, 6, 8, 8, 6, 8, 4, 7, 2, 6, 1, 5,
   -1, 5,-3, 6,-5, 7,-6, 9,-7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    2, 8, /* Ascii 124 */
    4,25, 4,-7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   39,14, /* Ascii 125 */
    5,25, 7,24, 8,23, 9,21, 9,19, 8,17, 7,16, 6,14, 6,12, 8,10,-1,-1, 7,
   24, 8,22, 8,20, 7,18, 6,17, 5,15, 5,13, 6,11,10, 9, 6, 7, 5, 5, 5, 3,
    6, 1, 7, 0, 8,-2, 8,-4, 7,-6,-1,-1, 8, 8, 6, 6, 6, 4, 7, 2, 8, 1, 9,
   -1, 9,-3, 8,-5, 7,-6, 5,-7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   23,24, /* Ascii 126 */
    3, 6, 3, 8, 4,11, 6,12, 8,12,10,11,14, 8,16, 7,18, 7,20, 8,21,10,-1,
   -1, 3, 8, 4,10, 6,11, 8,11,10,10,14, 7,16, 6,18, 6,20, 7,21,10,21,12,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
};

//void VectorDisplay::simplexMeasure(float scale, const char *string, float *out_width, float *out_height) {
    //not implemented :/
//}

void VectorDisplay::drawSimplexFont(float x, float y, float scale, const char *s) {
    for (;;) {
        char c = *s++;
        if (!c)                break;
        if (c < 32 || c > 126) continue;

        int *chr = simplex[c - 32];

        int nvertices = chr[0];
        int spacing   = chr[1];

        bool isDrawing = false;
        int i;
        for (i = 0; i < nvertices; i++) {
            int vx = chr[2 + i * 2];
            int vy = chr[2 + i * 2 + 1];
            if (vx == -1 && vy == -1) {
                if (isDrawing) {
                    endDraw();
                    isDrawing = false;
                }
            } else if (!isDrawing) {
                beginDraw(x + vx * scale, y - vy * scale);
                isDrawing = true;
            } else {
                drawTo(x + vx * scale, y - vy * scale);
            }
        }
        x += spacing * scale;
        if(isDrawing) 
            endDraw();
    }

}
