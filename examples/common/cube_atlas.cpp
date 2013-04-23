/* Copyright 2013 Jeremie Roy. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
*/
#pragma once
#include <bgfx.h> 
#include <assert.h>
#include <vector>
#include "cube_atlas.h"

//********** Rectangle packer implementation ************
class RectanglePacker
{ 
public:
	RectanglePacker();
	RectanglePacker(uint32_t width, uint32_t height);
	
	/// non constructor initialization
	void init(uint32_t width, uint32_t height);
	/// find a suitable position for the given rectangle 
	/// @return true if the rectangle can be added, false otherwise	
	bool addRectangle(uint16_t width, uint16_t height, uint16_t& outX, uint16_t& outY );
	/// return the used surface in squared unit
	uint32_t getUsedSurface() { return m_usedSpace; }
	/// return the total available surface in squared unit
	uint32_t getTotalSurface() { return m_width*m_height; }
	/// return the usage ratio of the available surface [0:1]
	float getUsageRatio();
	/// reset to initial state
    void clear();

private:
	int32_t fit(uint32_t skylineNodeIndex, uint16_t width, uint16_t height);
	/// Merges all skyline nodes that are at the same level.
	void merge();

	struct Node
	{
		Node(int16_t _x, int16_t _y, int16_t _width):x(_x), y(_y), width(_width) {} 
    
		/// The starting x-coordinate (leftmost).
		int16_t x;
		/// The y-coordinate of the skyline level line.
		int16_t y;
		/// The line width. The ending coordinate (inclusive) will be x+width-1.
		int32_t width; //32bit to avoid padding
	};

	 /// Width (in pixels) of the underlying texture
    uint32_t m_width;
    /// Height (in pixels) of the underlying texture
    uint32_t m_height;
    /// Surface used in squared pixel
    uint32_t m_usedSpace;
	/// node of the skyline algorithm
    std::vector<Node> m_skyline;
};

RectanglePacker::RectanglePacker(): m_width(0), m_height(0), m_usedSpace(0)
{	
}

RectanglePacker::RectanglePacker(uint32_t width, uint32_t height):m_width(width), m_height(height), m_usedSpace(0)
{   
    // We want a one pixel border around the whole atlas to avoid any artefact when
    // sampling texture    
    m_skyline.push_back(Node(1,1, width-2));
}

void RectanglePacker::init(uint32_t width, uint32_t height)
{
	assert(width > 2);
	assert(height > 2);
	m_width = width;
	m_height = height;
	m_usedSpace = 0;

	m_skyline.clear();
	// We want a one pixel border around the whole atlas to avoid any artifact when
    // sampling texture    
    m_skyline.push_back(Node(1,1, width-2));
}

bool RectanglePacker::addRectangle(uint16_t width, uint16_t height, uint16_t& outX, uint16_t& outY)
{
	int y, best_height, best_index;
    int32_t best_width;
    Node* node;
    Node* prev;
    outX = 0;
	outY = 0;
	
	size_t i;

    best_height = INT_MAX;
    best_index  = -1;
    best_width = INT_MAX;
	for( i = 0; i < m_skyline.size(); ++i )
	{
        y = fit( i, width, height );
		if( y >= 0 )
		{
            node = &m_skyline[i];
			if( ( (y + height) < best_height ) ||
                ( ((y + height) == best_height) && (node->width < best_width)) )
			{
				best_height = y + height;
				best_index = i;
				best_width = node->width;
				outX = node->x;
				outY = y;
			}
        }
    }

    if( best_index == -1 )
    {
		return false;
    }
    
    Node newNode(outX,outY + height, width);
    m_skyline.insert(m_skyline.begin() + best_index, newNode);

    for(i = best_index+1; i < m_skyline.size(); ++i)
    {
        node = &m_skyline[i];
        prev = &m_skyline[i-1];
        if (node->x < (prev->x + prev->width) )
        {
            int shrink = prev->x + prev->width - node->x;
            node->x += shrink;
            node->width -= shrink;
            if (node->width <= 0)
            {
                 m_skyline.erase(m_skyline.begin() + i);
                --i;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    merge();
    m_usedSpace += width * height;
    return true;
}
		
float RectanglePacker::getUsageRatio()
{ 
	uint32_t total = m_width*m_height;
	if(total > 0) 
		return (float) m_usedSpace / (float) total;
	else
		return 0.0f;
}

void RectanglePacker::clear()
{
	m_skyline.clear();
    m_usedSpace = 0;
    
    // We want a one pixel border around the whole atlas to avoid any artefact when
    // sampling texture
    m_skyline.push_back(Node(1,1, m_width-2));
}

int32_t RectanglePacker::fit(uint32_t skylineNodeIndex, uint16_t _width, uint16_t _height)
{
	int32_t width = _width;
    int32_t height = _height;
    
    const Node& baseNode = m_skyline[skylineNodeIndex];
    
    int32_t x = baseNode.x, y;
	int32_t width_left = width;
	int32_t i = skylineNodeIndex;

    if ( (x + width) > (int32_t)(m_width-1) )
    {
		return -1;
    }
    y = baseNode.y;
	while( width_left > 0 )
	{
        const Node& node = m_skyline[i];
        if( node.y > y )
        {
            y = node.y;
        }
		if( (y + height) > (int32_t)(m_height-1) )
        {
			return -1;
        }
        width_left -= node.width;
		++i;
	}
	return y;
}
	
void RectanglePacker::merge()
{
	Node* node;
    Node* next;
    uint32_t i;

	for( i=0; i < m_skyline.size()-1; ++i )
    {
        node = (Node *) &m_skyline[i];
        next = (Node *) &m_skyline[i+1];
		if( node->y == next->y )
		{
			node->width += next->width;
            m_skyline.erase(m_skyline.begin() + i + 1);
			--i;
		}
    }
}

//********** Cube Atlas implementation ************

struct Atlas::PackedLayer
{
	RectanglePacker packer;
	AtlasRegion faceRegion;
};

Atlas::Atlas(uint16_t textureSize, uint16_t maxRegionsCount )
{
	assert(textureSize >= 64 && textureSize <= 4096 && "suspicious texture size" );
	assert(maxRegionsCount >= 64 && maxRegionsCount <= 32000 && "suspicious regions count" );
	m_layers = new PackedLayer[24];
	for(int i=0; i<24;++i)
	{
		m_layers[i].packer.init(textureSize, textureSize);		
	}
	m_usedLayers = 0;
	m_usedFaces = 0;

	m_textureSize = textureSize;
	m_regionCount = 0;
	m_maxRegionCount = maxRegionsCount;
	m_regions = new AtlasRegion[maxRegionsCount];
	m_textureBuffer = new uint8_t[ textureSize * textureSize * 6 * 4 ];
	memset(m_textureBuffer, 0,  textureSize * textureSize * 6 * 4);
	//BGFX_TEXTURE_MIN_POINT|BGFX_TEXTURE_MAG_POINT|BGFX_TEXTURE_MIP_POINT;
	//BGFX_TEXTURE_MIN_ANISOTROPIC|BGFX_TEXTURE_MAG_ANISOTROPIC|BGFX_TEXTURE_MIP_POINT
	//BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP
	uint32_t flags = 0;// BGFX_TEXTURE_MIN_ANISOTROPIC|BGFX_TEXTURE_MAG_ANISOTROPIC|BGFX_TEXTURE_MIP_POINT;

	//Uncomment this to debug atlas
	//const bgfx::Memory* mem = bgfx::alloc(textureSize*textureSize * 6 * 4);
	//memset(mem->data, 255, mem->size);	
	const bgfx::Memory* mem = NULL;	
	m_textureHandle = bgfx::createTextureCube(6
			, textureSize
			, 1
			, bgfx::TextureFormat::BGRA8
			, flags
			,mem
			);
}

Atlas::Atlas(uint16_t textureSize, const uint8_t* textureBuffer , uint16_t regionCount, const uint8_t* regionBuffer, uint16_t maxRegionsCount)
{
	assert(regionCount <= 64 && maxRegionsCount <= 4096);
	//layers are frozen
	m_usedLayers = 24;
	m_usedFaces = 6;

	m_textureSize = textureSize;
	m_regionCount = regionCount;
	//regions are frozen
	m_maxRegionCount = regionCount;
	m_regions = new AtlasRegion[regionCount];
	m_textureBuffer = new uint8_t[getTextureBufferSize()];
	
	//BGFX_TEXTURE_MIN_POINT|BGFX_TEXTURE_MAG_POINT|BGFX_TEXTURE_MIP_POINT;
	//BGFX_TEXTURE_MIN_ANISOTROPIC|BGFX_TEXTURE_MAG_ANISOTROPIC|BGFX_TEXTURE_MIP_POINT
	//BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP
	uint32_t flags = 0;//BGFX_TEXTURE_MIN_ANISOTROPIC|BGFX_TEXTURE_MAG_ANISOTROPIC|BGFX_TEXTURE_MIP_POINT;
	memcpy(m_regions, regionBuffer, regionCount * sizeof(AtlasRegion));	
	memcpy(m_textureBuffer, textureBuffer, getTextureBufferSize());

	m_textureHandle = bgfx::createTextureCube(6
			, textureSize
			, 1
			, bgfx::TextureFormat::BGRA8
			, flags
			, bgfx::makeRef(m_textureBuffer, getTextureBufferSize())
			);
}

Atlas::~Atlas()
{
	delete[] m_layers;
	delete[] m_regions;
	delete[] m_textureBuffer;
}

uint16_t Atlas::addRegion(uint16_t width, uint16_t height, const uint8_t* bitmapBuffer,  AtlasRegion::Type type)
{
	if (m_regionCount >= m_maxRegionCount)
	{
		return UINT16_MAX;
	}
	
	uint16_t x,y;
	// We want each bitmap to be separated by at least one black pixel
	// TODO manage mipmaps
	uint32_t idx = 0;
	while(idx<m_usedLayers)
	{
		if(m_layers[idx].faceRegion.getType() == type)
		{
			if(m_layers[idx].packer.addRectangle(width+1,height+1,x,y)) break;			
		}
		idx++;
	}

	if(idx >= m_usedLayers)
	{
		//do we have still room to add layers ?
		if( (idx + type) > 24 || m_usedFaces>=6)
		{
				return UINT16_MAX;
		}		
		//create new layers
		for(int i=0; i < type;++i)
		{
			m_layers[idx+i].faceRegion.setMask(type, m_usedFaces, i);			
		}
		m_usedLayers += type;
		m_usedFaces++;


		//add it to the created layer
		if(!m_layers[idx].packer.addRectangle(width+1,height+1,x,y))
		{
			return UINT16_MAX;
		}
	}
	
	AtlasRegion& region = m_regions[m_regionCount];
	region.x = x;
	region.y = y;
	region.width = width;
	region.height = height;
	region.mask = m_layers[idx].faceRegion.mask;

	updateRegion(region, bitmapBuffer);
	return m_regionCount++;
}

void Atlas::updateRegion(const AtlasRegion& region, const uint8_t* bitmapBuffer)
{	
	const bgfx::Memory* mem = bgfx::alloc(region.width * region.height * 4);
	//BAD!
	memset(mem->data,0, mem->size);
	if(region.getType() == AtlasRegion::TYPE_BGRA8)
	{	
		const uint8_t* inLineBuffer = bitmapBuffer;
		uint8_t* outLineBuffer = m_textureBuffer + region.getFaceIndex() * (m_textureSize*m_textureSize*4) + (((region.y *m_textureSize)+region.x)*4);

		//update the cpu buffer
		for(int y = 0; y < region.height; ++y)
		{
			memcpy(outLineBuffer, inLineBuffer, region.width * 4);
			inLineBuffer += region.width*4;
			outLineBuffer += m_textureSize*4;
		}
		//update the GPU buffer
		memcpy(mem->data, bitmapBuffer, mem->size);
	}else
	{
		uint32_t layer = region.getComponentIndex();
		uint32_t face = region.getFaceIndex();
		const uint8_t* inLineBuffer = bitmapBuffer;
		uint8_t* outLineBuffer = (m_textureBuffer + region.getFaceIndex() * (m_textureSize*m_textureSize*4) + (((region.y *m_textureSize)+region.x)*4));
		
		//update the cpu buffer
		for(int y = 0; y<region.height; ++y)
		{
			for(int x = 0; x<region.width; ++x)
			{
				outLineBuffer[(x*4) + layer] = inLineBuffer[x];
			}
			//update the GPU buffer
			memcpy(mem->data + y*region.width*4, outLineBuffer, region.width*4);
			inLineBuffer += region.width;
			outLineBuffer +=  m_textureSize*4;
		}
	}
	bgfx::updateTextureCube(m_textureHandle, (uint8_t)region.getFaceIndex(), 0, region.x, region.y, region.width, region.height, mem);		
}

void Atlas::packFaceLayerUV(uint32_t idx, uint8_t* vertexBuffer, uint32_t offset, uint32_t stride )
{
	packUV(m_layers[idx].faceRegion, vertexBuffer, offset, stride);
}

void Atlas::packUV( uint16_t handle, uint8_t* vertexBuffer, uint32_t offset, uint32_t stride )
{
	const AtlasRegion& region = m_regions[handle];
	packUV(region, vertexBuffer, offset, stride);
}

void Atlas::packUV( const AtlasRegion& region, uint8_t* vertexBuffer, uint32_t offset, uint32_t stride )
{
	float texMult = 65535.0f / ((float)(m_textureSize));
	static const int16_t minVal = -32768;
	static const int16_t maxVal = 32767;
	
	int16_t x0 = (int16_t)(region.x * texMult)-32768;
	int16_t y0 = (int16_t)(region.y * texMult)-32768;
	int16_t x1 = (int16_t)((region.x + region.width)* texMult)-32768;
	int16_t y1 = (int16_t)((region.y + region.height)* texMult)-32768;
	int16_t w =  (int16_t) ((32767.0f/4.0f) * region.getComponentIndex());

	vertexBuffer+=offset;
	switch(region.getFaceIndex())
	{
	case 0: // +X
		x0= -x0; 
		x1= -x1;
		y0= -y0; 
		y1= -y1;
		writeUV(vertexBuffer, maxVal, y0, x0, w); vertexBuffer+=stride;
		writeUV(vertexBuffer, maxVal, y1, x0, w); vertexBuffer+=stride;
		writeUV(vertexBuffer, maxVal, y1, x1, w); vertexBuffer+=stride;
		writeUV(vertexBuffer, maxVal, y0, x1, w); vertexBuffer+=stride;
		break;
	case 1: // -X		
		y0= -y0; 
		y1= -y1;
		writeUV(vertexBuffer, minVal, y0, x0, w); vertexBuffer+=stride;
		writeUV(vertexBuffer, minVal, y1, x0, w); vertexBuffer+=stride;
		writeUV(vertexBuffer, minVal, y1, x1, w); vertexBuffer+=stride;
		writeUV(vertexBuffer, minVal, y0, x1, w); vertexBuffer+=stride;	
		break;
	case 2: // +Y		
		writeUV(vertexBuffer, x0, maxVal, y0, w); vertexBuffer+=stride;
		writeUV(vertexBuffer, x0, maxVal, y1, w); vertexBuffer+=stride;
		writeUV(vertexBuffer, x1, maxVal, y1, w); vertexBuffer+=stride;
		writeUV(vertexBuffer, x1, maxVal, y0, w); vertexBuffer+=stride;
		break;
	case 3: // -Y
		y0= -y0; 
		y1= -y1;
		writeUV(vertexBuffer, x0, minVal, y0, w); vertexBuffer+=stride;
		writeUV(vertexBuffer, x0, minVal, y1, w); vertexBuffer+=stride;
		writeUV(vertexBuffer, x1, minVal, y1, w); vertexBuffer+=stride;
		writeUV(vertexBuffer, x1, minVal, y0, w); vertexBuffer+=stride;
		break;
	case 4: // +Z
		y0= -y0; 
		y1= -y1;
		writeUV(vertexBuffer, x0, y0, maxVal, w); vertexBuffer+=stride;
		writeUV(vertexBuffer, x0, y1, maxVal, w); vertexBuffer+=stride;
		writeUV(vertexBuffer, x1, y1, maxVal, w); vertexBuffer+=stride;
		writeUV(vertexBuffer, x1, y0, maxVal, w); vertexBuffer+=stride;
		break;
	case 5: // -Z
		x0= -x0; 
		x1= -x1;
		y0= -y0; 
		y1= -y1;
		writeUV(vertexBuffer, x0, y0, minVal, w); vertexBuffer+=stride;
		writeUV(vertexBuffer, x0, y1, minVal, w); vertexBuffer+=stride;
		writeUV(vertexBuffer, x1, y1, minVal, w); vertexBuffer+=stride;
		writeUV(vertexBuffer, x1, y0, minVal, w); vertexBuffer+=stride;
		break;
	}
}
