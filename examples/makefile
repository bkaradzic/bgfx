#
# Copyright 2011-2021 Branimir Karadzic. All rights reserved.
# License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
#

all:
	@make -s --no-print-directory build -C 01-cubes
#embedded @make -s --no-print-directory -C 02-metaballs
	@make -s --no-print-directory build -C 03-raymarch
	@make -s --no-print-directory build -C 04-mesh
	@make -s --no-print-directory build -C 05-instancing
	@make -s --no-print-directory build -C 06-bump
	@make -s --no-print-directory build -C 07-callback
	@make -s --no-print-directory build -C 08-update
	@make -s --no-print-directory build -C 09-hdr
#embedded @make -s --no-print-directory build -C 10-font
#embedded @make -s --no-print-directory build -C 11-fontsdf
	@make -s --no-print-directory build -C 12-lod
	@make -s --no-print-directory build -C 13-stencil
	@make -s --no-print-directory build -C 14-shadowvolumes
	@make -s --no-print-directory build -C 15-shadowmaps-simple
	@make -s --no-print-directory build -C 16-shadowmaps
#embedded @make -s --no-print-directory build -C 17-drawstress
	@make -s --no-print-directory build -C 18-ibl
	@make -s --no-print-directory build -C 19-oit
#embedded @make -s --no-print-directory build -C 20-nanovg
	@make -s --no-print-directory build -C 21-deferred
#reused	@make -s --no-print-directory build -C 22-windows
	@make -s --no-print-directory build -C 23-vectordisplay
	@make -s --no-print-directory build -C 24-nbody
#reused @make -s --no-print-directory build -C 25-c99
#reused @make -s --no-print-directory build -C 26-occlusion
	@make -s --no-print-directory build -C 27-terrain
	@make -s --no-print-directory build -C 28-wireframe
#reused @make -s --no-print-directory build -C 29-debugdraw
	@make -s --no-print-directory build -C 30-picking
	@make -s --no-print-directory build -C 31-rsm
#reused	@make -s --no-print-directory build -C 32-particles
	@make -s --no-print-directory build -C 33-pom
#reused @make -s --no-print-directory build -C 34-mvs
#reused @make -s --no-print-directory build -C 35-dynamic
	@make -s --no-print-directory build -C 36-sky
#	@make -s --no-print-directory build -C 37-gpudrivenrendering
	@make -s --no-print-directory build -C 38-bloom
#	@make -s --no-print-directory build -C 39-assao
	@make -s --no-print-directory build -C 40-svt
	@make -s --no-print-directory build -C 41-tess
	@make -s --no-print-directory build -C 42-bunnylod
	@make -s --no-print-directory build -C 43-denoise
	@make -s --no-print-directory build -C 44-sss
	@make -s --no-print-directory build -C 45-bokeh

rebuild:
	@make -s --no-print-directory rebuild -C 01-cubes
#embedded @make -s --no-print-directory rebuild -C 02-metaballs
	@make -s --no-print-directory rebuild -C 03-raymarch
	@make -s --no-print-directory rebuild -C 04-mesh
	@make -s --no-print-directory rebuild -C 05-instancing
	@make -s --no-print-directory rebuild -C 06-bump
	@make -s --no-print-directory rebuild -C 07-callback
	@make -s --no-print-directory rebuild -C 08-update
	@make -s --no-print-directory rebuild -C 09-hdr
#embedded @make -s --no-print-directory rebuild -C 10-font
#embedded @make -s --no-print-directory rebuild -C 11-fontsdf
	@make -s --no-print-directory rebuild -C 12-lod
	@make -s --no-print-directory rebuild -C 13-stencil
	@make -s --no-print-directory rebuild -C 14-shadowvolumes
	@make -s --no-print-directory rebuild -C 15-shadowmaps-simple
	@make -s --no-print-directory rebuild -C 16-shadowmaps
#embedded @make -s --no-print-directory rebuild -C 17-drawstress
	@make -s --no-print-directory rebuild -C 18-ibl
	@make -s --no-print-directory rebuild -C 19-oit
#embedded @make -s --no-print-directory rebuild -C 20-nanovg
	@make -s --no-print-directory rebuild -C 21-deferred
#reused	@make -s --no-print-directory rebuild -C 22-windows
	@make -s --no-print-directory rebuild -C 23-vectordisplay
	@make -s --no-print-directory rebuild -C 24-nbody
#reused @make -s --no-print-directory rebuild -C 25-c99
#reused @make -s --no-print-directory rebuild -C 26-occlusion
	@make -s --no-print-directory rebuild -C 27-terrain
	@make -s --no-print-directory rebuild -C 28-wireframe
#reused @make -s --no-print-directory rebuild -C 29-debugdraw
	@make -s --no-print-directory rebuild -C 30-picking
	@make -s --no-print-directory rebuild -C 31-rsm
#reused	@make -s --no-print-directory rebuild -C 32-particles
	@make -s --no-print-directory rebuild -C 33-pom
#reused @make -s --no-print-directory rebuild -C 34-mvs
#reused @make -s --no-print-directory rebuild -C 35-dynamic
	@make -s --no-print-directory rebuild -C 36-sky
#	@make -s --no-print-directory rebuild -C 37-gpudrivenrendering
	@make -s --no-print-directory rebuild -C 38-bloom
#	@make -s --no-print-directory rebuild -C 39-assao
	@make -s --no-print-directory rebuild -C 40-svt
	@make -s --no-print-directory rebuild -C 41-tess
	@make -s --no-print-directory rebuild -C 42-bunnylod
	@make -s --no-print-directory rebuild -C 43-denoise
	@make -s --no-print-directory rebuild -C 44-sss
	@make -s --no-print-directory rebuild -C 45-bokeh

rebuild-embedded:
	@make -s --no-print-directory rebuild -C 02-metaballs
	@make -s --no-print-directory rebuild -C 17-drawstress
	@make -s --no-print-directory rebuild -C common/debugdraw
	@make -s --no-print-directory rebuild -C common/font
	@make -s --no-print-directory rebuild -C common/imgui
	@make -s --no-print-directory rebuild -C common/nanovg
	@make -s --no-print-directory rebuild -C common/ps
