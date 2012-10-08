//-----------------------------------------------------------------------------
// Product:     OpenCTM tools
// File:        ctmviewer.cpp
// Description: 3D file viewer. The program can be used to view OpenCTM files
//              in an interactive OpenGL window. Files in other supported
//              formats can also be viewed.
//-----------------------------------------------------------------------------
// Copyright (c) 2009-2010 Marcus Geelnard
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//     1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
//
//     2. Altered source versions must be plainly marked as such, and must not
//     be misrepresented as being the original software.
//
//     3. This notice may not be removed or altered from any source
//     distribution.
//-----------------------------------------------------------------------------

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <GL/glew.h>
#ifdef __APPLE_CC__
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif
#include <openctm.h>
#include "mesh.h"
#include "meshio.h"
#include "sysdialog.h"
#include "systimer.h"
#include "image.h"
#include "common.h"

using namespace std;


// We need PI
#ifndef PI
  #define PI 3.141592653589793238462643f
#endif

// Configuration constants
#define FOCUS_TIME        0.1
#define DOUBLE_CLICK_TIME 0.25


//-----------------------------------------------------------------------------
// GLSL source code (generated from source by bin2c)
//-----------------------------------------------------------------------------

#include "phong_vert.h"
#include "phong_frag.h"


//-----------------------------------------------------------------------------
// Icon bitmaps
//-----------------------------------------------------------------------------

#include "icons/icon_open.h"
#include "icons/icon_save.h"
#include "icons/icon_texture.h"
#include "icons/icon_help.h"


//-----------------------------------------------------------------------------
// The GLViewer application class (declaration)
//-----------------------------------------------------------------------------

class GLButton;

class GLViewer {
  private:
    // File information for the current mesh
    string mFileName, mFilePath;
    long mFileSize;

    // Window state cariables
    int mWidth, mHeight;
    GLint mDepthBufferResolution;
    int mOldMouseX, mOldMouseY;
    double mLastClickTime;
    bool mMouseRotate;
    bool mMouseZoom;
    bool mMousePan;
    bool mFocusing;
    Vector3 mFocusStartPos;
    Vector3 mFocusEndPos;
    double mFocusStartTime;
    double mFocusEndTime;
    double mFocusStartDistance;
    double mFocusEndDistance;

    // Camera state
    Vector3 mCameraPosition;
    Vector3 mCameraLookAt;
    Vector3 mCameraUp;
    GLdouble mModelviewMatrix[16];
    GLdouble mProjectionMatrix[16];
    GLint mViewport[4];

    // Mesh information
    Mesh * mMesh;
    Vector3 mAABBMin, mAABBMax;
    GLuint mDisplayList;
    GLuint mTexHandle;

    // Polygon rendering mode (fill / line)
    GLenum mPolyMode;

    // GLSL objects
    bool mUseShader;
    GLuint mShaderProgram;
    GLuint mVertShader;
    GLuint mFragShader;

    // List of GUI buttons
    list<GLButton *> mButtons;

    // Master timer resource
    SysTimer mTimer;

    /// Set up the camera.
    void SetupCamera();

    /// Initialize the GLSL shader (requires OpenGL 2.0 or better).
    void InitShader();

    /// Initialize the texture.
    void InitTexture(const char * aFileName);

    /// Set up the scene lighting.
    void SetupLighting();

    /// Set up the material.
    void SetupMaterial();

    /// Draw a mesh
    void DrawMesh(Mesh * aMesh);

    /// Load a file to the mesh
    void LoadFile(const char * aFileName, const char * aOverrideTexture);

    /// Load a texture file
    void LoadTexture(const char * aFileName);

    /// Draw an outline box.
    void DrawOutlineBox(int x1, int y1, int x2, int y2,
      float r, float g, float b, float a);

    /// Draw a string using GLUT. The string is shown on top of an alpha-blended
    /// quad.
    void DrawString(string aString, int x, int y);

    /// Draw 2D overlay
    void Draw2DOverlay();

    /// Get 3D coordinate under the mouse cursor.
    bool WinCoordTo3DCoord(int x, int y, Vector3 &aPoint);

    /// Update the focus position of the camera.
    void UpdateFocus();

  public:
    /// Constructor
    GLViewer();

    /// Destructor
    ~GLViewer();

    /// Open another file
    void ActionOpenFile();

    /// Save the file
    void ActionSaveFile();

    /// Open a texture file
    void ActionOpenTexture();

    /// Toggle wire frame view on/off
    void ActionToggleWireframe();

    /// Fit model to the screen (re-focus)
    void ActionFitToScreen();

    /// Set camera up direction to Y
    void ActionCameraUpY();

    /// Set camera up direction to Z
    void ActionCameraUpZ();

    /// Zoom camera one step in
    void ActionZoomIn();

    /// Zoom camera one step out
    void ActionZoomOut();

    /// Exit program
    void ActionExit();

    /// Show a help dialog
    void ActionHelp();

    /// Redraw function.
    void WindowRedraw(void);

    /// Resize function.
    void WindowResize(int w, int h);

    /// Mouse click function
    void MouseClick(int button, int state, int x, int y);

    /// Mouse move function
    void MouseMove(int x, int y);

    /// Keyboard function
    void KeyDown(unsigned char key, int x, int y);

    /// Keyboard function (special keys)
    void SpecialKeyDown(int key, int x, int y);

    /// Run the application
    void Run(int argc, char **argv);
};



//-----------------------------------------------------------------------------
// A class for OpenGL rendered GUI buttons
//-----------------------------------------------------------------------------

class GLButton {
  private:
    // Texture handle
    GLuint mTexHandle;

    // Highlight on/off
    bool mHighlight;

  public:
    /// Constructor.
    GLButton()
    {
      mTexHandle = 0;
      mPosX = 0;
      mPosY = 0;
      mWidth = 32;
      mHeight = 32;
      mHighlight = false;
      mParent = NULL;
    }

    /// Destructor.
    virtual ~GLButton()
    {
      if(mTexHandle)
        glDeleteTextures(1, &mTexHandle);
    }

    /// Set glyph for this button.
    void SetGlyph(const unsigned char * aBitmap, int aWidth, int aHeight,
      int aComponents)
    {
      // Update the button size
      mWidth = aWidth;
      mHeight = aHeight;

      // Upload the texture to OpenGL
      if(mTexHandle)
        glDeleteTextures(1, &mTexHandle);
      glGenTextures(1, &mTexHandle);
      if(mTexHandle)
      {
        // Determine the color format
        GLuint format;
        if(aComponents == 3)
          format = GL_RGB;
        else if(aComponents == 4)
          format = GL_RGBA;
        else
          format = GL_LUMINANCE;

        glBindTexture(GL_TEXTURE_2D, mTexHandle);

        if(GLEW_VERSION_1_4)
        {
          // Generate mipmaps automatically and use them
          glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        }
        else
        {
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, aComponents, aWidth, aHeight, 0,
                     format, GL_UNSIGNED_BYTE, (GLvoid *) aBitmap);
      }
    }

    /// Redraw function.
    void Redraw()
    {
      // Set opacity of the icon
      if(mHighlight)
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
      else
        glColor4f(1.0f, 1.0f, 1.0f, 0.7f);

      // Enable texturing
      if(mTexHandle)
      {
        glBindTexture(GL_TEXTURE_2D, mTexHandle);
        glEnable(GL_TEXTURE_2D);
      }

      // Enable blending
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

      // Draw the icon as a textured quad
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 0.0f);
      glVertex2i(mPosX, mPosY);
      glTexCoord2f(1.0f, 0.0f);
      glVertex2i(mPosX + mWidth, mPosY);
      glTexCoord2f(1.0f, 1.0f);
      glVertex2i(mPosX + mWidth, mPosY + mHeight);
      glTexCoord2f(0.0f, 1.0f);
      glVertex2i(mPosX, mPosY + mHeight);
      glEnd();

      // We're done
      glDisable(GL_BLEND);
      glDisable(GL_TEXTURE_2D);
    }

    /// Mouse move function. The function returns true if the state of the
    /// button has changed.
    bool MouseMove(int x, int y)
    {
      bool hit = (x >= mPosX) && (x < (mPosX + mWidth)) &&
                 (y >= mPosY) && (y < (mPosY + mHeight));
      bool changed = (mHighlight != hit);
      mHighlight = hit;
      return changed;
    }

    /// Mouse click function.
    bool MouseClick(int aState, int x, int y)
    {
      bool hit = (x >= mPosX) && (x < (mPosX + mWidth)) &&
                 (y >= mPosY) && (y < (mPosY + mHeight));
      if(hit && (aState == GLUT_DOWN))
        DoAction();
      return hit;
    }

    /// The action function that will be performed when a button is clicked.
    virtual void DoAction() {}

    GLint mPosX, mPosY;
    GLint mWidth, mHeight;
    GLViewer * mParent;
};


//-----------------------------------------------------------------------------
// Customized button classes (implementing different actions)
//-----------------------------------------------------------------------------

class OpenButton: public GLButton {
  public:
    void DoAction()
    {
      if(!mParent)
        return;
      mParent->ActionOpenFile();
    }
};

class SaveButton: public GLButton {
  public:
    void DoAction()
    {
      if(!mParent)
        return;
      mParent->ActionSaveFile();
    }
};

class OpenTextureButton: public GLButton {
  public:
    void DoAction()
    {
      if(!mParent)
        return;
      mParent->ActionOpenTexture();
    }
};

class HelpButton: public GLButton {
  public:
    void DoAction()
    {
      if(!mParent)
        return;
      mParent->ActionHelp();
    }
};


//-----------------------------------------------------------------------------
// GLUT callback function prototypes
//-----------------------------------------------------------------------------

void GLUTWindowRedraw(void);
void GLUTWindowResize(int w, int h);
void GLUTMouseClick(int button, int state, int x, int y);
void GLUTMouseMove(int x, int y);
void GLUTKeyDown(unsigned char key, int x, int y);
void GLUTSpecialKeyDown(int key, int x, int y);


//-----------------------------------------------------------------------------
// GLViewer: OpenGL related functions
//-----------------------------------------------------------------------------

/// Set up the camera.
void GLViewer::SetupCamera()
{
  if(mMesh)
    mMesh->BoundingBox(mAABBMin, mAABBMax);
  else
  {
    mAABBMin = Vector3(-1.0f, -1.0f, -1.0f);
    mAABBMax = Vector3(1.0f, 1.0f, 1.0f);
  }
  mCameraLookAt = (mAABBMax + mAABBMin) * 0.5f;
  float delta = (mAABBMax - mAABBMin).Abs();
  if(mCameraUp.z > 0.0f)
    mCameraPosition = Vector3(mCameraLookAt.x,
                              mCameraLookAt.y - 0.8f * delta,
                              mCameraLookAt.z + 0.2f * delta);
  else
    mCameraPosition = Vector3(mCameraLookAt.x,
                              mCameraLookAt.y + 0.2f * delta,
                              mCameraLookAt.z + 0.8f * delta);
}

/// Initialize the GLSL shader (requires OpenGL 2.0 or better).
void GLViewer::InitShader()
{
  const GLchar * src[1];

  // Load vertex shader
  mVertShader = glCreateShader(GL_VERTEX_SHADER);
  src[0] = (const GLchar *) phongVertSrc;
  glShaderSource(mVertShader, 1, src, NULL);

  // Load fragment shader
  mFragShader = glCreateShader(GL_FRAGMENT_SHADER);	
  src[0] = (const GLchar *) phongFragSrc;
  glShaderSource(mFragShader, 1, src, NULL);

  int status;

  // Compile the vertex shader
  glCompileShader(mVertShader);
  glGetShaderiv(mVertShader, GL_COMPILE_STATUS, &status);
  if(!status)
    throw runtime_error("Could not compile vertex shader.");

  // Compile the fragment shader
  glCompileShader(mFragShader);
  glGetShaderiv(mFragShader, GL_COMPILE_STATUS, &status);
  if(!status)
    throw runtime_error("Could not compile fragment shader.");

  // Link the shader program
  mShaderProgram = glCreateProgram();
  glAttachShader(mShaderProgram, mVertShader);
  glAttachShader(mShaderProgram, mFragShader);
  glLinkProgram(mShaderProgram);
  glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);
  if(!status)
    throw runtime_error("Could not link shader program.");

  mUseShader = true;
}

/// Initialize the texture.
void GLViewer::InitTexture(const char * aFileName)
{
  Image image;

  // Load texture from a file
  if(aFileName)
  {
    // Check if file exists, and determine actual file name (relative or absolute)
    bool fileExists = false;
    string name = string(aFileName);
    FILE * inFile = fopen(name.c_str(), "rb");
    if(inFile)
      fileExists = true;
    else if(mFilePath.size() > 0)
    {
      // Try the same path as the mesh file
      name = mFilePath + string(aFileName);
      inFile = fopen(name.c_str(), "rb");
      if(inFile)
        fileExists = true;
    }
    if(inFile)
      fclose(inFile);

    if(fileExists)
    {
      cout << "Loading texture (" << aFileName << ")..." << endl;
      try
      {
        image.LoadFromFile(name.c_str());
      }
      catch(exception &e)
      {
        cout << "Error loading texture: " << e.what() << endl;
        image.Clear();
      }
    }
  }

  // If no texture was loaded
  if(image.IsEmpty())
  {
    cout << "Loading texture (dummy)..." << endl;

    // Create a default, synthetic texture
    image.SetSize(256, 256, 1);
    for(int y = 0; y < image.mHeight; ++ y)
    {
      for(int x = 0; x < image.mWidth; ++ x)
      {
        if(((x & 0x000f) == 0) || ((y & 0x000f) == 0))
          image.mData[y * image.mWidth + x] = 192;
        else
          image.mData[y * image.mWidth + x] = 255;
      }
    }
  }

  // Upload the texture to OpenGL
  if(!image.IsEmpty())
    glGenTextures(1, &mTexHandle);
  else
    mTexHandle = 0;
  if(mTexHandle)
  {
    // Determine the color format
    GLuint format;
    if(image.mComponents == 3)
      format = GL_RGB;
    else if(image.mComponents == 4)
      format = GL_RGBA;
    else
      format = GL_LUMINANCE;

    glBindTexture(GL_TEXTURE_2D, mTexHandle);

    if(GLEW_VERSION_1_4)
    {
      // Generate mipmaps automatically and use them
      glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    }
    else
    {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, image.mComponents, image.mWidth, image.mHeight, 0, format, GL_UNSIGNED_BYTE, (GLvoid *) &image.mData[0]);
  }
}

/// Set up the scene lighting.
void GLViewer::SetupLighting()
{
  GLfloat pos[4], ambient[4], diffuse[4], specular[4];

  // Set scene lighting properties
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  ambient[0] = 0.2;
  ambient[1] = 0.2;
  ambient[2] = 0.2;
  ambient[3] = 1.0;
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

  // Set-up head light (GL_LIGHT0)
  pos[0] = mCameraPosition.x;
  pos[1] = mCameraPosition.y;
  pos[2] = mCameraPosition.z;
  pos[3] = 1.0f;
  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  ambient[0] = 0.0f;
  ambient[1] = 0.0f;
  ambient[2] = 0.0f;
  ambient[3] = 1.0f;
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  diffuse[0] = 0.8f;
  diffuse[1] = 0.8f;
  diffuse[2] = 0.8f;
  diffuse[3] = 1.0f;
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  specular[0] = 1.0f;
  specular[1] = 1.0f;
  specular[2] = 1.0f;
  specular[3] = 1.0f;
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
  glEnable(GL_LIGHT0);
}

/// Set up the material.
void GLViewer::SetupMaterial()
{
  GLfloat specular[4], emission[4];

  // Set up the material
  specular[0] = 0.3f;
  specular[1] = 0.3f;
  specular[2] = 0.3f;
  specular[3] = 1.0f;
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  emission[0] = 0.0f;
  emission[1] = 0.0f;
  emission[2] = 0.0f;
  emission[3] = 1.0f;
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 40.0f);

  // Use color material for the diffuse and ambient components
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
}

/// Draw a mesh
void GLViewer::DrawMesh(Mesh * aMesh)
{
  // We always have vertices
  glVertexPointer(3, GL_FLOAT, 0, &aMesh->mVertices[0]);
  glEnableClientState(GL_VERTEX_ARRAY);

  // Do we have normals?
  if(aMesh->mNormals.size() == aMesh->mVertices.size())
  {
    glNormalPointer(GL_FLOAT, 0, &aMesh->mNormals[0]);
    glEnableClientState(GL_NORMAL_ARRAY);
  }

  // Do we have texture coordinates?
  if(aMesh->mTexCoords.size() == aMesh->mVertices.size())
  {
    glTexCoordPointer(2, GL_FLOAT, 0, &aMesh->mTexCoords[0]);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  }

  // Do we have colors?
  if(aMesh->mColors.size() == aMesh->mVertices.size())
  {
    glColorPointer(4, GL_FLOAT, 0, &aMesh->mColors[0]);
    glEnableClientState(GL_COLOR_ARRAY);
  }

  // Use glDrawElements to draw the triangles...
  glShadeModel(GL_SMOOTH);
  if(GLEW_VERSION_1_2)
    glDrawRangeElements(GL_TRIANGLES, 0, aMesh->mVertices.size() - 1,
                        aMesh->mIndices.size(), GL_UNSIGNED_INT,
                        &aMesh->mIndices[0]);
  else
    glDrawElements(GL_TRIANGLES, aMesh->mIndices.size(), GL_UNSIGNED_INT,
                   &aMesh->mIndices[0]);

  // We do not use the client state anymore...
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
}

// Load a file to the mesh
void GLViewer::LoadFile(const char * aFileName, const char * aOverrideTexture)
{
  // Get the file size
  ifstream f(aFileName, ios::in | ios::binary);
  if(f.fail())
    throw runtime_error("Unable to open the file.");
  f.seekg(0, ios_base::end);
  long tmpFileSize = (long) f.tellg();
  f.close();

  // Load the mesh
  cout << "Loading " << aFileName << "..." << flush;
  mTimer.Push();
  Mesh * newMesh = new Mesh();
  try
  {
    ImportMesh(aFileName, newMesh);
  }
  catch(exception &e)
  {
    delete newMesh;
    throw;
  }
  if(mMesh)
    delete mMesh;
  mMesh = newMesh;
  cout << "done (" << int(mTimer.PopDelta() * 1000.0 + 0.5) << " ms)" << endl;

  // Get the file name (excluding the path), and the path (excluding the file name)
  mFileName = ExtractFileName(string(aFileName));
  mFilePath = ExtractFilePath(string(aFileName));

  // The temporary file size is now the official file size...
  mFileSize = tmpFileSize;

  // Set window title
  string windowCaption = string("OpenCTM viewer - ") + mFileName;
  glutSetWindowTitle(windowCaption.c_str());

  // If the file did not contain any normals, calculate them now...
  if(mMesh->mNormals.size() != mMesh->mVertices.size())
  {
    cout << "Calculating normals..." << flush;
    mTimer.Push();
    mMesh->CalculateNormals();
    cout << "done (" << int(mTimer.PopDelta() * 1000.0 + 0.5) << " ms)" << endl;
  }

  // Load the texture
  if(mTexHandle)
    glDeleteTextures(1, &mTexHandle);
  mTexHandle = 0;
  if(mMesh->mTexCoords.size() == mMesh->mVertices.size())
  {
    string texFileName = mMesh->mTexFileName;
    if(aOverrideTexture)
      texFileName = string(aOverrideTexture);
    if(texFileName.size() > 0)
      InitTexture(texFileName.c_str());
    else
      InitTexture(0);
  }

  // Setup texture parameters for the shader
  if(mUseShader)
  {
    glUseProgram(mShaderProgram);

    // Set the uUseTexture uniform
    GLint useTexLoc = glGetUniformLocation(mShaderProgram, "uUseTexture");
    if(useTexLoc >= 0)
      glUniform1i(useTexLoc, glIsTexture(mTexHandle));

    // Set the uTex uniform
    GLint texLoc = glGetUniformLocation(mShaderProgram, "uTex");
    if(texLoc >= 0)
      glUniform1i(texLoc, 0);

    glUseProgram(0);
  }

  // Load the mesh into a displaylist
  if(mDisplayList)
    glDeleteLists(mDisplayList, 1);
  mDisplayList = glGenLists(1);
  glNewList(mDisplayList, GL_COMPILE);
  DrawMesh(mMesh);
  glEndList();

  // Init the camera for the new mesh
  mCameraUp = Vector3(0.0f, 0.0f, 1.0f);
  SetupCamera();
}

// Load a texture file
void GLViewer::LoadTexture(const char * aFileName)
{
  // Load the texture
  if(mTexHandle)
    glDeleteTextures(1, &mTexHandle);
  mTexHandle = 0;
  if(mMesh->mTexCoords.size() == mMesh->mVertices.size())
    InitTexture(aFileName);

  // Setup texture parameters for the shader
  if(mUseShader)
  {
    glUseProgram(mShaderProgram);

    // Set the uUseTexture uniform
    GLint useTexLoc = glGetUniformLocation(mShaderProgram, "uUseTexture");
    if(useTexLoc >= 0)
      glUniform1i(useTexLoc, glIsTexture(mTexHandle));

    // Set the uTex uniform
    GLint texLoc = glGetUniformLocation(mShaderProgram, "uTex");
    if(texLoc >= 0)
      glUniform1i(texLoc, 0);

    glUseProgram(0);
  }
}

// Draw an outline box.
void GLViewer::DrawOutlineBox(int x1, int y1, int x2, int y2,
  float r, float g, float b, float a)
{
  // Draw a blended box
  // Note: We add (1,1) to the (x2,y2) corner to cover the entire pixel range
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBegin(GL_QUADS);
  glColor4f(r, g, b, 0.7f * a);
  glVertex2i(x1, y1);
  glVertex2i(x2+1, y1);
  glColor4f(r, g, b, 0.7f * a + 0.3f);
  glVertex2i(x2+1, y2+1);
  glVertex2i(x1, y2+1);
  glEnd();
  glDisable(GL_BLEND);

  // Draw a solid outline
  glPushMatrix();
  glTranslatef(0.5f, 0.5f, 0.0f);  // Compensate for 0.5 pixel center offset
  glColor4f(r, g, b, 1.0f);
  glBegin(GL_LINE_LOOP);
  glVertex2i(x1, y1-1);
  glVertex2i(x2, y1-1);
  glVertex2i(x2+1, y1);
  glVertex2i(x2+1, y2);
  glVertex2i(x2, y2+1);
  glVertex2i(x1, y2+1);
  glVertex2i(x1-1, y2);
  glVertex2i(x1-1, y1);
  glEnd();
  glPopMatrix();
}

// Draw a string using GLUT. The string is shown on top of an alpha-blended
// quad.
void GLViewer::DrawString(string aString, int x, int y)
{
  // Calculate the size of the string box
  int x0 = x, y0 = y;
  int x1 = x0, y1 = y0;
  int x2 = x0, y2 = y0;
  for(unsigned int i = 0; i < aString.size(); ++ i)
  {
    int c = (int) aString[i];
    if(c == (int) 10)
    {
      x2 = x;
      y2 += 13;
    }
    else if(c != (int) 13)
    {
      x2 += glutBitmapWidth(GLUT_BITMAP_8_BY_13, c);
      if(x2 > x1) x1 = x2;
    }
  }
  y1 = y2 + 13;

  // Draw a alpha blended box
  DrawOutlineBox(x0-4, y0-3, x1+4, y1+4, 0.3f, 0.3f, 0.3f, 0.6f);

  // Print the text
  glColor3f(1.0f, 1.0f, 1.0f);
  x2 = x;
  y2 = y + 13;
  for(unsigned int i = 0; i < aString.size(); ++ i)
  {
    int c = (int) aString[i];
    if(c == (int) 10)
    {
      x2 = x;
      y2 += 13;
    }
    else if(c != (int) 13)
    {
      glRasterPos2i(x2, y2);
      glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
      x2 += glutBitmapWidth(GLUT_BITMAP_8_BY_13, c);
    }
  }
}

// Draw 2D overlay
void GLViewer::Draw2DOverlay()
{
  // Setup the matrices for a width x height 2D screen
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, (double) mWidth, (double) mHeight, 0.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Setup the rendering pipeline for 2D rendering
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);

  // Render an info string
  if(mMesh)
  {
    stringstream s;
    s << mFileName << " (" << (mFileSize + 512) / 1024 << "KB)" << endl;
    s << mMesh->mVertices.size() << " vertices" << endl;
    s << mMesh->mIndices.size() / 3 << " triangles";
    DrawString(s.str(), 10, mHeight - 50);
  }

  // Calculate buttons bounding box, and draw it as an outline box
  int x1 = 9999, y1 = 9999, x2 = 0, y2 = 0;
  for(list<GLButton *>::iterator b = mButtons.begin(); b != mButtons.end(); ++ b)
  {
    if((*b)->mPosX < x1) x1 = (*b)->mPosX;
    if(((*b)->mPosX + (*b)->mWidth) > x2) x2 = (*b)->mPosX + (*b)->mWidth;
    if((*b)->mPosY < y1) y1 = (*b)->mPosY;
    if(((*b)->mPosY + (*b)->mHeight) > y2) y2 = (*b)->mPosY + (*b)->mHeight;
  }
  DrawOutlineBox(x1-5, y1-5, x2+5, y2+5, 0.3f, 0.3f, 0.3f, 0.6f);

  // Render all the buttons (last = on top)
  for(list<GLButton *>::iterator b = mButtons.begin(); b != mButtons.end(); ++ b)
    (*b)->Redraw();
}

/// Get 3D coordinate under the mouse cursor.
bool GLViewer::WinCoordTo3DCoord(int x, int y, Vector3 &aPoint)
{
  // Read back the depth value at at (x, y)
  GLfloat z = 0.0f;
  glReadPixels(x,  mHeight - y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, (GLvoid *) &z);
  if((z > 0.0f) && (z < 1.0f))
  {
    // Convert the window coordinate to space coordinates
    GLdouble objX, objY, objZ;
    gluUnProject((GLdouble) x, (GLdouble) (mHeight - y), (GLdouble) z,
                 mModelviewMatrix, mProjectionMatrix, mViewport,
                 &objX, &objY, &objZ);
    aPoint = Vector3((float) objX, (float) objY, (float) objZ);
    return true;
  }
  else
    return false;
}

/// Update the focus position of the camera.
void GLViewer::UpdateFocus()
{
  double w = (mTimer.GetTime() - mFocusStartTime) / (mFocusEndTime - mFocusStartTime);
  Vector3 dir = Normalize(mCameraPosition - mCameraLookAt);
  if(w < 1.0)
  {
    w = pow(w, 0.2);
    mCameraLookAt = mFocusStartPos + (mFocusEndPos - mFocusStartPos) * w;
    mCameraPosition = mCameraLookAt + dir * (mFocusStartDistance + (mFocusEndDistance - mFocusStartDistance) * w);
  }
  else
  {
    mCameraLookAt = mFocusEndPos;
    mCameraPosition = mCameraLookAt + dir * mFocusEndDistance;
    mFocusing = false;
  }
  glutPostRedisplay();
}


//-----------------------------------------------------------------------------
// Actions (user activated functions)
//-----------------------------------------------------------------------------

/// Open another file
void GLViewer::ActionOpenFile()
{
  SysOpenDialog od;
  od.mFilters.push_back(string("All supported 3D files|*.ctm;*.ply;*.stl;*.3ds;*.dae;*.obj;*.lwo;*.off"));
  od.mFilters.push_back(string("OpenCTM (.ctm)|*.ctm"));
  od.mFilters.push_back(string("Stanford triangle format (.ply)|*.ply"));
  od.mFilters.push_back(string("Stereolitography (.stl)|*.stl"));
  od.mFilters.push_back(string("3D Studio (.3ds)|*.3ds"));
  od.mFilters.push_back(string("COLLADA (.dae)|*.dae"));
  od.mFilters.push_back(string("Wavefront geometry file (.obj)|*.obj"));
  od.mFilters.push_back(string("LightWave object (.lwo)|*.lwo"));
  od.mFilters.push_back(string("Geomview object file format (.off)|*.off"));
  if(od.Show())
  {
    try
    {
      LoadFile(od.mFileName.c_str(), NULL);
      glutPostRedisplay();
    }
    catch(exception &e)
    {
      SysMessageBox mb;
      mb.mMessageType = SysMessageBox::mtError;
      mb.mCaption = "Error";
      mb.mText = string(e.what());
      mb.Show();
    }
  }
}

/// Save the file
void GLViewer::ActionSaveFile()
{
  if(!mMesh)
  {
    SysMessageBox mb;
    mb.mMessageType = SysMessageBox::mtError;
    mb.mCaption = "Save File";
    mb.mText = string("No mesh has been loaded.");
    mb.Show();
    return;
  }

  SysSaveDialog sd;
  sd.mFilters.push_back(string("All files|*"));
  sd.mFilters.push_back(string("OpenCTM (.ctm)|*.ctm"));
  sd.mFilters.push_back(string("Stanford triangle format (.ply)|*.ply"));
  sd.mFilters.push_back(string("Stereolitography (.stl)|*.stl"));
  sd.mFilters.push_back(string("3D Studio (.3ds)|*.3ds"));
  sd.mFilters.push_back(string("COLLADA (.dae)|*.dae"));
  sd.mFilters.push_back(string("Wavefront geometry file (.obj)|*.obj"));
  sd.mFilters.push_back(string("LightWave object (.lwo)|*.lwo"));
  sd.mFilters.push_back(string("Geomview object file format (.off)|*.off"));
  sd.mFilters.push_back(string("VRML 2.0 (.wrl)|*.wrl"));
  sd.mFileName = mFileName;
  if(sd.Show())
  {
    try
    {
      Options opt;

      // Do not export normals that do not come from the original file
      if(!mMesh->mOriginalNormals)
        opt.mNoNormals = true;

      // Export the mesh
      ExportMesh(sd.mFileName.c_str(), mMesh, opt);
    }
    catch(exception &e)
    {
      SysMessageBox mb;
      mb.mMessageType = SysMessageBox::mtError;
      mb.mCaption = "Error";
      mb.mText = string(e.what());
      mb.Show();
    }
  }
}

/// Open a texture file
void GLViewer::ActionOpenTexture()
{
  if(!mMesh || (mMesh->mTexCoords.size() < 1))
  {
    SysMessageBox mb;
    mb.mMessageType = SysMessageBox::mtError;
    mb.mCaption = "Open Texture File";
    mb.mText = string("This mesh does not have any texture coordinates.");
    mb.Show();
    return;
  }

  SysOpenDialog od;
  od.mCaption = string("Open Texture File");
  od.mFilters.push_back(string("All supported texture files|*.jpg;*.jpeg;*.png"));
  od.mFilters.push_back(string("JPEG|*.jpg;*.jpeg"));
  od.mFilters.push_back(string("PNG|*.png"));
  if(od.Show())
  {
    try
    {
      LoadTexture(od.mFileName.c_str());
      mMesh->mTexFileName = ExtractFileName(od.mFileName);
      glutPostRedisplay();
    }
    catch(exception &e)
    {
      SysMessageBox mb;
      mb.mMessageType = SysMessageBox::mtError;
      mb.mCaption = "Error";
      mb.mText = string(e.what());
      mb.Show();
    }
  }
}

/// Toggle wire frame view on/off
void GLViewer::ActionToggleWireframe()
{
  if(mPolyMode == GL_LINE)
    mPolyMode = GL_FILL;
  else
    mPolyMode = GL_LINE;
  glutPostRedisplay();
}

/// Fit model to the screen (re-focus)
void GLViewer::ActionFitToScreen()
{
  double now = mTimer.GetTime();
  mFocusStartTime = now;
  mFocusEndTime = now + FOCUS_TIME;
  mFocusStartPos = mCameraLookAt;
  mFocusStartDistance = (mCameraLookAt - mCameraPosition).Abs();
  mFocusEndPos = (mAABBMax + mAABBMin) * 0.5f;
  mFocusEndDistance = 0.825 * (mAABBMax - mAABBMin).Abs();
  mFocusing = true;
  UpdateFocus();
  glutPostRedisplay();
}

/// Set camera up direction to Y
void GLViewer::ActionCameraUpY()
{
  mCameraUp = Vector3(0.0f, 1.0f, 0.0f);
  SetupCamera();
  glutPostRedisplay();
}

/// Set camera up direction to Z
void GLViewer::ActionCameraUpZ()
{
  mCameraUp = Vector3(0.0f, 0.0f, 1.0f);
  SetupCamera();
  glutPostRedisplay();
}

/// Zoom camera one step in
void GLViewer::ActionZoomIn()
{
  double now = mTimer.GetTime();
  mFocusStartTime = now;
  mFocusEndTime = now + FOCUS_TIME;
  mFocusStartPos = mCameraLookAt;
  mFocusStartDistance = (mCameraLookAt - mCameraPosition).Abs();
  mFocusEndPos = mCameraLookAt;
  mFocusEndDistance = (1.0/1.5) * mFocusStartDistance;
  mFocusing = true;
  UpdateFocus();
  glutPostRedisplay();
}

/// Zoom camera one step out
void GLViewer::ActionZoomOut()
{
  double now = mTimer.GetTime();
  mFocusStartTime = now;
  mFocusEndTime = now + FOCUS_TIME;
  mFocusStartPos = mCameraLookAt;
  mFocusStartDistance = (mCameraLookAt - mCameraPosition).Abs();
  mFocusEndPos = mCameraLookAt;
  mFocusEndDistance = 1.5 * mFocusStartDistance;
  mFocusing = true;
  UpdateFocus();
  glutPostRedisplay();
}

/// Exit program
void GLViewer::ActionExit()
{
  // Note: In freeglut you can do glutLeaveMainLoop(), which is more graceful
  exit(0);
}

/// Show a help dialog
void GLViewer::ActionHelp()
{
  stringstream helpText;
  helpText << "ctmviewer - OpenCTM file viewer" << endl;
  helpText << "Copyright (c) 2009-2010 Marcus Geelnard" << endl << endl;
  helpText << "Keyboard actions:" << endl;
  helpText << "  W - Toggle wire frame view on/off" << endl;
  helpText << "  F - Fit model to the screen" << endl;
  helpText << "  Y - Set Y as the up axis (change camera view)" << endl;
  helpText << "  Z - Set Z as the up axis (change camera view)" << endl;
  helpText << "  +/- - Zoom in/out with the camera" << endl;
  helpText << "  ESC - Exit program" << endl << endl;
  helpText << "Mouse control:" << endl;
  helpText << "  Left button - Rotate camera" << endl;
  helpText << "  Middle button or wheel - Zoom camera" << endl;
  helpText << "  Right button - Pan camera" << endl;
  helpText << "  Double click - Focus on indicated surface";

  SysMessageBox mb;
  mb.mMessageType = SysMessageBox::mtInformation;
  mb.mCaption = "Help";
  mb.mText = helpText.str();
  mb.Show();
}


//-----------------------------------------------------------------------------
// GLUT callback functions
//-----------------------------------------------------------------------------

/// Redraw function.
void GLViewer::WindowRedraw(void)
{
  // Get buffer properties
  glGetIntegerv(GL_DEPTH_BITS, &mDepthBufferResolution);

  // Set the viewport to be the entire window
  glViewport(0, 0, mWidth, mHeight);

  // Clear the buffer(s)
  glClear(GL_DEPTH_BUFFER_BIT);

  // Draw a gradient background
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glBegin(GL_QUADS);
  glColor3f(0.4f, 0.5f, 0.7f);
  glVertex3f(-1.0f, -1.0f, 0.5f);
  glColor3f(0.3f, 0.4f, 0.7f);
  glVertex3f(1.0f, -1.0f, 0.5f);
  glColor3f(0.1f, 0.1f, 0.2f);
  glVertex3f(1.0f, 1.0f, 0.5f);
  glColor3f(0.1f, 0.15f, 0.24f);
  glVertex3f(-1.0f, 1.0f, 0.5f);
  glEnd();

  // Calculate screen ratio (width / height)
  float ratio;
  if(mHeight == 0)
    ratio = 1.0f;
  else
    ratio = (float) mWidth / (float) mHeight;

  // Calculate optimal near and far Z clipping planes
  float farZ = (mAABBMax - mAABBMin).Abs() +
               (mCameraPosition - mCameraLookAt).Abs();
  if(farZ < 1e-20f)
    farZ = 1e-20f;
  float nearZ;
  if(mDepthBufferResolution >= 24)
    nearZ = 0.0001f * farZ;
  else
    nearZ = 0.01f * farZ;

  // Set up perspective projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0f, ratio, nearZ, farZ);

  // Set up the camera modelview matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(mCameraPosition.x, mCameraPosition.y, mCameraPosition.z,
            mCameraLookAt.x, mCameraLookAt.y, mCameraLookAt.z,
            mCameraUp.x, mCameraUp.y, mCameraUp.z);

  // Read back camera matrices
  glGetDoublev(GL_MODELVIEW_MATRIX, mModelviewMatrix);
  glGetDoublev(GL_PROJECTION_MATRIX, mProjectionMatrix);
  glGetIntegerv(GL_VIEWPORT, mViewport);

  // Set up the lights
  SetupLighting();

  // Enable material shader
  if(mUseShader)
    glUseProgram(mShaderProgram);
  else
    glEnable(GL_LIGHTING);

  // Draw the mesh
  SetupMaterial();
  glEnable(GL_DEPTH_TEST);
  glPolygonMode(GL_FRONT_AND_BACK, mPolyMode);
  if(mTexHandle)
  {
    glBindTexture(GL_TEXTURE_2D, mTexHandle);
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);
  }
  else
    glColor3f(0.9f, 0.86f, 0.7f);
  if(mDisplayList)
    glCallList(mDisplayList);
  glDisable(GL_TEXTURE_2D);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  // Disable material shader
  if(mUseShader)
    glUseProgram(0);
  else
    glDisable(GL_LIGHTING);

  // Draw 2D overlay (information text etc)
  Draw2DOverlay();

  // Swap buffers
  glutSwapBuffers();

  // Focusing?
  if(mFocusing)
  {
    UpdateFocus();
    glutPostRedisplay();
  }
}

/// Resize function.
void GLViewer::WindowResize(int w, int h)
{
  // Store the new window size
  mWidth = w;
  mHeight = h;
}

/// Mouse click function
void GLViewer::MouseClick(int button, int state, int x, int y)
{
  bool clickConsumed = false;
  if(button == GLUT_LEFT_BUTTON)
  {
    // Check if any of the GUI buttons were clicked
    for(list<GLButton *>::iterator b = mButtons.begin(); b != mButtons.end(); ++ b)
    {
      if((*b)->MouseClick(state, x, y))
        clickConsumed = true;
    }
    if(!clickConsumed)
    {
      if(state == GLUT_DOWN)
      {
        double now = mTimer.GetTime();
        if((now - mLastClickTime) < DOUBLE_CLICK_TIME)
        {
          // Double click occured
          Vector3 mouseCoord3D;
          if(WinCoordTo3DCoord(x, y, mouseCoord3D))
          {
            mFocusStartTime = now;
            mFocusEndTime = now + FOCUS_TIME;
            mFocusStartPos = mCameraLookAt;
            mFocusEndPos = mouseCoord3D;
            mFocusStartDistance = (mCameraLookAt - mCameraPosition).Abs();
            mFocusEndDistance = mFocusStartDistance;
            mFocusing = true;
          }
          mLastClickTime = -1000.0;
        }
        else
        {
          // Single click occured
          mMouseRotate = true;
          mLastClickTime = now;
        }
      }
      else if(state == GLUT_UP)
        mMouseRotate = false;
    }
  }
  else if(button == GLUT_MIDDLE_BUTTON)
  {
    if(state == GLUT_DOWN)
      mMouseZoom = true;
    else if(state == GLUT_UP)
      mMouseZoom = false;
  }
  else if(button == GLUT_RIGHT_BUTTON)
  {
    if(state == GLUT_DOWN)
      mMousePan = true;
    else if(state == GLUT_UP)
      mMousePan = false;
  }
  else if(button == 3) // Mouse wheel up on some systems
  {
    if(state == GLUT_DOWN)
      ActionZoomIn();
  }
  else if(button == 4) // Mouse wheel down on some systems
  {
    if(state == GLUT_DOWN)
      ActionZoomOut();
  }
  mOldMouseX = x;
  mOldMouseY = y;

  // Focusing?
  if(mFocusing)
  {
    UpdateFocus();
    glutPostRedisplay();
  }
}

/// Mouse move function
void GLViewer::MouseMove(int x, int y)
{
  bool needsRedraw = false;

  float deltaX = (float) x - (float) mOldMouseX;
  float deltaY = (float) y - (float) mOldMouseY;
  mOldMouseX = x;
  mOldMouseY = y;

  if(mMouseRotate)
  {
    // Calculate delta angles
    float scale = 3.0f;
    if(mHeight > 0)
      scale /= (float) mHeight;
    float deltaTheta = -scale * deltaX;
    float deltaPhi = -scale * deltaY;

    // Adjust camera angles
    Vector3 viewVector = mCameraPosition - mCameraLookAt;
    float r = sqrtf(viewVector.x * viewVector.x +
                    viewVector.y * viewVector.y +
                    viewVector.z * viewVector.z);
    float phi, theta;
    if(r > 1e-20f)
    {
      if(mCameraUp.z > 0.0f)
      {
        phi = acosf(viewVector.z / r);
        theta = atan2f(viewVector.y, viewVector.x);
      }
      else
      {
        phi = acosf(viewVector.y / r);
        theta = atan2f(-viewVector.z, viewVector.x);
      }
    }
    else
    {
      if(mCameraUp.z > 0.0f)
        phi = viewVector.z > 0.0f ? 0.05f * PI : 0.95f * PI;
      else
        phi = viewVector.y > 0.0f ? 0.05f * PI : 0.95f * PI;
      theta = 0.0f;
    }
    phi += deltaPhi;
    theta += deltaTheta;
    if(phi > (0.95f * PI))
      phi = 0.95f * PI;
    else if(phi < (0.05f * PI))
      phi = 0.05f * PI;

    // Update the camera position
    if(mCameraUp.z > 0.0f)
    {
      viewVector.x = r * cos(theta) * sin(phi);
      viewVector.y = r * sin(theta) * sin(phi);
      viewVector.z = r * cos(phi);
    }
    else
    {
      viewVector.x = r * cos(theta) * sin(phi);
      viewVector.y = r * cos(phi);
      viewVector.z = -r * sin(theta) * sin(phi);
    }
    mCameraPosition = mCameraLookAt + viewVector;

    needsRedraw = true;
  }
  else if(mMouseZoom)
  {
    // Calculate delta angles
    float scale = 3.0f;
    if(mHeight > 0)
      scale /= (float) mHeight;
    float zoom = scale * deltaY;

    // Adjust camera zoom
    Vector3 viewVector = mCameraPosition - mCameraLookAt;
    viewVector = viewVector * powf(2.0f, zoom);

    // Update the camera position
    mCameraPosition = mCameraLookAt + viewVector;

    needsRedraw = true;
  }
  else if(mMousePan)
  {
    // Calculate delta movement
    float scale = 1.0f * (mCameraPosition - mCameraLookAt).Abs();
    if(mHeight > 0)
      scale /= (float) mHeight;
    float panX = scale * deltaX;
    float panY = scale * deltaY;

    // Calculate camera movement
    Vector3 viewDir = Normalize(mCameraPosition - mCameraLookAt);
    Vector3 rightDir = Normalize(Cross(viewDir, mCameraUp));
    Vector3 upDir = Normalize(Cross(rightDir, viewDir));
    Vector3 moveDelta = rightDir * panX + upDir * panY;

    // Update the camera position
    mCameraPosition += moveDelta;
    mCameraLookAt += moveDelta;

    needsRedraw = true;
  }
  else
  {
    // Call mouse move for all the GUI buttons
    for(list<GLButton *>::iterator b = mButtons.begin(); b != mButtons.end(); ++ b)
    {
      if((*b)->MouseMove(x, y))
        needsRedraw = true;
    }
  }

  // Redraw?
  if(needsRedraw)
    glutPostRedisplay();
}

/// Keyboard function
void GLViewer::KeyDown(unsigned char key, int x, int y)
{
  if(key == 15)       // CTRL+O
    ActionOpenFile();
  else if(key == 19)  // CTRL+S
    ActionSaveFile();
  else if(key == 'w')
    ActionToggleWireframe();
  else if(key == 'f')
    ActionFitToScreen();
  else if(key == 'y')
    ActionCameraUpY();
  else if(key == 'z')
    ActionCameraUpZ();
  else if(key == '+')
    ActionZoomIn();
  else if(key == '-')
    ActionZoomOut();
  else if(key == 27)  // ESC
    ActionExit();
}

/// Keyboard function (special keys)
void GLViewer::SpecialKeyDown(int key, int x, int y)
{
  if(key == GLUT_KEY_F1)
    ActionHelp();
}


//-----------------------------------------------------------------------------
// Application main code
//-----------------------------------------------------------------------------

/// Constructor
GLViewer::GLViewer()
{
  // Clear internal state
  mFileName = "";
  mFilePath = "";
  mFileSize = 0;
  mWidth = 1;
  mHeight = 1;
  mDepthBufferResolution = 16;
  mOldMouseX = 0;
  mOldMouseY = 0;
  mMouseRotate = false;
  mMouseZoom = false;
  mMousePan = false;
  mCameraUp = Vector3(0.0f, 0.0f, 1.0f);
  mFocusStartPos = Vector3(0.0f, 0.0f, 0.0f);
  mFocusEndPos = Vector3(0.0f, 0.0f, 0.0f);
  mFocusStartTime = 0.0;
  mFocusEndTime = 0.0;
  mFocusStartDistance = 1.0;
  mFocusEndDistance = 1.0;
  mFocusing = false;
  mLastClickTime = -1000.0;
  mDisplayList = 0;
  mPolyMode = GL_FILL;
  mTexHandle = 0;
  mUseShader = false;
  mShaderProgram = 0;
  mVertShader = 0;
  mFragShader = 0;
  mMesh = NULL;
}

/// Destructor
GLViewer::~GLViewer()
{
  // Free all GUI buttons
  for(list<GLButton *>::iterator b = mButtons.begin(); b != mButtons.end(); ++ b)
    delete (*b);

  // Free the mesh
  if(mMesh)
    delete mMesh;
}

/// Run the application
void GLViewer::Run(int argc, char **argv)
{
  try
  {
    // Init GLUT
    glutInit(&argc, argv);

    // Create the glut window
    glutInitWindowSize(640, 480);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("OpenCTM viewer");

    // Init GLEW (for OpenGL 2.x support)
    if(glewInit() != GLEW_OK)
      throw runtime_error("Unable to initialize GLEW.");

    // Load the phong shader, if we can
    if(GLEW_VERSION_2_0)
      InitShader();
    else if(GLEW_VERSION_1_2)
      glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

    // Set the GLUT callback functions (these are bridged to the corresponding
    // class methods)
    glutReshapeFunc(GLUTWindowResize);
    glutDisplayFunc(GLUTWindowRedraw);
    glutMouseFunc(GLUTMouseClick);
    glutMotionFunc(GLUTMouseMove);
    glutPassiveMotionFunc(GLUTMouseMove);
    glutKeyboardFunc(GLUTKeyDown);
    glutSpecialFunc(GLUTSpecialKeyDown);

    // Create GUI buttons
    GLButton * b1 = new OpenButton();
    mButtons.push_back(b1);
    b1->mParent = this;
    b1->SetGlyph(icon_open, 32, 32, 4);
    b1->mPosX = 12;
    b1->mPosY = 10;
    GLButton * b2 = new SaveButton();
    mButtons.push_back(b2);
    b2->mParent = this;
    b2->SetGlyph(icon_save, 32, 32, 4);
    b2->mPosX = 60;
    b2->mPosY = 10;
    GLButton * b3 = new OpenTextureButton();
    mButtons.push_back(b3);
    b3->mParent = this;
    b3->SetGlyph(icon_texture, 32, 32, 4);
    b3->mPosX = 108;
    b3->mPosY = 10;
    GLButton * b4 = new HelpButton();
    mButtons.push_back(b4);
    b4->mParent = this;
    b4->SetGlyph(icon_help, 32, 32, 4);
    b4->mPosX = 156;
    b4->mPosY = 10;

    // Load the file
    if(argc >= 2)
    {
      const char * overrideTexName = NULL;
      if(argc >= 3)
        overrideTexName = argv[2];
      LoadFile(argv[1], overrideTexName);
    }

    // Enter the main loop
    glutMainLoop();
  }
  catch(ctm_error &e)
  {
    SysMessageBox mb;
    mb.mMessageType = SysMessageBox::mtError;
    mb.mCaption = "Error";
    mb.mText = string("OpenCTM error: ") + string(e.what());
    mb.Show();
  }
  catch(exception &e)
  {
    SysMessageBox mb;
    mb.mMessageType = SysMessageBox::mtError;
    mb.mCaption = "Error";
    mb.mText = string(e.what());
    mb.Show();
  }
  cout << endl;
}


//-----------------------------------------------------------------------------
// Bridge GLUT callback functions to class methods
//-----------------------------------------------------------------------------

// NOTE: This is just a hack to be able to reference the application class
// object from the GLUT callback functions, since there is no way (afaik) to
// pass user data (i.e. the object reference) through GLUT...
static GLViewer * gGLViewer = NULL;

/// Redraw function.
void GLUTWindowRedraw(void)
{
  if(gGLViewer)
    gGLViewer->WindowRedraw();
}

/// Resize function.
void GLUTWindowResize(int w, int h)
{
  if(gGLViewer)
    gGLViewer->WindowResize(w, h);
}

/// Mouse click function
void GLUTMouseClick(int button, int state, int x, int y)
{
  if(gGLViewer)
    gGLViewer->MouseClick(button, state, x, y);
}

/// Mouse move function
void GLUTMouseMove(int x, int y)
{
  if(gGLViewer)
    gGLViewer->MouseMove(x, y);
}

/// Keyboard function
void GLUTKeyDown(unsigned char key, int x, int y)
{
  if(gGLViewer)
    gGLViewer->KeyDown(key, x, y);
}

/// Keyboard function (special keys)
void GLUTSpecialKeyDown(int key, int x, int y)
{
  if(gGLViewer)
    gGLViewer->SpecialKeyDown(key, x, y);
}


//-----------------------------------------------------------------------------
// Program startup
//-----------------------------------------------------------------------------

/// Program entry.
int main(int argc, char **argv)
{
  // Run the application class
  gGLViewer = new GLViewer;
  gGLViewer->Run(argc, argv);
  delete gGLViewer;
  gGLViewer = NULL;

  return 0;
}
