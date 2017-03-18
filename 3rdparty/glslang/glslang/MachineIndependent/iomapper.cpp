//
// Copyright (C) 2016 LunarG, Inc.
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//
//    Neither the name of 3Dlabs Inc. Ltd. nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

#include "../Include/Common.h"
#include "../Include/InfoSink.h"
#include "iomapper.h"
#include "LiveTraverser.h"
#include "localintermediate.h"

#include "gl_types.h"

#include <unordered_set>
#include <unordered_map>

//
// Map IO bindings.
//
// High-level algorithm for one stage:
//
// 1. Traverse all code (live+dead) to find the explicitly provided bindings.
//
// 2. Traverse (just) the live code to determine which non-provided bindings
//    require auto-numbering.  We do not auto-number dead ones.
//
// 3. Traverse all the code to apply the bindings:
//    a. explicitly given bindings are offset according to their type
//    b. implicit live bindings are auto-numbered into the holes, using
//       any open binding slot.
//    c. implicit dead bindings are left un-bound.
//


namespace glslang {

struct TVarEntryInfo
{
    int               id;
    TIntermSymbol*    symbol;
    bool              live;
    int               newBinding;
    int               newSet;
    int               newLocation;
    int               newComponent;
    int               newIndex;

    struct TOrderById
    {
      inline bool operator()(const TVarEntryInfo& l, const TVarEntryInfo& r)
      {
        return l.id < r.id;
      }
    };

    struct TOrderByPriority
    {
        // ordering:
        // 1) has both binding and set
        // 2) has binding but no set
        // 3) has no binding but set
        // 4) has no binding and no set
        inline bool operator()(const TVarEntryInfo& l, const TVarEntryInfo& r)
        {
            const TQualifier& lq = l.symbol->getQualifier();
            const TQualifier& rq = r.symbol->getQualifier();

            // simple rules:
            // has binding gives 2 points
            // has set gives 1 point
            // who has the most points is more important.
            int lPoints = (lq.hasBinding() ? 2 : 0) + (lq.hasSet() ? 1 : 0);
            int rPoints = (rq.hasBinding() ? 2 : 0) + (rq.hasSet() ? 1 : 0);

            if (lPoints == rPoints)
              return l.id < r.id;
            return lPoints > rPoints;
        }
    };
};



typedef std::vector<TVarEntryInfo> TVarLiveMap;

class TVarGatherTraverser : public TLiveTraverser
{
public:
    TVarGatherTraverser(const TIntermediate& i, bool traverseDeadCode, TVarLiveMap& inList, TVarLiveMap& outList, TVarLiveMap& uniformList)
      : TLiveTraverser(i, traverseDeadCode, true, true, false)
      , inputList(inList)
      , outputList(outList)
      , uniformList(uniformList)
    {
    }


    virtual void visitSymbol(TIntermSymbol* base)
    {
        TVarLiveMap* target = nullptr;
        if (base->getQualifier().storage == EvqVaryingIn)
            target = &inputList;
        else if (base->getQualifier().storage == EvqVaryingOut)
            target = &outputList;
        else if (base->getQualifier().isUniformOrBuffer())
            target = &uniformList;

        if (target) {
            TVarEntryInfo ent = { base->getId(), base, !traverseAll };
            TVarLiveMap::iterator at = std::lower_bound(target->begin(), target->end(), ent, TVarEntryInfo::TOrderById());
            if (at != target->end() && at->id == ent.id)
              at->live = at->live || !traverseAll; // update live state
            else
              target->insert(at, ent);
        }
    }

private:
    TVarLiveMap&    inputList;
    TVarLiveMap&    outputList;
    TVarLiveMap&    uniformList;
};

class TVarSetTraverser : public TLiveTraverser
{
public:
    TVarSetTraverser(const TIntermediate& i, const TVarLiveMap& inList, const TVarLiveMap& outList, const TVarLiveMap& uniformList)
      : TLiveTraverser(i, true, true, true, false)
      , inputList(inList)
      , outputList(outList)
      , uniformList(uniformList)
    {
    }


    virtual void visitSymbol(TIntermSymbol* base)
    {
        const TVarLiveMap* source;
        if (base->getQualifier().storage == EvqVaryingIn)
            source = &inputList;
        else if (base->getQualifier().storage == EvqVaryingOut)
            source = &outputList;
        else if (base->getQualifier().isUniformOrBuffer())
            source = &uniformList;
        else
            return;

        TVarEntryInfo ent = { base->getId() };
        TVarLiveMap::const_iterator at = std::lower_bound(source->begin(), source->end(), ent, TVarEntryInfo::TOrderById());
        if (at == source->end())
            return;

        if (at->id != ent.id)
            return;

        if (at->newBinding != -1)
            base->getWritableType().getQualifier().layoutBinding = at->newBinding;
        if (at->newSet != -1)
            base->getWritableType().getQualifier().layoutSet = at->newSet;
        if (at->newLocation != -1)
            base->getWritableType().getQualifier().layoutLocation = at->newLocation;
        if (at->newComponent != -1)
            base->getWritableType().getQualifier().layoutComponent = at->newComponent;
        if (at->newIndex != -1)
            base->getWritableType().getQualifier().layoutIndex = at->newIndex;
    }

  private:
    const TVarLiveMap&    inputList;
    const TVarLiveMap&    outputList;
    const TVarLiveMap&    uniformList;
};

struct TResolverUniformAdaptor
{
    TResolverUniformAdaptor(EShLanguage s, TIoMapResolver& r, TInfoSink& i, bool& e, TIntermediate& interm)
      : resolver(r)
      , stage(s)
      , infoSink(i)
      , error(e)
      , intermediate(interm)
    {
    }

    inline void operator()(TVarEntryInfo& ent)
    {
        ent.newLocation = -1;
        ent.newComponent = -1;
        ent.newBinding = -1;
        ent.newSet = -1;
        ent.newIndex = -1;
        const bool isValid = resolver.validateBinding(stage, ent.symbol->getName().c_str(), ent.symbol->getType(), ent.live);
        if (isValid) {
            ent.newBinding = resolver.resolveBinding(stage, ent.symbol->getName().c_str(), ent.symbol->getType(), ent.live);
            ent.newSet = resolver.resolveSet(stage, ent.symbol->getName().c_str(), ent.symbol->getType(), ent.live);

            if (ent.newBinding != -1) {
                if (ent.newBinding >= int(TQualifier::layoutBindingEnd)) {
                    TString err = "mapped binding out of range: " + ent.symbol->getName();

                    infoSink.info.message(EPrefixInternalError, err.c_str());
                    error = true;
                }
            }
            if (ent.newSet != -1) {
                if (ent.newSet >= int(TQualifier::layoutSetEnd)) {
                    TString err = "mapped set out of range: " + ent.symbol->getName();

                    infoSink.info.message(EPrefixInternalError, err.c_str());
                    error = true;
                }
            }
        } else {
            TString errorMsg = "Invalid binding: " + ent.symbol->getName();
            infoSink.info.message(EPrefixInternalError, errorMsg.c_str());
            error = true;
        }
    }

    EShLanguage     stage;
    TIoMapResolver& resolver;
    TInfoSink&      infoSink;
    bool&           error;
    TIntermediate&  intermediate;

private:
    TResolverUniformAdaptor& operator=(TResolverUniformAdaptor&);
};

struct TResolverInOutAdaptor
{
    TResolverInOutAdaptor(EShLanguage s, TIoMapResolver& r, TInfoSink& i, bool& e, TIntermediate& interm)
      : resolver(r)
      , stage(s)
      , infoSink(i)
      , error(e)
      , intermediate(interm)
    {
    }

    inline void operator()(TVarEntryInfo& ent)
    {
        ent.newLocation = -1;
        ent.newComponent = -1;
        ent.newBinding = -1;
        ent.newSet = -1;
        ent.newIndex = -1;
        const bool isValid = resolver.validateInOut(stage,
                                                    ent.symbol->getName().c_str(),
                                                    ent.symbol->getType(),
                                                    ent.live);
        if (isValid) {
            ent.newLocation = resolver.resolveInOutLocation(stage,
                                                            ent.symbol->getName().c_str(),
                                                            ent.symbol->getType(),
                                                            ent.live);
            ent.newComponent = resolver.resolveInOutComponent(stage,
                                                              ent.symbol->getName().c_str(),
                                                              ent.symbol->getType(),
                                                              ent.live);
            ent.newIndex = resolver.resolveInOutIndex(stage,
                                                      ent.symbol->getName().c_str(),
                                                      ent.symbol->getType(),
                                                      ent.live);
        } else {
            TString errorMsg = "Invalid shader In/Out variable semantic: ";
            errorMsg += ent.symbol->getType().getQualifier().semanticName;
            infoSink.info.message(EPrefixInternalError, errorMsg.c_str());
            error = true;
        }
    }

    EShLanguage     stage;
    TIoMapResolver& resolver;
    TInfoSink&      infoSink;
    bool&           error;
    TIntermediate&  intermediate;

private:
    TResolverInOutAdaptor& operator=(TResolverInOutAdaptor&);
};

/*
 * Basic implementation of glslang::TIoMapResolver that replaces the
 * previous offset behavior.
 * It does the same, uses the offsets for the corresponding uniform
 * types. Also respects the EOptionAutoMapBindings flag and binds
 * them if needed.
 */
struct TDefaultIoResolver : public glslang::TIoMapResolver
{
    int baseSamplerBinding;
    int baseTextureBinding;
    int baseImageBinding;
    int baseUboBinding;
    int baseSsboBinding;
    bool doAutoMapping;
    typedef std::vector<int> TSlotSet;
    typedef std::unordered_map<int, TSlotSet> TSlotSetMap;
    TSlotSetMap slots;

    TSlotSet::iterator findSlot(int set, int slot)
    {
        return std::lower_bound(slots[set].begin(), slots[set].end(), slot);
    }

    bool checkEmpty(int set, int slot)
    {
        TSlotSet::iterator at = findSlot(set, slot);
        return !(at != slots[set].end() && *at == slot);
    }

    int reserveSlot(int set, int slot)
    {
        TSlotSet::iterator at = findSlot(set, slot);
        slots[set].insert(at, slot);
        return slot;
    }

    int getFreeSlot(int set, int base)
    {
        TSlotSet::iterator at = findSlot(set, base);
        if (at == slots[set].end())
            return reserveSlot(set, base);

        // look in locksteps, if they not match, then there is a free slot
        for (; at != slots[set].end(); ++at, ++base)
            if (*at != base)
                break;
        return reserveSlot(set, base);
    }

    bool validateBinding(EShLanguage /*stage*/, const char* /*name*/, const glslang::TType& type, bool /*is_live*/) override
    {
        if (type.getQualifier().hasBinding()) {
            int set;
            if (type.getQualifier().hasSet())
                set = type.getQualifier().layoutSet;
            else
                set = 0;

            if (type.getBasicType() == glslang::EbtSampler) {
                const glslang::TSampler& sampler = type.getSampler();
                if (sampler.isPureSampler())
                    return checkEmpty(set, baseSamplerBinding + type.getQualifier().layoutBinding);

                if (sampler.isTexture())
                    return checkEmpty(set, baseTextureBinding + type.getQualifier().layoutBinding);
            }

            if (type.getQualifier().storage == EvqUniform)
                return checkEmpty(set, baseUboBinding + type.getQualifier().layoutBinding);

            if (type.getQualifier().storage == EvqBuffer)
                return checkEmpty(set, baseSsboBinding + type.getQualifier().layoutBinding);
        }
        return true;
    }

    int resolveBinding(EShLanguage /*stage*/, const char* /*name*/, const glslang::TType& type, bool is_live) override
    {
        int set;
        if (type.getQualifier().hasSet())
            set = type.getQualifier().layoutSet;
        else
            set = 0;

        if (type.getQualifier().hasBinding()) {
            if (type.getBasicType() == glslang::EbtSampler) {
                const glslang::TSampler& sampler = type.getSampler();
                if (sampler.isImage())
                    return reserveSlot(set, baseImageBinding + type.getQualifier().layoutBinding);

                if (sampler.isPureSampler())
                    return reserveSlot(set, baseSamplerBinding + type.getQualifier().layoutBinding);

                if (sampler.isTexture())
                    return reserveSlot(set, baseTextureBinding + type.getQualifier().layoutBinding);
            }

            if (type.getQualifier().storage == EvqUniform)
                return reserveSlot(set, baseUboBinding + type.getQualifier().layoutBinding);

            if (type.getQualifier().storage == EvqBuffer)
                return reserveSlot(set, baseSsboBinding + type.getQualifier().layoutBinding);
        } else if (is_live && doAutoMapping) {
            // find free slot, the caller did make sure it passes all vars with binding
            // first and now all are passed that do not have a binding and needs one
            if (type.getBasicType() == glslang::EbtSampler) {
                const glslang::TSampler& sampler = type.getSampler();
                if (sampler.isImage())
                    return getFreeSlot(set, baseImageBinding);

                if (sampler.isPureSampler())
                    return getFreeSlot(set, baseSamplerBinding);

                if (sampler.isTexture())
                    return getFreeSlot(set, baseTextureBinding);
            }

            if (type.getQualifier().storage == EvqUniform)
                return getFreeSlot(set, baseUboBinding);

            if (type.getQualifier().storage == EvqBuffer)
                return getFreeSlot(set, baseSsboBinding);
        }

        return -1;
    }

    int resolveSet(EShLanguage /*stage*/, const char* /*name*/, const glslang::TType& type, bool /*is_live*/) override
    {
        if (type.getQualifier().hasSet())
            return type.getQualifier().layoutSet;
        return 0;
    }

    bool validateInOut(EShLanguage stage, const char* name, const TType& type, bool is_live) override
    {
        return true;
    }
    int resolveInOutLocation(EShLanguage stage, const char* name, const TType& type, bool is_live) override
    {
        return -1;
    }
    int resolveInOutComponent(EShLanguage stage, const char* name, const TType& type, bool is_live) override
    {
        return -1;
    }
    int resolveInOutIndex(EShLanguage stage, const char* name, const TType& type, bool is_live) override
    {
        return -1;
    }
};

// Map I/O variables to provided offsets, and make bindings for
// unbound but live variables.
//
// Returns false if the input is too malformed to do this.
bool TIoMapper::addStage(EShLanguage stage, TIntermediate &intermediate, TInfoSink &infoSink, TIoMapResolver *resolver)
{
    // Trivial return if there is nothing to do.
    if (intermediate.getShiftSamplerBinding() == 0 &&
        intermediate.getShiftTextureBinding() == 0 &&
        intermediate.getShiftImageBinding() == 0 &&
        intermediate.getShiftUboBinding() == 0 &&
        intermediate.getShiftSsboBinding() == 0 &&
        intermediate.getAutoMapBindings() == false &&
        resolver == nullptr)
        return true;

    if (intermediate.getNumEntryPoints() != 1 || intermediate.isRecursive())
        return false;

    TIntermNode* root = intermediate.getTreeRoot();
    if (root == nullptr)
        return false;

    // if no resolver is provided, use the default resolver with the given shifts and auto map settings
    TDefaultIoResolver defaultResolver;
    if (resolver == nullptr) {
        defaultResolver.baseSamplerBinding = intermediate.getShiftSamplerBinding();
        defaultResolver.baseTextureBinding = intermediate.getShiftTextureBinding();
        defaultResolver.baseImageBinding = intermediate.getShiftImageBinding();
        defaultResolver.baseUboBinding = intermediate.getShiftUboBinding();
        defaultResolver.baseSsboBinding = intermediate.getShiftSsboBinding();
        defaultResolver.doAutoMapping = intermediate.getAutoMapBindings();

        resolver = &defaultResolver;
    }

    TVarLiveMap inVarMap, outVarMap, uniformVarMap;
    TVarGatherTraverser iter_binding_all(intermediate, true, inVarMap, outVarMap, uniformVarMap);
    TVarGatherTraverser iter_binding_live(intermediate, false, inVarMap, outVarMap, uniformVarMap);

    root->traverse(&iter_binding_all);
    iter_binding_live.pushFunction(intermediate.getEntryPointMangledName().c_str());

    while (!iter_binding_live.functions.empty()) {
        TIntermNode* function = iter_binding_live.functions.back();
        iter_binding_live.functions.pop_back();
        function->traverse(&iter_binding_live);
    }

    // sort entries by priority. see TVarEntryInfo::TOrderByPriority for info.
    std::sort(uniformVarMap.begin(), uniformVarMap.end(), TVarEntryInfo::TOrderByPriority());

    bool hadError = false;
    TResolverUniformAdaptor uniformResolve(stage, *resolver, infoSink, hadError, intermediate);
    TResolverInOutAdaptor inOutResolve(stage, *resolver, infoSink, hadError, intermediate);
    std::for_each(inVarMap.begin(), inVarMap.end(), inOutResolve);
    std::for_each(outVarMap.begin(), outVarMap.end(), inOutResolve);
    std::for_each(uniformVarMap.begin(), uniformVarMap.end(), uniformResolve);

    if (!hadError) {
        // sort by id again, so we can use lower bound to find entries
        std::sort(uniformVarMap.begin(), uniformVarMap.end(), TVarEntryInfo::TOrderById());
        TVarSetTraverser iter_iomap(intermediate, inVarMap, outVarMap, uniformVarMap);
        root->traverse(&iter_iomap);
    }

    return !hadError;
}

} // end namespace glslang
