/+
+ ┌==============================┐
+ │ AUTO GENERATED! DO NOT EDIT! │
+ └==============================┘
+/
module bgfx.renderertype;
import bgfx;

///NOTE: Do NOT use this module! Use the enum with the same name in `bgfx/package.d` instead.
extern(C++, "bgfx") package final abstract class RendererType{
	enum Enum{
		noop,agc,direct3D9,direct3D11,direct3D12,gnm,metal,nvn,openGLES,openGL,vulkan,webGPU,count
	}
}
