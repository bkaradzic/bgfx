# CMake generated Testfile for 
# Source directory: /home/bkaradzic/Private/projects/_github/glslang
# Build directory: /home/bkaradzic/Private/projects/_github/glslang/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(glslang-testsuite "bash" "runtests" "/home/bkaradzic/Private/projects/_github/glslang/build/localResults" "/home/bkaradzic/Private/projects/_github/glslang/build/StandAlone/glslangValidator" "/home/bkaradzic/Private/projects/_github/glslang/build/StandAlone/spirv-remap")
set_tests_properties(glslang-testsuite PROPERTIES  WORKING_DIRECTORY "/home/bkaradzic/Private/projects/_github/glslang/Test/")
subdirs("External")
subdirs("glslang")
subdirs("OGLCompilersDLL")
subdirs("StandAlone")
subdirs("SPIRV")
subdirs("hlsl")
subdirs("gtests")
