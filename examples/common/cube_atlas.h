/*
 * Copyright 2013 Jeremie Roy. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __CUBE_ATLAS_H__
#define __CUBE_ATLAS_H__

/// Inspired from texture-atlas from freetype-gl (http://code.google.com/p/freetype-gl/)
/// by Nicolas Rougier (Nicolas.Rougier@inria.fr)
/// The actual implementation is based on the article by Jukka Jylänki : "A
/// Thousand Ways to Pack the Bin - A Practical Approach to Two-Dimensional
/// Rectangle Bin Packing", February 27, 2010.
/// More precisely, this is an implementation of the Skyline Bottom-Left
/// algorithm based on C++ sources provided by Jukka Jylänki at:
/// http://clb.demon.fi/files/RectangleBinPack/

#include <bgfx.h>

struct AtlasRegion
{
	enum Type
	{
		TYPE_GRAY = 1, // 1 component
		TYPE_BGRA8 = 4  // 4 components
	};

	uint16_t m_x, m_y;
	uint16_t m_width, m_height;
	uint32_t m_mask; //encode the region type, the face index and the component index in case of a gray region

	Type getType() const
	{
		return (Type) ( (m_mask >> 0) & 0x0000000F);
	}
	uint32_t getFaceIndex() const
	{
		return (m_mask >> 4) & 0x0000000F;
	}
	uint32_t getComponentIndex() const
	{
		return (m_mask >> 8) & 0x0000000F;
	}
	void setMask(Type _type, uint32_t _faceIndex, uint32_t _componentIndex)
	{
		m_mask = (_componentIndex << 8) + (_faceIndex << 4) + (uint32_t)_type;
	}
};

class Atlas
{
public:
	/// create an empty dynamic atlas (region can be updated and added)
	/// @param textureSize an atlas creates a texture cube of 6 faces with size equal to (textureSize*textureSize * sizeof(RGBA))
	/// @param maxRegionCount maximum number of region allowed in the atlas
	Atlas(uint16_t _textureSize, uint16_t _maxRegionsCount = 4096);

	/// initialize a static atlas with serialized data	(region can be updated but not added)
	/// @param textureSize an atlas creates a texture cube of 6 faces with size equal to (textureSize*textureSize * sizeof(RGBA))
	/// @param textureBuffer buffer of size 6*textureSize*textureSize*sizeof(uint32_t) (will be copied)
	/// @param regionCount number of region in the Atlas
	/// @param regionBuffer buffer containing the region (will be copied)
	/// @param maxRegionCount maximum number of region allowed in the atlas
	Atlas(uint16_t _textureSize, const uint8_t* _textureBuffer, uint16_t _regionCount, const uint8_t* _regionBuffer, uint16_t _maxRegionsCount = 4096);
	~Atlas();

	/// add a region to the atlas, and copy the content of mem to the underlying texture
	uint16_t addRegion(uint16_t _width, uint16_t _height, const uint8_t* _bitmapBuffer, AtlasRegion::Type _type = AtlasRegion::TYPE_BGRA8, uint16_t outline = 0);

	/// update a preallocated region
	void updateRegion(const AtlasRegion& _region, const uint8_t* _bitmapBuffer);

	/// Pack the UV coordinates of the four corners of a region to a vertex buffer using the supplied vertex format.
	/// v0 -- v3
	/// |     |     encoded in that order:  v0,v1,v2,v3
	/// v1 -- v2
	/// @remark the UV are four signed short normalized components.
	/// @remark the x,y,z components encode cube uv coordinates. The w component encode the color channel if any.
	/// @param handle handle to the region we are interested in
	/// @param vertexBuffer address of the first vertex we want to update. Must be valid up to vertexBuffer + offset + 3*stride + 4*sizeof(int16_t), which means the buffer must contains at least 4 vertex includind the first.
	/// @param offset byte offset to the first uv coordinate of the vertex in the buffer
	/// @param stride stride between tho UV coordinates, usually size of a Vertex.
	void packUV(uint16_t _regionHandle, uint8_t* _vertexBuffer, uint32_t _offset, uint32_t _stride);
	void packUV(const AtlasRegion& _region, uint8_t* _vertexBuffer, uint32_t _offset, uint32_t _stride);

	/// Same as packUV but pack a whole face of the atlas cube, mostly used for debugging and visualizing atlas
	void packFaceLayerUV(uint32_t _idx, uint8_t* _vertexBuffer, uint32_t _offset, uint32_t _stride);

	/// Pack the vertex index of the region as 2 quad into an index buffer
	void packIndex(uint16_t* _indexBuffer, uint32_t _startIndex, uint32_t _startVertex)
	{
		_indexBuffer[_startIndex + 0] = _startVertex + 0;
		_indexBuffer[_startIndex + 1] = _startVertex + 1;
		_indexBuffer[_startIndex + 2] = _startVertex + 2;
		_indexBuffer[_startIndex + 3] = _startVertex + 0;
		_indexBuffer[_startIndex + 4] = _startVertex + 2;
		_indexBuffer[_startIndex + 5] = _startVertex + 3;
	}

	/// return the TextureHandle (cube) of the atlas
	bgfx::TextureHandle getTextureHandle() const
	{
		return m_textureHandle;
	}

	//retrieve a region info
	const AtlasRegion& getRegion(uint16_t _handle) const
	{
		return m_regions[_handle];
	}

	/// retrieve the size of side of a texture in pixels
	uint16_t getTextureSize()
	{
		return m_textureSize;
	}

	/// retrieve the usage ratio of the atlas
	//float getUsageRatio() const { return 0.0f; }

	/// retrieve the numbers of region in the atlas
	uint16_t getRegionCount() const
	{
		return m_regionCount;
	}

	/// retrieve a pointer to the region buffer (in order to serialize it)
	const AtlasRegion* getRegionBuffer() const
	{
		return m_regions;
	}

	/// retrieve the byte size of the texture
	uint32_t getTextureBufferSize() const
	{
		return 6 * m_textureSize * m_textureSize * 4;
	}

	/// retrieve the mirrored texture buffer (to serialize it)
	const uint8_t* getTextureBuffer() const
	{
		return m_textureBuffer;
	}

private:
	void writeUV(uint8_t* _vertexBuffer, int16_t _x, int16_t _y, int16_t _z, int16_t _w)
	{
		( (uint16_t*) _vertexBuffer)[0] = _x;
		( (uint16_t*) _vertexBuffer)[1] = _y;
		( (uint16_t*) _vertexBuffer)[2] = _z;
		( (uint16_t*) _vertexBuffer)[3] = _w;
	}

	struct PackedLayer;
	PackedLayer* m_layers;

	uint32_t m_usedLayers;
	uint32_t m_usedFaces;

	bgfx::TextureHandle m_textureHandle;
	uint16_t m_textureSize;

	uint16_t m_regionCount;
	uint16_t m_maxRegionCount;

	AtlasRegion* m_regions;
	uint8_t* m_textureBuffer;
};

#endif // __CUBE_ATLAS_H__
