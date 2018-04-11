# Copyright (c) 2017 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


add_spvtools_unittest(TARGET dominator_analysis_simple
    SRCS ../function_utils.h
         simple.cpp
    LIBS SPIRV-Tools-opt
)

add_spvtools_unittest(TARGET dominator_analysis_post
    SRCS ../function_utils.h
         post.cpp
    LIBS SPIRV-Tools-opt
)

add_spvtools_unittest(TARGET dominator_analysis_nested_ifs
    SRCS ../function_utils.h
         nested_ifs.cpp
    LIBS SPIRV-Tools-opt
)

add_spvtools_unittest(TARGET dominator_analysis_nested_ifs_post
    SRCS ../function_utils.h
         nested_ifs_post.cpp
    LIBS SPIRV-Tools-opt
)

add_spvtools_unittest(TARGET dominator_analysis_nested_loops
    SRCS ../function_utils.h
         nested_loops.cpp
    LIBS SPIRV-Tools-opt
)

add_spvtools_unittest(TARGET dominator_analysis_nested_loops_with_unreachables
    SRCS ../function_utils.h
         nested_loops_with_unreachables.cpp
    LIBS SPIRV-Tools-opt
)

add_spvtools_unittest(TARGET dominator_analysis_switch_case_fallthrough
    SRCS ../function_utils.h
         switch_case_fallthrough.cpp
    LIBS SPIRV-Tools-opt
)

add_spvtools_unittest(TARGET dominator_analysis_unreachable_for
    SRCS ../function_utils.h
         unreachable_for.cpp
    LIBS SPIRV-Tools-opt
)

add_spvtools_unittest(TARGET dominator_analysis_unreachable_for_post
    SRCS ../function_utils.h
         unreachable_for_post.cpp
    LIBS SPIRV-Tools-opt
)

add_spvtools_unittest(TARGET dominator_generated
    SRCS ../function_utils.h
         generated.cpp
    LIBS SPIRV-Tools-opt
)

add_spvtools_unittest(TARGET dominator_common_dominators
    SRCS common_dominators.cpp
    LIBS SPIRV-Tools-opt
)
