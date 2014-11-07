
// based on code from  Brian Luczkiewicz
// https://github.com/blucz/Vector

#ifndef __QVECTORDISPLAY_VECTORDISPLAY_H__
#define __QVECTORDISPLAY_VECTORDISPLAY_H__

#include "bgfx.h"

#include <tinystl/allocator.h>
#include <tinystl/vector.h>
namespace stl = tinystl;

class VectorDisplay {
public:
   VectorDisplay(bool originBottomLeft, float texelHalf) 
      : mOriginBottomLeft(originBottomLeft)
      , mTexelHalf(texelHalf)
   {}
   ~VectorDisplay() {}

   void setup(float width, float height, int view = 2);
   void resize(float width, float height);
   void teardown();

   void clear();
   void update();

   // Draw a series of connected line segments.
   void beginDraw(float x, float y);
   void drawTo(float x, float y);
   void endDraw();

   //HighLevel draw functions
  void drawLine(float x0, float y0, float x1, float y1);
  void drawBox(float x, float y, float w, float h);
  void drawCircle(float x, float y, float radius, float steps);
  void drawWheel(float spokeangle, float x, float y, float radius);

   //Font Stuff (Simplex)
   //void simplexMeasure(float scale, const char *string, float *out_width, float *out_height);
   void simplexDraw(float x, float y, float scale, const char *s);

   // Set the current drawing color
   void setColor(float r, float g, float b);

   // Set the number of frames of decay/fade to apply to the scene.
   int setDecaySteps(int steps);

   // Set the brightness multipler applied on each decay frame after the first.
   int setDecay(float decay);

   // Set the brightness multipler applied on the first decay frame.
   int setInitialDecay(float initial_decay);

   // Set a 2d transformation for the display.
   //
   // This relates logical coordinates, as passed to vector_display_begin_draw, 
   // vector_display_draw_to, and vector_display_draw, to coordinates from (0,0) 
   // to (width,height) in the destination framebuffer.
   //
   // The parameters impact coordinates as follows:
   //
   //      framebuffer_x = x * scale + offset_x
   //      framebuffer_y = y * scale + offset_y
   //
   void setTransform(float offset_x, float offset_y, float scale);

   // Set the line thickness. 
   //
   // The line thickness is measured in scene coordinates, and includes all pixels lit by 
   // the line before any post-processing. The apparent width of the line to the viewer 
   // is significantly narrower, since brightness decays exponentially to zero within the 
   // bounds of the line.
   //
   // Thickness, by default, is guessed based on width and height.
   //
   // This function clears the display.
   int setThickness(float thickness);
   void setDefaultThickness();

   // Set the "brightness" of the display
   //
   // useful values range from [0.5, 1.5]. 0.0 disables all glow effects.
   //
   // Due to implementation details of the glow effect, glow is related to 
   // the pixel density of the framebuffer. It may require adjustment, 
   // particularly when moving between devices of very different pixel density.
   //
   void setBrightness(float brightness);

   // Get the size from a vector display.
   void getSize(float *out_width, float *out_height);
protected:
  void screenSpaceQuad(float textureWidth, float textureHeight, float width = 1.0f, float height = 1.0f);

   typedef struct {        //has to match the spec submitted to the 3d-api!
       float x, y, z;
       float u, v;
       uint32_t color;
   } point_t;

   typedef struct {
       float x, y;
   } pending_point_t;

   typedef struct {
       float x0, y0, x1, y1;                      // nominal points
       float a;                                   // angle
       float sin_a, cos_a;                        // precomputed trig

       float xl0, yl0, xl1, yl1;                  // left side of the box
       float xr0, yr0, xr1, yr1;                  // right side of the box

       int is_first, is_last;
       int has_next, has_prev;                     // booleans indicating whether this line connects to prev/next

       float xlt0, ylt0, xlt1, ylt1;              // coordinates of endcaps (if !has_prev/!has_next)
       float xrt0, yrt0, xrt1, yrt1;              // coordinates of endcaps (if !has_prev/!has_next)

       float tl0, tl1, tr0, tr1;

       float s0, s1;                              // shorten line by this amount

       float len;
   } line_t;

   float effectiveThickness();
   void setupResDependent();
   void teardownResDependent();

   void appendTexpoint(float x, float y, float u, float v);

   float normalizef(float a);

   void drawFan(float cx, float cy, float pa, float a, float t, float s, float e);
   void drawLines(line_t *lines, int nlines);
   void genLinetex();

   bool mOriginBottomLeft;
   float mTexelHalf;

    bgfx::ProgramHandle fb_program; // program for drawing to the fb
    bgfx::UniformHandle fb_uniform_alpha;

    bgfx::FrameBufferHandle fb_scene;

    bgfx::ProgramHandle blur_program;  // program for gaussian blur
    bgfx::UniformHandle blur_uniform_scale;
    bgfx::UniformHandle blur_uniform_alpha;
    bgfx::UniformHandle blur_uniform_mult;
    bgfx::UniformHandle u_tex1;           //texture handle for blur

    bgfx::ProgramHandle blit_program;

    bgfx::FrameBufferHandle fb_glow0;            // framebuffer for glow0
    bgfx::FrameBufferHandle fb_glow1;            // framebuffer for glow1

    int mView;

    float mScreenWidth, mScreenHeight;
    float mGlowWidth, mGlowHeight;

    int mNumberDecaySteps;
    float mDecayValue;
    uint8_t mDrawColorR, mDrawColorG, mDrawColorB, mDrawColorA;

    stl::vector<point_t> mPoints;
    stl::vector<pending_point_t> mPendingPoints;

    int mCurrentDrawStep;
    stl::vector<bgfx::DynamicVertexBufferHandle> mVertexBuffers;
    stl::vector<int> mVertexBuffersSize;

    bgfx::TextureHandle mLineTexId;
    bgfx::UniformHandle u_linetexid;

    float mInitialDecay;

    float mThickness;
    bool mCustomThicknessEnabled;

    float mBrightness;

    float mDrawOffsetX, mDrawOffsetY;
    float mDrawScale;
};


#endif   //#ifndef __QVECTORDISPLAY_VECTORDISPLAY_H__
