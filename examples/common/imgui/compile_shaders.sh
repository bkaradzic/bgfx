#!/bin/bash

# Vertex Shaders
rm vs_ocornut_imgui.bin.h

shaderc --platform linux -p -i ../../../src/ -f vs_ocornut_imgui.sc -o vs_ocornut_imgui_glsl.bin.h --type v --varyingdef varying.def.sc --bin2c vs_ocornut_imgui_glsl
shaderc --platform linux -p spirv -i ../../../src/ -f vs_ocornut_imgui.sc -o vs_ocornut_imgui_glsl.bin.h --type v --varyingdef varying.def.sc --bin2c vs_ocornut_imgui_spv
# shaderc --platform windows -p ps_3_0 -O 3 -i ../../../src/ -f vs_ocornut_imgui.sc -o vs_ocornut_imgui_dx9.bin.h --type v --varyingdef varying.def.sc --bin2c vs_ocornut_imgui_dx9
# shaderc --platform windows -p ps_4_0 -O 3 -i ../../../src/ -f vs_ocornut_imgui.sc -o vs_ocornut_imgui_dx11.bin.h --type v --varyingdef varying.def.sc --bin2c vs_ocornut_imgui_dx11
shaderc --platform ios -p metal -O 3 -i ../../../src/ -f vs_ocornut_imgui.sc -o vs_ocornut_imgui_mtl.bin.h --type v --varyingdef varying.def.sc --bin2c vs_ocornut_imgui_mtl
cat vs_ocornut_imgui_* > vs_ocornut_imgui.bin.h

echo "static const uint8_t vs_ocornut_imgui_dx9[1] = {};" >> vs_ocornut_imgui.bin.h
echo "static const uint8_t vs_ocornut_imgui_dx11[1] = {};" >> vs_ocornut_imgui.bin.h
echo "static const uint8_t vs_ocornut_imgui_glsl[1] = {};" >> vs_ocornut_imgui.bin.h
echo "static const uint8_t vs_ocornut_imgui_pssl[1] = {};" >> vs_ocornut_imgui.bin.h

rm vs_ocornut_imgui_*

# Fragment Shaders
rm fs_ocornut_imgui.bin.h

shaderc --platform linux -p -i ../../../src/ -f fs_ocornut_imgui.sc -o fs_ocornut_imgui_glsl.bin.h --type f --varyingdef varying.def.sc --bin2c fs_ocornut_imgui_glsl
shaderc --platform linux -p spirv -i ../../../src/ -f fs_ocornut_imgui.sc -o fs_ocornut_imgui_glsl.bin.h --type f --varyingdef varying.def.sc --bin2c fs_ocornut_imgui_spv
# shaderc --platform windows -p ps_3_0 -O 3 -i ../../../src/ -f fs_ocornut_imgui.sc -o fs_ocornut_imgui_dx9.bin.h --type f --varyingdef varying.def.sc --bin2c fs_ocornut_imgui_dx9
# shaderc --platform windows -p ps_4_0 -O 3 -i ../../../src/ -f fs_ocornut_imgui.sc -o fs_ocornut_imgui_dx11.bin.h --type f --varyingdef varying.def.sc --bin2c fs_ocornut_imgui_dx11
shaderc --platform ios -p metal -O 3 -i ../../../src/ -f fs_ocornut_imgui.sc -o fs_ocornut_imgui_mtl.bin.h --type f --varyingdef varying.def.sc --bin2c fs_ocornut_imgui_mtl
cat fs_ocornut_imgui_* > fs_ocornut_imgui.bin.h

echo "static const uint8_t fs_ocornut_imgui_dx9[1] = {};" >> fs_ocornut_imgui.bin.h
echo "static const uint8_t fs_ocornut_imgui_dx11[1] = {};" >> fs_ocornut_imgui.bin.h
echo "static const uint8_t fs_ocornut_imgui_glsl[1] = {};" >> fs_ocornut_imgui.bin.h
echo "static const uint8_t fs_ocornut_imgui_pssl[1] = {};" >> fs_ocornut_imgui.bin.h

rm fs_ocornut_imgui_*
