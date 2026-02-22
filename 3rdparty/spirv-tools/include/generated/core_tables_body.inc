// Returns the name of an extension, as an index into kStrings
IndexRange ExtensionToIndexRange(Extension extension) {
  switch(extension) {
    case Extension::kSPV_ALTERA_arbitrary_precision_fixed_point: return IR(0, 43);
    case Extension::kSPV_ALTERA_arbitrary_precision_floating_point: return IR(43, 46);
    case Extension::kSPV_ALTERA_arbitrary_precision_integers: return IR(89, 40);
    case Extension::kSPV_ALTERA_blocking_pipes: return IR(129, 26);
    case Extension::kSPV_ALTERA_fpga_argument_interfaces: return IR(155, 36);
    case Extension::kSPV_ALTERA_fpga_buffer_location: return IR(191, 32);
    case Extension::kSPV_ALTERA_fpga_cluster_attributes: return IR(223, 35);
    case Extension::kSPV_ALTERA_fpga_dsp_control: return IR(258, 28);
    case Extension::kSPV_ALTERA_fpga_invocation_pipelining_attributes: return IR(286, 49);
    case Extension::kSPV_ALTERA_fpga_latency_control: return IR(335, 32);
    case Extension::kSPV_ALTERA_fpga_loop_controls: return IR(367, 30);
    case Extension::kSPV_ALTERA_fpga_memory_accesses: return IR(397, 32);
    case Extension::kSPV_ALTERA_fpga_memory_attributes: return IR(429, 34);
    case Extension::kSPV_ALTERA_fpga_reg: return IR(463, 20);
    case Extension::kSPV_ALTERA_global_variable_fpga_decorations: return IR(483, 44);
    case Extension::kSPV_ALTERA_io_pipes: return IR(527, 20);
    case Extension::kSPV_ALTERA_loop_fuse: return IR(547, 21);
    case Extension::kSPV_ALTERA_runtime_aligned: return IR(568, 27);
    case Extension::kSPV_ALTERA_task_sequence: return IR(595, 25);
    case Extension::kSPV_ALTERA_usm_storage_classes: return IR(620, 31);
    case Extension::kSPV_AMDX_shader_enqueue: return IR(651, 24);
    case Extension::kSPV_AMD_gcn_shader: return IR(675, 19);
    case Extension::kSPV_AMD_gpu_shader_half_float: return IR(694, 30);
    case Extension::kSPV_AMD_gpu_shader_half_float_fetch: return IR(724, 36);
    case Extension::kSPV_AMD_gpu_shader_int16: return IR(760, 25);
    case Extension::kSPV_AMD_shader_ballot: return IR(785, 22);
    case Extension::kSPV_AMD_shader_early_and_late_fragment_tests: return IR(807, 45);
    case Extension::kSPV_AMD_shader_explicit_vertex_parameter: return IR(852, 41);
    case Extension::kSPV_AMD_shader_fragment_mask: return IR(893, 29);
    case Extension::kSPV_AMD_shader_image_load_store_lod: return IR(922, 36);
    case Extension::kSPV_AMD_shader_trinary_minmax: return IR(958, 30);
    case Extension::kSPV_AMD_texture_gather_bias_lod: return IR(988, 32);
    case Extension::kSPV_ARM_cooperative_matrix_layouts: return IR(1020, 35);
    case Extension::kSPV_ARM_core_builtins: return IR(1055, 22);
    case Extension::kSPV_ARM_graph: return IR(1077, 14);
    case Extension::kSPV_ARM_tensors: return IR(1091, 16);
    case Extension::kSPV_EXT_arithmetic_fence: return IR(1107, 25);
    case Extension::kSPV_EXT_demote_to_helper_invocation: return IR(1132, 36);
    case Extension::kSPV_EXT_descriptor_heap: return IR(1168, 24);
    case Extension::kSPV_EXT_descriptor_indexing: return IR(1192, 28);
    case Extension::kSPV_EXT_float8: return IR(1220, 15);
    case Extension::kSPV_EXT_fragment_fully_covered: return IR(1235, 31);
    case Extension::kSPV_EXT_fragment_invocation_density: return IR(1266, 36);
    case Extension::kSPV_EXT_fragment_shader_interlock: return IR(1302, 34);
    case Extension::kSPV_EXT_long_vector: return IR(1336, 20);
    case Extension::kSPV_EXT_mesh_shader: return IR(1356, 20);
    case Extension::kSPV_EXT_opacity_micromap: return IR(1376, 25);
    case Extension::kSPV_EXT_optnone: return IR(1401, 16);
    case Extension::kSPV_EXT_physical_storage_buffer: return IR(1417, 32);
    case Extension::kSPV_EXT_relaxed_printf_string_address_space: return IR(1449, 44);
    case Extension::kSPV_EXT_replicated_composites: return IR(1493, 30);
    case Extension::kSPV_EXT_shader_64bit_indexing: return IR(1523, 30);
    case Extension::kSPV_EXT_shader_atomic_float16_add: return IR(1553, 34);
    case Extension::kSPV_EXT_shader_atomic_float_add: return IR(1587, 32);
    case Extension::kSPV_EXT_shader_atomic_float_min_max: return IR(1619, 36);
    case Extension::kSPV_EXT_shader_image_int64: return IR(1655, 27);
    case Extension::kSPV_EXT_shader_invocation_reorder: return IR(1682, 34);
    case Extension::kSPV_EXT_shader_stencil_export: return IR(1716, 30);
    case Extension::kSPV_EXT_shader_subgroup_partitioned: return IR(1746, 36);
    case Extension::kSPV_EXT_shader_tile_image: return IR(1782, 26);
    case Extension::kSPV_EXT_shader_viewport_index_layer: return IR(1808, 36);
    case Extension::kSPV_GOOGLE_decorate_string: return IR(1844, 27);
    case Extension::kSPV_GOOGLE_hlsl_functionality1: return IR(1871, 31);
    case Extension::kSPV_GOOGLE_user_type: return IR(1902, 21);
    case Extension::kSPV_INTEL_2d_block_io: return IR(1923, 22);
    case Extension::kSPV_INTEL_arbitrary_precision_fixed_point: return IR(1945, 42);
    case Extension::kSPV_INTEL_arbitrary_precision_floating_point: return IR(1987, 45);
    case Extension::kSPV_INTEL_arbitrary_precision_integers: return IR(2032, 39);
    case Extension::kSPV_INTEL_bfloat16_conversion: return IR(2071, 30);
    case Extension::kSPV_INTEL_bindless_images: return IR(2101, 26);
    case Extension::kSPV_INTEL_blocking_pipes: return IR(2127, 25);
    case Extension::kSPV_INTEL_cache_controls: return IR(2152, 25);
    case Extension::kSPV_INTEL_debug_module: return IR(2177, 23);
    case Extension::kSPV_INTEL_device_side_avc_motion_estimation: return IR(2200, 44);
    case Extension::kSPV_INTEL_float_controls2: return IR(2244, 26);
    case Extension::kSPV_INTEL_fp_fast_math_mode: return IR(2270, 28);
    case Extension::kSPV_INTEL_fp_max_error: return IR(2298, 23);
    case Extension::kSPV_INTEL_fpga_argument_interfaces: return IR(2321, 35);
    case Extension::kSPV_INTEL_fpga_buffer_location: return IR(2356, 31);
    case Extension::kSPV_INTEL_fpga_cluster_attributes: return IR(2387, 34);
    case Extension::kSPV_INTEL_fpga_dsp_control: return IR(2421, 27);
    case Extension::kSPV_INTEL_fpga_invocation_pipelining_attributes: return IR(2448, 48);
    case Extension::kSPV_INTEL_fpga_latency_control: return IR(2496, 31);
    case Extension::kSPV_INTEL_fpga_loop_controls: return IR(2527, 29);
    case Extension::kSPV_INTEL_fpga_memory_accesses: return IR(2556, 31);
    case Extension::kSPV_INTEL_fpga_memory_attributes: return IR(2587, 33);
    case Extension::kSPV_INTEL_fpga_reg: return IR(2620, 19);
    case Extension::kSPV_INTEL_function_pointers: return IR(2639, 28);
    case Extension::kSPV_INTEL_function_variants: return IR(2667, 28);
    case Extension::kSPV_INTEL_global_variable_fpga_decorations: return IR(2695, 43);
    case Extension::kSPV_INTEL_global_variable_host_access: return IR(2738, 38);
    case Extension::kSPV_INTEL_inline_assembly: return IR(2776, 26);
    case Extension::kSPV_INTEL_int4: return IR(2802, 15);
    case Extension::kSPV_INTEL_io_pipes: return IR(2817, 19);
    case Extension::kSPV_INTEL_kernel_attributes: return IR(2836, 28);
    case Extension::kSPV_INTEL_long_composites: return IR(2864, 26);
    case Extension::kSPV_INTEL_loop_fuse: return IR(2890, 20);
    case Extension::kSPV_INTEL_masked_gather_scatter: return IR(2910, 32);
    case Extension::kSPV_INTEL_maximum_registers: return IR(2942, 28);
    case Extension::kSPV_INTEL_media_block_io: return IR(2970, 25);
    case Extension::kSPV_INTEL_memory_access_aliasing: return IR(2995, 33);
    case Extension::kSPV_INTEL_optnone: return IR(3028, 18);
    case Extension::kSPV_INTEL_runtime_aligned: return IR(3046, 26);
    case Extension::kSPV_INTEL_shader_integer_functions2: return IR(3072, 36);
    case Extension::kSPV_INTEL_split_barrier: return IR(3108, 24);
    case Extension::kSPV_INTEL_subgroup_buffer_prefetch: return IR(3132, 35);
    case Extension::kSPV_INTEL_subgroup_matrix_multiply_accumulate: return IR(3167, 46);
    case Extension::kSPV_INTEL_subgroups: return IR(3213, 20);
    case Extension::kSPV_INTEL_task_sequence: return IR(3233, 24);
    case Extension::kSPV_INTEL_tensor_float32_conversion: return IR(3257, 36);
    case Extension::kSPV_INTEL_ternary_bitwise_function: return IR(3293, 35);
    case Extension::kSPV_INTEL_unstructured_loop_controls: return IR(3328, 37);
    case Extension::kSPV_INTEL_usm_storage_classes: return IR(3365, 30);
    case Extension::kSPV_INTEL_variable_length_array: return IR(3395, 32);
    case Extension::kSPV_INTEL_vector_compute: return IR(3427, 25);
    case Extension::kSPV_KHR_16bit_storage: return IR(3452, 22);
    case Extension::kSPV_KHR_8bit_storage: return IR(3474, 21);
    case Extension::kSPV_KHR_bfloat16: return IR(3495, 17);
    case Extension::kSPV_KHR_bit_instructions: return IR(3512, 25);
    case Extension::kSPV_KHR_compute_shader_derivatives: return IR(3537, 35);
    case Extension::kSPV_KHR_cooperative_matrix: return IR(3572, 27);
    case Extension::kSPV_KHR_device_group: return IR(3599, 21);
    case Extension::kSPV_KHR_expect_assume: return IR(3620, 22);
    case Extension::kSPV_KHR_float_controls: return IR(3642, 23);
    case Extension::kSPV_KHR_float_controls2: return IR(3665, 24);
    case Extension::kSPV_KHR_fma: return IR(3689, 12);
    case Extension::kSPV_KHR_fragment_shader_barycentric: return IR(3701, 36);
    case Extension::kSPV_KHR_fragment_shading_rate: return IR(3737, 30);
    case Extension::kSPV_KHR_integer_dot_product: return IR(3767, 28);
    case Extension::kSPV_KHR_linkonce_odr: return IR(3795, 21);
    case Extension::kSPV_KHR_maximal_reconvergence: return IR(3816, 30);
    case Extension::kSPV_KHR_multiview: return IR(3846, 18);
    case Extension::kSPV_KHR_no_integer_wrap_decoration: return IR(3864, 35);
    case Extension::kSPV_KHR_non_semantic_info: return IR(3899, 26);
    case Extension::kSPV_KHR_physical_storage_buffer: return IR(3925, 32);
    case Extension::kSPV_KHR_post_depth_coverage: return IR(3957, 28);
    case Extension::kSPV_KHR_quad_control: return IR(3985, 21);
    case Extension::kSPV_KHR_ray_cull_mask: return IR(4006, 22);
    case Extension::kSPV_KHR_ray_query: return IR(4028, 18);
    case Extension::kSPV_KHR_ray_tracing: return IR(4046, 20);
    case Extension::kSPV_KHR_ray_tracing_position_fetch: return IR(4066, 35);
    case Extension::kSPV_KHR_relaxed_extended_instruction: return IR(4101, 37);
    case Extension::kSPV_KHR_shader_atomic_counter_ops: return IR(4138, 34);
    case Extension::kSPV_KHR_shader_ballot: return IR(4172, 22);
    case Extension::kSPV_KHR_shader_clock: return IR(4194, 21);
    case Extension::kSPV_KHR_shader_draw_parameters: return IR(4215, 31);
    case Extension::kSPV_KHR_storage_buffer_storage_class: return IR(4246, 37);
    case Extension::kSPV_KHR_subgroup_rotate: return IR(4283, 24);
    case Extension::kSPV_KHR_subgroup_uniform_control_flow: return IR(4307, 38);
    case Extension::kSPV_KHR_subgroup_vote: return IR(4345, 22);
    case Extension::kSPV_KHR_terminate_invocation: return IR(4367, 29);
    case Extension::kSPV_KHR_uniform_group_instructions: return IR(4396, 35);
    case Extension::kSPV_KHR_untyped_pointers: return IR(4431, 25);
    case Extension::kSPV_KHR_variable_pointers: return IR(4456, 26);
    case Extension::kSPV_KHR_vulkan_memory_model: return IR(4482, 28);
    case Extension::kSPV_KHR_workgroup_memory_explicit_layout: return IR(4510, 41);
    case Extension::kSPV_NVX_multiview_per_view_attributes: return IR(4551, 38);
    case Extension::kSPV_NV_bindless_texture: return IR(4589, 24);
    case Extension::kSPV_NV_cluster_acceleration_structure: return IR(4613, 38);
    case Extension::kSPV_NV_compute_shader_derivatives: return IR(4651, 34);
    case Extension::kSPV_NV_cooperative_matrix: return IR(4685, 26);
    case Extension::kSPV_NV_cooperative_matrix2: return IR(4711, 27);
    case Extension::kSPV_NV_cooperative_vector: return IR(4738, 26);
    case Extension::kSPV_NV_displacement_micromap: return IR(4764, 29);
    case Extension::kSPV_NV_fragment_shader_barycentric: return IR(4793, 35);
    case Extension::kSPV_NV_geometry_shader_passthrough: return IR(4828, 35);
    case Extension::kSPV_NV_linear_swept_spheres: return IR(4863, 28);
    case Extension::kSPV_NV_mesh_shader: return IR(4891, 19);
    case Extension::kSPV_NV_push_constant_bank: return IR(4910, 26);
    case Extension::kSPV_NV_raw_access_chains: return IR(4936, 25);
    case Extension::kSPV_NV_ray_tracing: return IR(4961, 19);
    case Extension::kSPV_NV_ray_tracing_motion_blur: return IR(4980, 31);
    case Extension::kSPV_NV_sample_mask_override_coverage: return IR(5011, 37);
    case Extension::kSPV_NV_shader_atomic_fp16_vector: return IR(5048, 33);
    case Extension::kSPV_NV_shader_image_footprint: return IR(5081, 30);
    case Extension::kSPV_NV_shader_invocation_reorder: return IR(5111, 33);
    case Extension::kSPV_NV_shader_sm_builtins: return IR(5144, 26);
    case Extension::kSPV_NV_shader_subgroup_partitioned: return IR(5170, 35);
    case Extension::kSPV_NV_shading_rate: return IR(5205, 20);
    case Extension::kSPV_NV_stereo_view_rendering: return IR(5225, 29);
    case Extension::kSPV_NV_tensor_addressing: return IR(5254, 25);
    case Extension::kSPV_NV_viewport_array2: return IR(5279, 23);
    case Extension::kSPV_QCOM_cooperative_matrix_conversion: return IR(5302, 39);
    case Extension::kSPV_QCOM_image_processing: return IR(5341, 26);
    case Extension::kSPV_QCOM_image_processing2: return IR(5367, 27);
    case Extension::kSPV_QCOM_tile_shading: return IR(5394, 22);
    case Extension::kSPV_VALIDATOR_ignore_type_decl_unique: return IR(5416, 38);
    case Extension::kSPV_VALVE_mixed_float_dot_product: return IR(5454, 34);
    default: break;
  }
  return {};
}

// Extension names and values, ordered by name
// The fields in order are:
//   name, indexing into kStrings
//   enum value
static const std::array<NameValue,188> kExtensionNames{{
    {IR(0, 43), static_cast<uint32_t>(kSPV_ALTERA_arbitrary_precision_fixed_point)},
    {IR(43, 46), static_cast<uint32_t>(kSPV_ALTERA_arbitrary_precision_floating_point)},
    {IR(89, 40), static_cast<uint32_t>(kSPV_ALTERA_arbitrary_precision_integers)},
    {IR(129, 26), static_cast<uint32_t>(kSPV_ALTERA_blocking_pipes)},
    {IR(155, 36), static_cast<uint32_t>(kSPV_ALTERA_fpga_argument_interfaces)},
    {IR(191, 32), static_cast<uint32_t>(kSPV_ALTERA_fpga_buffer_location)},
    {IR(223, 35), static_cast<uint32_t>(kSPV_ALTERA_fpga_cluster_attributes)},
    {IR(258, 28), static_cast<uint32_t>(kSPV_ALTERA_fpga_dsp_control)},
    {IR(286, 49), static_cast<uint32_t>(kSPV_ALTERA_fpga_invocation_pipelining_attributes)},
    {IR(335, 32), static_cast<uint32_t>(kSPV_ALTERA_fpga_latency_control)},
    {IR(367, 30), static_cast<uint32_t>(kSPV_ALTERA_fpga_loop_controls)},
    {IR(397, 32), static_cast<uint32_t>(kSPV_ALTERA_fpga_memory_accesses)},
    {IR(429, 34), static_cast<uint32_t>(kSPV_ALTERA_fpga_memory_attributes)},
    {IR(463, 20), static_cast<uint32_t>(kSPV_ALTERA_fpga_reg)},
    {IR(483, 44), static_cast<uint32_t>(kSPV_ALTERA_global_variable_fpga_decorations)},
    {IR(527, 20), static_cast<uint32_t>(kSPV_ALTERA_io_pipes)},
    {IR(547, 21), static_cast<uint32_t>(kSPV_ALTERA_loop_fuse)},
    {IR(568, 27), static_cast<uint32_t>(kSPV_ALTERA_runtime_aligned)},
    {IR(595, 25), static_cast<uint32_t>(kSPV_ALTERA_task_sequence)},
    {IR(620, 31), static_cast<uint32_t>(kSPV_ALTERA_usm_storage_classes)},
    {IR(651, 24), static_cast<uint32_t>(kSPV_AMDX_shader_enqueue)},
    {IR(675, 19), static_cast<uint32_t>(kSPV_AMD_gcn_shader)},
    {IR(694, 30), static_cast<uint32_t>(kSPV_AMD_gpu_shader_half_float)},
    {IR(724, 36), static_cast<uint32_t>(kSPV_AMD_gpu_shader_half_float_fetch)},
    {IR(760, 25), static_cast<uint32_t>(kSPV_AMD_gpu_shader_int16)},
    {IR(785, 22), static_cast<uint32_t>(kSPV_AMD_shader_ballot)},
    {IR(807, 45), static_cast<uint32_t>(kSPV_AMD_shader_early_and_late_fragment_tests)},
    {IR(852, 41), static_cast<uint32_t>(kSPV_AMD_shader_explicit_vertex_parameter)},
    {IR(893, 29), static_cast<uint32_t>(kSPV_AMD_shader_fragment_mask)},
    {IR(922, 36), static_cast<uint32_t>(kSPV_AMD_shader_image_load_store_lod)},
    {IR(958, 30), static_cast<uint32_t>(kSPV_AMD_shader_trinary_minmax)},
    {IR(988, 32), static_cast<uint32_t>(kSPV_AMD_texture_gather_bias_lod)},
    {IR(1020, 35), static_cast<uint32_t>(kSPV_ARM_cooperative_matrix_layouts)},
    {IR(1055, 22), static_cast<uint32_t>(kSPV_ARM_core_builtins)},
    {IR(1077, 14), static_cast<uint32_t>(kSPV_ARM_graph)},
    {IR(1091, 16), static_cast<uint32_t>(kSPV_ARM_tensors)},
    {IR(1107, 25), static_cast<uint32_t>(kSPV_EXT_arithmetic_fence)},
    {IR(1132, 36), static_cast<uint32_t>(kSPV_EXT_demote_to_helper_invocation)},
    {IR(1168, 24), static_cast<uint32_t>(kSPV_EXT_descriptor_heap)},
    {IR(1192, 28), static_cast<uint32_t>(kSPV_EXT_descriptor_indexing)},
    {IR(1220, 15), static_cast<uint32_t>(kSPV_EXT_float8)},
    {IR(1235, 31), static_cast<uint32_t>(kSPV_EXT_fragment_fully_covered)},
    {IR(1266, 36), static_cast<uint32_t>(kSPV_EXT_fragment_invocation_density)},
    {IR(1302, 34), static_cast<uint32_t>(kSPV_EXT_fragment_shader_interlock)},
    {IR(1336, 20), static_cast<uint32_t>(kSPV_EXT_long_vector)},
    {IR(1356, 20), static_cast<uint32_t>(kSPV_EXT_mesh_shader)},
    {IR(1376, 25), static_cast<uint32_t>(kSPV_EXT_opacity_micromap)},
    {IR(1401, 16), static_cast<uint32_t>(kSPV_EXT_optnone)},
    {IR(1417, 32), static_cast<uint32_t>(kSPV_EXT_physical_storage_buffer)},
    {IR(1449, 44), static_cast<uint32_t>(kSPV_EXT_relaxed_printf_string_address_space)},
    {IR(1493, 30), static_cast<uint32_t>(kSPV_EXT_replicated_composites)},
    {IR(1523, 30), static_cast<uint32_t>(kSPV_EXT_shader_64bit_indexing)},
    {IR(1553, 34), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float16_add)},
    {IR(1587, 32), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float_add)},
    {IR(1619, 36), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float_min_max)},
    {IR(1655, 27), static_cast<uint32_t>(kSPV_EXT_shader_image_int64)},
    {IR(1682, 34), static_cast<uint32_t>(kSPV_EXT_shader_invocation_reorder)},
    {IR(1716, 30), static_cast<uint32_t>(kSPV_EXT_shader_stencil_export)},
    {IR(1746, 36), static_cast<uint32_t>(kSPV_EXT_shader_subgroup_partitioned)},
    {IR(1782, 26), static_cast<uint32_t>(kSPV_EXT_shader_tile_image)},
    {IR(1808, 36), static_cast<uint32_t>(kSPV_EXT_shader_viewport_index_layer)},
    {IR(1844, 27), static_cast<uint32_t>(kSPV_GOOGLE_decorate_string)},
    {IR(1871, 31), static_cast<uint32_t>(kSPV_GOOGLE_hlsl_functionality1)},
    {IR(1902, 21), static_cast<uint32_t>(kSPV_GOOGLE_user_type)},
    {IR(1923, 22), static_cast<uint32_t>(kSPV_INTEL_2d_block_io)},
    {IR(1945, 42), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_fixed_point)},
    {IR(1987, 45), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_floating_point)},
    {IR(2032, 39), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_integers)},
    {IR(2071, 30), static_cast<uint32_t>(kSPV_INTEL_bfloat16_conversion)},
    {IR(2101, 26), static_cast<uint32_t>(kSPV_INTEL_bindless_images)},
    {IR(2127, 25), static_cast<uint32_t>(kSPV_INTEL_blocking_pipes)},
    {IR(2152, 25), static_cast<uint32_t>(kSPV_INTEL_cache_controls)},
    {IR(2177, 23), static_cast<uint32_t>(kSPV_INTEL_debug_module)},
    {IR(2200, 44), static_cast<uint32_t>(kSPV_INTEL_device_side_avc_motion_estimation)},
    {IR(2244, 26), static_cast<uint32_t>(kSPV_INTEL_float_controls2)},
    {IR(2270, 28), static_cast<uint32_t>(kSPV_INTEL_fp_fast_math_mode)},
    {IR(2298, 23), static_cast<uint32_t>(kSPV_INTEL_fp_max_error)},
    {IR(2321, 35), static_cast<uint32_t>(kSPV_INTEL_fpga_argument_interfaces)},
    {IR(2356, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_buffer_location)},
    {IR(2387, 34), static_cast<uint32_t>(kSPV_INTEL_fpga_cluster_attributes)},
    {IR(2421, 27), static_cast<uint32_t>(kSPV_INTEL_fpga_dsp_control)},
    {IR(2448, 48), static_cast<uint32_t>(kSPV_INTEL_fpga_invocation_pipelining_attributes)},
    {IR(2496, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_latency_control)},
    {IR(2527, 29), static_cast<uint32_t>(kSPV_INTEL_fpga_loop_controls)},
    {IR(2556, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_memory_accesses)},
    {IR(2587, 33), static_cast<uint32_t>(kSPV_INTEL_fpga_memory_attributes)},
    {IR(2620, 19), static_cast<uint32_t>(kSPV_INTEL_fpga_reg)},
    {IR(2639, 28), static_cast<uint32_t>(kSPV_INTEL_function_pointers)},
    {IR(2667, 28), static_cast<uint32_t>(kSPV_INTEL_function_variants)},
    {IR(2695, 43), static_cast<uint32_t>(kSPV_INTEL_global_variable_fpga_decorations)},
    {IR(2738, 38), static_cast<uint32_t>(kSPV_INTEL_global_variable_host_access)},
    {IR(2776, 26), static_cast<uint32_t>(kSPV_INTEL_inline_assembly)},
    {IR(2802, 15), static_cast<uint32_t>(kSPV_INTEL_int4)},
    {IR(2817, 19), static_cast<uint32_t>(kSPV_INTEL_io_pipes)},
    {IR(2836, 28), static_cast<uint32_t>(kSPV_INTEL_kernel_attributes)},
    {IR(2864, 26), static_cast<uint32_t>(kSPV_INTEL_long_composites)},
    {IR(2890, 20), static_cast<uint32_t>(kSPV_INTEL_loop_fuse)},
    {IR(2910, 32), static_cast<uint32_t>(kSPV_INTEL_masked_gather_scatter)},
    {IR(2942, 28), static_cast<uint32_t>(kSPV_INTEL_maximum_registers)},
    {IR(2970, 25), static_cast<uint32_t>(kSPV_INTEL_media_block_io)},
    {IR(2995, 33), static_cast<uint32_t>(kSPV_INTEL_memory_access_aliasing)},
    {IR(3028, 18), static_cast<uint32_t>(kSPV_INTEL_optnone)},
    {IR(3046, 26), static_cast<uint32_t>(kSPV_INTEL_runtime_aligned)},
    {IR(3072, 36), static_cast<uint32_t>(kSPV_INTEL_shader_integer_functions2)},
    {IR(3108, 24), static_cast<uint32_t>(kSPV_INTEL_split_barrier)},
    {IR(3132, 35), static_cast<uint32_t>(kSPV_INTEL_subgroup_buffer_prefetch)},
    {IR(3167, 46), static_cast<uint32_t>(kSPV_INTEL_subgroup_matrix_multiply_accumulate)},
    {IR(3213, 20), static_cast<uint32_t>(kSPV_INTEL_subgroups)},
    {IR(3233, 24), static_cast<uint32_t>(kSPV_INTEL_task_sequence)},
    {IR(3257, 36), static_cast<uint32_t>(kSPV_INTEL_tensor_float32_conversion)},
    {IR(3293, 35), static_cast<uint32_t>(kSPV_INTEL_ternary_bitwise_function)},
    {IR(3328, 37), static_cast<uint32_t>(kSPV_INTEL_unstructured_loop_controls)},
    {IR(3365, 30), static_cast<uint32_t>(kSPV_INTEL_usm_storage_classes)},
    {IR(3395, 32), static_cast<uint32_t>(kSPV_INTEL_variable_length_array)},
    {IR(3427, 25), static_cast<uint32_t>(kSPV_INTEL_vector_compute)},
    {IR(3452, 22), static_cast<uint32_t>(kSPV_KHR_16bit_storage)},
    {IR(3474, 21), static_cast<uint32_t>(kSPV_KHR_8bit_storage)},
    {IR(3495, 17), static_cast<uint32_t>(kSPV_KHR_bfloat16)},
    {IR(3512, 25), static_cast<uint32_t>(kSPV_KHR_bit_instructions)},
    {IR(3537, 35), static_cast<uint32_t>(kSPV_KHR_compute_shader_derivatives)},
    {IR(3572, 27), static_cast<uint32_t>(kSPV_KHR_cooperative_matrix)},
    {IR(3599, 21), static_cast<uint32_t>(kSPV_KHR_device_group)},
    {IR(3620, 22), static_cast<uint32_t>(kSPV_KHR_expect_assume)},
    {IR(3642, 23), static_cast<uint32_t>(kSPV_KHR_float_controls)},
    {IR(3665, 24), static_cast<uint32_t>(kSPV_KHR_float_controls2)},
    {IR(3689, 12), static_cast<uint32_t>(kSPV_KHR_fma)},
    {IR(3701, 36), static_cast<uint32_t>(kSPV_KHR_fragment_shader_barycentric)},
    {IR(3737, 30), static_cast<uint32_t>(kSPV_KHR_fragment_shading_rate)},
    {IR(3767, 28), static_cast<uint32_t>(kSPV_KHR_integer_dot_product)},
    {IR(3795, 21), static_cast<uint32_t>(kSPV_KHR_linkonce_odr)},
    {IR(3816, 30), static_cast<uint32_t>(kSPV_KHR_maximal_reconvergence)},
    {IR(3846, 18), static_cast<uint32_t>(kSPV_KHR_multiview)},
    {IR(3864, 35), static_cast<uint32_t>(kSPV_KHR_no_integer_wrap_decoration)},
    {IR(3899, 26), static_cast<uint32_t>(kSPV_KHR_non_semantic_info)},
    {IR(3925, 32), static_cast<uint32_t>(kSPV_KHR_physical_storage_buffer)},
    {IR(3957, 28), static_cast<uint32_t>(kSPV_KHR_post_depth_coverage)},
    {IR(3985, 21), static_cast<uint32_t>(kSPV_KHR_quad_control)},
    {IR(4006, 22), static_cast<uint32_t>(kSPV_KHR_ray_cull_mask)},
    {IR(4028, 18), static_cast<uint32_t>(kSPV_KHR_ray_query)},
    {IR(4046, 20), static_cast<uint32_t>(kSPV_KHR_ray_tracing)},
    {IR(4066, 35), static_cast<uint32_t>(kSPV_KHR_ray_tracing_position_fetch)},
    {IR(4101, 37), static_cast<uint32_t>(kSPV_KHR_relaxed_extended_instruction)},
    {IR(4138, 34), static_cast<uint32_t>(kSPV_KHR_shader_atomic_counter_ops)},
    {IR(4172, 22), static_cast<uint32_t>(kSPV_KHR_shader_ballot)},
    {IR(4194, 21), static_cast<uint32_t>(kSPV_KHR_shader_clock)},
    {IR(4215, 31), static_cast<uint32_t>(kSPV_KHR_shader_draw_parameters)},
    {IR(4246, 37), static_cast<uint32_t>(kSPV_KHR_storage_buffer_storage_class)},
    {IR(4283, 24), static_cast<uint32_t>(kSPV_KHR_subgroup_rotate)},
    {IR(4307, 38), static_cast<uint32_t>(kSPV_KHR_subgroup_uniform_control_flow)},
    {IR(4345, 22), static_cast<uint32_t>(kSPV_KHR_subgroup_vote)},
    {IR(4367, 29), static_cast<uint32_t>(kSPV_KHR_terminate_invocation)},
    {IR(4396, 35), static_cast<uint32_t>(kSPV_KHR_uniform_group_instructions)},
    {IR(4431, 25), static_cast<uint32_t>(kSPV_KHR_untyped_pointers)},
    {IR(4456, 26), static_cast<uint32_t>(kSPV_KHR_variable_pointers)},
    {IR(4482, 28), static_cast<uint32_t>(kSPV_KHR_vulkan_memory_model)},
    {IR(4510, 41), static_cast<uint32_t>(kSPV_KHR_workgroup_memory_explicit_layout)},
    {IR(4551, 38), static_cast<uint32_t>(kSPV_NVX_multiview_per_view_attributes)},
    {IR(4589, 24), static_cast<uint32_t>(kSPV_NV_bindless_texture)},
    {IR(4613, 38), static_cast<uint32_t>(kSPV_NV_cluster_acceleration_structure)},
    {IR(4651, 34), static_cast<uint32_t>(kSPV_NV_compute_shader_derivatives)},
    {IR(4685, 26), static_cast<uint32_t>(kSPV_NV_cooperative_matrix)},
    {IR(4711, 27), static_cast<uint32_t>(kSPV_NV_cooperative_matrix2)},
    {IR(4738, 26), static_cast<uint32_t>(kSPV_NV_cooperative_vector)},
    {IR(4764, 29), static_cast<uint32_t>(kSPV_NV_displacement_micromap)},
    {IR(4793, 35), static_cast<uint32_t>(kSPV_NV_fragment_shader_barycentric)},
    {IR(4828, 35), static_cast<uint32_t>(kSPV_NV_geometry_shader_passthrough)},
    {IR(4863, 28), static_cast<uint32_t>(kSPV_NV_linear_swept_spheres)},
    {IR(4891, 19), static_cast<uint32_t>(kSPV_NV_mesh_shader)},
    {IR(4910, 26), static_cast<uint32_t>(kSPV_NV_push_constant_bank)},
    {IR(4936, 25), static_cast<uint32_t>(kSPV_NV_raw_access_chains)},
    {IR(4961, 19), static_cast<uint32_t>(kSPV_NV_ray_tracing)},
    {IR(4980, 31), static_cast<uint32_t>(kSPV_NV_ray_tracing_motion_blur)},
    {IR(5011, 37), static_cast<uint32_t>(kSPV_NV_sample_mask_override_coverage)},
    {IR(5048, 33), static_cast<uint32_t>(kSPV_NV_shader_atomic_fp16_vector)},
    {IR(5081, 30), static_cast<uint32_t>(kSPV_NV_shader_image_footprint)},
    {IR(5111, 33), static_cast<uint32_t>(kSPV_NV_shader_invocation_reorder)},
    {IR(5144, 26), static_cast<uint32_t>(kSPV_NV_shader_sm_builtins)},
    {IR(5170, 35), static_cast<uint32_t>(kSPV_NV_shader_subgroup_partitioned)},
    {IR(5205, 20), static_cast<uint32_t>(kSPV_NV_shading_rate)},
    {IR(5225, 29), static_cast<uint32_t>(kSPV_NV_stereo_view_rendering)},
    {IR(5254, 25), static_cast<uint32_t>(kSPV_NV_tensor_addressing)},
    {IR(5279, 23), static_cast<uint32_t>(kSPV_NV_viewport_array2)},
    {IR(5302, 39), static_cast<uint32_t>(kSPV_QCOM_cooperative_matrix_conversion)},
    {IR(5341, 26), static_cast<uint32_t>(kSPV_QCOM_image_processing)},
    {IR(5367, 27), static_cast<uint32_t>(kSPV_QCOM_image_processing2)},
    {IR(5394, 22), static_cast<uint32_t>(kSPV_QCOM_tile_shading)},
    {IR(5416, 38), static_cast<uint32_t>(kSPV_VALIDATOR_ignore_type_decl_unique)},
    {IR(5454, 34), static_cast<uint32_t>(kSPV_VALVE_mixed_float_dot_product)},
}};

// Operand descriptions, ordered by (operand kind, operand enum value).
// The fields in order are:
//   enum value
//   operands, an IndexRange into kOperandSpans
//   name, a character-counting IndexRange into kStrings
//   aliases, an IndexRange into kAliasSpans
//   capabilities, an IndexRange into kCapabilitySpans
//   extensions, as an IndexRange into kExtensionSpans
//   version, first version of SPIR-V that has it
//   lastVersion, last version of SPIR-V that has it
static const std::array<OperandDesc, 1207> kOperandsByValue{{
  {0,IR(0, 0),IR(5488, 9)/* ReadOnly */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {1,IR(0, 0),IR(5504, 10)/* WriteOnly */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {2,IR(0, 0),IR(5514, 10)/* ReadWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {0,IR(0, 0),IR(5524, 8)/* Logical */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {1,IR(0, 0),IR(5532, 11)/* Physical32 */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {2,IR(0, 0),IR(5553, 11)/* Physical64 */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {5348,IR(0, 0),IR(5564, 24)/* PhysicalStorageBuffer64 */,IR(0, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {0,IR(0, 0),IR(5646, 9)/* Position */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {1,IR(0, 0),IR(5662, 10)/* PointSize */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {3,IR(0, 0),IR(5672, 13)/* ClipDistance */,IR(0, 0),IR(4, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4,IR(0, 0),IR(5685, 13)/* CullDistance */,IR(0, 0),IR(5, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5,IR(0, 0),IR(5698, 9)/* VertexId */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {6,IR(0, 0),IR(5707, 11)/* InstanceId */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {7,IR(0, 0),IR(5718, 12)/* PrimitiveId */,IR(0, 0),IR(6, 6),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {8,IR(0, 0),IR(5808, 13)/* InvocationId */,IR(0, 0),IR(12, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {9,IR(0, 0),IR(5821, 6)/* Layer */,IR(0, 0),IR(14, 5),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {10,IR(0, 0),IR(5867, 14)/* ViewportIndex */,IR(0, 0),IR(19, 5),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {11,IR(0, 0),IR(5915, 15)/* TessLevelOuter */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {12,IR(0, 0),IR(5930, 15)/* TessLevelInner */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {13,IR(0, 0),IR(5945, 10)/* TessCoord */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {14,IR(0, 0),IR(5955, 14)/* PatchVertices */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {15,IR(0, 0),IR(5969, 10)/* FragCoord */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {16,IR(0, 0),IR(5979, 11)/* PointCoord */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {17,IR(0, 0),IR(5990, 12)/* FrontFacing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {18,IR(0, 0),IR(6002, 9)/* SampleId */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {19,IR(0, 0),IR(6029, 15)/* SamplePosition */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {20,IR(0, 0),IR(6044, 11)/* SampleMask */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {22,IR(0, 0),IR(6055, 10)/* FragDepth */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {23,IR(0, 0),IR(6065, 17)/* HelperInvocation */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {24,IR(0, 0),IR(6082, 14)/* NumWorkgroups */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {25,IR(0, 0),IR(6096, 14)/* WorkgroupSize */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {26,IR(0, 0),IR(6110, 12)/* WorkgroupId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {27,IR(0, 0),IR(6122, 18)/* LocalInvocationId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {28,IR(0, 0),IR(6140, 19)/* GlobalInvocationId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {29,IR(0, 0),IR(6159, 21)/* LocalInvocationIndex */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {30,IR(0, 0),IR(6180, 8)/* WorkDim */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {31,IR(0, 0),IR(6188, 11)/* GlobalSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {32,IR(0, 0),IR(6199, 22)/* EnqueuedWorkgroupSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {33,IR(0, 0),IR(6221, 13)/* GlobalOffset */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {34,IR(0, 0),IR(6234, 15)/* GlobalLinearId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {36,IR(0, 0),IR(6249, 13)/* SubgroupSize */,IR(0, 0),IR(26, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {37,IR(0, 0),IR(6296, 16)/* SubgroupMaxSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {38,IR(0, 0),IR(6312, 13)/* NumSubgroups */,IR(0, 0),IR(29, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {39,IR(0, 0),IR(6325, 21)/* NumEnqueuedSubgroups */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {40,IR(0, 0),IR(6346, 11)/* SubgroupId */,IR(0, 0),IR(29, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {41,IR(0, 0),IR(6357, 26)/* SubgroupLocalInvocationId */,IR(0, 0),IR(26, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {42,IR(0, 0),IR(6383, 12)/* VertexIndex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {43,IR(0, 0),IR(6395, 14)/* InstanceIndex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4160,IR(0, 0),IR(6409, 10)/* CoreIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4161,IR(0, 0),IR(6435, 13)/* CoreCountARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4162,IR(0, 0),IR(6448, 13)/* CoreMaxIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4163,IR(0, 0),IR(6461, 10)/* WarpIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4164,IR(0, 0),IR(6471, 13)/* WarpMaxIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4416,IR(0, 0),IR(6484, 15)/* SubgroupEqMask */,IR(1, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4417,IR(0, 0),IR(6539, 15)/* SubgroupGeMask */,IR(2, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4418,IR(0, 0),IR(6572, 15)/* SubgroupGtMask */,IR(3, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4419,IR(0, 0),IR(6605, 15)/* SubgroupLeMask */,IR(4, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4420,IR(0, 0),IR(6638, 15)/* SubgroupLtMask */,IR(5, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4424,IR(0, 0),IR(6671, 11)/* BaseVertex */,IR(0, 0),IR(34, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4425,IR(0, 0),IR(6697, 13)/* BaseInstance */,IR(0, 0),IR(34, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4426,IR(0, 0),IR(6710, 10)/* DrawIndex */,IR(0, 0),IR(35, 3),IR(4, 3),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4432,IR(0, 0),IR(6720, 24)/* PrimitiveShadingRateKHR */,IR(0, 0),IR(38, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4438,IR(0, 0),IR(6767, 12)/* DeviceIndex */,IR(0, 0),IR(39, 1),IR(8, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4440,IR(0, 0),IR(6791, 10)/* ViewIndex */,IR(0, 0),IR(40, 1),IR(9, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4444,IR(0, 0),IR(6811, 15)/* ShadingRateKHR */,IR(0, 0),IR(38, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4492,IR(0, 0),IR(6826, 15)/* TileOffsetQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4493,IR(0, 0),IR(6857, 18)/* TileDimensionQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4494,IR(0, 0),IR(6875, 18)/* TileApronSizeQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4992,IR(0, 0),IR(6893, 20)/* BaryCoordNoPerspAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4993,IR(0, 0),IR(6913, 28)/* BaryCoordNoPerspCentroidAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4994,IR(0, 0),IR(6941, 26)/* BaryCoordNoPerspSampleAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4995,IR(0, 0),IR(6967, 19)/* BaryCoordSmoothAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4996,IR(0, 0),IR(6986, 27)/* BaryCoordSmoothCentroidAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4997,IR(0, 0),IR(7013, 25)/* BaryCoordSmoothSampleAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4998,IR(0, 0),IR(7038, 22)/* BaryCoordPullModelAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5014,IR(0, 0),IR(7060, 18)/* FragStencilRefEXT */,IR(0, 0),IR(42, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5021,IR(0, 0),IR(7095, 29)/* RemainingRecursionLevelsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5073,IR(0, 0),IR(7142, 16)/* ShaderIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5122,IR(0, 0),IR(7158, 15)/* SamplerHeapEXT */,IR(0, 0),IR(44, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5123,IR(0, 0),IR(7191, 16)/* ResourceHeapEXT */,IR(0, 0),IR(44, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5253,IR(0, 0),IR(7207, 15)/* ViewportMaskNV */,IR(0, 0),IR(45, 2),IR(12, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5257,IR(0, 0),IR(7243, 20)/* SecondaryPositionNV */,IR(0, 0),IR(47, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5258,IR(0, 0),IR(7282, 24)/* SecondaryViewportMaskNV */,IR(0, 0),IR(47, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5261,IR(0, 0),IR(7306, 18)/* PositionPerViewNV */,IR(0, 0),IR(48, 2),IR(15, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5262,IR(0, 0),IR(7344, 22)/* ViewportMaskPerViewNV */,IR(0, 0),IR(48, 2),IR(15, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5264,IR(0, 0),IR(7366, 16)/* FullyCoveredEXT */,IR(0, 0),IR(50, 1),IR(17, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5274,IR(0, 0),IR(7406, 12)/* TaskCountNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5275,IR(0, 0),IR(7418, 17)/* PrimitiveCountNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5276,IR(0, 0),IR(7435, 19)/* PrimitiveIndicesNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5277,IR(0, 0),IR(7454, 22)/* ClipDistancePerViewNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5278,IR(0, 0),IR(7476, 22)/* CullDistancePerViewNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5279,IR(0, 0),IR(7498, 15)/* LayerPerViewNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5280,IR(0, 0),IR(7513, 16)/* MeshViewCountNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5281,IR(0, 0),IR(7529, 18)/* MeshViewIndicesNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5286,IR(0, 0),IR(7547, 13)/* BaryCoordKHR */,IR(6, 1),IR(52, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5287,IR(0, 0),IR(7595, 20)/* BaryCoordNoPerspKHR */,IR(7, 1),IR(52, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5292,IR(0, 0),IR(7634, 12)/* FragSizeEXT */,IR(8, 1),IR(53, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5293,IR(0, 0),IR(7680, 23)/* FragInvocationCountEXT */,IR(9, 1),IR(53, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5294,IR(0, 0),IR(7725, 25)/* PrimitivePointIndicesEXT */,IR(0, 0),IR(54, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5295,IR(0, 0),IR(7750, 24)/* PrimitiveLineIndicesEXT */,IR(0, 0),IR(54, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5296,IR(0, 0),IR(7774, 28)/* PrimitiveTriangleIndicesEXT */,IR(0, 0),IR(54, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5299,IR(0, 0),IR(7802, 17)/* CullPrimitiveEXT */,IR(0, 0),IR(54, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5319,IR(0, 0),IR(7819, 12)/* LaunchIdKHR */,IR(10, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5320,IR(0, 0),IR(7842, 14)/* LaunchSizeKHR */,IR(11, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5321,IR(0, 0),IR(7869, 18)/* WorldRayOriginKHR */,IR(12, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5322,IR(0, 0),IR(7904, 21)/* WorldRayDirectionKHR */,IR(13, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5323,IR(0, 0),IR(7945, 19)/* ObjectRayOriginKHR */,IR(14, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5324,IR(0, 0),IR(7982, 22)/* ObjectRayDirectionKHR */,IR(15, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5325,IR(0, 0),IR(8025, 11)/* RayTminKHR */,IR(16, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5326,IR(0, 0),IR(8046, 11)/* RayTmaxKHR */,IR(17, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5327,IR(0, 0),IR(8067, 23)/* InstanceCustomIndexKHR */,IR(18, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5330,IR(0, 0),IR(8112, 17)/* ObjectToWorldKHR */,IR(19, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5331,IR(0, 0),IR(8145, 17)/* WorldToObjectKHR */,IR(20, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5332,IR(0, 0),IR(8178, 7)/* HitTNV */,IR(0, 0),IR(57, 1),IR(26, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5333,IR(0, 0),IR(8185, 11)/* HitKindKHR */,IR(21, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5334,IR(0, 0),IR(8206, 17)/* CurrentRayTimeNV */,IR(0, 0),IR(58, 1),IR(27, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5335,IR(0, 0),IR(8246, 30)/* HitTriangleVertexPositionsKHR */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5337,IR(0, 0),IR(8303, 34)/* HitMicroTriangleVertexPositionsNV */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5344,IR(0, 0),IR(8370, 37)/* HitMicroTriangleVertexBarycentricsNV */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5351,IR(0, 0),IR(8407, 20)/* IncomingRayFlagsKHR */,IR(22, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5352,IR(0, 0),IR(8446, 20)/* RayGeometryIndexKHR */,IR(0, 0),IR(61, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5359,IR(0, 0),IR(8466, 14)/* HitIsSphereNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5360,IR(0, 0),IR(8508, 11)/* HitIsLSSNV */,IR(0, 0),IR(63, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5361,IR(0, 0),IR(8558, 20)/* HitSpherePositionNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5374,IR(0, 0),IR(8578, 13)/* WarpsPerSMNV */,IR(0, 0),IR(64, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5375,IR(0, 0),IR(8610, 10)/* SMCountNV */,IR(0, 0),IR(64, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5376,IR(0, 0),IR(8620, 9)/* WarpIDNV */,IR(0, 0),IR(64, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5377,IR(0, 0),IR(8629, 7)/* SMIDNV */,IR(0, 0),IR(64, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5396,IR(0, 0),IR(8636, 18)/* HitLSSPositionsNV */,IR(0, 0),IR(63, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5405,IR(0, 0),IR(8654, 34)/* HitKindFrontFacingMicroTriangleNV */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5406,IR(0, 0),IR(8688, 33)/* HitKindBackFacingMicroTriangleNV */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5420,IR(0, 0),IR(8721, 18)/* HitSphereRadiusNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5421,IR(0, 0),IR(8739, 14)/* HitLSSRadiiNV */,IR(0, 0),IR(63, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5436,IR(0, 0),IR(8753, 12)/* ClusterIDNV */,IR(0, 0),IR(65, 1),IR(31, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {6021,IR(0, 0),IR(8806, 12)/* CullMaskKHR */,IR(0, 0),IR(66, 1),IR(32, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {0,IR(0, 0),IR(8833, 7)/* Matrix */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {1,IR(0, 0),IR(5655, 7)/* Shader */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {2,IR(0, 0),IR(5730, 9)/* Geometry */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {3,IR(0, 0),IR(5739, 13)/* Tessellation */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4,IR(0, 0),IR(5543, 10)/* Addresses */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5,IR(0, 0),IR(8840, 8)/* Linkage */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6,IR(0, 0),IR(5497, 7)/* Kernel */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {7,IR(0, 0),IR(8848, 9)/* Vector16 */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {8,IR(0, 0),IR(8857, 14)/* Float16Buffer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {9,IR(0, 0),IR(8871, 8)/* Float16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {10,IR(0, 0),IR(8879, 8)/* Float64 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {11,IR(0, 0),IR(8887, 6)/* Int64 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {12,IR(0, 0),IR(8893, 13)/* Int64Atomics */,IR(0, 0),IR(68, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {13,IR(0, 0),IR(8906, 11)/* ImageBasic */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {14,IR(0, 0),IR(8917, 15)/* ImageReadWrite */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {15,IR(0, 0),IR(8932, 12)/* ImageMipmap */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {17,IR(0, 0),IR(8944, 6)/* Pipes */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {18,IR(0, 0),IR(8950, 7)/* Groups */,IR(0, 0),IR(1, 0),IR(33, 1),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {19,IR(0, 0),IR(8957, 14)/* DeviceEnqueue */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {20,IR(0, 0),IR(8971, 15)/* LiteralSampler */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {21,IR(0, 0),IR(8986, 14)/* AtomicStorage */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {22,IR(0, 0),IR(9000, 6)/* Int16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {23,IR(0, 0),IR(9006, 22)/* TessellationPointSize */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {24,IR(0, 0),IR(9028, 18)/* GeometryPointSize */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {25,IR(0, 0),IR(9046, 20)/* ImageGatherExtended */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {27,IR(0, 0),IR(9066, 24)/* StorageImageMultisample */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {28,IR(0, 0),IR(9090, 34)/* UniformBufferArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {29,IR(0, 0),IR(9124, 33)/* SampledImageArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {30,IR(0, 0),IR(9157, 34)/* StorageBufferArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {31,IR(0, 0),IR(9191, 33)/* StorageImageArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {32,IR(0, 0),IR(5672, 13)/* ClipDistance */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {33,IR(0, 0),IR(5685, 13)/* CullDistance */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {34,IR(0, 0),IR(9224, 15)/* ImageCubeArray */,IR(0, 0),IR(71, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {35,IR(0, 0),IR(6011, 18)/* SampleRateShading */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {36,IR(0, 0),IR(9256, 10)/* ImageRect */,IR(0, 0),IR(72, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {37,IR(0, 0),IR(9266, 12)/* SampledRect */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {38,IR(0, 0),IR(9278, 15)/* GenericPointer */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {39,IR(0, 0),IR(9293, 5)/* Int8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {40,IR(0, 0),IR(9298, 16)/* InputAttachment */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {41,IR(0, 0),IR(9314, 16)/* SparseResidency */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {42,IR(0, 0),IR(9330, 7)/* MinLod */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {43,IR(0, 0),IR(9337, 10)/* Sampled1D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {44,IR(0, 0),IR(9347, 8)/* Image1D */,IR(0, 0),IR(73, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {45,IR(0, 0),IR(9239, 17)/* SampledCubeArray */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {46,IR(0, 0),IR(9355, 14)/* SampledBuffer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {47,IR(0, 0),IR(9369, 12)/* ImageBuffer */,IR(0, 0),IR(74, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {48,IR(0, 0),IR(9381, 13)/* ImageMSArray */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {49,IR(0, 0),IR(9394, 28)/* StorageImageExtendedFormats */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {50,IR(0, 0),IR(9422, 11)/* ImageQuery */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {51,IR(0, 0),IR(9433, 18)/* DerivativeControl */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {52,IR(0, 0),IR(9451, 22)/* InterpolationFunction */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {53,IR(0, 0),IR(9473, 18)/* TransformFeedback */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {54,IR(0, 0),IR(9491, 16)/* GeometryStreams */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {55,IR(0, 0),IR(9507, 30)/* StorageImageReadWithoutFormat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {56,IR(0, 0),IR(9537, 31)/* StorageImageWriteWithoutFormat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {57,IR(0, 0),IR(5881, 14)/* MultiViewport */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {58,IR(0, 0),IR(9568, 17)/* SubgroupDispatch */,IR(0, 0),IR(75, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {59,IR(0, 0),IR(9585, 13)/* NamedBarrier */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {60,IR(0, 0),IR(9598, 12)/* PipeStorage */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {61,IR(0, 0),IR(6262, 16)/* GroupNonUniform */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {62,IR(0, 0),IR(9610, 20)/* GroupNonUniformVote */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {63,IR(0, 0),IR(9630, 26)/* GroupNonUniformArithmetic */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {64,IR(0, 0),IR(6517, 22)/* GroupNonUniformBallot */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {65,IR(0, 0),IR(9656, 23)/* GroupNonUniformShuffle */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {66,IR(0, 0),IR(9679, 31)/* GroupNonUniformShuffleRelative */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {67,IR(0, 0),IR(9710, 25)/* GroupNonUniformClustered */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {68,IR(0, 0),IR(9735, 20)/* GroupNonUniformQuad */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {69,IR(0, 0),IR(5827, 12)/* ShaderLayer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {70,IR(0, 0),IR(5895, 20)/* ShaderViewportIndex */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {71,IR(0, 0),IR(9755, 18)/* UniformDecoration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4165,IR(0, 0),IR(6419, 16)/* CoreBuiltinsARM */,IR(0, 0),IR(1, 0),IR(34, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4166,IR(0, 0),IR(9773, 28)/* TileImageColorReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4167,IR(0, 0),IR(9801, 28)/* TileImageDepthReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4168,IR(0, 0),IR(9829, 30)/* TileImageStencilReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4174,IR(0, 0),IR(9859, 11)/* TensorsARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4175,IR(0, 0),IR(9870, 37)/* StorageTensorArrayDynamicIndexingARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4176,IR(0, 0),IR(9907, 40)/* StorageTensorArrayNonUniformIndexingARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4191,IR(0, 0),IR(9947, 9)/* GraphARM */,IR(0, 0),IR(1, 0),IR(37, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4201,IR(0, 0),IR(9956, 28)/* CooperativeMatrixLayoutsARM */,IR(0, 0),IR(1, 0),IR(38, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4212,IR(0, 0),IR(9984, 10)/* Float8EXT */,IR(0, 0),IR(1, 0),IR(39, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4213,IR(0, 0),IR(9994, 27)/* Float8CooperativeMatrixEXT */,IR(0, 0),IR(78, 2),IR(39, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4422,IR(0, 0),IR(6744, 23)/* FragmentShadingRateKHR */,IR(0, 0),IR(3, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4423,IR(0, 0),IR(6278, 18)/* SubgroupBallotKHR */,IR(0, 0),IR(1, 0),IR(2, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4427,IR(0, 0),IR(6682, 15)/* DrawParameters */,IR(0, 0),IR(3, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4428,IR(0, 0),IR(10042, 33)/* WorkgroupMemoryExplicitLayoutKHR */,IR(0, 0),IR(3, 1),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4429,IR(0, 0),IR(10075, 43)/* WorkgroupMemoryExplicitLayout8BitAccessKHR */,IR(0, 0),IR(80, 1),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4430,IR(0, 0),IR(10118, 44)/* WorkgroupMemoryExplicitLayout16BitAccessKHR */,IR(0, 0),IR(80, 1),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4431,IR(0, 0),IR(10162, 16)/* SubgroupVoteKHR */,IR(0, 0),IR(1, 0),IR(41, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4433,IR(0, 0),IR(10178, 25)/* StorageBuffer16BitAccess */,IR(23, 1),IR(1, 0),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4434,IR(0, 0),IR(10231, 35)/* UniformAndStorageBuffer16BitAccess */,IR(24, 1),IR(81, 1),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4435,IR(0, 0),IR(10283, 22)/* StoragePushConstant16 */,IR(0, 0),IR(1, 0),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4436,IR(0, 0),IR(10305, 21)/* StorageInputOutput16 */,IR(0, 0),IR(1, 0),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4437,IR(0, 0),IR(6779, 12)/* DeviceGroup */,IR(0, 0),IR(1, 0),IR(8, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4439,IR(0, 0),IR(6801, 10)/* MultiView */,IR(0, 0),IR(3, 1),IR(9, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4441,IR(0, 0),IR(10326, 30)/* VariablePointersStorageBuffer */,IR(0, 0),IR(3, 1),IR(43, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4442,IR(0, 0),IR(10356, 17)/* VariablePointers */,IR(0, 0),IR(82, 1),IR(43, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4445,IR(0, 0),IR(10373, 17)/* AtomicStorageOps */,IR(0, 0),IR(83, 1),IR(44, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4447,IR(0, 0),IR(10390, 28)/* SampleMaskPostDepthCoverage */,IR(0, 0),IR(1, 0),IR(45, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4448,IR(0, 0),IR(10418, 24)/* StorageBuffer8BitAccess */,IR(0, 0),IR(1, 0),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4449,IR(0, 0),IR(10442, 34)/* UniformAndStorageBuffer8BitAccess */,IR(0, 0),IR(84, 1),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4450,IR(0, 0),IR(10476, 21)/* StoragePushConstant8 */,IR(0, 0),IR(1, 0),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4464,IR(0, 0),IR(10497, 15)/* DenormPreserve */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4465,IR(0, 0),IR(10512, 18)/* DenormFlushToZero */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4466,IR(0, 0),IR(10530, 25)/* SignedZeroInfNanPreserve */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4467,IR(0, 0),IR(10555, 16)/* RoundingModeRTE */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4468,IR(0, 0),IR(10571, 16)/* RoundingModeRTZ */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4471,IR(0, 0),IR(10587, 23)/* RayQueryProvisionalKHR */,IR(0, 0),IR(3, 1),IR(48, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4472,IR(0, 0),IR(10610, 12)/* RayQueryKHR */,IR(0, 0),IR(3, 1),IR(48, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4473,IR(0, 0),IR(10622, 19)/* UntypedPointersKHR */,IR(0, 0),IR(1, 0),IR(49, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4478,IR(0, 0),IR(10641, 32)/* RayTraversalPrimitiveCullingKHR */,IR(0, 0),IR(85, 2),IR(50, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4479,IR(0, 0),IR(5765, 14)/* RayTracingKHR */,IR(0, 0),IR(3, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4484,IR(0, 0),IR(10673, 26)/* TextureSampleWeightedQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4485,IR(0, 0),IR(10699, 21)/* TextureBoxFilterQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4486,IR(0, 0),IR(10720, 22)/* TextureBlockMatchQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4495,IR(0, 0),IR(6841, 16)/* TileShadingQCOM */,IR(0, 0),IR(3, 1),IR(53, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4496,IR(0, 0),IR(10742, 32)/* CooperativeMatrixConversionQCOM */,IR(0, 0),IR(87, 1),IR(54, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4498,IR(0, 0),IR(10774, 23)/* TextureBlockMatch2QCOM */,IR(0, 0),IR(1, 0),IR(55, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5008,IR(0, 0),IR(10797, 16)/* Float16ImageAMD */,IR(0, 0),IR(3, 1),IR(56, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5009,IR(0, 0),IR(10813, 22)/* ImageGatherBiasLodAMD */,IR(0, 0),IR(3, 1),IR(57, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5010,IR(0, 0),IR(10835, 16)/* FragmentMaskAMD */,IR(0, 0),IR(3, 1),IR(58, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5013,IR(0, 0),IR(7078, 17)/* StencilExportEXT */,IR(0, 0),IR(3, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5015,IR(0, 0),IR(10851, 21)/* ImageReadWriteLodAMD */,IR(0, 0),IR(3, 1),IR(59, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5016,IR(0, 0),IR(10872, 14)/* Int64ImageEXT */,IR(0, 0),IR(3, 1),IR(60, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5055,IR(0, 0),IR(10886, 15)/* ShaderClockKHR */,IR(0, 0),IR(1, 0),IR(61, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5067,IR(0, 0),IR(7124, 18)/* ShaderEnqueueAMDX */,IR(0, 0),IR(3, 1),IR(62, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5087,IR(0, 0),IR(10901, 15)/* QuadControlKHR */,IR(0, 0),IR(1, 0),IR(63, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5112,IR(0, 0),IR(10916, 14)/* Int4TypeINTEL */,IR(0, 0),IR(1, 0),IR(64, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5114,IR(0, 0),IR(10930, 27)/* Int4CooperativeMatrixINTEL */,IR(0, 0),IR(88, 2),IR(64, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5116,IR(0, 0),IR(10957, 16)/* BFloat16TypeKHR */,IR(0, 0),IR(1, 0),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5117,IR(0, 0),IR(10973, 22)/* BFloat16DotProductKHR */,IR(0, 0),IR(90, 1),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5118,IR(0, 0),IR(10995, 29)/* BFloat16CooperativeMatrixKHR */,IR(0, 0),IR(91, 2),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5128,IR(0, 0),IR(7173, 18)/* DescriptorHeapEXT */,IR(0, 0),IR(93, 1),IR(66, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5249,IR(0, 0),IR(11024, 29)/* SampleMaskOverrideCoverageNV */,IR(0, 0),IR(25, 1),IR(67, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5251,IR(0, 0),IR(11053, 28)/* GeometryShaderPassthroughNV */,IR(0, 0),IR(70, 1),IR(68, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5254,IR(0, 0),IR(5839, 28)/* ShaderViewportIndexLayerEXT */,IR(25, 1),IR(94, 1),IR(69, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5255,IR(0, 0),IR(7222, 21)/* ShaderViewportMaskNV */,IR(0, 0),IR(95, 1),IR(71, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5259,IR(0, 0),IR(7263, 19)/* ShaderStereoViewNV */,IR(0, 0),IR(96, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5260,IR(0, 0),IR(7324, 20)/* PerViewAttributesNV */,IR(0, 0),IR(40, 1),IR(72, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5265,IR(0, 0),IR(7382, 24)/* FragmentFullyCoveredEXT */,IR(0, 0),IR(3, 1),IR(17, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5266,IR(0, 0),IR(5779, 14)/* MeshShadingNV */,IR(0, 0),IR(3, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5282,IR(0, 0),IR(11108, 17)/* ImageFootprintNV */,IR(0, 0),IR(1, 0),IR(73, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5283,IR(0, 0),IR(5793, 15)/* MeshShadingEXT */,IR(0, 0),IR(3, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5284,IR(0, 0),IR(7572, 23)/* FragmentBarycentricKHR */,IR(26, 1),IR(1, 0),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5288,IR(0, 0),IR(11147, 31)/* ComputeDerivativeGroupQuadsKHR */,IR(27, 1),IR(3, 1),IR(74, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5291,IR(0, 0),IR(7661, 19)/* FragmentDensityEXT */,IR(28, 1),IR(3, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5297,IR(0, 0),IR(11222, 30)/* GroupNonUniformPartitionedEXT */,IR(29, 1),IR(1, 0),IR(76, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5301,IR(0, 0),IR(11281, 17)/* ShaderNonUniform */,IR(30, 1),IR(3, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5302,IR(0, 0),IR(11318, 23)/* RuntimeDescriptorArray */,IR(31, 1),IR(3, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5303,IR(0, 0),IR(11367, 36)/* InputAttachmentArrayDynamicIndexing */,IR(32, 1),IR(97, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5304,IR(0, 0),IR(11442, 39)/* UniformTexelBufferArrayDynamicIndexing */,IR(33, 1),IR(74, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5305,IR(0, 0),IR(11523, 39)/* StorageTexelBufferArrayDynamicIndexing */,IR(34, 1),IR(98, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5306,IR(0, 0),IR(11604, 37)/* UniformBufferArrayNonUniformIndexing */,IR(35, 1),IR(99, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5307,IR(0, 0),IR(11681, 36)/* SampledImageArrayNonUniformIndexing */,IR(36, 1),IR(99, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5308,IR(0, 0),IR(11756, 37)/* StorageBufferArrayNonUniformIndexing */,IR(37, 1),IR(99, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5309,IR(0, 0),IR(11833, 36)/* StorageImageArrayNonUniformIndexing */,IR(38, 1),IR(99, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5310,IR(0, 0),IR(11908, 39)/* InputAttachmentArrayNonUniformIndexing */,IR(39, 1),IR(100, 2),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5311,IR(0, 0),IR(11989, 42)/* UniformTexelBufferArrayNonUniformIndexing */,IR(40, 1),IR(102, 2),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5312,IR(0, 0),IR(12076, 42)/* StorageTexelBufferArrayNonUniformIndexing */,IR(41, 1),IR(104, 2),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5336,IR(0, 0),IR(8276, 27)/* RayTracingPositionFetchKHR */,IR(0, 0),IR(3, 1),IR(79, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5340,IR(0, 0),IR(5752, 13)/* RayTracingNV */,IR(0, 0),IR(3, 1),IR(26, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5341,IR(0, 0),IR(8223, 23)/* RayTracingMotionBlurNV */,IR(0, 0),IR(3, 1),IR(27, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5345,IR(0, 0),IR(12163, 18)/* VulkanMemoryModel */,IR(42, 1),IR(1, 0),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5346,IR(0, 0),IR(12202, 29)/* VulkanMemoryModelDeviceScope */,IR(43, 1),IR(1, 0),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5347,IR(0, 0),IR(5615, 31)/* PhysicalStorageBufferAddresses */,IR(44, 1),IR(3, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5350,IR(0, 0),IR(12297, 32)/* ComputeDerivativeGroupLinearKHR */,IR(45, 1),IR(3, 1),IR(74, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5353,IR(0, 0),IR(12360, 25)/* RayTracingProvisionalKHR */,IR(0, 0),IR(3, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5357,IR(0, 0),IR(12385, 20)/* CooperativeMatrixNV */,IR(0, 0),IR(3, 1),IR(81, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5363,IR(0, 0),IR(12405, 33)/* FragmentShaderSampleInterlockEXT */,IR(0, 0),IR(3, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5372,IR(0, 0),IR(12438, 38)/* FragmentShaderShadingRateInterlockEXT */,IR(0, 0),IR(3, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5373,IR(0, 0),IR(8591, 19)/* ShaderSMBuiltinsNV */,IR(0, 0),IR(3, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5378,IR(0, 0),IR(12476, 32)/* FragmentShaderPixelInterlockEXT */,IR(0, 0),IR(3, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5379,IR(0, 0),IR(12508, 25)/* DemoteToHelperInvocation */,IR(46, 1),IR(3, 1),IR(83, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5380,IR(0, 0),IR(12561, 23)/* DisplacementMicromapNV */,IR(0, 0),IR(3, 1),IR(84, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5381,IR(0, 0),IR(12584, 29)/* RayTracingOpacityMicromapEXT */,IR(0, 0),IR(3, 1),IR(85, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5383,IR(0, 0),IR(12613, 26)/* ShaderInvocationReorderNV */,IR(0, 0),IR(61, 1),IR(86, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5388,IR(0, 0),IR(12639, 27)/* ShaderInvocationReorderEXT */,IR(0, 0),IR(61, 1),IR(87, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5390,IR(0, 0),IR(12666, 18)/* BindlessTextureNV */,IR(0, 0),IR(1, 0),IR(88, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5391,IR(0, 0),IR(12684, 25)/* RayQueryPositionFetchKHR */,IR(0, 0),IR(3, 1),IR(79, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5394,IR(0, 0),IR(12709, 20)/* CooperativeVectorNV */,IR(0, 0),IR(1, 0),IR(89, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5404,IR(0, 0),IR(12729, 22)/* AtomicFloat16VectorNV */,IR(0, 0),IR(1, 0),IR(90, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5409,IR(0, 0),IR(8337, 33)/* RayTracingDisplacementMicromapNV */,IR(0, 0),IR(61, 1),IR(84, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5414,IR(0, 0),IR(12751, 18)/* RawAccessChainsNV */,IR(0, 0),IR(1, 0),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5418,IR(0, 0),IR(8480, 28)/* RayTracingSpheresGeometryNV */,IR(0, 0),IR(1, 0),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5419,IR(0, 0),IR(8519, 39)/* RayTracingLinearSweptSpheresGeometryNV */,IR(0, 0),IR(1, 0),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5423,IR(0, 0),IR(12769, 20)/* PushConstantBanksNV */,IR(0, 0),IR(3, 1),IR(92, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5425,IR(0, 0),IR(12789, 14)/* LongVectorEXT */,IR(0, 0),IR(1, 0),IR(93, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5426,IR(0, 0),IR(12803, 23)/* Shader64BitIndexingEXT */,IR(0, 0),IR(1, 0),IR(94, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5430,IR(0, 0),IR(12826, 30)/* CooperativeMatrixReductionsNV */,IR(0, 0),IR(1, 0),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5431,IR(0, 0),IR(12856, 31)/* CooperativeMatrixConversionsNV */,IR(0, 0),IR(1, 0),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5432,IR(0, 0),IR(12887, 40)/* CooperativeMatrixPerElementOperationsNV */,IR(0, 0),IR(1, 0),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5433,IR(0, 0),IR(12927, 36)/* CooperativeMatrixTensorAddressingNV */,IR(0, 0),IR(1, 0),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5434,IR(0, 0),IR(12963, 30)/* CooperativeMatrixBlockLoadsNV */,IR(0, 0),IR(1, 0),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5435,IR(0, 0),IR(12993, 28)/* CooperativeVectorTrainingNV */,IR(0, 0),IR(1, 0),IR(89, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5437,IR(0, 0),IR(8765, 41)/* RayTracingClusterAccelerationStructureNV */,IR(0, 0),IR(61, 1),IR(31, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5439,IR(0, 0),IR(13021, 19)/* TensorAddressingNV */,IR(0, 0),IR(1, 0),IR(96, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5568,IR(0, 0),IR(13040, 21)/* SubgroupShuffleINTEL */,IR(0, 0),IR(1, 0),IR(97, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5569,IR(0, 0),IR(13061, 27)/* SubgroupBufferBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(97, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5570,IR(0, 0),IR(13088, 26)/* SubgroupImageBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(97, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5579,IR(0, 0),IR(13114, 31)/* SubgroupImageMediaBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5582,IR(0, 0),IR(13145, 21)/* RoundToInfinityINTEL */,IR(0, 0),IR(1, 0),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5583,IR(0, 0),IR(13166, 23)/* FloatingPointModeINTEL */,IR(0, 0),IR(1, 0),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5584,IR(0, 0),IR(13189, 23)/* IntegerFunctions2INTEL */,IR(0, 0),IR(1, 0),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5603,IR(0, 0),IR(13212, 22)/* FunctionPointersINTEL */,IR(0, 0),IR(1, 0),IR(101, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5604,IR(0, 0),IR(13234, 24)/* IndirectReferencesINTEL */,IR(0, 0),IR(1, 0),IR(101, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5606,IR(0, 0),IR(13258, 9)/* AsmINTEL */,IR(0, 0),IR(1, 0),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5612,IR(0, 0),IR(13267, 23)/* AtomicFloat32MinMaxEXT */,IR(0, 0),IR(1, 0),IR(103, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5613,IR(0, 0),IR(13290, 23)/* AtomicFloat64MinMaxEXT */,IR(0, 0),IR(1, 0),IR(103, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5616,IR(0, 0),IR(13313, 23)/* AtomicFloat16MinMaxEXT */,IR(0, 0),IR(1, 0),IR(103, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5617,IR(0, 0),IR(13336, 19)/* VectorComputeINTEL */,IR(0, 0),IR(106, 1),IR(104, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5619,IR(0, 0),IR(13355, 15)/* VectorAnyINTEL */,IR(0, 0),IR(1, 0),IR(104, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5629,IR(0, 0),IR(13370, 16)/* ExpectAssumeKHR */,IR(0, 0),IR(1, 0),IR(105, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5696,IR(0, 0),IR(13386, 33)/* SubgroupAvcMotionEstimationINTEL */,IR(0, 0),IR(1, 0),IR(106, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5697,IR(0, 0),IR(13419, 38)/* SubgroupAvcMotionEstimationIntraINTEL */,IR(0, 0),IR(1, 0),IR(106, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5698,IR(0, 0),IR(13457, 39)/* SubgroupAvcMotionEstimationChromaINTEL */,IR(0, 0),IR(1, 0),IR(106, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5817,IR(0, 0),IR(13496, 25)/* VariableLengthArrayINTEL */,IR(0, 0),IR(1, 0),IR(107, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5821,IR(0, 0),IR(13521, 26)/* FunctionFloatControlINTEL */,IR(0, 0),IR(1, 0),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5824,IR(0, 0),IR(13547, 27)/* FPGAMemoryAttributesALTERA */,IR(47, 1),IR(1, 0),IR(108, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5837,IR(0, 0),IR(13600, 20)/* FPFastMathModeINTEL */,IR(0, 0),IR(0, 1),IR(110, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5844,IR(0, 0),IR(13620, 33)/* ArbitraryPrecisionIntegersALTERA */,IR(48, 1),IR(1, 0),IR(111, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5845,IR(0, 0),IR(13685, 38)/* ArbitraryPrecisionFloatingPointALTERA */,IR(49, 1),IR(1, 0),IR(113, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5886,IR(0, 0),IR(13760, 30)/* UnstructuredLoopControlsINTEL */,IR(0, 0),IR(1, 0),IR(115, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5888,IR(0, 0),IR(13790, 23)/* FPGALoopControlsALTERA */,IR(50, 1),IR(1, 0),IR(116, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5892,IR(0, 0),IR(13835, 22)/* KernelAttributesINTEL */,IR(0, 0),IR(1, 0),IR(118, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5897,IR(0, 0),IR(13857, 26)/* FPGAKernelAttributesINTEL */,IR(0, 0),IR(1, 0),IR(118, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5898,IR(0, 0),IR(13883, 25)/* FPGAMemoryAccessesALTERA */,IR(51, 1),IR(1, 0),IR(119, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5904,IR(0, 0),IR(13932, 28)/* FPGAClusterAttributesALTERA */,IR(52, 1),IR(1, 0),IR(121, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5906,IR(0, 0),IR(13987, 15)/* LoopFuseALTERA */,IR(53, 1),IR(1, 0),IR(123, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5908,IR(0, 0),IR(14016, 21)/* FPGADSPControlALTERA */,IR(54, 1),IR(1, 0),IR(125, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5910,IR(0, 0),IR(14057, 26)/* MemoryAccessAliasingINTEL */,IR(0, 0),IR(1, 0),IR(127, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5916,IR(0, 0),IR(14083, 41)/* FPGAInvocationPipeliningAttributesALTERA */,IR(55, 1),IR(1, 0),IR(128, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5920,IR(0, 0),IR(14164, 25)/* FPGABufferLocationALTERA */,IR(56, 1),IR(1, 0),IR(130, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5922,IR(0, 0),IR(14213, 35)/* ArbitraryPrecisionFixedPointALTERA */,IR(57, 1),IR(1, 0),IR(132, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5935,IR(0, 0),IR(14282, 24)/* USMStorageClassesALTERA */,IR(58, 1),IR(1, 0),IR(134, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5939,IR(0, 0),IR(14329, 30)/* RuntimeAlignedAttributeALTERA */,IR(59, 1),IR(1, 0),IR(136, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5943,IR(0, 0),IR(14388, 14)/* IOPipesALTERA */,IR(60, 1),IR(1, 0),IR(138, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5945,IR(0, 0),IR(14415, 20)/* BlockingPipesALTERA */,IR(61, 1),IR(1, 0),IR(140, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5948,IR(0, 0),IR(14454, 14)/* FPGARegALTERA */,IR(62, 1),IR(1, 0),IR(142, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6016,IR(0, 0),IR(14481, 19)/* DotProductInputAll */,IR(63, 1),IR(1, 0),IR(144, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6017,IR(0, 0),IR(14522, 22)/* DotProductInput4x8Bit */,IR(64, 1),IR(107, 1),IR(144, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6018,IR(0, 0),IR(14569, 28)/* DotProductInput4x8BitPacked */,IR(65, 1),IR(1, 0),IR(144, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6019,IR(0, 0),IR(14628, 11)/* DotProduct */,IR(66, 1),IR(1, 0),IR(144, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6020,IR(0, 0),IR(8818, 15)/* RayCullMaskKHR */,IR(0, 0),IR(1, 0),IR(32, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6022,IR(0, 0),IR(10021, 21)/* CooperativeMatrixKHR */,IR(0, 0),IR(1, 0),IR(145, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6024,IR(0, 0),IR(14653, 24)/* ReplicatedCompositesEXT */,IR(0, 0),IR(1, 0),IR(146, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6025,IR(0, 0),IR(14677, 16)/* BitInstructions */,IR(0, 0),IR(1, 0),IR(147, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6026,IR(0, 0),IR(14693, 25)/* GroupNonUniformRotateKHR */,IR(0, 0),IR(77, 1),IR(148, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6029,IR(0, 0),IR(14718, 15)/* FloatControls2 */,IR(0, 0),IR(1, 0),IR(149, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6030,IR(0, 0),IR(14733, 7)/* FMAKHR */,IR(0, 0),IR(1, 0),IR(150, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6033,IR(0, 0),IR(14740, 20)/* AtomicFloat32AddEXT */,IR(0, 0),IR(1, 0),IR(151, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6034,IR(0, 0),IR(14760, 20)/* AtomicFloat64AddEXT */,IR(0, 0),IR(1, 0),IR(151, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6089,IR(0, 0),IR(14780, 20)/* LongCompositesINTEL */,IR(0, 0),IR(1, 0),IR(152, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6094,IR(0, 0),IR(14800, 11)/* OptNoneEXT */,IR(67, 1),IR(1, 0),IR(153, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6095,IR(0, 0),IR(14824, 20)/* AtomicFloat16AddEXT */,IR(0, 0),IR(1, 0),IR(155, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6114,IR(0, 0),IR(14844, 21)/* DebugInfoModuleINTEL */,IR(0, 0),IR(1, 0),IR(156, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6115,IR(0, 0),IR(14865, 24)/* BFloat16ConversionINTEL */,IR(0, 0),IR(1, 0),IR(157, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6141,IR(0, 0),IR(14889, 18)/* SplitBarrierINTEL */,IR(0, 0),IR(1, 0),IR(158, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6144,IR(0, 0),IR(14907, 19)/* ArithmeticFenceEXT */,IR(0, 0),IR(1, 0),IR(159, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6150,IR(0, 0),IR(14926, 30)/* FPGAClusterAttributesV2ALTERA */,IR(68, 1),IR(108, 1),IR(121, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6161,IR(0, 0),IR(14985, 28)/* FPGAKernelAttributesv2INTEL */,IR(0, 0),IR(109, 1),IR(118, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6162,IR(0, 0),IR(15013, 19)/* TaskSequenceALTERA */,IR(69, 1),IR(1, 0),IR(160, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6169,IR(0, 0),IR(15050, 16)/* FPMaxErrorINTEL */,IR(0, 0),IR(1, 0),IR(162, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6171,IR(0, 0),IR(15066, 25)/* FPGALatencyControlALTERA */,IR(70, 1),IR(1, 0),IR(163, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6174,IR(0, 0),IR(15115, 29)/* FPGAArgumentInterfacesALTERA */,IR(71, 1),IR(1, 0),IR(165, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6187,IR(0, 0),IR(15172, 30)/* GlobalVariableHostAccessINTEL */,IR(0, 0),IR(1, 0),IR(167, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6189,IR(0, 0),IR(15202, 36)/* GlobalVariableFPGADecorationsALTERA */,IR(72, 1),IR(1, 0),IR(168, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6220,IR(0, 0),IR(15273, 28)/* SubgroupBufferPrefetchINTEL */,IR(0, 0),IR(1, 0),IR(170, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6228,IR(0, 0),IR(15301, 23)/* Subgroup2DBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(171, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6229,IR(0, 0),IR(15324, 30)/* Subgroup2DBlockTransformINTEL */,IR(0, 0),IR(110, 1),IR(171, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6230,IR(0, 0),IR(15354, 30)/* Subgroup2DBlockTransposeINTEL */,IR(0, 0),IR(110, 1),IR(171, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6236,IR(0, 0),IR(15384, 38)/* SubgroupMatrixMultiplyAccumulateINTEL */,IR(0, 0),IR(1, 0),IR(172, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6241,IR(0, 0),IR(15422, 28)/* TernaryBitwiseFunctionINTEL */,IR(0, 0),IR(1, 0),IR(173, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6243,IR(0, 0),IR(15450, 32)/* UntypedVariableLengthArrayINTEL */,IR(0, 0),IR(111, 2),IR(107, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6245,IR(0, 0),IR(15482, 21)/* SpecConditionalINTEL */,IR(0, 0),IR(1, 0),IR(174, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6246,IR(0, 0),IR(15503, 22)/* FunctionVariantsINTEL */,IR(0, 0),IR(113, 1),IR(174, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6400,IR(0, 0),IR(15525, 26)/* GroupUniformArithmeticKHR */,IR(0, 0),IR(1, 0),IR(175, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6425,IR(0, 0),IR(15551, 27)/* TensorFloat32RoundingINTEL */,IR(0, 0),IR(1, 0),IR(176, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6427,IR(0, 0),IR(15578, 25)/* MaskedGatherScatterINTEL */,IR(0, 0),IR(1, 0),IR(177, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6441,IR(0, 0),IR(15603, 19)/* CacheControlsINTEL */,IR(0, 0),IR(1, 0),IR(178, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6460,IR(0, 0),IR(15622, 20)/* RegisterLimitsINTEL */,IR(0, 0),IR(1, 0),IR(179, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6528,IR(0, 0),IR(15642, 20)/* BindlessImagesINTEL */,IR(0, 0),IR(1, 0),IR(180, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6912,IR(0, 0),IR(15662, 33)/* DotProductFloat16AccFloat32VALVE */,IR(0, 0),IR(114, 1),IR(181, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6913,IR(0, 0),IR(15695, 33)/* DotProductFloat16AccFloat16VALVE */,IR(0, 0),IR(114, 1),IR(181, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6914,IR(0, 0),IR(15728, 27)/* DotProductBFloat16AccVALVE */,IR(0, 0),IR(90, 1),IR(181, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6915,IR(0, 0),IR(15755, 32)/* DotProductFloat8AccFloat32VALVE */,IR(0, 0),IR(115, 1),IR(181, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {0,IR(0, 0),IR(15787, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(15799, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(15807, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {3,IR(0, 0),IR(15815, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(15821, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(15828, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(15839, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(15848, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(15861, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(15867, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(15877, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(15883, 15)/* ImportedModule */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {1,IR(0, 0),IR(15898, 20)/* ImportedDeclaration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {0,IR(0, 0),IR(15918, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(15923, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(15939, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(15953, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(15966, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(15978, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(15995, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(16007, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(16022, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(16035, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(16050, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(16068, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(16085, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(16106, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(16126, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(16146, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {16384,IR(0, 0),IR(16162, 16)/* FlagIsEnumClass */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {32768,IR(0, 0),IR(16178, 20)/* FlagTypePassByValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {65536,IR(0, 0),IR(16198, 24)/* FlagTypePassByReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(16222, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {1,IR(0, 0),IR(16228, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {2,IR(0, 0),IR(16233, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {3,IR(0, 1),IR(16272, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {4,IR(1, 2),IR(16283, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {5,IR(0, 0),IR(16292, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {6,IR(0, 0),IR(16297, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {7,IR(0, 0),IR(16304, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {8,IR(0, 1),IR(16315, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {9,IR(1, 2),IR(16322, 9)/* Fragment */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {0,IR(0, 0),IR(16331, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(16341, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(16354, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {3,IR(0, 0),IR(16367, 11)/* AtomicType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(16378, 10)/* Float16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1,IR(0, 0),IR(16388, 10)/* Float32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {2,IR(0, 0),IR(16398, 10)/* Float64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {3,IR(0, 0),IR(16408, 13)/* SignedInt8NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {4,IR(0, 0),IR(16421, 14)/* SignedInt16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {5,IR(0, 0),IR(16435, 14)/* SignedInt32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {6,IR(0, 0),IR(16449, 14)/* SignedInt64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {7,IR(0, 0),IR(16463, 15)/* UnsignedInt8NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {8,IR(0, 0),IR(16478, 16)/* UnsignedInt16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {9,IR(0, 0),IR(16494, 16)/* UnsignedInt32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {10,IR(0, 0),IR(16510, 16)/* UnsignedInt64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491000,IR(0, 0),IR(16526, 19)/* SignedInt8PackedNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491001,IR(0, 0),IR(16545, 21)/* UnsignedInt8PackedNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491002,IR(0, 0),IR(16566, 12)/* FloatE4M3NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491003,IR(0, 0),IR(16578, 12)/* FloatE5M2NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {0,IR(0, 0),IR(16590, 12)/* RowMajorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {1,IR(0, 0),IR(16602, 15)/* ColumnMajorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {4202,IR(0, 0),IR(16617, 25)/* RowBlockedInterleavedARM */,IR(0, 0),IR(116, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {4203,IR(0, 0),IR(16642, 28)/* ColumnBlockedInterleavedARM */,IR(0, 0),IR(116, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {0,IR(0, 0),IR(16670, 8)/* NoneKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {1,IR(0, 0),IR(16678, 27)/* MatrixASignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {2,IR(0, 0),IR(16705, 27)/* MatrixBSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {4,IR(0, 0),IR(16732, 27)/* MatrixCSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {8,IR(0, 0),IR(16759, 32)/* MatrixResultSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {16,IR(0, 0),IR(16791, 26)/* SaturatingAccumulationKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {1,IR(0, 0),IR(16817, 4)/* Row */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {2,IR(0, 0),IR(16821, 7)/* Column */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {4,IR(0, 0),IR(16828, 4)/* 2x2 */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {0,IR(0, 0),IR(16832, 11)/* MatrixAKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {1,IR(0, 0),IR(16843, 11)/* MatrixBKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {2,IR(0, 0),IR(16854, 21)/* MatrixAccumulatorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {0,IR(0, 0),IR(16875, 11)/* RowMajorNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {1,IR(0, 0),IR(16886, 14)/* ColumnMajorNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {2,IR(0, 0),IR(16900, 21)/* InferencingOptimalNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {3,IR(0, 0),IR(16921, 18)/* TrainingOptimalNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {0,IR(0, 0),IR(15787, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(15799, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(15807, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(15815, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(15821, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(15828, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(15839, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {8,IR(0, 0),IR(15848, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(15861, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(15867, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(15877, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(15918, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(15923, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(15939, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(15953, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(15966, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(15978, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(15995, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(16007, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(16022, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(16035, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(16050, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(16068, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(16085, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(16106, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(16126, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(16146, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(16222, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {1,IR(0, 0),IR(16228, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {2,IR(0, 0),IR(16233, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {3,IR(0, 1),IR(16272, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {4,IR(1, 2),IR(16283, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {5,IR(0, 0),IR(16292, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {6,IR(0, 0),IR(16297, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {7,IR(0, 0),IR(16304, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {8,IR(0, 1),IR(16315, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {0,IR(0, 0),IR(16331, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(16341, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(16354, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(16939, 17)/* RelaxedPrecision */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {1,IR(0, 1),IR(16956, 7)/* SpecId */,IR(0, 0),IR(117, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {2,IR(0, 0),IR(16963, 6)/* Block */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {3,IR(0, 0),IR(16969, 12)/* BufferBlock */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),SPV_SPIRV_VERSION_WORD(1,3)}, // SPV_OPERAND_TYPE_DECORATION
  {4,IR(0, 0),IR(16981, 9)/* RowMajor */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5,IR(0, 0),IR(16990, 9)/* ColMajor */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6,IR(0, 1),IR(16999, 12)/* ArrayStride */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {7,IR(0, 1),IR(17011, 13)/* MatrixStride */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {8,IR(0, 0),IR(17024, 11)/* GLSLShared */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {9,IR(0, 0),IR(17035, 11)/* GLSLPacked */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {10,IR(0, 0),IR(17046, 8)/* CPacked */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {11,IR(3, 1),IR(17080, 8)/* BuiltIn */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {13,IR(0, 0),IR(17088, 14)/* NoPerspective */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {14,IR(0, 0),IR(17102, 5)/* Flat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {15,IR(0, 0),IR(17107, 6)/* Patch */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {16,IR(0, 0),IR(17113, 9)/* Centroid */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {17,IR(0, 0),IR(17122, 7)/* Sample */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {18,IR(0, 0),IR(17129, 10)/* Invariant */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {19,IR(0, 0),IR(17139, 9)/* Restrict */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {20,IR(0, 0),IR(17148, 8)/* Aliased */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {21,IR(0, 0),IR(17156, 9)/* Volatile */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {22,IR(0, 0),IR(17165, 9)/* Constant */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {23,IR(0, 0),IR(17174, 9)/* Coherent */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {24,IR(0, 0),IR(17183, 12)/* NonWritable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {25,IR(0, 0),IR(17195, 12)/* NonReadable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {26,IR(0, 0),IR(17207, 8)/* Uniform */,IR(0, 0),IR(119, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {27,IR(4, 1),IR(17241, 10)/* UniformId */,IR(0, 0),IR(119, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {28,IR(0, 0),IR(17251, 20)/* SaturatedConversion */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {29,IR(0, 1),IR(17271, 7)/* Stream */,IR(0, 0),IR(121, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {30,IR(0, 1),IR(17278, 9)/* Location */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {31,IR(0, 1),IR(17287, 10)/* Component */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {32,IR(0, 1),IR(17297, 6)/* Index */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {33,IR(0, 1),IR(17303, 8)/* Binding */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {34,IR(0, 1),IR(17311, 14)/* DescriptorSet */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {35,IR(0, 1),IR(17325, 7)/* Offset */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {36,IR(0, 1),IR(17332, 10)/* XfbBuffer */,IR(0, 0),IR(122, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {37,IR(0, 1),IR(17342, 10)/* XfbStride */,IR(0, 0),IR(122, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {38,IR(5, 1),IR(17398, 14)/* FuncParamAttr */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {39,IR(6, 1),IR(17446, 15)/* FPRoundingMode */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {40,IR(7, 1),IR(17496, 15)/* FPFastMathMode */,IR(0, 0),IR(123, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {41,IR(8, 2),IR(17573, 18)/* LinkageAttributes */,IR(0, 0),IR(125, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {42,IR(0, 0),IR(17591, 14)/* NoContraction */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {43,IR(0, 1),IR(17605, 21)/* InputAttachmentIndex */,IR(0, 0),IR(97, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {44,IR(0, 1),IR(17626, 10)/* Alignment */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {45,IR(0, 1),IR(17636, 14)/* MaxByteOffset */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {46,IR(10, 1),IR(17670, 12)/* AlignmentId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {47,IR(10, 1),IR(17682, 16)/* MaxByteOffsetId */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4216,IR(0, 0),IR(17698, 44)/* SaturatedToLargestFloat8NormalConversionEXT */,IR(0, 0),IR(115, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4469,IR(0, 0),IR(17742, 13)/* NoSignedWrap */,IR(0, 0),IR(1, 0),IR(182, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4470,IR(0, 0),IR(17755, 15)/* NoUnsignedWrap */,IR(0, 0),IR(1, 0),IR(182, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4487,IR(0, 0),IR(17770, 18)/* WeightTextureQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4488,IR(0, 0),IR(17788, 22)/* BlockMatchTextureQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4499,IR(0, 0),IR(17810, 22)/* BlockMatchSamplerQCOM */,IR(0, 0),IR(1, 0),IR(55, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4999,IR(0, 0),IR(17832, 18)/* ExplicitInterpAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5019,IR(10, 1),IR(17850, 32)/* NodeSharesPayloadLimitsWithAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5020,IR(10, 1),IR(17882, 20)/* NodeMaxPayloadsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5078,IR(0, 0),IR(17902, 23)/* TrackFinishWritingAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5091,IR(10, 1),IR(17925, 20)/* PayloadNodeNameAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5098,IR(10, 1),IR(17945, 25)/* PayloadNodeBaseIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5099,IR(0, 0),IR(17970, 27)/* PayloadNodeSparseArrayAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5100,IR(10, 1),IR(17997, 25)/* PayloadNodeArraySizeAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5105,IR(0, 0),IR(18022, 28)/* PayloadDispatchIndirectAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5124,IR(10, 1),IR(18050, 17)/* ArrayStrideIdEXT */,IR(0, 0),IR(44, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5125,IR(10, 1),IR(18067, 12)/* OffsetIdEXT */,IR(0, 0),IR(44, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5248,IR(0, 0),IR(18079, 19)/* OverrideCoverageNV */,IR(0, 0),IR(126, 1),IR(67, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5250,IR(0, 0),IR(18098, 14)/* PassthroughNV */,IR(0, 0),IR(127, 1),IR(68, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5252,IR(0, 0),IR(18112, 19)/* ViewportRelativeNV */,IR(0, 0),IR(96, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5256,IR(0, 1),IR(18131, 28)/* SecondaryViewportRelativeNV */,IR(0, 0),IR(47, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5271,IR(0, 0),IR(18159, 16)/* PerPrimitiveEXT */,IR(73, 1),IR(128, 2),IR(183, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5272,IR(0, 0),IR(18190, 10)/* PerViewNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5273,IR(0, 0),IR(18200, 10)/* PerTaskNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5285,IR(0, 0),IR(18210, 13)/* PerVertexKHR */,IR(74, 1),IR(52, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5300,IR(0, 0),IR(18235, 11)/* NonUniform */,IR(75, 1),IR(99, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5355,IR(0, 0),IR(18260, 16)/* RestrictPointer */,IR(76, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5356,IR(0, 0),IR(18295, 15)/* AliasedPointer */,IR(77, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5358,IR(0, 1),IR(18328, 15)/* MemberOffsetNV */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5386,IR(0, 0),IR(18343, 30)/* HitObjectShaderRecordBufferNV */,IR(0, 0),IR(131, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5389,IR(0, 0),IR(18373, 31)/* HitObjectShaderRecordBufferEXT */,IR(0, 0),IR(132, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5397,IR(0, 1),IR(18404, 7)/* BankNV */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5398,IR(0, 0),IR(18411, 18)/* BindlessSamplerNV */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5399,IR(0, 0),IR(18429, 16)/* BindlessImageNV */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5400,IR(0, 0),IR(18445, 15)/* BoundSamplerNV */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5401,IR(0, 0),IR(18460, 13)/* BoundImageNV */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5599,IR(0, 1),IR(18473, 14)/* SIMTCallINTEL */,IR(0, 0),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5602,IR(0, 0),IR(18487, 26)/* ReferencedIndirectlyINTEL */,IR(0, 0),IR(135, 1),IR(101, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5607,IR(11, 1),IR(18513, 13)/* ClobberINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5608,IR(0, 0),IR(18526, 17)/* SideEffectsINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5624,IR(0, 0),IR(18543, 27)/* VectorComputeVariableINTEL */,IR(0, 0),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5625,IR(0, 1),IR(18570, 21)/* FuncParamIOKindINTEL */,IR(0, 0),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5626,IR(0, 0),IR(18591, 27)/* VectorComputeFunctionINTEL */,IR(0, 0),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5627,IR(0, 0),IR(18618, 15)/* StackCallINTEL */,IR(0, 0),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5628,IR(0, 1),IR(18633, 26)/* GlobalVariableOffsetINTEL */,IR(0, 0),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5634,IR(10, 1),IR(18659, 14)/* CounterBuffer */,IR(78, 1),IR(1, 0),IR(185, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5635,IR(11, 1),IR(18697, 13)/* UserSemantic */,IR(79, 1),IR(1, 0),IR(185, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5636,IR(11, 1),IR(18729, 15)/* UserTypeGOOGLE */,IR(0, 0),IR(1, 0),IR(186, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5822,IR(12, 2),IR(18744, 26)/* FunctionRoundingModeINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5823,IR(14, 2),IR(18801, 24)/* FunctionDenormModeINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5825,IR(0, 0),IR(18825, 15)/* RegisterALTERA */,IR(80, 1),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5826,IR(11, 1),IR(18854, 13)/* MemoryALTERA */,IR(81, 1),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5827,IR(0, 1),IR(18879, 15)/* NumbanksALTERA */,IR(82, 1),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5828,IR(0, 1),IR(18908, 16)/* BankwidthALTERA */,IR(83, 1),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5829,IR(0, 1),IR(18939, 23)/* MaxPrivateCopiesALTERA */,IR(84, 1),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5830,IR(0, 0),IR(18984, 17)/* SinglepumpALTERA */,IR(85, 1),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5831,IR(0, 0),IR(19017, 17)/* DoublepumpALTERA */,IR(86, 1),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5832,IR(0, 1),IR(19050, 20)/* MaxReplicatesALTERA */,IR(87, 1),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5833,IR(0, 0),IR(19089, 21)/* SimpleDualPortALTERA */,IR(88, 1),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5834,IR(16, 2),IR(19130, 12)/* MergeALTERA */,IR(89, 1),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5835,IR(18, 1),IR(19195, 15)/* BankBitsALTERA */,IR(90, 1),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5836,IR(0, 1),IR(19224, 21)/* ForcePow2DepthALTERA */,IR(91, 1),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5883,IR(0, 1),IR(19265, 17)/* StridesizeALTERA */,IR(92, 1),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5884,IR(0, 1),IR(19298, 15)/* WordsizeALTERA */,IR(93, 1),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5885,IR(0, 0),IR(19327, 19)/* TrueDualPortALTERA */,IR(94, 1),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5899,IR(0, 0),IR(19364, 20)/* BurstCoalesceALTERA */,IR(95, 1),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5900,IR(0, 1),IR(19403, 16)/* CacheSizeALTERA */,IR(96, 1),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5901,IR(0, 0),IR(19434, 29)/* DontStaticallyCoalesceALTERA */,IR(97, 1),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5902,IR(0, 1),IR(19491, 15)/* PrefetchALTERA */,IR(98, 1),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5905,IR(0, 0),IR(19520, 18)/* StallEnableALTERA */,IR(99, 1),IR(108, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5907,IR(0, 0),IR(19555, 26)/* FuseLoopsInFunctionALTERA */,IR(100, 1),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5909,IR(1, 2),IR(19606, 20)/* MathOpDSPModeALTERA */,IR(101, 1),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5914,IR(10, 1),IR(19645, 16)/* AliasScopeINTEL */,IR(0, 0),IR(142, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5915,IR(10, 1),IR(19661, 13)/* NoAliasINTEL */,IR(0, 0),IR(142, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5917,IR(0, 1),IR(19674, 25)/* InitiationIntervalALTERA */,IR(102, 1),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5918,IR(0, 1),IR(19723, 21)/* MaxConcurrencyALTERA */,IR(103, 1),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5919,IR(0, 1),IR(19764, 21)/* PipelineEnableALTERA */,IR(104, 1),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5921,IR(0, 1),IR(19805, 21)/* BufferLocationALTERA */,IR(105, 1),IR(144, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5944,IR(0, 1),IR(19846, 20)/* IOPipeStorageALTERA */,IR(106, 1),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6080,IR(19, 2),IR(19919, 31)/* FunctionFloatingPointModeINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6085,IR(0, 0),IR(19950, 25)/* SingleElementVectorINTEL */,IR(0, 0),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6087,IR(0, 0),IR(19975, 35)/* VectorComputeCallableFunctionINTEL */,IR(0, 0),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6140,IR(0, 0),IR(20010, 18)/* MediaBlockIOINTEL */,IR(0, 0),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6151,IR(0, 0),IR(20028, 16)/* StallFreeALTERA */,IR(107, 1),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6170,IR(21, 1),IR(20090, 26)/* FPMaxErrorDecorationINTEL */,IR(0, 0),IR(147, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6172,IR(0, 1),IR(20116, 26)/* LatencyControlLabelALTERA */,IR(108, 1),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6173,IR(22, 3),IR(20167, 31)/* LatencyControlConstraintALTERA */,IR(109, 1),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6175,IR(0, 0),IR(20228, 28)/* ConduitKernelArgumentALTERA */,IR(110, 1),IR(149, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6176,IR(0, 0),IR(20283, 32)/* RegisterMapKernelArgumentALTERA */,IR(111, 1),IR(149, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6177,IR(0, 1),IR(20346, 34)/* MMHostInterfaceAddressWidthALTERA */,IR(112, 1),IR(149, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6178,IR(0, 1),IR(20413, 31)/* MMHostInterfaceDataWidthALTERA */,IR(113, 1),IR(149, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6179,IR(0, 1),IR(20474, 29)/* MMHostInterfaceLatencyALTERA */,IR(114, 1),IR(149, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6180,IR(25, 1),IR(20565, 35)/* MMHostInterfaceReadWriteModeALTERA */,IR(115, 1),IR(149, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6181,IR(0, 1),IR(20634, 30)/* MMHostInterfaceMaxBurstALTERA */,IR(116, 1),IR(149, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6182,IR(0, 1),IR(20693, 33)/* MMHostInterfaceWaitRequestALTERA */,IR(117, 1),IR(149, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6183,IR(0, 0),IR(20758, 27)/* StableKernelArgumentALTERA */,IR(118, 1),IR(149, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6188,IR(26, 2),IR(20850, 16)/* HostAccessINTEL */,IR(0, 0),IR(150, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6190,IR(28, 1),IR(20913, 15)/* InitModeALTERA */,IR(119, 1),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6191,IR(0, 1),IR(20942, 29)/* ImplementInRegisterMapALTERA */,IR(120, 1),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6247,IR(10, 1),IR(20999, 17)/* ConditionalINTEL */,IR(0, 0),IR(113, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6442,IR(29, 2),IR(21052, 22)/* CacheControlLoadINTEL */,IR(0, 0),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6443,IR(31, 2),IR(21111, 23)/* CacheControlStoreINTEL */,IR(0, 0),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {0,IR(0, 0),IR(21134, 3)/* 1D */,IR(0, 0),IR(73, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {1,IR(0, 0),IR(21137, 3)/* 2D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {2,IR(0, 0),IR(21140, 3)/* 3D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {3,IR(0, 0),IR(21143, 5)/* Cube */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {4,IR(0, 0),IR(21148, 5)/* Rect */,IR(0, 0),IR(72, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {5,IR(0, 0),IR(21153, 7)/* Buffer */,IR(0, 0),IR(74, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {6,IR(0, 0),IR(21160, 12)/* SubpassData */,IR(0, 0),IR(97, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {4173,IR(0, 0),IR(21172, 17)/* TileImageDataEXT */,IR(0, 0),IR(153, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {0,IR(0, 1),IR(21189, 12)/* Invocations */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {1,IR(0, 0),IR(21201, 13)/* SpacingEqual */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {2,IR(0, 0),IR(21214, 22)/* SpacingFractionalEven */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {3,IR(0, 0),IR(21236, 21)/* SpacingFractionalOdd */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4,IR(0, 0),IR(21257, 14)/* VertexOrderCw */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5,IR(0, 0),IR(21271, 15)/* VertexOrderCcw */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6,IR(0, 0),IR(21286, 19)/* PixelCenterInteger */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {7,IR(0, 0),IR(21305, 16)/* OriginUpperLeft */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {8,IR(0, 0),IR(21321, 16)/* OriginLowerLeft */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {9,IR(0, 0),IR(21337, 19)/* EarlyFragmentTests */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {10,IR(0, 0),IR(21356, 10)/* PointMode */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {11,IR(0, 0),IR(21366, 4)/* Xfb */,IR(0, 0),IR(122, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {12,IR(0, 0),IR(21370, 15)/* DepthReplacing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {14,IR(0, 0),IR(21385, 13)/* DepthGreater */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {15,IR(0, 0),IR(21398, 10)/* DepthLess */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {16,IR(0, 0),IR(21408, 15)/* DepthUnchanged */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {17,IR(22, 3),IR(21423, 10)/* LocalSize */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {18,IR(22, 3),IR(21433, 14)/* LocalSizeHint */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {19,IR(0, 0),IR(21447, 12)/* InputPoints */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {20,IR(0, 0),IR(21459, 11)/* InputLines */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {21,IR(0, 0),IR(21470, 20)/* InputLinesAdjacency */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {22,IR(0, 0),IR(21490, 10)/* Triangles */,IR(0, 0),IR(12, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {23,IR(0, 0),IR(21500, 24)/* InputTrianglesAdjacency */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {24,IR(0, 0),IR(21524, 6)/* Quads */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {25,IR(0, 0),IR(21530, 9)/* Isolines */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {26,IR(0, 1),IR(21539, 15)/* OutputVertices */,IR(0, 0),IR(154, 4),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {27,IR(0, 0),IR(21554, 13)/* OutputPoints */,IR(0, 0),IR(158, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {28,IR(0, 0),IR(21567, 16)/* OutputLineStrip */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {29,IR(0, 0),IR(21583, 20)/* OutputTriangleStrip */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {30,IR(0, 1),IR(21603, 12)/* VecTypeHint */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {31,IR(0, 0),IR(21615, 15)/* ContractionOff */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {33,IR(0, 0),IR(21630, 12)/* Initializer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {34,IR(0, 0),IR(21642, 10)/* Finalizer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {35,IR(0, 1),IR(6249, 13)/* SubgroupSize */,IR(0, 0),IR(161, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {36,IR(0, 1),IR(21652, 22)/* SubgroupsPerWorkgroup */,IR(0, 0),IR(161, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {37,IR(10, 1),IR(21674, 24)/* SubgroupsPerWorkgroupId */,IR(0, 0),IR(161, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {38,IR(33, 3),IR(21698, 12)/* LocalSizeId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {39,IR(33, 3),IR(21710, 16)/* LocalSizeHintId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4169,IR(0, 0),IR(21726, 34)/* NonCoherentColorAttachmentReadEXT */,IR(0, 0),IR(153, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4170,IR(0, 0),IR(21760, 34)/* NonCoherentDepthAttachmentReadEXT */,IR(0, 0),IR(162, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4171,IR(0, 0),IR(21794, 36)/* NonCoherentStencilAttachmentReadEXT */,IR(0, 0),IR(163, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4421,IR(0, 0),IR(21830, 30)/* SubgroupUniformControlFlowKHR */,IR(0, 0),IR(3, 1),IR(187, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4446,IR(0, 0),IR(21860, 18)/* PostDepthCoverage */,IR(0, 0),IR(164, 1),IR(45, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4459,IR(0, 1),IR(10497, 15)/* DenormPreserve */,IR(0, 0),IR(165, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4460,IR(0, 1),IR(10512, 18)/* DenormFlushToZero */,IR(0, 0),IR(166, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4461,IR(0, 1),IR(10530, 25)/* SignedZeroInfNanPreserve */,IR(0, 0),IR(167, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4462,IR(0, 1),IR(10555, 16)/* RoundingModeRTE */,IR(0, 0),IR(168, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4463,IR(0, 1),IR(10571, 16)/* RoundingModeRTZ */,IR(0, 0),IR(169, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4489,IR(0, 0),IR(21878, 34)/* NonCoherentTileAttachmentReadQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4490,IR(22, 3),IR(21912, 20)/* TileShadingRateQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5017,IR(0, 0),IR(21932, 29)/* EarlyAndLateFragmentTestsAMD */,IR(0, 0),IR(3, 1),IR(188, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5027,IR(0, 0),IR(21961, 23)/* StencilRefReplacingEXT */,IR(0, 0),IR(42, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5069,IR(0, 0),IR(21984, 15)/* CoalescingAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5070,IR(10, 1),IR(21999, 15)/* IsApiEntryAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5071,IR(10, 1),IR(22014, 21)/* MaxNodeRecursionAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5072,IR(33, 3),IR(22035, 24)/* StaticNumWorkgroupsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5073,IR(10, 1),IR(7142, 16)/* ShaderIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5077,IR(33, 3),IR(22059, 21)/* MaxNumWorkgroupsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5079,IR(0, 0),IR(22080, 28)/* StencilRefUnchangedFrontAMD */,IR(0, 0),IR(42, 1),IR(189, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5080,IR(0, 0),IR(22108, 26)/* StencilRefGreaterFrontAMD */,IR(0, 0),IR(42, 1),IR(189, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5081,IR(0, 0),IR(22134, 23)/* StencilRefLessFrontAMD */,IR(0, 0),IR(42, 1),IR(189, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5082,IR(0, 0),IR(22157, 27)/* StencilRefUnchangedBackAMD */,IR(0, 0),IR(42, 1),IR(189, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5083,IR(0, 0),IR(22184, 25)/* StencilRefGreaterBackAMD */,IR(0, 0),IR(42, 1),IR(189, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5084,IR(0, 0),IR(22209, 22)/* StencilRefLessBackAMD */,IR(0, 0),IR(42, 1),IR(189, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5088,IR(0, 0),IR(22231, 19)/* QuadDerivativesKHR */,IR(0, 0),IR(170, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5089,IR(0, 0),IR(22250, 20)/* RequireFullQuadsKHR */,IR(0, 0),IR(170, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5102,IR(36, 2),IR(22270, 20)/* SharesInputWithAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5269,IR(0, 0),IR(22290, 15)/* OutputLinesEXT */,IR(121, 1),IR(128, 2),IR(183, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5270,IR(0, 1),IR(22319, 20)/* OutputPrimitivesEXT */,IR(122, 1),IR(128, 2),IR(183, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5289,IR(0, 0),IR(22358, 24)/* DerivativeGroupQuadsKHR */,IR(123, 1),IR(171, 1),IR(74, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5290,IR(0, 0),IR(22405, 25)/* DerivativeGroupLinearKHR */,IR(124, 1),IR(172, 1),IR(74, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5298,IR(0, 0),IR(22454, 19)/* OutputTrianglesEXT */,IR(125, 1),IR(128, 2),IR(183, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5366,IR(0, 0),IR(22491, 25)/* PixelInterlockOrderedEXT */,IR(0, 0),IR(173, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5367,IR(0, 0),IR(22516, 27)/* PixelInterlockUnorderedEXT */,IR(0, 0),IR(173, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5368,IR(0, 0),IR(22543, 26)/* SampleInterlockOrderedEXT */,IR(0, 0),IR(174, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5369,IR(0, 0),IR(22569, 28)/* SampleInterlockUnorderedEXT */,IR(0, 0),IR(174, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5370,IR(0, 0),IR(22597, 31)/* ShadingRateInterlockOrderedEXT */,IR(0, 0),IR(175, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5371,IR(0, 0),IR(22628, 33)/* ShadingRateInterlockUnorderedEXT */,IR(0, 0),IR(175, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5427,IR(0, 0),IR(12803, 23)/* Shader64BitIndexingEXT */,IR(0, 0),IR(176, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5618,IR(0, 1),IR(22661, 27)/* SharedLocalMemorySizeINTEL */,IR(0, 0),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5620,IR(0, 1),IR(22688, 21)/* RoundingModeRTPINTEL */,IR(0, 0),IR(177, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5621,IR(0, 1),IR(22709, 21)/* RoundingModeRTNINTEL */,IR(0, 0),IR(177, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5622,IR(0, 1),IR(22730, 26)/* FloatingPointModeALTINTEL */,IR(0, 0),IR(177, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5623,IR(0, 1),IR(22756, 27)/* FloatingPointModeIEEEINTEL */,IR(0, 0),IR(177, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5893,IR(22, 3),IR(22783, 22)/* MaxWorkgroupSizeINTEL */,IR(0, 0),IR(178, 1),IR(118, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5894,IR(0, 1),IR(22805, 16)/* MaxWorkDimINTEL */,IR(0, 0),IR(178, 1),IR(118, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5895,IR(0, 0),IR(22821, 20)/* NoGlobalOffsetINTEL */,IR(0, 0),IR(178, 1),IR(118, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5896,IR(0, 1),IR(22841, 22)/* NumSIMDWorkitemsINTEL */,IR(0, 0),IR(109, 1),IR(118, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5903,IR(0, 1),IR(22863, 28)/* SchedulerTargetFmaxMhzINTEL */,IR(0, 0),IR(109, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6023,IR(0, 0),IR(22891, 24)/* MaximallyReconvergesKHR */,IR(0, 0),IR(3, 1),IR(191, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6028,IR(36, 2),IR(22915, 18)/* FPFastMathDefault */,IR(0, 0),IR(179, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6154,IR(0, 1),IR(22933, 24)/* StreamingInterfaceINTEL */,IR(0, 0),IR(109, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6160,IR(0, 1),IR(22957, 26)/* RegisterMapInterfaceINTEL */,IR(0, 0),IR(180, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6417,IR(0, 1),IR(22983, 23)/* NamedBarrierCountINTEL */,IR(0, 0),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6461,IR(0, 1),IR(23006, 22)/* MaximumRegistersINTEL */,IR(0, 0),IR(181, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6462,IR(10, 1),IR(23028, 24)/* MaximumRegistersIdINTEL */,IR(0, 0),IR(181, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6463,IR(38, 1),IR(23103, 27)/* NamedMaximumRegistersINTEL */,IR(0, 0),IR(181, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {0,IR(0, 0),IR(23130, 7)/* Vertex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {1,IR(0, 0),IR(23137, 20)/* TessellationControl */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {2,IR(0, 0),IR(23157, 23)/* TessellationEvaluation */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {3,IR(0, 0),IR(5730, 9)/* Geometry */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {4,IR(0, 0),IR(16322, 9)/* Fragment */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5,IR(0, 0),IR(23180, 10)/* GLCompute */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {6,IR(0, 0),IR(5497, 7)/* Kernel */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5267,IR(0, 0),IR(23190, 7)/* TaskNV */,IR(0, 0),IR(51, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5268,IR(0, 0),IR(23197, 7)/* MeshNV */,IR(0, 0),IR(51, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5313,IR(0, 0),IR(23204, 17)/* RayGenerationKHR */,IR(126, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5314,IR(0, 0),IR(23237, 16)/* IntersectionKHR */,IR(127, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5315,IR(0, 0),IR(23268, 10)/* AnyHitKHR */,IR(128, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5316,IR(0, 0),IR(23287, 14)/* ClosestHitKHR */,IR(129, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5317,IR(0, 0),IR(23314, 8)/* MissKHR */,IR(130, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5318,IR(0, 0),IR(23329, 12)/* CallableKHR */,IR(131, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5364,IR(0, 0),IR(23352, 8)/* TaskEXT */,IR(0, 0),IR(54, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5365,IR(0, 0),IR(23360, 8)/* MeshEXT */,IR(0, 0),IR(54, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {0,IR(0, 0),IR(23368, 9)/* Preserve */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPDENORM_MODE
  {1,IR(0, 0),IR(23377, 12)/* FlushToZero */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPDENORM_MODE
  {0,IR(0, 0),IR(23389, 12)/* BFloat16KHR */,IR(0, 0),IR(90, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {4214,IR(0, 0),IR(23401, 14)/* Float8E4M3EXT */,IR(0, 0),IR(115, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {4215,IR(0, 0),IR(23415, 14)/* Float8E5M2EXT */,IR(0, 0),IR(115, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {0,IR(0, 0),IR(23429, 5)/* IEEE */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPOPERATION_MODE
  {1,IR(0, 0),IR(23434, 4)/* ALT */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPOPERATION_MODE
  {0,IR(0, 0),IR(15918, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {1,IR(0, 0),IR(23438, 7)/* NotNaN */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {2,IR(0, 0),IR(23445, 7)/* NotInf */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {4,IR(0, 0),IR(23452, 4)/* NSZ */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {8,IR(0, 0),IR(23456, 11)/* AllowRecip */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {16,IR(0, 0),IR(23467, 5)/* Fast */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {65536,IR(0, 0),IR(23472, 14)/* AllowContract */,IR(132, 1),IR(182, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {131072,IR(0, 0),IR(23509, 13)/* AllowReassoc */,IR(133, 1),IR(182, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {262144,IR(0, 0),IR(23540, 15)/* AllowTransform */,IR(0, 0),IR(179, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {0,IR(0, 0),IR(23555, 4)/* RTE */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {1,IR(0, 0),IR(23559, 4)/* RTZ */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {2,IR(0, 0),IR(23563, 4)/* RTP */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {3,IR(0, 0),IR(23567, 4)/* RTN */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {1,IR(0, 0),IR(23571, 16)/* Vertical2Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {2,IR(0, 0),IR(23587, 16)/* Vertical4Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {4,IR(0, 0),IR(23603, 18)/* Horizontal2Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {8,IR(0, 0),IR(23621, 18)/* Horizontal4Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {0,IR(0, 0),IR(15918, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {1,IR(0, 0),IR(23639, 7)/* Inline */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {2,IR(0, 0),IR(23646, 11)/* DontInline */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {4,IR(0, 0),IR(23657, 5)/* Pure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {8,IR(0, 0),IR(23662, 6)/* Const */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {65536,IR(0, 0),IR(14800, 11)/* OptNoneEXT */,IR(67, 1),IR(184, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {0,IR(0, 0),IR(23668, 5)/* Zext */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {1,IR(0, 0),IR(23673, 5)/* Sext */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {2,IR(0, 0),IR(23678, 6)/* ByVal */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {3,IR(0, 0),IR(23684, 5)/* Sret */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {4,IR(0, 0),IR(23689, 8)/* NoAlias */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {5,IR(0, 0),IR(23697, 10)/* NoCapture */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {6,IR(0, 0),IR(23707, 8)/* NoWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {7,IR(0, 0),IR(23715, 12)/* NoReadWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {5940,IR(0, 0),IR(23727, 21)/* RuntimeAlignedALTERA */,IR(134, 1),IR(185, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {0,IR(0, 0),IR(23768, 7)/* Reduce */,IR(0, 0),IR(186, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {1,IR(0, 0),IR(23775, 14)/* InclusiveScan */,IR(0, 0),IR(186, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {2,IR(0, 0),IR(23789, 14)/* ExclusiveScan */,IR(0, 0),IR(186, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {3,IR(0, 0),IR(23803, 16)/* ClusteredReduce */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {6,IR(0, 0),IR(23819, 21)/* PartitionedReduceEXT */,IR(135, 1),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {7,IR(0, 0),IR(23860, 28)/* PartitionedInclusiveScanEXT */,IR(136, 1),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {8,IR(0, 0),IR(23915, 28)/* PartitionedExclusiveScanEXT */,IR(137, 1),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {0,IR(0, 0),IR(23970, 10)/* NoneINTEL */,IR(0, 0),IR(150, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {1,IR(0, 0),IR(23980, 10)/* ReadINTEL */,IR(0, 0),IR(150, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {2,IR(0, 0),IR(23990, 11)/* WriteINTEL */,IR(0, 0),IR(150, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {3,IR(0, 0),IR(24001, 15)/* ReadWriteINTEL */,IR(0, 0),IR(150, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {0,IR(0, 0),IR(15918, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {1,IR(10, 1),IR(24016, 5)/* Bias */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {2,IR(10, 1),IR(24021, 4)/* Lod */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {4,IR(36, 2),IR(24025, 5)/* Grad */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {8,IR(10, 1),IR(24030, 12)/* ConstOffset */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {16,IR(10, 1),IR(17325, 7)/* Offset */,IR(0, 0),IR(191, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {32,IR(10, 1),IR(24042, 13)/* ConstOffsets */,IR(0, 0),IR(191, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {64,IR(10, 1),IR(17122, 7)/* Sample */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {128,IR(10, 1),IR(9330, 7)/* MinLod */,IR(0, 0),IR(192, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {256,IR(4, 1),IR(24055, 19)/* MakeTexelAvailable */,IR(138, 1),IR(193, 1),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {512,IR(4, 1),IR(24096, 17)/* MakeTexelVisible */,IR(139, 1),IR(193, 1),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {1024,IR(0, 0),IR(24133, 16)/* NonPrivateTexel */,IR(140, 1),IR(193, 1),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {2048,IR(0, 0),IR(24168, 14)/* VolatileTexel */,IR(141, 1),IR(193, 1),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {4096,IR(0, 0),IR(24199, 11)/* SignExtend */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {8192,IR(0, 0),IR(24210, 11)/* ZeroExtend */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {16384,IR(0, 0),IR(24221, 12)/* Nontemporal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {65536,IR(10, 1),IR(24233, 8)/* Offsets */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {0,IR(0, 0),IR(24241, 10)/* SnormInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {1,IR(0, 0),IR(24251, 11)/* SnormInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {2,IR(0, 0),IR(24262, 10)/* UnormInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {3,IR(0, 0),IR(24272, 11)/* UnormInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {4,IR(0, 0),IR(24283, 14)/* UnormShort565 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {5,IR(0, 0),IR(24297, 14)/* UnormShort555 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {6,IR(0, 0),IR(24311, 15)/* UnormInt101010 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {7,IR(0, 0),IR(24326, 11)/* SignedInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {8,IR(0, 0),IR(24337, 12)/* SignedInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {9,IR(0, 0),IR(24349, 12)/* SignedInt32 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {10,IR(0, 0),IR(24361, 13)/* UnsignedInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {11,IR(0, 0),IR(24374, 14)/* UnsignedInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {12,IR(0, 0),IR(24388, 14)/* UnsignedInt32 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {13,IR(0, 0),IR(24402, 10)/* HalfFloat */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {14,IR(0, 0),IR(15815, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {15,IR(0, 0),IR(24412, 11)/* UnormInt24 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {16,IR(0, 0),IR(24423, 17)/* UnormInt101010_2 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {17,IR(0, 0),IR(24440, 16)/* UnormInt10X6EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {19,IR(0, 0),IR(24456, 20)/* UnsignedIntRaw10EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {20,IR(0, 0),IR(24476, 20)/* UnsignedIntRaw12EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {21,IR(0, 0),IR(24496, 20)/* UnormInt2_101010EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {22,IR(0, 0),IR(24516, 19)/* UnsignedInt10X6EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {23,IR(0, 0),IR(24535, 19)/* UnsignedInt12X4EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {24,IR(0, 0),IR(24554, 19)/* UnsignedInt14X2EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {25,IR(0, 0),IR(24573, 16)/* UnormInt12X4EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {26,IR(0, 0),IR(24589, 16)/* UnormInt14X2EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {0,IR(0, 0),IR(24605, 2)/* R */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {1,IR(0, 0),IR(24607, 2)/* A */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {2,IR(0, 0),IR(24609, 3)/* RG */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {3,IR(0, 0),IR(24612, 3)/* RA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {4,IR(0, 0),IR(24615, 4)/* RGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {5,IR(0, 0),IR(24619, 5)/* RGBA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {6,IR(0, 0),IR(24624, 5)/* BGRA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {7,IR(0, 0),IR(24629, 5)/* ARGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {8,IR(0, 0),IR(24634, 10)/* Intensity */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {9,IR(0, 0),IR(24644, 10)/* Luminance */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {10,IR(0, 0),IR(24654, 3)/* Rx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {11,IR(0, 0),IR(24657, 4)/* RGx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {12,IR(0, 0),IR(24661, 5)/* RGBx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {13,IR(0, 0),IR(24666, 6)/* Depth */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {14,IR(0, 0),IR(24672, 13)/* DepthStencil */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {15,IR(0, 0),IR(24685, 5)/* sRGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {16,IR(0, 0),IR(24690, 6)/* sRGBx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {17,IR(0, 0),IR(24696, 6)/* sRGBA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {18,IR(0, 0),IR(24702, 6)/* sBGRA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {19,IR(0, 0),IR(24708, 5)/* ABGR */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {0,IR(0, 0),IR(24713, 28)/* InitOnDeviceReprogramALTERA */,IR(142, 1),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {1,IR(0, 0),IR(24768, 24)/* InitOnDeviceResetALTERA */,IR(143, 1),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {0,IR(0, 0),IR(24815, 7)/* NoWait */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {1,IR(0, 0),IR(24822, 11)/* WaitKernel */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {2,IR(0, 0),IR(24833, 14)/* WaitWorkGroup */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {0,IR(0, 0),IR(15918, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {1,IR(0, 0),IR(24847, 12)/* CmdExecTime */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {0,IR(0, 0),IR(15918, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {1,IR(0, 0),IR(24859, 13)/* MayUsePrintf */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {0,IR(0, 0),IR(24872, 7)/* Export */,IR(0, 0),IR(125, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {1,IR(0, 0),IR(24879, 7)/* Import */,IR(0, 0),IR(125, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {2,IR(0, 0),IR(24886, 12)/* LinkOnceODR */,IR(0, 0),IR(125, 1),IR(192, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {0,IR(0, 0),IR(24898, 14)/* UncachedINTEL */,IR(0, 0),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {1,IR(0, 0),IR(24912, 12)/* CachedINTEL */,IR(0, 0),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {2,IR(0, 0),IR(24924, 15)/* StreamingINTEL */,IR(0, 0),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {3,IR(0, 0),IR(24939, 25)/* InvalidateAfterReadINTEL */,IR(0, 0),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {4,IR(0, 0),IR(24964, 17)/* ConstCachedINTEL */,IR(0, 0),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {0,IR(0, 0),IR(15918, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {1,IR(0, 0),IR(24981, 7)/* Unroll */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {2,IR(0, 0),IR(24988, 11)/* DontUnroll */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {4,IR(0, 0),IR(24999, 19)/* DependencyInfinite */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {8,IR(0, 1),IR(25018, 17)/* DependencyLength */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {16,IR(0, 1),IR(25035, 14)/* MinIterations */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {32,IR(0, 1),IR(25049, 14)/* MaxIterations */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {64,IR(0, 1),IR(25063, 18)/* IterationMultiple */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {128,IR(0, 1),IR(25081, 10)/* PeelCount */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {256,IR(0, 1),IR(25091, 13)/* PartialCount */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {65536,IR(0, 1),IR(19674, 25)/* InitiationIntervalALTERA */,IR(102, 1),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {131072,IR(0, 1),IR(19723, 21)/* MaxConcurrencyALTERA */,IR(103, 1),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {262144,IR(0, 1),IR(25104, 22)/* DependencyArrayALTERA */,IR(144, 1),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {524288,IR(0, 1),IR(19764, 21)/* PipelineEnableALTERA */,IR(104, 1),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {1048576,IR(0, 1),IR(25147, 19)/* LoopCoalesceALTERA */,IR(145, 1),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {2097152,IR(0, 1),IR(25184, 22)/* MaxInterleavingALTERA */,IR(146, 1),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {4194304,IR(0, 1),IR(25227, 27)/* SpeculatedIterationsALTERA */,IR(147, 1),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {8388608,IR(0, 0),IR(25280, 15)/* NoFusionALTERA */,IR(148, 1),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {16777216,IR(0, 1),IR(25309, 16)/* LoopCountALTERA */,IR(149, 1),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {33554432,IR(0, 1),IR(25340, 27)/* MaxReinvocationDelayALTERA */,IR(150, 1),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {0,IR(0, 0),IR(15918, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {1,IR(0, 0),IR(25393, 29)/* MatrixASignedComponentsINTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {2,IR(0, 0),IR(25422, 29)/* MatrixBSignedComponentsINTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {4,IR(0, 0),IR(25451, 21)/* MatrixCBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {8,IR(0, 0),IR(25472, 26)/* MatrixResultBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {16,IR(0, 0),IR(25498, 23)/* MatrixAPackedInt8INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {32,IR(0, 0),IR(25521, 23)/* MatrixBPackedInt8INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {64,IR(0, 0),IR(25544, 23)/* MatrixAPackedInt4INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {128,IR(0, 0),IR(25567, 23)/* MatrixBPackedInt4INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {256,IR(0, 0),IR(25590, 17)/* MatrixATF32INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {512,IR(0, 0),IR(25607, 17)/* MatrixBTF32INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {1024,IR(0, 0),IR(25624, 26)/* MatrixAPackedFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {2048,IR(0, 0),IR(25650, 26)/* MatrixBPackedFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {4096,IR(0, 0),IR(25676, 27)/* MatrixAPackedBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {8192,IR(0, 0),IR(25703, 27)/* MatrixBPackedBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {0,IR(0, 0),IR(15918, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {1,IR(0, 0),IR(17156, 9)/* Volatile */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {2,IR(0, 1),IR(25730, 8)/* Aligned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {4,IR(0, 0),IR(24221, 12)/* Nontemporal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {8,IR(4, 1),IR(25738, 21)/* MakePointerAvailable */,IR(151, 1),IR(193, 1),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {16,IR(4, 1),IR(25783, 19)/* MakePointerVisible */,IR(152, 1),IR(193, 1),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {32,IR(0, 0),IR(25824, 18)/* NonPrivatePointer */,IR(153, 1),IR(193, 1),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {65536,IR(10, 1),IR(25863, 20)/* AliasScopeINTELMask */,IR(0, 0),IR(142, 1),IR(127, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {131072,IR(10, 1),IR(25883, 17)/* NoAliasINTELMask */,IR(0, 0),IR(142, 1),IR(127, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {0,IR(0, 0),IR(25900, 7)/* Simple */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {1,IR(0, 0),IR(25907, 8)/* GLSL450 */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {2,IR(0, 0),IR(25915, 7)/* OpenCL */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {3,IR(0, 0),IR(25922, 7)/* Vulkan */,IR(154, 1),IR(193, 1),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {0,IR(0, 0),IR(25939, 8)/* Relaxed */,IR(155, 1),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {2,IR(0, 0),IR(25947, 8)/* Acquire */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {4,IR(0, 0),IR(25955, 8)/* Release */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {8,IR(0, 0),IR(25963, 15)/* AcquireRelease */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {16,IR(0, 0),IR(25978, 23)/* SequentiallyConsistent */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {64,IR(0, 0),IR(26001, 14)/* UniformMemory */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {128,IR(0, 0),IR(26015, 15)/* SubgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {256,IR(0, 0),IR(26030, 16)/* WorkgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {512,IR(0, 0),IR(26046, 21)/* CrossWorkgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {1024,IR(0, 0),IR(26067, 20)/* AtomicCounterMemory */,IR(0, 0),IR(83, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {2048,IR(0, 0),IR(26087, 12)/* ImageMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {4096,IR(0, 0),IR(26099, 13)/* OutputMemory */,IR(156, 1),IR(193, 1),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {8192,IR(0, 0),IR(26128, 14)/* MakeAvailable */,IR(157, 1),IR(193, 1),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {16384,IR(0, 0),IR(26159, 12)/* MakeVisible */,IR(158, 1),IR(193, 1),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {32768,IR(0, 0),IR(17156, 9)/* Volatile */,IR(0, 0),IR(193, 1),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {0,IR(0, 0),IR(26186, 10)/* AutoINTEL */,IR(0, 0),IR(181, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS
  {0,IR(0, 0),IR(26196, 5)/* WRAP */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {1,IR(0, 0),IR(26201, 4)/* SAT */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {2,IR(0, 0),IR(26205, 9)/* SAT_ZERO */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {3,IR(0, 0),IR(26214, 8)/* SAT_SYM */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {0,IR(0, 0),IR(26222, 25)/* PackedVectorFormat4x8Bit */,IR(159, 1),IR(1, 0),IR(144, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {0,IR(0, 0),IR(26275, 4)/* TRN */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {1,IR(0, 0),IR(26279, 9)/* TRN_ZERO */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {2,IR(0, 0),IR(26288, 4)/* RND */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {3,IR(0, 0),IR(26292, 9)/* RND_ZERO */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {4,IR(0, 0),IR(26301, 8)/* RND_INF */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {5,IR(0, 0),IR(26309, 12)/* RND_MIN_INF */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {6,IR(0, 0),IR(26321, 9)/* RND_CONV */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {7,IR(0, 0),IR(26330, 13)/* RND_CONV_ODD */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {0,IR(0, 0),IR(15918, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {1,IR(0, 0),IR(26343, 25)/* RobustnessPerComponentNV */,IR(0, 0),IR(196, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {2,IR(0, 0),IR(26368, 23)/* RobustnessPerElementNV */,IR(0, 0),IR(196, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {0,IR(0, 0),IR(16670, 8)/* NoneKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {1,IR(0, 0),IR(26391, 10)/* OpaqueKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {2,IR(0, 0),IR(26401, 12)/* NoOpaqueKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {4,IR(0, 0),IR(26413, 23)/* TerminateOnFirstHitKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {8,IR(0, 0),IR(26436, 24)/* SkipClosestHitShaderKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {16,IR(0, 0),IR(26460, 27)/* CullBackFacingTrianglesKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {32,IR(0, 0),IR(26487, 28)/* CullFrontFacingTrianglesKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {64,IR(0, 0),IR(26515, 14)/* CullOpaqueKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {128,IR(0, 0),IR(26529, 16)/* CullNoOpaqueKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {256,IR(0, 0),IR(26545, 17)/* SkipTrianglesKHR */,IR(160, 1),IR(197, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {512,IR(0, 0),IR(26586, 13)/* SkipAABBsKHR */,IR(0, 0),IR(197, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {1024,IR(0, 0),IR(26599, 30)/* ForceOpacityMicromap2StateEXT */,IR(0, 0),IR(198, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {0,IR(0, 0),IR(26629, 41)/* RayQueryCandidateIntersectionTriangleKHR */,IR(0, 0),IR(199, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {1,IR(0, 0),IR(26670, 37)/* RayQueryCandidateIntersectionAABBKHR */,IR(0, 0),IR(199, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {0,IR(0, 0),IR(26707, 37)/* RayQueryCommittedIntersectionNoneKHR */,IR(0, 0),IR(199, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {1,IR(0, 0),IR(26744, 41)/* RayQueryCommittedIntersectionTriangleKHR */,IR(0, 0),IR(199, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {2,IR(0, 0),IR(26785, 42)/* RayQueryCommittedIntersectionGeneratedKHR */,IR(0, 0),IR(199, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {0,IR(0, 0),IR(26827, 33)/* RayQueryCandidateIntersectionKHR */,IR(0, 0),IR(199, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {1,IR(0, 0),IR(26860, 33)/* RayQueryCommittedIntersectionKHR */,IR(0, 0),IR(199, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {0,IR(0, 0),IR(15918, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {1,IR(0, 0),IR(26893, 12)/* ClampToEdge */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {2,IR(0, 0),IR(26905, 6)/* Clamp */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {3,IR(0, 0),IR(26911, 7)/* Repeat */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {4,IR(0, 0),IR(26918, 15)/* RepeatMirrored */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {0,IR(0, 0),IR(26933, 8)/* Nearest */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {1,IR(0, 0),IR(26941, 7)/* Linear */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {0,IR(0, 0),IR(26948, 8)/* Unknown */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {1,IR(0, 0),IR(26956, 8)/* Rgba32f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {2,IR(0, 0),IR(26964, 8)/* Rgba16f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {3,IR(0, 0),IR(26972, 5)/* R32f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {4,IR(0, 0),IR(26977, 6)/* Rgba8 */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {5,IR(0, 0),IR(26983, 11)/* Rgba8Snorm */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {6,IR(0, 0),IR(26994, 6)/* Rg32f */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {7,IR(0, 0),IR(27000, 6)/* Rg16f */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {8,IR(0, 0),IR(27006, 13)/* R11fG11fB10f */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {9,IR(0, 0),IR(27019, 5)/* R16f */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {10,IR(0, 0),IR(27024, 7)/* Rgba16 */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {11,IR(0, 0),IR(27031, 8)/* Rgb10A2 */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {12,IR(0, 0),IR(27039, 5)/* Rg16 */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {13,IR(0, 0),IR(27044, 4)/* Rg8 */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {14,IR(0, 0),IR(27048, 4)/* R16 */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {15,IR(0, 0),IR(27052, 3)/* R8 */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {16,IR(0, 0),IR(27055, 12)/* Rgba16Snorm */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {17,IR(0, 0),IR(27067, 10)/* Rg16Snorm */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {18,IR(0, 0),IR(27077, 9)/* Rg8Snorm */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {19,IR(0, 0),IR(27086, 9)/* R16Snorm */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {20,IR(0, 0),IR(27095, 8)/* R8Snorm */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {21,IR(0, 0),IR(27103, 8)/* Rgba32i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {22,IR(0, 0),IR(27111, 8)/* Rgba16i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {23,IR(0, 0),IR(27119, 7)/* Rgba8i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {24,IR(0, 0),IR(27126, 5)/* R32i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {25,IR(0, 0),IR(27131, 6)/* Rg32i */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {26,IR(0, 0),IR(27137, 6)/* Rg16i */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {27,IR(0, 0),IR(27143, 5)/* Rg8i */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {28,IR(0, 0),IR(27148, 5)/* R16i */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {29,IR(0, 0),IR(27153, 4)/* R8i */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {30,IR(0, 0),IR(27157, 9)/* Rgba32ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {31,IR(0, 0),IR(27166, 9)/* Rgba16ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {32,IR(0, 0),IR(27175, 8)/* Rgba8ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {33,IR(0, 0),IR(27183, 6)/* R32ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {34,IR(0, 0),IR(27189, 10)/* Rgb10a2ui */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {35,IR(0, 0),IR(27199, 7)/* Rg32ui */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {36,IR(0, 0),IR(27206, 7)/* Rg16ui */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {37,IR(0, 0),IR(27213, 6)/* Rg8ui */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {38,IR(0, 0),IR(27219, 6)/* R16ui */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {39,IR(0, 0),IR(27225, 5)/* R8ui */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {40,IR(0, 0),IR(27230, 6)/* R64ui */,IR(0, 0),IR(201, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {41,IR(0, 0),IR(27236, 5)/* R64i */,IR(0, 0),IR(201, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {0,IR(0, 0),IR(27241, 12)/* CrossDevice */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {1,IR(0, 0),IR(27253, 7)/* Device */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {2,IR(0, 0),IR(27260, 10)/* Workgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {3,IR(0, 0),IR(27270, 9)/* Subgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {4,IR(0, 0),IR(27279, 11)/* Invocation */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {5,IR(0, 0),IR(27290, 12)/* QueueFamily */,IR(161, 1),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {6,IR(0, 0),IR(27317, 14)/* ShaderCallKHR */,IR(0, 0),IR(61, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {0,IR(0, 0),IR(15918, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {1,IR(0, 0),IR(27331, 8)/* Flatten */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {2,IR(0, 0),IR(27339, 12)/* DontFlatten */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {1,IR(0, 0),IR(27351, 29)/* IdentifierPossibleDuplicates */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS
  {0,IR(0, 0),IR(15787, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(15799, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(15807, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {3,IR(0, 0),IR(15815, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(15821, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(15828, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(15839, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(15848, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(15861, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(15867, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(15877, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(15883, 15)/* ImportedModule */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {1,IR(0, 0),IR(15898, 20)/* ImportedDeclaration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {0,IR(0, 0),IR(15918, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(15923, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(15939, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(15953, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(15966, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(15978, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(15995, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(16007, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(16022, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(16035, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(16050, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(16068, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(16085, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(16106, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(16126, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(16146, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {16384,IR(0, 0),IR(16162, 16)/* FlagIsEnumClass */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {32768,IR(0, 0),IR(16178, 20)/* FlagTypePassByValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {65536,IR(0, 0),IR(16198, 24)/* FlagTypePassByReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {131072,IR(0, 0),IR(27380, 26)/* FlagUnknownPhysicalLayout */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(16222, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {1,IR(0, 0),IR(16228, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {2,IR(0, 0),IR(16233, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {3,IR(10, 1),IR(16272, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {4,IR(36, 2),IR(16283, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {5,IR(0, 0),IR(16292, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {6,IR(0, 0),IR(16297, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {7,IR(0, 0),IR(16304, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {8,IR(10, 1),IR(16315, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {9,IR(36, 2),IR(16322, 9)/* Fragment */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {0,IR(0, 0),IR(16331, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(16341, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(16354, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {3,IR(0, 0),IR(16367, 11)/* AtomicType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(26948, 8)/* Unknown */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {1,IR(0, 0),IR(27406, 5)/* ESSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {2,IR(0, 0),IR(27411, 5)/* GLSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {3,IR(0, 0),IR(27416, 9)/* OpenCL_C */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {4,IR(0, 0),IR(27425, 11)/* OpenCL_CPP */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {5,IR(0, 0),IR(27436, 5)/* HLSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {6,IR(0, 0),IR(27441, 15)/* CPP_for_OpenCL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {7,IR(0, 0),IR(27456, 5)/* SYCL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {8,IR(0, 0),IR(27461, 7)/* HERO_C */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {9,IR(0, 0),IR(27468, 5)/* NZSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {10,IR(0, 0),IR(27473, 5)/* WGSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {11,IR(0, 0),IR(27478, 6)/* Slang */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {12,IR(0, 0),IR(27484, 4)/* Zig */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {13,IR(0, 0),IR(27488, 5)/* Rust */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {0,IR(0, 0),IR(27493, 16)/* UniformConstant */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {1,IR(0, 0),IR(27509, 6)/* Input */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {2,IR(0, 0),IR(17207, 8)/* Uniform */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {3,IR(0, 0),IR(27515, 7)/* Output */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4,IR(0, 0),IR(27260, 10)/* Workgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5,IR(0, 0),IR(27522, 15)/* CrossWorkgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {6,IR(0, 0),IR(27537, 8)/* Private */,IR(0, 0),IR(202, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {7,IR(0, 0),IR(27545, 9)/* Function */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {8,IR(0, 0),IR(27554, 8)/* Generic */,IR(0, 0),IR(204, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {9,IR(0, 0),IR(27562, 13)/* PushConstant */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {10,IR(0, 0),IR(27575, 14)/* AtomicCounter */,IR(0, 0),IR(83, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {11,IR(0, 0),IR(27589, 6)/* Image */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {12,IR(0, 0),IR(27595, 14)/* StorageBuffer */,IR(0, 0),IR(3, 1),IR(193, 2),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4172,IR(0, 0),IR(27609, 13)/* TileImageEXT */,IR(0, 0),IR(153, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4491,IR(0, 0),IR(27622, 19)/* TileAttachmentQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5068,IR(0, 0),IR(27641, 16)/* NodePayloadAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5328,IR(0, 0),IR(27657, 16)/* CallableDataKHR */,IR(162, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5329,IR(0, 0),IR(27688, 24)/* IncomingCallableDataKHR */,IR(163, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5338,IR(0, 0),IR(27735, 14)/* RayPayloadKHR */,IR(164, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5339,IR(0, 0),IR(27762, 16)/* HitAttributeKHR */,IR(165, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5342,IR(0, 0),IR(27793, 22)/* IncomingRayPayloadKHR */,IR(166, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5343,IR(0, 0),IR(27836, 22)/* ShaderRecordBufferKHR */,IR(167, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5349,IR(0, 0),IR(27879, 22)/* PhysicalStorageBuffer */,IR(168, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5385,IR(0, 0),IR(27926, 21)/* HitObjectAttributeNV */,IR(0, 0),IR(131, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5402,IR(0, 0),IR(27947, 24)/* TaskPayloadWorkgroupEXT */,IR(0, 0),IR(54, 1),IR(23, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5411,IR(0, 0),IR(27971, 22)/* HitObjectAttributeEXT */,IR(0, 0),IR(132, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5605,IR(0, 0),IR(27993, 17)/* CodeSectionINTEL */,IR(0, 0),IR(205, 1),IR(101, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5936,IR(0, 0),IR(28010, 17)/* DeviceOnlyALTERA */,IR(169, 1),IR(206, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5937,IR(0, 0),IR(28043, 15)/* HostOnlyALTERA */,IR(170, 1),IR(206, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {0,IR(0, 0),IR(24898, 14)/* UncachedINTEL */,IR(0, 0),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {1,IR(0, 0),IR(28072, 18)/* WriteThroughINTEL */,IR(0, 0),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {2,IR(0, 0),IR(28090, 15)/* WriteBackINTEL */,IR(0, 0),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {3,IR(0, 0),IR(24924, 15)/* StreamingINTEL */,IR(0, 0),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {0,IR(0, 0),IR(15918, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {1,IR(10, 1),IR(28105, 11)/* TensorView */,IR(0, 0),IR(207, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {2,IR(10, 1),IR(28116, 11)/* DecodeFunc */,IR(0, 0),IR(208, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {0,IR(0, 0),IR(28127, 10)/* Undefined */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {1,IR(0, 0),IR(17165, 9)/* Constant */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {2,IR(0, 0),IR(26893, 12)/* ClampToEdge */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {3,IR(0, 0),IR(26911, 7)/* Repeat */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {4,IR(0, 0),IR(26918, 15)/* RepeatMirrored */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {0,IR(0, 0),IR(28137, 8)/* NoneARM */,IR(0, 0),IR(209, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {1,IR(0, 0),IR(28145, 15)/* NontemporalARM */,IR(0, 0),IR(209, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {2,IR(10, 1),IR(28160, 20)/* OutOfBoundsValueARM */,IR(0, 0),IR(209, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {4,IR(10, 1),IR(28180, 24)/* MakeElementAvailableARM */,IR(0, 0),IR(209, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {8,IR(10, 1),IR(28204, 22)/* MakeElementVisibleARM */,IR(0, 0),IR(209, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {16,IR(0, 0),IR(28226, 21)/* NonPrivateElementARM */,IR(0, 0),IR(209, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
}};

// Maps an operand kind to possible operands for that kind.
// The result is an IndexRange into kOperandsByValue, and the operands
// are sorted by value within that span.
// An optional variant of a kind maps to the details for the corresponding
// concrete operand kind.
IndexRange OperandByValueRangeForKind(spv_operand_type_t type) {
  switch(type) {
    case SPV_OPERAND_TYPE_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_ADDRESSING_MODEL: return IR(3, 4);
    case SPV_OPERAND_TYPE_BUILT_IN: return IR(7, 128);
    case SPV_OPERAND_TYPE_CAPABILITY: return IR(135, 284);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(419, 8);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(427, 3);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(430, 2);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS: return IR(432, 19);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION: return IR(451, 10);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(461, 4);
    case SPV_OPERAND_TYPE_COMPONENT_TYPE: return IR(465, 15);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT: return IR(480, 4);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS: return IR(484, 6);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE: return IR(490, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE: return IR(493, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT: return IR(496, 4);
    case SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(500, 8);
    case SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE: return IR(508, 3);
    case SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS: return IR(511, 16);
    case SPV_OPERAND_TYPE_DEBUG_OPERATION: return IR(527, 9);
    case SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER: return IR(536, 3);
    case SPV_OPERAND_TYPE_DECORATION: return IR(539, 149);
    case SPV_OPERAND_TYPE_DIMENSIONALITY: return IR(688, 8);
    case SPV_OPERAND_TYPE_EXECUTION_MODE: return IR(696, 97);
    case SPV_OPERAND_TYPE_EXECUTION_MODEL: return IR(793, 17);
    case SPV_OPERAND_TYPE_FPDENORM_MODE: return IR(810, 2);
    case SPV_OPERAND_TYPE_FPENCODING: return IR(812, 3);
    case SPV_OPERAND_TYPE_FPOPERATION_MODE: return IR(815, 2);
    case SPV_OPERAND_TYPE_FP_FAST_MATH_MODE: return IR(817, 9);
    case SPV_OPERAND_TYPE_FP_ROUNDING_MODE: return IR(826, 4);
    case SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE: return IR(830, 4);
    case SPV_OPERAND_TYPE_FUNCTION_CONTROL: return IR(834, 6);
    case SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE: return IR(840, 9);
    case SPV_OPERAND_TYPE_GROUP_OPERATION: return IR(849, 7);
    case SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER: return IR(856, 4);
    case SPV_OPERAND_TYPE_IMAGE: return IR(860, 17);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE: return IR(877, 26);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER: return IR(903, 20);
    case SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER: return IR(923, 2);
    case SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS: return IR(925, 3);
    case SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO: return IR(928, 2);
    case SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS: return IR(930, 2);
    case SPV_OPERAND_TYPE_LINKAGE_TYPE: return IR(932, 3);
    case SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL: return IR(935, 5);
    case SPV_OPERAND_TYPE_LOOP_CONTROL: return IR(940, 20);
    case SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(960, 15);
    case SPV_OPERAND_TYPE_MEMORY_ACCESS: return IR(975, 9);
    case SPV_OPERAND_TYPE_MEMORY_MODEL: return IR(984, 4);
    case SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID: return IR(988, 15);
    case SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS: return IR(1003, 1);
    case SPV_OPERAND_TYPE_OVERFLOW_MODES: return IR(1004, 4);
    case SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT: return IR(1008, 1);
    case SPV_OPERAND_TYPE_QUANTIZATION_MODES: return IR(1009, 8);
    case SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS: return IR(1017, 3);
    case SPV_OPERAND_TYPE_RAY_FLAGS: return IR(1020, 12);
    case SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE: return IR(1032, 2);
    case SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE: return IR(1034, 3);
    case SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION: return IR(1037, 2);
    case SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE: return IR(1039, 5);
    case SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE: return IR(1044, 2);
    case SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT: return IR(1046, 42);
    case SPV_OPERAND_TYPE_SCOPE_ID: return IR(1088, 7);
    case SPV_OPERAND_TYPE_SELECTION_CONTROL: return IR(1095, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS: return IR(1098, 1);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(1099, 8);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(1107, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(1110, 2);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS: return IR(1112, 20);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION: return IR(1132, 10);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(1142, 4);
    case SPV_OPERAND_TYPE_SOURCE_LANGUAGE: return IR(1146, 14);
    case SPV_OPERAND_TYPE_STORAGE_CLASS: return IR(1160, 29);
    case SPV_OPERAND_TYPE_STORE_CACHE_CONTROL: return IR(1189, 4);
    case SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS: return IR(1193, 3);
    case SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE: return IR(1196, 5);
    case SPV_OPERAND_TYPE_TENSOR_OPERANDS: return IR(1201, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_IMAGE: return IR(860, 17);
    case SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS: return IR(975, 9);
    case SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT: return IR(1008, 1);
    case SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS: return IR(484, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(960, 15);
    case SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS: return IR(1017, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_FPENCODING: return IR(812, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS: return IR(1201, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_CAPABILITY: return IR(135, 284);
    default: break;
  }
  return IR(0,0);
}

// Operand names and index into kOperandsByValue, ordered by (operand kind, name)
// The fields in order are:
//   name, either the primary name or an alias, indexing into kStrings
//   index into the kOperandsByValue array
static const std::array<NameIndex, 1382> kOperandNames{{
  {IR(5488, 9), 0}, // 0 ReadOnly in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(5514, 10), 2}, // 1 ReadWrite in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(5504, 10), 1}, // 2 WriteOnly in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(5524, 8), 3}, // 3 Logical in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5532, 11), 4}, // 4 Physical32 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5553, 11), 5}, // 5 Physical64 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5564, 24), 6}, // 6 PhysicalStorageBuffer64 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5588, 27), 6}, // 7 PhysicalStorageBuffer64EXT in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(7547, 13), 94}, // 8 BaryCoordKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7560, 12), 94}, // 9 BaryCoordNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6893, 20), 68}, // 10 BaryCoordNoPerspAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6913, 28), 69}, // 11 BaryCoordNoPerspCentroidAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7595, 20), 95}, // 12 BaryCoordNoPerspKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7615, 19), 95}, // 13 BaryCoordNoPerspNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6941, 26), 70}, // 14 BaryCoordNoPerspSampleAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7038, 22), 74}, // 15 BaryCoordPullModelAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6967, 19), 71}, // 16 BaryCoordSmoothAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6986, 27), 72}, // 17 BaryCoordSmoothCentroidAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7013, 25), 73}, // 18 BaryCoordSmoothSampleAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6697, 13), 59}, // 19 BaseInstance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6671, 11), 58}, // 20 BaseVertex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5672, 13), 9}, // 21 ClipDistance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7454, 22), 89}, // 22 ClipDistancePerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8753, 12), 133}, // 23 ClusterIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6435, 13), 49}, // 24 CoreCountARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6409, 10), 48}, // 25 CoreIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6448, 13), 50}, // 26 CoreMaxIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5685, 13), 10}, // 27 CullDistance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7476, 22), 90}, // 28 CullDistancePerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8806, 12), 134}, // 29 CullMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7802, 17), 101}, // 30 CullPrimitiveEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8206, 17), 115}, // 31 CurrentRayTimeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6767, 12), 62}, // 32 DeviceIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6710, 10), 60}, // 33 DrawIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6199, 22), 37}, // 34 EnqueuedWorkgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5969, 10), 21}, // 35 FragCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6055, 10), 27}, // 36 FragDepth in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7680, 23), 97}, // 37 FragInvocationCountEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7634, 12), 96}, // 38 FragSizeEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7060, 18), 75}, // 39 FragStencilRefEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7646, 15), 96}, // 40 FragmentSizeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5990, 12), 23}, // 41 FrontFacing in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7366, 16), 85}, // 42 FullyCoveredEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6140, 19), 33}, // 43 GlobalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6234, 15), 39}, // 44 GlobalLinearId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6221, 13), 38}, // 45 GlobalOffset in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6188, 11), 36}, // 46 GlobalSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6065, 17), 28}, // 47 HelperInvocation in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8508, 11), 122}, // 48 HitIsLSSNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8466, 14), 121}, // 49 HitIsSphereNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8688, 33), 130}, // 50 HitKindBackFacingMicroTriangleNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8654, 34), 129}, // 51 HitKindFrontFacingMicroTriangleNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8185, 11), 114}, // 52 HitKindKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8196, 10), 114}, // 53 HitKindNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8636, 18), 128}, // 54 HitLSSPositionsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8739, 14), 132}, // 55 HitLSSRadiiNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8370, 37), 118}, // 56 HitMicroTriangleVertexBarycentricsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8303, 34), 117}, // 57 HitMicroTriangleVertexPositionsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8558, 20), 123}, // 58 HitSpherePositionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8721, 18), 131}, // 59 HitSphereRadiusNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8178, 7), 113}, // 60 HitTNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8246, 30), 116}, // 61 HitTriangleVertexPositionsKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8407, 20), 119}, // 62 IncomingRayFlagsKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8427, 19), 119}, // 63 IncomingRayFlagsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8067, 23), 110}, // 64 InstanceCustomIndexKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8090, 22), 110}, // 65 InstanceCustomIndexNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5707, 11), 12}, // 66 InstanceId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6395, 14), 47}, // 67 InstanceIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5808, 13), 14}, // 68 InvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7703, 22), 97}, // 69 InvocationsPerPixelNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7819, 12), 102}, // 70 LaunchIdKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7831, 11), 102}, // 71 LaunchIdNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7842, 14), 103}, // 72 LaunchSizeKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7856, 13), 103}, // 73 LaunchSizeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5821, 6), 15}, // 74 Layer in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7498, 15), 91}, // 75 LayerPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6122, 18), 32}, // 76 LocalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6159, 21), 34}, // 77 LocalInvocationIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7513, 16), 92}, // 78 MeshViewCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7529, 18), 93}, // 79 MeshViewIndicesNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6325, 21), 43}, // 80 NumEnqueuedSubgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6312, 13), 42}, // 81 NumSubgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6082, 14), 29}, // 82 NumWorkgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7982, 22), 107}, // 83 ObjectRayDirectionKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8004, 21), 107}, // 84 ObjectRayDirectionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7945, 19), 106}, // 85 ObjectRayOriginKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7964, 18), 106}, // 86 ObjectRayOriginNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8112, 17), 111}, // 87 ObjectToWorldKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8129, 16), 111}, // 88 ObjectToWorldNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5955, 14), 20}, // 89 PatchVertices in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5979, 11), 22}, // 90 PointCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5662, 10), 8}, // 91 PointSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5646, 9), 7}, // 92 Position in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7306, 18), 83}, // 93 PositionPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7418, 17), 87}, // 94 PrimitiveCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5718, 12), 13}, // 95 PrimitiveId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7435, 19), 88}, // 96 PrimitiveIndicesNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7750, 24), 99}, // 97 PrimitiveLineIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7725, 25), 98}, // 98 PrimitivePointIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6720, 24), 61}, // 99 PrimitiveShadingRateKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7774, 28), 100}, // 100 PrimitiveTriangleIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8446, 20), 120}, // 101 RayGeometryIndexKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8046, 11), 109}, // 102 RayTmaxKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8057, 10), 109}, // 103 RayTmaxNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8025, 11), 108}, // 104 RayTminKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8036, 10), 108}, // 105 RayTminNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7095, 29), 76}, // 106 RemainingRecursionLevelsAMDX in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7191, 16), 79}, // 107 ResourceHeapEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8610, 10), 125}, // 108 SMCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8629, 7), 127}, // 109 SMIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6002, 9), 24}, // 110 SampleId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6044, 11), 26}, // 111 SampleMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6029, 15), 25}, // 112 SamplePosition in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7158, 15), 78}, // 113 SamplerHeapEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7243, 20), 81}, // 114 SecondaryPositionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7282, 24), 82}, // 115 SecondaryViewportMaskNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7142, 16), 77}, // 116 ShaderIndexAMDX in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6811, 15), 64}, // 117 ShadingRateKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6484, 15), 53}, // 118 SubgroupEqMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6499, 18), 53}, // 119 SubgroupEqMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6539, 15), 54}, // 120 SubgroupGeMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6554, 18), 54}, // 121 SubgroupGeMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6572, 15), 55}, // 122 SubgroupGtMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6587, 18), 55}, // 123 SubgroupGtMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6346, 11), 44}, // 124 SubgroupId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6605, 15), 56}, // 125 SubgroupLeMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6620, 18), 56}, // 126 SubgroupLeMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6357, 26), 45}, // 127 SubgroupLocalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6638, 15), 57}, // 128 SubgroupLtMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6653, 18), 57}, // 129 SubgroupLtMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6296, 16), 41}, // 130 SubgroupMaxSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6249, 13), 40}, // 131 SubgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7406, 12), 86}, // 132 TaskCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5945, 10), 19}, // 133 TessCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5930, 15), 18}, // 134 TessLevelInner in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5915, 15), 17}, // 135 TessLevelOuter in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6875, 18), 67}, // 136 TileApronSizeQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6857, 18), 66}, // 137 TileDimensionQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6826, 15), 65}, // 138 TileOffsetQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5698, 9), 11}, // 139 VertexId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6383, 12), 46}, // 140 VertexIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6791, 10), 63}, // 141 ViewIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5867, 14), 16}, // 142 ViewportIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7207, 15), 80}, // 143 ViewportMaskNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7344, 22), 84}, // 144 ViewportMaskPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6461, 10), 51}, // 145 WarpIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8620, 9), 126}, // 146 WarpIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6471, 13), 52}, // 147 WarpMaxIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8578, 13), 124}, // 148 WarpsPerSMNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6180, 8), 35}, // 149 WorkDim in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6110, 12), 31}, // 150 WorkgroupId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6096, 14), 30}, // 151 WorkgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7904, 21), 105}, // 152 WorldRayDirectionKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7925, 20), 105}, // 153 WorldRayDirectionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7869, 18), 104}, // 154 WorldRayOriginKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7887, 17), 104}, // 155 WorldRayOriginNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8145, 17), 112}, // 156 WorldToObjectKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8162, 16), 112}, // 157 WorldToObjectNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5543, 10), 139}, // 158 Addresses in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14213, 35), 366}, // 159 ArbitraryPrecisionFixedPointALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14248, 34), 366}, // 160 ArbitraryPrecisionFixedPointINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13685, 38), 354}, // 161 ArbitraryPrecisionFloatingPointALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13723, 37), 354}, // 162 ArbitraryPrecisionFloatingPointINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13620, 33), 353}, // 163 ArbitraryPrecisionIntegersALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13653, 32), 353}, // 164 ArbitraryPrecisionIntegersINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14907, 19), 391}, // 165 ArithmeticFenceEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13258, 9), 339}, // 166 AsmINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14824, 20), 387}, // 167 AtomicFloat16AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13313, 23), 342}, // 168 AtomicFloat16MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12729, 22), 314}, // 169 AtomicFloat16VectorNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14740, 20), 383}, // 170 AtomicFloat32AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13267, 23), 340}, // 171 AtomicFloat32MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14760, 20), 384}, // 172 AtomicFloat64AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13290, 23), 341}, // 173 AtomicFloat64MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8986, 14), 155}, // 174 AtomicStorage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10373, 17), 231}, // 175 AtomicStorageOps in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14865, 24), 389}, // 176 BFloat16ConversionINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10995, 29), 265}, // 177 BFloat16CooperativeMatrixKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10973, 22), 264}, // 178 BFloat16DotProductKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10957, 16), 263}, // 179 BFloat16TypeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15642, 20), 414}, // 180 BindlessImagesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12666, 18), 311}, // 181 BindlessTextureNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14677, 16), 379}, // 182 BitInstructions in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14415, 20), 370}, // 183 BlockingPipesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14435, 19), 370}, // 184 BlockingPipesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15603, 19), 412}, // 185 CacheControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5672, 13), 165}, // 186 ClipDistance in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12297, 32), 299}, // 187 ComputeDerivativeGroupLinearKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12329, 31), 299}, // 188 ComputeDerivativeGroupLinearNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11147, 31), 278}, // 189 ComputeDerivativeGroupQuadsKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11178, 30), 278}, // 190 ComputeDerivativeGroupQuadsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12963, 30), 326}, // 191 CooperativeMatrixBlockLoadsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10742, 32), 250}, // 192 CooperativeMatrixConversionQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12856, 31), 323}, // 193 CooperativeMatrixConversionsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10021, 21), 377}, // 194 CooperativeMatrixKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9956, 28), 213}, // 195 CooperativeMatrixLayoutsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12385, 20), 301}, // 196 CooperativeMatrixNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12887, 40), 324}, // 197 CooperativeMatrixPerElementOperationsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12826, 30), 322}, // 198 CooperativeMatrixReductionsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12927, 36), 325}, // 199 CooperativeMatrixTensorAddressingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12709, 20), 313}, // 200 CooperativeVectorNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12993, 28), 327}, // 201 CooperativeVectorTrainingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6419, 16), 205}, // 202 CoreBuiltinsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5685, 13), 166}, // 203 CullDistance in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14844, 21), 388}, // 204 DebugInfoModuleINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12508, 25), 306}, // 205 DemoteToHelperInvocation in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12533, 28), 306}, // 206 DemoteToHelperInvocationEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10512, 18), 237}, // 207 DenormFlushToZero in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10497, 15), 236}, // 208 DenormPreserve in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9433, 18), 184}, // 209 DerivativeControl in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7173, 18), 266}, // 210 DescriptorHeapEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8957, 14), 153}, // 211 DeviceEnqueue in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6779, 12), 227}, // 212 DeviceGroup in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12561, 23), 307}, // 213 DisplacementMicromapNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14628, 11), 375}, // 214 DotProduct in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15728, 27), 417}, // 215 DotProductBFloat16AccVALVE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15695, 33), 416}, // 216 DotProductFloat16AccFloat16VALVE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15662, 33), 415}, // 217 DotProductFloat16AccFloat32VALVE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15755, 32), 418}, // 218 DotProductFloat8AccFloat32VALVE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14522, 22), 373}, // 219 DotProductInput4x8Bit in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14544, 25), 373}, // 220 DotProductInput4x8BitKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14569, 28), 374}, // 221 DotProductInput4x8BitPacked in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14597, 31), 374}, // 222 DotProductInput4x8BitPackedKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14481, 19), 372}, // 223 DotProductInputAll in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14500, 22), 372}, // 224 DotProductInputAllKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14639, 14), 375}, // 225 DotProductKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6682, 15), 218}, // 226 DrawParameters in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13370, 16), 345}, // 227 ExpectAssumeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14733, 7), 382}, // 228 FMAKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13600, 20), 352}, // 229 FPFastMathModeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15115, 29), 397}, // 230 FPGAArgumentInterfacesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15144, 28), 397}, // 231 FPGAArgumentInterfacesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14164, 25), 365}, // 232 FPGABufferLocationALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14189, 24), 365}, // 233 FPGABufferLocationINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13932, 28), 360}, // 234 FPGAClusterAttributesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13960, 27), 360}, // 235 FPGAClusterAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14926, 30), 392}, // 236 FPGAClusterAttributesV2ALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14956, 29), 392}, // 237 FPGAClusterAttributesV2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14016, 21), 362}, // 238 FPGADSPControlALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14037, 20), 362}, // 239 FPGADSPControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14083, 41), 364}, // 240 FPGAInvocationPipeliningAttributesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14124, 40), 364}, // 241 FPGAInvocationPipeliningAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13857, 26), 358}, // 242 FPGAKernelAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14985, 28), 393}, // 243 FPGAKernelAttributesv2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15066, 25), 396}, // 244 FPGALatencyControlALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15091, 24), 396}, // 245 FPGALatencyControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13790, 23), 356}, // 246 FPGALoopControlsALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13813, 22), 356}, // 247 FPGALoopControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13883, 25), 359}, // 248 FPGAMemoryAccessesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13908, 24), 359}, // 249 FPGAMemoryAccessesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13547, 27), 351}, // 250 FPGAMemoryAttributesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13574, 26), 351}, // 251 FPGAMemoryAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14454, 14), 371}, // 252 FPGARegALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14468, 13), 371}, // 253 FPGARegINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15050, 16), 395}, // 254 FPMaxErrorINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8871, 8), 144}, // 255 Float16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8857, 14), 143}, // 256 Float16Buffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10797, 16), 252}, // 257 Float16ImageAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8879, 8), 145}, // 258 Float64 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9994, 27), 215}, // 259 Float8CooperativeMatrixEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9984, 10), 214}, // 260 Float8EXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14718, 15), 381}, // 261 FloatControls2 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13166, 23), 335}, // 262 FloatingPointModeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7572, 23), 277}, // 263 FragmentBarycentricKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11125, 22), 277}, // 264 FragmentBarycentricNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7661, 19), 279}, // 265 FragmentDensityEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7382, 24), 273}, // 266 FragmentFullyCoveredEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10835, 16), 254}, // 267 FragmentMaskAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12476, 32), 305}, // 268 FragmentShaderPixelInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12405, 33), 302}, // 269 FragmentShaderSampleInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12438, 38), 303}, // 270 FragmentShaderShadingRateInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6744, 23), 216}, // 271 FragmentShadingRateKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13521, 26), 350}, // 272 FunctionFloatControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13212, 22), 337}, // 273 FunctionPointersINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15503, 22), 408}, // 274 FunctionVariantsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9278, 15), 171}, // 275 GenericPointer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5730, 9), 137}, // 276 Geometry in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9028, 18), 158}, // 277 GeometryPointSize in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11053, 28), 268}, // 278 GeometryShaderPassthroughNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9491, 16), 187}, // 279 GeometryStreams in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15202, 36), 399}, // 280 GlobalVariableFPGADecorationsALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15238, 35), 399}, // 281 GlobalVariableFPGADecorationsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15172, 30), 398}, // 282 GlobalVariableHostAccessINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9947, 9), 212}, // 283 GraphARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6262, 16), 194}, // 284 GroupNonUniform in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9630, 26), 196}, // 285 GroupNonUniformArithmetic in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6517, 22), 197}, // 286 GroupNonUniformBallot in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9710, 25), 200}, // 287 GroupNonUniformClustered in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11222, 30), 280}, // 288 GroupNonUniformPartitionedEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11252, 29), 280}, // 289 GroupNonUniformPartitionedNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9735, 20), 201}, // 290 GroupNonUniformQuad in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14693, 25), 380}, // 291 GroupNonUniformRotateKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9656, 23), 198}, // 292 GroupNonUniformShuffle in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9679, 31), 199}, // 293 GroupNonUniformShuffleRelative in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9610, 20), 195}, // 294 GroupNonUniformVote in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15525, 26), 409}, // 295 GroupUniformArithmeticKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8950, 7), 152}, // 296 Groups in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14388, 14), 369}, // 297 IOPipesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14402, 13), 369}, // 298 IOPipesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9347, 8), 177}, // 299 Image1D in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8906, 11), 148}, // 300 ImageBasic in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9369, 12), 180}, // 301 ImageBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9224, 15), 167}, // 302 ImageCubeArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11108, 17), 275}, // 303 ImageFootprintNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10813, 22), 253}, // 304 ImageGatherBiasLodAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9046, 20), 159}, // 305 ImageGatherExtended in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9381, 13), 181}, // 306 ImageMSArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8932, 12), 150}, // 307 ImageMipmap in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9422, 11), 183}, // 308 ImageQuery in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8917, 15), 149}, // 309 ImageReadWrite in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10851, 21), 256}, // 310 ImageReadWriteLodAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9256, 10), 169}, // 311 ImageRect in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13234, 24), 338}, // 312 IndirectReferencesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9298, 16), 173}, // 313 InputAttachment in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11367, 36), 283}, // 314 InputAttachmentArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11403, 39), 283}, // 315 InputAttachmentArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11908, 39), 290}, // 316 InputAttachmentArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11947, 42), 290}, // 317 InputAttachmentArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9000, 6), 156}, // 318 Int16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10930, 27), 262}, // 319 Int4CooperativeMatrixINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10916, 14), 261}, // 320 Int4TypeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8887, 6), 146}, // 321 Int64 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8893, 13), 147}, // 322 Int64Atomics in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10872, 14), 257}, // 323 Int64ImageEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9293, 5), 172}, // 324 Int8 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13189, 23), 336}, // 325 IntegerFunctions2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9451, 22), 185}, // 326 InterpolationFunction in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5497, 7), 141}, // 327 Kernel in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13835, 22), 357}, // 328 KernelAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8840, 8), 140}, // 329 Linkage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8971, 15), 154}, // 330 LiteralSampler in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14780, 20), 385}, // 331 LongCompositesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12789, 14), 320}, // 332 LongVectorEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13987, 15), 361}, // 333 LoopFuseALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14002, 14), 361}, // 334 LoopFuseINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15578, 25), 411}, // 335 MaskedGatherScatterINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8833, 7), 135}, // 336 Matrix in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14057, 26), 363}, // 337 MemoryAccessAliasingINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5793, 15), 276}, // 338 MeshShadingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5779, 14), 274}, // 339 MeshShadingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9330, 7), 175}, // 340 MinLod in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6801, 10), 228}, // 341 MultiView in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5881, 14), 190}, // 342 MultiViewport in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9585, 13), 192}, // 343 NamedBarrier in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14800, 11), 386}, // 344 OptNoneEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14811, 13), 386}, // 345 OptNoneINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7324, 20), 272}, // 346 PerViewAttributesNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5615, 31), 298}, // 347 PhysicalStorageBufferAddresses in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12263, 34), 298}, // 348 PhysicalStorageBufferAddressesEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9598, 12), 193}, // 349 PipeStorage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8944, 6), 151}, // 350 Pipes in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12769, 20), 319}, // 351 PushConstantBanksNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10901, 15), 260}, // 352 QuadControlKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12751, 18), 316}, // 353 RawAccessChainsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8818, 15), 376}, // 354 RayCullMaskKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10610, 12), 242}, // 355 RayQueryKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12684, 25), 312}, // 356 RayQueryPositionFetchKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10587, 23), 241}, // 357 RayQueryProvisionalKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8765, 41), 328}, // 358 RayTracingClusterAccelerationStructureNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8337, 33), 315}, // 359 RayTracingDisplacementMicromapNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5765, 14), 245}, // 360 RayTracingKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8519, 39), 318}, // 361 RayTracingLinearSweptSpheresGeometryNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8223, 23), 295}, // 362 RayTracingMotionBlurNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5752, 13), 294}, // 363 RayTracingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12584, 29), 308}, // 364 RayTracingOpacityMicromapEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8276, 27), 293}, // 365 RayTracingPositionFetchKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12360, 25), 300}, // 366 RayTracingProvisionalKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8480, 28), 317}, // 367 RayTracingSpheresGeometryNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10641, 32), 244}, // 368 RayTraversalPrimitiveCullingKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15622, 20), 413}, // 369 RegisterLimitsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14653, 24), 378}, // 370 ReplicatedCompositesEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13145, 21), 334}, // 371 RoundToInfinityINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10555, 16), 239}, // 372 RoundingModeRTE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10571, 16), 240}, // 373 RoundingModeRTZ in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14329, 30), 368}, // 374 RuntimeAlignedAttributeALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14359, 29), 368}, // 375 RuntimeAlignedAttributeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11318, 23), 282}, // 376 RuntimeDescriptorArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11341, 26), 282}, // 377 RuntimeDescriptorArrayEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11024, 29), 267}, // 378 SampleMaskOverrideCoverageNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10390, 28), 232}, // 379 SampleMaskPostDepthCoverage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6011, 18), 168}, // 380 SampleRateShading in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9337, 10), 176}, // 381 Sampled1D in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9355, 14), 179}, // 382 SampledBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9239, 17), 178}, // 383 SampledCubeArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9124, 33), 162}, // 384 SampledImageArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11681, 36), 287}, // 385 SampledImageArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11717, 39), 287}, // 386 SampledImageArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9266, 12), 170}, // 387 SampledRect in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5655, 7), 136}, // 388 Shader in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12803, 23), 321}, // 389 Shader64BitIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10886, 15), 258}, // 390 ShaderClockKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7124, 18), 259}, // 391 ShaderEnqueueAMDX in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12639, 27), 310}, // 392 ShaderInvocationReorderEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12613, 26), 309}, // 393 ShaderInvocationReorderNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5827, 12), 202}, // 394 ShaderLayer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11281, 17), 281}, // 395 ShaderNonUniform in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11298, 20), 281}, // 396 ShaderNonUniformEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8591, 19), 304}, // 397 ShaderSMBuiltinsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7263, 19), 271}, // 398 ShaderStereoViewNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5895, 20), 203}, // 399 ShaderViewportIndex in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5839, 28), 269}, // 400 ShaderViewportIndexLayerEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11081, 27), 269}, // 401 ShaderViewportIndexLayerNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7222, 21), 270}, // 402 ShaderViewportMaskNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11208, 14), 279}, // 403 ShadingRateNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10530, 25), 238}, // 404 SignedZeroInfNanPreserve in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9314, 16), 174}, // 405 SparseResidency in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15482, 21), 407}, // 406 SpecConditionalINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14889, 18), 390}, // 407 SplitBarrierINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7078, 17), 255}, // 408 StencilExportEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10178, 25), 223}, // 409 StorageBuffer16BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10418, 24), 233}, // 410 StorageBuffer8BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9157, 34), 163}, // 411 StorageBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11756, 37), 288}, // 412 StorageBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11793, 40), 288}, // 413 StorageBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9191, 33), 164}, // 414 StorageImageArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11833, 36), 289}, // 415 StorageImageArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11869, 39), 289}, // 416 StorageImageArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9394, 28), 182}, // 417 StorageImageExtendedFormats in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9066, 24), 160}, // 418 StorageImageMultisample in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9507, 30), 188}, // 419 StorageImageReadWithoutFormat in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9537, 31), 189}, // 420 StorageImageWriteWithoutFormat in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10305, 21), 226}, // 421 StorageInputOutput16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10283, 22), 225}, // 422 StoragePushConstant16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10476, 21), 235}, // 423 StoragePushConstant8 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9870, 37), 210}, // 424 StorageTensorArrayDynamicIndexingARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9907, 40), 211}, // 425 StorageTensorArrayNonUniformIndexingARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11523, 39), 285}, // 426 StorageTexelBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11562, 42), 285}, // 427 StorageTexelBufferArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12076, 42), 292}, // 428 StorageTexelBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12118, 45), 292}, // 429 StorageTexelBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10266, 17), 224}, // 430 StorageUniform16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10203, 28), 223}, // 431 StorageUniformBufferBlock16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15301, 23), 401}, // 432 Subgroup2DBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15324, 30), 402}, // 433 Subgroup2DBlockTransformINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15354, 30), 403}, // 434 Subgroup2DBlockTransposeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13457, 39), 348}, // 435 SubgroupAvcMotionEstimationChromaINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13386, 33), 346}, // 436 SubgroupAvcMotionEstimationINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13419, 38), 347}, // 437 SubgroupAvcMotionEstimationIntraINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6278, 18), 217}, // 438 SubgroupBallotKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13061, 27), 331}, // 439 SubgroupBufferBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15273, 28), 400}, // 440 SubgroupBufferPrefetchINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9568, 17), 191}, // 441 SubgroupDispatch in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13088, 26), 332}, // 442 SubgroupImageBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13114, 31), 333}, // 443 SubgroupImageMediaBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15384, 38), 404}, // 444 SubgroupMatrixMultiplyAccumulateINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13040, 21), 330}, // 445 SubgroupShuffleINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10162, 16), 222}, // 446 SubgroupVoteKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15013, 19), 394}, // 447 TaskSequenceALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15032, 18), 394}, // 448 TaskSequenceINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13021, 19), 329}, // 449 TensorAddressingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15551, 27), 410}, // 450 TensorFloat32RoundingINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9859, 11), 209}, // 451 TensorsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15422, 28), 405}, // 452 TernaryBitwiseFunctionINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5739, 13), 138}, // 453 Tessellation in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9006, 22), 157}, // 454 TessellationPointSize in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10774, 23), 251}, // 455 TextureBlockMatch2QCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10720, 22), 248}, // 456 TextureBlockMatchQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10699, 21), 247}, // 457 TextureBoxFilterQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10673, 26), 246}, // 458 TextureSampleWeightedQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9773, 28), 206}, // 459 TileImageColorReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9801, 28), 207}, // 460 TileImageDepthReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9829, 30), 208}, // 461 TileImageStencilReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6841, 16), 249}, // 462 TileShadingQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9473, 18), 186}, // 463 TransformFeedback in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14282, 24), 367}, // 464 USMStorageClassesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14306, 23), 367}, // 465 USMStorageClassesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10231, 35), 224}, // 466 UniformAndStorageBuffer16BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10442, 34), 234}, // 467 UniformAndStorageBuffer8BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9090, 34), 161}, // 468 UniformBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11604, 37), 286}, // 469 UniformBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11641, 40), 286}, // 470 UniformBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9755, 18), 204}, // 471 UniformDecoration in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11442, 39), 284}, // 472 UniformTexelBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11481, 42), 284}, // 473 UniformTexelBufferArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11989, 42), 291}, // 474 UniformTexelBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12031, 45), 291}, // 475 UniformTexelBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13760, 30), 355}, // 476 UnstructuredLoopControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10622, 19), 243}, // 477 UntypedPointersKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15450, 32), 406}, // 478 UntypedVariableLengthArrayINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13496, 25), 349}, // 479 VariableLengthArrayINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10356, 17), 230}, // 480 VariablePointers in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10326, 30), 229}, // 481 VariablePointersStorageBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8848, 9), 142}, // 482 Vector16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13355, 15), 344}, // 483 VectorAnyINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13336, 19), 343}, // 484 VectorComputeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12163, 18), 296}, // 485 VulkanMemoryModel in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12202, 29), 297}, // 486 VulkanMemoryModelDeviceScope in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12231, 32), 297}, // 487 VulkanMemoryModelDeviceScopeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12181, 21), 296}, // 488 VulkanMemoryModelKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10118, 44), 221}, // 489 WorkgroupMemoryExplicitLayout16BitAccessKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10075, 43), 220}, // 490 WorkgroupMemoryExplicitLayout8BitAccessKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10042, 33), 219}, // 491 WorkgroupMemoryExplicitLayoutKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15799, 8), 420}, // 492 Address in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15807, 8), 421}, // 493 Boolean in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15815, 6), 422}, // 494 Float in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15821, 7), 423}, // 495 Signed in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15828, 11), 424}, // 496 SignedChar in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15839, 9), 425}, // 497 Unsigned in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15848, 13), 426}, // 498 UnsignedChar in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15787, 12), 419}, // 499 Unspecified in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15861, 6), 427}, // 500 Class in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15867, 10), 428}, // 501 Structure in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15877, 6), 429}, // 502 Union in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15898, 20), 431}, // 503 ImportedDeclaration in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(15883, 15), 430}, // 504 ImportedModule in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(16007, 15), 439}, // 505 FlagArtificial in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16022, 13), 440}, // 506 FlagExplicit in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15995, 12), 438}, // 507 FlagFwdDecl in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16085, 21), 444}, // 508 FlagIndirectVariable in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15978, 17), 437}, // 509 FlagIsDefinition in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16162, 16), 448}, // 510 FlagIsEnumClass in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15966, 12), 436}, // 511 FlagIsLocal in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16146, 16), 447}, // 512 FlagIsOptimized in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15939, 14), 434}, // 513 FlagIsPrivate in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15923, 16), 433}, // 514 FlagIsProtected in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15953, 13), 435}, // 515 FlagIsPublic in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16106, 20), 445}, // 516 FlagLValueReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16050, 18), 442}, // 517 FlagObjectPointer in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16035, 15), 441}, // 518 FlagPrototyped in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16126, 20), 446}, // 519 FlagRValueReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16068, 17), 443}, // 520 FlagStaticMember in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16198, 24), 450}, // 521 FlagTypePassByReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16178, 20), 449}, // 522 FlagTypePassByValue in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15918, 5), 432}, // 523 None in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16283, 9), 455}, // 524 BitPiece in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16315, 7), 459}, // 525 Constu in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16222, 6), 451}, // 526 Deref in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16322, 9), 460}, // 527 Fragment in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16233, 6), 453}, // 528 Minus in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16228, 5), 452}, // 529 Plus in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16272, 11), 454}, // 530 PlusUconst in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16304, 11), 458}, // 531 StackValue in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16292, 5), 456}, // 532 Swap in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16297, 7), 457}, // 533 Xderef in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16367, 11), 464}, // 534 AtomicType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16331, 10), 461}, // 535 ConstType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16354, 13), 463}, // 536 RestrictType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16341, 13), 462}, // 537 VolatileType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16378, 10), 465}, // 538 Float16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16388, 10), 466}, // 539 Float32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16398, 10), 467}, // 540 Float64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16566, 12), 478}, // 541 FloatE4M3NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16578, 12), 479}, // 542 FloatE5M2NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16421, 14), 469}, // 543 SignedInt16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16435, 14), 470}, // 544 SignedInt32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16449, 14), 471}, // 545 SignedInt64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16408, 13), 468}, // 546 SignedInt8NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16526, 19), 476}, // 547 SignedInt8PackedNV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16478, 16), 473}, // 548 UnsignedInt16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16494, 16), 474}, // 549 UnsignedInt32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16510, 16), 475}, // 550 UnsignedInt64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16463, 15), 472}, // 551 UnsignedInt8NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16545, 21), 477}, // 552 UnsignedInt8PackedNV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16642, 28), 483}, // 553 ColumnBlockedInterleavedARM in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(16602, 15), 481}, // 554 ColumnMajorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(16617, 25), 482}, // 555 RowBlockedInterleavedARM in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(16590, 12), 480}, // 556 RowMajorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(16678, 27), 485}, // 557 MatrixASignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16705, 27), 486}, // 558 MatrixBSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16732, 27), 487}, // 559 MatrixCSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16759, 32), 488}, // 560 MatrixResultSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16670, 8), 484}, // 561 NoneKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16791, 26), 489}, // 562 SaturatingAccumulationKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16828, 4), 492}, // 563 2x2 in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(16821, 7), 491}, // 564 Column in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(16817, 4), 490}, // 565 Row in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(16832, 11), 493}, // 566 MatrixAKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(16854, 21), 495}, // 567 MatrixAccumulatorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(16843, 11), 494}, // 568 MatrixBKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(16886, 14), 497}, // 569 ColumnMajorNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(16900, 21), 498}, // 570 InferencingOptimalNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(16875, 11), 496}, // 571 RowMajorNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(16921, 18), 499}, // 572 TrainingOptimalNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(15799, 8), 501}, // 573 Address in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15807, 8), 502}, // 574 Boolean in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15815, 6), 503}, // 575 Float in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15821, 7), 504}, // 576 Signed in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15828, 11), 505}, // 577 SignedChar in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15839, 9), 506}, // 578 Unsigned in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15848, 13), 507}, // 579 UnsignedChar in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15787, 12), 500}, // 580 Unspecified in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15861, 6), 508}, // 581 Class in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(15867, 10), 509}, // 582 Structure in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(15877, 6), 510}, // 583 Union in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(16007, 15), 518}, // 584 FlagArtificial in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16022, 13), 519}, // 585 FlagExplicit in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15995, 12), 517}, // 586 FlagFwdDecl in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16085, 21), 523}, // 587 FlagIndirectVariable in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15978, 17), 516}, // 588 FlagIsDefinition in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15966, 12), 515}, // 589 FlagIsLocal in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16146, 16), 526}, // 590 FlagIsOptimized in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15939, 14), 513}, // 591 FlagIsPrivate in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15923, 16), 512}, // 592 FlagIsProtected in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15953, 13), 514}, // 593 FlagIsPublic in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16106, 20), 524}, // 594 FlagLValueReference in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16050, 18), 521}, // 595 FlagObjectPointer in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16035, 15), 520}, // 596 FlagPrototyped in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16126, 20), 525}, // 597 FlagRValueReference in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16068, 17), 522}, // 598 FlagStaticMember in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15918, 5), 511}, // 599 None in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16283, 9), 531}, // 600 BitPiece in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16315, 7), 535}, // 601 Constu in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16222, 6), 527}, // 602 Deref in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16233, 6), 529}, // 603 Minus in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16228, 5), 528}, // 604 Plus in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16272, 11), 530}, // 605 PlusUconst in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16304, 11), 534}, // 606 StackValue in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16292, 5), 532}, // 607 Swap in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16297, 7), 533}, // 608 Xderef in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16331, 10), 536}, // 609 ConstType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(16354, 13), 538}, // 610 RestrictType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(16341, 13), 537}, // 611 VolatileType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(19645, 16), 658}, // 612 AliasScopeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17148, 8), 558}, // 613 Aliased in SPV_OPERAND_TYPE_DECORATION
  {IR(18295, 15), 613}, // 614 AliasedPointer in SPV_OPERAND_TYPE_DECORATION
  {IR(18310, 18), 613}, // 615 AliasedPointerEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(17626, 10), 582}, // 616 Alignment in SPV_OPERAND_TYPE_DECORATION
  {IR(17670, 12), 584}, // 617 AlignmentId in SPV_OPERAND_TYPE_DECORATION
  {IR(16999, 12), 545}, // 618 ArrayStride in SPV_OPERAND_TYPE_DECORATION
  {IR(18050, 17), 601}, // 619 ArrayStrideIdEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(19195, 15), 646}, // 620 BankBitsALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19210, 14), 646}, // 621 BankBitsINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18404, 7), 617}, // 622 BankNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18908, 16), 639}, // 623 BankwidthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18924, 15), 639}, // 624 BankwidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17303, 8), 571}, // 625 Binding in SPV_OPERAND_TYPE_DECORATION
  {IR(18429, 16), 619}, // 626 BindlessImageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18411, 18), 618}, // 627 BindlessSamplerNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16963, 6), 541}, // 628 Block in SPV_OPERAND_TYPE_DECORATION
  {IR(17810, 22), 591}, // 629 BlockMatchSamplerQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(17788, 22), 590}, // 630 BlockMatchTextureQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(18460, 13), 621}, // 631 BoundImageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18445, 15), 620}, // 632 BoundSamplerNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16969, 12), 542}, // 633 BufferBlock in SPV_OPERAND_TYPE_DECORATION
  {IR(19805, 21), 663}, // 634 BufferLocationALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19826, 20), 663}, // 635 BufferLocationINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17080, 8), 550}, // 636 BuiltIn in SPV_OPERAND_TYPE_DECORATION
  {IR(19364, 20), 651}, // 637 BurstCoalesceALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19384, 19), 651}, // 638 BurstCoalesceINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17046, 8), 549}, // 639 CPacked in SPV_OPERAND_TYPE_DECORATION
  {IR(21052, 22), 686}, // 640 CacheControlLoadINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(21111, 23), 687}, // 641 CacheControlStoreINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19403, 16), 652}, // 642 CacheSizeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19419, 15), 652}, // 643 CacheSizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17113, 9), 554}, // 644 Centroid in SPV_OPERAND_TYPE_DECORATION
  {IR(18513, 13), 624}, // 645 ClobberINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17174, 9), 561}, // 646 Coherent in SPV_OPERAND_TYPE_DECORATION
  {IR(16990, 9), 544}, // 647 ColMajor in SPV_OPERAND_TYPE_DECORATION
  {IR(17287, 10), 569}, // 648 Component in SPV_OPERAND_TYPE_DECORATION
  {IR(20999, 17), 685}, // 649 ConditionalINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20228, 28), 673}, // 650 ConduitKernelArgumentALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20256, 27), 673}, // 651 ConduitKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17165, 9), 560}, // 652 Constant in SPV_OPERAND_TYPE_DECORATION
  {IR(18659, 14), 631}, // 653 CounterBuffer in SPV_OPERAND_TYPE_DECORATION
  {IR(17311, 14), 572}, // 654 DescriptorSet in SPV_OPERAND_TYPE_DECORATION
  {IR(19434, 29), 653}, // 655 DontStaticallyCoalesceALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19463, 28), 653}, // 656 DontStaticallyCoalesceINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19017, 17), 642}, // 657 DoublepumpALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19034, 16), 642}, // 658 DoublepumpINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17832, 18), 592}, // 659 ExplicitInterpAMD in SPV_OPERAND_TYPE_DECORATION
  {IR(17496, 15), 578}, // 660 FPFastMathMode in SPV_OPERAND_TYPE_DECORATION
  {IR(20090, 26), 670}, // 661 FPMaxErrorDecorationINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17446, 15), 577}, // 662 FPRoundingMode in SPV_OPERAND_TYPE_DECORATION
  {IR(17102, 5), 552}, // 663 Flat in SPV_OPERAND_TYPE_DECORATION
  {IR(19224, 21), 647}, // 664 ForcePow2DepthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19245, 20), 647}, // 665 ForcePow2DepthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17398, 14), 576}, // 666 FuncParamAttr in SPV_OPERAND_TYPE_DECORATION
  {IR(18570, 21), 627}, // 667 FuncParamIOKindINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18801, 24), 635}, // 668 FunctionDenormModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19919, 31), 665}, // 669 FunctionFloatingPointModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18744, 26), 634}, // 670 FunctionRoundingModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19555, 26), 656}, // 671 FuseLoopsInFunctionALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19581, 25), 656}, // 672 FuseLoopsInFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17035, 11), 548}, // 673 GLSLPacked in SPV_OPERAND_TYPE_DECORATION
  {IR(17024, 11), 547}, // 674 GLSLShared in SPV_OPERAND_TYPE_DECORATION
  {IR(18633, 26), 630}, // 675 GlobalVariableOffsetINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18373, 31), 616}, // 676 HitObjectShaderRecordBufferEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(18343, 30), 615}, // 677 HitObjectShaderRecordBufferNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18673, 24), 631}, // 678 HlslCounterBufferGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(18710, 19), 632}, // 679 HlslSemanticGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(20850, 16), 682}, // 680 HostAccessINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19846, 20), 664}, // 681 IOPipeStorageALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19866, 19), 664}, // 682 IOPipeStorageINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20942, 29), 684}, // 683 ImplementInRegisterMapALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20971, 28), 684}, // 684 ImplementInRegisterMapINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17297, 6), 570}, // 685 Index in SPV_OPERAND_TYPE_DECORATION
  {IR(20913, 15), 683}, // 686 InitModeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20928, 14), 683}, // 687 InitModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19674, 25), 660}, // 688 InitiationIntervalALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19699, 24), 660}, // 689 InitiationIntervalINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17605, 21), 581}, // 690 InputAttachmentIndex in SPV_OPERAND_TYPE_DECORATION
  {IR(17129, 10), 556}, // 691 Invariant in SPV_OPERAND_TYPE_DECORATION
  {IR(20167, 31), 672}, // 692 LatencyControlConstraintALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20198, 30), 672}, // 693 LatencyControlConstraintINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20116, 26), 671}, // 694 LatencyControlLabelALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20142, 25), 671}, // 695 LatencyControlLabelINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17573, 18), 579}, // 696 LinkageAttributes in SPV_OPERAND_TYPE_DECORATION
  {IR(17278, 9), 568}, // 697 Location in SPV_OPERAND_TYPE_DECORATION
  {IR(20346, 34), 675}, // 698 MMHostInterfaceAddressWidthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20380, 33), 675}, // 699 MMHostInterfaceAddressWidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20413, 31), 676}, // 700 MMHostInterfaceDataWidthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20444, 30), 676}, // 701 MMHostInterfaceDataWidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20474, 29), 677}, // 702 MMHostInterfaceLatencyALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20503, 28), 677}, // 703 MMHostInterfaceLatencyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20634, 30), 679}, // 704 MMHostInterfaceMaxBurstALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20664, 29), 679}, // 705 MMHostInterfaceMaxBurstINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20565, 35), 678}, // 706 MMHostInterfaceReadWriteModeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20600, 34), 678}, // 707 MMHostInterfaceReadWriteModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20693, 33), 680}, // 708 MMHostInterfaceWaitRequestALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20726, 32), 680}, // 709 MMHostInterfaceWaitRequestINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19606, 20), 657}, // 710 MathOpDSPModeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19626, 19), 657}, // 711 MathOpDSPModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17011, 13), 546}, // 712 MatrixStride in SPV_OPERAND_TYPE_DECORATION
  {IR(17636, 14), 583}, // 713 MaxByteOffset in SPV_OPERAND_TYPE_DECORATION
  {IR(17682, 16), 585}, // 714 MaxByteOffsetId in SPV_OPERAND_TYPE_DECORATION
  {IR(19723, 21), 661}, // 715 MaxConcurrencyALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19744, 20), 661}, // 716 MaxConcurrencyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18939, 23), 640}, // 717 MaxPrivateCopiesALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18962, 22), 640}, // 718 MaxPrivateCopiesINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19050, 20), 643}, // 719 MaxReplicatesALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19070, 19), 643}, // 720 MaxReplicatesINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20010, 18), 668}, // 721 MediaBlockIOINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18328, 15), 614}, // 722 MemberOffsetNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18854, 13), 637}, // 723 MemoryALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18867, 12), 637}, // 724 MemoryINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19130, 12), 645}, // 725 MergeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19142, 11), 645}, // 726 MergeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19661, 13), 659}, // 727 NoAliasINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17591, 14), 580}, // 728 NoContraction in SPV_OPERAND_TYPE_DECORATION
  {IR(17088, 14), 551}, // 729 NoPerspective in SPV_OPERAND_TYPE_DECORATION
  {IR(17742, 13), 587}, // 730 NoSignedWrap in SPV_OPERAND_TYPE_DECORATION
  {IR(17755, 15), 588}, // 731 NoUnsignedWrap in SPV_OPERAND_TYPE_DECORATION
  {IR(17882, 20), 594}, // 732 NodeMaxPayloadsAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17850, 32), 593}, // 733 NodeSharesPayloadLimitsWithAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17195, 12), 563}, // 734 NonReadable in SPV_OPERAND_TYPE_DECORATION
  {IR(18235, 11), 611}, // 735 NonUniform in SPV_OPERAND_TYPE_DECORATION
  {IR(18246, 14), 611}, // 736 NonUniformEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(17183, 12), 562}, // 737 NonWritable in SPV_OPERAND_TYPE_DECORATION
  {IR(18879, 15), 638}, // 738 NumbanksALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18894, 14), 638}, // 739 NumbanksINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17325, 7), 573}, // 740 Offset in SPV_OPERAND_TYPE_DECORATION
  {IR(18067, 12), 602}, // 741 OffsetIdEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(18079, 19), 603}, // 742 OverrideCoverageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18098, 14), 604}, // 743 PassthroughNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17107, 6), 553}, // 744 Patch in SPV_OPERAND_TYPE_DECORATION
  {IR(18022, 28), 600}, // 745 PayloadDispatchIndirectAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17997, 25), 599}, // 746 PayloadNodeArraySizeAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17945, 25), 597}, // 747 PayloadNodeBaseIndexAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17925, 20), 596}, // 748 PayloadNodeNameAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17970, 27), 598}, // 749 PayloadNodeSparseArrayAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(18159, 16), 607}, // 750 PerPrimitiveEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(18175, 15), 607}, // 751 PerPrimitiveNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18200, 10), 609}, // 752 PerTaskNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18210, 13), 610}, // 753 PerVertexKHR in SPV_OPERAND_TYPE_DECORATION
  {IR(18223, 12), 610}, // 754 PerVertexNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18190, 10), 608}, // 755 PerViewNV in SPV_OPERAND_TYPE_DECORATION
  {IR(19764, 21), 662}, // 756 PipelineEnableALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19785, 20), 662}, // 757 PipelineEnableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19491, 15), 654}, // 758 PrefetchALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19506, 14), 654}, // 759 PrefetchINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18487, 26), 623}, // 760 ReferencedIndirectlyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18825, 15), 636}, // 761 RegisterALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18840, 14), 636}, // 762 RegisterINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20283, 32), 674}, // 763 RegisterMapKernelArgumentALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20315, 31), 674}, // 764 RegisterMapKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16939, 17), 539}, // 765 RelaxedPrecision in SPV_OPERAND_TYPE_DECORATION
  {IR(17139, 9), 557}, // 766 Restrict in SPV_OPERAND_TYPE_DECORATION
  {IR(18260, 16), 612}, // 767 RestrictPointer in SPV_OPERAND_TYPE_DECORATION
  {IR(18276, 19), 612}, // 768 RestrictPointerEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(16981, 9), 543}, // 769 RowMajor in SPV_OPERAND_TYPE_DECORATION
  {IR(18473, 14), 622}, // 770 SIMTCallINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17122, 7), 555}, // 771 Sample in SPV_OPERAND_TYPE_DECORATION
  {IR(17251, 20), 566}, // 772 SaturatedConversion in SPV_OPERAND_TYPE_DECORATION
  {IR(17698, 44), 586}, // 773 SaturatedToLargestFloat8NormalConversionEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(18131, 28), 606}, // 774 SecondaryViewportRelativeNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18526, 17), 625}, // 775 SideEffectsINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19089, 21), 644}, // 776 SimpleDualPortALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19110, 20), 644}, // 777 SimpleDualPortINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19950, 25), 666}, // 778 SingleElementVectorINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18984, 17), 641}, // 779 SinglepumpALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19001, 16), 641}, // 780 SinglepumpINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16956, 7), 540}, // 781 SpecId in SPV_OPERAND_TYPE_DECORATION
  {IR(20758, 27), 681}, // 782 StableKernelArgumentALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20785, 26), 681}, // 783 StableKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18618, 15), 629}, // 784 StackCallINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19520, 18), 655}, // 785 StallEnableALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19538, 17), 655}, // 786 StallEnableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20028, 16), 669}, // 787 StallFreeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20044, 15), 669}, // 788 StallFreeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17271, 7), 567}, // 789 Stream in SPV_OPERAND_TYPE_DECORATION
  {IR(19265, 17), 648}, // 790 StridesizeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19282, 16), 648}, // 791 StridesizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17902, 23), 595}, // 792 TrackFinishWritingAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(19327, 19), 650}, // 793 TrueDualPortALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19346, 18), 650}, // 794 TrueDualPortINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17207, 8), 564}, // 795 Uniform in SPV_OPERAND_TYPE_DECORATION
  {IR(17241, 10), 565}, // 796 UniformId in SPV_OPERAND_TYPE_DECORATION
  {IR(18697, 13), 632}, // 797 UserSemantic in SPV_OPERAND_TYPE_DECORATION
  {IR(18729, 15), 633}, // 798 UserTypeGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(19975, 35), 667}, // 799 VectorComputeCallableFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18591, 27), 628}, // 800 VectorComputeFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18543, 27), 626}, // 801 VectorComputeVariableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18112, 19), 605}, // 802 ViewportRelativeNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17156, 9), 559}, // 803 Volatile in SPV_OPERAND_TYPE_DECORATION
  {IR(17770, 18), 589}, // 804 WeightTextureQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(19298, 15), 649}, // 805 WordsizeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19313, 14), 649}, // 806 WordsizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17332, 10), 574}, // 807 XfbBuffer in SPV_OPERAND_TYPE_DECORATION
  {IR(17342, 10), 575}, // 808 XfbStride in SPV_OPERAND_TYPE_DECORATION
  {IR(21134, 3), 688}, // 809 1D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21137, 3), 689}, // 810 2D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21140, 3), 690}, // 811 3D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21153, 7), 693}, // 812 Buffer in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21143, 5), 691}, // 813 Cube in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21148, 5), 692}, // 814 Rect in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21160, 12), 694}, // 815 SubpassData in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21172, 17), 695}, // 816 TileImageDataEXT in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21984, 15), 748}, // 817 CoalescingAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21615, 15), 726}, // 818 ContractionOff in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10512, 18), 740}, // 819 DenormFlushToZero in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10497, 15), 739}, // 820 DenormPreserve in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21385, 13), 709}, // 821 DepthGreater in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21398, 10), 710}, // 822 DepthLess in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21370, 15), 708}, // 823 DepthReplacing in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21408, 15), 711}, // 824 DepthUnchanged in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22405, 25), 766}, // 825 DerivativeGroupLinearKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22430, 24), 766}, // 826 DerivativeGroupLinearNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22358, 24), 765}, // 827 DerivativeGroupQuadsKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22382, 23), 765}, // 828 DerivativeGroupQuadsNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21932, 29), 746}, // 829 EarlyAndLateFragmentTestsAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21337, 19), 705}, // 830 EarlyFragmentTests in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22915, 18), 786}, // 831 FPFastMathDefault in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21642, 10), 728}, // 832 Finalizer in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22730, 26), 778}, // 833 FloatingPointModeALTINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22756, 27), 779}, // 834 FloatingPointModeIEEEINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21630, 12), 727}, // 835 Initializer in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21459, 11), 715}, // 836 InputLines in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21470, 20), 716}, // 837 InputLinesAdjacency in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21447, 12), 714}, // 838 InputPoints in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21500, 24), 718}, // 839 InputTrianglesAdjacency in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21189, 12), 696}, // 840 Invocations in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21999, 15), 749}, // 841 IsApiEntryAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21530, 9), 720}, // 842 Isolines in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21423, 10), 712}, // 843 LocalSize in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21433, 14), 713}, // 844 LocalSizeHint in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21710, 16), 733}, // 845 LocalSizeHintId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21698, 12), 732}, // 846 LocalSizeId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22014, 21), 750}, // 847 MaxNodeRecursionAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22059, 21), 753}, // 848 MaxNumWorkgroupsAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22805, 16), 781}, // 849 MaxWorkDimINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22783, 22), 780}, // 850 MaxWorkgroupSizeINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22891, 24), 785}, // 851 MaximallyReconvergesKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23006, 22), 790}, // 852 MaximumRegistersINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23028, 24), 791}, // 853 MaximumRegistersIdINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22983, 23), 789}, // 854 NamedBarrierCountINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23103, 27), 792}, // 855 NamedMaximumRegistersINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22821, 20), 782}, // 856 NoGlobalOffsetINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21726, 34), 734}, // 857 NonCoherentColorAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21760, 34), 735}, // 858 NonCoherentDepthAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21794, 36), 736}, // 859 NonCoherentStencilAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21878, 34), 744}, // 860 NonCoherentTileAttachmentReadQCOM in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22841, 22), 783}, // 861 NumSIMDWorkitemsINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21321, 16), 704}, // 862 OriginLowerLeft in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21305, 16), 703}, // 863 OriginUpperLeft in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21567, 16), 723}, // 864 OutputLineStrip in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22290, 15), 763}, // 865 OutputLinesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22305, 14), 763}, // 866 OutputLinesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21554, 13), 722}, // 867 OutputPoints in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22319, 20), 764}, // 868 OutputPrimitivesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22339, 19), 764}, // 869 OutputPrimitivesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21583, 20), 724}, // 870 OutputTriangleStrip in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22454, 19), 767}, // 871 OutputTrianglesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22473, 18), 767}, // 872 OutputTrianglesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21539, 15), 721}, // 873 OutputVertices in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21286, 19), 702}, // 874 PixelCenterInteger in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22491, 25), 768}, // 875 PixelInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22516, 27), 769}, // 876 PixelInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21356, 10), 706}, // 877 PointMode in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21860, 18), 738}, // 878 PostDepthCoverage in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22231, 19), 760}, // 879 QuadDerivativesKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21524, 6), 719}, // 880 Quads in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22957, 26), 788}, // 881 RegisterMapInterfaceINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22250, 20), 761}, // 882 RequireFullQuadsKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10555, 16), 742}, // 883 RoundingModeRTE in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22709, 21), 777}, // 884 RoundingModeRTNINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22688, 21), 776}, // 885 RoundingModeRTPINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10571, 16), 743}, // 886 RoundingModeRTZ in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22543, 26), 770}, // 887 SampleInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22569, 28), 771}, // 888 SampleInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22863, 28), 784}, // 889 SchedulerTargetFmaxMhzINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(12803, 23), 774}, // 890 Shader64BitIndexingEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(7142, 16), 752}, // 891 ShaderIndexAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22597, 31), 772}, // 892 ShadingRateInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22628, 33), 773}, // 893 ShadingRateInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22661, 27), 775}, // 894 SharedLocalMemorySizeINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22270, 20), 762}, // 895 SharesInputWithAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10530, 25), 741}, // 896 SignedZeroInfNanPreserve in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21201, 13), 697}, // 897 SpacingEqual in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21214, 22), 698}, // 898 SpacingFractionalEven in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21236, 21), 699}, // 899 SpacingFractionalOdd in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22035, 24), 751}, // 900 StaticNumWorkgroupsAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22184, 25), 758}, // 901 StencilRefGreaterBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22108, 26), 755}, // 902 StencilRefGreaterFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22209, 22), 759}, // 903 StencilRefLessBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22134, 23), 756}, // 904 StencilRefLessFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21961, 23), 747}, // 905 StencilRefReplacingEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22157, 27), 757}, // 906 StencilRefUnchangedBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22080, 28), 754}, // 907 StencilRefUnchangedFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22933, 24), 787}, // 908 StreamingInterfaceINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(6249, 13), 729}, // 909 SubgroupSize in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21830, 30), 737}, // 910 SubgroupUniformControlFlowKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21652, 22), 730}, // 911 SubgroupsPerWorkgroup in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21674, 24), 731}, // 912 SubgroupsPerWorkgroupId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21912, 20), 745}, // 913 TileShadingRateQCOM in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21490, 10), 717}, // 914 Triangles in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21603, 12), 725}, // 915 VecTypeHint in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21271, 15), 701}, // 916 VertexOrderCcw in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21257, 14), 700}, // 917 VertexOrderCw in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21366, 4), 707}, // 918 Xfb in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23268, 10), 804}, // 919 AnyHitKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23278, 9), 804}, // 920 AnyHitNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23329, 12), 807}, // 921 CallableKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23341, 11), 807}, // 922 CallableNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23287, 14), 805}, // 923 ClosestHitKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23301, 13), 805}, // 924 ClosestHitNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(16322, 9), 797}, // 925 Fragment in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23180, 10), 798}, // 926 GLCompute in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(5730, 9), 796}, // 927 Geometry in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23237, 16), 803}, // 928 IntersectionKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23253, 15), 803}, // 929 IntersectionNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(5497, 7), 799}, // 930 Kernel in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23360, 8), 809}, // 931 MeshEXT in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23197, 7), 801}, // 932 MeshNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23314, 8), 806}, // 933 MissKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23322, 7), 806}, // 934 MissNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23204, 17), 802}, // 935 RayGenerationKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23221, 16), 802}, // 936 RayGenerationNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23352, 8), 808}, // 937 TaskEXT in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23190, 7), 800}, // 938 TaskNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23137, 20), 794}, // 939 TessellationControl in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23157, 23), 795}, // 940 TessellationEvaluation in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23130, 7), 793}, // 941 Vertex in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23377, 12), 811}, // 942 FlushToZero in SPV_OPERAND_TYPE_FPDENORM_MODE
  {IR(23368, 9), 810}, // 943 Preserve in SPV_OPERAND_TYPE_FPDENORM_MODE
  {IR(23389, 12), 812}, // 944 BFloat16KHR in SPV_OPERAND_TYPE_FPENCODING
  {IR(23401, 14), 813}, // 945 Float8E4M3EXT in SPV_OPERAND_TYPE_FPENCODING
  {IR(23415, 14), 814}, // 946 Float8E5M2EXT in SPV_OPERAND_TYPE_FPENCODING
  {IR(23434, 4), 816}, // 947 ALT in SPV_OPERAND_TYPE_FPOPERATION_MODE
  {IR(23429, 5), 815}, // 948 IEEE in SPV_OPERAND_TYPE_FPOPERATION_MODE
  {IR(23472, 14), 823}, // 949 AllowContract in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23486, 23), 823}, // 950 AllowContractFastINTEL in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23509, 13), 824}, // 951 AllowReassoc in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23522, 18), 824}, // 952 AllowReassocINTEL in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23456, 11), 821}, // 953 AllowRecip in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23540, 15), 825}, // 954 AllowTransform in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23467, 5), 822}, // 955 Fast in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23452, 4), 820}, // 956 NSZ in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(15918, 5), 817}, // 957 None in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23445, 7), 819}, // 958 NotInf in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23438, 7), 818}, // 959 NotNaN in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23555, 4), 826}, // 960 RTE in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(23567, 4), 829}, // 961 RTN in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(23563, 4), 828}, // 962 RTP in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(23559, 4), 827}, // 963 RTZ in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(23603, 18), 832}, // 964 Horizontal2Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(23621, 18), 833}, // 965 Horizontal4Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(23571, 16), 830}, // 966 Vertical2Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(23587, 16), 831}, // 967 Vertical4Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(23662, 6), 838}, // 968 Const in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(23646, 11), 836}, // 969 DontInline in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(23639, 7), 835}, // 970 Inline in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(15918, 5), 834}, // 971 None in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(14800, 11), 839}, // 972 OptNoneEXT in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(14811, 13), 839}, // 973 OptNoneINTEL in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(23657, 5), 837}, // 974 Pure in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(23678, 6), 842}, // 975 ByVal in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23689, 8), 844}, // 976 NoAlias in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23697, 10), 845}, // 977 NoCapture in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23715, 12), 847}, // 978 NoReadWrite in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23707, 8), 846}, // 979 NoWrite in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23727, 21), 848}, // 980 RuntimeAlignedALTERA in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23748, 20), 848}, // 981 RuntimeAlignedINTEL in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23673, 5), 841}, // 982 Sext in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23684, 5), 843}, // 983 Sret in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23668, 5), 840}, // 984 Zext in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23803, 16), 852}, // 985 ClusteredReduce in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23789, 14), 851}, // 986 ExclusiveScan in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23775, 14), 850}, // 987 InclusiveScan in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23915, 28), 855}, // 988 PartitionedExclusiveScanEXT in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23943, 27), 855}, // 989 PartitionedExclusiveScanNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23860, 28), 854}, // 990 PartitionedInclusiveScanEXT in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23888, 27), 854}, // 991 PartitionedInclusiveScanNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23819, 21), 853}, // 992 PartitionedReduceEXT in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23840, 20), 853}, // 993 PartitionedReduceNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23768, 7), 849}, // 994 Reduce in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23970, 10), 856}, // 995 NoneINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(23980, 10), 857}, // 996 ReadINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(24001, 15), 859}, // 997 ReadWriteINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(23990, 11), 858}, // 998 WriteINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(24016, 5), 861}, // 999 Bias in SPV_OPERAND_TYPE_IMAGE
  {IR(24030, 12), 864}, // 1000 ConstOffset in SPV_OPERAND_TYPE_IMAGE
  {IR(24042, 13), 866}, // 1001 ConstOffsets in SPV_OPERAND_TYPE_IMAGE
  {IR(24025, 5), 863}, // 1002 Grad in SPV_OPERAND_TYPE_IMAGE
  {IR(24021, 4), 862}, // 1003 Lod in SPV_OPERAND_TYPE_IMAGE
  {IR(24055, 19), 869}, // 1004 MakeTexelAvailable in SPV_OPERAND_TYPE_IMAGE
  {IR(24074, 22), 869}, // 1005 MakeTexelAvailableKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(24096, 17), 870}, // 1006 MakeTexelVisible in SPV_OPERAND_TYPE_IMAGE
  {IR(24113, 20), 870}, // 1007 MakeTexelVisibleKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(9330, 7), 868}, // 1008 MinLod in SPV_OPERAND_TYPE_IMAGE
  {IR(24133, 16), 871}, // 1009 NonPrivateTexel in SPV_OPERAND_TYPE_IMAGE
  {IR(24149, 19), 871}, // 1010 NonPrivateTexelKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(15918, 5), 860}, // 1011 None in SPV_OPERAND_TYPE_IMAGE
  {IR(24221, 12), 875}, // 1012 Nontemporal in SPV_OPERAND_TYPE_IMAGE
  {IR(17325, 7), 865}, // 1013 Offset in SPV_OPERAND_TYPE_IMAGE
  {IR(24233, 8), 876}, // 1014 Offsets in SPV_OPERAND_TYPE_IMAGE
  {IR(17122, 7), 867}, // 1015 Sample in SPV_OPERAND_TYPE_IMAGE
  {IR(24199, 11), 873}, // 1016 SignExtend in SPV_OPERAND_TYPE_IMAGE
  {IR(24168, 14), 872}, // 1017 VolatileTexel in SPV_OPERAND_TYPE_IMAGE
  {IR(24182, 17), 872}, // 1018 VolatileTexelKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(24210, 11), 874}, // 1019 ZeroExtend in SPV_OPERAND_TYPE_IMAGE
  {IR(15815, 6), 891}, // 1020 Float in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24402, 10), 890}, // 1021 HalfFloat in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24337, 12), 885}, // 1022 SignedInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24349, 12), 886}, // 1023 SignedInt32 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24326, 11), 884}, // 1024 SignedInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24251, 11), 878}, // 1025 SnormInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24241, 10), 877}, // 1026 SnormInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24311, 15), 883}, // 1027 UnormInt101010 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24423, 17), 893}, // 1028 UnormInt101010_2 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24440, 16), 894}, // 1029 UnormInt10X6EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24573, 16), 901}, // 1030 UnormInt12X4EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24589, 16), 902}, // 1031 UnormInt14X2EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24272, 11), 880}, // 1032 UnormInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24412, 11), 892}, // 1033 UnormInt24 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24496, 20), 897}, // 1034 UnormInt2_101010EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24262, 10), 879}, // 1035 UnormInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24297, 14), 882}, // 1036 UnormShort555 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24283, 14), 881}, // 1037 UnormShort565 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24516, 19), 898}, // 1038 UnsignedInt10X6EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24535, 19), 899}, // 1039 UnsignedInt12X4EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24554, 19), 900}, // 1040 UnsignedInt14X2EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24374, 14), 888}, // 1041 UnsignedInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24388, 14), 889}, // 1042 UnsignedInt32 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24361, 13), 887}, // 1043 UnsignedInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24456, 20), 895}, // 1044 UnsignedIntRaw10EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24476, 20), 896}, // 1045 UnsignedIntRaw12EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24607, 2), 904}, // 1046 A in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24708, 5), 922}, // 1047 ABGR in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24629, 5), 910}, // 1048 ARGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24624, 5), 909}, // 1049 BGRA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24666, 6), 916}, // 1050 Depth in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24672, 13), 917}, // 1051 DepthStencil in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24634, 10), 911}, // 1052 Intensity in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24644, 10), 912}, // 1053 Luminance in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24605, 2), 903}, // 1054 R in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24612, 3), 906}, // 1055 RA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24609, 3), 905}, // 1056 RG in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24615, 4), 907}, // 1057 RGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24619, 5), 908}, // 1058 RGBA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24661, 5), 915}, // 1059 RGBx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24657, 4), 914}, // 1060 RGx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24654, 3), 913}, // 1061 Rx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24702, 6), 921}, // 1062 sBGRA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24685, 5), 918}, // 1063 sRGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24696, 6), 920}, // 1064 sRGBA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24690, 6), 919}, // 1065 sRGBx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24713, 28), 923}, // 1066 InitOnDeviceReprogramALTERA in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(24741, 27), 923}, // 1067 InitOnDeviceReprogramINTEL in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(24768, 24), 924}, // 1068 InitOnDeviceResetALTERA in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(24792, 23), 924}, // 1069 InitOnDeviceResetINTEL in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(24815, 7), 925}, // 1070 NoWait in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(24822, 11), 926}, // 1071 WaitKernel in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(24833, 14), 927}, // 1072 WaitWorkGroup in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(24847, 12), 929}, // 1073 CmdExecTime in SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {IR(15918, 5), 928}, // 1074 None in SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {IR(24859, 13), 931}, // 1075 MayUsePrintf in SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {IR(15918, 5), 930}, // 1076 None in SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {IR(24872, 7), 932}, // 1077 Export in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(24879, 7), 933}, // 1078 Import in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(24886, 12), 934}, // 1079 LinkOnceODR in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(24912, 12), 936}, // 1080 CachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(24964, 17), 939}, // 1081 ConstCachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(24939, 25), 938}, // 1082 InvalidateAfterReadINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(24924, 15), 937}, // 1083 StreamingINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(24898, 14), 935}, // 1084 UncachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(25104, 22), 952}, // 1085 DependencyArrayALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25126, 21), 952}, // 1086 DependencyArrayINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24999, 19), 943}, // 1087 DependencyInfinite in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25018, 17), 944}, // 1088 DependencyLength in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24988, 11), 942}, // 1089 DontUnroll in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19674, 25), 950}, // 1090 InitiationIntervalALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19699, 24), 950}, // 1091 InitiationIntervalINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25063, 18), 947}, // 1092 IterationMultiple in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25147, 19), 954}, // 1093 LoopCoalesceALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25166, 18), 954}, // 1094 LoopCoalesceINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25309, 16), 958}, // 1095 LoopCountALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25325, 15), 958}, // 1096 LoopCountINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19723, 21), 951}, // 1097 MaxConcurrencyALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19744, 20), 951}, // 1098 MaxConcurrencyINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25184, 22), 955}, // 1099 MaxInterleavingALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25206, 21), 955}, // 1100 MaxInterleavingINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25049, 14), 946}, // 1101 MaxIterations in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25340, 27), 959}, // 1102 MaxReinvocationDelayALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25367, 26), 959}, // 1103 MaxReinvocationDelayINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25035, 14), 945}, // 1104 MinIterations in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25280, 15), 957}, // 1105 NoFusionALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25295, 14), 957}, // 1106 NoFusionINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(15918, 5), 940}, // 1107 None in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25091, 13), 949}, // 1108 PartialCount in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25081, 10), 948}, // 1109 PeelCount in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19764, 21), 953}, // 1110 PipelineEnableALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19785, 20), 953}, // 1111 PipelineEnableINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25227, 27), 956}, // 1112 SpeculatedIterationsALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25254, 26), 956}, // 1113 SpeculatedIterationsINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24981, 7), 941}, // 1114 Unroll in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25676, 27), 973}, // 1115 MatrixAPackedBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25624, 26), 971}, // 1116 MatrixAPackedFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25544, 23), 967}, // 1117 MatrixAPackedInt4INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25498, 23), 965}, // 1118 MatrixAPackedInt8INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25393, 29), 961}, // 1119 MatrixASignedComponentsINTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25590, 17), 969}, // 1120 MatrixATF32INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25703, 27), 974}, // 1121 MatrixBPackedBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25650, 26), 972}, // 1122 MatrixBPackedFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25567, 23), 968}, // 1123 MatrixBPackedInt4INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25521, 23), 966}, // 1124 MatrixBPackedInt8INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25422, 29), 962}, // 1125 MatrixBSignedComponentsINTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25607, 17), 970}, // 1126 MatrixBTF32INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25451, 21), 963}, // 1127 MatrixCBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25472, 26), 964}, // 1128 MatrixResultBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(15918, 5), 960}, // 1129 None in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25863, 20), 982}, // 1130 AliasScopeINTELMask in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25730, 8), 977}, // 1131 Aligned in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25738, 21), 979}, // 1132 MakePointerAvailable in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25759, 24), 979}, // 1133 MakePointerAvailableKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25783, 19), 980}, // 1134 MakePointerVisible in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25802, 22), 980}, // 1135 MakePointerVisibleKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25883, 17), 983}, // 1136 NoAliasINTELMask in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25824, 18), 981}, // 1137 NonPrivatePointer in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25842, 21), 981}, // 1138 NonPrivatePointerKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(15918, 5), 975}, // 1139 None in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(24221, 12), 978}, // 1140 Nontemporal in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(17156, 9), 976}, // 1141 Volatile in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25907, 8), 985}, // 1142 GLSL450 in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(25915, 7), 986}, // 1143 OpenCL in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(25900, 7), 984}, // 1144 Simple in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(25922, 7), 987}, // 1145 Vulkan in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(25929, 10), 987}, // 1146 VulkanKHR in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(25947, 8), 989}, // 1147 Acquire in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25963, 15), 991}, // 1148 AcquireRelease in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26067, 20), 997}, // 1149 AtomicCounterMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26046, 21), 996}, // 1150 CrossWorkgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26087, 12), 998}, // 1151 ImageMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26128, 14), 1000}, // 1152 MakeAvailable in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26142, 17), 1000}, // 1153 MakeAvailableKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26159, 12), 1001}, // 1154 MakeVisible in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26171, 15), 1001}, // 1155 MakeVisibleKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(15918, 5), 988}, // 1156 None in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26099, 13), 999}, // 1157 OutputMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26112, 16), 999}, // 1158 OutputMemoryKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25939, 8), 988}, // 1159 Relaxed in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25955, 8), 990}, // 1160 Release in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25978, 23), 992}, // 1161 SequentiallyConsistent in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26015, 15), 994}, // 1162 SubgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26001, 14), 993}, // 1163 UniformMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(17156, 9), 1002}, // 1164 Volatile in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26030, 16), 995}, // 1165 WorkgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26186, 10), 1003}, // 1166 AutoINTEL in SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS
  {IR(26201, 4), 1005}, // 1167 SAT in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(26214, 8), 1007}, // 1168 SAT_SYM in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(26205, 9), 1006}, // 1169 SAT_ZERO in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(26196, 5), 1004}, // 1170 WRAP in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(26222, 25), 1008}, // 1171 PackedVectorFormat4x8Bit in SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {IR(26247, 28), 1008}, // 1172 PackedVectorFormat4x8BitKHR in SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {IR(26288, 4), 1011}, // 1173 RND in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26321, 9), 1015}, // 1174 RND_CONV in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26330, 13), 1016}, // 1175 RND_CONV_ODD in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26301, 8), 1013}, // 1176 RND_INF in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26309, 12), 1014}, // 1177 RND_MIN_INF in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26292, 9), 1012}, // 1178 RND_ZERO in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26275, 4), 1009}, // 1179 TRN in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26279, 9), 1010}, // 1180 TRN_ZERO in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(15918, 5), 1017}, // 1181 None in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(26343, 25), 1018}, // 1182 RobustnessPerComponentNV in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(26368, 23), 1019}, // 1183 RobustnessPerElementNV in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(26460, 27), 1025}, // 1184 CullBackFacingTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26487, 28), 1026}, // 1185 CullFrontFacingTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26529, 16), 1028}, // 1186 CullNoOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26515, 14), 1027}, // 1187 CullOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26599, 30), 1031}, // 1188 ForceOpacityMicromap2StateEXT in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26401, 12), 1022}, // 1189 NoOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(16670, 8), 1020}, // 1190 NoneKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26391, 10), 1021}, // 1191 OpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26586, 13), 1030}, // 1192 SkipAABBsKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26562, 24), 1029}, // 1193 SkipBuiltinPrimitivesNV in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26436, 24), 1024}, // 1194 SkipClosestHitShaderKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26545, 17), 1029}, // 1195 SkipTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26413, 23), 1023}, // 1196 TerminateOnFirstHitKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26670, 37), 1033}, // 1197 RayQueryCandidateIntersectionAABBKHR in SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {IR(26629, 41), 1032}, // 1198 RayQueryCandidateIntersectionTriangleKHR in SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {IR(26785, 42), 1036}, // 1199 RayQueryCommittedIntersectionGeneratedKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(26707, 37), 1034}, // 1200 RayQueryCommittedIntersectionNoneKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(26744, 41), 1035}, // 1201 RayQueryCommittedIntersectionTriangleKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(26827, 33), 1037}, // 1202 RayQueryCandidateIntersectionKHR in SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {IR(26860, 33), 1038}, // 1203 RayQueryCommittedIntersectionKHR in SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {IR(26905, 6), 1041}, // 1204 Clamp in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(26893, 12), 1040}, // 1205 ClampToEdge in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(15918, 5), 1039}, // 1206 None in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(26911, 7), 1042}, // 1207 Repeat in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(26918, 15), 1043}, // 1208 RepeatMirrored in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(26941, 7), 1045}, // 1209 Linear in SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {IR(26933, 8), 1044}, // 1210 Nearest in SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {IR(27006, 13), 1054}, // 1211 R11fG11fB10f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27048, 4), 1060}, // 1212 R16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27086, 9), 1065}, // 1213 R16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27019, 5), 1055}, // 1214 R16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27148, 5), 1074}, // 1215 R16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27219, 6), 1084}, // 1216 R16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26972, 5), 1049}, // 1217 R32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27126, 5), 1070}, // 1218 R32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27183, 6), 1079}, // 1219 R32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27236, 5), 1087}, // 1220 R64i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27230, 6), 1086}, // 1221 R64ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27052, 3), 1061}, // 1222 R8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27095, 8), 1066}, // 1223 R8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27153, 4), 1075}, // 1224 R8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27225, 5), 1085}, // 1225 R8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27039, 5), 1058}, // 1226 Rg16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27067, 10), 1063}, // 1227 Rg16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27000, 6), 1053}, // 1228 Rg16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27137, 6), 1072}, // 1229 Rg16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27206, 7), 1082}, // 1230 Rg16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26994, 6), 1052}, // 1231 Rg32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27131, 6), 1071}, // 1232 Rg32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27199, 7), 1081}, // 1233 Rg32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27044, 4), 1059}, // 1234 Rg8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27077, 9), 1064}, // 1235 Rg8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27143, 5), 1073}, // 1236 Rg8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27213, 6), 1083}, // 1237 Rg8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27031, 8), 1057}, // 1238 Rgb10A2 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27189, 10), 1080}, // 1239 Rgb10a2ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27024, 7), 1056}, // 1240 Rgba16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27055, 12), 1062}, // 1241 Rgba16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26964, 8), 1048}, // 1242 Rgba16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27111, 8), 1068}, // 1243 Rgba16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27166, 9), 1077}, // 1244 Rgba16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26956, 8), 1047}, // 1245 Rgba32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27103, 8), 1067}, // 1246 Rgba32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27157, 9), 1076}, // 1247 Rgba32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26977, 6), 1050}, // 1248 Rgba8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26983, 11), 1051}, // 1249 Rgba8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27119, 7), 1069}, // 1250 Rgba8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27175, 8), 1078}, // 1251 Rgba8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26948, 8), 1046}, // 1252 Unknown in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27241, 12), 1088}, // 1253 CrossDevice in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27253, 7), 1089}, // 1254 Device in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27279, 11), 1092}, // 1255 Invocation in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27290, 12), 1093}, // 1256 QueueFamily in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27302, 15), 1093}, // 1257 QueueFamilyKHR in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27317, 14), 1094}, // 1258 ShaderCallKHR in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27270, 9), 1091}, // 1259 Subgroup in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27260, 10), 1090}, // 1260 Workgroup in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27339, 12), 1097}, // 1261 DontFlatten in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(27331, 8), 1096}, // 1262 Flatten in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(15918, 5), 1095}, // 1263 None in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(27351, 29), 1098}, // 1264 IdentifierPossibleDuplicates in SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS
  {IR(15799, 8), 1100}, // 1265 Address in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15807, 8), 1101}, // 1266 Boolean in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15815, 6), 1102}, // 1267 Float in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15821, 7), 1103}, // 1268 Signed in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15828, 11), 1104}, // 1269 SignedChar in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15839, 9), 1105}, // 1270 Unsigned in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15848, 13), 1106}, // 1271 UnsignedChar in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15787, 12), 1099}, // 1272 Unspecified in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15861, 6), 1107}, // 1273 Class in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15867, 10), 1108}, // 1274 Structure in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15877, 6), 1109}, // 1275 Union in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15898, 20), 1111}, // 1276 ImportedDeclaration in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(15883, 15), 1110}, // 1277 ImportedModule in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(16007, 15), 1119}, // 1278 FlagArtificial in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16022, 13), 1120}, // 1279 FlagExplicit in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15995, 12), 1118}, // 1280 FlagFwdDecl in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16085, 21), 1124}, // 1281 FlagIndirectVariable in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15978, 17), 1117}, // 1282 FlagIsDefinition in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16162, 16), 1128}, // 1283 FlagIsEnumClass in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15966, 12), 1116}, // 1284 FlagIsLocal in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16146, 16), 1127}, // 1285 FlagIsOptimized in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15939, 14), 1114}, // 1286 FlagIsPrivate in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15923, 16), 1113}, // 1287 FlagIsProtected in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15953, 13), 1115}, // 1288 FlagIsPublic in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16106, 20), 1125}, // 1289 FlagLValueReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16050, 18), 1122}, // 1290 FlagObjectPointer in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16035, 15), 1121}, // 1291 FlagPrototyped in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16126, 20), 1126}, // 1292 FlagRValueReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16068, 17), 1123}, // 1293 FlagStaticMember in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16198, 24), 1130}, // 1294 FlagTypePassByReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16178, 20), 1129}, // 1295 FlagTypePassByValue in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(27380, 26), 1131}, // 1296 FlagUnknownPhysicalLayout in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15918, 5), 1112}, // 1297 None in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16283, 9), 1136}, // 1298 BitPiece in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16315, 7), 1140}, // 1299 Constu in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16222, 6), 1132}, // 1300 Deref in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16322, 9), 1141}, // 1301 Fragment in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16233, 6), 1134}, // 1302 Minus in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16228, 5), 1133}, // 1303 Plus in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16272, 11), 1135}, // 1304 PlusUconst in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16304, 11), 1139}, // 1305 StackValue in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16292, 5), 1137}, // 1306 Swap in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16297, 7), 1138}, // 1307 Xderef in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16367, 11), 1145}, // 1308 AtomicType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16331, 10), 1142}, // 1309 ConstType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16354, 13), 1144}, // 1310 RestrictType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16341, 13), 1143}, // 1311 VolatileType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(27441, 15), 1152}, // 1312 CPP_for_OpenCL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27406, 5), 1147}, // 1313 ESSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27411, 5), 1148}, // 1314 GLSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27461, 7), 1154}, // 1315 HERO_C in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27436, 5), 1151}, // 1316 HLSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27468, 5), 1155}, // 1317 NZSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27416, 9), 1149}, // 1318 OpenCL_C in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27425, 11), 1150}, // 1319 OpenCL_CPP in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27488, 5), 1159}, // 1320 Rust in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27456, 5), 1153}, // 1321 SYCL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27478, 6), 1157}, // 1322 Slang in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(26948, 8), 1146}, // 1323 Unknown in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27473, 5), 1156}, // 1324 WGSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27484, 4), 1158}, // 1325 Zig in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27575, 14), 1170}, // 1326 AtomicCounter in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27657, 16), 1176}, // 1327 CallableDataKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27673, 15), 1176}, // 1328 CallableDataNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27993, 17), 1186}, // 1329 CodeSectionINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27522, 15), 1165}, // 1330 CrossWorkgroup in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28010, 17), 1187}, // 1331 DeviceOnlyALTERA in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28027, 16), 1187}, // 1332 DeviceOnlyINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27545, 9), 1167}, // 1333 Function in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27554, 8), 1168}, // 1334 Generic in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27762, 16), 1179}, // 1335 HitAttributeKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27778, 15), 1179}, // 1336 HitAttributeNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27971, 22), 1185}, // 1337 HitObjectAttributeEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27926, 21), 1183}, // 1338 HitObjectAttributeNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28043, 15), 1188}, // 1339 HostOnlyALTERA in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28058, 14), 1188}, // 1340 HostOnlyINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27589, 6), 1171}, // 1341 Image in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27688, 24), 1177}, // 1342 IncomingCallableDataKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27712, 23), 1177}, // 1343 IncomingCallableDataNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27793, 22), 1180}, // 1344 IncomingRayPayloadKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27815, 21), 1180}, // 1345 IncomingRayPayloadNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27509, 6), 1161}, // 1346 Input in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27641, 16), 1175}, // 1347 NodePayloadAMDX in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27515, 7), 1163}, // 1348 Output in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27879, 22), 1182}, // 1349 PhysicalStorageBuffer in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27901, 25), 1182}, // 1350 PhysicalStorageBufferEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27537, 8), 1166}, // 1351 Private in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27562, 13), 1169}, // 1352 PushConstant in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27735, 14), 1178}, // 1353 RayPayloadKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27749, 13), 1178}, // 1354 RayPayloadNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27836, 22), 1181}, // 1355 ShaderRecordBufferKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27858, 21), 1181}, // 1356 ShaderRecordBufferNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27595, 14), 1172}, // 1357 StorageBuffer in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27947, 24), 1184}, // 1358 TaskPayloadWorkgroupEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27622, 19), 1174}, // 1359 TileAttachmentQCOM in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27609, 13), 1173}, // 1360 TileImageEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(17207, 8), 1162}, // 1361 Uniform in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27493, 16), 1160}, // 1362 UniformConstant in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27260, 10), 1164}, // 1363 Workgroup in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24924, 15), 1192}, // 1364 StreamingINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(24898, 14), 1189}, // 1365 UncachedINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(28090, 15), 1191}, // 1366 WriteBackINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(28072, 18), 1190}, // 1367 WriteThroughINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(28116, 11), 1195}, // 1368 DecodeFunc in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(15918, 5), 1193}, // 1369 None in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(28105, 11), 1194}, // 1370 TensorView in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(26893, 12), 1198}, // 1371 ClampToEdge in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(17165, 9), 1197}, // 1372 Constant in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(26911, 7), 1199}, // 1373 Repeat in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(26918, 15), 1200}, // 1374 RepeatMirrored in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(28127, 10), 1196}, // 1375 Undefined in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(28180, 24), 1204}, // 1376 MakeElementAvailableARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(28204, 22), 1205}, // 1377 MakeElementVisibleARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(28226, 21), 1206}, // 1378 NonPrivateElementARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(28137, 8), 1201}, // 1379 NoneARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(28145, 15), 1202}, // 1380 NontemporalARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(28160, 20), 1203}, // 1381 OutOfBoundsValueARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
}};

IndexRange OperandNameRangeForKind(spv_operand_type_t type) {
  switch(type) {
    case SPV_OPERAND_TYPE_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_ADDRESSING_MODEL: return IR(3, 5);
    case SPV_OPERAND_TYPE_BUILT_IN: return IR(8, 150);
    case SPV_OPERAND_TYPE_CAPABILITY: return IR(158, 334);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(492, 8);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(500, 3);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(503, 2);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS: return IR(505, 19);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION: return IR(524, 10);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(534, 4);
    case SPV_OPERAND_TYPE_COMPONENT_TYPE: return IR(538, 15);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT: return IR(553, 4);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS: return IR(557, 6);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE: return IR(563, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE: return IR(566, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT: return IR(569, 4);
    case SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(573, 8);
    case SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE: return IR(581, 3);
    case SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS: return IR(584, 16);
    case SPV_OPERAND_TYPE_DEBUG_OPERATION: return IR(600, 9);
    case SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER: return IR(609, 3);
    case SPV_OPERAND_TYPE_DECORATION: return IR(612, 197);
    case SPV_OPERAND_TYPE_DIMENSIONALITY: return IR(809, 8);
    case SPV_OPERAND_TYPE_EXECUTION_MODE: return IR(817, 102);
    case SPV_OPERAND_TYPE_EXECUTION_MODEL: return IR(919, 23);
    case SPV_OPERAND_TYPE_FPDENORM_MODE: return IR(942, 2);
    case SPV_OPERAND_TYPE_FPENCODING: return IR(944, 3);
    case SPV_OPERAND_TYPE_FPOPERATION_MODE: return IR(947, 2);
    case SPV_OPERAND_TYPE_FP_FAST_MATH_MODE: return IR(949, 11);
    case SPV_OPERAND_TYPE_FP_ROUNDING_MODE: return IR(960, 4);
    case SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE: return IR(964, 4);
    case SPV_OPERAND_TYPE_FUNCTION_CONTROL: return IR(968, 7);
    case SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE: return IR(975, 10);
    case SPV_OPERAND_TYPE_GROUP_OPERATION: return IR(985, 10);
    case SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER: return IR(995, 4);
    case SPV_OPERAND_TYPE_IMAGE: return IR(999, 21);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE: return IR(1020, 26);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER: return IR(1046, 20);
    case SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER: return IR(1066, 4);
    case SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS: return IR(1070, 3);
    case SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO: return IR(1073, 2);
    case SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS: return IR(1075, 2);
    case SPV_OPERAND_TYPE_LINKAGE_TYPE: return IR(1077, 3);
    case SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL: return IR(1080, 5);
    case SPV_OPERAND_TYPE_LOOP_CONTROL: return IR(1085, 30);
    case SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(1115, 15);
    case SPV_OPERAND_TYPE_MEMORY_ACCESS: return IR(1130, 12);
    case SPV_OPERAND_TYPE_MEMORY_MODEL: return IR(1142, 5);
    case SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID: return IR(1147, 19);
    case SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS: return IR(1166, 1);
    case SPV_OPERAND_TYPE_OVERFLOW_MODES: return IR(1167, 4);
    case SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT: return IR(1171, 2);
    case SPV_OPERAND_TYPE_QUANTIZATION_MODES: return IR(1173, 8);
    case SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS: return IR(1181, 3);
    case SPV_OPERAND_TYPE_RAY_FLAGS: return IR(1184, 13);
    case SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE: return IR(1197, 2);
    case SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE: return IR(1199, 3);
    case SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION: return IR(1202, 2);
    case SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE: return IR(1204, 5);
    case SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE: return IR(1209, 2);
    case SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT: return IR(1211, 42);
    case SPV_OPERAND_TYPE_SCOPE_ID: return IR(1253, 8);
    case SPV_OPERAND_TYPE_SELECTION_CONTROL: return IR(1261, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS: return IR(1264, 1);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(1265, 8);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(1273, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(1276, 2);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS: return IR(1278, 20);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION: return IR(1298, 10);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(1308, 4);
    case SPV_OPERAND_TYPE_SOURCE_LANGUAGE: return IR(1312, 14);
    case SPV_OPERAND_TYPE_STORAGE_CLASS: return IR(1326, 38);
    case SPV_OPERAND_TYPE_STORE_CACHE_CONTROL: return IR(1364, 4);
    case SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS: return IR(1368, 3);
    case SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE: return IR(1371, 5);
    case SPV_OPERAND_TYPE_TENSOR_OPERANDS: return IR(1376, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_IMAGE: return IR(999, 21);
    case SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS: return IR(1130, 12);
    case SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT: return IR(1171, 2);
    case SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS: return IR(557, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(1115, 15);
    case SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS: return IR(1181, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_FPENCODING: return IR(944, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS: return IR(1376, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_CAPABILITY: return IR(158, 334);
    default: break;
  }
  return IR(0,0);
}

// Instruction descriptions, ordered by opcode.
// The fields in order are:
//   opcode
//   a boolean indicating if the instruction produces a result ID
//   a boolean indicating if the instruction result ID has a type
//   operands, an IndexRange into kOperandSpans
//   opcode name (without the 'Op' prefix), a character-counting IndexRange into kStrings
//   aliases, an IndexRange into kAliasSpans
//   capabilities, an IndexRange into kCapabilitySpans
//   extensions, as an IndexRange into kExtensionSpans
//   version, first version of SPIR-V that has it
//   lastVersion, last version of SPIR-V that has it
static const std::array<InstructionDesc, 866> kInstructionDesc{{
  {spv::Op::OpNop, false, false, IR(0, 0), IR(28247, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpUndef, true, true, IR(39, 2), IR(28303, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpSourceContinued, false, false, IR(11, 1), IR(28309, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpSource, false, false, IR(41, 4), IR(28428, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpSourceExtension, false, false, IR(11, 1), IR(28435, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpName, false, false, IR(45, 2), IR(28451, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpMemberName, false, false, IR(47, 3), IR(28456, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpString, true, false, IR(50, 2), IR(28467, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpLine, false, false, IR(52, 3), IR(28474, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpExtension, false, false, IR(11, 1), IR(28479, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpExtInstImport, true, false, IR(50, 2), IR(28489, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpExtInst, true, true, IR(55, 4), IR(28549, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpMemoryModel, false, false, IR(59, 2), IR(28621, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpEntryPoint, false, false, IR(61, 4), IR(28695, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpExecutionMode, false, false, IR(65, 2), IR(28738, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpCapability, false, false, IR(67, 1), IR(28780, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpTypeVoid, true, false, IR(68, 1), IR(28791, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeBool, true, false, IR(68, 1), IR(28800, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeInt, true, false, IR(69, 3), IR(28809, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeFloat, true, false, IR(72, 3), IR(28854, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeVector, true, false, IR(75, 3), IR(28864, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeMatrix, true, false, IR(75, 3), IR(28875, 11), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeImage, true, false, IR(78, 9), IR(28999, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeSampler, true, false, IR(68, 1), IR(29009, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeSampledImage, true, false, IR(87, 2), IR(29021, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeArray, true, false, IR(89, 3), IR(29038, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeRuntimeArray, true, false, IR(87, 2), IR(29048, 17), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeStruct, true, false, IR(92, 2), IR(29065, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeOpaque, true, false, IR(50, 2), IR(29076, 11), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypePointer, true, false, IR(94, 3), IR(29118, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeFunction, true, false, IR(97, 3), IR(29130, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeEvent, true, false, IR(68, 1), IR(29143, 10), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeDeviceEvent, true, false, IR(68, 1), IR(29153, 16), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeReserveId, true, false, IR(68, 1), IR(29169, 14), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeQueue, true, false, IR(68, 1), IR(29183, 10), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypePipe, true, false, IR(100, 2), IR(29193, 9), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeForwardPointer, false, false, IR(102, 2), IR(29202, 19), IR(0, 0), IR(210, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantTrue, true, true, IR(39, 2), IR(29221, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantFalse, true, true, IR(39, 2), IR(29234, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstant, true, true, IR(104, 3), IR(17165, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantComposite, true, true, IR(107, 3), IR(29286, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantSampler, true, true, IR(110, 5), IR(29382, 16), IR(0, 0), IR(212, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantNull, true, true, IR(39, 2), IR(29398, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantTrue, true, true, IR(39, 2), IR(29411, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantFalse, true, true, IR(39, 2), IR(29428, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstant, true, true, IR(104, 3), IR(29446, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantComposite, true, true, IR(107, 3), IR(29459, 22), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantOp, true, true, IR(115, 3), IR(29522, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpFunction, true, true, IR(118, 4), IR(27545, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionParameter, true, true, IR(39, 2), IR(29571, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionEnd, false, false, IR(0, 0), IR(29589, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionCall, true, true, IR(122, 4), IR(29601, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpVariable, true, true, IR(126, 4), IR(29614, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpImageTexelPointer, true, true, IR(130, 5), IR(29623, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpLoad, true, true, IR(135, 4), IR(29681, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpStore, false, false, IR(139, 3), IR(29686, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCopyMemory, false, false, IR(142, 4), IR(29692, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCopyMemorySized, false, false, IR(146, 5), IR(29703, 16), IR(0, 0), IR(213, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpAccessChain, true, true, IR(122, 4), IR(29719, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpInBoundsAccessChain, true, true, IR(122, 4), IR(29731, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrAccessChain, true, true, IR(151, 5), IR(29751, 15), IR(0, 0), IR(215, 4), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpArrayLength, true, true, IR(156, 4), IR(29766, 12), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpGenericPtrMemSemantics, true, true, IR(160, 3), IR(29778, 23), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpInBoundsPtrAccessChain, true, true, IR(151, 5), IR(29801, 23), IR(0, 0), IR(1, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpDecorate, false, false, IR(163, 2), IR(29852, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpMemberDecorate, false, false, IR(165, 3), IR(29861, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpDecorationGroup, true, false, IR(68, 1), IR(29876, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupDecorate, false, false, IR(168, 2), IR(29892, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupMemberDecorate, false, false, IR(170, 2), IR(29951, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpVectorExtractDynamic, true, true, IR(172, 4), IR(29971, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpVectorInsertDynamic, true, true, IR(130, 5), IR(29992, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpVectorShuffle, true, true, IR(176, 5), IR(30012, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeConstruct, true, true, IR(107, 3), IR(30026, 19), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeExtract, true, true, IR(181, 4), IR(30045, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeInsert, true, true, IR(176, 5), IR(30062, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCopyObject, true, true, IR(160, 3), IR(30078, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpTranspose, true, true, IR(160, 3), IR(30089, 10), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpSampledImage, true, true, IR(172, 4), IR(30099, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleImplicitLod, true, true, IR(185, 5), IR(30144, 23), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleExplicitLod, true, true, IR(190, 5), IR(30190, 23), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleDrefImplicitLod, true, true, IR(195, 6), IR(30213, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleDrefExplicitLod, true, true, IR(201, 6), IR(30240, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjImplicitLod, true, true, IR(185, 5), IR(30267, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjExplicitLod, true, true, IR(190, 5), IR(30294, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjDrefImplicitLod, true, true, IR(195, 6), IR(30321, 31), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjDrefExplicitLod, true, true, IR(201, 6), IR(30352, 31), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageFetch, true, true, IR(185, 5), IR(30383, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageGather, true, true, IR(195, 6), IR(30394, 12), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageDrefGather, true, true, IR(195, 6), IR(30406, 16), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageRead, true, true, IR(185, 5), IR(30422, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageWrite, false, false, IR(207, 4), IR(30432, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImage, true, true, IR(160, 3), IR(27589, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryFormat, true, true, IR(160, 3), IR(30443, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryOrder, true, true, IR(160, 3), IR(30460, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySizeLod, true, true, IR(172, 4), IR(30476, 18), IR(0, 0), IR(219, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySize, true, true, IR(160, 3), IR(30494, 15), IR(0, 0), IR(219, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryLod, true, true, IR(172, 4), IR(30509, 14), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryLevels, true, true, IR(160, 3), IR(30523, 17), IR(0, 0), IR(219, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySamples, true, true, IR(160, 3), IR(30540, 18), IR(0, 0), IR(219, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertFToU, true, true, IR(160, 3), IR(30558, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertFToS, true, true, IR(160, 3), IR(30570, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertSToF, true, true, IR(160, 3), IR(30582, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToF, true, true, IR(160, 3), IR(30594, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpUConvert, true, true, IR(160, 3), IR(30606, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSConvert, true, true, IR(160, 3), IR(30615, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpFConvert, true, true, IR(160, 3), IR(30624, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpQuantizeToF16, true, true, IR(160, 3), IR(30633, 14), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertPtrToU, true, true, IR(160, 3), IR(30647, 14), IR(0, 0), IR(210, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSatConvertSToU, true, true, IR(160, 3), IR(30661, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSatConvertUToS, true, true, IR(160, 3), IR(30676, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToPtr, true, true, IR(160, 3), IR(30691, 14), IR(0, 0), IR(210, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpPtrCastToGeneric, true, true, IR(160, 3), IR(30705, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpGenericCastToPtr, true, true, IR(160, 3), IR(30722, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpGenericCastToPtrExplicit, true, true, IR(211, 4), IR(30739, 25), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpBitcast, true, true, IR(160, 3), IR(30764, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSNegate, true, true, IR(160, 3), IR(30772, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFNegate, true, true, IR(160, 3), IR(30780, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIAdd, true, true, IR(172, 4), IR(30788, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFAdd, true, true, IR(172, 4), IR(30793, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpISub, true, true, IR(172, 4), IR(30798, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFSub, true, true, IR(172, 4), IR(30803, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIMul, true, true, IR(172, 4), IR(30808, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFMul, true, true, IR(172, 4), IR(30813, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDiv, true, true, IR(172, 4), IR(30818, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSDiv, true, true, IR(172, 4), IR(30823, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFDiv, true, true, IR(172, 4), IR(30828, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUMod, true, true, IR(172, 4), IR(30833, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSRem, true, true, IR(172, 4), IR(30838, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSMod, true, true, IR(172, 4), IR(30843, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFRem, true, true, IR(172, 4), IR(30848, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFMod, true, true, IR(172, 4), IR(30853, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpVectorTimesScalar, true, true, IR(172, 4), IR(30858, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesScalar, true, true, IR(172, 4), IR(30876, 18), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpVectorTimesMatrix, true, true, IR(172, 4), IR(30894, 18), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesVector, true, true, IR(172, 4), IR(30912, 18), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesMatrix, true, true, IR(172, 4), IR(30930, 18), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpOuterProduct, true, true, IR(172, 4), IR(30948, 13), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpDot, true, true, IR(172, 4), IR(30961, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIAddCarry, true, true, IR(172, 4), IR(30965, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpISubBorrow, true, true, IR(172, 4), IR(30975, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUMulExtended, true, true, IR(172, 4), IR(30986, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSMulExtended, true, true, IR(172, 4), IR(30999, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpAny, true, true, IR(160, 3), IR(31012, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpAll, true, true, IR(160, 3), IR(31016, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsNan, true, true, IR(160, 3), IR(31020, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsInf, true, true, IR(160, 3), IR(31026, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsFinite, true, true, IR(160, 3), IR(31032, 9), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsNormal, true, true, IR(160, 3), IR(31041, 9), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSignBitSet, true, true, IR(160, 3), IR(31050, 11), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLessOrGreater, true, true, IR(172, 4), IR(31061, 14), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), SPV_SPIRV_VERSION_WORD(1,5), PrintingClass::kRelational_and_Logical},
  {spv::Op::OpOrdered, true, true, IR(172, 4), IR(31075, 8), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUnordered, true, true, IR(172, 4), IR(31083, 10), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalEqual, true, true, IR(172, 4), IR(31093, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalNotEqual, true, true, IR(172, 4), IR(31106, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalOr, true, true, IR(172, 4), IR(31122, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalAnd, true, true, IR(172, 4), IR(31132, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalNot, true, true, IR(160, 3), IR(31143, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSelect, true, true, IR(130, 5), IR(31154, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIEqual, true, true, IR(172, 4), IR(31161, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpINotEqual, true, true, IR(172, 4), IR(31168, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUGreaterThan, true, true, IR(172, 4), IR(31178, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSGreaterThan, true, true, IR(172, 4), IR(31191, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUGreaterThanEqual, true, true, IR(172, 4), IR(31204, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSGreaterThanEqual, true, true, IR(172, 4), IR(31222, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpULessThan, true, true, IR(172, 4), IR(31240, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSLessThan, true, true, IR(172, 4), IR(31250, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpULessThanEqual, true, true, IR(172, 4), IR(31260, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSLessThanEqual, true, true, IR(172, 4), IR(31275, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdEqual, true, true, IR(172, 4), IR(31290, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordEqual, true, true, IR(172, 4), IR(31300, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdNotEqual, true, true, IR(172, 4), IR(31312, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordNotEqual, true, true, IR(172, 4), IR(31325, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdLessThan, true, true, IR(172, 4), IR(31340, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordLessThan, true, true, IR(172, 4), IR(31353, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdGreaterThan, true, true, IR(172, 4), IR(31368, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordGreaterThan, true, true, IR(172, 4), IR(31384, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdLessThanEqual, true, true, IR(172, 4), IR(31402, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordLessThanEqual, true, true, IR(172, 4), IR(31420, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdGreaterThanEqual, true, true, IR(172, 4), IR(31440, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordGreaterThanEqual, true, true, IR(172, 4), IR(31461, 23), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpShiftRightLogical, true, true, IR(172, 4), IR(31484, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpShiftRightArithmetic, true, true, IR(172, 4), IR(31502, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpShiftLeftLogical, true, true, IR(172, 4), IR(31523, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseOr, true, true, IR(172, 4), IR(31540, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseXor, true, true, IR(172, 4), IR(31550, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseAnd, true, true, IR(172, 4), IR(31561, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpNot, true, true, IR(160, 3), IR(31572, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldInsert, true, true, IR(215, 6), IR(31576, 15), IR(0, 0), IR(222, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldSExtract, true, true, IR(130, 5), IR(31591, 17), IR(0, 0), IR(222, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldUExtract, true, true, IR(130, 5), IR(31608, 17), IR(0, 0), IR(222, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitReverse, true, true, IR(160, 3), IR(31625, 11), IR(0, 0), IR(222, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitCount, true, true, IR(160, 3), IR(31636, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpDPdx, true, true, IR(160, 3), IR(31645, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdy, true, true, IR(160, 3), IR(31650, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidth, true, true, IR(160, 3), IR(31655, 7), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdxFine, true, true, IR(160, 3), IR(31662, 9), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdyFine, true, true, IR(160, 3), IR(31671, 9), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidthFine, true, true, IR(160, 3), IR(31680, 11), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdxCoarse, true, true, IR(160, 3), IR(31691, 11), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdyCoarse, true, true, IR(160, 3), IR(31702, 11), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidthCoarse, true, true, IR(160, 3), IR(31713, 13), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpEmitVertex, false, false, IR(0, 0), IR(31726, 11), IR(0, 0), IR(70, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEndPrimitive, false, false, IR(0, 0), IR(31737, 13), IR(0, 0), IR(70, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEmitStreamVertex, false, false, IR(10, 1), IR(31750, 17), IR(0, 0), IR(121, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEndStreamPrimitive, false, false, IR(10, 1), IR(31767, 19), IR(0, 0), IR(121, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpControlBarrier, false, false, IR(221, 3), IR(31823, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpMemoryBarrier, false, false, IR(224, 2), IR(31838, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpAtomicLoad, true, true, IR(226, 5), IR(31852, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicStore, false, false, IR(231, 4), IR(31863, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicExchange, true, true, IR(235, 6), IR(31875, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicCompareExchange, true, true, IR(241, 8), IR(31890, 22), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicCompareExchangeWeak, true, true, IR(241, 8), IR(31912, 26), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), SPV_SPIRV_VERSION_WORD(1,3), PrintingClass::kAtomic},
  {spv::Op::OpAtomicIIncrement, true, true, IR(226, 5), IR(31938, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicIDecrement, true, true, IR(226, 5), IR(31955, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicIAdd, true, true, IR(235, 6), IR(31972, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicISub, true, true, IR(235, 6), IR(31983, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicSMin, true, true, IR(235, 6), IR(31994, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicUMin, true, true, IR(235, 6), IR(32005, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicSMax, true, true, IR(235, 6), IR(32016, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicUMax, true, true, IR(235, 6), IR(32027, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicAnd, true, true, IR(235, 6), IR(32038, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicOr, true, true, IR(235, 6), IR(32048, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicXor, true, true, IR(235, 6), IR(32057, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpPhi, true, true, IR(107, 3), IR(32067, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLoopMerge, false, false, IR(249, 3), IR(32101, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpSelectionMerge, false, false, IR(252, 2), IR(32146, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLabel, true, false, IR(68, 1), IR(32161, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpBranch, false, false, IR(10, 1), IR(32167, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpBranchConditional, false, false, IR(254, 4), IR(32174, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpSwitch, false, false, IR(258, 3), IR(32237, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpKill, false, false, IR(0, 0), IR(32244, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpReturn, false, false, IR(0, 0), IR(32249, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpReturnValue, false, false, IR(10, 1), IR(32256, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpUnreachable, false, false, IR(0, 0), IR(32268, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLifetimeStart, false, false, IR(261, 2), IR(32280, 14), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLifetimeStop, false, false, IR(261, 2), IR(32294, 13), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpGroupAsyncCopy, true, true, IR(263, 8), IR(32307, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupWaitEvents, false, false, IR(271, 3), IR(32322, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupAll, true, true, IR(274, 4), IR(32338, 9), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupAny, true, true, IR(274, 4), IR(32347, 9), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBroadcast, true, true, IR(278, 5), IR(32356, 15), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupIAdd, true, true, IR(283, 5), IR(32404, 10), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFAdd, true, true, IR(283, 5), IR(32414, 10), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMin, true, true, IR(283, 5), IR(32424, 10), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMin, true, true, IR(283, 5), IR(32434, 10), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMin, true, true, IR(283, 5), IR(32444, 10), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMax, true, true, IR(283, 5), IR(32454, 10), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMax, true, true, IR(283, 5), IR(32464, 10), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMax, true, true, IR(283, 5), IR(32474, 10), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpReadPipe, true, true, IR(215, 6), IR(32484, 9), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpWritePipe, true, true, IR(215, 6), IR(32493, 10), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReservedReadPipe, true, true, IR(288, 8), IR(32503, 17), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReservedWritePipe, true, true, IR(288, 8), IR(32520, 18), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReserveReadPipePackets, true, true, IR(215, 6), IR(32538, 23), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReserveWritePipePackets, true, true, IR(215, 6), IR(32561, 24), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCommitReadPipe, false, false, IR(296, 4), IR(32585, 15), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCommitWritePipe, false, false, IR(296, 4), IR(32600, 16), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpIsValidReserveId, true, true, IR(160, 3), IR(32616, 17), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetNumPipePackets, true, true, IR(130, 5), IR(32633, 18), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetMaxPipePackets, true, true, IR(130, 5), IR(32651, 18), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupReserveReadPipePackets, true, true, IR(300, 7), IR(32669, 28), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupReserveWritePipePackets, true, true, IR(300, 7), IR(32697, 29), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupCommitReadPipe, false, false, IR(307, 5), IR(32726, 20), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupCommitWritePipe, false, false, IR(307, 5), IR(32746, 21), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpEnqueueMarker, true, true, IR(215, 6), IR(32767, 14), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpEnqueueKernel, true, true, IR(312, 13), IR(32781, 14), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelNDrangeSubGroupCount, true, true, IR(325, 7), IR(32795, 30), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelNDrangeMaxSubGroupSize, true, true, IR(325, 7), IR(32825, 32), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelWorkGroupSize, true, true, IR(215, 6), IR(32857, 23), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelPreferredWorkGroupSizeMultiple, true, true, IR(215, 6), IR(32880, 40), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpRetainEvent, false, false, IR(10, 1), IR(32920, 12), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpReleaseEvent, false, false, IR(10, 1), IR(32932, 13), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpCreateUserEvent, true, true, IR(39, 2), IR(32945, 16), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpIsValidEvent, true, true, IR(160, 3), IR(32961, 13), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpSetUserEventStatus, false, false, IR(36, 2), IR(32974, 19), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpCaptureEventProfilingInfo, false, false, IR(33, 3), IR(32993, 26), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetDefaultQueue, true, true, IR(39, 2), IR(33019, 16), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpBuildNDRange, true, true, IR(130, 5), IR(33035, 13), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpImageSparseSampleImplicitLod, true, true, IR(185, 5), IR(33048, 29), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleExplicitLod, true, true, IR(190, 5), IR(33077, 29), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleDrefImplicitLod, true, true, IR(195, 6), IR(33106, 33), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleDrefExplicitLod, true, true, IR(201, 6), IR(33139, 33), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjImplicitLod, true, true, IR(185, 5), IR(33172, 33), IR(0, 0), IR(226, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjExplicitLod, true, true, IR(190, 5), IR(33205, 33), IR(0, 0), IR(226, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjDrefImplicitLod, true, true, IR(195, 6), IR(33238, 37), IR(0, 0), IR(226, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjDrefExplicitLod, true, true, IR(201, 6), IR(33275, 37), IR(0, 0), IR(226, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseFetch, true, true, IR(185, 5), IR(33312, 17), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseGather, true, true, IR(195, 6), IR(33329, 18), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseDrefGather, true, true, IR(195, 6), IR(33347, 22), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseTexelsResident, true, true, IR(160, 3), IR(33369, 26), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpNoLine, false, false, IR(0, 0), IR(33395, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpAtomicFlagTestAndSet, true, true, IR(226, 5), IR(33402, 21), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicFlagClear, false, false, IR(332, 3), IR(33423, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpImageSparseRead, true, true, IR(185, 5), IR(33439, 16), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpSizeOf, true, true, IR(160, 3), IR(33455, 7), IR(0, 0), IR(1, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpTypePipeStorage, true, false, IR(68, 1), IR(33462, 16), IR(0, 0), IR(227, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantPipeStorage, true, true, IR(335, 5), IR(33478, 20), IR(0, 0), IR(227, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCreatePipeFromPipeStorage, true, true, IR(160, 3), IR(33498, 26), IR(0, 0), IR(227, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetKernelLocalSizeForSubgroupCount, true, true, IR(325, 7), IR(33524, 35), IR(0, 0), IR(161, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelMaxNumSubgroups, true, true, IR(215, 6), IR(33559, 25), IR(0, 0), IR(161, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpTypeNamedBarrier, true, false, IR(68, 1), IR(33584, 17), IR(0, 0), IR(228, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpNamedBarrierInitialize, true, true, IR(160, 3), IR(33601, 23), IR(0, 0), IR(228, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpMemoryNamedBarrier, false, false, IR(332, 3), IR(33624, 19), IR(0, 0), IR(228, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpModuleProcessed, false, false, IR(11, 1), IR(33643, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpExecutionModeId, false, false, IR(65, 2), IR(33659, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,2), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpDecorateId, false, false, IR(163, 2), IR(33675, 11), IR(0, 0), IR(1, 0), IR(185, 1), SPV_SPIRV_VERSION_WORD(1,2), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupNonUniformElect, true, true, IR(340, 3), IR(33686, 21), IR(0, 0), IR(77, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAll, true, true, IR(274, 4), IR(33707, 19), IR(0, 0), IR(229, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAny, true, true, IR(274, 4), IR(33726, 19), IR(0, 0), IR(229, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAllEqual, true, true, IR(274, 4), IR(33745, 24), IR(0, 0), IR(229, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBroadcast, true, true, IR(278, 5), IR(33769, 25), IR(0, 0), IR(230, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBroadcastFirst, true, true, IR(274, 4), IR(33794, 30), IR(0, 0), IR(230, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallot, true, true, IR(274, 4), IR(6517, 22), IR(0, 0), IR(230, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformInverseBallot, true, true, IR(274, 4), IR(33824, 29), IR(0, 0), IR(230, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotBitExtract, true, true, IR(278, 5), IR(33853, 32), IR(0, 0), IR(230, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotBitCount, true, true, IR(283, 5), IR(33885, 30), IR(0, 0), IR(230, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotFindLSB, true, true, IR(274, 4), IR(33915, 29), IR(0, 0), IR(230, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotFindMSB, true, true, IR(274, 4), IR(33944, 29), IR(0, 0), IR(230, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffle, true, true, IR(278, 5), IR(9656, 23), IR(0, 0), IR(231, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleXor, true, true, IR(278, 5), IR(33973, 26), IR(0, 0), IR(231, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleUp, true, true, IR(278, 5), IR(33999, 25), IR(0, 0), IR(232, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleDown, true, true, IR(278, 5), IR(34024, 27), IR(0, 0), IR(232, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformIAdd, true, true, IR(343, 6), IR(34051, 20), IR(0, 0), IR(233, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFAdd, true, true, IR(343, 6), IR(34071, 20), IR(0, 0), IR(233, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformIMul, true, true, IR(343, 6), IR(34091, 20), IR(0, 0), IR(233, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMul, true, true, IR(343, 6), IR(34111, 20), IR(0, 0), IR(233, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformSMin, true, true, IR(343, 6), IR(34131, 20), IR(0, 0), IR(233, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformUMin, true, true, IR(343, 6), IR(34151, 20), IR(0, 0), IR(233, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMin, true, true, IR(343, 6), IR(34171, 20), IR(0, 0), IR(233, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformSMax, true, true, IR(343, 6), IR(34191, 20), IR(0, 0), IR(233, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformUMax, true, true, IR(343, 6), IR(34211, 20), IR(0, 0), IR(233, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMax, true, true, IR(343, 6), IR(34231, 20), IR(0, 0), IR(233, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseAnd, true, true, IR(343, 6), IR(34251, 26), IR(0, 0), IR(233, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseOr, true, true, IR(343, 6), IR(34277, 25), IR(0, 0), IR(233, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseXor, true, true, IR(343, 6), IR(34302, 26), IR(0, 0), IR(233, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalAnd, true, true, IR(343, 6), IR(34328, 26), IR(0, 0), IR(233, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalOr, true, true, IR(343, 6), IR(34354, 25), IR(0, 0), IR(233, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalXor, true, true, IR(343, 6), IR(34379, 26), IR(0, 0), IR(233, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadBroadcast, true, true, IR(278, 5), IR(34405, 29), IR(0, 0), IR(236, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadSwap, true, true, IR(278, 5), IR(34434, 24), IR(0, 0), IR(236, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpCopyLogical, true, true, IR(160, 3), IR(34458, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpPtrEqual, true, true, IR(172, 4), IR(34470, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrNotEqual, true, true, IR(172, 4), IR(34479, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrDiff, true, true, IR(172, 4), IR(34491, 8), IR(0, 0), IR(237, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpColorAttachmentReadEXT, true, true, IR(349, 4), IR(34499, 23), IR(0, 0), IR(153, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpDepthAttachmentReadEXT, true, true, IR(353, 3), IR(34522, 23), IR(0, 0), IR(162, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpStencilAttachmentReadEXT, true, true, IR(353, 3), IR(34545, 25), IR(0, 0), IR(163, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpTypeTensorARM, true, false, IR(356, 4), IR(34570, 14), IR(0, 0), IR(209, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTensorReadARM, true, true, IR(360, 5), IR(34626, 14), IR(0, 0), IR(209, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpTensorWriteARM, false, false, IR(365, 4), IR(34640, 15), IR(0, 0), IR(209, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpTensorQuerySizeARM, true, true, IR(172, 4), IR(34655, 19), IR(0, 0), IR(209, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpGraphConstantARM, true, true, IR(369, 3), IR(34674, 17), IR(0, 0), IR(240, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphEntryPointARM, false, false, IR(372, 3), IR(34691, 19), IR(0, 0), IR(240, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphARM, true, true, IR(39, 2), IR(9947, 9), IR(0, 0), IR(240, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphInputARM, true, true, IR(122, 4), IR(34710, 14), IR(0, 0), IR(240, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphSetOutputARM, false, false, IR(375, 3), IR(34724, 18), IR(0, 0), IR(240, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphEndARM, false, false, IR(0, 0), IR(34742, 12), IR(0, 0), IR(240, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpTypeGraphARM, true, false, IR(378, 3), IR(34754, 13), IR(0, 0), IR(240, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTerminateInvocation, false, false, IR(0, 0), IR(34767, 20), IR(0, 0), IR(3, 1), IR(195, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpTypeUntypedPointerKHR, true, false, IR(381, 2), IR(34787, 22), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpUntypedVariableKHR, true, true, IR(383, 5), IR(34809, 19), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedAccessChainKHR, true, true, IR(151, 5), IR(34828, 22), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedInBoundsAccessChainKHR, true, true, IR(151, 5), IR(34850, 30), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpSubgroupBallotKHR, true, true, IR(160, 3), IR(6278, 18), IR(0, 0), IR(241, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupFirstInvocationKHR, true, true, IR(160, 3), IR(34880, 27), IR(0, 0), IR(241, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpUntypedPtrAccessChainKHR, true, true, IR(388, 6), IR(34907, 25), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedInBoundsPtrAccessChainKHR, true, true, IR(388, 6), IR(34932, 33), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedArrayLengthKHR, true, true, IR(394, 5), IR(34965, 22), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedPrefetchKHR, false, false, IR(399, 5), IR(34987, 19), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpFmaKHR, true, true, IR(130, 5), IR(35006, 7), IR(0, 0), IR(242, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSubgroupAllKHR, true, true, IR(160, 3), IR(35013, 15), IR(0, 0), IR(243, 1), IR(41, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupAnyKHR, true, true, IR(160, 3), IR(35028, 15), IR(0, 0), IR(243, 1), IR(41, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupAllEqualKHR, true, true, IR(160, 3), IR(35043, 20), IR(0, 0), IR(243, 1), IR(41, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupNonUniformRotateKHR, true, true, IR(404, 6), IR(14693, 25), IR(0, 0), IR(244, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupReadInvocationKHR, true, true, IR(172, 4), IR(35063, 26), IR(0, 0), IR(241, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpExtInstWithForwardRefsKHR, true, true, IR(410, 5), IR(35089, 26), IR(0, 0), IR(1, 0), IR(196, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpUntypedGroupAsyncCopyKHR, true, true, IR(415, 11), IR(35115, 25), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpTraceRayKHR, false, false, IR(426, 11), IR(35140, 12), IR(0, 0), IR(61, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpExecuteCallableKHR, false, false, IR(36, 2), IR(35152, 19), IR(0, 0), IR(61, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToAccelerationStructureKHR, true, true, IR(160, 3), IR(35171, 35), IR(0, 0), IR(245, 2), IR(197, 2), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIgnoreIntersectionKHR, false, false, IR(0, 0), IR(35206, 22), IR(0, 0), IR(61, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTerminateRayKHR, false, false, IR(0, 0), IR(35228, 16), IR(0, 0), IR(61, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSDot, true, true, IR(437, 5), IR(35291, 5), IR(171, 1), IR(247, 1), IR(144, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDot, true, true, IR(437, 5), IR(35304, 5), IR(172, 1), IR(247, 1), IR(144, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSUDot, true, true, IR(437, 5), IR(35317, 6), IR(173, 1), IR(247, 1), IR(144, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSDotAccSat, true, true, IR(442, 6), IR(35332, 11), IR(174, 1), IR(247, 1), IR(144, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDotAccSat, true, true, IR(442, 6), IR(35357, 11), IR(175, 1), IR(247, 1), IR(144, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSUDotAccSat, true, true, IR(442, 6), IR(35382, 12), IR(176, 1), IR(247, 1), IR(144, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpTypeCooperativeMatrixKHR, true, false, IR(448, 6), IR(35409, 25), IR(0, 0), IR(87, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeMatrixLoadKHR, true, true, IR(454, 6), IR(35434, 25), IR(0, 0), IR(87, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixStoreKHR, false, false, IR(460, 5), IR(35459, 26), IR(0, 0), IR(87, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixMulAddKHR, true, true, IR(465, 6), IR(35539, 27), IR(0, 0), IR(87, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpCooperativeMatrixLengthKHR, true, true, IR(160, 3), IR(35566, 27), IR(0, 0), IR(87, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpConstantCompositeReplicateEXT, true, true, IR(160, 3), IR(35593, 30), IR(0, 0), IR(248, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCompositeReplicateEXT, true, true, IR(160, 3), IR(35623, 34), IR(0, 0), IR(248, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpCompositeConstructReplicateEXT, true, true, IR(160, 3), IR(35657, 31), IR(0, 0), IR(248, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpTypeRayQueryKHR, true, false, IR(68, 1), IR(35688, 16), IR(0, 0), IR(199, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpRayQueryInitializeKHR, false, false, IR(471, 8), IR(35704, 22), IR(0, 0), IR(199, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryTerminateKHR, false, false, IR(10, 1), IR(35726, 21), IR(0, 0), IR(199, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGenerateIntersectionKHR, false, false, IR(36, 2), IR(35747, 32), IR(0, 0), IR(199, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryConfirmIntersectionKHR, false, false, IR(10, 1), IR(35779, 31), IR(0, 0), IR(199, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryProceedKHR, true, true, IR(160, 3), IR(35810, 19), IR(0, 0), IR(199, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTypeKHR, true, true, IR(172, 4), IR(35829, 31), IR(0, 0), IR(199, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpImageSampleWeightedQCOM, true, true, IR(130, 5), IR(35860, 24), IR(0, 0), IR(249, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBoxFilterQCOM, true, true, IR(130, 5), IR(35884, 19), IR(0, 0), IR(250, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchSSDQCOM, true, true, IR(325, 7), IR(35903, 23), IR(0, 0), IR(251, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchSADQCOM, true, true, IR(325, 7), IR(35926, 23), IR(0, 0), IR(251, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpBitCastArrayQCOM, true, true, IR(160, 3), IR(35949, 17), IR(0, 0), IR(252, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpImageBlockMatchWindowSSDQCOM, true, true, IR(325, 7), IR(35966, 29), IR(0, 0), IR(253, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchWindowSADQCOM, true, true, IR(325, 7), IR(35995, 29), IR(0, 0), IR(253, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchGatherSSDQCOM, true, true, IR(325, 7), IR(36024, 29), IR(0, 0), IR(253, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchGatherSADQCOM, true, true, IR(325, 7), IR(36053, 29), IR(0, 0), IR(253, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpCompositeConstructCoopMatQCOM, true, true, IR(160, 3), IR(36082, 30), IR(0, 0), IR(252, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeExtractCoopMatQCOM, true, true, IR(160, 3), IR(36112, 28), IR(0, 0), IR(252, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpExtractSubArrayQCOM, true, true, IR(172, 4), IR(36140, 20), IR(0, 0), IR(252, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpGroupIAddNonUniformAMD, true, true, IR(283, 5), IR(36160, 23), IR(0, 0), IR(225, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFAddNonUniformAMD, true, true, IR(283, 5), IR(36183, 23), IR(0, 0), IR(225, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMinNonUniformAMD, true, true, IR(283, 5), IR(36206, 23), IR(0, 0), IR(225, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMinNonUniformAMD, true, true, IR(283, 5), IR(36229, 23), IR(0, 0), IR(225, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMinNonUniformAMD, true, true, IR(283, 5), IR(36252, 23), IR(0, 0), IR(225, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMaxNonUniformAMD, true, true, IR(283, 5), IR(36275, 23), IR(0, 0), IR(225, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMaxNonUniformAMD, true, true, IR(283, 5), IR(36298, 23), IR(0, 0), IR(225, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMaxNonUniformAMD, true, true, IR(283, 5), IR(36321, 23), IR(0, 0), IR(225, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpFragmentMaskFetchAMD, true, true, IR(172, 4), IR(36344, 21), IR(0, 0), IR(254, 1), IR(58, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFragmentFetchAMD, true, true, IR(130, 5), IR(36365, 17), IR(0, 0), IR(254, 1), IR(58, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReadClockKHR, true, true, IR(340, 3), IR(36382, 13), IR(0, 0), IR(255, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAllocateNodePayloadsAMDX, true, true, IR(278, 5), IR(36395, 25), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpEnqueueNodePayloadsAMDX, false, false, IR(10, 1), IR(36420, 24), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeNodePayloadArrayAMDX, true, false, IR(87, 2), IR(36444, 25), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFinishWritingNodePayloadAMDX, true, true, IR(160, 3), IR(36469, 29), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpNodePayloadArrayLengthAMDX, true, true, IR(160, 3), IR(36498, 27), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIsNodePayloadValidAMDX, true, true, IR(172, 4), IR(36525, 23), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConstantStringAMDX, true, false, IR(50, 2), IR(36548, 19), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSpecConstantStringAMDX, true, false, IR(50, 2), IR(36567, 23), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpGroupNonUniformQuadAllKHR, true, true, IR(160, 3), IR(36590, 26), IR(0, 0), IR(170, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadAnyKHR, true, true, IR(160, 3), IR(36616, 26), IR(0, 0), IR(170, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpTypeBufferEXT, true, false, IR(381, 2), IR(36642, 14), IR(0, 0), IR(44, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpBufferPointerEXT, true, true, IR(160, 3), IR(36656, 17), IR(0, 0), IR(44, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedImageTexelPointerEXT, true, true, IR(215, 6), IR(36673, 28), IR(0, 0), IR(44, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpMemberDecorateIdEXT, false, false, IR(165, 3), IR(36701, 20), IR(0, 0), IR(44, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpConstantSizeOfEXT, true, true, IR(160, 3), IR(36721, 18), IR(0, 0), IR(44, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpHitObjectRecordHitMotionNV, false, false, IR(479, 14), IR(36739, 27), IR(0, 0), IR(256, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitWithIndexMotionNV, false, false, IR(493, 13), IR(36766, 36), IR(0, 0), IR(256, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissMotionNV, false, false, IR(506, 7), IR(36802, 28), IR(0, 0), IR(256, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldToObjectNV, true, true, IR(160, 3), IR(36830, 28), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectToWorldNV, true, true, IR(160, 3), IR(36858, 28), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayDirectionNV, true, true, IR(160, 3), IR(36886, 33), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayOriginNV, true, true, IR(160, 3), IR(36919, 30), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayMotionNV, false, false, IR(493, 13), IR(36949, 26), IR(0, 0), IR(256, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderRecordBufferHandleNV, true, true, IR(160, 3), IR(36975, 39), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderBindingTableRecordIndexNV, true, true, IR(160, 3), IR(37014, 44), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordEmptyNV, false, false, IR(10, 1), IR(37058, 23), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayNV, false, false, IR(513, 12), IR(37081, 20), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitNV, false, false, IR(493, 13), IR(37101, 21), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitWithIndexNV, false, false, IR(513, 12), IR(37122, 30), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissNV, false, false, IR(525, 6), IR(37152, 22), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectExecuteShaderNV, false, false, IR(36, 2), IR(37174, 25), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetCurrentTimeNV, true, true, IR(160, 3), IR(37199, 26), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetAttributesNV, false, false, IR(36, 2), IR(37225, 25), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetHitKindNV, true, true, IR(160, 3), IR(37250, 22), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetPrimitiveIndexNV, true, true, IR(160, 3), IR(37272, 29), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetGeometryIndexNV, true, true, IR(160, 3), IR(37301, 28), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceIdNV, true, true, IR(160, 3), IR(37329, 25), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceCustomIndexNV, true, true, IR(160, 3), IR(37354, 34), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayDirectionNV, true, true, IR(160, 3), IR(37388, 32), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayOriginNV, true, true, IR(160, 3), IR(37420, 29), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMaxNV, true, true, IR(160, 3), IR(37449, 22), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMinNV, true, true, IR(160, 3), IR(37471, 22), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsEmptyNV, true, true, IR(160, 3), IR(37493, 19), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsHitNV, true, true, IR(160, 3), IR(37512, 17), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsMissNV, true, true, IR(160, 3), IR(37529, 18), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHitObjectNV, false, false, IR(531, 3), IR(37547, 29), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHintNV, false, false, IR(36, 2), IR(37576, 24), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeHitObjectNV, true, false, IR(68, 1), IR(37600, 16), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpImageSampleFootprintNV, true, true, IR(534, 7), IR(37616, 23), IR(0, 0), IR(258, 1), IR(73, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpTypeVectorIdEXT, true, false, IR(89, 3), IR(37639, 16), IR(177, 1), IR(259, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeVectorMatrixMulNV, true, true, IR(541, 13), IR(37679, 29), IR(0, 0), IR(261, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorOuterProductAccumulateNV, false, false, IR(554, 7), IR(37708, 42), IR(0, 0), IR(262, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorReduceSumAccumulateNV, false, false, IR(33, 3), IR(37750, 39), IR(0, 0), IR(262, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorMatrixMulAddNV, true, true, IR(561, 16), IR(37789, 32), IR(0, 0), IR(261, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixConvertNV, true, true, IR(160, 3), IR(37821, 27), IR(0, 0), IR(263, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpEmitMeshTasksEXT, false, false, IR(577, 4), IR(37848, 17), IR(0, 0), IR(54, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSetMeshOutputsEXT, false, false, IR(36, 2), IR(37865, 18), IR(0, 0), IR(54, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpGroupNonUniformPartitionEXT, true, true, IR(160, 3), IR(37883, 28), IR(178, 1), IR(190, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpWritePackedPrimitiveIndices4x8NV, false, false, IR(36, 2), IR(37938, 33), IR(0, 0), IR(51, 1), IR(18, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFetchMicroTriangleVertexPositionNV, true, true, IR(325, 7), IR(37971, 35), IR(0, 0), IR(264, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFetchMicroTriangleVertexBarycentricNV, true, true, IR(325, 7), IR(38006, 38), IR(0, 0), IR(264, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorLoadNV, true, true, IR(581, 5), IR(38044, 24), IR(0, 0), IR(261, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeVectorStoreNV, false, false, IR(586, 4), IR(38068, 25), IR(0, 0), IR(261, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpHitObjectRecordFromQueryEXT, false, false, IR(296, 4), IR(38093, 28), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissEXT, false, false, IR(506, 7), IR(38121, 23), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissMotionEXT, false, false, IR(471, 8), IR(38144, 29), IR(0, 0), IR(265, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetIntersectionTriangleVertexPositionsEXT, true, true, IR(160, 3), IR(38173, 51), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayFlagsEXT, true, true, IR(160, 3), IR(38224, 24), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectSetShaderBindingTableRecordIndexEXT, false, false, IR(36, 2), IR(38248, 45), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectReorderExecuteShaderEXT, false, false, IR(590, 4), IR(38293, 33), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceReorderExecuteEXT, false, false, IR(594, 14), IR(38326, 32), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceMotionReorderExecuteEXT, false, false, IR(608, 15), IR(38358, 38), IR(0, 0), IR(265, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeHitObjectEXT, true, false, IR(68, 1), IR(38396, 17), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpReorderThreadWithHintEXT, false, false, IR(36, 2), IR(38413, 25), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHitObjectEXT, false, false, IR(531, 3), IR(38438, 30), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayEXT, false, false, IR(513, 12), IR(38468, 21), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayMotionEXT, false, false, IR(493, 13), IR(38489, 27), IR(0, 0), IR(265, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordEmptyEXT, false, false, IR(10, 1), IR(38516, 24), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectExecuteShaderEXT, false, false, IR(36, 2), IR(38540, 26), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetCurrentTimeEXT, true, true, IR(160, 3), IR(38566, 27), IR(0, 0), IR(265, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetAttributesEXT, false, false, IR(36, 2), IR(38593, 26), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetHitKindEXT, true, true, IR(160, 3), IR(38619, 23), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetPrimitiveIndexEXT, true, true, IR(160, 3), IR(38642, 30), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetGeometryIndexEXT, true, true, IR(160, 3), IR(38672, 29), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceIdEXT, true, true, IR(160, 3), IR(38701, 26), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceCustomIndexEXT, true, true, IR(160, 3), IR(38727, 35), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayOriginEXT, true, true, IR(160, 3), IR(38762, 31), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayDirectionEXT, true, true, IR(160, 3), IR(38793, 34), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayDirectionEXT, true, true, IR(160, 3), IR(38827, 33), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayOriginEXT, true, true, IR(160, 3), IR(38860, 30), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectToWorldEXT, true, true, IR(160, 3), IR(38890, 29), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldToObjectEXT, true, true, IR(160, 3), IR(38919, 29), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMaxEXT, true, true, IR(160, 3), IR(38948, 23), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReportIntersectionKHR, true, true, IR(172, 4), IR(38971, 22), IR(179, 1), IR(55, 2), IR(24, 2), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIgnoreIntersectionNV, false, false, IR(0, 0), IR(39014, 21), IR(0, 0), IR(57, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTerminateRayNV, false, false, IR(0, 0), IR(39035, 15), IR(0, 0), IR(57, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceNV, false, false, IR(426, 11), IR(39050, 8), IR(0, 0), IR(57, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceMotionNV, false, false, IR(513, 12), IR(39058, 14), IR(0, 0), IR(58, 1), IR(27, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceRayMotionNV, false, false, IR(513, 12), IR(39072, 17), IR(0, 0), IR(58, 1), IR(27, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTriangleVertexPositionsKHR, true, true, IR(172, 4), IR(39089, 50), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeAccelerationStructureKHR, true, false, IR(68, 1), IR(39139, 29), IR(180, 1), IR(268, 4), IR(199, 4), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpExecuteCallableNV, false, false, IR(36, 2), IR(39196, 18), IR(0, 0), IR(57, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionClusterIdNV, true, true, IR(172, 4), IR(39214, 35), IR(181, 1), IR(65, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetClusterIdNV, true, true, IR(160, 3), IR(39272, 24), IR(0, 0), IR(65, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMinEXT, true, true, IR(160, 3), IR(39296, 23), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderBindingTableRecordIndexEXT, true, true, IR(160, 3), IR(39319, 45), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderRecordBufferHandleEXT, true, true, IR(160, 3), IR(39364, 40), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsEmptyEXT, true, true, IR(160, 3), IR(39404, 20), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsHitEXT, true, true, IR(160, 3), IR(39424, 18), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsMissEXT, true, true, IR(160, 3), IR(39442, 19), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeCooperativeMatrixNV, true, false, IR(623, 5), IR(39461, 24), IR(0, 0), IR(272, 1), IR(81, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeMatrixLoadNV, true, true, IR(628, 6), IR(39485, 24), IR(0, 0), IR(272, 1), IR(81, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixStoreNV, false, false, IR(634, 5), IR(39509, 25), IR(0, 0), IR(272, 1), IR(81, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixMulAddNV, true, true, IR(130, 5), IR(39534, 26), IR(0, 0), IR(272, 1), IR(81, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixLengthNV, true, true, IR(160, 3), IR(39560, 26), IR(0, 0), IR(272, 1), IR(81, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpBeginInvocationInterlockEXT, false, false, IR(0, 0), IR(39586, 28), IR(0, 0), IR(273, 3), IR(82, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpEndInvocationInterlockEXT, false, false, IR(0, 0), IR(39614, 26), IR(0, 0), IR(273, 3), IR(82, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixReduceNV, true, true, IR(639, 5), IR(39683, 26), IR(0, 0), IR(276, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpCooperativeMatrixLoadTensorNV, true, true, IR(644, 7), IR(39784, 30), IR(0, 0), IR(207, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixStoreTensorNV, false, false, IR(651, 5), IR(39814, 31), IR(0, 0), IR(207, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixPerElementOpNV, true, true, IR(151, 5), IR(39845, 32), IR(0, 0), IR(277, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpTypeTensorLayoutNV, true, false, IR(89, 3), IR(39877, 19), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeTensorViewNV, true, false, IR(656, 4), IR(39896, 17), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCreateTensorLayoutNV, true, true, IR(39, 2), IR(39913, 21), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetDimensionNV, true, true, IR(122, 4), IR(39934, 27), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetStrideNV, true, true, IR(122, 4), IR(39961, 24), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSliceNV, true, true, IR(122, 4), IR(39985, 20), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetClampValueNV, true, true, IR(172, 4), IR(40005, 28), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCreateTensorViewNV, true, true, IR(39, 2), IR(40033, 19), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetDimensionNV, true, true, IR(122, 4), IR(40052, 25), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetStrideNV, true, true, IR(122, 4), IR(40077, 22), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpDemoteToHelperInvocation, false, false, IR(0, 0), IR(12508, 25), IR(46, 1), IR(279, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpIsHelperInvocationEXT, true, true, IR(39, 2), IR(40099, 22), IR(0, 0), IR(279, 1), IR(83, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetClipNV, true, true, IR(325, 7), IR(40121, 20), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetBlockSizeNV, true, true, IR(122, 4), IR(40141, 27), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixTransposeNV, true, true, IR(160, 3), IR(40168, 29), IR(0, 0), IR(263, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToImageNV, true, true, IR(160, 3), IR(40197, 18), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToSamplerNV, true, true, IR(160, 3), IR(40215, 20), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertImageToUNV, true, true, IR(160, 3), IR(40235, 18), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertSamplerToUNV, true, true, IR(160, 3), IR(40253, 20), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToSampledImageNV, true, true, IR(160, 3), IR(40273, 25), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertSampledImageToUNV, true, true, IR(160, 3), IR(40298, 25), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSamplerImageAddressingModeNV, false, false, IR(0, 1), IR(40323, 29), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRawAccessChainNV, true, true, IR(660, 7), IR(40404, 17), IR(0, 0), IR(196, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpRayQueryGetIntersectionSpherePositionNV, true, true, IR(172, 4), IR(40421, 40), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionSphereRadiusNV, true, true, IR(172, 4), IR(40461, 38), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSPositionsNV, true, true, IR(172, 4), IR(40499, 38), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSRadiiNV, true, true, IR(172, 4), IR(40537, 34), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSHitValueNV, true, true, IR(172, 4), IR(40571, 37), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetSpherePositionNV, true, true, IR(160, 3), IR(40608, 29), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetSphereRadiusNV, true, true, IR(160, 3), IR(40637, 27), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetLSSPositionsNV, true, true, IR(160, 3), IR(40664, 27), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetLSSRadiiNV, true, true, IR(160, 3), IR(40691, 23), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsSphereHitNV, true, true, IR(160, 3), IR(40714, 23), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsLSSHitNV, true, true, IR(160, 3), IR(40737, 20), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryIsSphereHitNV, true, true, IR(172, 4), IR(40757, 22), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryIsLSSHitNV, true, true, IR(172, 4), IR(40779, 19), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSubgroupShuffleINTEL, true, true, IR(172, 4), IR(13040, 21), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleDownINTEL, true, true, IR(130, 5), IR(40798, 25), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleUpINTEL, true, true, IR(130, 5), IR(40823, 23), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleXorINTEL, true, true, IR(172, 4), IR(40846, 24), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupBlockReadINTEL, true, true, IR(160, 3), IR(40870, 23), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupBlockWriteINTEL, false, false, IR(36, 2), IR(40893, 24), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageBlockReadINTEL, true, true, IR(172, 4), IR(40917, 28), IR(0, 0), IR(282, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageBlockWriteINTEL, false, false, IR(33, 3), IR(40945, 29), IR(0, 0), IR(282, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageMediaBlockReadINTEL, true, true, IR(215, 6), IR(40974, 33), IR(0, 0), IR(283, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageMediaBlockWriteINTEL, false, false, IR(667, 5), IR(41007, 34), IR(0, 0), IR(283, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpUCountLeadingZerosINTEL, true, true, IR(160, 3), IR(41041, 24), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUCountTrailingZerosINTEL, true, true, IR(160, 3), IR(41065, 25), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAbsISubINTEL, true, true, IR(172, 4), IR(41090, 13), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAbsUSubINTEL, true, true, IR(172, 4), IR(41103, 13), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAddSatINTEL, true, true, IR(172, 4), IR(41116, 13), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAddSatINTEL, true, true, IR(172, 4), IR(41129, 13), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAverageINTEL, true, true, IR(172, 4), IR(41142, 14), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAverageINTEL, true, true, IR(172, 4), IR(41156, 14), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAverageRoundedINTEL, true, true, IR(172, 4), IR(41170, 21), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAverageRoundedINTEL, true, true, IR(172, 4), IR(41191, 21), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpISubSatINTEL, true, true, IR(172, 4), IR(41212, 13), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUSubSatINTEL, true, true, IR(172, 4), IR(41225, 13), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIMul32x16INTEL, true, true, IR(172, 4), IR(41238, 15), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUMul32x16INTEL, true, true, IR(172, 4), IR(41253, 15), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConstantFunctionPointerINTEL, true, true, IR(160, 3), IR(41268, 29), IR(0, 0), IR(205, 1), IR(101, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFunctionPointerCallINTEL, true, true, IR(107, 3), IR(41297, 25), IR(0, 0), IR(205, 1), IR(101, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmTargetINTEL, true, false, IR(50, 2), IR(41322, 15), IR(0, 0), IR(136, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmINTEL, true, true, IR(672, 6), IR(13258, 9), IR(0, 0), IR(136, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmCallINTEL, true, true, IR(122, 4), IR(41337, 13), IR(0, 0), IR(136, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAtomicFMinEXT, true, true, IR(235, 6), IR(41350, 14), IR(0, 0), IR(285, 4), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicFMaxEXT, true, true, IR(235, 6), IR(41364, 14), IR(0, 0), IR(285, 4), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAssumeTrueKHR, false, false, IR(10, 1), IR(41378, 14), IR(0, 0), IR(289, 1), IR(105, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpExpectKHR, true, true, IR(172, 4), IR(41392, 10), IR(0, 0), IR(289, 1), IR(105, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpDecorateString, false, false, IR(163, 2), IR(41402, 15), IR(182, 1), IR(1, 0), IR(203, 2), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpMemberDecorateString, false, false, IR(165, 3), IR(41438, 21), IR(183, 1), IR(1, 0), IR(203, 2), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpVmeImageINTEL, true, true, IR(172, 4), IR(41486, 14), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeVmeImageINTEL, true, false, IR(87, 2), IR(41500, 18), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImePayloadINTEL, true, false, IR(68, 1), IR(41518, 23), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcRefPayloadINTEL, true, false, IR(68, 1), IR(41541, 23), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcSicPayloadINTEL, true, false, IR(68, 1), IR(41564, 23), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcMcePayloadINTEL, true, false, IR(68, 1), IR(41587, 23), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcMceResultINTEL, true, false, IR(68, 1), IR(41610, 22), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultINTEL, true, false, IR(68, 1), IR(41632, 22), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultSingleReferenceStreamoutINTEL, true, false, IR(68, 1), IR(41654, 46), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultDualReferenceStreamoutINTEL, true, false, IR(68, 1), IR(41700, 44), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeSingleReferenceStreaminINTEL, true, false, IR(68, 1), IR(41744, 39), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeDualReferenceStreaminINTEL, true, false, IR(68, 1), IR(41783, 37), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcRefResultINTEL, true, false, IR(68, 1), IR(41820, 22), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcSicResultINTEL, true, false, IR(68, 1), IR(41842, 22), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL, true, true, IR(172, 4), IR(41864, 60), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL, true, true, IR(172, 4), IR(41924, 53), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterShapePenaltyINTEL, true, true, IR(172, 4), IR(41977, 47), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterShapePenaltyINTEL, true, true, IR(172, 4), IR(42024, 40), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL, true, true, IR(172, 4), IR(42064, 51), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterDirectionPenaltyINTEL, true, true, IR(172, 4), IR(42115, 44), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL, true, true, IR(172, 4), IR(42159, 51), IR(0, 0), IR(291, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL, true, true, IR(172, 4), IR(42210, 56), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL, true, true, IR(39, 2), IR(42266, 50), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL, true, true, IR(39, 2), IR(42316, 52), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL, true, true, IR(39, 2), IR(42368, 49), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetMotionVectorCostFunctionINTEL, true, true, IR(215, 6), IR(42417, 47), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL, true, true, IR(172, 4), IR(42464, 50), IR(0, 0), IR(291, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL, true, true, IR(39, 2), IR(42514, 51), IR(0, 0), IR(291, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL, true, true, IR(39, 2), IR(42565, 56), IR(0, 0), IR(293, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetAcOnlyHaarINTEL, true, true, IR(160, 3), IR(42621, 33), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL, true, true, IR(172, 4), IR(42654, 52), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL, true, true, IR(172, 4), IR(42706, 61), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL, true, true, IR(130, 5), IR(42767, 61), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToImePayloadINTEL, true, true, IR(160, 3), IR(42828, 39), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToImeResultINTEL, true, true, IR(160, 3), IR(42867, 38), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToRefPayloadINTEL, true, true, IR(160, 3), IR(42905, 39), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToRefResultINTEL, true, true, IR(160, 3), IR(42944, 38), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToSicPayloadINTEL, true, true, IR(160, 3), IR(42982, 39), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToSicResultINTEL, true, true, IR(160, 3), IR(43021, 38), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetMotionVectorsINTEL, true, true, IR(160, 3), IR(43059, 36), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterDistortionsINTEL, true, true, IR(160, 3), IR(43095, 39), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetBestInterDistortionsINTEL, true, true, IR(160, 3), IR(43134, 43), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMajorShapeINTEL, true, true, IR(160, 3), IR(43177, 38), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMinorShapeINTEL, true, true, IR(160, 3), IR(43215, 38), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterDirectionsINTEL, true, true, IR(160, 3), IR(43253, 38), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMotionVectorCountINTEL, true, true, IR(160, 3), IR(43291, 45), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterReferenceIdsINTEL, true, true, IR(160, 3), IR(43336, 40), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL, true, true, IR(130, 5), IR(43376, 62), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeInitializeINTEL, true, true, IR(130, 5), IR(43438, 30), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetSingleReferenceINTEL, true, true, IR(130, 5), IR(43468, 38), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetDualReferenceINTEL, true, true, IR(215, 6), IR(43506, 36), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeRefWindowSizeINTEL, true, true, IR(172, 4), IR(43542, 33), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeAdjustRefOffsetINTEL, true, true, IR(215, 6), IR(43575, 35), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(43610, 39), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetMaxMotionVectorCountINTEL, true, true, IR(172, 4), IR(43649, 43), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetUnidirectionalMixDisableINTEL, true, true, IR(160, 3), IR(43692, 47), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetEarlySearchTerminationThresholdINTEL, true, true, IR(172, 4), IR(43739, 54), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetWeightedSadINTEL, true, true, IR(172, 4), IR(43793, 34), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(43827, 47), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(43874, 45), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL, true, true, IR(215, 6), IR(43919, 55), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL, true, true, IR(325, 7), IR(43974, 53), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL, true, true, IR(130, 5), IR(44027, 56), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL, true, true, IR(215, 6), IR(44083, 54), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL, true, true, IR(215, 6), IR(44137, 58), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL, true, true, IR(325, 7), IR(44195, 56), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeConvertToMceResultINTEL, true, true, IR(160, 3), IR(44251, 38), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetSingleReferenceStreaminINTEL, true, true, IR(160, 3), IR(44289, 46), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetDualReferenceStreaminINTEL, true, true, IR(160, 3), IR(44335, 44), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeStripSingleReferenceStreamoutINTEL, true, true, IR(160, 3), IR(44379, 49), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeStripDualReferenceStreamoutINTEL, true, true, IR(160, 3), IR(44428, 47), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL, true, true, IR(172, 4), IR(44475, 70), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL, true, true, IR(172, 4), IR(44545, 68), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL, true, true, IR(172, 4), IR(44613, 69), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL, true, true, IR(130, 5), IR(44682, 68), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL, true, true, IR(130, 5), IR(44750, 66), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL, true, true, IR(130, 5), IR(44816, 67), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetBorderReachedINTEL, true, true, IR(172, 4), IR(44883, 36), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetTruncatedSearchIndicationINTEL, true, true, IR(160, 3), IR(44919, 48), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL, true, true, IR(160, 3), IR(44967, 59), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL, true, true, IR(160, 3), IR(45026, 58), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL, true, true, IR(160, 3), IR(45084, 56), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcFmeInitializeINTEL, true, true, IR(678, 9), IR(45140, 30), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcBmeInitializeINTEL, true, true, IR(687, 10), IR(45170, 30), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(45200, 39), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefSetBidirectionalMixDisableINTEL, true, true, IR(160, 3), IR(45239, 46), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefSetBilinearFilterEnableINTEL, true, true, IR(160, 3), IR(45285, 43), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(45328, 47), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(45375, 45), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithMultiReferenceINTEL, true, true, IR(130, 5), IR(45420, 46), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL, true, true, IR(215, 6), IR(45466, 56), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefConvertToMceResultINTEL, true, true, IR(160, 3), IR(45522, 38), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicInitializeINTEL, true, true, IR(160, 3), IR(45560, 30), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureSkcINTEL, true, true, IR(288, 8), IR(45590, 32), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureIpeLumaINTEL, true, true, IR(687, 10), IR(45622, 36), IR(0, 0), IR(291, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureIpeLumaChromaINTEL, true, true, IR(697, 13), IR(45658, 42), IR(0, 0), IR(293, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetMotionVectorMaskINTEL, true, true, IR(172, 4), IR(45700, 39), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(45739, 39), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraLumaShapePenaltyINTEL, true, true, IR(172, 4), IR(45778, 44), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraLumaModeCostFunctionINTEL, true, true, IR(215, 6), IR(45822, 48), IR(0, 0), IR(291, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraChromaModeCostFunctionINTEL, true, true, IR(172, 4), IR(45870, 50), IR(0, 0), IR(293, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetBilinearFilterEnableINTEL, true, true, IR(160, 3), IR(45920, 43), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetSkcForwardTransformEnableINTEL, true, true, IR(172, 4), IR(45963, 48), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetBlockBasedRawSkipSadINTEL, true, true, IR(172, 4), IR(46011, 43), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateIpeINTEL, true, true, IR(172, 4), IR(46054, 31), IR(0, 0), IR(291, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(46085, 47), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(46132, 45), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithMultiReferenceINTEL, true, true, IR(130, 5), IR(46177, 46), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL, true, true, IR(215, 6), IR(46223, 56), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConvertToMceResultINTEL, true, true, IR(160, 3), IR(46279, 38), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetIpeLumaShapeINTEL, true, true, IR(160, 3), IR(46317, 35), IR(0, 0), IR(291, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetBestIpeLumaDistortionINTEL, true, true, IR(160, 3), IR(46352, 44), IR(0, 0), IR(291, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetBestIpeChromaDistortionINTEL, true, true, IR(160, 3), IR(46396, 46), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedIpeLumaModesINTEL, true, true, IR(160, 3), IR(46442, 41), IR(0, 0), IR(291, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetIpeChromaModeINTEL, true, true, IR(160, 3), IR(46483, 36), IR(0, 0), IR(293, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL, true, true, IR(160, 3), IR(46519, 50), IR(0, 0), IR(291, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL, true, true, IR(160, 3), IR(46569, 48), IR(0, 0), IR(291, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetInterRawSadsINTEL, true, true, IR(160, 3), IR(46617, 35), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpVariableLengthArrayINTEL, true, true, IR(160, 3), IR(13496, 25), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpSaveMemoryINTEL, true, true, IR(39, 2), IR(46652, 16), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpRestoreMemoryINTEL, false, false, IR(10, 1), IR(46668, 19), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpArbitraryFloatSinCosPiALTERA, true, true, IR(710, 8), IR(46687, 29), IR(184, 1), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastALTERA, true, true, IR(710, 8), IR(46744, 25), IR(185, 1), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastFromIntALTERA, true, true, IR(710, 8), IR(46793, 32), IR(186, 1), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastToIntALTERA, true, true, IR(710, 8), IR(46856, 30), IR(187, 1), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatAddALTERA, true, true, IR(718, 10), IR(46915, 24), IR(188, 1), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSubALTERA, true, true, IR(718, 10), IR(46962, 24), IR(189, 1), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatMulALTERA, true, true, IR(718, 10), IR(47009, 24), IR(190, 1), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatDivALTERA, true, true, IR(718, 10), IR(47056, 24), IR(191, 1), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatGTALTERA, true, true, IR(728, 6), IR(47103, 23), IR(192, 1), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatGEALTERA, true, true, IR(728, 6), IR(47148, 23), IR(193, 1), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLTALTERA, true, true, IR(728, 6), IR(47193, 23), IR(194, 1), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLEALTERA, true, true, IR(728, 6), IR(47238, 23), IR(195, 1), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatEQALTERA, true, true, IR(728, 6), IR(47283, 23), IR(196, 1), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatRecipALTERA, true, true, IR(710, 8), IR(47328, 26), IR(197, 1), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatRSqrtALTERA, true, true, IR(710, 8), IR(47379, 26), IR(198, 1), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCbrtALTERA, true, true, IR(710, 8), IR(47430, 25), IR(199, 1), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatHypotALTERA, true, true, IR(718, 10), IR(47479, 26), IR(200, 1), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSqrtALTERA, true, true, IR(710, 8), IR(47530, 25), IR(201, 1), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLogINTEL, true, true, IR(710, 8), IR(47579, 23), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog2INTEL, true, true, IR(710, 8), IR(47602, 24), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog10INTEL, true, true, IR(710, 8), IR(47626, 25), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog1pINTEL, true, true, IR(710, 8), IR(47651, 25), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExpINTEL, true, true, IR(710, 8), IR(47676, 23), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExp2INTEL, true, true, IR(710, 8), IR(47699, 24), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExp10INTEL, true, true, IR(710, 8), IR(47723, 25), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExpm1INTEL, true, true, IR(710, 8), IR(47748, 25), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinINTEL, true, true, IR(710, 8), IR(47773, 23), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCosINTEL, true, true, IR(710, 8), IR(47796, 23), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinCosINTEL, true, true, IR(710, 8), IR(47819, 26), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinPiINTEL, true, true, IR(710, 8), IR(47845, 25), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCosPiINTEL, true, true, IR(710, 8), IR(47870, 25), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatASinINTEL, true, true, IR(710, 8), IR(47895, 24), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatASinPiINTEL, true, true, IR(710, 8), IR(47919, 26), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatACosINTEL, true, true, IR(710, 8), IR(47945, 24), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatACosPiINTEL, true, true, IR(710, 8), IR(47969, 26), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATanINTEL, true, true, IR(710, 8), IR(47995, 24), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATanPiINTEL, true, true, IR(710, 8), IR(48019, 26), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATan2INTEL, true, true, IR(718, 10), IR(48045, 25), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowINTEL, true, true, IR(718, 10), IR(48070, 23), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowRINTEL, true, true, IR(718, 10), IR(48093, 24), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowNINTEL, true, true, IR(718, 10), IR(48117, 24), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpLoopControlINTEL, false, false, IR(18, 1), IR(48141, 17), IR(0, 0), IR(297, 1), IR(115, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAliasDomainDeclINTEL, true, false, IR(734, 2), IR(48158, 21), IR(0, 0), IR(142, 1), IR(127, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAliasScopeDeclINTEL, true, false, IR(736, 3), IR(48179, 20), IR(0, 0), IR(142, 1), IR(127, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAliasScopeListDeclINTEL, true, false, IR(92, 2), IR(48199, 24), IR(0, 0), IR(142, 1), IR(127, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSqrtALTERA, true, true, IR(710, 8), IR(48223, 16), IR(202, 1), IR(195, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedRecipALTERA, true, true, IR(710, 8), IR(48254, 17), IR(203, 1), IR(195, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedRsqrtALTERA, true, true, IR(710, 8), IR(48287, 17), IR(204, 1), IR(195, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinALTERA, true, true, IR(710, 8), IR(48320, 15), IR(205, 1), IR(195, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedCosALTERA, true, true, IR(710, 8), IR(48349, 15), IR(206, 1), IR(195, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinCosALTERA, true, true, IR(710, 8), IR(48378, 18), IR(207, 1), IR(195, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinPiALTERA, true, true, IR(710, 8), IR(48413, 17), IR(208, 1), IR(195, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedCosPiALTERA, true, true, IR(710, 8), IR(48446, 17), IR(209, 1), IR(195, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinCosPiALTERA, true, true, IR(710, 8), IR(48479, 20), IR(210, 1), IR(195, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedLogALTERA, true, true, IR(710, 8), IR(48518, 15), IR(211, 1), IR(195, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedExpALTERA, true, true, IR(710, 8), IR(48547, 15), IR(212, 1), IR(195, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpPtrCastToCrossWorkgroupALTERA, true, true, IR(160, 3), IR(48576, 30), IR(213, 1), IR(206, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpCrossWorkgroupCastToPtrALTERA, true, true, IR(160, 3), IR(48635, 30), IR(214, 1), IR(206, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpReadPipeBlockingALTERA, true, true, IR(172, 4), IR(48694, 23), IR(215, 1), IR(298, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpWritePipeBlockingALTERA, true, true, IR(172, 4), IR(48739, 24), IR(216, 1), IR(298, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFPGARegALTERA, true, true, IR(160, 3), IR(14454, 14), IR(62, 1), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpRayQueryGetRayTMinKHR, true, true, IR(160, 3), IR(48786, 22), IR(0, 0), IR(199, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetRayFlagsKHR, true, true, IR(160, 3), IR(48808, 23), IR(0, 0), IR(199, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTKHR, true, true, IR(172, 4), IR(48831, 28), IR(0, 0), IR(199, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceCustomIndexKHR, true, true, IR(172, 4), IR(48859, 46), IR(0, 0), IR(199, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceIdKHR, true, true, IR(172, 4), IR(48905, 37), IR(0, 0), IR(199, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR, true, true, IR(172, 4), IR(48942, 65), IR(0, 0), IR(199, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionGeometryIndexKHR, true, true, IR(172, 4), IR(49007, 40), IR(0, 0), IR(199, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionPrimitiveIndexKHR, true, true, IR(172, 4), IR(49047, 41), IR(0, 0), IR(199, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionBarycentricsKHR, true, true, IR(172, 4), IR(49088, 39), IR(0, 0), IR(199, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionFrontFaceKHR, true, true, IR(172, 4), IR(49127, 36), IR(0, 0), IR(199, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionCandidateAABBOpaqueKHR, true, true, IR(160, 3), IR(49163, 46), IR(0, 0), IR(199, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectRayDirectionKHR, true, true, IR(172, 4), IR(49209, 45), IR(0, 0), IR(199, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectRayOriginKHR, true, true, IR(172, 4), IR(49254, 42), IR(0, 0), IR(199, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetWorldRayDirectionKHR, true, true, IR(160, 3), IR(49296, 32), IR(0, 0), IR(199, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetWorldRayOriginKHR, true, true, IR(160, 3), IR(49328, 29), IR(0, 0), IR(199, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectToWorldKHR, true, true, IR(172, 4), IR(49357, 40), IR(0, 0), IR(199, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionWorldToObjectKHR, true, true, IR(172, 4), IR(49397, 40), IR(0, 0), IR(199, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAtomicFAddEXT, true, true, IR(235, 6), IR(49437, 14), IR(0, 0), IR(300, 4), IR(151, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpTypeBufferSurfaceINTEL, true, false, IR(100, 2), IR(49451, 23), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeStructContinuedINTEL, false, false, IR(739, 1), IR(49474, 25), IR(0, 0), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantCompositeContinuedINTEL, false, false, IR(739, 1), IR(49499, 32), IR(0, 0), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCompositeContinuedINTEL, false, false, IR(739, 1), IR(49531, 36), IR(0, 0), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpCompositeConstructContinuedINTEL, true, true, IR(107, 3), IR(49567, 33), IR(0, 0), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpConvertFToBF16INTEL, true, true, IR(160, 3), IR(49600, 20), IR(0, 0), IR(305, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertBF16ToFINTEL, true, true, IR(160, 3), IR(49620, 20), IR(0, 0), IR(305, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpControlBarrierArriveINTEL, false, false, IR(221, 3), IR(49640, 26), IR(0, 0), IR(306, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpControlBarrierWaitINTEL, false, false, IR(221, 3), IR(49666, 24), IR(0, 0), IR(306, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpArithmeticFenceEXT, true, true, IR(160, 3), IR(14907, 19), IR(0, 0), IR(307, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpTaskSequenceCreateALTERA, true, true, IR(740, 7), IR(49690, 25), IR(217, 1), IR(308, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTaskSequenceAsyncALTERA, false, false, IR(168, 2), IR(49739, 24), IR(218, 1), IR(308, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTaskSequenceGetALTERA, true, true, IR(160, 3), IR(49786, 22), IR(219, 1), IR(308, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTaskSequenceReleaseALTERA, false, false, IR(10, 1), IR(49829, 26), IR(220, 1), IR(308, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeTaskSequenceALTERA, true, false, IR(68, 1), IR(49880, 23), IR(221, 1), IR(308, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupBlockPrefetchINTEL, false, false, IR(139, 3), IR(49925, 27), IR(0, 0), IR(309, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadINTEL, false, false, IR(747, 10), IR(49952, 25), IR(0, 0), IR(110, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadTransformINTEL, false, false, IR(747, 10), IR(49977, 34), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadTransposeINTEL, false, false, IR(747, 10), IR(50011, 34), IR(0, 0), IR(311, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockPrefetchINTEL, false, false, IR(757, 9), IR(50045, 29), IR(0, 0), IR(110, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockStoreINTEL, false, false, IR(747, 10), IR(50074, 26), IR(0, 0), IR(110, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupMatrixMultiplyAccumulateINTEL, true, true, IR(766, 7), IR(15384, 38), IR(0, 0), IR(312, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpBitwiseFunctionINTEL, true, true, IR(215, 6), IR(50162, 21), IR(0, 0), IR(313, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpUntypedVariableLengthArrayINTEL, true, true, IR(172, 4), IR(15450, 32), IR(0, 0), IR(314, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpConditionalExtensionINTEL, false, false, IR(45, 2), IR(50183, 26), IR(0, 0), IR(113, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpConditionalEntryPointINTEL, false, false, IR(773, 5), IR(50209, 27), IR(0, 0), IR(113, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpConditionalCapabilityINTEL, false, false, IR(778, 2), IR(50236, 27), IR(0, 0), IR(113, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpSpecConstantTargetINTEL, true, true, IR(780, 4), IR(50263, 24), IR(0, 0), IR(315, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantArchitectureINTEL, true, true, IR(784, 6), IR(50287, 30), IR(0, 0), IR(315, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCapabilitiesINTEL, true, true, IR(790, 3), IR(50354, 30), IR(0, 0), IR(315, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConditionalCopyObjectINTEL, true, true, IR(107, 3), IR(50384, 27), IR(0, 0), IR(113, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpGroupIMulKHR, true, true, IR(283, 5), IR(50411, 13), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMulKHR, true, true, IR(283, 5), IR(50424, 13), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseAndKHR, true, true, IR(283, 5), IR(50437, 19), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseOrKHR, true, true, IR(283, 5), IR(50456, 18), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseXorKHR, true, true, IR(283, 5), IR(50474, 19), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalAndKHR, true, true, IR(283, 5), IR(50493, 19), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalOrKHR, true, true, IR(283, 5), IR(50512, 18), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalXorKHR, true, true, IR(283, 5), IR(50530, 19), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpRoundFToTF32INTEL, true, true, IR(160, 3), IR(50549, 18), IR(0, 0), IR(317, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpMaskedGatherINTEL, true, true, IR(793, 6), IR(50567, 18), IR(0, 0), IR(318, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpMaskedScatterINTEL, false, false, IR(799, 4), IR(50585, 19), IR(0, 0), IR(318, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpConvertHandleToImageINTEL, true, true, IR(160, 3), IR(50604, 26), IR(0, 0), IR(319, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertHandleToSamplerINTEL, true, true, IR(160, 3), IR(50630, 28), IR(0, 0), IR(319, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertHandleToSampledImageINTEL, true, true, IR(160, 3), IR(50658, 33), IR(0, 0), IR(319, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpFDot2MixAcc32VALVE, true, true, IR(130, 5), IR(50691, 19), IR(0, 0), IR(320, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFDot2MixAcc16VALVE, true, true, IR(130, 5), IR(50710, 19), IR(0, 0), IR(322, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFDot4MixAcc32VALVE, true, true, IR(130, 5), IR(50729, 19), IR(0, 0), IR(324, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
}};

// Opcode strings (without the 'Op' prefix) and opcode values, ordered by name.
// The fields in order are:
//   name, either the primary name or an alias, indexing into kStrings
//   index into kInstructionDesc
static const std::array<NameIndex, 919> kInstructionNames{{
  {IR(41090, 13), 595}, // 0 AbsISubINTEL
  {IR(41103, 13), 596}, // 1 AbsUSubINTEL
  {IR(29719, 12), 58}, // 2 AccessChain
  {IR(48158, 21), 781}, // 3 AliasDomainDeclINTEL
  {IR(48179, 20), 782}, // 4 AliasScopeDeclINTEL
  {IR(48199, 24), 783}, // 5 AliasScopeListDeclINTEL
  {IR(31016, 4), 143}, // 6 All
  {IR(36395, 25), 426}, // 7 AllocateNodePayloadsAMDX
  {IR(31012, 4), 142}, // 8 Any
  {IR(47945, 24), 772}, // 9 ArbitraryFloatACosINTEL
  {IR(47969, 26), 773}, // 10 ArbitraryFloatACosPiINTEL
  {IR(47895, 24), 770}, // 11 ArbitraryFloatASinINTEL
  {IR(47919, 26), 771}, // 12 ArbitraryFloatASinPiINTEL
  {IR(48045, 25), 776}, // 13 ArbitraryFloatATan2INTEL
  {IR(47995, 24), 774}, // 14 ArbitraryFloatATanINTEL
  {IR(48019, 26), 775}, // 15 ArbitraryFloatATanPiINTEL
  {IR(46915, 24), 743}, // 16 ArbitraryFloatAddALTERA
  {IR(46939, 23), 743}, // 17 ArbitraryFloatAddINTEL
  {IR(46744, 25), 740}, // 18 ArbitraryFloatCastALTERA
  {IR(46793, 32), 741}, // 19 ArbitraryFloatCastFromIntALTERA
  {IR(46825, 31), 741}, // 20 ArbitraryFloatCastFromIntINTEL
  {IR(46769, 24), 740}, // 21 ArbitraryFloatCastINTEL
  {IR(46856, 30), 742}, // 22 ArbitraryFloatCastToIntALTERA
  {IR(46886, 29), 742}, // 23 ArbitraryFloatCastToIntINTEL
  {IR(47430, 25), 754}, // 24 ArbitraryFloatCbrtALTERA
  {IR(47455, 24), 754}, // 25 ArbitraryFloatCbrtINTEL
  {IR(47796, 23), 766}, // 26 ArbitraryFloatCosINTEL
  {IR(47870, 25), 769}, // 27 ArbitraryFloatCosPiINTEL
  {IR(47056, 24), 746}, // 28 ArbitraryFloatDivALTERA
  {IR(47080, 23), 746}, // 29 ArbitraryFloatDivINTEL
  {IR(47283, 23), 751}, // 30 ArbitraryFloatEQALTERA
  {IR(47306, 22), 751}, // 31 ArbitraryFloatEQINTEL
  {IR(47723, 25), 763}, // 32 ArbitraryFloatExp10INTEL
  {IR(47699, 24), 762}, // 33 ArbitraryFloatExp2INTEL
  {IR(47676, 23), 761}, // 34 ArbitraryFloatExpINTEL
  {IR(47748, 25), 764}, // 35 ArbitraryFloatExpm1INTEL
  {IR(47148, 23), 748}, // 36 ArbitraryFloatGEALTERA
  {IR(47171, 22), 748}, // 37 ArbitraryFloatGEINTEL
  {IR(47103, 23), 747}, // 38 ArbitraryFloatGTALTERA
  {IR(47126, 22), 747}, // 39 ArbitraryFloatGTINTEL
  {IR(47479, 26), 755}, // 40 ArbitraryFloatHypotALTERA
  {IR(47505, 25), 755}, // 41 ArbitraryFloatHypotINTEL
  {IR(47238, 23), 750}, // 42 ArbitraryFloatLEALTERA
  {IR(47261, 22), 750}, // 43 ArbitraryFloatLEINTEL
  {IR(47193, 23), 749}, // 44 ArbitraryFloatLTALTERA
  {IR(47216, 22), 749}, // 45 ArbitraryFloatLTINTEL
  {IR(47626, 25), 759}, // 46 ArbitraryFloatLog10INTEL
  {IR(47651, 25), 760}, // 47 ArbitraryFloatLog1pINTEL
  {IR(47602, 24), 758}, // 48 ArbitraryFloatLog2INTEL
  {IR(47579, 23), 757}, // 49 ArbitraryFloatLogINTEL
  {IR(47009, 24), 745}, // 50 ArbitraryFloatMulALTERA
  {IR(47033, 23), 745}, // 51 ArbitraryFloatMulINTEL
  {IR(48070, 23), 777}, // 52 ArbitraryFloatPowINTEL
  {IR(48117, 24), 779}, // 53 ArbitraryFloatPowNINTEL
  {IR(48093, 24), 778}, // 54 ArbitraryFloatPowRINTEL
  {IR(47379, 26), 753}, // 55 ArbitraryFloatRSqrtALTERA
  {IR(47405, 25), 753}, // 56 ArbitraryFloatRSqrtINTEL
  {IR(47328, 26), 752}, // 57 ArbitraryFloatRecipALTERA
  {IR(47354, 25), 752}, // 58 ArbitraryFloatRecipINTEL
  {IR(47819, 26), 767}, // 59 ArbitraryFloatSinCosINTEL
  {IR(46687, 29), 739}, // 60 ArbitraryFloatSinCosPiALTERA
  {IR(46716, 28), 739}, // 61 ArbitraryFloatSinCosPiINTEL
  {IR(47773, 23), 765}, // 62 ArbitraryFloatSinINTEL
  {IR(47845, 25), 768}, // 63 ArbitraryFloatSinPiINTEL
  {IR(47530, 25), 756}, // 64 ArbitraryFloatSqrtALTERA
  {IR(47555, 24), 756}, // 65 ArbitraryFloatSqrtINTEL
  {IR(46962, 24), 744}, // 66 ArbitraryFloatSubALTERA
  {IR(46986, 23), 744}, // 67 ArbitraryFloatSubINTEL
  {IR(14907, 19), 827}, // 68 ArithmeticFenceEXT
  {IR(29766, 12), 61}, // 69 ArrayLength
  {IR(41337, 13), 611}, // 70 AsmCallINTEL
  {IR(13258, 9), 610}, // 71 AsmINTEL
  {IR(41322, 15), 609}, // 72 AsmTargetINTEL
  {IR(41378, 14), 614}, // 73 AssumeTrueKHR
  {IR(32038, 10), 220}, // 74 AtomicAnd
  {IR(31890, 22), 210}, // 75 AtomicCompareExchange
  {IR(31912, 26), 211}, // 76 AtomicCompareExchangeWeak
  {IR(31875, 15), 209}, // 77 AtomicExchange
  {IR(49437, 14), 817}, // 78 AtomicFAddEXT
  {IR(41364, 14), 613}, // 79 AtomicFMaxEXT
  {IR(41350, 14), 612}, // 80 AtomicFMinEXT
  {IR(33423, 16), 292}, // 81 AtomicFlagClear
  {IR(33402, 21), 291}, // 82 AtomicFlagTestAndSet
  {IR(31972, 11), 214}, // 83 AtomicIAdd
  {IR(31955, 17), 213}, // 84 AtomicIDecrement
  {IR(31938, 17), 212}, // 85 AtomicIIncrement
  {IR(31983, 11), 215}, // 86 AtomicISub
  {IR(31852, 11), 207}, // 87 AtomicLoad
  {IR(32048, 9), 221}, // 88 AtomicOr
  {IR(32016, 11), 218}, // 89 AtomicSMax
  {IR(31994, 11), 216}, // 90 AtomicSMin
  {IR(31863, 12), 208}, // 91 AtomicStore
  {IR(32027, 11), 219}, // 92 AtomicUMax
  {IR(32005, 11), 217}, // 93 AtomicUMin
  {IR(32057, 10), 222}, // 94 AtomicXor
  {IR(39586, 28), 541}, // 95 BeginInvocationInterlockEXT
  {IR(35949, 17), 407}, // 96 BitCastArrayQCOM
  {IR(31636, 9), 191}, // 97 BitCount
  {IR(31576, 15), 187}, // 98 BitFieldInsert
  {IR(31591, 17), 188}, // 99 BitFieldSExtract
  {IR(31608, 17), 189}, // 100 BitFieldUExtract
  {IR(31625, 11), 190}, // 101 BitReverse
  {IR(30764, 8), 114}, // 102 Bitcast
  {IR(31561, 11), 185}, // 103 BitwiseAnd
  {IR(50162, 21), 840}, // 104 BitwiseFunctionINTEL
  {IR(31540, 10), 183}, // 105 BitwiseOr
  {IR(31550, 11), 184}, // 106 BitwiseXor
  {IR(32167, 7), 227}, // 107 Branch
  {IR(32174, 18), 228}, // 108 BranchConditional
  {IR(36656, 17), 437}, // 109 BufferPointerEXT
  {IR(33035, 13), 277}, // 110 BuildNDRange
  {IR(28780, 11), 15}, // 111 Capability
  {IR(32993, 26), 275}, // 112 CaptureEventProfilingInfo
  {IR(34499, 23), 344}, // 113 ColorAttachmentReadEXT
  {IR(32585, 15), 255}, // 114 CommitReadPipe
  {IR(32600, 16), 256}, // 115 CommitWritePipe
  {IR(30026, 19), 72}, // 116 CompositeConstruct
  {IR(49567, 33), 822}, // 117 CompositeConstructContinuedINTEL
  {IR(36082, 30), 412}, // 118 CompositeConstructCoopMatQCOM
  {IR(35657, 31), 395}, // 119 CompositeConstructReplicateEXT
  {IR(30045, 17), 73}, // 120 CompositeExtract
  {IR(36112, 28), 413}, // 121 CompositeExtractCoopMatQCOM
  {IR(30062, 16), 74}, // 122 CompositeInsert
  {IR(50236, 27), 844}, // 123 ConditionalCapabilityINTEL
  {IR(50384, 27), 848}, // 124 ConditionalCopyObjectINTEL
  {IR(50209, 27), 843}, // 125 ConditionalEntryPointINTEL
  {IR(50183, 26), 842}, // 126 ConditionalExtensionINTEL
  {IR(17165, 9), 39}, // 127 Constant
  {IR(29286, 18), 40}, // 128 ConstantComposite
  {IR(49499, 32), 820}, // 129 ConstantCompositeContinuedINTEL
  {IR(35593, 30), 393}, // 130 ConstantCompositeReplicateEXT
  {IR(29234, 14), 38}, // 131 ConstantFalse
  {IR(41268, 29), 607}, // 132 ConstantFunctionPointerINTEL
  {IR(29398, 13), 42}, // 133 ConstantNull
  {IR(33478, 20), 296}, // 134 ConstantPipeStorage
  {IR(29382, 16), 41}, // 135 ConstantSampler
  {IR(36721, 18), 440}, // 136 ConstantSizeOfEXT
  {IR(36548, 19), 432}, // 137 ConstantStringAMDX
  {IR(29221, 13), 37}, // 138 ConstantTrue
  {IR(31823, 15), 205}, // 139 ControlBarrier
  {IR(49640, 26), 825}, // 140 ControlBarrierArriveINTEL
  {IR(49666, 24), 826}, // 141 ControlBarrierWaitINTEL
  {IR(49620, 20), 824}, // 142 ConvertBF16ToFINTEL
  {IR(49600, 20), 823}, // 143 ConvertFToBF16INTEL
  {IR(30570, 12), 100}, // 144 ConvertFToS
  {IR(30558, 12), 99}, // 145 ConvertFToU
  {IR(50604, 26), 860}, // 146 ConvertHandleToImageINTEL
  {IR(50658, 33), 862}, // 147 ConvertHandleToSampledImageINTEL
  {IR(50630, 28), 861}, // 148 ConvertHandleToSamplerINTEL
  {IR(40235, 18), 564}, // 149 ConvertImageToUNV
  {IR(30647, 14), 107}, // 150 ConvertPtrToU
  {IR(30582, 12), 101}, // 151 ConvertSToF
  {IR(40298, 25), 567}, // 152 ConvertSampledImageToUNV
  {IR(40253, 20), 565}, // 153 ConvertSamplerToUNV
  {IR(35171, 35), 379}, // 154 ConvertUToAccelerationStructureKHR
  {IR(30594, 12), 102}, // 155 ConvertUToF
  {IR(40197, 18), 562}, // 156 ConvertUToImageNV
  {IR(30691, 14), 110}, // 157 ConvertUToPtr
  {IR(40273, 25), 566}, // 158 ConvertUToSampledImageNV
  {IR(40215, 20), 563}, // 159 ConvertUToSamplerNV
  {IR(37821, 27), 480}, // 160 CooperativeMatrixConvertNV
  {IR(35566, 27), 392}, // 161 CooperativeMatrixLengthKHR
  {IR(39560, 26), 540}, // 162 CooperativeMatrixLengthNV
  {IR(35434, 25), 389}, // 163 CooperativeMatrixLoadKHR
  {IR(39485, 24), 537}, // 164 CooperativeMatrixLoadNV
  {IR(39784, 30), 544}, // 165 CooperativeMatrixLoadTensorNV
  {IR(35539, 27), 391}, // 166 CooperativeMatrixMulAddKHR
  {IR(39534, 26), 539}, // 167 CooperativeMatrixMulAddNV
  {IR(39845, 32), 546}, // 168 CooperativeMatrixPerElementOpNV
  {IR(39683, 26), 543}, // 169 CooperativeMatrixReduceNV
  {IR(35459, 26), 390}, // 170 CooperativeMatrixStoreKHR
  {IR(39509, 25), 538}, // 171 CooperativeMatrixStoreNV
  {IR(39814, 31), 545}, // 172 CooperativeMatrixStoreTensorNV
  {IR(40168, 29), 561}, // 173 CooperativeMatrixTransposeNV
  {IR(38044, 24), 487}, // 174 CooperativeVectorLoadNV
  {IR(37789, 32), 479}, // 175 CooperativeVectorMatrixMulAddNV
  {IR(37679, 29), 476}, // 176 CooperativeVectorMatrixMulNV
  {IR(37708, 42), 477}, // 177 CooperativeVectorOuterProductAccumulateNV
  {IR(37750, 39), 478}, // 178 CooperativeVectorReduceSumAccumulateNV
  {IR(38068, 25), 488}, // 179 CooperativeVectorStoreNV
  {IR(34458, 12), 340}, // 180 CopyLogical
  {IR(29692, 11), 56}, // 181 CopyMemory
  {IR(29703, 16), 57}, // 182 CopyMemorySized
  {IR(30078, 11), 75}, // 183 CopyObject
  {IR(33498, 26), 297}, // 184 CreatePipeFromPipeStorage
  {IR(39913, 21), 549}, // 185 CreateTensorLayoutNV
  {IR(40033, 19), 554}, // 186 CreateTensorViewNV
  {IR(32945, 16), 272}, // 187 CreateUserEvent
  {IR(48635, 30), 796}, // 188 CrossWorkgroupCastToPtrALTERA
  {IR(48665, 29), 796}, // 189 CrossWorkgroupCastToPtrINTEL
  {IR(31645, 5), 192}, // 190 DPdx
  {IR(31691, 11), 198}, // 191 DPdxCoarse
  {IR(31662, 9), 195}, // 192 DPdxFine
  {IR(31650, 5), 193}, // 193 DPdy
  {IR(31702, 11), 199}, // 194 DPdyCoarse
  {IR(31671, 9), 196}, // 195 DPdyFine
  {IR(29852, 9), 64}, // 196 Decorate
  {IR(33675, 11), 305}, // 197 DecorateId
  {IR(41402, 15), 616}, // 198 DecorateString
  {IR(41417, 21), 616}, // 199 DecorateStringGOOGLE
  {IR(29876, 16), 66}, // 200 DecorationGroup
  {IR(12508, 25), 557}, // 201 DemoteToHelperInvocation
  {IR(12533, 28), 557}, // 202 DemoteToHelperInvocationEXT
  {IR(34522, 23), 345}, // 203 DepthAttachmentReadEXT
  {IR(30961, 4), 137}, // 204 Dot
  {IR(37848, 17), 481}, // 205 EmitMeshTasksEXT
  {IR(31750, 17), 203}, // 206 EmitStreamVertex
  {IR(31726, 11), 201}, // 207 EmitVertex
  {IR(39614, 26), 542}, // 208 EndInvocationInterlockEXT
  {IR(31737, 13), 202}, // 209 EndPrimitive
  {IR(31767, 19), 204}, // 210 EndStreamPrimitive
  {IR(32781, 14), 265}, // 211 EnqueueKernel
  {IR(32767, 14), 264}, // 212 EnqueueMarker
  {IR(36420, 24), 427}, // 213 EnqueueNodePayloadsAMDX
  {IR(28695, 11), 13}, // 214 EntryPoint
  {IR(35152, 19), 378}, // 215 ExecuteCallableKHR
  {IR(39196, 18), 527}, // 216 ExecuteCallableNV
  {IR(28738, 14), 14}, // 217 ExecutionMode
  {IR(33659, 16), 304}, // 218 ExecutionModeId
  {IR(41392, 10), 615}, // 219 ExpectKHR
  {IR(28549, 8), 11}, // 220 ExtInst
  {IR(28489, 14), 10}, // 221 ExtInstImport
  {IR(35089, 26), 375}, // 222 ExtInstWithForwardRefsKHR
  {IR(28479, 10), 9}, // 223 Extension
  {IR(36140, 20), 414}, // 224 ExtractSubArrayQCOM
  {IR(30793, 5), 118}, // 225 FAdd
  {IR(30624, 9), 105}, // 226 FConvert
  {IR(30828, 5), 125}, // 227 FDiv
  {IR(50710, 19), 864}, // 228 FDot2MixAcc16VALVE
  {IR(50691, 19), 863}, // 229 FDot2MixAcc32VALVE
  {IR(50729, 19), 865}, // 230 FDot4MixAcc32VALVE
  {IR(30853, 5), 130}, // 231 FMod
  {IR(30813, 5), 122}, // 232 FMul
  {IR(30780, 8), 116}, // 233 FNegate
  {IR(31290, 10), 168}, // 234 FOrdEqual
  {IR(31368, 16), 174}, // 235 FOrdGreaterThan
  {IR(31440, 21), 178}, // 236 FOrdGreaterThanEqual
  {IR(31340, 13), 172}, // 237 FOrdLessThan
  {IR(31402, 18), 176}, // 238 FOrdLessThanEqual
  {IR(31312, 13), 170}, // 239 FOrdNotEqual
  {IR(14454, 14), 799}, // 240 FPGARegALTERA
  {IR(14468, 13), 799}, // 241 FPGARegINTEL
  {IR(30848, 5), 129}, // 242 FRem
  {IR(30803, 5), 120}, // 243 FSub
  {IR(31300, 12), 169}, // 244 FUnordEqual
  {IR(31384, 18), 175}, // 245 FUnordGreaterThan
  {IR(31461, 23), 179}, // 246 FUnordGreaterThanEqual
  {IR(31353, 15), 173}, // 247 FUnordLessThan
  {IR(31420, 20), 177}, // 248 FUnordLessThanEqual
  {IR(31325, 15), 171}, // 249 FUnordNotEqual
  {IR(38006, 38), 486}, // 250 FetchMicroTriangleVertexBarycentricNV
  {IR(37971, 35), 485}, // 251 FetchMicroTriangleVertexPositionNV
  {IR(36469, 29), 429}, // 252 FinishWritingNodePayloadAMDX
  {IR(48349, 15), 788}, // 253 FixedCosALTERA
  {IR(48364, 14), 788}, // 254 FixedCosINTEL
  {IR(48446, 17), 791}, // 255 FixedCosPiALTERA
  {IR(48463, 16), 791}, // 256 FixedCosPiINTEL
  {IR(48547, 15), 794}, // 257 FixedExpALTERA
  {IR(48562, 14), 794}, // 258 FixedExpINTEL
  {IR(48518, 15), 793}, // 259 FixedLogALTERA
  {IR(48533, 14), 793}, // 260 FixedLogINTEL
  {IR(48254, 17), 785}, // 261 FixedRecipALTERA
  {IR(48271, 16), 785}, // 262 FixedRecipINTEL
  {IR(48287, 17), 786}, // 263 FixedRsqrtALTERA
  {IR(48304, 16), 786}, // 264 FixedRsqrtINTEL
  {IR(48320, 15), 787}, // 265 FixedSinALTERA
  {IR(48378, 18), 789}, // 266 FixedSinCosALTERA
  {IR(48396, 17), 789}, // 267 FixedSinCosINTEL
  {IR(48479, 20), 792}, // 268 FixedSinCosPiALTERA
  {IR(48499, 19), 792}, // 269 FixedSinCosPiINTEL
  {IR(48335, 14), 787}, // 270 FixedSinINTEL
  {IR(48413, 17), 790}, // 271 FixedSinPiALTERA
  {IR(48430, 16), 790}, // 272 FixedSinPiINTEL
  {IR(48223, 16), 784}, // 273 FixedSqrtALTERA
  {IR(48239, 15), 784}, // 274 FixedSqrtINTEL
  {IR(35006, 7), 369}, // 275 FmaKHR
  {IR(36365, 17), 424}, // 276 FragmentFetchAMD
  {IR(36344, 21), 423}, // 277 FragmentMaskFetchAMD
  {IR(27545, 9), 48}, // 278 Function
  {IR(29601, 13), 51}, // 279 FunctionCall
  {IR(29589, 12), 50}, // 280 FunctionEnd
  {IR(29571, 18), 49}, // 281 FunctionParameter
  {IR(41297, 25), 608}, // 282 FunctionPointerCallINTEL
  {IR(31655, 7), 194}, // 283 Fwidth
  {IR(31713, 13), 200}, // 284 FwidthCoarse
  {IR(31680, 11), 197}, // 285 FwidthFine
  {IR(30722, 17), 112}, // 286 GenericCastToPtr
  {IR(30739, 25), 113}, // 287 GenericCastToPtrExplicit
  {IR(29778, 23), 62}, // 288 GenericPtrMemSemantics
  {IR(33019, 16), 276}, // 289 GetDefaultQueue
  {IR(33524, 35), 298}, // 290 GetKernelLocalSizeForSubgroupCount
  {IR(33559, 25), 299}, // 291 GetKernelMaxNumSubgroups
  {IR(32825, 32), 267}, // 292 GetKernelNDrangeMaxSubGroupSize
  {IR(32795, 30), 266}, // 293 GetKernelNDrangeSubGroupCount
  {IR(32880, 40), 269}, // 294 GetKernelPreferredWorkGroupSizeMultiple
  {IR(32857, 23), 268}, // 295 GetKernelWorkGroupSize
  {IR(32651, 18), 259}, // 296 GetMaxPipePackets
  {IR(32633, 18), 258}, // 297 GetNumPipePackets
  {IR(9947, 9), 353}, // 298 GraphARM
  {IR(34674, 17), 351}, // 299 GraphConstantARM
  {IR(34742, 12), 356}, // 300 GraphEndARM
  {IR(34691, 19), 352}, // 301 GraphEntryPointARM
  {IR(34710, 14), 354}, // 302 GraphInputARM
  {IR(34724, 18), 355}, // 303 GraphSetOutputARM
  {IR(32338, 9), 238}, // 304 GroupAll
  {IR(32347, 9), 239}, // 305 GroupAny
  {IR(32307, 15), 236}, // 306 GroupAsyncCopy
  {IR(50437, 19), 851}, // 307 GroupBitwiseAndKHR
  {IR(50456, 18), 852}, // 308 GroupBitwiseOrKHR
  {IR(50474, 19), 853}, // 309 GroupBitwiseXorKHR
  {IR(32356, 15), 240}, // 310 GroupBroadcast
  {IR(32726, 20), 262}, // 311 GroupCommitReadPipe
  {IR(32746, 21), 263}, // 312 GroupCommitWritePipe
  {IR(29892, 14), 67}, // 313 GroupDecorate
  {IR(32414, 10), 242}, // 314 GroupFAdd
  {IR(36183, 23), 416}, // 315 GroupFAddNonUniformAMD
  {IR(32454, 10), 246}, // 316 GroupFMax
  {IR(36275, 23), 420}, // 317 GroupFMaxNonUniformAMD
  {IR(32424, 10), 243}, // 318 GroupFMin
  {IR(36206, 23), 417}, // 319 GroupFMinNonUniformAMD
  {IR(50424, 13), 850}, // 320 GroupFMulKHR
  {IR(32404, 10), 241}, // 321 GroupIAdd
  {IR(36160, 23), 415}, // 322 GroupIAddNonUniformAMD
  {IR(50411, 13), 849}, // 323 GroupIMulKHR
  {IR(50493, 19), 854}, // 324 GroupLogicalAndKHR
  {IR(50512, 18), 855}, // 325 GroupLogicalOrKHR
  {IR(50530, 19), 856}, // 326 GroupLogicalXorKHR
  {IR(29951, 20), 68}, // 327 GroupMemberDecorate
  {IR(33707, 19), 307}, // 328 GroupNonUniformAll
  {IR(33745, 24), 309}, // 329 GroupNonUniformAllEqual
  {IR(33726, 19), 308}, // 330 GroupNonUniformAny
  {IR(6517, 22), 312}, // 331 GroupNonUniformBallot
  {IR(33885, 30), 315}, // 332 GroupNonUniformBallotBitCount
  {IR(33853, 32), 314}, // 333 GroupNonUniformBallotBitExtract
  {IR(33915, 29), 316}, // 334 GroupNonUniformBallotFindLSB
  {IR(33944, 29), 317}, // 335 GroupNonUniformBallotFindMSB
  {IR(34251, 26), 332}, // 336 GroupNonUniformBitwiseAnd
  {IR(34277, 25), 333}, // 337 GroupNonUniformBitwiseOr
  {IR(34302, 26), 334}, // 338 GroupNonUniformBitwiseXor
  {IR(33769, 25), 310}, // 339 GroupNonUniformBroadcast
  {IR(33794, 30), 311}, // 340 GroupNonUniformBroadcastFirst
  {IR(33686, 21), 306}, // 341 GroupNonUniformElect
  {IR(34071, 20), 323}, // 342 GroupNonUniformFAdd
  {IR(34231, 20), 331}, // 343 GroupNonUniformFMax
  {IR(34171, 20), 328}, // 344 GroupNonUniformFMin
  {IR(34111, 20), 325}, // 345 GroupNonUniformFMul
  {IR(34051, 20), 322}, // 346 GroupNonUniformIAdd
  {IR(34091, 20), 324}, // 347 GroupNonUniformIMul
  {IR(33824, 29), 313}, // 348 GroupNonUniformInverseBallot
  {IR(34328, 26), 335}, // 349 GroupNonUniformLogicalAnd
  {IR(34354, 25), 336}, // 350 GroupNonUniformLogicalOr
  {IR(34379, 26), 337}, // 351 GroupNonUniformLogicalXor
  {IR(37883, 28), 483}, // 352 GroupNonUniformPartitionEXT
  {IR(37911, 27), 483}, // 353 GroupNonUniformPartitionNV
  {IR(36590, 26), 434}, // 354 GroupNonUniformQuadAllKHR
  {IR(36616, 26), 435}, // 355 GroupNonUniformQuadAnyKHR
  {IR(34405, 29), 338}, // 356 GroupNonUniformQuadBroadcast
  {IR(34434, 24), 339}, // 357 GroupNonUniformQuadSwap
  {IR(14693, 25), 373}, // 358 GroupNonUniformRotateKHR
  {IR(34191, 20), 329}, // 359 GroupNonUniformSMax
  {IR(34131, 20), 326}, // 360 GroupNonUniformSMin
  {IR(9656, 23), 318}, // 361 GroupNonUniformShuffle
  {IR(34024, 27), 321}, // 362 GroupNonUniformShuffleDown
  {IR(33999, 25), 320}, // 363 GroupNonUniformShuffleUp
  {IR(33973, 26), 319}, // 364 GroupNonUniformShuffleXor
  {IR(34211, 20), 330}, // 365 GroupNonUniformUMax
  {IR(34151, 20), 327}, // 366 GroupNonUniformUMin
  {IR(32669, 28), 260}, // 367 GroupReserveReadPipePackets
  {IR(32697, 29), 261}, // 368 GroupReserveWritePipePackets
  {IR(32474, 10), 248}, // 369 GroupSMax
  {IR(36321, 23), 422}, // 370 GroupSMaxNonUniformAMD
  {IR(32444, 10), 245}, // 371 GroupSMin
  {IR(36252, 23), 419}, // 372 GroupSMinNonUniformAMD
  {IR(32464, 10), 247}, // 373 GroupUMax
  {IR(36298, 23), 421}, // 374 GroupUMaxNonUniformAMD
  {IR(32434, 10), 244}, // 375 GroupUMin
  {IR(36229, 23), 418}, // 376 GroupUMinNonUniformAMD
  {IR(32322, 16), 237}, // 377 GroupWaitEvents
  {IR(38540, 26), 504}, // 378 HitObjectExecuteShaderEXT
  {IR(37174, 25), 456}, // 379 HitObjectExecuteShaderNV
  {IR(38593, 26), 506}, // 380 HitObjectGetAttributesEXT
  {IR(37225, 25), 458}, // 381 HitObjectGetAttributesNV
  {IR(39272, 24), 529}, // 382 HitObjectGetClusterIdNV
  {IR(38566, 27), 505}, // 383 HitObjectGetCurrentTimeEXT
  {IR(37199, 26), 457}, // 384 HitObjectGetCurrentTimeNV
  {IR(38672, 29), 509}, // 385 HitObjectGetGeometryIndexEXT
  {IR(37301, 28), 461}, // 386 HitObjectGetGeometryIndexNV
  {IR(38619, 23), 507}, // 387 HitObjectGetHitKindEXT
  {IR(37250, 22), 459}, // 388 HitObjectGetHitKindNV
  {IR(38727, 35), 511}, // 389 HitObjectGetInstanceCustomIndexEXT
  {IR(37354, 34), 463}, // 390 HitObjectGetInstanceCustomIndexNV
  {IR(38701, 26), 510}, // 391 HitObjectGetInstanceIdEXT
  {IR(37329, 25), 462}, // 392 HitObjectGetInstanceIdNV
  {IR(38173, 51), 492}, // 393 HitObjectGetIntersectionTriangleVertexPositionsEXT
  {IR(40664, 27), 577}, // 394 HitObjectGetLSSPositionsNV
  {IR(40691, 23), 578}, // 395 HitObjectGetLSSRadiiNV
  {IR(38793, 34), 513}, // 396 HitObjectGetObjectRayDirectionEXT
  {IR(36886, 33), 446}, // 397 HitObjectGetObjectRayDirectionNV
  {IR(38762, 31), 512}, // 398 HitObjectGetObjectRayOriginEXT
  {IR(36919, 30), 447}, // 399 HitObjectGetObjectRayOriginNV
  {IR(38890, 29), 516}, // 400 HitObjectGetObjectToWorldEXT
  {IR(36858, 28), 445}, // 401 HitObjectGetObjectToWorldNV
  {IR(38642, 30), 508}, // 402 HitObjectGetPrimitiveIndexEXT
  {IR(37272, 29), 460}, // 403 HitObjectGetPrimitiveIndexNV
  {IR(38224, 24), 493}, // 404 HitObjectGetRayFlagsEXT
  {IR(38948, 23), 518}, // 405 HitObjectGetRayTMaxEXT
  {IR(37449, 22), 466}, // 406 HitObjectGetRayTMaxNV
  {IR(39296, 23), 530}, // 407 HitObjectGetRayTMinEXT
  {IR(37471, 22), 467}, // 408 HitObjectGetRayTMinNV
  {IR(39319, 45), 531}, // 409 HitObjectGetShaderBindingTableRecordIndexEXT
  {IR(37014, 44), 450}, // 410 HitObjectGetShaderBindingTableRecordIndexNV
  {IR(39364, 40), 532}, // 411 HitObjectGetShaderRecordBufferHandleEXT
  {IR(36975, 39), 449}, // 412 HitObjectGetShaderRecordBufferHandleNV
  {IR(40608, 29), 575}, // 413 HitObjectGetSpherePositionNV
  {IR(40637, 27), 576}, // 414 HitObjectGetSphereRadiusNV
  {IR(38827, 33), 514}, // 415 HitObjectGetWorldRayDirectionEXT
  {IR(37388, 32), 464}, // 416 HitObjectGetWorldRayDirectionNV
  {IR(38860, 30), 515}, // 417 HitObjectGetWorldRayOriginEXT
  {IR(37420, 29), 465}, // 418 HitObjectGetWorldRayOriginNV
  {IR(38919, 29), 517}, // 419 HitObjectGetWorldToObjectEXT
  {IR(36830, 28), 444}, // 420 HitObjectGetWorldToObjectNV
  {IR(39404, 20), 533}, // 421 HitObjectIsEmptyEXT
  {IR(37493, 19), 468}, // 422 HitObjectIsEmptyNV
  {IR(39424, 18), 534}, // 423 HitObjectIsHitEXT
  {IR(37512, 17), 469}, // 424 HitObjectIsHitNV
  {IR(40737, 20), 580}, // 425 HitObjectIsLSSHitNV
  {IR(39442, 19), 535}, // 426 HitObjectIsMissEXT
  {IR(37529, 18), 470}, // 427 HitObjectIsMissNV
  {IR(40714, 23), 579}, // 428 HitObjectIsSphereHitNV
  {IR(38516, 24), 503}, // 429 HitObjectRecordEmptyEXT
  {IR(37058, 23), 451}, // 430 HitObjectRecordEmptyNV
  {IR(38093, 28), 489}, // 431 HitObjectRecordFromQueryEXT
  {IR(36739, 27), 441}, // 432 HitObjectRecordHitMotionNV
  {IR(37101, 21), 453}, // 433 HitObjectRecordHitNV
  {IR(36766, 36), 442}, // 434 HitObjectRecordHitWithIndexMotionNV
  {IR(37122, 30), 454}, // 435 HitObjectRecordHitWithIndexNV
  {IR(38121, 23), 490}, // 436 HitObjectRecordMissEXT
  {IR(38144, 29), 491}, // 437 HitObjectRecordMissMotionEXT
  {IR(36802, 28), 443}, // 438 HitObjectRecordMissMotionNV
  {IR(37152, 22), 455}, // 439 HitObjectRecordMissNV
  {IR(38293, 33), 495}, // 440 HitObjectReorderExecuteShaderEXT
  {IR(38248, 45), 494}, // 441 HitObjectSetShaderBindingTableRecordIndexEXT
  {IR(38358, 38), 497}, // 442 HitObjectTraceMotionReorderExecuteEXT
  {IR(38468, 21), 501}, // 443 HitObjectTraceRayEXT
  {IR(38489, 27), 502}, // 444 HitObjectTraceRayMotionEXT
  {IR(36949, 26), 448}, // 445 HitObjectTraceRayMotionNV
  {IR(37081, 20), 452}, // 446 HitObjectTraceRayNV
  {IR(38326, 32), 496}, // 447 HitObjectTraceReorderExecuteEXT
  {IR(30788, 5), 117}, // 448 IAdd
  {IR(30965, 10), 138}, // 449 IAddCarry
  {IR(41116, 13), 597}, // 450 IAddSatINTEL
  {IR(41142, 14), 599}, // 451 IAverageINTEL
  {IR(41170, 21), 601}, // 452 IAverageRoundedINTEL
  {IR(31161, 7), 158}, // 453 IEqual
  {IR(30808, 5), 121}, // 454 IMul
  {IR(41238, 15), 605}, // 455 IMul32x16INTEL
  {IR(31168, 10), 159}, // 456 INotEqual
  {IR(30798, 5), 119}, // 457 ISub
  {IR(30975, 11), 139}, // 458 ISubBorrow
  {IR(41212, 13), 603}, // 459 ISubSatINTEL
  {IR(35206, 22), 380}, // 460 IgnoreIntersectionKHR
  {IR(39014, 21), 520}, // 461 IgnoreIntersectionNV
  {IR(27589, 6), 91}, // 462 Image
  {IR(36053, 29), 411}, // 463 ImageBlockMatchGatherSADQCOM
  {IR(36024, 29), 410}, // 464 ImageBlockMatchGatherSSDQCOM
  {IR(35926, 23), 406}, // 465 ImageBlockMatchSADQCOM
  {IR(35903, 23), 405}, // 466 ImageBlockMatchSSDQCOM
  {IR(35995, 29), 409}, // 467 ImageBlockMatchWindowSADQCOM
  {IR(35966, 29), 408}, // 468 ImageBlockMatchWindowSSDQCOM
  {IR(35884, 19), 404}, // 469 ImageBoxFilterQCOM
  {IR(30406, 16), 88}, // 470 ImageDrefGather
  {IR(30383, 11), 86}, // 471 ImageFetch
  {IR(30394, 12), 87}, // 472 ImageGather
  {IR(30443, 17), 92}, // 473 ImageQueryFormat
  {IR(30523, 17), 97}, // 474 ImageQueryLevels
  {IR(30509, 14), 96}, // 475 ImageQueryLod
  {IR(30460, 16), 93}, // 476 ImageQueryOrder
  {IR(30540, 18), 98}, // 477 ImageQuerySamples
  {IR(30494, 15), 95}, // 478 ImageQuerySize
  {IR(30476, 18), 94}, // 479 ImageQuerySizeLod
  {IR(30422, 10), 89}, // 480 ImageRead
  {IR(30240, 27), 81}, // 481 ImageSampleDrefExplicitLod
  {IR(30213, 27), 80}, // 482 ImageSampleDrefImplicitLod
  {IR(30190, 23), 79}, // 483 ImageSampleExplicitLod
  {IR(37616, 23), 474}, // 484 ImageSampleFootprintNV
  {IR(30144, 23), 78}, // 485 ImageSampleImplicitLod
  {IR(30352, 31), 85}, // 486 ImageSampleProjDrefExplicitLod
  {IR(30321, 31), 84}, // 487 ImageSampleProjDrefImplicitLod
  {IR(30294, 27), 83}, // 488 ImageSampleProjExplicitLod
  {IR(30267, 27), 82}, // 489 ImageSampleProjImplicitLod
  {IR(35860, 24), 403}, // 490 ImageSampleWeightedQCOM
  {IR(33347, 22), 288}, // 491 ImageSparseDrefGather
  {IR(33312, 17), 286}, // 492 ImageSparseFetch
  {IR(33329, 18), 287}, // 493 ImageSparseGather
  {IR(33439, 16), 293}, // 494 ImageSparseRead
  {IR(33139, 33), 281}, // 495 ImageSparseSampleDrefExplicitLod
  {IR(33106, 33), 280}, // 496 ImageSparseSampleDrefImplicitLod
  {IR(33077, 29), 279}, // 497 ImageSparseSampleExplicitLod
  {IR(33048, 29), 278}, // 498 ImageSparseSampleImplicitLod
  {IR(33275, 37), 285}, // 499 ImageSparseSampleProjDrefExplicitLod
  {IR(33238, 37), 284}, // 500 ImageSparseSampleProjDrefImplicitLod
  {IR(33205, 33), 283}, // 501 ImageSparseSampleProjExplicitLod
  {IR(33172, 33), 282}, // 502 ImageSparseSampleProjImplicitLod
  {IR(33369, 26), 289}, // 503 ImageSparseTexelsResident
  {IR(29623, 18), 53}, // 504 ImageTexelPointer
  {IR(30432, 11), 90}, // 505 ImageWrite
  {IR(29731, 20), 59}, // 506 InBoundsAccessChain
  {IR(29801, 23), 63}, // 507 InBoundsPtrAccessChain
  {IR(31032, 9), 146}, // 508 IsFinite
  {IR(40099, 22), 558}, // 509 IsHelperInvocationEXT
  {IR(31026, 6), 145}, // 510 IsInf
  {IR(31020, 6), 144}, // 511 IsNan
  {IR(36525, 23), 431}, // 512 IsNodePayloadValidAMDX
  {IR(31041, 9), 147}, // 513 IsNormal
  {IR(32961, 13), 273}, // 514 IsValidEvent
  {IR(32616, 17), 257}, // 515 IsValidReserveId
  {IR(32244, 5), 230}, // 516 Kill
  {IR(32161, 6), 226}, // 517 Label
  {IR(31061, 14), 149}, // 518 LessOrGreater
  {IR(32280, 14), 234}, // 519 LifetimeStart
  {IR(32294, 13), 235}, // 520 LifetimeStop
  {IR(28474, 5), 8}, // 521 Line
  {IR(29681, 5), 54}, // 522 Load
  {IR(31132, 11), 155}, // 523 LogicalAnd
  {IR(31093, 13), 152}, // 524 LogicalEqual
  {IR(31143, 11), 156}, // 525 LogicalNot
  {IR(31106, 16), 153}, // 526 LogicalNotEqual
  {IR(31122, 10), 154}, // 527 LogicalOr
  {IR(48141, 17), 780}, // 528 LoopControlINTEL
  {IR(32101, 10), 224}, // 529 LoopMerge
  {IR(50567, 18), 858}, // 530 MaskedGatherINTEL
  {IR(50585, 19), 859}, // 531 MaskedScatterINTEL
  {IR(30930, 18), 135}, // 532 MatrixTimesMatrix
  {IR(30876, 18), 132}, // 533 MatrixTimesScalar
  {IR(30912, 18), 134}, // 534 MatrixTimesVector
  {IR(29861, 15), 65}, // 535 MemberDecorate
  {IR(36701, 20), 439}, // 536 MemberDecorateIdEXT
  {IR(41438, 21), 617}, // 537 MemberDecorateString
  {IR(41459, 27), 617}, // 538 MemberDecorateStringGOOGLE
  {IR(28456, 11), 6}, // 539 MemberName
  {IR(31838, 14), 206}, // 540 MemoryBarrier
  {IR(28621, 12), 12}, // 541 MemoryModel
  {IR(33624, 19), 302}, // 542 MemoryNamedBarrier
  {IR(33643, 16), 303}, // 543 ModuleProcessed
  {IR(28451, 5), 5}, // 544 Name
  {IR(33601, 23), 301}, // 545 NamedBarrierInitialize
  {IR(33395, 7), 290}, // 546 NoLine
  {IR(36498, 27), 430}, // 547 NodePayloadArrayLengthAMDX
  {IR(28247, 4), 0}, // 548 Nop
  {IR(31572, 4), 186}, // 549 Not
  {IR(31075, 8), 150}, // 550 Ordered
  {IR(30948, 13), 136}, // 551 OuterProduct
  {IR(32067, 4), 223}, // 552 Phi
  {IR(29751, 15), 60}, // 553 PtrAccessChain
  {IR(48576, 30), 795}, // 554 PtrCastToCrossWorkgroupALTERA
  {IR(48606, 29), 795}, // 555 PtrCastToCrossWorkgroupINTEL
  {IR(30705, 17), 111}, // 556 PtrCastToGeneric
  {IR(34491, 8), 343}, // 557 PtrDiff
  {IR(34470, 9), 341}, // 558 PtrEqual
  {IR(34479, 12), 342}, // 559 PtrNotEqual
  {IR(30633, 14), 106}, // 560 QuantizeToF16
  {IR(40404, 17), 569}, // 561 RawAccessChainNV
  {IR(35779, 31), 400}, // 562 RayQueryConfirmIntersectionKHR
  {IR(35747, 32), 399}, // 563 RayQueryGenerateIntersectionKHR
  {IR(39249, 23), 528}, // 564 RayQueryGetClusterIdNV
  {IR(49088, 39), 808}, // 565 RayQueryGetIntersectionBarycentricsKHR
  {IR(49163, 46), 810}, // 566 RayQueryGetIntersectionCandidateAABBOpaqueKHR
  {IR(39214, 35), 528}, // 567 RayQueryGetIntersectionClusterIdNV
  {IR(49127, 36), 809}, // 568 RayQueryGetIntersectionFrontFaceKHR
  {IR(49007, 40), 806}, // 569 RayQueryGetIntersectionGeometryIndexKHR
  {IR(48859, 46), 803}, // 570 RayQueryGetIntersectionInstanceCustomIndexKHR
  {IR(48905, 37), 804}, // 571 RayQueryGetIntersectionInstanceIdKHR
  {IR(48942, 65), 805}, // 572 RayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR
  {IR(40571, 37), 574}, // 573 RayQueryGetIntersectionLSSHitValueNV
  {IR(40499, 38), 572}, // 574 RayQueryGetIntersectionLSSPositionsNV
  {IR(40537, 34), 573}, // 575 RayQueryGetIntersectionLSSRadiiNV
  {IR(49209, 45), 811}, // 576 RayQueryGetIntersectionObjectRayDirectionKHR
  {IR(49254, 42), 812}, // 577 RayQueryGetIntersectionObjectRayOriginKHR
  {IR(49357, 40), 815}, // 578 RayQueryGetIntersectionObjectToWorldKHR
  {IR(49047, 41), 807}, // 579 RayQueryGetIntersectionPrimitiveIndexKHR
  {IR(40421, 40), 570}, // 580 RayQueryGetIntersectionSpherePositionNV
  {IR(40461, 38), 571}, // 581 RayQueryGetIntersectionSphereRadiusNV
  {IR(48831, 28), 802}, // 582 RayQueryGetIntersectionTKHR
  {IR(39089, 50), 525}, // 583 RayQueryGetIntersectionTriangleVertexPositionsKHR
  {IR(35829, 31), 402}, // 584 RayQueryGetIntersectionTypeKHR
  {IR(49397, 40), 816}, // 585 RayQueryGetIntersectionWorldToObjectKHR
  {IR(48808, 23), 801}, // 586 RayQueryGetRayFlagsKHR
  {IR(48786, 22), 800}, // 587 RayQueryGetRayTMinKHR
  {IR(49296, 32), 813}, // 588 RayQueryGetWorldRayDirectionKHR
  {IR(49328, 29), 814}, // 589 RayQueryGetWorldRayOriginKHR
  {IR(35704, 22), 397}, // 590 RayQueryInitializeKHR
  {IR(40779, 19), 582}, // 591 RayQueryIsLSSHitNV
  {IR(40757, 22), 581}, // 592 RayQueryIsSphereHitNV
  {IR(35810, 19), 401}, // 593 RayQueryProceedKHR
  {IR(35726, 21), 398}, // 594 RayQueryTerminateKHR
  {IR(36382, 13), 425}, // 595 ReadClockKHR
  {IR(32484, 9), 249}, // 596 ReadPipe
  {IR(48694, 23), 797}, // 597 ReadPipeBlockingALTERA
  {IR(48717, 22), 797}, // 598 ReadPipeBlockingINTEL
  {IR(32932, 13), 271}, // 599 ReleaseEvent
  {IR(38413, 25), 499}, // 600 ReorderThreadWithHintEXT
  {IR(37576, 24), 472}, // 601 ReorderThreadWithHintNV
  {IR(38438, 30), 500}, // 602 ReorderThreadWithHitObjectEXT
  {IR(37547, 29), 471}, // 603 ReorderThreadWithHitObjectNV
  {IR(38971, 22), 519}, // 604 ReportIntersectionKHR
  {IR(38993, 21), 519}, // 605 ReportIntersectionNV
  {IR(32538, 23), 253}, // 606 ReserveReadPipePackets
  {IR(32561, 24), 254}, // 607 ReserveWritePipePackets
  {IR(32503, 17), 251}, // 608 ReservedReadPipe
  {IR(32520, 18), 252}, // 609 ReservedWritePipe
  {IR(46668, 19), 738}, // 610 RestoreMemoryINTEL
  {IR(32920, 12), 270}, // 611 RetainEvent
  {IR(32249, 7), 231}, // 612 Return
  {IR(32256, 12), 232}, // 613 ReturnValue
  {IR(50549, 18), 857}, // 614 RoundFToTF32INTEL
  {IR(30615, 9), 104}, // 615 SConvert
  {IR(30823, 5), 124}, // 616 SDiv
  {IR(35291, 5), 382}, // 617 SDot
  {IR(35332, 11), 385}, // 618 SDotAccSat
  {IR(35343, 14), 385}, // 619 SDotAccSatKHR
  {IR(35296, 8), 382}, // 620 SDotKHR
  {IR(31191, 13), 161}, // 621 SGreaterThan
  {IR(31222, 18), 163}, // 622 SGreaterThanEqual
  {IR(31250, 10), 165}, // 623 SLessThan
  {IR(31275, 15), 167}, // 624 SLessThanEqual
  {IR(30843, 5), 128}, // 625 SMod
  {IR(30999, 13), 141}, // 626 SMulExtended
  {IR(30772, 8), 115}, // 627 SNegate
  {IR(30838, 5), 127}, // 628 SRem
  {IR(35317, 6), 384}, // 629 SUDot
  {IR(35382, 12), 387}, // 630 SUDotAccSat
  {IR(35394, 15), 387}, // 631 SUDotAccSatKHR
  {IR(35323, 9), 384}, // 632 SUDotKHR
  {IR(30099, 13), 77}, // 633 SampledImage
  {IR(40323, 29), 568}, // 634 SamplerImageAddressingModeNV
  {IR(30661, 15), 108}, // 635 SatConvertSToU
  {IR(30676, 15), 109}, // 636 SatConvertUToS
  {IR(46652, 16), 737}, // 637 SaveMemoryINTEL
  {IR(31154, 7), 157}, // 638 Select
  {IR(32146, 15), 225}, // 639 SelectionMerge
  {IR(37865, 18), 482}, // 640 SetMeshOutputsEXT
  {IR(32974, 19), 274}, // 641 SetUserEventStatus
  {IR(31523, 17), 182}, // 642 ShiftLeftLogical
  {IR(31502, 21), 181}, // 643 ShiftRightArithmetic
  {IR(31484, 18), 180}, // 644 ShiftRightLogical
  {IR(31050, 11), 148}, // 645 SignBitSet
  {IR(33455, 7), 294}, // 646 SizeOf
  {IR(28428, 7), 3}, // 647 Source
  {IR(28309, 16), 2}, // 648 SourceContinued
  {IR(28435, 16), 4}, // 649 SourceExtension
  {IR(29446, 13), 45}, // 650 SpecConstant
  {IR(50287, 30), 846}, // 651 SpecConstantArchitectureINTEL
  {IR(50354, 30), 847}, // 652 SpecConstantCapabilitiesINTEL
  {IR(29459, 22), 46}, // 653 SpecConstantComposite
  {IR(49531, 36), 821}, // 654 SpecConstantCompositeContinuedINTEL
  {IR(35623, 34), 394}, // 655 SpecConstantCompositeReplicateEXT
  {IR(29428, 18), 44}, // 656 SpecConstantFalse
  {IR(29522, 15), 47}, // 657 SpecConstantOp
  {IR(36567, 23), 433}, // 658 SpecConstantStringAMDX
  {IR(50263, 24), 845}, // 659 SpecConstantTargetINTEL
  {IR(29411, 17), 43}, // 660 SpecConstantTrue
  {IR(34545, 25), 346}, // 661 StencilAttachmentReadEXT
  {IR(29686, 6), 55}, // 662 Store
  {IR(28467, 7), 7}, // 663 String
  {IR(49952, 25), 834}, // 664 Subgroup2DBlockLoadINTEL
  {IR(49977, 34), 835}, // 665 Subgroup2DBlockLoadTransformINTEL
  {IR(50011, 34), 836}, // 666 Subgroup2DBlockLoadTransposeINTEL
  {IR(50045, 29), 837}, // 667 Subgroup2DBlockPrefetchINTEL
  {IR(50074, 26), 838}, // 668 Subgroup2DBlockStoreINTEL
  {IR(35043, 20), 372}, // 669 SubgroupAllEqualKHR
  {IR(35013, 15), 370}, // 670 SubgroupAllKHR
  {IR(35028, 15), 371}, // 671 SubgroupAnyKHR
  {IR(45170, 30), 701}, // 672 SubgroupAvcBmeInitializeINTEL
  {IR(45140, 30), 700}, // 673 SubgroupAvcFmeInitializeINTEL
  {IR(43575, 35), 670}, // 674 SubgroupAvcImeAdjustRefOffsetINTEL
  {IR(43610, 39), 671}, // 675 SubgroupAvcImeConvertToMcePayloadINTEL
  {IR(44251, 38), 684}, // 676 SubgroupAvcImeConvertToMceResultINTEL
  {IR(43874, 45), 677}, // 677 SubgroupAvcImeEvaluateWithDualReferenceINTEL
  {IR(43974, 53), 679}, // 678 SubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL
  {IR(44195, 56), 683}, // 679 SubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL
  {IR(44083, 54), 681}, // 680 SubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL
  {IR(43827, 47), 676}, // 681 SubgroupAvcImeEvaluateWithSingleReferenceINTEL
  {IR(43919, 55), 678}, // 682 SubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL
  {IR(44137, 58), 682}, // 683 SubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL
  {IR(44027, 56), 680}, // 684 SubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL
  {IR(44883, 36), 695}, // 685 SubgroupAvcImeGetBorderReachedINTEL
  {IR(44335, 44), 686}, // 686 SubgroupAvcImeGetDualReferenceStreaminINTEL
  {IR(44289, 46), 685}, // 687 SubgroupAvcImeGetSingleReferenceStreaminINTEL
  {IR(44750, 66), 693}, // 688 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL
  {IR(44682, 68), 692}, // 689 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL
  {IR(44816, 67), 694}, // 690 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL
  {IR(44545, 68), 690}, // 691 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL
  {IR(44475, 70), 689}, // 692 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL
  {IR(44613, 69), 691}, // 693 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL
  {IR(44919, 48), 696}, // 694 SubgroupAvcImeGetTruncatedSearchIndicationINTEL
  {IR(44967, 59), 697}, // 695 SubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL
  {IR(45084, 56), 699}, // 696 SubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL
  {IR(45026, 58), 698}, // 697 SubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL
  {IR(43438, 30), 666}, // 698 SubgroupAvcImeInitializeINTEL
  {IR(43542, 33), 669}, // 699 SubgroupAvcImeRefWindowSizeINTEL
  {IR(43506, 36), 668}, // 700 SubgroupAvcImeSetDualReferenceINTEL
  {IR(43739, 54), 674}, // 701 SubgroupAvcImeSetEarlySearchTerminationThresholdINTEL
  {IR(43649, 43), 672}, // 702 SubgroupAvcImeSetMaxMotionVectorCountINTEL
  {IR(43468, 38), 667}, // 703 SubgroupAvcImeSetSingleReferenceINTEL
  {IR(43692, 47), 673}, // 704 SubgroupAvcImeSetUnidirectionalMixDisableINTEL
  {IR(43793, 34), 675}, // 705 SubgroupAvcImeSetWeightedSadINTEL
  {IR(44428, 47), 688}, // 706 SubgroupAvcImeStripDualReferenceStreamoutINTEL
  {IR(44379, 49), 687}, // 707 SubgroupAvcImeStripSingleReferenceStreamoutINTEL
  {IR(42828, 39), 651}, // 708 SubgroupAvcMceConvertToImePayloadINTEL
  {IR(42867, 38), 652}, // 709 SubgroupAvcMceConvertToImeResultINTEL
  {IR(42905, 39), 653}, // 710 SubgroupAvcMceConvertToRefPayloadINTEL
  {IR(42944, 38), 654}, // 711 SubgroupAvcMceConvertToRefResultINTEL
  {IR(42982, 39), 655}, // 712 SubgroupAvcMceConvertToSicPayloadINTEL
  {IR(43021, 38), 656}, // 713 SubgroupAvcMceConvertToSicResultINTEL
  {IR(43134, 43), 659}, // 714 SubgroupAvcMceGetBestInterDistortionsINTEL
  {IR(42266, 50), 640}, // 715 SubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL
  {IR(41864, 60), 632}, // 716 SubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL
  {IR(42064, 51), 636}, // 717 SubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL
  {IR(42210, 56), 639}, // 718 SubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL
  {IR(41977, 47), 634}, // 719 SubgroupAvcMceGetDefaultInterShapePenaltyINTEL
  {IR(42565, 56), 646}, // 720 SubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL
  {IR(42464, 50), 644}, // 721 SubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL
  {IR(42159, 51), 638}, // 722 SubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL
  {IR(42368, 49), 642}, // 723 SubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL
  {IR(42316, 52), 641}, // 724 SubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL
  {IR(42514, 51), 645}, // 725 SubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL
  {IR(43253, 38), 662}, // 726 SubgroupAvcMceGetInterDirectionsINTEL
  {IR(43095, 39), 658}, // 727 SubgroupAvcMceGetInterDistortionsINTEL
  {IR(43177, 38), 660}, // 728 SubgroupAvcMceGetInterMajorShapeINTEL
  {IR(43215, 38), 661}, // 729 SubgroupAvcMceGetInterMinorShapeINTEL
  {IR(43291, 45), 663}, // 730 SubgroupAvcMceGetInterMotionVectorCountINTEL
  {IR(43336, 40), 664}, // 731 SubgroupAvcMceGetInterReferenceIdsINTEL
  {IR(43376, 62), 665}, // 732 SubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL
  {IR(43059, 36), 657}, // 733 SubgroupAvcMceGetMotionVectorsINTEL
  {IR(42621, 33), 647}, // 734 SubgroupAvcMceSetAcOnlyHaarINTEL
  {IR(42767, 61), 650}, // 735 SubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL
  {IR(41924, 53), 633}, // 736 SubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL
  {IR(42115, 44), 637}, // 737 SubgroupAvcMceSetInterDirectionPenaltyINTEL
  {IR(42024, 40), 635}, // 738 SubgroupAvcMceSetInterShapePenaltyINTEL
  {IR(42417, 47), 643}, // 739 SubgroupAvcMceSetMotionVectorCostFunctionINTEL
  {IR(42706, 61), 649}, // 740 SubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL
  {IR(42654, 52), 648}, // 741 SubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL
  {IR(45200, 39), 702}, // 742 SubgroupAvcRefConvertToMcePayloadINTEL
  {IR(45522, 38), 709}, // 743 SubgroupAvcRefConvertToMceResultINTEL
  {IR(45375, 45), 706}, // 744 SubgroupAvcRefEvaluateWithDualReferenceINTEL
  {IR(45420, 46), 707}, // 745 SubgroupAvcRefEvaluateWithMultiReferenceINTEL
  {IR(45466, 56), 708}, // 746 SubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL
  {IR(45328, 47), 705}, // 747 SubgroupAvcRefEvaluateWithSingleReferenceINTEL
  {IR(45239, 46), 703}, // 748 SubgroupAvcRefSetBidirectionalMixDisableINTEL
  {IR(45285, 43), 704}, // 749 SubgroupAvcRefSetBilinearFilterEnableINTEL
  {IR(45658, 42), 713}, // 750 SubgroupAvcSicConfigureIpeLumaChromaINTEL
  {IR(45622, 36), 712}, // 751 SubgroupAvcSicConfigureIpeLumaINTEL
  {IR(45590, 32), 711}, // 752 SubgroupAvcSicConfigureSkcINTEL
  {IR(45739, 39), 715}, // 753 SubgroupAvcSicConvertToMcePayloadINTEL
  {IR(46279, 38), 727}, // 754 SubgroupAvcSicConvertToMceResultINTEL
  {IR(46054, 31), 722}, // 755 SubgroupAvcSicEvaluateIpeINTEL
  {IR(46132, 45), 724}, // 756 SubgroupAvcSicEvaluateWithDualReferenceINTEL
  {IR(46177, 46), 725}, // 757 SubgroupAvcSicEvaluateWithMultiReferenceINTEL
  {IR(46223, 56), 726}, // 758 SubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL
  {IR(46085, 47), 723}, // 759 SubgroupAvcSicEvaluateWithSingleReferenceINTEL
  {IR(46396, 46), 730}, // 760 SubgroupAvcSicGetBestIpeChromaDistortionINTEL
  {IR(46352, 44), 729}, // 761 SubgroupAvcSicGetBestIpeLumaDistortionINTEL
  {IR(46617, 35), 735}, // 762 SubgroupAvcSicGetInterRawSadsINTEL
  {IR(46483, 36), 732}, // 763 SubgroupAvcSicGetIpeChromaModeINTEL
  {IR(46317, 35), 728}, // 764 SubgroupAvcSicGetIpeLumaShapeINTEL
  {IR(45700, 39), 714}, // 765 SubgroupAvcSicGetMotionVectorMaskINTEL
  {IR(46442, 41), 731}, // 766 SubgroupAvcSicGetPackedIpeLumaModesINTEL
  {IR(46519, 50), 733}, // 767 SubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL
  {IR(46569, 48), 734}, // 768 SubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL
  {IR(45560, 30), 710}, // 769 SubgroupAvcSicInitializeINTEL
  {IR(45920, 43), 719}, // 770 SubgroupAvcSicSetBilinearFilterEnableINTEL
  {IR(46011, 43), 721}, // 771 SubgroupAvcSicSetBlockBasedRawSkipSadINTEL
  {IR(45870, 50), 718}, // 772 SubgroupAvcSicSetIntraChromaModeCostFunctionINTEL
  {IR(45822, 48), 717}, // 773 SubgroupAvcSicSetIntraLumaModeCostFunctionINTEL
  {IR(45778, 44), 716}, // 774 SubgroupAvcSicSetIntraLumaShapePenaltyINTEL
  {IR(45963, 48), 720}, // 775 SubgroupAvcSicSetSkcForwardTransformEnableINTEL
  {IR(6278, 18), 363}, // 776 SubgroupBallotKHR
  {IR(49925, 27), 833}, // 777 SubgroupBlockPrefetchINTEL
  {IR(40870, 23), 587}, // 778 SubgroupBlockReadINTEL
  {IR(40893, 24), 588}, // 779 SubgroupBlockWriteINTEL
  {IR(34880, 27), 364}, // 780 SubgroupFirstInvocationKHR
  {IR(40917, 28), 589}, // 781 SubgroupImageBlockReadINTEL
  {IR(40945, 29), 590}, // 782 SubgroupImageBlockWriteINTEL
  {IR(40974, 33), 591}, // 783 SubgroupImageMediaBlockReadINTEL
  {IR(41007, 34), 592}, // 784 SubgroupImageMediaBlockWriteINTEL
  {IR(15384, 38), 839}, // 785 SubgroupMatrixMultiplyAccumulateINTEL
  {IR(35063, 26), 374}, // 786 SubgroupReadInvocationKHR
  {IR(40798, 25), 584}, // 787 SubgroupShuffleDownINTEL
  {IR(13040, 21), 583}, // 788 SubgroupShuffleINTEL
  {IR(40823, 23), 585}, // 789 SubgroupShuffleUpINTEL
  {IR(40846, 24), 586}, // 790 SubgroupShuffleXorINTEL
  {IR(32237, 7), 229}, // 791 Switch
  {IR(49739, 24), 829}, // 792 TaskSequenceAsyncALTERA
  {IR(49763, 23), 829}, // 793 TaskSequenceAsyncINTEL
  {IR(49690, 25), 828}, // 794 TaskSequenceCreateALTERA
  {IR(49715, 24), 828}, // 795 TaskSequenceCreateINTEL
  {IR(49786, 22), 830}, // 796 TaskSequenceGetALTERA
  {IR(49808, 21), 830}, // 797 TaskSequenceGetINTEL
  {IR(49829, 26), 831}, // 798 TaskSequenceReleaseALTERA
  {IR(49855, 25), 831}, // 799 TaskSequenceReleaseINTEL
  {IR(40141, 27), 560}, // 800 TensorLayoutSetBlockSizeNV
  {IR(40005, 28), 553}, // 801 TensorLayoutSetClampValueNV
  {IR(39934, 27), 550}, // 802 TensorLayoutSetDimensionNV
  {IR(39961, 24), 551}, // 803 TensorLayoutSetStrideNV
  {IR(39985, 20), 552}, // 804 TensorLayoutSliceNV
  {IR(34655, 19), 350}, // 805 TensorQuerySizeARM
  {IR(34626, 14), 348}, // 806 TensorReadARM
  {IR(40121, 20), 559}, // 807 TensorViewSetClipNV
  {IR(40052, 25), 555}, // 808 TensorViewSetDimensionNV
  {IR(40077, 22), 556}, // 809 TensorViewSetStrideNV
  {IR(34640, 15), 349}, // 810 TensorWriteARM
  {IR(34767, 20), 358}, // 811 TerminateInvocation
  {IR(35228, 16), 381}, // 812 TerminateRayKHR
  {IR(39035, 15), 521}, // 813 TerminateRayNV
  {IR(39058, 14), 523}, // 814 TraceMotionNV
  {IR(39050, 8), 522}, // 815 TraceNV
  {IR(35140, 12), 377}, // 816 TraceRayKHR
  {IR(39072, 17), 524}, // 817 TraceRayMotionNV
  {IR(30089, 10), 76}, // 818 Transpose
  {IR(39139, 29), 526}, // 819 TypeAccelerationStructureKHR
  {IR(39168, 28), 526}, // 820 TypeAccelerationStructureNV
  {IR(29038, 10), 25}, // 821 TypeArray
  {IR(41783, 37), 629}, // 822 TypeAvcImeDualReferenceStreaminINTEL
  {IR(41518, 23), 620}, // 823 TypeAvcImePayloadINTEL
  {IR(41700, 44), 627}, // 824 TypeAvcImeResultDualReferenceStreamoutINTEL
  {IR(41632, 22), 625}, // 825 TypeAvcImeResultINTEL
  {IR(41654, 46), 626}, // 826 TypeAvcImeResultSingleReferenceStreamoutINTEL
  {IR(41744, 39), 628}, // 827 TypeAvcImeSingleReferenceStreaminINTEL
  {IR(41587, 23), 623}, // 828 TypeAvcMcePayloadINTEL
  {IR(41610, 22), 624}, // 829 TypeAvcMceResultINTEL
  {IR(41541, 23), 621}, // 830 TypeAvcRefPayloadINTEL
  {IR(41820, 22), 630}, // 831 TypeAvcRefResultINTEL
  {IR(41564, 23), 622}, // 832 TypeAvcSicPayloadINTEL
  {IR(41842, 22), 631}, // 833 TypeAvcSicResultINTEL
  {IR(28800, 9), 17}, // 834 TypeBool
  {IR(36642, 14), 436}, // 835 TypeBufferEXT
  {IR(49451, 23), 818}, // 836 TypeBufferSurfaceINTEL
  {IR(35409, 25), 388}, // 837 TypeCooperativeMatrixKHR
  {IR(39461, 24), 536}, // 838 TypeCooperativeMatrixNV
  {IR(37655, 24), 475}, // 839 TypeCooperativeVectorNV
  {IR(29153, 16), 32}, // 840 TypeDeviceEvent
  {IR(29143, 10), 31}, // 841 TypeEvent
  {IR(28854, 10), 19}, // 842 TypeFloat
  {IR(29202, 19), 36}, // 843 TypeForwardPointer
  {IR(29130, 13), 30}, // 844 TypeFunction
  {IR(34754, 13), 357}, // 845 TypeGraphARM
  {IR(38396, 17), 498}, // 846 TypeHitObjectEXT
  {IR(37600, 16), 473}, // 847 TypeHitObjectNV
  {IR(28999, 10), 22}, // 848 TypeImage
  {IR(28809, 8), 18}, // 849 TypeInt
  {IR(28875, 11), 21}, // 850 TypeMatrix
  {IR(33584, 17), 300}, // 851 TypeNamedBarrier
  {IR(36444, 25), 428}, // 852 TypeNodePayloadArrayAMDX
  {IR(29076, 11), 28}, // 853 TypeOpaque
  {IR(29193, 9), 35}, // 854 TypePipe
  {IR(33462, 16), 295}, // 855 TypePipeStorage
  {IR(29118, 12), 29}, // 856 TypePointer
  {IR(29183, 10), 34}, // 857 TypeQueue
  {IR(35688, 16), 396}, // 858 TypeRayQueryKHR
  {IR(29169, 14), 33}, // 859 TypeReserveId
  {IR(29048, 17), 26}, // 860 TypeRuntimeArray
  {IR(29021, 17), 24}, // 861 TypeSampledImage
  {IR(29009, 12), 23}, // 862 TypeSampler
  {IR(29065, 11), 27}, // 863 TypeStruct
  {IR(49474, 25), 819}, // 864 TypeStructContinuedINTEL
  {IR(49880, 23), 832}, // 865 TypeTaskSequenceALTERA
  {IR(49903, 22), 832}, // 866 TypeTaskSequenceINTEL
  {IR(34570, 14), 347}, // 867 TypeTensorARM
  {IR(39877, 19), 547}, // 868 TypeTensorLayoutNV
  {IR(39896, 17), 548}, // 869 TypeTensorViewNV
  {IR(34787, 22), 359}, // 870 TypeUntypedPointerKHR
  {IR(28864, 11), 20}, // 871 TypeVector
  {IR(37639, 16), 475}, // 872 TypeVectorIdEXT
  {IR(41500, 18), 619}, // 873 TypeVmeImageINTEL
  {IR(28791, 9), 16}, // 874 TypeVoid
  {IR(41129, 13), 598}, // 875 UAddSatINTEL
  {IR(41156, 14), 600}, // 876 UAverageINTEL
  {IR(41191, 21), 602}, // 877 UAverageRoundedINTEL
  {IR(30606, 9), 103}, // 878 UConvert
  {IR(41041, 24), 593}, // 879 UCountLeadingZerosINTEL
  {IR(41065, 25), 594}, // 880 UCountTrailingZerosINTEL
  {IR(30818, 5), 123}, // 881 UDiv
  {IR(35304, 5), 383}, // 882 UDot
  {IR(35357, 11), 386}, // 883 UDotAccSat
  {IR(35368, 14), 386}, // 884 UDotAccSatKHR
  {IR(35309, 8), 383}, // 885 UDotKHR
  {IR(31178, 13), 160}, // 886 UGreaterThan
  {IR(31204, 18), 162}, // 887 UGreaterThanEqual
  {IR(31240, 10), 164}, // 888 ULessThan
  {IR(31260, 15), 166}, // 889 ULessThanEqual
  {IR(30833, 5), 126}, // 890 UMod
  {IR(41253, 15), 606}, // 891 UMul32x16INTEL
  {IR(30986, 13), 140}, // 892 UMulExtended
  {IR(41225, 13), 604}, // 893 USubSatINTEL
  {IR(28303, 6), 1}, // 894 Undef
  {IR(31083, 10), 151}, // 895 Unordered
  {IR(32268, 12), 233}, // 896 Unreachable
  {IR(34828, 22), 361}, // 897 UntypedAccessChainKHR
  {IR(34965, 22), 367}, // 898 UntypedArrayLengthKHR
  {IR(35115, 25), 376}, // 899 UntypedGroupAsyncCopyKHR
  {IR(36673, 28), 438}, // 900 UntypedImageTexelPointerEXT
  {IR(34850, 30), 362}, // 901 UntypedInBoundsAccessChainKHR
  {IR(34932, 33), 366}, // 902 UntypedInBoundsPtrAccessChainKHR
  {IR(34987, 19), 368}, // 903 UntypedPrefetchKHR
  {IR(34907, 25), 365}, // 904 UntypedPtrAccessChainKHR
  {IR(34809, 19), 360}, // 905 UntypedVariableKHR
  {IR(15450, 32), 841}, // 906 UntypedVariableLengthArrayINTEL
  {IR(29614, 9), 52}, // 907 Variable
  {IR(13496, 25), 736}, // 908 VariableLengthArrayINTEL
  {IR(29971, 21), 69}, // 909 VectorExtractDynamic
  {IR(29992, 20), 70}, // 910 VectorInsertDynamic
  {IR(30012, 14), 71}, // 911 VectorShuffle
  {IR(30894, 18), 133}, // 912 VectorTimesMatrix
  {IR(30858, 18), 131}, // 913 VectorTimesScalar
  {IR(41486, 14), 618}, // 914 VmeImageINTEL
  {IR(37938, 33), 484}, // 915 WritePackedPrimitiveIndices4x8NV
  {IR(32493, 10), 250}, // 916 WritePipe
  {IR(48739, 24), 798}, // 917 WritePipeBlockingALTERA
  {IR(48763, 23), 798}, // 918 WritePipeBlockingINTEL
}};

// Extended instruction descriptions, ordered by (extinst enum, opcode value).
// The fields in order are:
//   enum value
//   operands, an IndexRange into kOperandSpans
//   name, a character-counting IndexRange into kStrings
//   capabilities, an IndexRange into kCapabilitySpans
static const std::array<ExtInstDesc, 425> kExtInstByValue{{
    {0,IR(0, 0),IR(50748, 14),IR(1, 0)}, // DebugInfoNone in debuginfo
    {1,IR(52, 3),IR(50762, 21),IR(1, 0)}, // DebugCompilationUnit in debuginfo
    {2,IR(803, 3),IR(50835, 15),IR(1, 0)}, // DebugTypeBasic in debuginfo
    {3,IR(806, 3),IR(50884, 17),IR(1, 0)}, // DebugTypePointer in debuginfo
    {4,IR(809, 2),IR(50939, 19),IR(1, 0)}, // DebugTypeQualifier in debuginfo
    {5,IR(168, 2),IR(50958, 15),IR(1, 0)}, // DebugTypeArray in debuginfo
    {6,IR(261, 2),IR(50973, 16),IR(1, 0)}, // DebugTypeVector in debuginfo
    {7,IR(811, 6),IR(50989, 13),IR(1, 0)}, // DebugTypedef in debuginfo
    {8,IR(168, 2),IR(51002, 18),IR(1, 0)}, // DebugTypeFunction in debuginfo
    {9,IR(817, 9),IR(51020, 14),IR(1, 0)}, // DebugTypeEnum in debuginfo
    {10,IR(826, 9),IR(51072, 19),IR(1, 0)}, // DebugTypeComposite in debuginfo
    {11,IR(835, 10),IR(51091, 16),IR(1, 0)}, // DebugTypeMember in debuginfo
    {12,IR(845, 5),IR(51107, 21),IR(1, 0)}, // DebugTypeInheritance in debuginfo
    {13,IR(36, 2),IR(51128, 21),IR(1, 0)}, // DebugTypePtrToMember in debuginfo
    {14,IR(168, 2),IR(51149, 18),IR(1, 0)}, // DebugTypeTemplate in debuginfo
    {15,IR(850, 6),IR(51167, 27),IR(1, 0)}, // DebugTypeTemplateParameter in debuginfo
    {16,IR(856, 5),IR(51194, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in debuginfo
    {17,IR(861, 5),IR(51229, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in debuginfo
    {18,IR(835, 10),IR(51260, 20),IR(1, 0)}, // DebugGlobalVariable in debuginfo
    {19,IR(866, 8),IR(51280, 25),IR(1, 0)}, // DebugFunctionDeclaration in debuginfo
    {20,IR(874, 11),IR(51305, 14),IR(1, 0)}, // DebugFunction in debuginfo
    {21,IR(885, 5),IR(51319, 18),IR(1, 0)}, // DebugLexicalBlock in debuginfo
    {22,IR(890, 3),IR(51337, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in debuginfo
    {23,IR(893, 2),IR(51368, 11),IR(1, 0)}, // DebugScope in debuginfo
    {24,IR(0, 0),IR(51379, 13),IR(1, 0)}, // DebugNoScope in debuginfo
    {25,IR(895, 3),IR(51392, 15),IR(1, 0)}, // DebugInlinedAt in debuginfo
    {26,IR(898, 7),IR(51449, 19),IR(1, 0)}, // DebugLocalVariable in debuginfo
    {27,IR(36, 2),IR(51468, 21),IR(1, 0)}, // DebugInlinedVariable in debuginfo
    {28,IR(33, 3),IR(51489, 13),IR(1, 0)}, // DebugDeclare in debuginfo
    {29,IR(375, 3),IR(51502, 11),IR(1, 0)}, // DebugValue in debuginfo
    {30,IR(905, 2),IR(51546, 15),IR(1, 0)}, // DebugOperation in debuginfo
    {31,IR(739, 1),IR(51561, 16),IR(1, 0)}, // DebugExpression in debuginfo
    {32,IR(907, 4),IR(51577, 14),IR(1, 0)}, // DebugMacroDef in debuginfo
    {33,IR(890, 3),IR(51591, 16),IR(1, 0)}, // DebugMacroUndef in debuginfo
    {1,IR(10, 1),IR(51607, 6),IR(1, 0)}, // Round in glsl_std_450
    {2,IR(10, 1),IR(51613, 10),IR(1, 0)}, // RoundEven in glsl_std_450
    {3,IR(10, 1),IR(51623, 6),IR(1, 0)}, // Trunc in glsl_std_450
    {4,IR(10, 1),IR(51629, 5),IR(1, 0)}, // FAbs in glsl_std_450
    {5,IR(10, 1),IR(51634, 5),IR(1, 0)}, // SAbs in glsl_std_450
    {6,IR(10, 1),IR(51639, 6),IR(1, 0)}, // FSign in glsl_std_450
    {7,IR(10, 1),IR(51645, 6),IR(1, 0)}, // SSign in glsl_std_450
    {8,IR(10, 1),IR(51651, 6),IR(1, 0)}, // Floor in glsl_std_450
    {9,IR(10, 1),IR(51657, 5),IR(1, 0)}, // Ceil in glsl_std_450
    {10,IR(10, 1),IR(51662, 6),IR(1, 0)}, // Fract in glsl_std_450
    {11,IR(10, 1),IR(51668, 8),IR(1, 0)}, // Radians in glsl_std_450
    {12,IR(10, 1),IR(51676, 8),IR(1, 0)}, // Degrees in glsl_std_450
    {13,IR(10, 1),IR(51684, 4),IR(1, 0)}, // Sin in glsl_std_450
    {14,IR(10, 1),IR(51688, 4),IR(1, 0)}, // Cos in glsl_std_450
    {15,IR(10, 1),IR(51692, 4),IR(1, 0)}, // Tan in glsl_std_450
    {16,IR(10, 1),IR(51696, 5),IR(1, 0)}, // Asin in glsl_std_450
    {17,IR(10, 1),IR(51701, 5),IR(1, 0)}, // Acos in glsl_std_450
    {18,IR(10, 1),IR(51706, 5),IR(1, 0)}, // Atan in glsl_std_450
    {19,IR(10, 1),IR(51711, 5),IR(1, 0)}, // Sinh in glsl_std_450
    {20,IR(10, 1),IR(51716, 5),IR(1, 0)}, // Cosh in glsl_std_450
    {21,IR(10, 1),IR(51721, 5),IR(1, 0)}, // Tanh in glsl_std_450
    {22,IR(10, 1),IR(51726, 6),IR(1, 0)}, // Asinh in glsl_std_450
    {23,IR(10, 1),IR(51732, 6),IR(1, 0)}, // Acosh in glsl_std_450
    {24,IR(10, 1),IR(51738, 6),IR(1, 0)}, // Atanh in glsl_std_450
    {25,IR(36, 2),IR(51744, 6),IR(1, 0)}, // Atan2 in glsl_std_450
    {26,IR(36, 2),IR(51750, 4),IR(1, 0)}, // Pow in glsl_std_450
    {27,IR(10, 1),IR(51754, 4),IR(1, 0)}, // Exp in glsl_std_450
    {28,IR(10, 1),IR(51758, 4),IR(1, 0)}, // Log in glsl_std_450
    {29,IR(10, 1),IR(51762, 5),IR(1, 0)}, // Exp2 in glsl_std_450
    {30,IR(10, 1),IR(51767, 5),IR(1, 0)}, // Log2 in glsl_std_450
    {31,IR(10, 1),IR(51772, 5),IR(1, 0)}, // Sqrt in glsl_std_450
    {32,IR(10, 1),IR(51777, 12),IR(1, 0)}, // InverseSqrt in glsl_std_450
    {33,IR(10, 1),IR(51789, 12),IR(1, 0)}, // Determinant in glsl_std_450
    {34,IR(10, 1),IR(51801, 14),IR(1, 0)}, // MatrixInverse in glsl_std_450
    {35,IR(36, 2),IR(51815, 5),IR(1, 0)}, // Modf in glsl_std_450
    {36,IR(10, 1),IR(51820, 11),IR(1, 0)}, // ModfStruct in glsl_std_450
    {37,IR(36, 2),IR(51831, 5),IR(1, 0)}, // FMin in glsl_std_450
    {38,IR(36, 2),IR(51836, 5),IR(1, 0)}, // UMin in glsl_std_450
    {39,IR(36, 2),IR(51841, 5),IR(1, 0)}, // SMin in glsl_std_450
    {40,IR(36, 2),IR(51846, 5),IR(1, 0)}, // FMax in glsl_std_450
    {41,IR(36, 2),IR(51851, 5),IR(1, 0)}, // UMax in glsl_std_450
    {42,IR(36, 2),IR(51856, 5),IR(1, 0)}, // SMax in glsl_std_450
    {43,IR(33, 3),IR(51861, 7),IR(1, 0)}, // FClamp in glsl_std_450
    {44,IR(33, 3),IR(51868, 7),IR(1, 0)}, // UClamp in glsl_std_450
    {45,IR(33, 3),IR(51875, 7),IR(1, 0)}, // SClamp in glsl_std_450
    {46,IR(33, 3),IR(51882, 5),IR(1, 0)}, // FMix in glsl_std_450
    {47,IR(33, 3),IR(51887, 5),IR(1, 0)}, // IMix in glsl_std_450
    {48,IR(36, 2),IR(51892, 5),IR(1, 0)}, // Step in glsl_std_450
    {49,IR(33, 3),IR(51897, 11),IR(1, 0)}, // SmoothStep in glsl_std_450
    {50,IR(33, 3),IR(51908, 4),IR(1, 0)}, // Fma in glsl_std_450
    {51,IR(36, 2),IR(51912, 6),IR(1, 0)}, // Frexp in glsl_std_450
    {52,IR(10, 1),IR(51918, 12),IR(1, 0)}, // FrexpStruct in glsl_std_450
    {53,IR(36, 2),IR(51930, 6),IR(1, 0)}, // Ldexp in glsl_std_450
    {54,IR(10, 1),IR(51936, 13),IR(1, 0)}, // PackSnorm4x8 in glsl_std_450
    {55,IR(10, 1),IR(51949, 13),IR(1, 0)}, // PackUnorm4x8 in glsl_std_450
    {56,IR(10, 1),IR(51962, 14),IR(1, 0)}, // PackSnorm2x16 in glsl_std_450
    {57,IR(10, 1),IR(51976, 14),IR(1, 0)}, // PackUnorm2x16 in glsl_std_450
    {58,IR(10, 1),IR(51990, 13),IR(1, 0)}, // PackHalf2x16 in glsl_std_450
    {59,IR(10, 1),IR(52003, 15),IR(325, 1)}, // PackDouble2x32 in glsl_std_450
    {60,IR(10, 1),IR(52018, 16),IR(1, 0)}, // UnpackSnorm2x16 in glsl_std_450
    {61,IR(10, 1),IR(52034, 16),IR(1, 0)}, // UnpackUnorm2x16 in glsl_std_450
    {62,IR(10, 1),IR(52050, 15),IR(1, 0)}, // UnpackHalf2x16 in glsl_std_450
    {63,IR(10, 1),IR(52065, 15),IR(1, 0)}, // UnpackSnorm4x8 in glsl_std_450
    {64,IR(10, 1),IR(52080, 15),IR(1, 0)}, // UnpackUnorm4x8 in glsl_std_450
    {65,IR(10, 1),IR(52095, 17),IR(325, 1)}, // UnpackDouble2x32 in glsl_std_450
    {66,IR(10, 1),IR(52112, 7),IR(1, 0)}, // Length in glsl_std_450
    {67,IR(36, 2),IR(52119, 9),IR(1, 0)}, // Distance in glsl_std_450
    {68,IR(36, 2),IR(52128, 6),IR(1, 0)}, // Cross in glsl_std_450
    {69,IR(10, 1),IR(52134, 10),IR(1, 0)}, // Normalize in glsl_std_450
    {70,IR(33, 3),IR(52144, 12),IR(1, 0)}, // FaceForward in glsl_std_450
    {71,IR(36, 2),IR(52156, 8),IR(1, 0)}, // Reflect in glsl_std_450
    {72,IR(33, 3),IR(52164, 8),IR(1, 0)}, // Refract in glsl_std_450
    {73,IR(10, 1),IR(52172, 9),IR(1, 0)}, // FindILsb in glsl_std_450
    {74,IR(10, 1),IR(52181, 9),IR(1, 0)}, // FindSMsb in glsl_std_450
    {75,IR(10, 1),IR(52190, 9),IR(1, 0)}, // FindUMsb in glsl_std_450
    {76,IR(10, 1),IR(52199, 22),IR(326, 1)}, // InterpolateAtCentroid in glsl_std_450
    {77,IR(36, 2),IR(52221, 20),IR(326, 1)}, // InterpolateAtSample in glsl_std_450
    {78,IR(36, 2),IR(52241, 20),IR(326, 1)}, // InterpolateAtOffset in glsl_std_450
    {79,IR(36, 2),IR(52261, 5),IR(1, 0)}, // NMin in glsl_std_450
    {80,IR(36, 2),IR(52266, 5),IR(1, 0)}, // NMax in glsl_std_450
    {81,IR(33, 3),IR(52271, 7),IR(1, 0)}, // NClamp in glsl_std_450
    {1,IR(399, 5),IR(5497, 7),IR(1, 0)}, // Kernel in nonsemantic_clspvreflection
    {2,IR(911, 5),IR(52278, 13),IR(1, 0)}, // ArgumentInfo in nonsemantic_clspvreflection
    {3,IR(916, 5),IR(52291, 22),IR(1, 0)}, // ArgumentStorageBuffer in nonsemantic_clspvreflection
    {4,IR(916, 5),IR(52313, 16),IR(1, 0)}, // ArgumentUniform in nonsemantic_clspvreflection
    {5,IR(554, 7),IR(52329, 25),IR(1, 0)}, // ArgumentPodStorageBuffer in nonsemantic_clspvreflection
    {6,IR(554, 7),IR(52354, 19),IR(1, 0)}, // ArgumentPodUniform in nonsemantic_clspvreflection
    {7,IR(916, 5),IR(52373, 24),IR(1, 0)}, // ArgumentPodPushConstant in nonsemantic_clspvreflection
    {8,IR(916, 5),IR(52397, 21),IR(1, 0)}, // ArgumentSampledImage in nonsemantic_clspvreflection
    {9,IR(916, 5),IR(52418, 21),IR(1, 0)}, // ArgumentStorageImage in nonsemantic_clspvreflection
    {10,IR(916, 5),IR(52439, 16),IR(1, 0)}, // ArgumentSampler in nonsemantic_clspvreflection
    {11,IR(916, 5),IR(52455, 18),IR(1, 0)}, // ArgumentWorkgroup in nonsemantic_clspvreflection
    {12,IR(33, 3),IR(52473, 26),IR(1, 0)}, // SpecConstantWorkgroupSize in nonsemantic_clspvreflection
    {13,IR(33, 3),IR(52499, 25),IR(1, 0)}, // SpecConstantGlobalOffset in nonsemantic_clspvreflection
    {14,IR(10, 1),IR(52524, 20),IR(1, 0)}, // SpecConstantWorkDim in nonsemantic_clspvreflection
    {15,IR(36, 2),IR(52544, 25),IR(1, 0)}, // PushConstantGlobalOffset in nonsemantic_clspvreflection
    {16,IR(36, 2),IR(52569, 30),IR(1, 0)}, // PushConstantEnqueuedLocalSize in nonsemantic_clspvreflection
    {17,IR(36, 2),IR(52599, 23),IR(1, 0)}, // PushConstantGlobalSize in nonsemantic_clspvreflection
    {18,IR(36, 2),IR(52622, 25),IR(1, 0)}, // PushConstantRegionOffset in nonsemantic_clspvreflection
    {19,IR(36, 2),IR(52647, 26),IR(1, 0)}, // PushConstantNumWorkgroups in nonsemantic_clspvreflection
    {20,IR(36, 2),IR(52673, 30),IR(1, 0)}, // PushConstantRegionGroupOffset in nonsemantic_clspvreflection
    {21,IR(33, 3),IR(52703, 26),IR(1, 0)}, // ConstantDataStorageBuffer in nonsemantic_clspvreflection
    {22,IR(33, 3),IR(52729, 20),IR(1, 0)}, // ConstantDataUniform in nonsemantic_clspvreflection
    {23,IR(33, 3),IR(8971, 15),IR(1, 0)}, // LiteralSampler in nonsemantic_clspvreflection
    {24,IR(296, 4),IR(52749, 30),IR(1, 0)}, // PropertyRequiredWorkgroupSize in nonsemantic_clspvreflection
    {25,IR(10, 1),IR(52779, 28),IR(1, 0)}, // SpecConstantSubgroupMaxSize in nonsemantic_clspvreflection
    {26,IR(916, 5),IR(52807, 28),IR(1, 0)}, // ArgumentPointerPushConstant in nonsemantic_clspvreflection
    {27,IR(554, 7),IR(52835, 23),IR(1, 0)}, // ArgumentPointerUniform in nonsemantic_clspvreflection
    {28,IR(33, 3),IR(52858, 35),IR(1, 0)}, // ProgramScopeVariablesStorageBuffer in nonsemantic_clspvreflection
    {29,IR(33, 3),IR(52893, 38),IR(1, 0)}, // ProgramScopeVariablePointerRelocation in nonsemantic_clspvreflection
    {30,IR(296, 4),IR(52931, 42),IR(1, 0)}, // ImageArgumentInfoChannelOrderPushConstant in nonsemantic_clspvreflection
    {31,IR(296, 4),IR(52973, 45),IR(1, 0)}, // ImageArgumentInfoChannelDataTypePushConstant in nonsemantic_clspvreflection
    {32,IR(525, 6),IR(53018, 37),IR(1, 0)}, // ImageArgumentInfoChannelOrderUniform in nonsemantic_clspvreflection
    {33,IR(525, 6),IR(53055, 40),IR(1, 0)}, // ImageArgumentInfoChannelDataTypeUniform in nonsemantic_clspvreflection
    {34,IR(916, 5),IR(53095, 27),IR(1, 0)}, // ArgumentStorageTexelBuffer in nonsemantic_clspvreflection
    {35,IR(916, 5),IR(53122, 27),IR(1, 0)}, // ArgumentUniformTexelBuffer in nonsemantic_clspvreflection
    {36,IR(33, 3),IR(53149, 32),IR(1, 0)}, // ConstantDataPointerPushConstant in nonsemantic_clspvreflection
    {37,IR(33, 3),IR(53181, 40),IR(1, 0)}, // ProgramScopeVariablePointerPushConstant in nonsemantic_clspvreflection
    {38,IR(375, 3),IR(53221, 11),IR(1, 0)}, // PrintfInfo in nonsemantic_clspvreflection
    {39,IR(33, 3),IR(53232, 26),IR(1, 0)}, // PrintfBufferStorageBuffer in nonsemantic_clspvreflection
    {40,IR(33, 3),IR(53258, 32),IR(1, 0)}, // PrintfBufferPointerPushConstant in nonsemantic_clspvreflection
    {41,IR(296, 4),IR(53290, 34),IR(1, 0)}, // NormalizedSamplerMaskPushConstant in nonsemantic_clspvreflection
    {42,IR(36, 2),IR(53324, 22),IR(1, 0)}, // WorkgroupVariableSize in nonsemantic_clspvreflection
    {0,IR(0, 0),IR(50748, 14),IR(1, 0)}, // DebugInfoNone in nonsemantic_shader_debuginfo_100
    {1,IR(296, 4),IR(50762, 21),IR(1, 0)}, // DebugCompilationUnit in nonsemantic_shader_debuginfo_100
    {2,IR(296, 4),IR(50835, 15),IR(1, 0)}, // DebugTypeBasic in nonsemantic_shader_debuginfo_100
    {3,IR(33, 3),IR(50884, 17),IR(1, 0)}, // DebugTypePointer in nonsemantic_shader_debuginfo_100
    {4,IR(36, 2),IR(50939, 19),IR(1, 0)}, // DebugTypeQualifier in nonsemantic_shader_debuginfo_100
    {5,IR(168, 2),IR(50958, 15),IR(1, 0)}, // DebugTypeArray in nonsemantic_shader_debuginfo_100
    {6,IR(36, 2),IR(50973, 16),IR(1, 0)}, // DebugTypeVector in nonsemantic_shader_debuginfo_100
    {7,IR(525, 6),IR(50989, 13),IR(1, 0)}, // DebugTypedef in nonsemantic_shader_debuginfo_100
    {8,IR(375, 3),IR(51002, 18),IR(1, 0)}, // DebugTypeFunction in nonsemantic_shader_debuginfo_100
    {9,IR(921, 9),IR(51020, 14),IR(1, 0)}, // DebugTypeEnum in nonsemantic_shader_debuginfo_100
    {10,IR(930, 10),IR(51072, 19),IR(1, 0)}, // DebugTypeComposite in nonsemantic_shader_debuginfo_100
    {11,IR(940, 9),IR(51091, 16),IR(1, 0)}, // DebugTypeMember in nonsemantic_shader_debuginfo_100
    {12,IR(296, 4),IR(51107, 21),IR(1, 0)}, // DebugTypeInheritance in nonsemantic_shader_debuginfo_100
    {13,IR(36, 2),IR(51128, 21),IR(1, 0)}, // DebugTypePtrToMember in nonsemantic_shader_debuginfo_100
    {14,IR(168, 2),IR(51149, 18),IR(1, 0)}, // DebugTypeTemplate in nonsemantic_shader_debuginfo_100
    {15,IR(525, 6),IR(51167, 27),IR(1, 0)}, // DebugTypeTemplateParameter in nonsemantic_shader_debuginfo_100
    {16,IR(667, 5),IR(51194, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in nonsemantic_shader_debuginfo_100
    {17,IR(949, 5),IR(51229, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in nonsemantic_shader_debuginfo_100
    {18,IR(954, 10),IR(51260, 20),IR(1, 0)}, // DebugGlobalVariable in nonsemantic_shader_debuginfo_100
    {19,IR(471, 8),IR(51280, 25),IR(1, 0)}, // DebugFunctionDeclaration in nonsemantic_shader_debuginfo_100
    {20,IR(954, 10),IR(51305, 14),IR(1, 0)}, // DebugFunction in nonsemantic_shader_debuginfo_100
    {21,IR(916, 5),IR(51319, 18),IR(1, 0)}, // DebugLexicalBlock in nonsemantic_shader_debuginfo_100
    {22,IR(33, 3),IR(51337, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in nonsemantic_shader_debuginfo_100
    {23,IR(893, 2),IR(51368, 11),IR(1, 0)}, // DebugScope in nonsemantic_shader_debuginfo_100
    {24,IR(0, 0),IR(51379, 13),IR(1, 0)}, // DebugNoScope in nonsemantic_shader_debuginfo_100
    {25,IR(964, 3),IR(51392, 15),IR(1, 0)}, // DebugInlinedAt in nonsemantic_shader_debuginfo_100
    {26,IR(967, 8),IR(51449, 19),IR(1, 0)}, // DebugLocalVariable in nonsemantic_shader_debuginfo_100
    {27,IR(36, 2),IR(51468, 21),IR(1, 0)}, // DebugInlinedVariable in nonsemantic_shader_debuginfo_100
    {28,IR(975, 4),IR(51489, 13),IR(1, 0)}, // DebugDeclare in nonsemantic_shader_debuginfo_100
    {29,IR(975, 4),IR(51502, 11),IR(1, 0)}, // DebugValue in nonsemantic_shader_debuginfo_100
    {30,IR(168, 2),IR(51546, 15),IR(1, 0)}, // DebugOperation in nonsemantic_shader_debuginfo_100
    {31,IR(739, 1),IR(51561, 16),IR(1, 0)}, // DebugExpression in nonsemantic_shader_debuginfo_100
    {32,IR(577, 4),IR(51577, 14),IR(1, 0)}, // DebugMacroDef in nonsemantic_shader_debuginfo_100
    {33,IR(33, 3),IR(51591, 16),IR(1, 0)}, // DebugMacroUndef in nonsemantic_shader_debuginfo_100
    {34,IR(506, 7),IR(53346, 20),IR(1, 0)}, // DebugImportedEntity in nonsemantic_shader_debuginfo_100
    {35,IR(893, 2),IR(53366, 12),IR(1, 0)}, // DebugSource in nonsemantic_shader_debuginfo_100
    {101,IR(36, 2),IR(53378, 24),IR(1, 0)}, // DebugFunctionDefinition in nonsemantic_shader_debuginfo_100
    {102,IR(10, 1),IR(53402, 21),IR(1, 0)}, // DebugSourceContinued in nonsemantic_shader_debuginfo_100
    {103,IR(667, 5),IR(53423, 10),IR(1, 0)}, // DebugLine in nonsemantic_shader_debuginfo_100
    {104,IR(0, 0),IR(53433, 12),IR(1, 0)}, // DebugNoLine in nonsemantic_shader_debuginfo_100
    {105,IR(36, 2),IR(53445, 21),IR(1, 0)}, // DebugBuildIdentifier in nonsemantic_shader_debuginfo_100
    {106,IR(10, 1),IR(53466, 17),IR(1, 0)}, // DebugStoragePath in nonsemantic_shader_debuginfo_100
    {107,IR(296, 4),IR(53483, 16),IR(1, 0)}, // DebugEntryPoint in nonsemantic_shader_debuginfo_100
    {108,IR(33, 3),IR(53499, 16),IR(1, 0)}, // DebugTypeMatrix in nonsemantic_shader_debuginfo_100
    {1,IR(757, 9),IR(53515, 14),IR(1, 0)}, // Configuration in nonsemantic_vkspreflection
    {2,IR(10, 1),IR(53529, 13),IR(1, 0)}, // StartCounter in nonsemantic_vkspreflection
    {3,IR(10, 1),IR(53542, 12),IR(1, 0)}, // StopCounter in nonsemantic_vkspreflection
    {4,IR(296, 4),IR(53554, 14),IR(1, 0)}, // PushConstants in nonsemantic_vkspreflection
    {5,IR(33, 3),IR(53568, 23),IR(1, 0)}, // SpecializationMapEntry in nonsemantic_vkspreflection
    {6,IR(979, 15),IR(53591, 20),IR(1, 0)}, // DescriptorSetBuffer in nonsemantic_vkspreflection
    {7,IR(994, 33),IR(53611, 19),IR(1, 0)}, // DescriptorSetImage in nonsemantic_vkspreflection
    {8,IR(1027, 19),IR(53630, 21),IR(1, 0)}, // DescriptorSetSampler in nonsemantic_vkspreflection
    {0,IR(0, 0),IR(50748, 14),IR(1, 0)}, // DebugInfoNone in opencl_debuginfo_100
    {1,IR(1046, 4),IR(50762, 21),IR(1, 0)}, // DebugCompilationUnit in opencl_debuginfo_100
    {2,IR(1050, 3),IR(50835, 15),IR(1, 0)}, // DebugTypeBasic in opencl_debuginfo_100
    {3,IR(1053, 3),IR(50884, 17),IR(1, 0)}, // DebugTypePointer in opencl_debuginfo_100
    {4,IR(1056, 2),IR(50939, 19),IR(1, 0)}, // DebugTypeQualifier in opencl_debuginfo_100
    {5,IR(168, 2),IR(50958, 15),IR(1, 0)}, // DebugTypeArray in opencl_debuginfo_100
    {6,IR(261, 2),IR(50973, 16),IR(1, 0)}, // DebugTypeVector in opencl_debuginfo_100
    {7,IR(811, 6),IR(50989, 13),IR(1, 0)}, // DebugTypedef in opencl_debuginfo_100
    {8,IR(1058, 3),IR(51002, 18),IR(1, 0)}, // DebugTypeFunction in opencl_debuginfo_100
    {9,IR(1061, 9),IR(51020, 14),IR(1, 0)}, // DebugTypeEnum in opencl_debuginfo_100
    {10,IR(1070, 10),IR(51072, 19),IR(1, 0)}, // DebugTypeComposite in opencl_debuginfo_100
    {11,IR(1080, 10),IR(51091, 16),IR(1, 0)}, // DebugTypeMember in opencl_debuginfo_100
    {12,IR(1090, 5),IR(51107, 21),IR(1, 0)}, // DebugTypeInheritance in opencl_debuginfo_100
    {13,IR(36, 2),IR(51128, 21),IR(1, 0)}, // DebugTypePtrToMember in opencl_debuginfo_100
    {14,IR(168, 2),IR(51149, 18),IR(1, 0)}, // DebugTypeTemplate in opencl_debuginfo_100
    {15,IR(850, 6),IR(51167, 27),IR(1, 0)}, // DebugTypeTemplateParameter in opencl_debuginfo_100
    {16,IR(856, 5),IR(51194, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in opencl_debuginfo_100
    {17,IR(861, 5),IR(51229, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in opencl_debuginfo_100
    {18,IR(1080, 10),IR(51260, 20),IR(1, 0)}, // DebugGlobalVariable in opencl_debuginfo_100
    {19,IR(1095, 8),IR(51280, 25),IR(1, 0)}, // DebugFunctionDeclaration in opencl_debuginfo_100
    {20,IR(1103, 11),IR(51305, 14),IR(1, 0)}, // DebugFunction in opencl_debuginfo_100
    {21,IR(885, 5),IR(51319, 18),IR(1, 0)}, // DebugLexicalBlock in opencl_debuginfo_100
    {22,IR(890, 3),IR(51337, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in opencl_debuginfo_100
    {23,IR(893, 2),IR(51368, 11),IR(1, 0)}, // DebugScope in opencl_debuginfo_100
    {24,IR(0, 0),IR(51379, 13),IR(1, 0)}, // DebugNoScope in opencl_debuginfo_100
    {25,IR(895, 3),IR(51392, 15),IR(1, 0)}, // DebugInlinedAt in opencl_debuginfo_100
    {26,IR(1114, 8),IR(51449, 19),IR(1, 0)}, // DebugLocalVariable in opencl_debuginfo_100
    {27,IR(36, 2),IR(51468, 21),IR(1, 0)}, // DebugInlinedVariable in opencl_debuginfo_100
    {28,IR(33, 3),IR(51489, 13),IR(1, 0)}, // DebugDeclare in opencl_debuginfo_100
    {29,IR(975, 4),IR(51502, 11),IR(1, 0)}, // DebugValue in opencl_debuginfo_100
    {30,IR(1122, 2),IR(51546, 15),IR(1, 0)}, // DebugOperation in opencl_debuginfo_100
    {31,IR(739, 1),IR(51561, 16),IR(1, 0)}, // DebugExpression in opencl_debuginfo_100
    {32,IR(907, 4),IR(51577, 14),IR(1, 0)}, // DebugMacroDef in opencl_debuginfo_100
    {33,IR(890, 3),IR(51591, 16),IR(1, 0)}, // DebugMacroUndef in opencl_debuginfo_100
    {34,IR(1124, 7),IR(53346, 20),IR(1, 0)}, // DebugImportedEntity in opencl_debuginfo_100
    {35,IR(893, 2),IR(53366, 12),IR(1, 0)}, // DebugSource in opencl_debuginfo_100
    {36,IR(1131, 8),IR(53951, 17),IR(1, 0)}, // DebugModuleINTEL in opencl_debuginfo_100
    {0,IR(10, 1),IR(53968, 5),IR(1, 0)}, // acos in opencl_std_100
    {1,IR(10, 1),IR(53973, 6),IR(1, 0)}, // acosh in opencl_std_100
    {2,IR(10, 1),IR(53979, 7),IR(1, 0)}, // acospi in opencl_std_100
    {3,IR(10, 1),IR(53986, 5),IR(1, 0)}, // asin in opencl_std_100
    {4,IR(10, 1),IR(53991, 6),IR(1, 0)}, // asinh in opencl_std_100
    {5,IR(10, 1),IR(53997, 7),IR(1, 0)}, // asinpi in opencl_std_100
    {6,IR(10, 1),IR(54004, 5),IR(1, 0)}, // atan in opencl_std_100
    {7,IR(36, 2),IR(54009, 6),IR(1, 0)}, // atan2 in opencl_std_100
    {8,IR(10, 1),IR(54015, 6),IR(1, 0)}, // atanh in opencl_std_100
    {9,IR(10, 1),IR(54021, 7),IR(1, 0)}, // atanpi in opencl_std_100
    {10,IR(36, 2),IR(54028, 8),IR(1, 0)}, // atan2pi in opencl_std_100
    {11,IR(10, 1),IR(54036, 5),IR(1, 0)}, // cbrt in opencl_std_100
    {12,IR(10, 1),IR(54041, 5),IR(1, 0)}, // ceil in opencl_std_100
    {13,IR(36, 2),IR(54046, 9),IR(1, 0)}, // copysign in opencl_std_100
    {14,IR(10, 1),IR(54055, 4),IR(1, 0)}, // cos in opencl_std_100
    {15,IR(10, 1),IR(54059, 5),IR(1, 0)}, // cosh in opencl_std_100
    {16,IR(10, 1),IR(54064, 6),IR(1, 0)}, // cospi in opencl_std_100
    {17,IR(10, 1),IR(54070, 5),IR(1, 0)}, // erfc in opencl_std_100
    {18,IR(10, 1),IR(54075, 4),IR(1, 0)}, // erf in opencl_std_100
    {19,IR(10, 1),IR(54079, 4),IR(1, 0)}, // exp in opencl_std_100
    {20,IR(10, 1),IR(54083, 5),IR(1, 0)}, // exp2 in opencl_std_100
    {21,IR(10, 1),IR(54088, 6),IR(1, 0)}, // exp10 in opencl_std_100
    {22,IR(10, 1),IR(54094, 6),IR(1, 0)}, // expm1 in opencl_std_100
    {23,IR(10, 1),IR(54100, 5),IR(1, 0)}, // fabs in opencl_std_100
    {24,IR(36, 2),IR(54105, 5),IR(1, 0)}, // fdim in opencl_std_100
    {25,IR(10, 1),IR(54110, 6),IR(1, 0)}, // floor in opencl_std_100
    {26,IR(33, 3),IR(54116, 4),IR(1, 0)}, // fma in opencl_std_100
    {27,IR(36, 2),IR(54120, 5),IR(1, 0)}, // fmax in opencl_std_100
    {28,IR(36, 2),IR(54125, 5),IR(1, 0)}, // fmin in opencl_std_100
    {29,IR(36, 2),IR(54130, 5),IR(1, 0)}, // fmod in opencl_std_100
    {30,IR(36, 2),IR(54135, 6),IR(1, 0)}, // fract in opencl_std_100
    {31,IR(36, 2),IR(54141, 6),IR(1, 0)}, // frexp in opencl_std_100
    {32,IR(36, 2),IR(54147, 6),IR(1, 0)}, // hypot in opencl_std_100
    {33,IR(10, 1),IR(54153, 6),IR(1, 0)}, // ilogb in opencl_std_100
    {34,IR(36, 2),IR(54159, 6),IR(1, 0)}, // ldexp in opencl_std_100
    {35,IR(10, 1),IR(54165, 7),IR(1, 0)}, // lgamma in opencl_std_100
    {36,IR(36, 2),IR(54172, 9),IR(1, 0)}, // lgamma_r in opencl_std_100
    {37,IR(10, 1),IR(54181, 4),IR(1, 0)}, // log in opencl_std_100
    {38,IR(10, 1),IR(54185, 5),IR(1, 0)}, // log2 in opencl_std_100
    {39,IR(10, 1),IR(54190, 6),IR(1, 0)}, // log10 in opencl_std_100
    {40,IR(10, 1),IR(54196, 6),IR(1, 0)}, // log1p in opencl_std_100
    {41,IR(10, 1),IR(54202, 5),IR(1, 0)}, // logb in opencl_std_100
    {42,IR(33, 3),IR(54207, 4),IR(1, 0)}, // mad in opencl_std_100
    {43,IR(36, 2),IR(54211, 7),IR(1, 0)}, // maxmag in opencl_std_100
    {44,IR(36, 2),IR(54218, 7),IR(1, 0)}, // minmag in opencl_std_100
    {45,IR(36, 2),IR(54225, 5),IR(1, 0)}, // modf in opencl_std_100
    {46,IR(10, 1),IR(54230, 4),IR(1, 0)}, // nan in opencl_std_100
    {47,IR(36, 2),IR(54234, 10),IR(1, 0)}, // nextafter in opencl_std_100
    {48,IR(36, 2),IR(54244, 4),IR(1, 0)}, // pow in opencl_std_100
    {49,IR(36, 2),IR(54248, 5),IR(1, 0)}, // pown in opencl_std_100
    {50,IR(36, 2),IR(54253, 5),IR(1, 0)}, // powr in opencl_std_100
    {51,IR(36, 2),IR(54258, 10),IR(1, 0)}, // remainder in opencl_std_100
    {52,IR(33, 3),IR(54268, 7),IR(1, 0)}, // remquo in opencl_std_100
    {53,IR(10, 1),IR(54275, 5),IR(1, 0)}, // rint in opencl_std_100
    {54,IR(36, 2),IR(54280, 6),IR(1, 0)}, // rootn in opencl_std_100
    {55,IR(10, 1),IR(54286, 6),IR(1, 0)}, // round in opencl_std_100
    {56,IR(10, 1),IR(54292, 6),IR(1, 0)}, // rsqrt in opencl_std_100
    {57,IR(10, 1),IR(54298, 4),IR(1, 0)}, // sin in opencl_std_100
    {58,IR(36, 2),IR(54302, 7),IR(1, 0)}, // sincos in opencl_std_100
    {59,IR(10, 1),IR(54309, 5),IR(1, 0)}, // sinh in opencl_std_100
    {60,IR(10, 1),IR(54314, 6),IR(1, 0)}, // sinpi in opencl_std_100
    {61,IR(10, 1),IR(54320, 5),IR(1, 0)}, // sqrt in opencl_std_100
    {62,IR(10, 1),IR(54325, 4),IR(1, 0)}, // tan in opencl_std_100
    {63,IR(10, 1),IR(54329, 5),IR(1, 0)}, // tanh in opencl_std_100
    {64,IR(10, 1),IR(54334, 6),IR(1, 0)}, // tanpi in opencl_std_100
    {65,IR(10, 1),IR(54340, 7),IR(1, 0)}, // tgamma in opencl_std_100
    {66,IR(10, 1),IR(54347, 6),IR(1, 0)}, // trunc in opencl_std_100
    {67,IR(10, 1),IR(54353, 9),IR(1, 0)}, // half_cos in opencl_std_100
    {68,IR(36, 2),IR(54362, 12),IR(1, 0)}, // half_divide in opencl_std_100
    {69,IR(10, 1),IR(54374, 9),IR(1, 0)}, // half_exp in opencl_std_100
    {70,IR(10, 1),IR(54383, 10),IR(1, 0)}, // half_exp2 in opencl_std_100
    {71,IR(10, 1),IR(54393, 11),IR(1, 0)}, // half_exp10 in opencl_std_100
    {72,IR(10, 1),IR(54404, 9),IR(1, 0)}, // half_log in opencl_std_100
    {73,IR(10, 1),IR(54413, 10),IR(1, 0)}, // half_log2 in opencl_std_100
    {74,IR(10, 1),IR(54423, 11),IR(1, 0)}, // half_log10 in opencl_std_100
    {75,IR(36, 2),IR(54434, 10),IR(1, 0)}, // half_powr in opencl_std_100
    {76,IR(10, 1),IR(54444, 11),IR(1, 0)}, // half_recip in opencl_std_100
    {77,IR(10, 1),IR(54455, 11),IR(1, 0)}, // half_rsqrt in opencl_std_100
    {78,IR(10, 1),IR(54466, 9),IR(1, 0)}, // half_sin in opencl_std_100
    {79,IR(10, 1),IR(54475, 10),IR(1, 0)}, // half_sqrt in opencl_std_100
    {80,IR(10, 1),IR(54485, 9),IR(1, 0)}, // half_tan in opencl_std_100
    {81,IR(10, 1),IR(54494, 11),IR(1, 0)}, // native_cos in opencl_std_100
    {82,IR(36, 2),IR(54505, 14),IR(1, 0)}, // native_divide in opencl_std_100
    {83,IR(10, 1),IR(54519, 11),IR(1, 0)}, // native_exp in opencl_std_100
    {84,IR(10, 1),IR(54530, 12),IR(1, 0)}, // native_exp2 in opencl_std_100
    {85,IR(10, 1),IR(54542, 13),IR(1, 0)}, // native_exp10 in opencl_std_100
    {86,IR(10, 1),IR(54555, 11),IR(1, 0)}, // native_log in opencl_std_100
    {87,IR(10, 1),IR(54566, 12),IR(1, 0)}, // native_log2 in opencl_std_100
    {88,IR(10, 1),IR(54578, 13),IR(1, 0)}, // native_log10 in opencl_std_100
    {89,IR(36, 2),IR(54591, 12),IR(1, 0)}, // native_powr in opencl_std_100
    {90,IR(10, 1),IR(54603, 13),IR(1, 0)}, // native_recip in opencl_std_100
    {91,IR(10, 1),IR(54616, 13),IR(1, 0)}, // native_rsqrt in opencl_std_100
    {92,IR(10, 1),IR(54629, 11),IR(1, 0)}, // native_sin in opencl_std_100
    {93,IR(10, 1),IR(54640, 12),IR(1, 0)}, // native_sqrt in opencl_std_100
    {94,IR(10, 1),IR(54652, 11),IR(1, 0)}, // native_tan in opencl_std_100
    {95,IR(33, 3),IR(54663, 7),IR(1, 0)}, // fclamp in opencl_std_100
    {96,IR(10, 1),IR(54670, 8),IR(1, 0)}, // degrees in opencl_std_100
    {97,IR(36, 2),IR(54678, 12),IR(1, 0)}, // fmax_common in opencl_std_100
    {98,IR(36, 2),IR(54690, 12),IR(1, 0)}, // fmin_common in opencl_std_100
    {99,IR(33, 3),IR(54702, 4),IR(1, 0)}, // mix in opencl_std_100
    {100,IR(10, 1),IR(54706, 8),IR(1, 0)}, // radians in opencl_std_100
    {101,IR(36, 2),IR(54714, 5),IR(1, 0)}, // step in opencl_std_100
    {102,IR(33, 3),IR(54719, 11),IR(1, 0)}, // smoothstep in opencl_std_100
    {103,IR(10, 1),IR(54730, 5),IR(1, 0)}, // sign in opencl_std_100
    {104,IR(36, 2),IR(54735, 6),IR(1, 0)}, // cross in opencl_std_100
    {105,IR(36, 2),IR(54741, 9),IR(1, 0)}, // distance in opencl_std_100
    {106,IR(10, 1),IR(54750, 7),IR(1, 0)}, // length in opencl_std_100
    {107,IR(10, 1),IR(54757, 10),IR(1, 0)}, // normalize in opencl_std_100
    {108,IR(36, 2),IR(54767, 14),IR(1, 0)}, // fast_distance in opencl_std_100
    {109,IR(10, 1),IR(54781, 12),IR(1, 0)}, // fast_length in opencl_std_100
    {110,IR(10, 1),IR(54793, 15),IR(1, 0)}, // fast_normalize in opencl_std_100
    {141,IR(10, 1),IR(54808, 6),IR(1, 0)}, // s_abs in opencl_std_100
    {142,IR(36, 2),IR(54814, 11),IR(1, 0)}, // s_abs_diff in opencl_std_100
    {143,IR(36, 2),IR(54825, 10),IR(1, 0)}, // s_add_sat in opencl_std_100
    {144,IR(36, 2),IR(54835, 10),IR(1, 0)}, // u_add_sat in opencl_std_100
    {145,IR(36, 2),IR(54845, 7),IR(1, 0)}, // s_hadd in opencl_std_100
    {146,IR(36, 2),IR(54852, 7),IR(1, 0)}, // u_hadd in opencl_std_100
    {147,IR(36, 2),IR(54859, 8),IR(1, 0)}, // s_rhadd in opencl_std_100
    {148,IR(36, 2),IR(54867, 8),IR(1, 0)}, // u_rhadd in opencl_std_100
    {149,IR(33, 3),IR(54875, 8),IR(1, 0)}, // s_clamp in opencl_std_100
    {150,IR(33, 3),IR(54883, 8),IR(1, 0)}, // u_clamp in opencl_std_100
    {151,IR(10, 1),IR(54891, 4),IR(1, 0)}, // clz in opencl_std_100
    {152,IR(10, 1),IR(54895, 4),IR(1, 0)}, // ctz in opencl_std_100
    {153,IR(33, 3),IR(54899, 9),IR(1, 0)}, // s_mad_hi in opencl_std_100
    {154,IR(33, 3),IR(54908, 10),IR(1, 0)}, // u_mad_sat in opencl_std_100
    {155,IR(33, 3),IR(54918, 10),IR(1, 0)}, // s_mad_sat in opencl_std_100
    {156,IR(36, 2),IR(54928, 6),IR(1, 0)}, // s_max in opencl_std_100
    {157,IR(36, 2),IR(54934, 6),IR(1, 0)}, // u_max in opencl_std_100
    {158,IR(36, 2),IR(54940, 6),IR(1, 0)}, // s_min in opencl_std_100
    {159,IR(36, 2),IR(54946, 6),IR(1, 0)}, // u_min in opencl_std_100
    {160,IR(36, 2),IR(54952, 9),IR(1, 0)}, // s_mul_hi in opencl_std_100
    {161,IR(36, 2),IR(54961, 7),IR(1, 0)}, // rotate in opencl_std_100
    {162,IR(36, 2),IR(54968, 10),IR(1, 0)}, // s_sub_sat in opencl_std_100
    {163,IR(36, 2),IR(54978, 10),IR(1, 0)}, // u_sub_sat in opencl_std_100
    {164,IR(36, 2),IR(54988, 11),IR(1, 0)}, // u_upsample in opencl_std_100
    {165,IR(36, 2),IR(54999, 11),IR(1, 0)}, // s_upsample in opencl_std_100
    {166,IR(10, 1),IR(55010, 9),IR(1, 0)}, // popcount in opencl_std_100
    {167,IR(33, 3),IR(55019, 8),IR(1, 0)}, // s_mad24 in opencl_std_100
    {168,IR(33, 3),IR(55027, 8),IR(1, 0)}, // u_mad24 in opencl_std_100
    {169,IR(36, 2),IR(55035, 8),IR(1, 0)}, // s_mul24 in opencl_std_100
    {170,IR(36, 2),IR(55043, 8),IR(1, 0)}, // u_mul24 in opencl_std_100
    {171,IR(1139, 3),IR(55051, 7),IR(1, 0)}, // vloadn in opencl_std_100
    {172,IR(33, 3),IR(55058, 8),IR(1, 0)}, // vstoren in opencl_std_100
    {173,IR(36, 2),IR(55066, 11),IR(1, 0)}, // vload_half in opencl_std_100
    {174,IR(1139, 3),IR(55077, 12),IR(1, 0)}, // vload_halfn in opencl_std_100
    {175,IR(33, 3),IR(55089, 12),IR(1, 0)}, // vstore_half in opencl_std_100
    {176,IR(1142, 4),IR(55101, 14),IR(1, 0)}, // vstore_half_r in opencl_std_100
    {177,IR(33, 3),IR(55115, 13),IR(1, 0)}, // vstore_halfn in opencl_std_100
    {178,IR(1142, 4),IR(55128, 15),IR(1, 0)}, // vstore_halfn_r in opencl_std_100
    {179,IR(1139, 3),IR(55143, 13),IR(1, 0)}, // vloada_halfn in opencl_std_100
    {180,IR(33, 3),IR(55156, 14),IR(1, 0)}, // vstorea_halfn in opencl_std_100
    {181,IR(1142, 4),IR(55170, 16),IR(1, 0)}, // vstorea_halfn_r in opencl_std_100
    {182,IR(36, 2),IR(55186, 8),IR(1, 0)}, // shuffle in opencl_std_100
    {183,IR(33, 3),IR(55194, 9),IR(1, 0)}, // shuffle2 in opencl_std_100
    {184,IR(168, 2),IR(55203, 7),IR(1, 0)}, // printf in opencl_std_100
    {185,IR(36, 2),IR(55210, 9),IR(1, 0)}, // prefetch in opencl_std_100
    {186,IR(33, 3),IR(55219, 10),IR(1, 0)}, // bitselect in opencl_std_100
    {187,IR(33, 3),IR(55229, 7),IR(1, 0)}, // select in opencl_std_100
    {201,IR(10, 1),IR(55236, 6),IR(1, 0)}, // u_abs in opencl_std_100
    {202,IR(36, 2),IR(55242, 11),IR(1, 0)}, // u_abs_diff in opencl_std_100
    {203,IR(36, 2),IR(55253, 9),IR(1, 0)}, // u_mul_hi in opencl_std_100
    {204,IR(33, 3),IR(55262, 9),IR(1, 0)}, // u_mad_hi in opencl_std_100
    {1,IR(10, 1),IR(55271, 17),IR(1, 0)}, // CubeFaceIndexAMD in spv_amd_gcn_shader
    {2,IR(10, 1),IR(55288, 17),IR(1, 0)}, // CubeFaceCoordAMD in spv_amd_gcn_shader
    {3,IR(0, 0),IR(55305, 8),IR(1, 0)}, // TimeAMD in spv_amd_gcn_shader
    {1,IR(36, 2),IR(55313, 22),IR(1, 0)}, // SwizzleInvocationsAMD in spv_amd_shader_ballot
    {2,IR(36, 2),IR(55335, 28),IR(1, 0)}, // SwizzleInvocationsMaskedAMD in spv_amd_shader_ballot
    {3,IR(33, 3),IR(55363, 19),IR(1, 0)}, // WriteInvocationAMD in spv_amd_shader_ballot
    {4,IR(10, 1),IR(55382, 9),IR(1, 0)}, // MbcntAMD in spv_amd_shader_ballot
    {1,IR(36, 2),IR(55391, 23),IR(1, 0)}, // InterpolateAtVertexAMD in spv_amd_shader_explicit_vertex_parameter
    {1,IR(33, 3),IR(55414, 9),IR(1, 0)}, // FMin3AMD in spv_amd_shader_trinary_minmax
    {2,IR(33, 3),IR(55423, 9),IR(1, 0)}, // UMin3AMD in spv_amd_shader_trinary_minmax
    {3,IR(33, 3),IR(55432, 9),IR(1, 0)}, // SMin3AMD in spv_amd_shader_trinary_minmax
    {4,IR(33, 3),IR(55441, 9),IR(1, 0)}, // FMax3AMD in spv_amd_shader_trinary_minmax
    {5,IR(33, 3),IR(55450, 9),IR(1, 0)}, // UMax3AMD in spv_amd_shader_trinary_minmax
    {6,IR(33, 3),IR(55459, 9),IR(1, 0)}, // SMax3AMD in spv_amd_shader_trinary_minmax
    {7,IR(33, 3),IR(55468, 9),IR(1, 0)}, // FMid3AMD in spv_amd_shader_trinary_minmax
    {8,IR(33, 3),IR(55477, 9),IR(1, 0)}, // UMid3AMD in spv_amd_shader_trinary_minmax
    {9,IR(33, 3),IR(55486, 9),IR(1, 0)}, // SMid3AMD in spv_amd_shader_trinary_minmax
}};

IndexRange ExtInstByValueRangeForKind(spv_ext_inst_type_t type) {
  switch(type) {
    case SPV_EXT_INST_TYPE_DEBUGINFO: return IR(0, 34);
    case SPV_EXT_INST_TYPE_GLSL_STD_450: return IR(34, 81);
    case SPV_EXT_INST_TYPE_NONSEMANTIC_CLSPVREFLECTION: return IR(115, 42);
    case SPV_EXT_INST_TYPE_NONSEMANTIC_SHADER_DEBUGINFO_100: return IR(157, 44);
    case SPV_EXT_INST_TYPE_NONSEMANTIC_VKSPREFLECTION: return IR(201, 8);
    case SPV_EXT_INST_TYPE_OPENCL_DEBUGINFO_100: return IR(209, 37);
    case SPV_EXT_INST_TYPE_OPENCL_STD: return IR(246, 162);
    case SPV_EXT_INST_TYPE_SPV_AMD_GCN_SHADER: return IR(408, 3);
    case SPV_EXT_INST_TYPE_SPV_AMD_SHADER_BALLOT: return IR(411, 4);
    case SPV_EXT_INST_TYPE_SPV_AMD_SHADER_EXPLICIT_VERTEX_PARAMETER: return IR(415, 1);
    case SPV_EXT_INST_TYPE_SPV_AMD_SHADER_TRINARY_MINMAX: return IR(416, 9);
    default: break;
  }
  return IR(0,0);
}

// Extended instruction opcode names sorted by extended instruction kind, then opcode name.
// The fields in order are:
//   name
//   index into kExtInstByValue
static const std::array<NameIndex, 425> kExtInstNames{{
    {IR(50762, 21), 1}, // DebugCompilationUnit in debuginfo
    {IR(51489, 13), 28}, // DebugDeclare in debuginfo
    {IR(51561, 16), 31}, // DebugExpression in debuginfo
    {IR(51305, 14), 20}, // DebugFunction in debuginfo
    {IR(51280, 25), 19}, // DebugFunctionDeclaration in debuginfo
    {IR(51260, 20), 18}, // DebugGlobalVariable in debuginfo
    {IR(50748, 14), 0}, // DebugInfoNone in debuginfo
    {IR(51392, 15), 25}, // DebugInlinedAt in debuginfo
    {IR(51468, 21), 27}, // DebugInlinedVariable in debuginfo
    {IR(51319, 18), 21}, // DebugLexicalBlock in debuginfo
    {IR(51337, 31), 22}, // DebugLexicalBlockDiscriminator in debuginfo
    {IR(51449, 19), 26}, // DebugLocalVariable in debuginfo
    {IR(51577, 14), 32}, // DebugMacroDef in debuginfo
    {IR(51591, 16), 33}, // DebugMacroUndef in debuginfo
    {IR(51379, 13), 24}, // DebugNoScope in debuginfo
    {IR(51546, 15), 30}, // DebugOperation in debuginfo
    {IR(51368, 11), 23}, // DebugScope in debuginfo
    {IR(50958, 15), 5}, // DebugTypeArray in debuginfo
    {IR(50835, 15), 2}, // DebugTypeBasic in debuginfo
    {IR(51072, 19), 10}, // DebugTypeComposite in debuginfo
    {IR(51020, 14), 9}, // DebugTypeEnum in debuginfo
    {IR(51002, 18), 8}, // DebugTypeFunction in debuginfo
    {IR(51107, 21), 12}, // DebugTypeInheritance in debuginfo
    {IR(51091, 16), 11}, // DebugTypeMember in debuginfo
    {IR(50884, 17), 3}, // DebugTypePointer in debuginfo
    {IR(51128, 21), 13}, // DebugTypePtrToMember in debuginfo
    {IR(50939, 19), 4}, // DebugTypeQualifier in debuginfo
    {IR(51149, 18), 14}, // DebugTypeTemplate in debuginfo
    {IR(51167, 27), 15}, // DebugTypeTemplateParameter in debuginfo
    {IR(51229, 31), 17}, // DebugTypeTemplateParameterPack in debuginfo
    {IR(51194, 35), 16}, // DebugTypeTemplateTemplateParameter in debuginfo
    {IR(50973, 16), 6}, // DebugTypeVector in debuginfo
    {IR(50989, 13), 7}, // DebugTypedef in debuginfo
    {IR(51502, 11), 29}, // DebugValue in debuginfo
    {IR(51701, 5), 50}, // Acos in glsl_std_450
    {IR(51732, 6), 56}, // Acosh in glsl_std_450
    {IR(51696, 5), 49}, // Asin in glsl_std_450
    {IR(51726, 6), 55}, // Asinh in glsl_std_450
    {IR(51706, 5), 51}, // Atan in glsl_std_450
    {IR(51744, 6), 58}, // Atan2 in glsl_std_450
    {IR(51738, 6), 57}, // Atanh in glsl_std_450
    {IR(51657, 5), 42}, // Ceil in glsl_std_450
    {IR(51688, 4), 47}, // Cos in glsl_std_450
    {IR(51716, 5), 53}, // Cosh in glsl_std_450
    {IR(52128, 6), 101}, // Cross in glsl_std_450
    {IR(51676, 8), 45}, // Degrees in glsl_std_450
    {IR(51789, 12), 66}, // Determinant in glsl_std_450
    {IR(52119, 9), 100}, // Distance in glsl_std_450
    {IR(51754, 4), 60}, // Exp in glsl_std_450
    {IR(51762, 5), 62}, // Exp2 in glsl_std_450
    {IR(51629, 5), 37}, // FAbs in glsl_std_450
    {IR(51861, 7), 76}, // FClamp in glsl_std_450
    {IR(51846, 5), 73}, // FMax in glsl_std_450
    {IR(51831, 5), 70}, // FMin in glsl_std_450
    {IR(51882, 5), 79}, // FMix in glsl_std_450
    {IR(51639, 6), 39}, // FSign in glsl_std_450
    {IR(52144, 12), 103}, // FaceForward in glsl_std_450
    {IR(52172, 9), 106}, // FindILsb in glsl_std_450
    {IR(52181, 9), 107}, // FindSMsb in glsl_std_450
    {IR(52190, 9), 108}, // FindUMsb in glsl_std_450
    {IR(51651, 6), 41}, // Floor in glsl_std_450
    {IR(51908, 4), 83}, // Fma in glsl_std_450
    {IR(51662, 6), 43}, // Fract in glsl_std_450
    {IR(51912, 6), 84}, // Frexp in glsl_std_450
    {IR(51918, 12), 85}, // FrexpStruct in glsl_std_450
    {IR(51887, 5), 80}, // IMix in glsl_std_450
    {IR(52199, 22), 109}, // InterpolateAtCentroid in glsl_std_450
    {IR(52241, 20), 111}, // InterpolateAtOffset in glsl_std_450
    {IR(52221, 20), 110}, // InterpolateAtSample in glsl_std_450
    {IR(51777, 12), 65}, // InverseSqrt in glsl_std_450
    {IR(51930, 6), 86}, // Ldexp in glsl_std_450
    {IR(52112, 7), 99}, // Length in glsl_std_450
    {IR(51758, 4), 61}, // Log in glsl_std_450
    {IR(51767, 5), 63}, // Log2 in glsl_std_450
    {IR(51801, 14), 67}, // MatrixInverse in glsl_std_450
    {IR(51815, 5), 68}, // Modf in glsl_std_450
    {IR(51820, 11), 69}, // ModfStruct in glsl_std_450
    {IR(52271, 7), 114}, // NClamp in glsl_std_450
    {IR(52266, 5), 113}, // NMax in glsl_std_450
    {IR(52261, 5), 112}, // NMin in glsl_std_450
    {IR(52134, 10), 102}, // Normalize in glsl_std_450
    {IR(52003, 15), 92}, // PackDouble2x32 in glsl_std_450
    {IR(51990, 13), 91}, // PackHalf2x16 in glsl_std_450
    {IR(51962, 14), 89}, // PackSnorm2x16 in glsl_std_450
    {IR(51936, 13), 87}, // PackSnorm4x8 in glsl_std_450
    {IR(51976, 14), 90}, // PackUnorm2x16 in glsl_std_450
    {IR(51949, 13), 88}, // PackUnorm4x8 in glsl_std_450
    {IR(51750, 4), 59}, // Pow in glsl_std_450
    {IR(51668, 8), 44}, // Radians in glsl_std_450
    {IR(52156, 8), 104}, // Reflect in glsl_std_450
    {IR(52164, 8), 105}, // Refract in glsl_std_450
    {IR(51607, 6), 34}, // Round in glsl_std_450
    {IR(51613, 10), 35}, // RoundEven in glsl_std_450
    {IR(51634, 5), 38}, // SAbs in glsl_std_450
    {IR(51875, 7), 78}, // SClamp in glsl_std_450
    {IR(51856, 5), 75}, // SMax in glsl_std_450
    {IR(51841, 5), 72}, // SMin in glsl_std_450
    {IR(51645, 6), 40}, // SSign in glsl_std_450
    {IR(51684, 4), 46}, // Sin in glsl_std_450
    {IR(51711, 5), 52}, // Sinh in glsl_std_450
    {IR(51897, 11), 82}, // SmoothStep in glsl_std_450
    {IR(51772, 5), 64}, // Sqrt in glsl_std_450
    {IR(51892, 5), 81}, // Step in glsl_std_450
    {IR(51692, 4), 48}, // Tan in glsl_std_450
    {IR(51721, 5), 54}, // Tanh in glsl_std_450
    {IR(51623, 6), 36}, // Trunc in glsl_std_450
    {IR(51868, 7), 77}, // UClamp in glsl_std_450
    {IR(51851, 5), 74}, // UMax in glsl_std_450
    {IR(51836, 5), 71}, // UMin in glsl_std_450
    {IR(52095, 17), 98}, // UnpackDouble2x32 in glsl_std_450
    {IR(52050, 15), 95}, // UnpackHalf2x16 in glsl_std_450
    {IR(52018, 16), 93}, // UnpackSnorm2x16 in glsl_std_450
    {IR(52065, 15), 96}, // UnpackSnorm4x8 in glsl_std_450
    {IR(52034, 16), 94}, // UnpackUnorm2x16 in glsl_std_450
    {IR(52080, 15), 97}, // UnpackUnorm4x8 in glsl_std_450
    {IR(52278, 13), 116}, // ArgumentInfo in nonsemantic_clspvreflection
    {IR(52373, 24), 121}, // ArgumentPodPushConstant in nonsemantic_clspvreflection
    {IR(52329, 25), 119}, // ArgumentPodStorageBuffer in nonsemantic_clspvreflection
    {IR(52354, 19), 120}, // ArgumentPodUniform in nonsemantic_clspvreflection
    {IR(52807, 28), 140}, // ArgumentPointerPushConstant in nonsemantic_clspvreflection
    {IR(52835, 23), 141}, // ArgumentPointerUniform in nonsemantic_clspvreflection
    {IR(52397, 21), 122}, // ArgumentSampledImage in nonsemantic_clspvreflection
    {IR(52439, 16), 124}, // ArgumentSampler in nonsemantic_clspvreflection
    {IR(52291, 22), 117}, // ArgumentStorageBuffer in nonsemantic_clspvreflection
    {IR(52418, 21), 123}, // ArgumentStorageImage in nonsemantic_clspvreflection
    {IR(53095, 27), 148}, // ArgumentStorageTexelBuffer in nonsemantic_clspvreflection
    {IR(52313, 16), 118}, // ArgumentUniform in nonsemantic_clspvreflection
    {IR(53122, 27), 149}, // ArgumentUniformTexelBuffer in nonsemantic_clspvreflection
    {IR(52455, 18), 125}, // ArgumentWorkgroup in nonsemantic_clspvreflection
    {IR(53149, 32), 150}, // ConstantDataPointerPushConstant in nonsemantic_clspvreflection
    {IR(52703, 26), 135}, // ConstantDataStorageBuffer in nonsemantic_clspvreflection
    {IR(52729, 20), 136}, // ConstantDataUniform in nonsemantic_clspvreflection
    {IR(52973, 45), 145}, // ImageArgumentInfoChannelDataTypePushConstant in nonsemantic_clspvreflection
    {IR(53055, 40), 147}, // ImageArgumentInfoChannelDataTypeUniform in nonsemantic_clspvreflection
    {IR(52931, 42), 144}, // ImageArgumentInfoChannelOrderPushConstant in nonsemantic_clspvreflection
    {IR(53018, 37), 146}, // ImageArgumentInfoChannelOrderUniform in nonsemantic_clspvreflection
    {IR(5497, 7), 115}, // Kernel in nonsemantic_clspvreflection
    {IR(8971, 15), 137}, // LiteralSampler in nonsemantic_clspvreflection
    {IR(53290, 34), 155}, // NormalizedSamplerMaskPushConstant in nonsemantic_clspvreflection
    {IR(53258, 32), 154}, // PrintfBufferPointerPushConstant in nonsemantic_clspvreflection
    {IR(53232, 26), 153}, // PrintfBufferStorageBuffer in nonsemantic_clspvreflection
    {IR(53221, 11), 152}, // PrintfInfo in nonsemantic_clspvreflection
    {IR(53181, 40), 151}, // ProgramScopeVariablePointerPushConstant in nonsemantic_clspvreflection
    {IR(52893, 38), 143}, // ProgramScopeVariablePointerRelocation in nonsemantic_clspvreflection
    {IR(52858, 35), 142}, // ProgramScopeVariablesStorageBuffer in nonsemantic_clspvreflection
    {IR(52749, 30), 138}, // PropertyRequiredWorkgroupSize in nonsemantic_clspvreflection
    {IR(52569, 30), 130}, // PushConstantEnqueuedLocalSize in nonsemantic_clspvreflection
    {IR(52544, 25), 129}, // PushConstantGlobalOffset in nonsemantic_clspvreflection
    {IR(52599, 23), 131}, // PushConstantGlobalSize in nonsemantic_clspvreflection
    {IR(52647, 26), 133}, // PushConstantNumWorkgroups in nonsemantic_clspvreflection
    {IR(52673, 30), 134}, // PushConstantRegionGroupOffset in nonsemantic_clspvreflection
    {IR(52622, 25), 132}, // PushConstantRegionOffset in nonsemantic_clspvreflection
    {IR(52499, 25), 127}, // SpecConstantGlobalOffset in nonsemantic_clspvreflection
    {IR(52779, 28), 139}, // SpecConstantSubgroupMaxSize in nonsemantic_clspvreflection
    {IR(52524, 20), 128}, // SpecConstantWorkDim in nonsemantic_clspvreflection
    {IR(52473, 26), 126}, // SpecConstantWorkgroupSize in nonsemantic_clspvreflection
    {IR(53324, 22), 156}, // WorkgroupVariableSize in nonsemantic_clspvreflection
    {IR(53445, 21), 197}, // DebugBuildIdentifier in nonsemantic_shader_debuginfo_100
    {IR(50762, 21), 158}, // DebugCompilationUnit in nonsemantic_shader_debuginfo_100
    {IR(51489, 13), 185}, // DebugDeclare in nonsemantic_shader_debuginfo_100
    {IR(53483, 16), 199}, // DebugEntryPoint in nonsemantic_shader_debuginfo_100
    {IR(51561, 16), 188}, // DebugExpression in nonsemantic_shader_debuginfo_100
    {IR(51305, 14), 177}, // DebugFunction in nonsemantic_shader_debuginfo_100
    {IR(51280, 25), 176}, // DebugFunctionDeclaration in nonsemantic_shader_debuginfo_100
    {IR(53378, 24), 193}, // DebugFunctionDefinition in nonsemantic_shader_debuginfo_100
    {IR(51260, 20), 175}, // DebugGlobalVariable in nonsemantic_shader_debuginfo_100
    {IR(53346, 20), 191}, // DebugImportedEntity in nonsemantic_shader_debuginfo_100
    {IR(50748, 14), 157}, // DebugInfoNone in nonsemantic_shader_debuginfo_100
    {IR(51392, 15), 182}, // DebugInlinedAt in nonsemantic_shader_debuginfo_100
    {IR(51468, 21), 184}, // DebugInlinedVariable in nonsemantic_shader_debuginfo_100
    {IR(51319, 18), 178}, // DebugLexicalBlock in nonsemantic_shader_debuginfo_100
    {IR(51337, 31), 179}, // DebugLexicalBlockDiscriminator in nonsemantic_shader_debuginfo_100
    {IR(53423, 10), 195}, // DebugLine in nonsemantic_shader_debuginfo_100
    {IR(51449, 19), 183}, // DebugLocalVariable in nonsemantic_shader_debuginfo_100
    {IR(51577, 14), 189}, // DebugMacroDef in nonsemantic_shader_debuginfo_100
    {IR(51591, 16), 190}, // DebugMacroUndef in nonsemantic_shader_debuginfo_100
    {IR(53433, 12), 196}, // DebugNoLine in nonsemantic_shader_debuginfo_100
    {IR(51379, 13), 181}, // DebugNoScope in nonsemantic_shader_debuginfo_100
    {IR(51546, 15), 187}, // DebugOperation in nonsemantic_shader_debuginfo_100
    {IR(51368, 11), 180}, // DebugScope in nonsemantic_shader_debuginfo_100
    {IR(53366, 12), 192}, // DebugSource in nonsemantic_shader_debuginfo_100
    {IR(53402, 21), 194}, // DebugSourceContinued in nonsemantic_shader_debuginfo_100
    {IR(53466, 17), 198}, // DebugStoragePath in nonsemantic_shader_debuginfo_100
    {IR(50958, 15), 162}, // DebugTypeArray in nonsemantic_shader_debuginfo_100
    {IR(50835, 15), 159}, // DebugTypeBasic in nonsemantic_shader_debuginfo_100
    {IR(51072, 19), 167}, // DebugTypeComposite in nonsemantic_shader_debuginfo_100
    {IR(51020, 14), 166}, // DebugTypeEnum in nonsemantic_shader_debuginfo_100
    {IR(51002, 18), 165}, // DebugTypeFunction in nonsemantic_shader_debuginfo_100
    {IR(51107, 21), 169}, // DebugTypeInheritance in nonsemantic_shader_debuginfo_100
    {IR(53499, 16), 200}, // DebugTypeMatrix in nonsemantic_shader_debuginfo_100
    {IR(51091, 16), 168}, // DebugTypeMember in nonsemantic_shader_debuginfo_100
    {IR(50884, 17), 160}, // DebugTypePointer in nonsemantic_shader_debuginfo_100
    {IR(51128, 21), 170}, // DebugTypePtrToMember in nonsemantic_shader_debuginfo_100
    {IR(50939, 19), 161}, // DebugTypeQualifier in nonsemantic_shader_debuginfo_100
    {IR(51149, 18), 171}, // DebugTypeTemplate in nonsemantic_shader_debuginfo_100
    {IR(51167, 27), 172}, // DebugTypeTemplateParameter in nonsemantic_shader_debuginfo_100
    {IR(51229, 31), 174}, // DebugTypeTemplateParameterPack in nonsemantic_shader_debuginfo_100
    {IR(51194, 35), 173}, // DebugTypeTemplateTemplateParameter in nonsemantic_shader_debuginfo_100
    {IR(50973, 16), 163}, // DebugTypeVector in nonsemantic_shader_debuginfo_100
    {IR(50989, 13), 164}, // DebugTypedef in nonsemantic_shader_debuginfo_100
    {IR(51502, 11), 186}, // DebugValue in nonsemantic_shader_debuginfo_100
    {IR(53515, 14), 201}, // Configuration in nonsemantic_vkspreflection
    {IR(53591, 20), 206}, // DescriptorSetBuffer in nonsemantic_vkspreflection
    {IR(53611, 19), 207}, // DescriptorSetImage in nonsemantic_vkspreflection
    {IR(53630, 21), 208}, // DescriptorSetSampler in nonsemantic_vkspreflection
    {IR(53554, 14), 204}, // PushConstants in nonsemantic_vkspreflection
    {IR(53568, 23), 205}, // SpecializationMapEntry in nonsemantic_vkspreflection
    {IR(53529, 13), 202}, // StartCounter in nonsemantic_vkspreflection
    {IR(53542, 12), 203}, // StopCounter in nonsemantic_vkspreflection
    {IR(50762, 21), 210}, // DebugCompilationUnit in opencl_debuginfo_100
    {IR(51489, 13), 237}, // DebugDeclare in opencl_debuginfo_100
    {IR(51561, 16), 240}, // DebugExpression in opencl_debuginfo_100
    {IR(51305, 14), 229}, // DebugFunction in opencl_debuginfo_100
    {IR(51280, 25), 228}, // DebugFunctionDeclaration in opencl_debuginfo_100
    {IR(51260, 20), 227}, // DebugGlobalVariable in opencl_debuginfo_100
    {IR(53346, 20), 243}, // DebugImportedEntity in opencl_debuginfo_100
    {IR(50748, 14), 209}, // DebugInfoNone in opencl_debuginfo_100
    {IR(51392, 15), 234}, // DebugInlinedAt in opencl_debuginfo_100
    {IR(51468, 21), 236}, // DebugInlinedVariable in opencl_debuginfo_100
    {IR(51319, 18), 230}, // DebugLexicalBlock in opencl_debuginfo_100
    {IR(51337, 31), 231}, // DebugLexicalBlockDiscriminator in opencl_debuginfo_100
    {IR(51449, 19), 235}, // DebugLocalVariable in opencl_debuginfo_100
    {IR(51577, 14), 241}, // DebugMacroDef in opencl_debuginfo_100
    {IR(51591, 16), 242}, // DebugMacroUndef in opencl_debuginfo_100
    {IR(53951, 17), 245}, // DebugModuleINTEL in opencl_debuginfo_100
    {IR(51379, 13), 233}, // DebugNoScope in opencl_debuginfo_100
    {IR(51546, 15), 239}, // DebugOperation in opencl_debuginfo_100
    {IR(51368, 11), 232}, // DebugScope in opencl_debuginfo_100
    {IR(53366, 12), 244}, // DebugSource in opencl_debuginfo_100
    {IR(50958, 15), 214}, // DebugTypeArray in opencl_debuginfo_100
    {IR(50835, 15), 211}, // DebugTypeBasic in opencl_debuginfo_100
    {IR(51072, 19), 219}, // DebugTypeComposite in opencl_debuginfo_100
    {IR(51020, 14), 218}, // DebugTypeEnum in opencl_debuginfo_100
    {IR(51002, 18), 217}, // DebugTypeFunction in opencl_debuginfo_100
    {IR(51107, 21), 221}, // DebugTypeInheritance in opencl_debuginfo_100
    {IR(51091, 16), 220}, // DebugTypeMember in opencl_debuginfo_100
    {IR(50884, 17), 212}, // DebugTypePointer in opencl_debuginfo_100
    {IR(51128, 21), 222}, // DebugTypePtrToMember in opencl_debuginfo_100
    {IR(50939, 19), 213}, // DebugTypeQualifier in opencl_debuginfo_100
    {IR(51149, 18), 223}, // DebugTypeTemplate in opencl_debuginfo_100
    {IR(51167, 27), 224}, // DebugTypeTemplateParameter in opencl_debuginfo_100
    {IR(51229, 31), 226}, // DebugTypeTemplateParameterPack in opencl_debuginfo_100
    {IR(51194, 35), 225}, // DebugTypeTemplateTemplateParameter in opencl_debuginfo_100
    {IR(50973, 16), 215}, // DebugTypeVector in opencl_debuginfo_100
    {IR(50989, 13), 216}, // DebugTypedef in opencl_debuginfo_100
    {IR(51502, 11), 238}, // DebugValue in opencl_debuginfo_100
    {IR(53968, 5), 246}, // acos in opencl_std_100
    {IR(53973, 6), 247}, // acosh in opencl_std_100
    {IR(53979, 7), 248}, // acospi in opencl_std_100
    {IR(53986, 5), 249}, // asin in opencl_std_100
    {IR(53991, 6), 250}, // asinh in opencl_std_100
    {IR(53997, 7), 251}, // asinpi in opencl_std_100
    {IR(54004, 5), 252}, // atan in opencl_std_100
    {IR(54009, 6), 253}, // atan2 in opencl_std_100
    {IR(54028, 8), 256}, // atan2pi in opencl_std_100
    {IR(54015, 6), 254}, // atanh in opencl_std_100
    {IR(54021, 7), 255}, // atanpi in opencl_std_100
    {IR(55219, 10), 402}, // bitselect in opencl_std_100
    {IR(54036, 5), 257}, // cbrt in opencl_std_100
    {IR(54041, 5), 258}, // ceil in opencl_std_100
    {IR(54891, 4), 367}, // clz in opencl_std_100
    {IR(54046, 9), 259}, // copysign in opencl_std_100
    {IR(54055, 4), 260}, // cos in opencl_std_100
    {IR(54059, 5), 261}, // cosh in opencl_std_100
    {IR(54064, 6), 262}, // cospi in opencl_std_100
    {IR(54735, 6), 350}, // cross in opencl_std_100
    {IR(54895, 4), 368}, // ctz in opencl_std_100
    {IR(54670, 8), 342}, // degrees in opencl_std_100
    {IR(54741, 9), 351}, // distance in opencl_std_100
    {IR(54075, 4), 264}, // erf in opencl_std_100
    {IR(54070, 5), 263}, // erfc in opencl_std_100
    {IR(54079, 4), 265}, // exp in opencl_std_100
    {IR(54088, 6), 267}, // exp10 in opencl_std_100
    {IR(54083, 5), 266}, // exp2 in opencl_std_100
    {IR(54094, 6), 268}, // expm1 in opencl_std_100
    {IR(54100, 5), 269}, // fabs in opencl_std_100
    {IR(54767, 14), 354}, // fast_distance in opencl_std_100
    {IR(54781, 12), 355}, // fast_length in opencl_std_100
    {IR(54793, 15), 356}, // fast_normalize in opencl_std_100
    {IR(54663, 7), 341}, // fclamp in opencl_std_100
    {IR(54105, 5), 270}, // fdim in opencl_std_100
    {IR(54110, 6), 271}, // floor in opencl_std_100
    {IR(54116, 4), 272}, // fma in opencl_std_100
    {IR(54120, 5), 273}, // fmax in opencl_std_100
    {IR(54678, 12), 343}, // fmax_common in opencl_std_100
    {IR(54125, 5), 274}, // fmin in opencl_std_100
    {IR(54690, 12), 344}, // fmin_common in opencl_std_100
    {IR(54130, 5), 275}, // fmod in opencl_std_100
    {IR(54135, 6), 276}, // fract in opencl_std_100
    {IR(54141, 6), 277}, // frexp in opencl_std_100
    {IR(54353, 9), 313}, // half_cos in opencl_std_100
    {IR(54362, 12), 314}, // half_divide in opencl_std_100
    {IR(54374, 9), 315}, // half_exp in opencl_std_100
    {IR(54393, 11), 317}, // half_exp10 in opencl_std_100
    {IR(54383, 10), 316}, // half_exp2 in opencl_std_100
    {IR(54404, 9), 318}, // half_log in opencl_std_100
    {IR(54423, 11), 320}, // half_log10 in opencl_std_100
    {IR(54413, 10), 319}, // half_log2 in opencl_std_100
    {IR(54434, 10), 321}, // half_powr in opencl_std_100
    {IR(54444, 11), 322}, // half_recip in opencl_std_100
    {IR(54455, 11), 323}, // half_rsqrt in opencl_std_100
    {IR(54466, 9), 324}, // half_sin in opencl_std_100
    {IR(54475, 10), 325}, // half_sqrt in opencl_std_100
    {IR(54485, 9), 326}, // half_tan in opencl_std_100
    {IR(54147, 6), 278}, // hypot in opencl_std_100
    {IR(54153, 6), 279}, // ilogb in opencl_std_100
    {IR(54159, 6), 280}, // ldexp in opencl_std_100
    {IR(54750, 7), 352}, // length in opencl_std_100
    {IR(54165, 7), 281}, // lgamma in opencl_std_100
    {IR(54172, 9), 282}, // lgamma_r in opencl_std_100
    {IR(54181, 4), 283}, // log in opencl_std_100
    {IR(54190, 6), 285}, // log10 in opencl_std_100
    {IR(54196, 6), 286}, // log1p in opencl_std_100
    {IR(54185, 5), 284}, // log2 in opencl_std_100
    {IR(54202, 5), 287}, // logb in opencl_std_100
    {IR(54207, 4), 288}, // mad in opencl_std_100
    {IR(54211, 7), 289}, // maxmag in opencl_std_100
    {IR(54218, 7), 290}, // minmag in opencl_std_100
    {IR(54702, 4), 345}, // mix in opencl_std_100
    {IR(54225, 5), 291}, // modf in opencl_std_100
    {IR(54230, 4), 292}, // nan in opencl_std_100
    {IR(54494, 11), 327}, // native_cos in opencl_std_100
    {IR(54505, 14), 328}, // native_divide in opencl_std_100
    {IR(54519, 11), 329}, // native_exp in opencl_std_100
    {IR(54542, 13), 331}, // native_exp10 in opencl_std_100
    {IR(54530, 12), 330}, // native_exp2 in opencl_std_100
    {IR(54555, 11), 332}, // native_log in opencl_std_100
    {IR(54578, 13), 334}, // native_log10 in opencl_std_100
    {IR(54566, 12), 333}, // native_log2 in opencl_std_100
    {IR(54591, 12), 335}, // native_powr in opencl_std_100
    {IR(54603, 13), 336}, // native_recip in opencl_std_100
    {IR(54616, 13), 337}, // native_rsqrt in opencl_std_100
    {IR(54629, 11), 338}, // native_sin in opencl_std_100
    {IR(54640, 12), 339}, // native_sqrt in opencl_std_100
    {IR(54652, 11), 340}, // native_tan in opencl_std_100
    {IR(54234, 10), 293}, // nextafter in opencl_std_100
    {IR(54757, 10), 353}, // normalize in opencl_std_100
    {IR(55010, 9), 382}, // popcount in opencl_std_100
    {IR(54244, 4), 294}, // pow in opencl_std_100
    {IR(54248, 5), 295}, // pown in opencl_std_100
    {IR(54253, 5), 296}, // powr in opencl_std_100
    {IR(55210, 9), 401}, // prefetch in opencl_std_100
    {IR(55203, 7), 400}, // printf in opencl_std_100
    {IR(54706, 8), 346}, // radians in opencl_std_100
    {IR(54258, 10), 297}, // remainder in opencl_std_100
    {IR(54268, 7), 298}, // remquo in opencl_std_100
    {IR(54275, 5), 299}, // rint in opencl_std_100
    {IR(54280, 6), 300}, // rootn in opencl_std_100
    {IR(54961, 7), 377}, // rotate in opencl_std_100
    {IR(54286, 6), 301}, // round in opencl_std_100
    {IR(54292, 6), 302}, // rsqrt in opencl_std_100
    {IR(54808, 6), 357}, // s_abs in opencl_std_100
    {IR(54814, 11), 358}, // s_abs_diff in opencl_std_100
    {IR(54825, 10), 359}, // s_add_sat in opencl_std_100
    {IR(54875, 8), 365}, // s_clamp in opencl_std_100
    {IR(54845, 7), 361}, // s_hadd in opencl_std_100
    {IR(55019, 8), 383}, // s_mad24 in opencl_std_100
    {IR(54899, 9), 369}, // s_mad_hi in opencl_std_100
    {IR(54918, 10), 371}, // s_mad_sat in opencl_std_100
    {IR(54928, 6), 372}, // s_max in opencl_std_100
    {IR(54940, 6), 374}, // s_min in opencl_std_100
    {IR(55035, 8), 385}, // s_mul24 in opencl_std_100
    {IR(54952, 9), 376}, // s_mul_hi in opencl_std_100
    {IR(54859, 8), 363}, // s_rhadd in opencl_std_100
    {IR(54968, 10), 378}, // s_sub_sat in opencl_std_100
    {IR(54999, 11), 381}, // s_upsample in opencl_std_100
    {IR(55229, 7), 403}, // select in opencl_std_100
    {IR(55186, 8), 398}, // shuffle in opencl_std_100
    {IR(55194, 9), 399}, // shuffle2 in opencl_std_100
    {IR(54730, 5), 349}, // sign in opencl_std_100
    {IR(54298, 4), 303}, // sin in opencl_std_100
    {IR(54302, 7), 304}, // sincos in opencl_std_100
    {IR(54309, 5), 305}, // sinh in opencl_std_100
    {IR(54314, 6), 306}, // sinpi in opencl_std_100
    {IR(54719, 11), 348}, // smoothstep in opencl_std_100
    {IR(54320, 5), 307}, // sqrt in opencl_std_100
    {IR(54714, 5), 347}, // step in opencl_std_100
    {IR(54325, 4), 308}, // tan in opencl_std_100
    {IR(54329, 5), 309}, // tanh in opencl_std_100
    {IR(54334, 6), 310}, // tanpi in opencl_std_100
    {IR(54340, 7), 311}, // tgamma in opencl_std_100
    {IR(54347, 6), 312}, // trunc in opencl_std_100
    {IR(55236, 6), 404}, // u_abs in opencl_std_100
    {IR(55242, 11), 405}, // u_abs_diff in opencl_std_100
    {IR(54835, 10), 360}, // u_add_sat in opencl_std_100
    {IR(54883, 8), 366}, // u_clamp in opencl_std_100
    {IR(54852, 7), 362}, // u_hadd in opencl_std_100
    {IR(55027, 8), 384}, // u_mad24 in opencl_std_100
    {IR(55262, 9), 407}, // u_mad_hi in opencl_std_100
    {IR(54908, 10), 370}, // u_mad_sat in opencl_std_100
    {IR(54934, 6), 373}, // u_max in opencl_std_100
    {IR(54946, 6), 375}, // u_min in opencl_std_100
    {IR(55043, 8), 386}, // u_mul24 in opencl_std_100
    {IR(55253, 9), 406}, // u_mul_hi in opencl_std_100
    {IR(54867, 8), 364}, // u_rhadd in opencl_std_100
    {IR(54978, 10), 379}, // u_sub_sat in opencl_std_100
    {IR(54988, 11), 380}, // u_upsample in opencl_std_100
    {IR(55066, 11), 389}, // vload_half in opencl_std_100
    {IR(55077, 12), 390}, // vload_halfn in opencl_std_100
    {IR(55143, 13), 395}, // vloada_halfn in opencl_std_100
    {IR(55051, 7), 387}, // vloadn in opencl_std_100
    {IR(55089, 12), 391}, // vstore_half in opencl_std_100
    {IR(55101, 14), 392}, // vstore_half_r in opencl_std_100
    {IR(55115, 13), 393}, // vstore_halfn in opencl_std_100
    {IR(55128, 15), 394}, // vstore_halfn_r in opencl_std_100
    {IR(55156, 14), 396}, // vstorea_halfn in opencl_std_100
    {IR(55170, 16), 397}, // vstorea_halfn_r in opencl_std_100
    {IR(55058, 8), 388}, // vstoren in opencl_std_100
    {IR(55288, 17), 409}, // CubeFaceCoordAMD in spv_amd_gcn_shader
    {IR(55271, 17), 408}, // CubeFaceIndexAMD in spv_amd_gcn_shader
    {IR(55305, 8), 410}, // TimeAMD in spv_amd_gcn_shader
    {IR(55382, 9), 414}, // MbcntAMD in spv_amd_shader_ballot
    {IR(55313, 22), 411}, // SwizzleInvocationsAMD in spv_amd_shader_ballot
    {IR(55335, 28), 412}, // SwizzleInvocationsMaskedAMD in spv_amd_shader_ballot
    {IR(55363, 19), 413}, // WriteInvocationAMD in spv_amd_shader_ballot
    {IR(55391, 23), 415}, // InterpolateAtVertexAMD in spv_amd_shader_explicit_vertex_parameter
    {IR(55441, 9), 419}, // FMax3AMD in spv_amd_shader_trinary_minmax
    {IR(55468, 9), 422}, // FMid3AMD in spv_amd_shader_trinary_minmax
    {IR(55414, 9), 416}, // FMin3AMD in spv_amd_shader_trinary_minmax
    {IR(55459, 9), 421}, // SMax3AMD in spv_amd_shader_trinary_minmax
    {IR(55486, 9), 424}, // SMid3AMD in spv_amd_shader_trinary_minmax
    {IR(55432, 9), 418}, // SMin3AMD in spv_amd_shader_trinary_minmax
    {IR(55450, 9), 420}, // UMax3AMD in spv_amd_shader_trinary_minmax
    {IR(55477, 9), 423}, // UMid3AMD in spv_amd_shader_trinary_minmax
    {IR(55423, 9), 417}, // UMin3AMD in spv_amd_shader_trinary_minmax
}};

IndexRange ExtInstNameRangeForKind(spv_ext_inst_type_t type) {
  switch(type) {
    case SPV_EXT_INST_TYPE_DEBUGINFO: return IR(0, 34);
    case SPV_EXT_INST_TYPE_GLSL_STD_450: return IR(34, 81);
    case SPV_EXT_INST_TYPE_NONSEMANTIC_CLSPVREFLECTION: return IR(115, 42);
    case SPV_EXT_INST_TYPE_NONSEMANTIC_SHADER_DEBUGINFO_100: return IR(157, 44);
    case SPV_EXT_INST_TYPE_NONSEMANTIC_VKSPREFLECTION: return IR(201, 8);
    case SPV_EXT_INST_TYPE_OPENCL_DEBUGINFO_100: return IR(209, 37);
    case SPV_EXT_INST_TYPE_OPENCL_STD: return IR(246, 162);
    case SPV_EXT_INST_TYPE_SPV_AMD_GCN_SHADER: return IR(408, 3);
    case SPV_EXT_INST_TYPE_SPV_AMD_SHADER_BALLOT: return IR(411, 4);
    case SPV_EXT_INST_TYPE_SPV_AMD_SHADER_EXPLICIT_VERTEX_PARAMETER: return IR(415, 1);
    case SPV_EXT_INST_TYPE_SPV_AMD_SHADER_TRINARY_MINMAX: return IR(416, 9);
    default: break;
  }
  return IR(0,0);
}

// Array of characters, referenced by IndexRanges elsewhere.
// Each IndexRange denotes a string.
static const char kStrings[] =
  "SPV_ALTERA_arbitrary_precision_fixed_point\0" // IR(0, 43)
  "SPV_ALTERA_arbitrary_precision_floating_point\0" // IR(43, 46)
  "SPV_ALTERA_arbitrary_precision_integers\0" // IR(89, 40)
  "SPV_ALTERA_blocking_pipes\0" // IR(129, 26)
  "SPV_ALTERA_fpga_argument_interfaces\0" // IR(155, 36)
  "SPV_ALTERA_fpga_buffer_location\0" // IR(191, 32)
  "SPV_ALTERA_fpga_cluster_attributes\0" // IR(223, 35)
  "SPV_ALTERA_fpga_dsp_control\0" // IR(258, 28)
  "SPV_ALTERA_fpga_invocation_pipelining_attributes\0" // IR(286, 49)
  "SPV_ALTERA_fpga_latency_control\0" // IR(335, 32)
  "SPV_ALTERA_fpga_loop_controls\0" // IR(367, 30)
  "SPV_ALTERA_fpga_memory_accesses\0" // IR(397, 32)
  "SPV_ALTERA_fpga_memory_attributes\0" // IR(429, 34)
  "SPV_ALTERA_fpga_reg\0" // IR(463, 20)
  "SPV_ALTERA_global_variable_fpga_decorations\0" // IR(483, 44)
  "SPV_ALTERA_io_pipes\0" // IR(527, 20)
  "SPV_ALTERA_loop_fuse\0" // IR(547, 21)
  "SPV_ALTERA_runtime_aligned\0" // IR(568, 27)
  "SPV_ALTERA_task_sequence\0" // IR(595, 25)
  "SPV_ALTERA_usm_storage_classes\0" // IR(620, 31)
  "SPV_AMDX_shader_enqueue\0" // IR(651, 24)
  "SPV_AMD_gcn_shader\0" // IR(675, 19)
  "SPV_AMD_gpu_shader_half_float\0" // IR(694, 30)
  "SPV_AMD_gpu_shader_half_float_fetch\0" // IR(724, 36)
  "SPV_AMD_gpu_shader_int16\0" // IR(760, 25)
  "SPV_AMD_shader_ballot\0" // IR(785, 22)
  "SPV_AMD_shader_early_and_late_fragment_tests\0" // IR(807, 45)
  "SPV_AMD_shader_explicit_vertex_parameter\0" // IR(852, 41)
  "SPV_AMD_shader_fragment_mask\0" // IR(893, 29)
  "SPV_AMD_shader_image_load_store_lod\0" // IR(922, 36)
  "SPV_AMD_shader_trinary_minmax\0" // IR(958, 30)
  "SPV_AMD_texture_gather_bias_lod\0" // IR(988, 32)
  "SPV_ARM_cooperative_matrix_layouts\0" // IR(1020, 35)
  "SPV_ARM_core_builtins\0" // IR(1055, 22)
  "SPV_ARM_graph\0" // IR(1077, 14)
  "SPV_ARM_tensors\0" // IR(1091, 16)
  "SPV_EXT_arithmetic_fence\0" // IR(1107, 25)
  "SPV_EXT_demote_to_helper_invocation\0" // IR(1132, 36)
  "SPV_EXT_descriptor_heap\0" // IR(1168, 24)
  "SPV_EXT_descriptor_indexing\0" // IR(1192, 28)
  "SPV_EXT_float8\0" // IR(1220, 15)
  "SPV_EXT_fragment_fully_covered\0" // IR(1235, 31)
  "SPV_EXT_fragment_invocation_density\0" // IR(1266, 36)
  "SPV_EXT_fragment_shader_interlock\0" // IR(1302, 34)
  "SPV_EXT_long_vector\0" // IR(1336, 20)
  "SPV_EXT_mesh_shader\0" // IR(1356, 20)
  "SPV_EXT_opacity_micromap\0" // IR(1376, 25)
  "SPV_EXT_optnone\0" // IR(1401, 16)
  "SPV_EXT_physical_storage_buffer\0" // IR(1417, 32)
  "SPV_EXT_relaxed_printf_string_address_space\0" // IR(1449, 44)
  "SPV_EXT_replicated_composites\0" // IR(1493, 30)
  "SPV_EXT_shader_64bit_indexing\0" // IR(1523, 30)
  "SPV_EXT_shader_atomic_float16_add\0" // IR(1553, 34)
  "SPV_EXT_shader_atomic_float_add\0" // IR(1587, 32)
  "SPV_EXT_shader_atomic_float_min_max\0" // IR(1619, 36)
  "SPV_EXT_shader_image_int64\0" // IR(1655, 27)
  "SPV_EXT_shader_invocation_reorder\0" // IR(1682, 34)
  "SPV_EXT_shader_stencil_export\0" // IR(1716, 30)
  "SPV_EXT_shader_subgroup_partitioned\0" // IR(1746, 36)
  "SPV_EXT_shader_tile_image\0" // IR(1782, 26)
  "SPV_EXT_shader_viewport_index_layer\0" // IR(1808, 36)
  "SPV_GOOGLE_decorate_string\0" // IR(1844, 27)
  "SPV_GOOGLE_hlsl_functionality1\0" // IR(1871, 31)
  "SPV_GOOGLE_user_type\0" // IR(1902, 21)
  "SPV_INTEL_2d_block_io\0" // IR(1923, 22)
  "SPV_INTEL_arbitrary_precision_fixed_point\0" // IR(1945, 42)
  "SPV_INTEL_arbitrary_precision_floating_point\0" // IR(1987, 45)
  "SPV_INTEL_arbitrary_precision_integers\0" // IR(2032, 39)
  "SPV_INTEL_bfloat16_conversion\0" // IR(2071, 30)
  "SPV_INTEL_bindless_images\0" // IR(2101, 26)
  "SPV_INTEL_blocking_pipes\0" // IR(2127, 25)
  "SPV_INTEL_cache_controls\0" // IR(2152, 25)
  "SPV_INTEL_debug_module\0" // IR(2177, 23)
  "SPV_INTEL_device_side_avc_motion_estimation\0" // IR(2200, 44)
  "SPV_INTEL_float_controls2\0" // IR(2244, 26)
  "SPV_INTEL_fp_fast_math_mode\0" // IR(2270, 28)
  "SPV_INTEL_fp_max_error\0" // IR(2298, 23)
  "SPV_INTEL_fpga_argument_interfaces\0" // IR(2321, 35)
  "SPV_INTEL_fpga_buffer_location\0" // IR(2356, 31)
  "SPV_INTEL_fpga_cluster_attributes\0" // IR(2387, 34)
  "SPV_INTEL_fpga_dsp_control\0" // IR(2421, 27)
  "SPV_INTEL_fpga_invocation_pipelining_attributes\0" // IR(2448, 48)
  "SPV_INTEL_fpga_latency_control\0" // IR(2496, 31)
  "SPV_INTEL_fpga_loop_controls\0" // IR(2527, 29)
  "SPV_INTEL_fpga_memory_accesses\0" // IR(2556, 31)
  "SPV_INTEL_fpga_memory_attributes\0" // IR(2587, 33)
  "SPV_INTEL_fpga_reg\0" // IR(2620, 19)
  "SPV_INTEL_function_pointers\0" // IR(2639, 28)
  "SPV_INTEL_function_variants\0" // IR(2667, 28)
  "SPV_INTEL_global_variable_fpga_decorations\0" // IR(2695, 43)
  "SPV_INTEL_global_variable_host_access\0" // IR(2738, 38)
  "SPV_INTEL_inline_assembly\0" // IR(2776, 26)
  "SPV_INTEL_int4\0" // IR(2802, 15)
  "SPV_INTEL_io_pipes\0" // IR(2817, 19)
  "SPV_INTEL_kernel_attributes\0" // IR(2836, 28)
  "SPV_INTEL_long_composites\0" // IR(2864, 26)
  "SPV_INTEL_loop_fuse\0" // IR(2890, 20)
  "SPV_INTEL_masked_gather_scatter\0" // IR(2910, 32)
  "SPV_INTEL_maximum_registers\0" // IR(2942, 28)
  "SPV_INTEL_media_block_io\0" // IR(2970, 25)
  "SPV_INTEL_memory_access_aliasing\0" // IR(2995, 33)
  "SPV_INTEL_optnone\0" // IR(3028, 18)
  "SPV_INTEL_runtime_aligned\0" // IR(3046, 26)
  "SPV_INTEL_shader_integer_functions2\0" // IR(3072, 36)
  "SPV_INTEL_split_barrier\0" // IR(3108, 24)
  "SPV_INTEL_subgroup_buffer_prefetch\0" // IR(3132, 35)
  "SPV_INTEL_subgroup_matrix_multiply_accumulate\0" // IR(3167, 46)
  "SPV_INTEL_subgroups\0" // IR(3213, 20)
  "SPV_INTEL_task_sequence\0" // IR(3233, 24)
  "SPV_INTEL_tensor_float32_conversion\0" // IR(3257, 36)
  "SPV_INTEL_ternary_bitwise_function\0" // IR(3293, 35)
  "SPV_INTEL_unstructured_loop_controls\0" // IR(3328, 37)
  "SPV_INTEL_usm_storage_classes\0" // IR(3365, 30)
  "SPV_INTEL_variable_length_array\0" // IR(3395, 32)
  "SPV_INTEL_vector_compute\0" // IR(3427, 25)
  "SPV_KHR_16bit_storage\0" // IR(3452, 22)
  "SPV_KHR_8bit_storage\0" // IR(3474, 21)
  "SPV_KHR_bfloat16\0" // IR(3495, 17)
  "SPV_KHR_bit_instructions\0" // IR(3512, 25)
  "SPV_KHR_compute_shader_derivatives\0" // IR(3537, 35)
  "SPV_KHR_cooperative_matrix\0" // IR(3572, 27)
  "SPV_KHR_device_group\0" // IR(3599, 21)
  "SPV_KHR_expect_assume\0" // IR(3620, 22)
  "SPV_KHR_float_controls\0" // IR(3642, 23)
  "SPV_KHR_float_controls2\0" // IR(3665, 24)
  "SPV_KHR_fma\0" // IR(3689, 12)
  "SPV_KHR_fragment_shader_barycentric\0" // IR(3701, 36)
  "SPV_KHR_fragment_shading_rate\0" // IR(3737, 30)
  "SPV_KHR_integer_dot_product\0" // IR(3767, 28)
  "SPV_KHR_linkonce_odr\0" // IR(3795, 21)
  "SPV_KHR_maximal_reconvergence\0" // IR(3816, 30)
  "SPV_KHR_multiview\0" // IR(3846, 18)
  "SPV_KHR_no_integer_wrap_decoration\0" // IR(3864, 35)
  "SPV_KHR_non_semantic_info\0" // IR(3899, 26)
  "SPV_KHR_physical_storage_buffer\0" // IR(3925, 32)
  "SPV_KHR_post_depth_coverage\0" // IR(3957, 28)
  "SPV_KHR_quad_control\0" // IR(3985, 21)
  "SPV_KHR_ray_cull_mask\0" // IR(4006, 22)
  "SPV_KHR_ray_query\0" // IR(4028, 18)
  "SPV_KHR_ray_tracing\0" // IR(4046, 20)
  "SPV_KHR_ray_tracing_position_fetch\0" // IR(4066, 35)
  "SPV_KHR_relaxed_extended_instruction\0" // IR(4101, 37)
  "SPV_KHR_shader_atomic_counter_ops\0" // IR(4138, 34)
  "SPV_KHR_shader_ballot\0" // IR(4172, 22)
  "SPV_KHR_shader_clock\0" // IR(4194, 21)
  "SPV_KHR_shader_draw_parameters\0" // IR(4215, 31)
  "SPV_KHR_storage_buffer_storage_class\0" // IR(4246, 37)
  "SPV_KHR_subgroup_rotate\0" // IR(4283, 24)
  "SPV_KHR_subgroup_uniform_control_flow\0" // IR(4307, 38)
  "SPV_KHR_subgroup_vote\0" // IR(4345, 22)
  "SPV_KHR_terminate_invocation\0" // IR(4367, 29)
  "SPV_KHR_uniform_group_instructions\0" // IR(4396, 35)
  "SPV_KHR_untyped_pointers\0" // IR(4431, 25)
  "SPV_KHR_variable_pointers\0" // IR(4456, 26)
  "SPV_KHR_vulkan_memory_model\0" // IR(4482, 28)
  "SPV_KHR_workgroup_memory_explicit_layout\0" // IR(4510, 41)
  "SPV_NVX_multiview_per_view_attributes\0" // IR(4551, 38)
  "SPV_NV_bindless_texture\0" // IR(4589, 24)
  "SPV_NV_cluster_acceleration_structure\0" // IR(4613, 38)
  "SPV_NV_compute_shader_derivatives\0" // IR(4651, 34)
  "SPV_NV_cooperative_matrix\0" // IR(4685, 26)
  "SPV_NV_cooperative_matrix2\0" // IR(4711, 27)
  "SPV_NV_cooperative_vector\0" // IR(4738, 26)
  "SPV_NV_displacement_micromap\0" // IR(4764, 29)
  "SPV_NV_fragment_shader_barycentric\0" // IR(4793, 35)
  "SPV_NV_geometry_shader_passthrough\0" // IR(4828, 35)
  "SPV_NV_linear_swept_spheres\0" // IR(4863, 28)
  "SPV_NV_mesh_shader\0" // IR(4891, 19)
  "SPV_NV_push_constant_bank\0" // IR(4910, 26)
  "SPV_NV_raw_access_chains\0" // IR(4936, 25)
  "SPV_NV_ray_tracing\0" // IR(4961, 19)
  "SPV_NV_ray_tracing_motion_blur\0" // IR(4980, 31)
  "SPV_NV_sample_mask_override_coverage\0" // IR(5011, 37)
  "SPV_NV_shader_atomic_fp16_vector\0" // IR(5048, 33)
  "SPV_NV_shader_image_footprint\0" // IR(5081, 30)
  "SPV_NV_shader_invocation_reorder\0" // IR(5111, 33)
  "SPV_NV_shader_sm_builtins\0" // IR(5144, 26)
  "SPV_NV_shader_subgroup_partitioned\0" // IR(5170, 35)
  "SPV_NV_shading_rate\0" // IR(5205, 20)
  "SPV_NV_stereo_view_rendering\0" // IR(5225, 29)
  "SPV_NV_tensor_addressing\0" // IR(5254, 25)
  "SPV_NV_viewport_array2\0" // IR(5279, 23)
  "SPV_QCOM_cooperative_matrix_conversion\0" // IR(5302, 39)
  "SPV_QCOM_image_processing\0" // IR(5341, 26)
  "SPV_QCOM_image_processing2\0" // IR(5367, 27)
  "SPV_QCOM_tile_shading\0" // IR(5394, 22)
  "SPV_VALIDATOR_ignore_type_decl_unique\0" // IR(5416, 38)
  "SPV_VALVE_mixed_float_dot_product\0" // IR(5454, 34)
  "ReadOnly\0" // IR(5488, 9)
  "Kernel\0" // IR(5497, 7)
  "WriteOnly\0" // IR(5504, 10)
  "ReadWrite\0" // IR(5514, 10)
  "Logical\0" // IR(5524, 8)
  "Physical32\0" // IR(5532, 11)
  "Addresses\0" // IR(5543, 10)
  "Physical64\0" // IR(5553, 11)
  "PhysicalStorageBuffer64\0" // IR(5564, 24)
  "PhysicalStorageBuffer64EXT\0" // IR(5588, 27)
  "PhysicalStorageBufferAddresses\0" // IR(5615, 31)
  "Position\0" // IR(5646, 9)
  "Shader\0" // IR(5655, 7)
  "PointSize\0" // IR(5662, 10)
  "ClipDistance\0" // IR(5672, 13)
  "CullDistance\0" // IR(5685, 13)
  "VertexId\0" // IR(5698, 9)
  "InstanceId\0" // IR(5707, 11)
  "PrimitiveId\0" // IR(5718, 12)
  "Geometry\0" // IR(5730, 9)
  "Tessellation\0" // IR(5739, 13)
  "RayTracingNV\0" // IR(5752, 13)
  "RayTracingKHR\0" // IR(5765, 14)
  "MeshShadingNV\0" // IR(5779, 14)
  "MeshShadingEXT\0" // IR(5793, 15)
  "InvocationId\0" // IR(5808, 13)
  "Layer\0" // IR(5821, 6)
  "ShaderLayer\0" // IR(5827, 12)
  "ShaderViewportIndexLayerEXT\0" // IR(5839, 28)
  "ViewportIndex\0" // IR(5867, 14)
  "MultiViewport\0" // IR(5881, 14)
  "ShaderViewportIndex\0" // IR(5895, 20)
  "TessLevelOuter\0" // IR(5915, 15)
  "TessLevelInner\0" // IR(5930, 15)
  "TessCoord\0" // IR(5945, 10)
  "PatchVertices\0" // IR(5955, 14)
  "FragCoord\0" // IR(5969, 10)
  "PointCoord\0" // IR(5979, 11)
  "FrontFacing\0" // IR(5990, 12)
  "SampleId\0" // IR(6002, 9)
  "SampleRateShading\0" // IR(6011, 18)
  "SamplePosition\0" // IR(6029, 15)
  "SampleMask\0" // IR(6044, 11)
  "FragDepth\0" // IR(6055, 10)
  "HelperInvocation\0" // IR(6065, 17)
  "NumWorkgroups\0" // IR(6082, 14)
  "WorkgroupSize\0" // IR(6096, 14)
  "WorkgroupId\0" // IR(6110, 12)
  "LocalInvocationId\0" // IR(6122, 18)
  "GlobalInvocationId\0" // IR(6140, 19)
  "LocalInvocationIndex\0" // IR(6159, 21)
  "WorkDim\0" // IR(6180, 8)
  "GlobalSize\0" // IR(6188, 11)
  "EnqueuedWorkgroupSize\0" // IR(6199, 22)
  "GlobalOffset\0" // IR(6221, 13)
  "GlobalLinearId\0" // IR(6234, 15)
  "SubgroupSize\0" // IR(6249, 13)
  "GroupNonUniform\0" // IR(6262, 16)
  "SubgroupBallotKHR\0" // IR(6278, 18)
  "SubgroupMaxSize\0" // IR(6296, 16)
  "NumSubgroups\0" // IR(6312, 13)
  "NumEnqueuedSubgroups\0" // IR(6325, 21)
  "SubgroupId\0" // IR(6346, 11)
  "SubgroupLocalInvocationId\0" // IR(6357, 26)
  "VertexIndex\0" // IR(6383, 12)
  "InstanceIndex\0" // IR(6395, 14)
  "CoreIDARM\0" // IR(6409, 10)
  "CoreBuiltinsARM\0" // IR(6419, 16)
  "CoreCountARM\0" // IR(6435, 13)
  "CoreMaxIDARM\0" // IR(6448, 13)
  "WarpIDARM\0" // IR(6461, 10)
  "WarpMaxIDARM\0" // IR(6471, 13)
  "SubgroupEqMask\0" // IR(6484, 15)
  "SubgroupEqMaskKHR\0" // IR(6499, 18)
  "GroupNonUniformBallot\0" // IR(6517, 22)
  "SubgroupGeMask\0" // IR(6539, 15)
  "SubgroupGeMaskKHR\0" // IR(6554, 18)
  "SubgroupGtMask\0" // IR(6572, 15)
  "SubgroupGtMaskKHR\0" // IR(6587, 18)
  "SubgroupLeMask\0" // IR(6605, 15)
  "SubgroupLeMaskKHR\0" // IR(6620, 18)
  "SubgroupLtMask\0" // IR(6638, 15)
  "SubgroupLtMaskKHR\0" // IR(6653, 18)
  "BaseVertex\0" // IR(6671, 11)
  "DrawParameters\0" // IR(6682, 15)
  "BaseInstance\0" // IR(6697, 13)
  "DrawIndex\0" // IR(6710, 10)
  "PrimitiveShadingRateKHR\0" // IR(6720, 24)
  "FragmentShadingRateKHR\0" // IR(6744, 23)
  "DeviceIndex\0" // IR(6767, 12)
  "DeviceGroup\0" // IR(6779, 12)
  "ViewIndex\0" // IR(6791, 10)
  "MultiView\0" // IR(6801, 10)
  "ShadingRateKHR\0" // IR(6811, 15)
  "TileOffsetQCOM\0" // IR(6826, 15)
  "TileShadingQCOM\0" // IR(6841, 16)
  "TileDimensionQCOM\0" // IR(6857, 18)
  "TileApronSizeQCOM\0" // IR(6875, 18)
  "BaryCoordNoPerspAMD\0" // IR(6893, 20)
  "BaryCoordNoPerspCentroidAMD\0" // IR(6913, 28)
  "BaryCoordNoPerspSampleAMD\0" // IR(6941, 26)
  "BaryCoordSmoothAMD\0" // IR(6967, 19)
  "BaryCoordSmoothCentroidAMD\0" // IR(6986, 27)
  "BaryCoordSmoothSampleAMD\0" // IR(7013, 25)
  "BaryCoordPullModelAMD\0" // IR(7038, 22)
  "FragStencilRefEXT\0" // IR(7060, 18)
  "StencilExportEXT\0" // IR(7078, 17)
  "RemainingRecursionLevelsAMDX\0" // IR(7095, 29)
  "ShaderEnqueueAMDX\0" // IR(7124, 18)
  "ShaderIndexAMDX\0" // IR(7142, 16)
  "SamplerHeapEXT\0" // IR(7158, 15)
  "DescriptorHeapEXT\0" // IR(7173, 18)
  "ResourceHeapEXT\0" // IR(7191, 16)
  "ViewportMaskNV\0" // IR(7207, 15)
  "ShaderViewportMaskNV\0" // IR(7222, 21)
  "SecondaryPositionNV\0" // IR(7243, 20)
  "ShaderStereoViewNV\0" // IR(7263, 19)
  "SecondaryViewportMaskNV\0" // IR(7282, 24)
  "PositionPerViewNV\0" // IR(7306, 18)
  "PerViewAttributesNV\0" // IR(7324, 20)
  "ViewportMaskPerViewNV\0" // IR(7344, 22)
  "FullyCoveredEXT\0" // IR(7366, 16)
  "FragmentFullyCoveredEXT\0" // IR(7382, 24)
  "TaskCountNV\0" // IR(7406, 12)
  "PrimitiveCountNV\0" // IR(7418, 17)
  "PrimitiveIndicesNV\0" // IR(7435, 19)
  "ClipDistancePerViewNV\0" // IR(7454, 22)
  "CullDistancePerViewNV\0" // IR(7476, 22)
  "LayerPerViewNV\0" // IR(7498, 15)
  "MeshViewCountNV\0" // IR(7513, 16)
  "MeshViewIndicesNV\0" // IR(7529, 18)
  "BaryCoordKHR\0" // IR(7547, 13)
  "BaryCoordNV\0" // IR(7560, 12)
  "FragmentBarycentricKHR\0" // IR(7572, 23)
  "BaryCoordNoPerspKHR\0" // IR(7595, 20)
  "BaryCoordNoPerspNV\0" // IR(7615, 19)
  "FragSizeEXT\0" // IR(7634, 12)
  "FragmentSizeNV\0" // IR(7646, 15)
  "FragmentDensityEXT\0" // IR(7661, 19)
  "FragInvocationCountEXT\0" // IR(7680, 23)
  "InvocationsPerPixelNV\0" // IR(7703, 22)
  "PrimitivePointIndicesEXT\0" // IR(7725, 25)
  "PrimitiveLineIndicesEXT\0" // IR(7750, 24)
  "PrimitiveTriangleIndicesEXT\0" // IR(7774, 28)
  "CullPrimitiveEXT\0" // IR(7802, 17)
  "LaunchIdKHR\0" // IR(7819, 12)
  "LaunchIdNV\0" // IR(7831, 11)
  "LaunchSizeKHR\0" // IR(7842, 14)
  "LaunchSizeNV\0" // IR(7856, 13)
  "WorldRayOriginKHR\0" // IR(7869, 18)
  "WorldRayOriginNV\0" // IR(7887, 17)
  "WorldRayDirectionKHR\0" // IR(7904, 21)
  "WorldRayDirectionNV\0" // IR(7925, 20)
  "ObjectRayOriginKHR\0" // IR(7945, 19)
  "ObjectRayOriginNV\0" // IR(7964, 18)
  "ObjectRayDirectionKHR\0" // IR(7982, 22)
  "ObjectRayDirectionNV\0" // IR(8004, 21)
  "RayTminKHR\0" // IR(8025, 11)
  "RayTminNV\0" // IR(8036, 10)
  "RayTmaxKHR\0" // IR(8046, 11)
  "RayTmaxNV\0" // IR(8057, 10)
  "InstanceCustomIndexKHR\0" // IR(8067, 23)
  "InstanceCustomIndexNV\0" // IR(8090, 22)
  "ObjectToWorldKHR\0" // IR(8112, 17)
  "ObjectToWorldNV\0" // IR(8129, 16)
  "WorldToObjectKHR\0" // IR(8145, 17)
  "WorldToObjectNV\0" // IR(8162, 16)
  "HitTNV\0" // IR(8178, 7)
  "HitKindKHR\0" // IR(8185, 11)
  "HitKindNV\0" // IR(8196, 10)
  "CurrentRayTimeNV\0" // IR(8206, 17)
  "RayTracingMotionBlurNV\0" // IR(8223, 23)
  "HitTriangleVertexPositionsKHR\0" // IR(8246, 30)
  "RayTracingPositionFetchKHR\0" // IR(8276, 27)
  "HitMicroTriangleVertexPositionsNV\0" // IR(8303, 34)
  "RayTracingDisplacementMicromapNV\0" // IR(8337, 33)
  "HitMicroTriangleVertexBarycentricsNV\0" // IR(8370, 37)
  "IncomingRayFlagsKHR\0" // IR(8407, 20)
  "IncomingRayFlagsNV\0" // IR(8427, 19)
  "RayGeometryIndexKHR\0" // IR(8446, 20)
  "HitIsSphereNV\0" // IR(8466, 14)
  "RayTracingSpheresGeometryNV\0" // IR(8480, 28)
  "HitIsLSSNV\0" // IR(8508, 11)
  "RayTracingLinearSweptSpheresGeometryNV\0" // IR(8519, 39)
  "HitSpherePositionNV\0" // IR(8558, 20)
  "WarpsPerSMNV\0" // IR(8578, 13)
  "ShaderSMBuiltinsNV\0" // IR(8591, 19)
  "SMCountNV\0" // IR(8610, 10)
  "WarpIDNV\0" // IR(8620, 9)
  "SMIDNV\0" // IR(8629, 7)
  "HitLSSPositionsNV\0" // IR(8636, 18)
  "HitKindFrontFacingMicroTriangleNV\0" // IR(8654, 34)
  "HitKindBackFacingMicroTriangleNV\0" // IR(8688, 33)
  "HitSphereRadiusNV\0" // IR(8721, 18)
  "HitLSSRadiiNV\0" // IR(8739, 14)
  "ClusterIDNV\0" // IR(8753, 12)
  "RayTracingClusterAccelerationStructureNV\0" // IR(8765, 41)
  "CullMaskKHR\0" // IR(8806, 12)
  "RayCullMaskKHR\0" // IR(8818, 15)
  "Matrix\0" // IR(8833, 7)
  "Linkage\0" // IR(8840, 8)
  "Vector16\0" // IR(8848, 9)
  "Float16Buffer\0" // IR(8857, 14)
  "Float16\0" // IR(8871, 8)
  "Float64\0" // IR(8879, 8)
  "Int64\0" // IR(8887, 6)
  "Int64Atomics\0" // IR(8893, 13)
  "ImageBasic\0" // IR(8906, 11)
  "ImageReadWrite\0" // IR(8917, 15)
  "ImageMipmap\0" // IR(8932, 12)
  "Pipes\0" // IR(8944, 6)
  "Groups\0" // IR(8950, 7)
  "DeviceEnqueue\0" // IR(8957, 14)
  "LiteralSampler\0" // IR(8971, 15)
  "AtomicStorage\0" // IR(8986, 14)
  "Int16\0" // IR(9000, 6)
  "TessellationPointSize\0" // IR(9006, 22)
  "GeometryPointSize\0" // IR(9028, 18)
  "ImageGatherExtended\0" // IR(9046, 20)
  "StorageImageMultisample\0" // IR(9066, 24)
  "UniformBufferArrayDynamicIndexing\0" // IR(9090, 34)
  "SampledImageArrayDynamicIndexing\0" // IR(9124, 33)
  "StorageBufferArrayDynamicIndexing\0" // IR(9157, 34)
  "StorageImageArrayDynamicIndexing\0" // IR(9191, 33)
  "ImageCubeArray\0" // IR(9224, 15)
  "SampledCubeArray\0" // IR(9239, 17)
  "ImageRect\0" // IR(9256, 10)
  "SampledRect\0" // IR(9266, 12)
  "GenericPointer\0" // IR(9278, 15)
  "Int8\0" // IR(9293, 5)
  "InputAttachment\0" // IR(9298, 16)
  "SparseResidency\0" // IR(9314, 16)
  "MinLod\0" // IR(9330, 7)
  "Sampled1D\0" // IR(9337, 10)
  "Image1D\0" // IR(9347, 8)
  "SampledBuffer\0" // IR(9355, 14)
  "ImageBuffer\0" // IR(9369, 12)
  "ImageMSArray\0" // IR(9381, 13)
  "StorageImageExtendedFormats\0" // IR(9394, 28)
  "ImageQuery\0" // IR(9422, 11)
  "DerivativeControl\0" // IR(9433, 18)
  "InterpolationFunction\0" // IR(9451, 22)
  "TransformFeedback\0" // IR(9473, 18)
  "GeometryStreams\0" // IR(9491, 16)
  "StorageImageReadWithoutFormat\0" // IR(9507, 30)
  "StorageImageWriteWithoutFormat\0" // IR(9537, 31)
  "SubgroupDispatch\0" // IR(9568, 17)
  "NamedBarrier\0" // IR(9585, 13)
  "PipeStorage\0" // IR(9598, 12)
  "GroupNonUniformVote\0" // IR(9610, 20)
  "GroupNonUniformArithmetic\0" // IR(9630, 26)
  "GroupNonUniformShuffle\0" // IR(9656, 23)
  "GroupNonUniformShuffleRelative\0" // IR(9679, 31)
  "GroupNonUniformClustered\0" // IR(9710, 25)
  "GroupNonUniformQuad\0" // IR(9735, 20)
  "UniformDecoration\0" // IR(9755, 18)
  "TileImageColorReadAccessEXT\0" // IR(9773, 28)
  "TileImageDepthReadAccessEXT\0" // IR(9801, 28)
  "TileImageStencilReadAccessEXT\0" // IR(9829, 30)
  "TensorsARM\0" // IR(9859, 11)
  "StorageTensorArrayDynamicIndexingARM\0" // IR(9870, 37)
  "StorageTensorArrayNonUniformIndexingARM\0" // IR(9907, 40)
  "GraphARM\0" // IR(9947, 9)
  "CooperativeMatrixLayoutsARM\0" // IR(9956, 28)
  "Float8EXT\0" // IR(9984, 10)
  "Float8CooperativeMatrixEXT\0" // IR(9994, 27)
  "CooperativeMatrixKHR\0" // IR(10021, 21)
  "WorkgroupMemoryExplicitLayoutKHR\0" // IR(10042, 33)
  "WorkgroupMemoryExplicitLayout8BitAccessKHR\0" // IR(10075, 43)
  "WorkgroupMemoryExplicitLayout16BitAccessKHR\0" // IR(10118, 44)
  "SubgroupVoteKHR\0" // IR(10162, 16)
  "StorageBuffer16BitAccess\0" // IR(10178, 25)
  "StorageUniformBufferBlock16\0" // IR(10203, 28)
  "UniformAndStorageBuffer16BitAccess\0" // IR(10231, 35)
  "StorageUniform16\0" // IR(10266, 17)
  "StoragePushConstant16\0" // IR(10283, 22)
  "StorageInputOutput16\0" // IR(10305, 21)
  "VariablePointersStorageBuffer\0" // IR(10326, 30)
  "VariablePointers\0" // IR(10356, 17)
  "AtomicStorageOps\0" // IR(10373, 17)
  "SampleMaskPostDepthCoverage\0" // IR(10390, 28)
  "StorageBuffer8BitAccess\0" // IR(10418, 24)
  "UniformAndStorageBuffer8BitAccess\0" // IR(10442, 34)
  "StoragePushConstant8\0" // IR(10476, 21)
  "DenormPreserve\0" // IR(10497, 15)
  "DenormFlushToZero\0" // IR(10512, 18)
  "SignedZeroInfNanPreserve\0" // IR(10530, 25)
  "RoundingModeRTE\0" // IR(10555, 16)
  "RoundingModeRTZ\0" // IR(10571, 16)
  "RayQueryProvisionalKHR\0" // IR(10587, 23)
  "RayQueryKHR\0" // IR(10610, 12)
  "UntypedPointersKHR\0" // IR(10622, 19)
  "RayTraversalPrimitiveCullingKHR\0" // IR(10641, 32)
  "TextureSampleWeightedQCOM\0" // IR(10673, 26)
  "TextureBoxFilterQCOM\0" // IR(10699, 21)
  "TextureBlockMatchQCOM\0" // IR(10720, 22)
  "CooperativeMatrixConversionQCOM\0" // IR(10742, 32)
  "TextureBlockMatch2QCOM\0" // IR(10774, 23)
  "Float16ImageAMD\0" // IR(10797, 16)
  "ImageGatherBiasLodAMD\0" // IR(10813, 22)
  "FragmentMaskAMD\0" // IR(10835, 16)
  "ImageReadWriteLodAMD\0" // IR(10851, 21)
  "Int64ImageEXT\0" // IR(10872, 14)
  "ShaderClockKHR\0" // IR(10886, 15)
  "QuadControlKHR\0" // IR(10901, 15)
  "Int4TypeINTEL\0" // IR(10916, 14)
  "Int4CooperativeMatrixINTEL\0" // IR(10930, 27)
  "BFloat16TypeKHR\0" // IR(10957, 16)
  "BFloat16DotProductKHR\0" // IR(10973, 22)
  "BFloat16CooperativeMatrixKHR\0" // IR(10995, 29)
  "SampleMaskOverrideCoverageNV\0" // IR(11024, 29)
  "GeometryShaderPassthroughNV\0" // IR(11053, 28)
  "ShaderViewportIndexLayerNV\0" // IR(11081, 27)
  "ImageFootprintNV\0" // IR(11108, 17)
  "FragmentBarycentricNV\0" // IR(11125, 22)
  "ComputeDerivativeGroupQuadsKHR\0" // IR(11147, 31)
  "ComputeDerivativeGroupQuadsNV\0" // IR(11178, 30)
  "ShadingRateNV\0" // IR(11208, 14)
  "GroupNonUniformPartitionedEXT\0" // IR(11222, 30)
  "GroupNonUniformPartitionedNV\0" // IR(11252, 29)
  "ShaderNonUniform\0" // IR(11281, 17)
  "ShaderNonUniformEXT\0" // IR(11298, 20)
  "RuntimeDescriptorArray\0" // IR(11318, 23)
  "RuntimeDescriptorArrayEXT\0" // IR(11341, 26)
  "InputAttachmentArrayDynamicIndexing\0" // IR(11367, 36)
  "InputAttachmentArrayDynamicIndexingEXT\0" // IR(11403, 39)
  "UniformTexelBufferArrayDynamicIndexing\0" // IR(11442, 39)
  "UniformTexelBufferArrayDynamicIndexingEXT\0" // IR(11481, 42)
  "StorageTexelBufferArrayDynamicIndexing\0" // IR(11523, 39)
  "StorageTexelBufferArrayDynamicIndexingEXT\0" // IR(11562, 42)
  "UniformBufferArrayNonUniformIndexing\0" // IR(11604, 37)
  "UniformBufferArrayNonUniformIndexingEXT\0" // IR(11641, 40)
  "SampledImageArrayNonUniformIndexing\0" // IR(11681, 36)
  "SampledImageArrayNonUniformIndexingEXT\0" // IR(11717, 39)
  "StorageBufferArrayNonUniformIndexing\0" // IR(11756, 37)
  "StorageBufferArrayNonUniformIndexingEXT\0" // IR(11793, 40)
  "StorageImageArrayNonUniformIndexing\0" // IR(11833, 36)
  "StorageImageArrayNonUniformIndexingEXT\0" // IR(11869, 39)
  "InputAttachmentArrayNonUniformIndexing\0" // IR(11908, 39)
  "InputAttachmentArrayNonUniformIndexingEXT\0" // IR(11947, 42)
  "UniformTexelBufferArrayNonUniformIndexing\0" // IR(11989, 42)
  "UniformTexelBufferArrayNonUniformIndexingEXT\0" // IR(12031, 45)
  "StorageTexelBufferArrayNonUniformIndexing\0" // IR(12076, 42)
  "StorageTexelBufferArrayNonUniformIndexingEXT\0" // IR(12118, 45)
  "VulkanMemoryModel\0" // IR(12163, 18)
  "VulkanMemoryModelKHR\0" // IR(12181, 21)
  "VulkanMemoryModelDeviceScope\0" // IR(12202, 29)
  "VulkanMemoryModelDeviceScopeKHR\0" // IR(12231, 32)
  "PhysicalStorageBufferAddressesEXT\0" // IR(12263, 34)
  "ComputeDerivativeGroupLinearKHR\0" // IR(12297, 32)
  "ComputeDerivativeGroupLinearNV\0" // IR(12329, 31)
  "RayTracingProvisionalKHR\0" // IR(12360, 25)
  "CooperativeMatrixNV\0" // IR(12385, 20)
  "FragmentShaderSampleInterlockEXT\0" // IR(12405, 33)
  "FragmentShaderShadingRateInterlockEXT\0" // IR(12438, 38)
  "FragmentShaderPixelInterlockEXT\0" // IR(12476, 32)
  "DemoteToHelperInvocation\0" // IR(12508, 25)
  "DemoteToHelperInvocationEXT\0" // IR(12533, 28)
  "DisplacementMicromapNV\0" // IR(12561, 23)
  "RayTracingOpacityMicromapEXT\0" // IR(12584, 29)
  "ShaderInvocationReorderNV\0" // IR(12613, 26)
  "ShaderInvocationReorderEXT\0" // IR(12639, 27)
  "BindlessTextureNV\0" // IR(12666, 18)
  "RayQueryPositionFetchKHR\0" // IR(12684, 25)
  "CooperativeVectorNV\0" // IR(12709, 20)
  "AtomicFloat16VectorNV\0" // IR(12729, 22)
  "RawAccessChainsNV\0" // IR(12751, 18)
  "PushConstantBanksNV\0" // IR(12769, 20)
  "LongVectorEXT\0" // IR(12789, 14)
  "Shader64BitIndexingEXT\0" // IR(12803, 23)
  "CooperativeMatrixReductionsNV\0" // IR(12826, 30)
  "CooperativeMatrixConversionsNV\0" // IR(12856, 31)
  "CooperativeMatrixPerElementOperationsNV\0" // IR(12887, 40)
  "CooperativeMatrixTensorAddressingNV\0" // IR(12927, 36)
  "CooperativeMatrixBlockLoadsNV\0" // IR(12963, 30)
  "CooperativeVectorTrainingNV\0" // IR(12993, 28)
  "TensorAddressingNV\0" // IR(13021, 19)
  "SubgroupShuffleINTEL\0" // IR(13040, 21)
  "SubgroupBufferBlockIOINTEL\0" // IR(13061, 27)
  "SubgroupImageBlockIOINTEL\0" // IR(13088, 26)
  "SubgroupImageMediaBlockIOINTEL\0" // IR(13114, 31)
  "RoundToInfinityINTEL\0" // IR(13145, 21)
  "FloatingPointModeINTEL\0" // IR(13166, 23)
  "IntegerFunctions2INTEL\0" // IR(13189, 23)
  "FunctionPointersINTEL\0" // IR(13212, 22)
  "IndirectReferencesINTEL\0" // IR(13234, 24)
  "AsmINTEL\0" // IR(13258, 9)
  "AtomicFloat32MinMaxEXT\0" // IR(13267, 23)
  "AtomicFloat64MinMaxEXT\0" // IR(13290, 23)
  "AtomicFloat16MinMaxEXT\0" // IR(13313, 23)
  "VectorComputeINTEL\0" // IR(13336, 19)
  "VectorAnyINTEL\0" // IR(13355, 15)
  "ExpectAssumeKHR\0" // IR(13370, 16)
  "SubgroupAvcMotionEstimationINTEL\0" // IR(13386, 33)
  "SubgroupAvcMotionEstimationIntraINTEL\0" // IR(13419, 38)
  "SubgroupAvcMotionEstimationChromaINTEL\0" // IR(13457, 39)
  "VariableLengthArrayINTEL\0" // IR(13496, 25)
  "FunctionFloatControlINTEL\0" // IR(13521, 26)
  "FPGAMemoryAttributesALTERA\0" // IR(13547, 27)
  "FPGAMemoryAttributesINTEL\0" // IR(13574, 26)
  "FPFastMathModeINTEL\0" // IR(13600, 20)
  "ArbitraryPrecisionIntegersALTERA\0" // IR(13620, 33)
  "ArbitraryPrecisionIntegersINTEL\0" // IR(13653, 32)
  "ArbitraryPrecisionFloatingPointALTERA\0" // IR(13685, 38)
  "ArbitraryPrecisionFloatingPointINTEL\0" // IR(13723, 37)
  "UnstructuredLoopControlsINTEL\0" // IR(13760, 30)
  "FPGALoopControlsALTERA\0" // IR(13790, 23)
  "FPGALoopControlsINTEL\0" // IR(13813, 22)
  "KernelAttributesINTEL\0" // IR(13835, 22)
  "FPGAKernelAttributesINTEL\0" // IR(13857, 26)
  "FPGAMemoryAccessesALTERA\0" // IR(13883, 25)
  "FPGAMemoryAccessesINTEL\0" // IR(13908, 24)
  "FPGAClusterAttributesALTERA\0" // IR(13932, 28)
  "FPGAClusterAttributesINTEL\0" // IR(13960, 27)
  "LoopFuseALTERA\0" // IR(13987, 15)
  "LoopFuseINTEL\0" // IR(14002, 14)
  "FPGADSPControlALTERA\0" // IR(14016, 21)
  "FPGADSPControlINTEL\0" // IR(14037, 20)
  "MemoryAccessAliasingINTEL\0" // IR(14057, 26)
  "FPGAInvocationPipeliningAttributesALTERA\0" // IR(14083, 41)
  "FPGAInvocationPipeliningAttributesINTEL\0" // IR(14124, 40)
  "FPGABufferLocationALTERA\0" // IR(14164, 25)
  "FPGABufferLocationINTEL\0" // IR(14189, 24)
  "ArbitraryPrecisionFixedPointALTERA\0" // IR(14213, 35)
  "ArbitraryPrecisionFixedPointINTEL\0" // IR(14248, 34)
  "USMStorageClassesALTERA\0" // IR(14282, 24)
  "USMStorageClassesINTEL\0" // IR(14306, 23)
  "RuntimeAlignedAttributeALTERA\0" // IR(14329, 30)
  "RuntimeAlignedAttributeINTEL\0" // IR(14359, 29)
  "IOPipesALTERA\0" // IR(14388, 14)
  "IOPipesINTEL\0" // IR(14402, 13)
  "BlockingPipesALTERA\0" // IR(14415, 20)
  "BlockingPipesINTEL\0" // IR(14435, 19)
  "FPGARegALTERA\0" // IR(14454, 14)
  "FPGARegINTEL\0" // IR(14468, 13)
  "DotProductInputAll\0" // IR(14481, 19)
  "DotProductInputAllKHR\0" // IR(14500, 22)
  "DotProductInput4x8Bit\0" // IR(14522, 22)
  "DotProductInput4x8BitKHR\0" // IR(14544, 25)
  "DotProductInput4x8BitPacked\0" // IR(14569, 28)
  "DotProductInput4x8BitPackedKHR\0" // IR(14597, 31)
  "DotProduct\0" // IR(14628, 11)
  "DotProductKHR\0" // IR(14639, 14)
  "ReplicatedCompositesEXT\0" // IR(14653, 24)
  "BitInstructions\0" // IR(14677, 16)
  "GroupNonUniformRotateKHR\0" // IR(14693, 25)
  "FloatControls2\0" // IR(14718, 15)
  "FMAKHR\0" // IR(14733, 7)
  "AtomicFloat32AddEXT\0" // IR(14740, 20)
  "AtomicFloat64AddEXT\0" // IR(14760, 20)
  "LongCompositesINTEL\0" // IR(14780, 20)
  "OptNoneEXT\0" // IR(14800, 11)
  "OptNoneINTEL\0" // IR(14811, 13)
  "AtomicFloat16AddEXT\0" // IR(14824, 20)
  "DebugInfoModuleINTEL\0" // IR(14844, 21)
  "BFloat16ConversionINTEL\0" // IR(14865, 24)
  "SplitBarrierINTEL\0" // IR(14889, 18)
  "ArithmeticFenceEXT\0" // IR(14907, 19)
  "FPGAClusterAttributesV2ALTERA\0" // IR(14926, 30)
  "FPGAClusterAttributesV2INTEL\0" // IR(14956, 29)
  "FPGAKernelAttributesv2INTEL\0" // IR(14985, 28)
  "TaskSequenceALTERA\0" // IR(15013, 19)
  "TaskSequenceINTEL\0" // IR(15032, 18)
  "FPMaxErrorINTEL\0" // IR(15050, 16)
  "FPGALatencyControlALTERA\0" // IR(15066, 25)
  "FPGALatencyControlINTEL\0" // IR(15091, 24)
  "FPGAArgumentInterfacesALTERA\0" // IR(15115, 29)
  "FPGAArgumentInterfacesINTEL\0" // IR(15144, 28)
  "GlobalVariableHostAccessINTEL\0" // IR(15172, 30)
  "GlobalVariableFPGADecorationsALTERA\0" // IR(15202, 36)
  "GlobalVariableFPGADecorationsINTEL\0" // IR(15238, 35)
  "SubgroupBufferPrefetchINTEL\0" // IR(15273, 28)
  "Subgroup2DBlockIOINTEL\0" // IR(15301, 23)
  "Subgroup2DBlockTransformINTEL\0" // IR(15324, 30)
  "Subgroup2DBlockTransposeINTEL\0" // IR(15354, 30)
  "SubgroupMatrixMultiplyAccumulateINTEL\0" // IR(15384, 38)
  "TernaryBitwiseFunctionINTEL\0" // IR(15422, 28)
  "UntypedVariableLengthArrayINTEL\0" // IR(15450, 32)
  "SpecConditionalINTEL\0" // IR(15482, 21)
  "FunctionVariantsINTEL\0" // IR(15503, 22)
  "GroupUniformArithmeticKHR\0" // IR(15525, 26)
  "TensorFloat32RoundingINTEL\0" // IR(15551, 27)
  "MaskedGatherScatterINTEL\0" // IR(15578, 25)
  "CacheControlsINTEL\0" // IR(15603, 19)
  "RegisterLimitsINTEL\0" // IR(15622, 20)
  "BindlessImagesINTEL\0" // IR(15642, 20)
  "DotProductFloat16AccFloat32VALVE\0" // IR(15662, 33)
  "DotProductFloat16AccFloat16VALVE\0" // IR(15695, 33)
  "DotProductBFloat16AccVALVE\0" // IR(15728, 27)
  "DotProductFloat8AccFloat32VALVE\0" // IR(15755, 32)
  "Unspecified\0" // IR(15787, 12)
  "Address\0" // IR(15799, 8)
  "Boolean\0" // IR(15807, 8)
  "Float\0" // IR(15815, 6)
  "Signed\0" // IR(15821, 7)
  "SignedChar\0" // IR(15828, 11)
  "Unsigned\0" // IR(15839, 9)
  "UnsignedChar\0" // IR(15848, 13)
  "Class\0" // IR(15861, 6)
  "Structure\0" // IR(15867, 10)
  "Union\0" // IR(15877, 6)
  "ImportedModule\0" // IR(15883, 15)
  "ImportedDeclaration\0" // IR(15898, 20)
  "None\0" // IR(15918, 5)
  "FlagIsProtected\0" // IR(15923, 16)
  "FlagIsPrivate\0" // IR(15939, 14)
  "FlagIsPublic\0" // IR(15953, 13)
  "FlagIsLocal\0" // IR(15966, 12)
  "FlagIsDefinition\0" // IR(15978, 17)
  "FlagFwdDecl\0" // IR(15995, 12)
  "FlagArtificial\0" // IR(16007, 15)
  "FlagExplicit\0" // IR(16022, 13)
  "FlagPrototyped\0" // IR(16035, 15)
  "FlagObjectPointer\0" // IR(16050, 18)
  "FlagStaticMember\0" // IR(16068, 17)
  "FlagIndirectVariable\0" // IR(16085, 21)
  "FlagLValueReference\0" // IR(16106, 20)
  "FlagRValueReference\0" // IR(16126, 20)
  "FlagIsOptimized\0" // IR(16146, 16)
  "FlagIsEnumClass\0" // IR(16162, 16)
  "FlagTypePassByValue\0" // IR(16178, 20)
  "FlagTypePassByReference\0" // IR(16198, 24)
  "Deref\0" // IR(16222, 6)
  "Plus\0" // IR(16228, 5)
  "Minus\0" // IR(16233, 6)
  "SPV_OPERAND_TYPE_LITERAL_INTEGER\0" // IR(16239, 33)
  "PlusUconst\0" // IR(16272, 11)
  "BitPiece\0" // IR(16283, 9)
  "Swap\0" // IR(16292, 5)
  "Xderef\0" // IR(16297, 7)
  "StackValue\0" // IR(16304, 11)
  "Constu\0" // IR(16315, 7)
  "Fragment\0" // IR(16322, 9)
  "ConstType\0" // IR(16331, 10)
  "VolatileType\0" // IR(16341, 13)
  "RestrictType\0" // IR(16354, 13)
  "AtomicType\0" // IR(16367, 11)
  "Float16NV\0" // IR(16378, 10)
  "Float32NV\0" // IR(16388, 10)
  "Float64NV\0" // IR(16398, 10)
  "SignedInt8NV\0" // IR(16408, 13)
  "SignedInt16NV\0" // IR(16421, 14)
  "SignedInt32NV\0" // IR(16435, 14)
  "SignedInt64NV\0" // IR(16449, 14)
  "UnsignedInt8NV\0" // IR(16463, 15)
  "UnsignedInt16NV\0" // IR(16478, 16)
  "UnsignedInt32NV\0" // IR(16494, 16)
  "UnsignedInt64NV\0" // IR(16510, 16)
  "SignedInt8PackedNV\0" // IR(16526, 19)
  "UnsignedInt8PackedNV\0" // IR(16545, 21)
  "FloatE4M3NV\0" // IR(16566, 12)
  "FloatE5M2NV\0" // IR(16578, 12)
  "RowMajorKHR\0" // IR(16590, 12)
  "ColumnMajorKHR\0" // IR(16602, 15)
  "RowBlockedInterleavedARM\0" // IR(16617, 25)
  "ColumnBlockedInterleavedARM\0" // IR(16642, 28)
  "NoneKHR\0" // IR(16670, 8)
  "MatrixASignedComponentsKHR\0" // IR(16678, 27)
  "MatrixBSignedComponentsKHR\0" // IR(16705, 27)
  "MatrixCSignedComponentsKHR\0" // IR(16732, 27)
  "MatrixResultSignedComponentsKHR\0" // IR(16759, 32)
  "SaturatingAccumulationKHR\0" // IR(16791, 26)
  "Row\0" // IR(16817, 4)
  "Column\0" // IR(16821, 7)
  "2x2\0" // IR(16828, 4)
  "MatrixAKHR\0" // IR(16832, 11)
  "MatrixBKHR\0" // IR(16843, 11)
  "MatrixAccumulatorKHR\0" // IR(16854, 21)
  "RowMajorNV\0" // IR(16875, 11)
  "ColumnMajorNV\0" // IR(16886, 14)
  "InferencingOptimalNV\0" // IR(16900, 21)
  "TrainingOptimalNV\0" // IR(16921, 18)
  "RelaxedPrecision\0" // IR(16939, 17)
  "SpecId\0" // IR(16956, 7)
  "Block\0" // IR(16963, 6)
  "BufferBlock\0" // IR(16969, 12)
  "RowMajor\0" // IR(16981, 9)
  "ColMajor\0" // IR(16990, 9)
  "ArrayStride\0" // IR(16999, 12)
  "MatrixStride\0" // IR(17011, 13)
  "GLSLShared\0" // IR(17024, 11)
  "GLSLPacked\0" // IR(17035, 11)
  "CPacked\0" // IR(17046, 8)
  "SPV_OPERAND_TYPE_BUILT_IN\0" // IR(17054, 26)
  "BuiltIn\0" // IR(17080, 8)
  "NoPerspective\0" // IR(17088, 14)
  "Flat\0" // IR(17102, 5)
  "Patch\0" // IR(17107, 6)
  "Centroid\0" // IR(17113, 9)
  "Sample\0" // IR(17122, 7)
  "Invariant\0" // IR(17129, 10)
  "Restrict\0" // IR(17139, 9)
  "Aliased\0" // IR(17148, 8)
  "Volatile\0" // IR(17156, 9)
  "Constant\0" // IR(17165, 9)
  "Coherent\0" // IR(17174, 9)
  "NonWritable\0" // IR(17183, 12)
  "NonReadable\0" // IR(17195, 12)
  "Uniform\0" // IR(17207, 8)
  "SPV_OPERAND_TYPE_SCOPE_ID\0" // IR(17215, 26)
  "UniformId\0" // IR(17241, 10)
  "SaturatedConversion\0" // IR(17251, 20)
  "Stream\0" // IR(17271, 7)
  "Location\0" // IR(17278, 9)
  "Component\0" // IR(17287, 10)
  "Index\0" // IR(17297, 6)
  "Binding\0" // IR(17303, 8)
  "DescriptorSet\0" // IR(17311, 14)
  "Offset\0" // IR(17325, 7)
  "XfbBuffer\0" // IR(17332, 10)
  "XfbStride\0" // IR(17342, 10)
  "SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE\0" // IR(17352, 46)
  "FuncParamAttr\0" // IR(17398, 14)
  "SPV_OPERAND_TYPE_FP_ROUNDING_MODE\0" // IR(17412, 34)
  "FPRoundingMode\0" // IR(17446, 15)
  "SPV_OPERAND_TYPE_FP_FAST_MATH_MODE\0" // IR(17461, 35)
  "FPFastMathMode\0" // IR(17496, 15)
  "SPV_OPERAND_TYPE_LITERAL_STRING\0" // IR(17511, 32)
  "SPV_OPERAND_TYPE_LINKAGE_TYPE\0" // IR(17543, 30)
  "LinkageAttributes\0" // IR(17573, 18)
  "NoContraction\0" // IR(17591, 14)
  "InputAttachmentIndex\0" // IR(17605, 21)
  "Alignment\0" // IR(17626, 10)
  "MaxByteOffset\0" // IR(17636, 14)
  "SPV_OPERAND_TYPE_ID\0" // IR(17650, 20)
  "AlignmentId\0" // IR(17670, 12)
  "MaxByteOffsetId\0" // IR(17682, 16)
  "SaturatedToLargestFloat8NormalConversionEXT\0" // IR(17698, 44)
  "NoSignedWrap\0" // IR(17742, 13)
  "NoUnsignedWrap\0" // IR(17755, 15)
  "WeightTextureQCOM\0" // IR(17770, 18)
  "BlockMatchTextureQCOM\0" // IR(17788, 22)
  "BlockMatchSamplerQCOM\0" // IR(17810, 22)
  "ExplicitInterpAMD\0" // IR(17832, 18)
  "NodeSharesPayloadLimitsWithAMDX\0" // IR(17850, 32)
  "NodeMaxPayloadsAMDX\0" // IR(17882, 20)
  "TrackFinishWritingAMDX\0" // IR(17902, 23)
  "PayloadNodeNameAMDX\0" // IR(17925, 20)
  "PayloadNodeBaseIndexAMDX\0" // IR(17945, 25)
  "PayloadNodeSparseArrayAMDX\0" // IR(17970, 27)
  "PayloadNodeArraySizeAMDX\0" // IR(17997, 25)
  "PayloadDispatchIndirectAMDX\0" // IR(18022, 28)
  "ArrayStrideIdEXT\0" // IR(18050, 17)
  "OffsetIdEXT\0" // IR(18067, 12)
  "OverrideCoverageNV\0" // IR(18079, 19)
  "PassthroughNV\0" // IR(18098, 14)
  "ViewportRelativeNV\0" // IR(18112, 19)
  "SecondaryViewportRelativeNV\0" // IR(18131, 28)
  "PerPrimitiveEXT\0" // IR(18159, 16)
  "PerPrimitiveNV\0" // IR(18175, 15)
  "PerViewNV\0" // IR(18190, 10)
  "PerTaskNV\0" // IR(18200, 10)
  "PerVertexKHR\0" // IR(18210, 13)
  "PerVertexNV\0" // IR(18223, 12)
  "NonUniform\0" // IR(18235, 11)
  "NonUniformEXT\0" // IR(18246, 14)
  "RestrictPointer\0" // IR(18260, 16)
  "RestrictPointerEXT\0" // IR(18276, 19)
  "AliasedPointer\0" // IR(18295, 15)
  "AliasedPointerEXT\0" // IR(18310, 18)
  "MemberOffsetNV\0" // IR(18328, 15)
  "HitObjectShaderRecordBufferNV\0" // IR(18343, 30)
  "HitObjectShaderRecordBufferEXT\0" // IR(18373, 31)
  "BankNV\0" // IR(18404, 7)
  "BindlessSamplerNV\0" // IR(18411, 18)
  "BindlessImageNV\0" // IR(18429, 16)
  "BoundSamplerNV\0" // IR(18445, 15)
  "BoundImageNV\0" // IR(18460, 13)
  "SIMTCallINTEL\0" // IR(18473, 14)
  "ReferencedIndirectlyINTEL\0" // IR(18487, 26)
  "ClobberINTEL\0" // IR(18513, 13)
  "SideEffectsINTEL\0" // IR(18526, 17)
  "VectorComputeVariableINTEL\0" // IR(18543, 27)
  "FuncParamIOKindINTEL\0" // IR(18570, 21)
  "VectorComputeFunctionINTEL\0" // IR(18591, 27)
  "StackCallINTEL\0" // IR(18618, 15)
  "GlobalVariableOffsetINTEL\0" // IR(18633, 26)
  "CounterBuffer\0" // IR(18659, 14)
  "HlslCounterBufferGOOGLE\0" // IR(18673, 24)
  "UserSemantic\0" // IR(18697, 13)
  "HlslSemanticGOOGLE\0" // IR(18710, 19)
  "UserTypeGOOGLE\0" // IR(18729, 15)
  "FunctionRoundingModeINTEL\0" // IR(18744, 26)
  "SPV_OPERAND_TYPE_FPDENORM_MODE\0" // IR(18770, 31)
  "FunctionDenormModeINTEL\0" // IR(18801, 24)
  "RegisterALTERA\0" // IR(18825, 15)
  "RegisterINTEL\0" // IR(18840, 14)
  "MemoryALTERA\0" // IR(18854, 13)
  "MemoryINTEL\0" // IR(18867, 12)
  "NumbanksALTERA\0" // IR(18879, 15)
  "NumbanksINTEL\0" // IR(18894, 14)
  "BankwidthALTERA\0" // IR(18908, 16)
  "BankwidthINTEL\0" // IR(18924, 15)
  "MaxPrivateCopiesALTERA\0" // IR(18939, 23)
  "MaxPrivateCopiesINTEL\0" // IR(18962, 22)
  "SinglepumpALTERA\0" // IR(18984, 17)
  "SinglepumpINTEL\0" // IR(19001, 16)
  "DoublepumpALTERA\0" // IR(19017, 17)
  "DoublepumpINTEL\0" // IR(19034, 16)
  "MaxReplicatesALTERA\0" // IR(19050, 20)
  "MaxReplicatesINTEL\0" // IR(19070, 19)
  "SimpleDualPortALTERA\0" // IR(19089, 21)
  "SimpleDualPortINTEL\0" // IR(19110, 20)
  "MergeALTERA\0" // IR(19130, 12)
  "MergeINTEL\0" // IR(19142, 11)
  "SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER\0" // IR(19153, 42)
  "BankBitsALTERA\0" // IR(19195, 15)
  "BankBitsINTEL\0" // IR(19210, 14)
  "ForcePow2DepthALTERA\0" // IR(19224, 21)
  "ForcePow2DepthINTEL\0" // IR(19245, 20)
  "StridesizeALTERA\0" // IR(19265, 17)
  "StridesizeINTEL\0" // IR(19282, 16)
  "WordsizeALTERA\0" // IR(19298, 15)
  "WordsizeINTEL\0" // IR(19313, 14)
  "TrueDualPortALTERA\0" // IR(19327, 19)
  "TrueDualPortINTEL\0" // IR(19346, 18)
  "BurstCoalesceALTERA\0" // IR(19364, 20)
  "BurstCoalesceINTEL\0" // IR(19384, 19)
  "CacheSizeALTERA\0" // IR(19403, 16)
  "CacheSizeINTEL\0" // IR(19419, 15)
  "DontStaticallyCoalesceALTERA\0" // IR(19434, 29)
  "DontStaticallyCoalesceINTEL\0" // IR(19463, 28)
  "PrefetchALTERA\0" // IR(19491, 15)
  "PrefetchINTEL\0" // IR(19506, 14)
  "StallEnableALTERA\0" // IR(19520, 18)
  "StallEnableINTEL\0" // IR(19538, 17)
  "FuseLoopsInFunctionALTERA\0" // IR(19555, 26)
  "FuseLoopsInFunctionINTEL\0" // IR(19581, 25)
  "MathOpDSPModeALTERA\0" // IR(19606, 20)
  "MathOpDSPModeINTEL\0" // IR(19626, 19)
  "AliasScopeINTEL\0" // IR(19645, 16)
  "NoAliasINTEL\0" // IR(19661, 13)
  "InitiationIntervalALTERA\0" // IR(19674, 25)
  "InitiationIntervalINTEL\0" // IR(19699, 24)
  "MaxConcurrencyALTERA\0" // IR(19723, 21)
  "MaxConcurrencyINTEL\0" // IR(19744, 20)
  "PipelineEnableALTERA\0" // IR(19764, 21)
  "PipelineEnableINTEL\0" // IR(19785, 20)
  "BufferLocationALTERA\0" // IR(19805, 21)
  "BufferLocationINTEL\0" // IR(19826, 20)
  "IOPipeStorageALTERA\0" // IR(19846, 20)
  "IOPipeStorageINTEL\0" // IR(19866, 19)
  "SPV_OPERAND_TYPE_FPOPERATION_MODE\0" // IR(19885, 34)
  "FunctionFloatingPointModeINTEL\0" // IR(19919, 31)
  "SingleElementVectorINTEL\0" // IR(19950, 25)
  "VectorComputeCallableFunctionINTEL\0" // IR(19975, 35)
  "MediaBlockIOINTEL\0" // IR(20010, 18)
  "StallFreeALTERA\0" // IR(20028, 16)
  "StallFreeINTEL\0" // IR(20044, 15)
  "SPV_OPERAND_TYPE_LITERAL_FLOAT\0" // IR(20059, 31)
  "FPMaxErrorDecorationINTEL\0" // IR(20090, 26)
  "LatencyControlLabelALTERA\0" // IR(20116, 26)
  "LatencyControlLabelINTEL\0" // IR(20142, 25)
  "LatencyControlConstraintALTERA\0" // IR(20167, 31)
  "LatencyControlConstraintINTEL\0" // IR(20198, 30)
  "ConduitKernelArgumentALTERA\0" // IR(20228, 28)
  "ConduitKernelArgumentINTEL\0" // IR(20256, 27)
  "RegisterMapKernelArgumentALTERA\0" // IR(20283, 32)
  "RegisterMapKernelArgumentINTEL\0" // IR(20315, 31)
  "MMHostInterfaceAddressWidthALTERA\0" // IR(20346, 34)
  "MMHostInterfaceAddressWidthINTEL\0" // IR(20380, 33)
  "MMHostInterfaceDataWidthALTERA\0" // IR(20413, 31)
  "MMHostInterfaceDataWidthINTEL\0" // IR(20444, 30)
  "MMHostInterfaceLatencyALTERA\0" // IR(20474, 29)
  "MMHostInterfaceLatencyINTEL\0" // IR(20503, 28)
  "SPV_OPERAND_TYPE_ACCESS_QUALIFIER\0" // IR(20531, 34)
  "MMHostInterfaceReadWriteModeALTERA\0" // IR(20565, 35)
  "MMHostInterfaceReadWriteModeINTEL\0" // IR(20600, 34)
  "MMHostInterfaceMaxBurstALTERA\0" // IR(20634, 30)
  "MMHostInterfaceMaxBurstINTEL\0" // IR(20664, 29)
  "MMHostInterfaceWaitRequestALTERA\0" // IR(20693, 33)
  "MMHostInterfaceWaitRequestINTEL\0" // IR(20726, 32)
  "StableKernelArgumentALTERA\0" // IR(20758, 27)
  "StableKernelArgumentINTEL\0" // IR(20785, 26)
  "SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER\0" // IR(20811, 39)
  "HostAccessINTEL\0" // IR(20850, 16)
  "SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER\0" // IR(20866, 47)
  "InitModeALTERA\0" // IR(20913, 15)
  "InitModeINTEL\0" // IR(20928, 14)
  "ImplementInRegisterMapALTERA\0" // IR(20942, 29)
  "ImplementInRegisterMapINTEL\0" // IR(20971, 28)
  "ConditionalINTEL\0" // IR(20999, 17)
  "SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL\0" // IR(21016, 36)
  "CacheControlLoadINTEL\0" // IR(21052, 22)
  "SPV_OPERAND_TYPE_STORE_CACHE_CONTROL\0" // IR(21074, 37)
  "CacheControlStoreINTEL\0" // IR(21111, 23)
  "1D\0" // IR(21134, 3)
  "2D\0" // IR(21137, 3)
  "3D\0" // IR(21140, 3)
  "Cube\0" // IR(21143, 5)
  "Rect\0" // IR(21148, 5)
  "Buffer\0" // IR(21153, 7)
  "SubpassData\0" // IR(21160, 12)
  "TileImageDataEXT\0" // IR(21172, 17)
  "Invocations\0" // IR(21189, 12)
  "SpacingEqual\0" // IR(21201, 13)
  "SpacingFractionalEven\0" // IR(21214, 22)
  "SpacingFractionalOdd\0" // IR(21236, 21)
  "VertexOrderCw\0" // IR(21257, 14)
  "VertexOrderCcw\0" // IR(21271, 15)
  "PixelCenterInteger\0" // IR(21286, 19)
  "OriginUpperLeft\0" // IR(21305, 16)
  "OriginLowerLeft\0" // IR(21321, 16)
  "EarlyFragmentTests\0" // IR(21337, 19)
  "PointMode\0" // IR(21356, 10)
  "Xfb\0" // IR(21366, 4)
  "DepthReplacing\0" // IR(21370, 15)
  "DepthGreater\0" // IR(21385, 13)
  "DepthLess\0" // IR(21398, 10)
  "DepthUnchanged\0" // IR(21408, 15)
  "LocalSize\0" // IR(21423, 10)
  "LocalSizeHint\0" // IR(21433, 14)
  "InputPoints\0" // IR(21447, 12)
  "InputLines\0" // IR(21459, 11)
  "InputLinesAdjacency\0" // IR(21470, 20)
  "Triangles\0" // IR(21490, 10)
  "InputTrianglesAdjacency\0" // IR(21500, 24)
  "Quads\0" // IR(21524, 6)
  "Isolines\0" // IR(21530, 9)
  "OutputVertices\0" // IR(21539, 15)
  "OutputPoints\0" // IR(21554, 13)
  "OutputLineStrip\0" // IR(21567, 16)
  "OutputTriangleStrip\0" // IR(21583, 20)
  "VecTypeHint\0" // IR(21603, 12)
  "ContractionOff\0" // IR(21615, 15)
  "Initializer\0" // IR(21630, 12)
  "Finalizer\0" // IR(21642, 10)
  "SubgroupsPerWorkgroup\0" // IR(21652, 22)
  "SubgroupsPerWorkgroupId\0" // IR(21674, 24)
  "LocalSizeId\0" // IR(21698, 12)
  "LocalSizeHintId\0" // IR(21710, 16)
  "NonCoherentColorAttachmentReadEXT\0" // IR(21726, 34)
  "NonCoherentDepthAttachmentReadEXT\0" // IR(21760, 34)
  "NonCoherentStencilAttachmentReadEXT\0" // IR(21794, 36)
  "SubgroupUniformControlFlowKHR\0" // IR(21830, 30)
  "PostDepthCoverage\0" // IR(21860, 18)
  "NonCoherentTileAttachmentReadQCOM\0" // IR(21878, 34)
  "TileShadingRateQCOM\0" // IR(21912, 20)
  "EarlyAndLateFragmentTestsAMD\0" // IR(21932, 29)
  "StencilRefReplacingEXT\0" // IR(21961, 23)
  "CoalescingAMDX\0" // IR(21984, 15)
  "IsApiEntryAMDX\0" // IR(21999, 15)
  "MaxNodeRecursionAMDX\0" // IR(22014, 21)
  "StaticNumWorkgroupsAMDX\0" // IR(22035, 24)
  "MaxNumWorkgroupsAMDX\0" // IR(22059, 21)
  "StencilRefUnchangedFrontAMD\0" // IR(22080, 28)
  "StencilRefGreaterFrontAMD\0" // IR(22108, 26)
  "StencilRefLessFrontAMD\0" // IR(22134, 23)
  "StencilRefUnchangedBackAMD\0" // IR(22157, 27)
  "StencilRefGreaterBackAMD\0" // IR(22184, 25)
  "StencilRefLessBackAMD\0" // IR(22209, 22)
  "QuadDerivativesKHR\0" // IR(22231, 19)
  "RequireFullQuadsKHR\0" // IR(22250, 20)
  "SharesInputWithAMDX\0" // IR(22270, 20)
  "OutputLinesEXT\0" // IR(22290, 15)
  "OutputLinesNV\0" // IR(22305, 14)
  "OutputPrimitivesEXT\0" // IR(22319, 20)
  "OutputPrimitivesNV\0" // IR(22339, 19)
  "DerivativeGroupQuadsKHR\0" // IR(22358, 24)
  "DerivativeGroupQuadsNV\0" // IR(22382, 23)
  "DerivativeGroupLinearKHR\0" // IR(22405, 25)
  "DerivativeGroupLinearNV\0" // IR(22430, 24)
  "OutputTrianglesEXT\0" // IR(22454, 19)
  "OutputTrianglesNV\0" // IR(22473, 18)
  "PixelInterlockOrderedEXT\0" // IR(22491, 25)
  "PixelInterlockUnorderedEXT\0" // IR(22516, 27)
  "SampleInterlockOrderedEXT\0" // IR(22543, 26)
  "SampleInterlockUnorderedEXT\0" // IR(22569, 28)
  "ShadingRateInterlockOrderedEXT\0" // IR(22597, 31)
  "ShadingRateInterlockUnorderedEXT\0" // IR(22628, 33)
  "SharedLocalMemorySizeINTEL\0" // IR(22661, 27)
  "RoundingModeRTPINTEL\0" // IR(22688, 21)
  "RoundingModeRTNINTEL\0" // IR(22709, 21)
  "FloatingPointModeALTINTEL\0" // IR(22730, 26)
  "FloatingPointModeIEEEINTEL\0" // IR(22756, 27)
  "MaxWorkgroupSizeINTEL\0" // IR(22783, 22)
  "MaxWorkDimINTEL\0" // IR(22805, 16)
  "NoGlobalOffsetINTEL\0" // IR(22821, 20)
  "NumSIMDWorkitemsINTEL\0" // IR(22841, 22)
  "SchedulerTargetFmaxMhzINTEL\0" // IR(22863, 28)
  "MaximallyReconvergesKHR\0" // IR(22891, 24)
  "FPFastMathDefault\0" // IR(22915, 18)
  "StreamingInterfaceINTEL\0" // IR(22933, 24)
  "RegisterMapInterfaceINTEL\0" // IR(22957, 26)
  "NamedBarrierCountINTEL\0" // IR(22983, 23)
  "MaximumRegistersINTEL\0" // IR(23006, 22)
  "MaximumRegistersIdINTEL\0" // IR(23028, 24)
  "SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS\0" // IR(23052, 51)
  "NamedMaximumRegistersINTEL\0" // IR(23103, 27)
  "Vertex\0" // IR(23130, 7)
  "TessellationControl\0" // IR(23137, 20)
  "TessellationEvaluation\0" // IR(23157, 23)
  "GLCompute\0" // IR(23180, 10)
  "TaskNV\0" // IR(23190, 7)
  "MeshNV\0" // IR(23197, 7)
  "RayGenerationKHR\0" // IR(23204, 17)
  "RayGenerationNV\0" // IR(23221, 16)
  "IntersectionKHR\0" // IR(23237, 16)
  "IntersectionNV\0" // IR(23253, 15)
  "AnyHitKHR\0" // IR(23268, 10)
  "AnyHitNV\0" // IR(23278, 9)
  "ClosestHitKHR\0" // IR(23287, 14)
  "ClosestHitNV\0" // IR(23301, 13)
  "MissKHR\0" // IR(23314, 8)
  "MissNV\0" // IR(23322, 7)
  "CallableKHR\0" // IR(23329, 12)
  "CallableNV\0" // IR(23341, 11)
  "TaskEXT\0" // IR(23352, 8)
  "MeshEXT\0" // IR(23360, 8)
  "Preserve\0" // IR(23368, 9)
  "FlushToZero\0" // IR(23377, 12)
  "BFloat16KHR\0" // IR(23389, 12)
  "Float8E4M3EXT\0" // IR(23401, 14)
  "Float8E5M2EXT\0" // IR(23415, 14)
  "IEEE\0" // IR(23429, 5)
  "ALT\0" // IR(23434, 4)
  "NotNaN\0" // IR(23438, 7)
  "NotInf\0" // IR(23445, 7)
  "NSZ\0" // IR(23452, 4)
  "AllowRecip\0" // IR(23456, 11)
  "Fast\0" // IR(23467, 5)
  "AllowContract\0" // IR(23472, 14)
  "AllowContractFastINTEL\0" // IR(23486, 23)
  "AllowReassoc\0" // IR(23509, 13)
  "AllowReassocINTEL\0" // IR(23522, 18)
  "AllowTransform\0" // IR(23540, 15)
  "RTE\0" // IR(23555, 4)
  "RTZ\0" // IR(23559, 4)
  "RTP\0" // IR(23563, 4)
  "RTN\0" // IR(23567, 4)
  "Vertical2Pixels\0" // IR(23571, 16)
  "Vertical4Pixels\0" // IR(23587, 16)
  "Horizontal2Pixels\0" // IR(23603, 18)
  "Horizontal4Pixels\0" // IR(23621, 18)
  "Inline\0" // IR(23639, 7)
  "DontInline\0" // IR(23646, 11)
  "Pure\0" // IR(23657, 5)
  "Const\0" // IR(23662, 6)
  "Zext\0" // IR(23668, 5)
  "Sext\0" // IR(23673, 5)
  "ByVal\0" // IR(23678, 6)
  "Sret\0" // IR(23684, 5)
  "NoAlias\0" // IR(23689, 8)
  "NoCapture\0" // IR(23697, 10)
  "NoWrite\0" // IR(23707, 8)
  "NoReadWrite\0" // IR(23715, 12)
  "RuntimeAlignedALTERA\0" // IR(23727, 21)
  "RuntimeAlignedINTEL\0" // IR(23748, 20)
  "Reduce\0" // IR(23768, 7)
  "InclusiveScan\0" // IR(23775, 14)
  "ExclusiveScan\0" // IR(23789, 14)
  "ClusteredReduce\0" // IR(23803, 16)
  "PartitionedReduceEXT\0" // IR(23819, 21)
  "PartitionedReduceNV\0" // IR(23840, 20)
  "PartitionedInclusiveScanEXT\0" // IR(23860, 28)
  "PartitionedInclusiveScanNV\0" // IR(23888, 27)
  "PartitionedExclusiveScanEXT\0" // IR(23915, 28)
  "PartitionedExclusiveScanNV\0" // IR(23943, 27)
  "NoneINTEL\0" // IR(23970, 10)
  "ReadINTEL\0" // IR(23980, 10)
  "WriteINTEL\0" // IR(23990, 11)
  "ReadWriteINTEL\0" // IR(24001, 15)
  "Bias\0" // IR(24016, 5)
  "Lod\0" // IR(24021, 4)
  "Grad\0" // IR(24025, 5)
  "ConstOffset\0" // IR(24030, 12)
  "ConstOffsets\0" // IR(24042, 13)
  "MakeTexelAvailable\0" // IR(24055, 19)
  "MakeTexelAvailableKHR\0" // IR(24074, 22)
  "MakeTexelVisible\0" // IR(24096, 17)
  "MakeTexelVisibleKHR\0" // IR(24113, 20)
  "NonPrivateTexel\0" // IR(24133, 16)
  "NonPrivateTexelKHR\0" // IR(24149, 19)
  "VolatileTexel\0" // IR(24168, 14)
  "VolatileTexelKHR\0" // IR(24182, 17)
  "SignExtend\0" // IR(24199, 11)
  "ZeroExtend\0" // IR(24210, 11)
  "Nontemporal\0" // IR(24221, 12)
  "Offsets\0" // IR(24233, 8)
  "SnormInt8\0" // IR(24241, 10)
  "SnormInt16\0" // IR(24251, 11)
  "UnormInt8\0" // IR(24262, 10)
  "UnormInt16\0" // IR(24272, 11)
  "UnormShort565\0" // IR(24283, 14)
  "UnormShort555\0" // IR(24297, 14)
  "UnormInt101010\0" // IR(24311, 15)
  "SignedInt8\0" // IR(24326, 11)
  "SignedInt16\0" // IR(24337, 12)
  "SignedInt32\0" // IR(24349, 12)
  "UnsignedInt8\0" // IR(24361, 13)
  "UnsignedInt16\0" // IR(24374, 14)
  "UnsignedInt32\0" // IR(24388, 14)
  "HalfFloat\0" // IR(24402, 10)
  "UnormInt24\0" // IR(24412, 11)
  "UnormInt101010_2\0" // IR(24423, 17)
  "UnormInt10X6EXT\0" // IR(24440, 16)
  "UnsignedIntRaw10EXT\0" // IR(24456, 20)
  "UnsignedIntRaw12EXT\0" // IR(24476, 20)
  "UnormInt2_101010EXT\0" // IR(24496, 20)
  "UnsignedInt10X6EXT\0" // IR(24516, 19)
  "UnsignedInt12X4EXT\0" // IR(24535, 19)
  "UnsignedInt14X2EXT\0" // IR(24554, 19)
  "UnormInt12X4EXT\0" // IR(24573, 16)
  "UnormInt14X2EXT\0" // IR(24589, 16)
  "R\0" // IR(24605, 2)
  "A\0" // IR(24607, 2)
  "RG\0" // IR(24609, 3)
  "RA\0" // IR(24612, 3)
  "RGB\0" // IR(24615, 4)
  "RGBA\0" // IR(24619, 5)
  "BGRA\0" // IR(24624, 5)
  "ARGB\0" // IR(24629, 5)
  "Intensity\0" // IR(24634, 10)
  "Luminance\0" // IR(24644, 10)
  "Rx\0" // IR(24654, 3)
  "RGx\0" // IR(24657, 4)
  "RGBx\0" // IR(24661, 5)
  "Depth\0" // IR(24666, 6)
  "DepthStencil\0" // IR(24672, 13)
  "sRGB\0" // IR(24685, 5)
  "sRGBx\0" // IR(24690, 6)
  "sRGBA\0" // IR(24696, 6)
  "sBGRA\0" // IR(24702, 6)
  "ABGR\0" // IR(24708, 5)
  "InitOnDeviceReprogramALTERA\0" // IR(24713, 28)
  "InitOnDeviceReprogramINTEL\0" // IR(24741, 27)
  "InitOnDeviceResetALTERA\0" // IR(24768, 24)
  "InitOnDeviceResetINTEL\0" // IR(24792, 23)
  "NoWait\0" // IR(24815, 7)
  "WaitKernel\0" // IR(24822, 11)
  "WaitWorkGroup\0" // IR(24833, 14)
  "CmdExecTime\0" // IR(24847, 12)
  "MayUsePrintf\0" // IR(24859, 13)
  "Export\0" // IR(24872, 7)
  "Import\0" // IR(24879, 7)
  "LinkOnceODR\0" // IR(24886, 12)
  "UncachedINTEL\0" // IR(24898, 14)
  "CachedINTEL\0" // IR(24912, 12)
  "StreamingINTEL\0" // IR(24924, 15)
  "InvalidateAfterReadINTEL\0" // IR(24939, 25)
  "ConstCachedINTEL\0" // IR(24964, 17)
  "Unroll\0" // IR(24981, 7)
  "DontUnroll\0" // IR(24988, 11)
  "DependencyInfinite\0" // IR(24999, 19)
  "DependencyLength\0" // IR(25018, 17)
  "MinIterations\0" // IR(25035, 14)
  "MaxIterations\0" // IR(25049, 14)
  "IterationMultiple\0" // IR(25063, 18)
  "PeelCount\0" // IR(25081, 10)
  "PartialCount\0" // IR(25091, 13)
  "DependencyArrayALTERA\0" // IR(25104, 22)
  "DependencyArrayINTEL\0" // IR(25126, 21)
  "LoopCoalesceALTERA\0" // IR(25147, 19)
  "LoopCoalesceINTEL\0" // IR(25166, 18)
  "MaxInterleavingALTERA\0" // IR(25184, 22)
  "MaxInterleavingINTEL\0" // IR(25206, 21)
  "SpeculatedIterationsALTERA\0" // IR(25227, 27)
  "SpeculatedIterationsINTEL\0" // IR(25254, 26)
  "NoFusionALTERA\0" // IR(25280, 15)
  "NoFusionINTEL\0" // IR(25295, 14)
  "LoopCountALTERA\0" // IR(25309, 16)
  "LoopCountINTEL\0" // IR(25325, 15)
  "MaxReinvocationDelayALTERA\0" // IR(25340, 27)
  "MaxReinvocationDelayINTEL\0" // IR(25367, 26)
  "MatrixASignedComponentsINTEL\0" // IR(25393, 29)
  "MatrixBSignedComponentsINTEL\0" // IR(25422, 29)
  "MatrixCBFloat16INTEL\0" // IR(25451, 21)
  "MatrixResultBFloat16INTEL\0" // IR(25472, 26)
  "MatrixAPackedInt8INTEL\0" // IR(25498, 23)
  "MatrixBPackedInt8INTEL\0" // IR(25521, 23)
  "MatrixAPackedInt4INTEL\0" // IR(25544, 23)
  "MatrixBPackedInt4INTEL\0" // IR(25567, 23)
  "MatrixATF32INTEL\0" // IR(25590, 17)
  "MatrixBTF32INTEL\0" // IR(25607, 17)
  "MatrixAPackedFloat16INTEL\0" // IR(25624, 26)
  "MatrixBPackedFloat16INTEL\0" // IR(25650, 26)
  "MatrixAPackedBFloat16INTEL\0" // IR(25676, 27)
  "MatrixBPackedBFloat16INTEL\0" // IR(25703, 27)
  "Aligned\0" // IR(25730, 8)
  "MakePointerAvailable\0" // IR(25738, 21)
  "MakePointerAvailableKHR\0" // IR(25759, 24)
  "MakePointerVisible\0" // IR(25783, 19)
  "MakePointerVisibleKHR\0" // IR(25802, 22)
  "NonPrivatePointer\0" // IR(25824, 18)
  "NonPrivatePointerKHR\0" // IR(25842, 21)
  "AliasScopeINTELMask\0" // IR(25863, 20)
  "NoAliasINTELMask\0" // IR(25883, 17)
  "Simple\0" // IR(25900, 7)
  "GLSL450\0" // IR(25907, 8)
  "OpenCL\0" // IR(25915, 7)
  "Vulkan\0" // IR(25922, 7)
  "VulkanKHR\0" // IR(25929, 10)
  "Relaxed\0" // IR(25939, 8)
  "Acquire\0" // IR(25947, 8)
  "Release\0" // IR(25955, 8)
  "AcquireRelease\0" // IR(25963, 15)
  "SequentiallyConsistent\0" // IR(25978, 23)
  "UniformMemory\0" // IR(26001, 14)
  "SubgroupMemory\0" // IR(26015, 15)
  "WorkgroupMemory\0" // IR(26030, 16)
  "CrossWorkgroupMemory\0" // IR(26046, 21)
  "AtomicCounterMemory\0" // IR(26067, 20)
  "ImageMemory\0" // IR(26087, 12)
  "OutputMemory\0" // IR(26099, 13)
  "OutputMemoryKHR\0" // IR(26112, 16)
  "MakeAvailable\0" // IR(26128, 14)
  "MakeAvailableKHR\0" // IR(26142, 17)
  "MakeVisible\0" // IR(26159, 12)
  "MakeVisibleKHR\0" // IR(26171, 15)
  "AutoINTEL\0" // IR(26186, 10)
  "WRAP\0" // IR(26196, 5)
  "SAT\0" // IR(26201, 4)
  "SAT_ZERO\0" // IR(26205, 9)
  "SAT_SYM\0" // IR(26214, 8)
  "PackedVectorFormat4x8Bit\0" // IR(26222, 25)
  "PackedVectorFormat4x8BitKHR\0" // IR(26247, 28)
  "TRN\0" // IR(26275, 4)
  "TRN_ZERO\0" // IR(26279, 9)
  "RND\0" // IR(26288, 4)
  "RND_ZERO\0" // IR(26292, 9)
  "RND_INF\0" // IR(26301, 8)
  "RND_MIN_INF\0" // IR(26309, 12)
  "RND_CONV\0" // IR(26321, 9)
  "RND_CONV_ODD\0" // IR(26330, 13)
  "RobustnessPerComponentNV\0" // IR(26343, 25)
  "RobustnessPerElementNV\0" // IR(26368, 23)
  "OpaqueKHR\0" // IR(26391, 10)
  "NoOpaqueKHR\0" // IR(26401, 12)
  "TerminateOnFirstHitKHR\0" // IR(26413, 23)
  "SkipClosestHitShaderKHR\0" // IR(26436, 24)
  "CullBackFacingTrianglesKHR\0" // IR(26460, 27)
  "CullFrontFacingTrianglesKHR\0" // IR(26487, 28)
  "CullOpaqueKHR\0" // IR(26515, 14)
  "CullNoOpaqueKHR\0" // IR(26529, 16)
  "SkipTrianglesKHR\0" // IR(26545, 17)
  "SkipBuiltinPrimitivesNV\0" // IR(26562, 24)
  "SkipAABBsKHR\0" // IR(26586, 13)
  "ForceOpacityMicromap2StateEXT\0" // IR(26599, 30)
  "RayQueryCandidateIntersectionTriangleKHR\0" // IR(26629, 41)
  "RayQueryCandidateIntersectionAABBKHR\0" // IR(26670, 37)
  "RayQueryCommittedIntersectionNoneKHR\0" // IR(26707, 37)
  "RayQueryCommittedIntersectionTriangleKHR\0" // IR(26744, 41)
  "RayQueryCommittedIntersectionGeneratedKHR\0" // IR(26785, 42)
  "RayQueryCandidateIntersectionKHR\0" // IR(26827, 33)
  "RayQueryCommittedIntersectionKHR\0" // IR(26860, 33)
  "ClampToEdge\0" // IR(26893, 12)
  "Clamp\0" // IR(26905, 6)
  "Repeat\0" // IR(26911, 7)
  "RepeatMirrored\0" // IR(26918, 15)
  "Nearest\0" // IR(26933, 8)
  "Linear\0" // IR(26941, 7)
  "Unknown\0" // IR(26948, 8)
  "Rgba32f\0" // IR(26956, 8)
  "Rgba16f\0" // IR(26964, 8)
  "R32f\0" // IR(26972, 5)
  "Rgba8\0" // IR(26977, 6)
  "Rgba8Snorm\0" // IR(26983, 11)
  "Rg32f\0" // IR(26994, 6)
  "Rg16f\0" // IR(27000, 6)
  "R11fG11fB10f\0" // IR(27006, 13)
  "R16f\0" // IR(27019, 5)
  "Rgba16\0" // IR(27024, 7)
  "Rgb10A2\0" // IR(27031, 8)
  "Rg16\0" // IR(27039, 5)
  "Rg8\0" // IR(27044, 4)
  "R16\0" // IR(27048, 4)
  "R8\0" // IR(27052, 3)
  "Rgba16Snorm\0" // IR(27055, 12)
  "Rg16Snorm\0" // IR(27067, 10)
  "Rg8Snorm\0" // IR(27077, 9)
  "R16Snorm\0" // IR(27086, 9)
  "R8Snorm\0" // IR(27095, 8)
  "Rgba32i\0" // IR(27103, 8)
  "Rgba16i\0" // IR(27111, 8)
  "Rgba8i\0" // IR(27119, 7)
  "R32i\0" // IR(27126, 5)
  "Rg32i\0" // IR(27131, 6)
  "Rg16i\0" // IR(27137, 6)
  "Rg8i\0" // IR(27143, 5)
  "R16i\0" // IR(27148, 5)
  "R8i\0" // IR(27153, 4)
  "Rgba32ui\0" // IR(27157, 9)
  "Rgba16ui\0" // IR(27166, 9)
  "Rgba8ui\0" // IR(27175, 8)
  "R32ui\0" // IR(27183, 6)
  "Rgb10a2ui\0" // IR(27189, 10)
  "Rg32ui\0" // IR(27199, 7)
  "Rg16ui\0" // IR(27206, 7)
  "Rg8ui\0" // IR(27213, 6)
  "R16ui\0" // IR(27219, 6)
  "R8ui\0" // IR(27225, 5)
  "R64ui\0" // IR(27230, 6)
  "R64i\0" // IR(27236, 5)
  "CrossDevice\0" // IR(27241, 12)
  "Device\0" // IR(27253, 7)
  "Workgroup\0" // IR(27260, 10)
  "Subgroup\0" // IR(27270, 9)
  "Invocation\0" // IR(27279, 11)
  "QueueFamily\0" // IR(27290, 12)
  "QueueFamilyKHR\0" // IR(27302, 15)
  "ShaderCallKHR\0" // IR(27317, 14)
  "Flatten\0" // IR(27331, 8)
  "DontFlatten\0" // IR(27339, 12)
  "IdentifierPossibleDuplicates\0" // IR(27351, 29)
  "FlagUnknownPhysicalLayout\0" // IR(27380, 26)
  "ESSL\0" // IR(27406, 5)
  "GLSL\0" // IR(27411, 5)
  "OpenCL_C\0" // IR(27416, 9)
  "OpenCL_CPP\0" // IR(27425, 11)
  "HLSL\0" // IR(27436, 5)
  "CPP_for_OpenCL\0" // IR(27441, 15)
  "SYCL\0" // IR(27456, 5)
  "HERO_C\0" // IR(27461, 7)
  "NZSL\0" // IR(27468, 5)
  "WGSL\0" // IR(27473, 5)
  "Slang\0" // IR(27478, 6)
  "Zig\0" // IR(27484, 4)
  "Rust\0" // IR(27488, 5)
  "UniformConstant\0" // IR(27493, 16)
  "Input\0" // IR(27509, 6)
  "Output\0" // IR(27515, 7)
  "CrossWorkgroup\0" // IR(27522, 15)
  "Private\0" // IR(27537, 8)
  "Function\0" // IR(27545, 9)
  "Generic\0" // IR(27554, 8)
  "PushConstant\0" // IR(27562, 13)
  "AtomicCounter\0" // IR(27575, 14)
  "Image\0" // IR(27589, 6)
  "StorageBuffer\0" // IR(27595, 14)
  "TileImageEXT\0" // IR(27609, 13)
  "TileAttachmentQCOM\0" // IR(27622, 19)
  "NodePayloadAMDX\0" // IR(27641, 16)
  "CallableDataKHR\0" // IR(27657, 16)
  "CallableDataNV\0" // IR(27673, 15)
  "IncomingCallableDataKHR\0" // IR(27688, 24)
  "IncomingCallableDataNV\0" // IR(27712, 23)
  "RayPayloadKHR\0" // IR(27735, 14)
  "RayPayloadNV\0" // IR(27749, 13)
  "HitAttributeKHR\0" // IR(27762, 16)
  "HitAttributeNV\0" // IR(27778, 15)
  "IncomingRayPayloadKHR\0" // IR(27793, 22)
  "IncomingRayPayloadNV\0" // IR(27815, 21)
  "ShaderRecordBufferKHR\0" // IR(27836, 22)
  "ShaderRecordBufferNV\0" // IR(27858, 21)
  "PhysicalStorageBuffer\0" // IR(27879, 22)
  "PhysicalStorageBufferEXT\0" // IR(27901, 25)
  "HitObjectAttributeNV\0" // IR(27926, 21)
  "TaskPayloadWorkgroupEXT\0" // IR(27947, 24)
  "HitObjectAttributeEXT\0" // IR(27971, 22)
  "CodeSectionINTEL\0" // IR(27993, 17)
  "DeviceOnlyALTERA\0" // IR(28010, 17)
  "DeviceOnlyINTEL\0" // IR(28027, 16)
  "HostOnlyALTERA\0" // IR(28043, 15)
  "HostOnlyINTEL\0" // IR(28058, 14)
  "WriteThroughINTEL\0" // IR(28072, 18)
  "WriteBackINTEL\0" // IR(28090, 15)
  "TensorView\0" // IR(28105, 11)
  "DecodeFunc\0" // IR(28116, 11)
  "Undefined\0" // IR(28127, 10)
  "NoneARM\0" // IR(28137, 8)
  "NontemporalARM\0" // IR(28145, 15)
  "OutOfBoundsValueARM\0" // IR(28160, 20)
  "MakeElementAvailableARM\0" // IR(28180, 24)
  "MakeElementVisibleARM\0" // IR(28204, 22)
  "NonPrivateElementARM\0" // IR(28226, 21)
  "Nop\0" // IR(28247, 4)
  "SPV_OPERAND_TYPE_TYPE_ID\0" // IR(28251, 25)
  "SPV_OPERAND_TYPE_RESULT_ID\0" // IR(28276, 27)
  "Undef\0" // IR(28303, 6)
  "SourceContinued\0" // IR(28309, 16)
  "SPV_OPERAND_TYPE_SOURCE_LANGUAGE\0" // IR(28325, 33)
  "SPV_OPERAND_TYPE_OPTIONAL_ID\0" // IR(28358, 29)
  "SPV_OPERAND_TYPE_OPTIONAL_LITERAL_STRING\0" // IR(28387, 41)
  "Source\0" // IR(28428, 7)
  "SourceExtension\0" // IR(28435, 16)
  "Name\0" // IR(28451, 5)
  "MemberName\0" // IR(28456, 11)
  "String\0" // IR(28467, 7)
  "Line\0" // IR(28474, 5)
  "Extension\0" // IR(28479, 10)
  "ExtInstImport\0" // IR(28489, 14)
  "SPV_OPERAND_TYPE_EXTENSION_INSTRUCTION_NUMBER\0" // IR(28503, 46)
  "ExtInst\0" // IR(28549, 8)
  "SPV_OPERAND_TYPE_ADDRESSING_MODEL\0" // IR(28557, 34)
  "SPV_OPERAND_TYPE_MEMORY_MODEL\0" // IR(28591, 30)
  "MemoryModel\0" // IR(28621, 12)
  "SPV_OPERAND_TYPE_EXECUTION_MODEL\0" // IR(28633, 33)
  "SPV_OPERAND_TYPE_VARIABLE_ID\0" // IR(28666, 29)
  "EntryPoint\0" // IR(28695, 11)
  "SPV_OPERAND_TYPE_EXECUTION_MODE\0" // IR(28706, 32)
  "ExecutionMode\0" // IR(28738, 14)
  "SPV_OPERAND_TYPE_CAPABILITY\0" // IR(28752, 28)
  "Capability\0" // IR(28780, 11)
  "TypeVoid\0" // IR(28791, 9)
  "TypeBool\0" // IR(28800, 9)
  "TypeInt\0" // IR(28809, 8)
  "SPV_OPERAND_TYPE_OPTIONAL_FPENCODING\0" // IR(28817, 37)
  "TypeFloat\0" // IR(28854, 10)
  "TypeVector\0" // IR(28864, 11)
  "TypeMatrix\0" // IR(28875, 11)
  "SPV_OPERAND_TYPE_DIMENSIONALITY\0" // IR(28886, 32)
  "SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT\0" // IR(28918, 38)
  "SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER\0" // IR(28956, 43)
  "TypeImage\0" // IR(28999, 10)
  "TypeSampler\0" // IR(29009, 12)
  "TypeSampledImage\0" // IR(29021, 17)
  "TypeArray\0" // IR(29038, 10)
  "TypeRuntimeArray\0" // IR(29048, 17)
  "TypeStruct\0" // IR(29065, 11)
  "TypeOpaque\0" // IR(29076, 11)
  "SPV_OPERAND_TYPE_STORAGE_CLASS\0" // IR(29087, 31)
  "TypePointer\0" // IR(29118, 12)
  "TypeFunction\0" // IR(29130, 13)
  "TypeEvent\0" // IR(29143, 10)
  "TypeDeviceEvent\0" // IR(29153, 16)
  "TypeReserveId\0" // IR(29169, 14)
  "TypeQueue\0" // IR(29183, 10)
  "TypePipe\0" // IR(29193, 9)
  "TypeForwardPointer\0" // IR(29202, 19)
  "ConstantTrue\0" // IR(29221, 13)
  "ConstantFalse\0" // IR(29234, 14)
  "SPV_OPERAND_TYPE_TYPED_LITERAL_NUMBER\0" // IR(29248, 38)
  "ConstantComposite\0" // IR(29286, 18)
  "SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE\0" // IR(29304, 41)
  "SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE\0" // IR(29345, 37)
  "ConstantSampler\0" // IR(29382, 16)
  "ConstantNull\0" // IR(29398, 13)
  "SpecConstantTrue\0" // IR(29411, 17)
  "SpecConstantFalse\0" // IR(29428, 18)
  "SpecConstant\0" // IR(29446, 13)
  "SpecConstantComposite\0" // IR(29459, 22)
  "SPV_OPERAND_TYPE_SPEC_CONSTANT_OP_NUMBER\0" // IR(29481, 41)
  "SpecConstantOp\0" // IR(29522, 15)
  "SPV_OPERAND_TYPE_FUNCTION_CONTROL\0" // IR(29537, 34)
  "FunctionParameter\0" // IR(29571, 18)
  "FunctionEnd\0" // IR(29589, 12)
  "FunctionCall\0" // IR(29601, 13)
  "Variable\0" // IR(29614, 9)
  "ImageTexelPointer\0" // IR(29623, 18)
  "SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS\0" // IR(29641, 40)
  "Load\0" // IR(29681, 5)
  "Store\0" // IR(29686, 6)
  "CopyMemory\0" // IR(29692, 11)
  "CopyMemorySized\0" // IR(29703, 16)
  "AccessChain\0" // IR(29719, 12)
  "InBoundsAccessChain\0" // IR(29731, 20)
  "PtrAccessChain\0" // IR(29751, 15)
  "ArrayLength\0" // IR(29766, 12)
  "GenericPtrMemSemantics\0" // IR(29778, 23)
  "InBoundsPtrAccessChain\0" // IR(29801, 23)
  "SPV_OPERAND_TYPE_DECORATION\0" // IR(29824, 28)
  "Decorate\0" // IR(29852, 9)
  "MemberDecorate\0" // IR(29861, 15)
  "DecorationGroup\0" // IR(29876, 16)
  "GroupDecorate\0" // IR(29892, 14)
  "SPV_OPERAND_TYPE_VARIABLE_ID_LITERAL_INTEGER\0" // IR(29906, 45)
  "GroupMemberDecorate\0" // IR(29951, 20)
  "VectorExtractDynamic\0" // IR(29971, 21)
  "VectorInsertDynamic\0" // IR(29992, 20)
  "VectorShuffle\0" // IR(30012, 14)
  "CompositeConstruct\0" // IR(30026, 19)
  "CompositeExtract\0" // IR(30045, 17)
  "CompositeInsert\0" // IR(30062, 16)
  "CopyObject\0" // IR(30078, 11)
  "Transpose\0" // IR(30089, 10)
  "SampledImage\0" // IR(30099, 13)
  "SPV_OPERAND_TYPE_OPTIONAL_IMAGE\0" // IR(30112, 32)
  "ImageSampleImplicitLod\0" // IR(30144, 23)
  "SPV_OPERAND_TYPE_IMAGE\0" // IR(30167, 23)
  "ImageSampleExplicitLod\0" // IR(30190, 23)
  "ImageSampleDrefImplicitLod\0" // IR(30213, 27)
  "ImageSampleDrefExplicitLod\0" // IR(30240, 27)
  "ImageSampleProjImplicitLod\0" // IR(30267, 27)
  "ImageSampleProjExplicitLod\0" // IR(30294, 27)
  "ImageSampleProjDrefImplicitLod\0" // IR(30321, 31)
  "ImageSampleProjDrefExplicitLod\0" // IR(30352, 31)
  "ImageFetch\0" // IR(30383, 11)
  "ImageGather\0" // IR(30394, 12)
  "ImageDrefGather\0" // IR(30406, 16)
  "ImageRead\0" // IR(30422, 10)
  "ImageWrite\0" // IR(30432, 11)
  "ImageQueryFormat\0" // IR(30443, 17)
  "ImageQueryOrder\0" // IR(30460, 16)
  "ImageQuerySizeLod\0" // IR(30476, 18)
  "ImageQuerySize\0" // IR(30494, 15)
  "ImageQueryLod\0" // IR(30509, 14)
  "ImageQueryLevels\0" // IR(30523, 17)
  "ImageQuerySamples\0" // IR(30540, 18)
  "ConvertFToU\0" // IR(30558, 12)
  "ConvertFToS\0" // IR(30570, 12)
  "ConvertSToF\0" // IR(30582, 12)
  "ConvertUToF\0" // IR(30594, 12)
  "UConvert\0" // IR(30606, 9)
  "SConvert\0" // IR(30615, 9)
  "FConvert\0" // IR(30624, 9)
  "QuantizeToF16\0" // IR(30633, 14)
  "ConvertPtrToU\0" // IR(30647, 14)
  "SatConvertSToU\0" // IR(30661, 15)
  "SatConvertUToS\0" // IR(30676, 15)
  "ConvertUToPtr\0" // IR(30691, 14)
  "PtrCastToGeneric\0" // IR(30705, 17)
  "GenericCastToPtr\0" // IR(30722, 17)
  "GenericCastToPtrExplicit\0" // IR(30739, 25)
  "Bitcast\0" // IR(30764, 8)
  "SNegate\0" // IR(30772, 8)
  "FNegate\0" // IR(30780, 8)
  "IAdd\0" // IR(30788, 5)
  "FAdd\0" // IR(30793, 5)
  "ISub\0" // IR(30798, 5)
  "FSub\0" // IR(30803, 5)
  "IMul\0" // IR(30808, 5)
  "FMul\0" // IR(30813, 5)
  "UDiv\0" // IR(30818, 5)
  "SDiv\0" // IR(30823, 5)
  "FDiv\0" // IR(30828, 5)
  "UMod\0" // IR(30833, 5)
  "SRem\0" // IR(30838, 5)
  "SMod\0" // IR(30843, 5)
  "FRem\0" // IR(30848, 5)
  "FMod\0" // IR(30853, 5)
  "VectorTimesScalar\0" // IR(30858, 18)
  "MatrixTimesScalar\0" // IR(30876, 18)
  "VectorTimesMatrix\0" // IR(30894, 18)
  "MatrixTimesVector\0" // IR(30912, 18)
  "MatrixTimesMatrix\0" // IR(30930, 18)
  "OuterProduct\0" // IR(30948, 13)
  "Dot\0" // IR(30961, 4)
  "IAddCarry\0" // IR(30965, 10)
  "ISubBorrow\0" // IR(30975, 11)
  "UMulExtended\0" // IR(30986, 13)
  "SMulExtended\0" // IR(30999, 13)
  "Any\0" // IR(31012, 4)
  "All\0" // IR(31016, 4)
  "IsNan\0" // IR(31020, 6)
  "IsInf\0" // IR(31026, 6)
  "IsFinite\0" // IR(31032, 9)
  "IsNormal\0" // IR(31041, 9)
  "SignBitSet\0" // IR(31050, 11)
  "LessOrGreater\0" // IR(31061, 14)
  "Ordered\0" // IR(31075, 8)
  "Unordered\0" // IR(31083, 10)
  "LogicalEqual\0" // IR(31093, 13)
  "LogicalNotEqual\0" // IR(31106, 16)
  "LogicalOr\0" // IR(31122, 10)
  "LogicalAnd\0" // IR(31132, 11)
  "LogicalNot\0" // IR(31143, 11)
  "Select\0" // IR(31154, 7)
  "IEqual\0" // IR(31161, 7)
  "INotEqual\0" // IR(31168, 10)
  "UGreaterThan\0" // IR(31178, 13)
  "SGreaterThan\0" // IR(31191, 13)
  "UGreaterThanEqual\0" // IR(31204, 18)
  "SGreaterThanEqual\0" // IR(31222, 18)
  "ULessThan\0" // IR(31240, 10)
  "SLessThan\0" // IR(31250, 10)
  "ULessThanEqual\0" // IR(31260, 15)
  "SLessThanEqual\0" // IR(31275, 15)
  "FOrdEqual\0" // IR(31290, 10)
  "FUnordEqual\0" // IR(31300, 12)
  "FOrdNotEqual\0" // IR(31312, 13)
  "FUnordNotEqual\0" // IR(31325, 15)
  "FOrdLessThan\0" // IR(31340, 13)
  "FUnordLessThan\0" // IR(31353, 15)
  "FOrdGreaterThan\0" // IR(31368, 16)
  "FUnordGreaterThan\0" // IR(31384, 18)
  "FOrdLessThanEqual\0" // IR(31402, 18)
  "FUnordLessThanEqual\0" // IR(31420, 20)
  "FOrdGreaterThanEqual\0" // IR(31440, 21)
  "FUnordGreaterThanEqual\0" // IR(31461, 23)
  "ShiftRightLogical\0" // IR(31484, 18)
  "ShiftRightArithmetic\0" // IR(31502, 21)
  "ShiftLeftLogical\0" // IR(31523, 17)
  "BitwiseOr\0" // IR(31540, 10)
  "BitwiseXor\0" // IR(31550, 11)
  "BitwiseAnd\0" // IR(31561, 11)
  "Not\0" // IR(31572, 4)
  "BitFieldInsert\0" // IR(31576, 15)
  "BitFieldSExtract\0" // IR(31591, 17)
  "BitFieldUExtract\0" // IR(31608, 17)
  "BitReverse\0" // IR(31625, 11)
  "BitCount\0" // IR(31636, 9)
  "DPdx\0" // IR(31645, 5)
  "DPdy\0" // IR(31650, 5)
  "Fwidth\0" // IR(31655, 7)
  "DPdxFine\0" // IR(31662, 9)
  "DPdyFine\0" // IR(31671, 9)
  "FwidthFine\0" // IR(31680, 11)
  "DPdxCoarse\0" // IR(31691, 11)
  "DPdyCoarse\0" // IR(31702, 11)
  "FwidthCoarse\0" // IR(31713, 13)
  "EmitVertex\0" // IR(31726, 11)
  "EndPrimitive\0" // IR(31737, 13)
  "EmitStreamVertex\0" // IR(31750, 17)
  "EndStreamPrimitive\0" // IR(31767, 19)
  "SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID\0" // IR(31786, 37)
  "ControlBarrier\0" // IR(31823, 15)
  "MemoryBarrier\0" // IR(31838, 14)
  "AtomicLoad\0" // IR(31852, 11)
  "AtomicStore\0" // IR(31863, 12)
  "AtomicExchange\0" // IR(31875, 15)
  "AtomicCompareExchange\0" // IR(31890, 22)
  "AtomicCompareExchangeWeak\0" // IR(31912, 26)
  "AtomicIIncrement\0" // IR(31938, 17)
  "AtomicIDecrement\0" // IR(31955, 17)
  "AtomicIAdd\0" // IR(31972, 11)
  "AtomicISub\0" // IR(31983, 11)
  "AtomicSMin\0" // IR(31994, 11)
  "AtomicUMin\0" // IR(32005, 11)
  "AtomicSMax\0" // IR(32016, 11)
  "AtomicUMax\0" // IR(32027, 11)
  "AtomicAnd\0" // IR(32038, 10)
  "AtomicOr\0" // IR(32048, 9)
  "AtomicXor\0" // IR(32057, 10)
  "Phi\0" // IR(32067, 4)
  "SPV_OPERAND_TYPE_LOOP_CONTROL\0" // IR(32071, 30)
  "LoopMerge\0" // IR(32101, 10)
  "SPV_OPERAND_TYPE_SELECTION_CONTROL\0" // IR(32111, 35)
  "SelectionMerge\0" // IR(32146, 15)
  "Label\0" // IR(32161, 6)
  "Branch\0" // IR(32167, 7)
  "BranchConditional\0" // IR(32174, 18)
  "SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER_ID\0" // IR(32192, 45)
  "Switch\0" // IR(32237, 7)
  "Kill\0" // IR(32244, 5)
  "Return\0" // IR(32249, 7)
  "ReturnValue\0" // IR(32256, 12)
  "Unreachable\0" // IR(32268, 12)
  "LifetimeStart\0" // IR(32280, 14)
  "LifetimeStop\0" // IR(32294, 13)
  "GroupAsyncCopy\0" // IR(32307, 15)
  "GroupWaitEvents\0" // IR(32322, 16)
  "GroupAll\0" // IR(32338, 9)
  "GroupAny\0" // IR(32347, 9)
  "GroupBroadcast\0" // IR(32356, 15)
  "SPV_OPERAND_TYPE_GROUP_OPERATION\0" // IR(32371, 33)
  "GroupIAdd\0" // IR(32404, 10)
  "GroupFAdd\0" // IR(32414, 10)
  "GroupFMin\0" // IR(32424, 10)
  "GroupUMin\0" // IR(32434, 10)
  "GroupSMin\0" // IR(32444, 10)
  "GroupFMax\0" // IR(32454, 10)
  "GroupUMax\0" // IR(32464, 10)
  "GroupSMax\0" // IR(32474, 10)
  "ReadPipe\0" // IR(32484, 9)
  "WritePipe\0" // IR(32493, 10)
  "ReservedReadPipe\0" // IR(32503, 17)
  "ReservedWritePipe\0" // IR(32520, 18)
  "ReserveReadPipePackets\0" // IR(32538, 23)
  "ReserveWritePipePackets\0" // IR(32561, 24)
  "CommitReadPipe\0" // IR(32585, 15)
  "CommitWritePipe\0" // IR(32600, 16)
  "IsValidReserveId\0" // IR(32616, 17)
  "GetNumPipePackets\0" // IR(32633, 18)
  "GetMaxPipePackets\0" // IR(32651, 18)
  "GroupReserveReadPipePackets\0" // IR(32669, 28)
  "GroupReserveWritePipePackets\0" // IR(32697, 29)
  "GroupCommitReadPipe\0" // IR(32726, 20)
  "GroupCommitWritePipe\0" // IR(32746, 21)
  "EnqueueMarker\0" // IR(32767, 14)
  "EnqueueKernel\0" // IR(32781, 14)
  "GetKernelNDrangeSubGroupCount\0" // IR(32795, 30)
  "GetKernelNDrangeMaxSubGroupSize\0" // IR(32825, 32)
  "GetKernelWorkGroupSize\0" // IR(32857, 23)
  "GetKernelPreferredWorkGroupSizeMultiple\0" // IR(32880, 40)
  "RetainEvent\0" // IR(32920, 12)
  "ReleaseEvent\0" // IR(32932, 13)
  "CreateUserEvent\0" // IR(32945, 16)
  "IsValidEvent\0" // IR(32961, 13)
  "SetUserEventStatus\0" // IR(32974, 19)
  "CaptureEventProfilingInfo\0" // IR(32993, 26)
  "GetDefaultQueue\0" // IR(33019, 16)
  "BuildNDRange\0" // IR(33035, 13)
  "ImageSparseSampleImplicitLod\0" // IR(33048, 29)
  "ImageSparseSampleExplicitLod\0" // IR(33077, 29)
  "ImageSparseSampleDrefImplicitLod\0" // IR(33106, 33)
  "ImageSparseSampleDrefExplicitLod\0" // IR(33139, 33)
  "ImageSparseSampleProjImplicitLod\0" // IR(33172, 33)
  "ImageSparseSampleProjExplicitLod\0" // IR(33205, 33)
  "ImageSparseSampleProjDrefImplicitLod\0" // IR(33238, 37)
  "ImageSparseSampleProjDrefExplicitLod\0" // IR(33275, 37)
  "ImageSparseFetch\0" // IR(33312, 17)
  "ImageSparseGather\0" // IR(33329, 18)
  "ImageSparseDrefGather\0" // IR(33347, 22)
  "ImageSparseTexelsResident\0" // IR(33369, 26)
  "NoLine\0" // IR(33395, 7)
  "AtomicFlagTestAndSet\0" // IR(33402, 21)
  "AtomicFlagClear\0" // IR(33423, 16)
  "ImageSparseRead\0" // IR(33439, 16)
  "SizeOf\0" // IR(33455, 7)
  "TypePipeStorage\0" // IR(33462, 16)
  "ConstantPipeStorage\0" // IR(33478, 20)
  "CreatePipeFromPipeStorage\0" // IR(33498, 26)
  "GetKernelLocalSizeForSubgroupCount\0" // IR(33524, 35)
  "GetKernelMaxNumSubgroups\0" // IR(33559, 25)
  "TypeNamedBarrier\0" // IR(33584, 17)
  "NamedBarrierInitialize\0" // IR(33601, 23)
  "MemoryNamedBarrier\0" // IR(33624, 19)
  "ModuleProcessed\0" // IR(33643, 16)
  "ExecutionModeId\0" // IR(33659, 16)
  "DecorateId\0" // IR(33675, 11)
  "GroupNonUniformElect\0" // IR(33686, 21)
  "GroupNonUniformAll\0" // IR(33707, 19)
  "GroupNonUniformAny\0" // IR(33726, 19)
  "GroupNonUniformAllEqual\0" // IR(33745, 24)
  "GroupNonUniformBroadcast\0" // IR(33769, 25)
  "GroupNonUniformBroadcastFirst\0" // IR(33794, 30)
  "GroupNonUniformInverseBallot\0" // IR(33824, 29)
  "GroupNonUniformBallotBitExtract\0" // IR(33853, 32)
  "GroupNonUniformBallotBitCount\0" // IR(33885, 30)
  "GroupNonUniformBallotFindLSB\0" // IR(33915, 29)
  "GroupNonUniformBallotFindMSB\0" // IR(33944, 29)
  "GroupNonUniformShuffleXor\0" // IR(33973, 26)
  "GroupNonUniformShuffleUp\0" // IR(33999, 25)
  "GroupNonUniformShuffleDown\0" // IR(34024, 27)
  "GroupNonUniformIAdd\0" // IR(34051, 20)
  "GroupNonUniformFAdd\0" // IR(34071, 20)
  "GroupNonUniformIMul\0" // IR(34091, 20)
  "GroupNonUniformFMul\0" // IR(34111, 20)
  "GroupNonUniformSMin\0" // IR(34131, 20)
  "GroupNonUniformUMin\0" // IR(34151, 20)
  "GroupNonUniformFMin\0" // IR(34171, 20)
  "GroupNonUniformSMax\0" // IR(34191, 20)
  "GroupNonUniformUMax\0" // IR(34211, 20)
  "GroupNonUniformFMax\0" // IR(34231, 20)
  "GroupNonUniformBitwiseAnd\0" // IR(34251, 26)
  "GroupNonUniformBitwiseOr\0" // IR(34277, 25)
  "GroupNonUniformBitwiseXor\0" // IR(34302, 26)
  "GroupNonUniformLogicalAnd\0" // IR(34328, 26)
  "GroupNonUniformLogicalOr\0" // IR(34354, 25)
  "GroupNonUniformLogicalXor\0" // IR(34379, 26)
  "GroupNonUniformQuadBroadcast\0" // IR(34405, 29)
  "GroupNonUniformQuadSwap\0" // IR(34434, 24)
  "CopyLogical\0" // IR(34458, 12)
  "PtrEqual\0" // IR(34470, 9)
  "PtrNotEqual\0" // IR(34479, 12)
  "PtrDiff\0" // IR(34491, 8)
  "ColorAttachmentReadEXT\0" // IR(34499, 23)
  "DepthAttachmentReadEXT\0" // IR(34522, 23)
  "StencilAttachmentReadEXT\0" // IR(34545, 25)
  "TypeTensorARM\0" // IR(34570, 14)
  "SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS\0" // IR(34584, 42)
  "TensorReadARM\0" // IR(34626, 14)
  "TensorWriteARM\0" // IR(34640, 15)
  "TensorQuerySizeARM\0" // IR(34655, 19)
  "GraphConstantARM\0" // IR(34674, 17)
  "GraphEntryPointARM\0" // IR(34691, 19)
  "GraphInputARM\0" // IR(34710, 14)
  "GraphSetOutputARM\0" // IR(34724, 18)
  "GraphEndARM\0" // IR(34742, 12)
  "TypeGraphARM\0" // IR(34754, 13)
  "TerminateInvocation\0" // IR(34767, 20)
  "TypeUntypedPointerKHR\0" // IR(34787, 22)
  "UntypedVariableKHR\0" // IR(34809, 19)
  "UntypedAccessChainKHR\0" // IR(34828, 22)
  "UntypedInBoundsAccessChainKHR\0" // IR(34850, 30)
  "SubgroupFirstInvocationKHR\0" // IR(34880, 27)
  "UntypedPtrAccessChainKHR\0" // IR(34907, 25)
  "UntypedInBoundsPtrAccessChainKHR\0" // IR(34932, 33)
  "UntypedArrayLengthKHR\0" // IR(34965, 22)
  "UntypedPrefetchKHR\0" // IR(34987, 19)
  "FmaKHR\0" // IR(35006, 7)
  "SubgroupAllKHR\0" // IR(35013, 15)
  "SubgroupAnyKHR\0" // IR(35028, 15)
  "SubgroupAllEqualKHR\0" // IR(35043, 20)
  "SubgroupReadInvocationKHR\0" // IR(35063, 26)
  "ExtInstWithForwardRefsKHR\0" // IR(35089, 26)
  "UntypedGroupAsyncCopyKHR\0" // IR(35115, 25)
  "TraceRayKHR\0" // IR(35140, 12)
  "ExecuteCallableKHR\0" // IR(35152, 19)
  "ConvertUToAccelerationStructureKHR\0" // IR(35171, 35)
  "IgnoreIntersectionKHR\0" // IR(35206, 22)
  "TerminateRayKHR\0" // IR(35228, 16)
  "SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT\0" // IR(35244, 47)
  "SDot\0" // IR(35291, 5)
  "SDotKHR\0" // IR(35296, 8)
  "UDot\0" // IR(35304, 5)
  "UDotKHR\0" // IR(35309, 8)
  "SUDot\0" // IR(35317, 6)
  "SUDotKHR\0" // IR(35323, 9)
  "SDotAccSat\0" // IR(35332, 11)
  "SDotAccSatKHR\0" // IR(35343, 14)
  "UDotAccSat\0" // IR(35357, 11)
  "UDotAccSatKHR\0" // IR(35368, 14)
  "SUDotAccSat\0" // IR(35382, 12)
  "SUDotAccSatKHR\0" // IR(35394, 15)
  "TypeCooperativeMatrixKHR\0" // IR(35409, 25)
  "CooperativeMatrixLoadKHR\0" // IR(35434, 25)
  "CooperativeMatrixStoreKHR\0" // IR(35459, 26)
  "SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS\0" // IR(35485, 54)
  "CooperativeMatrixMulAddKHR\0" // IR(35539, 27)
  "CooperativeMatrixLengthKHR\0" // IR(35566, 27)
  "ConstantCompositeReplicateEXT\0" // IR(35593, 30)
  "SpecConstantCompositeReplicateEXT\0" // IR(35623, 34)
  "CompositeConstructReplicateEXT\0" // IR(35657, 31)
  "TypeRayQueryKHR\0" // IR(35688, 16)
  "RayQueryInitializeKHR\0" // IR(35704, 22)
  "RayQueryTerminateKHR\0" // IR(35726, 21)
  "RayQueryGenerateIntersectionKHR\0" // IR(35747, 32)
  "RayQueryConfirmIntersectionKHR\0" // IR(35779, 31)
  "RayQueryProceedKHR\0" // IR(35810, 19)
  "RayQueryGetIntersectionTypeKHR\0" // IR(35829, 31)
  "ImageSampleWeightedQCOM\0" // IR(35860, 24)
  "ImageBoxFilterQCOM\0" // IR(35884, 19)
  "ImageBlockMatchSSDQCOM\0" // IR(35903, 23)
  "ImageBlockMatchSADQCOM\0" // IR(35926, 23)
  "BitCastArrayQCOM\0" // IR(35949, 17)
  "ImageBlockMatchWindowSSDQCOM\0" // IR(35966, 29)
  "ImageBlockMatchWindowSADQCOM\0" // IR(35995, 29)
  "ImageBlockMatchGatherSSDQCOM\0" // IR(36024, 29)
  "ImageBlockMatchGatherSADQCOM\0" // IR(36053, 29)
  "CompositeConstructCoopMatQCOM\0" // IR(36082, 30)
  "CompositeExtractCoopMatQCOM\0" // IR(36112, 28)
  "ExtractSubArrayQCOM\0" // IR(36140, 20)
  "GroupIAddNonUniformAMD\0" // IR(36160, 23)
  "GroupFAddNonUniformAMD\0" // IR(36183, 23)
  "GroupFMinNonUniformAMD\0" // IR(36206, 23)
  "GroupUMinNonUniformAMD\0" // IR(36229, 23)
  "GroupSMinNonUniformAMD\0" // IR(36252, 23)
  "GroupFMaxNonUniformAMD\0" // IR(36275, 23)
  "GroupUMaxNonUniformAMD\0" // IR(36298, 23)
  "GroupSMaxNonUniformAMD\0" // IR(36321, 23)
  "FragmentMaskFetchAMD\0" // IR(36344, 21)
  "FragmentFetchAMD\0" // IR(36365, 17)
  "ReadClockKHR\0" // IR(36382, 13)
  "AllocateNodePayloadsAMDX\0" // IR(36395, 25)
  "EnqueueNodePayloadsAMDX\0" // IR(36420, 24)
  "TypeNodePayloadArrayAMDX\0" // IR(36444, 25)
  "FinishWritingNodePayloadAMDX\0" // IR(36469, 29)
  "NodePayloadArrayLengthAMDX\0" // IR(36498, 27)
  "IsNodePayloadValidAMDX\0" // IR(36525, 23)
  "ConstantStringAMDX\0" // IR(36548, 19)
  "SpecConstantStringAMDX\0" // IR(36567, 23)
  "GroupNonUniformQuadAllKHR\0" // IR(36590, 26)
  "GroupNonUniformQuadAnyKHR\0" // IR(36616, 26)
  "TypeBufferEXT\0" // IR(36642, 14)
  "BufferPointerEXT\0" // IR(36656, 17)
  "UntypedImageTexelPointerEXT\0" // IR(36673, 28)
  "MemberDecorateIdEXT\0" // IR(36701, 20)
  "ConstantSizeOfEXT\0" // IR(36721, 18)
  "HitObjectRecordHitMotionNV\0" // IR(36739, 27)
  "HitObjectRecordHitWithIndexMotionNV\0" // IR(36766, 36)
  "HitObjectRecordMissMotionNV\0" // IR(36802, 28)
  "HitObjectGetWorldToObjectNV\0" // IR(36830, 28)
  "HitObjectGetObjectToWorldNV\0" // IR(36858, 28)
  "HitObjectGetObjectRayDirectionNV\0" // IR(36886, 33)
  "HitObjectGetObjectRayOriginNV\0" // IR(36919, 30)
  "HitObjectTraceRayMotionNV\0" // IR(36949, 26)
  "HitObjectGetShaderRecordBufferHandleNV\0" // IR(36975, 39)
  "HitObjectGetShaderBindingTableRecordIndexNV\0" // IR(37014, 44)
  "HitObjectRecordEmptyNV\0" // IR(37058, 23)
  "HitObjectTraceRayNV\0" // IR(37081, 20)
  "HitObjectRecordHitNV\0" // IR(37101, 21)
  "HitObjectRecordHitWithIndexNV\0" // IR(37122, 30)
  "HitObjectRecordMissNV\0" // IR(37152, 22)
  "HitObjectExecuteShaderNV\0" // IR(37174, 25)
  "HitObjectGetCurrentTimeNV\0" // IR(37199, 26)
  "HitObjectGetAttributesNV\0" // IR(37225, 25)
  "HitObjectGetHitKindNV\0" // IR(37250, 22)
  "HitObjectGetPrimitiveIndexNV\0" // IR(37272, 29)
  "HitObjectGetGeometryIndexNV\0" // IR(37301, 28)
  "HitObjectGetInstanceIdNV\0" // IR(37329, 25)
  "HitObjectGetInstanceCustomIndexNV\0" // IR(37354, 34)
  "HitObjectGetWorldRayDirectionNV\0" // IR(37388, 32)
  "HitObjectGetWorldRayOriginNV\0" // IR(37420, 29)
  "HitObjectGetRayTMaxNV\0" // IR(37449, 22)
  "HitObjectGetRayTMinNV\0" // IR(37471, 22)
  "HitObjectIsEmptyNV\0" // IR(37493, 19)
  "HitObjectIsHitNV\0" // IR(37512, 17)
  "HitObjectIsMissNV\0" // IR(37529, 18)
  "ReorderThreadWithHitObjectNV\0" // IR(37547, 29)
  "ReorderThreadWithHintNV\0" // IR(37576, 24)
  "TypeHitObjectNV\0" // IR(37600, 16)
  "ImageSampleFootprintNV\0" // IR(37616, 23)
  "TypeVectorIdEXT\0" // IR(37639, 16)
  "TypeCooperativeVectorNV\0" // IR(37655, 24)
  "CooperativeVectorMatrixMulNV\0" // IR(37679, 29)
  "CooperativeVectorOuterProductAccumulateNV\0" // IR(37708, 42)
  "CooperativeVectorReduceSumAccumulateNV\0" // IR(37750, 39)
  "CooperativeVectorMatrixMulAddNV\0" // IR(37789, 32)
  "CooperativeMatrixConvertNV\0" // IR(37821, 27)
  "EmitMeshTasksEXT\0" // IR(37848, 17)
  "SetMeshOutputsEXT\0" // IR(37865, 18)
  "GroupNonUniformPartitionEXT\0" // IR(37883, 28)
  "GroupNonUniformPartitionNV\0" // IR(37911, 27)
  "WritePackedPrimitiveIndices4x8NV\0" // IR(37938, 33)
  "FetchMicroTriangleVertexPositionNV\0" // IR(37971, 35)
  "FetchMicroTriangleVertexBarycentricNV\0" // IR(38006, 38)
  "CooperativeVectorLoadNV\0" // IR(38044, 24)
  "CooperativeVectorStoreNV\0" // IR(38068, 25)
  "HitObjectRecordFromQueryEXT\0" // IR(38093, 28)
  "HitObjectRecordMissEXT\0" // IR(38121, 23)
  "HitObjectRecordMissMotionEXT\0" // IR(38144, 29)
  "HitObjectGetIntersectionTriangleVertexPositionsEXT\0" // IR(38173, 51)
  "HitObjectGetRayFlagsEXT\0" // IR(38224, 24)
  "HitObjectSetShaderBindingTableRecordIndexEXT\0" // IR(38248, 45)
  "HitObjectReorderExecuteShaderEXT\0" // IR(38293, 33)
  "HitObjectTraceReorderExecuteEXT\0" // IR(38326, 32)
  "HitObjectTraceMotionReorderExecuteEXT\0" // IR(38358, 38)
  "TypeHitObjectEXT\0" // IR(38396, 17)
  "ReorderThreadWithHintEXT\0" // IR(38413, 25)
  "ReorderThreadWithHitObjectEXT\0" // IR(38438, 30)
  "HitObjectTraceRayEXT\0" // IR(38468, 21)
  "HitObjectTraceRayMotionEXT\0" // IR(38489, 27)
  "HitObjectRecordEmptyEXT\0" // IR(38516, 24)
  "HitObjectExecuteShaderEXT\0" // IR(38540, 26)
  "HitObjectGetCurrentTimeEXT\0" // IR(38566, 27)
  "HitObjectGetAttributesEXT\0" // IR(38593, 26)
  "HitObjectGetHitKindEXT\0" // IR(38619, 23)
  "HitObjectGetPrimitiveIndexEXT\0" // IR(38642, 30)
  "HitObjectGetGeometryIndexEXT\0" // IR(38672, 29)
  "HitObjectGetInstanceIdEXT\0" // IR(38701, 26)
  "HitObjectGetInstanceCustomIndexEXT\0" // IR(38727, 35)
  "HitObjectGetObjectRayOriginEXT\0" // IR(38762, 31)
  "HitObjectGetObjectRayDirectionEXT\0" // IR(38793, 34)
  "HitObjectGetWorldRayDirectionEXT\0" // IR(38827, 33)
  "HitObjectGetWorldRayOriginEXT\0" // IR(38860, 30)
  "HitObjectGetObjectToWorldEXT\0" // IR(38890, 29)
  "HitObjectGetWorldToObjectEXT\0" // IR(38919, 29)
  "HitObjectGetRayTMaxEXT\0" // IR(38948, 23)
  "ReportIntersectionKHR\0" // IR(38971, 22)
  "ReportIntersectionNV\0" // IR(38993, 21)
  "IgnoreIntersectionNV\0" // IR(39014, 21)
  "TerminateRayNV\0" // IR(39035, 15)
  "TraceNV\0" // IR(39050, 8)
  "TraceMotionNV\0" // IR(39058, 14)
  "TraceRayMotionNV\0" // IR(39072, 17)
  "RayQueryGetIntersectionTriangleVertexPositionsKHR\0" // IR(39089, 50)
  "TypeAccelerationStructureKHR\0" // IR(39139, 29)
  "TypeAccelerationStructureNV\0" // IR(39168, 28)
  "ExecuteCallableNV\0" // IR(39196, 18)
  "RayQueryGetIntersectionClusterIdNV\0" // IR(39214, 35)
  "RayQueryGetClusterIdNV\0" // IR(39249, 23)
  "HitObjectGetClusterIdNV\0" // IR(39272, 24)
  "HitObjectGetRayTMinEXT\0" // IR(39296, 23)
  "HitObjectGetShaderBindingTableRecordIndexEXT\0" // IR(39319, 45)
  "HitObjectGetShaderRecordBufferHandleEXT\0" // IR(39364, 40)
  "HitObjectIsEmptyEXT\0" // IR(39404, 20)
  "HitObjectIsHitEXT\0" // IR(39424, 18)
  "HitObjectIsMissEXT\0" // IR(39442, 19)
  "TypeCooperativeMatrixNV\0" // IR(39461, 24)
  "CooperativeMatrixLoadNV\0" // IR(39485, 24)
  "CooperativeMatrixStoreNV\0" // IR(39509, 25)
  "CooperativeMatrixMulAddNV\0" // IR(39534, 26)
  "CooperativeMatrixLengthNV\0" // IR(39560, 26)
  "BeginInvocationInterlockEXT\0" // IR(39586, 28)
  "EndInvocationInterlockEXT\0" // IR(39614, 26)
  "SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE\0" // IR(39640, 43)
  "CooperativeMatrixReduceNV\0" // IR(39683, 26)
  "SPV_OPERAND_TYPE_MEMORY_ACCESS\0" // IR(39709, 31)
  "SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS\0" // IR(39740, 44)
  "CooperativeMatrixLoadTensorNV\0" // IR(39784, 30)
  "CooperativeMatrixStoreTensorNV\0" // IR(39814, 31)
  "CooperativeMatrixPerElementOpNV\0" // IR(39845, 32)
  "TypeTensorLayoutNV\0" // IR(39877, 19)
  "TypeTensorViewNV\0" // IR(39896, 17)
  "CreateTensorLayoutNV\0" // IR(39913, 21)
  "TensorLayoutSetDimensionNV\0" // IR(39934, 27)
  "TensorLayoutSetStrideNV\0" // IR(39961, 24)
  "TensorLayoutSliceNV\0" // IR(39985, 20)
  "TensorLayoutSetClampValueNV\0" // IR(40005, 28)
  "CreateTensorViewNV\0" // IR(40033, 19)
  "TensorViewSetDimensionNV\0" // IR(40052, 25)
  "TensorViewSetStrideNV\0" // IR(40077, 22)
  "IsHelperInvocationEXT\0" // IR(40099, 22)
  "TensorViewSetClipNV\0" // IR(40121, 20)
  "TensorLayoutSetBlockSizeNV\0" // IR(40141, 27)
  "CooperativeMatrixTransposeNV\0" // IR(40168, 29)
  "ConvertUToImageNV\0" // IR(40197, 18)
  "ConvertUToSamplerNV\0" // IR(40215, 20)
  "ConvertImageToUNV\0" // IR(40235, 18)
  "ConvertSamplerToUNV\0" // IR(40253, 20)
  "ConvertUToSampledImageNV\0" // IR(40273, 25)
  "ConvertSampledImageToUNV\0" // IR(40298, 25)
  "SamplerImageAddressingModeNV\0" // IR(40323, 29)
  "SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS\0" // IR(40352, 52)
  "RawAccessChainNV\0" // IR(40404, 17)
  "RayQueryGetIntersectionSpherePositionNV\0" // IR(40421, 40)
  "RayQueryGetIntersectionSphereRadiusNV\0" // IR(40461, 38)
  "RayQueryGetIntersectionLSSPositionsNV\0" // IR(40499, 38)
  "RayQueryGetIntersectionLSSRadiiNV\0" // IR(40537, 34)
  "RayQueryGetIntersectionLSSHitValueNV\0" // IR(40571, 37)
  "HitObjectGetSpherePositionNV\0" // IR(40608, 29)
  "HitObjectGetSphereRadiusNV\0" // IR(40637, 27)
  "HitObjectGetLSSPositionsNV\0" // IR(40664, 27)
  "HitObjectGetLSSRadiiNV\0" // IR(40691, 23)
  "HitObjectIsSphereHitNV\0" // IR(40714, 23)
  "HitObjectIsLSSHitNV\0" // IR(40737, 20)
  "RayQueryIsSphereHitNV\0" // IR(40757, 22)
  "RayQueryIsLSSHitNV\0" // IR(40779, 19)
  "SubgroupShuffleDownINTEL\0" // IR(40798, 25)
  "SubgroupShuffleUpINTEL\0" // IR(40823, 23)
  "SubgroupShuffleXorINTEL\0" // IR(40846, 24)
  "SubgroupBlockReadINTEL\0" // IR(40870, 23)
  "SubgroupBlockWriteINTEL\0" // IR(40893, 24)
  "SubgroupImageBlockReadINTEL\0" // IR(40917, 28)
  "SubgroupImageBlockWriteINTEL\0" // IR(40945, 29)
  "SubgroupImageMediaBlockReadINTEL\0" // IR(40974, 33)
  "SubgroupImageMediaBlockWriteINTEL\0" // IR(41007, 34)
  "UCountLeadingZerosINTEL\0" // IR(41041, 24)
  "UCountTrailingZerosINTEL\0" // IR(41065, 25)
  "AbsISubINTEL\0" // IR(41090, 13)
  "AbsUSubINTEL\0" // IR(41103, 13)
  "IAddSatINTEL\0" // IR(41116, 13)
  "UAddSatINTEL\0" // IR(41129, 13)
  "IAverageINTEL\0" // IR(41142, 14)
  "UAverageINTEL\0" // IR(41156, 14)
  "IAverageRoundedINTEL\0" // IR(41170, 21)
  "UAverageRoundedINTEL\0" // IR(41191, 21)
  "ISubSatINTEL\0" // IR(41212, 13)
  "USubSatINTEL\0" // IR(41225, 13)
  "IMul32x16INTEL\0" // IR(41238, 15)
  "UMul32x16INTEL\0" // IR(41253, 15)
  "ConstantFunctionPointerINTEL\0" // IR(41268, 29)
  "FunctionPointerCallINTEL\0" // IR(41297, 25)
  "AsmTargetINTEL\0" // IR(41322, 15)
  "AsmCallINTEL\0" // IR(41337, 13)
  "AtomicFMinEXT\0" // IR(41350, 14)
  "AtomicFMaxEXT\0" // IR(41364, 14)
  "AssumeTrueKHR\0" // IR(41378, 14)
  "ExpectKHR\0" // IR(41392, 10)
  "DecorateString\0" // IR(41402, 15)
  "DecorateStringGOOGLE\0" // IR(41417, 21)
  "MemberDecorateString\0" // IR(41438, 21)
  "MemberDecorateStringGOOGLE\0" // IR(41459, 27)
  "VmeImageINTEL\0" // IR(41486, 14)
  "TypeVmeImageINTEL\0" // IR(41500, 18)
  "TypeAvcImePayloadINTEL\0" // IR(41518, 23)
  "TypeAvcRefPayloadINTEL\0" // IR(41541, 23)
  "TypeAvcSicPayloadINTEL\0" // IR(41564, 23)
  "TypeAvcMcePayloadINTEL\0" // IR(41587, 23)
  "TypeAvcMceResultINTEL\0" // IR(41610, 22)
  "TypeAvcImeResultINTEL\0" // IR(41632, 22)
  "TypeAvcImeResultSingleReferenceStreamoutINTEL\0" // IR(41654, 46)
  "TypeAvcImeResultDualReferenceStreamoutINTEL\0" // IR(41700, 44)
  "TypeAvcImeSingleReferenceStreaminINTEL\0" // IR(41744, 39)
  "TypeAvcImeDualReferenceStreaminINTEL\0" // IR(41783, 37)
  "TypeAvcRefResultINTEL\0" // IR(41820, 22)
  "TypeAvcSicResultINTEL\0" // IR(41842, 22)
  "SubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL\0" // IR(41864, 60)
  "SubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL\0" // IR(41924, 53)
  "SubgroupAvcMceGetDefaultInterShapePenaltyINTEL\0" // IR(41977, 47)
  "SubgroupAvcMceSetInterShapePenaltyINTEL\0" // IR(42024, 40)
  "SubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL\0" // IR(42064, 51)
  "SubgroupAvcMceSetInterDirectionPenaltyINTEL\0" // IR(42115, 44)
  "SubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL\0" // IR(42159, 51)
  "SubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL\0" // IR(42210, 56)
  "SubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL\0" // IR(42266, 50)
  "SubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL\0" // IR(42316, 52)
  "SubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL\0" // IR(42368, 49)
  "SubgroupAvcMceSetMotionVectorCostFunctionINTEL\0" // IR(42417, 47)
  "SubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL\0" // IR(42464, 50)
  "SubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL\0" // IR(42514, 51)
  "SubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL\0" // IR(42565, 56)
  "SubgroupAvcMceSetAcOnlyHaarINTEL\0" // IR(42621, 33)
  "SubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL\0" // IR(42654, 52)
  "SubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL\0" // IR(42706, 61)
  "SubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL\0" // IR(42767, 61)
  "SubgroupAvcMceConvertToImePayloadINTEL\0" // IR(42828, 39)
  "SubgroupAvcMceConvertToImeResultINTEL\0" // IR(42867, 38)
  "SubgroupAvcMceConvertToRefPayloadINTEL\0" // IR(42905, 39)
  "SubgroupAvcMceConvertToRefResultINTEL\0" // IR(42944, 38)
  "SubgroupAvcMceConvertToSicPayloadINTEL\0" // IR(42982, 39)
  "SubgroupAvcMceConvertToSicResultINTEL\0" // IR(43021, 38)
  "SubgroupAvcMceGetMotionVectorsINTEL\0" // IR(43059, 36)
  "SubgroupAvcMceGetInterDistortionsINTEL\0" // IR(43095, 39)
  "SubgroupAvcMceGetBestInterDistortionsINTEL\0" // IR(43134, 43)
  "SubgroupAvcMceGetInterMajorShapeINTEL\0" // IR(43177, 38)
  "SubgroupAvcMceGetInterMinorShapeINTEL\0" // IR(43215, 38)
  "SubgroupAvcMceGetInterDirectionsINTEL\0" // IR(43253, 38)
  "SubgroupAvcMceGetInterMotionVectorCountINTEL\0" // IR(43291, 45)
  "SubgroupAvcMceGetInterReferenceIdsINTEL\0" // IR(43336, 40)
  "SubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL\0" // IR(43376, 62)
  "SubgroupAvcImeInitializeINTEL\0" // IR(43438, 30)
  "SubgroupAvcImeSetSingleReferenceINTEL\0" // IR(43468, 38)
  "SubgroupAvcImeSetDualReferenceINTEL\0" // IR(43506, 36)
  "SubgroupAvcImeRefWindowSizeINTEL\0" // IR(43542, 33)
  "SubgroupAvcImeAdjustRefOffsetINTEL\0" // IR(43575, 35)
  "SubgroupAvcImeConvertToMcePayloadINTEL\0" // IR(43610, 39)
  "SubgroupAvcImeSetMaxMotionVectorCountINTEL\0" // IR(43649, 43)
  "SubgroupAvcImeSetUnidirectionalMixDisableINTEL\0" // IR(43692, 47)
  "SubgroupAvcImeSetEarlySearchTerminationThresholdINTEL\0" // IR(43739, 54)
  "SubgroupAvcImeSetWeightedSadINTEL\0" // IR(43793, 34)
  "SubgroupAvcImeEvaluateWithSingleReferenceINTEL\0" // IR(43827, 47)
  "SubgroupAvcImeEvaluateWithDualReferenceINTEL\0" // IR(43874, 45)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL\0" // IR(43919, 55)
  "SubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL\0" // IR(43974, 53)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL\0" // IR(44027, 56)
  "SubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL\0" // IR(44083, 54)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL\0" // IR(44137, 58)
  "SubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL\0" // IR(44195, 56)
  "SubgroupAvcImeConvertToMceResultINTEL\0" // IR(44251, 38)
  "SubgroupAvcImeGetSingleReferenceStreaminINTEL\0" // IR(44289, 46)
  "SubgroupAvcImeGetDualReferenceStreaminINTEL\0" // IR(44335, 44)
  "SubgroupAvcImeStripSingleReferenceStreamoutINTEL\0" // IR(44379, 49)
  "SubgroupAvcImeStripDualReferenceStreamoutINTEL\0" // IR(44428, 47)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL\0" // IR(44475, 70)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL\0" // IR(44545, 68)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL\0" // IR(44613, 69)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL\0" // IR(44682, 68)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL\0" // IR(44750, 66)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL\0" // IR(44816, 67)
  "SubgroupAvcImeGetBorderReachedINTEL\0" // IR(44883, 36)
  "SubgroupAvcImeGetTruncatedSearchIndicationINTEL\0" // IR(44919, 48)
  "SubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL\0" // IR(44967, 59)
  "SubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL\0" // IR(45026, 58)
  "SubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL\0" // IR(45084, 56)
  "SubgroupAvcFmeInitializeINTEL\0" // IR(45140, 30)
  "SubgroupAvcBmeInitializeINTEL\0" // IR(45170, 30)
  "SubgroupAvcRefConvertToMcePayloadINTEL\0" // IR(45200, 39)
  "SubgroupAvcRefSetBidirectionalMixDisableINTEL\0" // IR(45239, 46)
  "SubgroupAvcRefSetBilinearFilterEnableINTEL\0" // IR(45285, 43)
  "SubgroupAvcRefEvaluateWithSingleReferenceINTEL\0" // IR(45328, 47)
  "SubgroupAvcRefEvaluateWithDualReferenceINTEL\0" // IR(45375, 45)
  "SubgroupAvcRefEvaluateWithMultiReferenceINTEL\0" // IR(45420, 46)
  "SubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL\0" // IR(45466, 56)
  "SubgroupAvcRefConvertToMceResultINTEL\0" // IR(45522, 38)
  "SubgroupAvcSicInitializeINTEL\0" // IR(45560, 30)
  "SubgroupAvcSicConfigureSkcINTEL\0" // IR(45590, 32)
  "SubgroupAvcSicConfigureIpeLumaINTEL\0" // IR(45622, 36)
  "SubgroupAvcSicConfigureIpeLumaChromaINTEL\0" // IR(45658, 42)
  "SubgroupAvcSicGetMotionVectorMaskINTEL\0" // IR(45700, 39)
  "SubgroupAvcSicConvertToMcePayloadINTEL\0" // IR(45739, 39)
  "SubgroupAvcSicSetIntraLumaShapePenaltyINTEL\0" // IR(45778, 44)
  "SubgroupAvcSicSetIntraLumaModeCostFunctionINTEL\0" // IR(45822, 48)
  "SubgroupAvcSicSetIntraChromaModeCostFunctionINTEL\0" // IR(45870, 50)
  "SubgroupAvcSicSetBilinearFilterEnableINTEL\0" // IR(45920, 43)
  "SubgroupAvcSicSetSkcForwardTransformEnableINTEL\0" // IR(45963, 48)
  "SubgroupAvcSicSetBlockBasedRawSkipSadINTEL\0" // IR(46011, 43)
  "SubgroupAvcSicEvaluateIpeINTEL\0" // IR(46054, 31)
  "SubgroupAvcSicEvaluateWithSingleReferenceINTEL\0" // IR(46085, 47)
  "SubgroupAvcSicEvaluateWithDualReferenceINTEL\0" // IR(46132, 45)
  "SubgroupAvcSicEvaluateWithMultiReferenceINTEL\0" // IR(46177, 46)
  "SubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL\0" // IR(46223, 56)
  "SubgroupAvcSicConvertToMceResultINTEL\0" // IR(46279, 38)
  "SubgroupAvcSicGetIpeLumaShapeINTEL\0" // IR(46317, 35)
  "SubgroupAvcSicGetBestIpeLumaDistortionINTEL\0" // IR(46352, 44)
  "SubgroupAvcSicGetBestIpeChromaDistortionINTEL\0" // IR(46396, 46)
  "SubgroupAvcSicGetPackedIpeLumaModesINTEL\0" // IR(46442, 41)
  "SubgroupAvcSicGetIpeChromaModeINTEL\0" // IR(46483, 36)
  "SubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL\0" // IR(46519, 50)
  "SubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL\0" // IR(46569, 48)
  "SubgroupAvcSicGetInterRawSadsINTEL\0" // IR(46617, 35)
  "SaveMemoryINTEL\0" // IR(46652, 16)
  "RestoreMemoryINTEL\0" // IR(46668, 19)
  "ArbitraryFloatSinCosPiALTERA\0" // IR(46687, 29)
  "ArbitraryFloatSinCosPiINTEL\0" // IR(46716, 28)
  "ArbitraryFloatCastALTERA\0" // IR(46744, 25)
  "ArbitraryFloatCastINTEL\0" // IR(46769, 24)
  "ArbitraryFloatCastFromIntALTERA\0" // IR(46793, 32)
  "ArbitraryFloatCastFromIntINTEL\0" // IR(46825, 31)
  "ArbitraryFloatCastToIntALTERA\0" // IR(46856, 30)
  "ArbitraryFloatCastToIntINTEL\0" // IR(46886, 29)
  "ArbitraryFloatAddALTERA\0" // IR(46915, 24)
  "ArbitraryFloatAddINTEL\0" // IR(46939, 23)
  "ArbitraryFloatSubALTERA\0" // IR(46962, 24)
  "ArbitraryFloatSubINTEL\0" // IR(46986, 23)
  "ArbitraryFloatMulALTERA\0" // IR(47009, 24)
  "ArbitraryFloatMulINTEL\0" // IR(47033, 23)
  "ArbitraryFloatDivALTERA\0" // IR(47056, 24)
  "ArbitraryFloatDivINTEL\0" // IR(47080, 23)
  "ArbitraryFloatGTALTERA\0" // IR(47103, 23)
  "ArbitraryFloatGTINTEL\0" // IR(47126, 22)
  "ArbitraryFloatGEALTERA\0" // IR(47148, 23)
  "ArbitraryFloatGEINTEL\0" // IR(47171, 22)
  "ArbitraryFloatLTALTERA\0" // IR(47193, 23)
  "ArbitraryFloatLTINTEL\0" // IR(47216, 22)
  "ArbitraryFloatLEALTERA\0" // IR(47238, 23)
  "ArbitraryFloatLEINTEL\0" // IR(47261, 22)
  "ArbitraryFloatEQALTERA\0" // IR(47283, 23)
  "ArbitraryFloatEQINTEL\0" // IR(47306, 22)
  "ArbitraryFloatRecipALTERA\0" // IR(47328, 26)
  "ArbitraryFloatRecipINTEL\0" // IR(47354, 25)
  "ArbitraryFloatRSqrtALTERA\0" // IR(47379, 26)
  "ArbitraryFloatRSqrtINTEL\0" // IR(47405, 25)
  "ArbitraryFloatCbrtALTERA\0" // IR(47430, 25)
  "ArbitraryFloatCbrtINTEL\0" // IR(47455, 24)
  "ArbitraryFloatHypotALTERA\0" // IR(47479, 26)
  "ArbitraryFloatHypotINTEL\0" // IR(47505, 25)
  "ArbitraryFloatSqrtALTERA\0" // IR(47530, 25)
  "ArbitraryFloatSqrtINTEL\0" // IR(47555, 24)
  "ArbitraryFloatLogINTEL\0" // IR(47579, 23)
  "ArbitraryFloatLog2INTEL\0" // IR(47602, 24)
  "ArbitraryFloatLog10INTEL\0" // IR(47626, 25)
  "ArbitraryFloatLog1pINTEL\0" // IR(47651, 25)
  "ArbitraryFloatExpINTEL\0" // IR(47676, 23)
  "ArbitraryFloatExp2INTEL\0" // IR(47699, 24)
  "ArbitraryFloatExp10INTEL\0" // IR(47723, 25)
  "ArbitraryFloatExpm1INTEL\0" // IR(47748, 25)
  "ArbitraryFloatSinINTEL\0" // IR(47773, 23)
  "ArbitraryFloatCosINTEL\0" // IR(47796, 23)
  "ArbitraryFloatSinCosINTEL\0" // IR(47819, 26)
  "ArbitraryFloatSinPiINTEL\0" // IR(47845, 25)
  "ArbitraryFloatCosPiINTEL\0" // IR(47870, 25)
  "ArbitraryFloatASinINTEL\0" // IR(47895, 24)
  "ArbitraryFloatASinPiINTEL\0" // IR(47919, 26)
  "ArbitraryFloatACosINTEL\0" // IR(47945, 24)
  "ArbitraryFloatACosPiINTEL\0" // IR(47969, 26)
  "ArbitraryFloatATanINTEL\0" // IR(47995, 24)
  "ArbitraryFloatATanPiINTEL\0" // IR(48019, 26)
  "ArbitraryFloatATan2INTEL\0" // IR(48045, 25)
  "ArbitraryFloatPowINTEL\0" // IR(48070, 23)
  "ArbitraryFloatPowRINTEL\0" // IR(48093, 24)
  "ArbitraryFloatPowNINTEL\0" // IR(48117, 24)
  "LoopControlINTEL\0" // IR(48141, 17)
  "AliasDomainDeclINTEL\0" // IR(48158, 21)
  "AliasScopeDeclINTEL\0" // IR(48179, 20)
  "AliasScopeListDeclINTEL\0" // IR(48199, 24)
  "FixedSqrtALTERA\0" // IR(48223, 16)
  "FixedSqrtINTEL\0" // IR(48239, 15)
  "FixedRecipALTERA\0" // IR(48254, 17)
  "FixedRecipINTEL\0" // IR(48271, 16)
  "FixedRsqrtALTERA\0" // IR(48287, 17)
  "FixedRsqrtINTEL\0" // IR(48304, 16)
  "FixedSinALTERA\0" // IR(48320, 15)
  "FixedSinINTEL\0" // IR(48335, 14)
  "FixedCosALTERA\0" // IR(48349, 15)
  "FixedCosINTEL\0" // IR(48364, 14)
  "FixedSinCosALTERA\0" // IR(48378, 18)
  "FixedSinCosINTEL\0" // IR(48396, 17)
  "FixedSinPiALTERA\0" // IR(48413, 17)
  "FixedSinPiINTEL\0" // IR(48430, 16)
  "FixedCosPiALTERA\0" // IR(48446, 17)
  "FixedCosPiINTEL\0" // IR(48463, 16)
  "FixedSinCosPiALTERA\0" // IR(48479, 20)
  "FixedSinCosPiINTEL\0" // IR(48499, 19)
  "FixedLogALTERA\0" // IR(48518, 15)
  "FixedLogINTEL\0" // IR(48533, 14)
  "FixedExpALTERA\0" // IR(48547, 15)
  "FixedExpINTEL\0" // IR(48562, 14)
  "PtrCastToCrossWorkgroupALTERA\0" // IR(48576, 30)
  "PtrCastToCrossWorkgroupINTEL\0" // IR(48606, 29)
  "CrossWorkgroupCastToPtrALTERA\0" // IR(48635, 30)
  "CrossWorkgroupCastToPtrINTEL\0" // IR(48665, 29)
  "ReadPipeBlockingALTERA\0" // IR(48694, 23)
  "ReadPipeBlockingINTEL\0" // IR(48717, 22)
  "WritePipeBlockingALTERA\0" // IR(48739, 24)
  "WritePipeBlockingINTEL\0" // IR(48763, 23)
  "RayQueryGetRayTMinKHR\0" // IR(48786, 22)
  "RayQueryGetRayFlagsKHR\0" // IR(48808, 23)
  "RayQueryGetIntersectionTKHR\0" // IR(48831, 28)
  "RayQueryGetIntersectionInstanceCustomIndexKHR\0" // IR(48859, 46)
  "RayQueryGetIntersectionInstanceIdKHR\0" // IR(48905, 37)
  "RayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR\0" // IR(48942, 65)
  "RayQueryGetIntersectionGeometryIndexKHR\0" // IR(49007, 40)
  "RayQueryGetIntersectionPrimitiveIndexKHR\0" // IR(49047, 41)
  "RayQueryGetIntersectionBarycentricsKHR\0" // IR(49088, 39)
  "RayQueryGetIntersectionFrontFaceKHR\0" // IR(49127, 36)
  "RayQueryGetIntersectionCandidateAABBOpaqueKHR\0" // IR(49163, 46)
  "RayQueryGetIntersectionObjectRayDirectionKHR\0" // IR(49209, 45)
  "RayQueryGetIntersectionObjectRayOriginKHR\0" // IR(49254, 42)
  "RayQueryGetWorldRayDirectionKHR\0" // IR(49296, 32)
  "RayQueryGetWorldRayOriginKHR\0" // IR(49328, 29)
  "RayQueryGetIntersectionObjectToWorldKHR\0" // IR(49357, 40)
  "RayQueryGetIntersectionWorldToObjectKHR\0" // IR(49397, 40)
  "AtomicFAddEXT\0" // IR(49437, 14)
  "TypeBufferSurfaceINTEL\0" // IR(49451, 23)
  "TypeStructContinuedINTEL\0" // IR(49474, 25)
  "ConstantCompositeContinuedINTEL\0" // IR(49499, 32)
  "SpecConstantCompositeContinuedINTEL\0" // IR(49531, 36)
  "CompositeConstructContinuedINTEL\0" // IR(49567, 33)
  "ConvertFToBF16INTEL\0" // IR(49600, 20)
  "ConvertBF16ToFINTEL\0" // IR(49620, 20)
  "ControlBarrierArriveINTEL\0" // IR(49640, 26)
  "ControlBarrierWaitINTEL\0" // IR(49666, 24)
  "TaskSequenceCreateALTERA\0" // IR(49690, 25)
  "TaskSequenceCreateINTEL\0" // IR(49715, 24)
  "TaskSequenceAsyncALTERA\0" // IR(49739, 24)
  "TaskSequenceAsyncINTEL\0" // IR(49763, 23)
  "TaskSequenceGetALTERA\0" // IR(49786, 22)
  "TaskSequenceGetINTEL\0" // IR(49808, 21)
  "TaskSequenceReleaseALTERA\0" // IR(49829, 26)
  "TaskSequenceReleaseINTEL\0" // IR(49855, 25)
  "TypeTaskSequenceALTERA\0" // IR(49880, 23)
  "TypeTaskSequenceINTEL\0" // IR(49903, 22)
  "SubgroupBlockPrefetchINTEL\0" // IR(49925, 27)
  "Subgroup2DBlockLoadINTEL\0" // IR(49952, 25)
  "Subgroup2DBlockLoadTransformINTEL\0" // IR(49977, 34)
  "Subgroup2DBlockLoadTransposeINTEL\0" // IR(50011, 34)
  "Subgroup2DBlockPrefetchINTEL\0" // IR(50045, 29)
  "Subgroup2DBlockStoreINTEL\0" // IR(50074, 26)
  "SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS\0" // IR(50100, 62)
  "BitwiseFunctionINTEL\0" // IR(50162, 21)
  "ConditionalExtensionINTEL\0" // IR(50183, 26)
  "ConditionalEntryPointINTEL\0" // IR(50209, 27)
  "ConditionalCapabilityINTEL\0" // IR(50236, 27)
  "SpecConstantTargetINTEL\0" // IR(50263, 24)
  "SpecConstantArchitectureINTEL\0" // IR(50287, 30)
  "SPV_OPERAND_TYPE_VARIABLE_CAPABILITY\0" // IR(50317, 37)
  "SpecConstantCapabilitiesINTEL\0" // IR(50354, 30)
  "ConditionalCopyObjectINTEL\0" // IR(50384, 27)
  "GroupIMulKHR\0" // IR(50411, 13)
  "GroupFMulKHR\0" // IR(50424, 13)
  "GroupBitwiseAndKHR\0" // IR(50437, 19)
  "GroupBitwiseOrKHR\0" // IR(50456, 18)
  "GroupBitwiseXorKHR\0" // IR(50474, 19)
  "GroupLogicalAndKHR\0" // IR(50493, 19)
  "GroupLogicalOrKHR\0" // IR(50512, 18)
  "GroupLogicalXorKHR\0" // IR(50530, 19)
  "RoundFToTF32INTEL\0" // IR(50549, 18)
  "MaskedGatherINTEL\0" // IR(50567, 18)
  "MaskedScatterINTEL\0" // IR(50585, 19)
  "ConvertHandleToImageINTEL\0" // IR(50604, 26)
  "ConvertHandleToSamplerINTEL\0" // IR(50630, 28)
  "ConvertHandleToSampledImageINTEL\0" // IR(50658, 33)
  "FDot2MixAcc32VALVE\0" // IR(50691, 19)
  "FDot2MixAcc16VALVE\0" // IR(50710, 19)
  "FDot4MixAcc32VALVE\0" // IR(50729, 19)
  "DebugInfoNone\0" // IR(50748, 14)
  "DebugCompilationUnit\0" // IR(50762, 21)
  "SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING\0" // IR(50783, 52)
  "DebugTypeBasic\0" // IR(50835, 15)
  "SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS\0" // IR(50850, 34)
  "DebugTypePointer\0" // IR(50884, 17)
  "SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER\0" // IR(50901, 38)
  "DebugTypeQualifier\0" // IR(50939, 19)
  "DebugTypeArray\0" // IR(50958, 15)
  "DebugTypeVector\0" // IR(50973, 16)
  "DebugTypedef\0" // IR(50989, 13)
  "DebugTypeFunction\0" // IR(51002, 18)
  "DebugTypeEnum\0" // IR(51020, 14)
  "SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE\0" // IR(51034, 38)
  "DebugTypeComposite\0" // IR(51072, 19)
  "DebugTypeMember\0" // IR(51091, 16)
  "DebugTypeInheritance\0" // IR(51107, 21)
  "DebugTypePtrToMember\0" // IR(51128, 21)
  "DebugTypeTemplate\0" // IR(51149, 18)
  "DebugTypeTemplateParameter\0" // IR(51167, 27)
  "DebugTypeTemplateTemplateParameter\0" // IR(51194, 35)
  "DebugTypeTemplateParameterPack\0" // IR(51229, 31)
  "DebugGlobalVariable\0" // IR(51260, 20)
  "DebugFunctionDeclaration\0" // IR(51280, 25)
  "DebugFunction\0" // IR(51305, 14)
  "DebugLexicalBlock\0" // IR(51319, 18)
  "DebugLexicalBlockDiscriminator\0" // IR(51337, 31)
  "DebugScope\0" // IR(51368, 11)
  "DebugNoScope\0" // IR(51379, 13)
  "DebugInlinedAt\0" // IR(51392, 15)
  "SPV_OPERAND_TYPE_OPTIONAL_LITERAL_INTEGER\0" // IR(51407, 42)
  "DebugLocalVariable\0" // IR(51449, 19)
  "DebugInlinedVariable\0" // IR(51468, 21)
  "DebugDeclare\0" // IR(51489, 13)
  "DebugValue\0" // IR(51502, 11)
  "SPV_OPERAND_TYPE_DEBUG_OPERATION\0" // IR(51513, 33)
  "DebugOperation\0" // IR(51546, 15)
  "DebugExpression\0" // IR(51561, 16)
  "DebugMacroDef\0" // IR(51577, 14)
  "DebugMacroUndef\0" // IR(51591, 16)
  "Round\0" // IR(51607, 6)
  "RoundEven\0" // IR(51613, 10)
  "Trunc\0" // IR(51623, 6)
  "FAbs\0" // IR(51629, 5)
  "SAbs\0" // IR(51634, 5)
  "FSign\0" // IR(51639, 6)
  "SSign\0" // IR(51645, 6)
  "Floor\0" // IR(51651, 6)
  "Ceil\0" // IR(51657, 5)
  "Fract\0" // IR(51662, 6)
  "Radians\0" // IR(51668, 8)
  "Degrees\0" // IR(51676, 8)
  "Sin\0" // IR(51684, 4)
  "Cos\0" // IR(51688, 4)
  "Tan\0" // IR(51692, 4)
  "Asin\0" // IR(51696, 5)
  "Acos\0" // IR(51701, 5)
  "Atan\0" // IR(51706, 5)
  "Sinh\0" // IR(51711, 5)
  "Cosh\0" // IR(51716, 5)
  "Tanh\0" // IR(51721, 5)
  "Asinh\0" // IR(51726, 6)
  "Acosh\0" // IR(51732, 6)
  "Atanh\0" // IR(51738, 6)
  "Atan2\0" // IR(51744, 6)
  "Pow\0" // IR(51750, 4)
  "Exp\0" // IR(51754, 4)
  "Log\0" // IR(51758, 4)
  "Exp2\0" // IR(51762, 5)
  "Log2\0" // IR(51767, 5)
  "Sqrt\0" // IR(51772, 5)
  "InverseSqrt\0" // IR(51777, 12)
  "Determinant\0" // IR(51789, 12)
  "MatrixInverse\0" // IR(51801, 14)
  "Modf\0" // IR(51815, 5)
  "ModfStruct\0" // IR(51820, 11)
  "FMin\0" // IR(51831, 5)
  "UMin\0" // IR(51836, 5)
  "SMin\0" // IR(51841, 5)
  "FMax\0" // IR(51846, 5)
  "UMax\0" // IR(51851, 5)
  "SMax\0" // IR(51856, 5)
  "FClamp\0" // IR(51861, 7)
  "UClamp\0" // IR(51868, 7)
  "SClamp\0" // IR(51875, 7)
  "FMix\0" // IR(51882, 5)
  "IMix\0" // IR(51887, 5)
  "Step\0" // IR(51892, 5)
  "SmoothStep\0" // IR(51897, 11)
  "Fma\0" // IR(51908, 4)
  "Frexp\0" // IR(51912, 6)
  "FrexpStruct\0" // IR(51918, 12)
  "Ldexp\0" // IR(51930, 6)
  "PackSnorm4x8\0" // IR(51936, 13)
  "PackUnorm4x8\0" // IR(51949, 13)
  "PackSnorm2x16\0" // IR(51962, 14)
  "PackUnorm2x16\0" // IR(51976, 14)
  "PackHalf2x16\0" // IR(51990, 13)
  "PackDouble2x32\0" // IR(52003, 15)
  "UnpackSnorm2x16\0" // IR(52018, 16)
  "UnpackUnorm2x16\0" // IR(52034, 16)
  "UnpackHalf2x16\0" // IR(52050, 15)
  "UnpackSnorm4x8\0" // IR(52065, 15)
  "UnpackUnorm4x8\0" // IR(52080, 15)
  "UnpackDouble2x32\0" // IR(52095, 17)
  "Length\0" // IR(52112, 7)
  "Distance\0" // IR(52119, 9)
  "Cross\0" // IR(52128, 6)
  "Normalize\0" // IR(52134, 10)
  "FaceForward\0" // IR(52144, 12)
  "Reflect\0" // IR(52156, 8)
  "Refract\0" // IR(52164, 8)
  "FindILsb\0" // IR(52172, 9)
  "FindSMsb\0" // IR(52181, 9)
  "FindUMsb\0" // IR(52190, 9)
  "InterpolateAtCentroid\0" // IR(52199, 22)
  "InterpolateAtSample\0" // IR(52221, 20)
  "InterpolateAtOffset\0" // IR(52241, 20)
  "NMin\0" // IR(52261, 5)
  "NMax\0" // IR(52266, 5)
  "NClamp\0" // IR(52271, 7)
  "ArgumentInfo\0" // IR(52278, 13)
  "ArgumentStorageBuffer\0" // IR(52291, 22)
  "ArgumentUniform\0" // IR(52313, 16)
  "ArgumentPodStorageBuffer\0" // IR(52329, 25)
  "ArgumentPodUniform\0" // IR(52354, 19)
  "ArgumentPodPushConstant\0" // IR(52373, 24)
  "ArgumentSampledImage\0" // IR(52397, 21)
  "ArgumentStorageImage\0" // IR(52418, 21)
  "ArgumentSampler\0" // IR(52439, 16)
  "ArgumentWorkgroup\0" // IR(52455, 18)
  "SpecConstantWorkgroupSize\0" // IR(52473, 26)
  "SpecConstantGlobalOffset\0" // IR(52499, 25)
  "SpecConstantWorkDim\0" // IR(52524, 20)
  "PushConstantGlobalOffset\0" // IR(52544, 25)
  "PushConstantEnqueuedLocalSize\0" // IR(52569, 30)
  "PushConstantGlobalSize\0" // IR(52599, 23)
  "PushConstantRegionOffset\0" // IR(52622, 25)
  "PushConstantNumWorkgroups\0" // IR(52647, 26)
  "PushConstantRegionGroupOffset\0" // IR(52673, 30)
  "ConstantDataStorageBuffer\0" // IR(52703, 26)
  "ConstantDataUniform\0" // IR(52729, 20)
  "PropertyRequiredWorkgroupSize\0" // IR(52749, 30)
  "SpecConstantSubgroupMaxSize\0" // IR(52779, 28)
  "ArgumentPointerPushConstant\0" // IR(52807, 28)
  "ArgumentPointerUniform\0" // IR(52835, 23)
  "ProgramScopeVariablesStorageBuffer\0" // IR(52858, 35)
  "ProgramScopeVariablePointerRelocation\0" // IR(52893, 38)
  "ImageArgumentInfoChannelOrderPushConstant\0" // IR(52931, 42)
  "ImageArgumentInfoChannelDataTypePushConstant\0" // IR(52973, 45)
  "ImageArgumentInfoChannelOrderUniform\0" // IR(53018, 37)
  "ImageArgumentInfoChannelDataTypeUniform\0" // IR(53055, 40)
  "ArgumentStorageTexelBuffer\0" // IR(53095, 27)
  "ArgumentUniformTexelBuffer\0" // IR(53122, 27)
  "ConstantDataPointerPushConstant\0" // IR(53149, 32)
  "ProgramScopeVariablePointerPushConstant\0" // IR(53181, 40)
  "PrintfInfo\0" // IR(53221, 11)
  "PrintfBufferStorageBuffer\0" // IR(53232, 26)
  "PrintfBufferPointerPushConstant\0" // IR(53258, 32)
  "NormalizedSamplerMaskPushConstant\0" // IR(53290, 34)
  "WorkgroupVariableSize\0" // IR(53324, 22)
  "DebugImportedEntity\0" // IR(53346, 20)
  "DebugSource\0" // IR(53366, 12)
  "DebugFunctionDefinition\0" // IR(53378, 24)
  "DebugSourceContinued\0" // IR(53402, 21)
  "DebugLine\0" // IR(53423, 10)
  "DebugNoLine\0" // IR(53433, 12)
  "DebugBuildIdentifier\0" // IR(53445, 21)
  "DebugStoragePath\0" // IR(53466, 17)
  "DebugEntryPoint\0" // IR(53483, 16)
  "DebugTypeMatrix\0" // IR(53499, 16)
  "Configuration\0" // IR(53515, 14)
  "StartCounter\0" // IR(53529, 13)
  "StopCounter\0" // IR(53542, 12)
  "PushConstants\0" // IR(53554, 14)
  "SpecializationMapEntry\0" // IR(53568, 23)
  "DescriptorSetBuffer\0" // IR(53591, 20)
  "DescriptorSetImage\0" // IR(53611, 19)
  "DescriptorSetSampler\0" // IR(53630, 21)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING\0" // IR(53651, 63)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS\0" // IR(53714, 45)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER\0" // IR(53759, 49)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE\0" // IR(53808, 49)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION\0" // IR(53857, 44)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY\0" // IR(53901, 50)
  "DebugModuleINTEL\0" // IR(53951, 17)
  "acos\0" // IR(53968, 5)
  "acosh\0" // IR(53973, 6)
  "acospi\0" // IR(53979, 7)
  "asin\0" // IR(53986, 5)
  "asinh\0" // IR(53991, 6)
  "asinpi\0" // IR(53997, 7)
  "atan\0" // IR(54004, 5)
  "atan2\0" // IR(54009, 6)
  "atanh\0" // IR(54015, 6)
  "atanpi\0" // IR(54021, 7)
  "atan2pi\0" // IR(54028, 8)
  "cbrt\0" // IR(54036, 5)
  "ceil\0" // IR(54041, 5)
  "copysign\0" // IR(54046, 9)
  "cos\0" // IR(54055, 4)
  "cosh\0" // IR(54059, 5)
  "cospi\0" // IR(54064, 6)
  "erfc\0" // IR(54070, 5)
  "erf\0" // IR(54075, 4)
  "exp\0" // IR(54079, 4)
  "exp2\0" // IR(54083, 5)
  "exp10\0" // IR(54088, 6)
  "expm1\0" // IR(54094, 6)
  "fabs\0" // IR(54100, 5)
  "fdim\0" // IR(54105, 5)
  "floor\0" // IR(54110, 6)
  "fma\0" // IR(54116, 4)
  "fmax\0" // IR(54120, 5)
  "fmin\0" // IR(54125, 5)
  "fmod\0" // IR(54130, 5)
  "fract\0" // IR(54135, 6)
  "frexp\0" // IR(54141, 6)
  "hypot\0" // IR(54147, 6)
  "ilogb\0" // IR(54153, 6)
  "ldexp\0" // IR(54159, 6)
  "lgamma\0" // IR(54165, 7)
  "lgamma_r\0" // IR(54172, 9)
  "log\0" // IR(54181, 4)
  "log2\0" // IR(54185, 5)
  "log10\0" // IR(54190, 6)
  "log1p\0" // IR(54196, 6)
  "logb\0" // IR(54202, 5)
  "mad\0" // IR(54207, 4)
  "maxmag\0" // IR(54211, 7)
  "minmag\0" // IR(54218, 7)
  "modf\0" // IR(54225, 5)
  "nan\0" // IR(54230, 4)
  "nextafter\0" // IR(54234, 10)
  "pow\0" // IR(54244, 4)
  "pown\0" // IR(54248, 5)
  "powr\0" // IR(54253, 5)
  "remainder\0" // IR(54258, 10)
  "remquo\0" // IR(54268, 7)
  "rint\0" // IR(54275, 5)
  "rootn\0" // IR(54280, 6)
  "round\0" // IR(54286, 6)
  "rsqrt\0" // IR(54292, 6)
  "sin\0" // IR(54298, 4)
  "sincos\0" // IR(54302, 7)
  "sinh\0" // IR(54309, 5)
  "sinpi\0" // IR(54314, 6)
  "sqrt\0" // IR(54320, 5)
  "tan\0" // IR(54325, 4)
  "tanh\0" // IR(54329, 5)
  "tanpi\0" // IR(54334, 6)
  "tgamma\0" // IR(54340, 7)
  "trunc\0" // IR(54347, 6)
  "half_cos\0" // IR(54353, 9)
  "half_divide\0" // IR(54362, 12)
  "half_exp\0" // IR(54374, 9)
  "half_exp2\0" // IR(54383, 10)
  "half_exp10\0" // IR(54393, 11)
  "half_log\0" // IR(54404, 9)
  "half_log2\0" // IR(54413, 10)
  "half_log10\0" // IR(54423, 11)
  "half_powr\0" // IR(54434, 10)
  "half_recip\0" // IR(54444, 11)
  "half_rsqrt\0" // IR(54455, 11)
  "half_sin\0" // IR(54466, 9)
  "half_sqrt\0" // IR(54475, 10)
  "half_tan\0" // IR(54485, 9)
  "native_cos\0" // IR(54494, 11)
  "native_divide\0" // IR(54505, 14)
  "native_exp\0" // IR(54519, 11)
  "native_exp2\0" // IR(54530, 12)
  "native_exp10\0" // IR(54542, 13)
  "native_log\0" // IR(54555, 11)
  "native_log2\0" // IR(54566, 12)
  "native_log10\0" // IR(54578, 13)
  "native_powr\0" // IR(54591, 12)
  "native_recip\0" // IR(54603, 13)
  "native_rsqrt\0" // IR(54616, 13)
  "native_sin\0" // IR(54629, 11)
  "native_sqrt\0" // IR(54640, 12)
  "native_tan\0" // IR(54652, 11)
  "fclamp\0" // IR(54663, 7)
  "degrees\0" // IR(54670, 8)
  "fmax_common\0" // IR(54678, 12)
  "fmin_common\0" // IR(54690, 12)
  "mix\0" // IR(54702, 4)
  "radians\0" // IR(54706, 8)
  "step\0" // IR(54714, 5)
  "smoothstep\0" // IR(54719, 11)
  "sign\0" // IR(54730, 5)
  "cross\0" // IR(54735, 6)
  "distance\0" // IR(54741, 9)
  "length\0" // IR(54750, 7)
  "normalize\0" // IR(54757, 10)
  "fast_distance\0" // IR(54767, 14)
  "fast_length\0" // IR(54781, 12)
  "fast_normalize\0" // IR(54793, 15)
  "s_abs\0" // IR(54808, 6)
  "s_abs_diff\0" // IR(54814, 11)
  "s_add_sat\0" // IR(54825, 10)
  "u_add_sat\0" // IR(54835, 10)
  "s_hadd\0" // IR(54845, 7)
  "u_hadd\0" // IR(54852, 7)
  "s_rhadd\0" // IR(54859, 8)
  "u_rhadd\0" // IR(54867, 8)
  "s_clamp\0" // IR(54875, 8)
  "u_clamp\0" // IR(54883, 8)
  "clz\0" // IR(54891, 4)
  "ctz\0" // IR(54895, 4)
  "s_mad_hi\0" // IR(54899, 9)
  "u_mad_sat\0" // IR(54908, 10)
  "s_mad_sat\0" // IR(54918, 10)
  "s_max\0" // IR(54928, 6)
  "u_max\0" // IR(54934, 6)
  "s_min\0" // IR(54940, 6)
  "u_min\0" // IR(54946, 6)
  "s_mul_hi\0" // IR(54952, 9)
  "rotate\0" // IR(54961, 7)
  "s_sub_sat\0" // IR(54968, 10)
  "u_sub_sat\0" // IR(54978, 10)
  "u_upsample\0" // IR(54988, 11)
  "s_upsample\0" // IR(54999, 11)
  "popcount\0" // IR(55010, 9)
  "s_mad24\0" // IR(55019, 8)
  "u_mad24\0" // IR(55027, 8)
  "s_mul24\0" // IR(55035, 8)
  "u_mul24\0" // IR(55043, 8)
  "vloadn\0" // IR(55051, 7)
  "vstoren\0" // IR(55058, 8)
  "vload_half\0" // IR(55066, 11)
  "vload_halfn\0" // IR(55077, 12)
  "vstore_half\0" // IR(55089, 12)
  "vstore_half_r\0" // IR(55101, 14)
  "vstore_halfn\0" // IR(55115, 13)
  "vstore_halfn_r\0" // IR(55128, 15)
  "vloada_halfn\0" // IR(55143, 13)
  "vstorea_halfn\0" // IR(55156, 14)
  "vstorea_halfn_r\0" // IR(55170, 16)
  "shuffle\0" // IR(55186, 8)
  "shuffle2\0" // IR(55194, 9)
  "printf\0" // IR(55203, 7)
  "prefetch\0" // IR(55210, 9)
  "bitselect\0" // IR(55219, 10)
  "select\0" // IR(55229, 7)
  "u_abs\0" // IR(55236, 6)
  "u_abs_diff\0" // IR(55242, 11)
  "u_mul_hi\0" // IR(55253, 9)
  "u_mad_hi\0" // IR(55262, 9)
  "CubeFaceIndexAMD\0" // IR(55271, 17)
  "CubeFaceCoordAMD\0" // IR(55288, 17)
  "TimeAMD\0" // IR(55305, 8)
  "SwizzleInvocationsAMD\0" // IR(55313, 22)
  "SwizzleInvocationsMaskedAMD\0" // IR(55335, 28)
  "WriteInvocationAMD\0" // IR(55363, 19)
  "MbcntAMD\0" // IR(55382, 9)
  "InterpolateAtVertexAMD\0" // IR(55391, 23)
  "FMin3AMD\0" // IR(55414, 9)
  "UMin3AMD\0" // IR(55423, 9)
  "SMin3AMD\0" // IR(55432, 9)
  "FMax3AMD\0" // IR(55441, 9)
  "UMax3AMD\0" // IR(55450, 9)
  "SMax3AMD\0" // IR(55459, 9)
  "FMid3AMD\0" // IR(55468, 9)
  "UMid3AMD\0" // IR(55477, 9)
  "SMid3AMD\0" // IR(55486, 9)
;

// Array of IndexRanges, where each represents a string by referencing
// the kStrings table.
// This array contains all sequences of alias strings used in the grammar.
// This table is referenced by an IndexRange elsewhere, i.e. by the 'aliases'
// field of an instruction or operand description.
static const IndexRange kAliasSpans[] = {
  IR(5588, 27), // 0 PhysicalStorageBuffer64EXT
  IR(6499, 18), // 1 SubgroupEqMaskKHR
  IR(6554, 18), // 2 SubgroupGeMaskKHR
  IR(6587, 18), // 3 SubgroupGtMaskKHR
  IR(6620, 18), // 4 SubgroupLeMaskKHR
  IR(6653, 18), // 5 SubgroupLtMaskKHR
  IR(7560, 12), // 6 BaryCoordNV
  IR(7615, 19), // 7 BaryCoordNoPerspNV
  IR(7646, 15), // 8 FragmentSizeNV
  IR(7703, 22), // 9 InvocationsPerPixelNV
  IR(7831, 11), // 10 LaunchIdNV
  IR(7856, 13), // 11 LaunchSizeNV
  IR(7887, 17), // 12 WorldRayOriginNV
  IR(7925, 20), // 13 WorldRayDirectionNV
  IR(7964, 18), // 14 ObjectRayOriginNV
  IR(8004, 21), // 15 ObjectRayDirectionNV
  IR(8036, 10), // 16 RayTminNV
  IR(8057, 10), // 17 RayTmaxNV
  IR(8090, 22), // 18 InstanceCustomIndexNV
  IR(8129, 16), // 19 ObjectToWorldNV
  IR(8162, 16), // 20 WorldToObjectNV
  IR(8196, 10), // 21 HitKindNV
  IR(8427, 19), // 22 IncomingRayFlagsNV
  IR(10203, 28), // 23 StorageUniformBufferBlock16
  IR(10266, 17), // 24 StorageUniform16
  IR(11081, 27), // 25 ShaderViewportIndexLayerNV
  IR(11125, 22), // 26 FragmentBarycentricNV
  IR(11178, 30), // 27 ComputeDerivativeGroupQuadsNV
  IR(11208, 14), // 28 ShadingRateNV
  IR(11252, 29), // 29 GroupNonUniformPartitionedNV
  IR(11298, 20), // 30 ShaderNonUniformEXT
  IR(11341, 26), // 31 RuntimeDescriptorArrayEXT
  IR(11403, 39), // 32 InputAttachmentArrayDynamicIndexingEXT
  IR(11481, 42), // 33 UniformTexelBufferArrayDynamicIndexingEXT
  IR(11562, 42), // 34 StorageTexelBufferArrayDynamicIndexingEXT
  IR(11641, 40), // 35 UniformBufferArrayNonUniformIndexingEXT
  IR(11717, 39), // 36 SampledImageArrayNonUniformIndexingEXT
  IR(11793, 40), // 37 StorageBufferArrayNonUniformIndexingEXT
  IR(11869, 39), // 38 StorageImageArrayNonUniformIndexingEXT
  IR(11947, 42), // 39 InputAttachmentArrayNonUniformIndexingEXT
  IR(12031, 45), // 40 UniformTexelBufferArrayNonUniformIndexingEXT
  IR(12118, 45), // 41 StorageTexelBufferArrayNonUniformIndexingEXT
  IR(12181, 21), // 42 VulkanMemoryModelKHR
  IR(12231, 32), // 43 VulkanMemoryModelDeviceScopeKHR
  IR(12263, 34), // 44 PhysicalStorageBufferAddressesEXT
  IR(12329, 31), // 45 ComputeDerivativeGroupLinearNV
  IR(12533, 28), // 46 DemoteToHelperInvocationEXT
  IR(13574, 26), // 47 FPGAMemoryAttributesINTEL
  IR(13653, 32), // 48 ArbitraryPrecisionIntegersINTEL
  IR(13723, 37), // 49 ArbitraryPrecisionFloatingPointINTEL
  IR(13813, 22), // 50 FPGALoopControlsINTEL
  IR(13908, 24), // 51 FPGAMemoryAccessesINTEL
  IR(13960, 27), // 52 FPGAClusterAttributesINTEL
  IR(14002, 14), // 53 LoopFuseINTEL
  IR(14037, 20), // 54 FPGADSPControlINTEL
  IR(14124, 40), // 55 FPGAInvocationPipeliningAttributesINTEL
  IR(14189, 24), // 56 FPGABufferLocationINTEL
  IR(14248, 34), // 57 ArbitraryPrecisionFixedPointINTEL
  IR(14306, 23), // 58 USMStorageClassesINTEL
  IR(14359, 29), // 59 RuntimeAlignedAttributeINTEL
  IR(14402, 13), // 60 IOPipesINTEL
  IR(14435, 19), // 61 BlockingPipesINTEL
  IR(14468, 13), // 62 FPGARegINTEL
  IR(14500, 22), // 63 DotProductInputAllKHR
  IR(14544, 25), // 64 DotProductInput4x8BitKHR
  IR(14597, 31), // 65 DotProductInput4x8BitPackedKHR
  IR(14639, 14), // 66 DotProductKHR
  IR(14811, 13), // 67 OptNoneINTEL
  IR(14956, 29), // 68 FPGAClusterAttributesV2INTEL
  IR(15032, 18), // 69 TaskSequenceINTEL
  IR(15091, 24), // 70 FPGALatencyControlINTEL
  IR(15144, 28), // 71 FPGAArgumentInterfacesINTEL
  IR(15238, 35), // 72 GlobalVariableFPGADecorationsINTEL
  IR(18175, 15), // 73 PerPrimitiveNV
  IR(18223, 12), // 74 PerVertexNV
  IR(18246, 14), // 75 NonUniformEXT
  IR(18276, 19), // 76 RestrictPointerEXT
  IR(18310, 18), // 77 AliasedPointerEXT
  IR(18673, 24), // 78 HlslCounterBufferGOOGLE
  IR(18710, 19), // 79 HlslSemanticGOOGLE
  IR(18840, 14), // 80 RegisterINTEL
  IR(18867, 12), // 81 MemoryINTEL
  IR(18894, 14), // 82 NumbanksINTEL
  IR(18924, 15), // 83 BankwidthINTEL
  IR(18962, 22), // 84 MaxPrivateCopiesINTEL
  IR(19001, 16), // 85 SinglepumpINTEL
  IR(19034, 16), // 86 DoublepumpINTEL
  IR(19070, 19), // 87 MaxReplicatesINTEL
  IR(19110, 20), // 88 SimpleDualPortINTEL
  IR(19142, 11), // 89 MergeINTEL
  IR(19210, 14), // 90 BankBitsINTEL
  IR(19245, 20), // 91 ForcePow2DepthINTEL
  IR(19282, 16), // 92 StridesizeINTEL
  IR(19313, 14), // 93 WordsizeINTEL
  IR(19346, 18), // 94 TrueDualPortINTEL
  IR(19384, 19), // 95 BurstCoalesceINTEL
  IR(19419, 15), // 96 CacheSizeINTEL
  IR(19463, 28), // 97 DontStaticallyCoalesceINTEL
  IR(19506, 14), // 98 PrefetchINTEL
  IR(19538, 17), // 99 StallEnableINTEL
  IR(19581, 25), // 100 FuseLoopsInFunctionINTEL
  IR(19626, 19), // 101 MathOpDSPModeINTEL
  IR(19699, 24), // 102 InitiationIntervalINTEL
  IR(19744, 20), // 103 MaxConcurrencyINTEL
  IR(19785, 20), // 104 PipelineEnableINTEL
  IR(19826, 20), // 105 BufferLocationINTEL
  IR(19866, 19), // 106 IOPipeStorageINTEL
  IR(20044, 15), // 107 StallFreeINTEL
  IR(20142, 25), // 108 LatencyControlLabelINTEL
  IR(20198, 30), // 109 LatencyControlConstraintINTEL
  IR(20256, 27), // 110 ConduitKernelArgumentINTEL
  IR(20315, 31), // 111 RegisterMapKernelArgumentINTEL
  IR(20380, 33), // 112 MMHostInterfaceAddressWidthINTEL
  IR(20444, 30), // 113 MMHostInterfaceDataWidthINTEL
  IR(20503, 28), // 114 MMHostInterfaceLatencyINTEL
  IR(20600, 34), // 115 MMHostInterfaceReadWriteModeINTEL
  IR(20664, 29), // 116 MMHostInterfaceMaxBurstINTEL
  IR(20726, 32), // 117 MMHostInterfaceWaitRequestINTEL
  IR(20785, 26), // 118 StableKernelArgumentINTEL
  IR(20928, 14), // 119 InitModeINTEL
  IR(20971, 28), // 120 ImplementInRegisterMapINTEL
  IR(22305, 14), // 121 OutputLinesNV
  IR(22339, 19), // 122 OutputPrimitivesNV
  IR(22382, 23), // 123 DerivativeGroupQuadsNV
  IR(22430, 24), // 124 DerivativeGroupLinearNV
  IR(22473, 18), // 125 OutputTrianglesNV
  IR(23221, 16), // 126 RayGenerationNV
  IR(23253, 15), // 127 IntersectionNV
  IR(23278, 9), // 128 AnyHitNV
  IR(23301, 13), // 129 ClosestHitNV
  IR(23322, 7), // 130 MissNV
  IR(23341, 11), // 131 CallableNV
  IR(23486, 23), // 132 AllowContractFastINTEL
  IR(23522, 18), // 133 AllowReassocINTEL
  IR(23748, 20), // 134 RuntimeAlignedINTEL
  IR(23840, 20), // 135 PartitionedReduceNV
  IR(23888, 27), // 136 PartitionedInclusiveScanNV
  IR(23943, 27), // 137 PartitionedExclusiveScanNV
  IR(24074, 22), // 138 MakeTexelAvailableKHR
  IR(24113, 20), // 139 MakeTexelVisibleKHR
  IR(24149, 19), // 140 NonPrivateTexelKHR
  IR(24182, 17), // 141 VolatileTexelKHR
  IR(24741, 27), // 142 InitOnDeviceReprogramINTEL
  IR(24792, 23), // 143 InitOnDeviceResetINTEL
  IR(25126, 21), // 144 DependencyArrayINTEL
  IR(25166, 18), // 145 LoopCoalesceINTEL
  IR(25206, 21), // 146 MaxInterleavingINTEL
  IR(25254, 26), // 147 SpeculatedIterationsINTEL
  IR(25295, 14), // 148 NoFusionINTEL
  IR(25325, 15), // 149 LoopCountINTEL
  IR(25367, 26), // 150 MaxReinvocationDelayINTEL
  IR(25759, 24), // 151 MakePointerAvailableKHR
  IR(25802, 22), // 152 MakePointerVisibleKHR
  IR(25842, 21), // 153 NonPrivatePointerKHR
  IR(25929, 10), // 154 VulkanKHR
  IR(15918, 5), // 155 None
  IR(26112, 16), // 156 OutputMemoryKHR
  IR(26142, 17), // 157 MakeAvailableKHR
  IR(26171, 15), // 158 MakeVisibleKHR
  IR(26247, 28), // 159 PackedVectorFormat4x8BitKHR
  IR(26562, 24), // 160 SkipBuiltinPrimitivesNV
  IR(27302, 15), // 161 QueueFamilyKHR
  IR(27673, 15), // 162 CallableDataNV
  IR(27712, 23), // 163 IncomingCallableDataNV
  IR(27749, 13), // 164 RayPayloadNV
  IR(27778, 15), // 165 HitAttributeNV
  IR(27815, 21), // 166 IncomingRayPayloadNV
  IR(27858, 21), // 167 ShaderRecordBufferNV
  IR(27901, 25), // 168 PhysicalStorageBufferEXT
  IR(28027, 16), // 169 DeviceOnlyINTEL
  IR(28058, 14), // 170 HostOnlyINTEL
  IR(35296, 8), // 171 SDotKHR
  IR(35309, 8), // 172 UDotKHR
  IR(35323, 9), // 173 SUDotKHR
  IR(35343, 14), // 174 SDotAccSatKHR
  IR(35368, 14), // 175 UDotAccSatKHR
  IR(35394, 15), // 176 SUDotAccSatKHR
  IR(37655, 24), // 177 TypeCooperativeVectorNV
  IR(37911, 27), // 178 GroupNonUniformPartitionNV
  IR(38993, 21), // 179 ReportIntersectionNV
  IR(39168, 28), // 180 TypeAccelerationStructureNV
  IR(39249, 23), // 181 RayQueryGetClusterIdNV
  IR(41417, 21), // 182 DecorateStringGOOGLE
  IR(41459, 27), // 183 MemberDecorateStringGOOGLE
  IR(46716, 28), // 184 ArbitraryFloatSinCosPiINTEL
  IR(46769, 24), // 185 ArbitraryFloatCastINTEL
  IR(46825, 31), // 186 ArbitraryFloatCastFromIntINTEL
  IR(46886, 29), // 187 ArbitraryFloatCastToIntINTEL
  IR(46939, 23), // 188 ArbitraryFloatAddINTEL
  IR(46986, 23), // 189 ArbitraryFloatSubINTEL
  IR(47033, 23), // 190 ArbitraryFloatMulINTEL
  IR(47080, 23), // 191 ArbitraryFloatDivINTEL
  IR(47126, 22), // 192 ArbitraryFloatGTINTEL
  IR(47171, 22), // 193 ArbitraryFloatGEINTEL
  IR(47216, 22), // 194 ArbitraryFloatLTINTEL
  IR(47261, 22), // 195 ArbitraryFloatLEINTEL
  IR(47306, 22), // 196 ArbitraryFloatEQINTEL
  IR(47354, 25), // 197 ArbitraryFloatRecipINTEL
  IR(47405, 25), // 198 ArbitraryFloatRSqrtINTEL
  IR(47455, 24), // 199 ArbitraryFloatCbrtINTEL
  IR(47505, 25), // 200 ArbitraryFloatHypotINTEL
  IR(47555, 24), // 201 ArbitraryFloatSqrtINTEL
  IR(48239, 15), // 202 FixedSqrtINTEL
  IR(48271, 16), // 203 FixedRecipINTEL
  IR(48304, 16), // 204 FixedRsqrtINTEL
  IR(48335, 14), // 205 FixedSinINTEL
  IR(48364, 14), // 206 FixedCosINTEL
  IR(48396, 17), // 207 FixedSinCosINTEL
  IR(48430, 16), // 208 FixedSinPiINTEL
  IR(48463, 16), // 209 FixedCosPiINTEL
  IR(48499, 19), // 210 FixedSinCosPiINTEL
  IR(48533, 14), // 211 FixedLogINTEL
  IR(48562, 14), // 212 FixedExpINTEL
  IR(48606, 29), // 213 PtrCastToCrossWorkgroupINTEL
  IR(48665, 29), // 214 CrossWorkgroupCastToPtrINTEL
  IR(48717, 22), // 215 ReadPipeBlockingINTEL
  IR(48763, 23), // 216 WritePipeBlockingINTEL
  IR(49715, 24), // 217 TaskSequenceCreateINTEL
  IR(49763, 23), // 218 TaskSequenceAsyncINTEL
  IR(49808, 21), // 219 TaskSequenceGetINTEL
  IR(49855, 25), // 220 TaskSequenceReleaseINTEL
  IR(49903, 22), // 221 TypeTaskSequenceINTEL
};

// Array of capabilities, referenced by IndexRanges elsewhere.
// Contains all sequences of capabilities used in the grammar.
static const spv::Capability kCapabilitySpans[] = {
  spv::Capability::Kernel, // 0
  spv::Capability::Addresses, // 1
  spv::Capability::PhysicalStorageBufferAddresses, // 2
  spv::Capability::Shader, // 3
  spv::Capability::ClipDistance, // 4
  spv::Capability::CullDistance, // 5
  spv::Capability::Geometry, // 6
  spv::Capability::Tessellation, // 7
  spv::Capability::RayTracingNV, // 8
  spv::Capability::RayTracingKHR, // 9
  spv::Capability::MeshShadingNV, // 10
  spv::Capability::MeshShadingEXT, // 11
  spv::Capability::Geometry, // 12
  spv::Capability::Tessellation, // 13
  spv::Capability::Geometry, // 14
  spv::Capability::ShaderLayer, // 15
  spv::Capability::ShaderViewportIndexLayerEXT, // 16
  spv::Capability::MeshShadingNV, // 17
  spv::Capability::MeshShadingEXT, // 18
  spv::Capability::MultiViewport, // 19
  spv::Capability::ShaderViewportIndex, // 20
  spv::Capability::ShaderViewportIndexLayerEXT, // 21
  spv::Capability::MeshShadingNV, // 22
  spv::Capability::MeshShadingEXT, // 23
  spv::Capability::Tessellation, // 24
  spv::Capability::SampleRateShading, // 25
  spv::Capability::Kernel, // 26
  spv::Capability::GroupNonUniform, // 27
  spv::Capability::SubgroupBallotKHR, // 28
  spv::Capability::Kernel, // 29
  spv::Capability::GroupNonUniform, // 30
  spv::Capability::CoreBuiltinsARM, // 31
  spv::Capability::SubgroupBallotKHR, // 32
  spv::Capability::GroupNonUniformBallot, // 33
  spv::Capability::DrawParameters, // 34
  spv::Capability::DrawParameters, // 35
  spv::Capability::MeshShadingNV, // 36
  spv::Capability::MeshShadingEXT, // 37
  spv::Capability::FragmentShadingRateKHR, // 38
  spv::Capability::DeviceGroup, // 39
  spv::Capability::MultiView, // 40
  spv::Capability::TileShadingQCOM, // 41
  spv::Capability::StencilExportEXT, // 42
  spv::Capability::ShaderEnqueueAMDX, // 43
  spv::Capability::DescriptorHeapEXT, // 44
  spv::Capability::ShaderViewportMaskNV, // 45
  spv::Capability::MeshShadingNV, // 46
  spv::Capability::ShaderStereoViewNV, // 47
  spv::Capability::PerViewAttributesNV, // 48
  spv::Capability::MeshShadingNV, // 49
  spv::Capability::FragmentFullyCoveredEXT, // 50
  spv::Capability::MeshShadingNV, // 51
  spv::Capability::FragmentBarycentricKHR, // 52
  spv::Capability::FragmentDensityEXT, // 53
  spv::Capability::MeshShadingEXT, // 54
  spv::Capability::RayTracingNV, // 55
  spv::Capability::RayTracingKHR, // 56
  spv::Capability::RayTracingNV, // 57
  spv::Capability::RayTracingMotionBlurNV, // 58
  spv::Capability::RayTracingPositionFetchKHR, // 59
  spv::Capability::RayTracingDisplacementMicromapNV, // 60
  spv::Capability::RayTracingKHR, // 61
  spv::Capability::RayTracingSpheresGeometryNV, // 62
  spv::Capability::RayTracingLinearSweptSpheresGeometryNV, // 63
  spv::Capability::ShaderSMBuiltinsNV, // 64
  spv::Capability::RayTracingClusterAccelerationStructureNV, // 65
  spv::Capability::RayCullMaskKHR, // 66
  spv::Capability::Matrix, // 67
  spv::Capability::Int64, // 68
  spv::Capability::ImageBasic, // 69
  spv::Capability::Geometry, // 70
  spv::Capability::SampledCubeArray, // 71
  spv::Capability::SampledRect, // 72
  spv::Capability::Sampled1D, // 73
  spv::Capability::SampledBuffer, // 74
  spv::Capability::DeviceEnqueue, // 75
  spv::Capability::Pipes, // 76
  spv::Capability::GroupNonUniform, // 77
  spv::Capability::Float8EXT, // 78
  spv::Capability::CooperativeMatrixKHR, // 79
  spv::Capability::WorkgroupMemoryExplicitLayoutKHR, // 80
  spv::Capability::StorageBuffer16BitAccess, // 81
  spv::Capability::VariablePointersStorageBuffer, // 82
  spv::Capability::AtomicStorage, // 83
  spv::Capability::StorageBuffer8BitAccess, // 84
  spv::Capability::RayQueryKHR, // 85
  spv::Capability::RayTracingKHR, // 86
  spv::Capability::CooperativeMatrixKHR, // 87
  spv::Capability::Int4TypeINTEL, // 88
  spv::Capability::CooperativeMatrixKHR, // 89
  spv::Capability::BFloat16TypeKHR, // 90
  spv::Capability::BFloat16TypeKHR, // 91
  spv::Capability::CooperativeMatrixKHR, // 92
  spv::Capability::UntypedPointersKHR, // 93
  spv::Capability::MultiViewport, // 94
  spv::Capability::ShaderViewportIndexLayerEXT, // 95
  spv::Capability::ShaderViewportMaskNV, // 96
  spv::Capability::InputAttachment, // 97
  spv::Capability::ImageBuffer, // 98
  spv::Capability::ShaderNonUniform, // 99
  spv::Capability::InputAttachment, // 100
  spv::Capability::ShaderNonUniform, // 101
  spv::Capability::SampledBuffer, // 102
  spv::Capability::ShaderNonUniform, // 103
  spv::Capability::ImageBuffer, // 104
  spv::Capability::ShaderNonUniform, // 105
  spv::Capability::VectorAnyINTEL, // 106
  spv::Capability::Int8, // 107
  spv::Capability::FPGAClusterAttributesALTERA, // 108
  spv::Capability::FPGAKernelAttributesINTEL, // 109
  spv::Capability::Subgroup2DBlockIOINTEL, // 110
  spv::Capability::VariableLengthArrayINTEL, // 111
  spv::Capability::UntypedPointersKHR, // 112
  spv::Capability::SpecConditionalINTEL, // 113
  spv::Capability::Float16, // 114
  spv::Capability::Float8EXT, // 115
  spv::Capability::CooperativeMatrixLayoutsARM, // 116
  spv::Capability::Shader, // 117
  spv::Capability::Kernel, // 118
  spv::Capability::Shader, // 119
  spv::Capability::UniformDecoration, // 120
  spv::Capability::GeometryStreams, // 121
  spv::Capability::TransformFeedback, // 122
  spv::Capability::Kernel, // 123
  spv::Capability::FloatControls2, // 124
  spv::Capability::Linkage, // 125
  spv::Capability::SampleMaskOverrideCoverageNV, // 126
  spv::Capability::GeometryShaderPassthroughNV, // 127
  spv::Capability::MeshShadingNV, // 128
  spv::Capability::MeshShadingEXT, // 129
  spv::Capability::PushConstantBanksNV, // 130
  spv::Capability::ShaderInvocationReorderNV, // 131
  spv::Capability::ShaderInvocationReorderEXT, // 132
  spv::Capability::BindlessTextureNV, // 133
  spv::Capability::VectorComputeINTEL, // 134
  spv::Capability::IndirectReferencesINTEL, // 135
  spv::Capability::AsmINTEL, // 136
  spv::Capability::FunctionFloatControlINTEL, // 137
  spv::Capability::FPGAMemoryAttributesALTERA, // 138
  spv::Capability::FPGAMemoryAccessesALTERA, // 139
  spv::Capability::LoopFuseALTERA, // 140
  spv::Capability::FPGADSPControlALTERA, // 141
  spv::Capability::MemoryAccessAliasingINTEL, // 142
  spv::Capability::FPGAInvocationPipeliningAttributesALTERA, // 143
  spv::Capability::FPGABufferLocationALTERA, // 144
  spv::Capability::IOPipesALTERA, // 145
  spv::Capability::FPGAClusterAttributesV2ALTERA, // 146
  spv::Capability::FPMaxErrorINTEL, // 147
  spv::Capability::FPGALatencyControlALTERA, // 148
  spv::Capability::FPGAArgumentInterfacesALTERA, // 149
  spv::Capability::GlobalVariableHostAccessINTEL, // 150
  spv::Capability::GlobalVariableFPGADecorationsALTERA, // 151
  spv::Capability::CacheControlsINTEL, // 152
  spv::Capability::TileImageColorReadAccessEXT, // 153
  spv::Capability::Geometry, // 154
  spv::Capability::Tessellation, // 155
  spv::Capability::MeshShadingNV, // 156
  spv::Capability::MeshShadingEXT, // 157
  spv::Capability::Geometry, // 158
  spv::Capability::MeshShadingNV, // 159
  spv::Capability::MeshShadingEXT, // 160
  spv::Capability::SubgroupDispatch, // 161
  spv::Capability::TileImageDepthReadAccessEXT, // 162
  spv::Capability::TileImageStencilReadAccessEXT, // 163
  spv::Capability::SampleMaskPostDepthCoverage, // 164
  spv::Capability::DenormPreserve, // 165
  spv::Capability::DenormFlushToZero, // 166
  spv::Capability::SignedZeroInfNanPreserve, // 167
  spv::Capability::RoundingModeRTE, // 168
  spv::Capability::RoundingModeRTZ, // 169
  spv::Capability::QuadControlKHR, // 170
  spv::Capability::ComputeDerivativeGroupQuadsKHR, // 171
  spv::Capability::ComputeDerivativeGroupLinearKHR, // 172
  spv::Capability::FragmentShaderPixelInterlockEXT, // 173
  spv::Capability::FragmentShaderSampleInterlockEXT, // 174
  spv::Capability::FragmentShaderShadingRateInterlockEXT, // 175
  spv::Capability::Shader64BitIndexingEXT, // 176
  spv::Capability::RoundToInfinityINTEL, // 177
  spv::Capability::KernelAttributesINTEL, // 178
  spv::Capability::FloatControls2, // 179
  spv::Capability::FPGAKernelAttributesv2INTEL, // 180
  spv::Capability::RegisterLimitsINTEL, // 181
  spv::Capability::FloatControls2, // 182
  spv::Capability::FPFastMathModeINTEL, // 183
  spv::Capability::OptNoneEXT, // 184
  spv::Capability::RuntimeAlignedAttributeALTERA, // 185
  spv::Capability::Kernel, // 186
  spv::Capability::GroupNonUniformArithmetic, // 187
  spv::Capability::GroupNonUniformBallot, // 188
  spv::Capability::GroupNonUniformClustered, // 189
  spv::Capability::GroupNonUniformPartitionedEXT, // 190
  spv::Capability::ImageGatherExtended, // 191
  spv::Capability::MinLod, // 192
  spv::Capability::VulkanMemoryModel, // 193
  spv::Capability::FPGALoopControlsALTERA, // 194
  spv::Capability::ArbitraryPrecisionFixedPointALTERA, // 195
  spv::Capability::RawAccessChainsNV, // 196
  spv::Capability::RayTraversalPrimitiveCullingKHR, // 197
  spv::Capability::RayTracingOpacityMicromapEXT, // 198
  spv::Capability::RayQueryKHR, // 199
  spv::Capability::StorageImageExtendedFormats, // 200
  spv::Capability::Int64ImageEXT, // 201
  spv::Capability::Shader, // 202
  spv::Capability::VectorComputeINTEL, // 203
  spv::Capability::GenericPointer, // 204
  spv::Capability::FunctionPointersINTEL, // 205
  spv::Capability::USMStorageClassesALTERA, // 206
  spv::Capability::CooperativeMatrixTensorAddressingNV, // 207
  spv::Capability::CooperativeMatrixBlockLoadsNV, // 208
  spv::Capability::TensorsARM, // 209
  spv::Capability::Addresses, // 210
  spv::Capability::PhysicalStorageBufferAddresses, // 211
  spv::Capability::LiteralSampler, // 212
  spv::Capability::Addresses, // 213
  spv::Capability::UntypedPointersKHR, // 214
  spv::Capability::Addresses, // 215
  spv::Capability::VariablePointers, // 216
  spv::Capability::VariablePointersStorageBuffer, // 217
  spv::Capability::PhysicalStorageBufferAddresses, // 218
  spv::Capability::Kernel, // 219
  spv::Capability::ImageQuery, // 220
  spv::Capability::ImageQuery, // 221
  spv::Capability::Shader, // 222
  spv::Capability::BitInstructions, // 223
  spv::Capability::DerivativeControl, // 224
  spv::Capability::Groups, // 225
  spv::Capability::SparseResidency, // 226
  spv::Capability::PipeStorage, // 227
  spv::Capability::NamedBarrier, // 228
  spv::Capability::GroupNonUniformVote, // 229
  spv::Capability::GroupNonUniformBallot, // 230
  spv::Capability::GroupNonUniformShuffle, // 231
  spv::Capability::GroupNonUniformShuffleRelative, // 232
  spv::Capability::GroupNonUniformArithmetic, // 233
  spv::Capability::GroupNonUniformClustered, // 234
  spv::Capability::GroupNonUniformPartitionedEXT, // 235
  spv::Capability::GroupNonUniformQuad, // 236
  spv::Capability::Addresses, // 237
  spv::Capability::VariablePointers, // 238
  spv::Capability::VariablePointersStorageBuffer, // 239
  spv::Capability::GraphARM, // 240
  spv::Capability::SubgroupBallotKHR, // 241
  spv::Capability::FMAKHR, // 242
  spv::Capability::SubgroupVoteKHR, // 243
  spv::Capability::GroupNonUniformRotateKHR, // 244
  spv::Capability::RayTracingKHR, // 245
  spv::Capability::RayQueryKHR, // 246
  spv::Capability::DotProduct, // 247
  spv::Capability::ReplicatedCompositesEXT, // 248
  spv::Capability::TextureSampleWeightedQCOM, // 249
  spv::Capability::TextureBoxFilterQCOM, // 250
  spv::Capability::TextureBlockMatchQCOM, // 251
  spv::Capability::CooperativeMatrixConversionQCOM, // 252
  spv::Capability::TextureBlockMatch2QCOM, // 253
  spv::Capability::FragmentMaskAMD, // 254
  spv::Capability::ShaderClockKHR, // 255
  spv::Capability::ShaderInvocationReorderNV, // 256
  spv::Capability::RayTracingMotionBlurNV, // 257
  spv::Capability::ImageFootprintNV, // 258
  spv::Capability::CooperativeVectorNV, // 259
  spv::Capability::LongVectorEXT, // 260
  spv::Capability::CooperativeVectorNV, // 261
  spv::Capability::CooperativeVectorTrainingNV, // 262
  spv::Capability::CooperativeMatrixConversionsNV, // 263
  spv::Capability::DisplacementMicromapNV, // 264
  spv::Capability::ShaderInvocationReorderEXT, // 265
  spv::Capability::RayTracingMotionBlurNV, // 266
  spv::Capability::RayQueryPositionFetchKHR, // 267
  spv::Capability::RayTracingNV, // 268
  spv::Capability::RayTracingKHR, // 269
  spv::Capability::RayQueryKHR, // 270
  spv::Capability::DisplacementMicromapNV, // 271
  spv::Capability::CooperativeMatrixNV, // 272
  spv::Capability::FragmentShaderSampleInterlockEXT, // 273
  spv::Capability::FragmentShaderPixelInterlockEXT, // 274
  spv::Capability::FragmentShaderShadingRateInterlockEXT, // 275
  spv::Capability::CooperativeMatrixReductionsNV, // 276
  spv::Capability::CooperativeMatrixPerElementOperationsNV, // 277
  spv::Capability::TensorAddressingNV, // 278
  spv::Capability::DemoteToHelperInvocation, // 279
  spv::Capability::SubgroupShuffleINTEL, // 280
  spv::Capability::SubgroupBufferBlockIOINTEL, // 281
  spv::Capability::SubgroupImageBlockIOINTEL, // 282
  spv::Capability::SubgroupImageMediaBlockIOINTEL, // 283
  spv::Capability::IntegerFunctions2INTEL, // 284
  spv::Capability::AtomicFloat16MinMaxEXT, // 285
  spv::Capability::AtomicFloat32MinMaxEXT, // 286
  spv::Capability::AtomicFloat64MinMaxEXT, // 287
  spv::Capability::AtomicFloat16VectorNV, // 288
  spv::Capability::ExpectAssumeKHR, // 289
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 290
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 291
  spv::Capability::SubgroupAvcMotionEstimationIntraINTEL, // 292
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 293
  spv::Capability::SubgroupAvcMotionEstimationChromaINTEL, // 294
  spv::Capability::VariableLengthArrayINTEL, // 295
  spv::Capability::ArbitraryPrecisionFloatingPointALTERA, // 296
  spv::Capability::UnstructuredLoopControlsINTEL, // 297
  spv::Capability::BlockingPipesALTERA, // 298
  spv::Capability::FPGARegALTERA, // 299
  spv::Capability::AtomicFloat16AddEXT, // 300
  spv::Capability::AtomicFloat32AddEXT, // 301
  spv::Capability::AtomicFloat64AddEXT, // 302
  spv::Capability::AtomicFloat16VectorNV, // 303
  spv::Capability::LongCompositesINTEL, // 304
  spv::Capability::BFloat16ConversionINTEL, // 305
  spv::Capability::SplitBarrierINTEL, // 306
  spv::Capability::ArithmeticFenceEXT, // 307
  spv::Capability::TaskSequenceALTERA, // 308
  spv::Capability::SubgroupBufferPrefetchINTEL, // 309
  spv::Capability::Subgroup2DBlockTransformINTEL, // 310
  spv::Capability::Subgroup2DBlockTransposeINTEL, // 311
  spv::Capability::SubgroupMatrixMultiplyAccumulateINTEL, // 312
  spv::Capability::TernaryBitwiseFunctionINTEL, // 313
  spv::Capability::UntypedVariableLengthArrayINTEL, // 314
  spv::Capability::FunctionVariantsINTEL, // 315
  spv::Capability::GroupUniformArithmeticKHR, // 316
  spv::Capability::TensorFloat32RoundingINTEL, // 317
  spv::Capability::MaskedGatherScatterINTEL, // 318
  spv::Capability::BindlessImagesINTEL, // 319
  spv::Capability::DotProductFloat16AccFloat32VALVE, // 320
  spv::Capability::DotProductBFloat16AccVALVE, // 321
  spv::Capability::DotProductFloat16AccFloat16VALVE, // 322
  spv::Capability::DotProductBFloat16AccVALVE, // 323
  spv::Capability::DotProductFloat8AccFloat32VALVE, // 324
  spv::Capability::Float64, // 325
  spv::Capability::InterpolationFunction, // 326
};

// Array of extensions, referenced by IndexRanges elsewhere.
// Contains all sequences of extensions used in the grammar.
static const spvtools::Extension kExtensionSpans[] = {
  spvtools::Extension::kSPV_EXT_physical_storage_buffer, // 0
  spvtools::Extension::kSPV_KHR_physical_storage_buffer, // 1
  spvtools::Extension::kSPV_KHR_shader_ballot, // 2
  spvtools::Extension::kSPV_KHR_shader_draw_parameters, // 3
  spvtools::Extension::kSPV_KHR_shader_draw_parameters, // 4
  spvtools::Extension::kSPV_NV_mesh_shader, // 5
  spvtools::Extension::kSPV_EXT_mesh_shader, // 6
  spvtools::Extension::kSPV_KHR_fragment_shading_rate, // 7
  spvtools::Extension::kSPV_KHR_device_group, // 8
  spvtools::Extension::kSPV_KHR_multiview, // 9
  spvtools::Extension::kSPV_AMD_shader_explicit_vertex_parameter, // 10
  spvtools::Extension::kSPV_EXT_shader_stencil_export, // 11
  spvtools::Extension::kSPV_NV_viewport_array2, // 12
  spvtools::Extension::kSPV_NV_mesh_shader, // 13
  spvtools::Extension::kSPV_NV_stereo_view_rendering, // 14
  spvtools::Extension::kSPV_NVX_multiview_per_view_attributes, // 15
  spvtools::Extension::kSPV_NV_mesh_shader, // 16
  spvtools::Extension::kSPV_EXT_fragment_fully_covered, // 17
  spvtools::Extension::kSPV_NV_mesh_shader, // 18
  spvtools::Extension::kSPV_NV_fragment_shader_barycentric, // 19
  spvtools::Extension::kSPV_KHR_fragment_shader_barycentric, // 20
  spvtools::Extension::kSPV_EXT_fragment_invocation_density, // 21
  spvtools::Extension::kSPV_NV_shading_rate, // 22
  spvtools::Extension::kSPV_EXT_mesh_shader, // 23
  spvtools::Extension::kSPV_NV_ray_tracing, // 24
  spvtools::Extension::kSPV_KHR_ray_tracing, // 25
  spvtools::Extension::kSPV_NV_ray_tracing, // 26
  spvtools::Extension::kSPV_NV_ray_tracing_motion_blur, // 27
  spvtools::Extension::kSPV_KHR_ray_tracing, // 28
  spvtools::Extension::kSPV_NV_linear_swept_spheres, // 29
  spvtools::Extension::kSPV_NV_shader_sm_builtins, // 30
  spvtools::Extension::kSPV_NV_cluster_acceleration_structure, // 31
  spvtools::Extension::kSPV_KHR_ray_cull_mask, // 32
  spvtools::Extension::kSPV_AMD_shader_ballot, // 33
  spvtools::Extension::kSPV_ARM_core_builtins, // 34
  spvtools::Extension::kSPV_EXT_shader_tile_image, // 35
  spvtools::Extension::kSPV_ARM_tensors, // 36
  spvtools::Extension::kSPV_ARM_graph, // 37
  spvtools::Extension::kSPV_ARM_cooperative_matrix_layouts, // 38
  spvtools::Extension::kSPV_EXT_float8, // 39
  spvtools::Extension::kSPV_KHR_workgroup_memory_explicit_layout, // 40
  spvtools::Extension::kSPV_KHR_subgroup_vote, // 41
  spvtools::Extension::kSPV_KHR_16bit_storage, // 42
  spvtools::Extension::kSPV_KHR_variable_pointers, // 43
  spvtools::Extension::kSPV_KHR_shader_atomic_counter_ops, // 44
  spvtools::Extension::kSPV_KHR_post_depth_coverage, // 45
  spvtools::Extension::kSPV_KHR_8bit_storage, // 46
  spvtools::Extension::kSPV_KHR_float_controls, // 47
  spvtools::Extension::kSPV_KHR_ray_query, // 48
  spvtools::Extension::kSPV_KHR_untyped_pointers, // 49
  spvtools::Extension::kSPV_KHR_ray_query, // 50
  spvtools::Extension::kSPV_KHR_ray_tracing, // 51
  spvtools::Extension::kSPV_QCOM_image_processing, // 52
  spvtools::Extension::kSPV_QCOM_tile_shading, // 53
  spvtools::Extension::kSPV_QCOM_cooperative_matrix_conversion, // 54
  spvtools::Extension::kSPV_QCOM_image_processing2, // 55
  spvtools::Extension::kSPV_AMD_gpu_shader_half_float_fetch, // 56
  spvtools::Extension::kSPV_AMD_texture_gather_bias_lod, // 57
  spvtools::Extension::kSPV_AMD_shader_fragment_mask, // 58
  spvtools::Extension::kSPV_AMD_shader_image_load_store_lod, // 59
  spvtools::Extension::kSPV_EXT_shader_image_int64, // 60
  spvtools::Extension::kSPV_KHR_shader_clock, // 61
  spvtools::Extension::kSPV_AMDX_shader_enqueue, // 62
  spvtools::Extension::kSPV_KHR_quad_control, // 63
  spvtools::Extension::kSPV_INTEL_int4, // 64
  spvtools::Extension::kSPV_KHR_bfloat16, // 65
  spvtools::Extension::kSPV_EXT_descriptor_heap, // 66
  spvtools::Extension::kSPV_NV_sample_mask_override_coverage, // 67
  spvtools::Extension::kSPV_NV_geometry_shader_passthrough, // 68
  spvtools::Extension::kSPV_EXT_shader_viewport_index_layer, // 69
  spvtools::Extension::kSPV_NV_viewport_array2, // 70
  spvtools::Extension::kSPV_NV_viewport_array2, // 71
  spvtools::Extension::kSPV_NVX_multiview_per_view_attributes, // 72
  spvtools::Extension::kSPV_NV_shader_image_footprint, // 73
  spvtools::Extension::kSPV_NV_compute_shader_derivatives, // 74
  spvtools::Extension::kSPV_KHR_compute_shader_derivatives, // 75
  spvtools::Extension::kSPV_NV_shader_subgroup_partitioned, // 76
  spvtools::Extension::kSPV_EXT_shader_subgroup_partitioned, // 77
  spvtools::Extension::kSPV_EXT_descriptor_indexing, // 78
  spvtools::Extension::kSPV_KHR_ray_tracing_position_fetch, // 79
  spvtools::Extension::kSPV_KHR_vulkan_memory_model, // 80
  spvtools::Extension::kSPV_NV_cooperative_matrix, // 81
  spvtools::Extension::kSPV_EXT_fragment_shader_interlock, // 82
  spvtools::Extension::kSPV_EXT_demote_to_helper_invocation, // 83
  spvtools::Extension::kSPV_NV_displacement_micromap, // 84
  spvtools::Extension::kSPV_EXT_opacity_micromap, // 85
  spvtools::Extension::kSPV_NV_shader_invocation_reorder, // 86
  spvtools::Extension::kSPV_EXT_shader_invocation_reorder, // 87
  spvtools::Extension::kSPV_NV_bindless_texture, // 88
  spvtools::Extension::kSPV_NV_cooperative_vector, // 89
  spvtools::Extension::kSPV_NV_shader_atomic_fp16_vector, // 90
  spvtools::Extension::kSPV_NV_raw_access_chains, // 91
  spvtools::Extension::kSPV_NV_push_constant_bank, // 92
  spvtools::Extension::kSPV_EXT_long_vector, // 93
  spvtools::Extension::kSPV_EXT_shader_64bit_indexing, // 94
  spvtools::Extension::kSPV_NV_cooperative_matrix2, // 95
  spvtools::Extension::kSPV_NV_tensor_addressing, // 96
  spvtools::Extension::kSPV_INTEL_subgroups, // 97
  spvtools::Extension::kSPV_INTEL_media_block_io, // 98
  spvtools::Extension::kSPV_INTEL_float_controls2, // 99
  spvtools::Extension::kSPV_INTEL_shader_integer_functions2, // 100
  spvtools::Extension::kSPV_INTEL_function_pointers, // 101
  spvtools::Extension::kSPV_INTEL_inline_assembly, // 102
  spvtools::Extension::kSPV_EXT_shader_atomic_float_min_max, // 103
  spvtools::Extension::kSPV_INTEL_vector_compute, // 104
  spvtools::Extension::kSPV_KHR_expect_assume, // 105
  spvtools::Extension::kSPV_INTEL_device_side_avc_motion_estimation, // 106
  spvtools::Extension::kSPV_INTEL_variable_length_array, // 107
  spvtools::Extension::kSPV_ALTERA_fpga_memory_attributes, // 108
  spvtools::Extension::kSPV_INTEL_fpga_memory_attributes, // 109
  spvtools::Extension::kSPV_INTEL_fp_fast_math_mode, // 110
  spvtools::Extension::kSPV_ALTERA_arbitrary_precision_integers, // 111
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_integers, // 112
  spvtools::Extension::kSPV_ALTERA_arbitrary_precision_floating_point, // 113
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_floating_point, // 114
  spvtools::Extension::kSPV_INTEL_unstructured_loop_controls, // 115
  spvtools::Extension::kSPV_ALTERA_fpga_loop_controls, // 116
  spvtools::Extension::kSPV_INTEL_fpga_loop_controls, // 117
  spvtools::Extension::kSPV_INTEL_kernel_attributes, // 118
  spvtools::Extension::kSPV_ALTERA_fpga_memory_accesses, // 119
  spvtools::Extension::kSPV_INTEL_fpga_memory_accesses, // 120
  spvtools::Extension::kSPV_ALTERA_fpga_cluster_attributes, // 121
  spvtools::Extension::kSPV_INTEL_fpga_cluster_attributes, // 122
  spvtools::Extension::kSPV_ALTERA_loop_fuse, // 123
  spvtools::Extension::kSPV_INTEL_loop_fuse, // 124
  spvtools::Extension::kSPV_ALTERA_fpga_dsp_control, // 125
  spvtools::Extension::kSPV_INTEL_fpga_dsp_control, // 126
  spvtools::Extension::kSPV_INTEL_memory_access_aliasing, // 127
  spvtools::Extension::kSPV_ALTERA_fpga_invocation_pipelining_attributes, // 128
  spvtools::Extension::kSPV_INTEL_fpga_invocation_pipelining_attributes, // 129
  spvtools::Extension::kSPV_ALTERA_fpga_buffer_location, // 130
  spvtools::Extension::kSPV_INTEL_fpga_buffer_location, // 131
  spvtools::Extension::kSPV_ALTERA_arbitrary_precision_fixed_point, // 132
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_fixed_point, // 133
  spvtools::Extension::kSPV_ALTERA_usm_storage_classes, // 134
  spvtools::Extension::kSPV_INTEL_usm_storage_classes, // 135
  spvtools::Extension::kSPV_ALTERA_runtime_aligned, // 136
  spvtools::Extension::kSPV_INTEL_runtime_aligned, // 137
  spvtools::Extension::kSPV_ALTERA_io_pipes, // 138
  spvtools::Extension::kSPV_INTEL_io_pipes, // 139
  spvtools::Extension::kSPV_ALTERA_blocking_pipes, // 140
  spvtools::Extension::kSPV_INTEL_blocking_pipes, // 141
  spvtools::Extension::kSPV_ALTERA_fpga_reg, // 142
  spvtools::Extension::kSPV_INTEL_fpga_reg, // 143
  spvtools::Extension::kSPV_KHR_integer_dot_product, // 144
  spvtools::Extension::kSPV_KHR_cooperative_matrix, // 145
  spvtools::Extension::kSPV_EXT_replicated_composites, // 146
  spvtools::Extension::kSPV_KHR_bit_instructions, // 147
  spvtools::Extension::kSPV_KHR_subgroup_rotate, // 148
  spvtools::Extension::kSPV_KHR_float_controls2, // 149
  spvtools::Extension::kSPV_KHR_fma, // 150
  spvtools::Extension::kSPV_EXT_shader_atomic_float_add, // 151
  spvtools::Extension::kSPV_INTEL_long_composites, // 152
  spvtools::Extension::kSPV_EXT_optnone, // 153
  spvtools::Extension::kSPV_INTEL_optnone, // 154
  spvtools::Extension::kSPV_EXT_shader_atomic_float16_add, // 155
  spvtools::Extension::kSPV_INTEL_debug_module, // 156
  spvtools::Extension::kSPV_INTEL_bfloat16_conversion, // 157
  spvtools::Extension::kSPV_INTEL_split_barrier, // 158
  spvtools::Extension::kSPV_EXT_arithmetic_fence, // 159
  spvtools::Extension::kSPV_ALTERA_task_sequence, // 160
  spvtools::Extension::kSPV_INTEL_task_sequence, // 161
  spvtools::Extension::kSPV_INTEL_fp_max_error, // 162
  spvtools::Extension::kSPV_ALTERA_fpga_latency_control, // 163
  spvtools::Extension::kSPV_INTEL_fpga_latency_control, // 164
  spvtools::Extension::kSPV_ALTERA_fpga_argument_interfaces, // 165
  spvtools::Extension::kSPV_INTEL_fpga_argument_interfaces, // 166
  spvtools::Extension::kSPV_INTEL_global_variable_host_access, // 167
  spvtools::Extension::kSPV_ALTERA_global_variable_fpga_decorations, // 168
  spvtools::Extension::kSPV_INTEL_global_variable_fpga_decorations, // 169
  spvtools::Extension::kSPV_INTEL_subgroup_buffer_prefetch, // 170
  spvtools::Extension::kSPV_INTEL_2d_block_io, // 171
  spvtools::Extension::kSPV_INTEL_subgroup_matrix_multiply_accumulate, // 172
  spvtools::Extension::kSPV_INTEL_ternary_bitwise_function, // 173
  spvtools::Extension::kSPV_INTEL_function_variants, // 174
  spvtools::Extension::kSPV_KHR_uniform_group_instructions, // 175
  spvtools::Extension::kSPV_INTEL_tensor_float32_conversion, // 176
  spvtools::Extension::kSPV_INTEL_masked_gather_scatter, // 177
  spvtools::Extension::kSPV_INTEL_cache_controls, // 178
  spvtools::Extension::kSPV_INTEL_maximum_registers, // 179
  spvtools::Extension::kSPV_INTEL_bindless_images, // 180
  spvtools::Extension::kSPV_VALVE_mixed_float_dot_product, // 181
  spvtools::Extension::kSPV_KHR_no_integer_wrap_decoration, // 182
  spvtools::Extension::kSPV_NV_mesh_shader, // 183
  spvtools::Extension::kSPV_EXT_mesh_shader, // 184
  spvtools::Extension::kSPV_GOOGLE_hlsl_functionality1, // 185
  spvtools::Extension::kSPV_GOOGLE_user_type, // 186
  spvtools::Extension::kSPV_KHR_subgroup_uniform_control_flow, // 187
  spvtools::Extension::kSPV_AMD_shader_early_and_late_fragment_tests, // 188
  spvtools::Extension::kSPV_AMD_shader_early_and_late_fragment_tests, // 189
  spvtools::Extension::kSPV_EXT_shader_stencil_export, // 190
  spvtools::Extension::kSPV_KHR_maximal_reconvergence, // 191
  spvtools::Extension::kSPV_KHR_linkonce_odr, // 192
  spvtools::Extension::kSPV_KHR_storage_buffer_storage_class, // 193
  spvtools::Extension::kSPV_KHR_variable_pointers, // 194
  spvtools::Extension::kSPV_KHR_terminate_invocation, // 195
  spvtools::Extension::kSPV_KHR_relaxed_extended_instruction, // 196
  spvtools::Extension::kSPV_KHR_ray_tracing, // 197
  spvtools::Extension::kSPV_KHR_ray_query, // 198
  spvtools::Extension::kSPV_NV_ray_tracing, // 199
  spvtools::Extension::kSPV_KHR_ray_tracing, // 200
  spvtools::Extension::kSPV_KHR_ray_query, // 201
  spvtools::Extension::kSPV_NV_displacement_micromap, // 202
  spvtools::Extension::kSPV_GOOGLE_decorate_string, // 203
  spvtools::Extension::kSPV_GOOGLE_hlsl_functionality1, // 204
};

// Array of operand types, referenced by IndexRanges elsewhere.
// Contains all sequences of operand types used in the grammar.
static const spv_operand_type_t kOperandSpans[] = {
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 0
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 2
  SPV_OPERAND_TYPE_BUILT_IN, // 3
  SPV_OPERAND_TYPE_SCOPE_ID, // 4
  SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE, // 5
  SPV_OPERAND_TYPE_FP_ROUNDING_MODE, // 6
  SPV_OPERAND_TYPE_FP_FAST_MATH_MODE, // 7
  SPV_OPERAND_TYPE_LITERAL_STRING, // 8
  SPV_OPERAND_TYPE_LINKAGE_TYPE, // 9
  SPV_OPERAND_TYPE_ID, // 10
  SPV_OPERAND_TYPE_LITERAL_STRING, // 11
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 12
  SPV_OPERAND_TYPE_FP_ROUNDING_MODE, // 13
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 14
  SPV_OPERAND_TYPE_FPDENORM_MODE, // 15
  SPV_OPERAND_TYPE_LITERAL_STRING, // 16
  SPV_OPERAND_TYPE_LITERAL_STRING, // 17
  SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER, // 18
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 19
  SPV_OPERAND_TYPE_FPOPERATION_MODE, // 20
  SPV_OPERAND_TYPE_LITERAL_FLOAT, // 21
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 22
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 23
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 24
  SPV_OPERAND_TYPE_ACCESS_QUALIFIER, // 25
  SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER, // 26
  SPV_OPERAND_TYPE_LITERAL_STRING, // 27
  SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER, // 28
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 29
  SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL, // 30
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 31
  SPV_OPERAND_TYPE_STORE_CACHE_CONTROL, // 32
  SPV_OPERAND_TYPE_ID, // 33
  SPV_OPERAND_TYPE_ID, // 34
  SPV_OPERAND_TYPE_ID, // 35
  SPV_OPERAND_TYPE_ID, // 36
  SPV_OPERAND_TYPE_ID, // 37
  SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS, // 38
  SPV_OPERAND_TYPE_TYPE_ID, // 39
  SPV_OPERAND_TYPE_RESULT_ID, // 40
  SPV_OPERAND_TYPE_SOURCE_LANGUAGE, // 41
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 42
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 43
  SPV_OPERAND_TYPE_OPTIONAL_LITERAL_STRING, // 44
  SPV_OPERAND_TYPE_ID, // 45
  SPV_OPERAND_TYPE_LITERAL_STRING, // 46
  SPV_OPERAND_TYPE_ID, // 47
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 48
  SPV_OPERAND_TYPE_LITERAL_STRING, // 49
  SPV_OPERAND_TYPE_RESULT_ID, // 50
  SPV_OPERAND_TYPE_LITERAL_STRING, // 51
  SPV_OPERAND_TYPE_ID, // 52
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 53
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 54
  SPV_OPERAND_TYPE_TYPE_ID, // 55
  SPV_OPERAND_TYPE_RESULT_ID, // 56
  SPV_OPERAND_TYPE_ID, // 57
  SPV_OPERAND_TYPE_EXTENSION_INSTRUCTION_NUMBER, // 58
  SPV_OPERAND_TYPE_ADDRESSING_MODEL, // 59
  SPV_OPERAND_TYPE_MEMORY_MODEL, // 60
  SPV_OPERAND_TYPE_EXECUTION_MODEL, // 61
  SPV_OPERAND_TYPE_ID, // 62
  SPV_OPERAND_TYPE_LITERAL_STRING, // 63
  SPV_OPERAND_TYPE_VARIABLE_ID, // 64
  SPV_OPERAND_TYPE_ID, // 65
  SPV_OPERAND_TYPE_EXECUTION_MODE, // 66
  SPV_OPERAND_TYPE_CAPABILITY, // 67
  SPV_OPERAND_TYPE_RESULT_ID, // 68
  SPV_OPERAND_TYPE_RESULT_ID, // 69
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 70
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 71
  SPV_OPERAND_TYPE_RESULT_ID, // 72
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 73
  SPV_OPERAND_TYPE_OPTIONAL_FPENCODING, // 74
  SPV_OPERAND_TYPE_RESULT_ID, // 75
  SPV_OPERAND_TYPE_ID, // 76
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 77
  SPV_OPERAND_TYPE_RESULT_ID, // 78
  SPV_OPERAND_TYPE_ID, // 79
  SPV_OPERAND_TYPE_DIMENSIONALITY, // 80
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 81
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 82
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 83
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 84
  SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT, // 85
  SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER, // 86
  SPV_OPERAND_TYPE_RESULT_ID, // 87
  SPV_OPERAND_TYPE_ID, // 88
  SPV_OPERAND_TYPE_RESULT_ID, // 89
  SPV_OPERAND_TYPE_ID, // 90
  SPV_OPERAND_TYPE_ID, // 91
  SPV_OPERAND_TYPE_RESULT_ID, // 92
  SPV_OPERAND_TYPE_VARIABLE_ID, // 93
  SPV_OPERAND_TYPE_RESULT_ID, // 94
  SPV_OPERAND_TYPE_STORAGE_CLASS, // 95
  SPV_OPERAND_TYPE_ID, // 96
  SPV_OPERAND_TYPE_RESULT_ID, // 97
  SPV_OPERAND_TYPE_ID, // 98
  SPV_OPERAND_TYPE_VARIABLE_ID, // 99
  SPV_OPERAND_TYPE_RESULT_ID, // 100
  SPV_OPERAND_TYPE_ACCESS_QUALIFIER, // 101
  SPV_OPERAND_TYPE_ID, // 102
  SPV_OPERAND_TYPE_STORAGE_CLASS, // 103
  SPV_OPERAND_TYPE_TYPE_ID, // 104
  SPV_OPERAND_TYPE_RESULT_ID, // 105
  SPV_OPERAND_TYPE_TYPED_LITERAL_NUMBER, // 106
  SPV_OPERAND_TYPE_TYPE_ID, // 107
  SPV_OPERAND_TYPE_RESULT_ID, // 108
  SPV_OPERAND_TYPE_VARIABLE_ID, // 109
  SPV_OPERAND_TYPE_TYPE_ID, // 110
  SPV_OPERAND_TYPE_RESULT_ID, // 111
  SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE, // 112
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 113
  SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE, // 114
  SPV_OPERAND_TYPE_TYPE_ID, // 115
  SPV_OPERAND_TYPE_RESULT_ID, // 116
  SPV_OPERAND_TYPE_SPEC_CONSTANT_OP_NUMBER, // 117
  SPV_OPERAND_TYPE_TYPE_ID, // 118
  SPV_OPERAND_TYPE_RESULT_ID, // 119
  SPV_OPERAND_TYPE_FUNCTION_CONTROL, // 120
  SPV_OPERAND_TYPE_ID, // 121
  SPV_OPERAND_TYPE_TYPE_ID, // 122
  SPV_OPERAND_TYPE_RESULT_ID, // 123
  SPV_OPERAND_TYPE_ID, // 124
  SPV_OPERAND_TYPE_VARIABLE_ID, // 125
  SPV_OPERAND_TYPE_TYPE_ID, // 126
  SPV_OPERAND_TYPE_RESULT_ID, // 127
  SPV_OPERAND_TYPE_STORAGE_CLASS, // 128
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 129
  SPV_OPERAND_TYPE_TYPE_ID, // 130
  SPV_OPERAND_TYPE_RESULT_ID, // 131
  SPV_OPERAND_TYPE_ID, // 132
  SPV_OPERAND_TYPE_ID, // 133
  SPV_OPERAND_TYPE_ID, // 134
  SPV_OPERAND_TYPE_TYPE_ID, // 135
  SPV_OPERAND_TYPE_RESULT_ID, // 136
  SPV_OPERAND_TYPE_ID, // 137
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 138
  SPV_OPERAND_TYPE_ID, // 139
  SPV_OPERAND_TYPE_ID, // 140
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 141
  SPV_OPERAND_TYPE_ID, // 142
  SPV_OPERAND_TYPE_ID, // 143
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 144
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 145
  SPV_OPERAND_TYPE_ID, // 146
  SPV_OPERAND_TYPE_ID, // 147
  SPV_OPERAND_TYPE_ID, // 148
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 149
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 150
  SPV_OPERAND_TYPE_TYPE_ID, // 151
  SPV_OPERAND_TYPE_RESULT_ID, // 152
  SPV_OPERAND_TYPE_ID, // 153
  SPV_OPERAND_TYPE_ID, // 154
  SPV_OPERAND_TYPE_VARIABLE_ID, // 155
  SPV_OPERAND_TYPE_TYPE_ID, // 156
  SPV_OPERAND_TYPE_RESULT_ID, // 157
  SPV_OPERAND_TYPE_ID, // 158
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 159
  SPV_OPERAND_TYPE_TYPE_ID, // 160
  SPV_OPERAND_TYPE_RESULT_ID, // 161
  SPV_OPERAND_TYPE_ID, // 162
  SPV_OPERAND_TYPE_ID, // 163
  SPV_OPERAND_TYPE_DECORATION, // 164
  SPV_OPERAND_TYPE_ID, // 165
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 166
  SPV_OPERAND_TYPE_DECORATION, // 167
  SPV_OPERAND_TYPE_ID, // 168
  SPV_OPERAND_TYPE_VARIABLE_ID, // 169
  SPV_OPERAND_TYPE_ID, // 170
  SPV_OPERAND_TYPE_VARIABLE_ID_LITERAL_INTEGER, // 171
  SPV_OPERAND_TYPE_TYPE_ID, // 172
  SPV_OPERAND_TYPE_RESULT_ID, // 173
  SPV_OPERAND_TYPE_ID, // 174
  SPV_OPERAND_TYPE_ID, // 175
  SPV_OPERAND_TYPE_TYPE_ID, // 176
  SPV_OPERAND_TYPE_RESULT_ID, // 177
  SPV_OPERAND_TYPE_ID, // 178
  SPV_OPERAND_TYPE_ID, // 179
  SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER, // 180
  SPV_OPERAND_TYPE_TYPE_ID, // 181
  SPV_OPERAND_TYPE_RESULT_ID, // 182
  SPV_OPERAND_TYPE_ID, // 183
  SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER, // 184
  SPV_OPERAND_TYPE_TYPE_ID, // 185
  SPV_OPERAND_TYPE_RESULT_ID, // 186
  SPV_OPERAND_TYPE_ID, // 187
  SPV_OPERAND_TYPE_ID, // 188
  SPV_OPERAND_TYPE_OPTIONAL_IMAGE, // 189
  SPV_OPERAND_TYPE_TYPE_ID, // 190
  SPV_OPERAND_TYPE_RESULT_ID, // 191
  SPV_OPERAND_TYPE_ID, // 192
  SPV_OPERAND_TYPE_ID, // 193
  SPV_OPERAND_TYPE_IMAGE, // 194
  SPV_OPERAND_TYPE_TYPE_ID, // 195
  SPV_OPERAND_TYPE_RESULT_ID, // 196
  SPV_OPERAND_TYPE_ID, // 197
  SPV_OPERAND_TYPE_ID, // 198
  SPV_OPERAND_TYPE_ID, // 199
  SPV_OPERAND_TYPE_OPTIONAL_IMAGE, // 200
  SPV_OPERAND_TYPE_TYPE_ID, // 201
  SPV_OPERAND_TYPE_RESULT_ID, // 202
  SPV_OPERAND_TYPE_ID, // 203
  SPV_OPERAND_TYPE_ID, // 204
  SPV_OPERAND_TYPE_ID, // 205
  SPV_OPERAND_TYPE_IMAGE, // 206
  SPV_OPERAND_TYPE_ID, // 207
  SPV_OPERAND_TYPE_ID, // 208
  SPV_OPERAND_TYPE_ID, // 209
  SPV_OPERAND_TYPE_OPTIONAL_IMAGE, // 210
  SPV_OPERAND_TYPE_TYPE_ID, // 211
  SPV_OPERAND_TYPE_RESULT_ID, // 212
  SPV_OPERAND_TYPE_ID, // 213
  SPV_OPERAND_TYPE_STORAGE_CLASS, // 214
  SPV_OPERAND_TYPE_TYPE_ID, // 215
  SPV_OPERAND_TYPE_RESULT_ID, // 216
  SPV_OPERAND_TYPE_ID, // 217
  SPV_OPERAND_TYPE_ID, // 218
  SPV_OPERAND_TYPE_ID, // 219
  SPV_OPERAND_TYPE_ID, // 220
  SPV_OPERAND_TYPE_SCOPE_ID, // 221
  SPV_OPERAND_TYPE_SCOPE_ID, // 222
  SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID, // 223
  SPV_OPERAND_TYPE_SCOPE_ID, // 224
  SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID, // 225
  SPV_OPERAND_TYPE_TYPE_ID, // 226
  SPV_OPERAND_TYPE_RESULT_ID, // 227
  SPV_OPERAND_TYPE_ID, // 228
  SPV_OPERAND_TYPE_SCOPE_ID, // 229
  SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID, // 230
  SPV_OPERAND_TYPE_ID, // 231
  SPV_OPERAND_TYPE_SCOPE_ID, // 232
  SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID, // 233
  SPV_OPERAND_TYPE_ID, // 234
  SPV_OPERAND_TYPE_TYPE_ID, // 235
  SPV_OPERAND_TYPE_RESULT_ID, // 236
  SPV_OPERAND_TYPE_ID, // 237
  SPV_OPERAND_TYPE_SCOPE_ID, // 238
  SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID, // 239
  SPV_OPERAND_TYPE_ID, // 240
  SPV_OPERAND_TYPE_TYPE_ID, // 241
  SPV_OPERAND_TYPE_RESULT_ID, // 242
  SPV_OPERAND_TYPE_ID, // 243
  SPV_OPERAND_TYPE_SCOPE_ID, // 244
  SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID, // 245
  SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID, // 246
  SPV_OPERAND_TYPE_ID, // 247
  SPV_OPERAND_TYPE_ID, // 248
  SPV_OPERAND_TYPE_ID, // 249
  SPV_OPERAND_TYPE_ID, // 250
  SPV_OPERAND_TYPE_LOOP_CONTROL, // 251
  SPV_OPERAND_TYPE_ID, // 252
  SPV_OPERAND_TYPE_SELECTION_CONTROL, // 253
  SPV_OPERAND_TYPE_ID, // 254
  SPV_OPERAND_TYPE_ID, // 255
  SPV_OPERAND_TYPE_ID, // 256
  SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER, // 257
  SPV_OPERAND_TYPE_ID, // 258
  SPV_OPERAND_TYPE_ID, // 259
  SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER_ID, // 260
  SPV_OPERAND_TYPE_ID, // 261
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 262
  SPV_OPERAND_TYPE_TYPE_ID, // 263
  SPV_OPERAND_TYPE_RESULT_ID, // 264
  SPV_OPERAND_TYPE_SCOPE_ID, // 265
  SPV_OPERAND_TYPE_ID, // 266
  SPV_OPERAND_TYPE_ID, // 267
  SPV_OPERAND_TYPE_ID, // 268
  SPV_OPERAND_TYPE_ID, // 269
  SPV_OPERAND_TYPE_ID, // 270
  SPV_OPERAND_TYPE_SCOPE_ID, // 271
  SPV_OPERAND_TYPE_ID, // 272
  SPV_OPERAND_TYPE_ID, // 273
  SPV_OPERAND_TYPE_TYPE_ID, // 274
  SPV_OPERAND_TYPE_RESULT_ID, // 275
  SPV_OPERAND_TYPE_SCOPE_ID, // 276
  SPV_OPERAND_TYPE_ID, // 277
  SPV_OPERAND_TYPE_TYPE_ID, // 278
  SPV_OPERAND_TYPE_RESULT_ID, // 279
  SPV_OPERAND_TYPE_SCOPE_ID, // 280
  SPV_OPERAND_TYPE_ID, // 281
  SPV_OPERAND_TYPE_ID, // 282
  SPV_OPERAND_TYPE_TYPE_ID, // 283
  SPV_OPERAND_TYPE_RESULT_ID, // 284
  SPV_OPERAND_TYPE_SCOPE_ID, // 285
  SPV_OPERAND_TYPE_GROUP_OPERATION, // 286
  SPV_OPERAND_TYPE_ID, // 287
  SPV_OPERAND_TYPE_TYPE_ID, // 288
  SPV_OPERAND_TYPE_RESULT_ID, // 289
  SPV_OPERAND_TYPE_ID, // 290
  SPV_OPERAND_TYPE_ID, // 291
  SPV_OPERAND_TYPE_ID, // 292
  SPV_OPERAND_TYPE_ID, // 293
  SPV_OPERAND_TYPE_ID, // 294
  SPV_OPERAND_TYPE_ID, // 295
  SPV_OPERAND_TYPE_ID, // 296
  SPV_OPERAND_TYPE_ID, // 297
  SPV_OPERAND_TYPE_ID, // 298
  SPV_OPERAND_TYPE_ID, // 299
  SPV_OPERAND_TYPE_TYPE_ID, // 300
  SPV_OPERAND_TYPE_RESULT_ID, // 301
  SPV_OPERAND_TYPE_SCOPE_ID, // 302
  SPV_OPERAND_TYPE_ID, // 303
  SPV_OPERAND_TYPE_ID, // 304
  SPV_OPERAND_TYPE_ID, // 305
  SPV_OPERAND_TYPE_ID, // 306
  SPV_OPERAND_TYPE_SCOPE_ID, // 307
  SPV_OPERAND_TYPE_ID, // 308
  SPV_OPERAND_TYPE_ID, // 309
  SPV_OPERAND_TYPE_ID, // 310
  SPV_OPERAND_TYPE_ID, // 311
  SPV_OPERAND_TYPE_TYPE_ID, // 312
  SPV_OPERAND_TYPE_RESULT_ID, // 313
  SPV_OPERAND_TYPE_ID, // 314
  SPV_OPERAND_TYPE_ID, // 315
  SPV_OPERAND_TYPE_ID, // 316
  SPV_OPERAND_TYPE_ID, // 317
  SPV_OPERAND_TYPE_ID, // 318
  SPV_OPERAND_TYPE_ID, // 319
  SPV_OPERAND_TYPE_ID, // 320
  SPV_OPERAND_TYPE_ID, // 321
  SPV_OPERAND_TYPE_ID, // 322
  SPV_OPERAND_TYPE_ID, // 323
  SPV_OPERAND_TYPE_VARIABLE_ID, // 324
  SPV_OPERAND_TYPE_TYPE_ID, // 325
  SPV_OPERAND_TYPE_RESULT_ID, // 326
  SPV_OPERAND_TYPE_ID, // 327
  SPV_OPERAND_TYPE_ID, // 328
  SPV_OPERAND_TYPE_ID, // 329
  SPV_OPERAND_TYPE_ID, // 330
  SPV_OPERAND_TYPE_ID, // 331
  SPV_OPERAND_TYPE_ID, // 332
  SPV_OPERAND_TYPE_SCOPE_ID, // 333
  SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID, // 334
  SPV_OPERAND_TYPE_TYPE_ID, // 335
  SPV_OPERAND_TYPE_RESULT_ID, // 336
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 337
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 338
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 339
  SPV_OPERAND_TYPE_TYPE_ID, // 340
  SPV_OPERAND_TYPE_RESULT_ID, // 341
  SPV_OPERAND_TYPE_SCOPE_ID, // 342
  SPV_OPERAND_TYPE_TYPE_ID, // 343
  SPV_OPERAND_TYPE_RESULT_ID, // 344
  SPV_OPERAND_TYPE_SCOPE_ID, // 345
  SPV_OPERAND_TYPE_GROUP_OPERATION, // 346
  SPV_OPERAND_TYPE_ID, // 347
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 348
  SPV_OPERAND_TYPE_TYPE_ID, // 349
  SPV_OPERAND_TYPE_RESULT_ID, // 350
  SPV_OPERAND_TYPE_ID, // 351
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 352
  SPV_OPERAND_TYPE_TYPE_ID, // 353
  SPV_OPERAND_TYPE_RESULT_ID, // 354
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 355
  SPV_OPERAND_TYPE_RESULT_ID, // 356
  SPV_OPERAND_TYPE_ID, // 357
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 358
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 359
  SPV_OPERAND_TYPE_TYPE_ID, // 360
  SPV_OPERAND_TYPE_RESULT_ID, // 361
  SPV_OPERAND_TYPE_ID, // 362
  SPV_OPERAND_TYPE_ID, // 363
  SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS, // 364
  SPV_OPERAND_TYPE_ID, // 365
  SPV_OPERAND_TYPE_ID, // 366
  SPV_OPERAND_TYPE_ID, // 367
  SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS, // 368
  SPV_OPERAND_TYPE_TYPE_ID, // 369
  SPV_OPERAND_TYPE_RESULT_ID, // 370
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 371
  SPV_OPERAND_TYPE_ID, // 372
  SPV_OPERAND_TYPE_LITERAL_STRING, // 373
  SPV_OPERAND_TYPE_VARIABLE_ID, // 374
  SPV_OPERAND_TYPE_ID, // 375
  SPV_OPERAND_TYPE_ID, // 376
  SPV_OPERAND_TYPE_VARIABLE_ID, // 377
  SPV_OPERAND_TYPE_RESULT_ID, // 378
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 379
  SPV_OPERAND_TYPE_VARIABLE_ID, // 380
  SPV_OPERAND_TYPE_RESULT_ID, // 381
  SPV_OPERAND_TYPE_STORAGE_CLASS, // 382
  SPV_OPERAND_TYPE_TYPE_ID, // 383
  SPV_OPERAND_TYPE_RESULT_ID, // 384
  SPV_OPERAND_TYPE_STORAGE_CLASS, // 385
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 386
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 387
  SPV_OPERAND_TYPE_TYPE_ID, // 388
  SPV_OPERAND_TYPE_RESULT_ID, // 389
  SPV_OPERAND_TYPE_ID, // 390
  SPV_OPERAND_TYPE_ID, // 391
  SPV_OPERAND_TYPE_ID, // 392
  SPV_OPERAND_TYPE_VARIABLE_ID, // 393
  SPV_OPERAND_TYPE_TYPE_ID, // 394
  SPV_OPERAND_TYPE_RESULT_ID, // 395
  SPV_OPERAND_TYPE_ID, // 396
  SPV_OPERAND_TYPE_ID, // 397
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 398
  SPV_OPERAND_TYPE_ID, // 399
  SPV_OPERAND_TYPE_ID, // 400
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 401
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 402
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 403
  SPV_OPERAND_TYPE_TYPE_ID, // 404
  SPV_OPERAND_TYPE_RESULT_ID, // 405
  SPV_OPERAND_TYPE_SCOPE_ID, // 406
  SPV_OPERAND_TYPE_ID, // 407
  SPV_OPERAND_TYPE_ID, // 408
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 409
  SPV_OPERAND_TYPE_TYPE_ID, // 410
  SPV_OPERAND_TYPE_RESULT_ID, // 411
  SPV_OPERAND_TYPE_ID, // 412
  SPV_OPERAND_TYPE_EXTENSION_INSTRUCTION_NUMBER, // 413
  SPV_OPERAND_TYPE_VARIABLE_ID, // 414
  SPV_OPERAND_TYPE_TYPE_ID, // 415
  SPV_OPERAND_TYPE_RESULT_ID, // 416
  SPV_OPERAND_TYPE_ID, // 417
  SPV_OPERAND_TYPE_ID, // 418
  SPV_OPERAND_TYPE_ID, // 419
  SPV_OPERAND_TYPE_ID, // 420
  SPV_OPERAND_TYPE_ID, // 421
  SPV_OPERAND_TYPE_ID, // 422
  SPV_OPERAND_TYPE_ID, // 423
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 424
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 425
  SPV_OPERAND_TYPE_ID, // 426
  SPV_OPERAND_TYPE_ID, // 427
  SPV_OPERAND_TYPE_ID, // 428
  SPV_OPERAND_TYPE_ID, // 429
  SPV_OPERAND_TYPE_ID, // 430
  SPV_OPERAND_TYPE_ID, // 431
  SPV_OPERAND_TYPE_ID, // 432
  SPV_OPERAND_TYPE_ID, // 433
  SPV_OPERAND_TYPE_ID, // 434
  SPV_OPERAND_TYPE_ID, // 435
  SPV_OPERAND_TYPE_ID, // 436
  SPV_OPERAND_TYPE_TYPE_ID, // 437
  SPV_OPERAND_TYPE_RESULT_ID, // 438
  SPV_OPERAND_TYPE_ID, // 439
  SPV_OPERAND_TYPE_ID, // 440
  SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT, // 441
  SPV_OPERAND_TYPE_TYPE_ID, // 442
  SPV_OPERAND_TYPE_RESULT_ID, // 443
  SPV_OPERAND_TYPE_ID, // 444
  SPV_OPERAND_TYPE_ID, // 445
  SPV_OPERAND_TYPE_ID, // 446
  SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT, // 447
  SPV_OPERAND_TYPE_RESULT_ID, // 448
  SPV_OPERAND_TYPE_ID, // 449
  SPV_OPERAND_TYPE_SCOPE_ID, // 450
  SPV_OPERAND_TYPE_ID, // 451
  SPV_OPERAND_TYPE_ID, // 452
  SPV_OPERAND_TYPE_ID, // 453
  SPV_OPERAND_TYPE_TYPE_ID, // 454
  SPV_OPERAND_TYPE_RESULT_ID, // 455
  SPV_OPERAND_TYPE_ID, // 456
  SPV_OPERAND_TYPE_ID, // 457
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 458
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 459
  SPV_OPERAND_TYPE_ID, // 460
  SPV_OPERAND_TYPE_ID, // 461
  SPV_OPERAND_TYPE_ID, // 462
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 463
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 464
  SPV_OPERAND_TYPE_TYPE_ID, // 465
  SPV_OPERAND_TYPE_RESULT_ID, // 466
  SPV_OPERAND_TYPE_ID, // 467
  SPV_OPERAND_TYPE_ID, // 468
  SPV_OPERAND_TYPE_ID, // 469
  SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS, // 470
  SPV_OPERAND_TYPE_ID, // 471
  SPV_OPERAND_TYPE_ID, // 472
  SPV_OPERAND_TYPE_ID, // 473
  SPV_OPERAND_TYPE_ID, // 474
  SPV_OPERAND_TYPE_ID, // 475
  SPV_OPERAND_TYPE_ID, // 476
  SPV_OPERAND_TYPE_ID, // 477
  SPV_OPERAND_TYPE_ID, // 478
  SPV_OPERAND_TYPE_ID, // 479
  SPV_OPERAND_TYPE_ID, // 480
  SPV_OPERAND_TYPE_ID, // 481
  SPV_OPERAND_TYPE_ID, // 482
  SPV_OPERAND_TYPE_ID, // 483
  SPV_OPERAND_TYPE_ID, // 484
  SPV_OPERAND_TYPE_ID, // 485
  SPV_OPERAND_TYPE_ID, // 486
  SPV_OPERAND_TYPE_ID, // 487
  SPV_OPERAND_TYPE_ID, // 488
  SPV_OPERAND_TYPE_ID, // 489
  SPV_OPERAND_TYPE_ID, // 490
  SPV_OPERAND_TYPE_ID, // 491
  SPV_OPERAND_TYPE_ID, // 492
  SPV_OPERAND_TYPE_ID, // 493
  SPV_OPERAND_TYPE_ID, // 494
  SPV_OPERAND_TYPE_ID, // 495
  SPV_OPERAND_TYPE_ID, // 496
  SPV_OPERAND_TYPE_ID, // 497
  SPV_OPERAND_TYPE_ID, // 498
  SPV_OPERAND_TYPE_ID, // 499
  SPV_OPERAND_TYPE_ID, // 500
  SPV_OPERAND_TYPE_ID, // 501
  SPV_OPERAND_TYPE_ID, // 502
  SPV_OPERAND_TYPE_ID, // 503
  SPV_OPERAND_TYPE_ID, // 504
  SPV_OPERAND_TYPE_ID, // 505
  SPV_OPERAND_TYPE_ID, // 506
  SPV_OPERAND_TYPE_ID, // 507
  SPV_OPERAND_TYPE_ID, // 508
  SPV_OPERAND_TYPE_ID, // 509
  SPV_OPERAND_TYPE_ID, // 510
  SPV_OPERAND_TYPE_ID, // 511
  SPV_OPERAND_TYPE_ID, // 512
  SPV_OPERAND_TYPE_ID, // 513
  SPV_OPERAND_TYPE_ID, // 514
  SPV_OPERAND_TYPE_ID, // 515
  SPV_OPERAND_TYPE_ID, // 516
  SPV_OPERAND_TYPE_ID, // 517
  SPV_OPERAND_TYPE_ID, // 518
  SPV_OPERAND_TYPE_ID, // 519
  SPV_OPERAND_TYPE_ID, // 520
  SPV_OPERAND_TYPE_ID, // 521
  SPV_OPERAND_TYPE_ID, // 522
  SPV_OPERAND_TYPE_ID, // 523
  SPV_OPERAND_TYPE_ID, // 524
  SPV_OPERAND_TYPE_ID, // 525
  SPV_OPERAND_TYPE_ID, // 526
  SPV_OPERAND_TYPE_ID, // 527
  SPV_OPERAND_TYPE_ID, // 528
  SPV_OPERAND_TYPE_ID, // 529
  SPV_OPERAND_TYPE_ID, // 530
  SPV_OPERAND_TYPE_ID, // 531
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 532
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 533
  SPV_OPERAND_TYPE_TYPE_ID, // 534
  SPV_OPERAND_TYPE_RESULT_ID, // 535
  SPV_OPERAND_TYPE_ID, // 536
  SPV_OPERAND_TYPE_ID, // 537
  SPV_OPERAND_TYPE_ID, // 538
  SPV_OPERAND_TYPE_ID, // 539
  SPV_OPERAND_TYPE_OPTIONAL_IMAGE, // 540
  SPV_OPERAND_TYPE_TYPE_ID, // 541
  SPV_OPERAND_TYPE_RESULT_ID, // 542
  SPV_OPERAND_TYPE_ID, // 543
  SPV_OPERAND_TYPE_ID, // 544
  SPV_OPERAND_TYPE_ID, // 545
  SPV_OPERAND_TYPE_ID, // 546
  SPV_OPERAND_TYPE_ID, // 547
  SPV_OPERAND_TYPE_ID, // 548
  SPV_OPERAND_TYPE_ID, // 549
  SPV_OPERAND_TYPE_ID, // 550
  SPV_OPERAND_TYPE_ID, // 551
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 552
  SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS, // 553
  SPV_OPERAND_TYPE_ID, // 554
  SPV_OPERAND_TYPE_ID, // 555
  SPV_OPERAND_TYPE_ID, // 556
  SPV_OPERAND_TYPE_ID, // 557
  SPV_OPERAND_TYPE_ID, // 558
  SPV_OPERAND_TYPE_ID, // 559
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 560
  SPV_OPERAND_TYPE_TYPE_ID, // 561
  SPV_OPERAND_TYPE_RESULT_ID, // 562
  SPV_OPERAND_TYPE_ID, // 563
  SPV_OPERAND_TYPE_ID, // 564
  SPV_OPERAND_TYPE_ID, // 565
  SPV_OPERAND_TYPE_ID, // 566
  SPV_OPERAND_TYPE_ID, // 567
  SPV_OPERAND_TYPE_ID, // 568
  SPV_OPERAND_TYPE_ID, // 569
  SPV_OPERAND_TYPE_ID, // 570
  SPV_OPERAND_TYPE_ID, // 571
  SPV_OPERAND_TYPE_ID, // 572
  SPV_OPERAND_TYPE_ID, // 573
  SPV_OPERAND_TYPE_ID, // 574
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 575
  SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS, // 576
  SPV_OPERAND_TYPE_ID, // 577
  SPV_OPERAND_TYPE_ID, // 578
  SPV_OPERAND_TYPE_ID, // 579
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 580
  SPV_OPERAND_TYPE_TYPE_ID, // 581
  SPV_OPERAND_TYPE_RESULT_ID, // 582
  SPV_OPERAND_TYPE_ID, // 583
  SPV_OPERAND_TYPE_ID, // 584
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 585
  SPV_OPERAND_TYPE_ID, // 586
  SPV_OPERAND_TYPE_ID, // 587
  SPV_OPERAND_TYPE_ID, // 588
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 589
  SPV_OPERAND_TYPE_ID, // 590
  SPV_OPERAND_TYPE_ID, // 591
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 592
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 593
  SPV_OPERAND_TYPE_ID, // 594
  SPV_OPERAND_TYPE_ID, // 595
  SPV_OPERAND_TYPE_ID, // 596
  SPV_OPERAND_TYPE_ID, // 597
  SPV_OPERAND_TYPE_ID, // 598
  SPV_OPERAND_TYPE_ID, // 599
  SPV_OPERAND_TYPE_ID, // 600
  SPV_OPERAND_TYPE_ID, // 601
  SPV_OPERAND_TYPE_ID, // 602
  SPV_OPERAND_TYPE_ID, // 603
  SPV_OPERAND_TYPE_ID, // 604
  SPV_OPERAND_TYPE_ID, // 605
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 606
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 607
  SPV_OPERAND_TYPE_ID, // 608
  SPV_OPERAND_TYPE_ID, // 609
  SPV_OPERAND_TYPE_ID, // 610
  SPV_OPERAND_TYPE_ID, // 611
  SPV_OPERAND_TYPE_ID, // 612
  SPV_OPERAND_TYPE_ID, // 613
  SPV_OPERAND_TYPE_ID, // 614
  SPV_OPERAND_TYPE_ID, // 615
  SPV_OPERAND_TYPE_ID, // 616
  SPV_OPERAND_TYPE_ID, // 617
  SPV_OPERAND_TYPE_ID, // 618
  SPV_OPERAND_TYPE_ID, // 619
  SPV_OPERAND_TYPE_ID, // 620
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 621
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 622
  SPV_OPERAND_TYPE_RESULT_ID, // 623
  SPV_OPERAND_TYPE_ID, // 624
  SPV_OPERAND_TYPE_SCOPE_ID, // 625
  SPV_OPERAND_TYPE_ID, // 626
  SPV_OPERAND_TYPE_ID, // 627
  SPV_OPERAND_TYPE_TYPE_ID, // 628
  SPV_OPERAND_TYPE_RESULT_ID, // 629
  SPV_OPERAND_TYPE_ID, // 630
  SPV_OPERAND_TYPE_ID, // 631
  SPV_OPERAND_TYPE_ID, // 632
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 633
  SPV_OPERAND_TYPE_ID, // 634
  SPV_OPERAND_TYPE_ID, // 635
  SPV_OPERAND_TYPE_ID, // 636
  SPV_OPERAND_TYPE_ID, // 637
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 638
  SPV_OPERAND_TYPE_TYPE_ID, // 639
  SPV_OPERAND_TYPE_RESULT_ID, // 640
  SPV_OPERAND_TYPE_ID, // 641
  SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE, // 642
  SPV_OPERAND_TYPE_ID, // 643
  SPV_OPERAND_TYPE_TYPE_ID, // 644
  SPV_OPERAND_TYPE_RESULT_ID, // 645
  SPV_OPERAND_TYPE_ID, // 646
  SPV_OPERAND_TYPE_ID, // 647
  SPV_OPERAND_TYPE_ID, // 648
  SPV_OPERAND_TYPE_MEMORY_ACCESS, // 649
  SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS, // 650
  SPV_OPERAND_TYPE_ID, // 651
  SPV_OPERAND_TYPE_ID, // 652
  SPV_OPERAND_TYPE_ID, // 653
  SPV_OPERAND_TYPE_MEMORY_ACCESS, // 654
  SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS, // 655
  SPV_OPERAND_TYPE_RESULT_ID, // 656
  SPV_OPERAND_TYPE_ID, // 657
  SPV_OPERAND_TYPE_ID, // 658
  SPV_OPERAND_TYPE_VARIABLE_ID, // 659
  SPV_OPERAND_TYPE_TYPE_ID, // 660
  SPV_OPERAND_TYPE_RESULT_ID, // 661
  SPV_OPERAND_TYPE_ID, // 662
  SPV_OPERAND_TYPE_ID, // 663
  SPV_OPERAND_TYPE_ID, // 664
  SPV_OPERAND_TYPE_ID, // 665
  SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS, // 666
  SPV_OPERAND_TYPE_ID, // 667
  SPV_OPERAND_TYPE_ID, // 668
  SPV_OPERAND_TYPE_ID, // 669
  SPV_OPERAND_TYPE_ID, // 670
  SPV_OPERAND_TYPE_ID, // 671
  SPV_OPERAND_TYPE_TYPE_ID, // 672
  SPV_OPERAND_TYPE_RESULT_ID, // 673
  SPV_OPERAND_TYPE_ID, // 674
  SPV_OPERAND_TYPE_ID, // 675
  SPV_OPERAND_TYPE_LITERAL_STRING, // 676
  SPV_OPERAND_TYPE_LITERAL_STRING, // 677
  SPV_OPERAND_TYPE_TYPE_ID, // 678
  SPV_OPERAND_TYPE_RESULT_ID, // 679
  SPV_OPERAND_TYPE_ID, // 680
  SPV_OPERAND_TYPE_ID, // 681
  SPV_OPERAND_TYPE_ID, // 682
  SPV_OPERAND_TYPE_ID, // 683
  SPV_OPERAND_TYPE_ID, // 684
  SPV_OPERAND_TYPE_ID, // 685
  SPV_OPERAND_TYPE_ID, // 686
  SPV_OPERAND_TYPE_TYPE_ID, // 687
  SPV_OPERAND_TYPE_RESULT_ID, // 688
  SPV_OPERAND_TYPE_ID, // 689
  SPV_OPERAND_TYPE_ID, // 690
  SPV_OPERAND_TYPE_ID, // 691
  SPV_OPERAND_TYPE_ID, // 692
  SPV_OPERAND_TYPE_ID, // 693
  SPV_OPERAND_TYPE_ID, // 694
  SPV_OPERAND_TYPE_ID, // 695
  SPV_OPERAND_TYPE_ID, // 696
  SPV_OPERAND_TYPE_TYPE_ID, // 697
  SPV_OPERAND_TYPE_RESULT_ID, // 698
  SPV_OPERAND_TYPE_ID, // 699
  SPV_OPERAND_TYPE_ID, // 700
  SPV_OPERAND_TYPE_ID, // 701
  SPV_OPERAND_TYPE_ID, // 702
  SPV_OPERAND_TYPE_ID, // 703
  SPV_OPERAND_TYPE_ID, // 704
  SPV_OPERAND_TYPE_ID, // 705
  SPV_OPERAND_TYPE_ID, // 706
  SPV_OPERAND_TYPE_ID, // 707
  SPV_OPERAND_TYPE_ID, // 708
  SPV_OPERAND_TYPE_ID, // 709
  SPV_OPERAND_TYPE_TYPE_ID, // 710
  SPV_OPERAND_TYPE_RESULT_ID, // 711
  SPV_OPERAND_TYPE_ID, // 712
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 713
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 714
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 715
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 716
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 717
  SPV_OPERAND_TYPE_TYPE_ID, // 718
  SPV_OPERAND_TYPE_RESULT_ID, // 719
  SPV_OPERAND_TYPE_ID, // 720
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 721
  SPV_OPERAND_TYPE_ID, // 722
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 723
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 724
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 725
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 726
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 727
  SPV_OPERAND_TYPE_TYPE_ID, // 728
  SPV_OPERAND_TYPE_RESULT_ID, // 729
  SPV_OPERAND_TYPE_ID, // 730
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 731
  SPV_OPERAND_TYPE_ID, // 732
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 733
  SPV_OPERAND_TYPE_RESULT_ID, // 734
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 735
  SPV_OPERAND_TYPE_RESULT_ID, // 736
  SPV_OPERAND_TYPE_ID, // 737
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 738
  SPV_OPERAND_TYPE_VARIABLE_ID, // 739
  SPV_OPERAND_TYPE_TYPE_ID, // 740
  SPV_OPERAND_TYPE_RESULT_ID, // 741
  SPV_OPERAND_TYPE_ID, // 742
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 743
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 744
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 745
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 746
  SPV_OPERAND_TYPE_ID, // 747
  SPV_OPERAND_TYPE_ID, // 748
  SPV_OPERAND_TYPE_ID, // 749
  SPV_OPERAND_TYPE_ID, // 750
  SPV_OPERAND_TYPE_ID, // 751
  SPV_OPERAND_TYPE_ID, // 752
  SPV_OPERAND_TYPE_ID, // 753
  SPV_OPERAND_TYPE_ID, // 754
  SPV_OPERAND_TYPE_ID, // 755
  SPV_OPERAND_TYPE_ID, // 756
  SPV_OPERAND_TYPE_ID, // 757
  SPV_OPERAND_TYPE_ID, // 758
  SPV_OPERAND_TYPE_ID, // 759
  SPV_OPERAND_TYPE_ID, // 760
  SPV_OPERAND_TYPE_ID, // 761
  SPV_OPERAND_TYPE_ID, // 762
  SPV_OPERAND_TYPE_ID, // 763
  SPV_OPERAND_TYPE_ID, // 764
  SPV_OPERAND_TYPE_ID, // 765
  SPV_OPERAND_TYPE_TYPE_ID, // 766
  SPV_OPERAND_TYPE_RESULT_ID, // 767
  SPV_OPERAND_TYPE_ID, // 768
  SPV_OPERAND_TYPE_ID, // 769
  SPV_OPERAND_TYPE_ID, // 770
  SPV_OPERAND_TYPE_ID, // 771
  SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS, // 772
  SPV_OPERAND_TYPE_ID, // 773
  SPV_OPERAND_TYPE_EXECUTION_MODEL, // 774
  SPV_OPERAND_TYPE_ID, // 775
  SPV_OPERAND_TYPE_LITERAL_STRING, // 776
  SPV_OPERAND_TYPE_VARIABLE_ID, // 777
  SPV_OPERAND_TYPE_ID, // 778
  SPV_OPERAND_TYPE_CAPABILITY, // 779
  SPV_OPERAND_TYPE_TYPE_ID, // 780
  SPV_OPERAND_TYPE_RESULT_ID, // 781
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 782
  SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER, // 783
  SPV_OPERAND_TYPE_TYPE_ID, // 784
  SPV_OPERAND_TYPE_RESULT_ID, // 785
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 786
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 787
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 788
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 789
  SPV_OPERAND_TYPE_TYPE_ID, // 790
  SPV_OPERAND_TYPE_RESULT_ID, // 791
  SPV_OPERAND_TYPE_VARIABLE_CAPABILITY, // 792
  SPV_OPERAND_TYPE_TYPE_ID, // 793
  SPV_OPERAND_TYPE_RESULT_ID, // 794
  SPV_OPERAND_TYPE_ID, // 795
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 796
  SPV_OPERAND_TYPE_ID, // 797
  SPV_OPERAND_TYPE_ID, // 798
  SPV_OPERAND_TYPE_ID, // 799
  SPV_OPERAND_TYPE_ID, // 800
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 801
  SPV_OPERAND_TYPE_ID, // 802
  SPV_OPERAND_TYPE_ID, // 803
  SPV_OPERAND_TYPE_ID, // 804
  SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING, // 805
  SPV_OPERAND_TYPE_ID, // 806
  SPV_OPERAND_TYPE_STORAGE_CLASS, // 807
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 808
  SPV_OPERAND_TYPE_ID, // 809
  SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER, // 810
  SPV_OPERAND_TYPE_ID, // 811
  SPV_OPERAND_TYPE_ID, // 812
  SPV_OPERAND_TYPE_ID, // 813
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 814
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 815
  SPV_OPERAND_TYPE_ID, // 816
  SPV_OPERAND_TYPE_ID, // 817
  SPV_OPERAND_TYPE_ID, // 818
  SPV_OPERAND_TYPE_ID, // 819
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 820
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 821
  SPV_OPERAND_TYPE_ID, // 822
  SPV_OPERAND_TYPE_ID, // 823
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 824
  SPV_OPERAND_TYPE_VARIABLE_ID, // 825
  SPV_OPERAND_TYPE_ID, // 826
  SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE, // 827
  SPV_OPERAND_TYPE_ID, // 828
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 829
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 830
  SPV_OPERAND_TYPE_ID, // 831
  SPV_OPERAND_TYPE_ID, // 832
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 833
  SPV_OPERAND_TYPE_VARIABLE_ID, // 834
  SPV_OPERAND_TYPE_ID, // 835
  SPV_OPERAND_TYPE_ID, // 836
  SPV_OPERAND_TYPE_ID, // 837
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 838
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 839
  SPV_OPERAND_TYPE_ID, // 840
  SPV_OPERAND_TYPE_ID, // 841
  SPV_OPERAND_TYPE_ID, // 842
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 843
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 844
  SPV_OPERAND_TYPE_ID, // 845
  SPV_OPERAND_TYPE_ID, // 846
  SPV_OPERAND_TYPE_ID, // 847
  SPV_OPERAND_TYPE_ID, // 848
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 849
  SPV_OPERAND_TYPE_ID, // 850
  SPV_OPERAND_TYPE_ID, // 851
  SPV_OPERAND_TYPE_ID, // 852
  SPV_OPERAND_TYPE_ID, // 853
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 854
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 855
  SPV_OPERAND_TYPE_ID, // 856
  SPV_OPERAND_TYPE_ID, // 857
  SPV_OPERAND_TYPE_ID, // 858
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 859
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 860
  SPV_OPERAND_TYPE_ID, // 861
  SPV_OPERAND_TYPE_ID, // 862
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 863
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 864
  SPV_OPERAND_TYPE_VARIABLE_ID, // 865
  SPV_OPERAND_TYPE_ID, // 866
  SPV_OPERAND_TYPE_ID, // 867
  SPV_OPERAND_TYPE_ID, // 868
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 869
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 870
  SPV_OPERAND_TYPE_ID, // 871
  SPV_OPERAND_TYPE_ID, // 872
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 873
  SPV_OPERAND_TYPE_ID, // 874
  SPV_OPERAND_TYPE_ID, // 875
  SPV_OPERAND_TYPE_ID, // 876
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 877
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 878
  SPV_OPERAND_TYPE_ID, // 879
  SPV_OPERAND_TYPE_ID, // 880
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 881
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 882
  SPV_OPERAND_TYPE_ID, // 883
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 884
  SPV_OPERAND_TYPE_ID, // 885
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 886
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 887
  SPV_OPERAND_TYPE_ID, // 888
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 889
  SPV_OPERAND_TYPE_ID, // 890
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 891
  SPV_OPERAND_TYPE_ID, // 892
  SPV_OPERAND_TYPE_ID, // 893
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 894
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 895
  SPV_OPERAND_TYPE_ID, // 896
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 897
  SPV_OPERAND_TYPE_ID, // 898
  SPV_OPERAND_TYPE_ID, // 899
  SPV_OPERAND_TYPE_ID, // 900
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 901
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 902
  SPV_OPERAND_TYPE_ID, // 903
  SPV_OPERAND_TYPE_OPTIONAL_LITERAL_INTEGER, // 904
  SPV_OPERAND_TYPE_DEBUG_OPERATION, // 905
  SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER, // 906
  SPV_OPERAND_TYPE_ID, // 907
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 908
  SPV_OPERAND_TYPE_ID, // 909
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 910
  SPV_OPERAND_TYPE_ID, // 911
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 912
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 913
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 914
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 915
  SPV_OPERAND_TYPE_ID, // 916
  SPV_OPERAND_TYPE_ID, // 917
  SPV_OPERAND_TYPE_ID, // 918
  SPV_OPERAND_TYPE_ID, // 919
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 920
  SPV_OPERAND_TYPE_ID, // 921
  SPV_OPERAND_TYPE_ID, // 922
  SPV_OPERAND_TYPE_ID, // 923
  SPV_OPERAND_TYPE_ID, // 924
  SPV_OPERAND_TYPE_ID, // 925
  SPV_OPERAND_TYPE_ID, // 926
  SPV_OPERAND_TYPE_ID, // 927
  SPV_OPERAND_TYPE_ID, // 928
  SPV_OPERAND_TYPE_VARIABLE_ID, // 929
  SPV_OPERAND_TYPE_ID, // 930
  SPV_OPERAND_TYPE_ID, // 931
  SPV_OPERAND_TYPE_ID, // 932
  SPV_OPERAND_TYPE_ID, // 933
  SPV_OPERAND_TYPE_ID, // 934
  SPV_OPERAND_TYPE_ID, // 935
  SPV_OPERAND_TYPE_ID, // 936
  SPV_OPERAND_TYPE_ID, // 937
  SPV_OPERAND_TYPE_ID, // 938
  SPV_OPERAND_TYPE_VARIABLE_ID, // 939
  SPV_OPERAND_TYPE_ID, // 940
  SPV_OPERAND_TYPE_ID, // 941
  SPV_OPERAND_TYPE_ID, // 942
  SPV_OPERAND_TYPE_ID, // 943
  SPV_OPERAND_TYPE_ID, // 944
  SPV_OPERAND_TYPE_ID, // 945
  SPV_OPERAND_TYPE_ID, // 946
  SPV_OPERAND_TYPE_ID, // 947
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 948
  SPV_OPERAND_TYPE_ID, // 949
  SPV_OPERAND_TYPE_ID, // 950
  SPV_OPERAND_TYPE_ID, // 951
  SPV_OPERAND_TYPE_ID, // 952
  SPV_OPERAND_TYPE_VARIABLE_ID, // 953
  SPV_OPERAND_TYPE_ID, // 954
  SPV_OPERAND_TYPE_ID, // 955
  SPV_OPERAND_TYPE_ID, // 956
  SPV_OPERAND_TYPE_ID, // 957
  SPV_OPERAND_TYPE_ID, // 958
  SPV_OPERAND_TYPE_ID, // 959
  SPV_OPERAND_TYPE_ID, // 960
  SPV_OPERAND_TYPE_ID, // 961
  SPV_OPERAND_TYPE_ID, // 962
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 963
  SPV_OPERAND_TYPE_ID, // 964
  SPV_OPERAND_TYPE_ID, // 965
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 966
  SPV_OPERAND_TYPE_ID, // 967
  SPV_OPERAND_TYPE_ID, // 968
  SPV_OPERAND_TYPE_ID, // 969
  SPV_OPERAND_TYPE_ID, // 970
  SPV_OPERAND_TYPE_ID, // 971
  SPV_OPERAND_TYPE_ID, // 972
  SPV_OPERAND_TYPE_ID, // 973
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 974
  SPV_OPERAND_TYPE_ID, // 975
  SPV_OPERAND_TYPE_ID, // 976
  SPV_OPERAND_TYPE_ID, // 977
  SPV_OPERAND_TYPE_VARIABLE_ID, // 978
  SPV_OPERAND_TYPE_ID, // 979
  SPV_OPERAND_TYPE_ID, // 980
  SPV_OPERAND_TYPE_ID, // 981
  SPV_OPERAND_TYPE_ID, // 982
  SPV_OPERAND_TYPE_ID, // 983
  SPV_OPERAND_TYPE_ID, // 984
  SPV_OPERAND_TYPE_ID, // 985
  SPV_OPERAND_TYPE_ID, // 986
  SPV_OPERAND_TYPE_ID, // 987
  SPV_OPERAND_TYPE_ID, // 988
  SPV_OPERAND_TYPE_ID, // 989
  SPV_OPERAND_TYPE_ID, // 990
  SPV_OPERAND_TYPE_ID, // 991
  SPV_OPERAND_TYPE_ID, // 992
  SPV_OPERAND_TYPE_ID, // 993
  SPV_OPERAND_TYPE_ID, // 994
  SPV_OPERAND_TYPE_ID, // 995
  SPV_OPERAND_TYPE_ID, // 996
  SPV_OPERAND_TYPE_ID, // 997
  SPV_OPERAND_TYPE_ID, // 998
  SPV_OPERAND_TYPE_ID, // 999
  SPV_OPERAND_TYPE_ID, // 1000
  SPV_OPERAND_TYPE_ID, // 1001
  SPV_OPERAND_TYPE_ID, // 1002
  SPV_OPERAND_TYPE_ID, // 1003
  SPV_OPERAND_TYPE_ID, // 1004
  SPV_OPERAND_TYPE_ID, // 1005
  SPV_OPERAND_TYPE_ID, // 1006
  SPV_OPERAND_TYPE_ID, // 1007
  SPV_OPERAND_TYPE_ID, // 1008
  SPV_OPERAND_TYPE_ID, // 1009
  SPV_OPERAND_TYPE_ID, // 1010
  SPV_OPERAND_TYPE_ID, // 1011
  SPV_OPERAND_TYPE_ID, // 1012
  SPV_OPERAND_TYPE_ID, // 1013
  SPV_OPERAND_TYPE_ID, // 1014
  SPV_OPERAND_TYPE_ID, // 1015
  SPV_OPERAND_TYPE_ID, // 1016
  SPV_OPERAND_TYPE_ID, // 1017
  SPV_OPERAND_TYPE_ID, // 1018
  SPV_OPERAND_TYPE_ID, // 1019
  SPV_OPERAND_TYPE_ID, // 1020
  SPV_OPERAND_TYPE_ID, // 1021
  SPV_OPERAND_TYPE_ID, // 1022
  SPV_OPERAND_TYPE_ID, // 1023
  SPV_OPERAND_TYPE_ID, // 1024
  SPV_OPERAND_TYPE_ID, // 1025
  SPV_OPERAND_TYPE_ID, // 1026
  SPV_OPERAND_TYPE_ID, // 1027
  SPV_OPERAND_TYPE_ID, // 1028
  SPV_OPERAND_TYPE_ID, // 1029
  SPV_OPERAND_TYPE_ID, // 1030
  SPV_OPERAND_TYPE_ID, // 1031
  SPV_OPERAND_TYPE_ID, // 1032
  SPV_OPERAND_TYPE_ID, // 1033
  SPV_OPERAND_TYPE_ID, // 1034
  SPV_OPERAND_TYPE_ID, // 1035
  SPV_OPERAND_TYPE_ID, // 1036
  SPV_OPERAND_TYPE_ID, // 1037
  SPV_OPERAND_TYPE_ID, // 1038
  SPV_OPERAND_TYPE_ID, // 1039
  SPV_OPERAND_TYPE_ID, // 1040
  SPV_OPERAND_TYPE_ID, // 1041
  SPV_OPERAND_TYPE_ID, // 1042
  SPV_OPERAND_TYPE_ID, // 1043
  SPV_OPERAND_TYPE_ID, // 1044
  SPV_OPERAND_TYPE_ID, // 1045
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1046
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1047
  SPV_OPERAND_TYPE_ID, // 1048
  SPV_OPERAND_TYPE_SOURCE_LANGUAGE, // 1049
  SPV_OPERAND_TYPE_ID, // 1050
  SPV_OPERAND_TYPE_ID, // 1051
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING, // 1052
  SPV_OPERAND_TYPE_ID, // 1053
  SPV_OPERAND_TYPE_STORAGE_CLASS, // 1054
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1055
  SPV_OPERAND_TYPE_ID, // 1056
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER, // 1057
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1058
  SPV_OPERAND_TYPE_ID, // 1059
  SPV_OPERAND_TYPE_VARIABLE_ID, // 1060
  SPV_OPERAND_TYPE_ID, // 1061
  SPV_OPERAND_TYPE_ID, // 1062
  SPV_OPERAND_TYPE_ID, // 1063
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1064
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1065
  SPV_OPERAND_TYPE_ID, // 1066
  SPV_OPERAND_TYPE_ID, // 1067
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1068
  SPV_OPERAND_TYPE_VARIABLE_ID, // 1069
  SPV_OPERAND_TYPE_ID, // 1070
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE, // 1071
  SPV_OPERAND_TYPE_ID, // 1072
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1073
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1074
  SPV_OPERAND_TYPE_ID, // 1075
  SPV_OPERAND_TYPE_ID, // 1076
  SPV_OPERAND_TYPE_ID, // 1077
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1078
  SPV_OPERAND_TYPE_VARIABLE_ID, // 1079
  SPV_OPERAND_TYPE_ID, // 1080
  SPV_OPERAND_TYPE_ID, // 1081
  SPV_OPERAND_TYPE_ID, // 1082
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1083
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1084
  SPV_OPERAND_TYPE_ID, // 1085
  SPV_OPERAND_TYPE_ID, // 1086
  SPV_OPERAND_TYPE_ID, // 1087
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1088
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 1089
  SPV_OPERAND_TYPE_ID, // 1090
  SPV_OPERAND_TYPE_ID, // 1091
  SPV_OPERAND_TYPE_ID, // 1092
  SPV_OPERAND_TYPE_ID, // 1093
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1094
  SPV_OPERAND_TYPE_ID, // 1095
  SPV_OPERAND_TYPE_ID, // 1096
  SPV_OPERAND_TYPE_ID, // 1097
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1098
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1099
  SPV_OPERAND_TYPE_ID, // 1100
  SPV_OPERAND_TYPE_ID, // 1101
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1102
  SPV_OPERAND_TYPE_ID, // 1103
  SPV_OPERAND_TYPE_ID, // 1104
  SPV_OPERAND_TYPE_ID, // 1105
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1106
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1107
  SPV_OPERAND_TYPE_ID, // 1108
  SPV_OPERAND_TYPE_ID, // 1109
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1110
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1111
  SPV_OPERAND_TYPE_ID, // 1112
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 1113
  SPV_OPERAND_TYPE_ID, // 1114
  SPV_OPERAND_TYPE_ID, // 1115
  SPV_OPERAND_TYPE_ID, // 1116
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1117
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1118
  SPV_OPERAND_TYPE_ID, // 1119
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1120
  SPV_OPERAND_TYPE_OPTIONAL_LITERAL_INTEGER, // 1121
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION, // 1122
  SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER, // 1123
  SPV_OPERAND_TYPE_ID, // 1124
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY, // 1125
  SPV_OPERAND_TYPE_ID, // 1126
  SPV_OPERAND_TYPE_ID, // 1127
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1128
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1129
  SPV_OPERAND_TYPE_ID, // 1130
  SPV_OPERAND_TYPE_ID, // 1131
  SPV_OPERAND_TYPE_ID, // 1132
  SPV_OPERAND_TYPE_ID, // 1133
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1134
  SPV_OPERAND_TYPE_ID, // 1135
  SPV_OPERAND_TYPE_ID, // 1136
  SPV_OPERAND_TYPE_ID, // 1137
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1138
  SPV_OPERAND_TYPE_ID, // 1139
  SPV_OPERAND_TYPE_ID, // 1140
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1141
  SPV_OPERAND_TYPE_ID, // 1142
  SPV_OPERAND_TYPE_ID, // 1143
  SPV_OPERAND_TYPE_ID, // 1144
  SPV_OPERAND_TYPE_FP_ROUNDING_MODE, // 1145
};
