/// \file   glview.hpp
/// \brief  OpenGL visualisation.
/// \author smal.root@gmail.com
/// \date   2016

#pragma once

// Header files, Qt.
#include <QtOpenGL>

// Header files Assimp
#include <assimp/scene.h>

/// \class CGLView
/// Class which hold and render scene.
class CGLView : public QGLWidget
{
	Q_OBJECT

	/**********************************/
	/************* Types **************/
	/**********************************/

private:

	/// \struct SBBox
	/// Bounding box for object.
	struct SBBox
	{
		aiVector3D Minimum;///< Minimum values of coordinates.
		aiVector3D Maximum;///< Maximum values of coordinates.
	};

	/// \struct SHelper_Mesh
	/// Helper object for fast rendering of mesh (\ref aiMesh).
	struct SHelper_Mesh
	{
		const size_t Quantity_Point;///< Quantity of points.
		const size_t Quantity_Line;///< Quantity of lines.
		const size_t Quantity_Triangle;///< Quantity of triangles.
		GLuint* Index_Point;///< Array of indices for drawing points.
		GLuint* Index_Line;///< Array of indices for drawing lines.
		GLuint* Index_Triangle;///< Array of indices for drawing triangles.

		const SBBox BBox;///< BBox of mesh.

		/// \fn explicit SHelper_Mesh(const size_t pQuantity_Point, const size_t pQuantity_Line, const size_t pQuantity_Triangle, const SBBox& pBBox = {{0, 0, 0}, {0, 0, 0}})
		/// Constructor.
		/// \param [in] pQuantity_Point - quantity of points.
		/// \param [in] pQuantity_Line - quantity of lines.
		/// \param [in] pQuantity_Triangle - quantity of triangles.
		/// \param [in] pBBox - BBox of mesh.
		explicit SHelper_Mesh(const size_t pQuantity_Point, const size_t pQuantity_Line, const size_t pQuantity_Triangle, const SBBox& pBBox = {{0, 0, 0}, {0, 0, 0}});

		/// \fn ~SHelper_Mesh()
		/// Destructor.
		~SHelper_Mesh();
	};

	/// \struct SHelper_Camera
	/// Information about position of the camera in space.
	struct SHelper_Camera
	{
		aiVector3D Position;///< Coordinates of the camera.
		aiVector3D Target;///< Target point of the camera.
		// Transformation path:
		// set Camera -> Rotation_AroundCamera -> Translation_ToScene -> Rotation_Scene -> draw Scene
		aiMatrix4x4 Rotation_AroundCamera;///< Rotation matrix which set rotation angles of the scene around camera.
		aiMatrix4x4 Rotation_Scene;///< Rotation matrix which set rotation angles of the scene around own center.
		aiVector3D Translation_ToScene;///< Translation vector from camera to the scene.

		/// \fn void SetDefault()
		/// Set default parameters of camera.
		void SetDefault();
	};

public:

	/// \enum ELightType
	/// Type of light source.
	enum class ELightType { Directional, Point, Spot };

	/// \struct SLightParameters
	/// Parameters of light source.
	struct SLightParameters
	{
		aiLightSourceType Type;///< Type of light source.

		aiColor4D Ambient;///< Ambient RGBA intensity of the light.
		aiColor4D Diffuse;///< Diffuse RGBA intensity of the light.
		aiColor4D Specular;///< Specular RGBA intensity of the light.

		union UFor
		{
			/// \struct SDirectional
			/// Parameters of directional light source.
			struct SDirectional
			{
				aiVector3D Direction;

				SDirectional() {}
			} Directional;

			/// \struct SPoint
			/// Parameters of point light source.
			struct SPoint
			{
				aiVector3D Position;
				GLfloat Attenuation_Constant;
				GLfloat Attenuation_Linear;
				GLfloat Attenuation_Quadratic;

				SPoint() {}
			} Point;

			/// \struct SSpot
			/// Parameters of spot light source.
			struct SSpot
			{
				aiVector3D Position;
				GLfloat Attenuation_Constant;
				GLfloat Attenuation_Linear;
				GLfloat Attenuation_Quadratic;
				aiVector3D Direction;
				GLfloat CutOff;

				SSpot() {}
			} Spot;

			UFor() {}
		} For;

		SLightParameters() {}
	};

	/**********************************/
	/************ Variables ***********/
	/**********************************/

private:

	// Scene
	const aiScene* mScene = nullptr;///< Copy of pointer to scene (\ref aiScene).
	SBBox mScene_BBox;///< Bounding box of scene.
	aiVector3D mScene_Center;///< Coordinates of center of the scene.
	bool mScene_DrawBBox = false;///< Flag which control drawing scene BBox.
	// Meshes
	size_t mHelper_Mesh_Quantity = 0;///< Quantity of meshes in scene.
	SHelper_Mesh** mHelper_Mesh = nullptr;///< Array of pointers to helper objects for drawing mesh. Sequence of meshes are equivalent to \ref aiScene::mMeshes.
	// Cameras
	SHelper_Camera mHelper_Camera;///< Information about current camera placing in space.
	SHelper_Camera mHelper_CameraDefault;///< Information about default camera initial placing in space.
	bool mCamera_DefaultAdded = true;///< If true then scene has no defined cameras and default was added, if false - scene has defined cameras.
	GLdouble mCamera_FOVY = 45.0;///< Specifies the field of view angle, in degrees, in the y direction.
	GLdouble mCamera_Viewport_AspectRatio;///< Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	// Lighting
	bool mLightingEnabled = false;///< If true then OpenGL lighting is enabled (glEnable(GL_LIGHTING)), if false - disabled.
	// Textures
	///TODO: map is goooood, but not for case when one image can be used in different materials with difference in: texture transformation, targeting of the
	/// texture (ambient or emission, or even height map), texture properties.
	QMap<QString, GLuint> mTexture_IDMap;///< Map image filenames to textures ID's.

	/**********************************/
	/************ Functions ***********/
	/**********************************/

private:

	// Why in some cases pointers are used? Because: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=36566
	template<typename TArg> void AssignIfLesser(TArg* pBaseValue, const TArg pTestValue) { if(pTestValue < *pBaseValue) *pBaseValue = pTestValue; }
	template<typename TArg> void AssignIfGreater(TArg* pBaseValue, const TArg pTestValue) { if(pTestValue > *pBaseValue) *pBaseValue = pTestValue; }

	template<typename TArg> void AssignIfLesser(TArg& pBaseValue, const TArg pTestValue) { if(pTestValue < pBaseValue) pBaseValue = pTestValue; }
	template<typename TArg> void AssignIfGreater(TArg& pBaseValue, const TArg pTestValue) { if(pTestValue > pBaseValue) pBaseValue = pTestValue; }

	/// \fn void Material_Apply(const aiMaterial* pMaterial)
	/// Enable pointed material.
	/// \param [in] pMaterial - pointer to material which must be used.
	void Material_Apply(const aiMaterial* pMaterial);

	/// \fn void Matrix_NodeToRoot(const aiNode* pNode, aiMatrix4x4& pOutMatrix)
	/// Calculate matrix for transforming coordinates from pointed node to root node (read as "global coordinate system").
	/// \param [in] pNode - pointer initial node from which relative coordintaes will be taken,
	/// \param [out] pOutMatrix - matrix for transform relative coordinates in \ref pNode to coordinates in root node (\ref aiScene::mRootNode).
	void Matrix_NodeToRoot(const aiNode* pNode, aiMatrix4x4& pOutMatrix);

	/// \fn void ImportTextures()
	/// Import textures.
	/// \param [in] pScenePath - path to the file of the scene.
	void ImportTextures(const QString& pScenePath);

	/// \fn void BBox_GetForNode(const aiNode& pNode, const aiMatrix4x4& pParentNode_TransformationMatrix, SBBox& pNodeBBox, bool& pFirstAssign)
	/// Calculate BBox for pointed node. Function walk thru child nodes and apply all transformations.
	/// \param [in] pNode - reference to node for which needed BBox.
	/// \param [in] pParent_TransformationMatrix - reference to parent (parent for pNode) transformation matrix.
	/// \param [in,out] pNodeBBox - reference to where pNode BBox will be placed. It will expanded by child nodes BBoxes.
	/// \param [in] pFirstAssign - means that pNodeBBox not contain valid BBox at now and assign ('=') will used for setting new value, If
	/// false then \ref BBox_Extend will be used for setting new BBox.
	void BBox_GetForNode(const aiNode& pNode, const aiMatrix4x4& pParent_TransformationMatrix, SBBox& pNodeBBox, bool& pFirstAssign);

	/// \fn void BBox_Extend(const SBBox& pChild, SBBox& pParent)
	/// Check and if need - extend current node BBox with BBox of child node.
	/// \param [in] pChild - reference to BBox which used for extend parent BBox.
	/// \param [in.out] pParent - BBox which will be extended using child BBox.
	void BBox_Extend(const SBBox& pChild, SBBox& pParent);

	/// \fn void BBox_GetVertices(const SBBox& pBBox, aiVector3D pVertices[8])
	/// Get vertices of a parallelepiped which is described by BBox.
	/// \param [in] pBBox - input BBox.
	/// \param [out] pVertices - array of vertices.
	void BBox_GetVertices(const SBBox& pBBox, aiVector3D pVertices[8]);

	/// \fn void BBox_GetFromVertices(const aiVector3D* pVertices, const size_t pVerticesQuantity, SBBox& pBBox)
	/// Calculate BBox for vertices array.
	/// \param [in] pVertices - vertices array.
	/// \param [in] pVerticesQuantity - quantity of vertices in array. If 0 then pBBox will be assigned with {{0, 0, 0}, {0, 0, 0}}.
	/// \param [out] pBBox - calculated BBox.
	void BBox_GetFromVertices(const aiVector3D* pVertices, const size_t pVerticesQuantity, SBBox& pBBox);

	/********************************************************************/
	/************************ Logging functions *************************/
	/********************************************************************/

	/// \fn void LogInfo(const QString& pMessage)
	/// Add message with severity "Warning" to log.
	void LogInfo(const QString& pMessage);

	/// \fn void LogError(const QString& pMessage)
	/// Add message with severity "Error" to log.
	void LogError(const QString& pMessage);

	/********************************************************************/
	/************************** Draw functions **************************/
	/********************************************************************/

	/// \fn void Draw_Node(const aiNode* pNode)
	/// Apply node transformation and draw meshes assigned to this node.
	/// \param [in] pNode - pointer to node for drawing (\ref aiNode).
	void Draw_Node(const aiNode* pNode);

	/// \fn void Draw_Mesh(const size_t pMesh_Index)
	/// Draw mesh.
	/// \param [in] pMesh_Index - index of mesh which must be drawn. Index point to mesh in \ref mHelper_Mesh.
	void Draw_Mesh(const size_t pMesh_Index);

	/// \fn void Draw_BBox(const SBBox& pBBox)
	/// Draw bounding box using lines.
	/// \param [in] pBBox - bounding box for drawing.
	void Draw_BBox(const SBBox& pBBox);

	/********************************************************************/
	/*********************** Overrided functions ************************/
	/********************************************************************/

protected:
    void drawCoordSystem();
	/// \fn void initializeGL() override
	/// Overrided function for initialise OpenGL.
	void initializeGL() override;

	/// \fn void resizeGL(int pWidth, int pHeight) override
	/// \param [in] pWidth - new width of viewport.
	/// \param [in] pHeight - new height of viewport.
	void resizeGL(int pWidth, int pHeight) override;

	/// \fn void paintGL() override
	/// Overrided function for rendering.
	void paintGL() override;

public:

	/********************************************************************/
	/********************** Constructor/Destructor **********************/
	/********************************************************************/

	/// \fn explicit CGLView(QWidget* pParent)
	/// Constructor.
	/// \param [in] pParent - parent widget.
	explicit CGLView(QWidget* pParent);

	/// \fn virtual ~CGLView()
	/// Destructor.
	virtual ~CGLView();

	/********************************************************************/
	/********************* Scene control functions **********************/
	/********************************************************************/

	/// \fn void FreeScene()
	/// Free all helper objects data.
	void FreeScene();

	/// \fn void SetScene(const aiScene* pScene)
	/// Set scene for rendering.
	/// \param [in] pScene - pointer to scene.
	/// \param [in] pScenePath - path to the file of the scene.
	void SetScene(const aiScene* pScene, const QString& pScenePath);

	/// \fn void Enable_SceneBBox(const bool pEnable)
	/// Enable drawing scene bounding box.
	/// \param [in] pEnable - if true then bbox will be drawing, if false - will not be drawing.
	void Enable_SceneBBox(const bool pEnable) { mScene_DrawBBox = pEnable; }

	/// \fn void Enable_Textures(const bool pEnable)
	/// Control textures drawing.
	/// \param [in] pEnable - if true then enable textures, false - disable textures.
	void Enable_Textures(const bool pEnable);

	/********************************************************************/
	/******************** Lighting control functions ********************/
	/********************************************************************/

	/// \fn void Lighting_Enable()
	/// Enable OpenGL lighting.
	void Lighting_Enable();

	/// \fn void Lighting_Disable()
	/// Disable OpenGL lighting.
	void Lighting_Disable();

	/// \fn void Lighting_EditSource(const size_t pLightNumber, const SLightParameters& pLightParameters)
	/// Edit light source properties.
	/// \param [in] pLightNumber - light source number. \ref aiScene::mLights.
	/// \param [in] pLightParameters - light source parameters.
	void Lighting_EditSource(const size_t pLightNumber, const SLightParameters& pLightParameters);///TODO: function set

	/// \fn void Lighting_EnableSource(const size_t pLightNumber)
	/// Enable light source.
	/// \param [in] pLightNumber - light source number. \ref aiScene::mLights.
	void Lighting_EnableSource(const size_t pLightNumber);

	///void Lighting_DisableSource(const size_t pLightNumber)
	/// Disable light source,
	/// \param [in] pLightNumber - light source number. \ref aiScene::mLights.
	void Lighting_DisableSource(const size_t pLightNumber);

	/********************************************************************/
	/******************** Cameras control functions *********************/
	/********************************************************************/

	/// \fn void Camera_Set(const size_t pCameraNumber)
	/// Set view from pointed camera.
	/// \param [in] pCamera_Index - index of the camera (\ref aiScene::mCameras).
	void Camera_Set(const size_t pCameraNumber);

	/// \fn void Camera_RotateScene(const GLfloat pAngle_X, const GLfloat pAngle_Y, const GLfloat pAngle_Z)
	/// Rotate scene around axisees.
	/// \param [in] pAngle_X - specifies the angle of rotation around axis oX, in degrees.
	/// \param [in] pAngle_Y - specifies the angle of rotation around axis oY, in degrees.
	/// \param [in] pAngle_Z - specifies the angle of rotation around axis oZ, in degrees.
	void Camera_RotateScene(const GLfloat pAngle_X, const GLfloat pAngle_Y, const GLfloat pAngle_Z);

	/// \fn void Camera_Rotate(const GLfloat pAngle_X, const GLfloat pAngle_Y, const GLfloat pAngle_Z)
	/// Rotate camera around axisees.
	/// \param [in] pAngle_X - specifies the angle of rotation around axis oX, in degrees.
	/// \param [in] pAngle_Y - specifies the angle of rotation around axis oY, in degrees.
	/// \param [in] pAngle_Z - specifies the angle of rotation around axis oZ, in degrees.
	void Camera_Rotate(const GLfloat pAngle_X, const GLfloat pAngle_Y, const GLfloat pAngle_Z);

	/// \fn void Camera_Translate(const size_t pTranslate_X, const size_t pTranslate_Y, const size_t pTranslate_Z)
	/// Translate camera along axises. In local coordinates.
	/// \param [in] pTranslate_X - specifies the X coordinate of translation vector.
	/// \param [in] pTranslate_Y - specifies the Y coordinate of translation vector.
	/// \param [in] pTranslate_Z - specifies the Z coordinate of translation vector.
	void Camera_Translate(const GLfloat pTranslate_X, const GLfloat pTranslate_Y, const GLfloat pTranslate_Z);

signals:

	/// \fn void Paint_Finished(const size_t pPaintTime, const GLfloat pDistance)
	///< Signal. Emits when execution of \ref paintGL is end.
	/// \param [out] pPaintTime_ms - time spent for rendering, in milliseconds.
	/// \param [out] pDistance - distance between current camera and center of the scene. \sa SHelper_Camera::Translation_ToScene.
	void Paint_Finished(const size_t pPaintTime_ms, const GLfloat pDistance);

	/// \fn void SceneObject_Camera(const QString& pName)
	/// Signal. Emit for every camera found in scene. Also for default camera.
	/// \param [out] pName - name of the camera.
	void SceneObject_Camera(const QString& pName);

	/// \fn void SceneObject_LightSource(const QString& pName)
	/// Signal. Emit for every light source found in scene. Also for default light source.
	/// \param [out] pName - name of the light source.
	void SceneObject_LightSource(const QString& pName);
};// class CGLView
