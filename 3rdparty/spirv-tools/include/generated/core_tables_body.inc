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
    case Extension::kSPV_AMD_weak_linkage: return IR(1020, 21);
    case Extension::kSPV_ARM_cooperative_matrix_layouts: return IR(1041, 35);
    case Extension::kSPV_ARM_core_builtins: return IR(1076, 22);
    case Extension::kSPV_ARM_graph: return IR(1098, 14);
    case Extension::kSPV_ARM_tensors: return IR(1112, 16);
    case Extension::kSPV_EXT_arithmetic_fence: return IR(1128, 25);
    case Extension::kSPV_EXT_cooperative_matrix_maintenance1: return IR(1153, 40);
    case Extension::kSPV_EXT_demote_to_helper_invocation: return IR(1193, 36);
    case Extension::kSPV_EXT_descriptor_heap: return IR(1229, 24);
    case Extension::kSPV_EXT_descriptor_indexing: return IR(1253, 28);
    case Extension::kSPV_EXT_float8: return IR(1281, 15);
    case Extension::kSPV_EXT_fragment_fully_covered: return IR(1296, 31);
    case Extension::kSPV_EXT_fragment_invocation_density: return IR(1327, 36);
    case Extension::kSPV_EXT_fragment_shader_interlock: return IR(1363, 34);
    case Extension::kSPV_EXT_long_vector: return IR(1397, 20);
    case Extension::kSPV_EXT_mesh_shader: return IR(1417, 20);
    case Extension::kSPV_EXT_ocp_microscaling_types: return IR(1437, 31);
    case Extension::kSPV_EXT_opacity_micromap: return IR(1468, 25);
    case Extension::kSPV_EXT_optnone: return IR(1493, 16);
    case Extension::kSPV_EXT_physical_storage_buffer: return IR(1509, 32);
    case Extension::kSPV_EXT_relaxed_printf_string_address_space: return IR(1541, 44);
    case Extension::kSPV_EXT_replicated_composites: return IR(1585, 30);
    case Extension::kSPV_EXT_shader_64bit_indexing: return IR(1615, 30);
    case Extension::kSPV_EXT_shader_atomic_float16_add: return IR(1645, 34);
    case Extension::kSPV_EXT_shader_atomic_float_add: return IR(1679, 32);
    case Extension::kSPV_EXT_shader_atomic_float_min_max: return IR(1711, 36);
    case Extension::kSPV_EXT_shader_image_int64: return IR(1747, 27);
    case Extension::kSPV_EXT_shader_invocation_reorder: return IR(1774, 34);
    case Extension::kSPV_EXT_shader_stencil_export: return IR(1808, 30);
    case Extension::kSPV_EXT_shader_subgroup_partitioned: return IR(1838, 36);
    case Extension::kSPV_EXT_shader_tile_image: return IR(1874, 26);
    case Extension::kSPV_EXT_shader_viewport_index_layer: return IR(1900, 36);
    case Extension::kSPV_EXT_split_barrier: return IR(1936, 22);
    case Extension::kSPV_GOOGLE_decorate_string: return IR(1958, 27);
    case Extension::kSPV_GOOGLE_hlsl_functionality1: return IR(1985, 31);
    case Extension::kSPV_GOOGLE_user_type: return IR(2016, 21);
    case Extension::kSPV_INTEL_2d_block_io: return IR(2037, 22);
    case Extension::kSPV_INTEL_arbitrary_precision_fixed_point: return IR(2059, 42);
    case Extension::kSPV_INTEL_arbitrary_precision_floating_point: return IR(2101, 45);
    case Extension::kSPV_INTEL_arbitrary_precision_integers: return IR(2146, 39);
    case Extension::kSPV_INTEL_bfloat16_conversion: return IR(2185, 30);
    case Extension::kSPV_INTEL_bindless_images: return IR(2215, 26);
    case Extension::kSPV_INTEL_blocking_pipes: return IR(2241, 25);
    case Extension::kSPV_INTEL_cache_controls: return IR(2266, 25);
    case Extension::kSPV_INTEL_debug_module: return IR(2291, 23);
    case Extension::kSPV_INTEL_device_side_avc_motion_estimation: return IR(2314, 44);
    case Extension::kSPV_INTEL_float_controls2: return IR(2358, 26);
    case Extension::kSPV_INTEL_fp_fast_math_mode: return IR(2384, 28);
    case Extension::kSPV_INTEL_fp_max_error: return IR(2412, 23);
    case Extension::kSPV_INTEL_fpga_argument_interfaces: return IR(2435, 35);
    case Extension::kSPV_INTEL_fpga_buffer_location: return IR(2470, 31);
    case Extension::kSPV_INTEL_fpga_cluster_attributes: return IR(2501, 34);
    case Extension::kSPV_INTEL_fpga_dsp_control: return IR(2535, 27);
    case Extension::kSPV_INTEL_fpga_invocation_pipelining_attributes: return IR(2562, 48);
    case Extension::kSPV_INTEL_fpga_latency_control: return IR(2610, 31);
    case Extension::kSPV_INTEL_fpga_loop_controls: return IR(2641, 29);
    case Extension::kSPV_INTEL_fpga_memory_accesses: return IR(2670, 31);
    case Extension::kSPV_INTEL_fpga_memory_attributes: return IR(2701, 33);
    case Extension::kSPV_INTEL_fpga_reg: return IR(2734, 19);
    case Extension::kSPV_INTEL_function_pointers: return IR(2753, 28);
    case Extension::kSPV_INTEL_function_variants: return IR(2781, 28);
    case Extension::kSPV_INTEL_global_variable_fpga_decorations: return IR(2809, 43);
    case Extension::kSPV_INTEL_global_variable_host_access: return IR(2852, 38);
    case Extension::kSPV_INTEL_inline_assembly: return IR(2890, 26);
    case Extension::kSPV_INTEL_int4: return IR(2916, 15);
    case Extension::kSPV_INTEL_io_pipes: return IR(2931, 19);
    case Extension::kSPV_INTEL_kernel_attributes: return IR(2950, 28);
    case Extension::kSPV_INTEL_long_composites: return IR(2978, 26);
    case Extension::kSPV_INTEL_loop_fuse: return IR(3004, 20);
    case Extension::kSPV_INTEL_masked_gather_scatter: return IR(3024, 32);
    case Extension::kSPV_INTEL_maximum_registers: return IR(3056, 28);
    case Extension::kSPV_INTEL_media_block_io: return IR(3084, 25);
    case Extension::kSPV_INTEL_memory_access_aliasing: return IR(3109, 33);
    case Extension::kSPV_INTEL_optnone: return IR(3142, 18);
    case Extension::kSPV_INTEL_predicated_io: return IR(3160, 24);
    case Extension::kSPV_INTEL_rounded_divide_sqrt: return IR(3184, 30);
    case Extension::kSPV_INTEL_runtime_aligned: return IR(3214, 26);
    case Extension::kSPV_INTEL_shader_integer_functions2: return IR(3240, 36);
    case Extension::kSPV_INTEL_split_barrier: return IR(3276, 24);
    case Extension::kSPV_INTEL_subgroup_buffer_prefetch: return IR(3300, 35);
    case Extension::kSPV_INTEL_subgroup_matrix_multiply_accumulate: return IR(3335, 46);
    case Extension::kSPV_INTEL_subgroups: return IR(3381, 20);
    case Extension::kSPV_INTEL_task_sequence: return IR(3401, 24);
    case Extension::kSPV_INTEL_tensor_float32_conversion: return IR(3425, 36);
    case Extension::kSPV_INTEL_ternary_bitwise_function: return IR(3461, 35);
    case Extension::kSPV_INTEL_unstructured_loop_controls: return IR(3496, 37);
    case Extension::kSPV_INTEL_usm_storage_classes: return IR(3533, 30);
    case Extension::kSPV_INTEL_variable_length_array: return IR(3563, 32);
    case Extension::kSPV_INTEL_vector_compute: return IR(3595, 25);
    case Extension::kSPV_KHR_16bit_storage: return IR(3620, 22);
    case Extension::kSPV_KHR_8bit_storage: return IR(3642, 21);
    case Extension::kSPV_KHR_abort: return IR(3663, 14);
    case Extension::kSPV_KHR_bfloat16: return IR(3677, 17);
    case Extension::kSPV_KHR_bit_instructions: return IR(3694, 25);
    case Extension::kSPV_KHR_compute_shader_derivatives: return IR(3719, 35);
    case Extension::kSPV_KHR_constant_data: return IR(3754, 22);
    case Extension::kSPV_KHR_cooperative_matrix: return IR(3776, 27);
    case Extension::kSPV_KHR_device_group: return IR(3803, 21);
    case Extension::kSPV_KHR_expect_assume: return IR(3824, 22);
    case Extension::kSPV_KHR_float_controls: return IR(3846, 23);
    case Extension::kSPV_KHR_float_controls2: return IR(3869, 24);
    case Extension::kSPV_KHR_fma: return IR(3893, 12);
    case Extension::kSPV_KHR_fragment_shader_barycentric: return IR(3905, 36);
    case Extension::kSPV_KHR_fragment_shading_rate: return IR(3941, 30);
    case Extension::kSPV_KHR_integer_dot_product: return IR(3971, 28);
    case Extension::kSPV_KHR_linkonce_odr: return IR(3999, 21);
    case Extension::kSPV_KHR_maximal_reconvergence: return IR(4020, 30);
    case Extension::kSPV_KHR_multiview: return IR(4050, 18);
    case Extension::kSPV_KHR_no_integer_wrap_decoration: return IR(4068, 35);
    case Extension::kSPV_KHR_non_semantic_info: return IR(4103, 26);
    case Extension::kSPV_KHR_opacity_micromap: return IR(4129, 25);
    case Extension::kSPV_KHR_physical_storage_buffer: return IR(4154, 32);
    case Extension::kSPV_KHR_poison_freeze: return IR(4186, 22);
    case Extension::kSPV_KHR_post_depth_coverage: return IR(4208, 28);
    case Extension::kSPV_KHR_quad_control: return IR(4236, 21);
    case Extension::kSPV_KHR_ray_cull_mask: return IR(4257, 22);
    case Extension::kSPV_KHR_ray_query: return IR(4279, 18);
    case Extension::kSPV_KHR_ray_tracing: return IR(4297, 20);
    case Extension::kSPV_KHR_ray_tracing_position_fetch: return IR(4317, 35);
    case Extension::kSPV_KHR_relaxed_extended_instruction: return IR(4352, 37);
    case Extension::kSPV_KHR_shader_atomic_counter_ops: return IR(4389, 34);
    case Extension::kSPV_KHR_shader_ballot: return IR(4423, 22);
    case Extension::kSPV_KHR_shader_clock: return IR(4445, 21);
    case Extension::kSPV_KHR_shader_draw_parameters: return IR(4466, 31);
    case Extension::kSPV_KHR_storage_buffer_storage_class: return IR(4497, 37);
    case Extension::kSPV_KHR_subgroup_rotate: return IR(4534, 24);
    case Extension::kSPV_KHR_subgroup_uniform_control_flow: return IR(4558, 38);
    case Extension::kSPV_KHR_subgroup_vote: return IR(4596, 22);
    case Extension::kSPV_KHR_terminate_invocation: return IR(4618, 29);
    case Extension::kSPV_KHR_uniform_group_instructions: return IR(4647, 35);
    case Extension::kSPV_KHR_untyped_pointers: return IR(4682, 25);
    case Extension::kSPV_KHR_variable_pointers: return IR(4707, 26);
    case Extension::kSPV_KHR_vulkan_memory_model: return IR(4733, 28);
    case Extension::kSPV_KHR_workgroup_memory_explicit_layout: return IR(4761, 41);
    case Extension::kSPV_NVX_multiview_per_view_attributes: return IR(4802, 38);
    case Extension::kSPV_NV_bindless_texture: return IR(4840, 24);
    case Extension::kSPV_NV_cluster_acceleration_structure: return IR(4864, 38);
    case Extension::kSPV_NV_compute_shader_derivatives: return IR(4902, 34);
    case Extension::kSPV_NV_cooperative_matrix: return IR(4936, 26);
    case Extension::kSPV_NV_cooperative_matrix2: return IR(4962, 27);
    case Extension::kSPV_NV_cooperative_matrix_decode_vector: return IR(4989, 40);
    case Extension::kSPV_NV_cooperative_vector: return IR(5029, 26);
    case Extension::kSPV_NV_displacement_micromap: return IR(5055, 29);
    case Extension::kSPV_NV_fragment_shader_barycentric: return IR(5084, 35);
    case Extension::kSPV_NV_geometry_shader_passthrough: return IR(5119, 35);
    case Extension::kSPV_NV_linear_swept_spheres: return IR(5154, 28);
    case Extension::kSPV_NV_mesh_shader: return IR(5182, 19);
    case Extension::kSPV_NV_push_constant_bank: return IR(5201, 26);
    case Extension::kSPV_NV_raw_access_chains: return IR(5227, 25);
    case Extension::kSPV_NV_ray_tracing: return IR(5252, 19);
    case Extension::kSPV_NV_ray_tracing_motion_blur: return IR(5271, 31);
    case Extension::kSPV_NV_sample_mask_override_coverage: return IR(5302, 37);
    case Extension::kSPV_NV_shader_atomic_fp16_vector: return IR(5339, 33);
    case Extension::kSPV_NV_shader_image_footprint: return IR(5372, 30);
    case Extension::kSPV_NV_shader_invocation_reorder: return IR(5402, 33);
    case Extension::kSPV_NV_shader_sm_builtins: return IR(5435, 26);
    case Extension::kSPV_NV_shader_subgroup_partitioned: return IR(5461, 35);
    case Extension::kSPV_NV_shading_rate: return IR(5496, 20);
    case Extension::kSPV_NV_stereo_view_rendering: return IR(5516, 29);
    case Extension::kSPV_NV_tensor_addressing: return IR(5545, 25);
    case Extension::kSPV_NV_viewport_array2: return IR(5570, 23);
    case Extension::kSPV_QCOM_bfloat16_muladd: return IR(5593, 25);
    case Extension::kSPV_QCOM_cooperative_matrix_conversion: return IR(5618, 39);
    case Extension::kSPV_QCOM_image_processing: return IR(5657, 26);
    case Extension::kSPV_QCOM_image_processing2: return IR(5683, 27);
    case Extension::kSPV_QCOM_image_processing3: return IR(5710, 27);
    case Extension::kSPV_QCOM_multiple_wait_queues: return IR(5737, 30);
    case Extension::kSPV_QCOM_subgroup_size: return IR(5767, 23);
    case Extension::kSPV_QCOM_tile_shading: return IR(5790, 22);
    case Extension::kSPV_SAMSUNG_intrinsic: return IR(5812, 22);
    case Extension::kSPV_VALIDATOR_ignore_type_decl_unique: return IR(5834, 38);
    case Extension::kSPV_VALVE_mixed_float_dot_product: return IR(5872, 34);
    default: break;
  }
  return {};
}

// Extension names and values, ordered by name
// The fields in order are:
//   name, indexing into kStrings
//   enum value
static const std::array<NameValue,204> kExtensionNames{{
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
    {IR(1020, 21), static_cast<uint32_t>(kSPV_AMD_weak_linkage)},
    {IR(1041, 35), static_cast<uint32_t>(kSPV_ARM_cooperative_matrix_layouts)},
    {IR(1076, 22), static_cast<uint32_t>(kSPV_ARM_core_builtins)},
    {IR(1098, 14), static_cast<uint32_t>(kSPV_ARM_graph)},
    {IR(1112, 16), static_cast<uint32_t>(kSPV_ARM_tensors)},
    {IR(1128, 25), static_cast<uint32_t>(kSPV_EXT_arithmetic_fence)},
    {IR(1153, 40), static_cast<uint32_t>(kSPV_EXT_cooperative_matrix_maintenance1)},
    {IR(1193, 36), static_cast<uint32_t>(kSPV_EXT_demote_to_helper_invocation)},
    {IR(1229, 24), static_cast<uint32_t>(kSPV_EXT_descriptor_heap)},
    {IR(1253, 28), static_cast<uint32_t>(kSPV_EXT_descriptor_indexing)},
    {IR(1281, 15), static_cast<uint32_t>(kSPV_EXT_float8)},
    {IR(1296, 31), static_cast<uint32_t>(kSPV_EXT_fragment_fully_covered)},
    {IR(1327, 36), static_cast<uint32_t>(kSPV_EXT_fragment_invocation_density)},
    {IR(1363, 34), static_cast<uint32_t>(kSPV_EXT_fragment_shader_interlock)},
    {IR(1397, 20), static_cast<uint32_t>(kSPV_EXT_long_vector)},
    {IR(1417, 20), static_cast<uint32_t>(kSPV_EXT_mesh_shader)},
    {IR(1437, 31), static_cast<uint32_t>(kSPV_EXT_ocp_microscaling_types)},
    {IR(1468, 25), static_cast<uint32_t>(kSPV_EXT_opacity_micromap)},
    {IR(1493, 16), static_cast<uint32_t>(kSPV_EXT_optnone)},
    {IR(1509, 32), static_cast<uint32_t>(kSPV_EXT_physical_storage_buffer)},
    {IR(1541, 44), static_cast<uint32_t>(kSPV_EXT_relaxed_printf_string_address_space)},
    {IR(1585, 30), static_cast<uint32_t>(kSPV_EXT_replicated_composites)},
    {IR(1615, 30), static_cast<uint32_t>(kSPV_EXT_shader_64bit_indexing)},
    {IR(1645, 34), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float16_add)},
    {IR(1679, 32), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float_add)},
    {IR(1711, 36), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float_min_max)},
    {IR(1747, 27), static_cast<uint32_t>(kSPV_EXT_shader_image_int64)},
    {IR(1774, 34), static_cast<uint32_t>(kSPV_EXT_shader_invocation_reorder)},
    {IR(1808, 30), static_cast<uint32_t>(kSPV_EXT_shader_stencil_export)},
    {IR(1838, 36), static_cast<uint32_t>(kSPV_EXT_shader_subgroup_partitioned)},
    {IR(1874, 26), static_cast<uint32_t>(kSPV_EXT_shader_tile_image)},
    {IR(1900, 36), static_cast<uint32_t>(kSPV_EXT_shader_viewport_index_layer)},
    {IR(1936, 22), static_cast<uint32_t>(kSPV_EXT_split_barrier)},
    {IR(1958, 27), static_cast<uint32_t>(kSPV_GOOGLE_decorate_string)},
    {IR(1985, 31), static_cast<uint32_t>(kSPV_GOOGLE_hlsl_functionality1)},
    {IR(2016, 21), static_cast<uint32_t>(kSPV_GOOGLE_user_type)},
    {IR(2037, 22), static_cast<uint32_t>(kSPV_INTEL_2d_block_io)},
    {IR(2059, 42), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_fixed_point)},
    {IR(2101, 45), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_floating_point)},
    {IR(2146, 39), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_integers)},
    {IR(2185, 30), static_cast<uint32_t>(kSPV_INTEL_bfloat16_conversion)},
    {IR(2215, 26), static_cast<uint32_t>(kSPV_INTEL_bindless_images)},
    {IR(2241, 25), static_cast<uint32_t>(kSPV_INTEL_blocking_pipes)},
    {IR(2266, 25), static_cast<uint32_t>(kSPV_INTEL_cache_controls)},
    {IR(2291, 23), static_cast<uint32_t>(kSPV_INTEL_debug_module)},
    {IR(2314, 44), static_cast<uint32_t>(kSPV_INTEL_device_side_avc_motion_estimation)},
    {IR(2358, 26), static_cast<uint32_t>(kSPV_INTEL_float_controls2)},
    {IR(2384, 28), static_cast<uint32_t>(kSPV_INTEL_fp_fast_math_mode)},
    {IR(2412, 23), static_cast<uint32_t>(kSPV_INTEL_fp_max_error)},
    {IR(2435, 35), static_cast<uint32_t>(kSPV_INTEL_fpga_argument_interfaces)},
    {IR(2470, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_buffer_location)},
    {IR(2501, 34), static_cast<uint32_t>(kSPV_INTEL_fpga_cluster_attributes)},
    {IR(2535, 27), static_cast<uint32_t>(kSPV_INTEL_fpga_dsp_control)},
    {IR(2562, 48), static_cast<uint32_t>(kSPV_INTEL_fpga_invocation_pipelining_attributes)},
    {IR(2610, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_latency_control)},
    {IR(2641, 29), static_cast<uint32_t>(kSPV_INTEL_fpga_loop_controls)},
    {IR(2670, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_memory_accesses)},
    {IR(2701, 33), static_cast<uint32_t>(kSPV_INTEL_fpga_memory_attributes)},
    {IR(2734, 19), static_cast<uint32_t>(kSPV_INTEL_fpga_reg)},
    {IR(2753, 28), static_cast<uint32_t>(kSPV_INTEL_function_pointers)},
    {IR(2781, 28), static_cast<uint32_t>(kSPV_INTEL_function_variants)},
    {IR(2809, 43), static_cast<uint32_t>(kSPV_INTEL_global_variable_fpga_decorations)},
    {IR(2852, 38), static_cast<uint32_t>(kSPV_INTEL_global_variable_host_access)},
    {IR(2890, 26), static_cast<uint32_t>(kSPV_INTEL_inline_assembly)},
    {IR(2916, 15), static_cast<uint32_t>(kSPV_INTEL_int4)},
    {IR(2931, 19), static_cast<uint32_t>(kSPV_INTEL_io_pipes)},
    {IR(2950, 28), static_cast<uint32_t>(kSPV_INTEL_kernel_attributes)},
    {IR(2978, 26), static_cast<uint32_t>(kSPV_INTEL_long_composites)},
    {IR(3004, 20), static_cast<uint32_t>(kSPV_INTEL_loop_fuse)},
    {IR(3024, 32), static_cast<uint32_t>(kSPV_INTEL_masked_gather_scatter)},
    {IR(3056, 28), static_cast<uint32_t>(kSPV_INTEL_maximum_registers)},
    {IR(3084, 25), static_cast<uint32_t>(kSPV_INTEL_media_block_io)},
    {IR(3109, 33), static_cast<uint32_t>(kSPV_INTEL_memory_access_aliasing)},
    {IR(3142, 18), static_cast<uint32_t>(kSPV_INTEL_optnone)},
    {IR(3160, 24), static_cast<uint32_t>(kSPV_INTEL_predicated_io)},
    {IR(3184, 30), static_cast<uint32_t>(kSPV_INTEL_rounded_divide_sqrt)},
    {IR(3214, 26), static_cast<uint32_t>(kSPV_INTEL_runtime_aligned)},
    {IR(3240, 36), static_cast<uint32_t>(kSPV_INTEL_shader_integer_functions2)},
    {IR(3276, 24), static_cast<uint32_t>(kSPV_INTEL_split_barrier)},
    {IR(3300, 35), static_cast<uint32_t>(kSPV_INTEL_subgroup_buffer_prefetch)},
    {IR(3335, 46), static_cast<uint32_t>(kSPV_INTEL_subgroup_matrix_multiply_accumulate)},
    {IR(3381, 20), static_cast<uint32_t>(kSPV_INTEL_subgroups)},
    {IR(3401, 24), static_cast<uint32_t>(kSPV_INTEL_task_sequence)},
    {IR(3425, 36), static_cast<uint32_t>(kSPV_INTEL_tensor_float32_conversion)},
    {IR(3461, 35), static_cast<uint32_t>(kSPV_INTEL_ternary_bitwise_function)},
    {IR(3496, 37), static_cast<uint32_t>(kSPV_INTEL_unstructured_loop_controls)},
    {IR(3533, 30), static_cast<uint32_t>(kSPV_INTEL_usm_storage_classes)},
    {IR(3563, 32), static_cast<uint32_t>(kSPV_INTEL_variable_length_array)},
    {IR(3595, 25), static_cast<uint32_t>(kSPV_INTEL_vector_compute)},
    {IR(3620, 22), static_cast<uint32_t>(kSPV_KHR_16bit_storage)},
    {IR(3642, 21), static_cast<uint32_t>(kSPV_KHR_8bit_storage)},
    {IR(3663, 14), static_cast<uint32_t>(kSPV_KHR_abort)},
    {IR(3677, 17), static_cast<uint32_t>(kSPV_KHR_bfloat16)},
    {IR(3694, 25), static_cast<uint32_t>(kSPV_KHR_bit_instructions)},
    {IR(3719, 35), static_cast<uint32_t>(kSPV_KHR_compute_shader_derivatives)},
    {IR(3754, 22), static_cast<uint32_t>(kSPV_KHR_constant_data)},
    {IR(3776, 27), static_cast<uint32_t>(kSPV_KHR_cooperative_matrix)},
    {IR(3803, 21), static_cast<uint32_t>(kSPV_KHR_device_group)},
    {IR(3824, 22), static_cast<uint32_t>(kSPV_KHR_expect_assume)},
    {IR(3846, 23), static_cast<uint32_t>(kSPV_KHR_float_controls)},
    {IR(3869, 24), static_cast<uint32_t>(kSPV_KHR_float_controls2)},
    {IR(3893, 12), static_cast<uint32_t>(kSPV_KHR_fma)},
    {IR(3905, 36), static_cast<uint32_t>(kSPV_KHR_fragment_shader_barycentric)},
    {IR(3941, 30), static_cast<uint32_t>(kSPV_KHR_fragment_shading_rate)},
    {IR(3971, 28), static_cast<uint32_t>(kSPV_KHR_integer_dot_product)},
    {IR(3999, 21), static_cast<uint32_t>(kSPV_KHR_linkonce_odr)},
    {IR(4020, 30), static_cast<uint32_t>(kSPV_KHR_maximal_reconvergence)},
    {IR(4050, 18), static_cast<uint32_t>(kSPV_KHR_multiview)},
    {IR(4068, 35), static_cast<uint32_t>(kSPV_KHR_no_integer_wrap_decoration)},
    {IR(4103, 26), static_cast<uint32_t>(kSPV_KHR_non_semantic_info)},
    {IR(4129, 25), static_cast<uint32_t>(kSPV_KHR_opacity_micromap)},
    {IR(4154, 32), static_cast<uint32_t>(kSPV_KHR_physical_storage_buffer)},
    {IR(4186, 22), static_cast<uint32_t>(kSPV_KHR_poison_freeze)},
    {IR(4208, 28), static_cast<uint32_t>(kSPV_KHR_post_depth_coverage)},
    {IR(4236, 21), static_cast<uint32_t>(kSPV_KHR_quad_control)},
    {IR(4257, 22), static_cast<uint32_t>(kSPV_KHR_ray_cull_mask)},
    {IR(4279, 18), static_cast<uint32_t>(kSPV_KHR_ray_query)},
    {IR(4297, 20), static_cast<uint32_t>(kSPV_KHR_ray_tracing)},
    {IR(4317, 35), static_cast<uint32_t>(kSPV_KHR_ray_tracing_position_fetch)},
    {IR(4352, 37), static_cast<uint32_t>(kSPV_KHR_relaxed_extended_instruction)},
    {IR(4389, 34), static_cast<uint32_t>(kSPV_KHR_shader_atomic_counter_ops)},
    {IR(4423, 22), static_cast<uint32_t>(kSPV_KHR_shader_ballot)},
    {IR(4445, 21), static_cast<uint32_t>(kSPV_KHR_shader_clock)},
    {IR(4466, 31), static_cast<uint32_t>(kSPV_KHR_shader_draw_parameters)},
    {IR(4497, 37), static_cast<uint32_t>(kSPV_KHR_storage_buffer_storage_class)},
    {IR(4534, 24), static_cast<uint32_t>(kSPV_KHR_subgroup_rotate)},
    {IR(4558, 38), static_cast<uint32_t>(kSPV_KHR_subgroup_uniform_control_flow)},
    {IR(4596, 22), static_cast<uint32_t>(kSPV_KHR_subgroup_vote)},
    {IR(4618, 29), static_cast<uint32_t>(kSPV_KHR_terminate_invocation)},
    {IR(4647, 35), static_cast<uint32_t>(kSPV_KHR_uniform_group_instructions)},
    {IR(4682, 25), static_cast<uint32_t>(kSPV_KHR_untyped_pointers)},
    {IR(4707, 26), static_cast<uint32_t>(kSPV_KHR_variable_pointers)},
    {IR(4733, 28), static_cast<uint32_t>(kSPV_KHR_vulkan_memory_model)},
    {IR(4761, 41), static_cast<uint32_t>(kSPV_KHR_workgroup_memory_explicit_layout)},
    {IR(4802, 38), static_cast<uint32_t>(kSPV_NVX_multiview_per_view_attributes)},
    {IR(4840, 24), static_cast<uint32_t>(kSPV_NV_bindless_texture)},
    {IR(4864, 38), static_cast<uint32_t>(kSPV_NV_cluster_acceleration_structure)},
    {IR(4902, 34), static_cast<uint32_t>(kSPV_NV_compute_shader_derivatives)},
    {IR(4936, 26), static_cast<uint32_t>(kSPV_NV_cooperative_matrix)},
    {IR(4962, 27), static_cast<uint32_t>(kSPV_NV_cooperative_matrix2)},
    {IR(4989, 40), static_cast<uint32_t>(kSPV_NV_cooperative_matrix_decode_vector)},
    {IR(5029, 26), static_cast<uint32_t>(kSPV_NV_cooperative_vector)},
    {IR(5055, 29), static_cast<uint32_t>(kSPV_NV_displacement_micromap)},
    {IR(5084, 35), static_cast<uint32_t>(kSPV_NV_fragment_shader_barycentric)},
    {IR(5119, 35), static_cast<uint32_t>(kSPV_NV_geometry_shader_passthrough)},
    {IR(5154, 28), static_cast<uint32_t>(kSPV_NV_linear_swept_spheres)},
    {IR(5182, 19), static_cast<uint32_t>(kSPV_NV_mesh_shader)},
    {IR(5201, 26), static_cast<uint32_t>(kSPV_NV_push_constant_bank)},
    {IR(5227, 25), static_cast<uint32_t>(kSPV_NV_raw_access_chains)},
    {IR(5252, 19), static_cast<uint32_t>(kSPV_NV_ray_tracing)},
    {IR(5271, 31), static_cast<uint32_t>(kSPV_NV_ray_tracing_motion_blur)},
    {IR(5302, 37), static_cast<uint32_t>(kSPV_NV_sample_mask_override_coverage)},
    {IR(5339, 33), static_cast<uint32_t>(kSPV_NV_shader_atomic_fp16_vector)},
    {IR(5372, 30), static_cast<uint32_t>(kSPV_NV_shader_image_footprint)},
    {IR(5402, 33), static_cast<uint32_t>(kSPV_NV_shader_invocation_reorder)},
    {IR(5435, 26), static_cast<uint32_t>(kSPV_NV_shader_sm_builtins)},
    {IR(5461, 35), static_cast<uint32_t>(kSPV_NV_shader_subgroup_partitioned)},
    {IR(5496, 20), static_cast<uint32_t>(kSPV_NV_shading_rate)},
    {IR(5516, 29), static_cast<uint32_t>(kSPV_NV_stereo_view_rendering)},
    {IR(5545, 25), static_cast<uint32_t>(kSPV_NV_tensor_addressing)},
    {IR(5570, 23), static_cast<uint32_t>(kSPV_NV_viewport_array2)},
    {IR(5593, 25), static_cast<uint32_t>(kSPV_QCOM_bfloat16_muladd)},
    {IR(5618, 39), static_cast<uint32_t>(kSPV_QCOM_cooperative_matrix_conversion)},
    {IR(5657, 26), static_cast<uint32_t>(kSPV_QCOM_image_processing)},
    {IR(5683, 27), static_cast<uint32_t>(kSPV_QCOM_image_processing2)},
    {IR(5710, 27), static_cast<uint32_t>(kSPV_QCOM_image_processing3)},
    {IR(5737, 30), static_cast<uint32_t>(kSPV_QCOM_multiple_wait_queues)},
    {IR(5767, 23), static_cast<uint32_t>(kSPV_QCOM_subgroup_size)},
    {IR(5790, 22), static_cast<uint32_t>(kSPV_QCOM_tile_shading)},
    {IR(5812, 22), static_cast<uint32_t>(kSPV_SAMSUNG_intrinsic)},
    {IR(5834, 38), static_cast<uint32_t>(kSPV_VALIDATOR_ignore_type_decl_unique)},
    {IR(5872, 34), static_cast<uint32_t>(kSPV_VALVE_mixed_float_dot_product)},
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
static const std::array<OperandDesc, 1249> kOperandsByValue{{
  {0,IR(0, 0),IR(5906, 9)/* ReadOnly */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {1,IR(0, 0),IR(5922, 10)/* WriteOnly */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {2,IR(0, 0),IR(5932, 10)/* ReadWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {0,IR(0, 0),IR(5942, 8)/* Logical */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {1,IR(0, 0),IR(5950, 11)/* Physical32 */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {2,IR(0, 0),IR(5971, 11)/* Physical64 */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {5348,IR(0, 0),IR(5982, 24)/* PhysicalStorageBuffer64 */,IR(0, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {0,IR(0, 0),IR(6064, 9)/* Position */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {1,IR(0, 0),IR(6080, 10)/* PointSize */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {3,IR(0, 0),IR(6090, 13)/* ClipDistance */,IR(0, 0),IR(4, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4,IR(0, 0),IR(6103, 13)/* CullDistance */,IR(0, 0),IR(5, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5,IR(0, 0),IR(6116, 9)/* VertexId */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {6,IR(0, 0),IR(6125, 11)/* InstanceId */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {7,IR(0, 0),IR(6136, 12)/* PrimitiveId */,IR(0, 0),IR(6, 6),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {8,IR(0, 0),IR(6226, 13)/* InvocationId */,IR(0, 0),IR(12, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {9,IR(0, 0),IR(6239, 6)/* Layer */,IR(0, 0),IR(14, 5),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {10,IR(0, 0),IR(6285, 14)/* ViewportIndex */,IR(0, 0),IR(19, 5),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {11,IR(0, 0),IR(6333, 15)/* TessLevelOuter */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {12,IR(0, 0),IR(6348, 15)/* TessLevelInner */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {13,IR(0, 0),IR(6363, 10)/* TessCoord */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {14,IR(0, 0),IR(6373, 14)/* PatchVertices */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {15,IR(0, 0),IR(6387, 10)/* FragCoord */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {16,IR(0, 0),IR(6397, 11)/* PointCoord */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {17,IR(0, 0),IR(6408, 12)/* FrontFacing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {18,IR(0, 0),IR(6420, 9)/* SampleId */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {19,IR(0, 0),IR(6447, 15)/* SamplePosition */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {20,IR(0, 0),IR(6462, 11)/* SampleMask */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {22,IR(0, 0),IR(6473, 10)/* FragDepth */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {23,IR(0, 0),IR(6483, 17)/* HelperInvocation */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {24,IR(0, 0),IR(6500, 14)/* NumWorkgroups */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {25,IR(0, 0),IR(6514, 14)/* WorkgroupSize */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {26,IR(0, 0),IR(6528, 12)/* WorkgroupId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {27,IR(0, 0),IR(6540, 18)/* LocalInvocationId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {28,IR(0, 0),IR(6558, 19)/* GlobalInvocationId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {29,IR(0, 0),IR(6577, 21)/* LocalInvocationIndex */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {30,IR(0, 0),IR(6598, 8)/* WorkDim */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {31,IR(0, 0),IR(6606, 11)/* GlobalSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {32,IR(0, 0),IR(6617, 22)/* EnqueuedWorkgroupSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {33,IR(0, 0),IR(6639, 13)/* GlobalOffset */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {34,IR(0, 0),IR(6652, 15)/* GlobalLinearId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {36,IR(0, 0),IR(6667, 13)/* SubgroupSize */,IR(0, 0),IR(26, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {37,IR(0, 0),IR(6714, 16)/* SubgroupMaxSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {38,IR(0, 0),IR(6730, 13)/* NumSubgroups */,IR(0, 0),IR(29, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {39,IR(0, 0),IR(6743, 21)/* NumEnqueuedSubgroups */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {40,IR(0, 0),IR(6764, 11)/* SubgroupId */,IR(0, 0),IR(29, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {41,IR(0, 0),IR(6775, 26)/* SubgroupLocalInvocationId */,IR(0, 0),IR(26, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {42,IR(0, 0),IR(6801, 12)/* VertexIndex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {43,IR(0, 0),IR(6813, 14)/* InstanceIndex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4160,IR(0, 0),IR(6827, 10)/* CoreIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4161,IR(0, 0),IR(6853, 13)/* CoreCountARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4162,IR(0, 0),IR(6866, 13)/* CoreMaxIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4163,IR(0, 0),IR(6879, 10)/* WarpIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4164,IR(0, 0),IR(6889, 13)/* WarpMaxIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4416,IR(0, 0),IR(6902, 15)/* SubgroupEqMask */,IR(1, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4417,IR(0, 0),IR(6957, 15)/* SubgroupGeMask */,IR(2, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4418,IR(0, 0),IR(6990, 15)/* SubgroupGtMask */,IR(3, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4419,IR(0, 0),IR(7023, 15)/* SubgroupLeMask */,IR(4, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4420,IR(0, 0),IR(7056, 15)/* SubgroupLtMask */,IR(5, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4424,IR(0, 0),IR(7089, 11)/* BaseVertex */,IR(0, 0),IR(34, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4425,IR(0, 0),IR(7115, 13)/* BaseInstance */,IR(0, 0),IR(34, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4426,IR(0, 0),IR(7128, 10)/* DrawIndex */,IR(0, 0),IR(35, 3),IR(4, 3),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4432,IR(0, 0),IR(7138, 24)/* PrimitiveShadingRateKHR */,IR(0, 0),IR(38, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4438,IR(0, 0),IR(7185, 12)/* DeviceIndex */,IR(0, 0),IR(39, 1),IR(8, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4440,IR(0, 0),IR(7209, 10)/* ViewIndex */,IR(0, 0),IR(40, 1),IR(9, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4444,IR(0, 0),IR(7229, 15)/* ShadingRateKHR */,IR(0, 0),IR(38, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4492,IR(0, 0),IR(7244, 15)/* TileOffsetQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4493,IR(0, 0),IR(7275, 18)/* TileDimensionQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4494,IR(0, 0),IR(7293, 18)/* TileApronSizeQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4992,IR(0, 0),IR(7311, 20)/* BaryCoordNoPerspAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4993,IR(0, 0),IR(7331, 28)/* BaryCoordNoPerspCentroidAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4994,IR(0, 0),IR(7359, 26)/* BaryCoordNoPerspSampleAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4995,IR(0, 0),IR(7385, 19)/* BaryCoordSmoothAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4996,IR(0, 0),IR(7404, 27)/* BaryCoordSmoothCentroidAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4997,IR(0, 0),IR(7431, 25)/* BaryCoordSmoothSampleAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4998,IR(0, 0),IR(7456, 22)/* BaryCoordPullModelAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5014,IR(0, 0),IR(7478, 18)/* FragStencilRefEXT */,IR(0, 0),IR(42, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5021,IR(0, 0),IR(7513, 29)/* RemainingRecursionLevelsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5073,IR(0, 0),IR(7560, 16)/* ShaderIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5122,IR(0, 0),IR(7576, 15)/* SamplerHeapEXT */,IR(0, 0),IR(44, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5123,IR(0, 0),IR(7609, 16)/* ResourceHeapEXT */,IR(0, 0),IR(44, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5253,IR(0, 0),IR(7625, 15)/* ViewportMaskNV */,IR(0, 0),IR(45, 2),IR(12, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5257,IR(0, 0),IR(7661, 20)/* SecondaryPositionNV */,IR(0, 0),IR(47, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5258,IR(0, 0),IR(7700, 24)/* SecondaryViewportMaskNV */,IR(0, 0),IR(47, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5261,IR(0, 0),IR(7724, 18)/* PositionPerViewNV */,IR(0, 0),IR(48, 2),IR(15, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5262,IR(0, 0),IR(7762, 22)/* ViewportMaskPerViewNV */,IR(0, 0),IR(48, 2),IR(15, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5264,IR(0, 0),IR(7784, 16)/* FullyCoveredEXT */,IR(0, 0),IR(50, 1),IR(17, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5274,IR(0, 0),IR(7824, 12)/* TaskCountNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5275,IR(0, 0),IR(7836, 17)/* PrimitiveCountNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5276,IR(0, 0),IR(7853, 19)/* PrimitiveIndicesNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5277,IR(0, 0),IR(7872, 22)/* ClipDistancePerViewNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5278,IR(0, 0),IR(7894, 22)/* CullDistancePerViewNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5279,IR(0, 0),IR(7916, 15)/* LayerPerViewNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5280,IR(0, 0),IR(7931, 16)/* MeshViewCountNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5281,IR(0, 0),IR(7947, 18)/* MeshViewIndicesNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5286,IR(0, 0),IR(7965, 13)/* BaryCoordKHR */,IR(6, 1),IR(52, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5287,IR(0, 0),IR(8013, 20)/* BaryCoordNoPerspKHR */,IR(7, 1),IR(52, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5292,IR(0, 0),IR(8052, 12)/* FragSizeEXT */,IR(8, 1),IR(53, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5293,IR(0, 0),IR(8098, 23)/* FragInvocationCountEXT */,IR(9, 1),IR(53, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5294,IR(0, 0),IR(8143, 25)/* PrimitivePointIndicesEXT */,IR(0, 0),IR(54, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5295,IR(0, 0),IR(8168, 24)/* PrimitiveLineIndicesEXT */,IR(0, 0),IR(54, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5296,IR(0, 0),IR(8192, 28)/* PrimitiveTriangleIndicesEXT */,IR(0, 0),IR(54, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5299,IR(0, 0),IR(8220, 17)/* CullPrimitiveEXT */,IR(0, 0),IR(54, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5319,IR(0, 0),IR(8237, 12)/* LaunchIdKHR */,IR(10, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5320,IR(0, 0),IR(8260, 14)/* LaunchSizeKHR */,IR(11, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5321,IR(0, 0),IR(8287, 18)/* WorldRayOriginKHR */,IR(12, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5322,IR(0, 0),IR(8322, 21)/* WorldRayDirectionKHR */,IR(13, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5323,IR(0, 0),IR(8363, 19)/* ObjectRayOriginKHR */,IR(14, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5324,IR(0, 0),IR(8400, 22)/* ObjectRayDirectionKHR */,IR(15, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5325,IR(0, 0),IR(8443, 11)/* RayTminKHR */,IR(16, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5326,IR(0, 0),IR(8464, 11)/* RayTmaxKHR */,IR(17, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5327,IR(0, 0),IR(8485, 23)/* InstanceCustomIndexKHR */,IR(18, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5330,IR(0, 0),IR(8530, 17)/* ObjectToWorldKHR */,IR(19, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5331,IR(0, 0),IR(8563, 17)/* WorldToObjectKHR */,IR(20, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5332,IR(0, 0),IR(8596, 7)/* HitTNV */,IR(0, 0),IR(57, 1),IR(26, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5333,IR(0, 0),IR(8603, 11)/* HitKindKHR */,IR(21, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5334,IR(0, 0),IR(8624, 17)/* CurrentRayTimeNV */,IR(0, 0),IR(58, 1),IR(27, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5335,IR(0, 0),IR(8664, 30)/* HitTriangleVertexPositionsKHR */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5337,IR(0, 0),IR(8721, 34)/* HitMicroTriangleVertexPositionsNV */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5344,IR(0, 0),IR(8788, 37)/* HitMicroTriangleVertexBarycentricsNV */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5351,IR(0, 0),IR(8825, 20)/* IncomingRayFlagsKHR */,IR(22, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5352,IR(0, 0),IR(8864, 20)/* RayGeometryIndexKHR */,IR(0, 0),IR(61, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5359,IR(0, 0),IR(8884, 14)/* HitIsSphereNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5360,IR(0, 0),IR(8926, 11)/* HitIsLSSNV */,IR(0, 0),IR(63, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5361,IR(0, 0),IR(8976, 20)/* HitSpherePositionNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5374,IR(0, 0),IR(8996, 13)/* WarpsPerSMNV */,IR(0, 0),IR(64, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5375,IR(0, 0),IR(9028, 10)/* SMCountNV */,IR(0, 0),IR(64, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5376,IR(0, 0),IR(9038, 9)/* WarpIDNV */,IR(0, 0),IR(64, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5377,IR(0, 0),IR(9047, 7)/* SMIDNV */,IR(0, 0),IR(64, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5396,IR(0, 0),IR(9054, 18)/* HitLSSPositionsNV */,IR(0, 0),IR(63, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5405,IR(0, 0),IR(9072, 34)/* HitKindFrontFacingMicroTriangleNV */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5406,IR(0, 0),IR(9106, 33)/* HitKindBackFacingMicroTriangleNV */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5420,IR(0, 0),IR(9139, 18)/* HitSphereRadiusNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5421,IR(0, 0),IR(9157, 14)/* HitLSSRadiiNV */,IR(0, 0),IR(63, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5436,IR(0, 0),IR(9171, 12)/* ClusterIDNV */,IR(0, 0),IR(65, 1),IR(31, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {6021,IR(0, 0),IR(9224, 12)/* CullMaskKHR */,IR(0, 0),IR(66, 1),IR(32, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {0,IR(0, 0),IR(9251, 7)/* Matrix */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {1,IR(0, 0),IR(6073, 7)/* Shader */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {2,IR(0, 0),IR(6148, 9)/* Geometry */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {3,IR(0, 0),IR(6157, 13)/* Tessellation */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4,IR(0, 0),IR(5961, 10)/* Addresses */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5,IR(0, 0),IR(9258, 8)/* Linkage */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6,IR(0, 0),IR(5915, 7)/* Kernel */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {7,IR(0, 0),IR(9266, 9)/* Vector16 */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {8,IR(0, 0),IR(9275, 14)/* Float16Buffer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {9,IR(0, 0),IR(9289, 8)/* Float16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {10,IR(0, 0),IR(9297, 8)/* Float64 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {11,IR(0, 0),IR(9305, 6)/* Int64 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {12,IR(0, 0),IR(9311, 13)/* Int64Atomics */,IR(0, 0),IR(68, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {13,IR(0, 0),IR(9324, 11)/* ImageBasic */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {14,IR(0, 0),IR(9335, 15)/* ImageReadWrite */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {15,IR(0, 0),IR(9350, 12)/* ImageMipmap */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {17,IR(0, 0),IR(9362, 6)/* Pipes */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {18,IR(0, 0),IR(9368, 7)/* Groups */,IR(0, 0),IR(1, 0),IR(33, 1),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {19,IR(0, 0),IR(9375, 14)/* DeviceEnqueue */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {20,IR(0, 0),IR(9389, 15)/* LiteralSampler */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {21,IR(0, 0),IR(9404, 14)/* AtomicStorage */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {22,IR(0, 0),IR(9418, 6)/* Int16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {23,IR(0, 0),IR(9424, 22)/* TessellationPointSize */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {24,IR(0, 0),IR(9446, 18)/* GeometryPointSize */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {25,IR(0, 0),IR(9464, 20)/* ImageGatherExtended */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {27,IR(0, 0),IR(9484, 24)/* StorageImageMultisample */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {28,IR(0, 0),IR(9508, 34)/* UniformBufferArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {29,IR(0, 0),IR(9542, 33)/* SampledImageArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {30,IR(0, 0),IR(9575, 34)/* StorageBufferArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {31,IR(0, 0),IR(9609, 33)/* StorageImageArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {32,IR(0, 0),IR(6090, 13)/* ClipDistance */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {33,IR(0, 0),IR(6103, 13)/* CullDistance */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {34,IR(0, 0),IR(9642, 15)/* ImageCubeArray */,IR(0, 0),IR(71, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {35,IR(0, 0),IR(6429, 18)/* SampleRateShading */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {36,IR(0, 0),IR(9674, 10)/* ImageRect */,IR(0, 0),IR(72, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {37,IR(0, 0),IR(9684, 12)/* SampledRect */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {38,IR(0, 0),IR(9696, 15)/* GenericPointer */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {39,IR(0, 0),IR(9711, 5)/* Int8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {40,IR(0, 0),IR(9716, 16)/* InputAttachment */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {41,IR(0, 0),IR(9732, 16)/* SparseResidency */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {42,IR(0, 0),IR(9748, 7)/* MinLod */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {43,IR(0, 0),IR(9755, 10)/* Sampled1D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {44,IR(0, 0),IR(9765, 8)/* Image1D */,IR(0, 0),IR(73, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {45,IR(0, 0),IR(9657, 17)/* SampledCubeArray */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {46,IR(0, 0),IR(9773, 14)/* SampledBuffer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {47,IR(0, 0),IR(9787, 12)/* ImageBuffer */,IR(0, 0),IR(74, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {48,IR(0, 0),IR(9799, 13)/* ImageMSArray */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {49,IR(0, 0),IR(9812, 28)/* StorageImageExtendedFormats */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {50,IR(0, 0),IR(9840, 11)/* ImageQuery */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {51,IR(0, 0),IR(9851, 18)/* DerivativeControl */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {52,IR(0, 0),IR(9869, 22)/* InterpolationFunction */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {53,IR(0, 0),IR(9891, 18)/* TransformFeedback */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {54,IR(0, 0),IR(9909, 16)/* GeometryStreams */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {55,IR(0, 0),IR(9925, 30)/* StorageImageReadWithoutFormat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {56,IR(0, 0),IR(9955, 31)/* StorageImageWriteWithoutFormat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {57,IR(0, 0),IR(6299, 14)/* MultiViewport */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {58,IR(0, 0),IR(9986, 17)/* SubgroupDispatch */,IR(0, 0),IR(75, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {59,IR(0, 0),IR(10003, 13)/* NamedBarrier */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {60,IR(0, 0),IR(10016, 12)/* PipeStorage */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {61,IR(0, 0),IR(6680, 16)/* GroupNonUniform */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {62,IR(0, 0),IR(10028, 20)/* GroupNonUniformVote */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {63,IR(0, 0),IR(10048, 26)/* GroupNonUniformArithmetic */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {64,IR(0, 0),IR(6935, 22)/* GroupNonUniformBallot */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {65,IR(0, 0),IR(10074, 23)/* GroupNonUniformShuffle */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {66,IR(0, 0),IR(10097, 31)/* GroupNonUniformShuffleRelative */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {67,IR(0, 0),IR(10128, 25)/* GroupNonUniformClustered */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {68,IR(0, 0),IR(10153, 20)/* GroupNonUniformQuad */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {69,IR(0, 0),IR(6245, 12)/* ShaderLayer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {70,IR(0, 0),IR(6313, 20)/* ShaderViewportIndex */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {71,IR(0, 0),IR(10173, 18)/* UniformDecoration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4165,IR(0, 0),IR(6837, 16)/* CoreBuiltinsARM */,IR(0, 0),IR(1, 0),IR(34, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4166,IR(0, 0),IR(10191, 28)/* TileImageColorReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4167,IR(0, 0),IR(10219, 28)/* TileImageDepthReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4168,IR(0, 0),IR(10247, 30)/* TileImageStencilReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4174,IR(0, 0),IR(10277, 11)/* TensorsARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4175,IR(0, 0),IR(10288, 37)/* StorageTensorArrayDynamicIndexingARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4176,IR(0, 0),IR(10325, 40)/* StorageTensorArrayNonUniformIndexingARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4191,IR(0, 0),IR(10365, 9)/* GraphARM */,IR(0, 0),IR(1, 0),IR(37, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4201,IR(0, 0),IR(10374, 28)/* CooperativeMatrixLayoutsARM */,IR(0, 0),IR(1, 0),IR(38, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4212,IR(0, 0),IR(10402, 10)/* Float8EXT */,IR(0, 0),IR(1, 0),IR(39, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4213,IR(0, 0),IR(10412, 27)/* Float8CooperativeMatrixEXT */,IR(0, 0),IR(78, 2),IR(39, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4228,IR(0, 0),IR(10460, 10)/* Float6EXT */,IR(0, 0),IR(1, 0),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4229,IR(0, 0),IR(10470, 10)/* Float4EXT */,IR(0, 0),IR(1, 0),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4230,IR(0, 0),IR(10480, 22)/* Float8UnsignedE8M0EXT */,IR(0, 0),IR(1, 0),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4231,IR(0, 0),IR(10502, 10)/* MXInt8EXT */,IR(0, 0),IR(1, 0),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4232,IR(0, 0),IR(10512, 18)/* BitcastExtractEXT */,IR(0, 0),IR(1, 0),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4422,IR(0, 0),IR(7162, 23)/* FragmentShadingRateKHR */,IR(0, 0),IR(3, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4423,IR(0, 0),IR(6696, 18)/* SubgroupBallotKHR */,IR(0, 0),IR(1, 0),IR(2, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4427,IR(0, 0),IR(7100, 15)/* DrawParameters */,IR(0, 0),IR(3, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4428,IR(0, 0),IR(10530, 33)/* WorkgroupMemoryExplicitLayoutKHR */,IR(0, 0),IR(3, 1),IR(41, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4429,IR(0, 0),IR(10563, 43)/* WorkgroupMemoryExplicitLayout8BitAccessKHR */,IR(0, 0),IR(80, 1),IR(41, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4430,IR(0, 0),IR(10606, 44)/* WorkgroupMemoryExplicitLayout16BitAccessKHR */,IR(0, 0),IR(80, 1),IR(41, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4431,IR(0, 0),IR(10650, 16)/* SubgroupVoteKHR */,IR(0, 0),IR(1, 0),IR(42, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4433,IR(0, 0),IR(10666, 25)/* StorageBuffer16BitAccess */,IR(23, 1),IR(1, 0),IR(43, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4434,IR(0, 0),IR(10719, 35)/* UniformAndStorageBuffer16BitAccess */,IR(24, 1),IR(81, 1),IR(43, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4435,IR(0, 0),IR(10771, 22)/* StoragePushConstant16 */,IR(0, 0),IR(1, 0),IR(43, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4436,IR(0, 0),IR(10793, 21)/* StorageInputOutput16 */,IR(0, 0),IR(1, 0),IR(43, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4437,IR(0, 0),IR(7197, 12)/* DeviceGroup */,IR(0, 0),IR(1, 0),IR(8, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4439,IR(0, 0),IR(7219, 10)/* MultiView */,IR(0, 0),IR(3, 1),IR(9, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4441,IR(0, 0),IR(10814, 30)/* VariablePointersStorageBuffer */,IR(0, 0),IR(3, 1),IR(44, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4442,IR(0, 0),IR(10844, 17)/* VariablePointers */,IR(0, 0),IR(82, 1),IR(44, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4445,IR(0, 0),IR(10861, 17)/* AtomicStorageOps */,IR(0, 0),IR(83, 1),IR(45, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4447,IR(0, 0),IR(10878, 28)/* SampleMaskPostDepthCoverage */,IR(0, 0),IR(1, 0),IR(46, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4448,IR(0, 0),IR(10906, 24)/* StorageBuffer8BitAccess */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4449,IR(0, 0),IR(10930, 34)/* UniformAndStorageBuffer8BitAccess */,IR(0, 0),IR(84, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4450,IR(0, 0),IR(10964, 21)/* StoragePushConstant8 */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4464,IR(0, 0),IR(10985, 15)/* DenormPreserve */,IR(0, 0),IR(1, 0),IR(48, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4465,IR(0, 0),IR(11000, 18)/* DenormFlushToZero */,IR(0, 0),IR(1, 0),IR(48, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4466,IR(0, 0),IR(11018, 25)/* SignedZeroInfNanPreserve */,IR(0, 0),IR(1, 0),IR(48, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4467,IR(0, 0),IR(11043, 16)/* RoundingModeRTE */,IR(0, 0),IR(1, 0),IR(48, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4468,IR(0, 0),IR(11059, 16)/* RoundingModeRTZ */,IR(0, 0),IR(1, 0),IR(48, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4471,IR(0, 0),IR(11075, 23)/* RayQueryProvisionalKHR */,IR(0, 0),IR(3, 1),IR(49, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4472,IR(0, 0),IR(11098, 12)/* RayQueryKHR */,IR(0, 0),IR(3, 1),IR(49, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4473,IR(0, 0),IR(11110, 19)/* UntypedPointersKHR */,IR(0, 0),IR(1, 0),IR(50, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4478,IR(0, 0),IR(11129, 32)/* RayTraversalPrimitiveCullingKHR */,IR(0, 0),IR(85, 2),IR(51, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4479,IR(0, 0),IR(6183, 14)/* RayTracingKHR */,IR(0, 0),IR(3, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4484,IR(0, 0),IR(11161, 26)/* TextureSampleWeightedQCOM */,IR(0, 0),IR(1, 0),IR(53, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4485,IR(0, 0),IR(11187, 21)/* TextureBoxFilterQCOM */,IR(0, 0),IR(1, 0),IR(53, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4486,IR(0, 0),IR(11208, 22)/* TextureBlockMatchQCOM */,IR(0, 0),IR(1, 0),IR(53, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4495,IR(0, 0),IR(7259, 16)/* TileShadingQCOM */,IR(0, 0),IR(3, 1),IR(54, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4496,IR(0, 0),IR(11230, 32)/* CooperativeMatrixConversionQCOM */,IR(0, 0),IR(87, 1),IR(55, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4498,IR(0, 0),IR(11262, 23)/* TextureBlockMatch2QCOM */,IR(0, 0),IR(1, 0),IR(56, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4504,IR(0, 0),IR(11285, 19)/* BFloat16MulAddQCOM */,IR(0, 0),IR(1, 0),IR(57, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4506,IR(0, 0),IR(11304, 17)/* SubgroupSizeQCOM */,IR(0, 0),IR(1, 0),IR(58, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4539,IR(0, 0),IR(11321, 23)/* MultipleWaitQueuesQCOM */,IR(0, 0),IR(1, 0),IR(59, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4543,IR(0, 0),IR(11344, 22)/* ImageGatherLinearQCOM */,IR(0, 0),IR(1, 0),IR(60, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4544,IR(0, 0),IR(11366, 29)/* ImageGatherExtendedModesQCOM */,IR(0, 0),IR(1, 0),IR(60, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5008,IR(0, 0),IR(11395, 16)/* Float16ImageAMD */,IR(0, 0),IR(3, 1),IR(61, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5009,IR(0, 0),IR(11411, 22)/* ImageGatherBiasLodAMD */,IR(0, 0),IR(3, 1),IR(62, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5010,IR(0, 0),IR(11433, 16)/* FragmentMaskAMD */,IR(0, 0),IR(3, 1),IR(63, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5013,IR(0, 0),IR(7496, 17)/* StencilExportEXT */,IR(0, 0),IR(3, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5015,IR(0, 0),IR(11449, 21)/* ImageReadWriteLodAMD */,IR(0, 0),IR(3, 1),IR(64, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5016,IR(0, 0),IR(11470, 14)/* Int64ImageEXT */,IR(0, 0),IR(68, 1),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5055,IR(0, 0),IR(11484, 15)/* ShaderClockKHR */,IR(0, 0),IR(1, 0),IR(66, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5067,IR(0, 0),IR(7542, 18)/* ShaderEnqueueAMDX */,IR(0, 0),IR(3, 1),IR(67, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5087,IR(0, 0),IR(11499, 15)/* QuadControlKHR */,IR(0, 0),IR(1, 0),IR(68, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5112,IR(0, 0),IR(11514, 14)/* Int4TypeINTEL */,IR(0, 0),IR(1, 0),IR(69, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5114,IR(0, 0),IR(11528, 27)/* Int4CooperativeMatrixINTEL */,IR(0, 0),IR(88, 2),IR(69, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5116,IR(0, 0),IR(11555, 16)/* BFloat16TypeKHR */,IR(0, 0),IR(1, 0),IR(70, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5117,IR(0, 0),IR(11571, 22)/* BFloat16DotProductKHR */,IR(0, 0),IR(90, 1),IR(70, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5118,IR(0, 0),IR(11593, 29)/* BFloat16CooperativeMatrixKHR */,IR(0, 0),IR(91, 2),IR(70, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5120,IR(0, 0),IR(11622, 9)/* AbortKHR */,IR(0, 0),IR(1, 0),IR(71, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5128,IR(0, 0),IR(7591, 18)/* DescriptorHeapEXT */,IR(0, 0),IR(93, 1),IR(72, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5146,IR(0, 0),IR(11631, 16)/* ConstantDataKHR */,IR(0, 0),IR(1, 0),IR(73, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5156,IR(0, 0),IR(11647, 16)/* PoisonFreezeKHR */,IR(0, 0),IR(1, 0),IR(74, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5181,IR(0, 0),IR(11663, 15)/* WeakLinkageAMD */,IR(0, 0),IR(94, 1),IR(75, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5249,IR(0, 0),IR(11678, 29)/* SampleMaskOverrideCoverageNV */,IR(0, 0),IR(25, 1),IR(76, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5251,IR(0, 0),IR(11707, 28)/* GeometryShaderPassthroughNV */,IR(0, 0),IR(70, 1),IR(77, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5254,IR(0, 0),IR(6257, 28)/* ShaderViewportIndexLayerEXT */,IR(25, 1),IR(95, 1),IR(78, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5255,IR(0, 0),IR(7640, 21)/* ShaderViewportMaskNV */,IR(0, 0),IR(96, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5259,IR(0, 0),IR(7681, 19)/* ShaderStereoViewNV */,IR(0, 0),IR(97, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5260,IR(0, 0),IR(7742, 20)/* PerViewAttributesNV */,IR(0, 0),IR(40, 1),IR(81, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5265,IR(0, 0),IR(7800, 24)/* FragmentFullyCoveredEXT */,IR(0, 0),IR(3, 1),IR(17, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5266,IR(0, 0),IR(6197, 14)/* MeshShadingNV */,IR(0, 0),IR(3, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5282,IR(0, 0),IR(11762, 17)/* ImageFootprintNV */,IR(0, 0),IR(1, 0),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5283,IR(0, 0),IR(6211, 15)/* MeshShadingEXT */,IR(0, 0),IR(3, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5284,IR(0, 0),IR(7990, 23)/* FragmentBarycentricKHR */,IR(26, 1),IR(1, 0),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5288,IR(0, 0),IR(11801, 31)/* ComputeDerivativeGroupQuadsKHR */,IR(27, 1),IR(3, 1),IR(83, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5291,IR(0, 0),IR(8079, 19)/* FragmentDensityEXT */,IR(28, 1),IR(3, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5297,IR(0, 0),IR(11876, 30)/* GroupNonUniformPartitionedEXT */,IR(29, 1),IR(1, 0),IR(85, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5301,IR(0, 0),IR(11935, 17)/* ShaderNonUniform */,IR(30, 1),IR(3, 1),IR(87, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5302,IR(0, 0),IR(11972, 23)/* RuntimeDescriptorArray */,IR(31, 1),IR(3, 1),IR(87, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5303,IR(0, 0),IR(12021, 36)/* InputAttachmentArrayDynamicIndexing */,IR(32, 1),IR(98, 1),IR(87, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5304,IR(0, 0),IR(12096, 39)/* UniformTexelBufferArrayDynamicIndexing */,IR(33, 1),IR(74, 1),IR(87, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5305,IR(0, 0),IR(12177, 39)/* StorageTexelBufferArrayDynamicIndexing */,IR(34, 1),IR(99, 1),IR(87, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5306,IR(0, 0),IR(12258, 37)/* UniformBufferArrayNonUniformIndexing */,IR(35, 1),IR(100, 1),IR(87, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5307,IR(0, 0),IR(12335, 36)/* SampledImageArrayNonUniformIndexing */,IR(36, 1),IR(100, 1),IR(87, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5308,IR(0, 0),IR(12410, 37)/* StorageBufferArrayNonUniformIndexing */,IR(37, 1),IR(100, 1),IR(87, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5309,IR(0, 0),IR(12487, 36)/* StorageImageArrayNonUniformIndexing */,IR(38, 1),IR(100, 1),IR(87, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5310,IR(0, 0),IR(12562, 39)/* InputAttachmentArrayNonUniformIndexing */,IR(39, 1),IR(101, 2),IR(87, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5311,IR(0, 0),IR(12643, 42)/* UniformTexelBufferArrayNonUniformIndexing */,IR(40, 1),IR(103, 2),IR(87, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5312,IR(0, 0),IR(12730, 42)/* StorageTexelBufferArrayNonUniformIndexing */,IR(41, 1),IR(105, 2),IR(87, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5336,IR(0, 0),IR(8694, 27)/* RayTracingPositionFetchKHR */,IR(0, 0),IR(3, 1),IR(88, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5340,IR(0, 0),IR(6170, 13)/* RayTracingNV */,IR(0, 0),IR(3, 1),IR(26, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5341,IR(0, 0),IR(8641, 23)/* RayTracingMotionBlurNV */,IR(0, 0),IR(3, 1),IR(27, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5345,IR(0, 0),IR(12817, 18)/* VulkanMemoryModel */,IR(42, 1),IR(1, 0),IR(89, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5346,IR(0, 0),IR(12856, 29)/* VulkanMemoryModelDeviceScope */,IR(43, 1),IR(1, 0),IR(89, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5347,IR(0, 0),IR(6033, 31)/* PhysicalStorageBufferAddresses */,IR(44, 1),IR(3, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5350,IR(0, 0),IR(12951, 32)/* ComputeDerivativeGroupLinearKHR */,IR(45, 1),IR(3, 1),IR(83, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5353,IR(0, 0),IR(13014, 25)/* RayTracingProvisionalKHR */,IR(0, 0),IR(3, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5357,IR(0, 0),IR(13039, 20)/* CooperativeMatrixNV */,IR(0, 0),IR(3, 1),IR(90, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5363,IR(0, 0),IR(13059, 33)/* FragmentShaderSampleInterlockEXT */,IR(0, 0),IR(3, 1),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5372,IR(0, 0),IR(13092, 38)/* FragmentShaderShadingRateInterlockEXT */,IR(0, 0),IR(3, 1),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5373,IR(0, 0),IR(9009, 19)/* ShaderSMBuiltinsNV */,IR(0, 0),IR(3, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5378,IR(0, 0),IR(13130, 32)/* FragmentShaderPixelInterlockEXT */,IR(0, 0),IR(3, 1),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5379,IR(0, 0),IR(13162, 25)/* DemoteToHelperInvocation */,IR(46, 1),IR(3, 1),IR(92, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5380,IR(0, 0),IR(13215, 23)/* DisplacementMicromapNV */,IR(0, 0),IR(3, 1),IR(93, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5381,IR(0, 0),IR(13238, 29)/* RayTracingOpacityMicromapKHR */,IR(47, 1),IR(3, 1),IR(94, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5383,IR(0, 0),IR(13296, 26)/* ShaderInvocationReorderNV */,IR(0, 0),IR(61, 1),IR(96, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5388,IR(0, 0),IR(13322, 27)/* ShaderInvocationReorderEXT */,IR(0, 0),IR(61, 1),IR(97, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5390,IR(0, 0),IR(13349, 18)/* BindlessTextureNV */,IR(0, 0),IR(1, 0),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5391,IR(0, 0),IR(13367, 25)/* RayQueryPositionFetchKHR */,IR(0, 0),IR(3, 1),IR(88, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5394,IR(0, 0),IR(13392, 20)/* CooperativeVectorNV */,IR(0, 0),IR(1, 0),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5404,IR(0, 0),IR(13412, 22)/* AtomicFloat16VectorNV */,IR(0, 0),IR(1, 0),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5409,IR(0, 0),IR(8755, 33)/* RayTracingDisplacementMicromapNV */,IR(0, 0),IR(61, 1),IR(93, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5414,IR(0, 0),IR(13434, 18)/* RawAccessChainsNV */,IR(0, 0),IR(1, 0),IR(101, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5418,IR(0, 0),IR(8898, 28)/* RayTracingSpheresGeometryNV */,IR(0, 0),IR(1, 0),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5419,IR(0, 0),IR(8937, 39)/* RayTracingLinearSweptSpheresGeometryNV */,IR(0, 0),IR(1, 0),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5423,IR(0, 0),IR(13452, 20)/* PushConstantBanksNV */,IR(0, 0),IR(3, 1),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5425,IR(0, 0),IR(13472, 14)/* LongVectorEXT */,IR(0, 0),IR(1, 0),IR(103, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5426,IR(0, 0),IR(13486, 23)/* Shader64BitIndexingEXT */,IR(0, 0),IR(1, 0),IR(104, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5429,IR(0, 0),IR(13509, 32)/* CooperativeMatrixConversionsEXT */,IR(0, 0),IR(1, 0),IR(105, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5430,IR(0, 0),IR(13541, 31)/* CooperativeMatrixReductionsEXT */,IR(48, 1),IR(1, 0),IR(106, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5431,IR(0, 0),IR(13602, 31)/* CooperativeMatrixConversionsNV */,IR(0, 0),IR(1, 0),IR(108, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5432,IR(0, 0),IR(13633, 41)/* CooperativeMatrixPerElementOperationsEXT */,IR(49, 1),IR(1, 0),IR(106, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5433,IR(0, 0),IR(13714, 36)/* CooperativeMatrixTensorAddressingNV */,IR(0, 0),IR(1, 0),IR(108, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5434,IR(0, 0),IR(13750, 30)/* CooperativeMatrixBlockLoadsNV */,IR(0, 0),IR(1, 0),IR(108, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5435,IR(0, 0),IR(13780, 28)/* CooperativeVectorTrainingNV */,IR(0, 0),IR(1, 0),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5437,IR(0, 0),IR(9183, 41)/* RayTracingClusterAccelerationStructureNV */,IR(0, 0),IR(61, 1),IR(31, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5438,IR(0, 0),IR(13808, 34)/* CooperativeMatrixGetCoordinateEXT */,IR(0, 0),IR(1, 0),IR(105, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5439,IR(0, 0),IR(13842, 19)/* TensorAddressingNV */,IR(0, 0),IR(1, 0),IR(109, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5447,IR(0, 0),IR(13861, 32)/* CooperativeMatrixDecodeVectorNV */,IR(0, 0),IR(107, 1),IR(110, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5568,IR(0, 0),IR(13893, 21)/* SubgroupShuffleINTEL */,IR(0, 0),IR(1, 0),IR(111, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5569,IR(0, 0),IR(13914, 27)/* SubgroupBufferBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(111, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5570,IR(0, 0),IR(13941, 26)/* SubgroupImageBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(111, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5579,IR(0, 0),IR(13967, 31)/* SubgroupImageMediaBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(112, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5582,IR(0, 0),IR(13998, 21)/* RoundToInfinityINTEL */,IR(0, 0),IR(1, 0),IR(113, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5583,IR(0, 0),IR(14019, 23)/* FloatingPointModeINTEL */,IR(0, 0),IR(1, 0),IR(113, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5584,IR(0, 0),IR(14042, 23)/* IntegerFunctions2INTEL */,IR(0, 0),IR(1, 0),IR(114, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5603,IR(0, 0),IR(14065, 22)/* FunctionPointersINTEL */,IR(0, 0),IR(1, 0),IR(115, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5604,IR(0, 0),IR(14087, 24)/* IndirectReferencesINTEL */,IR(0, 0),IR(1, 0),IR(115, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5606,IR(0, 0),IR(14111, 9)/* AsmINTEL */,IR(0, 0),IR(1, 0),IR(116, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5612,IR(0, 0),IR(14120, 23)/* AtomicFloat32MinMaxEXT */,IR(0, 0),IR(1, 0),IR(117, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5613,IR(0, 0),IR(14143, 23)/* AtomicFloat64MinMaxEXT */,IR(0, 0),IR(1, 0),IR(117, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5616,IR(0, 0),IR(14166, 23)/* AtomicFloat16MinMaxEXT */,IR(0, 0),IR(1, 0),IR(117, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5617,IR(0, 0),IR(14189, 19)/* VectorComputeINTEL */,IR(0, 0),IR(108, 1),IR(118, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5619,IR(0, 0),IR(14208, 15)/* VectorAnyINTEL */,IR(0, 0),IR(1, 0),IR(118, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5629,IR(0, 0),IR(14223, 16)/* ExpectAssumeKHR */,IR(0, 0),IR(1, 0),IR(119, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5696,IR(0, 0),IR(14239, 33)/* SubgroupAvcMotionEstimationINTEL */,IR(0, 0),IR(1, 0),IR(120, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5697,IR(0, 0),IR(14272, 38)/* SubgroupAvcMotionEstimationIntraINTEL */,IR(0, 0),IR(1, 0),IR(120, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5698,IR(0, 0),IR(14310, 39)/* SubgroupAvcMotionEstimationChromaINTEL */,IR(0, 0),IR(1, 0),IR(120, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5817,IR(0, 0),IR(14349, 25)/* VariableLengthArrayINTEL */,IR(0, 0),IR(1, 0),IR(121, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5821,IR(0, 0),IR(14374, 26)/* FunctionFloatControlINTEL */,IR(0, 0),IR(1, 0),IR(113, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5824,IR(0, 0),IR(14400, 27)/* FPGAMemoryAttributesALTERA */,IR(50, 1),IR(1, 0),IR(122, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5837,IR(0, 0),IR(14453, 20)/* FPFastMathModeINTEL */,IR(0, 0),IR(0, 1),IR(124, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5844,IR(0, 0),IR(14473, 33)/* ArbitraryPrecisionIntegersALTERA */,IR(51, 1),IR(1, 0),IR(125, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5845,IR(0, 0),IR(14538, 38)/* ArbitraryPrecisionFloatingPointALTERA */,IR(52, 1),IR(1, 0),IR(127, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5886,IR(0, 0),IR(14613, 30)/* UnstructuredLoopControlsINTEL */,IR(0, 0),IR(1, 0),IR(129, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5888,IR(0, 0),IR(14643, 23)/* FPGALoopControlsALTERA */,IR(53, 1),IR(1, 0),IR(130, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5892,IR(0, 0),IR(14688, 22)/* KernelAttributesINTEL */,IR(0, 0),IR(1, 0),IR(132, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5897,IR(0, 0),IR(14710, 26)/* FPGAKernelAttributesINTEL */,IR(0, 0),IR(1, 0),IR(132, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5898,IR(0, 0),IR(14736, 25)/* FPGAMemoryAccessesALTERA */,IR(54, 1),IR(1, 0),IR(133, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5904,IR(0, 0),IR(14785, 28)/* FPGAClusterAttributesALTERA */,IR(55, 1),IR(1, 0),IR(135, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5906,IR(0, 0),IR(14840, 15)/* LoopFuseALTERA */,IR(56, 1),IR(1, 0),IR(137, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5908,IR(0, 0),IR(14869, 21)/* FPGADSPControlALTERA */,IR(57, 1),IR(1, 0),IR(139, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5910,IR(0, 0),IR(14910, 26)/* MemoryAccessAliasingINTEL */,IR(0, 0),IR(1, 0),IR(141, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5916,IR(0, 0),IR(14936, 41)/* FPGAInvocationPipeliningAttributesALTERA */,IR(58, 1),IR(1, 0),IR(142, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5920,IR(0, 0),IR(15017, 25)/* FPGABufferLocationALTERA */,IR(59, 1),IR(1, 0),IR(144, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5922,IR(0, 0),IR(15066, 35)/* ArbitraryPrecisionFixedPointALTERA */,IR(60, 1),IR(1, 0),IR(146, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5935,IR(0, 0),IR(15135, 24)/* USMStorageClassesALTERA */,IR(61, 1),IR(1, 0),IR(148, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5939,IR(0, 0),IR(15182, 30)/* RuntimeAlignedAttributeALTERA */,IR(62, 1),IR(1, 0),IR(150, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5943,IR(0, 0),IR(15241, 14)/* IOPipesALTERA */,IR(63, 1),IR(1, 0),IR(152, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5945,IR(0, 0),IR(15268, 20)/* BlockingPipesALTERA */,IR(64, 1),IR(1, 0),IR(154, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5948,IR(0, 0),IR(15307, 14)/* FPGARegALTERA */,IR(65, 1),IR(1, 0),IR(156, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6016,IR(0, 0),IR(15334, 19)/* DotProductInputAll */,IR(66, 1),IR(1, 0),IR(158, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6017,IR(0, 0),IR(15375, 22)/* DotProductInput4x8Bit */,IR(67, 1),IR(109, 1),IR(158, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6018,IR(0, 0),IR(15422, 28)/* DotProductInput4x8BitPacked */,IR(68, 1),IR(1, 0),IR(158, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6019,IR(0, 0),IR(15481, 11)/* DotProduct */,IR(69, 1),IR(1, 0),IR(158, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6020,IR(0, 0),IR(9236, 15)/* RayCullMaskKHR */,IR(0, 0),IR(1, 0),IR(32, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6022,IR(0, 0),IR(10439, 21)/* CooperativeMatrixKHR */,IR(0, 0),IR(1, 0),IR(159, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6024,IR(0, 0),IR(15506, 24)/* ReplicatedCompositesEXT */,IR(0, 0),IR(1, 0),IR(160, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6025,IR(0, 0),IR(15530, 16)/* BitInstructions */,IR(0, 0),IR(1, 0),IR(161, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6026,IR(0, 0),IR(15546, 25)/* GroupNonUniformRotateKHR */,IR(0, 0),IR(77, 1),IR(162, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6029,IR(0, 0),IR(15571, 15)/* FloatControls2 */,IR(0, 0),IR(1, 0),IR(163, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6030,IR(0, 0),IR(15586, 7)/* FMAKHR */,IR(0, 0),IR(1, 0),IR(164, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6032,IR(0, 0),IR(15593, 42)/* RayTracingOpacityMicromapExecutionModeKHR */,IR(0, 0),IR(3, 1),IR(165, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6033,IR(0, 0),IR(15635, 20)/* AtomicFloat32AddEXT */,IR(0, 0),IR(1, 0),IR(166, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6034,IR(0, 0),IR(15655, 20)/* AtomicFloat64AddEXT */,IR(0, 0),IR(1, 0),IR(166, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6089,IR(0, 0),IR(15675, 20)/* LongCompositesINTEL */,IR(0, 0),IR(1, 0),IR(167, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6094,IR(0, 0),IR(15695, 11)/* OptNoneEXT */,IR(70, 1),IR(1, 0),IR(168, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6095,IR(0, 0),IR(15719, 20)/* AtomicFloat16AddEXT */,IR(0, 0),IR(1, 0),IR(170, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6114,IR(0, 0),IR(15739, 21)/* DebugInfoModuleINTEL */,IR(0, 0),IR(1, 0),IR(171, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6115,IR(0, 0),IR(15760, 24)/* BFloat16ConversionINTEL */,IR(0, 0),IR(1, 0),IR(172, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6141,IR(0, 0),IR(15784, 16)/* SplitBarrierEXT */,IR(71, 1),IR(1, 0),IR(173, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6144,IR(0, 0),IR(15818, 19)/* ArithmeticFenceEXT */,IR(0, 0),IR(1, 0),IR(175, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6150,IR(0, 0),IR(15837, 30)/* FPGAClusterAttributesV2ALTERA */,IR(72, 1),IR(110, 1),IR(135, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6161,IR(0, 0),IR(15896, 28)/* FPGAKernelAttributesv2INTEL */,IR(0, 0),IR(111, 1),IR(132, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6162,IR(0, 0),IR(15924, 19)/* TaskSequenceALTERA */,IR(73, 1),IR(1, 0),IR(176, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6169,IR(0, 0),IR(15961, 16)/* FPMaxErrorINTEL */,IR(0, 0),IR(1, 0),IR(178, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6171,IR(0, 0),IR(15977, 25)/* FPGALatencyControlALTERA */,IR(74, 1),IR(1, 0),IR(179, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6174,IR(0, 0),IR(16026, 29)/* FPGAArgumentInterfacesALTERA */,IR(75, 1),IR(1, 0),IR(181, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6187,IR(0, 0),IR(16083, 30)/* GlobalVariableHostAccessINTEL */,IR(0, 0),IR(1, 0),IR(183, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6189,IR(0, 0),IR(16113, 36)/* GlobalVariableFPGADecorationsALTERA */,IR(76, 1),IR(1, 0),IR(184, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6220,IR(0, 0),IR(16184, 28)/* SubgroupBufferPrefetchINTEL */,IR(0, 0),IR(1, 0),IR(186, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6228,IR(0, 0),IR(16212, 23)/* Subgroup2DBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(187, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6229,IR(0, 0),IR(16235, 30)/* Subgroup2DBlockTransformINTEL */,IR(0, 0),IR(112, 1),IR(187, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6230,IR(0, 0),IR(16265, 30)/* Subgroup2DBlockTransposeINTEL */,IR(0, 0),IR(112, 1),IR(187, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6236,IR(0, 0),IR(16295, 38)/* SubgroupMatrixMultiplyAccumulateINTEL */,IR(0, 0),IR(1, 0),IR(188, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6241,IR(0, 0),IR(16333, 28)/* TernaryBitwiseFunctionINTEL */,IR(0, 0),IR(1, 0),IR(189, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6243,IR(0, 0),IR(16361, 32)/* UntypedVariableLengthArrayINTEL */,IR(0, 0),IR(113, 2),IR(121, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6245,IR(0, 0),IR(16393, 21)/* SpecConditionalINTEL */,IR(0, 0),IR(1, 0),IR(190, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6246,IR(0, 0),IR(16414, 22)/* FunctionVariantsINTEL */,IR(0, 0),IR(115, 1),IR(190, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6257,IR(0, 0),IR(16436, 18)/* PredicatedIOINTEL */,IR(0, 0),IR(1, 0),IR(191, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6265,IR(0, 0),IR(16454, 23)/* RoundedDivideSqrtINTEL */,IR(0, 0),IR(1, 0),IR(192, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6400,IR(0, 0),IR(16477, 26)/* GroupUniformArithmeticKHR */,IR(0, 0),IR(1, 0),IR(193, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6425,IR(0, 0),IR(16503, 27)/* TensorFloat32RoundingINTEL */,IR(0, 0),IR(1, 0),IR(194, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6427,IR(0, 0),IR(16530, 25)/* MaskedGatherScatterINTEL */,IR(0, 0),IR(1, 0),IR(195, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6441,IR(0, 0),IR(16555, 19)/* CacheControlsINTEL */,IR(0, 0),IR(1, 0),IR(196, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6460,IR(0, 0),IR(16574, 20)/* RegisterLimitsINTEL */,IR(0, 0),IR(1, 0),IR(197, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6528,IR(0, 0),IR(16594, 20)/* BindlessImagesINTEL */,IR(0, 0),IR(1, 0),IR(198, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6912,IR(0, 0),IR(16614, 33)/* DotProductFloat16AccFloat32VALVE */,IR(0, 0),IR(116, 1),IR(199, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6913,IR(0, 0),IR(16647, 33)/* DotProductFloat16AccFloat16VALVE */,IR(0, 0),IR(116, 1),IR(199, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6914,IR(0, 0),IR(16680, 27)/* DotProductBFloat16AccVALVE */,IR(0, 0),IR(90, 1),IR(199, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6915,IR(0, 0),IR(16707, 32)/* DotProductFloat8AccFloat32VALVE */,IR(0, 0),IR(117, 1),IR(199, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {7041,IR(0, 0),IR(16739, 17)/* IntrinsicSAMSUNG */,IR(0, 0),IR(1, 0),IR(200, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {0,IR(0, 0),IR(16756, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(16768, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(16776, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {3,IR(0, 0),IR(16784, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(16790, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(16797, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(16808, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(16817, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(16830, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(16836, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(16846, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(16852, 15)/* ImportedModule */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {1,IR(0, 0),IR(16867, 20)/* ImportedDeclaration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {0,IR(0, 0),IR(16887, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(16892, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(16908, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(16922, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(16935, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(16947, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(16964, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(16976, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(16991, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(17004, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(17019, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(17037, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(17054, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(17075, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(17095, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(17115, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {16384,IR(0, 0),IR(17131, 16)/* FlagIsEnumClass */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {32768,IR(0, 0),IR(17147, 20)/* FlagTypePassByValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {65536,IR(0, 0),IR(17167, 24)/* FlagTypePassByReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(17191, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {1,IR(0, 0),IR(17197, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {2,IR(0, 0),IR(17202, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {3,IR(0, 1),IR(17241, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {4,IR(1, 2),IR(17252, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {5,IR(0, 0),IR(17261, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {6,IR(0, 0),IR(17266, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {7,IR(0, 0),IR(17273, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {8,IR(0, 1),IR(17284, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {9,IR(1, 2),IR(17291, 9)/* Fragment */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {0,IR(0, 0),IR(17300, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(17310, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(17323, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {3,IR(0, 0),IR(17336, 11)/* AtomicType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(17347, 10)/* Float16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1,IR(0, 0),IR(17357, 10)/* Float32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {2,IR(0, 0),IR(17367, 10)/* Float64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {3,IR(0, 0),IR(17377, 13)/* SignedInt8NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {4,IR(0, 0),IR(17390, 14)/* SignedInt16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {5,IR(0, 0),IR(17404, 14)/* SignedInt32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {6,IR(0, 0),IR(17418, 14)/* SignedInt64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {7,IR(0, 0),IR(17432, 15)/* UnsignedInt8NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {8,IR(0, 0),IR(17447, 16)/* UnsignedInt16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {9,IR(0, 0),IR(17463, 16)/* UnsignedInt32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {10,IR(0, 0),IR(17479, 16)/* UnsignedInt64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491000,IR(0, 0),IR(17495, 19)/* SignedInt8PackedNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491001,IR(0, 0),IR(17514, 21)/* UnsignedInt8PackedNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491002,IR(0, 0),IR(17535, 12)/* FloatE4M3NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491003,IR(0, 0),IR(17547, 12)/* FloatE5M2NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {0,IR(0, 0),IR(17559, 12)/* RowMajorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {1,IR(0, 0),IR(17571, 15)/* ColumnMajorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {4202,IR(0, 0),IR(17586, 25)/* RowBlockedInterleavedARM */,IR(0, 0),IR(118, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {4203,IR(0, 0),IR(17611, 28)/* ColumnBlockedInterleavedARM */,IR(0, 0),IR(118, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {0,IR(0, 0),IR(17639, 8)/* NoneKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {1,IR(0, 0),IR(17647, 27)/* MatrixASignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {2,IR(0, 0),IR(17674, 27)/* MatrixBSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {4,IR(0, 0),IR(17701, 27)/* MatrixCSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {8,IR(0, 0),IR(17728, 32)/* MatrixResultSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {16,IR(0, 0),IR(17760, 26)/* SaturatingAccumulationKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {1,IR(0, 0),IR(17786, 4)/* Row */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {2,IR(0, 0),IR(17790, 7)/* Column */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {4,IR(0, 0),IR(17797, 4)/* 2x2 */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {0,IR(0, 0),IR(17801, 11)/* MatrixAKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {1,IR(0, 0),IR(17812, 11)/* MatrixBKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {2,IR(0, 0),IR(17823, 21)/* MatrixAccumulatorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {0,IR(0, 0),IR(17844, 11)/* RowMajorNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {1,IR(0, 0),IR(17855, 14)/* ColumnMajorNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {2,IR(0, 0),IR(17869, 21)/* InferencingOptimalNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {3,IR(0, 0),IR(17890, 18)/* TrainingOptimalNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {0,IR(0, 0),IR(16756, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(16768, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(16776, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(16784, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(16790, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(16797, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(16808, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {8,IR(0, 0),IR(16817, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(16830, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(16836, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(16846, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(16887, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(16892, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(16908, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(16922, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(16935, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(16947, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(16964, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(16976, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(16991, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(17004, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(17019, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(17037, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(17054, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(17075, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(17095, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(17115, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(17191, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {1,IR(0, 0),IR(17197, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {2,IR(0, 0),IR(17202, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {3,IR(0, 1),IR(17241, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {4,IR(1, 2),IR(17252, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {5,IR(0, 0),IR(17261, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {6,IR(0, 0),IR(17266, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {7,IR(0, 0),IR(17273, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {8,IR(0, 1),IR(17284, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {0,IR(0, 0),IR(17300, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(17310, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(17323, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(17908, 17)/* RelaxedPrecision */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {1,IR(0, 1),IR(17925, 7)/* SpecId */,IR(0, 0),IR(119, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {2,IR(0, 0),IR(17932, 6)/* Block */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {3,IR(0, 0),IR(17938, 12)/* BufferBlock */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),SPV_SPIRV_VERSION_WORD(1,3)}, // SPV_OPERAND_TYPE_DECORATION
  {4,IR(0, 0),IR(17950, 9)/* RowMajor */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5,IR(0, 0),IR(17959, 9)/* ColMajor */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6,IR(0, 1),IR(17968, 12)/* ArrayStride */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {7,IR(0, 1),IR(17980, 13)/* MatrixStride */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {8,IR(0, 0),IR(17993, 11)/* GLSLShared */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {9,IR(0, 0),IR(18004, 11)/* GLSLPacked */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {10,IR(0, 0),IR(18015, 8)/* CPacked */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {11,IR(3, 1),IR(18049, 8)/* BuiltIn */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {13,IR(0, 0),IR(18057, 14)/* NoPerspective */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {14,IR(0, 0),IR(18071, 5)/* Flat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {15,IR(0, 0),IR(18076, 6)/* Patch */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {16,IR(0, 0),IR(18082, 9)/* Centroid */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {17,IR(0, 0),IR(18091, 7)/* Sample */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {18,IR(0, 0),IR(18098, 10)/* Invariant */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {19,IR(0, 0),IR(18108, 9)/* Restrict */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {20,IR(0, 0),IR(18117, 8)/* Aliased */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {21,IR(0, 0),IR(18125, 9)/* Volatile */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {22,IR(0, 0),IR(18134, 9)/* Constant */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {23,IR(0, 0),IR(18143, 9)/* Coherent */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {24,IR(0, 0),IR(18152, 12)/* NonWritable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {25,IR(0, 0),IR(18164, 12)/* NonReadable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {26,IR(0, 0),IR(18176, 8)/* Uniform */,IR(0, 0),IR(121, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {27,IR(4, 1),IR(18210, 10)/* UniformId */,IR(0, 0),IR(121, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {28,IR(0, 0),IR(18220, 20)/* SaturatedConversion */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {29,IR(0, 1),IR(18240, 7)/* Stream */,IR(0, 0),IR(123, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {30,IR(0, 1),IR(18247, 9)/* Location */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {31,IR(0, 1),IR(18256, 10)/* Component */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {32,IR(0, 1),IR(18266, 6)/* Index */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {33,IR(0, 1),IR(18272, 8)/* Binding */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {34,IR(0, 1),IR(18280, 14)/* DescriptorSet */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {35,IR(0, 1),IR(18294, 7)/* Offset */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {36,IR(0, 1),IR(18301, 10)/* XfbBuffer */,IR(0, 0),IR(124, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {37,IR(0, 1),IR(18311, 10)/* XfbStride */,IR(0, 0),IR(124, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {38,IR(5, 1),IR(18367, 14)/* FuncParamAttr */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {39,IR(6, 1),IR(18415, 15)/* FPRoundingMode */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {40,IR(7, 1),IR(18465, 15)/* FPFastMathMode */,IR(0, 0),IR(125, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {41,IR(8, 2),IR(18542, 18)/* LinkageAttributes */,IR(0, 0),IR(94, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {42,IR(0, 0),IR(18560, 14)/* NoContraction */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {43,IR(0, 1),IR(18574, 21)/* InputAttachmentIndex */,IR(0, 0),IR(98, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {44,IR(0, 1),IR(18595, 10)/* Alignment */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {45,IR(0, 1),IR(18605, 14)/* MaxByteOffset */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {46,IR(10, 1),IR(18639, 12)/* AlignmentId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {47,IR(10, 1),IR(18651, 16)/* MaxByteOffsetId */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4216,IR(0, 0),IR(18667, 44)/* SaturatedToLargestFloat8NormalConversionEXT */,IR(0, 0),IR(117, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4469,IR(0, 0),IR(18711, 13)/* NoSignedWrap */,IR(0, 0),IR(1, 0),IR(201, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4470,IR(0, 0),IR(18724, 15)/* NoUnsignedWrap */,IR(0, 0),IR(1, 0),IR(201, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4487,IR(0, 0),IR(18739, 18)/* WeightTextureQCOM */,IR(0, 0),IR(1, 0),IR(53, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4488,IR(0, 0),IR(18757, 22)/* BlockMatchTextureQCOM */,IR(0, 0),IR(1, 0),IR(53, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4499,IR(0, 0),IR(18779, 22)/* BlockMatchSamplerQCOM */,IR(0, 0),IR(1, 0),IR(56, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4999,IR(0, 0),IR(18801, 18)/* ExplicitInterpAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5019,IR(10, 1),IR(18819, 32)/* NodeSharesPayloadLimitsWithAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5020,IR(10, 1),IR(18851, 20)/* NodeMaxPayloadsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5078,IR(0, 0),IR(18871, 23)/* TrackFinishWritingAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5091,IR(10, 1),IR(18894, 20)/* PayloadNodeNameAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5098,IR(10, 1),IR(18914, 25)/* PayloadNodeBaseIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5099,IR(0, 0),IR(18939, 27)/* PayloadNodeSparseArrayAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5100,IR(10, 1),IR(18966, 25)/* PayloadNodeArraySizeAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5105,IR(0, 0),IR(18991, 28)/* PayloadDispatchIndirectAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5124,IR(10, 1),IR(19019, 17)/* ArrayStrideIdEXT */,IR(0, 0),IR(44, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5125,IR(10, 1),IR(19036, 12)/* OffsetIdEXT */,IR(0, 0),IR(44, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5145,IR(0, 0),IR(19048, 14)/* UTFEncodedKHR */,IR(0, 0),IR(127, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5248,IR(0, 0),IR(19062, 19)/* OverrideCoverageNV */,IR(0, 0),IR(128, 1),IR(76, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5250,IR(0, 0),IR(19081, 14)/* PassthroughNV */,IR(0, 0),IR(129, 1),IR(77, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5252,IR(0, 0),IR(19095, 19)/* ViewportRelativeNV */,IR(0, 0),IR(97, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5256,IR(0, 1),IR(19114, 28)/* SecondaryViewportRelativeNV */,IR(0, 0),IR(47, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5271,IR(0, 0),IR(19142, 16)/* PerPrimitiveEXT */,IR(77, 1),IR(130, 2),IR(202, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5272,IR(0, 0),IR(19173, 10)/* PerViewNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5273,IR(0, 0),IR(19183, 10)/* PerTaskNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5285,IR(0, 0),IR(19193, 13)/* PerVertexKHR */,IR(78, 1),IR(52, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5300,IR(0, 0),IR(19218, 11)/* NonUniform */,IR(79, 1),IR(100, 1),IR(87, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5355,IR(0, 0),IR(19243, 16)/* RestrictPointer */,IR(80, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5356,IR(0, 0),IR(19278, 15)/* AliasedPointer */,IR(81, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5358,IR(0, 1),IR(19311, 15)/* MemberOffsetNV */,IR(0, 0),IR(132, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5386,IR(0, 0),IR(19326, 30)/* HitObjectShaderRecordBufferNV */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5389,IR(0, 0),IR(19356, 31)/* HitObjectShaderRecordBufferEXT */,IR(0, 0),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5397,IR(0, 1),IR(19387, 7)/* BankNV */,IR(0, 0),IR(132, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5398,IR(0, 0),IR(19394, 18)/* BindlessSamplerNV */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5399,IR(0, 0),IR(19412, 16)/* BindlessImageNV */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5400,IR(0, 0),IR(19428, 15)/* BoundSamplerNV */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5401,IR(0, 0),IR(19443, 13)/* BoundImageNV */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5440,IR(0, 0),IR(19456, 30)/* CooperativeMatrixTransposeEXT */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5599,IR(0, 1),IR(19486, 14)/* SIMTCallINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5602,IR(0, 0),IR(19500, 26)/* ReferencedIndirectlyINTEL */,IR(0, 0),IR(138, 1),IR(115, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5607,IR(11, 1),IR(19526, 13)/* ClobberINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5608,IR(0, 0),IR(19539, 17)/* SideEffectsINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5624,IR(0, 0),IR(19556, 27)/* VectorComputeVariableINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5625,IR(0, 1),IR(19583, 21)/* FuncParamIOKindINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5626,IR(0, 0),IR(19604, 27)/* VectorComputeFunctionINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5627,IR(0, 0),IR(19631, 15)/* StackCallINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5628,IR(0, 1),IR(19646, 26)/* GlobalVariableOffsetINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5634,IR(10, 1),IR(19672, 14)/* CounterBuffer */,IR(82, 1),IR(1, 0),IR(204, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5635,IR(11, 1),IR(19710, 13)/* UserSemantic */,IR(83, 1),IR(1, 0),IR(204, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5636,IR(11, 1),IR(19742, 15)/* UserTypeGOOGLE */,IR(0, 0),IR(1, 0),IR(205, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5822,IR(12, 2),IR(19757, 26)/* FunctionRoundingModeINTEL */,IR(0, 0),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5823,IR(14, 2),IR(19814, 24)/* FunctionDenormModeINTEL */,IR(0, 0),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5825,IR(0, 0),IR(19838, 15)/* RegisterALTERA */,IR(84, 1),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5826,IR(11, 1),IR(19867, 13)/* MemoryALTERA */,IR(85, 1),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5827,IR(0, 1),IR(19892, 15)/* NumbanksALTERA */,IR(86, 1),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5828,IR(0, 1),IR(19921, 16)/* BankwidthALTERA */,IR(87, 1),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5829,IR(0, 1),IR(19952, 23)/* MaxPrivateCopiesALTERA */,IR(88, 1),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5830,IR(0, 0),IR(19997, 17)/* SinglepumpALTERA */,IR(89, 1),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5831,IR(0, 0),IR(20030, 17)/* DoublepumpALTERA */,IR(90, 1),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5832,IR(0, 1),IR(20063, 20)/* MaxReplicatesALTERA */,IR(91, 1),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5833,IR(0, 0),IR(20102, 21)/* SimpleDualPortALTERA */,IR(92, 1),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5834,IR(16, 2),IR(20143, 12)/* MergeALTERA */,IR(93, 1),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5835,IR(18, 1),IR(20208, 15)/* BankBitsALTERA */,IR(94, 1),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5836,IR(0, 1),IR(20237, 21)/* ForcePow2DepthALTERA */,IR(95, 1),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5883,IR(0, 1),IR(20278, 17)/* StridesizeALTERA */,IR(96, 1),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5884,IR(0, 1),IR(20311, 15)/* WordsizeALTERA */,IR(97, 1),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5885,IR(0, 0),IR(20340, 19)/* TrueDualPortALTERA */,IR(98, 1),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5899,IR(0, 0),IR(20377, 20)/* BurstCoalesceALTERA */,IR(99, 1),IR(142, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5900,IR(0, 1),IR(20416, 16)/* CacheSizeALTERA */,IR(100, 1),IR(142, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5901,IR(0, 0),IR(20447, 29)/* DontStaticallyCoalesceALTERA */,IR(101, 1),IR(142, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5902,IR(0, 1),IR(20504, 15)/* PrefetchALTERA */,IR(102, 1),IR(142, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5905,IR(0, 0),IR(20533, 18)/* StallEnableALTERA */,IR(103, 1),IR(110, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5907,IR(0, 0),IR(20568, 26)/* FuseLoopsInFunctionALTERA */,IR(104, 1),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5909,IR(1, 2),IR(20619, 20)/* MathOpDSPModeALTERA */,IR(105, 1),IR(144, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5914,IR(10, 1),IR(20658, 16)/* AliasScopeINTEL */,IR(0, 0),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5915,IR(10, 1),IR(20674, 13)/* NoAliasINTEL */,IR(0, 0),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5917,IR(0, 1),IR(20687, 25)/* InitiationIntervalALTERA */,IR(106, 1),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5918,IR(0, 1),IR(20736, 21)/* MaxConcurrencyALTERA */,IR(107, 1),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5919,IR(0, 1),IR(20777, 21)/* PipelineEnableALTERA */,IR(108, 1),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5921,IR(0, 1),IR(20818, 21)/* BufferLocationALTERA */,IR(109, 1),IR(147, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5944,IR(0, 1),IR(20859, 20)/* IOPipeStorageALTERA */,IR(110, 1),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6080,IR(19, 2),IR(20932, 31)/* FunctionFloatingPointModeINTEL */,IR(0, 0),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6085,IR(0, 0),IR(20963, 25)/* SingleElementVectorINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6087,IR(0, 0),IR(20988, 35)/* VectorComputeCallableFunctionINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6140,IR(0, 0),IR(21023, 18)/* MediaBlockIOINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6151,IR(0, 0),IR(21041, 16)/* StallFreeALTERA */,IR(111, 1),IR(149, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6170,IR(21, 1),IR(21103, 26)/* FPMaxErrorDecorationINTEL */,IR(0, 0),IR(150, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6172,IR(0, 1),IR(21129, 26)/* LatencyControlLabelALTERA */,IR(112, 1),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6173,IR(22, 3),IR(21180, 31)/* LatencyControlConstraintALTERA */,IR(113, 1),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6175,IR(0, 0),IR(21241, 28)/* ConduitKernelArgumentALTERA */,IR(114, 1),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6176,IR(0, 0),IR(21296, 32)/* RegisterMapKernelArgumentALTERA */,IR(115, 1),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6177,IR(0, 1),IR(21359, 34)/* MMHostInterfaceAddressWidthALTERA */,IR(116, 1),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6178,IR(0, 1),IR(21426, 31)/* MMHostInterfaceDataWidthALTERA */,IR(117, 1),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6179,IR(0, 1),IR(21487, 29)/* MMHostInterfaceLatencyALTERA */,IR(118, 1),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6180,IR(25, 1),IR(21578, 35)/* MMHostInterfaceReadWriteModeALTERA */,IR(119, 1),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6181,IR(0, 1),IR(21647, 30)/* MMHostInterfaceMaxBurstALTERA */,IR(120, 1),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6182,IR(0, 1),IR(21706, 33)/* MMHostInterfaceWaitRequestALTERA */,IR(121, 1),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6183,IR(0, 0),IR(21771, 27)/* StableKernelArgumentALTERA */,IR(122, 1),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6188,IR(26, 2),IR(21863, 16)/* HostAccessINTEL */,IR(0, 0),IR(153, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6190,IR(28, 1),IR(21926, 15)/* InitModeALTERA */,IR(123, 1),IR(154, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6191,IR(0, 1),IR(21955, 29)/* ImplementInRegisterMapALTERA */,IR(124, 1),IR(154, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6247,IR(10, 1),IR(22012, 17)/* ConditionalINTEL */,IR(0, 0),IR(115, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6442,IR(29, 2),IR(22065, 22)/* CacheControlLoadINTEL */,IR(0, 0),IR(155, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6443,IR(31, 2),IR(22124, 23)/* CacheControlStoreINTEL */,IR(0, 0),IR(155, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {7040,IR(0, 1),IR(16739, 17)/* IntrinsicSAMSUNG */,IR(0, 0),IR(156, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {0,IR(0, 0),IR(22147, 3)/* 1D */,IR(0, 0),IR(73, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {1,IR(0, 0),IR(22150, 3)/* 2D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {2,IR(0, 0),IR(22153, 3)/* 3D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {3,IR(0, 0),IR(22156, 5)/* Cube */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {4,IR(0, 0),IR(22161, 5)/* Rect */,IR(0, 0),IR(72, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {5,IR(0, 0),IR(22166, 7)/* Buffer */,IR(0, 0),IR(74, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {6,IR(0, 0),IR(22173, 12)/* SubpassData */,IR(0, 0),IR(98, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {4173,IR(0, 0),IR(22185, 17)/* TileImageDataEXT */,IR(0, 0),IR(157, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {0,IR(0, 1),IR(22202, 12)/* Invocations */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {1,IR(0, 0),IR(22214, 13)/* SpacingEqual */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {2,IR(0, 0),IR(22227, 22)/* SpacingFractionalEven */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {3,IR(0, 0),IR(22249, 21)/* SpacingFractionalOdd */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4,IR(0, 0),IR(22270, 14)/* VertexOrderCw */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5,IR(0, 0),IR(22284, 15)/* VertexOrderCcw */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6,IR(0, 0),IR(22299, 19)/* PixelCenterInteger */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {7,IR(0, 0),IR(22318, 16)/* OriginUpperLeft */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {8,IR(0, 0),IR(22334, 16)/* OriginLowerLeft */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {9,IR(0, 0),IR(22350, 19)/* EarlyFragmentTests */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {10,IR(0, 0),IR(22369, 10)/* PointMode */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {11,IR(0, 0),IR(22379, 4)/* Xfb */,IR(0, 0),IR(124, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {12,IR(0, 0),IR(22383, 15)/* DepthReplacing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {14,IR(0, 0),IR(22398, 13)/* DepthGreater */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {15,IR(0, 0),IR(22411, 10)/* DepthLess */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {16,IR(0, 0),IR(22421, 15)/* DepthUnchanged */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {17,IR(22, 3),IR(22436, 10)/* LocalSize */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {18,IR(22, 3),IR(22446, 14)/* LocalSizeHint */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {19,IR(0, 0),IR(22460, 12)/* InputPoints */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {20,IR(0, 0),IR(22472, 11)/* InputLines */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {21,IR(0, 0),IR(22483, 20)/* InputLinesAdjacency */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {22,IR(0, 0),IR(22503, 10)/* Triangles */,IR(0, 0),IR(12, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {23,IR(0, 0),IR(22513, 24)/* InputTrianglesAdjacency */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {24,IR(0, 0),IR(22537, 6)/* Quads */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {25,IR(0, 0),IR(22543, 9)/* Isolines */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {26,IR(0, 1),IR(22552, 15)/* OutputVertices */,IR(0, 0),IR(158, 4),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {27,IR(0, 0),IR(22567, 13)/* OutputPoints */,IR(0, 0),IR(162, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {28,IR(0, 0),IR(22580, 16)/* OutputLineStrip */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {29,IR(0, 0),IR(22596, 20)/* OutputTriangleStrip */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {30,IR(0, 1),IR(22616, 12)/* VecTypeHint */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {31,IR(0, 0),IR(22628, 15)/* ContractionOff */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {33,IR(0, 0),IR(22643, 12)/* Initializer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {34,IR(0, 0),IR(22655, 10)/* Finalizer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {35,IR(0, 1),IR(6667, 13)/* SubgroupSize */,IR(0, 0),IR(165, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {36,IR(0, 1),IR(22665, 22)/* SubgroupsPerWorkgroup */,IR(0, 0),IR(165, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {37,IR(10, 1),IR(22687, 24)/* SubgroupsPerWorkgroupId */,IR(0, 0),IR(165, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {38,IR(33, 3),IR(22711, 12)/* LocalSizeId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {39,IR(33, 3),IR(22723, 16)/* LocalSizeHintId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4169,IR(0, 0),IR(22739, 34)/* NonCoherentColorAttachmentReadEXT */,IR(0, 0),IR(157, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4170,IR(0, 0),IR(22773, 34)/* NonCoherentDepthAttachmentReadEXT */,IR(0, 0),IR(166, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4171,IR(0, 0),IR(22807, 36)/* NonCoherentStencilAttachmentReadEXT */,IR(0, 0),IR(167, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4421,IR(0, 0),IR(22843, 30)/* SubgroupUniformControlFlowKHR */,IR(0, 0),IR(3, 1),IR(206, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4446,IR(0, 0),IR(22873, 18)/* PostDepthCoverage */,IR(0, 0),IR(168, 1),IR(46, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4459,IR(0, 1),IR(10985, 15)/* DenormPreserve */,IR(0, 0),IR(169, 1),IR(48, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4460,IR(0, 1),IR(11000, 18)/* DenormFlushToZero */,IR(0, 0),IR(170, 1),IR(48, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4461,IR(0, 1),IR(11018, 25)/* SignedZeroInfNanPreserve */,IR(0, 0),IR(171, 1),IR(48, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4462,IR(0, 1),IR(11043, 16)/* RoundingModeRTE */,IR(0, 0),IR(172, 1),IR(48, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4463,IR(0, 1),IR(11059, 16)/* RoundingModeRTZ */,IR(0, 0),IR(173, 1),IR(48, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4489,IR(0, 0),IR(22891, 34)/* NonCoherentTileAttachmentReadQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4490,IR(22, 3),IR(22925, 20)/* TileShadingRateQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4507,IR(0, 0),IR(22945, 21)/* SubgroupSizeHalfQCOM */,IR(0, 0),IR(174, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4508,IR(0, 0),IR(22966, 21)/* SubgroupSizeFullQCOM */,IR(0, 0),IR(174, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5017,IR(0, 0),IR(22987, 29)/* EarlyAndLateFragmentTestsAMD */,IR(0, 0),IR(3, 1),IR(207, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5027,IR(0, 0),IR(23016, 23)/* StencilRefReplacingEXT */,IR(0, 0),IR(42, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5069,IR(0, 0),IR(23039, 15)/* CoalescingAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5070,IR(10, 1),IR(23054, 15)/* IsApiEntryAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5071,IR(10, 1),IR(23069, 21)/* MaxNodeRecursionAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5072,IR(33, 3),IR(23090, 24)/* StaticNumWorkgroupsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5073,IR(10, 1),IR(7560, 16)/* ShaderIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5077,IR(33, 3),IR(23114, 21)/* MaxNumWorkgroupsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5079,IR(0, 0),IR(23135, 28)/* StencilRefUnchangedFrontAMD */,IR(0, 0),IR(42, 1),IR(208, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5080,IR(0, 0),IR(23163, 26)/* StencilRefGreaterFrontAMD */,IR(0, 0),IR(42, 1),IR(208, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5081,IR(0, 0),IR(23189, 23)/* StencilRefLessFrontAMD */,IR(0, 0),IR(42, 1),IR(208, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5082,IR(0, 0),IR(23212, 27)/* StencilRefUnchangedBackAMD */,IR(0, 0),IR(42, 1),IR(208, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5083,IR(0, 0),IR(23239, 25)/* StencilRefGreaterBackAMD */,IR(0, 0),IR(42, 1),IR(208, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5084,IR(0, 0),IR(23264, 22)/* StencilRefLessBackAMD */,IR(0, 0),IR(42, 1),IR(208, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5088,IR(0, 0),IR(23286, 19)/* QuadDerivativesKHR */,IR(0, 0),IR(175, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5089,IR(0, 0),IR(23305, 20)/* RequireFullQuadsKHR */,IR(0, 0),IR(175, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5102,IR(36, 2),IR(23325, 20)/* SharesInputWithAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5157,IR(0, 0),IR(23345, 20)/* ArithmeticPoisonKHR */,IR(0, 0),IR(176, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5269,IR(0, 0),IR(23365, 15)/* OutputLinesEXT */,IR(125, 1),IR(130, 2),IR(202, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5270,IR(0, 1),IR(23394, 20)/* OutputPrimitivesEXT */,IR(126, 1),IR(130, 2),IR(202, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5289,IR(0, 0),IR(23433, 24)/* DerivativeGroupQuadsKHR */,IR(127, 1),IR(177, 1),IR(83, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5290,IR(0, 0),IR(23480, 25)/* DerivativeGroupLinearKHR */,IR(128, 1),IR(178, 1),IR(83, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5298,IR(0, 0),IR(23529, 19)/* OutputTrianglesEXT */,IR(129, 1),IR(130, 2),IR(202, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5366,IR(0, 0),IR(23566, 25)/* PixelInterlockOrderedEXT */,IR(0, 0),IR(179, 1),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5367,IR(0, 0),IR(23591, 27)/* PixelInterlockUnorderedEXT */,IR(0, 0),IR(179, 1),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5368,IR(0, 0),IR(23618, 26)/* SampleInterlockOrderedEXT */,IR(0, 0),IR(180, 1),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5369,IR(0, 0),IR(23644, 28)/* SampleInterlockUnorderedEXT */,IR(0, 0),IR(180, 1),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5370,IR(0, 0),IR(23672, 31)/* ShadingRateInterlockOrderedEXT */,IR(0, 0),IR(181, 1),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5371,IR(0, 0),IR(23703, 33)/* ShadingRateInterlockUnorderedEXT */,IR(0, 0),IR(181, 1),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5427,IR(0, 0),IR(13486, 23)/* Shader64BitIndexingEXT */,IR(0, 0),IR(182, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5618,IR(0, 1),IR(23736, 27)/* SharedLocalMemorySizeINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5620,IR(0, 1),IR(23763, 21)/* RoundingModeRTPINTEL */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5621,IR(0, 1),IR(23784, 21)/* RoundingModeRTNINTEL */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5622,IR(0, 1),IR(23805, 26)/* FloatingPointModeALTINTEL */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5623,IR(0, 1),IR(23831, 27)/* FloatingPointModeIEEEINTEL */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5893,IR(22, 3),IR(23858, 22)/* MaxWorkgroupSizeINTEL */,IR(0, 0),IR(184, 1),IR(132, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5894,IR(0, 1),IR(23880, 16)/* MaxWorkDimINTEL */,IR(0, 0),IR(184, 1),IR(132, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5895,IR(0, 0),IR(23896, 20)/* NoGlobalOffsetINTEL */,IR(0, 0),IR(184, 1),IR(132, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5896,IR(0, 1),IR(23916, 22)/* NumSIMDWorkitemsINTEL */,IR(0, 0),IR(111, 1),IR(132, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5903,IR(0, 1),IR(23938, 28)/* SchedulerTargetFmaxMhzINTEL */,IR(0, 0),IR(111, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6023,IR(0, 0),IR(23966, 24)/* MaximallyReconvergesKHR */,IR(0, 0),IR(3, 1),IR(210, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6028,IR(36, 2),IR(23990, 18)/* FPFastMathDefault */,IR(0, 0),IR(185, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6031,IR(10, 1),IR(24008, 21)/* OpacityMicromapIdKHR */,IR(0, 0),IR(186, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6154,IR(0, 1),IR(24029, 24)/* StreamingInterfaceINTEL */,IR(0, 0),IR(111, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6160,IR(0, 1),IR(24053, 26)/* RegisterMapInterfaceINTEL */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6417,IR(0, 1),IR(24079, 23)/* NamedBarrierCountINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6461,IR(0, 1),IR(24102, 22)/* MaximumRegistersINTEL */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6462,IR(10, 1),IR(24124, 24)/* MaximumRegistersIdINTEL */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6463,IR(38, 1),IR(24199, 27)/* NamedMaximumRegistersINTEL */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {0,IR(0, 0),IR(24226, 7)/* Vertex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {1,IR(0, 0),IR(24233, 20)/* TessellationControl */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {2,IR(0, 0),IR(24253, 23)/* TessellationEvaluation */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {3,IR(0, 0),IR(6148, 9)/* Geometry */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {4,IR(0, 0),IR(17291, 9)/* Fragment */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5,IR(0, 0),IR(24276, 10)/* GLCompute */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {6,IR(0, 0),IR(5915, 7)/* Kernel */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5267,IR(0, 0),IR(24286, 7)/* TaskNV */,IR(0, 0),IR(51, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5268,IR(0, 0),IR(24293, 7)/* MeshNV */,IR(0, 0),IR(51, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5313,IR(0, 0),IR(24300, 17)/* RayGenerationKHR */,IR(130, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5314,IR(0, 0),IR(24333, 16)/* IntersectionKHR */,IR(131, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5315,IR(0, 0),IR(24364, 10)/* AnyHitKHR */,IR(132, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5316,IR(0, 0),IR(24383, 14)/* ClosestHitKHR */,IR(133, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5317,IR(0, 0),IR(24410, 8)/* MissKHR */,IR(134, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5318,IR(0, 0),IR(24425, 12)/* CallableKHR */,IR(135, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5364,IR(0, 0),IR(24448, 8)/* TaskEXT */,IR(0, 0),IR(54, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5365,IR(0, 0),IR(24456, 8)/* MeshEXT */,IR(0, 0),IR(54, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {0,IR(0, 0),IR(24464, 9)/* Preserve */,IR(0, 0),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPDENORM_MODE
  {1,IR(0, 0),IR(24473, 12)/* FlushToZero */,IR(0, 0),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPDENORM_MODE
  {0,IR(0, 0),IR(24485, 12)/* BFloat16KHR */,IR(0, 0),IR(90, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {4214,IR(0, 0),IR(24497, 14)/* Float8E4M3EXT */,IR(0, 0),IR(117, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {4215,IR(0, 0),IR(24511, 14)/* Float8E5M2EXT */,IR(0, 0),IR(117, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {4223,IR(0, 0),IR(24525, 14)/* Float6E2M3EXT */,IR(0, 0),IR(189, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {4224,IR(0, 0),IR(24539, 14)/* Float6E3M2EXT */,IR(0, 0),IR(189, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {4225,IR(0, 0),IR(24553, 14)/* Float4E2M1EXT */,IR(0, 0),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {4226,IR(0, 0),IR(10480, 22)/* Float8UnsignedE8M0EXT */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {4227,IR(0, 0),IR(10502, 10)/* MXInt8EXT */,IR(0, 0),IR(192, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {0,IR(0, 0),IR(24567, 5)/* IEEE */,IR(0, 0),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPOPERATION_MODE
  {1,IR(0, 0),IR(24572, 4)/* ALT */,IR(0, 0),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPOPERATION_MODE
  {0,IR(0, 0),IR(16887, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {1,IR(0, 0),IR(24576, 7)/* NotNaN */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {2,IR(0, 0),IR(24583, 7)/* NotInf */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {4,IR(0, 0),IR(24590, 4)/* NSZ */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {8,IR(0, 0),IR(24594, 11)/* AllowRecip */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {16,IR(0, 0),IR(24605, 5)/* Fast */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {65536,IR(0, 0),IR(24610, 14)/* AllowContract */,IR(136, 1),IR(193, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {131072,IR(0, 0),IR(24647, 13)/* AllowReassoc */,IR(137, 1),IR(193, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {262144,IR(0, 0),IR(24678, 15)/* AllowTransform */,IR(0, 0),IR(185, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {0,IR(0, 0),IR(24693, 4)/* RTE */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {1,IR(0, 0),IR(24697, 4)/* RTZ */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {2,IR(0, 0),IR(24701, 4)/* RTP */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {3,IR(0, 0),IR(24705, 4)/* RTN */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {1,IR(0, 0),IR(24709, 16)/* Vertical2Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {2,IR(0, 0),IR(24725, 16)/* Vertical4Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {4,IR(0, 0),IR(24741, 18)/* Horizontal2Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {8,IR(0, 0),IR(24759, 18)/* Horizontal4Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {0,IR(0, 0),IR(16887, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {1,IR(0, 0),IR(24777, 7)/* Inline */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {2,IR(0, 0),IR(24784, 11)/* DontInline */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {4,IR(0, 0),IR(24795, 5)/* Pure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {8,IR(0, 0),IR(24800, 6)/* Const */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {65536,IR(0, 0),IR(15695, 11)/* OptNoneEXT */,IR(70, 1),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {0,IR(0, 0),IR(24806, 5)/* Zext */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {1,IR(0, 0),IR(24811, 5)/* Sext */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {2,IR(0, 0),IR(24816, 6)/* ByVal */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {3,IR(0, 0),IR(24822, 5)/* Sret */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {4,IR(0, 0),IR(24827, 8)/* NoAlias */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {5,IR(0, 0),IR(24835, 10)/* NoCapture */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {6,IR(0, 0),IR(24845, 8)/* NoWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {7,IR(0, 0),IR(24853, 12)/* NoReadWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {5940,IR(0, 0),IR(24865, 21)/* RuntimeAlignedALTERA */,IR(138, 1),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {0,IR(0, 0),IR(24906, 14)/* Gather4x1QCOM */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GATHER_MODES
  {1,IR(0, 0),IR(24920, 12)/* GatherDQCOM */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GATHER_MODES
  {2,IR(0, 0),IR(24932, 13)/* GatherH2QCOM */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GATHER_MODES
  {3,IR(0, 0),IR(24945, 13)/* GatherV2QCOM */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GATHER_MODES
  {0,IR(0, 0),IR(24958, 7)/* Reduce */,IR(0, 0),IR(197, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {1,IR(0, 0),IR(24965, 14)/* InclusiveScan */,IR(0, 0),IR(197, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {2,IR(0, 0),IR(24979, 14)/* ExclusiveScan */,IR(0, 0),IR(197, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {3,IR(0, 0),IR(24993, 16)/* ClusteredReduce */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {6,IR(0, 0),IR(25009, 21)/* PartitionedReduceEXT */,IR(139, 1),IR(201, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {7,IR(0, 0),IR(25050, 28)/* PartitionedInclusiveScanEXT */,IR(140, 1),IR(201, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {8,IR(0, 0),IR(25105, 28)/* PartitionedExclusiveScanEXT */,IR(141, 1),IR(201, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {0,IR(0, 0),IR(25160, 10)/* NoneINTEL */,IR(0, 0),IR(153, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {1,IR(0, 0),IR(25170, 10)/* ReadINTEL */,IR(0, 0),IR(153, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {2,IR(0, 0),IR(25180, 11)/* WriteINTEL */,IR(0, 0),IR(153, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {3,IR(0, 0),IR(25191, 15)/* ReadWriteINTEL */,IR(0, 0),IR(153, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {0,IR(0, 0),IR(16887, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {1,IR(10, 1),IR(25206, 5)/* Bias */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {2,IR(10, 1),IR(25211, 4)/* Lod */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {4,IR(36, 2),IR(25215, 5)/* Grad */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {8,IR(10, 1),IR(25220, 12)/* ConstOffset */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {16,IR(10, 1),IR(18294, 7)/* Offset */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {32,IR(10, 1),IR(25232, 13)/* ConstOffsets */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {64,IR(10, 1),IR(18091, 7)/* Sample */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {128,IR(10, 1),IR(9748, 7)/* MinLod */,IR(0, 0),IR(203, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {256,IR(4, 1),IR(25245, 19)/* MakeTexelAvailable */,IR(142, 1),IR(204, 1),IR(89, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {512,IR(4, 1),IR(25286, 17)/* MakeTexelVisible */,IR(143, 1),IR(204, 1),IR(89, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {1024,IR(0, 0),IR(25323, 16)/* NonPrivateTexel */,IR(144, 1),IR(204, 1),IR(89, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {2048,IR(0, 0),IR(25358, 14)/* VolatileTexel */,IR(145, 1),IR(204, 1),IR(89, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {4096,IR(0, 0),IR(25389, 11)/* SignExtend */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {8192,IR(0, 0),IR(25400, 11)/* ZeroExtend */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {16384,IR(0, 0),IR(25411, 12)/* Nontemporal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {65536,IR(10, 1),IR(25423, 8)/* Offsets */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {0,IR(0, 0),IR(25431, 10)/* SnormInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {1,IR(0, 0),IR(25441, 11)/* SnormInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {2,IR(0, 0),IR(25452, 10)/* UnormInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {3,IR(0, 0),IR(25462, 11)/* UnormInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {4,IR(0, 0),IR(25473, 14)/* UnormShort565 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {5,IR(0, 0),IR(25487, 14)/* UnormShort555 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {6,IR(0, 0),IR(25501, 15)/* UnormInt101010 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {7,IR(0, 0),IR(25516, 11)/* SignedInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {8,IR(0, 0),IR(25527, 12)/* SignedInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {9,IR(0, 0),IR(25539, 12)/* SignedInt32 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {10,IR(0, 0),IR(25551, 13)/* UnsignedInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {11,IR(0, 0),IR(25564, 14)/* UnsignedInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {12,IR(0, 0),IR(25578, 14)/* UnsignedInt32 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {13,IR(0, 0),IR(25592, 10)/* HalfFloat */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {14,IR(0, 0),IR(16784, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {15,IR(0, 0),IR(25602, 11)/* UnormInt24 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {16,IR(0, 0),IR(25613, 17)/* UnormInt101010_2 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {17,IR(0, 0),IR(25630, 16)/* UnormInt10X6EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {19,IR(0, 0),IR(25646, 20)/* UnsignedIntRaw10EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {20,IR(0, 0),IR(25666, 20)/* UnsignedIntRaw12EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {21,IR(0, 0),IR(25686, 20)/* UnormInt2_101010EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {22,IR(0, 0),IR(25706, 19)/* UnsignedInt10X6EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {23,IR(0, 0),IR(25725, 19)/* UnsignedInt12X4EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {24,IR(0, 0),IR(25744, 19)/* UnsignedInt14X2EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {25,IR(0, 0),IR(25763, 16)/* UnormInt12X4EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {26,IR(0, 0),IR(25779, 16)/* UnormInt14X2EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {0,IR(0, 0),IR(25795, 2)/* R */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {1,IR(0, 0),IR(25797, 2)/* A */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {2,IR(0, 0),IR(25799, 3)/* RG */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {3,IR(0, 0),IR(25802, 3)/* RA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {4,IR(0, 0),IR(25805, 4)/* RGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {5,IR(0, 0),IR(25809, 5)/* RGBA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {6,IR(0, 0),IR(25814, 5)/* BGRA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {7,IR(0, 0),IR(25819, 5)/* ARGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {8,IR(0, 0),IR(25824, 10)/* Intensity */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {9,IR(0, 0),IR(25834, 10)/* Luminance */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {10,IR(0, 0),IR(25844, 3)/* Rx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {11,IR(0, 0),IR(25847, 4)/* RGx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {12,IR(0, 0),IR(25851, 5)/* RGBx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {13,IR(0, 0),IR(25856, 6)/* Depth */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {14,IR(0, 0),IR(25862, 13)/* DepthStencil */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {15,IR(0, 0),IR(25875, 5)/* sRGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {16,IR(0, 0),IR(25880, 6)/* sRGBx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {17,IR(0, 0),IR(25886, 6)/* sRGBA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {18,IR(0, 0),IR(25892, 6)/* sBGRA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {19,IR(0, 0),IR(25898, 5)/* ABGR */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {0,IR(0, 0),IR(25903, 28)/* InitOnDeviceReprogramALTERA */,IR(146, 1),IR(154, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {1,IR(0, 0),IR(25958, 24)/* InitOnDeviceResetALTERA */,IR(147, 1),IR(154, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {0,IR(0, 0),IR(26005, 7)/* NoWait */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {1,IR(0, 0),IR(26012, 11)/* WaitKernel */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {2,IR(0, 0),IR(26023, 14)/* WaitWorkGroup */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {0,IR(0, 0),IR(16887, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {1,IR(0, 0),IR(26037, 12)/* CmdExecTime */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {0,IR(0, 0),IR(16887, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {1,IR(0, 0),IR(26049, 13)/* MayUsePrintf */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {0,IR(0, 0),IR(26062, 7)/* Export */,IR(0, 0),IR(94, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {1,IR(0, 0),IR(26069, 7)/* Import */,IR(0, 0),IR(94, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {2,IR(0, 0),IR(26076, 12)/* LinkOnceODR */,IR(0, 0),IR(94, 1),IR(211, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {3,IR(0, 0),IR(26088, 8)/* WeakAMD */,IR(0, 0),IR(205, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {0,IR(0, 0),IR(26096, 14)/* UncachedINTEL */,IR(0, 0),IR(155, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {1,IR(0, 0),IR(26110, 12)/* CachedINTEL */,IR(0, 0),IR(155, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {2,IR(0, 0),IR(26122, 15)/* StreamingINTEL */,IR(0, 0),IR(155, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {3,IR(0, 0),IR(26137, 25)/* InvalidateAfterReadINTEL */,IR(0, 0),IR(155, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {4,IR(0, 0),IR(26162, 17)/* ConstCachedINTEL */,IR(0, 0),IR(155, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {0,IR(0, 0),IR(16887, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {1,IR(0, 0),IR(26179, 7)/* Unroll */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {2,IR(0, 0),IR(26186, 11)/* DontUnroll */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {4,IR(0, 0),IR(26197, 19)/* DependencyInfinite */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {8,IR(0, 1),IR(26216, 17)/* DependencyLength */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {16,IR(0, 1),IR(26233, 14)/* MinIterations */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {32,IR(0, 1),IR(26247, 14)/* MaxIterations */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {64,IR(0, 1),IR(26261, 18)/* IterationMultiple */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {128,IR(0, 1),IR(26279, 10)/* PeelCount */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {256,IR(0, 1),IR(26289, 13)/* PartialCount */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {65536,IR(0, 1),IR(20687, 25)/* InitiationIntervalALTERA */,IR(106, 1),IR(206, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {131072,IR(0, 1),IR(20736, 21)/* MaxConcurrencyALTERA */,IR(107, 1),IR(206, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {262144,IR(0, 1),IR(26302, 22)/* DependencyArrayALTERA */,IR(148, 1),IR(206, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {524288,IR(0, 1),IR(20777, 21)/* PipelineEnableALTERA */,IR(108, 1),IR(206, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {1048576,IR(0, 1),IR(26345, 19)/* LoopCoalesceALTERA */,IR(149, 1),IR(206, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {2097152,IR(0, 1),IR(26382, 22)/* MaxInterleavingALTERA */,IR(150, 1),IR(206, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {4194304,IR(0, 1),IR(26425, 27)/* SpeculatedIterationsALTERA */,IR(151, 1),IR(206, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {8388608,IR(0, 0),IR(26478, 15)/* NoFusionALTERA */,IR(152, 1),IR(206, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {16777216,IR(0, 1),IR(26507, 16)/* LoopCountALTERA */,IR(153, 1),IR(206, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {33554432,IR(0, 1),IR(26538, 27)/* MaxReinvocationDelayALTERA */,IR(154, 1),IR(206, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {268435456,IR(0, 1),IR(11321, 23)/* MultipleWaitQueuesQCOM */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {0,IR(0, 0),IR(16887, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {1,IR(0, 0),IR(26591, 29)/* MatrixASignedComponentsINTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {2,IR(0, 0),IR(26620, 29)/* MatrixBSignedComponentsINTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {4,IR(0, 0),IR(26649, 21)/* MatrixCBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {8,IR(0, 0),IR(26670, 26)/* MatrixResultBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {16,IR(0, 0),IR(26696, 23)/* MatrixAPackedInt8INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {32,IR(0, 0),IR(26719, 23)/* MatrixBPackedInt8INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {64,IR(0, 0),IR(26742, 23)/* MatrixAPackedInt4INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {128,IR(0, 0),IR(26765, 23)/* MatrixBPackedInt4INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {256,IR(0, 0),IR(26788, 17)/* MatrixATF32INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {512,IR(0, 0),IR(26805, 17)/* MatrixBTF32INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {1024,IR(0, 0),IR(26822, 26)/* MatrixAPackedFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {2048,IR(0, 0),IR(26848, 26)/* MatrixBPackedFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {4096,IR(0, 0),IR(26874, 27)/* MatrixAPackedBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {8192,IR(0, 0),IR(26901, 27)/* MatrixBPackedBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {0,IR(0, 0),IR(16887, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {1,IR(0, 0),IR(18125, 9)/* Volatile */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {2,IR(0, 1),IR(26928, 8)/* Aligned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {4,IR(0, 0),IR(25411, 12)/* Nontemporal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {8,IR(4, 1),IR(26936, 21)/* MakePointerAvailable */,IR(155, 1),IR(204, 1),IR(89, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {16,IR(4, 1),IR(26981, 19)/* MakePointerVisible */,IR(156, 1),IR(204, 1),IR(89, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {32,IR(0, 0),IR(27022, 18)/* NonPrivatePointer */,IR(157, 1),IR(204, 1),IR(89, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {65536,IR(10, 1),IR(27061, 20)/* AliasScopeINTELMask */,IR(0, 0),IR(145, 1),IR(141, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {131072,IR(10, 1),IR(27081, 17)/* NoAliasINTELMask */,IR(0, 0),IR(145, 1),IR(141, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {0,IR(0, 0),IR(27098, 7)/* Simple */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {1,IR(0, 0),IR(27105, 8)/* GLSL450 */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {2,IR(0, 0),IR(27113, 7)/* OpenCL */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {3,IR(0, 0),IR(27120, 7)/* Vulkan */,IR(158, 1),IR(204, 1),IR(89, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {0,IR(0, 0),IR(27137, 8)/* Relaxed */,IR(159, 1),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {2,IR(0, 0),IR(27145, 8)/* Acquire */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {4,IR(0, 0),IR(27153, 8)/* Release */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {8,IR(0, 0),IR(27161, 15)/* AcquireRelease */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {16,IR(0, 0),IR(27176, 23)/* SequentiallyConsistent */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {64,IR(0, 0),IR(27199, 14)/* UniformMemory */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {128,IR(0, 0),IR(27213, 15)/* SubgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {256,IR(0, 0),IR(27228, 16)/* WorkgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {512,IR(0, 0),IR(27244, 21)/* CrossWorkgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {1024,IR(0, 0),IR(27265, 20)/* AtomicCounterMemory */,IR(0, 0),IR(83, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {2048,IR(0, 0),IR(27285, 12)/* ImageMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {4096,IR(0, 0),IR(27297, 13)/* OutputMemory */,IR(160, 1),IR(204, 1),IR(89, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {8192,IR(0, 0),IR(27326, 14)/* MakeAvailable */,IR(161, 1),IR(204, 1),IR(89, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {16384,IR(0, 0),IR(27357, 12)/* MakeVisible */,IR(162, 1),IR(204, 1),IR(89, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {32768,IR(0, 0),IR(18125, 9)/* Volatile */,IR(0, 0),IR(204, 1),IR(89, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {0,IR(0, 0),IR(27384, 10)/* AutoINTEL */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS
  {0,IR(0, 0),IR(27394, 5)/* WRAP */,IR(0, 0),IR(207, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {1,IR(0, 0),IR(27399, 4)/* SAT */,IR(0, 0),IR(207, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {2,IR(0, 0),IR(27403, 9)/* SAT_ZERO */,IR(0, 0),IR(207, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {3,IR(0, 0),IR(27412, 8)/* SAT_SYM */,IR(0, 0),IR(207, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {0,IR(0, 0),IR(27420, 25)/* PackedVectorFormat4x8Bit */,IR(163, 1),IR(1, 0),IR(158, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {0,IR(0, 0),IR(27473, 4)/* TRN */,IR(0, 0),IR(207, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {1,IR(0, 0),IR(27477, 9)/* TRN_ZERO */,IR(0, 0),IR(207, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {2,IR(0, 0),IR(27486, 4)/* RND */,IR(0, 0),IR(207, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {3,IR(0, 0),IR(27490, 9)/* RND_ZERO */,IR(0, 0),IR(207, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {4,IR(0, 0),IR(27499, 8)/* RND_INF */,IR(0, 0),IR(207, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {5,IR(0, 0),IR(27507, 12)/* RND_MIN_INF */,IR(0, 0),IR(207, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {6,IR(0, 0),IR(27519, 9)/* RND_CONV */,IR(0, 0),IR(207, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {7,IR(0, 0),IR(27528, 13)/* RND_CONV_ODD */,IR(0, 0),IR(207, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {0,IR(0, 0),IR(16887, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {1,IR(0, 0),IR(27541, 25)/* RobustnessPerComponentNV */,IR(0, 0),IR(208, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {2,IR(0, 0),IR(27566, 23)/* RobustnessPerElementNV */,IR(0, 0),IR(208, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {0,IR(0, 0),IR(17639, 8)/* NoneKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {1,IR(0, 0),IR(27589, 10)/* OpaqueKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {2,IR(0, 0),IR(27599, 12)/* NoOpaqueKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {4,IR(0, 0),IR(27611, 23)/* TerminateOnFirstHitKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {8,IR(0, 0),IR(27634, 24)/* SkipClosestHitShaderKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {16,IR(0, 0),IR(27658, 27)/* CullBackFacingTrianglesKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {32,IR(0, 0),IR(27685, 28)/* CullFrontFacingTrianglesKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {64,IR(0, 0),IR(27713, 14)/* CullOpaqueKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {128,IR(0, 0),IR(27727, 16)/* CullNoOpaqueKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {256,IR(0, 0),IR(27743, 17)/* SkipTrianglesKHR */,IR(164, 1),IR(209, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {512,IR(0, 0),IR(27784, 13)/* SkipAABBsKHR */,IR(0, 0),IR(209, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {1024,IR(0, 0),IR(27797, 30)/* ForceOpacityMicromap2StateKHR */,IR(165, 1),IR(210, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {0,IR(0, 0),IR(27857, 41)/* RayQueryCandidateIntersectionTriangleKHR */,IR(0, 0),IR(211, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {1,IR(0, 0),IR(27898, 37)/* RayQueryCandidateIntersectionAABBKHR */,IR(0, 0),IR(211, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {0,IR(0, 0),IR(27935, 37)/* RayQueryCommittedIntersectionNoneKHR */,IR(0, 0),IR(211, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {1,IR(0, 0),IR(27972, 41)/* RayQueryCommittedIntersectionTriangleKHR */,IR(0, 0),IR(211, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {2,IR(0, 0),IR(28013, 42)/* RayQueryCommittedIntersectionGeneratedKHR */,IR(0, 0),IR(211, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {0,IR(0, 0),IR(28055, 33)/* RayQueryCandidateIntersectionKHR */,IR(0, 0),IR(211, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {1,IR(0, 0),IR(28088, 33)/* RayQueryCommittedIntersectionKHR */,IR(0, 0),IR(211, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {0,IR(0, 0),IR(16887, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {1,IR(0, 0),IR(28121, 12)/* ClampToEdge */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {2,IR(0, 0),IR(28133, 6)/* Clamp */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {3,IR(0, 0),IR(28139, 7)/* Repeat */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {4,IR(0, 0),IR(28146, 15)/* RepeatMirrored */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {0,IR(0, 0),IR(28161, 8)/* Nearest */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {1,IR(0, 0),IR(28169, 7)/* Linear */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {0,IR(0, 0),IR(28176, 8)/* Unknown */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {1,IR(0, 0),IR(28184, 8)/* Rgba32f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {2,IR(0, 0),IR(28192, 8)/* Rgba16f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {3,IR(0, 0),IR(28200, 5)/* R32f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {4,IR(0, 0),IR(28205, 6)/* Rgba8 */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {5,IR(0, 0),IR(28211, 11)/* Rgba8Snorm */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {6,IR(0, 0),IR(28222, 6)/* Rg32f */,IR(0, 0),IR(212, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {7,IR(0, 0),IR(28228, 6)/* Rg16f */,IR(0, 0),IR(212, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {8,IR(0, 0),IR(28234, 13)/* R11fG11fB10f */,IR(0, 0),IR(212, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {9,IR(0, 0),IR(28247, 5)/* R16f */,IR(0, 0),IR(212, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {10,IR(0, 0),IR(28252, 7)/* Rgba16 */,IR(0, 0),IR(212, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {11,IR(0, 0),IR(28259, 8)/* Rgb10A2 */,IR(0, 0),IR(212, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {12,IR(0, 0),IR(28267, 5)/* Rg16 */,IR(0, 0),IR(212, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {13,IR(0, 0),IR(28272, 4)/* Rg8 */,IR(0, 0),IR(212, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {14,IR(0, 0),IR(28276, 4)/* R16 */,IR(0, 0),IR(212, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {15,IR(0, 0),IR(28280, 3)/* R8 */,IR(0, 0),IR(212, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {16,IR(0, 0),IR(28283, 12)/* Rgba16Snorm */,IR(0, 0),IR(212, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {17,IR(0, 0),IR(28295, 10)/* Rg16Snorm */,IR(0, 0),IR(212, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {18,IR(0, 0),IR(28305, 9)/* Rg8Snorm */,IR(0, 0),IR(212, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {19,IR(0, 0),IR(28314, 9)/* R16Snorm */,IR(0, 0),IR(212, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {20,IR(0, 0),IR(28323, 8)/* R8Snorm */,IR(0, 0),IR(212, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {21,IR(0, 0),IR(28331, 8)/* Rgba32i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {22,IR(0, 0),IR(28339, 8)/* Rgba16i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {23,IR(0, 0),IR(28347, 7)/* Rgba8i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {24,IR(0, 0),IR(28354, 5)/* R32i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {25,IR(0, 0),IR(28359, 6)/* Rg32i */,IR(0, 0),IR(212, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {26,IR(0, 0),IR(28365, 6)/* Rg16i */,IR(0, 0),IR(212, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {27,IR(0, 0),IR(28371, 5)/* Rg8i */,IR(0, 0),IR(212, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {28,IR(0, 0),IR(28376, 5)/* R16i */,IR(0, 0),IR(212, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {29,IR(0, 0),IR(28381, 4)/* R8i */,IR(0, 0),IR(212, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {30,IR(0, 0),IR(28385, 9)/* Rgba32ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {31,IR(0, 0),IR(28394, 9)/* Rgba16ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {32,IR(0, 0),IR(28403, 8)/* Rgba8ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {33,IR(0, 0),IR(28411, 6)/* R32ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {34,IR(0, 0),IR(28417, 10)/* Rgb10a2ui */,IR(0, 0),IR(212, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {35,IR(0, 0),IR(28427, 7)/* Rg32ui */,IR(0, 0),IR(212, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {36,IR(0, 0),IR(28434, 7)/* Rg16ui */,IR(0, 0),IR(212, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {37,IR(0, 0),IR(28441, 6)/* Rg8ui */,IR(0, 0),IR(212, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {38,IR(0, 0),IR(28447, 6)/* R16ui */,IR(0, 0),IR(212, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {39,IR(0, 0),IR(28453, 5)/* R8ui */,IR(0, 0),IR(212, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {40,IR(0, 0),IR(28458, 6)/* R64ui */,IR(0, 0),IR(213, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {41,IR(0, 0),IR(28464, 5)/* R64i */,IR(0, 0),IR(213, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {0,IR(0, 0),IR(28469, 12)/* CrossDevice */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {1,IR(0, 0),IR(28481, 7)/* Device */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {2,IR(0, 0),IR(28488, 10)/* Workgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {3,IR(0, 0),IR(28498, 9)/* Subgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {4,IR(0, 0),IR(28507, 11)/* Invocation */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {5,IR(0, 0),IR(28518, 12)/* QueueFamily */,IR(166, 1),IR(204, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {6,IR(0, 0),IR(28545, 14)/* ShaderCallKHR */,IR(0, 0),IR(61, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {0,IR(0, 0),IR(16887, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {1,IR(0, 0),IR(28559, 8)/* Flatten */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {2,IR(0, 0),IR(28567, 12)/* DontFlatten */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {1,IR(0, 0),IR(28579, 29)/* IdentifierPossibleDuplicates */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS
  {0,IR(0, 0),IR(16756, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(16768, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(16776, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {3,IR(0, 0),IR(16784, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(16790, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(16797, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(16808, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(16817, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(16830, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(16836, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(16846, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(16852, 15)/* ImportedModule */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {1,IR(0, 0),IR(16867, 20)/* ImportedDeclaration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {0,IR(0, 0),IR(16887, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(16892, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(16908, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(16922, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(16935, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(16947, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(16964, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(16976, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(16991, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(17004, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(17019, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(17037, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(17054, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(17075, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(17095, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(17115, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {16384,IR(0, 0),IR(17131, 16)/* FlagIsEnumClass */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {32768,IR(0, 0),IR(17147, 20)/* FlagTypePassByValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {65536,IR(0, 0),IR(17167, 24)/* FlagTypePassByReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {131072,IR(0, 0),IR(28608, 26)/* FlagUnknownPhysicalLayout */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(17191, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {1,IR(0, 0),IR(17197, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {2,IR(0, 0),IR(17202, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {3,IR(10, 1),IR(17241, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {4,IR(36, 2),IR(17252, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {5,IR(0, 0),IR(17261, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {6,IR(0, 0),IR(17266, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {7,IR(0, 0),IR(17273, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {8,IR(10, 1),IR(17284, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {9,IR(36, 2),IR(17291, 9)/* Fragment */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {0,IR(0, 0),IR(17300, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(17310, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(17323, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {3,IR(0, 0),IR(17336, 11)/* AtomicType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(28176, 8)/* Unknown */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {1,IR(0, 0),IR(28634, 5)/* ESSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {2,IR(0, 0),IR(28639, 5)/* GLSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {3,IR(0, 0),IR(28644, 9)/* OpenCL_C */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {4,IR(0, 0),IR(28653, 11)/* OpenCL_CPP */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {5,IR(0, 0),IR(28664, 5)/* HLSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {6,IR(0, 0),IR(28669, 15)/* CPP_for_OpenCL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {7,IR(0, 0),IR(28684, 5)/* SYCL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {8,IR(0, 0),IR(28689, 7)/* HERO_C */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {9,IR(0, 0),IR(28696, 5)/* NZSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {10,IR(0, 0),IR(28701, 5)/* WGSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {11,IR(0, 0),IR(28706, 6)/* Slang */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {12,IR(0, 0),IR(28712, 4)/* Zig */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {13,IR(0, 0),IR(28716, 5)/* Rust */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {14,IR(0, 0),IR(28721, 5)/* Pred */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {15,IR(0, 0),IR(28726, 9)/* ApilaJai */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {0,IR(0, 0),IR(28735, 16)/* UniformConstant */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {1,IR(0, 0),IR(28751, 6)/* Input */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {2,IR(0, 0),IR(18176, 8)/* Uniform */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {3,IR(0, 0),IR(28757, 7)/* Output */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4,IR(0, 0),IR(28488, 10)/* Workgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5,IR(0, 0),IR(28764, 15)/* CrossWorkgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {6,IR(0, 0),IR(28779, 8)/* Private */,IR(0, 0),IR(214, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {7,IR(0, 0),IR(28787, 9)/* Function */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {8,IR(0, 0),IR(28796, 8)/* Generic */,IR(0, 0),IR(216, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {9,IR(0, 0),IR(28804, 13)/* PushConstant */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {10,IR(0, 0),IR(28817, 14)/* AtomicCounter */,IR(0, 0),IR(83, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {11,IR(0, 0),IR(28831, 6)/* Image */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {12,IR(0, 0),IR(28837, 14)/* StorageBuffer */,IR(0, 0),IR(3, 1),IR(212, 2),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4172,IR(0, 0),IR(28851, 13)/* TileImageEXT */,IR(0, 0),IR(157, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4491,IR(0, 0),IR(28864, 19)/* TileAttachmentQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5068,IR(0, 0),IR(28883, 16)/* NodePayloadAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5328,IR(0, 0),IR(28899, 16)/* CallableDataKHR */,IR(167, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5329,IR(0, 0),IR(28930, 24)/* IncomingCallableDataKHR */,IR(168, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5338,IR(0, 0),IR(28977, 14)/* RayPayloadKHR */,IR(169, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5339,IR(0, 0),IR(29004, 16)/* HitAttributeKHR */,IR(170, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5342,IR(0, 0),IR(29035, 22)/* IncomingRayPayloadKHR */,IR(171, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5343,IR(0, 0),IR(29078, 22)/* ShaderRecordBufferKHR */,IR(172, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5349,IR(0, 0),IR(29121, 22)/* PhysicalStorageBuffer */,IR(173, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5385,IR(0, 0),IR(29168, 21)/* HitObjectAttributeNV */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5402,IR(0, 0),IR(29189, 24)/* TaskPayloadWorkgroupEXT */,IR(0, 0),IR(54, 1),IR(23, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5411,IR(0, 0),IR(29213, 22)/* HitObjectAttributeEXT */,IR(0, 0),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5605,IR(0, 0),IR(29235, 17)/* CodeSectionINTEL */,IR(0, 0),IR(217, 1),IR(115, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5936,IR(0, 0),IR(29252, 17)/* DeviceOnlyALTERA */,IR(174, 1),IR(218, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5937,IR(0, 0),IR(29285, 15)/* HostOnlyALTERA */,IR(175, 1),IR(218, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {0,IR(0, 0),IR(26096, 14)/* UncachedINTEL */,IR(0, 0),IR(155, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {1,IR(0, 0),IR(29314, 18)/* WriteThroughINTEL */,IR(0, 0),IR(155, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {2,IR(0, 0),IR(29332, 15)/* WriteBackINTEL */,IR(0, 0),IR(155, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {3,IR(0, 0),IR(26122, 15)/* StreamingINTEL */,IR(0, 0),IR(155, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {0,IR(0, 0),IR(16887, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {1,IR(10, 1),IR(29347, 11)/* TensorView */,IR(0, 0),IR(219, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {2,IR(10, 1),IR(29358, 11)/* DecodeFunc */,IR(0, 0),IR(107, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {4,IR(10, 1),IR(29369, 17)/* DecodeVectorFunc */,IR(0, 0),IR(220, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {0,IR(0, 0),IR(29386, 10)/* Undefined */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {1,IR(0, 0),IR(18134, 9)/* Constant */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {2,IR(0, 0),IR(28121, 12)/* ClampToEdge */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {3,IR(0, 0),IR(28139, 7)/* Repeat */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {4,IR(0, 0),IR(28146, 15)/* RepeatMirrored */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {0,IR(0, 0),IR(29396, 8)/* NoneARM */,IR(0, 0),IR(221, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {1,IR(0, 0),IR(29404, 15)/* NontemporalARM */,IR(0, 0),IR(221, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {2,IR(10, 1),IR(29419, 20)/* OutOfBoundsValueARM */,IR(0, 0),IR(221, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {4,IR(10, 1),IR(29439, 24)/* MakeElementAvailableARM */,IR(0, 0),IR(221, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {8,IR(10, 1),IR(29463, 22)/* MakeElementVisibleARM */,IR(0, 0),IR(221, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {16,IR(0, 0),IR(29485, 21)/* NonPrivateElementARM */,IR(0, 0),IR(221, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
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
    case SPV_OPERAND_TYPE_CAPABILITY: return IR(135, 305);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(440, 8);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(448, 3);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(451, 2);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS: return IR(453, 19);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION: return IR(472, 10);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(482, 4);
    case SPV_OPERAND_TYPE_COMPONENT_TYPE: return IR(486, 15);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT: return IR(501, 4);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS: return IR(505, 6);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE: return IR(511, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE: return IR(514, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT: return IR(517, 4);
    case SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(521, 8);
    case SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE: return IR(529, 3);
    case SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS: return IR(532, 16);
    case SPV_OPERAND_TYPE_DEBUG_OPERATION: return IR(548, 9);
    case SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER: return IR(557, 3);
    case SPV_OPERAND_TYPE_DECORATION: return IR(560, 152);
    case SPV_OPERAND_TYPE_DIMENSIONALITY: return IR(712, 8);
    case SPV_OPERAND_TYPE_EXECUTION_MODE: return IR(720, 101);
    case SPV_OPERAND_TYPE_EXECUTION_MODEL: return IR(821, 17);
    case SPV_OPERAND_TYPE_FPDENORM_MODE: return IR(838, 2);
    case SPV_OPERAND_TYPE_FPENCODING: return IR(840, 8);
    case SPV_OPERAND_TYPE_FPOPERATION_MODE: return IR(848, 2);
    case SPV_OPERAND_TYPE_FP_FAST_MATH_MODE: return IR(850, 9);
    case SPV_OPERAND_TYPE_FP_ROUNDING_MODE: return IR(859, 4);
    case SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE: return IR(863, 4);
    case SPV_OPERAND_TYPE_FUNCTION_CONTROL: return IR(867, 6);
    case SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE: return IR(873, 9);
    case SPV_OPERAND_TYPE_GATHER_MODES: return IR(882, 4);
    case SPV_OPERAND_TYPE_GROUP_OPERATION: return IR(886, 7);
    case SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER: return IR(893, 4);
    case SPV_OPERAND_TYPE_IMAGE: return IR(897, 17);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE: return IR(914, 26);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER: return IR(940, 20);
    case SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER: return IR(960, 2);
    case SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS: return IR(962, 3);
    case SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO: return IR(965, 2);
    case SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS: return IR(967, 2);
    case SPV_OPERAND_TYPE_LINKAGE_TYPE: return IR(969, 4);
    case SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL: return IR(973, 5);
    case SPV_OPERAND_TYPE_LOOP_CONTROL: return IR(978, 21);
    case SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(999, 15);
    case SPV_OPERAND_TYPE_MEMORY_ACCESS: return IR(1014, 9);
    case SPV_OPERAND_TYPE_MEMORY_MODEL: return IR(1023, 4);
    case SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID: return IR(1027, 15);
    case SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS: return IR(1042, 1);
    case SPV_OPERAND_TYPE_OVERFLOW_MODES: return IR(1043, 4);
    case SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT: return IR(1047, 1);
    case SPV_OPERAND_TYPE_QUANTIZATION_MODES: return IR(1048, 8);
    case SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS: return IR(1056, 3);
    case SPV_OPERAND_TYPE_RAY_FLAGS: return IR(1059, 12);
    case SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE: return IR(1071, 2);
    case SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE: return IR(1073, 3);
    case SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION: return IR(1076, 2);
    case SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE: return IR(1078, 5);
    case SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE: return IR(1083, 2);
    case SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT: return IR(1085, 42);
    case SPV_OPERAND_TYPE_SCOPE_ID: return IR(1127, 7);
    case SPV_OPERAND_TYPE_SELECTION_CONTROL: return IR(1134, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS: return IR(1137, 1);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(1138, 8);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(1146, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(1149, 2);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS: return IR(1151, 20);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION: return IR(1171, 10);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(1181, 4);
    case SPV_OPERAND_TYPE_SOURCE_LANGUAGE: return IR(1185, 16);
    case SPV_OPERAND_TYPE_STORAGE_CLASS: return IR(1201, 29);
    case SPV_OPERAND_TYPE_STORE_CACHE_CONTROL: return IR(1230, 4);
    case SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS: return IR(1234, 4);
    case SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE: return IR(1238, 5);
    case SPV_OPERAND_TYPE_TENSOR_OPERANDS: return IR(1243, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_IMAGE: return IR(897, 17);
    case SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS: return IR(1014, 9);
    case SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT: return IR(1047, 1);
    case SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS: return IR(505, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(999, 15);
    case SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS: return IR(1056, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_FPENCODING: return IR(840, 8);
    case SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS: return IR(1243, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_CAPABILITY: return IR(135, 305);
    default: break;
  }
  return IR(0,0);
}

// Operand names and index into kOperandsByValue, ordered by (operand kind, name)
// The fields in order are:
//   name, either the primary name or an alias, indexing into kStrings
//   index into the kOperandsByValue array
static const std::array<NameIndex, 1429> kOperandNames{{
  {IR(5906, 9), 0}, // 0 ReadOnly in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(5932, 10), 2}, // 1 ReadWrite in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(5922, 10), 1}, // 2 WriteOnly in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(5942, 8), 3}, // 3 Logical in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5950, 11), 4}, // 4 Physical32 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5971, 11), 5}, // 5 Physical64 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5982, 24), 6}, // 6 PhysicalStorageBuffer64 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(6006, 27), 6}, // 7 PhysicalStorageBuffer64EXT in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(7965, 13), 94}, // 8 BaryCoordKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7978, 12), 94}, // 9 BaryCoordNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7311, 20), 68}, // 10 BaryCoordNoPerspAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7331, 28), 69}, // 11 BaryCoordNoPerspCentroidAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8013, 20), 95}, // 12 BaryCoordNoPerspKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8033, 19), 95}, // 13 BaryCoordNoPerspNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7359, 26), 70}, // 14 BaryCoordNoPerspSampleAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7456, 22), 74}, // 15 BaryCoordPullModelAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7385, 19), 71}, // 16 BaryCoordSmoothAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7404, 27), 72}, // 17 BaryCoordSmoothCentroidAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7431, 25), 73}, // 18 BaryCoordSmoothSampleAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7115, 13), 59}, // 19 BaseInstance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7089, 11), 58}, // 20 BaseVertex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6090, 13), 9}, // 21 ClipDistance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7872, 22), 89}, // 22 ClipDistancePerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(9171, 12), 133}, // 23 ClusterIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6853, 13), 49}, // 24 CoreCountARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6827, 10), 48}, // 25 CoreIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6866, 13), 50}, // 26 CoreMaxIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6103, 13), 10}, // 27 CullDistance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7894, 22), 90}, // 28 CullDistancePerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(9224, 12), 134}, // 29 CullMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8220, 17), 101}, // 30 CullPrimitiveEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8624, 17), 115}, // 31 CurrentRayTimeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7185, 12), 62}, // 32 DeviceIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7128, 10), 60}, // 33 DrawIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6617, 22), 37}, // 34 EnqueuedWorkgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6387, 10), 21}, // 35 FragCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6473, 10), 27}, // 36 FragDepth in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8098, 23), 97}, // 37 FragInvocationCountEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8052, 12), 96}, // 38 FragSizeEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7478, 18), 75}, // 39 FragStencilRefEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8064, 15), 96}, // 40 FragmentSizeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6408, 12), 23}, // 41 FrontFacing in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7784, 16), 85}, // 42 FullyCoveredEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6558, 19), 33}, // 43 GlobalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6652, 15), 39}, // 44 GlobalLinearId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6639, 13), 38}, // 45 GlobalOffset in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6606, 11), 36}, // 46 GlobalSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6483, 17), 28}, // 47 HelperInvocation in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8926, 11), 122}, // 48 HitIsLSSNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8884, 14), 121}, // 49 HitIsSphereNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(9106, 33), 130}, // 50 HitKindBackFacingMicroTriangleNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(9072, 34), 129}, // 51 HitKindFrontFacingMicroTriangleNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8603, 11), 114}, // 52 HitKindKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8614, 10), 114}, // 53 HitKindNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(9054, 18), 128}, // 54 HitLSSPositionsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(9157, 14), 132}, // 55 HitLSSRadiiNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8788, 37), 118}, // 56 HitMicroTriangleVertexBarycentricsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8721, 34), 117}, // 57 HitMicroTriangleVertexPositionsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8976, 20), 123}, // 58 HitSpherePositionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(9139, 18), 131}, // 59 HitSphereRadiusNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8596, 7), 113}, // 60 HitTNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8664, 30), 116}, // 61 HitTriangleVertexPositionsKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8825, 20), 119}, // 62 IncomingRayFlagsKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8845, 19), 119}, // 63 IncomingRayFlagsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8485, 23), 110}, // 64 InstanceCustomIndexKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8508, 22), 110}, // 65 InstanceCustomIndexNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6125, 11), 12}, // 66 InstanceId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6813, 14), 47}, // 67 InstanceIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6226, 13), 14}, // 68 InvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8121, 22), 97}, // 69 InvocationsPerPixelNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8237, 12), 102}, // 70 LaunchIdKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8249, 11), 102}, // 71 LaunchIdNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8260, 14), 103}, // 72 LaunchSizeKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8274, 13), 103}, // 73 LaunchSizeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6239, 6), 15}, // 74 Layer in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7916, 15), 91}, // 75 LayerPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6540, 18), 32}, // 76 LocalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6577, 21), 34}, // 77 LocalInvocationIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7931, 16), 92}, // 78 MeshViewCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7947, 18), 93}, // 79 MeshViewIndicesNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6743, 21), 43}, // 80 NumEnqueuedSubgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6730, 13), 42}, // 81 NumSubgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6500, 14), 29}, // 82 NumWorkgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8400, 22), 107}, // 83 ObjectRayDirectionKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8422, 21), 107}, // 84 ObjectRayDirectionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8363, 19), 106}, // 85 ObjectRayOriginKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8382, 18), 106}, // 86 ObjectRayOriginNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8530, 17), 111}, // 87 ObjectToWorldKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8547, 16), 111}, // 88 ObjectToWorldNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6373, 14), 20}, // 89 PatchVertices in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6397, 11), 22}, // 90 PointCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6080, 10), 8}, // 91 PointSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6064, 9), 7}, // 92 Position in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7724, 18), 83}, // 93 PositionPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7836, 17), 87}, // 94 PrimitiveCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6136, 12), 13}, // 95 PrimitiveId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7853, 19), 88}, // 96 PrimitiveIndicesNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8168, 24), 99}, // 97 PrimitiveLineIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8143, 25), 98}, // 98 PrimitivePointIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7138, 24), 61}, // 99 PrimitiveShadingRateKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8192, 28), 100}, // 100 PrimitiveTriangleIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8864, 20), 120}, // 101 RayGeometryIndexKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8464, 11), 109}, // 102 RayTmaxKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8475, 10), 109}, // 103 RayTmaxNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8443, 11), 108}, // 104 RayTminKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8454, 10), 108}, // 105 RayTminNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7513, 29), 76}, // 106 RemainingRecursionLevelsAMDX in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7609, 16), 79}, // 107 ResourceHeapEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(9028, 10), 125}, // 108 SMCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(9047, 7), 127}, // 109 SMIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6420, 9), 24}, // 110 SampleId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6462, 11), 26}, // 111 SampleMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6447, 15), 25}, // 112 SamplePosition in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7576, 15), 78}, // 113 SamplerHeapEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7661, 20), 81}, // 114 SecondaryPositionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7700, 24), 82}, // 115 SecondaryViewportMaskNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7560, 16), 77}, // 116 ShaderIndexAMDX in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7229, 15), 64}, // 117 ShadingRateKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6902, 15), 53}, // 118 SubgroupEqMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6917, 18), 53}, // 119 SubgroupEqMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6957, 15), 54}, // 120 SubgroupGeMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6972, 18), 54}, // 121 SubgroupGeMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6990, 15), 55}, // 122 SubgroupGtMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7005, 18), 55}, // 123 SubgroupGtMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6764, 11), 44}, // 124 SubgroupId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7023, 15), 56}, // 125 SubgroupLeMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7038, 18), 56}, // 126 SubgroupLeMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6775, 26), 45}, // 127 SubgroupLocalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7056, 15), 57}, // 128 SubgroupLtMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7071, 18), 57}, // 129 SubgroupLtMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6714, 16), 41}, // 130 SubgroupMaxSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6667, 13), 40}, // 131 SubgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7824, 12), 86}, // 132 TaskCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6363, 10), 19}, // 133 TessCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6348, 15), 18}, // 134 TessLevelInner in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6333, 15), 17}, // 135 TessLevelOuter in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7293, 18), 67}, // 136 TileApronSizeQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7275, 18), 66}, // 137 TileDimensionQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7244, 15), 65}, // 138 TileOffsetQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6116, 9), 11}, // 139 VertexId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6801, 12), 46}, // 140 VertexIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7209, 10), 63}, // 141 ViewIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6285, 14), 16}, // 142 ViewportIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7625, 15), 80}, // 143 ViewportMaskNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7762, 22), 84}, // 144 ViewportMaskPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6879, 10), 51}, // 145 WarpIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(9038, 9), 126}, // 146 WarpIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6889, 13), 52}, // 147 WarpMaxIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8996, 13), 124}, // 148 WarpsPerSMNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6598, 8), 35}, // 149 WorkDim in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6528, 12), 31}, // 150 WorkgroupId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6514, 14), 30}, // 151 WorkgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8322, 21), 105}, // 152 WorldRayDirectionKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8343, 20), 105}, // 153 WorldRayDirectionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8287, 18), 104}, // 154 WorldRayOriginKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8305, 17), 104}, // 155 WorldRayOriginNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8563, 17), 112}, // 156 WorldToObjectKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8580, 16), 112}, // 157 WorldToObjectNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(11622, 9), 276}, // 158 AbortKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5961, 10), 139}, // 159 Addresses in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15066, 35), 383}, // 160 ArbitraryPrecisionFixedPointALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15101, 34), 383}, // 161 ArbitraryPrecisionFixedPointINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14538, 38), 371}, // 162 ArbitraryPrecisionFloatingPointALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14576, 37), 371}, // 163 ArbitraryPrecisionFloatingPointINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14473, 33), 370}, // 164 ArbitraryPrecisionIntegersALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14506, 32), 370}, // 165 ArbitraryPrecisionIntegersINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15818, 19), 409}, // 166 ArithmeticFenceEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14111, 9), 356}, // 167 AsmINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15719, 20), 405}, // 168 AtomicFloat16AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14166, 23), 359}, // 169 AtomicFloat16MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13412, 22), 328}, // 170 AtomicFloat16VectorNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15635, 20), 401}, // 171 AtomicFloat32AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14120, 23), 357}, // 172 AtomicFloat32MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15655, 20), 402}, // 173 AtomicFloat64AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14143, 23), 358}, // 174 AtomicFloat64MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9404, 14), 155}, // 175 AtomicStorage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10861, 17), 236}, // 176 AtomicStorageOps in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15760, 24), 407}, // 177 BFloat16ConversionINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11593, 29), 275}, // 178 BFloat16CooperativeMatrixKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11571, 22), 274}, // 179 BFloat16DotProductKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11285, 19), 257}, // 180 BFloat16MulAddQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11555, 16), 273}, // 181 BFloat16TypeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16594, 20), 434}, // 182 BindlessImagesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13349, 18), 325}, // 183 BindlessTextureNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15530, 16), 396}, // 184 BitInstructions in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10512, 18), 220}, // 185 BitcastExtractEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15268, 20), 387}, // 186 BlockingPipesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15288, 19), 387}, // 187 BlockingPipesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16555, 19), 432}, // 188 CacheControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6090, 13), 165}, // 189 ClipDistance in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12951, 32), 313}, // 190 ComputeDerivativeGroupLinearKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12983, 31), 313}, // 191 ComputeDerivativeGroupLinearNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11801, 31), 292}, // 192 ComputeDerivativeGroupQuadsKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11832, 30), 292}, // 193 ComputeDerivativeGroupQuadsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11631, 16), 278}, // 194 ConstantDataKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13750, 30), 341}, // 195 CooperativeMatrixBlockLoadsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11230, 32), 255}, // 196 CooperativeMatrixConversionQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13509, 32), 336}, // 197 CooperativeMatrixConversionsEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13602, 31), 338}, // 198 CooperativeMatrixConversionsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13861, 32), 346}, // 199 CooperativeMatrixDecodeVectorNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13808, 34), 344}, // 200 CooperativeMatrixGetCoordinateEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10439, 21), 394}, // 201 CooperativeMatrixKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10374, 28), 213}, // 202 CooperativeMatrixLayoutsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13039, 20), 315}, // 203 CooperativeMatrixNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13633, 41), 339}, // 204 CooperativeMatrixPerElementOperationsEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13674, 40), 339}, // 205 CooperativeMatrixPerElementOperationsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13541, 31), 337}, // 206 CooperativeMatrixReductionsEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13572, 30), 337}, // 207 CooperativeMatrixReductionsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13714, 36), 340}, // 208 CooperativeMatrixTensorAddressingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13392, 20), 327}, // 209 CooperativeVectorNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13780, 28), 342}, // 210 CooperativeVectorTrainingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6837, 16), 205}, // 211 CoreBuiltinsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6103, 13), 166}, // 212 CullDistance in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15739, 21), 406}, // 213 DebugInfoModuleINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13162, 25), 320}, // 214 DemoteToHelperInvocation in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13187, 28), 320}, // 215 DemoteToHelperInvocationEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11000, 18), 242}, // 216 DenormFlushToZero in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10985, 15), 241}, // 217 DenormPreserve in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9851, 18), 184}, // 218 DerivativeControl in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7591, 18), 277}, // 219 DescriptorHeapEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9375, 14), 153}, // 220 DeviceEnqueue in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7197, 12), 232}, // 221 DeviceGroup in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13215, 23), 321}, // 222 DisplacementMicromapNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15481, 11), 392}, // 223 DotProduct in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16680, 27), 437}, // 224 DotProductBFloat16AccVALVE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16647, 33), 436}, // 225 DotProductFloat16AccFloat16VALVE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16614, 33), 435}, // 226 DotProductFloat16AccFloat32VALVE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16707, 32), 438}, // 227 DotProductFloat8AccFloat32VALVE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15375, 22), 390}, // 228 DotProductInput4x8Bit in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15397, 25), 390}, // 229 DotProductInput4x8BitKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15422, 28), 391}, // 230 DotProductInput4x8BitPacked in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15450, 31), 391}, // 231 DotProductInput4x8BitPackedKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15334, 19), 389}, // 232 DotProductInputAll in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15353, 22), 389}, // 233 DotProductInputAllKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15492, 14), 392}, // 234 DotProductKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7100, 15), 223}, // 235 DrawParameters in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14223, 16), 362}, // 236 ExpectAssumeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15586, 7), 399}, // 237 FMAKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14453, 20), 369}, // 238 FPFastMathModeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16026, 29), 415}, // 239 FPGAArgumentInterfacesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16055, 28), 415}, // 240 FPGAArgumentInterfacesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15017, 25), 382}, // 241 FPGABufferLocationALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15042, 24), 382}, // 242 FPGABufferLocationINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14785, 28), 377}, // 243 FPGAClusterAttributesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14813, 27), 377}, // 244 FPGAClusterAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15837, 30), 410}, // 245 FPGAClusterAttributesV2ALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15867, 29), 410}, // 246 FPGAClusterAttributesV2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14869, 21), 379}, // 247 FPGADSPControlALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14890, 20), 379}, // 248 FPGADSPControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14936, 41), 381}, // 249 FPGAInvocationPipeliningAttributesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14977, 40), 381}, // 250 FPGAInvocationPipeliningAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14710, 26), 375}, // 251 FPGAKernelAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15896, 28), 411}, // 252 FPGAKernelAttributesv2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15977, 25), 414}, // 253 FPGALatencyControlALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16002, 24), 414}, // 254 FPGALatencyControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14643, 23), 373}, // 255 FPGALoopControlsALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14666, 22), 373}, // 256 FPGALoopControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14736, 25), 376}, // 257 FPGAMemoryAccessesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14761, 24), 376}, // 258 FPGAMemoryAccessesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14400, 27), 368}, // 259 FPGAMemoryAttributesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14427, 26), 368}, // 260 FPGAMemoryAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15307, 14), 388}, // 261 FPGARegALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15321, 13), 388}, // 262 FPGARegINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15961, 16), 413}, // 263 FPMaxErrorINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9289, 8), 144}, // 264 Float16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9275, 14), 143}, // 265 Float16Buffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11395, 16), 262}, // 266 Float16ImageAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10470, 10), 217}, // 267 Float4EXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9297, 8), 145}, // 268 Float64 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10460, 10), 216}, // 269 Float6EXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10412, 27), 215}, // 270 Float8CooperativeMatrixEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10402, 10), 214}, // 271 Float8EXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10480, 22), 218}, // 272 Float8UnsignedE8M0EXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15571, 15), 398}, // 273 FloatControls2 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14019, 23), 352}, // 274 FloatingPointModeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7990, 23), 291}, // 275 FragmentBarycentricKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11779, 22), 291}, // 276 FragmentBarycentricNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8079, 19), 293}, // 277 FragmentDensityEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7800, 24), 287}, // 278 FragmentFullyCoveredEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11433, 16), 264}, // 279 FragmentMaskAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13130, 32), 319}, // 280 FragmentShaderPixelInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13059, 33), 316}, // 281 FragmentShaderSampleInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13092, 38), 317}, // 282 FragmentShaderShadingRateInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7162, 23), 221}, // 283 FragmentShadingRateKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14374, 26), 367}, // 284 FunctionFloatControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14065, 22), 354}, // 285 FunctionPointersINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16414, 22), 426}, // 286 FunctionVariantsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9696, 15), 171}, // 287 GenericPointer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6148, 9), 137}, // 288 Geometry in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9446, 18), 158}, // 289 GeometryPointSize in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11707, 28), 282}, // 290 GeometryShaderPassthroughNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9909, 16), 187}, // 291 GeometryStreams in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16113, 36), 417}, // 292 GlobalVariableFPGADecorationsALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16149, 35), 417}, // 293 GlobalVariableFPGADecorationsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16083, 30), 416}, // 294 GlobalVariableHostAccessINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10365, 9), 212}, // 295 GraphARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6680, 16), 194}, // 296 GroupNonUniform in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10048, 26), 196}, // 297 GroupNonUniformArithmetic in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6935, 22), 197}, // 298 GroupNonUniformBallot in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10128, 25), 200}, // 299 GroupNonUniformClustered in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11876, 30), 294}, // 300 GroupNonUniformPartitionedEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11906, 29), 294}, // 301 GroupNonUniformPartitionedNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10153, 20), 201}, // 302 GroupNonUniformQuad in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15546, 25), 397}, // 303 GroupNonUniformRotateKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10074, 23), 198}, // 304 GroupNonUniformShuffle in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10097, 31), 199}, // 305 GroupNonUniformShuffleRelative in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10028, 20), 195}, // 306 GroupNonUniformVote in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16477, 26), 429}, // 307 GroupUniformArithmeticKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9368, 7), 152}, // 308 Groups in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15241, 14), 386}, // 309 IOPipesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15255, 13), 386}, // 310 IOPipesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9765, 8), 177}, // 311 Image1D in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9324, 11), 148}, // 312 ImageBasic in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9787, 12), 180}, // 313 ImageBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9642, 15), 167}, // 314 ImageCubeArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11762, 17), 289}, // 315 ImageFootprintNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11411, 22), 263}, // 316 ImageGatherBiasLodAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9464, 20), 159}, // 317 ImageGatherExtended in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11366, 29), 261}, // 318 ImageGatherExtendedModesQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11344, 22), 260}, // 319 ImageGatherLinearQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9799, 13), 181}, // 320 ImageMSArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9350, 12), 150}, // 321 ImageMipmap in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9840, 11), 183}, // 322 ImageQuery in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9335, 15), 149}, // 323 ImageReadWrite in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11449, 21), 266}, // 324 ImageReadWriteLodAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9674, 10), 169}, // 325 ImageRect in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14087, 24), 355}, // 326 IndirectReferencesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9716, 16), 173}, // 327 InputAttachment in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12021, 36), 297}, // 328 InputAttachmentArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12057, 39), 297}, // 329 InputAttachmentArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12562, 39), 304}, // 330 InputAttachmentArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12601, 42), 304}, // 331 InputAttachmentArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9418, 6), 156}, // 332 Int16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11528, 27), 272}, // 333 Int4CooperativeMatrixINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11514, 14), 271}, // 334 Int4TypeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9305, 6), 146}, // 335 Int64 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9311, 13), 147}, // 336 Int64Atomics in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11470, 14), 267}, // 337 Int64ImageEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9711, 5), 172}, // 338 Int8 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14042, 23), 353}, // 339 IntegerFunctions2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9869, 22), 185}, // 340 InterpolationFunction in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16739, 17), 439}, // 341 IntrinsicSAMSUNG in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5915, 7), 141}, // 342 Kernel in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14688, 22), 374}, // 343 KernelAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9258, 8), 140}, // 344 Linkage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9389, 15), 154}, // 345 LiteralSampler in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15675, 20), 403}, // 346 LongCompositesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13472, 14), 334}, // 347 LongVectorEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14840, 15), 378}, // 348 LoopFuseALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14855, 14), 378}, // 349 LoopFuseINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10502, 10), 219}, // 350 MXInt8EXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16530, 25), 431}, // 351 MaskedGatherScatterINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9251, 7), 135}, // 352 Matrix in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14910, 26), 380}, // 353 MemoryAccessAliasingINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6211, 15), 290}, // 354 MeshShadingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6197, 14), 288}, // 355 MeshShadingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9748, 7), 175}, // 356 MinLod in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7219, 10), 233}, // 357 MultiView in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6299, 14), 190}, // 358 MultiViewport in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11321, 23), 259}, // 359 MultipleWaitQueuesQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10003, 13), 192}, // 360 NamedBarrier in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15695, 11), 404}, // 361 OptNoneEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15706, 13), 404}, // 362 OptNoneINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7742, 20), 286}, // 363 PerViewAttributesNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6033, 31), 312}, // 364 PhysicalStorageBufferAddresses in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12917, 34), 312}, // 365 PhysicalStorageBufferAddressesEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10016, 12), 193}, // 366 PipeStorage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9362, 6), 151}, // 367 Pipes in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11647, 16), 279}, // 368 PoisonFreezeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16436, 18), 427}, // 369 PredicatedIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13452, 20), 333}, // 370 PushConstantBanksNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11499, 15), 270}, // 371 QuadControlKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13434, 18), 330}, // 372 RawAccessChainsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9236, 15), 393}, // 373 RayCullMaskKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11098, 12), 247}, // 374 RayQueryKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13367, 25), 326}, // 375 RayQueryPositionFetchKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11075, 23), 246}, // 376 RayQueryProvisionalKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9183, 41), 343}, // 377 RayTracingClusterAccelerationStructureNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8755, 33), 329}, // 378 RayTracingDisplacementMicromapNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6183, 14), 250}, // 379 RayTracingKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8937, 39), 332}, // 380 RayTracingLinearSweptSpheresGeometryNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8641, 23), 309}, // 381 RayTracingMotionBlurNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6170, 13), 308}, // 382 RayTracingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13267, 29), 322}, // 383 RayTracingOpacityMicromapEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15593, 42), 400}, // 384 RayTracingOpacityMicromapExecutionModeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13238, 29), 322}, // 385 RayTracingOpacityMicromapKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8694, 27), 307}, // 386 RayTracingPositionFetchKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13014, 25), 314}, // 387 RayTracingProvisionalKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8898, 28), 331}, // 388 RayTracingSpheresGeometryNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11129, 32), 249}, // 389 RayTraversalPrimitiveCullingKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16574, 20), 433}, // 390 RegisterLimitsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15506, 24), 395}, // 391 ReplicatedCompositesEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13998, 21), 351}, // 392 RoundToInfinityINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16454, 23), 428}, // 393 RoundedDivideSqrtINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11043, 16), 244}, // 394 RoundingModeRTE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11059, 16), 245}, // 395 RoundingModeRTZ in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15182, 30), 385}, // 396 RuntimeAlignedAttributeALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15212, 29), 385}, // 397 RuntimeAlignedAttributeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11972, 23), 296}, // 398 RuntimeDescriptorArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11995, 26), 296}, // 399 RuntimeDescriptorArrayEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11678, 29), 281}, // 400 SampleMaskOverrideCoverageNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10878, 28), 237}, // 401 SampleMaskPostDepthCoverage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6429, 18), 168}, // 402 SampleRateShading in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9755, 10), 176}, // 403 Sampled1D in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9773, 14), 179}, // 404 SampledBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9657, 17), 178}, // 405 SampledCubeArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9542, 33), 162}, // 406 SampledImageArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12335, 36), 301}, // 407 SampledImageArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12371, 39), 301}, // 408 SampledImageArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9684, 12), 170}, // 409 SampledRect in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6073, 7), 136}, // 410 Shader in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13486, 23), 335}, // 411 Shader64BitIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11484, 15), 268}, // 412 ShaderClockKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7542, 18), 269}, // 413 ShaderEnqueueAMDX in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13322, 27), 324}, // 414 ShaderInvocationReorderEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13296, 26), 323}, // 415 ShaderInvocationReorderNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6245, 12), 202}, // 416 ShaderLayer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11935, 17), 295}, // 417 ShaderNonUniform in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11952, 20), 295}, // 418 ShaderNonUniformEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9009, 19), 318}, // 419 ShaderSMBuiltinsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7681, 19), 285}, // 420 ShaderStereoViewNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6313, 20), 203}, // 421 ShaderViewportIndex in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6257, 28), 283}, // 422 ShaderViewportIndexLayerEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11735, 27), 283}, // 423 ShaderViewportIndexLayerNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7640, 21), 284}, // 424 ShaderViewportMaskNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11862, 14), 293}, // 425 ShadingRateNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11018, 25), 243}, // 426 SignedZeroInfNanPreserve in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9732, 16), 174}, // 427 SparseResidency in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16393, 21), 425}, // 428 SpecConditionalINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15784, 16), 408}, // 429 SplitBarrierEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15800, 18), 408}, // 430 SplitBarrierINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7496, 17), 265}, // 431 StencilExportEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10666, 25), 228}, // 432 StorageBuffer16BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10906, 24), 238}, // 433 StorageBuffer8BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9575, 34), 163}, // 434 StorageBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12410, 37), 302}, // 435 StorageBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12447, 40), 302}, // 436 StorageBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9609, 33), 164}, // 437 StorageImageArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12487, 36), 303}, // 438 StorageImageArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12523, 39), 303}, // 439 StorageImageArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9812, 28), 182}, // 440 StorageImageExtendedFormats in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9484, 24), 160}, // 441 StorageImageMultisample in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9925, 30), 188}, // 442 StorageImageReadWithoutFormat in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9955, 31), 189}, // 443 StorageImageWriteWithoutFormat in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10793, 21), 231}, // 444 StorageInputOutput16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10771, 22), 230}, // 445 StoragePushConstant16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10964, 21), 240}, // 446 StoragePushConstant8 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10288, 37), 210}, // 447 StorageTensorArrayDynamicIndexingARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10325, 40), 211}, // 448 StorageTensorArrayNonUniformIndexingARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12177, 39), 299}, // 449 StorageTexelBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12216, 42), 299}, // 450 StorageTexelBufferArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12730, 42), 306}, // 451 StorageTexelBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12772, 45), 306}, // 452 StorageTexelBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10754, 17), 229}, // 453 StorageUniform16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10691, 28), 228}, // 454 StorageUniformBufferBlock16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16212, 23), 419}, // 455 Subgroup2DBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16235, 30), 420}, // 456 Subgroup2DBlockTransformINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16265, 30), 421}, // 457 Subgroup2DBlockTransposeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14310, 39), 365}, // 458 SubgroupAvcMotionEstimationChromaINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14239, 33), 363}, // 459 SubgroupAvcMotionEstimationINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14272, 38), 364}, // 460 SubgroupAvcMotionEstimationIntraINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6696, 18), 222}, // 461 SubgroupBallotKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13914, 27), 348}, // 462 SubgroupBufferBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16184, 28), 418}, // 463 SubgroupBufferPrefetchINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9986, 17), 191}, // 464 SubgroupDispatch in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13941, 26), 349}, // 465 SubgroupImageBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13967, 31), 350}, // 466 SubgroupImageMediaBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16295, 38), 422}, // 467 SubgroupMatrixMultiplyAccumulateINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13893, 21), 347}, // 468 SubgroupShuffleINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11304, 17), 258}, // 469 SubgroupSizeQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10650, 16), 227}, // 470 SubgroupVoteKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15924, 19), 412}, // 471 TaskSequenceALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15943, 18), 412}, // 472 TaskSequenceINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13842, 19), 345}, // 473 TensorAddressingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16503, 27), 430}, // 474 TensorFloat32RoundingINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10277, 11), 209}, // 475 TensorsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16333, 28), 423}, // 476 TernaryBitwiseFunctionINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6157, 13), 138}, // 477 Tessellation in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9424, 22), 157}, // 478 TessellationPointSize in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11262, 23), 256}, // 479 TextureBlockMatch2QCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11208, 22), 253}, // 480 TextureBlockMatchQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11187, 21), 252}, // 481 TextureBoxFilterQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11161, 26), 251}, // 482 TextureSampleWeightedQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10191, 28), 206}, // 483 TileImageColorReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10219, 28), 207}, // 484 TileImageDepthReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10247, 30), 208}, // 485 TileImageStencilReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7259, 16), 254}, // 486 TileShadingQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9891, 18), 186}, // 487 TransformFeedback in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15135, 24), 384}, // 488 USMStorageClassesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15159, 23), 384}, // 489 USMStorageClassesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10719, 35), 229}, // 490 UniformAndStorageBuffer16BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10930, 34), 239}, // 491 UniformAndStorageBuffer8BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9508, 34), 161}, // 492 UniformBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12258, 37), 300}, // 493 UniformBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12295, 40), 300}, // 494 UniformBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10173, 18), 204}, // 495 UniformDecoration in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12096, 39), 298}, // 496 UniformTexelBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12135, 42), 298}, // 497 UniformTexelBufferArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12643, 42), 305}, // 498 UniformTexelBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12685, 45), 305}, // 499 UniformTexelBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14613, 30), 372}, // 500 UnstructuredLoopControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11110, 19), 248}, // 501 UntypedPointersKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16361, 32), 424}, // 502 UntypedVariableLengthArrayINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14349, 25), 366}, // 503 VariableLengthArrayINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10844, 17), 235}, // 504 VariablePointers in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10814, 30), 234}, // 505 VariablePointersStorageBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9266, 9), 142}, // 506 Vector16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14208, 15), 361}, // 507 VectorAnyINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14189, 19), 360}, // 508 VectorComputeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12817, 18), 310}, // 509 VulkanMemoryModel in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12856, 29), 311}, // 510 VulkanMemoryModelDeviceScope in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12885, 32), 311}, // 511 VulkanMemoryModelDeviceScopeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12835, 21), 310}, // 512 VulkanMemoryModelKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11663, 15), 280}, // 513 WeakLinkageAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10606, 44), 226}, // 514 WorkgroupMemoryExplicitLayout16BitAccessKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10563, 43), 225}, // 515 WorkgroupMemoryExplicitLayout8BitAccessKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10530, 33), 224}, // 516 WorkgroupMemoryExplicitLayoutKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16768, 8), 441}, // 517 Address in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16776, 8), 442}, // 518 Boolean in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16784, 6), 443}, // 519 Float in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16790, 7), 444}, // 520 Signed in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16797, 11), 445}, // 521 SignedChar in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16808, 9), 446}, // 522 Unsigned in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16817, 13), 447}, // 523 UnsignedChar in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16756, 12), 440}, // 524 Unspecified in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16830, 6), 448}, // 525 Class in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(16836, 10), 449}, // 526 Structure in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(16846, 6), 450}, // 527 Union in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(16867, 20), 452}, // 528 ImportedDeclaration in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(16852, 15), 451}, // 529 ImportedModule in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(16976, 15), 460}, // 530 FlagArtificial in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16991, 13), 461}, // 531 FlagExplicit in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16964, 12), 459}, // 532 FlagFwdDecl in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(17054, 21), 465}, // 533 FlagIndirectVariable in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16947, 17), 458}, // 534 FlagIsDefinition in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(17131, 16), 469}, // 535 FlagIsEnumClass in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16935, 12), 457}, // 536 FlagIsLocal in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(17115, 16), 468}, // 537 FlagIsOptimized in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16908, 14), 455}, // 538 FlagIsPrivate in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16892, 16), 454}, // 539 FlagIsProtected in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16922, 13), 456}, // 540 FlagIsPublic in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(17075, 20), 466}, // 541 FlagLValueReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(17019, 18), 463}, // 542 FlagObjectPointer in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(17004, 15), 462}, // 543 FlagPrototyped in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(17095, 20), 467}, // 544 FlagRValueReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(17037, 17), 464}, // 545 FlagStaticMember in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(17167, 24), 471}, // 546 FlagTypePassByReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(17147, 20), 470}, // 547 FlagTypePassByValue in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16887, 5), 453}, // 548 None in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(17252, 9), 476}, // 549 BitPiece in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(17284, 7), 480}, // 550 Constu in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(17191, 6), 472}, // 551 Deref in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(17291, 9), 481}, // 552 Fragment in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(17202, 6), 474}, // 553 Minus in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(17197, 5), 473}, // 554 Plus in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(17241, 11), 475}, // 555 PlusUconst in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(17273, 11), 479}, // 556 StackValue in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(17261, 5), 477}, // 557 Swap in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(17266, 7), 478}, // 558 Xderef in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(17336, 11), 485}, // 559 AtomicType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(17300, 10), 482}, // 560 ConstType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(17323, 13), 484}, // 561 RestrictType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(17310, 13), 483}, // 562 VolatileType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(17347, 10), 486}, // 563 Float16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(17357, 10), 487}, // 564 Float32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(17367, 10), 488}, // 565 Float64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(17535, 12), 499}, // 566 FloatE4M3NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(17547, 12), 500}, // 567 FloatE5M2NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(17390, 14), 490}, // 568 SignedInt16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(17404, 14), 491}, // 569 SignedInt32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(17418, 14), 492}, // 570 SignedInt64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(17377, 13), 489}, // 571 SignedInt8NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(17495, 19), 497}, // 572 SignedInt8PackedNV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(17447, 16), 494}, // 573 UnsignedInt16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(17463, 16), 495}, // 574 UnsignedInt32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(17479, 16), 496}, // 575 UnsignedInt64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(17432, 15), 493}, // 576 UnsignedInt8NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(17514, 21), 498}, // 577 UnsignedInt8PackedNV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(17611, 28), 504}, // 578 ColumnBlockedInterleavedARM in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(17571, 15), 502}, // 579 ColumnMajorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(17586, 25), 503}, // 580 RowBlockedInterleavedARM in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(17559, 12), 501}, // 581 RowMajorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(17647, 27), 506}, // 582 MatrixASignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(17674, 27), 507}, // 583 MatrixBSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(17701, 27), 508}, // 584 MatrixCSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(17728, 32), 509}, // 585 MatrixResultSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(17639, 8), 505}, // 586 NoneKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(17760, 26), 510}, // 587 SaturatingAccumulationKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(17797, 4), 513}, // 588 2x2 in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(17790, 7), 512}, // 589 Column in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(17786, 4), 511}, // 590 Row in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(17801, 11), 514}, // 591 MatrixAKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(17823, 21), 516}, // 592 MatrixAccumulatorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(17812, 11), 515}, // 593 MatrixBKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(17855, 14), 518}, // 594 ColumnMajorNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(17869, 21), 519}, // 595 InferencingOptimalNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(17844, 11), 517}, // 596 RowMajorNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(17890, 18), 520}, // 597 TrainingOptimalNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(16768, 8), 522}, // 598 Address in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16776, 8), 523}, // 599 Boolean in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16784, 6), 524}, // 600 Float in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16790, 7), 525}, // 601 Signed in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16797, 11), 526}, // 602 SignedChar in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16808, 9), 527}, // 603 Unsigned in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16817, 13), 528}, // 604 UnsignedChar in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16756, 12), 521}, // 605 Unspecified in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16830, 6), 529}, // 606 Class in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(16836, 10), 530}, // 607 Structure in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(16846, 6), 531}, // 608 Union in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(16976, 15), 539}, // 609 FlagArtificial in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16991, 13), 540}, // 610 FlagExplicit in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16964, 12), 538}, // 611 FlagFwdDecl in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(17054, 21), 544}, // 612 FlagIndirectVariable in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16947, 17), 537}, // 613 FlagIsDefinition in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16935, 12), 536}, // 614 FlagIsLocal in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(17115, 16), 547}, // 615 FlagIsOptimized in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16908, 14), 534}, // 616 FlagIsPrivate in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16892, 16), 533}, // 617 FlagIsProtected in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16922, 13), 535}, // 618 FlagIsPublic in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(17075, 20), 545}, // 619 FlagLValueReference in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(17019, 18), 542}, // 620 FlagObjectPointer in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(17004, 15), 541}, // 621 FlagPrototyped in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(17095, 20), 546}, // 622 FlagRValueReference in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(17037, 17), 543}, // 623 FlagStaticMember in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16887, 5), 532}, // 624 None in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(17252, 9), 552}, // 625 BitPiece in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(17284, 7), 556}, // 626 Constu in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(17191, 6), 548}, // 627 Deref in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(17202, 6), 550}, // 628 Minus in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(17197, 5), 549}, // 629 Plus in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(17241, 11), 551}, // 630 PlusUconst in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(17273, 11), 555}, // 631 StackValue in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(17261, 5), 553}, // 632 Swap in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(17266, 7), 554}, // 633 Xderef in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(17300, 10), 557}, // 634 ConstType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(17323, 13), 559}, // 635 RestrictType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(17310, 13), 558}, // 636 VolatileType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(20658, 16), 681}, // 637 AliasScopeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18117, 8), 579}, // 638 Aliased in SPV_OPERAND_TYPE_DECORATION
  {IR(19278, 15), 635}, // 639 AliasedPointer in SPV_OPERAND_TYPE_DECORATION
  {IR(19293, 18), 635}, // 640 AliasedPointerEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(18595, 10), 603}, // 641 Alignment in SPV_OPERAND_TYPE_DECORATION
  {IR(18639, 12), 605}, // 642 AlignmentId in SPV_OPERAND_TYPE_DECORATION
  {IR(17968, 12), 566}, // 643 ArrayStride in SPV_OPERAND_TYPE_DECORATION
  {IR(19019, 17), 622}, // 644 ArrayStrideIdEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(20208, 15), 669}, // 645 BankBitsALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20223, 14), 669}, // 646 BankBitsINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19387, 7), 639}, // 647 BankNV in SPV_OPERAND_TYPE_DECORATION
  {IR(19921, 16), 662}, // 648 BankwidthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19937, 15), 662}, // 649 BankwidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18272, 8), 592}, // 650 Binding in SPV_OPERAND_TYPE_DECORATION
  {IR(19412, 16), 641}, // 651 BindlessImageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(19394, 18), 640}, // 652 BindlessSamplerNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17932, 6), 562}, // 653 Block in SPV_OPERAND_TYPE_DECORATION
  {IR(18779, 22), 612}, // 654 BlockMatchSamplerQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(18757, 22), 611}, // 655 BlockMatchTextureQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(19443, 13), 643}, // 656 BoundImageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(19428, 15), 642}, // 657 BoundSamplerNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17938, 12), 563}, // 658 BufferBlock in SPV_OPERAND_TYPE_DECORATION
  {IR(20818, 21), 686}, // 659 BufferLocationALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20839, 20), 686}, // 660 BufferLocationINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18049, 8), 571}, // 661 BuiltIn in SPV_OPERAND_TYPE_DECORATION
  {IR(20377, 20), 674}, // 662 BurstCoalesceALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20397, 19), 674}, // 663 BurstCoalesceINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18015, 8), 570}, // 664 CPacked in SPV_OPERAND_TYPE_DECORATION
  {IR(22065, 22), 709}, // 665 CacheControlLoadINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(22124, 23), 710}, // 666 CacheControlStoreINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20416, 16), 675}, // 667 CacheSizeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20432, 15), 675}, // 668 CacheSizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18082, 9), 575}, // 669 Centroid in SPV_OPERAND_TYPE_DECORATION
  {IR(19526, 13), 647}, // 670 ClobberINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18143, 9), 582}, // 671 Coherent in SPV_OPERAND_TYPE_DECORATION
  {IR(17959, 9), 565}, // 672 ColMajor in SPV_OPERAND_TYPE_DECORATION
  {IR(18256, 10), 590}, // 673 Component in SPV_OPERAND_TYPE_DECORATION
  {IR(22012, 17), 708}, // 674 ConditionalINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(21241, 28), 696}, // 675 ConduitKernelArgumentALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(21269, 27), 696}, // 676 ConduitKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18134, 9), 581}, // 677 Constant in SPV_OPERAND_TYPE_DECORATION
  {IR(19456, 30), 644}, // 678 CooperativeMatrixTransposeEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(19672, 14), 654}, // 679 CounterBuffer in SPV_OPERAND_TYPE_DECORATION
  {IR(18280, 14), 593}, // 680 DescriptorSet in SPV_OPERAND_TYPE_DECORATION
  {IR(20447, 29), 676}, // 681 DontStaticallyCoalesceALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20476, 28), 676}, // 682 DontStaticallyCoalesceINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20030, 17), 665}, // 683 DoublepumpALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20047, 16), 665}, // 684 DoublepumpINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18801, 18), 613}, // 685 ExplicitInterpAMD in SPV_OPERAND_TYPE_DECORATION
  {IR(18465, 15), 599}, // 686 FPFastMathMode in SPV_OPERAND_TYPE_DECORATION
  {IR(21103, 26), 693}, // 687 FPMaxErrorDecorationINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18415, 15), 598}, // 688 FPRoundingMode in SPV_OPERAND_TYPE_DECORATION
  {IR(18071, 5), 573}, // 689 Flat in SPV_OPERAND_TYPE_DECORATION
  {IR(20237, 21), 670}, // 690 ForcePow2DepthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20258, 20), 670}, // 691 ForcePow2DepthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18367, 14), 597}, // 692 FuncParamAttr in SPV_OPERAND_TYPE_DECORATION
  {IR(19583, 21), 650}, // 693 FuncParamIOKindINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19814, 24), 658}, // 694 FunctionDenormModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20932, 31), 688}, // 695 FunctionFloatingPointModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19757, 26), 657}, // 696 FunctionRoundingModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20568, 26), 679}, // 697 FuseLoopsInFunctionALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20594, 25), 679}, // 698 FuseLoopsInFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18004, 11), 569}, // 699 GLSLPacked in SPV_OPERAND_TYPE_DECORATION
  {IR(17993, 11), 568}, // 700 GLSLShared in SPV_OPERAND_TYPE_DECORATION
  {IR(19646, 26), 653}, // 701 GlobalVariableOffsetINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19356, 31), 638}, // 702 HitObjectShaderRecordBufferEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(19326, 30), 637}, // 703 HitObjectShaderRecordBufferNV in SPV_OPERAND_TYPE_DECORATION
  {IR(19686, 24), 654}, // 704 HlslCounterBufferGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(19723, 19), 655}, // 705 HlslSemanticGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(21863, 16), 705}, // 706 HostAccessINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20859, 20), 687}, // 707 IOPipeStorageALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20879, 19), 687}, // 708 IOPipeStorageINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(21955, 29), 707}, // 709 ImplementInRegisterMapALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(21984, 28), 707}, // 710 ImplementInRegisterMapINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18266, 6), 591}, // 711 Index in SPV_OPERAND_TYPE_DECORATION
  {IR(21926, 15), 706}, // 712 InitModeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(21941, 14), 706}, // 713 InitModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20687, 25), 683}, // 714 InitiationIntervalALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20712, 24), 683}, // 715 InitiationIntervalINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18574, 21), 602}, // 716 InputAttachmentIndex in SPV_OPERAND_TYPE_DECORATION
  {IR(16739, 17), 711}, // 717 IntrinsicSAMSUNG in SPV_OPERAND_TYPE_DECORATION
  {IR(18098, 10), 577}, // 718 Invariant in SPV_OPERAND_TYPE_DECORATION
  {IR(21180, 31), 695}, // 719 LatencyControlConstraintALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(21211, 30), 695}, // 720 LatencyControlConstraintINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(21129, 26), 694}, // 721 LatencyControlLabelALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(21155, 25), 694}, // 722 LatencyControlLabelINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18542, 18), 600}, // 723 LinkageAttributes in SPV_OPERAND_TYPE_DECORATION
  {IR(18247, 9), 589}, // 724 Location in SPV_OPERAND_TYPE_DECORATION
  {IR(21359, 34), 698}, // 725 MMHostInterfaceAddressWidthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(21393, 33), 698}, // 726 MMHostInterfaceAddressWidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(21426, 31), 699}, // 727 MMHostInterfaceDataWidthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(21457, 30), 699}, // 728 MMHostInterfaceDataWidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(21487, 29), 700}, // 729 MMHostInterfaceLatencyALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(21516, 28), 700}, // 730 MMHostInterfaceLatencyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(21647, 30), 702}, // 731 MMHostInterfaceMaxBurstALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(21677, 29), 702}, // 732 MMHostInterfaceMaxBurstINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(21578, 35), 701}, // 733 MMHostInterfaceReadWriteModeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(21613, 34), 701}, // 734 MMHostInterfaceReadWriteModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(21706, 33), 703}, // 735 MMHostInterfaceWaitRequestALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(21739, 32), 703}, // 736 MMHostInterfaceWaitRequestINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20619, 20), 680}, // 737 MathOpDSPModeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20639, 19), 680}, // 738 MathOpDSPModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17980, 13), 567}, // 739 MatrixStride in SPV_OPERAND_TYPE_DECORATION
  {IR(18605, 14), 604}, // 740 MaxByteOffset in SPV_OPERAND_TYPE_DECORATION
  {IR(18651, 16), 606}, // 741 MaxByteOffsetId in SPV_OPERAND_TYPE_DECORATION
  {IR(20736, 21), 684}, // 742 MaxConcurrencyALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20757, 20), 684}, // 743 MaxConcurrencyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19952, 23), 663}, // 744 MaxPrivateCopiesALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19975, 22), 663}, // 745 MaxPrivateCopiesINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20063, 20), 666}, // 746 MaxReplicatesALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20083, 19), 666}, // 747 MaxReplicatesINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(21023, 18), 691}, // 748 MediaBlockIOINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19311, 15), 636}, // 749 MemberOffsetNV in SPV_OPERAND_TYPE_DECORATION
  {IR(19867, 13), 660}, // 750 MemoryALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19880, 12), 660}, // 751 MemoryINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20143, 12), 668}, // 752 MergeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20155, 11), 668}, // 753 MergeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20674, 13), 682}, // 754 NoAliasINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18560, 14), 601}, // 755 NoContraction in SPV_OPERAND_TYPE_DECORATION
  {IR(18057, 14), 572}, // 756 NoPerspective in SPV_OPERAND_TYPE_DECORATION
  {IR(18711, 13), 608}, // 757 NoSignedWrap in SPV_OPERAND_TYPE_DECORATION
  {IR(18724, 15), 609}, // 758 NoUnsignedWrap in SPV_OPERAND_TYPE_DECORATION
  {IR(18851, 20), 615}, // 759 NodeMaxPayloadsAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(18819, 32), 614}, // 760 NodeSharesPayloadLimitsWithAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(18164, 12), 584}, // 761 NonReadable in SPV_OPERAND_TYPE_DECORATION
  {IR(19218, 11), 633}, // 762 NonUniform in SPV_OPERAND_TYPE_DECORATION
  {IR(19229, 14), 633}, // 763 NonUniformEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(18152, 12), 583}, // 764 NonWritable in SPV_OPERAND_TYPE_DECORATION
  {IR(19892, 15), 661}, // 765 NumbanksALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19907, 14), 661}, // 766 NumbanksINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18294, 7), 594}, // 767 Offset in SPV_OPERAND_TYPE_DECORATION
  {IR(19036, 12), 623}, // 768 OffsetIdEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(19062, 19), 625}, // 769 OverrideCoverageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(19081, 14), 626}, // 770 PassthroughNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18076, 6), 574}, // 771 Patch in SPV_OPERAND_TYPE_DECORATION
  {IR(18991, 28), 621}, // 772 PayloadDispatchIndirectAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(18966, 25), 620}, // 773 PayloadNodeArraySizeAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(18914, 25), 618}, // 774 PayloadNodeBaseIndexAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(18894, 20), 617}, // 775 PayloadNodeNameAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(18939, 27), 619}, // 776 PayloadNodeSparseArrayAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(19142, 16), 629}, // 777 PerPrimitiveEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(19158, 15), 629}, // 778 PerPrimitiveNV in SPV_OPERAND_TYPE_DECORATION
  {IR(19183, 10), 631}, // 779 PerTaskNV in SPV_OPERAND_TYPE_DECORATION
  {IR(19193, 13), 632}, // 780 PerVertexKHR in SPV_OPERAND_TYPE_DECORATION
  {IR(19206, 12), 632}, // 781 PerVertexNV in SPV_OPERAND_TYPE_DECORATION
  {IR(19173, 10), 630}, // 782 PerViewNV in SPV_OPERAND_TYPE_DECORATION
  {IR(20777, 21), 685}, // 783 PipelineEnableALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20798, 20), 685}, // 784 PipelineEnableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20504, 15), 677}, // 785 PrefetchALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20519, 14), 677}, // 786 PrefetchINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19500, 26), 646}, // 787 ReferencedIndirectlyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19838, 15), 659}, // 788 RegisterALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19853, 14), 659}, // 789 RegisterINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(21296, 32), 697}, // 790 RegisterMapKernelArgumentALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(21328, 31), 697}, // 791 RegisterMapKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17908, 17), 560}, // 792 RelaxedPrecision in SPV_OPERAND_TYPE_DECORATION
  {IR(18108, 9), 578}, // 793 Restrict in SPV_OPERAND_TYPE_DECORATION
  {IR(19243, 16), 634}, // 794 RestrictPointer in SPV_OPERAND_TYPE_DECORATION
  {IR(19259, 19), 634}, // 795 RestrictPointerEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(17950, 9), 564}, // 796 RowMajor in SPV_OPERAND_TYPE_DECORATION
  {IR(19486, 14), 645}, // 797 SIMTCallINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18091, 7), 576}, // 798 Sample in SPV_OPERAND_TYPE_DECORATION
  {IR(18220, 20), 587}, // 799 SaturatedConversion in SPV_OPERAND_TYPE_DECORATION
  {IR(18667, 44), 607}, // 800 SaturatedToLargestFloat8NormalConversionEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(19114, 28), 628}, // 801 SecondaryViewportRelativeNV in SPV_OPERAND_TYPE_DECORATION
  {IR(19539, 17), 648}, // 802 SideEffectsINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20102, 21), 667}, // 803 SimpleDualPortALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20123, 20), 667}, // 804 SimpleDualPortINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20963, 25), 689}, // 805 SingleElementVectorINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19997, 17), 664}, // 806 SinglepumpALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20014, 16), 664}, // 807 SinglepumpINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17925, 7), 561}, // 808 SpecId in SPV_OPERAND_TYPE_DECORATION
  {IR(21771, 27), 704}, // 809 StableKernelArgumentALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(21798, 26), 704}, // 810 StableKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19631, 15), 652}, // 811 StackCallINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20533, 18), 678}, // 812 StallEnableALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20551, 17), 678}, // 813 StallEnableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(21041, 16), 692}, // 814 StallFreeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(21057, 15), 692}, // 815 StallFreeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18240, 7), 588}, // 816 Stream in SPV_OPERAND_TYPE_DECORATION
  {IR(20278, 17), 671}, // 817 StridesizeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20295, 16), 671}, // 818 StridesizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18871, 23), 616}, // 819 TrackFinishWritingAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(20340, 19), 673}, // 820 TrueDualPortALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20359, 18), 673}, // 821 TrueDualPortINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19048, 14), 624}, // 822 UTFEncodedKHR in SPV_OPERAND_TYPE_DECORATION
  {IR(18176, 8), 585}, // 823 Uniform in SPV_OPERAND_TYPE_DECORATION
  {IR(18210, 10), 586}, // 824 UniformId in SPV_OPERAND_TYPE_DECORATION
  {IR(19710, 13), 655}, // 825 UserSemantic in SPV_OPERAND_TYPE_DECORATION
  {IR(19742, 15), 656}, // 826 UserTypeGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(20988, 35), 690}, // 827 VectorComputeCallableFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19604, 27), 651}, // 828 VectorComputeFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19556, 27), 649}, // 829 VectorComputeVariableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19095, 19), 627}, // 830 ViewportRelativeNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18125, 9), 580}, // 831 Volatile in SPV_OPERAND_TYPE_DECORATION
  {IR(18739, 18), 610}, // 832 WeightTextureQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(20311, 15), 672}, // 833 WordsizeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20326, 14), 672}, // 834 WordsizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18301, 10), 595}, // 835 XfbBuffer in SPV_OPERAND_TYPE_DECORATION
  {IR(18311, 10), 596}, // 836 XfbStride in SPV_OPERAND_TYPE_DECORATION
  {IR(22147, 3), 712}, // 837 1D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(22150, 3), 713}, // 838 2D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(22153, 3), 714}, // 839 3D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(22166, 7), 717}, // 840 Buffer in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(22156, 5), 715}, // 841 Cube in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(22161, 5), 716}, // 842 Rect in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(22173, 12), 718}, // 843 SubpassData in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(22185, 17), 719}, // 844 TileImageDataEXT in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(23345, 20), 789}, // 845 ArithmeticPoisonKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23039, 15), 774}, // 846 CoalescingAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22628, 15), 750}, // 847 ContractionOff in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(11000, 18), 764}, // 848 DenormFlushToZero in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10985, 15), 763}, // 849 DenormPreserve in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22398, 13), 733}, // 850 DepthGreater in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22411, 10), 734}, // 851 DepthLess in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22383, 15), 732}, // 852 DepthReplacing in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22421, 15), 735}, // 853 DepthUnchanged in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23480, 25), 793}, // 854 DerivativeGroupLinearKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23505, 24), 793}, // 855 DerivativeGroupLinearNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23433, 24), 792}, // 856 DerivativeGroupQuadsKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23457, 23), 792}, // 857 DerivativeGroupQuadsNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22987, 29), 772}, // 858 EarlyAndLateFragmentTestsAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22350, 19), 729}, // 859 EarlyFragmentTests in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23990, 18), 813}, // 860 FPFastMathDefault in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22655, 10), 752}, // 861 Finalizer in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23805, 26), 805}, // 862 FloatingPointModeALTINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23831, 27), 806}, // 863 FloatingPointModeIEEEINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22643, 12), 751}, // 864 Initializer in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22472, 11), 739}, // 865 InputLines in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22483, 20), 740}, // 866 InputLinesAdjacency in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22460, 12), 738}, // 867 InputPoints in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22513, 24), 742}, // 868 InputTrianglesAdjacency in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22202, 12), 720}, // 869 Invocations in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23054, 15), 775}, // 870 IsApiEntryAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22543, 9), 744}, // 871 Isolines in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22436, 10), 736}, // 872 LocalSize in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22446, 14), 737}, // 873 LocalSizeHint in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22723, 16), 757}, // 874 LocalSizeHintId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22711, 12), 756}, // 875 LocalSizeId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23069, 21), 776}, // 876 MaxNodeRecursionAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23114, 21), 779}, // 877 MaxNumWorkgroupsAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23880, 16), 808}, // 878 MaxWorkDimINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23858, 22), 807}, // 879 MaxWorkgroupSizeINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23966, 24), 812}, // 880 MaximallyReconvergesKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(24102, 22), 818}, // 881 MaximumRegistersINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(24124, 24), 819}, // 882 MaximumRegistersIdINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(24079, 23), 817}, // 883 NamedBarrierCountINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(24199, 27), 820}, // 884 NamedMaximumRegistersINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23896, 20), 809}, // 885 NoGlobalOffsetINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22739, 34), 758}, // 886 NonCoherentColorAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22773, 34), 759}, // 887 NonCoherentDepthAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22807, 36), 760}, // 888 NonCoherentStencilAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22891, 34), 768}, // 889 NonCoherentTileAttachmentReadQCOM in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23916, 22), 810}, // 890 NumSIMDWorkitemsINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(24008, 21), 814}, // 891 OpacityMicromapIdKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22334, 16), 728}, // 892 OriginLowerLeft in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22318, 16), 727}, // 893 OriginUpperLeft in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22580, 16), 747}, // 894 OutputLineStrip in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23365, 15), 790}, // 895 OutputLinesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23380, 14), 790}, // 896 OutputLinesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22567, 13), 746}, // 897 OutputPoints in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23394, 20), 791}, // 898 OutputPrimitivesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23414, 19), 791}, // 899 OutputPrimitivesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22596, 20), 748}, // 900 OutputTriangleStrip in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23529, 19), 794}, // 901 OutputTrianglesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23548, 18), 794}, // 902 OutputTrianglesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22552, 15), 745}, // 903 OutputVertices in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22299, 19), 726}, // 904 PixelCenterInteger in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23566, 25), 795}, // 905 PixelInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23591, 27), 796}, // 906 PixelInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22369, 10), 730}, // 907 PointMode in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22873, 18), 762}, // 908 PostDepthCoverage in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23286, 19), 786}, // 909 QuadDerivativesKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22537, 6), 743}, // 910 Quads in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(24053, 26), 816}, // 911 RegisterMapInterfaceINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23305, 20), 787}, // 912 RequireFullQuadsKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(11043, 16), 766}, // 913 RoundingModeRTE in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23784, 21), 804}, // 914 RoundingModeRTNINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23763, 21), 803}, // 915 RoundingModeRTPINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(11059, 16), 767}, // 916 RoundingModeRTZ in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23618, 26), 797}, // 917 SampleInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23644, 28), 798}, // 918 SampleInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23938, 28), 811}, // 919 SchedulerTargetFmaxMhzINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(13486, 23), 801}, // 920 Shader64BitIndexingEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(7560, 16), 778}, // 921 ShaderIndexAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23672, 31), 799}, // 922 ShadingRateInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23703, 33), 800}, // 923 ShadingRateInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23736, 27), 802}, // 924 SharedLocalMemorySizeINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23325, 20), 788}, // 925 SharesInputWithAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(11018, 25), 765}, // 926 SignedZeroInfNanPreserve in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22214, 13), 721}, // 927 SpacingEqual in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22227, 22), 722}, // 928 SpacingFractionalEven in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22249, 21), 723}, // 929 SpacingFractionalOdd in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23090, 24), 777}, // 930 StaticNumWorkgroupsAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23239, 25), 784}, // 931 StencilRefGreaterBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23163, 26), 781}, // 932 StencilRefGreaterFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23264, 22), 785}, // 933 StencilRefLessBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23189, 23), 782}, // 934 StencilRefLessFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23016, 23), 773}, // 935 StencilRefReplacingEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23212, 27), 783}, // 936 StencilRefUnchangedBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23135, 28), 780}, // 937 StencilRefUnchangedFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(24029, 24), 815}, // 938 StreamingInterfaceINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(6667, 13), 753}, // 939 SubgroupSize in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22966, 21), 771}, // 940 SubgroupSizeFullQCOM in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22945, 21), 770}, // 941 SubgroupSizeHalfQCOM in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22843, 30), 761}, // 942 SubgroupUniformControlFlowKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22665, 22), 754}, // 943 SubgroupsPerWorkgroup in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22687, 24), 755}, // 944 SubgroupsPerWorkgroupId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22925, 20), 769}, // 945 TileShadingRateQCOM in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22503, 10), 741}, // 946 Triangles in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22616, 12), 749}, // 947 VecTypeHint in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22284, 15), 725}, // 948 VertexOrderCcw in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22270, 14), 724}, // 949 VertexOrderCw in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22379, 4), 731}, // 950 Xfb in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(24364, 10), 832}, // 951 AnyHitKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(24374, 9), 832}, // 952 AnyHitNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(24425, 12), 835}, // 953 CallableKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(24437, 11), 835}, // 954 CallableNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(24383, 14), 833}, // 955 ClosestHitKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(24397, 13), 833}, // 956 ClosestHitNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(17291, 9), 825}, // 957 Fragment in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(24276, 10), 826}, // 958 GLCompute in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(6148, 9), 824}, // 959 Geometry in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(24333, 16), 831}, // 960 IntersectionKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(24349, 15), 831}, // 961 IntersectionNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(5915, 7), 827}, // 962 Kernel in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(24456, 8), 837}, // 963 MeshEXT in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(24293, 7), 829}, // 964 MeshNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(24410, 8), 834}, // 965 MissKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(24418, 7), 834}, // 966 MissNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(24300, 17), 830}, // 967 RayGenerationKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(24317, 16), 830}, // 968 RayGenerationNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(24448, 8), 836}, // 969 TaskEXT in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(24286, 7), 828}, // 970 TaskNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(24233, 20), 822}, // 971 TessellationControl in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(24253, 23), 823}, // 972 TessellationEvaluation in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(24226, 7), 821}, // 973 Vertex in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(24473, 12), 839}, // 974 FlushToZero in SPV_OPERAND_TYPE_FPDENORM_MODE
  {IR(24464, 9), 838}, // 975 Preserve in SPV_OPERAND_TYPE_FPDENORM_MODE
  {IR(24485, 12), 840}, // 976 BFloat16KHR in SPV_OPERAND_TYPE_FPENCODING
  {IR(24553, 14), 845}, // 977 Float4E2M1EXT in SPV_OPERAND_TYPE_FPENCODING
  {IR(24525, 14), 843}, // 978 Float6E2M3EXT in SPV_OPERAND_TYPE_FPENCODING
  {IR(24539, 14), 844}, // 979 Float6E3M2EXT in SPV_OPERAND_TYPE_FPENCODING
  {IR(24497, 14), 841}, // 980 Float8E4M3EXT in SPV_OPERAND_TYPE_FPENCODING
  {IR(24511, 14), 842}, // 981 Float8E5M2EXT in SPV_OPERAND_TYPE_FPENCODING
  {IR(10480, 22), 846}, // 982 Float8UnsignedE8M0EXT in SPV_OPERAND_TYPE_FPENCODING
  {IR(10502, 10), 847}, // 983 MXInt8EXT in SPV_OPERAND_TYPE_FPENCODING
  {IR(24572, 4), 849}, // 984 ALT in SPV_OPERAND_TYPE_FPOPERATION_MODE
  {IR(24567, 5), 848}, // 985 IEEE in SPV_OPERAND_TYPE_FPOPERATION_MODE
  {IR(24610, 14), 856}, // 986 AllowContract in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(24624, 23), 856}, // 987 AllowContractFastINTEL in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(24647, 13), 857}, // 988 AllowReassoc in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(24660, 18), 857}, // 989 AllowReassocINTEL in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(24594, 11), 854}, // 990 AllowRecip in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(24678, 15), 858}, // 991 AllowTransform in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(24605, 5), 855}, // 992 Fast in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(24590, 4), 853}, // 993 NSZ in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(16887, 5), 850}, // 994 None in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(24583, 7), 852}, // 995 NotInf in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(24576, 7), 851}, // 996 NotNaN in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(24693, 4), 859}, // 997 RTE in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(24705, 4), 862}, // 998 RTN in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(24701, 4), 861}, // 999 RTP in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(24697, 4), 860}, // 1000 RTZ in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(24741, 18), 865}, // 1001 Horizontal2Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(24759, 18), 866}, // 1002 Horizontal4Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(24709, 16), 863}, // 1003 Vertical2Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(24725, 16), 864}, // 1004 Vertical4Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(24800, 6), 871}, // 1005 Const in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(24784, 11), 869}, // 1006 DontInline in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(24777, 7), 868}, // 1007 Inline in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(16887, 5), 867}, // 1008 None in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(15695, 11), 872}, // 1009 OptNoneEXT in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(15706, 13), 872}, // 1010 OptNoneINTEL in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(24795, 5), 870}, // 1011 Pure in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(24816, 6), 875}, // 1012 ByVal in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(24827, 8), 877}, // 1013 NoAlias in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(24835, 10), 878}, // 1014 NoCapture in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(24853, 12), 880}, // 1015 NoReadWrite in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(24845, 8), 879}, // 1016 NoWrite in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(24865, 21), 881}, // 1017 RuntimeAlignedALTERA in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(24886, 20), 881}, // 1018 RuntimeAlignedINTEL in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(24811, 5), 874}, // 1019 Sext in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(24822, 5), 876}, // 1020 Sret in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(24806, 5), 873}, // 1021 Zext in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(24906, 14), 882}, // 1022 Gather4x1QCOM in SPV_OPERAND_TYPE_GATHER_MODES
  {IR(24920, 12), 883}, // 1023 GatherDQCOM in SPV_OPERAND_TYPE_GATHER_MODES
  {IR(24932, 13), 884}, // 1024 GatherH2QCOM in SPV_OPERAND_TYPE_GATHER_MODES
  {IR(24945, 13), 885}, // 1025 GatherV2QCOM in SPV_OPERAND_TYPE_GATHER_MODES
  {IR(24993, 16), 889}, // 1026 ClusteredReduce in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(24979, 14), 888}, // 1027 ExclusiveScan in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(24965, 14), 887}, // 1028 InclusiveScan in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(25105, 28), 892}, // 1029 PartitionedExclusiveScanEXT in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(25133, 27), 892}, // 1030 PartitionedExclusiveScanNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(25050, 28), 891}, // 1031 PartitionedInclusiveScanEXT in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(25078, 27), 891}, // 1032 PartitionedInclusiveScanNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(25009, 21), 890}, // 1033 PartitionedReduceEXT in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(25030, 20), 890}, // 1034 PartitionedReduceNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(24958, 7), 886}, // 1035 Reduce in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(25160, 10), 893}, // 1036 NoneINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(25170, 10), 894}, // 1037 ReadINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(25191, 15), 896}, // 1038 ReadWriteINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(25180, 11), 895}, // 1039 WriteINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(25206, 5), 898}, // 1040 Bias in SPV_OPERAND_TYPE_IMAGE
  {IR(25220, 12), 901}, // 1041 ConstOffset in SPV_OPERAND_TYPE_IMAGE
  {IR(25232, 13), 903}, // 1042 ConstOffsets in SPV_OPERAND_TYPE_IMAGE
  {IR(25215, 5), 900}, // 1043 Grad in SPV_OPERAND_TYPE_IMAGE
  {IR(25211, 4), 899}, // 1044 Lod in SPV_OPERAND_TYPE_IMAGE
  {IR(25245, 19), 906}, // 1045 MakeTexelAvailable in SPV_OPERAND_TYPE_IMAGE
  {IR(25264, 22), 906}, // 1046 MakeTexelAvailableKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(25286, 17), 907}, // 1047 MakeTexelVisible in SPV_OPERAND_TYPE_IMAGE
  {IR(25303, 20), 907}, // 1048 MakeTexelVisibleKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(9748, 7), 905}, // 1049 MinLod in SPV_OPERAND_TYPE_IMAGE
  {IR(25323, 16), 908}, // 1050 NonPrivateTexel in SPV_OPERAND_TYPE_IMAGE
  {IR(25339, 19), 908}, // 1051 NonPrivateTexelKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(16887, 5), 897}, // 1052 None in SPV_OPERAND_TYPE_IMAGE
  {IR(25411, 12), 912}, // 1053 Nontemporal in SPV_OPERAND_TYPE_IMAGE
  {IR(18294, 7), 902}, // 1054 Offset in SPV_OPERAND_TYPE_IMAGE
  {IR(25423, 8), 913}, // 1055 Offsets in SPV_OPERAND_TYPE_IMAGE
  {IR(18091, 7), 904}, // 1056 Sample in SPV_OPERAND_TYPE_IMAGE
  {IR(25389, 11), 910}, // 1057 SignExtend in SPV_OPERAND_TYPE_IMAGE
  {IR(25358, 14), 909}, // 1058 VolatileTexel in SPV_OPERAND_TYPE_IMAGE
  {IR(25372, 17), 909}, // 1059 VolatileTexelKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(25400, 11), 911}, // 1060 ZeroExtend in SPV_OPERAND_TYPE_IMAGE
  {IR(16784, 6), 928}, // 1061 Float in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25592, 10), 927}, // 1062 HalfFloat in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25527, 12), 922}, // 1063 SignedInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25539, 12), 923}, // 1064 SignedInt32 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25516, 11), 921}, // 1065 SignedInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25441, 11), 915}, // 1066 SnormInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25431, 10), 914}, // 1067 SnormInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25501, 15), 920}, // 1068 UnormInt101010 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25613, 17), 930}, // 1069 UnormInt101010_2 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25630, 16), 931}, // 1070 UnormInt10X6EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25763, 16), 938}, // 1071 UnormInt12X4EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25779, 16), 939}, // 1072 UnormInt14X2EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25462, 11), 917}, // 1073 UnormInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25602, 11), 929}, // 1074 UnormInt24 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25686, 20), 934}, // 1075 UnormInt2_101010EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25452, 10), 916}, // 1076 UnormInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25487, 14), 919}, // 1077 UnormShort555 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25473, 14), 918}, // 1078 UnormShort565 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25706, 19), 935}, // 1079 UnsignedInt10X6EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25725, 19), 936}, // 1080 UnsignedInt12X4EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25744, 19), 937}, // 1081 UnsignedInt14X2EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25564, 14), 925}, // 1082 UnsignedInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25578, 14), 926}, // 1083 UnsignedInt32 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25551, 13), 924}, // 1084 UnsignedInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25646, 20), 932}, // 1085 UnsignedIntRaw10EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25666, 20), 933}, // 1086 UnsignedIntRaw12EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25797, 2), 941}, // 1087 A in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25898, 5), 959}, // 1088 ABGR in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25819, 5), 947}, // 1089 ARGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25814, 5), 946}, // 1090 BGRA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25856, 6), 953}, // 1091 Depth in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25862, 13), 954}, // 1092 DepthStencil in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25824, 10), 948}, // 1093 Intensity in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25834, 10), 949}, // 1094 Luminance in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25795, 2), 940}, // 1095 R in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25802, 3), 943}, // 1096 RA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25799, 3), 942}, // 1097 RG in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25805, 4), 944}, // 1098 RGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25809, 5), 945}, // 1099 RGBA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25851, 5), 952}, // 1100 RGBx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25847, 4), 951}, // 1101 RGx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25844, 3), 950}, // 1102 Rx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25892, 6), 958}, // 1103 sBGRA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25875, 5), 955}, // 1104 sRGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25886, 6), 957}, // 1105 sRGBA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25880, 6), 956}, // 1106 sRGBx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25903, 28), 960}, // 1107 InitOnDeviceReprogramALTERA in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(25931, 27), 960}, // 1108 InitOnDeviceReprogramINTEL in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(25958, 24), 961}, // 1109 InitOnDeviceResetALTERA in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(25982, 23), 961}, // 1110 InitOnDeviceResetINTEL in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(26005, 7), 962}, // 1111 NoWait in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(26012, 11), 963}, // 1112 WaitKernel in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(26023, 14), 964}, // 1113 WaitWorkGroup in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(26037, 12), 966}, // 1114 CmdExecTime in SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {IR(16887, 5), 965}, // 1115 None in SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {IR(26049, 13), 968}, // 1116 MayUsePrintf in SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {IR(16887, 5), 967}, // 1117 None in SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {IR(26062, 7), 969}, // 1118 Export in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(26069, 7), 970}, // 1119 Import in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(26076, 12), 971}, // 1120 LinkOnceODR in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(26088, 8), 972}, // 1121 WeakAMD in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(26110, 12), 974}, // 1122 CachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(26162, 17), 977}, // 1123 ConstCachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(26137, 25), 976}, // 1124 InvalidateAfterReadINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(26122, 15), 975}, // 1125 StreamingINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(26096, 14), 973}, // 1126 UncachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(26302, 22), 990}, // 1127 DependencyArrayALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(26324, 21), 990}, // 1128 DependencyArrayINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(26197, 19), 981}, // 1129 DependencyInfinite in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(26216, 17), 982}, // 1130 DependencyLength in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(26186, 11), 980}, // 1131 DontUnroll in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(20687, 25), 988}, // 1132 InitiationIntervalALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(20712, 24), 988}, // 1133 InitiationIntervalINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(26261, 18), 985}, // 1134 IterationMultiple in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(26345, 19), 992}, // 1135 LoopCoalesceALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(26364, 18), 992}, // 1136 LoopCoalesceINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(26507, 16), 996}, // 1137 LoopCountALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(26523, 15), 996}, // 1138 LoopCountINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(20736, 21), 989}, // 1139 MaxConcurrencyALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(20757, 20), 989}, // 1140 MaxConcurrencyINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(26382, 22), 993}, // 1141 MaxInterleavingALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(26404, 21), 993}, // 1142 MaxInterleavingINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(26247, 14), 984}, // 1143 MaxIterations in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(26538, 27), 997}, // 1144 MaxReinvocationDelayALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(26565, 26), 997}, // 1145 MaxReinvocationDelayINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(26233, 14), 983}, // 1146 MinIterations in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(11321, 23), 998}, // 1147 MultipleWaitQueuesQCOM in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(26478, 15), 995}, // 1148 NoFusionALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(26493, 14), 995}, // 1149 NoFusionINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(16887, 5), 978}, // 1150 None in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(26289, 13), 987}, // 1151 PartialCount in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(26279, 10), 986}, // 1152 PeelCount in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(20777, 21), 991}, // 1153 PipelineEnableALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(20798, 20), 991}, // 1154 PipelineEnableINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(26425, 27), 994}, // 1155 SpeculatedIterationsALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(26452, 26), 994}, // 1156 SpeculatedIterationsINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(26179, 7), 979}, // 1157 Unroll in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(26874, 27), 1012}, // 1158 MatrixAPackedBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(26822, 26), 1010}, // 1159 MatrixAPackedFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(26742, 23), 1006}, // 1160 MatrixAPackedInt4INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(26696, 23), 1004}, // 1161 MatrixAPackedInt8INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(26591, 29), 1000}, // 1162 MatrixASignedComponentsINTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(26788, 17), 1008}, // 1163 MatrixATF32INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(26901, 27), 1013}, // 1164 MatrixBPackedBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(26848, 26), 1011}, // 1165 MatrixBPackedFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(26765, 23), 1007}, // 1166 MatrixBPackedInt4INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(26719, 23), 1005}, // 1167 MatrixBPackedInt8INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(26620, 29), 1001}, // 1168 MatrixBSignedComponentsINTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(26805, 17), 1009}, // 1169 MatrixBTF32INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(26649, 21), 1002}, // 1170 MatrixCBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(26670, 26), 1003}, // 1171 MatrixResultBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(16887, 5), 999}, // 1172 None in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(27061, 20), 1021}, // 1173 AliasScopeINTELMask in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(26928, 8), 1016}, // 1174 Aligned in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(26936, 21), 1018}, // 1175 MakePointerAvailable in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(26957, 24), 1018}, // 1176 MakePointerAvailableKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(26981, 19), 1019}, // 1177 MakePointerVisible in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(27000, 22), 1019}, // 1178 MakePointerVisibleKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(27081, 17), 1022}, // 1179 NoAliasINTELMask in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(27022, 18), 1020}, // 1180 NonPrivatePointer in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(27040, 21), 1020}, // 1181 NonPrivatePointerKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(16887, 5), 1014}, // 1182 None in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25411, 12), 1017}, // 1183 Nontemporal in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(18125, 9), 1015}, // 1184 Volatile in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(27105, 8), 1024}, // 1185 GLSL450 in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(27113, 7), 1025}, // 1186 OpenCL in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(27098, 7), 1023}, // 1187 Simple in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(27120, 7), 1026}, // 1188 Vulkan in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(27127, 10), 1026}, // 1189 VulkanKHR in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(27145, 8), 1028}, // 1190 Acquire in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(27161, 15), 1030}, // 1191 AcquireRelease in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(27265, 20), 1036}, // 1192 AtomicCounterMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(27244, 21), 1035}, // 1193 CrossWorkgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(27285, 12), 1037}, // 1194 ImageMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(27326, 14), 1039}, // 1195 MakeAvailable in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(27340, 17), 1039}, // 1196 MakeAvailableKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(27357, 12), 1040}, // 1197 MakeVisible in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(27369, 15), 1040}, // 1198 MakeVisibleKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(16887, 5), 1027}, // 1199 None in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(27297, 13), 1038}, // 1200 OutputMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(27310, 16), 1038}, // 1201 OutputMemoryKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(27137, 8), 1027}, // 1202 Relaxed in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(27153, 8), 1029}, // 1203 Release in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(27176, 23), 1031}, // 1204 SequentiallyConsistent in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(27213, 15), 1033}, // 1205 SubgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(27199, 14), 1032}, // 1206 UniformMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(18125, 9), 1041}, // 1207 Volatile in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(27228, 16), 1034}, // 1208 WorkgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(27384, 10), 1042}, // 1209 AutoINTEL in SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS
  {IR(27399, 4), 1044}, // 1210 SAT in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(27412, 8), 1046}, // 1211 SAT_SYM in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(27403, 9), 1045}, // 1212 SAT_ZERO in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(27394, 5), 1043}, // 1213 WRAP in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(27420, 25), 1047}, // 1214 PackedVectorFormat4x8Bit in SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {IR(27445, 28), 1047}, // 1215 PackedVectorFormat4x8BitKHR in SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {IR(27486, 4), 1050}, // 1216 RND in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(27519, 9), 1054}, // 1217 RND_CONV in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(27528, 13), 1055}, // 1218 RND_CONV_ODD in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(27499, 8), 1052}, // 1219 RND_INF in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(27507, 12), 1053}, // 1220 RND_MIN_INF in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(27490, 9), 1051}, // 1221 RND_ZERO in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(27473, 4), 1048}, // 1222 TRN in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(27477, 9), 1049}, // 1223 TRN_ZERO in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(16887, 5), 1056}, // 1224 None in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(27541, 25), 1057}, // 1225 RobustnessPerComponentNV in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(27566, 23), 1058}, // 1226 RobustnessPerElementNV in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(27658, 27), 1064}, // 1227 CullBackFacingTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(27685, 28), 1065}, // 1228 CullFrontFacingTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(27727, 16), 1067}, // 1229 CullNoOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(27713, 14), 1066}, // 1230 CullOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(27827, 30), 1070}, // 1231 ForceOpacityMicromap2StateEXT in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(27797, 30), 1070}, // 1232 ForceOpacityMicromap2StateKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(27599, 12), 1061}, // 1233 NoOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(17639, 8), 1059}, // 1234 NoneKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(27589, 10), 1060}, // 1235 OpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(27784, 13), 1069}, // 1236 SkipAABBsKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(27760, 24), 1068}, // 1237 SkipBuiltinPrimitivesNV in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(27634, 24), 1063}, // 1238 SkipClosestHitShaderKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(27743, 17), 1068}, // 1239 SkipTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(27611, 23), 1062}, // 1240 TerminateOnFirstHitKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(27898, 37), 1072}, // 1241 RayQueryCandidateIntersectionAABBKHR in SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {IR(27857, 41), 1071}, // 1242 RayQueryCandidateIntersectionTriangleKHR in SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {IR(28013, 42), 1075}, // 1243 RayQueryCommittedIntersectionGeneratedKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(27935, 37), 1073}, // 1244 RayQueryCommittedIntersectionNoneKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(27972, 41), 1074}, // 1245 RayQueryCommittedIntersectionTriangleKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(28055, 33), 1076}, // 1246 RayQueryCandidateIntersectionKHR in SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {IR(28088, 33), 1077}, // 1247 RayQueryCommittedIntersectionKHR in SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {IR(28133, 6), 1080}, // 1248 Clamp in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(28121, 12), 1079}, // 1249 ClampToEdge in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(16887, 5), 1078}, // 1250 None in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(28139, 7), 1081}, // 1251 Repeat in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(28146, 15), 1082}, // 1252 RepeatMirrored in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(28169, 7), 1084}, // 1253 Linear in SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {IR(28161, 8), 1083}, // 1254 Nearest in SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {IR(28234, 13), 1093}, // 1255 R11fG11fB10f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28276, 4), 1099}, // 1256 R16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28314, 9), 1104}, // 1257 R16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28247, 5), 1094}, // 1258 R16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28376, 5), 1113}, // 1259 R16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28447, 6), 1123}, // 1260 R16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28200, 5), 1088}, // 1261 R32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28354, 5), 1109}, // 1262 R32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28411, 6), 1118}, // 1263 R32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28464, 5), 1126}, // 1264 R64i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28458, 6), 1125}, // 1265 R64ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28280, 3), 1100}, // 1266 R8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28323, 8), 1105}, // 1267 R8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28381, 4), 1114}, // 1268 R8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28453, 5), 1124}, // 1269 R8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28267, 5), 1097}, // 1270 Rg16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28295, 10), 1102}, // 1271 Rg16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28228, 6), 1092}, // 1272 Rg16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28365, 6), 1111}, // 1273 Rg16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28434, 7), 1121}, // 1274 Rg16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28222, 6), 1091}, // 1275 Rg32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28359, 6), 1110}, // 1276 Rg32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28427, 7), 1120}, // 1277 Rg32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28272, 4), 1098}, // 1278 Rg8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28305, 9), 1103}, // 1279 Rg8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28371, 5), 1112}, // 1280 Rg8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28441, 6), 1122}, // 1281 Rg8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28259, 8), 1096}, // 1282 Rgb10A2 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28417, 10), 1119}, // 1283 Rgb10a2ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28252, 7), 1095}, // 1284 Rgba16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28283, 12), 1101}, // 1285 Rgba16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28192, 8), 1087}, // 1286 Rgba16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28339, 8), 1107}, // 1287 Rgba16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28394, 9), 1116}, // 1288 Rgba16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28184, 8), 1086}, // 1289 Rgba32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28331, 8), 1106}, // 1290 Rgba32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28385, 9), 1115}, // 1291 Rgba32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28205, 6), 1089}, // 1292 Rgba8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28211, 11), 1090}, // 1293 Rgba8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28347, 7), 1108}, // 1294 Rgba8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28403, 8), 1117}, // 1295 Rgba8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28176, 8), 1085}, // 1296 Unknown in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(28469, 12), 1127}, // 1297 CrossDevice in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(28481, 7), 1128}, // 1298 Device in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(28507, 11), 1131}, // 1299 Invocation in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(28518, 12), 1132}, // 1300 QueueFamily in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(28530, 15), 1132}, // 1301 QueueFamilyKHR in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(28545, 14), 1133}, // 1302 ShaderCallKHR in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(28498, 9), 1130}, // 1303 Subgroup in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(28488, 10), 1129}, // 1304 Workgroup in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(28567, 12), 1136}, // 1305 DontFlatten in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(28559, 8), 1135}, // 1306 Flatten in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(16887, 5), 1134}, // 1307 None in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(28579, 29), 1137}, // 1308 IdentifierPossibleDuplicates in SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS
  {IR(16768, 8), 1139}, // 1309 Address in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16776, 8), 1140}, // 1310 Boolean in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16784, 6), 1141}, // 1311 Float in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16790, 7), 1142}, // 1312 Signed in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16797, 11), 1143}, // 1313 SignedChar in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16808, 9), 1144}, // 1314 Unsigned in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16817, 13), 1145}, // 1315 UnsignedChar in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16756, 12), 1138}, // 1316 Unspecified in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16830, 6), 1146}, // 1317 Class in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(16836, 10), 1147}, // 1318 Structure in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(16846, 6), 1148}, // 1319 Union in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(16867, 20), 1150}, // 1320 ImportedDeclaration in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(16852, 15), 1149}, // 1321 ImportedModule in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(16976, 15), 1158}, // 1322 FlagArtificial in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16991, 13), 1159}, // 1323 FlagExplicit in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16964, 12), 1157}, // 1324 FlagFwdDecl in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(17054, 21), 1163}, // 1325 FlagIndirectVariable in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16947, 17), 1156}, // 1326 FlagIsDefinition in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(17131, 16), 1167}, // 1327 FlagIsEnumClass in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16935, 12), 1155}, // 1328 FlagIsLocal in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(17115, 16), 1166}, // 1329 FlagIsOptimized in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16908, 14), 1153}, // 1330 FlagIsPrivate in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16892, 16), 1152}, // 1331 FlagIsProtected in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16922, 13), 1154}, // 1332 FlagIsPublic in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(17075, 20), 1164}, // 1333 FlagLValueReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(17019, 18), 1161}, // 1334 FlagObjectPointer in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(17004, 15), 1160}, // 1335 FlagPrototyped in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(17095, 20), 1165}, // 1336 FlagRValueReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(17037, 17), 1162}, // 1337 FlagStaticMember in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(17167, 24), 1169}, // 1338 FlagTypePassByReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(17147, 20), 1168}, // 1339 FlagTypePassByValue in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(28608, 26), 1170}, // 1340 FlagUnknownPhysicalLayout in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16887, 5), 1151}, // 1341 None in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(17252, 9), 1175}, // 1342 BitPiece in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(17284, 7), 1179}, // 1343 Constu in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(17191, 6), 1171}, // 1344 Deref in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(17291, 9), 1180}, // 1345 Fragment in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(17202, 6), 1173}, // 1346 Minus in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(17197, 5), 1172}, // 1347 Plus in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(17241, 11), 1174}, // 1348 PlusUconst in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(17273, 11), 1178}, // 1349 StackValue in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(17261, 5), 1176}, // 1350 Swap in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(17266, 7), 1177}, // 1351 Xderef in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(17336, 11), 1184}, // 1352 AtomicType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(17300, 10), 1181}, // 1353 ConstType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(17323, 13), 1183}, // 1354 RestrictType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(17310, 13), 1182}, // 1355 VolatileType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(28726, 9), 1200}, // 1356 ApilaJai in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(28669, 15), 1191}, // 1357 CPP_for_OpenCL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(28634, 5), 1186}, // 1358 ESSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(28639, 5), 1187}, // 1359 GLSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(28689, 7), 1193}, // 1360 HERO_C in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(28664, 5), 1190}, // 1361 HLSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(28696, 5), 1194}, // 1362 NZSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(28644, 9), 1188}, // 1363 OpenCL_C in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(28653, 11), 1189}, // 1364 OpenCL_CPP in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(28721, 5), 1199}, // 1365 Pred in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(28716, 5), 1198}, // 1366 Rust in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(28684, 5), 1192}, // 1367 SYCL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(28706, 6), 1196}, // 1368 Slang in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(28176, 8), 1185}, // 1369 Unknown in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(28701, 5), 1195}, // 1370 WGSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(28712, 4), 1197}, // 1371 Zig in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(28817, 14), 1211}, // 1372 AtomicCounter in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28899, 16), 1217}, // 1373 CallableDataKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28915, 15), 1217}, // 1374 CallableDataNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(29235, 17), 1227}, // 1375 CodeSectionINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28764, 15), 1206}, // 1376 CrossWorkgroup in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(29252, 17), 1228}, // 1377 DeviceOnlyALTERA in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(29269, 16), 1228}, // 1378 DeviceOnlyINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28787, 9), 1208}, // 1379 Function in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28796, 8), 1209}, // 1380 Generic in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(29004, 16), 1220}, // 1381 HitAttributeKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(29020, 15), 1220}, // 1382 HitAttributeNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(29213, 22), 1226}, // 1383 HitObjectAttributeEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(29168, 21), 1224}, // 1384 HitObjectAttributeNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(29285, 15), 1229}, // 1385 HostOnlyALTERA in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(29300, 14), 1229}, // 1386 HostOnlyINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28831, 6), 1212}, // 1387 Image in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28930, 24), 1218}, // 1388 IncomingCallableDataKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28954, 23), 1218}, // 1389 IncomingCallableDataNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(29035, 22), 1221}, // 1390 IncomingRayPayloadKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(29057, 21), 1221}, // 1391 IncomingRayPayloadNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28751, 6), 1202}, // 1392 Input in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28883, 16), 1216}, // 1393 NodePayloadAMDX in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28757, 7), 1204}, // 1394 Output in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(29121, 22), 1223}, // 1395 PhysicalStorageBuffer in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(29143, 25), 1223}, // 1396 PhysicalStorageBufferEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28779, 8), 1207}, // 1397 Private in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28804, 13), 1210}, // 1398 PushConstant in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28977, 14), 1219}, // 1399 RayPayloadKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28991, 13), 1219}, // 1400 RayPayloadNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(29078, 22), 1222}, // 1401 ShaderRecordBufferKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(29100, 21), 1222}, // 1402 ShaderRecordBufferNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28837, 14), 1213}, // 1403 StorageBuffer in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(29189, 24), 1225}, // 1404 TaskPayloadWorkgroupEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28864, 19), 1215}, // 1405 TileAttachmentQCOM in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28851, 13), 1214}, // 1406 TileImageEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(18176, 8), 1203}, // 1407 Uniform in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28735, 16), 1201}, // 1408 UniformConstant in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28488, 10), 1205}, // 1409 Workgroup in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(26122, 15), 1233}, // 1410 StreamingINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(26096, 14), 1230}, // 1411 UncachedINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(29332, 15), 1232}, // 1412 WriteBackINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(29314, 18), 1231}, // 1413 WriteThroughINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(29358, 11), 1236}, // 1414 DecodeFunc in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(29369, 17), 1237}, // 1415 DecodeVectorFunc in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(16887, 5), 1234}, // 1416 None in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(29347, 11), 1235}, // 1417 TensorView in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(28121, 12), 1240}, // 1418 ClampToEdge in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(18134, 9), 1239}, // 1419 Constant in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(28139, 7), 1241}, // 1420 Repeat in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(28146, 15), 1242}, // 1421 RepeatMirrored in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(29386, 10), 1238}, // 1422 Undefined in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(29439, 24), 1246}, // 1423 MakeElementAvailableARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(29463, 22), 1247}, // 1424 MakeElementVisibleARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(29485, 21), 1248}, // 1425 NonPrivateElementARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(29396, 8), 1243}, // 1426 NoneARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(29404, 15), 1244}, // 1427 NontemporalARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(29419, 20), 1245}, // 1428 OutOfBoundsValueARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
}};

IndexRange OperandNameRangeForKind(spv_operand_type_t type) {
  switch(type) {
    case SPV_OPERAND_TYPE_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_ADDRESSING_MODEL: return IR(3, 5);
    case SPV_OPERAND_TYPE_BUILT_IN: return IR(8, 150);
    case SPV_OPERAND_TYPE_CAPABILITY: return IR(158, 359);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(517, 8);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(525, 3);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(528, 2);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS: return IR(530, 19);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION: return IR(549, 10);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(559, 4);
    case SPV_OPERAND_TYPE_COMPONENT_TYPE: return IR(563, 15);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT: return IR(578, 4);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS: return IR(582, 6);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE: return IR(588, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE: return IR(591, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT: return IR(594, 4);
    case SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(598, 8);
    case SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE: return IR(606, 3);
    case SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS: return IR(609, 16);
    case SPV_OPERAND_TYPE_DEBUG_OPERATION: return IR(625, 9);
    case SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER: return IR(634, 3);
    case SPV_OPERAND_TYPE_DECORATION: return IR(637, 200);
    case SPV_OPERAND_TYPE_DIMENSIONALITY: return IR(837, 8);
    case SPV_OPERAND_TYPE_EXECUTION_MODE: return IR(845, 106);
    case SPV_OPERAND_TYPE_EXECUTION_MODEL: return IR(951, 23);
    case SPV_OPERAND_TYPE_FPDENORM_MODE: return IR(974, 2);
    case SPV_OPERAND_TYPE_FPENCODING: return IR(976, 8);
    case SPV_OPERAND_TYPE_FPOPERATION_MODE: return IR(984, 2);
    case SPV_OPERAND_TYPE_FP_FAST_MATH_MODE: return IR(986, 11);
    case SPV_OPERAND_TYPE_FP_ROUNDING_MODE: return IR(997, 4);
    case SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE: return IR(1001, 4);
    case SPV_OPERAND_TYPE_FUNCTION_CONTROL: return IR(1005, 7);
    case SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE: return IR(1012, 10);
    case SPV_OPERAND_TYPE_GATHER_MODES: return IR(1022, 4);
    case SPV_OPERAND_TYPE_GROUP_OPERATION: return IR(1026, 10);
    case SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER: return IR(1036, 4);
    case SPV_OPERAND_TYPE_IMAGE: return IR(1040, 21);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE: return IR(1061, 26);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER: return IR(1087, 20);
    case SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER: return IR(1107, 4);
    case SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS: return IR(1111, 3);
    case SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO: return IR(1114, 2);
    case SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS: return IR(1116, 2);
    case SPV_OPERAND_TYPE_LINKAGE_TYPE: return IR(1118, 4);
    case SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL: return IR(1122, 5);
    case SPV_OPERAND_TYPE_LOOP_CONTROL: return IR(1127, 31);
    case SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(1158, 15);
    case SPV_OPERAND_TYPE_MEMORY_ACCESS: return IR(1173, 12);
    case SPV_OPERAND_TYPE_MEMORY_MODEL: return IR(1185, 5);
    case SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID: return IR(1190, 19);
    case SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS: return IR(1209, 1);
    case SPV_OPERAND_TYPE_OVERFLOW_MODES: return IR(1210, 4);
    case SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT: return IR(1214, 2);
    case SPV_OPERAND_TYPE_QUANTIZATION_MODES: return IR(1216, 8);
    case SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS: return IR(1224, 3);
    case SPV_OPERAND_TYPE_RAY_FLAGS: return IR(1227, 14);
    case SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE: return IR(1241, 2);
    case SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE: return IR(1243, 3);
    case SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION: return IR(1246, 2);
    case SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE: return IR(1248, 5);
    case SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE: return IR(1253, 2);
    case SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT: return IR(1255, 42);
    case SPV_OPERAND_TYPE_SCOPE_ID: return IR(1297, 8);
    case SPV_OPERAND_TYPE_SELECTION_CONTROL: return IR(1305, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS: return IR(1308, 1);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(1309, 8);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(1317, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(1320, 2);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS: return IR(1322, 20);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION: return IR(1342, 10);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(1352, 4);
    case SPV_OPERAND_TYPE_SOURCE_LANGUAGE: return IR(1356, 16);
    case SPV_OPERAND_TYPE_STORAGE_CLASS: return IR(1372, 38);
    case SPV_OPERAND_TYPE_STORE_CACHE_CONTROL: return IR(1410, 4);
    case SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS: return IR(1414, 4);
    case SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE: return IR(1418, 5);
    case SPV_OPERAND_TYPE_TENSOR_OPERANDS: return IR(1423, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_IMAGE: return IR(1040, 21);
    case SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS: return IR(1173, 12);
    case SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT: return IR(1214, 2);
    case SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS: return IR(582, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(1158, 15);
    case SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS: return IR(1224, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_FPENCODING: return IR(976, 8);
    case SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS: return IR(1423, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_CAPABILITY: return IR(158, 359);
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
static const std::array<InstructionDesc, 877> kInstructionDesc{{
  {spv::Op::OpNop, false, false, IR(0, 0), IR(29506, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpUndef, true, true, IR(39, 2), IR(29562, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpSourceContinued, false, false, IR(11, 1), IR(29568, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpSource, false, false, IR(41, 4), IR(29687, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpSourceExtension, false, false, IR(11, 1), IR(29694, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpName, false, false, IR(45, 2), IR(29710, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpMemberName, false, false, IR(47, 3), IR(29715, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpString, true, false, IR(50, 2), IR(29726, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpLine, false, false, IR(52, 3), IR(29733, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpExtension, false, false, IR(11, 1), IR(29738, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpExtInstImport, true, false, IR(50, 2), IR(29748, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpExtInst, true, true, IR(55, 4), IR(29808, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpMemoryModel, false, false, IR(59, 2), IR(29880, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpEntryPoint, false, false, IR(61, 4), IR(29954, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpExecutionMode, false, false, IR(65, 2), IR(29997, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpCapability, false, false, IR(67, 1), IR(30039, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpTypeVoid, true, false, IR(68, 1), IR(30050, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeBool, true, false, IR(68, 1), IR(30059, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeInt, true, false, IR(69, 3), IR(30068, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeFloat, true, false, IR(72, 3), IR(30113, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeVector, true, false, IR(75, 3), IR(30123, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeMatrix, true, false, IR(75, 3), IR(30134, 11), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeImage, true, false, IR(78, 9), IR(30258, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeSampler, true, false, IR(68, 1), IR(30268, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeSampledImage, true, false, IR(87, 2), IR(30280, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeArray, true, false, IR(89, 3), IR(30297, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeRuntimeArray, true, false, IR(87, 2), IR(30307, 17), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeStruct, true, false, IR(92, 2), IR(30324, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeOpaque, true, false, IR(50, 2), IR(30335, 11), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypePointer, true, false, IR(94, 3), IR(30377, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeFunction, true, false, IR(97, 3), IR(30389, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeEvent, true, false, IR(68, 1), IR(30402, 10), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeDeviceEvent, true, false, IR(68, 1), IR(30412, 16), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeReserveId, true, false, IR(68, 1), IR(30428, 14), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeQueue, true, false, IR(68, 1), IR(30442, 10), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypePipe, true, false, IR(100, 2), IR(30452, 9), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeForwardPointer, false, false, IR(102, 2), IR(30461, 19), IR(0, 0), IR(222, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantTrue, true, true, IR(39, 2), IR(30480, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantFalse, true, true, IR(39, 2), IR(30493, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstant, true, true, IR(104, 3), IR(18134, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantComposite, true, true, IR(107, 3), IR(30545, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantSampler, true, true, IR(110, 5), IR(30641, 16), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantNull, true, true, IR(39, 2), IR(30657, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantTrue, true, true, IR(39, 2), IR(30670, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantFalse, true, true, IR(39, 2), IR(30687, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstant, true, true, IR(104, 3), IR(30705, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantComposite, true, true, IR(107, 3), IR(30718, 22), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantOp, true, true, IR(115, 3), IR(30781, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpFunction, true, true, IR(118, 4), IR(28787, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionParameter, true, true, IR(39, 2), IR(30830, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionEnd, false, false, IR(0, 0), IR(30848, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionCall, true, true, IR(122, 4), IR(30860, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpVariable, true, true, IR(126, 4), IR(30873, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpImageTexelPointer, true, true, IR(130, 5), IR(30882, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpLoad, true, true, IR(135, 4), IR(30940, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpStore, false, false, IR(139, 3), IR(30945, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCopyMemory, false, false, IR(142, 4), IR(30951, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCopyMemorySized, false, false, IR(146, 5), IR(30962, 16), IR(0, 0), IR(225, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpAccessChain, true, true, IR(122, 4), IR(30978, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpInBoundsAccessChain, true, true, IR(122, 4), IR(30990, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrAccessChain, true, true, IR(151, 5), IR(31010, 15), IR(0, 0), IR(227, 4), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpArrayLength, true, true, IR(156, 4), IR(31025, 12), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpGenericPtrMemSemantics, true, true, IR(160, 3), IR(31037, 23), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpInBoundsPtrAccessChain, true, true, IR(151, 5), IR(31060, 23), IR(0, 0), IR(1, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpDecorate, false, false, IR(163, 2), IR(31111, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpMemberDecorate, false, false, IR(165, 3), IR(31120, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpDecorationGroup, true, false, IR(68, 1), IR(31135, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupDecorate, false, false, IR(168, 2), IR(31151, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupMemberDecorate, false, false, IR(170, 2), IR(31210, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpVectorExtractDynamic, true, true, IR(172, 4), IR(31230, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpVectorInsertDynamic, true, true, IR(130, 5), IR(31251, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpVectorShuffle, true, true, IR(176, 5), IR(31271, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeConstruct, true, true, IR(107, 3), IR(31285, 19), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeExtract, true, true, IR(181, 4), IR(31304, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeInsert, true, true, IR(176, 5), IR(31321, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCopyObject, true, true, IR(160, 3), IR(31337, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpTranspose, true, true, IR(160, 3), IR(31348, 10), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpSampledImage, true, true, IR(172, 4), IR(31358, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleImplicitLod, true, true, IR(185, 5), IR(31403, 23), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleExplicitLod, true, true, IR(190, 5), IR(31449, 23), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleDrefImplicitLod, true, true, IR(195, 6), IR(31472, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleDrefExplicitLod, true, true, IR(201, 6), IR(31499, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjImplicitLod, true, true, IR(185, 5), IR(31526, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjExplicitLod, true, true, IR(190, 5), IR(31553, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjDrefImplicitLod, true, true, IR(195, 6), IR(31580, 31), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjDrefExplicitLod, true, true, IR(201, 6), IR(31611, 31), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageFetch, true, true, IR(185, 5), IR(31642, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageGather, true, true, IR(195, 6), IR(31653, 12), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageDrefGather, true, true, IR(195, 6), IR(31665, 16), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageRead, true, true, IR(185, 5), IR(31681, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageWrite, false, false, IR(207, 4), IR(31691, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImage, true, true, IR(160, 3), IR(28831, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryFormat, true, true, IR(160, 3), IR(31702, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryOrder, true, true, IR(160, 3), IR(31719, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySizeLod, true, true, IR(172, 4), IR(31735, 18), IR(0, 0), IR(231, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySize, true, true, IR(160, 3), IR(31753, 15), IR(0, 0), IR(231, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryLod, true, true, IR(172, 4), IR(31768, 14), IR(0, 0), IR(233, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryLevels, true, true, IR(160, 3), IR(31782, 17), IR(0, 0), IR(231, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySamples, true, true, IR(160, 3), IR(31799, 18), IR(0, 0), IR(231, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertFToU, true, true, IR(160, 3), IR(31817, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertFToS, true, true, IR(160, 3), IR(31829, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertSToF, true, true, IR(160, 3), IR(31841, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToF, true, true, IR(160, 3), IR(31853, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpUConvert, true, true, IR(160, 3), IR(31865, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSConvert, true, true, IR(160, 3), IR(31874, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpFConvert, true, true, IR(160, 3), IR(31883, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpQuantizeToF16, true, true, IR(160, 3), IR(31892, 14), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertPtrToU, true, true, IR(160, 3), IR(31906, 14), IR(0, 0), IR(222, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSatConvertSToU, true, true, IR(160, 3), IR(31920, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSatConvertUToS, true, true, IR(160, 3), IR(31935, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToPtr, true, true, IR(160, 3), IR(31950, 14), IR(0, 0), IR(222, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpPtrCastToGeneric, true, true, IR(160, 3), IR(31964, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpGenericCastToPtr, true, true, IR(160, 3), IR(31981, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpGenericCastToPtrExplicit, true, true, IR(211, 4), IR(31998, 25), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpBitcast, true, true, IR(160, 3), IR(32023, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSNegate, true, true, IR(160, 3), IR(32031, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFNegate, true, true, IR(160, 3), IR(32039, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIAdd, true, true, IR(172, 4), IR(32047, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFAdd, true, true, IR(172, 4), IR(32052, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpISub, true, true, IR(172, 4), IR(32057, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFSub, true, true, IR(172, 4), IR(32062, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIMul, true, true, IR(172, 4), IR(32067, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFMul, true, true, IR(172, 4), IR(32072, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDiv, true, true, IR(172, 4), IR(32077, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSDiv, true, true, IR(172, 4), IR(32082, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFDiv, true, true, IR(172, 4), IR(32087, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUMod, true, true, IR(172, 4), IR(32092, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSRem, true, true, IR(172, 4), IR(32097, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSMod, true, true, IR(172, 4), IR(32102, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFRem, true, true, IR(172, 4), IR(32107, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFMod, true, true, IR(172, 4), IR(32112, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpVectorTimesScalar, true, true, IR(172, 4), IR(32117, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesScalar, true, true, IR(172, 4), IR(32135, 18), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpVectorTimesMatrix, true, true, IR(172, 4), IR(32153, 18), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesVector, true, true, IR(172, 4), IR(32171, 18), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesMatrix, true, true, IR(172, 4), IR(32189, 18), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpOuterProduct, true, true, IR(172, 4), IR(32207, 13), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpDot, true, true, IR(172, 4), IR(32220, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIAddCarry, true, true, IR(172, 4), IR(32224, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpISubBorrow, true, true, IR(172, 4), IR(32234, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUMulExtended, true, true, IR(172, 4), IR(32245, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSMulExtended, true, true, IR(172, 4), IR(32258, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpAny, true, true, IR(160, 3), IR(32271, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpAll, true, true, IR(160, 3), IR(32275, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsNan, true, true, IR(160, 3), IR(32279, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsInf, true, true, IR(160, 3), IR(32285, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsFinite, true, true, IR(160, 3), IR(32291, 9), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsNormal, true, true, IR(160, 3), IR(32300, 9), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSignBitSet, true, true, IR(160, 3), IR(32309, 11), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLessOrGreater, true, true, IR(172, 4), IR(32320, 14), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), SPV_SPIRV_VERSION_WORD(1,5), PrintingClass::kRelational_and_Logical},
  {spv::Op::OpOrdered, true, true, IR(172, 4), IR(32334, 8), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUnordered, true, true, IR(172, 4), IR(32342, 10), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalEqual, true, true, IR(172, 4), IR(32352, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalNotEqual, true, true, IR(172, 4), IR(32365, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalOr, true, true, IR(172, 4), IR(32381, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalAnd, true, true, IR(172, 4), IR(32391, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalNot, true, true, IR(160, 3), IR(32402, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSelect, true, true, IR(130, 5), IR(32413, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIEqual, true, true, IR(172, 4), IR(32420, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpINotEqual, true, true, IR(172, 4), IR(32427, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUGreaterThan, true, true, IR(172, 4), IR(32437, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSGreaterThan, true, true, IR(172, 4), IR(32450, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUGreaterThanEqual, true, true, IR(172, 4), IR(32463, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSGreaterThanEqual, true, true, IR(172, 4), IR(32481, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpULessThan, true, true, IR(172, 4), IR(32499, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSLessThan, true, true, IR(172, 4), IR(32509, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpULessThanEqual, true, true, IR(172, 4), IR(32519, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSLessThanEqual, true, true, IR(172, 4), IR(32534, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdEqual, true, true, IR(172, 4), IR(32549, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordEqual, true, true, IR(172, 4), IR(32559, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdNotEqual, true, true, IR(172, 4), IR(32571, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordNotEqual, true, true, IR(172, 4), IR(32584, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdLessThan, true, true, IR(172, 4), IR(32599, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordLessThan, true, true, IR(172, 4), IR(32612, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdGreaterThan, true, true, IR(172, 4), IR(32627, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordGreaterThan, true, true, IR(172, 4), IR(32643, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdLessThanEqual, true, true, IR(172, 4), IR(32661, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordLessThanEqual, true, true, IR(172, 4), IR(32679, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdGreaterThanEqual, true, true, IR(172, 4), IR(32699, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordGreaterThanEqual, true, true, IR(172, 4), IR(32720, 23), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpShiftRightLogical, true, true, IR(172, 4), IR(32743, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpShiftRightArithmetic, true, true, IR(172, 4), IR(32761, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpShiftLeftLogical, true, true, IR(172, 4), IR(32782, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseOr, true, true, IR(172, 4), IR(32799, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseXor, true, true, IR(172, 4), IR(32809, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseAnd, true, true, IR(172, 4), IR(32820, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpNot, true, true, IR(160, 3), IR(32831, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldInsert, true, true, IR(215, 6), IR(32835, 15), IR(0, 0), IR(234, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldSExtract, true, true, IR(130, 5), IR(32850, 17), IR(0, 0), IR(234, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldUExtract, true, true, IR(130, 5), IR(32867, 17), IR(0, 0), IR(234, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitReverse, true, true, IR(160, 3), IR(32884, 11), IR(0, 0), IR(234, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitCount, true, true, IR(160, 3), IR(32895, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpDPdx, true, true, IR(160, 3), IR(32904, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdy, true, true, IR(160, 3), IR(32909, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidth, true, true, IR(160, 3), IR(32914, 7), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdxFine, true, true, IR(160, 3), IR(32921, 9), IR(0, 0), IR(236, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdyFine, true, true, IR(160, 3), IR(32930, 9), IR(0, 0), IR(236, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidthFine, true, true, IR(160, 3), IR(32939, 11), IR(0, 0), IR(236, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdxCoarse, true, true, IR(160, 3), IR(32950, 11), IR(0, 0), IR(236, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdyCoarse, true, true, IR(160, 3), IR(32961, 11), IR(0, 0), IR(236, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidthCoarse, true, true, IR(160, 3), IR(32972, 13), IR(0, 0), IR(236, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpEmitVertex, false, false, IR(0, 0), IR(32985, 11), IR(0, 0), IR(70, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEndPrimitive, false, false, IR(0, 0), IR(32996, 13), IR(0, 0), IR(70, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEmitStreamVertex, false, false, IR(10, 1), IR(33009, 17), IR(0, 0), IR(123, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEndStreamPrimitive, false, false, IR(10, 1), IR(33026, 19), IR(0, 0), IR(123, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpControlBarrier, false, false, IR(221, 3), IR(33082, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpMemoryBarrier, false, false, IR(224, 2), IR(33097, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpAtomicLoad, true, true, IR(226, 5), IR(33111, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicStore, false, false, IR(231, 4), IR(33122, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicExchange, true, true, IR(235, 6), IR(33134, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicCompareExchange, true, true, IR(241, 8), IR(33149, 22), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicCompareExchangeWeak, true, true, IR(241, 8), IR(33171, 26), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), SPV_SPIRV_VERSION_WORD(1,3), PrintingClass::kAtomic},
  {spv::Op::OpAtomicIIncrement, true, true, IR(226, 5), IR(33197, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicIDecrement, true, true, IR(226, 5), IR(33214, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicIAdd, true, true, IR(235, 6), IR(33231, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicISub, true, true, IR(235, 6), IR(33242, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicSMin, true, true, IR(235, 6), IR(33253, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicUMin, true, true, IR(235, 6), IR(33264, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicSMax, true, true, IR(235, 6), IR(33275, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicUMax, true, true, IR(235, 6), IR(33286, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicAnd, true, true, IR(235, 6), IR(33297, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicOr, true, true, IR(235, 6), IR(33307, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicXor, true, true, IR(235, 6), IR(33316, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpPhi, true, true, IR(107, 3), IR(33326, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLoopMerge, false, false, IR(249, 3), IR(33360, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpSelectionMerge, false, false, IR(252, 2), IR(33405, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLabel, true, false, IR(68, 1), IR(33420, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpBranch, false, false, IR(10, 1), IR(33426, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpBranchConditional, false, false, IR(254, 4), IR(33433, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpSwitch, false, false, IR(258, 3), IR(33496, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpKill, false, false, IR(0, 0), IR(33503, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpReturn, false, false, IR(0, 0), IR(33508, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpReturnValue, false, false, IR(10, 1), IR(33515, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpUnreachable, false, false, IR(0, 0), IR(33527, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLifetimeStart, false, false, IR(261, 2), IR(33539, 14), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLifetimeStop, false, false, IR(261, 2), IR(33553, 13), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpGroupAsyncCopy, true, true, IR(263, 8), IR(33566, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupWaitEvents, false, false, IR(271, 3), IR(33581, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupAll, true, true, IR(274, 4), IR(33597, 9), IR(0, 0), IR(237, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupAny, true, true, IR(274, 4), IR(33606, 9), IR(0, 0), IR(237, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBroadcast, true, true, IR(278, 5), IR(33615, 15), IR(0, 0), IR(237, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupIAdd, true, true, IR(283, 5), IR(33663, 10), IR(0, 0), IR(237, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFAdd, true, true, IR(283, 5), IR(33673, 10), IR(0, 0), IR(237, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMin, true, true, IR(283, 5), IR(33683, 10), IR(0, 0), IR(237, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMin, true, true, IR(283, 5), IR(33693, 10), IR(0, 0), IR(237, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMin, true, true, IR(283, 5), IR(33703, 10), IR(0, 0), IR(237, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMax, true, true, IR(283, 5), IR(33713, 10), IR(0, 0), IR(237, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMax, true, true, IR(283, 5), IR(33723, 10), IR(0, 0), IR(237, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMax, true, true, IR(283, 5), IR(33733, 10), IR(0, 0), IR(237, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpReadPipe, true, true, IR(215, 6), IR(33743, 9), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpWritePipe, true, true, IR(215, 6), IR(33752, 10), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReservedReadPipe, true, true, IR(288, 8), IR(33762, 17), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReservedWritePipe, true, true, IR(288, 8), IR(33779, 18), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReserveReadPipePackets, true, true, IR(215, 6), IR(33797, 23), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReserveWritePipePackets, true, true, IR(215, 6), IR(33820, 24), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCommitReadPipe, false, false, IR(296, 4), IR(33844, 15), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCommitWritePipe, false, false, IR(296, 4), IR(33859, 16), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpIsValidReserveId, true, true, IR(160, 3), IR(33875, 17), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetNumPipePackets, true, true, IR(130, 5), IR(33892, 18), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetMaxPipePackets, true, true, IR(130, 5), IR(33910, 18), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupReserveReadPipePackets, true, true, IR(300, 7), IR(33928, 28), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupReserveWritePipePackets, true, true, IR(300, 7), IR(33956, 29), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupCommitReadPipe, false, false, IR(307, 5), IR(33985, 20), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupCommitWritePipe, false, false, IR(307, 5), IR(34005, 21), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpEnqueueMarker, true, true, IR(215, 6), IR(34026, 14), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpEnqueueKernel, true, true, IR(312, 13), IR(34040, 14), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelNDrangeSubGroupCount, true, true, IR(325, 7), IR(34054, 30), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelNDrangeMaxSubGroupSize, true, true, IR(325, 7), IR(34084, 32), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelWorkGroupSize, true, true, IR(215, 6), IR(34116, 23), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelPreferredWorkGroupSizeMultiple, true, true, IR(215, 6), IR(34139, 40), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpRetainEvent, false, false, IR(10, 1), IR(34179, 12), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpReleaseEvent, false, false, IR(10, 1), IR(34191, 13), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpCreateUserEvent, true, true, IR(39, 2), IR(34204, 16), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpIsValidEvent, true, true, IR(160, 3), IR(34220, 13), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpSetUserEventStatus, false, false, IR(36, 2), IR(34233, 19), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpCaptureEventProfilingInfo, false, false, IR(33, 3), IR(34252, 26), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetDefaultQueue, true, true, IR(39, 2), IR(34278, 16), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpBuildNDRange, true, true, IR(130, 5), IR(34294, 13), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpImageSparseSampleImplicitLod, true, true, IR(185, 5), IR(34307, 29), IR(0, 0), IR(238, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleExplicitLod, true, true, IR(190, 5), IR(34336, 29), IR(0, 0), IR(238, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleDrefImplicitLod, true, true, IR(195, 6), IR(34365, 33), IR(0, 0), IR(238, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleDrefExplicitLod, true, true, IR(201, 6), IR(34398, 33), IR(0, 0), IR(238, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjImplicitLod, true, true, IR(185, 5), IR(34431, 33), IR(0, 0), IR(238, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjExplicitLod, true, true, IR(190, 5), IR(34464, 33), IR(0, 0), IR(238, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjDrefImplicitLod, true, true, IR(195, 6), IR(34497, 37), IR(0, 0), IR(238, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjDrefExplicitLod, true, true, IR(201, 6), IR(34534, 37), IR(0, 0), IR(238, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseFetch, true, true, IR(185, 5), IR(34571, 17), IR(0, 0), IR(238, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseGather, true, true, IR(195, 6), IR(34588, 18), IR(0, 0), IR(238, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseDrefGather, true, true, IR(195, 6), IR(34606, 22), IR(0, 0), IR(238, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseTexelsResident, true, true, IR(160, 3), IR(34628, 26), IR(0, 0), IR(238, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpNoLine, false, false, IR(0, 0), IR(34654, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpAtomicFlagTestAndSet, true, true, IR(226, 5), IR(34661, 21), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicFlagClear, false, false, IR(332, 3), IR(34682, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpImageSparseRead, true, true, IR(185, 5), IR(34698, 16), IR(0, 0), IR(238, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpSizeOf, true, true, IR(160, 3), IR(34714, 7), IR(0, 0), IR(1, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpTypePipeStorage, true, false, IR(68, 1), IR(34721, 16), IR(0, 0), IR(239, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantPipeStorage, true, true, IR(335, 5), IR(34737, 20), IR(0, 0), IR(239, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCreatePipeFromPipeStorage, true, true, IR(160, 3), IR(34757, 26), IR(0, 0), IR(239, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetKernelLocalSizeForSubgroupCount, true, true, IR(325, 7), IR(34783, 35), IR(0, 0), IR(165, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelMaxNumSubgroups, true, true, IR(215, 6), IR(34818, 25), IR(0, 0), IR(165, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpTypeNamedBarrier, true, false, IR(68, 1), IR(34843, 17), IR(0, 0), IR(240, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpNamedBarrierInitialize, true, true, IR(160, 3), IR(34860, 23), IR(0, 0), IR(240, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpMemoryNamedBarrier, false, false, IR(332, 3), IR(34883, 19), IR(0, 0), IR(240, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpModuleProcessed, false, false, IR(11, 1), IR(34902, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpExecutionModeId, false, false, IR(65, 2), IR(34918, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,2), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpDecorateId, false, false, IR(163, 2), IR(34934, 11), IR(0, 0), IR(1, 0), IR(204, 1), SPV_SPIRV_VERSION_WORD(1,2), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupNonUniformElect, true, true, IR(340, 3), IR(34945, 21), IR(0, 0), IR(77, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAll, true, true, IR(274, 4), IR(34966, 19), IR(0, 0), IR(241, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAny, true, true, IR(274, 4), IR(34985, 19), IR(0, 0), IR(241, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAllEqual, true, true, IR(274, 4), IR(35004, 24), IR(0, 0), IR(241, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBroadcast, true, true, IR(278, 5), IR(35028, 25), IR(0, 0), IR(242, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBroadcastFirst, true, true, IR(274, 4), IR(35053, 30), IR(0, 0), IR(242, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallot, true, true, IR(274, 4), IR(6935, 22), IR(0, 0), IR(242, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformInverseBallot, true, true, IR(274, 4), IR(35083, 29), IR(0, 0), IR(242, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotBitExtract, true, true, IR(278, 5), IR(35112, 32), IR(0, 0), IR(242, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotBitCount, true, true, IR(283, 5), IR(35144, 30), IR(0, 0), IR(242, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotFindLSB, true, true, IR(274, 4), IR(35174, 29), IR(0, 0), IR(242, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotFindMSB, true, true, IR(274, 4), IR(35203, 29), IR(0, 0), IR(242, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffle, true, true, IR(278, 5), IR(10074, 23), IR(0, 0), IR(243, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleXor, true, true, IR(278, 5), IR(35232, 26), IR(0, 0), IR(243, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleUp, true, true, IR(278, 5), IR(35258, 25), IR(0, 0), IR(244, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleDown, true, true, IR(278, 5), IR(35283, 27), IR(0, 0), IR(244, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformIAdd, true, true, IR(343, 6), IR(35310, 20), IR(0, 0), IR(245, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFAdd, true, true, IR(343, 6), IR(35330, 20), IR(0, 0), IR(245, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformIMul, true, true, IR(343, 6), IR(35350, 20), IR(0, 0), IR(245, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMul, true, true, IR(343, 6), IR(35370, 20), IR(0, 0), IR(245, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformSMin, true, true, IR(343, 6), IR(35390, 20), IR(0, 0), IR(245, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformUMin, true, true, IR(343, 6), IR(35410, 20), IR(0, 0), IR(245, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMin, true, true, IR(343, 6), IR(35430, 20), IR(0, 0), IR(245, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformSMax, true, true, IR(343, 6), IR(35450, 20), IR(0, 0), IR(245, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformUMax, true, true, IR(343, 6), IR(35470, 20), IR(0, 0), IR(245, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMax, true, true, IR(343, 6), IR(35490, 20), IR(0, 0), IR(245, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseAnd, true, true, IR(343, 6), IR(35510, 26), IR(0, 0), IR(245, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseOr, true, true, IR(343, 6), IR(35536, 25), IR(0, 0), IR(245, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseXor, true, true, IR(343, 6), IR(35561, 26), IR(0, 0), IR(245, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalAnd, true, true, IR(343, 6), IR(35587, 26), IR(0, 0), IR(245, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalOr, true, true, IR(343, 6), IR(35613, 25), IR(0, 0), IR(245, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalXor, true, true, IR(343, 6), IR(35638, 26), IR(0, 0), IR(245, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadBroadcast, true, true, IR(278, 5), IR(35664, 29), IR(0, 0), IR(248, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadSwap, true, true, IR(278, 5), IR(35693, 24), IR(0, 0), IR(248, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpCopyLogical, true, true, IR(160, 3), IR(35717, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpPtrEqual, true, true, IR(172, 4), IR(35729, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrNotEqual, true, true, IR(172, 4), IR(35738, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrDiff, true, true, IR(172, 4), IR(35750, 8), IR(0, 0), IR(249, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpColorAttachmentReadEXT, true, true, IR(349, 4), IR(35758, 23), IR(0, 0), IR(157, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpDepthAttachmentReadEXT, true, true, IR(353, 3), IR(35781, 23), IR(0, 0), IR(166, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpStencilAttachmentReadEXT, true, true, IR(353, 3), IR(35804, 25), IR(0, 0), IR(167, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpTypeTensorARM, true, false, IR(356, 4), IR(35829, 14), IR(0, 0), IR(221, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTensorReadARM, true, true, IR(360, 5), IR(35885, 14), IR(0, 0), IR(221, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpTensorWriteARM, false, false, IR(365, 4), IR(35899, 15), IR(0, 0), IR(221, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpTensorQuerySizeARM, true, true, IR(172, 4), IR(35914, 19), IR(0, 0), IR(221, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpGraphConstantARM, true, true, IR(369, 3), IR(35933, 17), IR(0, 0), IR(252, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphEntryPointARM, false, false, IR(372, 3), IR(35950, 19), IR(0, 0), IR(252, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphARM, true, true, IR(39, 2), IR(10365, 9), IR(0, 0), IR(252, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphInputARM, true, true, IR(122, 4), IR(35969, 14), IR(0, 0), IR(252, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphSetOutputARM, false, false, IR(375, 3), IR(35983, 18), IR(0, 0), IR(252, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphEndARM, false, false, IR(0, 0), IR(36001, 12), IR(0, 0), IR(252, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpTypeGraphARM, true, false, IR(378, 3), IR(36013, 13), IR(0, 0), IR(252, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpBitcastExtractEXT, true, true, IR(172, 4), IR(10512, 18), IR(0, 0), IR(253, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpTerminateInvocation, false, false, IR(0, 0), IR(36026, 20), IR(0, 0), IR(3, 1), IR(214, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpTypeUntypedPointerKHR, true, false, IR(381, 2), IR(36046, 22), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpUntypedVariableKHR, true, true, IR(383, 5), IR(36068, 19), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedAccessChainKHR, true, true, IR(151, 5), IR(36087, 22), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedInBoundsAccessChainKHR, true, true, IR(151, 5), IR(36109, 30), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpSubgroupBallotKHR, true, true, IR(160, 3), IR(6696, 18), IR(0, 0), IR(254, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupFirstInvocationKHR, true, true, IR(160, 3), IR(36139, 27), IR(0, 0), IR(254, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpUntypedPtrAccessChainKHR, true, true, IR(388, 6), IR(36166, 25), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedInBoundsPtrAccessChainKHR, true, true, IR(388, 6), IR(36191, 33), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedArrayLengthKHR, true, true, IR(394, 5), IR(36224, 22), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedPrefetchKHR, false, false, IR(399, 5), IR(36246, 19), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpFmaKHR, true, true, IR(130, 5), IR(36265, 7), IR(0, 0), IR(255, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSubgroupAllKHR, true, true, IR(160, 3), IR(36272, 15), IR(0, 0), IR(256, 1), IR(42, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupAnyKHR, true, true, IR(160, 3), IR(36287, 15), IR(0, 0), IR(256, 1), IR(42, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupAllEqualKHR, true, true, IR(160, 3), IR(36302, 20), IR(0, 0), IR(256, 1), IR(42, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupNonUniformRotateKHR, true, true, IR(404, 6), IR(15546, 25), IR(0, 0), IR(257, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupReadInvocationKHR, true, true, IR(172, 4), IR(36322, 26), IR(0, 0), IR(254, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpExtInstWithForwardRefsKHR, true, true, IR(410, 5), IR(36348, 26), IR(0, 0), IR(1, 0), IR(215, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpUntypedGroupAsyncCopyKHR, true, true, IR(415, 11), IR(36374, 25), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpTraceRayKHR, false, false, IR(426, 11), IR(36399, 12), IR(0, 0), IR(61, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpExecuteCallableKHR, false, false, IR(36, 2), IR(36411, 19), IR(0, 0), IR(61, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToAccelerationStructureKHR, true, true, IR(160, 3), IR(36430, 35), IR(0, 0), IR(258, 2), IR(216, 2), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIgnoreIntersectionKHR, false, false, IR(0, 0), IR(36465, 22), IR(0, 0), IR(61, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTerminateRayKHR, false, false, IR(0, 0), IR(36487, 16), IR(0, 0), IR(61, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSDot, true, true, IR(437, 5), IR(36550, 5), IR(176, 1), IR(260, 1), IR(158, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDot, true, true, IR(437, 5), IR(36563, 5), IR(177, 1), IR(260, 1), IR(158, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSUDot, true, true, IR(437, 5), IR(36576, 6), IR(178, 1), IR(260, 1), IR(158, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSDotAccSat, true, true, IR(442, 6), IR(36591, 11), IR(179, 1), IR(260, 1), IR(158, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDotAccSat, true, true, IR(442, 6), IR(36616, 11), IR(180, 1), IR(260, 1), IR(158, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSUDotAccSat, true, true, IR(442, 6), IR(36641, 12), IR(181, 1), IR(260, 1), IR(158, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpTypeCooperativeMatrixKHR, true, false, IR(448, 6), IR(36668, 25), IR(0, 0), IR(87, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeMatrixLoadKHR, true, true, IR(454, 6), IR(36693, 25), IR(0, 0), IR(87, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixStoreKHR, false, false, IR(460, 5), IR(36718, 26), IR(0, 0), IR(87, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixMulAddKHR, true, true, IR(465, 6), IR(36798, 27), IR(0, 0), IR(87, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpCooperativeMatrixLengthKHR, true, true, IR(160, 3), IR(36825, 27), IR(0, 0), IR(87, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpConstantCompositeReplicateEXT, true, true, IR(160, 3), IR(36852, 30), IR(0, 0), IR(261, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCompositeReplicateEXT, true, true, IR(160, 3), IR(36882, 34), IR(0, 0), IR(261, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpCompositeConstructReplicateEXT, true, true, IR(160, 3), IR(36916, 31), IR(0, 0), IR(261, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpTypeRayQueryKHR, true, false, IR(68, 1), IR(36947, 16), IR(0, 0), IR(211, 1), IR(49, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpRayQueryInitializeKHR, false, false, IR(471, 8), IR(36963, 22), IR(0, 0), IR(211, 1), IR(49, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryTerminateKHR, false, false, IR(10, 1), IR(36985, 21), IR(0, 0), IR(211, 1), IR(49, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGenerateIntersectionKHR, false, false, IR(36, 2), IR(37006, 32), IR(0, 0), IR(211, 1), IR(49, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryConfirmIntersectionKHR, false, false, IR(10, 1), IR(37038, 31), IR(0, 0), IR(211, 1), IR(49, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryProceedKHR, true, true, IR(160, 3), IR(37069, 19), IR(0, 0), IR(211, 1), IR(49, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTypeKHR, true, true, IR(172, 4), IR(37088, 31), IR(0, 0), IR(211, 1), IR(49, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpImageSampleWeightedQCOM, true, true, IR(130, 5), IR(37119, 24), IR(0, 0), IR(262, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBoxFilterQCOM, true, true, IR(130, 5), IR(37143, 19), IR(0, 0), IR(263, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchSSDQCOM, true, true, IR(325, 7), IR(37162, 23), IR(0, 0), IR(264, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchSADQCOM, true, true, IR(325, 7), IR(37185, 23), IR(0, 0), IR(264, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpBitCastArrayQCOM, true, true, IR(160, 3), IR(37208, 17), IR(0, 0), IR(265, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpImageBlockMatchWindowSSDQCOM, true, true, IR(325, 7), IR(37225, 29), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchWindowSADQCOM, true, true, IR(325, 7), IR(37254, 29), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchGatherSSDQCOM, true, true, IR(325, 7), IR(37283, 29), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchGatherSADQCOM, true, true, IR(325, 7), IR(37312, 29), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpBFloat16MulAddQCOM, true, true, IR(130, 5), IR(11285, 19), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpCompositeConstructCoopMatQCOM, true, true, IR(160, 3), IR(37341, 30), IR(0, 0), IR(265, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeExtractCoopMatQCOM, true, true, IR(160, 3), IR(37371, 28), IR(0, 0), IR(265, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpExtractSubArrayQCOM, true, true, IR(172, 4), IR(37399, 20), IR(0, 0), IR(265, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpImageGatherQCOM, true, true, IR(479, 7), IR(37419, 16), IR(0, 0), IR(268, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpGroupIAddNonUniformAMD, true, true, IR(283, 5), IR(37435, 23), IR(0, 0), IR(237, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFAddNonUniformAMD, true, true, IR(283, 5), IR(37458, 23), IR(0, 0), IR(237, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMinNonUniformAMD, true, true, IR(283, 5), IR(37481, 23), IR(0, 0), IR(237, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMinNonUniformAMD, true, true, IR(283, 5), IR(37504, 23), IR(0, 0), IR(237, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMinNonUniformAMD, true, true, IR(283, 5), IR(37527, 23), IR(0, 0), IR(237, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMaxNonUniformAMD, true, true, IR(283, 5), IR(37550, 23), IR(0, 0), IR(237, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMaxNonUniformAMD, true, true, IR(283, 5), IR(37573, 23), IR(0, 0), IR(237, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMaxNonUniformAMD, true, true, IR(283, 5), IR(37596, 23), IR(0, 0), IR(237, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpFragmentMaskFetchAMD, true, true, IR(172, 4), IR(37619, 21), IR(0, 0), IR(270, 1), IR(63, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFragmentFetchAMD, true, true, IR(130, 5), IR(37640, 17), IR(0, 0), IR(270, 1), IR(63, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReadClockKHR, true, true, IR(340, 3), IR(37657, 13), IR(0, 0), IR(271, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAllocateNodePayloadsAMDX, true, true, IR(278, 5), IR(37670, 25), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpEnqueueNodePayloadsAMDX, false, false, IR(10, 1), IR(37695, 24), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeNodePayloadArrayAMDX, true, false, IR(87, 2), IR(37719, 25), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFinishWritingNodePayloadAMDX, true, true, IR(160, 3), IR(37744, 29), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpNodePayloadArrayLengthAMDX, true, true, IR(160, 3), IR(37773, 27), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIsNodePayloadValidAMDX, true, true, IR(172, 4), IR(37800, 23), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConstantStringAMDX, true, false, IR(50, 2), IR(37823, 19), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSpecConstantStringAMDX, true, false, IR(50, 2), IR(37842, 23), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpGroupNonUniformQuadAllKHR, true, true, IR(160, 3), IR(37865, 26), IR(0, 0), IR(175, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadAnyKHR, true, true, IR(160, 3), IR(37891, 26), IR(0, 0), IR(175, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpTypeBufferEXT, true, false, IR(381, 2), IR(37917, 14), IR(0, 0), IR(44, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpBufferPointerEXT, true, true, IR(160, 3), IR(37931, 17), IR(0, 0), IR(44, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpAbortKHR, false, false, IR(36, 2), IR(11622, 9), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpUntypedImageTexelPointerEXT, true, true, IR(215, 6), IR(37948, 28), IR(0, 0), IR(44, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpMemberDecorateIdEXT, false, false, IR(165, 3), IR(37976, 20), IR(0, 0), IR(44, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpConstantSizeOfEXT, true, true, IR(160, 3), IR(37996, 18), IR(0, 0), IR(44, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantDataKHR, true, true, IR(486, 3), IR(11631, 16), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantDataKHR, true, true, IR(486, 3), IR(38014, 20), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpPoisonKHR, true, true, IR(39, 2), IR(38034, 10), IR(0, 0), IR(176, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpFreezeKHR, true, true, IR(160, 3), IR(38044, 10), IR(0, 0), IR(176, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpHitObjectRecordHitMotionNV, false, false, IR(489, 14), IR(38054, 27), IR(0, 0), IR(273, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitWithIndexMotionNV, false, false, IR(503, 13), IR(38081, 36), IR(0, 0), IR(273, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissMotionNV, false, false, IR(516, 7), IR(38117, 28), IR(0, 0), IR(273, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldToObjectNV, true, true, IR(160, 3), IR(38145, 28), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectToWorldNV, true, true, IR(160, 3), IR(38173, 28), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayDirectionNV, true, true, IR(160, 3), IR(38201, 33), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayOriginNV, true, true, IR(160, 3), IR(38234, 30), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayMotionNV, false, false, IR(503, 13), IR(38264, 26), IR(0, 0), IR(273, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderRecordBufferHandleNV, true, true, IR(160, 3), IR(38290, 39), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderBindingTableRecordIndexNV, true, true, IR(160, 3), IR(38329, 44), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordEmptyNV, false, false, IR(10, 1), IR(38373, 23), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayNV, false, false, IR(523, 12), IR(38396, 20), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitNV, false, false, IR(503, 13), IR(38416, 21), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitWithIndexNV, false, false, IR(523, 12), IR(38437, 30), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissNV, false, false, IR(535, 6), IR(38467, 22), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectExecuteShaderNV, false, false, IR(36, 2), IR(38489, 25), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetCurrentTimeNV, true, true, IR(160, 3), IR(38514, 26), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetAttributesNV, false, false, IR(36, 2), IR(38540, 25), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetHitKindNV, true, true, IR(160, 3), IR(38565, 22), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetPrimitiveIndexNV, true, true, IR(160, 3), IR(38587, 29), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetGeometryIndexNV, true, true, IR(160, 3), IR(38616, 28), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceIdNV, true, true, IR(160, 3), IR(38644, 25), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceCustomIndexNV, true, true, IR(160, 3), IR(38669, 34), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayDirectionNV, true, true, IR(160, 3), IR(38703, 32), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayOriginNV, true, true, IR(160, 3), IR(38735, 29), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMaxNV, true, true, IR(160, 3), IR(38764, 22), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMinNV, true, true, IR(160, 3), IR(38786, 22), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsEmptyNV, true, true, IR(160, 3), IR(38808, 19), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsHitNV, true, true, IR(160, 3), IR(38827, 17), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsMissNV, true, true, IR(160, 3), IR(38844, 18), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHitObjectNV, false, false, IR(541, 3), IR(38862, 29), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHintNV, false, false, IR(36, 2), IR(38891, 24), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeHitObjectNV, true, false, IR(68, 1), IR(38915, 16), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpImageSampleFootprintNV, true, true, IR(479, 7), IR(38931, 23), IR(0, 0), IR(275, 1), IR(82, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpTypeVectorIdEXT, true, false, IR(89, 3), IR(38954, 16), IR(182, 1), IR(276, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeVectorMatrixMulNV, true, true, IR(544, 13), IR(38994, 29), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorOuterProductAccumulateNV, false, false, IR(557, 7), IR(39023, 42), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorReduceSumAccumulateNV, false, false, IR(33, 3), IR(39065, 39), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorMatrixMulAddNV, true, true, IR(564, 16), IR(39104, 32), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixConvertUseEXT, true, true, IR(160, 3), IR(39136, 31), IR(183, 1), IR(280, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpEmitMeshTasksEXT, false, false, IR(580, 4), IR(39194, 17), IR(0, 0), IR(54, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSetMeshOutputsEXT, false, false, IR(36, 2), IR(39211, 18), IR(0, 0), IR(54, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpGroupNonUniformPartitionEXT, true, true, IR(160, 3), IR(39229, 28), IR(184, 1), IR(201, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpWritePackedPrimitiveIndices4x8NV, false, false, IR(36, 2), IR(39284, 33), IR(0, 0), IR(51, 1), IR(18, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFetchMicroTriangleVertexPositionNV, true, true, IR(325, 7), IR(39317, 35), IR(0, 0), IR(282, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFetchMicroTriangleVertexBarycentricNV, true, true, IR(325, 7), IR(39352, 38), IR(0, 0), IR(282, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorLoadNV, true, true, IR(584, 5), IR(39390, 24), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeVectorStoreNV, false, false, IR(589, 4), IR(39414, 25), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpHitObjectRecordFromQueryEXT, false, false, IR(593, 5), IR(39439, 28), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissEXT, false, false, IR(516, 7), IR(39467, 23), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissMotionEXT, false, false, IR(471, 8), IR(39490, 29), IR(0, 0), IR(283, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetIntersectionTriangleVertexPositionsEXT, true, true, IR(160, 3), IR(39519, 51), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayFlagsEXT, true, true, IR(160, 3), IR(39570, 24), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectSetShaderBindingTableRecordIndexEXT, false, false, IR(36, 2), IR(39594, 45), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectReorderExecuteShaderEXT, false, false, IR(598, 4), IR(39639, 33), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceReorderExecuteEXT, false, false, IR(602, 14), IR(39672, 32), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceMotionReorderExecuteEXT, false, false, IR(616, 15), IR(39704, 38), IR(0, 0), IR(283, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeHitObjectEXT, true, false, IR(68, 1), IR(39742, 17), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpReorderThreadWithHintEXT, false, false, IR(36, 2), IR(39759, 25), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHitObjectEXT, false, false, IR(541, 3), IR(39784, 30), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayEXT, false, false, IR(523, 12), IR(39814, 21), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayMotionEXT, false, false, IR(503, 13), IR(39835, 27), IR(0, 0), IR(283, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordEmptyEXT, false, false, IR(10, 1), IR(39862, 24), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectExecuteShaderEXT, false, false, IR(36, 2), IR(39886, 26), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetCurrentTimeEXT, true, true, IR(160, 3), IR(39912, 27), IR(0, 0), IR(283, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetAttributesEXT, false, false, IR(36, 2), IR(39939, 26), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetHitKindEXT, true, true, IR(160, 3), IR(39965, 23), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetPrimitiveIndexEXT, true, true, IR(160, 3), IR(39988, 30), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetGeometryIndexEXT, true, true, IR(160, 3), IR(40018, 29), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceIdEXT, true, true, IR(160, 3), IR(40047, 26), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceCustomIndexEXT, true, true, IR(160, 3), IR(40073, 35), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayOriginEXT, true, true, IR(160, 3), IR(40108, 31), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayDirectionEXT, true, true, IR(160, 3), IR(40139, 34), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayDirectionEXT, true, true, IR(160, 3), IR(40173, 33), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayOriginEXT, true, true, IR(160, 3), IR(40206, 30), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectToWorldEXT, true, true, IR(160, 3), IR(40236, 29), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldToObjectEXT, true, true, IR(160, 3), IR(40265, 29), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMaxEXT, true, true, IR(160, 3), IR(40294, 23), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReportIntersectionKHR, true, true, IR(172, 4), IR(40317, 22), IR(185, 1), IR(55, 2), IR(24, 2), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIgnoreIntersectionNV, false, false, IR(0, 0), IR(40360, 21), IR(0, 0), IR(57, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTerminateRayNV, false, false, IR(0, 0), IR(40381, 15), IR(0, 0), IR(57, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceNV, false, false, IR(426, 11), IR(40396, 8), IR(0, 0), IR(57, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceMotionNV, false, false, IR(523, 12), IR(40404, 14), IR(0, 0), IR(58, 1), IR(27, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceRayMotionNV, false, false, IR(523, 12), IR(40418, 17), IR(0, 0), IR(58, 1), IR(27, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTriangleVertexPositionsKHR, true, true, IR(172, 4), IR(40435, 50), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeAccelerationStructureKHR, true, false, IR(68, 1), IR(40485, 29), IR(186, 1), IR(286, 4), IR(218, 4), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpExecuteCallableNV, false, false, IR(36, 2), IR(40542, 18), IR(0, 0), IR(57, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionClusterIdNV, true, true, IR(172, 4), IR(40560, 35), IR(187, 1), IR(65, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetClusterIdNV, true, true, IR(160, 3), IR(40618, 24), IR(0, 0), IR(65, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMinEXT, true, true, IR(160, 3), IR(40642, 23), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderBindingTableRecordIndexEXT, true, true, IR(160, 3), IR(40665, 45), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderRecordBufferHandleEXT, true, true, IR(160, 3), IR(40710, 40), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsEmptyEXT, true, true, IR(160, 3), IR(40750, 20), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsHitEXT, true, true, IR(160, 3), IR(40770, 18), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsMissEXT, true, true, IR(160, 3), IR(40788, 19), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeCooperativeMatrixNV, true, false, IR(631, 5), IR(40807, 24), IR(0, 0), IR(290, 1), IR(90, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeMatrixLoadNV, true, true, IR(636, 6), IR(40831, 24), IR(0, 0), IR(290, 1), IR(90, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixStoreNV, false, false, IR(642, 5), IR(40855, 25), IR(0, 0), IR(290, 1), IR(90, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixMulAddNV, true, true, IR(130, 5), IR(40880, 26), IR(0, 0), IR(290, 1), IR(90, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixLengthNV, true, true, IR(160, 3), IR(40906, 26), IR(0, 0), IR(290, 1), IR(90, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixGetCoordinateEXT, true, true, IR(172, 4), IR(13808, 34), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpBeginInvocationInterlockEXT, false, false, IR(0, 0), IR(40932, 28), IR(0, 0), IR(292, 3), IR(91, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpEndInvocationInterlockEXT, false, false, IR(0, 0), IR(40960, 26), IR(0, 0), IR(292, 3), IR(91, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixReduceEXT, true, true, IR(647, 5), IR(41029, 27), IR(188, 1), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpCooperativeMatrixLoadTensorNV, true, true, IR(652, 7), IR(41157, 30), IR(0, 0), IR(219, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixStoreTensorNV, false, false, IR(659, 5), IR(41187, 31), IR(0, 0), IR(219, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixPerElementOpEXT, true, true, IR(151, 5), IR(41218, 33), IR(189, 1), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpTypeTensorLayoutNV, true, false, IR(89, 3), IR(41283, 19), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeTensorViewNV, true, false, IR(664, 4), IR(41302, 17), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCreateTensorLayoutNV, true, true, IR(39, 2), IR(41319, 21), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetDimensionNV, true, true, IR(122, 4), IR(41340, 27), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetStrideNV, true, true, IR(122, 4), IR(41367, 24), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSliceNV, true, true, IR(122, 4), IR(41391, 20), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetClampValueNV, true, true, IR(172, 4), IR(41411, 28), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCreateTensorViewNV, true, true, IR(39, 2), IR(41439, 19), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetDimensionNV, true, true, IR(122, 4), IR(41458, 25), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetStrideNV, true, true, IR(122, 4), IR(41483, 22), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpDemoteToHelperInvocation, false, false, IR(0, 0), IR(13162, 25), IR(46, 1), IR(298, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpIsHelperInvocationEXT, true, true, IR(39, 2), IR(41505, 22), IR(0, 0), IR(298, 1), IR(92, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetClipNV, true, true, IR(325, 7), IR(41527, 20), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetBlockSizeNV, true, true, IR(122, 4), IR(41547, 27), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixTransposeNV, true, true, IR(160, 3), IR(41574, 29), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToImageNV, true, true, IR(160, 3), IR(41603, 18), IR(0, 0), IR(135, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToSamplerNV, true, true, IR(160, 3), IR(41621, 20), IR(0, 0), IR(135, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertImageToUNV, true, true, IR(160, 3), IR(41641, 18), IR(0, 0), IR(135, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertSamplerToUNV, true, true, IR(160, 3), IR(41659, 20), IR(0, 0), IR(135, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToSampledImageNV, true, true, IR(160, 3), IR(41679, 25), IR(0, 0), IR(135, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertSampledImageToUNV, true, true, IR(160, 3), IR(41704, 25), IR(0, 0), IR(135, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSamplerImageAddressingModeNV, false, false, IR(0, 1), IR(41729, 29), IR(0, 0), IR(135, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRawAccessChainNV, true, true, IR(668, 7), IR(41810, 17), IR(0, 0), IR(208, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpRayQueryGetIntersectionSpherePositionNV, true, true, IR(172, 4), IR(41827, 40), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionSphereRadiusNV, true, true, IR(172, 4), IR(41867, 38), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSPositionsNV, true, true, IR(172, 4), IR(41905, 38), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSRadiiNV, true, true, IR(172, 4), IR(41943, 34), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSHitValueNV, true, true, IR(172, 4), IR(41977, 37), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetSpherePositionNV, true, true, IR(160, 3), IR(42014, 29), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetSphereRadiusNV, true, true, IR(160, 3), IR(42043, 27), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetLSSPositionsNV, true, true, IR(160, 3), IR(42070, 27), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetLSSRadiiNV, true, true, IR(160, 3), IR(42097, 23), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsSphereHitNV, true, true, IR(160, 3), IR(42120, 23), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsLSSHitNV, true, true, IR(160, 3), IR(42143, 20), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryIsSphereHitNV, true, true, IR(172, 4), IR(42163, 22), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryIsLSSHitNV, true, true, IR(172, 4), IR(42185, 19), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSubgroupShuffleINTEL, true, true, IR(172, 4), IR(13893, 21), IR(0, 0), IR(300, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleDownINTEL, true, true, IR(130, 5), IR(42204, 25), IR(0, 0), IR(300, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleUpINTEL, true, true, IR(130, 5), IR(42229, 23), IR(0, 0), IR(300, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleXorINTEL, true, true, IR(172, 4), IR(42252, 24), IR(0, 0), IR(300, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupBlockReadINTEL, true, true, IR(160, 3), IR(42276, 23), IR(0, 0), IR(301, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupBlockWriteINTEL, false, false, IR(36, 2), IR(42299, 24), IR(0, 0), IR(301, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageBlockReadINTEL, true, true, IR(172, 4), IR(42323, 28), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageBlockWriteINTEL, false, false, IR(33, 3), IR(42351, 29), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageMediaBlockReadINTEL, true, true, IR(215, 6), IR(42380, 33), IR(0, 0), IR(303, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageMediaBlockWriteINTEL, false, false, IR(675, 5), IR(42413, 34), IR(0, 0), IR(303, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpUCountLeadingZerosINTEL, true, true, IR(160, 3), IR(42447, 24), IR(0, 0), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUCountTrailingZerosINTEL, true, true, IR(160, 3), IR(42471, 25), IR(0, 0), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAbsISubINTEL, true, true, IR(172, 4), IR(42496, 13), IR(0, 0), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAbsUSubINTEL, true, true, IR(172, 4), IR(42509, 13), IR(0, 0), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAddSatINTEL, true, true, IR(172, 4), IR(42522, 13), IR(0, 0), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAddSatINTEL, true, true, IR(172, 4), IR(42535, 13), IR(0, 0), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAverageINTEL, true, true, IR(172, 4), IR(42548, 14), IR(0, 0), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAverageINTEL, true, true, IR(172, 4), IR(42562, 14), IR(0, 0), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAverageRoundedINTEL, true, true, IR(172, 4), IR(42576, 21), IR(0, 0), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAverageRoundedINTEL, true, true, IR(172, 4), IR(42597, 21), IR(0, 0), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpISubSatINTEL, true, true, IR(172, 4), IR(42618, 13), IR(0, 0), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUSubSatINTEL, true, true, IR(172, 4), IR(42631, 13), IR(0, 0), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIMul32x16INTEL, true, true, IR(172, 4), IR(42644, 15), IR(0, 0), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUMul32x16INTEL, true, true, IR(172, 4), IR(42659, 15), IR(0, 0), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConstantFunctionPointerINTEL, true, true, IR(160, 3), IR(42674, 29), IR(0, 0), IR(217, 1), IR(115, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFunctionPointerCallINTEL, true, true, IR(107, 3), IR(42703, 25), IR(0, 0), IR(217, 1), IR(115, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmTargetINTEL, true, false, IR(50, 2), IR(42728, 15), IR(0, 0), IR(139, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmINTEL, true, true, IR(680, 6), IR(14111, 9), IR(0, 0), IR(139, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmCallINTEL, true, true, IR(122, 4), IR(42743, 13), IR(0, 0), IR(139, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAtomicFMinEXT, true, true, IR(235, 6), IR(42756, 14), IR(0, 0), IR(305, 4), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicFMaxEXT, true, true, IR(235, 6), IR(42770, 14), IR(0, 0), IR(305, 4), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAssumeTrueKHR, false, false, IR(10, 1), IR(42784, 14), IR(0, 0), IR(309, 1), IR(119, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpExpectKHR, true, true, IR(172, 4), IR(42798, 10), IR(0, 0), IR(309, 1), IR(119, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpDecorateString, false, false, IR(163, 2), IR(42808, 15), IR(190, 1), IR(1, 0), IR(222, 2), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpMemberDecorateString, false, false, IR(165, 3), IR(42844, 21), IR(191, 1), IR(1, 0), IR(222, 2), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpVmeImageINTEL, true, true, IR(172, 4), IR(42892, 14), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeVmeImageINTEL, true, false, IR(87, 2), IR(42906, 18), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImePayloadINTEL, true, false, IR(68, 1), IR(42924, 23), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcRefPayloadINTEL, true, false, IR(68, 1), IR(42947, 23), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcSicPayloadINTEL, true, false, IR(68, 1), IR(42970, 23), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcMcePayloadINTEL, true, false, IR(68, 1), IR(42993, 23), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcMceResultINTEL, true, false, IR(68, 1), IR(43016, 22), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultINTEL, true, false, IR(68, 1), IR(43038, 22), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultSingleReferenceStreamoutINTEL, true, false, IR(68, 1), IR(43060, 46), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultDualReferenceStreamoutINTEL, true, false, IR(68, 1), IR(43106, 44), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeSingleReferenceStreaminINTEL, true, false, IR(68, 1), IR(43150, 39), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeDualReferenceStreaminINTEL, true, false, IR(68, 1), IR(43189, 37), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcRefResultINTEL, true, false, IR(68, 1), IR(43226, 22), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcSicResultINTEL, true, false, IR(68, 1), IR(43248, 22), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL, true, true, IR(172, 4), IR(43270, 60), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL, true, true, IR(172, 4), IR(43330, 53), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterShapePenaltyINTEL, true, true, IR(172, 4), IR(43383, 47), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterShapePenaltyINTEL, true, true, IR(172, 4), IR(43430, 40), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL, true, true, IR(172, 4), IR(43470, 51), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterDirectionPenaltyINTEL, true, true, IR(172, 4), IR(43521, 44), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL, true, true, IR(172, 4), IR(43565, 51), IR(0, 0), IR(311, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL, true, true, IR(172, 4), IR(43616, 56), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL, true, true, IR(39, 2), IR(43672, 50), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL, true, true, IR(39, 2), IR(43722, 52), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL, true, true, IR(39, 2), IR(43774, 49), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetMotionVectorCostFunctionINTEL, true, true, IR(215, 6), IR(43823, 47), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL, true, true, IR(172, 4), IR(43870, 50), IR(0, 0), IR(311, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL, true, true, IR(39, 2), IR(43920, 51), IR(0, 0), IR(311, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL, true, true, IR(39, 2), IR(43971, 56), IR(0, 0), IR(313, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetAcOnlyHaarINTEL, true, true, IR(160, 3), IR(44027, 33), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL, true, true, IR(172, 4), IR(44060, 52), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL, true, true, IR(172, 4), IR(44112, 61), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL, true, true, IR(130, 5), IR(44173, 61), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToImePayloadINTEL, true, true, IR(160, 3), IR(44234, 39), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToImeResultINTEL, true, true, IR(160, 3), IR(44273, 38), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToRefPayloadINTEL, true, true, IR(160, 3), IR(44311, 39), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToRefResultINTEL, true, true, IR(160, 3), IR(44350, 38), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToSicPayloadINTEL, true, true, IR(160, 3), IR(44388, 39), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToSicResultINTEL, true, true, IR(160, 3), IR(44427, 38), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetMotionVectorsINTEL, true, true, IR(160, 3), IR(44465, 36), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterDistortionsINTEL, true, true, IR(160, 3), IR(44501, 39), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetBestInterDistortionsINTEL, true, true, IR(160, 3), IR(44540, 43), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMajorShapeINTEL, true, true, IR(160, 3), IR(44583, 38), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMinorShapeINTEL, true, true, IR(160, 3), IR(44621, 38), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterDirectionsINTEL, true, true, IR(160, 3), IR(44659, 38), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMotionVectorCountINTEL, true, true, IR(160, 3), IR(44697, 45), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterReferenceIdsINTEL, true, true, IR(160, 3), IR(44742, 40), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL, true, true, IR(130, 5), IR(44782, 62), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeInitializeINTEL, true, true, IR(130, 5), IR(44844, 30), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetSingleReferenceINTEL, true, true, IR(130, 5), IR(44874, 38), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetDualReferenceINTEL, true, true, IR(215, 6), IR(44912, 36), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeRefWindowSizeINTEL, true, true, IR(172, 4), IR(44948, 33), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeAdjustRefOffsetINTEL, true, true, IR(215, 6), IR(44981, 35), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(45016, 39), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetMaxMotionVectorCountINTEL, true, true, IR(172, 4), IR(45055, 43), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetUnidirectionalMixDisableINTEL, true, true, IR(160, 3), IR(45098, 47), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetEarlySearchTerminationThresholdINTEL, true, true, IR(172, 4), IR(45145, 54), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetWeightedSadINTEL, true, true, IR(172, 4), IR(45199, 34), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(45233, 47), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(45280, 45), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL, true, true, IR(215, 6), IR(45325, 55), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL, true, true, IR(325, 7), IR(45380, 53), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL, true, true, IR(130, 5), IR(45433, 56), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL, true, true, IR(215, 6), IR(45489, 54), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL, true, true, IR(215, 6), IR(45543, 58), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL, true, true, IR(325, 7), IR(45601, 56), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeConvertToMceResultINTEL, true, true, IR(160, 3), IR(45657, 38), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetSingleReferenceStreaminINTEL, true, true, IR(160, 3), IR(45695, 46), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetDualReferenceStreaminINTEL, true, true, IR(160, 3), IR(45741, 44), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeStripSingleReferenceStreamoutINTEL, true, true, IR(160, 3), IR(45785, 49), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeStripDualReferenceStreamoutINTEL, true, true, IR(160, 3), IR(45834, 47), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL, true, true, IR(172, 4), IR(45881, 70), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL, true, true, IR(172, 4), IR(45951, 68), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL, true, true, IR(172, 4), IR(46019, 69), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL, true, true, IR(130, 5), IR(46088, 68), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL, true, true, IR(130, 5), IR(46156, 66), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL, true, true, IR(130, 5), IR(46222, 67), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetBorderReachedINTEL, true, true, IR(172, 4), IR(46289, 36), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetTruncatedSearchIndicationINTEL, true, true, IR(160, 3), IR(46325, 48), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL, true, true, IR(160, 3), IR(46373, 59), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL, true, true, IR(160, 3), IR(46432, 58), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL, true, true, IR(160, 3), IR(46490, 56), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcFmeInitializeINTEL, true, true, IR(686, 9), IR(46546, 30), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcBmeInitializeINTEL, true, true, IR(695, 10), IR(46576, 30), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(46606, 39), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefSetBidirectionalMixDisableINTEL, true, true, IR(160, 3), IR(46645, 46), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefSetBilinearFilterEnableINTEL, true, true, IR(160, 3), IR(46691, 43), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(46734, 47), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(46781, 45), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithMultiReferenceINTEL, true, true, IR(130, 5), IR(46826, 46), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL, true, true, IR(215, 6), IR(46872, 56), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefConvertToMceResultINTEL, true, true, IR(160, 3), IR(46928, 38), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicInitializeINTEL, true, true, IR(160, 3), IR(46966, 30), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureSkcINTEL, true, true, IR(288, 8), IR(46996, 32), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureIpeLumaINTEL, true, true, IR(695, 10), IR(47028, 36), IR(0, 0), IR(311, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureIpeLumaChromaINTEL, true, true, IR(705, 13), IR(47064, 42), IR(0, 0), IR(313, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetMotionVectorMaskINTEL, true, true, IR(172, 4), IR(47106, 39), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(47145, 39), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraLumaShapePenaltyINTEL, true, true, IR(172, 4), IR(47184, 44), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraLumaModeCostFunctionINTEL, true, true, IR(215, 6), IR(47228, 48), IR(0, 0), IR(311, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraChromaModeCostFunctionINTEL, true, true, IR(172, 4), IR(47276, 50), IR(0, 0), IR(313, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetBilinearFilterEnableINTEL, true, true, IR(160, 3), IR(47326, 43), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetSkcForwardTransformEnableINTEL, true, true, IR(172, 4), IR(47369, 48), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetBlockBasedRawSkipSadINTEL, true, true, IR(172, 4), IR(47417, 43), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateIpeINTEL, true, true, IR(172, 4), IR(47460, 31), IR(0, 0), IR(311, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(47491, 47), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(47538, 45), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithMultiReferenceINTEL, true, true, IR(130, 5), IR(47583, 46), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL, true, true, IR(215, 6), IR(47629, 56), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConvertToMceResultINTEL, true, true, IR(160, 3), IR(47685, 38), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetIpeLumaShapeINTEL, true, true, IR(160, 3), IR(47723, 35), IR(0, 0), IR(311, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetBestIpeLumaDistortionINTEL, true, true, IR(160, 3), IR(47758, 44), IR(0, 0), IR(311, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetBestIpeChromaDistortionINTEL, true, true, IR(160, 3), IR(47802, 46), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedIpeLumaModesINTEL, true, true, IR(160, 3), IR(47848, 41), IR(0, 0), IR(311, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetIpeChromaModeINTEL, true, true, IR(160, 3), IR(47889, 36), IR(0, 0), IR(313, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL, true, true, IR(160, 3), IR(47925, 50), IR(0, 0), IR(311, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL, true, true, IR(160, 3), IR(47975, 48), IR(0, 0), IR(311, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetInterRawSadsINTEL, true, true, IR(160, 3), IR(48023, 35), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpVariableLengthArrayINTEL, true, true, IR(160, 3), IR(14349, 25), IR(0, 0), IR(315, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpSaveMemoryINTEL, true, true, IR(39, 2), IR(48058, 16), IR(0, 0), IR(315, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpRestoreMemoryINTEL, false, false, IR(10, 1), IR(48074, 19), IR(0, 0), IR(315, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpArbitraryFloatSinCosPiALTERA, true, true, IR(718, 8), IR(48093, 29), IR(192, 1), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastALTERA, true, true, IR(718, 8), IR(48150, 25), IR(193, 1), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastFromIntALTERA, true, true, IR(718, 8), IR(48199, 32), IR(194, 1), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastToIntALTERA, true, true, IR(718, 8), IR(48262, 30), IR(195, 1), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatAddALTERA, true, true, IR(726, 10), IR(48321, 24), IR(196, 1), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSubALTERA, true, true, IR(726, 10), IR(48368, 24), IR(197, 1), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatMulALTERA, true, true, IR(726, 10), IR(48415, 24), IR(198, 1), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatDivALTERA, true, true, IR(726, 10), IR(48462, 24), IR(199, 1), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatGTALTERA, true, true, IR(736, 6), IR(48509, 23), IR(200, 1), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatGEALTERA, true, true, IR(736, 6), IR(48554, 23), IR(201, 1), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLTALTERA, true, true, IR(736, 6), IR(48599, 23), IR(202, 1), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLEALTERA, true, true, IR(736, 6), IR(48644, 23), IR(203, 1), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatEQALTERA, true, true, IR(736, 6), IR(48689, 23), IR(204, 1), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatRecipALTERA, true, true, IR(718, 8), IR(48734, 26), IR(205, 1), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatRSqrtALTERA, true, true, IR(718, 8), IR(48785, 26), IR(206, 1), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCbrtALTERA, true, true, IR(718, 8), IR(48836, 25), IR(207, 1), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatHypotALTERA, true, true, IR(726, 10), IR(48885, 26), IR(208, 1), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSqrtALTERA, true, true, IR(718, 8), IR(48936, 25), IR(209, 1), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLogINTEL, true, true, IR(718, 8), IR(48985, 23), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog2INTEL, true, true, IR(718, 8), IR(49008, 24), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog10INTEL, true, true, IR(718, 8), IR(49032, 25), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog1pINTEL, true, true, IR(718, 8), IR(49057, 25), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExpINTEL, true, true, IR(718, 8), IR(49082, 23), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExp2INTEL, true, true, IR(718, 8), IR(49105, 24), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExp10INTEL, true, true, IR(718, 8), IR(49129, 25), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExpm1INTEL, true, true, IR(718, 8), IR(49154, 25), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinINTEL, true, true, IR(718, 8), IR(49179, 23), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCosINTEL, true, true, IR(718, 8), IR(49202, 23), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinCosINTEL, true, true, IR(718, 8), IR(49225, 26), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinPiINTEL, true, true, IR(718, 8), IR(49251, 25), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCosPiINTEL, true, true, IR(718, 8), IR(49276, 25), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatASinINTEL, true, true, IR(718, 8), IR(49301, 24), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatASinPiINTEL, true, true, IR(718, 8), IR(49325, 26), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatACosINTEL, true, true, IR(718, 8), IR(49351, 24), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatACosPiINTEL, true, true, IR(718, 8), IR(49375, 26), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATanINTEL, true, true, IR(718, 8), IR(49401, 24), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATanPiINTEL, true, true, IR(718, 8), IR(49425, 26), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATan2INTEL, true, true, IR(726, 10), IR(49451, 25), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowINTEL, true, true, IR(726, 10), IR(49476, 23), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowRINTEL, true, true, IR(726, 10), IR(49499, 24), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowNINTEL, true, true, IR(726, 10), IR(49523, 24), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpLoopControlINTEL, false, false, IR(18, 1), IR(49547, 17), IR(0, 0), IR(317, 1), IR(129, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAliasDomainDeclINTEL, true, false, IR(742, 2), IR(49564, 21), IR(0, 0), IR(145, 1), IR(141, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAliasScopeDeclINTEL, true, false, IR(744, 3), IR(49585, 20), IR(0, 0), IR(145, 1), IR(141, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAliasScopeListDeclINTEL, true, false, IR(92, 2), IR(49605, 24), IR(0, 0), IR(145, 1), IR(141, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSqrtALTERA, true, true, IR(718, 8), IR(49629, 16), IR(210, 1), IR(207, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedRecipALTERA, true, true, IR(718, 8), IR(49660, 17), IR(211, 1), IR(207, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedRsqrtALTERA, true, true, IR(718, 8), IR(49693, 17), IR(212, 1), IR(207, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinALTERA, true, true, IR(718, 8), IR(49726, 15), IR(213, 1), IR(207, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedCosALTERA, true, true, IR(718, 8), IR(49755, 15), IR(214, 1), IR(207, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinCosALTERA, true, true, IR(718, 8), IR(49784, 18), IR(215, 1), IR(207, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinPiALTERA, true, true, IR(718, 8), IR(49819, 17), IR(216, 1), IR(207, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedCosPiALTERA, true, true, IR(718, 8), IR(49852, 17), IR(217, 1), IR(207, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinCosPiALTERA, true, true, IR(718, 8), IR(49885, 20), IR(218, 1), IR(207, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedLogALTERA, true, true, IR(718, 8), IR(49924, 15), IR(219, 1), IR(207, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedExpALTERA, true, true, IR(718, 8), IR(49953, 15), IR(220, 1), IR(207, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpPtrCastToCrossWorkgroupALTERA, true, true, IR(160, 3), IR(49982, 30), IR(221, 1), IR(218, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpCrossWorkgroupCastToPtrALTERA, true, true, IR(160, 3), IR(50041, 30), IR(222, 1), IR(218, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpReadPipeBlockingALTERA, false, false, IR(296, 4), IR(50100, 23), IR(223, 1), IR(318, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpWritePipeBlockingALTERA, false, false, IR(296, 4), IR(50145, 24), IR(224, 1), IR(318, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFPGARegALTERA, true, true, IR(160, 3), IR(15307, 14), IR(65, 1), IR(319, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpRayQueryGetRayTMinKHR, true, true, IR(160, 3), IR(50192, 22), IR(0, 0), IR(211, 1), IR(49, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetRayFlagsKHR, true, true, IR(160, 3), IR(50214, 23), IR(0, 0), IR(211, 1), IR(49, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTKHR, true, true, IR(172, 4), IR(50237, 28), IR(0, 0), IR(211, 1), IR(49, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceCustomIndexKHR, true, true, IR(172, 4), IR(50265, 46), IR(0, 0), IR(211, 1), IR(49, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceIdKHR, true, true, IR(172, 4), IR(50311, 37), IR(0, 0), IR(211, 1), IR(49, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR, true, true, IR(172, 4), IR(50348, 65), IR(0, 0), IR(211, 1), IR(49, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionGeometryIndexKHR, true, true, IR(172, 4), IR(50413, 40), IR(0, 0), IR(211, 1), IR(49, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionPrimitiveIndexKHR, true, true, IR(172, 4), IR(50453, 41), IR(0, 0), IR(211, 1), IR(49, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionBarycentricsKHR, true, true, IR(172, 4), IR(50494, 39), IR(0, 0), IR(211, 1), IR(49, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionFrontFaceKHR, true, true, IR(172, 4), IR(50533, 36), IR(0, 0), IR(211, 1), IR(49, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionCandidateAABBOpaqueKHR, true, true, IR(160, 3), IR(50569, 46), IR(0, 0), IR(211, 1), IR(49, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectRayDirectionKHR, true, true, IR(172, 4), IR(50615, 45), IR(0, 0), IR(211, 1), IR(49, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectRayOriginKHR, true, true, IR(172, 4), IR(50660, 42), IR(0, 0), IR(211, 1), IR(49, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetWorldRayDirectionKHR, true, true, IR(160, 3), IR(50702, 32), IR(0, 0), IR(211, 1), IR(49, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetWorldRayOriginKHR, true, true, IR(160, 3), IR(50734, 29), IR(0, 0), IR(211, 1), IR(49, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectToWorldKHR, true, true, IR(172, 4), IR(50763, 40), IR(0, 0), IR(211, 1), IR(49, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionWorldToObjectKHR, true, true, IR(172, 4), IR(50803, 40), IR(0, 0), IR(211, 1), IR(49, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAtomicFAddEXT, true, true, IR(235, 6), IR(50843, 14), IR(0, 0), IR(320, 4), IR(166, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpTypeBufferSurfaceINTEL, true, false, IR(100, 2), IR(50857, 23), IR(0, 0), IR(137, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeStructContinuedINTEL, false, false, IR(747, 1), IR(50880, 25), IR(0, 0), IR(324, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantCompositeContinuedINTEL, false, false, IR(747, 1), IR(50905, 32), IR(0, 0), IR(324, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCompositeContinuedINTEL, false, false, IR(747, 1), IR(50937, 36), IR(0, 0), IR(324, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpCompositeConstructContinuedINTEL, false, false, IR(747, 1), IR(50973, 33), IR(0, 0), IR(324, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpConvertFToBF16INTEL, true, true, IR(160, 3), IR(51006, 20), IR(0, 0), IR(325, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertBF16ToFINTEL, true, true, IR(160, 3), IR(51026, 20), IR(0, 0), IR(325, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpControlBarrierArriveEXT, false, false, IR(221, 3), IR(51046, 24), IR(225, 1), IR(326, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpControlBarrierWaitEXT, false, false, IR(221, 3), IR(51096, 22), IR(226, 1), IR(326, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpArithmeticFenceEXT, true, true, IR(160, 3), IR(15818, 19), IR(0, 0), IR(327, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpTaskSequenceCreateALTERA, true, true, IR(748, 7), IR(51142, 25), IR(227, 1), IR(328, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTaskSequenceAsyncALTERA, false, false, IR(168, 2), IR(51191, 24), IR(228, 1), IR(328, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTaskSequenceGetALTERA, true, true, IR(160, 3), IR(51238, 22), IR(229, 1), IR(328, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTaskSequenceReleaseALTERA, false, false, IR(10, 1), IR(51281, 26), IR(230, 1), IR(328, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeTaskSequenceALTERA, true, false, IR(68, 1), IR(51332, 23), IR(231, 1), IR(328, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupBlockPrefetchINTEL, false, false, IR(139, 3), IR(51377, 27), IR(0, 0), IR(329, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadINTEL, false, false, IR(755, 10), IR(51404, 25), IR(0, 0), IR(112, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadTransformINTEL, false, false, IR(755, 10), IR(51429, 34), IR(0, 0), IR(330, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadTransposeINTEL, false, false, IR(755, 10), IR(51463, 34), IR(0, 0), IR(331, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockPrefetchINTEL, false, false, IR(765, 9), IR(51497, 29), IR(0, 0), IR(112, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockStoreINTEL, false, false, IR(755, 10), IR(51526, 26), IR(0, 0), IR(112, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupMatrixMultiplyAccumulateINTEL, true, true, IR(774, 7), IR(16295, 38), IR(0, 0), IR(332, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpBitwiseFunctionINTEL, true, true, IR(215, 6), IR(51614, 21), IR(0, 0), IR(333, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpUntypedVariableLengthArrayINTEL, true, true, IR(172, 4), IR(16361, 32), IR(0, 0), IR(334, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpConditionalExtensionINTEL, false, false, IR(45, 2), IR(51635, 26), IR(0, 0), IR(115, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpConditionalEntryPointINTEL, false, false, IR(781, 5), IR(51661, 27), IR(0, 0), IR(115, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpConditionalCapabilityINTEL, false, false, IR(786, 2), IR(51688, 27), IR(0, 0), IR(115, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpSpecConstantTargetINTEL, true, true, IR(788, 4), IR(51715, 24), IR(0, 0), IR(335, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantArchitectureINTEL, true, true, IR(792, 6), IR(51739, 30), IR(0, 0), IR(335, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCapabilitiesINTEL, true, true, IR(798, 3), IR(51806, 30), IR(0, 0), IR(335, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConditionalCopyObjectINTEL, true, true, IR(107, 3), IR(51836, 27), IR(0, 0), IR(115, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpPredicatedLoadINTEL, true, true, IR(636, 6), IR(51863, 20), IR(0, 0), IR(336, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPredicatedStoreINTEL, false, false, IR(589, 4), IR(51883, 21), IR(0, 0), IR(336, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpGroupIMulKHR, true, true, IR(283, 5), IR(51904, 13), IR(0, 0), IR(337, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMulKHR, true, true, IR(283, 5), IR(51917, 13), IR(0, 0), IR(337, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseAndKHR, true, true, IR(283, 5), IR(51930, 19), IR(0, 0), IR(337, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseOrKHR, true, true, IR(283, 5), IR(51949, 18), IR(0, 0), IR(337, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseXorKHR, true, true, IR(283, 5), IR(51967, 19), IR(0, 0), IR(337, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalAndKHR, true, true, IR(283, 5), IR(51986, 19), IR(0, 0), IR(337, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalOrKHR, true, true, IR(283, 5), IR(52005, 18), IR(0, 0), IR(337, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalXorKHR, true, true, IR(283, 5), IR(52023, 19), IR(0, 0), IR(337, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpRoundFToTF32INTEL, true, true, IR(160, 3), IR(52042, 18), IR(0, 0), IR(338, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpMaskedGatherINTEL, true, true, IR(801, 6), IR(52060, 18), IR(0, 0), IR(339, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpMaskedScatterINTEL, false, false, IR(807, 4), IR(52078, 19), IR(0, 0), IR(339, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpConvertHandleToImageINTEL, true, true, IR(160, 3), IR(52097, 26), IR(0, 0), IR(340, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertHandleToSamplerINTEL, true, true, IR(160, 3), IR(52123, 28), IR(0, 0), IR(340, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertHandleToSampledImageINTEL, true, true, IR(160, 3), IR(52151, 33), IR(0, 0), IR(340, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpFDot2MixAcc32VALVE, true, true, IR(130, 5), IR(52184, 19), IR(0, 0), IR(341, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFDot2MixAcc16VALVE, true, true, IR(130, 5), IR(52203, 19), IR(0, 0), IR(343, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFDot4MixAcc32VALVE, true, true, IR(130, 5), IR(52222, 19), IR(0, 0), IR(345, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
}};

// Opcode strings (without the 'Op' prefix) and opcode values, ordered by name.
// The fields in order are:
//   name, either the primary name or an alias, indexing into kStrings
//   index into kInstructionDesc
static const std::array<NameIndex, 935> kInstructionNames{{
  {IR(11622, 9), 441}, // 0 AbortKHR
  {IR(42496, 13), 604}, // 1 AbsISubINTEL
  {IR(42509, 13), 605}, // 2 AbsUSubINTEL
  {IR(30978, 12), 58}, // 3 AccessChain
  {IR(49564, 21), 790}, // 4 AliasDomainDeclINTEL
  {IR(49585, 20), 791}, // 5 AliasScopeDeclINTEL
  {IR(49605, 24), 792}, // 6 AliasScopeListDeclINTEL
  {IR(32275, 4), 143}, // 7 All
  {IR(37670, 25), 429}, // 8 AllocateNodePayloadsAMDX
  {IR(32271, 4), 142}, // 9 Any
  {IR(49351, 24), 781}, // 10 ArbitraryFloatACosINTEL
  {IR(49375, 26), 782}, // 11 ArbitraryFloatACosPiINTEL
  {IR(49301, 24), 779}, // 12 ArbitraryFloatASinINTEL
  {IR(49325, 26), 780}, // 13 ArbitraryFloatASinPiINTEL
  {IR(49451, 25), 785}, // 14 ArbitraryFloatATan2INTEL
  {IR(49401, 24), 783}, // 15 ArbitraryFloatATanINTEL
  {IR(49425, 26), 784}, // 16 ArbitraryFloatATanPiINTEL
  {IR(48321, 24), 752}, // 17 ArbitraryFloatAddALTERA
  {IR(48345, 23), 752}, // 18 ArbitraryFloatAddINTEL
  {IR(48150, 25), 749}, // 19 ArbitraryFloatCastALTERA
  {IR(48199, 32), 750}, // 20 ArbitraryFloatCastFromIntALTERA
  {IR(48231, 31), 750}, // 21 ArbitraryFloatCastFromIntINTEL
  {IR(48175, 24), 749}, // 22 ArbitraryFloatCastINTEL
  {IR(48262, 30), 751}, // 23 ArbitraryFloatCastToIntALTERA
  {IR(48292, 29), 751}, // 24 ArbitraryFloatCastToIntINTEL
  {IR(48836, 25), 763}, // 25 ArbitraryFloatCbrtALTERA
  {IR(48861, 24), 763}, // 26 ArbitraryFloatCbrtINTEL
  {IR(49202, 23), 775}, // 27 ArbitraryFloatCosINTEL
  {IR(49276, 25), 778}, // 28 ArbitraryFloatCosPiINTEL
  {IR(48462, 24), 755}, // 29 ArbitraryFloatDivALTERA
  {IR(48486, 23), 755}, // 30 ArbitraryFloatDivINTEL
  {IR(48689, 23), 760}, // 31 ArbitraryFloatEQALTERA
  {IR(48712, 22), 760}, // 32 ArbitraryFloatEQINTEL
  {IR(49129, 25), 772}, // 33 ArbitraryFloatExp10INTEL
  {IR(49105, 24), 771}, // 34 ArbitraryFloatExp2INTEL
  {IR(49082, 23), 770}, // 35 ArbitraryFloatExpINTEL
  {IR(49154, 25), 773}, // 36 ArbitraryFloatExpm1INTEL
  {IR(48554, 23), 757}, // 37 ArbitraryFloatGEALTERA
  {IR(48577, 22), 757}, // 38 ArbitraryFloatGEINTEL
  {IR(48509, 23), 756}, // 39 ArbitraryFloatGTALTERA
  {IR(48532, 22), 756}, // 40 ArbitraryFloatGTINTEL
  {IR(48885, 26), 764}, // 41 ArbitraryFloatHypotALTERA
  {IR(48911, 25), 764}, // 42 ArbitraryFloatHypotINTEL
  {IR(48644, 23), 759}, // 43 ArbitraryFloatLEALTERA
  {IR(48667, 22), 759}, // 44 ArbitraryFloatLEINTEL
  {IR(48599, 23), 758}, // 45 ArbitraryFloatLTALTERA
  {IR(48622, 22), 758}, // 46 ArbitraryFloatLTINTEL
  {IR(49032, 25), 768}, // 47 ArbitraryFloatLog10INTEL
  {IR(49057, 25), 769}, // 48 ArbitraryFloatLog1pINTEL
  {IR(49008, 24), 767}, // 49 ArbitraryFloatLog2INTEL
  {IR(48985, 23), 766}, // 50 ArbitraryFloatLogINTEL
  {IR(48415, 24), 754}, // 51 ArbitraryFloatMulALTERA
  {IR(48439, 23), 754}, // 52 ArbitraryFloatMulINTEL
  {IR(49476, 23), 786}, // 53 ArbitraryFloatPowINTEL
  {IR(49523, 24), 788}, // 54 ArbitraryFloatPowNINTEL
  {IR(49499, 24), 787}, // 55 ArbitraryFloatPowRINTEL
  {IR(48785, 26), 762}, // 56 ArbitraryFloatRSqrtALTERA
  {IR(48811, 25), 762}, // 57 ArbitraryFloatRSqrtINTEL
  {IR(48734, 26), 761}, // 58 ArbitraryFloatRecipALTERA
  {IR(48760, 25), 761}, // 59 ArbitraryFloatRecipINTEL
  {IR(49225, 26), 776}, // 60 ArbitraryFloatSinCosINTEL
  {IR(48093, 29), 748}, // 61 ArbitraryFloatSinCosPiALTERA
  {IR(48122, 28), 748}, // 62 ArbitraryFloatSinCosPiINTEL
  {IR(49179, 23), 774}, // 63 ArbitraryFloatSinINTEL
  {IR(49251, 25), 777}, // 64 ArbitraryFloatSinPiINTEL
  {IR(48936, 25), 765}, // 65 ArbitraryFloatSqrtALTERA
  {IR(48961, 24), 765}, // 66 ArbitraryFloatSqrtINTEL
  {IR(48368, 24), 753}, // 67 ArbitraryFloatSubALTERA
  {IR(48392, 23), 753}, // 68 ArbitraryFloatSubINTEL
  {IR(15818, 19), 836}, // 69 ArithmeticFenceEXT
  {IR(31025, 12), 61}, // 70 ArrayLength
  {IR(42743, 13), 620}, // 71 AsmCallINTEL
  {IR(14111, 9), 619}, // 72 AsmINTEL
  {IR(42728, 15), 618}, // 73 AsmTargetINTEL
  {IR(42784, 14), 623}, // 74 AssumeTrueKHR
  {IR(33297, 10), 220}, // 75 AtomicAnd
  {IR(33149, 22), 210}, // 76 AtomicCompareExchange
  {IR(33171, 26), 211}, // 77 AtomicCompareExchangeWeak
  {IR(33134, 15), 209}, // 78 AtomicExchange
  {IR(50843, 14), 826}, // 79 AtomicFAddEXT
  {IR(42770, 14), 622}, // 80 AtomicFMaxEXT
  {IR(42756, 14), 621}, // 81 AtomicFMinEXT
  {IR(34682, 16), 292}, // 82 AtomicFlagClear
  {IR(34661, 21), 291}, // 83 AtomicFlagTestAndSet
  {IR(33231, 11), 214}, // 84 AtomicIAdd
  {IR(33214, 17), 213}, // 85 AtomicIDecrement
  {IR(33197, 17), 212}, // 86 AtomicIIncrement
  {IR(33242, 11), 215}, // 87 AtomicISub
  {IR(33111, 11), 207}, // 88 AtomicLoad
  {IR(33307, 9), 221}, // 89 AtomicOr
  {IR(33275, 11), 218}, // 90 AtomicSMax
  {IR(33253, 11), 216}, // 91 AtomicSMin
  {IR(33122, 12), 208}, // 92 AtomicStore
  {IR(33286, 11), 219}, // 93 AtomicUMax
  {IR(33264, 11), 217}, // 94 AtomicUMin
  {IR(33316, 10), 222}, // 95 AtomicXor
  {IR(11285, 19), 413}, // 96 BFloat16MulAddQCOM
  {IR(40932, 28), 550}, // 97 BeginInvocationInterlockEXT
  {IR(37208, 17), 408}, // 98 BitCastArrayQCOM
  {IR(32895, 9), 191}, // 99 BitCount
  {IR(32835, 15), 187}, // 100 BitFieldInsert
  {IR(32850, 17), 188}, // 101 BitFieldSExtract
  {IR(32867, 17), 189}, // 102 BitFieldUExtract
  {IR(32884, 11), 190}, // 103 BitReverse
  {IR(32023, 8), 114}, // 104 Bitcast
  {IR(10512, 18), 358}, // 105 BitcastExtractEXT
  {IR(32820, 11), 185}, // 106 BitwiseAnd
  {IR(51614, 21), 849}, // 107 BitwiseFunctionINTEL
  {IR(32799, 10), 183}, // 108 BitwiseOr
  {IR(32809, 11), 184}, // 109 BitwiseXor
  {IR(33426, 7), 227}, // 110 Branch
  {IR(33433, 18), 228}, // 111 BranchConditional
  {IR(37931, 17), 440}, // 112 BufferPointerEXT
  {IR(34294, 13), 277}, // 113 BuildNDRange
  {IR(30039, 11), 15}, // 114 Capability
  {IR(34252, 26), 275}, // 115 CaptureEventProfilingInfo
  {IR(35758, 23), 344}, // 116 ColorAttachmentReadEXT
  {IR(33844, 15), 255}, // 117 CommitReadPipe
  {IR(33859, 16), 256}, // 118 CommitWritePipe
  {IR(31285, 19), 72}, // 119 CompositeConstruct
  {IR(50973, 33), 831}, // 120 CompositeConstructContinuedINTEL
  {IR(37341, 30), 414}, // 121 CompositeConstructCoopMatQCOM
  {IR(36916, 31), 396}, // 122 CompositeConstructReplicateEXT
  {IR(31304, 17), 73}, // 123 CompositeExtract
  {IR(37371, 28), 415}, // 124 CompositeExtractCoopMatQCOM
  {IR(31321, 16), 74}, // 125 CompositeInsert
  {IR(51688, 27), 853}, // 126 ConditionalCapabilityINTEL
  {IR(51836, 27), 857}, // 127 ConditionalCopyObjectINTEL
  {IR(51661, 27), 852}, // 128 ConditionalEntryPointINTEL
  {IR(51635, 26), 851}, // 129 ConditionalExtensionINTEL
  {IR(18134, 9), 39}, // 130 Constant
  {IR(30545, 18), 40}, // 131 ConstantComposite
  {IR(50905, 32), 829}, // 132 ConstantCompositeContinuedINTEL
  {IR(36852, 30), 394}, // 133 ConstantCompositeReplicateEXT
  {IR(11631, 16), 445}, // 134 ConstantDataKHR
  {IR(30493, 14), 38}, // 135 ConstantFalse
  {IR(42674, 29), 616}, // 136 ConstantFunctionPointerINTEL
  {IR(30657, 13), 42}, // 137 ConstantNull
  {IR(34737, 20), 296}, // 138 ConstantPipeStorage
  {IR(30641, 16), 41}, // 139 ConstantSampler
  {IR(37996, 18), 444}, // 140 ConstantSizeOfEXT
  {IR(37823, 19), 435}, // 141 ConstantStringAMDX
  {IR(30480, 13), 37}, // 142 ConstantTrue
  {IR(33082, 15), 205}, // 143 ControlBarrier
  {IR(51046, 24), 834}, // 144 ControlBarrierArriveEXT
  {IR(51070, 26), 834}, // 145 ControlBarrierArriveINTEL
  {IR(51096, 22), 835}, // 146 ControlBarrierWaitEXT
  {IR(51118, 24), 835}, // 147 ControlBarrierWaitINTEL
  {IR(51026, 20), 833}, // 148 ConvertBF16ToFINTEL
  {IR(51006, 20), 832}, // 149 ConvertFToBF16INTEL
  {IR(31829, 12), 100}, // 150 ConvertFToS
  {IR(31817, 12), 99}, // 151 ConvertFToU
  {IR(52097, 26), 871}, // 152 ConvertHandleToImageINTEL
  {IR(52151, 33), 873}, // 153 ConvertHandleToSampledImageINTEL
  {IR(52123, 28), 872}, // 154 ConvertHandleToSamplerINTEL
  {IR(41641, 18), 573}, // 155 ConvertImageToUNV
  {IR(31906, 14), 107}, // 156 ConvertPtrToU
  {IR(31841, 12), 101}, // 157 ConvertSToF
  {IR(41704, 25), 576}, // 158 ConvertSampledImageToUNV
  {IR(41659, 20), 574}, // 159 ConvertSamplerToUNV
  {IR(36430, 35), 380}, // 160 ConvertUToAccelerationStructureKHR
  {IR(31853, 12), 102}, // 161 ConvertUToF
  {IR(41603, 18), 571}, // 162 ConvertUToImageNV
  {IR(31950, 14), 110}, // 163 ConvertUToPtr
  {IR(41679, 25), 575}, // 164 ConvertUToSampledImageNV
  {IR(41621, 20), 572}, // 165 ConvertUToSamplerNV
  {IR(39167, 27), 488}, // 166 CooperativeMatrixConvertNV
  {IR(39136, 31), 488}, // 167 CooperativeMatrixConvertUseEXT
  {IR(13808, 34), 549}, // 168 CooperativeMatrixGetCoordinateEXT
  {IR(36825, 27), 393}, // 169 CooperativeMatrixLengthKHR
  {IR(40906, 26), 548}, // 170 CooperativeMatrixLengthNV
  {IR(36693, 25), 390}, // 171 CooperativeMatrixLoadKHR
  {IR(40831, 24), 545}, // 172 CooperativeMatrixLoadNV
  {IR(41157, 30), 553}, // 173 CooperativeMatrixLoadTensorNV
  {IR(36798, 27), 392}, // 174 CooperativeMatrixMulAddKHR
  {IR(40880, 26), 547}, // 175 CooperativeMatrixMulAddNV
  {IR(41218, 33), 555}, // 176 CooperativeMatrixPerElementOpEXT
  {IR(41251, 32), 555}, // 177 CooperativeMatrixPerElementOpNV
  {IR(41029, 27), 552}, // 178 CooperativeMatrixReduceEXT
  {IR(41056, 26), 552}, // 179 CooperativeMatrixReduceNV
  {IR(36718, 26), 391}, // 180 CooperativeMatrixStoreKHR
  {IR(40855, 25), 546}, // 181 CooperativeMatrixStoreNV
  {IR(41187, 31), 554}, // 182 CooperativeMatrixStoreTensorNV
  {IR(41574, 29), 570}, // 183 CooperativeMatrixTransposeNV
  {IR(39390, 24), 495}, // 184 CooperativeVectorLoadNV
  {IR(39104, 32), 487}, // 185 CooperativeVectorMatrixMulAddNV
  {IR(38994, 29), 484}, // 186 CooperativeVectorMatrixMulNV
  {IR(39023, 42), 485}, // 187 CooperativeVectorOuterProductAccumulateNV
  {IR(39065, 39), 486}, // 188 CooperativeVectorReduceSumAccumulateNV
  {IR(39414, 25), 496}, // 189 CooperativeVectorStoreNV
  {IR(35717, 12), 340}, // 190 CopyLogical
  {IR(30951, 11), 56}, // 191 CopyMemory
  {IR(30962, 16), 57}, // 192 CopyMemorySized
  {IR(31337, 11), 75}, // 193 CopyObject
  {IR(34757, 26), 297}, // 194 CreatePipeFromPipeStorage
  {IR(41319, 21), 558}, // 195 CreateTensorLayoutNV
  {IR(41439, 19), 563}, // 196 CreateTensorViewNV
  {IR(34204, 16), 272}, // 197 CreateUserEvent
  {IR(50041, 30), 805}, // 198 CrossWorkgroupCastToPtrALTERA
  {IR(50071, 29), 805}, // 199 CrossWorkgroupCastToPtrINTEL
  {IR(32904, 5), 192}, // 200 DPdx
  {IR(32950, 11), 198}, // 201 DPdxCoarse
  {IR(32921, 9), 195}, // 202 DPdxFine
  {IR(32909, 5), 193}, // 203 DPdy
  {IR(32961, 11), 199}, // 204 DPdyCoarse
  {IR(32930, 9), 196}, // 205 DPdyFine
  {IR(31111, 9), 64}, // 206 Decorate
  {IR(34934, 11), 305}, // 207 DecorateId
  {IR(42808, 15), 625}, // 208 DecorateString
  {IR(42823, 21), 625}, // 209 DecorateStringGOOGLE
  {IR(31135, 16), 66}, // 210 DecorationGroup
  {IR(13162, 25), 566}, // 211 DemoteToHelperInvocation
  {IR(13187, 28), 566}, // 212 DemoteToHelperInvocationEXT
  {IR(35781, 23), 345}, // 213 DepthAttachmentReadEXT
  {IR(32220, 4), 137}, // 214 Dot
  {IR(39194, 17), 489}, // 215 EmitMeshTasksEXT
  {IR(33009, 17), 203}, // 216 EmitStreamVertex
  {IR(32985, 11), 201}, // 217 EmitVertex
  {IR(40960, 26), 551}, // 218 EndInvocationInterlockEXT
  {IR(32996, 13), 202}, // 219 EndPrimitive
  {IR(33026, 19), 204}, // 220 EndStreamPrimitive
  {IR(34040, 14), 265}, // 221 EnqueueKernel
  {IR(34026, 14), 264}, // 222 EnqueueMarker
  {IR(37695, 24), 430}, // 223 EnqueueNodePayloadsAMDX
  {IR(29954, 11), 13}, // 224 EntryPoint
  {IR(36411, 19), 379}, // 225 ExecuteCallableKHR
  {IR(40542, 18), 535}, // 226 ExecuteCallableNV
  {IR(29997, 14), 14}, // 227 ExecutionMode
  {IR(34918, 16), 304}, // 228 ExecutionModeId
  {IR(42798, 10), 624}, // 229 ExpectKHR
  {IR(29808, 8), 11}, // 230 ExtInst
  {IR(29748, 14), 10}, // 231 ExtInstImport
  {IR(36348, 26), 376}, // 232 ExtInstWithForwardRefsKHR
  {IR(29738, 10), 9}, // 233 Extension
  {IR(37399, 20), 416}, // 234 ExtractSubArrayQCOM
  {IR(32052, 5), 118}, // 235 FAdd
  {IR(31883, 9), 105}, // 236 FConvert
  {IR(32087, 5), 125}, // 237 FDiv
  {IR(52203, 19), 875}, // 238 FDot2MixAcc16VALVE
  {IR(52184, 19), 874}, // 239 FDot2MixAcc32VALVE
  {IR(52222, 19), 876}, // 240 FDot4MixAcc32VALVE
  {IR(32112, 5), 130}, // 241 FMod
  {IR(32072, 5), 122}, // 242 FMul
  {IR(32039, 8), 116}, // 243 FNegate
  {IR(32549, 10), 168}, // 244 FOrdEqual
  {IR(32627, 16), 174}, // 245 FOrdGreaterThan
  {IR(32699, 21), 178}, // 246 FOrdGreaterThanEqual
  {IR(32599, 13), 172}, // 247 FOrdLessThan
  {IR(32661, 18), 176}, // 248 FOrdLessThanEqual
  {IR(32571, 13), 170}, // 249 FOrdNotEqual
  {IR(15307, 14), 808}, // 250 FPGARegALTERA
  {IR(15321, 13), 808}, // 251 FPGARegINTEL
  {IR(32107, 5), 129}, // 252 FRem
  {IR(32062, 5), 120}, // 253 FSub
  {IR(32559, 12), 169}, // 254 FUnordEqual
  {IR(32643, 18), 175}, // 255 FUnordGreaterThan
  {IR(32720, 23), 179}, // 256 FUnordGreaterThanEqual
  {IR(32612, 15), 173}, // 257 FUnordLessThan
  {IR(32679, 20), 177}, // 258 FUnordLessThanEqual
  {IR(32584, 15), 171}, // 259 FUnordNotEqual
  {IR(39352, 38), 494}, // 260 FetchMicroTriangleVertexBarycentricNV
  {IR(39317, 35), 493}, // 261 FetchMicroTriangleVertexPositionNV
  {IR(37744, 29), 432}, // 262 FinishWritingNodePayloadAMDX
  {IR(49755, 15), 797}, // 263 FixedCosALTERA
  {IR(49770, 14), 797}, // 264 FixedCosINTEL
  {IR(49852, 17), 800}, // 265 FixedCosPiALTERA
  {IR(49869, 16), 800}, // 266 FixedCosPiINTEL
  {IR(49953, 15), 803}, // 267 FixedExpALTERA
  {IR(49968, 14), 803}, // 268 FixedExpINTEL
  {IR(49924, 15), 802}, // 269 FixedLogALTERA
  {IR(49939, 14), 802}, // 270 FixedLogINTEL
  {IR(49660, 17), 794}, // 271 FixedRecipALTERA
  {IR(49677, 16), 794}, // 272 FixedRecipINTEL
  {IR(49693, 17), 795}, // 273 FixedRsqrtALTERA
  {IR(49710, 16), 795}, // 274 FixedRsqrtINTEL
  {IR(49726, 15), 796}, // 275 FixedSinALTERA
  {IR(49784, 18), 798}, // 276 FixedSinCosALTERA
  {IR(49802, 17), 798}, // 277 FixedSinCosINTEL
  {IR(49885, 20), 801}, // 278 FixedSinCosPiALTERA
  {IR(49905, 19), 801}, // 279 FixedSinCosPiINTEL
  {IR(49741, 14), 796}, // 280 FixedSinINTEL
  {IR(49819, 17), 799}, // 281 FixedSinPiALTERA
  {IR(49836, 16), 799}, // 282 FixedSinPiINTEL
  {IR(49629, 16), 793}, // 283 FixedSqrtALTERA
  {IR(49645, 15), 793}, // 284 FixedSqrtINTEL
  {IR(36265, 7), 370}, // 285 FmaKHR
  {IR(37640, 17), 427}, // 286 FragmentFetchAMD
  {IR(37619, 21), 426}, // 287 FragmentMaskFetchAMD
  {IR(38044, 10), 448}, // 288 FreezeKHR
  {IR(28787, 9), 48}, // 289 Function
  {IR(30860, 13), 51}, // 290 FunctionCall
  {IR(30848, 12), 50}, // 291 FunctionEnd
  {IR(30830, 18), 49}, // 292 FunctionParameter
  {IR(42703, 25), 617}, // 293 FunctionPointerCallINTEL
  {IR(32914, 7), 194}, // 294 Fwidth
  {IR(32972, 13), 200}, // 295 FwidthCoarse
  {IR(32939, 11), 197}, // 296 FwidthFine
  {IR(31981, 17), 112}, // 297 GenericCastToPtr
  {IR(31998, 25), 113}, // 298 GenericCastToPtrExplicit
  {IR(31037, 23), 62}, // 299 GenericPtrMemSemantics
  {IR(34278, 16), 276}, // 300 GetDefaultQueue
  {IR(34783, 35), 298}, // 301 GetKernelLocalSizeForSubgroupCount
  {IR(34818, 25), 299}, // 302 GetKernelMaxNumSubgroups
  {IR(34084, 32), 267}, // 303 GetKernelNDrangeMaxSubGroupSize
  {IR(34054, 30), 266}, // 304 GetKernelNDrangeSubGroupCount
  {IR(34139, 40), 269}, // 305 GetKernelPreferredWorkGroupSizeMultiple
  {IR(34116, 23), 268}, // 306 GetKernelWorkGroupSize
  {IR(33910, 18), 259}, // 307 GetMaxPipePackets
  {IR(33892, 18), 258}, // 308 GetNumPipePackets
  {IR(10365, 9), 353}, // 309 GraphARM
  {IR(35933, 17), 351}, // 310 GraphConstantARM
  {IR(36001, 12), 356}, // 311 GraphEndARM
  {IR(35950, 19), 352}, // 312 GraphEntryPointARM
  {IR(35969, 14), 354}, // 313 GraphInputARM
  {IR(35983, 18), 355}, // 314 GraphSetOutputARM
  {IR(33597, 9), 238}, // 315 GroupAll
  {IR(33606, 9), 239}, // 316 GroupAny
  {IR(33566, 15), 236}, // 317 GroupAsyncCopy
  {IR(51930, 19), 862}, // 318 GroupBitwiseAndKHR
  {IR(51949, 18), 863}, // 319 GroupBitwiseOrKHR
  {IR(51967, 19), 864}, // 320 GroupBitwiseXorKHR
  {IR(33615, 15), 240}, // 321 GroupBroadcast
  {IR(33985, 20), 262}, // 322 GroupCommitReadPipe
  {IR(34005, 21), 263}, // 323 GroupCommitWritePipe
  {IR(31151, 14), 67}, // 324 GroupDecorate
  {IR(33673, 10), 242}, // 325 GroupFAdd
  {IR(37458, 23), 419}, // 326 GroupFAddNonUniformAMD
  {IR(33713, 10), 246}, // 327 GroupFMax
  {IR(37550, 23), 423}, // 328 GroupFMaxNonUniformAMD
  {IR(33683, 10), 243}, // 329 GroupFMin
  {IR(37481, 23), 420}, // 330 GroupFMinNonUniformAMD
  {IR(51917, 13), 861}, // 331 GroupFMulKHR
  {IR(33663, 10), 241}, // 332 GroupIAdd
  {IR(37435, 23), 418}, // 333 GroupIAddNonUniformAMD
  {IR(51904, 13), 860}, // 334 GroupIMulKHR
  {IR(51986, 19), 865}, // 335 GroupLogicalAndKHR
  {IR(52005, 18), 866}, // 336 GroupLogicalOrKHR
  {IR(52023, 19), 867}, // 337 GroupLogicalXorKHR
  {IR(31210, 20), 68}, // 338 GroupMemberDecorate
  {IR(34966, 19), 307}, // 339 GroupNonUniformAll
  {IR(35004, 24), 309}, // 340 GroupNonUniformAllEqual
  {IR(34985, 19), 308}, // 341 GroupNonUniformAny
  {IR(6935, 22), 312}, // 342 GroupNonUniformBallot
  {IR(35144, 30), 315}, // 343 GroupNonUniformBallotBitCount
  {IR(35112, 32), 314}, // 344 GroupNonUniformBallotBitExtract
  {IR(35174, 29), 316}, // 345 GroupNonUniformBallotFindLSB
  {IR(35203, 29), 317}, // 346 GroupNonUniformBallotFindMSB
  {IR(35510, 26), 332}, // 347 GroupNonUniformBitwiseAnd
  {IR(35536, 25), 333}, // 348 GroupNonUniformBitwiseOr
  {IR(35561, 26), 334}, // 349 GroupNonUniformBitwiseXor
  {IR(35028, 25), 310}, // 350 GroupNonUniformBroadcast
  {IR(35053, 30), 311}, // 351 GroupNonUniformBroadcastFirst
  {IR(34945, 21), 306}, // 352 GroupNonUniformElect
  {IR(35330, 20), 323}, // 353 GroupNonUniformFAdd
  {IR(35490, 20), 331}, // 354 GroupNonUniformFMax
  {IR(35430, 20), 328}, // 355 GroupNonUniformFMin
  {IR(35370, 20), 325}, // 356 GroupNonUniformFMul
  {IR(35310, 20), 322}, // 357 GroupNonUniformIAdd
  {IR(35350, 20), 324}, // 358 GroupNonUniformIMul
  {IR(35083, 29), 313}, // 359 GroupNonUniformInverseBallot
  {IR(35587, 26), 335}, // 360 GroupNonUniformLogicalAnd
  {IR(35613, 25), 336}, // 361 GroupNonUniformLogicalOr
  {IR(35638, 26), 337}, // 362 GroupNonUniformLogicalXor
  {IR(39229, 28), 491}, // 363 GroupNonUniformPartitionEXT
  {IR(39257, 27), 491}, // 364 GroupNonUniformPartitionNV
  {IR(37865, 26), 437}, // 365 GroupNonUniformQuadAllKHR
  {IR(37891, 26), 438}, // 366 GroupNonUniformQuadAnyKHR
  {IR(35664, 29), 338}, // 367 GroupNonUniformQuadBroadcast
  {IR(35693, 24), 339}, // 368 GroupNonUniformQuadSwap
  {IR(15546, 25), 374}, // 369 GroupNonUniformRotateKHR
  {IR(35450, 20), 329}, // 370 GroupNonUniformSMax
  {IR(35390, 20), 326}, // 371 GroupNonUniformSMin
  {IR(10074, 23), 318}, // 372 GroupNonUniformShuffle
  {IR(35283, 27), 321}, // 373 GroupNonUniformShuffleDown
  {IR(35258, 25), 320}, // 374 GroupNonUniformShuffleUp
  {IR(35232, 26), 319}, // 375 GroupNonUniformShuffleXor
  {IR(35470, 20), 330}, // 376 GroupNonUniformUMax
  {IR(35410, 20), 327}, // 377 GroupNonUniformUMin
  {IR(33928, 28), 260}, // 378 GroupReserveReadPipePackets
  {IR(33956, 29), 261}, // 379 GroupReserveWritePipePackets
  {IR(33733, 10), 248}, // 380 GroupSMax
  {IR(37596, 23), 425}, // 381 GroupSMaxNonUniformAMD
  {IR(33703, 10), 245}, // 382 GroupSMin
  {IR(37527, 23), 422}, // 383 GroupSMinNonUniformAMD
  {IR(33723, 10), 247}, // 384 GroupUMax
  {IR(37573, 23), 424}, // 385 GroupUMaxNonUniformAMD
  {IR(33693, 10), 244}, // 386 GroupUMin
  {IR(37504, 23), 421}, // 387 GroupUMinNonUniformAMD
  {IR(33581, 16), 237}, // 388 GroupWaitEvents
  {IR(39886, 26), 512}, // 389 HitObjectExecuteShaderEXT
  {IR(38489, 25), 464}, // 390 HitObjectExecuteShaderNV
  {IR(39939, 26), 514}, // 391 HitObjectGetAttributesEXT
  {IR(38540, 25), 466}, // 392 HitObjectGetAttributesNV
  {IR(40618, 24), 537}, // 393 HitObjectGetClusterIdNV
  {IR(39912, 27), 513}, // 394 HitObjectGetCurrentTimeEXT
  {IR(38514, 26), 465}, // 395 HitObjectGetCurrentTimeNV
  {IR(40018, 29), 517}, // 396 HitObjectGetGeometryIndexEXT
  {IR(38616, 28), 469}, // 397 HitObjectGetGeometryIndexNV
  {IR(39965, 23), 515}, // 398 HitObjectGetHitKindEXT
  {IR(38565, 22), 467}, // 399 HitObjectGetHitKindNV
  {IR(40073, 35), 519}, // 400 HitObjectGetInstanceCustomIndexEXT
  {IR(38669, 34), 471}, // 401 HitObjectGetInstanceCustomIndexNV
  {IR(40047, 26), 518}, // 402 HitObjectGetInstanceIdEXT
  {IR(38644, 25), 470}, // 403 HitObjectGetInstanceIdNV
  {IR(39519, 51), 500}, // 404 HitObjectGetIntersectionTriangleVertexPositionsEXT
  {IR(42070, 27), 586}, // 405 HitObjectGetLSSPositionsNV
  {IR(42097, 23), 587}, // 406 HitObjectGetLSSRadiiNV
  {IR(40139, 34), 521}, // 407 HitObjectGetObjectRayDirectionEXT
  {IR(38201, 33), 454}, // 408 HitObjectGetObjectRayDirectionNV
  {IR(40108, 31), 520}, // 409 HitObjectGetObjectRayOriginEXT
  {IR(38234, 30), 455}, // 410 HitObjectGetObjectRayOriginNV
  {IR(40236, 29), 524}, // 411 HitObjectGetObjectToWorldEXT
  {IR(38173, 28), 453}, // 412 HitObjectGetObjectToWorldNV
  {IR(39988, 30), 516}, // 413 HitObjectGetPrimitiveIndexEXT
  {IR(38587, 29), 468}, // 414 HitObjectGetPrimitiveIndexNV
  {IR(39570, 24), 501}, // 415 HitObjectGetRayFlagsEXT
  {IR(40294, 23), 526}, // 416 HitObjectGetRayTMaxEXT
  {IR(38764, 22), 474}, // 417 HitObjectGetRayTMaxNV
  {IR(40642, 23), 538}, // 418 HitObjectGetRayTMinEXT
  {IR(38786, 22), 475}, // 419 HitObjectGetRayTMinNV
  {IR(40665, 45), 539}, // 420 HitObjectGetShaderBindingTableRecordIndexEXT
  {IR(38329, 44), 458}, // 421 HitObjectGetShaderBindingTableRecordIndexNV
  {IR(40710, 40), 540}, // 422 HitObjectGetShaderRecordBufferHandleEXT
  {IR(38290, 39), 457}, // 423 HitObjectGetShaderRecordBufferHandleNV
  {IR(42014, 29), 584}, // 424 HitObjectGetSpherePositionNV
  {IR(42043, 27), 585}, // 425 HitObjectGetSphereRadiusNV
  {IR(40173, 33), 522}, // 426 HitObjectGetWorldRayDirectionEXT
  {IR(38703, 32), 472}, // 427 HitObjectGetWorldRayDirectionNV
  {IR(40206, 30), 523}, // 428 HitObjectGetWorldRayOriginEXT
  {IR(38735, 29), 473}, // 429 HitObjectGetWorldRayOriginNV
  {IR(40265, 29), 525}, // 430 HitObjectGetWorldToObjectEXT
  {IR(38145, 28), 452}, // 431 HitObjectGetWorldToObjectNV
  {IR(40750, 20), 541}, // 432 HitObjectIsEmptyEXT
  {IR(38808, 19), 476}, // 433 HitObjectIsEmptyNV
  {IR(40770, 18), 542}, // 434 HitObjectIsHitEXT
  {IR(38827, 17), 477}, // 435 HitObjectIsHitNV
  {IR(42143, 20), 589}, // 436 HitObjectIsLSSHitNV
  {IR(40788, 19), 543}, // 437 HitObjectIsMissEXT
  {IR(38844, 18), 478}, // 438 HitObjectIsMissNV
  {IR(42120, 23), 588}, // 439 HitObjectIsSphereHitNV
  {IR(39862, 24), 511}, // 440 HitObjectRecordEmptyEXT
  {IR(38373, 23), 459}, // 441 HitObjectRecordEmptyNV
  {IR(39439, 28), 497}, // 442 HitObjectRecordFromQueryEXT
  {IR(38054, 27), 449}, // 443 HitObjectRecordHitMotionNV
  {IR(38416, 21), 461}, // 444 HitObjectRecordHitNV
  {IR(38081, 36), 450}, // 445 HitObjectRecordHitWithIndexMotionNV
  {IR(38437, 30), 462}, // 446 HitObjectRecordHitWithIndexNV
  {IR(39467, 23), 498}, // 447 HitObjectRecordMissEXT
  {IR(39490, 29), 499}, // 448 HitObjectRecordMissMotionEXT
  {IR(38117, 28), 451}, // 449 HitObjectRecordMissMotionNV
  {IR(38467, 22), 463}, // 450 HitObjectRecordMissNV
  {IR(39639, 33), 503}, // 451 HitObjectReorderExecuteShaderEXT
  {IR(39594, 45), 502}, // 452 HitObjectSetShaderBindingTableRecordIndexEXT
  {IR(39704, 38), 505}, // 453 HitObjectTraceMotionReorderExecuteEXT
  {IR(39814, 21), 509}, // 454 HitObjectTraceRayEXT
  {IR(39835, 27), 510}, // 455 HitObjectTraceRayMotionEXT
  {IR(38264, 26), 456}, // 456 HitObjectTraceRayMotionNV
  {IR(38396, 20), 460}, // 457 HitObjectTraceRayNV
  {IR(39672, 32), 504}, // 458 HitObjectTraceReorderExecuteEXT
  {IR(32047, 5), 117}, // 459 IAdd
  {IR(32224, 10), 138}, // 460 IAddCarry
  {IR(42522, 13), 606}, // 461 IAddSatINTEL
  {IR(42548, 14), 608}, // 462 IAverageINTEL
  {IR(42576, 21), 610}, // 463 IAverageRoundedINTEL
  {IR(32420, 7), 158}, // 464 IEqual
  {IR(32067, 5), 121}, // 465 IMul
  {IR(42644, 15), 614}, // 466 IMul32x16INTEL
  {IR(32427, 10), 159}, // 467 INotEqual
  {IR(32057, 5), 119}, // 468 ISub
  {IR(32234, 11), 139}, // 469 ISubBorrow
  {IR(42618, 13), 612}, // 470 ISubSatINTEL
  {IR(36465, 22), 381}, // 471 IgnoreIntersectionKHR
  {IR(40360, 21), 528}, // 472 IgnoreIntersectionNV
  {IR(28831, 6), 91}, // 473 Image
  {IR(37312, 29), 412}, // 474 ImageBlockMatchGatherSADQCOM
  {IR(37283, 29), 411}, // 475 ImageBlockMatchGatherSSDQCOM
  {IR(37185, 23), 407}, // 476 ImageBlockMatchSADQCOM
  {IR(37162, 23), 406}, // 477 ImageBlockMatchSSDQCOM
  {IR(37254, 29), 410}, // 478 ImageBlockMatchWindowSADQCOM
  {IR(37225, 29), 409}, // 479 ImageBlockMatchWindowSSDQCOM
  {IR(37143, 19), 405}, // 480 ImageBoxFilterQCOM
  {IR(31665, 16), 88}, // 481 ImageDrefGather
  {IR(31642, 11), 86}, // 482 ImageFetch
  {IR(31653, 12), 87}, // 483 ImageGather
  {IR(37419, 16), 417}, // 484 ImageGatherQCOM
  {IR(31702, 17), 92}, // 485 ImageQueryFormat
  {IR(31782, 17), 97}, // 486 ImageQueryLevels
  {IR(31768, 14), 96}, // 487 ImageQueryLod
  {IR(31719, 16), 93}, // 488 ImageQueryOrder
  {IR(31799, 18), 98}, // 489 ImageQuerySamples
  {IR(31753, 15), 95}, // 490 ImageQuerySize
  {IR(31735, 18), 94}, // 491 ImageQuerySizeLod
  {IR(31681, 10), 89}, // 492 ImageRead
  {IR(31499, 27), 81}, // 493 ImageSampleDrefExplicitLod
  {IR(31472, 27), 80}, // 494 ImageSampleDrefImplicitLod
  {IR(31449, 23), 79}, // 495 ImageSampleExplicitLod
  {IR(38931, 23), 482}, // 496 ImageSampleFootprintNV
  {IR(31403, 23), 78}, // 497 ImageSampleImplicitLod
  {IR(31611, 31), 85}, // 498 ImageSampleProjDrefExplicitLod
  {IR(31580, 31), 84}, // 499 ImageSampleProjDrefImplicitLod
  {IR(31553, 27), 83}, // 500 ImageSampleProjExplicitLod
  {IR(31526, 27), 82}, // 501 ImageSampleProjImplicitLod
  {IR(37119, 24), 404}, // 502 ImageSampleWeightedQCOM
  {IR(34606, 22), 288}, // 503 ImageSparseDrefGather
  {IR(34571, 17), 286}, // 504 ImageSparseFetch
  {IR(34588, 18), 287}, // 505 ImageSparseGather
  {IR(34698, 16), 293}, // 506 ImageSparseRead
  {IR(34398, 33), 281}, // 507 ImageSparseSampleDrefExplicitLod
  {IR(34365, 33), 280}, // 508 ImageSparseSampleDrefImplicitLod
  {IR(34336, 29), 279}, // 509 ImageSparseSampleExplicitLod
  {IR(34307, 29), 278}, // 510 ImageSparseSampleImplicitLod
  {IR(34534, 37), 285}, // 511 ImageSparseSampleProjDrefExplicitLod
  {IR(34497, 37), 284}, // 512 ImageSparseSampleProjDrefImplicitLod
  {IR(34464, 33), 283}, // 513 ImageSparseSampleProjExplicitLod
  {IR(34431, 33), 282}, // 514 ImageSparseSampleProjImplicitLod
  {IR(34628, 26), 289}, // 515 ImageSparseTexelsResident
  {IR(30882, 18), 53}, // 516 ImageTexelPointer
  {IR(31691, 11), 90}, // 517 ImageWrite
  {IR(30990, 20), 59}, // 518 InBoundsAccessChain
  {IR(31060, 23), 63}, // 519 InBoundsPtrAccessChain
  {IR(32291, 9), 146}, // 520 IsFinite
  {IR(41505, 22), 567}, // 521 IsHelperInvocationEXT
  {IR(32285, 6), 145}, // 522 IsInf
  {IR(32279, 6), 144}, // 523 IsNan
  {IR(37800, 23), 434}, // 524 IsNodePayloadValidAMDX
  {IR(32300, 9), 147}, // 525 IsNormal
  {IR(34220, 13), 273}, // 526 IsValidEvent
  {IR(33875, 17), 257}, // 527 IsValidReserveId
  {IR(33503, 5), 230}, // 528 Kill
  {IR(33420, 6), 226}, // 529 Label
  {IR(32320, 14), 149}, // 530 LessOrGreater
  {IR(33539, 14), 234}, // 531 LifetimeStart
  {IR(33553, 13), 235}, // 532 LifetimeStop
  {IR(29733, 5), 8}, // 533 Line
  {IR(30940, 5), 54}, // 534 Load
  {IR(32391, 11), 155}, // 535 LogicalAnd
  {IR(32352, 13), 152}, // 536 LogicalEqual
  {IR(32402, 11), 156}, // 537 LogicalNot
  {IR(32365, 16), 153}, // 538 LogicalNotEqual
  {IR(32381, 10), 154}, // 539 LogicalOr
  {IR(49547, 17), 789}, // 540 LoopControlINTEL
  {IR(33360, 10), 224}, // 541 LoopMerge
  {IR(52060, 18), 869}, // 542 MaskedGatherINTEL
  {IR(52078, 19), 870}, // 543 MaskedScatterINTEL
  {IR(32189, 18), 135}, // 544 MatrixTimesMatrix
  {IR(32135, 18), 132}, // 545 MatrixTimesScalar
  {IR(32171, 18), 134}, // 546 MatrixTimesVector
  {IR(31120, 15), 65}, // 547 MemberDecorate
  {IR(37976, 20), 443}, // 548 MemberDecorateIdEXT
  {IR(42844, 21), 626}, // 549 MemberDecorateString
  {IR(42865, 27), 626}, // 550 MemberDecorateStringGOOGLE
  {IR(29715, 11), 6}, // 551 MemberName
  {IR(33097, 14), 206}, // 552 MemoryBarrier
  {IR(29880, 12), 12}, // 553 MemoryModel
  {IR(34883, 19), 302}, // 554 MemoryNamedBarrier
  {IR(34902, 16), 303}, // 555 ModuleProcessed
  {IR(29710, 5), 5}, // 556 Name
  {IR(34860, 23), 301}, // 557 NamedBarrierInitialize
  {IR(34654, 7), 290}, // 558 NoLine
  {IR(37773, 27), 433}, // 559 NodePayloadArrayLengthAMDX
  {IR(29506, 4), 0}, // 560 Nop
  {IR(32831, 4), 186}, // 561 Not
  {IR(32334, 8), 150}, // 562 Ordered
  {IR(32207, 13), 136}, // 563 OuterProduct
  {IR(33326, 4), 223}, // 564 Phi
  {IR(38034, 10), 447}, // 565 PoisonKHR
  {IR(51863, 20), 858}, // 566 PredicatedLoadINTEL
  {IR(51883, 21), 859}, // 567 PredicatedStoreINTEL
  {IR(31010, 15), 60}, // 568 PtrAccessChain
  {IR(49982, 30), 804}, // 569 PtrCastToCrossWorkgroupALTERA
  {IR(50012, 29), 804}, // 570 PtrCastToCrossWorkgroupINTEL
  {IR(31964, 17), 111}, // 571 PtrCastToGeneric
  {IR(35750, 8), 343}, // 572 PtrDiff
  {IR(35729, 9), 341}, // 573 PtrEqual
  {IR(35738, 12), 342}, // 574 PtrNotEqual
  {IR(31892, 14), 106}, // 575 QuantizeToF16
  {IR(41810, 17), 578}, // 576 RawAccessChainNV
  {IR(37038, 31), 401}, // 577 RayQueryConfirmIntersectionKHR
  {IR(37006, 32), 400}, // 578 RayQueryGenerateIntersectionKHR
  {IR(40595, 23), 536}, // 579 RayQueryGetClusterIdNV
  {IR(50494, 39), 817}, // 580 RayQueryGetIntersectionBarycentricsKHR
  {IR(50569, 46), 819}, // 581 RayQueryGetIntersectionCandidateAABBOpaqueKHR
  {IR(40560, 35), 536}, // 582 RayQueryGetIntersectionClusterIdNV
  {IR(50533, 36), 818}, // 583 RayQueryGetIntersectionFrontFaceKHR
  {IR(50413, 40), 815}, // 584 RayQueryGetIntersectionGeometryIndexKHR
  {IR(50265, 46), 812}, // 585 RayQueryGetIntersectionInstanceCustomIndexKHR
  {IR(50311, 37), 813}, // 586 RayQueryGetIntersectionInstanceIdKHR
  {IR(50348, 65), 814}, // 587 RayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR
  {IR(41977, 37), 583}, // 588 RayQueryGetIntersectionLSSHitValueNV
  {IR(41905, 38), 581}, // 589 RayQueryGetIntersectionLSSPositionsNV
  {IR(41943, 34), 582}, // 590 RayQueryGetIntersectionLSSRadiiNV
  {IR(50615, 45), 820}, // 591 RayQueryGetIntersectionObjectRayDirectionKHR
  {IR(50660, 42), 821}, // 592 RayQueryGetIntersectionObjectRayOriginKHR
  {IR(50763, 40), 824}, // 593 RayQueryGetIntersectionObjectToWorldKHR
  {IR(50453, 41), 816}, // 594 RayQueryGetIntersectionPrimitiveIndexKHR
  {IR(41827, 40), 579}, // 595 RayQueryGetIntersectionSpherePositionNV
  {IR(41867, 38), 580}, // 596 RayQueryGetIntersectionSphereRadiusNV
  {IR(50237, 28), 811}, // 597 RayQueryGetIntersectionTKHR
  {IR(40435, 50), 533}, // 598 RayQueryGetIntersectionTriangleVertexPositionsKHR
  {IR(37088, 31), 403}, // 599 RayQueryGetIntersectionTypeKHR
  {IR(50803, 40), 825}, // 600 RayQueryGetIntersectionWorldToObjectKHR
  {IR(50214, 23), 810}, // 601 RayQueryGetRayFlagsKHR
  {IR(50192, 22), 809}, // 602 RayQueryGetRayTMinKHR
  {IR(50702, 32), 822}, // 603 RayQueryGetWorldRayDirectionKHR
  {IR(50734, 29), 823}, // 604 RayQueryGetWorldRayOriginKHR
  {IR(36963, 22), 398}, // 605 RayQueryInitializeKHR
  {IR(42185, 19), 591}, // 606 RayQueryIsLSSHitNV
  {IR(42163, 22), 590}, // 607 RayQueryIsSphereHitNV
  {IR(37069, 19), 402}, // 608 RayQueryProceedKHR
  {IR(36985, 21), 399}, // 609 RayQueryTerminateKHR
  {IR(37657, 13), 428}, // 610 ReadClockKHR
  {IR(33743, 9), 249}, // 611 ReadPipe
  {IR(50100, 23), 806}, // 612 ReadPipeBlockingALTERA
  {IR(50123, 22), 806}, // 613 ReadPipeBlockingINTEL
  {IR(34191, 13), 271}, // 614 ReleaseEvent
  {IR(39759, 25), 507}, // 615 ReorderThreadWithHintEXT
  {IR(38891, 24), 480}, // 616 ReorderThreadWithHintNV
  {IR(39784, 30), 508}, // 617 ReorderThreadWithHitObjectEXT
  {IR(38862, 29), 479}, // 618 ReorderThreadWithHitObjectNV
  {IR(40317, 22), 527}, // 619 ReportIntersectionKHR
  {IR(40339, 21), 527}, // 620 ReportIntersectionNV
  {IR(33797, 23), 253}, // 621 ReserveReadPipePackets
  {IR(33820, 24), 254}, // 622 ReserveWritePipePackets
  {IR(33762, 17), 251}, // 623 ReservedReadPipe
  {IR(33779, 18), 252}, // 624 ReservedWritePipe
  {IR(48074, 19), 747}, // 625 RestoreMemoryINTEL
  {IR(34179, 12), 270}, // 626 RetainEvent
  {IR(33508, 7), 231}, // 627 Return
  {IR(33515, 12), 232}, // 628 ReturnValue
  {IR(52042, 18), 868}, // 629 RoundFToTF32INTEL
  {IR(31874, 9), 104}, // 630 SConvert
  {IR(32082, 5), 124}, // 631 SDiv
  {IR(36550, 5), 383}, // 632 SDot
  {IR(36591, 11), 386}, // 633 SDotAccSat
  {IR(36602, 14), 386}, // 634 SDotAccSatKHR
  {IR(36555, 8), 383}, // 635 SDotKHR
  {IR(32450, 13), 161}, // 636 SGreaterThan
  {IR(32481, 18), 163}, // 637 SGreaterThanEqual
  {IR(32509, 10), 165}, // 638 SLessThan
  {IR(32534, 15), 167}, // 639 SLessThanEqual
  {IR(32102, 5), 128}, // 640 SMod
  {IR(32258, 13), 141}, // 641 SMulExtended
  {IR(32031, 8), 115}, // 642 SNegate
  {IR(32097, 5), 127}, // 643 SRem
  {IR(36576, 6), 385}, // 644 SUDot
  {IR(36641, 12), 388}, // 645 SUDotAccSat
  {IR(36653, 15), 388}, // 646 SUDotAccSatKHR
  {IR(36582, 9), 385}, // 647 SUDotKHR
  {IR(31358, 13), 77}, // 648 SampledImage
  {IR(41729, 29), 577}, // 649 SamplerImageAddressingModeNV
  {IR(31920, 15), 108}, // 650 SatConvertSToU
  {IR(31935, 15), 109}, // 651 SatConvertUToS
  {IR(48058, 16), 746}, // 652 SaveMemoryINTEL
  {IR(32413, 7), 157}, // 653 Select
  {IR(33405, 15), 225}, // 654 SelectionMerge
  {IR(39211, 18), 490}, // 655 SetMeshOutputsEXT
  {IR(34233, 19), 274}, // 656 SetUserEventStatus
  {IR(32782, 17), 182}, // 657 ShiftLeftLogical
  {IR(32761, 21), 181}, // 658 ShiftRightArithmetic
  {IR(32743, 18), 180}, // 659 ShiftRightLogical
  {IR(32309, 11), 148}, // 660 SignBitSet
  {IR(34714, 7), 294}, // 661 SizeOf
  {IR(29687, 7), 3}, // 662 Source
  {IR(29568, 16), 2}, // 663 SourceContinued
  {IR(29694, 16), 4}, // 664 SourceExtension
  {IR(30705, 13), 45}, // 665 SpecConstant
  {IR(51739, 30), 855}, // 666 SpecConstantArchitectureINTEL
  {IR(51806, 30), 856}, // 667 SpecConstantCapabilitiesINTEL
  {IR(30718, 22), 46}, // 668 SpecConstantComposite
  {IR(50937, 36), 830}, // 669 SpecConstantCompositeContinuedINTEL
  {IR(36882, 34), 395}, // 670 SpecConstantCompositeReplicateEXT
  {IR(38014, 20), 446}, // 671 SpecConstantDataKHR
  {IR(30687, 18), 44}, // 672 SpecConstantFalse
  {IR(30781, 15), 47}, // 673 SpecConstantOp
  {IR(37842, 23), 436}, // 674 SpecConstantStringAMDX
  {IR(51715, 24), 854}, // 675 SpecConstantTargetINTEL
  {IR(30670, 17), 43}, // 676 SpecConstantTrue
  {IR(35804, 25), 346}, // 677 StencilAttachmentReadEXT
  {IR(30945, 6), 55}, // 678 Store
  {IR(29726, 7), 7}, // 679 String
  {IR(51404, 25), 843}, // 680 Subgroup2DBlockLoadINTEL
  {IR(51429, 34), 844}, // 681 Subgroup2DBlockLoadTransformINTEL
  {IR(51463, 34), 845}, // 682 Subgroup2DBlockLoadTransposeINTEL
  {IR(51497, 29), 846}, // 683 Subgroup2DBlockPrefetchINTEL
  {IR(51526, 26), 847}, // 684 Subgroup2DBlockStoreINTEL
  {IR(36302, 20), 373}, // 685 SubgroupAllEqualKHR
  {IR(36272, 15), 371}, // 686 SubgroupAllKHR
  {IR(36287, 15), 372}, // 687 SubgroupAnyKHR
  {IR(46576, 30), 710}, // 688 SubgroupAvcBmeInitializeINTEL
  {IR(46546, 30), 709}, // 689 SubgroupAvcFmeInitializeINTEL
  {IR(44981, 35), 679}, // 690 SubgroupAvcImeAdjustRefOffsetINTEL
  {IR(45016, 39), 680}, // 691 SubgroupAvcImeConvertToMcePayloadINTEL
  {IR(45657, 38), 693}, // 692 SubgroupAvcImeConvertToMceResultINTEL
  {IR(45280, 45), 686}, // 693 SubgroupAvcImeEvaluateWithDualReferenceINTEL
  {IR(45380, 53), 688}, // 694 SubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL
  {IR(45601, 56), 692}, // 695 SubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL
  {IR(45489, 54), 690}, // 696 SubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL
  {IR(45233, 47), 685}, // 697 SubgroupAvcImeEvaluateWithSingleReferenceINTEL
  {IR(45325, 55), 687}, // 698 SubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL
  {IR(45543, 58), 691}, // 699 SubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL
  {IR(45433, 56), 689}, // 700 SubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL
  {IR(46289, 36), 704}, // 701 SubgroupAvcImeGetBorderReachedINTEL
  {IR(45741, 44), 695}, // 702 SubgroupAvcImeGetDualReferenceStreaminINTEL
  {IR(45695, 46), 694}, // 703 SubgroupAvcImeGetSingleReferenceStreaminINTEL
  {IR(46156, 66), 702}, // 704 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL
  {IR(46088, 68), 701}, // 705 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL
  {IR(46222, 67), 703}, // 706 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL
  {IR(45951, 68), 699}, // 707 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL
  {IR(45881, 70), 698}, // 708 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL
  {IR(46019, 69), 700}, // 709 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL
  {IR(46325, 48), 705}, // 710 SubgroupAvcImeGetTruncatedSearchIndicationINTEL
  {IR(46373, 59), 706}, // 711 SubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL
  {IR(46490, 56), 708}, // 712 SubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL
  {IR(46432, 58), 707}, // 713 SubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL
  {IR(44844, 30), 675}, // 714 SubgroupAvcImeInitializeINTEL
  {IR(44948, 33), 678}, // 715 SubgroupAvcImeRefWindowSizeINTEL
  {IR(44912, 36), 677}, // 716 SubgroupAvcImeSetDualReferenceINTEL
  {IR(45145, 54), 683}, // 717 SubgroupAvcImeSetEarlySearchTerminationThresholdINTEL
  {IR(45055, 43), 681}, // 718 SubgroupAvcImeSetMaxMotionVectorCountINTEL
  {IR(44874, 38), 676}, // 719 SubgroupAvcImeSetSingleReferenceINTEL
  {IR(45098, 47), 682}, // 720 SubgroupAvcImeSetUnidirectionalMixDisableINTEL
  {IR(45199, 34), 684}, // 721 SubgroupAvcImeSetWeightedSadINTEL
  {IR(45834, 47), 697}, // 722 SubgroupAvcImeStripDualReferenceStreamoutINTEL
  {IR(45785, 49), 696}, // 723 SubgroupAvcImeStripSingleReferenceStreamoutINTEL
  {IR(44234, 39), 660}, // 724 SubgroupAvcMceConvertToImePayloadINTEL
  {IR(44273, 38), 661}, // 725 SubgroupAvcMceConvertToImeResultINTEL
  {IR(44311, 39), 662}, // 726 SubgroupAvcMceConvertToRefPayloadINTEL
  {IR(44350, 38), 663}, // 727 SubgroupAvcMceConvertToRefResultINTEL
  {IR(44388, 39), 664}, // 728 SubgroupAvcMceConvertToSicPayloadINTEL
  {IR(44427, 38), 665}, // 729 SubgroupAvcMceConvertToSicResultINTEL
  {IR(44540, 43), 668}, // 730 SubgroupAvcMceGetBestInterDistortionsINTEL
  {IR(43672, 50), 649}, // 731 SubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL
  {IR(43270, 60), 641}, // 732 SubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL
  {IR(43470, 51), 645}, // 733 SubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL
  {IR(43616, 56), 648}, // 734 SubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL
  {IR(43383, 47), 643}, // 735 SubgroupAvcMceGetDefaultInterShapePenaltyINTEL
  {IR(43971, 56), 655}, // 736 SubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL
  {IR(43870, 50), 653}, // 737 SubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL
  {IR(43565, 51), 647}, // 738 SubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL
  {IR(43774, 49), 651}, // 739 SubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL
  {IR(43722, 52), 650}, // 740 SubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL
  {IR(43920, 51), 654}, // 741 SubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL
  {IR(44659, 38), 671}, // 742 SubgroupAvcMceGetInterDirectionsINTEL
  {IR(44501, 39), 667}, // 743 SubgroupAvcMceGetInterDistortionsINTEL
  {IR(44583, 38), 669}, // 744 SubgroupAvcMceGetInterMajorShapeINTEL
  {IR(44621, 38), 670}, // 745 SubgroupAvcMceGetInterMinorShapeINTEL
  {IR(44697, 45), 672}, // 746 SubgroupAvcMceGetInterMotionVectorCountINTEL
  {IR(44742, 40), 673}, // 747 SubgroupAvcMceGetInterReferenceIdsINTEL
  {IR(44782, 62), 674}, // 748 SubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL
  {IR(44465, 36), 666}, // 749 SubgroupAvcMceGetMotionVectorsINTEL
  {IR(44027, 33), 656}, // 750 SubgroupAvcMceSetAcOnlyHaarINTEL
  {IR(44173, 61), 659}, // 751 SubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL
  {IR(43330, 53), 642}, // 752 SubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL
  {IR(43521, 44), 646}, // 753 SubgroupAvcMceSetInterDirectionPenaltyINTEL
  {IR(43430, 40), 644}, // 754 SubgroupAvcMceSetInterShapePenaltyINTEL
  {IR(43823, 47), 652}, // 755 SubgroupAvcMceSetMotionVectorCostFunctionINTEL
  {IR(44112, 61), 658}, // 756 SubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL
  {IR(44060, 52), 657}, // 757 SubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL
  {IR(46606, 39), 711}, // 758 SubgroupAvcRefConvertToMcePayloadINTEL
  {IR(46928, 38), 718}, // 759 SubgroupAvcRefConvertToMceResultINTEL
  {IR(46781, 45), 715}, // 760 SubgroupAvcRefEvaluateWithDualReferenceINTEL
  {IR(46826, 46), 716}, // 761 SubgroupAvcRefEvaluateWithMultiReferenceINTEL
  {IR(46872, 56), 717}, // 762 SubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL
  {IR(46734, 47), 714}, // 763 SubgroupAvcRefEvaluateWithSingleReferenceINTEL
  {IR(46645, 46), 712}, // 764 SubgroupAvcRefSetBidirectionalMixDisableINTEL
  {IR(46691, 43), 713}, // 765 SubgroupAvcRefSetBilinearFilterEnableINTEL
  {IR(47064, 42), 722}, // 766 SubgroupAvcSicConfigureIpeLumaChromaINTEL
  {IR(47028, 36), 721}, // 767 SubgroupAvcSicConfigureIpeLumaINTEL
  {IR(46996, 32), 720}, // 768 SubgroupAvcSicConfigureSkcINTEL
  {IR(47145, 39), 724}, // 769 SubgroupAvcSicConvertToMcePayloadINTEL
  {IR(47685, 38), 736}, // 770 SubgroupAvcSicConvertToMceResultINTEL
  {IR(47460, 31), 731}, // 771 SubgroupAvcSicEvaluateIpeINTEL
  {IR(47538, 45), 733}, // 772 SubgroupAvcSicEvaluateWithDualReferenceINTEL
  {IR(47583, 46), 734}, // 773 SubgroupAvcSicEvaluateWithMultiReferenceINTEL
  {IR(47629, 56), 735}, // 774 SubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL
  {IR(47491, 47), 732}, // 775 SubgroupAvcSicEvaluateWithSingleReferenceINTEL
  {IR(47802, 46), 739}, // 776 SubgroupAvcSicGetBestIpeChromaDistortionINTEL
  {IR(47758, 44), 738}, // 777 SubgroupAvcSicGetBestIpeLumaDistortionINTEL
  {IR(48023, 35), 744}, // 778 SubgroupAvcSicGetInterRawSadsINTEL
  {IR(47889, 36), 741}, // 779 SubgroupAvcSicGetIpeChromaModeINTEL
  {IR(47723, 35), 737}, // 780 SubgroupAvcSicGetIpeLumaShapeINTEL
  {IR(47106, 39), 723}, // 781 SubgroupAvcSicGetMotionVectorMaskINTEL
  {IR(47848, 41), 740}, // 782 SubgroupAvcSicGetPackedIpeLumaModesINTEL
  {IR(47925, 50), 742}, // 783 SubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL
  {IR(47975, 48), 743}, // 784 SubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL
  {IR(46966, 30), 719}, // 785 SubgroupAvcSicInitializeINTEL
  {IR(47326, 43), 728}, // 786 SubgroupAvcSicSetBilinearFilterEnableINTEL
  {IR(47417, 43), 730}, // 787 SubgroupAvcSicSetBlockBasedRawSkipSadINTEL
  {IR(47276, 50), 727}, // 788 SubgroupAvcSicSetIntraChromaModeCostFunctionINTEL
  {IR(47228, 48), 726}, // 789 SubgroupAvcSicSetIntraLumaModeCostFunctionINTEL
  {IR(47184, 44), 725}, // 790 SubgroupAvcSicSetIntraLumaShapePenaltyINTEL
  {IR(47369, 48), 729}, // 791 SubgroupAvcSicSetSkcForwardTransformEnableINTEL
  {IR(6696, 18), 364}, // 792 SubgroupBallotKHR
  {IR(51377, 27), 842}, // 793 SubgroupBlockPrefetchINTEL
  {IR(42276, 23), 596}, // 794 SubgroupBlockReadINTEL
  {IR(42299, 24), 597}, // 795 SubgroupBlockWriteINTEL
  {IR(36139, 27), 365}, // 796 SubgroupFirstInvocationKHR
  {IR(42323, 28), 598}, // 797 SubgroupImageBlockReadINTEL
  {IR(42351, 29), 599}, // 798 SubgroupImageBlockWriteINTEL
  {IR(42380, 33), 600}, // 799 SubgroupImageMediaBlockReadINTEL
  {IR(42413, 34), 601}, // 800 SubgroupImageMediaBlockWriteINTEL
  {IR(16295, 38), 848}, // 801 SubgroupMatrixMultiplyAccumulateINTEL
  {IR(36322, 26), 375}, // 802 SubgroupReadInvocationKHR
  {IR(42204, 25), 593}, // 803 SubgroupShuffleDownINTEL
  {IR(13893, 21), 592}, // 804 SubgroupShuffleINTEL
  {IR(42229, 23), 594}, // 805 SubgroupShuffleUpINTEL
  {IR(42252, 24), 595}, // 806 SubgroupShuffleXorINTEL
  {IR(33496, 7), 229}, // 807 Switch
  {IR(51191, 24), 838}, // 808 TaskSequenceAsyncALTERA
  {IR(51215, 23), 838}, // 809 TaskSequenceAsyncINTEL
  {IR(51142, 25), 837}, // 810 TaskSequenceCreateALTERA
  {IR(51167, 24), 837}, // 811 TaskSequenceCreateINTEL
  {IR(51238, 22), 839}, // 812 TaskSequenceGetALTERA
  {IR(51260, 21), 839}, // 813 TaskSequenceGetINTEL
  {IR(51281, 26), 840}, // 814 TaskSequenceReleaseALTERA
  {IR(51307, 25), 840}, // 815 TaskSequenceReleaseINTEL
  {IR(41547, 27), 569}, // 816 TensorLayoutSetBlockSizeNV
  {IR(41411, 28), 562}, // 817 TensorLayoutSetClampValueNV
  {IR(41340, 27), 559}, // 818 TensorLayoutSetDimensionNV
  {IR(41367, 24), 560}, // 819 TensorLayoutSetStrideNV
  {IR(41391, 20), 561}, // 820 TensorLayoutSliceNV
  {IR(35914, 19), 350}, // 821 TensorQuerySizeARM
  {IR(35885, 14), 348}, // 822 TensorReadARM
  {IR(41527, 20), 568}, // 823 TensorViewSetClipNV
  {IR(41458, 25), 564}, // 824 TensorViewSetDimensionNV
  {IR(41483, 22), 565}, // 825 TensorViewSetStrideNV
  {IR(35899, 15), 349}, // 826 TensorWriteARM
  {IR(36026, 20), 359}, // 827 TerminateInvocation
  {IR(36487, 16), 382}, // 828 TerminateRayKHR
  {IR(40381, 15), 529}, // 829 TerminateRayNV
  {IR(40404, 14), 531}, // 830 TraceMotionNV
  {IR(40396, 8), 530}, // 831 TraceNV
  {IR(36399, 12), 378}, // 832 TraceRayKHR
  {IR(40418, 17), 532}, // 833 TraceRayMotionNV
  {IR(31348, 10), 76}, // 834 Transpose
  {IR(40485, 29), 534}, // 835 TypeAccelerationStructureKHR
  {IR(40514, 28), 534}, // 836 TypeAccelerationStructureNV
  {IR(30297, 10), 25}, // 837 TypeArray
  {IR(43189, 37), 638}, // 838 TypeAvcImeDualReferenceStreaminINTEL
  {IR(42924, 23), 629}, // 839 TypeAvcImePayloadINTEL
  {IR(43106, 44), 636}, // 840 TypeAvcImeResultDualReferenceStreamoutINTEL
  {IR(43038, 22), 634}, // 841 TypeAvcImeResultINTEL
  {IR(43060, 46), 635}, // 842 TypeAvcImeResultSingleReferenceStreamoutINTEL
  {IR(43150, 39), 637}, // 843 TypeAvcImeSingleReferenceStreaminINTEL
  {IR(42993, 23), 632}, // 844 TypeAvcMcePayloadINTEL
  {IR(43016, 22), 633}, // 845 TypeAvcMceResultINTEL
  {IR(42947, 23), 630}, // 846 TypeAvcRefPayloadINTEL
  {IR(43226, 22), 639}, // 847 TypeAvcRefResultINTEL
  {IR(42970, 23), 631}, // 848 TypeAvcSicPayloadINTEL
  {IR(43248, 22), 640}, // 849 TypeAvcSicResultINTEL
  {IR(30059, 9), 17}, // 850 TypeBool
  {IR(37917, 14), 439}, // 851 TypeBufferEXT
  {IR(50857, 23), 827}, // 852 TypeBufferSurfaceINTEL
  {IR(36668, 25), 389}, // 853 TypeCooperativeMatrixKHR
  {IR(40807, 24), 544}, // 854 TypeCooperativeMatrixNV
  {IR(38970, 24), 483}, // 855 TypeCooperativeVectorNV
  {IR(30412, 16), 32}, // 856 TypeDeviceEvent
  {IR(30402, 10), 31}, // 857 TypeEvent
  {IR(30113, 10), 19}, // 858 TypeFloat
  {IR(30461, 19), 36}, // 859 TypeForwardPointer
  {IR(30389, 13), 30}, // 860 TypeFunction
  {IR(36013, 13), 357}, // 861 TypeGraphARM
  {IR(39742, 17), 506}, // 862 TypeHitObjectEXT
  {IR(38915, 16), 481}, // 863 TypeHitObjectNV
  {IR(30258, 10), 22}, // 864 TypeImage
  {IR(30068, 8), 18}, // 865 TypeInt
  {IR(30134, 11), 21}, // 866 TypeMatrix
  {IR(34843, 17), 300}, // 867 TypeNamedBarrier
  {IR(37719, 25), 431}, // 868 TypeNodePayloadArrayAMDX
  {IR(30335, 11), 28}, // 869 TypeOpaque
  {IR(30452, 9), 35}, // 870 TypePipe
  {IR(34721, 16), 295}, // 871 TypePipeStorage
  {IR(30377, 12), 29}, // 872 TypePointer
  {IR(30442, 10), 34}, // 873 TypeQueue
  {IR(36947, 16), 397}, // 874 TypeRayQueryKHR
  {IR(30428, 14), 33}, // 875 TypeReserveId
  {IR(30307, 17), 26}, // 876 TypeRuntimeArray
  {IR(30280, 17), 24}, // 877 TypeSampledImage
  {IR(30268, 12), 23}, // 878 TypeSampler
  {IR(30324, 11), 27}, // 879 TypeStruct
  {IR(50880, 25), 828}, // 880 TypeStructContinuedINTEL
  {IR(51332, 23), 841}, // 881 TypeTaskSequenceALTERA
  {IR(51355, 22), 841}, // 882 TypeTaskSequenceINTEL
  {IR(35829, 14), 347}, // 883 TypeTensorARM
  {IR(41283, 19), 556}, // 884 TypeTensorLayoutNV
  {IR(41302, 17), 557}, // 885 TypeTensorViewNV
  {IR(36046, 22), 360}, // 886 TypeUntypedPointerKHR
  {IR(30123, 11), 20}, // 887 TypeVector
  {IR(38954, 16), 483}, // 888 TypeVectorIdEXT
  {IR(42906, 18), 628}, // 889 TypeVmeImageINTEL
  {IR(30050, 9), 16}, // 890 TypeVoid
  {IR(42535, 13), 607}, // 891 UAddSatINTEL
  {IR(42562, 14), 609}, // 892 UAverageINTEL
  {IR(42597, 21), 611}, // 893 UAverageRoundedINTEL
  {IR(31865, 9), 103}, // 894 UConvert
  {IR(42447, 24), 602}, // 895 UCountLeadingZerosINTEL
  {IR(42471, 25), 603}, // 896 UCountTrailingZerosINTEL
  {IR(32077, 5), 123}, // 897 UDiv
  {IR(36563, 5), 384}, // 898 UDot
  {IR(36616, 11), 387}, // 899 UDotAccSat
  {IR(36627, 14), 387}, // 900 UDotAccSatKHR
  {IR(36568, 8), 384}, // 901 UDotKHR
  {IR(32437, 13), 160}, // 902 UGreaterThan
  {IR(32463, 18), 162}, // 903 UGreaterThanEqual
  {IR(32499, 10), 164}, // 904 ULessThan
  {IR(32519, 15), 166}, // 905 ULessThanEqual
  {IR(32092, 5), 126}, // 906 UMod
  {IR(42659, 15), 615}, // 907 UMul32x16INTEL
  {IR(32245, 13), 140}, // 908 UMulExtended
  {IR(42631, 13), 613}, // 909 USubSatINTEL
  {IR(29562, 6), 1}, // 910 Undef
  {IR(32342, 10), 151}, // 911 Unordered
  {IR(33527, 12), 233}, // 912 Unreachable
  {IR(36087, 22), 362}, // 913 UntypedAccessChainKHR
  {IR(36224, 22), 368}, // 914 UntypedArrayLengthKHR
  {IR(36374, 25), 377}, // 915 UntypedGroupAsyncCopyKHR
  {IR(37948, 28), 442}, // 916 UntypedImageTexelPointerEXT
  {IR(36109, 30), 363}, // 917 UntypedInBoundsAccessChainKHR
  {IR(36191, 33), 367}, // 918 UntypedInBoundsPtrAccessChainKHR
  {IR(36246, 19), 369}, // 919 UntypedPrefetchKHR
  {IR(36166, 25), 366}, // 920 UntypedPtrAccessChainKHR
  {IR(36068, 19), 361}, // 921 UntypedVariableKHR
  {IR(16361, 32), 850}, // 922 UntypedVariableLengthArrayINTEL
  {IR(30873, 9), 52}, // 923 Variable
  {IR(14349, 25), 745}, // 924 VariableLengthArrayINTEL
  {IR(31230, 21), 69}, // 925 VectorExtractDynamic
  {IR(31251, 20), 70}, // 926 VectorInsertDynamic
  {IR(31271, 14), 71}, // 927 VectorShuffle
  {IR(32153, 18), 133}, // 928 VectorTimesMatrix
  {IR(32117, 18), 131}, // 929 VectorTimesScalar
  {IR(42892, 14), 627}, // 930 VmeImageINTEL
  {IR(39284, 33), 492}, // 931 WritePackedPrimitiveIndices4x8NV
  {IR(33752, 10), 250}, // 932 WritePipe
  {IR(50145, 24), 807}, // 933 WritePipeBlockingALTERA
  {IR(50169, 23), 807}, // 934 WritePipeBlockingINTEL
}};

// Extended instruction descriptions, ordered by (extinst enum, opcode value).
// The fields in order are:
//   enum value
//   operands, an IndexRange into kOperandSpans
//   name, a character-counting IndexRange into kStrings
//   capabilities, an IndexRange into kCapabilitySpans
static const std::array<ExtInstDesc, 425> kExtInstByValue{{
    {0,IR(0, 0),IR(52241, 14),IR(1, 0)}, // DebugInfoNone in debuginfo
    {1,IR(52, 3),IR(52255, 21),IR(1, 0)}, // DebugCompilationUnit in debuginfo
    {2,IR(811, 3),IR(52328, 15),IR(1, 0)}, // DebugTypeBasic in debuginfo
    {3,IR(814, 3),IR(52377, 17),IR(1, 0)}, // DebugTypePointer in debuginfo
    {4,IR(817, 2),IR(52432, 19),IR(1, 0)}, // DebugTypeQualifier in debuginfo
    {5,IR(168, 2),IR(52451, 15),IR(1, 0)}, // DebugTypeArray in debuginfo
    {6,IR(261, 2),IR(52466, 16),IR(1, 0)}, // DebugTypeVector in debuginfo
    {7,IR(819, 6),IR(52482, 13),IR(1, 0)}, // DebugTypedef in debuginfo
    {8,IR(168, 2),IR(52495, 18),IR(1, 0)}, // DebugTypeFunction in debuginfo
    {9,IR(825, 9),IR(52513, 14),IR(1, 0)}, // DebugTypeEnum in debuginfo
    {10,IR(834, 9),IR(52565, 19),IR(1, 0)}, // DebugTypeComposite in debuginfo
    {11,IR(843, 10),IR(52584, 16),IR(1, 0)}, // DebugTypeMember in debuginfo
    {12,IR(853, 5),IR(52600, 21),IR(1, 0)}, // DebugTypeInheritance in debuginfo
    {13,IR(36, 2),IR(52621, 21),IR(1, 0)}, // DebugTypePtrToMember in debuginfo
    {14,IR(168, 2),IR(52642, 18),IR(1, 0)}, // DebugTypeTemplate in debuginfo
    {15,IR(858, 6),IR(52660, 27),IR(1, 0)}, // DebugTypeTemplateParameter in debuginfo
    {16,IR(864, 5),IR(52687, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in debuginfo
    {17,IR(869, 5),IR(52722, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in debuginfo
    {18,IR(843, 10),IR(52753, 20),IR(1, 0)}, // DebugGlobalVariable in debuginfo
    {19,IR(874, 8),IR(52773, 25),IR(1, 0)}, // DebugFunctionDeclaration in debuginfo
    {20,IR(882, 11),IR(52798, 14),IR(1, 0)}, // DebugFunction in debuginfo
    {21,IR(893, 5),IR(52812, 18),IR(1, 0)}, // DebugLexicalBlock in debuginfo
    {22,IR(898, 3),IR(52830, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in debuginfo
    {23,IR(901, 2),IR(52861, 11),IR(1, 0)}, // DebugScope in debuginfo
    {24,IR(0, 0),IR(52872, 13),IR(1, 0)}, // DebugNoScope in debuginfo
    {25,IR(903, 3),IR(52885, 15),IR(1, 0)}, // DebugInlinedAt in debuginfo
    {26,IR(906, 7),IR(52942, 19),IR(1, 0)}, // DebugLocalVariable in debuginfo
    {27,IR(36, 2),IR(52961, 21),IR(1, 0)}, // DebugInlinedVariable in debuginfo
    {28,IR(33, 3),IR(52982, 13),IR(1, 0)}, // DebugDeclare in debuginfo
    {29,IR(375, 3),IR(52995, 11),IR(1, 0)}, // DebugValue in debuginfo
    {30,IR(913, 2),IR(53039, 15),IR(1, 0)}, // DebugOperation in debuginfo
    {31,IR(747, 1),IR(53054, 16),IR(1, 0)}, // DebugExpression in debuginfo
    {32,IR(915, 4),IR(53070, 14),IR(1, 0)}, // DebugMacroDef in debuginfo
    {33,IR(898, 3),IR(53084, 16),IR(1, 0)}, // DebugMacroUndef in debuginfo
    {1,IR(10, 1),IR(53100, 6),IR(1, 0)}, // Round in glsl_std_450
    {2,IR(10, 1),IR(53106, 10),IR(1, 0)}, // RoundEven in glsl_std_450
    {3,IR(10, 1),IR(53116, 6),IR(1, 0)}, // Trunc in glsl_std_450
    {4,IR(10, 1),IR(53122, 5),IR(1, 0)}, // FAbs in glsl_std_450
    {5,IR(10, 1),IR(53127, 5),IR(1, 0)}, // SAbs in glsl_std_450
    {6,IR(10, 1),IR(53132, 6),IR(1, 0)}, // FSign in glsl_std_450
    {7,IR(10, 1),IR(53138, 6),IR(1, 0)}, // SSign in glsl_std_450
    {8,IR(10, 1),IR(53144, 6),IR(1, 0)}, // Floor in glsl_std_450
    {9,IR(10, 1),IR(53150, 5),IR(1, 0)}, // Ceil in glsl_std_450
    {10,IR(10, 1),IR(53155, 6),IR(1, 0)}, // Fract in glsl_std_450
    {11,IR(10, 1),IR(53161, 8),IR(1, 0)}, // Radians in glsl_std_450
    {12,IR(10, 1),IR(53169, 8),IR(1, 0)}, // Degrees in glsl_std_450
    {13,IR(10, 1),IR(53177, 4),IR(1, 0)}, // Sin in glsl_std_450
    {14,IR(10, 1),IR(53181, 4),IR(1, 0)}, // Cos in glsl_std_450
    {15,IR(10, 1),IR(53185, 4),IR(1, 0)}, // Tan in glsl_std_450
    {16,IR(10, 1),IR(53189, 5),IR(1, 0)}, // Asin in glsl_std_450
    {17,IR(10, 1),IR(53194, 5),IR(1, 0)}, // Acos in glsl_std_450
    {18,IR(10, 1),IR(53199, 5),IR(1, 0)}, // Atan in glsl_std_450
    {19,IR(10, 1),IR(53204, 5),IR(1, 0)}, // Sinh in glsl_std_450
    {20,IR(10, 1),IR(53209, 5),IR(1, 0)}, // Cosh in glsl_std_450
    {21,IR(10, 1),IR(53214, 5),IR(1, 0)}, // Tanh in glsl_std_450
    {22,IR(10, 1),IR(53219, 6),IR(1, 0)}, // Asinh in glsl_std_450
    {23,IR(10, 1),IR(53225, 6),IR(1, 0)}, // Acosh in glsl_std_450
    {24,IR(10, 1),IR(53231, 6),IR(1, 0)}, // Atanh in glsl_std_450
    {25,IR(36, 2),IR(53237, 6),IR(1, 0)}, // Atan2 in glsl_std_450
    {26,IR(36, 2),IR(53243, 4),IR(1, 0)}, // Pow in glsl_std_450
    {27,IR(10, 1),IR(53247, 4),IR(1, 0)}, // Exp in glsl_std_450
    {28,IR(10, 1),IR(53251, 4),IR(1, 0)}, // Log in glsl_std_450
    {29,IR(10, 1),IR(53255, 5),IR(1, 0)}, // Exp2 in glsl_std_450
    {30,IR(10, 1),IR(53260, 5),IR(1, 0)}, // Log2 in glsl_std_450
    {31,IR(10, 1),IR(53265, 5),IR(1, 0)}, // Sqrt in glsl_std_450
    {32,IR(10, 1),IR(53270, 12),IR(1, 0)}, // InverseSqrt in glsl_std_450
    {33,IR(10, 1),IR(53282, 12),IR(1, 0)}, // Determinant in glsl_std_450
    {34,IR(10, 1),IR(53294, 14),IR(1, 0)}, // MatrixInverse in glsl_std_450
    {35,IR(36, 2),IR(53308, 5),IR(1, 0)}, // Modf in glsl_std_450
    {36,IR(10, 1),IR(53313, 11),IR(1, 0)}, // ModfStruct in glsl_std_450
    {37,IR(36, 2),IR(53324, 5),IR(1, 0)}, // FMin in glsl_std_450
    {38,IR(36, 2),IR(53329, 5),IR(1, 0)}, // UMin in glsl_std_450
    {39,IR(36, 2),IR(53334, 5),IR(1, 0)}, // SMin in glsl_std_450
    {40,IR(36, 2),IR(53339, 5),IR(1, 0)}, // FMax in glsl_std_450
    {41,IR(36, 2),IR(53344, 5),IR(1, 0)}, // UMax in glsl_std_450
    {42,IR(36, 2),IR(53349, 5),IR(1, 0)}, // SMax in glsl_std_450
    {43,IR(33, 3),IR(53354, 7),IR(1, 0)}, // FClamp in glsl_std_450
    {44,IR(33, 3),IR(53361, 7),IR(1, 0)}, // UClamp in glsl_std_450
    {45,IR(33, 3),IR(53368, 7),IR(1, 0)}, // SClamp in glsl_std_450
    {46,IR(33, 3),IR(53375, 5),IR(1, 0)}, // FMix in glsl_std_450
    {47,IR(33, 3),IR(53380, 5),IR(1, 0)}, // IMix in glsl_std_450
    {48,IR(36, 2),IR(53385, 5),IR(1, 0)}, // Step in glsl_std_450
    {49,IR(33, 3),IR(53390, 11),IR(1, 0)}, // SmoothStep in glsl_std_450
    {50,IR(33, 3),IR(53401, 4),IR(1, 0)}, // Fma in glsl_std_450
    {51,IR(36, 2),IR(53405, 6),IR(1, 0)}, // Frexp in glsl_std_450
    {52,IR(10, 1),IR(53411, 12),IR(1, 0)}, // FrexpStruct in glsl_std_450
    {53,IR(36, 2),IR(53423, 6),IR(1, 0)}, // Ldexp in glsl_std_450
    {54,IR(10, 1),IR(53429, 13),IR(1, 0)}, // PackSnorm4x8 in glsl_std_450
    {55,IR(10, 1),IR(53442, 13),IR(1, 0)}, // PackUnorm4x8 in glsl_std_450
    {56,IR(10, 1),IR(53455, 14),IR(1, 0)}, // PackSnorm2x16 in glsl_std_450
    {57,IR(10, 1),IR(53469, 14),IR(1, 0)}, // PackUnorm2x16 in glsl_std_450
    {58,IR(10, 1),IR(53483, 13),IR(1, 0)}, // PackHalf2x16 in glsl_std_450
    {59,IR(10, 1),IR(53496, 15),IR(346, 1)}, // PackDouble2x32 in glsl_std_450
    {60,IR(10, 1),IR(53511, 16),IR(1, 0)}, // UnpackSnorm2x16 in glsl_std_450
    {61,IR(10, 1),IR(53527, 16),IR(1, 0)}, // UnpackUnorm2x16 in glsl_std_450
    {62,IR(10, 1),IR(53543, 15),IR(1, 0)}, // UnpackHalf2x16 in glsl_std_450
    {63,IR(10, 1),IR(53558, 15),IR(1, 0)}, // UnpackSnorm4x8 in glsl_std_450
    {64,IR(10, 1),IR(53573, 15),IR(1, 0)}, // UnpackUnorm4x8 in glsl_std_450
    {65,IR(10, 1),IR(53588, 17),IR(346, 1)}, // UnpackDouble2x32 in glsl_std_450
    {66,IR(10, 1),IR(53605, 7),IR(1, 0)}, // Length in glsl_std_450
    {67,IR(36, 2),IR(53612, 9),IR(1, 0)}, // Distance in glsl_std_450
    {68,IR(36, 2),IR(53621, 6),IR(1, 0)}, // Cross in glsl_std_450
    {69,IR(10, 1),IR(53627, 10),IR(1, 0)}, // Normalize in glsl_std_450
    {70,IR(33, 3),IR(53637, 12),IR(1, 0)}, // FaceForward in glsl_std_450
    {71,IR(36, 2),IR(53649, 8),IR(1, 0)}, // Reflect in glsl_std_450
    {72,IR(33, 3),IR(53657, 8),IR(1, 0)}, // Refract in glsl_std_450
    {73,IR(10, 1),IR(53665, 9),IR(1, 0)}, // FindILsb in glsl_std_450
    {74,IR(10, 1),IR(53674, 9),IR(1, 0)}, // FindSMsb in glsl_std_450
    {75,IR(10, 1),IR(53683, 9),IR(1, 0)}, // FindUMsb in glsl_std_450
    {76,IR(10, 1),IR(53692, 22),IR(347, 1)}, // InterpolateAtCentroid in glsl_std_450
    {77,IR(36, 2),IR(53714, 20),IR(347, 1)}, // InterpolateAtSample in glsl_std_450
    {78,IR(36, 2),IR(53734, 20),IR(347, 1)}, // InterpolateAtOffset in glsl_std_450
    {79,IR(36, 2),IR(53754, 5),IR(1, 0)}, // NMin in glsl_std_450
    {80,IR(36, 2),IR(53759, 5),IR(1, 0)}, // NMax in glsl_std_450
    {81,IR(33, 3),IR(53764, 7),IR(1, 0)}, // NClamp in glsl_std_450
    {1,IR(399, 5),IR(5915, 7),IR(1, 0)}, // Kernel in nonsemantic_clspvreflection
    {2,IR(919, 5),IR(53771, 13),IR(1, 0)}, // ArgumentInfo in nonsemantic_clspvreflection
    {3,IR(593, 5),IR(53784, 22),IR(1, 0)}, // ArgumentStorageBuffer in nonsemantic_clspvreflection
    {4,IR(593, 5),IR(53806, 16),IR(1, 0)}, // ArgumentUniform in nonsemantic_clspvreflection
    {5,IR(557, 7),IR(53822, 25),IR(1, 0)}, // ArgumentPodStorageBuffer in nonsemantic_clspvreflection
    {6,IR(557, 7),IR(53847, 19),IR(1, 0)}, // ArgumentPodUniform in nonsemantic_clspvreflection
    {7,IR(593, 5),IR(53866, 24),IR(1, 0)}, // ArgumentPodPushConstant in nonsemantic_clspvreflection
    {8,IR(593, 5),IR(53890, 21),IR(1, 0)}, // ArgumentSampledImage in nonsemantic_clspvreflection
    {9,IR(593, 5),IR(53911, 21),IR(1, 0)}, // ArgumentStorageImage in nonsemantic_clspvreflection
    {10,IR(593, 5),IR(53932, 16),IR(1, 0)}, // ArgumentSampler in nonsemantic_clspvreflection
    {11,IR(593, 5),IR(53948, 18),IR(1, 0)}, // ArgumentWorkgroup in nonsemantic_clspvreflection
    {12,IR(33, 3),IR(53966, 26),IR(1, 0)}, // SpecConstantWorkgroupSize in nonsemantic_clspvreflection
    {13,IR(33, 3),IR(53992, 25),IR(1, 0)}, // SpecConstantGlobalOffset in nonsemantic_clspvreflection
    {14,IR(10, 1),IR(54017, 20),IR(1, 0)}, // SpecConstantWorkDim in nonsemantic_clspvreflection
    {15,IR(36, 2),IR(54037, 25),IR(1, 0)}, // PushConstantGlobalOffset in nonsemantic_clspvreflection
    {16,IR(36, 2),IR(54062, 30),IR(1, 0)}, // PushConstantEnqueuedLocalSize in nonsemantic_clspvreflection
    {17,IR(36, 2),IR(54092, 23),IR(1, 0)}, // PushConstantGlobalSize in nonsemantic_clspvreflection
    {18,IR(36, 2),IR(54115, 25),IR(1, 0)}, // PushConstantRegionOffset in nonsemantic_clspvreflection
    {19,IR(36, 2),IR(54140, 26),IR(1, 0)}, // PushConstantNumWorkgroups in nonsemantic_clspvreflection
    {20,IR(36, 2),IR(54166, 30),IR(1, 0)}, // PushConstantRegionGroupOffset in nonsemantic_clspvreflection
    {21,IR(33, 3),IR(54196, 26),IR(1, 0)}, // ConstantDataStorageBuffer in nonsemantic_clspvreflection
    {22,IR(33, 3),IR(54222, 20),IR(1, 0)}, // ConstantDataUniform in nonsemantic_clspvreflection
    {23,IR(33, 3),IR(9389, 15),IR(1, 0)}, // LiteralSampler in nonsemantic_clspvreflection
    {24,IR(296, 4),IR(54242, 30),IR(1, 0)}, // PropertyRequiredWorkgroupSize in nonsemantic_clspvreflection
    {25,IR(10, 1),IR(54272, 28),IR(1, 0)}, // SpecConstantSubgroupMaxSize in nonsemantic_clspvreflection
    {26,IR(593, 5),IR(54300, 28),IR(1, 0)}, // ArgumentPointerPushConstant in nonsemantic_clspvreflection
    {27,IR(557, 7),IR(54328, 23),IR(1, 0)}, // ArgumentPointerUniform in nonsemantic_clspvreflection
    {28,IR(33, 3),IR(54351, 35),IR(1, 0)}, // ProgramScopeVariablesStorageBuffer in nonsemantic_clspvreflection
    {29,IR(33, 3),IR(54386, 38),IR(1, 0)}, // ProgramScopeVariablePointerRelocation in nonsemantic_clspvreflection
    {30,IR(296, 4),IR(54424, 42),IR(1, 0)}, // ImageArgumentInfoChannelOrderPushConstant in nonsemantic_clspvreflection
    {31,IR(296, 4),IR(54466, 45),IR(1, 0)}, // ImageArgumentInfoChannelDataTypePushConstant in nonsemantic_clspvreflection
    {32,IR(535, 6),IR(54511, 37),IR(1, 0)}, // ImageArgumentInfoChannelOrderUniform in nonsemantic_clspvreflection
    {33,IR(535, 6),IR(54548, 40),IR(1, 0)}, // ImageArgumentInfoChannelDataTypeUniform in nonsemantic_clspvreflection
    {34,IR(593, 5),IR(54588, 27),IR(1, 0)}, // ArgumentStorageTexelBuffer in nonsemantic_clspvreflection
    {35,IR(593, 5),IR(54615, 27),IR(1, 0)}, // ArgumentUniformTexelBuffer in nonsemantic_clspvreflection
    {36,IR(33, 3),IR(54642, 32),IR(1, 0)}, // ConstantDataPointerPushConstant in nonsemantic_clspvreflection
    {37,IR(33, 3),IR(54674, 40),IR(1, 0)}, // ProgramScopeVariablePointerPushConstant in nonsemantic_clspvreflection
    {38,IR(375, 3),IR(54714, 11),IR(1, 0)}, // PrintfInfo in nonsemantic_clspvreflection
    {39,IR(33, 3),IR(54725, 26),IR(1, 0)}, // PrintfBufferStorageBuffer in nonsemantic_clspvreflection
    {40,IR(33, 3),IR(54751, 32),IR(1, 0)}, // PrintfBufferPointerPushConstant in nonsemantic_clspvreflection
    {41,IR(296, 4),IR(54783, 34),IR(1, 0)}, // NormalizedSamplerMaskPushConstant in nonsemantic_clspvreflection
    {42,IR(36, 2),IR(54817, 22),IR(1, 0)}, // WorkgroupVariableSize in nonsemantic_clspvreflection
    {0,IR(0, 0),IR(52241, 14),IR(1, 0)}, // DebugInfoNone in nonsemantic_shader_debuginfo_100
    {1,IR(296, 4),IR(52255, 21),IR(1, 0)}, // DebugCompilationUnit in nonsemantic_shader_debuginfo_100
    {2,IR(296, 4),IR(52328, 15),IR(1, 0)}, // DebugTypeBasic in nonsemantic_shader_debuginfo_100
    {3,IR(33, 3),IR(52377, 17),IR(1, 0)}, // DebugTypePointer in nonsemantic_shader_debuginfo_100
    {4,IR(36, 2),IR(52432, 19),IR(1, 0)}, // DebugTypeQualifier in nonsemantic_shader_debuginfo_100
    {5,IR(168, 2),IR(52451, 15),IR(1, 0)}, // DebugTypeArray in nonsemantic_shader_debuginfo_100
    {6,IR(36, 2),IR(52466, 16),IR(1, 0)}, // DebugTypeVector in nonsemantic_shader_debuginfo_100
    {7,IR(535, 6),IR(52482, 13),IR(1, 0)}, // DebugTypedef in nonsemantic_shader_debuginfo_100
    {8,IR(375, 3),IR(52495, 18),IR(1, 0)}, // DebugTypeFunction in nonsemantic_shader_debuginfo_100
    {9,IR(924, 9),IR(52513, 14),IR(1, 0)}, // DebugTypeEnum in nonsemantic_shader_debuginfo_100
    {10,IR(933, 10),IR(52565, 19),IR(1, 0)}, // DebugTypeComposite in nonsemantic_shader_debuginfo_100
    {11,IR(943, 9),IR(52584, 16),IR(1, 0)}, // DebugTypeMember in nonsemantic_shader_debuginfo_100
    {12,IR(296, 4),IR(52600, 21),IR(1, 0)}, // DebugTypeInheritance in nonsemantic_shader_debuginfo_100
    {13,IR(36, 2),IR(52621, 21),IR(1, 0)}, // DebugTypePtrToMember in nonsemantic_shader_debuginfo_100
    {14,IR(168, 2),IR(52642, 18),IR(1, 0)}, // DebugTypeTemplate in nonsemantic_shader_debuginfo_100
    {15,IR(535, 6),IR(52660, 27),IR(1, 0)}, // DebugTypeTemplateParameter in nonsemantic_shader_debuginfo_100
    {16,IR(675, 5),IR(52687, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in nonsemantic_shader_debuginfo_100
    {17,IR(952, 5),IR(52722, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in nonsemantic_shader_debuginfo_100
    {18,IR(957, 10),IR(52753, 20),IR(1, 0)}, // DebugGlobalVariable in nonsemantic_shader_debuginfo_100
    {19,IR(471, 8),IR(52773, 25),IR(1, 0)}, // DebugFunctionDeclaration in nonsemantic_shader_debuginfo_100
    {20,IR(957, 10),IR(52798, 14),IR(1, 0)}, // DebugFunction in nonsemantic_shader_debuginfo_100
    {21,IR(593, 5),IR(52812, 18),IR(1, 0)}, // DebugLexicalBlock in nonsemantic_shader_debuginfo_100
    {22,IR(33, 3),IR(52830, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in nonsemantic_shader_debuginfo_100
    {23,IR(901, 2),IR(52861, 11),IR(1, 0)}, // DebugScope in nonsemantic_shader_debuginfo_100
    {24,IR(0, 0),IR(52872, 13),IR(1, 0)}, // DebugNoScope in nonsemantic_shader_debuginfo_100
    {25,IR(967, 3),IR(52885, 15),IR(1, 0)}, // DebugInlinedAt in nonsemantic_shader_debuginfo_100
    {26,IR(970, 8),IR(52942, 19),IR(1, 0)}, // DebugLocalVariable in nonsemantic_shader_debuginfo_100
    {27,IR(36, 2),IR(52961, 21),IR(1, 0)}, // DebugInlinedVariable in nonsemantic_shader_debuginfo_100
    {28,IR(978, 4),IR(52982, 13),IR(1, 0)}, // DebugDeclare in nonsemantic_shader_debuginfo_100
    {29,IR(978, 4),IR(52995, 11),IR(1, 0)}, // DebugValue in nonsemantic_shader_debuginfo_100
    {30,IR(168, 2),IR(53039, 15),IR(1, 0)}, // DebugOperation in nonsemantic_shader_debuginfo_100
    {31,IR(747, 1),IR(53054, 16),IR(1, 0)}, // DebugExpression in nonsemantic_shader_debuginfo_100
    {32,IR(580, 4),IR(53070, 14),IR(1, 0)}, // DebugMacroDef in nonsemantic_shader_debuginfo_100
    {33,IR(33, 3),IR(53084, 16),IR(1, 0)}, // DebugMacroUndef in nonsemantic_shader_debuginfo_100
    {34,IR(516, 7),IR(54839, 20),IR(1, 0)}, // DebugImportedEntity in nonsemantic_shader_debuginfo_100
    {35,IR(901, 2),IR(54859, 12),IR(1, 0)}, // DebugSource in nonsemantic_shader_debuginfo_100
    {101,IR(36, 2),IR(54871, 24),IR(1, 0)}, // DebugFunctionDefinition in nonsemantic_shader_debuginfo_100
    {102,IR(10, 1),IR(54895, 21),IR(1, 0)}, // DebugSourceContinued in nonsemantic_shader_debuginfo_100
    {103,IR(675, 5),IR(54916, 10),IR(1, 0)}, // DebugLine in nonsemantic_shader_debuginfo_100
    {104,IR(0, 0),IR(54926, 12),IR(1, 0)}, // DebugNoLine in nonsemantic_shader_debuginfo_100
    {105,IR(36, 2),IR(54938, 21),IR(1, 0)}, // DebugBuildIdentifier in nonsemantic_shader_debuginfo_100
    {106,IR(10, 1),IR(54959, 17),IR(1, 0)}, // DebugStoragePath in nonsemantic_shader_debuginfo_100
    {107,IR(296, 4),IR(54976, 16),IR(1, 0)}, // DebugEntryPoint in nonsemantic_shader_debuginfo_100
    {108,IR(33, 3),IR(54992, 16),IR(1, 0)}, // DebugTypeMatrix in nonsemantic_shader_debuginfo_100
    {1,IR(765, 9),IR(55008, 14),IR(1, 0)}, // Configuration in nonsemantic_vkspreflection
    {2,IR(10, 1),IR(55022, 13),IR(1, 0)}, // StartCounter in nonsemantic_vkspreflection
    {3,IR(10, 1),IR(55035, 12),IR(1, 0)}, // StopCounter in nonsemantic_vkspreflection
    {4,IR(296, 4),IR(55047, 14),IR(1, 0)}, // PushConstants in nonsemantic_vkspreflection
    {5,IR(33, 3),IR(55061, 23),IR(1, 0)}, // SpecializationMapEntry in nonsemantic_vkspreflection
    {6,IR(982, 15),IR(55084, 20),IR(1, 0)}, // DescriptorSetBuffer in nonsemantic_vkspreflection
    {7,IR(997, 33),IR(55104, 19),IR(1, 0)}, // DescriptorSetImage in nonsemantic_vkspreflection
    {8,IR(1030, 19),IR(55123, 21),IR(1, 0)}, // DescriptorSetSampler in nonsemantic_vkspreflection
    {0,IR(0, 0),IR(52241, 14),IR(1, 0)}, // DebugInfoNone in opencl_debuginfo_100
    {1,IR(1049, 4),IR(52255, 21),IR(1, 0)}, // DebugCompilationUnit in opencl_debuginfo_100
    {2,IR(1053, 3),IR(52328, 15),IR(1, 0)}, // DebugTypeBasic in opencl_debuginfo_100
    {3,IR(1056, 3),IR(52377, 17),IR(1, 0)}, // DebugTypePointer in opencl_debuginfo_100
    {4,IR(1059, 2),IR(52432, 19),IR(1, 0)}, // DebugTypeQualifier in opencl_debuginfo_100
    {5,IR(168, 2),IR(52451, 15),IR(1, 0)}, // DebugTypeArray in opencl_debuginfo_100
    {6,IR(261, 2),IR(52466, 16),IR(1, 0)}, // DebugTypeVector in opencl_debuginfo_100
    {7,IR(819, 6),IR(52482, 13),IR(1, 0)}, // DebugTypedef in opencl_debuginfo_100
    {8,IR(1061, 3),IR(52495, 18),IR(1, 0)}, // DebugTypeFunction in opencl_debuginfo_100
    {9,IR(1064, 9),IR(52513, 14),IR(1, 0)}, // DebugTypeEnum in opencl_debuginfo_100
    {10,IR(1073, 10),IR(52565, 19),IR(1, 0)}, // DebugTypeComposite in opencl_debuginfo_100
    {11,IR(1083, 10),IR(52584, 16),IR(1, 0)}, // DebugTypeMember in opencl_debuginfo_100
    {12,IR(1093, 5),IR(52600, 21),IR(1, 0)}, // DebugTypeInheritance in opencl_debuginfo_100
    {13,IR(36, 2),IR(52621, 21),IR(1, 0)}, // DebugTypePtrToMember in opencl_debuginfo_100
    {14,IR(168, 2),IR(52642, 18),IR(1, 0)}, // DebugTypeTemplate in opencl_debuginfo_100
    {15,IR(858, 6),IR(52660, 27),IR(1, 0)}, // DebugTypeTemplateParameter in opencl_debuginfo_100
    {16,IR(864, 5),IR(52687, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in opencl_debuginfo_100
    {17,IR(869, 5),IR(52722, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in opencl_debuginfo_100
    {18,IR(1083, 10),IR(52753, 20),IR(1, 0)}, // DebugGlobalVariable in opencl_debuginfo_100
    {19,IR(1098, 8),IR(52773, 25),IR(1, 0)}, // DebugFunctionDeclaration in opencl_debuginfo_100
    {20,IR(1106, 11),IR(52798, 14),IR(1, 0)}, // DebugFunction in opencl_debuginfo_100
    {21,IR(893, 5),IR(52812, 18),IR(1, 0)}, // DebugLexicalBlock in opencl_debuginfo_100
    {22,IR(898, 3),IR(52830, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in opencl_debuginfo_100
    {23,IR(901, 2),IR(52861, 11),IR(1, 0)}, // DebugScope in opencl_debuginfo_100
    {24,IR(0, 0),IR(52872, 13),IR(1, 0)}, // DebugNoScope in opencl_debuginfo_100
    {25,IR(903, 3),IR(52885, 15),IR(1, 0)}, // DebugInlinedAt in opencl_debuginfo_100
    {26,IR(1117, 8),IR(52942, 19),IR(1, 0)}, // DebugLocalVariable in opencl_debuginfo_100
    {27,IR(36, 2),IR(52961, 21),IR(1, 0)}, // DebugInlinedVariable in opencl_debuginfo_100
    {28,IR(33, 3),IR(52982, 13),IR(1, 0)}, // DebugDeclare in opencl_debuginfo_100
    {29,IR(978, 4),IR(52995, 11),IR(1, 0)}, // DebugValue in opencl_debuginfo_100
    {30,IR(1125, 2),IR(53039, 15),IR(1, 0)}, // DebugOperation in opencl_debuginfo_100
    {31,IR(747, 1),IR(53054, 16),IR(1, 0)}, // DebugExpression in opencl_debuginfo_100
    {32,IR(915, 4),IR(53070, 14),IR(1, 0)}, // DebugMacroDef in opencl_debuginfo_100
    {33,IR(898, 3),IR(53084, 16),IR(1, 0)}, // DebugMacroUndef in opencl_debuginfo_100
    {34,IR(1127, 7),IR(54839, 20),IR(1, 0)}, // DebugImportedEntity in opencl_debuginfo_100
    {35,IR(901, 2),IR(54859, 12),IR(1, 0)}, // DebugSource in opencl_debuginfo_100
    {36,IR(1134, 8),IR(55444, 17),IR(1, 0)}, // DebugModuleINTEL in opencl_debuginfo_100
    {0,IR(10, 1),IR(55461, 5),IR(1, 0)}, // acos in opencl_std_100
    {1,IR(10, 1),IR(55466, 6),IR(1, 0)}, // acosh in opencl_std_100
    {2,IR(10, 1),IR(55472, 7),IR(1, 0)}, // acospi in opencl_std_100
    {3,IR(10, 1),IR(55479, 5),IR(1, 0)}, // asin in opencl_std_100
    {4,IR(10, 1),IR(55484, 6),IR(1, 0)}, // asinh in opencl_std_100
    {5,IR(10, 1),IR(55490, 7),IR(1, 0)}, // asinpi in opencl_std_100
    {6,IR(10, 1),IR(55497, 5),IR(1, 0)}, // atan in opencl_std_100
    {7,IR(36, 2),IR(55502, 6),IR(1, 0)}, // atan2 in opencl_std_100
    {8,IR(10, 1),IR(55508, 6),IR(1, 0)}, // atanh in opencl_std_100
    {9,IR(10, 1),IR(55514, 7),IR(1, 0)}, // atanpi in opencl_std_100
    {10,IR(36, 2),IR(55521, 8),IR(1, 0)}, // atan2pi in opencl_std_100
    {11,IR(10, 1),IR(55529, 5),IR(1, 0)}, // cbrt in opencl_std_100
    {12,IR(10, 1),IR(55534, 5),IR(1, 0)}, // ceil in opencl_std_100
    {13,IR(36, 2),IR(55539, 9),IR(1, 0)}, // copysign in opencl_std_100
    {14,IR(10, 1),IR(55548, 4),IR(1, 0)}, // cos in opencl_std_100
    {15,IR(10, 1),IR(55552, 5),IR(1, 0)}, // cosh in opencl_std_100
    {16,IR(10, 1),IR(55557, 6),IR(1, 0)}, // cospi in opencl_std_100
    {17,IR(10, 1),IR(55563, 5),IR(1, 0)}, // erfc in opencl_std_100
    {18,IR(10, 1),IR(55568, 4),IR(1, 0)}, // erf in opencl_std_100
    {19,IR(10, 1),IR(55572, 4),IR(1, 0)}, // exp in opencl_std_100
    {20,IR(10, 1),IR(55576, 5),IR(1, 0)}, // exp2 in opencl_std_100
    {21,IR(10, 1),IR(55581, 6),IR(1, 0)}, // exp10 in opencl_std_100
    {22,IR(10, 1),IR(55587, 6),IR(1, 0)}, // expm1 in opencl_std_100
    {23,IR(10, 1),IR(55593, 5),IR(1, 0)}, // fabs in opencl_std_100
    {24,IR(36, 2),IR(55598, 5),IR(1, 0)}, // fdim in opencl_std_100
    {25,IR(10, 1),IR(55603, 6),IR(1, 0)}, // floor in opencl_std_100
    {26,IR(33, 3),IR(55609, 4),IR(1, 0)}, // fma in opencl_std_100
    {27,IR(36, 2),IR(55613, 5),IR(1, 0)}, // fmax in opencl_std_100
    {28,IR(36, 2),IR(55618, 5),IR(1, 0)}, // fmin in opencl_std_100
    {29,IR(36, 2),IR(55623, 5),IR(1, 0)}, // fmod in opencl_std_100
    {30,IR(36, 2),IR(55628, 6),IR(1, 0)}, // fract in opencl_std_100
    {31,IR(36, 2),IR(55634, 6),IR(1, 0)}, // frexp in opencl_std_100
    {32,IR(36, 2),IR(55640, 6),IR(1, 0)}, // hypot in opencl_std_100
    {33,IR(10, 1),IR(55646, 6),IR(1, 0)}, // ilogb in opencl_std_100
    {34,IR(36, 2),IR(55652, 6),IR(1, 0)}, // ldexp in opencl_std_100
    {35,IR(10, 1),IR(55658, 7),IR(1, 0)}, // lgamma in opencl_std_100
    {36,IR(36, 2),IR(55665, 9),IR(1, 0)}, // lgamma_r in opencl_std_100
    {37,IR(10, 1),IR(55674, 4),IR(1, 0)}, // log in opencl_std_100
    {38,IR(10, 1),IR(55678, 5),IR(1, 0)}, // log2 in opencl_std_100
    {39,IR(10, 1),IR(55683, 6),IR(1, 0)}, // log10 in opencl_std_100
    {40,IR(10, 1),IR(55689, 6),IR(1, 0)}, // log1p in opencl_std_100
    {41,IR(10, 1),IR(55695, 5),IR(1, 0)}, // logb in opencl_std_100
    {42,IR(33, 3),IR(55700, 4),IR(1, 0)}, // mad in opencl_std_100
    {43,IR(36, 2),IR(55704, 7),IR(1, 0)}, // maxmag in opencl_std_100
    {44,IR(36, 2),IR(55711, 7),IR(1, 0)}, // minmag in opencl_std_100
    {45,IR(36, 2),IR(55718, 5),IR(1, 0)}, // modf in opencl_std_100
    {46,IR(10, 1),IR(55723, 4),IR(1, 0)}, // nan in opencl_std_100
    {47,IR(36, 2),IR(55727, 10),IR(1, 0)}, // nextafter in opencl_std_100
    {48,IR(36, 2),IR(55737, 4),IR(1, 0)}, // pow in opencl_std_100
    {49,IR(36, 2),IR(55741, 5),IR(1, 0)}, // pown in opencl_std_100
    {50,IR(36, 2),IR(55746, 5),IR(1, 0)}, // powr in opencl_std_100
    {51,IR(36, 2),IR(55751, 10),IR(1, 0)}, // remainder in opencl_std_100
    {52,IR(33, 3),IR(55761, 7),IR(1, 0)}, // remquo in opencl_std_100
    {53,IR(10, 1),IR(55768, 5),IR(1, 0)}, // rint in opencl_std_100
    {54,IR(36, 2),IR(55773, 6),IR(1, 0)}, // rootn in opencl_std_100
    {55,IR(10, 1),IR(55779, 6),IR(1, 0)}, // round in opencl_std_100
    {56,IR(10, 1),IR(55785, 6),IR(1, 0)}, // rsqrt in opencl_std_100
    {57,IR(10, 1),IR(55791, 4),IR(1, 0)}, // sin in opencl_std_100
    {58,IR(36, 2),IR(55795, 7),IR(1, 0)}, // sincos in opencl_std_100
    {59,IR(10, 1),IR(55802, 5),IR(1, 0)}, // sinh in opencl_std_100
    {60,IR(10, 1),IR(55807, 6),IR(1, 0)}, // sinpi in opencl_std_100
    {61,IR(10, 1),IR(55813, 5),IR(1, 0)}, // sqrt in opencl_std_100
    {62,IR(10, 1),IR(55818, 4),IR(1, 0)}, // tan in opencl_std_100
    {63,IR(10, 1),IR(55822, 5),IR(1, 0)}, // tanh in opencl_std_100
    {64,IR(10, 1),IR(55827, 6),IR(1, 0)}, // tanpi in opencl_std_100
    {65,IR(10, 1),IR(55833, 7),IR(1, 0)}, // tgamma in opencl_std_100
    {66,IR(10, 1),IR(55840, 6),IR(1, 0)}, // trunc in opencl_std_100
    {67,IR(10, 1),IR(55846, 9),IR(1, 0)}, // half_cos in opencl_std_100
    {68,IR(36, 2),IR(55855, 12),IR(1, 0)}, // half_divide in opencl_std_100
    {69,IR(10, 1),IR(55867, 9),IR(1, 0)}, // half_exp in opencl_std_100
    {70,IR(10, 1),IR(55876, 10),IR(1, 0)}, // half_exp2 in opencl_std_100
    {71,IR(10, 1),IR(55886, 11),IR(1, 0)}, // half_exp10 in opencl_std_100
    {72,IR(10, 1),IR(55897, 9),IR(1, 0)}, // half_log in opencl_std_100
    {73,IR(10, 1),IR(55906, 10),IR(1, 0)}, // half_log2 in opencl_std_100
    {74,IR(10, 1),IR(55916, 11),IR(1, 0)}, // half_log10 in opencl_std_100
    {75,IR(36, 2),IR(55927, 10),IR(1, 0)}, // half_powr in opencl_std_100
    {76,IR(10, 1),IR(55937, 11),IR(1, 0)}, // half_recip in opencl_std_100
    {77,IR(10, 1),IR(55948, 11),IR(1, 0)}, // half_rsqrt in opencl_std_100
    {78,IR(10, 1),IR(55959, 9),IR(1, 0)}, // half_sin in opencl_std_100
    {79,IR(10, 1),IR(55968, 10),IR(1, 0)}, // half_sqrt in opencl_std_100
    {80,IR(10, 1),IR(55978, 9),IR(1, 0)}, // half_tan in opencl_std_100
    {81,IR(10, 1),IR(55987, 11),IR(1, 0)}, // native_cos in opencl_std_100
    {82,IR(36, 2),IR(55998, 14),IR(1, 0)}, // native_divide in opencl_std_100
    {83,IR(10, 1),IR(56012, 11),IR(1, 0)}, // native_exp in opencl_std_100
    {84,IR(10, 1),IR(56023, 12),IR(1, 0)}, // native_exp2 in opencl_std_100
    {85,IR(10, 1),IR(56035, 13),IR(1, 0)}, // native_exp10 in opencl_std_100
    {86,IR(10, 1),IR(56048, 11),IR(1, 0)}, // native_log in opencl_std_100
    {87,IR(10, 1),IR(56059, 12),IR(1, 0)}, // native_log2 in opencl_std_100
    {88,IR(10, 1),IR(56071, 13),IR(1, 0)}, // native_log10 in opencl_std_100
    {89,IR(36, 2),IR(56084, 12),IR(1, 0)}, // native_powr in opencl_std_100
    {90,IR(10, 1),IR(56096, 13),IR(1, 0)}, // native_recip in opencl_std_100
    {91,IR(10, 1),IR(56109, 13),IR(1, 0)}, // native_rsqrt in opencl_std_100
    {92,IR(10, 1),IR(56122, 11),IR(1, 0)}, // native_sin in opencl_std_100
    {93,IR(10, 1),IR(56133, 12),IR(1, 0)}, // native_sqrt in opencl_std_100
    {94,IR(10, 1),IR(56145, 11),IR(1, 0)}, // native_tan in opencl_std_100
    {95,IR(33, 3),IR(56156, 7),IR(1, 0)}, // fclamp in opencl_std_100
    {96,IR(10, 1),IR(56163, 8),IR(1, 0)}, // degrees in opencl_std_100
    {97,IR(36, 2),IR(56171, 12),IR(1, 0)}, // fmax_common in opencl_std_100
    {98,IR(36, 2),IR(56183, 12),IR(1, 0)}, // fmin_common in opencl_std_100
    {99,IR(33, 3),IR(56195, 4),IR(1, 0)}, // mix in opencl_std_100
    {100,IR(10, 1),IR(56199, 8),IR(1, 0)}, // radians in opencl_std_100
    {101,IR(36, 2),IR(56207, 5),IR(1, 0)}, // step in opencl_std_100
    {102,IR(33, 3),IR(56212, 11),IR(1, 0)}, // smoothstep in opencl_std_100
    {103,IR(10, 1),IR(56223, 5),IR(1, 0)}, // sign in opencl_std_100
    {104,IR(36, 2),IR(56228, 6),IR(1, 0)}, // cross in opencl_std_100
    {105,IR(36, 2),IR(56234, 9),IR(1, 0)}, // distance in opencl_std_100
    {106,IR(10, 1),IR(56243, 7),IR(1, 0)}, // length in opencl_std_100
    {107,IR(10, 1),IR(56250, 10),IR(1, 0)}, // normalize in opencl_std_100
    {108,IR(36, 2),IR(56260, 14),IR(1, 0)}, // fast_distance in opencl_std_100
    {109,IR(10, 1),IR(56274, 12),IR(1, 0)}, // fast_length in opencl_std_100
    {110,IR(10, 1),IR(56286, 15),IR(1, 0)}, // fast_normalize in opencl_std_100
    {141,IR(10, 1),IR(56301, 6),IR(1, 0)}, // s_abs in opencl_std_100
    {142,IR(36, 2),IR(56307, 11),IR(1, 0)}, // s_abs_diff in opencl_std_100
    {143,IR(36, 2),IR(56318, 10),IR(1, 0)}, // s_add_sat in opencl_std_100
    {144,IR(36, 2),IR(56328, 10),IR(1, 0)}, // u_add_sat in opencl_std_100
    {145,IR(36, 2),IR(56338, 7),IR(1, 0)}, // s_hadd in opencl_std_100
    {146,IR(36, 2),IR(56345, 7),IR(1, 0)}, // u_hadd in opencl_std_100
    {147,IR(36, 2),IR(56352, 8),IR(1, 0)}, // s_rhadd in opencl_std_100
    {148,IR(36, 2),IR(56360, 8),IR(1, 0)}, // u_rhadd in opencl_std_100
    {149,IR(33, 3),IR(56368, 8),IR(1, 0)}, // s_clamp in opencl_std_100
    {150,IR(33, 3),IR(56376, 8),IR(1, 0)}, // u_clamp in opencl_std_100
    {151,IR(10, 1),IR(56384, 4),IR(1, 0)}, // clz in opencl_std_100
    {152,IR(10, 1),IR(56388, 4),IR(1, 0)}, // ctz in opencl_std_100
    {153,IR(33, 3),IR(56392, 9),IR(1, 0)}, // s_mad_hi in opencl_std_100
    {154,IR(33, 3),IR(56401, 10),IR(1, 0)}, // u_mad_sat in opencl_std_100
    {155,IR(33, 3),IR(56411, 10),IR(1, 0)}, // s_mad_sat in opencl_std_100
    {156,IR(36, 2),IR(56421, 6),IR(1, 0)}, // s_max in opencl_std_100
    {157,IR(36, 2),IR(56427, 6),IR(1, 0)}, // u_max in opencl_std_100
    {158,IR(36, 2),IR(56433, 6),IR(1, 0)}, // s_min in opencl_std_100
    {159,IR(36, 2),IR(56439, 6),IR(1, 0)}, // u_min in opencl_std_100
    {160,IR(36, 2),IR(56445, 9),IR(1, 0)}, // s_mul_hi in opencl_std_100
    {161,IR(36, 2),IR(56454, 7),IR(1, 0)}, // rotate in opencl_std_100
    {162,IR(36, 2),IR(56461, 10),IR(1, 0)}, // s_sub_sat in opencl_std_100
    {163,IR(36, 2),IR(56471, 10),IR(1, 0)}, // u_sub_sat in opencl_std_100
    {164,IR(36, 2),IR(56481, 11),IR(1, 0)}, // u_upsample in opencl_std_100
    {165,IR(36, 2),IR(56492, 11),IR(1, 0)}, // s_upsample in opencl_std_100
    {166,IR(10, 1),IR(56503, 9),IR(1, 0)}, // popcount in opencl_std_100
    {167,IR(33, 3),IR(56512, 8),IR(1, 0)}, // s_mad24 in opencl_std_100
    {168,IR(33, 3),IR(56520, 8),IR(1, 0)}, // u_mad24 in opencl_std_100
    {169,IR(36, 2),IR(56528, 8),IR(1, 0)}, // s_mul24 in opencl_std_100
    {170,IR(36, 2),IR(56536, 8),IR(1, 0)}, // u_mul24 in opencl_std_100
    {171,IR(1142, 3),IR(56544, 7),IR(1, 0)}, // vloadn in opencl_std_100
    {172,IR(33, 3),IR(56551, 8),IR(1, 0)}, // vstoren in opencl_std_100
    {173,IR(36, 2),IR(56559, 11),IR(1, 0)}, // vload_half in opencl_std_100
    {174,IR(1142, 3),IR(56570, 12),IR(1, 0)}, // vload_halfn in opencl_std_100
    {175,IR(33, 3),IR(56582, 12),IR(1, 0)}, // vstore_half in opencl_std_100
    {176,IR(1145, 4),IR(56594, 14),IR(1, 0)}, // vstore_half_r in opencl_std_100
    {177,IR(33, 3),IR(56608, 13),IR(1, 0)}, // vstore_halfn in opencl_std_100
    {178,IR(1145, 4),IR(56621, 15),IR(1, 0)}, // vstore_halfn_r in opencl_std_100
    {179,IR(1142, 3),IR(56636, 13),IR(1, 0)}, // vloada_halfn in opencl_std_100
    {180,IR(33, 3),IR(56649, 14),IR(1, 0)}, // vstorea_halfn in opencl_std_100
    {181,IR(1145, 4),IR(56663, 16),IR(1, 0)}, // vstorea_halfn_r in opencl_std_100
    {182,IR(36, 2),IR(56679, 8),IR(1, 0)}, // shuffle in opencl_std_100
    {183,IR(33, 3),IR(56687, 9),IR(1, 0)}, // shuffle2 in opencl_std_100
    {184,IR(168, 2),IR(56696, 7),IR(1, 0)}, // printf in opencl_std_100
    {185,IR(36, 2),IR(56703, 9),IR(1, 0)}, // prefetch in opencl_std_100
    {186,IR(33, 3),IR(56712, 10),IR(1, 0)}, // bitselect in opencl_std_100
    {187,IR(33, 3),IR(56722, 7),IR(1, 0)}, // select in opencl_std_100
    {201,IR(10, 1),IR(56729, 6),IR(1, 0)}, // u_abs in opencl_std_100
    {202,IR(36, 2),IR(56735, 11),IR(1, 0)}, // u_abs_diff in opencl_std_100
    {203,IR(36, 2),IR(56746, 9),IR(1, 0)}, // u_mul_hi in opencl_std_100
    {204,IR(33, 3),IR(56755, 9),IR(1, 0)}, // u_mad_hi in opencl_std_100
    {1,IR(10, 1),IR(56764, 17),IR(1, 0)}, // CubeFaceIndexAMD in spv_amd_gcn_shader
    {2,IR(10, 1),IR(56781, 17),IR(1, 0)}, // CubeFaceCoordAMD in spv_amd_gcn_shader
    {3,IR(0, 0),IR(56798, 8),IR(1, 0)}, // TimeAMD in spv_amd_gcn_shader
    {1,IR(36, 2),IR(56806, 22),IR(1, 0)}, // SwizzleInvocationsAMD in spv_amd_shader_ballot
    {2,IR(36, 2),IR(56828, 28),IR(1, 0)}, // SwizzleInvocationsMaskedAMD in spv_amd_shader_ballot
    {3,IR(33, 3),IR(56856, 19),IR(1, 0)}, // WriteInvocationAMD in spv_amd_shader_ballot
    {4,IR(10, 1),IR(56875, 9),IR(1, 0)}, // MbcntAMD in spv_amd_shader_ballot
    {1,IR(36, 2),IR(56884, 23),IR(1, 0)}, // InterpolateAtVertexAMD in spv_amd_shader_explicit_vertex_parameter
    {1,IR(33, 3),IR(56907, 9),IR(1, 0)}, // FMin3AMD in spv_amd_shader_trinary_minmax
    {2,IR(33, 3),IR(56916, 9),IR(1, 0)}, // UMin3AMD in spv_amd_shader_trinary_minmax
    {3,IR(33, 3),IR(56925, 9),IR(1, 0)}, // SMin3AMD in spv_amd_shader_trinary_minmax
    {4,IR(33, 3),IR(56934, 9),IR(1, 0)}, // FMax3AMD in spv_amd_shader_trinary_minmax
    {5,IR(33, 3),IR(56943, 9),IR(1, 0)}, // UMax3AMD in spv_amd_shader_trinary_minmax
    {6,IR(33, 3),IR(56952, 9),IR(1, 0)}, // SMax3AMD in spv_amd_shader_trinary_minmax
    {7,IR(33, 3),IR(56961, 9),IR(1, 0)}, // FMid3AMD in spv_amd_shader_trinary_minmax
    {8,IR(33, 3),IR(56970, 9),IR(1, 0)}, // UMid3AMD in spv_amd_shader_trinary_minmax
    {9,IR(33, 3),IR(56979, 9),IR(1, 0)}, // SMid3AMD in spv_amd_shader_trinary_minmax
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
    {IR(52255, 21), 1}, // DebugCompilationUnit in debuginfo
    {IR(52982, 13), 28}, // DebugDeclare in debuginfo
    {IR(53054, 16), 31}, // DebugExpression in debuginfo
    {IR(52798, 14), 20}, // DebugFunction in debuginfo
    {IR(52773, 25), 19}, // DebugFunctionDeclaration in debuginfo
    {IR(52753, 20), 18}, // DebugGlobalVariable in debuginfo
    {IR(52241, 14), 0}, // DebugInfoNone in debuginfo
    {IR(52885, 15), 25}, // DebugInlinedAt in debuginfo
    {IR(52961, 21), 27}, // DebugInlinedVariable in debuginfo
    {IR(52812, 18), 21}, // DebugLexicalBlock in debuginfo
    {IR(52830, 31), 22}, // DebugLexicalBlockDiscriminator in debuginfo
    {IR(52942, 19), 26}, // DebugLocalVariable in debuginfo
    {IR(53070, 14), 32}, // DebugMacroDef in debuginfo
    {IR(53084, 16), 33}, // DebugMacroUndef in debuginfo
    {IR(52872, 13), 24}, // DebugNoScope in debuginfo
    {IR(53039, 15), 30}, // DebugOperation in debuginfo
    {IR(52861, 11), 23}, // DebugScope in debuginfo
    {IR(52451, 15), 5}, // DebugTypeArray in debuginfo
    {IR(52328, 15), 2}, // DebugTypeBasic in debuginfo
    {IR(52565, 19), 10}, // DebugTypeComposite in debuginfo
    {IR(52513, 14), 9}, // DebugTypeEnum in debuginfo
    {IR(52495, 18), 8}, // DebugTypeFunction in debuginfo
    {IR(52600, 21), 12}, // DebugTypeInheritance in debuginfo
    {IR(52584, 16), 11}, // DebugTypeMember in debuginfo
    {IR(52377, 17), 3}, // DebugTypePointer in debuginfo
    {IR(52621, 21), 13}, // DebugTypePtrToMember in debuginfo
    {IR(52432, 19), 4}, // DebugTypeQualifier in debuginfo
    {IR(52642, 18), 14}, // DebugTypeTemplate in debuginfo
    {IR(52660, 27), 15}, // DebugTypeTemplateParameter in debuginfo
    {IR(52722, 31), 17}, // DebugTypeTemplateParameterPack in debuginfo
    {IR(52687, 35), 16}, // DebugTypeTemplateTemplateParameter in debuginfo
    {IR(52466, 16), 6}, // DebugTypeVector in debuginfo
    {IR(52482, 13), 7}, // DebugTypedef in debuginfo
    {IR(52995, 11), 29}, // DebugValue in debuginfo
    {IR(53194, 5), 50}, // Acos in glsl_std_450
    {IR(53225, 6), 56}, // Acosh in glsl_std_450
    {IR(53189, 5), 49}, // Asin in glsl_std_450
    {IR(53219, 6), 55}, // Asinh in glsl_std_450
    {IR(53199, 5), 51}, // Atan in glsl_std_450
    {IR(53237, 6), 58}, // Atan2 in glsl_std_450
    {IR(53231, 6), 57}, // Atanh in glsl_std_450
    {IR(53150, 5), 42}, // Ceil in glsl_std_450
    {IR(53181, 4), 47}, // Cos in glsl_std_450
    {IR(53209, 5), 53}, // Cosh in glsl_std_450
    {IR(53621, 6), 101}, // Cross in glsl_std_450
    {IR(53169, 8), 45}, // Degrees in glsl_std_450
    {IR(53282, 12), 66}, // Determinant in glsl_std_450
    {IR(53612, 9), 100}, // Distance in glsl_std_450
    {IR(53247, 4), 60}, // Exp in glsl_std_450
    {IR(53255, 5), 62}, // Exp2 in glsl_std_450
    {IR(53122, 5), 37}, // FAbs in glsl_std_450
    {IR(53354, 7), 76}, // FClamp in glsl_std_450
    {IR(53339, 5), 73}, // FMax in glsl_std_450
    {IR(53324, 5), 70}, // FMin in glsl_std_450
    {IR(53375, 5), 79}, // FMix in glsl_std_450
    {IR(53132, 6), 39}, // FSign in glsl_std_450
    {IR(53637, 12), 103}, // FaceForward in glsl_std_450
    {IR(53665, 9), 106}, // FindILsb in glsl_std_450
    {IR(53674, 9), 107}, // FindSMsb in glsl_std_450
    {IR(53683, 9), 108}, // FindUMsb in glsl_std_450
    {IR(53144, 6), 41}, // Floor in glsl_std_450
    {IR(53401, 4), 83}, // Fma in glsl_std_450
    {IR(53155, 6), 43}, // Fract in glsl_std_450
    {IR(53405, 6), 84}, // Frexp in glsl_std_450
    {IR(53411, 12), 85}, // FrexpStruct in glsl_std_450
    {IR(53380, 5), 80}, // IMix in glsl_std_450
    {IR(53692, 22), 109}, // InterpolateAtCentroid in glsl_std_450
    {IR(53734, 20), 111}, // InterpolateAtOffset in glsl_std_450
    {IR(53714, 20), 110}, // InterpolateAtSample in glsl_std_450
    {IR(53270, 12), 65}, // InverseSqrt in glsl_std_450
    {IR(53423, 6), 86}, // Ldexp in glsl_std_450
    {IR(53605, 7), 99}, // Length in glsl_std_450
    {IR(53251, 4), 61}, // Log in glsl_std_450
    {IR(53260, 5), 63}, // Log2 in glsl_std_450
    {IR(53294, 14), 67}, // MatrixInverse in glsl_std_450
    {IR(53308, 5), 68}, // Modf in glsl_std_450
    {IR(53313, 11), 69}, // ModfStruct in glsl_std_450
    {IR(53764, 7), 114}, // NClamp in glsl_std_450
    {IR(53759, 5), 113}, // NMax in glsl_std_450
    {IR(53754, 5), 112}, // NMin in glsl_std_450
    {IR(53627, 10), 102}, // Normalize in glsl_std_450
    {IR(53496, 15), 92}, // PackDouble2x32 in glsl_std_450
    {IR(53483, 13), 91}, // PackHalf2x16 in glsl_std_450
    {IR(53455, 14), 89}, // PackSnorm2x16 in glsl_std_450
    {IR(53429, 13), 87}, // PackSnorm4x8 in glsl_std_450
    {IR(53469, 14), 90}, // PackUnorm2x16 in glsl_std_450
    {IR(53442, 13), 88}, // PackUnorm4x8 in glsl_std_450
    {IR(53243, 4), 59}, // Pow in glsl_std_450
    {IR(53161, 8), 44}, // Radians in glsl_std_450
    {IR(53649, 8), 104}, // Reflect in glsl_std_450
    {IR(53657, 8), 105}, // Refract in glsl_std_450
    {IR(53100, 6), 34}, // Round in glsl_std_450
    {IR(53106, 10), 35}, // RoundEven in glsl_std_450
    {IR(53127, 5), 38}, // SAbs in glsl_std_450
    {IR(53368, 7), 78}, // SClamp in glsl_std_450
    {IR(53349, 5), 75}, // SMax in glsl_std_450
    {IR(53334, 5), 72}, // SMin in glsl_std_450
    {IR(53138, 6), 40}, // SSign in glsl_std_450
    {IR(53177, 4), 46}, // Sin in glsl_std_450
    {IR(53204, 5), 52}, // Sinh in glsl_std_450
    {IR(53390, 11), 82}, // SmoothStep in glsl_std_450
    {IR(53265, 5), 64}, // Sqrt in glsl_std_450
    {IR(53385, 5), 81}, // Step in glsl_std_450
    {IR(53185, 4), 48}, // Tan in glsl_std_450
    {IR(53214, 5), 54}, // Tanh in glsl_std_450
    {IR(53116, 6), 36}, // Trunc in glsl_std_450
    {IR(53361, 7), 77}, // UClamp in glsl_std_450
    {IR(53344, 5), 74}, // UMax in glsl_std_450
    {IR(53329, 5), 71}, // UMin in glsl_std_450
    {IR(53588, 17), 98}, // UnpackDouble2x32 in glsl_std_450
    {IR(53543, 15), 95}, // UnpackHalf2x16 in glsl_std_450
    {IR(53511, 16), 93}, // UnpackSnorm2x16 in glsl_std_450
    {IR(53558, 15), 96}, // UnpackSnorm4x8 in glsl_std_450
    {IR(53527, 16), 94}, // UnpackUnorm2x16 in glsl_std_450
    {IR(53573, 15), 97}, // UnpackUnorm4x8 in glsl_std_450
    {IR(53771, 13), 116}, // ArgumentInfo in nonsemantic_clspvreflection
    {IR(53866, 24), 121}, // ArgumentPodPushConstant in nonsemantic_clspvreflection
    {IR(53822, 25), 119}, // ArgumentPodStorageBuffer in nonsemantic_clspvreflection
    {IR(53847, 19), 120}, // ArgumentPodUniform in nonsemantic_clspvreflection
    {IR(54300, 28), 140}, // ArgumentPointerPushConstant in nonsemantic_clspvreflection
    {IR(54328, 23), 141}, // ArgumentPointerUniform in nonsemantic_clspvreflection
    {IR(53890, 21), 122}, // ArgumentSampledImage in nonsemantic_clspvreflection
    {IR(53932, 16), 124}, // ArgumentSampler in nonsemantic_clspvreflection
    {IR(53784, 22), 117}, // ArgumentStorageBuffer in nonsemantic_clspvreflection
    {IR(53911, 21), 123}, // ArgumentStorageImage in nonsemantic_clspvreflection
    {IR(54588, 27), 148}, // ArgumentStorageTexelBuffer in nonsemantic_clspvreflection
    {IR(53806, 16), 118}, // ArgumentUniform in nonsemantic_clspvreflection
    {IR(54615, 27), 149}, // ArgumentUniformTexelBuffer in nonsemantic_clspvreflection
    {IR(53948, 18), 125}, // ArgumentWorkgroup in nonsemantic_clspvreflection
    {IR(54642, 32), 150}, // ConstantDataPointerPushConstant in nonsemantic_clspvreflection
    {IR(54196, 26), 135}, // ConstantDataStorageBuffer in nonsemantic_clspvreflection
    {IR(54222, 20), 136}, // ConstantDataUniform in nonsemantic_clspvreflection
    {IR(54466, 45), 145}, // ImageArgumentInfoChannelDataTypePushConstant in nonsemantic_clspvreflection
    {IR(54548, 40), 147}, // ImageArgumentInfoChannelDataTypeUniform in nonsemantic_clspvreflection
    {IR(54424, 42), 144}, // ImageArgumentInfoChannelOrderPushConstant in nonsemantic_clspvreflection
    {IR(54511, 37), 146}, // ImageArgumentInfoChannelOrderUniform in nonsemantic_clspvreflection
    {IR(5915, 7), 115}, // Kernel in nonsemantic_clspvreflection
    {IR(9389, 15), 137}, // LiteralSampler in nonsemantic_clspvreflection
    {IR(54783, 34), 155}, // NormalizedSamplerMaskPushConstant in nonsemantic_clspvreflection
    {IR(54751, 32), 154}, // PrintfBufferPointerPushConstant in nonsemantic_clspvreflection
    {IR(54725, 26), 153}, // PrintfBufferStorageBuffer in nonsemantic_clspvreflection
    {IR(54714, 11), 152}, // PrintfInfo in nonsemantic_clspvreflection
    {IR(54674, 40), 151}, // ProgramScopeVariablePointerPushConstant in nonsemantic_clspvreflection
    {IR(54386, 38), 143}, // ProgramScopeVariablePointerRelocation in nonsemantic_clspvreflection
    {IR(54351, 35), 142}, // ProgramScopeVariablesStorageBuffer in nonsemantic_clspvreflection
    {IR(54242, 30), 138}, // PropertyRequiredWorkgroupSize in nonsemantic_clspvreflection
    {IR(54062, 30), 130}, // PushConstantEnqueuedLocalSize in nonsemantic_clspvreflection
    {IR(54037, 25), 129}, // PushConstantGlobalOffset in nonsemantic_clspvreflection
    {IR(54092, 23), 131}, // PushConstantGlobalSize in nonsemantic_clspvreflection
    {IR(54140, 26), 133}, // PushConstantNumWorkgroups in nonsemantic_clspvreflection
    {IR(54166, 30), 134}, // PushConstantRegionGroupOffset in nonsemantic_clspvreflection
    {IR(54115, 25), 132}, // PushConstantRegionOffset in nonsemantic_clspvreflection
    {IR(53992, 25), 127}, // SpecConstantGlobalOffset in nonsemantic_clspvreflection
    {IR(54272, 28), 139}, // SpecConstantSubgroupMaxSize in nonsemantic_clspvreflection
    {IR(54017, 20), 128}, // SpecConstantWorkDim in nonsemantic_clspvreflection
    {IR(53966, 26), 126}, // SpecConstantWorkgroupSize in nonsemantic_clspvreflection
    {IR(54817, 22), 156}, // WorkgroupVariableSize in nonsemantic_clspvreflection
    {IR(54938, 21), 197}, // DebugBuildIdentifier in nonsemantic_shader_debuginfo_100
    {IR(52255, 21), 158}, // DebugCompilationUnit in nonsemantic_shader_debuginfo_100
    {IR(52982, 13), 185}, // DebugDeclare in nonsemantic_shader_debuginfo_100
    {IR(54976, 16), 199}, // DebugEntryPoint in nonsemantic_shader_debuginfo_100
    {IR(53054, 16), 188}, // DebugExpression in nonsemantic_shader_debuginfo_100
    {IR(52798, 14), 177}, // DebugFunction in nonsemantic_shader_debuginfo_100
    {IR(52773, 25), 176}, // DebugFunctionDeclaration in nonsemantic_shader_debuginfo_100
    {IR(54871, 24), 193}, // DebugFunctionDefinition in nonsemantic_shader_debuginfo_100
    {IR(52753, 20), 175}, // DebugGlobalVariable in nonsemantic_shader_debuginfo_100
    {IR(54839, 20), 191}, // DebugImportedEntity in nonsemantic_shader_debuginfo_100
    {IR(52241, 14), 157}, // DebugInfoNone in nonsemantic_shader_debuginfo_100
    {IR(52885, 15), 182}, // DebugInlinedAt in nonsemantic_shader_debuginfo_100
    {IR(52961, 21), 184}, // DebugInlinedVariable in nonsemantic_shader_debuginfo_100
    {IR(52812, 18), 178}, // DebugLexicalBlock in nonsemantic_shader_debuginfo_100
    {IR(52830, 31), 179}, // DebugLexicalBlockDiscriminator in nonsemantic_shader_debuginfo_100
    {IR(54916, 10), 195}, // DebugLine in nonsemantic_shader_debuginfo_100
    {IR(52942, 19), 183}, // DebugLocalVariable in nonsemantic_shader_debuginfo_100
    {IR(53070, 14), 189}, // DebugMacroDef in nonsemantic_shader_debuginfo_100
    {IR(53084, 16), 190}, // DebugMacroUndef in nonsemantic_shader_debuginfo_100
    {IR(54926, 12), 196}, // DebugNoLine in nonsemantic_shader_debuginfo_100
    {IR(52872, 13), 181}, // DebugNoScope in nonsemantic_shader_debuginfo_100
    {IR(53039, 15), 187}, // DebugOperation in nonsemantic_shader_debuginfo_100
    {IR(52861, 11), 180}, // DebugScope in nonsemantic_shader_debuginfo_100
    {IR(54859, 12), 192}, // DebugSource in nonsemantic_shader_debuginfo_100
    {IR(54895, 21), 194}, // DebugSourceContinued in nonsemantic_shader_debuginfo_100
    {IR(54959, 17), 198}, // DebugStoragePath in nonsemantic_shader_debuginfo_100
    {IR(52451, 15), 162}, // DebugTypeArray in nonsemantic_shader_debuginfo_100
    {IR(52328, 15), 159}, // DebugTypeBasic in nonsemantic_shader_debuginfo_100
    {IR(52565, 19), 167}, // DebugTypeComposite in nonsemantic_shader_debuginfo_100
    {IR(52513, 14), 166}, // DebugTypeEnum in nonsemantic_shader_debuginfo_100
    {IR(52495, 18), 165}, // DebugTypeFunction in nonsemantic_shader_debuginfo_100
    {IR(52600, 21), 169}, // DebugTypeInheritance in nonsemantic_shader_debuginfo_100
    {IR(54992, 16), 200}, // DebugTypeMatrix in nonsemantic_shader_debuginfo_100
    {IR(52584, 16), 168}, // DebugTypeMember in nonsemantic_shader_debuginfo_100
    {IR(52377, 17), 160}, // DebugTypePointer in nonsemantic_shader_debuginfo_100
    {IR(52621, 21), 170}, // DebugTypePtrToMember in nonsemantic_shader_debuginfo_100
    {IR(52432, 19), 161}, // DebugTypeQualifier in nonsemantic_shader_debuginfo_100
    {IR(52642, 18), 171}, // DebugTypeTemplate in nonsemantic_shader_debuginfo_100
    {IR(52660, 27), 172}, // DebugTypeTemplateParameter in nonsemantic_shader_debuginfo_100
    {IR(52722, 31), 174}, // DebugTypeTemplateParameterPack in nonsemantic_shader_debuginfo_100
    {IR(52687, 35), 173}, // DebugTypeTemplateTemplateParameter in nonsemantic_shader_debuginfo_100
    {IR(52466, 16), 163}, // DebugTypeVector in nonsemantic_shader_debuginfo_100
    {IR(52482, 13), 164}, // DebugTypedef in nonsemantic_shader_debuginfo_100
    {IR(52995, 11), 186}, // DebugValue in nonsemantic_shader_debuginfo_100
    {IR(55008, 14), 201}, // Configuration in nonsemantic_vkspreflection
    {IR(55084, 20), 206}, // DescriptorSetBuffer in nonsemantic_vkspreflection
    {IR(55104, 19), 207}, // DescriptorSetImage in nonsemantic_vkspreflection
    {IR(55123, 21), 208}, // DescriptorSetSampler in nonsemantic_vkspreflection
    {IR(55047, 14), 204}, // PushConstants in nonsemantic_vkspreflection
    {IR(55061, 23), 205}, // SpecializationMapEntry in nonsemantic_vkspreflection
    {IR(55022, 13), 202}, // StartCounter in nonsemantic_vkspreflection
    {IR(55035, 12), 203}, // StopCounter in nonsemantic_vkspreflection
    {IR(52255, 21), 210}, // DebugCompilationUnit in opencl_debuginfo_100
    {IR(52982, 13), 237}, // DebugDeclare in opencl_debuginfo_100
    {IR(53054, 16), 240}, // DebugExpression in opencl_debuginfo_100
    {IR(52798, 14), 229}, // DebugFunction in opencl_debuginfo_100
    {IR(52773, 25), 228}, // DebugFunctionDeclaration in opencl_debuginfo_100
    {IR(52753, 20), 227}, // DebugGlobalVariable in opencl_debuginfo_100
    {IR(54839, 20), 243}, // DebugImportedEntity in opencl_debuginfo_100
    {IR(52241, 14), 209}, // DebugInfoNone in opencl_debuginfo_100
    {IR(52885, 15), 234}, // DebugInlinedAt in opencl_debuginfo_100
    {IR(52961, 21), 236}, // DebugInlinedVariable in opencl_debuginfo_100
    {IR(52812, 18), 230}, // DebugLexicalBlock in opencl_debuginfo_100
    {IR(52830, 31), 231}, // DebugLexicalBlockDiscriminator in opencl_debuginfo_100
    {IR(52942, 19), 235}, // DebugLocalVariable in opencl_debuginfo_100
    {IR(53070, 14), 241}, // DebugMacroDef in opencl_debuginfo_100
    {IR(53084, 16), 242}, // DebugMacroUndef in opencl_debuginfo_100
    {IR(55444, 17), 245}, // DebugModuleINTEL in opencl_debuginfo_100
    {IR(52872, 13), 233}, // DebugNoScope in opencl_debuginfo_100
    {IR(53039, 15), 239}, // DebugOperation in opencl_debuginfo_100
    {IR(52861, 11), 232}, // DebugScope in opencl_debuginfo_100
    {IR(54859, 12), 244}, // DebugSource in opencl_debuginfo_100
    {IR(52451, 15), 214}, // DebugTypeArray in opencl_debuginfo_100
    {IR(52328, 15), 211}, // DebugTypeBasic in opencl_debuginfo_100
    {IR(52565, 19), 219}, // DebugTypeComposite in opencl_debuginfo_100
    {IR(52513, 14), 218}, // DebugTypeEnum in opencl_debuginfo_100
    {IR(52495, 18), 217}, // DebugTypeFunction in opencl_debuginfo_100
    {IR(52600, 21), 221}, // DebugTypeInheritance in opencl_debuginfo_100
    {IR(52584, 16), 220}, // DebugTypeMember in opencl_debuginfo_100
    {IR(52377, 17), 212}, // DebugTypePointer in opencl_debuginfo_100
    {IR(52621, 21), 222}, // DebugTypePtrToMember in opencl_debuginfo_100
    {IR(52432, 19), 213}, // DebugTypeQualifier in opencl_debuginfo_100
    {IR(52642, 18), 223}, // DebugTypeTemplate in opencl_debuginfo_100
    {IR(52660, 27), 224}, // DebugTypeTemplateParameter in opencl_debuginfo_100
    {IR(52722, 31), 226}, // DebugTypeTemplateParameterPack in opencl_debuginfo_100
    {IR(52687, 35), 225}, // DebugTypeTemplateTemplateParameter in opencl_debuginfo_100
    {IR(52466, 16), 215}, // DebugTypeVector in opencl_debuginfo_100
    {IR(52482, 13), 216}, // DebugTypedef in opencl_debuginfo_100
    {IR(52995, 11), 238}, // DebugValue in opencl_debuginfo_100
    {IR(55461, 5), 246}, // acos in opencl_std_100
    {IR(55466, 6), 247}, // acosh in opencl_std_100
    {IR(55472, 7), 248}, // acospi in opencl_std_100
    {IR(55479, 5), 249}, // asin in opencl_std_100
    {IR(55484, 6), 250}, // asinh in opencl_std_100
    {IR(55490, 7), 251}, // asinpi in opencl_std_100
    {IR(55497, 5), 252}, // atan in opencl_std_100
    {IR(55502, 6), 253}, // atan2 in opencl_std_100
    {IR(55521, 8), 256}, // atan2pi in opencl_std_100
    {IR(55508, 6), 254}, // atanh in opencl_std_100
    {IR(55514, 7), 255}, // atanpi in opencl_std_100
    {IR(56712, 10), 402}, // bitselect in opencl_std_100
    {IR(55529, 5), 257}, // cbrt in opencl_std_100
    {IR(55534, 5), 258}, // ceil in opencl_std_100
    {IR(56384, 4), 367}, // clz in opencl_std_100
    {IR(55539, 9), 259}, // copysign in opencl_std_100
    {IR(55548, 4), 260}, // cos in opencl_std_100
    {IR(55552, 5), 261}, // cosh in opencl_std_100
    {IR(55557, 6), 262}, // cospi in opencl_std_100
    {IR(56228, 6), 350}, // cross in opencl_std_100
    {IR(56388, 4), 368}, // ctz in opencl_std_100
    {IR(56163, 8), 342}, // degrees in opencl_std_100
    {IR(56234, 9), 351}, // distance in opencl_std_100
    {IR(55568, 4), 264}, // erf in opencl_std_100
    {IR(55563, 5), 263}, // erfc in opencl_std_100
    {IR(55572, 4), 265}, // exp in opencl_std_100
    {IR(55581, 6), 267}, // exp10 in opencl_std_100
    {IR(55576, 5), 266}, // exp2 in opencl_std_100
    {IR(55587, 6), 268}, // expm1 in opencl_std_100
    {IR(55593, 5), 269}, // fabs in opencl_std_100
    {IR(56260, 14), 354}, // fast_distance in opencl_std_100
    {IR(56274, 12), 355}, // fast_length in opencl_std_100
    {IR(56286, 15), 356}, // fast_normalize in opencl_std_100
    {IR(56156, 7), 341}, // fclamp in opencl_std_100
    {IR(55598, 5), 270}, // fdim in opencl_std_100
    {IR(55603, 6), 271}, // floor in opencl_std_100
    {IR(55609, 4), 272}, // fma in opencl_std_100
    {IR(55613, 5), 273}, // fmax in opencl_std_100
    {IR(56171, 12), 343}, // fmax_common in opencl_std_100
    {IR(55618, 5), 274}, // fmin in opencl_std_100
    {IR(56183, 12), 344}, // fmin_common in opencl_std_100
    {IR(55623, 5), 275}, // fmod in opencl_std_100
    {IR(55628, 6), 276}, // fract in opencl_std_100
    {IR(55634, 6), 277}, // frexp in opencl_std_100
    {IR(55846, 9), 313}, // half_cos in opencl_std_100
    {IR(55855, 12), 314}, // half_divide in opencl_std_100
    {IR(55867, 9), 315}, // half_exp in opencl_std_100
    {IR(55886, 11), 317}, // half_exp10 in opencl_std_100
    {IR(55876, 10), 316}, // half_exp2 in opencl_std_100
    {IR(55897, 9), 318}, // half_log in opencl_std_100
    {IR(55916, 11), 320}, // half_log10 in opencl_std_100
    {IR(55906, 10), 319}, // half_log2 in opencl_std_100
    {IR(55927, 10), 321}, // half_powr in opencl_std_100
    {IR(55937, 11), 322}, // half_recip in opencl_std_100
    {IR(55948, 11), 323}, // half_rsqrt in opencl_std_100
    {IR(55959, 9), 324}, // half_sin in opencl_std_100
    {IR(55968, 10), 325}, // half_sqrt in opencl_std_100
    {IR(55978, 9), 326}, // half_tan in opencl_std_100
    {IR(55640, 6), 278}, // hypot in opencl_std_100
    {IR(55646, 6), 279}, // ilogb in opencl_std_100
    {IR(55652, 6), 280}, // ldexp in opencl_std_100
    {IR(56243, 7), 352}, // length in opencl_std_100
    {IR(55658, 7), 281}, // lgamma in opencl_std_100
    {IR(55665, 9), 282}, // lgamma_r in opencl_std_100
    {IR(55674, 4), 283}, // log in opencl_std_100
    {IR(55683, 6), 285}, // log10 in opencl_std_100
    {IR(55689, 6), 286}, // log1p in opencl_std_100
    {IR(55678, 5), 284}, // log2 in opencl_std_100
    {IR(55695, 5), 287}, // logb in opencl_std_100
    {IR(55700, 4), 288}, // mad in opencl_std_100
    {IR(55704, 7), 289}, // maxmag in opencl_std_100
    {IR(55711, 7), 290}, // minmag in opencl_std_100
    {IR(56195, 4), 345}, // mix in opencl_std_100
    {IR(55718, 5), 291}, // modf in opencl_std_100
    {IR(55723, 4), 292}, // nan in opencl_std_100
    {IR(55987, 11), 327}, // native_cos in opencl_std_100
    {IR(55998, 14), 328}, // native_divide in opencl_std_100
    {IR(56012, 11), 329}, // native_exp in opencl_std_100
    {IR(56035, 13), 331}, // native_exp10 in opencl_std_100
    {IR(56023, 12), 330}, // native_exp2 in opencl_std_100
    {IR(56048, 11), 332}, // native_log in opencl_std_100
    {IR(56071, 13), 334}, // native_log10 in opencl_std_100
    {IR(56059, 12), 333}, // native_log2 in opencl_std_100
    {IR(56084, 12), 335}, // native_powr in opencl_std_100
    {IR(56096, 13), 336}, // native_recip in opencl_std_100
    {IR(56109, 13), 337}, // native_rsqrt in opencl_std_100
    {IR(56122, 11), 338}, // native_sin in opencl_std_100
    {IR(56133, 12), 339}, // native_sqrt in opencl_std_100
    {IR(56145, 11), 340}, // native_tan in opencl_std_100
    {IR(55727, 10), 293}, // nextafter in opencl_std_100
    {IR(56250, 10), 353}, // normalize in opencl_std_100
    {IR(56503, 9), 382}, // popcount in opencl_std_100
    {IR(55737, 4), 294}, // pow in opencl_std_100
    {IR(55741, 5), 295}, // pown in opencl_std_100
    {IR(55746, 5), 296}, // powr in opencl_std_100
    {IR(56703, 9), 401}, // prefetch in opencl_std_100
    {IR(56696, 7), 400}, // printf in opencl_std_100
    {IR(56199, 8), 346}, // radians in opencl_std_100
    {IR(55751, 10), 297}, // remainder in opencl_std_100
    {IR(55761, 7), 298}, // remquo in opencl_std_100
    {IR(55768, 5), 299}, // rint in opencl_std_100
    {IR(55773, 6), 300}, // rootn in opencl_std_100
    {IR(56454, 7), 377}, // rotate in opencl_std_100
    {IR(55779, 6), 301}, // round in opencl_std_100
    {IR(55785, 6), 302}, // rsqrt in opencl_std_100
    {IR(56301, 6), 357}, // s_abs in opencl_std_100
    {IR(56307, 11), 358}, // s_abs_diff in opencl_std_100
    {IR(56318, 10), 359}, // s_add_sat in opencl_std_100
    {IR(56368, 8), 365}, // s_clamp in opencl_std_100
    {IR(56338, 7), 361}, // s_hadd in opencl_std_100
    {IR(56512, 8), 383}, // s_mad24 in opencl_std_100
    {IR(56392, 9), 369}, // s_mad_hi in opencl_std_100
    {IR(56411, 10), 371}, // s_mad_sat in opencl_std_100
    {IR(56421, 6), 372}, // s_max in opencl_std_100
    {IR(56433, 6), 374}, // s_min in opencl_std_100
    {IR(56528, 8), 385}, // s_mul24 in opencl_std_100
    {IR(56445, 9), 376}, // s_mul_hi in opencl_std_100
    {IR(56352, 8), 363}, // s_rhadd in opencl_std_100
    {IR(56461, 10), 378}, // s_sub_sat in opencl_std_100
    {IR(56492, 11), 381}, // s_upsample in opencl_std_100
    {IR(56722, 7), 403}, // select in opencl_std_100
    {IR(56679, 8), 398}, // shuffle in opencl_std_100
    {IR(56687, 9), 399}, // shuffle2 in opencl_std_100
    {IR(56223, 5), 349}, // sign in opencl_std_100
    {IR(55791, 4), 303}, // sin in opencl_std_100
    {IR(55795, 7), 304}, // sincos in opencl_std_100
    {IR(55802, 5), 305}, // sinh in opencl_std_100
    {IR(55807, 6), 306}, // sinpi in opencl_std_100
    {IR(56212, 11), 348}, // smoothstep in opencl_std_100
    {IR(55813, 5), 307}, // sqrt in opencl_std_100
    {IR(56207, 5), 347}, // step in opencl_std_100
    {IR(55818, 4), 308}, // tan in opencl_std_100
    {IR(55822, 5), 309}, // tanh in opencl_std_100
    {IR(55827, 6), 310}, // tanpi in opencl_std_100
    {IR(55833, 7), 311}, // tgamma in opencl_std_100
    {IR(55840, 6), 312}, // trunc in opencl_std_100
    {IR(56729, 6), 404}, // u_abs in opencl_std_100
    {IR(56735, 11), 405}, // u_abs_diff in opencl_std_100
    {IR(56328, 10), 360}, // u_add_sat in opencl_std_100
    {IR(56376, 8), 366}, // u_clamp in opencl_std_100
    {IR(56345, 7), 362}, // u_hadd in opencl_std_100
    {IR(56520, 8), 384}, // u_mad24 in opencl_std_100
    {IR(56755, 9), 407}, // u_mad_hi in opencl_std_100
    {IR(56401, 10), 370}, // u_mad_sat in opencl_std_100
    {IR(56427, 6), 373}, // u_max in opencl_std_100
    {IR(56439, 6), 375}, // u_min in opencl_std_100
    {IR(56536, 8), 386}, // u_mul24 in opencl_std_100
    {IR(56746, 9), 406}, // u_mul_hi in opencl_std_100
    {IR(56360, 8), 364}, // u_rhadd in opencl_std_100
    {IR(56471, 10), 379}, // u_sub_sat in opencl_std_100
    {IR(56481, 11), 380}, // u_upsample in opencl_std_100
    {IR(56559, 11), 389}, // vload_half in opencl_std_100
    {IR(56570, 12), 390}, // vload_halfn in opencl_std_100
    {IR(56636, 13), 395}, // vloada_halfn in opencl_std_100
    {IR(56544, 7), 387}, // vloadn in opencl_std_100
    {IR(56582, 12), 391}, // vstore_half in opencl_std_100
    {IR(56594, 14), 392}, // vstore_half_r in opencl_std_100
    {IR(56608, 13), 393}, // vstore_halfn in opencl_std_100
    {IR(56621, 15), 394}, // vstore_halfn_r in opencl_std_100
    {IR(56649, 14), 396}, // vstorea_halfn in opencl_std_100
    {IR(56663, 16), 397}, // vstorea_halfn_r in opencl_std_100
    {IR(56551, 8), 388}, // vstoren in opencl_std_100
    {IR(56781, 17), 409}, // CubeFaceCoordAMD in spv_amd_gcn_shader
    {IR(56764, 17), 408}, // CubeFaceIndexAMD in spv_amd_gcn_shader
    {IR(56798, 8), 410}, // TimeAMD in spv_amd_gcn_shader
    {IR(56875, 9), 414}, // MbcntAMD in spv_amd_shader_ballot
    {IR(56806, 22), 411}, // SwizzleInvocationsAMD in spv_amd_shader_ballot
    {IR(56828, 28), 412}, // SwizzleInvocationsMaskedAMD in spv_amd_shader_ballot
    {IR(56856, 19), 413}, // WriteInvocationAMD in spv_amd_shader_ballot
    {IR(56884, 23), 415}, // InterpolateAtVertexAMD in spv_amd_shader_explicit_vertex_parameter
    {IR(56934, 9), 419}, // FMax3AMD in spv_amd_shader_trinary_minmax
    {IR(56961, 9), 422}, // FMid3AMD in spv_amd_shader_trinary_minmax
    {IR(56907, 9), 416}, // FMin3AMD in spv_amd_shader_trinary_minmax
    {IR(56952, 9), 421}, // SMax3AMD in spv_amd_shader_trinary_minmax
    {IR(56979, 9), 424}, // SMid3AMD in spv_amd_shader_trinary_minmax
    {IR(56925, 9), 418}, // SMin3AMD in spv_amd_shader_trinary_minmax
    {IR(56943, 9), 420}, // UMax3AMD in spv_amd_shader_trinary_minmax
    {IR(56970, 9), 423}, // UMid3AMD in spv_amd_shader_trinary_minmax
    {IR(56916, 9), 417}, // UMin3AMD in spv_amd_shader_trinary_minmax
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
  "SPV_AMD_weak_linkage\0" // IR(1020, 21)
  "SPV_ARM_cooperative_matrix_layouts\0" // IR(1041, 35)
  "SPV_ARM_core_builtins\0" // IR(1076, 22)
  "SPV_ARM_graph\0" // IR(1098, 14)
  "SPV_ARM_tensors\0" // IR(1112, 16)
  "SPV_EXT_arithmetic_fence\0" // IR(1128, 25)
  "SPV_EXT_cooperative_matrix_maintenance1\0" // IR(1153, 40)
  "SPV_EXT_demote_to_helper_invocation\0" // IR(1193, 36)
  "SPV_EXT_descriptor_heap\0" // IR(1229, 24)
  "SPV_EXT_descriptor_indexing\0" // IR(1253, 28)
  "SPV_EXT_float8\0" // IR(1281, 15)
  "SPV_EXT_fragment_fully_covered\0" // IR(1296, 31)
  "SPV_EXT_fragment_invocation_density\0" // IR(1327, 36)
  "SPV_EXT_fragment_shader_interlock\0" // IR(1363, 34)
  "SPV_EXT_long_vector\0" // IR(1397, 20)
  "SPV_EXT_mesh_shader\0" // IR(1417, 20)
  "SPV_EXT_ocp_microscaling_types\0" // IR(1437, 31)
  "SPV_EXT_opacity_micromap\0" // IR(1468, 25)
  "SPV_EXT_optnone\0" // IR(1493, 16)
  "SPV_EXT_physical_storage_buffer\0" // IR(1509, 32)
  "SPV_EXT_relaxed_printf_string_address_space\0" // IR(1541, 44)
  "SPV_EXT_replicated_composites\0" // IR(1585, 30)
  "SPV_EXT_shader_64bit_indexing\0" // IR(1615, 30)
  "SPV_EXT_shader_atomic_float16_add\0" // IR(1645, 34)
  "SPV_EXT_shader_atomic_float_add\0" // IR(1679, 32)
  "SPV_EXT_shader_atomic_float_min_max\0" // IR(1711, 36)
  "SPV_EXT_shader_image_int64\0" // IR(1747, 27)
  "SPV_EXT_shader_invocation_reorder\0" // IR(1774, 34)
  "SPV_EXT_shader_stencil_export\0" // IR(1808, 30)
  "SPV_EXT_shader_subgroup_partitioned\0" // IR(1838, 36)
  "SPV_EXT_shader_tile_image\0" // IR(1874, 26)
  "SPV_EXT_shader_viewport_index_layer\0" // IR(1900, 36)
  "SPV_EXT_split_barrier\0" // IR(1936, 22)
  "SPV_GOOGLE_decorate_string\0" // IR(1958, 27)
  "SPV_GOOGLE_hlsl_functionality1\0" // IR(1985, 31)
  "SPV_GOOGLE_user_type\0" // IR(2016, 21)
  "SPV_INTEL_2d_block_io\0" // IR(2037, 22)
  "SPV_INTEL_arbitrary_precision_fixed_point\0" // IR(2059, 42)
  "SPV_INTEL_arbitrary_precision_floating_point\0" // IR(2101, 45)
  "SPV_INTEL_arbitrary_precision_integers\0" // IR(2146, 39)
  "SPV_INTEL_bfloat16_conversion\0" // IR(2185, 30)
  "SPV_INTEL_bindless_images\0" // IR(2215, 26)
  "SPV_INTEL_blocking_pipes\0" // IR(2241, 25)
  "SPV_INTEL_cache_controls\0" // IR(2266, 25)
  "SPV_INTEL_debug_module\0" // IR(2291, 23)
  "SPV_INTEL_device_side_avc_motion_estimation\0" // IR(2314, 44)
  "SPV_INTEL_float_controls2\0" // IR(2358, 26)
  "SPV_INTEL_fp_fast_math_mode\0" // IR(2384, 28)
  "SPV_INTEL_fp_max_error\0" // IR(2412, 23)
  "SPV_INTEL_fpga_argument_interfaces\0" // IR(2435, 35)
  "SPV_INTEL_fpga_buffer_location\0" // IR(2470, 31)
  "SPV_INTEL_fpga_cluster_attributes\0" // IR(2501, 34)
  "SPV_INTEL_fpga_dsp_control\0" // IR(2535, 27)
  "SPV_INTEL_fpga_invocation_pipelining_attributes\0" // IR(2562, 48)
  "SPV_INTEL_fpga_latency_control\0" // IR(2610, 31)
  "SPV_INTEL_fpga_loop_controls\0" // IR(2641, 29)
  "SPV_INTEL_fpga_memory_accesses\0" // IR(2670, 31)
  "SPV_INTEL_fpga_memory_attributes\0" // IR(2701, 33)
  "SPV_INTEL_fpga_reg\0" // IR(2734, 19)
  "SPV_INTEL_function_pointers\0" // IR(2753, 28)
  "SPV_INTEL_function_variants\0" // IR(2781, 28)
  "SPV_INTEL_global_variable_fpga_decorations\0" // IR(2809, 43)
  "SPV_INTEL_global_variable_host_access\0" // IR(2852, 38)
  "SPV_INTEL_inline_assembly\0" // IR(2890, 26)
  "SPV_INTEL_int4\0" // IR(2916, 15)
  "SPV_INTEL_io_pipes\0" // IR(2931, 19)
  "SPV_INTEL_kernel_attributes\0" // IR(2950, 28)
  "SPV_INTEL_long_composites\0" // IR(2978, 26)
  "SPV_INTEL_loop_fuse\0" // IR(3004, 20)
  "SPV_INTEL_masked_gather_scatter\0" // IR(3024, 32)
  "SPV_INTEL_maximum_registers\0" // IR(3056, 28)
  "SPV_INTEL_media_block_io\0" // IR(3084, 25)
  "SPV_INTEL_memory_access_aliasing\0" // IR(3109, 33)
  "SPV_INTEL_optnone\0" // IR(3142, 18)
  "SPV_INTEL_predicated_io\0" // IR(3160, 24)
  "SPV_INTEL_rounded_divide_sqrt\0" // IR(3184, 30)
  "SPV_INTEL_runtime_aligned\0" // IR(3214, 26)
  "SPV_INTEL_shader_integer_functions2\0" // IR(3240, 36)
  "SPV_INTEL_split_barrier\0" // IR(3276, 24)
  "SPV_INTEL_subgroup_buffer_prefetch\0" // IR(3300, 35)
  "SPV_INTEL_subgroup_matrix_multiply_accumulate\0" // IR(3335, 46)
  "SPV_INTEL_subgroups\0" // IR(3381, 20)
  "SPV_INTEL_task_sequence\0" // IR(3401, 24)
  "SPV_INTEL_tensor_float32_conversion\0" // IR(3425, 36)
  "SPV_INTEL_ternary_bitwise_function\0" // IR(3461, 35)
  "SPV_INTEL_unstructured_loop_controls\0" // IR(3496, 37)
  "SPV_INTEL_usm_storage_classes\0" // IR(3533, 30)
  "SPV_INTEL_variable_length_array\0" // IR(3563, 32)
  "SPV_INTEL_vector_compute\0" // IR(3595, 25)
  "SPV_KHR_16bit_storage\0" // IR(3620, 22)
  "SPV_KHR_8bit_storage\0" // IR(3642, 21)
  "SPV_KHR_abort\0" // IR(3663, 14)
  "SPV_KHR_bfloat16\0" // IR(3677, 17)
  "SPV_KHR_bit_instructions\0" // IR(3694, 25)
  "SPV_KHR_compute_shader_derivatives\0" // IR(3719, 35)
  "SPV_KHR_constant_data\0" // IR(3754, 22)
  "SPV_KHR_cooperative_matrix\0" // IR(3776, 27)
  "SPV_KHR_device_group\0" // IR(3803, 21)
  "SPV_KHR_expect_assume\0" // IR(3824, 22)
  "SPV_KHR_float_controls\0" // IR(3846, 23)
  "SPV_KHR_float_controls2\0" // IR(3869, 24)
  "SPV_KHR_fma\0" // IR(3893, 12)
  "SPV_KHR_fragment_shader_barycentric\0" // IR(3905, 36)
  "SPV_KHR_fragment_shading_rate\0" // IR(3941, 30)
  "SPV_KHR_integer_dot_product\0" // IR(3971, 28)
  "SPV_KHR_linkonce_odr\0" // IR(3999, 21)
  "SPV_KHR_maximal_reconvergence\0" // IR(4020, 30)
  "SPV_KHR_multiview\0" // IR(4050, 18)
  "SPV_KHR_no_integer_wrap_decoration\0" // IR(4068, 35)
  "SPV_KHR_non_semantic_info\0" // IR(4103, 26)
  "SPV_KHR_opacity_micromap\0" // IR(4129, 25)
  "SPV_KHR_physical_storage_buffer\0" // IR(4154, 32)
  "SPV_KHR_poison_freeze\0" // IR(4186, 22)
  "SPV_KHR_post_depth_coverage\0" // IR(4208, 28)
  "SPV_KHR_quad_control\0" // IR(4236, 21)
  "SPV_KHR_ray_cull_mask\0" // IR(4257, 22)
  "SPV_KHR_ray_query\0" // IR(4279, 18)
  "SPV_KHR_ray_tracing\0" // IR(4297, 20)
  "SPV_KHR_ray_tracing_position_fetch\0" // IR(4317, 35)
  "SPV_KHR_relaxed_extended_instruction\0" // IR(4352, 37)
  "SPV_KHR_shader_atomic_counter_ops\0" // IR(4389, 34)
  "SPV_KHR_shader_ballot\0" // IR(4423, 22)
  "SPV_KHR_shader_clock\0" // IR(4445, 21)
  "SPV_KHR_shader_draw_parameters\0" // IR(4466, 31)
  "SPV_KHR_storage_buffer_storage_class\0" // IR(4497, 37)
  "SPV_KHR_subgroup_rotate\0" // IR(4534, 24)
  "SPV_KHR_subgroup_uniform_control_flow\0" // IR(4558, 38)
  "SPV_KHR_subgroup_vote\0" // IR(4596, 22)
  "SPV_KHR_terminate_invocation\0" // IR(4618, 29)
  "SPV_KHR_uniform_group_instructions\0" // IR(4647, 35)
  "SPV_KHR_untyped_pointers\0" // IR(4682, 25)
  "SPV_KHR_variable_pointers\0" // IR(4707, 26)
  "SPV_KHR_vulkan_memory_model\0" // IR(4733, 28)
  "SPV_KHR_workgroup_memory_explicit_layout\0" // IR(4761, 41)
  "SPV_NVX_multiview_per_view_attributes\0" // IR(4802, 38)
  "SPV_NV_bindless_texture\0" // IR(4840, 24)
  "SPV_NV_cluster_acceleration_structure\0" // IR(4864, 38)
  "SPV_NV_compute_shader_derivatives\0" // IR(4902, 34)
  "SPV_NV_cooperative_matrix\0" // IR(4936, 26)
  "SPV_NV_cooperative_matrix2\0" // IR(4962, 27)
  "SPV_NV_cooperative_matrix_decode_vector\0" // IR(4989, 40)
  "SPV_NV_cooperative_vector\0" // IR(5029, 26)
  "SPV_NV_displacement_micromap\0" // IR(5055, 29)
  "SPV_NV_fragment_shader_barycentric\0" // IR(5084, 35)
  "SPV_NV_geometry_shader_passthrough\0" // IR(5119, 35)
  "SPV_NV_linear_swept_spheres\0" // IR(5154, 28)
  "SPV_NV_mesh_shader\0" // IR(5182, 19)
  "SPV_NV_push_constant_bank\0" // IR(5201, 26)
  "SPV_NV_raw_access_chains\0" // IR(5227, 25)
  "SPV_NV_ray_tracing\0" // IR(5252, 19)
  "SPV_NV_ray_tracing_motion_blur\0" // IR(5271, 31)
  "SPV_NV_sample_mask_override_coverage\0" // IR(5302, 37)
  "SPV_NV_shader_atomic_fp16_vector\0" // IR(5339, 33)
  "SPV_NV_shader_image_footprint\0" // IR(5372, 30)
  "SPV_NV_shader_invocation_reorder\0" // IR(5402, 33)
  "SPV_NV_shader_sm_builtins\0" // IR(5435, 26)
  "SPV_NV_shader_subgroup_partitioned\0" // IR(5461, 35)
  "SPV_NV_shading_rate\0" // IR(5496, 20)
  "SPV_NV_stereo_view_rendering\0" // IR(5516, 29)
  "SPV_NV_tensor_addressing\0" // IR(5545, 25)
  "SPV_NV_viewport_array2\0" // IR(5570, 23)
  "SPV_QCOM_bfloat16_muladd\0" // IR(5593, 25)
  "SPV_QCOM_cooperative_matrix_conversion\0" // IR(5618, 39)
  "SPV_QCOM_image_processing\0" // IR(5657, 26)
  "SPV_QCOM_image_processing2\0" // IR(5683, 27)
  "SPV_QCOM_image_processing3\0" // IR(5710, 27)
  "SPV_QCOM_multiple_wait_queues\0" // IR(5737, 30)
  "SPV_QCOM_subgroup_size\0" // IR(5767, 23)
  "SPV_QCOM_tile_shading\0" // IR(5790, 22)
  "SPV_SAMSUNG_intrinsic\0" // IR(5812, 22)
  "SPV_VALIDATOR_ignore_type_decl_unique\0" // IR(5834, 38)
  "SPV_VALVE_mixed_float_dot_product\0" // IR(5872, 34)
  "ReadOnly\0" // IR(5906, 9)
  "Kernel\0" // IR(5915, 7)
  "WriteOnly\0" // IR(5922, 10)
  "ReadWrite\0" // IR(5932, 10)
  "Logical\0" // IR(5942, 8)
  "Physical32\0" // IR(5950, 11)
  "Addresses\0" // IR(5961, 10)
  "Physical64\0" // IR(5971, 11)
  "PhysicalStorageBuffer64\0" // IR(5982, 24)
  "PhysicalStorageBuffer64EXT\0" // IR(6006, 27)
  "PhysicalStorageBufferAddresses\0" // IR(6033, 31)
  "Position\0" // IR(6064, 9)
  "Shader\0" // IR(6073, 7)
  "PointSize\0" // IR(6080, 10)
  "ClipDistance\0" // IR(6090, 13)
  "CullDistance\0" // IR(6103, 13)
  "VertexId\0" // IR(6116, 9)
  "InstanceId\0" // IR(6125, 11)
  "PrimitiveId\0" // IR(6136, 12)
  "Geometry\0" // IR(6148, 9)
  "Tessellation\0" // IR(6157, 13)
  "RayTracingNV\0" // IR(6170, 13)
  "RayTracingKHR\0" // IR(6183, 14)
  "MeshShadingNV\0" // IR(6197, 14)
  "MeshShadingEXT\0" // IR(6211, 15)
  "InvocationId\0" // IR(6226, 13)
  "Layer\0" // IR(6239, 6)
  "ShaderLayer\0" // IR(6245, 12)
  "ShaderViewportIndexLayerEXT\0" // IR(6257, 28)
  "ViewportIndex\0" // IR(6285, 14)
  "MultiViewport\0" // IR(6299, 14)
  "ShaderViewportIndex\0" // IR(6313, 20)
  "TessLevelOuter\0" // IR(6333, 15)
  "TessLevelInner\0" // IR(6348, 15)
  "TessCoord\0" // IR(6363, 10)
  "PatchVertices\0" // IR(6373, 14)
  "FragCoord\0" // IR(6387, 10)
  "PointCoord\0" // IR(6397, 11)
  "FrontFacing\0" // IR(6408, 12)
  "SampleId\0" // IR(6420, 9)
  "SampleRateShading\0" // IR(6429, 18)
  "SamplePosition\0" // IR(6447, 15)
  "SampleMask\0" // IR(6462, 11)
  "FragDepth\0" // IR(6473, 10)
  "HelperInvocation\0" // IR(6483, 17)
  "NumWorkgroups\0" // IR(6500, 14)
  "WorkgroupSize\0" // IR(6514, 14)
  "WorkgroupId\0" // IR(6528, 12)
  "LocalInvocationId\0" // IR(6540, 18)
  "GlobalInvocationId\0" // IR(6558, 19)
  "LocalInvocationIndex\0" // IR(6577, 21)
  "WorkDim\0" // IR(6598, 8)
  "GlobalSize\0" // IR(6606, 11)
  "EnqueuedWorkgroupSize\0" // IR(6617, 22)
  "GlobalOffset\0" // IR(6639, 13)
  "GlobalLinearId\0" // IR(6652, 15)
  "SubgroupSize\0" // IR(6667, 13)
  "GroupNonUniform\0" // IR(6680, 16)
  "SubgroupBallotKHR\0" // IR(6696, 18)
  "SubgroupMaxSize\0" // IR(6714, 16)
  "NumSubgroups\0" // IR(6730, 13)
  "NumEnqueuedSubgroups\0" // IR(6743, 21)
  "SubgroupId\0" // IR(6764, 11)
  "SubgroupLocalInvocationId\0" // IR(6775, 26)
  "VertexIndex\0" // IR(6801, 12)
  "InstanceIndex\0" // IR(6813, 14)
  "CoreIDARM\0" // IR(6827, 10)
  "CoreBuiltinsARM\0" // IR(6837, 16)
  "CoreCountARM\0" // IR(6853, 13)
  "CoreMaxIDARM\0" // IR(6866, 13)
  "WarpIDARM\0" // IR(6879, 10)
  "WarpMaxIDARM\0" // IR(6889, 13)
  "SubgroupEqMask\0" // IR(6902, 15)
  "SubgroupEqMaskKHR\0" // IR(6917, 18)
  "GroupNonUniformBallot\0" // IR(6935, 22)
  "SubgroupGeMask\0" // IR(6957, 15)
  "SubgroupGeMaskKHR\0" // IR(6972, 18)
  "SubgroupGtMask\0" // IR(6990, 15)
  "SubgroupGtMaskKHR\0" // IR(7005, 18)
  "SubgroupLeMask\0" // IR(7023, 15)
  "SubgroupLeMaskKHR\0" // IR(7038, 18)
  "SubgroupLtMask\0" // IR(7056, 15)
  "SubgroupLtMaskKHR\0" // IR(7071, 18)
  "BaseVertex\0" // IR(7089, 11)
  "DrawParameters\0" // IR(7100, 15)
  "BaseInstance\0" // IR(7115, 13)
  "DrawIndex\0" // IR(7128, 10)
  "PrimitiveShadingRateKHR\0" // IR(7138, 24)
  "FragmentShadingRateKHR\0" // IR(7162, 23)
  "DeviceIndex\0" // IR(7185, 12)
  "DeviceGroup\0" // IR(7197, 12)
  "ViewIndex\0" // IR(7209, 10)
  "MultiView\0" // IR(7219, 10)
  "ShadingRateKHR\0" // IR(7229, 15)
  "TileOffsetQCOM\0" // IR(7244, 15)
  "TileShadingQCOM\0" // IR(7259, 16)
  "TileDimensionQCOM\0" // IR(7275, 18)
  "TileApronSizeQCOM\0" // IR(7293, 18)
  "BaryCoordNoPerspAMD\0" // IR(7311, 20)
  "BaryCoordNoPerspCentroidAMD\0" // IR(7331, 28)
  "BaryCoordNoPerspSampleAMD\0" // IR(7359, 26)
  "BaryCoordSmoothAMD\0" // IR(7385, 19)
  "BaryCoordSmoothCentroidAMD\0" // IR(7404, 27)
  "BaryCoordSmoothSampleAMD\0" // IR(7431, 25)
  "BaryCoordPullModelAMD\0" // IR(7456, 22)
  "FragStencilRefEXT\0" // IR(7478, 18)
  "StencilExportEXT\0" // IR(7496, 17)
  "RemainingRecursionLevelsAMDX\0" // IR(7513, 29)
  "ShaderEnqueueAMDX\0" // IR(7542, 18)
  "ShaderIndexAMDX\0" // IR(7560, 16)
  "SamplerHeapEXT\0" // IR(7576, 15)
  "DescriptorHeapEXT\0" // IR(7591, 18)
  "ResourceHeapEXT\0" // IR(7609, 16)
  "ViewportMaskNV\0" // IR(7625, 15)
  "ShaderViewportMaskNV\0" // IR(7640, 21)
  "SecondaryPositionNV\0" // IR(7661, 20)
  "ShaderStereoViewNV\0" // IR(7681, 19)
  "SecondaryViewportMaskNV\0" // IR(7700, 24)
  "PositionPerViewNV\0" // IR(7724, 18)
  "PerViewAttributesNV\0" // IR(7742, 20)
  "ViewportMaskPerViewNV\0" // IR(7762, 22)
  "FullyCoveredEXT\0" // IR(7784, 16)
  "FragmentFullyCoveredEXT\0" // IR(7800, 24)
  "TaskCountNV\0" // IR(7824, 12)
  "PrimitiveCountNV\0" // IR(7836, 17)
  "PrimitiveIndicesNV\0" // IR(7853, 19)
  "ClipDistancePerViewNV\0" // IR(7872, 22)
  "CullDistancePerViewNV\0" // IR(7894, 22)
  "LayerPerViewNV\0" // IR(7916, 15)
  "MeshViewCountNV\0" // IR(7931, 16)
  "MeshViewIndicesNV\0" // IR(7947, 18)
  "BaryCoordKHR\0" // IR(7965, 13)
  "BaryCoordNV\0" // IR(7978, 12)
  "FragmentBarycentricKHR\0" // IR(7990, 23)
  "BaryCoordNoPerspKHR\0" // IR(8013, 20)
  "BaryCoordNoPerspNV\0" // IR(8033, 19)
  "FragSizeEXT\0" // IR(8052, 12)
  "FragmentSizeNV\0" // IR(8064, 15)
  "FragmentDensityEXT\0" // IR(8079, 19)
  "FragInvocationCountEXT\0" // IR(8098, 23)
  "InvocationsPerPixelNV\0" // IR(8121, 22)
  "PrimitivePointIndicesEXT\0" // IR(8143, 25)
  "PrimitiveLineIndicesEXT\0" // IR(8168, 24)
  "PrimitiveTriangleIndicesEXT\0" // IR(8192, 28)
  "CullPrimitiveEXT\0" // IR(8220, 17)
  "LaunchIdKHR\0" // IR(8237, 12)
  "LaunchIdNV\0" // IR(8249, 11)
  "LaunchSizeKHR\0" // IR(8260, 14)
  "LaunchSizeNV\0" // IR(8274, 13)
  "WorldRayOriginKHR\0" // IR(8287, 18)
  "WorldRayOriginNV\0" // IR(8305, 17)
  "WorldRayDirectionKHR\0" // IR(8322, 21)
  "WorldRayDirectionNV\0" // IR(8343, 20)
  "ObjectRayOriginKHR\0" // IR(8363, 19)
  "ObjectRayOriginNV\0" // IR(8382, 18)
  "ObjectRayDirectionKHR\0" // IR(8400, 22)
  "ObjectRayDirectionNV\0" // IR(8422, 21)
  "RayTminKHR\0" // IR(8443, 11)
  "RayTminNV\0" // IR(8454, 10)
  "RayTmaxKHR\0" // IR(8464, 11)
  "RayTmaxNV\0" // IR(8475, 10)
  "InstanceCustomIndexKHR\0" // IR(8485, 23)
  "InstanceCustomIndexNV\0" // IR(8508, 22)
  "ObjectToWorldKHR\0" // IR(8530, 17)
  "ObjectToWorldNV\0" // IR(8547, 16)
  "WorldToObjectKHR\0" // IR(8563, 17)
  "WorldToObjectNV\0" // IR(8580, 16)
  "HitTNV\0" // IR(8596, 7)
  "HitKindKHR\0" // IR(8603, 11)
  "HitKindNV\0" // IR(8614, 10)
  "CurrentRayTimeNV\0" // IR(8624, 17)
  "RayTracingMotionBlurNV\0" // IR(8641, 23)
  "HitTriangleVertexPositionsKHR\0" // IR(8664, 30)
  "RayTracingPositionFetchKHR\0" // IR(8694, 27)
  "HitMicroTriangleVertexPositionsNV\0" // IR(8721, 34)
  "RayTracingDisplacementMicromapNV\0" // IR(8755, 33)
  "HitMicroTriangleVertexBarycentricsNV\0" // IR(8788, 37)
  "IncomingRayFlagsKHR\0" // IR(8825, 20)
  "IncomingRayFlagsNV\0" // IR(8845, 19)
  "RayGeometryIndexKHR\0" // IR(8864, 20)
  "HitIsSphereNV\0" // IR(8884, 14)
  "RayTracingSpheresGeometryNV\0" // IR(8898, 28)
  "HitIsLSSNV\0" // IR(8926, 11)
  "RayTracingLinearSweptSpheresGeometryNV\0" // IR(8937, 39)
  "HitSpherePositionNV\0" // IR(8976, 20)
  "WarpsPerSMNV\0" // IR(8996, 13)
  "ShaderSMBuiltinsNV\0" // IR(9009, 19)
  "SMCountNV\0" // IR(9028, 10)
  "WarpIDNV\0" // IR(9038, 9)
  "SMIDNV\0" // IR(9047, 7)
  "HitLSSPositionsNV\0" // IR(9054, 18)
  "HitKindFrontFacingMicroTriangleNV\0" // IR(9072, 34)
  "HitKindBackFacingMicroTriangleNV\0" // IR(9106, 33)
  "HitSphereRadiusNV\0" // IR(9139, 18)
  "HitLSSRadiiNV\0" // IR(9157, 14)
  "ClusterIDNV\0" // IR(9171, 12)
  "RayTracingClusterAccelerationStructureNV\0" // IR(9183, 41)
  "CullMaskKHR\0" // IR(9224, 12)
  "RayCullMaskKHR\0" // IR(9236, 15)
  "Matrix\0" // IR(9251, 7)
  "Linkage\0" // IR(9258, 8)
  "Vector16\0" // IR(9266, 9)
  "Float16Buffer\0" // IR(9275, 14)
  "Float16\0" // IR(9289, 8)
  "Float64\0" // IR(9297, 8)
  "Int64\0" // IR(9305, 6)
  "Int64Atomics\0" // IR(9311, 13)
  "ImageBasic\0" // IR(9324, 11)
  "ImageReadWrite\0" // IR(9335, 15)
  "ImageMipmap\0" // IR(9350, 12)
  "Pipes\0" // IR(9362, 6)
  "Groups\0" // IR(9368, 7)
  "DeviceEnqueue\0" // IR(9375, 14)
  "LiteralSampler\0" // IR(9389, 15)
  "AtomicStorage\0" // IR(9404, 14)
  "Int16\0" // IR(9418, 6)
  "TessellationPointSize\0" // IR(9424, 22)
  "GeometryPointSize\0" // IR(9446, 18)
  "ImageGatherExtended\0" // IR(9464, 20)
  "StorageImageMultisample\0" // IR(9484, 24)
  "UniformBufferArrayDynamicIndexing\0" // IR(9508, 34)
  "SampledImageArrayDynamicIndexing\0" // IR(9542, 33)
  "StorageBufferArrayDynamicIndexing\0" // IR(9575, 34)
  "StorageImageArrayDynamicIndexing\0" // IR(9609, 33)
  "ImageCubeArray\0" // IR(9642, 15)
  "SampledCubeArray\0" // IR(9657, 17)
  "ImageRect\0" // IR(9674, 10)
  "SampledRect\0" // IR(9684, 12)
  "GenericPointer\0" // IR(9696, 15)
  "Int8\0" // IR(9711, 5)
  "InputAttachment\0" // IR(9716, 16)
  "SparseResidency\0" // IR(9732, 16)
  "MinLod\0" // IR(9748, 7)
  "Sampled1D\0" // IR(9755, 10)
  "Image1D\0" // IR(9765, 8)
  "SampledBuffer\0" // IR(9773, 14)
  "ImageBuffer\0" // IR(9787, 12)
  "ImageMSArray\0" // IR(9799, 13)
  "StorageImageExtendedFormats\0" // IR(9812, 28)
  "ImageQuery\0" // IR(9840, 11)
  "DerivativeControl\0" // IR(9851, 18)
  "InterpolationFunction\0" // IR(9869, 22)
  "TransformFeedback\0" // IR(9891, 18)
  "GeometryStreams\0" // IR(9909, 16)
  "StorageImageReadWithoutFormat\0" // IR(9925, 30)
  "StorageImageWriteWithoutFormat\0" // IR(9955, 31)
  "SubgroupDispatch\0" // IR(9986, 17)
  "NamedBarrier\0" // IR(10003, 13)
  "PipeStorage\0" // IR(10016, 12)
  "GroupNonUniformVote\0" // IR(10028, 20)
  "GroupNonUniformArithmetic\0" // IR(10048, 26)
  "GroupNonUniformShuffle\0" // IR(10074, 23)
  "GroupNonUniformShuffleRelative\0" // IR(10097, 31)
  "GroupNonUniformClustered\0" // IR(10128, 25)
  "GroupNonUniformQuad\0" // IR(10153, 20)
  "UniformDecoration\0" // IR(10173, 18)
  "TileImageColorReadAccessEXT\0" // IR(10191, 28)
  "TileImageDepthReadAccessEXT\0" // IR(10219, 28)
  "TileImageStencilReadAccessEXT\0" // IR(10247, 30)
  "TensorsARM\0" // IR(10277, 11)
  "StorageTensorArrayDynamicIndexingARM\0" // IR(10288, 37)
  "StorageTensorArrayNonUniformIndexingARM\0" // IR(10325, 40)
  "GraphARM\0" // IR(10365, 9)
  "CooperativeMatrixLayoutsARM\0" // IR(10374, 28)
  "Float8EXT\0" // IR(10402, 10)
  "Float8CooperativeMatrixEXT\0" // IR(10412, 27)
  "CooperativeMatrixKHR\0" // IR(10439, 21)
  "Float6EXT\0" // IR(10460, 10)
  "Float4EXT\0" // IR(10470, 10)
  "Float8UnsignedE8M0EXT\0" // IR(10480, 22)
  "MXInt8EXT\0" // IR(10502, 10)
  "BitcastExtractEXT\0" // IR(10512, 18)
  "WorkgroupMemoryExplicitLayoutKHR\0" // IR(10530, 33)
  "WorkgroupMemoryExplicitLayout8BitAccessKHR\0" // IR(10563, 43)
  "WorkgroupMemoryExplicitLayout16BitAccessKHR\0" // IR(10606, 44)
  "SubgroupVoteKHR\0" // IR(10650, 16)
  "StorageBuffer16BitAccess\0" // IR(10666, 25)
  "StorageUniformBufferBlock16\0" // IR(10691, 28)
  "UniformAndStorageBuffer16BitAccess\0" // IR(10719, 35)
  "StorageUniform16\0" // IR(10754, 17)
  "StoragePushConstant16\0" // IR(10771, 22)
  "StorageInputOutput16\0" // IR(10793, 21)
  "VariablePointersStorageBuffer\0" // IR(10814, 30)
  "VariablePointers\0" // IR(10844, 17)
  "AtomicStorageOps\0" // IR(10861, 17)
  "SampleMaskPostDepthCoverage\0" // IR(10878, 28)
  "StorageBuffer8BitAccess\0" // IR(10906, 24)
  "UniformAndStorageBuffer8BitAccess\0" // IR(10930, 34)
  "StoragePushConstant8\0" // IR(10964, 21)
  "DenormPreserve\0" // IR(10985, 15)
  "DenormFlushToZero\0" // IR(11000, 18)
  "SignedZeroInfNanPreserve\0" // IR(11018, 25)
  "RoundingModeRTE\0" // IR(11043, 16)
  "RoundingModeRTZ\0" // IR(11059, 16)
  "RayQueryProvisionalKHR\0" // IR(11075, 23)
  "RayQueryKHR\0" // IR(11098, 12)
  "UntypedPointersKHR\0" // IR(11110, 19)
  "RayTraversalPrimitiveCullingKHR\0" // IR(11129, 32)
  "TextureSampleWeightedQCOM\0" // IR(11161, 26)
  "TextureBoxFilterQCOM\0" // IR(11187, 21)
  "TextureBlockMatchQCOM\0" // IR(11208, 22)
  "CooperativeMatrixConversionQCOM\0" // IR(11230, 32)
  "TextureBlockMatch2QCOM\0" // IR(11262, 23)
  "BFloat16MulAddQCOM\0" // IR(11285, 19)
  "SubgroupSizeQCOM\0" // IR(11304, 17)
  "MultipleWaitQueuesQCOM\0" // IR(11321, 23)
  "ImageGatherLinearQCOM\0" // IR(11344, 22)
  "ImageGatherExtendedModesQCOM\0" // IR(11366, 29)
  "Float16ImageAMD\0" // IR(11395, 16)
  "ImageGatherBiasLodAMD\0" // IR(11411, 22)
  "FragmentMaskAMD\0" // IR(11433, 16)
  "ImageReadWriteLodAMD\0" // IR(11449, 21)
  "Int64ImageEXT\0" // IR(11470, 14)
  "ShaderClockKHR\0" // IR(11484, 15)
  "QuadControlKHR\0" // IR(11499, 15)
  "Int4TypeINTEL\0" // IR(11514, 14)
  "Int4CooperativeMatrixINTEL\0" // IR(11528, 27)
  "BFloat16TypeKHR\0" // IR(11555, 16)
  "BFloat16DotProductKHR\0" // IR(11571, 22)
  "BFloat16CooperativeMatrixKHR\0" // IR(11593, 29)
  "AbortKHR\0" // IR(11622, 9)
  "ConstantDataKHR\0" // IR(11631, 16)
  "PoisonFreezeKHR\0" // IR(11647, 16)
  "WeakLinkageAMD\0" // IR(11663, 15)
  "SampleMaskOverrideCoverageNV\0" // IR(11678, 29)
  "GeometryShaderPassthroughNV\0" // IR(11707, 28)
  "ShaderViewportIndexLayerNV\0" // IR(11735, 27)
  "ImageFootprintNV\0" // IR(11762, 17)
  "FragmentBarycentricNV\0" // IR(11779, 22)
  "ComputeDerivativeGroupQuadsKHR\0" // IR(11801, 31)
  "ComputeDerivativeGroupQuadsNV\0" // IR(11832, 30)
  "ShadingRateNV\0" // IR(11862, 14)
  "GroupNonUniformPartitionedEXT\0" // IR(11876, 30)
  "GroupNonUniformPartitionedNV\0" // IR(11906, 29)
  "ShaderNonUniform\0" // IR(11935, 17)
  "ShaderNonUniformEXT\0" // IR(11952, 20)
  "RuntimeDescriptorArray\0" // IR(11972, 23)
  "RuntimeDescriptorArrayEXT\0" // IR(11995, 26)
  "InputAttachmentArrayDynamicIndexing\0" // IR(12021, 36)
  "InputAttachmentArrayDynamicIndexingEXT\0" // IR(12057, 39)
  "UniformTexelBufferArrayDynamicIndexing\0" // IR(12096, 39)
  "UniformTexelBufferArrayDynamicIndexingEXT\0" // IR(12135, 42)
  "StorageTexelBufferArrayDynamicIndexing\0" // IR(12177, 39)
  "StorageTexelBufferArrayDynamicIndexingEXT\0" // IR(12216, 42)
  "UniformBufferArrayNonUniformIndexing\0" // IR(12258, 37)
  "UniformBufferArrayNonUniformIndexingEXT\0" // IR(12295, 40)
  "SampledImageArrayNonUniformIndexing\0" // IR(12335, 36)
  "SampledImageArrayNonUniformIndexingEXT\0" // IR(12371, 39)
  "StorageBufferArrayNonUniformIndexing\0" // IR(12410, 37)
  "StorageBufferArrayNonUniformIndexingEXT\0" // IR(12447, 40)
  "StorageImageArrayNonUniformIndexing\0" // IR(12487, 36)
  "StorageImageArrayNonUniformIndexingEXT\0" // IR(12523, 39)
  "InputAttachmentArrayNonUniformIndexing\0" // IR(12562, 39)
  "InputAttachmentArrayNonUniformIndexingEXT\0" // IR(12601, 42)
  "UniformTexelBufferArrayNonUniformIndexing\0" // IR(12643, 42)
  "UniformTexelBufferArrayNonUniformIndexingEXT\0" // IR(12685, 45)
  "StorageTexelBufferArrayNonUniformIndexing\0" // IR(12730, 42)
  "StorageTexelBufferArrayNonUniformIndexingEXT\0" // IR(12772, 45)
  "VulkanMemoryModel\0" // IR(12817, 18)
  "VulkanMemoryModelKHR\0" // IR(12835, 21)
  "VulkanMemoryModelDeviceScope\0" // IR(12856, 29)
  "VulkanMemoryModelDeviceScopeKHR\0" // IR(12885, 32)
  "PhysicalStorageBufferAddressesEXT\0" // IR(12917, 34)
  "ComputeDerivativeGroupLinearKHR\0" // IR(12951, 32)
  "ComputeDerivativeGroupLinearNV\0" // IR(12983, 31)
  "RayTracingProvisionalKHR\0" // IR(13014, 25)
  "CooperativeMatrixNV\0" // IR(13039, 20)
  "FragmentShaderSampleInterlockEXT\0" // IR(13059, 33)
  "FragmentShaderShadingRateInterlockEXT\0" // IR(13092, 38)
  "FragmentShaderPixelInterlockEXT\0" // IR(13130, 32)
  "DemoteToHelperInvocation\0" // IR(13162, 25)
  "DemoteToHelperInvocationEXT\0" // IR(13187, 28)
  "DisplacementMicromapNV\0" // IR(13215, 23)
  "RayTracingOpacityMicromapKHR\0" // IR(13238, 29)
  "RayTracingOpacityMicromapEXT\0" // IR(13267, 29)
  "ShaderInvocationReorderNV\0" // IR(13296, 26)
  "ShaderInvocationReorderEXT\0" // IR(13322, 27)
  "BindlessTextureNV\0" // IR(13349, 18)
  "RayQueryPositionFetchKHR\0" // IR(13367, 25)
  "CooperativeVectorNV\0" // IR(13392, 20)
  "AtomicFloat16VectorNV\0" // IR(13412, 22)
  "RawAccessChainsNV\0" // IR(13434, 18)
  "PushConstantBanksNV\0" // IR(13452, 20)
  "LongVectorEXT\0" // IR(13472, 14)
  "Shader64BitIndexingEXT\0" // IR(13486, 23)
  "CooperativeMatrixConversionsEXT\0" // IR(13509, 32)
  "CooperativeMatrixReductionsEXT\0" // IR(13541, 31)
  "CooperativeMatrixReductionsNV\0" // IR(13572, 30)
  "CooperativeMatrixConversionsNV\0" // IR(13602, 31)
  "CooperativeMatrixPerElementOperationsEXT\0" // IR(13633, 41)
  "CooperativeMatrixPerElementOperationsNV\0" // IR(13674, 40)
  "CooperativeMatrixTensorAddressingNV\0" // IR(13714, 36)
  "CooperativeMatrixBlockLoadsNV\0" // IR(13750, 30)
  "CooperativeVectorTrainingNV\0" // IR(13780, 28)
  "CooperativeMatrixGetCoordinateEXT\0" // IR(13808, 34)
  "TensorAddressingNV\0" // IR(13842, 19)
  "CooperativeMatrixDecodeVectorNV\0" // IR(13861, 32)
  "SubgroupShuffleINTEL\0" // IR(13893, 21)
  "SubgroupBufferBlockIOINTEL\0" // IR(13914, 27)
  "SubgroupImageBlockIOINTEL\0" // IR(13941, 26)
  "SubgroupImageMediaBlockIOINTEL\0" // IR(13967, 31)
  "RoundToInfinityINTEL\0" // IR(13998, 21)
  "FloatingPointModeINTEL\0" // IR(14019, 23)
  "IntegerFunctions2INTEL\0" // IR(14042, 23)
  "FunctionPointersINTEL\0" // IR(14065, 22)
  "IndirectReferencesINTEL\0" // IR(14087, 24)
  "AsmINTEL\0" // IR(14111, 9)
  "AtomicFloat32MinMaxEXT\0" // IR(14120, 23)
  "AtomicFloat64MinMaxEXT\0" // IR(14143, 23)
  "AtomicFloat16MinMaxEXT\0" // IR(14166, 23)
  "VectorComputeINTEL\0" // IR(14189, 19)
  "VectorAnyINTEL\0" // IR(14208, 15)
  "ExpectAssumeKHR\0" // IR(14223, 16)
  "SubgroupAvcMotionEstimationINTEL\0" // IR(14239, 33)
  "SubgroupAvcMotionEstimationIntraINTEL\0" // IR(14272, 38)
  "SubgroupAvcMotionEstimationChromaINTEL\0" // IR(14310, 39)
  "VariableLengthArrayINTEL\0" // IR(14349, 25)
  "FunctionFloatControlINTEL\0" // IR(14374, 26)
  "FPGAMemoryAttributesALTERA\0" // IR(14400, 27)
  "FPGAMemoryAttributesINTEL\0" // IR(14427, 26)
  "FPFastMathModeINTEL\0" // IR(14453, 20)
  "ArbitraryPrecisionIntegersALTERA\0" // IR(14473, 33)
  "ArbitraryPrecisionIntegersINTEL\0" // IR(14506, 32)
  "ArbitraryPrecisionFloatingPointALTERA\0" // IR(14538, 38)
  "ArbitraryPrecisionFloatingPointINTEL\0" // IR(14576, 37)
  "UnstructuredLoopControlsINTEL\0" // IR(14613, 30)
  "FPGALoopControlsALTERA\0" // IR(14643, 23)
  "FPGALoopControlsINTEL\0" // IR(14666, 22)
  "KernelAttributesINTEL\0" // IR(14688, 22)
  "FPGAKernelAttributesINTEL\0" // IR(14710, 26)
  "FPGAMemoryAccessesALTERA\0" // IR(14736, 25)
  "FPGAMemoryAccessesINTEL\0" // IR(14761, 24)
  "FPGAClusterAttributesALTERA\0" // IR(14785, 28)
  "FPGAClusterAttributesINTEL\0" // IR(14813, 27)
  "LoopFuseALTERA\0" // IR(14840, 15)
  "LoopFuseINTEL\0" // IR(14855, 14)
  "FPGADSPControlALTERA\0" // IR(14869, 21)
  "FPGADSPControlINTEL\0" // IR(14890, 20)
  "MemoryAccessAliasingINTEL\0" // IR(14910, 26)
  "FPGAInvocationPipeliningAttributesALTERA\0" // IR(14936, 41)
  "FPGAInvocationPipeliningAttributesINTEL\0" // IR(14977, 40)
  "FPGABufferLocationALTERA\0" // IR(15017, 25)
  "FPGABufferLocationINTEL\0" // IR(15042, 24)
  "ArbitraryPrecisionFixedPointALTERA\0" // IR(15066, 35)
  "ArbitraryPrecisionFixedPointINTEL\0" // IR(15101, 34)
  "USMStorageClassesALTERA\0" // IR(15135, 24)
  "USMStorageClassesINTEL\0" // IR(15159, 23)
  "RuntimeAlignedAttributeALTERA\0" // IR(15182, 30)
  "RuntimeAlignedAttributeINTEL\0" // IR(15212, 29)
  "IOPipesALTERA\0" // IR(15241, 14)
  "IOPipesINTEL\0" // IR(15255, 13)
  "BlockingPipesALTERA\0" // IR(15268, 20)
  "BlockingPipesINTEL\0" // IR(15288, 19)
  "FPGARegALTERA\0" // IR(15307, 14)
  "FPGARegINTEL\0" // IR(15321, 13)
  "DotProductInputAll\0" // IR(15334, 19)
  "DotProductInputAllKHR\0" // IR(15353, 22)
  "DotProductInput4x8Bit\0" // IR(15375, 22)
  "DotProductInput4x8BitKHR\0" // IR(15397, 25)
  "DotProductInput4x8BitPacked\0" // IR(15422, 28)
  "DotProductInput4x8BitPackedKHR\0" // IR(15450, 31)
  "DotProduct\0" // IR(15481, 11)
  "DotProductKHR\0" // IR(15492, 14)
  "ReplicatedCompositesEXT\0" // IR(15506, 24)
  "BitInstructions\0" // IR(15530, 16)
  "GroupNonUniformRotateKHR\0" // IR(15546, 25)
  "FloatControls2\0" // IR(15571, 15)
  "FMAKHR\0" // IR(15586, 7)
  "RayTracingOpacityMicromapExecutionModeKHR\0" // IR(15593, 42)
  "AtomicFloat32AddEXT\0" // IR(15635, 20)
  "AtomicFloat64AddEXT\0" // IR(15655, 20)
  "LongCompositesINTEL\0" // IR(15675, 20)
  "OptNoneEXT\0" // IR(15695, 11)
  "OptNoneINTEL\0" // IR(15706, 13)
  "AtomicFloat16AddEXT\0" // IR(15719, 20)
  "DebugInfoModuleINTEL\0" // IR(15739, 21)
  "BFloat16ConversionINTEL\0" // IR(15760, 24)
  "SplitBarrierEXT\0" // IR(15784, 16)
  "SplitBarrierINTEL\0" // IR(15800, 18)
  "ArithmeticFenceEXT\0" // IR(15818, 19)
  "FPGAClusterAttributesV2ALTERA\0" // IR(15837, 30)
  "FPGAClusterAttributesV2INTEL\0" // IR(15867, 29)
  "FPGAKernelAttributesv2INTEL\0" // IR(15896, 28)
  "TaskSequenceALTERA\0" // IR(15924, 19)
  "TaskSequenceINTEL\0" // IR(15943, 18)
  "FPMaxErrorINTEL\0" // IR(15961, 16)
  "FPGALatencyControlALTERA\0" // IR(15977, 25)
  "FPGALatencyControlINTEL\0" // IR(16002, 24)
  "FPGAArgumentInterfacesALTERA\0" // IR(16026, 29)
  "FPGAArgumentInterfacesINTEL\0" // IR(16055, 28)
  "GlobalVariableHostAccessINTEL\0" // IR(16083, 30)
  "GlobalVariableFPGADecorationsALTERA\0" // IR(16113, 36)
  "GlobalVariableFPGADecorationsINTEL\0" // IR(16149, 35)
  "SubgroupBufferPrefetchINTEL\0" // IR(16184, 28)
  "Subgroup2DBlockIOINTEL\0" // IR(16212, 23)
  "Subgroup2DBlockTransformINTEL\0" // IR(16235, 30)
  "Subgroup2DBlockTransposeINTEL\0" // IR(16265, 30)
  "SubgroupMatrixMultiplyAccumulateINTEL\0" // IR(16295, 38)
  "TernaryBitwiseFunctionINTEL\0" // IR(16333, 28)
  "UntypedVariableLengthArrayINTEL\0" // IR(16361, 32)
  "SpecConditionalINTEL\0" // IR(16393, 21)
  "FunctionVariantsINTEL\0" // IR(16414, 22)
  "PredicatedIOINTEL\0" // IR(16436, 18)
  "RoundedDivideSqrtINTEL\0" // IR(16454, 23)
  "GroupUniformArithmeticKHR\0" // IR(16477, 26)
  "TensorFloat32RoundingINTEL\0" // IR(16503, 27)
  "MaskedGatherScatterINTEL\0" // IR(16530, 25)
  "CacheControlsINTEL\0" // IR(16555, 19)
  "RegisterLimitsINTEL\0" // IR(16574, 20)
  "BindlessImagesINTEL\0" // IR(16594, 20)
  "DotProductFloat16AccFloat32VALVE\0" // IR(16614, 33)
  "DotProductFloat16AccFloat16VALVE\0" // IR(16647, 33)
  "DotProductBFloat16AccVALVE\0" // IR(16680, 27)
  "DotProductFloat8AccFloat32VALVE\0" // IR(16707, 32)
  "IntrinsicSAMSUNG\0" // IR(16739, 17)
  "Unspecified\0" // IR(16756, 12)
  "Address\0" // IR(16768, 8)
  "Boolean\0" // IR(16776, 8)
  "Float\0" // IR(16784, 6)
  "Signed\0" // IR(16790, 7)
  "SignedChar\0" // IR(16797, 11)
  "Unsigned\0" // IR(16808, 9)
  "UnsignedChar\0" // IR(16817, 13)
  "Class\0" // IR(16830, 6)
  "Structure\0" // IR(16836, 10)
  "Union\0" // IR(16846, 6)
  "ImportedModule\0" // IR(16852, 15)
  "ImportedDeclaration\0" // IR(16867, 20)
  "None\0" // IR(16887, 5)
  "FlagIsProtected\0" // IR(16892, 16)
  "FlagIsPrivate\0" // IR(16908, 14)
  "FlagIsPublic\0" // IR(16922, 13)
  "FlagIsLocal\0" // IR(16935, 12)
  "FlagIsDefinition\0" // IR(16947, 17)
  "FlagFwdDecl\0" // IR(16964, 12)
  "FlagArtificial\0" // IR(16976, 15)
  "FlagExplicit\0" // IR(16991, 13)
  "FlagPrototyped\0" // IR(17004, 15)
  "FlagObjectPointer\0" // IR(17019, 18)
  "FlagStaticMember\0" // IR(17037, 17)
  "FlagIndirectVariable\0" // IR(17054, 21)
  "FlagLValueReference\0" // IR(17075, 20)
  "FlagRValueReference\0" // IR(17095, 20)
  "FlagIsOptimized\0" // IR(17115, 16)
  "FlagIsEnumClass\0" // IR(17131, 16)
  "FlagTypePassByValue\0" // IR(17147, 20)
  "FlagTypePassByReference\0" // IR(17167, 24)
  "Deref\0" // IR(17191, 6)
  "Plus\0" // IR(17197, 5)
  "Minus\0" // IR(17202, 6)
  "SPV_OPERAND_TYPE_LITERAL_INTEGER\0" // IR(17208, 33)
  "PlusUconst\0" // IR(17241, 11)
  "BitPiece\0" // IR(17252, 9)
  "Swap\0" // IR(17261, 5)
  "Xderef\0" // IR(17266, 7)
  "StackValue\0" // IR(17273, 11)
  "Constu\0" // IR(17284, 7)
  "Fragment\0" // IR(17291, 9)
  "ConstType\0" // IR(17300, 10)
  "VolatileType\0" // IR(17310, 13)
  "RestrictType\0" // IR(17323, 13)
  "AtomicType\0" // IR(17336, 11)
  "Float16NV\0" // IR(17347, 10)
  "Float32NV\0" // IR(17357, 10)
  "Float64NV\0" // IR(17367, 10)
  "SignedInt8NV\0" // IR(17377, 13)
  "SignedInt16NV\0" // IR(17390, 14)
  "SignedInt32NV\0" // IR(17404, 14)
  "SignedInt64NV\0" // IR(17418, 14)
  "UnsignedInt8NV\0" // IR(17432, 15)
  "UnsignedInt16NV\0" // IR(17447, 16)
  "UnsignedInt32NV\0" // IR(17463, 16)
  "UnsignedInt64NV\0" // IR(17479, 16)
  "SignedInt8PackedNV\0" // IR(17495, 19)
  "UnsignedInt8PackedNV\0" // IR(17514, 21)
  "FloatE4M3NV\0" // IR(17535, 12)
  "FloatE5M2NV\0" // IR(17547, 12)
  "RowMajorKHR\0" // IR(17559, 12)
  "ColumnMajorKHR\0" // IR(17571, 15)
  "RowBlockedInterleavedARM\0" // IR(17586, 25)
  "ColumnBlockedInterleavedARM\0" // IR(17611, 28)
  "NoneKHR\0" // IR(17639, 8)
  "MatrixASignedComponentsKHR\0" // IR(17647, 27)
  "MatrixBSignedComponentsKHR\0" // IR(17674, 27)
  "MatrixCSignedComponentsKHR\0" // IR(17701, 27)
  "MatrixResultSignedComponentsKHR\0" // IR(17728, 32)
  "SaturatingAccumulationKHR\0" // IR(17760, 26)
  "Row\0" // IR(17786, 4)
  "Column\0" // IR(17790, 7)
  "2x2\0" // IR(17797, 4)
  "MatrixAKHR\0" // IR(17801, 11)
  "MatrixBKHR\0" // IR(17812, 11)
  "MatrixAccumulatorKHR\0" // IR(17823, 21)
  "RowMajorNV\0" // IR(17844, 11)
  "ColumnMajorNV\0" // IR(17855, 14)
  "InferencingOptimalNV\0" // IR(17869, 21)
  "TrainingOptimalNV\0" // IR(17890, 18)
  "RelaxedPrecision\0" // IR(17908, 17)
  "SpecId\0" // IR(17925, 7)
  "Block\0" // IR(17932, 6)
  "BufferBlock\0" // IR(17938, 12)
  "RowMajor\0" // IR(17950, 9)
  "ColMajor\0" // IR(17959, 9)
  "ArrayStride\0" // IR(17968, 12)
  "MatrixStride\0" // IR(17980, 13)
  "GLSLShared\0" // IR(17993, 11)
  "GLSLPacked\0" // IR(18004, 11)
  "CPacked\0" // IR(18015, 8)
  "SPV_OPERAND_TYPE_BUILT_IN\0" // IR(18023, 26)
  "BuiltIn\0" // IR(18049, 8)
  "NoPerspective\0" // IR(18057, 14)
  "Flat\0" // IR(18071, 5)
  "Patch\0" // IR(18076, 6)
  "Centroid\0" // IR(18082, 9)
  "Sample\0" // IR(18091, 7)
  "Invariant\0" // IR(18098, 10)
  "Restrict\0" // IR(18108, 9)
  "Aliased\0" // IR(18117, 8)
  "Volatile\0" // IR(18125, 9)
  "Constant\0" // IR(18134, 9)
  "Coherent\0" // IR(18143, 9)
  "NonWritable\0" // IR(18152, 12)
  "NonReadable\0" // IR(18164, 12)
  "Uniform\0" // IR(18176, 8)
  "SPV_OPERAND_TYPE_SCOPE_ID\0" // IR(18184, 26)
  "UniformId\0" // IR(18210, 10)
  "SaturatedConversion\0" // IR(18220, 20)
  "Stream\0" // IR(18240, 7)
  "Location\0" // IR(18247, 9)
  "Component\0" // IR(18256, 10)
  "Index\0" // IR(18266, 6)
  "Binding\0" // IR(18272, 8)
  "DescriptorSet\0" // IR(18280, 14)
  "Offset\0" // IR(18294, 7)
  "XfbBuffer\0" // IR(18301, 10)
  "XfbStride\0" // IR(18311, 10)
  "SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE\0" // IR(18321, 46)
  "FuncParamAttr\0" // IR(18367, 14)
  "SPV_OPERAND_TYPE_FP_ROUNDING_MODE\0" // IR(18381, 34)
  "FPRoundingMode\0" // IR(18415, 15)
  "SPV_OPERAND_TYPE_FP_FAST_MATH_MODE\0" // IR(18430, 35)
  "FPFastMathMode\0" // IR(18465, 15)
  "SPV_OPERAND_TYPE_LITERAL_STRING\0" // IR(18480, 32)
  "SPV_OPERAND_TYPE_LINKAGE_TYPE\0" // IR(18512, 30)
  "LinkageAttributes\0" // IR(18542, 18)
  "NoContraction\0" // IR(18560, 14)
  "InputAttachmentIndex\0" // IR(18574, 21)
  "Alignment\0" // IR(18595, 10)
  "MaxByteOffset\0" // IR(18605, 14)
  "SPV_OPERAND_TYPE_ID\0" // IR(18619, 20)
  "AlignmentId\0" // IR(18639, 12)
  "MaxByteOffsetId\0" // IR(18651, 16)
  "SaturatedToLargestFloat8NormalConversionEXT\0" // IR(18667, 44)
  "NoSignedWrap\0" // IR(18711, 13)
  "NoUnsignedWrap\0" // IR(18724, 15)
  "WeightTextureQCOM\0" // IR(18739, 18)
  "BlockMatchTextureQCOM\0" // IR(18757, 22)
  "BlockMatchSamplerQCOM\0" // IR(18779, 22)
  "ExplicitInterpAMD\0" // IR(18801, 18)
  "NodeSharesPayloadLimitsWithAMDX\0" // IR(18819, 32)
  "NodeMaxPayloadsAMDX\0" // IR(18851, 20)
  "TrackFinishWritingAMDX\0" // IR(18871, 23)
  "PayloadNodeNameAMDX\0" // IR(18894, 20)
  "PayloadNodeBaseIndexAMDX\0" // IR(18914, 25)
  "PayloadNodeSparseArrayAMDX\0" // IR(18939, 27)
  "PayloadNodeArraySizeAMDX\0" // IR(18966, 25)
  "PayloadDispatchIndirectAMDX\0" // IR(18991, 28)
  "ArrayStrideIdEXT\0" // IR(19019, 17)
  "OffsetIdEXT\0" // IR(19036, 12)
  "UTFEncodedKHR\0" // IR(19048, 14)
  "OverrideCoverageNV\0" // IR(19062, 19)
  "PassthroughNV\0" // IR(19081, 14)
  "ViewportRelativeNV\0" // IR(19095, 19)
  "SecondaryViewportRelativeNV\0" // IR(19114, 28)
  "PerPrimitiveEXT\0" // IR(19142, 16)
  "PerPrimitiveNV\0" // IR(19158, 15)
  "PerViewNV\0" // IR(19173, 10)
  "PerTaskNV\0" // IR(19183, 10)
  "PerVertexKHR\0" // IR(19193, 13)
  "PerVertexNV\0" // IR(19206, 12)
  "NonUniform\0" // IR(19218, 11)
  "NonUniformEXT\0" // IR(19229, 14)
  "RestrictPointer\0" // IR(19243, 16)
  "RestrictPointerEXT\0" // IR(19259, 19)
  "AliasedPointer\0" // IR(19278, 15)
  "AliasedPointerEXT\0" // IR(19293, 18)
  "MemberOffsetNV\0" // IR(19311, 15)
  "HitObjectShaderRecordBufferNV\0" // IR(19326, 30)
  "HitObjectShaderRecordBufferEXT\0" // IR(19356, 31)
  "BankNV\0" // IR(19387, 7)
  "BindlessSamplerNV\0" // IR(19394, 18)
  "BindlessImageNV\0" // IR(19412, 16)
  "BoundSamplerNV\0" // IR(19428, 15)
  "BoundImageNV\0" // IR(19443, 13)
  "CooperativeMatrixTransposeEXT\0" // IR(19456, 30)
  "SIMTCallINTEL\0" // IR(19486, 14)
  "ReferencedIndirectlyINTEL\0" // IR(19500, 26)
  "ClobberINTEL\0" // IR(19526, 13)
  "SideEffectsINTEL\0" // IR(19539, 17)
  "VectorComputeVariableINTEL\0" // IR(19556, 27)
  "FuncParamIOKindINTEL\0" // IR(19583, 21)
  "VectorComputeFunctionINTEL\0" // IR(19604, 27)
  "StackCallINTEL\0" // IR(19631, 15)
  "GlobalVariableOffsetINTEL\0" // IR(19646, 26)
  "CounterBuffer\0" // IR(19672, 14)
  "HlslCounterBufferGOOGLE\0" // IR(19686, 24)
  "UserSemantic\0" // IR(19710, 13)
  "HlslSemanticGOOGLE\0" // IR(19723, 19)
  "UserTypeGOOGLE\0" // IR(19742, 15)
  "FunctionRoundingModeINTEL\0" // IR(19757, 26)
  "SPV_OPERAND_TYPE_FPDENORM_MODE\0" // IR(19783, 31)
  "FunctionDenormModeINTEL\0" // IR(19814, 24)
  "RegisterALTERA\0" // IR(19838, 15)
  "RegisterINTEL\0" // IR(19853, 14)
  "MemoryALTERA\0" // IR(19867, 13)
  "MemoryINTEL\0" // IR(19880, 12)
  "NumbanksALTERA\0" // IR(19892, 15)
  "NumbanksINTEL\0" // IR(19907, 14)
  "BankwidthALTERA\0" // IR(19921, 16)
  "BankwidthINTEL\0" // IR(19937, 15)
  "MaxPrivateCopiesALTERA\0" // IR(19952, 23)
  "MaxPrivateCopiesINTEL\0" // IR(19975, 22)
  "SinglepumpALTERA\0" // IR(19997, 17)
  "SinglepumpINTEL\0" // IR(20014, 16)
  "DoublepumpALTERA\0" // IR(20030, 17)
  "DoublepumpINTEL\0" // IR(20047, 16)
  "MaxReplicatesALTERA\0" // IR(20063, 20)
  "MaxReplicatesINTEL\0" // IR(20083, 19)
  "SimpleDualPortALTERA\0" // IR(20102, 21)
  "SimpleDualPortINTEL\0" // IR(20123, 20)
  "MergeALTERA\0" // IR(20143, 12)
  "MergeINTEL\0" // IR(20155, 11)
  "SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER\0" // IR(20166, 42)
  "BankBitsALTERA\0" // IR(20208, 15)
  "BankBitsINTEL\0" // IR(20223, 14)
  "ForcePow2DepthALTERA\0" // IR(20237, 21)
  "ForcePow2DepthINTEL\0" // IR(20258, 20)
  "StridesizeALTERA\0" // IR(20278, 17)
  "StridesizeINTEL\0" // IR(20295, 16)
  "WordsizeALTERA\0" // IR(20311, 15)
  "WordsizeINTEL\0" // IR(20326, 14)
  "TrueDualPortALTERA\0" // IR(20340, 19)
  "TrueDualPortINTEL\0" // IR(20359, 18)
  "BurstCoalesceALTERA\0" // IR(20377, 20)
  "BurstCoalesceINTEL\0" // IR(20397, 19)
  "CacheSizeALTERA\0" // IR(20416, 16)
  "CacheSizeINTEL\0" // IR(20432, 15)
  "DontStaticallyCoalesceALTERA\0" // IR(20447, 29)
  "DontStaticallyCoalesceINTEL\0" // IR(20476, 28)
  "PrefetchALTERA\0" // IR(20504, 15)
  "PrefetchINTEL\0" // IR(20519, 14)
  "StallEnableALTERA\0" // IR(20533, 18)
  "StallEnableINTEL\0" // IR(20551, 17)
  "FuseLoopsInFunctionALTERA\0" // IR(20568, 26)
  "FuseLoopsInFunctionINTEL\0" // IR(20594, 25)
  "MathOpDSPModeALTERA\0" // IR(20619, 20)
  "MathOpDSPModeINTEL\0" // IR(20639, 19)
  "AliasScopeINTEL\0" // IR(20658, 16)
  "NoAliasINTEL\0" // IR(20674, 13)
  "InitiationIntervalALTERA\0" // IR(20687, 25)
  "InitiationIntervalINTEL\0" // IR(20712, 24)
  "MaxConcurrencyALTERA\0" // IR(20736, 21)
  "MaxConcurrencyINTEL\0" // IR(20757, 20)
  "PipelineEnableALTERA\0" // IR(20777, 21)
  "PipelineEnableINTEL\0" // IR(20798, 20)
  "BufferLocationALTERA\0" // IR(20818, 21)
  "BufferLocationINTEL\0" // IR(20839, 20)
  "IOPipeStorageALTERA\0" // IR(20859, 20)
  "IOPipeStorageINTEL\0" // IR(20879, 19)
  "SPV_OPERAND_TYPE_FPOPERATION_MODE\0" // IR(20898, 34)
  "FunctionFloatingPointModeINTEL\0" // IR(20932, 31)
  "SingleElementVectorINTEL\0" // IR(20963, 25)
  "VectorComputeCallableFunctionINTEL\0" // IR(20988, 35)
  "MediaBlockIOINTEL\0" // IR(21023, 18)
  "StallFreeALTERA\0" // IR(21041, 16)
  "StallFreeINTEL\0" // IR(21057, 15)
  "SPV_OPERAND_TYPE_LITERAL_FLOAT\0" // IR(21072, 31)
  "FPMaxErrorDecorationINTEL\0" // IR(21103, 26)
  "LatencyControlLabelALTERA\0" // IR(21129, 26)
  "LatencyControlLabelINTEL\0" // IR(21155, 25)
  "LatencyControlConstraintALTERA\0" // IR(21180, 31)
  "LatencyControlConstraintINTEL\0" // IR(21211, 30)
  "ConduitKernelArgumentALTERA\0" // IR(21241, 28)
  "ConduitKernelArgumentINTEL\0" // IR(21269, 27)
  "RegisterMapKernelArgumentALTERA\0" // IR(21296, 32)
  "RegisterMapKernelArgumentINTEL\0" // IR(21328, 31)
  "MMHostInterfaceAddressWidthALTERA\0" // IR(21359, 34)
  "MMHostInterfaceAddressWidthINTEL\0" // IR(21393, 33)
  "MMHostInterfaceDataWidthALTERA\0" // IR(21426, 31)
  "MMHostInterfaceDataWidthINTEL\0" // IR(21457, 30)
  "MMHostInterfaceLatencyALTERA\0" // IR(21487, 29)
  "MMHostInterfaceLatencyINTEL\0" // IR(21516, 28)
  "SPV_OPERAND_TYPE_ACCESS_QUALIFIER\0" // IR(21544, 34)
  "MMHostInterfaceReadWriteModeALTERA\0" // IR(21578, 35)
  "MMHostInterfaceReadWriteModeINTEL\0" // IR(21613, 34)
  "MMHostInterfaceMaxBurstALTERA\0" // IR(21647, 30)
  "MMHostInterfaceMaxBurstINTEL\0" // IR(21677, 29)
  "MMHostInterfaceWaitRequestALTERA\0" // IR(21706, 33)
  "MMHostInterfaceWaitRequestINTEL\0" // IR(21739, 32)
  "StableKernelArgumentALTERA\0" // IR(21771, 27)
  "StableKernelArgumentINTEL\0" // IR(21798, 26)
  "SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER\0" // IR(21824, 39)
  "HostAccessINTEL\0" // IR(21863, 16)
  "SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER\0" // IR(21879, 47)
  "InitModeALTERA\0" // IR(21926, 15)
  "InitModeINTEL\0" // IR(21941, 14)
  "ImplementInRegisterMapALTERA\0" // IR(21955, 29)
  "ImplementInRegisterMapINTEL\0" // IR(21984, 28)
  "ConditionalINTEL\0" // IR(22012, 17)
  "SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL\0" // IR(22029, 36)
  "CacheControlLoadINTEL\0" // IR(22065, 22)
  "SPV_OPERAND_TYPE_STORE_CACHE_CONTROL\0" // IR(22087, 37)
  "CacheControlStoreINTEL\0" // IR(22124, 23)
  "1D\0" // IR(22147, 3)
  "2D\0" // IR(22150, 3)
  "3D\0" // IR(22153, 3)
  "Cube\0" // IR(22156, 5)
  "Rect\0" // IR(22161, 5)
  "Buffer\0" // IR(22166, 7)
  "SubpassData\0" // IR(22173, 12)
  "TileImageDataEXT\0" // IR(22185, 17)
  "Invocations\0" // IR(22202, 12)
  "SpacingEqual\0" // IR(22214, 13)
  "SpacingFractionalEven\0" // IR(22227, 22)
  "SpacingFractionalOdd\0" // IR(22249, 21)
  "VertexOrderCw\0" // IR(22270, 14)
  "VertexOrderCcw\0" // IR(22284, 15)
  "PixelCenterInteger\0" // IR(22299, 19)
  "OriginUpperLeft\0" // IR(22318, 16)
  "OriginLowerLeft\0" // IR(22334, 16)
  "EarlyFragmentTests\0" // IR(22350, 19)
  "PointMode\0" // IR(22369, 10)
  "Xfb\0" // IR(22379, 4)
  "DepthReplacing\0" // IR(22383, 15)
  "DepthGreater\0" // IR(22398, 13)
  "DepthLess\0" // IR(22411, 10)
  "DepthUnchanged\0" // IR(22421, 15)
  "LocalSize\0" // IR(22436, 10)
  "LocalSizeHint\0" // IR(22446, 14)
  "InputPoints\0" // IR(22460, 12)
  "InputLines\0" // IR(22472, 11)
  "InputLinesAdjacency\0" // IR(22483, 20)
  "Triangles\0" // IR(22503, 10)
  "InputTrianglesAdjacency\0" // IR(22513, 24)
  "Quads\0" // IR(22537, 6)
  "Isolines\0" // IR(22543, 9)
  "OutputVertices\0" // IR(22552, 15)
  "OutputPoints\0" // IR(22567, 13)
  "OutputLineStrip\0" // IR(22580, 16)
  "OutputTriangleStrip\0" // IR(22596, 20)
  "VecTypeHint\0" // IR(22616, 12)
  "ContractionOff\0" // IR(22628, 15)
  "Initializer\0" // IR(22643, 12)
  "Finalizer\0" // IR(22655, 10)
  "SubgroupsPerWorkgroup\0" // IR(22665, 22)
  "SubgroupsPerWorkgroupId\0" // IR(22687, 24)
  "LocalSizeId\0" // IR(22711, 12)
  "LocalSizeHintId\0" // IR(22723, 16)
  "NonCoherentColorAttachmentReadEXT\0" // IR(22739, 34)
  "NonCoherentDepthAttachmentReadEXT\0" // IR(22773, 34)
  "NonCoherentStencilAttachmentReadEXT\0" // IR(22807, 36)
  "SubgroupUniformControlFlowKHR\0" // IR(22843, 30)
  "PostDepthCoverage\0" // IR(22873, 18)
  "NonCoherentTileAttachmentReadQCOM\0" // IR(22891, 34)
  "TileShadingRateQCOM\0" // IR(22925, 20)
  "SubgroupSizeHalfQCOM\0" // IR(22945, 21)
  "SubgroupSizeFullQCOM\0" // IR(22966, 21)
  "EarlyAndLateFragmentTestsAMD\0" // IR(22987, 29)
  "StencilRefReplacingEXT\0" // IR(23016, 23)
  "CoalescingAMDX\0" // IR(23039, 15)
  "IsApiEntryAMDX\0" // IR(23054, 15)
  "MaxNodeRecursionAMDX\0" // IR(23069, 21)
  "StaticNumWorkgroupsAMDX\0" // IR(23090, 24)
  "MaxNumWorkgroupsAMDX\0" // IR(23114, 21)
  "StencilRefUnchangedFrontAMD\0" // IR(23135, 28)
  "StencilRefGreaterFrontAMD\0" // IR(23163, 26)
  "StencilRefLessFrontAMD\0" // IR(23189, 23)
  "StencilRefUnchangedBackAMD\0" // IR(23212, 27)
  "StencilRefGreaterBackAMD\0" // IR(23239, 25)
  "StencilRefLessBackAMD\0" // IR(23264, 22)
  "QuadDerivativesKHR\0" // IR(23286, 19)
  "RequireFullQuadsKHR\0" // IR(23305, 20)
  "SharesInputWithAMDX\0" // IR(23325, 20)
  "ArithmeticPoisonKHR\0" // IR(23345, 20)
  "OutputLinesEXT\0" // IR(23365, 15)
  "OutputLinesNV\0" // IR(23380, 14)
  "OutputPrimitivesEXT\0" // IR(23394, 20)
  "OutputPrimitivesNV\0" // IR(23414, 19)
  "DerivativeGroupQuadsKHR\0" // IR(23433, 24)
  "DerivativeGroupQuadsNV\0" // IR(23457, 23)
  "DerivativeGroupLinearKHR\0" // IR(23480, 25)
  "DerivativeGroupLinearNV\0" // IR(23505, 24)
  "OutputTrianglesEXT\0" // IR(23529, 19)
  "OutputTrianglesNV\0" // IR(23548, 18)
  "PixelInterlockOrderedEXT\0" // IR(23566, 25)
  "PixelInterlockUnorderedEXT\0" // IR(23591, 27)
  "SampleInterlockOrderedEXT\0" // IR(23618, 26)
  "SampleInterlockUnorderedEXT\0" // IR(23644, 28)
  "ShadingRateInterlockOrderedEXT\0" // IR(23672, 31)
  "ShadingRateInterlockUnorderedEXT\0" // IR(23703, 33)
  "SharedLocalMemorySizeINTEL\0" // IR(23736, 27)
  "RoundingModeRTPINTEL\0" // IR(23763, 21)
  "RoundingModeRTNINTEL\0" // IR(23784, 21)
  "FloatingPointModeALTINTEL\0" // IR(23805, 26)
  "FloatingPointModeIEEEINTEL\0" // IR(23831, 27)
  "MaxWorkgroupSizeINTEL\0" // IR(23858, 22)
  "MaxWorkDimINTEL\0" // IR(23880, 16)
  "NoGlobalOffsetINTEL\0" // IR(23896, 20)
  "NumSIMDWorkitemsINTEL\0" // IR(23916, 22)
  "SchedulerTargetFmaxMhzINTEL\0" // IR(23938, 28)
  "MaximallyReconvergesKHR\0" // IR(23966, 24)
  "FPFastMathDefault\0" // IR(23990, 18)
  "OpacityMicromapIdKHR\0" // IR(24008, 21)
  "StreamingInterfaceINTEL\0" // IR(24029, 24)
  "RegisterMapInterfaceINTEL\0" // IR(24053, 26)
  "NamedBarrierCountINTEL\0" // IR(24079, 23)
  "MaximumRegistersINTEL\0" // IR(24102, 22)
  "MaximumRegistersIdINTEL\0" // IR(24124, 24)
  "SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS\0" // IR(24148, 51)
  "NamedMaximumRegistersINTEL\0" // IR(24199, 27)
  "Vertex\0" // IR(24226, 7)
  "TessellationControl\0" // IR(24233, 20)
  "TessellationEvaluation\0" // IR(24253, 23)
  "GLCompute\0" // IR(24276, 10)
  "TaskNV\0" // IR(24286, 7)
  "MeshNV\0" // IR(24293, 7)
  "RayGenerationKHR\0" // IR(24300, 17)
  "RayGenerationNV\0" // IR(24317, 16)
  "IntersectionKHR\0" // IR(24333, 16)
  "IntersectionNV\0" // IR(24349, 15)
  "AnyHitKHR\0" // IR(24364, 10)
  "AnyHitNV\0" // IR(24374, 9)
  "ClosestHitKHR\0" // IR(24383, 14)
  "ClosestHitNV\0" // IR(24397, 13)
  "MissKHR\0" // IR(24410, 8)
  "MissNV\0" // IR(24418, 7)
  "CallableKHR\0" // IR(24425, 12)
  "CallableNV\0" // IR(24437, 11)
  "TaskEXT\0" // IR(24448, 8)
  "MeshEXT\0" // IR(24456, 8)
  "Preserve\0" // IR(24464, 9)
  "FlushToZero\0" // IR(24473, 12)
  "BFloat16KHR\0" // IR(24485, 12)
  "Float8E4M3EXT\0" // IR(24497, 14)
  "Float8E5M2EXT\0" // IR(24511, 14)
  "Float6E2M3EXT\0" // IR(24525, 14)
  "Float6E3M2EXT\0" // IR(24539, 14)
  "Float4E2M1EXT\0" // IR(24553, 14)
  "IEEE\0" // IR(24567, 5)
  "ALT\0" // IR(24572, 4)
  "NotNaN\0" // IR(24576, 7)
  "NotInf\0" // IR(24583, 7)
  "NSZ\0" // IR(24590, 4)
  "AllowRecip\0" // IR(24594, 11)
  "Fast\0" // IR(24605, 5)
  "AllowContract\0" // IR(24610, 14)
  "AllowContractFastINTEL\0" // IR(24624, 23)
  "AllowReassoc\0" // IR(24647, 13)
  "AllowReassocINTEL\0" // IR(24660, 18)
  "AllowTransform\0" // IR(24678, 15)
  "RTE\0" // IR(24693, 4)
  "RTZ\0" // IR(24697, 4)
  "RTP\0" // IR(24701, 4)
  "RTN\0" // IR(24705, 4)
  "Vertical2Pixels\0" // IR(24709, 16)
  "Vertical4Pixels\0" // IR(24725, 16)
  "Horizontal2Pixels\0" // IR(24741, 18)
  "Horizontal4Pixels\0" // IR(24759, 18)
  "Inline\0" // IR(24777, 7)
  "DontInline\0" // IR(24784, 11)
  "Pure\0" // IR(24795, 5)
  "Const\0" // IR(24800, 6)
  "Zext\0" // IR(24806, 5)
  "Sext\0" // IR(24811, 5)
  "ByVal\0" // IR(24816, 6)
  "Sret\0" // IR(24822, 5)
  "NoAlias\0" // IR(24827, 8)
  "NoCapture\0" // IR(24835, 10)
  "NoWrite\0" // IR(24845, 8)
  "NoReadWrite\0" // IR(24853, 12)
  "RuntimeAlignedALTERA\0" // IR(24865, 21)
  "RuntimeAlignedINTEL\0" // IR(24886, 20)
  "Gather4x1QCOM\0" // IR(24906, 14)
  "GatherDQCOM\0" // IR(24920, 12)
  "GatherH2QCOM\0" // IR(24932, 13)
  "GatherV2QCOM\0" // IR(24945, 13)
  "Reduce\0" // IR(24958, 7)
  "InclusiveScan\0" // IR(24965, 14)
  "ExclusiveScan\0" // IR(24979, 14)
  "ClusteredReduce\0" // IR(24993, 16)
  "PartitionedReduceEXT\0" // IR(25009, 21)
  "PartitionedReduceNV\0" // IR(25030, 20)
  "PartitionedInclusiveScanEXT\0" // IR(25050, 28)
  "PartitionedInclusiveScanNV\0" // IR(25078, 27)
  "PartitionedExclusiveScanEXT\0" // IR(25105, 28)
  "PartitionedExclusiveScanNV\0" // IR(25133, 27)
  "NoneINTEL\0" // IR(25160, 10)
  "ReadINTEL\0" // IR(25170, 10)
  "WriteINTEL\0" // IR(25180, 11)
  "ReadWriteINTEL\0" // IR(25191, 15)
  "Bias\0" // IR(25206, 5)
  "Lod\0" // IR(25211, 4)
  "Grad\0" // IR(25215, 5)
  "ConstOffset\0" // IR(25220, 12)
  "ConstOffsets\0" // IR(25232, 13)
  "MakeTexelAvailable\0" // IR(25245, 19)
  "MakeTexelAvailableKHR\0" // IR(25264, 22)
  "MakeTexelVisible\0" // IR(25286, 17)
  "MakeTexelVisibleKHR\0" // IR(25303, 20)
  "NonPrivateTexel\0" // IR(25323, 16)
  "NonPrivateTexelKHR\0" // IR(25339, 19)
  "VolatileTexel\0" // IR(25358, 14)
  "VolatileTexelKHR\0" // IR(25372, 17)
  "SignExtend\0" // IR(25389, 11)
  "ZeroExtend\0" // IR(25400, 11)
  "Nontemporal\0" // IR(25411, 12)
  "Offsets\0" // IR(25423, 8)
  "SnormInt8\0" // IR(25431, 10)
  "SnormInt16\0" // IR(25441, 11)
  "UnormInt8\0" // IR(25452, 10)
  "UnormInt16\0" // IR(25462, 11)
  "UnormShort565\0" // IR(25473, 14)
  "UnormShort555\0" // IR(25487, 14)
  "UnormInt101010\0" // IR(25501, 15)
  "SignedInt8\0" // IR(25516, 11)
  "SignedInt16\0" // IR(25527, 12)
  "SignedInt32\0" // IR(25539, 12)
  "UnsignedInt8\0" // IR(25551, 13)
  "UnsignedInt16\0" // IR(25564, 14)
  "UnsignedInt32\0" // IR(25578, 14)
  "HalfFloat\0" // IR(25592, 10)
  "UnormInt24\0" // IR(25602, 11)
  "UnormInt101010_2\0" // IR(25613, 17)
  "UnormInt10X6EXT\0" // IR(25630, 16)
  "UnsignedIntRaw10EXT\0" // IR(25646, 20)
  "UnsignedIntRaw12EXT\0" // IR(25666, 20)
  "UnormInt2_101010EXT\0" // IR(25686, 20)
  "UnsignedInt10X6EXT\0" // IR(25706, 19)
  "UnsignedInt12X4EXT\0" // IR(25725, 19)
  "UnsignedInt14X2EXT\0" // IR(25744, 19)
  "UnormInt12X4EXT\0" // IR(25763, 16)
  "UnormInt14X2EXT\0" // IR(25779, 16)
  "R\0" // IR(25795, 2)
  "A\0" // IR(25797, 2)
  "RG\0" // IR(25799, 3)
  "RA\0" // IR(25802, 3)
  "RGB\0" // IR(25805, 4)
  "RGBA\0" // IR(25809, 5)
  "BGRA\0" // IR(25814, 5)
  "ARGB\0" // IR(25819, 5)
  "Intensity\0" // IR(25824, 10)
  "Luminance\0" // IR(25834, 10)
  "Rx\0" // IR(25844, 3)
  "RGx\0" // IR(25847, 4)
  "RGBx\0" // IR(25851, 5)
  "Depth\0" // IR(25856, 6)
  "DepthStencil\0" // IR(25862, 13)
  "sRGB\0" // IR(25875, 5)
  "sRGBx\0" // IR(25880, 6)
  "sRGBA\0" // IR(25886, 6)
  "sBGRA\0" // IR(25892, 6)
  "ABGR\0" // IR(25898, 5)
  "InitOnDeviceReprogramALTERA\0" // IR(25903, 28)
  "InitOnDeviceReprogramINTEL\0" // IR(25931, 27)
  "InitOnDeviceResetALTERA\0" // IR(25958, 24)
  "InitOnDeviceResetINTEL\0" // IR(25982, 23)
  "NoWait\0" // IR(26005, 7)
  "WaitKernel\0" // IR(26012, 11)
  "WaitWorkGroup\0" // IR(26023, 14)
  "CmdExecTime\0" // IR(26037, 12)
  "MayUsePrintf\0" // IR(26049, 13)
  "Export\0" // IR(26062, 7)
  "Import\0" // IR(26069, 7)
  "LinkOnceODR\0" // IR(26076, 12)
  "WeakAMD\0" // IR(26088, 8)
  "UncachedINTEL\0" // IR(26096, 14)
  "CachedINTEL\0" // IR(26110, 12)
  "StreamingINTEL\0" // IR(26122, 15)
  "InvalidateAfterReadINTEL\0" // IR(26137, 25)
  "ConstCachedINTEL\0" // IR(26162, 17)
  "Unroll\0" // IR(26179, 7)
  "DontUnroll\0" // IR(26186, 11)
  "DependencyInfinite\0" // IR(26197, 19)
  "DependencyLength\0" // IR(26216, 17)
  "MinIterations\0" // IR(26233, 14)
  "MaxIterations\0" // IR(26247, 14)
  "IterationMultiple\0" // IR(26261, 18)
  "PeelCount\0" // IR(26279, 10)
  "PartialCount\0" // IR(26289, 13)
  "DependencyArrayALTERA\0" // IR(26302, 22)
  "DependencyArrayINTEL\0" // IR(26324, 21)
  "LoopCoalesceALTERA\0" // IR(26345, 19)
  "LoopCoalesceINTEL\0" // IR(26364, 18)
  "MaxInterleavingALTERA\0" // IR(26382, 22)
  "MaxInterleavingINTEL\0" // IR(26404, 21)
  "SpeculatedIterationsALTERA\0" // IR(26425, 27)
  "SpeculatedIterationsINTEL\0" // IR(26452, 26)
  "NoFusionALTERA\0" // IR(26478, 15)
  "NoFusionINTEL\0" // IR(26493, 14)
  "LoopCountALTERA\0" // IR(26507, 16)
  "LoopCountINTEL\0" // IR(26523, 15)
  "MaxReinvocationDelayALTERA\0" // IR(26538, 27)
  "MaxReinvocationDelayINTEL\0" // IR(26565, 26)
  "MatrixASignedComponentsINTEL\0" // IR(26591, 29)
  "MatrixBSignedComponentsINTEL\0" // IR(26620, 29)
  "MatrixCBFloat16INTEL\0" // IR(26649, 21)
  "MatrixResultBFloat16INTEL\0" // IR(26670, 26)
  "MatrixAPackedInt8INTEL\0" // IR(26696, 23)
  "MatrixBPackedInt8INTEL\0" // IR(26719, 23)
  "MatrixAPackedInt4INTEL\0" // IR(26742, 23)
  "MatrixBPackedInt4INTEL\0" // IR(26765, 23)
  "MatrixATF32INTEL\0" // IR(26788, 17)
  "MatrixBTF32INTEL\0" // IR(26805, 17)
  "MatrixAPackedFloat16INTEL\0" // IR(26822, 26)
  "MatrixBPackedFloat16INTEL\0" // IR(26848, 26)
  "MatrixAPackedBFloat16INTEL\0" // IR(26874, 27)
  "MatrixBPackedBFloat16INTEL\0" // IR(26901, 27)
  "Aligned\0" // IR(26928, 8)
  "MakePointerAvailable\0" // IR(26936, 21)
  "MakePointerAvailableKHR\0" // IR(26957, 24)
  "MakePointerVisible\0" // IR(26981, 19)
  "MakePointerVisibleKHR\0" // IR(27000, 22)
  "NonPrivatePointer\0" // IR(27022, 18)
  "NonPrivatePointerKHR\0" // IR(27040, 21)
  "AliasScopeINTELMask\0" // IR(27061, 20)
  "NoAliasINTELMask\0" // IR(27081, 17)
  "Simple\0" // IR(27098, 7)
  "GLSL450\0" // IR(27105, 8)
  "OpenCL\0" // IR(27113, 7)
  "Vulkan\0" // IR(27120, 7)
  "VulkanKHR\0" // IR(27127, 10)
  "Relaxed\0" // IR(27137, 8)
  "Acquire\0" // IR(27145, 8)
  "Release\0" // IR(27153, 8)
  "AcquireRelease\0" // IR(27161, 15)
  "SequentiallyConsistent\0" // IR(27176, 23)
  "UniformMemory\0" // IR(27199, 14)
  "SubgroupMemory\0" // IR(27213, 15)
  "WorkgroupMemory\0" // IR(27228, 16)
  "CrossWorkgroupMemory\0" // IR(27244, 21)
  "AtomicCounterMemory\0" // IR(27265, 20)
  "ImageMemory\0" // IR(27285, 12)
  "OutputMemory\0" // IR(27297, 13)
  "OutputMemoryKHR\0" // IR(27310, 16)
  "MakeAvailable\0" // IR(27326, 14)
  "MakeAvailableKHR\0" // IR(27340, 17)
  "MakeVisible\0" // IR(27357, 12)
  "MakeVisibleKHR\0" // IR(27369, 15)
  "AutoINTEL\0" // IR(27384, 10)
  "WRAP\0" // IR(27394, 5)
  "SAT\0" // IR(27399, 4)
  "SAT_ZERO\0" // IR(27403, 9)
  "SAT_SYM\0" // IR(27412, 8)
  "PackedVectorFormat4x8Bit\0" // IR(27420, 25)
  "PackedVectorFormat4x8BitKHR\0" // IR(27445, 28)
  "TRN\0" // IR(27473, 4)
  "TRN_ZERO\0" // IR(27477, 9)
  "RND\0" // IR(27486, 4)
  "RND_ZERO\0" // IR(27490, 9)
  "RND_INF\0" // IR(27499, 8)
  "RND_MIN_INF\0" // IR(27507, 12)
  "RND_CONV\0" // IR(27519, 9)
  "RND_CONV_ODD\0" // IR(27528, 13)
  "RobustnessPerComponentNV\0" // IR(27541, 25)
  "RobustnessPerElementNV\0" // IR(27566, 23)
  "OpaqueKHR\0" // IR(27589, 10)
  "NoOpaqueKHR\0" // IR(27599, 12)
  "TerminateOnFirstHitKHR\0" // IR(27611, 23)
  "SkipClosestHitShaderKHR\0" // IR(27634, 24)
  "CullBackFacingTrianglesKHR\0" // IR(27658, 27)
  "CullFrontFacingTrianglesKHR\0" // IR(27685, 28)
  "CullOpaqueKHR\0" // IR(27713, 14)
  "CullNoOpaqueKHR\0" // IR(27727, 16)
  "SkipTrianglesKHR\0" // IR(27743, 17)
  "SkipBuiltinPrimitivesNV\0" // IR(27760, 24)
  "SkipAABBsKHR\0" // IR(27784, 13)
  "ForceOpacityMicromap2StateKHR\0" // IR(27797, 30)
  "ForceOpacityMicromap2StateEXT\0" // IR(27827, 30)
  "RayQueryCandidateIntersectionTriangleKHR\0" // IR(27857, 41)
  "RayQueryCandidateIntersectionAABBKHR\0" // IR(27898, 37)
  "RayQueryCommittedIntersectionNoneKHR\0" // IR(27935, 37)
  "RayQueryCommittedIntersectionTriangleKHR\0" // IR(27972, 41)
  "RayQueryCommittedIntersectionGeneratedKHR\0" // IR(28013, 42)
  "RayQueryCandidateIntersectionKHR\0" // IR(28055, 33)
  "RayQueryCommittedIntersectionKHR\0" // IR(28088, 33)
  "ClampToEdge\0" // IR(28121, 12)
  "Clamp\0" // IR(28133, 6)
  "Repeat\0" // IR(28139, 7)
  "RepeatMirrored\0" // IR(28146, 15)
  "Nearest\0" // IR(28161, 8)
  "Linear\0" // IR(28169, 7)
  "Unknown\0" // IR(28176, 8)
  "Rgba32f\0" // IR(28184, 8)
  "Rgba16f\0" // IR(28192, 8)
  "R32f\0" // IR(28200, 5)
  "Rgba8\0" // IR(28205, 6)
  "Rgba8Snorm\0" // IR(28211, 11)
  "Rg32f\0" // IR(28222, 6)
  "Rg16f\0" // IR(28228, 6)
  "R11fG11fB10f\0" // IR(28234, 13)
  "R16f\0" // IR(28247, 5)
  "Rgba16\0" // IR(28252, 7)
  "Rgb10A2\0" // IR(28259, 8)
  "Rg16\0" // IR(28267, 5)
  "Rg8\0" // IR(28272, 4)
  "R16\0" // IR(28276, 4)
  "R8\0" // IR(28280, 3)
  "Rgba16Snorm\0" // IR(28283, 12)
  "Rg16Snorm\0" // IR(28295, 10)
  "Rg8Snorm\0" // IR(28305, 9)
  "R16Snorm\0" // IR(28314, 9)
  "R8Snorm\0" // IR(28323, 8)
  "Rgba32i\0" // IR(28331, 8)
  "Rgba16i\0" // IR(28339, 8)
  "Rgba8i\0" // IR(28347, 7)
  "R32i\0" // IR(28354, 5)
  "Rg32i\0" // IR(28359, 6)
  "Rg16i\0" // IR(28365, 6)
  "Rg8i\0" // IR(28371, 5)
  "R16i\0" // IR(28376, 5)
  "R8i\0" // IR(28381, 4)
  "Rgba32ui\0" // IR(28385, 9)
  "Rgba16ui\0" // IR(28394, 9)
  "Rgba8ui\0" // IR(28403, 8)
  "R32ui\0" // IR(28411, 6)
  "Rgb10a2ui\0" // IR(28417, 10)
  "Rg32ui\0" // IR(28427, 7)
  "Rg16ui\0" // IR(28434, 7)
  "Rg8ui\0" // IR(28441, 6)
  "R16ui\0" // IR(28447, 6)
  "R8ui\0" // IR(28453, 5)
  "R64ui\0" // IR(28458, 6)
  "R64i\0" // IR(28464, 5)
  "CrossDevice\0" // IR(28469, 12)
  "Device\0" // IR(28481, 7)
  "Workgroup\0" // IR(28488, 10)
  "Subgroup\0" // IR(28498, 9)
  "Invocation\0" // IR(28507, 11)
  "QueueFamily\0" // IR(28518, 12)
  "QueueFamilyKHR\0" // IR(28530, 15)
  "ShaderCallKHR\0" // IR(28545, 14)
  "Flatten\0" // IR(28559, 8)
  "DontFlatten\0" // IR(28567, 12)
  "IdentifierPossibleDuplicates\0" // IR(28579, 29)
  "FlagUnknownPhysicalLayout\0" // IR(28608, 26)
  "ESSL\0" // IR(28634, 5)
  "GLSL\0" // IR(28639, 5)
  "OpenCL_C\0" // IR(28644, 9)
  "OpenCL_CPP\0" // IR(28653, 11)
  "HLSL\0" // IR(28664, 5)
  "CPP_for_OpenCL\0" // IR(28669, 15)
  "SYCL\0" // IR(28684, 5)
  "HERO_C\0" // IR(28689, 7)
  "NZSL\0" // IR(28696, 5)
  "WGSL\0" // IR(28701, 5)
  "Slang\0" // IR(28706, 6)
  "Zig\0" // IR(28712, 4)
  "Rust\0" // IR(28716, 5)
  "Pred\0" // IR(28721, 5)
  "ApilaJai\0" // IR(28726, 9)
  "UniformConstant\0" // IR(28735, 16)
  "Input\0" // IR(28751, 6)
  "Output\0" // IR(28757, 7)
  "CrossWorkgroup\0" // IR(28764, 15)
  "Private\0" // IR(28779, 8)
  "Function\0" // IR(28787, 9)
  "Generic\0" // IR(28796, 8)
  "PushConstant\0" // IR(28804, 13)
  "AtomicCounter\0" // IR(28817, 14)
  "Image\0" // IR(28831, 6)
  "StorageBuffer\0" // IR(28837, 14)
  "TileImageEXT\0" // IR(28851, 13)
  "TileAttachmentQCOM\0" // IR(28864, 19)
  "NodePayloadAMDX\0" // IR(28883, 16)
  "CallableDataKHR\0" // IR(28899, 16)
  "CallableDataNV\0" // IR(28915, 15)
  "IncomingCallableDataKHR\0" // IR(28930, 24)
  "IncomingCallableDataNV\0" // IR(28954, 23)
  "RayPayloadKHR\0" // IR(28977, 14)
  "RayPayloadNV\0" // IR(28991, 13)
  "HitAttributeKHR\0" // IR(29004, 16)
  "HitAttributeNV\0" // IR(29020, 15)
  "IncomingRayPayloadKHR\0" // IR(29035, 22)
  "IncomingRayPayloadNV\0" // IR(29057, 21)
  "ShaderRecordBufferKHR\0" // IR(29078, 22)
  "ShaderRecordBufferNV\0" // IR(29100, 21)
  "PhysicalStorageBuffer\0" // IR(29121, 22)
  "PhysicalStorageBufferEXT\0" // IR(29143, 25)
  "HitObjectAttributeNV\0" // IR(29168, 21)
  "TaskPayloadWorkgroupEXT\0" // IR(29189, 24)
  "HitObjectAttributeEXT\0" // IR(29213, 22)
  "CodeSectionINTEL\0" // IR(29235, 17)
  "DeviceOnlyALTERA\0" // IR(29252, 17)
  "DeviceOnlyINTEL\0" // IR(29269, 16)
  "HostOnlyALTERA\0" // IR(29285, 15)
  "HostOnlyINTEL\0" // IR(29300, 14)
  "WriteThroughINTEL\0" // IR(29314, 18)
  "WriteBackINTEL\0" // IR(29332, 15)
  "TensorView\0" // IR(29347, 11)
  "DecodeFunc\0" // IR(29358, 11)
  "DecodeVectorFunc\0" // IR(29369, 17)
  "Undefined\0" // IR(29386, 10)
  "NoneARM\0" // IR(29396, 8)
  "NontemporalARM\0" // IR(29404, 15)
  "OutOfBoundsValueARM\0" // IR(29419, 20)
  "MakeElementAvailableARM\0" // IR(29439, 24)
  "MakeElementVisibleARM\0" // IR(29463, 22)
  "NonPrivateElementARM\0" // IR(29485, 21)
  "Nop\0" // IR(29506, 4)
  "SPV_OPERAND_TYPE_TYPE_ID\0" // IR(29510, 25)
  "SPV_OPERAND_TYPE_RESULT_ID\0" // IR(29535, 27)
  "Undef\0" // IR(29562, 6)
  "SourceContinued\0" // IR(29568, 16)
  "SPV_OPERAND_TYPE_SOURCE_LANGUAGE\0" // IR(29584, 33)
  "SPV_OPERAND_TYPE_OPTIONAL_ID\0" // IR(29617, 29)
  "SPV_OPERAND_TYPE_OPTIONAL_LITERAL_STRING\0" // IR(29646, 41)
  "Source\0" // IR(29687, 7)
  "SourceExtension\0" // IR(29694, 16)
  "Name\0" // IR(29710, 5)
  "MemberName\0" // IR(29715, 11)
  "String\0" // IR(29726, 7)
  "Line\0" // IR(29733, 5)
  "Extension\0" // IR(29738, 10)
  "ExtInstImport\0" // IR(29748, 14)
  "SPV_OPERAND_TYPE_EXTENSION_INSTRUCTION_NUMBER\0" // IR(29762, 46)
  "ExtInst\0" // IR(29808, 8)
  "SPV_OPERAND_TYPE_ADDRESSING_MODEL\0" // IR(29816, 34)
  "SPV_OPERAND_TYPE_MEMORY_MODEL\0" // IR(29850, 30)
  "MemoryModel\0" // IR(29880, 12)
  "SPV_OPERAND_TYPE_EXECUTION_MODEL\0" // IR(29892, 33)
  "SPV_OPERAND_TYPE_VARIABLE_ID\0" // IR(29925, 29)
  "EntryPoint\0" // IR(29954, 11)
  "SPV_OPERAND_TYPE_EXECUTION_MODE\0" // IR(29965, 32)
  "ExecutionMode\0" // IR(29997, 14)
  "SPV_OPERAND_TYPE_CAPABILITY\0" // IR(30011, 28)
  "Capability\0" // IR(30039, 11)
  "TypeVoid\0" // IR(30050, 9)
  "TypeBool\0" // IR(30059, 9)
  "TypeInt\0" // IR(30068, 8)
  "SPV_OPERAND_TYPE_OPTIONAL_FPENCODING\0" // IR(30076, 37)
  "TypeFloat\0" // IR(30113, 10)
  "TypeVector\0" // IR(30123, 11)
  "TypeMatrix\0" // IR(30134, 11)
  "SPV_OPERAND_TYPE_DIMENSIONALITY\0" // IR(30145, 32)
  "SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT\0" // IR(30177, 38)
  "SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER\0" // IR(30215, 43)
  "TypeImage\0" // IR(30258, 10)
  "TypeSampler\0" // IR(30268, 12)
  "TypeSampledImage\0" // IR(30280, 17)
  "TypeArray\0" // IR(30297, 10)
  "TypeRuntimeArray\0" // IR(30307, 17)
  "TypeStruct\0" // IR(30324, 11)
  "TypeOpaque\0" // IR(30335, 11)
  "SPV_OPERAND_TYPE_STORAGE_CLASS\0" // IR(30346, 31)
  "TypePointer\0" // IR(30377, 12)
  "TypeFunction\0" // IR(30389, 13)
  "TypeEvent\0" // IR(30402, 10)
  "TypeDeviceEvent\0" // IR(30412, 16)
  "TypeReserveId\0" // IR(30428, 14)
  "TypeQueue\0" // IR(30442, 10)
  "TypePipe\0" // IR(30452, 9)
  "TypeForwardPointer\0" // IR(30461, 19)
  "ConstantTrue\0" // IR(30480, 13)
  "ConstantFalse\0" // IR(30493, 14)
  "SPV_OPERAND_TYPE_TYPED_LITERAL_NUMBER\0" // IR(30507, 38)
  "ConstantComposite\0" // IR(30545, 18)
  "SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE\0" // IR(30563, 41)
  "SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE\0" // IR(30604, 37)
  "ConstantSampler\0" // IR(30641, 16)
  "ConstantNull\0" // IR(30657, 13)
  "SpecConstantTrue\0" // IR(30670, 17)
  "SpecConstantFalse\0" // IR(30687, 18)
  "SpecConstant\0" // IR(30705, 13)
  "SpecConstantComposite\0" // IR(30718, 22)
  "SPV_OPERAND_TYPE_SPEC_CONSTANT_OP_NUMBER\0" // IR(30740, 41)
  "SpecConstantOp\0" // IR(30781, 15)
  "SPV_OPERAND_TYPE_FUNCTION_CONTROL\0" // IR(30796, 34)
  "FunctionParameter\0" // IR(30830, 18)
  "FunctionEnd\0" // IR(30848, 12)
  "FunctionCall\0" // IR(30860, 13)
  "Variable\0" // IR(30873, 9)
  "ImageTexelPointer\0" // IR(30882, 18)
  "SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS\0" // IR(30900, 40)
  "Load\0" // IR(30940, 5)
  "Store\0" // IR(30945, 6)
  "CopyMemory\0" // IR(30951, 11)
  "CopyMemorySized\0" // IR(30962, 16)
  "AccessChain\0" // IR(30978, 12)
  "InBoundsAccessChain\0" // IR(30990, 20)
  "PtrAccessChain\0" // IR(31010, 15)
  "ArrayLength\0" // IR(31025, 12)
  "GenericPtrMemSemantics\0" // IR(31037, 23)
  "InBoundsPtrAccessChain\0" // IR(31060, 23)
  "SPV_OPERAND_TYPE_DECORATION\0" // IR(31083, 28)
  "Decorate\0" // IR(31111, 9)
  "MemberDecorate\0" // IR(31120, 15)
  "DecorationGroup\0" // IR(31135, 16)
  "GroupDecorate\0" // IR(31151, 14)
  "SPV_OPERAND_TYPE_VARIABLE_ID_LITERAL_INTEGER\0" // IR(31165, 45)
  "GroupMemberDecorate\0" // IR(31210, 20)
  "VectorExtractDynamic\0" // IR(31230, 21)
  "VectorInsertDynamic\0" // IR(31251, 20)
  "VectorShuffle\0" // IR(31271, 14)
  "CompositeConstruct\0" // IR(31285, 19)
  "CompositeExtract\0" // IR(31304, 17)
  "CompositeInsert\0" // IR(31321, 16)
  "CopyObject\0" // IR(31337, 11)
  "Transpose\0" // IR(31348, 10)
  "SampledImage\0" // IR(31358, 13)
  "SPV_OPERAND_TYPE_OPTIONAL_IMAGE\0" // IR(31371, 32)
  "ImageSampleImplicitLod\0" // IR(31403, 23)
  "SPV_OPERAND_TYPE_IMAGE\0" // IR(31426, 23)
  "ImageSampleExplicitLod\0" // IR(31449, 23)
  "ImageSampleDrefImplicitLod\0" // IR(31472, 27)
  "ImageSampleDrefExplicitLod\0" // IR(31499, 27)
  "ImageSampleProjImplicitLod\0" // IR(31526, 27)
  "ImageSampleProjExplicitLod\0" // IR(31553, 27)
  "ImageSampleProjDrefImplicitLod\0" // IR(31580, 31)
  "ImageSampleProjDrefExplicitLod\0" // IR(31611, 31)
  "ImageFetch\0" // IR(31642, 11)
  "ImageGather\0" // IR(31653, 12)
  "ImageDrefGather\0" // IR(31665, 16)
  "ImageRead\0" // IR(31681, 10)
  "ImageWrite\0" // IR(31691, 11)
  "ImageQueryFormat\0" // IR(31702, 17)
  "ImageQueryOrder\0" // IR(31719, 16)
  "ImageQuerySizeLod\0" // IR(31735, 18)
  "ImageQuerySize\0" // IR(31753, 15)
  "ImageQueryLod\0" // IR(31768, 14)
  "ImageQueryLevels\0" // IR(31782, 17)
  "ImageQuerySamples\0" // IR(31799, 18)
  "ConvertFToU\0" // IR(31817, 12)
  "ConvertFToS\0" // IR(31829, 12)
  "ConvertSToF\0" // IR(31841, 12)
  "ConvertUToF\0" // IR(31853, 12)
  "UConvert\0" // IR(31865, 9)
  "SConvert\0" // IR(31874, 9)
  "FConvert\0" // IR(31883, 9)
  "QuantizeToF16\0" // IR(31892, 14)
  "ConvertPtrToU\0" // IR(31906, 14)
  "SatConvertSToU\0" // IR(31920, 15)
  "SatConvertUToS\0" // IR(31935, 15)
  "ConvertUToPtr\0" // IR(31950, 14)
  "PtrCastToGeneric\0" // IR(31964, 17)
  "GenericCastToPtr\0" // IR(31981, 17)
  "GenericCastToPtrExplicit\0" // IR(31998, 25)
  "Bitcast\0" // IR(32023, 8)
  "SNegate\0" // IR(32031, 8)
  "FNegate\0" // IR(32039, 8)
  "IAdd\0" // IR(32047, 5)
  "FAdd\0" // IR(32052, 5)
  "ISub\0" // IR(32057, 5)
  "FSub\0" // IR(32062, 5)
  "IMul\0" // IR(32067, 5)
  "FMul\0" // IR(32072, 5)
  "UDiv\0" // IR(32077, 5)
  "SDiv\0" // IR(32082, 5)
  "FDiv\0" // IR(32087, 5)
  "UMod\0" // IR(32092, 5)
  "SRem\0" // IR(32097, 5)
  "SMod\0" // IR(32102, 5)
  "FRem\0" // IR(32107, 5)
  "FMod\0" // IR(32112, 5)
  "VectorTimesScalar\0" // IR(32117, 18)
  "MatrixTimesScalar\0" // IR(32135, 18)
  "VectorTimesMatrix\0" // IR(32153, 18)
  "MatrixTimesVector\0" // IR(32171, 18)
  "MatrixTimesMatrix\0" // IR(32189, 18)
  "OuterProduct\0" // IR(32207, 13)
  "Dot\0" // IR(32220, 4)
  "IAddCarry\0" // IR(32224, 10)
  "ISubBorrow\0" // IR(32234, 11)
  "UMulExtended\0" // IR(32245, 13)
  "SMulExtended\0" // IR(32258, 13)
  "Any\0" // IR(32271, 4)
  "All\0" // IR(32275, 4)
  "IsNan\0" // IR(32279, 6)
  "IsInf\0" // IR(32285, 6)
  "IsFinite\0" // IR(32291, 9)
  "IsNormal\0" // IR(32300, 9)
  "SignBitSet\0" // IR(32309, 11)
  "LessOrGreater\0" // IR(32320, 14)
  "Ordered\0" // IR(32334, 8)
  "Unordered\0" // IR(32342, 10)
  "LogicalEqual\0" // IR(32352, 13)
  "LogicalNotEqual\0" // IR(32365, 16)
  "LogicalOr\0" // IR(32381, 10)
  "LogicalAnd\0" // IR(32391, 11)
  "LogicalNot\0" // IR(32402, 11)
  "Select\0" // IR(32413, 7)
  "IEqual\0" // IR(32420, 7)
  "INotEqual\0" // IR(32427, 10)
  "UGreaterThan\0" // IR(32437, 13)
  "SGreaterThan\0" // IR(32450, 13)
  "UGreaterThanEqual\0" // IR(32463, 18)
  "SGreaterThanEqual\0" // IR(32481, 18)
  "ULessThan\0" // IR(32499, 10)
  "SLessThan\0" // IR(32509, 10)
  "ULessThanEqual\0" // IR(32519, 15)
  "SLessThanEqual\0" // IR(32534, 15)
  "FOrdEqual\0" // IR(32549, 10)
  "FUnordEqual\0" // IR(32559, 12)
  "FOrdNotEqual\0" // IR(32571, 13)
  "FUnordNotEqual\0" // IR(32584, 15)
  "FOrdLessThan\0" // IR(32599, 13)
  "FUnordLessThan\0" // IR(32612, 15)
  "FOrdGreaterThan\0" // IR(32627, 16)
  "FUnordGreaterThan\0" // IR(32643, 18)
  "FOrdLessThanEqual\0" // IR(32661, 18)
  "FUnordLessThanEqual\0" // IR(32679, 20)
  "FOrdGreaterThanEqual\0" // IR(32699, 21)
  "FUnordGreaterThanEqual\0" // IR(32720, 23)
  "ShiftRightLogical\0" // IR(32743, 18)
  "ShiftRightArithmetic\0" // IR(32761, 21)
  "ShiftLeftLogical\0" // IR(32782, 17)
  "BitwiseOr\0" // IR(32799, 10)
  "BitwiseXor\0" // IR(32809, 11)
  "BitwiseAnd\0" // IR(32820, 11)
  "Not\0" // IR(32831, 4)
  "BitFieldInsert\0" // IR(32835, 15)
  "BitFieldSExtract\0" // IR(32850, 17)
  "BitFieldUExtract\0" // IR(32867, 17)
  "BitReverse\0" // IR(32884, 11)
  "BitCount\0" // IR(32895, 9)
  "DPdx\0" // IR(32904, 5)
  "DPdy\0" // IR(32909, 5)
  "Fwidth\0" // IR(32914, 7)
  "DPdxFine\0" // IR(32921, 9)
  "DPdyFine\0" // IR(32930, 9)
  "FwidthFine\0" // IR(32939, 11)
  "DPdxCoarse\0" // IR(32950, 11)
  "DPdyCoarse\0" // IR(32961, 11)
  "FwidthCoarse\0" // IR(32972, 13)
  "EmitVertex\0" // IR(32985, 11)
  "EndPrimitive\0" // IR(32996, 13)
  "EmitStreamVertex\0" // IR(33009, 17)
  "EndStreamPrimitive\0" // IR(33026, 19)
  "SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID\0" // IR(33045, 37)
  "ControlBarrier\0" // IR(33082, 15)
  "MemoryBarrier\0" // IR(33097, 14)
  "AtomicLoad\0" // IR(33111, 11)
  "AtomicStore\0" // IR(33122, 12)
  "AtomicExchange\0" // IR(33134, 15)
  "AtomicCompareExchange\0" // IR(33149, 22)
  "AtomicCompareExchangeWeak\0" // IR(33171, 26)
  "AtomicIIncrement\0" // IR(33197, 17)
  "AtomicIDecrement\0" // IR(33214, 17)
  "AtomicIAdd\0" // IR(33231, 11)
  "AtomicISub\0" // IR(33242, 11)
  "AtomicSMin\0" // IR(33253, 11)
  "AtomicUMin\0" // IR(33264, 11)
  "AtomicSMax\0" // IR(33275, 11)
  "AtomicUMax\0" // IR(33286, 11)
  "AtomicAnd\0" // IR(33297, 10)
  "AtomicOr\0" // IR(33307, 9)
  "AtomicXor\0" // IR(33316, 10)
  "Phi\0" // IR(33326, 4)
  "SPV_OPERAND_TYPE_LOOP_CONTROL\0" // IR(33330, 30)
  "LoopMerge\0" // IR(33360, 10)
  "SPV_OPERAND_TYPE_SELECTION_CONTROL\0" // IR(33370, 35)
  "SelectionMerge\0" // IR(33405, 15)
  "Label\0" // IR(33420, 6)
  "Branch\0" // IR(33426, 7)
  "BranchConditional\0" // IR(33433, 18)
  "SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER_ID\0" // IR(33451, 45)
  "Switch\0" // IR(33496, 7)
  "Kill\0" // IR(33503, 5)
  "Return\0" // IR(33508, 7)
  "ReturnValue\0" // IR(33515, 12)
  "Unreachable\0" // IR(33527, 12)
  "LifetimeStart\0" // IR(33539, 14)
  "LifetimeStop\0" // IR(33553, 13)
  "GroupAsyncCopy\0" // IR(33566, 15)
  "GroupWaitEvents\0" // IR(33581, 16)
  "GroupAll\0" // IR(33597, 9)
  "GroupAny\0" // IR(33606, 9)
  "GroupBroadcast\0" // IR(33615, 15)
  "SPV_OPERAND_TYPE_GROUP_OPERATION\0" // IR(33630, 33)
  "GroupIAdd\0" // IR(33663, 10)
  "GroupFAdd\0" // IR(33673, 10)
  "GroupFMin\0" // IR(33683, 10)
  "GroupUMin\0" // IR(33693, 10)
  "GroupSMin\0" // IR(33703, 10)
  "GroupFMax\0" // IR(33713, 10)
  "GroupUMax\0" // IR(33723, 10)
  "GroupSMax\0" // IR(33733, 10)
  "ReadPipe\0" // IR(33743, 9)
  "WritePipe\0" // IR(33752, 10)
  "ReservedReadPipe\0" // IR(33762, 17)
  "ReservedWritePipe\0" // IR(33779, 18)
  "ReserveReadPipePackets\0" // IR(33797, 23)
  "ReserveWritePipePackets\0" // IR(33820, 24)
  "CommitReadPipe\0" // IR(33844, 15)
  "CommitWritePipe\0" // IR(33859, 16)
  "IsValidReserveId\0" // IR(33875, 17)
  "GetNumPipePackets\0" // IR(33892, 18)
  "GetMaxPipePackets\0" // IR(33910, 18)
  "GroupReserveReadPipePackets\0" // IR(33928, 28)
  "GroupReserveWritePipePackets\0" // IR(33956, 29)
  "GroupCommitReadPipe\0" // IR(33985, 20)
  "GroupCommitWritePipe\0" // IR(34005, 21)
  "EnqueueMarker\0" // IR(34026, 14)
  "EnqueueKernel\0" // IR(34040, 14)
  "GetKernelNDrangeSubGroupCount\0" // IR(34054, 30)
  "GetKernelNDrangeMaxSubGroupSize\0" // IR(34084, 32)
  "GetKernelWorkGroupSize\0" // IR(34116, 23)
  "GetKernelPreferredWorkGroupSizeMultiple\0" // IR(34139, 40)
  "RetainEvent\0" // IR(34179, 12)
  "ReleaseEvent\0" // IR(34191, 13)
  "CreateUserEvent\0" // IR(34204, 16)
  "IsValidEvent\0" // IR(34220, 13)
  "SetUserEventStatus\0" // IR(34233, 19)
  "CaptureEventProfilingInfo\0" // IR(34252, 26)
  "GetDefaultQueue\0" // IR(34278, 16)
  "BuildNDRange\0" // IR(34294, 13)
  "ImageSparseSampleImplicitLod\0" // IR(34307, 29)
  "ImageSparseSampleExplicitLod\0" // IR(34336, 29)
  "ImageSparseSampleDrefImplicitLod\0" // IR(34365, 33)
  "ImageSparseSampleDrefExplicitLod\0" // IR(34398, 33)
  "ImageSparseSampleProjImplicitLod\0" // IR(34431, 33)
  "ImageSparseSampleProjExplicitLod\0" // IR(34464, 33)
  "ImageSparseSampleProjDrefImplicitLod\0" // IR(34497, 37)
  "ImageSparseSampleProjDrefExplicitLod\0" // IR(34534, 37)
  "ImageSparseFetch\0" // IR(34571, 17)
  "ImageSparseGather\0" // IR(34588, 18)
  "ImageSparseDrefGather\0" // IR(34606, 22)
  "ImageSparseTexelsResident\0" // IR(34628, 26)
  "NoLine\0" // IR(34654, 7)
  "AtomicFlagTestAndSet\0" // IR(34661, 21)
  "AtomicFlagClear\0" // IR(34682, 16)
  "ImageSparseRead\0" // IR(34698, 16)
  "SizeOf\0" // IR(34714, 7)
  "TypePipeStorage\0" // IR(34721, 16)
  "ConstantPipeStorage\0" // IR(34737, 20)
  "CreatePipeFromPipeStorage\0" // IR(34757, 26)
  "GetKernelLocalSizeForSubgroupCount\0" // IR(34783, 35)
  "GetKernelMaxNumSubgroups\0" // IR(34818, 25)
  "TypeNamedBarrier\0" // IR(34843, 17)
  "NamedBarrierInitialize\0" // IR(34860, 23)
  "MemoryNamedBarrier\0" // IR(34883, 19)
  "ModuleProcessed\0" // IR(34902, 16)
  "ExecutionModeId\0" // IR(34918, 16)
  "DecorateId\0" // IR(34934, 11)
  "GroupNonUniformElect\0" // IR(34945, 21)
  "GroupNonUniformAll\0" // IR(34966, 19)
  "GroupNonUniformAny\0" // IR(34985, 19)
  "GroupNonUniformAllEqual\0" // IR(35004, 24)
  "GroupNonUniformBroadcast\0" // IR(35028, 25)
  "GroupNonUniformBroadcastFirst\0" // IR(35053, 30)
  "GroupNonUniformInverseBallot\0" // IR(35083, 29)
  "GroupNonUniformBallotBitExtract\0" // IR(35112, 32)
  "GroupNonUniformBallotBitCount\0" // IR(35144, 30)
  "GroupNonUniformBallotFindLSB\0" // IR(35174, 29)
  "GroupNonUniformBallotFindMSB\0" // IR(35203, 29)
  "GroupNonUniformShuffleXor\0" // IR(35232, 26)
  "GroupNonUniformShuffleUp\0" // IR(35258, 25)
  "GroupNonUniformShuffleDown\0" // IR(35283, 27)
  "GroupNonUniformIAdd\0" // IR(35310, 20)
  "GroupNonUniformFAdd\0" // IR(35330, 20)
  "GroupNonUniformIMul\0" // IR(35350, 20)
  "GroupNonUniformFMul\0" // IR(35370, 20)
  "GroupNonUniformSMin\0" // IR(35390, 20)
  "GroupNonUniformUMin\0" // IR(35410, 20)
  "GroupNonUniformFMin\0" // IR(35430, 20)
  "GroupNonUniformSMax\0" // IR(35450, 20)
  "GroupNonUniformUMax\0" // IR(35470, 20)
  "GroupNonUniformFMax\0" // IR(35490, 20)
  "GroupNonUniformBitwiseAnd\0" // IR(35510, 26)
  "GroupNonUniformBitwiseOr\0" // IR(35536, 25)
  "GroupNonUniformBitwiseXor\0" // IR(35561, 26)
  "GroupNonUniformLogicalAnd\0" // IR(35587, 26)
  "GroupNonUniformLogicalOr\0" // IR(35613, 25)
  "GroupNonUniformLogicalXor\0" // IR(35638, 26)
  "GroupNonUniformQuadBroadcast\0" // IR(35664, 29)
  "GroupNonUniformQuadSwap\0" // IR(35693, 24)
  "CopyLogical\0" // IR(35717, 12)
  "PtrEqual\0" // IR(35729, 9)
  "PtrNotEqual\0" // IR(35738, 12)
  "PtrDiff\0" // IR(35750, 8)
  "ColorAttachmentReadEXT\0" // IR(35758, 23)
  "DepthAttachmentReadEXT\0" // IR(35781, 23)
  "StencilAttachmentReadEXT\0" // IR(35804, 25)
  "TypeTensorARM\0" // IR(35829, 14)
  "SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS\0" // IR(35843, 42)
  "TensorReadARM\0" // IR(35885, 14)
  "TensorWriteARM\0" // IR(35899, 15)
  "TensorQuerySizeARM\0" // IR(35914, 19)
  "GraphConstantARM\0" // IR(35933, 17)
  "GraphEntryPointARM\0" // IR(35950, 19)
  "GraphInputARM\0" // IR(35969, 14)
  "GraphSetOutputARM\0" // IR(35983, 18)
  "GraphEndARM\0" // IR(36001, 12)
  "TypeGraphARM\0" // IR(36013, 13)
  "TerminateInvocation\0" // IR(36026, 20)
  "TypeUntypedPointerKHR\0" // IR(36046, 22)
  "UntypedVariableKHR\0" // IR(36068, 19)
  "UntypedAccessChainKHR\0" // IR(36087, 22)
  "UntypedInBoundsAccessChainKHR\0" // IR(36109, 30)
  "SubgroupFirstInvocationKHR\0" // IR(36139, 27)
  "UntypedPtrAccessChainKHR\0" // IR(36166, 25)
  "UntypedInBoundsPtrAccessChainKHR\0" // IR(36191, 33)
  "UntypedArrayLengthKHR\0" // IR(36224, 22)
  "UntypedPrefetchKHR\0" // IR(36246, 19)
  "FmaKHR\0" // IR(36265, 7)
  "SubgroupAllKHR\0" // IR(36272, 15)
  "SubgroupAnyKHR\0" // IR(36287, 15)
  "SubgroupAllEqualKHR\0" // IR(36302, 20)
  "SubgroupReadInvocationKHR\0" // IR(36322, 26)
  "ExtInstWithForwardRefsKHR\0" // IR(36348, 26)
  "UntypedGroupAsyncCopyKHR\0" // IR(36374, 25)
  "TraceRayKHR\0" // IR(36399, 12)
  "ExecuteCallableKHR\0" // IR(36411, 19)
  "ConvertUToAccelerationStructureKHR\0" // IR(36430, 35)
  "IgnoreIntersectionKHR\0" // IR(36465, 22)
  "TerminateRayKHR\0" // IR(36487, 16)
  "SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT\0" // IR(36503, 47)
  "SDot\0" // IR(36550, 5)
  "SDotKHR\0" // IR(36555, 8)
  "UDot\0" // IR(36563, 5)
  "UDotKHR\0" // IR(36568, 8)
  "SUDot\0" // IR(36576, 6)
  "SUDotKHR\0" // IR(36582, 9)
  "SDotAccSat\0" // IR(36591, 11)
  "SDotAccSatKHR\0" // IR(36602, 14)
  "UDotAccSat\0" // IR(36616, 11)
  "UDotAccSatKHR\0" // IR(36627, 14)
  "SUDotAccSat\0" // IR(36641, 12)
  "SUDotAccSatKHR\0" // IR(36653, 15)
  "TypeCooperativeMatrixKHR\0" // IR(36668, 25)
  "CooperativeMatrixLoadKHR\0" // IR(36693, 25)
  "CooperativeMatrixStoreKHR\0" // IR(36718, 26)
  "SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS\0" // IR(36744, 54)
  "CooperativeMatrixMulAddKHR\0" // IR(36798, 27)
  "CooperativeMatrixLengthKHR\0" // IR(36825, 27)
  "ConstantCompositeReplicateEXT\0" // IR(36852, 30)
  "SpecConstantCompositeReplicateEXT\0" // IR(36882, 34)
  "CompositeConstructReplicateEXT\0" // IR(36916, 31)
  "TypeRayQueryKHR\0" // IR(36947, 16)
  "RayQueryInitializeKHR\0" // IR(36963, 22)
  "RayQueryTerminateKHR\0" // IR(36985, 21)
  "RayQueryGenerateIntersectionKHR\0" // IR(37006, 32)
  "RayQueryConfirmIntersectionKHR\0" // IR(37038, 31)
  "RayQueryProceedKHR\0" // IR(37069, 19)
  "RayQueryGetIntersectionTypeKHR\0" // IR(37088, 31)
  "ImageSampleWeightedQCOM\0" // IR(37119, 24)
  "ImageBoxFilterQCOM\0" // IR(37143, 19)
  "ImageBlockMatchSSDQCOM\0" // IR(37162, 23)
  "ImageBlockMatchSADQCOM\0" // IR(37185, 23)
  "BitCastArrayQCOM\0" // IR(37208, 17)
  "ImageBlockMatchWindowSSDQCOM\0" // IR(37225, 29)
  "ImageBlockMatchWindowSADQCOM\0" // IR(37254, 29)
  "ImageBlockMatchGatherSSDQCOM\0" // IR(37283, 29)
  "ImageBlockMatchGatherSADQCOM\0" // IR(37312, 29)
  "CompositeConstructCoopMatQCOM\0" // IR(37341, 30)
  "CompositeExtractCoopMatQCOM\0" // IR(37371, 28)
  "ExtractSubArrayQCOM\0" // IR(37399, 20)
  "ImageGatherQCOM\0" // IR(37419, 16)
  "GroupIAddNonUniformAMD\0" // IR(37435, 23)
  "GroupFAddNonUniformAMD\0" // IR(37458, 23)
  "GroupFMinNonUniformAMD\0" // IR(37481, 23)
  "GroupUMinNonUniformAMD\0" // IR(37504, 23)
  "GroupSMinNonUniformAMD\0" // IR(37527, 23)
  "GroupFMaxNonUniformAMD\0" // IR(37550, 23)
  "GroupUMaxNonUniformAMD\0" // IR(37573, 23)
  "GroupSMaxNonUniformAMD\0" // IR(37596, 23)
  "FragmentMaskFetchAMD\0" // IR(37619, 21)
  "FragmentFetchAMD\0" // IR(37640, 17)
  "ReadClockKHR\0" // IR(37657, 13)
  "AllocateNodePayloadsAMDX\0" // IR(37670, 25)
  "EnqueueNodePayloadsAMDX\0" // IR(37695, 24)
  "TypeNodePayloadArrayAMDX\0" // IR(37719, 25)
  "FinishWritingNodePayloadAMDX\0" // IR(37744, 29)
  "NodePayloadArrayLengthAMDX\0" // IR(37773, 27)
  "IsNodePayloadValidAMDX\0" // IR(37800, 23)
  "ConstantStringAMDX\0" // IR(37823, 19)
  "SpecConstantStringAMDX\0" // IR(37842, 23)
  "GroupNonUniformQuadAllKHR\0" // IR(37865, 26)
  "GroupNonUniformQuadAnyKHR\0" // IR(37891, 26)
  "TypeBufferEXT\0" // IR(37917, 14)
  "BufferPointerEXT\0" // IR(37931, 17)
  "UntypedImageTexelPointerEXT\0" // IR(37948, 28)
  "MemberDecorateIdEXT\0" // IR(37976, 20)
  "ConstantSizeOfEXT\0" // IR(37996, 18)
  "SpecConstantDataKHR\0" // IR(38014, 20)
  "PoisonKHR\0" // IR(38034, 10)
  "FreezeKHR\0" // IR(38044, 10)
  "HitObjectRecordHitMotionNV\0" // IR(38054, 27)
  "HitObjectRecordHitWithIndexMotionNV\0" // IR(38081, 36)
  "HitObjectRecordMissMotionNV\0" // IR(38117, 28)
  "HitObjectGetWorldToObjectNV\0" // IR(38145, 28)
  "HitObjectGetObjectToWorldNV\0" // IR(38173, 28)
  "HitObjectGetObjectRayDirectionNV\0" // IR(38201, 33)
  "HitObjectGetObjectRayOriginNV\0" // IR(38234, 30)
  "HitObjectTraceRayMotionNV\0" // IR(38264, 26)
  "HitObjectGetShaderRecordBufferHandleNV\0" // IR(38290, 39)
  "HitObjectGetShaderBindingTableRecordIndexNV\0" // IR(38329, 44)
  "HitObjectRecordEmptyNV\0" // IR(38373, 23)
  "HitObjectTraceRayNV\0" // IR(38396, 20)
  "HitObjectRecordHitNV\0" // IR(38416, 21)
  "HitObjectRecordHitWithIndexNV\0" // IR(38437, 30)
  "HitObjectRecordMissNV\0" // IR(38467, 22)
  "HitObjectExecuteShaderNV\0" // IR(38489, 25)
  "HitObjectGetCurrentTimeNV\0" // IR(38514, 26)
  "HitObjectGetAttributesNV\0" // IR(38540, 25)
  "HitObjectGetHitKindNV\0" // IR(38565, 22)
  "HitObjectGetPrimitiveIndexNV\0" // IR(38587, 29)
  "HitObjectGetGeometryIndexNV\0" // IR(38616, 28)
  "HitObjectGetInstanceIdNV\0" // IR(38644, 25)
  "HitObjectGetInstanceCustomIndexNV\0" // IR(38669, 34)
  "HitObjectGetWorldRayDirectionNV\0" // IR(38703, 32)
  "HitObjectGetWorldRayOriginNV\0" // IR(38735, 29)
  "HitObjectGetRayTMaxNV\0" // IR(38764, 22)
  "HitObjectGetRayTMinNV\0" // IR(38786, 22)
  "HitObjectIsEmptyNV\0" // IR(38808, 19)
  "HitObjectIsHitNV\0" // IR(38827, 17)
  "HitObjectIsMissNV\0" // IR(38844, 18)
  "ReorderThreadWithHitObjectNV\0" // IR(38862, 29)
  "ReorderThreadWithHintNV\0" // IR(38891, 24)
  "TypeHitObjectNV\0" // IR(38915, 16)
  "ImageSampleFootprintNV\0" // IR(38931, 23)
  "TypeVectorIdEXT\0" // IR(38954, 16)
  "TypeCooperativeVectorNV\0" // IR(38970, 24)
  "CooperativeVectorMatrixMulNV\0" // IR(38994, 29)
  "CooperativeVectorOuterProductAccumulateNV\0" // IR(39023, 42)
  "CooperativeVectorReduceSumAccumulateNV\0" // IR(39065, 39)
  "CooperativeVectorMatrixMulAddNV\0" // IR(39104, 32)
  "CooperativeMatrixConvertUseEXT\0" // IR(39136, 31)
  "CooperativeMatrixConvertNV\0" // IR(39167, 27)
  "EmitMeshTasksEXT\0" // IR(39194, 17)
  "SetMeshOutputsEXT\0" // IR(39211, 18)
  "GroupNonUniformPartitionEXT\0" // IR(39229, 28)
  "GroupNonUniformPartitionNV\0" // IR(39257, 27)
  "WritePackedPrimitiveIndices4x8NV\0" // IR(39284, 33)
  "FetchMicroTriangleVertexPositionNV\0" // IR(39317, 35)
  "FetchMicroTriangleVertexBarycentricNV\0" // IR(39352, 38)
  "CooperativeVectorLoadNV\0" // IR(39390, 24)
  "CooperativeVectorStoreNV\0" // IR(39414, 25)
  "HitObjectRecordFromQueryEXT\0" // IR(39439, 28)
  "HitObjectRecordMissEXT\0" // IR(39467, 23)
  "HitObjectRecordMissMotionEXT\0" // IR(39490, 29)
  "HitObjectGetIntersectionTriangleVertexPositionsEXT\0" // IR(39519, 51)
  "HitObjectGetRayFlagsEXT\0" // IR(39570, 24)
  "HitObjectSetShaderBindingTableRecordIndexEXT\0" // IR(39594, 45)
  "HitObjectReorderExecuteShaderEXT\0" // IR(39639, 33)
  "HitObjectTraceReorderExecuteEXT\0" // IR(39672, 32)
  "HitObjectTraceMotionReorderExecuteEXT\0" // IR(39704, 38)
  "TypeHitObjectEXT\0" // IR(39742, 17)
  "ReorderThreadWithHintEXT\0" // IR(39759, 25)
  "ReorderThreadWithHitObjectEXT\0" // IR(39784, 30)
  "HitObjectTraceRayEXT\0" // IR(39814, 21)
  "HitObjectTraceRayMotionEXT\0" // IR(39835, 27)
  "HitObjectRecordEmptyEXT\0" // IR(39862, 24)
  "HitObjectExecuteShaderEXT\0" // IR(39886, 26)
  "HitObjectGetCurrentTimeEXT\0" // IR(39912, 27)
  "HitObjectGetAttributesEXT\0" // IR(39939, 26)
  "HitObjectGetHitKindEXT\0" // IR(39965, 23)
  "HitObjectGetPrimitiveIndexEXT\0" // IR(39988, 30)
  "HitObjectGetGeometryIndexEXT\0" // IR(40018, 29)
  "HitObjectGetInstanceIdEXT\0" // IR(40047, 26)
  "HitObjectGetInstanceCustomIndexEXT\0" // IR(40073, 35)
  "HitObjectGetObjectRayOriginEXT\0" // IR(40108, 31)
  "HitObjectGetObjectRayDirectionEXT\0" // IR(40139, 34)
  "HitObjectGetWorldRayDirectionEXT\0" // IR(40173, 33)
  "HitObjectGetWorldRayOriginEXT\0" // IR(40206, 30)
  "HitObjectGetObjectToWorldEXT\0" // IR(40236, 29)
  "HitObjectGetWorldToObjectEXT\0" // IR(40265, 29)
  "HitObjectGetRayTMaxEXT\0" // IR(40294, 23)
  "ReportIntersectionKHR\0" // IR(40317, 22)
  "ReportIntersectionNV\0" // IR(40339, 21)
  "IgnoreIntersectionNV\0" // IR(40360, 21)
  "TerminateRayNV\0" // IR(40381, 15)
  "TraceNV\0" // IR(40396, 8)
  "TraceMotionNV\0" // IR(40404, 14)
  "TraceRayMotionNV\0" // IR(40418, 17)
  "RayQueryGetIntersectionTriangleVertexPositionsKHR\0" // IR(40435, 50)
  "TypeAccelerationStructureKHR\0" // IR(40485, 29)
  "TypeAccelerationStructureNV\0" // IR(40514, 28)
  "ExecuteCallableNV\0" // IR(40542, 18)
  "RayQueryGetIntersectionClusterIdNV\0" // IR(40560, 35)
  "RayQueryGetClusterIdNV\0" // IR(40595, 23)
  "HitObjectGetClusterIdNV\0" // IR(40618, 24)
  "HitObjectGetRayTMinEXT\0" // IR(40642, 23)
  "HitObjectGetShaderBindingTableRecordIndexEXT\0" // IR(40665, 45)
  "HitObjectGetShaderRecordBufferHandleEXT\0" // IR(40710, 40)
  "HitObjectIsEmptyEXT\0" // IR(40750, 20)
  "HitObjectIsHitEXT\0" // IR(40770, 18)
  "HitObjectIsMissEXT\0" // IR(40788, 19)
  "TypeCooperativeMatrixNV\0" // IR(40807, 24)
  "CooperativeMatrixLoadNV\0" // IR(40831, 24)
  "CooperativeMatrixStoreNV\0" // IR(40855, 25)
  "CooperativeMatrixMulAddNV\0" // IR(40880, 26)
  "CooperativeMatrixLengthNV\0" // IR(40906, 26)
  "BeginInvocationInterlockEXT\0" // IR(40932, 28)
  "EndInvocationInterlockEXT\0" // IR(40960, 26)
  "SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE\0" // IR(40986, 43)
  "CooperativeMatrixReduceEXT\0" // IR(41029, 27)
  "CooperativeMatrixReduceNV\0" // IR(41056, 26)
  "SPV_OPERAND_TYPE_MEMORY_ACCESS\0" // IR(41082, 31)
  "SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS\0" // IR(41113, 44)
  "CooperativeMatrixLoadTensorNV\0" // IR(41157, 30)
  "CooperativeMatrixStoreTensorNV\0" // IR(41187, 31)
  "CooperativeMatrixPerElementOpEXT\0" // IR(41218, 33)
  "CooperativeMatrixPerElementOpNV\0" // IR(41251, 32)
  "TypeTensorLayoutNV\0" // IR(41283, 19)
  "TypeTensorViewNV\0" // IR(41302, 17)
  "CreateTensorLayoutNV\0" // IR(41319, 21)
  "TensorLayoutSetDimensionNV\0" // IR(41340, 27)
  "TensorLayoutSetStrideNV\0" // IR(41367, 24)
  "TensorLayoutSliceNV\0" // IR(41391, 20)
  "TensorLayoutSetClampValueNV\0" // IR(41411, 28)
  "CreateTensorViewNV\0" // IR(41439, 19)
  "TensorViewSetDimensionNV\0" // IR(41458, 25)
  "TensorViewSetStrideNV\0" // IR(41483, 22)
  "IsHelperInvocationEXT\0" // IR(41505, 22)
  "TensorViewSetClipNV\0" // IR(41527, 20)
  "TensorLayoutSetBlockSizeNV\0" // IR(41547, 27)
  "CooperativeMatrixTransposeNV\0" // IR(41574, 29)
  "ConvertUToImageNV\0" // IR(41603, 18)
  "ConvertUToSamplerNV\0" // IR(41621, 20)
  "ConvertImageToUNV\0" // IR(41641, 18)
  "ConvertSamplerToUNV\0" // IR(41659, 20)
  "ConvertUToSampledImageNV\0" // IR(41679, 25)
  "ConvertSampledImageToUNV\0" // IR(41704, 25)
  "SamplerImageAddressingModeNV\0" // IR(41729, 29)
  "SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS\0" // IR(41758, 52)
  "RawAccessChainNV\0" // IR(41810, 17)
  "RayQueryGetIntersectionSpherePositionNV\0" // IR(41827, 40)
  "RayQueryGetIntersectionSphereRadiusNV\0" // IR(41867, 38)
  "RayQueryGetIntersectionLSSPositionsNV\0" // IR(41905, 38)
  "RayQueryGetIntersectionLSSRadiiNV\0" // IR(41943, 34)
  "RayQueryGetIntersectionLSSHitValueNV\0" // IR(41977, 37)
  "HitObjectGetSpherePositionNV\0" // IR(42014, 29)
  "HitObjectGetSphereRadiusNV\0" // IR(42043, 27)
  "HitObjectGetLSSPositionsNV\0" // IR(42070, 27)
  "HitObjectGetLSSRadiiNV\0" // IR(42097, 23)
  "HitObjectIsSphereHitNV\0" // IR(42120, 23)
  "HitObjectIsLSSHitNV\0" // IR(42143, 20)
  "RayQueryIsSphereHitNV\0" // IR(42163, 22)
  "RayQueryIsLSSHitNV\0" // IR(42185, 19)
  "SubgroupShuffleDownINTEL\0" // IR(42204, 25)
  "SubgroupShuffleUpINTEL\0" // IR(42229, 23)
  "SubgroupShuffleXorINTEL\0" // IR(42252, 24)
  "SubgroupBlockReadINTEL\0" // IR(42276, 23)
  "SubgroupBlockWriteINTEL\0" // IR(42299, 24)
  "SubgroupImageBlockReadINTEL\0" // IR(42323, 28)
  "SubgroupImageBlockWriteINTEL\0" // IR(42351, 29)
  "SubgroupImageMediaBlockReadINTEL\0" // IR(42380, 33)
  "SubgroupImageMediaBlockWriteINTEL\0" // IR(42413, 34)
  "UCountLeadingZerosINTEL\0" // IR(42447, 24)
  "UCountTrailingZerosINTEL\0" // IR(42471, 25)
  "AbsISubINTEL\0" // IR(42496, 13)
  "AbsUSubINTEL\0" // IR(42509, 13)
  "IAddSatINTEL\0" // IR(42522, 13)
  "UAddSatINTEL\0" // IR(42535, 13)
  "IAverageINTEL\0" // IR(42548, 14)
  "UAverageINTEL\0" // IR(42562, 14)
  "IAverageRoundedINTEL\0" // IR(42576, 21)
  "UAverageRoundedINTEL\0" // IR(42597, 21)
  "ISubSatINTEL\0" // IR(42618, 13)
  "USubSatINTEL\0" // IR(42631, 13)
  "IMul32x16INTEL\0" // IR(42644, 15)
  "UMul32x16INTEL\0" // IR(42659, 15)
  "ConstantFunctionPointerINTEL\0" // IR(42674, 29)
  "FunctionPointerCallINTEL\0" // IR(42703, 25)
  "AsmTargetINTEL\0" // IR(42728, 15)
  "AsmCallINTEL\0" // IR(42743, 13)
  "AtomicFMinEXT\0" // IR(42756, 14)
  "AtomicFMaxEXT\0" // IR(42770, 14)
  "AssumeTrueKHR\0" // IR(42784, 14)
  "ExpectKHR\0" // IR(42798, 10)
  "DecorateString\0" // IR(42808, 15)
  "DecorateStringGOOGLE\0" // IR(42823, 21)
  "MemberDecorateString\0" // IR(42844, 21)
  "MemberDecorateStringGOOGLE\0" // IR(42865, 27)
  "VmeImageINTEL\0" // IR(42892, 14)
  "TypeVmeImageINTEL\0" // IR(42906, 18)
  "TypeAvcImePayloadINTEL\0" // IR(42924, 23)
  "TypeAvcRefPayloadINTEL\0" // IR(42947, 23)
  "TypeAvcSicPayloadINTEL\0" // IR(42970, 23)
  "TypeAvcMcePayloadINTEL\0" // IR(42993, 23)
  "TypeAvcMceResultINTEL\0" // IR(43016, 22)
  "TypeAvcImeResultINTEL\0" // IR(43038, 22)
  "TypeAvcImeResultSingleReferenceStreamoutINTEL\0" // IR(43060, 46)
  "TypeAvcImeResultDualReferenceStreamoutINTEL\0" // IR(43106, 44)
  "TypeAvcImeSingleReferenceStreaminINTEL\0" // IR(43150, 39)
  "TypeAvcImeDualReferenceStreaminINTEL\0" // IR(43189, 37)
  "TypeAvcRefResultINTEL\0" // IR(43226, 22)
  "TypeAvcSicResultINTEL\0" // IR(43248, 22)
  "SubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL\0" // IR(43270, 60)
  "SubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL\0" // IR(43330, 53)
  "SubgroupAvcMceGetDefaultInterShapePenaltyINTEL\0" // IR(43383, 47)
  "SubgroupAvcMceSetInterShapePenaltyINTEL\0" // IR(43430, 40)
  "SubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL\0" // IR(43470, 51)
  "SubgroupAvcMceSetInterDirectionPenaltyINTEL\0" // IR(43521, 44)
  "SubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL\0" // IR(43565, 51)
  "SubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL\0" // IR(43616, 56)
  "SubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL\0" // IR(43672, 50)
  "SubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL\0" // IR(43722, 52)
  "SubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL\0" // IR(43774, 49)
  "SubgroupAvcMceSetMotionVectorCostFunctionINTEL\0" // IR(43823, 47)
  "SubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL\0" // IR(43870, 50)
  "SubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL\0" // IR(43920, 51)
  "SubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL\0" // IR(43971, 56)
  "SubgroupAvcMceSetAcOnlyHaarINTEL\0" // IR(44027, 33)
  "SubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL\0" // IR(44060, 52)
  "SubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL\0" // IR(44112, 61)
  "SubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL\0" // IR(44173, 61)
  "SubgroupAvcMceConvertToImePayloadINTEL\0" // IR(44234, 39)
  "SubgroupAvcMceConvertToImeResultINTEL\0" // IR(44273, 38)
  "SubgroupAvcMceConvertToRefPayloadINTEL\0" // IR(44311, 39)
  "SubgroupAvcMceConvertToRefResultINTEL\0" // IR(44350, 38)
  "SubgroupAvcMceConvertToSicPayloadINTEL\0" // IR(44388, 39)
  "SubgroupAvcMceConvertToSicResultINTEL\0" // IR(44427, 38)
  "SubgroupAvcMceGetMotionVectorsINTEL\0" // IR(44465, 36)
  "SubgroupAvcMceGetInterDistortionsINTEL\0" // IR(44501, 39)
  "SubgroupAvcMceGetBestInterDistortionsINTEL\0" // IR(44540, 43)
  "SubgroupAvcMceGetInterMajorShapeINTEL\0" // IR(44583, 38)
  "SubgroupAvcMceGetInterMinorShapeINTEL\0" // IR(44621, 38)
  "SubgroupAvcMceGetInterDirectionsINTEL\0" // IR(44659, 38)
  "SubgroupAvcMceGetInterMotionVectorCountINTEL\0" // IR(44697, 45)
  "SubgroupAvcMceGetInterReferenceIdsINTEL\0" // IR(44742, 40)
  "SubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL\0" // IR(44782, 62)
  "SubgroupAvcImeInitializeINTEL\0" // IR(44844, 30)
  "SubgroupAvcImeSetSingleReferenceINTEL\0" // IR(44874, 38)
  "SubgroupAvcImeSetDualReferenceINTEL\0" // IR(44912, 36)
  "SubgroupAvcImeRefWindowSizeINTEL\0" // IR(44948, 33)
  "SubgroupAvcImeAdjustRefOffsetINTEL\0" // IR(44981, 35)
  "SubgroupAvcImeConvertToMcePayloadINTEL\0" // IR(45016, 39)
  "SubgroupAvcImeSetMaxMotionVectorCountINTEL\0" // IR(45055, 43)
  "SubgroupAvcImeSetUnidirectionalMixDisableINTEL\0" // IR(45098, 47)
  "SubgroupAvcImeSetEarlySearchTerminationThresholdINTEL\0" // IR(45145, 54)
  "SubgroupAvcImeSetWeightedSadINTEL\0" // IR(45199, 34)
  "SubgroupAvcImeEvaluateWithSingleReferenceINTEL\0" // IR(45233, 47)
  "SubgroupAvcImeEvaluateWithDualReferenceINTEL\0" // IR(45280, 45)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL\0" // IR(45325, 55)
  "SubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL\0" // IR(45380, 53)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL\0" // IR(45433, 56)
  "SubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL\0" // IR(45489, 54)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL\0" // IR(45543, 58)
  "SubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL\0" // IR(45601, 56)
  "SubgroupAvcImeConvertToMceResultINTEL\0" // IR(45657, 38)
  "SubgroupAvcImeGetSingleReferenceStreaminINTEL\0" // IR(45695, 46)
  "SubgroupAvcImeGetDualReferenceStreaminINTEL\0" // IR(45741, 44)
  "SubgroupAvcImeStripSingleReferenceStreamoutINTEL\0" // IR(45785, 49)
  "SubgroupAvcImeStripDualReferenceStreamoutINTEL\0" // IR(45834, 47)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL\0" // IR(45881, 70)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL\0" // IR(45951, 68)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL\0" // IR(46019, 69)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL\0" // IR(46088, 68)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL\0" // IR(46156, 66)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL\0" // IR(46222, 67)
  "SubgroupAvcImeGetBorderReachedINTEL\0" // IR(46289, 36)
  "SubgroupAvcImeGetTruncatedSearchIndicationINTEL\0" // IR(46325, 48)
  "SubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL\0" // IR(46373, 59)
  "SubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL\0" // IR(46432, 58)
  "SubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL\0" // IR(46490, 56)
  "SubgroupAvcFmeInitializeINTEL\0" // IR(46546, 30)
  "SubgroupAvcBmeInitializeINTEL\0" // IR(46576, 30)
  "SubgroupAvcRefConvertToMcePayloadINTEL\0" // IR(46606, 39)
  "SubgroupAvcRefSetBidirectionalMixDisableINTEL\0" // IR(46645, 46)
  "SubgroupAvcRefSetBilinearFilterEnableINTEL\0" // IR(46691, 43)
  "SubgroupAvcRefEvaluateWithSingleReferenceINTEL\0" // IR(46734, 47)
  "SubgroupAvcRefEvaluateWithDualReferenceINTEL\0" // IR(46781, 45)
  "SubgroupAvcRefEvaluateWithMultiReferenceINTEL\0" // IR(46826, 46)
  "SubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL\0" // IR(46872, 56)
  "SubgroupAvcRefConvertToMceResultINTEL\0" // IR(46928, 38)
  "SubgroupAvcSicInitializeINTEL\0" // IR(46966, 30)
  "SubgroupAvcSicConfigureSkcINTEL\0" // IR(46996, 32)
  "SubgroupAvcSicConfigureIpeLumaINTEL\0" // IR(47028, 36)
  "SubgroupAvcSicConfigureIpeLumaChromaINTEL\0" // IR(47064, 42)
  "SubgroupAvcSicGetMotionVectorMaskINTEL\0" // IR(47106, 39)
  "SubgroupAvcSicConvertToMcePayloadINTEL\0" // IR(47145, 39)
  "SubgroupAvcSicSetIntraLumaShapePenaltyINTEL\0" // IR(47184, 44)
  "SubgroupAvcSicSetIntraLumaModeCostFunctionINTEL\0" // IR(47228, 48)
  "SubgroupAvcSicSetIntraChromaModeCostFunctionINTEL\0" // IR(47276, 50)
  "SubgroupAvcSicSetBilinearFilterEnableINTEL\0" // IR(47326, 43)
  "SubgroupAvcSicSetSkcForwardTransformEnableINTEL\0" // IR(47369, 48)
  "SubgroupAvcSicSetBlockBasedRawSkipSadINTEL\0" // IR(47417, 43)
  "SubgroupAvcSicEvaluateIpeINTEL\0" // IR(47460, 31)
  "SubgroupAvcSicEvaluateWithSingleReferenceINTEL\0" // IR(47491, 47)
  "SubgroupAvcSicEvaluateWithDualReferenceINTEL\0" // IR(47538, 45)
  "SubgroupAvcSicEvaluateWithMultiReferenceINTEL\0" // IR(47583, 46)
  "SubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL\0" // IR(47629, 56)
  "SubgroupAvcSicConvertToMceResultINTEL\0" // IR(47685, 38)
  "SubgroupAvcSicGetIpeLumaShapeINTEL\0" // IR(47723, 35)
  "SubgroupAvcSicGetBestIpeLumaDistortionINTEL\0" // IR(47758, 44)
  "SubgroupAvcSicGetBestIpeChromaDistortionINTEL\0" // IR(47802, 46)
  "SubgroupAvcSicGetPackedIpeLumaModesINTEL\0" // IR(47848, 41)
  "SubgroupAvcSicGetIpeChromaModeINTEL\0" // IR(47889, 36)
  "SubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL\0" // IR(47925, 50)
  "SubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL\0" // IR(47975, 48)
  "SubgroupAvcSicGetInterRawSadsINTEL\0" // IR(48023, 35)
  "SaveMemoryINTEL\0" // IR(48058, 16)
  "RestoreMemoryINTEL\0" // IR(48074, 19)
  "ArbitraryFloatSinCosPiALTERA\0" // IR(48093, 29)
  "ArbitraryFloatSinCosPiINTEL\0" // IR(48122, 28)
  "ArbitraryFloatCastALTERA\0" // IR(48150, 25)
  "ArbitraryFloatCastINTEL\0" // IR(48175, 24)
  "ArbitraryFloatCastFromIntALTERA\0" // IR(48199, 32)
  "ArbitraryFloatCastFromIntINTEL\0" // IR(48231, 31)
  "ArbitraryFloatCastToIntALTERA\0" // IR(48262, 30)
  "ArbitraryFloatCastToIntINTEL\0" // IR(48292, 29)
  "ArbitraryFloatAddALTERA\0" // IR(48321, 24)
  "ArbitraryFloatAddINTEL\0" // IR(48345, 23)
  "ArbitraryFloatSubALTERA\0" // IR(48368, 24)
  "ArbitraryFloatSubINTEL\0" // IR(48392, 23)
  "ArbitraryFloatMulALTERA\0" // IR(48415, 24)
  "ArbitraryFloatMulINTEL\0" // IR(48439, 23)
  "ArbitraryFloatDivALTERA\0" // IR(48462, 24)
  "ArbitraryFloatDivINTEL\0" // IR(48486, 23)
  "ArbitraryFloatGTALTERA\0" // IR(48509, 23)
  "ArbitraryFloatGTINTEL\0" // IR(48532, 22)
  "ArbitraryFloatGEALTERA\0" // IR(48554, 23)
  "ArbitraryFloatGEINTEL\0" // IR(48577, 22)
  "ArbitraryFloatLTALTERA\0" // IR(48599, 23)
  "ArbitraryFloatLTINTEL\0" // IR(48622, 22)
  "ArbitraryFloatLEALTERA\0" // IR(48644, 23)
  "ArbitraryFloatLEINTEL\0" // IR(48667, 22)
  "ArbitraryFloatEQALTERA\0" // IR(48689, 23)
  "ArbitraryFloatEQINTEL\0" // IR(48712, 22)
  "ArbitraryFloatRecipALTERA\0" // IR(48734, 26)
  "ArbitraryFloatRecipINTEL\0" // IR(48760, 25)
  "ArbitraryFloatRSqrtALTERA\0" // IR(48785, 26)
  "ArbitraryFloatRSqrtINTEL\0" // IR(48811, 25)
  "ArbitraryFloatCbrtALTERA\0" // IR(48836, 25)
  "ArbitraryFloatCbrtINTEL\0" // IR(48861, 24)
  "ArbitraryFloatHypotALTERA\0" // IR(48885, 26)
  "ArbitraryFloatHypotINTEL\0" // IR(48911, 25)
  "ArbitraryFloatSqrtALTERA\0" // IR(48936, 25)
  "ArbitraryFloatSqrtINTEL\0" // IR(48961, 24)
  "ArbitraryFloatLogINTEL\0" // IR(48985, 23)
  "ArbitraryFloatLog2INTEL\0" // IR(49008, 24)
  "ArbitraryFloatLog10INTEL\0" // IR(49032, 25)
  "ArbitraryFloatLog1pINTEL\0" // IR(49057, 25)
  "ArbitraryFloatExpINTEL\0" // IR(49082, 23)
  "ArbitraryFloatExp2INTEL\0" // IR(49105, 24)
  "ArbitraryFloatExp10INTEL\0" // IR(49129, 25)
  "ArbitraryFloatExpm1INTEL\0" // IR(49154, 25)
  "ArbitraryFloatSinINTEL\0" // IR(49179, 23)
  "ArbitraryFloatCosINTEL\0" // IR(49202, 23)
  "ArbitraryFloatSinCosINTEL\0" // IR(49225, 26)
  "ArbitraryFloatSinPiINTEL\0" // IR(49251, 25)
  "ArbitraryFloatCosPiINTEL\0" // IR(49276, 25)
  "ArbitraryFloatASinINTEL\0" // IR(49301, 24)
  "ArbitraryFloatASinPiINTEL\0" // IR(49325, 26)
  "ArbitraryFloatACosINTEL\0" // IR(49351, 24)
  "ArbitraryFloatACosPiINTEL\0" // IR(49375, 26)
  "ArbitraryFloatATanINTEL\0" // IR(49401, 24)
  "ArbitraryFloatATanPiINTEL\0" // IR(49425, 26)
  "ArbitraryFloatATan2INTEL\0" // IR(49451, 25)
  "ArbitraryFloatPowINTEL\0" // IR(49476, 23)
  "ArbitraryFloatPowRINTEL\0" // IR(49499, 24)
  "ArbitraryFloatPowNINTEL\0" // IR(49523, 24)
  "LoopControlINTEL\0" // IR(49547, 17)
  "AliasDomainDeclINTEL\0" // IR(49564, 21)
  "AliasScopeDeclINTEL\0" // IR(49585, 20)
  "AliasScopeListDeclINTEL\0" // IR(49605, 24)
  "FixedSqrtALTERA\0" // IR(49629, 16)
  "FixedSqrtINTEL\0" // IR(49645, 15)
  "FixedRecipALTERA\0" // IR(49660, 17)
  "FixedRecipINTEL\0" // IR(49677, 16)
  "FixedRsqrtALTERA\0" // IR(49693, 17)
  "FixedRsqrtINTEL\0" // IR(49710, 16)
  "FixedSinALTERA\0" // IR(49726, 15)
  "FixedSinINTEL\0" // IR(49741, 14)
  "FixedCosALTERA\0" // IR(49755, 15)
  "FixedCosINTEL\0" // IR(49770, 14)
  "FixedSinCosALTERA\0" // IR(49784, 18)
  "FixedSinCosINTEL\0" // IR(49802, 17)
  "FixedSinPiALTERA\0" // IR(49819, 17)
  "FixedSinPiINTEL\0" // IR(49836, 16)
  "FixedCosPiALTERA\0" // IR(49852, 17)
  "FixedCosPiINTEL\0" // IR(49869, 16)
  "FixedSinCosPiALTERA\0" // IR(49885, 20)
  "FixedSinCosPiINTEL\0" // IR(49905, 19)
  "FixedLogALTERA\0" // IR(49924, 15)
  "FixedLogINTEL\0" // IR(49939, 14)
  "FixedExpALTERA\0" // IR(49953, 15)
  "FixedExpINTEL\0" // IR(49968, 14)
  "PtrCastToCrossWorkgroupALTERA\0" // IR(49982, 30)
  "PtrCastToCrossWorkgroupINTEL\0" // IR(50012, 29)
  "CrossWorkgroupCastToPtrALTERA\0" // IR(50041, 30)
  "CrossWorkgroupCastToPtrINTEL\0" // IR(50071, 29)
  "ReadPipeBlockingALTERA\0" // IR(50100, 23)
  "ReadPipeBlockingINTEL\0" // IR(50123, 22)
  "WritePipeBlockingALTERA\0" // IR(50145, 24)
  "WritePipeBlockingINTEL\0" // IR(50169, 23)
  "RayQueryGetRayTMinKHR\0" // IR(50192, 22)
  "RayQueryGetRayFlagsKHR\0" // IR(50214, 23)
  "RayQueryGetIntersectionTKHR\0" // IR(50237, 28)
  "RayQueryGetIntersectionInstanceCustomIndexKHR\0" // IR(50265, 46)
  "RayQueryGetIntersectionInstanceIdKHR\0" // IR(50311, 37)
  "RayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR\0" // IR(50348, 65)
  "RayQueryGetIntersectionGeometryIndexKHR\0" // IR(50413, 40)
  "RayQueryGetIntersectionPrimitiveIndexKHR\0" // IR(50453, 41)
  "RayQueryGetIntersectionBarycentricsKHR\0" // IR(50494, 39)
  "RayQueryGetIntersectionFrontFaceKHR\0" // IR(50533, 36)
  "RayQueryGetIntersectionCandidateAABBOpaqueKHR\0" // IR(50569, 46)
  "RayQueryGetIntersectionObjectRayDirectionKHR\0" // IR(50615, 45)
  "RayQueryGetIntersectionObjectRayOriginKHR\0" // IR(50660, 42)
  "RayQueryGetWorldRayDirectionKHR\0" // IR(50702, 32)
  "RayQueryGetWorldRayOriginKHR\0" // IR(50734, 29)
  "RayQueryGetIntersectionObjectToWorldKHR\0" // IR(50763, 40)
  "RayQueryGetIntersectionWorldToObjectKHR\0" // IR(50803, 40)
  "AtomicFAddEXT\0" // IR(50843, 14)
  "TypeBufferSurfaceINTEL\0" // IR(50857, 23)
  "TypeStructContinuedINTEL\0" // IR(50880, 25)
  "ConstantCompositeContinuedINTEL\0" // IR(50905, 32)
  "SpecConstantCompositeContinuedINTEL\0" // IR(50937, 36)
  "CompositeConstructContinuedINTEL\0" // IR(50973, 33)
  "ConvertFToBF16INTEL\0" // IR(51006, 20)
  "ConvertBF16ToFINTEL\0" // IR(51026, 20)
  "ControlBarrierArriveEXT\0" // IR(51046, 24)
  "ControlBarrierArriveINTEL\0" // IR(51070, 26)
  "ControlBarrierWaitEXT\0" // IR(51096, 22)
  "ControlBarrierWaitINTEL\0" // IR(51118, 24)
  "TaskSequenceCreateALTERA\0" // IR(51142, 25)
  "TaskSequenceCreateINTEL\0" // IR(51167, 24)
  "TaskSequenceAsyncALTERA\0" // IR(51191, 24)
  "TaskSequenceAsyncINTEL\0" // IR(51215, 23)
  "TaskSequenceGetALTERA\0" // IR(51238, 22)
  "TaskSequenceGetINTEL\0" // IR(51260, 21)
  "TaskSequenceReleaseALTERA\0" // IR(51281, 26)
  "TaskSequenceReleaseINTEL\0" // IR(51307, 25)
  "TypeTaskSequenceALTERA\0" // IR(51332, 23)
  "TypeTaskSequenceINTEL\0" // IR(51355, 22)
  "SubgroupBlockPrefetchINTEL\0" // IR(51377, 27)
  "Subgroup2DBlockLoadINTEL\0" // IR(51404, 25)
  "Subgroup2DBlockLoadTransformINTEL\0" // IR(51429, 34)
  "Subgroup2DBlockLoadTransposeINTEL\0" // IR(51463, 34)
  "Subgroup2DBlockPrefetchINTEL\0" // IR(51497, 29)
  "Subgroup2DBlockStoreINTEL\0" // IR(51526, 26)
  "SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS\0" // IR(51552, 62)
  "BitwiseFunctionINTEL\0" // IR(51614, 21)
  "ConditionalExtensionINTEL\0" // IR(51635, 26)
  "ConditionalEntryPointINTEL\0" // IR(51661, 27)
  "ConditionalCapabilityINTEL\0" // IR(51688, 27)
  "SpecConstantTargetINTEL\0" // IR(51715, 24)
  "SpecConstantArchitectureINTEL\0" // IR(51739, 30)
  "SPV_OPERAND_TYPE_VARIABLE_CAPABILITY\0" // IR(51769, 37)
  "SpecConstantCapabilitiesINTEL\0" // IR(51806, 30)
  "ConditionalCopyObjectINTEL\0" // IR(51836, 27)
  "PredicatedLoadINTEL\0" // IR(51863, 20)
  "PredicatedStoreINTEL\0" // IR(51883, 21)
  "GroupIMulKHR\0" // IR(51904, 13)
  "GroupFMulKHR\0" // IR(51917, 13)
  "GroupBitwiseAndKHR\0" // IR(51930, 19)
  "GroupBitwiseOrKHR\0" // IR(51949, 18)
  "GroupBitwiseXorKHR\0" // IR(51967, 19)
  "GroupLogicalAndKHR\0" // IR(51986, 19)
  "GroupLogicalOrKHR\0" // IR(52005, 18)
  "GroupLogicalXorKHR\0" // IR(52023, 19)
  "RoundFToTF32INTEL\0" // IR(52042, 18)
  "MaskedGatherINTEL\0" // IR(52060, 18)
  "MaskedScatterINTEL\0" // IR(52078, 19)
  "ConvertHandleToImageINTEL\0" // IR(52097, 26)
  "ConvertHandleToSamplerINTEL\0" // IR(52123, 28)
  "ConvertHandleToSampledImageINTEL\0" // IR(52151, 33)
  "FDot2MixAcc32VALVE\0" // IR(52184, 19)
  "FDot2MixAcc16VALVE\0" // IR(52203, 19)
  "FDot4MixAcc32VALVE\0" // IR(52222, 19)
  "DebugInfoNone\0" // IR(52241, 14)
  "DebugCompilationUnit\0" // IR(52255, 21)
  "SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING\0" // IR(52276, 52)
  "DebugTypeBasic\0" // IR(52328, 15)
  "SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS\0" // IR(52343, 34)
  "DebugTypePointer\0" // IR(52377, 17)
  "SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER\0" // IR(52394, 38)
  "DebugTypeQualifier\0" // IR(52432, 19)
  "DebugTypeArray\0" // IR(52451, 15)
  "DebugTypeVector\0" // IR(52466, 16)
  "DebugTypedef\0" // IR(52482, 13)
  "DebugTypeFunction\0" // IR(52495, 18)
  "DebugTypeEnum\0" // IR(52513, 14)
  "SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE\0" // IR(52527, 38)
  "DebugTypeComposite\0" // IR(52565, 19)
  "DebugTypeMember\0" // IR(52584, 16)
  "DebugTypeInheritance\0" // IR(52600, 21)
  "DebugTypePtrToMember\0" // IR(52621, 21)
  "DebugTypeTemplate\0" // IR(52642, 18)
  "DebugTypeTemplateParameter\0" // IR(52660, 27)
  "DebugTypeTemplateTemplateParameter\0" // IR(52687, 35)
  "DebugTypeTemplateParameterPack\0" // IR(52722, 31)
  "DebugGlobalVariable\0" // IR(52753, 20)
  "DebugFunctionDeclaration\0" // IR(52773, 25)
  "DebugFunction\0" // IR(52798, 14)
  "DebugLexicalBlock\0" // IR(52812, 18)
  "DebugLexicalBlockDiscriminator\0" // IR(52830, 31)
  "DebugScope\0" // IR(52861, 11)
  "DebugNoScope\0" // IR(52872, 13)
  "DebugInlinedAt\0" // IR(52885, 15)
  "SPV_OPERAND_TYPE_OPTIONAL_LITERAL_INTEGER\0" // IR(52900, 42)
  "DebugLocalVariable\0" // IR(52942, 19)
  "DebugInlinedVariable\0" // IR(52961, 21)
  "DebugDeclare\0" // IR(52982, 13)
  "DebugValue\0" // IR(52995, 11)
  "SPV_OPERAND_TYPE_DEBUG_OPERATION\0" // IR(53006, 33)
  "DebugOperation\0" // IR(53039, 15)
  "DebugExpression\0" // IR(53054, 16)
  "DebugMacroDef\0" // IR(53070, 14)
  "DebugMacroUndef\0" // IR(53084, 16)
  "Round\0" // IR(53100, 6)
  "RoundEven\0" // IR(53106, 10)
  "Trunc\0" // IR(53116, 6)
  "FAbs\0" // IR(53122, 5)
  "SAbs\0" // IR(53127, 5)
  "FSign\0" // IR(53132, 6)
  "SSign\0" // IR(53138, 6)
  "Floor\0" // IR(53144, 6)
  "Ceil\0" // IR(53150, 5)
  "Fract\0" // IR(53155, 6)
  "Radians\0" // IR(53161, 8)
  "Degrees\0" // IR(53169, 8)
  "Sin\0" // IR(53177, 4)
  "Cos\0" // IR(53181, 4)
  "Tan\0" // IR(53185, 4)
  "Asin\0" // IR(53189, 5)
  "Acos\0" // IR(53194, 5)
  "Atan\0" // IR(53199, 5)
  "Sinh\0" // IR(53204, 5)
  "Cosh\0" // IR(53209, 5)
  "Tanh\0" // IR(53214, 5)
  "Asinh\0" // IR(53219, 6)
  "Acosh\0" // IR(53225, 6)
  "Atanh\0" // IR(53231, 6)
  "Atan2\0" // IR(53237, 6)
  "Pow\0" // IR(53243, 4)
  "Exp\0" // IR(53247, 4)
  "Log\0" // IR(53251, 4)
  "Exp2\0" // IR(53255, 5)
  "Log2\0" // IR(53260, 5)
  "Sqrt\0" // IR(53265, 5)
  "InverseSqrt\0" // IR(53270, 12)
  "Determinant\0" // IR(53282, 12)
  "MatrixInverse\0" // IR(53294, 14)
  "Modf\0" // IR(53308, 5)
  "ModfStruct\0" // IR(53313, 11)
  "FMin\0" // IR(53324, 5)
  "UMin\0" // IR(53329, 5)
  "SMin\0" // IR(53334, 5)
  "FMax\0" // IR(53339, 5)
  "UMax\0" // IR(53344, 5)
  "SMax\0" // IR(53349, 5)
  "FClamp\0" // IR(53354, 7)
  "UClamp\0" // IR(53361, 7)
  "SClamp\0" // IR(53368, 7)
  "FMix\0" // IR(53375, 5)
  "IMix\0" // IR(53380, 5)
  "Step\0" // IR(53385, 5)
  "SmoothStep\0" // IR(53390, 11)
  "Fma\0" // IR(53401, 4)
  "Frexp\0" // IR(53405, 6)
  "FrexpStruct\0" // IR(53411, 12)
  "Ldexp\0" // IR(53423, 6)
  "PackSnorm4x8\0" // IR(53429, 13)
  "PackUnorm4x8\0" // IR(53442, 13)
  "PackSnorm2x16\0" // IR(53455, 14)
  "PackUnorm2x16\0" // IR(53469, 14)
  "PackHalf2x16\0" // IR(53483, 13)
  "PackDouble2x32\0" // IR(53496, 15)
  "UnpackSnorm2x16\0" // IR(53511, 16)
  "UnpackUnorm2x16\0" // IR(53527, 16)
  "UnpackHalf2x16\0" // IR(53543, 15)
  "UnpackSnorm4x8\0" // IR(53558, 15)
  "UnpackUnorm4x8\0" // IR(53573, 15)
  "UnpackDouble2x32\0" // IR(53588, 17)
  "Length\0" // IR(53605, 7)
  "Distance\0" // IR(53612, 9)
  "Cross\0" // IR(53621, 6)
  "Normalize\0" // IR(53627, 10)
  "FaceForward\0" // IR(53637, 12)
  "Reflect\0" // IR(53649, 8)
  "Refract\0" // IR(53657, 8)
  "FindILsb\0" // IR(53665, 9)
  "FindSMsb\0" // IR(53674, 9)
  "FindUMsb\0" // IR(53683, 9)
  "InterpolateAtCentroid\0" // IR(53692, 22)
  "InterpolateAtSample\0" // IR(53714, 20)
  "InterpolateAtOffset\0" // IR(53734, 20)
  "NMin\0" // IR(53754, 5)
  "NMax\0" // IR(53759, 5)
  "NClamp\0" // IR(53764, 7)
  "ArgumentInfo\0" // IR(53771, 13)
  "ArgumentStorageBuffer\0" // IR(53784, 22)
  "ArgumentUniform\0" // IR(53806, 16)
  "ArgumentPodStorageBuffer\0" // IR(53822, 25)
  "ArgumentPodUniform\0" // IR(53847, 19)
  "ArgumentPodPushConstant\0" // IR(53866, 24)
  "ArgumentSampledImage\0" // IR(53890, 21)
  "ArgumentStorageImage\0" // IR(53911, 21)
  "ArgumentSampler\0" // IR(53932, 16)
  "ArgumentWorkgroup\0" // IR(53948, 18)
  "SpecConstantWorkgroupSize\0" // IR(53966, 26)
  "SpecConstantGlobalOffset\0" // IR(53992, 25)
  "SpecConstantWorkDim\0" // IR(54017, 20)
  "PushConstantGlobalOffset\0" // IR(54037, 25)
  "PushConstantEnqueuedLocalSize\0" // IR(54062, 30)
  "PushConstantGlobalSize\0" // IR(54092, 23)
  "PushConstantRegionOffset\0" // IR(54115, 25)
  "PushConstantNumWorkgroups\0" // IR(54140, 26)
  "PushConstantRegionGroupOffset\0" // IR(54166, 30)
  "ConstantDataStorageBuffer\0" // IR(54196, 26)
  "ConstantDataUniform\0" // IR(54222, 20)
  "PropertyRequiredWorkgroupSize\0" // IR(54242, 30)
  "SpecConstantSubgroupMaxSize\0" // IR(54272, 28)
  "ArgumentPointerPushConstant\0" // IR(54300, 28)
  "ArgumentPointerUniform\0" // IR(54328, 23)
  "ProgramScopeVariablesStorageBuffer\0" // IR(54351, 35)
  "ProgramScopeVariablePointerRelocation\0" // IR(54386, 38)
  "ImageArgumentInfoChannelOrderPushConstant\0" // IR(54424, 42)
  "ImageArgumentInfoChannelDataTypePushConstant\0" // IR(54466, 45)
  "ImageArgumentInfoChannelOrderUniform\0" // IR(54511, 37)
  "ImageArgumentInfoChannelDataTypeUniform\0" // IR(54548, 40)
  "ArgumentStorageTexelBuffer\0" // IR(54588, 27)
  "ArgumentUniformTexelBuffer\0" // IR(54615, 27)
  "ConstantDataPointerPushConstant\0" // IR(54642, 32)
  "ProgramScopeVariablePointerPushConstant\0" // IR(54674, 40)
  "PrintfInfo\0" // IR(54714, 11)
  "PrintfBufferStorageBuffer\0" // IR(54725, 26)
  "PrintfBufferPointerPushConstant\0" // IR(54751, 32)
  "NormalizedSamplerMaskPushConstant\0" // IR(54783, 34)
  "WorkgroupVariableSize\0" // IR(54817, 22)
  "DebugImportedEntity\0" // IR(54839, 20)
  "DebugSource\0" // IR(54859, 12)
  "DebugFunctionDefinition\0" // IR(54871, 24)
  "DebugSourceContinued\0" // IR(54895, 21)
  "DebugLine\0" // IR(54916, 10)
  "DebugNoLine\0" // IR(54926, 12)
  "DebugBuildIdentifier\0" // IR(54938, 21)
  "DebugStoragePath\0" // IR(54959, 17)
  "DebugEntryPoint\0" // IR(54976, 16)
  "DebugTypeMatrix\0" // IR(54992, 16)
  "Configuration\0" // IR(55008, 14)
  "StartCounter\0" // IR(55022, 13)
  "StopCounter\0" // IR(55035, 12)
  "PushConstants\0" // IR(55047, 14)
  "SpecializationMapEntry\0" // IR(55061, 23)
  "DescriptorSetBuffer\0" // IR(55084, 20)
  "DescriptorSetImage\0" // IR(55104, 19)
  "DescriptorSetSampler\0" // IR(55123, 21)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING\0" // IR(55144, 63)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS\0" // IR(55207, 45)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER\0" // IR(55252, 49)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE\0" // IR(55301, 49)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION\0" // IR(55350, 44)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY\0" // IR(55394, 50)
  "DebugModuleINTEL\0" // IR(55444, 17)
  "acos\0" // IR(55461, 5)
  "acosh\0" // IR(55466, 6)
  "acospi\0" // IR(55472, 7)
  "asin\0" // IR(55479, 5)
  "asinh\0" // IR(55484, 6)
  "asinpi\0" // IR(55490, 7)
  "atan\0" // IR(55497, 5)
  "atan2\0" // IR(55502, 6)
  "atanh\0" // IR(55508, 6)
  "atanpi\0" // IR(55514, 7)
  "atan2pi\0" // IR(55521, 8)
  "cbrt\0" // IR(55529, 5)
  "ceil\0" // IR(55534, 5)
  "copysign\0" // IR(55539, 9)
  "cos\0" // IR(55548, 4)
  "cosh\0" // IR(55552, 5)
  "cospi\0" // IR(55557, 6)
  "erfc\0" // IR(55563, 5)
  "erf\0" // IR(55568, 4)
  "exp\0" // IR(55572, 4)
  "exp2\0" // IR(55576, 5)
  "exp10\0" // IR(55581, 6)
  "expm1\0" // IR(55587, 6)
  "fabs\0" // IR(55593, 5)
  "fdim\0" // IR(55598, 5)
  "floor\0" // IR(55603, 6)
  "fma\0" // IR(55609, 4)
  "fmax\0" // IR(55613, 5)
  "fmin\0" // IR(55618, 5)
  "fmod\0" // IR(55623, 5)
  "fract\0" // IR(55628, 6)
  "frexp\0" // IR(55634, 6)
  "hypot\0" // IR(55640, 6)
  "ilogb\0" // IR(55646, 6)
  "ldexp\0" // IR(55652, 6)
  "lgamma\0" // IR(55658, 7)
  "lgamma_r\0" // IR(55665, 9)
  "log\0" // IR(55674, 4)
  "log2\0" // IR(55678, 5)
  "log10\0" // IR(55683, 6)
  "log1p\0" // IR(55689, 6)
  "logb\0" // IR(55695, 5)
  "mad\0" // IR(55700, 4)
  "maxmag\0" // IR(55704, 7)
  "minmag\0" // IR(55711, 7)
  "modf\0" // IR(55718, 5)
  "nan\0" // IR(55723, 4)
  "nextafter\0" // IR(55727, 10)
  "pow\0" // IR(55737, 4)
  "pown\0" // IR(55741, 5)
  "powr\0" // IR(55746, 5)
  "remainder\0" // IR(55751, 10)
  "remquo\0" // IR(55761, 7)
  "rint\0" // IR(55768, 5)
  "rootn\0" // IR(55773, 6)
  "round\0" // IR(55779, 6)
  "rsqrt\0" // IR(55785, 6)
  "sin\0" // IR(55791, 4)
  "sincos\0" // IR(55795, 7)
  "sinh\0" // IR(55802, 5)
  "sinpi\0" // IR(55807, 6)
  "sqrt\0" // IR(55813, 5)
  "tan\0" // IR(55818, 4)
  "tanh\0" // IR(55822, 5)
  "tanpi\0" // IR(55827, 6)
  "tgamma\0" // IR(55833, 7)
  "trunc\0" // IR(55840, 6)
  "half_cos\0" // IR(55846, 9)
  "half_divide\0" // IR(55855, 12)
  "half_exp\0" // IR(55867, 9)
  "half_exp2\0" // IR(55876, 10)
  "half_exp10\0" // IR(55886, 11)
  "half_log\0" // IR(55897, 9)
  "half_log2\0" // IR(55906, 10)
  "half_log10\0" // IR(55916, 11)
  "half_powr\0" // IR(55927, 10)
  "half_recip\0" // IR(55937, 11)
  "half_rsqrt\0" // IR(55948, 11)
  "half_sin\0" // IR(55959, 9)
  "half_sqrt\0" // IR(55968, 10)
  "half_tan\0" // IR(55978, 9)
  "native_cos\0" // IR(55987, 11)
  "native_divide\0" // IR(55998, 14)
  "native_exp\0" // IR(56012, 11)
  "native_exp2\0" // IR(56023, 12)
  "native_exp10\0" // IR(56035, 13)
  "native_log\0" // IR(56048, 11)
  "native_log2\0" // IR(56059, 12)
  "native_log10\0" // IR(56071, 13)
  "native_powr\0" // IR(56084, 12)
  "native_recip\0" // IR(56096, 13)
  "native_rsqrt\0" // IR(56109, 13)
  "native_sin\0" // IR(56122, 11)
  "native_sqrt\0" // IR(56133, 12)
  "native_tan\0" // IR(56145, 11)
  "fclamp\0" // IR(56156, 7)
  "degrees\0" // IR(56163, 8)
  "fmax_common\0" // IR(56171, 12)
  "fmin_common\0" // IR(56183, 12)
  "mix\0" // IR(56195, 4)
  "radians\0" // IR(56199, 8)
  "step\0" // IR(56207, 5)
  "smoothstep\0" // IR(56212, 11)
  "sign\0" // IR(56223, 5)
  "cross\0" // IR(56228, 6)
  "distance\0" // IR(56234, 9)
  "length\0" // IR(56243, 7)
  "normalize\0" // IR(56250, 10)
  "fast_distance\0" // IR(56260, 14)
  "fast_length\0" // IR(56274, 12)
  "fast_normalize\0" // IR(56286, 15)
  "s_abs\0" // IR(56301, 6)
  "s_abs_diff\0" // IR(56307, 11)
  "s_add_sat\0" // IR(56318, 10)
  "u_add_sat\0" // IR(56328, 10)
  "s_hadd\0" // IR(56338, 7)
  "u_hadd\0" // IR(56345, 7)
  "s_rhadd\0" // IR(56352, 8)
  "u_rhadd\0" // IR(56360, 8)
  "s_clamp\0" // IR(56368, 8)
  "u_clamp\0" // IR(56376, 8)
  "clz\0" // IR(56384, 4)
  "ctz\0" // IR(56388, 4)
  "s_mad_hi\0" // IR(56392, 9)
  "u_mad_sat\0" // IR(56401, 10)
  "s_mad_sat\0" // IR(56411, 10)
  "s_max\0" // IR(56421, 6)
  "u_max\0" // IR(56427, 6)
  "s_min\0" // IR(56433, 6)
  "u_min\0" // IR(56439, 6)
  "s_mul_hi\0" // IR(56445, 9)
  "rotate\0" // IR(56454, 7)
  "s_sub_sat\0" // IR(56461, 10)
  "u_sub_sat\0" // IR(56471, 10)
  "u_upsample\0" // IR(56481, 11)
  "s_upsample\0" // IR(56492, 11)
  "popcount\0" // IR(56503, 9)
  "s_mad24\0" // IR(56512, 8)
  "u_mad24\0" // IR(56520, 8)
  "s_mul24\0" // IR(56528, 8)
  "u_mul24\0" // IR(56536, 8)
  "vloadn\0" // IR(56544, 7)
  "vstoren\0" // IR(56551, 8)
  "vload_half\0" // IR(56559, 11)
  "vload_halfn\0" // IR(56570, 12)
  "vstore_half\0" // IR(56582, 12)
  "vstore_half_r\0" // IR(56594, 14)
  "vstore_halfn\0" // IR(56608, 13)
  "vstore_halfn_r\0" // IR(56621, 15)
  "vloada_halfn\0" // IR(56636, 13)
  "vstorea_halfn\0" // IR(56649, 14)
  "vstorea_halfn_r\0" // IR(56663, 16)
  "shuffle\0" // IR(56679, 8)
  "shuffle2\0" // IR(56687, 9)
  "printf\0" // IR(56696, 7)
  "prefetch\0" // IR(56703, 9)
  "bitselect\0" // IR(56712, 10)
  "select\0" // IR(56722, 7)
  "u_abs\0" // IR(56729, 6)
  "u_abs_diff\0" // IR(56735, 11)
  "u_mul_hi\0" // IR(56746, 9)
  "u_mad_hi\0" // IR(56755, 9)
  "CubeFaceIndexAMD\0" // IR(56764, 17)
  "CubeFaceCoordAMD\0" // IR(56781, 17)
  "TimeAMD\0" // IR(56798, 8)
  "SwizzleInvocationsAMD\0" // IR(56806, 22)
  "SwizzleInvocationsMaskedAMD\0" // IR(56828, 28)
  "WriteInvocationAMD\0" // IR(56856, 19)
  "MbcntAMD\0" // IR(56875, 9)
  "InterpolateAtVertexAMD\0" // IR(56884, 23)
  "FMin3AMD\0" // IR(56907, 9)
  "UMin3AMD\0" // IR(56916, 9)
  "SMin3AMD\0" // IR(56925, 9)
  "FMax3AMD\0" // IR(56934, 9)
  "UMax3AMD\0" // IR(56943, 9)
  "SMax3AMD\0" // IR(56952, 9)
  "FMid3AMD\0" // IR(56961, 9)
  "UMid3AMD\0" // IR(56970, 9)
  "SMid3AMD\0" // IR(56979, 9)
;

// Array of IndexRanges, where each represents a string by referencing
// the kStrings table.
// This array contains all sequences of alias strings used in the grammar.
// This table is referenced by an IndexRange elsewhere, i.e. by the 'aliases'
// field of an instruction or operand description.
static const IndexRange kAliasSpans[] = {
  IR(6006, 27), // 0 PhysicalStorageBuffer64EXT
  IR(6917, 18), // 1 SubgroupEqMaskKHR
  IR(6972, 18), // 2 SubgroupGeMaskKHR
  IR(7005, 18), // 3 SubgroupGtMaskKHR
  IR(7038, 18), // 4 SubgroupLeMaskKHR
  IR(7071, 18), // 5 SubgroupLtMaskKHR
  IR(7978, 12), // 6 BaryCoordNV
  IR(8033, 19), // 7 BaryCoordNoPerspNV
  IR(8064, 15), // 8 FragmentSizeNV
  IR(8121, 22), // 9 InvocationsPerPixelNV
  IR(8249, 11), // 10 LaunchIdNV
  IR(8274, 13), // 11 LaunchSizeNV
  IR(8305, 17), // 12 WorldRayOriginNV
  IR(8343, 20), // 13 WorldRayDirectionNV
  IR(8382, 18), // 14 ObjectRayOriginNV
  IR(8422, 21), // 15 ObjectRayDirectionNV
  IR(8454, 10), // 16 RayTminNV
  IR(8475, 10), // 17 RayTmaxNV
  IR(8508, 22), // 18 InstanceCustomIndexNV
  IR(8547, 16), // 19 ObjectToWorldNV
  IR(8580, 16), // 20 WorldToObjectNV
  IR(8614, 10), // 21 HitKindNV
  IR(8845, 19), // 22 IncomingRayFlagsNV
  IR(10691, 28), // 23 StorageUniformBufferBlock16
  IR(10754, 17), // 24 StorageUniform16
  IR(11735, 27), // 25 ShaderViewportIndexLayerNV
  IR(11779, 22), // 26 FragmentBarycentricNV
  IR(11832, 30), // 27 ComputeDerivativeGroupQuadsNV
  IR(11862, 14), // 28 ShadingRateNV
  IR(11906, 29), // 29 GroupNonUniformPartitionedNV
  IR(11952, 20), // 30 ShaderNonUniformEXT
  IR(11995, 26), // 31 RuntimeDescriptorArrayEXT
  IR(12057, 39), // 32 InputAttachmentArrayDynamicIndexingEXT
  IR(12135, 42), // 33 UniformTexelBufferArrayDynamicIndexingEXT
  IR(12216, 42), // 34 StorageTexelBufferArrayDynamicIndexingEXT
  IR(12295, 40), // 35 UniformBufferArrayNonUniformIndexingEXT
  IR(12371, 39), // 36 SampledImageArrayNonUniformIndexingEXT
  IR(12447, 40), // 37 StorageBufferArrayNonUniformIndexingEXT
  IR(12523, 39), // 38 StorageImageArrayNonUniformIndexingEXT
  IR(12601, 42), // 39 InputAttachmentArrayNonUniformIndexingEXT
  IR(12685, 45), // 40 UniformTexelBufferArrayNonUniformIndexingEXT
  IR(12772, 45), // 41 StorageTexelBufferArrayNonUniformIndexingEXT
  IR(12835, 21), // 42 VulkanMemoryModelKHR
  IR(12885, 32), // 43 VulkanMemoryModelDeviceScopeKHR
  IR(12917, 34), // 44 PhysicalStorageBufferAddressesEXT
  IR(12983, 31), // 45 ComputeDerivativeGroupLinearNV
  IR(13187, 28), // 46 DemoteToHelperInvocationEXT
  IR(13267, 29), // 47 RayTracingOpacityMicromapEXT
  IR(13572, 30), // 48 CooperativeMatrixReductionsNV
  IR(13674, 40), // 49 CooperativeMatrixPerElementOperationsNV
  IR(14427, 26), // 50 FPGAMemoryAttributesINTEL
  IR(14506, 32), // 51 ArbitraryPrecisionIntegersINTEL
  IR(14576, 37), // 52 ArbitraryPrecisionFloatingPointINTEL
  IR(14666, 22), // 53 FPGALoopControlsINTEL
  IR(14761, 24), // 54 FPGAMemoryAccessesINTEL
  IR(14813, 27), // 55 FPGAClusterAttributesINTEL
  IR(14855, 14), // 56 LoopFuseINTEL
  IR(14890, 20), // 57 FPGADSPControlINTEL
  IR(14977, 40), // 58 FPGAInvocationPipeliningAttributesINTEL
  IR(15042, 24), // 59 FPGABufferLocationINTEL
  IR(15101, 34), // 60 ArbitraryPrecisionFixedPointINTEL
  IR(15159, 23), // 61 USMStorageClassesINTEL
  IR(15212, 29), // 62 RuntimeAlignedAttributeINTEL
  IR(15255, 13), // 63 IOPipesINTEL
  IR(15288, 19), // 64 BlockingPipesINTEL
  IR(15321, 13), // 65 FPGARegINTEL
  IR(15353, 22), // 66 DotProductInputAllKHR
  IR(15397, 25), // 67 DotProductInput4x8BitKHR
  IR(15450, 31), // 68 DotProductInput4x8BitPackedKHR
  IR(15492, 14), // 69 DotProductKHR
  IR(15706, 13), // 70 OptNoneINTEL
  IR(15800, 18), // 71 SplitBarrierINTEL
  IR(15867, 29), // 72 FPGAClusterAttributesV2INTEL
  IR(15943, 18), // 73 TaskSequenceINTEL
  IR(16002, 24), // 74 FPGALatencyControlINTEL
  IR(16055, 28), // 75 FPGAArgumentInterfacesINTEL
  IR(16149, 35), // 76 GlobalVariableFPGADecorationsINTEL
  IR(19158, 15), // 77 PerPrimitiveNV
  IR(19206, 12), // 78 PerVertexNV
  IR(19229, 14), // 79 NonUniformEXT
  IR(19259, 19), // 80 RestrictPointerEXT
  IR(19293, 18), // 81 AliasedPointerEXT
  IR(19686, 24), // 82 HlslCounterBufferGOOGLE
  IR(19723, 19), // 83 HlslSemanticGOOGLE
  IR(19853, 14), // 84 RegisterINTEL
  IR(19880, 12), // 85 MemoryINTEL
  IR(19907, 14), // 86 NumbanksINTEL
  IR(19937, 15), // 87 BankwidthINTEL
  IR(19975, 22), // 88 MaxPrivateCopiesINTEL
  IR(20014, 16), // 89 SinglepumpINTEL
  IR(20047, 16), // 90 DoublepumpINTEL
  IR(20083, 19), // 91 MaxReplicatesINTEL
  IR(20123, 20), // 92 SimpleDualPortINTEL
  IR(20155, 11), // 93 MergeINTEL
  IR(20223, 14), // 94 BankBitsINTEL
  IR(20258, 20), // 95 ForcePow2DepthINTEL
  IR(20295, 16), // 96 StridesizeINTEL
  IR(20326, 14), // 97 WordsizeINTEL
  IR(20359, 18), // 98 TrueDualPortINTEL
  IR(20397, 19), // 99 BurstCoalesceINTEL
  IR(20432, 15), // 100 CacheSizeINTEL
  IR(20476, 28), // 101 DontStaticallyCoalesceINTEL
  IR(20519, 14), // 102 PrefetchINTEL
  IR(20551, 17), // 103 StallEnableINTEL
  IR(20594, 25), // 104 FuseLoopsInFunctionINTEL
  IR(20639, 19), // 105 MathOpDSPModeINTEL
  IR(20712, 24), // 106 InitiationIntervalINTEL
  IR(20757, 20), // 107 MaxConcurrencyINTEL
  IR(20798, 20), // 108 PipelineEnableINTEL
  IR(20839, 20), // 109 BufferLocationINTEL
  IR(20879, 19), // 110 IOPipeStorageINTEL
  IR(21057, 15), // 111 StallFreeINTEL
  IR(21155, 25), // 112 LatencyControlLabelINTEL
  IR(21211, 30), // 113 LatencyControlConstraintINTEL
  IR(21269, 27), // 114 ConduitKernelArgumentINTEL
  IR(21328, 31), // 115 RegisterMapKernelArgumentINTEL
  IR(21393, 33), // 116 MMHostInterfaceAddressWidthINTEL
  IR(21457, 30), // 117 MMHostInterfaceDataWidthINTEL
  IR(21516, 28), // 118 MMHostInterfaceLatencyINTEL
  IR(21613, 34), // 119 MMHostInterfaceReadWriteModeINTEL
  IR(21677, 29), // 120 MMHostInterfaceMaxBurstINTEL
  IR(21739, 32), // 121 MMHostInterfaceWaitRequestINTEL
  IR(21798, 26), // 122 StableKernelArgumentINTEL
  IR(21941, 14), // 123 InitModeINTEL
  IR(21984, 28), // 124 ImplementInRegisterMapINTEL
  IR(23380, 14), // 125 OutputLinesNV
  IR(23414, 19), // 126 OutputPrimitivesNV
  IR(23457, 23), // 127 DerivativeGroupQuadsNV
  IR(23505, 24), // 128 DerivativeGroupLinearNV
  IR(23548, 18), // 129 OutputTrianglesNV
  IR(24317, 16), // 130 RayGenerationNV
  IR(24349, 15), // 131 IntersectionNV
  IR(24374, 9), // 132 AnyHitNV
  IR(24397, 13), // 133 ClosestHitNV
  IR(24418, 7), // 134 MissNV
  IR(24437, 11), // 135 CallableNV
  IR(24624, 23), // 136 AllowContractFastINTEL
  IR(24660, 18), // 137 AllowReassocINTEL
  IR(24886, 20), // 138 RuntimeAlignedINTEL
  IR(25030, 20), // 139 PartitionedReduceNV
  IR(25078, 27), // 140 PartitionedInclusiveScanNV
  IR(25133, 27), // 141 PartitionedExclusiveScanNV
  IR(25264, 22), // 142 MakeTexelAvailableKHR
  IR(25303, 20), // 143 MakeTexelVisibleKHR
  IR(25339, 19), // 144 NonPrivateTexelKHR
  IR(25372, 17), // 145 VolatileTexelKHR
  IR(25931, 27), // 146 InitOnDeviceReprogramINTEL
  IR(25982, 23), // 147 InitOnDeviceResetINTEL
  IR(26324, 21), // 148 DependencyArrayINTEL
  IR(26364, 18), // 149 LoopCoalesceINTEL
  IR(26404, 21), // 150 MaxInterleavingINTEL
  IR(26452, 26), // 151 SpeculatedIterationsINTEL
  IR(26493, 14), // 152 NoFusionINTEL
  IR(26523, 15), // 153 LoopCountINTEL
  IR(26565, 26), // 154 MaxReinvocationDelayINTEL
  IR(26957, 24), // 155 MakePointerAvailableKHR
  IR(27000, 22), // 156 MakePointerVisibleKHR
  IR(27040, 21), // 157 NonPrivatePointerKHR
  IR(27127, 10), // 158 VulkanKHR
  IR(16887, 5), // 159 None
  IR(27310, 16), // 160 OutputMemoryKHR
  IR(27340, 17), // 161 MakeAvailableKHR
  IR(27369, 15), // 162 MakeVisibleKHR
  IR(27445, 28), // 163 PackedVectorFormat4x8BitKHR
  IR(27760, 24), // 164 SkipBuiltinPrimitivesNV
  IR(27827, 30), // 165 ForceOpacityMicromap2StateEXT
  IR(28530, 15), // 166 QueueFamilyKHR
  IR(28915, 15), // 167 CallableDataNV
  IR(28954, 23), // 168 IncomingCallableDataNV
  IR(28991, 13), // 169 RayPayloadNV
  IR(29020, 15), // 170 HitAttributeNV
  IR(29057, 21), // 171 IncomingRayPayloadNV
  IR(29100, 21), // 172 ShaderRecordBufferNV
  IR(29143, 25), // 173 PhysicalStorageBufferEXT
  IR(29269, 16), // 174 DeviceOnlyINTEL
  IR(29300, 14), // 175 HostOnlyINTEL
  IR(36555, 8), // 176 SDotKHR
  IR(36568, 8), // 177 UDotKHR
  IR(36582, 9), // 178 SUDotKHR
  IR(36602, 14), // 179 SDotAccSatKHR
  IR(36627, 14), // 180 UDotAccSatKHR
  IR(36653, 15), // 181 SUDotAccSatKHR
  IR(38970, 24), // 182 TypeCooperativeVectorNV
  IR(39167, 27), // 183 CooperativeMatrixConvertNV
  IR(39257, 27), // 184 GroupNonUniformPartitionNV
  IR(40339, 21), // 185 ReportIntersectionNV
  IR(40514, 28), // 186 TypeAccelerationStructureNV
  IR(40595, 23), // 187 RayQueryGetClusterIdNV
  IR(41056, 26), // 188 CooperativeMatrixReduceNV
  IR(41251, 32), // 189 CooperativeMatrixPerElementOpNV
  IR(42823, 21), // 190 DecorateStringGOOGLE
  IR(42865, 27), // 191 MemberDecorateStringGOOGLE
  IR(48122, 28), // 192 ArbitraryFloatSinCosPiINTEL
  IR(48175, 24), // 193 ArbitraryFloatCastINTEL
  IR(48231, 31), // 194 ArbitraryFloatCastFromIntINTEL
  IR(48292, 29), // 195 ArbitraryFloatCastToIntINTEL
  IR(48345, 23), // 196 ArbitraryFloatAddINTEL
  IR(48392, 23), // 197 ArbitraryFloatSubINTEL
  IR(48439, 23), // 198 ArbitraryFloatMulINTEL
  IR(48486, 23), // 199 ArbitraryFloatDivINTEL
  IR(48532, 22), // 200 ArbitraryFloatGTINTEL
  IR(48577, 22), // 201 ArbitraryFloatGEINTEL
  IR(48622, 22), // 202 ArbitraryFloatLTINTEL
  IR(48667, 22), // 203 ArbitraryFloatLEINTEL
  IR(48712, 22), // 204 ArbitraryFloatEQINTEL
  IR(48760, 25), // 205 ArbitraryFloatRecipINTEL
  IR(48811, 25), // 206 ArbitraryFloatRSqrtINTEL
  IR(48861, 24), // 207 ArbitraryFloatCbrtINTEL
  IR(48911, 25), // 208 ArbitraryFloatHypotINTEL
  IR(48961, 24), // 209 ArbitraryFloatSqrtINTEL
  IR(49645, 15), // 210 FixedSqrtINTEL
  IR(49677, 16), // 211 FixedRecipINTEL
  IR(49710, 16), // 212 FixedRsqrtINTEL
  IR(49741, 14), // 213 FixedSinINTEL
  IR(49770, 14), // 214 FixedCosINTEL
  IR(49802, 17), // 215 FixedSinCosINTEL
  IR(49836, 16), // 216 FixedSinPiINTEL
  IR(49869, 16), // 217 FixedCosPiINTEL
  IR(49905, 19), // 218 FixedSinCosPiINTEL
  IR(49939, 14), // 219 FixedLogINTEL
  IR(49968, 14), // 220 FixedExpINTEL
  IR(50012, 29), // 221 PtrCastToCrossWorkgroupINTEL
  IR(50071, 29), // 222 CrossWorkgroupCastToPtrINTEL
  IR(50123, 22), // 223 ReadPipeBlockingINTEL
  IR(50169, 23), // 224 WritePipeBlockingINTEL
  IR(51070, 26), // 225 ControlBarrierArriveINTEL
  IR(51118, 24), // 226 ControlBarrierWaitINTEL
  IR(51167, 24), // 227 TaskSequenceCreateINTEL
  IR(51215, 23), // 228 TaskSequenceAsyncINTEL
  IR(51260, 21), // 229 TaskSequenceGetINTEL
  IR(51307, 25), // 230 TaskSequenceReleaseINTEL
  IR(51355, 22), // 231 TypeTaskSequenceINTEL
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
  spv::Capability::Linkage, // 94
  spv::Capability::MultiViewport, // 95
  spv::Capability::ShaderViewportIndexLayerEXT, // 96
  spv::Capability::ShaderViewportMaskNV, // 97
  spv::Capability::InputAttachment, // 98
  spv::Capability::ImageBuffer, // 99
  spv::Capability::ShaderNonUniform, // 100
  spv::Capability::InputAttachment, // 101
  spv::Capability::ShaderNonUniform, // 102
  spv::Capability::SampledBuffer, // 103
  spv::Capability::ShaderNonUniform, // 104
  spv::Capability::ImageBuffer, // 105
  spv::Capability::ShaderNonUniform, // 106
  spv::Capability::CooperativeMatrixBlockLoadsNV, // 107
  spv::Capability::VectorAnyINTEL, // 108
  spv::Capability::Int8, // 109
  spv::Capability::FPGAClusterAttributesALTERA, // 110
  spv::Capability::FPGAKernelAttributesINTEL, // 111
  spv::Capability::Subgroup2DBlockIOINTEL, // 112
  spv::Capability::VariableLengthArrayINTEL, // 113
  spv::Capability::UntypedPointersKHR, // 114
  spv::Capability::SpecConditionalINTEL, // 115
  spv::Capability::Float16, // 116
  spv::Capability::Float8EXT, // 117
  spv::Capability::CooperativeMatrixLayoutsARM, // 118
  spv::Capability::Shader, // 119
  spv::Capability::Kernel, // 120
  spv::Capability::Shader, // 121
  spv::Capability::UniformDecoration, // 122
  spv::Capability::GeometryStreams, // 123
  spv::Capability::TransformFeedback, // 124
  spv::Capability::Kernel, // 125
  spv::Capability::FloatControls2, // 126
  spv::Capability::ConstantDataKHR, // 127
  spv::Capability::SampleMaskOverrideCoverageNV, // 128
  spv::Capability::GeometryShaderPassthroughNV, // 129
  spv::Capability::MeshShadingNV, // 130
  spv::Capability::MeshShadingEXT, // 131
  spv::Capability::PushConstantBanksNV, // 132
  spv::Capability::ShaderInvocationReorderNV, // 133
  spv::Capability::ShaderInvocationReorderEXT, // 134
  spv::Capability::BindlessTextureNV, // 135
  spv::Capability::CooperativeMatrixConversionsEXT, // 136
  spv::Capability::VectorComputeINTEL, // 137
  spv::Capability::IndirectReferencesINTEL, // 138
  spv::Capability::AsmINTEL, // 139
  spv::Capability::FunctionFloatControlINTEL, // 140
  spv::Capability::FPGAMemoryAttributesALTERA, // 141
  spv::Capability::FPGAMemoryAccessesALTERA, // 142
  spv::Capability::LoopFuseALTERA, // 143
  spv::Capability::FPGADSPControlALTERA, // 144
  spv::Capability::MemoryAccessAliasingINTEL, // 145
  spv::Capability::FPGAInvocationPipeliningAttributesALTERA, // 146
  spv::Capability::FPGABufferLocationALTERA, // 147
  spv::Capability::IOPipesALTERA, // 148
  spv::Capability::FPGAClusterAttributesV2ALTERA, // 149
  spv::Capability::FPMaxErrorINTEL, // 150
  spv::Capability::FPGALatencyControlALTERA, // 151
  spv::Capability::FPGAArgumentInterfacesALTERA, // 152
  spv::Capability::GlobalVariableHostAccessINTEL, // 153
  spv::Capability::GlobalVariableFPGADecorationsALTERA, // 154
  spv::Capability::CacheControlsINTEL, // 155
  spv::Capability::IntrinsicSAMSUNG, // 156
  spv::Capability::TileImageColorReadAccessEXT, // 157
  spv::Capability::Geometry, // 158
  spv::Capability::Tessellation, // 159
  spv::Capability::MeshShadingNV, // 160
  spv::Capability::MeshShadingEXT, // 161
  spv::Capability::Geometry, // 162
  spv::Capability::MeshShadingNV, // 163
  spv::Capability::MeshShadingEXT, // 164
  spv::Capability::SubgroupDispatch, // 165
  spv::Capability::TileImageDepthReadAccessEXT, // 166
  spv::Capability::TileImageStencilReadAccessEXT, // 167
  spv::Capability::SampleMaskPostDepthCoverage, // 168
  spv::Capability::DenormPreserve, // 169
  spv::Capability::DenormFlushToZero, // 170
  spv::Capability::SignedZeroInfNanPreserve, // 171
  spv::Capability::RoundingModeRTE, // 172
  spv::Capability::RoundingModeRTZ, // 173
  spv::Capability::SubgroupSizeQCOM, // 174
  spv::Capability::QuadControlKHR, // 175
  spv::Capability::PoisonFreezeKHR, // 176
  spv::Capability::ComputeDerivativeGroupQuadsKHR, // 177
  spv::Capability::ComputeDerivativeGroupLinearKHR, // 178
  spv::Capability::FragmentShaderPixelInterlockEXT, // 179
  spv::Capability::FragmentShaderSampleInterlockEXT, // 180
  spv::Capability::FragmentShaderShadingRateInterlockEXT, // 181
  spv::Capability::Shader64BitIndexingEXT, // 182
  spv::Capability::RoundToInfinityINTEL, // 183
  spv::Capability::KernelAttributesINTEL, // 184
  spv::Capability::FloatControls2, // 185
  spv::Capability::RayTracingOpacityMicromapExecutionModeKHR, // 186
  spv::Capability::FPGAKernelAttributesv2INTEL, // 187
  spv::Capability::RegisterLimitsINTEL, // 188
  spv::Capability::Float6EXT, // 189
  spv::Capability::Float4EXT, // 190
  spv::Capability::Float8UnsignedE8M0EXT, // 191
  spv::Capability::MXInt8EXT, // 192
  spv::Capability::FloatControls2, // 193
  spv::Capability::FPFastMathModeINTEL, // 194
  spv::Capability::OptNoneEXT, // 195
  spv::Capability::RuntimeAlignedAttributeALTERA, // 196
  spv::Capability::Kernel, // 197
  spv::Capability::GroupNonUniformArithmetic, // 198
  spv::Capability::GroupNonUniformBallot, // 199
  spv::Capability::GroupNonUniformClustered, // 200
  spv::Capability::GroupNonUniformPartitionedEXT, // 201
  spv::Capability::ImageGatherExtended, // 202
  spv::Capability::MinLod, // 203
  spv::Capability::VulkanMemoryModel, // 204
  spv::Capability::WeakLinkageAMD, // 205
  spv::Capability::FPGALoopControlsALTERA, // 206
  spv::Capability::ArbitraryPrecisionFixedPointALTERA, // 207
  spv::Capability::RawAccessChainsNV, // 208
  spv::Capability::RayTraversalPrimitiveCullingKHR, // 209
  spv::Capability::RayTracingOpacityMicromapKHR, // 210
  spv::Capability::RayQueryKHR, // 211
  spv::Capability::StorageImageExtendedFormats, // 212
  spv::Capability::Int64ImageEXT, // 213
  spv::Capability::Shader, // 214
  spv::Capability::VectorComputeINTEL, // 215
  spv::Capability::GenericPointer, // 216
  spv::Capability::FunctionPointersINTEL, // 217
  spv::Capability::USMStorageClassesALTERA, // 218
  spv::Capability::CooperativeMatrixTensorAddressingNV, // 219
  spv::Capability::CooperativeMatrixDecodeVectorNV, // 220
  spv::Capability::TensorsARM, // 221
  spv::Capability::Addresses, // 222
  spv::Capability::PhysicalStorageBufferAddresses, // 223
  spv::Capability::LiteralSampler, // 224
  spv::Capability::Addresses, // 225
  spv::Capability::UntypedPointersKHR, // 226
  spv::Capability::Addresses, // 227
  spv::Capability::VariablePointers, // 228
  spv::Capability::VariablePointersStorageBuffer, // 229
  spv::Capability::PhysicalStorageBufferAddresses, // 230
  spv::Capability::Kernel, // 231
  spv::Capability::ImageQuery, // 232
  spv::Capability::ImageQuery, // 233
  spv::Capability::Shader, // 234
  spv::Capability::BitInstructions, // 235
  spv::Capability::DerivativeControl, // 236
  spv::Capability::Groups, // 237
  spv::Capability::SparseResidency, // 238
  spv::Capability::PipeStorage, // 239
  spv::Capability::NamedBarrier, // 240
  spv::Capability::GroupNonUniformVote, // 241
  spv::Capability::GroupNonUniformBallot, // 242
  spv::Capability::GroupNonUniformShuffle, // 243
  spv::Capability::GroupNonUniformShuffleRelative, // 244
  spv::Capability::GroupNonUniformArithmetic, // 245
  spv::Capability::GroupNonUniformClustered, // 246
  spv::Capability::GroupNonUniformPartitionedEXT, // 247
  spv::Capability::GroupNonUniformQuad, // 248
  spv::Capability::Addresses, // 249
  spv::Capability::VariablePointers, // 250
  spv::Capability::VariablePointersStorageBuffer, // 251
  spv::Capability::GraphARM, // 252
  spv::Capability::BitcastExtractEXT, // 253
  spv::Capability::SubgroupBallotKHR, // 254
  spv::Capability::FMAKHR, // 255
  spv::Capability::SubgroupVoteKHR, // 256
  spv::Capability::GroupNonUniformRotateKHR, // 257
  spv::Capability::RayTracingKHR, // 258
  spv::Capability::RayQueryKHR, // 259
  spv::Capability::DotProduct, // 260
  spv::Capability::ReplicatedCompositesEXT, // 261
  spv::Capability::TextureSampleWeightedQCOM, // 262
  spv::Capability::TextureBoxFilterQCOM, // 263
  spv::Capability::TextureBlockMatchQCOM, // 264
  spv::Capability::CooperativeMatrixConversionQCOM, // 265
  spv::Capability::TextureBlockMatch2QCOM, // 266
  spv::Capability::BFloat16MulAddQCOM, // 267
  spv::Capability::ImageGatherLinearQCOM, // 268
  spv::Capability::ImageGatherExtendedModesQCOM, // 269
  spv::Capability::FragmentMaskAMD, // 270
  spv::Capability::ShaderClockKHR, // 271
  spv::Capability::AbortKHR, // 272
  spv::Capability::ShaderInvocationReorderNV, // 273
  spv::Capability::RayTracingMotionBlurNV, // 274
  spv::Capability::ImageFootprintNV, // 275
  spv::Capability::CooperativeVectorNV, // 276
  spv::Capability::LongVectorEXT, // 277
  spv::Capability::CooperativeVectorNV, // 278
  spv::Capability::CooperativeVectorTrainingNV, // 279
  spv::Capability::CooperativeMatrixConversionsEXT, // 280
  spv::Capability::CooperativeMatrixConversionsNV, // 281
  spv::Capability::DisplacementMicromapNV, // 282
  spv::Capability::ShaderInvocationReorderEXT, // 283
  spv::Capability::RayTracingMotionBlurNV, // 284
  spv::Capability::RayQueryPositionFetchKHR, // 285
  spv::Capability::RayTracingNV, // 286
  spv::Capability::RayTracingKHR, // 287
  spv::Capability::RayQueryKHR, // 288
  spv::Capability::DisplacementMicromapNV, // 289
  spv::Capability::CooperativeMatrixNV, // 290
  spv::Capability::CooperativeMatrixGetCoordinateEXT, // 291
  spv::Capability::FragmentShaderSampleInterlockEXT, // 292
  spv::Capability::FragmentShaderPixelInterlockEXT, // 293
  spv::Capability::FragmentShaderShadingRateInterlockEXT, // 294
  spv::Capability::CooperativeMatrixReductionsEXT, // 295
  spv::Capability::CooperativeMatrixPerElementOperationsEXT, // 296
  spv::Capability::TensorAddressingNV, // 297
  spv::Capability::DemoteToHelperInvocation, // 298
  spv::Capability::CooperativeMatrixConversionsNV, // 299
  spv::Capability::SubgroupShuffleINTEL, // 300
  spv::Capability::SubgroupBufferBlockIOINTEL, // 301
  spv::Capability::SubgroupImageBlockIOINTEL, // 302
  spv::Capability::SubgroupImageMediaBlockIOINTEL, // 303
  spv::Capability::IntegerFunctions2INTEL, // 304
  spv::Capability::AtomicFloat16MinMaxEXT, // 305
  spv::Capability::AtomicFloat32MinMaxEXT, // 306
  spv::Capability::AtomicFloat64MinMaxEXT, // 307
  spv::Capability::AtomicFloat16VectorNV, // 308
  spv::Capability::ExpectAssumeKHR, // 309
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 310
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 311
  spv::Capability::SubgroupAvcMotionEstimationIntraINTEL, // 312
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 313
  spv::Capability::SubgroupAvcMotionEstimationChromaINTEL, // 314
  spv::Capability::VariableLengthArrayINTEL, // 315
  spv::Capability::ArbitraryPrecisionFloatingPointALTERA, // 316
  spv::Capability::UnstructuredLoopControlsINTEL, // 317
  spv::Capability::BlockingPipesALTERA, // 318
  spv::Capability::FPGARegALTERA, // 319
  spv::Capability::AtomicFloat16AddEXT, // 320
  spv::Capability::AtomicFloat32AddEXT, // 321
  spv::Capability::AtomicFloat64AddEXT, // 322
  spv::Capability::AtomicFloat16VectorNV, // 323
  spv::Capability::LongCompositesINTEL, // 324
  spv::Capability::BFloat16ConversionINTEL, // 325
  spv::Capability::SplitBarrierEXT, // 326
  spv::Capability::ArithmeticFenceEXT, // 327
  spv::Capability::TaskSequenceALTERA, // 328
  spv::Capability::SubgroupBufferPrefetchINTEL, // 329
  spv::Capability::Subgroup2DBlockTransformINTEL, // 330
  spv::Capability::Subgroup2DBlockTransposeINTEL, // 331
  spv::Capability::SubgroupMatrixMultiplyAccumulateINTEL, // 332
  spv::Capability::TernaryBitwiseFunctionINTEL, // 333
  spv::Capability::UntypedVariableLengthArrayINTEL, // 334
  spv::Capability::FunctionVariantsINTEL, // 335
  spv::Capability::PredicatedIOINTEL, // 336
  spv::Capability::GroupUniformArithmeticKHR, // 337
  spv::Capability::TensorFloat32RoundingINTEL, // 338
  spv::Capability::MaskedGatherScatterINTEL, // 339
  spv::Capability::BindlessImagesINTEL, // 340
  spv::Capability::DotProductFloat16AccFloat32VALVE, // 341
  spv::Capability::DotProductBFloat16AccVALVE, // 342
  spv::Capability::DotProductFloat16AccFloat16VALVE, // 343
  spv::Capability::DotProductBFloat16AccVALVE, // 344
  spv::Capability::DotProductFloat8AccFloat32VALVE, // 345
  spv::Capability::Float64, // 346
  spv::Capability::InterpolationFunction, // 347
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
  spvtools::Extension::kSPV_EXT_ocp_microscaling_types, // 40
  spvtools::Extension::kSPV_KHR_workgroup_memory_explicit_layout, // 41
  spvtools::Extension::kSPV_KHR_subgroup_vote, // 42
  spvtools::Extension::kSPV_KHR_16bit_storage, // 43
  spvtools::Extension::kSPV_KHR_variable_pointers, // 44
  spvtools::Extension::kSPV_KHR_shader_atomic_counter_ops, // 45
  spvtools::Extension::kSPV_KHR_post_depth_coverage, // 46
  spvtools::Extension::kSPV_KHR_8bit_storage, // 47
  spvtools::Extension::kSPV_KHR_float_controls, // 48
  spvtools::Extension::kSPV_KHR_ray_query, // 49
  spvtools::Extension::kSPV_KHR_untyped_pointers, // 50
  spvtools::Extension::kSPV_KHR_ray_query, // 51
  spvtools::Extension::kSPV_KHR_ray_tracing, // 52
  spvtools::Extension::kSPV_QCOM_image_processing, // 53
  spvtools::Extension::kSPV_QCOM_tile_shading, // 54
  spvtools::Extension::kSPV_QCOM_cooperative_matrix_conversion, // 55
  spvtools::Extension::kSPV_QCOM_image_processing2, // 56
  spvtools::Extension::kSPV_QCOM_bfloat16_muladd, // 57
  spvtools::Extension::kSPV_QCOM_subgroup_size, // 58
  spvtools::Extension::kSPV_QCOM_multiple_wait_queues, // 59
  spvtools::Extension::kSPV_QCOM_image_processing3, // 60
  spvtools::Extension::kSPV_AMD_gpu_shader_half_float_fetch, // 61
  spvtools::Extension::kSPV_AMD_texture_gather_bias_lod, // 62
  spvtools::Extension::kSPV_AMD_shader_fragment_mask, // 63
  spvtools::Extension::kSPV_AMD_shader_image_load_store_lod, // 64
  spvtools::Extension::kSPV_EXT_shader_image_int64, // 65
  spvtools::Extension::kSPV_KHR_shader_clock, // 66
  spvtools::Extension::kSPV_AMDX_shader_enqueue, // 67
  spvtools::Extension::kSPV_KHR_quad_control, // 68
  spvtools::Extension::kSPV_INTEL_int4, // 69
  spvtools::Extension::kSPV_KHR_bfloat16, // 70
  spvtools::Extension::kSPV_KHR_abort, // 71
  spvtools::Extension::kSPV_EXT_descriptor_heap, // 72
  spvtools::Extension::kSPV_KHR_constant_data, // 73
  spvtools::Extension::kSPV_KHR_poison_freeze, // 74
  spvtools::Extension::kSPV_AMD_weak_linkage, // 75
  spvtools::Extension::kSPV_NV_sample_mask_override_coverage, // 76
  spvtools::Extension::kSPV_NV_geometry_shader_passthrough, // 77
  spvtools::Extension::kSPV_EXT_shader_viewport_index_layer, // 78
  spvtools::Extension::kSPV_NV_viewport_array2, // 79
  spvtools::Extension::kSPV_NV_viewport_array2, // 80
  spvtools::Extension::kSPV_NVX_multiview_per_view_attributes, // 81
  spvtools::Extension::kSPV_NV_shader_image_footprint, // 82
  spvtools::Extension::kSPV_NV_compute_shader_derivatives, // 83
  spvtools::Extension::kSPV_KHR_compute_shader_derivatives, // 84
  spvtools::Extension::kSPV_NV_shader_subgroup_partitioned, // 85
  spvtools::Extension::kSPV_EXT_shader_subgroup_partitioned, // 86
  spvtools::Extension::kSPV_EXT_descriptor_indexing, // 87
  spvtools::Extension::kSPV_KHR_ray_tracing_position_fetch, // 88
  spvtools::Extension::kSPV_KHR_vulkan_memory_model, // 89
  spvtools::Extension::kSPV_NV_cooperative_matrix, // 90
  spvtools::Extension::kSPV_EXT_fragment_shader_interlock, // 91
  spvtools::Extension::kSPV_EXT_demote_to_helper_invocation, // 92
  spvtools::Extension::kSPV_NV_displacement_micromap, // 93
  spvtools::Extension::kSPV_KHR_opacity_micromap, // 94
  spvtools::Extension::kSPV_EXT_opacity_micromap, // 95
  spvtools::Extension::kSPV_NV_shader_invocation_reorder, // 96
  spvtools::Extension::kSPV_EXT_shader_invocation_reorder, // 97
  spvtools::Extension::kSPV_NV_bindless_texture, // 98
  spvtools::Extension::kSPV_NV_cooperative_vector, // 99
  spvtools::Extension::kSPV_NV_shader_atomic_fp16_vector, // 100
  spvtools::Extension::kSPV_NV_raw_access_chains, // 101
  spvtools::Extension::kSPV_NV_push_constant_bank, // 102
  spvtools::Extension::kSPV_EXT_long_vector, // 103
  spvtools::Extension::kSPV_EXT_shader_64bit_indexing, // 104
  spvtools::Extension::kSPV_EXT_cooperative_matrix_maintenance1, // 105
  spvtools::Extension::kSPV_EXT_cooperative_matrix_maintenance1, // 106
  spvtools::Extension::kSPV_NV_cooperative_matrix2, // 107
  spvtools::Extension::kSPV_NV_cooperative_matrix2, // 108
  spvtools::Extension::kSPV_NV_tensor_addressing, // 109
  spvtools::Extension::kSPV_NV_cooperative_matrix_decode_vector, // 110
  spvtools::Extension::kSPV_INTEL_subgroups, // 111
  spvtools::Extension::kSPV_INTEL_media_block_io, // 112
  spvtools::Extension::kSPV_INTEL_float_controls2, // 113
  spvtools::Extension::kSPV_INTEL_shader_integer_functions2, // 114
  spvtools::Extension::kSPV_INTEL_function_pointers, // 115
  spvtools::Extension::kSPV_INTEL_inline_assembly, // 116
  spvtools::Extension::kSPV_EXT_shader_atomic_float_min_max, // 117
  spvtools::Extension::kSPV_INTEL_vector_compute, // 118
  spvtools::Extension::kSPV_KHR_expect_assume, // 119
  spvtools::Extension::kSPV_INTEL_device_side_avc_motion_estimation, // 120
  spvtools::Extension::kSPV_INTEL_variable_length_array, // 121
  spvtools::Extension::kSPV_ALTERA_fpga_memory_attributes, // 122
  spvtools::Extension::kSPV_INTEL_fpga_memory_attributes, // 123
  spvtools::Extension::kSPV_INTEL_fp_fast_math_mode, // 124
  spvtools::Extension::kSPV_ALTERA_arbitrary_precision_integers, // 125
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_integers, // 126
  spvtools::Extension::kSPV_ALTERA_arbitrary_precision_floating_point, // 127
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_floating_point, // 128
  spvtools::Extension::kSPV_INTEL_unstructured_loop_controls, // 129
  spvtools::Extension::kSPV_ALTERA_fpga_loop_controls, // 130
  spvtools::Extension::kSPV_INTEL_fpga_loop_controls, // 131
  spvtools::Extension::kSPV_INTEL_kernel_attributes, // 132
  spvtools::Extension::kSPV_ALTERA_fpga_memory_accesses, // 133
  spvtools::Extension::kSPV_INTEL_fpga_memory_accesses, // 134
  spvtools::Extension::kSPV_ALTERA_fpga_cluster_attributes, // 135
  spvtools::Extension::kSPV_INTEL_fpga_cluster_attributes, // 136
  spvtools::Extension::kSPV_ALTERA_loop_fuse, // 137
  spvtools::Extension::kSPV_INTEL_loop_fuse, // 138
  spvtools::Extension::kSPV_ALTERA_fpga_dsp_control, // 139
  spvtools::Extension::kSPV_INTEL_fpga_dsp_control, // 140
  spvtools::Extension::kSPV_INTEL_memory_access_aliasing, // 141
  spvtools::Extension::kSPV_ALTERA_fpga_invocation_pipelining_attributes, // 142
  spvtools::Extension::kSPV_INTEL_fpga_invocation_pipelining_attributes, // 143
  spvtools::Extension::kSPV_ALTERA_fpga_buffer_location, // 144
  spvtools::Extension::kSPV_INTEL_fpga_buffer_location, // 145
  spvtools::Extension::kSPV_ALTERA_arbitrary_precision_fixed_point, // 146
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_fixed_point, // 147
  spvtools::Extension::kSPV_ALTERA_usm_storage_classes, // 148
  spvtools::Extension::kSPV_INTEL_usm_storage_classes, // 149
  spvtools::Extension::kSPV_ALTERA_runtime_aligned, // 150
  spvtools::Extension::kSPV_INTEL_runtime_aligned, // 151
  spvtools::Extension::kSPV_ALTERA_io_pipes, // 152
  spvtools::Extension::kSPV_INTEL_io_pipes, // 153
  spvtools::Extension::kSPV_ALTERA_blocking_pipes, // 154
  spvtools::Extension::kSPV_INTEL_blocking_pipes, // 155
  spvtools::Extension::kSPV_ALTERA_fpga_reg, // 156
  spvtools::Extension::kSPV_INTEL_fpga_reg, // 157
  spvtools::Extension::kSPV_KHR_integer_dot_product, // 158
  spvtools::Extension::kSPV_KHR_cooperative_matrix, // 159
  spvtools::Extension::kSPV_EXT_replicated_composites, // 160
  spvtools::Extension::kSPV_KHR_bit_instructions, // 161
  spvtools::Extension::kSPV_KHR_subgroup_rotate, // 162
  spvtools::Extension::kSPV_KHR_float_controls2, // 163
  spvtools::Extension::kSPV_KHR_fma, // 164
  spvtools::Extension::kSPV_KHR_opacity_micromap, // 165
  spvtools::Extension::kSPV_EXT_shader_atomic_float_add, // 166
  spvtools::Extension::kSPV_INTEL_long_composites, // 167
  spvtools::Extension::kSPV_EXT_optnone, // 168
  spvtools::Extension::kSPV_INTEL_optnone, // 169
  spvtools::Extension::kSPV_EXT_shader_atomic_float16_add, // 170
  spvtools::Extension::kSPV_INTEL_debug_module, // 171
  spvtools::Extension::kSPV_INTEL_bfloat16_conversion, // 172
  spvtools::Extension::kSPV_EXT_split_barrier, // 173
  spvtools::Extension::kSPV_INTEL_split_barrier, // 174
  spvtools::Extension::kSPV_EXT_arithmetic_fence, // 175
  spvtools::Extension::kSPV_ALTERA_task_sequence, // 176
  spvtools::Extension::kSPV_INTEL_task_sequence, // 177
  spvtools::Extension::kSPV_INTEL_fp_max_error, // 178
  spvtools::Extension::kSPV_ALTERA_fpga_latency_control, // 179
  spvtools::Extension::kSPV_INTEL_fpga_latency_control, // 180
  spvtools::Extension::kSPV_ALTERA_fpga_argument_interfaces, // 181
  spvtools::Extension::kSPV_INTEL_fpga_argument_interfaces, // 182
  spvtools::Extension::kSPV_INTEL_global_variable_host_access, // 183
  spvtools::Extension::kSPV_ALTERA_global_variable_fpga_decorations, // 184
  spvtools::Extension::kSPV_INTEL_global_variable_fpga_decorations, // 185
  spvtools::Extension::kSPV_INTEL_subgroup_buffer_prefetch, // 186
  spvtools::Extension::kSPV_INTEL_2d_block_io, // 187
  spvtools::Extension::kSPV_INTEL_subgroup_matrix_multiply_accumulate, // 188
  spvtools::Extension::kSPV_INTEL_ternary_bitwise_function, // 189
  spvtools::Extension::kSPV_INTEL_function_variants, // 190
  spvtools::Extension::kSPV_INTEL_predicated_io, // 191
  spvtools::Extension::kSPV_INTEL_rounded_divide_sqrt, // 192
  spvtools::Extension::kSPV_KHR_uniform_group_instructions, // 193
  spvtools::Extension::kSPV_INTEL_tensor_float32_conversion, // 194
  spvtools::Extension::kSPV_INTEL_masked_gather_scatter, // 195
  spvtools::Extension::kSPV_INTEL_cache_controls, // 196
  spvtools::Extension::kSPV_INTEL_maximum_registers, // 197
  spvtools::Extension::kSPV_INTEL_bindless_images, // 198
  spvtools::Extension::kSPV_VALVE_mixed_float_dot_product, // 199
  spvtools::Extension::kSPV_SAMSUNG_intrinsic, // 200
  spvtools::Extension::kSPV_KHR_no_integer_wrap_decoration, // 201
  spvtools::Extension::kSPV_NV_mesh_shader, // 202
  spvtools::Extension::kSPV_EXT_mesh_shader, // 203
  spvtools::Extension::kSPV_GOOGLE_hlsl_functionality1, // 204
  spvtools::Extension::kSPV_GOOGLE_user_type, // 205
  spvtools::Extension::kSPV_KHR_subgroup_uniform_control_flow, // 206
  spvtools::Extension::kSPV_AMD_shader_early_and_late_fragment_tests, // 207
  spvtools::Extension::kSPV_AMD_shader_early_and_late_fragment_tests, // 208
  spvtools::Extension::kSPV_EXT_shader_stencil_export, // 209
  spvtools::Extension::kSPV_KHR_maximal_reconvergence, // 210
  spvtools::Extension::kSPV_KHR_linkonce_odr, // 211
  spvtools::Extension::kSPV_KHR_storage_buffer_storage_class, // 212
  spvtools::Extension::kSPV_KHR_variable_pointers, // 213
  spvtools::Extension::kSPV_KHR_terminate_invocation, // 214
  spvtools::Extension::kSPV_KHR_relaxed_extended_instruction, // 215
  spvtools::Extension::kSPV_KHR_ray_tracing, // 216
  spvtools::Extension::kSPV_KHR_ray_query, // 217
  spvtools::Extension::kSPV_NV_ray_tracing, // 218
  spvtools::Extension::kSPV_KHR_ray_tracing, // 219
  spvtools::Extension::kSPV_KHR_ray_query, // 220
  spvtools::Extension::kSPV_NV_displacement_micromap, // 221
  spvtools::Extension::kSPV_GOOGLE_decorate_string, // 222
  spvtools::Extension::kSPV_GOOGLE_hlsl_functionality1, // 223
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
  SPV_OPERAND_TYPE_TYPE_ID, // 479
  SPV_OPERAND_TYPE_RESULT_ID, // 480
  SPV_OPERAND_TYPE_ID, // 481
  SPV_OPERAND_TYPE_ID, // 482
  SPV_OPERAND_TYPE_ID, // 483
  SPV_OPERAND_TYPE_ID, // 484
  SPV_OPERAND_TYPE_OPTIONAL_IMAGE, // 485
  SPV_OPERAND_TYPE_TYPE_ID, // 486
  SPV_OPERAND_TYPE_RESULT_ID, // 487
  SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER, // 488
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
  SPV_OPERAND_TYPE_ID, // 532
  SPV_OPERAND_TYPE_ID, // 533
  SPV_OPERAND_TYPE_ID, // 534
  SPV_OPERAND_TYPE_ID, // 535
  SPV_OPERAND_TYPE_ID, // 536
  SPV_OPERAND_TYPE_ID, // 537
  SPV_OPERAND_TYPE_ID, // 538
  SPV_OPERAND_TYPE_ID, // 539
  SPV_OPERAND_TYPE_ID, // 540
  SPV_OPERAND_TYPE_ID, // 541
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 542
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 543
  SPV_OPERAND_TYPE_TYPE_ID, // 544
  SPV_OPERAND_TYPE_RESULT_ID, // 545
  SPV_OPERAND_TYPE_ID, // 546
  SPV_OPERAND_TYPE_ID, // 547
  SPV_OPERAND_TYPE_ID, // 548
  SPV_OPERAND_TYPE_ID, // 549
  SPV_OPERAND_TYPE_ID, // 550
  SPV_OPERAND_TYPE_ID, // 551
  SPV_OPERAND_TYPE_ID, // 552
  SPV_OPERAND_TYPE_ID, // 553
  SPV_OPERAND_TYPE_ID, // 554
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 555
  SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS, // 556
  SPV_OPERAND_TYPE_ID, // 557
  SPV_OPERAND_TYPE_ID, // 558
  SPV_OPERAND_TYPE_ID, // 559
  SPV_OPERAND_TYPE_ID, // 560
  SPV_OPERAND_TYPE_ID, // 561
  SPV_OPERAND_TYPE_ID, // 562
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 563
  SPV_OPERAND_TYPE_TYPE_ID, // 564
  SPV_OPERAND_TYPE_RESULT_ID, // 565
  SPV_OPERAND_TYPE_ID, // 566
  SPV_OPERAND_TYPE_ID, // 567
  SPV_OPERAND_TYPE_ID, // 568
  SPV_OPERAND_TYPE_ID, // 569
  SPV_OPERAND_TYPE_ID, // 570
  SPV_OPERAND_TYPE_ID, // 571
  SPV_OPERAND_TYPE_ID, // 572
  SPV_OPERAND_TYPE_ID, // 573
  SPV_OPERAND_TYPE_ID, // 574
  SPV_OPERAND_TYPE_ID, // 575
  SPV_OPERAND_TYPE_ID, // 576
  SPV_OPERAND_TYPE_ID, // 577
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 578
  SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS, // 579
  SPV_OPERAND_TYPE_ID, // 580
  SPV_OPERAND_TYPE_ID, // 581
  SPV_OPERAND_TYPE_ID, // 582
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 583
  SPV_OPERAND_TYPE_TYPE_ID, // 584
  SPV_OPERAND_TYPE_RESULT_ID, // 585
  SPV_OPERAND_TYPE_ID, // 586
  SPV_OPERAND_TYPE_ID, // 587
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 588
  SPV_OPERAND_TYPE_ID, // 589
  SPV_OPERAND_TYPE_ID, // 590
  SPV_OPERAND_TYPE_ID, // 591
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 592
  SPV_OPERAND_TYPE_ID, // 593
  SPV_OPERAND_TYPE_ID, // 594
  SPV_OPERAND_TYPE_ID, // 595
  SPV_OPERAND_TYPE_ID, // 596
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 597
  SPV_OPERAND_TYPE_ID, // 598
  SPV_OPERAND_TYPE_ID, // 599
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 600
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 601
  SPV_OPERAND_TYPE_ID, // 602
  SPV_OPERAND_TYPE_ID, // 603
  SPV_OPERAND_TYPE_ID, // 604
  SPV_OPERAND_TYPE_ID, // 605
  SPV_OPERAND_TYPE_ID, // 606
  SPV_OPERAND_TYPE_ID, // 607
  SPV_OPERAND_TYPE_ID, // 608
  SPV_OPERAND_TYPE_ID, // 609
  SPV_OPERAND_TYPE_ID, // 610
  SPV_OPERAND_TYPE_ID, // 611
  SPV_OPERAND_TYPE_ID, // 612
  SPV_OPERAND_TYPE_ID, // 613
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 614
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 615
  SPV_OPERAND_TYPE_ID, // 616
  SPV_OPERAND_TYPE_ID, // 617
  SPV_OPERAND_TYPE_ID, // 618
  SPV_OPERAND_TYPE_ID, // 619
  SPV_OPERAND_TYPE_ID, // 620
  SPV_OPERAND_TYPE_ID, // 621
  SPV_OPERAND_TYPE_ID, // 622
  SPV_OPERAND_TYPE_ID, // 623
  SPV_OPERAND_TYPE_ID, // 624
  SPV_OPERAND_TYPE_ID, // 625
  SPV_OPERAND_TYPE_ID, // 626
  SPV_OPERAND_TYPE_ID, // 627
  SPV_OPERAND_TYPE_ID, // 628
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 629
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 630
  SPV_OPERAND_TYPE_RESULT_ID, // 631
  SPV_OPERAND_TYPE_ID, // 632
  SPV_OPERAND_TYPE_SCOPE_ID, // 633
  SPV_OPERAND_TYPE_ID, // 634
  SPV_OPERAND_TYPE_ID, // 635
  SPV_OPERAND_TYPE_TYPE_ID, // 636
  SPV_OPERAND_TYPE_RESULT_ID, // 637
  SPV_OPERAND_TYPE_ID, // 638
  SPV_OPERAND_TYPE_ID, // 639
  SPV_OPERAND_TYPE_ID, // 640
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 641
  SPV_OPERAND_TYPE_ID, // 642
  SPV_OPERAND_TYPE_ID, // 643
  SPV_OPERAND_TYPE_ID, // 644
  SPV_OPERAND_TYPE_ID, // 645
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 646
  SPV_OPERAND_TYPE_TYPE_ID, // 647
  SPV_OPERAND_TYPE_RESULT_ID, // 648
  SPV_OPERAND_TYPE_ID, // 649
  SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE, // 650
  SPV_OPERAND_TYPE_ID, // 651
  SPV_OPERAND_TYPE_TYPE_ID, // 652
  SPV_OPERAND_TYPE_RESULT_ID, // 653
  SPV_OPERAND_TYPE_ID, // 654
  SPV_OPERAND_TYPE_ID, // 655
  SPV_OPERAND_TYPE_ID, // 656
  SPV_OPERAND_TYPE_MEMORY_ACCESS, // 657
  SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS, // 658
  SPV_OPERAND_TYPE_ID, // 659
  SPV_OPERAND_TYPE_ID, // 660
  SPV_OPERAND_TYPE_ID, // 661
  SPV_OPERAND_TYPE_MEMORY_ACCESS, // 662
  SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS, // 663
  SPV_OPERAND_TYPE_RESULT_ID, // 664
  SPV_OPERAND_TYPE_ID, // 665
  SPV_OPERAND_TYPE_ID, // 666
  SPV_OPERAND_TYPE_VARIABLE_ID, // 667
  SPV_OPERAND_TYPE_TYPE_ID, // 668
  SPV_OPERAND_TYPE_RESULT_ID, // 669
  SPV_OPERAND_TYPE_ID, // 670
  SPV_OPERAND_TYPE_ID, // 671
  SPV_OPERAND_TYPE_ID, // 672
  SPV_OPERAND_TYPE_ID, // 673
  SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS, // 674
  SPV_OPERAND_TYPE_ID, // 675
  SPV_OPERAND_TYPE_ID, // 676
  SPV_OPERAND_TYPE_ID, // 677
  SPV_OPERAND_TYPE_ID, // 678
  SPV_OPERAND_TYPE_ID, // 679
  SPV_OPERAND_TYPE_TYPE_ID, // 680
  SPV_OPERAND_TYPE_RESULT_ID, // 681
  SPV_OPERAND_TYPE_ID, // 682
  SPV_OPERAND_TYPE_ID, // 683
  SPV_OPERAND_TYPE_LITERAL_STRING, // 684
  SPV_OPERAND_TYPE_LITERAL_STRING, // 685
  SPV_OPERAND_TYPE_TYPE_ID, // 686
  SPV_OPERAND_TYPE_RESULT_ID, // 687
  SPV_OPERAND_TYPE_ID, // 688
  SPV_OPERAND_TYPE_ID, // 689
  SPV_OPERAND_TYPE_ID, // 690
  SPV_OPERAND_TYPE_ID, // 691
  SPV_OPERAND_TYPE_ID, // 692
  SPV_OPERAND_TYPE_ID, // 693
  SPV_OPERAND_TYPE_ID, // 694
  SPV_OPERAND_TYPE_TYPE_ID, // 695
  SPV_OPERAND_TYPE_RESULT_ID, // 696
  SPV_OPERAND_TYPE_ID, // 697
  SPV_OPERAND_TYPE_ID, // 698
  SPV_OPERAND_TYPE_ID, // 699
  SPV_OPERAND_TYPE_ID, // 700
  SPV_OPERAND_TYPE_ID, // 701
  SPV_OPERAND_TYPE_ID, // 702
  SPV_OPERAND_TYPE_ID, // 703
  SPV_OPERAND_TYPE_ID, // 704
  SPV_OPERAND_TYPE_TYPE_ID, // 705
  SPV_OPERAND_TYPE_RESULT_ID, // 706
  SPV_OPERAND_TYPE_ID, // 707
  SPV_OPERAND_TYPE_ID, // 708
  SPV_OPERAND_TYPE_ID, // 709
  SPV_OPERAND_TYPE_ID, // 710
  SPV_OPERAND_TYPE_ID, // 711
  SPV_OPERAND_TYPE_ID, // 712
  SPV_OPERAND_TYPE_ID, // 713
  SPV_OPERAND_TYPE_ID, // 714
  SPV_OPERAND_TYPE_ID, // 715
  SPV_OPERAND_TYPE_ID, // 716
  SPV_OPERAND_TYPE_ID, // 717
  SPV_OPERAND_TYPE_TYPE_ID, // 718
  SPV_OPERAND_TYPE_RESULT_ID, // 719
  SPV_OPERAND_TYPE_ID, // 720
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 721
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 722
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 723
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 724
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 725
  SPV_OPERAND_TYPE_TYPE_ID, // 726
  SPV_OPERAND_TYPE_RESULT_ID, // 727
  SPV_OPERAND_TYPE_ID, // 728
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 729
  SPV_OPERAND_TYPE_ID, // 730
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 731
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 732
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 733
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 734
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 735
  SPV_OPERAND_TYPE_TYPE_ID, // 736
  SPV_OPERAND_TYPE_RESULT_ID, // 737
  SPV_OPERAND_TYPE_ID, // 738
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 739
  SPV_OPERAND_TYPE_ID, // 740
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 741
  SPV_OPERAND_TYPE_RESULT_ID, // 742
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 743
  SPV_OPERAND_TYPE_RESULT_ID, // 744
  SPV_OPERAND_TYPE_ID, // 745
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 746
  SPV_OPERAND_TYPE_VARIABLE_ID, // 747
  SPV_OPERAND_TYPE_TYPE_ID, // 748
  SPV_OPERAND_TYPE_RESULT_ID, // 749
  SPV_OPERAND_TYPE_ID, // 750
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 751
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 752
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 753
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 754
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
  SPV_OPERAND_TYPE_ID, // 766
  SPV_OPERAND_TYPE_ID, // 767
  SPV_OPERAND_TYPE_ID, // 768
  SPV_OPERAND_TYPE_ID, // 769
  SPV_OPERAND_TYPE_ID, // 770
  SPV_OPERAND_TYPE_ID, // 771
  SPV_OPERAND_TYPE_ID, // 772
  SPV_OPERAND_TYPE_ID, // 773
  SPV_OPERAND_TYPE_TYPE_ID, // 774
  SPV_OPERAND_TYPE_RESULT_ID, // 775
  SPV_OPERAND_TYPE_ID, // 776
  SPV_OPERAND_TYPE_ID, // 777
  SPV_OPERAND_TYPE_ID, // 778
  SPV_OPERAND_TYPE_ID, // 779
  SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS, // 780
  SPV_OPERAND_TYPE_ID, // 781
  SPV_OPERAND_TYPE_EXECUTION_MODEL, // 782
  SPV_OPERAND_TYPE_ID, // 783
  SPV_OPERAND_TYPE_LITERAL_STRING, // 784
  SPV_OPERAND_TYPE_VARIABLE_ID, // 785
  SPV_OPERAND_TYPE_ID, // 786
  SPV_OPERAND_TYPE_CAPABILITY, // 787
  SPV_OPERAND_TYPE_TYPE_ID, // 788
  SPV_OPERAND_TYPE_RESULT_ID, // 789
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 790
  SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER, // 791
  SPV_OPERAND_TYPE_TYPE_ID, // 792
  SPV_OPERAND_TYPE_RESULT_ID, // 793
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 794
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 795
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 796
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 797
  SPV_OPERAND_TYPE_TYPE_ID, // 798
  SPV_OPERAND_TYPE_RESULT_ID, // 799
  SPV_OPERAND_TYPE_VARIABLE_CAPABILITY, // 800
  SPV_OPERAND_TYPE_TYPE_ID, // 801
  SPV_OPERAND_TYPE_RESULT_ID, // 802
  SPV_OPERAND_TYPE_ID, // 803
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 804
  SPV_OPERAND_TYPE_ID, // 805
  SPV_OPERAND_TYPE_ID, // 806
  SPV_OPERAND_TYPE_ID, // 807
  SPV_OPERAND_TYPE_ID, // 808
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 809
  SPV_OPERAND_TYPE_ID, // 810
  SPV_OPERAND_TYPE_ID, // 811
  SPV_OPERAND_TYPE_ID, // 812
  SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING, // 813
  SPV_OPERAND_TYPE_ID, // 814
  SPV_OPERAND_TYPE_STORAGE_CLASS, // 815
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 816
  SPV_OPERAND_TYPE_ID, // 817
  SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER, // 818
  SPV_OPERAND_TYPE_ID, // 819
  SPV_OPERAND_TYPE_ID, // 820
  SPV_OPERAND_TYPE_ID, // 821
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 822
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 823
  SPV_OPERAND_TYPE_ID, // 824
  SPV_OPERAND_TYPE_ID, // 825
  SPV_OPERAND_TYPE_ID, // 826
  SPV_OPERAND_TYPE_ID, // 827
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 828
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 829
  SPV_OPERAND_TYPE_ID, // 830
  SPV_OPERAND_TYPE_ID, // 831
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 832
  SPV_OPERAND_TYPE_VARIABLE_ID, // 833
  SPV_OPERAND_TYPE_ID, // 834
  SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE, // 835
  SPV_OPERAND_TYPE_ID, // 836
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 837
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 838
  SPV_OPERAND_TYPE_ID, // 839
  SPV_OPERAND_TYPE_ID, // 840
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 841
  SPV_OPERAND_TYPE_VARIABLE_ID, // 842
  SPV_OPERAND_TYPE_ID, // 843
  SPV_OPERAND_TYPE_ID, // 844
  SPV_OPERAND_TYPE_ID, // 845
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 846
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 847
  SPV_OPERAND_TYPE_ID, // 848
  SPV_OPERAND_TYPE_ID, // 849
  SPV_OPERAND_TYPE_ID, // 850
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 851
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 852
  SPV_OPERAND_TYPE_ID, // 853
  SPV_OPERAND_TYPE_ID, // 854
  SPV_OPERAND_TYPE_ID, // 855
  SPV_OPERAND_TYPE_ID, // 856
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 857
  SPV_OPERAND_TYPE_ID, // 858
  SPV_OPERAND_TYPE_ID, // 859
  SPV_OPERAND_TYPE_ID, // 860
  SPV_OPERAND_TYPE_ID, // 861
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 862
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 863
  SPV_OPERAND_TYPE_ID, // 864
  SPV_OPERAND_TYPE_ID, // 865
  SPV_OPERAND_TYPE_ID, // 866
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 867
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 868
  SPV_OPERAND_TYPE_ID, // 869
  SPV_OPERAND_TYPE_ID, // 870
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 871
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 872
  SPV_OPERAND_TYPE_VARIABLE_ID, // 873
  SPV_OPERAND_TYPE_ID, // 874
  SPV_OPERAND_TYPE_ID, // 875
  SPV_OPERAND_TYPE_ID, // 876
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 877
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 878
  SPV_OPERAND_TYPE_ID, // 879
  SPV_OPERAND_TYPE_ID, // 880
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 881
  SPV_OPERAND_TYPE_ID, // 882
  SPV_OPERAND_TYPE_ID, // 883
  SPV_OPERAND_TYPE_ID, // 884
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 885
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 886
  SPV_OPERAND_TYPE_ID, // 887
  SPV_OPERAND_TYPE_ID, // 888
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 889
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 890
  SPV_OPERAND_TYPE_ID, // 891
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 892
  SPV_OPERAND_TYPE_ID, // 893
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 894
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 895
  SPV_OPERAND_TYPE_ID, // 896
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 897
  SPV_OPERAND_TYPE_ID, // 898
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 899
  SPV_OPERAND_TYPE_ID, // 900
  SPV_OPERAND_TYPE_ID, // 901
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 902
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 903
  SPV_OPERAND_TYPE_ID, // 904
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 905
  SPV_OPERAND_TYPE_ID, // 906
  SPV_OPERAND_TYPE_ID, // 907
  SPV_OPERAND_TYPE_ID, // 908
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 909
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 910
  SPV_OPERAND_TYPE_ID, // 911
  SPV_OPERAND_TYPE_OPTIONAL_LITERAL_INTEGER, // 912
  SPV_OPERAND_TYPE_DEBUG_OPERATION, // 913
  SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER, // 914
  SPV_OPERAND_TYPE_ID, // 915
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 916
  SPV_OPERAND_TYPE_ID, // 917
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 918
  SPV_OPERAND_TYPE_ID, // 919
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 920
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 921
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 922
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 923
  SPV_OPERAND_TYPE_ID, // 924
  SPV_OPERAND_TYPE_ID, // 925
  SPV_OPERAND_TYPE_ID, // 926
  SPV_OPERAND_TYPE_ID, // 927
  SPV_OPERAND_TYPE_ID, // 928
  SPV_OPERAND_TYPE_ID, // 929
  SPV_OPERAND_TYPE_ID, // 930
  SPV_OPERAND_TYPE_ID, // 931
  SPV_OPERAND_TYPE_VARIABLE_ID, // 932
  SPV_OPERAND_TYPE_ID, // 933
  SPV_OPERAND_TYPE_ID, // 934
  SPV_OPERAND_TYPE_ID, // 935
  SPV_OPERAND_TYPE_ID, // 936
  SPV_OPERAND_TYPE_ID, // 937
  SPV_OPERAND_TYPE_ID, // 938
  SPV_OPERAND_TYPE_ID, // 939
  SPV_OPERAND_TYPE_ID, // 940
  SPV_OPERAND_TYPE_ID, // 941
  SPV_OPERAND_TYPE_VARIABLE_ID, // 942
  SPV_OPERAND_TYPE_ID, // 943
  SPV_OPERAND_TYPE_ID, // 944
  SPV_OPERAND_TYPE_ID, // 945
  SPV_OPERAND_TYPE_ID, // 946
  SPV_OPERAND_TYPE_ID, // 947
  SPV_OPERAND_TYPE_ID, // 948
  SPV_OPERAND_TYPE_ID, // 949
  SPV_OPERAND_TYPE_ID, // 950
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 951
  SPV_OPERAND_TYPE_ID, // 952
  SPV_OPERAND_TYPE_ID, // 953
  SPV_OPERAND_TYPE_ID, // 954
  SPV_OPERAND_TYPE_ID, // 955
  SPV_OPERAND_TYPE_VARIABLE_ID, // 956
  SPV_OPERAND_TYPE_ID, // 957
  SPV_OPERAND_TYPE_ID, // 958
  SPV_OPERAND_TYPE_ID, // 959
  SPV_OPERAND_TYPE_ID, // 960
  SPV_OPERAND_TYPE_ID, // 961
  SPV_OPERAND_TYPE_ID, // 962
  SPV_OPERAND_TYPE_ID, // 963
  SPV_OPERAND_TYPE_ID, // 964
  SPV_OPERAND_TYPE_ID, // 965
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 966
  SPV_OPERAND_TYPE_ID, // 967
  SPV_OPERAND_TYPE_ID, // 968
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 969
  SPV_OPERAND_TYPE_ID, // 970
  SPV_OPERAND_TYPE_ID, // 971
  SPV_OPERAND_TYPE_ID, // 972
  SPV_OPERAND_TYPE_ID, // 973
  SPV_OPERAND_TYPE_ID, // 974
  SPV_OPERAND_TYPE_ID, // 975
  SPV_OPERAND_TYPE_ID, // 976
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 977
  SPV_OPERAND_TYPE_ID, // 978
  SPV_OPERAND_TYPE_ID, // 979
  SPV_OPERAND_TYPE_ID, // 980
  SPV_OPERAND_TYPE_VARIABLE_ID, // 981
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
  SPV_OPERAND_TYPE_ID, // 1046
  SPV_OPERAND_TYPE_ID, // 1047
  SPV_OPERAND_TYPE_ID, // 1048
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1049
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1050
  SPV_OPERAND_TYPE_ID, // 1051
  SPV_OPERAND_TYPE_SOURCE_LANGUAGE, // 1052
  SPV_OPERAND_TYPE_ID, // 1053
  SPV_OPERAND_TYPE_ID, // 1054
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING, // 1055
  SPV_OPERAND_TYPE_ID, // 1056
  SPV_OPERAND_TYPE_STORAGE_CLASS, // 1057
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1058
  SPV_OPERAND_TYPE_ID, // 1059
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER, // 1060
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1061
  SPV_OPERAND_TYPE_ID, // 1062
  SPV_OPERAND_TYPE_VARIABLE_ID, // 1063
  SPV_OPERAND_TYPE_ID, // 1064
  SPV_OPERAND_TYPE_ID, // 1065
  SPV_OPERAND_TYPE_ID, // 1066
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1067
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1068
  SPV_OPERAND_TYPE_ID, // 1069
  SPV_OPERAND_TYPE_ID, // 1070
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1071
  SPV_OPERAND_TYPE_VARIABLE_ID, // 1072
  SPV_OPERAND_TYPE_ID, // 1073
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE, // 1074
  SPV_OPERAND_TYPE_ID, // 1075
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1076
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1077
  SPV_OPERAND_TYPE_ID, // 1078
  SPV_OPERAND_TYPE_ID, // 1079
  SPV_OPERAND_TYPE_ID, // 1080
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1081
  SPV_OPERAND_TYPE_VARIABLE_ID, // 1082
  SPV_OPERAND_TYPE_ID, // 1083
  SPV_OPERAND_TYPE_ID, // 1084
  SPV_OPERAND_TYPE_ID, // 1085
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1086
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1087
  SPV_OPERAND_TYPE_ID, // 1088
  SPV_OPERAND_TYPE_ID, // 1089
  SPV_OPERAND_TYPE_ID, // 1090
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1091
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 1092
  SPV_OPERAND_TYPE_ID, // 1093
  SPV_OPERAND_TYPE_ID, // 1094
  SPV_OPERAND_TYPE_ID, // 1095
  SPV_OPERAND_TYPE_ID, // 1096
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1097
  SPV_OPERAND_TYPE_ID, // 1098
  SPV_OPERAND_TYPE_ID, // 1099
  SPV_OPERAND_TYPE_ID, // 1100
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1101
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1102
  SPV_OPERAND_TYPE_ID, // 1103
  SPV_OPERAND_TYPE_ID, // 1104
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1105
  SPV_OPERAND_TYPE_ID, // 1106
  SPV_OPERAND_TYPE_ID, // 1107
  SPV_OPERAND_TYPE_ID, // 1108
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1109
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1110
  SPV_OPERAND_TYPE_ID, // 1111
  SPV_OPERAND_TYPE_ID, // 1112
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1113
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1114
  SPV_OPERAND_TYPE_ID, // 1115
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 1116
  SPV_OPERAND_TYPE_ID, // 1117
  SPV_OPERAND_TYPE_ID, // 1118
  SPV_OPERAND_TYPE_ID, // 1119
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1120
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1121
  SPV_OPERAND_TYPE_ID, // 1122
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1123
  SPV_OPERAND_TYPE_OPTIONAL_LITERAL_INTEGER, // 1124
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION, // 1125
  SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER, // 1126
  SPV_OPERAND_TYPE_ID, // 1127
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY, // 1128
  SPV_OPERAND_TYPE_ID, // 1129
  SPV_OPERAND_TYPE_ID, // 1130
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1131
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1132
  SPV_OPERAND_TYPE_ID, // 1133
  SPV_OPERAND_TYPE_ID, // 1134
  SPV_OPERAND_TYPE_ID, // 1135
  SPV_OPERAND_TYPE_ID, // 1136
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1137
  SPV_OPERAND_TYPE_ID, // 1138
  SPV_OPERAND_TYPE_ID, // 1139
  SPV_OPERAND_TYPE_ID, // 1140
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1141
  SPV_OPERAND_TYPE_ID, // 1142
  SPV_OPERAND_TYPE_ID, // 1143
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1144
  SPV_OPERAND_TYPE_ID, // 1145
  SPV_OPERAND_TYPE_ID, // 1146
  SPV_OPERAND_TYPE_ID, // 1147
  SPV_OPERAND_TYPE_FP_ROUNDING_MODE, // 1148
};
