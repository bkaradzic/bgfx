/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */
 
/*
 * Reference(s):
 * - Based on Virtual Texture Demo by Brad Blanchard
 *   http://web.archive.org/web/20190103162638/http://linedef.com/virtual-texture-demo.html
 */

uniform vec4 u_vt_settings_1;
uniform vec4 u_vt_settings_2;

#define VirtualTextureSize u_vt_settings_1.x
#define AtlasScale u_vt_settings_1.y
#define BorderScale u_vt_settings_1.z
#define BorderOffset u_vt_settings_1.w

#define MipBias u_vt_settings_2.x
#define PageTableSize u_vt_settings_2.y

SAMPLER2D(s_vt_page_table,  0);
SAMPLER2D(s_vt_texture_atlas,  1);

// This function estimates mipmap levels
float MipLevel( vec2 uv, float size )
{
   vec2 dx = dFdx( uv * size );
   vec2 dy = dFdy( uv * size );
   float d = max( dot( dx, dx ), dot( dy, dy ) );

   return max( 0.5 * log2( d ), 0 );
}

// This function samples the page table and returns the page's 
// position and mip level. 
vec3 SampleTable( vec2 uv, float mip )
{
   vec2 offset = fract( uv * PageTableSize ) / PageTableSize;
   return texture2DLod( s_vt_page_table, uv - offset, mip ).xyz;
}

// This functions samples from the texture atlas and returns the final color
vec4 SampleAtlas( vec3 page, vec2 uv )
{
   float mipsize = exp2( floor( page.z * 255.0 + 0.5 ) );

   uv = fract( uv * PageTableSize / mipsize );

   uv *= BorderScale;
   uv += BorderOffset;

   vec2 offset = floor( page.xy * 255.0 + 0.5 );

   return texture2D( s_vt_texture_atlas, ( offset + uv ) * AtlasScale );
}

// Ugly brute force trilinear, look up twice and mix
vec4 VirtualTextureTrilinear( vec2 uv )
{
   float miplevel = MipLevel( uv, VirtualTextureSize );
   miplevel = clamp( miplevel, 0.0, log2( PageTableSize )-1.0 );

   float mip1     = floor( miplevel );
   float mip2    = mip1 + 1.0;
   float mipfrac  = miplevel - mip1;

   vec3 page1 = SampleTable( uv, mip1 );
   vec3 page2 = SampleTable( uv, mip2 );

   vec4 sample1 = SampleAtlas( page1, uv );
   vec4 sample2 = SampleAtlas( page2, uv );

   return mix( sample1, sample2, mipfrac );
}

// Simple bilinear
vec4 VirtualTexture( vec2 uv )
{
   float mip = floor( MipLevel( uv, VirtualTextureSize ) );
   mip = clamp( mip, 0, log2( PageTableSize ) );

   vec3 page = SampleTable( uv, mip );
   return SampleAtlas( page, uv );
}
