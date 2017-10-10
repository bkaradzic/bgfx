// ----------------------------------------------------------------------------
// Another Assimp OpenGL sample including texturing.
// Note that it is very basic and will only read and apply the model's diffuse
// textures (by their material ids)
//
// Don't worry about the "Couldn't load Image: ...dwarf2.jpg" Message.
// It's caused by a bad texture reference in the model file (I guess)
//
// If you intend to _use_ this code sample in your app, do yourself a favour
// and replace immediate mode calls with VBOs ...
//
// Thanks to NeHe on whose OpenGL tutorials this one's based on! :)
// http://nehe.gamedev.net/
// ----------------------------------------------------------------------------
#include <windows.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <IL/il.h>

#include <fstream>

//to map image filenames to textureIds
#include <string.h>
#include <map>


// assimp include files. These three are usually needed.
#include "assimp/Importer.hpp"	//OO version Header!
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "assimp/DefaultLogger.hpp"
#include "assimp/LogStream.hpp"


// The default hard-coded path. Can be overridden by supplying a path through the command line.
static std::string modelpath = "../../test/models/OBJ/spider.obj";


HGLRC		hRC=NULL;			// Permanent Rendering Context
HDC			hDC=NULL;			// Private GDI Device Context
HWND		hWnd=NULL;			// Holds Window Handle
HINSTANCE	hInstance;	// Holds The Instance Of The Application

bool		keys[256];			// Array used for Keyboard Routine;
bool		active=TRUE;		// Window Active Flag Set To TRUE by Default
bool		fullscreen=TRUE;	// full-screen Flag Set To full-screen By Default

GLfloat		xrot;
GLfloat		yrot;
GLfloat		zrot;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
GLboolean abortGLInit(const char*);

const char* windowTitle = "OpenGL Framework";

GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]= { 0.0f, 0.0f, 15.0f, 1.0f };



// the global Assimp scene object
const aiScene* scene = NULL;
GLuint scene_list = 0;
aiVector3D scene_min, scene_max, scene_center;

// images / texture
std::map<std::string, GLuint*> textureIdMap;	// map image filenames to textureIds
GLuint*		textureIds;							// pointer to texture Array

// Create an instance of the Importer class
Assimp::Importer importer;


void createAILogger()
{
    // Change this line to normal if you not want to analyse the import process
	//Assimp::Logger::LogSeverity severity = Assimp::Logger::NORMAL;
	Assimp::Logger::LogSeverity severity = Assimp::Logger::VERBOSE;

	// Create a logger instance for Console Output
	Assimp::DefaultLogger::create("",severity, aiDefaultLogStream_STDOUT);

	// Create a logger instance for File Output (found in project folder or near .exe)
	Assimp::DefaultLogger::create("assimp_log.txt",severity, aiDefaultLogStream_FILE);

	// Now I am ready for logging my stuff
	Assimp::DefaultLogger::get()->info("this is my info-call");
}

void destroyAILogger()
{
	// Kill it after the work is done
	Assimp::DefaultLogger::kill();
}

void logInfo(std::string logString)
{
	// Will add message to File with "info" Tag
	Assimp::DefaultLogger::get()->info(logString.c_str());
}

void logDebug(const char* logString)
{
	// Will add message to File with "debug" Tag
	Assimp::DefaultLogger::get()->debug(logString);
}


bool Import3DFromFile( const std::string& pFile)
{
	// Check if file exists
	std::ifstream fin(pFile.c_str());
	if(!fin.fail())
	{
		fin.close();
	}
	else
	{
		MessageBox(NULL, ("Couldn't open file: " + pFile).c_str() , "ERROR", MB_OK | MB_ICONEXCLAMATION);
		logInfo( importer.GetErrorString());
		return false;
	}

	scene = importer.ReadFile( pFile, aiProcessPreset_TargetRealtime_Quality);

	// If the import failed, report it
	if( !scene)
	{
		logInfo( importer.GetErrorString());
		return false;
	}

	// Now we can access the file's contents.
	logInfo("Import of scene " + pFile + " succeeded.");

	// We're done. Everything will be cleaned up by the importer destructor
	return true;
}

// Resize And Initialize The GL Window
void ReSizeGLScene(GLsizei width, GLsizei height)
{
    // Prevent A Divide By Zero By
	if (height==0)
	{
        // Making Height Equal One
        height=1;
	}

	glViewport(0, 0, width, height);					// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();							// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix
	glLoadIdentity();							// Reset The Modelview Matrix
}


std::string getBasePath(const std::string& path)
{
	size_t pos = path.find_last_of("\\/");
	return (std::string::npos == pos) ? "" : path.substr(0, pos + 1);
}

int LoadGLTextures(const aiScene* scene)
{
	ILboolean success;

	/* Before calling ilInit() version should be checked. */
	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
	{
		/// wrong DevIL version ///
		std::string err_msg = "Wrong DevIL version. Old devil.dll in system32/SysWow64?";
		char* cErr_msg = (char *) err_msg.c_str();
		abortGLInit(cErr_msg);
		return -1;
	}

	ilInit(); /* Initialization of DevIL */

	if (scene->HasTextures()) abortGLInit("Support for meshes with embedded textures is not implemented");

	/* getTexture Filenames and Numb of Textures */
	for (unsigned int m=0; m<scene->mNumMaterials; m++)
	{
		int texIndex = 0;
		aiReturn texFound = AI_SUCCESS;

		aiString path;	// filename

		while (texFound == AI_SUCCESS)
		{
			texFound = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
			textureIdMap[path.data] = NULL; //fill map with textures, pointers still NULL yet
			texIndex++;
		}
	}

	int numTextures = textureIdMap.size();

	/* array with DevIL image IDs */
	ILuint* imageIds = NULL;
	imageIds = new ILuint[numTextures];

	/* generate DevIL Image IDs */
	ilGenImages(numTextures, imageIds); /* Generation of numTextures image names */

	/* create and fill array with GL texture ids */
	textureIds = new GLuint[numTextures];
	glGenTextures(numTextures, textureIds); /* Texture name generation */

	/* get iterator */
	std::map<std::string, GLuint*>::iterator itr = textureIdMap.begin();

	std::string basepath = getBasePath(modelpath);
	for (int i=0; i<numTextures; i++)
	{

		//save IL image ID
		std::string filename = (*itr).first;  // get filename
		(*itr).second =  &textureIds[i];	  // save texture id for filename in map
		itr++;								  // next texture


		ilBindImage(imageIds[i]); /* Binding of DevIL image name */
		std::string fileloc = basepath + filename;	/* Loading of image */
		success = ilLoadImage(fileloc.c_str());

		if (success) /* If no error occurred: */
		{
            // Convert every colour component into unsigned byte.If your image contains
            // alpha channel you can replace IL_RGB with IL_RGBA
            success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
			if (!success)
			{
				/* Error occurred */
				abortGLInit("Couldn't convert image");
				return -1;
			}
            // Binding of texture name
            glBindTexture(GL_TEXTURE_2D, textureIds[i]);
			// redefine standard texture values
            // We will use linear interpolation for magnification filter
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
            // We will use linear interpolation for minifying filter
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            // Texture specification
            glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
				ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
				ilGetData());
            // we also want to be able to deal with odd texture dimensions
            glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
            glPixelStorei( GL_UNPACK_ROW_LENGTH, 0 );
            glPixelStorei( GL_UNPACK_SKIP_PIXELS, 0 );
            glPixelStorei( GL_UNPACK_SKIP_ROWS, 0 );
		}
		else
		{
			/* Error occurred */
			MessageBox(NULL, ("Couldn't load Image: " + fileloc).c_str() , "ERROR", MB_OK | MB_ICONEXCLAMATION);
		}
	}
    // Because we have already copied image data into texture data  we can release memory used by image.
	ilDeleteImages(numTextures, imageIds);

	// Cleanup
	delete [] imageIds;
	imageIds = NULL;

	return TRUE;
}

// All Setup For OpenGL goes here
int InitGL()
{
	if (!LoadGLTextures(scene))
	{
		return FALSE;
	}


	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);		 // Enables Smooth Shading
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClearDepth(1.0f);				// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);		// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);			// The Type Of Depth Test To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculation


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);    // Uses default lighting parameters
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_NORMALIZE);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
	glEnable(GL_LIGHT1);

	return TRUE;					// Initialization Went OK
}


// Can't send color down as a pointer to aiColor4D because AI colors are ABGR.
void Color4f(const aiColor4D *color)
{
	glColor4f(color->r, color->g, color->b, color->a);
}

void set_float4(float f[4], float a, float b, float c, float d)
{
	f[0] = a;
	f[1] = b;
	f[2] = c;
	f[3] = d;
}

void color4_to_float4(const aiColor4D *c, float f[4])
{
	f[0] = c->r;
	f[1] = c->g;
	f[2] = c->b;
	f[3] = c->a;
}

void apply_material(const aiMaterial *mtl)
{
	float c[4];

	GLenum fill_mode;
	int ret1, ret2;
	aiColor4D diffuse;
	aiColor4D specular;
	aiColor4D ambient;
	aiColor4D emission;
	ai_real shininess, strength;
	int two_sided;
	int wireframe;
	unsigned int max;	// changed: to unsigned

	int texIndex = 0;
	aiString texPath;	//contains filename of texture

	if(AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, texIndex, &texPath))
	{
		//bind texture
		unsigned int texId = *textureIdMap[texPath.data];
		glBindTexture(GL_TEXTURE_2D, texId);
	}

	set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
		color4_to_float4(&diffuse, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c);

	set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
		color4_to_float4(&specular, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

	set_float4(c, 0.2f, 0.2f, 0.2f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
		color4_to_float4(&ambient, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);

	set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
		color4_to_float4(&emission, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, c);

	max = 1;
	ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
	max = 1;
	ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);
	if((ret1 == AI_SUCCESS) && (ret2 == AI_SUCCESS))
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
	else {
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
		set_float4(c, 0.0f, 0.0f, 0.0f, 0.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);
	}

	max = 1;
	if(AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max))
		fill_mode = wireframe ? GL_LINE : GL_FILL;
	else
		fill_mode = GL_FILL;
	glPolygonMode(GL_FRONT_AND_BACK, fill_mode);

	max = 1;
	if((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
}


void recursive_render (const struct aiScene *sc, const struct aiNode* nd, float scale)
{
	unsigned int i;
	unsigned int n=0, t;
	aiMatrix4x4 m = nd->mTransformation;

	aiMatrix4x4 m2;
	aiMatrix4x4::Scaling(aiVector3D(scale, scale, scale), m2);
	m = m * m2;

	// update transform
	m.Transpose();
	glPushMatrix();
	glMultMatrixf((float*)&m);

	// draw all meshes assigned to this node
	for (; n < nd->mNumMeshes; ++n)
	{
		const struct aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];

		apply_material(sc->mMaterials[mesh->mMaterialIndex]);


		if(mesh->mNormals == NULL)
		{
			glDisable(GL_LIGHTING);
		}
		else
		{
			glEnable(GL_LIGHTING);
		}

		if(mesh->mColors[0] != NULL)
		{
			glEnable(GL_COLOR_MATERIAL);
		}
		else
		{
			glDisable(GL_COLOR_MATERIAL);
		}

		for (t = 0; t < mesh->mNumFaces; ++t) {
			const struct aiFace* face = &mesh->mFaces[t];
			GLenum face_mode;

			switch(face->mNumIndices)
			{
				case 1: face_mode = GL_POINTS; break;
				case 2: face_mode = GL_LINES; break;
				case 3: face_mode = GL_TRIANGLES; break;
				default: face_mode = GL_POLYGON; break;
			}

			glBegin(face_mode);

			for(i = 0; i < face->mNumIndices; i++)		// go through all vertices in face
			{
				int vertexIndex = face->mIndices[i];	// get group index for current index
				if(mesh->mColors[0] != NULL)
					Color4f(&mesh->mColors[0][vertexIndex]);
				if(mesh->mNormals != NULL)

					if(mesh->HasTextureCoords(0))		//HasTextureCoords(texture_coordinates_set)
					{
						glTexCoord2f(mesh->mTextureCoords[0][vertexIndex].x, 1 - mesh->mTextureCoords[0][vertexIndex].y); //mTextureCoords[channel][vertex]
					}

					glNormal3fv(&mesh->mNormals[vertexIndex].x);
					glVertex3fv(&mesh->mVertices[vertexIndex].x);
			}
			glEnd();
		}
	}

	// draw all children
	for (n = 0; n < nd->mNumChildren; ++n)
	{
		recursive_render(sc, nd->mChildren[n], scale);
	}

	glPopMatrix();
}


void drawAiScene(const aiScene* scene)
{
	logInfo("drawing objects");

	recursive_render(scene, scene->mRootNode, 0.5);

}

int DrawGLScene()				//Here's where we do all the drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();				// Reset MV Matrix


	glTranslatef(0.0f, -10.0f, -40.0f);	// Move 40 Units And Into The Screen


	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(zrot, 0.0f, 0.0f, 1.0f);

	drawAiScene(scene);

	//xrot+=0.3f;
	yrot+=0.2f;
	//zrot+=0.4f;

	return TRUE;					// okay
}


void KillGLWindow()			// Properly Kill The Window
{
	if (fullscreen)					// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);		// If So Switch Back To The Desktop
		ShowCursor(TRUE);					// Show Mouse Pointer
	}

	if (hRC)					// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))	// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))			// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;
	}

	if (hDC && !ReleaseDC(hWnd, hDC))	// Are We able to Release The DC?
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC=NULL;
	}

	if (hWnd && !DestroyWindow(hWnd))	// Are We Able To Destroy The Window
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;
	}

	if (!UnregisterClass("OpenGL", hInstance))	// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;
	}
}

GLboolean abortGLInit(const char* abortMessage)
{
	KillGLWindow();									// Reset Display
	MessageBox(NULL, abortMessage, "ERROR", MB_OK|MB_ICONEXCLAMATION);
	return FALSE;									// quit and return False
}

BOOL CreateGLWindow(const char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;		// Hold the result after searching for a match
	WNDCLASS	wc;					// Window Class Structure
	DWORD		dwExStyle;			// Window Extended Style
	DWORD		dwStyle;			// Window Style
	RECT		WindowRect;			// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left		= (long)0;
	WindowRect.right	= (long)width;
	WindowRect.top		= (long)0;
	WindowRect.bottom	= (long)height;

	fullscreen = fullscreenflag;

	hInstance = GetModuleHandle(NULL);	// Grab An Instance For Our Window
	wc.style		= CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // Redraw On Move, And Own DC For Window
	wc.lpfnWndProc	= (WNDPROC) WndProc;		// WndProc handles Messages
	wc.cbClsExtra	= 0;	// No Extra Window Data
	wc.cbWndExtra	= 0;	// No Extra Window Data
	wc.hInstance	= hInstance;
	wc.hIcon		= LoadIcon(NULL, IDI_WINLOGO);	// Load The Default Icon
	wc.hCursor		= LoadCursor(NULL, IDC_ARROW);	// Load the default arrow
	wc.hbrBackground= NULL;							// No Background required for OpenGL
	wc.lpszMenuName	= NULL;							// No Menu
	wc.lpszClassName= "OpenGL";						// Class Name

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "Failed to register the window class", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;		//exit and return false
	}

	if (fullscreen)		// attempt fullscreen mode
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Make Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of the devmode structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// bits per pixel
		dmScreenSettings.dmFields		= DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode and Get Results. NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Run In A Window.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen = FALSE;		// Select Windowed Mode (Fullscreen = FALSE)
			}
			else
			{
				//Popup Messagebox: Closing
				MessageBox(NULL, "Program will close now.", "ERROR", MB_OK|MB_ICONSTOP);
				return FALSE; //exit, return false
			}
		}
	}

	if (fullscreen)		// when mode really succeeded
	{
		dwExStyle=WS_EX_APPWINDOW;		// Window Extended Style
		dwStyle=WS_POPUP;
		ShowCursor(FALSE);
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	// Window extended style
		dwStyle=WS_OVERLAPPEDWINDOW;					// Windows style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requestes Size

	if (!(hWnd=CreateWindowEx(	dwExStyle,						// Extended Style For The Window
								"OpenGL",						// Class Name
								title,							// Window Title
								WS_CLIPSIBLINGS |				// Required Window Style
								WS_CLIPCHILDREN |				// Required Window Style
								dwStyle,						// Selected WIndow Style
								0, 0,							// Window Position
								WindowRect.right-WindowRect.left, // Calc adjusted Window Width
								WindowRect.bottom-WindowRect.top, // Calc adjustes Window Height
								NULL,							// No Parent Window
								NULL,							// No Menu
								hInstance,						// Instance
								NULL )))						// Don't pass anything To WM_CREATE
	{
		abortGLInit("Window Creation Error.");
		return FALSE;
	}

	static	PIXELFORMATDESCRIPTOR pfd=					// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),					// Size Of This Pixel Format Descriptor
		1,												// Version Number
		PFD_DRAW_TO_WINDOW |							// Format Must Support Window
		PFD_SUPPORT_OPENGL |							// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,								// Must Support Double Buffering
		PFD_TYPE_RGBA,									// Request An RGBA Format
		bits,											// Select Our Color Depth
		0, 0, 0, 0, 0, 0,								// Color Bits Ignored
		0,												// No Alpha Buffer
		0,												// Shift Bit Ignored
		0,												// No Accumulation Buffer
		0, 0, 0, 0,										// Accumulation Bits Ignored
		16,												// 16Bit Z-Buffer (Depth Buffer)
		0,												// No Stencil Buffer
		0,												// No Auxiliary Buffer
		PFD_MAIN_PLANE,									// Main Drawing Layer
		0,												// Reserved
		0, 0, 0											// Layer Masks Ignored
	};

	if (!(hDC=GetDC(hWnd)))								// Did we get the Device Context?
	{
		abortGLInit("Can't Create A GL Device Context.");
		return FALSE;
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC, &pfd)))	// Did We Find a matching pixel Format?
	{
		abortGLInit("Can't Find Suitable PixelFormat");
		return FALSE;
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))
	{
		abortGLInit("Can't Set The PixelFormat");
		return FALSE;
	}

	if (!(hRC=wglCreateContext(hDC)))
	{
		abortGLInit("Can't Create A GL Rendering Context.");
		return FALSE;
	}

	if (!(wglMakeCurrent(hDC,hRC)))						// Try to activate the rendering context
	{
		abortGLInit("Can't Activate The Rendering Context");
		return FALSE;
	}

	//// *** everything okay ***

	ShowWindow(hWnd, SW_SHOW);		// Show The Window
	SetForegroundWindow(hWnd);		// Slightly Higher Prio
	SetFocus(hWnd);					// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);	// Set Up Our Perspective GL Screen

	if (!InitGL())
	{
		abortGLInit("Initialization failed");
		return FALSE;
	}

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd,				// Handles for this Window
						 UINT uMsg,				// Message for this Window
						 WPARAM wParam,			// additional message Info
						 LPARAM lParam)			// additional message Info
{
	switch (uMsg)				// check for Window Messages
	{
		case WM_ACTIVATE:				// Watch For Window Activate Message
			{
				if (!HIWORD(wParam))	// Check Minimization State
				{
					active=TRUE;
				}
				else
				{
					active=FALSE;
				}

				return 0;				// return To The Message Loop
			}

		case WM_SYSCOMMAND:			// Interrupt System Commands
			{
				switch (wParam)
				{
					case SC_SCREENSAVE:		// Screen-saver trying to start
					case SC_MONITORPOWER:	// Monitor trying to enter power-safe
					return 0;
				}
				break;
			}

		case WM_CLOSE:			// close message received?
			{
				PostQuitMessage(0);	// Send WM_QUIT quit message
				return 0;			// Jump Back
			}

		case WM_KEYDOWN:		// Is a key pressed?
			{
				keys[wParam] = TRUE;	// If so, Mark it as true
				return 0;
			}

		case WM_KEYUP:			// Has Key Been released?
			{
				keys[wParam] = FALSE;	// If so, Mark It As FALSE
				return 0;
			}

		case WM_SIZE:			// Resize The OpenGL Window
			{
				ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));	// LoWord-Width, HiWord-Height
				return 0;
			}
	}

	// Pass All unhandled Messaged To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain( HINSTANCE hInstance,         // The instance
				   HINSTANCE hPrevInstance,      // Previous instance
				   LPSTR lpCmdLine,              // Command Line Parameters
				   int nShowCmd )                // Window Show State
{
	MSG msg;
	BOOL done=FALSE;

	createAILogger();
	logInfo("App fired!");

	// Check the command line for an override file path.
	int argc;
	LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	if (argv != NULL && argc > 1)
	{
		std::wstring modelpathW(argv[1]);
		modelpath = std::string(modelpathW.begin(), modelpathW.end());
	}

	if (!Import3DFromFile(modelpath)) return 0;

	logInfo("=============== Post Import ====================");

	if (MessageBox(NULL, "Would You Like To Run In Fullscreen Mode?", "Start Fullscreen?", MB_YESNO|MB_ICONEXCLAMATION)==IDNO)
	{
		fullscreen=FALSE;
	}

	if (!CreateGLWindow(windowTitle, 640, 480, 16, fullscreen))
	{
		return 0;
	}

	while(!done)	// Game Loop
	{
		if (PeekMessage(&msg, NULL, 0,0, PM_REMOVE))
		{
			if (msg.message==WM_QUIT)
			{
				done=TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			// Draw The Scene. Watch For ESC Key And Quit Messaged From DrawGLScene()
			if (active)
			{
				if (keys[VK_ESCAPE])
				{
					done=TRUE;
				}
				else
				{
					DrawGLScene();
					SwapBuffers(hDC);
				}
			}

			if (keys[VK_F1])
			{
				keys[VK_F1]=FALSE;
				KillGLWindow();
				fullscreen=!fullscreen;
				if (!CreateGLWindow(windowTitle, 640, 480, 16, fullscreen))
				{
					return 0;
				}
			}
		}
	}

	// *** cleanup ***

	textureIdMap.clear(); //no need to delete pointers in it manually here. (Pointers point to textureIds deleted in next step)

	if (textureIds)
	{
		delete[] textureIds;
		textureIds = NULL;
	}

	// *** cleanup end ***

	destroyAILogger();
	KillGLWindow();
	return (msg.wParam);
}
