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

/** @file SceneAnimator.h
 *  Manages animations for a given scene and calculates present
 *  transformations for all nodes
 */

#ifndef AV_SCENEANIMATOR_H_INCLUDED
#define AV_SCENEANIMATOR_H_INCLUDED

#include <map>

namespace AssimpView    {

// ---------------------------------------------------------------------------------
/** A little tree structure to match the scene's node structure, but holding
 *  additional data. Needs to be public to allow using it in templates at
 *  certain compilers.
 */
struct SceneAnimNode
{
    std::string mName;
    SceneAnimNode* mParent;
    std::vector<SceneAnimNode*> mChildren;

    //! most recently calculated local transform
    aiMatrix4x4 mLocalTransform;

    //! same, but in world space
    aiMatrix4x4 mGlobalTransform;

    //!  index in the current animation's channel array. -1 if not animated.
    size_t mChannelIndex;

    //! Default construction
    SceneAnimNode()
    : mName()
    , mParent(NULL)
    , mChannelIndex(-1) {
        // empty
    }

    //! Construction from a given name
    SceneAnimNode( const std::string& pName)
    : mName( pName)
    , mParent(NULL)
    , mChannelIndex( -1 ) {
        // empty
    }

    //! Destruct all children recursively
    ~SceneAnimNode() {
        for (std::vector<SceneAnimNode*>::iterator it = mChildren.begin(); it != mChildren.end(); ++it) {
            delete *it;
        }
    }
};

// ---------------------------------------------------------------------------------
/** Calculates the animated node transformations for a given scene and timestamp.
 *
 *  Create an instance for a aiScene you want to animate and set the current animation
 *  to play. You can then have the instance calculate the current pose for all nodes
 *  by calling Calculate() for a given timestamp. After this you can retrieve the
 *  present transformation for a given node by calling GetLocalTransform() or
 *  GetGlobalTransform(). A full set of bone matrices can be retrieved by
 *  GetBoneMatrices() for a given mesh.
 */
class SceneAnimator
{
public:

    // ----------------------------------------------------------------------------
    /** Constructor for a given scene.
     *
     * The object keeps a reference to the scene during its lifetime, but
     * ownership stays at the caller.
     * @param pScene The scene to animate.
     * @param pAnimIndex [optional] Index of the animation to play. Assumed to
     *  be 0 if not given.
     */
    SceneAnimator( const aiScene* pScene, size_t pAnimIndex = 0);

    /** Destructor */
    ~SceneAnimator();

    // ----------------------------------------------------------------------------
    /** Sets the animation to use for playback. This also recreates the internal
     * mapping structures, which might take a few cycles.
     * @param pAnimIndex Index of the animation in the scene's animation array
     */
    void SetAnimIndex( size_t pAnimIndex);

    // ----------------------------------------------------------------------------
    /** Calculates the node transformations for the scene. Call this to get
     * uptodate results before calling one of the getters.
     * @param pTime Current time. Can be an arbitrary range.
     */
    void Calculate( double pTime);

    // ----------------------------------------------------------------------------
    /** Retrieves the most recent local transformation matrix for the given node.
     *
     * The returned matrix is in the node's parent's local space, just like the
     * original node's transformation matrix. If the node is not animated, the
     * node's original transformation is returned so that you can safely use or
     * assign it to the node itsself. If there is no node with the given name,
     * the identity matrix is returned. All transformations are updated whenever
     * Calculate() is called.
     * @param pNodeName Name of the node
     * @return A reference to the node's most recently calculated local
     *   transformation matrix.
     */
    const aiMatrix4x4& GetLocalTransform( const aiNode* node) const;

    // ----------------------------------------------------------------------------
    /** Retrieves the most recent global transformation matrix for the given node.
     *
     * The returned matrix is in world space, which is the same coordinate space
     * as the transformation of the scene's root node. If the node is not animated,
     * the node's original transformation is returned so that you can safely use or
     * assign it to the node itsself. If there is no node with the given name, the
     * identity matrix is returned. All transformations are updated whenever
     * Calculate() is called.
     * @param pNodeName Name of the node
     * @return A reference to the node's most recently calculated global
     *   transformation matrix.
     */
    const aiMatrix4x4& GetGlobalTransform( const aiNode* node) const;

    // ----------------------------------------------------------------------------
    /** Calculates the bone matrices for the given mesh.
     *
     * Each bone matrix transforms from mesh space in bind pose to mesh space in
     * skinned pose, it does not contain the mesh's world matrix. Thus the usual
     * matrix chain for using in the vertex shader is
     * @code
     * boneMatrix * worldMatrix * viewMatrix * projMatrix
     * @endcode
     * @param pNode The node carrying the mesh.
     * @param pMeshIndex Index of the mesh in the node's mesh array. The NODE's
     *   mesh array, not  the scene's mesh array! Leave out to use the first mesh
     *   of the node, which is usually also the only one.
     * @return A reference to a vector of bone matrices. Stays stable till the
     *   next call to GetBoneMatrices();
     */
    const std::vector<aiMatrix4x4>& GetBoneMatrices( const aiNode* pNode,
        size_t pMeshIndex = 0);


    // ----------------------------------------------------------------------------
    /** @brief Get the current animation index
     */
    size_t CurrentAnimIndex() const {
        return mCurrentAnimIndex;
    }

    // ----------------------------------------------------------------------------
    /** @brief Get the current animation or NULL
     */
    aiAnimation* CurrentAnim() const {
        return  mCurrentAnimIndex < mScene->mNumAnimations ? mScene->mAnimations[ mCurrentAnimIndex ] : NULL;
    }

protected:

    /** Recursively creates an internal node structure matching the
     *  current scene and animation.
     */
    SceneAnimNode* CreateNodeTree( aiNode* pNode, SceneAnimNode* pParent);

    /** Recursively updates the internal node transformations from the
     *  given matrix array
     */
    void UpdateTransforms( SceneAnimNode* pNode, const std::vector<aiMatrix4x4>& pTransforms);

    /** Calculates the global transformation matrix for the given internal node */
    void CalculateGlobalTransform( SceneAnimNode* pInternalNode);

protected:
    /** The scene we're operating on */
    const aiScene* mScene;

    /** Current animation index */
    size_t mCurrentAnimIndex;

    /** The AnimEvaluator we use to calculate the current pose for the current animation */
    AnimEvaluator* mAnimEvaluator;

    /** Root node of the internal scene structure */
    SceneAnimNode* mRootNode;

    /** Name to node map to quickly find nodes by their name */
    typedef std::map<const aiNode*, SceneAnimNode*> NodeMap;
    NodeMap mNodesByName;

    /** Name to node map to quickly find nodes for given bones by their name */
    typedef std::map<const char*, const aiNode*> BoneMap;
    BoneMap mBoneNodesByName;

    /** Array to return transformations results inside. */
    std::vector<aiMatrix4x4> mTransforms;

    /** Identity matrix to return a reference to in case of error */
    aiMatrix4x4 mIdentityMatrix;
};

} // end of namespace AssimpView

#endif // AV_SCENEANIMATOR_H_INCLUDED