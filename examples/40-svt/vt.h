#pragma once
#include "common.h"
#include "bgfx_utils.h"
#include "bimg/decode.h"
#include <vector>
#include <set>
#include <functional>

namespace vt
{

// Forward declarations
class PageCache;
class TextureAtlas;
class TileDataFile;

// Point
struct Point
{
	int m_x, m_y;
};

// Rect
struct Rect
{
	int minX() const
	{
		return m_x;
	}

	int minY() const
	{
		return m_y;
	}

	int maxX() const
	{
		return m_x + m_width;
	}

	int maxY() const
	{
		return m_y + m_height;
	}

	bool contains(const Point& p) const
	{
		return p.m_x >= minX() && p.m_y >= minY() && p.m_x < maxX() && p.m_y < maxY();
	}

	int m_x, m_y, m_width, m_height;
};

// Color
struct Color
{
	uint8_t m_r, m_g, m_b, m_a;
};

// Page
struct Page
{
	uint64_t hash() const;
	bool   operator==(const Page& page) const;
	bool   operator<(const Page& page) const;

	int m_x;
	int m_y;
	int m_mip;
};

// PageCount
struct PageCount
{
	Page m_page;
	int  m_count;

	PageCount(Page _page = Page(), int _count = 0);

	int  compareTo(const PageCount& other) const;
	bool operator==(const PageCount& other) const;
	bool operator<(const PageCount& other) const;
};

// VirtualTextureInfo
struct VirtualTextureInfo
{
	VirtualTextureInfo();
	int GetPageSize() const;
	int GetPageTableSize() const;

	int m_virtualTextureSize = 0;
	int m_tileSize = 0;
	int m_borderSize = 0;
};

// StagingPool
class StagingPool
{
public:
	StagingPool(int _width, int _height, int _count, bool _readBack);
	~StagingPool();

	void grow(int count);

	bgfx::TextureHandle getTexture();
	void				next();

private:
	std::vector<bgfx::TextureHandle>  m_stagingTextures;

	int			m_stagingTextureIndex;
	int			m_width;
	int			m_height;
	uint64_t	m_flags;
};

// PageIndexer
struct PageIndexer
{
public:
	PageIndexer(VirtualTextureInfo* _info);

	int  getIndexFromPage(Page page);
	Page getPageFromIndex(int index);

	bool isValid(Page page);
	int  getCount() const;

private:
	VirtualTextureInfo* m_info;
	int                 m_mipcount;
	std::vector<int>    m_offsets; // This stores the offsets to the first page of the start of a mipmap level
	std::vector<int>    m_sizes; // This stores the sizes of various mip levels
	std::vector<Page>   m_reverse;
	int					m_count;
};

// SimpleImage
struct SimpleImage
{
	SimpleImage(int _width, int _height, int _channelCount, uint8_t _clearValue = 0);
	SimpleImage(int _width, int _height, int _channelCount, std::vector<uint8_t>& _data);

	void copy(Point dest_offset, SimpleImage& src, Rect src_rect);
	void clear(uint8_t clearValue = 0);
	void fill(Rect rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	static void mipmap(uint8_t* source, int size, int channels, uint8_t* dest);

	int					 m_width = 0;
	int					 m_height = 0;
	int					 m_channelCount = 0;
	std::vector<uint8_t> m_data;
};

// Quadtree
struct Quadtree
{
	Quadtree(Rect _rect, int _level);
	~Quadtree();

	void             add(Page request, Point mapping);
	void             remove(Page request);
	void             write(SimpleImage& image, int miplevel);
	Rect			 getRectangle(int index);

	void		     write(Quadtree* node, SimpleImage& image, int miplevel);
	static Quadtree* findPage(Quadtree* node, Page request, int* index);

	int		  m_level;
	Rect      m_rectangle;
	Point     m_mapping;
	Quadtree* m_children[4];
};

// PageTable
class PageTable
{
public:
	PageTable(PageCache* _cache, VirtualTextureInfo* _info, PageIndexer* _indexer);
	~PageTable();

	void update(bgfx::ViewId blitViewId);
	bgfx::TextureHandle getTexture();

private:
	VirtualTextureInfo* m_info;
	bgfx::TextureHandle m_texture;
	PageIndexer*		m_indexer;
	Quadtree*			m_quadtree;
	bool				m_quadtreeDirty;

	std::vector<SimpleImage*>			m_images;
	std::vector<bgfx::TextureHandle>    m_stagingTextures;
};

// PageLoader
class PageLoader
{
public:
	struct ReadState
	{
		Page					m_page;
		std::vector<uint8_t>	m_data;
	};

	PageLoader(TileDataFile* _tileDataFile, PageIndexer* _indexer, VirtualTextureInfo* _info);
	void submit(Page request);
	void loadPage(ReadState& state);
	void onPageLoadComplete(ReadState& state);
	void copyBorder(uint8_t* image);
	void copyColor(uint8_t* image, Page request);

	std::function<void(Page, uint8_t*)> loadComplete;

	bool m_colorMipLevels;
	bool m_showBorders;

private:
	TileDataFile*		m_tileDataFile;
	PageIndexer*        m_indexer;
	VirtualTextureInfo* m_info;
};

// PageCache
class PageCache
{
public:
	PageCache(VirtualTextureInfo* _info, TextureAtlas* _atlas, PageLoader* _loader, PageIndexer* _indexer, int _count);
	bool touch(Page page);
	bool request(Page request, bgfx::ViewId blitViewId);
	void clear();
	void loadComplete(Page page, uint8_t* data);

	// These callbacks are used to notify the other systems
	std::function<void(Page, Point)> removed;
	std::function<void(Page, Point)> added;

private:
	VirtualTextureInfo* m_info;
	TextureAtlas*		m_atlas;
	PageLoader*			m_loader;
	PageIndexer*		m_indexer;

	int m_count;

	struct LruPage
	{
		Page	m_page;
		Point	m_point;

		bool operator==(const Page& other) const
		{
			return m_page == other;
		}
	};

	int m_current; // This is used for generating the texture atlas indices before the lru is full

	std::set<Page>       m_lru_used;
	std::vector<LruPage> m_lru;
	std::set<Page>       m_loading;

	bgfx::ViewId m_blitViewId;
};

// TextureAtlas
class TextureAtlas
{
public:
	TextureAtlas(VirtualTextureInfo* _info, int count, int uploadsperframe);
	~TextureAtlas();

	void setUploadsPerFrame(int count);
	void uploadPage(Point pt, uint8_t* data, bgfx::ViewId blitViewId);

	bgfx::TextureHandle getTexture();

private:
	VirtualTextureInfo*  m_info;
	bgfx::TextureHandle  m_texture;
	StagingPool          m_stagingPool;
};

// FeedbackBuffer
class FeedbackBuffer
{
public:
	FeedbackBuffer(VirtualTextureInfo* _info, int _width, int _height);
	~FeedbackBuffer();

	void clear();

	void copy(bgfx::ViewId viewId);
	void download();

	// This function validates the pages and adds the page's parents
	// We do this so that we can fall back to them if we run out of memory
	void addRequestAndParents(Page request);

	const std::vector<int>& getRequests() const;
	bgfx::FrameBufferHandle getFrameBuffer();

	int getWidth() const;
	int getHeight() const;

private:
	VirtualTextureInfo* m_info;
	PageIndexer*		m_indexer;

	int m_width = 0;
	int m_height = 0;

	StagingPool				m_stagingPool;
	bgfx::TextureHandle		m_lastStagingTexture;
	bgfx::FrameBufferHandle m_feedbackFrameBuffer;

	// This stores the pages by index.  The int value is number of requests.
	std::vector<int>		m_requests;
	std::vector<uint8_t>	m_downloadBuffer;
};

// VirtualTexture
class VirtualTexture
{
public:
	VirtualTexture(TileDataFile* _tileDataFile, VirtualTextureInfo* _info, int _atlassize, int _uploadsperframe, int _mipBias = 4);
	~VirtualTexture();

	int  getMipBias() const;
	void setMipBias(int value);

	void setUploadsPerFrame(int count);
	int getUploadsPerFrame() const;

	void enableShowBoarders(bool enable);
	bool isShowBoardersEnabled() const;

	void enableColorMipLevels(bool enable);
	bool isColorMipLevelsEnabled() const;

	bgfx::TextureHandle getAtlastTexture();
	bgfx::TextureHandle getPageTableTexture();

	void clear();
	void update(const std::vector<int>& requests, bgfx::ViewId blitViewId);

	void setUniforms();

private:
	TileDataFile*		m_tileDataFile;
	VirtualTextureInfo* m_info;
	PageIndexer*        m_indexer;
	PageTable*          m_pageTable;
	TextureAtlas*       m_atlas;
	PageLoader*         m_loader;
	PageCache*          m_cache;

	int m_atlasCount;
	int m_uploadsPerFrame;

	std::vector<PageCount> m_pagesToLoad;

	int m_mipBias;

	bgfx::UniformHandle u_vt_settings_1;
	bgfx::UniformHandle u_vt_settings_2;
	bgfx::UniformHandle s_vt_page_table;
	bgfx::UniformHandle s_vt_texture_atlas;
};

// TileDataFile
class TileDataFile
{
public:
	TileDataFile(const std::string& filename, VirtualTextureInfo* _info, bool _readWrite = false);
	~TileDataFile();

	void readInfo();
	void writeInfo();

	void readPage(int index, uint8_t* data);
	void writePage(int index, uint8_t* data);

private:
	VirtualTextureInfo*	m_info;
	int					m_size;
	FILE*				m_file;
};

// TileGenerator
class TileGenerator
{
public:
	TileGenerator(VirtualTextureInfo* _info);
	~TileGenerator();

	bool generate(const std::string& filename);

private:
	void CopyTile(SimpleImage& image, Page request);

private:
	VirtualTextureInfo* m_info;
	PageIndexer*		m_indexer;
	TileDataFile*		m_tileDataFile;

	int	m_tilesize;
	int	m_pagesize;

	bx::DefaultAllocator	m_allocator;
	bimg::ImageContainer*	m_sourceImage;

	SimpleImage* m_page1Image;
	SimpleImage* m_page2Image;
	SimpleImage* m_2xtileImage;
	SimpleImage* m_4xtileImage;
	SimpleImage* m_tileImage;
};

} // namespace vt
