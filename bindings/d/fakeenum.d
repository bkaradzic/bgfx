/+
+ ┌==============================┐
+ │ AUTO GENERATED! DO NOT EDIT! │
+ └==============================┘
+/
module bgfx.fakeenum;

//NOTE: Do NOT use this module! Use the enums with the same names in `bgfx/package.d` instead.
package:
extern(C++, "bgfx") package final abstract class Fatal{
	enum Enum{
		debugCheck,invalidShader,unableToInitialize,unableToCreateTexture,deviceLost,count
	}
}
extern(C++, "bgfx") package final abstract class RendererType{
	enum Enum{
		noop,agc,direct3D11,direct3D12,gnm,metal,nvn,openGLES,openGL,vulkan,count
	}
}
extern(C++, "bgfx") package final abstract class Access{
	enum Enum{
		read,write,readWrite,count
	}
}
extern(C++, "bgfx") package final abstract class Attrib{
	enum Enum{
		position,normal,tangent,bitangent,color0,color1,color2,color3,indices,weight,texCoord0,texCoord1,texCoord2,texCoord3,texCoord4,texCoord5,texCoord6,texCoord7,count
	}
}
extern(C++, "bgfx") package final abstract class AttribType{
	enum Enum{
		uint8,uint10,int16,half,float_,count
	}
}
extern(C++, "bgfx") package final abstract class TextureFormat{
	enum Enum{
		bc1,bc2,bc3,bc4,bc5,bc6h,bc7,etc1,etc2,etc2a,etc2a1,ptc12,ptc14,ptc12a,ptc14a,ptc22,ptc24,atc,atce,atci,astc4x4,astc5x4,astc5x5,astc6x5,astc6x6,astc8x5,astc8x6,astc8x8,astc10x5,astc10x6,astc10x8,astc10x10,astc12x10,astc12x12,unknown,r1,a8,r8,r8i,r8u,r8s,r16,r16i,r16u,r16f,r16s,r32i,r32u,r32f,rg8,rg8i,rg8u,rg8s,rg16,rg16i,rg16u,rg16f,rg16s,rg32i,rg32u,rg32f,rgb8,rgb8i,rgb8u,rgb8s,rgb9e5f,bgra8,rgba8,rgba8i,rgba8u,rgba8s,rgba16,rgba16i,rgba16u,rgba16f,rgba16s,rgba32i,rgba32u,rgba32f,b5g6r5,r5g6b5,bgra4,rgba4,bgr5a1,rgb5a1,rgb10a2,rg11b10f,unknownDepth,d16,d24,d24s8,d32,d16f,d24f,d32f,d0s8,count
	}
}
extern(C++, "bgfx") package final abstract class UniformType{
	enum Enum{
		sampler,end,vec4,mat3,mat4,count
	}
}
extern(C++, "bgfx") package final abstract class BackbufferRatio{
	enum Enum{
		equal,half,quarter,eighth,sixteenth,double_,count
	}
}
extern(C++, "bgfx") package final abstract class OcclusionQueryResult{
	enum Enum{
		invisible,visible,noResult,count
	}
}
extern(C++, "bgfx") package final abstract class Topology{
	enum Enum{
		triList,triStrip,lineList,lineStrip,pointList,count
	}
}
extern(C++, "bgfx") package final abstract class TopologyConvert{
	enum Enum{
		triListFlipWinding,triStripFlipWinding,triListToLineList,triStripToTriList,lineStripToLineList,count
	}
}
extern(C++, "bgfx") package final abstract class TopologySort{
	enum Enum{
		directionFrontToBackMin,directionFrontToBackAvg,directionFrontToBackMax,directionBackToFrontMin,directionBackToFrontAvg,directionBackToFrontMax,distanceFrontToBackMin,distanceFrontToBackAvg,distanceFrontToBackMax,distanceBackToFrontMin,distanceBackToFrontAvg,distanceBackToFrontMax,count
	}
}
extern(C++, "bgfx") package final abstract class ViewMode{
	enum Enum{
		default_,sequential,depthAscending,depthDescending,count
	}
}
extern(C++, "bgfx") package final abstract class NativeWindowHandleType{
	enum Enum{
		default_,wayland,count
	}
}
extern(C++, "bgfx") package final abstract class RenderFrame{
	enum Enum{
		noContext,render,timeout,exiting,count
	}
}
