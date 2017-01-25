/*
** Copyright (c) 2014-2016 The Khronos Group Inc.
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and/or associated documentation files (the "Materials"),
** to deal in the Materials without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and/or sell copies of the Materials, and to permit persons to whom the
** Materials are furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Materials.
**
** MODIFICATIONS TO THIS FILE MAY MEAN IT NO LONGER ACCURATELY REFLECTS KHRONOS
** STANDARDS. THE UNMODIFIED, NORMATIVE VERSIONS OF KHRONOS SPECIFICATIONS AND
** HEADER INFORMATION ARE LOCATED AT https://www.khronos.org/registry/
**
** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
** OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
** FROM,OUT OF OR IN CONNECTION WITH THE MATERIALS OR THE USE OR OTHER DEALINGS
** IN THE MATERIALS.
*/

#ifndef GLSLextNV_H
#define GLSLextNV_H

enum BuiltIn;
enum Decoration;
enum Op;
enum Capability;

static const int GLSLextNVVersion = 100;
static const int GLSLextNVRevision = 4;

//SPV_NV_sample_mask_override_coverage
const char* const E_SPV_NV_sample_mask_override_coverage = "SPV_NV_sample_mask_override_coverage";

static const Decoration DecorationOverrideCoverageNV = static_cast<Decoration>(5248);


//SPV_NV_geometry_shader_passthrough
const char* const E_SPV_NV_geometry_shader_passthrough = "SPV_NV_geometry_shader_passthrough";

static const Decoration DecorationPassthroughNV = static_cast<Decoration>(5250);

static const Capability CapabilityGeometryShaderPassthroughNV = static_cast<Capability>(5251);


//SPV_NV_viewport_array2
const char* const E_SPV_NV_viewport_array2 = "SPV_NV_viewport_array2";
const char* const E_ARB_shader_viewport_layer_array = "SPV_ARB_shader_viewport_layer_array";

static const Decoration DecorationViewportRelativeNV = static_cast<Decoration>(5252);

static const BuiltIn BuiltInViewportMaskNV = static_cast<BuiltIn>(5253);

static const Capability CapabilityShaderViewportIndexLayerNV = static_cast<Capability>(5254);
static const Capability CapabilityShaderViewportMaskNV       = static_cast<Capability>(5255);


//SPV_NV_stereo_view_rendering
const char* const E_SPV_NV_stereo_view_rendering = "SPV_NV_stereo_view_rendering";

static const Decoration DecorationSecondaryViewportRelativeNV = static_cast<Decoration>(5256);

static const BuiltIn BuiltInSecondaryPositionNV = static_cast<BuiltIn>(5257);
static const BuiltIn BuiltInSecondaryViewportMaskNV = static_cast<BuiltIn>(5258);

static const Capability CapabilityShaderStereoViewNV = static_cast<Capability>(5259);

#endif  // #ifndef GLSLextNV_H