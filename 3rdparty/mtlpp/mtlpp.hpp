/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

#pragma once

//////////////////////////////////////
// FILE: defines.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

#include <stdint.h>
#include <assert.h>
#include <functional>

#ifndef __has_feature
#   define __has_feature(x) 0
#endif

#ifndef MTLPP_CONFIG_RVALUE_REFERENCES
#   define MTLPP_CONFIG_RVALUE_REFERENCES __has_feature(cxx_rvalue_references)
#endif

#ifndef MTLPP_CONFIG_VALIDATE
#   define MTLPP_CONFIG_VALIDATE 1
#endif

#ifndef MTLPP_CONFIG_USE_AVAILABILITY
#   define MTLPP_CONFIG_USE_AVAILABILITY 0
#endif

#if MTLPP_CONFIG_USE_AVAILABILITY
#   if __has_feature(attribute_availability_with_version_underscores) || (__has_feature(attribute_availability_with_message) && __clang__ && __clang_major__ >= 7)
#       include <CoreFoundation/CFAvailability.h>
#       define MTLPP_AVAILABLE(mac, ios)                            CF_AVAILABLE(mac, ios)
#       define MTLPP_AVAILABLE_MAC(mac)                             CF_AVAILABLE_MAC(mac)
#       define MTLPP_AVAILABLE_IOS(ios)                             CF_AVAILABLE_IOS(ios)
#       define MTLPP_AVAILABLE_TVOS(tvos)
#       define MTLPP_DEPRECATED(macIntro, macDep, iosIntro, iosDep) CF_DEPRECATED(macIntro, macDep, iosIntro, iosDep)
#       define MTLPP_DEPRECATED_MAC(macIntro, macDep)               CF_DEPRECATED_MAC(macIntro, macDep)
#       define MTLPP_DEPRECATED_IOS(iosIntro, iosDep)               CF_DEPRECATED_IOS(iosIntro, iosDep)
#   endif
#endif

#ifndef MTLPP_AVAILABLE
#   define MTLPP_AVAILABLE(mac, ios)
#   define MTLPP_AVAILABLE_MAC(mac)
#   define MTLPP_AVAILABLE_IOS(ios)
#   define MTLPP_AVAILABLE_TVOS(tvos)
#   define MTLPP_DEPRECATED(macIntro, macDep, iosIntro, iosDep)
#   define MTLPP_DEPRECATED_MAC(macIntro, macDep)
#   define MTLPP_DEPRECATED_IOS(iosIntro, iosDep)
#endif

#ifndef __DARWIN_ALIAS_STARTING_MAC___MAC_10_11
#   define __DARWIN_ALIAS_STARTING_MAC___MAC_10_11(x)
#endif
#ifndef __DARWIN_ALIAS_STARTING_MAC___MAC_10_12
#   define __DARWIN_ALIAS_STARTING_MAC___MAC_10_12(x)
#endif
#ifndef __DARWIN_ALIAS_STARTING_IPHONE___IPHONE_8_0
#   define __DARWIN_ALIAS_STARTING_IPHONE___IPHONE_8_0(x)
#endif
#ifndef __DARWIN_ALIAS_STARTING_IPHONE___IPHONE_9_0
#   define __DARWIN_ALIAS_STARTING_IPHONE___IPHONE_9_0(x)
#endif
#ifndef __DARWIN_ALIAS_STARTING_IPHONE___IPHONE_10_0
#   define __DARWIN_ALIAS_STARTING_IPHONE___IPHONE_10_0(x)
#endif

#define MTLPP_IS_AVAILABLE_MAC(mac)  (0 __DARWIN_ALIAS_STARTING_MAC___MAC_##mac( || 1 ))
#define MTLPP_IS_AVAILABLE_IOS(ios)  (0 __DARWIN_ALIAS_STARTING_IPHONE___IPHONE_##ios( || 1 ))
#define MTLPP_IS_AVAILABLE(mac, ios) (MTLPP_IS_AVAILABLE_MAC(mac) || MTLPP_IS_AVAILABLE_IOS(ios))


//////////////////////////////////////
// FILE: ns.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"

namespace ns
{
    struct Handle
    {
        const void* ptr;
    };

    class Object
    {
    public:
        inline const void* GetPtr() const { return m_ptr; }

        inline operator bool() const { return m_ptr != nullptr; }

    protected:
        Object();
        Object(const Handle& handle);
        Object(const Object& rhs);
#if MTLPP_CONFIG_RVALUE_REFERENCES
        Object(Object&& rhs);
#endif
        virtual ~Object();

        Object& operator=(const Object& rhs);
#if MTLPP_CONFIG_RVALUE_REFERENCES
        Object& operator=(Object&& rhs);
#endif

        inline void Validate() const
        {
#if MTLPP_CONFIG_VALIDATE
            assert(m_ptr);
#endif
        }

        const void* m_ptr = nullptr;
    };

    struct Range
    {
        inline Range(uint32_t location, uint32_t length) :
            Location(location),
            Length(length)
        { }

        uint32_t Location;
        uint32_t Length;
    };

    class ArrayBase : public Object
    {
    public:
        ArrayBase() { }
        ArrayBase(const Handle& handle) : Object(handle) { }

        const uint32_t GetSize() const;

    protected:
        void* GetItem(uint32_t index) const;
    };

    template<typename T>
    class Array : public ArrayBase
    {
    public:
        Array() { }
        Array(const Handle& handle) : ArrayBase(handle) { }

        const T operator[](uint32_t index) const
        {
            return Handle{ GetItem(index) };
        }

        T operator[](uint32_t index)
        {
            return Handle{ GetItem(index) };
        }
    };

    class DictionaryBase : public Object
    {
    public:
        DictionaryBase() { }
        DictionaryBase(const Handle& handle) : Object(handle) { }

    protected:

    };

    template<typename KeyT, typename ValueT>
    class Dictionary : public DictionaryBase
    {
    public:
        Dictionary() { }
        Dictionary(const Handle& handle) : DictionaryBase(handle) { }
    };

    class String : public Object
    {
    public:
        String() { }
        String(const Handle& handle) : Object(handle) { }
        String(const char* cstr);

        const char* GetCStr() const;
        uint32_t    GetLength() const;
    };

    class Error : public Object
    {
    public:
        Error();
        Error(const Handle& handle) : Object(handle) { }

        String   GetDomain() const;
        uint32_t GetCode() const;
        //@property (readonly, copy) NSDictionary *userInfo;
        String   GetLocalizedDescription() const;
        String   GetLocalizedFailureReason() const;
        String   GetLocalizedRecoverySuggestion() const;
        String   GetLocalizedRecoveryOptions() const;
        //@property (nullable, readonly, strong) id recoveryAttempter;
        String   GetHelpAnchor() const;
    };
}

//////////////////////////////////////
// FILE: command_encoder.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"
// #include "ns.hpp"

namespace mtlpp
{
    class Device;

    class CommandEncoder : public ns::Object
    {
    public:
        CommandEncoder() { }
        CommandEncoder(const ns::Handle& handle) : ns::Object(handle) { }

        Device     GetDevice() const;
        ns::String GetLabel() const;

        void SetLabel(const ns::String& label);

        void EndEncoding();
        void InsertDebugSignpost(const ns::String& string);
        void PushDebugGroup(const ns::String& string);
        void PopDebugGroup();
    }
    MTLPP_AVAILABLE(10_11, 8_0);
}

//////////////////////////////////////
// FILE: pixel_format.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"

namespace mtlpp
{
    enum class PixelFormat
    {
        Invalid                                            = 0,

        A8Unorm                                            = 1,

        R8Unorm                                            = 10,
        R8Unorm_sRGB          MTLPP_AVAILABLE_IOS(8_0)     = 11,

        R8Snorm                                            = 12,
        R8Uint                                             = 13,
        R8Sint                                             = 14,

        R16Unorm                                           = 20,
        R16Snorm                                           = 22,
        R16Uint                                            = 23,
        R16Sint                                            = 24,
        R16Float                                           = 25,

        RG8Unorm                                           = 30,
        RG8Unorm_sRGB         MTLPP_AVAILABLE_IOS(8_0)     = 31,
        RG8Snorm                                           = 32,
        RG8Uint                                            = 33,
        RG8Sint                                            = 34,

        B5G6R5Unorm           MTLPP_AVAILABLE_IOS(8_0)     = 40,
        A1BGR5Unorm           MTLPP_AVAILABLE_IOS(8_0)     = 41,
        ABGR4Unorm            MTLPP_AVAILABLE_IOS(8_0)     = 42,
        BGR5A1Unorm           MTLPP_AVAILABLE_IOS(8_0)     = 43,

        R32Uint                                            = 53,
        R32Sint                                            = 54,
        R32Float                                           = 55,

        RG16Unorm                                          = 60,
        RG16Snorm                                          = 62,
        RG16Uint                                           = 63,
        RG16Sint                                           = 64,
        RG16Float                                          = 65,

        RGBA8Unorm                                         = 70,
        RGBA8Unorm_sRGB                                    = 71,
        RGBA8Snorm                                         = 72,
        RGBA8Uint                                          = 73,
        RGBA8Sint                                          = 74,

        BGRA8Unorm                                         = 80,
        BGRA8Unorm_sRGB                                    = 81,

        RGB10A2Unorm                                       = 90,
        RGB10A2Uint                                        = 91,

        RG11B10Float                                       = 92,
        RGB9E5Float                                        = 93,

        BGR10_XR              MTLPP_AVAILABLE_IOS(10_0)    = 554,
        BGR10_XR_sRGB         MTLPP_AVAILABLE_IOS(10_0)    = 555,


        RG32Uint                                           = 103,
        RG32Sint                                           = 104,
        RG32Float                                          = 105,

        RGBA16Unorm                                        = 110,
        RGBA16Snorm                                        = 112,
        RGBA16Uint                                         = 113,
        RGBA16Sint                                         = 114,
        RGBA16Float                                        = 115,

        BGRA10_XR             MTLPP_AVAILABLE_IOS(10_0)    = 552,
        BGRA10_XR_sRGB        MTLPP_AVAILABLE_IOS(10_0)    = 553,

        RGBA32Uint                                         = 123,
        RGBA32Sint                                         = 124,
        RGBA32Float                                        = 125,

        BC1_RGBA              MTLPP_AVAILABLE_MAC(10_11)   = 130,
        BC1_RGBA_sRGB         MTLPP_AVAILABLE_MAC(10_11)   = 131,
        BC2_RGBA              MTLPP_AVAILABLE_MAC(10_11)   = 132,
        BC2_RGBA_sRGB         MTLPP_AVAILABLE_MAC(10_11)   = 133,
        BC3_RGBA              MTLPP_AVAILABLE_MAC(10_11)   = 134,
        BC3_RGBA_sRGB         MTLPP_AVAILABLE_MAC(10_11)   = 135,

        BC4_RUnorm            MTLPP_AVAILABLE_MAC(10_11)   = 140,
        BC4_RSnorm            MTLPP_AVAILABLE_MAC(10_11)   = 141,
        BC5_RGUnorm           MTLPP_AVAILABLE_MAC(10_11)   = 142,
        BC5_RGSnorm           MTLPP_AVAILABLE_MAC(10_11)   = 143,

        BC6H_RGBFloat         MTLPP_AVAILABLE_MAC(10_11)   = 150,
        BC6H_RGBUfloat        MTLPP_AVAILABLE_MAC(10_11)   = 151,
        BC7_RGBAUnorm         MTLPP_AVAILABLE_MAC(10_11)   = 152,
        BC7_RGBAUnorm_sRGB    MTLPP_AVAILABLE_MAC(10_11)   = 153,

        PVRTC_RGB_2BPP        MTLPP_AVAILABLE_IOS(8_0)     = 160,
        PVRTC_RGB_2BPP_sRGB   MTLPP_AVAILABLE_IOS(8_0)     = 161,
        PVRTC_RGB_4BPP        MTLPP_AVAILABLE_IOS(8_0)     = 162,
        PVRTC_RGB_4BPP_sRGB   MTLPP_AVAILABLE_IOS(8_0)     = 163,
        PVRTC_RGBA_2BPP       MTLPP_AVAILABLE_IOS(8_0)     = 164,
        PVRTC_RGBA_2BPP_sRGB  MTLPP_AVAILABLE_IOS(8_0)     = 165,
        PVRTC_RGBA_4BPP       MTLPP_AVAILABLE_IOS(8_0)     = 166,
        PVRTC_RGBA_4BPP_sRGB  MTLPP_AVAILABLE_IOS(8_0)     = 167,

        EAC_R11Unorm          MTLPP_AVAILABLE_IOS(8_0)     = 170,
        EAC_R11Snorm          MTLPP_AVAILABLE_IOS(8_0)     = 172,
        EAC_RG11Unorm         MTLPP_AVAILABLE_IOS(8_0)     = 174,
        EAC_RG11Snorm         MTLPP_AVAILABLE_IOS(8_0)     = 176,
        EAC_RGBA8             MTLPP_AVAILABLE_IOS(8_0)     = 178,
        EAC_RGBA8_sRGB        MTLPP_AVAILABLE_IOS(8_0)     = 179,

        ETC2_RGB8             MTLPP_AVAILABLE_IOS(8_0)     = 180,
        ETC2_RGB8_sRGB        MTLPP_AVAILABLE_IOS(8_0)     = 181,
        ETC2_RGB8A1           MTLPP_AVAILABLE_IOS(8_0)     = 182,
        ETC2_RGB8A1_sRGB      MTLPP_AVAILABLE_IOS(8_0)     = 183,

        ASTC_4x4_sRGB         MTLPP_AVAILABLE_IOS(8_0)     = 186,
        ASTC_5x4_sRGB         MTLPP_AVAILABLE_IOS(8_0)     = 187,
        ASTC_5x5_sRGB         MTLPP_AVAILABLE_IOS(8_0)     = 188,
        ASTC_6x5_sRGB         MTLPP_AVAILABLE_IOS(8_0)     = 189,
        ASTC_6x6_sRGB         MTLPP_AVAILABLE_IOS(8_0)     = 190,
        ASTC_8x5_sRGB         MTLPP_AVAILABLE_IOS(8_0)     = 192,
        ASTC_8x6_sRGB         MTLPP_AVAILABLE_IOS(8_0)     = 193,
        ASTC_8x8_sRGB         MTLPP_AVAILABLE_IOS(8_0)     = 194,
        ASTC_10x5_sRGB        MTLPP_AVAILABLE_IOS(8_0)     = 195,
        ASTC_10x6_sRGB        MTLPP_AVAILABLE_IOS(8_0)     = 196,
        ASTC_10x8_sRGB        MTLPP_AVAILABLE_IOS(8_0)     = 197,
        ASTC_10x10_sRGB       MTLPP_AVAILABLE_IOS(8_0)     = 198,
        ASTC_12x10_sRGB       MTLPP_AVAILABLE_IOS(8_0)     = 199,
        ASTC_12x12_sRGB       MTLPP_AVAILABLE_IOS(8_0)     = 200,

        ASTC_4x4_LDR          MTLPP_AVAILABLE_IOS(8_0)     = 204,
        ASTC_5x4_LDR          MTLPP_AVAILABLE_IOS(8_0)     = 205,
        ASTC_5x5_LDR          MTLPP_AVAILABLE_IOS(8_0)     = 206,
        ASTC_6x5_LDR          MTLPP_AVAILABLE_IOS(8_0)     = 207,
        ASTC_6x6_LDR          MTLPP_AVAILABLE_IOS(8_0)     = 208,
        ASTC_8x5_LDR          MTLPP_AVAILABLE_IOS(8_0)     = 210,
        ASTC_8x6_LDR          MTLPP_AVAILABLE_IOS(8_0)     = 211,
        ASTC_8x8_LDR          MTLPP_AVAILABLE_IOS(8_0)     = 212,
        ASTC_10x5_LDR         MTLPP_AVAILABLE_IOS(8_0)     = 213,
        ASTC_10x6_LDR         MTLPP_AVAILABLE_IOS(8_0)     = 214,
        ASTC_10x8_LDR         MTLPP_AVAILABLE_IOS(8_0)     = 215,
        ASTC_10x10_LDR        MTLPP_AVAILABLE_IOS(8_0)     = 216,
        ASTC_12x10_LDR        MTLPP_AVAILABLE_IOS(8_0)     = 217,
        ASTC_12x12_LDR        MTLPP_AVAILABLE_IOS(8_0)     = 218,

        GBGR422                                            = 240,

        BGRG422                                            = 241,

        Depth16Unorm          MTLPP_AVAILABLE_MAC(10_12)   = 250,
        Depth32Float                                       = 252,

        Stencil8                                           = 253,

        Depth24Unorm_Stencil8 MTLPP_AVAILABLE_MAC(10_11)   = 255,
        Depth32Float_Stencil8 MTLPP_AVAILABLE(10_11, 9_0)  = 260,

        X32_Stencil8          MTLPP_AVAILABLE(10_12, 10_0) = 261,
        X24_Stencil8          MTLPP_AVAILABLE_MAC(10_12)   = 262,
    }
    MTLPP_AVAILABLE(10_11, 8_0);
}


//////////////////////////////////////
// FILE: resource.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"
// #include "ns.hpp"

namespace mtlpp
{
    class Heap;

    static const uint32_t ResourceCpuCacheModeShift        = 0;
    static const uint32_t ResourceStorageModeShift         = 4;
    static const uint32_t ResourceHazardTrackingModeShift  = 8;

    enum class PurgeableState
    {
        KeepCurrent = 1,
        NonVolatile = 2,
        Volatile    = 3,
        Empty       = 4,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class CpuCacheMode
    {
        DefaultCache  = 0,
        WriteCombined = 1,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class StorageMode
    {
        Shared                                = 0,
        Managed    MTLPP_AVAILABLE(10_11, NA) = 1,
        Private                               = 2,
        Memoryless MTLPP_AVAILABLE(NA, 10_0)  = 3,
    }
    MTLPP_AVAILABLE(10_11, 9_0);

    enum class ResourceOptions
    {
        CpuCacheModeDefaultCache                                = uint32_t(CpuCacheMode::DefaultCache)  << ResourceCpuCacheModeShift,
        CpuCacheModeWriteCombined                               = uint32_t(CpuCacheMode::WriteCombined) << ResourceCpuCacheModeShift,

        StorageModeShared           MTLPP_AVAILABLE(10_11, 9_0) = uint32_t(StorageMode::Shared)     << ResourceStorageModeShift,
        StorageModeManaged          MTLPP_AVAILABLE(10_11, NA)  = uint32_t(StorageMode::Managed)    << ResourceStorageModeShift,
        StorageModePrivate          MTLPP_AVAILABLE(10_11, 9_0) = uint32_t(StorageMode::Private)    << ResourceStorageModeShift,
        StorageModeMemoryless       MTLPP_AVAILABLE(NA, 10_0)   = uint32_t(StorageMode::Memoryless) << ResourceStorageModeShift,

        HazardTrackingModeUntracked MTLPP_AVAILABLE(NA, 10_0)   = 0x1 << ResourceHazardTrackingModeShift,

        OptionCPUCacheModeDefault                               = CpuCacheModeDefaultCache,
        OptionCPUCacheModeWriteCombined                         = CpuCacheModeWriteCombined,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class Resource : public ns::Object
    {
    public:
        Resource() { }
        Resource(const ns::Handle& handle) : ns::Object(handle) { }

        ns::String   GetLabel() const;
        CpuCacheMode GetCpuCacheMode() const;
        StorageMode  GetStorageMode() const MTLPP_AVAILABLE(10_11, 9_0);
        Heap         GetHeap() const MTLPP_AVAILABLE(NA, 10_0);
        bool         IsAliasable() const MTLPP_AVAILABLE(NA, 10_0);

        void SetLabel(const ns::String& label);

        PurgeableState SetPurgeableState(PurgeableState state);
        void MakeAliasable() const MTLPP_AVAILABLE(NA, 10_0);
    }
    MTLPP_AVAILABLE(10_11, 8_0);
}

//////////////////////////////////////
// FILE: buffer.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"
// #include "pixel_format.hpp"
// #include "resource.hpp"

namespace mtlpp
{
    class Texture;
    class TextureDescriptor;

    class Buffer : public Resource
    {
    public:
        Buffer() { }
        Buffer(const ns::Handle& handle) : Resource(handle) { }

        uint32_t GetLength() const;
        void*    GetContents();
        void     DidModify(const ns::Range& range) MTLPP_AVAILABLE_MAC(10_11);
        Texture  NewTexture(const TextureDescriptor& descriptor, uint32_t offset, uint32_t bytesPerRow) MTLPP_AVAILABLE_IOS(8_0);
        void     AddDebugMarker(const ns::String& marker, const ns::Range& range) MTLPP_AVAILABLE(10_12, 10_0);
        void     RemoveAllDebugMarkers() MTLPP_AVAILABLE(10_12, 10_0);
    }
    MTLPP_AVAILABLE(10_11, 8_0);
}

//////////////////////////////////////
// FILE: types.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"

namespace mtlpp
{
    struct Origin
    {
        inline Origin(uint32_t x, uint32_t y, uint32_t z) :
            X(x),
            Y(y),
            Z(z)
        { }

        uint32_t X;
        uint32_t Y;
        uint32_t Z;
    };

    struct Size
    {
        inline Size(uint32_t width, uint32_t height, uint32_t depth) :
            Width(width),
            Height(height),
            Depth(depth)
        { }

        uint32_t Width;
        uint32_t Height;
        uint32_t Depth;
    };

    struct Region
    {
        inline Region(uint32_t x, uint32_t width) :
            Origin(x, 0, 0),
            Size(width, 1, 1)
        { }

        inline Region(uint32_t x, uint32_t y, uint32_t width, uint32_t height) :
            Origin(x, y, 0),
            Size(width, height, 1)
        { }

        inline Region(uint32_t x, uint32_t y, uint32_t z, uint32_t width, uint32_t height, uint32_t depth) :
            Origin(x, y, z),
            Size(width, height, depth)
        { }

        Origin Origin;
        Size   Size;
    };
}

//////////////////////////////////////
// FILE: texture.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"
// #include "resource.hpp"
// #include "buffer.hpp"
// #include "types.hpp"

namespace mtlpp
{
    enum class TextureType
    {
        Texture1D                                       = 0,
        Texture1DArray                                  = 1,
        Texture2D                                       = 2,
        Texture2DArray                                  = 3,
        Texture2DMultisample                            = 4,
        TextureCube                                     = 5,
        TextureCubeArray     MTLPP_AVAILABLE_MAC(10_11) = 6,
        Texture3D                                       = 7,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class TextureUsage
    {
        Unknown         = 0x0000,
        ShaderRead      = 0x0001,
        ShaderWrite     = 0x0002,
        RenderTarget    = 0x0004,
        PixelFormatView = 0x0010,
    }
    MTLPP_AVAILABLE(10_11, 9_0);


    class TextureDescriptor : public ns::Object
    {
    public:
        TextureDescriptor();
        TextureDescriptor(const ns::Handle& handle) : ns::Object(handle) { }

        static TextureDescriptor Texture2DDescriptor(PixelFormat pixelFormat, uint32_t width, uint32_t height, bool mipmapped);
        static TextureDescriptor TextureCubeDescriptor(PixelFormat pixelFormat, uint32_t size, bool mipmapped);

        TextureType     GetTextureType() const;
        PixelFormat     GetPixelFormat() const;
        uint32_t        GetWidth() const;
        uint32_t        GetHeight() const;
        uint32_t        GetDepth() const;
        uint32_t        GetMipmapLevelCount() const;
        uint32_t        GetSampleCount() const;
        uint32_t        GetArrayLength() const;
        ResourceOptions GetResourceOptions() const;
        CpuCacheMode    GetCpuCacheMode() const MTLPP_AVAILABLE(10_11, 9_0);
        StorageMode     GetStorageMode() const MTLPP_AVAILABLE(10_11, 9_0);
        TextureUsage    GetUsage() const MTLPP_AVAILABLE(10_11, 9_0);

        void SetTextureType(TextureType textureType);
        void SetPixelFormat(PixelFormat pixelFormat);
        void SetWidth(uint32_t width);
        void SetHeight(uint32_t height);
        void SetDepth(uint32_t depth);
        void SetMipmapLevelCount(uint32_t mipmapLevelCount);
        void SetSampleCount(uint32_t sampleCount);
        void SetArrayLength(uint32_t arrayLength);
        void SetResourceOptions(ResourceOptions resourceOptions);
        void SetCpuCacheMode(CpuCacheMode cpuCacheMode) MTLPP_AVAILABLE(10_11, 9_0);
        void SetStorageMode(StorageMode storageMode) MTLPP_AVAILABLE(10_11, 9_0);
        void SetUsage(TextureUsage usage) MTLPP_AVAILABLE(10_11, 9_0);
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class Texture : public Resource
    {
    public:
        Texture() { }
        Texture(const ns::Handle& handle) : Resource(handle) { }

        Resource     GetRootResource() const MTLPP_DEPRECATED(10_11, 10_12, 8_0, 10_0);
        Texture      GetParentTexture() const MTLPP_AVAILABLE(10_11, 9_0);
        uint32_t     GetParentRelativeLevel() const MTLPP_AVAILABLE(10_11, 9_0);
        uint32_t     GetParentRelativeSlice() const MTLPP_AVAILABLE(10_11, 9_0);
        Buffer       GetBuffer() const MTLPP_AVAILABLE(10_12, 9_0);
        uint32_t     GetBufferOffset() const MTLPP_AVAILABLE(10_12, 9_0);
        uint32_t     GetBufferBytesPerRow() const MTLPP_AVAILABLE(10_12, 9_0);
        //IOSurfaceRef GetIOSurface() const;
        uint32_t     GetIOSurfacePlane() const MTLPP_AVAILABLE_MAC(10_11);
        TextureType  GetTextureType() const;
        PixelFormat  GetPixelFormat() const;
        uint32_t     GetWidth() const;
        uint32_t     GetHeight() const;
        uint32_t     GetDepth() const;
        uint32_t     GetMipmapLevelCount() const;
        uint32_t     GetSampleCount() const;
        uint32_t     GetArrayLength() const;
        TextureUsage GetUsage() const;
        bool         IsFrameBufferOnly() const;

        void GetBytes(void* pixelBytes, uint32_t bytesPerRow, uint32_t bytesPerImage, const Region& fromRegion, uint32_t mipmapLevel, uint32_t slice);
        void Replace(const Region& region, uint32_t mipmapLevel, uint32_t slice, void* pixelBytes, uint32_t bytesPerRow, uint32_t bytesPerImage);
        void GetBytes(void* pixelBytes, uint32_t bytesPerRow, const Region& fromRegion, uint32_t mipmapLevel);
        void Replace(const Region& region, uint32_t mipmapLevel, void* pixelBytes, uint32_t bytesPerRow);
        Texture NewTextureView(PixelFormat pixelFormat);
        Texture NewTextureView(PixelFormat pixelFormat, TextureType textureType, const ns::Range& mipmapLevelRange, const ns::Range& sliceRange);
    }
    MTLPP_AVAILABLE(10_11, 8_0);
}

//////////////////////////////////////
// FILE: argument.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"
// #include "texture.hpp"

namespace mtlpp
{
    class StructType;
    class ArrayType;

    enum class DataType
    {
        None     = 0,

        Struct   = 1,
        Array    = 2,

        Float    = 3,
        Float2   = 4,
        Float3   = 5,
        Float4   = 6,

        Float2x2 = 7,
        Float2x3 = 8,
        Float2x4 = 9,

        Float3x2 = 10,
        Float3x3 = 11,
        Float3x4 = 12,

        Float4x2 = 13,
        Float4x3 = 14,
        Float4x4 = 15,

        Half     = 16,
        Half2    = 17,
        Half3    = 18,
        Half4    = 19,

        Half2x2  = 20,
        Half2x3  = 21,
        Half2x4  = 22,

        Half3x2  = 23,
        Half3x3  = 24,
        Half3x4  = 25,

        Half4x2  = 26,
        Half4x3  = 27,
        Half4x4  = 28,

        Int      = 29,
        Int2     = 30,
        Int3     = 31,
        Int4     = 32,

        UInt     = 33,
        UInt2    = 34,
        UInt3    = 35,
        UInt4    = 36,

        Short    = 37,
        Short2   = 38,
        Short3   = 39,
        Short4   = 40,

        UShort   = 41,
        UShort2  = 42,
        UShort3  = 43,
        UShort4  = 44,

        Char     = 45,
        Char2    = 46,
        Char3    = 47,
        Char4    = 48,

        UChar    = 49,
        UChar2   = 50,
        UChar3   = 51,
        UChar4   = 52,

        Bool     = 53,
        Bool2    = 54,
        Bool3    = 55,
        Bool4    = 56,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class ArgumentType
    {
        Buffer            = 0,
        ThreadgroupMemory = 1,
        Texture           = 2,
        Sampler           = 3,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class ArgumentAccess
    {
        ReadOnly  = 0,
        ReadWrite = 1,
        WriteOnly = 2,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class StructMember : public ns::Object
    {
    public:
        StructMember();
        StructMember(const ns::Handle& handle) : ns::Object(handle) { }

        ns::String GetName() const;
        uint32_t   GetOffset() const;
        DataType   GetDataType() const;

        StructType GetStructType() const;
        ArrayType  GetArrayType() const;
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class StructType : public ns::Object
    {
    public:
        StructType();
        StructType(const ns::Handle& handle) : ns::Object(handle) { }

        const ns::Array<StructMember> GetMembers() const;
        StructMember                  GetMember(const ns::String& name) const;
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class ArrayType : public ns::Object
    {
    public:
        ArrayType();
        ArrayType(const ns::Handle& handle) : ns::Object(handle) { }

        uint32_t   GetArrayLength() const;
        DataType   GetElementType() const;
        uint32_t   GetStride() const;
        StructType GetElementStructType() const;
        ArrayType  GetElementArrayType() const;
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class Argument : public ns::Object
    {
    public:
        Argument();
        Argument(const ns::Handle& handle) : ns::Object(handle) { }

        ns::String     GetName() const;
        ArgumentType   GetType() const;
        ArgumentAccess GetAccess() const;
        uint32_t       GetIndex() const;

        bool           IsActive() const;

        uint32_t       GetBufferAlignment() const;
        uint32_t       GetBufferDataSize() const;
        DataType       GetBufferDataType() const;
        StructType     GetBufferStructType() const;

        uint32_t       GetThreadgroupMemoryAlignment() const;
        uint32_t       GetThreadgroupMemoryDataSize() const;

        TextureType    GetTextureType() const;
        DataType       GetTextureDataType() const;

        bool           IsDepthTexture() const MTLPP_AVAILABLE(10_12, 10_0);
    }
    MTLPP_AVAILABLE(10_11, 8_0);
}


//////////////////////////////////////
// FILE: library.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"
// #include "ns.hpp"
// #include "argument.hpp"

namespace mtlpp
{
    class Device;
    class FunctionConstantValues;

    enum class PatchType
    {
        None     = 0,
        Triangle = 1,
        Quad     = 2,
    }
    MTLPP_AVAILABLE(10_12, 10_0);

    class VertexAttribute : public ns::Object
    {
    public:
        VertexAttribute();
        VertexAttribute(const ns::Handle& handle) : ns::Object(handle) { }

        ns::String   GetName() const;
        uint32_t     GetAttributeIndex() const;
        DataType     GetAttributeType() const MTLPP_AVAILABLE(10_11, 8_3);
        bool         IsActive() const;
        bool         IsPatchData() const MTLPP_AVAILABLE(10_12, 10_0);
        bool         IsPatchControlPointData() const MTLPP_AVAILABLE(10_12, 10_0);
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class Attribute : public ns::Object
    {
    public:
        Attribute();
        Attribute(const ns::Handle& handle) : ns::Object(handle) { }

        ns::String   GetName() const;
        uint32_t     GetAttributeIndex() const;
        DataType     GetAttributeType() const MTLPP_AVAILABLE(10_11, 8_3);
        bool         IsActive() const;
        bool         IsPatchData() const MTLPP_AVAILABLE(10_12, 10_0);
        bool         IsPatchControlPointData() const MTLPP_AVAILABLE(10_12, 10_0);
    }
    MTLPP_AVAILABLE(10_12, 10_0);

    enum class FunctionType
    {
        TypeVertex   = 1,
        TypeFragment = 2,
        TypeKernel   = 3,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class FunctionConstant : public ns::Object
    {
    public:
        FunctionConstant();
        FunctionConstant(const ns::Handle& handle) : ns::Object(handle) { }

        ns::String GetName() const;
        DataType   GetType() const;
        uint32_t   GetIndex() const;
        bool       IsRequired() const;
    }
    MTLPP_AVAILABLE(10_12, 10_0);

    class Function : public ns::Object
    {
    public:
        Function(const ns::Handle& handle) : ns::Object(handle) { }

        ns::String                                   GetLabel() const MTLPP_AVAILABLE(10_12, 10_0);
        Device                                       GetDevice() const;
        FunctionType                                 GetFunctionType() const;
        PatchType                                    GetPatchType() const MTLPP_AVAILABLE(10_12, 10_0);
        int32_t                                      GetPatchControlPointCount() const MTLPP_AVAILABLE(10_12, 10_0);
        const ns::Array<VertexAttribute>             GetVertexAttributes() const;
        const ns::Array<Attribute>                   GetStageInputAttributes() const MTLPP_AVAILABLE(10_12, 10_0);
        ns::String                                   GetName() const;
        ns::Dictionary<ns::String, FunctionConstant> GetFunctionConstants() const MTLPP_AVAILABLE(10_12, 10_0);

        void SetLabel(const ns::String& label) MTLPP_AVAILABLE(10_12, 10_0);
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class LanguageVersion
    {
        Version1_0 MTLPP_AVAILABLE(NA, 9_0)     = (1 << 16),
        Version1_1 MTLPP_AVAILABLE(10_11, 9_0)  = (1 << 16) + 1,
        Version1_2 MTLPP_AVAILABLE(10_12, 10_0) = (1 << 16) + 2,
    }
    MTLPP_AVAILABLE(10_11, 9_0);

    class CompileOptions : public ns::Object
    {
    public:
        CompileOptions();
        CompileOptions(const ns::Handle& handle) : ns::Object(handle) { }

        ns::Dictionary<ns::String, ns::String> GetPreprocessorMacros() const;
        bool                                   IsFastMathEnabled() const;
        LanguageVersion                        GetLanguageVersion() const MTLPP_AVAILABLE(10_11, 9_0);

        void SetFastMathEnabled(bool fastMathEnabled);
        void SetFastMathEnabled(LanguageVersion languageVersion);
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class LibraryError
    {
        Unsupported                                   = 1,
        Internal                                      = 2,
        CompileFailure                                = 3,
        CompileWarning                                = 4,
        FunctionNotFound MTLPP_AVAILABLE(10_12, 10_0) = 5,
        FileNotFound     MTLPP_AVAILABLE(10_12, 10_0) = 6,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class RenderPipelineError
    {
        Internal     = 1,
        Unsupported  = 2,
        InvalidInput = 3,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class Library : public ns::Object
    {
    public:
        Library() { }
        Library(const ns::Handle& handle) : ns::Object(handle) { }

        ns::String            GetLabel() const;
        Device                GetDevice() const;
        ns::Array<ns::String> GetFunctionNames() const;

        void SetLabel(const ns::String& label);

        Function NewFunction(const ns::String& functionName);
        Function NewFunction(const ns::String& functionName, const FunctionConstantValues& constantValues, ns::Error* error) MTLPP_AVAILABLE(10_12, 10_0);
        void NewFunction(const ns::String& functionName, const FunctionConstantValues& constantValues, std::function<void(const Function&, const ns::Error&)> completionHandler) MTLPP_AVAILABLE(10_12, 10_0);
    }
    MTLPP_AVAILABLE(10_11, 8_0);
}

//////////////////////////////////////
// FILE: device.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"
// #include "types.hpp"
// #include "pixel_format.hpp"
// #include "resource.hpp"
// #include "library.hpp"

namespace mtlpp
{
    class CommandQueue;
    class Device;
    class Buffer;
    class DepthStencilState;
    class Function;
    class Library;
    class Texture;
    class SamplerState;
    class RenderPipelineState;
    class ComputePipelineState;
    class Heap;
    class Fence;

    class SamplerDescriptor;
    class RenderPipelineColorAttachmentDescriptor;
    class DepthStencilDescriptor;
    class TextureDescriptor;
    class CompileOptions;
    class RenderPipelineDescriptor;
    class RenderPassDescriptor;
    class RenderPipelineReflection;
    class ComputePipelineDescriptor;
    class ComputePipelineReflection;
    class CommandQueueDescriptor;
    class HeapDescriptor;

    enum class FeatureSet
    {
        iOS_GPUFamily1_v1         MTLPP_AVAILABLE_IOS(8_0)   = 0,
        iOS_GPUFamily2_v1         MTLPP_AVAILABLE_IOS(8_0)   = 1,

        iOS_GPUFamily1_v2         MTLPP_AVAILABLE_IOS(8_0)   = 2,
        iOS_GPUFamily2_v2         MTLPP_AVAILABLE_IOS(8_0)   = 3,
        iOS_GPUFamily3_v1         MTLPP_AVAILABLE_IOS(9_0)   = 4,

        iOS_GPUFamily1_v3         MTLPP_AVAILABLE_IOS(10_0)  = 5,
        iOS_GPUFamily2_v3         MTLPP_AVAILABLE_IOS(10_0)  = 6,
        iOS_GPUFamily3_v2         MTLPP_AVAILABLE_IOS(10_0)  = 7,

        OSX_GPUFamily1_v1         MTLPP_AVAILABLE_MAC(8_0)   = 10000,

        OSX_GPUFamily1_v2         MTLPP_AVAILABLE_MAC(10_12) = 10001,
        OSX_ReadWriteTextureTier2 MTLPP_AVAILABLE_MAC(10_12) = 10002,

        tvOS_GPUFamily1_v1        MTLPP_AVAILABLE_TVOS(9_0)  = 30000,

        tvOS_GPUFamily1_v2        MTLPP_AVAILABLE_TVOS(10_0) = 30001,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class PipelineOption
    {
        None           = 0,
        ArgumentInfo   = 1 << 0,
        BufferTypeInfo = 1 << 1,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    struct SizeAndAlign
    {
        uint32_t Size;
        uint32_t Align;
    };

    class Device : public ns::Object
    {
    public:
        Device() { }
        Device(const ns::Handle& handle) : ns::Object(handle) { }

        static Device CreateSystemDefaultDevice() MTLPP_AVAILABLE(10_11, 8_0);
        static ns::Array<Device> CopyAllDevices() MTLPP_AVAILABLE(10_11, NA);

        ns::String GetName() const;
        Size       GetMaxThreadsPerThreadgroup() const MTLPP_AVAILABLE(10_11, 9_0);
        bool       IsLowPower() const MTLPP_AVAILABLE_MAC(10_11);
        bool       IsHeadless() const MTLPP_AVAILABLE_MAC(10_11);
        uint64_t   GetRecommendedMaxWorkingSetSize() const MTLPP_AVAILABLE_MAC(10_12);
        bool       IsDepth24Stencil8PixelFormatSupported() const MTLPP_AVAILABLE_MAC(10_11);

        CommandQueue NewCommandQueue();
        CommandQueue NewCommandQueue(uint32_t maxCommandBufferCount);
        SizeAndAlign HeapTextureSizeAndAlign(const TextureDescriptor& desc) MTLPP_AVAILABLE(NA, 10_0);
        SizeAndAlign HeapBufferSizeAndAlign(uint32_t length, ResourceOptions options) MTLPP_AVAILABLE(NA, 10_0);
        Heap NewHeap(const HeapDescriptor& descriptor) MTLPP_AVAILABLE(NA, 10_0);
        Buffer NewBuffer(uint32_t length, ResourceOptions options);
        Buffer NewBuffer(const void* pointer, uint32_t length, ResourceOptions options);
        Buffer NewBuffer(void* pointer, uint32_t length, ResourceOptions options, std::function<void (void* pointer, uint32_t length)> deallocator);
        DepthStencilState NewDepthStencilState(const DepthStencilDescriptor& descriptor);
        Texture NewTexture(const TextureDescriptor& descriptor);
        //- (id <MTLTexture>)newTextureWithDescriptor:(MTLTextureDescriptor *)descriptor iosurface:(IOSurfaceRef)iosurface plane:(NSUInteger)plane NS_AVAILABLE_MAC(10_11);
        SamplerState NewSamplerState(const SamplerDescriptor& descriptor);
        Library NewDefaultLibrary();
        //- (nullable id <MTLLibrary>)newDefaultLibraryWithBundle:(NSBundle *)bundle error:(__autoreleasing NSError **)error NS_AVAILABLE(10_12, 10_0);
        Library NewLibrary(const ns::String& filepath, ns::Error* error);
        Library NewLibrary(const char* source, const CompileOptions& options, ns::Error* error);
        void NewLibrary(const char* source, const CompileOptions& options, std::function<void(const Library&, const ns::Error&)> completionHandler);
        RenderPipelineState NewRenderPipelineState(const RenderPipelineDescriptor& descriptor, ns::Error* error);
        RenderPipelineState NewRenderPipelineState(const RenderPipelineDescriptor& descriptor, PipelineOption options, RenderPipelineReflection* outReflection, ns::Error* error);
        void NewRenderPipelineState(const RenderPipelineDescriptor& descriptor, std::function<void(const RenderPipelineState&, const ns::Error&)> completionHandler);
        void NewRenderPipelineState(const RenderPipelineDescriptor& descriptor, PipelineOption options, std::function<void(const RenderPipelineState&, const RenderPipelineReflection&, const ns::Error&)> completionHandler);
        ComputePipelineState NewComputePipelineState(const Function& computeFunction, ns::Error* error);
        ComputePipelineState NewComputePipelineState(const Function& computeFunction, PipelineOption options, ComputePipelineReflection& outReflection, ns::Error* error);
        void NewComputePipelineState(const Function& computeFunction, std::function<void(const ComputePipelineState&, const ns::Error&)> completionHandler);
        void NewComputePipelineState(const Function& computeFunction, PipelineOption options, std::function<void(const ComputePipelineState&, const ComputePipelineReflection&, const ns::Error&)> completionHandler);
        ComputePipelineState NewComputePipelineState(const ComputePipelineDescriptor& descriptor, PipelineOption options, ComputePipelineReflection* outReflection, ns::Error* error);
        void NewComputePipelineState(const ComputePipelineDescriptor& descriptor, PipelineOption options, std::function<void(const ComputePipelineState&, const ComputePipelineReflection&, const ns::Error&)> completionHandler) MTLPP_AVAILABLE(10_11, 9_0);
        Fence NewFence() MTLPP_AVAILABLE(NA, 10_0);
        bool SupportsFeatureSet(FeatureSet featureSet) const;
        bool SupportsTextureSampleCount(uint32_t sampleCount) const MTLPP_AVAILABLE(10_11, 9_0);
    }
    MTLPP_AVAILABLE(10_11, 8_0);
}

//////////////////////////////////////
// FILE: fence.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"
// #include "ns.hpp"
// #include "device.hpp"


namespace mtlpp
{
    class Fence : public ns::Object
    {
    public:
        Fence(const ns::Handle& handle) : ns::Object(handle) { }

        Texture    GetDevice() const;
        ns::String GetLabel() const;

        void SetLabel(const ns::String& label);
    }
    MTLPP_AVAILABLE(NA, 10_0);
}

//////////////////////////////////////
// FILE: blit_command_encoder.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"
// #include "command_encoder.hpp"
// #include "buffer.hpp"
// #include "texture.hpp"
// #include "fence.hpp"

namespace mtlpp
{
    enum class BlitOption
    {
        None                                             = 0,
        DepthFromDepthStencil                            = 1 << 0,
        StencilFromDepthStencil                          = 1 << 1,
        RowLinearPVRTC          MTLPP_AVAILABLE_IOS(9_0) = 1 << 2,
    }
    MTLPP_AVAILABLE(10_11, 9_0);

    class BlitCommandEncoder : public ns::Object
    {
    public:
        BlitCommandEncoder() { }
        BlitCommandEncoder(const ns::Handle& handle) : ns::Object(handle) { }

        void Synchronize(const Resource& resource) MTLPP_AVAILABLE_MAC(10_11);
        void Synchronize(const Texture& texture, uint32_t slice, uint32_t level) MTLPP_AVAILABLE_MAC(10_11);
        void Copy(const Texture& sourceTexture, uint32_t sourceSlice, uint32_t sourceLevel, const Origin& sourceOrigin, const Size& sourceSize, const Texture& destinationTexture, uint32_t destinationSlice, uint32_t destinationLevel, const Origin& destinationOrigin);
        void Copy(const Buffer& sourceBuffer, uint32_t sourceOffset, uint32_t sourceBytesPerRow, uint32_t sourceBytesPerImage, const Size& sourceSize, const Texture& destinationTexture, uint32_t destinationSlice, uint32_t destinationLevel, const Origin& destinationOrigin);
        void Copy(const Buffer& sourceBuffer, uint32_t sourceOffset, uint32_t sourceBytesPerRow, uint32_t sourceBytesPerImage, const Size& sourceSize, const Texture& destinationTexture, uint32_t destinationSlice, uint32_t destinationLevel, const Origin& destinationOrigin, BlitOption options);
        void Copy(const Texture& sourceTexture, uint32_t sourceSlice, uint32_t sourceLevel, const Origin& sourceOrigin, const Size& sourceSize, const Buffer& destinationBuffer, uint32_t destinationOffset, uint32_t destinationBytesPerRow, uint32_t destinationBytesPerImage);
        void Copy(const Texture& sourceTexture, uint32_t sourceSlice, uint32_t sourceLevel, const Origin& sourceOrigin, const Size& sourceSize, const Buffer& destinationBuffer, uint32_t destinationOffset, uint32_t destinationBytesPerRow, uint32_t destinationBytesPerImage, BlitOption options);
        void Copy(const Buffer& sourceBuffer, uint32_t soruceOffset, const Buffer& destinationBuffer, uint32_t destinationOffset, uint32_t size);
        void GenerateMipmaps(const Texture& texture);
        void Fill(const Buffer& buffer, const ns::Range& range, uint8_t value);
        void UpdateFence(const Fence& fence) MTLPP_AVAILABLE_IOS(10_0);
        void WaitForFence(const Fence& fence) MTLPP_AVAILABLE_IOS(10_0);
    };
}

//////////////////////////////////////
// FILE: command_buffer.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"
// #include "ns.hpp"

namespace mtlpp
{
    class Device;
    class CommandQueue;
    class BlitCommandEncoder;
    class RenderCommandEncoder;
    class ParallelRenderCommandEncoder;
    class ComputeCommandEncoder;
    class CommandQueue;
    class Drawable;
    class RenderPassDescriptor;

    enum class CommandBufferStatus
    {
        NotEnqueued = 0,
        Enqueued    = 1,
        Committed   = 2,
        Scheduled   = 3,
        Completed   = 4,
        Error       = 5,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class CommandBufferError
    {
        None                                      = 0,
        Internal                                  = 1,
        Timeout                                   = 2,
        PageFault                                 = 3,
        Blacklisted                               = 4,
        NotPermitted                              = 7,
        OutOfMemory                               = 8,
        InvalidResource                           = 9,
        Memoryless      MTLPP_AVAILABLE_IOS(10_0) = 10,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class CommandBuffer : public ns::Object
    {
    public:
        CommandBuffer() { }
        CommandBuffer(const ns::Handle& handle) : ns::Object(handle) { }

        Device              GetDevice() const;
        CommandQueue        GetCommandQueue() const;
        bool                GetRetainedReferences() const;
        ns::String          GetLabel() const;
        CommandBufferStatus GetStatus() const;
        ns::Error           GetError() const;

        void SetLabel(const ns::String& label);

        void Enqueue();
        void Commit();
        void AddScheduledHandler(std::function<void(const CommandBuffer&)> handler);
        void AddCompletedHandler(std::function<void(const CommandBuffer&)> handler);
        void Present(const Drawable& drawable);
        void Present(const Drawable& drawable, double presentationTime);
        void WaitUntilScheduled();
        void WaitUntilCompleted();
        BlitCommandEncoder BlitCommandEncoder();
        RenderCommandEncoder RenderCommandEncoder(const RenderPassDescriptor& renderPassDescriptor);
        ComputeCommandEncoder ComputeCommandEncoder();
        ParallelRenderCommandEncoder ParallelRenderCommandEncoder(const RenderPassDescriptor& renderPassDescriptor);
    }
    MTLPP_AVAILABLE(10_11, 8_0);
}

//////////////////////////////////////
// FILE: compute_command_encoder.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"
// #include "ns.hpp"
// #include "command_encoder.hpp"
// #include "texture.hpp"
// #include "command_buffer.hpp"
// #include "fence.hpp"

namespace mtlpp
{
    class ComputeCommandEncoder : public CommandEncoder
    {
    public:
        ComputeCommandEncoder() { }
        ComputeCommandEncoder(const ns::Handle& handle) : CommandEncoder(handle) { }

        void SetComputePipelineState(const ComputePipelineState& state);
        void SetBytes(const void* data, uint32_t length, uint32_t index);
        void SetBuffer(const Buffer& buffer, uint32_t offset, uint32_t index);
        void SetBufferOffset(uint32_t offset, uint32_t index) MTLPP_AVAILABLE(10_11, 8_3);
        void SetBuffers(const Buffer* buffers, const uint32_t* offsets, const ns::Range& range);
        void SetTexture(const Texture& texture, uint32_t index);
        void SetTextures(const Texture* textures, const ns::Range& range);
        void SetSamplerState(const SamplerState& sampler, uint32_t index);
        void SetSamplerStates(const SamplerState* samplers, const ns::Range& range);
        void SetSamplerState(const SamplerState& sampler, float lodMinClamp, float lodMaxClamp, uint32_t index);
        void SetSamplerStates(const SamplerState* samplers, const float* lodMinClamps, const float* lodMaxClamps, const ns::Range& range);
        void SetThreadgroupMemory(uint32_t length, uint32_t index);
        void SetStageInRegion(const Region& region) MTLPP_AVAILABLE(10_12, 10_0);
        void DispatchThreadgroups(const Size& threadgroupsPerGrid, const Size& threadsPerThreadgroup);
        void DispatchThreadgroupsWithIndirectBuffer(const Buffer& indirectBuffer, uint32_t indirectBufferOffset, const Size& threadsPerThreadgroup);
        void UpdateFence(const Fence& fence) MTLPP_AVAILABLE_IOS(10_0);
        void WaitForFence(const Fence& fence) MTLPP_AVAILABLE_IOS(10_0);
    }
    MTLPP_AVAILABLE(10_11, 8_0);
}

//////////////////////////////////////
// FILE: command_queue.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"
// #include "ns.hpp"

namespace mtlpp
{
    class Device;
    class CommandBuffer;

    class CommandQueue : public ns::Object
    {
    public:
        CommandQueue() { }
        CommandQueue(const ns::Handle& handle) : ns::Object(handle) { }

        ns::String GetLabel() const;
        Device     GetDevice() const;

        void SetLabel(const ns::String& label);

        class CommandBuffer CommandBufferWithUnretainedReferences();
        class CommandBuffer CommandBuffer();
        void                InsertDebugCaptureBoundary();
    }
    MTLPP_AVAILABLE(10_11, 8_0);
}

//////////////////////////////////////
// FILE: depth_stencil.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"
// #include "ns.hpp"
// #include "device.hpp"

namespace mtlpp
{
    enum class CompareFunction
    {
        Never        = 0,
        Less         = 1,
        Equal        = 2,
        LessEqual    = 3,
        Greater      = 4,
        NotEqual     = 5,
        GreaterEqual = 6,
        Always       = 7,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class StencilOperation
    {
        Keep           = 0,
        Zero           = 1,
        Replace        = 2,
        IncrementClamp = 3,
        DecrementClamp = 4,
        Invert         = 5,
        IncrementWrap  = 6,
        DecrementWrap  = 7,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class StencilDescriptor : public ns::Object
    {
    public:
        StencilDescriptor();
        StencilDescriptor(const ns::Handle& handle) : ns::Object(handle) { }

        CompareFunction  GetStencilCompareFunction() const;
        StencilOperation GetStencilFailureOperation() const;
        StencilOperation GetDepthFailureOperation() const;
        StencilOperation GetDepthStencilPassOperation() const;
        uint32_t         GetReadMask() const;
        uint32_t         GetWriteMask() const;

        void SetStencilCompareFunction(CompareFunction stencilCompareFunction);
        void SetStencilFailureOperation(StencilOperation stencilFailureOperation);
        void SetDepthFailureOperation(StencilOperation depthFailureOperation);
        void SetDepthStencilPassOperation(StencilOperation depthStencilPassOperation);
        void SetReadMask(uint32_t readMask);
        void SetWriteMask(uint32_t writeMask);
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class DepthStencilDescriptor : public ns::Object
    {
    public:
        DepthStencilDescriptor();
        DepthStencilDescriptor(const ns::Handle& handle) : ns::Object(handle) { }

        CompareFunction   GetDepthCompareFunction() const;
        bool              IsDepthWriteEnabled() const;
        StencilDescriptor GetFrontFaceStencil() const;
        StencilDescriptor GetBackFaceStencil() const;
        ns::String        GetLabel() const;

        void SetDepthCompareFunction(CompareFunction depthCompareFunction) const;
        void SetDepthWriteEnabled(bool depthWriteEnabled) const;
        void SetFrontFaceStencil(const StencilDescriptor& frontFaceStencil) const;
        void SetBackFaceStencil(const StencilDescriptor& backFaceStencil) const;
        void SetLabel(const ns::String& label) const;
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class DepthStencilState : public ns::Object
    {
    public:
        DepthStencilState() { }
        DepthStencilState(const ns::Handle& handle) : ns::Object(handle) { }

        ns::String GetLabel() const;
        Device     GetDevice() const;
    }
    MTLPP_AVAILABLE(10_11, 8_0);
}

//////////////////////////////////////
// FILE: drawable.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"
// #include "ns.hpp"

namespace mtlpp
{
    class Drawable : public ns::Object
    {
    public:
        Drawable() { }
        Drawable(const ns::Handle& handle) : ns::Object(handle) { }

        void Present();
        void Present(double presentationTime);
    }
    MTLPP_AVAILABLE(10_11, 8_0);
}


//////////////////////////////////////
// FILE: render_pass.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"
// #include "ns.hpp"

namespace mtlpp
{
    class Texture;
    class Buffer;

    enum class LoadAction
    {
        DontCare = 0,
        Load     = 1,
        Clear    = 2,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class StoreAction
    {
        DontCare                                               = 0,
        Store                                                  = 1,
        MultisampleResolve                                     = 2,
        StoreAndMultisampleResolve MTLPP_AVAILABLE(10_12,10_0) = 3,
        Unknown                    MTLPP_AVAILABLE(10_12,10_0) = 4,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class MultisampleDepthResolveFilter
    {
        Sample0 = 0,
        Min     = 1,
        Max     = 2,
    }
    MTLPP_AVAILABLE_IOS(9_0);

    struct ClearColor
    {
        ClearColor(double red, double green, double blue, double alpha) :
            Red(red),
            Green(green),
            Blue(blue),
            Alpha(alpha) { }

        double Red;
        double Green;
        double Blue;
        double Alpha;
    };

    class RenderPassAttachmentDescriptor : public ns::Object
    {
    public:
        RenderPassAttachmentDescriptor();
        RenderPassAttachmentDescriptor(const ns::Handle& handle) : ns::Object(handle) { }

        Texture     GetTexture() const;
        uint32_t    GetLevel() const;
        uint32_t    GetSlice() const;
        uint32_t    GetDepthPlane() const;
        Texture     GetResolveTexture() const;
        uint32_t    GetResolveLevel() const;
        uint32_t    GetResolveSlice() const;
        uint32_t    GetResolveDepthPlane() const;
        LoadAction  GetLoadAction() const;
        StoreAction GetStoreAction() const;

        void SetTexture(const Texture& texture);
        void SetLevel(uint32_t level);
        void SetSlice(uint32_t slice);
        void SetDepthPlane(uint32_t depthPlane);
        void SetResolveTexture(const Texture& texture);
        void SetResolveLevel(uint32_t resolveLevel);
        void SetResolveSlice(uint32_t resolveSlice);
        void SetResolveDepthPlane(uint32_t resolveDepthPlane);
        void SetLoadAction(LoadAction loadAction);
        void SetStoreAction(StoreAction storeAction);
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class RenderPassColorAttachmentDescriptor : public RenderPassAttachmentDescriptor
    {
    public:
        RenderPassColorAttachmentDescriptor();
        RenderPassColorAttachmentDescriptor(const ns::Handle& handle) : RenderPassAttachmentDescriptor(handle) { }

        ClearColor GetClearColor() const;

        void SetClearColor(const ClearColor& clearColor);
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class RenderPassDepthAttachmentDescriptor : public RenderPassAttachmentDescriptor
    {
    public:
        RenderPassDepthAttachmentDescriptor();
        RenderPassDepthAttachmentDescriptor(const ns::Handle& handle) : RenderPassAttachmentDescriptor(handle) { }

        double                        GetClearDepth() const;
        MultisampleDepthResolveFilter GetDepthResolveFilter() const MTLPP_AVAILABLE_IOS(9_0);

        void SetClearDepth(double clearDepth);
        void SetDepthResolveFilter(MultisampleDepthResolveFilter depthResolveFilter) MTLPP_AVAILABLE_IOS(9_0);
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class RenderPassStencilAttachmentDescriptor : public RenderPassAttachmentDescriptor
    {
    public:
        RenderPassStencilAttachmentDescriptor();
        RenderPassStencilAttachmentDescriptor(const ns::Handle& handle) : RenderPassAttachmentDescriptor(handle) { }

        uint32_t GetClearStencil() const;

        void SetClearStencil(uint32_t clearStencil);
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class RenderPassDescriptor : public ns::Object
    {
    public:
        RenderPassDescriptor();
        RenderPassDescriptor(const ns::Handle& handle) : ns::Object(handle) { }

        ns::Array<RenderPassColorAttachmentDescriptor> GetColorAttachments() const;
        RenderPassDepthAttachmentDescriptor   GetDepthAttachment() const;
        RenderPassStencilAttachmentDescriptor GetStencilAttachment() const;
        Buffer                                GetVisibilityResultBuffer() const;
        uint32_t                              GetRenderTargetArrayLength() const MTLPP_AVAILABLE_MAC(10_11);

        void SetDepthAttachment(const RenderPassDepthAttachmentDescriptor& depthAttachment);
        void SetStencilAttachment(const RenderPassStencilAttachmentDescriptor& stencilAttachment);
        void SetVisibilityResultBuffer(const Buffer& visibilityResultBuffer);
        void SetRenderTargetArrayLength(uint32_t renderTargetArrayLength) MTLPP_AVAILABLE_MAC(10_11);
    }
    MTLPP_AVAILABLE(10_11, 8_0);
}

//////////////////////////////////////
// FILE: stage_input_output_descriptor.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"
// #include "device.hpp"

namespace mtlpp
{
    enum class AttributeFormat
    {
        Invalid               = 0,

        UChar2                = 1,
        UChar3                = 2,
        UChar4                = 3,

        Char2                 = 4,
        Char3                 = 5,
        Char4                 = 6,

        UChar2Normalized      = 7,
        UChar3Normalized      = 8,
        UChar4Normalized      = 9,

        Char2Normalized       = 10,
        Char3Normalized       = 11,
        Char4Normalized       = 12,

        UShort2               = 13,
        UShort3               = 14,
        UShort4               = 15,

        Short2                = 16,
        Short3                = 17,
        Short4                = 18,

        UShort2Normalized     = 19,
        UShort3Normalized     = 20,
        UShort4Normalized     = 21,

        Short2Normalized      = 22,
        Short3Normalized      = 23,
        Short4Normalized      = 24,

        Half2                 = 25,
        Half3                 = 26,
        Half4                 = 27,

        Float                 = 28,
        Float2                = 29,
        Float3                = 30,
        Float4                = 31,

        Int                   = 32,
        Int2                  = 33,
        Int3                  = 34,
        Int4                  = 35,

        UInt                  = 36,
        UInt2                 = 37,
        UInt3                 = 38,
        UInt4                 = 39,

        Int1010102Normalized  = 40,
        UInt1010102Normalized = 41,
    }
    MTLPP_AVAILABLE(10_12, 10_0);

    enum class IndexType
    {
        UInt16 = 0,
        UInt32 = 1,
    }
    MTLPP_AVAILABLE(10_11, 8_0);


    enum class StepFunction
    {
        Constant                                                  = 0,

        PerVertex                                                 = 1,
        PerInstance                                               = 2,
        PerPatch                     MTLPP_AVAILABLE(10_12, 10_0) = 3,
        PerPatchControlPoint         MTLPP_AVAILABLE(10_12, 10_0) = 4,

        ThreadPositionInGridX                                     = 5,
        ThreadPositionInGridY                                     = 6,
        ThreadPositionInGridXIndexed                              = 7,
        ThreadPositionInGridYIndexed                              = 8,
    }
    MTLPP_AVAILABLE(10_12, 10_0);

    class BufferLayoutDescriptor : public ns::Object
    {
    public:
        BufferLayoutDescriptor();
        BufferLayoutDescriptor(const ns::Handle& handle) : ns::Object(handle) { }

        uint32_t     GetStride() const;
        StepFunction GetStepFunction() const;
        uint32_t     GetStepRate() const;

        void SetStride(uint32_t stride);
        void SetStepFunction(StepFunction stepFunction);
        void SetStepRate(uint32_t stepRate);
    }
    MTLPP_AVAILABLE(10_12, 10_0);

    class AttributeDescriptor : public ns::Object
    {
    public:
        AttributeDescriptor();
        AttributeDescriptor(const ns::Handle& handle) : ns::Object(handle) { }

        AttributeFormat GetFormat() const;
        uint32_t        GetOffset() const;
        uint32_t        GetBufferIndex() const;

        void SetFormat(AttributeFormat format);
        void SetOffset(uint32_t offset);
        void SetBufferIndex(uint32_t bufferIndex);
    }
    MTLPP_AVAILABLE(10_12, 10_0);

    class StageInputOutputDescriptor : public ns::Object
    {
    public:
        StageInputOutputDescriptor();
        StageInputOutputDescriptor(const ns::Handle& handle) : ns::Object(handle) { }


        ns::Array<BufferLayoutDescriptor> GetLayouts() const;
        ns::Array<AttributeDescriptor>    GetAttributes() const;
        IndexType                         GetIndexType() const;
        uint32_t                          GetIndexBufferIndex() const;

        void SetIndexType(IndexType indexType);
        void SetIndexBufferIndex(uint32_t indexBufferIndex);

        void Reset();
    }
    MTLPP_AVAILABLE(10_12, 10_0);
}

//////////////////////////////////////
// FILE: compute_pipeline.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"
// #include "device.hpp"
// #include "argument.hpp"
// #include "stage_input_output_descriptor.hpp"

namespace mtlpp
{
    class ComputePipelineReflection : public ns::Object
    {
    public:
        ComputePipelineReflection();
        ComputePipelineReflection(const ns::Handle& handle) : ns::Object(handle) { }

        ns::Array<Argument> GetArguments() const;
    }
    MTLPP_AVAILABLE(10_11, 9_0);

    class ComputePipelineDescriptor : public ns::Object
    {
    public:
        ComputePipelineDescriptor();
        ComputePipelineDescriptor(const ns::Handle& handle) : ns::Object(handle) { }

        ns::String                 GetLabel() const;
        Function                   GetComputeFunction() const;
        bool                       GetThreadGroupSizeIsMultipleOfThreadExecutionWidth() const;
        StageInputOutputDescriptor GetStageInputDescriptor() const MTLPP_AVAILABLE(10_12, 10_0);

        void SetLabel(const ns::String& label);
        void SetComputeFunction(const Function& function);
        void SetThreadGroupSizeIsMultipleOfThreadExecutionWidth(bool value);
        void SetStageInputDescriptor(const StageInputOutputDescriptor& stageInputDescriptor) const MTLPP_AVAILABLE(10_12, 10_0);

        void Reset();
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class ComputePipelineState : public ns::Object
    {
    public:
        ComputePipelineState() { }
        ComputePipelineState(const ns::Handle& handle) : ns::Object(handle) { }

        Device   GetDevice() const;
        uint32_t GetMaxTotalThreadsPerThreadgroup() const;
        uint32_t GetThreadExecutionWidth() const;
    }
    MTLPP_AVAILABLE(10_11, 8_0);
}

//////////////////////////////////////
// FILE: render_command_encoder.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"
// #include "command_encoder.hpp"
// #include "command_buffer.hpp"
// #include "render_pass.hpp"
// #include "fence.hpp"
// #include "stage_input_output_descriptor.hpp"

namespace mtlpp
{
    enum class PrimitiveType
    {
        Point         = 0,
        Line          = 1,
        LineStrip     = 2,
        Triangle      = 3,
        TriangleStrip = 4,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class VisibilityResultMode
    {
        Disabled                             = 0,
        Boolean                              = 1,
        Counting MTLPP_AVAILABLE(10_11, 9_0) = 2,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    struct ScissorRect
    {
        uint32_t X;
        uint32_t Y;
        uint32_t Width;
        uint32_t Height;
    };

    struct Viewport
    {
        double OriginX;
        double OriginY;
        double Width;
        double Height;
        double ZNear;
        double ZFar;
    };

    enum class CullMode
    {
        None  = 0,
        Front = 1,
        Back  = 2,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class Winding
    {
        Clockwise        = 0,
        CounterClockwise = 1,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class DepthClipMode
    {
        Clip  = 0,
        Clamp = 1,
    }
    MTLPP_AVAILABLE(10_11, 9_0);

    enum class TriangleFillMode
    {
        Fill  = 0,
        Lines = 1,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    struct DrawPrimitivesIndirectArguments
    {
        uint32_t VertexCount;
        uint32_t InstanceCount;
        uint32_t VertexStart;
        uint32_t BaseInstance;
    };

    struct DrawIndexedPrimitivesIndirectArguments
    {
        uint32_t IndexCount;
        uint32_t InstanceCount;
        uint32_t IndexStart;
        int32_t  BaseVertex;
        uint32_t BaseInstance;
    };

    struct DrawPatchIndirectArguments
    {
        uint32_t PatchCount;
        uint32_t InstanceCount;
        uint32_t PatchStart;
        uint32_t BaseInstance;
    };

    struct QuadTessellationFactorsHalf
    {
        uint16_t EdgeTessellationFactor[4];
        uint16_t InsideTessellationFactor[2];
    };

    struct riangleTessellationFactorsHalf
    {
        uint16_t EdgeTessellationFactor[3];
        uint16_t InsideTessellationFactor;
    };

    enum class RenderStages
    {
        Vertex   = (1 << 0),
        Fragment = (1 << 1),
    }
    MTLPP_AVAILABLE_IOS(10_0);


    class RenderCommandEncoder : public CommandEncoder
    {
    public:
        RenderCommandEncoder() { }
        RenderCommandEncoder(const ns::Handle& handle) : CommandEncoder(handle) { }

        void SetRenderPipelineState(const RenderPipelineState& pipelineState);
        void SetVertexData(const void* bytes, uint32_t length, uint32_t index) MTLPP_AVAILABLE(10_11, 8_3);
        void SetVertexBuffer(const Buffer& buffer, uint32_t offset, uint32_t index);
        void SetVertexBufferOffset(uint32_t offset, uint32_t index) MTLPP_AVAILABLE(10_11, 8_3);
        void SetVertexBuffers(const Buffer* buffers, const uint32_t* offsets, const ns::Range& range);
        void SetVertexTexture(const Texture& texture, uint32_t index);
        void SetVertexTextures(const Texture* textures, const ns::Range& range);
        void SetVertexSamplerState(const SamplerState& sampler, uint32_t index);
        void SetVertexSamplerStates(const SamplerState* samplers, const ns::Range& range);
        void SetVertexSamplerState(const SamplerState& sampler, float lodMinClamp, float lodMaxClamp, uint32_t index);
        void SetVertexSamplerStates(const SamplerState* samplers, const float* lodMinClamps, const float* lodMaxClamps, const ns::Range& range);
        void SetViewport(const Viewport& viewport);
        void SetFrontFacingWinding(Winding frontFacingWinding);
        void SetCullMode(CullMode cullMode);
        void SetDepthClipMode(DepthClipMode depthClipMode) MTLPP_AVAILABLE(10_11, NA);
        void SetDepthBias(float depthBias, float slopeScale, float clamp);
        void SetScissorRect(const ScissorRect& rect);
        void SetTriangleFillMode(TriangleFillMode fillMode);
        void SetFragmentData(const void* bytes, uint32_t length, uint32_t index);
        void SetFragmentBuffer(const Buffer& buffer, uint32_t offset, uint32_t index);
        void SetFragmentBufferOffset(uint32_t offset, uint32_t index) MTLPP_AVAILABLE(10_11, 8_3);
        void SetFragmentBuffers(const Buffer* buffers, const uint32_t* offsets, const ns::Range& range);
        void SetFragmentTexture(const Texture& texture, uint32_t index);
        void SetFragmentTextures(const Texture* textures, const ns::Range& range);
        void SetFragmentSamplerState(const SamplerState& sampler, uint32_t index);
        void SetFragmentSamplerStates(const SamplerState* samplers, const ns::Range& range);
        void SetFragmentSamplerState(const SamplerState& sampler, float lodMinClamp, float lodMaxClamp, uint32_t index);
        void SetFragmentSamplerStates(const SamplerState* samplers, const float* lodMinClamps, const float* lodMaxClamps, const ns::Range& range);
        void SetBlendColor(float red, float green, float blue, float alpha);
        void SetDepthStencilState(const DepthStencilState& depthStencilState);
        void SetStencilReferenceValue(uint32_t referenceValue);
        void SetStencilReferenceValue(uint32_t frontReferenceValue, uint32_t backReferenceValue);
        void SetVisibilityResultMode(VisibilityResultMode mode, uint32_t offset);
        void SetColorStoreAction(StoreAction storeAction, uint32_t colorAttachmentIndex) MTLPP_AVAILABLE(10_12, 10_0);
        void SetDepthStoreAction(StoreAction storeAction) MTLPP_AVAILABLE(10_12, 10_0);
        void SetStencilStoreAction(StoreAction storeAction) MTLPP_AVAILABLE(10_12, 10_0);
        void Draw(PrimitiveType primitiveType, uint32_t vertexStart, uint32_t vertexCount);
        void Draw(PrimitiveType primitiveType, uint32_t vertexStart, uint32_t vertexCount, uint32_t instanceCount) MTLPP_AVAILABLE(10_11, 9_0);
        void Draw(PrimitiveType primitiveType, uint32_t vertexStart, uint32_t vertexCount, uint32_t instanceCount, uint32_t baseInstance) MTLPP_AVAILABLE(10_11, 9_0);
        void Draw(PrimitiveType primitiveType, Buffer indirectBuffer, uint32_t indirectBufferOffset);
        void DrawIndexed(PrimitiveType primitiveType, uint32_t indexCount, IndexType indexType, const Buffer& indexBuffer, uint32_t indexBufferOffset);
        void DrawIndexed(PrimitiveType primitiveType, uint32_t indexCount, IndexType indexType, const Buffer& indexBuffer, uint32_t indexBufferOffset, uint32_t instanceCount) MTLPP_AVAILABLE(10_11, 9_0);
        void DrawIndexed(PrimitiveType primitiveType, uint32_t indexCount, IndexType indexType, const Buffer& indexBuffer, uint32_t indexBufferOffset, uint32_t instanceCount, uint32_t baseVertex, uint32_t baseInstance) MTLPP_AVAILABLE(10_11, 9_0);
        void DrawIndexed(PrimitiveType primitiveType, IndexType indexType, const Buffer& indexBuffer, uint32_t indexBufferOffset, const Buffer& indirectBuffer, uint32_t indirectBufferOffset);
        void TextureBarrier() MTLPP_AVAILABLE_MAC(10_11);
        void UpdateFence(const Fence& fence, RenderStages afterStages) MTLPP_AVAILABLE_IOS(10_0);
        void WaitForFence(const Fence& fence, RenderStages beforeStages) MTLPP_AVAILABLE_IOS(10_0);
        void SetTessellationFactorBuffer(const Buffer& buffer, uint32_t offset, uint32_t instanceStride) MTLPP_AVAILABLE(10_12, 10_0);
        void SetTessellationFactorScale(float scale) MTLPP_AVAILABLE(10_12, 10_0);
        void DrawPatches(uint32_t numberOfPatchControlPoints, uint32_t patchStart, uint32_t patchCount, const Buffer& patchIndexBuffer, uint32_t patchIndexBufferOffset, uint32_t instanceCount, uint32_t baseInstance) MTLPP_AVAILABLE(10_12, 10_0);
        void DrawPatches(uint32_t numberOfPatchControlPoints, const Buffer& patchIndexBuffer, uint32_t patchIndexBufferOffset, const Buffer& indirectBuffer, uint32_t indirectBufferOffset) MTLPP_AVAILABLE(10_12, NA);
        void DrawIndexedPatches(uint32_t numberOfPatchControlPoints, uint32_t patchStart, uint32_t patchCount, const Buffer& patchIndexBuffer, uint32_t patchIndexBufferOffset, const Buffer& controlPointIndexBuffer, uint32_t controlPointIndexBufferOffset, uint32_t instanceCount, uint32_t baseInstance) MTLPP_AVAILABLE(10_12, 10_0);
        void DrawIndexedPatches(uint32_t numberOfPatchControlPoints, const Buffer& patchIndexBuffer, uint32_t patchIndexBufferOffset, const Buffer& controlPointIndexBuffer, uint32_t controlPointIndexBufferOffset, const Buffer& indirectBuffer, uint32_t indirectBufferOffset) MTLPP_AVAILABLE(10_12, NA);
    }
    MTLPP_AVAILABLE(10_11, 8_0);
}


//////////////////////////////////////
// FILE: function_constant_values.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"
// #include "ns.hpp"
// #include "argument.hpp"

namespace mtlpp
{
    class FunctionConstantValues : public ns::Object
    {
    public:
        FunctionConstantValues();
        FunctionConstantValues(const ns::Handle& handle) : ns::Object(handle) { }

        void SetConstantValue(const void* value, DataType type, uint32_t index);
        void SetConstantValue(const void* value, DataType type, const ns::String& name);
        void SetConstantValues(const void* value, DataType type, const ns::Range& range);

        void Reset();
    }
    MTLPP_AVAILABLE(10_12, 10_0);
}

//////////////////////////////////////
// FILE: render_pipeline.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"
// #include "device.hpp"
// #include "render_command_encoder.hpp"
// #include "render_pass.hpp"
// #include "pixel_format.hpp"
// #include "argument.hpp"
// #include "function_constant_values.hpp"

namespace mtlpp
{
    class VertexDescriptor;

    enum class BlendFactor
    {
        Zero                                                = 0,
        One                                                 = 1,
        SourceColor                                         = 2,
        OneMinusSourceColor                                 = 3,
        SourceAlpha                                         = 4,
        OneMinusSourceAlpha                                 = 5,
        DestinationColor                                    = 6,
        OneMinusDestinationColor                            = 7,
        DestinationAlpha                                    = 8,
        OneMinusDestinationAlpha                            = 9,
        SourceAlphaSaturated                                = 10,
        BlendColor                                          = 11,
        OneMinusBlendColor                                  = 12,
        BlendAlpha                                          = 13,
        OneMinusBlendAlpha                                  = 14,
        Source1Color             MTLPP_AVAILABLE_MAC(10_12) = 15,
        OneMinusSource1Color     MTLPP_AVAILABLE_MAC(10_12) = 16,
        Source1Alpha             MTLPP_AVAILABLE_MAC(10_12) = 17,
        OneMinusSource1Alpha     MTLPP_AVAILABLE_MAC(10_12) = 18,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class BlendOperation
    {
        Add             = 0,
        Subtract        = 1,
        ReverseSubtract = 2,
        Min             = 3,
        Max             = 4,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class ColorWriteMask
    {
        None  = 0,
        Red   = 0x1 << 3,
        Green = 0x1 << 2,
        Blue  = 0x1 << 1,
        Alpha = 0x1 << 0,
        All   = 0xf
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class PrimitiveTopologyClass
    {
        Unspecified = 0,
        Point       = 1,
        Line        = 2,
        Triangle    = 3,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class TessellationPartitionMode
    {
        ModePow2           = 0,
        ModeInteger        = 1,
        ModeFractionalOdd  = 2,
        ModeFractionalEven = 3,
    }
    MTLPP_AVAILABLE(10_12, 10_0);

    enum class TessellationFactorStepFunction
    {
        Constant               = 0,
        PerPatch               = 1,
        PerInstance            = 2,
        PerPatchAndPerInstance = 3,
    }
    MTLPP_AVAILABLE(10_12, 10_0);

    enum class TessellationFactorFormat
    {
        Half = 0,
    }
    MTLPP_AVAILABLE(10_12, 10_0);

    enum class TessellationControlPointIndexType
    {
        None   = 0,
        UInt16 = 1,
        UInt32 = 2,
    }
    MTLPP_AVAILABLE(10_12, 10_0);

    class RenderPipelineColorAttachmentDescriptor : public ns::Object
    {
    public:
        RenderPipelineColorAttachmentDescriptor();
        RenderPipelineColorAttachmentDescriptor(const ns::Handle& handle) : ns::Object(handle) { }

        PixelFormat     GetPixelFormat() const;
        bool            IsBlendingEnabled() const;
        BlendFactor     GetSourceRgbBlendFactor() const;
        BlendFactor     GetDestinationRgbBlendFactor() const;
        BlendOperation  GetRgbBlendOperation() const;
        BlendFactor     GetSourceAlphaBlendFactor() const;
        BlendFactor     GetDestinationAlphaBlendFactor() const;
        BlendOperation  GetAlphaBlendOperation() const;
        ColorWriteMask  GetWriteMask() const;

        void SetPixelFormat(PixelFormat pixelFormat);
        void SetBlendingEnabled(bool blendingEnabled);
        void SetSourceRgbBlendFactor(BlendFactor sourceRgbBlendFactor);
        void SetDestinationRgbBlendFactor(BlendFactor destinationRgbBlendFactor);
        void SetRgbBlendOperation(BlendOperation rgbBlendOperation);
        void SetSourceAlphaBlendFactor(BlendFactor sourceAlphaBlendFactor);
        void SetDestinationAlphaBlendFactor(BlendFactor destinationAlphaBlendFactor);
        void SetAlphaBlendOperation(BlendOperation alphaBlendOperation);
        void SetWriteMask(ColorWriteMask writeMask);
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class RenderPipelineReflection : public ns::Object
    {
    public:
        RenderPipelineReflection();
        RenderPipelineReflection(const ns::Handle& handle) : ns::Object(handle) { }

        const ns::Array<Argument> GetVertexArguments() const;
        const ns::Array<Argument> GetFragmentArguments() const;
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class RenderPipelineDescriptor : public ns::Object
    {
    public:
        RenderPipelineDescriptor();
        RenderPipelineDescriptor(const ns::Handle& handle) : ns::Object(handle) { }

        ns::String                                         GetLabel() const;
        Function                                           GetVertexFunction() const;
        Function                                           GetFragmentFunction() const;
        VertexDescriptor                                   GetVertexDescriptor() const;
        uint32_t                                           GetSampleCount() const;
        bool                                               IsAlphaToCoverageEnabled() const;
        bool                                               IsAlphaToOneEnabled() const;
        bool                                               IsRasterizationEnabled() const;
        ns::Array<RenderPipelineColorAttachmentDescriptor> GetColorAttachments() const;
        PixelFormat                                        GetDepthAttachmentPixelFormat() const;
        PixelFormat                                        GetStencilAttachmentPixelFormat() const;
        PrimitiveTopologyClass                             GetInputPrimitiveTopology() const MTLPP_AVAILABLE_MAC(10_11);
        TessellationPartitionMode                          GetTessellationPartitionMode() const MTLPP_AVAILABLE(10_12, 10_0);
        uint32_t                                           GetMaxTessellationFactor() const MTLPP_AVAILABLE(10_12, 10_0);
        bool                                               IsTessellationFactorScaleEnabled() const MTLPP_AVAILABLE(10_12, 10_0);
        TessellationFactorFormat                           GetTessellationFactorFormat() const MTLPP_AVAILABLE(10_12, 10_0);
        TessellationControlPointIndexType                  GetTessellationControlPointIndexType() const MTLPP_AVAILABLE(10_12, 10_0);
        TessellationFactorStepFunction                     GetTessellationFactorStepFunction() const MTLPP_AVAILABLE(10_12, 10_0);
        Winding                                            GetTessellationOutputWindingOrder() const MTLPP_AVAILABLE(10_12, 10_0);


        void SetLabel(const ns::String& label);
        void SetVertexFunction(const Function& vertexFunction);
        void SetFragmentFunction(const Function& fragmentFunction);
        void SetVertexDescriptor(const VertexDescriptor& vertexDescriptor);
        void SetSampleCount(uint32_t sampleCount);
        void SetAlphaToCoverageEnabled(bool alphaToCoverageEnabled);
        void SetAlphaToOneEnabled(bool alphaToOneEnabled);
        void SetRasterizationEnabled(bool rasterizationEnabled);
        void SetDepthAttachmentPixelFormat(PixelFormat depthAttachmentPixelFormat);
        void SetStencilAttachmentPixelFormat(PixelFormat stencilAttachmentPixelFormat);
        void SetInputPrimitiveTopology(PrimitiveTopologyClass inputPrimitiveTopology) MTLPP_AVAILABLE_MAC(10_11);
        void SetTessellationPartitionMode(TessellationPartitionMode tessellationPartitionMode) MTLPP_AVAILABLE(10_12, 10_0);
        void SetMaxTessellationFactor(uint32_t maxTessellationFactor) MTLPP_AVAILABLE(10_12, 10_0);
        void SetTessellationFactorScaleEnabled(bool tessellationFactorScaleEnabled) MTLPP_AVAILABLE(10_12, 10_0);
        void SetTessellationFactorFormat(TessellationFactorFormat tessellationFactorFormat) MTLPP_AVAILABLE(10_12, 10_0);
        void SetTessellationControlPointIndexType(TessellationControlPointIndexType tessellationControlPointIndexType) MTLPP_AVAILABLE(10_12, 10_0);
        void SetTessellationFactorStepFunction(TessellationFactorStepFunction tessellationFactorStepFunction) MTLPP_AVAILABLE(10_12, 10_0);
        void SetTessellationOutputWindingOrder(Winding tessellationOutputWindingOrder) MTLPP_AVAILABLE(10_12, 10_0);

        void Reset();
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class RenderPipelineState : public ns::Object
    {
    public:
        RenderPipelineState() { }
        RenderPipelineState(const ns::Handle& handle) : ns::Object(handle) { }

        ns::String GetLabel() const;
        Device     GetDevice() const;
    }
    MTLPP_AVAILABLE(10_11, 8_0);
}

//////////////////////////////////////
// FILE: vertex_descriptor.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"
// #include "ns.hpp"

namespace mtlpp
{
    enum class VertexFormat
    {
        Invalid               = 0,

        UChar2                = 1,
        UChar3                = 2,
        UChar4                = 3,

        Char2                 = 4,
        Char3                 = 5,
        Char4                 = 6,

        UChar2Normalized      = 7,
        UChar3Normalized      = 8,
        UChar4Normalized      = 9,

        Char2Normalized       = 10,
        Char3Normalized       = 11,
        Char4Normalized       = 12,

        UShort2               = 13,
        UShort3               = 14,
        UShort4               = 15,

        Short2                = 16,
        Short3                = 17,
        Short4                = 18,

        UShort2Normalized     = 19,
        UShort3Normalized     = 20,
        UShort4Normalized     = 21,

        Short2Normalized      = 22,
        Short3Normalized      = 23,
        Short4Normalized      = 24,

        Half2                 = 25,
        Half3                 = 26,
        Half4                 = 27,

        Float                 = 28,
        Float2                = 29,
        Float3                = 30,
        Float4                = 31,

        Int                   = 32,
        Int2                  = 33,
        Int3                  = 34,
        Int4                  = 35,

        UInt                  = 36,
        UInt2                 = 37,
        UInt3                 = 38,
        UInt4                 = 39,

        Int1010102Normalized  = 40,
        UInt1010102Normalized = 41,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class VertexStepFunction
    {
        Constant                                          = 0,
        PerVertex                                         = 1,
        PerInstance                                       = 2,
        PerPatch             MTLPP_AVAILABLE(10_12, 10_0) = 3,
        PerPatchControlPoint MTLPP_AVAILABLE(10_12, 10_0) = 4,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class VertexBufferLayoutDescriptor : public ns::Object
    {
    public:
        VertexBufferLayoutDescriptor();
        VertexBufferLayoutDescriptor(const ns::Handle& handle) : ns::Object(handle) { }

        uint32_t           GetStride() const;
        VertexStepFunction GetStepFunction() const;
        uint32_t           GetStepRate() const;

        void SetStride(uint32_t stride);
        void SetStepFunction(VertexStepFunction stepFunction);
        void SetStepRate(uint32_t stepRate);
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class VertexAttributeDescriptor : public ns::Object
    {
    public:
        VertexAttributeDescriptor();
        VertexAttributeDescriptor(const ns::Handle& handle) : ns::Object(handle) { }

        VertexFormat GetFormat() const;
        uint32_t     GetOffset() const;
        uint32_t     GetBufferIndex() const;

        void SetFormat(VertexFormat format);
        void SetOffset(uint32_t offset);
        void SetBufferIndex(uint32_t bufferIndex);
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class VertexDescriptor : public ns::Object
    {
    public:
        VertexDescriptor();
        VertexDescriptor(const ns::Handle& handle) : ns::Object(handle) { }

        ns::Array<VertexBufferLayoutDescriptor> GetLayouts() const;
        ns::Array<VertexAttributeDescriptor>    GetAttributes() const;

        void Reset();
    }
    MTLPP_AVAILABLE(10_11, 8_0);
}

//////////////////////////////////////
// FILE: parallel_render_command_encoder.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"
// #include "ns.hpp"
// #include "render_pass.hpp"
// #include "command_encoder.hpp"

namespace mtlpp
{
    class RenderCommandEncoder;

    class ParallelRenderCommandEncoder : public ns::Object
    {
    public:
        ParallelRenderCommandEncoder() { }
        ParallelRenderCommandEncoder(const ns::Handle& handle) : ns::Object(handle) { }

        RenderCommandEncoder GetRenderCommandEncoder();

        void SetColorStoreAction(StoreAction storeAction, uint32_t colorAttachmentIndex) MTLPP_AVAILABLE(10_12, 10_0);
        void SetDepthStoreAction(StoreAction storeAction) MTLPP_AVAILABLE(10_12, 10_0);
        void SetStencilStoreAction(StoreAction storeAction) MTLPP_AVAILABLE(10_12, 10_0);
    }
    MTLPP_AVAILABLE(10_11, 8_0);
}


//////////////////////////////////////
// FILE: sampler.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"
// #include "depth_stencil.hpp"
// #include "device.hpp"

namespace mtlpp
{
    enum class SamplerMinMagFilter
    {
        Nearest = 0,
        Linear  = 1,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class SamplerMipFilter
    {
        NotMipmapped = 0,
        Nearest      = 1,
        Linear       = 2,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class SamplerAddressMode
    {
        ClampToEdge                                   = 0,
        MirrorClampToEdge  MTLPP_AVAILABLE_MAC(10_11) = 1,
        Repeat                                        = 2,
        MirrorRepeat                                  = 3,
        ClampToZero                                   = 4,
        ClampToBorderColor MTLPP_AVAILABLE_MAC(10_12) = 5,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class SamplerBorderColor
    {
        TransparentBlack = 0,  // {0,0,0,0}
        OpaqueBlack = 1,       // {0,0,0,1}
        OpaqueWhite = 2,       // {1,1,1,1}
    };

    class SamplerDescriptor : public ns::Object
    {
    public:
        SamplerDescriptor();
        SamplerDescriptor(const ns::Handle& handle) : ns::Object(handle) { }

        SamplerMinMagFilter GetMinFilter() const;
        SamplerMinMagFilter GetMagFilter() const;
        SamplerMipFilter    GetMipFilter() const;
        uint32_t            GetMaxAnisotropy() const;
        SamplerAddressMode  GetSAddressMode() const;
        SamplerAddressMode  GetTAddressMode() const;
        SamplerAddressMode  GetRAddressMode() const;
        SamplerBorderColor  GetBorderColor() const MTLPP_AVAILABLE_MAC(10_12);
        bool                IsNormalizedCoordinates() const;
        float               GetLodMinClamp() const;
        float               GetLodMaxClamp() const;
        CompareFunction     GetCompareFunction() const MTLPP_AVAILABLE(10_11, 9_0);
        ns::String          GetLabel() const;

        void SetMinFilter(SamplerMinMagFilter minFilter);
        void SetMagFilter(SamplerMinMagFilter magFilter);
        void SetMipFilter(SamplerMipFilter mipFilter);
        void SetMaxAnisotropy(uint32_t maxAnisotropy);
        void SetSAddressMode(SamplerAddressMode sAddressMode);
        void SetTAddressMode(SamplerAddressMode tAddressMode);
        void SetRAddressMode(SamplerAddressMode rAddressMode);
        void SetBorderColor(SamplerBorderColor borderColor) MTLPP_AVAILABLE_MAC(10_12);
        void SetNormalizedCoordinates(bool normalizedCoordinates);
        void SetLodMinClamp(float lodMinClamp);
        void SetLodMaxClamp(float lodMaxClamp);
        void SetCompareFunction(CompareFunction compareFunction) MTLPP_AVAILABLE(10_11, 9_0);
        void SetLabel(const ns::String& label);
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class SamplerState : public ns::Object
    {
    public:
        SamplerState() { }
        SamplerState(const ns::Handle& handle) : ns::Object(handle) { }

        ns::String GetLabel() const;
        Device     GetDevice() const;
    }
    MTLPP_AVAILABLE(10_11, 8_0);
}


//////////////////////////////////////
// FILE: heap.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"
// #include "ns.hpp"
// #include "device.hpp"
// #include "resource.hpp"
// #include "buffer.hpp"
// #include "texture.hpp"
// #include "types.hpp"

namespace mtlpp
{
    class HeapDescriptor : public ns::Object
    {
    public:
        HeapDescriptor(const ns::Handle& handle) : ns::Object(handle) { }

        uint32_t     GetSize() const;
        StorageMode  GetStorageMode() const;
        CpuCacheMode GetCpuCacheMode() const;

        void SetSize(uint32_t size) const;
        void SetStorageMode(StorageMode storageMode) const;
        void SetCpuCacheMode(CpuCacheMode cpuCacheMode) const;
    }
    MTLPP_AVAILABLE(NA, 10_0);

    class Heap : public ns::Object
    {
    public:
        Heap(const ns::Handle& handle) : ns::Object(handle) { }

        ns::String   GetLabel() const;
        Device       GetDevice() const;
        StorageMode  GetStorageMode() const;
        CpuCacheMode GetCpuCacheMode() const;
        uint32_t     GetSize() const;
        uint32_t     GetUsedSize() const;

        void SetLabel(const ns::String& label);

        uint32_t MaxAvailableSizeWithAlignment(uint32_t alignment);
        Buffer NewBuffer(uint32_t length, ResourceOptions options);
        Texture NewTexture(const TextureDescriptor& desc);
        PurgeableState SetPurgeableState(PurgeableState state);
    }
    MTLPP_AVAILABLE(NA, 10_0);
}

//////////////////////////////////////
// FILE: mtlpp.hpp
//////////////////////////////////////
/*
 * Copyright 2016 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

// #pragma once

// #include "defines.hpp"
// #include "blit_command_encoder.hpp"
// #include "buffer.hpp"
// #include "command_buffer.hpp"
// #include "compute_command_encoder.hpp"
// #include "command_queue.hpp"
// #include "device.hpp"
// #include "depth_stencil.hpp"
// #include "drawable.hpp"
// #include "render_pass.hpp"
// #include "compute_pipeline.hpp"
// #include "library.hpp"
// #include "pixel_format.hpp"
// #include "render_pipeline.hpp"
// #include "vertex_descriptor.hpp"
// #include "parallel_render_command_encoder.hpp"
// #include "render_command_encoder.hpp"
// #include "sampler.hpp"
// #include "texture.hpp"
// #include "heap.hpp"

