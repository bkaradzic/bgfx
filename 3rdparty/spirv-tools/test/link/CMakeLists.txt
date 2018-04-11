# Copyright (c) 2017 Pierre Moreau
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

add_spvtools_unittest(TARGET link_binary_version
  SRCS binary_version_test.cpp
  LIBS SPIRV-Tools-opt SPIRV-Tools-link
)

add_spvtools_unittest(TARGET link_memory_model
  SRCS memory_model_test.cpp
  LIBS SPIRV-Tools-opt SPIRV-Tools-link
)

add_spvtools_unittest(TARGET link_entry_points
  SRCS entry_points_test.cpp
  LIBS SPIRV-Tools-opt SPIRV-Tools-link
)

add_spvtools_unittest(TARGET link_global_values_amount
  SRCS global_values_amount_test.cpp
  LIBS SPIRV-Tools-opt SPIRV-Tools-link
)

add_spvtools_unittest(TARGET link_ids_limit
  SRCS ids_limit_test.cpp
  LIBS SPIRV-Tools-opt SPIRV-Tools-link
)

add_spvtools_unittest(TARGET link_matching_imports_to_exports
  SRCS matching_imports_to_exports_test.cpp
  LIBS SPIRV-Tools-opt SPIRV-Tools-link
)

add_spvtools_unittest(TARGET link_unique_ids
  SRCS unique_ids_test.cpp
  LIBS SPIRV-Tools-opt SPIRV-Tools-link
)

add_spvtools_unittest(TARGET link_partial_linkage
  SRCS partial_linkage_test.cpp
  LIBS SPIRV-Tools-opt SPIRV-Tools-link
)
