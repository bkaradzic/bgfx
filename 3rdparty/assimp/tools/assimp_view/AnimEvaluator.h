/** Calculates a pose for a given time of an animation */
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

#ifndef AV_ANIMEVALUATOR_H_INCLUDED
#define AV_ANIMEVALUATOR_H_INCLUDED

#include <tuple>
#include <vector>

namespace AssimpView
{

/** Calculates transformations for a given timestamp from a set of animation tracks. Not directly useful,
 * better use the AnimPlayer class.
 */
class AnimEvaluator
{
public:
    /** Constructor on a given animation. The animation is fixed throughout the lifetime of
     * the object.
     * @param pAnim The animation to calculate poses for. Ownership of the animation object stays
     *   at the caller, the evaluator just keeps a reference to it as long as it persists.
     */
    AnimEvaluator( const aiAnimation* pAnim);

    /** Evaluates the animation tracks for a given time stamp. The calculated pose can be retrieved as a
     * array of transformation matrices afterwards by calling GetTransformations().
     * @param pTime The time for which you want to evaluate the animation, in seconds. Will be mapped into the animation cycle, so
     *   it can be an arbitrary value. Best use with ever-increasing time stamps.
     */
    void Evaluate( double pTime);

    /** Returns the transform matrices calculated at the last Evaluate() call. The array matches the mChannels array of
     * the aiAnimation. */
    const std::vector<aiMatrix4x4>& GetTransformations() const { return mTransforms; }

protected:
    /** The animation we're working on */
    const aiAnimation* mAnim;

    /** At which frame the last evaluation happened for each channel.
     * Useful to quickly find the corresponding frame for slightly increased time stamps
     */
    double mLastTime;
    std::vector<std::tuple<unsigned int, unsigned int, unsigned int> > mLastPositions;

    /** The array to store the transformations results of the evaluation */
    std::vector<aiMatrix4x4> mTransforms;
};

} // end of namespace AssimpView

#endif // AV_ANIMEVALUATOR_H_INCLUDED
