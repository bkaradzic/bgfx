# CMake generated Testfile for 
# Source directory: /home/bkaradzic/Private/projects/_github/SPIRV-Tools
# Build directory: /home/bkaradzic/Private/projects/_github/SPIRV-Tools/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(spirv-tools-copyrights "/usr/bin/python" "utils/check_copyright.py")
set_tests_properties(spirv-tools-copyrights PROPERTIES  WORKING_DIRECTORY "/home/bkaradzic/Private/projects/_github/SPIRV-Tools")
subdirs(external)
subdirs(source)
subdirs(tools)
subdirs(test)
subdirs(examples)
