/*
 * Copyright 2018 Ales Mlakar. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

 /*
  * Reference(s):
  * - Sparse Virtual Textures by Sean Barrett
  *   http://web.archive.org/web/20190103162611/http://silverspaceship.com/src/svt/
  * - Based on Virtual Texture Demo by Brad Blanchard
  *   http://web.archive.org/web/20190103162638/http://linedef.com/virtual-texture-demo.html
  * - Mars texture
  *   http://web.archive.org/web/20190103162730/http://www.celestiamotherlode.net/catalog/mars.php
  */

#include <bx/file.h>
#include <bx/sort.h>

#include "vt.h"

namespace vt
{

// Constants
static const int s_channelCount = 4;
static const int s_tileFileDataOffset = sizeof(VirtualTextureInfo);

// Page
Page::operator size_t() const
{
	return size_t((uint32_t(m_mip) << 16) | uint32_t((uint16_t(m_x) << 8) | uint16_t(m_y)));
}

// PageCount
PageCount::PageCount(Page _page, int _count)
	: m_page(_page)
	, m_count(_count)
{
}

int PageCount::compareTo(const PageCount& other) const
{
	if (other.m_page.m_mip != m_page.m_mip)
	{
		return bx::clamp<int>(other.m_page.m_mip - m_page.m_mip, -1, 1);
	}

	return bx::clamp<int>(other.m_count - m_count, -1, 1);
}

// VirtualTextureInfo
VirtualTextureInfo::VirtualTextureInfo()
	: m_virtualTextureSize(0)
	, m_tileSize(0)
	, m_borderSize(0)
{
}

int VirtualTextureInfo::GetPageSize() const
{
	return m_tileSize + 2 * m_borderSize;
}

int VirtualTextureInfo::GetPageTableSize() const
{
	return m_virtualTextureSize / m_tileSize;
}

StagingPool::StagingPool(int _width, int _height, int _count, bool _readBack)
	: m_stagingTextureIndex(0)
	, m_width(_width)
	, m_height(_height)
	, m_flags(0)
{
	m_flags = BGFX_TEXTURE_BLIT_DST | BGFX_SAMPLER_UVW_CLAMP;
	if (_readBack)
	{
		m_flags |= BGFX_TEXTURE_READ_BACK;
	}
	grow(_count);
}

StagingPool::~StagingPool()
{
	for (int i = 0; i < (int)m_stagingTextures.size(); ++i)
	{
		bgfx::destroy(m_stagingTextures[i]);
	}
}

void StagingPool::grow(int count)
{
	while ((int)m_stagingTextures.size() < count)
	{
		auto stagingTexture = bgfx::createTexture2D((uint16_t)m_width, (uint16_t)m_height, false, 1, bgfx::TextureFormat::BGRA8, m_flags);
		m_stagingTextures.push_back(stagingTexture);
	}
}

bgfx::TextureHandle StagingPool::getTexture()
{
	return m_stagingTextures[m_stagingTextureIndex];
}

void StagingPool::next()
{
	m_stagingTextureIndex = (m_stagingTextureIndex + 1) % (int)m_stagingTextures.size();
}

PageIndexer::PageIndexer(VirtualTextureInfo* _info)
	: m_info(_info)
{
	m_mipcount = int(bx::log2((float)m_info->GetPageTableSize()) + 1);

	m_sizes.resize(m_mipcount);
	for (int i = 0; i < m_mipcount; ++i)
	{
		m_sizes[i] = (m_info->m_virtualTextureSize / m_info->m_tileSize) >> i;
	}

	m_offsets.resize(m_mipcount);
	m_count = 0;

	for (int i = 0; i < m_mipcount; ++i)
	{
		m_offsets[i] = m_count;
		m_count += m_sizes[i] * m_sizes[i];
	}

	// Calculate reverse mapping
	m_reverse.resize(m_count);

	for (int i = 0; i < m_mipcount; ++i)
	{
		int size = m_sizes[i];
		for (int y = 0; y < size; ++y)
		{
			for (int x = 0; x < size; ++x)
			{
				Page page = { x, y, i };
				m_reverse[getIndexFromPage(page)] = page;
			}
		}
	}
}

int PageIndexer::getIndexFromPage(Page page)
{
	int offset = m_offsets[page.m_mip];
	int stride = m_sizes[page.m_mip];

	return offset + page.m_y * stride + page.m_x;
}

Page PageIndexer::getPageFromIndex(int index)
{
	return m_reverse[index];
}

bool PageIndexer::isValid(Page page)
{
	if (page.m_mip < 0)
	{
		return false;
	}

	if (page.m_mip >= m_mipcount)
	{
		return false;
	}

	if (page.m_x < 0)
	{
		return false;
	}

	if (page.m_x >= m_sizes[page.m_mip])
	{
		return false;
	}

	if (page.m_y < 0)
	{
		return false;
	}

	if (page.m_y >= m_sizes[page.m_mip])
	{
		return false;
	}

	return true;
}

int PageIndexer::getCount() const
{
	return m_count;
}

int PageIndexer::getMipCount() const
{
	return m_mipcount;
}

SimpleImage::SimpleImage(int _width, int _height, int _channelCount, uint8_t _clearValue)
	: m_width(_width)
	, m_height(_height)
	, m_channelCount(_channelCount)
{
	m_data.resize(m_width * m_height * m_channelCount);
	clear(_clearValue);
}

SimpleImage::SimpleImage(int _width, int _height, int _channelCount, tinystl::vector<uint8_t>& _data)
	: m_width(_width)
	, m_height(_height)
	, m_channelCount(_channelCount)
{
	m_data = _data;
}

void SimpleImage::copy(Point dest_offset, SimpleImage& src, Rect src_rect)
{
	int width = bx::min(m_width - dest_offset.m_x, src_rect.m_width);
	int height = bx::min(m_height - dest_offset.m_y, src_rect.m_height);
	int channels = bx::min(m_channelCount, src.m_channelCount);

	for (int j = 0; j < height; ++j)
	{
		for (int i = 0; i < width; ++i)
		{
			int i1 = ((j + dest_offset.m_y) * m_width + (i + dest_offset.m_x)) * m_channelCount;
			int i2 = ((j + src_rect.m_y) * src.m_width + (i + src_rect.m_x)) * src.m_channelCount;
			for (int c = 0; c < channels; ++c)
			{
				m_data[i1 + c] = src.m_data[i2 + c];
			}
		}
	}
}

void SimpleImage::clear(uint8_t clearValue)
{
	bx::memSet(&m_data[0], clearValue, m_width * m_height * m_channelCount);
}

void SimpleImage::fill(Rect rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	for (int y = rect.minY(); y < rect.maxY(); ++y)
	{
		for (int x = rect.minX(); x < rect.maxX(); ++x)
		{
			m_data[m_channelCount * (y * m_width + x) + 0] = b;
			m_data[m_channelCount * (y * m_width + x) + 1] = g;
			m_data[m_channelCount * (y * m_width + x) + 2] = r;
			m_data[m_channelCount * (y * m_width + x) + 3] = a;
		}
	}
}

void SimpleImage::mipmap(uint8_t* source, int size, int channels, uint8_t* dest)
{
	int mipsize = size / 2;

	for (int y = 0; y < mipsize; ++y)
	{
		for (int x = 0; x < mipsize; ++x)
		{
			for (int c = 0; c < channels; ++c)
			{
				int index = channels * ((y * 2) * size + (x * 2)) + c;
				int sum_value = 4 >> 1;
				sum_value += source[index + channels * (0 * size + 0)];
				sum_value += source[index + channels * (0 * size + 1)];
				sum_value += source[index + channels * (1 * size + 0)];
				sum_value += source[index + channels * (1 * size + 1)];
				dest[channels * (y * mipsize + x) + c] = (uint8_t)(sum_value / 4);
			}
		}
	}
}

Quadtree::Quadtree(Rect _rect, int _level)
	: m_rectangle(_rect)
	, m_level(_level)
{
	for (int i = 0; i < 4; ++i)
	{
		m_children[i] = nullptr;
	}
}

Quadtree::~Quadtree()
{
	for (int i = 0; i < 4; ++i)
	{
		if (m_children[i] != nullptr)
		{
			BX_DELETE(VirtualTexture::getAllocator(), m_children[i]);
		}
	}
}

void Quadtree::add(Page request, Point mapping)
{
	int scale = 1 << request.m_mip; // Same as pow( 2, mip )
	int x = request.m_x * scale;
	int y = request.m_y * scale;

	Quadtree* node = this;

	while (request.m_mip < node->m_level)
	{
		for (int i = 0; i < 4; ++i)
		{
			auto rect = node->getRectangle(i);
			if (rect.contains({ x, y }))
			{
				// Create a new one if needed
				if (node->m_children[i] == nullptr)
				{
					node->m_children[i] = BX_NEW(VirtualTexture::getAllocator(), Quadtree)(rect, node->m_level - 1);
					node = node->m_children[i];
					break;
				}
				// Otherwise traverse the tree
				else
				{
					node = node->m_children[i];
					break;
				}
			}
		}
	}

	// We have created the correct node, now set the mapping
	node->m_mapping = mapping;
}

void Quadtree::remove(Page request)
{
	int  index;
	auto node = findPage(this, request, &index);

	if (node != nullptr)
	{
		BX_DELETE(VirtualTexture::getAllocator(), node->m_children[index]);
		node->m_children[index] = nullptr;
	}
}

void Quadtree::write(SimpleImage& image, int miplevel)
{
	write(this, image, miplevel);
}

Rect Quadtree::getRectangle(int index)
{
	int x = m_rectangle.m_x;
	int y = m_rectangle.m_y;
	int w = m_rectangle.m_width / 2;
	int h = m_rectangle.m_width / 2;

	switch (index)
	{
	case 0: return { x    , y    , w, h };
	case 1: return { x + w, y    , w, h };
	case 2: return { x + w, y + h, w, h };
	case 3: return { x    , y + h, w, h };
	default: break;
	}

	return { 0, 0, 0, 0 };
}

void Quadtree::write(Quadtree* node, SimpleImage& image, int miplevel)
{
	if (node->m_level >= miplevel)
	{
		int rx = node->m_rectangle.m_x >> miplevel;
		int ry = node->m_rectangle.m_y >> miplevel;
		int rw = node->m_rectangle.m_width >> miplevel;
		int rh = node->m_rectangle.m_width >> miplevel;

		image.fill({ rx, ry, rw, rh }, (uint8_t)node->m_mapping.m_x, (uint8_t)node->m_mapping.m_y, (uint8_t)node->m_level, 255);

		for (int i = 0; i < 4; ++i)
		{
			auto child = node->m_children[i];
			if (child != nullptr)
			{
				Quadtree::write(child, image, miplevel);
			}
		}
	}
}

Quadtree* Quadtree::findPage(Quadtree* node, Page request, int* index)
{
	int scale = 1 << request.m_mip; // Same as pow( 2, mip )
	int x = request.m_x * scale;
	int y = request.m_y * scale;

	// Find the parent of the child we want to remove
	bool exitloop = false;
	while (!exitloop)
	{
		exitloop = true;
		for (int i = 0; i < 4; ++i)
		{
			if (node->m_children[i] != nullptr && node->m_children[i]->m_rectangle.contains({ x, y }))
			{
				// We found it
				if (request.m_mip == node->m_level - 1)
				{
					*index = i;
					return node;
				}
				// Check the children
				else
				{
					node = node->m_children[i];
					exitloop = false;
				}
			}
		}
	}

	// We couldn't find it so it must not exist anymore
	*index = -1;
	return nullptr;
}

// PageTable
PageTable::PageTable(PageCache* _cache, VirtualTextureInfo* _info, PageIndexer* _indexer)
	: m_info(_info)
	, m_indexer(_indexer)
	, m_quadtree(nullptr)
	, m_quadtreeDirty(true) // Force quadtree dirty on startup
{
	auto size = m_info->GetPageTableSize();
	m_quadtree = BX_NEW(VirtualTexture::getAllocator(), Quadtree)({ 0, 0, size, size }, (int)bx::log2((float)size));
	m_texture = bgfx::createTexture2D((uint16_t)size, (uint16_t)size, true, 1, bgfx::TextureFormat::BGRA8, BGFX_SAMPLER_UVW_CLAMP | BGFX_SAMPLER_POINT);

	_cache->added = [=](Page page, Point pt) { m_quadtreeDirty = true; m_quadtree->add(page, pt); };
	_cache->removed = [=](Page page, Point pt) { m_quadtreeDirty = true; m_quadtree->remove(page); BX_UNUSED(pt); };

	auto PageTableSizeLog2 = m_indexer->getMipCount();

	for (int i = 0; i < PageTableSizeLog2; ++i)
	{
		int  mipSize = m_info->GetPageTableSize() >> i;
		auto simpleImage = BX_NEW(VirtualTexture::getAllocator(), SimpleImage)(mipSize, mipSize, s_channelCount);
		auto stagingTexture = bgfx::createTexture2D((uint16_t)mipSize, (uint16_t)mipSize, false, 1, bgfx::TextureFormat::BGRA8, BGFX_SAMPLER_UVW_CLAMP | BGFX_SAMPLER_POINT);
		m_images.push_back(simpleImage);
		m_stagingTextures.push_back(stagingTexture);
	}
}

PageTable::~PageTable()
{
	BX_DELETE(VirtualTexture::getAllocator(), m_quadtree);
	bgfx::destroy(m_texture);

	for (int i = 0; i < (int)m_images.size(); ++i)
	{
		BX_DELETE(VirtualTexture::getAllocator(), m_images[i]);
	}

	for (int i = 0; i < (int)m_stagingTextures.size(); ++i)
	{
		bgfx::destroy(m_stagingTextures[i]);
	}
}

void PageTable::update(bgfx::ViewId blitViewId)
{
	if (!m_quadtreeDirty)
	{
		return;
	}

	m_quadtreeDirty = false;
	auto PageTableSizeLog2 = m_indexer->getMipCount();

	for (int i = 0; i < PageTableSizeLog2; ++i)
	{
		m_quadtree->write(*m_images[i], i);
		auto stagingTexture = m_stagingTextures[i];
		auto size = uint16_t(m_info->GetPageTableSize() >> i);
		bgfx::updateTexture2D(stagingTexture, 0, 0, 0, 0, size, size, bgfx::copy(&m_images[i]->m_data[0], size * size * s_channelCount));
		bgfx::blit(blitViewId, m_texture, uint8_t(i), 0, 0, 0, stagingTexture, 0, 0, 0, 0, size, size);
	}
}

bgfx::TextureHandle PageTable::getTexture()
{
	return m_texture;
}

// PageLoader
PageLoader::PageLoader(TileDataFile* _tileDataFile, PageIndexer* _indexer, VirtualTextureInfo* _info)
	: m_colorMipLevels(false)
	, m_showBorders(false)
	, m_tileDataFile(_tileDataFile)
	, m_indexer(_indexer)
	, m_info(_info)
{
}

void PageLoader::submit(Page request)
{
	ReadState state;
	state.m_page = request;
	loadPage(state);
	onPageLoadComplete(state);
}

void PageLoader::loadPage(ReadState& state)
{
	int size = m_info->GetPageSize() * m_info->GetPageSize() * s_channelCount;
	state.m_data.resize(size);

	if (m_colorMipLevels)
	{
		copyColor(&state.m_data[0], state.m_page);
	}
	else if (m_tileDataFile != nullptr)
	{
		m_tileDataFile->readPage(m_indexer->getIndexFromPage(state.m_page), &state.m_data[0]);
	}

	if (m_showBorders)
	{
		copyBorder(&state.m_data[0]);
	}
}

void PageLoader::onPageLoadComplete(ReadState& state)
{
	loadComplete(state.m_page, &state.m_data[0]);
}

void PageLoader::copyBorder(uint8_t* image)
{
	int pagesize = m_info->GetPageSize();
	int bordersize = m_info->m_borderSize;

	for (int i = 0; i < pagesize; ++i)
	{
		int xindex = bordersize * pagesize + i;
		image[xindex * s_channelCount + 0] = 0;
		image[xindex * s_channelCount + 1] = 255;
		image[xindex * s_channelCount + 2] = 0;
		image[xindex * s_channelCount + 3] = 255;

		int yindex = i * pagesize + bordersize;
		image[yindex * s_channelCount + 0] = 0;
		image[yindex * s_channelCount + 1] = 255;
		image[yindex * s_channelCount + 2] = 0;
		image[yindex * s_channelCount + 3] = 255;
	}
}

void PageLoader::copyColor(uint8_t* image, Page request)
{
	static const Color colors[] =
	{
		{   0,   0, 255, 255 },
		{   0, 255, 255, 255 },
		{ 255,   0,   0, 255 },
		{ 255,   0, 255, 255 },
		{ 255, 255,   0, 255 },
		{  64,  64, 192, 255 },
		{  64, 192,  64, 255 },
		{  64, 192, 192, 255 },
		{ 192,  64,  64, 255 },
		{ 192,  64, 192, 255 },
		{ 192, 192,  64, 255 },
		{   0, 255,   0, 255 },
	};

	int pagesize = m_info->GetPageSize();

	for (int y = 0; y < pagesize; ++y)
	{
		for (int x = 0; x < pagesize; ++x)
		{
			image[(y * pagesize + x) * s_channelCount + 0] = colors[request.m_mip].m_b;
			image[(y * pagesize + x) * s_channelCount + 1] = colors[request.m_mip].m_g;
			image[(y * pagesize + x) * s_channelCount + 2] = colors[request.m_mip].m_r;
			image[(y * pagesize + x) * s_channelCount + 3] = colors[request.m_mip].m_a;
		}
	}
}

PageCache::PageCache(TextureAtlas* _atlas, PageLoader* _loader, int _count)
	: m_atlas(_atlas)
	, m_loader(_loader)
	, m_count(_count)
{
	clear();
	m_loader->loadComplete = [&](Page page, uint8_t* data) { loadComplete(page, data); };
}

// Update the pages's position in the lru
bool PageCache::touch(Page page)
{
	if (m_loading.find(page) == m_loading.end())
	{
		if (m_lru_used.find(page) != m_lru_used.end())
		{
			// Find the page (slow!!) and add it to the back of the list
			for (auto it = m_lru.begin(); it != m_lru.end(); ++it)
			{
				if (it->m_page == page)
				{
					auto lruPage = *it;
					m_lru.erase(it);
					m_lru.push_back(lruPage);
					return true;
				}
			}
			return false;
		}
	}

	return false;
}

// Schedule a load if not already loaded or loading
bool PageCache::request(Page request, bgfx::ViewId blitViewId)
{
	m_blitViewId = blitViewId;
	if (m_loading.find(request) == m_loading.end())
	{
		if (m_lru_used.find(request) == m_lru_used.end())
		{
			m_loading.insert(request);
			m_loader->submit(request);
			return true;
		}
	}

	return false;
}

void PageCache::clear()
{
	for (auto& lru_page : m_lru)
	{
		if (m_lru_used.find(lru_page.m_page) != m_lru_used.end())
		{
			removed(lru_page.m_page, lru_page.m_point);
		}
	}
	m_lru_used.clear();
	m_lru.clear();
	m_lru.reserve(m_count * m_count);
	m_current = 0;
}

void PageCache::loadComplete(Page page, uint8_t* data)
{
	m_loading.erase(page);

	// Find a place in the atlas for the data
	Point pt;

	if (m_current == m_count * m_count)
	{
		// Remove the oldest lru page and remember it's location so we can use it
		auto lru_page = m_lru[0];
		m_lru.erase(m_lru.begin());
		m_lru_used.erase(lru_page.m_page);
		pt = lru_page.m_point;
		// Notify that we removed a page
		removed(lru_page.m_page, lru_page.m_point);
	}
	else
	{
		pt = { m_current % m_count, m_current / m_count };
		++m_current;

		if (m_current == m_count * m_count)
		{
			bx::debugPrintf("Atlas is full!");
		}
	}

	// Notify atlas that he can upload the page and add the page to lru
	m_atlas->uploadPage(pt, data, m_blitViewId);
	m_lru.push_back({ page, pt });
	m_lru_used.insert(page);

	// Signal that we added a page
	added(page, pt);
}

// TextureAtlas
TextureAtlas::TextureAtlas(VirtualTextureInfo* _info, int _count, int _uploadsperframe)
	: m_info(_info)
	, m_stagingPool(_info->GetPageSize(), _info->GetPageSize(), _uploadsperframe, false)
{
	// Create atlas texture
	int pagesize = m_info->GetPageSize();
	int size = _count * pagesize;

	m_texture = bgfx::createTexture2D(
		  (uint16_t)size
		, (uint16_t)size
		, false
		, 1
		, bgfx::TextureFormat::BGRA8
		, BGFX_SAMPLER_UVW_CLAMP
		);
}

TextureAtlas::~TextureAtlas()
{
	bgfx::destroy(m_texture);
}

void TextureAtlas::setUploadsPerFrame(int count)
{
	m_stagingPool.grow(count);
}

void TextureAtlas::uploadPage(Point pt, uint8_t* data, bgfx::ViewId blitViewId)
{
	// Get next staging texture to write to
	auto writer = m_stagingPool.getTexture();
	m_stagingPool.next();

	// Update texture with new atlas data
	auto   pagesize = uint16_t(m_info->GetPageSize());
	bgfx::updateTexture2D(
		  writer
		, 0
		, 0
		, 0
		, 0
		, pagesize
		, pagesize
		, bgfx::copy(data, pagesize * pagesize * s_channelCount)
		);

	// Copy the texture part to the actual atlas texture
	auto xpos = uint16_t(pt.m_x * pagesize);
	auto ypos = uint16_t(pt.m_y * pagesize);
	bgfx::blit(blitViewId, m_texture, 0, xpos, ypos, 0, writer, 0, 0, 0, 0, pagesize, pagesize);
}

bgfx::TextureHandle TextureAtlas::getTexture()
{
	return m_texture;
}

// FeedbackBuffer
FeedbackBuffer::FeedbackBuffer(VirtualTextureInfo* _info, int _width, int _height)
	: m_info(_info)
	, m_width(_width)
	, m_height(_height)
	, m_stagingPool(_width, _height, 1, true)
{
	// Setup classes
	m_indexer = BX_NEW(VirtualTexture::getAllocator(), PageIndexer)(m_info);
	m_requests.resize(m_indexer->getCount());

	// Initialize and clear buffers
	m_downloadBuffer.resize(m_width * m_height * s_channelCount);
	bx::memSet(&m_downloadBuffer[0], 0, m_width * m_height * s_channelCount);
	clear();

	// Initialize feedback frame buffer
	bgfx::TextureHandle feedbackFrameBufferTextures[] =
	{
		bgfx::createTexture2D(uint16_t(m_width), uint16_t(m_height), false, 1, bgfx::TextureFormat::BGRA8, BGFX_TEXTURE_RT),
		bgfx::createTexture2D(uint16_t(m_width), uint16_t(m_height), false, 1, bgfx::TextureFormat::D24S8, BGFX_TEXTURE_RT),
	};

	m_feedbackFrameBuffer = bgfx::createFrameBuffer(BX_COUNTOF(feedbackFrameBufferTextures), feedbackFrameBufferTextures, true);
	m_lastStagingTexture = { bgfx::kInvalidHandle };
}

FeedbackBuffer::~FeedbackBuffer()
{
	BX_DELETE(VirtualTexture::getAllocator(), m_indexer);
	bgfx::destroy(m_feedbackFrameBuffer);
}

void FeedbackBuffer::clear()
{
	// Clear Table
	bx::memSet(&m_requests[0], 0, sizeof(int) * m_indexer->getCount());
}

void FeedbackBuffer::copy(bgfx::ViewId viewId)
{
	m_lastStagingTexture = m_stagingPool.getTexture();
	// Copy feedback buffer render target to staging texture
	bgfx::blit(viewId, m_lastStagingTexture, 0, 0, bgfx::getTexture(m_feedbackFrameBuffer));
	m_stagingPool.next();
}

void FeedbackBuffer::download()
{
	// Check if there's an already rendered feedback buffer available
	if (m_lastStagingTexture.idx == bgfx::kInvalidHandle)
	{
		return;
	}

	// Read the texture
	bgfx::readTexture(m_lastStagingTexture, &m_downloadBuffer[0]);
	// Loop through pixels and check if anything was written
	auto data = &m_downloadBuffer[0];
	auto colors = (Color*)data;
	auto dataSize = m_width * m_height;

	for (int i = 0; i < dataSize; ++i)
	{
		auto& color = colors[i];
		if (color.m_a >= 0xff)
		{
			// Page found! Add it to the request queue
			Page request = { color.m_b, color.m_g, color.m_r };
			addRequestAndParents(request);
			// Clear the pixel, so that we don't have to do it in another pass
			color = { 0,0,0,0 };
		}
	}
}

// This function validates the pages and adds the page's parents
// We do this so that we can fall back to them if we run out of memory
void FeedbackBuffer::addRequestAndParents(Page request)
{
	auto PageTableSizeLog2 = m_indexer->getMipCount();
	auto count = PageTableSizeLog2 - request.m_mip;

	for (int i = 0; i < count; ++i)
	{
		int xpos = request.m_x >> i;
		int ypos = request.m_y >> i;

		Page page = { xpos, ypos, request.m_mip + i };

		// If it's not a valid page (position or mip out of range) just skip it
		if (!m_indexer->isValid(page))
		{
			return;
		}

		++m_requests[m_indexer->getIndexFromPage(page)];
	}
}

const tinystl::vector<int>& FeedbackBuffer::getRequests() const
{
	return m_requests;
}

bgfx::FrameBufferHandle FeedbackBuffer::getFrameBuffer()
{
	return m_feedbackFrameBuffer;
}

int FeedbackBuffer::getWidth() const
{
	return m_width;
}

int FeedbackBuffer::getHeight() const
{
	return m_height;
}

// VirtualTexture
VirtualTexture::VirtualTexture(TileDataFile* _tileDataFile, VirtualTextureInfo* _info, int _atlassize, int _uploadsperframe, int _mipBias)
	: m_tileDataFile(_tileDataFile)
	, m_info(_info)
	, m_uploadsPerFrame(_uploadsperframe)
	, m_mipBias(_mipBias)

{
	m_atlasCount = _atlassize / m_info->GetPageSize();

	// Setup indexer
	m_indexer = BX_NEW(VirtualTexture::getAllocator(), PageIndexer)(m_info);
	m_pagesToLoad.reserve(m_indexer->getCount());

	// Setup classes
	m_atlas = BX_NEW(VirtualTexture::getAllocator(), TextureAtlas)(m_info, m_atlasCount, m_uploadsPerFrame);
	m_loader = BX_NEW(VirtualTexture::getAllocator(), PageLoader)(m_tileDataFile, m_indexer, m_info);
	m_cache = BX_NEW(VirtualTexture::getAllocator(), PageCache)(m_atlas, m_loader, m_atlasCount);
	m_pageTable = BX_NEW(VirtualTexture::getAllocator(), PageTable)(m_cache, m_info, m_indexer);

	// Create uniforms
	u_vt_settings_1 = bgfx::createUniform("u_vt_settings_1", bgfx::UniformType::Vec4);
	u_vt_settings_2 = bgfx::createUniform("u_vt_settings_2", bgfx::UniformType::Vec4);
	s_vt_page_table = bgfx::createUniform("s_vt_page_table", bgfx::UniformType::Sampler);
	s_vt_texture_atlas = bgfx::createUniform("s_vt_texture_atlas", bgfx::UniformType::Sampler);
}

VirtualTexture::~VirtualTexture()
{
	// Destroy
	BX_DELETE(VirtualTexture::getAllocator(), m_indexer);
	BX_DELETE(VirtualTexture::getAllocator(), m_atlas);
	BX_DELETE(VirtualTexture::getAllocator(), m_loader);
	BX_DELETE(VirtualTexture::getAllocator(), m_cache);
	BX_DELETE(VirtualTexture::getAllocator(), m_pageTable);
	// Destroy all uniforms and textures
	bgfx::destroy(u_vt_settings_1);
	bgfx::destroy(u_vt_settings_2);
	bgfx::destroy(s_vt_page_table);
	bgfx::destroy(s_vt_texture_atlas);
}

int VirtualTexture::getMipBias() const
{
	return m_mipBias;
}

void VirtualTexture::setMipBias(int value)
{
	m_mipBias = bx::max(0, value);
}

void VirtualTexture::setUniforms()
{
	struct
	{
		struct
		{
			float VirtualTextureSize;
			float ooAtlasScale;
			float BorderScale;
			float BorderOffset;
		} m_settings_1;

		struct
		{
			float MipBias;
			float PageTableSize;
			float unused1;
			float unused2;
		} m_settings_2;

	} uniforms;

	int pagesize = m_info->GetPageSize();
	uniforms.m_settings_1.VirtualTextureSize = (float)m_info->m_virtualTextureSize;
	uniforms.m_settings_1.ooAtlasScale = 1.0f / (float)m_atlasCount;
	uniforms.m_settings_1.BorderScale = (float)((pagesize - 2.0f * m_info->m_borderSize) / pagesize);
	uniforms.m_settings_1.BorderOffset = (float)m_info->m_borderSize / (float)pagesize;
	uniforms.m_settings_2.MipBias = (float)m_mipBias;
	uniforms.m_settings_2.PageTableSize = (float)m_info->GetPageTableSize();
	uniforms.m_settings_2.unused1 = uniforms.m_settings_2.unused2 = 0.0f;

	bgfx::setUniform(u_vt_settings_1, &uniforms.m_settings_1);
	bgfx::setUniform(u_vt_settings_2, &uniforms.m_settings_2);

	bgfx::setTexture(0, s_vt_page_table, m_pageTable->getTexture());
	bgfx::setTexture(1, s_vt_texture_atlas, m_atlas->getTexture());
}

void VirtualTexture::setUploadsPerFrame(int count)
{
	m_uploadsPerFrame = count;
	m_atlas->setUploadsPerFrame(count);
}

int VirtualTexture::getUploadsPerFrame() const
{
	return m_uploadsPerFrame;
}


void VirtualTexture::enableShowBoarders(bool enable)
{
	if (m_loader->m_showBorders == enable)
	{
		return;
	}

	m_loader->m_showBorders = enable;
	clear();
}

bool VirtualTexture::isShowBoardersEnabled() const
{
	return m_loader->m_showBorders;
}

void VirtualTexture::enableColorMipLevels(bool enable)
{
	if (m_loader->m_colorMipLevels == enable)
	{
		return;
	}

	m_loader->m_colorMipLevels = enable;
	clear();
}

bool VirtualTexture::isColorMipLevelsEnabled() const
{
	return m_loader->m_colorMipLevels;
}

bgfx::TextureHandle VirtualTexture::getAtlastTexture()
{
	return m_atlas->getTexture();
}

bgfx::TextureHandle VirtualTexture::getPageTableTexture()
{
	return m_pageTable->getTexture();
}

void VirtualTexture::clear()
{
	m_cache->clear();
}

void VirtualTexture::update(const tinystl::vector<int>& requests, bgfx::ViewId blitViewId)
{
	m_pagesToLoad.clear();

	// Find out what is already in memory
	// If it is, update it's position in the LRU collection
	// Otherwise add it to the list of pages to load
	int touched = 0;
	for (int i = 0; i < (int)requests.size(); ++i)
	{
		if (requests[i] > 0)
		{
			PageCount pc(m_indexer->getPageFromIndex(i), requests[i]);
			if (!m_cache->touch(pc.m_page))
			{
				m_pagesToLoad.push_back(pc);
			}
			else
			{
				++touched;
			}
		}
	}

	// Check to make sure we don't thrash
	if (touched < m_atlasCount * m_atlasCount)
	{
		// sort by low res to high res and number of requests
		bx::quickSort(
			m_pagesToLoad.begin()
			, uint32_t(m_pagesToLoad.size())
			, sizeof(vt::PageCount)
			, [](const void* _a, const void* _b) -> int32_t {
			const vt::PageCount& lhs = *(const vt::PageCount*)(_a);
			const vt::PageCount& rhs = *(const vt::PageCount*)(_b);
			return lhs.compareTo(rhs);
		});

		// if more pages than will fit in memory or more than update per frame drop high res pages with lowest use count
		int loadcount = bx::min(bx::min((int)m_pagesToLoad.size(), m_uploadsPerFrame), m_atlasCount * m_atlasCount);
		for (int i = 0; i < loadcount; ++i)
			m_cache->request(m_pagesToLoad[i].m_page, blitViewId);
	}
	else
	{
		// The problem here is that all pages in cache are requested and the new or high res ones don't get uploaded
		// We can adjust the mip bias to make it all fit. This solves the problem of page cache thrashing
		--m_mipBias;
	}

	// Update the page table
	m_pageTable->update(blitViewId);
}

bx::AllocatorI* VirtualTexture::s_allocator = nullptr;

void VirtualTexture::setAllocator(bx::AllocatorI* allocator)
{
	s_allocator = allocator;
}

bx::AllocatorI* VirtualTexture::getAllocator()
{
	return s_allocator;
}

TileDataFile::TileDataFile(const bx::FilePath& filename, VirtualTextureInfo* _info, bool _readWrite) : m_info(_info)
{
	const char* access = _readWrite ? "w+b" : "rb";
	m_file = fopen(filename.getCPtr(), access);
	m_size = m_info->GetPageSize() * m_info->GetPageSize() * s_channelCount;
}

TileDataFile::~TileDataFile()
{
	fclose(m_file);
}

void TileDataFile::readInfo()
{
	fseek(m_file, 0, SEEK_SET);
	auto ret = fread(m_info, sizeof(*m_info), 1, m_file);
	BX_UNUSED(ret);
	m_size = m_info->GetPageSize() * m_info->GetPageSize() * s_channelCount;
}

void TileDataFile::writeInfo()
{
	fseek(m_file, 0, SEEK_SET);
	auto ret = fwrite(m_info, sizeof(*m_info), 1, m_file);
	BX_UNUSED(ret);
}

void TileDataFile::readPage(int index, uint8_t* data)
{
	fseek(m_file, m_size * index + s_tileFileDataOffset, SEEK_SET);
	auto ret = fread(data, m_size, 1, m_file);
	BX_UNUSED(ret);
}

void TileDataFile::writePage(int index, uint8_t* data)
{
	fseek(m_file, m_size * index + s_tileFileDataOffset, SEEK_SET);
	auto ret = fwrite(data, m_size, 1, m_file);
	BX_UNUSED(ret);
}

// TileGenerator
TileGenerator::TileGenerator(VirtualTextureInfo* _info)
	: m_info(_info)
	, m_indexer(nullptr)
	, m_tileDataFile(nullptr)
	, m_sourceImage(nullptr)
	, m_page1Image(nullptr)
	, m_page2Image(nullptr)
	, m_2xtileImage(nullptr)
	, m_4xtileImage(nullptr)
	, m_tileImage(nullptr)
{
	m_tilesize = m_info->m_tileSize;
	m_pagesize = m_info->GetPageSize();
}

TileGenerator::~TileGenerator()
{
	if (m_sourceImage != nullptr)
	{
		bimg::imageFree(m_sourceImage);
	}

	BX_DELETE(VirtualTexture::getAllocator(), m_indexer);

	BX_DELETE(VirtualTexture::getAllocator(), m_page1Image);
	BX_DELETE(VirtualTexture::getAllocator(), m_page2Image);
	BX_DELETE(VirtualTexture::getAllocator(), m_2xtileImage);
	BX_DELETE(VirtualTexture::getAllocator(), m_4xtileImage);
	BX_DELETE(VirtualTexture::getAllocator(), m_tileImage);
}

bool TileGenerator::generate(const bx::FilePath& _filePath)
{
	const bx::StringView baseName = _filePath.getBaseName();

	// Generate cache filename
	char tmp[256];
	bx::snprintf(tmp, sizeof(tmp), "%.*s.vt", baseName.getLength(), baseName.getPtr() );

	bx::FilePath cacheFilePath("temp");
	cacheFilePath.join(tmp);

	// Check if tile file already exist
	{
		bx::Error err;
		bx::FileReader fileReader;

		if (bx::open(&fileReader, cacheFilePath, &err) )
		{
			bx::close(&fileReader);

			bx::debugPrintf("Tile data file '%s' already exists. Skipping generation.\n", cacheFilePath.getCPtr() );
			return true;
		}
	}

	// Read image
	{
		bx::debugPrintf("Reading image '%s'.\n", _filePath.getCPtr() );

		bx::Error err;
		bx::FileReader fileReader;

		if (!bx::open(&fileReader, _filePath, &err) )
		{
			bx::debugPrintf("Image open failed'%s'.\n", _filePath.getCPtr() );
			return false;
		}

		int64_t size = bx::getSize(&fileReader);

		if (0 == size)
		{
			bx::debugPrintf("Image '%s' size is 0.\n", _filePath.getCPtr() );
			return false;
		}

		uint8_t* rawImage = (uint8_t*)BX_ALLOC(VirtualTexture::getAllocator(), size_t(size) );

		bx::read(&fileReader, rawImage, int32_t(size), &err);
		bx::close(&fileReader);

		if (!err.isOk() )
		{
			bx::debugPrintf("Image read failed'%s'.\n", _filePath.getCPtr() );
			BX_FREE(VirtualTexture::getAllocator(), rawImage);
			return false;
		}

		m_sourceImage = bimg::imageParse(VirtualTexture::getAllocator(), rawImage, uint32_t(size), bimg::TextureFormat::BGRA8, &err);
		BX_FREE(VirtualTexture::getAllocator(), rawImage);

		if (!err.isOk() )
		{
			bx::debugPrintf("Image parse failed'%s'.\n", _filePath.getCPtr() );
			return false;
		}
	}

	// Setup
	m_info->m_virtualTextureSize = int(m_sourceImage->m_width);
	m_indexer = BX_NEW(VirtualTexture::getAllocator(), PageIndexer)(m_info);

	// Open tile data file
	m_tileDataFile = BX_NEW(VirtualTexture::getAllocator(), TileDataFile)(cacheFilePath, m_info, true);
	m_page1Image   = BX_NEW(VirtualTexture::getAllocator(), SimpleImage)(m_pagesize, m_pagesize, s_channelCount, 0xff);
	m_page2Image   = BX_NEW(VirtualTexture::getAllocator(), SimpleImage)(m_pagesize, m_pagesize, s_channelCount, 0xff);
	m_tileImage    = BX_NEW(VirtualTexture::getAllocator(), SimpleImage)(m_tilesize, m_tilesize, s_channelCount, 0xff);
	m_2xtileImage  = BX_NEW(VirtualTexture::getAllocator(), SimpleImage)(m_tilesize * 2, m_tilesize * 2, s_channelCount, 0xff);
	m_4xtileImage  = BX_NEW(VirtualTexture::getAllocator(), SimpleImage)(m_tilesize * 4, m_tilesize * 4, s_channelCount, 0xff);

	// Generate tiles
	bx::debugPrintf("Generating tiles\n");
	auto mipcount = m_indexer->getMipCount();
	for (int i = 0; i < mipcount; ++i)
	{
		int count = (m_info->m_virtualTextureSize / m_tilesize) >> i;
		bx::debugPrintf("Generating Mip:%d Count:%dx%d\n", i, count, count);
		for (int y = 0; y < count; ++y)
		{
			for (int x = 0; x < count; ++x)
			{
				Page page = { x, y, i };
				int index = m_indexer->getIndexFromPage(page);
				CopyTile(*m_page1Image, page);
				m_tileDataFile->writePage(index, &m_page1Image->m_data[0]);
			}
		}
	}

	bx::debugPrintf("Finising\n");
	// Write header
	m_tileDataFile->writeInfo();
	// Close tile file
	BX_DELETE(VirtualTexture::getAllocator(), m_tileDataFile);
	m_tileDataFile = nullptr;
	bx::debugPrintf("Done!\n");
	return true;
}

void TileGenerator::CopyTile(SimpleImage& image, Page request)
{
	if (request.m_mip == 0)
	{
		int x = request.m_x * m_tilesize - m_info->m_borderSize;
		int y = request.m_y * m_tilesize - m_info->m_borderSize;
		// Copy sub-image with border
		auto srcPitch = m_sourceImage->m_width * s_channelCount;
		auto src = (uint8_t*)m_sourceImage->m_data;
		auto dstPitch = image.m_width * image.m_channelCount;
		auto dst = &image.m_data[0];
		for (int iy = 0; iy < m_pagesize; ++iy)
		{
			int ry = bx::clamp(y + iy, 0, (int)m_sourceImage->m_height - 1);
			for (int ix = 0; ix < m_pagesize; ++ix)
			{
				int rx = bx::clamp(x + ix, 0, (int)m_sourceImage->m_width - 1);
				bx::memCopy(&dst[iy * dstPitch + ix * image.m_channelCount], &src[ry * srcPitch + rx * s_channelCount], image.m_channelCount);
			}
		}
	}
	else
	{
		int xpos = request.m_x << 1;
		int ypos = request.m_y << 1;
		int mip = request.m_mip - 1;

		int size = m_info->GetPageTableSize() >> mip;

		m_4xtileImage->clear((uint8_t)request.m_mip);

		for (int y = 0; y < 4; ++y)
		{
			for (int x = 0; x < 4; ++x)
			{
				Page page = { xpos + x - 1, ypos + y - 1, mip };

				// Wrap so we get the border sections of other pages
				page.m_x = (int)bx::mod((float)page.m_x, (float)size);
				page.m_y = (int)bx::mod((float)page.m_y, (float)size);

				m_tileDataFile->readPage(m_indexer->getIndexFromPage(page), &m_page2Image->m_data[0]);

				Rect src_rect = { m_info->m_borderSize, m_info->m_borderSize, m_tilesize, m_tilesize };
				Point dst_offset = { x * m_tilesize, y * m_tilesize };

				m_4xtileImage->copy(dst_offset, *m_page2Image, src_rect);
			}
		}

		SimpleImage::mipmap(&m_4xtileImage->m_data[0], m_4xtileImage->m_width, s_channelCount, &m_2xtileImage->m_data[0]);

		Rect srect = { m_tilesize / 2 - m_info->m_borderSize, m_tilesize / 2 - m_info->m_borderSize, m_pagesize, m_pagesize };
		image.copy({ 0,0 }, *m_2xtileImage, srect);
	}
}

} // namespace vt
