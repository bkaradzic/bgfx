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


add_spvtools_unittest(TARGET loop_descriptor_simple
    SRCS ../function_utils.h
        loop_descriptions.cpp
    LIBS SPIRV-Tools-opt
)

add_spvtools_unittest(TARGET loop_descriptor_nested
    SRCS ../function_utils.h
        nested_loops.cpp
    LIBS SPIRV-Tools-opt
)

add_spvtools_unittest(TARGET lcssa_test
    SRCS ../function_utils.h
        lcssa.cpp
    LIBS SPIRV-Tools-opt
)

add_spvtools_unittest(TARGET licm_all_loop_types
    SRCS ../function_utils.h
        hoist_all_loop_types.cpp
    LIBS SPIRV-Tools-opt
)

add_spvtools_unittest(TARGET licm_hoist_independent_loops
    SRCS ../function_utils.h
        hoist_from_independent_loops.cpp
    LIBS SPIRV-Tools-opt
)

add_spvtools_unittest(TARGET licm_hoist_double_nested_loops
    SRCS ../function_utils.h
        hoist_double_nested_loops.cpp
    LIBS SPIRV-Tools-opt
)

add_spvtools_unittest(TARGET licm_hoist_single_nested_loops
    SRCS ../function_utils.h
        hoist_single_nested_loops.cpp
    LIBS SPIRV-Tools-opt
)

add_spvtools_unittest(TARGET licm_hoist_simple_case
    SRCS ../function_utils.h
        hoist_simple_case.cpp
    LIBS SPIRV-Tools-opt
)

add_spvtools_unittest(TARGET licm_hoist_no_preheader
    SRCS ../function_utils.h
        hoist_without_preheader.cpp
    LIBS SPIRV-Tools-opt
)

add_spvtools_unittest(TARGET loop_unroll_simple
    SRCS ../function_utils.h
        unroll_simple.cpp
    LIBS SPIRV-Tools-opt
)

add_spvtools_unittest(TARGET loop_unroll_assumtion_checks
    SRCS ../function_utils.h
        unroll_assumptions.cpp
    LIBS SPIRV-Tools-opt
)

add_spvtools_unittest(TARGET unswitch_test
    SRCS ../function_utils.h
        unswitch.cpp
    LIBS SPIRV-Tools-opt
)

add_spvtools_unittest(TARGET peeling_test
    SRCS ../function_utils.h
        peeling.cpp
    LIBS SPIRV-Tools-opt
)
