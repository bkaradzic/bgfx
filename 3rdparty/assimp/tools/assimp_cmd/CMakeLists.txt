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

INCLUDE_DIRECTORIES(
  ${Assimp_SOURCE_DIR}/include
  ${Assimp_SOURCE_DIR}/code
)

LINK_DIRECTORIES( ${Assimp_BINARY_DIR} ${Assimp_BINARY_DIR}/lib )

ADD_EXECUTABLE( assimp_cmd
  assimp_cmd.rc
  CompareDump.cpp
  ImageExtractor.cpp
  Main.cpp
  Main.h
  resource.h
  WriteDumb.cpp
  Info.cpp
  Export.cpp
)

SET_PROPERTY(TARGET assimp_cmd PROPERTY DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

IF( WIN32 )
  ADD_CUSTOM_COMMAND(TARGET assimp_cmd
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:assimp> $<TARGET_FILE_DIR:assimp_cmd>
    MAIN_DEPENDENCY assimp)
ENDIF( WIN32 )

TARGET_LINK_LIBRARIES( assimp_cmd assimp ${ZLIB_LIBRARIES} )
SET_TARGET_PROPERTIES( assimp_cmd PROPERTIES
  OUTPUT_NAME assimp
)

INSTALL( TARGETS assimp_cmd
  DESTINATION "${ASSIMP_BIN_INSTALL_DIR}" COMPONENT assimp-bin
)
