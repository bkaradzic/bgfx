/+
+ ┌==============================┐
+ │ AUTO GENERATED! DO NOT EDIT! │
+ └==============================┘
+/
module bgfx.fatal;
import bgfx;

///NOTE: Do NOT use this module! Use the enum with the same name in `bgfx/package.d` instead.
extern(C++, "bgfx") package final abstract class Fatal{
	enum Enum{
		debugCheck,invalidShader,unableToInitialize,unableToCreateTexture,deviceLost,count
	}
}
