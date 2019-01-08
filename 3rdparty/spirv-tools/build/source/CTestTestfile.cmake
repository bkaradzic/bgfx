# CMake generated Testfile for 
# Source directory: /home/bkaradzic/Private/projects/_github/SPIRV-Tools/source
# Build directory: /home/bkaradzic/Private/projects/_github/SPIRV-Tools/build/source
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(spirv-tools-symbol-exports-SPIRV-Tools "/usr/bin/python" "/home/bkaradzic/Private/projects/_github/SPIRV-Tools/utils/check_symbol_exports.py" "/home/bkaradzic/Private/projects/_github/SPIRV-Tools/build/source/libSPIRV-Tools.a")
add_test(spirv-tools-symbol-exports-SPIRV-Tools-shared "/usr/bin/python" "/home/bkaradzic/Private/projects/_github/SPIRV-Tools/utils/check_symbol_exports.py" "/home/bkaradzic/Private/projects/_github/SPIRV-Tools/build/source/libSPIRV-Tools-shared.so")
subdirs(comp)
subdirs(opt)
subdirs(link)
