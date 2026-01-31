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
    default: break;
  }
  return {};
}

// Extension names and values, ordered by name
// The fields in order are:
//   name, indexing into kStrings
//   enum value
static const std::array<NameValue,187> kExtensionNames{{
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
static const std::array<OperandDesc, 1203> kOperandsByValue{{
  {0,IR(0, 0),IR(5454, 9)/* ReadOnly */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {1,IR(0, 0),IR(5470, 10)/* WriteOnly */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {2,IR(0, 0),IR(5480, 10)/* ReadWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {0,IR(0, 0),IR(5490, 8)/* Logical */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {1,IR(0, 0),IR(5498, 11)/* Physical32 */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {2,IR(0, 0),IR(5519, 11)/* Physical64 */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {5348,IR(0, 0),IR(5530, 24)/* PhysicalStorageBuffer64 */,IR(0, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {0,IR(0, 0),IR(5612, 9)/* Position */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {1,IR(0, 0),IR(5628, 10)/* PointSize */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {3,IR(0, 0),IR(5638, 13)/* ClipDistance */,IR(0, 0),IR(4, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4,IR(0, 0),IR(5651, 13)/* CullDistance */,IR(0, 0),IR(5, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5,IR(0, 0),IR(5664, 9)/* VertexId */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {6,IR(0, 0),IR(5673, 11)/* InstanceId */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {7,IR(0, 0),IR(5684, 12)/* PrimitiveId */,IR(0, 0),IR(6, 6),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {8,IR(0, 0),IR(5774, 13)/* InvocationId */,IR(0, 0),IR(12, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {9,IR(0, 0),IR(5787, 6)/* Layer */,IR(0, 0),IR(14, 5),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {10,IR(0, 0),IR(5833, 14)/* ViewportIndex */,IR(0, 0),IR(19, 5),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {11,IR(0, 0),IR(5881, 15)/* TessLevelOuter */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {12,IR(0, 0),IR(5896, 15)/* TessLevelInner */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {13,IR(0, 0),IR(5911, 10)/* TessCoord */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {14,IR(0, 0),IR(5921, 14)/* PatchVertices */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {15,IR(0, 0),IR(5935, 10)/* FragCoord */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {16,IR(0, 0),IR(5945, 11)/* PointCoord */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {17,IR(0, 0),IR(5956, 12)/* FrontFacing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {18,IR(0, 0),IR(5968, 9)/* SampleId */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {19,IR(0, 0),IR(5995, 15)/* SamplePosition */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {20,IR(0, 0),IR(6010, 11)/* SampleMask */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {22,IR(0, 0),IR(6021, 10)/* FragDepth */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {23,IR(0, 0),IR(6031, 17)/* HelperInvocation */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {24,IR(0, 0),IR(6048, 14)/* NumWorkgroups */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {25,IR(0, 0),IR(6062, 14)/* WorkgroupSize */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {26,IR(0, 0),IR(6076, 12)/* WorkgroupId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {27,IR(0, 0),IR(6088, 18)/* LocalInvocationId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {28,IR(0, 0),IR(6106, 19)/* GlobalInvocationId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {29,IR(0, 0),IR(6125, 21)/* LocalInvocationIndex */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {30,IR(0, 0),IR(6146, 8)/* WorkDim */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {31,IR(0, 0),IR(6154, 11)/* GlobalSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {32,IR(0, 0),IR(6165, 22)/* EnqueuedWorkgroupSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {33,IR(0, 0),IR(6187, 13)/* GlobalOffset */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {34,IR(0, 0),IR(6200, 15)/* GlobalLinearId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {36,IR(0, 0),IR(6215, 13)/* SubgroupSize */,IR(0, 0),IR(26, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {37,IR(0, 0),IR(6262, 16)/* SubgroupMaxSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {38,IR(0, 0),IR(6278, 13)/* NumSubgroups */,IR(0, 0),IR(29, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {39,IR(0, 0),IR(6291, 21)/* NumEnqueuedSubgroups */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {40,IR(0, 0),IR(6312, 11)/* SubgroupId */,IR(0, 0),IR(29, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {41,IR(0, 0),IR(6323, 26)/* SubgroupLocalInvocationId */,IR(0, 0),IR(26, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {42,IR(0, 0),IR(6349, 12)/* VertexIndex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {43,IR(0, 0),IR(6361, 14)/* InstanceIndex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4160,IR(0, 0),IR(6375, 10)/* CoreIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4161,IR(0, 0),IR(6401, 13)/* CoreCountARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4162,IR(0, 0),IR(6414, 13)/* CoreMaxIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4163,IR(0, 0),IR(6427, 10)/* WarpIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4164,IR(0, 0),IR(6437, 13)/* WarpMaxIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4416,IR(0, 0),IR(6450, 15)/* SubgroupEqMask */,IR(1, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4417,IR(0, 0),IR(6505, 15)/* SubgroupGeMask */,IR(2, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4418,IR(0, 0),IR(6538, 15)/* SubgroupGtMask */,IR(3, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4419,IR(0, 0),IR(6571, 15)/* SubgroupLeMask */,IR(4, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4420,IR(0, 0),IR(6604, 15)/* SubgroupLtMask */,IR(5, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4424,IR(0, 0),IR(6637, 11)/* BaseVertex */,IR(0, 0),IR(34, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4425,IR(0, 0),IR(6663, 13)/* BaseInstance */,IR(0, 0),IR(34, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4426,IR(0, 0),IR(6676, 10)/* DrawIndex */,IR(0, 0),IR(35, 3),IR(4, 3),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4432,IR(0, 0),IR(6686, 24)/* PrimitiveShadingRateKHR */,IR(0, 0),IR(38, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4438,IR(0, 0),IR(6733, 12)/* DeviceIndex */,IR(0, 0),IR(39, 1),IR(8, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4440,IR(0, 0),IR(6757, 10)/* ViewIndex */,IR(0, 0),IR(40, 1),IR(9, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4444,IR(0, 0),IR(6777, 15)/* ShadingRateKHR */,IR(0, 0),IR(38, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4492,IR(0, 0),IR(6792, 15)/* TileOffsetQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4493,IR(0, 0),IR(6823, 18)/* TileDimensionQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4494,IR(0, 0),IR(6841, 18)/* TileApronSizeQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4992,IR(0, 0),IR(6859, 20)/* BaryCoordNoPerspAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4993,IR(0, 0),IR(6879, 28)/* BaryCoordNoPerspCentroidAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4994,IR(0, 0),IR(6907, 26)/* BaryCoordNoPerspSampleAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4995,IR(0, 0),IR(6933, 19)/* BaryCoordSmoothAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4996,IR(0, 0),IR(6952, 27)/* BaryCoordSmoothCentroidAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4997,IR(0, 0),IR(6979, 25)/* BaryCoordSmoothSampleAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4998,IR(0, 0),IR(7004, 22)/* BaryCoordPullModelAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5014,IR(0, 0),IR(7026, 18)/* FragStencilRefEXT */,IR(0, 0),IR(42, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5021,IR(0, 0),IR(7061, 29)/* RemainingRecursionLevelsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5073,IR(0, 0),IR(7108, 16)/* ShaderIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5122,IR(0, 0),IR(7124, 15)/* SamplerHeapEXT */,IR(0, 0),IR(44, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5123,IR(0, 0),IR(7157, 16)/* ResourceHeapEXT */,IR(0, 0),IR(44, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5253,IR(0, 0),IR(7173, 15)/* ViewportMaskNV */,IR(0, 0),IR(45, 2),IR(12, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5257,IR(0, 0),IR(7209, 20)/* SecondaryPositionNV */,IR(0, 0),IR(47, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5258,IR(0, 0),IR(7248, 24)/* SecondaryViewportMaskNV */,IR(0, 0),IR(47, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5261,IR(0, 0),IR(7272, 18)/* PositionPerViewNV */,IR(0, 0),IR(48, 2),IR(15, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5262,IR(0, 0),IR(7310, 22)/* ViewportMaskPerViewNV */,IR(0, 0),IR(48, 2),IR(15, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5264,IR(0, 0),IR(7332, 16)/* FullyCoveredEXT */,IR(0, 0),IR(50, 1),IR(17, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5274,IR(0, 0),IR(7372, 12)/* TaskCountNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5275,IR(0, 0),IR(7384, 17)/* PrimitiveCountNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5276,IR(0, 0),IR(7401, 19)/* PrimitiveIndicesNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5277,IR(0, 0),IR(7420, 22)/* ClipDistancePerViewNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5278,IR(0, 0),IR(7442, 22)/* CullDistancePerViewNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5279,IR(0, 0),IR(7464, 15)/* LayerPerViewNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5280,IR(0, 0),IR(7479, 16)/* MeshViewCountNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5281,IR(0, 0),IR(7495, 18)/* MeshViewIndicesNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5286,IR(0, 0),IR(7513, 13)/* BaryCoordKHR */,IR(6, 1),IR(52, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5287,IR(0, 0),IR(7561, 20)/* BaryCoordNoPerspKHR */,IR(7, 1),IR(52, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5292,IR(0, 0),IR(7600, 12)/* FragSizeEXT */,IR(8, 1),IR(53, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5293,IR(0, 0),IR(7646, 23)/* FragInvocationCountEXT */,IR(9, 1),IR(53, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5294,IR(0, 0),IR(7691, 25)/* PrimitivePointIndicesEXT */,IR(0, 0),IR(54, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5295,IR(0, 0),IR(7716, 24)/* PrimitiveLineIndicesEXT */,IR(0, 0),IR(54, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5296,IR(0, 0),IR(7740, 28)/* PrimitiveTriangleIndicesEXT */,IR(0, 0),IR(54, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5299,IR(0, 0),IR(7768, 17)/* CullPrimitiveEXT */,IR(0, 0),IR(54, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5319,IR(0, 0),IR(7785, 12)/* LaunchIdKHR */,IR(10, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5320,IR(0, 0),IR(7808, 14)/* LaunchSizeKHR */,IR(11, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5321,IR(0, 0),IR(7835, 18)/* WorldRayOriginKHR */,IR(12, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5322,IR(0, 0),IR(7870, 21)/* WorldRayDirectionKHR */,IR(13, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5323,IR(0, 0),IR(7911, 19)/* ObjectRayOriginKHR */,IR(14, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5324,IR(0, 0),IR(7948, 22)/* ObjectRayDirectionKHR */,IR(15, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5325,IR(0, 0),IR(7991, 11)/* RayTminKHR */,IR(16, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5326,IR(0, 0),IR(8012, 11)/* RayTmaxKHR */,IR(17, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5327,IR(0, 0),IR(8033, 23)/* InstanceCustomIndexKHR */,IR(18, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5330,IR(0, 0),IR(8078, 17)/* ObjectToWorldKHR */,IR(19, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5331,IR(0, 0),IR(8111, 17)/* WorldToObjectKHR */,IR(20, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5332,IR(0, 0),IR(8144, 7)/* HitTNV */,IR(0, 0),IR(57, 1),IR(26, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5333,IR(0, 0),IR(8151, 11)/* HitKindKHR */,IR(21, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5334,IR(0, 0),IR(8172, 17)/* CurrentRayTimeNV */,IR(0, 0),IR(58, 1),IR(27, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5335,IR(0, 0),IR(8212, 30)/* HitTriangleVertexPositionsKHR */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5337,IR(0, 0),IR(8269, 34)/* HitMicroTriangleVertexPositionsNV */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5344,IR(0, 0),IR(8336, 37)/* HitMicroTriangleVertexBarycentricsNV */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5351,IR(0, 0),IR(8373, 20)/* IncomingRayFlagsKHR */,IR(22, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5352,IR(0, 0),IR(8412, 20)/* RayGeometryIndexKHR */,IR(0, 0),IR(61, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5359,IR(0, 0),IR(8432, 14)/* HitIsSphereNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5360,IR(0, 0),IR(8474, 11)/* HitIsLSSNV */,IR(0, 0),IR(63, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5361,IR(0, 0),IR(8524, 20)/* HitSpherePositionNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5374,IR(0, 0),IR(8544, 13)/* WarpsPerSMNV */,IR(0, 0),IR(64, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5375,IR(0, 0),IR(8576, 10)/* SMCountNV */,IR(0, 0),IR(64, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5376,IR(0, 0),IR(8586, 9)/* WarpIDNV */,IR(0, 0),IR(64, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5377,IR(0, 0),IR(8595, 7)/* SMIDNV */,IR(0, 0),IR(64, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5396,IR(0, 0),IR(8602, 18)/* HitLSSPositionsNV */,IR(0, 0),IR(63, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5405,IR(0, 0),IR(8620, 34)/* HitKindFrontFacingMicroTriangleNV */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5406,IR(0, 0),IR(8654, 33)/* HitKindBackFacingMicroTriangleNV */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5420,IR(0, 0),IR(8687, 18)/* HitSphereRadiusNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5421,IR(0, 0),IR(8705, 14)/* HitLSSRadiiNV */,IR(0, 0),IR(63, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5436,IR(0, 0),IR(8719, 12)/* ClusterIDNV */,IR(0, 0),IR(65, 1),IR(31, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {6021,IR(0, 0),IR(8772, 12)/* CullMaskKHR */,IR(0, 0),IR(66, 1),IR(32, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {0,IR(0, 0),IR(8799, 7)/* Matrix */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {1,IR(0, 0),IR(5621, 7)/* Shader */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {2,IR(0, 0),IR(5696, 9)/* Geometry */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {3,IR(0, 0),IR(5705, 13)/* Tessellation */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4,IR(0, 0),IR(5509, 10)/* Addresses */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5,IR(0, 0),IR(8806, 8)/* Linkage */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6,IR(0, 0),IR(5463, 7)/* Kernel */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {7,IR(0, 0),IR(8814, 9)/* Vector16 */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {8,IR(0, 0),IR(8823, 14)/* Float16Buffer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {9,IR(0, 0),IR(8837, 8)/* Float16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {10,IR(0, 0),IR(8845, 8)/* Float64 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {11,IR(0, 0),IR(8853, 6)/* Int64 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {12,IR(0, 0),IR(8859, 13)/* Int64Atomics */,IR(0, 0),IR(68, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {13,IR(0, 0),IR(8872, 11)/* ImageBasic */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {14,IR(0, 0),IR(8883, 15)/* ImageReadWrite */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {15,IR(0, 0),IR(8898, 12)/* ImageMipmap */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {17,IR(0, 0),IR(8910, 6)/* Pipes */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {18,IR(0, 0),IR(8916, 7)/* Groups */,IR(0, 0),IR(1, 0),IR(33, 1),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {19,IR(0, 0),IR(8923, 14)/* DeviceEnqueue */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {20,IR(0, 0),IR(8937, 15)/* LiteralSampler */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {21,IR(0, 0),IR(8952, 14)/* AtomicStorage */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {22,IR(0, 0),IR(8966, 6)/* Int16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {23,IR(0, 0),IR(8972, 22)/* TessellationPointSize */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {24,IR(0, 0),IR(8994, 18)/* GeometryPointSize */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {25,IR(0, 0),IR(9012, 20)/* ImageGatherExtended */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {27,IR(0, 0),IR(9032, 24)/* StorageImageMultisample */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {28,IR(0, 0),IR(9056, 34)/* UniformBufferArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {29,IR(0, 0),IR(9090, 33)/* SampledImageArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {30,IR(0, 0),IR(9123, 34)/* StorageBufferArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {31,IR(0, 0),IR(9157, 33)/* StorageImageArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {32,IR(0, 0),IR(5638, 13)/* ClipDistance */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {33,IR(0, 0),IR(5651, 13)/* CullDistance */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {34,IR(0, 0),IR(9190, 15)/* ImageCubeArray */,IR(0, 0),IR(71, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {35,IR(0, 0),IR(5977, 18)/* SampleRateShading */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {36,IR(0, 0),IR(9222, 10)/* ImageRect */,IR(0, 0),IR(72, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {37,IR(0, 0),IR(9232, 12)/* SampledRect */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {38,IR(0, 0),IR(9244, 15)/* GenericPointer */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {39,IR(0, 0),IR(9259, 5)/* Int8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {40,IR(0, 0),IR(9264, 16)/* InputAttachment */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {41,IR(0, 0),IR(9280, 16)/* SparseResidency */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {42,IR(0, 0),IR(9296, 7)/* MinLod */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {43,IR(0, 0),IR(9303, 10)/* Sampled1D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {44,IR(0, 0),IR(9313, 8)/* Image1D */,IR(0, 0),IR(73, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {45,IR(0, 0),IR(9205, 17)/* SampledCubeArray */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {46,IR(0, 0),IR(9321, 14)/* SampledBuffer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {47,IR(0, 0),IR(9335, 12)/* ImageBuffer */,IR(0, 0),IR(74, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {48,IR(0, 0),IR(9347, 13)/* ImageMSArray */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {49,IR(0, 0),IR(9360, 28)/* StorageImageExtendedFormats */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {50,IR(0, 0),IR(9388, 11)/* ImageQuery */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {51,IR(0, 0),IR(9399, 18)/* DerivativeControl */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {52,IR(0, 0),IR(9417, 22)/* InterpolationFunction */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {53,IR(0, 0),IR(9439, 18)/* TransformFeedback */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {54,IR(0, 0),IR(9457, 16)/* GeometryStreams */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {55,IR(0, 0),IR(9473, 30)/* StorageImageReadWithoutFormat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {56,IR(0, 0),IR(9503, 31)/* StorageImageWriteWithoutFormat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {57,IR(0, 0),IR(5847, 14)/* MultiViewport */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {58,IR(0, 0),IR(9534, 17)/* SubgroupDispatch */,IR(0, 0),IR(75, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {59,IR(0, 0),IR(9551, 13)/* NamedBarrier */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {60,IR(0, 0),IR(9564, 12)/* PipeStorage */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {61,IR(0, 0),IR(6228, 16)/* GroupNonUniform */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {62,IR(0, 0),IR(9576, 20)/* GroupNonUniformVote */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {63,IR(0, 0),IR(9596, 26)/* GroupNonUniformArithmetic */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {64,IR(0, 0),IR(6483, 22)/* GroupNonUniformBallot */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {65,IR(0, 0),IR(9622, 23)/* GroupNonUniformShuffle */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {66,IR(0, 0),IR(9645, 31)/* GroupNonUniformShuffleRelative */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {67,IR(0, 0),IR(9676, 25)/* GroupNonUniformClustered */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {68,IR(0, 0),IR(9701, 20)/* GroupNonUniformQuad */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {69,IR(0, 0),IR(5793, 12)/* ShaderLayer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {70,IR(0, 0),IR(5861, 20)/* ShaderViewportIndex */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {71,IR(0, 0),IR(9721, 18)/* UniformDecoration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4165,IR(0, 0),IR(6385, 16)/* CoreBuiltinsARM */,IR(0, 0),IR(1, 0),IR(34, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4166,IR(0, 0),IR(9739, 28)/* TileImageColorReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4167,IR(0, 0),IR(9767, 28)/* TileImageDepthReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4168,IR(0, 0),IR(9795, 30)/* TileImageStencilReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4174,IR(0, 0),IR(9825, 11)/* TensorsARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4175,IR(0, 0),IR(9836, 37)/* StorageTensorArrayDynamicIndexingARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4176,IR(0, 0),IR(9873, 40)/* StorageTensorArrayNonUniformIndexingARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4191,IR(0, 0),IR(9913, 9)/* GraphARM */,IR(0, 0),IR(1, 0),IR(37, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4201,IR(0, 0),IR(9922, 28)/* CooperativeMatrixLayoutsARM */,IR(0, 0),IR(1, 0),IR(38, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4212,IR(0, 0),IR(9950, 10)/* Float8EXT */,IR(0, 0),IR(1, 0),IR(39, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4213,IR(0, 0),IR(9960, 27)/* Float8CooperativeMatrixEXT */,IR(0, 0),IR(78, 2),IR(39, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4422,IR(0, 0),IR(6710, 23)/* FragmentShadingRateKHR */,IR(0, 0),IR(3, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4423,IR(0, 0),IR(6244, 18)/* SubgroupBallotKHR */,IR(0, 0),IR(1, 0),IR(2, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4427,IR(0, 0),IR(6648, 15)/* DrawParameters */,IR(0, 0),IR(3, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4428,IR(0, 0),IR(10008, 33)/* WorkgroupMemoryExplicitLayoutKHR */,IR(0, 0),IR(3, 1),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4429,IR(0, 0),IR(10041, 43)/* WorkgroupMemoryExplicitLayout8BitAccessKHR */,IR(0, 0),IR(80, 1),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4430,IR(0, 0),IR(10084, 44)/* WorkgroupMemoryExplicitLayout16BitAccessKHR */,IR(0, 0),IR(80, 1),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4431,IR(0, 0),IR(10128, 16)/* SubgroupVoteKHR */,IR(0, 0),IR(1, 0),IR(41, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4433,IR(0, 0),IR(10144, 25)/* StorageBuffer16BitAccess */,IR(23, 1),IR(1, 0),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4434,IR(0, 0),IR(10197, 35)/* UniformAndStorageBuffer16BitAccess */,IR(24, 1),IR(81, 1),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4435,IR(0, 0),IR(10249, 22)/* StoragePushConstant16 */,IR(0, 0),IR(1, 0),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4436,IR(0, 0),IR(10271, 21)/* StorageInputOutput16 */,IR(0, 0),IR(1, 0),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4437,IR(0, 0),IR(6745, 12)/* DeviceGroup */,IR(0, 0),IR(1, 0),IR(8, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4439,IR(0, 0),IR(6767, 10)/* MultiView */,IR(0, 0),IR(3, 1),IR(9, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4441,IR(0, 0),IR(10292, 30)/* VariablePointersStorageBuffer */,IR(0, 0),IR(3, 1),IR(43, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4442,IR(0, 0),IR(10322, 17)/* VariablePointers */,IR(0, 0),IR(82, 1),IR(43, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4445,IR(0, 0),IR(10339, 17)/* AtomicStorageOps */,IR(0, 0),IR(83, 1),IR(44, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4447,IR(0, 0),IR(10356, 28)/* SampleMaskPostDepthCoverage */,IR(0, 0),IR(1, 0),IR(45, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4448,IR(0, 0),IR(10384, 24)/* StorageBuffer8BitAccess */,IR(0, 0),IR(1, 0),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4449,IR(0, 0),IR(10408, 34)/* UniformAndStorageBuffer8BitAccess */,IR(0, 0),IR(84, 1),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4450,IR(0, 0),IR(10442, 21)/* StoragePushConstant8 */,IR(0, 0),IR(1, 0),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4464,IR(0, 0),IR(10463, 15)/* DenormPreserve */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4465,IR(0, 0),IR(10478, 18)/* DenormFlushToZero */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4466,IR(0, 0),IR(10496, 25)/* SignedZeroInfNanPreserve */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4467,IR(0, 0),IR(10521, 16)/* RoundingModeRTE */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4468,IR(0, 0),IR(10537, 16)/* RoundingModeRTZ */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4471,IR(0, 0),IR(10553, 23)/* RayQueryProvisionalKHR */,IR(0, 0),IR(3, 1),IR(48, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4472,IR(0, 0),IR(10576, 12)/* RayQueryKHR */,IR(0, 0),IR(3, 1),IR(48, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4473,IR(0, 0),IR(10588, 19)/* UntypedPointersKHR */,IR(0, 0),IR(1, 0),IR(49, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4478,IR(0, 0),IR(10607, 32)/* RayTraversalPrimitiveCullingKHR */,IR(0, 0),IR(85, 2),IR(50, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4479,IR(0, 0),IR(5731, 14)/* RayTracingKHR */,IR(0, 0),IR(3, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4484,IR(0, 0),IR(10639, 26)/* TextureSampleWeightedQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4485,IR(0, 0),IR(10665, 21)/* TextureBoxFilterQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4486,IR(0, 0),IR(10686, 22)/* TextureBlockMatchQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4495,IR(0, 0),IR(6807, 16)/* TileShadingQCOM */,IR(0, 0),IR(3, 1),IR(53, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4496,IR(0, 0),IR(10708, 32)/* CooperativeMatrixConversionQCOM */,IR(0, 0),IR(87, 1),IR(54, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4498,IR(0, 0),IR(10740, 23)/* TextureBlockMatch2QCOM */,IR(0, 0),IR(1, 0),IR(55, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5008,IR(0, 0),IR(10763, 16)/* Float16ImageAMD */,IR(0, 0),IR(3, 1),IR(56, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5009,IR(0, 0),IR(10779, 22)/* ImageGatherBiasLodAMD */,IR(0, 0),IR(3, 1),IR(57, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5010,IR(0, 0),IR(10801, 16)/* FragmentMaskAMD */,IR(0, 0),IR(3, 1),IR(58, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5013,IR(0, 0),IR(7044, 17)/* StencilExportEXT */,IR(0, 0),IR(3, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5015,IR(0, 0),IR(10817, 21)/* ImageReadWriteLodAMD */,IR(0, 0),IR(3, 1),IR(59, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5016,IR(0, 0),IR(10838, 14)/* Int64ImageEXT */,IR(0, 0),IR(3, 1),IR(60, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5055,IR(0, 0),IR(10852, 15)/* ShaderClockKHR */,IR(0, 0),IR(1, 0),IR(61, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5067,IR(0, 0),IR(7090, 18)/* ShaderEnqueueAMDX */,IR(0, 0),IR(3, 1),IR(62, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5087,IR(0, 0),IR(10867, 15)/* QuadControlKHR */,IR(0, 0),IR(1, 0),IR(63, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5112,IR(0, 0),IR(10882, 14)/* Int4TypeINTEL */,IR(0, 0),IR(1, 0),IR(64, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5114,IR(0, 0),IR(10896, 27)/* Int4CooperativeMatrixINTEL */,IR(0, 0),IR(88, 2),IR(64, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5116,IR(0, 0),IR(10923, 16)/* BFloat16TypeKHR */,IR(0, 0),IR(1, 0),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5117,IR(0, 0),IR(10939, 22)/* BFloat16DotProductKHR */,IR(0, 0),IR(90, 1),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5118,IR(0, 0),IR(10961, 29)/* BFloat16CooperativeMatrixKHR */,IR(0, 0),IR(91, 2),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5128,IR(0, 0),IR(7139, 18)/* DescriptorHeapEXT */,IR(0, 0),IR(93, 1),IR(66, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5249,IR(0, 0),IR(10990, 29)/* SampleMaskOverrideCoverageNV */,IR(0, 0),IR(25, 1),IR(67, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5251,IR(0, 0),IR(11019, 28)/* GeometryShaderPassthroughNV */,IR(0, 0),IR(70, 1),IR(68, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5254,IR(0, 0),IR(5805, 28)/* ShaderViewportIndexLayerEXT */,IR(25, 1),IR(94, 1),IR(69, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5255,IR(0, 0),IR(7188, 21)/* ShaderViewportMaskNV */,IR(0, 0),IR(95, 1),IR(71, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5259,IR(0, 0),IR(7229, 19)/* ShaderStereoViewNV */,IR(0, 0),IR(96, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5260,IR(0, 0),IR(7290, 20)/* PerViewAttributesNV */,IR(0, 0),IR(40, 1),IR(72, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5265,IR(0, 0),IR(7348, 24)/* FragmentFullyCoveredEXT */,IR(0, 0),IR(3, 1),IR(17, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5266,IR(0, 0),IR(5745, 14)/* MeshShadingNV */,IR(0, 0),IR(3, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5282,IR(0, 0),IR(11074, 17)/* ImageFootprintNV */,IR(0, 0),IR(1, 0),IR(73, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5283,IR(0, 0),IR(5759, 15)/* MeshShadingEXT */,IR(0, 0),IR(3, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5284,IR(0, 0),IR(7538, 23)/* FragmentBarycentricKHR */,IR(26, 1),IR(1, 0),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5288,IR(0, 0),IR(11113, 31)/* ComputeDerivativeGroupQuadsKHR */,IR(27, 1),IR(3, 1),IR(74, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5291,IR(0, 0),IR(7627, 19)/* FragmentDensityEXT */,IR(28, 1),IR(3, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5297,IR(0, 0),IR(11188, 30)/* GroupNonUniformPartitionedEXT */,IR(29, 1),IR(1, 0),IR(76, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5301,IR(0, 0),IR(11247, 17)/* ShaderNonUniform */,IR(30, 1),IR(3, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5302,IR(0, 0),IR(11284, 23)/* RuntimeDescriptorArray */,IR(31, 1),IR(3, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5303,IR(0, 0),IR(11333, 36)/* InputAttachmentArrayDynamicIndexing */,IR(32, 1),IR(97, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5304,IR(0, 0),IR(11408, 39)/* UniformTexelBufferArrayDynamicIndexing */,IR(33, 1),IR(74, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5305,IR(0, 0),IR(11489, 39)/* StorageTexelBufferArrayDynamicIndexing */,IR(34, 1),IR(98, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5306,IR(0, 0),IR(11570, 37)/* UniformBufferArrayNonUniformIndexing */,IR(35, 1),IR(99, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5307,IR(0, 0),IR(11647, 36)/* SampledImageArrayNonUniformIndexing */,IR(36, 1),IR(99, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5308,IR(0, 0),IR(11722, 37)/* StorageBufferArrayNonUniformIndexing */,IR(37, 1),IR(99, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5309,IR(0, 0),IR(11799, 36)/* StorageImageArrayNonUniformIndexing */,IR(38, 1),IR(99, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5310,IR(0, 0),IR(11874, 39)/* InputAttachmentArrayNonUniformIndexing */,IR(39, 1),IR(100, 2),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5311,IR(0, 0),IR(11955, 42)/* UniformTexelBufferArrayNonUniformIndexing */,IR(40, 1),IR(102, 2),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5312,IR(0, 0),IR(12042, 42)/* StorageTexelBufferArrayNonUniformIndexing */,IR(41, 1),IR(104, 2),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5336,IR(0, 0),IR(8242, 27)/* RayTracingPositionFetchKHR */,IR(0, 0),IR(3, 1),IR(79, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5340,IR(0, 0),IR(5718, 13)/* RayTracingNV */,IR(0, 0),IR(3, 1),IR(26, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5341,IR(0, 0),IR(8189, 23)/* RayTracingMotionBlurNV */,IR(0, 0),IR(3, 1),IR(27, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5345,IR(0, 0),IR(12129, 18)/* VulkanMemoryModel */,IR(42, 1),IR(1, 0),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5346,IR(0, 0),IR(12168, 29)/* VulkanMemoryModelDeviceScope */,IR(43, 1),IR(1, 0),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5347,IR(0, 0),IR(5581, 31)/* PhysicalStorageBufferAddresses */,IR(44, 1),IR(3, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5350,IR(0, 0),IR(12263, 32)/* ComputeDerivativeGroupLinearKHR */,IR(45, 1),IR(3, 1),IR(74, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5353,IR(0, 0),IR(12326, 25)/* RayTracingProvisionalKHR */,IR(0, 0),IR(3, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5357,IR(0, 0),IR(12351, 20)/* CooperativeMatrixNV */,IR(0, 0),IR(3, 1),IR(81, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5363,IR(0, 0),IR(12371, 33)/* FragmentShaderSampleInterlockEXT */,IR(0, 0),IR(3, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5372,IR(0, 0),IR(12404, 38)/* FragmentShaderShadingRateInterlockEXT */,IR(0, 0),IR(3, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5373,IR(0, 0),IR(8557, 19)/* ShaderSMBuiltinsNV */,IR(0, 0),IR(3, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5378,IR(0, 0),IR(12442, 32)/* FragmentShaderPixelInterlockEXT */,IR(0, 0),IR(3, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5379,IR(0, 0),IR(12474, 25)/* DemoteToHelperInvocation */,IR(46, 1),IR(3, 1),IR(83, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5380,IR(0, 0),IR(12527, 23)/* DisplacementMicromapNV */,IR(0, 0),IR(3, 1),IR(84, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5381,IR(0, 0),IR(12550, 29)/* RayTracingOpacityMicromapEXT */,IR(0, 0),IR(3, 1),IR(85, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5383,IR(0, 0),IR(12579, 26)/* ShaderInvocationReorderNV */,IR(0, 0),IR(61, 1),IR(86, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5388,IR(0, 0),IR(12605, 27)/* ShaderInvocationReorderEXT */,IR(0, 0),IR(61, 1),IR(87, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5390,IR(0, 0),IR(12632, 18)/* BindlessTextureNV */,IR(0, 0),IR(1, 0),IR(88, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5391,IR(0, 0),IR(12650, 25)/* RayQueryPositionFetchKHR */,IR(0, 0),IR(3, 1),IR(79, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5394,IR(0, 0),IR(12675, 20)/* CooperativeVectorNV */,IR(0, 0),IR(1, 0),IR(89, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5404,IR(0, 0),IR(12695, 22)/* AtomicFloat16VectorNV */,IR(0, 0),IR(1, 0),IR(90, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5409,IR(0, 0),IR(8303, 33)/* RayTracingDisplacementMicromapNV */,IR(0, 0),IR(61, 1),IR(84, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5414,IR(0, 0),IR(12717, 18)/* RawAccessChainsNV */,IR(0, 0),IR(1, 0),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5418,IR(0, 0),IR(8446, 28)/* RayTracingSpheresGeometryNV */,IR(0, 0),IR(1, 0),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5419,IR(0, 0),IR(8485, 39)/* RayTracingLinearSweptSpheresGeometryNV */,IR(0, 0),IR(1, 0),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5423,IR(0, 0),IR(12735, 20)/* PushConstantBanksNV */,IR(0, 0),IR(3, 1),IR(92, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5425,IR(0, 0),IR(12755, 14)/* LongVectorEXT */,IR(0, 0),IR(1, 0),IR(93, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5426,IR(0, 0),IR(12769, 23)/* Shader64BitIndexingEXT */,IR(0, 0),IR(1, 0),IR(94, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5430,IR(0, 0),IR(12792, 30)/* CooperativeMatrixReductionsNV */,IR(0, 0),IR(1, 0),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5431,IR(0, 0),IR(12822, 31)/* CooperativeMatrixConversionsNV */,IR(0, 0),IR(1, 0),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5432,IR(0, 0),IR(12853, 40)/* CooperativeMatrixPerElementOperationsNV */,IR(0, 0),IR(1, 0),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5433,IR(0, 0),IR(12893, 36)/* CooperativeMatrixTensorAddressingNV */,IR(0, 0),IR(1, 0),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5434,IR(0, 0),IR(12929, 30)/* CooperativeMatrixBlockLoadsNV */,IR(0, 0),IR(1, 0),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5435,IR(0, 0),IR(12959, 28)/* CooperativeVectorTrainingNV */,IR(0, 0),IR(1, 0),IR(89, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5437,IR(0, 0),IR(8731, 41)/* RayTracingClusterAccelerationStructureNV */,IR(0, 0),IR(61, 1),IR(31, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5439,IR(0, 0),IR(12987, 19)/* TensorAddressingNV */,IR(0, 0),IR(1, 0),IR(96, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5568,IR(0, 0),IR(13006, 21)/* SubgroupShuffleINTEL */,IR(0, 0),IR(1, 0),IR(97, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5569,IR(0, 0),IR(13027, 27)/* SubgroupBufferBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(97, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5570,IR(0, 0),IR(13054, 26)/* SubgroupImageBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(97, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5579,IR(0, 0),IR(13080, 31)/* SubgroupImageMediaBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5582,IR(0, 0),IR(13111, 21)/* RoundToInfinityINTEL */,IR(0, 0),IR(1, 0),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5583,IR(0, 0),IR(13132, 23)/* FloatingPointModeINTEL */,IR(0, 0),IR(1, 0),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5584,IR(0, 0),IR(13155, 23)/* IntegerFunctions2INTEL */,IR(0, 0),IR(1, 0),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5603,IR(0, 0),IR(13178, 22)/* FunctionPointersINTEL */,IR(0, 0),IR(1, 0),IR(101, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5604,IR(0, 0),IR(13200, 24)/* IndirectReferencesINTEL */,IR(0, 0),IR(1, 0),IR(101, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5606,IR(0, 0),IR(13224, 9)/* AsmINTEL */,IR(0, 0),IR(1, 0),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5612,IR(0, 0),IR(13233, 23)/* AtomicFloat32MinMaxEXT */,IR(0, 0),IR(1, 0),IR(103, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5613,IR(0, 0),IR(13256, 23)/* AtomicFloat64MinMaxEXT */,IR(0, 0),IR(1, 0),IR(103, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5616,IR(0, 0),IR(13279, 23)/* AtomicFloat16MinMaxEXT */,IR(0, 0),IR(1, 0),IR(103, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5617,IR(0, 0),IR(13302, 19)/* VectorComputeINTEL */,IR(0, 0),IR(106, 1),IR(104, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5619,IR(0, 0),IR(13321, 15)/* VectorAnyINTEL */,IR(0, 0),IR(1, 0),IR(104, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5629,IR(0, 0),IR(13336, 16)/* ExpectAssumeKHR */,IR(0, 0),IR(1, 0),IR(105, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5696,IR(0, 0),IR(13352, 33)/* SubgroupAvcMotionEstimationINTEL */,IR(0, 0),IR(1, 0),IR(106, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5697,IR(0, 0),IR(13385, 38)/* SubgroupAvcMotionEstimationIntraINTEL */,IR(0, 0),IR(1, 0),IR(106, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5698,IR(0, 0),IR(13423, 39)/* SubgroupAvcMotionEstimationChromaINTEL */,IR(0, 0),IR(1, 0),IR(106, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5817,IR(0, 0),IR(13462, 25)/* VariableLengthArrayINTEL */,IR(0, 0),IR(1, 0),IR(107, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5821,IR(0, 0),IR(13487, 26)/* FunctionFloatControlINTEL */,IR(0, 0),IR(1, 0),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5824,IR(0, 0),IR(13513, 27)/* FPGAMemoryAttributesALTERA */,IR(47, 1),IR(1, 0),IR(108, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5837,IR(0, 0),IR(13566, 20)/* FPFastMathModeINTEL */,IR(0, 0),IR(0, 1),IR(110, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5844,IR(0, 0),IR(13586, 33)/* ArbitraryPrecisionIntegersALTERA */,IR(48, 1),IR(1, 0),IR(111, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5845,IR(0, 0),IR(13651, 38)/* ArbitraryPrecisionFloatingPointALTERA */,IR(49, 1),IR(1, 0),IR(113, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5886,IR(0, 0),IR(13726, 30)/* UnstructuredLoopControlsINTEL */,IR(0, 0),IR(1, 0),IR(115, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5888,IR(0, 0),IR(13756, 23)/* FPGALoopControlsALTERA */,IR(50, 1),IR(1, 0),IR(116, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5892,IR(0, 0),IR(13801, 22)/* KernelAttributesINTEL */,IR(0, 0),IR(1, 0),IR(118, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5897,IR(0, 0),IR(13823, 26)/* FPGAKernelAttributesINTEL */,IR(0, 0),IR(1, 0),IR(118, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5898,IR(0, 0),IR(13849, 25)/* FPGAMemoryAccessesALTERA */,IR(51, 1),IR(1, 0),IR(119, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5904,IR(0, 0),IR(13898, 28)/* FPGAClusterAttributesALTERA */,IR(52, 1),IR(1, 0),IR(121, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5906,IR(0, 0),IR(13953, 15)/* LoopFuseALTERA */,IR(53, 1),IR(1, 0),IR(123, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5908,IR(0, 0),IR(13982, 21)/* FPGADSPControlALTERA */,IR(54, 1),IR(1, 0),IR(125, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5910,IR(0, 0),IR(14023, 26)/* MemoryAccessAliasingINTEL */,IR(0, 0),IR(1, 0),IR(127, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5916,IR(0, 0),IR(14049, 41)/* FPGAInvocationPipeliningAttributesALTERA */,IR(55, 1),IR(1, 0),IR(128, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5920,IR(0, 0),IR(14130, 25)/* FPGABufferLocationALTERA */,IR(56, 1),IR(1, 0),IR(130, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5922,IR(0, 0),IR(14179, 35)/* ArbitraryPrecisionFixedPointALTERA */,IR(57, 1),IR(1, 0),IR(132, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5935,IR(0, 0),IR(14248, 24)/* USMStorageClassesALTERA */,IR(58, 1),IR(1, 0),IR(134, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5939,IR(0, 0),IR(14295, 30)/* RuntimeAlignedAttributeALTERA */,IR(59, 1),IR(1, 0),IR(136, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5943,IR(0, 0),IR(14354, 14)/* IOPipesALTERA */,IR(60, 1),IR(1, 0),IR(138, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5945,IR(0, 0),IR(14381, 20)/* BlockingPipesALTERA */,IR(61, 1),IR(1, 0),IR(140, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5948,IR(0, 0),IR(14420, 14)/* FPGARegALTERA */,IR(62, 1),IR(1, 0),IR(142, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6016,IR(0, 0),IR(14447, 19)/* DotProductInputAll */,IR(63, 1),IR(1, 0),IR(144, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6017,IR(0, 0),IR(14488, 22)/* DotProductInput4x8Bit */,IR(64, 1),IR(107, 1),IR(144, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6018,IR(0, 0),IR(14535, 28)/* DotProductInput4x8BitPacked */,IR(65, 1),IR(1, 0),IR(144, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6019,IR(0, 0),IR(14594, 11)/* DotProduct */,IR(66, 1),IR(1, 0),IR(144, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6020,IR(0, 0),IR(8784, 15)/* RayCullMaskKHR */,IR(0, 0),IR(1, 0),IR(32, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6022,IR(0, 0),IR(9987, 21)/* CooperativeMatrixKHR */,IR(0, 0),IR(1, 0),IR(145, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6024,IR(0, 0),IR(14619, 24)/* ReplicatedCompositesEXT */,IR(0, 0),IR(1, 0),IR(146, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6025,IR(0, 0),IR(14643, 16)/* BitInstructions */,IR(0, 0),IR(1, 0),IR(147, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6026,IR(0, 0),IR(14659, 25)/* GroupNonUniformRotateKHR */,IR(0, 0),IR(77, 1),IR(148, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6029,IR(0, 0),IR(14684, 15)/* FloatControls2 */,IR(0, 0),IR(1, 0),IR(149, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6030,IR(0, 0),IR(14699, 7)/* FMAKHR */,IR(0, 0),IR(1, 0),IR(150, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6033,IR(0, 0),IR(14706, 20)/* AtomicFloat32AddEXT */,IR(0, 0),IR(1, 0),IR(151, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6034,IR(0, 0),IR(14726, 20)/* AtomicFloat64AddEXT */,IR(0, 0),IR(1, 0),IR(151, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6089,IR(0, 0),IR(14746, 20)/* LongCompositesINTEL */,IR(0, 0),IR(1, 0),IR(152, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6094,IR(0, 0),IR(14766, 11)/* OptNoneEXT */,IR(67, 1),IR(1, 0),IR(153, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6095,IR(0, 0),IR(14790, 20)/* AtomicFloat16AddEXT */,IR(0, 0),IR(1, 0),IR(155, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6114,IR(0, 0),IR(14810, 21)/* DebugInfoModuleINTEL */,IR(0, 0),IR(1, 0),IR(156, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6115,IR(0, 0),IR(14831, 24)/* BFloat16ConversionINTEL */,IR(0, 0),IR(1, 0),IR(157, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6141,IR(0, 0),IR(14855, 18)/* SplitBarrierINTEL */,IR(0, 0),IR(1, 0),IR(158, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6144,IR(0, 0),IR(14873, 19)/* ArithmeticFenceEXT */,IR(0, 0),IR(1, 0),IR(159, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6150,IR(0, 0),IR(14892, 30)/* FPGAClusterAttributesV2ALTERA */,IR(68, 1),IR(108, 1),IR(121, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6161,IR(0, 0),IR(14951, 28)/* FPGAKernelAttributesv2INTEL */,IR(0, 0),IR(109, 1),IR(118, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6162,IR(0, 0),IR(14979, 19)/* TaskSequenceALTERA */,IR(69, 1),IR(1, 0),IR(160, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6169,IR(0, 0),IR(15016, 16)/* FPMaxErrorINTEL */,IR(0, 0),IR(1, 0),IR(162, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6171,IR(0, 0),IR(15032, 25)/* FPGALatencyControlALTERA */,IR(70, 1),IR(1, 0),IR(163, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6174,IR(0, 0),IR(15081, 29)/* FPGAArgumentInterfacesALTERA */,IR(71, 1),IR(1, 0),IR(165, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6187,IR(0, 0),IR(15138, 30)/* GlobalVariableHostAccessINTEL */,IR(0, 0),IR(1, 0),IR(167, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6189,IR(0, 0),IR(15168, 36)/* GlobalVariableFPGADecorationsALTERA */,IR(72, 1),IR(1, 0),IR(168, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6220,IR(0, 0),IR(15239, 28)/* SubgroupBufferPrefetchINTEL */,IR(0, 0),IR(1, 0),IR(170, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6228,IR(0, 0),IR(15267, 23)/* Subgroup2DBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(171, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6229,IR(0, 0),IR(15290, 30)/* Subgroup2DBlockTransformINTEL */,IR(0, 0),IR(110, 1),IR(171, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6230,IR(0, 0),IR(15320, 30)/* Subgroup2DBlockTransposeINTEL */,IR(0, 0),IR(110, 1),IR(171, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6236,IR(0, 0),IR(15350, 38)/* SubgroupMatrixMultiplyAccumulateINTEL */,IR(0, 0),IR(1, 0),IR(172, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6241,IR(0, 0),IR(15388, 28)/* TernaryBitwiseFunctionINTEL */,IR(0, 0),IR(1, 0),IR(173, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6243,IR(0, 0),IR(15416, 32)/* UntypedVariableLengthArrayINTEL */,IR(0, 0),IR(111, 2),IR(107, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6245,IR(0, 0),IR(15448, 21)/* SpecConditionalINTEL */,IR(0, 0),IR(1, 0),IR(174, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6246,IR(0, 0),IR(15469, 22)/* FunctionVariantsINTEL */,IR(0, 0),IR(113, 1),IR(174, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6400,IR(0, 0),IR(15491, 26)/* GroupUniformArithmeticKHR */,IR(0, 0),IR(1, 0),IR(175, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6425,IR(0, 0),IR(15517, 27)/* TensorFloat32RoundingINTEL */,IR(0, 0),IR(1, 0),IR(176, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6427,IR(0, 0),IR(15544, 25)/* MaskedGatherScatterINTEL */,IR(0, 0),IR(1, 0),IR(177, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6441,IR(0, 0),IR(15569, 19)/* CacheControlsINTEL */,IR(0, 0),IR(1, 0),IR(178, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6460,IR(0, 0),IR(15588, 20)/* RegisterLimitsINTEL */,IR(0, 0),IR(1, 0),IR(179, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6528,IR(0, 0),IR(15608, 20)/* BindlessImagesINTEL */,IR(0, 0),IR(1, 0),IR(180, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {0,IR(0, 0),IR(15628, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(15640, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(15648, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {3,IR(0, 0),IR(15656, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(15662, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(15669, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(15680, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(15689, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(15702, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(15708, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(15718, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(15724, 15)/* ImportedModule */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {1,IR(0, 0),IR(15739, 20)/* ImportedDeclaration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {0,IR(0, 0),IR(15759, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(15764, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(15780, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(15794, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(15807, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(15819, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(15836, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(15848, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(15863, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(15876, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(15891, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(15909, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(15926, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(15947, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(15967, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(15987, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {16384,IR(0, 0),IR(16003, 16)/* FlagIsEnumClass */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {32768,IR(0, 0),IR(16019, 20)/* FlagTypePassByValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {65536,IR(0, 0),IR(16039, 24)/* FlagTypePassByReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(16063, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {1,IR(0, 0),IR(16069, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {2,IR(0, 0),IR(16074, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {3,IR(0, 1),IR(16113, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {4,IR(1, 2),IR(16124, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {5,IR(0, 0),IR(16133, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {6,IR(0, 0),IR(16138, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {7,IR(0, 0),IR(16145, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {8,IR(0, 1),IR(16156, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {9,IR(1, 2),IR(16163, 9)/* Fragment */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {0,IR(0, 0),IR(16172, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(16182, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(16195, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {3,IR(0, 0),IR(16208, 11)/* AtomicType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(16219, 10)/* Float16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1,IR(0, 0),IR(16229, 10)/* Float32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {2,IR(0, 0),IR(16239, 10)/* Float64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {3,IR(0, 0),IR(16249, 13)/* SignedInt8NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {4,IR(0, 0),IR(16262, 14)/* SignedInt16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {5,IR(0, 0),IR(16276, 14)/* SignedInt32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {6,IR(0, 0),IR(16290, 14)/* SignedInt64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {7,IR(0, 0),IR(16304, 15)/* UnsignedInt8NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {8,IR(0, 0),IR(16319, 16)/* UnsignedInt16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {9,IR(0, 0),IR(16335, 16)/* UnsignedInt32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {10,IR(0, 0),IR(16351, 16)/* UnsignedInt64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491000,IR(0, 0),IR(16367, 19)/* SignedInt8PackedNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491001,IR(0, 0),IR(16386, 21)/* UnsignedInt8PackedNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491002,IR(0, 0),IR(16407, 12)/* FloatE4M3NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491003,IR(0, 0),IR(16419, 12)/* FloatE5M2NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {0,IR(0, 0),IR(16431, 12)/* RowMajorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {1,IR(0, 0),IR(16443, 15)/* ColumnMajorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {4202,IR(0, 0),IR(16458, 25)/* RowBlockedInterleavedARM */,IR(0, 0),IR(114, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {4203,IR(0, 0),IR(16483, 28)/* ColumnBlockedInterleavedARM */,IR(0, 0),IR(114, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {0,IR(0, 0),IR(16511, 8)/* NoneKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {1,IR(0, 0),IR(16519, 27)/* MatrixASignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {2,IR(0, 0),IR(16546, 27)/* MatrixBSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {4,IR(0, 0),IR(16573, 27)/* MatrixCSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {8,IR(0, 0),IR(16600, 32)/* MatrixResultSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {16,IR(0, 0),IR(16632, 26)/* SaturatingAccumulationKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {1,IR(0, 0),IR(16658, 4)/* Row */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {2,IR(0, 0),IR(16662, 7)/* Column */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {4,IR(0, 0),IR(16669, 4)/* 2x2 */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {0,IR(0, 0),IR(16673, 11)/* MatrixAKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {1,IR(0, 0),IR(16684, 11)/* MatrixBKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {2,IR(0, 0),IR(16695, 21)/* MatrixAccumulatorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {0,IR(0, 0),IR(16716, 11)/* RowMajorNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {1,IR(0, 0),IR(16727, 14)/* ColumnMajorNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {2,IR(0, 0),IR(16741, 21)/* InferencingOptimalNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {3,IR(0, 0),IR(16762, 18)/* TrainingOptimalNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {0,IR(0, 0),IR(15628, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(15640, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(15648, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(15656, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(15662, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(15669, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(15680, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {8,IR(0, 0),IR(15689, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(15702, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(15708, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(15718, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(15759, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(15764, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(15780, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(15794, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(15807, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(15819, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(15836, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(15848, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(15863, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(15876, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(15891, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(15909, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(15926, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(15947, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(15967, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(15987, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(16063, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {1,IR(0, 0),IR(16069, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {2,IR(0, 0),IR(16074, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {3,IR(0, 1),IR(16113, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {4,IR(1, 2),IR(16124, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {5,IR(0, 0),IR(16133, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {6,IR(0, 0),IR(16138, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {7,IR(0, 0),IR(16145, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {8,IR(0, 1),IR(16156, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {0,IR(0, 0),IR(16172, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(16182, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(16195, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(16780, 17)/* RelaxedPrecision */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {1,IR(0, 1),IR(16797, 7)/* SpecId */,IR(0, 0),IR(115, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {2,IR(0, 0),IR(16804, 6)/* Block */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {3,IR(0, 0),IR(16810, 12)/* BufferBlock */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),SPV_SPIRV_VERSION_WORD(1,3)}, // SPV_OPERAND_TYPE_DECORATION
  {4,IR(0, 0),IR(16822, 9)/* RowMajor */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5,IR(0, 0),IR(16831, 9)/* ColMajor */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6,IR(0, 1),IR(16840, 12)/* ArrayStride */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {7,IR(0, 1),IR(16852, 13)/* MatrixStride */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {8,IR(0, 0),IR(16865, 11)/* GLSLShared */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {9,IR(0, 0),IR(16876, 11)/* GLSLPacked */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {10,IR(0, 0),IR(16887, 8)/* CPacked */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {11,IR(3, 1),IR(16921, 8)/* BuiltIn */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {13,IR(0, 0),IR(16929, 14)/* NoPerspective */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {14,IR(0, 0),IR(16943, 5)/* Flat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {15,IR(0, 0),IR(16948, 6)/* Patch */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {16,IR(0, 0),IR(16954, 9)/* Centroid */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {17,IR(0, 0),IR(16963, 7)/* Sample */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {18,IR(0, 0),IR(16970, 10)/* Invariant */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {19,IR(0, 0),IR(16980, 9)/* Restrict */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {20,IR(0, 0),IR(16989, 8)/* Aliased */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {21,IR(0, 0),IR(16997, 9)/* Volatile */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {22,IR(0, 0),IR(17006, 9)/* Constant */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {23,IR(0, 0),IR(17015, 9)/* Coherent */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {24,IR(0, 0),IR(17024, 12)/* NonWritable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {25,IR(0, 0),IR(17036, 12)/* NonReadable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {26,IR(0, 0),IR(17048, 8)/* Uniform */,IR(0, 0),IR(117, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {27,IR(4, 1),IR(17082, 10)/* UniformId */,IR(0, 0),IR(117, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {28,IR(0, 0),IR(17092, 20)/* SaturatedConversion */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {29,IR(0, 1),IR(17112, 7)/* Stream */,IR(0, 0),IR(119, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {30,IR(0, 1),IR(17119, 9)/* Location */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {31,IR(0, 1),IR(17128, 10)/* Component */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {32,IR(0, 1),IR(17138, 6)/* Index */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {33,IR(0, 1),IR(17144, 8)/* Binding */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {34,IR(0, 1),IR(17152, 14)/* DescriptorSet */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {35,IR(0, 1),IR(17166, 7)/* Offset */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {36,IR(0, 1),IR(17173, 10)/* XfbBuffer */,IR(0, 0),IR(120, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {37,IR(0, 1),IR(17183, 10)/* XfbStride */,IR(0, 0),IR(120, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {38,IR(5, 1),IR(17239, 14)/* FuncParamAttr */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {39,IR(6, 1),IR(17287, 15)/* FPRoundingMode */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {40,IR(7, 1),IR(17337, 15)/* FPFastMathMode */,IR(0, 0),IR(121, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {41,IR(8, 2),IR(17414, 18)/* LinkageAttributes */,IR(0, 0),IR(123, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {42,IR(0, 0),IR(17432, 14)/* NoContraction */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {43,IR(0, 1),IR(17446, 21)/* InputAttachmentIndex */,IR(0, 0),IR(97, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {44,IR(0, 1),IR(17467, 10)/* Alignment */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {45,IR(0, 1),IR(17477, 14)/* MaxByteOffset */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {46,IR(10, 1),IR(17511, 12)/* AlignmentId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {47,IR(10, 1),IR(17523, 16)/* MaxByteOffsetId */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4216,IR(0, 0),IR(17539, 44)/* SaturatedToLargestFloat8NormalConversionEXT */,IR(0, 0),IR(124, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4469,IR(0, 0),IR(17583, 13)/* NoSignedWrap */,IR(0, 0),IR(1, 0),IR(181, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4470,IR(0, 0),IR(17596, 15)/* NoUnsignedWrap */,IR(0, 0),IR(1, 0),IR(181, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4487,IR(0, 0),IR(17611, 18)/* WeightTextureQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4488,IR(0, 0),IR(17629, 22)/* BlockMatchTextureQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4499,IR(0, 0),IR(17651, 22)/* BlockMatchSamplerQCOM */,IR(0, 0),IR(1, 0),IR(55, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4999,IR(0, 0),IR(17673, 18)/* ExplicitInterpAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5019,IR(10, 1),IR(17691, 32)/* NodeSharesPayloadLimitsWithAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5020,IR(10, 1),IR(17723, 20)/* NodeMaxPayloadsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5078,IR(0, 0),IR(17743, 23)/* TrackFinishWritingAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5091,IR(10, 1),IR(17766, 20)/* PayloadNodeNameAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5098,IR(10, 1),IR(17786, 25)/* PayloadNodeBaseIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5099,IR(0, 0),IR(17811, 27)/* PayloadNodeSparseArrayAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5100,IR(10, 1),IR(17838, 25)/* PayloadNodeArraySizeAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5105,IR(0, 0),IR(17863, 28)/* PayloadDispatchIndirectAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5124,IR(10, 1),IR(17891, 17)/* ArrayStrideIdEXT */,IR(0, 0),IR(44, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5125,IR(10, 1),IR(17908, 12)/* OffsetIdEXT */,IR(0, 0),IR(44, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5248,IR(0, 0),IR(17920, 19)/* OverrideCoverageNV */,IR(0, 0),IR(125, 1),IR(67, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5250,IR(0, 0),IR(17939, 14)/* PassthroughNV */,IR(0, 0),IR(126, 1),IR(68, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5252,IR(0, 0),IR(17953, 19)/* ViewportRelativeNV */,IR(0, 0),IR(96, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5256,IR(0, 1),IR(17972, 28)/* SecondaryViewportRelativeNV */,IR(0, 0),IR(47, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5271,IR(0, 0),IR(18000, 16)/* PerPrimitiveEXT */,IR(73, 1),IR(127, 2),IR(182, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5272,IR(0, 0),IR(18031, 10)/* PerViewNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5273,IR(0, 0),IR(18041, 10)/* PerTaskNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5285,IR(0, 0),IR(18051, 13)/* PerVertexKHR */,IR(74, 1),IR(52, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5300,IR(0, 0),IR(18076, 11)/* NonUniform */,IR(75, 1),IR(99, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5355,IR(0, 0),IR(18101, 16)/* RestrictPointer */,IR(76, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5356,IR(0, 0),IR(18136, 15)/* AliasedPointer */,IR(77, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5358,IR(0, 1),IR(18169, 15)/* MemberOffsetNV */,IR(0, 0),IR(129, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5386,IR(0, 0),IR(18184, 30)/* HitObjectShaderRecordBufferNV */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5389,IR(0, 0),IR(18214, 31)/* HitObjectShaderRecordBufferEXT */,IR(0, 0),IR(131, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5397,IR(0, 1),IR(18245, 7)/* BankNV */,IR(0, 0),IR(129, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5398,IR(0, 0),IR(18252, 18)/* BindlessSamplerNV */,IR(0, 0),IR(132, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5399,IR(0, 0),IR(18270, 16)/* BindlessImageNV */,IR(0, 0),IR(132, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5400,IR(0, 0),IR(18286, 15)/* BoundSamplerNV */,IR(0, 0),IR(132, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5401,IR(0, 0),IR(18301, 13)/* BoundImageNV */,IR(0, 0),IR(132, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5599,IR(0, 1),IR(18314, 14)/* SIMTCallINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5602,IR(0, 0),IR(18328, 26)/* ReferencedIndirectlyINTEL */,IR(0, 0),IR(134, 1),IR(101, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5607,IR(11, 1),IR(18354, 13)/* ClobberINTEL */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5608,IR(0, 0),IR(18367, 17)/* SideEffectsINTEL */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5624,IR(0, 0),IR(18384, 27)/* VectorComputeVariableINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5625,IR(0, 1),IR(18411, 21)/* FuncParamIOKindINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5626,IR(0, 0),IR(18432, 27)/* VectorComputeFunctionINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5627,IR(0, 0),IR(18459, 15)/* StackCallINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5628,IR(0, 1),IR(18474, 26)/* GlobalVariableOffsetINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5634,IR(10, 1),IR(18500, 14)/* CounterBuffer */,IR(78, 1),IR(1, 0),IR(184, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5635,IR(11, 1),IR(18538, 13)/* UserSemantic */,IR(79, 1),IR(1, 0),IR(184, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5636,IR(11, 1),IR(18570, 15)/* UserTypeGOOGLE */,IR(0, 0),IR(1, 0),IR(185, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5822,IR(12, 2),IR(18585, 26)/* FunctionRoundingModeINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5823,IR(14, 2),IR(18642, 24)/* FunctionDenormModeINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5825,IR(0, 0),IR(18666, 15)/* RegisterALTERA */,IR(80, 1),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5826,IR(11, 1),IR(18695, 13)/* MemoryALTERA */,IR(81, 1),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5827,IR(0, 1),IR(18720, 15)/* NumbanksALTERA */,IR(82, 1),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5828,IR(0, 1),IR(18749, 16)/* BankwidthALTERA */,IR(83, 1),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5829,IR(0, 1),IR(18780, 23)/* MaxPrivateCopiesALTERA */,IR(84, 1),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5830,IR(0, 0),IR(18825, 17)/* SinglepumpALTERA */,IR(85, 1),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5831,IR(0, 0),IR(18858, 17)/* DoublepumpALTERA */,IR(86, 1),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5832,IR(0, 1),IR(18891, 20)/* MaxReplicatesALTERA */,IR(87, 1),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5833,IR(0, 0),IR(18930, 21)/* SimpleDualPortALTERA */,IR(88, 1),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5834,IR(16, 2),IR(18971, 12)/* MergeALTERA */,IR(89, 1),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5835,IR(18, 1),IR(19036, 15)/* BankBitsALTERA */,IR(90, 1),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5836,IR(0, 1),IR(19065, 21)/* ForcePow2DepthALTERA */,IR(91, 1),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5883,IR(0, 1),IR(19106, 17)/* StridesizeALTERA */,IR(92, 1),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5884,IR(0, 1),IR(19139, 15)/* WordsizeALTERA */,IR(93, 1),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5885,IR(0, 0),IR(19168, 19)/* TrueDualPortALTERA */,IR(94, 1),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5899,IR(0, 0),IR(19205, 20)/* BurstCoalesceALTERA */,IR(95, 1),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5900,IR(0, 1),IR(19244, 16)/* CacheSizeALTERA */,IR(96, 1),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5901,IR(0, 0),IR(19275, 29)/* DontStaticallyCoalesceALTERA */,IR(97, 1),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5902,IR(0, 1),IR(19332, 15)/* PrefetchALTERA */,IR(98, 1),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5905,IR(0, 0),IR(19361, 18)/* StallEnableALTERA */,IR(99, 1),IR(108, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5907,IR(0, 0),IR(19396, 26)/* FuseLoopsInFunctionALTERA */,IR(100, 1),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5909,IR(1, 2),IR(19447, 20)/* MathOpDSPModeALTERA */,IR(101, 1),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5914,IR(10, 1),IR(19486, 16)/* AliasScopeINTEL */,IR(0, 0),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5915,IR(10, 1),IR(19502, 13)/* NoAliasINTEL */,IR(0, 0),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5917,IR(0, 1),IR(19515, 25)/* InitiationIntervalALTERA */,IR(102, 1),IR(142, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5918,IR(0, 1),IR(19564, 21)/* MaxConcurrencyALTERA */,IR(103, 1),IR(142, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5919,IR(0, 1),IR(19605, 21)/* PipelineEnableALTERA */,IR(104, 1),IR(142, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5921,IR(0, 1),IR(19646, 21)/* BufferLocationALTERA */,IR(105, 1),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5944,IR(0, 1),IR(19687, 20)/* IOPipeStorageALTERA */,IR(106, 1),IR(144, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6080,IR(19, 2),IR(19760, 31)/* FunctionFloatingPointModeINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6085,IR(0, 0),IR(19791, 25)/* SingleElementVectorINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6087,IR(0, 0),IR(19816, 35)/* VectorComputeCallableFunctionINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6140,IR(0, 0),IR(19851, 18)/* MediaBlockIOINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6151,IR(0, 0),IR(19869, 16)/* StallFreeALTERA */,IR(107, 1),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6170,IR(21, 1),IR(19931, 26)/* FPMaxErrorDecorationINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6172,IR(0, 1),IR(19957, 26)/* LatencyControlLabelALTERA */,IR(108, 1),IR(147, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6173,IR(22, 3),IR(20008, 31)/* LatencyControlConstraintALTERA */,IR(109, 1),IR(147, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6175,IR(0, 0),IR(20069, 28)/* ConduitKernelArgumentALTERA */,IR(110, 1),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6176,IR(0, 0),IR(20124, 32)/* RegisterMapKernelArgumentALTERA */,IR(111, 1),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6177,IR(0, 1),IR(20187, 34)/* MMHostInterfaceAddressWidthALTERA */,IR(112, 1),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6178,IR(0, 1),IR(20254, 31)/* MMHostInterfaceDataWidthALTERA */,IR(113, 1),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6179,IR(0, 1),IR(20315, 29)/* MMHostInterfaceLatencyALTERA */,IR(114, 1),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6180,IR(25, 1),IR(20406, 35)/* MMHostInterfaceReadWriteModeALTERA */,IR(115, 1),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6181,IR(0, 1),IR(20475, 30)/* MMHostInterfaceMaxBurstALTERA */,IR(116, 1),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6182,IR(0, 1),IR(20534, 33)/* MMHostInterfaceWaitRequestALTERA */,IR(117, 1),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6183,IR(0, 0),IR(20599, 27)/* StableKernelArgumentALTERA */,IR(118, 1),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6188,IR(26, 2),IR(20691, 16)/* HostAccessINTEL */,IR(0, 0),IR(149, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6190,IR(28, 1),IR(20754, 15)/* InitModeALTERA */,IR(119, 1),IR(150, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6191,IR(0, 1),IR(20783, 29)/* ImplementInRegisterMapALTERA */,IR(120, 1),IR(150, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6247,IR(10, 1),IR(20840, 17)/* ConditionalINTEL */,IR(0, 0),IR(113, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6442,IR(29, 2),IR(20893, 22)/* CacheControlLoadINTEL */,IR(0, 0),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6443,IR(31, 2),IR(20952, 23)/* CacheControlStoreINTEL */,IR(0, 0),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {0,IR(0, 0),IR(20975, 3)/* 1D */,IR(0, 0),IR(73, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {1,IR(0, 0),IR(20978, 3)/* 2D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {2,IR(0, 0),IR(20981, 3)/* 3D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {3,IR(0, 0),IR(20984, 5)/* Cube */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {4,IR(0, 0),IR(20989, 5)/* Rect */,IR(0, 0),IR(72, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {5,IR(0, 0),IR(20994, 7)/* Buffer */,IR(0, 0),IR(74, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {6,IR(0, 0),IR(21001, 12)/* SubpassData */,IR(0, 0),IR(97, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {4173,IR(0, 0),IR(21013, 17)/* TileImageDataEXT */,IR(0, 0),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {0,IR(0, 1),IR(21030, 12)/* Invocations */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {1,IR(0, 0),IR(21042, 13)/* SpacingEqual */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {2,IR(0, 0),IR(21055, 22)/* SpacingFractionalEven */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {3,IR(0, 0),IR(21077, 21)/* SpacingFractionalOdd */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4,IR(0, 0),IR(21098, 14)/* VertexOrderCw */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5,IR(0, 0),IR(21112, 15)/* VertexOrderCcw */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6,IR(0, 0),IR(21127, 19)/* PixelCenterInteger */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {7,IR(0, 0),IR(21146, 16)/* OriginUpperLeft */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {8,IR(0, 0),IR(21162, 16)/* OriginLowerLeft */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {9,IR(0, 0),IR(21178, 19)/* EarlyFragmentTests */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {10,IR(0, 0),IR(21197, 10)/* PointMode */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {11,IR(0, 0),IR(21207, 4)/* Xfb */,IR(0, 0),IR(120, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {12,IR(0, 0),IR(21211, 15)/* DepthReplacing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {14,IR(0, 0),IR(21226, 13)/* DepthGreater */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {15,IR(0, 0),IR(21239, 10)/* DepthLess */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {16,IR(0, 0),IR(21249, 15)/* DepthUnchanged */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {17,IR(22, 3),IR(21264, 10)/* LocalSize */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {18,IR(22, 3),IR(21274, 14)/* LocalSizeHint */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {19,IR(0, 0),IR(21288, 12)/* InputPoints */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {20,IR(0, 0),IR(21300, 11)/* InputLines */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {21,IR(0, 0),IR(21311, 20)/* InputLinesAdjacency */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {22,IR(0, 0),IR(21331, 10)/* Triangles */,IR(0, 0),IR(12, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {23,IR(0, 0),IR(21341, 24)/* InputTrianglesAdjacency */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {24,IR(0, 0),IR(21365, 6)/* Quads */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {25,IR(0, 0),IR(21371, 9)/* Isolines */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {26,IR(0, 1),IR(21380, 15)/* OutputVertices */,IR(0, 0),IR(153, 4),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {27,IR(0, 0),IR(21395, 13)/* OutputPoints */,IR(0, 0),IR(157, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {28,IR(0, 0),IR(21408, 16)/* OutputLineStrip */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {29,IR(0, 0),IR(21424, 20)/* OutputTriangleStrip */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {30,IR(0, 1),IR(21444, 12)/* VecTypeHint */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {31,IR(0, 0),IR(21456, 15)/* ContractionOff */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {33,IR(0, 0),IR(21471, 12)/* Initializer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {34,IR(0, 0),IR(21483, 10)/* Finalizer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {35,IR(0, 1),IR(6215, 13)/* SubgroupSize */,IR(0, 0),IR(160, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {36,IR(0, 1),IR(21493, 22)/* SubgroupsPerWorkgroup */,IR(0, 0),IR(160, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {37,IR(10, 1),IR(21515, 24)/* SubgroupsPerWorkgroupId */,IR(0, 0),IR(160, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {38,IR(33, 3),IR(21539, 12)/* LocalSizeId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {39,IR(33, 3),IR(21551, 16)/* LocalSizeHintId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4169,IR(0, 0),IR(21567, 34)/* NonCoherentColorAttachmentReadEXT */,IR(0, 0),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4170,IR(0, 0),IR(21601, 34)/* NonCoherentDepthAttachmentReadEXT */,IR(0, 0),IR(161, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4171,IR(0, 0),IR(21635, 36)/* NonCoherentStencilAttachmentReadEXT */,IR(0, 0),IR(162, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4421,IR(0, 0),IR(21671, 30)/* SubgroupUniformControlFlowKHR */,IR(0, 0),IR(3, 1),IR(186, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4446,IR(0, 0),IR(21701, 18)/* PostDepthCoverage */,IR(0, 0),IR(163, 1),IR(45, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4459,IR(0, 1),IR(10463, 15)/* DenormPreserve */,IR(0, 0),IR(164, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4460,IR(0, 1),IR(10478, 18)/* DenormFlushToZero */,IR(0, 0),IR(165, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4461,IR(0, 1),IR(10496, 25)/* SignedZeroInfNanPreserve */,IR(0, 0),IR(166, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4462,IR(0, 1),IR(10521, 16)/* RoundingModeRTE */,IR(0, 0),IR(167, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4463,IR(0, 1),IR(10537, 16)/* RoundingModeRTZ */,IR(0, 0),IR(168, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4489,IR(0, 0),IR(21719, 34)/* NonCoherentTileAttachmentReadQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4490,IR(22, 3),IR(21753, 20)/* TileShadingRateQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5017,IR(0, 0),IR(21773, 29)/* EarlyAndLateFragmentTestsAMD */,IR(0, 0),IR(3, 1),IR(187, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5027,IR(0, 0),IR(21802, 23)/* StencilRefReplacingEXT */,IR(0, 0),IR(42, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5069,IR(0, 0),IR(21825, 15)/* CoalescingAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5070,IR(10, 1),IR(21840, 15)/* IsApiEntryAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5071,IR(10, 1),IR(21855, 21)/* MaxNodeRecursionAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5072,IR(33, 3),IR(21876, 24)/* StaticNumWorkgroupsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5073,IR(10, 1),IR(7108, 16)/* ShaderIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5077,IR(33, 3),IR(21900, 21)/* MaxNumWorkgroupsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5079,IR(0, 0),IR(21921, 28)/* StencilRefUnchangedFrontAMD */,IR(0, 0),IR(42, 1),IR(188, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5080,IR(0, 0),IR(21949, 26)/* StencilRefGreaterFrontAMD */,IR(0, 0),IR(42, 1),IR(188, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5081,IR(0, 0),IR(21975, 23)/* StencilRefLessFrontAMD */,IR(0, 0),IR(42, 1),IR(188, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5082,IR(0, 0),IR(21998, 27)/* StencilRefUnchangedBackAMD */,IR(0, 0),IR(42, 1),IR(188, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5083,IR(0, 0),IR(22025, 25)/* StencilRefGreaterBackAMD */,IR(0, 0),IR(42, 1),IR(188, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5084,IR(0, 0),IR(22050, 22)/* StencilRefLessBackAMD */,IR(0, 0),IR(42, 1),IR(188, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5088,IR(0, 0),IR(22072, 19)/* QuadDerivativesKHR */,IR(0, 0),IR(169, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5089,IR(0, 0),IR(22091, 20)/* RequireFullQuadsKHR */,IR(0, 0),IR(169, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5102,IR(36, 2),IR(22111, 20)/* SharesInputWithAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5269,IR(0, 0),IR(22131, 15)/* OutputLinesEXT */,IR(121, 1),IR(127, 2),IR(182, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5270,IR(0, 1),IR(22160, 20)/* OutputPrimitivesEXT */,IR(122, 1),IR(127, 2),IR(182, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5289,IR(0, 0),IR(22199, 24)/* DerivativeGroupQuadsKHR */,IR(123, 1),IR(170, 1),IR(74, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5290,IR(0, 0),IR(22246, 25)/* DerivativeGroupLinearKHR */,IR(124, 1),IR(171, 1),IR(74, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5298,IR(0, 0),IR(22295, 19)/* OutputTrianglesEXT */,IR(125, 1),IR(127, 2),IR(182, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5366,IR(0, 0),IR(22332, 25)/* PixelInterlockOrderedEXT */,IR(0, 0),IR(172, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5367,IR(0, 0),IR(22357, 27)/* PixelInterlockUnorderedEXT */,IR(0, 0),IR(172, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5368,IR(0, 0),IR(22384, 26)/* SampleInterlockOrderedEXT */,IR(0, 0),IR(173, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5369,IR(0, 0),IR(22410, 28)/* SampleInterlockUnorderedEXT */,IR(0, 0),IR(173, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5370,IR(0, 0),IR(22438, 31)/* ShadingRateInterlockOrderedEXT */,IR(0, 0),IR(174, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5371,IR(0, 0),IR(22469, 33)/* ShadingRateInterlockUnorderedEXT */,IR(0, 0),IR(174, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5427,IR(0, 0),IR(12769, 23)/* Shader64BitIndexingEXT */,IR(0, 0),IR(175, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5618,IR(0, 1),IR(22502, 27)/* SharedLocalMemorySizeINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5620,IR(0, 1),IR(22529, 21)/* RoundingModeRTPINTEL */,IR(0, 0),IR(176, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5621,IR(0, 1),IR(22550, 21)/* RoundingModeRTNINTEL */,IR(0, 0),IR(176, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5622,IR(0, 1),IR(22571, 26)/* FloatingPointModeALTINTEL */,IR(0, 0),IR(176, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5623,IR(0, 1),IR(22597, 27)/* FloatingPointModeIEEEINTEL */,IR(0, 0),IR(176, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5893,IR(22, 3),IR(22624, 22)/* MaxWorkgroupSizeINTEL */,IR(0, 0),IR(177, 1),IR(118, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5894,IR(0, 1),IR(22646, 16)/* MaxWorkDimINTEL */,IR(0, 0),IR(177, 1),IR(118, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5895,IR(0, 0),IR(22662, 20)/* NoGlobalOffsetINTEL */,IR(0, 0),IR(177, 1),IR(118, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5896,IR(0, 1),IR(22682, 22)/* NumSIMDWorkitemsINTEL */,IR(0, 0),IR(109, 1),IR(118, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5903,IR(0, 1),IR(22704, 28)/* SchedulerTargetFmaxMhzINTEL */,IR(0, 0),IR(109, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6023,IR(0, 0),IR(22732, 24)/* MaximallyReconvergesKHR */,IR(0, 0),IR(3, 1),IR(190, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6028,IR(36, 2),IR(22756, 18)/* FPFastMathDefault */,IR(0, 0),IR(178, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6154,IR(0, 1),IR(22774, 24)/* StreamingInterfaceINTEL */,IR(0, 0),IR(109, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6160,IR(0, 1),IR(22798, 26)/* RegisterMapInterfaceINTEL */,IR(0, 0),IR(179, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6417,IR(0, 1),IR(22824, 23)/* NamedBarrierCountINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6461,IR(0, 1),IR(22847, 22)/* MaximumRegistersINTEL */,IR(0, 0),IR(180, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6462,IR(10, 1),IR(22869, 24)/* MaximumRegistersIdINTEL */,IR(0, 0),IR(180, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6463,IR(38, 1),IR(22944, 27)/* NamedMaximumRegistersINTEL */,IR(0, 0),IR(180, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {0,IR(0, 0),IR(22971, 7)/* Vertex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {1,IR(0, 0),IR(22978, 20)/* TessellationControl */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {2,IR(0, 0),IR(22998, 23)/* TessellationEvaluation */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {3,IR(0, 0),IR(5696, 9)/* Geometry */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {4,IR(0, 0),IR(16163, 9)/* Fragment */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5,IR(0, 0),IR(23021, 10)/* GLCompute */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {6,IR(0, 0),IR(5463, 7)/* Kernel */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5267,IR(0, 0),IR(23031, 7)/* TaskNV */,IR(0, 0),IR(51, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5268,IR(0, 0),IR(23038, 7)/* MeshNV */,IR(0, 0),IR(51, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5313,IR(0, 0),IR(23045, 17)/* RayGenerationKHR */,IR(126, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5314,IR(0, 0),IR(23078, 16)/* IntersectionKHR */,IR(127, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5315,IR(0, 0),IR(23109, 10)/* AnyHitKHR */,IR(128, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5316,IR(0, 0),IR(23128, 14)/* ClosestHitKHR */,IR(129, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5317,IR(0, 0),IR(23155, 8)/* MissKHR */,IR(130, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5318,IR(0, 0),IR(23170, 12)/* CallableKHR */,IR(131, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5364,IR(0, 0),IR(23193, 8)/* TaskEXT */,IR(0, 0),IR(54, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5365,IR(0, 0),IR(23201, 8)/* MeshEXT */,IR(0, 0),IR(54, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {0,IR(0, 0),IR(23209, 9)/* Preserve */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPDENORM_MODE
  {1,IR(0, 0),IR(23218, 12)/* FlushToZero */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPDENORM_MODE
  {0,IR(0, 0),IR(23230, 12)/* BFloat16KHR */,IR(0, 0),IR(90, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {4214,IR(0, 0),IR(23242, 14)/* Float8E4M3EXT */,IR(0, 0),IR(124, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {4215,IR(0, 0),IR(23256, 14)/* Float8E5M2EXT */,IR(0, 0),IR(124, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {0,IR(0, 0),IR(23270, 5)/* IEEE */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPOPERATION_MODE
  {1,IR(0, 0),IR(23275, 4)/* ALT */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPOPERATION_MODE
  {0,IR(0, 0),IR(15759, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {1,IR(0, 0),IR(23279, 7)/* NotNaN */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {2,IR(0, 0),IR(23286, 7)/* NotInf */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {4,IR(0, 0),IR(23293, 4)/* NSZ */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {8,IR(0, 0),IR(23297, 11)/* AllowRecip */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {16,IR(0, 0),IR(23308, 5)/* Fast */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {65536,IR(0, 0),IR(23313, 14)/* AllowContract */,IR(132, 1),IR(181, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {131072,IR(0, 0),IR(23350, 13)/* AllowReassoc */,IR(133, 1),IR(181, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {262144,IR(0, 0),IR(23381, 15)/* AllowTransform */,IR(0, 0),IR(178, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {0,IR(0, 0),IR(23396, 4)/* RTE */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {1,IR(0, 0),IR(23400, 4)/* RTZ */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {2,IR(0, 0),IR(23404, 4)/* RTP */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {3,IR(0, 0),IR(23408, 4)/* RTN */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {1,IR(0, 0),IR(23412, 16)/* Vertical2Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {2,IR(0, 0),IR(23428, 16)/* Vertical4Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {4,IR(0, 0),IR(23444, 18)/* Horizontal2Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {8,IR(0, 0),IR(23462, 18)/* Horizontal4Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {0,IR(0, 0),IR(15759, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {1,IR(0, 0),IR(23480, 7)/* Inline */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {2,IR(0, 0),IR(23487, 11)/* DontInline */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {4,IR(0, 0),IR(23498, 5)/* Pure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {8,IR(0, 0),IR(23503, 6)/* Const */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {65536,IR(0, 0),IR(14766, 11)/* OptNoneEXT */,IR(67, 1),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {0,IR(0, 0),IR(23509, 5)/* Zext */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {1,IR(0, 0),IR(23514, 5)/* Sext */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {2,IR(0, 0),IR(23519, 6)/* ByVal */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {3,IR(0, 0),IR(23525, 5)/* Sret */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {4,IR(0, 0),IR(23530, 8)/* NoAlias */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {5,IR(0, 0),IR(23538, 10)/* NoCapture */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {6,IR(0, 0),IR(23548, 8)/* NoWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {7,IR(0, 0),IR(23556, 12)/* NoReadWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {5940,IR(0, 0),IR(23568, 21)/* RuntimeAlignedALTERA */,IR(134, 1),IR(184, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {0,IR(0, 0),IR(23609, 7)/* Reduce */,IR(0, 0),IR(185, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {1,IR(0, 0),IR(23616, 14)/* InclusiveScan */,IR(0, 0),IR(185, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {2,IR(0, 0),IR(23630, 14)/* ExclusiveScan */,IR(0, 0),IR(185, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {3,IR(0, 0),IR(23644, 16)/* ClusteredReduce */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {6,IR(0, 0),IR(23660, 21)/* PartitionedReduceEXT */,IR(135, 1),IR(189, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {7,IR(0, 0),IR(23701, 28)/* PartitionedInclusiveScanEXT */,IR(136, 1),IR(189, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {8,IR(0, 0),IR(23756, 28)/* PartitionedExclusiveScanEXT */,IR(137, 1),IR(189, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {0,IR(0, 0),IR(23811, 10)/* NoneINTEL */,IR(0, 0),IR(149, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {1,IR(0, 0),IR(23821, 10)/* ReadINTEL */,IR(0, 0),IR(149, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {2,IR(0, 0),IR(23831, 11)/* WriteINTEL */,IR(0, 0),IR(149, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {3,IR(0, 0),IR(23842, 15)/* ReadWriteINTEL */,IR(0, 0),IR(149, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {0,IR(0, 0),IR(15759, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {1,IR(10, 1),IR(23857, 5)/* Bias */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {2,IR(10, 1),IR(23862, 4)/* Lod */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {4,IR(36, 2),IR(23866, 5)/* Grad */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {8,IR(10, 1),IR(23871, 12)/* ConstOffset */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {16,IR(10, 1),IR(17166, 7)/* Offset */,IR(0, 0),IR(190, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {32,IR(10, 1),IR(23883, 13)/* ConstOffsets */,IR(0, 0),IR(190, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {64,IR(10, 1),IR(16963, 7)/* Sample */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {128,IR(10, 1),IR(9296, 7)/* MinLod */,IR(0, 0),IR(191, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {256,IR(4, 1),IR(23896, 19)/* MakeTexelAvailable */,IR(138, 1),IR(192, 1),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {512,IR(4, 1),IR(23937, 17)/* MakeTexelVisible */,IR(139, 1),IR(192, 1),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {1024,IR(0, 0),IR(23974, 16)/* NonPrivateTexel */,IR(140, 1),IR(192, 1),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {2048,IR(0, 0),IR(24009, 14)/* VolatileTexel */,IR(141, 1),IR(192, 1),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {4096,IR(0, 0),IR(24040, 11)/* SignExtend */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {8192,IR(0, 0),IR(24051, 11)/* ZeroExtend */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {16384,IR(0, 0),IR(24062, 12)/* Nontemporal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {65536,IR(10, 1),IR(24074, 8)/* Offsets */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {0,IR(0, 0),IR(24082, 10)/* SnormInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {1,IR(0, 0),IR(24092, 11)/* SnormInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {2,IR(0, 0),IR(24103, 10)/* UnormInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {3,IR(0, 0),IR(24113, 11)/* UnormInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {4,IR(0, 0),IR(24124, 14)/* UnormShort565 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {5,IR(0, 0),IR(24138, 14)/* UnormShort555 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {6,IR(0, 0),IR(24152, 15)/* UnormInt101010 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {7,IR(0, 0),IR(24167, 11)/* SignedInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {8,IR(0, 0),IR(24178, 12)/* SignedInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {9,IR(0, 0),IR(24190, 12)/* SignedInt32 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {10,IR(0, 0),IR(24202, 13)/* UnsignedInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {11,IR(0, 0),IR(24215, 14)/* UnsignedInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {12,IR(0, 0),IR(24229, 14)/* UnsignedInt32 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {13,IR(0, 0),IR(24243, 10)/* HalfFloat */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {14,IR(0, 0),IR(15656, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {15,IR(0, 0),IR(24253, 11)/* UnormInt24 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {16,IR(0, 0),IR(24264, 17)/* UnormInt101010_2 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {17,IR(0, 0),IR(24281, 16)/* UnormInt10X6EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {19,IR(0, 0),IR(24297, 20)/* UnsignedIntRaw10EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {20,IR(0, 0),IR(24317, 20)/* UnsignedIntRaw12EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {21,IR(0, 0),IR(24337, 20)/* UnormInt2_101010EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {22,IR(0, 0),IR(24357, 19)/* UnsignedInt10X6EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {23,IR(0, 0),IR(24376, 19)/* UnsignedInt12X4EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {24,IR(0, 0),IR(24395, 19)/* UnsignedInt14X2EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {25,IR(0, 0),IR(24414, 16)/* UnormInt12X4EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {26,IR(0, 0),IR(24430, 16)/* UnormInt14X2EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {0,IR(0, 0),IR(24446, 2)/* R */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {1,IR(0, 0),IR(24448, 2)/* A */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {2,IR(0, 0),IR(24450, 3)/* RG */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {3,IR(0, 0),IR(24453, 3)/* RA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {4,IR(0, 0),IR(24456, 4)/* RGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {5,IR(0, 0),IR(24460, 5)/* RGBA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {6,IR(0, 0),IR(24465, 5)/* BGRA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {7,IR(0, 0),IR(24470, 5)/* ARGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {8,IR(0, 0),IR(24475, 10)/* Intensity */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {9,IR(0, 0),IR(24485, 10)/* Luminance */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {10,IR(0, 0),IR(24495, 3)/* Rx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {11,IR(0, 0),IR(24498, 4)/* RGx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {12,IR(0, 0),IR(24502, 5)/* RGBx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {13,IR(0, 0),IR(24507, 6)/* Depth */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {14,IR(0, 0),IR(24513, 13)/* DepthStencil */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {15,IR(0, 0),IR(24526, 5)/* sRGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {16,IR(0, 0),IR(24531, 6)/* sRGBx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {17,IR(0, 0),IR(24537, 6)/* sRGBA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {18,IR(0, 0),IR(24543, 6)/* sBGRA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {19,IR(0, 0),IR(24549, 5)/* ABGR */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {0,IR(0, 0),IR(24554, 28)/* InitOnDeviceReprogramALTERA */,IR(142, 1),IR(150, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {1,IR(0, 0),IR(24609, 24)/* InitOnDeviceResetALTERA */,IR(143, 1),IR(150, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {0,IR(0, 0),IR(24656, 7)/* NoWait */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {1,IR(0, 0),IR(24663, 11)/* WaitKernel */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {2,IR(0, 0),IR(24674, 14)/* WaitWorkGroup */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {0,IR(0, 0),IR(15759, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {1,IR(0, 0),IR(24688, 12)/* CmdExecTime */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {0,IR(0, 0),IR(15759, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {1,IR(0, 0),IR(24700, 13)/* MayUsePrintf */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {0,IR(0, 0),IR(24713, 7)/* Export */,IR(0, 0),IR(123, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {1,IR(0, 0),IR(24720, 7)/* Import */,IR(0, 0),IR(123, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {2,IR(0, 0),IR(24727, 12)/* LinkOnceODR */,IR(0, 0),IR(123, 1),IR(191, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {0,IR(0, 0),IR(24739, 14)/* UncachedINTEL */,IR(0, 0),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {1,IR(0, 0),IR(24753, 12)/* CachedINTEL */,IR(0, 0),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {2,IR(0, 0),IR(24765, 15)/* StreamingINTEL */,IR(0, 0),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {3,IR(0, 0),IR(24780, 25)/* InvalidateAfterReadINTEL */,IR(0, 0),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {4,IR(0, 0),IR(24805, 17)/* ConstCachedINTEL */,IR(0, 0),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {0,IR(0, 0),IR(15759, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {1,IR(0, 0),IR(24822, 7)/* Unroll */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {2,IR(0, 0),IR(24829, 11)/* DontUnroll */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {4,IR(0, 0),IR(24840, 19)/* DependencyInfinite */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {8,IR(0, 1),IR(24859, 17)/* DependencyLength */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {16,IR(0, 1),IR(24876, 14)/* MinIterations */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {32,IR(0, 1),IR(24890, 14)/* MaxIterations */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {64,IR(0, 1),IR(24904, 18)/* IterationMultiple */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {128,IR(0, 1),IR(24922, 10)/* PeelCount */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {256,IR(0, 1),IR(24932, 13)/* PartialCount */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {65536,IR(0, 1),IR(19515, 25)/* InitiationIntervalALTERA */,IR(102, 1),IR(193, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {131072,IR(0, 1),IR(19564, 21)/* MaxConcurrencyALTERA */,IR(103, 1),IR(193, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {262144,IR(0, 1),IR(24945, 22)/* DependencyArrayALTERA */,IR(144, 1),IR(193, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {524288,IR(0, 1),IR(19605, 21)/* PipelineEnableALTERA */,IR(104, 1),IR(193, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {1048576,IR(0, 1),IR(24988, 19)/* LoopCoalesceALTERA */,IR(145, 1),IR(193, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {2097152,IR(0, 1),IR(25025, 22)/* MaxInterleavingALTERA */,IR(146, 1),IR(193, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {4194304,IR(0, 1),IR(25068, 27)/* SpeculatedIterationsALTERA */,IR(147, 1),IR(193, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {8388608,IR(0, 0),IR(25121, 15)/* NoFusionALTERA */,IR(148, 1),IR(193, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {16777216,IR(0, 1),IR(25150, 16)/* LoopCountALTERA */,IR(149, 1),IR(193, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {33554432,IR(0, 1),IR(25181, 27)/* MaxReinvocationDelayALTERA */,IR(150, 1),IR(193, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {0,IR(0, 0),IR(15759, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {1,IR(0, 0),IR(25234, 29)/* MatrixASignedComponentsINTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {2,IR(0, 0),IR(25263, 29)/* MatrixBSignedComponentsINTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {4,IR(0, 0),IR(25292, 21)/* MatrixCBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {8,IR(0, 0),IR(25313, 26)/* MatrixResultBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {16,IR(0, 0),IR(25339, 23)/* MatrixAPackedInt8INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {32,IR(0, 0),IR(25362, 23)/* MatrixBPackedInt8INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {64,IR(0, 0),IR(25385, 23)/* MatrixAPackedInt4INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {128,IR(0, 0),IR(25408, 23)/* MatrixBPackedInt4INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {256,IR(0, 0),IR(25431, 17)/* MatrixATF32INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {512,IR(0, 0),IR(25448, 17)/* MatrixBTF32INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {1024,IR(0, 0),IR(25465, 26)/* MatrixAPackedFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {2048,IR(0, 0),IR(25491, 26)/* MatrixBPackedFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {4096,IR(0, 0),IR(25517, 27)/* MatrixAPackedBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {8192,IR(0, 0),IR(25544, 27)/* MatrixBPackedBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {0,IR(0, 0),IR(15759, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {1,IR(0, 0),IR(16997, 9)/* Volatile */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {2,IR(0, 1),IR(25571, 8)/* Aligned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {4,IR(0, 0),IR(24062, 12)/* Nontemporal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {8,IR(4, 1),IR(25579, 21)/* MakePointerAvailable */,IR(151, 1),IR(192, 1),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {16,IR(4, 1),IR(25624, 19)/* MakePointerVisible */,IR(152, 1),IR(192, 1),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {32,IR(0, 0),IR(25665, 18)/* NonPrivatePointer */,IR(153, 1),IR(192, 1),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {65536,IR(10, 1),IR(25704, 20)/* AliasScopeINTELMask */,IR(0, 0),IR(141, 1),IR(127, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {131072,IR(10, 1),IR(25724, 17)/* NoAliasINTELMask */,IR(0, 0),IR(141, 1),IR(127, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {0,IR(0, 0),IR(25741, 7)/* Simple */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {1,IR(0, 0),IR(25748, 8)/* GLSL450 */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {2,IR(0, 0),IR(25756, 7)/* OpenCL */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {3,IR(0, 0),IR(25763, 7)/* Vulkan */,IR(154, 1),IR(192, 1),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {0,IR(0, 0),IR(25780, 8)/* Relaxed */,IR(155, 1),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {2,IR(0, 0),IR(25788, 8)/* Acquire */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {4,IR(0, 0),IR(25796, 8)/* Release */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {8,IR(0, 0),IR(25804, 15)/* AcquireRelease */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {16,IR(0, 0),IR(25819, 23)/* SequentiallyConsistent */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {64,IR(0, 0),IR(25842, 14)/* UniformMemory */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {128,IR(0, 0),IR(25856, 15)/* SubgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {256,IR(0, 0),IR(25871, 16)/* WorkgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {512,IR(0, 0),IR(25887, 21)/* CrossWorkgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {1024,IR(0, 0),IR(25908, 20)/* AtomicCounterMemory */,IR(0, 0),IR(83, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {2048,IR(0, 0),IR(25928, 12)/* ImageMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {4096,IR(0, 0),IR(25940, 13)/* OutputMemory */,IR(156, 1),IR(192, 1),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {8192,IR(0, 0),IR(25969, 14)/* MakeAvailable */,IR(157, 1),IR(192, 1),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {16384,IR(0, 0),IR(26000, 12)/* MakeVisible */,IR(158, 1),IR(192, 1),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {32768,IR(0, 0),IR(16997, 9)/* Volatile */,IR(0, 0),IR(192, 1),IR(80, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {0,IR(0, 0),IR(26027, 10)/* AutoINTEL */,IR(0, 0),IR(180, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS
  {0,IR(0, 0),IR(26037, 5)/* WRAP */,IR(0, 0),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {1,IR(0, 0),IR(26042, 4)/* SAT */,IR(0, 0),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {2,IR(0, 0),IR(26046, 9)/* SAT_ZERO */,IR(0, 0),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {3,IR(0, 0),IR(26055, 8)/* SAT_SYM */,IR(0, 0),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {0,IR(0, 0),IR(26063, 25)/* PackedVectorFormat4x8Bit */,IR(159, 1),IR(1, 0),IR(144, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {0,IR(0, 0),IR(26116, 4)/* TRN */,IR(0, 0),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {1,IR(0, 0),IR(26120, 9)/* TRN_ZERO */,IR(0, 0),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {2,IR(0, 0),IR(26129, 4)/* RND */,IR(0, 0),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {3,IR(0, 0),IR(26133, 9)/* RND_ZERO */,IR(0, 0),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {4,IR(0, 0),IR(26142, 8)/* RND_INF */,IR(0, 0),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {5,IR(0, 0),IR(26150, 12)/* RND_MIN_INF */,IR(0, 0),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {6,IR(0, 0),IR(26162, 9)/* RND_CONV */,IR(0, 0),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {7,IR(0, 0),IR(26171, 13)/* RND_CONV_ODD */,IR(0, 0),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {0,IR(0, 0),IR(15759, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {1,IR(0, 0),IR(26184, 25)/* RobustnessPerComponentNV */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {2,IR(0, 0),IR(26209, 23)/* RobustnessPerElementNV */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {0,IR(0, 0),IR(16511, 8)/* NoneKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {1,IR(0, 0),IR(26232, 10)/* OpaqueKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {2,IR(0, 0),IR(26242, 12)/* NoOpaqueKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {4,IR(0, 0),IR(26254, 23)/* TerminateOnFirstHitKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {8,IR(0, 0),IR(26277, 24)/* SkipClosestHitShaderKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {16,IR(0, 0),IR(26301, 27)/* CullBackFacingTrianglesKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {32,IR(0, 0),IR(26328, 28)/* CullFrontFacingTrianglesKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {64,IR(0, 0),IR(26356, 14)/* CullOpaqueKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {128,IR(0, 0),IR(26370, 16)/* CullNoOpaqueKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {256,IR(0, 0),IR(26386, 17)/* SkipTrianglesKHR */,IR(160, 1),IR(196, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {512,IR(0, 0),IR(26427, 13)/* SkipAABBsKHR */,IR(0, 0),IR(196, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {1024,IR(0, 0),IR(26440, 30)/* ForceOpacityMicromap2StateEXT */,IR(0, 0),IR(197, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {0,IR(0, 0),IR(26470, 41)/* RayQueryCandidateIntersectionTriangleKHR */,IR(0, 0),IR(198, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {1,IR(0, 0),IR(26511, 37)/* RayQueryCandidateIntersectionAABBKHR */,IR(0, 0),IR(198, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {0,IR(0, 0),IR(26548, 37)/* RayQueryCommittedIntersectionNoneKHR */,IR(0, 0),IR(198, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {1,IR(0, 0),IR(26585, 41)/* RayQueryCommittedIntersectionTriangleKHR */,IR(0, 0),IR(198, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {2,IR(0, 0),IR(26626, 42)/* RayQueryCommittedIntersectionGeneratedKHR */,IR(0, 0),IR(198, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {0,IR(0, 0),IR(26668, 33)/* RayQueryCandidateIntersectionKHR */,IR(0, 0),IR(198, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {1,IR(0, 0),IR(26701, 33)/* RayQueryCommittedIntersectionKHR */,IR(0, 0),IR(198, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {0,IR(0, 0),IR(15759, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {1,IR(0, 0),IR(26734, 12)/* ClampToEdge */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {2,IR(0, 0),IR(26746, 6)/* Clamp */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {3,IR(0, 0),IR(26752, 7)/* Repeat */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {4,IR(0, 0),IR(26759, 15)/* RepeatMirrored */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {0,IR(0, 0),IR(26774, 8)/* Nearest */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {1,IR(0, 0),IR(26782, 7)/* Linear */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {0,IR(0, 0),IR(26789, 8)/* Unknown */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {1,IR(0, 0),IR(26797, 8)/* Rgba32f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {2,IR(0, 0),IR(26805, 8)/* Rgba16f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {3,IR(0, 0),IR(26813, 5)/* R32f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {4,IR(0, 0),IR(26818, 6)/* Rgba8 */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {5,IR(0, 0),IR(26824, 11)/* Rgba8Snorm */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {6,IR(0, 0),IR(26835, 6)/* Rg32f */,IR(0, 0),IR(199, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {7,IR(0, 0),IR(26841, 6)/* Rg16f */,IR(0, 0),IR(199, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {8,IR(0, 0),IR(26847, 13)/* R11fG11fB10f */,IR(0, 0),IR(199, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {9,IR(0, 0),IR(26860, 5)/* R16f */,IR(0, 0),IR(199, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {10,IR(0, 0),IR(26865, 7)/* Rgba16 */,IR(0, 0),IR(199, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {11,IR(0, 0),IR(26872, 8)/* Rgb10A2 */,IR(0, 0),IR(199, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {12,IR(0, 0),IR(26880, 5)/* Rg16 */,IR(0, 0),IR(199, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {13,IR(0, 0),IR(26885, 4)/* Rg8 */,IR(0, 0),IR(199, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {14,IR(0, 0),IR(26889, 4)/* R16 */,IR(0, 0),IR(199, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {15,IR(0, 0),IR(26893, 3)/* R8 */,IR(0, 0),IR(199, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {16,IR(0, 0),IR(26896, 12)/* Rgba16Snorm */,IR(0, 0),IR(199, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {17,IR(0, 0),IR(26908, 10)/* Rg16Snorm */,IR(0, 0),IR(199, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {18,IR(0, 0),IR(26918, 9)/* Rg8Snorm */,IR(0, 0),IR(199, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {19,IR(0, 0),IR(26927, 9)/* R16Snorm */,IR(0, 0),IR(199, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {20,IR(0, 0),IR(26936, 8)/* R8Snorm */,IR(0, 0),IR(199, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {21,IR(0, 0),IR(26944, 8)/* Rgba32i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {22,IR(0, 0),IR(26952, 8)/* Rgba16i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {23,IR(0, 0),IR(26960, 7)/* Rgba8i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {24,IR(0, 0),IR(26967, 5)/* R32i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {25,IR(0, 0),IR(26972, 6)/* Rg32i */,IR(0, 0),IR(199, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {26,IR(0, 0),IR(26978, 6)/* Rg16i */,IR(0, 0),IR(199, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {27,IR(0, 0),IR(26984, 5)/* Rg8i */,IR(0, 0),IR(199, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {28,IR(0, 0),IR(26989, 5)/* R16i */,IR(0, 0),IR(199, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {29,IR(0, 0),IR(26994, 4)/* R8i */,IR(0, 0),IR(199, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {30,IR(0, 0),IR(26998, 9)/* Rgba32ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {31,IR(0, 0),IR(27007, 9)/* Rgba16ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {32,IR(0, 0),IR(27016, 8)/* Rgba8ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {33,IR(0, 0),IR(27024, 6)/* R32ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {34,IR(0, 0),IR(27030, 10)/* Rgb10a2ui */,IR(0, 0),IR(199, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {35,IR(0, 0),IR(27040, 7)/* Rg32ui */,IR(0, 0),IR(199, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {36,IR(0, 0),IR(27047, 7)/* Rg16ui */,IR(0, 0),IR(199, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {37,IR(0, 0),IR(27054, 6)/* Rg8ui */,IR(0, 0),IR(199, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {38,IR(0, 0),IR(27060, 6)/* R16ui */,IR(0, 0),IR(199, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {39,IR(0, 0),IR(27066, 5)/* R8ui */,IR(0, 0),IR(199, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {40,IR(0, 0),IR(27071, 6)/* R64ui */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {41,IR(0, 0),IR(27077, 5)/* R64i */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {0,IR(0, 0),IR(27082, 12)/* CrossDevice */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {1,IR(0, 0),IR(27094, 7)/* Device */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {2,IR(0, 0),IR(27101, 10)/* Workgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {3,IR(0, 0),IR(27111, 9)/* Subgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {4,IR(0, 0),IR(27120, 11)/* Invocation */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {5,IR(0, 0),IR(27131, 12)/* QueueFamily */,IR(161, 1),IR(192, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {6,IR(0, 0),IR(27158, 14)/* ShaderCallKHR */,IR(0, 0),IR(61, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {0,IR(0, 0),IR(15759, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {1,IR(0, 0),IR(27172, 8)/* Flatten */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {2,IR(0, 0),IR(27180, 12)/* DontFlatten */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {1,IR(0, 0),IR(27192, 29)/* IdentifierPossibleDuplicates */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS
  {0,IR(0, 0),IR(15628, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(15640, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(15648, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {3,IR(0, 0),IR(15656, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(15662, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(15669, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(15680, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(15689, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(15702, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(15708, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(15718, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(15724, 15)/* ImportedModule */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {1,IR(0, 0),IR(15739, 20)/* ImportedDeclaration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {0,IR(0, 0),IR(15759, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(15764, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(15780, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(15794, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(15807, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(15819, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(15836, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(15848, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(15863, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(15876, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(15891, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(15909, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(15926, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(15947, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(15967, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(15987, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {16384,IR(0, 0),IR(16003, 16)/* FlagIsEnumClass */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {32768,IR(0, 0),IR(16019, 20)/* FlagTypePassByValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {65536,IR(0, 0),IR(16039, 24)/* FlagTypePassByReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {131072,IR(0, 0),IR(27221, 26)/* FlagUnknownPhysicalLayout */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(16063, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {1,IR(0, 0),IR(16069, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {2,IR(0, 0),IR(16074, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {3,IR(10, 1),IR(16113, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {4,IR(36, 2),IR(16124, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {5,IR(0, 0),IR(16133, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {6,IR(0, 0),IR(16138, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {7,IR(0, 0),IR(16145, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {8,IR(10, 1),IR(16156, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {9,IR(36, 2),IR(16163, 9)/* Fragment */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {0,IR(0, 0),IR(16172, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(16182, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(16195, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {3,IR(0, 0),IR(16208, 11)/* AtomicType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(26789, 8)/* Unknown */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {1,IR(0, 0),IR(27247, 5)/* ESSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {2,IR(0, 0),IR(27252, 5)/* GLSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {3,IR(0, 0),IR(27257, 9)/* OpenCL_C */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {4,IR(0, 0),IR(27266, 11)/* OpenCL_CPP */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {5,IR(0, 0),IR(27277, 5)/* HLSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {6,IR(0, 0),IR(27282, 15)/* CPP_for_OpenCL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {7,IR(0, 0),IR(27297, 5)/* SYCL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {8,IR(0, 0),IR(27302, 7)/* HERO_C */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {9,IR(0, 0),IR(27309, 5)/* NZSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {10,IR(0, 0),IR(27314, 5)/* WGSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {11,IR(0, 0),IR(27319, 6)/* Slang */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {12,IR(0, 0),IR(27325, 4)/* Zig */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {13,IR(0, 0),IR(27329, 5)/* Rust */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {0,IR(0, 0),IR(27334, 16)/* UniformConstant */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {1,IR(0, 0),IR(27350, 6)/* Input */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {2,IR(0, 0),IR(17048, 8)/* Uniform */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {3,IR(0, 0),IR(27356, 7)/* Output */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4,IR(0, 0),IR(27101, 10)/* Workgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5,IR(0, 0),IR(27363, 15)/* CrossWorkgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {6,IR(0, 0),IR(27378, 8)/* Private */,IR(0, 0),IR(201, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {7,IR(0, 0),IR(27386, 9)/* Function */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {8,IR(0, 0),IR(27395, 8)/* Generic */,IR(0, 0),IR(203, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {9,IR(0, 0),IR(27403, 13)/* PushConstant */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {10,IR(0, 0),IR(27416, 14)/* AtomicCounter */,IR(0, 0),IR(83, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {11,IR(0, 0),IR(27430, 6)/* Image */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {12,IR(0, 0),IR(27436, 14)/* StorageBuffer */,IR(0, 0),IR(3, 1),IR(192, 2),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4172,IR(0, 0),IR(27450, 13)/* TileImageEXT */,IR(0, 0),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4491,IR(0, 0),IR(27463, 19)/* TileAttachmentQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5068,IR(0, 0),IR(27482, 16)/* NodePayloadAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5328,IR(0, 0),IR(27498, 16)/* CallableDataKHR */,IR(162, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5329,IR(0, 0),IR(27529, 24)/* IncomingCallableDataKHR */,IR(163, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5338,IR(0, 0),IR(27576, 14)/* RayPayloadKHR */,IR(164, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5339,IR(0, 0),IR(27603, 16)/* HitAttributeKHR */,IR(165, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5342,IR(0, 0),IR(27634, 22)/* IncomingRayPayloadKHR */,IR(166, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5343,IR(0, 0),IR(27677, 22)/* ShaderRecordBufferKHR */,IR(167, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5349,IR(0, 0),IR(27720, 22)/* PhysicalStorageBuffer */,IR(168, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5385,IR(0, 0),IR(27767, 21)/* HitObjectAttributeNV */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5402,IR(0, 0),IR(27788, 24)/* TaskPayloadWorkgroupEXT */,IR(0, 0),IR(54, 1),IR(23, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5411,IR(0, 0),IR(27812, 22)/* HitObjectAttributeEXT */,IR(0, 0),IR(131, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5605,IR(0, 0),IR(27834, 17)/* CodeSectionINTEL */,IR(0, 0),IR(204, 1),IR(101, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5936,IR(0, 0),IR(27851, 17)/* DeviceOnlyALTERA */,IR(169, 1),IR(205, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5937,IR(0, 0),IR(27884, 15)/* HostOnlyALTERA */,IR(170, 1),IR(205, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {0,IR(0, 0),IR(24739, 14)/* UncachedINTEL */,IR(0, 0),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {1,IR(0, 0),IR(27913, 18)/* WriteThroughINTEL */,IR(0, 0),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {2,IR(0, 0),IR(27931, 15)/* WriteBackINTEL */,IR(0, 0),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {3,IR(0, 0),IR(24765, 15)/* StreamingINTEL */,IR(0, 0),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {0,IR(0, 0),IR(15759, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {1,IR(10, 1),IR(27946, 11)/* TensorView */,IR(0, 0),IR(206, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {2,IR(10, 1),IR(27957, 11)/* DecodeFunc */,IR(0, 0),IR(207, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {0,IR(0, 0),IR(27968, 10)/* Undefined */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {1,IR(0, 0),IR(17006, 9)/* Constant */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {2,IR(0, 0),IR(26734, 12)/* ClampToEdge */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {3,IR(0, 0),IR(26752, 7)/* Repeat */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {4,IR(0, 0),IR(26759, 15)/* RepeatMirrored */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {0,IR(0, 0),IR(27978, 8)/* NoneARM */,IR(0, 0),IR(208, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {1,IR(0, 0),IR(27986, 15)/* NontemporalARM */,IR(0, 0),IR(208, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {2,IR(10, 1),IR(28001, 20)/* OutOfBoundsValueARM */,IR(0, 0),IR(208, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {4,IR(10, 1),IR(28021, 24)/* MakeElementAvailableARM */,IR(0, 0),IR(208, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {8,IR(10, 1),IR(28045, 22)/* MakeElementVisibleARM */,IR(0, 0),IR(208, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {16,IR(0, 0),IR(28067, 21)/* NonPrivateElementARM */,IR(0, 0),IR(208, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
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
    case SPV_OPERAND_TYPE_CAPABILITY: return IR(135, 280);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(415, 8);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(423, 3);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(426, 2);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS: return IR(428, 19);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION: return IR(447, 10);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(457, 4);
    case SPV_OPERAND_TYPE_COMPONENT_TYPE: return IR(461, 15);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT: return IR(476, 4);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS: return IR(480, 6);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE: return IR(486, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE: return IR(489, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT: return IR(492, 4);
    case SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(496, 8);
    case SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE: return IR(504, 3);
    case SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS: return IR(507, 16);
    case SPV_OPERAND_TYPE_DEBUG_OPERATION: return IR(523, 9);
    case SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER: return IR(532, 3);
    case SPV_OPERAND_TYPE_DECORATION: return IR(535, 149);
    case SPV_OPERAND_TYPE_DIMENSIONALITY: return IR(684, 8);
    case SPV_OPERAND_TYPE_EXECUTION_MODE: return IR(692, 97);
    case SPV_OPERAND_TYPE_EXECUTION_MODEL: return IR(789, 17);
    case SPV_OPERAND_TYPE_FPDENORM_MODE: return IR(806, 2);
    case SPV_OPERAND_TYPE_FPENCODING: return IR(808, 3);
    case SPV_OPERAND_TYPE_FPOPERATION_MODE: return IR(811, 2);
    case SPV_OPERAND_TYPE_FP_FAST_MATH_MODE: return IR(813, 9);
    case SPV_OPERAND_TYPE_FP_ROUNDING_MODE: return IR(822, 4);
    case SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE: return IR(826, 4);
    case SPV_OPERAND_TYPE_FUNCTION_CONTROL: return IR(830, 6);
    case SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE: return IR(836, 9);
    case SPV_OPERAND_TYPE_GROUP_OPERATION: return IR(845, 7);
    case SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER: return IR(852, 4);
    case SPV_OPERAND_TYPE_IMAGE: return IR(856, 17);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE: return IR(873, 26);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER: return IR(899, 20);
    case SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER: return IR(919, 2);
    case SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS: return IR(921, 3);
    case SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO: return IR(924, 2);
    case SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS: return IR(926, 2);
    case SPV_OPERAND_TYPE_LINKAGE_TYPE: return IR(928, 3);
    case SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL: return IR(931, 5);
    case SPV_OPERAND_TYPE_LOOP_CONTROL: return IR(936, 20);
    case SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(956, 15);
    case SPV_OPERAND_TYPE_MEMORY_ACCESS: return IR(971, 9);
    case SPV_OPERAND_TYPE_MEMORY_MODEL: return IR(980, 4);
    case SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID: return IR(984, 15);
    case SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS: return IR(999, 1);
    case SPV_OPERAND_TYPE_OVERFLOW_MODES: return IR(1000, 4);
    case SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT: return IR(1004, 1);
    case SPV_OPERAND_TYPE_QUANTIZATION_MODES: return IR(1005, 8);
    case SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS: return IR(1013, 3);
    case SPV_OPERAND_TYPE_RAY_FLAGS: return IR(1016, 12);
    case SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE: return IR(1028, 2);
    case SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE: return IR(1030, 3);
    case SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION: return IR(1033, 2);
    case SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE: return IR(1035, 5);
    case SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE: return IR(1040, 2);
    case SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT: return IR(1042, 42);
    case SPV_OPERAND_TYPE_SCOPE_ID: return IR(1084, 7);
    case SPV_OPERAND_TYPE_SELECTION_CONTROL: return IR(1091, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS: return IR(1094, 1);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(1095, 8);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(1103, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(1106, 2);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS: return IR(1108, 20);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION: return IR(1128, 10);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(1138, 4);
    case SPV_OPERAND_TYPE_SOURCE_LANGUAGE: return IR(1142, 14);
    case SPV_OPERAND_TYPE_STORAGE_CLASS: return IR(1156, 29);
    case SPV_OPERAND_TYPE_STORE_CACHE_CONTROL: return IR(1185, 4);
    case SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS: return IR(1189, 3);
    case SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE: return IR(1192, 5);
    case SPV_OPERAND_TYPE_TENSOR_OPERANDS: return IR(1197, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_IMAGE: return IR(856, 17);
    case SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS: return IR(971, 9);
    case SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT: return IR(1004, 1);
    case SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS: return IR(480, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(956, 15);
    case SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS: return IR(1013, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_FPENCODING: return IR(808, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS: return IR(1197, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_CAPABILITY: return IR(135, 280);
    default: break;
  }
  return IR(0,0);
}

// Operand names and index into kOperandsByValue, ordered by (operand kind, name)
// The fields in order are:
//   name, either the primary name or an alias, indexing into kStrings
//   index into the kOperandsByValue array
static const std::array<NameIndex, 1378> kOperandNames{{
  {IR(5454, 9), 0}, // 0 ReadOnly in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(5480, 10), 2}, // 1 ReadWrite in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(5470, 10), 1}, // 2 WriteOnly in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(5490, 8), 3}, // 3 Logical in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5498, 11), 4}, // 4 Physical32 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5519, 11), 5}, // 5 Physical64 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5530, 24), 6}, // 6 PhysicalStorageBuffer64 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5554, 27), 6}, // 7 PhysicalStorageBuffer64EXT in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(7513, 13), 94}, // 8 BaryCoordKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7526, 12), 94}, // 9 BaryCoordNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6859, 20), 68}, // 10 BaryCoordNoPerspAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6879, 28), 69}, // 11 BaryCoordNoPerspCentroidAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7561, 20), 95}, // 12 BaryCoordNoPerspKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7581, 19), 95}, // 13 BaryCoordNoPerspNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6907, 26), 70}, // 14 BaryCoordNoPerspSampleAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7004, 22), 74}, // 15 BaryCoordPullModelAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6933, 19), 71}, // 16 BaryCoordSmoothAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6952, 27), 72}, // 17 BaryCoordSmoothCentroidAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6979, 25), 73}, // 18 BaryCoordSmoothSampleAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6663, 13), 59}, // 19 BaseInstance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6637, 11), 58}, // 20 BaseVertex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5638, 13), 9}, // 21 ClipDistance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7420, 22), 89}, // 22 ClipDistancePerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8719, 12), 133}, // 23 ClusterIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6401, 13), 49}, // 24 CoreCountARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6375, 10), 48}, // 25 CoreIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6414, 13), 50}, // 26 CoreMaxIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5651, 13), 10}, // 27 CullDistance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7442, 22), 90}, // 28 CullDistancePerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8772, 12), 134}, // 29 CullMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7768, 17), 101}, // 30 CullPrimitiveEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8172, 17), 115}, // 31 CurrentRayTimeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6733, 12), 62}, // 32 DeviceIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6676, 10), 60}, // 33 DrawIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6165, 22), 37}, // 34 EnqueuedWorkgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5935, 10), 21}, // 35 FragCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6021, 10), 27}, // 36 FragDepth in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7646, 23), 97}, // 37 FragInvocationCountEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7600, 12), 96}, // 38 FragSizeEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7026, 18), 75}, // 39 FragStencilRefEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7612, 15), 96}, // 40 FragmentSizeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5956, 12), 23}, // 41 FrontFacing in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7332, 16), 85}, // 42 FullyCoveredEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6106, 19), 33}, // 43 GlobalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6200, 15), 39}, // 44 GlobalLinearId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6187, 13), 38}, // 45 GlobalOffset in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6154, 11), 36}, // 46 GlobalSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6031, 17), 28}, // 47 HelperInvocation in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8474, 11), 122}, // 48 HitIsLSSNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8432, 14), 121}, // 49 HitIsSphereNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8654, 33), 130}, // 50 HitKindBackFacingMicroTriangleNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8620, 34), 129}, // 51 HitKindFrontFacingMicroTriangleNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8151, 11), 114}, // 52 HitKindKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8162, 10), 114}, // 53 HitKindNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8602, 18), 128}, // 54 HitLSSPositionsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8705, 14), 132}, // 55 HitLSSRadiiNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8336, 37), 118}, // 56 HitMicroTriangleVertexBarycentricsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8269, 34), 117}, // 57 HitMicroTriangleVertexPositionsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8524, 20), 123}, // 58 HitSpherePositionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8687, 18), 131}, // 59 HitSphereRadiusNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8144, 7), 113}, // 60 HitTNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8212, 30), 116}, // 61 HitTriangleVertexPositionsKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8373, 20), 119}, // 62 IncomingRayFlagsKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8393, 19), 119}, // 63 IncomingRayFlagsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8033, 23), 110}, // 64 InstanceCustomIndexKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8056, 22), 110}, // 65 InstanceCustomIndexNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5673, 11), 12}, // 66 InstanceId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6361, 14), 47}, // 67 InstanceIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5774, 13), 14}, // 68 InvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7669, 22), 97}, // 69 InvocationsPerPixelNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7785, 12), 102}, // 70 LaunchIdKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7797, 11), 102}, // 71 LaunchIdNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7808, 14), 103}, // 72 LaunchSizeKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7822, 13), 103}, // 73 LaunchSizeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5787, 6), 15}, // 74 Layer in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7464, 15), 91}, // 75 LayerPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6088, 18), 32}, // 76 LocalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6125, 21), 34}, // 77 LocalInvocationIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7479, 16), 92}, // 78 MeshViewCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7495, 18), 93}, // 79 MeshViewIndicesNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6291, 21), 43}, // 80 NumEnqueuedSubgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6278, 13), 42}, // 81 NumSubgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6048, 14), 29}, // 82 NumWorkgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7948, 22), 107}, // 83 ObjectRayDirectionKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7970, 21), 107}, // 84 ObjectRayDirectionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7911, 19), 106}, // 85 ObjectRayOriginKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7930, 18), 106}, // 86 ObjectRayOriginNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8078, 17), 111}, // 87 ObjectToWorldKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8095, 16), 111}, // 88 ObjectToWorldNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5921, 14), 20}, // 89 PatchVertices in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5945, 11), 22}, // 90 PointCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5628, 10), 8}, // 91 PointSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5612, 9), 7}, // 92 Position in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7272, 18), 83}, // 93 PositionPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7384, 17), 87}, // 94 PrimitiveCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5684, 12), 13}, // 95 PrimitiveId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7401, 19), 88}, // 96 PrimitiveIndicesNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7716, 24), 99}, // 97 PrimitiveLineIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7691, 25), 98}, // 98 PrimitivePointIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6686, 24), 61}, // 99 PrimitiveShadingRateKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7740, 28), 100}, // 100 PrimitiveTriangleIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8412, 20), 120}, // 101 RayGeometryIndexKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8012, 11), 109}, // 102 RayTmaxKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8023, 10), 109}, // 103 RayTmaxNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7991, 11), 108}, // 104 RayTminKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8002, 10), 108}, // 105 RayTminNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7061, 29), 76}, // 106 RemainingRecursionLevelsAMDX in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7157, 16), 79}, // 107 ResourceHeapEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8576, 10), 125}, // 108 SMCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8595, 7), 127}, // 109 SMIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5968, 9), 24}, // 110 SampleId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6010, 11), 26}, // 111 SampleMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5995, 15), 25}, // 112 SamplePosition in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7124, 15), 78}, // 113 SamplerHeapEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7209, 20), 81}, // 114 SecondaryPositionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7248, 24), 82}, // 115 SecondaryViewportMaskNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7108, 16), 77}, // 116 ShaderIndexAMDX in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6777, 15), 64}, // 117 ShadingRateKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6450, 15), 53}, // 118 SubgroupEqMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6465, 18), 53}, // 119 SubgroupEqMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6505, 15), 54}, // 120 SubgroupGeMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6520, 18), 54}, // 121 SubgroupGeMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6538, 15), 55}, // 122 SubgroupGtMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6553, 18), 55}, // 123 SubgroupGtMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6312, 11), 44}, // 124 SubgroupId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6571, 15), 56}, // 125 SubgroupLeMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6586, 18), 56}, // 126 SubgroupLeMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6323, 26), 45}, // 127 SubgroupLocalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6604, 15), 57}, // 128 SubgroupLtMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6619, 18), 57}, // 129 SubgroupLtMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6262, 16), 41}, // 130 SubgroupMaxSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6215, 13), 40}, // 131 SubgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7372, 12), 86}, // 132 TaskCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5911, 10), 19}, // 133 TessCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5896, 15), 18}, // 134 TessLevelInner in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5881, 15), 17}, // 135 TessLevelOuter in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6841, 18), 67}, // 136 TileApronSizeQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6823, 18), 66}, // 137 TileDimensionQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6792, 15), 65}, // 138 TileOffsetQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5664, 9), 11}, // 139 VertexId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6349, 12), 46}, // 140 VertexIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6757, 10), 63}, // 141 ViewIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5833, 14), 16}, // 142 ViewportIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7173, 15), 80}, // 143 ViewportMaskNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7310, 22), 84}, // 144 ViewportMaskPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6427, 10), 51}, // 145 WarpIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8586, 9), 126}, // 146 WarpIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6437, 13), 52}, // 147 WarpMaxIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8544, 13), 124}, // 148 WarpsPerSMNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6146, 8), 35}, // 149 WorkDim in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6076, 12), 31}, // 150 WorkgroupId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6062, 14), 30}, // 151 WorkgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7870, 21), 105}, // 152 WorldRayDirectionKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7891, 20), 105}, // 153 WorldRayDirectionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7835, 18), 104}, // 154 WorldRayOriginKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7853, 17), 104}, // 155 WorldRayOriginNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8111, 17), 112}, // 156 WorldToObjectKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8128, 16), 112}, // 157 WorldToObjectNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5509, 10), 139}, // 158 Addresses in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14179, 35), 366}, // 159 ArbitraryPrecisionFixedPointALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14214, 34), 366}, // 160 ArbitraryPrecisionFixedPointINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13651, 38), 354}, // 161 ArbitraryPrecisionFloatingPointALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13689, 37), 354}, // 162 ArbitraryPrecisionFloatingPointINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13586, 33), 353}, // 163 ArbitraryPrecisionIntegersALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13619, 32), 353}, // 164 ArbitraryPrecisionIntegersINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14873, 19), 391}, // 165 ArithmeticFenceEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13224, 9), 339}, // 166 AsmINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14790, 20), 387}, // 167 AtomicFloat16AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13279, 23), 342}, // 168 AtomicFloat16MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12695, 22), 314}, // 169 AtomicFloat16VectorNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14706, 20), 383}, // 170 AtomicFloat32AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13233, 23), 340}, // 171 AtomicFloat32MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14726, 20), 384}, // 172 AtomicFloat64AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13256, 23), 341}, // 173 AtomicFloat64MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8952, 14), 155}, // 174 AtomicStorage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10339, 17), 231}, // 175 AtomicStorageOps in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14831, 24), 389}, // 176 BFloat16ConversionINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10961, 29), 265}, // 177 BFloat16CooperativeMatrixKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10939, 22), 264}, // 178 BFloat16DotProductKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10923, 16), 263}, // 179 BFloat16TypeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15608, 20), 414}, // 180 BindlessImagesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12632, 18), 311}, // 181 BindlessTextureNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14643, 16), 379}, // 182 BitInstructions in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14381, 20), 370}, // 183 BlockingPipesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14401, 19), 370}, // 184 BlockingPipesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15569, 19), 412}, // 185 CacheControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5638, 13), 165}, // 186 ClipDistance in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12263, 32), 299}, // 187 ComputeDerivativeGroupLinearKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12295, 31), 299}, // 188 ComputeDerivativeGroupLinearNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11113, 31), 278}, // 189 ComputeDerivativeGroupQuadsKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11144, 30), 278}, // 190 ComputeDerivativeGroupQuadsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12929, 30), 326}, // 191 CooperativeMatrixBlockLoadsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10708, 32), 250}, // 192 CooperativeMatrixConversionQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12822, 31), 323}, // 193 CooperativeMatrixConversionsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9987, 21), 377}, // 194 CooperativeMatrixKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9922, 28), 213}, // 195 CooperativeMatrixLayoutsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12351, 20), 301}, // 196 CooperativeMatrixNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12853, 40), 324}, // 197 CooperativeMatrixPerElementOperationsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12792, 30), 322}, // 198 CooperativeMatrixReductionsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12893, 36), 325}, // 199 CooperativeMatrixTensorAddressingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12675, 20), 313}, // 200 CooperativeVectorNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12959, 28), 327}, // 201 CooperativeVectorTrainingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6385, 16), 205}, // 202 CoreBuiltinsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5651, 13), 166}, // 203 CullDistance in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14810, 21), 388}, // 204 DebugInfoModuleINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12474, 25), 306}, // 205 DemoteToHelperInvocation in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12499, 28), 306}, // 206 DemoteToHelperInvocationEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10478, 18), 237}, // 207 DenormFlushToZero in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10463, 15), 236}, // 208 DenormPreserve in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9399, 18), 184}, // 209 DerivativeControl in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7139, 18), 266}, // 210 DescriptorHeapEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8923, 14), 153}, // 211 DeviceEnqueue in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6745, 12), 227}, // 212 DeviceGroup in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12527, 23), 307}, // 213 DisplacementMicromapNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14594, 11), 375}, // 214 DotProduct in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14488, 22), 373}, // 215 DotProductInput4x8Bit in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14510, 25), 373}, // 216 DotProductInput4x8BitKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14535, 28), 374}, // 217 DotProductInput4x8BitPacked in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14563, 31), 374}, // 218 DotProductInput4x8BitPackedKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14447, 19), 372}, // 219 DotProductInputAll in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14466, 22), 372}, // 220 DotProductInputAllKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14605, 14), 375}, // 221 DotProductKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6648, 15), 218}, // 222 DrawParameters in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13336, 16), 345}, // 223 ExpectAssumeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14699, 7), 382}, // 224 FMAKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13566, 20), 352}, // 225 FPFastMathModeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15081, 29), 397}, // 226 FPGAArgumentInterfacesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15110, 28), 397}, // 227 FPGAArgumentInterfacesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14130, 25), 365}, // 228 FPGABufferLocationALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14155, 24), 365}, // 229 FPGABufferLocationINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13898, 28), 360}, // 230 FPGAClusterAttributesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13926, 27), 360}, // 231 FPGAClusterAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14892, 30), 392}, // 232 FPGAClusterAttributesV2ALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14922, 29), 392}, // 233 FPGAClusterAttributesV2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13982, 21), 362}, // 234 FPGADSPControlALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14003, 20), 362}, // 235 FPGADSPControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14049, 41), 364}, // 236 FPGAInvocationPipeliningAttributesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14090, 40), 364}, // 237 FPGAInvocationPipeliningAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13823, 26), 358}, // 238 FPGAKernelAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14951, 28), 393}, // 239 FPGAKernelAttributesv2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15032, 25), 396}, // 240 FPGALatencyControlALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15057, 24), 396}, // 241 FPGALatencyControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13756, 23), 356}, // 242 FPGALoopControlsALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13779, 22), 356}, // 243 FPGALoopControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13849, 25), 359}, // 244 FPGAMemoryAccessesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13874, 24), 359}, // 245 FPGAMemoryAccessesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13513, 27), 351}, // 246 FPGAMemoryAttributesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13540, 26), 351}, // 247 FPGAMemoryAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14420, 14), 371}, // 248 FPGARegALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14434, 13), 371}, // 249 FPGARegINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15016, 16), 395}, // 250 FPMaxErrorINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8837, 8), 144}, // 251 Float16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8823, 14), 143}, // 252 Float16Buffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10763, 16), 252}, // 253 Float16ImageAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8845, 8), 145}, // 254 Float64 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9960, 27), 215}, // 255 Float8CooperativeMatrixEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9950, 10), 214}, // 256 Float8EXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14684, 15), 381}, // 257 FloatControls2 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13132, 23), 335}, // 258 FloatingPointModeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7538, 23), 277}, // 259 FragmentBarycentricKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11091, 22), 277}, // 260 FragmentBarycentricNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7627, 19), 279}, // 261 FragmentDensityEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7348, 24), 273}, // 262 FragmentFullyCoveredEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10801, 16), 254}, // 263 FragmentMaskAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12442, 32), 305}, // 264 FragmentShaderPixelInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12371, 33), 302}, // 265 FragmentShaderSampleInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12404, 38), 303}, // 266 FragmentShaderShadingRateInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6710, 23), 216}, // 267 FragmentShadingRateKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13487, 26), 350}, // 268 FunctionFloatControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13178, 22), 337}, // 269 FunctionPointersINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15469, 22), 408}, // 270 FunctionVariantsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9244, 15), 171}, // 271 GenericPointer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5696, 9), 137}, // 272 Geometry in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8994, 18), 158}, // 273 GeometryPointSize in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11019, 28), 268}, // 274 GeometryShaderPassthroughNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9457, 16), 187}, // 275 GeometryStreams in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15168, 36), 399}, // 276 GlobalVariableFPGADecorationsALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15204, 35), 399}, // 277 GlobalVariableFPGADecorationsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15138, 30), 398}, // 278 GlobalVariableHostAccessINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9913, 9), 212}, // 279 GraphARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6228, 16), 194}, // 280 GroupNonUniform in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9596, 26), 196}, // 281 GroupNonUniformArithmetic in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6483, 22), 197}, // 282 GroupNonUniformBallot in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9676, 25), 200}, // 283 GroupNonUniformClustered in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11188, 30), 280}, // 284 GroupNonUniformPartitionedEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11218, 29), 280}, // 285 GroupNonUniformPartitionedNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9701, 20), 201}, // 286 GroupNonUniformQuad in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14659, 25), 380}, // 287 GroupNonUniformRotateKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9622, 23), 198}, // 288 GroupNonUniformShuffle in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9645, 31), 199}, // 289 GroupNonUniformShuffleRelative in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9576, 20), 195}, // 290 GroupNonUniformVote in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15491, 26), 409}, // 291 GroupUniformArithmeticKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8916, 7), 152}, // 292 Groups in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14354, 14), 369}, // 293 IOPipesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14368, 13), 369}, // 294 IOPipesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9313, 8), 177}, // 295 Image1D in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8872, 11), 148}, // 296 ImageBasic in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9335, 12), 180}, // 297 ImageBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9190, 15), 167}, // 298 ImageCubeArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11074, 17), 275}, // 299 ImageFootprintNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10779, 22), 253}, // 300 ImageGatherBiasLodAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9012, 20), 159}, // 301 ImageGatherExtended in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9347, 13), 181}, // 302 ImageMSArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8898, 12), 150}, // 303 ImageMipmap in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9388, 11), 183}, // 304 ImageQuery in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8883, 15), 149}, // 305 ImageReadWrite in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10817, 21), 256}, // 306 ImageReadWriteLodAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9222, 10), 169}, // 307 ImageRect in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13200, 24), 338}, // 308 IndirectReferencesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9264, 16), 173}, // 309 InputAttachment in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11333, 36), 283}, // 310 InputAttachmentArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11369, 39), 283}, // 311 InputAttachmentArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11874, 39), 290}, // 312 InputAttachmentArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11913, 42), 290}, // 313 InputAttachmentArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8966, 6), 156}, // 314 Int16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10896, 27), 262}, // 315 Int4CooperativeMatrixINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10882, 14), 261}, // 316 Int4TypeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8853, 6), 146}, // 317 Int64 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8859, 13), 147}, // 318 Int64Atomics in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10838, 14), 257}, // 319 Int64ImageEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9259, 5), 172}, // 320 Int8 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13155, 23), 336}, // 321 IntegerFunctions2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9417, 22), 185}, // 322 InterpolationFunction in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5463, 7), 141}, // 323 Kernel in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13801, 22), 357}, // 324 KernelAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8806, 8), 140}, // 325 Linkage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8937, 15), 154}, // 326 LiteralSampler in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14746, 20), 385}, // 327 LongCompositesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12755, 14), 320}, // 328 LongVectorEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13953, 15), 361}, // 329 LoopFuseALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13968, 14), 361}, // 330 LoopFuseINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15544, 25), 411}, // 331 MaskedGatherScatterINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8799, 7), 135}, // 332 Matrix in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14023, 26), 363}, // 333 MemoryAccessAliasingINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5759, 15), 276}, // 334 MeshShadingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5745, 14), 274}, // 335 MeshShadingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9296, 7), 175}, // 336 MinLod in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6767, 10), 228}, // 337 MultiView in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5847, 14), 190}, // 338 MultiViewport in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9551, 13), 192}, // 339 NamedBarrier in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14766, 11), 386}, // 340 OptNoneEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14777, 13), 386}, // 341 OptNoneINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7290, 20), 272}, // 342 PerViewAttributesNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5581, 31), 298}, // 343 PhysicalStorageBufferAddresses in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12229, 34), 298}, // 344 PhysicalStorageBufferAddressesEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9564, 12), 193}, // 345 PipeStorage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8910, 6), 151}, // 346 Pipes in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12735, 20), 319}, // 347 PushConstantBanksNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10867, 15), 260}, // 348 QuadControlKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12717, 18), 316}, // 349 RawAccessChainsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8784, 15), 376}, // 350 RayCullMaskKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10576, 12), 242}, // 351 RayQueryKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12650, 25), 312}, // 352 RayQueryPositionFetchKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10553, 23), 241}, // 353 RayQueryProvisionalKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8731, 41), 328}, // 354 RayTracingClusterAccelerationStructureNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8303, 33), 315}, // 355 RayTracingDisplacementMicromapNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5731, 14), 245}, // 356 RayTracingKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8485, 39), 318}, // 357 RayTracingLinearSweptSpheresGeometryNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8189, 23), 295}, // 358 RayTracingMotionBlurNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5718, 13), 294}, // 359 RayTracingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12550, 29), 308}, // 360 RayTracingOpacityMicromapEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8242, 27), 293}, // 361 RayTracingPositionFetchKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12326, 25), 300}, // 362 RayTracingProvisionalKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8446, 28), 317}, // 363 RayTracingSpheresGeometryNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10607, 32), 244}, // 364 RayTraversalPrimitiveCullingKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15588, 20), 413}, // 365 RegisterLimitsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14619, 24), 378}, // 366 ReplicatedCompositesEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13111, 21), 334}, // 367 RoundToInfinityINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10521, 16), 239}, // 368 RoundingModeRTE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10537, 16), 240}, // 369 RoundingModeRTZ in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14295, 30), 368}, // 370 RuntimeAlignedAttributeALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14325, 29), 368}, // 371 RuntimeAlignedAttributeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11284, 23), 282}, // 372 RuntimeDescriptorArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11307, 26), 282}, // 373 RuntimeDescriptorArrayEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10990, 29), 267}, // 374 SampleMaskOverrideCoverageNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10356, 28), 232}, // 375 SampleMaskPostDepthCoverage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5977, 18), 168}, // 376 SampleRateShading in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9303, 10), 176}, // 377 Sampled1D in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9321, 14), 179}, // 378 SampledBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9205, 17), 178}, // 379 SampledCubeArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9090, 33), 162}, // 380 SampledImageArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11647, 36), 287}, // 381 SampledImageArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11683, 39), 287}, // 382 SampledImageArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9232, 12), 170}, // 383 SampledRect in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5621, 7), 136}, // 384 Shader in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12769, 23), 321}, // 385 Shader64BitIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10852, 15), 258}, // 386 ShaderClockKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7090, 18), 259}, // 387 ShaderEnqueueAMDX in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12605, 27), 310}, // 388 ShaderInvocationReorderEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12579, 26), 309}, // 389 ShaderInvocationReorderNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5793, 12), 202}, // 390 ShaderLayer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11247, 17), 281}, // 391 ShaderNonUniform in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11264, 20), 281}, // 392 ShaderNonUniformEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8557, 19), 304}, // 393 ShaderSMBuiltinsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7229, 19), 271}, // 394 ShaderStereoViewNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5861, 20), 203}, // 395 ShaderViewportIndex in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5805, 28), 269}, // 396 ShaderViewportIndexLayerEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11047, 27), 269}, // 397 ShaderViewportIndexLayerNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7188, 21), 270}, // 398 ShaderViewportMaskNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11174, 14), 279}, // 399 ShadingRateNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10496, 25), 238}, // 400 SignedZeroInfNanPreserve in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9280, 16), 174}, // 401 SparseResidency in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15448, 21), 407}, // 402 SpecConditionalINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14855, 18), 390}, // 403 SplitBarrierINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7044, 17), 255}, // 404 StencilExportEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10144, 25), 223}, // 405 StorageBuffer16BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10384, 24), 233}, // 406 StorageBuffer8BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9123, 34), 163}, // 407 StorageBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11722, 37), 288}, // 408 StorageBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11759, 40), 288}, // 409 StorageBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9157, 33), 164}, // 410 StorageImageArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11799, 36), 289}, // 411 StorageImageArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11835, 39), 289}, // 412 StorageImageArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9360, 28), 182}, // 413 StorageImageExtendedFormats in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9032, 24), 160}, // 414 StorageImageMultisample in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9473, 30), 188}, // 415 StorageImageReadWithoutFormat in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9503, 31), 189}, // 416 StorageImageWriteWithoutFormat in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10271, 21), 226}, // 417 StorageInputOutput16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10249, 22), 225}, // 418 StoragePushConstant16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10442, 21), 235}, // 419 StoragePushConstant8 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9836, 37), 210}, // 420 StorageTensorArrayDynamicIndexingARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9873, 40), 211}, // 421 StorageTensorArrayNonUniformIndexingARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11489, 39), 285}, // 422 StorageTexelBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11528, 42), 285}, // 423 StorageTexelBufferArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12042, 42), 292}, // 424 StorageTexelBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12084, 45), 292}, // 425 StorageTexelBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10232, 17), 224}, // 426 StorageUniform16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10169, 28), 223}, // 427 StorageUniformBufferBlock16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15267, 23), 401}, // 428 Subgroup2DBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15290, 30), 402}, // 429 Subgroup2DBlockTransformINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15320, 30), 403}, // 430 Subgroup2DBlockTransposeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13423, 39), 348}, // 431 SubgroupAvcMotionEstimationChromaINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13352, 33), 346}, // 432 SubgroupAvcMotionEstimationINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13385, 38), 347}, // 433 SubgroupAvcMotionEstimationIntraINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6244, 18), 217}, // 434 SubgroupBallotKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13027, 27), 331}, // 435 SubgroupBufferBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15239, 28), 400}, // 436 SubgroupBufferPrefetchINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9534, 17), 191}, // 437 SubgroupDispatch in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13054, 26), 332}, // 438 SubgroupImageBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13080, 31), 333}, // 439 SubgroupImageMediaBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15350, 38), 404}, // 440 SubgroupMatrixMultiplyAccumulateINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13006, 21), 330}, // 441 SubgroupShuffleINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10128, 16), 222}, // 442 SubgroupVoteKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14979, 19), 394}, // 443 TaskSequenceALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14998, 18), 394}, // 444 TaskSequenceINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12987, 19), 329}, // 445 TensorAddressingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15517, 27), 410}, // 446 TensorFloat32RoundingINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9825, 11), 209}, // 447 TensorsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15388, 28), 405}, // 448 TernaryBitwiseFunctionINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5705, 13), 138}, // 449 Tessellation in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8972, 22), 157}, // 450 TessellationPointSize in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10740, 23), 251}, // 451 TextureBlockMatch2QCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10686, 22), 248}, // 452 TextureBlockMatchQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10665, 21), 247}, // 453 TextureBoxFilterQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10639, 26), 246}, // 454 TextureSampleWeightedQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9739, 28), 206}, // 455 TileImageColorReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9767, 28), 207}, // 456 TileImageDepthReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9795, 30), 208}, // 457 TileImageStencilReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6807, 16), 249}, // 458 TileShadingQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9439, 18), 186}, // 459 TransformFeedback in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14248, 24), 367}, // 460 USMStorageClassesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14272, 23), 367}, // 461 USMStorageClassesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10197, 35), 224}, // 462 UniformAndStorageBuffer16BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10408, 34), 234}, // 463 UniformAndStorageBuffer8BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9056, 34), 161}, // 464 UniformBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11570, 37), 286}, // 465 UniformBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11607, 40), 286}, // 466 UniformBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9721, 18), 204}, // 467 UniformDecoration in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11408, 39), 284}, // 468 UniformTexelBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11447, 42), 284}, // 469 UniformTexelBufferArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11955, 42), 291}, // 470 UniformTexelBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11997, 45), 291}, // 471 UniformTexelBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13726, 30), 355}, // 472 UnstructuredLoopControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10588, 19), 243}, // 473 UntypedPointersKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15416, 32), 406}, // 474 UntypedVariableLengthArrayINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13462, 25), 349}, // 475 VariableLengthArrayINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10322, 17), 230}, // 476 VariablePointers in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10292, 30), 229}, // 477 VariablePointersStorageBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8814, 9), 142}, // 478 Vector16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13321, 15), 344}, // 479 VectorAnyINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13302, 19), 343}, // 480 VectorComputeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12129, 18), 296}, // 481 VulkanMemoryModel in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12168, 29), 297}, // 482 VulkanMemoryModelDeviceScope in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12197, 32), 297}, // 483 VulkanMemoryModelDeviceScopeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12147, 21), 296}, // 484 VulkanMemoryModelKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10084, 44), 221}, // 485 WorkgroupMemoryExplicitLayout16BitAccessKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10041, 43), 220}, // 486 WorkgroupMemoryExplicitLayout8BitAccessKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10008, 33), 219}, // 487 WorkgroupMemoryExplicitLayoutKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15640, 8), 416}, // 488 Address in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15648, 8), 417}, // 489 Boolean in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15656, 6), 418}, // 490 Float in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15662, 7), 419}, // 491 Signed in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15669, 11), 420}, // 492 SignedChar in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15680, 9), 421}, // 493 Unsigned in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15689, 13), 422}, // 494 UnsignedChar in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15628, 12), 415}, // 495 Unspecified in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15702, 6), 423}, // 496 Class in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15708, 10), 424}, // 497 Structure in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15718, 6), 425}, // 498 Union in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15739, 20), 427}, // 499 ImportedDeclaration in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(15724, 15), 426}, // 500 ImportedModule in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(15848, 15), 435}, // 501 FlagArtificial in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15863, 13), 436}, // 502 FlagExplicit in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15836, 12), 434}, // 503 FlagFwdDecl in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15926, 21), 440}, // 504 FlagIndirectVariable in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15819, 17), 433}, // 505 FlagIsDefinition in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16003, 16), 444}, // 506 FlagIsEnumClass in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15807, 12), 432}, // 507 FlagIsLocal in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15987, 16), 443}, // 508 FlagIsOptimized in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15780, 14), 430}, // 509 FlagIsPrivate in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15764, 16), 429}, // 510 FlagIsProtected in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15794, 13), 431}, // 511 FlagIsPublic in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15947, 20), 441}, // 512 FlagLValueReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15891, 18), 438}, // 513 FlagObjectPointer in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15876, 15), 437}, // 514 FlagPrototyped in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15967, 20), 442}, // 515 FlagRValueReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15909, 17), 439}, // 516 FlagStaticMember in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16039, 24), 446}, // 517 FlagTypePassByReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16019, 20), 445}, // 518 FlagTypePassByValue in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15759, 5), 428}, // 519 None in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16124, 9), 451}, // 520 BitPiece in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16156, 7), 455}, // 521 Constu in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16063, 6), 447}, // 522 Deref in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16163, 9), 456}, // 523 Fragment in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16074, 6), 449}, // 524 Minus in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16069, 5), 448}, // 525 Plus in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16113, 11), 450}, // 526 PlusUconst in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16145, 11), 454}, // 527 StackValue in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16133, 5), 452}, // 528 Swap in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16138, 7), 453}, // 529 Xderef in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16208, 11), 460}, // 530 AtomicType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16172, 10), 457}, // 531 ConstType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16195, 13), 459}, // 532 RestrictType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16182, 13), 458}, // 533 VolatileType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16219, 10), 461}, // 534 Float16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16229, 10), 462}, // 535 Float32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16239, 10), 463}, // 536 Float64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16407, 12), 474}, // 537 FloatE4M3NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16419, 12), 475}, // 538 FloatE5M2NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16262, 14), 465}, // 539 SignedInt16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16276, 14), 466}, // 540 SignedInt32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16290, 14), 467}, // 541 SignedInt64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16249, 13), 464}, // 542 SignedInt8NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16367, 19), 472}, // 543 SignedInt8PackedNV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16319, 16), 469}, // 544 UnsignedInt16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16335, 16), 470}, // 545 UnsignedInt32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16351, 16), 471}, // 546 UnsignedInt64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16304, 15), 468}, // 547 UnsignedInt8NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16386, 21), 473}, // 548 UnsignedInt8PackedNV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16483, 28), 479}, // 549 ColumnBlockedInterleavedARM in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(16443, 15), 477}, // 550 ColumnMajorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(16458, 25), 478}, // 551 RowBlockedInterleavedARM in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(16431, 12), 476}, // 552 RowMajorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(16519, 27), 481}, // 553 MatrixASignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16546, 27), 482}, // 554 MatrixBSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16573, 27), 483}, // 555 MatrixCSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16600, 32), 484}, // 556 MatrixResultSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16511, 8), 480}, // 557 NoneKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16632, 26), 485}, // 558 SaturatingAccumulationKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16669, 4), 488}, // 559 2x2 in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(16662, 7), 487}, // 560 Column in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(16658, 4), 486}, // 561 Row in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(16673, 11), 489}, // 562 MatrixAKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(16695, 21), 491}, // 563 MatrixAccumulatorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(16684, 11), 490}, // 564 MatrixBKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(16727, 14), 493}, // 565 ColumnMajorNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(16741, 21), 494}, // 566 InferencingOptimalNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(16716, 11), 492}, // 567 RowMajorNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(16762, 18), 495}, // 568 TrainingOptimalNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(15640, 8), 497}, // 569 Address in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15648, 8), 498}, // 570 Boolean in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15656, 6), 499}, // 571 Float in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15662, 7), 500}, // 572 Signed in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15669, 11), 501}, // 573 SignedChar in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15680, 9), 502}, // 574 Unsigned in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15689, 13), 503}, // 575 UnsignedChar in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15628, 12), 496}, // 576 Unspecified in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15702, 6), 504}, // 577 Class in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(15708, 10), 505}, // 578 Structure in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(15718, 6), 506}, // 579 Union in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(15848, 15), 514}, // 580 FlagArtificial in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15863, 13), 515}, // 581 FlagExplicit in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15836, 12), 513}, // 582 FlagFwdDecl in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15926, 21), 519}, // 583 FlagIndirectVariable in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15819, 17), 512}, // 584 FlagIsDefinition in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15807, 12), 511}, // 585 FlagIsLocal in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15987, 16), 522}, // 586 FlagIsOptimized in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15780, 14), 509}, // 587 FlagIsPrivate in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15764, 16), 508}, // 588 FlagIsProtected in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15794, 13), 510}, // 589 FlagIsPublic in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15947, 20), 520}, // 590 FlagLValueReference in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15891, 18), 517}, // 591 FlagObjectPointer in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15876, 15), 516}, // 592 FlagPrototyped in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15967, 20), 521}, // 593 FlagRValueReference in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15909, 17), 518}, // 594 FlagStaticMember in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15759, 5), 507}, // 595 None in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16124, 9), 527}, // 596 BitPiece in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16156, 7), 531}, // 597 Constu in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16063, 6), 523}, // 598 Deref in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16074, 6), 525}, // 599 Minus in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16069, 5), 524}, // 600 Plus in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16113, 11), 526}, // 601 PlusUconst in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16145, 11), 530}, // 602 StackValue in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16133, 5), 528}, // 603 Swap in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16138, 7), 529}, // 604 Xderef in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16172, 10), 532}, // 605 ConstType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(16195, 13), 534}, // 606 RestrictType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(16182, 13), 533}, // 607 VolatileType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(19486, 16), 654}, // 608 AliasScopeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16989, 8), 554}, // 609 Aliased in SPV_OPERAND_TYPE_DECORATION
  {IR(18136, 15), 609}, // 610 AliasedPointer in SPV_OPERAND_TYPE_DECORATION
  {IR(18151, 18), 609}, // 611 AliasedPointerEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(17467, 10), 578}, // 612 Alignment in SPV_OPERAND_TYPE_DECORATION
  {IR(17511, 12), 580}, // 613 AlignmentId in SPV_OPERAND_TYPE_DECORATION
  {IR(16840, 12), 541}, // 614 ArrayStride in SPV_OPERAND_TYPE_DECORATION
  {IR(17891, 17), 597}, // 615 ArrayStrideIdEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(19036, 15), 642}, // 616 BankBitsALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19051, 14), 642}, // 617 BankBitsINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18245, 7), 613}, // 618 BankNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18749, 16), 635}, // 619 BankwidthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18765, 15), 635}, // 620 BankwidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17144, 8), 567}, // 621 Binding in SPV_OPERAND_TYPE_DECORATION
  {IR(18270, 16), 615}, // 622 BindlessImageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18252, 18), 614}, // 623 BindlessSamplerNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16804, 6), 537}, // 624 Block in SPV_OPERAND_TYPE_DECORATION
  {IR(17651, 22), 587}, // 625 BlockMatchSamplerQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(17629, 22), 586}, // 626 BlockMatchTextureQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(18301, 13), 617}, // 627 BoundImageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18286, 15), 616}, // 628 BoundSamplerNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16810, 12), 538}, // 629 BufferBlock in SPV_OPERAND_TYPE_DECORATION
  {IR(19646, 21), 659}, // 630 BufferLocationALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19667, 20), 659}, // 631 BufferLocationINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16921, 8), 546}, // 632 BuiltIn in SPV_OPERAND_TYPE_DECORATION
  {IR(19205, 20), 647}, // 633 BurstCoalesceALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19225, 19), 647}, // 634 BurstCoalesceINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16887, 8), 545}, // 635 CPacked in SPV_OPERAND_TYPE_DECORATION
  {IR(20893, 22), 682}, // 636 CacheControlLoadINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20952, 23), 683}, // 637 CacheControlStoreINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19244, 16), 648}, // 638 CacheSizeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19260, 15), 648}, // 639 CacheSizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16954, 9), 550}, // 640 Centroid in SPV_OPERAND_TYPE_DECORATION
  {IR(18354, 13), 620}, // 641 ClobberINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17015, 9), 557}, // 642 Coherent in SPV_OPERAND_TYPE_DECORATION
  {IR(16831, 9), 540}, // 643 ColMajor in SPV_OPERAND_TYPE_DECORATION
  {IR(17128, 10), 565}, // 644 Component in SPV_OPERAND_TYPE_DECORATION
  {IR(20840, 17), 681}, // 645 ConditionalINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20069, 28), 669}, // 646 ConduitKernelArgumentALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20097, 27), 669}, // 647 ConduitKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17006, 9), 556}, // 648 Constant in SPV_OPERAND_TYPE_DECORATION
  {IR(18500, 14), 627}, // 649 CounterBuffer in SPV_OPERAND_TYPE_DECORATION
  {IR(17152, 14), 568}, // 650 DescriptorSet in SPV_OPERAND_TYPE_DECORATION
  {IR(19275, 29), 649}, // 651 DontStaticallyCoalesceALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19304, 28), 649}, // 652 DontStaticallyCoalesceINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18858, 17), 638}, // 653 DoublepumpALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18875, 16), 638}, // 654 DoublepumpINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17673, 18), 588}, // 655 ExplicitInterpAMD in SPV_OPERAND_TYPE_DECORATION
  {IR(17337, 15), 574}, // 656 FPFastMathMode in SPV_OPERAND_TYPE_DECORATION
  {IR(19931, 26), 666}, // 657 FPMaxErrorDecorationINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17287, 15), 573}, // 658 FPRoundingMode in SPV_OPERAND_TYPE_DECORATION
  {IR(16943, 5), 548}, // 659 Flat in SPV_OPERAND_TYPE_DECORATION
  {IR(19065, 21), 643}, // 660 ForcePow2DepthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19086, 20), 643}, // 661 ForcePow2DepthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17239, 14), 572}, // 662 FuncParamAttr in SPV_OPERAND_TYPE_DECORATION
  {IR(18411, 21), 623}, // 663 FuncParamIOKindINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18642, 24), 631}, // 664 FunctionDenormModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19760, 31), 661}, // 665 FunctionFloatingPointModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18585, 26), 630}, // 666 FunctionRoundingModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19396, 26), 652}, // 667 FuseLoopsInFunctionALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19422, 25), 652}, // 668 FuseLoopsInFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16876, 11), 544}, // 669 GLSLPacked in SPV_OPERAND_TYPE_DECORATION
  {IR(16865, 11), 543}, // 670 GLSLShared in SPV_OPERAND_TYPE_DECORATION
  {IR(18474, 26), 626}, // 671 GlobalVariableOffsetINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18214, 31), 612}, // 672 HitObjectShaderRecordBufferEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(18184, 30), 611}, // 673 HitObjectShaderRecordBufferNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18514, 24), 627}, // 674 HlslCounterBufferGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(18551, 19), 628}, // 675 HlslSemanticGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(20691, 16), 678}, // 676 HostAccessINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19687, 20), 660}, // 677 IOPipeStorageALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19707, 19), 660}, // 678 IOPipeStorageINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20783, 29), 680}, // 679 ImplementInRegisterMapALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20812, 28), 680}, // 680 ImplementInRegisterMapINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17138, 6), 566}, // 681 Index in SPV_OPERAND_TYPE_DECORATION
  {IR(20754, 15), 679}, // 682 InitModeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20769, 14), 679}, // 683 InitModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19515, 25), 656}, // 684 InitiationIntervalALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19540, 24), 656}, // 685 InitiationIntervalINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17446, 21), 577}, // 686 InputAttachmentIndex in SPV_OPERAND_TYPE_DECORATION
  {IR(16970, 10), 552}, // 687 Invariant in SPV_OPERAND_TYPE_DECORATION
  {IR(20008, 31), 668}, // 688 LatencyControlConstraintALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20039, 30), 668}, // 689 LatencyControlConstraintINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19957, 26), 667}, // 690 LatencyControlLabelALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19983, 25), 667}, // 691 LatencyControlLabelINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17414, 18), 575}, // 692 LinkageAttributes in SPV_OPERAND_TYPE_DECORATION
  {IR(17119, 9), 564}, // 693 Location in SPV_OPERAND_TYPE_DECORATION
  {IR(20187, 34), 671}, // 694 MMHostInterfaceAddressWidthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20221, 33), 671}, // 695 MMHostInterfaceAddressWidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20254, 31), 672}, // 696 MMHostInterfaceDataWidthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20285, 30), 672}, // 697 MMHostInterfaceDataWidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20315, 29), 673}, // 698 MMHostInterfaceLatencyALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20344, 28), 673}, // 699 MMHostInterfaceLatencyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20475, 30), 675}, // 700 MMHostInterfaceMaxBurstALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20505, 29), 675}, // 701 MMHostInterfaceMaxBurstINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20406, 35), 674}, // 702 MMHostInterfaceReadWriteModeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20441, 34), 674}, // 703 MMHostInterfaceReadWriteModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20534, 33), 676}, // 704 MMHostInterfaceWaitRequestALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20567, 32), 676}, // 705 MMHostInterfaceWaitRequestINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19447, 20), 653}, // 706 MathOpDSPModeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19467, 19), 653}, // 707 MathOpDSPModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16852, 13), 542}, // 708 MatrixStride in SPV_OPERAND_TYPE_DECORATION
  {IR(17477, 14), 579}, // 709 MaxByteOffset in SPV_OPERAND_TYPE_DECORATION
  {IR(17523, 16), 581}, // 710 MaxByteOffsetId in SPV_OPERAND_TYPE_DECORATION
  {IR(19564, 21), 657}, // 711 MaxConcurrencyALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19585, 20), 657}, // 712 MaxConcurrencyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18780, 23), 636}, // 713 MaxPrivateCopiesALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18803, 22), 636}, // 714 MaxPrivateCopiesINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18891, 20), 639}, // 715 MaxReplicatesALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18911, 19), 639}, // 716 MaxReplicatesINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19851, 18), 664}, // 717 MediaBlockIOINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18169, 15), 610}, // 718 MemberOffsetNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18695, 13), 633}, // 719 MemoryALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18708, 12), 633}, // 720 MemoryINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18971, 12), 641}, // 721 MergeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18983, 11), 641}, // 722 MergeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19502, 13), 655}, // 723 NoAliasINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17432, 14), 576}, // 724 NoContraction in SPV_OPERAND_TYPE_DECORATION
  {IR(16929, 14), 547}, // 725 NoPerspective in SPV_OPERAND_TYPE_DECORATION
  {IR(17583, 13), 583}, // 726 NoSignedWrap in SPV_OPERAND_TYPE_DECORATION
  {IR(17596, 15), 584}, // 727 NoUnsignedWrap in SPV_OPERAND_TYPE_DECORATION
  {IR(17723, 20), 590}, // 728 NodeMaxPayloadsAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17691, 32), 589}, // 729 NodeSharesPayloadLimitsWithAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17036, 12), 559}, // 730 NonReadable in SPV_OPERAND_TYPE_DECORATION
  {IR(18076, 11), 607}, // 731 NonUniform in SPV_OPERAND_TYPE_DECORATION
  {IR(18087, 14), 607}, // 732 NonUniformEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(17024, 12), 558}, // 733 NonWritable in SPV_OPERAND_TYPE_DECORATION
  {IR(18720, 15), 634}, // 734 NumbanksALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18735, 14), 634}, // 735 NumbanksINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17166, 7), 569}, // 736 Offset in SPV_OPERAND_TYPE_DECORATION
  {IR(17908, 12), 598}, // 737 OffsetIdEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(17920, 19), 599}, // 738 OverrideCoverageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17939, 14), 600}, // 739 PassthroughNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16948, 6), 549}, // 740 Patch in SPV_OPERAND_TYPE_DECORATION
  {IR(17863, 28), 596}, // 741 PayloadDispatchIndirectAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17838, 25), 595}, // 742 PayloadNodeArraySizeAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17786, 25), 593}, // 743 PayloadNodeBaseIndexAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17766, 20), 592}, // 744 PayloadNodeNameAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17811, 27), 594}, // 745 PayloadNodeSparseArrayAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(18000, 16), 603}, // 746 PerPrimitiveEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(18016, 15), 603}, // 747 PerPrimitiveNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18041, 10), 605}, // 748 PerTaskNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18051, 13), 606}, // 749 PerVertexKHR in SPV_OPERAND_TYPE_DECORATION
  {IR(18064, 12), 606}, // 750 PerVertexNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18031, 10), 604}, // 751 PerViewNV in SPV_OPERAND_TYPE_DECORATION
  {IR(19605, 21), 658}, // 752 PipelineEnableALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19626, 20), 658}, // 753 PipelineEnableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19332, 15), 650}, // 754 PrefetchALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19347, 14), 650}, // 755 PrefetchINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18328, 26), 619}, // 756 ReferencedIndirectlyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18666, 15), 632}, // 757 RegisterALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18681, 14), 632}, // 758 RegisterINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20124, 32), 670}, // 759 RegisterMapKernelArgumentALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20156, 31), 670}, // 760 RegisterMapKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16780, 17), 535}, // 761 RelaxedPrecision in SPV_OPERAND_TYPE_DECORATION
  {IR(16980, 9), 553}, // 762 Restrict in SPV_OPERAND_TYPE_DECORATION
  {IR(18101, 16), 608}, // 763 RestrictPointer in SPV_OPERAND_TYPE_DECORATION
  {IR(18117, 19), 608}, // 764 RestrictPointerEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(16822, 9), 539}, // 765 RowMajor in SPV_OPERAND_TYPE_DECORATION
  {IR(18314, 14), 618}, // 766 SIMTCallINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16963, 7), 551}, // 767 Sample in SPV_OPERAND_TYPE_DECORATION
  {IR(17092, 20), 562}, // 768 SaturatedConversion in SPV_OPERAND_TYPE_DECORATION
  {IR(17539, 44), 582}, // 769 SaturatedToLargestFloat8NormalConversionEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(17972, 28), 602}, // 770 SecondaryViewportRelativeNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18367, 17), 621}, // 771 SideEffectsINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18930, 21), 640}, // 772 SimpleDualPortALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18951, 20), 640}, // 773 SimpleDualPortINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19791, 25), 662}, // 774 SingleElementVectorINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18825, 17), 637}, // 775 SinglepumpALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18842, 16), 637}, // 776 SinglepumpINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16797, 7), 536}, // 777 SpecId in SPV_OPERAND_TYPE_DECORATION
  {IR(20599, 27), 677}, // 778 StableKernelArgumentALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20626, 26), 677}, // 779 StableKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18459, 15), 625}, // 780 StackCallINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19361, 18), 651}, // 781 StallEnableALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19379, 17), 651}, // 782 StallEnableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19869, 16), 665}, // 783 StallFreeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19885, 15), 665}, // 784 StallFreeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17112, 7), 563}, // 785 Stream in SPV_OPERAND_TYPE_DECORATION
  {IR(19106, 17), 644}, // 786 StridesizeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19123, 16), 644}, // 787 StridesizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17743, 23), 591}, // 788 TrackFinishWritingAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(19168, 19), 646}, // 789 TrueDualPortALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19187, 18), 646}, // 790 TrueDualPortINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17048, 8), 560}, // 791 Uniform in SPV_OPERAND_TYPE_DECORATION
  {IR(17082, 10), 561}, // 792 UniformId in SPV_OPERAND_TYPE_DECORATION
  {IR(18538, 13), 628}, // 793 UserSemantic in SPV_OPERAND_TYPE_DECORATION
  {IR(18570, 15), 629}, // 794 UserTypeGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(19816, 35), 663}, // 795 VectorComputeCallableFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18432, 27), 624}, // 796 VectorComputeFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18384, 27), 622}, // 797 VectorComputeVariableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17953, 19), 601}, // 798 ViewportRelativeNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16997, 9), 555}, // 799 Volatile in SPV_OPERAND_TYPE_DECORATION
  {IR(17611, 18), 585}, // 800 WeightTextureQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(19139, 15), 645}, // 801 WordsizeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19154, 14), 645}, // 802 WordsizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17173, 10), 570}, // 803 XfbBuffer in SPV_OPERAND_TYPE_DECORATION
  {IR(17183, 10), 571}, // 804 XfbStride in SPV_OPERAND_TYPE_DECORATION
  {IR(20975, 3), 684}, // 805 1D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(20978, 3), 685}, // 806 2D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(20981, 3), 686}, // 807 3D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(20994, 7), 689}, // 808 Buffer in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(20984, 5), 687}, // 809 Cube in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(20989, 5), 688}, // 810 Rect in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21001, 12), 690}, // 811 SubpassData in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21013, 17), 691}, // 812 TileImageDataEXT in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21825, 15), 744}, // 813 CoalescingAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21456, 15), 722}, // 814 ContractionOff in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10478, 18), 736}, // 815 DenormFlushToZero in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10463, 15), 735}, // 816 DenormPreserve in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21226, 13), 705}, // 817 DepthGreater in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21239, 10), 706}, // 818 DepthLess in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21211, 15), 704}, // 819 DepthReplacing in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21249, 15), 707}, // 820 DepthUnchanged in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22246, 25), 762}, // 821 DerivativeGroupLinearKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22271, 24), 762}, // 822 DerivativeGroupLinearNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22199, 24), 761}, // 823 DerivativeGroupQuadsKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22223, 23), 761}, // 824 DerivativeGroupQuadsNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21773, 29), 742}, // 825 EarlyAndLateFragmentTestsAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21178, 19), 701}, // 826 EarlyFragmentTests in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22756, 18), 782}, // 827 FPFastMathDefault in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21483, 10), 724}, // 828 Finalizer in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22571, 26), 774}, // 829 FloatingPointModeALTINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22597, 27), 775}, // 830 FloatingPointModeIEEEINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21471, 12), 723}, // 831 Initializer in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21300, 11), 711}, // 832 InputLines in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21311, 20), 712}, // 833 InputLinesAdjacency in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21288, 12), 710}, // 834 InputPoints in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21341, 24), 714}, // 835 InputTrianglesAdjacency in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21030, 12), 692}, // 836 Invocations in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21840, 15), 745}, // 837 IsApiEntryAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21371, 9), 716}, // 838 Isolines in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21264, 10), 708}, // 839 LocalSize in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21274, 14), 709}, // 840 LocalSizeHint in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21551, 16), 729}, // 841 LocalSizeHintId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21539, 12), 728}, // 842 LocalSizeId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21855, 21), 746}, // 843 MaxNodeRecursionAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21900, 21), 749}, // 844 MaxNumWorkgroupsAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22646, 16), 777}, // 845 MaxWorkDimINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22624, 22), 776}, // 846 MaxWorkgroupSizeINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22732, 24), 781}, // 847 MaximallyReconvergesKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22847, 22), 786}, // 848 MaximumRegistersINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22869, 24), 787}, // 849 MaximumRegistersIdINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22824, 23), 785}, // 850 NamedBarrierCountINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22944, 27), 788}, // 851 NamedMaximumRegistersINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22662, 20), 778}, // 852 NoGlobalOffsetINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21567, 34), 730}, // 853 NonCoherentColorAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21601, 34), 731}, // 854 NonCoherentDepthAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21635, 36), 732}, // 855 NonCoherentStencilAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21719, 34), 740}, // 856 NonCoherentTileAttachmentReadQCOM in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22682, 22), 779}, // 857 NumSIMDWorkitemsINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21162, 16), 700}, // 858 OriginLowerLeft in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21146, 16), 699}, // 859 OriginUpperLeft in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21408, 16), 719}, // 860 OutputLineStrip in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22131, 15), 759}, // 861 OutputLinesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22146, 14), 759}, // 862 OutputLinesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21395, 13), 718}, // 863 OutputPoints in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22160, 20), 760}, // 864 OutputPrimitivesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22180, 19), 760}, // 865 OutputPrimitivesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21424, 20), 720}, // 866 OutputTriangleStrip in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22295, 19), 763}, // 867 OutputTrianglesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22314, 18), 763}, // 868 OutputTrianglesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21380, 15), 717}, // 869 OutputVertices in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21127, 19), 698}, // 870 PixelCenterInteger in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22332, 25), 764}, // 871 PixelInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22357, 27), 765}, // 872 PixelInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21197, 10), 702}, // 873 PointMode in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21701, 18), 734}, // 874 PostDepthCoverage in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22072, 19), 756}, // 875 QuadDerivativesKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21365, 6), 715}, // 876 Quads in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22798, 26), 784}, // 877 RegisterMapInterfaceINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22091, 20), 757}, // 878 RequireFullQuadsKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10521, 16), 738}, // 879 RoundingModeRTE in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22550, 21), 773}, // 880 RoundingModeRTNINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22529, 21), 772}, // 881 RoundingModeRTPINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10537, 16), 739}, // 882 RoundingModeRTZ in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22384, 26), 766}, // 883 SampleInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22410, 28), 767}, // 884 SampleInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22704, 28), 780}, // 885 SchedulerTargetFmaxMhzINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(12769, 23), 770}, // 886 Shader64BitIndexingEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(7108, 16), 748}, // 887 ShaderIndexAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22438, 31), 768}, // 888 ShadingRateInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22469, 33), 769}, // 889 ShadingRateInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22502, 27), 771}, // 890 SharedLocalMemorySizeINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22111, 20), 758}, // 891 SharesInputWithAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10496, 25), 737}, // 892 SignedZeroInfNanPreserve in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21042, 13), 693}, // 893 SpacingEqual in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21055, 22), 694}, // 894 SpacingFractionalEven in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21077, 21), 695}, // 895 SpacingFractionalOdd in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21876, 24), 747}, // 896 StaticNumWorkgroupsAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22025, 25), 754}, // 897 StencilRefGreaterBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21949, 26), 751}, // 898 StencilRefGreaterFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22050, 22), 755}, // 899 StencilRefLessBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21975, 23), 752}, // 900 StencilRefLessFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21802, 23), 743}, // 901 StencilRefReplacingEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21998, 27), 753}, // 902 StencilRefUnchangedBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21921, 28), 750}, // 903 StencilRefUnchangedFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22774, 24), 783}, // 904 StreamingInterfaceINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(6215, 13), 725}, // 905 SubgroupSize in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21671, 30), 733}, // 906 SubgroupUniformControlFlowKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21493, 22), 726}, // 907 SubgroupsPerWorkgroup in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21515, 24), 727}, // 908 SubgroupsPerWorkgroupId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21753, 20), 741}, // 909 TileShadingRateQCOM in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21331, 10), 713}, // 910 Triangles in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21444, 12), 721}, // 911 VecTypeHint in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21112, 15), 697}, // 912 VertexOrderCcw in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21098, 14), 696}, // 913 VertexOrderCw in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21207, 4), 703}, // 914 Xfb in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23109, 10), 800}, // 915 AnyHitKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23119, 9), 800}, // 916 AnyHitNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23170, 12), 803}, // 917 CallableKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23182, 11), 803}, // 918 CallableNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23128, 14), 801}, // 919 ClosestHitKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23142, 13), 801}, // 920 ClosestHitNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(16163, 9), 793}, // 921 Fragment in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23021, 10), 794}, // 922 GLCompute in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(5696, 9), 792}, // 923 Geometry in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23078, 16), 799}, // 924 IntersectionKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23094, 15), 799}, // 925 IntersectionNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(5463, 7), 795}, // 926 Kernel in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23201, 8), 805}, // 927 MeshEXT in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23038, 7), 797}, // 928 MeshNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23155, 8), 802}, // 929 MissKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23163, 7), 802}, // 930 MissNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23045, 17), 798}, // 931 RayGenerationKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23062, 16), 798}, // 932 RayGenerationNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23193, 8), 804}, // 933 TaskEXT in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23031, 7), 796}, // 934 TaskNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22978, 20), 790}, // 935 TessellationControl in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22998, 23), 791}, // 936 TessellationEvaluation in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22971, 7), 789}, // 937 Vertex in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23218, 12), 807}, // 938 FlushToZero in SPV_OPERAND_TYPE_FPDENORM_MODE
  {IR(23209, 9), 806}, // 939 Preserve in SPV_OPERAND_TYPE_FPDENORM_MODE
  {IR(23230, 12), 808}, // 940 BFloat16KHR in SPV_OPERAND_TYPE_FPENCODING
  {IR(23242, 14), 809}, // 941 Float8E4M3EXT in SPV_OPERAND_TYPE_FPENCODING
  {IR(23256, 14), 810}, // 942 Float8E5M2EXT in SPV_OPERAND_TYPE_FPENCODING
  {IR(23275, 4), 812}, // 943 ALT in SPV_OPERAND_TYPE_FPOPERATION_MODE
  {IR(23270, 5), 811}, // 944 IEEE in SPV_OPERAND_TYPE_FPOPERATION_MODE
  {IR(23313, 14), 819}, // 945 AllowContract in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23327, 23), 819}, // 946 AllowContractFastINTEL in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23350, 13), 820}, // 947 AllowReassoc in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23363, 18), 820}, // 948 AllowReassocINTEL in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23297, 11), 817}, // 949 AllowRecip in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23381, 15), 821}, // 950 AllowTransform in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23308, 5), 818}, // 951 Fast in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23293, 4), 816}, // 952 NSZ in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(15759, 5), 813}, // 953 None in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23286, 7), 815}, // 954 NotInf in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23279, 7), 814}, // 955 NotNaN in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23396, 4), 822}, // 956 RTE in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(23408, 4), 825}, // 957 RTN in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(23404, 4), 824}, // 958 RTP in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(23400, 4), 823}, // 959 RTZ in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(23444, 18), 828}, // 960 Horizontal2Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(23462, 18), 829}, // 961 Horizontal4Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(23412, 16), 826}, // 962 Vertical2Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(23428, 16), 827}, // 963 Vertical4Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(23503, 6), 834}, // 964 Const in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(23487, 11), 832}, // 965 DontInline in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(23480, 7), 831}, // 966 Inline in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(15759, 5), 830}, // 967 None in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(14766, 11), 835}, // 968 OptNoneEXT in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(14777, 13), 835}, // 969 OptNoneINTEL in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(23498, 5), 833}, // 970 Pure in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(23519, 6), 838}, // 971 ByVal in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23530, 8), 840}, // 972 NoAlias in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23538, 10), 841}, // 973 NoCapture in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23556, 12), 843}, // 974 NoReadWrite in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23548, 8), 842}, // 975 NoWrite in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23568, 21), 844}, // 976 RuntimeAlignedALTERA in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23589, 20), 844}, // 977 RuntimeAlignedINTEL in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23514, 5), 837}, // 978 Sext in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23525, 5), 839}, // 979 Sret in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23509, 5), 836}, // 980 Zext in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23644, 16), 848}, // 981 ClusteredReduce in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23630, 14), 847}, // 982 ExclusiveScan in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23616, 14), 846}, // 983 InclusiveScan in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23756, 28), 851}, // 984 PartitionedExclusiveScanEXT in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23784, 27), 851}, // 985 PartitionedExclusiveScanNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23701, 28), 850}, // 986 PartitionedInclusiveScanEXT in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23729, 27), 850}, // 987 PartitionedInclusiveScanNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23660, 21), 849}, // 988 PartitionedReduceEXT in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23681, 20), 849}, // 989 PartitionedReduceNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23609, 7), 845}, // 990 Reduce in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23811, 10), 852}, // 991 NoneINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(23821, 10), 853}, // 992 ReadINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(23842, 15), 855}, // 993 ReadWriteINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(23831, 11), 854}, // 994 WriteINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(23857, 5), 857}, // 995 Bias in SPV_OPERAND_TYPE_IMAGE
  {IR(23871, 12), 860}, // 996 ConstOffset in SPV_OPERAND_TYPE_IMAGE
  {IR(23883, 13), 862}, // 997 ConstOffsets in SPV_OPERAND_TYPE_IMAGE
  {IR(23866, 5), 859}, // 998 Grad in SPV_OPERAND_TYPE_IMAGE
  {IR(23862, 4), 858}, // 999 Lod in SPV_OPERAND_TYPE_IMAGE
  {IR(23896, 19), 865}, // 1000 MakeTexelAvailable in SPV_OPERAND_TYPE_IMAGE
  {IR(23915, 22), 865}, // 1001 MakeTexelAvailableKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(23937, 17), 866}, // 1002 MakeTexelVisible in SPV_OPERAND_TYPE_IMAGE
  {IR(23954, 20), 866}, // 1003 MakeTexelVisibleKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(9296, 7), 864}, // 1004 MinLod in SPV_OPERAND_TYPE_IMAGE
  {IR(23974, 16), 867}, // 1005 NonPrivateTexel in SPV_OPERAND_TYPE_IMAGE
  {IR(23990, 19), 867}, // 1006 NonPrivateTexelKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(15759, 5), 856}, // 1007 None in SPV_OPERAND_TYPE_IMAGE
  {IR(24062, 12), 871}, // 1008 Nontemporal in SPV_OPERAND_TYPE_IMAGE
  {IR(17166, 7), 861}, // 1009 Offset in SPV_OPERAND_TYPE_IMAGE
  {IR(24074, 8), 872}, // 1010 Offsets in SPV_OPERAND_TYPE_IMAGE
  {IR(16963, 7), 863}, // 1011 Sample in SPV_OPERAND_TYPE_IMAGE
  {IR(24040, 11), 869}, // 1012 SignExtend in SPV_OPERAND_TYPE_IMAGE
  {IR(24009, 14), 868}, // 1013 VolatileTexel in SPV_OPERAND_TYPE_IMAGE
  {IR(24023, 17), 868}, // 1014 VolatileTexelKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(24051, 11), 870}, // 1015 ZeroExtend in SPV_OPERAND_TYPE_IMAGE
  {IR(15656, 6), 887}, // 1016 Float in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24243, 10), 886}, // 1017 HalfFloat in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24178, 12), 881}, // 1018 SignedInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24190, 12), 882}, // 1019 SignedInt32 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24167, 11), 880}, // 1020 SignedInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24092, 11), 874}, // 1021 SnormInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24082, 10), 873}, // 1022 SnormInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24152, 15), 879}, // 1023 UnormInt101010 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24264, 17), 889}, // 1024 UnormInt101010_2 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24281, 16), 890}, // 1025 UnormInt10X6EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24414, 16), 897}, // 1026 UnormInt12X4EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24430, 16), 898}, // 1027 UnormInt14X2EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24113, 11), 876}, // 1028 UnormInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24253, 11), 888}, // 1029 UnormInt24 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24337, 20), 893}, // 1030 UnormInt2_101010EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24103, 10), 875}, // 1031 UnormInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24138, 14), 878}, // 1032 UnormShort555 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24124, 14), 877}, // 1033 UnormShort565 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24357, 19), 894}, // 1034 UnsignedInt10X6EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24376, 19), 895}, // 1035 UnsignedInt12X4EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24395, 19), 896}, // 1036 UnsignedInt14X2EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24215, 14), 884}, // 1037 UnsignedInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24229, 14), 885}, // 1038 UnsignedInt32 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24202, 13), 883}, // 1039 UnsignedInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24297, 20), 891}, // 1040 UnsignedIntRaw10EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24317, 20), 892}, // 1041 UnsignedIntRaw12EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24448, 2), 900}, // 1042 A in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24549, 5), 918}, // 1043 ABGR in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24470, 5), 906}, // 1044 ARGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24465, 5), 905}, // 1045 BGRA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24507, 6), 912}, // 1046 Depth in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24513, 13), 913}, // 1047 DepthStencil in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24475, 10), 907}, // 1048 Intensity in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24485, 10), 908}, // 1049 Luminance in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24446, 2), 899}, // 1050 R in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24453, 3), 902}, // 1051 RA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24450, 3), 901}, // 1052 RG in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24456, 4), 903}, // 1053 RGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24460, 5), 904}, // 1054 RGBA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24502, 5), 911}, // 1055 RGBx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24498, 4), 910}, // 1056 RGx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24495, 3), 909}, // 1057 Rx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24543, 6), 917}, // 1058 sBGRA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24526, 5), 914}, // 1059 sRGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24537, 6), 916}, // 1060 sRGBA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24531, 6), 915}, // 1061 sRGBx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24554, 28), 919}, // 1062 InitOnDeviceReprogramALTERA in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(24582, 27), 919}, // 1063 InitOnDeviceReprogramINTEL in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(24609, 24), 920}, // 1064 InitOnDeviceResetALTERA in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(24633, 23), 920}, // 1065 InitOnDeviceResetINTEL in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(24656, 7), 921}, // 1066 NoWait in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(24663, 11), 922}, // 1067 WaitKernel in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(24674, 14), 923}, // 1068 WaitWorkGroup in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(24688, 12), 925}, // 1069 CmdExecTime in SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {IR(15759, 5), 924}, // 1070 None in SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {IR(24700, 13), 927}, // 1071 MayUsePrintf in SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {IR(15759, 5), 926}, // 1072 None in SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {IR(24713, 7), 928}, // 1073 Export in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(24720, 7), 929}, // 1074 Import in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(24727, 12), 930}, // 1075 LinkOnceODR in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(24753, 12), 932}, // 1076 CachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(24805, 17), 935}, // 1077 ConstCachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(24780, 25), 934}, // 1078 InvalidateAfterReadINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(24765, 15), 933}, // 1079 StreamingINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(24739, 14), 931}, // 1080 UncachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(24945, 22), 948}, // 1081 DependencyArrayALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24967, 21), 948}, // 1082 DependencyArrayINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24840, 19), 939}, // 1083 DependencyInfinite in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24859, 17), 940}, // 1084 DependencyLength in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24829, 11), 938}, // 1085 DontUnroll in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19515, 25), 946}, // 1086 InitiationIntervalALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19540, 24), 946}, // 1087 InitiationIntervalINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24904, 18), 943}, // 1088 IterationMultiple in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24988, 19), 950}, // 1089 LoopCoalesceALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25007, 18), 950}, // 1090 LoopCoalesceINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25150, 16), 954}, // 1091 LoopCountALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25166, 15), 954}, // 1092 LoopCountINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19564, 21), 947}, // 1093 MaxConcurrencyALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19585, 20), 947}, // 1094 MaxConcurrencyINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25025, 22), 951}, // 1095 MaxInterleavingALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25047, 21), 951}, // 1096 MaxInterleavingINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24890, 14), 942}, // 1097 MaxIterations in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25181, 27), 955}, // 1098 MaxReinvocationDelayALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25208, 26), 955}, // 1099 MaxReinvocationDelayINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24876, 14), 941}, // 1100 MinIterations in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25121, 15), 953}, // 1101 NoFusionALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25136, 14), 953}, // 1102 NoFusionINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(15759, 5), 936}, // 1103 None in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24932, 13), 945}, // 1104 PartialCount in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24922, 10), 944}, // 1105 PeelCount in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19605, 21), 949}, // 1106 PipelineEnableALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19626, 20), 949}, // 1107 PipelineEnableINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25068, 27), 952}, // 1108 SpeculatedIterationsALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25095, 26), 952}, // 1109 SpeculatedIterationsINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24822, 7), 937}, // 1110 Unroll in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25517, 27), 969}, // 1111 MatrixAPackedBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25465, 26), 967}, // 1112 MatrixAPackedFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25385, 23), 963}, // 1113 MatrixAPackedInt4INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25339, 23), 961}, // 1114 MatrixAPackedInt8INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25234, 29), 957}, // 1115 MatrixASignedComponentsINTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25431, 17), 965}, // 1116 MatrixATF32INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25544, 27), 970}, // 1117 MatrixBPackedBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25491, 26), 968}, // 1118 MatrixBPackedFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25408, 23), 964}, // 1119 MatrixBPackedInt4INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25362, 23), 962}, // 1120 MatrixBPackedInt8INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25263, 29), 958}, // 1121 MatrixBSignedComponentsINTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25448, 17), 966}, // 1122 MatrixBTF32INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25292, 21), 959}, // 1123 MatrixCBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25313, 26), 960}, // 1124 MatrixResultBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(15759, 5), 956}, // 1125 None in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25704, 20), 978}, // 1126 AliasScopeINTELMask in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25571, 8), 973}, // 1127 Aligned in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25579, 21), 975}, // 1128 MakePointerAvailable in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25600, 24), 975}, // 1129 MakePointerAvailableKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25624, 19), 976}, // 1130 MakePointerVisible in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25643, 22), 976}, // 1131 MakePointerVisibleKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25724, 17), 979}, // 1132 NoAliasINTELMask in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25665, 18), 977}, // 1133 NonPrivatePointer in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25683, 21), 977}, // 1134 NonPrivatePointerKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(15759, 5), 971}, // 1135 None in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(24062, 12), 974}, // 1136 Nontemporal in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(16997, 9), 972}, // 1137 Volatile in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25748, 8), 981}, // 1138 GLSL450 in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(25756, 7), 982}, // 1139 OpenCL in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(25741, 7), 980}, // 1140 Simple in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(25763, 7), 983}, // 1141 Vulkan in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(25770, 10), 983}, // 1142 VulkanKHR in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(25788, 8), 985}, // 1143 Acquire in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25804, 15), 987}, // 1144 AcquireRelease in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25908, 20), 993}, // 1145 AtomicCounterMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25887, 21), 992}, // 1146 CrossWorkgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25928, 12), 994}, // 1147 ImageMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25969, 14), 996}, // 1148 MakeAvailable in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25983, 17), 996}, // 1149 MakeAvailableKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26000, 12), 997}, // 1150 MakeVisible in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26012, 15), 997}, // 1151 MakeVisibleKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(15759, 5), 984}, // 1152 None in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25940, 13), 995}, // 1153 OutputMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25953, 16), 995}, // 1154 OutputMemoryKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25780, 8), 984}, // 1155 Relaxed in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25796, 8), 986}, // 1156 Release in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25819, 23), 988}, // 1157 SequentiallyConsistent in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25856, 15), 990}, // 1158 SubgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25842, 14), 989}, // 1159 UniformMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(16997, 9), 998}, // 1160 Volatile in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25871, 16), 991}, // 1161 WorkgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26027, 10), 999}, // 1162 AutoINTEL in SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS
  {IR(26042, 4), 1001}, // 1163 SAT in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(26055, 8), 1003}, // 1164 SAT_SYM in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(26046, 9), 1002}, // 1165 SAT_ZERO in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(26037, 5), 1000}, // 1166 WRAP in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(26063, 25), 1004}, // 1167 PackedVectorFormat4x8Bit in SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {IR(26088, 28), 1004}, // 1168 PackedVectorFormat4x8BitKHR in SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {IR(26129, 4), 1007}, // 1169 RND in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26162, 9), 1011}, // 1170 RND_CONV in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26171, 13), 1012}, // 1171 RND_CONV_ODD in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26142, 8), 1009}, // 1172 RND_INF in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26150, 12), 1010}, // 1173 RND_MIN_INF in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26133, 9), 1008}, // 1174 RND_ZERO in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26116, 4), 1005}, // 1175 TRN in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26120, 9), 1006}, // 1176 TRN_ZERO in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(15759, 5), 1013}, // 1177 None in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(26184, 25), 1014}, // 1178 RobustnessPerComponentNV in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(26209, 23), 1015}, // 1179 RobustnessPerElementNV in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(26301, 27), 1021}, // 1180 CullBackFacingTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26328, 28), 1022}, // 1181 CullFrontFacingTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26370, 16), 1024}, // 1182 CullNoOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26356, 14), 1023}, // 1183 CullOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26440, 30), 1027}, // 1184 ForceOpacityMicromap2StateEXT in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26242, 12), 1018}, // 1185 NoOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(16511, 8), 1016}, // 1186 NoneKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26232, 10), 1017}, // 1187 OpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26427, 13), 1026}, // 1188 SkipAABBsKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26403, 24), 1025}, // 1189 SkipBuiltinPrimitivesNV in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26277, 24), 1020}, // 1190 SkipClosestHitShaderKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26386, 17), 1025}, // 1191 SkipTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26254, 23), 1019}, // 1192 TerminateOnFirstHitKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26511, 37), 1029}, // 1193 RayQueryCandidateIntersectionAABBKHR in SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {IR(26470, 41), 1028}, // 1194 RayQueryCandidateIntersectionTriangleKHR in SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {IR(26626, 42), 1032}, // 1195 RayQueryCommittedIntersectionGeneratedKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(26548, 37), 1030}, // 1196 RayQueryCommittedIntersectionNoneKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(26585, 41), 1031}, // 1197 RayQueryCommittedIntersectionTriangleKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(26668, 33), 1033}, // 1198 RayQueryCandidateIntersectionKHR in SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {IR(26701, 33), 1034}, // 1199 RayQueryCommittedIntersectionKHR in SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {IR(26746, 6), 1037}, // 1200 Clamp in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(26734, 12), 1036}, // 1201 ClampToEdge in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(15759, 5), 1035}, // 1202 None in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(26752, 7), 1038}, // 1203 Repeat in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(26759, 15), 1039}, // 1204 RepeatMirrored in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(26782, 7), 1041}, // 1205 Linear in SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {IR(26774, 8), 1040}, // 1206 Nearest in SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {IR(26847, 13), 1050}, // 1207 R11fG11fB10f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26889, 4), 1056}, // 1208 R16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26927, 9), 1061}, // 1209 R16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26860, 5), 1051}, // 1210 R16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26989, 5), 1070}, // 1211 R16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27060, 6), 1080}, // 1212 R16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26813, 5), 1045}, // 1213 R32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26967, 5), 1066}, // 1214 R32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27024, 6), 1075}, // 1215 R32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27077, 5), 1083}, // 1216 R64i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27071, 6), 1082}, // 1217 R64ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26893, 3), 1057}, // 1218 R8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26936, 8), 1062}, // 1219 R8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26994, 4), 1071}, // 1220 R8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27066, 5), 1081}, // 1221 R8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26880, 5), 1054}, // 1222 Rg16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26908, 10), 1059}, // 1223 Rg16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26841, 6), 1049}, // 1224 Rg16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26978, 6), 1068}, // 1225 Rg16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27047, 7), 1078}, // 1226 Rg16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26835, 6), 1048}, // 1227 Rg32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26972, 6), 1067}, // 1228 Rg32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27040, 7), 1077}, // 1229 Rg32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26885, 4), 1055}, // 1230 Rg8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26918, 9), 1060}, // 1231 Rg8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26984, 5), 1069}, // 1232 Rg8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27054, 6), 1079}, // 1233 Rg8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26872, 8), 1053}, // 1234 Rgb10A2 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27030, 10), 1076}, // 1235 Rgb10a2ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26865, 7), 1052}, // 1236 Rgba16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26896, 12), 1058}, // 1237 Rgba16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26805, 8), 1044}, // 1238 Rgba16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26952, 8), 1064}, // 1239 Rgba16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27007, 9), 1073}, // 1240 Rgba16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26797, 8), 1043}, // 1241 Rgba32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26944, 8), 1063}, // 1242 Rgba32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26998, 9), 1072}, // 1243 Rgba32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26818, 6), 1046}, // 1244 Rgba8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26824, 11), 1047}, // 1245 Rgba8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26960, 7), 1065}, // 1246 Rgba8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27016, 8), 1074}, // 1247 Rgba8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26789, 8), 1042}, // 1248 Unknown in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27082, 12), 1084}, // 1249 CrossDevice in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27094, 7), 1085}, // 1250 Device in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27120, 11), 1088}, // 1251 Invocation in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27131, 12), 1089}, // 1252 QueueFamily in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27143, 15), 1089}, // 1253 QueueFamilyKHR in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27158, 14), 1090}, // 1254 ShaderCallKHR in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27111, 9), 1087}, // 1255 Subgroup in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27101, 10), 1086}, // 1256 Workgroup in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27180, 12), 1093}, // 1257 DontFlatten in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(27172, 8), 1092}, // 1258 Flatten in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(15759, 5), 1091}, // 1259 None in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(27192, 29), 1094}, // 1260 IdentifierPossibleDuplicates in SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS
  {IR(15640, 8), 1096}, // 1261 Address in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15648, 8), 1097}, // 1262 Boolean in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15656, 6), 1098}, // 1263 Float in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15662, 7), 1099}, // 1264 Signed in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15669, 11), 1100}, // 1265 SignedChar in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15680, 9), 1101}, // 1266 Unsigned in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15689, 13), 1102}, // 1267 UnsignedChar in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15628, 12), 1095}, // 1268 Unspecified in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15702, 6), 1103}, // 1269 Class in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15708, 10), 1104}, // 1270 Structure in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15718, 6), 1105}, // 1271 Union in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15739, 20), 1107}, // 1272 ImportedDeclaration in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(15724, 15), 1106}, // 1273 ImportedModule in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(15848, 15), 1115}, // 1274 FlagArtificial in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15863, 13), 1116}, // 1275 FlagExplicit in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15836, 12), 1114}, // 1276 FlagFwdDecl in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15926, 21), 1120}, // 1277 FlagIndirectVariable in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15819, 17), 1113}, // 1278 FlagIsDefinition in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16003, 16), 1124}, // 1279 FlagIsEnumClass in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15807, 12), 1112}, // 1280 FlagIsLocal in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15987, 16), 1123}, // 1281 FlagIsOptimized in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15780, 14), 1110}, // 1282 FlagIsPrivate in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15764, 16), 1109}, // 1283 FlagIsProtected in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15794, 13), 1111}, // 1284 FlagIsPublic in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15947, 20), 1121}, // 1285 FlagLValueReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15891, 18), 1118}, // 1286 FlagObjectPointer in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15876, 15), 1117}, // 1287 FlagPrototyped in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15967, 20), 1122}, // 1288 FlagRValueReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15909, 17), 1119}, // 1289 FlagStaticMember in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16039, 24), 1126}, // 1290 FlagTypePassByReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16019, 20), 1125}, // 1291 FlagTypePassByValue in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(27221, 26), 1127}, // 1292 FlagUnknownPhysicalLayout in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15759, 5), 1108}, // 1293 None in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16124, 9), 1132}, // 1294 BitPiece in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16156, 7), 1136}, // 1295 Constu in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16063, 6), 1128}, // 1296 Deref in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16163, 9), 1137}, // 1297 Fragment in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16074, 6), 1130}, // 1298 Minus in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16069, 5), 1129}, // 1299 Plus in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16113, 11), 1131}, // 1300 PlusUconst in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16145, 11), 1135}, // 1301 StackValue in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16133, 5), 1133}, // 1302 Swap in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16138, 7), 1134}, // 1303 Xderef in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16208, 11), 1141}, // 1304 AtomicType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16172, 10), 1138}, // 1305 ConstType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16195, 13), 1140}, // 1306 RestrictType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16182, 13), 1139}, // 1307 VolatileType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(27282, 15), 1148}, // 1308 CPP_for_OpenCL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27247, 5), 1143}, // 1309 ESSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27252, 5), 1144}, // 1310 GLSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27302, 7), 1150}, // 1311 HERO_C in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27277, 5), 1147}, // 1312 HLSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27309, 5), 1151}, // 1313 NZSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27257, 9), 1145}, // 1314 OpenCL_C in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27266, 11), 1146}, // 1315 OpenCL_CPP in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27329, 5), 1155}, // 1316 Rust in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27297, 5), 1149}, // 1317 SYCL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27319, 6), 1153}, // 1318 Slang in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(26789, 8), 1142}, // 1319 Unknown in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27314, 5), 1152}, // 1320 WGSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27325, 4), 1154}, // 1321 Zig in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27416, 14), 1166}, // 1322 AtomicCounter in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27498, 16), 1172}, // 1323 CallableDataKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27514, 15), 1172}, // 1324 CallableDataNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27834, 17), 1182}, // 1325 CodeSectionINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27363, 15), 1161}, // 1326 CrossWorkgroup in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27851, 17), 1183}, // 1327 DeviceOnlyALTERA in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27868, 16), 1183}, // 1328 DeviceOnlyINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27386, 9), 1163}, // 1329 Function in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27395, 8), 1164}, // 1330 Generic in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27603, 16), 1175}, // 1331 HitAttributeKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27619, 15), 1175}, // 1332 HitAttributeNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27812, 22), 1181}, // 1333 HitObjectAttributeEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27767, 21), 1179}, // 1334 HitObjectAttributeNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27884, 15), 1184}, // 1335 HostOnlyALTERA in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27899, 14), 1184}, // 1336 HostOnlyINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27430, 6), 1167}, // 1337 Image in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27529, 24), 1173}, // 1338 IncomingCallableDataKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27553, 23), 1173}, // 1339 IncomingCallableDataNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27634, 22), 1176}, // 1340 IncomingRayPayloadKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27656, 21), 1176}, // 1341 IncomingRayPayloadNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27350, 6), 1157}, // 1342 Input in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27482, 16), 1171}, // 1343 NodePayloadAMDX in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27356, 7), 1159}, // 1344 Output in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27720, 22), 1178}, // 1345 PhysicalStorageBuffer in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27742, 25), 1178}, // 1346 PhysicalStorageBufferEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27378, 8), 1162}, // 1347 Private in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27403, 13), 1165}, // 1348 PushConstant in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27576, 14), 1174}, // 1349 RayPayloadKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27590, 13), 1174}, // 1350 RayPayloadNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27677, 22), 1177}, // 1351 ShaderRecordBufferKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27699, 21), 1177}, // 1352 ShaderRecordBufferNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27436, 14), 1168}, // 1353 StorageBuffer in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27788, 24), 1180}, // 1354 TaskPayloadWorkgroupEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27463, 19), 1170}, // 1355 TileAttachmentQCOM in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27450, 13), 1169}, // 1356 TileImageEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(17048, 8), 1158}, // 1357 Uniform in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27334, 16), 1156}, // 1358 UniformConstant in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27101, 10), 1160}, // 1359 Workgroup in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24765, 15), 1188}, // 1360 StreamingINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(24739, 14), 1185}, // 1361 UncachedINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(27931, 15), 1187}, // 1362 WriteBackINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(27913, 18), 1186}, // 1363 WriteThroughINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(27957, 11), 1191}, // 1364 DecodeFunc in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(15759, 5), 1189}, // 1365 None in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(27946, 11), 1190}, // 1366 TensorView in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(26734, 12), 1194}, // 1367 ClampToEdge in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(17006, 9), 1193}, // 1368 Constant in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(26752, 7), 1195}, // 1369 Repeat in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(26759, 15), 1196}, // 1370 RepeatMirrored in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(27968, 10), 1192}, // 1371 Undefined in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(28021, 24), 1200}, // 1372 MakeElementAvailableARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(28045, 22), 1201}, // 1373 MakeElementVisibleARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(28067, 21), 1202}, // 1374 NonPrivateElementARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(27978, 8), 1197}, // 1375 NoneARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(27986, 15), 1198}, // 1376 NontemporalARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(28001, 20), 1199}, // 1377 OutOfBoundsValueARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
}};

IndexRange OperandNameRangeForKind(spv_operand_type_t type) {
  switch(type) {
    case SPV_OPERAND_TYPE_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_ADDRESSING_MODEL: return IR(3, 5);
    case SPV_OPERAND_TYPE_BUILT_IN: return IR(8, 150);
    case SPV_OPERAND_TYPE_CAPABILITY: return IR(158, 330);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(488, 8);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(496, 3);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(499, 2);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS: return IR(501, 19);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION: return IR(520, 10);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(530, 4);
    case SPV_OPERAND_TYPE_COMPONENT_TYPE: return IR(534, 15);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT: return IR(549, 4);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS: return IR(553, 6);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE: return IR(559, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE: return IR(562, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT: return IR(565, 4);
    case SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(569, 8);
    case SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE: return IR(577, 3);
    case SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS: return IR(580, 16);
    case SPV_OPERAND_TYPE_DEBUG_OPERATION: return IR(596, 9);
    case SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER: return IR(605, 3);
    case SPV_OPERAND_TYPE_DECORATION: return IR(608, 197);
    case SPV_OPERAND_TYPE_DIMENSIONALITY: return IR(805, 8);
    case SPV_OPERAND_TYPE_EXECUTION_MODE: return IR(813, 102);
    case SPV_OPERAND_TYPE_EXECUTION_MODEL: return IR(915, 23);
    case SPV_OPERAND_TYPE_FPDENORM_MODE: return IR(938, 2);
    case SPV_OPERAND_TYPE_FPENCODING: return IR(940, 3);
    case SPV_OPERAND_TYPE_FPOPERATION_MODE: return IR(943, 2);
    case SPV_OPERAND_TYPE_FP_FAST_MATH_MODE: return IR(945, 11);
    case SPV_OPERAND_TYPE_FP_ROUNDING_MODE: return IR(956, 4);
    case SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE: return IR(960, 4);
    case SPV_OPERAND_TYPE_FUNCTION_CONTROL: return IR(964, 7);
    case SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE: return IR(971, 10);
    case SPV_OPERAND_TYPE_GROUP_OPERATION: return IR(981, 10);
    case SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER: return IR(991, 4);
    case SPV_OPERAND_TYPE_IMAGE: return IR(995, 21);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE: return IR(1016, 26);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER: return IR(1042, 20);
    case SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER: return IR(1062, 4);
    case SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS: return IR(1066, 3);
    case SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO: return IR(1069, 2);
    case SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS: return IR(1071, 2);
    case SPV_OPERAND_TYPE_LINKAGE_TYPE: return IR(1073, 3);
    case SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL: return IR(1076, 5);
    case SPV_OPERAND_TYPE_LOOP_CONTROL: return IR(1081, 30);
    case SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(1111, 15);
    case SPV_OPERAND_TYPE_MEMORY_ACCESS: return IR(1126, 12);
    case SPV_OPERAND_TYPE_MEMORY_MODEL: return IR(1138, 5);
    case SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID: return IR(1143, 19);
    case SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS: return IR(1162, 1);
    case SPV_OPERAND_TYPE_OVERFLOW_MODES: return IR(1163, 4);
    case SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT: return IR(1167, 2);
    case SPV_OPERAND_TYPE_QUANTIZATION_MODES: return IR(1169, 8);
    case SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS: return IR(1177, 3);
    case SPV_OPERAND_TYPE_RAY_FLAGS: return IR(1180, 13);
    case SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE: return IR(1193, 2);
    case SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE: return IR(1195, 3);
    case SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION: return IR(1198, 2);
    case SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE: return IR(1200, 5);
    case SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE: return IR(1205, 2);
    case SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT: return IR(1207, 42);
    case SPV_OPERAND_TYPE_SCOPE_ID: return IR(1249, 8);
    case SPV_OPERAND_TYPE_SELECTION_CONTROL: return IR(1257, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS: return IR(1260, 1);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(1261, 8);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(1269, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(1272, 2);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS: return IR(1274, 20);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION: return IR(1294, 10);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(1304, 4);
    case SPV_OPERAND_TYPE_SOURCE_LANGUAGE: return IR(1308, 14);
    case SPV_OPERAND_TYPE_STORAGE_CLASS: return IR(1322, 38);
    case SPV_OPERAND_TYPE_STORE_CACHE_CONTROL: return IR(1360, 4);
    case SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS: return IR(1364, 3);
    case SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE: return IR(1367, 5);
    case SPV_OPERAND_TYPE_TENSOR_OPERANDS: return IR(1372, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_IMAGE: return IR(995, 21);
    case SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS: return IR(1126, 12);
    case SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT: return IR(1167, 2);
    case SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS: return IR(553, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(1111, 15);
    case SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS: return IR(1177, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_FPENCODING: return IR(940, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS: return IR(1372, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_CAPABILITY: return IR(158, 330);
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
static const std::array<InstructionDesc, 863> kInstructionDesc{{
  {spv::Op::OpNop, false, false, IR(0, 0), IR(28088, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpUndef, true, true, IR(39, 2), IR(28144, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpSourceContinued, false, false, IR(11, 1), IR(28150, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpSource, false, false, IR(41, 4), IR(28269, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpSourceExtension, false, false, IR(11, 1), IR(28276, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpName, false, false, IR(45, 2), IR(28292, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpMemberName, false, false, IR(47, 3), IR(28297, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpString, true, false, IR(50, 2), IR(28308, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpLine, false, false, IR(52, 3), IR(28315, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpExtension, false, false, IR(11, 1), IR(28320, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpExtInstImport, true, false, IR(50, 2), IR(28330, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpExtInst, true, true, IR(55, 4), IR(28390, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpMemoryModel, false, false, IR(59, 2), IR(28462, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpEntryPoint, false, false, IR(61, 4), IR(28536, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpExecutionMode, false, false, IR(65, 2), IR(28579, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpCapability, false, false, IR(67, 1), IR(28621, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpTypeVoid, true, false, IR(68, 1), IR(28632, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeBool, true, false, IR(68, 1), IR(28641, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeInt, true, false, IR(69, 3), IR(28650, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeFloat, true, false, IR(72, 3), IR(28695, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeVector, true, false, IR(75, 3), IR(28705, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeMatrix, true, false, IR(75, 3), IR(28716, 11), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeImage, true, false, IR(78, 9), IR(28840, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeSampler, true, false, IR(68, 1), IR(28850, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeSampledImage, true, false, IR(87, 2), IR(28862, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeArray, true, false, IR(89, 3), IR(28879, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeRuntimeArray, true, false, IR(87, 2), IR(28889, 17), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeStruct, true, false, IR(92, 2), IR(28906, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeOpaque, true, false, IR(50, 2), IR(28917, 11), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypePointer, true, false, IR(94, 3), IR(28959, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeFunction, true, false, IR(97, 3), IR(28971, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeEvent, true, false, IR(68, 1), IR(28984, 10), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeDeviceEvent, true, false, IR(68, 1), IR(28994, 16), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeReserveId, true, false, IR(68, 1), IR(29010, 14), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeQueue, true, false, IR(68, 1), IR(29024, 10), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypePipe, true, false, IR(100, 2), IR(29034, 9), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeForwardPointer, false, false, IR(102, 2), IR(29043, 19), IR(0, 0), IR(209, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantTrue, true, true, IR(39, 2), IR(29062, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantFalse, true, true, IR(39, 2), IR(29075, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstant, true, true, IR(104, 3), IR(17006, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantComposite, true, true, IR(107, 3), IR(29127, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantSampler, true, true, IR(110, 5), IR(29223, 16), IR(0, 0), IR(211, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantNull, true, true, IR(39, 2), IR(29239, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantTrue, true, true, IR(39, 2), IR(29252, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantFalse, true, true, IR(39, 2), IR(29269, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstant, true, true, IR(104, 3), IR(29287, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantComposite, true, true, IR(107, 3), IR(29300, 22), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantOp, true, true, IR(115, 3), IR(29363, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpFunction, true, true, IR(118, 4), IR(27386, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionParameter, true, true, IR(39, 2), IR(29412, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionEnd, false, false, IR(0, 0), IR(29430, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionCall, true, true, IR(122, 4), IR(29442, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpVariable, true, true, IR(126, 4), IR(29455, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpImageTexelPointer, true, true, IR(130, 5), IR(29464, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpLoad, true, true, IR(135, 4), IR(29522, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpStore, false, false, IR(139, 3), IR(29527, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCopyMemory, false, false, IR(142, 4), IR(29533, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCopyMemorySized, false, false, IR(146, 5), IR(29544, 16), IR(0, 0), IR(212, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpAccessChain, true, true, IR(122, 4), IR(29560, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpInBoundsAccessChain, true, true, IR(122, 4), IR(29572, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrAccessChain, true, true, IR(151, 5), IR(29592, 15), IR(0, 0), IR(214, 4), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpArrayLength, true, true, IR(156, 4), IR(29607, 12), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpGenericPtrMemSemantics, true, true, IR(160, 3), IR(29619, 23), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpInBoundsPtrAccessChain, true, true, IR(151, 5), IR(29642, 23), IR(0, 0), IR(1, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpDecorate, false, false, IR(163, 2), IR(29693, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpMemberDecorate, false, false, IR(165, 3), IR(29702, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpDecorationGroup, true, false, IR(68, 1), IR(29717, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupDecorate, false, false, IR(168, 2), IR(29733, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupMemberDecorate, false, false, IR(170, 2), IR(29792, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpVectorExtractDynamic, true, true, IR(172, 4), IR(29812, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpVectorInsertDynamic, true, true, IR(130, 5), IR(29833, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpVectorShuffle, true, true, IR(176, 5), IR(29853, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeConstruct, true, true, IR(107, 3), IR(29867, 19), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeExtract, true, true, IR(181, 4), IR(29886, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeInsert, true, true, IR(176, 5), IR(29903, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCopyObject, true, true, IR(160, 3), IR(29919, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpTranspose, true, true, IR(160, 3), IR(29930, 10), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpSampledImage, true, true, IR(172, 4), IR(29940, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleImplicitLod, true, true, IR(185, 5), IR(29985, 23), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleExplicitLod, true, true, IR(190, 5), IR(30031, 23), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleDrefImplicitLod, true, true, IR(195, 6), IR(30054, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleDrefExplicitLod, true, true, IR(201, 6), IR(30081, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjImplicitLod, true, true, IR(185, 5), IR(30108, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjExplicitLod, true, true, IR(190, 5), IR(30135, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjDrefImplicitLod, true, true, IR(195, 6), IR(30162, 31), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjDrefExplicitLod, true, true, IR(201, 6), IR(30193, 31), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageFetch, true, true, IR(185, 5), IR(30224, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageGather, true, true, IR(195, 6), IR(30235, 12), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageDrefGather, true, true, IR(195, 6), IR(30247, 16), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageRead, true, true, IR(185, 5), IR(30263, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageWrite, false, false, IR(207, 4), IR(30273, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImage, true, true, IR(160, 3), IR(27430, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryFormat, true, true, IR(160, 3), IR(30284, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryOrder, true, true, IR(160, 3), IR(30301, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySizeLod, true, true, IR(172, 4), IR(30317, 18), IR(0, 0), IR(218, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySize, true, true, IR(160, 3), IR(30335, 15), IR(0, 0), IR(218, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryLod, true, true, IR(172, 4), IR(30350, 14), IR(0, 0), IR(220, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryLevels, true, true, IR(160, 3), IR(30364, 17), IR(0, 0), IR(218, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySamples, true, true, IR(160, 3), IR(30381, 18), IR(0, 0), IR(218, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertFToU, true, true, IR(160, 3), IR(30399, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertFToS, true, true, IR(160, 3), IR(30411, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertSToF, true, true, IR(160, 3), IR(30423, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToF, true, true, IR(160, 3), IR(30435, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpUConvert, true, true, IR(160, 3), IR(30447, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSConvert, true, true, IR(160, 3), IR(30456, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpFConvert, true, true, IR(160, 3), IR(30465, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpQuantizeToF16, true, true, IR(160, 3), IR(30474, 14), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertPtrToU, true, true, IR(160, 3), IR(30488, 14), IR(0, 0), IR(209, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSatConvertSToU, true, true, IR(160, 3), IR(30502, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSatConvertUToS, true, true, IR(160, 3), IR(30517, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToPtr, true, true, IR(160, 3), IR(30532, 14), IR(0, 0), IR(209, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpPtrCastToGeneric, true, true, IR(160, 3), IR(30546, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpGenericCastToPtr, true, true, IR(160, 3), IR(30563, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpGenericCastToPtrExplicit, true, true, IR(211, 4), IR(30580, 25), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpBitcast, true, true, IR(160, 3), IR(30605, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSNegate, true, true, IR(160, 3), IR(30613, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFNegate, true, true, IR(160, 3), IR(30621, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIAdd, true, true, IR(172, 4), IR(30629, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFAdd, true, true, IR(172, 4), IR(30634, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpISub, true, true, IR(172, 4), IR(30639, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFSub, true, true, IR(172, 4), IR(30644, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIMul, true, true, IR(172, 4), IR(30649, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFMul, true, true, IR(172, 4), IR(30654, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDiv, true, true, IR(172, 4), IR(30659, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSDiv, true, true, IR(172, 4), IR(30664, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFDiv, true, true, IR(172, 4), IR(30669, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUMod, true, true, IR(172, 4), IR(30674, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSRem, true, true, IR(172, 4), IR(30679, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSMod, true, true, IR(172, 4), IR(30684, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFRem, true, true, IR(172, 4), IR(30689, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFMod, true, true, IR(172, 4), IR(30694, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpVectorTimesScalar, true, true, IR(172, 4), IR(30699, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesScalar, true, true, IR(172, 4), IR(30717, 18), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpVectorTimesMatrix, true, true, IR(172, 4), IR(30735, 18), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesVector, true, true, IR(172, 4), IR(30753, 18), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesMatrix, true, true, IR(172, 4), IR(30771, 18), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpOuterProduct, true, true, IR(172, 4), IR(30789, 13), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpDot, true, true, IR(172, 4), IR(30802, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIAddCarry, true, true, IR(172, 4), IR(30806, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpISubBorrow, true, true, IR(172, 4), IR(30816, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUMulExtended, true, true, IR(172, 4), IR(30827, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSMulExtended, true, true, IR(172, 4), IR(30840, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpAny, true, true, IR(160, 3), IR(30853, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpAll, true, true, IR(160, 3), IR(30857, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsNan, true, true, IR(160, 3), IR(30861, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsInf, true, true, IR(160, 3), IR(30867, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsFinite, true, true, IR(160, 3), IR(30873, 9), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsNormal, true, true, IR(160, 3), IR(30882, 9), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSignBitSet, true, true, IR(160, 3), IR(30891, 11), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLessOrGreater, true, true, IR(172, 4), IR(30902, 14), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), SPV_SPIRV_VERSION_WORD(1,5), PrintingClass::kRelational_and_Logical},
  {spv::Op::OpOrdered, true, true, IR(172, 4), IR(30916, 8), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUnordered, true, true, IR(172, 4), IR(30924, 10), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalEqual, true, true, IR(172, 4), IR(30934, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalNotEqual, true, true, IR(172, 4), IR(30947, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalOr, true, true, IR(172, 4), IR(30963, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalAnd, true, true, IR(172, 4), IR(30973, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalNot, true, true, IR(160, 3), IR(30984, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSelect, true, true, IR(130, 5), IR(30995, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIEqual, true, true, IR(172, 4), IR(31002, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpINotEqual, true, true, IR(172, 4), IR(31009, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUGreaterThan, true, true, IR(172, 4), IR(31019, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSGreaterThan, true, true, IR(172, 4), IR(31032, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUGreaterThanEqual, true, true, IR(172, 4), IR(31045, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSGreaterThanEqual, true, true, IR(172, 4), IR(31063, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpULessThan, true, true, IR(172, 4), IR(31081, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSLessThan, true, true, IR(172, 4), IR(31091, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpULessThanEqual, true, true, IR(172, 4), IR(31101, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSLessThanEqual, true, true, IR(172, 4), IR(31116, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdEqual, true, true, IR(172, 4), IR(31131, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordEqual, true, true, IR(172, 4), IR(31141, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdNotEqual, true, true, IR(172, 4), IR(31153, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordNotEqual, true, true, IR(172, 4), IR(31166, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdLessThan, true, true, IR(172, 4), IR(31181, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordLessThan, true, true, IR(172, 4), IR(31194, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdGreaterThan, true, true, IR(172, 4), IR(31209, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordGreaterThan, true, true, IR(172, 4), IR(31225, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdLessThanEqual, true, true, IR(172, 4), IR(31243, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordLessThanEqual, true, true, IR(172, 4), IR(31261, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdGreaterThanEqual, true, true, IR(172, 4), IR(31281, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordGreaterThanEqual, true, true, IR(172, 4), IR(31302, 23), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpShiftRightLogical, true, true, IR(172, 4), IR(31325, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpShiftRightArithmetic, true, true, IR(172, 4), IR(31343, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpShiftLeftLogical, true, true, IR(172, 4), IR(31364, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseOr, true, true, IR(172, 4), IR(31381, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseXor, true, true, IR(172, 4), IR(31391, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseAnd, true, true, IR(172, 4), IR(31402, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpNot, true, true, IR(160, 3), IR(31413, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldInsert, true, true, IR(215, 6), IR(31417, 15), IR(0, 0), IR(221, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldSExtract, true, true, IR(130, 5), IR(31432, 17), IR(0, 0), IR(221, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldUExtract, true, true, IR(130, 5), IR(31449, 17), IR(0, 0), IR(221, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitReverse, true, true, IR(160, 3), IR(31466, 11), IR(0, 0), IR(221, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitCount, true, true, IR(160, 3), IR(31477, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpDPdx, true, true, IR(160, 3), IR(31486, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdy, true, true, IR(160, 3), IR(31491, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidth, true, true, IR(160, 3), IR(31496, 7), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdxFine, true, true, IR(160, 3), IR(31503, 9), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdyFine, true, true, IR(160, 3), IR(31512, 9), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidthFine, true, true, IR(160, 3), IR(31521, 11), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdxCoarse, true, true, IR(160, 3), IR(31532, 11), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdyCoarse, true, true, IR(160, 3), IR(31543, 11), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidthCoarse, true, true, IR(160, 3), IR(31554, 13), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpEmitVertex, false, false, IR(0, 0), IR(31567, 11), IR(0, 0), IR(70, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEndPrimitive, false, false, IR(0, 0), IR(31578, 13), IR(0, 0), IR(70, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEmitStreamVertex, false, false, IR(10, 1), IR(31591, 17), IR(0, 0), IR(119, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEndStreamPrimitive, false, false, IR(10, 1), IR(31608, 19), IR(0, 0), IR(119, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpControlBarrier, false, false, IR(221, 3), IR(31664, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpMemoryBarrier, false, false, IR(224, 2), IR(31679, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpAtomicLoad, true, true, IR(226, 5), IR(31693, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicStore, false, false, IR(231, 4), IR(31704, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicExchange, true, true, IR(235, 6), IR(31716, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicCompareExchange, true, true, IR(241, 8), IR(31731, 22), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicCompareExchangeWeak, true, true, IR(241, 8), IR(31753, 26), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), SPV_SPIRV_VERSION_WORD(1,3), PrintingClass::kAtomic},
  {spv::Op::OpAtomicIIncrement, true, true, IR(226, 5), IR(31779, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicIDecrement, true, true, IR(226, 5), IR(31796, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicIAdd, true, true, IR(235, 6), IR(31813, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicISub, true, true, IR(235, 6), IR(31824, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicSMin, true, true, IR(235, 6), IR(31835, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicUMin, true, true, IR(235, 6), IR(31846, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicSMax, true, true, IR(235, 6), IR(31857, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicUMax, true, true, IR(235, 6), IR(31868, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicAnd, true, true, IR(235, 6), IR(31879, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicOr, true, true, IR(235, 6), IR(31889, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicXor, true, true, IR(235, 6), IR(31898, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpPhi, true, true, IR(107, 3), IR(31908, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLoopMerge, false, false, IR(249, 3), IR(31942, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpSelectionMerge, false, false, IR(252, 2), IR(31987, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLabel, true, false, IR(68, 1), IR(32002, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpBranch, false, false, IR(10, 1), IR(32008, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpBranchConditional, false, false, IR(254, 4), IR(32015, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpSwitch, false, false, IR(258, 3), IR(32078, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpKill, false, false, IR(0, 0), IR(32085, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpReturn, false, false, IR(0, 0), IR(32090, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpReturnValue, false, false, IR(10, 1), IR(32097, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpUnreachable, false, false, IR(0, 0), IR(32109, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLifetimeStart, false, false, IR(261, 2), IR(32121, 14), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLifetimeStop, false, false, IR(261, 2), IR(32135, 13), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpGroupAsyncCopy, true, true, IR(263, 8), IR(32148, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupWaitEvents, false, false, IR(271, 3), IR(32163, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupAll, true, true, IR(274, 4), IR(32179, 9), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupAny, true, true, IR(274, 4), IR(32188, 9), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBroadcast, true, true, IR(278, 5), IR(32197, 15), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupIAdd, true, true, IR(283, 5), IR(32245, 10), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFAdd, true, true, IR(283, 5), IR(32255, 10), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMin, true, true, IR(283, 5), IR(32265, 10), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMin, true, true, IR(283, 5), IR(32275, 10), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMin, true, true, IR(283, 5), IR(32285, 10), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMax, true, true, IR(283, 5), IR(32295, 10), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMax, true, true, IR(283, 5), IR(32305, 10), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMax, true, true, IR(283, 5), IR(32315, 10), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpReadPipe, true, true, IR(215, 6), IR(32325, 9), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpWritePipe, true, true, IR(215, 6), IR(32334, 10), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReservedReadPipe, true, true, IR(288, 8), IR(32344, 17), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReservedWritePipe, true, true, IR(288, 8), IR(32361, 18), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReserveReadPipePackets, true, true, IR(215, 6), IR(32379, 23), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReserveWritePipePackets, true, true, IR(215, 6), IR(32402, 24), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCommitReadPipe, false, false, IR(296, 4), IR(32426, 15), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCommitWritePipe, false, false, IR(296, 4), IR(32441, 16), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpIsValidReserveId, true, true, IR(160, 3), IR(32457, 17), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetNumPipePackets, true, true, IR(130, 5), IR(32474, 18), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetMaxPipePackets, true, true, IR(130, 5), IR(32492, 18), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupReserveReadPipePackets, true, true, IR(300, 7), IR(32510, 28), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupReserveWritePipePackets, true, true, IR(300, 7), IR(32538, 29), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupCommitReadPipe, false, false, IR(307, 5), IR(32567, 20), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupCommitWritePipe, false, false, IR(307, 5), IR(32587, 21), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpEnqueueMarker, true, true, IR(215, 6), IR(32608, 14), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpEnqueueKernel, true, true, IR(312, 13), IR(32622, 14), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelNDrangeSubGroupCount, true, true, IR(325, 7), IR(32636, 30), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelNDrangeMaxSubGroupSize, true, true, IR(325, 7), IR(32666, 32), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelWorkGroupSize, true, true, IR(215, 6), IR(32698, 23), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelPreferredWorkGroupSizeMultiple, true, true, IR(215, 6), IR(32721, 40), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpRetainEvent, false, false, IR(10, 1), IR(32761, 12), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpReleaseEvent, false, false, IR(10, 1), IR(32773, 13), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpCreateUserEvent, true, true, IR(39, 2), IR(32786, 16), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpIsValidEvent, true, true, IR(160, 3), IR(32802, 13), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpSetUserEventStatus, false, false, IR(36, 2), IR(32815, 19), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpCaptureEventProfilingInfo, false, false, IR(33, 3), IR(32834, 26), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetDefaultQueue, true, true, IR(39, 2), IR(32860, 16), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpBuildNDRange, true, true, IR(130, 5), IR(32876, 13), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpImageSparseSampleImplicitLod, true, true, IR(185, 5), IR(32889, 29), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleExplicitLod, true, true, IR(190, 5), IR(32918, 29), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleDrefImplicitLod, true, true, IR(195, 6), IR(32947, 33), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleDrefExplicitLod, true, true, IR(201, 6), IR(32980, 33), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjImplicitLod, true, true, IR(185, 5), IR(33013, 33), IR(0, 0), IR(225, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjExplicitLod, true, true, IR(190, 5), IR(33046, 33), IR(0, 0), IR(225, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjDrefImplicitLod, true, true, IR(195, 6), IR(33079, 37), IR(0, 0), IR(225, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjDrefExplicitLod, true, true, IR(201, 6), IR(33116, 37), IR(0, 0), IR(225, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseFetch, true, true, IR(185, 5), IR(33153, 17), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseGather, true, true, IR(195, 6), IR(33170, 18), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseDrefGather, true, true, IR(195, 6), IR(33188, 22), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseTexelsResident, true, true, IR(160, 3), IR(33210, 26), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpNoLine, false, false, IR(0, 0), IR(33236, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpAtomicFlagTestAndSet, true, true, IR(226, 5), IR(33243, 21), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicFlagClear, false, false, IR(332, 3), IR(33264, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpImageSparseRead, true, true, IR(185, 5), IR(33280, 16), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpSizeOf, true, true, IR(160, 3), IR(33296, 7), IR(0, 0), IR(1, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpTypePipeStorage, true, false, IR(68, 1), IR(33303, 16), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantPipeStorage, true, true, IR(335, 5), IR(33319, 20), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCreatePipeFromPipeStorage, true, true, IR(160, 3), IR(33339, 26), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetKernelLocalSizeForSubgroupCount, true, true, IR(325, 7), IR(33365, 35), IR(0, 0), IR(160, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelMaxNumSubgroups, true, true, IR(215, 6), IR(33400, 25), IR(0, 0), IR(160, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpTypeNamedBarrier, true, false, IR(68, 1), IR(33425, 17), IR(0, 0), IR(227, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpNamedBarrierInitialize, true, true, IR(160, 3), IR(33442, 23), IR(0, 0), IR(227, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpMemoryNamedBarrier, false, false, IR(332, 3), IR(33465, 19), IR(0, 0), IR(227, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpModuleProcessed, false, false, IR(11, 1), IR(33484, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpExecutionModeId, false, false, IR(65, 2), IR(33500, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,2), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpDecorateId, false, false, IR(163, 2), IR(33516, 11), IR(0, 0), IR(1, 0), IR(184, 1), SPV_SPIRV_VERSION_WORD(1,2), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupNonUniformElect, true, true, IR(340, 3), IR(33527, 21), IR(0, 0), IR(77, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAll, true, true, IR(274, 4), IR(33548, 19), IR(0, 0), IR(228, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAny, true, true, IR(274, 4), IR(33567, 19), IR(0, 0), IR(228, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAllEqual, true, true, IR(274, 4), IR(33586, 24), IR(0, 0), IR(228, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBroadcast, true, true, IR(278, 5), IR(33610, 25), IR(0, 0), IR(229, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBroadcastFirst, true, true, IR(274, 4), IR(33635, 30), IR(0, 0), IR(229, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallot, true, true, IR(274, 4), IR(6483, 22), IR(0, 0), IR(229, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformInverseBallot, true, true, IR(274, 4), IR(33665, 29), IR(0, 0), IR(229, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotBitExtract, true, true, IR(278, 5), IR(33694, 32), IR(0, 0), IR(229, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotBitCount, true, true, IR(283, 5), IR(33726, 30), IR(0, 0), IR(229, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotFindLSB, true, true, IR(274, 4), IR(33756, 29), IR(0, 0), IR(229, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotFindMSB, true, true, IR(274, 4), IR(33785, 29), IR(0, 0), IR(229, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffle, true, true, IR(278, 5), IR(9622, 23), IR(0, 0), IR(230, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleXor, true, true, IR(278, 5), IR(33814, 26), IR(0, 0), IR(230, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleUp, true, true, IR(278, 5), IR(33840, 25), IR(0, 0), IR(231, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleDown, true, true, IR(278, 5), IR(33865, 27), IR(0, 0), IR(231, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformIAdd, true, true, IR(343, 6), IR(33892, 20), IR(0, 0), IR(232, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFAdd, true, true, IR(343, 6), IR(33912, 20), IR(0, 0), IR(232, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformIMul, true, true, IR(343, 6), IR(33932, 20), IR(0, 0), IR(232, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMul, true, true, IR(343, 6), IR(33952, 20), IR(0, 0), IR(232, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformSMin, true, true, IR(343, 6), IR(33972, 20), IR(0, 0), IR(232, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformUMin, true, true, IR(343, 6), IR(33992, 20), IR(0, 0), IR(232, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMin, true, true, IR(343, 6), IR(34012, 20), IR(0, 0), IR(232, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformSMax, true, true, IR(343, 6), IR(34032, 20), IR(0, 0), IR(232, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformUMax, true, true, IR(343, 6), IR(34052, 20), IR(0, 0), IR(232, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMax, true, true, IR(343, 6), IR(34072, 20), IR(0, 0), IR(232, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseAnd, true, true, IR(343, 6), IR(34092, 26), IR(0, 0), IR(232, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseOr, true, true, IR(343, 6), IR(34118, 25), IR(0, 0), IR(232, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseXor, true, true, IR(343, 6), IR(34143, 26), IR(0, 0), IR(232, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalAnd, true, true, IR(343, 6), IR(34169, 26), IR(0, 0), IR(232, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalOr, true, true, IR(343, 6), IR(34195, 25), IR(0, 0), IR(232, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalXor, true, true, IR(343, 6), IR(34220, 26), IR(0, 0), IR(232, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadBroadcast, true, true, IR(278, 5), IR(34246, 29), IR(0, 0), IR(235, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadSwap, true, true, IR(278, 5), IR(34275, 24), IR(0, 0), IR(235, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpCopyLogical, true, true, IR(160, 3), IR(34299, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpPtrEqual, true, true, IR(172, 4), IR(34311, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrNotEqual, true, true, IR(172, 4), IR(34320, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrDiff, true, true, IR(172, 4), IR(34332, 8), IR(0, 0), IR(236, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpColorAttachmentReadEXT, true, true, IR(349, 4), IR(34340, 23), IR(0, 0), IR(152, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpDepthAttachmentReadEXT, true, true, IR(353, 3), IR(34363, 23), IR(0, 0), IR(161, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpStencilAttachmentReadEXT, true, true, IR(353, 3), IR(34386, 25), IR(0, 0), IR(162, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpTypeTensorARM, true, false, IR(356, 4), IR(34411, 14), IR(0, 0), IR(208, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTensorReadARM, true, true, IR(360, 5), IR(34467, 14), IR(0, 0), IR(208, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpTensorWriteARM, false, false, IR(365, 4), IR(34481, 15), IR(0, 0), IR(208, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpTensorQuerySizeARM, true, true, IR(172, 4), IR(34496, 19), IR(0, 0), IR(208, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpGraphConstantARM, true, true, IR(369, 3), IR(34515, 17), IR(0, 0), IR(239, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphEntryPointARM, false, false, IR(372, 3), IR(34532, 19), IR(0, 0), IR(239, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphARM, true, true, IR(39, 2), IR(9913, 9), IR(0, 0), IR(239, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphInputARM, true, true, IR(122, 4), IR(34551, 14), IR(0, 0), IR(239, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphSetOutputARM, false, false, IR(375, 3), IR(34565, 18), IR(0, 0), IR(239, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphEndARM, false, false, IR(0, 0), IR(34583, 12), IR(0, 0), IR(239, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpTypeGraphARM, true, false, IR(378, 3), IR(34595, 13), IR(0, 0), IR(239, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTerminateInvocation, false, false, IR(0, 0), IR(34608, 20), IR(0, 0), IR(3, 1), IR(194, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpTypeUntypedPointerKHR, true, false, IR(381, 2), IR(34628, 22), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpUntypedVariableKHR, true, true, IR(383, 5), IR(34650, 19), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedAccessChainKHR, true, true, IR(151, 5), IR(34669, 22), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedInBoundsAccessChainKHR, true, true, IR(151, 5), IR(34691, 30), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpSubgroupBallotKHR, true, true, IR(160, 3), IR(6244, 18), IR(0, 0), IR(240, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupFirstInvocationKHR, true, true, IR(160, 3), IR(34721, 27), IR(0, 0), IR(240, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpUntypedPtrAccessChainKHR, true, true, IR(388, 6), IR(34748, 25), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedInBoundsPtrAccessChainKHR, true, true, IR(388, 6), IR(34773, 33), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedArrayLengthKHR, true, true, IR(394, 5), IR(34806, 22), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedPrefetchKHR, false, false, IR(399, 5), IR(34828, 19), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpFmaKHR, true, true, IR(130, 5), IR(34847, 7), IR(0, 0), IR(241, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSubgroupAllKHR, true, true, IR(160, 3), IR(34854, 15), IR(0, 0), IR(242, 1), IR(41, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupAnyKHR, true, true, IR(160, 3), IR(34869, 15), IR(0, 0), IR(242, 1), IR(41, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupAllEqualKHR, true, true, IR(160, 3), IR(34884, 20), IR(0, 0), IR(242, 1), IR(41, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupNonUniformRotateKHR, true, true, IR(404, 6), IR(14659, 25), IR(0, 0), IR(243, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupReadInvocationKHR, true, true, IR(172, 4), IR(34904, 26), IR(0, 0), IR(240, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpExtInstWithForwardRefsKHR, true, true, IR(410, 5), IR(34930, 26), IR(0, 0), IR(1, 0), IR(195, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpUntypedGroupAsyncCopyKHR, true, true, IR(415, 11), IR(34956, 25), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpTraceRayKHR, false, false, IR(426, 11), IR(34981, 12), IR(0, 0), IR(61, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpExecuteCallableKHR, false, false, IR(36, 2), IR(34993, 19), IR(0, 0), IR(61, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToAccelerationStructureKHR, true, true, IR(160, 3), IR(35012, 35), IR(0, 0), IR(244, 2), IR(196, 2), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIgnoreIntersectionKHR, false, false, IR(0, 0), IR(35047, 22), IR(0, 0), IR(61, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTerminateRayKHR, false, false, IR(0, 0), IR(35069, 16), IR(0, 0), IR(61, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSDot, true, true, IR(437, 5), IR(35132, 5), IR(171, 1), IR(246, 1), IR(144, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDot, true, true, IR(437, 5), IR(35145, 5), IR(172, 1), IR(246, 1), IR(144, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSUDot, true, true, IR(437, 5), IR(35158, 6), IR(173, 1), IR(246, 1), IR(144, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSDotAccSat, true, true, IR(442, 6), IR(35173, 11), IR(174, 1), IR(246, 1), IR(144, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDotAccSat, true, true, IR(442, 6), IR(35198, 11), IR(175, 1), IR(246, 1), IR(144, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSUDotAccSat, true, true, IR(442, 6), IR(35223, 12), IR(176, 1), IR(246, 1), IR(144, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpTypeCooperativeMatrixKHR, true, false, IR(448, 6), IR(35250, 25), IR(0, 0), IR(87, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeMatrixLoadKHR, true, true, IR(454, 6), IR(35275, 25), IR(0, 0), IR(87, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixStoreKHR, false, false, IR(460, 5), IR(35300, 26), IR(0, 0), IR(87, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixMulAddKHR, true, true, IR(465, 6), IR(35380, 27), IR(0, 0), IR(87, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpCooperativeMatrixLengthKHR, true, true, IR(160, 3), IR(35407, 27), IR(0, 0), IR(87, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpConstantCompositeReplicateEXT, true, true, IR(160, 3), IR(35434, 30), IR(0, 0), IR(247, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCompositeReplicateEXT, true, true, IR(160, 3), IR(35464, 34), IR(0, 0), IR(247, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpCompositeConstructReplicateEXT, true, true, IR(160, 3), IR(35498, 31), IR(0, 0), IR(247, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpTypeRayQueryKHR, true, false, IR(68, 1), IR(35529, 16), IR(0, 0), IR(198, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpRayQueryInitializeKHR, false, false, IR(471, 8), IR(35545, 22), IR(0, 0), IR(198, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryTerminateKHR, false, false, IR(10, 1), IR(35567, 21), IR(0, 0), IR(198, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGenerateIntersectionKHR, false, false, IR(36, 2), IR(35588, 32), IR(0, 0), IR(198, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryConfirmIntersectionKHR, false, false, IR(10, 1), IR(35620, 31), IR(0, 0), IR(198, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryProceedKHR, true, true, IR(160, 3), IR(35651, 19), IR(0, 0), IR(198, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTypeKHR, true, true, IR(172, 4), IR(35670, 31), IR(0, 0), IR(198, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpImageSampleWeightedQCOM, true, true, IR(130, 5), IR(35701, 24), IR(0, 0), IR(248, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBoxFilterQCOM, true, true, IR(130, 5), IR(35725, 19), IR(0, 0), IR(249, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchSSDQCOM, true, true, IR(325, 7), IR(35744, 23), IR(0, 0), IR(250, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchSADQCOM, true, true, IR(325, 7), IR(35767, 23), IR(0, 0), IR(250, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpBitCastArrayQCOM, true, true, IR(160, 3), IR(35790, 17), IR(0, 0), IR(251, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpImageBlockMatchWindowSSDQCOM, true, true, IR(325, 7), IR(35807, 29), IR(0, 0), IR(252, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchWindowSADQCOM, true, true, IR(325, 7), IR(35836, 29), IR(0, 0), IR(252, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchGatherSSDQCOM, true, true, IR(325, 7), IR(35865, 29), IR(0, 0), IR(252, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchGatherSADQCOM, true, true, IR(325, 7), IR(35894, 29), IR(0, 0), IR(252, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpCompositeConstructCoopMatQCOM, true, true, IR(160, 3), IR(35923, 30), IR(0, 0), IR(251, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeExtractCoopMatQCOM, true, true, IR(160, 3), IR(35953, 28), IR(0, 0), IR(251, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpExtractSubArrayQCOM, true, true, IR(172, 4), IR(35981, 20), IR(0, 0), IR(251, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpGroupIAddNonUniformAMD, true, true, IR(283, 5), IR(36001, 23), IR(0, 0), IR(224, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFAddNonUniformAMD, true, true, IR(283, 5), IR(36024, 23), IR(0, 0), IR(224, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMinNonUniformAMD, true, true, IR(283, 5), IR(36047, 23), IR(0, 0), IR(224, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMinNonUniformAMD, true, true, IR(283, 5), IR(36070, 23), IR(0, 0), IR(224, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMinNonUniformAMD, true, true, IR(283, 5), IR(36093, 23), IR(0, 0), IR(224, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMaxNonUniformAMD, true, true, IR(283, 5), IR(36116, 23), IR(0, 0), IR(224, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMaxNonUniformAMD, true, true, IR(283, 5), IR(36139, 23), IR(0, 0), IR(224, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMaxNonUniformAMD, true, true, IR(283, 5), IR(36162, 23), IR(0, 0), IR(224, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpFragmentMaskFetchAMD, true, true, IR(172, 4), IR(36185, 21), IR(0, 0), IR(253, 1), IR(58, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFragmentFetchAMD, true, true, IR(130, 5), IR(36206, 17), IR(0, 0), IR(253, 1), IR(58, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReadClockKHR, true, true, IR(340, 3), IR(36223, 13), IR(0, 0), IR(254, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAllocateNodePayloadsAMDX, true, true, IR(278, 5), IR(36236, 25), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpEnqueueNodePayloadsAMDX, false, false, IR(10, 1), IR(36261, 24), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeNodePayloadArrayAMDX, true, false, IR(87, 2), IR(36285, 25), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFinishWritingNodePayloadAMDX, true, true, IR(160, 3), IR(36310, 29), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpNodePayloadArrayLengthAMDX, true, true, IR(160, 3), IR(36339, 27), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIsNodePayloadValidAMDX, true, true, IR(172, 4), IR(36366, 23), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConstantStringAMDX, true, false, IR(50, 2), IR(36389, 19), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSpecConstantStringAMDX, true, false, IR(50, 2), IR(36408, 23), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpGroupNonUniformQuadAllKHR, true, true, IR(160, 3), IR(36431, 26), IR(0, 0), IR(169, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadAnyKHR, true, true, IR(160, 3), IR(36457, 26), IR(0, 0), IR(169, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpTypeBufferEXT, true, false, IR(381, 2), IR(36483, 14), IR(0, 0), IR(44, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpBufferPointerEXT, true, true, IR(160, 3), IR(36497, 17), IR(0, 0), IR(44, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedImageTexelPointerEXT, true, true, IR(215, 6), IR(36514, 28), IR(0, 0), IR(44, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpMemberDecorateIdEXT, false, false, IR(165, 3), IR(36542, 20), IR(0, 0), IR(44, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpConstantSizeOfEXT, true, true, IR(160, 3), IR(36562, 18), IR(0, 0), IR(44, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpHitObjectRecordHitMotionNV, false, false, IR(479, 14), IR(36580, 27), IR(0, 0), IR(255, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitWithIndexMotionNV, false, false, IR(493, 13), IR(36607, 36), IR(0, 0), IR(255, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissMotionNV, false, false, IR(506, 7), IR(36643, 28), IR(0, 0), IR(255, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldToObjectNV, true, true, IR(160, 3), IR(36671, 28), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectToWorldNV, true, true, IR(160, 3), IR(36699, 28), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayDirectionNV, true, true, IR(160, 3), IR(36727, 33), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayOriginNV, true, true, IR(160, 3), IR(36760, 30), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayMotionNV, false, false, IR(493, 13), IR(36790, 26), IR(0, 0), IR(255, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderRecordBufferHandleNV, true, true, IR(160, 3), IR(36816, 39), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderBindingTableRecordIndexNV, true, true, IR(160, 3), IR(36855, 44), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordEmptyNV, false, false, IR(10, 1), IR(36899, 23), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayNV, false, false, IR(513, 12), IR(36922, 20), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitNV, false, false, IR(493, 13), IR(36942, 21), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitWithIndexNV, false, false, IR(513, 12), IR(36963, 30), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissNV, false, false, IR(525, 6), IR(36993, 22), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectExecuteShaderNV, false, false, IR(36, 2), IR(37015, 25), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetCurrentTimeNV, true, true, IR(160, 3), IR(37040, 26), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetAttributesNV, false, false, IR(36, 2), IR(37066, 25), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetHitKindNV, true, true, IR(160, 3), IR(37091, 22), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetPrimitiveIndexNV, true, true, IR(160, 3), IR(37113, 29), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetGeometryIndexNV, true, true, IR(160, 3), IR(37142, 28), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceIdNV, true, true, IR(160, 3), IR(37170, 25), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceCustomIndexNV, true, true, IR(160, 3), IR(37195, 34), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayDirectionNV, true, true, IR(160, 3), IR(37229, 32), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayOriginNV, true, true, IR(160, 3), IR(37261, 29), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMaxNV, true, true, IR(160, 3), IR(37290, 22), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMinNV, true, true, IR(160, 3), IR(37312, 22), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsEmptyNV, true, true, IR(160, 3), IR(37334, 19), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsHitNV, true, true, IR(160, 3), IR(37353, 17), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsMissNV, true, true, IR(160, 3), IR(37370, 18), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHitObjectNV, false, false, IR(531, 3), IR(37388, 29), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHintNV, false, false, IR(36, 2), IR(37417, 24), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeHitObjectNV, true, false, IR(68, 1), IR(37441, 16), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpImageSampleFootprintNV, true, true, IR(534, 7), IR(37457, 23), IR(0, 0), IR(257, 1), IR(73, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpTypeVectorIdEXT, true, false, IR(89, 3), IR(37480, 16), IR(177, 1), IR(258, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeVectorMatrixMulNV, true, true, IR(541, 13), IR(37520, 29), IR(0, 0), IR(260, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorOuterProductAccumulateNV, false, false, IR(554, 7), IR(37549, 42), IR(0, 0), IR(261, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorReduceSumAccumulateNV, false, false, IR(33, 3), IR(37591, 39), IR(0, 0), IR(261, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorMatrixMulAddNV, true, true, IR(561, 16), IR(37630, 32), IR(0, 0), IR(260, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixConvertNV, true, true, IR(160, 3), IR(37662, 27), IR(0, 0), IR(262, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpEmitMeshTasksEXT, false, false, IR(577, 4), IR(37689, 17), IR(0, 0), IR(54, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSetMeshOutputsEXT, false, false, IR(36, 2), IR(37706, 18), IR(0, 0), IR(54, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpGroupNonUniformPartitionEXT, true, true, IR(160, 3), IR(37724, 28), IR(178, 1), IR(189, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpWritePackedPrimitiveIndices4x8NV, false, false, IR(36, 2), IR(37779, 33), IR(0, 0), IR(51, 1), IR(18, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFetchMicroTriangleVertexPositionNV, true, true, IR(325, 7), IR(37812, 35), IR(0, 0), IR(263, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFetchMicroTriangleVertexBarycentricNV, true, true, IR(325, 7), IR(37847, 38), IR(0, 0), IR(263, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorLoadNV, true, true, IR(581, 5), IR(37885, 24), IR(0, 0), IR(260, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeVectorStoreNV, false, false, IR(586, 4), IR(37909, 25), IR(0, 0), IR(260, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpHitObjectRecordFromQueryEXT, false, false, IR(296, 4), IR(37934, 28), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissEXT, false, false, IR(506, 7), IR(37962, 23), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissMotionEXT, false, false, IR(471, 8), IR(37985, 29), IR(0, 0), IR(264, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetIntersectionTriangleVertexPositionsEXT, true, true, IR(160, 3), IR(38014, 51), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayFlagsEXT, true, true, IR(160, 3), IR(38065, 24), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectSetShaderBindingTableRecordIndexEXT, false, false, IR(36, 2), IR(38089, 45), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectReorderExecuteShaderEXT, false, false, IR(590, 4), IR(38134, 33), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceReorderExecuteEXT, false, false, IR(594, 14), IR(38167, 32), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceMotionReorderExecuteEXT, false, false, IR(608, 15), IR(38199, 38), IR(0, 0), IR(264, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeHitObjectEXT, true, false, IR(68, 1), IR(38237, 17), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpReorderThreadWithHintEXT, false, false, IR(36, 2), IR(38254, 25), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHitObjectEXT, false, false, IR(531, 3), IR(38279, 30), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayEXT, false, false, IR(513, 12), IR(38309, 21), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayMotionEXT, false, false, IR(493, 13), IR(38330, 27), IR(0, 0), IR(264, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordEmptyEXT, false, false, IR(10, 1), IR(38357, 24), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectExecuteShaderEXT, false, false, IR(36, 2), IR(38381, 26), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetCurrentTimeEXT, true, true, IR(160, 3), IR(38407, 27), IR(0, 0), IR(264, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetAttributesEXT, false, false, IR(36, 2), IR(38434, 26), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetHitKindEXT, true, true, IR(160, 3), IR(38460, 23), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetPrimitiveIndexEXT, true, true, IR(160, 3), IR(38483, 30), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetGeometryIndexEXT, true, true, IR(160, 3), IR(38513, 29), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceIdEXT, true, true, IR(160, 3), IR(38542, 26), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceCustomIndexEXT, true, true, IR(160, 3), IR(38568, 35), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayOriginEXT, true, true, IR(160, 3), IR(38603, 31), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayDirectionEXT, true, true, IR(160, 3), IR(38634, 34), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayDirectionEXT, true, true, IR(160, 3), IR(38668, 33), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayOriginEXT, true, true, IR(160, 3), IR(38701, 30), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectToWorldEXT, true, true, IR(160, 3), IR(38731, 29), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldToObjectEXT, true, true, IR(160, 3), IR(38760, 29), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMaxEXT, true, true, IR(160, 3), IR(38789, 23), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReportIntersectionKHR, true, true, IR(172, 4), IR(38812, 22), IR(179, 1), IR(55, 2), IR(24, 2), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIgnoreIntersectionNV, false, false, IR(0, 0), IR(38855, 21), IR(0, 0), IR(57, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTerminateRayNV, false, false, IR(0, 0), IR(38876, 15), IR(0, 0), IR(57, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceNV, false, false, IR(426, 11), IR(38891, 8), IR(0, 0), IR(57, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceMotionNV, false, false, IR(513, 12), IR(38899, 14), IR(0, 0), IR(58, 1), IR(27, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceRayMotionNV, false, false, IR(513, 12), IR(38913, 17), IR(0, 0), IR(58, 1), IR(27, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTriangleVertexPositionsKHR, true, true, IR(172, 4), IR(38930, 50), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeAccelerationStructureKHR, true, false, IR(68, 1), IR(38980, 29), IR(180, 1), IR(267, 4), IR(198, 4), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpExecuteCallableNV, false, false, IR(36, 2), IR(39037, 18), IR(0, 0), IR(57, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionClusterIdNV, true, true, IR(172, 4), IR(39055, 35), IR(181, 1), IR(65, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetClusterIdNV, true, true, IR(160, 3), IR(39113, 24), IR(0, 0), IR(65, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMinEXT, true, true, IR(160, 3), IR(39137, 23), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderBindingTableRecordIndexEXT, true, true, IR(160, 3), IR(39160, 45), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderRecordBufferHandleEXT, true, true, IR(160, 3), IR(39205, 40), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsEmptyEXT, true, true, IR(160, 3), IR(39245, 20), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsHitEXT, true, true, IR(160, 3), IR(39265, 18), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsMissEXT, true, true, IR(160, 3), IR(39283, 19), IR(0, 0), IR(131, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeCooperativeMatrixNV, true, false, IR(623, 5), IR(39302, 24), IR(0, 0), IR(271, 1), IR(81, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeMatrixLoadNV, true, true, IR(628, 6), IR(39326, 24), IR(0, 0), IR(271, 1), IR(81, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixStoreNV, false, false, IR(634, 5), IR(39350, 25), IR(0, 0), IR(271, 1), IR(81, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixMulAddNV, true, true, IR(130, 5), IR(39375, 26), IR(0, 0), IR(271, 1), IR(81, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixLengthNV, true, true, IR(160, 3), IR(39401, 26), IR(0, 0), IR(271, 1), IR(81, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpBeginInvocationInterlockEXT, false, false, IR(0, 0), IR(39427, 28), IR(0, 0), IR(272, 3), IR(82, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpEndInvocationInterlockEXT, false, false, IR(0, 0), IR(39455, 26), IR(0, 0), IR(272, 3), IR(82, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixReduceNV, true, true, IR(639, 5), IR(39524, 26), IR(0, 0), IR(275, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpCooperativeMatrixLoadTensorNV, true, true, IR(644, 7), IR(39625, 30), IR(0, 0), IR(206, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixStoreTensorNV, false, false, IR(651, 5), IR(39655, 31), IR(0, 0), IR(206, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixPerElementOpNV, true, true, IR(151, 5), IR(39686, 32), IR(0, 0), IR(276, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpTypeTensorLayoutNV, true, false, IR(89, 3), IR(39718, 19), IR(0, 0), IR(277, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeTensorViewNV, true, false, IR(656, 4), IR(39737, 17), IR(0, 0), IR(277, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCreateTensorLayoutNV, true, true, IR(39, 2), IR(39754, 21), IR(0, 0), IR(277, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetDimensionNV, true, true, IR(122, 4), IR(39775, 27), IR(0, 0), IR(277, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetStrideNV, true, true, IR(122, 4), IR(39802, 24), IR(0, 0), IR(277, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSliceNV, true, true, IR(122, 4), IR(39826, 20), IR(0, 0), IR(277, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetClampValueNV, true, true, IR(172, 4), IR(39846, 28), IR(0, 0), IR(277, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCreateTensorViewNV, true, true, IR(39, 2), IR(39874, 19), IR(0, 0), IR(277, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetDimensionNV, true, true, IR(122, 4), IR(39893, 25), IR(0, 0), IR(277, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetStrideNV, true, true, IR(122, 4), IR(39918, 22), IR(0, 0), IR(277, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpDemoteToHelperInvocation, false, false, IR(0, 0), IR(12474, 25), IR(46, 1), IR(278, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpIsHelperInvocationEXT, true, true, IR(39, 2), IR(39940, 22), IR(0, 0), IR(278, 1), IR(83, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetClipNV, true, true, IR(325, 7), IR(39962, 20), IR(0, 0), IR(277, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetBlockSizeNV, true, true, IR(122, 4), IR(39982, 27), IR(0, 0), IR(277, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixTransposeNV, true, true, IR(160, 3), IR(40009, 29), IR(0, 0), IR(262, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToImageNV, true, true, IR(160, 3), IR(40038, 18), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToSamplerNV, true, true, IR(160, 3), IR(40056, 20), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertImageToUNV, true, true, IR(160, 3), IR(40076, 18), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertSamplerToUNV, true, true, IR(160, 3), IR(40094, 20), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToSampledImageNV, true, true, IR(160, 3), IR(40114, 25), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertSampledImageToUNV, true, true, IR(160, 3), IR(40139, 25), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSamplerImageAddressingModeNV, false, false, IR(0, 1), IR(40164, 29), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRawAccessChainNV, true, true, IR(660, 7), IR(40245, 17), IR(0, 0), IR(195, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpRayQueryGetIntersectionSpherePositionNV, true, true, IR(172, 4), IR(40262, 40), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionSphereRadiusNV, true, true, IR(172, 4), IR(40302, 38), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSPositionsNV, true, true, IR(172, 4), IR(40340, 38), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSRadiiNV, true, true, IR(172, 4), IR(40378, 34), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSHitValueNV, true, true, IR(172, 4), IR(40412, 37), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetSpherePositionNV, true, true, IR(160, 3), IR(40449, 29), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetSphereRadiusNV, true, true, IR(160, 3), IR(40478, 27), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetLSSPositionsNV, true, true, IR(160, 3), IR(40505, 27), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetLSSRadiiNV, true, true, IR(160, 3), IR(40532, 23), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsSphereHitNV, true, true, IR(160, 3), IR(40555, 23), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsLSSHitNV, true, true, IR(160, 3), IR(40578, 20), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryIsSphereHitNV, true, true, IR(172, 4), IR(40598, 22), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryIsLSSHitNV, true, true, IR(172, 4), IR(40620, 19), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSubgroupShuffleINTEL, true, true, IR(172, 4), IR(13006, 21), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleDownINTEL, true, true, IR(130, 5), IR(40639, 25), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleUpINTEL, true, true, IR(130, 5), IR(40664, 23), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleXorINTEL, true, true, IR(172, 4), IR(40687, 24), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupBlockReadINTEL, true, true, IR(160, 3), IR(40711, 23), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupBlockWriteINTEL, false, false, IR(36, 2), IR(40734, 24), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageBlockReadINTEL, true, true, IR(172, 4), IR(40758, 28), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageBlockWriteINTEL, false, false, IR(33, 3), IR(40786, 29), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageMediaBlockReadINTEL, true, true, IR(215, 6), IR(40815, 33), IR(0, 0), IR(282, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageMediaBlockWriteINTEL, false, false, IR(667, 5), IR(40848, 34), IR(0, 0), IR(282, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpUCountLeadingZerosINTEL, true, true, IR(160, 3), IR(40882, 24), IR(0, 0), IR(283, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUCountTrailingZerosINTEL, true, true, IR(160, 3), IR(40906, 25), IR(0, 0), IR(283, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAbsISubINTEL, true, true, IR(172, 4), IR(40931, 13), IR(0, 0), IR(283, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAbsUSubINTEL, true, true, IR(172, 4), IR(40944, 13), IR(0, 0), IR(283, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAddSatINTEL, true, true, IR(172, 4), IR(40957, 13), IR(0, 0), IR(283, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAddSatINTEL, true, true, IR(172, 4), IR(40970, 13), IR(0, 0), IR(283, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAverageINTEL, true, true, IR(172, 4), IR(40983, 14), IR(0, 0), IR(283, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAverageINTEL, true, true, IR(172, 4), IR(40997, 14), IR(0, 0), IR(283, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAverageRoundedINTEL, true, true, IR(172, 4), IR(41011, 21), IR(0, 0), IR(283, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAverageRoundedINTEL, true, true, IR(172, 4), IR(41032, 21), IR(0, 0), IR(283, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpISubSatINTEL, true, true, IR(172, 4), IR(41053, 13), IR(0, 0), IR(283, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUSubSatINTEL, true, true, IR(172, 4), IR(41066, 13), IR(0, 0), IR(283, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIMul32x16INTEL, true, true, IR(172, 4), IR(41079, 15), IR(0, 0), IR(283, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUMul32x16INTEL, true, true, IR(172, 4), IR(41094, 15), IR(0, 0), IR(283, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConstantFunctionPointerINTEL, true, true, IR(160, 3), IR(41109, 29), IR(0, 0), IR(204, 1), IR(101, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFunctionPointerCallINTEL, true, true, IR(107, 3), IR(41138, 25), IR(0, 0), IR(204, 1), IR(101, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmTargetINTEL, true, false, IR(50, 2), IR(41163, 15), IR(0, 0), IR(135, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmINTEL, true, true, IR(672, 6), IR(13224, 9), IR(0, 0), IR(135, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmCallINTEL, true, true, IR(122, 4), IR(41178, 13), IR(0, 0), IR(135, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAtomicFMinEXT, true, true, IR(235, 6), IR(41191, 14), IR(0, 0), IR(284, 4), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicFMaxEXT, true, true, IR(235, 6), IR(41205, 14), IR(0, 0), IR(284, 4), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAssumeTrueKHR, false, false, IR(10, 1), IR(41219, 14), IR(0, 0), IR(288, 1), IR(105, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpExpectKHR, true, true, IR(172, 4), IR(41233, 10), IR(0, 0), IR(288, 1), IR(105, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpDecorateString, false, false, IR(163, 2), IR(41243, 15), IR(182, 1), IR(1, 0), IR(202, 2), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpMemberDecorateString, false, false, IR(165, 3), IR(41279, 21), IR(183, 1), IR(1, 0), IR(202, 2), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpVmeImageINTEL, true, true, IR(172, 4), IR(41327, 14), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeVmeImageINTEL, true, false, IR(87, 2), IR(41341, 18), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImePayloadINTEL, true, false, IR(68, 1), IR(41359, 23), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcRefPayloadINTEL, true, false, IR(68, 1), IR(41382, 23), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcSicPayloadINTEL, true, false, IR(68, 1), IR(41405, 23), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcMcePayloadINTEL, true, false, IR(68, 1), IR(41428, 23), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcMceResultINTEL, true, false, IR(68, 1), IR(41451, 22), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultINTEL, true, false, IR(68, 1), IR(41473, 22), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultSingleReferenceStreamoutINTEL, true, false, IR(68, 1), IR(41495, 46), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultDualReferenceStreamoutINTEL, true, false, IR(68, 1), IR(41541, 44), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeSingleReferenceStreaminINTEL, true, false, IR(68, 1), IR(41585, 39), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeDualReferenceStreaminINTEL, true, false, IR(68, 1), IR(41624, 37), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcRefResultINTEL, true, false, IR(68, 1), IR(41661, 22), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcSicResultINTEL, true, false, IR(68, 1), IR(41683, 22), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL, true, true, IR(172, 4), IR(41705, 60), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL, true, true, IR(172, 4), IR(41765, 53), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterShapePenaltyINTEL, true, true, IR(172, 4), IR(41818, 47), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterShapePenaltyINTEL, true, true, IR(172, 4), IR(41865, 40), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL, true, true, IR(172, 4), IR(41905, 51), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterDirectionPenaltyINTEL, true, true, IR(172, 4), IR(41956, 44), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL, true, true, IR(172, 4), IR(42000, 51), IR(0, 0), IR(290, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL, true, true, IR(172, 4), IR(42051, 56), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL, true, true, IR(39, 2), IR(42107, 50), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL, true, true, IR(39, 2), IR(42157, 52), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL, true, true, IR(39, 2), IR(42209, 49), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetMotionVectorCostFunctionINTEL, true, true, IR(215, 6), IR(42258, 47), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL, true, true, IR(172, 4), IR(42305, 50), IR(0, 0), IR(290, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL, true, true, IR(39, 2), IR(42355, 51), IR(0, 0), IR(290, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL, true, true, IR(39, 2), IR(42406, 56), IR(0, 0), IR(292, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetAcOnlyHaarINTEL, true, true, IR(160, 3), IR(42462, 33), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL, true, true, IR(172, 4), IR(42495, 52), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL, true, true, IR(172, 4), IR(42547, 61), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL, true, true, IR(130, 5), IR(42608, 61), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToImePayloadINTEL, true, true, IR(160, 3), IR(42669, 39), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToImeResultINTEL, true, true, IR(160, 3), IR(42708, 38), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToRefPayloadINTEL, true, true, IR(160, 3), IR(42746, 39), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToRefResultINTEL, true, true, IR(160, 3), IR(42785, 38), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToSicPayloadINTEL, true, true, IR(160, 3), IR(42823, 39), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToSicResultINTEL, true, true, IR(160, 3), IR(42862, 38), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetMotionVectorsINTEL, true, true, IR(160, 3), IR(42900, 36), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterDistortionsINTEL, true, true, IR(160, 3), IR(42936, 39), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetBestInterDistortionsINTEL, true, true, IR(160, 3), IR(42975, 43), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMajorShapeINTEL, true, true, IR(160, 3), IR(43018, 38), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMinorShapeINTEL, true, true, IR(160, 3), IR(43056, 38), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterDirectionsINTEL, true, true, IR(160, 3), IR(43094, 38), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMotionVectorCountINTEL, true, true, IR(160, 3), IR(43132, 45), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterReferenceIdsINTEL, true, true, IR(160, 3), IR(43177, 40), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL, true, true, IR(130, 5), IR(43217, 62), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeInitializeINTEL, true, true, IR(130, 5), IR(43279, 30), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetSingleReferenceINTEL, true, true, IR(130, 5), IR(43309, 38), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetDualReferenceINTEL, true, true, IR(215, 6), IR(43347, 36), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeRefWindowSizeINTEL, true, true, IR(172, 4), IR(43383, 33), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeAdjustRefOffsetINTEL, true, true, IR(215, 6), IR(43416, 35), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(43451, 39), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetMaxMotionVectorCountINTEL, true, true, IR(172, 4), IR(43490, 43), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetUnidirectionalMixDisableINTEL, true, true, IR(160, 3), IR(43533, 47), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetEarlySearchTerminationThresholdINTEL, true, true, IR(172, 4), IR(43580, 54), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetWeightedSadINTEL, true, true, IR(172, 4), IR(43634, 34), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(43668, 47), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(43715, 45), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL, true, true, IR(215, 6), IR(43760, 55), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL, true, true, IR(325, 7), IR(43815, 53), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL, true, true, IR(130, 5), IR(43868, 56), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL, true, true, IR(215, 6), IR(43924, 54), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL, true, true, IR(215, 6), IR(43978, 58), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL, true, true, IR(325, 7), IR(44036, 56), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeConvertToMceResultINTEL, true, true, IR(160, 3), IR(44092, 38), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetSingleReferenceStreaminINTEL, true, true, IR(160, 3), IR(44130, 46), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetDualReferenceStreaminINTEL, true, true, IR(160, 3), IR(44176, 44), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeStripSingleReferenceStreamoutINTEL, true, true, IR(160, 3), IR(44220, 49), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeStripDualReferenceStreamoutINTEL, true, true, IR(160, 3), IR(44269, 47), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL, true, true, IR(172, 4), IR(44316, 70), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL, true, true, IR(172, 4), IR(44386, 68), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL, true, true, IR(172, 4), IR(44454, 69), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL, true, true, IR(130, 5), IR(44523, 68), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL, true, true, IR(130, 5), IR(44591, 66), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL, true, true, IR(130, 5), IR(44657, 67), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetBorderReachedINTEL, true, true, IR(172, 4), IR(44724, 36), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetTruncatedSearchIndicationINTEL, true, true, IR(160, 3), IR(44760, 48), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL, true, true, IR(160, 3), IR(44808, 59), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL, true, true, IR(160, 3), IR(44867, 58), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL, true, true, IR(160, 3), IR(44925, 56), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcFmeInitializeINTEL, true, true, IR(678, 9), IR(44981, 30), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcBmeInitializeINTEL, true, true, IR(687, 10), IR(45011, 30), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(45041, 39), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefSetBidirectionalMixDisableINTEL, true, true, IR(160, 3), IR(45080, 46), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefSetBilinearFilterEnableINTEL, true, true, IR(160, 3), IR(45126, 43), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(45169, 47), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(45216, 45), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithMultiReferenceINTEL, true, true, IR(130, 5), IR(45261, 46), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL, true, true, IR(215, 6), IR(45307, 56), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefConvertToMceResultINTEL, true, true, IR(160, 3), IR(45363, 38), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicInitializeINTEL, true, true, IR(160, 3), IR(45401, 30), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureSkcINTEL, true, true, IR(288, 8), IR(45431, 32), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureIpeLumaINTEL, true, true, IR(687, 10), IR(45463, 36), IR(0, 0), IR(290, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureIpeLumaChromaINTEL, true, true, IR(697, 13), IR(45499, 42), IR(0, 0), IR(292, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetMotionVectorMaskINTEL, true, true, IR(172, 4), IR(45541, 39), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(45580, 39), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraLumaShapePenaltyINTEL, true, true, IR(172, 4), IR(45619, 44), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraLumaModeCostFunctionINTEL, true, true, IR(215, 6), IR(45663, 48), IR(0, 0), IR(290, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraChromaModeCostFunctionINTEL, true, true, IR(172, 4), IR(45711, 50), IR(0, 0), IR(292, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetBilinearFilterEnableINTEL, true, true, IR(160, 3), IR(45761, 43), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetSkcForwardTransformEnableINTEL, true, true, IR(172, 4), IR(45804, 48), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetBlockBasedRawSkipSadINTEL, true, true, IR(172, 4), IR(45852, 43), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateIpeINTEL, true, true, IR(172, 4), IR(45895, 31), IR(0, 0), IR(290, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(45926, 47), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(45973, 45), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithMultiReferenceINTEL, true, true, IR(130, 5), IR(46018, 46), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL, true, true, IR(215, 6), IR(46064, 56), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConvertToMceResultINTEL, true, true, IR(160, 3), IR(46120, 38), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetIpeLumaShapeINTEL, true, true, IR(160, 3), IR(46158, 35), IR(0, 0), IR(290, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetBestIpeLumaDistortionINTEL, true, true, IR(160, 3), IR(46193, 44), IR(0, 0), IR(290, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetBestIpeChromaDistortionINTEL, true, true, IR(160, 3), IR(46237, 46), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedIpeLumaModesINTEL, true, true, IR(160, 3), IR(46283, 41), IR(0, 0), IR(290, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetIpeChromaModeINTEL, true, true, IR(160, 3), IR(46324, 36), IR(0, 0), IR(292, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL, true, true, IR(160, 3), IR(46360, 50), IR(0, 0), IR(290, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL, true, true, IR(160, 3), IR(46410, 48), IR(0, 0), IR(290, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetInterRawSadsINTEL, true, true, IR(160, 3), IR(46458, 35), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpVariableLengthArrayINTEL, true, true, IR(160, 3), IR(13462, 25), IR(0, 0), IR(294, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpSaveMemoryINTEL, true, true, IR(39, 2), IR(46493, 16), IR(0, 0), IR(294, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpRestoreMemoryINTEL, false, false, IR(10, 1), IR(46509, 19), IR(0, 0), IR(294, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpArbitraryFloatSinCosPiALTERA, true, true, IR(710, 8), IR(46528, 29), IR(184, 1), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastALTERA, true, true, IR(710, 8), IR(46585, 25), IR(185, 1), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastFromIntALTERA, true, true, IR(710, 8), IR(46634, 32), IR(186, 1), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastToIntALTERA, true, true, IR(710, 8), IR(46697, 30), IR(187, 1), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatAddALTERA, true, true, IR(718, 10), IR(46756, 24), IR(188, 1), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSubALTERA, true, true, IR(718, 10), IR(46803, 24), IR(189, 1), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatMulALTERA, true, true, IR(718, 10), IR(46850, 24), IR(190, 1), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatDivALTERA, true, true, IR(718, 10), IR(46897, 24), IR(191, 1), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatGTALTERA, true, true, IR(728, 6), IR(46944, 23), IR(192, 1), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatGEALTERA, true, true, IR(728, 6), IR(46989, 23), IR(193, 1), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLTALTERA, true, true, IR(728, 6), IR(47034, 23), IR(194, 1), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLEALTERA, true, true, IR(728, 6), IR(47079, 23), IR(195, 1), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatEQALTERA, true, true, IR(728, 6), IR(47124, 23), IR(196, 1), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatRecipALTERA, true, true, IR(710, 8), IR(47169, 26), IR(197, 1), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatRSqrtALTERA, true, true, IR(710, 8), IR(47220, 26), IR(198, 1), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCbrtALTERA, true, true, IR(710, 8), IR(47271, 25), IR(199, 1), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatHypotALTERA, true, true, IR(718, 10), IR(47320, 26), IR(200, 1), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSqrtALTERA, true, true, IR(710, 8), IR(47371, 25), IR(201, 1), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLogINTEL, true, true, IR(710, 8), IR(47420, 23), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog2INTEL, true, true, IR(710, 8), IR(47443, 24), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog10INTEL, true, true, IR(710, 8), IR(47467, 25), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog1pINTEL, true, true, IR(710, 8), IR(47492, 25), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExpINTEL, true, true, IR(710, 8), IR(47517, 23), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExp2INTEL, true, true, IR(710, 8), IR(47540, 24), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExp10INTEL, true, true, IR(710, 8), IR(47564, 25), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExpm1INTEL, true, true, IR(710, 8), IR(47589, 25), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinINTEL, true, true, IR(710, 8), IR(47614, 23), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCosINTEL, true, true, IR(710, 8), IR(47637, 23), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinCosINTEL, true, true, IR(710, 8), IR(47660, 26), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinPiINTEL, true, true, IR(710, 8), IR(47686, 25), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCosPiINTEL, true, true, IR(710, 8), IR(47711, 25), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatASinINTEL, true, true, IR(710, 8), IR(47736, 24), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatASinPiINTEL, true, true, IR(710, 8), IR(47760, 26), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatACosINTEL, true, true, IR(710, 8), IR(47786, 24), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatACosPiINTEL, true, true, IR(710, 8), IR(47810, 26), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATanINTEL, true, true, IR(710, 8), IR(47836, 24), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATanPiINTEL, true, true, IR(710, 8), IR(47860, 26), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATan2INTEL, true, true, IR(718, 10), IR(47886, 25), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowINTEL, true, true, IR(718, 10), IR(47911, 23), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowRINTEL, true, true, IR(718, 10), IR(47934, 24), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowNINTEL, true, true, IR(718, 10), IR(47958, 24), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpLoopControlINTEL, false, false, IR(18, 1), IR(47982, 17), IR(0, 0), IR(296, 1), IR(115, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAliasDomainDeclINTEL, true, false, IR(734, 2), IR(47999, 21), IR(0, 0), IR(141, 1), IR(127, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAliasScopeDeclINTEL, true, false, IR(736, 3), IR(48020, 20), IR(0, 0), IR(141, 1), IR(127, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAliasScopeListDeclINTEL, true, false, IR(92, 2), IR(48040, 24), IR(0, 0), IR(141, 1), IR(127, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSqrtALTERA, true, true, IR(710, 8), IR(48064, 16), IR(202, 1), IR(194, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedRecipALTERA, true, true, IR(710, 8), IR(48095, 17), IR(203, 1), IR(194, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedRsqrtALTERA, true, true, IR(710, 8), IR(48128, 17), IR(204, 1), IR(194, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinALTERA, true, true, IR(710, 8), IR(48161, 15), IR(205, 1), IR(194, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedCosALTERA, true, true, IR(710, 8), IR(48190, 15), IR(206, 1), IR(194, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinCosALTERA, true, true, IR(710, 8), IR(48219, 18), IR(207, 1), IR(194, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinPiALTERA, true, true, IR(710, 8), IR(48254, 17), IR(208, 1), IR(194, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedCosPiALTERA, true, true, IR(710, 8), IR(48287, 17), IR(209, 1), IR(194, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinCosPiALTERA, true, true, IR(710, 8), IR(48320, 20), IR(210, 1), IR(194, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedLogALTERA, true, true, IR(710, 8), IR(48359, 15), IR(211, 1), IR(194, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedExpALTERA, true, true, IR(710, 8), IR(48388, 15), IR(212, 1), IR(194, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpPtrCastToCrossWorkgroupALTERA, true, true, IR(160, 3), IR(48417, 30), IR(213, 1), IR(205, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpCrossWorkgroupCastToPtrALTERA, true, true, IR(160, 3), IR(48476, 30), IR(214, 1), IR(205, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpReadPipeBlockingALTERA, true, true, IR(172, 4), IR(48535, 23), IR(215, 1), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpWritePipeBlockingALTERA, true, true, IR(172, 4), IR(48580, 24), IR(216, 1), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFPGARegALTERA, true, true, IR(160, 3), IR(14420, 14), IR(62, 1), IR(298, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpRayQueryGetRayTMinKHR, true, true, IR(160, 3), IR(48627, 22), IR(0, 0), IR(198, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetRayFlagsKHR, true, true, IR(160, 3), IR(48649, 23), IR(0, 0), IR(198, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTKHR, true, true, IR(172, 4), IR(48672, 28), IR(0, 0), IR(198, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceCustomIndexKHR, true, true, IR(172, 4), IR(48700, 46), IR(0, 0), IR(198, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceIdKHR, true, true, IR(172, 4), IR(48746, 37), IR(0, 0), IR(198, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR, true, true, IR(172, 4), IR(48783, 65), IR(0, 0), IR(198, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionGeometryIndexKHR, true, true, IR(172, 4), IR(48848, 40), IR(0, 0), IR(198, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionPrimitiveIndexKHR, true, true, IR(172, 4), IR(48888, 41), IR(0, 0), IR(198, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionBarycentricsKHR, true, true, IR(172, 4), IR(48929, 39), IR(0, 0), IR(198, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionFrontFaceKHR, true, true, IR(172, 4), IR(48968, 36), IR(0, 0), IR(198, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionCandidateAABBOpaqueKHR, true, true, IR(160, 3), IR(49004, 46), IR(0, 0), IR(198, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectRayDirectionKHR, true, true, IR(172, 4), IR(49050, 45), IR(0, 0), IR(198, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectRayOriginKHR, true, true, IR(172, 4), IR(49095, 42), IR(0, 0), IR(198, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetWorldRayDirectionKHR, true, true, IR(160, 3), IR(49137, 32), IR(0, 0), IR(198, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetWorldRayOriginKHR, true, true, IR(160, 3), IR(49169, 29), IR(0, 0), IR(198, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectToWorldKHR, true, true, IR(172, 4), IR(49198, 40), IR(0, 0), IR(198, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionWorldToObjectKHR, true, true, IR(172, 4), IR(49238, 40), IR(0, 0), IR(198, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAtomicFAddEXT, true, true, IR(235, 6), IR(49278, 14), IR(0, 0), IR(299, 4), IR(151, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpTypeBufferSurfaceINTEL, true, false, IR(100, 2), IR(49292, 23), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeStructContinuedINTEL, false, false, IR(739, 1), IR(49315, 25), IR(0, 0), IR(303, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantCompositeContinuedINTEL, false, false, IR(739, 1), IR(49340, 32), IR(0, 0), IR(303, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCompositeContinuedINTEL, false, false, IR(739, 1), IR(49372, 36), IR(0, 0), IR(303, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpCompositeConstructContinuedINTEL, true, true, IR(107, 3), IR(49408, 33), IR(0, 0), IR(303, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpConvertFToBF16INTEL, true, true, IR(160, 3), IR(49441, 20), IR(0, 0), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertBF16ToFINTEL, true, true, IR(160, 3), IR(49461, 20), IR(0, 0), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpControlBarrierArriveINTEL, false, false, IR(221, 3), IR(49481, 26), IR(0, 0), IR(305, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpControlBarrierWaitINTEL, false, false, IR(221, 3), IR(49507, 24), IR(0, 0), IR(305, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpArithmeticFenceEXT, true, true, IR(160, 3), IR(14873, 19), IR(0, 0), IR(306, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpTaskSequenceCreateALTERA, true, true, IR(740, 7), IR(49531, 25), IR(217, 1), IR(307, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTaskSequenceAsyncALTERA, false, false, IR(168, 2), IR(49580, 24), IR(218, 1), IR(307, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTaskSequenceGetALTERA, true, true, IR(160, 3), IR(49627, 22), IR(219, 1), IR(307, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTaskSequenceReleaseALTERA, false, false, IR(10, 1), IR(49670, 26), IR(220, 1), IR(307, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeTaskSequenceALTERA, true, false, IR(68, 1), IR(49721, 23), IR(221, 1), IR(307, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupBlockPrefetchINTEL, false, false, IR(139, 3), IR(49766, 27), IR(0, 0), IR(308, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadINTEL, false, false, IR(747, 10), IR(49793, 25), IR(0, 0), IR(110, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadTransformINTEL, false, false, IR(747, 10), IR(49818, 34), IR(0, 0), IR(309, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadTransposeINTEL, false, false, IR(747, 10), IR(49852, 34), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockPrefetchINTEL, false, false, IR(757, 9), IR(49886, 29), IR(0, 0), IR(110, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockStoreINTEL, false, false, IR(747, 10), IR(49915, 26), IR(0, 0), IR(110, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupMatrixMultiplyAccumulateINTEL, true, true, IR(766, 7), IR(15350, 38), IR(0, 0), IR(311, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpBitwiseFunctionINTEL, true, true, IR(215, 6), IR(50003, 21), IR(0, 0), IR(312, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpUntypedVariableLengthArrayINTEL, true, true, IR(172, 4), IR(15416, 32), IR(0, 0), IR(313, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpConditionalExtensionINTEL, false, false, IR(45, 2), IR(50024, 26), IR(0, 0), IR(113, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpConditionalEntryPointINTEL, false, false, IR(773, 5), IR(50050, 27), IR(0, 0), IR(113, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpConditionalCapabilityINTEL, false, false, IR(778, 2), IR(50077, 27), IR(0, 0), IR(113, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpSpecConstantTargetINTEL, true, true, IR(780, 4), IR(50104, 24), IR(0, 0), IR(314, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantArchitectureINTEL, true, true, IR(784, 6), IR(50128, 30), IR(0, 0), IR(314, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCapabilitiesINTEL, true, true, IR(790, 3), IR(50195, 30), IR(0, 0), IR(314, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConditionalCopyObjectINTEL, true, true, IR(107, 3), IR(50225, 27), IR(0, 0), IR(113, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpGroupIMulKHR, true, true, IR(283, 5), IR(50252, 13), IR(0, 0), IR(315, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMulKHR, true, true, IR(283, 5), IR(50265, 13), IR(0, 0), IR(315, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseAndKHR, true, true, IR(283, 5), IR(50278, 19), IR(0, 0), IR(315, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseOrKHR, true, true, IR(283, 5), IR(50297, 18), IR(0, 0), IR(315, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseXorKHR, true, true, IR(283, 5), IR(50315, 19), IR(0, 0), IR(315, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalAndKHR, true, true, IR(283, 5), IR(50334, 19), IR(0, 0), IR(315, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalOrKHR, true, true, IR(283, 5), IR(50353, 18), IR(0, 0), IR(315, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalXorKHR, true, true, IR(283, 5), IR(50371, 19), IR(0, 0), IR(315, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpRoundFToTF32INTEL, true, true, IR(160, 3), IR(50390, 18), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpMaskedGatherINTEL, true, true, IR(793, 6), IR(50408, 18), IR(0, 0), IR(317, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpMaskedScatterINTEL, false, false, IR(799, 4), IR(50426, 19), IR(0, 0), IR(317, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpConvertHandleToImageINTEL, true, true, IR(160, 3), IR(50445, 26), IR(0, 0), IR(318, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertHandleToSamplerINTEL, true, true, IR(160, 3), IR(50471, 28), IR(0, 0), IR(318, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertHandleToSampledImageINTEL, true, true, IR(160, 3), IR(50499, 33), IR(0, 0), IR(318, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
}};

// Opcode strings (without the 'Op' prefix) and opcode values, ordered by name.
// The fields in order are:
//   name, either the primary name or an alias, indexing into kStrings
//   index into kInstructionDesc
static const std::array<NameIndex, 916> kInstructionNames{{
  {IR(40931, 13), 595}, // 0 AbsISubINTEL
  {IR(40944, 13), 596}, // 1 AbsUSubINTEL
  {IR(29560, 12), 58}, // 2 AccessChain
  {IR(47999, 21), 781}, // 3 AliasDomainDeclINTEL
  {IR(48020, 20), 782}, // 4 AliasScopeDeclINTEL
  {IR(48040, 24), 783}, // 5 AliasScopeListDeclINTEL
  {IR(30857, 4), 143}, // 6 All
  {IR(36236, 25), 426}, // 7 AllocateNodePayloadsAMDX
  {IR(30853, 4), 142}, // 8 Any
  {IR(47786, 24), 772}, // 9 ArbitraryFloatACosINTEL
  {IR(47810, 26), 773}, // 10 ArbitraryFloatACosPiINTEL
  {IR(47736, 24), 770}, // 11 ArbitraryFloatASinINTEL
  {IR(47760, 26), 771}, // 12 ArbitraryFloatASinPiINTEL
  {IR(47886, 25), 776}, // 13 ArbitraryFloatATan2INTEL
  {IR(47836, 24), 774}, // 14 ArbitraryFloatATanINTEL
  {IR(47860, 26), 775}, // 15 ArbitraryFloatATanPiINTEL
  {IR(46756, 24), 743}, // 16 ArbitraryFloatAddALTERA
  {IR(46780, 23), 743}, // 17 ArbitraryFloatAddINTEL
  {IR(46585, 25), 740}, // 18 ArbitraryFloatCastALTERA
  {IR(46634, 32), 741}, // 19 ArbitraryFloatCastFromIntALTERA
  {IR(46666, 31), 741}, // 20 ArbitraryFloatCastFromIntINTEL
  {IR(46610, 24), 740}, // 21 ArbitraryFloatCastINTEL
  {IR(46697, 30), 742}, // 22 ArbitraryFloatCastToIntALTERA
  {IR(46727, 29), 742}, // 23 ArbitraryFloatCastToIntINTEL
  {IR(47271, 25), 754}, // 24 ArbitraryFloatCbrtALTERA
  {IR(47296, 24), 754}, // 25 ArbitraryFloatCbrtINTEL
  {IR(47637, 23), 766}, // 26 ArbitraryFloatCosINTEL
  {IR(47711, 25), 769}, // 27 ArbitraryFloatCosPiINTEL
  {IR(46897, 24), 746}, // 28 ArbitraryFloatDivALTERA
  {IR(46921, 23), 746}, // 29 ArbitraryFloatDivINTEL
  {IR(47124, 23), 751}, // 30 ArbitraryFloatEQALTERA
  {IR(47147, 22), 751}, // 31 ArbitraryFloatEQINTEL
  {IR(47564, 25), 763}, // 32 ArbitraryFloatExp10INTEL
  {IR(47540, 24), 762}, // 33 ArbitraryFloatExp2INTEL
  {IR(47517, 23), 761}, // 34 ArbitraryFloatExpINTEL
  {IR(47589, 25), 764}, // 35 ArbitraryFloatExpm1INTEL
  {IR(46989, 23), 748}, // 36 ArbitraryFloatGEALTERA
  {IR(47012, 22), 748}, // 37 ArbitraryFloatGEINTEL
  {IR(46944, 23), 747}, // 38 ArbitraryFloatGTALTERA
  {IR(46967, 22), 747}, // 39 ArbitraryFloatGTINTEL
  {IR(47320, 26), 755}, // 40 ArbitraryFloatHypotALTERA
  {IR(47346, 25), 755}, // 41 ArbitraryFloatHypotINTEL
  {IR(47079, 23), 750}, // 42 ArbitraryFloatLEALTERA
  {IR(47102, 22), 750}, // 43 ArbitraryFloatLEINTEL
  {IR(47034, 23), 749}, // 44 ArbitraryFloatLTALTERA
  {IR(47057, 22), 749}, // 45 ArbitraryFloatLTINTEL
  {IR(47467, 25), 759}, // 46 ArbitraryFloatLog10INTEL
  {IR(47492, 25), 760}, // 47 ArbitraryFloatLog1pINTEL
  {IR(47443, 24), 758}, // 48 ArbitraryFloatLog2INTEL
  {IR(47420, 23), 757}, // 49 ArbitraryFloatLogINTEL
  {IR(46850, 24), 745}, // 50 ArbitraryFloatMulALTERA
  {IR(46874, 23), 745}, // 51 ArbitraryFloatMulINTEL
  {IR(47911, 23), 777}, // 52 ArbitraryFloatPowINTEL
  {IR(47958, 24), 779}, // 53 ArbitraryFloatPowNINTEL
  {IR(47934, 24), 778}, // 54 ArbitraryFloatPowRINTEL
  {IR(47220, 26), 753}, // 55 ArbitraryFloatRSqrtALTERA
  {IR(47246, 25), 753}, // 56 ArbitraryFloatRSqrtINTEL
  {IR(47169, 26), 752}, // 57 ArbitraryFloatRecipALTERA
  {IR(47195, 25), 752}, // 58 ArbitraryFloatRecipINTEL
  {IR(47660, 26), 767}, // 59 ArbitraryFloatSinCosINTEL
  {IR(46528, 29), 739}, // 60 ArbitraryFloatSinCosPiALTERA
  {IR(46557, 28), 739}, // 61 ArbitraryFloatSinCosPiINTEL
  {IR(47614, 23), 765}, // 62 ArbitraryFloatSinINTEL
  {IR(47686, 25), 768}, // 63 ArbitraryFloatSinPiINTEL
  {IR(47371, 25), 756}, // 64 ArbitraryFloatSqrtALTERA
  {IR(47396, 24), 756}, // 65 ArbitraryFloatSqrtINTEL
  {IR(46803, 24), 744}, // 66 ArbitraryFloatSubALTERA
  {IR(46827, 23), 744}, // 67 ArbitraryFloatSubINTEL
  {IR(14873, 19), 827}, // 68 ArithmeticFenceEXT
  {IR(29607, 12), 61}, // 69 ArrayLength
  {IR(41178, 13), 611}, // 70 AsmCallINTEL
  {IR(13224, 9), 610}, // 71 AsmINTEL
  {IR(41163, 15), 609}, // 72 AsmTargetINTEL
  {IR(41219, 14), 614}, // 73 AssumeTrueKHR
  {IR(31879, 10), 220}, // 74 AtomicAnd
  {IR(31731, 22), 210}, // 75 AtomicCompareExchange
  {IR(31753, 26), 211}, // 76 AtomicCompareExchangeWeak
  {IR(31716, 15), 209}, // 77 AtomicExchange
  {IR(49278, 14), 817}, // 78 AtomicFAddEXT
  {IR(41205, 14), 613}, // 79 AtomicFMaxEXT
  {IR(41191, 14), 612}, // 80 AtomicFMinEXT
  {IR(33264, 16), 292}, // 81 AtomicFlagClear
  {IR(33243, 21), 291}, // 82 AtomicFlagTestAndSet
  {IR(31813, 11), 214}, // 83 AtomicIAdd
  {IR(31796, 17), 213}, // 84 AtomicIDecrement
  {IR(31779, 17), 212}, // 85 AtomicIIncrement
  {IR(31824, 11), 215}, // 86 AtomicISub
  {IR(31693, 11), 207}, // 87 AtomicLoad
  {IR(31889, 9), 221}, // 88 AtomicOr
  {IR(31857, 11), 218}, // 89 AtomicSMax
  {IR(31835, 11), 216}, // 90 AtomicSMin
  {IR(31704, 12), 208}, // 91 AtomicStore
  {IR(31868, 11), 219}, // 92 AtomicUMax
  {IR(31846, 11), 217}, // 93 AtomicUMin
  {IR(31898, 10), 222}, // 94 AtomicXor
  {IR(39427, 28), 541}, // 95 BeginInvocationInterlockEXT
  {IR(35790, 17), 407}, // 96 BitCastArrayQCOM
  {IR(31477, 9), 191}, // 97 BitCount
  {IR(31417, 15), 187}, // 98 BitFieldInsert
  {IR(31432, 17), 188}, // 99 BitFieldSExtract
  {IR(31449, 17), 189}, // 100 BitFieldUExtract
  {IR(31466, 11), 190}, // 101 BitReverse
  {IR(30605, 8), 114}, // 102 Bitcast
  {IR(31402, 11), 185}, // 103 BitwiseAnd
  {IR(50003, 21), 840}, // 104 BitwiseFunctionINTEL
  {IR(31381, 10), 183}, // 105 BitwiseOr
  {IR(31391, 11), 184}, // 106 BitwiseXor
  {IR(32008, 7), 227}, // 107 Branch
  {IR(32015, 18), 228}, // 108 BranchConditional
  {IR(36497, 17), 437}, // 109 BufferPointerEXT
  {IR(32876, 13), 277}, // 110 BuildNDRange
  {IR(28621, 11), 15}, // 111 Capability
  {IR(32834, 26), 275}, // 112 CaptureEventProfilingInfo
  {IR(34340, 23), 344}, // 113 ColorAttachmentReadEXT
  {IR(32426, 15), 255}, // 114 CommitReadPipe
  {IR(32441, 16), 256}, // 115 CommitWritePipe
  {IR(29867, 19), 72}, // 116 CompositeConstruct
  {IR(49408, 33), 822}, // 117 CompositeConstructContinuedINTEL
  {IR(35923, 30), 412}, // 118 CompositeConstructCoopMatQCOM
  {IR(35498, 31), 395}, // 119 CompositeConstructReplicateEXT
  {IR(29886, 17), 73}, // 120 CompositeExtract
  {IR(35953, 28), 413}, // 121 CompositeExtractCoopMatQCOM
  {IR(29903, 16), 74}, // 122 CompositeInsert
  {IR(50077, 27), 844}, // 123 ConditionalCapabilityINTEL
  {IR(50225, 27), 848}, // 124 ConditionalCopyObjectINTEL
  {IR(50050, 27), 843}, // 125 ConditionalEntryPointINTEL
  {IR(50024, 26), 842}, // 126 ConditionalExtensionINTEL
  {IR(17006, 9), 39}, // 127 Constant
  {IR(29127, 18), 40}, // 128 ConstantComposite
  {IR(49340, 32), 820}, // 129 ConstantCompositeContinuedINTEL
  {IR(35434, 30), 393}, // 130 ConstantCompositeReplicateEXT
  {IR(29075, 14), 38}, // 131 ConstantFalse
  {IR(41109, 29), 607}, // 132 ConstantFunctionPointerINTEL
  {IR(29239, 13), 42}, // 133 ConstantNull
  {IR(33319, 20), 296}, // 134 ConstantPipeStorage
  {IR(29223, 16), 41}, // 135 ConstantSampler
  {IR(36562, 18), 440}, // 136 ConstantSizeOfEXT
  {IR(36389, 19), 432}, // 137 ConstantStringAMDX
  {IR(29062, 13), 37}, // 138 ConstantTrue
  {IR(31664, 15), 205}, // 139 ControlBarrier
  {IR(49481, 26), 825}, // 140 ControlBarrierArriveINTEL
  {IR(49507, 24), 826}, // 141 ControlBarrierWaitINTEL
  {IR(49461, 20), 824}, // 142 ConvertBF16ToFINTEL
  {IR(49441, 20), 823}, // 143 ConvertFToBF16INTEL
  {IR(30411, 12), 100}, // 144 ConvertFToS
  {IR(30399, 12), 99}, // 145 ConvertFToU
  {IR(50445, 26), 860}, // 146 ConvertHandleToImageINTEL
  {IR(50499, 33), 862}, // 147 ConvertHandleToSampledImageINTEL
  {IR(50471, 28), 861}, // 148 ConvertHandleToSamplerINTEL
  {IR(40076, 18), 564}, // 149 ConvertImageToUNV
  {IR(30488, 14), 107}, // 150 ConvertPtrToU
  {IR(30423, 12), 101}, // 151 ConvertSToF
  {IR(40139, 25), 567}, // 152 ConvertSampledImageToUNV
  {IR(40094, 20), 565}, // 153 ConvertSamplerToUNV
  {IR(35012, 35), 379}, // 154 ConvertUToAccelerationStructureKHR
  {IR(30435, 12), 102}, // 155 ConvertUToF
  {IR(40038, 18), 562}, // 156 ConvertUToImageNV
  {IR(30532, 14), 110}, // 157 ConvertUToPtr
  {IR(40114, 25), 566}, // 158 ConvertUToSampledImageNV
  {IR(40056, 20), 563}, // 159 ConvertUToSamplerNV
  {IR(37662, 27), 480}, // 160 CooperativeMatrixConvertNV
  {IR(35407, 27), 392}, // 161 CooperativeMatrixLengthKHR
  {IR(39401, 26), 540}, // 162 CooperativeMatrixLengthNV
  {IR(35275, 25), 389}, // 163 CooperativeMatrixLoadKHR
  {IR(39326, 24), 537}, // 164 CooperativeMatrixLoadNV
  {IR(39625, 30), 544}, // 165 CooperativeMatrixLoadTensorNV
  {IR(35380, 27), 391}, // 166 CooperativeMatrixMulAddKHR
  {IR(39375, 26), 539}, // 167 CooperativeMatrixMulAddNV
  {IR(39686, 32), 546}, // 168 CooperativeMatrixPerElementOpNV
  {IR(39524, 26), 543}, // 169 CooperativeMatrixReduceNV
  {IR(35300, 26), 390}, // 170 CooperativeMatrixStoreKHR
  {IR(39350, 25), 538}, // 171 CooperativeMatrixStoreNV
  {IR(39655, 31), 545}, // 172 CooperativeMatrixStoreTensorNV
  {IR(40009, 29), 561}, // 173 CooperativeMatrixTransposeNV
  {IR(37885, 24), 487}, // 174 CooperativeVectorLoadNV
  {IR(37630, 32), 479}, // 175 CooperativeVectorMatrixMulAddNV
  {IR(37520, 29), 476}, // 176 CooperativeVectorMatrixMulNV
  {IR(37549, 42), 477}, // 177 CooperativeVectorOuterProductAccumulateNV
  {IR(37591, 39), 478}, // 178 CooperativeVectorReduceSumAccumulateNV
  {IR(37909, 25), 488}, // 179 CooperativeVectorStoreNV
  {IR(34299, 12), 340}, // 180 CopyLogical
  {IR(29533, 11), 56}, // 181 CopyMemory
  {IR(29544, 16), 57}, // 182 CopyMemorySized
  {IR(29919, 11), 75}, // 183 CopyObject
  {IR(33339, 26), 297}, // 184 CreatePipeFromPipeStorage
  {IR(39754, 21), 549}, // 185 CreateTensorLayoutNV
  {IR(39874, 19), 554}, // 186 CreateTensorViewNV
  {IR(32786, 16), 272}, // 187 CreateUserEvent
  {IR(48476, 30), 796}, // 188 CrossWorkgroupCastToPtrALTERA
  {IR(48506, 29), 796}, // 189 CrossWorkgroupCastToPtrINTEL
  {IR(31486, 5), 192}, // 190 DPdx
  {IR(31532, 11), 198}, // 191 DPdxCoarse
  {IR(31503, 9), 195}, // 192 DPdxFine
  {IR(31491, 5), 193}, // 193 DPdy
  {IR(31543, 11), 199}, // 194 DPdyCoarse
  {IR(31512, 9), 196}, // 195 DPdyFine
  {IR(29693, 9), 64}, // 196 Decorate
  {IR(33516, 11), 305}, // 197 DecorateId
  {IR(41243, 15), 616}, // 198 DecorateString
  {IR(41258, 21), 616}, // 199 DecorateStringGOOGLE
  {IR(29717, 16), 66}, // 200 DecorationGroup
  {IR(12474, 25), 557}, // 201 DemoteToHelperInvocation
  {IR(12499, 28), 557}, // 202 DemoteToHelperInvocationEXT
  {IR(34363, 23), 345}, // 203 DepthAttachmentReadEXT
  {IR(30802, 4), 137}, // 204 Dot
  {IR(37689, 17), 481}, // 205 EmitMeshTasksEXT
  {IR(31591, 17), 203}, // 206 EmitStreamVertex
  {IR(31567, 11), 201}, // 207 EmitVertex
  {IR(39455, 26), 542}, // 208 EndInvocationInterlockEXT
  {IR(31578, 13), 202}, // 209 EndPrimitive
  {IR(31608, 19), 204}, // 210 EndStreamPrimitive
  {IR(32622, 14), 265}, // 211 EnqueueKernel
  {IR(32608, 14), 264}, // 212 EnqueueMarker
  {IR(36261, 24), 427}, // 213 EnqueueNodePayloadsAMDX
  {IR(28536, 11), 13}, // 214 EntryPoint
  {IR(34993, 19), 378}, // 215 ExecuteCallableKHR
  {IR(39037, 18), 527}, // 216 ExecuteCallableNV
  {IR(28579, 14), 14}, // 217 ExecutionMode
  {IR(33500, 16), 304}, // 218 ExecutionModeId
  {IR(41233, 10), 615}, // 219 ExpectKHR
  {IR(28390, 8), 11}, // 220 ExtInst
  {IR(28330, 14), 10}, // 221 ExtInstImport
  {IR(34930, 26), 375}, // 222 ExtInstWithForwardRefsKHR
  {IR(28320, 10), 9}, // 223 Extension
  {IR(35981, 20), 414}, // 224 ExtractSubArrayQCOM
  {IR(30634, 5), 118}, // 225 FAdd
  {IR(30465, 9), 105}, // 226 FConvert
  {IR(30669, 5), 125}, // 227 FDiv
  {IR(30694, 5), 130}, // 228 FMod
  {IR(30654, 5), 122}, // 229 FMul
  {IR(30621, 8), 116}, // 230 FNegate
  {IR(31131, 10), 168}, // 231 FOrdEqual
  {IR(31209, 16), 174}, // 232 FOrdGreaterThan
  {IR(31281, 21), 178}, // 233 FOrdGreaterThanEqual
  {IR(31181, 13), 172}, // 234 FOrdLessThan
  {IR(31243, 18), 176}, // 235 FOrdLessThanEqual
  {IR(31153, 13), 170}, // 236 FOrdNotEqual
  {IR(14420, 14), 799}, // 237 FPGARegALTERA
  {IR(14434, 13), 799}, // 238 FPGARegINTEL
  {IR(30689, 5), 129}, // 239 FRem
  {IR(30644, 5), 120}, // 240 FSub
  {IR(31141, 12), 169}, // 241 FUnordEqual
  {IR(31225, 18), 175}, // 242 FUnordGreaterThan
  {IR(31302, 23), 179}, // 243 FUnordGreaterThanEqual
  {IR(31194, 15), 173}, // 244 FUnordLessThan
  {IR(31261, 20), 177}, // 245 FUnordLessThanEqual
  {IR(31166, 15), 171}, // 246 FUnordNotEqual
  {IR(37847, 38), 486}, // 247 FetchMicroTriangleVertexBarycentricNV
  {IR(37812, 35), 485}, // 248 FetchMicroTriangleVertexPositionNV
  {IR(36310, 29), 429}, // 249 FinishWritingNodePayloadAMDX
  {IR(48190, 15), 788}, // 250 FixedCosALTERA
  {IR(48205, 14), 788}, // 251 FixedCosINTEL
  {IR(48287, 17), 791}, // 252 FixedCosPiALTERA
  {IR(48304, 16), 791}, // 253 FixedCosPiINTEL
  {IR(48388, 15), 794}, // 254 FixedExpALTERA
  {IR(48403, 14), 794}, // 255 FixedExpINTEL
  {IR(48359, 15), 793}, // 256 FixedLogALTERA
  {IR(48374, 14), 793}, // 257 FixedLogINTEL
  {IR(48095, 17), 785}, // 258 FixedRecipALTERA
  {IR(48112, 16), 785}, // 259 FixedRecipINTEL
  {IR(48128, 17), 786}, // 260 FixedRsqrtALTERA
  {IR(48145, 16), 786}, // 261 FixedRsqrtINTEL
  {IR(48161, 15), 787}, // 262 FixedSinALTERA
  {IR(48219, 18), 789}, // 263 FixedSinCosALTERA
  {IR(48237, 17), 789}, // 264 FixedSinCosINTEL
  {IR(48320, 20), 792}, // 265 FixedSinCosPiALTERA
  {IR(48340, 19), 792}, // 266 FixedSinCosPiINTEL
  {IR(48176, 14), 787}, // 267 FixedSinINTEL
  {IR(48254, 17), 790}, // 268 FixedSinPiALTERA
  {IR(48271, 16), 790}, // 269 FixedSinPiINTEL
  {IR(48064, 16), 784}, // 270 FixedSqrtALTERA
  {IR(48080, 15), 784}, // 271 FixedSqrtINTEL
  {IR(34847, 7), 369}, // 272 FmaKHR
  {IR(36206, 17), 424}, // 273 FragmentFetchAMD
  {IR(36185, 21), 423}, // 274 FragmentMaskFetchAMD
  {IR(27386, 9), 48}, // 275 Function
  {IR(29442, 13), 51}, // 276 FunctionCall
  {IR(29430, 12), 50}, // 277 FunctionEnd
  {IR(29412, 18), 49}, // 278 FunctionParameter
  {IR(41138, 25), 608}, // 279 FunctionPointerCallINTEL
  {IR(31496, 7), 194}, // 280 Fwidth
  {IR(31554, 13), 200}, // 281 FwidthCoarse
  {IR(31521, 11), 197}, // 282 FwidthFine
  {IR(30563, 17), 112}, // 283 GenericCastToPtr
  {IR(30580, 25), 113}, // 284 GenericCastToPtrExplicit
  {IR(29619, 23), 62}, // 285 GenericPtrMemSemantics
  {IR(32860, 16), 276}, // 286 GetDefaultQueue
  {IR(33365, 35), 298}, // 287 GetKernelLocalSizeForSubgroupCount
  {IR(33400, 25), 299}, // 288 GetKernelMaxNumSubgroups
  {IR(32666, 32), 267}, // 289 GetKernelNDrangeMaxSubGroupSize
  {IR(32636, 30), 266}, // 290 GetKernelNDrangeSubGroupCount
  {IR(32721, 40), 269}, // 291 GetKernelPreferredWorkGroupSizeMultiple
  {IR(32698, 23), 268}, // 292 GetKernelWorkGroupSize
  {IR(32492, 18), 259}, // 293 GetMaxPipePackets
  {IR(32474, 18), 258}, // 294 GetNumPipePackets
  {IR(9913, 9), 353}, // 295 GraphARM
  {IR(34515, 17), 351}, // 296 GraphConstantARM
  {IR(34583, 12), 356}, // 297 GraphEndARM
  {IR(34532, 19), 352}, // 298 GraphEntryPointARM
  {IR(34551, 14), 354}, // 299 GraphInputARM
  {IR(34565, 18), 355}, // 300 GraphSetOutputARM
  {IR(32179, 9), 238}, // 301 GroupAll
  {IR(32188, 9), 239}, // 302 GroupAny
  {IR(32148, 15), 236}, // 303 GroupAsyncCopy
  {IR(50278, 19), 851}, // 304 GroupBitwiseAndKHR
  {IR(50297, 18), 852}, // 305 GroupBitwiseOrKHR
  {IR(50315, 19), 853}, // 306 GroupBitwiseXorKHR
  {IR(32197, 15), 240}, // 307 GroupBroadcast
  {IR(32567, 20), 262}, // 308 GroupCommitReadPipe
  {IR(32587, 21), 263}, // 309 GroupCommitWritePipe
  {IR(29733, 14), 67}, // 310 GroupDecorate
  {IR(32255, 10), 242}, // 311 GroupFAdd
  {IR(36024, 23), 416}, // 312 GroupFAddNonUniformAMD
  {IR(32295, 10), 246}, // 313 GroupFMax
  {IR(36116, 23), 420}, // 314 GroupFMaxNonUniformAMD
  {IR(32265, 10), 243}, // 315 GroupFMin
  {IR(36047, 23), 417}, // 316 GroupFMinNonUniformAMD
  {IR(50265, 13), 850}, // 317 GroupFMulKHR
  {IR(32245, 10), 241}, // 318 GroupIAdd
  {IR(36001, 23), 415}, // 319 GroupIAddNonUniformAMD
  {IR(50252, 13), 849}, // 320 GroupIMulKHR
  {IR(50334, 19), 854}, // 321 GroupLogicalAndKHR
  {IR(50353, 18), 855}, // 322 GroupLogicalOrKHR
  {IR(50371, 19), 856}, // 323 GroupLogicalXorKHR
  {IR(29792, 20), 68}, // 324 GroupMemberDecorate
  {IR(33548, 19), 307}, // 325 GroupNonUniformAll
  {IR(33586, 24), 309}, // 326 GroupNonUniformAllEqual
  {IR(33567, 19), 308}, // 327 GroupNonUniformAny
  {IR(6483, 22), 312}, // 328 GroupNonUniformBallot
  {IR(33726, 30), 315}, // 329 GroupNonUniformBallotBitCount
  {IR(33694, 32), 314}, // 330 GroupNonUniformBallotBitExtract
  {IR(33756, 29), 316}, // 331 GroupNonUniformBallotFindLSB
  {IR(33785, 29), 317}, // 332 GroupNonUniformBallotFindMSB
  {IR(34092, 26), 332}, // 333 GroupNonUniformBitwiseAnd
  {IR(34118, 25), 333}, // 334 GroupNonUniformBitwiseOr
  {IR(34143, 26), 334}, // 335 GroupNonUniformBitwiseXor
  {IR(33610, 25), 310}, // 336 GroupNonUniformBroadcast
  {IR(33635, 30), 311}, // 337 GroupNonUniformBroadcastFirst
  {IR(33527, 21), 306}, // 338 GroupNonUniformElect
  {IR(33912, 20), 323}, // 339 GroupNonUniformFAdd
  {IR(34072, 20), 331}, // 340 GroupNonUniformFMax
  {IR(34012, 20), 328}, // 341 GroupNonUniformFMin
  {IR(33952, 20), 325}, // 342 GroupNonUniformFMul
  {IR(33892, 20), 322}, // 343 GroupNonUniformIAdd
  {IR(33932, 20), 324}, // 344 GroupNonUniformIMul
  {IR(33665, 29), 313}, // 345 GroupNonUniformInverseBallot
  {IR(34169, 26), 335}, // 346 GroupNonUniformLogicalAnd
  {IR(34195, 25), 336}, // 347 GroupNonUniformLogicalOr
  {IR(34220, 26), 337}, // 348 GroupNonUniformLogicalXor
  {IR(37724, 28), 483}, // 349 GroupNonUniformPartitionEXT
  {IR(37752, 27), 483}, // 350 GroupNonUniformPartitionNV
  {IR(36431, 26), 434}, // 351 GroupNonUniformQuadAllKHR
  {IR(36457, 26), 435}, // 352 GroupNonUniformQuadAnyKHR
  {IR(34246, 29), 338}, // 353 GroupNonUniformQuadBroadcast
  {IR(34275, 24), 339}, // 354 GroupNonUniformQuadSwap
  {IR(14659, 25), 373}, // 355 GroupNonUniformRotateKHR
  {IR(34032, 20), 329}, // 356 GroupNonUniformSMax
  {IR(33972, 20), 326}, // 357 GroupNonUniformSMin
  {IR(9622, 23), 318}, // 358 GroupNonUniformShuffle
  {IR(33865, 27), 321}, // 359 GroupNonUniformShuffleDown
  {IR(33840, 25), 320}, // 360 GroupNonUniformShuffleUp
  {IR(33814, 26), 319}, // 361 GroupNonUniformShuffleXor
  {IR(34052, 20), 330}, // 362 GroupNonUniformUMax
  {IR(33992, 20), 327}, // 363 GroupNonUniformUMin
  {IR(32510, 28), 260}, // 364 GroupReserveReadPipePackets
  {IR(32538, 29), 261}, // 365 GroupReserveWritePipePackets
  {IR(32315, 10), 248}, // 366 GroupSMax
  {IR(36162, 23), 422}, // 367 GroupSMaxNonUniformAMD
  {IR(32285, 10), 245}, // 368 GroupSMin
  {IR(36093, 23), 419}, // 369 GroupSMinNonUniformAMD
  {IR(32305, 10), 247}, // 370 GroupUMax
  {IR(36139, 23), 421}, // 371 GroupUMaxNonUniformAMD
  {IR(32275, 10), 244}, // 372 GroupUMin
  {IR(36070, 23), 418}, // 373 GroupUMinNonUniformAMD
  {IR(32163, 16), 237}, // 374 GroupWaitEvents
  {IR(38381, 26), 504}, // 375 HitObjectExecuteShaderEXT
  {IR(37015, 25), 456}, // 376 HitObjectExecuteShaderNV
  {IR(38434, 26), 506}, // 377 HitObjectGetAttributesEXT
  {IR(37066, 25), 458}, // 378 HitObjectGetAttributesNV
  {IR(39113, 24), 529}, // 379 HitObjectGetClusterIdNV
  {IR(38407, 27), 505}, // 380 HitObjectGetCurrentTimeEXT
  {IR(37040, 26), 457}, // 381 HitObjectGetCurrentTimeNV
  {IR(38513, 29), 509}, // 382 HitObjectGetGeometryIndexEXT
  {IR(37142, 28), 461}, // 383 HitObjectGetGeometryIndexNV
  {IR(38460, 23), 507}, // 384 HitObjectGetHitKindEXT
  {IR(37091, 22), 459}, // 385 HitObjectGetHitKindNV
  {IR(38568, 35), 511}, // 386 HitObjectGetInstanceCustomIndexEXT
  {IR(37195, 34), 463}, // 387 HitObjectGetInstanceCustomIndexNV
  {IR(38542, 26), 510}, // 388 HitObjectGetInstanceIdEXT
  {IR(37170, 25), 462}, // 389 HitObjectGetInstanceIdNV
  {IR(38014, 51), 492}, // 390 HitObjectGetIntersectionTriangleVertexPositionsEXT
  {IR(40505, 27), 577}, // 391 HitObjectGetLSSPositionsNV
  {IR(40532, 23), 578}, // 392 HitObjectGetLSSRadiiNV
  {IR(38634, 34), 513}, // 393 HitObjectGetObjectRayDirectionEXT
  {IR(36727, 33), 446}, // 394 HitObjectGetObjectRayDirectionNV
  {IR(38603, 31), 512}, // 395 HitObjectGetObjectRayOriginEXT
  {IR(36760, 30), 447}, // 396 HitObjectGetObjectRayOriginNV
  {IR(38731, 29), 516}, // 397 HitObjectGetObjectToWorldEXT
  {IR(36699, 28), 445}, // 398 HitObjectGetObjectToWorldNV
  {IR(38483, 30), 508}, // 399 HitObjectGetPrimitiveIndexEXT
  {IR(37113, 29), 460}, // 400 HitObjectGetPrimitiveIndexNV
  {IR(38065, 24), 493}, // 401 HitObjectGetRayFlagsEXT
  {IR(38789, 23), 518}, // 402 HitObjectGetRayTMaxEXT
  {IR(37290, 22), 466}, // 403 HitObjectGetRayTMaxNV
  {IR(39137, 23), 530}, // 404 HitObjectGetRayTMinEXT
  {IR(37312, 22), 467}, // 405 HitObjectGetRayTMinNV
  {IR(39160, 45), 531}, // 406 HitObjectGetShaderBindingTableRecordIndexEXT
  {IR(36855, 44), 450}, // 407 HitObjectGetShaderBindingTableRecordIndexNV
  {IR(39205, 40), 532}, // 408 HitObjectGetShaderRecordBufferHandleEXT
  {IR(36816, 39), 449}, // 409 HitObjectGetShaderRecordBufferHandleNV
  {IR(40449, 29), 575}, // 410 HitObjectGetSpherePositionNV
  {IR(40478, 27), 576}, // 411 HitObjectGetSphereRadiusNV
  {IR(38668, 33), 514}, // 412 HitObjectGetWorldRayDirectionEXT
  {IR(37229, 32), 464}, // 413 HitObjectGetWorldRayDirectionNV
  {IR(38701, 30), 515}, // 414 HitObjectGetWorldRayOriginEXT
  {IR(37261, 29), 465}, // 415 HitObjectGetWorldRayOriginNV
  {IR(38760, 29), 517}, // 416 HitObjectGetWorldToObjectEXT
  {IR(36671, 28), 444}, // 417 HitObjectGetWorldToObjectNV
  {IR(39245, 20), 533}, // 418 HitObjectIsEmptyEXT
  {IR(37334, 19), 468}, // 419 HitObjectIsEmptyNV
  {IR(39265, 18), 534}, // 420 HitObjectIsHitEXT
  {IR(37353, 17), 469}, // 421 HitObjectIsHitNV
  {IR(40578, 20), 580}, // 422 HitObjectIsLSSHitNV
  {IR(39283, 19), 535}, // 423 HitObjectIsMissEXT
  {IR(37370, 18), 470}, // 424 HitObjectIsMissNV
  {IR(40555, 23), 579}, // 425 HitObjectIsSphereHitNV
  {IR(38357, 24), 503}, // 426 HitObjectRecordEmptyEXT
  {IR(36899, 23), 451}, // 427 HitObjectRecordEmptyNV
  {IR(37934, 28), 489}, // 428 HitObjectRecordFromQueryEXT
  {IR(36580, 27), 441}, // 429 HitObjectRecordHitMotionNV
  {IR(36942, 21), 453}, // 430 HitObjectRecordHitNV
  {IR(36607, 36), 442}, // 431 HitObjectRecordHitWithIndexMotionNV
  {IR(36963, 30), 454}, // 432 HitObjectRecordHitWithIndexNV
  {IR(37962, 23), 490}, // 433 HitObjectRecordMissEXT
  {IR(37985, 29), 491}, // 434 HitObjectRecordMissMotionEXT
  {IR(36643, 28), 443}, // 435 HitObjectRecordMissMotionNV
  {IR(36993, 22), 455}, // 436 HitObjectRecordMissNV
  {IR(38134, 33), 495}, // 437 HitObjectReorderExecuteShaderEXT
  {IR(38089, 45), 494}, // 438 HitObjectSetShaderBindingTableRecordIndexEXT
  {IR(38199, 38), 497}, // 439 HitObjectTraceMotionReorderExecuteEXT
  {IR(38309, 21), 501}, // 440 HitObjectTraceRayEXT
  {IR(38330, 27), 502}, // 441 HitObjectTraceRayMotionEXT
  {IR(36790, 26), 448}, // 442 HitObjectTraceRayMotionNV
  {IR(36922, 20), 452}, // 443 HitObjectTraceRayNV
  {IR(38167, 32), 496}, // 444 HitObjectTraceReorderExecuteEXT
  {IR(30629, 5), 117}, // 445 IAdd
  {IR(30806, 10), 138}, // 446 IAddCarry
  {IR(40957, 13), 597}, // 447 IAddSatINTEL
  {IR(40983, 14), 599}, // 448 IAverageINTEL
  {IR(41011, 21), 601}, // 449 IAverageRoundedINTEL
  {IR(31002, 7), 158}, // 450 IEqual
  {IR(30649, 5), 121}, // 451 IMul
  {IR(41079, 15), 605}, // 452 IMul32x16INTEL
  {IR(31009, 10), 159}, // 453 INotEqual
  {IR(30639, 5), 119}, // 454 ISub
  {IR(30816, 11), 139}, // 455 ISubBorrow
  {IR(41053, 13), 603}, // 456 ISubSatINTEL
  {IR(35047, 22), 380}, // 457 IgnoreIntersectionKHR
  {IR(38855, 21), 520}, // 458 IgnoreIntersectionNV
  {IR(27430, 6), 91}, // 459 Image
  {IR(35894, 29), 411}, // 460 ImageBlockMatchGatherSADQCOM
  {IR(35865, 29), 410}, // 461 ImageBlockMatchGatherSSDQCOM
  {IR(35767, 23), 406}, // 462 ImageBlockMatchSADQCOM
  {IR(35744, 23), 405}, // 463 ImageBlockMatchSSDQCOM
  {IR(35836, 29), 409}, // 464 ImageBlockMatchWindowSADQCOM
  {IR(35807, 29), 408}, // 465 ImageBlockMatchWindowSSDQCOM
  {IR(35725, 19), 404}, // 466 ImageBoxFilterQCOM
  {IR(30247, 16), 88}, // 467 ImageDrefGather
  {IR(30224, 11), 86}, // 468 ImageFetch
  {IR(30235, 12), 87}, // 469 ImageGather
  {IR(30284, 17), 92}, // 470 ImageQueryFormat
  {IR(30364, 17), 97}, // 471 ImageQueryLevels
  {IR(30350, 14), 96}, // 472 ImageQueryLod
  {IR(30301, 16), 93}, // 473 ImageQueryOrder
  {IR(30381, 18), 98}, // 474 ImageQuerySamples
  {IR(30335, 15), 95}, // 475 ImageQuerySize
  {IR(30317, 18), 94}, // 476 ImageQuerySizeLod
  {IR(30263, 10), 89}, // 477 ImageRead
  {IR(30081, 27), 81}, // 478 ImageSampleDrefExplicitLod
  {IR(30054, 27), 80}, // 479 ImageSampleDrefImplicitLod
  {IR(30031, 23), 79}, // 480 ImageSampleExplicitLod
  {IR(37457, 23), 474}, // 481 ImageSampleFootprintNV
  {IR(29985, 23), 78}, // 482 ImageSampleImplicitLod
  {IR(30193, 31), 85}, // 483 ImageSampleProjDrefExplicitLod
  {IR(30162, 31), 84}, // 484 ImageSampleProjDrefImplicitLod
  {IR(30135, 27), 83}, // 485 ImageSampleProjExplicitLod
  {IR(30108, 27), 82}, // 486 ImageSampleProjImplicitLod
  {IR(35701, 24), 403}, // 487 ImageSampleWeightedQCOM
  {IR(33188, 22), 288}, // 488 ImageSparseDrefGather
  {IR(33153, 17), 286}, // 489 ImageSparseFetch
  {IR(33170, 18), 287}, // 490 ImageSparseGather
  {IR(33280, 16), 293}, // 491 ImageSparseRead
  {IR(32980, 33), 281}, // 492 ImageSparseSampleDrefExplicitLod
  {IR(32947, 33), 280}, // 493 ImageSparseSampleDrefImplicitLod
  {IR(32918, 29), 279}, // 494 ImageSparseSampleExplicitLod
  {IR(32889, 29), 278}, // 495 ImageSparseSampleImplicitLod
  {IR(33116, 37), 285}, // 496 ImageSparseSampleProjDrefExplicitLod
  {IR(33079, 37), 284}, // 497 ImageSparseSampleProjDrefImplicitLod
  {IR(33046, 33), 283}, // 498 ImageSparseSampleProjExplicitLod
  {IR(33013, 33), 282}, // 499 ImageSparseSampleProjImplicitLod
  {IR(33210, 26), 289}, // 500 ImageSparseTexelsResident
  {IR(29464, 18), 53}, // 501 ImageTexelPointer
  {IR(30273, 11), 90}, // 502 ImageWrite
  {IR(29572, 20), 59}, // 503 InBoundsAccessChain
  {IR(29642, 23), 63}, // 504 InBoundsPtrAccessChain
  {IR(30873, 9), 146}, // 505 IsFinite
  {IR(39940, 22), 558}, // 506 IsHelperInvocationEXT
  {IR(30867, 6), 145}, // 507 IsInf
  {IR(30861, 6), 144}, // 508 IsNan
  {IR(36366, 23), 431}, // 509 IsNodePayloadValidAMDX
  {IR(30882, 9), 147}, // 510 IsNormal
  {IR(32802, 13), 273}, // 511 IsValidEvent
  {IR(32457, 17), 257}, // 512 IsValidReserveId
  {IR(32085, 5), 230}, // 513 Kill
  {IR(32002, 6), 226}, // 514 Label
  {IR(30902, 14), 149}, // 515 LessOrGreater
  {IR(32121, 14), 234}, // 516 LifetimeStart
  {IR(32135, 13), 235}, // 517 LifetimeStop
  {IR(28315, 5), 8}, // 518 Line
  {IR(29522, 5), 54}, // 519 Load
  {IR(30973, 11), 155}, // 520 LogicalAnd
  {IR(30934, 13), 152}, // 521 LogicalEqual
  {IR(30984, 11), 156}, // 522 LogicalNot
  {IR(30947, 16), 153}, // 523 LogicalNotEqual
  {IR(30963, 10), 154}, // 524 LogicalOr
  {IR(47982, 17), 780}, // 525 LoopControlINTEL
  {IR(31942, 10), 224}, // 526 LoopMerge
  {IR(50408, 18), 858}, // 527 MaskedGatherINTEL
  {IR(50426, 19), 859}, // 528 MaskedScatterINTEL
  {IR(30771, 18), 135}, // 529 MatrixTimesMatrix
  {IR(30717, 18), 132}, // 530 MatrixTimesScalar
  {IR(30753, 18), 134}, // 531 MatrixTimesVector
  {IR(29702, 15), 65}, // 532 MemberDecorate
  {IR(36542, 20), 439}, // 533 MemberDecorateIdEXT
  {IR(41279, 21), 617}, // 534 MemberDecorateString
  {IR(41300, 27), 617}, // 535 MemberDecorateStringGOOGLE
  {IR(28297, 11), 6}, // 536 MemberName
  {IR(31679, 14), 206}, // 537 MemoryBarrier
  {IR(28462, 12), 12}, // 538 MemoryModel
  {IR(33465, 19), 302}, // 539 MemoryNamedBarrier
  {IR(33484, 16), 303}, // 540 ModuleProcessed
  {IR(28292, 5), 5}, // 541 Name
  {IR(33442, 23), 301}, // 542 NamedBarrierInitialize
  {IR(33236, 7), 290}, // 543 NoLine
  {IR(36339, 27), 430}, // 544 NodePayloadArrayLengthAMDX
  {IR(28088, 4), 0}, // 545 Nop
  {IR(31413, 4), 186}, // 546 Not
  {IR(30916, 8), 150}, // 547 Ordered
  {IR(30789, 13), 136}, // 548 OuterProduct
  {IR(31908, 4), 223}, // 549 Phi
  {IR(29592, 15), 60}, // 550 PtrAccessChain
  {IR(48417, 30), 795}, // 551 PtrCastToCrossWorkgroupALTERA
  {IR(48447, 29), 795}, // 552 PtrCastToCrossWorkgroupINTEL
  {IR(30546, 17), 111}, // 553 PtrCastToGeneric
  {IR(34332, 8), 343}, // 554 PtrDiff
  {IR(34311, 9), 341}, // 555 PtrEqual
  {IR(34320, 12), 342}, // 556 PtrNotEqual
  {IR(30474, 14), 106}, // 557 QuantizeToF16
  {IR(40245, 17), 569}, // 558 RawAccessChainNV
  {IR(35620, 31), 400}, // 559 RayQueryConfirmIntersectionKHR
  {IR(35588, 32), 399}, // 560 RayQueryGenerateIntersectionKHR
  {IR(39090, 23), 528}, // 561 RayQueryGetClusterIdNV
  {IR(48929, 39), 808}, // 562 RayQueryGetIntersectionBarycentricsKHR
  {IR(49004, 46), 810}, // 563 RayQueryGetIntersectionCandidateAABBOpaqueKHR
  {IR(39055, 35), 528}, // 564 RayQueryGetIntersectionClusterIdNV
  {IR(48968, 36), 809}, // 565 RayQueryGetIntersectionFrontFaceKHR
  {IR(48848, 40), 806}, // 566 RayQueryGetIntersectionGeometryIndexKHR
  {IR(48700, 46), 803}, // 567 RayQueryGetIntersectionInstanceCustomIndexKHR
  {IR(48746, 37), 804}, // 568 RayQueryGetIntersectionInstanceIdKHR
  {IR(48783, 65), 805}, // 569 RayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR
  {IR(40412, 37), 574}, // 570 RayQueryGetIntersectionLSSHitValueNV
  {IR(40340, 38), 572}, // 571 RayQueryGetIntersectionLSSPositionsNV
  {IR(40378, 34), 573}, // 572 RayQueryGetIntersectionLSSRadiiNV
  {IR(49050, 45), 811}, // 573 RayQueryGetIntersectionObjectRayDirectionKHR
  {IR(49095, 42), 812}, // 574 RayQueryGetIntersectionObjectRayOriginKHR
  {IR(49198, 40), 815}, // 575 RayQueryGetIntersectionObjectToWorldKHR
  {IR(48888, 41), 807}, // 576 RayQueryGetIntersectionPrimitiveIndexKHR
  {IR(40262, 40), 570}, // 577 RayQueryGetIntersectionSpherePositionNV
  {IR(40302, 38), 571}, // 578 RayQueryGetIntersectionSphereRadiusNV
  {IR(48672, 28), 802}, // 579 RayQueryGetIntersectionTKHR
  {IR(38930, 50), 525}, // 580 RayQueryGetIntersectionTriangleVertexPositionsKHR
  {IR(35670, 31), 402}, // 581 RayQueryGetIntersectionTypeKHR
  {IR(49238, 40), 816}, // 582 RayQueryGetIntersectionWorldToObjectKHR
  {IR(48649, 23), 801}, // 583 RayQueryGetRayFlagsKHR
  {IR(48627, 22), 800}, // 584 RayQueryGetRayTMinKHR
  {IR(49137, 32), 813}, // 585 RayQueryGetWorldRayDirectionKHR
  {IR(49169, 29), 814}, // 586 RayQueryGetWorldRayOriginKHR
  {IR(35545, 22), 397}, // 587 RayQueryInitializeKHR
  {IR(40620, 19), 582}, // 588 RayQueryIsLSSHitNV
  {IR(40598, 22), 581}, // 589 RayQueryIsSphereHitNV
  {IR(35651, 19), 401}, // 590 RayQueryProceedKHR
  {IR(35567, 21), 398}, // 591 RayQueryTerminateKHR
  {IR(36223, 13), 425}, // 592 ReadClockKHR
  {IR(32325, 9), 249}, // 593 ReadPipe
  {IR(48535, 23), 797}, // 594 ReadPipeBlockingALTERA
  {IR(48558, 22), 797}, // 595 ReadPipeBlockingINTEL
  {IR(32773, 13), 271}, // 596 ReleaseEvent
  {IR(38254, 25), 499}, // 597 ReorderThreadWithHintEXT
  {IR(37417, 24), 472}, // 598 ReorderThreadWithHintNV
  {IR(38279, 30), 500}, // 599 ReorderThreadWithHitObjectEXT
  {IR(37388, 29), 471}, // 600 ReorderThreadWithHitObjectNV
  {IR(38812, 22), 519}, // 601 ReportIntersectionKHR
  {IR(38834, 21), 519}, // 602 ReportIntersectionNV
  {IR(32379, 23), 253}, // 603 ReserveReadPipePackets
  {IR(32402, 24), 254}, // 604 ReserveWritePipePackets
  {IR(32344, 17), 251}, // 605 ReservedReadPipe
  {IR(32361, 18), 252}, // 606 ReservedWritePipe
  {IR(46509, 19), 738}, // 607 RestoreMemoryINTEL
  {IR(32761, 12), 270}, // 608 RetainEvent
  {IR(32090, 7), 231}, // 609 Return
  {IR(32097, 12), 232}, // 610 ReturnValue
  {IR(50390, 18), 857}, // 611 RoundFToTF32INTEL
  {IR(30456, 9), 104}, // 612 SConvert
  {IR(30664, 5), 124}, // 613 SDiv
  {IR(35132, 5), 382}, // 614 SDot
  {IR(35173, 11), 385}, // 615 SDotAccSat
  {IR(35184, 14), 385}, // 616 SDotAccSatKHR
  {IR(35137, 8), 382}, // 617 SDotKHR
  {IR(31032, 13), 161}, // 618 SGreaterThan
  {IR(31063, 18), 163}, // 619 SGreaterThanEqual
  {IR(31091, 10), 165}, // 620 SLessThan
  {IR(31116, 15), 167}, // 621 SLessThanEqual
  {IR(30684, 5), 128}, // 622 SMod
  {IR(30840, 13), 141}, // 623 SMulExtended
  {IR(30613, 8), 115}, // 624 SNegate
  {IR(30679, 5), 127}, // 625 SRem
  {IR(35158, 6), 384}, // 626 SUDot
  {IR(35223, 12), 387}, // 627 SUDotAccSat
  {IR(35235, 15), 387}, // 628 SUDotAccSatKHR
  {IR(35164, 9), 384}, // 629 SUDotKHR
  {IR(29940, 13), 77}, // 630 SampledImage
  {IR(40164, 29), 568}, // 631 SamplerImageAddressingModeNV
  {IR(30502, 15), 108}, // 632 SatConvertSToU
  {IR(30517, 15), 109}, // 633 SatConvertUToS
  {IR(46493, 16), 737}, // 634 SaveMemoryINTEL
  {IR(30995, 7), 157}, // 635 Select
  {IR(31987, 15), 225}, // 636 SelectionMerge
  {IR(37706, 18), 482}, // 637 SetMeshOutputsEXT
  {IR(32815, 19), 274}, // 638 SetUserEventStatus
  {IR(31364, 17), 182}, // 639 ShiftLeftLogical
  {IR(31343, 21), 181}, // 640 ShiftRightArithmetic
  {IR(31325, 18), 180}, // 641 ShiftRightLogical
  {IR(30891, 11), 148}, // 642 SignBitSet
  {IR(33296, 7), 294}, // 643 SizeOf
  {IR(28269, 7), 3}, // 644 Source
  {IR(28150, 16), 2}, // 645 SourceContinued
  {IR(28276, 16), 4}, // 646 SourceExtension
  {IR(29287, 13), 45}, // 647 SpecConstant
  {IR(50128, 30), 846}, // 648 SpecConstantArchitectureINTEL
  {IR(50195, 30), 847}, // 649 SpecConstantCapabilitiesINTEL
  {IR(29300, 22), 46}, // 650 SpecConstantComposite
  {IR(49372, 36), 821}, // 651 SpecConstantCompositeContinuedINTEL
  {IR(35464, 34), 394}, // 652 SpecConstantCompositeReplicateEXT
  {IR(29269, 18), 44}, // 653 SpecConstantFalse
  {IR(29363, 15), 47}, // 654 SpecConstantOp
  {IR(36408, 23), 433}, // 655 SpecConstantStringAMDX
  {IR(50104, 24), 845}, // 656 SpecConstantTargetINTEL
  {IR(29252, 17), 43}, // 657 SpecConstantTrue
  {IR(34386, 25), 346}, // 658 StencilAttachmentReadEXT
  {IR(29527, 6), 55}, // 659 Store
  {IR(28308, 7), 7}, // 660 String
  {IR(49793, 25), 834}, // 661 Subgroup2DBlockLoadINTEL
  {IR(49818, 34), 835}, // 662 Subgroup2DBlockLoadTransformINTEL
  {IR(49852, 34), 836}, // 663 Subgroup2DBlockLoadTransposeINTEL
  {IR(49886, 29), 837}, // 664 Subgroup2DBlockPrefetchINTEL
  {IR(49915, 26), 838}, // 665 Subgroup2DBlockStoreINTEL
  {IR(34884, 20), 372}, // 666 SubgroupAllEqualKHR
  {IR(34854, 15), 370}, // 667 SubgroupAllKHR
  {IR(34869, 15), 371}, // 668 SubgroupAnyKHR
  {IR(45011, 30), 701}, // 669 SubgroupAvcBmeInitializeINTEL
  {IR(44981, 30), 700}, // 670 SubgroupAvcFmeInitializeINTEL
  {IR(43416, 35), 670}, // 671 SubgroupAvcImeAdjustRefOffsetINTEL
  {IR(43451, 39), 671}, // 672 SubgroupAvcImeConvertToMcePayloadINTEL
  {IR(44092, 38), 684}, // 673 SubgroupAvcImeConvertToMceResultINTEL
  {IR(43715, 45), 677}, // 674 SubgroupAvcImeEvaluateWithDualReferenceINTEL
  {IR(43815, 53), 679}, // 675 SubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL
  {IR(44036, 56), 683}, // 676 SubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL
  {IR(43924, 54), 681}, // 677 SubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL
  {IR(43668, 47), 676}, // 678 SubgroupAvcImeEvaluateWithSingleReferenceINTEL
  {IR(43760, 55), 678}, // 679 SubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL
  {IR(43978, 58), 682}, // 680 SubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL
  {IR(43868, 56), 680}, // 681 SubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL
  {IR(44724, 36), 695}, // 682 SubgroupAvcImeGetBorderReachedINTEL
  {IR(44176, 44), 686}, // 683 SubgroupAvcImeGetDualReferenceStreaminINTEL
  {IR(44130, 46), 685}, // 684 SubgroupAvcImeGetSingleReferenceStreaminINTEL
  {IR(44591, 66), 693}, // 685 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL
  {IR(44523, 68), 692}, // 686 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL
  {IR(44657, 67), 694}, // 687 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL
  {IR(44386, 68), 690}, // 688 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL
  {IR(44316, 70), 689}, // 689 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL
  {IR(44454, 69), 691}, // 690 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL
  {IR(44760, 48), 696}, // 691 SubgroupAvcImeGetTruncatedSearchIndicationINTEL
  {IR(44808, 59), 697}, // 692 SubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL
  {IR(44925, 56), 699}, // 693 SubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL
  {IR(44867, 58), 698}, // 694 SubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL
  {IR(43279, 30), 666}, // 695 SubgroupAvcImeInitializeINTEL
  {IR(43383, 33), 669}, // 696 SubgroupAvcImeRefWindowSizeINTEL
  {IR(43347, 36), 668}, // 697 SubgroupAvcImeSetDualReferenceINTEL
  {IR(43580, 54), 674}, // 698 SubgroupAvcImeSetEarlySearchTerminationThresholdINTEL
  {IR(43490, 43), 672}, // 699 SubgroupAvcImeSetMaxMotionVectorCountINTEL
  {IR(43309, 38), 667}, // 700 SubgroupAvcImeSetSingleReferenceINTEL
  {IR(43533, 47), 673}, // 701 SubgroupAvcImeSetUnidirectionalMixDisableINTEL
  {IR(43634, 34), 675}, // 702 SubgroupAvcImeSetWeightedSadINTEL
  {IR(44269, 47), 688}, // 703 SubgroupAvcImeStripDualReferenceStreamoutINTEL
  {IR(44220, 49), 687}, // 704 SubgroupAvcImeStripSingleReferenceStreamoutINTEL
  {IR(42669, 39), 651}, // 705 SubgroupAvcMceConvertToImePayloadINTEL
  {IR(42708, 38), 652}, // 706 SubgroupAvcMceConvertToImeResultINTEL
  {IR(42746, 39), 653}, // 707 SubgroupAvcMceConvertToRefPayloadINTEL
  {IR(42785, 38), 654}, // 708 SubgroupAvcMceConvertToRefResultINTEL
  {IR(42823, 39), 655}, // 709 SubgroupAvcMceConvertToSicPayloadINTEL
  {IR(42862, 38), 656}, // 710 SubgroupAvcMceConvertToSicResultINTEL
  {IR(42975, 43), 659}, // 711 SubgroupAvcMceGetBestInterDistortionsINTEL
  {IR(42107, 50), 640}, // 712 SubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL
  {IR(41705, 60), 632}, // 713 SubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL
  {IR(41905, 51), 636}, // 714 SubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL
  {IR(42051, 56), 639}, // 715 SubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL
  {IR(41818, 47), 634}, // 716 SubgroupAvcMceGetDefaultInterShapePenaltyINTEL
  {IR(42406, 56), 646}, // 717 SubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL
  {IR(42305, 50), 644}, // 718 SubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL
  {IR(42000, 51), 638}, // 719 SubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL
  {IR(42209, 49), 642}, // 720 SubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL
  {IR(42157, 52), 641}, // 721 SubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL
  {IR(42355, 51), 645}, // 722 SubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL
  {IR(43094, 38), 662}, // 723 SubgroupAvcMceGetInterDirectionsINTEL
  {IR(42936, 39), 658}, // 724 SubgroupAvcMceGetInterDistortionsINTEL
  {IR(43018, 38), 660}, // 725 SubgroupAvcMceGetInterMajorShapeINTEL
  {IR(43056, 38), 661}, // 726 SubgroupAvcMceGetInterMinorShapeINTEL
  {IR(43132, 45), 663}, // 727 SubgroupAvcMceGetInterMotionVectorCountINTEL
  {IR(43177, 40), 664}, // 728 SubgroupAvcMceGetInterReferenceIdsINTEL
  {IR(43217, 62), 665}, // 729 SubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL
  {IR(42900, 36), 657}, // 730 SubgroupAvcMceGetMotionVectorsINTEL
  {IR(42462, 33), 647}, // 731 SubgroupAvcMceSetAcOnlyHaarINTEL
  {IR(42608, 61), 650}, // 732 SubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL
  {IR(41765, 53), 633}, // 733 SubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL
  {IR(41956, 44), 637}, // 734 SubgroupAvcMceSetInterDirectionPenaltyINTEL
  {IR(41865, 40), 635}, // 735 SubgroupAvcMceSetInterShapePenaltyINTEL
  {IR(42258, 47), 643}, // 736 SubgroupAvcMceSetMotionVectorCostFunctionINTEL
  {IR(42547, 61), 649}, // 737 SubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL
  {IR(42495, 52), 648}, // 738 SubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL
  {IR(45041, 39), 702}, // 739 SubgroupAvcRefConvertToMcePayloadINTEL
  {IR(45363, 38), 709}, // 740 SubgroupAvcRefConvertToMceResultINTEL
  {IR(45216, 45), 706}, // 741 SubgroupAvcRefEvaluateWithDualReferenceINTEL
  {IR(45261, 46), 707}, // 742 SubgroupAvcRefEvaluateWithMultiReferenceINTEL
  {IR(45307, 56), 708}, // 743 SubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL
  {IR(45169, 47), 705}, // 744 SubgroupAvcRefEvaluateWithSingleReferenceINTEL
  {IR(45080, 46), 703}, // 745 SubgroupAvcRefSetBidirectionalMixDisableINTEL
  {IR(45126, 43), 704}, // 746 SubgroupAvcRefSetBilinearFilterEnableINTEL
  {IR(45499, 42), 713}, // 747 SubgroupAvcSicConfigureIpeLumaChromaINTEL
  {IR(45463, 36), 712}, // 748 SubgroupAvcSicConfigureIpeLumaINTEL
  {IR(45431, 32), 711}, // 749 SubgroupAvcSicConfigureSkcINTEL
  {IR(45580, 39), 715}, // 750 SubgroupAvcSicConvertToMcePayloadINTEL
  {IR(46120, 38), 727}, // 751 SubgroupAvcSicConvertToMceResultINTEL
  {IR(45895, 31), 722}, // 752 SubgroupAvcSicEvaluateIpeINTEL
  {IR(45973, 45), 724}, // 753 SubgroupAvcSicEvaluateWithDualReferenceINTEL
  {IR(46018, 46), 725}, // 754 SubgroupAvcSicEvaluateWithMultiReferenceINTEL
  {IR(46064, 56), 726}, // 755 SubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL
  {IR(45926, 47), 723}, // 756 SubgroupAvcSicEvaluateWithSingleReferenceINTEL
  {IR(46237, 46), 730}, // 757 SubgroupAvcSicGetBestIpeChromaDistortionINTEL
  {IR(46193, 44), 729}, // 758 SubgroupAvcSicGetBestIpeLumaDistortionINTEL
  {IR(46458, 35), 735}, // 759 SubgroupAvcSicGetInterRawSadsINTEL
  {IR(46324, 36), 732}, // 760 SubgroupAvcSicGetIpeChromaModeINTEL
  {IR(46158, 35), 728}, // 761 SubgroupAvcSicGetIpeLumaShapeINTEL
  {IR(45541, 39), 714}, // 762 SubgroupAvcSicGetMotionVectorMaskINTEL
  {IR(46283, 41), 731}, // 763 SubgroupAvcSicGetPackedIpeLumaModesINTEL
  {IR(46360, 50), 733}, // 764 SubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL
  {IR(46410, 48), 734}, // 765 SubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL
  {IR(45401, 30), 710}, // 766 SubgroupAvcSicInitializeINTEL
  {IR(45761, 43), 719}, // 767 SubgroupAvcSicSetBilinearFilterEnableINTEL
  {IR(45852, 43), 721}, // 768 SubgroupAvcSicSetBlockBasedRawSkipSadINTEL
  {IR(45711, 50), 718}, // 769 SubgroupAvcSicSetIntraChromaModeCostFunctionINTEL
  {IR(45663, 48), 717}, // 770 SubgroupAvcSicSetIntraLumaModeCostFunctionINTEL
  {IR(45619, 44), 716}, // 771 SubgroupAvcSicSetIntraLumaShapePenaltyINTEL
  {IR(45804, 48), 720}, // 772 SubgroupAvcSicSetSkcForwardTransformEnableINTEL
  {IR(6244, 18), 363}, // 773 SubgroupBallotKHR
  {IR(49766, 27), 833}, // 774 SubgroupBlockPrefetchINTEL
  {IR(40711, 23), 587}, // 775 SubgroupBlockReadINTEL
  {IR(40734, 24), 588}, // 776 SubgroupBlockWriteINTEL
  {IR(34721, 27), 364}, // 777 SubgroupFirstInvocationKHR
  {IR(40758, 28), 589}, // 778 SubgroupImageBlockReadINTEL
  {IR(40786, 29), 590}, // 779 SubgroupImageBlockWriteINTEL
  {IR(40815, 33), 591}, // 780 SubgroupImageMediaBlockReadINTEL
  {IR(40848, 34), 592}, // 781 SubgroupImageMediaBlockWriteINTEL
  {IR(15350, 38), 839}, // 782 SubgroupMatrixMultiplyAccumulateINTEL
  {IR(34904, 26), 374}, // 783 SubgroupReadInvocationKHR
  {IR(40639, 25), 584}, // 784 SubgroupShuffleDownINTEL
  {IR(13006, 21), 583}, // 785 SubgroupShuffleINTEL
  {IR(40664, 23), 585}, // 786 SubgroupShuffleUpINTEL
  {IR(40687, 24), 586}, // 787 SubgroupShuffleXorINTEL
  {IR(32078, 7), 229}, // 788 Switch
  {IR(49580, 24), 829}, // 789 TaskSequenceAsyncALTERA
  {IR(49604, 23), 829}, // 790 TaskSequenceAsyncINTEL
  {IR(49531, 25), 828}, // 791 TaskSequenceCreateALTERA
  {IR(49556, 24), 828}, // 792 TaskSequenceCreateINTEL
  {IR(49627, 22), 830}, // 793 TaskSequenceGetALTERA
  {IR(49649, 21), 830}, // 794 TaskSequenceGetINTEL
  {IR(49670, 26), 831}, // 795 TaskSequenceReleaseALTERA
  {IR(49696, 25), 831}, // 796 TaskSequenceReleaseINTEL
  {IR(39982, 27), 560}, // 797 TensorLayoutSetBlockSizeNV
  {IR(39846, 28), 553}, // 798 TensorLayoutSetClampValueNV
  {IR(39775, 27), 550}, // 799 TensorLayoutSetDimensionNV
  {IR(39802, 24), 551}, // 800 TensorLayoutSetStrideNV
  {IR(39826, 20), 552}, // 801 TensorLayoutSliceNV
  {IR(34496, 19), 350}, // 802 TensorQuerySizeARM
  {IR(34467, 14), 348}, // 803 TensorReadARM
  {IR(39962, 20), 559}, // 804 TensorViewSetClipNV
  {IR(39893, 25), 555}, // 805 TensorViewSetDimensionNV
  {IR(39918, 22), 556}, // 806 TensorViewSetStrideNV
  {IR(34481, 15), 349}, // 807 TensorWriteARM
  {IR(34608, 20), 358}, // 808 TerminateInvocation
  {IR(35069, 16), 381}, // 809 TerminateRayKHR
  {IR(38876, 15), 521}, // 810 TerminateRayNV
  {IR(38899, 14), 523}, // 811 TraceMotionNV
  {IR(38891, 8), 522}, // 812 TraceNV
  {IR(34981, 12), 377}, // 813 TraceRayKHR
  {IR(38913, 17), 524}, // 814 TraceRayMotionNV
  {IR(29930, 10), 76}, // 815 Transpose
  {IR(38980, 29), 526}, // 816 TypeAccelerationStructureKHR
  {IR(39009, 28), 526}, // 817 TypeAccelerationStructureNV
  {IR(28879, 10), 25}, // 818 TypeArray
  {IR(41624, 37), 629}, // 819 TypeAvcImeDualReferenceStreaminINTEL
  {IR(41359, 23), 620}, // 820 TypeAvcImePayloadINTEL
  {IR(41541, 44), 627}, // 821 TypeAvcImeResultDualReferenceStreamoutINTEL
  {IR(41473, 22), 625}, // 822 TypeAvcImeResultINTEL
  {IR(41495, 46), 626}, // 823 TypeAvcImeResultSingleReferenceStreamoutINTEL
  {IR(41585, 39), 628}, // 824 TypeAvcImeSingleReferenceStreaminINTEL
  {IR(41428, 23), 623}, // 825 TypeAvcMcePayloadINTEL
  {IR(41451, 22), 624}, // 826 TypeAvcMceResultINTEL
  {IR(41382, 23), 621}, // 827 TypeAvcRefPayloadINTEL
  {IR(41661, 22), 630}, // 828 TypeAvcRefResultINTEL
  {IR(41405, 23), 622}, // 829 TypeAvcSicPayloadINTEL
  {IR(41683, 22), 631}, // 830 TypeAvcSicResultINTEL
  {IR(28641, 9), 17}, // 831 TypeBool
  {IR(36483, 14), 436}, // 832 TypeBufferEXT
  {IR(49292, 23), 818}, // 833 TypeBufferSurfaceINTEL
  {IR(35250, 25), 388}, // 834 TypeCooperativeMatrixKHR
  {IR(39302, 24), 536}, // 835 TypeCooperativeMatrixNV
  {IR(37496, 24), 475}, // 836 TypeCooperativeVectorNV
  {IR(28994, 16), 32}, // 837 TypeDeviceEvent
  {IR(28984, 10), 31}, // 838 TypeEvent
  {IR(28695, 10), 19}, // 839 TypeFloat
  {IR(29043, 19), 36}, // 840 TypeForwardPointer
  {IR(28971, 13), 30}, // 841 TypeFunction
  {IR(34595, 13), 357}, // 842 TypeGraphARM
  {IR(38237, 17), 498}, // 843 TypeHitObjectEXT
  {IR(37441, 16), 473}, // 844 TypeHitObjectNV
  {IR(28840, 10), 22}, // 845 TypeImage
  {IR(28650, 8), 18}, // 846 TypeInt
  {IR(28716, 11), 21}, // 847 TypeMatrix
  {IR(33425, 17), 300}, // 848 TypeNamedBarrier
  {IR(36285, 25), 428}, // 849 TypeNodePayloadArrayAMDX
  {IR(28917, 11), 28}, // 850 TypeOpaque
  {IR(29034, 9), 35}, // 851 TypePipe
  {IR(33303, 16), 295}, // 852 TypePipeStorage
  {IR(28959, 12), 29}, // 853 TypePointer
  {IR(29024, 10), 34}, // 854 TypeQueue
  {IR(35529, 16), 396}, // 855 TypeRayQueryKHR
  {IR(29010, 14), 33}, // 856 TypeReserveId
  {IR(28889, 17), 26}, // 857 TypeRuntimeArray
  {IR(28862, 17), 24}, // 858 TypeSampledImage
  {IR(28850, 12), 23}, // 859 TypeSampler
  {IR(28906, 11), 27}, // 860 TypeStruct
  {IR(49315, 25), 819}, // 861 TypeStructContinuedINTEL
  {IR(49721, 23), 832}, // 862 TypeTaskSequenceALTERA
  {IR(49744, 22), 832}, // 863 TypeTaskSequenceINTEL
  {IR(34411, 14), 347}, // 864 TypeTensorARM
  {IR(39718, 19), 547}, // 865 TypeTensorLayoutNV
  {IR(39737, 17), 548}, // 866 TypeTensorViewNV
  {IR(34628, 22), 359}, // 867 TypeUntypedPointerKHR
  {IR(28705, 11), 20}, // 868 TypeVector
  {IR(37480, 16), 475}, // 869 TypeVectorIdEXT
  {IR(41341, 18), 619}, // 870 TypeVmeImageINTEL
  {IR(28632, 9), 16}, // 871 TypeVoid
  {IR(40970, 13), 598}, // 872 UAddSatINTEL
  {IR(40997, 14), 600}, // 873 UAverageINTEL
  {IR(41032, 21), 602}, // 874 UAverageRoundedINTEL
  {IR(30447, 9), 103}, // 875 UConvert
  {IR(40882, 24), 593}, // 876 UCountLeadingZerosINTEL
  {IR(40906, 25), 594}, // 877 UCountTrailingZerosINTEL
  {IR(30659, 5), 123}, // 878 UDiv
  {IR(35145, 5), 383}, // 879 UDot
  {IR(35198, 11), 386}, // 880 UDotAccSat
  {IR(35209, 14), 386}, // 881 UDotAccSatKHR
  {IR(35150, 8), 383}, // 882 UDotKHR
  {IR(31019, 13), 160}, // 883 UGreaterThan
  {IR(31045, 18), 162}, // 884 UGreaterThanEqual
  {IR(31081, 10), 164}, // 885 ULessThan
  {IR(31101, 15), 166}, // 886 ULessThanEqual
  {IR(30674, 5), 126}, // 887 UMod
  {IR(41094, 15), 606}, // 888 UMul32x16INTEL
  {IR(30827, 13), 140}, // 889 UMulExtended
  {IR(41066, 13), 604}, // 890 USubSatINTEL
  {IR(28144, 6), 1}, // 891 Undef
  {IR(30924, 10), 151}, // 892 Unordered
  {IR(32109, 12), 233}, // 893 Unreachable
  {IR(34669, 22), 361}, // 894 UntypedAccessChainKHR
  {IR(34806, 22), 367}, // 895 UntypedArrayLengthKHR
  {IR(34956, 25), 376}, // 896 UntypedGroupAsyncCopyKHR
  {IR(36514, 28), 438}, // 897 UntypedImageTexelPointerEXT
  {IR(34691, 30), 362}, // 898 UntypedInBoundsAccessChainKHR
  {IR(34773, 33), 366}, // 899 UntypedInBoundsPtrAccessChainKHR
  {IR(34828, 19), 368}, // 900 UntypedPrefetchKHR
  {IR(34748, 25), 365}, // 901 UntypedPtrAccessChainKHR
  {IR(34650, 19), 360}, // 902 UntypedVariableKHR
  {IR(15416, 32), 841}, // 903 UntypedVariableLengthArrayINTEL
  {IR(29455, 9), 52}, // 904 Variable
  {IR(13462, 25), 736}, // 905 VariableLengthArrayINTEL
  {IR(29812, 21), 69}, // 906 VectorExtractDynamic
  {IR(29833, 20), 70}, // 907 VectorInsertDynamic
  {IR(29853, 14), 71}, // 908 VectorShuffle
  {IR(30735, 18), 133}, // 909 VectorTimesMatrix
  {IR(30699, 18), 131}, // 910 VectorTimesScalar
  {IR(41327, 14), 618}, // 911 VmeImageINTEL
  {IR(37779, 33), 484}, // 912 WritePackedPrimitiveIndices4x8NV
  {IR(32334, 10), 250}, // 913 WritePipe
  {IR(48580, 24), 798}, // 914 WritePipeBlockingALTERA
  {IR(48604, 23), 798}, // 915 WritePipeBlockingINTEL
}};

// Extended instruction descriptions, ordered by (extinst enum, opcode value).
// The fields in order are:
//   enum value
//   operands, an IndexRange into kOperandSpans
//   name, a character-counting IndexRange into kStrings
//   capabilities, an IndexRange into kCapabilitySpans
static const std::array<ExtInstDesc, 425> kExtInstByValue{{
    {0,IR(0, 0),IR(50532, 14),IR(1, 0)}, // DebugInfoNone in debuginfo
    {1,IR(52, 3),IR(50546, 21),IR(1, 0)}, // DebugCompilationUnit in debuginfo
    {2,IR(803, 3),IR(50619, 15),IR(1, 0)}, // DebugTypeBasic in debuginfo
    {3,IR(806, 3),IR(50668, 17),IR(1, 0)}, // DebugTypePointer in debuginfo
    {4,IR(809, 2),IR(50723, 19),IR(1, 0)}, // DebugTypeQualifier in debuginfo
    {5,IR(168, 2),IR(50742, 15),IR(1, 0)}, // DebugTypeArray in debuginfo
    {6,IR(261, 2),IR(50757, 16),IR(1, 0)}, // DebugTypeVector in debuginfo
    {7,IR(811, 6),IR(50773, 13),IR(1, 0)}, // DebugTypedef in debuginfo
    {8,IR(168, 2),IR(50786, 18),IR(1, 0)}, // DebugTypeFunction in debuginfo
    {9,IR(817, 9),IR(50804, 14),IR(1, 0)}, // DebugTypeEnum in debuginfo
    {10,IR(826, 9),IR(50856, 19),IR(1, 0)}, // DebugTypeComposite in debuginfo
    {11,IR(835, 10),IR(50875, 16),IR(1, 0)}, // DebugTypeMember in debuginfo
    {12,IR(845, 5),IR(50891, 21),IR(1, 0)}, // DebugTypeInheritance in debuginfo
    {13,IR(36, 2),IR(50912, 21),IR(1, 0)}, // DebugTypePtrToMember in debuginfo
    {14,IR(168, 2),IR(50933, 18),IR(1, 0)}, // DebugTypeTemplate in debuginfo
    {15,IR(850, 6),IR(50951, 27),IR(1, 0)}, // DebugTypeTemplateParameter in debuginfo
    {16,IR(856, 5),IR(50978, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in debuginfo
    {17,IR(861, 5),IR(51013, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in debuginfo
    {18,IR(835, 10),IR(51044, 20),IR(1, 0)}, // DebugGlobalVariable in debuginfo
    {19,IR(866, 8),IR(51064, 25),IR(1, 0)}, // DebugFunctionDeclaration in debuginfo
    {20,IR(874, 11),IR(51089, 14),IR(1, 0)}, // DebugFunction in debuginfo
    {21,IR(885, 5),IR(51103, 18),IR(1, 0)}, // DebugLexicalBlock in debuginfo
    {22,IR(890, 3),IR(51121, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in debuginfo
    {23,IR(893, 2),IR(51152, 11),IR(1, 0)}, // DebugScope in debuginfo
    {24,IR(0, 0),IR(51163, 13),IR(1, 0)}, // DebugNoScope in debuginfo
    {25,IR(895, 3),IR(51176, 15),IR(1, 0)}, // DebugInlinedAt in debuginfo
    {26,IR(898, 7),IR(51233, 19),IR(1, 0)}, // DebugLocalVariable in debuginfo
    {27,IR(36, 2),IR(51252, 21),IR(1, 0)}, // DebugInlinedVariable in debuginfo
    {28,IR(33, 3),IR(51273, 13),IR(1, 0)}, // DebugDeclare in debuginfo
    {29,IR(375, 3),IR(51286, 11),IR(1, 0)}, // DebugValue in debuginfo
    {30,IR(905, 2),IR(51330, 15),IR(1, 0)}, // DebugOperation in debuginfo
    {31,IR(739, 1),IR(51345, 16),IR(1, 0)}, // DebugExpression in debuginfo
    {32,IR(907, 4),IR(51361, 14),IR(1, 0)}, // DebugMacroDef in debuginfo
    {33,IR(890, 3),IR(51375, 16),IR(1, 0)}, // DebugMacroUndef in debuginfo
    {1,IR(10, 1),IR(51391, 6),IR(1, 0)}, // Round in glsl_std_450
    {2,IR(10, 1),IR(51397, 10),IR(1, 0)}, // RoundEven in glsl_std_450
    {3,IR(10, 1),IR(51407, 6),IR(1, 0)}, // Trunc in glsl_std_450
    {4,IR(10, 1),IR(51413, 5),IR(1, 0)}, // FAbs in glsl_std_450
    {5,IR(10, 1),IR(51418, 5),IR(1, 0)}, // SAbs in glsl_std_450
    {6,IR(10, 1),IR(51423, 6),IR(1, 0)}, // FSign in glsl_std_450
    {7,IR(10, 1),IR(51429, 6),IR(1, 0)}, // SSign in glsl_std_450
    {8,IR(10, 1),IR(51435, 6),IR(1, 0)}, // Floor in glsl_std_450
    {9,IR(10, 1),IR(51441, 5),IR(1, 0)}, // Ceil in glsl_std_450
    {10,IR(10, 1),IR(51446, 6),IR(1, 0)}, // Fract in glsl_std_450
    {11,IR(10, 1),IR(51452, 8),IR(1, 0)}, // Radians in glsl_std_450
    {12,IR(10, 1),IR(51460, 8),IR(1, 0)}, // Degrees in glsl_std_450
    {13,IR(10, 1),IR(51468, 4),IR(1, 0)}, // Sin in glsl_std_450
    {14,IR(10, 1),IR(51472, 4),IR(1, 0)}, // Cos in glsl_std_450
    {15,IR(10, 1),IR(51476, 4),IR(1, 0)}, // Tan in glsl_std_450
    {16,IR(10, 1),IR(51480, 5),IR(1, 0)}, // Asin in glsl_std_450
    {17,IR(10, 1),IR(51485, 5),IR(1, 0)}, // Acos in glsl_std_450
    {18,IR(10, 1),IR(51490, 5),IR(1, 0)}, // Atan in glsl_std_450
    {19,IR(10, 1),IR(51495, 5),IR(1, 0)}, // Sinh in glsl_std_450
    {20,IR(10, 1),IR(51500, 5),IR(1, 0)}, // Cosh in glsl_std_450
    {21,IR(10, 1),IR(51505, 5),IR(1, 0)}, // Tanh in glsl_std_450
    {22,IR(10, 1),IR(51510, 6),IR(1, 0)}, // Asinh in glsl_std_450
    {23,IR(10, 1),IR(51516, 6),IR(1, 0)}, // Acosh in glsl_std_450
    {24,IR(10, 1),IR(51522, 6),IR(1, 0)}, // Atanh in glsl_std_450
    {25,IR(36, 2),IR(51528, 6),IR(1, 0)}, // Atan2 in glsl_std_450
    {26,IR(36, 2),IR(51534, 4),IR(1, 0)}, // Pow in glsl_std_450
    {27,IR(10, 1),IR(51538, 4),IR(1, 0)}, // Exp in glsl_std_450
    {28,IR(10, 1),IR(51542, 4),IR(1, 0)}, // Log in glsl_std_450
    {29,IR(10, 1),IR(51546, 5),IR(1, 0)}, // Exp2 in glsl_std_450
    {30,IR(10, 1),IR(51551, 5),IR(1, 0)}, // Log2 in glsl_std_450
    {31,IR(10, 1),IR(51556, 5),IR(1, 0)}, // Sqrt in glsl_std_450
    {32,IR(10, 1),IR(51561, 12),IR(1, 0)}, // InverseSqrt in glsl_std_450
    {33,IR(10, 1),IR(51573, 12),IR(1, 0)}, // Determinant in glsl_std_450
    {34,IR(10, 1),IR(51585, 14),IR(1, 0)}, // MatrixInverse in glsl_std_450
    {35,IR(36, 2),IR(51599, 5),IR(1, 0)}, // Modf in glsl_std_450
    {36,IR(10, 1),IR(51604, 11),IR(1, 0)}, // ModfStruct in glsl_std_450
    {37,IR(36, 2),IR(51615, 5),IR(1, 0)}, // FMin in glsl_std_450
    {38,IR(36, 2),IR(51620, 5),IR(1, 0)}, // UMin in glsl_std_450
    {39,IR(36, 2),IR(51625, 5),IR(1, 0)}, // SMin in glsl_std_450
    {40,IR(36, 2),IR(51630, 5),IR(1, 0)}, // FMax in glsl_std_450
    {41,IR(36, 2),IR(51635, 5),IR(1, 0)}, // UMax in glsl_std_450
    {42,IR(36, 2),IR(51640, 5),IR(1, 0)}, // SMax in glsl_std_450
    {43,IR(33, 3),IR(51645, 7),IR(1, 0)}, // FClamp in glsl_std_450
    {44,IR(33, 3),IR(51652, 7),IR(1, 0)}, // UClamp in glsl_std_450
    {45,IR(33, 3),IR(51659, 7),IR(1, 0)}, // SClamp in glsl_std_450
    {46,IR(33, 3),IR(51666, 5),IR(1, 0)}, // FMix in glsl_std_450
    {47,IR(33, 3),IR(51671, 5),IR(1, 0)}, // IMix in glsl_std_450
    {48,IR(36, 2),IR(51676, 5),IR(1, 0)}, // Step in glsl_std_450
    {49,IR(33, 3),IR(51681, 11),IR(1, 0)}, // SmoothStep in glsl_std_450
    {50,IR(33, 3),IR(51692, 4),IR(1, 0)}, // Fma in glsl_std_450
    {51,IR(36, 2),IR(51696, 6),IR(1, 0)}, // Frexp in glsl_std_450
    {52,IR(10, 1),IR(51702, 12),IR(1, 0)}, // FrexpStruct in glsl_std_450
    {53,IR(36, 2),IR(51714, 6),IR(1, 0)}, // Ldexp in glsl_std_450
    {54,IR(10, 1),IR(51720, 13),IR(1, 0)}, // PackSnorm4x8 in glsl_std_450
    {55,IR(10, 1),IR(51733, 13),IR(1, 0)}, // PackUnorm4x8 in glsl_std_450
    {56,IR(10, 1),IR(51746, 14),IR(1, 0)}, // PackSnorm2x16 in glsl_std_450
    {57,IR(10, 1),IR(51760, 14),IR(1, 0)}, // PackUnorm2x16 in glsl_std_450
    {58,IR(10, 1),IR(51774, 13),IR(1, 0)}, // PackHalf2x16 in glsl_std_450
    {59,IR(10, 1),IR(51787, 15),IR(319, 1)}, // PackDouble2x32 in glsl_std_450
    {60,IR(10, 1),IR(51802, 16),IR(1, 0)}, // UnpackSnorm2x16 in glsl_std_450
    {61,IR(10, 1),IR(51818, 16),IR(1, 0)}, // UnpackUnorm2x16 in glsl_std_450
    {62,IR(10, 1),IR(51834, 15),IR(1, 0)}, // UnpackHalf2x16 in glsl_std_450
    {63,IR(10, 1),IR(51849, 15),IR(1, 0)}, // UnpackSnorm4x8 in glsl_std_450
    {64,IR(10, 1),IR(51864, 15),IR(1, 0)}, // UnpackUnorm4x8 in glsl_std_450
    {65,IR(10, 1),IR(51879, 17),IR(319, 1)}, // UnpackDouble2x32 in glsl_std_450
    {66,IR(10, 1),IR(51896, 7),IR(1, 0)}, // Length in glsl_std_450
    {67,IR(36, 2),IR(51903, 9),IR(1, 0)}, // Distance in glsl_std_450
    {68,IR(36, 2),IR(51912, 6),IR(1, 0)}, // Cross in glsl_std_450
    {69,IR(10, 1),IR(51918, 10),IR(1, 0)}, // Normalize in glsl_std_450
    {70,IR(33, 3),IR(51928, 12),IR(1, 0)}, // FaceForward in glsl_std_450
    {71,IR(36, 2),IR(51940, 8),IR(1, 0)}, // Reflect in glsl_std_450
    {72,IR(33, 3),IR(51948, 8),IR(1, 0)}, // Refract in glsl_std_450
    {73,IR(10, 1),IR(51956, 9),IR(1, 0)}, // FindILsb in glsl_std_450
    {74,IR(10, 1),IR(51965, 9),IR(1, 0)}, // FindSMsb in glsl_std_450
    {75,IR(10, 1),IR(51974, 9),IR(1, 0)}, // FindUMsb in glsl_std_450
    {76,IR(10, 1),IR(51983, 22),IR(320, 1)}, // InterpolateAtCentroid in glsl_std_450
    {77,IR(36, 2),IR(52005, 20),IR(320, 1)}, // InterpolateAtSample in glsl_std_450
    {78,IR(36, 2),IR(52025, 20),IR(320, 1)}, // InterpolateAtOffset in glsl_std_450
    {79,IR(36, 2),IR(52045, 5),IR(1, 0)}, // NMin in glsl_std_450
    {80,IR(36, 2),IR(52050, 5),IR(1, 0)}, // NMax in glsl_std_450
    {81,IR(33, 3),IR(52055, 7),IR(1, 0)}, // NClamp in glsl_std_450
    {1,IR(399, 5),IR(5463, 7),IR(1, 0)}, // Kernel in nonsemantic_clspvreflection
    {2,IR(911, 5),IR(52062, 13),IR(1, 0)}, // ArgumentInfo in nonsemantic_clspvreflection
    {3,IR(916, 5),IR(52075, 22),IR(1, 0)}, // ArgumentStorageBuffer in nonsemantic_clspvreflection
    {4,IR(916, 5),IR(52097, 16),IR(1, 0)}, // ArgumentUniform in nonsemantic_clspvreflection
    {5,IR(554, 7),IR(52113, 25),IR(1, 0)}, // ArgumentPodStorageBuffer in nonsemantic_clspvreflection
    {6,IR(554, 7),IR(52138, 19),IR(1, 0)}, // ArgumentPodUniform in nonsemantic_clspvreflection
    {7,IR(916, 5),IR(52157, 24),IR(1, 0)}, // ArgumentPodPushConstant in nonsemantic_clspvreflection
    {8,IR(916, 5),IR(52181, 21),IR(1, 0)}, // ArgumentSampledImage in nonsemantic_clspvreflection
    {9,IR(916, 5),IR(52202, 21),IR(1, 0)}, // ArgumentStorageImage in nonsemantic_clspvreflection
    {10,IR(916, 5),IR(52223, 16),IR(1, 0)}, // ArgumentSampler in nonsemantic_clspvreflection
    {11,IR(916, 5),IR(52239, 18),IR(1, 0)}, // ArgumentWorkgroup in nonsemantic_clspvreflection
    {12,IR(33, 3),IR(52257, 26),IR(1, 0)}, // SpecConstantWorkgroupSize in nonsemantic_clspvreflection
    {13,IR(33, 3),IR(52283, 25),IR(1, 0)}, // SpecConstantGlobalOffset in nonsemantic_clspvreflection
    {14,IR(10, 1),IR(52308, 20),IR(1, 0)}, // SpecConstantWorkDim in nonsemantic_clspvreflection
    {15,IR(36, 2),IR(52328, 25),IR(1, 0)}, // PushConstantGlobalOffset in nonsemantic_clspvreflection
    {16,IR(36, 2),IR(52353, 30),IR(1, 0)}, // PushConstantEnqueuedLocalSize in nonsemantic_clspvreflection
    {17,IR(36, 2),IR(52383, 23),IR(1, 0)}, // PushConstantGlobalSize in nonsemantic_clspvreflection
    {18,IR(36, 2),IR(52406, 25),IR(1, 0)}, // PushConstantRegionOffset in nonsemantic_clspvreflection
    {19,IR(36, 2),IR(52431, 26),IR(1, 0)}, // PushConstantNumWorkgroups in nonsemantic_clspvreflection
    {20,IR(36, 2),IR(52457, 30),IR(1, 0)}, // PushConstantRegionGroupOffset in nonsemantic_clspvreflection
    {21,IR(33, 3),IR(52487, 26),IR(1, 0)}, // ConstantDataStorageBuffer in nonsemantic_clspvreflection
    {22,IR(33, 3),IR(52513, 20),IR(1, 0)}, // ConstantDataUniform in nonsemantic_clspvreflection
    {23,IR(33, 3),IR(8937, 15),IR(1, 0)}, // LiteralSampler in nonsemantic_clspvreflection
    {24,IR(296, 4),IR(52533, 30),IR(1, 0)}, // PropertyRequiredWorkgroupSize in nonsemantic_clspvreflection
    {25,IR(10, 1),IR(52563, 28),IR(1, 0)}, // SpecConstantSubgroupMaxSize in nonsemantic_clspvreflection
    {26,IR(916, 5),IR(52591, 28),IR(1, 0)}, // ArgumentPointerPushConstant in nonsemantic_clspvreflection
    {27,IR(554, 7),IR(52619, 23),IR(1, 0)}, // ArgumentPointerUniform in nonsemantic_clspvreflection
    {28,IR(33, 3),IR(52642, 35),IR(1, 0)}, // ProgramScopeVariablesStorageBuffer in nonsemantic_clspvreflection
    {29,IR(33, 3),IR(52677, 38),IR(1, 0)}, // ProgramScopeVariablePointerRelocation in nonsemantic_clspvreflection
    {30,IR(296, 4),IR(52715, 42),IR(1, 0)}, // ImageArgumentInfoChannelOrderPushConstant in nonsemantic_clspvreflection
    {31,IR(296, 4),IR(52757, 45),IR(1, 0)}, // ImageArgumentInfoChannelDataTypePushConstant in nonsemantic_clspvreflection
    {32,IR(525, 6),IR(52802, 37),IR(1, 0)}, // ImageArgumentInfoChannelOrderUniform in nonsemantic_clspvreflection
    {33,IR(525, 6),IR(52839, 40),IR(1, 0)}, // ImageArgumentInfoChannelDataTypeUniform in nonsemantic_clspvreflection
    {34,IR(916, 5),IR(52879, 27),IR(1, 0)}, // ArgumentStorageTexelBuffer in nonsemantic_clspvreflection
    {35,IR(916, 5),IR(52906, 27),IR(1, 0)}, // ArgumentUniformTexelBuffer in nonsemantic_clspvreflection
    {36,IR(33, 3),IR(52933, 32),IR(1, 0)}, // ConstantDataPointerPushConstant in nonsemantic_clspvreflection
    {37,IR(33, 3),IR(52965, 40),IR(1, 0)}, // ProgramScopeVariablePointerPushConstant in nonsemantic_clspvreflection
    {38,IR(375, 3),IR(53005, 11),IR(1, 0)}, // PrintfInfo in nonsemantic_clspvreflection
    {39,IR(33, 3),IR(53016, 26),IR(1, 0)}, // PrintfBufferStorageBuffer in nonsemantic_clspvreflection
    {40,IR(33, 3),IR(53042, 32),IR(1, 0)}, // PrintfBufferPointerPushConstant in nonsemantic_clspvreflection
    {41,IR(296, 4),IR(53074, 34),IR(1, 0)}, // NormalizedSamplerMaskPushConstant in nonsemantic_clspvreflection
    {42,IR(36, 2),IR(53108, 22),IR(1, 0)}, // WorkgroupVariableSize in nonsemantic_clspvreflection
    {0,IR(0, 0),IR(50532, 14),IR(1, 0)}, // DebugInfoNone in nonsemantic_shader_debuginfo_100
    {1,IR(296, 4),IR(50546, 21),IR(1, 0)}, // DebugCompilationUnit in nonsemantic_shader_debuginfo_100
    {2,IR(296, 4),IR(50619, 15),IR(1, 0)}, // DebugTypeBasic in nonsemantic_shader_debuginfo_100
    {3,IR(33, 3),IR(50668, 17),IR(1, 0)}, // DebugTypePointer in nonsemantic_shader_debuginfo_100
    {4,IR(36, 2),IR(50723, 19),IR(1, 0)}, // DebugTypeQualifier in nonsemantic_shader_debuginfo_100
    {5,IR(168, 2),IR(50742, 15),IR(1, 0)}, // DebugTypeArray in nonsemantic_shader_debuginfo_100
    {6,IR(36, 2),IR(50757, 16),IR(1, 0)}, // DebugTypeVector in nonsemantic_shader_debuginfo_100
    {7,IR(525, 6),IR(50773, 13),IR(1, 0)}, // DebugTypedef in nonsemantic_shader_debuginfo_100
    {8,IR(375, 3),IR(50786, 18),IR(1, 0)}, // DebugTypeFunction in nonsemantic_shader_debuginfo_100
    {9,IR(921, 9),IR(50804, 14),IR(1, 0)}, // DebugTypeEnum in nonsemantic_shader_debuginfo_100
    {10,IR(930, 10),IR(50856, 19),IR(1, 0)}, // DebugTypeComposite in nonsemantic_shader_debuginfo_100
    {11,IR(940, 9),IR(50875, 16),IR(1, 0)}, // DebugTypeMember in nonsemantic_shader_debuginfo_100
    {12,IR(296, 4),IR(50891, 21),IR(1, 0)}, // DebugTypeInheritance in nonsemantic_shader_debuginfo_100
    {13,IR(36, 2),IR(50912, 21),IR(1, 0)}, // DebugTypePtrToMember in nonsemantic_shader_debuginfo_100
    {14,IR(168, 2),IR(50933, 18),IR(1, 0)}, // DebugTypeTemplate in nonsemantic_shader_debuginfo_100
    {15,IR(525, 6),IR(50951, 27),IR(1, 0)}, // DebugTypeTemplateParameter in nonsemantic_shader_debuginfo_100
    {16,IR(667, 5),IR(50978, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in nonsemantic_shader_debuginfo_100
    {17,IR(949, 5),IR(51013, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in nonsemantic_shader_debuginfo_100
    {18,IR(954, 10),IR(51044, 20),IR(1, 0)}, // DebugGlobalVariable in nonsemantic_shader_debuginfo_100
    {19,IR(471, 8),IR(51064, 25),IR(1, 0)}, // DebugFunctionDeclaration in nonsemantic_shader_debuginfo_100
    {20,IR(954, 10),IR(51089, 14),IR(1, 0)}, // DebugFunction in nonsemantic_shader_debuginfo_100
    {21,IR(916, 5),IR(51103, 18),IR(1, 0)}, // DebugLexicalBlock in nonsemantic_shader_debuginfo_100
    {22,IR(33, 3),IR(51121, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in nonsemantic_shader_debuginfo_100
    {23,IR(893, 2),IR(51152, 11),IR(1, 0)}, // DebugScope in nonsemantic_shader_debuginfo_100
    {24,IR(0, 0),IR(51163, 13),IR(1, 0)}, // DebugNoScope in nonsemantic_shader_debuginfo_100
    {25,IR(964, 3),IR(51176, 15),IR(1, 0)}, // DebugInlinedAt in nonsemantic_shader_debuginfo_100
    {26,IR(967, 8),IR(51233, 19),IR(1, 0)}, // DebugLocalVariable in nonsemantic_shader_debuginfo_100
    {27,IR(36, 2),IR(51252, 21),IR(1, 0)}, // DebugInlinedVariable in nonsemantic_shader_debuginfo_100
    {28,IR(975, 4),IR(51273, 13),IR(1, 0)}, // DebugDeclare in nonsemantic_shader_debuginfo_100
    {29,IR(975, 4),IR(51286, 11),IR(1, 0)}, // DebugValue in nonsemantic_shader_debuginfo_100
    {30,IR(168, 2),IR(51330, 15),IR(1, 0)}, // DebugOperation in nonsemantic_shader_debuginfo_100
    {31,IR(739, 1),IR(51345, 16),IR(1, 0)}, // DebugExpression in nonsemantic_shader_debuginfo_100
    {32,IR(577, 4),IR(51361, 14),IR(1, 0)}, // DebugMacroDef in nonsemantic_shader_debuginfo_100
    {33,IR(33, 3),IR(51375, 16),IR(1, 0)}, // DebugMacroUndef in nonsemantic_shader_debuginfo_100
    {34,IR(506, 7),IR(53130, 20),IR(1, 0)}, // DebugImportedEntity in nonsemantic_shader_debuginfo_100
    {35,IR(893, 2),IR(53150, 12),IR(1, 0)}, // DebugSource in nonsemantic_shader_debuginfo_100
    {101,IR(36, 2),IR(53162, 24),IR(1, 0)}, // DebugFunctionDefinition in nonsemantic_shader_debuginfo_100
    {102,IR(10, 1),IR(53186, 21),IR(1, 0)}, // DebugSourceContinued in nonsemantic_shader_debuginfo_100
    {103,IR(667, 5),IR(53207, 10),IR(1, 0)}, // DebugLine in nonsemantic_shader_debuginfo_100
    {104,IR(0, 0),IR(53217, 12),IR(1, 0)}, // DebugNoLine in nonsemantic_shader_debuginfo_100
    {105,IR(36, 2),IR(53229, 21),IR(1, 0)}, // DebugBuildIdentifier in nonsemantic_shader_debuginfo_100
    {106,IR(10, 1),IR(53250, 17),IR(1, 0)}, // DebugStoragePath in nonsemantic_shader_debuginfo_100
    {107,IR(296, 4),IR(53267, 16),IR(1, 0)}, // DebugEntryPoint in nonsemantic_shader_debuginfo_100
    {108,IR(33, 3),IR(53283, 16),IR(1, 0)}, // DebugTypeMatrix in nonsemantic_shader_debuginfo_100
    {1,IR(757, 9),IR(53299, 14),IR(1, 0)}, // Configuration in nonsemantic_vkspreflection
    {2,IR(10, 1),IR(53313, 13),IR(1, 0)}, // StartCounter in nonsemantic_vkspreflection
    {3,IR(10, 1),IR(53326, 12),IR(1, 0)}, // StopCounter in nonsemantic_vkspreflection
    {4,IR(296, 4),IR(53338, 14),IR(1, 0)}, // PushConstants in nonsemantic_vkspreflection
    {5,IR(33, 3),IR(53352, 23),IR(1, 0)}, // SpecializationMapEntry in nonsemantic_vkspreflection
    {6,IR(979, 15),IR(53375, 20),IR(1, 0)}, // DescriptorSetBuffer in nonsemantic_vkspreflection
    {7,IR(994, 33),IR(53395, 19),IR(1, 0)}, // DescriptorSetImage in nonsemantic_vkspreflection
    {8,IR(1027, 19),IR(53414, 21),IR(1, 0)}, // DescriptorSetSampler in nonsemantic_vkspreflection
    {0,IR(0, 0),IR(50532, 14),IR(1, 0)}, // DebugInfoNone in opencl_debuginfo_100
    {1,IR(1046, 4),IR(50546, 21),IR(1, 0)}, // DebugCompilationUnit in opencl_debuginfo_100
    {2,IR(1050, 3),IR(50619, 15),IR(1, 0)}, // DebugTypeBasic in opencl_debuginfo_100
    {3,IR(1053, 3),IR(50668, 17),IR(1, 0)}, // DebugTypePointer in opencl_debuginfo_100
    {4,IR(1056, 2),IR(50723, 19),IR(1, 0)}, // DebugTypeQualifier in opencl_debuginfo_100
    {5,IR(168, 2),IR(50742, 15),IR(1, 0)}, // DebugTypeArray in opencl_debuginfo_100
    {6,IR(261, 2),IR(50757, 16),IR(1, 0)}, // DebugTypeVector in opencl_debuginfo_100
    {7,IR(811, 6),IR(50773, 13),IR(1, 0)}, // DebugTypedef in opencl_debuginfo_100
    {8,IR(1058, 3),IR(50786, 18),IR(1, 0)}, // DebugTypeFunction in opencl_debuginfo_100
    {9,IR(1061, 9),IR(50804, 14),IR(1, 0)}, // DebugTypeEnum in opencl_debuginfo_100
    {10,IR(1070, 10),IR(50856, 19),IR(1, 0)}, // DebugTypeComposite in opencl_debuginfo_100
    {11,IR(1080, 10),IR(50875, 16),IR(1, 0)}, // DebugTypeMember in opencl_debuginfo_100
    {12,IR(1090, 5),IR(50891, 21),IR(1, 0)}, // DebugTypeInheritance in opencl_debuginfo_100
    {13,IR(36, 2),IR(50912, 21),IR(1, 0)}, // DebugTypePtrToMember in opencl_debuginfo_100
    {14,IR(168, 2),IR(50933, 18),IR(1, 0)}, // DebugTypeTemplate in opencl_debuginfo_100
    {15,IR(850, 6),IR(50951, 27),IR(1, 0)}, // DebugTypeTemplateParameter in opencl_debuginfo_100
    {16,IR(856, 5),IR(50978, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in opencl_debuginfo_100
    {17,IR(861, 5),IR(51013, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in opencl_debuginfo_100
    {18,IR(1080, 10),IR(51044, 20),IR(1, 0)}, // DebugGlobalVariable in opencl_debuginfo_100
    {19,IR(1095, 8),IR(51064, 25),IR(1, 0)}, // DebugFunctionDeclaration in opencl_debuginfo_100
    {20,IR(1103, 11),IR(51089, 14),IR(1, 0)}, // DebugFunction in opencl_debuginfo_100
    {21,IR(885, 5),IR(51103, 18),IR(1, 0)}, // DebugLexicalBlock in opencl_debuginfo_100
    {22,IR(890, 3),IR(51121, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in opencl_debuginfo_100
    {23,IR(893, 2),IR(51152, 11),IR(1, 0)}, // DebugScope in opencl_debuginfo_100
    {24,IR(0, 0),IR(51163, 13),IR(1, 0)}, // DebugNoScope in opencl_debuginfo_100
    {25,IR(895, 3),IR(51176, 15),IR(1, 0)}, // DebugInlinedAt in opencl_debuginfo_100
    {26,IR(1114, 8),IR(51233, 19),IR(1, 0)}, // DebugLocalVariable in opencl_debuginfo_100
    {27,IR(36, 2),IR(51252, 21),IR(1, 0)}, // DebugInlinedVariable in opencl_debuginfo_100
    {28,IR(33, 3),IR(51273, 13),IR(1, 0)}, // DebugDeclare in opencl_debuginfo_100
    {29,IR(975, 4),IR(51286, 11),IR(1, 0)}, // DebugValue in opencl_debuginfo_100
    {30,IR(1122, 2),IR(51330, 15),IR(1, 0)}, // DebugOperation in opencl_debuginfo_100
    {31,IR(739, 1),IR(51345, 16),IR(1, 0)}, // DebugExpression in opencl_debuginfo_100
    {32,IR(907, 4),IR(51361, 14),IR(1, 0)}, // DebugMacroDef in opencl_debuginfo_100
    {33,IR(890, 3),IR(51375, 16),IR(1, 0)}, // DebugMacroUndef in opencl_debuginfo_100
    {34,IR(1124, 7),IR(53130, 20),IR(1, 0)}, // DebugImportedEntity in opencl_debuginfo_100
    {35,IR(893, 2),IR(53150, 12),IR(1, 0)}, // DebugSource in opencl_debuginfo_100
    {36,IR(1131, 8),IR(53735, 17),IR(1, 0)}, // DebugModuleINTEL in opencl_debuginfo_100
    {0,IR(10, 1),IR(53752, 5),IR(1, 0)}, // acos in opencl_std_100
    {1,IR(10, 1),IR(53757, 6),IR(1, 0)}, // acosh in opencl_std_100
    {2,IR(10, 1),IR(53763, 7),IR(1, 0)}, // acospi in opencl_std_100
    {3,IR(10, 1),IR(53770, 5),IR(1, 0)}, // asin in opencl_std_100
    {4,IR(10, 1),IR(53775, 6),IR(1, 0)}, // asinh in opencl_std_100
    {5,IR(10, 1),IR(53781, 7),IR(1, 0)}, // asinpi in opencl_std_100
    {6,IR(10, 1),IR(53788, 5),IR(1, 0)}, // atan in opencl_std_100
    {7,IR(36, 2),IR(53793, 6),IR(1, 0)}, // atan2 in opencl_std_100
    {8,IR(10, 1),IR(53799, 6),IR(1, 0)}, // atanh in opencl_std_100
    {9,IR(10, 1),IR(53805, 7),IR(1, 0)}, // atanpi in opencl_std_100
    {10,IR(36, 2),IR(53812, 8),IR(1, 0)}, // atan2pi in opencl_std_100
    {11,IR(10, 1),IR(53820, 5),IR(1, 0)}, // cbrt in opencl_std_100
    {12,IR(10, 1),IR(53825, 5),IR(1, 0)}, // ceil in opencl_std_100
    {13,IR(36, 2),IR(53830, 9),IR(1, 0)}, // copysign in opencl_std_100
    {14,IR(10, 1),IR(53839, 4),IR(1, 0)}, // cos in opencl_std_100
    {15,IR(10, 1),IR(53843, 5),IR(1, 0)}, // cosh in opencl_std_100
    {16,IR(10, 1),IR(53848, 6),IR(1, 0)}, // cospi in opencl_std_100
    {17,IR(10, 1),IR(53854, 5),IR(1, 0)}, // erfc in opencl_std_100
    {18,IR(10, 1),IR(53859, 4),IR(1, 0)}, // erf in opencl_std_100
    {19,IR(10, 1),IR(53863, 4),IR(1, 0)}, // exp in opencl_std_100
    {20,IR(10, 1),IR(53867, 5),IR(1, 0)}, // exp2 in opencl_std_100
    {21,IR(10, 1),IR(53872, 6),IR(1, 0)}, // exp10 in opencl_std_100
    {22,IR(10, 1),IR(53878, 6),IR(1, 0)}, // expm1 in opencl_std_100
    {23,IR(10, 1),IR(53884, 5),IR(1, 0)}, // fabs in opencl_std_100
    {24,IR(36, 2),IR(53889, 5),IR(1, 0)}, // fdim in opencl_std_100
    {25,IR(10, 1),IR(53894, 6),IR(1, 0)}, // floor in opencl_std_100
    {26,IR(33, 3),IR(53900, 4),IR(1, 0)}, // fma in opencl_std_100
    {27,IR(36, 2),IR(53904, 5),IR(1, 0)}, // fmax in opencl_std_100
    {28,IR(36, 2),IR(53909, 5),IR(1, 0)}, // fmin in opencl_std_100
    {29,IR(36, 2),IR(53914, 5),IR(1, 0)}, // fmod in opencl_std_100
    {30,IR(36, 2),IR(53919, 6),IR(1, 0)}, // fract in opencl_std_100
    {31,IR(36, 2),IR(53925, 6),IR(1, 0)}, // frexp in opencl_std_100
    {32,IR(36, 2),IR(53931, 6),IR(1, 0)}, // hypot in opencl_std_100
    {33,IR(10, 1),IR(53937, 6),IR(1, 0)}, // ilogb in opencl_std_100
    {34,IR(36, 2),IR(53943, 6),IR(1, 0)}, // ldexp in opencl_std_100
    {35,IR(10, 1),IR(53949, 7),IR(1, 0)}, // lgamma in opencl_std_100
    {36,IR(36, 2),IR(53956, 9),IR(1, 0)}, // lgamma_r in opencl_std_100
    {37,IR(10, 1),IR(53965, 4),IR(1, 0)}, // log in opencl_std_100
    {38,IR(10, 1),IR(53969, 5),IR(1, 0)}, // log2 in opencl_std_100
    {39,IR(10, 1),IR(53974, 6),IR(1, 0)}, // log10 in opencl_std_100
    {40,IR(10, 1),IR(53980, 6),IR(1, 0)}, // log1p in opencl_std_100
    {41,IR(10, 1),IR(53986, 5),IR(1, 0)}, // logb in opencl_std_100
    {42,IR(33, 3),IR(53991, 4),IR(1, 0)}, // mad in opencl_std_100
    {43,IR(36, 2),IR(53995, 7),IR(1, 0)}, // maxmag in opencl_std_100
    {44,IR(36, 2),IR(54002, 7),IR(1, 0)}, // minmag in opencl_std_100
    {45,IR(36, 2),IR(54009, 5),IR(1, 0)}, // modf in opencl_std_100
    {46,IR(10, 1),IR(54014, 4),IR(1, 0)}, // nan in opencl_std_100
    {47,IR(36, 2),IR(54018, 10),IR(1, 0)}, // nextafter in opencl_std_100
    {48,IR(36, 2),IR(54028, 4),IR(1, 0)}, // pow in opencl_std_100
    {49,IR(36, 2),IR(54032, 5),IR(1, 0)}, // pown in opencl_std_100
    {50,IR(36, 2),IR(54037, 5),IR(1, 0)}, // powr in opencl_std_100
    {51,IR(36, 2),IR(54042, 10),IR(1, 0)}, // remainder in opencl_std_100
    {52,IR(33, 3),IR(54052, 7),IR(1, 0)}, // remquo in opencl_std_100
    {53,IR(10, 1),IR(54059, 5),IR(1, 0)}, // rint in opencl_std_100
    {54,IR(36, 2),IR(54064, 6),IR(1, 0)}, // rootn in opencl_std_100
    {55,IR(10, 1),IR(54070, 6),IR(1, 0)}, // round in opencl_std_100
    {56,IR(10, 1),IR(54076, 6),IR(1, 0)}, // rsqrt in opencl_std_100
    {57,IR(10, 1),IR(54082, 4),IR(1, 0)}, // sin in opencl_std_100
    {58,IR(36, 2),IR(54086, 7),IR(1, 0)}, // sincos in opencl_std_100
    {59,IR(10, 1),IR(54093, 5),IR(1, 0)}, // sinh in opencl_std_100
    {60,IR(10, 1),IR(54098, 6),IR(1, 0)}, // sinpi in opencl_std_100
    {61,IR(10, 1),IR(54104, 5),IR(1, 0)}, // sqrt in opencl_std_100
    {62,IR(10, 1),IR(54109, 4),IR(1, 0)}, // tan in opencl_std_100
    {63,IR(10, 1),IR(54113, 5),IR(1, 0)}, // tanh in opencl_std_100
    {64,IR(10, 1),IR(54118, 6),IR(1, 0)}, // tanpi in opencl_std_100
    {65,IR(10, 1),IR(54124, 7),IR(1, 0)}, // tgamma in opencl_std_100
    {66,IR(10, 1),IR(54131, 6),IR(1, 0)}, // trunc in opencl_std_100
    {67,IR(10, 1),IR(54137, 9),IR(1, 0)}, // half_cos in opencl_std_100
    {68,IR(36, 2),IR(54146, 12),IR(1, 0)}, // half_divide in opencl_std_100
    {69,IR(10, 1),IR(54158, 9),IR(1, 0)}, // half_exp in opencl_std_100
    {70,IR(10, 1),IR(54167, 10),IR(1, 0)}, // half_exp2 in opencl_std_100
    {71,IR(10, 1),IR(54177, 11),IR(1, 0)}, // half_exp10 in opencl_std_100
    {72,IR(10, 1),IR(54188, 9),IR(1, 0)}, // half_log in opencl_std_100
    {73,IR(10, 1),IR(54197, 10),IR(1, 0)}, // half_log2 in opencl_std_100
    {74,IR(10, 1),IR(54207, 11),IR(1, 0)}, // half_log10 in opencl_std_100
    {75,IR(36, 2),IR(54218, 10),IR(1, 0)}, // half_powr in opencl_std_100
    {76,IR(10, 1),IR(54228, 11),IR(1, 0)}, // half_recip in opencl_std_100
    {77,IR(10, 1),IR(54239, 11),IR(1, 0)}, // half_rsqrt in opencl_std_100
    {78,IR(10, 1),IR(54250, 9),IR(1, 0)}, // half_sin in opencl_std_100
    {79,IR(10, 1),IR(54259, 10),IR(1, 0)}, // half_sqrt in opencl_std_100
    {80,IR(10, 1),IR(54269, 9),IR(1, 0)}, // half_tan in opencl_std_100
    {81,IR(10, 1),IR(54278, 11),IR(1, 0)}, // native_cos in opencl_std_100
    {82,IR(36, 2),IR(54289, 14),IR(1, 0)}, // native_divide in opencl_std_100
    {83,IR(10, 1),IR(54303, 11),IR(1, 0)}, // native_exp in opencl_std_100
    {84,IR(10, 1),IR(54314, 12),IR(1, 0)}, // native_exp2 in opencl_std_100
    {85,IR(10, 1),IR(54326, 13),IR(1, 0)}, // native_exp10 in opencl_std_100
    {86,IR(10, 1),IR(54339, 11),IR(1, 0)}, // native_log in opencl_std_100
    {87,IR(10, 1),IR(54350, 12),IR(1, 0)}, // native_log2 in opencl_std_100
    {88,IR(10, 1),IR(54362, 13),IR(1, 0)}, // native_log10 in opencl_std_100
    {89,IR(36, 2),IR(54375, 12),IR(1, 0)}, // native_powr in opencl_std_100
    {90,IR(10, 1),IR(54387, 13),IR(1, 0)}, // native_recip in opencl_std_100
    {91,IR(10, 1),IR(54400, 13),IR(1, 0)}, // native_rsqrt in opencl_std_100
    {92,IR(10, 1),IR(54413, 11),IR(1, 0)}, // native_sin in opencl_std_100
    {93,IR(10, 1),IR(54424, 12),IR(1, 0)}, // native_sqrt in opencl_std_100
    {94,IR(10, 1),IR(54436, 11),IR(1, 0)}, // native_tan in opencl_std_100
    {95,IR(33, 3),IR(54447, 7),IR(1, 0)}, // fclamp in opencl_std_100
    {96,IR(10, 1),IR(54454, 8),IR(1, 0)}, // degrees in opencl_std_100
    {97,IR(36, 2),IR(54462, 12),IR(1, 0)}, // fmax_common in opencl_std_100
    {98,IR(36, 2),IR(54474, 12),IR(1, 0)}, // fmin_common in opencl_std_100
    {99,IR(33, 3),IR(54486, 4),IR(1, 0)}, // mix in opencl_std_100
    {100,IR(10, 1),IR(54490, 8),IR(1, 0)}, // radians in opencl_std_100
    {101,IR(36, 2),IR(54498, 5),IR(1, 0)}, // step in opencl_std_100
    {102,IR(33, 3),IR(54503, 11),IR(1, 0)}, // smoothstep in opencl_std_100
    {103,IR(10, 1),IR(54514, 5),IR(1, 0)}, // sign in opencl_std_100
    {104,IR(36, 2),IR(54519, 6),IR(1, 0)}, // cross in opencl_std_100
    {105,IR(36, 2),IR(54525, 9),IR(1, 0)}, // distance in opencl_std_100
    {106,IR(10, 1),IR(54534, 7),IR(1, 0)}, // length in opencl_std_100
    {107,IR(10, 1),IR(54541, 10),IR(1, 0)}, // normalize in opencl_std_100
    {108,IR(36, 2),IR(54551, 14),IR(1, 0)}, // fast_distance in opencl_std_100
    {109,IR(10, 1),IR(54565, 12),IR(1, 0)}, // fast_length in opencl_std_100
    {110,IR(10, 1),IR(54577, 15),IR(1, 0)}, // fast_normalize in opencl_std_100
    {141,IR(10, 1),IR(54592, 6),IR(1, 0)}, // s_abs in opencl_std_100
    {142,IR(36, 2),IR(54598, 11),IR(1, 0)}, // s_abs_diff in opencl_std_100
    {143,IR(36, 2),IR(54609, 10),IR(1, 0)}, // s_add_sat in opencl_std_100
    {144,IR(36, 2),IR(54619, 10),IR(1, 0)}, // u_add_sat in opencl_std_100
    {145,IR(36, 2),IR(54629, 7),IR(1, 0)}, // s_hadd in opencl_std_100
    {146,IR(36, 2),IR(54636, 7),IR(1, 0)}, // u_hadd in opencl_std_100
    {147,IR(36, 2),IR(54643, 8),IR(1, 0)}, // s_rhadd in opencl_std_100
    {148,IR(36, 2),IR(54651, 8),IR(1, 0)}, // u_rhadd in opencl_std_100
    {149,IR(33, 3),IR(54659, 8),IR(1, 0)}, // s_clamp in opencl_std_100
    {150,IR(33, 3),IR(54667, 8),IR(1, 0)}, // u_clamp in opencl_std_100
    {151,IR(10, 1),IR(54675, 4),IR(1, 0)}, // clz in opencl_std_100
    {152,IR(10, 1),IR(54679, 4),IR(1, 0)}, // ctz in opencl_std_100
    {153,IR(33, 3),IR(54683, 9),IR(1, 0)}, // s_mad_hi in opencl_std_100
    {154,IR(33, 3),IR(54692, 10),IR(1, 0)}, // u_mad_sat in opencl_std_100
    {155,IR(33, 3),IR(54702, 10),IR(1, 0)}, // s_mad_sat in opencl_std_100
    {156,IR(36, 2),IR(54712, 6),IR(1, 0)}, // s_max in opencl_std_100
    {157,IR(36, 2),IR(54718, 6),IR(1, 0)}, // u_max in opencl_std_100
    {158,IR(36, 2),IR(54724, 6),IR(1, 0)}, // s_min in opencl_std_100
    {159,IR(36, 2),IR(54730, 6),IR(1, 0)}, // u_min in opencl_std_100
    {160,IR(36, 2),IR(54736, 9),IR(1, 0)}, // s_mul_hi in opencl_std_100
    {161,IR(36, 2),IR(54745, 7),IR(1, 0)}, // rotate in opencl_std_100
    {162,IR(36, 2),IR(54752, 10),IR(1, 0)}, // s_sub_sat in opencl_std_100
    {163,IR(36, 2),IR(54762, 10),IR(1, 0)}, // u_sub_sat in opencl_std_100
    {164,IR(36, 2),IR(54772, 11),IR(1, 0)}, // u_upsample in opencl_std_100
    {165,IR(36, 2),IR(54783, 11),IR(1, 0)}, // s_upsample in opencl_std_100
    {166,IR(10, 1),IR(54794, 9),IR(1, 0)}, // popcount in opencl_std_100
    {167,IR(33, 3),IR(54803, 8),IR(1, 0)}, // s_mad24 in opencl_std_100
    {168,IR(33, 3),IR(54811, 8),IR(1, 0)}, // u_mad24 in opencl_std_100
    {169,IR(36, 2),IR(54819, 8),IR(1, 0)}, // s_mul24 in opencl_std_100
    {170,IR(36, 2),IR(54827, 8),IR(1, 0)}, // u_mul24 in opencl_std_100
    {171,IR(1139, 3),IR(54835, 7),IR(1, 0)}, // vloadn in opencl_std_100
    {172,IR(33, 3),IR(54842, 8),IR(1, 0)}, // vstoren in opencl_std_100
    {173,IR(36, 2),IR(54850, 11),IR(1, 0)}, // vload_half in opencl_std_100
    {174,IR(1139, 3),IR(54861, 12),IR(1, 0)}, // vload_halfn in opencl_std_100
    {175,IR(33, 3),IR(54873, 12),IR(1, 0)}, // vstore_half in opencl_std_100
    {176,IR(1142, 4),IR(54885, 14),IR(1, 0)}, // vstore_half_r in opencl_std_100
    {177,IR(33, 3),IR(54899, 13),IR(1, 0)}, // vstore_halfn in opencl_std_100
    {178,IR(1142, 4),IR(54912, 15),IR(1, 0)}, // vstore_halfn_r in opencl_std_100
    {179,IR(1139, 3),IR(54927, 13),IR(1, 0)}, // vloada_halfn in opencl_std_100
    {180,IR(33, 3),IR(54940, 14),IR(1, 0)}, // vstorea_halfn in opencl_std_100
    {181,IR(1142, 4),IR(54954, 16),IR(1, 0)}, // vstorea_halfn_r in opencl_std_100
    {182,IR(36, 2),IR(54970, 8),IR(1, 0)}, // shuffle in opencl_std_100
    {183,IR(33, 3),IR(54978, 9),IR(1, 0)}, // shuffle2 in opencl_std_100
    {184,IR(168, 2),IR(54987, 7),IR(1, 0)}, // printf in opencl_std_100
    {185,IR(36, 2),IR(54994, 9),IR(1, 0)}, // prefetch in opencl_std_100
    {186,IR(33, 3),IR(55003, 10),IR(1, 0)}, // bitselect in opencl_std_100
    {187,IR(33, 3),IR(55013, 7),IR(1, 0)}, // select in opencl_std_100
    {201,IR(10, 1),IR(55020, 6),IR(1, 0)}, // u_abs in opencl_std_100
    {202,IR(36, 2),IR(55026, 11),IR(1, 0)}, // u_abs_diff in opencl_std_100
    {203,IR(36, 2),IR(55037, 9),IR(1, 0)}, // u_mul_hi in opencl_std_100
    {204,IR(33, 3),IR(55046, 9),IR(1, 0)}, // u_mad_hi in opencl_std_100
    {1,IR(10, 1),IR(55055, 17),IR(1, 0)}, // CubeFaceIndexAMD in spv_amd_gcn_shader
    {2,IR(10, 1),IR(55072, 17),IR(1, 0)}, // CubeFaceCoordAMD in spv_amd_gcn_shader
    {3,IR(0, 0),IR(55089, 8),IR(1, 0)}, // TimeAMD in spv_amd_gcn_shader
    {1,IR(36, 2),IR(55097, 22),IR(1, 0)}, // SwizzleInvocationsAMD in spv_amd_shader_ballot
    {2,IR(36, 2),IR(55119, 28),IR(1, 0)}, // SwizzleInvocationsMaskedAMD in spv_amd_shader_ballot
    {3,IR(33, 3),IR(55147, 19),IR(1, 0)}, // WriteInvocationAMD in spv_amd_shader_ballot
    {4,IR(10, 1),IR(55166, 9),IR(1, 0)}, // MbcntAMD in spv_amd_shader_ballot
    {1,IR(36, 2),IR(55175, 23),IR(1, 0)}, // InterpolateAtVertexAMD in spv_amd_shader_explicit_vertex_parameter
    {1,IR(33, 3),IR(55198, 9),IR(1, 0)}, // FMin3AMD in spv_amd_shader_trinary_minmax
    {2,IR(33, 3),IR(55207, 9),IR(1, 0)}, // UMin3AMD in spv_amd_shader_trinary_minmax
    {3,IR(33, 3),IR(55216, 9),IR(1, 0)}, // SMin3AMD in spv_amd_shader_trinary_minmax
    {4,IR(33, 3),IR(55225, 9),IR(1, 0)}, // FMax3AMD in spv_amd_shader_trinary_minmax
    {5,IR(33, 3),IR(55234, 9),IR(1, 0)}, // UMax3AMD in spv_amd_shader_trinary_minmax
    {6,IR(33, 3),IR(55243, 9),IR(1, 0)}, // SMax3AMD in spv_amd_shader_trinary_minmax
    {7,IR(33, 3),IR(55252, 9),IR(1, 0)}, // FMid3AMD in spv_amd_shader_trinary_minmax
    {8,IR(33, 3),IR(55261, 9),IR(1, 0)}, // UMid3AMD in spv_amd_shader_trinary_minmax
    {9,IR(33, 3),IR(55270, 9),IR(1, 0)}, // SMid3AMD in spv_amd_shader_trinary_minmax
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
    {IR(50546, 21), 1}, // DebugCompilationUnit in debuginfo
    {IR(51273, 13), 28}, // DebugDeclare in debuginfo
    {IR(51345, 16), 31}, // DebugExpression in debuginfo
    {IR(51089, 14), 20}, // DebugFunction in debuginfo
    {IR(51064, 25), 19}, // DebugFunctionDeclaration in debuginfo
    {IR(51044, 20), 18}, // DebugGlobalVariable in debuginfo
    {IR(50532, 14), 0}, // DebugInfoNone in debuginfo
    {IR(51176, 15), 25}, // DebugInlinedAt in debuginfo
    {IR(51252, 21), 27}, // DebugInlinedVariable in debuginfo
    {IR(51103, 18), 21}, // DebugLexicalBlock in debuginfo
    {IR(51121, 31), 22}, // DebugLexicalBlockDiscriminator in debuginfo
    {IR(51233, 19), 26}, // DebugLocalVariable in debuginfo
    {IR(51361, 14), 32}, // DebugMacroDef in debuginfo
    {IR(51375, 16), 33}, // DebugMacroUndef in debuginfo
    {IR(51163, 13), 24}, // DebugNoScope in debuginfo
    {IR(51330, 15), 30}, // DebugOperation in debuginfo
    {IR(51152, 11), 23}, // DebugScope in debuginfo
    {IR(50742, 15), 5}, // DebugTypeArray in debuginfo
    {IR(50619, 15), 2}, // DebugTypeBasic in debuginfo
    {IR(50856, 19), 10}, // DebugTypeComposite in debuginfo
    {IR(50804, 14), 9}, // DebugTypeEnum in debuginfo
    {IR(50786, 18), 8}, // DebugTypeFunction in debuginfo
    {IR(50891, 21), 12}, // DebugTypeInheritance in debuginfo
    {IR(50875, 16), 11}, // DebugTypeMember in debuginfo
    {IR(50668, 17), 3}, // DebugTypePointer in debuginfo
    {IR(50912, 21), 13}, // DebugTypePtrToMember in debuginfo
    {IR(50723, 19), 4}, // DebugTypeQualifier in debuginfo
    {IR(50933, 18), 14}, // DebugTypeTemplate in debuginfo
    {IR(50951, 27), 15}, // DebugTypeTemplateParameter in debuginfo
    {IR(51013, 31), 17}, // DebugTypeTemplateParameterPack in debuginfo
    {IR(50978, 35), 16}, // DebugTypeTemplateTemplateParameter in debuginfo
    {IR(50757, 16), 6}, // DebugTypeVector in debuginfo
    {IR(50773, 13), 7}, // DebugTypedef in debuginfo
    {IR(51286, 11), 29}, // DebugValue in debuginfo
    {IR(51485, 5), 50}, // Acos in glsl_std_450
    {IR(51516, 6), 56}, // Acosh in glsl_std_450
    {IR(51480, 5), 49}, // Asin in glsl_std_450
    {IR(51510, 6), 55}, // Asinh in glsl_std_450
    {IR(51490, 5), 51}, // Atan in glsl_std_450
    {IR(51528, 6), 58}, // Atan2 in glsl_std_450
    {IR(51522, 6), 57}, // Atanh in glsl_std_450
    {IR(51441, 5), 42}, // Ceil in glsl_std_450
    {IR(51472, 4), 47}, // Cos in glsl_std_450
    {IR(51500, 5), 53}, // Cosh in glsl_std_450
    {IR(51912, 6), 101}, // Cross in glsl_std_450
    {IR(51460, 8), 45}, // Degrees in glsl_std_450
    {IR(51573, 12), 66}, // Determinant in glsl_std_450
    {IR(51903, 9), 100}, // Distance in glsl_std_450
    {IR(51538, 4), 60}, // Exp in glsl_std_450
    {IR(51546, 5), 62}, // Exp2 in glsl_std_450
    {IR(51413, 5), 37}, // FAbs in glsl_std_450
    {IR(51645, 7), 76}, // FClamp in glsl_std_450
    {IR(51630, 5), 73}, // FMax in glsl_std_450
    {IR(51615, 5), 70}, // FMin in glsl_std_450
    {IR(51666, 5), 79}, // FMix in glsl_std_450
    {IR(51423, 6), 39}, // FSign in glsl_std_450
    {IR(51928, 12), 103}, // FaceForward in glsl_std_450
    {IR(51956, 9), 106}, // FindILsb in glsl_std_450
    {IR(51965, 9), 107}, // FindSMsb in glsl_std_450
    {IR(51974, 9), 108}, // FindUMsb in glsl_std_450
    {IR(51435, 6), 41}, // Floor in glsl_std_450
    {IR(51692, 4), 83}, // Fma in glsl_std_450
    {IR(51446, 6), 43}, // Fract in glsl_std_450
    {IR(51696, 6), 84}, // Frexp in glsl_std_450
    {IR(51702, 12), 85}, // FrexpStruct in glsl_std_450
    {IR(51671, 5), 80}, // IMix in glsl_std_450
    {IR(51983, 22), 109}, // InterpolateAtCentroid in glsl_std_450
    {IR(52025, 20), 111}, // InterpolateAtOffset in glsl_std_450
    {IR(52005, 20), 110}, // InterpolateAtSample in glsl_std_450
    {IR(51561, 12), 65}, // InverseSqrt in glsl_std_450
    {IR(51714, 6), 86}, // Ldexp in glsl_std_450
    {IR(51896, 7), 99}, // Length in glsl_std_450
    {IR(51542, 4), 61}, // Log in glsl_std_450
    {IR(51551, 5), 63}, // Log2 in glsl_std_450
    {IR(51585, 14), 67}, // MatrixInverse in glsl_std_450
    {IR(51599, 5), 68}, // Modf in glsl_std_450
    {IR(51604, 11), 69}, // ModfStruct in glsl_std_450
    {IR(52055, 7), 114}, // NClamp in glsl_std_450
    {IR(52050, 5), 113}, // NMax in glsl_std_450
    {IR(52045, 5), 112}, // NMin in glsl_std_450
    {IR(51918, 10), 102}, // Normalize in glsl_std_450
    {IR(51787, 15), 92}, // PackDouble2x32 in glsl_std_450
    {IR(51774, 13), 91}, // PackHalf2x16 in glsl_std_450
    {IR(51746, 14), 89}, // PackSnorm2x16 in glsl_std_450
    {IR(51720, 13), 87}, // PackSnorm4x8 in glsl_std_450
    {IR(51760, 14), 90}, // PackUnorm2x16 in glsl_std_450
    {IR(51733, 13), 88}, // PackUnorm4x8 in glsl_std_450
    {IR(51534, 4), 59}, // Pow in glsl_std_450
    {IR(51452, 8), 44}, // Radians in glsl_std_450
    {IR(51940, 8), 104}, // Reflect in glsl_std_450
    {IR(51948, 8), 105}, // Refract in glsl_std_450
    {IR(51391, 6), 34}, // Round in glsl_std_450
    {IR(51397, 10), 35}, // RoundEven in glsl_std_450
    {IR(51418, 5), 38}, // SAbs in glsl_std_450
    {IR(51659, 7), 78}, // SClamp in glsl_std_450
    {IR(51640, 5), 75}, // SMax in glsl_std_450
    {IR(51625, 5), 72}, // SMin in glsl_std_450
    {IR(51429, 6), 40}, // SSign in glsl_std_450
    {IR(51468, 4), 46}, // Sin in glsl_std_450
    {IR(51495, 5), 52}, // Sinh in glsl_std_450
    {IR(51681, 11), 82}, // SmoothStep in glsl_std_450
    {IR(51556, 5), 64}, // Sqrt in glsl_std_450
    {IR(51676, 5), 81}, // Step in glsl_std_450
    {IR(51476, 4), 48}, // Tan in glsl_std_450
    {IR(51505, 5), 54}, // Tanh in glsl_std_450
    {IR(51407, 6), 36}, // Trunc in glsl_std_450
    {IR(51652, 7), 77}, // UClamp in glsl_std_450
    {IR(51635, 5), 74}, // UMax in glsl_std_450
    {IR(51620, 5), 71}, // UMin in glsl_std_450
    {IR(51879, 17), 98}, // UnpackDouble2x32 in glsl_std_450
    {IR(51834, 15), 95}, // UnpackHalf2x16 in glsl_std_450
    {IR(51802, 16), 93}, // UnpackSnorm2x16 in glsl_std_450
    {IR(51849, 15), 96}, // UnpackSnorm4x8 in glsl_std_450
    {IR(51818, 16), 94}, // UnpackUnorm2x16 in glsl_std_450
    {IR(51864, 15), 97}, // UnpackUnorm4x8 in glsl_std_450
    {IR(52062, 13), 116}, // ArgumentInfo in nonsemantic_clspvreflection
    {IR(52157, 24), 121}, // ArgumentPodPushConstant in nonsemantic_clspvreflection
    {IR(52113, 25), 119}, // ArgumentPodStorageBuffer in nonsemantic_clspvreflection
    {IR(52138, 19), 120}, // ArgumentPodUniform in nonsemantic_clspvreflection
    {IR(52591, 28), 140}, // ArgumentPointerPushConstant in nonsemantic_clspvreflection
    {IR(52619, 23), 141}, // ArgumentPointerUniform in nonsemantic_clspvreflection
    {IR(52181, 21), 122}, // ArgumentSampledImage in nonsemantic_clspvreflection
    {IR(52223, 16), 124}, // ArgumentSampler in nonsemantic_clspvreflection
    {IR(52075, 22), 117}, // ArgumentStorageBuffer in nonsemantic_clspvreflection
    {IR(52202, 21), 123}, // ArgumentStorageImage in nonsemantic_clspvreflection
    {IR(52879, 27), 148}, // ArgumentStorageTexelBuffer in nonsemantic_clspvreflection
    {IR(52097, 16), 118}, // ArgumentUniform in nonsemantic_clspvreflection
    {IR(52906, 27), 149}, // ArgumentUniformTexelBuffer in nonsemantic_clspvreflection
    {IR(52239, 18), 125}, // ArgumentWorkgroup in nonsemantic_clspvreflection
    {IR(52933, 32), 150}, // ConstantDataPointerPushConstant in nonsemantic_clspvreflection
    {IR(52487, 26), 135}, // ConstantDataStorageBuffer in nonsemantic_clspvreflection
    {IR(52513, 20), 136}, // ConstantDataUniform in nonsemantic_clspvreflection
    {IR(52757, 45), 145}, // ImageArgumentInfoChannelDataTypePushConstant in nonsemantic_clspvreflection
    {IR(52839, 40), 147}, // ImageArgumentInfoChannelDataTypeUniform in nonsemantic_clspvreflection
    {IR(52715, 42), 144}, // ImageArgumentInfoChannelOrderPushConstant in nonsemantic_clspvreflection
    {IR(52802, 37), 146}, // ImageArgumentInfoChannelOrderUniform in nonsemantic_clspvreflection
    {IR(5463, 7), 115}, // Kernel in nonsemantic_clspvreflection
    {IR(8937, 15), 137}, // LiteralSampler in nonsemantic_clspvreflection
    {IR(53074, 34), 155}, // NormalizedSamplerMaskPushConstant in nonsemantic_clspvreflection
    {IR(53042, 32), 154}, // PrintfBufferPointerPushConstant in nonsemantic_clspvreflection
    {IR(53016, 26), 153}, // PrintfBufferStorageBuffer in nonsemantic_clspvreflection
    {IR(53005, 11), 152}, // PrintfInfo in nonsemantic_clspvreflection
    {IR(52965, 40), 151}, // ProgramScopeVariablePointerPushConstant in nonsemantic_clspvreflection
    {IR(52677, 38), 143}, // ProgramScopeVariablePointerRelocation in nonsemantic_clspvreflection
    {IR(52642, 35), 142}, // ProgramScopeVariablesStorageBuffer in nonsemantic_clspvreflection
    {IR(52533, 30), 138}, // PropertyRequiredWorkgroupSize in nonsemantic_clspvreflection
    {IR(52353, 30), 130}, // PushConstantEnqueuedLocalSize in nonsemantic_clspvreflection
    {IR(52328, 25), 129}, // PushConstantGlobalOffset in nonsemantic_clspvreflection
    {IR(52383, 23), 131}, // PushConstantGlobalSize in nonsemantic_clspvreflection
    {IR(52431, 26), 133}, // PushConstantNumWorkgroups in nonsemantic_clspvreflection
    {IR(52457, 30), 134}, // PushConstantRegionGroupOffset in nonsemantic_clspvreflection
    {IR(52406, 25), 132}, // PushConstantRegionOffset in nonsemantic_clspvreflection
    {IR(52283, 25), 127}, // SpecConstantGlobalOffset in nonsemantic_clspvreflection
    {IR(52563, 28), 139}, // SpecConstantSubgroupMaxSize in nonsemantic_clspvreflection
    {IR(52308, 20), 128}, // SpecConstantWorkDim in nonsemantic_clspvreflection
    {IR(52257, 26), 126}, // SpecConstantWorkgroupSize in nonsemantic_clspvreflection
    {IR(53108, 22), 156}, // WorkgroupVariableSize in nonsemantic_clspvreflection
    {IR(53229, 21), 197}, // DebugBuildIdentifier in nonsemantic_shader_debuginfo_100
    {IR(50546, 21), 158}, // DebugCompilationUnit in nonsemantic_shader_debuginfo_100
    {IR(51273, 13), 185}, // DebugDeclare in nonsemantic_shader_debuginfo_100
    {IR(53267, 16), 199}, // DebugEntryPoint in nonsemantic_shader_debuginfo_100
    {IR(51345, 16), 188}, // DebugExpression in nonsemantic_shader_debuginfo_100
    {IR(51089, 14), 177}, // DebugFunction in nonsemantic_shader_debuginfo_100
    {IR(51064, 25), 176}, // DebugFunctionDeclaration in nonsemantic_shader_debuginfo_100
    {IR(53162, 24), 193}, // DebugFunctionDefinition in nonsemantic_shader_debuginfo_100
    {IR(51044, 20), 175}, // DebugGlobalVariable in nonsemantic_shader_debuginfo_100
    {IR(53130, 20), 191}, // DebugImportedEntity in nonsemantic_shader_debuginfo_100
    {IR(50532, 14), 157}, // DebugInfoNone in nonsemantic_shader_debuginfo_100
    {IR(51176, 15), 182}, // DebugInlinedAt in nonsemantic_shader_debuginfo_100
    {IR(51252, 21), 184}, // DebugInlinedVariable in nonsemantic_shader_debuginfo_100
    {IR(51103, 18), 178}, // DebugLexicalBlock in nonsemantic_shader_debuginfo_100
    {IR(51121, 31), 179}, // DebugLexicalBlockDiscriminator in nonsemantic_shader_debuginfo_100
    {IR(53207, 10), 195}, // DebugLine in nonsemantic_shader_debuginfo_100
    {IR(51233, 19), 183}, // DebugLocalVariable in nonsemantic_shader_debuginfo_100
    {IR(51361, 14), 189}, // DebugMacroDef in nonsemantic_shader_debuginfo_100
    {IR(51375, 16), 190}, // DebugMacroUndef in nonsemantic_shader_debuginfo_100
    {IR(53217, 12), 196}, // DebugNoLine in nonsemantic_shader_debuginfo_100
    {IR(51163, 13), 181}, // DebugNoScope in nonsemantic_shader_debuginfo_100
    {IR(51330, 15), 187}, // DebugOperation in nonsemantic_shader_debuginfo_100
    {IR(51152, 11), 180}, // DebugScope in nonsemantic_shader_debuginfo_100
    {IR(53150, 12), 192}, // DebugSource in nonsemantic_shader_debuginfo_100
    {IR(53186, 21), 194}, // DebugSourceContinued in nonsemantic_shader_debuginfo_100
    {IR(53250, 17), 198}, // DebugStoragePath in nonsemantic_shader_debuginfo_100
    {IR(50742, 15), 162}, // DebugTypeArray in nonsemantic_shader_debuginfo_100
    {IR(50619, 15), 159}, // DebugTypeBasic in nonsemantic_shader_debuginfo_100
    {IR(50856, 19), 167}, // DebugTypeComposite in nonsemantic_shader_debuginfo_100
    {IR(50804, 14), 166}, // DebugTypeEnum in nonsemantic_shader_debuginfo_100
    {IR(50786, 18), 165}, // DebugTypeFunction in nonsemantic_shader_debuginfo_100
    {IR(50891, 21), 169}, // DebugTypeInheritance in nonsemantic_shader_debuginfo_100
    {IR(53283, 16), 200}, // DebugTypeMatrix in nonsemantic_shader_debuginfo_100
    {IR(50875, 16), 168}, // DebugTypeMember in nonsemantic_shader_debuginfo_100
    {IR(50668, 17), 160}, // DebugTypePointer in nonsemantic_shader_debuginfo_100
    {IR(50912, 21), 170}, // DebugTypePtrToMember in nonsemantic_shader_debuginfo_100
    {IR(50723, 19), 161}, // DebugTypeQualifier in nonsemantic_shader_debuginfo_100
    {IR(50933, 18), 171}, // DebugTypeTemplate in nonsemantic_shader_debuginfo_100
    {IR(50951, 27), 172}, // DebugTypeTemplateParameter in nonsemantic_shader_debuginfo_100
    {IR(51013, 31), 174}, // DebugTypeTemplateParameterPack in nonsemantic_shader_debuginfo_100
    {IR(50978, 35), 173}, // DebugTypeTemplateTemplateParameter in nonsemantic_shader_debuginfo_100
    {IR(50757, 16), 163}, // DebugTypeVector in nonsemantic_shader_debuginfo_100
    {IR(50773, 13), 164}, // DebugTypedef in nonsemantic_shader_debuginfo_100
    {IR(51286, 11), 186}, // DebugValue in nonsemantic_shader_debuginfo_100
    {IR(53299, 14), 201}, // Configuration in nonsemantic_vkspreflection
    {IR(53375, 20), 206}, // DescriptorSetBuffer in nonsemantic_vkspreflection
    {IR(53395, 19), 207}, // DescriptorSetImage in nonsemantic_vkspreflection
    {IR(53414, 21), 208}, // DescriptorSetSampler in nonsemantic_vkspreflection
    {IR(53338, 14), 204}, // PushConstants in nonsemantic_vkspreflection
    {IR(53352, 23), 205}, // SpecializationMapEntry in nonsemantic_vkspreflection
    {IR(53313, 13), 202}, // StartCounter in nonsemantic_vkspreflection
    {IR(53326, 12), 203}, // StopCounter in nonsemantic_vkspreflection
    {IR(50546, 21), 210}, // DebugCompilationUnit in opencl_debuginfo_100
    {IR(51273, 13), 237}, // DebugDeclare in opencl_debuginfo_100
    {IR(51345, 16), 240}, // DebugExpression in opencl_debuginfo_100
    {IR(51089, 14), 229}, // DebugFunction in opencl_debuginfo_100
    {IR(51064, 25), 228}, // DebugFunctionDeclaration in opencl_debuginfo_100
    {IR(51044, 20), 227}, // DebugGlobalVariable in opencl_debuginfo_100
    {IR(53130, 20), 243}, // DebugImportedEntity in opencl_debuginfo_100
    {IR(50532, 14), 209}, // DebugInfoNone in opencl_debuginfo_100
    {IR(51176, 15), 234}, // DebugInlinedAt in opencl_debuginfo_100
    {IR(51252, 21), 236}, // DebugInlinedVariable in opencl_debuginfo_100
    {IR(51103, 18), 230}, // DebugLexicalBlock in opencl_debuginfo_100
    {IR(51121, 31), 231}, // DebugLexicalBlockDiscriminator in opencl_debuginfo_100
    {IR(51233, 19), 235}, // DebugLocalVariable in opencl_debuginfo_100
    {IR(51361, 14), 241}, // DebugMacroDef in opencl_debuginfo_100
    {IR(51375, 16), 242}, // DebugMacroUndef in opencl_debuginfo_100
    {IR(53735, 17), 245}, // DebugModuleINTEL in opencl_debuginfo_100
    {IR(51163, 13), 233}, // DebugNoScope in opencl_debuginfo_100
    {IR(51330, 15), 239}, // DebugOperation in opencl_debuginfo_100
    {IR(51152, 11), 232}, // DebugScope in opencl_debuginfo_100
    {IR(53150, 12), 244}, // DebugSource in opencl_debuginfo_100
    {IR(50742, 15), 214}, // DebugTypeArray in opencl_debuginfo_100
    {IR(50619, 15), 211}, // DebugTypeBasic in opencl_debuginfo_100
    {IR(50856, 19), 219}, // DebugTypeComposite in opencl_debuginfo_100
    {IR(50804, 14), 218}, // DebugTypeEnum in opencl_debuginfo_100
    {IR(50786, 18), 217}, // DebugTypeFunction in opencl_debuginfo_100
    {IR(50891, 21), 221}, // DebugTypeInheritance in opencl_debuginfo_100
    {IR(50875, 16), 220}, // DebugTypeMember in opencl_debuginfo_100
    {IR(50668, 17), 212}, // DebugTypePointer in opencl_debuginfo_100
    {IR(50912, 21), 222}, // DebugTypePtrToMember in opencl_debuginfo_100
    {IR(50723, 19), 213}, // DebugTypeQualifier in opencl_debuginfo_100
    {IR(50933, 18), 223}, // DebugTypeTemplate in opencl_debuginfo_100
    {IR(50951, 27), 224}, // DebugTypeTemplateParameter in opencl_debuginfo_100
    {IR(51013, 31), 226}, // DebugTypeTemplateParameterPack in opencl_debuginfo_100
    {IR(50978, 35), 225}, // DebugTypeTemplateTemplateParameter in opencl_debuginfo_100
    {IR(50757, 16), 215}, // DebugTypeVector in opencl_debuginfo_100
    {IR(50773, 13), 216}, // DebugTypedef in opencl_debuginfo_100
    {IR(51286, 11), 238}, // DebugValue in opencl_debuginfo_100
    {IR(53752, 5), 246}, // acos in opencl_std_100
    {IR(53757, 6), 247}, // acosh in opencl_std_100
    {IR(53763, 7), 248}, // acospi in opencl_std_100
    {IR(53770, 5), 249}, // asin in opencl_std_100
    {IR(53775, 6), 250}, // asinh in opencl_std_100
    {IR(53781, 7), 251}, // asinpi in opencl_std_100
    {IR(53788, 5), 252}, // atan in opencl_std_100
    {IR(53793, 6), 253}, // atan2 in opencl_std_100
    {IR(53812, 8), 256}, // atan2pi in opencl_std_100
    {IR(53799, 6), 254}, // atanh in opencl_std_100
    {IR(53805, 7), 255}, // atanpi in opencl_std_100
    {IR(55003, 10), 402}, // bitselect in opencl_std_100
    {IR(53820, 5), 257}, // cbrt in opencl_std_100
    {IR(53825, 5), 258}, // ceil in opencl_std_100
    {IR(54675, 4), 367}, // clz in opencl_std_100
    {IR(53830, 9), 259}, // copysign in opencl_std_100
    {IR(53839, 4), 260}, // cos in opencl_std_100
    {IR(53843, 5), 261}, // cosh in opencl_std_100
    {IR(53848, 6), 262}, // cospi in opencl_std_100
    {IR(54519, 6), 350}, // cross in opencl_std_100
    {IR(54679, 4), 368}, // ctz in opencl_std_100
    {IR(54454, 8), 342}, // degrees in opencl_std_100
    {IR(54525, 9), 351}, // distance in opencl_std_100
    {IR(53859, 4), 264}, // erf in opencl_std_100
    {IR(53854, 5), 263}, // erfc in opencl_std_100
    {IR(53863, 4), 265}, // exp in opencl_std_100
    {IR(53872, 6), 267}, // exp10 in opencl_std_100
    {IR(53867, 5), 266}, // exp2 in opencl_std_100
    {IR(53878, 6), 268}, // expm1 in opencl_std_100
    {IR(53884, 5), 269}, // fabs in opencl_std_100
    {IR(54551, 14), 354}, // fast_distance in opencl_std_100
    {IR(54565, 12), 355}, // fast_length in opencl_std_100
    {IR(54577, 15), 356}, // fast_normalize in opencl_std_100
    {IR(54447, 7), 341}, // fclamp in opencl_std_100
    {IR(53889, 5), 270}, // fdim in opencl_std_100
    {IR(53894, 6), 271}, // floor in opencl_std_100
    {IR(53900, 4), 272}, // fma in opencl_std_100
    {IR(53904, 5), 273}, // fmax in opencl_std_100
    {IR(54462, 12), 343}, // fmax_common in opencl_std_100
    {IR(53909, 5), 274}, // fmin in opencl_std_100
    {IR(54474, 12), 344}, // fmin_common in opencl_std_100
    {IR(53914, 5), 275}, // fmod in opencl_std_100
    {IR(53919, 6), 276}, // fract in opencl_std_100
    {IR(53925, 6), 277}, // frexp in opencl_std_100
    {IR(54137, 9), 313}, // half_cos in opencl_std_100
    {IR(54146, 12), 314}, // half_divide in opencl_std_100
    {IR(54158, 9), 315}, // half_exp in opencl_std_100
    {IR(54177, 11), 317}, // half_exp10 in opencl_std_100
    {IR(54167, 10), 316}, // half_exp2 in opencl_std_100
    {IR(54188, 9), 318}, // half_log in opencl_std_100
    {IR(54207, 11), 320}, // half_log10 in opencl_std_100
    {IR(54197, 10), 319}, // half_log2 in opencl_std_100
    {IR(54218, 10), 321}, // half_powr in opencl_std_100
    {IR(54228, 11), 322}, // half_recip in opencl_std_100
    {IR(54239, 11), 323}, // half_rsqrt in opencl_std_100
    {IR(54250, 9), 324}, // half_sin in opencl_std_100
    {IR(54259, 10), 325}, // half_sqrt in opencl_std_100
    {IR(54269, 9), 326}, // half_tan in opencl_std_100
    {IR(53931, 6), 278}, // hypot in opencl_std_100
    {IR(53937, 6), 279}, // ilogb in opencl_std_100
    {IR(53943, 6), 280}, // ldexp in opencl_std_100
    {IR(54534, 7), 352}, // length in opencl_std_100
    {IR(53949, 7), 281}, // lgamma in opencl_std_100
    {IR(53956, 9), 282}, // lgamma_r in opencl_std_100
    {IR(53965, 4), 283}, // log in opencl_std_100
    {IR(53974, 6), 285}, // log10 in opencl_std_100
    {IR(53980, 6), 286}, // log1p in opencl_std_100
    {IR(53969, 5), 284}, // log2 in opencl_std_100
    {IR(53986, 5), 287}, // logb in opencl_std_100
    {IR(53991, 4), 288}, // mad in opencl_std_100
    {IR(53995, 7), 289}, // maxmag in opencl_std_100
    {IR(54002, 7), 290}, // minmag in opencl_std_100
    {IR(54486, 4), 345}, // mix in opencl_std_100
    {IR(54009, 5), 291}, // modf in opencl_std_100
    {IR(54014, 4), 292}, // nan in opencl_std_100
    {IR(54278, 11), 327}, // native_cos in opencl_std_100
    {IR(54289, 14), 328}, // native_divide in opencl_std_100
    {IR(54303, 11), 329}, // native_exp in opencl_std_100
    {IR(54326, 13), 331}, // native_exp10 in opencl_std_100
    {IR(54314, 12), 330}, // native_exp2 in opencl_std_100
    {IR(54339, 11), 332}, // native_log in opencl_std_100
    {IR(54362, 13), 334}, // native_log10 in opencl_std_100
    {IR(54350, 12), 333}, // native_log2 in opencl_std_100
    {IR(54375, 12), 335}, // native_powr in opencl_std_100
    {IR(54387, 13), 336}, // native_recip in opencl_std_100
    {IR(54400, 13), 337}, // native_rsqrt in opencl_std_100
    {IR(54413, 11), 338}, // native_sin in opencl_std_100
    {IR(54424, 12), 339}, // native_sqrt in opencl_std_100
    {IR(54436, 11), 340}, // native_tan in opencl_std_100
    {IR(54018, 10), 293}, // nextafter in opencl_std_100
    {IR(54541, 10), 353}, // normalize in opencl_std_100
    {IR(54794, 9), 382}, // popcount in opencl_std_100
    {IR(54028, 4), 294}, // pow in opencl_std_100
    {IR(54032, 5), 295}, // pown in opencl_std_100
    {IR(54037, 5), 296}, // powr in opencl_std_100
    {IR(54994, 9), 401}, // prefetch in opencl_std_100
    {IR(54987, 7), 400}, // printf in opencl_std_100
    {IR(54490, 8), 346}, // radians in opencl_std_100
    {IR(54042, 10), 297}, // remainder in opencl_std_100
    {IR(54052, 7), 298}, // remquo in opencl_std_100
    {IR(54059, 5), 299}, // rint in opencl_std_100
    {IR(54064, 6), 300}, // rootn in opencl_std_100
    {IR(54745, 7), 377}, // rotate in opencl_std_100
    {IR(54070, 6), 301}, // round in opencl_std_100
    {IR(54076, 6), 302}, // rsqrt in opencl_std_100
    {IR(54592, 6), 357}, // s_abs in opencl_std_100
    {IR(54598, 11), 358}, // s_abs_diff in opencl_std_100
    {IR(54609, 10), 359}, // s_add_sat in opencl_std_100
    {IR(54659, 8), 365}, // s_clamp in opencl_std_100
    {IR(54629, 7), 361}, // s_hadd in opencl_std_100
    {IR(54803, 8), 383}, // s_mad24 in opencl_std_100
    {IR(54683, 9), 369}, // s_mad_hi in opencl_std_100
    {IR(54702, 10), 371}, // s_mad_sat in opencl_std_100
    {IR(54712, 6), 372}, // s_max in opencl_std_100
    {IR(54724, 6), 374}, // s_min in opencl_std_100
    {IR(54819, 8), 385}, // s_mul24 in opencl_std_100
    {IR(54736, 9), 376}, // s_mul_hi in opencl_std_100
    {IR(54643, 8), 363}, // s_rhadd in opencl_std_100
    {IR(54752, 10), 378}, // s_sub_sat in opencl_std_100
    {IR(54783, 11), 381}, // s_upsample in opencl_std_100
    {IR(55013, 7), 403}, // select in opencl_std_100
    {IR(54970, 8), 398}, // shuffle in opencl_std_100
    {IR(54978, 9), 399}, // shuffle2 in opencl_std_100
    {IR(54514, 5), 349}, // sign in opencl_std_100
    {IR(54082, 4), 303}, // sin in opencl_std_100
    {IR(54086, 7), 304}, // sincos in opencl_std_100
    {IR(54093, 5), 305}, // sinh in opencl_std_100
    {IR(54098, 6), 306}, // sinpi in opencl_std_100
    {IR(54503, 11), 348}, // smoothstep in opencl_std_100
    {IR(54104, 5), 307}, // sqrt in opencl_std_100
    {IR(54498, 5), 347}, // step in opencl_std_100
    {IR(54109, 4), 308}, // tan in opencl_std_100
    {IR(54113, 5), 309}, // tanh in opencl_std_100
    {IR(54118, 6), 310}, // tanpi in opencl_std_100
    {IR(54124, 7), 311}, // tgamma in opencl_std_100
    {IR(54131, 6), 312}, // trunc in opencl_std_100
    {IR(55020, 6), 404}, // u_abs in opencl_std_100
    {IR(55026, 11), 405}, // u_abs_diff in opencl_std_100
    {IR(54619, 10), 360}, // u_add_sat in opencl_std_100
    {IR(54667, 8), 366}, // u_clamp in opencl_std_100
    {IR(54636, 7), 362}, // u_hadd in opencl_std_100
    {IR(54811, 8), 384}, // u_mad24 in opencl_std_100
    {IR(55046, 9), 407}, // u_mad_hi in opencl_std_100
    {IR(54692, 10), 370}, // u_mad_sat in opencl_std_100
    {IR(54718, 6), 373}, // u_max in opencl_std_100
    {IR(54730, 6), 375}, // u_min in opencl_std_100
    {IR(54827, 8), 386}, // u_mul24 in opencl_std_100
    {IR(55037, 9), 406}, // u_mul_hi in opencl_std_100
    {IR(54651, 8), 364}, // u_rhadd in opencl_std_100
    {IR(54762, 10), 379}, // u_sub_sat in opencl_std_100
    {IR(54772, 11), 380}, // u_upsample in opencl_std_100
    {IR(54850, 11), 389}, // vload_half in opencl_std_100
    {IR(54861, 12), 390}, // vload_halfn in opencl_std_100
    {IR(54927, 13), 395}, // vloada_halfn in opencl_std_100
    {IR(54835, 7), 387}, // vloadn in opencl_std_100
    {IR(54873, 12), 391}, // vstore_half in opencl_std_100
    {IR(54885, 14), 392}, // vstore_half_r in opencl_std_100
    {IR(54899, 13), 393}, // vstore_halfn in opencl_std_100
    {IR(54912, 15), 394}, // vstore_halfn_r in opencl_std_100
    {IR(54940, 14), 396}, // vstorea_halfn in opencl_std_100
    {IR(54954, 16), 397}, // vstorea_halfn_r in opencl_std_100
    {IR(54842, 8), 388}, // vstoren in opencl_std_100
    {IR(55072, 17), 409}, // CubeFaceCoordAMD in spv_amd_gcn_shader
    {IR(55055, 17), 408}, // CubeFaceIndexAMD in spv_amd_gcn_shader
    {IR(55089, 8), 410}, // TimeAMD in spv_amd_gcn_shader
    {IR(55166, 9), 414}, // MbcntAMD in spv_amd_shader_ballot
    {IR(55097, 22), 411}, // SwizzleInvocationsAMD in spv_amd_shader_ballot
    {IR(55119, 28), 412}, // SwizzleInvocationsMaskedAMD in spv_amd_shader_ballot
    {IR(55147, 19), 413}, // WriteInvocationAMD in spv_amd_shader_ballot
    {IR(55175, 23), 415}, // InterpolateAtVertexAMD in spv_amd_shader_explicit_vertex_parameter
    {IR(55225, 9), 419}, // FMax3AMD in spv_amd_shader_trinary_minmax
    {IR(55252, 9), 422}, // FMid3AMD in spv_amd_shader_trinary_minmax
    {IR(55198, 9), 416}, // FMin3AMD in spv_amd_shader_trinary_minmax
    {IR(55243, 9), 421}, // SMax3AMD in spv_amd_shader_trinary_minmax
    {IR(55270, 9), 424}, // SMid3AMD in spv_amd_shader_trinary_minmax
    {IR(55216, 9), 418}, // SMin3AMD in spv_amd_shader_trinary_minmax
    {IR(55234, 9), 420}, // UMax3AMD in spv_amd_shader_trinary_minmax
    {IR(55261, 9), 423}, // UMid3AMD in spv_amd_shader_trinary_minmax
    {IR(55207, 9), 417}, // UMin3AMD in spv_amd_shader_trinary_minmax
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
  "ReadOnly\0" // IR(5454, 9)
  "Kernel\0" // IR(5463, 7)
  "WriteOnly\0" // IR(5470, 10)
  "ReadWrite\0" // IR(5480, 10)
  "Logical\0" // IR(5490, 8)
  "Physical32\0" // IR(5498, 11)
  "Addresses\0" // IR(5509, 10)
  "Physical64\0" // IR(5519, 11)
  "PhysicalStorageBuffer64\0" // IR(5530, 24)
  "PhysicalStorageBuffer64EXT\0" // IR(5554, 27)
  "PhysicalStorageBufferAddresses\0" // IR(5581, 31)
  "Position\0" // IR(5612, 9)
  "Shader\0" // IR(5621, 7)
  "PointSize\0" // IR(5628, 10)
  "ClipDistance\0" // IR(5638, 13)
  "CullDistance\0" // IR(5651, 13)
  "VertexId\0" // IR(5664, 9)
  "InstanceId\0" // IR(5673, 11)
  "PrimitiveId\0" // IR(5684, 12)
  "Geometry\0" // IR(5696, 9)
  "Tessellation\0" // IR(5705, 13)
  "RayTracingNV\0" // IR(5718, 13)
  "RayTracingKHR\0" // IR(5731, 14)
  "MeshShadingNV\0" // IR(5745, 14)
  "MeshShadingEXT\0" // IR(5759, 15)
  "InvocationId\0" // IR(5774, 13)
  "Layer\0" // IR(5787, 6)
  "ShaderLayer\0" // IR(5793, 12)
  "ShaderViewportIndexLayerEXT\0" // IR(5805, 28)
  "ViewportIndex\0" // IR(5833, 14)
  "MultiViewport\0" // IR(5847, 14)
  "ShaderViewportIndex\0" // IR(5861, 20)
  "TessLevelOuter\0" // IR(5881, 15)
  "TessLevelInner\0" // IR(5896, 15)
  "TessCoord\0" // IR(5911, 10)
  "PatchVertices\0" // IR(5921, 14)
  "FragCoord\0" // IR(5935, 10)
  "PointCoord\0" // IR(5945, 11)
  "FrontFacing\0" // IR(5956, 12)
  "SampleId\0" // IR(5968, 9)
  "SampleRateShading\0" // IR(5977, 18)
  "SamplePosition\0" // IR(5995, 15)
  "SampleMask\0" // IR(6010, 11)
  "FragDepth\0" // IR(6021, 10)
  "HelperInvocation\0" // IR(6031, 17)
  "NumWorkgroups\0" // IR(6048, 14)
  "WorkgroupSize\0" // IR(6062, 14)
  "WorkgroupId\0" // IR(6076, 12)
  "LocalInvocationId\0" // IR(6088, 18)
  "GlobalInvocationId\0" // IR(6106, 19)
  "LocalInvocationIndex\0" // IR(6125, 21)
  "WorkDim\0" // IR(6146, 8)
  "GlobalSize\0" // IR(6154, 11)
  "EnqueuedWorkgroupSize\0" // IR(6165, 22)
  "GlobalOffset\0" // IR(6187, 13)
  "GlobalLinearId\0" // IR(6200, 15)
  "SubgroupSize\0" // IR(6215, 13)
  "GroupNonUniform\0" // IR(6228, 16)
  "SubgroupBallotKHR\0" // IR(6244, 18)
  "SubgroupMaxSize\0" // IR(6262, 16)
  "NumSubgroups\0" // IR(6278, 13)
  "NumEnqueuedSubgroups\0" // IR(6291, 21)
  "SubgroupId\0" // IR(6312, 11)
  "SubgroupLocalInvocationId\0" // IR(6323, 26)
  "VertexIndex\0" // IR(6349, 12)
  "InstanceIndex\0" // IR(6361, 14)
  "CoreIDARM\0" // IR(6375, 10)
  "CoreBuiltinsARM\0" // IR(6385, 16)
  "CoreCountARM\0" // IR(6401, 13)
  "CoreMaxIDARM\0" // IR(6414, 13)
  "WarpIDARM\0" // IR(6427, 10)
  "WarpMaxIDARM\0" // IR(6437, 13)
  "SubgroupEqMask\0" // IR(6450, 15)
  "SubgroupEqMaskKHR\0" // IR(6465, 18)
  "GroupNonUniformBallot\0" // IR(6483, 22)
  "SubgroupGeMask\0" // IR(6505, 15)
  "SubgroupGeMaskKHR\0" // IR(6520, 18)
  "SubgroupGtMask\0" // IR(6538, 15)
  "SubgroupGtMaskKHR\0" // IR(6553, 18)
  "SubgroupLeMask\0" // IR(6571, 15)
  "SubgroupLeMaskKHR\0" // IR(6586, 18)
  "SubgroupLtMask\0" // IR(6604, 15)
  "SubgroupLtMaskKHR\0" // IR(6619, 18)
  "BaseVertex\0" // IR(6637, 11)
  "DrawParameters\0" // IR(6648, 15)
  "BaseInstance\0" // IR(6663, 13)
  "DrawIndex\0" // IR(6676, 10)
  "PrimitiveShadingRateKHR\0" // IR(6686, 24)
  "FragmentShadingRateKHR\0" // IR(6710, 23)
  "DeviceIndex\0" // IR(6733, 12)
  "DeviceGroup\0" // IR(6745, 12)
  "ViewIndex\0" // IR(6757, 10)
  "MultiView\0" // IR(6767, 10)
  "ShadingRateKHR\0" // IR(6777, 15)
  "TileOffsetQCOM\0" // IR(6792, 15)
  "TileShadingQCOM\0" // IR(6807, 16)
  "TileDimensionQCOM\0" // IR(6823, 18)
  "TileApronSizeQCOM\0" // IR(6841, 18)
  "BaryCoordNoPerspAMD\0" // IR(6859, 20)
  "BaryCoordNoPerspCentroidAMD\0" // IR(6879, 28)
  "BaryCoordNoPerspSampleAMD\0" // IR(6907, 26)
  "BaryCoordSmoothAMD\0" // IR(6933, 19)
  "BaryCoordSmoothCentroidAMD\0" // IR(6952, 27)
  "BaryCoordSmoothSampleAMD\0" // IR(6979, 25)
  "BaryCoordPullModelAMD\0" // IR(7004, 22)
  "FragStencilRefEXT\0" // IR(7026, 18)
  "StencilExportEXT\0" // IR(7044, 17)
  "RemainingRecursionLevelsAMDX\0" // IR(7061, 29)
  "ShaderEnqueueAMDX\0" // IR(7090, 18)
  "ShaderIndexAMDX\0" // IR(7108, 16)
  "SamplerHeapEXT\0" // IR(7124, 15)
  "DescriptorHeapEXT\0" // IR(7139, 18)
  "ResourceHeapEXT\0" // IR(7157, 16)
  "ViewportMaskNV\0" // IR(7173, 15)
  "ShaderViewportMaskNV\0" // IR(7188, 21)
  "SecondaryPositionNV\0" // IR(7209, 20)
  "ShaderStereoViewNV\0" // IR(7229, 19)
  "SecondaryViewportMaskNV\0" // IR(7248, 24)
  "PositionPerViewNV\0" // IR(7272, 18)
  "PerViewAttributesNV\0" // IR(7290, 20)
  "ViewportMaskPerViewNV\0" // IR(7310, 22)
  "FullyCoveredEXT\0" // IR(7332, 16)
  "FragmentFullyCoveredEXT\0" // IR(7348, 24)
  "TaskCountNV\0" // IR(7372, 12)
  "PrimitiveCountNV\0" // IR(7384, 17)
  "PrimitiveIndicesNV\0" // IR(7401, 19)
  "ClipDistancePerViewNV\0" // IR(7420, 22)
  "CullDistancePerViewNV\0" // IR(7442, 22)
  "LayerPerViewNV\0" // IR(7464, 15)
  "MeshViewCountNV\0" // IR(7479, 16)
  "MeshViewIndicesNV\0" // IR(7495, 18)
  "BaryCoordKHR\0" // IR(7513, 13)
  "BaryCoordNV\0" // IR(7526, 12)
  "FragmentBarycentricKHR\0" // IR(7538, 23)
  "BaryCoordNoPerspKHR\0" // IR(7561, 20)
  "BaryCoordNoPerspNV\0" // IR(7581, 19)
  "FragSizeEXT\0" // IR(7600, 12)
  "FragmentSizeNV\0" // IR(7612, 15)
  "FragmentDensityEXT\0" // IR(7627, 19)
  "FragInvocationCountEXT\0" // IR(7646, 23)
  "InvocationsPerPixelNV\0" // IR(7669, 22)
  "PrimitivePointIndicesEXT\0" // IR(7691, 25)
  "PrimitiveLineIndicesEXT\0" // IR(7716, 24)
  "PrimitiveTriangleIndicesEXT\0" // IR(7740, 28)
  "CullPrimitiveEXT\0" // IR(7768, 17)
  "LaunchIdKHR\0" // IR(7785, 12)
  "LaunchIdNV\0" // IR(7797, 11)
  "LaunchSizeKHR\0" // IR(7808, 14)
  "LaunchSizeNV\0" // IR(7822, 13)
  "WorldRayOriginKHR\0" // IR(7835, 18)
  "WorldRayOriginNV\0" // IR(7853, 17)
  "WorldRayDirectionKHR\0" // IR(7870, 21)
  "WorldRayDirectionNV\0" // IR(7891, 20)
  "ObjectRayOriginKHR\0" // IR(7911, 19)
  "ObjectRayOriginNV\0" // IR(7930, 18)
  "ObjectRayDirectionKHR\0" // IR(7948, 22)
  "ObjectRayDirectionNV\0" // IR(7970, 21)
  "RayTminKHR\0" // IR(7991, 11)
  "RayTminNV\0" // IR(8002, 10)
  "RayTmaxKHR\0" // IR(8012, 11)
  "RayTmaxNV\0" // IR(8023, 10)
  "InstanceCustomIndexKHR\0" // IR(8033, 23)
  "InstanceCustomIndexNV\0" // IR(8056, 22)
  "ObjectToWorldKHR\0" // IR(8078, 17)
  "ObjectToWorldNV\0" // IR(8095, 16)
  "WorldToObjectKHR\0" // IR(8111, 17)
  "WorldToObjectNV\0" // IR(8128, 16)
  "HitTNV\0" // IR(8144, 7)
  "HitKindKHR\0" // IR(8151, 11)
  "HitKindNV\0" // IR(8162, 10)
  "CurrentRayTimeNV\0" // IR(8172, 17)
  "RayTracingMotionBlurNV\0" // IR(8189, 23)
  "HitTriangleVertexPositionsKHR\0" // IR(8212, 30)
  "RayTracingPositionFetchKHR\0" // IR(8242, 27)
  "HitMicroTriangleVertexPositionsNV\0" // IR(8269, 34)
  "RayTracingDisplacementMicromapNV\0" // IR(8303, 33)
  "HitMicroTriangleVertexBarycentricsNV\0" // IR(8336, 37)
  "IncomingRayFlagsKHR\0" // IR(8373, 20)
  "IncomingRayFlagsNV\0" // IR(8393, 19)
  "RayGeometryIndexKHR\0" // IR(8412, 20)
  "HitIsSphereNV\0" // IR(8432, 14)
  "RayTracingSpheresGeometryNV\0" // IR(8446, 28)
  "HitIsLSSNV\0" // IR(8474, 11)
  "RayTracingLinearSweptSpheresGeometryNV\0" // IR(8485, 39)
  "HitSpherePositionNV\0" // IR(8524, 20)
  "WarpsPerSMNV\0" // IR(8544, 13)
  "ShaderSMBuiltinsNV\0" // IR(8557, 19)
  "SMCountNV\0" // IR(8576, 10)
  "WarpIDNV\0" // IR(8586, 9)
  "SMIDNV\0" // IR(8595, 7)
  "HitLSSPositionsNV\0" // IR(8602, 18)
  "HitKindFrontFacingMicroTriangleNV\0" // IR(8620, 34)
  "HitKindBackFacingMicroTriangleNV\0" // IR(8654, 33)
  "HitSphereRadiusNV\0" // IR(8687, 18)
  "HitLSSRadiiNV\0" // IR(8705, 14)
  "ClusterIDNV\0" // IR(8719, 12)
  "RayTracingClusterAccelerationStructureNV\0" // IR(8731, 41)
  "CullMaskKHR\0" // IR(8772, 12)
  "RayCullMaskKHR\0" // IR(8784, 15)
  "Matrix\0" // IR(8799, 7)
  "Linkage\0" // IR(8806, 8)
  "Vector16\0" // IR(8814, 9)
  "Float16Buffer\0" // IR(8823, 14)
  "Float16\0" // IR(8837, 8)
  "Float64\0" // IR(8845, 8)
  "Int64\0" // IR(8853, 6)
  "Int64Atomics\0" // IR(8859, 13)
  "ImageBasic\0" // IR(8872, 11)
  "ImageReadWrite\0" // IR(8883, 15)
  "ImageMipmap\0" // IR(8898, 12)
  "Pipes\0" // IR(8910, 6)
  "Groups\0" // IR(8916, 7)
  "DeviceEnqueue\0" // IR(8923, 14)
  "LiteralSampler\0" // IR(8937, 15)
  "AtomicStorage\0" // IR(8952, 14)
  "Int16\0" // IR(8966, 6)
  "TessellationPointSize\0" // IR(8972, 22)
  "GeometryPointSize\0" // IR(8994, 18)
  "ImageGatherExtended\0" // IR(9012, 20)
  "StorageImageMultisample\0" // IR(9032, 24)
  "UniformBufferArrayDynamicIndexing\0" // IR(9056, 34)
  "SampledImageArrayDynamicIndexing\0" // IR(9090, 33)
  "StorageBufferArrayDynamicIndexing\0" // IR(9123, 34)
  "StorageImageArrayDynamicIndexing\0" // IR(9157, 33)
  "ImageCubeArray\0" // IR(9190, 15)
  "SampledCubeArray\0" // IR(9205, 17)
  "ImageRect\0" // IR(9222, 10)
  "SampledRect\0" // IR(9232, 12)
  "GenericPointer\0" // IR(9244, 15)
  "Int8\0" // IR(9259, 5)
  "InputAttachment\0" // IR(9264, 16)
  "SparseResidency\0" // IR(9280, 16)
  "MinLod\0" // IR(9296, 7)
  "Sampled1D\0" // IR(9303, 10)
  "Image1D\0" // IR(9313, 8)
  "SampledBuffer\0" // IR(9321, 14)
  "ImageBuffer\0" // IR(9335, 12)
  "ImageMSArray\0" // IR(9347, 13)
  "StorageImageExtendedFormats\0" // IR(9360, 28)
  "ImageQuery\0" // IR(9388, 11)
  "DerivativeControl\0" // IR(9399, 18)
  "InterpolationFunction\0" // IR(9417, 22)
  "TransformFeedback\0" // IR(9439, 18)
  "GeometryStreams\0" // IR(9457, 16)
  "StorageImageReadWithoutFormat\0" // IR(9473, 30)
  "StorageImageWriteWithoutFormat\0" // IR(9503, 31)
  "SubgroupDispatch\0" // IR(9534, 17)
  "NamedBarrier\0" // IR(9551, 13)
  "PipeStorage\0" // IR(9564, 12)
  "GroupNonUniformVote\0" // IR(9576, 20)
  "GroupNonUniformArithmetic\0" // IR(9596, 26)
  "GroupNonUniformShuffle\0" // IR(9622, 23)
  "GroupNonUniformShuffleRelative\0" // IR(9645, 31)
  "GroupNonUniformClustered\0" // IR(9676, 25)
  "GroupNonUniformQuad\0" // IR(9701, 20)
  "UniformDecoration\0" // IR(9721, 18)
  "TileImageColorReadAccessEXT\0" // IR(9739, 28)
  "TileImageDepthReadAccessEXT\0" // IR(9767, 28)
  "TileImageStencilReadAccessEXT\0" // IR(9795, 30)
  "TensorsARM\0" // IR(9825, 11)
  "StorageTensorArrayDynamicIndexingARM\0" // IR(9836, 37)
  "StorageTensorArrayNonUniformIndexingARM\0" // IR(9873, 40)
  "GraphARM\0" // IR(9913, 9)
  "CooperativeMatrixLayoutsARM\0" // IR(9922, 28)
  "Float8EXT\0" // IR(9950, 10)
  "Float8CooperativeMatrixEXT\0" // IR(9960, 27)
  "CooperativeMatrixKHR\0" // IR(9987, 21)
  "WorkgroupMemoryExplicitLayoutKHR\0" // IR(10008, 33)
  "WorkgroupMemoryExplicitLayout8BitAccessKHR\0" // IR(10041, 43)
  "WorkgroupMemoryExplicitLayout16BitAccessKHR\0" // IR(10084, 44)
  "SubgroupVoteKHR\0" // IR(10128, 16)
  "StorageBuffer16BitAccess\0" // IR(10144, 25)
  "StorageUniformBufferBlock16\0" // IR(10169, 28)
  "UniformAndStorageBuffer16BitAccess\0" // IR(10197, 35)
  "StorageUniform16\0" // IR(10232, 17)
  "StoragePushConstant16\0" // IR(10249, 22)
  "StorageInputOutput16\0" // IR(10271, 21)
  "VariablePointersStorageBuffer\0" // IR(10292, 30)
  "VariablePointers\0" // IR(10322, 17)
  "AtomicStorageOps\0" // IR(10339, 17)
  "SampleMaskPostDepthCoverage\0" // IR(10356, 28)
  "StorageBuffer8BitAccess\0" // IR(10384, 24)
  "UniformAndStorageBuffer8BitAccess\0" // IR(10408, 34)
  "StoragePushConstant8\0" // IR(10442, 21)
  "DenormPreserve\0" // IR(10463, 15)
  "DenormFlushToZero\0" // IR(10478, 18)
  "SignedZeroInfNanPreserve\0" // IR(10496, 25)
  "RoundingModeRTE\0" // IR(10521, 16)
  "RoundingModeRTZ\0" // IR(10537, 16)
  "RayQueryProvisionalKHR\0" // IR(10553, 23)
  "RayQueryKHR\0" // IR(10576, 12)
  "UntypedPointersKHR\0" // IR(10588, 19)
  "RayTraversalPrimitiveCullingKHR\0" // IR(10607, 32)
  "TextureSampleWeightedQCOM\0" // IR(10639, 26)
  "TextureBoxFilterQCOM\0" // IR(10665, 21)
  "TextureBlockMatchQCOM\0" // IR(10686, 22)
  "CooperativeMatrixConversionQCOM\0" // IR(10708, 32)
  "TextureBlockMatch2QCOM\0" // IR(10740, 23)
  "Float16ImageAMD\0" // IR(10763, 16)
  "ImageGatherBiasLodAMD\0" // IR(10779, 22)
  "FragmentMaskAMD\0" // IR(10801, 16)
  "ImageReadWriteLodAMD\0" // IR(10817, 21)
  "Int64ImageEXT\0" // IR(10838, 14)
  "ShaderClockKHR\0" // IR(10852, 15)
  "QuadControlKHR\0" // IR(10867, 15)
  "Int4TypeINTEL\0" // IR(10882, 14)
  "Int4CooperativeMatrixINTEL\0" // IR(10896, 27)
  "BFloat16TypeKHR\0" // IR(10923, 16)
  "BFloat16DotProductKHR\0" // IR(10939, 22)
  "BFloat16CooperativeMatrixKHR\0" // IR(10961, 29)
  "SampleMaskOverrideCoverageNV\0" // IR(10990, 29)
  "GeometryShaderPassthroughNV\0" // IR(11019, 28)
  "ShaderViewportIndexLayerNV\0" // IR(11047, 27)
  "ImageFootprintNV\0" // IR(11074, 17)
  "FragmentBarycentricNV\0" // IR(11091, 22)
  "ComputeDerivativeGroupQuadsKHR\0" // IR(11113, 31)
  "ComputeDerivativeGroupQuadsNV\0" // IR(11144, 30)
  "ShadingRateNV\0" // IR(11174, 14)
  "GroupNonUniformPartitionedEXT\0" // IR(11188, 30)
  "GroupNonUniformPartitionedNV\0" // IR(11218, 29)
  "ShaderNonUniform\0" // IR(11247, 17)
  "ShaderNonUniformEXT\0" // IR(11264, 20)
  "RuntimeDescriptorArray\0" // IR(11284, 23)
  "RuntimeDescriptorArrayEXT\0" // IR(11307, 26)
  "InputAttachmentArrayDynamicIndexing\0" // IR(11333, 36)
  "InputAttachmentArrayDynamicIndexingEXT\0" // IR(11369, 39)
  "UniformTexelBufferArrayDynamicIndexing\0" // IR(11408, 39)
  "UniformTexelBufferArrayDynamicIndexingEXT\0" // IR(11447, 42)
  "StorageTexelBufferArrayDynamicIndexing\0" // IR(11489, 39)
  "StorageTexelBufferArrayDynamicIndexingEXT\0" // IR(11528, 42)
  "UniformBufferArrayNonUniformIndexing\0" // IR(11570, 37)
  "UniformBufferArrayNonUniformIndexingEXT\0" // IR(11607, 40)
  "SampledImageArrayNonUniformIndexing\0" // IR(11647, 36)
  "SampledImageArrayNonUniformIndexingEXT\0" // IR(11683, 39)
  "StorageBufferArrayNonUniformIndexing\0" // IR(11722, 37)
  "StorageBufferArrayNonUniformIndexingEXT\0" // IR(11759, 40)
  "StorageImageArrayNonUniformIndexing\0" // IR(11799, 36)
  "StorageImageArrayNonUniformIndexingEXT\0" // IR(11835, 39)
  "InputAttachmentArrayNonUniformIndexing\0" // IR(11874, 39)
  "InputAttachmentArrayNonUniformIndexingEXT\0" // IR(11913, 42)
  "UniformTexelBufferArrayNonUniformIndexing\0" // IR(11955, 42)
  "UniformTexelBufferArrayNonUniformIndexingEXT\0" // IR(11997, 45)
  "StorageTexelBufferArrayNonUniformIndexing\0" // IR(12042, 42)
  "StorageTexelBufferArrayNonUniformIndexingEXT\0" // IR(12084, 45)
  "VulkanMemoryModel\0" // IR(12129, 18)
  "VulkanMemoryModelKHR\0" // IR(12147, 21)
  "VulkanMemoryModelDeviceScope\0" // IR(12168, 29)
  "VulkanMemoryModelDeviceScopeKHR\0" // IR(12197, 32)
  "PhysicalStorageBufferAddressesEXT\0" // IR(12229, 34)
  "ComputeDerivativeGroupLinearKHR\0" // IR(12263, 32)
  "ComputeDerivativeGroupLinearNV\0" // IR(12295, 31)
  "RayTracingProvisionalKHR\0" // IR(12326, 25)
  "CooperativeMatrixNV\0" // IR(12351, 20)
  "FragmentShaderSampleInterlockEXT\0" // IR(12371, 33)
  "FragmentShaderShadingRateInterlockEXT\0" // IR(12404, 38)
  "FragmentShaderPixelInterlockEXT\0" // IR(12442, 32)
  "DemoteToHelperInvocation\0" // IR(12474, 25)
  "DemoteToHelperInvocationEXT\0" // IR(12499, 28)
  "DisplacementMicromapNV\0" // IR(12527, 23)
  "RayTracingOpacityMicromapEXT\0" // IR(12550, 29)
  "ShaderInvocationReorderNV\0" // IR(12579, 26)
  "ShaderInvocationReorderEXT\0" // IR(12605, 27)
  "BindlessTextureNV\0" // IR(12632, 18)
  "RayQueryPositionFetchKHR\0" // IR(12650, 25)
  "CooperativeVectorNV\0" // IR(12675, 20)
  "AtomicFloat16VectorNV\0" // IR(12695, 22)
  "RawAccessChainsNV\0" // IR(12717, 18)
  "PushConstantBanksNV\0" // IR(12735, 20)
  "LongVectorEXT\0" // IR(12755, 14)
  "Shader64BitIndexingEXT\0" // IR(12769, 23)
  "CooperativeMatrixReductionsNV\0" // IR(12792, 30)
  "CooperativeMatrixConversionsNV\0" // IR(12822, 31)
  "CooperativeMatrixPerElementOperationsNV\0" // IR(12853, 40)
  "CooperativeMatrixTensorAddressingNV\0" // IR(12893, 36)
  "CooperativeMatrixBlockLoadsNV\0" // IR(12929, 30)
  "CooperativeVectorTrainingNV\0" // IR(12959, 28)
  "TensorAddressingNV\0" // IR(12987, 19)
  "SubgroupShuffleINTEL\0" // IR(13006, 21)
  "SubgroupBufferBlockIOINTEL\0" // IR(13027, 27)
  "SubgroupImageBlockIOINTEL\0" // IR(13054, 26)
  "SubgroupImageMediaBlockIOINTEL\0" // IR(13080, 31)
  "RoundToInfinityINTEL\0" // IR(13111, 21)
  "FloatingPointModeINTEL\0" // IR(13132, 23)
  "IntegerFunctions2INTEL\0" // IR(13155, 23)
  "FunctionPointersINTEL\0" // IR(13178, 22)
  "IndirectReferencesINTEL\0" // IR(13200, 24)
  "AsmINTEL\0" // IR(13224, 9)
  "AtomicFloat32MinMaxEXT\0" // IR(13233, 23)
  "AtomicFloat64MinMaxEXT\0" // IR(13256, 23)
  "AtomicFloat16MinMaxEXT\0" // IR(13279, 23)
  "VectorComputeINTEL\0" // IR(13302, 19)
  "VectorAnyINTEL\0" // IR(13321, 15)
  "ExpectAssumeKHR\0" // IR(13336, 16)
  "SubgroupAvcMotionEstimationINTEL\0" // IR(13352, 33)
  "SubgroupAvcMotionEstimationIntraINTEL\0" // IR(13385, 38)
  "SubgroupAvcMotionEstimationChromaINTEL\0" // IR(13423, 39)
  "VariableLengthArrayINTEL\0" // IR(13462, 25)
  "FunctionFloatControlINTEL\0" // IR(13487, 26)
  "FPGAMemoryAttributesALTERA\0" // IR(13513, 27)
  "FPGAMemoryAttributesINTEL\0" // IR(13540, 26)
  "FPFastMathModeINTEL\0" // IR(13566, 20)
  "ArbitraryPrecisionIntegersALTERA\0" // IR(13586, 33)
  "ArbitraryPrecisionIntegersINTEL\0" // IR(13619, 32)
  "ArbitraryPrecisionFloatingPointALTERA\0" // IR(13651, 38)
  "ArbitraryPrecisionFloatingPointINTEL\0" // IR(13689, 37)
  "UnstructuredLoopControlsINTEL\0" // IR(13726, 30)
  "FPGALoopControlsALTERA\0" // IR(13756, 23)
  "FPGALoopControlsINTEL\0" // IR(13779, 22)
  "KernelAttributesINTEL\0" // IR(13801, 22)
  "FPGAKernelAttributesINTEL\0" // IR(13823, 26)
  "FPGAMemoryAccessesALTERA\0" // IR(13849, 25)
  "FPGAMemoryAccessesINTEL\0" // IR(13874, 24)
  "FPGAClusterAttributesALTERA\0" // IR(13898, 28)
  "FPGAClusterAttributesINTEL\0" // IR(13926, 27)
  "LoopFuseALTERA\0" // IR(13953, 15)
  "LoopFuseINTEL\0" // IR(13968, 14)
  "FPGADSPControlALTERA\0" // IR(13982, 21)
  "FPGADSPControlINTEL\0" // IR(14003, 20)
  "MemoryAccessAliasingINTEL\0" // IR(14023, 26)
  "FPGAInvocationPipeliningAttributesALTERA\0" // IR(14049, 41)
  "FPGAInvocationPipeliningAttributesINTEL\0" // IR(14090, 40)
  "FPGABufferLocationALTERA\0" // IR(14130, 25)
  "FPGABufferLocationINTEL\0" // IR(14155, 24)
  "ArbitraryPrecisionFixedPointALTERA\0" // IR(14179, 35)
  "ArbitraryPrecisionFixedPointINTEL\0" // IR(14214, 34)
  "USMStorageClassesALTERA\0" // IR(14248, 24)
  "USMStorageClassesINTEL\0" // IR(14272, 23)
  "RuntimeAlignedAttributeALTERA\0" // IR(14295, 30)
  "RuntimeAlignedAttributeINTEL\0" // IR(14325, 29)
  "IOPipesALTERA\0" // IR(14354, 14)
  "IOPipesINTEL\0" // IR(14368, 13)
  "BlockingPipesALTERA\0" // IR(14381, 20)
  "BlockingPipesINTEL\0" // IR(14401, 19)
  "FPGARegALTERA\0" // IR(14420, 14)
  "FPGARegINTEL\0" // IR(14434, 13)
  "DotProductInputAll\0" // IR(14447, 19)
  "DotProductInputAllKHR\0" // IR(14466, 22)
  "DotProductInput4x8Bit\0" // IR(14488, 22)
  "DotProductInput4x8BitKHR\0" // IR(14510, 25)
  "DotProductInput4x8BitPacked\0" // IR(14535, 28)
  "DotProductInput4x8BitPackedKHR\0" // IR(14563, 31)
  "DotProduct\0" // IR(14594, 11)
  "DotProductKHR\0" // IR(14605, 14)
  "ReplicatedCompositesEXT\0" // IR(14619, 24)
  "BitInstructions\0" // IR(14643, 16)
  "GroupNonUniformRotateKHR\0" // IR(14659, 25)
  "FloatControls2\0" // IR(14684, 15)
  "FMAKHR\0" // IR(14699, 7)
  "AtomicFloat32AddEXT\0" // IR(14706, 20)
  "AtomicFloat64AddEXT\0" // IR(14726, 20)
  "LongCompositesINTEL\0" // IR(14746, 20)
  "OptNoneEXT\0" // IR(14766, 11)
  "OptNoneINTEL\0" // IR(14777, 13)
  "AtomicFloat16AddEXT\0" // IR(14790, 20)
  "DebugInfoModuleINTEL\0" // IR(14810, 21)
  "BFloat16ConversionINTEL\0" // IR(14831, 24)
  "SplitBarrierINTEL\0" // IR(14855, 18)
  "ArithmeticFenceEXT\0" // IR(14873, 19)
  "FPGAClusterAttributesV2ALTERA\0" // IR(14892, 30)
  "FPGAClusterAttributesV2INTEL\0" // IR(14922, 29)
  "FPGAKernelAttributesv2INTEL\0" // IR(14951, 28)
  "TaskSequenceALTERA\0" // IR(14979, 19)
  "TaskSequenceINTEL\0" // IR(14998, 18)
  "FPMaxErrorINTEL\0" // IR(15016, 16)
  "FPGALatencyControlALTERA\0" // IR(15032, 25)
  "FPGALatencyControlINTEL\0" // IR(15057, 24)
  "FPGAArgumentInterfacesALTERA\0" // IR(15081, 29)
  "FPGAArgumentInterfacesINTEL\0" // IR(15110, 28)
  "GlobalVariableHostAccessINTEL\0" // IR(15138, 30)
  "GlobalVariableFPGADecorationsALTERA\0" // IR(15168, 36)
  "GlobalVariableFPGADecorationsINTEL\0" // IR(15204, 35)
  "SubgroupBufferPrefetchINTEL\0" // IR(15239, 28)
  "Subgroup2DBlockIOINTEL\0" // IR(15267, 23)
  "Subgroup2DBlockTransformINTEL\0" // IR(15290, 30)
  "Subgroup2DBlockTransposeINTEL\0" // IR(15320, 30)
  "SubgroupMatrixMultiplyAccumulateINTEL\0" // IR(15350, 38)
  "TernaryBitwiseFunctionINTEL\0" // IR(15388, 28)
  "UntypedVariableLengthArrayINTEL\0" // IR(15416, 32)
  "SpecConditionalINTEL\0" // IR(15448, 21)
  "FunctionVariantsINTEL\0" // IR(15469, 22)
  "GroupUniformArithmeticKHR\0" // IR(15491, 26)
  "TensorFloat32RoundingINTEL\0" // IR(15517, 27)
  "MaskedGatherScatterINTEL\0" // IR(15544, 25)
  "CacheControlsINTEL\0" // IR(15569, 19)
  "RegisterLimitsINTEL\0" // IR(15588, 20)
  "BindlessImagesINTEL\0" // IR(15608, 20)
  "Unspecified\0" // IR(15628, 12)
  "Address\0" // IR(15640, 8)
  "Boolean\0" // IR(15648, 8)
  "Float\0" // IR(15656, 6)
  "Signed\0" // IR(15662, 7)
  "SignedChar\0" // IR(15669, 11)
  "Unsigned\0" // IR(15680, 9)
  "UnsignedChar\0" // IR(15689, 13)
  "Class\0" // IR(15702, 6)
  "Structure\0" // IR(15708, 10)
  "Union\0" // IR(15718, 6)
  "ImportedModule\0" // IR(15724, 15)
  "ImportedDeclaration\0" // IR(15739, 20)
  "None\0" // IR(15759, 5)
  "FlagIsProtected\0" // IR(15764, 16)
  "FlagIsPrivate\0" // IR(15780, 14)
  "FlagIsPublic\0" // IR(15794, 13)
  "FlagIsLocal\0" // IR(15807, 12)
  "FlagIsDefinition\0" // IR(15819, 17)
  "FlagFwdDecl\0" // IR(15836, 12)
  "FlagArtificial\0" // IR(15848, 15)
  "FlagExplicit\0" // IR(15863, 13)
  "FlagPrototyped\0" // IR(15876, 15)
  "FlagObjectPointer\0" // IR(15891, 18)
  "FlagStaticMember\0" // IR(15909, 17)
  "FlagIndirectVariable\0" // IR(15926, 21)
  "FlagLValueReference\0" // IR(15947, 20)
  "FlagRValueReference\0" // IR(15967, 20)
  "FlagIsOptimized\0" // IR(15987, 16)
  "FlagIsEnumClass\0" // IR(16003, 16)
  "FlagTypePassByValue\0" // IR(16019, 20)
  "FlagTypePassByReference\0" // IR(16039, 24)
  "Deref\0" // IR(16063, 6)
  "Plus\0" // IR(16069, 5)
  "Minus\0" // IR(16074, 6)
  "SPV_OPERAND_TYPE_LITERAL_INTEGER\0" // IR(16080, 33)
  "PlusUconst\0" // IR(16113, 11)
  "BitPiece\0" // IR(16124, 9)
  "Swap\0" // IR(16133, 5)
  "Xderef\0" // IR(16138, 7)
  "StackValue\0" // IR(16145, 11)
  "Constu\0" // IR(16156, 7)
  "Fragment\0" // IR(16163, 9)
  "ConstType\0" // IR(16172, 10)
  "VolatileType\0" // IR(16182, 13)
  "RestrictType\0" // IR(16195, 13)
  "AtomicType\0" // IR(16208, 11)
  "Float16NV\0" // IR(16219, 10)
  "Float32NV\0" // IR(16229, 10)
  "Float64NV\0" // IR(16239, 10)
  "SignedInt8NV\0" // IR(16249, 13)
  "SignedInt16NV\0" // IR(16262, 14)
  "SignedInt32NV\0" // IR(16276, 14)
  "SignedInt64NV\0" // IR(16290, 14)
  "UnsignedInt8NV\0" // IR(16304, 15)
  "UnsignedInt16NV\0" // IR(16319, 16)
  "UnsignedInt32NV\0" // IR(16335, 16)
  "UnsignedInt64NV\0" // IR(16351, 16)
  "SignedInt8PackedNV\0" // IR(16367, 19)
  "UnsignedInt8PackedNV\0" // IR(16386, 21)
  "FloatE4M3NV\0" // IR(16407, 12)
  "FloatE5M2NV\0" // IR(16419, 12)
  "RowMajorKHR\0" // IR(16431, 12)
  "ColumnMajorKHR\0" // IR(16443, 15)
  "RowBlockedInterleavedARM\0" // IR(16458, 25)
  "ColumnBlockedInterleavedARM\0" // IR(16483, 28)
  "NoneKHR\0" // IR(16511, 8)
  "MatrixASignedComponentsKHR\0" // IR(16519, 27)
  "MatrixBSignedComponentsKHR\0" // IR(16546, 27)
  "MatrixCSignedComponentsKHR\0" // IR(16573, 27)
  "MatrixResultSignedComponentsKHR\0" // IR(16600, 32)
  "SaturatingAccumulationKHR\0" // IR(16632, 26)
  "Row\0" // IR(16658, 4)
  "Column\0" // IR(16662, 7)
  "2x2\0" // IR(16669, 4)
  "MatrixAKHR\0" // IR(16673, 11)
  "MatrixBKHR\0" // IR(16684, 11)
  "MatrixAccumulatorKHR\0" // IR(16695, 21)
  "RowMajorNV\0" // IR(16716, 11)
  "ColumnMajorNV\0" // IR(16727, 14)
  "InferencingOptimalNV\0" // IR(16741, 21)
  "TrainingOptimalNV\0" // IR(16762, 18)
  "RelaxedPrecision\0" // IR(16780, 17)
  "SpecId\0" // IR(16797, 7)
  "Block\0" // IR(16804, 6)
  "BufferBlock\0" // IR(16810, 12)
  "RowMajor\0" // IR(16822, 9)
  "ColMajor\0" // IR(16831, 9)
  "ArrayStride\0" // IR(16840, 12)
  "MatrixStride\0" // IR(16852, 13)
  "GLSLShared\0" // IR(16865, 11)
  "GLSLPacked\0" // IR(16876, 11)
  "CPacked\0" // IR(16887, 8)
  "SPV_OPERAND_TYPE_BUILT_IN\0" // IR(16895, 26)
  "BuiltIn\0" // IR(16921, 8)
  "NoPerspective\0" // IR(16929, 14)
  "Flat\0" // IR(16943, 5)
  "Patch\0" // IR(16948, 6)
  "Centroid\0" // IR(16954, 9)
  "Sample\0" // IR(16963, 7)
  "Invariant\0" // IR(16970, 10)
  "Restrict\0" // IR(16980, 9)
  "Aliased\0" // IR(16989, 8)
  "Volatile\0" // IR(16997, 9)
  "Constant\0" // IR(17006, 9)
  "Coherent\0" // IR(17015, 9)
  "NonWritable\0" // IR(17024, 12)
  "NonReadable\0" // IR(17036, 12)
  "Uniform\0" // IR(17048, 8)
  "SPV_OPERAND_TYPE_SCOPE_ID\0" // IR(17056, 26)
  "UniformId\0" // IR(17082, 10)
  "SaturatedConversion\0" // IR(17092, 20)
  "Stream\0" // IR(17112, 7)
  "Location\0" // IR(17119, 9)
  "Component\0" // IR(17128, 10)
  "Index\0" // IR(17138, 6)
  "Binding\0" // IR(17144, 8)
  "DescriptorSet\0" // IR(17152, 14)
  "Offset\0" // IR(17166, 7)
  "XfbBuffer\0" // IR(17173, 10)
  "XfbStride\0" // IR(17183, 10)
  "SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE\0" // IR(17193, 46)
  "FuncParamAttr\0" // IR(17239, 14)
  "SPV_OPERAND_TYPE_FP_ROUNDING_MODE\0" // IR(17253, 34)
  "FPRoundingMode\0" // IR(17287, 15)
  "SPV_OPERAND_TYPE_FP_FAST_MATH_MODE\0" // IR(17302, 35)
  "FPFastMathMode\0" // IR(17337, 15)
  "SPV_OPERAND_TYPE_LITERAL_STRING\0" // IR(17352, 32)
  "SPV_OPERAND_TYPE_LINKAGE_TYPE\0" // IR(17384, 30)
  "LinkageAttributes\0" // IR(17414, 18)
  "NoContraction\0" // IR(17432, 14)
  "InputAttachmentIndex\0" // IR(17446, 21)
  "Alignment\0" // IR(17467, 10)
  "MaxByteOffset\0" // IR(17477, 14)
  "SPV_OPERAND_TYPE_ID\0" // IR(17491, 20)
  "AlignmentId\0" // IR(17511, 12)
  "MaxByteOffsetId\0" // IR(17523, 16)
  "SaturatedToLargestFloat8NormalConversionEXT\0" // IR(17539, 44)
  "NoSignedWrap\0" // IR(17583, 13)
  "NoUnsignedWrap\0" // IR(17596, 15)
  "WeightTextureQCOM\0" // IR(17611, 18)
  "BlockMatchTextureQCOM\0" // IR(17629, 22)
  "BlockMatchSamplerQCOM\0" // IR(17651, 22)
  "ExplicitInterpAMD\0" // IR(17673, 18)
  "NodeSharesPayloadLimitsWithAMDX\0" // IR(17691, 32)
  "NodeMaxPayloadsAMDX\0" // IR(17723, 20)
  "TrackFinishWritingAMDX\0" // IR(17743, 23)
  "PayloadNodeNameAMDX\0" // IR(17766, 20)
  "PayloadNodeBaseIndexAMDX\0" // IR(17786, 25)
  "PayloadNodeSparseArrayAMDX\0" // IR(17811, 27)
  "PayloadNodeArraySizeAMDX\0" // IR(17838, 25)
  "PayloadDispatchIndirectAMDX\0" // IR(17863, 28)
  "ArrayStrideIdEXT\0" // IR(17891, 17)
  "OffsetIdEXT\0" // IR(17908, 12)
  "OverrideCoverageNV\0" // IR(17920, 19)
  "PassthroughNV\0" // IR(17939, 14)
  "ViewportRelativeNV\0" // IR(17953, 19)
  "SecondaryViewportRelativeNV\0" // IR(17972, 28)
  "PerPrimitiveEXT\0" // IR(18000, 16)
  "PerPrimitiveNV\0" // IR(18016, 15)
  "PerViewNV\0" // IR(18031, 10)
  "PerTaskNV\0" // IR(18041, 10)
  "PerVertexKHR\0" // IR(18051, 13)
  "PerVertexNV\0" // IR(18064, 12)
  "NonUniform\0" // IR(18076, 11)
  "NonUniformEXT\0" // IR(18087, 14)
  "RestrictPointer\0" // IR(18101, 16)
  "RestrictPointerEXT\0" // IR(18117, 19)
  "AliasedPointer\0" // IR(18136, 15)
  "AliasedPointerEXT\0" // IR(18151, 18)
  "MemberOffsetNV\0" // IR(18169, 15)
  "HitObjectShaderRecordBufferNV\0" // IR(18184, 30)
  "HitObjectShaderRecordBufferEXT\0" // IR(18214, 31)
  "BankNV\0" // IR(18245, 7)
  "BindlessSamplerNV\0" // IR(18252, 18)
  "BindlessImageNV\0" // IR(18270, 16)
  "BoundSamplerNV\0" // IR(18286, 15)
  "BoundImageNV\0" // IR(18301, 13)
  "SIMTCallINTEL\0" // IR(18314, 14)
  "ReferencedIndirectlyINTEL\0" // IR(18328, 26)
  "ClobberINTEL\0" // IR(18354, 13)
  "SideEffectsINTEL\0" // IR(18367, 17)
  "VectorComputeVariableINTEL\0" // IR(18384, 27)
  "FuncParamIOKindINTEL\0" // IR(18411, 21)
  "VectorComputeFunctionINTEL\0" // IR(18432, 27)
  "StackCallINTEL\0" // IR(18459, 15)
  "GlobalVariableOffsetINTEL\0" // IR(18474, 26)
  "CounterBuffer\0" // IR(18500, 14)
  "HlslCounterBufferGOOGLE\0" // IR(18514, 24)
  "UserSemantic\0" // IR(18538, 13)
  "HlslSemanticGOOGLE\0" // IR(18551, 19)
  "UserTypeGOOGLE\0" // IR(18570, 15)
  "FunctionRoundingModeINTEL\0" // IR(18585, 26)
  "SPV_OPERAND_TYPE_FPDENORM_MODE\0" // IR(18611, 31)
  "FunctionDenormModeINTEL\0" // IR(18642, 24)
  "RegisterALTERA\0" // IR(18666, 15)
  "RegisterINTEL\0" // IR(18681, 14)
  "MemoryALTERA\0" // IR(18695, 13)
  "MemoryINTEL\0" // IR(18708, 12)
  "NumbanksALTERA\0" // IR(18720, 15)
  "NumbanksINTEL\0" // IR(18735, 14)
  "BankwidthALTERA\0" // IR(18749, 16)
  "BankwidthINTEL\0" // IR(18765, 15)
  "MaxPrivateCopiesALTERA\0" // IR(18780, 23)
  "MaxPrivateCopiesINTEL\0" // IR(18803, 22)
  "SinglepumpALTERA\0" // IR(18825, 17)
  "SinglepumpINTEL\0" // IR(18842, 16)
  "DoublepumpALTERA\0" // IR(18858, 17)
  "DoublepumpINTEL\0" // IR(18875, 16)
  "MaxReplicatesALTERA\0" // IR(18891, 20)
  "MaxReplicatesINTEL\0" // IR(18911, 19)
  "SimpleDualPortALTERA\0" // IR(18930, 21)
  "SimpleDualPortINTEL\0" // IR(18951, 20)
  "MergeALTERA\0" // IR(18971, 12)
  "MergeINTEL\0" // IR(18983, 11)
  "SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER\0" // IR(18994, 42)
  "BankBitsALTERA\0" // IR(19036, 15)
  "BankBitsINTEL\0" // IR(19051, 14)
  "ForcePow2DepthALTERA\0" // IR(19065, 21)
  "ForcePow2DepthINTEL\0" // IR(19086, 20)
  "StridesizeALTERA\0" // IR(19106, 17)
  "StridesizeINTEL\0" // IR(19123, 16)
  "WordsizeALTERA\0" // IR(19139, 15)
  "WordsizeINTEL\0" // IR(19154, 14)
  "TrueDualPortALTERA\0" // IR(19168, 19)
  "TrueDualPortINTEL\0" // IR(19187, 18)
  "BurstCoalesceALTERA\0" // IR(19205, 20)
  "BurstCoalesceINTEL\0" // IR(19225, 19)
  "CacheSizeALTERA\0" // IR(19244, 16)
  "CacheSizeINTEL\0" // IR(19260, 15)
  "DontStaticallyCoalesceALTERA\0" // IR(19275, 29)
  "DontStaticallyCoalesceINTEL\0" // IR(19304, 28)
  "PrefetchALTERA\0" // IR(19332, 15)
  "PrefetchINTEL\0" // IR(19347, 14)
  "StallEnableALTERA\0" // IR(19361, 18)
  "StallEnableINTEL\0" // IR(19379, 17)
  "FuseLoopsInFunctionALTERA\0" // IR(19396, 26)
  "FuseLoopsInFunctionINTEL\0" // IR(19422, 25)
  "MathOpDSPModeALTERA\0" // IR(19447, 20)
  "MathOpDSPModeINTEL\0" // IR(19467, 19)
  "AliasScopeINTEL\0" // IR(19486, 16)
  "NoAliasINTEL\0" // IR(19502, 13)
  "InitiationIntervalALTERA\0" // IR(19515, 25)
  "InitiationIntervalINTEL\0" // IR(19540, 24)
  "MaxConcurrencyALTERA\0" // IR(19564, 21)
  "MaxConcurrencyINTEL\0" // IR(19585, 20)
  "PipelineEnableALTERA\0" // IR(19605, 21)
  "PipelineEnableINTEL\0" // IR(19626, 20)
  "BufferLocationALTERA\0" // IR(19646, 21)
  "BufferLocationINTEL\0" // IR(19667, 20)
  "IOPipeStorageALTERA\0" // IR(19687, 20)
  "IOPipeStorageINTEL\0" // IR(19707, 19)
  "SPV_OPERAND_TYPE_FPOPERATION_MODE\0" // IR(19726, 34)
  "FunctionFloatingPointModeINTEL\0" // IR(19760, 31)
  "SingleElementVectorINTEL\0" // IR(19791, 25)
  "VectorComputeCallableFunctionINTEL\0" // IR(19816, 35)
  "MediaBlockIOINTEL\0" // IR(19851, 18)
  "StallFreeALTERA\0" // IR(19869, 16)
  "StallFreeINTEL\0" // IR(19885, 15)
  "SPV_OPERAND_TYPE_LITERAL_FLOAT\0" // IR(19900, 31)
  "FPMaxErrorDecorationINTEL\0" // IR(19931, 26)
  "LatencyControlLabelALTERA\0" // IR(19957, 26)
  "LatencyControlLabelINTEL\0" // IR(19983, 25)
  "LatencyControlConstraintALTERA\0" // IR(20008, 31)
  "LatencyControlConstraintINTEL\0" // IR(20039, 30)
  "ConduitKernelArgumentALTERA\0" // IR(20069, 28)
  "ConduitKernelArgumentINTEL\0" // IR(20097, 27)
  "RegisterMapKernelArgumentALTERA\0" // IR(20124, 32)
  "RegisterMapKernelArgumentINTEL\0" // IR(20156, 31)
  "MMHostInterfaceAddressWidthALTERA\0" // IR(20187, 34)
  "MMHostInterfaceAddressWidthINTEL\0" // IR(20221, 33)
  "MMHostInterfaceDataWidthALTERA\0" // IR(20254, 31)
  "MMHostInterfaceDataWidthINTEL\0" // IR(20285, 30)
  "MMHostInterfaceLatencyALTERA\0" // IR(20315, 29)
  "MMHostInterfaceLatencyINTEL\0" // IR(20344, 28)
  "SPV_OPERAND_TYPE_ACCESS_QUALIFIER\0" // IR(20372, 34)
  "MMHostInterfaceReadWriteModeALTERA\0" // IR(20406, 35)
  "MMHostInterfaceReadWriteModeINTEL\0" // IR(20441, 34)
  "MMHostInterfaceMaxBurstALTERA\0" // IR(20475, 30)
  "MMHostInterfaceMaxBurstINTEL\0" // IR(20505, 29)
  "MMHostInterfaceWaitRequestALTERA\0" // IR(20534, 33)
  "MMHostInterfaceWaitRequestINTEL\0" // IR(20567, 32)
  "StableKernelArgumentALTERA\0" // IR(20599, 27)
  "StableKernelArgumentINTEL\0" // IR(20626, 26)
  "SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER\0" // IR(20652, 39)
  "HostAccessINTEL\0" // IR(20691, 16)
  "SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER\0" // IR(20707, 47)
  "InitModeALTERA\0" // IR(20754, 15)
  "InitModeINTEL\0" // IR(20769, 14)
  "ImplementInRegisterMapALTERA\0" // IR(20783, 29)
  "ImplementInRegisterMapINTEL\0" // IR(20812, 28)
  "ConditionalINTEL\0" // IR(20840, 17)
  "SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL\0" // IR(20857, 36)
  "CacheControlLoadINTEL\0" // IR(20893, 22)
  "SPV_OPERAND_TYPE_STORE_CACHE_CONTROL\0" // IR(20915, 37)
  "CacheControlStoreINTEL\0" // IR(20952, 23)
  "1D\0" // IR(20975, 3)
  "2D\0" // IR(20978, 3)
  "3D\0" // IR(20981, 3)
  "Cube\0" // IR(20984, 5)
  "Rect\0" // IR(20989, 5)
  "Buffer\0" // IR(20994, 7)
  "SubpassData\0" // IR(21001, 12)
  "TileImageDataEXT\0" // IR(21013, 17)
  "Invocations\0" // IR(21030, 12)
  "SpacingEqual\0" // IR(21042, 13)
  "SpacingFractionalEven\0" // IR(21055, 22)
  "SpacingFractionalOdd\0" // IR(21077, 21)
  "VertexOrderCw\0" // IR(21098, 14)
  "VertexOrderCcw\0" // IR(21112, 15)
  "PixelCenterInteger\0" // IR(21127, 19)
  "OriginUpperLeft\0" // IR(21146, 16)
  "OriginLowerLeft\0" // IR(21162, 16)
  "EarlyFragmentTests\0" // IR(21178, 19)
  "PointMode\0" // IR(21197, 10)
  "Xfb\0" // IR(21207, 4)
  "DepthReplacing\0" // IR(21211, 15)
  "DepthGreater\0" // IR(21226, 13)
  "DepthLess\0" // IR(21239, 10)
  "DepthUnchanged\0" // IR(21249, 15)
  "LocalSize\0" // IR(21264, 10)
  "LocalSizeHint\0" // IR(21274, 14)
  "InputPoints\0" // IR(21288, 12)
  "InputLines\0" // IR(21300, 11)
  "InputLinesAdjacency\0" // IR(21311, 20)
  "Triangles\0" // IR(21331, 10)
  "InputTrianglesAdjacency\0" // IR(21341, 24)
  "Quads\0" // IR(21365, 6)
  "Isolines\0" // IR(21371, 9)
  "OutputVertices\0" // IR(21380, 15)
  "OutputPoints\0" // IR(21395, 13)
  "OutputLineStrip\0" // IR(21408, 16)
  "OutputTriangleStrip\0" // IR(21424, 20)
  "VecTypeHint\0" // IR(21444, 12)
  "ContractionOff\0" // IR(21456, 15)
  "Initializer\0" // IR(21471, 12)
  "Finalizer\0" // IR(21483, 10)
  "SubgroupsPerWorkgroup\0" // IR(21493, 22)
  "SubgroupsPerWorkgroupId\0" // IR(21515, 24)
  "LocalSizeId\0" // IR(21539, 12)
  "LocalSizeHintId\0" // IR(21551, 16)
  "NonCoherentColorAttachmentReadEXT\0" // IR(21567, 34)
  "NonCoherentDepthAttachmentReadEXT\0" // IR(21601, 34)
  "NonCoherentStencilAttachmentReadEXT\0" // IR(21635, 36)
  "SubgroupUniformControlFlowKHR\0" // IR(21671, 30)
  "PostDepthCoverage\0" // IR(21701, 18)
  "NonCoherentTileAttachmentReadQCOM\0" // IR(21719, 34)
  "TileShadingRateQCOM\0" // IR(21753, 20)
  "EarlyAndLateFragmentTestsAMD\0" // IR(21773, 29)
  "StencilRefReplacingEXT\0" // IR(21802, 23)
  "CoalescingAMDX\0" // IR(21825, 15)
  "IsApiEntryAMDX\0" // IR(21840, 15)
  "MaxNodeRecursionAMDX\0" // IR(21855, 21)
  "StaticNumWorkgroupsAMDX\0" // IR(21876, 24)
  "MaxNumWorkgroupsAMDX\0" // IR(21900, 21)
  "StencilRefUnchangedFrontAMD\0" // IR(21921, 28)
  "StencilRefGreaterFrontAMD\0" // IR(21949, 26)
  "StencilRefLessFrontAMD\0" // IR(21975, 23)
  "StencilRefUnchangedBackAMD\0" // IR(21998, 27)
  "StencilRefGreaterBackAMD\0" // IR(22025, 25)
  "StencilRefLessBackAMD\0" // IR(22050, 22)
  "QuadDerivativesKHR\0" // IR(22072, 19)
  "RequireFullQuadsKHR\0" // IR(22091, 20)
  "SharesInputWithAMDX\0" // IR(22111, 20)
  "OutputLinesEXT\0" // IR(22131, 15)
  "OutputLinesNV\0" // IR(22146, 14)
  "OutputPrimitivesEXT\0" // IR(22160, 20)
  "OutputPrimitivesNV\0" // IR(22180, 19)
  "DerivativeGroupQuadsKHR\0" // IR(22199, 24)
  "DerivativeGroupQuadsNV\0" // IR(22223, 23)
  "DerivativeGroupLinearKHR\0" // IR(22246, 25)
  "DerivativeGroupLinearNV\0" // IR(22271, 24)
  "OutputTrianglesEXT\0" // IR(22295, 19)
  "OutputTrianglesNV\0" // IR(22314, 18)
  "PixelInterlockOrderedEXT\0" // IR(22332, 25)
  "PixelInterlockUnorderedEXT\0" // IR(22357, 27)
  "SampleInterlockOrderedEXT\0" // IR(22384, 26)
  "SampleInterlockUnorderedEXT\0" // IR(22410, 28)
  "ShadingRateInterlockOrderedEXT\0" // IR(22438, 31)
  "ShadingRateInterlockUnorderedEXT\0" // IR(22469, 33)
  "SharedLocalMemorySizeINTEL\0" // IR(22502, 27)
  "RoundingModeRTPINTEL\0" // IR(22529, 21)
  "RoundingModeRTNINTEL\0" // IR(22550, 21)
  "FloatingPointModeALTINTEL\0" // IR(22571, 26)
  "FloatingPointModeIEEEINTEL\0" // IR(22597, 27)
  "MaxWorkgroupSizeINTEL\0" // IR(22624, 22)
  "MaxWorkDimINTEL\0" // IR(22646, 16)
  "NoGlobalOffsetINTEL\0" // IR(22662, 20)
  "NumSIMDWorkitemsINTEL\0" // IR(22682, 22)
  "SchedulerTargetFmaxMhzINTEL\0" // IR(22704, 28)
  "MaximallyReconvergesKHR\0" // IR(22732, 24)
  "FPFastMathDefault\0" // IR(22756, 18)
  "StreamingInterfaceINTEL\0" // IR(22774, 24)
  "RegisterMapInterfaceINTEL\0" // IR(22798, 26)
  "NamedBarrierCountINTEL\0" // IR(22824, 23)
  "MaximumRegistersINTEL\0" // IR(22847, 22)
  "MaximumRegistersIdINTEL\0" // IR(22869, 24)
  "SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS\0" // IR(22893, 51)
  "NamedMaximumRegistersINTEL\0" // IR(22944, 27)
  "Vertex\0" // IR(22971, 7)
  "TessellationControl\0" // IR(22978, 20)
  "TessellationEvaluation\0" // IR(22998, 23)
  "GLCompute\0" // IR(23021, 10)
  "TaskNV\0" // IR(23031, 7)
  "MeshNV\0" // IR(23038, 7)
  "RayGenerationKHR\0" // IR(23045, 17)
  "RayGenerationNV\0" // IR(23062, 16)
  "IntersectionKHR\0" // IR(23078, 16)
  "IntersectionNV\0" // IR(23094, 15)
  "AnyHitKHR\0" // IR(23109, 10)
  "AnyHitNV\0" // IR(23119, 9)
  "ClosestHitKHR\0" // IR(23128, 14)
  "ClosestHitNV\0" // IR(23142, 13)
  "MissKHR\0" // IR(23155, 8)
  "MissNV\0" // IR(23163, 7)
  "CallableKHR\0" // IR(23170, 12)
  "CallableNV\0" // IR(23182, 11)
  "TaskEXT\0" // IR(23193, 8)
  "MeshEXT\0" // IR(23201, 8)
  "Preserve\0" // IR(23209, 9)
  "FlushToZero\0" // IR(23218, 12)
  "BFloat16KHR\0" // IR(23230, 12)
  "Float8E4M3EXT\0" // IR(23242, 14)
  "Float8E5M2EXT\0" // IR(23256, 14)
  "IEEE\0" // IR(23270, 5)
  "ALT\0" // IR(23275, 4)
  "NotNaN\0" // IR(23279, 7)
  "NotInf\0" // IR(23286, 7)
  "NSZ\0" // IR(23293, 4)
  "AllowRecip\0" // IR(23297, 11)
  "Fast\0" // IR(23308, 5)
  "AllowContract\0" // IR(23313, 14)
  "AllowContractFastINTEL\0" // IR(23327, 23)
  "AllowReassoc\0" // IR(23350, 13)
  "AllowReassocINTEL\0" // IR(23363, 18)
  "AllowTransform\0" // IR(23381, 15)
  "RTE\0" // IR(23396, 4)
  "RTZ\0" // IR(23400, 4)
  "RTP\0" // IR(23404, 4)
  "RTN\0" // IR(23408, 4)
  "Vertical2Pixels\0" // IR(23412, 16)
  "Vertical4Pixels\0" // IR(23428, 16)
  "Horizontal2Pixels\0" // IR(23444, 18)
  "Horizontal4Pixels\0" // IR(23462, 18)
  "Inline\0" // IR(23480, 7)
  "DontInline\0" // IR(23487, 11)
  "Pure\0" // IR(23498, 5)
  "Const\0" // IR(23503, 6)
  "Zext\0" // IR(23509, 5)
  "Sext\0" // IR(23514, 5)
  "ByVal\0" // IR(23519, 6)
  "Sret\0" // IR(23525, 5)
  "NoAlias\0" // IR(23530, 8)
  "NoCapture\0" // IR(23538, 10)
  "NoWrite\0" // IR(23548, 8)
  "NoReadWrite\0" // IR(23556, 12)
  "RuntimeAlignedALTERA\0" // IR(23568, 21)
  "RuntimeAlignedINTEL\0" // IR(23589, 20)
  "Reduce\0" // IR(23609, 7)
  "InclusiveScan\0" // IR(23616, 14)
  "ExclusiveScan\0" // IR(23630, 14)
  "ClusteredReduce\0" // IR(23644, 16)
  "PartitionedReduceEXT\0" // IR(23660, 21)
  "PartitionedReduceNV\0" // IR(23681, 20)
  "PartitionedInclusiveScanEXT\0" // IR(23701, 28)
  "PartitionedInclusiveScanNV\0" // IR(23729, 27)
  "PartitionedExclusiveScanEXT\0" // IR(23756, 28)
  "PartitionedExclusiveScanNV\0" // IR(23784, 27)
  "NoneINTEL\0" // IR(23811, 10)
  "ReadINTEL\0" // IR(23821, 10)
  "WriteINTEL\0" // IR(23831, 11)
  "ReadWriteINTEL\0" // IR(23842, 15)
  "Bias\0" // IR(23857, 5)
  "Lod\0" // IR(23862, 4)
  "Grad\0" // IR(23866, 5)
  "ConstOffset\0" // IR(23871, 12)
  "ConstOffsets\0" // IR(23883, 13)
  "MakeTexelAvailable\0" // IR(23896, 19)
  "MakeTexelAvailableKHR\0" // IR(23915, 22)
  "MakeTexelVisible\0" // IR(23937, 17)
  "MakeTexelVisibleKHR\0" // IR(23954, 20)
  "NonPrivateTexel\0" // IR(23974, 16)
  "NonPrivateTexelKHR\0" // IR(23990, 19)
  "VolatileTexel\0" // IR(24009, 14)
  "VolatileTexelKHR\0" // IR(24023, 17)
  "SignExtend\0" // IR(24040, 11)
  "ZeroExtend\0" // IR(24051, 11)
  "Nontemporal\0" // IR(24062, 12)
  "Offsets\0" // IR(24074, 8)
  "SnormInt8\0" // IR(24082, 10)
  "SnormInt16\0" // IR(24092, 11)
  "UnormInt8\0" // IR(24103, 10)
  "UnormInt16\0" // IR(24113, 11)
  "UnormShort565\0" // IR(24124, 14)
  "UnormShort555\0" // IR(24138, 14)
  "UnormInt101010\0" // IR(24152, 15)
  "SignedInt8\0" // IR(24167, 11)
  "SignedInt16\0" // IR(24178, 12)
  "SignedInt32\0" // IR(24190, 12)
  "UnsignedInt8\0" // IR(24202, 13)
  "UnsignedInt16\0" // IR(24215, 14)
  "UnsignedInt32\0" // IR(24229, 14)
  "HalfFloat\0" // IR(24243, 10)
  "UnormInt24\0" // IR(24253, 11)
  "UnormInt101010_2\0" // IR(24264, 17)
  "UnormInt10X6EXT\0" // IR(24281, 16)
  "UnsignedIntRaw10EXT\0" // IR(24297, 20)
  "UnsignedIntRaw12EXT\0" // IR(24317, 20)
  "UnormInt2_101010EXT\0" // IR(24337, 20)
  "UnsignedInt10X6EXT\0" // IR(24357, 19)
  "UnsignedInt12X4EXT\0" // IR(24376, 19)
  "UnsignedInt14X2EXT\0" // IR(24395, 19)
  "UnormInt12X4EXT\0" // IR(24414, 16)
  "UnormInt14X2EXT\0" // IR(24430, 16)
  "R\0" // IR(24446, 2)
  "A\0" // IR(24448, 2)
  "RG\0" // IR(24450, 3)
  "RA\0" // IR(24453, 3)
  "RGB\0" // IR(24456, 4)
  "RGBA\0" // IR(24460, 5)
  "BGRA\0" // IR(24465, 5)
  "ARGB\0" // IR(24470, 5)
  "Intensity\0" // IR(24475, 10)
  "Luminance\0" // IR(24485, 10)
  "Rx\0" // IR(24495, 3)
  "RGx\0" // IR(24498, 4)
  "RGBx\0" // IR(24502, 5)
  "Depth\0" // IR(24507, 6)
  "DepthStencil\0" // IR(24513, 13)
  "sRGB\0" // IR(24526, 5)
  "sRGBx\0" // IR(24531, 6)
  "sRGBA\0" // IR(24537, 6)
  "sBGRA\0" // IR(24543, 6)
  "ABGR\0" // IR(24549, 5)
  "InitOnDeviceReprogramALTERA\0" // IR(24554, 28)
  "InitOnDeviceReprogramINTEL\0" // IR(24582, 27)
  "InitOnDeviceResetALTERA\0" // IR(24609, 24)
  "InitOnDeviceResetINTEL\0" // IR(24633, 23)
  "NoWait\0" // IR(24656, 7)
  "WaitKernel\0" // IR(24663, 11)
  "WaitWorkGroup\0" // IR(24674, 14)
  "CmdExecTime\0" // IR(24688, 12)
  "MayUsePrintf\0" // IR(24700, 13)
  "Export\0" // IR(24713, 7)
  "Import\0" // IR(24720, 7)
  "LinkOnceODR\0" // IR(24727, 12)
  "UncachedINTEL\0" // IR(24739, 14)
  "CachedINTEL\0" // IR(24753, 12)
  "StreamingINTEL\0" // IR(24765, 15)
  "InvalidateAfterReadINTEL\0" // IR(24780, 25)
  "ConstCachedINTEL\0" // IR(24805, 17)
  "Unroll\0" // IR(24822, 7)
  "DontUnroll\0" // IR(24829, 11)
  "DependencyInfinite\0" // IR(24840, 19)
  "DependencyLength\0" // IR(24859, 17)
  "MinIterations\0" // IR(24876, 14)
  "MaxIterations\0" // IR(24890, 14)
  "IterationMultiple\0" // IR(24904, 18)
  "PeelCount\0" // IR(24922, 10)
  "PartialCount\0" // IR(24932, 13)
  "DependencyArrayALTERA\0" // IR(24945, 22)
  "DependencyArrayINTEL\0" // IR(24967, 21)
  "LoopCoalesceALTERA\0" // IR(24988, 19)
  "LoopCoalesceINTEL\0" // IR(25007, 18)
  "MaxInterleavingALTERA\0" // IR(25025, 22)
  "MaxInterleavingINTEL\0" // IR(25047, 21)
  "SpeculatedIterationsALTERA\0" // IR(25068, 27)
  "SpeculatedIterationsINTEL\0" // IR(25095, 26)
  "NoFusionALTERA\0" // IR(25121, 15)
  "NoFusionINTEL\0" // IR(25136, 14)
  "LoopCountALTERA\0" // IR(25150, 16)
  "LoopCountINTEL\0" // IR(25166, 15)
  "MaxReinvocationDelayALTERA\0" // IR(25181, 27)
  "MaxReinvocationDelayINTEL\0" // IR(25208, 26)
  "MatrixASignedComponentsINTEL\0" // IR(25234, 29)
  "MatrixBSignedComponentsINTEL\0" // IR(25263, 29)
  "MatrixCBFloat16INTEL\0" // IR(25292, 21)
  "MatrixResultBFloat16INTEL\0" // IR(25313, 26)
  "MatrixAPackedInt8INTEL\0" // IR(25339, 23)
  "MatrixBPackedInt8INTEL\0" // IR(25362, 23)
  "MatrixAPackedInt4INTEL\0" // IR(25385, 23)
  "MatrixBPackedInt4INTEL\0" // IR(25408, 23)
  "MatrixATF32INTEL\0" // IR(25431, 17)
  "MatrixBTF32INTEL\0" // IR(25448, 17)
  "MatrixAPackedFloat16INTEL\0" // IR(25465, 26)
  "MatrixBPackedFloat16INTEL\0" // IR(25491, 26)
  "MatrixAPackedBFloat16INTEL\0" // IR(25517, 27)
  "MatrixBPackedBFloat16INTEL\0" // IR(25544, 27)
  "Aligned\0" // IR(25571, 8)
  "MakePointerAvailable\0" // IR(25579, 21)
  "MakePointerAvailableKHR\0" // IR(25600, 24)
  "MakePointerVisible\0" // IR(25624, 19)
  "MakePointerVisibleKHR\0" // IR(25643, 22)
  "NonPrivatePointer\0" // IR(25665, 18)
  "NonPrivatePointerKHR\0" // IR(25683, 21)
  "AliasScopeINTELMask\0" // IR(25704, 20)
  "NoAliasINTELMask\0" // IR(25724, 17)
  "Simple\0" // IR(25741, 7)
  "GLSL450\0" // IR(25748, 8)
  "OpenCL\0" // IR(25756, 7)
  "Vulkan\0" // IR(25763, 7)
  "VulkanKHR\0" // IR(25770, 10)
  "Relaxed\0" // IR(25780, 8)
  "Acquire\0" // IR(25788, 8)
  "Release\0" // IR(25796, 8)
  "AcquireRelease\0" // IR(25804, 15)
  "SequentiallyConsistent\0" // IR(25819, 23)
  "UniformMemory\0" // IR(25842, 14)
  "SubgroupMemory\0" // IR(25856, 15)
  "WorkgroupMemory\0" // IR(25871, 16)
  "CrossWorkgroupMemory\0" // IR(25887, 21)
  "AtomicCounterMemory\0" // IR(25908, 20)
  "ImageMemory\0" // IR(25928, 12)
  "OutputMemory\0" // IR(25940, 13)
  "OutputMemoryKHR\0" // IR(25953, 16)
  "MakeAvailable\0" // IR(25969, 14)
  "MakeAvailableKHR\0" // IR(25983, 17)
  "MakeVisible\0" // IR(26000, 12)
  "MakeVisibleKHR\0" // IR(26012, 15)
  "AutoINTEL\0" // IR(26027, 10)
  "WRAP\0" // IR(26037, 5)
  "SAT\0" // IR(26042, 4)
  "SAT_ZERO\0" // IR(26046, 9)
  "SAT_SYM\0" // IR(26055, 8)
  "PackedVectorFormat4x8Bit\0" // IR(26063, 25)
  "PackedVectorFormat4x8BitKHR\0" // IR(26088, 28)
  "TRN\0" // IR(26116, 4)
  "TRN_ZERO\0" // IR(26120, 9)
  "RND\0" // IR(26129, 4)
  "RND_ZERO\0" // IR(26133, 9)
  "RND_INF\0" // IR(26142, 8)
  "RND_MIN_INF\0" // IR(26150, 12)
  "RND_CONV\0" // IR(26162, 9)
  "RND_CONV_ODD\0" // IR(26171, 13)
  "RobustnessPerComponentNV\0" // IR(26184, 25)
  "RobustnessPerElementNV\0" // IR(26209, 23)
  "OpaqueKHR\0" // IR(26232, 10)
  "NoOpaqueKHR\0" // IR(26242, 12)
  "TerminateOnFirstHitKHR\0" // IR(26254, 23)
  "SkipClosestHitShaderKHR\0" // IR(26277, 24)
  "CullBackFacingTrianglesKHR\0" // IR(26301, 27)
  "CullFrontFacingTrianglesKHR\0" // IR(26328, 28)
  "CullOpaqueKHR\0" // IR(26356, 14)
  "CullNoOpaqueKHR\0" // IR(26370, 16)
  "SkipTrianglesKHR\0" // IR(26386, 17)
  "SkipBuiltinPrimitivesNV\0" // IR(26403, 24)
  "SkipAABBsKHR\0" // IR(26427, 13)
  "ForceOpacityMicromap2StateEXT\0" // IR(26440, 30)
  "RayQueryCandidateIntersectionTriangleKHR\0" // IR(26470, 41)
  "RayQueryCandidateIntersectionAABBKHR\0" // IR(26511, 37)
  "RayQueryCommittedIntersectionNoneKHR\0" // IR(26548, 37)
  "RayQueryCommittedIntersectionTriangleKHR\0" // IR(26585, 41)
  "RayQueryCommittedIntersectionGeneratedKHR\0" // IR(26626, 42)
  "RayQueryCandidateIntersectionKHR\0" // IR(26668, 33)
  "RayQueryCommittedIntersectionKHR\0" // IR(26701, 33)
  "ClampToEdge\0" // IR(26734, 12)
  "Clamp\0" // IR(26746, 6)
  "Repeat\0" // IR(26752, 7)
  "RepeatMirrored\0" // IR(26759, 15)
  "Nearest\0" // IR(26774, 8)
  "Linear\0" // IR(26782, 7)
  "Unknown\0" // IR(26789, 8)
  "Rgba32f\0" // IR(26797, 8)
  "Rgba16f\0" // IR(26805, 8)
  "R32f\0" // IR(26813, 5)
  "Rgba8\0" // IR(26818, 6)
  "Rgba8Snorm\0" // IR(26824, 11)
  "Rg32f\0" // IR(26835, 6)
  "Rg16f\0" // IR(26841, 6)
  "R11fG11fB10f\0" // IR(26847, 13)
  "R16f\0" // IR(26860, 5)
  "Rgba16\0" // IR(26865, 7)
  "Rgb10A2\0" // IR(26872, 8)
  "Rg16\0" // IR(26880, 5)
  "Rg8\0" // IR(26885, 4)
  "R16\0" // IR(26889, 4)
  "R8\0" // IR(26893, 3)
  "Rgba16Snorm\0" // IR(26896, 12)
  "Rg16Snorm\0" // IR(26908, 10)
  "Rg8Snorm\0" // IR(26918, 9)
  "R16Snorm\0" // IR(26927, 9)
  "R8Snorm\0" // IR(26936, 8)
  "Rgba32i\0" // IR(26944, 8)
  "Rgba16i\0" // IR(26952, 8)
  "Rgba8i\0" // IR(26960, 7)
  "R32i\0" // IR(26967, 5)
  "Rg32i\0" // IR(26972, 6)
  "Rg16i\0" // IR(26978, 6)
  "Rg8i\0" // IR(26984, 5)
  "R16i\0" // IR(26989, 5)
  "R8i\0" // IR(26994, 4)
  "Rgba32ui\0" // IR(26998, 9)
  "Rgba16ui\0" // IR(27007, 9)
  "Rgba8ui\0" // IR(27016, 8)
  "R32ui\0" // IR(27024, 6)
  "Rgb10a2ui\0" // IR(27030, 10)
  "Rg32ui\0" // IR(27040, 7)
  "Rg16ui\0" // IR(27047, 7)
  "Rg8ui\0" // IR(27054, 6)
  "R16ui\0" // IR(27060, 6)
  "R8ui\0" // IR(27066, 5)
  "R64ui\0" // IR(27071, 6)
  "R64i\0" // IR(27077, 5)
  "CrossDevice\0" // IR(27082, 12)
  "Device\0" // IR(27094, 7)
  "Workgroup\0" // IR(27101, 10)
  "Subgroup\0" // IR(27111, 9)
  "Invocation\0" // IR(27120, 11)
  "QueueFamily\0" // IR(27131, 12)
  "QueueFamilyKHR\0" // IR(27143, 15)
  "ShaderCallKHR\0" // IR(27158, 14)
  "Flatten\0" // IR(27172, 8)
  "DontFlatten\0" // IR(27180, 12)
  "IdentifierPossibleDuplicates\0" // IR(27192, 29)
  "FlagUnknownPhysicalLayout\0" // IR(27221, 26)
  "ESSL\0" // IR(27247, 5)
  "GLSL\0" // IR(27252, 5)
  "OpenCL_C\0" // IR(27257, 9)
  "OpenCL_CPP\0" // IR(27266, 11)
  "HLSL\0" // IR(27277, 5)
  "CPP_for_OpenCL\0" // IR(27282, 15)
  "SYCL\0" // IR(27297, 5)
  "HERO_C\0" // IR(27302, 7)
  "NZSL\0" // IR(27309, 5)
  "WGSL\0" // IR(27314, 5)
  "Slang\0" // IR(27319, 6)
  "Zig\0" // IR(27325, 4)
  "Rust\0" // IR(27329, 5)
  "UniformConstant\0" // IR(27334, 16)
  "Input\0" // IR(27350, 6)
  "Output\0" // IR(27356, 7)
  "CrossWorkgroup\0" // IR(27363, 15)
  "Private\0" // IR(27378, 8)
  "Function\0" // IR(27386, 9)
  "Generic\0" // IR(27395, 8)
  "PushConstant\0" // IR(27403, 13)
  "AtomicCounter\0" // IR(27416, 14)
  "Image\0" // IR(27430, 6)
  "StorageBuffer\0" // IR(27436, 14)
  "TileImageEXT\0" // IR(27450, 13)
  "TileAttachmentQCOM\0" // IR(27463, 19)
  "NodePayloadAMDX\0" // IR(27482, 16)
  "CallableDataKHR\0" // IR(27498, 16)
  "CallableDataNV\0" // IR(27514, 15)
  "IncomingCallableDataKHR\0" // IR(27529, 24)
  "IncomingCallableDataNV\0" // IR(27553, 23)
  "RayPayloadKHR\0" // IR(27576, 14)
  "RayPayloadNV\0" // IR(27590, 13)
  "HitAttributeKHR\0" // IR(27603, 16)
  "HitAttributeNV\0" // IR(27619, 15)
  "IncomingRayPayloadKHR\0" // IR(27634, 22)
  "IncomingRayPayloadNV\0" // IR(27656, 21)
  "ShaderRecordBufferKHR\0" // IR(27677, 22)
  "ShaderRecordBufferNV\0" // IR(27699, 21)
  "PhysicalStorageBuffer\0" // IR(27720, 22)
  "PhysicalStorageBufferEXT\0" // IR(27742, 25)
  "HitObjectAttributeNV\0" // IR(27767, 21)
  "TaskPayloadWorkgroupEXT\0" // IR(27788, 24)
  "HitObjectAttributeEXT\0" // IR(27812, 22)
  "CodeSectionINTEL\0" // IR(27834, 17)
  "DeviceOnlyALTERA\0" // IR(27851, 17)
  "DeviceOnlyINTEL\0" // IR(27868, 16)
  "HostOnlyALTERA\0" // IR(27884, 15)
  "HostOnlyINTEL\0" // IR(27899, 14)
  "WriteThroughINTEL\0" // IR(27913, 18)
  "WriteBackINTEL\0" // IR(27931, 15)
  "TensorView\0" // IR(27946, 11)
  "DecodeFunc\0" // IR(27957, 11)
  "Undefined\0" // IR(27968, 10)
  "NoneARM\0" // IR(27978, 8)
  "NontemporalARM\0" // IR(27986, 15)
  "OutOfBoundsValueARM\0" // IR(28001, 20)
  "MakeElementAvailableARM\0" // IR(28021, 24)
  "MakeElementVisibleARM\0" // IR(28045, 22)
  "NonPrivateElementARM\0" // IR(28067, 21)
  "Nop\0" // IR(28088, 4)
  "SPV_OPERAND_TYPE_TYPE_ID\0" // IR(28092, 25)
  "SPV_OPERAND_TYPE_RESULT_ID\0" // IR(28117, 27)
  "Undef\0" // IR(28144, 6)
  "SourceContinued\0" // IR(28150, 16)
  "SPV_OPERAND_TYPE_SOURCE_LANGUAGE\0" // IR(28166, 33)
  "SPV_OPERAND_TYPE_OPTIONAL_ID\0" // IR(28199, 29)
  "SPV_OPERAND_TYPE_OPTIONAL_LITERAL_STRING\0" // IR(28228, 41)
  "Source\0" // IR(28269, 7)
  "SourceExtension\0" // IR(28276, 16)
  "Name\0" // IR(28292, 5)
  "MemberName\0" // IR(28297, 11)
  "String\0" // IR(28308, 7)
  "Line\0" // IR(28315, 5)
  "Extension\0" // IR(28320, 10)
  "ExtInstImport\0" // IR(28330, 14)
  "SPV_OPERAND_TYPE_EXTENSION_INSTRUCTION_NUMBER\0" // IR(28344, 46)
  "ExtInst\0" // IR(28390, 8)
  "SPV_OPERAND_TYPE_ADDRESSING_MODEL\0" // IR(28398, 34)
  "SPV_OPERAND_TYPE_MEMORY_MODEL\0" // IR(28432, 30)
  "MemoryModel\0" // IR(28462, 12)
  "SPV_OPERAND_TYPE_EXECUTION_MODEL\0" // IR(28474, 33)
  "SPV_OPERAND_TYPE_VARIABLE_ID\0" // IR(28507, 29)
  "EntryPoint\0" // IR(28536, 11)
  "SPV_OPERAND_TYPE_EXECUTION_MODE\0" // IR(28547, 32)
  "ExecutionMode\0" // IR(28579, 14)
  "SPV_OPERAND_TYPE_CAPABILITY\0" // IR(28593, 28)
  "Capability\0" // IR(28621, 11)
  "TypeVoid\0" // IR(28632, 9)
  "TypeBool\0" // IR(28641, 9)
  "TypeInt\0" // IR(28650, 8)
  "SPV_OPERAND_TYPE_OPTIONAL_FPENCODING\0" // IR(28658, 37)
  "TypeFloat\0" // IR(28695, 10)
  "TypeVector\0" // IR(28705, 11)
  "TypeMatrix\0" // IR(28716, 11)
  "SPV_OPERAND_TYPE_DIMENSIONALITY\0" // IR(28727, 32)
  "SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT\0" // IR(28759, 38)
  "SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER\0" // IR(28797, 43)
  "TypeImage\0" // IR(28840, 10)
  "TypeSampler\0" // IR(28850, 12)
  "TypeSampledImage\0" // IR(28862, 17)
  "TypeArray\0" // IR(28879, 10)
  "TypeRuntimeArray\0" // IR(28889, 17)
  "TypeStruct\0" // IR(28906, 11)
  "TypeOpaque\0" // IR(28917, 11)
  "SPV_OPERAND_TYPE_STORAGE_CLASS\0" // IR(28928, 31)
  "TypePointer\0" // IR(28959, 12)
  "TypeFunction\0" // IR(28971, 13)
  "TypeEvent\0" // IR(28984, 10)
  "TypeDeviceEvent\0" // IR(28994, 16)
  "TypeReserveId\0" // IR(29010, 14)
  "TypeQueue\0" // IR(29024, 10)
  "TypePipe\0" // IR(29034, 9)
  "TypeForwardPointer\0" // IR(29043, 19)
  "ConstantTrue\0" // IR(29062, 13)
  "ConstantFalse\0" // IR(29075, 14)
  "SPV_OPERAND_TYPE_TYPED_LITERAL_NUMBER\0" // IR(29089, 38)
  "ConstantComposite\0" // IR(29127, 18)
  "SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE\0" // IR(29145, 41)
  "SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE\0" // IR(29186, 37)
  "ConstantSampler\0" // IR(29223, 16)
  "ConstantNull\0" // IR(29239, 13)
  "SpecConstantTrue\0" // IR(29252, 17)
  "SpecConstantFalse\0" // IR(29269, 18)
  "SpecConstant\0" // IR(29287, 13)
  "SpecConstantComposite\0" // IR(29300, 22)
  "SPV_OPERAND_TYPE_SPEC_CONSTANT_OP_NUMBER\0" // IR(29322, 41)
  "SpecConstantOp\0" // IR(29363, 15)
  "SPV_OPERAND_TYPE_FUNCTION_CONTROL\0" // IR(29378, 34)
  "FunctionParameter\0" // IR(29412, 18)
  "FunctionEnd\0" // IR(29430, 12)
  "FunctionCall\0" // IR(29442, 13)
  "Variable\0" // IR(29455, 9)
  "ImageTexelPointer\0" // IR(29464, 18)
  "SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS\0" // IR(29482, 40)
  "Load\0" // IR(29522, 5)
  "Store\0" // IR(29527, 6)
  "CopyMemory\0" // IR(29533, 11)
  "CopyMemorySized\0" // IR(29544, 16)
  "AccessChain\0" // IR(29560, 12)
  "InBoundsAccessChain\0" // IR(29572, 20)
  "PtrAccessChain\0" // IR(29592, 15)
  "ArrayLength\0" // IR(29607, 12)
  "GenericPtrMemSemantics\0" // IR(29619, 23)
  "InBoundsPtrAccessChain\0" // IR(29642, 23)
  "SPV_OPERAND_TYPE_DECORATION\0" // IR(29665, 28)
  "Decorate\0" // IR(29693, 9)
  "MemberDecorate\0" // IR(29702, 15)
  "DecorationGroup\0" // IR(29717, 16)
  "GroupDecorate\0" // IR(29733, 14)
  "SPV_OPERAND_TYPE_VARIABLE_ID_LITERAL_INTEGER\0" // IR(29747, 45)
  "GroupMemberDecorate\0" // IR(29792, 20)
  "VectorExtractDynamic\0" // IR(29812, 21)
  "VectorInsertDynamic\0" // IR(29833, 20)
  "VectorShuffle\0" // IR(29853, 14)
  "CompositeConstruct\0" // IR(29867, 19)
  "CompositeExtract\0" // IR(29886, 17)
  "CompositeInsert\0" // IR(29903, 16)
  "CopyObject\0" // IR(29919, 11)
  "Transpose\0" // IR(29930, 10)
  "SampledImage\0" // IR(29940, 13)
  "SPV_OPERAND_TYPE_OPTIONAL_IMAGE\0" // IR(29953, 32)
  "ImageSampleImplicitLod\0" // IR(29985, 23)
  "SPV_OPERAND_TYPE_IMAGE\0" // IR(30008, 23)
  "ImageSampleExplicitLod\0" // IR(30031, 23)
  "ImageSampleDrefImplicitLod\0" // IR(30054, 27)
  "ImageSampleDrefExplicitLod\0" // IR(30081, 27)
  "ImageSampleProjImplicitLod\0" // IR(30108, 27)
  "ImageSampleProjExplicitLod\0" // IR(30135, 27)
  "ImageSampleProjDrefImplicitLod\0" // IR(30162, 31)
  "ImageSampleProjDrefExplicitLod\0" // IR(30193, 31)
  "ImageFetch\0" // IR(30224, 11)
  "ImageGather\0" // IR(30235, 12)
  "ImageDrefGather\0" // IR(30247, 16)
  "ImageRead\0" // IR(30263, 10)
  "ImageWrite\0" // IR(30273, 11)
  "ImageQueryFormat\0" // IR(30284, 17)
  "ImageQueryOrder\0" // IR(30301, 16)
  "ImageQuerySizeLod\0" // IR(30317, 18)
  "ImageQuerySize\0" // IR(30335, 15)
  "ImageQueryLod\0" // IR(30350, 14)
  "ImageQueryLevels\0" // IR(30364, 17)
  "ImageQuerySamples\0" // IR(30381, 18)
  "ConvertFToU\0" // IR(30399, 12)
  "ConvertFToS\0" // IR(30411, 12)
  "ConvertSToF\0" // IR(30423, 12)
  "ConvertUToF\0" // IR(30435, 12)
  "UConvert\0" // IR(30447, 9)
  "SConvert\0" // IR(30456, 9)
  "FConvert\0" // IR(30465, 9)
  "QuantizeToF16\0" // IR(30474, 14)
  "ConvertPtrToU\0" // IR(30488, 14)
  "SatConvertSToU\0" // IR(30502, 15)
  "SatConvertUToS\0" // IR(30517, 15)
  "ConvertUToPtr\0" // IR(30532, 14)
  "PtrCastToGeneric\0" // IR(30546, 17)
  "GenericCastToPtr\0" // IR(30563, 17)
  "GenericCastToPtrExplicit\0" // IR(30580, 25)
  "Bitcast\0" // IR(30605, 8)
  "SNegate\0" // IR(30613, 8)
  "FNegate\0" // IR(30621, 8)
  "IAdd\0" // IR(30629, 5)
  "FAdd\0" // IR(30634, 5)
  "ISub\0" // IR(30639, 5)
  "FSub\0" // IR(30644, 5)
  "IMul\0" // IR(30649, 5)
  "FMul\0" // IR(30654, 5)
  "UDiv\0" // IR(30659, 5)
  "SDiv\0" // IR(30664, 5)
  "FDiv\0" // IR(30669, 5)
  "UMod\0" // IR(30674, 5)
  "SRem\0" // IR(30679, 5)
  "SMod\0" // IR(30684, 5)
  "FRem\0" // IR(30689, 5)
  "FMod\0" // IR(30694, 5)
  "VectorTimesScalar\0" // IR(30699, 18)
  "MatrixTimesScalar\0" // IR(30717, 18)
  "VectorTimesMatrix\0" // IR(30735, 18)
  "MatrixTimesVector\0" // IR(30753, 18)
  "MatrixTimesMatrix\0" // IR(30771, 18)
  "OuterProduct\0" // IR(30789, 13)
  "Dot\0" // IR(30802, 4)
  "IAddCarry\0" // IR(30806, 10)
  "ISubBorrow\0" // IR(30816, 11)
  "UMulExtended\0" // IR(30827, 13)
  "SMulExtended\0" // IR(30840, 13)
  "Any\0" // IR(30853, 4)
  "All\0" // IR(30857, 4)
  "IsNan\0" // IR(30861, 6)
  "IsInf\0" // IR(30867, 6)
  "IsFinite\0" // IR(30873, 9)
  "IsNormal\0" // IR(30882, 9)
  "SignBitSet\0" // IR(30891, 11)
  "LessOrGreater\0" // IR(30902, 14)
  "Ordered\0" // IR(30916, 8)
  "Unordered\0" // IR(30924, 10)
  "LogicalEqual\0" // IR(30934, 13)
  "LogicalNotEqual\0" // IR(30947, 16)
  "LogicalOr\0" // IR(30963, 10)
  "LogicalAnd\0" // IR(30973, 11)
  "LogicalNot\0" // IR(30984, 11)
  "Select\0" // IR(30995, 7)
  "IEqual\0" // IR(31002, 7)
  "INotEqual\0" // IR(31009, 10)
  "UGreaterThan\0" // IR(31019, 13)
  "SGreaterThan\0" // IR(31032, 13)
  "UGreaterThanEqual\0" // IR(31045, 18)
  "SGreaterThanEqual\0" // IR(31063, 18)
  "ULessThan\0" // IR(31081, 10)
  "SLessThan\0" // IR(31091, 10)
  "ULessThanEqual\0" // IR(31101, 15)
  "SLessThanEqual\0" // IR(31116, 15)
  "FOrdEqual\0" // IR(31131, 10)
  "FUnordEqual\0" // IR(31141, 12)
  "FOrdNotEqual\0" // IR(31153, 13)
  "FUnordNotEqual\0" // IR(31166, 15)
  "FOrdLessThan\0" // IR(31181, 13)
  "FUnordLessThan\0" // IR(31194, 15)
  "FOrdGreaterThan\0" // IR(31209, 16)
  "FUnordGreaterThan\0" // IR(31225, 18)
  "FOrdLessThanEqual\0" // IR(31243, 18)
  "FUnordLessThanEqual\0" // IR(31261, 20)
  "FOrdGreaterThanEqual\0" // IR(31281, 21)
  "FUnordGreaterThanEqual\0" // IR(31302, 23)
  "ShiftRightLogical\0" // IR(31325, 18)
  "ShiftRightArithmetic\0" // IR(31343, 21)
  "ShiftLeftLogical\0" // IR(31364, 17)
  "BitwiseOr\0" // IR(31381, 10)
  "BitwiseXor\0" // IR(31391, 11)
  "BitwiseAnd\0" // IR(31402, 11)
  "Not\0" // IR(31413, 4)
  "BitFieldInsert\0" // IR(31417, 15)
  "BitFieldSExtract\0" // IR(31432, 17)
  "BitFieldUExtract\0" // IR(31449, 17)
  "BitReverse\0" // IR(31466, 11)
  "BitCount\0" // IR(31477, 9)
  "DPdx\0" // IR(31486, 5)
  "DPdy\0" // IR(31491, 5)
  "Fwidth\0" // IR(31496, 7)
  "DPdxFine\0" // IR(31503, 9)
  "DPdyFine\0" // IR(31512, 9)
  "FwidthFine\0" // IR(31521, 11)
  "DPdxCoarse\0" // IR(31532, 11)
  "DPdyCoarse\0" // IR(31543, 11)
  "FwidthCoarse\0" // IR(31554, 13)
  "EmitVertex\0" // IR(31567, 11)
  "EndPrimitive\0" // IR(31578, 13)
  "EmitStreamVertex\0" // IR(31591, 17)
  "EndStreamPrimitive\0" // IR(31608, 19)
  "SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID\0" // IR(31627, 37)
  "ControlBarrier\0" // IR(31664, 15)
  "MemoryBarrier\0" // IR(31679, 14)
  "AtomicLoad\0" // IR(31693, 11)
  "AtomicStore\0" // IR(31704, 12)
  "AtomicExchange\0" // IR(31716, 15)
  "AtomicCompareExchange\0" // IR(31731, 22)
  "AtomicCompareExchangeWeak\0" // IR(31753, 26)
  "AtomicIIncrement\0" // IR(31779, 17)
  "AtomicIDecrement\0" // IR(31796, 17)
  "AtomicIAdd\0" // IR(31813, 11)
  "AtomicISub\0" // IR(31824, 11)
  "AtomicSMin\0" // IR(31835, 11)
  "AtomicUMin\0" // IR(31846, 11)
  "AtomicSMax\0" // IR(31857, 11)
  "AtomicUMax\0" // IR(31868, 11)
  "AtomicAnd\0" // IR(31879, 10)
  "AtomicOr\0" // IR(31889, 9)
  "AtomicXor\0" // IR(31898, 10)
  "Phi\0" // IR(31908, 4)
  "SPV_OPERAND_TYPE_LOOP_CONTROL\0" // IR(31912, 30)
  "LoopMerge\0" // IR(31942, 10)
  "SPV_OPERAND_TYPE_SELECTION_CONTROL\0" // IR(31952, 35)
  "SelectionMerge\0" // IR(31987, 15)
  "Label\0" // IR(32002, 6)
  "Branch\0" // IR(32008, 7)
  "BranchConditional\0" // IR(32015, 18)
  "SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER_ID\0" // IR(32033, 45)
  "Switch\0" // IR(32078, 7)
  "Kill\0" // IR(32085, 5)
  "Return\0" // IR(32090, 7)
  "ReturnValue\0" // IR(32097, 12)
  "Unreachable\0" // IR(32109, 12)
  "LifetimeStart\0" // IR(32121, 14)
  "LifetimeStop\0" // IR(32135, 13)
  "GroupAsyncCopy\0" // IR(32148, 15)
  "GroupWaitEvents\0" // IR(32163, 16)
  "GroupAll\0" // IR(32179, 9)
  "GroupAny\0" // IR(32188, 9)
  "GroupBroadcast\0" // IR(32197, 15)
  "SPV_OPERAND_TYPE_GROUP_OPERATION\0" // IR(32212, 33)
  "GroupIAdd\0" // IR(32245, 10)
  "GroupFAdd\0" // IR(32255, 10)
  "GroupFMin\0" // IR(32265, 10)
  "GroupUMin\0" // IR(32275, 10)
  "GroupSMin\0" // IR(32285, 10)
  "GroupFMax\0" // IR(32295, 10)
  "GroupUMax\0" // IR(32305, 10)
  "GroupSMax\0" // IR(32315, 10)
  "ReadPipe\0" // IR(32325, 9)
  "WritePipe\0" // IR(32334, 10)
  "ReservedReadPipe\0" // IR(32344, 17)
  "ReservedWritePipe\0" // IR(32361, 18)
  "ReserveReadPipePackets\0" // IR(32379, 23)
  "ReserveWritePipePackets\0" // IR(32402, 24)
  "CommitReadPipe\0" // IR(32426, 15)
  "CommitWritePipe\0" // IR(32441, 16)
  "IsValidReserveId\0" // IR(32457, 17)
  "GetNumPipePackets\0" // IR(32474, 18)
  "GetMaxPipePackets\0" // IR(32492, 18)
  "GroupReserveReadPipePackets\0" // IR(32510, 28)
  "GroupReserveWritePipePackets\0" // IR(32538, 29)
  "GroupCommitReadPipe\0" // IR(32567, 20)
  "GroupCommitWritePipe\0" // IR(32587, 21)
  "EnqueueMarker\0" // IR(32608, 14)
  "EnqueueKernel\0" // IR(32622, 14)
  "GetKernelNDrangeSubGroupCount\0" // IR(32636, 30)
  "GetKernelNDrangeMaxSubGroupSize\0" // IR(32666, 32)
  "GetKernelWorkGroupSize\0" // IR(32698, 23)
  "GetKernelPreferredWorkGroupSizeMultiple\0" // IR(32721, 40)
  "RetainEvent\0" // IR(32761, 12)
  "ReleaseEvent\0" // IR(32773, 13)
  "CreateUserEvent\0" // IR(32786, 16)
  "IsValidEvent\0" // IR(32802, 13)
  "SetUserEventStatus\0" // IR(32815, 19)
  "CaptureEventProfilingInfo\0" // IR(32834, 26)
  "GetDefaultQueue\0" // IR(32860, 16)
  "BuildNDRange\0" // IR(32876, 13)
  "ImageSparseSampleImplicitLod\0" // IR(32889, 29)
  "ImageSparseSampleExplicitLod\0" // IR(32918, 29)
  "ImageSparseSampleDrefImplicitLod\0" // IR(32947, 33)
  "ImageSparseSampleDrefExplicitLod\0" // IR(32980, 33)
  "ImageSparseSampleProjImplicitLod\0" // IR(33013, 33)
  "ImageSparseSampleProjExplicitLod\0" // IR(33046, 33)
  "ImageSparseSampleProjDrefImplicitLod\0" // IR(33079, 37)
  "ImageSparseSampleProjDrefExplicitLod\0" // IR(33116, 37)
  "ImageSparseFetch\0" // IR(33153, 17)
  "ImageSparseGather\0" // IR(33170, 18)
  "ImageSparseDrefGather\0" // IR(33188, 22)
  "ImageSparseTexelsResident\0" // IR(33210, 26)
  "NoLine\0" // IR(33236, 7)
  "AtomicFlagTestAndSet\0" // IR(33243, 21)
  "AtomicFlagClear\0" // IR(33264, 16)
  "ImageSparseRead\0" // IR(33280, 16)
  "SizeOf\0" // IR(33296, 7)
  "TypePipeStorage\0" // IR(33303, 16)
  "ConstantPipeStorage\0" // IR(33319, 20)
  "CreatePipeFromPipeStorage\0" // IR(33339, 26)
  "GetKernelLocalSizeForSubgroupCount\0" // IR(33365, 35)
  "GetKernelMaxNumSubgroups\0" // IR(33400, 25)
  "TypeNamedBarrier\0" // IR(33425, 17)
  "NamedBarrierInitialize\0" // IR(33442, 23)
  "MemoryNamedBarrier\0" // IR(33465, 19)
  "ModuleProcessed\0" // IR(33484, 16)
  "ExecutionModeId\0" // IR(33500, 16)
  "DecorateId\0" // IR(33516, 11)
  "GroupNonUniformElect\0" // IR(33527, 21)
  "GroupNonUniformAll\0" // IR(33548, 19)
  "GroupNonUniformAny\0" // IR(33567, 19)
  "GroupNonUniformAllEqual\0" // IR(33586, 24)
  "GroupNonUniformBroadcast\0" // IR(33610, 25)
  "GroupNonUniformBroadcastFirst\0" // IR(33635, 30)
  "GroupNonUniformInverseBallot\0" // IR(33665, 29)
  "GroupNonUniformBallotBitExtract\0" // IR(33694, 32)
  "GroupNonUniformBallotBitCount\0" // IR(33726, 30)
  "GroupNonUniformBallotFindLSB\0" // IR(33756, 29)
  "GroupNonUniformBallotFindMSB\0" // IR(33785, 29)
  "GroupNonUniformShuffleXor\0" // IR(33814, 26)
  "GroupNonUniformShuffleUp\0" // IR(33840, 25)
  "GroupNonUniformShuffleDown\0" // IR(33865, 27)
  "GroupNonUniformIAdd\0" // IR(33892, 20)
  "GroupNonUniformFAdd\0" // IR(33912, 20)
  "GroupNonUniformIMul\0" // IR(33932, 20)
  "GroupNonUniformFMul\0" // IR(33952, 20)
  "GroupNonUniformSMin\0" // IR(33972, 20)
  "GroupNonUniformUMin\0" // IR(33992, 20)
  "GroupNonUniformFMin\0" // IR(34012, 20)
  "GroupNonUniformSMax\0" // IR(34032, 20)
  "GroupNonUniformUMax\0" // IR(34052, 20)
  "GroupNonUniformFMax\0" // IR(34072, 20)
  "GroupNonUniformBitwiseAnd\0" // IR(34092, 26)
  "GroupNonUniformBitwiseOr\0" // IR(34118, 25)
  "GroupNonUniformBitwiseXor\0" // IR(34143, 26)
  "GroupNonUniformLogicalAnd\0" // IR(34169, 26)
  "GroupNonUniformLogicalOr\0" // IR(34195, 25)
  "GroupNonUniformLogicalXor\0" // IR(34220, 26)
  "GroupNonUniformQuadBroadcast\0" // IR(34246, 29)
  "GroupNonUniformQuadSwap\0" // IR(34275, 24)
  "CopyLogical\0" // IR(34299, 12)
  "PtrEqual\0" // IR(34311, 9)
  "PtrNotEqual\0" // IR(34320, 12)
  "PtrDiff\0" // IR(34332, 8)
  "ColorAttachmentReadEXT\0" // IR(34340, 23)
  "DepthAttachmentReadEXT\0" // IR(34363, 23)
  "StencilAttachmentReadEXT\0" // IR(34386, 25)
  "TypeTensorARM\0" // IR(34411, 14)
  "SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS\0" // IR(34425, 42)
  "TensorReadARM\0" // IR(34467, 14)
  "TensorWriteARM\0" // IR(34481, 15)
  "TensorQuerySizeARM\0" // IR(34496, 19)
  "GraphConstantARM\0" // IR(34515, 17)
  "GraphEntryPointARM\0" // IR(34532, 19)
  "GraphInputARM\0" // IR(34551, 14)
  "GraphSetOutputARM\0" // IR(34565, 18)
  "GraphEndARM\0" // IR(34583, 12)
  "TypeGraphARM\0" // IR(34595, 13)
  "TerminateInvocation\0" // IR(34608, 20)
  "TypeUntypedPointerKHR\0" // IR(34628, 22)
  "UntypedVariableKHR\0" // IR(34650, 19)
  "UntypedAccessChainKHR\0" // IR(34669, 22)
  "UntypedInBoundsAccessChainKHR\0" // IR(34691, 30)
  "SubgroupFirstInvocationKHR\0" // IR(34721, 27)
  "UntypedPtrAccessChainKHR\0" // IR(34748, 25)
  "UntypedInBoundsPtrAccessChainKHR\0" // IR(34773, 33)
  "UntypedArrayLengthKHR\0" // IR(34806, 22)
  "UntypedPrefetchKHR\0" // IR(34828, 19)
  "FmaKHR\0" // IR(34847, 7)
  "SubgroupAllKHR\0" // IR(34854, 15)
  "SubgroupAnyKHR\0" // IR(34869, 15)
  "SubgroupAllEqualKHR\0" // IR(34884, 20)
  "SubgroupReadInvocationKHR\0" // IR(34904, 26)
  "ExtInstWithForwardRefsKHR\0" // IR(34930, 26)
  "UntypedGroupAsyncCopyKHR\0" // IR(34956, 25)
  "TraceRayKHR\0" // IR(34981, 12)
  "ExecuteCallableKHR\0" // IR(34993, 19)
  "ConvertUToAccelerationStructureKHR\0" // IR(35012, 35)
  "IgnoreIntersectionKHR\0" // IR(35047, 22)
  "TerminateRayKHR\0" // IR(35069, 16)
  "SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT\0" // IR(35085, 47)
  "SDot\0" // IR(35132, 5)
  "SDotKHR\0" // IR(35137, 8)
  "UDot\0" // IR(35145, 5)
  "UDotKHR\0" // IR(35150, 8)
  "SUDot\0" // IR(35158, 6)
  "SUDotKHR\0" // IR(35164, 9)
  "SDotAccSat\0" // IR(35173, 11)
  "SDotAccSatKHR\0" // IR(35184, 14)
  "UDotAccSat\0" // IR(35198, 11)
  "UDotAccSatKHR\0" // IR(35209, 14)
  "SUDotAccSat\0" // IR(35223, 12)
  "SUDotAccSatKHR\0" // IR(35235, 15)
  "TypeCooperativeMatrixKHR\0" // IR(35250, 25)
  "CooperativeMatrixLoadKHR\0" // IR(35275, 25)
  "CooperativeMatrixStoreKHR\0" // IR(35300, 26)
  "SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS\0" // IR(35326, 54)
  "CooperativeMatrixMulAddKHR\0" // IR(35380, 27)
  "CooperativeMatrixLengthKHR\0" // IR(35407, 27)
  "ConstantCompositeReplicateEXT\0" // IR(35434, 30)
  "SpecConstantCompositeReplicateEXT\0" // IR(35464, 34)
  "CompositeConstructReplicateEXT\0" // IR(35498, 31)
  "TypeRayQueryKHR\0" // IR(35529, 16)
  "RayQueryInitializeKHR\0" // IR(35545, 22)
  "RayQueryTerminateKHR\0" // IR(35567, 21)
  "RayQueryGenerateIntersectionKHR\0" // IR(35588, 32)
  "RayQueryConfirmIntersectionKHR\0" // IR(35620, 31)
  "RayQueryProceedKHR\0" // IR(35651, 19)
  "RayQueryGetIntersectionTypeKHR\0" // IR(35670, 31)
  "ImageSampleWeightedQCOM\0" // IR(35701, 24)
  "ImageBoxFilterQCOM\0" // IR(35725, 19)
  "ImageBlockMatchSSDQCOM\0" // IR(35744, 23)
  "ImageBlockMatchSADQCOM\0" // IR(35767, 23)
  "BitCastArrayQCOM\0" // IR(35790, 17)
  "ImageBlockMatchWindowSSDQCOM\0" // IR(35807, 29)
  "ImageBlockMatchWindowSADQCOM\0" // IR(35836, 29)
  "ImageBlockMatchGatherSSDQCOM\0" // IR(35865, 29)
  "ImageBlockMatchGatherSADQCOM\0" // IR(35894, 29)
  "CompositeConstructCoopMatQCOM\0" // IR(35923, 30)
  "CompositeExtractCoopMatQCOM\0" // IR(35953, 28)
  "ExtractSubArrayQCOM\0" // IR(35981, 20)
  "GroupIAddNonUniformAMD\0" // IR(36001, 23)
  "GroupFAddNonUniformAMD\0" // IR(36024, 23)
  "GroupFMinNonUniformAMD\0" // IR(36047, 23)
  "GroupUMinNonUniformAMD\0" // IR(36070, 23)
  "GroupSMinNonUniformAMD\0" // IR(36093, 23)
  "GroupFMaxNonUniformAMD\0" // IR(36116, 23)
  "GroupUMaxNonUniformAMD\0" // IR(36139, 23)
  "GroupSMaxNonUniformAMD\0" // IR(36162, 23)
  "FragmentMaskFetchAMD\0" // IR(36185, 21)
  "FragmentFetchAMD\0" // IR(36206, 17)
  "ReadClockKHR\0" // IR(36223, 13)
  "AllocateNodePayloadsAMDX\0" // IR(36236, 25)
  "EnqueueNodePayloadsAMDX\0" // IR(36261, 24)
  "TypeNodePayloadArrayAMDX\0" // IR(36285, 25)
  "FinishWritingNodePayloadAMDX\0" // IR(36310, 29)
  "NodePayloadArrayLengthAMDX\0" // IR(36339, 27)
  "IsNodePayloadValidAMDX\0" // IR(36366, 23)
  "ConstantStringAMDX\0" // IR(36389, 19)
  "SpecConstantStringAMDX\0" // IR(36408, 23)
  "GroupNonUniformQuadAllKHR\0" // IR(36431, 26)
  "GroupNonUniformQuadAnyKHR\0" // IR(36457, 26)
  "TypeBufferEXT\0" // IR(36483, 14)
  "BufferPointerEXT\0" // IR(36497, 17)
  "UntypedImageTexelPointerEXT\0" // IR(36514, 28)
  "MemberDecorateIdEXT\0" // IR(36542, 20)
  "ConstantSizeOfEXT\0" // IR(36562, 18)
  "HitObjectRecordHitMotionNV\0" // IR(36580, 27)
  "HitObjectRecordHitWithIndexMotionNV\0" // IR(36607, 36)
  "HitObjectRecordMissMotionNV\0" // IR(36643, 28)
  "HitObjectGetWorldToObjectNV\0" // IR(36671, 28)
  "HitObjectGetObjectToWorldNV\0" // IR(36699, 28)
  "HitObjectGetObjectRayDirectionNV\0" // IR(36727, 33)
  "HitObjectGetObjectRayOriginNV\0" // IR(36760, 30)
  "HitObjectTraceRayMotionNV\0" // IR(36790, 26)
  "HitObjectGetShaderRecordBufferHandleNV\0" // IR(36816, 39)
  "HitObjectGetShaderBindingTableRecordIndexNV\0" // IR(36855, 44)
  "HitObjectRecordEmptyNV\0" // IR(36899, 23)
  "HitObjectTraceRayNV\0" // IR(36922, 20)
  "HitObjectRecordHitNV\0" // IR(36942, 21)
  "HitObjectRecordHitWithIndexNV\0" // IR(36963, 30)
  "HitObjectRecordMissNV\0" // IR(36993, 22)
  "HitObjectExecuteShaderNV\0" // IR(37015, 25)
  "HitObjectGetCurrentTimeNV\0" // IR(37040, 26)
  "HitObjectGetAttributesNV\0" // IR(37066, 25)
  "HitObjectGetHitKindNV\0" // IR(37091, 22)
  "HitObjectGetPrimitiveIndexNV\0" // IR(37113, 29)
  "HitObjectGetGeometryIndexNV\0" // IR(37142, 28)
  "HitObjectGetInstanceIdNV\0" // IR(37170, 25)
  "HitObjectGetInstanceCustomIndexNV\0" // IR(37195, 34)
  "HitObjectGetWorldRayDirectionNV\0" // IR(37229, 32)
  "HitObjectGetWorldRayOriginNV\0" // IR(37261, 29)
  "HitObjectGetRayTMaxNV\0" // IR(37290, 22)
  "HitObjectGetRayTMinNV\0" // IR(37312, 22)
  "HitObjectIsEmptyNV\0" // IR(37334, 19)
  "HitObjectIsHitNV\0" // IR(37353, 17)
  "HitObjectIsMissNV\0" // IR(37370, 18)
  "ReorderThreadWithHitObjectNV\0" // IR(37388, 29)
  "ReorderThreadWithHintNV\0" // IR(37417, 24)
  "TypeHitObjectNV\0" // IR(37441, 16)
  "ImageSampleFootprintNV\0" // IR(37457, 23)
  "TypeVectorIdEXT\0" // IR(37480, 16)
  "TypeCooperativeVectorNV\0" // IR(37496, 24)
  "CooperativeVectorMatrixMulNV\0" // IR(37520, 29)
  "CooperativeVectorOuterProductAccumulateNV\0" // IR(37549, 42)
  "CooperativeVectorReduceSumAccumulateNV\0" // IR(37591, 39)
  "CooperativeVectorMatrixMulAddNV\0" // IR(37630, 32)
  "CooperativeMatrixConvertNV\0" // IR(37662, 27)
  "EmitMeshTasksEXT\0" // IR(37689, 17)
  "SetMeshOutputsEXT\0" // IR(37706, 18)
  "GroupNonUniformPartitionEXT\0" // IR(37724, 28)
  "GroupNonUniformPartitionNV\0" // IR(37752, 27)
  "WritePackedPrimitiveIndices4x8NV\0" // IR(37779, 33)
  "FetchMicroTriangleVertexPositionNV\0" // IR(37812, 35)
  "FetchMicroTriangleVertexBarycentricNV\0" // IR(37847, 38)
  "CooperativeVectorLoadNV\0" // IR(37885, 24)
  "CooperativeVectorStoreNV\0" // IR(37909, 25)
  "HitObjectRecordFromQueryEXT\0" // IR(37934, 28)
  "HitObjectRecordMissEXT\0" // IR(37962, 23)
  "HitObjectRecordMissMotionEXT\0" // IR(37985, 29)
  "HitObjectGetIntersectionTriangleVertexPositionsEXT\0" // IR(38014, 51)
  "HitObjectGetRayFlagsEXT\0" // IR(38065, 24)
  "HitObjectSetShaderBindingTableRecordIndexEXT\0" // IR(38089, 45)
  "HitObjectReorderExecuteShaderEXT\0" // IR(38134, 33)
  "HitObjectTraceReorderExecuteEXT\0" // IR(38167, 32)
  "HitObjectTraceMotionReorderExecuteEXT\0" // IR(38199, 38)
  "TypeHitObjectEXT\0" // IR(38237, 17)
  "ReorderThreadWithHintEXT\0" // IR(38254, 25)
  "ReorderThreadWithHitObjectEXT\0" // IR(38279, 30)
  "HitObjectTraceRayEXT\0" // IR(38309, 21)
  "HitObjectTraceRayMotionEXT\0" // IR(38330, 27)
  "HitObjectRecordEmptyEXT\0" // IR(38357, 24)
  "HitObjectExecuteShaderEXT\0" // IR(38381, 26)
  "HitObjectGetCurrentTimeEXT\0" // IR(38407, 27)
  "HitObjectGetAttributesEXT\0" // IR(38434, 26)
  "HitObjectGetHitKindEXT\0" // IR(38460, 23)
  "HitObjectGetPrimitiveIndexEXT\0" // IR(38483, 30)
  "HitObjectGetGeometryIndexEXT\0" // IR(38513, 29)
  "HitObjectGetInstanceIdEXT\0" // IR(38542, 26)
  "HitObjectGetInstanceCustomIndexEXT\0" // IR(38568, 35)
  "HitObjectGetObjectRayOriginEXT\0" // IR(38603, 31)
  "HitObjectGetObjectRayDirectionEXT\0" // IR(38634, 34)
  "HitObjectGetWorldRayDirectionEXT\0" // IR(38668, 33)
  "HitObjectGetWorldRayOriginEXT\0" // IR(38701, 30)
  "HitObjectGetObjectToWorldEXT\0" // IR(38731, 29)
  "HitObjectGetWorldToObjectEXT\0" // IR(38760, 29)
  "HitObjectGetRayTMaxEXT\0" // IR(38789, 23)
  "ReportIntersectionKHR\0" // IR(38812, 22)
  "ReportIntersectionNV\0" // IR(38834, 21)
  "IgnoreIntersectionNV\0" // IR(38855, 21)
  "TerminateRayNV\0" // IR(38876, 15)
  "TraceNV\0" // IR(38891, 8)
  "TraceMotionNV\0" // IR(38899, 14)
  "TraceRayMotionNV\0" // IR(38913, 17)
  "RayQueryGetIntersectionTriangleVertexPositionsKHR\0" // IR(38930, 50)
  "TypeAccelerationStructureKHR\0" // IR(38980, 29)
  "TypeAccelerationStructureNV\0" // IR(39009, 28)
  "ExecuteCallableNV\0" // IR(39037, 18)
  "RayQueryGetIntersectionClusterIdNV\0" // IR(39055, 35)
  "RayQueryGetClusterIdNV\0" // IR(39090, 23)
  "HitObjectGetClusterIdNV\0" // IR(39113, 24)
  "HitObjectGetRayTMinEXT\0" // IR(39137, 23)
  "HitObjectGetShaderBindingTableRecordIndexEXT\0" // IR(39160, 45)
  "HitObjectGetShaderRecordBufferHandleEXT\0" // IR(39205, 40)
  "HitObjectIsEmptyEXT\0" // IR(39245, 20)
  "HitObjectIsHitEXT\0" // IR(39265, 18)
  "HitObjectIsMissEXT\0" // IR(39283, 19)
  "TypeCooperativeMatrixNV\0" // IR(39302, 24)
  "CooperativeMatrixLoadNV\0" // IR(39326, 24)
  "CooperativeMatrixStoreNV\0" // IR(39350, 25)
  "CooperativeMatrixMulAddNV\0" // IR(39375, 26)
  "CooperativeMatrixLengthNV\0" // IR(39401, 26)
  "BeginInvocationInterlockEXT\0" // IR(39427, 28)
  "EndInvocationInterlockEXT\0" // IR(39455, 26)
  "SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE\0" // IR(39481, 43)
  "CooperativeMatrixReduceNV\0" // IR(39524, 26)
  "SPV_OPERAND_TYPE_MEMORY_ACCESS\0" // IR(39550, 31)
  "SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS\0" // IR(39581, 44)
  "CooperativeMatrixLoadTensorNV\0" // IR(39625, 30)
  "CooperativeMatrixStoreTensorNV\0" // IR(39655, 31)
  "CooperativeMatrixPerElementOpNV\0" // IR(39686, 32)
  "TypeTensorLayoutNV\0" // IR(39718, 19)
  "TypeTensorViewNV\0" // IR(39737, 17)
  "CreateTensorLayoutNV\0" // IR(39754, 21)
  "TensorLayoutSetDimensionNV\0" // IR(39775, 27)
  "TensorLayoutSetStrideNV\0" // IR(39802, 24)
  "TensorLayoutSliceNV\0" // IR(39826, 20)
  "TensorLayoutSetClampValueNV\0" // IR(39846, 28)
  "CreateTensorViewNV\0" // IR(39874, 19)
  "TensorViewSetDimensionNV\0" // IR(39893, 25)
  "TensorViewSetStrideNV\0" // IR(39918, 22)
  "IsHelperInvocationEXT\0" // IR(39940, 22)
  "TensorViewSetClipNV\0" // IR(39962, 20)
  "TensorLayoutSetBlockSizeNV\0" // IR(39982, 27)
  "CooperativeMatrixTransposeNV\0" // IR(40009, 29)
  "ConvertUToImageNV\0" // IR(40038, 18)
  "ConvertUToSamplerNV\0" // IR(40056, 20)
  "ConvertImageToUNV\0" // IR(40076, 18)
  "ConvertSamplerToUNV\0" // IR(40094, 20)
  "ConvertUToSampledImageNV\0" // IR(40114, 25)
  "ConvertSampledImageToUNV\0" // IR(40139, 25)
  "SamplerImageAddressingModeNV\0" // IR(40164, 29)
  "SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS\0" // IR(40193, 52)
  "RawAccessChainNV\0" // IR(40245, 17)
  "RayQueryGetIntersectionSpherePositionNV\0" // IR(40262, 40)
  "RayQueryGetIntersectionSphereRadiusNV\0" // IR(40302, 38)
  "RayQueryGetIntersectionLSSPositionsNV\0" // IR(40340, 38)
  "RayQueryGetIntersectionLSSRadiiNV\0" // IR(40378, 34)
  "RayQueryGetIntersectionLSSHitValueNV\0" // IR(40412, 37)
  "HitObjectGetSpherePositionNV\0" // IR(40449, 29)
  "HitObjectGetSphereRadiusNV\0" // IR(40478, 27)
  "HitObjectGetLSSPositionsNV\0" // IR(40505, 27)
  "HitObjectGetLSSRadiiNV\0" // IR(40532, 23)
  "HitObjectIsSphereHitNV\0" // IR(40555, 23)
  "HitObjectIsLSSHitNV\0" // IR(40578, 20)
  "RayQueryIsSphereHitNV\0" // IR(40598, 22)
  "RayQueryIsLSSHitNV\0" // IR(40620, 19)
  "SubgroupShuffleDownINTEL\0" // IR(40639, 25)
  "SubgroupShuffleUpINTEL\0" // IR(40664, 23)
  "SubgroupShuffleXorINTEL\0" // IR(40687, 24)
  "SubgroupBlockReadINTEL\0" // IR(40711, 23)
  "SubgroupBlockWriteINTEL\0" // IR(40734, 24)
  "SubgroupImageBlockReadINTEL\0" // IR(40758, 28)
  "SubgroupImageBlockWriteINTEL\0" // IR(40786, 29)
  "SubgroupImageMediaBlockReadINTEL\0" // IR(40815, 33)
  "SubgroupImageMediaBlockWriteINTEL\0" // IR(40848, 34)
  "UCountLeadingZerosINTEL\0" // IR(40882, 24)
  "UCountTrailingZerosINTEL\0" // IR(40906, 25)
  "AbsISubINTEL\0" // IR(40931, 13)
  "AbsUSubINTEL\0" // IR(40944, 13)
  "IAddSatINTEL\0" // IR(40957, 13)
  "UAddSatINTEL\0" // IR(40970, 13)
  "IAverageINTEL\0" // IR(40983, 14)
  "UAverageINTEL\0" // IR(40997, 14)
  "IAverageRoundedINTEL\0" // IR(41011, 21)
  "UAverageRoundedINTEL\0" // IR(41032, 21)
  "ISubSatINTEL\0" // IR(41053, 13)
  "USubSatINTEL\0" // IR(41066, 13)
  "IMul32x16INTEL\0" // IR(41079, 15)
  "UMul32x16INTEL\0" // IR(41094, 15)
  "ConstantFunctionPointerINTEL\0" // IR(41109, 29)
  "FunctionPointerCallINTEL\0" // IR(41138, 25)
  "AsmTargetINTEL\0" // IR(41163, 15)
  "AsmCallINTEL\0" // IR(41178, 13)
  "AtomicFMinEXT\0" // IR(41191, 14)
  "AtomicFMaxEXT\0" // IR(41205, 14)
  "AssumeTrueKHR\0" // IR(41219, 14)
  "ExpectKHR\0" // IR(41233, 10)
  "DecorateString\0" // IR(41243, 15)
  "DecorateStringGOOGLE\0" // IR(41258, 21)
  "MemberDecorateString\0" // IR(41279, 21)
  "MemberDecorateStringGOOGLE\0" // IR(41300, 27)
  "VmeImageINTEL\0" // IR(41327, 14)
  "TypeVmeImageINTEL\0" // IR(41341, 18)
  "TypeAvcImePayloadINTEL\0" // IR(41359, 23)
  "TypeAvcRefPayloadINTEL\0" // IR(41382, 23)
  "TypeAvcSicPayloadINTEL\0" // IR(41405, 23)
  "TypeAvcMcePayloadINTEL\0" // IR(41428, 23)
  "TypeAvcMceResultINTEL\0" // IR(41451, 22)
  "TypeAvcImeResultINTEL\0" // IR(41473, 22)
  "TypeAvcImeResultSingleReferenceStreamoutINTEL\0" // IR(41495, 46)
  "TypeAvcImeResultDualReferenceStreamoutINTEL\0" // IR(41541, 44)
  "TypeAvcImeSingleReferenceStreaminINTEL\0" // IR(41585, 39)
  "TypeAvcImeDualReferenceStreaminINTEL\0" // IR(41624, 37)
  "TypeAvcRefResultINTEL\0" // IR(41661, 22)
  "TypeAvcSicResultINTEL\0" // IR(41683, 22)
  "SubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL\0" // IR(41705, 60)
  "SubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL\0" // IR(41765, 53)
  "SubgroupAvcMceGetDefaultInterShapePenaltyINTEL\0" // IR(41818, 47)
  "SubgroupAvcMceSetInterShapePenaltyINTEL\0" // IR(41865, 40)
  "SubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL\0" // IR(41905, 51)
  "SubgroupAvcMceSetInterDirectionPenaltyINTEL\0" // IR(41956, 44)
  "SubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL\0" // IR(42000, 51)
  "SubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL\0" // IR(42051, 56)
  "SubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL\0" // IR(42107, 50)
  "SubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL\0" // IR(42157, 52)
  "SubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL\0" // IR(42209, 49)
  "SubgroupAvcMceSetMotionVectorCostFunctionINTEL\0" // IR(42258, 47)
  "SubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL\0" // IR(42305, 50)
  "SubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL\0" // IR(42355, 51)
  "SubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL\0" // IR(42406, 56)
  "SubgroupAvcMceSetAcOnlyHaarINTEL\0" // IR(42462, 33)
  "SubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL\0" // IR(42495, 52)
  "SubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL\0" // IR(42547, 61)
  "SubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL\0" // IR(42608, 61)
  "SubgroupAvcMceConvertToImePayloadINTEL\0" // IR(42669, 39)
  "SubgroupAvcMceConvertToImeResultINTEL\0" // IR(42708, 38)
  "SubgroupAvcMceConvertToRefPayloadINTEL\0" // IR(42746, 39)
  "SubgroupAvcMceConvertToRefResultINTEL\0" // IR(42785, 38)
  "SubgroupAvcMceConvertToSicPayloadINTEL\0" // IR(42823, 39)
  "SubgroupAvcMceConvertToSicResultINTEL\0" // IR(42862, 38)
  "SubgroupAvcMceGetMotionVectorsINTEL\0" // IR(42900, 36)
  "SubgroupAvcMceGetInterDistortionsINTEL\0" // IR(42936, 39)
  "SubgroupAvcMceGetBestInterDistortionsINTEL\0" // IR(42975, 43)
  "SubgroupAvcMceGetInterMajorShapeINTEL\0" // IR(43018, 38)
  "SubgroupAvcMceGetInterMinorShapeINTEL\0" // IR(43056, 38)
  "SubgroupAvcMceGetInterDirectionsINTEL\0" // IR(43094, 38)
  "SubgroupAvcMceGetInterMotionVectorCountINTEL\0" // IR(43132, 45)
  "SubgroupAvcMceGetInterReferenceIdsINTEL\0" // IR(43177, 40)
  "SubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL\0" // IR(43217, 62)
  "SubgroupAvcImeInitializeINTEL\0" // IR(43279, 30)
  "SubgroupAvcImeSetSingleReferenceINTEL\0" // IR(43309, 38)
  "SubgroupAvcImeSetDualReferenceINTEL\0" // IR(43347, 36)
  "SubgroupAvcImeRefWindowSizeINTEL\0" // IR(43383, 33)
  "SubgroupAvcImeAdjustRefOffsetINTEL\0" // IR(43416, 35)
  "SubgroupAvcImeConvertToMcePayloadINTEL\0" // IR(43451, 39)
  "SubgroupAvcImeSetMaxMotionVectorCountINTEL\0" // IR(43490, 43)
  "SubgroupAvcImeSetUnidirectionalMixDisableINTEL\0" // IR(43533, 47)
  "SubgroupAvcImeSetEarlySearchTerminationThresholdINTEL\0" // IR(43580, 54)
  "SubgroupAvcImeSetWeightedSadINTEL\0" // IR(43634, 34)
  "SubgroupAvcImeEvaluateWithSingleReferenceINTEL\0" // IR(43668, 47)
  "SubgroupAvcImeEvaluateWithDualReferenceINTEL\0" // IR(43715, 45)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL\0" // IR(43760, 55)
  "SubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL\0" // IR(43815, 53)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL\0" // IR(43868, 56)
  "SubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL\0" // IR(43924, 54)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL\0" // IR(43978, 58)
  "SubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL\0" // IR(44036, 56)
  "SubgroupAvcImeConvertToMceResultINTEL\0" // IR(44092, 38)
  "SubgroupAvcImeGetSingleReferenceStreaminINTEL\0" // IR(44130, 46)
  "SubgroupAvcImeGetDualReferenceStreaminINTEL\0" // IR(44176, 44)
  "SubgroupAvcImeStripSingleReferenceStreamoutINTEL\0" // IR(44220, 49)
  "SubgroupAvcImeStripDualReferenceStreamoutINTEL\0" // IR(44269, 47)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL\0" // IR(44316, 70)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL\0" // IR(44386, 68)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL\0" // IR(44454, 69)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL\0" // IR(44523, 68)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL\0" // IR(44591, 66)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL\0" // IR(44657, 67)
  "SubgroupAvcImeGetBorderReachedINTEL\0" // IR(44724, 36)
  "SubgroupAvcImeGetTruncatedSearchIndicationINTEL\0" // IR(44760, 48)
  "SubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL\0" // IR(44808, 59)
  "SubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL\0" // IR(44867, 58)
  "SubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL\0" // IR(44925, 56)
  "SubgroupAvcFmeInitializeINTEL\0" // IR(44981, 30)
  "SubgroupAvcBmeInitializeINTEL\0" // IR(45011, 30)
  "SubgroupAvcRefConvertToMcePayloadINTEL\0" // IR(45041, 39)
  "SubgroupAvcRefSetBidirectionalMixDisableINTEL\0" // IR(45080, 46)
  "SubgroupAvcRefSetBilinearFilterEnableINTEL\0" // IR(45126, 43)
  "SubgroupAvcRefEvaluateWithSingleReferenceINTEL\0" // IR(45169, 47)
  "SubgroupAvcRefEvaluateWithDualReferenceINTEL\0" // IR(45216, 45)
  "SubgroupAvcRefEvaluateWithMultiReferenceINTEL\0" // IR(45261, 46)
  "SubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL\0" // IR(45307, 56)
  "SubgroupAvcRefConvertToMceResultINTEL\0" // IR(45363, 38)
  "SubgroupAvcSicInitializeINTEL\0" // IR(45401, 30)
  "SubgroupAvcSicConfigureSkcINTEL\0" // IR(45431, 32)
  "SubgroupAvcSicConfigureIpeLumaINTEL\0" // IR(45463, 36)
  "SubgroupAvcSicConfigureIpeLumaChromaINTEL\0" // IR(45499, 42)
  "SubgroupAvcSicGetMotionVectorMaskINTEL\0" // IR(45541, 39)
  "SubgroupAvcSicConvertToMcePayloadINTEL\0" // IR(45580, 39)
  "SubgroupAvcSicSetIntraLumaShapePenaltyINTEL\0" // IR(45619, 44)
  "SubgroupAvcSicSetIntraLumaModeCostFunctionINTEL\0" // IR(45663, 48)
  "SubgroupAvcSicSetIntraChromaModeCostFunctionINTEL\0" // IR(45711, 50)
  "SubgroupAvcSicSetBilinearFilterEnableINTEL\0" // IR(45761, 43)
  "SubgroupAvcSicSetSkcForwardTransformEnableINTEL\0" // IR(45804, 48)
  "SubgroupAvcSicSetBlockBasedRawSkipSadINTEL\0" // IR(45852, 43)
  "SubgroupAvcSicEvaluateIpeINTEL\0" // IR(45895, 31)
  "SubgroupAvcSicEvaluateWithSingleReferenceINTEL\0" // IR(45926, 47)
  "SubgroupAvcSicEvaluateWithDualReferenceINTEL\0" // IR(45973, 45)
  "SubgroupAvcSicEvaluateWithMultiReferenceINTEL\0" // IR(46018, 46)
  "SubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL\0" // IR(46064, 56)
  "SubgroupAvcSicConvertToMceResultINTEL\0" // IR(46120, 38)
  "SubgroupAvcSicGetIpeLumaShapeINTEL\0" // IR(46158, 35)
  "SubgroupAvcSicGetBestIpeLumaDistortionINTEL\0" // IR(46193, 44)
  "SubgroupAvcSicGetBestIpeChromaDistortionINTEL\0" // IR(46237, 46)
  "SubgroupAvcSicGetPackedIpeLumaModesINTEL\0" // IR(46283, 41)
  "SubgroupAvcSicGetIpeChromaModeINTEL\0" // IR(46324, 36)
  "SubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL\0" // IR(46360, 50)
  "SubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL\0" // IR(46410, 48)
  "SubgroupAvcSicGetInterRawSadsINTEL\0" // IR(46458, 35)
  "SaveMemoryINTEL\0" // IR(46493, 16)
  "RestoreMemoryINTEL\0" // IR(46509, 19)
  "ArbitraryFloatSinCosPiALTERA\0" // IR(46528, 29)
  "ArbitraryFloatSinCosPiINTEL\0" // IR(46557, 28)
  "ArbitraryFloatCastALTERA\0" // IR(46585, 25)
  "ArbitraryFloatCastINTEL\0" // IR(46610, 24)
  "ArbitraryFloatCastFromIntALTERA\0" // IR(46634, 32)
  "ArbitraryFloatCastFromIntINTEL\0" // IR(46666, 31)
  "ArbitraryFloatCastToIntALTERA\0" // IR(46697, 30)
  "ArbitraryFloatCastToIntINTEL\0" // IR(46727, 29)
  "ArbitraryFloatAddALTERA\0" // IR(46756, 24)
  "ArbitraryFloatAddINTEL\0" // IR(46780, 23)
  "ArbitraryFloatSubALTERA\0" // IR(46803, 24)
  "ArbitraryFloatSubINTEL\0" // IR(46827, 23)
  "ArbitraryFloatMulALTERA\0" // IR(46850, 24)
  "ArbitraryFloatMulINTEL\0" // IR(46874, 23)
  "ArbitraryFloatDivALTERA\0" // IR(46897, 24)
  "ArbitraryFloatDivINTEL\0" // IR(46921, 23)
  "ArbitraryFloatGTALTERA\0" // IR(46944, 23)
  "ArbitraryFloatGTINTEL\0" // IR(46967, 22)
  "ArbitraryFloatGEALTERA\0" // IR(46989, 23)
  "ArbitraryFloatGEINTEL\0" // IR(47012, 22)
  "ArbitraryFloatLTALTERA\0" // IR(47034, 23)
  "ArbitraryFloatLTINTEL\0" // IR(47057, 22)
  "ArbitraryFloatLEALTERA\0" // IR(47079, 23)
  "ArbitraryFloatLEINTEL\0" // IR(47102, 22)
  "ArbitraryFloatEQALTERA\0" // IR(47124, 23)
  "ArbitraryFloatEQINTEL\0" // IR(47147, 22)
  "ArbitraryFloatRecipALTERA\0" // IR(47169, 26)
  "ArbitraryFloatRecipINTEL\0" // IR(47195, 25)
  "ArbitraryFloatRSqrtALTERA\0" // IR(47220, 26)
  "ArbitraryFloatRSqrtINTEL\0" // IR(47246, 25)
  "ArbitraryFloatCbrtALTERA\0" // IR(47271, 25)
  "ArbitraryFloatCbrtINTEL\0" // IR(47296, 24)
  "ArbitraryFloatHypotALTERA\0" // IR(47320, 26)
  "ArbitraryFloatHypotINTEL\0" // IR(47346, 25)
  "ArbitraryFloatSqrtALTERA\0" // IR(47371, 25)
  "ArbitraryFloatSqrtINTEL\0" // IR(47396, 24)
  "ArbitraryFloatLogINTEL\0" // IR(47420, 23)
  "ArbitraryFloatLog2INTEL\0" // IR(47443, 24)
  "ArbitraryFloatLog10INTEL\0" // IR(47467, 25)
  "ArbitraryFloatLog1pINTEL\0" // IR(47492, 25)
  "ArbitraryFloatExpINTEL\0" // IR(47517, 23)
  "ArbitraryFloatExp2INTEL\0" // IR(47540, 24)
  "ArbitraryFloatExp10INTEL\0" // IR(47564, 25)
  "ArbitraryFloatExpm1INTEL\0" // IR(47589, 25)
  "ArbitraryFloatSinINTEL\0" // IR(47614, 23)
  "ArbitraryFloatCosINTEL\0" // IR(47637, 23)
  "ArbitraryFloatSinCosINTEL\0" // IR(47660, 26)
  "ArbitraryFloatSinPiINTEL\0" // IR(47686, 25)
  "ArbitraryFloatCosPiINTEL\0" // IR(47711, 25)
  "ArbitraryFloatASinINTEL\0" // IR(47736, 24)
  "ArbitraryFloatASinPiINTEL\0" // IR(47760, 26)
  "ArbitraryFloatACosINTEL\0" // IR(47786, 24)
  "ArbitraryFloatACosPiINTEL\0" // IR(47810, 26)
  "ArbitraryFloatATanINTEL\0" // IR(47836, 24)
  "ArbitraryFloatATanPiINTEL\0" // IR(47860, 26)
  "ArbitraryFloatATan2INTEL\0" // IR(47886, 25)
  "ArbitraryFloatPowINTEL\0" // IR(47911, 23)
  "ArbitraryFloatPowRINTEL\0" // IR(47934, 24)
  "ArbitraryFloatPowNINTEL\0" // IR(47958, 24)
  "LoopControlINTEL\0" // IR(47982, 17)
  "AliasDomainDeclINTEL\0" // IR(47999, 21)
  "AliasScopeDeclINTEL\0" // IR(48020, 20)
  "AliasScopeListDeclINTEL\0" // IR(48040, 24)
  "FixedSqrtALTERA\0" // IR(48064, 16)
  "FixedSqrtINTEL\0" // IR(48080, 15)
  "FixedRecipALTERA\0" // IR(48095, 17)
  "FixedRecipINTEL\0" // IR(48112, 16)
  "FixedRsqrtALTERA\0" // IR(48128, 17)
  "FixedRsqrtINTEL\0" // IR(48145, 16)
  "FixedSinALTERA\0" // IR(48161, 15)
  "FixedSinINTEL\0" // IR(48176, 14)
  "FixedCosALTERA\0" // IR(48190, 15)
  "FixedCosINTEL\0" // IR(48205, 14)
  "FixedSinCosALTERA\0" // IR(48219, 18)
  "FixedSinCosINTEL\0" // IR(48237, 17)
  "FixedSinPiALTERA\0" // IR(48254, 17)
  "FixedSinPiINTEL\0" // IR(48271, 16)
  "FixedCosPiALTERA\0" // IR(48287, 17)
  "FixedCosPiINTEL\0" // IR(48304, 16)
  "FixedSinCosPiALTERA\0" // IR(48320, 20)
  "FixedSinCosPiINTEL\0" // IR(48340, 19)
  "FixedLogALTERA\0" // IR(48359, 15)
  "FixedLogINTEL\0" // IR(48374, 14)
  "FixedExpALTERA\0" // IR(48388, 15)
  "FixedExpINTEL\0" // IR(48403, 14)
  "PtrCastToCrossWorkgroupALTERA\0" // IR(48417, 30)
  "PtrCastToCrossWorkgroupINTEL\0" // IR(48447, 29)
  "CrossWorkgroupCastToPtrALTERA\0" // IR(48476, 30)
  "CrossWorkgroupCastToPtrINTEL\0" // IR(48506, 29)
  "ReadPipeBlockingALTERA\0" // IR(48535, 23)
  "ReadPipeBlockingINTEL\0" // IR(48558, 22)
  "WritePipeBlockingALTERA\0" // IR(48580, 24)
  "WritePipeBlockingINTEL\0" // IR(48604, 23)
  "RayQueryGetRayTMinKHR\0" // IR(48627, 22)
  "RayQueryGetRayFlagsKHR\0" // IR(48649, 23)
  "RayQueryGetIntersectionTKHR\0" // IR(48672, 28)
  "RayQueryGetIntersectionInstanceCustomIndexKHR\0" // IR(48700, 46)
  "RayQueryGetIntersectionInstanceIdKHR\0" // IR(48746, 37)
  "RayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR\0" // IR(48783, 65)
  "RayQueryGetIntersectionGeometryIndexKHR\0" // IR(48848, 40)
  "RayQueryGetIntersectionPrimitiveIndexKHR\0" // IR(48888, 41)
  "RayQueryGetIntersectionBarycentricsKHR\0" // IR(48929, 39)
  "RayQueryGetIntersectionFrontFaceKHR\0" // IR(48968, 36)
  "RayQueryGetIntersectionCandidateAABBOpaqueKHR\0" // IR(49004, 46)
  "RayQueryGetIntersectionObjectRayDirectionKHR\0" // IR(49050, 45)
  "RayQueryGetIntersectionObjectRayOriginKHR\0" // IR(49095, 42)
  "RayQueryGetWorldRayDirectionKHR\0" // IR(49137, 32)
  "RayQueryGetWorldRayOriginKHR\0" // IR(49169, 29)
  "RayQueryGetIntersectionObjectToWorldKHR\0" // IR(49198, 40)
  "RayQueryGetIntersectionWorldToObjectKHR\0" // IR(49238, 40)
  "AtomicFAddEXT\0" // IR(49278, 14)
  "TypeBufferSurfaceINTEL\0" // IR(49292, 23)
  "TypeStructContinuedINTEL\0" // IR(49315, 25)
  "ConstantCompositeContinuedINTEL\0" // IR(49340, 32)
  "SpecConstantCompositeContinuedINTEL\0" // IR(49372, 36)
  "CompositeConstructContinuedINTEL\0" // IR(49408, 33)
  "ConvertFToBF16INTEL\0" // IR(49441, 20)
  "ConvertBF16ToFINTEL\0" // IR(49461, 20)
  "ControlBarrierArriveINTEL\0" // IR(49481, 26)
  "ControlBarrierWaitINTEL\0" // IR(49507, 24)
  "TaskSequenceCreateALTERA\0" // IR(49531, 25)
  "TaskSequenceCreateINTEL\0" // IR(49556, 24)
  "TaskSequenceAsyncALTERA\0" // IR(49580, 24)
  "TaskSequenceAsyncINTEL\0" // IR(49604, 23)
  "TaskSequenceGetALTERA\0" // IR(49627, 22)
  "TaskSequenceGetINTEL\0" // IR(49649, 21)
  "TaskSequenceReleaseALTERA\0" // IR(49670, 26)
  "TaskSequenceReleaseINTEL\0" // IR(49696, 25)
  "TypeTaskSequenceALTERA\0" // IR(49721, 23)
  "TypeTaskSequenceINTEL\0" // IR(49744, 22)
  "SubgroupBlockPrefetchINTEL\0" // IR(49766, 27)
  "Subgroup2DBlockLoadINTEL\0" // IR(49793, 25)
  "Subgroup2DBlockLoadTransformINTEL\0" // IR(49818, 34)
  "Subgroup2DBlockLoadTransposeINTEL\0" // IR(49852, 34)
  "Subgroup2DBlockPrefetchINTEL\0" // IR(49886, 29)
  "Subgroup2DBlockStoreINTEL\0" // IR(49915, 26)
  "SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS\0" // IR(49941, 62)
  "BitwiseFunctionINTEL\0" // IR(50003, 21)
  "ConditionalExtensionINTEL\0" // IR(50024, 26)
  "ConditionalEntryPointINTEL\0" // IR(50050, 27)
  "ConditionalCapabilityINTEL\0" // IR(50077, 27)
  "SpecConstantTargetINTEL\0" // IR(50104, 24)
  "SpecConstantArchitectureINTEL\0" // IR(50128, 30)
  "SPV_OPERAND_TYPE_VARIABLE_CAPABILITY\0" // IR(50158, 37)
  "SpecConstantCapabilitiesINTEL\0" // IR(50195, 30)
  "ConditionalCopyObjectINTEL\0" // IR(50225, 27)
  "GroupIMulKHR\0" // IR(50252, 13)
  "GroupFMulKHR\0" // IR(50265, 13)
  "GroupBitwiseAndKHR\0" // IR(50278, 19)
  "GroupBitwiseOrKHR\0" // IR(50297, 18)
  "GroupBitwiseXorKHR\0" // IR(50315, 19)
  "GroupLogicalAndKHR\0" // IR(50334, 19)
  "GroupLogicalOrKHR\0" // IR(50353, 18)
  "GroupLogicalXorKHR\0" // IR(50371, 19)
  "RoundFToTF32INTEL\0" // IR(50390, 18)
  "MaskedGatherINTEL\0" // IR(50408, 18)
  "MaskedScatterINTEL\0" // IR(50426, 19)
  "ConvertHandleToImageINTEL\0" // IR(50445, 26)
  "ConvertHandleToSamplerINTEL\0" // IR(50471, 28)
  "ConvertHandleToSampledImageINTEL\0" // IR(50499, 33)
  "DebugInfoNone\0" // IR(50532, 14)
  "DebugCompilationUnit\0" // IR(50546, 21)
  "SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING\0" // IR(50567, 52)
  "DebugTypeBasic\0" // IR(50619, 15)
  "SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS\0" // IR(50634, 34)
  "DebugTypePointer\0" // IR(50668, 17)
  "SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER\0" // IR(50685, 38)
  "DebugTypeQualifier\0" // IR(50723, 19)
  "DebugTypeArray\0" // IR(50742, 15)
  "DebugTypeVector\0" // IR(50757, 16)
  "DebugTypedef\0" // IR(50773, 13)
  "DebugTypeFunction\0" // IR(50786, 18)
  "DebugTypeEnum\0" // IR(50804, 14)
  "SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE\0" // IR(50818, 38)
  "DebugTypeComposite\0" // IR(50856, 19)
  "DebugTypeMember\0" // IR(50875, 16)
  "DebugTypeInheritance\0" // IR(50891, 21)
  "DebugTypePtrToMember\0" // IR(50912, 21)
  "DebugTypeTemplate\0" // IR(50933, 18)
  "DebugTypeTemplateParameter\0" // IR(50951, 27)
  "DebugTypeTemplateTemplateParameter\0" // IR(50978, 35)
  "DebugTypeTemplateParameterPack\0" // IR(51013, 31)
  "DebugGlobalVariable\0" // IR(51044, 20)
  "DebugFunctionDeclaration\0" // IR(51064, 25)
  "DebugFunction\0" // IR(51089, 14)
  "DebugLexicalBlock\0" // IR(51103, 18)
  "DebugLexicalBlockDiscriminator\0" // IR(51121, 31)
  "DebugScope\0" // IR(51152, 11)
  "DebugNoScope\0" // IR(51163, 13)
  "DebugInlinedAt\0" // IR(51176, 15)
  "SPV_OPERAND_TYPE_OPTIONAL_LITERAL_INTEGER\0" // IR(51191, 42)
  "DebugLocalVariable\0" // IR(51233, 19)
  "DebugInlinedVariable\0" // IR(51252, 21)
  "DebugDeclare\0" // IR(51273, 13)
  "DebugValue\0" // IR(51286, 11)
  "SPV_OPERAND_TYPE_DEBUG_OPERATION\0" // IR(51297, 33)
  "DebugOperation\0" // IR(51330, 15)
  "DebugExpression\0" // IR(51345, 16)
  "DebugMacroDef\0" // IR(51361, 14)
  "DebugMacroUndef\0" // IR(51375, 16)
  "Round\0" // IR(51391, 6)
  "RoundEven\0" // IR(51397, 10)
  "Trunc\0" // IR(51407, 6)
  "FAbs\0" // IR(51413, 5)
  "SAbs\0" // IR(51418, 5)
  "FSign\0" // IR(51423, 6)
  "SSign\0" // IR(51429, 6)
  "Floor\0" // IR(51435, 6)
  "Ceil\0" // IR(51441, 5)
  "Fract\0" // IR(51446, 6)
  "Radians\0" // IR(51452, 8)
  "Degrees\0" // IR(51460, 8)
  "Sin\0" // IR(51468, 4)
  "Cos\0" // IR(51472, 4)
  "Tan\0" // IR(51476, 4)
  "Asin\0" // IR(51480, 5)
  "Acos\0" // IR(51485, 5)
  "Atan\0" // IR(51490, 5)
  "Sinh\0" // IR(51495, 5)
  "Cosh\0" // IR(51500, 5)
  "Tanh\0" // IR(51505, 5)
  "Asinh\0" // IR(51510, 6)
  "Acosh\0" // IR(51516, 6)
  "Atanh\0" // IR(51522, 6)
  "Atan2\0" // IR(51528, 6)
  "Pow\0" // IR(51534, 4)
  "Exp\0" // IR(51538, 4)
  "Log\0" // IR(51542, 4)
  "Exp2\0" // IR(51546, 5)
  "Log2\0" // IR(51551, 5)
  "Sqrt\0" // IR(51556, 5)
  "InverseSqrt\0" // IR(51561, 12)
  "Determinant\0" // IR(51573, 12)
  "MatrixInverse\0" // IR(51585, 14)
  "Modf\0" // IR(51599, 5)
  "ModfStruct\0" // IR(51604, 11)
  "FMin\0" // IR(51615, 5)
  "UMin\0" // IR(51620, 5)
  "SMin\0" // IR(51625, 5)
  "FMax\0" // IR(51630, 5)
  "UMax\0" // IR(51635, 5)
  "SMax\0" // IR(51640, 5)
  "FClamp\0" // IR(51645, 7)
  "UClamp\0" // IR(51652, 7)
  "SClamp\0" // IR(51659, 7)
  "FMix\0" // IR(51666, 5)
  "IMix\0" // IR(51671, 5)
  "Step\0" // IR(51676, 5)
  "SmoothStep\0" // IR(51681, 11)
  "Fma\0" // IR(51692, 4)
  "Frexp\0" // IR(51696, 6)
  "FrexpStruct\0" // IR(51702, 12)
  "Ldexp\0" // IR(51714, 6)
  "PackSnorm4x8\0" // IR(51720, 13)
  "PackUnorm4x8\0" // IR(51733, 13)
  "PackSnorm2x16\0" // IR(51746, 14)
  "PackUnorm2x16\0" // IR(51760, 14)
  "PackHalf2x16\0" // IR(51774, 13)
  "PackDouble2x32\0" // IR(51787, 15)
  "UnpackSnorm2x16\0" // IR(51802, 16)
  "UnpackUnorm2x16\0" // IR(51818, 16)
  "UnpackHalf2x16\0" // IR(51834, 15)
  "UnpackSnorm4x8\0" // IR(51849, 15)
  "UnpackUnorm4x8\0" // IR(51864, 15)
  "UnpackDouble2x32\0" // IR(51879, 17)
  "Length\0" // IR(51896, 7)
  "Distance\0" // IR(51903, 9)
  "Cross\0" // IR(51912, 6)
  "Normalize\0" // IR(51918, 10)
  "FaceForward\0" // IR(51928, 12)
  "Reflect\0" // IR(51940, 8)
  "Refract\0" // IR(51948, 8)
  "FindILsb\0" // IR(51956, 9)
  "FindSMsb\0" // IR(51965, 9)
  "FindUMsb\0" // IR(51974, 9)
  "InterpolateAtCentroid\0" // IR(51983, 22)
  "InterpolateAtSample\0" // IR(52005, 20)
  "InterpolateAtOffset\0" // IR(52025, 20)
  "NMin\0" // IR(52045, 5)
  "NMax\0" // IR(52050, 5)
  "NClamp\0" // IR(52055, 7)
  "ArgumentInfo\0" // IR(52062, 13)
  "ArgumentStorageBuffer\0" // IR(52075, 22)
  "ArgumentUniform\0" // IR(52097, 16)
  "ArgumentPodStorageBuffer\0" // IR(52113, 25)
  "ArgumentPodUniform\0" // IR(52138, 19)
  "ArgumentPodPushConstant\0" // IR(52157, 24)
  "ArgumentSampledImage\0" // IR(52181, 21)
  "ArgumentStorageImage\0" // IR(52202, 21)
  "ArgumentSampler\0" // IR(52223, 16)
  "ArgumentWorkgroup\0" // IR(52239, 18)
  "SpecConstantWorkgroupSize\0" // IR(52257, 26)
  "SpecConstantGlobalOffset\0" // IR(52283, 25)
  "SpecConstantWorkDim\0" // IR(52308, 20)
  "PushConstantGlobalOffset\0" // IR(52328, 25)
  "PushConstantEnqueuedLocalSize\0" // IR(52353, 30)
  "PushConstantGlobalSize\0" // IR(52383, 23)
  "PushConstantRegionOffset\0" // IR(52406, 25)
  "PushConstantNumWorkgroups\0" // IR(52431, 26)
  "PushConstantRegionGroupOffset\0" // IR(52457, 30)
  "ConstantDataStorageBuffer\0" // IR(52487, 26)
  "ConstantDataUniform\0" // IR(52513, 20)
  "PropertyRequiredWorkgroupSize\0" // IR(52533, 30)
  "SpecConstantSubgroupMaxSize\0" // IR(52563, 28)
  "ArgumentPointerPushConstant\0" // IR(52591, 28)
  "ArgumentPointerUniform\0" // IR(52619, 23)
  "ProgramScopeVariablesStorageBuffer\0" // IR(52642, 35)
  "ProgramScopeVariablePointerRelocation\0" // IR(52677, 38)
  "ImageArgumentInfoChannelOrderPushConstant\0" // IR(52715, 42)
  "ImageArgumentInfoChannelDataTypePushConstant\0" // IR(52757, 45)
  "ImageArgumentInfoChannelOrderUniform\0" // IR(52802, 37)
  "ImageArgumentInfoChannelDataTypeUniform\0" // IR(52839, 40)
  "ArgumentStorageTexelBuffer\0" // IR(52879, 27)
  "ArgumentUniformTexelBuffer\0" // IR(52906, 27)
  "ConstantDataPointerPushConstant\0" // IR(52933, 32)
  "ProgramScopeVariablePointerPushConstant\0" // IR(52965, 40)
  "PrintfInfo\0" // IR(53005, 11)
  "PrintfBufferStorageBuffer\0" // IR(53016, 26)
  "PrintfBufferPointerPushConstant\0" // IR(53042, 32)
  "NormalizedSamplerMaskPushConstant\0" // IR(53074, 34)
  "WorkgroupVariableSize\0" // IR(53108, 22)
  "DebugImportedEntity\0" // IR(53130, 20)
  "DebugSource\0" // IR(53150, 12)
  "DebugFunctionDefinition\0" // IR(53162, 24)
  "DebugSourceContinued\0" // IR(53186, 21)
  "DebugLine\0" // IR(53207, 10)
  "DebugNoLine\0" // IR(53217, 12)
  "DebugBuildIdentifier\0" // IR(53229, 21)
  "DebugStoragePath\0" // IR(53250, 17)
  "DebugEntryPoint\0" // IR(53267, 16)
  "DebugTypeMatrix\0" // IR(53283, 16)
  "Configuration\0" // IR(53299, 14)
  "StartCounter\0" // IR(53313, 13)
  "StopCounter\0" // IR(53326, 12)
  "PushConstants\0" // IR(53338, 14)
  "SpecializationMapEntry\0" // IR(53352, 23)
  "DescriptorSetBuffer\0" // IR(53375, 20)
  "DescriptorSetImage\0" // IR(53395, 19)
  "DescriptorSetSampler\0" // IR(53414, 21)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING\0" // IR(53435, 63)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS\0" // IR(53498, 45)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER\0" // IR(53543, 49)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE\0" // IR(53592, 49)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION\0" // IR(53641, 44)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY\0" // IR(53685, 50)
  "DebugModuleINTEL\0" // IR(53735, 17)
  "acos\0" // IR(53752, 5)
  "acosh\0" // IR(53757, 6)
  "acospi\0" // IR(53763, 7)
  "asin\0" // IR(53770, 5)
  "asinh\0" // IR(53775, 6)
  "asinpi\0" // IR(53781, 7)
  "atan\0" // IR(53788, 5)
  "atan2\0" // IR(53793, 6)
  "atanh\0" // IR(53799, 6)
  "atanpi\0" // IR(53805, 7)
  "atan2pi\0" // IR(53812, 8)
  "cbrt\0" // IR(53820, 5)
  "ceil\0" // IR(53825, 5)
  "copysign\0" // IR(53830, 9)
  "cos\0" // IR(53839, 4)
  "cosh\0" // IR(53843, 5)
  "cospi\0" // IR(53848, 6)
  "erfc\0" // IR(53854, 5)
  "erf\0" // IR(53859, 4)
  "exp\0" // IR(53863, 4)
  "exp2\0" // IR(53867, 5)
  "exp10\0" // IR(53872, 6)
  "expm1\0" // IR(53878, 6)
  "fabs\0" // IR(53884, 5)
  "fdim\0" // IR(53889, 5)
  "floor\0" // IR(53894, 6)
  "fma\0" // IR(53900, 4)
  "fmax\0" // IR(53904, 5)
  "fmin\0" // IR(53909, 5)
  "fmod\0" // IR(53914, 5)
  "fract\0" // IR(53919, 6)
  "frexp\0" // IR(53925, 6)
  "hypot\0" // IR(53931, 6)
  "ilogb\0" // IR(53937, 6)
  "ldexp\0" // IR(53943, 6)
  "lgamma\0" // IR(53949, 7)
  "lgamma_r\0" // IR(53956, 9)
  "log\0" // IR(53965, 4)
  "log2\0" // IR(53969, 5)
  "log10\0" // IR(53974, 6)
  "log1p\0" // IR(53980, 6)
  "logb\0" // IR(53986, 5)
  "mad\0" // IR(53991, 4)
  "maxmag\0" // IR(53995, 7)
  "minmag\0" // IR(54002, 7)
  "modf\0" // IR(54009, 5)
  "nan\0" // IR(54014, 4)
  "nextafter\0" // IR(54018, 10)
  "pow\0" // IR(54028, 4)
  "pown\0" // IR(54032, 5)
  "powr\0" // IR(54037, 5)
  "remainder\0" // IR(54042, 10)
  "remquo\0" // IR(54052, 7)
  "rint\0" // IR(54059, 5)
  "rootn\0" // IR(54064, 6)
  "round\0" // IR(54070, 6)
  "rsqrt\0" // IR(54076, 6)
  "sin\0" // IR(54082, 4)
  "sincos\0" // IR(54086, 7)
  "sinh\0" // IR(54093, 5)
  "sinpi\0" // IR(54098, 6)
  "sqrt\0" // IR(54104, 5)
  "tan\0" // IR(54109, 4)
  "tanh\0" // IR(54113, 5)
  "tanpi\0" // IR(54118, 6)
  "tgamma\0" // IR(54124, 7)
  "trunc\0" // IR(54131, 6)
  "half_cos\0" // IR(54137, 9)
  "half_divide\0" // IR(54146, 12)
  "half_exp\0" // IR(54158, 9)
  "half_exp2\0" // IR(54167, 10)
  "half_exp10\0" // IR(54177, 11)
  "half_log\0" // IR(54188, 9)
  "half_log2\0" // IR(54197, 10)
  "half_log10\0" // IR(54207, 11)
  "half_powr\0" // IR(54218, 10)
  "half_recip\0" // IR(54228, 11)
  "half_rsqrt\0" // IR(54239, 11)
  "half_sin\0" // IR(54250, 9)
  "half_sqrt\0" // IR(54259, 10)
  "half_tan\0" // IR(54269, 9)
  "native_cos\0" // IR(54278, 11)
  "native_divide\0" // IR(54289, 14)
  "native_exp\0" // IR(54303, 11)
  "native_exp2\0" // IR(54314, 12)
  "native_exp10\0" // IR(54326, 13)
  "native_log\0" // IR(54339, 11)
  "native_log2\0" // IR(54350, 12)
  "native_log10\0" // IR(54362, 13)
  "native_powr\0" // IR(54375, 12)
  "native_recip\0" // IR(54387, 13)
  "native_rsqrt\0" // IR(54400, 13)
  "native_sin\0" // IR(54413, 11)
  "native_sqrt\0" // IR(54424, 12)
  "native_tan\0" // IR(54436, 11)
  "fclamp\0" // IR(54447, 7)
  "degrees\0" // IR(54454, 8)
  "fmax_common\0" // IR(54462, 12)
  "fmin_common\0" // IR(54474, 12)
  "mix\0" // IR(54486, 4)
  "radians\0" // IR(54490, 8)
  "step\0" // IR(54498, 5)
  "smoothstep\0" // IR(54503, 11)
  "sign\0" // IR(54514, 5)
  "cross\0" // IR(54519, 6)
  "distance\0" // IR(54525, 9)
  "length\0" // IR(54534, 7)
  "normalize\0" // IR(54541, 10)
  "fast_distance\0" // IR(54551, 14)
  "fast_length\0" // IR(54565, 12)
  "fast_normalize\0" // IR(54577, 15)
  "s_abs\0" // IR(54592, 6)
  "s_abs_diff\0" // IR(54598, 11)
  "s_add_sat\0" // IR(54609, 10)
  "u_add_sat\0" // IR(54619, 10)
  "s_hadd\0" // IR(54629, 7)
  "u_hadd\0" // IR(54636, 7)
  "s_rhadd\0" // IR(54643, 8)
  "u_rhadd\0" // IR(54651, 8)
  "s_clamp\0" // IR(54659, 8)
  "u_clamp\0" // IR(54667, 8)
  "clz\0" // IR(54675, 4)
  "ctz\0" // IR(54679, 4)
  "s_mad_hi\0" // IR(54683, 9)
  "u_mad_sat\0" // IR(54692, 10)
  "s_mad_sat\0" // IR(54702, 10)
  "s_max\0" // IR(54712, 6)
  "u_max\0" // IR(54718, 6)
  "s_min\0" // IR(54724, 6)
  "u_min\0" // IR(54730, 6)
  "s_mul_hi\0" // IR(54736, 9)
  "rotate\0" // IR(54745, 7)
  "s_sub_sat\0" // IR(54752, 10)
  "u_sub_sat\0" // IR(54762, 10)
  "u_upsample\0" // IR(54772, 11)
  "s_upsample\0" // IR(54783, 11)
  "popcount\0" // IR(54794, 9)
  "s_mad24\0" // IR(54803, 8)
  "u_mad24\0" // IR(54811, 8)
  "s_mul24\0" // IR(54819, 8)
  "u_mul24\0" // IR(54827, 8)
  "vloadn\0" // IR(54835, 7)
  "vstoren\0" // IR(54842, 8)
  "vload_half\0" // IR(54850, 11)
  "vload_halfn\0" // IR(54861, 12)
  "vstore_half\0" // IR(54873, 12)
  "vstore_half_r\0" // IR(54885, 14)
  "vstore_halfn\0" // IR(54899, 13)
  "vstore_halfn_r\0" // IR(54912, 15)
  "vloada_halfn\0" // IR(54927, 13)
  "vstorea_halfn\0" // IR(54940, 14)
  "vstorea_halfn_r\0" // IR(54954, 16)
  "shuffle\0" // IR(54970, 8)
  "shuffle2\0" // IR(54978, 9)
  "printf\0" // IR(54987, 7)
  "prefetch\0" // IR(54994, 9)
  "bitselect\0" // IR(55003, 10)
  "select\0" // IR(55013, 7)
  "u_abs\0" // IR(55020, 6)
  "u_abs_diff\0" // IR(55026, 11)
  "u_mul_hi\0" // IR(55037, 9)
  "u_mad_hi\0" // IR(55046, 9)
  "CubeFaceIndexAMD\0" // IR(55055, 17)
  "CubeFaceCoordAMD\0" // IR(55072, 17)
  "TimeAMD\0" // IR(55089, 8)
  "SwizzleInvocationsAMD\0" // IR(55097, 22)
  "SwizzleInvocationsMaskedAMD\0" // IR(55119, 28)
  "WriteInvocationAMD\0" // IR(55147, 19)
  "MbcntAMD\0" // IR(55166, 9)
  "InterpolateAtVertexAMD\0" // IR(55175, 23)
  "FMin3AMD\0" // IR(55198, 9)
  "UMin3AMD\0" // IR(55207, 9)
  "SMin3AMD\0" // IR(55216, 9)
  "FMax3AMD\0" // IR(55225, 9)
  "UMax3AMD\0" // IR(55234, 9)
  "SMax3AMD\0" // IR(55243, 9)
  "FMid3AMD\0" // IR(55252, 9)
  "UMid3AMD\0" // IR(55261, 9)
  "SMid3AMD\0" // IR(55270, 9)
;

// Array of IndexRanges, where each represents a string by referencing
// the kStrings table.
// This array contains all sequences of alias strings used in the grammar.
// This table is referenced by an IndexRange elsewhere, i.e. by the 'aliases'
// field of an instruction or operand description.
static const IndexRange kAliasSpans[] = {
  IR(5554, 27), // 0 PhysicalStorageBuffer64EXT
  IR(6465, 18), // 1 SubgroupEqMaskKHR
  IR(6520, 18), // 2 SubgroupGeMaskKHR
  IR(6553, 18), // 3 SubgroupGtMaskKHR
  IR(6586, 18), // 4 SubgroupLeMaskKHR
  IR(6619, 18), // 5 SubgroupLtMaskKHR
  IR(7526, 12), // 6 BaryCoordNV
  IR(7581, 19), // 7 BaryCoordNoPerspNV
  IR(7612, 15), // 8 FragmentSizeNV
  IR(7669, 22), // 9 InvocationsPerPixelNV
  IR(7797, 11), // 10 LaunchIdNV
  IR(7822, 13), // 11 LaunchSizeNV
  IR(7853, 17), // 12 WorldRayOriginNV
  IR(7891, 20), // 13 WorldRayDirectionNV
  IR(7930, 18), // 14 ObjectRayOriginNV
  IR(7970, 21), // 15 ObjectRayDirectionNV
  IR(8002, 10), // 16 RayTminNV
  IR(8023, 10), // 17 RayTmaxNV
  IR(8056, 22), // 18 InstanceCustomIndexNV
  IR(8095, 16), // 19 ObjectToWorldNV
  IR(8128, 16), // 20 WorldToObjectNV
  IR(8162, 10), // 21 HitKindNV
  IR(8393, 19), // 22 IncomingRayFlagsNV
  IR(10169, 28), // 23 StorageUniformBufferBlock16
  IR(10232, 17), // 24 StorageUniform16
  IR(11047, 27), // 25 ShaderViewportIndexLayerNV
  IR(11091, 22), // 26 FragmentBarycentricNV
  IR(11144, 30), // 27 ComputeDerivativeGroupQuadsNV
  IR(11174, 14), // 28 ShadingRateNV
  IR(11218, 29), // 29 GroupNonUniformPartitionedNV
  IR(11264, 20), // 30 ShaderNonUniformEXT
  IR(11307, 26), // 31 RuntimeDescriptorArrayEXT
  IR(11369, 39), // 32 InputAttachmentArrayDynamicIndexingEXT
  IR(11447, 42), // 33 UniformTexelBufferArrayDynamicIndexingEXT
  IR(11528, 42), // 34 StorageTexelBufferArrayDynamicIndexingEXT
  IR(11607, 40), // 35 UniformBufferArrayNonUniformIndexingEXT
  IR(11683, 39), // 36 SampledImageArrayNonUniformIndexingEXT
  IR(11759, 40), // 37 StorageBufferArrayNonUniformIndexingEXT
  IR(11835, 39), // 38 StorageImageArrayNonUniformIndexingEXT
  IR(11913, 42), // 39 InputAttachmentArrayNonUniformIndexingEXT
  IR(11997, 45), // 40 UniformTexelBufferArrayNonUniformIndexingEXT
  IR(12084, 45), // 41 StorageTexelBufferArrayNonUniformIndexingEXT
  IR(12147, 21), // 42 VulkanMemoryModelKHR
  IR(12197, 32), // 43 VulkanMemoryModelDeviceScopeKHR
  IR(12229, 34), // 44 PhysicalStorageBufferAddressesEXT
  IR(12295, 31), // 45 ComputeDerivativeGroupLinearNV
  IR(12499, 28), // 46 DemoteToHelperInvocationEXT
  IR(13540, 26), // 47 FPGAMemoryAttributesINTEL
  IR(13619, 32), // 48 ArbitraryPrecisionIntegersINTEL
  IR(13689, 37), // 49 ArbitraryPrecisionFloatingPointINTEL
  IR(13779, 22), // 50 FPGALoopControlsINTEL
  IR(13874, 24), // 51 FPGAMemoryAccessesINTEL
  IR(13926, 27), // 52 FPGAClusterAttributesINTEL
  IR(13968, 14), // 53 LoopFuseINTEL
  IR(14003, 20), // 54 FPGADSPControlINTEL
  IR(14090, 40), // 55 FPGAInvocationPipeliningAttributesINTEL
  IR(14155, 24), // 56 FPGABufferLocationINTEL
  IR(14214, 34), // 57 ArbitraryPrecisionFixedPointINTEL
  IR(14272, 23), // 58 USMStorageClassesINTEL
  IR(14325, 29), // 59 RuntimeAlignedAttributeINTEL
  IR(14368, 13), // 60 IOPipesINTEL
  IR(14401, 19), // 61 BlockingPipesINTEL
  IR(14434, 13), // 62 FPGARegINTEL
  IR(14466, 22), // 63 DotProductInputAllKHR
  IR(14510, 25), // 64 DotProductInput4x8BitKHR
  IR(14563, 31), // 65 DotProductInput4x8BitPackedKHR
  IR(14605, 14), // 66 DotProductKHR
  IR(14777, 13), // 67 OptNoneINTEL
  IR(14922, 29), // 68 FPGAClusterAttributesV2INTEL
  IR(14998, 18), // 69 TaskSequenceINTEL
  IR(15057, 24), // 70 FPGALatencyControlINTEL
  IR(15110, 28), // 71 FPGAArgumentInterfacesINTEL
  IR(15204, 35), // 72 GlobalVariableFPGADecorationsINTEL
  IR(18016, 15), // 73 PerPrimitiveNV
  IR(18064, 12), // 74 PerVertexNV
  IR(18087, 14), // 75 NonUniformEXT
  IR(18117, 19), // 76 RestrictPointerEXT
  IR(18151, 18), // 77 AliasedPointerEXT
  IR(18514, 24), // 78 HlslCounterBufferGOOGLE
  IR(18551, 19), // 79 HlslSemanticGOOGLE
  IR(18681, 14), // 80 RegisterINTEL
  IR(18708, 12), // 81 MemoryINTEL
  IR(18735, 14), // 82 NumbanksINTEL
  IR(18765, 15), // 83 BankwidthINTEL
  IR(18803, 22), // 84 MaxPrivateCopiesINTEL
  IR(18842, 16), // 85 SinglepumpINTEL
  IR(18875, 16), // 86 DoublepumpINTEL
  IR(18911, 19), // 87 MaxReplicatesINTEL
  IR(18951, 20), // 88 SimpleDualPortINTEL
  IR(18983, 11), // 89 MergeINTEL
  IR(19051, 14), // 90 BankBitsINTEL
  IR(19086, 20), // 91 ForcePow2DepthINTEL
  IR(19123, 16), // 92 StridesizeINTEL
  IR(19154, 14), // 93 WordsizeINTEL
  IR(19187, 18), // 94 TrueDualPortINTEL
  IR(19225, 19), // 95 BurstCoalesceINTEL
  IR(19260, 15), // 96 CacheSizeINTEL
  IR(19304, 28), // 97 DontStaticallyCoalesceINTEL
  IR(19347, 14), // 98 PrefetchINTEL
  IR(19379, 17), // 99 StallEnableINTEL
  IR(19422, 25), // 100 FuseLoopsInFunctionINTEL
  IR(19467, 19), // 101 MathOpDSPModeINTEL
  IR(19540, 24), // 102 InitiationIntervalINTEL
  IR(19585, 20), // 103 MaxConcurrencyINTEL
  IR(19626, 20), // 104 PipelineEnableINTEL
  IR(19667, 20), // 105 BufferLocationINTEL
  IR(19707, 19), // 106 IOPipeStorageINTEL
  IR(19885, 15), // 107 StallFreeINTEL
  IR(19983, 25), // 108 LatencyControlLabelINTEL
  IR(20039, 30), // 109 LatencyControlConstraintINTEL
  IR(20097, 27), // 110 ConduitKernelArgumentINTEL
  IR(20156, 31), // 111 RegisterMapKernelArgumentINTEL
  IR(20221, 33), // 112 MMHostInterfaceAddressWidthINTEL
  IR(20285, 30), // 113 MMHostInterfaceDataWidthINTEL
  IR(20344, 28), // 114 MMHostInterfaceLatencyINTEL
  IR(20441, 34), // 115 MMHostInterfaceReadWriteModeINTEL
  IR(20505, 29), // 116 MMHostInterfaceMaxBurstINTEL
  IR(20567, 32), // 117 MMHostInterfaceWaitRequestINTEL
  IR(20626, 26), // 118 StableKernelArgumentINTEL
  IR(20769, 14), // 119 InitModeINTEL
  IR(20812, 28), // 120 ImplementInRegisterMapINTEL
  IR(22146, 14), // 121 OutputLinesNV
  IR(22180, 19), // 122 OutputPrimitivesNV
  IR(22223, 23), // 123 DerivativeGroupQuadsNV
  IR(22271, 24), // 124 DerivativeGroupLinearNV
  IR(22314, 18), // 125 OutputTrianglesNV
  IR(23062, 16), // 126 RayGenerationNV
  IR(23094, 15), // 127 IntersectionNV
  IR(23119, 9), // 128 AnyHitNV
  IR(23142, 13), // 129 ClosestHitNV
  IR(23163, 7), // 130 MissNV
  IR(23182, 11), // 131 CallableNV
  IR(23327, 23), // 132 AllowContractFastINTEL
  IR(23363, 18), // 133 AllowReassocINTEL
  IR(23589, 20), // 134 RuntimeAlignedINTEL
  IR(23681, 20), // 135 PartitionedReduceNV
  IR(23729, 27), // 136 PartitionedInclusiveScanNV
  IR(23784, 27), // 137 PartitionedExclusiveScanNV
  IR(23915, 22), // 138 MakeTexelAvailableKHR
  IR(23954, 20), // 139 MakeTexelVisibleKHR
  IR(23990, 19), // 140 NonPrivateTexelKHR
  IR(24023, 17), // 141 VolatileTexelKHR
  IR(24582, 27), // 142 InitOnDeviceReprogramINTEL
  IR(24633, 23), // 143 InitOnDeviceResetINTEL
  IR(24967, 21), // 144 DependencyArrayINTEL
  IR(25007, 18), // 145 LoopCoalesceINTEL
  IR(25047, 21), // 146 MaxInterleavingINTEL
  IR(25095, 26), // 147 SpeculatedIterationsINTEL
  IR(25136, 14), // 148 NoFusionINTEL
  IR(25166, 15), // 149 LoopCountINTEL
  IR(25208, 26), // 150 MaxReinvocationDelayINTEL
  IR(25600, 24), // 151 MakePointerAvailableKHR
  IR(25643, 22), // 152 MakePointerVisibleKHR
  IR(25683, 21), // 153 NonPrivatePointerKHR
  IR(25770, 10), // 154 VulkanKHR
  IR(15759, 5), // 155 None
  IR(25953, 16), // 156 OutputMemoryKHR
  IR(25983, 17), // 157 MakeAvailableKHR
  IR(26012, 15), // 158 MakeVisibleKHR
  IR(26088, 28), // 159 PackedVectorFormat4x8BitKHR
  IR(26403, 24), // 160 SkipBuiltinPrimitivesNV
  IR(27143, 15), // 161 QueueFamilyKHR
  IR(27514, 15), // 162 CallableDataNV
  IR(27553, 23), // 163 IncomingCallableDataNV
  IR(27590, 13), // 164 RayPayloadNV
  IR(27619, 15), // 165 HitAttributeNV
  IR(27656, 21), // 166 IncomingRayPayloadNV
  IR(27699, 21), // 167 ShaderRecordBufferNV
  IR(27742, 25), // 168 PhysicalStorageBufferEXT
  IR(27868, 16), // 169 DeviceOnlyINTEL
  IR(27899, 14), // 170 HostOnlyINTEL
  IR(35137, 8), // 171 SDotKHR
  IR(35150, 8), // 172 UDotKHR
  IR(35164, 9), // 173 SUDotKHR
  IR(35184, 14), // 174 SDotAccSatKHR
  IR(35209, 14), // 175 UDotAccSatKHR
  IR(35235, 15), // 176 SUDotAccSatKHR
  IR(37496, 24), // 177 TypeCooperativeVectorNV
  IR(37752, 27), // 178 GroupNonUniformPartitionNV
  IR(38834, 21), // 179 ReportIntersectionNV
  IR(39009, 28), // 180 TypeAccelerationStructureNV
  IR(39090, 23), // 181 RayQueryGetClusterIdNV
  IR(41258, 21), // 182 DecorateStringGOOGLE
  IR(41300, 27), // 183 MemberDecorateStringGOOGLE
  IR(46557, 28), // 184 ArbitraryFloatSinCosPiINTEL
  IR(46610, 24), // 185 ArbitraryFloatCastINTEL
  IR(46666, 31), // 186 ArbitraryFloatCastFromIntINTEL
  IR(46727, 29), // 187 ArbitraryFloatCastToIntINTEL
  IR(46780, 23), // 188 ArbitraryFloatAddINTEL
  IR(46827, 23), // 189 ArbitraryFloatSubINTEL
  IR(46874, 23), // 190 ArbitraryFloatMulINTEL
  IR(46921, 23), // 191 ArbitraryFloatDivINTEL
  IR(46967, 22), // 192 ArbitraryFloatGTINTEL
  IR(47012, 22), // 193 ArbitraryFloatGEINTEL
  IR(47057, 22), // 194 ArbitraryFloatLTINTEL
  IR(47102, 22), // 195 ArbitraryFloatLEINTEL
  IR(47147, 22), // 196 ArbitraryFloatEQINTEL
  IR(47195, 25), // 197 ArbitraryFloatRecipINTEL
  IR(47246, 25), // 198 ArbitraryFloatRSqrtINTEL
  IR(47296, 24), // 199 ArbitraryFloatCbrtINTEL
  IR(47346, 25), // 200 ArbitraryFloatHypotINTEL
  IR(47396, 24), // 201 ArbitraryFloatSqrtINTEL
  IR(48080, 15), // 202 FixedSqrtINTEL
  IR(48112, 16), // 203 FixedRecipINTEL
  IR(48145, 16), // 204 FixedRsqrtINTEL
  IR(48176, 14), // 205 FixedSinINTEL
  IR(48205, 14), // 206 FixedCosINTEL
  IR(48237, 17), // 207 FixedSinCosINTEL
  IR(48271, 16), // 208 FixedSinPiINTEL
  IR(48304, 16), // 209 FixedCosPiINTEL
  IR(48340, 19), // 210 FixedSinCosPiINTEL
  IR(48374, 14), // 211 FixedLogINTEL
  IR(48403, 14), // 212 FixedExpINTEL
  IR(48447, 29), // 213 PtrCastToCrossWorkgroupINTEL
  IR(48506, 29), // 214 CrossWorkgroupCastToPtrINTEL
  IR(48558, 22), // 215 ReadPipeBlockingINTEL
  IR(48604, 23), // 216 WritePipeBlockingINTEL
  IR(49556, 24), // 217 TaskSequenceCreateINTEL
  IR(49604, 23), // 218 TaskSequenceAsyncINTEL
  IR(49649, 21), // 219 TaskSequenceGetINTEL
  IR(49696, 25), // 220 TaskSequenceReleaseINTEL
  IR(49744, 22), // 221 TypeTaskSequenceINTEL
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
  spv::Capability::CooperativeMatrixLayoutsARM, // 114
  spv::Capability::Shader, // 115
  spv::Capability::Kernel, // 116
  spv::Capability::Shader, // 117
  spv::Capability::UniformDecoration, // 118
  spv::Capability::GeometryStreams, // 119
  spv::Capability::TransformFeedback, // 120
  spv::Capability::Kernel, // 121
  spv::Capability::FloatControls2, // 122
  spv::Capability::Linkage, // 123
  spv::Capability::Float8EXT, // 124
  spv::Capability::SampleMaskOverrideCoverageNV, // 125
  spv::Capability::GeometryShaderPassthroughNV, // 126
  spv::Capability::MeshShadingNV, // 127
  spv::Capability::MeshShadingEXT, // 128
  spv::Capability::PushConstantBanksNV, // 129
  spv::Capability::ShaderInvocationReorderNV, // 130
  spv::Capability::ShaderInvocationReorderEXT, // 131
  spv::Capability::BindlessTextureNV, // 132
  spv::Capability::VectorComputeINTEL, // 133
  spv::Capability::IndirectReferencesINTEL, // 134
  spv::Capability::AsmINTEL, // 135
  spv::Capability::FunctionFloatControlINTEL, // 136
  spv::Capability::FPGAMemoryAttributesALTERA, // 137
  spv::Capability::FPGAMemoryAccessesALTERA, // 138
  spv::Capability::LoopFuseALTERA, // 139
  spv::Capability::FPGADSPControlALTERA, // 140
  spv::Capability::MemoryAccessAliasingINTEL, // 141
  spv::Capability::FPGAInvocationPipeliningAttributesALTERA, // 142
  spv::Capability::FPGABufferLocationALTERA, // 143
  spv::Capability::IOPipesALTERA, // 144
  spv::Capability::FPGAClusterAttributesV2ALTERA, // 145
  spv::Capability::FPMaxErrorINTEL, // 146
  spv::Capability::FPGALatencyControlALTERA, // 147
  spv::Capability::FPGAArgumentInterfacesALTERA, // 148
  spv::Capability::GlobalVariableHostAccessINTEL, // 149
  spv::Capability::GlobalVariableFPGADecorationsALTERA, // 150
  spv::Capability::CacheControlsINTEL, // 151
  spv::Capability::TileImageColorReadAccessEXT, // 152
  spv::Capability::Geometry, // 153
  spv::Capability::Tessellation, // 154
  spv::Capability::MeshShadingNV, // 155
  spv::Capability::MeshShadingEXT, // 156
  spv::Capability::Geometry, // 157
  spv::Capability::MeshShadingNV, // 158
  spv::Capability::MeshShadingEXT, // 159
  spv::Capability::SubgroupDispatch, // 160
  spv::Capability::TileImageDepthReadAccessEXT, // 161
  spv::Capability::TileImageStencilReadAccessEXT, // 162
  spv::Capability::SampleMaskPostDepthCoverage, // 163
  spv::Capability::DenormPreserve, // 164
  spv::Capability::DenormFlushToZero, // 165
  spv::Capability::SignedZeroInfNanPreserve, // 166
  spv::Capability::RoundingModeRTE, // 167
  spv::Capability::RoundingModeRTZ, // 168
  spv::Capability::QuadControlKHR, // 169
  spv::Capability::ComputeDerivativeGroupQuadsKHR, // 170
  spv::Capability::ComputeDerivativeGroupLinearKHR, // 171
  spv::Capability::FragmentShaderPixelInterlockEXT, // 172
  spv::Capability::FragmentShaderSampleInterlockEXT, // 173
  spv::Capability::FragmentShaderShadingRateInterlockEXT, // 174
  spv::Capability::Shader64BitIndexingEXT, // 175
  spv::Capability::RoundToInfinityINTEL, // 176
  spv::Capability::KernelAttributesINTEL, // 177
  spv::Capability::FloatControls2, // 178
  spv::Capability::FPGAKernelAttributesv2INTEL, // 179
  spv::Capability::RegisterLimitsINTEL, // 180
  spv::Capability::FloatControls2, // 181
  spv::Capability::FPFastMathModeINTEL, // 182
  spv::Capability::OptNoneEXT, // 183
  spv::Capability::RuntimeAlignedAttributeALTERA, // 184
  spv::Capability::Kernel, // 185
  spv::Capability::GroupNonUniformArithmetic, // 186
  spv::Capability::GroupNonUniformBallot, // 187
  spv::Capability::GroupNonUniformClustered, // 188
  spv::Capability::GroupNonUniformPartitionedEXT, // 189
  spv::Capability::ImageGatherExtended, // 190
  spv::Capability::MinLod, // 191
  spv::Capability::VulkanMemoryModel, // 192
  spv::Capability::FPGALoopControlsALTERA, // 193
  spv::Capability::ArbitraryPrecisionFixedPointALTERA, // 194
  spv::Capability::RawAccessChainsNV, // 195
  spv::Capability::RayTraversalPrimitiveCullingKHR, // 196
  spv::Capability::RayTracingOpacityMicromapEXT, // 197
  spv::Capability::RayQueryKHR, // 198
  spv::Capability::StorageImageExtendedFormats, // 199
  spv::Capability::Int64ImageEXT, // 200
  spv::Capability::Shader, // 201
  spv::Capability::VectorComputeINTEL, // 202
  spv::Capability::GenericPointer, // 203
  spv::Capability::FunctionPointersINTEL, // 204
  spv::Capability::USMStorageClassesALTERA, // 205
  spv::Capability::CooperativeMatrixTensorAddressingNV, // 206
  spv::Capability::CooperativeMatrixBlockLoadsNV, // 207
  spv::Capability::TensorsARM, // 208
  spv::Capability::Addresses, // 209
  spv::Capability::PhysicalStorageBufferAddresses, // 210
  spv::Capability::LiteralSampler, // 211
  spv::Capability::Addresses, // 212
  spv::Capability::UntypedPointersKHR, // 213
  spv::Capability::Addresses, // 214
  spv::Capability::VariablePointers, // 215
  spv::Capability::VariablePointersStorageBuffer, // 216
  spv::Capability::PhysicalStorageBufferAddresses, // 217
  spv::Capability::Kernel, // 218
  spv::Capability::ImageQuery, // 219
  spv::Capability::ImageQuery, // 220
  spv::Capability::Shader, // 221
  spv::Capability::BitInstructions, // 222
  spv::Capability::DerivativeControl, // 223
  spv::Capability::Groups, // 224
  spv::Capability::SparseResidency, // 225
  spv::Capability::PipeStorage, // 226
  spv::Capability::NamedBarrier, // 227
  spv::Capability::GroupNonUniformVote, // 228
  spv::Capability::GroupNonUniformBallot, // 229
  spv::Capability::GroupNonUniformShuffle, // 230
  spv::Capability::GroupNonUniformShuffleRelative, // 231
  spv::Capability::GroupNonUniformArithmetic, // 232
  spv::Capability::GroupNonUniformClustered, // 233
  spv::Capability::GroupNonUniformPartitionedEXT, // 234
  spv::Capability::GroupNonUniformQuad, // 235
  spv::Capability::Addresses, // 236
  spv::Capability::VariablePointers, // 237
  spv::Capability::VariablePointersStorageBuffer, // 238
  spv::Capability::GraphARM, // 239
  spv::Capability::SubgroupBallotKHR, // 240
  spv::Capability::FMAKHR, // 241
  spv::Capability::SubgroupVoteKHR, // 242
  spv::Capability::GroupNonUniformRotateKHR, // 243
  spv::Capability::RayTracingKHR, // 244
  spv::Capability::RayQueryKHR, // 245
  spv::Capability::DotProduct, // 246
  spv::Capability::ReplicatedCompositesEXT, // 247
  spv::Capability::TextureSampleWeightedQCOM, // 248
  spv::Capability::TextureBoxFilterQCOM, // 249
  spv::Capability::TextureBlockMatchQCOM, // 250
  spv::Capability::CooperativeMatrixConversionQCOM, // 251
  spv::Capability::TextureBlockMatch2QCOM, // 252
  spv::Capability::FragmentMaskAMD, // 253
  spv::Capability::ShaderClockKHR, // 254
  spv::Capability::ShaderInvocationReorderNV, // 255
  spv::Capability::RayTracingMotionBlurNV, // 256
  spv::Capability::ImageFootprintNV, // 257
  spv::Capability::CooperativeVectorNV, // 258
  spv::Capability::LongVectorEXT, // 259
  spv::Capability::CooperativeVectorNV, // 260
  spv::Capability::CooperativeVectorTrainingNV, // 261
  spv::Capability::CooperativeMatrixConversionsNV, // 262
  spv::Capability::DisplacementMicromapNV, // 263
  spv::Capability::ShaderInvocationReorderEXT, // 264
  spv::Capability::RayTracingMotionBlurNV, // 265
  spv::Capability::RayQueryPositionFetchKHR, // 266
  spv::Capability::RayTracingNV, // 267
  spv::Capability::RayTracingKHR, // 268
  spv::Capability::RayQueryKHR, // 269
  spv::Capability::DisplacementMicromapNV, // 270
  spv::Capability::CooperativeMatrixNV, // 271
  spv::Capability::FragmentShaderSampleInterlockEXT, // 272
  spv::Capability::FragmentShaderPixelInterlockEXT, // 273
  spv::Capability::FragmentShaderShadingRateInterlockEXT, // 274
  spv::Capability::CooperativeMatrixReductionsNV, // 275
  spv::Capability::CooperativeMatrixPerElementOperationsNV, // 276
  spv::Capability::TensorAddressingNV, // 277
  spv::Capability::DemoteToHelperInvocation, // 278
  spv::Capability::SubgroupShuffleINTEL, // 279
  spv::Capability::SubgroupBufferBlockIOINTEL, // 280
  spv::Capability::SubgroupImageBlockIOINTEL, // 281
  spv::Capability::SubgroupImageMediaBlockIOINTEL, // 282
  spv::Capability::IntegerFunctions2INTEL, // 283
  spv::Capability::AtomicFloat16MinMaxEXT, // 284
  spv::Capability::AtomicFloat32MinMaxEXT, // 285
  spv::Capability::AtomicFloat64MinMaxEXT, // 286
  spv::Capability::AtomicFloat16VectorNV, // 287
  spv::Capability::ExpectAssumeKHR, // 288
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 289
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 290
  spv::Capability::SubgroupAvcMotionEstimationIntraINTEL, // 291
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 292
  spv::Capability::SubgroupAvcMotionEstimationChromaINTEL, // 293
  spv::Capability::VariableLengthArrayINTEL, // 294
  spv::Capability::ArbitraryPrecisionFloatingPointALTERA, // 295
  spv::Capability::UnstructuredLoopControlsINTEL, // 296
  spv::Capability::BlockingPipesALTERA, // 297
  spv::Capability::FPGARegALTERA, // 298
  spv::Capability::AtomicFloat16AddEXT, // 299
  spv::Capability::AtomicFloat32AddEXT, // 300
  spv::Capability::AtomicFloat64AddEXT, // 301
  spv::Capability::AtomicFloat16VectorNV, // 302
  spv::Capability::LongCompositesINTEL, // 303
  spv::Capability::BFloat16ConversionINTEL, // 304
  spv::Capability::SplitBarrierINTEL, // 305
  spv::Capability::ArithmeticFenceEXT, // 306
  spv::Capability::TaskSequenceALTERA, // 307
  spv::Capability::SubgroupBufferPrefetchINTEL, // 308
  spv::Capability::Subgroup2DBlockTransformINTEL, // 309
  spv::Capability::Subgroup2DBlockTransposeINTEL, // 310
  spv::Capability::SubgroupMatrixMultiplyAccumulateINTEL, // 311
  spv::Capability::TernaryBitwiseFunctionINTEL, // 312
  spv::Capability::UntypedVariableLengthArrayINTEL, // 313
  spv::Capability::FunctionVariantsINTEL, // 314
  spv::Capability::GroupUniformArithmeticKHR, // 315
  spv::Capability::TensorFloat32RoundingINTEL, // 316
  spv::Capability::MaskedGatherScatterINTEL, // 317
  spv::Capability::BindlessImagesINTEL, // 318
  spv::Capability::Float64, // 319
  spv::Capability::InterpolationFunction, // 320
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
  spvtools::Extension::kSPV_KHR_no_integer_wrap_decoration, // 181
  spvtools::Extension::kSPV_NV_mesh_shader, // 182
  spvtools::Extension::kSPV_EXT_mesh_shader, // 183
  spvtools::Extension::kSPV_GOOGLE_hlsl_functionality1, // 184
  spvtools::Extension::kSPV_GOOGLE_user_type, // 185
  spvtools::Extension::kSPV_KHR_subgroup_uniform_control_flow, // 186
  spvtools::Extension::kSPV_AMD_shader_early_and_late_fragment_tests, // 187
  spvtools::Extension::kSPV_AMD_shader_early_and_late_fragment_tests, // 188
  spvtools::Extension::kSPV_EXT_shader_stencil_export, // 189
  spvtools::Extension::kSPV_KHR_maximal_reconvergence, // 190
  spvtools::Extension::kSPV_KHR_linkonce_odr, // 191
  spvtools::Extension::kSPV_KHR_storage_buffer_storage_class, // 192
  spvtools::Extension::kSPV_KHR_variable_pointers, // 193
  spvtools::Extension::kSPV_KHR_terminate_invocation, // 194
  spvtools::Extension::kSPV_KHR_relaxed_extended_instruction, // 195
  spvtools::Extension::kSPV_KHR_ray_tracing, // 196
  spvtools::Extension::kSPV_KHR_ray_query, // 197
  spvtools::Extension::kSPV_NV_ray_tracing, // 198
  spvtools::Extension::kSPV_KHR_ray_tracing, // 199
  spvtools::Extension::kSPV_KHR_ray_query, // 200
  spvtools::Extension::kSPV_NV_displacement_micromap, // 201
  spvtools::Extension::kSPV_GOOGLE_decorate_string, // 202
  spvtools::Extension::kSPV_GOOGLE_hlsl_functionality1, // 203
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
