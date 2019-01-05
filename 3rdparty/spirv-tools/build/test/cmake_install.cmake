# Install script for directory: /home/bkaradzic/Private/projects/_github/SPIRV-Tools/test

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/bkaradzic/Private/projects/_github/SPIRV-Tools/build/test/comp/cmake_install.cmake")
  include("/home/bkaradzic/Private/projects/_github/SPIRV-Tools/build/test/link/cmake_install.cmake")
  include("/home/bkaradzic/Private/projects/_github/SPIRV-Tools/build/test/opt/cmake_install.cmake")
  include("/home/bkaradzic/Private/projects/_github/SPIRV-Tools/build/test/stats/cmake_install.cmake")
  include("/home/bkaradzic/Private/projects/_github/SPIRV-Tools/build/test/tools/cmake_install.cmake")
  include("/home/bkaradzic/Private/projects/_github/SPIRV-Tools/build/test/util/cmake_install.cmake")
  include("/home/bkaradzic/Private/projects/_github/SPIRV-Tools/build/test/val/cmake_install.cmake")

endif()

