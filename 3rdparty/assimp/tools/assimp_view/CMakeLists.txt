# Open Asset Import Library (assimp)
# ----------------------------------------------------------------------
# 
# Copyright (c) 2006-2017, assimp team

# All rights reserved.
#
# Redistribution and use of this software in source and binary forms,
# with or without modification, are permitted provided that the
# following conditions are met:
#
# * Redistributions of source code must retain the above
#   copyright notice, this list of conditions and the
#   following disclaimer.
#
# * Redistributions in binary form must reproduce the above
#   copyright notice, this list of conditions and the
#   following disclaimer in the documentation and/or other
#   materials provided with the distribution.
#
# * Neither the name of the assimp team, nor the names of its
#   contributors may be used to endorse or promote products
#   derived from this software without specific prior
#   written permission of the assimp team.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#----------------------------------------------------------------------
cmake_minimum_required( VERSION 2.6 )

FIND_PACKAGE(DirectX REQUIRED)

INCLUDE_DIRECTORIES (
  ${Assimp_SOURCE_DIR}/include
  ${Assimp_SOURCE_DIR}/code
  ${DirectX_INCLUDE_DIR}
)

# Make sure the linker can find the Assimp library once it is built.
LINK_DIRECTORIES (${Assimp_BINARY_DIR} ${AssetImporter_BINARY_DIR}/lib)

ADD_EXECUTABLE(  assimp_viewer WIN32
  AnimEvaluator.cpp
  Background.cpp
  Display.cpp
  HelpDialog.cpp
  Input.cpp
  LogDisplay.cpp
  LogWindow.cpp
  Material.cpp
  MeshRenderer.cpp
  MessageProc.cpp
  Normals.cpp
  SceneAnimator.cpp
  Shaders.cpp
  assimp_view.h
  assimp_view.cpp
  stdafx.cpp
  assimp_view.rc
  banner.bmp
  banner_pure.bmp
  base_anim.bmp
  base_display.bmp
  base_inter.bmp
  base_rendering.bmp
  base_stats.bmp
  fx.bmp
  n.bmp
  root.bmp
  tx.bmp
  txi.bmp
)

SET_PROPERTY(TARGET assimp_viewer PROPERTY DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})


IF ( MSVC )
  ADD_DEFINITIONS( -D_SCL_SECURE_NO_WARNINGS )
  ADD_DEFINITIONS( -D_CRT_SECURE_NO_WARNINGS )
ENDIF ( MSVC )


#
ADD_CUSTOM_COMMAND(TARGET assimp_viewer
  PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:assimp> $<TARGET_FILE_DIR:assimp_viewer>
  MAIN_DEPENDENCY assimp)

# Link the executable to the assimp + dx libs.
TARGET_LINK_LIBRARIES ( assimp_viewer assimp ${DirectX_LIBRARY} ${DirectX_D3DX9_LIBRARY} comctl32.lib winmm.lib )

INSTALL( TARGETS assimp_viewer
  DESTINATION "${ASSIMP_BIN_INSTALL_DIR}" COMPONENT assimp-dev
)
