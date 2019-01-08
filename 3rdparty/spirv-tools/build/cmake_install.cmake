# Install script for directory: /home/bkaradzic/Private/projects/_github/SPIRV-Tools

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/spirv-tools" TYPE FILE FILES
    "/home/bkaradzic/Private/projects/_github/SPIRV-Tools/include/spirv-tools/libspirv.h"
    "/home/bkaradzic/Private/projects/_github/SPIRV-Tools/include/spirv-tools/libspirv.hpp"
    "/home/bkaradzic/Private/projects/_github/SPIRV-Tools/include/spirv-tools/optimizer.hpp"
    "/home/bkaradzic/Private/projects/_github/SPIRV-Tools/include/spirv-tools/linker.hpp"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES
    "/home/bkaradzic/Private/projects/_github/SPIRV-Tools/build/SPIRV-Tools.pc"
    "/home/bkaradzic/Private/projects/_github/SPIRV-Tools/build/SPIRV-Tools-shared.pc"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/bkaradzic/Private/projects/_github/SPIRV-Tools/build/external/cmake_install.cmake")
  include("/home/bkaradzic/Private/projects/_github/SPIRV-Tools/build/source/cmake_install.cmake")
  include("/home/bkaradzic/Private/projects/_github/SPIRV-Tools/build/tools/cmake_install.cmake")
  include("/home/bkaradzic/Private/projects/_github/SPIRV-Tools/build/test/cmake_install.cmake")
  include("/home/bkaradzic/Private/projects/_github/SPIRV-Tools/build/examples/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/bkaradzic/Private/projects/_github/SPIRV-Tools/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
