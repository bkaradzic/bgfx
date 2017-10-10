/*
---------------------------------------------------------------------------
Open Asset Import Library (assimp)
---------------------------------------------------------------------------

Copyright (c) 2006-2012, assimp team

All rights reserved.

Redistribution and use of this software in source and binary forms,
with or without modification, are permitted provided that the following
conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the assimp team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the assimp team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------------
*/

#if (!defined AV_DISPLAY_H_INCLUDED)
#define AV_DISPLAY_H_INCLUDE

#include <windows.h>
#include <shellapi.h>
#include <commctrl.h>

// see CDisplay::m_aiImageList
#define AI_VIEW_IMGLIST_NODE            0x0
#define AI_VIEW_IMGLIST_MATERIAL        0x1
#define AI_VIEW_IMGLIST_TEXTURE         0x2
#define AI_VIEW_IMGLIST_TEXTURE_INVALID 0x3
#define AI_VIEW_IMGLIST_MODEL           0x4

namespace AssimpView
{

    //-------------------------------------------------------------------------------
    /* Corresponds to the "Display" combobox in the UI
    */
    //-------------------------------------------------------------------------------
    class CDisplay
    {
    private:

        // helper class
        struct Info
        {
            Info( D3DXVECTOR4* p1,
                AssetHelper::MeshHelper* p2,
                const char* p3 )
                : pclrColor( p1 ), pMesh( p2 ), szShaderParam( p3 ) {}

            D3DXVECTOR4* pclrColor;
            AssetHelper::MeshHelper* pMesh;
            const char* szShaderParam;
        };

        // default constructor
        CDisplay()
            : m_iViewMode( VIEWMODE_FULL ),
            m_pcCurrentTexture( NULL ),
            m_pcCurrentNode( NULL ),
            m_pcCurrentMaterial( NULL ),
            m_hImageList( NULL ),
            m_hRoot( NULL ),
            m_fTextureZoom( 1000.0f )
        {
            this->m_aiImageList[ 0 ] = 0;
            this->m_aiImageList[ 1 ] = 1;
            this->m_aiImageList[ 2 ] = 2;
            this->m_aiImageList[ 3 ] = 3;
            this->m_aiImageList[ 4 ] = 4;

            this->m_avCheckerColors[ 0 ].x = this->m_avCheckerColors[ 0 ].y = this->m_avCheckerColors[ 0 ].z = 0.4f;
            this->m_avCheckerColors[ 1 ].x = this->m_avCheckerColors[ 1 ].y = this->m_avCheckerColors[ 1 ].z = 0.6f;
        }

    public:


        //------------------------------------------------------------------
        enum
        {
            // the full model is displayed
            VIEWMODE_FULL,

            // a material is displayed on a simple spjere as model
            VIEWMODE_MATERIAL,

            // a texture with an UV set mapped on it is displayed
            VIEWMODE_TEXTURE,

            // a single node in the scenegraph is displayed
            VIEWMODE_NODE,
        };


        //------------------------------------------------------------------
        // represents a texture in the tree view
        struct TextureInfo
        {
            // texture info
            IDirect3DTexture9** piTexture;

            // Blend factor of the texture
            float fBlend;

            // blend operation for the texture
            aiTextureOp eOp;

            // UV index for the texture
            unsigned int iUV;

            // Associated tree item
            HTREEITEM hTreeItem;

            // Original path to the texture
            std::string szPath;

            // index of the corresponding material
            unsigned int iMatIndex;

            // type of the texture
            unsigned int iType;
        };

        //------------------------------------------------------------------
        // represents a node in the tree view
        struct NodeInfo
        {
            // node object
            aiNode* psNode;

            // corresponding tree view item
            HTREEITEM hTreeItem;
        };

        //------------------------------------------------------------------
        // represents a mesh in the tree view
        struct MeshInfo
        {
            // the mesh object
            aiMesh* psMesh;

            // corresponding tree view item
            HTREEITEM hTreeItem;
        };

        //------------------------------------------------------------------
        // represents a material in the tree view
        struct MaterialInfo
        {
            // material index
            unsigned int iIndex;

            // material object
            aiMaterial* psMaterial;

            // ID3DXEffect interface
            ID3DXEffect* piEffect;

            // corresponding tree view item
            HTREEITEM hTreeItem;
        };

        //------------------------------------------------------------------
        // Singleton accessors
        static CDisplay s_cInstance;
        inline static CDisplay& Instance()
        {
            return s_cInstance;
        }


        //------------------------------------------------------------------
        // Called during the render loop. Renders the scene (including the
        // HUD etc) in the current view mode
        int OnRender();

        //------------------------------------------------------------------
        // called when the user selects another item in the "Display" tree
        // view the method determines the new view mode and performs all
        // required operations
        // \param p_hTreeItem Selected tree view item
        int OnSetup( HTREEITEM p_hTreeItem );

        //------------------------------------------------------------------
        // Variant 1: Render the full scene with the asset
        int RenderFullScene();

#if 0
        //------------------------------------------------------------------
        // Variant 2: Render only a part of the scene. One node to
        // be exact
        int RenderScenePart();
#endif

        //------------------------------------------------------------------
        // Variant 3: Render a large sphere and map a given material on it
        int RenderMaterialView();

        //------------------------------------------------------------------
        // Variant 4: Render a flat plane, map a texture on it and
        // display the UV wire on it
        int RenderTextureView();

        //------------------------------------------------------------------
        // Fill the UI combobox with a list of all supported view modi
        //
        // The display modes are added in order
        int FillDisplayList( void );

        //------------------------------------------------------------------
        // Add a material and all sub textures to the display mode list
        // hRoot - Handle to the root of the tree view
        // iIndex - Material index
        int AddMaterialToDisplayList( HTREEITEM hRoot,
            unsigned int iIndex );

        //------------------------------------------------------------------
        // Add a texture to the display list
        // pcMat - material containing the texture
        // hTexture - Handle to the material tree item
        // szPath - Path to the texture
        // iUVIndex - UV index to be used for the texture
        // fBlendFactor - Blend factor to be used for the texture
        // eTextureOp - texture operation to be used for the texture
        int AddTextureToDisplayList( unsigned int iType,
            unsigned int iIndex,
            const aiString* szPath,
            HTREEITEM hFX,
            unsigned int iUVIndex = 0,
            const float fBlendFactor = 0.0f,
            aiTextureOp eTextureOp = aiTextureOp_Multiply,
            unsigned int iMesh = 0 );

        //------------------------------------------------------------------
        // Add a node to the display list
        // Recusrivly adds all subnodes as well
        // iIndex - Index of the node in the parent's child list
        // iDepth - Current depth of the node
        // pcNode - Node object
        // hRoot - Parent tree view node
        int AddNodeToDisplayList(
            unsigned int iIndex,
            unsigned int iDepth,
            aiNode* pcNode,
            HTREEITEM hRoot );

        //------------------------------------------------------------------
        // Add a mesh to the display list
        // iIndex - Index of the mesh in the scene's mesh list
        // hRoot - Parent tree view node
        int AddMeshToDisplayList(
            unsigned int iIndex,
            HTREEITEM hRoot );

        //------------------------------------------------------------------
        // Load the image list for the tree view item
        int LoadImageList( void );

        //------------------------------------------------------------------
        // Expand all nodes in the tree
        int ExpandTree();

        //------------------------------------------------------------------
        // Fill the UI combobox with a list of all supported animations
        // The animations are added in order
        int FillAnimList( void );

        //------------------------------------------------------------------
        // Clear the combox box containing the list of animations
        int ClearAnimList( void );

        //------------------------------------------------------------------
        // Clear the combox box containing the list of scenegraph items
        int ClearDisplayList( void );

        //------------------------------------------------------------------
        // Fill in the default statistics
        int FillDefaultStatistics( void );

        //------------------------------------------------------------------
        // Called by LoadAsset()
        // reset the class instance to the default values
        int Reset( void );

        //------------------------------------------------------------------
        // Replace the texture that is current selected with
        // a new texture
        int ReplaceCurrentTexture( const char* szPath );

        //------------------------------------------------------------------
        // Display the context menu (if there) for the specified tree item
        // hItem Valid tree view item handle
        int ShowTreeViewContextMenu( HTREEITEM hItem );

        //------------------------------------------------------------------
        // Event handling for pop-up menus displayed by th tree view
        int HandleTreeViewPopup( WPARAM wParam, LPARAM lParam );

        //------------------------------------------------------------------
        // Enable animation-related parts of the UI
        int EnableAnimTools( BOOL hm );

        //------------------------------------------------------------------
        // setter for m_iViewMode
        inline void SetViewMode( unsigned int p_iNew )
        {
            this->m_iViewMode = p_iNew;
        }

        //------------------------------------------------------------------
        // getter for m_iViewMode
        inline unsigned int GetViewMode()
        {
            return m_iViewMode;
        }

        //------------------------------------------------------------------
        // change the texture view's zoom factor
        inline void SetTextureViewZoom( float f )
        {
            // FIX: Removed log(), seems to make more problems than it fixes
            this->m_fTextureZoom += f * 15;
            if( this->m_fTextureZoom < 0.05f )this->m_fTextureZoom = 0.05f;
        }

        //------------------------------------------------------------------
        // change the texture view's offset on the x axis
        inline void SetTextureViewOffsetX( float f )
        {
            this->m_vTextureOffset.x += f;
        }

        //------------------------------------------------------------------
        // change the texture view's offset on the y axis
        inline void SetTextureViewOffsetY( float f )
        {
            this->m_vTextureOffset.y += f;
        }

        //------------------------------------------------------------------
        // add a new texture to the list
        inline void AddTexture( const TextureInfo& info )
        {
            this->m_asTextures.push_back( info );
        }

        //------------------------------------------------------------------
        // add a new node to the list
        inline void AddNode( const NodeInfo& info )
        {
            this->m_asNodes.push_back( info );
        }

        //------------------------------------------------------------------
        // add a new mesh to the list
        inline void AddMesh( const MeshInfo& info )
        {
            this->m_asMeshes.push_back( info );
        }

        //------------------------------------------------------------------
        // add a new material to the list
        inline void AddMaterial( const MaterialInfo& info )
        {
            this->m_asMaterials.push_back( info );
        }

        //------------------------------------------------------------------
        // set the primary color of the checker pattern background
        inline void SetFirstCheckerColor( D3DXVECTOR4 c )
        {
            this->m_avCheckerColors[ 0 ] = c;
        }

        //------------------------------------------------------------------
        // set the secondary color of the checker pattern background
        inline void SetSecondCheckerColor( D3DXVECTOR4 c )
        {
            this->m_avCheckerColors[ 1 ] = c;
        }

        //------------------------------------------------------------------
        // get the primary color of the checker pattern background
        inline const D3DXVECTOR4* GetFirstCheckerColor() const
        {
            return &this->m_avCheckerColors[ 0 ];
        }

        //------------------------------------------------------------------
        // get the secondary color of the checker pattern background
        inline const D3DXVECTOR4* GetSecondCheckerColor() const
        {
            return &this->m_avCheckerColors[ 1 ];
        }

    private:

        //------------------------------------------------------------------
        // Render a screen-filling square using the checker pattern shader
        int RenderPatternBG();

        //------------------------------------------------------------------
        // Render a given node in the scenegraph
        // piNode Node to be rendered
        // piMatrix Current transformation matrix
        // bAlpha Render alpha or opaque objects only?
        int RenderNode( aiNode* piNode, const aiMatrix4x4& piMatrix,
            bool bAlpha = false );

        //------------------------------------------------------------------
        // Setup the camera for the stereo view rendering mode
        int SetupStereoView();

        //------------------------------------------------------------------
        // Render the second view (for the right eye) in stereo mod
        // m - World matrix
        int RenderStereoView( const aiMatrix4x4& m );

        //------------------------------------------------------------------
        // Handle user input
        int HandleInput();

        //------------------------------------------------------------------
        // Handle user input for the texture viewer
        int HandleInputTextureView();

        //------------------------------------------------------------------
        // Handle user input if no asset is loaded
        int HandleInputEmptyScene();

        //------------------------------------------------------------------
        // Draw the HUD (call only if FPS mode isn't active)
        int DrawHUD();

        //------------------------------------------------------------------
        // Used by OnSetup().
        // Do everything necessary to switch to texture view mode
        int OnSetupTextureView( TextureInfo* pcNew );

        //------------------------------------------------------------------
        // Used by OnSetup().
        // Do everything necessary to switch to material view mode
        int OnSetupMaterialView( MaterialInfo* pcNew );

        //------------------------------------------------------------------
        // Used by OnSetup().
        // Do everything necessary to switch to node view mode
        int OnSetupNodeView( NodeInfo* pcNew );

        //------------------------------------------------------------------
        // Used by OnSetup().
        // Do everything necessary to switch back to normal view mode
        int OnSetupNormalView();

        //------------------------------------------------------------------
        // Used by HandleTreeViewPopup().
        int HandleTreeViewPopup2( WPARAM wParam, LPARAM lParam );

        //------------------------------------------------------------------
        // Render skeleton
        int RenderSkeleton( aiNode* piNode, const aiMatrix4x4& piMatrix,
            const aiMatrix4x4& parent );



    private:

        // view mode
        unsigned int m_iViewMode;

        // List of all textures in the display CB
        std::vector<TextureInfo> m_asTextures;

        // current texture or NULL if no texture is active
        TextureInfo* m_pcCurrentTexture;

        // List of all node in the display CB
        std::vector<NodeInfo> m_asNodes;

        // List of all node in the display CB
        std::vector<MeshInfo> m_asMeshes;

        // current Node or NULL if no Node is active
        NodeInfo* m_pcCurrentNode;

        // List of all materials in the display CB
        std::vector<MaterialInfo> m_asMaterials;

        // current material or NULL if no material is active
        MaterialInfo* m_pcCurrentMaterial;

        // indices into the image list of the "display" tree view control
        unsigned int m_aiImageList[ 5 ]; /* = {0,1,2,3,4};*/

        // Image list
        HIMAGELIST m_hImageList;

        // Root node of the tree, "Model"
        HTREEITEM m_hRoot;

        // Current zoom factor of the texture viewer
        float m_fTextureZoom;

        // Current offset (in pixels) of the texture viewer
        aiVector2D m_vTextureOffset;

        // Colors used to draw the checker pattern (for the
        // texture viewer as background )
        D3DXVECTOR4 m_avCheckerColors[ 2 ];

        // View projection matrix
        aiMatrix4x4 mViewProjection;
        aiVector3D vPos;
    };

}
#endif // AV_DISPLAY_H_INCLUDE