/// \file   glview.cpp
/// \brief  OpenGL visualisation. Implementation file.
/// \author smal.root@gmail.com
/// \date   2016

#include "glview.hpp"

// Header files, OpenGL.
#include <GL/glu.h>

// Header files, DevIL.
#include <il.h>

// Header files, Assimp.
#include <assimp/DefaultLogger.hpp>

#ifndef __unused
	#define __unused	__attribute__((unused))
#endif // __unused

/**********************************/
/********** SHelper_Mesh **********/
/**********************************/

CGLView::SHelper_Mesh::SHelper_Mesh(const size_t pQuantity_Point, const size_t pQuantity_Line, const size_t pQuantity_Triangle, const SBBox& pBBox)
	: Quantity_Point(pQuantity_Point), Quantity_Line(pQuantity_Line), Quantity_Triangle(pQuantity_Triangle), BBox(pBBox)
{
	Index_Point = pQuantity_Point ? new GLuint[pQuantity_Point * 1] : nullptr;
	Index_Line = pQuantity_Line ? new GLuint[pQuantity_Line * 2] : nullptr;
	Index_Triangle = pQuantity_Triangle ? new GLuint[pQuantity_Triangle * 3] : nullptr;
}

CGLView::SHelper_Mesh::~SHelper_Mesh()
{
	if(Index_Point != nullptr) delete [] Index_Point;
	if(Index_Line != nullptr) delete [] Index_Line;
	if(Index_Triangle != nullptr) delete [] Index_Triangle;
}

/**********************************/
/********** SHelper_Mesh **********/
/**********************************/

void CGLView::SHelper_Camera::SetDefault()
{
	Position.Set(0, 0, 0);
	Target.Set(0, 0, -1);
	Rotation_AroundCamera = aiMatrix4x4();
	Rotation_Scene = aiMatrix4x4();
	Translation_ToScene.Set(0, 0, 2);
}

/**********************************/
/************ CGLView *************/
/**********************************/

void CGLView::Material_Apply(const aiMaterial* pMaterial)
{
    GLfloat tcol[4];
    aiColor4D taicol;
    unsigned int max;
    int ret1, ret2;
    int texture_index = 0;
    aiString texture_path;

    auto set_float4 = [](float f[4], float a, float b, float c, float d) { f[0] = a, f[1] = b, f[2] = c, f[3] = d; };
    auto color4_to_float4 = [](const aiColor4D *c, float f[4]) { f[0] = c->r, f[1] = c->g, f[2] = c->b, f[3] = c->a; };

	///TODO: cache materials
	// Disable color material because glMaterial is used.
	glDisable(GL_COLOR_MATERIAL);///TODO: cache
	// Set texture. If assigned.
	if(AI_SUCCESS == pMaterial->GetTexture(aiTextureType_DIFFUSE, texture_index, &texture_path))
	{
		//bind texture
		unsigned int texture_ID = mTexture_IDMap.value(texture_path.data, 0);

		glBindTexture(GL_TEXTURE_2D, texture_ID);
	}
	//
	// Set material parameters from scene or default values.
	//
	// Diffuse
	set_float4(tcol, 0.8f, 0.8f, 0.8f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(pMaterial, AI_MATKEY_COLOR_DIFFUSE, &taicol)) color4_to_float4(&taicol, tcol);

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tcol);
	// Specular
	set_float4(tcol, 0.0f, 0.0f, 0.0f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(pMaterial, AI_MATKEY_COLOR_SPECULAR, &taicol)) color4_to_float4(&taicol, tcol);

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tcol);
	// Ambient
	set_float4(tcol, 0.2f, 0.2f, 0.2f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(pMaterial, AI_MATKEY_COLOR_AMBIENT, &taicol)) color4_to_float4(&taicol, tcol);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tcol);
	// Emission
	set_float4(tcol, 0.0f, 0.0f, 0.0f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(pMaterial, AI_MATKEY_COLOR_EMISSIVE, &taicol)) color4_to_float4(&taicol, tcol);

	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, tcol);
	// Shininess
	float shininess, strength;

	max = 1;
	ret1 = aiGetMaterialFloatArray(pMaterial, AI_MATKEY_SHININESS, &shininess, &max);
	// Shininess strength
	max = 1;
	ret2 = aiGetMaterialFloatArray(pMaterial, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);
	if((ret1 == AI_SUCCESS) && (ret2 == AI_SUCCESS))
	{
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);///TODO: cache
	}
	else
	{
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);///TODO: cache
		set_float4(tcol, 0.0f, 0.0f, 0.0f, 0.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tcol);
	}

	// Fill mode
	GLenum fill_mode;
	int wireframe;

	max = 1;
	if(AI_SUCCESS == aiGetMaterialIntegerArray(pMaterial, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max))
		fill_mode = wireframe ? GL_LINE : GL_FILL;
	else
		fill_mode = GL_FILL;

	glPolygonMode(GL_FRONT_AND_BACK, fill_mode);///TODO: cache
	// Fill side
	int two_sided;

	max = 1;
	if((AI_SUCCESS == aiGetMaterialIntegerArray(pMaterial, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)///TODO: cache
		glDisable(GL_CULL_FACE);
	else
		glEnable(GL_CULL_FACE);
}

void CGLView::Matrix_NodeToRoot(const aiNode* pNode, aiMatrix4x4& pOutMatrix)
{
const aiNode* node_cur;
std::list<aiMatrix4x4> mat_list;

	pOutMatrix = aiMatrix4x4();
	// starting walk from current element to root
	node_cur = pNode;
	if(node_cur != nullptr)
	{
		do
		{
			// if cur_node is group then store group transformation matrix in list.
			mat_list.push_back(node_cur->mTransformation);
			node_cur = node_cur->mParent;
		} while(node_cur != nullptr);
	}

	// multiply all matrices in reverse order
    for ( std::list<aiMatrix4x4>::reverse_iterator rit = mat_list.rbegin(); rit != mat_list.rend(); rit++)
    {
        pOutMatrix = pOutMatrix * (*rit);
    }
}

void CGLView::ImportTextures(const QString& pScenePath)
{
    auto LoadTexture = [&](const QString& pFileName) -> bool ///TODO: IME texture mode, operation.
    {
        ILboolean success;
        GLuint id_ogl_texture;// OpenGL texture ID.

	    if(!pFileName.startsWith(AI_EMBEDDED_TEXNAME_PREFIX))
	    {
		    ILuint id_image;// DevIL image ID.
		    QString basepath = pScenePath.left(pScenePath.lastIndexOf('/') + 1);// path with '/' at the end.
		    QString fileloc = (basepath + pFileName);

		    fileloc.replace('\\', "/");
		    ilGenImages(1, &id_image);// Generate DevIL image ID.
		    ilBindImage(id_image);
		    success = ilLoadImage(fileloc.toLocal8Bit());
		    if(!success)
		    {
			    LogError(QString("Couldn't load Image: %1").arg(fileloc));

			    return false;
		    }

		    // Convert every colour component into unsigned byte. If your image contains alpha channel you can replace IL_RGB with IL_RGBA.
		    success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		    if(!success)
		    {
			    LogError("Couldn't convert image.");

			    return false;
		    }

		    glGenTextures(1, &id_ogl_texture);// Texture ID generation.
		    mTexture_IDMap[pFileName] = id_ogl_texture;// save texture ID for filename in map
		    glBindTexture(GL_TEXTURE_2D, id_ogl_texture);// Binding of texture ID.
		    // Redefine standard texture values
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);// We will use linear interpolation for magnification filter.
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);// We will use linear interpolation for minifying filter.
		    glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0,
						    ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());// Texture specification.

		    //Cleanup
		    ilDeleteImages(1, &id_image);// Because we have already copied image data into texture data we can release memory used by image.
	    }
	    else
	    {
		    struct SPixel_Description
		    {
			    const char* FormatHint;
			    const GLint Image_InternalFormat;
			    const GLint Pixel_Format;
		    };

		    constexpr SPixel_Description Pixel_Description[] = {
			    {"rgba8880", GL_RGB, GL_RGB},
			    {"rgba8888", GL_RGBA, GL_RGBA}
		    };

		    constexpr size_t Pixel_Description_Count = sizeof(Pixel_Description) / sizeof(SPixel_Description);

		    size_t idx_description;
		    // Get texture index.
		    bool ok;
		    size_t idx_texture = pFileName.right(strlen(AI_EMBEDDED_TEXNAME_PREFIX)).toULong(&ok);

		    if(!ok)
		    {
			    LogError("Can not get index of the embedded texture from path in material.");

			    return false;
		    }

		    // Create alias for conveniance.
		    const aiTexture& als = *mScene->mTextures[idx_texture];

		    if(als.mHeight == 0)// Compressed texture.
		    {
			    LogError("IME: compressed embedded textures are not implemented.");
		    }
		    else
		    {
			    ok = false;
			    for(size_t idx = 0; idx < Pixel_Description_Count; idx++)
			    {
				    if(als.CheckFormat(Pixel_Description[idx].FormatHint))
				    {
					    idx_description = idx;
					    ok = true;
					    break;
				    }
			    }

			    if(!ok)
			    {
				    LogError(QString("Unsupported format hint for embedded texture: [%1]").arg(als.achFormatHint));

				    return false;
			    }

			    glGenTextures(1, &id_ogl_texture);// Texture ID generation.
			    mTexture_IDMap[pFileName] = id_ogl_texture;// save texture ID for filename in map
			    glBindTexture(GL_TEXTURE_2D, id_ogl_texture);// Binding of texture ID.
			    // Redefine standard texture values
			    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);// We will use linear interpolation for magnification filter.
			    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);// We will use linear interpolation for minifying filter.
			    // Texture specification.
			    glTexImage2D(GL_TEXTURE_2D, 0, Pixel_Description[idx_description].Image_InternalFormat, als.mWidth, als.mHeight, 0,
							    Pixel_Description[idx_description].Pixel_Format, GL_UNSIGNED_BYTE, (uint8_t*)als.pcData);
		    }// if(als.mHeight == 0) else
	    }// if(!filename.startsWith(AI_EMBEDDED_TEXNAME_PREFIX)) else

	    return true;
    };// auto LoadTexture = [&](const aiString& pPath)

	if(mScene == nullptr)
	{
		LogError("Trying to load textures for empty scene.");

		return;
	}

	// Before calling ilInit() version should be checked.
	if(ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
	{
		LogError("Wrong DevIL version.");

		return;
	}

	ilInit();// Initialization of DevIL.
	//
	// Load textures.
	//
	// Get textures file names and number of textures.
	for(size_t idx_material = 0; idx_material < mScene->mNumMaterials; idx_material++)
	{
		int idx_texture = 0;
		aiString path;

		do
		{
			if(mScene->mMaterials[idx_material]->GetTexture(aiTextureType_DIFFUSE, idx_texture, &path) != AI_SUCCESS) break;

			LoadTexture(QString(path.C_Str()));
			idx_texture++;
		} while(true);
	}// for(size_t idx_material = 0; idx_material < mScene->mNumMaterials; idx_material++)

	// Textures list is empty, exit.
	if(mTexture_IDMap.size() == 0)
	{
		LogInfo("No textures for import.");

		return;
	}
}

void CGLView::BBox_GetForNode(const aiNode& pNode, const aiMatrix4x4& pParent_TransformationMatrix, SBBox& pNodeBBox, bool& pFirstAssign)
{
    aiMatrix4x4 mat_trans = pParent_TransformationMatrix * pNode.mTransformation;

	// Check if node has meshes
	for(size_t idx_idx_mesh = 0; idx_idx_mesh < pNode.mNumMeshes; idx_idx_mesh++)
	{
		size_t idx_mesh;
		SBBox bbox_local;
		aiVector3D bbox_vertices[8];

		idx_mesh = pNode.mMeshes[idx_idx_mesh];
		// Get vertices of mesh BBox
		BBox_GetVertices(mHelper_Mesh[idx_mesh]->BBox, bbox_vertices);
		// Transform vertices
		for(size_t idx_vert = 0; idx_vert < 8; idx_vert++) bbox_vertices[idx_vert] *= mat_trans;

		// And create BBox for transformed mesh
		BBox_GetFromVertices(bbox_vertices, 8, bbox_local);

		if(!pFirstAssign)
		{
			BBox_Extend(bbox_local, pNodeBBox);
		}
		else
		{
			pFirstAssign = false;
			pNodeBBox = bbox_local;
		}
	}// for(size_t idx_idx_mesh = 0; idx_idx_mesh < pNode.mNumMeshes; idx_idx_mesh++)

	for(size_t idx_node = 0; idx_node < pNode.mNumChildren; idx_node++)
	{
		BBox_GetForNode(*pNode.mChildren[idx_node], mat_trans, pNodeBBox, pFirstAssign);
	}
}

void CGLView::BBox_Extend(const SBBox& pChild, SBBox& pParent)
{
	// search minimal...
	AssignIfLesser(&pParent.Minimum.x, pChild.Minimum.x);
	AssignIfLesser(&pParent.Minimum.y, pChild.Minimum.y);
	AssignIfLesser(&pParent.Minimum.z, pChild.Minimum.z);
	// and maximal values
	AssignIfGreater(&pParent.Maximum.x, pChild.Maximum.x);
	AssignIfGreater(&pParent.Maximum.y, pChild.Maximum.y);
	AssignIfGreater(&pParent.Maximum.z, pChild.Maximum.z);
}

void CGLView::BBox_GetVertices(const SBBox& pBBox, aiVector3D pVertex[8])
{
	pVertex[0] = pBBox.Minimum;
	pVertex[1].Set(pBBox.Minimum.x, pBBox.Minimum.y, pBBox.Maximum.z);
	pVertex[2].Set(pBBox.Minimum.x, pBBox.Maximum.y, pBBox.Maximum.z);
	pVertex[3].Set(pBBox.Minimum.x, pBBox.Maximum.y, pBBox.Minimum.z);

	pVertex[4].Set(pBBox.Maximum.x, pBBox.Minimum.y, pBBox.Minimum.z);
	pVertex[5].Set(pBBox.Maximum.x, pBBox.Minimum.y, pBBox.Maximum.z);
	pVertex[6] = pBBox.Maximum;
	pVertex[7].Set(pBBox.Maximum.x, pBBox.Maximum.y, pBBox.Minimum.z);

}

void CGLView::BBox_GetFromVertices(const aiVector3D* pVertices, const size_t pVerticesQuantity, SBBox& pBBox)
{
	if(pVerticesQuantity == 0)
	{
		pBBox.Maximum.Set(0, 0, 0);
		pBBox.Minimum.Set(0, 0, 0);

		return;
	}

	// Assign first values.
	pBBox.Minimum = pVertices[0];
	pBBox.Maximum = pVertices[0];

	for(size_t idx_vert = 1; idx_vert < pVerticesQuantity; idx_vert++)
	{
		const GLfloat x = pVertices[idx_vert].x;
		const GLfloat y = pVertices[idx_vert].y;
		const GLfloat z = pVertices[idx_vert].z;

		// search minimal...
		AssignIfLesser(&pBBox.Minimum.x, x);
		AssignIfLesser(&pBBox.Minimum.y, y);
		AssignIfLesser(&pBBox.Minimum.z, z);
		// and maximal values
		AssignIfGreater(&pBBox.Maximum.x, x);
		AssignIfGreater(&pBBox.Maximum.y, y);
		AssignIfGreater(&pBBox.Maximum.z, z);
	}
}

/********************************************************************/
/************************ Logging functions *************************/
/********************************************************************/

void CGLView::LogInfo(const QString& pMessage)
{
	Assimp::DefaultLogger::get()->info(pMessage.toStdString());
}

void CGLView::LogError(const QString& pMessage)
{
	Assimp::DefaultLogger::get()->error(pMessage.toStdString());
}

/********************************************************************/
/************************** Draw functions **************************/
/********************************************************************/

void CGLView::Draw_Node(const aiNode* pNode)
{
    aiMatrix4x4 mat_node = pNode->mTransformation;

	// Apply node transformation matrix.
	mat_node.Transpose();
	glPushMatrix();
	glMultMatrixf((GLfloat*)&mat_node);
	// Draw all meshes assigned to this node
	for(size_t idx_mesh_arr = 0; idx_mesh_arr < pNode->mNumMeshes; idx_mesh_arr++) Draw_Mesh(pNode->mMeshes[idx_mesh_arr]);

	// Draw all children nodes
	for(size_t idx_node = 0; idx_node < pNode->mNumChildren; idx_node++) Draw_Node(pNode->mChildren[idx_node]);

	// Restore transformation matrix.
	glPopMatrix();
}

void CGLView::Draw_Mesh(const size_t pMesh_Index)
{
	// Check argument
	if(pMesh_Index >= mHelper_Mesh_Quantity) return;

	aiMesh& mesh_cur = *mScene->mMeshes[pMesh_Index];

	if(!mesh_cur.HasPositions()) return;// Nothing to draw.

	// If mesh use material then apply it
	if(mScene->HasMaterials()) Material_Apply(mScene->mMaterials[mesh_cur.mMaterialIndex]);

	//
	// Vertices array
	//
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, mesh_cur.mVertices);

	if(mesh_cur.HasVertexColors(0))
	{
		glEnable(GL_COLOR_MATERIAL);///TODO: cache
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(4, GL_FLOAT, 0, mesh_cur.mColors[0]);
	}

	//
	// Texture coordinates array
	//
	if(mesh_cur.HasTextureCoords(0))
	{
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, sizeof(aiVector3D), mesh_cur.mTextureCoords[0]);
	}

	//
	// Normals array
	//
	if(mesh_cur.HasNormals())
	{
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, 0, mesh_cur.mNormals);
	}

	//
	// Draw arrays
	//
	SHelper_Mesh& helper_cur = *mHelper_Mesh[pMesh_Index];

	if(helper_cur.Quantity_Triangle > 0) glDrawElements(GL_TRIANGLES, helper_cur.Quantity_Triangle * 3, GL_UNSIGNED_INT, helper_cur.Index_Triangle);
	if(helper_cur.Quantity_Line > 0) glDrawElements(GL_LINES,helper_cur.Quantity_Line * 2, GL_UNSIGNED_INT, helper_cur.Index_Line);
	if(helper_cur.Quantity_Point > 0) glDrawElements(GL_POINTS, helper_cur.Quantity_Point, GL_UNSIGNED_INT, helper_cur.Index_Point);

	//
	// Clean up
	//
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void CGLView::Draw_BBox(const SBBox& pBBox)
{
    aiVector3D vertex[8];

	BBox_GetVertices(pBBox, vertex);
	// Draw
	if(mLightingEnabled) glDisable(GL_LIGHTING);///TODO: display list

	glEnable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_1D, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_3D, 0);
	qglColor(QColor(Qt::white));
	glBegin(GL_LINE_STRIP);
		glVertex3fv(&vertex[0][0]), glVertex3fv(&vertex[1][0]), glVertex3fv(&vertex[2][0]), glVertex3fv(&vertex[3][0]), glVertex3fv(&vertex[0][0]);// "Minimum" side.
		glVertex3fv(&vertex[4][0]), glVertex3fv(&vertex[5][0]), glVertex3fv(&vertex[6][0]), glVertex3fv(&vertex[7][0]), glVertex3fv(&vertex[4][0]);// Edge and "maximum" side.
	glEnd();
	glBegin(GL_LINES);
		glVertex3fv(&vertex[1][0]), glVertex3fv(&vertex[5][0]);
		glVertex3fv(&vertex[2][0]), glVertex3fv(&vertex[6][0]);
		glVertex3fv(&vertex[3][0]), glVertex3fv(&vertex[7][0]);
	glEnd();
	glDisable(GL_COLOR_MATERIAL);
	if(mLightingEnabled) glEnable(GL_LIGHTING);
}

void CGLView::Enable_Textures(const bool pEnable)
{
	if(pEnable)
	{
		glEnable(GL_TEXTURE_1D);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_3D);
	}
	else
	{
		glDisable(GL_TEXTURE_1D);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_TEXTURE_3D);
	}
}

/********************************************************************/
/*********************** Overrided functions ************************/
/********************************************************************/

void CGLView::initializeGL()
{
	qglClearColor(Qt::gray);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	glDisable(GL_COLOR_MATERIAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glFrontFace(GL_CCW);
}

void CGLView::resizeGL(int pWidth, int pHeight)
{
	mCamera_Viewport_AspectRatio = (GLdouble)pWidth / pHeight;
	glViewport(0, 0, pWidth, pHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(mCamera_FOVY, mCamera_Viewport_AspectRatio, 1.0, 100000.0);///TODO: znear/zfar depend on scene size.
}

void CGLView::drawCoordSystem() {
    glBindTexture(GL_TEXTURE_1D, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindTexture(GL_TEXTURE_3D, 0);
    glEnable(GL_COLOR_MATERIAL);
    glBegin(GL_LINES);
    // X, -X
    qglColor(QColor(Qt::red)), glVertex3f(0.0, 0.0, 0.0), glVertex3f(100000.0, 0.0, 0.0);
    qglColor(QColor(Qt::cyan)), glVertex3f(0.0, 0.0, 0.0), glVertex3f(-100000.0, 0.0, 0.0);
    // Y, -Y
    qglColor(QColor(Qt::green)), glVertex3f(0.0, 0.0, 0.0), glVertex3f(0.0, 100000.0, 0.0);
    qglColor(QColor(Qt::magenta)), glVertex3f(0.0, 0.0, 0.0), glVertex3f(0.0, -100000.0, 0.0);
    // Z, -Z
    qglColor(QColor(Qt::blue)), glVertex3f(0.0, 0.0, 0.0), glVertex3f(0.0, 0.0, 100000.0);
    qglColor(QColor(Qt::yellow)), glVertex3f(0.0, 0.0, 0.0), glVertex3f(0.0, 0.0, -100000.0);
    glEnd();
}

void CGLView::paintGL()
{
    QTime time_paintbegin;

	time_paintbegin = QTime::currentTime();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Apply current camera transformations.
	glMultMatrixf((GLfloat*)&mHelper_Camera.Rotation_AroundCamera);
	glTranslatef(-mHelper_Camera.Translation_ToScene.x, -mHelper_Camera.Translation_ToScene.y, -mHelper_Camera.Translation_ToScene.z);
	glMultMatrixf((GLfloat*)&mHelper_Camera.Rotation_Scene);
	// Coordinate system
    if ( mLightingEnabled ) {
        glDisable( GL_LIGHTING );///TODO: display list
    }
    drawCoordSystem();

	glDisable(GL_COLOR_MATERIAL);
	if(mLightingEnabled) glEnable(GL_LIGHTING);

	// Scene
	if(mScene != nullptr)
	{
		Draw_Node(mScene->mRootNode);
		// Scene BBox
		if(mScene_DrawBBox) Draw_BBox(mScene_BBox);
	}

	emit Paint_Finished((size_t)time_paintbegin.msecsTo(QTime::currentTime()), mHelper_Camera.Translation_ToScene.Length());
}

/********************************************************************/
/********************** Constructor/Destructor **********************/
/********************************************************************/

CGLView::CGLView(QWidget *pParent)
	: QGLWidget(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer), pParent)
{
	static_assert(sizeof(GLfloat) == sizeof(ai_real), "ai_real in Assimp must be equal to GLfloat/float.");///TODO: may be templates can be used.

	// set initial view
	mHelper_CameraDefault.SetDefault();
	Camera_Set(0);
}

CGLView::~CGLView()
{
	FreeScene();
}

/********************************************************************/
/********************* Scene control functions **********************/
/********************************************************************/

void CGLView::FreeScene()
{
	// Set scene to null and after that \ref paintGL will not try to render it.
	mScene = nullptr;
	// Clean helper objects.
	if(mHelper_Mesh != nullptr)
	{
		for(size_t idx_mesh = 0; idx_mesh < mHelper_Mesh_Quantity; idx_mesh++) delete mHelper_Mesh[idx_mesh];

		delete [] mHelper_Mesh;
		mHelper_Mesh = nullptr;
	}

	mHelper_Mesh_Quantity = 0;
	// Delete textures
	const int id_tex_size = mTexture_IDMap.size();

	if(id_tex_size)
	{
		GLuint* id_tex = new GLuint[id_tex_size];
		QMap<QString, GLuint>::iterator it = mTexture_IDMap.begin();

		for(int idx = 0; idx < id_tex_size; idx++, it++)
		{
			id_tex[idx] = it.value();
		}

		glDeleteTextures(id_tex_size, id_tex);
		mTexture_IDMap.clear();
		delete [] id_tex;
	}
}

void CGLView::SetScene(const aiScene *pScene, const QString& pScenePath)
{
	FreeScene();// Clear old data
	// Why checking here, not at begin of function. Because old scene may not exist at know. So, need cleanup.
	if(pScene == nullptr) return;

	mScene = pScene;// Copy pointer of new scene.

	//
	// Meshes
	//
	// Create helper objects for meshes. This allow to render meshes as OpenGL arrays.
	if(mScene->HasMeshes())
	{
		// Create mesh helpers array.
		mHelper_Mesh_Quantity = mScene->mNumMeshes;
		mHelper_Mesh = new SHelper_Mesh*[mScene->mNumMeshes];

		// Walk through the meshes and extract needed data and, also calculate BBox.
		for(size_t idx_mesh = 0; idx_mesh < mScene->mNumMeshes; idx_mesh++)
		{
			aiMesh& mesh_cur = *mScene->mMeshes[idx_mesh];

			//
			// Calculate BBox
			//
			SBBox mesh_bbox;

			BBox_GetFromVertices(mesh_cur.mVertices, mesh_cur.mNumVertices, mesh_bbox);
			//
			// Create vertices indices arrays splited by primitive type.
			//
			size_t indcnt_p = 0;// points quantity
			size_t indcnt_l = 0;// lines quantity
			size_t indcnt_t = 0;// triangles quantity

			if(mesh_cur.HasFaces())
			{
				// Usual way: all faces are triangles
				if(mesh_cur.mPrimitiveTypes == aiPrimitiveType_TRIANGLE)
				{
					indcnt_t = mesh_cur.mNumFaces;
				}
				else
				{
					// Calculate count of primitives by types.
					for(size_t idx_face = 0; idx_face < mesh_cur.mNumFaces; idx_face++)
					{
						if(mesh_cur.mFaces[idx_face].mNumIndices == 3)
							indcnt_t++;
						else if(mesh_cur.mFaces[idx_face].mNumIndices == 2)
							indcnt_l++;
						else if(mesh_cur.mFaces[idx_face].mNumIndices == 1)
							indcnt_p++;
					}
				}// if(mesh_cur.mPrimitiveTypes == aiPrimitiveType_TRIANGLE) else

				// Create helper
				mHelper_Mesh[idx_mesh] = new SHelper_Mesh(indcnt_p, indcnt_l, indcnt_t, mesh_bbox);
				// Fill indices arrays
				indcnt_p = 0, indcnt_l = 0, indcnt_t = 0;// Reuse variables as indices
				for(size_t idx_face = 0; idx_face < mesh_cur.mNumFaces; idx_face++)
				{
					if(mesh_cur.mFaces[idx_face].mNumIndices == 3)
					{
						mHelper_Mesh[idx_mesh]->Index_Triangle[indcnt_t++] = mesh_cur.mFaces[idx_face].mIndices[0];
						mHelper_Mesh[idx_mesh]->Index_Triangle[indcnt_t++] = mesh_cur.mFaces[idx_face].mIndices[1];
						mHelper_Mesh[idx_mesh]->Index_Triangle[indcnt_t++] = mesh_cur.mFaces[idx_face].mIndices[2];
					}
					else if(mesh_cur.mFaces[idx_face].mNumIndices == 2)
					{
						mHelper_Mesh[idx_mesh]->Index_Line[indcnt_l++] = mesh_cur.mFaces[idx_face].mIndices[0];
						mHelper_Mesh[idx_mesh]->Index_Line[indcnt_l++] = mesh_cur.mFaces[idx_face].mIndices[1];
					}
					else if(mesh_cur.mFaces[idx_face].mNumIndices == 1)
					{
						mHelper_Mesh[idx_mesh]->Index_Point[indcnt_p++] = mesh_cur.mFaces[idx_face].mIndices[0];
					}
				}// for(size_t idx_face = 0; idx_face < mesh_cur.mNumFaces; idx_face++)
			}// if(mesh_cur.HasFaces())
			else
			{
				// If mesh has no faces then vertices can be just points set.
				indcnt_p = mesh_cur.mNumVertices;
				// Create helper
				mHelper_Mesh[idx_mesh] = new SHelper_Mesh(indcnt_p, 0, 0, mesh_bbox);
				// Fill indices arrays
				for(size_t idx = 0; idx < indcnt_p; idx++) mHelper_Mesh[idx_mesh]->Index_Point[idx] = idx;

			}// if(mesh_cur.HasFaces()) else
		}// for(size_t idx_mesh = 0; idx_mesh < mScene->mNumMeshes; idx_mesh++)
	}// if(mScene->HasMeshes())

	//
	// Scene BBox
	//
	// For calculating right BBox we must walk through all nodes and apply transformation to meshes BBoxes
	if(mHelper_Mesh_Quantity > 0)
	{
		bool first_assign = true;
		aiMatrix4x4 mat_root;

		BBox_GetForNode(*mScene->mRootNode, mat_root, mScene_BBox, first_assign);
		mScene_Center = mScene_BBox.Maximum + mScene_BBox.Minimum;
		mScene_Center /= 2;
	}
	else
	{
		mScene_BBox = {{0, 0, 0}, {0, 0, 0}};
		mScene_Center = {0, 0, 0};
	}// if(mHelper_Mesh_Count > 0) else

	//
	// Textures
	//
	ImportTextures(pScenePath);

	//
	// Light sources
	//
	Lighting_Enable();
	// If scene has no lights then enable default
	if(!mScene->HasLights())
	{
		const GLfloat col_amb[4] = { 0.2, 0.2, 0.2, 1.0 };
		SLightParameters lp;

		lp.Type = aiLightSource_POINT;
		lp.Ambient.r = col_amb[0], lp.Ambient.g = col_amb[1], lp.Ambient.b = col_amb[2], lp.Ambient.a = col_amb[3];
		lp.Diffuse = { 1.0, 1.0, 1.0, 1.0 };
		lp.Specular = lp.Diffuse;
		lp.For.Point.Position = mScene_Center;
		lp.For.Point.Attenuation_Constant = 1;
		lp.For.Point.Attenuation_Linear = 0;
		lp.For.Point.Attenuation_Quadratic = 0;
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, col_amb);
		Lighting_EditSource(0, lp);
		emit SceneObject_LightSource("_default");// Light source will be enabled in signal handler.
	}
	else
	{
		for(size_t idx_light = 0; idx_light < mScene->mNumLights; idx_light++)
		{
			SLightParameters lp;
			QString name;
			const aiLight& light_cur = *mScene->mLights[idx_light];

			auto col3_to_col4 = [](const aiColor3D& pCol3) -> aiColor4D { return aiColor4D(pCol3.r, pCol3.g, pCol3.b, 1.0); };

			///TODO: find light source node and apply all transformations
			// General properties
			name = light_cur.mName.C_Str();
			lp.Ambient = col3_to_col4(light_cur.mColorAmbient);
			lp.Diffuse = col3_to_col4(light_cur.mColorDiffuse);
			lp.Specular = col3_to_col4(light_cur.mColorSpecular);
			lp.Type = light_cur.mType;
			// Depend on type properties
			switch(light_cur.mType)
			{
				case aiLightSource_DIRECTIONAL:
					lp.For.Directional.Direction = light_cur.mDirection;
					break;
				case aiLightSource_POINT:
					lp.For.Point.Position = light_cur.mPosition;
					lp.For.Point.Attenuation_Constant = light_cur.mAttenuationConstant;
					lp.For.Point.Attenuation_Linear = light_cur.mAttenuationLinear;
					lp.For.Point.Attenuation_Quadratic = light_cur.mAttenuationQuadratic;
					break;
				case aiLightSource_SPOT:
					lp.For.Spot.Position = light_cur.mPosition;
					lp.For.Spot.Direction = light_cur.mDirection;
					lp.For.Spot.Attenuation_Constant = light_cur.mAttenuationConstant;
					lp.For.Spot.Attenuation_Linear = light_cur.mAttenuationLinear;
					lp.For.Spot.Attenuation_Quadratic = light_cur.mAttenuationQuadratic;
					lp.For.Spot.CutOff = light_cur.mAngleOuterCone;
					break;
				case aiLightSource_AMBIENT:
					lp.For.Point.Position = light_cur.mPosition, lp.For.Point.Attenuation_Constant = 1, lp.For.Point.Attenuation_Linear = 0, lp.For.Point.Attenuation_Quadratic = 0;
					name.append("_unsup_ambient");
					break;
				case aiLightSource_AREA:
					lp.For.Point.Position = light_cur.mPosition, lp.For.Point.Attenuation_Constant = 1, lp.For.Point.Attenuation_Linear = 0, lp.For.Point.Attenuation_Quadratic = 0;
					name.append("_unsup_area");
					break;
				case aiLightSource_UNDEFINED:
					lp.For.Point.Position = light_cur.mPosition, lp.For.Point.Attenuation_Constant = 1, lp.For.Point.Attenuation_Linear = 0, lp.For.Point.Attenuation_Quadratic = 0;
					name.append("_unsup_undefined");
					break;
				default:
					lp.For.Point.Position = light_cur.mPosition, lp.For.Point.Attenuation_Constant = 1, lp.For.Point.Attenuation_Linear = 0, lp.For.Point.Attenuation_Quadratic = 0;
					name.append("_unsupported_invalid");
					break;
			}// switch(light_cur.mType)

			// Add light source
			if(name.isEmpty()) name += QString("%1").arg(idx_light);// Use index if name is empty.

			Lighting_EditSource(idx_light, lp);
			emit SceneObject_LightSource(name);// Light source will be enabled in signal handler.
		}// for(size_t idx_light = 0; idx_light < mScene->mNumLights; idx_light++)
	}// if(!mScene->HasLights()) else

	//
	// Cameras
	//
	if(!mScene->HasCameras())
	{
		mCamera_DefaultAdded = true;
		mHelper_CameraDefault.SetDefault();
		// Calculate distance from camera to scene. Distance must be enoguh for that viewport contain whole scene.
		const GLfloat tg_angle = tan(mCamera_FOVY / 2);

		GLfloat val_x = ((mScene_BBox.Maximum.x - mScene_BBox.Minimum.x) / 2) / (mCamera_Viewport_AspectRatio * tg_angle);
		GLfloat val_y = ((mScene_BBox.Maximum.y - mScene_BBox.Minimum.y) / 2) / tg_angle;
		GLfloat val_step = val_x;

		AssignIfGreater(val_step, val_y);
		mHelper_CameraDefault.Translation_ToScene.Set(mScene_Center.x, mScene_Center.y, val_step + mScene_BBox.Maximum.z);
		emit SceneObject_Camera("_default");
	}
	else
	{
		mCamera_DefaultAdded = false;
		for(size_t idx_cam = 0; idx_cam < mScene->mNumCameras; idx_cam++)
		{
			emit SceneObject_Camera(mScene->mCameras[idx_cam]->mName.C_Str());
		}
	}// if(!mScene->HasCameras()) else
}

/********************************************************************/
/******************** Lighting control functions ********************/
/********************************************************************/

void CGLView::Lighting_Enable()
{
	mLightingEnabled = true;
	glEnable(GL_LIGHTING);
}

void CGLView::Lighting_Disable()
{
	glDisable(GL_LIGHTING);
	mLightingEnabled = false;
}

void CGLView::Lighting_EditSource(const size_t pLightNumber, const SLightParameters& pLightParameters)
{
const size_t light_num = GL_LIGHT0 + pLightNumber;

GLfloat farr[4];

	if(pLightNumber >= GL_MAX_LIGHTS) return;///TODO: return value;

	glLightfv(light_num, GL_AMBIENT, &pLightParameters.Ambient.r);// Ambient color
	glLightfv(light_num, GL_DIFFUSE, &pLightParameters.Diffuse.r);// Diffuse color
	glLightfv(light_num, GL_SPECULAR, &pLightParameters.Specular.r);// Specular color
	// Other parameters
	switch(pLightParameters.Type)
	{
		case aiLightSource_DIRECTIONAL:
			// Direction
			farr[0] = pLightParameters.For.Directional.Direction.x, farr[2] = pLightParameters.For.Directional.Direction.y;
			farr[2] = pLightParameters.For.Directional.Direction.z; farr[3] = 0;
			glLightfv(light_num, GL_POSITION, farr);
			break;
		case aiLightSource_POINT:
			// Position
			farr[0] = pLightParameters.For.Point.Position.x, farr[2] = pLightParameters.For.Point.Position.y;
			farr[2] = pLightParameters.For.Point.Position.z; farr[3] = 1;
			glLightfv(light_num, GL_POSITION, farr);
			// Attenuation
			glLightf(light_num, GL_CONSTANT_ATTENUATION, pLightParameters.For.Point.Attenuation_Constant);
			glLightf(light_num, GL_LINEAR_ATTENUATION, pLightParameters.For.Point.Attenuation_Linear);
			glLightf(light_num, GL_QUADRATIC_ATTENUATION, pLightParameters.For.Point.Attenuation_Quadratic);
			glLightf(light_num, GL_SPOT_CUTOFF, 180.0);
			break;
		case aiLightSource_SPOT:
			// Position
			farr[0] = pLightParameters.For.Spot.Position.x, farr[2] = pLightParameters.For.Spot.Position.y, farr[2] = pLightParameters.For.Spot.Position.z; farr[3] = 1;
			glLightfv(light_num, GL_POSITION, farr);
			// Attenuation
			glLightf(light_num, GL_CONSTANT_ATTENUATION, pLightParameters.For.Spot.Attenuation_Constant);
			glLightf(light_num, GL_LINEAR_ATTENUATION, pLightParameters.For.Spot.Attenuation_Linear);
			glLightf(light_num, GL_QUADRATIC_ATTENUATION, pLightParameters.For.Spot.Attenuation_Quadratic);
			// Spot specific
			farr[0] = pLightParameters.For.Spot.Direction.x, farr[2] = pLightParameters.For.Spot.Direction.y, farr[2] = pLightParameters.For.Spot.Direction.z; farr[3] = 0;
			glLightfv(light_num, GL_SPOT_DIRECTION, farr);
			glLightf(light_num, GL_SPOT_CUTOFF, pLightParameters.For.Spot.CutOff);
			break;
		default:// For unknown light source types use point source.
			// Position
			farr[0] = pLightParameters.For.Point.Position.x, farr[2] = pLightParameters.For.Point.Position.y;
			farr[2] = pLightParameters.For.Point.Position.z; farr[3] = 1;
			glLightfv(light_num, GL_POSITION, farr);
			// Attenuation
			glLightf(light_num, GL_CONSTANT_ATTENUATION, 1);
			glLightf(light_num, GL_LINEAR_ATTENUATION, 0);
			glLightf(light_num, GL_QUADRATIC_ATTENUATION, 0);
			glLightf(light_num, GL_SPOT_CUTOFF, 180.0);
			break;
	}// switch(pLightParameters.Type)
}

void CGLView::Lighting_EnableSource(const size_t pLightNumber)
{
	if(pLightNumber >= GL_MAX_LIGHTS) return;///TODO: return value;

	glEnable(GL_LIGHT0 + pLightNumber);
}

void CGLView::Lighting_DisableSource(const size_t pLightNumber)
{
	if(pLightNumber >= GL_MAX_LIGHTS) return;///TODO: return value;

	glDisable(GL_LIGHT0 + pLightNumber);
}

/********************************************************************/
/******************** Cameras control functions *********************/
/********************************************************************/

void CGLView::Camera_Set(const size_t pCameraNumber)
{
    SHelper_Camera& hcam = mHelper_Camera;// reference with short name for conveniance.
    aiVector3D up;

	if(mCamera_DefaultAdded || (pCameraNumber >= mScene->mNumCameras))// If default camera used then 'pCameraNumber' doesn't matter.
	{
		// Transformation parameters
		hcam = mHelper_CameraDefault;
		up.Set(0, 1, 0);
	}
	else
	{
		const aiCamera& camera_cur = *mScene->mCameras[pCameraNumber];
		const aiNode* camera_node;

		aiMatrix4x4 camera_mat;
		aiQuaternion camera_quat_rot;
		aiVector3D camera_tr;

		up = camera_cur.mUp;
		//
		// Try to get real coordinates of the camera.
		//
		// Find node
		camera_node = mScene->mRootNode->FindNode(camera_cur.mName);
		if(camera_node != nullptr) Matrix_NodeToRoot(camera_node, camera_mat);

		hcam.Position = camera_cur.mLookAt;
		hcam.Target = camera_cur.mPosition;
		hcam.Rotation_AroundCamera = aiMatrix4x4(camera_quat_rot.GetMatrix());
		hcam.Rotation_AroundCamera.Transpose();
		// get components of transformation matrix.
		camera_mat.DecomposeNoScaling(camera_quat_rot, camera_tr);
		hcam.Rotation_Scene = aiMatrix4x4();
		hcam.Translation_ToScene = camera_tr;
	}

	// Load identity matrix - travel to world begin.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Set camera and update picture
	gluLookAt(hcam.Position.x, hcam.Position.y, hcam.Position.z, hcam.Target.x, hcam.Target.y, hcam.Target.z, up.x, up.y, up.z);
}

void CGLView::Camera_RotateScene(const GLfloat pAngle_X, const GLfloat pAngle_Y, const GLfloat pAngle_Z)
{
auto deg2rad = [](const GLfloat pDegree) -> GLfloat { return pDegree * M_PI / 180.0; };

	aiMatrix4x4 mat_rot;

	mat_rot.FromEulerAnglesXYZ(deg2rad(pAngle_X), deg2rad(pAngle_Y), deg2rad(pAngle_Z));
	mHelper_Camera.Rotation_Scene *= mat_rot;
}

void CGLView::Camera_Rotate(const GLfloat pAngle_X, const GLfloat pAngle_Y, const GLfloat pAngle_Z)
{
auto deg2rad = [](const GLfloat pDegree) -> GLfloat { return pDegree * M_PI / 180.0; };

	aiMatrix4x4 mat_rot;

	mat_rot.FromEulerAnglesXYZ(deg2rad(pAngle_X), deg2rad(pAngle_Y), deg2rad(pAngle_Z));
	mHelper_Camera.Rotation_AroundCamera *= mat_rot;
}

void CGLView::Camera_Translate(const GLfloat pTranslate_X, const GLfloat pTranslate_Y, const GLfloat pTranslate_Z)
{
aiVector3D vect_tr(pTranslate_X, pTranslate_Y, pTranslate_Z);

	vect_tr *= mHelper_Camera.Rotation_AroundCamera;
	mHelper_Camera.Translation_ToScene += vect_tr;
}
