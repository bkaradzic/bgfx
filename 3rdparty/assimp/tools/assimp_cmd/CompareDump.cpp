/*
---------------------------------------------------------------------------
Open Asset Import Library (assimp)
---------------------------------------------------------------------------

Copyright (c) 2006-2017, assimp team


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

/** @file  CompareDump.cpp
 *  @brief Implementation of the 'assimp cmpdmp', which compares
 *    two model dumps for equality. It plays an important role
 *    in the regression test suite.
 */

#include "Main.h"
const char* AICMD_MSG_CMPDUMP_HELP =
"assimp cmpdump <actual> <expected>\n"
"\tCompare two short dumps produced with \'assimp dump <..> -s\' for equality.\n"
;

#include "../../code/assbin_chunks.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
#include "generic_inserter.hpp"
#include <map>
#include <deque>
#include <stack>
#include <sstream>
#include <iostream>
#include "../../include/assimp/ai_assert.h"

// get << for aiString
template <typename char_t, typename traits_t>
void mysprint(std::basic_ostream<char_t, traits_t>& os,  const aiString& vec)   {
    os << "[length: \'" << std::dec << vec.length << "\' content: \'"  << vec.data << "\']";
}

template <typename char_t, typename traits_t>
std::basic_ostream<char_t, traits_t>& operator<< (std::basic_ostream<char_t, traits_t>& os, const aiString& vec)    {
    return generic_inserter(mysprint<char_t,traits_t>, os, vec);
}

class sliced_chunk_iterator;
////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class  compare_fails_exception
///
/// @brief  Sentinel exception to return quickly from deeply nested control paths
////////////////////////////////////////////////////////////////////////////////////////////////////
class compare_fails_exception : public virtual std::exception {
public:

    enum {MAX_ERR_LEN = 4096};

    /* public c'tors */
    compare_fails_exception(const char* msg) {
        strncpy(mywhat,msg,MAX_ERR_LEN-1);
        strcat(mywhat,"\n");
    }

    /* public member functions */
    const char* what() const throw() {
        return mywhat;
    }

private:

    char mywhat[MAX_ERR_LEN+1];
};


#define MY_FLT_EPSILON 1e-1f
#define MY_DBL_EPSILON 1e-1
////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class  comparer_context
///
/// @brief  Record our way through the files to be compared and dump useful information if we fail.
////////////////////////////////////////////////////////////////////////////////////////////////////
class comparer_context {
    friend class sliced_chunk_iterator;

public:

    /* construct given two file handles to compare */
    comparer_context(FILE* actual,FILE* expect)
        : actual(actual)
        , expect(expect)
        , cnt_chunks(0)
    {
        ai_assert(actual);
        ai_assert(expect);

        fseek(actual,0,SEEK_END);
        lengths.push(std::make_pair(static_cast<uint32_t>(ftell(actual)),0));
        fseek(actual,0,SEEK_SET);

        history.push_back(HistoryEntry("---",PerChunkCounter()));
    }

public:


    /* set new scope */
    void push_elem(const char* msg) {
        const std::string s = msg;

        PerChunkCounter::const_iterator it = history.back().second.find(s);
        if(it != history.back().second.end()) {
            ++history.back().second[s];
        }
        else history.back().second[s] = 0;

        history.push_back(HistoryEntry(s,PerChunkCounter()));
        debug_trace.push_back("PUSH " + s);
    }

    /* leave current scope */
    void pop_elem() {
        ai_assert(history.size());
        debug_trace.push_back("POP "+ history.back().first);
        history.pop_back();
    }


    /* push current chunk length and start offset on top of stack */
    void push_length(uint32_t nl, uint32_t start) {
        lengths.push(std::make_pair(nl,start));
        ++cnt_chunks;
    }

    /* pop the chunk length stack */
    void pop_length() {
        ai_assert(lengths.size());
        lengths.pop();
    }

    /* access the current chunk length */
    uint32_t get_latest_chunk_length() {
        ai_assert(lengths.size());
        return lengths.top().first;
    }

    /* access the current chunk start offset */
    uint32_t get_latest_chunk_start() {
        ai_assert(lengths.size());
        return lengths.top().second;
    }

    /* total number of chunk headers passed so far*/
    uint32_t get_num_chunks() {
        return cnt_chunks;
    }


    /* get ACTUAL file desc. != NULL */
    FILE* get_actual() const {
        return actual;
    }

    /* get EXPECT file desc. != NULL */
    FILE* get_expect() const {
        return expect;
    }


    /* compare next T from both streams, name occurs in error messages */
    template<typename T> T cmp(const std::string& name) {
        T a,e;
        read(a,e);

        if(a != e) {
            std::stringstream ss;
            failure((ss<< "Expected " << e << ", but actual is " << a,
                ss.str()),name);
        }
    //  std::cout << name << " " << std::hex << a << std::endl;
        return a;
    }

    /* compare next num T's from both streams, name occurs in error messages */
    template<typename T> void cmp(size_t num,const std::string& name) {
        for(size_t n = 0; n < num; ++n) {
            std::stringstream ss;
            cmp<T>((ss<<name<<"["<<n<<"]",ss.str()));
    //      std::cout << name << " " << std::hex << a << std::endl;
        }
    }

    /* Bounds of an aiVector3D array (separate function
     *  because partial specializations of member functions are illegal--)*/
    template<typename T> void cmp_bounds(const std::string& name) {
        cmp<T> (name+".<minimum-value>");
        cmp<T> (name+".<maximum-value>");
    }

private:

    /* Report failure */
    AI_WONT_RETURN void failure(const std::string& err, const std::string& name) AI_WONT_RETURN_SUFFIX {
        std::stringstream ss;
        throw compare_fails_exception((ss
            << "Files are different at "
            << history.back().first
            << "."
            << name
            << ".\nError is: "
            << err
            << ".\nCurrent position in scene hierarchy is "
            << print_hierarchy(),ss.str().c_str()
            ));
    }

    /** print our 'stack' */
    std::string print_hierarchy() {
        std::stringstream ss;
        ss << "\n";

        const char* last = history.back().first.c_str();
        std::string pad;

        for(ChunkHistory::reverse_iterator rev = history.rbegin(),
            end = history.rend(); rev != end; ++rev, pad += "  ")
        {
            ss << pad << (*rev).first << "(Index: " << (*rev).second[last] << ")" << "\n";
            last = (*rev).first.c_str();
        }

        ss << std::endl << "Debug trace: "<< "\n";
        for (std::vector<std::string>::const_iterator it = debug_trace.begin(); it != debug_trace.end(); ++it) {
            ss << *it << "\n";
        }
        ss << std::flush;

        return ss.str();
    }


    /* read from both streams at the same time */
    template <typename T> void read(T& filla,T& fille) {
        if(1 != fread(&filla,sizeof(T),1,actual)) {
            EOFActual();
        }
        if(1 != fread(&fille,sizeof(T),1,expect)) {
            EOFExpect();
        }
    }

private:

    void EOFActual() {
        std::stringstream ss;
        throw compare_fails_exception((ss
            << "Unexpected EOF reading ACTUAL.\nCurrent position in scene hierarchy is "
            << print_hierarchy(),ss.str().c_str()
            ));
    }

    void EOFExpect() {
        std::stringstream ss;
        throw compare_fails_exception((ss
            << "Unexpected EOF reading EXPECT.\nCurrent position in scene hierarchy is "
            << print_hierarchy(),ss.str().c_str()
            ));
    }


    FILE *const actual, *const expect;

    typedef std::map<std::string,unsigned int> PerChunkCounter;
    typedef std::pair<std::string,PerChunkCounter> HistoryEntry;

    typedef std::deque<HistoryEntry> ChunkHistory;
    ChunkHistory history;

    std::vector<std::string> debug_trace;

    typedef std::stack<std::pair<uint32_t,uint32_t> > LengthStack;
    LengthStack lengths;

    uint32_t cnt_chunks;
};


////////////////////////////////////////////////////////////////////////////////////////////////////
/* specialization for aiString (it needs separate handling because its on-disk representation
 * differs from its binary representation in memory and can't be treated as an array of n T's.*/
template <> void comparer_context :: read<aiString>(aiString& filla,aiString& fille) {
    uint32_t lena,lene;
    read(lena,lene);

    if(lena && 1 != fread(&filla.data,lena,1,actual)) {
        EOFActual();
    }
    if(lene && 1 != fread(&fille.data,lene,1,expect)) {
        EOFExpect();
    }

    fille.data[fille.length=static_cast<unsigned int>(lene)] = '\0';
    filla.data[filla.length=static_cast<unsigned int>(lena)] = '\0';
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/* Specialization for float, uses epsilon for comparisons*/
template<> float comparer_context :: cmp<float>(const std::string& name)
{
    float a,e,t;
    read(a,e);

    if((t=fabs(a-e)) > MY_FLT_EPSILON) {
        std::stringstream ss;
        failure((ss<< "Expected " << e << ", but actual is "
            << a << " (delta is " << t << ")", ss.str()),name);
    }
    return a;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/* Specialization for double, uses epsilon for comparisons*/
template<> double comparer_context :: cmp<double>(const std::string& name)
{
    double a,e,t;
    read(a,e);

    if((t=fabs(a-e)) > MY_DBL_EPSILON) {
        std::stringstream ss;
        failure((ss<< "Expected " << e << ", but actual is "
            << a << " (delta is " << t << ")", ss.str()),name);
    }
    return a;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/* Specialization for aiVector3D */
template<> aiVector3D comparer_context :: cmp<aiVector3D >(const std::string& name)
{
    const float x = cmp<float>(name+".x");
    const float y = cmp<float>(name+".y");
    const float z = cmp<float>(name+".z");

    return aiVector3D(x,y,z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/* Specialization for aiColor4D */
template<> aiColor4D comparer_context :: cmp<aiColor4D >(const std::string& name)
{
    const float r = cmp<float>(name+".r");
    const float g = cmp<float>(name+".g");
    const float b = cmp<float>(name+".b");
    const float a = cmp<float>(name+".a");

    return aiColor4D(r,g,b,a);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/* Specialization for aiQuaternion */
template<> aiQuaternion comparer_context :: cmp<aiQuaternion >(const std::string& name)
{
    const float w = cmp<float>(name+".w");
    const float x = cmp<float>(name+".x");
    const float y = cmp<float>(name+".y");
    const float z = cmp<float>(name+".z");

    return aiQuaternion(w,x,y,z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/* Specialization for aiQuatKey */
template<> aiQuatKey comparer_context :: cmp<aiQuatKey >(const std::string& name)
{
    const double mTime = cmp<double>(name+".mTime");
    const aiQuaternion mValue = cmp<aiQuaternion>(name+".mValue");

    return aiQuatKey(mTime,mValue);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/* Specialization for aiVectorKey */
template<> aiVectorKey comparer_context :: cmp<aiVectorKey >(const std::string& name)
{
    const double mTime = cmp<double>(name+".mTime");
    const aiVector3D mValue = cmp<aiVector3D>(name+".mValue");

    return aiVectorKey(mTime,mValue);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/* Specialization for aiMatrix4x4 */
template<> aiMatrix4x4 comparer_context :: cmp<aiMatrix4x4 >(const std::string& name)
{
    aiMatrix4x4 res;
    for(unsigned int i = 0; i < 4; ++i) {
        for(unsigned int j = 0; j < 4; ++j) {
            std::stringstream ss;
            res[i][j] = cmp<float>(name+(ss<<".m"<<i<<j,ss.str()));
        }
    }

    return res;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/* Specialization for aiVertexWeight */
template<> aiVertexWeight comparer_context :: cmp<aiVertexWeight >(const std::string& name)
{
    const unsigned int mVertexId = cmp<unsigned int>(name+".mVertexId");
    const float mWeight = cmp<float>(name+".mWeight");

    return aiVertexWeight(mVertexId,mWeight);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class  sliced_chunk_iterator
///
/// @brief  Helper to iterate easily through corresponding chunks of two dumps simultaneously.
///
/// Not a *real* iterator, doesn't fully conform to the isocpp iterator spec
////////////////////////////////////////////////////////////////////////////////////////////////////
class sliced_chunk_iterator {

    friend class sliced_chunk_reader;
    sliced_chunk_iterator(comparer_context& ctx, long end)
        : ctx(ctx)
        , endit(false)
        , next(std::numeric_limits<long>::max())
        , end(end)
    {
        load_next();
    }

public:

    ~sliced_chunk_iterator() {
        fseek(ctx.get_actual(),end,SEEK_SET);
        fseek(ctx.get_expect(),end,SEEK_SET);
    }

public:

    /* get current chunk head */
    typedef std::pair<uint32_t,uint32_t> Chunk;
    const Chunk& operator*() {
        return current;
    }

    /* get to next chunk head */
    const sliced_chunk_iterator& operator++() {
        cleanup();
        load_next();
        return *this;
    }

    /* */
    bool is_end() const {
        return endit;
    }

private:

    /* get to the end of *this* chunk */
    void cleanup() {
        if(next != std::numeric_limits<long>::max()) {
            fseek(ctx.get_actual(),next,SEEK_SET);
            fseek(ctx.get_expect(),next,SEEK_SET);

            ctx.pop_length();
        }
    }

    /* advance to the next chunk */
    void load_next() {

        Chunk actual;
        size_t res=0;

        const long cur = ftell(ctx.get_expect());
        if(end-cur<8) {
            current = std::make_pair(0u,0u);
            endit = true;
            return;
        }

        res|=fread(&current.first,4,1,ctx.get_expect());
        res|=fread(&current.second,4,1,ctx.get_expect())    <<1u;
        res|=fread(&actual.first,4,1,ctx.get_actual())      <<2u;
        res|=fread(&actual.second,4,1,ctx.get_actual())     <<3u;

        if(res!=0xf) {
            ctx.failure("IO Error reading chunk head, dumps are malformed","<ChunkHead>");
        }

        if (current.first != actual.first) {
            std::stringstream ss;
            ctx.failure((ss
                <<"Chunk headers do not match. EXPECT: "
                << std::hex << current.first
                <<" ACTUAL: "
                << /*std::hex */actual.first,
                ss.str()),
                "<ChunkHead>");
        }

        if (current.first != actual.first) {
            std::stringstream ss;
            ctx.failure((ss
                <<"Chunk lengths do not match. EXPECT: "
                <<current.second
                <<" ACTUAL: "
                << actual.second,
                ss.str()),
                "<ChunkHead>");
        }

        next = cur+current.second+8;
        ctx.push_length(current.second,cur+8);
    }

    comparer_context& ctx;
    Chunk current;
    bool endit;
    long next,end;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class  sliced_chunk_reader
///
/// @brief  Helper to iterate easily through corresponding chunks of two dumps simultaneously.
////////////////////////////////////////////////////////////////////////////////////////////////////
class sliced_chunk_reader  {
public:

    //
    sliced_chunk_reader(comparer_context& ctx)
        : ctx(ctx)
    {}

    //
    ~sliced_chunk_reader() {
    }

public:

    sliced_chunk_iterator begin() const {
        return sliced_chunk_iterator(ctx,ctx.get_latest_chunk_length()+
            ctx.get_latest_chunk_start());
    }

private:

    comparer_context& ctx;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class  scoped_chunk
///
/// @brief  Utility to simplify usage of comparer_context.push_elem/pop_elem
////////////////////////////////////////////////////////////////////////////////////////////////////
class scoped_chunk {
public:

    //
    scoped_chunk(comparer_context& ctx,const char* msg)
        : ctx(ctx)
    {
        ctx.push_elem(msg);
    }

    //
    ~scoped_chunk()
    {
        ctx.pop_elem();
    }

private:

    comparer_context& ctx;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
void CompareOnTheFlyMaterialProperty(comparer_context& comp)    {
    scoped_chunk chunk(comp,"aiMaterialProperty");

    comp.cmp<aiString>("mKey");
    comp.cmp<uint32_t>("mSemantic");
    comp.cmp<uint32_t>("mIndex");
    const uint32_t length = comp.cmp<uint32_t>("mDataLength");
    const aiPropertyTypeInfo type = static_cast<aiPropertyTypeInfo>(
        comp.cmp<uint32_t>("mType"));

    switch (type)
    {
        case aiPTI_Float:
            comp.cmp<float>(length/4,"mData");
            break;

        case aiPTI_String:
            comp.cmp<aiString>("mData");
            break;

        case aiPTI_Integer:
            comp.cmp<uint32_t>(length/4,"mData");
            break;

        case aiPTI_Buffer:
            comp.cmp<uint8_t>(length,"mData");
            break;

        default:
            break;
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CompareOnTheFlyMaterial(comparer_context& comp)    {
    scoped_chunk chunk(comp,"aiMaterial");

    comp.cmp<uint32_t>("aiMaterial::mNumProperties");
    sliced_chunk_reader reader(comp);
    for(sliced_chunk_iterator it = reader.begin(); !it.is_end(); ++it) {
        if ((*it).first == ASSBIN_CHUNK_AIMATERIALPROPERTY) {
            CompareOnTheFlyMaterialProperty(comp);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CompareOnTheFlyBone(comparer_context& comp)    {
    scoped_chunk chunk(comp,"aiBone");
    comp.cmp<aiString>("mName");
    comp.cmp<uint32_t>("mNumWeights");
    comp.cmp<aiMatrix4x4>("mOffsetMatrix");

    comp.cmp_bounds<aiVertexWeight>("mWeights");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CompareOnTheFlyNodeAnim(comparer_context& comp)    {
    scoped_chunk chunk(comp,"aiNodeAnim");

    comp.cmp<aiString>("mNodeName");
    comp.cmp<uint32_t>("mNumPositionKeys");
    comp.cmp<uint32_t>("mNumRotationKeys");
    comp.cmp<uint32_t>("mNumScalingKeys");
    comp.cmp<uint32_t>("mPreState");
    comp.cmp<uint32_t>("mPostState");

    comp.cmp_bounds<aiVectorKey>("mPositionKeys");
    comp.cmp_bounds<aiQuatKey>("mRotationKeys");
    comp.cmp_bounds<aiVectorKey>("mScalingKeys");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CompareOnTheFlyMesh(comparer_context& comp)    {
    scoped_chunk chunk(comp,"aiMesh");

    comp.cmp<uint32_t>("mPrimitiveTypes");
    comp.cmp<uint32_t>("mNumVertices");
    const uint32_t nf = comp.cmp<uint32_t>("mNumFaces");
    comp.cmp<uint32_t>("mNumBones");
    comp.cmp<uint32_t>("mMaterialIndex");

    const uint32_t present = comp.cmp<uint32_t>("<vertex-components-present>");
    if(present & ASSBIN_MESH_HAS_POSITIONS) {
        comp.cmp_bounds<aiVector3D>("mVertices");
    }

    if(present & ASSBIN_MESH_HAS_NORMALS) {
        comp.cmp_bounds<aiVector3D>("mNormals");
    }

    if(present & ASSBIN_MESH_HAS_TANGENTS_AND_BITANGENTS) {
        comp.cmp_bounds<aiVector3D>("mTangents");
        comp.cmp_bounds<aiVector3D>("mBitangents");
    }

    for(unsigned int i = 0; present & ASSBIN_MESH_HAS_COLOR(i); ++i) {
        std::stringstream ss;
        comp.cmp_bounds<aiColor4D>((ss<<"mColors["<<i<<"]",ss.str()));
    }

    for(unsigned int i = 0; present & ASSBIN_MESH_HAS_TEXCOORD(i); ++i) {
        std::stringstream ss;
        comp.cmp<uint32_t>((ss<<"mNumUVComponents["<<i<<"]",ss.str()));
        comp.cmp_bounds<aiVector3D>((ss.clear(),ss<<"mTextureCoords["<<i<<"]",ss.str()));
    }

    for(unsigned int i = 0; i< ((nf+511)/512); ++i) {
        std::stringstream ss;
        comp.cmp<uint32_t>((ss<<"mFaces["<<i*512<<"-"<<std::min(static_cast<
            uint32_t>((i+1)*512),nf)<<"]",ss.str()));
    }

    sliced_chunk_reader reader(comp);
    for(sliced_chunk_iterator it = reader.begin(); !it.is_end(); ++it) {
        if ((*it).first == ASSBIN_CHUNK_AIBONE) {
            CompareOnTheFlyBone(comp);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CompareOnTheFlyCamera(comparer_context& comp)  {
    scoped_chunk chunk(comp,"aiCamera");

    comp.cmp<aiString>("mName");

    comp.cmp<aiVector3D>("mPosition");
    comp.cmp<aiVector3D>("mLookAt");
    comp.cmp<aiVector3D>("mUp");

    comp.cmp<float>("mHorizontalFOV");
    comp.cmp<float>("mClipPlaneNear");
    comp.cmp<float>("mClipPlaneFar");
    comp.cmp<float>("mAspect");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CompareOnTheFlyLight(comparer_context& comp)   {
    scoped_chunk chunk(comp,"aiLight");

    comp.cmp<aiString>("mName");
    const aiLightSourceType type = static_cast<aiLightSourceType>(
        comp.cmp<uint32_t>("mType"));

    if(type!=aiLightSource_DIRECTIONAL) {
        comp.cmp<float>("mAttenuationConstant");
        comp.cmp<float>("mAttenuationLinear");
        comp.cmp<float>("mAttenuationQuadratic");
    }

    comp.cmp<aiVector3D>("mColorDiffuse");
    comp.cmp<aiVector3D>("mColorSpecular");
    comp.cmp<aiVector3D>("mColorAmbient");

    if(type==aiLightSource_SPOT) {
        comp.cmp<float>("mAngleInnerCone");
        comp.cmp<float>("mAngleOuterCone");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CompareOnTheFlyAnimation(comparer_context& comp)   {
    scoped_chunk chunk(comp,"aiAnimation");

    comp.cmp<aiString>("mName");
    comp.cmp<double>("mDuration");
    comp.cmp<double>("mTicksPerSecond");
    comp.cmp<uint32_t>("mNumChannels");

    sliced_chunk_reader reader(comp);
    for(sliced_chunk_iterator it = reader.begin(); !it.is_end(); ++it) {
        if ((*it).first == ASSBIN_CHUNK_AINODEANIM) {
            CompareOnTheFlyNodeAnim(comp);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CompareOnTheFlyTexture(comparer_context& comp) {
    scoped_chunk chunk(comp,"aiTexture");

    const uint32_t w = comp.cmp<uint32_t>("mWidth");
    const uint32_t h = comp.cmp<uint32_t>("mHeight");
    (void)w; (void)h;
    comp.cmp<char>("achFormatHint[0]");
    comp.cmp<char>("achFormatHint[1]");
    comp.cmp<char>("achFormatHint[2]");
    comp.cmp<char>("achFormatHint[3]");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CompareOnTheFlyNode(comparer_context& comp)    {
    scoped_chunk chunk(comp,"aiNode");
    comp.cmp<aiString>("mName");
    comp.cmp<aiMatrix4x4>("mTransformation");
    comp.cmp<uint32_t>("mNumChildren");
    comp.cmp<uint32_t>(comp.cmp<uint32_t>("mNumMeshes"),"mMeshes");

    sliced_chunk_reader reader(comp);
    for(sliced_chunk_iterator it = reader.begin(); !it.is_end(); ++it) {
        if ((*it).first == ASSBIN_CHUNK_AINODE) {
            CompareOnTheFlyNode(comp);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CompareOnTheFlyScene(comparer_context& comp)   {
    scoped_chunk chunk(comp,"aiScene");

    comp.cmp<uint32_t>("mFlags");
    comp.cmp<uint32_t>("mNumMeshes");
    comp.cmp<uint32_t>("mNumMaterials");
    comp.cmp<uint32_t>("mNumAnimations");
    comp.cmp<uint32_t>("mNumTextures");
    comp.cmp<uint32_t>("mNumLights");
    comp.cmp<uint32_t>("mNumCameras");

    sliced_chunk_reader reader(comp);
    for(sliced_chunk_iterator it = reader.begin(); !it.is_end(); ++it) {
        if ((*it).first == ASSBIN_CHUNK_AIMATERIAL) {
            CompareOnTheFlyMaterial(comp);
        }
        else if ((*it).first == ASSBIN_CHUNK_AITEXTURE) {
            CompareOnTheFlyTexture(comp);
        }
        else if ((*it).first == ASSBIN_CHUNK_AIMESH) {
            CompareOnTheFlyMesh(comp);
        }
        else if ((*it).first == ASSBIN_CHUNK_AIANIMATION) {
            CompareOnTheFlyAnimation(comp);
        }
        else if ((*it).first == ASSBIN_CHUNK_AICAMERA) {
            CompareOnTheFlyCamera(comp);
        }
        else if ((*it).first == ASSBIN_CHUNK_AILIGHT) {
            CompareOnTheFlyLight(comp);
        }
        else if ((*it).first == ASSBIN_CHUNK_AINODE) {
            CompareOnTheFlyNode(comp);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CompareOnTheFly(comparer_context& comp)
{
    sliced_chunk_reader reader(comp);
    for(sliced_chunk_iterator it = reader.begin(); !it.is_end(); ++it) {
        if ((*it).first == ASSBIN_CHUNK_AISCENE) {
            CompareOnTheFlyScene(comp);
            break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CheckHeader(comparer_context& comp)
{
    fseek(comp.get_actual(),ASSBIN_HEADER_LENGTH,SEEK_CUR);
    fseek(comp.get_expect(),ASSBIN_HEADER_LENGTH,SEEK_CUR);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int Assimp_CompareDump (const char* const* params, unsigned int num)
{
    // --help
    if ((num == 1 && !strcmp( params[0], "-h")) || !strcmp( params[0], "--help") || !strcmp( params[0], "-?") ) {
        printf("%s",AICMD_MSG_CMPDUMP_HELP);
        return 0;
    }

    // assimp cmpdump actual expected
    if (num < 2) {
        std::cout << "assimp cmpdump: Invalid number of arguments. "
            "See \'assimp cmpdump --help\'\r\n" << std::endl;
        return 1;
    }

    if(!strcmp(params[0],params[1])) {
        std::cout << "assimp cmpdump: same file, same content." << std::endl;
        return 0;
    }

    class file_ptr
    {
    public:
        file_ptr(FILE *p)
            : m_file(p)
        {}
        ~file_ptr()
        {
            if (m_file)
            {
                fclose(m_file);
                m_file = NULL;
            }
        }

        operator FILE *() { return m_file; }

    private:
        FILE *m_file;
    };
    file_ptr actual(fopen(params[0],"rb"));
    if (!actual) {
        std::cout << "assimp cmpdump: Failure reading ACTUAL data from " <<
            params[0]  << std::endl;
        return -5;
    }
    file_ptr expected(fopen(params[1],"rb"));
    if (!expected) {
        std::cout << "assimp cmpdump: Failure reading EXPECT data from " <<
            params[1]  << std::endl;
        return -6;
    }

    comparer_context comp(actual,expected);
    try {
        CheckHeader(comp);
        CompareOnTheFly(comp);
    }
    catch(const compare_fails_exception& ex) {
        printf("%s",ex.what());
        return -1;
    }
    catch(...) {
        // we don't bother checking too rigourously here, so
        // we might end up here ...
        std::cout << "Unknown failure, are the input files well-defined?";
        return -3;
    }

    std::cout << "Success (totally " << std::dec << comp.get_num_chunks() <<
        " chunks)" << std::endl;

    return 0;
}
