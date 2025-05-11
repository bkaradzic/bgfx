// Returns the name of an extension, as an index into kStrings
IndexRange ExtensionToIndexRange(Extension extension) {
  switch(extension) {
    case Extension::kSPV_AMDX_shader_enqueue: return IR(0, 24);
    case Extension::kSPV_AMD_gcn_shader: return IR(24, 19);
    case Extension::kSPV_AMD_gpu_shader_half_float: return IR(43, 30);
    case Extension::kSPV_AMD_gpu_shader_half_float_fetch: return IR(73, 36);
    case Extension::kSPV_AMD_gpu_shader_int16: return IR(109, 25);
    case Extension::kSPV_AMD_shader_ballot: return IR(134, 22);
    case Extension::kSPV_AMD_shader_early_and_late_fragment_tests: return IR(156, 45);
    case Extension::kSPV_AMD_shader_explicit_vertex_parameter: return IR(201, 41);
    case Extension::kSPV_AMD_shader_fragment_mask: return IR(242, 29);
    case Extension::kSPV_AMD_shader_image_load_store_lod: return IR(271, 36);
    case Extension::kSPV_AMD_shader_trinary_minmax: return IR(307, 30);
    case Extension::kSPV_AMD_texture_gather_bias_lod: return IR(337, 32);
    case Extension::kSPV_ARM_cooperative_matrix_layouts: return IR(369, 35);
    case Extension::kSPV_ARM_core_builtins: return IR(404, 22);
    case Extension::kSPV_EXT_arithmetic_fence: return IR(426, 25);
    case Extension::kSPV_EXT_demote_to_helper_invocation: return IR(451, 36);
    case Extension::kSPV_EXT_descriptor_indexing: return IR(487, 28);
    case Extension::kSPV_EXT_fragment_fully_covered: return IR(515, 31);
    case Extension::kSPV_EXT_fragment_invocation_density: return IR(546, 36);
    case Extension::kSPV_EXT_fragment_shader_interlock: return IR(582, 34);
    case Extension::kSPV_EXT_mesh_shader: return IR(616, 20);
    case Extension::kSPV_EXT_opacity_micromap: return IR(636, 25);
    case Extension::kSPV_EXT_optnone: return IR(661, 16);
    case Extension::kSPV_EXT_physical_storage_buffer: return IR(677, 32);
    case Extension::kSPV_EXT_relaxed_printf_string_address_space: return IR(709, 44);
    case Extension::kSPV_EXT_replicated_composites: return IR(753, 30);
    case Extension::kSPV_EXT_shader_atomic_float16_add: return IR(783, 34);
    case Extension::kSPV_EXT_shader_atomic_float_add: return IR(817, 32);
    case Extension::kSPV_EXT_shader_atomic_float_min_max: return IR(849, 36);
    case Extension::kSPV_EXT_shader_image_int64: return IR(885, 27);
    case Extension::kSPV_EXT_shader_stencil_export: return IR(912, 30);
    case Extension::kSPV_EXT_shader_tile_image: return IR(942, 26);
    case Extension::kSPV_EXT_shader_viewport_index_layer: return IR(968, 36);
    case Extension::kSPV_GOOGLE_decorate_string: return IR(1004, 27);
    case Extension::kSPV_GOOGLE_hlsl_functionality1: return IR(1031, 31);
    case Extension::kSPV_GOOGLE_user_type: return IR(1062, 21);
    case Extension::kSPV_INTEL_2d_block_io: return IR(1083, 22);
    case Extension::kSPV_INTEL_arbitrary_precision_fixed_point: return IR(1105, 42);
    case Extension::kSPV_INTEL_arbitrary_precision_floating_point: return IR(1147, 45);
    case Extension::kSPV_INTEL_arbitrary_precision_integers: return IR(1192, 39);
    case Extension::kSPV_INTEL_bfloat16_conversion: return IR(1231, 30);
    case Extension::kSPV_INTEL_blocking_pipes: return IR(1261, 25);
    case Extension::kSPV_INTEL_cache_controls: return IR(1286, 25);
    case Extension::kSPV_INTEL_debug_module: return IR(1311, 23);
    case Extension::kSPV_INTEL_device_side_avc_motion_estimation: return IR(1334, 44);
    case Extension::kSPV_INTEL_float_controls2: return IR(1378, 26);
    case Extension::kSPV_INTEL_fp_fast_math_mode: return IR(1404, 28);
    case Extension::kSPV_INTEL_fp_max_error: return IR(1432, 23);
    case Extension::kSPV_INTEL_fpga_argument_interfaces: return IR(1455, 35);
    case Extension::kSPV_INTEL_fpga_buffer_location: return IR(1490, 31);
    case Extension::kSPV_INTEL_fpga_cluster_attributes: return IR(1521, 34);
    case Extension::kSPV_INTEL_fpga_dsp_control: return IR(1555, 27);
    case Extension::kSPV_INTEL_fpga_invocation_pipelining_attributes: return IR(1582, 48);
    case Extension::kSPV_INTEL_fpga_latency_control: return IR(1630, 31);
    case Extension::kSPV_INTEL_fpga_loop_controls: return IR(1661, 29);
    case Extension::kSPV_INTEL_fpga_memory_accesses: return IR(1690, 31);
    case Extension::kSPV_INTEL_fpga_memory_attributes: return IR(1721, 33);
    case Extension::kSPV_INTEL_fpga_reg: return IR(1754, 19);
    case Extension::kSPV_INTEL_function_pointers: return IR(1773, 28);
    case Extension::kSPV_INTEL_global_variable_fpga_decorations: return IR(1801, 43);
    case Extension::kSPV_INTEL_global_variable_host_access: return IR(1844, 38);
    case Extension::kSPV_INTEL_inline_assembly: return IR(1882, 26);
    case Extension::kSPV_INTEL_int4: return IR(1908, 15);
    case Extension::kSPV_INTEL_io_pipes: return IR(1923, 19);
    case Extension::kSPV_INTEL_kernel_attributes: return IR(1942, 28);
    case Extension::kSPV_INTEL_long_composites: return IR(1970, 26);
    case Extension::kSPV_INTEL_loop_fuse: return IR(1996, 20);
    case Extension::kSPV_INTEL_masked_gather_scatter: return IR(2016, 32);
    case Extension::kSPV_INTEL_maximum_registers: return IR(2048, 28);
    case Extension::kSPV_INTEL_media_block_io: return IR(2076, 25);
    case Extension::kSPV_INTEL_memory_access_aliasing: return IR(2101, 33);
    case Extension::kSPV_INTEL_optnone: return IR(2134, 18);
    case Extension::kSPV_INTEL_runtime_aligned: return IR(2152, 26);
    case Extension::kSPV_INTEL_shader_integer_functions2: return IR(2178, 36);
    case Extension::kSPV_INTEL_split_barrier: return IR(2214, 24);
    case Extension::kSPV_INTEL_subgroup_buffer_prefetch: return IR(2238, 35);
    case Extension::kSPV_INTEL_subgroup_matrix_multiply_accumulate: return IR(2273, 46);
    case Extension::kSPV_INTEL_subgroups: return IR(2319, 20);
    case Extension::kSPV_INTEL_task_sequence: return IR(2339, 24);
    case Extension::kSPV_INTEL_tensor_float32_conversion: return IR(2363, 36);
    case Extension::kSPV_INTEL_ternary_bitwise_function: return IR(2399, 35);
    case Extension::kSPV_INTEL_unstructured_loop_controls: return IR(2434, 37);
    case Extension::kSPV_INTEL_usm_storage_classes: return IR(2471, 30);
    case Extension::kSPV_INTEL_variable_length_array: return IR(2501, 32);
    case Extension::kSPV_INTEL_vector_compute: return IR(2533, 25);
    case Extension::kSPV_KHR_16bit_storage: return IR(2558, 22);
    case Extension::kSPV_KHR_8bit_storage: return IR(2580, 21);
    case Extension::kSPV_KHR_bfloat16: return IR(2601, 17);
    case Extension::kSPV_KHR_bit_instructions: return IR(2618, 25);
    case Extension::kSPV_KHR_compute_shader_derivatives: return IR(2643, 35);
    case Extension::kSPV_KHR_cooperative_matrix: return IR(2678, 27);
    case Extension::kSPV_KHR_device_group: return IR(2705, 21);
    case Extension::kSPV_KHR_expect_assume: return IR(2726, 22);
    case Extension::kSPV_KHR_float_controls: return IR(2748, 23);
    case Extension::kSPV_KHR_float_controls2: return IR(2771, 24);
    case Extension::kSPV_KHR_fragment_shader_barycentric: return IR(2795, 36);
    case Extension::kSPV_KHR_fragment_shading_rate: return IR(2831, 30);
    case Extension::kSPV_KHR_integer_dot_product: return IR(2861, 28);
    case Extension::kSPV_KHR_linkonce_odr: return IR(2889, 21);
    case Extension::kSPV_KHR_maximal_reconvergence: return IR(2910, 30);
    case Extension::kSPV_KHR_multiview: return IR(2940, 18);
    case Extension::kSPV_KHR_no_integer_wrap_decoration: return IR(2958, 35);
    case Extension::kSPV_KHR_non_semantic_info: return IR(2993, 26);
    case Extension::kSPV_KHR_physical_storage_buffer: return IR(3019, 32);
    case Extension::kSPV_KHR_post_depth_coverage: return IR(3051, 28);
    case Extension::kSPV_KHR_quad_control: return IR(3079, 21);
    case Extension::kSPV_KHR_ray_cull_mask: return IR(3100, 22);
    case Extension::kSPV_KHR_ray_query: return IR(3122, 18);
    case Extension::kSPV_KHR_ray_tracing: return IR(3140, 20);
    case Extension::kSPV_KHR_ray_tracing_position_fetch: return IR(3160, 35);
    case Extension::kSPV_KHR_relaxed_extended_instruction: return IR(3195, 37);
    case Extension::kSPV_KHR_shader_atomic_counter_ops: return IR(3232, 34);
    case Extension::kSPV_KHR_shader_ballot: return IR(3266, 22);
    case Extension::kSPV_KHR_shader_clock: return IR(3288, 21);
    case Extension::kSPV_KHR_shader_draw_parameters: return IR(3309, 31);
    case Extension::kSPV_KHR_storage_buffer_storage_class: return IR(3340, 37);
    case Extension::kSPV_KHR_subgroup_rotate: return IR(3377, 24);
    case Extension::kSPV_KHR_subgroup_uniform_control_flow: return IR(3401, 38);
    case Extension::kSPV_KHR_subgroup_vote: return IR(3439, 22);
    case Extension::kSPV_KHR_terminate_invocation: return IR(3461, 29);
    case Extension::kSPV_KHR_uniform_group_instructions: return IR(3490, 35);
    case Extension::kSPV_KHR_untyped_pointers: return IR(3525, 25);
    case Extension::kSPV_KHR_variable_pointers: return IR(3550, 26);
    case Extension::kSPV_KHR_vulkan_memory_model: return IR(3576, 28);
    case Extension::kSPV_KHR_workgroup_memory_explicit_layout: return IR(3604, 41);
    case Extension::kSPV_NVX_multiview_per_view_attributes: return IR(3645, 38);
    case Extension::kSPV_NV_bindless_texture: return IR(3683, 24);
    case Extension::kSPV_NV_cluster_acceleration_structure: return IR(3707, 38);
    case Extension::kSPV_NV_compute_shader_derivatives: return IR(3745, 34);
    case Extension::kSPV_NV_cooperative_matrix: return IR(3779, 26);
    case Extension::kSPV_NV_cooperative_matrix2: return IR(3805, 27);
    case Extension::kSPV_NV_cooperative_vector: return IR(3832, 26);
    case Extension::kSPV_NV_displacement_micromap: return IR(3858, 29);
    case Extension::kSPV_NV_fragment_shader_barycentric: return IR(3887, 35);
    case Extension::kSPV_NV_geometry_shader_passthrough: return IR(3922, 35);
    case Extension::kSPV_NV_linear_swept_spheres: return IR(3957, 28);
    case Extension::kSPV_NV_mesh_shader: return IR(3985, 19);
    case Extension::kSPV_NV_raw_access_chains: return IR(4004, 25);
    case Extension::kSPV_NV_ray_tracing: return IR(4029, 19);
    case Extension::kSPV_NV_ray_tracing_motion_blur: return IR(4048, 31);
    case Extension::kSPV_NV_sample_mask_override_coverage: return IR(4079, 37);
    case Extension::kSPV_NV_shader_atomic_fp16_vector: return IR(4116, 33);
    case Extension::kSPV_NV_shader_image_footprint: return IR(4149, 30);
    case Extension::kSPV_NV_shader_invocation_reorder: return IR(4179, 33);
    case Extension::kSPV_NV_shader_sm_builtins: return IR(4212, 26);
    case Extension::kSPV_NV_shader_subgroup_partitioned: return IR(4238, 35);
    case Extension::kSPV_NV_shading_rate: return IR(4273, 20);
    case Extension::kSPV_NV_stereo_view_rendering: return IR(4293, 29);
    case Extension::kSPV_NV_tensor_addressing: return IR(4322, 25);
    case Extension::kSPV_NV_viewport_array2: return IR(4347, 23);
    case Extension::kSPV_QCOM_image_processing: return IR(4370, 26);
    case Extension::kSPV_QCOM_image_processing2: return IR(4396, 27);
    case Extension::kSPV_QCOM_tile_shading: return IR(4423, 22);
    case Extension::kSPV_VALIDATOR_ignore_type_decl_unique: return IR(4445, 38);
    default: break;
  }
  return {};
}

// Extension names and values, ordered by name
// The fields in order are:
//   name, indexing into kStrings
//   enum value
static const std::array<NameValue,154> kExtensionNames{{
    {IR(0, 24), static_cast<uint32_t>(kSPV_AMDX_shader_enqueue)},
    {IR(24, 19), static_cast<uint32_t>(kSPV_AMD_gcn_shader)},
    {IR(43, 30), static_cast<uint32_t>(kSPV_AMD_gpu_shader_half_float)},
    {IR(73, 36), static_cast<uint32_t>(kSPV_AMD_gpu_shader_half_float_fetch)},
    {IR(109, 25), static_cast<uint32_t>(kSPV_AMD_gpu_shader_int16)},
    {IR(134, 22), static_cast<uint32_t>(kSPV_AMD_shader_ballot)},
    {IR(156, 45), static_cast<uint32_t>(kSPV_AMD_shader_early_and_late_fragment_tests)},
    {IR(201, 41), static_cast<uint32_t>(kSPV_AMD_shader_explicit_vertex_parameter)},
    {IR(242, 29), static_cast<uint32_t>(kSPV_AMD_shader_fragment_mask)},
    {IR(271, 36), static_cast<uint32_t>(kSPV_AMD_shader_image_load_store_lod)},
    {IR(307, 30), static_cast<uint32_t>(kSPV_AMD_shader_trinary_minmax)},
    {IR(337, 32), static_cast<uint32_t>(kSPV_AMD_texture_gather_bias_lod)},
    {IR(369, 35), static_cast<uint32_t>(kSPV_ARM_cooperative_matrix_layouts)},
    {IR(404, 22), static_cast<uint32_t>(kSPV_ARM_core_builtins)},
    {IR(426, 25), static_cast<uint32_t>(kSPV_EXT_arithmetic_fence)},
    {IR(451, 36), static_cast<uint32_t>(kSPV_EXT_demote_to_helper_invocation)},
    {IR(487, 28), static_cast<uint32_t>(kSPV_EXT_descriptor_indexing)},
    {IR(515, 31), static_cast<uint32_t>(kSPV_EXT_fragment_fully_covered)},
    {IR(546, 36), static_cast<uint32_t>(kSPV_EXT_fragment_invocation_density)},
    {IR(582, 34), static_cast<uint32_t>(kSPV_EXT_fragment_shader_interlock)},
    {IR(616, 20), static_cast<uint32_t>(kSPV_EXT_mesh_shader)},
    {IR(636, 25), static_cast<uint32_t>(kSPV_EXT_opacity_micromap)},
    {IR(661, 16), static_cast<uint32_t>(kSPV_EXT_optnone)},
    {IR(677, 32), static_cast<uint32_t>(kSPV_EXT_physical_storage_buffer)},
    {IR(709, 44), static_cast<uint32_t>(kSPV_EXT_relaxed_printf_string_address_space)},
    {IR(753, 30), static_cast<uint32_t>(kSPV_EXT_replicated_composites)},
    {IR(783, 34), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float16_add)},
    {IR(817, 32), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float_add)},
    {IR(849, 36), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float_min_max)},
    {IR(885, 27), static_cast<uint32_t>(kSPV_EXT_shader_image_int64)},
    {IR(912, 30), static_cast<uint32_t>(kSPV_EXT_shader_stencil_export)},
    {IR(942, 26), static_cast<uint32_t>(kSPV_EXT_shader_tile_image)},
    {IR(968, 36), static_cast<uint32_t>(kSPV_EXT_shader_viewport_index_layer)},
    {IR(1004, 27), static_cast<uint32_t>(kSPV_GOOGLE_decorate_string)},
    {IR(1031, 31), static_cast<uint32_t>(kSPV_GOOGLE_hlsl_functionality1)},
    {IR(1062, 21), static_cast<uint32_t>(kSPV_GOOGLE_user_type)},
    {IR(1083, 22), static_cast<uint32_t>(kSPV_INTEL_2d_block_io)},
    {IR(1105, 42), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_fixed_point)},
    {IR(1147, 45), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_floating_point)},
    {IR(1192, 39), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_integers)},
    {IR(1231, 30), static_cast<uint32_t>(kSPV_INTEL_bfloat16_conversion)},
    {IR(1261, 25), static_cast<uint32_t>(kSPV_INTEL_blocking_pipes)},
    {IR(1286, 25), static_cast<uint32_t>(kSPV_INTEL_cache_controls)},
    {IR(1311, 23), static_cast<uint32_t>(kSPV_INTEL_debug_module)},
    {IR(1334, 44), static_cast<uint32_t>(kSPV_INTEL_device_side_avc_motion_estimation)},
    {IR(1378, 26), static_cast<uint32_t>(kSPV_INTEL_float_controls2)},
    {IR(1404, 28), static_cast<uint32_t>(kSPV_INTEL_fp_fast_math_mode)},
    {IR(1432, 23), static_cast<uint32_t>(kSPV_INTEL_fp_max_error)},
    {IR(1455, 35), static_cast<uint32_t>(kSPV_INTEL_fpga_argument_interfaces)},
    {IR(1490, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_buffer_location)},
    {IR(1521, 34), static_cast<uint32_t>(kSPV_INTEL_fpga_cluster_attributes)},
    {IR(1555, 27), static_cast<uint32_t>(kSPV_INTEL_fpga_dsp_control)},
    {IR(1582, 48), static_cast<uint32_t>(kSPV_INTEL_fpga_invocation_pipelining_attributes)},
    {IR(1630, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_latency_control)},
    {IR(1661, 29), static_cast<uint32_t>(kSPV_INTEL_fpga_loop_controls)},
    {IR(1690, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_memory_accesses)},
    {IR(1721, 33), static_cast<uint32_t>(kSPV_INTEL_fpga_memory_attributes)},
    {IR(1754, 19), static_cast<uint32_t>(kSPV_INTEL_fpga_reg)},
    {IR(1773, 28), static_cast<uint32_t>(kSPV_INTEL_function_pointers)},
    {IR(1801, 43), static_cast<uint32_t>(kSPV_INTEL_global_variable_fpga_decorations)},
    {IR(1844, 38), static_cast<uint32_t>(kSPV_INTEL_global_variable_host_access)},
    {IR(1882, 26), static_cast<uint32_t>(kSPV_INTEL_inline_assembly)},
    {IR(1908, 15), static_cast<uint32_t>(kSPV_INTEL_int4)},
    {IR(1923, 19), static_cast<uint32_t>(kSPV_INTEL_io_pipes)},
    {IR(1942, 28), static_cast<uint32_t>(kSPV_INTEL_kernel_attributes)},
    {IR(1970, 26), static_cast<uint32_t>(kSPV_INTEL_long_composites)},
    {IR(1996, 20), static_cast<uint32_t>(kSPV_INTEL_loop_fuse)},
    {IR(2016, 32), static_cast<uint32_t>(kSPV_INTEL_masked_gather_scatter)},
    {IR(2048, 28), static_cast<uint32_t>(kSPV_INTEL_maximum_registers)},
    {IR(2076, 25), static_cast<uint32_t>(kSPV_INTEL_media_block_io)},
    {IR(2101, 33), static_cast<uint32_t>(kSPV_INTEL_memory_access_aliasing)},
    {IR(2134, 18), static_cast<uint32_t>(kSPV_INTEL_optnone)},
    {IR(2152, 26), static_cast<uint32_t>(kSPV_INTEL_runtime_aligned)},
    {IR(2178, 36), static_cast<uint32_t>(kSPV_INTEL_shader_integer_functions2)},
    {IR(2214, 24), static_cast<uint32_t>(kSPV_INTEL_split_barrier)},
    {IR(2238, 35), static_cast<uint32_t>(kSPV_INTEL_subgroup_buffer_prefetch)},
    {IR(2273, 46), static_cast<uint32_t>(kSPV_INTEL_subgroup_matrix_multiply_accumulate)},
    {IR(2319, 20), static_cast<uint32_t>(kSPV_INTEL_subgroups)},
    {IR(2339, 24), static_cast<uint32_t>(kSPV_INTEL_task_sequence)},
    {IR(2363, 36), static_cast<uint32_t>(kSPV_INTEL_tensor_float32_conversion)},
    {IR(2399, 35), static_cast<uint32_t>(kSPV_INTEL_ternary_bitwise_function)},
    {IR(2434, 37), static_cast<uint32_t>(kSPV_INTEL_unstructured_loop_controls)},
    {IR(2471, 30), static_cast<uint32_t>(kSPV_INTEL_usm_storage_classes)},
    {IR(2501, 32), static_cast<uint32_t>(kSPV_INTEL_variable_length_array)},
    {IR(2533, 25), static_cast<uint32_t>(kSPV_INTEL_vector_compute)},
    {IR(2558, 22), static_cast<uint32_t>(kSPV_KHR_16bit_storage)},
    {IR(2580, 21), static_cast<uint32_t>(kSPV_KHR_8bit_storage)},
    {IR(2601, 17), static_cast<uint32_t>(kSPV_KHR_bfloat16)},
    {IR(2618, 25), static_cast<uint32_t>(kSPV_KHR_bit_instructions)},
    {IR(2643, 35), static_cast<uint32_t>(kSPV_KHR_compute_shader_derivatives)},
    {IR(2678, 27), static_cast<uint32_t>(kSPV_KHR_cooperative_matrix)},
    {IR(2705, 21), static_cast<uint32_t>(kSPV_KHR_device_group)},
    {IR(2726, 22), static_cast<uint32_t>(kSPV_KHR_expect_assume)},
    {IR(2748, 23), static_cast<uint32_t>(kSPV_KHR_float_controls)},
    {IR(2771, 24), static_cast<uint32_t>(kSPV_KHR_float_controls2)},
    {IR(2795, 36), static_cast<uint32_t>(kSPV_KHR_fragment_shader_barycentric)},
    {IR(2831, 30), static_cast<uint32_t>(kSPV_KHR_fragment_shading_rate)},
    {IR(2861, 28), static_cast<uint32_t>(kSPV_KHR_integer_dot_product)},
    {IR(2889, 21), static_cast<uint32_t>(kSPV_KHR_linkonce_odr)},
    {IR(2910, 30), static_cast<uint32_t>(kSPV_KHR_maximal_reconvergence)},
    {IR(2940, 18), static_cast<uint32_t>(kSPV_KHR_multiview)},
    {IR(2958, 35), static_cast<uint32_t>(kSPV_KHR_no_integer_wrap_decoration)},
    {IR(2993, 26), static_cast<uint32_t>(kSPV_KHR_non_semantic_info)},
    {IR(3019, 32), static_cast<uint32_t>(kSPV_KHR_physical_storage_buffer)},
    {IR(3051, 28), static_cast<uint32_t>(kSPV_KHR_post_depth_coverage)},
    {IR(3079, 21), static_cast<uint32_t>(kSPV_KHR_quad_control)},
    {IR(3100, 22), static_cast<uint32_t>(kSPV_KHR_ray_cull_mask)},
    {IR(3122, 18), static_cast<uint32_t>(kSPV_KHR_ray_query)},
    {IR(3140, 20), static_cast<uint32_t>(kSPV_KHR_ray_tracing)},
    {IR(3160, 35), static_cast<uint32_t>(kSPV_KHR_ray_tracing_position_fetch)},
    {IR(3195, 37), static_cast<uint32_t>(kSPV_KHR_relaxed_extended_instruction)},
    {IR(3232, 34), static_cast<uint32_t>(kSPV_KHR_shader_atomic_counter_ops)},
    {IR(3266, 22), static_cast<uint32_t>(kSPV_KHR_shader_ballot)},
    {IR(3288, 21), static_cast<uint32_t>(kSPV_KHR_shader_clock)},
    {IR(3309, 31), static_cast<uint32_t>(kSPV_KHR_shader_draw_parameters)},
    {IR(3340, 37), static_cast<uint32_t>(kSPV_KHR_storage_buffer_storage_class)},
    {IR(3377, 24), static_cast<uint32_t>(kSPV_KHR_subgroup_rotate)},
    {IR(3401, 38), static_cast<uint32_t>(kSPV_KHR_subgroup_uniform_control_flow)},
    {IR(3439, 22), static_cast<uint32_t>(kSPV_KHR_subgroup_vote)},
    {IR(3461, 29), static_cast<uint32_t>(kSPV_KHR_terminate_invocation)},
    {IR(3490, 35), static_cast<uint32_t>(kSPV_KHR_uniform_group_instructions)},
    {IR(3525, 25), static_cast<uint32_t>(kSPV_KHR_untyped_pointers)},
    {IR(3550, 26), static_cast<uint32_t>(kSPV_KHR_variable_pointers)},
    {IR(3576, 28), static_cast<uint32_t>(kSPV_KHR_vulkan_memory_model)},
    {IR(3604, 41), static_cast<uint32_t>(kSPV_KHR_workgroup_memory_explicit_layout)},
    {IR(3645, 38), static_cast<uint32_t>(kSPV_NVX_multiview_per_view_attributes)},
    {IR(3683, 24), static_cast<uint32_t>(kSPV_NV_bindless_texture)},
    {IR(3707, 38), static_cast<uint32_t>(kSPV_NV_cluster_acceleration_structure)},
    {IR(3745, 34), static_cast<uint32_t>(kSPV_NV_compute_shader_derivatives)},
    {IR(3779, 26), static_cast<uint32_t>(kSPV_NV_cooperative_matrix)},
    {IR(3805, 27), static_cast<uint32_t>(kSPV_NV_cooperative_matrix2)},
    {IR(3832, 26), static_cast<uint32_t>(kSPV_NV_cooperative_vector)},
    {IR(3858, 29), static_cast<uint32_t>(kSPV_NV_displacement_micromap)},
    {IR(3887, 35), static_cast<uint32_t>(kSPV_NV_fragment_shader_barycentric)},
    {IR(3922, 35), static_cast<uint32_t>(kSPV_NV_geometry_shader_passthrough)},
    {IR(3957, 28), static_cast<uint32_t>(kSPV_NV_linear_swept_spheres)},
    {IR(3985, 19), static_cast<uint32_t>(kSPV_NV_mesh_shader)},
    {IR(4004, 25), static_cast<uint32_t>(kSPV_NV_raw_access_chains)},
    {IR(4029, 19), static_cast<uint32_t>(kSPV_NV_ray_tracing)},
    {IR(4048, 31), static_cast<uint32_t>(kSPV_NV_ray_tracing_motion_blur)},
    {IR(4079, 37), static_cast<uint32_t>(kSPV_NV_sample_mask_override_coverage)},
    {IR(4116, 33), static_cast<uint32_t>(kSPV_NV_shader_atomic_fp16_vector)},
    {IR(4149, 30), static_cast<uint32_t>(kSPV_NV_shader_image_footprint)},
    {IR(4179, 33), static_cast<uint32_t>(kSPV_NV_shader_invocation_reorder)},
    {IR(4212, 26), static_cast<uint32_t>(kSPV_NV_shader_sm_builtins)},
    {IR(4238, 35), static_cast<uint32_t>(kSPV_NV_shader_subgroup_partitioned)},
    {IR(4273, 20), static_cast<uint32_t>(kSPV_NV_shading_rate)},
    {IR(4293, 29), static_cast<uint32_t>(kSPV_NV_stereo_view_rendering)},
    {IR(4322, 25), static_cast<uint32_t>(kSPV_NV_tensor_addressing)},
    {IR(4347, 23), static_cast<uint32_t>(kSPV_NV_viewport_array2)},
    {IR(4370, 26), static_cast<uint32_t>(kSPV_QCOM_image_processing)},
    {IR(4396, 27), static_cast<uint32_t>(kSPV_QCOM_image_processing2)},
    {IR(4423, 22), static_cast<uint32_t>(kSPV_QCOM_tile_shading)},
    {IR(4445, 38), static_cast<uint32_t>(kSPV_VALIDATOR_ignore_type_decl_unique)},
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
static const std::array<OperandDesc, 1167> kOperandsByValue{{
  {0,IR(0, 0),IR(4483, 9)/* ReadOnly */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {1,IR(0, 0),IR(4499, 10)/* WriteOnly */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {2,IR(0, 0),IR(4509, 10)/* ReadWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {0,IR(0, 0),IR(4519, 8)/* Logical */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {1,IR(0, 0),IR(4527, 11)/* Physical32 */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {2,IR(0, 0),IR(4548, 11)/* Physical64 */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {5348,IR(0, 0),IR(4559, 24)/* PhysicalStorageBuffer64 */,IR(0, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {0,IR(0, 0),IR(4641, 9)/* Position */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {1,IR(0, 0),IR(4657, 10)/* PointSize */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {3,IR(0, 0),IR(4667, 13)/* ClipDistance */,IR(0, 0),IR(4, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4,IR(0, 0),IR(4680, 13)/* CullDistance */,IR(0, 0),IR(5, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5,IR(0, 0),IR(4693, 9)/* VertexId */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {6,IR(0, 0),IR(4702, 11)/* InstanceId */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {7,IR(0, 0),IR(4713, 12)/* PrimitiveId */,IR(0, 0),IR(6, 6),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {8,IR(0, 0),IR(4803, 13)/* InvocationId */,IR(0, 0),IR(12, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {9,IR(0, 0),IR(4816, 6)/* Layer */,IR(0, 0),IR(14, 5),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {10,IR(0, 0),IR(4862, 14)/* ViewportIndex */,IR(0, 0),IR(19, 5),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {11,IR(0, 0),IR(4910, 15)/* TessLevelOuter */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {12,IR(0, 0),IR(4925, 15)/* TessLevelInner */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {13,IR(0, 0),IR(4940, 10)/* TessCoord */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {14,IR(0, 0),IR(4950, 14)/* PatchVertices */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {15,IR(0, 0),IR(4964, 10)/* FragCoord */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {16,IR(0, 0),IR(4974, 11)/* PointCoord */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {17,IR(0, 0),IR(4985, 12)/* FrontFacing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {18,IR(0, 0),IR(4997, 9)/* SampleId */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {19,IR(0, 0),IR(5024, 15)/* SamplePosition */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {20,IR(0, 0),IR(5039, 11)/* SampleMask */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {22,IR(0, 0),IR(5050, 10)/* FragDepth */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {23,IR(0, 0),IR(5060, 17)/* HelperInvocation */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {24,IR(0, 0),IR(5077, 14)/* NumWorkgroups */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {25,IR(0, 0),IR(5091, 14)/* WorkgroupSize */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {26,IR(0, 0),IR(5105, 12)/* WorkgroupId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {27,IR(0, 0),IR(5117, 18)/* LocalInvocationId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {28,IR(0, 0),IR(5135, 19)/* GlobalInvocationId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {29,IR(0, 0),IR(5154, 21)/* LocalInvocationIndex */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {30,IR(0, 0),IR(5175, 8)/* WorkDim */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {31,IR(0, 0),IR(5183, 11)/* GlobalSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {32,IR(0, 0),IR(5194, 22)/* EnqueuedWorkgroupSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {33,IR(0, 0),IR(5216, 13)/* GlobalOffset */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {34,IR(0, 0),IR(5229, 15)/* GlobalLinearId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {36,IR(0, 0),IR(5244, 13)/* SubgroupSize */,IR(0, 0),IR(26, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {37,IR(0, 0),IR(5291, 16)/* SubgroupMaxSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {38,IR(0, 0),IR(5307, 13)/* NumSubgroups */,IR(0, 0),IR(29, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {39,IR(0, 0),IR(5320, 21)/* NumEnqueuedSubgroups */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {40,IR(0, 0),IR(5341, 11)/* SubgroupId */,IR(0, 0),IR(29, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {41,IR(0, 0),IR(5352, 26)/* SubgroupLocalInvocationId */,IR(0, 0),IR(26, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {42,IR(0, 0),IR(5378, 12)/* VertexIndex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {43,IR(0, 0),IR(5390, 14)/* InstanceIndex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4160,IR(0, 0),IR(5404, 10)/* CoreIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4161,IR(0, 0),IR(5430, 13)/* CoreCountARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4162,IR(0, 0),IR(5443, 13)/* CoreMaxIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4163,IR(0, 0),IR(5456, 10)/* WarpIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4164,IR(0, 0),IR(5466, 13)/* WarpMaxIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4416,IR(0, 0),IR(5479, 15)/* SubgroupEqMask */,IR(1, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4417,IR(0, 0),IR(5534, 15)/* SubgroupGeMask */,IR(2, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4418,IR(0, 0),IR(5567, 15)/* SubgroupGtMask */,IR(3, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4419,IR(0, 0),IR(5600, 15)/* SubgroupLeMask */,IR(4, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4420,IR(0, 0),IR(5633, 15)/* SubgroupLtMask */,IR(5, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4424,IR(0, 0),IR(5666, 11)/* BaseVertex */,IR(0, 0),IR(34, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4425,IR(0, 0),IR(5692, 13)/* BaseInstance */,IR(0, 0),IR(34, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4426,IR(0, 0),IR(5705, 10)/* DrawIndex */,IR(0, 0),IR(35, 3),IR(4, 3),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4432,IR(0, 0),IR(5715, 24)/* PrimitiveShadingRateKHR */,IR(0, 0),IR(38, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4438,IR(0, 0),IR(5762, 12)/* DeviceIndex */,IR(0, 0),IR(39, 1),IR(8, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4440,IR(0, 0),IR(5786, 10)/* ViewIndex */,IR(0, 0),IR(40, 1),IR(9, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4444,IR(0, 0),IR(5806, 15)/* ShadingRateKHR */,IR(0, 0),IR(38, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4492,IR(0, 0),IR(5821, 15)/* TileOffsetQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4493,IR(0, 0),IR(5852, 18)/* TileDimensionQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4494,IR(0, 0),IR(5870, 18)/* TileApronSizeQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4992,IR(0, 0),IR(5888, 20)/* BaryCoordNoPerspAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4993,IR(0, 0),IR(5908, 28)/* BaryCoordNoPerspCentroidAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4994,IR(0, 0),IR(5936, 26)/* BaryCoordNoPerspSampleAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4995,IR(0, 0),IR(5962, 19)/* BaryCoordSmoothAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4996,IR(0, 0),IR(5981, 27)/* BaryCoordSmoothCentroidAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4997,IR(0, 0),IR(6008, 25)/* BaryCoordSmoothSampleAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4998,IR(0, 0),IR(6033, 22)/* BaryCoordPullModelAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5014,IR(0, 0),IR(6055, 18)/* FragStencilRefEXT */,IR(0, 0),IR(42, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5021,IR(0, 0),IR(6090, 29)/* RemainingRecursionLevelsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5073,IR(0, 0),IR(6137, 16)/* ShaderIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5253,IR(0, 0),IR(6153, 15)/* ViewportMaskNV */,IR(0, 0),IR(44, 2),IR(12, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5257,IR(0, 0),IR(6189, 20)/* SecondaryPositionNV */,IR(0, 0),IR(46, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5258,IR(0, 0),IR(6228, 24)/* SecondaryViewportMaskNV */,IR(0, 0),IR(46, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5261,IR(0, 0),IR(6252, 18)/* PositionPerViewNV */,IR(0, 0),IR(47, 2),IR(15, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5262,IR(0, 0),IR(6290, 22)/* ViewportMaskPerViewNV */,IR(0, 0),IR(47, 2),IR(15, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5264,IR(0, 0),IR(6312, 16)/* FullyCoveredEXT */,IR(0, 0),IR(49, 1),IR(17, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5274,IR(0, 0),IR(6352, 12)/* TaskCountNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5275,IR(0, 0),IR(6364, 17)/* PrimitiveCountNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5276,IR(0, 0),IR(6381, 19)/* PrimitiveIndicesNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5277,IR(0, 0),IR(6400, 22)/* ClipDistancePerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5278,IR(0, 0),IR(6422, 22)/* CullDistancePerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5279,IR(0, 0),IR(6444, 15)/* LayerPerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5280,IR(0, 0),IR(6459, 16)/* MeshViewCountNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5281,IR(0, 0),IR(6475, 18)/* MeshViewIndicesNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5286,IR(0, 0),IR(6493, 13)/* BaryCoordKHR */,IR(6, 1),IR(51, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5287,IR(0, 0),IR(6541, 20)/* BaryCoordNoPerspKHR */,IR(7, 1),IR(51, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5292,IR(0, 0),IR(6580, 12)/* FragSizeEXT */,IR(8, 1),IR(52, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5293,IR(0, 0),IR(6626, 23)/* FragInvocationCountEXT */,IR(9, 1),IR(52, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5294,IR(0, 0),IR(6671, 25)/* PrimitivePointIndicesEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5295,IR(0, 0),IR(6696, 24)/* PrimitiveLineIndicesEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5296,IR(0, 0),IR(6720, 28)/* PrimitiveTriangleIndicesEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5299,IR(0, 0),IR(6748, 17)/* CullPrimitiveEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5319,IR(0, 0),IR(6765, 12)/* LaunchIdKHR */,IR(10, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5320,IR(0, 0),IR(6788, 14)/* LaunchSizeKHR */,IR(11, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5321,IR(0, 0),IR(6815, 18)/* WorldRayOriginKHR */,IR(12, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5322,IR(0, 0),IR(6850, 21)/* WorldRayDirectionKHR */,IR(13, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5323,IR(0, 0),IR(6891, 19)/* ObjectRayOriginKHR */,IR(14, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5324,IR(0, 0),IR(6928, 22)/* ObjectRayDirectionKHR */,IR(15, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5325,IR(0, 0),IR(6971, 11)/* RayTminKHR */,IR(16, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5326,IR(0, 0),IR(6992, 11)/* RayTmaxKHR */,IR(17, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5327,IR(0, 0),IR(7013, 23)/* InstanceCustomIndexKHR */,IR(18, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5330,IR(0, 0),IR(7058, 17)/* ObjectToWorldKHR */,IR(19, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5331,IR(0, 0),IR(7091, 17)/* WorldToObjectKHR */,IR(20, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5332,IR(0, 0),IR(7124, 7)/* HitTNV */,IR(0, 0),IR(56, 1),IR(26, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5333,IR(0, 0),IR(7131, 11)/* HitKindKHR */,IR(21, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5334,IR(0, 0),IR(7152, 17)/* CurrentRayTimeNV */,IR(0, 0),IR(57, 1),IR(27, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5335,IR(0, 0),IR(7192, 30)/* HitTriangleVertexPositionsKHR */,IR(0, 0),IR(58, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5337,IR(0, 0),IR(7249, 34)/* HitMicroTriangleVertexPositionsNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5344,IR(0, 0),IR(7316, 37)/* HitMicroTriangleVertexBarycentricsNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5351,IR(0, 0),IR(7353, 20)/* IncomingRayFlagsKHR */,IR(22, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5352,IR(0, 0),IR(7392, 20)/* RayGeometryIndexKHR */,IR(0, 0),IR(60, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5359,IR(0, 0),IR(7412, 14)/* HitIsSphereNV */,IR(0, 0),IR(61, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5360,IR(0, 0),IR(7454, 11)/* HitIsLSSNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5361,IR(0, 0),IR(7504, 20)/* HitSpherePositionNV */,IR(0, 0),IR(61, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5374,IR(0, 0),IR(7524, 13)/* WarpsPerSMNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5375,IR(0, 0),IR(7556, 10)/* SMCountNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5376,IR(0, 0),IR(7566, 9)/* WarpIDNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5377,IR(0, 0),IR(7575, 7)/* SMIDNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5396,IR(0, 0),IR(7582, 18)/* HitLSSPositionsNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5405,IR(0, 0),IR(7600, 34)/* HitKindFrontFacingMicroTriangleNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5406,IR(0, 0),IR(7634, 33)/* HitKindBackFacingMicroTriangleNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5420,IR(0, 0),IR(7667, 18)/* HitSphereRadiusNV */,IR(0, 0),IR(61, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5421,IR(0, 0),IR(7685, 14)/* HitLSSRadiiNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5436,IR(0, 0),IR(7699, 12)/* ClusterIDNV */,IR(0, 0),IR(64, 1),IR(31, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {6021,IR(0, 0),IR(7752, 12)/* CullMaskKHR */,IR(0, 0),IR(65, 1),IR(32, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {0,IR(0, 0),IR(7779, 7)/* Matrix */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {1,IR(0, 0),IR(4650, 7)/* Shader */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {2,IR(0, 0),IR(4725, 9)/* Geometry */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {3,IR(0, 0),IR(4734, 13)/* Tessellation */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4,IR(0, 0),IR(4538, 10)/* Addresses */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5,IR(0, 0),IR(7786, 8)/* Linkage */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6,IR(0, 0),IR(4492, 7)/* Kernel */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {7,IR(0, 0),IR(7794, 9)/* Vector16 */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {8,IR(0, 0),IR(7803, 14)/* Float16Buffer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {9,IR(0, 0),IR(7817, 8)/* Float16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {10,IR(0, 0),IR(7825, 8)/* Float64 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {11,IR(0, 0),IR(7833, 6)/* Int64 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {12,IR(0, 0),IR(7839, 13)/* Int64Atomics */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {13,IR(0, 0),IR(7852, 11)/* ImageBasic */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {14,IR(0, 0),IR(7863, 15)/* ImageReadWrite */,IR(0, 0),IR(68, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {15,IR(0, 0),IR(7878, 12)/* ImageMipmap */,IR(0, 0),IR(68, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {17,IR(0, 0),IR(7890, 6)/* Pipes */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {18,IR(0, 0),IR(7896, 7)/* Groups */,IR(0, 0),IR(1, 0),IR(33, 1),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {19,IR(0, 0),IR(7903, 14)/* DeviceEnqueue */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {20,IR(0, 0),IR(7917, 15)/* LiteralSampler */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {21,IR(0, 0),IR(7932, 14)/* AtomicStorage */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {22,IR(0, 0),IR(7946, 6)/* Int16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {23,IR(0, 0),IR(7952, 22)/* TessellationPointSize */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {24,IR(0, 0),IR(7974, 18)/* GeometryPointSize */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {25,IR(0, 0),IR(7992, 20)/* ImageGatherExtended */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {27,IR(0, 0),IR(8012, 24)/* StorageImageMultisample */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {28,IR(0, 0),IR(8036, 34)/* UniformBufferArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {29,IR(0, 0),IR(8070, 33)/* SampledImageArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {30,IR(0, 0),IR(8103, 34)/* StorageBufferArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {31,IR(0, 0),IR(8137, 33)/* StorageImageArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {32,IR(0, 0),IR(4667, 13)/* ClipDistance */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {33,IR(0, 0),IR(4680, 13)/* CullDistance */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {34,IR(0, 0),IR(8170, 15)/* ImageCubeArray */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {35,IR(0, 0),IR(5006, 18)/* SampleRateShading */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {36,IR(0, 0),IR(8202, 10)/* ImageRect */,IR(0, 0),IR(71, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {37,IR(0, 0),IR(8212, 12)/* SampledRect */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {38,IR(0, 0),IR(8224, 15)/* GenericPointer */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {39,IR(0, 0),IR(8239, 5)/* Int8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {40,IR(0, 0),IR(8244, 16)/* InputAttachment */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {41,IR(0, 0),IR(8260, 16)/* SparseResidency */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {42,IR(0, 0),IR(8276, 7)/* MinLod */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {43,IR(0, 0),IR(8283, 10)/* Sampled1D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {44,IR(0, 0),IR(8293, 8)/* Image1D */,IR(0, 0),IR(72, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {45,IR(0, 0),IR(8185, 17)/* SampledCubeArray */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {46,IR(0, 0),IR(8301, 14)/* SampledBuffer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {47,IR(0, 0),IR(8315, 12)/* ImageBuffer */,IR(0, 0),IR(73, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {48,IR(0, 0),IR(8327, 13)/* ImageMSArray */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {49,IR(0, 0),IR(8340, 28)/* StorageImageExtendedFormats */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {50,IR(0, 0),IR(8368, 11)/* ImageQuery */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {51,IR(0, 0),IR(8379, 18)/* DerivativeControl */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {52,IR(0, 0),IR(8397, 22)/* InterpolationFunction */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {53,IR(0, 0),IR(8419, 18)/* TransformFeedback */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {54,IR(0, 0),IR(8437, 16)/* GeometryStreams */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {55,IR(0, 0),IR(8453, 30)/* StorageImageReadWithoutFormat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {56,IR(0, 0),IR(8483, 31)/* StorageImageWriteWithoutFormat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {57,IR(0, 0),IR(4876, 14)/* MultiViewport */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {58,IR(0, 0),IR(8514, 17)/* SubgroupDispatch */,IR(0, 0),IR(74, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {59,IR(0, 0),IR(8531, 13)/* NamedBarrier */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {60,IR(0, 0),IR(8544, 12)/* PipeStorage */,IR(0, 0),IR(75, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {61,IR(0, 0),IR(5257, 16)/* GroupNonUniform */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {62,IR(0, 0),IR(8556, 20)/* GroupNonUniformVote */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {63,IR(0, 0),IR(8576, 26)/* GroupNonUniformArithmetic */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {64,IR(0, 0),IR(5512, 22)/* GroupNonUniformBallot */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {65,IR(0, 0),IR(8602, 23)/* GroupNonUniformShuffle */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {66,IR(0, 0),IR(8625, 31)/* GroupNonUniformShuffleRelative */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {67,IR(0, 0),IR(8656, 25)/* GroupNonUniformClustered */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {68,IR(0, 0),IR(8681, 20)/* GroupNonUniformQuad */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {69,IR(0, 0),IR(4822, 12)/* ShaderLayer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {70,IR(0, 0),IR(4890, 20)/* ShaderViewportIndex */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {71,IR(0, 0),IR(8701, 18)/* UniformDecoration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4165,IR(0, 0),IR(5414, 16)/* CoreBuiltinsARM */,IR(0, 0),IR(1, 0),IR(34, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4166,IR(0, 0),IR(8719, 28)/* TileImageColorReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4167,IR(0, 0),IR(8747, 28)/* TileImageDepthReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4168,IR(0, 0),IR(8775, 30)/* TileImageStencilReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4201,IR(0, 0),IR(8805, 28)/* CooperativeMatrixLayoutsARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4422,IR(0, 0),IR(5739, 23)/* FragmentShadingRateKHR */,IR(0, 0),IR(3, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4423,IR(0, 0),IR(5273, 18)/* SubgroupBallotKHR */,IR(0, 0),IR(1, 0),IR(2, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4427,IR(0, 0),IR(5677, 15)/* DrawParameters */,IR(0, 0),IR(3, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4428,IR(0, 0),IR(8833, 33)/* WorkgroupMemoryExplicitLayoutKHR */,IR(0, 0),IR(3, 1),IR(37, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4429,IR(0, 0),IR(8866, 43)/* WorkgroupMemoryExplicitLayout8BitAccessKHR */,IR(0, 0),IR(77, 1),IR(37, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4430,IR(0, 0),IR(8909, 44)/* WorkgroupMemoryExplicitLayout16BitAccessKHR */,IR(0, 0),IR(77, 1),IR(37, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4431,IR(0, 0),IR(8953, 16)/* SubgroupVoteKHR */,IR(0, 0),IR(1, 0),IR(38, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4433,IR(0, 0),IR(8969, 25)/* StorageBuffer16BitAccess */,IR(23, 1),IR(1, 0),IR(39, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4434,IR(0, 0),IR(9022, 35)/* UniformAndStorageBuffer16BitAccess */,IR(24, 1),IR(78, 1),IR(39, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4435,IR(0, 0),IR(9074, 22)/* StoragePushConstant16 */,IR(0, 0),IR(1, 0),IR(39, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4436,IR(0, 0),IR(9096, 21)/* StorageInputOutput16 */,IR(0, 0),IR(1, 0),IR(39, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4437,IR(0, 0),IR(5774, 12)/* DeviceGroup */,IR(0, 0),IR(1, 0),IR(8, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4439,IR(0, 0),IR(5796, 10)/* MultiView */,IR(0, 0),IR(3, 1),IR(9, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4441,IR(0, 0),IR(9117, 30)/* VariablePointersStorageBuffer */,IR(0, 0),IR(3, 1),IR(40, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4442,IR(0, 0),IR(9147, 17)/* VariablePointers */,IR(0, 0),IR(79, 1),IR(40, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4445,IR(0, 0),IR(9164, 17)/* AtomicStorageOps */,IR(0, 0),IR(80, 1),IR(41, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4447,IR(0, 0),IR(9181, 28)/* SampleMaskPostDepthCoverage */,IR(0, 0),IR(1, 0),IR(42, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4448,IR(0, 0),IR(9209, 24)/* StorageBuffer8BitAccess */,IR(0, 0),IR(1, 0),IR(43, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4449,IR(0, 0),IR(9233, 34)/* UniformAndStorageBuffer8BitAccess */,IR(0, 0),IR(81, 1),IR(43, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4450,IR(0, 0),IR(9267, 21)/* StoragePushConstant8 */,IR(0, 0),IR(1, 0),IR(43, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4464,IR(0, 0),IR(9288, 15)/* DenormPreserve */,IR(0, 0),IR(1, 0),IR(44, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4465,IR(0, 0),IR(9303, 18)/* DenormFlushToZero */,IR(0, 0),IR(1, 0),IR(44, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4466,IR(0, 0),IR(9321, 25)/* SignedZeroInfNanPreserve */,IR(0, 0),IR(1, 0),IR(44, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4467,IR(0, 0),IR(9346, 16)/* RoundingModeRTE */,IR(0, 0),IR(1, 0),IR(44, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4468,IR(0, 0),IR(9362, 16)/* RoundingModeRTZ */,IR(0, 0),IR(1, 0),IR(44, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4471,IR(0, 0),IR(9378, 23)/* RayQueryProvisionalKHR */,IR(0, 0),IR(3, 1),IR(45, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4472,IR(0, 0),IR(9401, 12)/* RayQueryKHR */,IR(0, 0),IR(3, 1),IR(45, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4473,IR(0, 0),IR(9413, 19)/* UntypedPointersKHR */,IR(0, 0),IR(1, 0),IR(46, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4478,IR(0, 0),IR(9432, 32)/* RayTraversalPrimitiveCullingKHR */,IR(0, 0),IR(82, 2),IR(47, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4479,IR(0, 0),IR(4760, 14)/* RayTracingKHR */,IR(0, 0),IR(3, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4484,IR(0, 0),IR(9464, 26)/* TextureSampleWeightedQCOM */,IR(0, 0),IR(1, 0),IR(49, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4485,IR(0, 0),IR(9490, 21)/* TextureBoxFilterQCOM */,IR(0, 0),IR(1, 0),IR(49, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4486,IR(0, 0),IR(9511, 22)/* TextureBlockMatchQCOM */,IR(0, 0),IR(1, 0),IR(49, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4495,IR(0, 0),IR(5836, 16)/* TileShadingQCOM */,IR(0, 0),IR(3, 1),IR(50, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4498,IR(0, 0),IR(9533, 23)/* TextureBlockMatch2QCOM */,IR(0, 0),IR(1, 0),IR(51, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5008,IR(0, 0),IR(9556, 16)/* Float16ImageAMD */,IR(0, 0),IR(3, 1),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5009,IR(0, 0),IR(9572, 22)/* ImageGatherBiasLodAMD */,IR(0, 0),IR(3, 1),IR(53, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5010,IR(0, 0),IR(9594, 16)/* FragmentMaskAMD */,IR(0, 0),IR(3, 1),IR(54, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5013,IR(0, 0),IR(6073, 17)/* StencilExportEXT */,IR(0, 0),IR(3, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5015,IR(0, 0),IR(9610, 21)/* ImageReadWriteLodAMD */,IR(0, 0),IR(3, 1),IR(55, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5016,IR(0, 0),IR(9631, 14)/* Int64ImageEXT */,IR(0, 0),IR(3, 1),IR(56, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5055,IR(0, 0),IR(9645, 15)/* ShaderClockKHR */,IR(0, 0),IR(1, 0),IR(57, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5067,IR(0, 0),IR(6119, 18)/* ShaderEnqueueAMDX */,IR(0, 0),IR(3, 1),IR(58, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5087,IR(0, 0),IR(9660, 15)/* QuadControlKHR */,IR(0, 0),IR(1, 0),IR(59, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5112,IR(0, 0),IR(9675, 14)/* Int4TypeINTEL */,IR(0, 0),IR(1, 0),IR(60, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5114,IR(0, 0),IR(9689, 27)/* Int4CooperativeMatrixINTEL */,IR(0, 0),IR(84, 2),IR(60, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5116,IR(0, 0),IR(9737, 16)/* BFloat16TypeKHR */,IR(0, 0),IR(1, 0),IR(61, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5117,IR(0, 0),IR(9753, 22)/* BFloat16DotProductKHR */,IR(0, 0),IR(86, 1),IR(61, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5118,IR(0, 0),IR(9775, 29)/* BFloat16CooperativeMatrixKHR */,IR(0, 0),IR(87, 2),IR(61, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5249,IR(0, 0),IR(9804, 29)/* SampleMaskOverrideCoverageNV */,IR(0, 0),IR(25, 1),IR(62, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5251,IR(0, 0),IR(9833, 28)/* GeometryShaderPassthroughNV */,IR(0, 0),IR(69, 1),IR(63, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5254,IR(0, 0),IR(4834, 28)/* ShaderViewportIndexLayerEXT */,IR(25, 1),IR(89, 1),IR(64, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5255,IR(0, 0),IR(6168, 21)/* ShaderViewportMaskNV */,IR(0, 0),IR(90, 1),IR(66, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5259,IR(0, 0),IR(6209, 19)/* ShaderStereoViewNV */,IR(0, 0),IR(91, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5260,IR(0, 0),IR(6270, 20)/* PerViewAttributesNV */,IR(0, 0),IR(40, 1),IR(67, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5265,IR(0, 0),IR(6328, 24)/* FragmentFullyCoveredEXT */,IR(0, 0),IR(3, 1),IR(17, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5266,IR(0, 0),IR(4774, 14)/* MeshShadingNV */,IR(0, 0),IR(3, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5282,IR(0, 0),IR(9888, 17)/* ImageFootprintNV */,IR(0, 0),IR(1, 0),IR(68, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5283,IR(0, 0),IR(4788, 15)/* MeshShadingEXT */,IR(0, 0),IR(3, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5284,IR(0, 0),IR(6518, 23)/* FragmentBarycentricKHR */,IR(26, 1),IR(1, 0),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5288,IR(0, 0),IR(9927, 31)/* ComputeDerivativeGroupQuadsKHR */,IR(27, 1),IR(3, 1),IR(69, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5291,IR(0, 0),IR(6607, 19)/* FragmentDensityEXT */,IR(28, 1),IR(3, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5297,IR(0, 0),IR(10002, 29)/* GroupNonUniformPartitionedNV */,IR(0, 0),IR(1, 0),IR(71, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5301,IR(0, 0),IR(10031, 17)/* ShaderNonUniform */,IR(29, 1),IR(3, 1),IR(72, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5302,IR(0, 0),IR(10068, 23)/* RuntimeDescriptorArray */,IR(30, 1),IR(3, 1),IR(72, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5303,IR(0, 0),IR(10117, 36)/* InputAttachmentArrayDynamicIndexing */,IR(31, 1),IR(92, 1),IR(72, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5304,IR(0, 0),IR(10192, 39)/* UniformTexelBufferArrayDynamicIndexing */,IR(32, 1),IR(73, 1),IR(72, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5305,IR(0, 0),IR(10273, 39)/* StorageTexelBufferArrayDynamicIndexing */,IR(33, 1),IR(93, 1),IR(72, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5306,IR(0, 0),IR(10354, 37)/* UniformBufferArrayNonUniformIndexing */,IR(34, 1),IR(94, 1),IR(72, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5307,IR(0, 0),IR(10431, 36)/* SampledImageArrayNonUniformIndexing */,IR(35, 1),IR(94, 1),IR(72, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5308,IR(0, 0),IR(10506, 37)/* StorageBufferArrayNonUniformIndexing */,IR(36, 1),IR(94, 1),IR(72, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5309,IR(0, 0),IR(10583, 36)/* StorageImageArrayNonUniformIndexing */,IR(37, 1),IR(94, 1),IR(72, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5310,IR(0, 0),IR(10658, 39)/* InputAttachmentArrayNonUniformIndexing */,IR(38, 1),IR(95, 2),IR(72, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5311,IR(0, 0),IR(10739, 42)/* UniformTexelBufferArrayNonUniformIndexing */,IR(39, 1),IR(97, 2),IR(72, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5312,IR(0, 0),IR(10826, 42)/* StorageTexelBufferArrayNonUniformIndexing */,IR(40, 1),IR(99, 2),IR(72, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5336,IR(0, 0),IR(7222, 27)/* RayTracingPositionFetchKHR */,IR(0, 0),IR(3, 1),IR(73, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5340,IR(0, 0),IR(4747, 13)/* RayTracingNV */,IR(0, 0),IR(3, 1),IR(26, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5341,IR(0, 0),IR(7169, 23)/* RayTracingMotionBlurNV */,IR(0, 0),IR(3, 1),IR(27, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5345,IR(0, 0),IR(10913, 18)/* VulkanMemoryModel */,IR(41, 1),IR(1, 0),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5346,IR(0, 0),IR(10952, 29)/* VulkanMemoryModelDeviceScope */,IR(42, 1),IR(1, 0),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5347,IR(0, 0),IR(4610, 31)/* PhysicalStorageBufferAddresses */,IR(43, 1),IR(3, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5350,IR(0, 0),IR(11047, 32)/* ComputeDerivativeGroupLinearKHR */,IR(44, 1),IR(3, 1),IR(69, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5353,IR(0, 0),IR(11110, 25)/* RayTracingProvisionalKHR */,IR(0, 0),IR(3, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5357,IR(0, 0),IR(11135, 20)/* CooperativeMatrixNV */,IR(0, 0),IR(3, 1),IR(75, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5363,IR(0, 0),IR(11155, 33)/* FragmentShaderSampleInterlockEXT */,IR(0, 0),IR(3, 1),IR(76, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5372,IR(0, 0),IR(11188, 38)/* FragmentShaderShadingRateInterlockEXT */,IR(0, 0),IR(3, 1),IR(76, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5373,IR(0, 0),IR(7537, 19)/* ShaderSMBuiltinsNV */,IR(0, 0),IR(3, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5378,IR(0, 0),IR(11226, 32)/* FragmentShaderPixelInterlockEXT */,IR(0, 0),IR(3, 1),IR(76, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5379,IR(0, 0),IR(11258, 25)/* DemoteToHelperInvocation */,IR(45, 1),IR(3, 1),IR(77, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5380,IR(0, 0),IR(11311, 23)/* DisplacementMicromapNV */,IR(0, 0),IR(3, 1),IR(78, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5381,IR(0, 0),IR(11334, 29)/* RayTracingOpacityMicromapEXT */,IR(0, 0),IR(3, 1),IR(79, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5383,IR(0, 0),IR(11363, 26)/* ShaderInvocationReorderNV */,IR(0, 0),IR(60, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5390,IR(0, 0),IR(11389, 18)/* BindlessTextureNV */,IR(0, 0),IR(1, 0),IR(81, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5391,IR(0, 0),IR(11407, 25)/* RayQueryPositionFetchKHR */,IR(0, 0),IR(3, 1),IR(73, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5394,IR(0, 0),IR(11432, 20)/* CooperativeVectorNV */,IR(0, 0),IR(1, 0),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5404,IR(0, 0),IR(11452, 22)/* AtomicFloat16VectorNV */,IR(0, 0),IR(1, 0),IR(83, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5409,IR(0, 0),IR(7283, 33)/* RayTracingDisplacementMicromapNV */,IR(0, 0),IR(60, 1),IR(78, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5414,IR(0, 0),IR(11474, 18)/* RawAccessChainsNV */,IR(0, 0),IR(1, 0),IR(84, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5418,IR(0, 0),IR(7426, 28)/* RayTracingSpheresGeometryNV */,IR(0, 0),IR(1, 0),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5419,IR(0, 0),IR(7465, 39)/* RayTracingLinearSweptSpheresGeometryNV */,IR(0, 0),IR(1, 0),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5430,IR(0, 0),IR(11492, 30)/* CooperativeMatrixReductionsNV */,IR(0, 0),IR(1, 0),IR(85, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5431,IR(0, 0),IR(11522, 31)/* CooperativeMatrixConversionsNV */,IR(0, 0),IR(1, 0),IR(85, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5432,IR(0, 0),IR(11553, 40)/* CooperativeMatrixPerElementOperationsNV */,IR(0, 0),IR(1, 0),IR(85, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5433,IR(0, 0),IR(11593, 36)/* CooperativeMatrixTensorAddressingNV */,IR(0, 0),IR(1, 0),IR(85, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5434,IR(0, 0),IR(11629, 30)/* CooperativeMatrixBlockLoadsNV */,IR(0, 0),IR(1, 0),IR(85, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5435,IR(0, 0),IR(11659, 28)/* CooperativeVectorTrainingNV */,IR(0, 0),IR(1, 0),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5437,IR(0, 0),IR(7711, 41)/* RayTracingClusterAccelerationStructureNV */,IR(0, 0),IR(60, 1),IR(31, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5439,IR(0, 0),IR(11687, 19)/* TensorAddressingNV */,IR(0, 0),IR(1, 0),IR(86, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5568,IR(0, 0),IR(11706, 21)/* SubgroupShuffleINTEL */,IR(0, 0),IR(1, 0),IR(87, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5569,IR(0, 0),IR(11727, 27)/* SubgroupBufferBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(87, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5570,IR(0, 0),IR(11754, 26)/* SubgroupImageBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(87, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5579,IR(0, 0),IR(11780, 31)/* SubgroupImageMediaBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(88, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5582,IR(0, 0),IR(11811, 21)/* RoundToInfinityINTEL */,IR(0, 0),IR(1, 0),IR(89, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5583,IR(0, 0),IR(11832, 23)/* FloatingPointModeINTEL */,IR(0, 0),IR(1, 0),IR(89, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5584,IR(0, 0),IR(11855, 23)/* IntegerFunctions2INTEL */,IR(0, 0),IR(1, 0),IR(90, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5603,IR(0, 0),IR(11878, 22)/* FunctionPointersINTEL */,IR(0, 0),IR(1, 0),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5604,IR(0, 0),IR(11900, 24)/* IndirectReferencesINTEL */,IR(0, 0),IR(1, 0),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5606,IR(0, 0),IR(11924, 9)/* AsmINTEL */,IR(0, 0),IR(1, 0),IR(92, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5612,IR(0, 0),IR(11933, 23)/* AtomicFloat32MinMaxEXT */,IR(0, 0),IR(1, 0),IR(93, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5613,IR(0, 0),IR(11956, 23)/* AtomicFloat64MinMaxEXT */,IR(0, 0),IR(1, 0),IR(93, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5616,IR(0, 0),IR(11979, 23)/* AtomicFloat16MinMaxEXT */,IR(0, 0),IR(1, 0),IR(93, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5617,IR(0, 0),IR(12002, 19)/* VectorComputeINTEL */,IR(0, 0),IR(101, 1),IR(94, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5619,IR(0, 0),IR(12021, 15)/* VectorAnyINTEL */,IR(0, 0),IR(1, 0),IR(94, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5629,IR(0, 0),IR(12036, 16)/* ExpectAssumeKHR */,IR(0, 0),IR(1, 0),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5696,IR(0, 0),IR(12052, 33)/* SubgroupAvcMotionEstimationINTEL */,IR(0, 0),IR(1, 0),IR(96, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5697,IR(0, 0),IR(12085, 38)/* SubgroupAvcMotionEstimationIntraINTEL */,IR(0, 0),IR(1, 0),IR(96, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5698,IR(0, 0),IR(12123, 39)/* SubgroupAvcMotionEstimationChromaINTEL */,IR(0, 0),IR(1, 0),IR(96, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5817,IR(0, 0),IR(12162, 25)/* VariableLengthArrayINTEL */,IR(0, 0),IR(1, 0),IR(97, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5821,IR(0, 0),IR(12187, 26)/* FunctionFloatControlINTEL */,IR(0, 0),IR(1, 0),IR(89, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5824,IR(0, 0),IR(12213, 26)/* FPGAMemoryAttributesINTEL */,IR(0, 0),IR(1, 0),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5837,IR(0, 0),IR(12239, 20)/* FPFastMathModeINTEL */,IR(0, 0),IR(0, 1),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5844,IR(0, 0),IR(12259, 32)/* ArbitraryPrecisionIntegersINTEL */,IR(0, 0),IR(1, 0),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5845,IR(0, 0),IR(12291, 37)/* ArbitraryPrecisionFloatingPointINTEL */,IR(0, 0),IR(1, 0),IR(101, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5886,IR(0, 0),IR(12328, 30)/* UnstructuredLoopControlsINTEL */,IR(0, 0),IR(1, 0),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5888,IR(0, 0),IR(12358, 22)/* FPGALoopControlsINTEL */,IR(0, 0),IR(1, 0),IR(103, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5892,IR(0, 0),IR(12380, 22)/* KernelAttributesINTEL */,IR(0, 0),IR(1, 0),IR(104, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5897,IR(0, 0),IR(12402, 26)/* FPGAKernelAttributesINTEL */,IR(0, 0),IR(1, 0),IR(104, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5898,IR(0, 0),IR(12428, 24)/* FPGAMemoryAccessesINTEL */,IR(0, 0),IR(1, 0),IR(105, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5904,IR(0, 0),IR(12452, 27)/* FPGAClusterAttributesINTEL */,IR(0, 0),IR(1, 0),IR(106, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5906,IR(0, 0),IR(12479, 14)/* LoopFuseINTEL */,IR(0, 0),IR(1, 0),IR(107, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5908,IR(0, 0),IR(12493, 20)/* FPGADSPControlINTEL */,IR(0, 0),IR(1, 0),IR(108, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5910,IR(0, 0),IR(12513, 26)/* MemoryAccessAliasingINTEL */,IR(0, 0),IR(1, 0),IR(109, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5916,IR(0, 0),IR(12539, 40)/* FPGAInvocationPipeliningAttributesINTEL */,IR(0, 0),IR(1, 0),IR(110, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5920,IR(0, 0),IR(12579, 24)/* FPGABufferLocationINTEL */,IR(0, 0),IR(1, 0),IR(111, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5922,IR(0, 0),IR(12603, 34)/* ArbitraryPrecisionFixedPointINTEL */,IR(0, 0),IR(1, 0),IR(112, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5935,IR(0, 0),IR(12637, 23)/* USMStorageClassesINTEL */,IR(0, 0),IR(1, 0),IR(113, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5939,IR(0, 0),IR(12660, 29)/* RuntimeAlignedAttributeINTEL */,IR(0, 0),IR(1, 0),IR(114, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5943,IR(0, 0),IR(12689, 13)/* IOPipesINTEL */,IR(0, 0),IR(1, 0),IR(115, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5945,IR(0, 0),IR(12702, 19)/* BlockingPipesINTEL */,IR(0, 0),IR(1, 0),IR(116, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5948,IR(0, 0),IR(12721, 13)/* FPGARegINTEL */,IR(0, 0),IR(1, 0),IR(117, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6016,IR(0, 0),IR(12734, 19)/* DotProductInputAll */,IR(46, 1),IR(1, 0),IR(118, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6017,IR(0, 0),IR(12775, 22)/* DotProductInput4x8Bit */,IR(47, 1),IR(102, 1),IR(118, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6018,IR(0, 0),IR(12822, 28)/* DotProductInput4x8BitPacked */,IR(48, 1),IR(1, 0),IR(118, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6019,IR(0, 0),IR(12881, 11)/* DotProduct */,IR(49, 1),IR(1, 0),IR(118, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6020,IR(0, 0),IR(7764, 15)/* RayCullMaskKHR */,IR(0, 0),IR(1, 0),IR(32, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6022,IR(0, 0),IR(9716, 21)/* CooperativeMatrixKHR */,IR(0, 0),IR(1, 0),IR(119, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6024,IR(0, 0),IR(12906, 24)/* ReplicatedCompositesEXT */,IR(0, 0),IR(1, 0),IR(120, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6025,IR(0, 0),IR(12930, 16)/* BitInstructions */,IR(0, 0),IR(1, 0),IR(121, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6026,IR(0, 0),IR(12946, 25)/* GroupNonUniformRotateKHR */,IR(0, 0),IR(76, 1),IR(122, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6029,IR(0, 0),IR(12971, 15)/* FloatControls2 */,IR(0, 0),IR(1, 0),IR(123, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6033,IR(0, 0),IR(12986, 20)/* AtomicFloat32AddEXT */,IR(0, 0),IR(1, 0),IR(124, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6034,IR(0, 0),IR(13006, 20)/* AtomicFloat64AddEXT */,IR(0, 0),IR(1, 0),IR(124, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6089,IR(0, 0),IR(13026, 20)/* LongCompositesINTEL */,IR(0, 0),IR(1, 0),IR(125, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6094,IR(0, 0),IR(13046, 11)/* OptNoneEXT */,IR(50, 1),IR(1, 0),IR(126, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6095,IR(0, 0),IR(13070, 20)/* AtomicFloat16AddEXT */,IR(0, 0),IR(1, 0),IR(128, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6114,IR(0, 0),IR(13090, 21)/* DebugInfoModuleINTEL */,IR(0, 0),IR(1, 0),IR(129, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6115,IR(0, 0),IR(13111, 24)/* BFloat16ConversionINTEL */,IR(0, 0),IR(1, 0),IR(130, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6141,IR(0, 0),IR(13135, 18)/* SplitBarrierINTEL */,IR(0, 0),IR(1, 0),IR(131, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6144,IR(0, 0),IR(13153, 19)/* ArithmeticFenceEXT */,IR(0, 0),IR(1, 0),IR(132, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6150,IR(0, 0),IR(13172, 29)/* FPGAClusterAttributesV2INTEL */,IR(0, 0),IR(103, 1),IR(106, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6161,IR(0, 0),IR(13201, 28)/* FPGAKernelAttributesv2INTEL */,IR(0, 0),IR(104, 1),IR(104, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6162,IR(0, 0),IR(13229, 18)/* TaskSequenceINTEL */,IR(0, 0),IR(1, 0),IR(133, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6169,IR(0, 0),IR(13247, 16)/* FPMaxErrorINTEL */,IR(0, 0),IR(1, 0),IR(134, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6171,IR(0, 0),IR(13263, 24)/* FPGALatencyControlINTEL */,IR(0, 0),IR(1, 0),IR(135, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6174,IR(0, 0),IR(13287, 28)/* FPGAArgumentInterfacesINTEL */,IR(0, 0),IR(1, 0),IR(136, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6187,IR(0, 0),IR(13315, 30)/* GlobalVariableHostAccessINTEL */,IR(0, 0),IR(1, 0),IR(137, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6189,IR(0, 0),IR(13345, 35)/* GlobalVariableFPGADecorationsINTEL */,IR(0, 0),IR(1, 0),IR(138, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6220,IR(0, 0),IR(13380, 28)/* SubgroupBufferPrefetchINTEL */,IR(0, 0),IR(1, 0),IR(139, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6228,IR(0, 0),IR(13408, 23)/* Subgroup2DBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(140, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6229,IR(0, 0),IR(13431, 30)/* Subgroup2DBlockTransformINTEL */,IR(0, 0),IR(105, 1),IR(140, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6230,IR(0, 0),IR(13461, 30)/* Subgroup2DBlockTransposeINTEL */,IR(0, 0),IR(105, 1),IR(140, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6236,IR(0, 0),IR(13491, 38)/* SubgroupMatrixMultiplyAccumulateINTEL */,IR(0, 0),IR(1, 0),IR(141, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6241,IR(0, 0),IR(13529, 28)/* TernaryBitwiseFunctionINTEL */,IR(0, 0),IR(1, 0),IR(142, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6400,IR(0, 0),IR(13557, 26)/* GroupUniformArithmeticKHR */,IR(0, 0),IR(1, 0),IR(143, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6425,IR(0, 0),IR(13583, 27)/* TensorFloat32RoundingINTEL */,IR(0, 0),IR(1, 0),IR(144, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6427,IR(0, 0),IR(13610, 25)/* MaskedGatherScatterINTEL */,IR(0, 0),IR(1, 0),IR(145, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6441,IR(0, 0),IR(13635, 19)/* CacheControlsINTEL */,IR(0, 0),IR(1, 0),IR(146, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6460,IR(0, 0),IR(13654, 20)/* RegisterLimitsINTEL */,IR(0, 0),IR(1, 0),IR(147, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {0,IR(0, 0),IR(13674, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(13686, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(13694, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {3,IR(0, 0),IR(13702, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(13708, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(13715, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(13726, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(13735, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(13748, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(13754, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(13764, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(13770, 15)/* ImportedModule */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {1,IR(0, 0),IR(13785, 20)/* ImportedDeclaration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {0,IR(0, 0),IR(13805, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(13810, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(13826, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(13840, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(13853, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(13865, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(13882, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(13894, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(13909, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(13922, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(13937, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(13955, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(13972, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(13993, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(14013, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(14033, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {16384,IR(0, 0),IR(14049, 16)/* FlagIsEnumClass */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {32768,IR(0, 0),IR(14065, 20)/* FlagTypePassByValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {65536,IR(0, 0),IR(14085, 24)/* FlagTypePassByReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(14109, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {1,IR(0, 0),IR(14115, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {2,IR(0, 0),IR(14120, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {3,IR(0, 1),IR(14159, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {4,IR(1, 2),IR(14170, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {5,IR(0, 0),IR(14179, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {6,IR(0, 0),IR(14184, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {7,IR(0, 0),IR(14191, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {8,IR(0, 1),IR(14202, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {9,IR(1, 2),IR(14209, 9)/* Fragment */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {0,IR(0, 0),IR(14218, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(14228, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(14241, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {3,IR(0, 0),IR(14254, 11)/* AtomicType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(14265, 10)/* Float16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1,IR(0, 0),IR(14275, 10)/* Float32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {2,IR(0, 0),IR(14285, 10)/* Float64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {3,IR(0, 0),IR(14295, 13)/* SignedInt8NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {4,IR(0, 0),IR(14308, 14)/* SignedInt16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {5,IR(0, 0),IR(14322, 14)/* SignedInt32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {6,IR(0, 0),IR(14336, 14)/* SignedInt64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {7,IR(0, 0),IR(14350, 15)/* UnsignedInt8NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {8,IR(0, 0),IR(14365, 16)/* UnsignedInt16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {9,IR(0, 0),IR(14381, 16)/* UnsignedInt32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {10,IR(0, 0),IR(14397, 16)/* UnsignedInt64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491000,IR(0, 0),IR(14413, 19)/* SignedInt8PackedNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491001,IR(0, 0),IR(14432, 21)/* UnsignedInt8PackedNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491002,IR(0, 0),IR(14453, 12)/* FloatE4M3NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491003,IR(0, 0),IR(14465, 12)/* FloatE5M2NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {0,IR(0, 0),IR(14477, 12)/* RowMajorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {1,IR(0, 0),IR(14489, 15)/* ColumnMajorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {4202,IR(0, 0),IR(14504, 25)/* RowBlockedInterleavedARM */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {4203,IR(0, 0),IR(14529, 28)/* ColumnBlockedInterleavedARM */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {0,IR(0, 0),IR(14557, 8)/* NoneKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {1,IR(0, 0),IR(14565, 27)/* MatrixASignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {2,IR(0, 0),IR(14592, 27)/* MatrixBSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {4,IR(0, 0),IR(14619, 27)/* MatrixCSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {8,IR(0, 0),IR(14646, 32)/* MatrixResultSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {16,IR(0, 0),IR(14678, 26)/* SaturatingAccumulationKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {1,IR(0, 0),IR(14704, 4)/* Row */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {2,IR(0, 0),IR(14708, 7)/* Column */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {4,IR(0, 0),IR(14715, 4)/* 2x2 */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {0,IR(0, 0),IR(14719, 11)/* MatrixAKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {1,IR(0, 0),IR(14730, 11)/* MatrixBKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {2,IR(0, 0),IR(14741, 21)/* MatrixAccumulatorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {0,IR(0, 0),IR(14762, 11)/* RowMajorNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {1,IR(0, 0),IR(14773, 14)/* ColumnMajorNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {2,IR(0, 0),IR(14787, 21)/* InferencingOptimalNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {3,IR(0, 0),IR(14808, 18)/* TrainingOptimalNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {0,IR(0, 0),IR(13674, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(13686, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(13694, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(13702, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(13708, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(13715, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(13726, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {8,IR(0, 0),IR(13735, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(13748, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(13754, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(13764, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(13805, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(13810, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(13826, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(13840, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(13853, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(13865, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(13882, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(13894, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(13909, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(13922, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(13937, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(13955, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(13972, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(13993, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(14013, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(14033, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(14109, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {1,IR(0, 0),IR(14115, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {2,IR(0, 0),IR(14120, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {3,IR(0, 1),IR(14159, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {4,IR(1, 2),IR(14170, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {5,IR(0, 0),IR(14179, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {6,IR(0, 0),IR(14184, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {7,IR(0, 0),IR(14191, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {8,IR(0, 1),IR(14202, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {0,IR(0, 0),IR(14218, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(14228, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(14241, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(14826, 17)/* RelaxedPrecision */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {1,IR(0, 1),IR(14843, 7)/* SpecId */,IR(0, 0),IR(106, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {2,IR(0, 0),IR(14850, 6)/* Block */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {3,IR(0, 0),IR(14856, 12)/* BufferBlock */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),SPV_SPIRV_VERSION_WORD(1,3)}, // SPV_OPERAND_TYPE_DECORATION
  {4,IR(0, 0),IR(14868, 9)/* RowMajor */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5,IR(0, 0),IR(14877, 9)/* ColMajor */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6,IR(0, 1),IR(14886, 12)/* ArrayStride */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {7,IR(0, 1),IR(14898, 13)/* MatrixStride */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {8,IR(0, 0),IR(14911, 11)/* GLSLShared */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {9,IR(0, 0),IR(14922, 11)/* GLSLPacked */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {10,IR(0, 0),IR(14933, 8)/* CPacked */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {11,IR(3, 1),IR(14967, 8)/* BuiltIn */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {13,IR(0, 0),IR(14975, 14)/* NoPerspective */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {14,IR(0, 0),IR(14989, 5)/* Flat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {15,IR(0, 0),IR(14994, 6)/* Patch */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {16,IR(0, 0),IR(15000, 9)/* Centroid */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {17,IR(0, 0),IR(15009, 7)/* Sample */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {18,IR(0, 0),IR(15016, 10)/* Invariant */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {19,IR(0, 0),IR(15026, 9)/* Restrict */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {20,IR(0, 0),IR(15035, 8)/* Aliased */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {21,IR(0, 0),IR(15043, 9)/* Volatile */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {22,IR(0, 0),IR(15052, 9)/* Constant */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {23,IR(0, 0),IR(15061, 9)/* Coherent */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {24,IR(0, 0),IR(15070, 12)/* NonWritable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {25,IR(0, 0),IR(15082, 12)/* NonReadable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {26,IR(0, 0),IR(15094, 8)/* Uniform */,IR(0, 0),IR(108, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {27,IR(4, 1),IR(15128, 10)/* UniformId */,IR(0, 0),IR(108, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {28,IR(0, 0),IR(15138, 20)/* SaturatedConversion */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {29,IR(0, 1),IR(15158, 7)/* Stream */,IR(0, 0),IR(110, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {30,IR(0, 1),IR(15165, 9)/* Location */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {31,IR(0, 1),IR(15174, 10)/* Component */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {32,IR(0, 1),IR(15184, 6)/* Index */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {33,IR(0, 1),IR(15190, 8)/* Binding */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {34,IR(0, 1),IR(15198, 14)/* DescriptorSet */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {35,IR(0, 1),IR(15212, 7)/* Offset */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {36,IR(0, 1),IR(15219, 10)/* XfbBuffer */,IR(0, 0),IR(111, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {37,IR(0, 1),IR(15229, 10)/* XfbStride */,IR(0, 0),IR(111, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {38,IR(5, 1),IR(15285, 14)/* FuncParamAttr */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {39,IR(6, 1),IR(15333, 15)/* FPRoundingMode */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {40,IR(7, 1),IR(15383, 15)/* FPFastMathMode */,IR(0, 0),IR(112, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {41,IR(8, 2),IR(15460, 18)/* LinkageAttributes */,IR(0, 0),IR(114, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {42,IR(0, 0),IR(15478, 14)/* NoContraction */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {43,IR(0, 1),IR(15492, 21)/* InputAttachmentIndex */,IR(0, 0),IR(92, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {44,IR(0, 1),IR(15513, 10)/* Alignment */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {45,IR(0, 1),IR(15523, 14)/* MaxByteOffset */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {46,IR(10, 1),IR(15557, 12)/* AlignmentId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {47,IR(10, 1),IR(15569, 16)/* MaxByteOffsetId */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4469,IR(0, 0),IR(15585, 13)/* NoSignedWrap */,IR(0, 0),IR(1, 0),IR(148, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4470,IR(0, 0),IR(15598, 15)/* NoUnsignedWrap */,IR(0, 0),IR(1, 0),IR(148, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4487,IR(0, 0),IR(15613, 18)/* WeightTextureQCOM */,IR(0, 0),IR(1, 0),IR(49, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4488,IR(0, 0),IR(15631, 22)/* BlockMatchTextureQCOM */,IR(0, 0),IR(1, 0),IR(49, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4499,IR(0, 0),IR(15653, 22)/* BlockMatchSamplerQCOM */,IR(0, 0),IR(1, 0),IR(51, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4999,IR(0, 0),IR(15675, 18)/* ExplicitInterpAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5019,IR(10, 1),IR(15693, 32)/* NodeSharesPayloadLimitsWithAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5020,IR(10, 1),IR(15725, 20)/* NodeMaxPayloadsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5078,IR(0, 0),IR(15745, 23)/* TrackFinishWritingAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5091,IR(10, 1),IR(15768, 20)/* PayloadNodeNameAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5098,IR(10, 1),IR(15788, 25)/* PayloadNodeBaseIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5099,IR(0, 0),IR(15813, 27)/* PayloadNodeSparseArrayAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5100,IR(10, 1),IR(15840, 25)/* PayloadNodeArraySizeAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5105,IR(0, 0),IR(15865, 28)/* PayloadDispatchIndirectAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5248,IR(0, 0),IR(15893, 19)/* OverrideCoverageNV */,IR(0, 0),IR(115, 1),IR(62, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5250,IR(0, 0),IR(15912, 14)/* PassthroughNV */,IR(0, 0),IR(116, 1),IR(63, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5252,IR(0, 0),IR(15926, 19)/* ViewportRelativeNV */,IR(0, 0),IR(91, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5256,IR(0, 1),IR(15945, 28)/* SecondaryViewportRelativeNV */,IR(0, 0),IR(46, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5271,IR(0, 0),IR(15973, 16)/* PerPrimitiveEXT */,IR(51, 1),IR(117, 2),IR(149, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5272,IR(0, 0),IR(16004, 10)/* PerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5273,IR(0, 0),IR(16014, 10)/* PerTaskNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5285,IR(0, 0),IR(16024, 13)/* PerVertexKHR */,IR(52, 1),IR(51, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5300,IR(0, 0),IR(16049, 11)/* NonUniform */,IR(53, 1),IR(94, 1),IR(72, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5355,IR(0, 0),IR(16074, 16)/* RestrictPointer */,IR(54, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5356,IR(0, 0),IR(16109, 15)/* AliasedPointer */,IR(55, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5386,IR(0, 0),IR(16142, 30)/* HitObjectShaderRecordBufferNV */,IR(0, 0),IR(119, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5398,IR(0, 0),IR(16172, 18)/* BindlessSamplerNV */,IR(0, 0),IR(120, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5399,IR(0, 0),IR(16190, 16)/* BindlessImageNV */,IR(0, 0),IR(120, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5400,IR(0, 0),IR(16206, 15)/* BoundSamplerNV */,IR(0, 0),IR(120, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5401,IR(0, 0),IR(16221, 13)/* BoundImageNV */,IR(0, 0),IR(120, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5599,IR(0, 1),IR(16234, 14)/* SIMTCallINTEL */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5602,IR(0, 0),IR(16248, 26)/* ReferencedIndirectlyINTEL */,IR(0, 0),IR(122, 1),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5607,IR(11, 1),IR(16274, 13)/* ClobberINTEL */,IR(0, 0),IR(123, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5608,IR(0, 0),IR(16287, 17)/* SideEffectsINTEL */,IR(0, 0),IR(123, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5624,IR(0, 0),IR(16304, 27)/* VectorComputeVariableINTEL */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5625,IR(0, 1),IR(16331, 21)/* FuncParamIOKindINTEL */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5626,IR(0, 0),IR(16352, 27)/* VectorComputeFunctionINTEL */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5627,IR(0, 0),IR(16379, 15)/* StackCallINTEL */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5628,IR(0, 1),IR(16394, 26)/* GlobalVariableOffsetINTEL */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5634,IR(10, 1),IR(16420, 14)/* CounterBuffer */,IR(56, 1),IR(1, 0),IR(151, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5635,IR(11, 1),IR(16458, 13)/* UserSemantic */,IR(57, 1),IR(1, 0),IR(151, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5636,IR(11, 1),IR(16490, 15)/* UserTypeGOOGLE */,IR(0, 0),IR(1, 0),IR(152, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5822,IR(12, 2),IR(16505, 26)/* FunctionRoundingModeINTEL */,IR(0, 0),IR(124, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5823,IR(14, 2),IR(16562, 24)/* FunctionDenormModeINTEL */,IR(0, 0),IR(124, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5825,IR(0, 0),IR(16586, 14)/* RegisterINTEL */,IR(0, 0),IR(125, 1),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5826,IR(11, 1),IR(16600, 12)/* MemoryINTEL */,IR(0, 0),IR(125, 1),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5827,IR(0, 1),IR(16612, 14)/* NumbanksINTEL */,IR(0, 0),IR(125, 1),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5828,IR(0, 1),IR(16626, 15)/* BankwidthINTEL */,IR(0, 0),IR(125, 1),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5829,IR(0, 1),IR(16641, 22)/* MaxPrivateCopiesINTEL */,IR(0, 0),IR(125, 1),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5830,IR(0, 0),IR(16663, 16)/* SinglepumpINTEL */,IR(0, 0),IR(125, 1),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5831,IR(0, 0),IR(16679, 16)/* DoublepumpINTEL */,IR(0, 0),IR(125, 1),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5832,IR(0, 1),IR(16695, 19)/* MaxReplicatesINTEL */,IR(0, 0),IR(125, 1),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5833,IR(0, 0),IR(16714, 20)/* SimpleDualPortINTEL */,IR(0, 0),IR(125, 1),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5834,IR(16, 2),IR(16734, 11)/* MergeINTEL */,IR(0, 0),IR(125, 1),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5835,IR(18, 1),IR(16787, 14)/* BankBitsINTEL */,IR(0, 0),IR(125, 1),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5836,IR(0, 1),IR(16801, 20)/* ForcePow2DepthINTEL */,IR(0, 0),IR(125, 1),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5883,IR(0, 1),IR(16821, 16)/* StridesizeINTEL */,IR(0, 0),IR(125, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5884,IR(0, 1),IR(16837, 14)/* WordsizeINTEL */,IR(0, 0),IR(125, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5885,IR(0, 0),IR(16851, 18)/* TrueDualPortINTEL */,IR(0, 0),IR(125, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5899,IR(0, 0),IR(16869, 19)/* BurstCoalesceINTEL */,IR(0, 0),IR(126, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5900,IR(0, 1),IR(16888, 15)/* CacheSizeINTEL */,IR(0, 0),IR(126, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5901,IR(0, 0),IR(16903, 28)/* DontStaticallyCoalesceINTEL */,IR(0, 0),IR(126, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5902,IR(0, 1),IR(16931, 14)/* PrefetchINTEL */,IR(0, 0),IR(126, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5905,IR(0, 0),IR(16945, 17)/* StallEnableINTEL */,IR(0, 0),IR(103, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5907,IR(0, 0),IR(16962, 25)/* FuseLoopsInFunctionINTEL */,IR(0, 0),IR(127, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5909,IR(1, 2),IR(16987, 19)/* MathOpDSPModeINTEL */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5914,IR(10, 1),IR(17006, 16)/* AliasScopeINTEL */,IR(0, 0),IR(129, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5915,IR(10, 1),IR(17022, 13)/* NoAliasINTEL */,IR(0, 0),IR(129, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5917,IR(0, 1),IR(17035, 24)/* InitiationIntervalINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5918,IR(0, 1),IR(17059, 20)/* MaxConcurrencyINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5919,IR(0, 1),IR(17079, 20)/* PipelineEnableINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5921,IR(0, 1),IR(17099, 20)/* BufferLocationINTEL */,IR(0, 0),IR(131, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5944,IR(0, 1),IR(17119, 19)/* IOPipeStorageINTEL */,IR(0, 0),IR(132, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6080,IR(19, 2),IR(17172, 31)/* FunctionFloatingPointModeINTEL */,IR(0, 0),IR(124, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6085,IR(0, 0),IR(17203, 25)/* SingleElementVectorINTEL */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6087,IR(0, 0),IR(17228, 35)/* VectorComputeCallableFunctionINTEL */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6140,IR(0, 0),IR(17263, 18)/* MediaBlockIOINTEL */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6151,IR(0, 0),IR(17281, 15)/* StallFreeINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6170,IR(21, 1),IR(17327, 26)/* FPMaxErrorDecorationINTEL */,IR(0, 0),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6172,IR(0, 1),IR(17353, 25)/* LatencyControlLabelINTEL */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6173,IR(22, 3),IR(17378, 30)/* LatencyControlConstraintINTEL */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6175,IR(0, 0),IR(17408, 27)/* ConduitKernelArgumentINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6176,IR(0, 0),IR(17435, 31)/* RegisterMapKernelArgumentINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6177,IR(0, 1),IR(17466, 33)/* MMHostInterfaceAddressWidthINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6178,IR(0, 1),IR(17499, 30)/* MMHostInterfaceDataWidthINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6179,IR(0, 1),IR(17529, 28)/* MMHostInterfaceLatencyINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6180,IR(25, 1),IR(17591, 34)/* MMHostInterfaceReadWriteModeINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6181,IR(0, 1),IR(17625, 29)/* MMHostInterfaceMaxBurstINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6182,IR(0, 1),IR(17654, 32)/* MMHostInterfaceWaitRequestINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6183,IR(0, 0),IR(17686, 26)/* StableKernelArgumentINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6188,IR(26, 2),IR(17751, 16)/* HostAccessINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6190,IR(28, 1),IR(17814, 14)/* InitModeINTEL */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6191,IR(0, 1),IR(17828, 28)/* ImplementInRegisterMapINTEL */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6442,IR(29, 2),IR(17892, 22)/* CacheControlLoadINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6443,IR(31, 2),IR(17951, 23)/* CacheControlStoreINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {0,IR(0, 0),IR(17974, 3)/* 1D */,IR(0, 0),IR(72, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {1,IR(0, 0),IR(17977, 3)/* 2D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {2,IR(0, 0),IR(17980, 3)/* 3D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {3,IR(0, 0),IR(17983, 5)/* Cube */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {4,IR(0, 0),IR(17988, 5)/* Rect */,IR(0, 0),IR(71, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {5,IR(0, 0),IR(17993, 7)/* Buffer */,IR(0, 0),IR(73, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {6,IR(0, 0),IR(18000, 12)/* SubpassData */,IR(0, 0),IR(92, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {4173,IR(0, 0),IR(18012, 17)/* TileImageDataEXT */,IR(0, 0),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {0,IR(0, 1),IR(18029, 12)/* Invocations */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {1,IR(0, 0),IR(18041, 13)/* SpacingEqual */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {2,IR(0, 0),IR(18054, 22)/* SpacingFractionalEven */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {3,IR(0, 0),IR(18076, 21)/* SpacingFractionalOdd */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4,IR(0, 0),IR(18097, 14)/* VertexOrderCw */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5,IR(0, 0),IR(18111, 15)/* VertexOrderCcw */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6,IR(0, 0),IR(18126, 19)/* PixelCenterInteger */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {7,IR(0, 0),IR(18145, 16)/* OriginUpperLeft */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {8,IR(0, 0),IR(18161, 16)/* OriginLowerLeft */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {9,IR(0, 0),IR(18177, 19)/* EarlyFragmentTests */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {10,IR(0, 0),IR(18196, 10)/* PointMode */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {11,IR(0, 0),IR(18206, 4)/* Xfb */,IR(0, 0),IR(111, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {12,IR(0, 0),IR(18210, 15)/* DepthReplacing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {14,IR(0, 0),IR(18225, 13)/* DepthGreater */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {15,IR(0, 0),IR(18238, 10)/* DepthLess */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {16,IR(0, 0),IR(18248, 15)/* DepthUnchanged */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {17,IR(22, 3),IR(18263, 10)/* LocalSize */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {18,IR(22, 3),IR(18273, 14)/* LocalSizeHint */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {19,IR(0, 0),IR(18287, 12)/* InputPoints */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {20,IR(0, 0),IR(18299, 11)/* InputLines */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {21,IR(0, 0),IR(18310, 20)/* InputLinesAdjacency */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {22,IR(0, 0),IR(18330, 10)/* Triangles */,IR(0, 0),IR(12, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {23,IR(0, 0),IR(18340, 24)/* InputTrianglesAdjacency */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {24,IR(0, 0),IR(18364, 6)/* Quads */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {25,IR(0, 0),IR(18370, 9)/* Isolines */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {26,IR(0, 1),IR(18379, 15)/* OutputVertices */,IR(0, 0),IR(141, 4),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {27,IR(0, 0),IR(18394, 13)/* OutputPoints */,IR(0, 0),IR(145, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {28,IR(0, 0),IR(18407, 16)/* OutputLineStrip */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {29,IR(0, 0),IR(18423, 20)/* OutputTriangleStrip */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {30,IR(0, 1),IR(18443, 12)/* VecTypeHint */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {31,IR(0, 0),IR(18455, 15)/* ContractionOff */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {33,IR(0, 0),IR(18470, 12)/* Initializer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {34,IR(0, 0),IR(18482, 10)/* Finalizer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {35,IR(0, 1),IR(5244, 13)/* SubgroupSize */,IR(0, 0),IR(148, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {36,IR(0, 1),IR(18492, 22)/* SubgroupsPerWorkgroup */,IR(0, 0),IR(148, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {37,IR(10, 1),IR(18514, 24)/* SubgroupsPerWorkgroupId */,IR(0, 0),IR(148, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {38,IR(33, 3),IR(18538, 12)/* LocalSizeId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {39,IR(33, 3),IR(18550, 16)/* LocalSizeHintId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4169,IR(0, 0),IR(18566, 34)/* NonCoherentColorAttachmentReadEXT */,IR(0, 0),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4170,IR(0, 0),IR(18600, 34)/* NonCoherentDepthAttachmentReadEXT */,IR(0, 0),IR(149, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4171,IR(0, 0),IR(18634, 36)/* NonCoherentStencilAttachmentReadEXT */,IR(0, 0),IR(150, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4421,IR(0, 0),IR(18670, 30)/* SubgroupUniformControlFlowKHR */,IR(0, 0),IR(3, 1),IR(153, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4446,IR(0, 0),IR(18700, 18)/* PostDepthCoverage */,IR(0, 0),IR(151, 1),IR(42, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4459,IR(0, 1),IR(9288, 15)/* DenormPreserve */,IR(0, 0),IR(152, 1),IR(44, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4460,IR(0, 1),IR(9303, 18)/* DenormFlushToZero */,IR(0, 0),IR(153, 1),IR(44, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4461,IR(0, 1),IR(9321, 25)/* SignedZeroInfNanPreserve */,IR(0, 0),IR(154, 1),IR(44, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4462,IR(0, 1),IR(9346, 16)/* RoundingModeRTE */,IR(0, 0),IR(155, 1),IR(44, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4463,IR(0, 1),IR(9362, 16)/* RoundingModeRTZ */,IR(0, 0),IR(156, 1),IR(44, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4489,IR(0, 0),IR(18718, 34)/* NonCoherentTileAttachmentReadQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4490,IR(22, 3),IR(18752, 20)/* TileShadingRateQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5017,IR(0, 0),IR(18772, 29)/* EarlyAndLateFragmentTestsAMD */,IR(0, 0),IR(3, 1),IR(154, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5027,IR(0, 0),IR(18801, 23)/* StencilRefReplacingEXT */,IR(0, 0),IR(42, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5069,IR(0, 0),IR(18824, 15)/* CoalescingAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5070,IR(10, 1),IR(18839, 15)/* IsApiEntryAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5071,IR(10, 1),IR(18854, 21)/* MaxNodeRecursionAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5072,IR(33, 3),IR(18875, 24)/* StaticNumWorkgroupsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5073,IR(10, 1),IR(6137, 16)/* ShaderIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5077,IR(33, 3),IR(18899, 21)/* MaxNumWorkgroupsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5079,IR(0, 0),IR(18920, 28)/* StencilRefUnchangedFrontAMD */,IR(0, 0),IR(42, 1),IR(155, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5080,IR(0, 0),IR(18948, 26)/* StencilRefGreaterFrontAMD */,IR(0, 0),IR(42, 1),IR(155, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5081,IR(0, 0),IR(18974, 23)/* StencilRefLessFrontAMD */,IR(0, 0),IR(42, 1),IR(155, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5082,IR(0, 0),IR(18997, 27)/* StencilRefUnchangedBackAMD */,IR(0, 0),IR(42, 1),IR(155, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5083,IR(0, 0),IR(19024, 25)/* StencilRefGreaterBackAMD */,IR(0, 0),IR(42, 1),IR(155, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5084,IR(0, 0),IR(19049, 22)/* StencilRefLessBackAMD */,IR(0, 0),IR(42, 1),IR(155, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5088,IR(0, 0),IR(19071, 19)/* QuadDerivativesKHR */,IR(0, 0),IR(157, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5089,IR(0, 0),IR(19090, 20)/* RequireFullQuadsKHR */,IR(0, 0),IR(157, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5102,IR(36, 2),IR(19110, 20)/* SharesInputWithAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5269,IR(0, 0),IR(19130, 15)/* OutputLinesEXT */,IR(58, 1),IR(117, 2),IR(149, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5270,IR(0, 1),IR(19159, 20)/* OutputPrimitivesEXT */,IR(59, 1),IR(117, 2),IR(149, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5289,IR(0, 0),IR(19198, 24)/* DerivativeGroupQuadsKHR */,IR(60, 1),IR(158, 2),IR(69, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5290,IR(0, 0),IR(19245, 25)/* DerivativeGroupLinearKHR */,IR(61, 1),IR(160, 2),IR(69, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5298,IR(0, 0),IR(19294, 19)/* OutputTrianglesEXT */,IR(62, 1),IR(117, 2),IR(149, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5366,IR(0, 0),IR(19331, 25)/* PixelInterlockOrderedEXT */,IR(0, 0),IR(162, 1),IR(76, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5367,IR(0, 0),IR(19356, 27)/* PixelInterlockUnorderedEXT */,IR(0, 0),IR(162, 1),IR(76, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5368,IR(0, 0),IR(19383, 26)/* SampleInterlockOrderedEXT */,IR(0, 0),IR(163, 1),IR(76, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5369,IR(0, 0),IR(19409, 28)/* SampleInterlockUnorderedEXT */,IR(0, 0),IR(163, 1),IR(76, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5370,IR(0, 0),IR(19437, 31)/* ShadingRateInterlockOrderedEXT */,IR(0, 0),IR(164, 1),IR(76, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5371,IR(0, 0),IR(19468, 33)/* ShadingRateInterlockUnorderedEXT */,IR(0, 0),IR(164, 1),IR(76, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5618,IR(0, 1),IR(19501, 27)/* SharedLocalMemorySizeINTEL */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5620,IR(0, 1),IR(19528, 21)/* RoundingModeRTPINTEL */,IR(0, 0),IR(165, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5621,IR(0, 1),IR(19549, 21)/* RoundingModeRTNINTEL */,IR(0, 0),IR(165, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5622,IR(0, 1),IR(19570, 26)/* FloatingPointModeALTINTEL */,IR(0, 0),IR(165, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5623,IR(0, 1),IR(19596, 27)/* FloatingPointModeIEEEINTEL */,IR(0, 0),IR(165, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5893,IR(22, 3),IR(19623, 22)/* MaxWorkgroupSizeINTEL */,IR(0, 0),IR(166, 1),IR(104, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5894,IR(0, 1),IR(19645, 16)/* MaxWorkDimINTEL */,IR(0, 0),IR(166, 1),IR(104, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5895,IR(0, 0),IR(19661, 20)/* NoGlobalOffsetINTEL */,IR(0, 0),IR(166, 1),IR(104, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5896,IR(0, 1),IR(19681, 22)/* NumSIMDWorkitemsINTEL */,IR(0, 0),IR(104, 1),IR(104, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5903,IR(0, 1),IR(19703, 28)/* SchedulerTargetFmaxMhzINTEL */,IR(0, 0),IR(104, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6023,IR(0, 0),IR(19731, 24)/* MaximallyReconvergesKHR */,IR(0, 0),IR(3, 1),IR(157, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6028,IR(36, 2),IR(19755, 18)/* FPFastMathDefault */,IR(0, 0),IR(167, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6154,IR(0, 1),IR(19773, 24)/* StreamingInterfaceINTEL */,IR(0, 0),IR(104, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6160,IR(0, 1),IR(19797, 26)/* RegisterMapInterfaceINTEL */,IR(0, 0),IR(168, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6417,IR(0, 1),IR(19823, 23)/* NamedBarrierCountINTEL */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6461,IR(0, 1),IR(19846, 22)/* MaximumRegistersINTEL */,IR(0, 0),IR(169, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6462,IR(10, 1),IR(19868, 24)/* MaximumRegistersIdINTEL */,IR(0, 0),IR(169, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6463,IR(38, 1),IR(19943, 27)/* NamedMaximumRegistersINTEL */,IR(0, 0),IR(169, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {0,IR(0, 0),IR(19970, 7)/* Vertex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {1,IR(0, 0),IR(19977, 20)/* TessellationControl */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {2,IR(0, 0),IR(19997, 23)/* TessellationEvaluation */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {3,IR(0, 0),IR(4725, 9)/* Geometry */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {4,IR(0, 0),IR(14209, 9)/* Fragment */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5,IR(0, 0),IR(20020, 10)/* GLCompute */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {6,IR(0, 0),IR(4492, 7)/* Kernel */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5267,IR(0, 0),IR(20030, 7)/* TaskNV */,IR(0, 0),IR(50, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5268,IR(0, 0),IR(20037, 7)/* MeshNV */,IR(0, 0),IR(50, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5313,IR(0, 0),IR(20044, 17)/* RayGenerationKHR */,IR(63, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5314,IR(0, 0),IR(20077, 16)/* IntersectionKHR */,IR(64, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5315,IR(0, 0),IR(20108, 10)/* AnyHitKHR */,IR(65, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5316,IR(0, 0),IR(20127, 14)/* ClosestHitKHR */,IR(66, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5317,IR(0, 0),IR(20154, 8)/* MissKHR */,IR(67, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5318,IR(0, 0),IR(20169, 12)/* CallableKHR */,IR(68, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5364,IR(0, 0),IR(20192, 8)/* TaskEXT */,IR(0, 0),IR(53, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5365,IR(0, 0),IR(20200, 8)/* MeshEXT */,IR(0, 0),IR(53, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {0,IR(0, 0),IR(20208, 9)/* Preserve */,IR(0, 0),IR(124, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPDENORM_MODE
  {1,IR(0, 0),IR(20217, 12)/* FlushToZero */,IR(0, 0),IR(124, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPDENORM_MODE
  {0,IR(0, 0),IR(20229, 12)/* BFloat16KHR */,IR(0, 0),IR(86, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {0,IR(0, 0),IR(20241, 5)/* IEEE */,IR(0, 0),IR(124, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPOPERATION_MODE
  {1,IR(0, 0),IR(20246, 4)/* ALT */,IR(0, 0),IR(124, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPOPERATION_MODE
  {0,IR(0, 0),IR(13805, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {1,IR(0, 0),IR(20250, 7)/* NotNaN */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {2,IR(0, 0),IR(20257, 7)/* NotInf */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {4,IR(0, 0),IR(20264, 4)/* NSZ */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {8,IR(0, 0),IR(20268, 11)/* AllowRecip */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {16,IR(0, 0),IR(20279, 5)/* Fast */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {65536,IR(0, 0),IR(20284, 14)/* AllowContract */,IR(69, 1),IR(170, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {131072,IR(0, 0),IR(20321, 13)/* AllowReassoc */,IR(70, 1),IR(170, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {262144,IR(0, 0),IR(20352, 15)/* AllowTransform */,IR(0, 0),IR(167, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {0,IR(0, 0),IR(20367, 4)/* RTE */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {1,IR(0, 0),IR(20371, 4)/* RTZ */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {2,IR(0, 0),IR(20375, 4)/* RTP */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {3,IR(0, 0),IR(20379, 4)/* RTN */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {1,IR(0, 0),IR(20383, 16)/* Vertical2Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {2,IR(0, 0),IR(20399, 16)/* Vertical4Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {4,IR(0, 0),IR(20415, 18)/* Horizontal2Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {8,IR(0, 0),IR(20433, 18)/* Horizontal4Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {0,IR(0, 0),IR(13805, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {1,IR(0, 0),IR(20451, 7)/* Inline */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {2,IR(0, 0),IR(20458, 11)/* DontInline */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {4,IR(0, 0),IR(20469, 5)/* Pure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {8,IR(0, 0),IR(20474, 6)/* Const */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {65536,IR(0, 0),IR(13046, 11)/* OptNoneEXT */,IR(50, 1),IR(172, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {0,IR(0, 0),IR(20480, 5)/* Zext */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {1,IR(0, 0),IR(20485, 5)/* Sext */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {2,IR(0, 0),IR(20490, 6)/* ByVal */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {3,IR(0, 0),IR(20496, 5)/* Sret */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {4,IR(0, 0),IR(20501, 8)/* NoAlias */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {5,IR(0, 0),IR(20509, 10)/* NoCapture */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {6,IR(0, 0),IR(20519, 8)/* NoWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {7,IR(0, 0),IR(20527, 12)/* NoReadWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {5940,IR(0, 0),IR(20539, 20)/* RuntimeAlignedINTEL */,IR(0, 0),IR(173, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {0,IR(0, 0),IR(20559, 7)/* Reduce */,IR(0, 0),IR(174, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {1,IR(0, 0),IR(20566, 14)/* InclusiveScan */,IR(0, 0),IR(174, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {2,IR(0, 0),IR(20580, 14)/* ExclusiveScan */,IR(0, 0),IR(174, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {3,IR(0, 0),IR(20594, 16)/* ClusteredReduce */,IR(0, 0),IR(177, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {6,IR(0, 0),IR(20610, 20)/* PartitionedReduceNV */,IR(0, 0),IR(178, 1),IR(71, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {7,IR(0, 0),IR(20630, 27)/* PartitionedInclusiveScanNV */,IR(0, 0),IR(178, 1),IR(71, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {8,IR(0, 0),IR(20657, 27)/* PartitionedExclusiveScanNV */,IR(0, 0),IR(178, 1),IR(71, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {0,IR(0, 0),IR(20684, 10)/* NoneINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {1,IR(0, 0),IR(20694, 10)/* ReadINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {2,IR(0, 0),IR(20704, 11)/* WriteINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {3,IR(0, 0),IR(20715, 15)/* ReadWriteINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {0,IR(0, 0),IR(13805, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {1,IR(10, 1),IR(20730, 5)/* Bias */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {2,IR(10, 1),IR(20735, 4)/* Lod */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {4,IR(36, 2),IR(20739, 5)/* Grad */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {8,IR(10, 1),IR(20744, 12)/* ConstOffset */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {16,IR(10, 1),IR(15212, 7)/* Offset */,IR(0, 0),IR(179, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {32,IR(10, 1),IR(20756, 13)/* ConstOffsets */,IR(0, 0),IR(179, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {64,IR(10, 1),IR(15009, 7)/* Sample */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {128,IR(10, 1),IR(8276, 7)/* MinLod */,IR(0, 0),IR(180, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {256,IR(4, 1),IR(20769, 19)/* MakeTexelAvailable */,IR(71, 1),IR(181, 1),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {512,IR(4, 1),IR(20810, 17)/* MakeTexelVisible */,IR(72, 1),IR(181, 1),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {1024,IR(0, 0),IR(20847, 16)/* NonPrivateTexel */,IR(73, 1),IR(181, 1),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {2048,IR(0, 0),IR(20882, 14)/* VolatileTexel */,IR(74, 1),IR(181, 1),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {4096,IR(0, 0),IR(20913, 11)/* SignExtend */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {8192,IR(0, 0),IR(20924, 11)/* ZeroExtend */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {16384,IR(0, 0),IR(20935, 12)/* Nontemporal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {65536,IR(10, 1),IR(20947, 8)/* Offsets */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {0,IR(0, 0),IR(20955, 10)/* SnormInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {1,IR(0, 0),IR(20965, 11)/* SnormInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {2,IR(0, 0),IR(20976, 10)/* UnormInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {3,IR(0, 0),IR(20986, 11)/* UnormInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {4,IR(0, 0),IR(20997, 14)/* UnormShort565 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {5,IR(0, 0),IR(21011, 14)/* UnormShort555 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {6,IR(0, 0),IR(21025, 15)/* UnormInt101010 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {7,IR(0, 0),IR(21040, 11)/* SignedInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {8,IR(0, 0),IR(21051, 12)/* SignedInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {9,IR(0, 0),IR(21063, 12)/* SignedInt32 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {10,IR(0, 0),IR(21075, 13)/* UnsignedInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {11,IR(0, 0),IR(21088, 14)/* UnsignedInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {12,IR(0, 0),IR(21102, 14)/* UnsignedInt32 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {13,IR(0, 0),IR(21116, 10)/* HalfFloat */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {14,IR(0, 0),IR(13702, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {15,IR(0, 0),IR(21126, 11)/* UnormInt24 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {16,IR(0, 0),IR(21137, 17)/* UnormInt101010_2 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {17,IR(0, 0),IR(21154, 16)/* UnormInt10X6EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {19,IR(0, 0),IR(21170, 20)/* UnsignedIntRaw10EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {20,IR(0, 0),IR(21190, 20)/* UnsignedIntRaw12EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {21,IR(0, 0),IR(21210, 20)/* UnormInt2_101010EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {22,IR(0, 0),IR(21230, 19)/* UnsignedInt10X6EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {23,IR(0, 0),IR(21249, 19)/* UnsignedInt12X4EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {24,IR(0, 0),IR(21268, 19)/* UnsignedInt14X2EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {25,IR(0, 0),IR(21287, 16)/* UnormInt12X4EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {26,IR(0, 0),IR(21303, 16)/* UnormInt14X2EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {0,IR(0, 0),IR(21319, 2)/* R */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {1,IR(0, 0),IR(21321, 2)/* A */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {2,IR(0, 0),IR(21323, 3)/* RG */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {3,IR(0, 0),IR(21326, 3)/* RA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {4,IR(0, 0),IR(21329, 4)/* RGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {5,IR(0, 0),IR(21333, 5)/* RGBA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {6,IR(0, 0),IR(21338, 5)/* BGRA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {7,IR(0, 0),IR(21343, 5)/* ARGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {8,IR(0, 0),IR(21348, 10)/* Intensity */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {9,IR(0, 0),IR(21358, 10)/* Luminance */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {10,IR(0, 0),IR(21368, 3)/* Rx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {11,IR(0, 0),IR(21371, 4)/* RGx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {12,IR(0, 0),IR(21375, 5)/* RGBx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {13,IR(0, 0),IR(21380, 6)/* Depth */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {14,IR(0, 0),IR(21386, 13)/* DepthStencil */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {15,IR(0, 0),IR(21399, 5)/* sRGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {16,IR(0, 0),IR(21404, 6)/* sRGBx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {17,IR(0, 0),IR(21410, 6)/* sRGBA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {18,IR(0, 0),IR(21416, 6)/* sBGRA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {19,IR(0, 0),IR(21422, 5)/* ABGR */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {0,IR(0, 0),IR(21427, 27)/* InitOnDeviceReprogramINTEL */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {1,IR(0, 0),IR(21454, 23)/* InitOnDeviceResetINTEL */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {0,IR(0, 0),IR(21477, 7)/* NoWait */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {1,IR(0, 0),IR(21484, 11)/* WaitKernel */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {2,IR(0, 0),IR(21495, 14)/* WaitWorkGroup */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {0,IR(0, 0),IR(13805, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {1,IR(0, 0),IR(21509, 12)/* CmdExecTime */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {0,IR(0, 0),IR(13805, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {1,IR(0, 0),IR(21521, 13)/* MayUsePrintf */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {0,IR(0, 0),IR(21534, 7)/* Export */,IR(0, 0),IR(114, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {1,IR(0, 0),IR(21541, 7)/* Import */,IR(0, 0),IR(114, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {2,IR(0, 0),IR(21548, 12)/* LinkOnceODR */,IR(0, 0),IR(114, 1),IR(158, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {0,IR(0, 0),IR(21560, 14)/* UncachedINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {1,IR(0, 0),IR(21574, 12)/* CachedINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {2,IR(0, 0),IR(21586, 15)/* StreamingINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {3,IR(0, 0),IR(21601, 25)/* InvalidateAfterReadINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {4,IR(0, 0),IR(21626, 17)/* ConstCachedINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {0,IR(0, 0),IR(13805, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {1,IR(0, 0),IR(21643, 7)/* Unroll */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {2,IR(0, 0),IR(21650, 11)/* DontUnroll */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {4,IR(0, 0),IR(21661, 19)/* DependencyInfinite */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {8,IR(0, 1),IR(21680, 17)/* DependencyLength */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {16,IR(0, 1),IR(21697, 14)/* MinIterations */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {32,IR(0, 1),IR(21711, 14)/* MaxIterations */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {64,IR(0, 1),IR(21725, 18)/* IterationMultiple */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {128,IR(0, 1),IR(21743, 10)/* PeelCount */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {256,IR(0, 1),IR(21753, 13)/* PartialCount */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {65536,IR(0, 1),IR(17035, 24)/* InitiationIntervalINTEL */,IR(0, 0),IR(182, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {131072,IR(0, 1),IR(17059, 20)/* MaxConcurrencyINTEL */,IR(0, 0),IR(182, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {262144,IR(0, 1),IR(21766, 21)/* DependencyArrayINTEL */,IR(0, 0),IR(182, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {524288,IR(0, 1),IR(17079, 20)/* PipelineEnableINTEL */,IR(0, 0),IR(182, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {1048576,IR(0, 1),IR(21787, 18)/* LoopCoalesceINTEL */,IR(0, 0),IR(182, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {2097152,IR(0, 1),IR(21805, 21)/* MaxInterleavingINTEL */,IR(0, 0),IR(182, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {4194304,IR(0, 1),IR(21826, 26)/* SpeculatedIterationsINTEL */,IR(0, 0),IR(182, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {8388608,IR(0, 0),IR(21852, 14)/* NoFusionINTEL */,IR(0, 0),IR(182, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {16777216,IR(0, 1),IR(21866, 15)/* LoopCountINTEL */,IR(0, 0),IR(182, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {33554432,IR(0, 1),IR(21881, 26)/* MaxReinvocationDelayINTEL */,IR(0, 0),IR(182, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {0,IR(0, 0),IR(13805, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {1,IR(0, 0),IR(21907, 29)/* MatrixASignedComponentsINTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {2,IR(0, 0),IR(21936, 29)/* MatrixBSignedComponentsINTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {4,IR(0, 0),IR(21965, 21)/* MatrixCBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {8,IR(0, 0),IR(21986, 26)/* MatrixResultBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {16,IR(0, 0),IR(22012, 23)/* MatrixAPackedInt8INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {32,IR(0, 0),IR(22035, 23)/* MatrixBPackedInt8INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {64,IR(0, 0),IR(22058, 23)/* MatrixAPackedInt4INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {128,IR(0, 0),IR(22081, 23)/* MatrixBPackedInt4INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {256,IR(0, 0),IR(22104, 17)/* MatrixATF32INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {512,IR(0, 0),IR(22121, 17)/* MatrixBTF32INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {1024,IR(0, 0),IR(22138, 26)/* MatrixAPackedFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {2048,IR(0, 0),IR(22164, 26)/* MatrixBPackedFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {4096,IR(0, 0),IR(22190, 27)/* MatrixAPackedBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {8192,IR(0, 0),IR(22217, 27)/* MatrixBPackedBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {0,IR(0, 0),IR(13805, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {1,IR(0, 0),IR(15043, 9)/* Volatile */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {2,IR(0, 1),IR(22244, 8)/* Aligned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {4,IR(0, 0),IR(20935, 12)/* Nontemporal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {8,IR(4, 1),IR(22252, 21)/* MakePointerAvailable */,IR(75, 1),IR(181, 1),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {16,IR(4, 1),IR(22297, 19)/* MakePointerVisible */,IR(76, 1),IR(181, 1),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {32,IR(0, 0),IR(22338, 18)/* NonPrivatePointer */,IR(77, 1),IR(181, 1),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {65536,IR(10, 1),IR(22377, 20)/* AliasScopeINTELMask */,IR(0, 0),IR(129, 1),IR(109, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {131072,IR(10, 1),IR(22397, 17)/* NoAliasINTELMask */,IR(0, 0),IR(129, 1),IR(109, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {0,IR(0, 0),IR(22414, 7)/* Simple */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {1,IR(0, 0),IR(22421, 8)/* GLSL450 */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {2,IR(0, 0),IR(22429, 7)/* OpenCL */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {3,IR(0, 0),IR(22436, 7)/* Vulkan */,IR(78, 1),IR(181, 1),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {0,IR(0, 0),IR(22453, 8)/* Relaxed */,IR(79, 1),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {2,IR(0, 0),IR(22461, 8)/* Acquire */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {4,IR(0, 0),IR(22469, 8)/* Release */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {8,IR(0, 0),IR(22477, 15)/* AcquireRelease */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {16,IR(0, 0),IR(22492, 23)/* SequentiallyConsistent */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {64,IR(0, 0),IR(22515, 14)/* UniformMemory */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {128,IR(0, 0),IR(22529, 15)/* SubgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {256,IR(0, 0),IR(22544, 16)/* WorkgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {512,IR(0, 0),IR(22560, 21)/* CrossWorkgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {1024,IR(0, 0),IR(22581, 20)/* AtomicCounterMemory */,IR(0, 0),IR(80, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {2048,IR(0, 0),IR(22601, 12)/* ImageMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {4096,IR(0, 0),IR(22613, 13)/* OutputMemory */,IR(80, 1),IR(181, 1),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {8192,IR(0, 0),IR(22642, 14)/* MakeAvailable */,IR(81, 1),IR(181, 1),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {16384,IR(0, 0),IR(22673, 12)/* MakeVisible */,IR(82, 1),IR(181, 1),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {32768,IR(0, 0),IR(15043, 9)/* Volatile */,IR(0, 0),IR(181, 1),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {0,IR(0, 0),IR(22700, 10)/* AutoINTEL */,IR(0, 0),IR(169, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS
  {0,IR(0, 0),IR(22710, 5)/* WRAP */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {1,IR(0, 0),IR(22715, 4)/* SAT */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {2,IR(0, 0),IR(22719, 9)/* SAT_ZERO */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {3,IR(0, 0),IR(22728, 8)/* SAT_SYM */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {0,IR(0, 0),IR(22736, 25)/* PackedVectorFormat4x8Bit */,IR(83, 1),IR(1, 0),IR(118, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {0,IR(0, 0),IR(22789, 4)/* TRN */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {1,IR(0, 0),IR(22793, 9)/* TRN_ZERO */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {2,IR(0, 0),IR(22802, 4)/* RND */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {3,IR(0, 0),IR(22806, 9)/* RND_ZERO */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {4,IR(0, 0),IR(22815, 8)/* RND_INF */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {5,IR(0, 0),IR(22823, 12)/* RND_MIN_INF */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {6,IR(0, 0),IR(22835, 9)/* RND_CONV */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {7,IR(0, 0),IR(22844, 13)/* RND_CONV_ODD */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {0,IR(0, 0),IR(13805, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {1,IR(0, 0),IR(22857, 25)/* RobustnessPerComponentNV */,IR(0, 0),IR(184, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {2,IR(0, 0),IR(22882, 23)/* RobustnessPerElementNV */,IR(0, 0),IR(184, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {0,IR(0, 0),IR(14557, 8)/* NoneKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {1,IR(0, 0),IR(22905, 10)/* OpaqueKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {2,IR(0, 0),IR(22915, 12)/* NoOpaqueKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {4,IR(0, 0),IR(22927, 23)/* TerminateOnFirstHitKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {8,IR(0, 0),IR(22950, 24)/* SkipClosestHitShaderKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {16,IR(0, 0),IR(22974, 27)/* CullBackFacingTrianglesKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {32,IR(0, 0),IR(23001, 28)/* CullFrontFacingTrianglesKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {64,IR(0, 0),IR(23029, 14)/* CullOpaqueKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {128,IR(0, 0),IR(23043, 16)/* CullNoOpaqueKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {256,IR(0, 0),IR(23059, 17)/* SkipTrianglesKHR */,IR(84, 1),IR(185, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {512,IR(0, 0),IR(23100, 13)/* SkipAABBsKHR */,IR(0, 0),IR(185, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {1024,IR(0, 0),IR(23113, 30)/* ForceOpacityMicromap2StateEXT */,IR(0, 0),IR(186, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {0,IR(0, 0),IR(23143, 41)/* RayQueryCandidateIntersectionTriangleKHR */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {1,IR(0, 0),IR(23184, 37)/* RayQueryCandidateIntersectionAABBKHR */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {0,IR(0, 0),IR(23221, 37)/* RayQueryCommittedIntersectionNoneKHR */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {1,IR(0, 0),IR(23258, 41)/* RayQueryCommittedIntersectionTriangleKHR */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {2,IR(0, 0),IR(23299, 42)/* RayQueryCommittedIntersectionGeneratedKHR */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {0,IR(0, 0),IR(23341, 33)/* RayQueryCandidateIntersectionKHR */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {1,IR(0, 0),IR(23374, 33)/* RayQueryCommittedIntersectionKHR */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {0,IR(0, 0),IR(13805, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {1,IR(0, 0),IR(23407, 12)/* ClampToEdge */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {2,IR(0, 0),IR(23419, 6)/* Clamp */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {3,IR(0, 0),IR(23425, 7)/* Repeat */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {4,IR(0, 0),IR(23432, 15)/* RepeatMirrored */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {0,IR(0, 0),IR(23447, 8)/* Nearest */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {1,IR(0, 0),IR(23455, 7)/* Linear */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {0,IR(0, 0),IR(23462, 8)/* Unknown */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {1,IR(0, 0),IR(23470, 8)/* Rgba32f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {2,IR(0, 0),IR(23478, 8)/* Rgba16f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {3,IR(0, 0),IR(23486, 5)/* R32f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {4,IR(0, 0),IR(23491, 6)/* Rgba8 */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {5,IR(0, 0),IR(23497, 11)/* Rgba8Snorm */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {6,IR(0, 0),IR(23508, 6)/* Rg32f */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {7,IR(0, 0),IR(23514, 6)/* Rg16f */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {8,IR(0, 0),IR(23520, 13)/* R11fG11fB10f */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {9,IR(0, 0),IR(23533, 5)/* R16f */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {10,IR(0, 0),IR(23538, 7)/* Rgba16 */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {11,IR(0, 0),IR(23545, 8)/* Rgb10A2 */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {12,IR(0, 0),IR(23553, 5)/* Rg16 */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {13,IR(0, 0),IR(23558, 4)/* Rg8 */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {14,IR(0, 0),IR(23562, 4)/* R16 */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {15,IR(0, 0),IR(23566, 3)/* R8 */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {16,IR(0, 0),IR(23569, 12)/* Rgba16Snorm */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {17,IR(0, 0),IR(23581, 10)/* Rg16Snorm */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {18,IR(0, 0),IR(23591, 9)/* Rg8Snorm */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {19,IR(0, 0),IR(23600, 9)/* R16Snorm */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {20,IR(0, 0),IR(23609, 8)/* R8Snorm */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {21,IR(0, 0),IR(23617, 8)/* Rgba32i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {22,IR(0, 0),IR(23625, 8)/* Rgba16i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {23,IR(0, 0),IR(23633, 7)/* Rgba8i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {24,IR(0, 0),IR(23640, 5)/* R32i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {25,IR(0, 0),IR(23645, 6)/* Rg32i */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {26,IR(0, 0),IR(23651, 6)/* Rg16i */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {27,IR(0, 0),IR(23657, 5)/* Rg8i */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {28,IR(0, 0),IR(23662, 5)/* R16i */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {29,IR(0, 0),IR(23667, 4)/* R8i */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {30,IR(0, 0),IR(23671, 9)/* Rgba32ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {31,IR(0, 0),IR(23680, 9)/* Rgba16ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {32,IR(0, 0),IR(23689, 8)/* Rgba8ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {33,IR(0, 0),IR(23697, 6)/* R32ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {34,IR(0, 0),IR(23703, 10)/* Rgb10a2ui */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {35,IR(0, 0),IR(23713, 7)/* Rg32ui */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {36,IR(0, 0),IR(23720, 7)/* Rg16ui */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {37,IR(0, 0),IR(23727, 6)/* Rg8ui */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {38,IR(0, 0),IR(23733, 6)/* R16ui */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {39,IR(0, 0),IR(23739, 5)/* R8ui */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {40,IR(0, 0),IR(23744, 6)/* R64ui */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {41,IR(0, 0),IR(23750, 5)/* R64i */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {0,IR(0, 0),IR(23755, 12)/* CrossDevice */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {1,IR(0, 0),IR(23767, 7)/* Device */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {2,IR(0, 0),IR(23774, 10)/* Workgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {3,IR(0, 0),IR(23784, 9)/* Subgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {4,IR(0, 0),IR(23793, 11)/* Invocation */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {5,IR(0, 0),IR(23804, 12)/* QueueFamily */,IR(85, 1),IR(181, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {6,IR(0, 0),IR(23831, 14)/* ShaderCallKHR */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {0,IR(0, 0),IR(13805, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {1,IR(0, 0),IR(23845, 8)/* Flatten */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {2,IR(0, 0),IR(23853, 12)/* DontFlatten */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {1,IR(0, 0),IR(23865, 29)/* IdentifierPossibleDuplicates */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS
  {0,IR(0, 0),IR(13674, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(13686, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(13694, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {3,IR(0, 0),IR(13702, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(13708, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(13715, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(13726, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(13735, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(13748, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(13754, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(13764, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(13770, 15)/* ImportedModule */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {1,IR(0, 0),IR(13785, 20)/* ImportedDeclaration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {0,IR(0, 0),IR(13805, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(13810, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(13826, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(13840, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(13853, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(13865, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(13882, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(13894, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(13909, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(13922, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(13937, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(13955, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(13972, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(13993, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(14013, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(14033, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {16384,IR(0, 0),IR(14049, 16)/* FlagIsEnumClass */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {32768,IR(0, 0),IR(14065, 20)/* FlagTypePassByValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {65536,IR(0, 0),IR(14085, 24)/* FlagTypePassByReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {131072,IR(0, 0),IR(23894, 26)/* FlagUnknownPhysicalLayout */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(14109, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {1,IR(0, 0),IR(14115, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {2,IR(0, 0),IR(14120, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {3,IR(10, 1),IR(14159, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {4,IR(36, 2),IR(14170, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {5,IR(0, 0),IR(14179, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {6,IR(0, 0),IR(14184, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {7,IR(0, 0),IR(14191, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {8,IR(10, 1),IR(14202, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {9,IR(36, 2),IR(14209, 9)/* Fragment */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {0,IR(0, 0),IR(14218, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(14228, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(14241, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {3,IR(0, 0),IR(14254, 11)/* AtomicType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(23462, 8)/* Unknown */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {1,IR(0, 0),IR(23920, 5)/* ESSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {2,IR(0, 0),IR(23925, 5)/* GLSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {3,IR(0, 0),IR(23930, 9)/* OpenCL_C */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {4,IR(0, 0),IR(23939, 11)/* OpenCL_CPP */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {5,IR(0, 0),IR(23950, 5)/* HLSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {6,IR(0, 0),IR(23955, 15)/* CPP_for_OpenCL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {7,IR(0, 0),IR(23970, 5)/* SYCL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {8,IR(0, 0),IR(23975, 7)/* HERO_C */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {9,IR(0, 0),IR(23982, 5)/* NZSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {10,IR(0, 0),IR(23987, 5)/* WGSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {11,IR(0, 0),IR(23992, 6)/* Slang */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {12,IR(0, 0),IR(23998, 4)/* Zig */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {13,IR(0, 0),IR(24002, 5)/* Rust */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {0,IR(0, 0),IR(24007, 16)/* UniformConstant */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {1,IR(0, 0),IR(24023, 6)/* Input */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {2,IR(0, 0),IR(15094, 8)/* Uniform */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {3,IR(0, 0),IR(24029, 7)/* Output */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4,IR(0, 0),IR(23774, 10)/* Workgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5,IR(0, 0),IR(24036, 15)/* CrossWorkgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {6,IR(0, 0),IR(24051, 8)/* Private */,IR(0, 0),IR(190, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {7,IR(0, 0),IR(24059, 9)/* Function */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {8,IR(0, 0),IR(24068, 8)/* Generic */,IR(0, 0),IR(192, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {9,IR(0, 0),IR(24076, 13)/* PushConstant */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {10,IR(0, 0),IR(24089, 14)/* AtomicCounter */,IR(0, 0),IR(80, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {11,IR(0, 0),IR(24103, 6)/* Image */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {12,IR(0, 0),IR(24109, 14)/* StorageBuffer */,IR(0, 0),IR(3, 1),IR(159, 2),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4172,IR(0, 0),IR(24123, 13)/* TileImageEXT */,IR(0, 0),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4491,IR(0, 0),IR(24136, 19)/* TileAttachmentQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5068,IR(0, 0),IR(24155, 16)/* NodePayloadAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5328,IR(0, 0),IR(24171, 16)/* CallableDataKHR */,IR(86, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5329,IR(0, 0),IR(24202, 24)/* IncomingCallableDataKHR */,IR(87, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5338,IR(0, 0),IR(24249, 14)/* RayPayloadKHR */,IR(88, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5339,IR(0, 0),IR(24276, 16)/* HitAttributeKHR */,IR(89, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5342,IR(0, 0),IR(24307, 22)/* IncomingRayPayloadKHR */,IR(90, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5343,IR(0, 0),IR(24350, 22)/* ShaderRecordBufferKHR */,IR(91, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5349,IR(0, 0),IR(24393, 22)/* PhysicalStorageBuffer */,IR(92, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5385,IR(0, 0),IR(24440, 21)/* HitObjectAttributeNV */,IR(0, 0),IR(119, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5402,IR(0, 0),IR(24461, 24)/* TaskPayloadWorkgroupEXT */,IR(0, 0),IR(53, 1),IR(23, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5605,IR(0, 0),IR(24485, 17)/* CodeSectionINTEL */,IR(0, 0),IR(193, 1),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5936,IR(0, 0),IR(24502, 16)/* DeviceOnlyINTEL */,IR(0, 0),IR(194, 1),IR(113, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5937,IR(0, 0),IR(24518, 14)/* HostOnlyINTEL */,IR(0, 0),IR(194, 1),IR(113, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {0,IR(0, 0),IR(21560, 14)/* UncachedINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {1,IR(0, 0),IR(24532, 18)/* WriteThroughINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {2,IR(0, 0),IR(24550, 15)/* WriteBackINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {3,IR(0, 0),IR(21586, 15)/* StreamingINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {0,IR(0, 0),IR(13805, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {1,IR(10, 1),IR(24565, 11)/* TensorView */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {2,IR(10, 1),IR(24576, 11)/* DecodeFunc */,IR(0, 0),IR(196, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {0,IR(0, 0),IR(24587, 10)/* Undefined */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {1,IR(0, 0),IR(15052, 9)/* Constant */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {2,IR(0, 0),IR(23407, 12)/* ClampToEdge */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {3,IR(0, 0),IR(23425, 7)/* Repeat */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {4,IR(0, 0),IR(23432, 15)/* RepeatMirrored */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
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
    case SPV_OPERAND_TYPE_BUILT_IN: return IR(7, 126);
    case SPV_OPERAND_TYPE_CAPABILITY: return IR(133, 263);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(396, 8);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(404, 3);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(407, 2);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS: return IR(409, 19);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION: return IR(428, 10);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(438, 4);
    case SPV_OPERAND_TYPE_COMPONENT_TYPE: return IR(442, 15);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT: return IR(457, 4);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS: return IR(461, 6);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE: return IR(467, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE: return IR(470, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT: return IR(473, 4);
    case SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(477, 8);
    case SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE: return IR(485, 3);
    case SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS: return IR(488, 16);
    case SPV_OPERAND_TYPE_DEBUG_OPERATION: return IR(504, 9);
    case SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER: return IR(513, 3);
    case SPV_OPERAND_TYPE_DECORATION: return IR(516, 142);
    case SPV_OPERAND_TYPE_DIMENSIONALITY: return IR(658, 8);
    case SPV_OPERAND_TYPE_EXECUTION_MODE: return IR(666, 96);
    case SPV_OPERAND_TYPE_EXECUTION_MODEL: return IR(762, 17);
    case SPV_OPERAND_TYPE_FPDENORM_MODE: return IR(779, 2);
    case SPV_OPERAND_TYPE_FPENCODING: return IR(781, 1);
    case SPV_OPERAND_TYPE_FPOPERATION_MODE: return IR(782, 2);
    case SPV_OPERAND_TYPE_FP_FAST_MATH_MODE: return IR(784, 9);
    case SPV_OPERAND_TYPE_FP_ROUNDING_MODE: return IR(793, 4);
    case SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE: return IR(797, 4);
    case SPV_OPERAND_TYPE_FUNCTION_CONTROL: return IR(801, 6);
    case SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE: return IR(807, 9);
    case SPV_OPERAND_TYPE_GROUP_OPERATION: return IR(816, 7);
    case SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER: return IR(823, 4);
    case SPV_OPERAND_TYPE_IMAGE: return IR(827, 17);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE: return IR(844, 26);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER: return IR(870, 20);
    case SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER: return IR(890, 2);
    case SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS: return IR(892, 3);
    case SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO: return IR(895, 2);
    case SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS: return IR(897, 2);
    case SPV_OPERAND_TYPE_LINKAGE_TYPE: return IR(899, 3);
    case SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL: return IR(902, 5);
    case SPV_OPERAND_TYPE_LOOP_CONTROL: return IR(907, 20);
    case SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(927, 15);
    case SPV_OPERAND_TYPE_MEMORY_ACCESS: return IR(942, 9);
    case SPV_OPERAND_TYPE_MEMORY_MODEL: return IR(951, 4);
    case SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID: return IR(955, 15);
    case SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS: return IR(970, 1);
    case SPV_OPERAND_TYPE_OVERFLOW_MODES: return IR(971, 4);
    case SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT: return IR(975, 1);
    case SPV_OPERAND_TYPE_QUANTIZATION_MODES: return IR(976, 8);
    case SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS: return IR(984, 3);
    case SPV_OPERAND_TYPE_RAY_FLAGS: return IR(987, 12);
    case SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE: return IR(999, 2);
    case SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE: return IR(1001, 3);
    case SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION: return IR(1004, 2);
    case SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE: return IR(1006, 5);
    case SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE: return IR(1011, 2);
    case SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT: return IR(1013, 42);
    case SPV_OPERAND_TYPE_SCOPE_ID: return IR(1055, 7);
    case SPV_OPERAND_TYPE_SELECTION_CONTROL: return IR(1062, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS: return IR(1065, 1);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(1066, 8);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(1074, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(1077, 2);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS: return IR(1079, 20);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION: return IR(1099, 10);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(1109, 4);
    case SPV_OPERAND_TYPE_SOURCE_LANGUAGE: return IR(1113, 14);
    case SPV_OPERAND_TYPE_STORAGE_CLASS: return IR(1127, 28);
    case SPV_OPERAND_TYPE_STORE_CACHE_CONTROL: return IR(1155, 4);
    case SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS: return IR(1159, 3);
    case SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE: return IR(1162, 5);
    case SPV_OPERAND_TYPE_OPTIONAL_IMAGE: return IR(827, 17);
    case SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS: return IR(942, 9);
    case SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT: return IR(975, 1);
    case SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS: return IR(461, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(927, 15);
    case SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS: return IR(984, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_FPENCODING: return IR(781, 1);
    default: break;
  }
  return IR(0,0);
}

// Operand names and index into kOperandsByValue, ordered by (operand kind, name)
// The fields in order are:
//   name, either the primary name or an alias, indexing into kStrings
//   index into the kOperandsByValue array
static const std::array<NameIndex, 1261> kOperandNames{{
  {IR(4483, 9), 0}, // 0 ReadOnly in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(4509, 10), 2}, // 1 ReadWrite in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(4499, 10), 1}, // 2 WriteOnly in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(4519, 8), 3}, // 3 Logical in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(4527, 11), 4}, // 4 Physical32 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(4548, 11), 5}, // 5 Physical64 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(4559, 24), 6}, // 6 PhysicalStorageBuffer64 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(4583, 27), 6}, // 7 PhysicalStorageBuffer64EXT in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(6493, 13), 92}, // 8 BaryCoordKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6506, 12), 92}, // 9 BaryCoordNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5888, 20), 68}, // 10 BaryCoordNoPerspAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5908, 28), 69}, // 11 BaryCoordNoPerspCentroidAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6541, 20), 93}, // 12 BaryCoordNoPerspKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6561, 19), 93}, // 13 BaryCoordNoPerspNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5936, 26), 70}, // 14 BaryCoordNoPerspSampleAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6033, 22), 74}, // 15 BaryCoordPullModelAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5962, 19), 71}, // 16 BaryCoordSmoothAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5981, 27), 72}, // 17 BaryCoordSmoothCentroidAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6008, 25), 73}, // 18 BaryCoordSmoothSampleAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5692, 13), 59}, // 19 BaseInstance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5666, 11), 58}, // 20 BaseVertex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4667, 13), 9}, // 21 ClipDistance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6400, 22), 87}, // 22 ClipDistancePerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7699, 12), 131}, // 23 ClusterIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5430, 13), 49}, // 24 CoreCountARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5404, 10), 48}, // 25 CoreIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5443, 13), 50}, // 26 CoreMaxIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4680, 13), 10}, // 27 CullDistance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6422, 22), 88}, // 28 CullDistancePerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7752, 12), 132}, // 29 CullMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6748, 17), 99}, // 30 CullPrimitiveEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7152, 17), 113}, // 31 CurrentRayTimeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5762, 12), 62}, // 32 DeviceIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5705, 10), 60}, // 33 DrawIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5194, 22), 37}, // 34 EnqueuedWorkgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4964, 10), 21}, // 35 FragCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5050, 10), 27}, // 36 FragDepth in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6626, 23), 95}, // 37 FragInvocationCountEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6580, 12), 94}, // 38 FragSizeEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6055, 18), 75}, // 39 FragStencilRefEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6592, 15), 94}, // 40 FragmentSizeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4985, 12), 23}, // 41 FrontFacing in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6312, 16), 83}, // 42 FullyCoveredEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5135, 19), 33}, // 43 GlobalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5229, 15), 39}, // 44 GlobalLinearId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5216, 13), 38}, // 45 GlobalOffset in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5183, 11), 36}, // 46 GlobalSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5060, 17), 28}, // 47 HelperInvocation in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7454, 11), 120}, // 48 HitIsLSSNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7412, 14), 119}, // 49 HitIsSphereNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7634, 33), 128}, // 50 HitKindBackFacingMicroTriangleNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7600, 34), 127}, // 51 HitKindFrontFacingMicroTriangleNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7131, 11), 112}, // 52 HitKindKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7142, 10), 112}, // 53 HitKindNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7582, 18), 126}, // 54 HitLSSPositionsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7685, 14), 130}, // 55 HitLSSRadiiNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7316, 37), 116}, // 56 HitMicroTriangleVertexBarycentricsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7249, 34), 115}, // 57 HitMicroTriangleVertexPositionsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7504, 20), 121}, // 58 HitSpherePositionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7667, 18), 129}, // 59 HitSphereRadiusNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7124, 7), 111}, // 60 HitTNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7192, 30), 114}, // 61 HitTriangleVertexPositionsKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7353, 20), 117}, // 62 IncomingRayFlagsKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7373, 19), 117}, // 63 IncomingRayFlagsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7013, 23), 108}, // 64 InstanceCustomIndexKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7036, 22), 108}, // 65 InstanceCustomIndexNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4702, 11), 12}, // 66 InstanceId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5390, 14), 47}, // 67 InstanceIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4803, 13), 14}, // 68 InvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6649, 22), 95}, // 69 InvocationsPerPixelNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6765, 12), 100}, // 70 LaunchIdKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6777, 11), 100}, // 71 LaunchIdNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6788, 14), 101}, // 72 LaunchSizeKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6802, 13), 101}, // 73 LaunchSizeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4816, 6), 15}, // 74 Layer in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6444, 15), 89}, // 75 LayerPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5117, 18), 32}, // 76 LocalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5154, 21), 34}, // 77 LocalInvocationIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6459, 16), 90}, // 78 MeshViewCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6475, 18), 91}, // 79 MeshViewIndicesNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5320, 21), 43}, // 80 NumEnqueuedSubgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5307, 13), 42}, // 81 NumSubgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5077, 14), 29}, // 82 NumWorkgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6928, 22), 105}, // 83 ObjectRayDirectionKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6950, 21), 105}, // 84 ObjectRayDirectionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6891, 19), 104}, // 85 ObjectRayOriginKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6910, 18), 104}, // 86 ObjectRayOriginNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7058, 17), 109}, // 87 ObjectToWorldKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7075, 16), 109}, // 88 ObjectToWorldNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4950, 14), 20}, // 89 PatchVertices in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4974, 11), 22}, // 90 PointCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4657, 10), 8}, // 91 PointSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4641, 9), 7}, // 92 Position in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6252, 18), 81}, // 93 PositionPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6364, 17), 85}, // 94 PrimitiveCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4713, 12), 13}, // 95 PrimitiveId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6381, 19), 86}, // 96 PrimitiveIndicesNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6696, 24), 97}, // 97 PrimitiveLineIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6671, 25), 96}, // 98 PrimitivePointIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5715, 24), 61}, // 99 PrimitiveShadingRateKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6720, 28), 98}, // 100 PrimitiveTriangleIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7392, 20), 118}, // 101 RayGeometryIndexKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6992, 11), 107}, // 102 RayTmaxKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7003, 10), 107}, // 103 RayTmaxNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6971, 11), 106}, // 104 RayTminKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6982, 10), 106}, // 105 RayTminNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6090, 29), 76}, // 106 RemainingRecursionLevelsAMDX in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7556, 10), 123}, // 107 SMCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7575, 7), 125}, // 108 SMIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4997, 9), 24}, // 109 SampleId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5039, 11), 26}, // 110 SampleMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5024, 15), 25}, // 111 SamplePosition in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6189, 20), 79}, // 112 SecondaryPositionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6228, 24), 80}, // 113 SecondaryViewportMaskNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6137, 16), 77}, // 114 ShaderIndexAMDX in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5806, 15), 64}, // 115 ShadingRateKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5479, 15), 53}, // 116 SubgroupEqMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5494, 18), 53}, // 117 SubgroupEqMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5534, 15), 54}, // 118 SubgroupGeMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5549, 18), 54}, // 119 SubgroupGeMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5567, 15), 55}, // 120 SubgroupGtMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5582, 18), 55}, // 121 SubgroupGtMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5341, 11), 44}, // 122 SubgroupId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5600, 15), 56}, // 123 SubgroupLeMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5615, 18), 56}, // 124 SubgroupLeMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5352, 26), 45}, // 125 SubgroupLocalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5633, 15), 57}, // 126 SubgroupLtMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5648, 18), 57}, // 127 SubgroupLtMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5291, 16), 41}, // 128 SubgroupMaxSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5244, 13), 40}, // 129 SubgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6352, 12), 84}, // 130 TaskCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4940, 10), 19}, // 131 TessCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4925, 15), 18}, // 132 TessLevelInner in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4910, 15), 17}, // 133 TessLevelOuter in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5870, 18), 67}, // 134 TileApronSizeQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5852, 18), 66}, // 135 TileDimensionQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5821, 15), 65}, // 136 TileOffsetQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4693, 9), 11}, // 137 VertexId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5378, 12), 46}, // 138 VertexIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5786, 10), 63}, // 139 ViewIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4862, 14), 16}, // 140 ViewportIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6153, 15), 78}, // 141 ViewportMaskNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6290, 22), 82}, // 142 ViewportMaskPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5456, 10), 51}, // 143 WarpIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7566, 9), 124}, // 144 WarpIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5466, 13), 52}, // 145 WarpMaxIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7524, 13), 122}, // 146 WarpsPerSMNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5175, 8), 35}, // 147 WorkDim in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5105, 12), 31}, // 148 WorkgroupId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5091, 14), 30}, // 149 WorkgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6850, 21), 103}, // 150 WorldRayDirectionKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6871, 20), 103}, // 151 WorldRayDirectionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6815, 18), 102}, // 152 WorldRayOriginKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6833, 17), 102}, // 153 WorldRayOriginNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7091, 17), 110}, // 154 WorldToObjectKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7108, 16), 110}, // 155 WorldToObjectNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4538, 10), 137}, // 156 Addresses in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12603, 34), 352}, // 157 ArbitraryPrecisionFixedPointINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12291, 37), 340}, // 158 ArbitraryPrecisionFloatingPointINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12259, 32), 339}, // 159 ArbitraryPrecisionIntegersINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13153, 19), 376}, // 160 ArithmeticFenceEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11924, 9), 325}, // 161 AsmINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13070, 20), 372}, // 162 AtomicFloat16AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11979, 23), 328}, // 163 AtomicFloat16MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11452, 22), 303}, // 164 AtomicFloat16VectorNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12986, 20), 368}, // 165 AtomicFloat32AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11933, 23), 326}, // 166 AtomicFloat32MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13006, 20), 369}, // 167 AtomicFloat64AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11956, 23), 327}, // 168 AtomicFloat64MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7932, 14), 153}, // 169 AtomicStorage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9164, 17), 223}, // 170 AtomicStorageOps in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13111, 24), 374}, // 171 BFloat16ConversionINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9775, 29), 256}, // 172 BFloat16CooperativeMatrixKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9753, 22), 255}, // 173 BFloat16DotProductKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9737, 16), 254}, // 174 BFloat16TypeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11389, 18), 300}, // 175 BindlessTextureNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12930, 16), 365}, // 176 BitInstructions in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12702, 19), 356}, // 177 BlockingPipesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13635, 19), 394}, // 178 CacheControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4667, 13), 163}, // 179 ClipDistance in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11047, 32), 289}, // 180 ComputeDerivativeGroupLinearKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11079, 31), 289}, // 181 ComputeDerivativeGroupLinearNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9927, 31), 268}, // 182 ComputeDerivativeGroupQuadsKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9958, 30), 268}, // 183 ComputeDerivativeGroupQuadsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11629, 30), 312}, // 184 CooperativeMatrixBlockLoadsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11522, 31), 309}, // 185 CooperativeMatrixConversionsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9716, 21), 363}, // 186 CooperativeMatrixKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8805, 28), 207}, // 187 CooperativeMatrixLayoutsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11135, 20), 291}, // 188 CooperativeMatrixNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11553, 40), 310}, // 189 CooperativeMatrixPerElementOperationsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11492, 30), 308}, // 190 CooperativeMatrixReductionsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11593, 36), 311}, // 191 CooperativeMatrixTensorAddressingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11432, 20), 302}, // 192 CooperativeVectorNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11659, 28), 313}, // 193 CooperativeVectorTrainingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5414, 16), 203}, // 194 CoreBuiltinsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4680, 13), 164}, // 195 CullDistance in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13090, 21), 373}, // 196 DebugInfoModuleINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11258, 25), 296}, // 197 DemoteToHelperInvocation in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11283, 28), 296}, // 198 DemoteToHelperInvocationEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9303, 18), 229}, // 199 DenormFlushToZero in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9288, 15), 228}, // 200 DenormPreserve in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8379, 18), 182}, // 201 DerivativeControl in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7903, 14), 151}, // 202 DeviceEnqueue in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5774, 12), 219}, // 203 DeviceGroup in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11311, 23), 297}, // 204 DisplacementMicromapNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12881, 11), 361}, // 205 DotProduct in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12775, 22), 359}, // 206 DotProductInput4x8Bit in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12797, 25), 359}, // 207 DotProductInput4x8BitKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12822, 28), 360}, // 208 DotProductInput4x8BitPacked in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12850, 31), 360}, // 209 DotProductInput4x8BitPackedKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12734, 19), 358}, // 210 DotProductInputAll in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12753, 22), 358}, // 211 DotProductInputAllKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12892, 14), 361}, // 212 DotProductKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5677, 15), 210}, // 213 DrawParameters in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12036, 16), 331}, // 214 ExpectAssumeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12239, 20), 338}, // 215 FPFastMathModeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13287, 28), 382}, // 216 FPGAArgumentInterfacesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12579, 24), 351}, // 217 FPGABufferLocationINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12452, 27), 346}, // 218 FPGAClusterAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13172, 29), 377}, // 219 FPGAClusterAttributesV2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12493, 20), 348}, // 220 FPGADSPControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12539, 40), 350}, // 221 FPGAInvocationPipeliningAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12402, 26), 344}, // 222 FPGAKernelAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13201, 28), 378}, // 223 FPGAKernelAttributesv2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13263, 24), 381}, // 224 FPGALatencyControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12358, 22), 342}, // 225 FPGALoopControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12428, 24), 345}, // 226 FPGAMemoryAccessesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12213, 26), 337}, // 227 FPGAMemoryAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12721, 13), 357}, // 228 FPGARegINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13247, 16), 380}, // 229 FPMaxErrorINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7817, 8), 142}, // 230 Float16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7803, 14), 141}, // 231 Float16Buffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9556, 16), 243}, // 232 Float16ImageAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7825, 8), 143}, // 233 Float64 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12971, 15), 367}, // 234 FloatControls2 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11832, 23), 321}, // 235 FloatingPointModeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6518, 23), 267}, // 236 FragmentBarycentricKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9905, 22), 267}, // 237 FragmentBarycentricNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6607, 19), 269}, // 238 FragmentDensityEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6328, 24), 263}, // 239 FragmentFullyCoveredEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9594, 16), 245}, // 240 FragmentMaskAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11226, 32), 295}, // 241 FragmentShaderPixelInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11155, 33), 292}, // 242 FragmentShaderSampleInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11188, 38), 293}, // 243 FragmentShaderShadingRateInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5739, 23), 208}, // 244 FragmentShadingRateKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12187, 26), 336}, // 245 FunctionFloatControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11878, 22), 323}, // 246 FunctionPointersINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8224, 15), 169}, // 247 GenericPointer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4725, 9), 135}, // 248 Geometry in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7974, 18), 156}, // 249 GeometryPointSize in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9833, 28), 258}, // 250 GeometryShaderPassthroughNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8437, 16), 185}, // 251 GeometryStreams in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13345, 35), 384}, // 252 GlobalVariableFPGADecorationsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13315, 30), 383}, // 253 GlobalVariableHostAccessINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5257, 16), 192}, // 254 GroupNonUniform in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8576, 26), 194}, // 255 GroupNonUniformArithmetic in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5512, 22), 195}, // 256 GroupNonUniformBallot in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8656, 25), 198}, // 257 GroupNonUniformClustered in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10002, 29), 270}, // 258 GroupNonUniformPartitionedNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8681, 20), 199}, // 259 GroupNonUniformQuad in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12946, 25), 366}, // 260 GroupNonUniformRotateKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8602, 23), 196}, // 261 GroupNonUniformShuffle in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8625, 31), 197}, // 262 GroupNonUniformShuffleRelative in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8556, 20), 193}, // 263 GroupNonUniformVote in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13557, 26), 391}, // 264 GroupUniformArithmeticKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7896, 7), 150}, // 265 Groups in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12689, 13), 355}, // 266 IOPipesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8293, 8), 175}, // 267 Image1D in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7852, 11), 146}, // 268 ImageBasic in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8315, 12), 178}, // 269 ImageBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8170, 15), 165}, // 270 ImageCubeArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9888, 17), 265}, // 271 ImageFootprintNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9572, 22), 244}, // 272 ImageGatherBiasLodAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7992, 20), 157}, // 273 ImageGatherExtended in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8327, 13), 179}, // 274 ImageMSArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7878, 12), 148}, // 275 ImageMipmap in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8368, 11), 181}, // 276 ImageQuery in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7863, 15), 147}, // 277 ImageReadWrite in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9610, 21), 247}, // 278 ImageReadWriteLodAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8202, 10), 167}, // 279 ImageRect in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11900, 24), 324}, // 280 IndirectReferencesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8244, 16), 171}, // 281 InputAttachment in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10117, 36), 273}, // 282 InputAttachmentArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10153, 39), 273}, // 283 InputAttachmentArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10658, 39), 280}, // 284 InputAttachmentArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10697, 42), 280}, // 285 InputAttachmentArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7946, 6), 154}, // 286 Int16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9689, 27), 253}, // 287 Int4CooperativeMatrixINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9675, 14), 252}, // 288 Int4TypeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7833, 6), 144}, // 289 Int64 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7839, 13), 145}, // 290 Int64Atomics in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9631, 14), 248}, // 291 Int64ImageEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8239, 5), 170}, // 292 Int8 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11855, 23), 322}, // 293 IntegerFunctions2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8397, 22), 183}, // 294 InterpolationFunction in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4492, 7), 139}, // 295 Kernel in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12380, 22), 343}, // 296 KernelAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7786, 8), 138}, // 297 Linkage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7917, 15), 152}, // 298 LiteralSampler in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13026, 20), 370}, // 299 LongCompositesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12479, 14), 347}, // 300 LoopFuseINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13610, 25), 393}, // 301 MaskedGatherScatterINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7779, 7), 133}, // 302 Matrix in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12513, 26), 349}, // 303 MemoryAccessAliasingINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4788, 15), 266}, // 304 MeshShadingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4774, 14), 264}, // 305 MeshShadingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8276, 7), 173}, // 306 MinLod in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5796, 10), 220}, // 307 MultiView in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4876, 14), 188}, // 308 MultiViewport in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8531, 13), 190}, // 309 NamedBarrier in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13046, 11), 371}, // 310 OptNoneEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13057, 13), 371}, // 311 OptNoneINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6270, 20), 262}, // 312 PerViewAttributesNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4610, 31), 288}, // 313 PhysicalStorageBufferAddresses in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11013, 34), 288}, // 314 PhysicalStorageBufferAddressesEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8544, 12), 191}, // 315 PipeStorage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7890, 6), 149}, // 316 Pipes in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9660, 15), 251}, // 317 QuadControlKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11474, 18), 305}, // 318 RawAccessChainsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7764, 15), 362}, // 319 RayCullMaskKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9401, 12), 234}, // 320 RayQueryKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11407, 25), 301}, // 321 RayQueryPositionFetchKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9378, 23), 233}, // 322 RayQueryProvisionalKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7711, 41), 314}, // 323 RayTracingClusterAccelerationStructureNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7283, 33), 304}, // 324 RayTracingDisplacementMicromapNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4760, 14), 237}, // 325 RayTracingKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7465, 39), 307}, // 326 RayTracingLinearSweptSpheresGeometryNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7169, 23), 285}, // 327 RayTracingMotionBlurNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4747, 13), 284}, // 328 RayTracingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11334, 29), 298}, // 329 RayTracingOpacityMicromapEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7222, 27), 283}, // 330 RayTracingPositionFetchKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11110, 25), 290}, // 331 RayTracingProvisionalKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7426, 28), 306}, // 332 RayTracingSpheresGeometryNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9432, 32), 236}, // 333 RayTraversalPrimitiveCullingKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13654, 20), 395}, // 334 RegisterLimitsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12906, 24), 364}, // 335 ReplicatedCompositesEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11811, 21), 320}, // 336 RoundToInfinityINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9346, 16), 231}, // 337 RoundingModeRTE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9362, 16), 232}, // 338 RoundingModeRTZ in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12660, 29), 354}, // 339 RuntimeAlignedAttributeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10068, 23), 272}, // 340 RuntimeDescriptorArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10091, 26), 272}, // 341 RuntimeDescriptorArrayEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9804, 29), 257}, // 342 SampleMaskOverrideCoverageNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9181, 28), 224}, // 343 SampleMaskPostDepthCoverage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5006, 18), 166}, // 344 SampleRateShading in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8283, 10), 174}, // 345 Sampled1D in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8301, 14), 177}, // 346 SampledBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8185, 17), 176}, // 347 SampledCubeArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8070, 33), 160}, // 348 SampledImageArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10431, 36), 277}, // 349 SampledImageArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10467, 39), 277}, // 350 SampledImageArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8212, 12), 168}, // 351 SampledRect in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4650, 7), 134}, // 352 Shader in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9645, 15), 249}, // 353 ShaderClockKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6119, 18), 250}, // 354 ShaderEnqueueAMDX in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11363, 26), 299}, // 355 ShaderInvocationReorderNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4822, 12), 200}, // 356 ShaderLayer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10031, 17), 271}, // 357 ShaderNonUniform in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10048, 20), 271}, // 358 ShaderNonUniformEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7537, 19), 294}, // 359 ShaderSMBuiltinsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6209, 19), 261}, // 360 ShaderStereoViewNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4890, 20), 201}, // 361 ShaderViewportIndex in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4834, 28), 259}, // 362 ShaderViewportIndexLayerEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9861, 27), 259}, // 363 ShaderViewportIndexLayerNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6168, 21), 260}, // 364 ShaderViewportMaskNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9988, 14), 269}, // 365 ShadingRateNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9321, 25), 230}, // 366 SignedZeroInfNanPreserve in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8260, 16), 172}, // 367 SparseResidency in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13135, 18), 375}, // 368 SplitBarrierINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6073, 17), 246}, // 369 StencilExportEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8969, 25), 215}, // 370 StorageBuffer16BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9209, 24), 225}, // 371 StorageBuffer8BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8103, 34), 161}, // 372 StorageBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10506, 37), 278}, // 373 StorageBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10543, 40), 278}, // 374 StorageBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8137, 33), 162}, // 375 StorageImageArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10583, 36), 279}, // 376 StorageImageArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10619, 39), 279}, // 377 StorageImageArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8340, 28), 180}, // 378 StorageImageExtendedFormats in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8012, 24), 158}, // 379 StorageImageMultisample in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8453, 30), 186}, // 380 StorageImageReadWithoutFormat in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8483, 31), 187}, // 381 StorageImageWriteWithoutFormat in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9096, 21), 218}, // 382 StorageInputOutput16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9074, 22), 217}, // 383 StoragePushConstant16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9267, 21), 227}, // 384 StoragePushConstant8 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10273, 39), 275}, // 385 StorageTexelBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10312, 42), 275}, // 386 StorageTexelBufferArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10826, 42), 282}, // 387 StorageTexelBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10868, 45), 282}, // 388 StorageTexelBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9057, 17), 216}, // 389 StorageUniform16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8994, 28), 215}, // 390 StorageUniformBufferBlock16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13408, 23), 386}, // 391 Subgroup2DBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13431, 30), 387}, // 392 Subgroup2DBlockTransformINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13461, 30), 388}, // 393 Subgroup2DBlockTransposeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12123, 39), 334}, // 394 SubgroupAvcMotionEstimationChromaINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12052, 33), 332}, // 395 SubgroupAvcMotionEstimationINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12085, 38), 333}, // 396 SubgroupAvcMotionEstimationIntraINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5273, 18), 209}, // 397 SubgroupBallotKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11727, 27), 317}, // 398 SubgroupBufferBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13380, 28), 385}, // 399 SubgroupBufferPrefetchINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8514, 17), 189}, // 400 SubgroupDispatch in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11754, 26), 318}, // 401 SubgroupImageBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11780, 31), 319}, // 402 SubgroupImageMediaBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13491, 38), 389}, // 403 SubgroupMatrixMultiplyAccumulateINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11706, 21), 316}, // 404 SubgroupShuffleINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8953, 16), 214}, // 405 SubgroupVoteKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13229, 18), 379}, // 406 TaskSequenceINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11687, 19), 315}, // 407 TensorAddressingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13583, 27), 392}, // 408 TensorFloat32RoundingINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13529, 28), 390}, // 409 TernaryBitwiseFunctionINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4734, 13), 136}, // 410 Tessellation in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7952, 22), 155}, // 411 TessellationPointSize in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9533, 23), 242}, // 412 TextureBlockMatch2QCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9511, 22), 240}, // 413 TextureBlockMatchQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9490, 21), 239}, // 414 TextureBoxFilterQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9464, 26), 238}, // 415 TextureSampleWeightedQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8719, 28), 204}, // 416 TileImageColorReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8747, 28), 205}, // 417 TileImageDepthReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8775, 30), 206}, // 418 TileImageStencilReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5836, 16), 241}, // 419 TileShadingQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8419, 18), 184}, // 420 TransformFeedback in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12637, 23), 353}, // 421 USMStorageClassesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9022, 35), 216}, // 422 UniformAndStorageBuffer16BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9233, 34), 226}, // 423 UniformAndStorageBuffer8BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8036, 34), 159}, // 424 UniformBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10354, 37), 276}, // 425 UniformBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10391, 40), 276}, // 426 UniformBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8701, 18), 202}, // 427 UniformDecoration in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10192, 39), 274}, // 428 UniformTexelBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10231, 42), 274}, // 429 UniformTexelBufferArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10739, 42), 281}, // 430 UniformTexelBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10781, 45), 281}, // 431 UniformTexelBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12328, 30), 341}, // 432 UnstructuredLoopControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9413, 19), 235}, // 433 UntypedPointersKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12162, 25), 335}, // 434 VariableLengthArrayINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9147, 17), 222}, // 435 VariablePointers in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9117, 30), 221}, // 436 VariablePointersStorageBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7794, 9), 140}, // 437 Vector16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12021, 15), 330}, // 438 VectorAnyINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12002, 19), 329}, // 439 VectorComputeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10913, 18), 286}, // 440 VulkanMemoryModel in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10952, 29), 287}, // 441 VulkanMemoryModelDeviceScope in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10981, 32), 287}, // 442 VulkanMemoryModelDeviceScopeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10931, 21), 286}, // 443 VulkanMemoryModelKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8909, 44), 213}, // 444 WorkgroupMemoryExplicitLayout16BitAccessKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8866, 43), 212}, // 445 WorkgroupMemoryExplicitLayout8BitAccessKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8833, 33), 211}, // 446 WorkgroupMemoryExplicitLayoutKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13686, 8), 397}, // 447 Address in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13694, 8), 398}, // 448 Boolean in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13702, 6), 399}, // 449 Float in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13708, 7), 400}, // 450 Signed in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13715, 11), 401}, // 451 SignedChar in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13726, 9), 402}, // 452 Unsigned in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13735, 13), 403}, // 453 UnsignedChar in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13674, 12), 396}, // 454 Unspecified in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13748, 6), 404}, // 455 Class in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(13754, 10), 405}, // 456 Structure in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(13764, 6), 406}, // 457 Union in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(13785, 20), 408}, // 458 ImportedDeclaration in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(13770, 15), 407}, // 459 ImportedModule in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(13894, 15), 416}, // 460 FlagArtificial in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(13909, 13), 417}, // 461 FlagExplicit in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(13882, 12), 415}, // 462 FlagFwdDecl in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(13972, 21), 421}, // 463 FlagIndirectVariable in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(13865, 17), 414}, // 464 FlagIsDefinition in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14049, 16), 425}, // 465 FlagIsEnumClass in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(13853, 12), 413}, // 466 FlagIsLocal in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14033, 16), 424}, // 467 FlagIsOptimized in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(13826, 14), 411}, // 468 FlagIsPrivate in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(13810, 16), 410}, // 469 FlagIsProtected in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(13840, 13), 412}, // 470 FlagIsPublic in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(13993, 20), 422}, // 471 FlagLValueReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(13937, 18), 419}, // 472 FlagObjectPointer in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(13922, 15), 418}, // 473 FlagPrototyped in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14013, 20), 423}, // 474 FlagRValueReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(13955, 17), 420}, // 475 FlagStaticMember in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14085, 24), 427}, // 476 FlagTypePassByReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14065, 20), 426}, // 477 FlagTypePassByValue in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(13805, 5), 409}, // 478 None in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14170, 9), 432}, // 479 BitPiece in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14202, 7), 436}, // 480 Constu in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14109, 6), 428}, // 481 Deref in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14209, 9), 437}, // 482 Fragment in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14120, 6), 430}, // 483 Minus in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14115, 5), 429}, // 484 Plus in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14159, 11), 431}, // 485 PlusUconst in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14191, 11), 435}, // 486 StackValue in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14179, 5), 433}, // 487 Swap in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14184, 7), 434}, // 488 Xderef in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14254, 11), 441}, // 489 AtomicType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14218, 10), 438}, // 490 ConstType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14241, 13), 440}, // 491 RestrictType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14228, 13), 439}, // 492 VolatileType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14265, 10), 442}, // 493 Float16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14275, 10), 443}, // 494 Float32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14285, 10), 444}, // 495 Float64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14453, 12), 455}, // 496 FloatE4M3NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14465, 12), 456}, // 497 FloatE5M2NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14308, 14), 446}, // 498 SignedInt16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14322, 14), 447}, // 499 SignedInt32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14336, 14), 448}, // 500 SignedInt64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14295, 13), 445}, // 501 SignedInt8NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14413, 19), 453}, // 502 SignedInt8PackedNV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14365, 16), 450}, // 503 UnsignedInt16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14381, 16), 451}, // 504 UnsignedInt32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14397, 16), 452}, // 505 UnsignedInt64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14350, 15), 449}, // 506 UnsignedInt8NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14432, 21), 454}, // 507 UnsignedInt8PackedNV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14529, 28), 460}, // 508 ColumnBlockedInterleavedARM in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(14489, 15), 458}, // 509 ColumnMajorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(14504, 25), 459}, // 510 RowBlockedInterleavedARM in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(14477, 12), 457}, // 511 RowMajorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(14565, 27), 462}, // 512 MatrixASignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(14592, 27), 463}, // 513 MatrixBSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(14619, 27), 464}, // 514 MatrixCSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(14646, 32), 465}, // 515 MatrixResultSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(14557, 8), 461}, // 516 NoneKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(14678, 26), 466}, // 517 SaturatingAccumulationKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(14715, 4), 469}, // 518 2x2 in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(14708, 7), 468}, // 519 Column in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(14704, 4), 467}, // 520 Row in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(14719, 11), 470}, // 521 MatrixAKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(14741, 21), 472}, // 522 MatrixAccumulatorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(14730, 11), 471}, // 523 MatrixBKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(14773, 14), 474}, // 524 ColumnMajorNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(14787, 21), 475}, // 525 InferencingOptimalNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(14762, 11), 473}, // 526 RowMajorNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(14808, 18), 476}, // 527 TrainingOptimalNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(13686, 8), 478}, // 528 Address in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13694, 8), 479}, // 529 Boolean in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13702, 6), 480}, // 530 Float in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13708, 7), 481}, // 531 Signed in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13715, 11), 482}, // 532 SignedChar in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13726, 9), 483}, // 533 Unsigned in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13735, 13), 484}, // 534 UnsignedChar in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13674, 12), 477}, // 535 Unspecified in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13748, 6), 485}, // 536 Class in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(13754, 10), 486}, // 537 Structure in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(13764, 6), 487}, // 538 Union in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(13894, 15), 495}, // 539 FlagArtificial in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(13909, 13), 496}, // 540 FlagExplicit in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(13882, 12), 494}, // 541 FlagFwdDecl in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(13972, 21), 500}, // 542 FlagIndirectVariable in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(13865, 17), 493}, // 543 FlagIsDefinition in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(13853, 12), 492}, // 544 FlagIsLocal in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14033, 16), 503}, // 545 FlagIsOptimized in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(13826, 14), 490}, // 546 FlagIsPrivate in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(13810, 16), 489}, // 547 FlagIsProtected in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(13840, 13), 491}, // 548 FlagIsPublic in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(13993, 20), 501}, // 549 FlagLValueReference in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(13937, 18), 498}, // 550 FlagObjectPointer in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(13922, 15), 497}, // 551 FlagPrototyped in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14013, 20), 502}, // 552 FlagRValueReference in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(13955, 17), 499}, // 553 FlagStaticMember in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(13805, 5), 488}, // 554 None in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14170, 9), 508}, // 555 BitPiece in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14202, 7), 512}, // 556 Constu in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14109, 6), 504}, // 557 Deref in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14120, 6), 506}, // 558 Minus in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14115, 5), 505}, // 559 Plus in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14159, 11), 507}, // 560 PlusUconst in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14191, 11), 511}, // 561 StackValue in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14179, 5), 509}, // 562 Swap in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14184, 7), 510}, // 563 Xderef in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14218, 10), 513}, // 564 ConstType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(14241, 13), 515}, // 565 RestrictType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(14228, 13), 514}, // 566 VolatileType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(17006, 16), 629}, // 567 AliasScopeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15035, 8), 535}, // 568 Aliased in SPV_OPERAND_TYPE_DECORATION
  {IR(16109, 15), 587}, // 569 AliasedPointer in SPV_OPERAND_TYPE_DECORATION
  {IR(16124, 18), 587}, // 570 AliasedPointerEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(15513, 10), 559}, // 571 Alignment in SPV_OPERAND_TYPE_DECORATION
  {IR(15557, 12), 561}, // 572 AlignmentId in SPV_OPERAND_TYPE_DECORATION
  {IR(14886, 12), 522}, // 573 ArrayStride in SPV_OPERAND_TYPE_DECORATION
  {IR(16787, 14), 617}, // 574 BankBitsINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16626, 15), 610}, // 575 BankwidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15190, 8), 548}, // 576 Binding in SPV_OPERAND_TYPE_DECORATION
  {IR(16190, 16), 590}, // 577 BindlessImageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16172, 18), 589}, // 578 BindlessSamplerNV in SPV_OPERAND_TYPE_DECORATION
  {IR(14850, 6), 518}, // 579 Block in SPV_OPERAND_TYPE_DECORATION
  {IR(15653, 22), 567}, // 580 BlockMatchSamplerQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(15631, 22), 566}, // 581 BlockMatchTextureQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(16221, 13), 592}, // 582 BoundImageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16206, 15), 591}, // 583 BoundSamplerNV in SPV_OPERAND_TYPE_DECORATION
  {IR(14856, 12), 519}, // 584 BufferBlock in SPV_OPERAND_TYPE_DECORATION
  {IR(17099, 20), 634}, // 585 BufferLocationINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(14967, 8), 527}, // 586 BuiltIn in SPV_OPERAND_TYPE_DECORATION
  {IR(16869, 19), 622}, // 587 BurstCoalesceINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(14933, 8), 526}, // 588 CPacked in SPV_OPERAND_TYPE_DECORATION
  {IR(17892, 22), 656}, // 589 CacheControlLoadINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17951, 23), 657}, // 590 CacheControlStoreINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16888, 15), 623}, // 591 CacheSizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15000, 9), 531}, // 592 Centroid in SPV_OPERAND_TYPE_DECORATION
  {IR(16274, 13), 595}, // 593 ClobberINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15061, 9), 538}, // 594 Coherent in SPV_OPERAND_TYPE_DECORATION
  {IR(14877, 9), 521}, // 595 ColMajor in SPV_OPERAND_TYPE_DECORATION
  {IR(15174, 10), 546}, // 596 Component in SPV_OPERAND_TYPE_DECORATION
  {IR(17408, 27), 644}, // 597 ConduitKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15052, 9), 537}, // 598 Constant in SPV_OPERAND_TYPE_DECORATION
  {IR(16420, 14), 602}, // 599 CounterBuffer in SPV_OPERAND_TYPE_DECORATION
  {IR(15198, 14), 549}, // 600 DescriptorSet in SPV_OPERAND_TYPE_DECORATION
  {IR(16903, 28), 624}, // 601 DontStaticallyCoalesceINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16679, 16), 613}, // 602 DoublepumpINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15675, 18), 568}, // 603 ExplicitInterpAMD in SPV_OPERAND_TYPE_DECORATION
  {IR(15383, 15), 555}, // 604 FPFastMathMode in SPV_OPERAND_TYPE_DECORATION
  {IR(17327, 26), 641}, // 605 FPMaxErrorDecorationINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15333, 15), 554}, // 606 FPRoundingMode in SPV_OPERAND_TYPE_DECORATION
  {IR(14989, 5), 529}, // 607 Flat in SPV_OPERAND_TYPE_DECORATION
  {IR(16801, 20), 618}, // 608 ForcePow2DepthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15285, 14), 553}, // 609 FuncParamAttr in SPV_OPERAND_TYPE_DECORATION
  {IR(16331, 21), 598}, // 610 FuncParamIOKindINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16562, 24), 606}, // 611 FunctionDenormModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17172, 31), 636}, // 612 FunctionFloatingPointModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16505, 26), 605}, // 613 FunctionRoundingModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16962, 25), 627}, // 614 FuseLoopsInFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(14922, 11), 525}, // 615 GLSLPacked in SPV_OPERAND_TYPE_DECORATION
  {IR(14911, 11), 524}, // 616 GLSLShared in SPV_OPERAND_TYPE_DECORATION
  {IR(16394, 26), 601}, // 617 GlobalVariableOffsetINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16142, 30), 588}, // 618 HitObjectShaderRecordBufferNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16434, 24), 602}, // 619 HlslCounterBufferGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(16471, 19), 603}, // 620 HlslSemanticGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(17751, 16), 653}, // 621 HostAccessINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17119, 19), 635}, // 622 IOPipeStorageINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17828, 28), 655}, // 623 ImplementInRegisterMapINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15184, 6), 547}, // 624 Index in SPV_OPERAND_TYPE_DECORATION
  {IR(17814, 14), 654}, // 625 InitModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17035, 24), 631}, // 626 InitiationIntervalINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15492, 21), 558}, // 627 InputAttachmentIndex in SPV_OPERAND_TYPE_DECORATION
  {IR(15016, 10), 533}, // 628 Invariant in SPV_OPERAND_TYPE_DECORATION
  {IR(17378, 30), 643}, // 629 LatencyControlConstraintINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17353, 25), 642}, // 630 LatencyControlLabelINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15460, 18), 556}, // 631 LinkageAttributes in SPV_OPERAND_TYPE_DECORATION
  {IR(15165, 9), 545}, // 632 Location in SPV_OPERAND_TYPE_DECORATION
  {IR(17466, 33), 646}, // 633 MMHostInterfaceAddressWidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17499, 30), 647}, // 634 MMHostInterfaceDataWidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17529, 28), 648}, // 635 MMHostInterfaceLatencyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17625, 29), 650}, // 636 MMHostInterfaceMaxBurstINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17591, 34), 649}, // 637 MMHostInterfaceReadWriteModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17654, 32), 651}, // 638 MMHostInterfaceWaitRequestINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16987, 19), 628}, // 639 MathOpDSPModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(14898, 13), 523}, // 640 MatrixStride in SPV_OPERAND_TYPE_DECORATION
  {IR(15523, 14), 560}, // 641 MaxByteOffset in SPV_OPERAND_TYPE_DECORATION
  {IR(15569, 16), 562}, // 642 MaxByteOffsetId in SPV_OPERAND_TYPE_DECORATION
  {IR(17059, 20), 632}, // 643 MaxConcurrencyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16641, 22), 611}, // 644 MaxPrivateCopiesINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16695, 19), 614}, // 645 MaxReplicatesINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17263, 18), 639}, // 646 MediaBlockIOINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16600, 12), 608}, // 647 MemoryINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16734, 11), 616}, // 648 MergeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17022, 13), 630}, // 649 NoAliasINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15478, 14), 557}, // 650 NoContraction in SPV_OPERAND_TYPE_DECORATION
  {IR(14975, 14), 528}, // 651 NoPerspective in SPV_OPERAND_TYPE_DECORATION
  {IR(15585, 13), 563}, // 652 NoSignedWrap in SPV_OPERAND_TYPE_DECORATION
  {IR(15598, 15), 564}, // 653 NoUnsignedWrap in SPV_OPERAND_TYPE_DECORATION
  {IR(15725, 20), 570}, // 654 NodeMaxPayloadsAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(15693, 32), 569}, // 655 NodeSharesPayloadLimitsWithAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(15082, 12), 540}, // 656 NonReadable in SPV_OPERAND_TYPE_DECORATION
  {IR(16049, 11), 585}, // 657 NonUniform in SPV_OPERAND_TYPE_DECORATION
  {IR(16060, 14), 585}, // 658 NonUniformEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(15070, 12), 539}, // 659 NonWritable in SPV_OPERAND_TYPE_DECORATION
  {IR(16612, 14), 609}, // 660 NumbanksINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15212, 7), 550}, // 661 Offset in SPV_OPERAND_TYPE_DECORATION
  {IR(15893, 19), 577}, // 662 OverrideCoverageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(15912, 14), 578}, // 663 PassthroughNV in SPV_OPERAND_TYPE_DECORATION
  {IR(14994, 6), 530}, // 664 Patch in SPV_OPERAND_TYPE_DECORATION
  {IR(15865, 28), 576}, // 665 PayloadDispatchIndirectAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(15840, 25), 575}, // 666 PayloadNodeArraySizeAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(15788, 25), 573}, // 667 PayloadNodeBaseIndexAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(15768, 20), 572}, // 668 PayloadNodeNameAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(15813, 27), 574}, // 669 PayloadNodeSparseArrayAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(15973, 16), 581}, // 670 PerPrimitiveEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(15989, 15), 581}, // 671 PerPrimitiveNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16014, 10), 583}, // 672 PerTaskNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16024, 13), 584}, // 673 PerVertexKHR in SPV_OPERAND_TYPE_DECORATION
  {IR(16037, 12), 584}, // 674 PerVertexNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16004, 10), 582}, // 675 PerViewNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17079, 20), 633}, // 676 PipelineEnableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16931, 14), 625}, // 677 PrefetchINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16248, 26), 594}, // 678 ReferencedIndirectlyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16586, 14), 607}, // 679 RegisterINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17435, 31), 645}, // 680 RegisterMapKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(14826, 17), 516}, // 681 RelaxedPrecision in SPV_OPERAND_TYPE_DECORATION
  {IR(15026, 9), 534}, // 682 Restrict in SPV_OPERAND_TYPE_DECORATION
  {IR(16074, 16), 586}, // 683 RestrictPointer in SPV_OPERAND_TYPE_DECORATION
  {IR(16090, 19), 586}, // 684 RestrictPointerEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(14868, 9), 520}, // 685 RowMajor in SPV_OPERAND_TYPE_DECORATION
  {IR(16234, 14), 593}, // 686 SIMTCallINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15009, 7), 532}, // 687 Sample in SPV_OPERAND_TYPE_DECORATION
  {IR(15138, 20), 543}, // 688 SaturatedConversion in SPV_OPERAND_TYPE_DECORATION
  {IR(15945, 28), 580}, // 689 SecondaryViewportRelativeNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16287, 17), 596}, // 690 SideEffectsINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16714, 20), 615}, // 691 SimpleDualPortINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17203, 25), 637}, // 692 SingleElementVectorINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16663, 16), 612}, // 693 SinglepumpINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(14843, 7), 517}, // 694 SpecId in SPV_OPERAND_TYPE_DECORATION
  {IR(17686, 26), 652}, // 695 StableKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16379, 15), 600}, // 696 StackCallINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16945, 17), 626}, // 697 StallEnableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17281, 15), 640}, // 698 StallFreeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15158, 7), 544}, // 699 Stream in SPV_OPERAND_TYPE_DECORATION
  {IR(16821, 16), 619}, // 700 StridesizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15745, 23), 571}, // 701 TrackFinishWritingAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(16851, 18), 621}, // 702 TrueDualPortINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15094, 8), 541}, // 703 Uniform in SPV_OPERAND_TYPE_DECORATION
  {IR(15128, 10), 542}, // 704 UniformId in SPV_OPERAND_TYPE_DECORATION
  {IR(16458, 13), 603}, // 705 UserSemantic in SPV_OPERAND_TYPE_DECORATION
  {IR(16490, 15), 604}, // 706 UserTypeGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(17228, 35), 638}, // 707 VectorComputeCallableFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16352, 27), 599}, // 708 VectorComputeFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16304, 27), 597}, // 709 VectorComputeVariableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15926, 19), 579}, // 710 ViewportRelativeNV in SPV_OPERAND_TYPE_DECORATION
  {IR(15043, 9), 536}, // 711 Volatile in SPV_OPERAND_TYPE_DECORATION
  {IR(15613, 18), 565}, // 712 WeightTextureQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(16837, 14), 620}, // 713 WordsizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15219, 10), 551}, // 714 XfbBuffer in SPV_OPERAND_TYPE_DECORATION
  {IR(15229, 10), 552}, // 715 XfbStride in SPV_OPERAND_TYPE_DECORATION
  {IR(17974, 3), 658}, // 716 1D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(17977, 3), 659}, // 717 2D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(17980, 3), 660}, // 718 3D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(17993, 7), 663}, // 719 Buffer in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(17983, 5), 661}, // 720 Cube in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(17988, 5), 662}, // 721 Rect in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18000, 12), 664}, // 722 SubpassData in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18012, 17), 665}, // 723 TileImageDataEXT in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18824, 15), 718}, // 724 CoalescingAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18455, 15), 696}, // 725 ContractionOff in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(9303, 18), 710}, // 726 DenormFlushToZero in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(9288, 15), 709}, // 727 DenormPreserve in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18225, 13), 679}, // 728 DepthGreater in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18238, 10), 680}, // 729 DepthLess in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18210, 15), 678}, // 730 DepthReplacing in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18248, 15), 681}, // 731 DepthUnchanged in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19245, 25), 736}, // 732 DerivativeGroupLinearKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19270, 24), 736}, // 733 DerivativeGroupLinearNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19198, 24), 735}, // 734 DerivativeGroupQuadsKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19222, 23), 735}, // 735 DerivativeGroupQuadsNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18772, 29), 716}, // 736 EarlyAndLateFragmentTestsAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18177, 19), 675}, // 737 EarlyFragmentTests in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19755, 18), 755}, // 738 FPFastMathDefault in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18482, 10), 698}, // 739 Finalizer in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19570, 26), 747}, // 740 FloatingPointModeALTINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19596, 27), 748}, // 741 FloatingPointModeIEEEINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18470, 12), 697}, // 742 Initializer in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18299, 11), 685}, // 743 InputLines in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18310, 20), 686}, // 744 InputLinesAdjacency in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18287, 12), 684}, // 745 InputPoints in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18340, 24), 688}, // 746 InputTrianglesAdjacency in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18029, 12), 666}, // 747 Invocations in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18839, 15), 719}, // 748 IsApiEntryAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18370, 9), 690}, // 749 Isolines in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18263, 10), 682}, // 750 LocalSize in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18273, 14), 683}, // 751 LocalSizeHint in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18550, 16), 703}, // 752 LocalSizeHintId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18538, 12), 702}, // 753 LocalSizeId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18854, 21), 720}, // 754 MaxNodeRecursionAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18899, 21), 723}, // 755 MaxNumWorkgroupsAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19645, 16), 750}, // 756 MaxWorkDimINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19623, 22), 749}, // 757 MaxWorkgroupSizeINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19731, 24), 754}, // 758 MaximallyReconvergesKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19846, 22), 759}, // 759 MaximumRegistersINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19868, 24), 760}, // 760 MaximumRegistersIdINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19823, 23), 758}, // 761 NamedBarrierCountINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19943, 27), 761}, // 762 NamedMaximumRegistersINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19661, 20), 751}, // 763 NoGlobalOffsetINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18566, 34), 704}, // 764 NonCoherentColorAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18600, 34), 705}, // 765 NonCoherentDepthAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18634, 36), 706}, // 766 NonCoherentStencilAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18718, 34), 714}, // 767 NonCoherentTileAttachmentReadQCOM in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19681, 22), 752}, // 768 NumSIMDWorkitemsINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18161, 16), 674}, // 769 OriginLowerLeft in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18145, 16), 673}, // 770 OriginUpperLeft in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18407, 16), 693}, // 771 OutputLineStrip in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19130, 15), 733}, // 772 OutputLinesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19145, 14), 733}, // 773 OutputLinesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18394, 13), 692}, // 774 OutputPoints in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19159, 20), 734}, // 775 OutputPrimitivesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19179, 19), 734}, // 776 OutputPrimitivesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18423, 20), 694}, // 777 OutputTriangleStrip in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19294, 19), 737}, // 778 OutputTrianglesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19313, 18), 737}, // 779 OutputTrianglesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18379, 15), 691}, // 780 OutputVertices in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18126, 19), 672}, // 781 PixelCenterInteger in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19331, 25), 738}, // 782 PixelInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19356, 27), 739}, // 783 PixelInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18196, 10), 676}, // 784 PointMode in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18700, 18), 708}, // 785 PostDepthCoverage in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19071, 19), 730}, // 786 QuadDerivativesKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18364, 6), 689}, // 787 Quads in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19797, 26), 757}, // 788 RegisterMapInterfaceINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19090, 20), 731}, // 789 RequireFullQuadsKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(9346, 16), 712}, // 790 RoundingModeRTE in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19549, 21), 746}, // 791 RoundingModeRTNINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19528, 21), 745}, // 792 RoundingModeRTPINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(9362, 16), 713}, // 793 RoundingModeRTZ in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19383, 26), 740}, // 794 SampleInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19409, 28), 741}, // 795 SampleInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19703, 28), 753}, // 796 SchedulerTargetFmaxMhzINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(6137, 16), 722}, // 797 ShaderIndexAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19437, 31), 742}, // 798 ShadingRateInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19468, 33), 743}, // 799 ShadingRateInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19501, 27), 744}, // 800 SharedLocalMemorySizeINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19110, 20), 732}, // 801 SharesInputWithAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(9321, 25), 711}, // 802 SignedZeroInfNanPreserve in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18041, 13), 667}, // 803 SpacingEqual in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18054, 22), 668}, // 804 SpacingFractionalEven in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18076, 21), 669}, // 805 SpacingFractionalOdd in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18875, 24), 721}, // 806 StaticNumWorkgroupsAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19024, 25), 728}, // 807 StencilRefGreaterBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18948, 26), 725}, // 808 StencilRefGreaterFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19049, 22), 729}, // 809 StencilRefLessBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18974, 23), 726}, // 810 StencilRefLessFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18801, 23), 717}, // 811 StencilRefReplacingEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18997, 27), 727}, // 812 StencilRefUnchangedBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18920, 28), 724}, // 813 StencilRefUnchangedFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19773, 24), 756}, // 814 StreamingInterfaceINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(5244, 13), 699}, // 815 SubgroupSize in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18670, 30), 707}, // 816 SubgroupUniformControlFlowKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18492, 22), 700}, // 817 SubgroupsPerWorkgroup in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18514, 24), 701}, // 818 SubgroupsPerWorkgroupId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18752, 20), 715}, // 819 TileShadingRateQCOM in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18330, 10), 687}, // 820 Triangles in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18443, 12), 695}, // 821 VecTypeHint in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18111, 15), 671}, // 822 VertexOrderCcw in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18097, 14), 670}, // 823 VertexOrderCw in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18206, 4), 677}, // 824 Xfb in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20108, 10), 773}, // 825 AnyHitKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20118, 9), 773}, // 826 AnyHitNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20169, 12), 776}, // 827 CallableKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20181, 11), 776}, // 828 CallableNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20127, 14), 774}, // 829 ClosestHitKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20141, 13), 774}, // 830 ClosestHitNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(14209, 9), 766}, // 831 Fragment in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20020, 10), 767}, // 832 GLCompute in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(4725, 9), 765}, // 833 Geometry in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20077, 16), 772}, // 834 IntersectionKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20093, 15), 772}, // 835 IntersectionNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(4492, 7), 768}, // 836 Kernel in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20200, 8), 778}, // 837 MeshEXT in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20037, 7), 770}, // 838 MeshNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20154, 8), 775}, // 839 MissKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20162, 7), 775}, // 840 MissNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20044, 17), 771}, // 841 RayGenerationKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20061, 16), 771}, // 842 RayGenerationNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20192, 8), 777}, // 843 TaskEXT in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20030, 7), 769}, // 844 TaskNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(19977, 20), 763}, // 845 TessellationControl in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(19997, 23), 764}, // 846 TessellationEvaluation in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(19970, 7), 762}, // 847 Vertex in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20217, 12), 780}, // 848 FlushToZero in SPV_OPERAND_TYPE_FPDENORM_MODE
  {IR(20208, 9), 779}, // 849 Preserve in SPV_OPERAND_TYPE_FPDENORM_MODE
  {IR(20229, 12), 781}, // 850 BFloat16KHR in SPV_OPERAND_TYPE_FPENCODING
  {IR(20246, 4), 783}, // 851 ALT in SPV_OPERAND_TYPE_FPOPERATION_MODE
  {IR(20241, 5), 782}, // 852 IEEE in SPV_OPERAND_TYPE_FPOPERATION_MODE
  {IR(20284, 14), 790}, // 853 AllowContract in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20298, 23), 790}, // 854 AllowContractFastINTEL in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20321, 13), 791}, // 855 AllowReassoc in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20334, 18), 791}, // 856 AllowReassocINTEL in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20268, 11), 788}, // 857 AllowRecip in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20352, 15), 792}, // 858 AllowTransform in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20279, 5), 789}, // 859 Fast in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20264, 4), 787}, // 860 NSZ in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(13805, 5), 784}, // 861 None in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20257, 7), 786}, // 862 NotInf in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20250, 7), 785}, // 863 NotNaN in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20367, 4), 793}, // 864 RTE in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(20379, 4), 796}, // 865 RTN in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(20375, 4), 795}, // 866 RTP in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(20371, 4), 794}, // 867 RTZ in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(20415, 18), 799}, // 868 Horizontal2Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(20433, 18), 800}, // 869 Horizontal4Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(20383, 16), 797}, // 870 Vertical2Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(20399, 16), 798}, // 871 Vertical4Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(20474, 6), 805}, // 872 Const in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(20458, 11), 803}, // 873 DontInline in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(20451, 7), 802}, // 874 Inline in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(13805, 5), 801}, // 875 None in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(13046, 11), 806}, // 876 OptNoneEXT in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(13057, 13), 806}, // 877 OptNoneINTEL in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(20469, 5), 804}, // 878 Pure in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(20490, 6), 809}, // 879 ByVal in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20501, 8), 811}, // 880 NoAlias in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20509, 10), 812}, // 881 NoCapture in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20527, 12), 814}, // 882 NoReadWrite in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20519, 8), 813}, // 883 NoWrite in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20539, 20), 815}, // 884 RuntimeAlignedINTEL in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20485, 5), 808}, // 885 Sext in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20496, 5), 810}, // 886 Sret in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20480, 5), 807}, // 887 Zext in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20594, 16), 819}, // 888 ClusteredReduce in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(20580, 14), 818}, // 889 ExclusiveScan in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(20566, 14), 817}, // 890 InclusiveScan in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(20657, 27), 822}, // 891 PartitionedExclusiveScanNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(20630, 27), 821}, // 892 PartitionedInclusiveScanNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(20610, 20), 820}, // 893 PartitionedReduceNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(20559, 7), 816}, // 894 Reduce in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(20684, 10), 823}, // 895 NoneINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(20694, 10), 824}, // 896 ReadINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(20715, 15), 826}, // 897 ReadWriteINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(20704, 11), 825}, // 898 WriteINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(20730, 5), 828}, // 899 Bias in SPV_OPERAND_TYPE_IMAGE
  {IR(20744, 12), 831}, // 900 ConstOffset in SPV_OPERAND_TYPE_IMAGE
  {IR(20756, 13), 833}, // 901 ConstOffsets in SPV_OPERAND_TYPE_IMAGE
  {IR(20739, 5), 830}, // 902 Grad in SPV_OPERAND_TYPE_IMAGE
  {IR(20735, 4), 829}, // 903 Lod in SPV_OPERAND_TYPE_IMAGE
  {IR(20769, 19), 836}, // 904 MakeTexelAvailable in SPV_OPERAND_TYPE_IMAGE
  {IR(20788, 22), 836}, // 905 MakeTexelAvailableKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(20810, 17), 837}, // 906 MakeTexelVisible in SPV_OPERAND_TYPE_IMAGE
  {IR(20827, 20), 837}, // 907 MakeTexelVisibleKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(8276, 7), 835}, // 908 MinLod in SPV_OPERAND_TYPE_IMAGE
  {IR(20847, 16), 838}, // 909 NonPrivateTexel in SPV_OPERAND_TYPE_IMAGE
  {IR(20863, 19), 838}, // 910 NonPrivateTexelKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(13805, 5), 827}, // 911 None in SPV_OPERAND_TYPE_IMAGE
  {IR(20935, 12), 842}, // 912 Nontemporal in SPV_OPERAND_TYPE_IMAGE
  {IR(15212, 7), 832}, // 913 Offset in SPV_OPERAND_TYPE_IMAGE
  {IR(20947, 8), 843}, // 914 Offsets in SPV_OPERAND_TYPE_IMAGE
  {IR(15009, 7), 834}, // 915 Sample in SPV_OPERAND_TYPE_IMAGE
  {IR(20913, 11), 840}, // 916 SignExtend in SPV_OPERAND_TYPE_IMAGE
  {IR(20882, 14), 839}, // 917 VolatileTexel in SPV_OPERAND_TYPE_IMAGE
  {IR(20896, 17), 839}, // 918 VolatileTexelKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(20924, 11), 841}, // 919 ZeroExtend in SPV_OPERAND_TYPE_IMAGE
  {IR(13702, 6), 858}, // 920 Float in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21116, 10), 857}, // 921 HalfFloat in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21051, 12), 852}, // 922 SignedInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21063, 12), 853}, // 923 SignedInt32 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21040, 11), 851}, // 924 SignedInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(20965, 11), 845}, // 925 SnormInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(20955, 10), 844}, // 926 SnormInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21025, 15), 850}, // 927 UnormInt101010 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21137, 17), 860}, // 928 UnormInt101010_2 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21154, 16), 861}, // 929 UnormInt10X6EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21287, 16), 868}, // 930 UnormInt12X4EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21303, 16), 869}, // 931 UnormInt14X2EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(20986, 11), 847}, // 932 UnormInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21126, 11), 859}, // 933 UnormInt24 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21210, 20), 864}, // 934 UnormInt2_101010EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(20976, 10), 846}, // 935 UnormInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21011, 14), 849}, // 936 UnormShort555 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(20997, 14), 848}, // 937 UnormShort565 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21230, 19), 865}, // 938 UnsignedInt10X6EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21249, 19), 866}, // 939 UnsignedInt12X4EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21268, 19), 867}, // 940 UnsignedInt14X2EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21088, 14), 855}, // 941 UnsignedInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21102, 14), 856}, // 942 UnsignedInt32 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21075, 13), 854}, // 943 UnsignedInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21170, 20), 862}, // 944 UnsignedIntRaw10EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21190, 20), 863}, // 945 UnsignedIntRaw12EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21321, 2), 871}, // 946 A in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21422, 5), 889}, // 947 ABGR in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21343, 5), 877}, // 948 ARGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21338, 5), 876}, // 949 BGRA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21380, 6), 883}, // 950 Depth in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21386, 13), 884}, // 951 DepthStencil in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21348, 10), 878}, // 952 Intensity in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21358, 10), 879}, // 953 Luminance in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21319, 2), 870}, // 954 R in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21326, 3), 873}, // 955 RA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21323, 3), 872}, // 956 RG in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21329, 4), 874}, // 957 RGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21333, 5), 875}, // 958 RGBA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21375, 5), 882}, // 959 RGBx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21371, 4), 881}, // 960 RGx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21368, 3), 880}, // 961 Rx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21416, 6), 888}, // 962 sBGRA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21399, 5), 885}, // 963 sRGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21410, 6), 887}, // 964 sRGBA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21404, 6), 886}, // 965 sRGBx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21427, 27), 890}, // 966 InitOnDeviceReprogramINTEL in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(21454, 23), 891}, // 967 InitOnDeviceResetINTEL in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(21477, 7), 892}, // 968 NoWait in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(21484, 11), 893}, // 969 WaitKernel in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(21495, 14), 894}, // 970 WaitWorkGroup in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(21509, 12), 896}, // 971 CmdExecTime in SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {IR(13805, 5), 895}, // 972 None in SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {IR(21521, 13), 898}, // 973 MayUsePrintf in SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {IR(13805, 5), 897}, // 974 None in SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {IR(21534, 7), 899}, // 975 Export in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(21541, 7), 900}, // 976 Import in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(21548, 12), 901}, // 977 LinkOnceODR in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(21574, 12), 903}, // 978 CachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(21626, 17), 906}, // 979 ConstCachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(21601, 25), 905}, // 980 InvalidateAfterReadINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(21586, 15), 904}, // 981 StreamingINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(21560, 14), 902}, // 982 UncachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(21766, 21), 919}, // 983 DependencyArrayINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21661, 19), 910}, // 984 DependencyInfinite in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21680, 17), 911}, // 985 DependencyLength in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21650, 11), 909}, // 986 DontUnroll in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(17035, 24), 917}, // 987 InitiationIntervalINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21725, 18), 914}, // 988 IterationMultiple in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21787, 18), 921}, // 989 LoopCoalesceINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21866, 15), 925}, // 990 LoopCountINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(17059, 20), 918}, // 991 MaxConcurrencyINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21805, 21), 922}, // 992 MaxInterleavingINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21711, 14), 913}, // 993 MaxIterations in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21881, 26), 926}, // 994 MaxReinvocationDelayINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21697, 14), 912}, // 995 MinIterations in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21852, 14), 924}, // 996 NoFusionINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(13805, 5), 907}, // 997 None in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21753, 13), 916}, // 998 PartialCount in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21743, 10), 915}, // 999 PeelCount in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(17079, 20), 920}, // 1000 PipelineEnableINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21826, 26), 923}, // 1001 SpeculatedIterationsINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21643, 7), 908}, // 1002 Unroll in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22190, 27), 940}, // 1003 MatrixAPackedBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22138, 26), 938}, // 1004 MatrixAPackedFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22058, 23), 934}, // 1005 MatrixAPackedInt4INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22012, 23), 932}, // 1006 MatrixAPackedInt8INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(21907, 29), 928}, // 1007 MatrixASignedComponentsINTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22104, 17), 936}, // 1008 MatrixATF32INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22217, 27), 941}, // 1009 MatrixBPackedBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22164, 26), 939}, // 1010 MatrixBPackedFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22081, 23), 935}, // 1011 MatrixBPackedInt4INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22035, 23), 933}, // 1012 MatrixBPackedInt8INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(21936, 29), 929}, // 1013 MatrixBSignedComponentsINTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22121, 17), 937}, // 1014 MatrixBTF32INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(21965, 21), 930}, // 1015 MatrixCBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(21986, 26), 931}, // 1016 MatrixResultBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(13805, 5), 927}, // 1017 None in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22377, 20), 949}, // 1018 AliasScopeINTELMask in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22244, 8), 944}, // 1019 Aligned in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22252, 21), 946}, // 1020 MakePointerAvailable in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22273, 24), 946}, // 1021 MakePointerAvailableKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22297, 19), 947}, // 1022 MakePointerVisible in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22316, 22), 947}, // 1023 MakePointerVisibleKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22397, 17), 950}, // 1024 NoAliasINTELMask in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22338, 18), 948}, // 1025 NonPrivatePointer in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22356, 21), 948}, // 1026 NonPrivatePointerKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(13805, 5), 942}, // 1027 None in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(20935, 12), 945}, // 1028 Nontemporal in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(15043, 9), 943}, // 1029 Volatile in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22421, 8), 952}, // 1030 GLSL450 in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(22429, 7), 953}, // 1031 OpenCL in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(22414, 7), 951}, // 1032 Simple in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(22436, 7), 954}, // 1033 Vulkan in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(22443, 10), 954}, // 1034 VulkanKHR in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(22461, 8), 956}, // 1035 Acquire in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22477, 15), 958}, // 1036 AcquireRelease in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22581, 20), 964}, // 1037 AtomicCounterMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22560, 21), 963}, // 1038 CrossWorkgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22601, 12), 965}, // 1039 ImageMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22642, 14), 967}, // 1040 MakeAvailable in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22656, 17), 967}, // 1041 MakeAvailableKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22673, 12), 968}, // 1042 MakeVisible in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22685, 15), 968}, // 1043 MakeVisibleKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(13805, 5), 955}, // 1044 None in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22613, 13), 966}, // 1045 OutputMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22626, 16), 966}, // 1046 OutputMemoryKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22453, 8), 955}, // 1047 Relaxed in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22469, 8), 957}, // 1048 Release in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22492, 23), 959}, // 1049 SequentiallyConsistent in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22529, 15), 961}, // 1050 SubgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22515, 14), 960}, // 1051 UniformMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(15043, 9), 969}, // 1052 Volatile in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22544, 16), 962}, // 1053 WorkgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22700, 10), 970}, // 1054 AutoINTEL in SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS
  {IR(22715, 4), 972}, // 1055 SAT in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(22728, 8), 974}, // 1056 SAT_SYM in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(22719, 9), 973}, // 1057 SAT_ZERO in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(22710, 5), 971}, // 1058 WRAP in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(22736, 25), 975}, // 1059 PackedVectorFormat4x8Bit in SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {IR(22761, 28), 975}, // 1060 PackedVectorFormat4x8BitKHR in SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {IR(22802, 4), 978}, // 1061 RND in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(22835, 9), 982}, // 1062 RND_CONV in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(22844, 13), 983}, // 1063 RND_CONV_ODD in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(22815, 8), 980}, // 1064 RND_INF in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(22823, 12), 981}, // 1065 RND_MIN_INF in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(22806, 9), 979}, // 1066 RND_ZERO in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(22789, 4), 976}, // 1067 TRN in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(22793, 9), 977}, // 1068 TRN_ZERO in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(13805, 5), 984}, // 1069 None in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(22857, 25), 985}, // 1070 RobustnessPerComponentNV in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(22882, 23), 986}, // 1071 RobustnessPerElementNV in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(22974, 27), 992}, // 1072 CullBackFacingTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23001, 28), 993}, // 1073 CullFrontFacingTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23043, 16), 995}, // 1074 CullNoOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23029, 14), 994}, // 1075 CullOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23113, 30), 998}, // 1076 ForceOpacityMicromap2StateEXT in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(22915, 12), 989}, // 1077 NoOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(14557, 8), 987}, // 1078 NoneKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(22905, 10), 988}, // 1079 OpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23100, 13), 997}, // 1080 SkipAABBsKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23076, 24), 996}, // 1081 SkipBuiltinPrimitivesNV in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(22950, 24), 991}, // 1082 SkipClosestHitShaderKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23059, 17), 996}, // 1083 SkipTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(22927, 23), 990}, // 1084 TerminateOnFirstHitKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23184, 37), 1000}, // 1085 RayQueryCandidateIntersectionAABBKHR in SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {IR(23143, 41), 999}, // 1086 RayQueryCandidateIntersectionTriangleKHR in SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {IR(23299, 42), 1003}, // 1087 RayQueryCommittedIntersectionGeneratedKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(23221, 37), 1001}, // 1088 RayQueryCommittedIntersectionNoneKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(23258, 41), 1002}, // 1089 RayQueryCommittedIntersectionTriangleKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(23341, 33), 1004}, // 1090 RayQueryCandidateIntersectionKHR in SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {IR(23374, 33), 1005}, // 1091 RayQueryCommittedIntersectionKHR in SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {IR(23419, 6), 1008}, // 1092 Clamp in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(23407, 12), 1007}, // 1093 ClampToEdge in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(13805, 5), 1006}, // 1094 None in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(23425, 7), 1009}, // 1095 Repeat in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(23432, 15), 1010}, // 1096 RepeatMirrored in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(23455, 7), 1012}, // 1097 Linear in SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {IR(23447, 8), 1011}, // 1098 Nearest in SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {IR(23520, 13), 1021}, // 1099 R11fG11fB10f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23562, 4), 1027}, // 1100 R16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23600, 9), 1032}, // 1101 R16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23533, 5), 1022}, // 1102 R16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23662, 5), 1041}, // 1103 R16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23733, 6), 1051}, // 1104 R16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23486, 5), 1016}, // 1105 R32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23640, 5), 1037}, // 1106 R32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23697, 6), 1046}, // 1107 R32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23750, 5), 1054}, // 1108 R64i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23744, 6), 1053}, // 1109 R64ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23566, 3), 1028}, // 1110 R8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23609, 8), 1033}, // 1111 R8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23667, 4), 1042}, // 1112 R8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23739, 5), 1052}, // 1113 R8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23553, 5), 1025}, // 1114 Rg16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23581, 10), 1030}, // 1115 Rg16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23514, 6), 1020}, // 1116 Rg16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23651, 6), 1039}, // 1117 Rg16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23720, 7), 1049}, // 1118 Rg16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23508, 6), 1019}, // 1119 Rg32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23645, 6), 1038}, // 1120 Rg32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23713, 7), 1048}, // 1121 Rg32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23558, 4), 1026}, // 1122 Rg8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23591, 9), 1031}, // 1123 Rg8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23657, 5), 1040}, // 1124 Rg8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23727, 6), 1050}, // 1125 Rg8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23545, 8), 1024}, // 1126 Rgb10A2 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23703, 10), 1047}, // 1127 Rgb10a2ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23538, 7), 1023}, // 1128 Rgba16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23569, 12), 1029}, // 1129 Rgba16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23478, 8), 1015}, // 1130 Rgba16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23625, 8), 1035}, // 1131 Rgba16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23680, 9), 1044}, // 1132 Rgba16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23470, 8), 1014}, // 1133 Rgba32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23617, 8), 1034}, // 1134 Rgba32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23671, 9), 1043}, // 1135 Rgba32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23491, 6), 1017}, // 1136 Rgba8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23497, 11), 1018}, // 1137 Rgba8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23633, 7), 1036}, // 1138 Rgba8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23689, 8), 1045}, // 1139 Rgba8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23462, 8), 1013}, // 1140 Unknown in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23755, 12), 1055}, // 1141 CrossDevice in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(23767, 7), 1056}, // 1142 Device in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(23793, 11), 1059}, // 1143 Invocation in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(23804, 12), 1060}, // 1144 QueueFamily in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(23816, 15), 1060}, // 1145 QueueFamilyKHR in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(23831, 14), 1061}, // 1146 ShaderCallKHR in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(23784, 9), 1058}, // 1147 Subgroup in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(23774, 10), 1057}, // 1148 Workgroup in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(23853, 12), 1064}, // 1149 DontFlatten in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(23845, 8), 1063}, // 1150 Flatten in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(13805, 5), 1062}, // 1151 None in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(23865, 29), 1065}, // 1152 IdentifierPossibleDuplicates in SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS
  {IR(13686, 8), 1067}, // 1153 Address in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13694, 8), 1068}, // 1154 Boolean in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13702, 6), 1069}, // 1155 Float in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13708, 7), 1070}, // 1156 Signed in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13715, 11), 1071}, // 1157 SignedChar in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13726, 9), 1072}, // 1158 Unsigned in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13735, 13), 1073}, // 1159 UnsignedChar in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13674, 12), 1066}, // 1160 Unspecified in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13748, 6), 1074}, // 1161 Class in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(13754, 10), 1075}, // 1162 Structure in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(13764, 6), 1076}, // 1163 Union in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(13785, 20), 1078}, // 1164 ImportedDeclaration in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(13770, 15), 1077}, // 1165 ImportedModule in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(13894, 15), 1086}, // 1166 FlagArtificial in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(13909, 13), 1087}, // 1167 FlagExplicit in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(13882, 12), 1085}, // 1168 FlagFwdDecl in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(13972, 21), 1091}, // 1169 FlagIndirectVariable in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(13865, 17), 1084}, // 1170 FlagIsDefinition in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14049, 16), 1095}, // 1171 FlagIsEnumClass in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(13853, 12), 1083}, // 1172 FlagIsLocal in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14033, 16), 1094}, // 1173 FlagIsOptimized in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(13826, 14), 1081}, // 1174 FlagIsPrivate in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(13810, 16), 1080}, // 1175 FlagIsProtected in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(13840, 13), 1082}, // 1176 FlagIsPublic in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(13993, 20), 1092}, // 1177 FlagLValueReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(13937, 18), 1089}, // 1178 FlagObjectPointer in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(13922, 15), 1088}, // 1179 FlagPrototyped in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14013, 20), 1093}, // 1180 FlagRValueReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(13955, 17), 1090}, // 1181 FlagStaticMember in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14085, 24), 1097}, // 1182 FlagTypePassByReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14065, 20), 1096}, // 1183 FlagTypePassByValue in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(23894, 26), 1098}, // 1184 FlagUnknownPhysicalLayout in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(13805, 5), 1079}, // 1185 None in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14170, 9), 1103}, // 1186 BitPiece in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14202, 7), 1107}, // 1187 Constu in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14109, 6), 1099}, // 1188 Deref in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14209, 9), 1108}, // 1189 Fragment in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14120, 6), 1101}, // 1190 Minus in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14115, 5), 1100}, // 1191 Plus in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14159, 11), 1102}, // 1192 PlusUconst in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14191, 11), 1106}, // 1193 StackValue in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14179, 5), 1104}, // 1194 Swap in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14184, 7), 1105}, // 1195 Xderef in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14254, 11), 1112}, // 1196 AtomicType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14218, 10), 1109}, // 1197 ConstType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14241, 13), 1111}, // 1198 RestrictType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14228, 13), 1110}, // 1199 VolatileType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(23955, 15), 1119}, // 1200 CPP_for_OpenCL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(23920, 5), 1114}, // 1201 ESSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(23925, 5), 1115}, // 1202 GLSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(23975, 7), 1121}, // 1203 HERO_C in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(23950, 5), 1118}, // 1204 HLSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(23982, 5), 1122}, // 1205 NZSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(23930, 9), 1116}, // 1206 OpenCL_C in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(23939, 11), 1117}, // 1207 OpenCL_CPP in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24002, 5), 1126}, // 1208 Rust in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(23970, 5), 1120}, // 1209 SYCL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(23992, 6), 1124}, // 1210 Slang in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(23462, 8), 1113}, // 1211 Unknown in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(23987, 5), 1123}, // 1212 WGSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(23998, 4), 1125}, // 1213 Zig in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24089, 14), 1137}, // 1214 AtomicCounter in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24171, 16), 1143}, // 1215 CallableDataKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24187, 15), 1143}, // 1216 CallableDataNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24485, 17), 1152}, // 1217 CodeSectionINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24036, 15), 1132}, // 1218 CrossWorkgroup in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24502, 16), 1153}, // 1219 DeviceOnlyINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24059, 9), 1134}, // 1220 Function in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24068, 8), 1135}, // 1221 Generic in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24276, 16), 1146}, // 1222 HitAttributeKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24292, 15), 1146}, // 1223 HitAttributeNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24440, 21), 1150}, // 1224 HitObjectAttributeNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24518, 14), 1154}, // 1225 HostOnlyINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24103, 6), 1138}, // 1226 Image in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24202, 24), 1144}, // 1227 IncomingCallableDataKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24226, 23), 1144}, // 1228 IncomingCallableDataNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24307, 22), 1147}, // 1229 IncomingRayPayloadKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24329, 21), 1147}, // 1230 IncomingRayPayloadNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24023, 6), 1128}, // 1231 Input in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24155, 16), 1142}, // 1232 NodePayloadAMDX in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24029, 7), 1130}, // 1233 Output in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24393, 22), 1149}, // 1234 PhysicalStorageBuffer in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24415, 25), 1149}, // 1235 PhysicalStorageBufferEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24051, 8), 1133}, // 1236 Private in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24076, 13), 1136}, // 1237 PushConstant in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24249, 14), 1145}, // 1238 RayPayloadKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24263, 13), 1145}, // 1239 RayPayloadNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24350, 22), 1148}, // 1240 ShaderRecordBufferKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24372, 21), 1148}, // 1241 ShaderRecordBufferNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24109, 14), 1139}, // 1242 StorageBuffer in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24461, 24), 1151}, // 1243 TaskPayloadWorkgroupEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24136, 19), 1141}, // 1244 TileAttachmentQCOM in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24123, 13), 1140}, // 1245 TileImageEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(15094, 8), 1129}, // 1246 Uniform in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24007, 16), 1127}, // 1247 UniformConstant in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(23774, 10), 1131}, // 1248 Workgroup in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(21586, 15), 1158}, // 1249 StreamingINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(21560, 14), 1155}, // 1250 UncachedINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(24550, 15), 1157}, // 1251 WriteBackINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(24532, 18), 1156}, // 1252 WriteThroughINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(24576, 11), 1161}, // 1253 DecodeFunc in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(13805, 5), 1159}, // 1254 None in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(24565, 11), 1160}, // 1255 TensorView in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(23407, 12), 1164}, // 1256 ClampToEdge in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(15052, 9), 1163}, // 1257 Constant in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(23425, 7), 1165}, // 1258 Repeat in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(23432, 15), 1166}, // 1259 RepeatMirrored in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(24587, 10), 1162}, // 1260 Undefined in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
}};

IndexRange OperandNameRangeForKind(spv_operand_type_t type) {
  switch(type) {
    case SPV_OPERAND_TYPE_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_ADDRESSING_MODEL: return IR(3, 5);
    case SPV_OPERAND_TYPE_BUILT_IN: return IR(8, 148);
    case SPV_OPERAND_TYPE_CAPABILITY: return IR(156, 291);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(447, 8);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(455, 3);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(458, 2);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS: return IR(460, 19);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION: return IR(479, 10);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(489, 4);
    case SPV_OPERAND_TYPE_COMPONENT_TYPE: return IR(493, 15);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT: return IR(508, 4);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS: return IR(512, 6);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE: return IR(518, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE: return IR(521, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT: return IR(524, 4);
    case SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(528, 8);
    case SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE: return IR(536, 3);
    case SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS: return IR(539, 16);
    case SPV_OPERAND_TYPE_DEBUG_OPERATION: return IR(555, 9);
    case SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER: return IR(564, 3);
    case SPV_OPERAND_TYPE_DECORATION: return IR(567, 149);
    case SPV_OPERAND_TYPE_DIMENSIONALITY: return IR(716, 8);
    case SPV_OPERAND_TYPE_EXECUTION_MODE: return IR(724, 101);
    case SPV_OPERAND_TYPE_EXECUTION_MODEL: return IR(825, 23);
    case SPV_OPERAND_TYPE_FPDENORM_MODE: return IR(848, 2);
    case SPV_OPERAND_TYPE_FPENCODING: return IR(850, 1);
    case SPV_OPERAND_TYPE_FPOPERATION_MODE: return IR(851, 2);
    case SPV_OPERAND_TYPE_FP_FAST_MATH_MODE: return IR(853, 11);
    case SPV_OPERAND_TYPE_FP_ROUNDING_MODE: return IR(864, 4);
    case SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE: return IR(868, 4);
    case SPV_OPERAND_TYPE_FUNCTION_CONTROL: return IR(872, 7);
    case SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE: return IR(879, 9);
    case SPV_OPERAND_TYPE_GROUP_OPERATION: return IR(888, 7);
    case SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER: return IR(895, 4);
    case SPV_OPERAND_TYPE_IMAGE: return IR(899, 21);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE: return IR(920, 26);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER: return IR(946, 20);
    case SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER: return IR(966, 2);
    case SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS: return IR(968, 3);
    case SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO: return IR(971, 2);
    case SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS: return IR(973, 2);
    case SPV_OPERAND_TYPE_LINKAGE_TYPE: return IR(975, 3);
    case SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL: return IR(978, 5);
    case SPV_OPERAND_TYPE_LOOP_CONTROL: return IR(983, 20);
    case SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(1003, 15);
    case SPV_OPERAND_TYPE_MEMORY_ACCESS: return IR(1018, 12);
    case SPV_OPERAND_TYPE_MEMORY_MODEL: return IR(1030, 5);
    case SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID: return IR(1035, 19);
    case SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS: return IR(1054, 1);
    case SPV_OPERAND_TYPE_OVERFLOW_MODES: return IR(1055, 4);
    case SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT: return IR(1059, 2);
    case SPV_OPERAND_TYPE_QUANTIZATION_MODES: return IR(1061, 8);
    case SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS: return IR(1069, 3);
    case SPV_OPERAND_TYPE_RAY_FLAGS: return IR(1072, 13);
    case SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE: return IR(1085, 2);
    case SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE: return IR(1087, 3);
    case SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION: return IR(1090, 2);
    case SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE: return IR(1092, 5);
    case SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE: return IR(1097, 2);
    case SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT: return IR(1099, 42);
    case SPV_OPERAND_TYPE_SCOPE_ID: return IR(1141, 8);
    case SPV_OPERAND_TYPE_SELECTION_CONTROL: return IR(1149, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS: return IR(1152, 1);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(1153, 8);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(1161, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(1164, 2);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS: return IR(1166, 20);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION: return IR(1186, 10);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(1196, 4);
    case SPV_OPERAND_TYPE_SOURCE_LANGUAGE: return IR(1200, 14);
    case SPV_OPERAND_TYPE_STORAGE_CLASS: return IR(1214, 35);
    case SPV_OPERAND_TYPE_STORE_CACHE_CONTROL: return IR(1249, 4);
    case SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS: return IR(1253, 3);
    case SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE: return IR(1256, 5);
    case SPV_OPERAND_TYPE_OPTIONAL_IMAGE: return IR(899, 21);
    case SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS: return IR(1018, 12);
    case SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT: return IR(1059, 2);
    case SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS: return IR(512, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(1003, 15);
    case SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS: return IR(1069, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_FPENCODING: return IR(850, 1);
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
static const std::array<InstructionDesc, 794> kInstructionDesc{{
  {spv::Op::OpNop, false, false, IR(0, 0), IR(24597, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpUndef, true, true, IR(39, 2), IR(24653, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpSourceContinued, false, false, IR(11, 1), IR(24659, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpSource, false, false, IR(41, 4), IR(24778, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpSourceExtension, false, false, IR(11, 1), IR(24785, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpName, false, false, IR(45, 2), IR(24801, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpMemberName, false, false, IR(47, 3), IR(24806, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpString, true, false, IR(50, 2), IR(24817, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpLine, false, false, IR(52, 3), IR(24824, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpExtension, false, false, IR(11, 1), IR(24829, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpExtInstImport, true, false, IR(50, 2), IR(24839, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpExtInst, true, true, IR(55, 4), IR(24899, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpMemoryModel, false, false, IR(59, 2), IR(24971, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpEntryPoint, false, false, IR(61, 4), IR(25045, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpExecutionMode, false, false, IR(65, 2), IR(25088, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpCapability, false, false, IR(67, 1), IR(25130, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpTypeVoid, true, false, IR(68, 1), IR(25141, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeBool, true, false, IR(68, 1), IR(25150, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeInt, true, false, IR(69, 3), IR(25159, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeFloat, true, false, IR(72, 3), IR(25204, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeVector, true, false, IR(75, 3), IR(25214, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeMatrix, true, false, IR(75, 3), IR(25225, 11), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeImage, true, false, IR(78, 9), IR(25349, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeSampler, true, false, IR(68, 1), IR(25359, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeSampledImage, true, false, IR(87, 2), IR(25371, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeArray, true, false, IR(89, 3), IR(25388, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeRuntimeArray, true, false, IR(87, 2), IR(25398, 17), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeStruct, true, false, IR(92, 2), IR(25415, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeOpaque, true, false, IR(50, 2), IR(25426, 11), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypePointer, true, false, IR(94, 3), IR(25468, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeFunction, true, false, IR(97, 3), IR(25480, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeEvent, true, false, IR(68, 1), IR(25493, 10), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeDeviceEvent, true, false, IR(68, 1), IR(25503, 16), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeReserveId, true, false, IR(68, 1), IR(25519, 14), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeQueue, true, false, IR(68, 1), IR(25533, 10), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypePipe, true, false, IR(100, 2), IR(25543, 9), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeForwardPointer, false, false, IR(102, 2), IR(25552, 19), IR(0, 0), IR(197, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantTrue, true, true, IR(39, 2), IR(25571, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantFalse, true, true, IR(39, 2), IR(25584, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstant, true, true, IR(104, 3), IR(15052, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantComposite, true, true, IR(107, 3), IR(25636, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantSampler, true, true, IR(110, 5), IR(25732, 16), IR(0, 0), IR(199, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantNull, true, true, IR(39, 2), IR(25748, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantTrue, true, true, IR(39, 2), IR(25761, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantFalse, true, true, IR(39, 2), IR(25778, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstant, true, true, IR(104, 3), IR(25796, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantComposite, true, true, IR(107, 3), IR(25809, 22), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantOp, true, true, IR(115, 3), IR(25872, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpFunction, true, true, IR(118, 4), IR(24059, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionParameter, true, true, IR(39, 2), IR(25921, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionEnd, false, false, IR(0, 0), IR(25939, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionCall, true, true, IR(122, 4), IR(25951, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpVariable, true, true, IR(126, 4), IR(25964, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpImageTexelPointer, true, true, IR(130, 5), IR(25973, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpLoad, true, true, IR(135, 4), IR(26031, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpStore, false, false, IR(139, 3), IR(26036, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCopyMemory, false, false, IR(142, 4), IR(26042, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCopyMemorySized, false, false, IR(146, 5), IR(26053, 16), IR(0, 0), IR(200, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpAccessChain, true, true, IR(122, 4), IR(26069, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpInBoundsAccessChain, true, true, IR(122, 4), IR(26081, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrAccessChain, true, true, IR(151, 5), IR(26101, 15), IR(0, 0), IR(202, 4), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpArrayLength, true, true, IR(156, 4), IR(26116, 12), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpGenericPtrMemSemantics, true, true, IR(160, 3), IR(26128, 23), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpInBoundsPtrAccessChain, true, true, IR(151, 5), IR(26151, 23), IR(0, 0), IR(1, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpDecorate, false, false, IR(163, 2), IR(26202, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpMemberDecorate, false, false, IR(165, 3), IR(26211, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpDecorationGroup, true, false, IR(68, 1), IR(26226, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupDecorate, false, false, IR(168, 2), IR(26242, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupMemberDecorate, false, false, IR(170, 2), IR(26301, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpVectorExtractDynamic, true, true, IR(172, 4), IR(26321, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpVectorInsertDynamic, true, true, IR(130, 5), IR(26342, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpVectorShuffle, true, true, IR(176, 5), IR(26362, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeConstruct, true, true, IR(107, 3), IR(26376, 19), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeExtract, true, true, IR(181, 4), IR(26395, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeInsert, true, true, IR(176, 5), IR(26412, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCopyObject, true, true, IR(160, 3), IR(26428, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpTranspose, true, true, IR(160, 3), IR(26439, 10), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpSampledImage, true, true, IR(172, 4), IR(26449, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleImplicitLod, true, true, IR(185, 5), IR(26494, 23), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleExplicitLod, true, true, IR(190, 5), IR(26540, 23), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleDrefImplicitLod, true, true, IR(195, 6), IR(26563, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleDrefExplicitLod, true, true, IR(201, 6), IR(26590, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjImplicitLod, true, true, IR(185, 5), IR(26617, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjExplicitLod, true, true, IR(190, 5), IR(26644, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjDrefImplicitLod, true, true, IR(195, 6), IR(26671, 31), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjDrefExplicitLod, true, true, IR(201, 6), IR(26702, 31), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageFetch, true, true, IR(185, 5), IR(26733, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageGather, true, true, IR(195, 6), IR(26744, 12), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageDrefGather, true, true, IR(195, 6), IR(26756, 16), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageRead, true, true, IR(185, 5), IR(26772, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageWrite, false, false, IR(207, 4), IR(26782, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImage, true, true, IR(160, 3), IR(24103, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryFormat, true, true, IR(160, 3), IR(26793, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryOrder, true, true, IR(160, 3), IR(26810, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySizeLod, true, true, IR(172, 4), IR(26826, 18), IR(0, 0), IR(206, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySize, true, true, IR(160, 3), IR(26844, 15), IR(0, 0), IR(206, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryLod, true, true, IR(172, 4), IR(26859, 14), IR(0, 0), IR(208, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryLevels, true, true, IR(160, 3), IR(26873, 17), IR(0, 0), IR(206, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySamples, true, true, IR(160, 3), IR(26890, 18), IR(0, 0), IR(206, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertFToU, true, true, IR(160, 3), IR(26908, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertFToS, true, true, IR(160, 3), IR(26920, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertSToF, true, true, IR(160, 3), IR(26932, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToF, true, true, IR(160, 3), IR(26944, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpUConvert, true, true, IR(160, 3), IR(26956, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSConvert, true, true, IR(160, 3), IR(26965, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpFConvert, true, true, IR(160, 3), IR(26974, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpQuantizeToF16, true, true, IR(160, 3), IR(26983, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertPtrToU, true, true, IR(160, 3), IR(26997, 14), IR(0, 0), IR(197, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSatConvertSToU, true, true, IR(160, 3), IR(27011, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSatConvertUToS, true, true, IR(160, 3), IR(27026, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToPtr, true, true, IR(160, 3), IR(27041, 14), IR(0, 0), IR(197, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpPtrCastToGeneric, true, true, IR(160, 3), IR(27055, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpGenericCastToPtr, true, true, IR(160, 3), IR(27072, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpGenericCastToPtrExplicit, true, true, IR(211, 4), IR(27089, 25), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpBitcast, true, true, IR(160, 3), IR(27114, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSNegate, true, true, IR(160, 3), IR(27122, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFNegate, true, true, IR(160, 3), IR(27130, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIAdd, true, true, IR(172, 4), IR(27138, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFAdd, true, true, IR(172, 4), IR(27143, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpISub, true, true, IR(172, 4), IR(27148, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFSub, true, true, IR(172, 4), IR(27153, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIMul, true, true, IR(172, 4), IR(27158, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFMul, true, true, IR(172, 4), IR(27163, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDiv, true, true, IR(172, 4), IR(27168, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSDiv, true, true, IR(172, 4), IR(27173, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFDiv, true, true, IR(172, 4), IR(27178, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUMod, true, true, IR(172, 4), IR(27183, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSRem, true, true, IR(172, 4), IR(27188, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSMod, true, true, IR(172, 4), IR(27193, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFRem, true, true, IR(172, 4), IR(27198, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFMod, true, true, IR(172, 4), IR(27203, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpVectorTimesScalar, true, true, IR(172, 4), IR(27208, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesScalar, true, true, IR(172, 4), IR(27226, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpVectorTimesMatrix, true, true, IR(172, 4), IR(27244, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesVector, true, true, IR(172, 4), IR(27262, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesMatrix, true, true, IR(172, 4), IR(27280, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpOuterProduct, true, true, IR(172, 4), IR(27298, 13), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpDot, true, true, IR(172, 4), IR(27311, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIAddCarry, true, true, IR(172, 4), IR(27315, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpISubBorrow, true, true, IR(172, 4), IR(27325, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUMulExtended, true, true, IR(172, 4), IR(27336, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSMulExtended, true, true, IR(172, 4), IR(27349, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpAny, true, true, IR(160, 3), IR(27362, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpAll, true, true, IR(160, 3), IR(27366, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsNan, true, true, IR(160, 3), IR(27370, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsInf, true, true, IR(160, 3), IR(27376, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsFinite, true, true, IR(160, 3), IR(27382, 9), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsNormal, true, true, IR(160, 3), IR(27391, 9), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSignBitSet, true, true, IR(160, 3), IR(27400, 11), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLessOrGreater, true, true, IR(172, 4), IR(27411, 14), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), SPV_SPIRV_VERSION_WORD(1,5), PrintingClass::kRelational_and_Logical},
  {spv::Op::OpOrdered, true, true, IR(172, 4), IR(27425, 8), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUnordered, true, true, IR(172, 4), IR(27433, 10), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalEqual, true, true, IR(172, 4), IR(27443, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalNotEqual, true, true, IR(172, 4), IR(27456, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalOr, true, true, IR(172, 4), IR(27472, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalAnd, true, true, IR(172, 4), IR(27482, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalNot, true, true, IR(160, 3), IR(27493, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSelect, true, true, IR(130, 5), IR(27504, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIEqual, true, true, IR(172, 4), IR(27511, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpINotEqual, true, true, IR(172, 4), IR(27518, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUGreaterThan, true, true, IR(172, 4), IR(27528, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSGreaterThan, true, true, IR(172, 4), IR(27541, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUGreaterThanEqual, true, true, IR(172, 4), IR(27554, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSGreaterThanEqual, true, true, IR(172, 4), IR(27572, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpULessThan, true, true, IR(172, 4), IR(27590, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSLessThan, true, true, IR(172, 4), IR(27600, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpULessThanEqual, true, true, IR(172, 4), IR(27610, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSLessThanEqual, true, true, IR(172, 4), IR(27625, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdEqual, true, true, IR(172, 4), IR(27640, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordEqual, true, true, IR(172, 4), IR(27650, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdNotEqual, true, true, IR(172, 4), IR(27662, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordNotEqual, true, true, IR(172, 4), IR(27675, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdLessThan, true, true, IR(172, 4), IR(27690, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordLessThan, true, true, IR(172, 4), IR(27703, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdGreaterThan, true, true, IR(172, 4), IR(27718, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordGreaterThan, true, true, IR(172, 4), IR(27734, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdLessThanEqual, true, true, IR(172, 4), IR(27752, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordLessThanEqual, true, true, IR(172, 4), IR(27770, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdGreaterThanEqual, true, true, IR(172, 4), IR(27790, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordGreaterThanEqual, true, true, IR(172, 4), IR(27811, 23), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpShiftRightLogical, true, true, IR(172, 4), IR(27834, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpShiftRightArithmetic, true, true, IR(172, 4), IR(27852, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpShiftLeftLogical, true, true, IR(172, 4), IR(27873, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseOr, true, true, IR(172, 4), IR(27890, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseXor, true, true, IR(172, 4), IR(27900, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseAnd, true, true, IR(172, 4), IR(27911, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpNot, true, true, IR(160, 3), IR(27922, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldInsert, true, true, IR(215, 6), IR(27926, 15), IR(0, 0), IR(209, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldSExtract, true, true, IR(130, 5), IR(27941, 17), IR(0, 0), IR(209, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldUExtract, true, true, IR(130, 5), IR(27958, 17), IR(0, 0), IR(209, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitReverse, true, true, IR(160, 3), IR(27975, 11), IR(0, 0), IR(209, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitCount, true, true, IR(160, 3), IR(27986, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpDPdx, true, true, IR(160, 3), IR(27995, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdy, true, true, IR(160, 3), IR(28000, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidth, true, true, IR(160, 3), IR(28005, 7), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdxFine, true, true, IR(160, 3), IR(28012, 9), IR(0, 0), IR(211, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdyFine, true, true, IR(160, 3), IR(28021, 9), IR(0, 0), IR(211, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidthFine, true, true, IR(160, 3), IR(28030, 11), IR(0, 0), IR(211, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdxCoarse, true, true, IR(160, 3), IR(28041, 11), IR(0, 0), IR(211, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdyCoarse, true, true, IR(160, 3), IR(28052, 11), IR(0, 0), IR(211, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidthCoarse, true, true, IR(160, 3), IR(28063, 13), IR(0, 0), IR(211, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpEmitVertex, false, false, IR(0, 0), IR(28076, 11), IR(0, 0), IR(69, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEndPrimitive, false, false, IR(0, 0), IR(28087, 13), IR(0, 0), IR(69, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEmitStreamVertex, false, false, IR(10, 1), IR(28100, 17), IR(0, 0), IR(110, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEndStreamPrimitive, false, false, IR(10, 1), IR(28117, 19), IR(0, 0), IR(110, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpControlBarrier, false, false, IR(221, 3), IR(28173, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpMemoryBarrier, false, false, IR(224, 2), IR(28188, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpAtomicLoad, true, true, IR(226, 5), IR(28202, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicStore, false, false, IR(231, 4), IR(28213, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicExchange, true, true, IR(235, 6), IR(28225, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicCompareExchange, true, true, IR(241, 8), IR(28240, 22), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicCompareExchangeWeak, true, true, IR(241, 8), IR(28262, 26), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), SPV_SPIRV_VERSION_WORD(1,3), PrintingClass::kAtomic},
  {spv::Op::OpAtomicIIncrement, true, true, IR(226, 5), IR(28288, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicIDecrement, true, true, IR(226, 5), IR(28305, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicIAdd, true, true, IR(235, 6), IR(28322, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicISub, true, true, IR(235, 6), IR(28333, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicSMin, true, true, IR(235, 6), IR(28344, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicUMin, true, true, IR(235, 6), IR(28355, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicSMax, true, true, IR(235, 6), IR(28366, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicUMax, true, true, IR(235, 6), IR(28377, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicAnd, true, true, IR(235, 6), IR(28388, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicOr, true, true, IR(235, 6), IR(28398, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicXor, true, true, IR(235, 6), IR(28407, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpPhi, true, true, IR(107, 3), IR(28417, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLoopMerge, false, false, IR(249, 3), IR(28451, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpSelectionMerge, false, false, IR(252, 2), IR(28496, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLabel, true, false, IR(68, 1), IR(28511, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpBranch, false, false, IR(10, 1), IR(28517, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpBranchConditional, false, false, IR(254, 4), IR(28524, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpSwitch, false, false, IR(258, 3), IR(28587, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpKill, false, false, IR(0, 0), IR(28594, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpReturn, false, false, IR(0, 0), IR(28599, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpReturnValue, false, false, IR(10, 1), IR(28606, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpUnreachable, false, false, IR(0, 0), IR(28618, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLifetimeStart, false, false, IR(261, 2), IR(28630, 14), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLifetimeStop, false, false, IR(261, 2), IR(28644, 13), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpGroupAsyncCopy, true, true, IR(263, 8), IR(28657, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupWaitEvents, false, false, IR(271, 3), IR(28672, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupAll, true, true, IR(274, 4), IR(28688, 9), IR(0, 0), IR(212, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupAny, true, true, IR(274, 4), IR(28697, 9), IR(0, 0), IR(212, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBroadcast, true, true, IR(278, 5), IR(28706, 15), IR(0, 0), IR(212, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupIAdd, true, true, IR(283, 5), IR(28754, 10), IR(0, 0), IR(212, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFAdd, true, true, IR(283, 5), IR(28764, 10), IR(0, 0), IR(212, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMin, true, true, IR(283, 5), IR(28774, 10), IR(0, 0), IR(212, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMin, true, true, IR(283, 5), IR(28784, 10), IR(0, 0), IR(212, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMin, true, true, IR(283, 5), IR(28794, 10), IR(0, 0), IR(212, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMax, true, true, IR(283, 5), IR(28804, 10), IR(0, 0), IR(212, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMax, true, true, IR(283, 5), IR(28814, 10), IR(0, 0), IR(212, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMax, true, true, IR(283, 5), IR(28824, 10), IR(0, 0), IR(212, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpReadPipe, true, true, IR(215, 6), IR(28834, 9), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpWritePipe, true, true, IR(215, 6), IR(28843, 10), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReservedReadPipe, true, true, IR(288, 8), IR(28853, 17), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReservedWritePipe, true, true, IR(288, 8), IR(28870, 18), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReserveReadPipePackets, true, true, IR(215, 6), IR(28888, 23), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReserveWritePipePackets, true, true, IR(215, 6), IR(28911, 24), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCommitReadPipe, false, false, IR(296, 4), IR(28935, 15), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCommitWritePipe, false, false, IR(296, 4), IR(28950, 16), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpIsValidReserveId, true, true, IR(160, 3), IR(28966, 17), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetNumPipePackets, true, true, IR(130, 5), IR(28983, 18), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetMaxPipePackets, true, true, IR(130, 5), IR(29001, 18), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupReserveReadPipePackets, true, true, IR(300, 7), IR(29019, 28), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupReserveWritePipePackets, true, true, IR(300, 7), IR(29047, 29), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupCommitReadPipe, false, false, IR(307, 5), IR(29076, 20), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupCommitWritePipe, false, false, IR(307, 5), IR(29096, 21), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpEnqueueMarker, true, true, IR(215, 6), IR(29117, 14), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpEnqueueKernel, true, true, IR(312, 13), IR(29131, 14), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelNDrangeSubGroupCount, true, true, IR(325, 7), IR(29145, 30), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelNDrangeMaxSubGroupSize, true, true, IR(325, 7), IR(29175, 32), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelWorkGroupSize, true, true, IR(215, 6), IR(29207, 23), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelPreferredWorkGroupSizeMultiple, true, true, IR(215, 6), IR(29230, 40), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpRetainEvent, false, false, IR(10, 1), IR(29270, 12), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpReleaseEvent, false, false, IR(10, 1), IR(29282, 13), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpCreateUserEvent, true, true, IR(39, 2), IR(29295, 16), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpIsValidEvent, true, true, IR(160, 3), IR(29311, 13), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpSetUserEventStatus, false, false, IR(36, 2), IR(29324, 19), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpCaptureEventProfilingInfo, false, false, IR(33, 3), IR(29343, 26), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetDefaultQueue, true, true, IR(39, 2), IR(29369, 16), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpBuildNDRange, true, true, IR(130, 5), IR(29385, 13), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpImageSparseSampleImplicitLod, true, true, IR(185, 5), IR(29398, 29), IR(0, 0), IR(213, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleExplicitLod, true, true, IR(190, 5), IR(29427, 29), IR(0, 0), IR(213, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleDrefImplicitLod, true, true, IR(195, 6), IR(29456, 33), IR(0, 0), IR(213, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleDrefExplicitLod, true, true, IR(201, 6), IR(29489, 33), IR(0, 0), IR(213, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjImplicitLod, true, true, IR(185, 5), IR(29522, 33), IR(0, 0), IR(213, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjExplicitLod, true, true, IR(190, 5), IR(29555, 33), IR(0, 0), IR(213, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjDrefImplicitLod, true, true, IR(195, 6), IR(29588, 37), IR(0, 0), IR(213, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjDrefExplicitLod, true, true, IR(201, 6), IR(29625, 37), IR(0, 0), IR(213, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseFetch, true, true, IR(185, 5), IR(29662, 17), IR(0, 0), IR(213, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseGather, true, true, IR(195, 6), IR(29679, 18), IR(0, 0), IR(213, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseDrefGather, true, true, IR(195, 6), IR(29697, 22), IR(0, 0), IR(213, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseTexelsResident, true, true, IR(160, 3), IR(29719, 26), IR(0, 0), IR(213, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpNoLine, false, false, IR(0, 0), IR(29745, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpAtomicFlagTestAndSet, true, true, IR(226, 5), IR(29752, 21), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicFlagClear, false, false, IR(332, 3), IR(29773, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpImageSparseRead, true, true, IR(185, 5), IR(29789, 16), IR(0, 0), IR(213, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpSizeOf, true, true, IR(160, 3), IR(29805, 7), IR(0, 0), IR(1, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpTypePipeStorage, true, false, IR(68, 1), IR(29812, 16), IR(0, 0), IR(214, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantPipeStorage, true, true, IR(335, 5), IR(29828, 20), IR(0, 0), IR(214, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCreatePipeFromPipeStorage, true, true, IR(160, 3), IR(29848, 26), IR(0, 0), IR(214, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetKernelLocalSizeForSubgroupCount, true, true, IR(325, 7), IR(29874, 35), IR(0, 0), IR(148, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelMaxNumSubgroups, true, true, IR(215, 6), IR(29909, 25), IR(0, 0), IR(148, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpTypeNamedBarrier, true, false, IR(68, 1), IR(29934, 17), IR(0, 0), IR(215, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpNamedBarrierInitialize, true, true, IR(160, 3), IR(29951, 23), IR(0, 0), IR(215, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpMemoryNamedBarrier, false, false, IR(332, 3), IR(29974, 19), IR(0, 0), IR(215, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpModuleProcessed, false, false, IR(11, 1), IR(29993, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpExecutionModeId, false, false, IR(65, 2), IR(30009, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,2), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpDecorateId, false, false, IR(163, 2), IR(30025, 11), IR(0, 0), IR(1, 0), IR(151, 1), SPV_SPIRV_VERSION_WORD(1,2), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupNonUniformElect, true, true, IR(340, 3), IR(30036, 21), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAll, true, true, IR(274, 4), IR(30057, 19), IR(0, 0), IR(216, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAny, true, true, IR(274, 4), IR(30076, 19), IR(0, 0), IR(216, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAllEqual, true, true, IR(274, 4), IR(30095, 24), IR(0, 0), IR(216, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBroadcast, true, true, IR(278, 5), IR(30119, 25), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBroadcastFirst, true, true, IR(274, 4), IR(30144, 30), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallot, true, true, IR(274, 4), IR(5512, 22), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformInverseBallot, true, true, IR(274, 4), IR(30174, 29), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotBitExtract, true, true, IR(278, 5), IR(30203, 32), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotBitCount, true, true, IR(283, 5), IR(30235, 30), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotFindLSB, true, true, IR(274, 4), IR(30265, 29), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotFindMSB, true, true, IR(274, 4), IR(30294, 29), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffle, true, true, IR(278, 5), IR(8602, 23), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleXor, true, true, IR(278, 5), IR(30323, 26), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleUp, true, true, IR(278, 5), IR(30349, 25), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleDown, true, true, IR(278, 5), IR(30374, 27), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformIAdd, true, true, IR(343, 6), IR(30401, 20), IR(0, 0), IR(220, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFAdd, true, true, IR(343, 6), IR(30421, 20), IR(0, 0), IR(220, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformIMul, true, true, IR(343, 6), IR(30441, 20), IR(0, 0), IR(220, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMul, true, true, IR(343, 6), IR(30461, 20), IR(0, 0), IR(220, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformSMin, true, true, IR(343, 6), IR(30481, 20), IR(0, 0), IR(220, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformUMin, true, true, IR(343, 6), IR(30501, 20), IR(0, 0), IR(220, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMin, true, true, IR(343, 6), IR(30521, 20), IR(0, 0), IR(220, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformSMax, true, true, IR(343, 6), IR(30541, 20), IR(0, 0), IR(220, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformUMax, true, true, IR(343, 6), IR(30561, 20), IR(0, 0), IR(220, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMax, true, true, IR(343, 6), IR(30581, 20), IR(0, 0), IR(220, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseAnd, true, true, IR(343, 6), IR(30601, 26), IR(0, 0), IR(220, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseOr, true, true, IR(343, 6), IR(30627, 25), IR(0, 0), IR(220, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseXor, true, true, IR(343, 6), IR(30652, 26), IR(0, 0), IR(220, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalAnd, true, true, IR(343, 6), IR(30678, 26), IR(0, 0), IR(220, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalOr, true, true, IR(343, 6), IR(30704, 25), IR(0, 0), IR(220, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalXor, true, true, IR(343, 6), IR(30729, 26), IR(0, 0), IR(220, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadBroadcast, true, true, IR(278, 5), IR(30755, 29), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadSwap, true, true, IR(278, 5), IR(30784, 24), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpCopyLogical, true, true, IR(160, 3), IR(30808, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpPtrEqual, true, true, IR(172, 4), IR(30820, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrNotEqual, true, true, IR(172, 4), IR(30829, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrDiff, true, true, IR(172, 4), IR(30841, 8), IR(0, 0), IR(224, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpColorAttachmentReadEXT, true, true, IR(349, 4), IR(30849, 23), IR(0, 0), IR(140, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpDepthAttachmentReadEXT, true, true, IR(353, 3), IR(30872, 23), IR(0, 0), IR(149, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpStencilAttachmentReadEXT, true, true, IR(353, 3), IR(30895, 25), IR(0, 0), IR(150, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpTerminateInvocation, false, false, IR(0, 0), IR(30920, 20), IR(0, 0), IR(3, 1), IR(161, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpTypeUntypedPointerKHR, true, false, IR(356, 2), IR(30940, 22), IR(0, 0), IR(227, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpUntypedVariableKHR, true, true, IR(358, 5), IR(30962, 19), IR(0, 0), IR(227, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedAccessChainKHR, true, true, IR(151, 5), IR(30981, 22), IR(0, 0), IR(227, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedInBoundsAccessChainKHR, true, true, IR(151, 5), IR(31003, 30), IR(0, 0), IR(227, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpSubgroupBallotKHR, true, true, IR(160, 3), IR(5273, 18), IR(0, 0), IR(228, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupFirstInvocationKHR, true, true, IR(160, 3), IR(31033, 27), IR(0, 0), IR(228, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpUntypedPtrAccessChainKHR, true, true, IR(363, 6), IR(31060, 25), IR(0, 0), IR(227, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedInBoundsPtrAccessChainKHR, true, true, IR(363, 6), IR(31085, 33), IR(0, 0), IR(227, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedArrayLengthKHR, true, true, IR(369, 5), IR(31118, 22), IR(0, 0), IR(227, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedPrefetchKHR, false, false, IR(374, 5), IR(31140, 19), IR(0, 0), IR(227, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpSubgroupAllKHR, true, true, IR(160, 3), IR(31159, 15), IR(0, 0), IR(229, 1), IR(38, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupAnyKHR, true, true, IR(160, 3), IR(31174, 15), IR(0, 0), IR(229, 1), IR(38, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupAllEqualKHR, true, true, IR(160, 3), IR(31189, 20), IR(0, 0), IR(229, 1), IR(38, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupNonUniformRotateKHR, true, true, IR(379, 6), IR(12946, 25), IR(0, 0), IR(230, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupReadInvocationKHR, true, true, IR(172, 4), IR(31209, 26), IR(0, 0), IR(228, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpExtInstWithForwardRefsKHR, true, true, IR(385, 5), IR(31235, 26), IR(0, 0), IR(1, 0), IR(162, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpTraceRayKHR, false, false, IR(390, 11), IR(31261, 12), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpExecuteCallableKHR, false, false, IR(36, 2), IR(31273, 19), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToAccelerationStructureKHR, true, true, IR(160, 3), IR(31292, 35), IR(0, 0), IR(231, 2), IR(163, 2), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIgnoreIntersectionKHR, false, false, IR(0, 0), IR(31327, 22), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTerminateRayKHR, false, false, IR(0, 0), IR(31349, 16), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSDot, true, true, IR(401, 5), IR(31412, 5), IR(93, 1), IR(233, 1), IR(118, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDot, true, true, IR(401, 5), IR(31425, 5), IR(94, 1), IR(233, 1), IR(118, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSUDot, true, true, IR(401, 5), IR(31438, 6), IR(95, 1), IR(233, 1), IR(118, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSDotAccSat, true, true, IR(406, 6), IR(31453, 11), IR(96, 1), IR(233, 1), IR(118, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDotAccSat, true, true, IR(406, 6), IR(31478, 11), IR(97, 1), IR(233, 1), IR(118, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSUDotAccSat, true, true, IR(406, 6), IR(31503, 12), IR(98, 1), IR(233, 1), IR(118, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpTypeCooperativeMatrixKHR, true, false, IR(412, 6), IR(31530, 25), IR(0, 0), IR(234, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeMatrixLoadKHR, true, true, IR(418, 6), IR(31555, 25), IR(0, 0), IR(234, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixStoreKHR, false, false, IR(424, 5), IR(31580, 26), IR(0, 0), IR(234, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixMulAddKHR, true, true, IR(429, 6), IR(31660, 27), IR(0, 0), IR(234, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpCooperativeMatrixLengthKHR, true, true, IR(160, 3), IR(31687, 27), IR(0, 0), IR(234, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpConstantCompositeReplicateEXT, true, true, IR(160, 3), IR(31714, 30), IR(0, 0), IR(235, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCompositeReplicateEXT, true, true, IR(160, 3), IR(31744, 34), IR(0, 0), IR(235, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpCompositeConstructReplicateEXT, true, true, IR(160, 3), IR(31778, 31), IR(0, 0), IR(235, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpTypeRayQueryKHR, true, false, IR(68, 1), IR(31809, 16), IR(0, 0), IR(187, 1), IR(45, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpRayQueryInitializeKHR, false, false, IR(435, 8), IR(31825, 22), IR(0, 0), IR(187, 1), IR(45, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryTerminateKHR, false, false, IR(10, 1), IR(31847, 21), IR(0, 0), IR(187, 1), IR(45, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGenerateIntersectionKHR, false, false, IR(36, 2), IR(31868, 32), IR(0, 0), IR(187, 1), IR(45, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryConfirmIntersectionKHR, false, false, IR(10, 1), IR(31900, 31), IR(0, 0), IR(187, 1), IR(45, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryProceedKHR, true, true, IR(160, 3), IR(31931, 19), IR(0, 0), IR(187, 1), IR(45, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTypeKHR, true, true, IR(172, 4), IR(31950, 31), IR(0, 0), IR(187, 1), IR(45, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpImageSampleWeightedQCOM, true, true, IR(130, 5), IR(31981, 24), IR(0, 0), IR(236, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBoxFilterQCOM, true, true, IR(130, 5), IR(32005, 19), IR(0, 0), IR(237, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchSSDQCOM, true, true, IR(325, 7), IR(32024, 23), IR(0, 0), IR(238, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchSADQCOM, true, true, IR(325, 7), IR(32047, 23), IR(0, 0), IR(238, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchWindowSSDQCOM, true, true, IR(325, 7), IR(32070, 29), IR(0, 0), IR(239, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchWindowSADQCOM, true, true, IR(325, 7), IR(32099, 29), IR(0, 0), IR(239, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchGatherSSDQCOM, true, true, IR(325, 7), IR(32128, 29), IR(0, 0), IR(239, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchGatherSADQCOM, true, true, IR(325, 7), IR(32157, 29), IR(0, 0), IR(239, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpGroupIAddNonUniformAMD, true, true, IR(283, 5), IR(32186, 23), IR(0, 0), IR(212, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFAddNonUniformAMD, true, true, IR(283, 5), IR(32209, 23), IR(0, 0), IR(212, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMinNonUniformAMD, true, true, IR(283, 5), IR(32232, 23), IR(0, 0), IR(212, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMinNonUniformAMD, true, true, IR(283, 5), IR(32255, 23), IR(0, 0), IR(212, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMinNonUniformAMD, true, true, IR(283, 5), IR(32278, 23), IR(0, 0), IR(212, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMaxNonUniformAMD, true, true, IR(283, 5), IR(32301, 23), IR(0, 0), IR(212, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMaxNonUniformAMD, true, true, IR(283, 5), IR(32324, 23), IR(0, 0), IR(212, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMaxNonUniformAMD, true, true, IR(283, 5), IR(32347, 23), IR(0, 0), IR(212, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpFragmentMaskFetchAMD, true, true, IR(172, 4), IR(32370, 21), IR(0, 0), IR(240, 1), IR(54, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFragmentFetchAMD, true, true, IR(130, 5), IR(32391, 17), IR(0, 0), IR(240, 1), IR(54, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReadClockKHR, true, true, IR(340, 3), IR(32408, 13), IR(0, 0), IR(241, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAllocateNodePayloadsAMDX, true, true, IR(278, 5), IR(32421, 25), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpEnqueueNodePayloadsAMDX, false, false, IR(10, 1), IR(32446, 24), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeNodePayloadArrayAMDX, true, false, IR(87, 2), IR(32470, 25), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFinishWritingNodePayloadAMDX, true, true, IR(160, 3), IR(32495, 29), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpNodePayloadArrayLengthAMDX, true, true, IR(160, 3), IR(32524, 27), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIsNodePayloadValidAMDX, true, true, IR(172, 4), IR(32551, 23), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConstantStringAMDX, true, false, IR(50, 2), IR(32574, 19), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSpecConstantStringAMDX, true, false, IR(50, 2), IR(32593, 23), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpGroupNonUniformQuadAllKHR, true, true, IR(160, 3), IR(32616, 26), IR(0, 0), IR(157, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadAnyKHR, true, true, IR(160, 3), IR(32642, 26), IR(0, 0), IR(157, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpHitObjectRecordHitMotionNV, false, false, IR(443, 14), IR(32668, 27), IR(0, 0), IR(242, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitWithIndexMotionNV, false, false, IR(457, 13), IR(32695, 36), IR(0, 0), IR(242, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissMotionNV, false, false, IR(470, 7), IR(32731, 28), IR(0, 0), IR(242, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldToObjectNV, true, true, IR(160, 3), IR(32759, 28), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectToWorldNV, true, true, IR(160, 3), IR(32787, 28), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayDirectionNV, true, true, IR(160, 3), IR(32815, 33), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayOriginNV, true, true, IR(160, 3), IR(32848, 30), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayMotionNV, false, false, IR(457, 13), IR(32878, 26), IR(0, 0), IR(242, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderRecordBufferHandleNV, true, true, IR(160, 3), IR(32904, 39), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderBindingTableRecordIndexNV, true, true, IR(160, 3), IR(32943, 44), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordEmptyNV, false, false, IR(10, 1), IR(32987, 23), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayNV, false, false, IR(477, 12), IR(33010, 20), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitNV, false, false, IR(457, 13), IR(33030, 21), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitWithIndexNV, false, false, IR(477, 12), IR(33051, 30), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissNV, false, false, IR(489, 6), IR(33081, 22), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectExecuteShaderNV, false, false, IR(36, 2), IR(33103, 25), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetCurrentTimeNV, true, true, IR(160, 3), IR(33128, 26), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetAttributesNV, false, false, IR(36, 2), IR(33154, 25), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetHitKindNV, true, true, IR(160, 3), IR(33179, 22), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetPrimitiveIndexNV, true, true, IR(160, 3), IR(33201, 29), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetGeometryIndexNV, true, true, IR(160, 3), IR(33230, 28), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceIdNV, true, true, IR(160, 3), IR(33258, 25), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceCustomIndexNV, true, true, IR(160, 3), IR(33283, 34), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayDirectionNV, true, true, IR(160, 3), IR(33317, 32), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayOriginNV, true, true, IR(160, 3), IR(33349, 29), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMaxNV, true, true, IR(160, 3), IR(33378, 22), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMinNV, true, true, IR(160, 3), IR(33400, 22), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsEmptyNV, true, true, IR(160, 3), IR(33422, 19), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsHitNV, true, true, IR(160, 3), IR(33441, 17), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsMissNV, true, true, IR(160, 3), IR(33458, 18), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHitObjectNV, false, false, IR(495, 3), IR(33476, 29), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHintNV, false, false, IR(36, 2), IR(33505, 24), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeHitObjectNV, true, false, IR(68, 1), IR(33529, 16), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpImageSampleFootprintNV, true, true, IR(498, 7), IR(33545, 23), IR(0, 0), IR(244, 1), IR(68, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpTypeCooperativeVectorNV, true, false, IR(89, 3), IR(33568, 24), IR(0, 0), IR(245, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeVectorMatrixMulNV, true, true, IR(505, 13), IR(33592, 29), IR(0, 0), IR(245, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorOuterProductAccumulateNV, false, false, IR(518, 7), IR(33621, 42), IR(0, 0), IR(246, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorReduceSumAccumulateNV, false, false, IR(33, 3), IR(33663, 39), IR(0, 0), IR(246, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorMatrixMulAddNV, true, true, IR(525, 16), IR(33702, 32), IR(0, 0), IR(245, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixConvertNV, true, true, IR(160, 3), IR(33734, 27), IR(0, 0), IR(247, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpEmitMeshTasksEXT, false, false, IR(541, 4), IR(33761, 17), IR(0, 0), IR(53, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSetMeshOutputsEXT, false, false, IR(36, 2), IR(33778, 18), IR(0, 0), IR(53, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpGroupNonUniformPartitionNV, true, true, IR(160, 3), IR(33796, 27), IR(0, 0), IR(178, 1), IR(71, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpWritePackedPrimitiveIndices4x8NV, false, false, IR(36, 2), IR(33823, 33), IR(0, 0), IR(50, 1), IR(18, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFetchMicroTriangleVertexPositionNV, true, true, IR(325, 7), IR(33856, 35), IR(0, 0), IR(248, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFetchMicroTriangleVertexBarycentricNV, true, true, IR(325, 7), IR(33891, 38), IR(0, 0), IR(248, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorLoadNV, true, true, IR(545, 5), IR(33929, 24), IR(0, 0), IR(245, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeVectorStoreNV, false, false, IR(550, 4), IR(33953, 25), IR(0, 0), IR(245, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpReportIntersectionKHR, true, true, IR(172, 4), IR(33978, 22), IR(99, 1), IR(54, 2), IR(165, 2), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIgnoreIntersectionNV, false, false, IR(0, 0), IR(34021, 21), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTerminateRayNV, false, false, IR(0, 0), IR(34042, 15), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceNV, false, false, IR(390, 11), IR(34057, 8), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceMotionNV, false, false, IR(477, 12), IR(34065, 14), IR(0, 0), IR(57, 1), IR(27, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceRayMotionNV, false, false, IR(477, 12), IR(34079, 17), IR(0, 0), IR(57, 1), IR(27, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTriangleVertexPositionsKHR, true, true, IR(172, 4), IR(34096, 50), IR(0, 0), IR(249, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeAccelerationStructureKHR, true, false, IR(68, 1), IR(34146, 29), IR(100, 1), IR(250, 4), IR(167, 4), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpExecuteCallableNV, false, false, IR(36, 2), IR(34203, 18), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetClusterIdNV, true, true, IR(172, 4), IR(34221, 23), IR(0, 0), IR(64, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetClusterIdNV, true, true, IR(160, 3), IR(34244, 24), IR(0, 0), IR(64, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeCooperativeMatrixNV, true, false, IR(554, 5), IR(34268, 24), IR(0, 0), IR(254, 1), IR(75, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeMatrixLoadNV, true, true, IR(559, 6), IR(34292, 24), IR(0, 0), IR(254, 1), IR(75, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixStoreNV, false, false, IR(565, 5), IR(34316, 25), IR(0, 0), IR(254, 1), IR(75, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixMulAddNV, true, true, IR(130, 5), IR(34341, 26), IR(0, 0), IR(254, 1), IR(75, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixLengthNV, true, true, IR(160, 3), IR(34367, 26), IR(0, 0), IR(254, 1), IR(75, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpBeginInvocationInterlockEXT, false, false, IR(0, 0), IR(34393, 28), IR(0, 0), IR(255, 3), IR(76, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpEndInvocationInterlockEXT, false, false, IR(0, 0), IR(34421, 26), IR(0, 0), IR(255, 3), IR(76, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixReduceNV, true, true, IR(570, 5), IR(34490, 26), IR(0, 0), IR(258, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpCooperativeMatrixLoadTensorNV, true, true, IR(575, 7), IR(34591, 30), IR(0, 0), IR(195, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixStoreTensorNV, false, false, IR(582, 5), IR(34621, 31), IR(0, 0), IR(195, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixPerElementOpNV, true, true, IR(151, 5), IR(34652, 32), IR(0, 0), IR(259, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpTypeTensorLayoutNV, true, false, IR(89, 3), IR(34684, 19), IR(0, 0), IR(260, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeTensorViewNV, true, false, IR(587, 4), IR(34703, 17), IR(0, 0), IR(260, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCreateTensorLayoutNV, true, true, IR(39, 2), IR(34720, 21), IR(0, 0), IR(260, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetDimensionNV, true, true, IR(122, 4), IR(34741, 27), IR(0, 0), IR(260, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetStrideNV, true, true, IR(122, 4), IR(34768, 24), IR(0, 0), IR(260, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSliceNV, true, true, IR(122, 4), IR(34792, 20), IR(0, 0), IR(260, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetClampValueNV, true, true, IR(172, 4), IR(34812, 28), IR(0, 0), IR(260, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCreateTensorViewNV, true, true, IR(39, 2), IR(34840, 19), IR(0, 0), IR(260, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetDimensionNV, true, true, IR(122, 4), IR(34859, 25), IR(0, 0), IR(260, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetStrideNV, true, true, IR(122, 4), IR(34884, 22), IR(0, 0), IR(260, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpDemoteToHelperInvocation, false, false, IR(0, 0), IR(11258, 25), IR(45, 1), IR(261, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpIsHelperInvocationEXT, true, true, IR(39, 2), IR(34906, 22), IR(0, 0), IR(261, 1), IR(77, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetClipNV, true, true, IR(325, 7), IR(34928, 20), IR(0, 0), IR(260, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetBlockSizeNV, true, true, IR(122, 4), IR(34948, 27), IR(0, 0), IR(260, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixTransposeNV, true, true, IR(160, 3), IR(34975, 29), IR(0, 0), IR(247, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToImageNV, true, true, IR(160, 3), IR(35004, 18), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToSamplerNV, true, true, IR(160, 3), IR(35022, 20), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertImageToUNV, true, true, IR(160, 3), IR(35042, 18), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertSamplerToUNV, true, true, IR(160, 3), IR(35060, 20), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToSampledImageNV, true, true, IR(160, 3), IR(35080, 25), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertSampledImageToUNV, true, true, IR(160, 3), IR(35105, 25), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSamplerImageAddressingModeNV, false, false, IR(0, 1), IR(35130, 29), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRawAccessChainNV, true, true, IR(591, 7), IR(35211, 17), IR(0, 0), IR(184, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpRayQueryGetIntersectionSpherePositionNV, true, true, IR(172, 4), IR(35228, 40), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionSphereRadiusNV, true, true, IR(172, 4), IR(35268, 38), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSPositionsNV, true, true, IR(172, 4), IR(35306, 38), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSRadiiNV, true, true, IR(172, 4), IR(35344, 34), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSHitValueNV, true, true, IR(172, 4), IR(35378, 37), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetSpherePositionNV, true, true, IR(160, 3), IR(35415, 29), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetSphereRadiusNV, true, true, IR(160, 3), IR(35444, 27), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetLSSPositionsNV, true, true, IR(160, 3), IR(35471, 27), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetLSSRadiiNV, true, true, IR(160, 3), IR(35498, 23), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsSphereHitNV, true, true, IR(160, 3), IR(35521, 23), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsLSSHitNV, true, true, IR(160, 3), IR(35544, 20), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryIsSphereHitNV, true, true, IR(172, 4), IR(35564, 22), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryIsLSSHitNV, true, true, IR(172, 4), IR(35586, 19), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSubgroupShuffleINTEL, true, true, IR(172, 4), IR(11706, 21), IR(0, 0), IR(262, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleDownINTEL, true, true, IR(130, 5), IR(35605, 25), IR(0, 0), IR(262, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleUpINTEL, true, true, IR(130, 5), IR(35630, 23), IR(0, 0), IR(262, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleXorINTEL, true, true, IR(172, 4), IR(35653, 24), IR(0, 0), IR(262, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupBlockReadINTEL, true, true, IR(160, 3), IR(35677, 23), IR(0, 0), IR(263, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupBlockWriteINTEL, false, false, IR(36, 2), IR(35700, 24), IR(0, 0), IR(263, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageBlockReadINTEL, true, true, IR(172, 4), IR(35724, 28), IR(0, 0), IR(264, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageBlockWriteINTEL, false, false, IR(33, 3), IR(35752, 29), IR(0, 0), IR(264, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageMediaBlockReadINTEL, true, true, IR(215, 6), IR(35781, 33), IR(0, 0), IR(265, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageMediaBlockWriteINTEL, false, false, IR(598, 5), IR(35814, 34), IR(0, 0), IR(265, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpUCountLeadingZerosINTEL, true, true, IR(160, 3), IR(35848, 24), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUCountTrailingZerosINTEL, true, true, IR(160, 3), IR(35872, 25), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAbsISubINTEL, true, true, IR(172, 4), IR(35897, 13), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAbsUSubINTEL, true, true, IR(172, 4), IR(35910, 13), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAddSatINTEL, true, true, IR(172, 4), IR(35923, 13), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAddSatINTEL, true, true, IR(172, 4), IR(35936, 13), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAverageINTEL, true, true, IR(172, 4), IR(35949, 14), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAverageINTEL, true, true, IR(172, 4), IR(35963, 14), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAverageRoundedINTEL, true, true, IR(172, 4), IR(35977, 21), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAverageRoundedINTEL, true, true, IR(172, 4), IR(35998, 21), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpISubSatINTEL, true, true, IR(172, 4), IR(36019, 13), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUSubSatINTEL, true, true, IR(172, 4), IR(36032, 13), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIMul32x16INTEL, true, true, IR(172, 4), IR(36045, 15), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUMul32x16INTEL, true, true, IR(172, 4), IR(36060, 15), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConstantFunctionPointerINTEL, true, true, IR(160, 3), IR(36075, 29), IR(0, 0), IR(193, 1), IR(91, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFunctionPointerCallINTEL, true, true, IR(107, 3), IR(36104, 25), IR(0, 0), IR(193, 1), IR(91, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmTargetINTEL, true, false, IR(50, 2), IR(36129, 15), IR(0, 0), IR(123, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmINTEL, true, true, IR(603, 6), IR(11924, 9), IR(0, 0), IR(123, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmCallINTEL, true, true, IR(122, 4), IR(36144, 13), IR(0, 0), IR(123, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAtomicFMinEXT, true, true, IR(235, 6), IR(36157, 14), IR(0, 0), IR(267, 4), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicFMaxEXT, true, true, IR(235, 6), IR(36171, 14), IR(0, 0), IR(267, 4), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAssumeTrueKHR, false, false, IR(10, 1), IR(36185, 14), IR(0, 0), IR(271, 1), IR(95, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpExpectKHR, true, true, IR(172, 4), IR(36199, 10), IR(0, 0), IR(271, 1), IR(95, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpDecorateString, false, false, IR(163, 2), IR(36209, 15), IR(101, 1), IR(1, 0), IR(171, 2), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpMemberDecorateString, false, false, IR(165, 3), IR(36245, 21), IR(102, 1), IR(1, 0), IR(171, 2), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpVmeImageINTEL, true, true, IR(172, 4), IR(36293, 14), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeVmeImageINTEL, true, false, IR(87, 2), IR(36307, 18), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImePayloadINTEL, true, false, IR(68, 1), IR(36325, 23), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcRefPayloadINTEL, true, false, IR(68, 1), IR(36348, 23), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcSicPayloadINTEL, true, false, IR(68, 1), IR(36371, 23), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcMcePayloadINTEL, true, false, IR(68, 1), IR(36394, 23), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcMceResultINTEL, true, false, IR(68, 1), IR(36417, 22), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultINTEL, true, false, IR(68, 1), IR(36439, 22), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultSingleReferenceStreamoutINTEL, true, false, IR(68, 1), IR(36461, 46), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultDualReferenceStreamoutINTEL, true, false, IR(68, 1), IR(36507, 44), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeSingleReferenceStreaminINTEL, true, false, IR(68, 1), IR(36551, 39), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeDualReferenceStreaminINTEL, true, false, IR(68, 1), IR(36590, 37), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcRefResultINTEL, true, false, IR(68, 1), IR(36627, 22), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcSicResultINTEL, true, false, IR(68, 1), IR(36649, 22), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL, true, true, IR(172, 4), IR(36671, 60), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL, true, true, IR(172, 4), IR(36731, 53), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterShapePenaltyINTEL, true, true, IR(172, 4), IR(36784, 47), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterShapePenaltyINTEL, true, true, IR(172, 4), IR(36831, 40), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL, true, true, IR(172, 4), IR(36871, 51), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterDirectionPenaltyINTEL, true, true, IR(172, 4), IR(36922, 44), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL, true, true, IR(172, 4), IR(36966, 51), IR(0, 0), IR(273, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL, true, true, IR(172, 4), IR(37017, 56), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL, true, true, IR(39, 2), IR(37073, 50), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL, true, true, IR(39, 2), IR(37123, 52), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL, true, true, IR(39, 2), IR(37175, 49), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetMotionVectorCostFunctionINTEL, true, true, IR(215, 6), IR(37224, 47), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL, true, true, IR(172, 4), IR(37271, 50), IR(0, 0), IR(273, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL, true, true, IR(39, 2), IR(37321, 51), IR(0, 0), IR(273, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL, true, true, IR(39, 2), IR(37372, 56), IR(0, 0), IR(275, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetAcOnlyHaarINTEL, true, true, IR(160, 3), IR(37428, 33), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL, true, true, IR(172, 4), IR(37461, 52), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL, true, true, IR(172, 4), IR(37513, 61), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL, true, true, IR(130, 5), IR(37574, 61), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToImePayloadINTEL, true, true, IR(160, 3), IR(37635, 39), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToImeResultINTEL, true, true, IR(160, 3), IR(37674, 38), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToRefPayloadINTEL, true, true, IR(160, 3), IR(37712, 39), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToRefResultINTEL, true, true, IR(160, 3), IR(37751, 38), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToSicPayloadINTEL, true, true, IR(160, 3), IR(37789, 39), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToSicResultINTEL, true, true, IR(160, 3), IR(37828, 38), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetMotionVectorsINTEL, true, true, IR(160, 3), IR(37866, 36), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterDistortionsINTEL, true, true, IR(160, 3), IR(37902, 39), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetBestInterDistortionsINTEL, true, true, IR(160, 3), IR(37941, 43), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMajorShapeINTEL, true, true, IR(160, 3), IR(37984, 38), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMinorShapeINTEL, true, true, IR(160, 3), IR(38022, 38), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterDirectionsINTEL, true, true, IR(160, 3), IR(38060, 38), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMotionVectorCountINTEL, true, true, IR(160, 3), IR(38098, 45), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterReferenceIdsINTEL, true, true, IR(160, 3), IR(38143, 40), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL, true, true, IR(130, 5), IR(38183, 62), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeInitializeINTEL, true, true, IR(130, 5), IR(38245, 30), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetSingleReferenceINTEL, true, true, IR(130, 5), IR(38275, 38), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetDualReferenceINTEL, true, true, IR(215, 6), IR(38313, 36), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeRefWindowSizeINTEL, true, true, IR(172, 4), IR(38349, 33), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeAdjustRefOffsetINTEL, true, true, IR(215, 6), IR(38382, 35), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(38417, 39), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetMaxMotionVectorCountINTEL, true, true, IR(172, 4), IR(38456, 43), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetUnidirectionalMixDisableINTEL, true, true, IR(160, 3), IR(38499, 47), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetEarlySearchTerminationThresholdINTEL, true, true, IR(172, 4), IR(38546, 54), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetWeightedSadINTEL, true, true, IR(172, 4), IR(38600, 34), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(38634, 47), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(38681, 45), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL, true, true, IR(215, 6), IR(38726, 55), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL, true, true, IR(325, 7), IR(38781, 53), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL, true, true, IR(130, 5), IR(38834, 56), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL, true, true, IR(215, 6), IR(38890, 54), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL, true, true, IR(215, 6), IR(38944, 58), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL, true, true, IR(325, 7), IR(39002, 56), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeConvertToMceResultINTEL, true, true, IR(160, 3), IR(39058, 38), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetSingleReferenceStreaminINTEL, true, true, IR(160, 3), IR(39096, 46), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetDualReferenceStreaminINTEL, true, true, IR(160, 3), IR(39142, 44), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeStripSingleReferenceStreamoutINTEL, true, true, IR(160, 3), IR(39186, 49), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeStripDualReferenceStreamoutINTEL, true, true, IR(160, 3), IR(39235, 47), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL, true, true, IR(172, 4), IR(39282, 70), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL, true, true, IR(172, 4), IR(39352, 68), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL, true, true, IR(172, 4), IR(39420, 69), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL, true, true, IR(130, 5), IR(39489, 68), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL, true, true, IR(130, 5), IR(39557, 66), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL, true, true, IR(130, 5), IR(39623, 67), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetBorderReachedINTEL, true, true, IR(172, 4), IR(39690, 36), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetTruncatedSearchIndicationINTEL, true, true, IR(160, 3), IR(39726, 48), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL, true, true, IR(160, 3), IR(39774, 59), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL, true, true, IR(160, 3), IR(39833, 58), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL, true, true, IR(160, 3), IR(39891, 56), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcFmeInitializeINTEL, true, true, IR(609, 9), IR(39947, 30), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcBmeInitializeINTEL, true, true, IR(618, 10), IR(39977, 30), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(40007, 39), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefSetBidirectionalMixDisableINTEL, true, true, IR(160, 3), IR(40046, 46), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefSetBilinearFilterEnableINTEL, true, true, IR(160, 3), IR(40092, 43), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(40135, 47), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(40182, 45), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithMultiReferenceINTEL, true, true, IR(130, 5), IR(40227, 46), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL, true, true, IR(215, 6), IR(40273, 56), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefConvertToMceResultINTEL, true, true, IR(160, 3), IR(40329, 38), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicInitializeINTEL, true, true, IR(160, 3), IR(40367, 30), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureSkcINTEL, true, true, IR(288, 8), IR(40397, 32), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureIpeLumaINTEL, true, true, IR(618, 10), IR(40429, 36), IR(0, 0), IR(273, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureIpeLumaChromaINTEL, true, true, IR(628, 13), IR(40465, 42), IR(0, 0), IR(275, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetMotionVectorMaskINTEL, true, true, IR(172, 4), IR(40507, 39), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(40546, 39), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraLumaShapePenaltyINTEL, true, true, IR(172, 4), IR(40585, 44), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraLumaModeCostFunctionINTEL, true, true, IR(215, 6), IR(40629, 48), IR(0, 0), IR(273, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraChromaModeCostFunctionINTEL, true, true, IR(172, 4), IR(40677, 50), IR(0, 0), IR(275, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetBilinearFilterEnableINTEL, true, true, IR(160, 3), IR(40727, 43), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetSkcForwardTransformEnableINTEL, true, true, IR(172, 4), IR(40770, 48), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetBlockBasedRawSkipSadINTEL, true, true, IR(172, 4), IR(40818, 43), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateIpeINTEL, true, true, IR(172, 4), IR(40861, 31), IR(0, 0), IR(273, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(40892, 47), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(40939, 45), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithMultiReferenceINTEL, true, true, IR(130, 5), IR(40984, 46), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL, true, true, IR(215, 6), IR(41030, 56), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConvertToMceResultINTEL, true, true, IR(160, 3), IR(41086, 38), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetIpeLumaShapeINTEL, true, true, IR(160, 3), IR(41124, 35), IR(0, 0), IR(273, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetBestIpeLumaDistortionINTEL, true, true, IR(160, 3), IR(41159, 44), IR(0, 0), IR(273, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetBestIpeChromaDistortionINTEL, true, true, IR(160, 3), IR(41203, 46), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedIpeLumaModesINTEL, true, true, IR(160, 3), IR(41249, 41), IR(0, 0), IR(273, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetIpeChromaModeINTEL, true, true, IR(160, 3), IR(41290, 36), IR(0, 0), IR(275, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL, true, true, IR(160, 3), IR(41326, 50), IR(0, 0), IR(273, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL, true, true, IR(160, 3), IR(41376, 48), IR(0, 0), IR(273, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetInterRawSadsINTEL, true, true, IR(160, 3), IR(41424, 35), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpVariableLengthArrayINTEL, true, true, IR(160, 3), IR(12162, 25), IR(0, 0), IR(277, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSaveMemoryINTEL, true, true, IR(39, 2), IR(41459, 16), IR(0, 0), IR(277, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpRestoreMemoryINTEL, false, false, IR(10, 1), IR(41475, 19), IR(0, 0), IR(277, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinCosPiINTEL, true, true, IR(641, 8), IR(41494, 28), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastINTEL, true, true, IR(641, 8), IR(41522, 24), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastFromIntINTEL, true, true, IR(641, 8), IR(41546, 31), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastToIntINTEL, true, true, IR(641, 8), IR(41577, 29), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatAddINTEL, true, true, IR(649, 10), IR(41606, 23), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSubINTEL, true, true, IR(649, 10), IR(41629, 23), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatMulINTEL, true, true, IR(649, 10), IR(41652, 23), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatDivINTEL, true, true, IR(649, 10), IR(41675, 23), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatGTINTEL, true, true, IR(659, 6), IR(41698, 22), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatGEINTEL, true, true, IR(659, 6), IR(41720, 22), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLTINTEL, true, true, IR(659, 6), IR(41742, 22), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLEINTEL, true, true, IR(659, 6), IR(41764, 22), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatEQINTEL, true, true, IR(659, 6), IR(41786, 22), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatRecipINTEL, true, true, IR(641, 8), IR(41808, 25), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatRSqrtINTEL, true, true, IR(641, 8), IR(41833, 25), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCbrtINTEL, true, true, IR(641, 8), IR(41858, 24), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatHypotINTEL, true, true, IR(649, 10), IR(41882, 25), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSqrtINTEL, true, true, IR(641, 8), IR(41907, 24), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLogINTEL, true, true, IR(641, 8), IR(41931, 23), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog2INTEL, true, true, IR(641, 8), IR(41954, 24), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog10INTEL, true, true, IR(641, 8), IR(41978, 25), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog1pINTEL, true, true, IR(641, 8), IR(42003, 25), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExpINTEL, true, true, IR(641, 8), IR(42028, 23), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExp2INTEL, true, true, IR(641, 8), IR(42051, 24), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExp10INTEL, true, true, IR(641, 8), IR(42075, 25), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExpm1INTEL, true, true, IR(641, 8), IR(42100, 25), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinINTEL, true, true, IR(641, 8), IR(42125, 23), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCosINTEL, true, true, IR(641, 8), IR(42148, 23), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinCosINTEL, true, true, IR(641, 8), IR(42171, 26), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinPiINTEL, true, true, IR(641, 8), IR(42197, 25), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCosPiINTEL, true, true, IR(641, 8), IR(42222, 25), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatASinINTEL, true, true, IR(641, 8), IR(42247, 24), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatASinPiINTEL, true, true, IR(641, 8), IR(42271, 26), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatACosINTEL, true, true, IR(641, 8), IR(42297, 24), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatACosPiINTEL, true, true, IR(641, 8), IR(42321, 26), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATanINTEL, true, true, IR(641, 8), IR(42347, 24), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATanPiINTEL, true, true, IR(641, 8), IR(42371, 26), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATan2INTEL, true, true, IR(649, 10), IR(42397, 25), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowINTEL, true, true, IR(649, 10), IR(42422, 23), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowRINTEL, true, true, IR(649, 10), IR(42445, 24), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowNINTEL, true, true, IR(649, 10), IR(42469, 24), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpLoopControlINTEL, false, false, IR(18, 1), IR(42493, 17), IR(0, 0), IR(279, 1), IR(102, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAliasDomainDeclINTEL, true, false, IR(665, 2), IR(42510, 21), IR(0, 0), IR(129, 1), IR(109, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAliasScopeDeclINTEL, true, false, IR(667, 3), IR(42531, 20), IR(0, 0), IR(129, 1), IR(109, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAliasScopeListDeclINTEL, true, false, IR(92, 2), IR(42551, 24), IR(0, 0), IR(129, 1), IR(109, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSqrtINTEL, true, true, IR(641, 8), IR(42575, 15), IR(0, 0), IR(183, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedRecipINTEL, true, true, IR(641, 8), IR(42590, 16), IR(0, 0), IR(183, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedRsqrtINTEL, true, true, IR(641, 8), IR(42606, 16), IR(0, 0), IR(183, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinINTEL, true, true, IR(641, 8), IR(42622, 14), IR(0, 0), IR(183, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedCosINTEL, true, true, IR(641, 8), IR(42636, 14), IR(0, 0), IR(183, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinCosINTEL, true, true, IR(641, 8), IR(42650, 17), IR(0, 0), IR(183, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinPiINTEL, true, true, IR(641, 8), IR(42667, 16), IR(0, 0), IR(183, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedCosPiINTEL, true, true, IR(641, 8), IR(42683, 16), IR(0, 0), IR(183, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinCosPiINTEL, true, true, IR(641, 8), IR(42699, 19), IR(0, 0), IR(183, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedLogINTEL, true, true, IR(641, 8), IR(42718, 14), IR(0, 0), IR(183, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedExpINTEL, true, true, IR(641, 8), IR(42732, 14), IR(0, 0), IR(183, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpPtrCastToCrossWorkgroupINTEL, true, true, IR(160, 3), IR(42746, 29), IR(0, 0), IR(194, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpCrossWorkgroupCastToPtrINTEL, true, true, IR(160, 3), IR(42775, 29), IR(0, 0), IR(194, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpReadPipeBlockingINTEL, true, true, IR(172, 4), IR(42804, 22), IR(0, 0), IR(280, 1), IR(116, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpWritePipeBlockingINTEL, true, true, IR(172, 4), IR(42826, 23), IR(0, 0), IR(280, 1), IR(116, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpFPGARegINTEL, true, true, IR(160, 3), IR(12721, 13), IR(0, 0), IR(281, 1), IR(117, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetRayTMinKHR, true, true, IR(160, 3), IR(42849, 22), IR(0, 0), IR(187, 1), IR(45, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetRayFlagsKHR, true, true, IR(160, 3), IR(42871, 23), IR(0, 0), IR(187, 1), IR(45, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTKHR, true, true, IR(172, 4), IR(42894, 28), IR(0, 0), IR(187, 1), IR(45, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceCustomIndexKHR, true, true, IR(172, 4), IR(42922, 46), IR(0, 0), IR(187, 1), IR(45, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceIdKHR, true, true, IR(172, 4), IR(42968, 37), IR(0, 0), IR(187, 1), IR(45, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR, true, true, IR(172, 4), IR(43005, 65), IR(0, 0), IR(187, 1), IR(45, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionGeometryIndexKHR, true, true, IR(172, 4), IR(43070, 40), IR(0, 0), IR(187, 1), IR(45, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionPrimitiveIndexKHR, true, true, IR(172, 4), IR(43110, 41), IR(0, 0), IR(187, 1), IR(45, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionBarycentricsKHR, true, true, IR(172, 4), IR(43151, 39), IR(0, 0), IR(187, 1), IR(45, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionFrontFaceKHR, true, true, IR(172, 4), IR(43190, 36), IR(0, 0), IR(187, 1), IR(45, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionCandidateAABBOpaqueKHR, true, true, IR(160, 3), IR(43226, 46), IR(0, 0), IR(187, 1), IR(45, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectRayDirectionKHR, true, true, IR(172, 4), IR(43272, 45), IR(0, 0), IR(187, 1), IR(45, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectRayOriginKHR, true, true, IR(172, 4), IR(43317, 42), IR(0, 0), IR(187, 1), IR(45, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetWorldRayDirectionKHR, true, true, IR(160, 3), IR(43359, 32), IR(0, 0), IR(187, 1), IR(45, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetWorldRayOriginKHR, true, true, IR(160, 3), IR(43391, 29), IR(0, 0), IR(187, 1), IR(45, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectToWorldKHR, true, true, IR(172, 4), IR(43420, 40), IR(0, 0), IR(187, 1), IR(45, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionWorldToObjectKHR, true, true, IR(172, 4), IR(43460, 40), IR(0, 0), IR(187, 1), IR(45, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAtomicFAddEXT, true, true, IR(235, 6), IR(43500, 14), IR(0, 0), IR(282, 4), IR(124, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpTypeBufferSurfaceINTEL, true, false, IR(100, 2), IR(43514, 23), IR(0, 0), IR(121, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeStructContinuedINTEL, false, false, IR(670, 1), IR(43537, 25), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantCompositeContinuedINTEL, false, false, IR(670, 1), IR(43562, 32), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCompositeContinuedINTEL, false, false, IR(670, 1), IR(43594, 36), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpCompositeConstructContinuedINTEL, true, true, IR(107, 3), IR(43630, 33), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpConvertFToBF16INTEL, true, true, IR(160, 3), IR(43663, 20), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertBF16ToFINTEL, true, true, IR(160, 3), IR(43683, 20), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpControlBarrierArriveINTEL, false, false, IR(221, 3), IR(43703, 26), IR(0, 0), IR(288, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpControlBarrierWaitINTEL, false, false, IR(221, 3), IR(43729, 24), IR(0, 0), IR(288, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpArithmeticFenceEXT, true, true, IR(160, 3), IR(13153, 19), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpTaskSequenceCreateINTEL, true, true, IR(671, 7), IR(43753, 24), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTaskSequenceAsyncINTEL, false, false, IR(168, 2), IR(43777, 23), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTaskSequenceGetINTEL, true, true, IR(160, 3), IR(43800, 21), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTaskSequenceReleaseINTEL, false, false, IR(10, 1), IR(43821, 25), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeTaskSequenceINTEL, true, false, IR(68, 1), IR(43846, 22), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpSubgroupBlockPrefetchINTEL, false, false, IR(139, 3), IR(43868, 27), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadINTEL, false, false, IR(678, 10), IR(43895, 25), IR(0, 0), IR(105, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadTransformINTEL, false, false, IR(678, 10), IR(43920, 34), IR(0, 0), IR(292, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadTransposeINTEL, false, false, IR(678, 10), IR(43954, 34), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockPrefetchINTEL, false, false, IR(688, 9), IR(43988, 29), IR(0, 0), IR(105, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockStoreINTEL, false, false, IR(678, 10), IR(44017, 26), IR(0, 0), IR(105, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupMatrixMultiplyAccumulateINTEL, true, true, IR(697, 7), IR(13491, 38), IR(0, 0), IR(294, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpBitwiseFunctionINTEL, true, true, IR(215, 6), IR(44105, 21), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpGroupIMulKHR, true, true, IR(283, 5), IR(44126, 13), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMulKHR, true, true, IR(283, 5), IR(44139, 13), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseAndKHR, true, true, IR(283, 5), IR(44152, 19), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseOrKHR, true, true, IR(283, 5), IR(44171, 18), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseXorKHR, true, true, IR(283, 5), IR(44189, 19), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalAndKHR, true, true, IR(283, 5), IR(44208, 19), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalOrKHR, true, true, IR(283, 5), IR(44227, 18), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalXorKHR, true, true, IR(283, 5), IR(44245, 19), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpRoundFToTF32INTEL, true, true, IR(160, 3), IR(44264, 18), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpMaskedGatherINTEL, true, true, IR(704, 6), IR(44282, 18), IR(0, 0), IR(298, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpMaskedScatterINTEL, false, false, IR(710, 4), IR(44300, 19), IR(0, 0), IR(298, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
}};

// Opcode strings (without the 'Op' prefix) and opcode values, ordered by name.
// The fields in order are:
//   name, either the primary name or an alias, indexing into kStrings
//   index into kInstructionDesc
static const std::array<NameIndex, 805> kInstructionNames{{
  {IR(35897, 13), 537}, // 0 AbsISubINTEL
  {IR(35910, 13), 538}, // 1 AbsUSubINTEL
  {IR(26069, 12), 58}, // 2 AccessChain
  {IR(42510, 21), 723}, // 3 AliasDomainDeclINTEL
  {IR(42531, 20), 724}, // 4 AliasScopeDeclINTEL
  {IR(42551, 24), 725}, // 5 AliasScopeListDeclINTEL
  {IR(27366, 4), 143}, // 6 All
  {IR(32421, 25), 409}, // 7 AllocateNodePayloadsAMDX
  {IR(27362, 4), 142}, // 8 Any
  {IR(42297, 24), 714}, // 9 ArbitraryFloatACosINTEL
  {IR(42321, 26), 715}, // 10 ArbitraryFloatACosPiINTEL
  {IR(42247, 24), 712}, // 11 ArbitraryFloatASinINTEL
  {IR(42271, 26), 713}, // 12 ArbitraryFloatASinPiINTEL
  {IR(42397, 25), 718}, // 13 ArbitraryFloatATan2INTEL
  {IR(42347, 24), 716}, // 14 ArbitraryFloatATanINTEL
  {IR(42371, 26), 717}, // 15 ArbitraryFloatATanPiINTEL
  {IR(41606, 23), 685}, // 16 ArbitraryFloatAddINTEL
  {IR(41546, 31), 683}, // 17 ArbitraryFloatCastFromIntINTEL
  {IR(41522, 24), 682}, // 18 ArbitraryFloatCastINTEL
  {IR(41577, 29), 684}, // 19 ArbitraryFloatCastToIntINTEL
  {IR(41858, 24), 696}, // 20 ArbitraryFloatCbrtINTEL
  {IR(42148, 23), 708}, // 21 ArbitraryFloatCosINTEL
  {IR(42222, 25), 711}, // 22 ArbitraryFloatCosPiINTEL
  {IR(41675, 23), 688}, // 23 ArbitraryFloatDivINTEL
  {IR(41786, 22), 693}, // 24 ArbitraryFloatEQINTEL
  {IR(42075, 25), 705}, // 25 ArbitraryFloatExp10INTEL
  {IR(42051, 24), 704}, // 26 ArbitraryFloatExp2INTEL
  {IR(42028, 23), 703}, // 27 ArbitraryFloatExpINTEL
  {IR(42100, 25), 706}, // 28 ArbitraryFloatExpm1INTEL
  {IR(41720, 22), 690}, // 29 ArbitraryFloatGEINTEL
  {IR(41698, 22), 689}, // 30 ArbitraryFloatGTINTEL
  {IR(41882, 25), 697}, // 31 ArbitraryFloatHypotINTEL
  {IR(41764, 22), 692}, // 32 ArbitraryFloatLEINTEL
  {IR(41742, 22), 691}, // 33 ArbitraryFloatLTINTEL
  {IR(41978, 25), 701}, // 34 ArbitraryFloatLog10INTEL
  {IR(42003, 25), 702}, // 35 ArbitraryFloatLog1pINTEL
  {IR(41954, 24), 700}, // 36 ArbitraryFloatLog2INTEL
  {IR(41931, 23), 699}, // 37 ArbitraryFloatLogINTEL
  {IR(41652, 23), 687}, // 38 ArbitraryFloatMulINTEL
  {IR(42422, 23), 719}, // 39 ArbitraryFloatPowINTEL
  {IR(42469, 24), 721}, // 40 ArbitraryFloatPowNINTEL
  {IR(42445, 24), 720}, // 41 ArbitraryFloatPowRINTEL
  {IR(41833, 25), 695}, // 42 ArbitraryFloatRSqrtINTEL
  {IR(41808, 25), 694}, // 43 ArbitraryFloatRecipINTEL
  {IR(42171, 26), 709}, // 44 ArbitraryFloatSinCosINTEL
  {IR(41494, 28), 681}, // 45 ArbitraryFloatSinCosPiINTEL
  {IR(42125, 23), 707}, // 46 ArbitraryFloatSinINTEL
  {IR(42197, 25), 710}, // 47 ArbitraryFloatSinPiINTEL
  {IR(41907, 24), 698}, // 48 ArbitraryFloatSqrtINTEL
  {IR(41629, 23), 686}, // 49 ArbitraryFloatSubINTEL
  {IR(13153, 19), 769}, // 50 ArithmeticFenceEXT
  {IR(26116, 12), 61}, // 51 ArrayLength
  {IR(36144, 13), 553}, // 52 AsmCallINTEL
  {IR(11924, 9), 552}, // 53 AsmINTEL
  {IR(36129, 15), 551}, // 54 AsmTargetINTEL
  {IR(36185, 14), 556}, // 55 AssumeTrueKHR
  {IR(28388, 10), 220}, // 56 AtomicAnd
  {IR(28240, 22), 210}, // 57 AtomicCompareExchange
  {IR(28262, 26), 211}, // 58 AtomicCompareExchangeWeak
  {IR(28225, 15), 209}, // 59 AtomicExchange
  {IR(43500, 14), 759}, // 60 AtomicFAddEXT
  {IR(36171, 14), 555}, // 61 AtomicFMaxEXT
  {IR(36157, 14), 554}, // 62 AtomicFMinEXT
  {IR(29773, 16), 292}, // 63 AtomicFlagClear
  {IR(29752, 21), 291}, // 64 AtomicFlagTestAndSet
  {IR(28322, 11), 214}, // 65 AtomicIAdd
  {IR(28305, 17), 213}, // 66 AtomicIDecrement
  {IR(28288, 17), 212}, // 67 AtomicIIncrement
  {IR(28333, 11), 215}, // 68 AtomicISub
  {IR(28202, 11), 207}, // 69 AtomicLoad
  {IR(28398, 9), 221}, // 70 AtomicOr
  {IR(28366, 11), 218}, // 71 AtomicSMax
  {IR(28344, 11), 216}, // 72 AtomicSMin
  {IR(28213, 12), 208}, // 73 AtomicStore
  {IR(28377, 11), 219}, // 74 AtomicUMax
  {IR(28355, 11), 217}, // 75 AtomicUMin
  {IR(28407, 10), 222}, // 76 AtomicXor
  {IR(34393, 28), 483}, // 77 BeginInvocationInterlockEXT
  {IR(27986, 9), 191}, // 78 BitCount
  {IR(27926, 15), 187}, // 79 BitFieldInsert
  {IR(27941, 17), 188}, // 80 BitFieldSExtract
  {IR(27958, 17), 189}, // 81 BitFieldUExtract
  {IR(27975, 11), 190}, // 82 BitReverse
  {IR(27114, 8), 114}, // 83 Bitcast
  {IR(27911, 11), 185}, // 84 BitwiseAnd
  {IR(44105, 21), 782}, // 85 BitwiseFunctionINTEL
  {IR(27890, 10), 183}, // 86 BitwiseOr
  {IR(27900, 11), 184}, // 87 BitwiseXor
  {IR(28517, 7), 227}, // 88 Branch
  {IR(28524, 18), 228}, // 89 BranchConditional
  {IR(29385, 13), 277}, // 90 BuildNDRange
  {IR(25130, 11), 15}, // 91 Capability
  {IR(29343, 26), 275}, // 92 CaptureEventProfilingInfo
  {IR(30849, 23), 344}, // 93 ColorAttachmentReadEXT
  {IR(28935, 15), 255}, // 94 CommitReadPipe
  {IR(28950, 16), 256}, // 95 CommitWritePipe
  {IR(26376, 19), 72}, // 96 CompositeConstruct
  {IR(43630, 33), 764}, // 97 CompositeConstructContinuedINTEL
  {IR(31778, 31), 382}, // 98 CompositeConstructReplicateEXT
  {IR(26395, 17), 73}, // 99 CompositeExtract
  {IR(26412, 16), 74}, // 100 CompositeInsert
  {IR(15052, 9), 39}, // 101 Constant
  {IR(25636, 18), 40}, // 102 ConstantComposite
  {IR(43562, 32), 762}, // 103 ConstantCompositeContinuedINTEL
  {IR(31714, 30), 380}, // 104 ConstantCompositeReplicateEXT
  {IR(25584, 14), 38}, // 105 ConstantFalse
  {IR(36075, 29), 549}, // 106 ConstantFunctionPointerINTEL
  {IR(25748, 13), 42}, // 107 ConstantNull
  {IR(29828, 20), 296}, // 108 ConstantPipeStorage
  {IR(25732, 16), 41}, // 109 ConstantSampler
  {IR(32574, 19), 415}, // 110 ConstantStringAMDX
  {IR(25571, 13), 37}, // 111 ConstantTrue
  {IR(28173, 15), 205}, // 112 ControlBarrier
  {IR(43703, 26), 767}, // 113 ControlBarrierArriveINTEL
  {IR(43729, 24), 768}, // 114 ControlBarrierWaitINTEL
  {IR(43683, 20), 766}, // 115 ConvertBF16ToFINTEL
  {IR(43663, 20), 765}, // 116 ConvertFToBF16INTEL
  {IR(26920, 12), 100}, // 117 ConvertFToS
  {IR(26908, 12), 99}, // 118 ConvertFToU
  {IR(35042, 18), 506}, // 119 ConvertImageToUNV
  {IR(26997, 14), 107}, // 120 ConvertPtrToU
  {IR(26932, 12), 101}, // 121 ConvertSToF
  {IR(35105, 25), 509}, // 122 ConvertSampledImageToUNV
  {IR(35060, 20), 507}, // 123 ConvertSamplerToUNV
  {IR(31292, 35), 366}, // 124 ConvertUToAccelerationStructureKHR
  {IR(26944, 12), 102}, // 125 ConvertUToF
  {IR(35004, 18), 504}, // 126 ConvertUToImageNV
  {IR(27041, 14), 110}, // 127 ConvertUToPtr
  {IR(35080, 25), 508}, // 128 ConvertUToSampledImageNV
  {IR(35022, 20), 505}, // 129 ConvertUToSamplerNV
  {IR(33734, 27), 458}, // 130 CooperativeMatrixConvertNV
  {IR(31687, 27), 379}, // 131 CooperativeMatrixLengthKHR
  {IR(34367, 26), 482}, // 132 CooperativeMatrixLengthNV
  {IR(31555, 25), 376}, // 133 CooperativeMatrixLoadKHR
  {IR(34292, 24), 479}, // 134 CooperativeMatrixLoadNV
  {IR(34591, 30), 486}, // 135 CooperativeMatrixLoadTensorNV
  {IR(31660, 27), 378}, // 136 CooperativeMatrixMulAddKHR
  {IR(34341, 26), 481}, // 137 CooperativeMatrixMulAddNV
  {IR(34652, 32), 488}, // 138 CooperativeMatrixPerElementOpNV
  {IR(34490, 26), 485}, // 139 CooperativeMatrixReduceNV
  {IR(31580, 26), 377}, // 140 CooperativeMatrixStoreKHR
  {IR(34316, 25), 480}, // 141 CooperativeMatrixStoreNV
  {IR(34621, 31), 487}, // 142 CooperativeMatrixStoreTensorNV
  {IR(34975, 29), 503}, // 143 CooperativeMatrixTransposeNV
  {IR(33929, 24), 465}, // 144 CooperativeVectorLoadNV
  {IR(33702, 32), 457}, // 145 CooperativeVectorMatrixMulAddNV
  {IR(33592, 29), 454}, // 146 CooperativeVectorMatrixMulNV
  {IR(33621, 42), 455}, // 147 CooperativeVectorOuterProductAccumulateNV
  {IR(33663, 39), 456}, // 148 CooperativeVectorReduceSumAccumulateNV
  {IR(33953, 25), 466}, // 149 CooperativeVectorStoreNV
  {IR(30808, 12), 340}, // 150 CopyLogical
  {IR(26042, 11), 56}, // 151 CopyMemory
  {IR(26053, 16), 57}, // 152 CopyMemorySized
  {IR(26428, 11), 75}, // 153 CopyObject
  {IR(29848, 26), 297}, // 154 CreatePipeFromPipeStorage
  {IR(34720, 21), 491}, // 155 CreateTensorLayoutNV
  {IR(34840, 19), 496}, // 156 CreateTensorViewNV
  {IR(29295, 16), 272}, // 157 CreateUserEvent
  {IR(42775, 29), 738}, // 158 CrossWorkgroupCastToPtrINTEL
  {IR(27995, 5), 192}, // 159 DPdx
  {IR(28041, 11), 198}, // 160 DPdxCoarse
  {IR(28012, 9), 195}, // 161 DPdxFine
  {IR(28000, 5), 193}, // 162 DPdy
  {IR(28052, 11), 199}, // 163 DPdyCoarse
  {IR(28021, 9), 196}, // 164 DPdyFine
  {IR(26202, 9), 64}, // 165 Decorate
  {IR(30025, 11), 305}, // 166 DecorateId
  {IR(36209, 15), 558}, // 167 DecorateString
  {IR(36224, 21), 558}, // 168 DecorateStringGOOGLE
  {IR(26226, 16), 66}, // 169 DecorationGroup
  {IR(11258, 25), 499}, // 170 DemoteToHelperInvocation
  {IR(11283, 28), 499}, // 171 DemoteToHelperInvocationEXT
  {IR(30872, 23), 345}, // 172 DepthAttachmentReadEXT
  {IR(27311, 4), 137}, // 173 Dot
  {IR(33761, 17), 459}, // 174 EmitMeshTasksEXT
  {IR(28100, 17), 203}, // 175 EmitStreamVertex
  {IR(28076, 11), 201}, // 176 EmitVertex
  {IR(34421, 26), 484}, // 177 EndInvocationInterlockEXT
  {IR(28087, 13), 202}, // 178 EndPrimitive
  {IR(28117, 19), 204}, // 179 EndStreamPrimitive
  {IR(29131, 14), 265}, // 180 EnqueueKernel
  {IR(29117, 14), 264}, // 181 EnqueueMarker
  {IR(32446, 24), 410}, // 182 EnqueueNodePayloadsAMDX
  {IR(25045, 11), 13}, // 183 EntryPoint
  {IR(31273, 19), 365}, // 184 ExecuteCallableKHR
  {IR(34203, 18), 475}, // 185 ExecuteCallableNV
  {IR(25088, 14), 14}, // 186 ExecutionMode
  {IR(30009, 16), 304}, // 187 ExecutionModeId
  {IR(36199, 10), 557}, // 188 ExpectKHR
  {IR(24899, 8), 11}, // 189 ExtInst
  {IR(24839, 14), 10}, // 190 ExtInstImport
  {IR(31235, 26), 363}, // 191 ExtInstWithForwardRefsKHR
  {IR(24829, 10), 9}, // 192 Extension
  {IR(27143, 5), 118}, // 193 FAdd
  {IR(26974, 9), 105}, // 194 FConvert
  {IR(27178, 5), 125}, // 195 FDiv
  {IR(27203, 5), 130}, // 196 FMod
  {IR(27163, 5), 122}, // 197 FMul
  {IR(27130, 8), 116}, // 198 FNegate
  {IR(27640, 10), 168}, // 199 FOrdEqual
  {IR(27718, 16), 174}, // 200 FOrdGreaterThan
  {IR(27790, 21), 178}, // 201 FOrdGreaterThanEqual
  {IR(27690, 13), 172}, // 202 FOrdLessThan
  {IR(27752, 18), 176}, // 203 FOrdLessThanEqual
  {IR(27662, 13), 170}, // 204 FOrdNotEqual
  {IR(12721, 13), 741}, // 205 FPGARegINTEL
  {IR(27198, 5), 129}, // 206 FRem
  {IR(27153, 5), 120}, // 207 FSub
  {IR(27650, 12), 169}, // 208 FUnordEqual
  {IR(27734, 18), 175}, // 209 FUnordGreaterThan
  {IR(27811, 23), 179}, // 210 FUnordGreaterThanEqual
  {IR(27703, 15), 173}, // 211 FUnordLessThan
  {IR(27770, 20), 177}, // 212 FUnordLessThanEqual
  {IR(27675, 15), 171}, // 213 FUnordNotEqual
  {IR(33891, 38), 464}, // 214 FetchMicroTriangleVertexBarycentricNV
  {IR(33856, 35), 463}, // 215 FetchMicroTriangleVertexPositionNV
  {IR(32495, 29), 412}, // 216 FinishWritingNodePayloadAMDX
  {IR(42636, 14), 730}, // 217 FixedCosINTEL
  {IR(42683, 16), 733}, // 218 FixedCosPiINTEL
  {IR(42732, 14), 736}, // 219 FixedExpINTEL
  {IR(42718, 14), 735}, // 220 FixedLogINTEL
  {IR(42590, 16), 727}, // 221 FixedRecipINTEL
  {IR(42606, 16), 728}, // 222 FixedRsqrtINTEL
  {IR(42650, 17), 731}, // 223 FixedSinCosINTEL
  {IR(42699, 19), 734}, // 224 FixedSinCosPiINTEL
  {IR(42622, 14), 729}, // 225 FixedSinINTEL
  {IR(42667, 16), 732}, // 226 FixedSinPiINTEL
  {IR(42575, 15), 726}, // 227 FixedSqrtINTEL
  {IR(32391, 17), 407}, // 228 FragmentFetchAMD
  {IR(32370, 21), 406}, // 229 FragmentMaskFetchAMD
  {IR(24059, 9), 48}, // 230 Function
  {IR(25951, 13), 51}, // 231 FunctionCall
  {IR(25939, 12), 50}, // 232 FunctionEnd
  {IR(25921, 18), 49}, // 233 FunctionParameter
  {IR(36104, 25), 550}, // 234 FunctionPointerCallINTEL
  {IR(28005, 7), 194}, // 235 Fwidth
  {IR(28063, 13), 200}, // 236 FwidthCoarse
  {IR(28030, 11), 197}, // 237 FwidthFine
  {IR(27072, 17), 112}, // 238 GenericCastToPtr
  {IR(27089, 25), 113}, // 239 GenericCastToPtrExplicit
  {IR(26128, 23), 62}, // 240 GenericPtrMemSemantics
  {IR(29369, 16), 276}, // 241 GetDefaultQueue
  {IR(29874, 35), 298}, // 242 GetKernelLocalSizeForSubgroupCount
  {IR(29909, 25), 299}, // 243 GetKernelMaxNumSubgroups
  {IR(29175, 32), 267}, // 244 GetKernelNDrangeMaxSubGroupSize
  {IR(29145, 30), 266}, // 245 GetKernelNDrangeSubGroupCount
  {IR(29230, 40), 269}, // 246 GetKernelPreferredWorkGroupSizeMultiple
  {IR(29207, 23), 268}, // 247 GetKernelWorkGroupSize
  {IR(29001, 18), 259}, // 248 GetMaxPipePackets
  {IR(28983, 18), 258}, // 249 GetNumPipePackets
  {IR(28688, 9), 238}, // 250 GroupAll
  {IR(28697, 9), 239}, // 251 GroupAny
  {IR(28657, 15), 236}, // 252 GroupAsyncCopy
  {IR(44152, 19), 785}, // 253 GroupBitwiseAndKHR
  {IR(44171, 18), 786}, // 254 GroupBitwiseOrKHR
  {IR(44189, 19), 787}, // 255 GroupBitwiseXorKHR
  {IR(28706, 15), 240}, // 256 GroupBroadcast
  {IR(29076, 20), 262}, // 257 GroupCommitReadPipe
  {IR(29096, 21), 263}, // 258 GroupCommitWritePipe
  {IR(26242, 14), 67}, // 259 GroupDecorate
  {IR(28764, 10), 242}, // 260 GroupFAdd
  {IR(32209, 23), 399}, // 261 GroupFAddNonUniformAMD
  {IR(28804, 10), 246}, // 262 GroupFMax
  {IR(32301, 23), 403}, // 263 GroupFMaxNonUniformAMD
  {IR(28774, 10), 243}, // 264 GroupFMin
  {IR(32232, 23), 400}, // 265 GroupFMinNonUniformAMD
  {IR(44139, 13), 784}, // 266 GroupFMulKHR
  {IR(28754, 10), 241}, // 267 GroupIAdd
  {IR(32186, 23), 398}, // 268 GroupIAddNonUniformAMD
  {IR(44126, 13), 783}, // 269 GroupIMulKHR
  {IR(44208, 19), 788}, // 270 GroupLogicalAndKHR
  {IR(44227, 18), 789}, // 271 GroupLogicalOrKHR
  {IR(44245, 19), 790}, // 272 GroupLogicalXorKHR
  {IR(26301, 20), 68}, // 273 GroupMemberDecorate
  {IR(30057, 19), 307}, // 274 GroupNonUniformAll
  {IR(30095, 24), 309}, // 275 GroupNonUniformAllEqual
  {IR(30076, 19), 308}, // 276 GroupNonUniformAny
  {IR(5512, 22), 312}, // 277 GroupNonUniformBallot
  {IR(30235, 30), 315}, // 278 GroupNonUniformBallotBitCount
  {IR(30203, 32), 314}, // 279 GroupNonUniformBallotBitExtract
  {IR(30265, 29), 316}, // 280 GroupNonUniformBallotFindLSB
  {IR(30294, 29), 317}, // 281 GroupNonUniformBallotFindMSB
  {IR(30601, 26), 332}, // 282 GroupNonUniformBitwiseAnd
  {IR(30627, 25), 333}, // 283 GroupNonUniformBitwiseOr
  {IR(30652, 26), 334}, // 284 GroupNonUniformBitwiseXor
  {IR(30119, 25), 310}, // 285 GroupNonUniformBroadcast
  {IR(30144, 30), 311}, // 286 GroupNonUniformBroadcastFirst
  {IR(30036, 21), 306}, // 287 GroupNonUniformElect
  {IR(30421, 20), 323}, // 288 GroupNonUniformFAdd
  {IR(30581, 20), 331}, // 289 GroupNonUniformFMax
  {IR(30521, 20), 328}, // 290 GroupNonUniformFMin
  {IR(30461, 20), 325}, // 291 GroupNonUniformFMul
  {IR(30401, 20), 322}, // 292 GroupNonUniformIAdd
  {IR(30441, 20), 324}, // 293 GroupNonUniformIMul
  {IR(30174, 29), 313}, // 294 GroupNonUniformInverseBallot
  {IR(30678, 26), 335}, // 295 GroupNonUniformLogicalAnd
  {IR(30704, 25), 336}, // 296 GroupNonUniformLogicalOr
  {IR(30729, 26), 337}, // 297 GroupNonUniformLogicalXor
  {IR(33796, 27), 461}, // 298 GroupNonUniformPartitionNV
  {IR(32616, 26), 417}, // 299 GroupNonUniformQuadAllKHR
  {IR(32642, 26), 418}, // 300 GroupNonUniformQuadAnyKHR
  {IR(30755, 29), 338}, // 301 GroupNonUniformQuadBroadcast
  {IR(30784, 24), 339}, // 302 GroupNonUniformQuadSwap
  {IR(12946, 25), 361}, // 303 GroupNonUniformRotateKHR
  {IR(30541, 20), 329}, // 304 GroupNonUniformSMax
  {IR(30481, 20), 326}, // 305 GroupNonUniformSMin
  {IR(8602, 23), 318}, // 306 GroupNonUniformShuffle
  {IR(30374, 27), 321}, // 307 GroupNonUniformShuffleDown
  {IR(30349, 25), 320}, // 308 GroupNonUniformShuffleUp
  {IR(30323, 26), 319}, // 309 GroupNonUniformShuffleXor
  {IR(30561, 20), 330}, // 310 GroupNonUniformUMax
  {IR(30501, 20), 327}, // 311 GroupNonUniformUMin
  {IR(29019, 28), 260}, // 312 GroupReserveReadPipePackets
  {IR(29047, 29), 261}, // 313 GroupReserveWritePipePackets
  {IR(28824, 10), 248}, // 314 GroupSMax
  {IR(32347, 23), 405}, // 315 GroupSMaxNonUniformAMD
  {IR(28794, 10), 245}, // 316 GroupSMin
  {IR(32278, 23), 402}, // 317 GroupSMinNonUniformAMD
  {IR(28814, 10), 247}, // 318 GroupUMax
  {IR(32324, 23), 404}, // 319 GroupUMaxNonUniformAMD
  {IR(28784, 10), 244}, // 320 GroupUMin
  {IR(32255, 23), 401}, // 321 GroupUMinNonUniformAMD
  {IR(28672, 16), 237}, // 322 GroupWaitEvents
  {IR(33103, 25), 434}, // 323 HitObjectExecuteShaderNV
  {IR(33154, 25), 436}, // 324 HitObjectGetAttributesNV
  {IR(34244, 24), 477}, // 325 HitObjectGetClusterIdNV
  {IR(33128, 26), 435}, // 326 HitObjectGetCurrentTimeNV
  {IR(33230, 28), 439}, // 327 HitObjectGetGeometryIndexNV
  {IR(33179, 22), 437}, // 328 HitObjectGetHitKindNV
  {IR(33283, 34), 441}, // 329 HitObjectGetInstanceCustomIndexNV
  {IR(33258, 25), 440}, // 330 HitObjectGetInstanceIdNV
  {IR(35471, 27), 519}, // 331 HitObjectGetLSSPositionsNV
  {IR(35498, 23), 520}, // 332 HitObjectGetLSSRadiiNV
  {IR(32815, 33), 424}, // 333 HitObjectGetObjectRayDirectionNV
  {IR(32848, 30), 425}, // 334 HitObjectGetObjectRayOriginNV
  {IR(32787, 28), 423}, // 335 HitObjectGetObjectToWorldNV
  {IR(33201, 29), 438}, // 336 HitObjectGetPrimitiveIndexNV
  {IR(33378, 22), 444}, // 337 HitObjectGetRayTMaxNV
  {IR(33400, 22), 445}, // 338 HitObjectGetRayTMinNV
  {IR(32943, 44), 428}, // 339 HitObjectGetShaderBindingTableRecordIndexNV
  {IR(32904, 39), 427}, // 340 HitObjectGetShaderRecordBufferHandleNV
  {IR(35415, 29), 517}, // 341 HitObjectGetSpherePositionNV
  {IR(35444, 27), 518}, // 342 HitObjectGetSphereRadiusNV
  {IR(33317, 32), 442}, // 343 HitObjectGetWorldRayDirectionNV
  {IR(33349, 29), 443}, // 344 HitObjectGetWorldRayOriginNV
  {IR(32759, 28), 422}, // 345 HitObjectGetWorldToObjectNV
  {IR(33422, 19), 446}, // 346 HitObjectIsEmptyNV
  {IR(33441, 17), 447}, // 347 HitObjectIsHitNV
  {IR(35544, 20), 522}, // 348 HitObjectIsLSSHitNV
  {IR(33458, 18), 448}, // 349 HitObjectIsMissNV
  {IR(35521, 23), 521}, // 350 HitObjectIsSphereHitNV
  {IR(32987, 23), 429}, // 351 HitObjectRecordEmptyNV
  {IR(32668, 27), 419}, // 352 HitObjectRecordHitMotionNV
  {IR(33030, 21), 431}, // 353 HitObjectRecordHitNV
  {IR(32695, 36), 420}, // 354 HitObjectRecordHitWithIndexMotionNV
  {IR(33051, 30), 432}, // 355 HitObjectRecordHitWithIndexNV
  {IR(32731, 28), 421}, // 356 HitObjectRecordMissMotionNV
  {IR(33081, 22), 433}, // 357 HitObjectRecordMissNV
  {IR(32878, 26), 426}, // 358 HitObjectTraceRayMotionNV
  {IR(33010, 20), 430}, // 359 HitObjectTraceRayNV
  {IR(27138, 5), 117}, // 360 IAdd
  {IR(27315, 10), 138}, // 361 IAddCarry
  {IR(35923, 13), 539}, // 362 IAddSatINTEL
  {IR(35949, 14), 541}, // 363 IAverageINTEL
  {IR(35977, 21), 543}, // 364 IAverageRoundedINTEL
  {IR(27511, 7), 158}, // 365 IEqual
  {IR(27158, 5), 121}, // 366 IMul
  {IR(36045, 15), 547}, // 367 IMul32x16INTEL
  {IR(27518, 10), 159}, // 368 INotEqual
  {IR(27148, 5), 119}, // 369 ISub
  {IR(27325, 11), 139}, // 370 ISubBorrow
  {IR(36019, 13), 545}, // 371 ISubSatINTEL
  {IR(31327, 22), 367}, // 372 IgnoreIntersectionKHR
  {IR(34021, 21), 468}, // 373 IgnoreIntersectionNV
  {IR(24103, 6), 91}, // 374 Image
  {IR(32157, 29), 397}, // 375 ImageBlockMatchGatherSADQCOM
  {IR(32128, 29), 396}, // 376 ImageBlockMatchGatherSSDQCOM
  {IR(32047, 23), 393}, // 377 ImageBlockMatchSADQCOM
  {IR(32024, 23), 392}, // 378 ImageBlockMatchSSDQCOM
  {IR(32099, 29), 395}, // 379 ImageBlockMatchWindowSADQCOM
  {IR(32070, 29), 394}, // 380 ImageBlockMatchWindowSSDQCOM
  {IR(32005, 19), 391}, // 381 ImageBoxFilterQCOM
  {IR(26756, 16), 88}, // 382 ImageDrefGather
  {IR(26733, 11), 86}, // 383 ImageFetch
  {IR(26744, 12), 87}, // 384 ImageGather
  {IR(26793, 17), 92}, // 385 ImageQueryFormat
  {IR(26873, 17), 97}, // 386 ImageQueryLevels
  {IR(26859, 14), 96}, // 387 ImageQueryLod
  {IR(26810, 16), 93}, // 388 ImageQueryOrder
  {IR(26890, 18), 98}, // 389 ImageQuerySamples
  {IR(26844, 15), 95}, // 390 ImageQuerySize
  {IR(26826, 18), 94}, // 391 ImageQuerySizeLod
  {IR(26772, 10), 89}, // 392 ImageRead
  {IR(26590, 27), 81}, // 393 ImageSampleDrefExplicitLod
  {IR(26563, 27), 80}, // 394 ImageSampleDrefImplicitLod
  {IR(26540, 23), 79}, // 395 ImageSampleExplicitLod
  {IR(33545, 23), 452}, // 396 ImageSampleFootprintNV
  {IR(26494, 23), 78}, // 397 ImageSampleImplicitLod
  {IR(26702, 31), 85}, // 398 ImageSampleProjDrefExplicitLod
  {IR(26671, 31), 84}, // 399 ImageSampleProjDrefImplicitLod
  {IR(26644, 27), 83}, // 400 ImageSampleProjExplicitLod
  {IR(26617, 27), 82}, // 401 ImageSampleProjImplicitLod
  {IR(31981, 24), 390}, // 402 ImageSampleWeightedQCOM
  {IR(29697, 22), 288}, // 403 ImageSparseDrefGather
  {IR(29662, 17), 286}, // 404 ImageSparseFetch
  {IR(29679, 18), 287}, // 405 ImageSparseGather
  {IR(29789, 16), 293}, // 406 ImageSparseRead
  {IR(29489, 33), 281}, // 407 ImageSparseSampleDrefExplicitLod
  {IR(29456, 33), 280}, // 408 ImageSparseSampleDrefImplicitLod
  {IR(29427, 29), 279}, // 409 ImageSparseSampleExplicitLod
  {IR(29398, 29), 278}, // 410 ImageSparseSampleImplicitLod
  {IR(29625, 37), 285}, // 411 ImageSparseSampleProjDrefExplicitLod
  {IR(29588, 37), 284}, // 412 ImageSparseSampleProjDrefImplicitLod
  {IR(29555, 33), 283}, // 413 ImageSparseSampleProjExplicitLod
  {IR(29522, 33), 282}, // 414 ImageSparseSampleProjImplicitLod
  {IR(29719, 26), 289}, // 415 ImageSparseTexelsResident
  {IR(25973, 18), 53}, // 416 ImageTexelPointer
  {IR(26782, 11), 90}, // 417 ImageWrite
  {IR(26081, 20), 59}, // 418 InBoundsAccessChain
  {IR(26151, 23), 63}, // 419 InBoundsPtrAccessChain
  {IR(27382, 9), 146}, // 420 IsFinite
  {IR(34906, 22), 500}, // 421 IsHelperInvocationEXT
  {IR(27376, 6), 145}, // 422 IsInf
  {IR(27370, 6), 144}, // 423 IsNan
  {IR(32551, 23), 414}, // 424 IsNodePayloadValidAMDX
  {IR(27391, 9), 147}, // 425 IsNormal
  {IR(29311, 13), 273}, // 426 IsValidEvent
  {IR(28966, 17), 257}, // 427 IsValidReserveId
  {IR(28594, 5), 230}, // 428 Kill
  {IR(28511, 6), 226}, // 429 Label
  {IR(27411, 14), 149}, // 430 LessOrGreater
  {IR(28630, 14), 234}, // 431 LifetimeStart
  {IR(28644, 13), 235}, // 432 LifetimeStop
  {IR(24824, 5), 8}, // 433 Line
  {IR(26031, 5), 54}, // 434 Load
  {IR(27482, 11), 155}, // 435 LogicalAnd
  {IR(27443, 13), 152}, // 436 LogicalEqual
  {IR(27493, 11), 156}, // 437 LogicalNot
  {IR(27456, 16), 153}, // 438 LogicalNotEqual
  {IR(27472, 10), 154}, // 439 LogicalOr
  {IR(42493, 17), 722}, // 440 LoopControlINTEL
  {IR(28451, 10), 224}, // 441 LoopMerge
  {IR(44282, 18), 792}, // 442 MaskedGatherINTEL
  {IR(44300, 19), 793}, // 443 MaskedScatterINTEL
  {IR(27280, 18), 135}, // 444 MatrixTimesMatrix
  {IR(27226, 18), 132}, // 445 MatrixTimesScalar
  {IR(27262, 18), 134}, // 446 MatrixTimesVector
  {IR(26211, 15), 65}, // 447 MemberDecorate
  {IR(36245, 21), 559}, // 448 MemberDecorateString
  {IR(36266, 27), 559}, // 449 MemberDecorateStringGOOGLE
  {IR(24806, 11), 6}, // 450 MemberName
  {IR(28188, 14), 206}, // 451 MemoryBarrier
  {IR(24971, 12), 12}, // 452 MemoryModel
  {IR(29974, 19), 302}, // 453 MemoryNamedBarrier
  {IR(29993, 16), 303}, // 454 ModuleProcessed
  {IR(24801, 5), 5}, // 455 Name
  {IR(29951, 23), 301}, // 456 NamedBarrierInitialize
  {IR(29745, 7), 290}, // 457 NoLine
  {IR(32524, 27), 413}, // 458 NodePayloadArrayLengthAMDX
  {IR(24597, 4), 0}, // 459 Nop
  {IR(27922, 4), 186}, // 460 Not
  {IR(27425, 8), 150}, // 461 Ordered
  {IR(27298, 13), 136}, // 462 OuterProduct
  {IR(28417, 4), 223}, // 463 Phi
  {IR(26101, 15), 60}, // 464 PtrAccessChain
  {IR(42746, 29), 737}, // 465 PtrCastToCrossWorkgroupINTEL
  {IR(27055, 17), 111}, // 466 PtrCastToGeneric
  {IR(30841, 8), 343}, // 467 PtrDiff
  {IR(30820, 9), 341}, // 468 PtrEqual
  {IR(30829, 12), 342}, // 469 PtrNotEqual
  {IR(26983, 14), 106}, // 470 QuantizeToF16
  {IR(35211, 17), 511}, // 471 RawAccessChainNV
  {IR(31900, 31), 387}, // 472 RayQueryConfirmIntersectionKHR
  {IR(31868, 32), 386}, // 473 RayQueryGenerateIntersectionKHR
  {IR(34221, 23), 476}, // 474 RayQueryGetClusterIdNV
  {IR(43151, 39), 750}, // 475 RayQueryGetIntersectionBarycentricsKHR
  {IR(43226, 46), 752}, // 476 RayQueryGetIntersectionCandidateAABBOpaqueKHR
  {IR(43190, 36), 751}, // 477 RayQueryGetIntersectionFrontFaceKHR
  {IR(43070, 40), 748}, // 478 RayQueryGetIntersectionGeometryIndexKHR
  {IR(42922, 46), 745}, // 479 RayQueryGetIntersectionInstanceCustomIndexKHR
  {IR(42968, 37), 746}, // 480 RayQueryGetIntersectionInstanceIdKHR
  {IR(43005, 65), 747}, // 481 RayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR
  {IR(35378, 37), 516}, // 482 RayQueryGetIntersectionLSSHitValueNV
  {IR(35306, 38), 514}, // 483 RayQueryGetIntersectionLSSPositionsNV
  {IR(35344, 34), 515}, // 484 RayQueryGetIntersectionLSSRadiiNV
  {IR(43272, 45), 753}, // 485 RayQueryGetIntersectionObjectRayDirectionKHR
  {IR(43317, 42), 754}, // 486 RayQueryGetIntersectionObjectRayOriginKHR
  {IR(43420, 40), 757}, // 487 RayQueryGetIntersectionObjectToWorldKHR
  {IR(43110, 41), 749}, // 488 RayQueryGetIntersectionPrimitiveIndexKHR
  {IR(35228, 40), 512}, // 489 RayQueryGetIntersectionSpherePositionNV
  {IR(35268, 38), 513}, // 490 RayQueryGetIntersectionSphereRadiusNV
  {IR(42894, 28), 744}, // 491 RayQueryGetIntersectionTKHR
  {IR(34096, 50), 473}, // 492 RayQueryGetIntersectionTriangleVertexPositionsKHR
  {IR(31950, 31), 389}, // 493 RayQueryGetIntersectionTypeKHR
  {IR(43460, 40), 758}, // 494 RayQueryGetIntersectionWorldToObjectKHR
  {IR(42871, 23), 743}, // 495 RayQueryGetRayFlagsKHR
  {IR(42849, 22), 742}, // 496 RayQueryGetRayTMinKHR
  {IR(43359, 32), 755}, // 497 RayQueryGetWorldRayDirectionKHR
  {IR(43391, 29), 756}, // 498 RayQueryGetWorldRayOriginKHR
  {IR(31825, 22), 384}, // 499 RayQueryInitializeKHR
  {IR(35586, 19), 524}, // 500 RayQueryIsLSSHitNV
  {IR(35564, 22), 523}, // 501 RayQueryIsSphereHitNV
  {IR(31931, 19), 388}, // 502 RayQueryProceedKHR
  {IR(31847, 21), 385}, // 503 RayQueryTerminateKHR
  {IR(32408, 13), 408}, // 504 ReadClockKHR
  {IR(28834, 9), 249}, // 505 ReadPipe
  {IR(42804, 22), 739}, // 506 ReadPipeBlockingINTEL
  {IR(29282, 13), 271}, // 507 ReleaseEvent
  {IR(33505, 24), 450}, // 508 ReorderThreadWithHintNV
  {IR(33476, 29), 449}, // 509 ReorderThreadWithHitObjectNV
  {IR(33978, 22), 467}, // 510 ReportIntersectionKHR
  {IR(34000, 21), 467}, // 511 ReportIntersectionNV
  {IR(28888, 23), 253}, // 512 ReserveReadPipePackets
  {IR(28911, 24), 254}, // 513 ReserveWritePipePackets
  {IR(28853, 17), 251}, // 514 ReservedReadPipe
  {IR(28870, 18), 252}, // 515 ReservedWritePipe
  {IR(41475, 19), 680}, // 516 RestoreMemoryINTEL
  {IR(29270, 12), 270}, // 517 RetainEvent
  {IR(28599, 7), 231}, // 518 Return
  {IR(28606, 12), 232}, // 519 ReturnValue
  {IR(44264, 18), 791}, // 520 RoundFToTF32INTEL
  {IR(26965, 9), 104}, // 521 SConvert
  {IR(27173, 5), 124}, // 522 SDiv
  {IR(31412, 5), 369}, // 523 SDot
  {IR(31453, 11), 372}, // 524 SDotAccSat
  {IR(31464, 14), 372}, // 525 SDotAccSatKHR
  {IR(31417, 8), 369}, // 526 SDotKHR
  {IR(27541, 13), 161}, // 527 SGreaterThan
  {IR(27572, 18), 163}, // 528 SGreaterThanEqual
  {IR(27600, 10), 165}, // 529 SLessThan
  {IR(27625, 15), 167}, // 530 SLessThanEqual
  {IR(27193, 5), 128}, // 531 SMod
  {IR(27349, 13), 141}, // 532 SMulExtended
  {IR(27122, 8), 115}, // 533 SNegate
  {IR(27188, 5), 127}, // 534 SRem
  {IR(31438, 6), 371}, // 535 SUDot
  {IR(31503, 12), 374}, // 536 SUDotAccSat
  {IR(31515, 15), 374}, // 537 SUDotAccSatKHR
  {IR(31444, 9), 371}, // 538 SUDotKHR
  {IR(26449, 13), 77}, // 539 SampledImage
  {IR(35130, 29), 510}, // 540 SamplerImageAddressingModeNV
  {IR(27011, 15), 108}, // 541 SatConvertSToU
  {IR(27026, 15), 109}, // 542 SatConvertUToS
  {IR(41459, 16), 679}, // 543 SaveMemoryINTEL
  {IR(27504, 7), 157}, // 544 Select
  {IR(28496, 15), 225}, // 545 SelectionMerge
  {IR(33778, 18), 460}, // 546 SetMeshOutputsEXT
  {IR(29324, 19), 274}, // 547 SetUserEventStatus
  {IR(27873, 17), 182}, // 548 ShiftLeftLogical
  {IR(27852, 21), 181}, // 549 ShiftRightArithmetic
  {IR(27834, 18), 180}, // 550 ShiftRightLogical
  {IR(27400, 11), 148}, // 551 SignBitSet
  {IR(29805, 7), 294}, // 552 SizeOf
  {IR(24778, 7), 3}, // 553 Source
  {IR(24659, 16), 2}, // 554 SourceContinued
  {IR(24785, 16), 4}, // 555 SourceExtension
  {IR(25796, 13), 45}, // 556 SpecConstant
  {IR(25809, 22), 46}, // 557 SpecConstantComposite
  {IR(43594, 36), 763}, // 558 SpecConstantCompositeContinuedINTEL
  {IR(31744, 34), 381}, // 559 SpecConstantCompositeReplicateEXT
  {IR(25778, 18), 44}, // 560 SpecConstantFalse
  {IR(25872, 15), 47}, // 561 SpecConstantOp
  {IR(32593, 23), 416}, // 562 SpecConstantStringAMDX
  {IR(25761, 17), 43}, // 563 SpecConstantTrue
  {IR(30895, 25), 346}, // 564 StencilAttachmentReadEXT
  {IR(26036, 6), 55}, // 565 Store
  {IR(24817, 7), 7}, // 566 String
  {IR(43895, 25), 776}, // 567 Subgroup2DBlockLoadINTEL
  {IR(43920, 34), 777}, // 568 Subgroup2DBlockLoadTransformINTEL
  {IR(43954, 34), 778}, // 569 Subgroup2DBlockLoadTransposeINTEL
  {IR(43988, 29), 779}, // 570 Subgroup2DBlockPrefetchINTEL
  {IR(44017, 26), 780}, // 571 Subgroup2DBlockStoreINTEL
  {IR(31189, 20), 360}, // 572 SubgroupAllEqualKHR
  {IR(31159, 15), 358}, // 573 SubgroupAllKHR
  {IR(31174, 15), 359}, // 574 SubgroupAnyKHR
  {IR(39977, 30), 643}, // 575 SubgroupAvcBmeInitializeINTEL
  {IR(39947, 30), 642}, // 576 SubgroupAvcFmeInitializeINTEL
  {IR(38382, 35), 612}, // 577 SubgroupAvcImeAdjustRefOffsetINTEL
  {IR(38417, 39), 613}, // 578 SubgroupAvcImeConvertToMcePayloadINTEL
  {IR(39058, 38), 626}, // 579 SubgroupAvcImeConvertToMceResultINTEL
  {IR(38681, 45), 619}, // 580 SubgroupAvcImeEvaluateWithDualReferenceINTEL
  {IR(38781, 53), 621}, // 581 SubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL
  {IR(39002, 56), 625}, // 582 SubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL
  {IR(38890, 54), 623}, // 583 SubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL
  {IR(38634, 47), 618}, // 584 SubgroupAvcImeEvaluateWithSingleReferenceINTEL
  {IR(38726, 55), 620}, // 585 SubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL
  {IR(38944, 58), 624}, // 586 SubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL
  {IR(38834, 56), 622}, // 587 SubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL
  {IR(39690, 36), 637}, // 588 SubgroupAvcImeGetBorderReachedINTEL
  {IR(39142, 44), 628}, // 589 SubgroupAvcImeGetDualReferenceStreaminINTEL
  {IR(39096, 46), 627}, // 590 SubgroupAvcImeGetSingleReferenceStreaminINTEL
  {IR(39557, 66), 635}, // 591 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL
  {IR(39489, 68), 634}, // 592 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL
  {IR(39623, 67), 636}, // 593 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL
  {IR(39352, 68), 632}, // 594 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL
  {IR(39282, 70), 631}, // 595 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL
  {IR(39420, 69), 633}, // 596 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL
  {IR(39726, 48), 638}, // 597 SubgroupAvcImeGetTruncatedSearchIndicationINTEL
  {IR(39774, 59), 639}, // 598 SubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL
  {IR(39891, 56), 641}, // 599 SubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL
  {IR(39833, 58), 640}, // 600 SubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL
  {IR(38245, 30), 608}, // 601 SubgroupAvcImeInitializeINTEL
  {IR(38349, 33), 611}, // 602 SubgroupAvcImeRefWindowSizeINTEL
  {IR(38313, 36), 610}, // 603 SubgroupAvcImeSetDualReferenceINTEL
  {IR(38546, 54), 616}, // 604 SubgroupAvcImeSetEarlySearchTerminationThresholdINTEL
  {IR(38456, 43), 614}, // 605 SubgroupAvcImeSetMaxMotionVectorCountINTEL
  {IR(38275, 38), 609}, // 606 SubgroupAvcImeSetSingleReferenceINTEL
  {IR(38499, 47), 615}, // 607 SubgroupAvcImeSetUnidirectionalMixDisableINTEL
  {IR(38600, 34), 617}, // 608 SubgroupAvcImeSetWeightedSadINTEL
  {IR(39235, 47), 630}, // 609 SubgroupAvcImeStripDualReferenceStreamoutINTEL
  {IR(39186, 49), 629}, // 610 SubgroupAvcImeStripSingleReferenceStreamoutINTEL
  {IR(37635, 39), 593}, // 611 SubgroupAvcMceConvertToImePayloadINTEL
  {IR(37674, 38), 594}, // 612 SubgroupAvcMceConvertToImeResultINTEL
  {IR(37712, 39), 595}, // 613 SubgroupAvcMceConvertToRefPayloadINTEL
  {IR(37751, 38), 596}, // 614 SubgroupAvcMceConvertToRefResultINTEL
  {IR(37789, 39), 597}, // 615 SubgroupAvcMceConvertToSicPayloadINTEL
  {IR(37828, 38), 598}, // 616 SubgroupAvcMceConvertToSicResultINTEL
  {IR(37941, 43), 601}, // 617 SubgroupAvcMceGetBestInterDistortionsINTEL
  {IR(37073, 50), 582}, // 618 SubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL
  {IR(36671, 60), 574}, // 619 SubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL
  {IR(36871, 51), 578}, // 620 SubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL
  {IR(37017, 56), 581}, // 621 SubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL
  {IR(36784, 47), 576}, // 622 SubgroupAvcMceGetDefaultInterShapePenaltyINTEL
  {IR(37372, 56), 588}, // 623 SubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL
  {IR(37271, 50), 586}, // 624 SubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL
  {IR(36966, 51), 580}, // 625 SubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL
  {IR(37175, 49), 584}, // 626 SubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL
  {IR(37123, 52), 583}, // 627 SubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL
  {IR(37321, 51), 587}, // 628 SubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL
  {IR(38060, 38), 604}, // 629 SubgroupAvcMceGetInterDirectionsINTEL
  {IR(37902, 39), 600}, // 630 SubgroupAvcMceGetInterDistortionsINTEL
  {IR(37984, 38), 602}, // 631 SubgroupAvcMceGetInterMajorShapeINTEL
  {IR(38022, 38), 603}, // 632 SubgroupAvcMceGetInterMinorShapeINTEL
  {IR(38098, 45), 605}, // 633 SubgroupAvcMceGetInterMotionVectorCountINTEL
  {IR(38143, 40), 606}, // 634 SubgroupAvcMceGetInterReferenceIdsINTEL
  {IR(38183, 62), 607}, // 635 SubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL
  {IR(37866, 36), 599}, // 636 SubgroupAvcMceGetMotionVectorsINTEL
  {IR(37428, 33), 589}, // 637 SubgroupAvcMceSetAcOnlyHaarINTEL
  {IR(37574, 61), 592}, // 638 SubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL
  {IR(36731, 53), 575}, // 639 SubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL
  {IR(36922, 44), 579}, // 640 SubgroupAvcMceSetInterDirectionPenaltyINTEL
  {IR(36831, 40), 577}, // 641 SubgroupAvcMceSetInterShapePenaltyINTEL
  {IR(37224, 47), 585}, // 642 SubgroupAvcMceSetMotionVectorCostFunctionINTEL
  {IR(37513, 61), 591}, // 643 SubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL
  {IR(37461, 52), 590}, // 644 SubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL
  {IR(40007, 39), 644}, // 645 SubgroupAvcRefConvertToMcePayloadINTEL
  {IR(40329, 38), 651}, // 646 SubgroupAvcRefConvertToMceResultINTEL
  {IR(40182, 45), 648}, // 647 SubgroupAvcRefEvaluateWithDualReferenceINTEL
  {IR(40227, 46), 649}, // 648 SubgroupAvcRefEvaluateWithMultiReferenceINTEL
  {IR(40273, 56), 650}, // 649 SubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL
  {IR(40135, 47), 647}, // 650 SubgroupAvcRefEvaluateWithSingleReferenceINTEL
  {IR(40046, 46), 645}, // 651 SubgroupAvcRefSetBidirectionalMixDisableINTEL
  {IR(40092, 43), 646}, // 652 SubgroupAvcRefSetBilinearFilterEnableINTEL
  {IR(40465, 42), 655}, // 653 SubgroupAvcSicConfigureIpeLumaChromaINTEL
  {IR(40429, 36), 654}, // 654 SubgroupAvcSicConfigureIpeLumaINTEL
  {IR(40397, 32), 653}, // 655 SubgroupAvcSicConfigureSkcINTEL
  {IR(40546, 39), 657}, // 656 SubgroupAvcSicConvertToMcePayloadINTEL
  {IR(41086, 38), 669}, // 657 SubgroupAvcSicConvertToMceResultINTEL
  {IR(40861, 31), 664}, // 658 SubgroupAvcSicEvaluateIpeINTEL
  {IR(40939, 45), 666}, // 659 SubgroupAvcSicEvaluateWithDualReferenceINTEL
  {IR(40984, 46), 667}, // 660 SubgroupAvcSicEvaluateWithMultiReferenceINTEL
  {IR(41030, 56), 668}, // 661 SubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL
  {IR(40892, 47), 665}, // 662 SubgroupAvcSicEvaluateWithSingleReferenceINTEL
  {IR(41203, 46), 672}, // 663 SubgroupAvcSicGetBestIpeChromaDistortionINTEL
  {IR(41159, 44), 671}, // 664 SubgroupAvcSicGetBestIpeLumaDistortionINTEL
  {IR(41424, 35), 677}, // 665 SubgroupAvcSicGetInterRawSadsINTEL
  {IR(41290, 36), 674}, // 666 SubgroupAvcSicGetIpeChromaModeINTEL
  {IR(41124, 35), 670}, // 667 SubgroupAvcSicGetIpeLumaShapeINTEL
  {IR(40507, 39), 656}, // 668 SubgroupAvcSicGetMotionVectorMaskINTEL
  {IR(41249, 41), 673}, // 669 SubgroupAvcSicGetPackedIpeLumaModesINTEL
  {IR(41326, 50), 675}, // 670 SubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL
  {IR(41376, 48), 676}, // 671 SubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL
  {IR(40367, 30), 652}, // 672 SubgroupAvcSicInitializeINTEL
  {IR(40727, 43), 661}, // 673 SubgroupAvcSicSetBilinearFilterEnableINTEL
  {IR(40818, 43), 663}, // 674 SubgroupAvcSicSetBlockBasedRawSkipSadINTEL
  {IR(40677, 50), 660}, // 675 SubgroupAvcSicSetIntraChromaModeCostFunctionINTEL
  {IR(40629, 48), 659}, // 676 SubgroupAvcSicSetIntraLumaModeCostFunctionINTEL
  {IR(40585, 44), 658}, // 677 SubgroupAvcSicSetIntraLumaShapePenaltyINTEL
  {IR(40770, 48), 662}, // 678 SubgroupAvcSicSetSkcForwardTransformEnableINTEL
  {IR(5273, 18), 352}, // 679 SubgroupBallotKHR
  {IR(43868, 27), 775}, // 680 SubgroupBlockPrefetchINTEL
  {IR(35677, 23), 529}, // 681 SubgroupBlockReadINTEL
  {IR(35700, 24), 530}, // 682 SubgroupBlockWriteINTEL
  {IR(31033, 27), 353}, // 683 SubgroupFirstInvocationKHR
  {IR(35724, 28), 531}, // 684 SubgroupImageBlockReadINTEL
  {IR(35752, 29), 532}, // 685 SubgroupImageBlockWriteINTEL
  {IR(35781, 33), 533}, // 686 SubgroupImageMediaBlockReadINTEL
  {IR(35814, 34), 534}, // 687 SubgroupImageMediaBlockWriteINTEL
  {IR(13491, 38), 781}, // 688 SubgroupMatrixMultiplyAccumulateINTEL
  {IR(31209, 26), 362}, // 689 SubgroupReadInvocationKHR
  {IR(35605, 25), 526}, // 690 SubgroupShuffleDownINTEL
  {IR(11706, 21), 525}, // 691 SubgroupShuffleINTEL
  {IR(35630, 23), 527}, // 692 SubgroupShuffleUpINTEL
  {IR(35653, 24), 528}, // 693 SubgroupShuffleXorINTEL
  {IR(28587, 7), 229}, // 694 Switch
  {IR(43777, 23), 771}, // 695 TaskSequenceAsyncINTEL
  {IR(43753, 24), 770}, // 696 TaskSequenceCreateINTEL
  {IR(43800, 21), 772}, // 697 TaskSequenceGetINTEL
  {IR(43821, 25), 773}, // 698 TaskSequenceReleaseINTEL
  {IR(34948, 27), 502}, // 699 TensorLayoutSetBlockSizeNV
  {IR(34812, 28), 495}, // 700 TensorLayoutSetClampValueNV
  {IR(34741, 27), 492}, // 701 TensorLayoutSetDimensionNV
  {IR(34768, 24), 493}, // 702 TensorLayoutSetStrideNV
  {IR(34792, 20), 494}, // 703 TensorLayoutSliceNV
  {IR(34928, 20), 501}, // 704 TensorViewSetClipNV
  {IR(34859, 25), 497}, // 705 TensorViewSetDimensionNV
  {IR(34884, 22), 498}, // 706 TensorViewSetStrideNV
  {IR(30920, 20), 347}, // 707 TerminateInvocation
  {IR(31349, 16), 368}, // 708 TerminateRayKHR
  {IR(34042, 15), 469}, // 709 TerminateRayNV
  {IR(34065, 14), 471}, // 710 TraceMotionNV
  {IR(34057, 8), 470}, // 711 TraceNV
  {IR(31261, 12), 364}, // 712 TraceRayKHR
  {IR(34079, 17), 472}, // 713 TraceRayMotionNV
  {IR(26439, 10), 76}, // 714 Transpose
  {IR(34146, 29), 474}, // 715 TypeAccelerationStructureKHR
  {IR(34175, 28), 474}, // 716 TypeAccelerationStructureNV
  {IR(25388, 10), 25}, // 717 TypeArray
  {IR(36590, 37), 571}, // 718 TypeAvcImeDualReferenceStreaminINTEL
  {IR(36325, 23), 562}, // 719 TypeAvcImePayloadINTEL
  {IR(36507, 44), 569}, // 720 TypeAvcImeResultDualReferenceStreamoutINTEL
  {IR(36439, 22), 567}, // 721 TypeAvcImeResultINTEL
  {IR(36461, 46), 568}, // 722 TypeAvcImeResultSingleReferenceStreamoutINTEL
  {IR(36551, 39), 570}, // 723 TypeAvcImeSingleReferenceStreaminINTEL
  {IR(36394, 23), 565}, // 724 TypeAvcMcePayloadINTEL
  {IR(36417, 22), 566}, // 725 TypeAvcMceResultINTEL
  {IR(36348, 23), 563}, // 726 TypeAvcRefPayloadINTEL
  {IR(36627, 22), 572}, // 727 TypeAvcRefResultINTEL
  {IR(36371, 23), 564}, // 728 TypeAvcSicPayloadINTEL
  {IR(36649, 22), 573}, // 729 TypeAvcSicResultINTEL
  {IR(25150, 9), 17}, // 730 TypeBool
  {IR(43514, 23), 760}, // 731 TypeBufferSurfaceINTEL
  {IR(31530, 25), 375}, // 732 TypeCooperativeMatrixKHR
  {IR(34268, 24), 478}, // 733 TypeCooperativeMatrixNV
  {IR(33568, 24), 453}, // 734 TypeCooperativeVectorNV
  {IR(25503, 16), 32}, // 735 TypeDeviceEvent
  {IR(25493, 10), 31}, // 736 TypeEvent
  {IR(25204, 10), 19}, // 737 TypeFloat
  {IR(25552, 19), 36}, // 738 TypeForwardPointer
  {IR(25480, 13), 30}, // 739 TypeFunction
  {IR(33529, 16), 451}, // 740 TypeHitObjectNV
  {IR(25349, 10), 22}, // 741 TypeImage
  {IR(25159, 8), 18}, // 742 TypeInt
  {IR(25225, 11), 21}, // 743 TypeMatrix
  {IR(29934, 17), 300}, // 744 TypeNamedBarrier
  {IR(32470, 25), 411}, // 745 TypeNodePayloadArrayAMDX
  {IR(25426, 11), 28}, // 746 TypeOpaque
  {IR(25543, 9), 35}, // 747 TypePipe
  {IR(29812, 16), 295}, // 748 TypePipeStorage
  {IR(25468, 12), 29}, // 749 TypePointer
  {IR(25533, 10), 34}, // 750 TypeQueue
  {IR(31809, 16), 383}, // 751 TypeRayQueryKHR
  {IR(25519, 14), 33}, // 752 TypeReserveId
  {IR(25398, 17), 26}, // 753 TypeRuntimeArray
  {IR(25371, 17), 24}, // 754 TypeSampledImage
  {IR(25359, 12), 23}, // 755 TypeSampler
  {IR(25415, 11), 27}, // 756 TypeStruct
  {IR(43537, 25), 761}, // 757 TypeStructContinuedINTEL
  {IR(43846, 22), 774}, // 758 TypeTaskSequenceINTEL
  {IR(34684, 19), 489}, // 759 TypeTensorLayoutNV
  {IR(34703, 17), 490}, // 760 TypeTensorViewNV
  {IR(30940, 22), 348}, // 761 TypeUntypedPointerKHR
  {IR(25214, 11), 20}, // 762 TypeVector
  {IR(36307, 18), 561}, // 763 TypeVmeImageINTEL
  {IR(25141, 9), 16}, // 764 TypeVoid
  {IR(35936, 13), 540}, // 765 UAddSatINTEL
  {IR(35963, 14), 542}, // 766 UAverageINTEL
  {IR(35998, 21), 544}, // 767 UAverageRoundedINTEL
  {IR(26956, 9), 103}, // 768 UConvert
  {IR(35848, 24), 535}, // 769 UCountLeadingZerosINTEL
  {IR(35872, 25), 536}, // 770 UCountTrailingZerosINTEL
  {IR(27168, 5), 123}, // 771 UDiv
  {IR(31425, 5), 370}, // 772 UDot
  {IR(31478, 11), 373}, // 773 UDotAccSat
  {IR(31489, 14), 373}, // 774 UDotAccSatKHR
  {IR(31430, 8), 370}, // 775 UDotKHR
  {IR(27528, 13), 160}, // 776 UGreaterThan
  {IR(27554, 18), 162}, // 777 UGreaterThanEqual
  {IR(27590, 10), 164}, // 778 ULessThan
  {IR(27610, 15), 166}, // 779 ULessThanEqual
  {IR(27183, 5), 126}, // 780 UMod
  {IR(36060, 15), 548}, // 781 UMul32x16INTEL
  {IR(27336, 13), 140}, // 782 UMulExtended
  {IR(36032, 13), 546}, // 783 USubSatINTEL
  {IR(24653, 6), 1}, // 784 Undef
  {IR(27433, 10), 151}, // 785 Unordered
  {IR(28618, 12), 233}, // 786 Unreachable
  {IR(30981, 22), 350}, // 787 UntypedAccessChainKHR
  {IR(31118, 22), 356}, // 788 UntypedArrayLengthKHR
  {IR(31003, 30), 351}, // 789 UntypedInBoundsAccessChainKHR
  {IR(31085, 33), 355}, // 790 UntypedInBoundsPtrAccessChainKHR
  {IR(31140, 19), 357}, // 791 UntypedPrefetchKHR
  {IR(31060, 25), 354}, // 792 UntypedPtrAccessChainKHR
  {IR(30962, 19), 349}, // 793 UntypedVariableKHR
  {IR(25964, 9), 52}, // 794 Variable
  {IR(12162, 25), 678}, // 795 VariableLengthArrayINTEL
  {IR(26321, 21), 69}, // 796 VectorExtractDynamic
  {IR(26342, 20), 70}, // 797 VectorInsertDynamic
  {IR(26362, 14), 71}, // 798 VectorShuffle
  {IR(27244, 18), 133}, // 799 VectorTimesMatrix
  {IR(27208, 18), 131}, // 800 VectorTimesScalar
  {IR(36293, 14), 560}, // 801 VmeImageINTEL
  {IR(33823, 33), 462}, // 802 WritePackedPrimitiveIndices4x8NV
  {IR(28843, 10), 250}, // 803 WritePipe
  {IR(42826, 23), 740}, // 804 WritePipeBlockingINTEL
}};

// Extended instruction descriptions, ordered by (extinst enum, opcode value).
// The fields in order are:
//   enum value
//   operands, an IndexRange into kOperandSpans
//   name, a character-counting IndexRange into kStrings
//   capabilities, an IndexRange into kCapabilitySpans
static const std::array<ExtInstDesc, 425> kExtInstByValue{{
    {0,IR(0, 0),IR(44319, 14),IR(1, 0)}, // DebugInfoNone in debuginfo
    {1,IR(52, 3),IR(44333, 21),IR(1, 0)}, // DebugCompilationUnit in debuginfo
    {2,IR(714, 3),IR(44406, 15),IR(1, 0)}, // DebugTypeBasic in debuginfo
    {3,IR(717, 3),IR(44455, 17),IR(1, 0)}, // DebugTypePointer in debuginfo
    {4,IR(720, 2),IR(44510, 19),IR(1, 0)}, // DebugTypeQualifier in debuginfo
    {5,IR(168, 2),IR(44529, 15),IR(1, 0)}, // DebugTypeArray in debuginfo
    {6,IR(261, 2),IR(44544, 16),IR(1, 0)}, // DebugTypeVector in debuginfo
    {7,IR(722, 6),IR(44560, 13),IR(1, 0)}, // DebugTypedef in debuginfo
    {8,IR(168, 2),IR(44573, 18),IR(1, 0)}, // DebugTypeFunction in debuginfo
    {9,IR(728, 9),IR(44591, 14),IR(1, 0)}, // DebugTypeEnum in debuginfo
    {10,IR(737, 9),IR(44643, 19),IR(1, 0)}, // DebugTypeComposite in debuginfo
    {11,IR(746, 10),IR(44662, 16),IR(1, 0)}, // DebugTypeMember in debuginfo
    {12,IR(756, 5),IR(44678, 21),IR(1, 0)}, // DebugTypeInheritance in debuginfo
    {13,IR(36, 2),IR(44699, 21),IR(1, 0)}, // DebugTypePtrToMember in debuginfo
    {14,IR(168, 2),IR(44720, 18),IR(1, 0)}, // DebugTypeTemplate in debuginfo
    {15,IR(761, 6),IR(44738, 27),IR(1, 0)}, // DebugTypeTemplateParameter in debuginfo
    {16,IR(767, 5),IR(44765, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in debuginfo
    {17,IR(772, 5),IR(44800, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in debuginfo
    {18,IR(746, 10),IR(44831, 20),IR(1, 0)}, // DebugGlobalVariable in debuginfo
    {19,IR(777, 8),IR(44851, 25),IR(1, 0)}, // DebugFunctionDeclaration in debuginfo
    {20,IR(785, 11),IR(44876, 14),IR(1, 0)}, // DebugFunction in debuginfo
    {21,IR(796, 5),IR(44890, 18),IR(1, 0)}, // DebugLexicalBlock in debuginfo
    {22,IR(801, 3),IR(44908, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in debuginfo
    {23,IR(804, 2),IR(44939, 11),IR(1, 0)}, // DebugScope in debuginfo
    {24,IR(0, 0),IR(44950, 13),IR(1, 0)}, // DebugNoScope in debuginfo
    {25,IR(806, 3),IR(44963, 15),IR(1, 0)}, // DebugInlinedAt in debuginfo
    {26,IR(809, 7),IR(45020, 19),IR(1, 0)}, // DebugLocalVariable in debuginfo
    {27,IR(36, 2),IR(45039, 21),IR(1, 0)}, // DebugInlinedVariable in debuginfo
    {28,IR(33, 3),IR(45060, 13),IR(1, 0)}, // DebugDeclare in debuginfo
    {29,IR(816, 3),IR(45073, 11),IR(1, 0)}, // DebugValue in debuginfo
    {30,IR(819, 2),IR(45117, 15),IR(1, 0)}, // DebugOperation in debuginfo
    {31,IR(670, 1),IR(45132, 16),IR(1, 0)}, // DebugExpression in debuginfo
    {32,IR(821, 4),IR(45148, 14),IR(1, 0)}, // DebugMacroDef in debuginfo
    {33,IR(801, 3),IR(45162, 16),IR(1, 0)}, // DebugMacroUndef in debuginfo
    {1,IR(10, 1),IR(45178, 6),IR(1, 0)}, // Round in glsl_std_450
    {2,IR(10, 1),IR(45184, 10),IR(1, 0)}, // RoundEven in glsl_std_450
    {3,IR(10, 1),IR(45194, 6),IR(1, 0)}, // Trunc in glsl_std_450
    {4,IR(10, 1),IR(45200, 5),IR(1, 0)}, // FAbs in glsl_std_450
    {5,IR(10, 1),IR(45205, 5),IR(1, 0)}, // SAbs in glsl_std_450
    {6,IR(10, 1),IR(45210, 6),IR(1, 0)}, // FSign in glsl_std_450
    {7,IR(10, 1),IR(45216, 6),IR(1, 0)}, // SSign in glsl_std_450
    {8,IR(10, 1),IR(45222, 6),IR(1, 0)}, // Floor in glsl_std_450
    {9,IR(10, 1),IR(45228, 5),IR(1, 0)}, // Ceil in glsl_std_450
    {10,IR(10, 1),IR(45233, 6),IR(1, 0)}, // Fract in glsl_std_450
    {11,IR(10, 1),IR(45239, 8),IR(1, 0)}, // Radians in glsl_std_450
    {12,IR(10, 1),IR(45247, 8),IR(1, 0)}, // Degrees in glsl_std_450
    {13,IR(10, 1),IR(45255, 4),IR(1, 0)}, // Sin in glsl_std_450
    {14,IR(10, 1),IR(45259, 4),IR(1, 0)}, // Cos in glsl_std_450
    {15,IR(10, 1),IR(45263, 4),IR(1, 0)}, // Tan in glsl_std_450
    {16,IR(10, 1),IR(45267, 5),IR(1, 0)}, // Asin in glsl_std_450
    {17,IR(10, 1),IR(45272, 5),IR(1, 0)}, // Acos in glsl_std_450
    {18,IR(10, 1),IR(45277, 5),IR(1, 0)}, // Atan in glsl_std_450
    {19,IR(10, 1),IR(45282, 5),IR(1, 0)}, // Sinh in glsl_std_450
    {20,IR(10, 1),IR(45287, 5),IR(1, 0)}, // Cosh in glsl_std_450
    {21,IR(10, 1),IR(45292, 5),IR(1, 0)}, // Tanh in glsl_std_450
    {22,IR(10, 1),IR(45297, 6),IR(1, 0)}, // Asinh in glsl_std_450
    {23,IR(10, 1),IR(45303, 6),IR(1, 0)}, // Acosh in glsl_std_450
    {24,IR(10, 1),IR(45309, 6),IR(1, 0)}, // Atanh in glsl_std_450
    {25,IR(36, 2),IR(45315, 6),IR(1, 0)}, // Atan2 in glsl_std_450
    {26,IR(36, 2),IR(45321, 4),IR(1, 0)}, // Pow in glsl_std_450
    {27,IR(10, 1),IR(45325, 4),IR(1, 0)}, // Exp in glsl_std_450
    {28,IR(10, 1),IR(45329, 4),IR(1, 0)}, // Log in glsl_std_450
    {29,IR(10, 1),IR(45333, 5),IR(1, 0)}, // Exp2 in glsl_std_450
    {30,IR(10, 1),IR(45338, 5),IR(1, 0)}, // Log2 in glsl_std_450
    {31,IR(10, 1),IR(45343, 5),IR(1, 0)}, // Sqrt in glsl_std_450
    {32,IR(10, 1),IR(45348, 12),IR(1, 0)}, // InverseSqrt in glsl_std_450
    {33,IR(10, 1),IR(45360, 12),IR(1, 0)}, // Determinant in glsl_std_450
    {34,IR(10, 1),IR(45372, 14),IR(1, 0)}, // MatrixInverse in glsl_std_450
    {35,IR(36, 2),IR(45386, 5),IR(1, 0)}, // Modf in glsl_std_450
    {36,IR(10, 1),IR(45391, 11),IR(1, 0)}, // ModfStruct in glsl_std_450
    {37,IR(36, 2),IR(45402, 5),IR(1, 0)}, // FMin in glsl_std_450
    {38,IR(36, 2),IR(45407, 5),IR(1, 0)}, // UMin in glsl_std_450
    {39,IR(36, 2),IR(45412, 5),IR(1, 0)}, // SMin in glsl_std_450
    {40,IR(36, 2),IR(45417, 5),IR(1, 0)}, // FMax in glsl_std_450
    {41,IR(36, 2),IR(45422, 5),IR(1, 0)}, // UMax in glsl_std_450
    {42,IR(36, 2),IR(45427, 5),IR(1, 0)}, // SMax in glsl_std_450
    {43,IR(33, 3),IR(45432, 7),IR(1, 0)}, // FClamp in glsl_std_450
    {44,IR(33, 3),IR(45439, 7),IR(1, 0)}, // UClamp in glsl_std_450
    {45,IR(33, 3),IR(45446, 7),IR(1, 0)}, // SClamp in glsl_std_450
    {46,IR(33, 3),IR(45453, 5),IR(1, 0)}, // FMix in glsl_std_450
    {47,IR(33, 3),IR(45458, 5),IR(1, 0)}, // IMix in glsl_std_450
    {48,IR(36, 2),IR(45463, 5),IR(1, 0)}, // Step in glsl_std_450
    {49,IR(33, 3),IR(45468, 11),IR(1, 0)}, // SmoothStep in glsl_std_450
    {50,IR(33, 3),IR(45479, 4),IR(1, 0)}, // Fma in glsl_std_450
    {51,IR(36, 2),IR(45483, 6),IR(1, 0)}, // Frexp in glsl_std_450
    {52,IR(10, 1),IR(45489, 12),IR(1, 0)}, // FrexpStruct in glsl_std_450
    {53,IR(36, 2),IR(45501, 6),IR(1, 0)}, // Ldexp in glsl_std_450
    {54,IR(10, 1),IR(45507, 13),IR(1, 0)}, // PackSnorm4x8 in glsl_std_450
    {55,IR(10, 1),IR(45520, 13),IR(1, 0)}, // PackUnorm4x8 in glsl_std_450
    {56,IR(10, 1),IR(45533, 14),IR(1, 0)}, // PackSnorm2x16 in glsl_std_450
    {57,IR(10, 1),IR(45547, 14),IR(1, 0)}, // PackUnorm2x16 in glsl_std_450
    {58,IR(10, 1),IR(45561, 13),IR(1, 0)}, // PackHalf2x16 in glsl_std_450
    {59,IR(10, 1),IR(45574, 15),IR(299, 1)}, // PackDouble2x32 in glsl_std_450
    {60,IR(10, 1),IR(45589, 16),IR(1, 0)}, // UnpackSnorm2x16 in glsl_std_450
    {61,IR(10, 1),IR(45605, 16),IR(1, 0)}, // UnpackUnorm2x16 in glsl_std_450
    {62,IR(10, 1),IR(45621, 15),IR(1, 0)}, // UnpackHalf2x16 in glsl_std_450
    {63,IR(10, 1),IR(45636, 15),IR(1, 0)}, // UnpackSnorm4x8 in glsl_std_450
    {64,IR(10, 1),IR(45651, 15),IR(1, 0)}, // UnpackUnorm4x8 in glsl_std_450
    {65,IR(10, 1),IR(45666, 17),IR(299, 1)}, // UnpackDouble2x32 in glsl_std_450
    {66,IR(10, 1),IR(45683, 7),IR(1, 0)}, // Length in glsl_std_450
    {67,IR(36, 2),IR(45690, 9),IR(1, 0)}, // Distance in glsl_std_450
    {68,IR(36, 2),IR(45699, 6),IR(1, 0)}, // Cross in glsl_std_450
    {69,IR(10, 1),IR(45705, 10),IR(1, 0)}, // Normalize in glsl_std_450
    {70,IR(33, 3),IR(45715, 12),IR(1, 0)}, // FaceForward in glsl_std_450
    {71,IR(36, 2),IR(45727, 8),IR(1, 0)}, // Reflect in glsl_std_450
    {72,IR(33, 3),IR(45735, 8),IR(1, 0)}, // Refract in glsl_std_450
    {73,IR(10, 1),IR(45743, 9),IR(1, 0)}, // FindILsb in glsl_std_450
    {74,IR(10, 1),IR(45752, 9),IR(1, 0)}, // FindSMsb in glsl_std_450
    {75,IR(10, 1),IR(45761, 9),IR(1, 0)}, // FindUMsb in glsl_std_450
    {76,IR(10, 1),IR(45770, 22),IR(300, 1)}, // InterpolateAtCentroid in glsl_std_450
    {77,IR(36, 2),IR(45792, 20),IR(300, 1)}, // InterpolateAtSample in glsl_std_450
    {78,IR(36, 2),IR(45812, 20),IR(300, 1)}, // InterpolateAtOffset in glsl_std_450
    {79,IR(36, 2),IR(45832, 5),IR(1, 0)}, // NMin in glsl_std_450
    {80,IR(36, 2),IR(45837, 5),IR(1, 0)}, // NMax in glsl_std_450
    {81,IR(33, 3),IR(45842, 7),IR(1, 0)}, // NClamp in glsl_std_450
    {1,IR(374, 5),IR(4492, 7),IR(1, 0)}, // Kernel in nonsemantic_clspvreflection
    {2,IR(825, 5),IR(45849, 13),IR(1, 0)}, // ArgumentInfo in nonsemantic_clspvreflection
    {3,IR(830, 5),IR(45862, 22),IR(1, 0)}, // ArgumentStorageBuffer in nonsemantic_clspvreflection
    {4,IR(830, 5),IR(45884, 16),IR(1, 0)}, // ArgumentUniform in nonsemantic_clspvreflection
    {5,IR(518, 7),IR(45900, 25),IR(1, 0)}, // ArgumentPodStorageBuffer in nonsemantic_clspvreflection
    {6,IR(518, 7),IR(45925, 19),IR(1, 0)}, // ArgumentPodUniform in nonsemantic_clspvreflection
    {7,IR(830, 5),IR(45944, 24),IR(1, 0)}, // ArgumentPodPushConstant in nonsemantic_clspvreflection
    {8,IR(830, 5),IR(45968, 21),IR(1, 0)}, // ArgumentSampledImage in nonsemantic_clspvreflection
    {9,IR(830, 5),IR(45989, 21),IR(1, 0)}, // ArgumentStorageImage in nonsemantic_clspvreflection
    {10,IR(830, 5),IR(46010, 16),IR(1, 0)}, // ArgumentSampler in nonsemantic_clspvreflection
    {11,IR(830, 5),IR(46026, 18),IR(1, 0)}, // ArgumentWorkgroup in nonsemantic_clspvreflection
    {12,IR(33, 3),IR(46044, 26),IR(1, 0)}, // SpecConstantWorkgroupSize in nonsemantic_clspvreflection
    {13,IR(33, 3),IR(46070, 25),IR(1, 0)}, // SpecConstantGlobalOffset in nonsemantic_clspvreflection
    {14,IR(10, 1),IR(46095, 20),IR(1, 0)}, // SpecConstantWorkDim in nonsemantic_clspvreflection
    {15,IR(36, 2),IR(46115, 25),IR(1, 0)}, // PushConstantGlobalOffset in nonsemantic_clspvreflection
    {16,IR(36, 2),IR(46140, 30),IR(1, 0)}, // PushConstantEnqueuedLocalSize in nonsemantic_clspvreflection
    {17,IR(36, 2),IR(46170, 23),IR(1, 0)}, // PushConstantGlobalSize in nonsemantic_clspvreflection
    {18,IR(36, 2),IR(46193, 25),IR(1, 0)}, // PushConstantRegionOffset in nonsemantic_clspvreflection
    {19,IR(36, 2),IR(46218, 26),IR(1, 0)}, // PushConstantNumWorkgroups in nonsemantic_clspvreflection
    {20,IR(36, 2),IR(46244, 30),IR(1, 0)}, // PushConstantRegionGroupOffset in nonsemantic_clspvreflection
    {21,IR(33, 3),IR(46274, 26),IR(1, 0)}, // ConstantDataStorageBuffer in nonsemantic_clspvreflection
    {22,IR(33, 3),IR(46300, 20),IR(1, 0)}, // ConstantDataUniform in nonsemantic_clspvreflection
    {23,IR(33, 3),IR(7917, 15),IR(1, 0)}, // LiteralSampler in nonsemantic_clspvreflection
    {24,IR(296, 4),IR(46320, 30),IR(1, 0)}, // PropertyRequiredWorkgroupSize in nonsemantic_clspvreflection
    {25,IR(10, 1),IR(46350, 28),IR(1, 0)}, // SpecConstantSubgroupMaxSize in nonsemantic_clspvreflection
    {26,IR(830, 5),IR(46378, 28),IR(1, 0)}, // ArgumentPointerPushConstant in nonsemantic_clspvreflection
    {27,IR(518, 7),IR(46406, 23),IR(1, 0)}, // ArgumentPointerUniform in nonsemantic_clspvreflection
    {28,IR(33, 3),IR(46429, 35),IR(1, 0)}, // ProgramScopeVariablesStorageBuffer in nonsemantic_clspvreflection
    {29,IR(33, 3),IR(46464, 38),IR(1, 0)}, // ProgramScopeVariablePointerRelocation in nonsemantic_clspvreflection
    {30,IR(296, 4),IR(46502, 42),IR(1, 0)}, // ImageArgumentInfoChannelOrderPushConstant in nonsemantic_clspvreflection
    {31,IR(296, 4),IR(46544, 45),IR(1, 0)}, // ImageArgumentInfoChannelDataTypePushConstant in nonsemantic_clspvreflection
    {32,IR(489, 6),IR(46589, 37),IR(1, 0)}, // ImageArgumentInfoChannelOrderUniform in nonsemantic_clspvreflection
    {33,IR(489, 6),IR(46626, 40),IR(1, 0)}, // ImageArgumentInfoChannelDataTypeUniform in nonsemantic_clspvreflection
    {34,IR(830, 5),IR(46666, 27),IR(1, 0)}, // ArgumentStorageTexelBuffer in nonsemantic_clspvreflection
    {35,IR(830, 5),IR(46693, 27),IR(1, 0)}, // ArgumentUniformTexelBuffer in nonsemantic_clspvreflection
    {36,IR(33, 3),IR(46720, 32),IR(1, 0)}, // ConstantDataPointerPushConstant in nonsemantic_clspvreflection
    {37,IR(33, 3),IR(46752, 40),IR(1, 0)}, // ProgramScopeVariablePointerPushConstant in nonsemantic_clspvreflection
    {38,IR(816, 3),IR(46792, 11),IR(1, 0)}, // PrintfInfo in nonsemantic_clspvreflection
    {39,IR(33, 3),IR(46803, 26),IR(1, 0)}, // PrintfBufferStorageBuffer in nonsemantic_clspvreflection
    {40,IR(33, 3),IR(46829, 32),IR(1, 0)}, // PrintfBufferPointerPushConstant in nonsemantic_clspvreflection
    {41,IR(296, 4),IR(46861, 34),IR(1, 0)}, // NormalizedSamplerMaskPushConstant in nonsemantic_clspvreflection
    {42,IR(36, 2),IR(46895, 22),IR(1, 0)}, // WorkgroupVariableSize in nonsemantic_clspvreflection
    {0,IR(0, 0),IR(44319, 14),IR(1, 0)}, // DebugInfoNone in nonsemantic_shader_debuginfo_100
    {1,IR(296, 4),IR(44333, 21),IR(1, 0)}, // DebugCompilationUnit in nonsemantic_shader_debuginfo_100
    {2,IR(296, 4),IR(44406, 15),IR(1, 0)}, // DebugTypeBasic in nonsemantic_shader_debuginfo_100
    {3,IR(33, 3),IR(44455, 17),IR(1, 0)}, // DebugTypePointer in nonsemantic_shader_debuginfo_100
    {4,IR(36, 2),IR(44510, 19),IR(1, 0)}, // DebugTypeQualifier in nonsemantic_shader_debuginfo_100
    {5,IR(168, 2),IR(44529, 15),IR(1, 0)}, // DebugTypeArray in nonsemantic_shader_debuginfo_100
    {6,IR(36, 2),IR(44544, 16),IR(1, 0)}, // DebugTypeVector in nonsemantic_shader_debuginfo_100
    {7,IR(489, 6),IR(44560, 13),IR(1, 0)}, // DebugTypedef in nonsemantic_shader_debuginfo_100
    {8,IR(816, 3),IR(44573, 18),IR(1, 0)}, // DebugTypeFunction in nonsemantic_shader_debuginfo_100
    {9,IR(835, 9),IR(44591, 14),IR(1, 0)}, // DebugTypeEnum in nonsemantic_shader_debuginfo_100
    {10,IR(844, 10),IR(44643, 19),IR(1, 0)}, // DebugTypeComposite in nonsemantic_shader_debuginfo_100
    {11,IR(854, 9),IR(44662, 16),IR(1, 0)}, // DebugTypeMember in nonsemantic_shader_debuginfo_100
    {12,IR(296, 4),IR(44678, 21),IR(1, 0)}, // DebugTypeInheritance in nonsemantic_shader_debuginfo_100
    {13,IR(36, 2),IR(44699, 21),IR(1, 0)}, // DebugTypePtrToMember in nonsemantic_shader_debuginfo_100
    {14,IR(168, 2),IR(44720, 18),IR(1, 0)}, // DebugTypeTemplate in nonsemantic_shader_debuginfo_100
    {15,IR(489, 6),IR(44738, 27),IR(1, 0)}, // DebugTypeTemplateParameter in nonsemantic_shader_debuginfo_100
    {16,IR(598, 5),IR(44765, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in nonsemantic_shader_debuginfo_100
    {17,IR(863, 5),IR(44800, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in nonsemantic_shader_debuginfo_100
    {18,IR(868, 10),IR(44831, 20),IR(1, 0)}, // DebugGlobalVariable in nonsemantic_shader_debuginfo_100
    {19,IR(435, 8),IR(44851, 25),IR(1, 0)}, // DebugFunctionDeclaration in nonsemantic_shader_debuginfo_100
    {20,IR(868, 10),IR(44876, 14),IR(1, 0)}, // DebugFunction in nonsemantic_shader_debuginfo_100
    {21,IR(830, 5),IR(44890, 18),IR(1, 0)}, // DebugLexicalBlock in nonsemantic_shader_debuginfo_100
    {22,IR(33, 3),IR(44908, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in nonsemantic_shader_debuginfo_100
    {23,IR(804, 2),IR(44939, 11),IR(1, 0)}, // DebugScope in nonsemantic_shader_debuginfo_100
    {24,IR(0, 0),IR(44950, 13),IR(1, 0)}, // DebugNoScope in nonsemantic_shader_debuginfo_100
    {25,IR(878, 3),IR(44963, 15),IR(1, 0)}, // DebugInlinedAt in nonsemantic_shader_debuginfo_100
    {26,IR(881, 8),IR(45020, 19),IR(1, 0)}, // DebugLocalVariable in nonsemantic_shader_debuginfo_100
    {27,IR(36, 2),IR(45039, 21),IR(1, 0)}, // DebugInlinedVariable in nonsemantic_shader_debuginfo_100
    {28,IR(889, 4),IR(45060, 13),IR(1, 0)}, // DebugDeclare in nonsemantic_shader_debuginfo_100
    {29,IR(889, 4),IR(45073, 11),IR(1, 0)}, // DebugValue in nonsemantic_shader_debuginfo_100
    {30,IR(168, 2),IR(45117, 15),IR(1, 0)}, // DebugOperation in nonsemantic_shader_debuginfo_100
    {31,IR(670, 1),IR(45132, 16),IR(1, 0)}, // DebugExpression in nonsemantic_shader_debuginfo_100
    {32,IR(541, 4),IR(45148, 14),IR(1, 0)}, // DebugMacroDef in nonsemantic_shader_debuginfo_100
    {33,IR(33, 3),IR(45162, 16),IR(1, 0)}, // DebugMacroUndef in nonsemantic_shader_debuginfo_100
    {34,IR(470, 7),IR(46917, 20),IR(1, 0)}, // DebugImportedEntity in nonsemantic_shader_debuginfo_100
    {35,IR(804, 2),IR(46937, 12),IR(1, 0)}, // DebugSource in nonsemantic_shader_debuginfo_100
    {101,IR(36, 2),IR(46949, 24),IR(1, 0)}, // DebugFunctionDefinition in nonsemantic_shader_debuginfo_100
    {102,IR(10, 1),IR(46973, 21),IR(1, 0)}, // DebugSourceContinued in nonsemantic_shader_debuginfo_100
    {103,IR(598, 5),IR(46994, 10),IR(1, 0)}, // DebugLine in nonsemantic_shader_debuginfo_100
    {104,IR(0, 0),IR(47004, 12),IR(1, 0)}, // DebugNoLine in nonsemantic_shader_debuginfo_100
    {105,IR(36, 2),IR(47016, 21),IR(1, 0)}, // DebugBuildIdentifier in nonsemantic_shader_debuginfo_100
    {106,IR(10, 1),IR(47037, 17),IR(1, 0)}, // DebugStoragePath in nonsemantic_shader_debuginfo_100
    {107,IR(296, 4),IR(47054, 16),IR(1, 0)}, // DebugEntryPoint in nonsemantic_shader_debuginfo_100
    {108,IR(33, 3),IR(47070, 16),IR(1, 0)}, // DebugTypeMatrix in nonsemantic_shader_debuginfo_100
    {1,IR(688, 9),IR(47086, 14),IR(1, 0)}, // Configuration in nonsemantic_vkspreflection
    {2,IR(10, 1),IR(47100, 13),IR(1, 0)}, // StartCounter in nonsemantic_vkspreflection
    {3,IR(10, 1),IR(47113, 12),IR(1, 0)}, // StopCounter in nonsemantic_vkspreflection
    {4,IR(296, 4),IR(47125, 14),IR(1, 0)}, // PushConstants in nonsemantic_vkspreflection
    {5,IR(33, 3),IR(47139, 23),IR(1, 0)}, // SpecializationMapEntry in nonsemantic_vkspreflection
    {6,IR(893, 15),IR(47162, 20),IR(1, 0)}, // DescriptorSetBuffer in nonsemantic_vkspreflection
    {7,IR(908, 33),IR(47182, 19),IR(1, 0)}, // DescriptorSetImage in nonsemantic_vkspreflection
    {8,IR(941, 19),IR(47201, 21),IR(1, 0)}, // DescriptorSetSampler in nonsemantic_vkspreflection
    {0,IR(0, 0),IR(44319, 14),IR(1, 0)}, // DebugInfoNone in opencl_debuginfo_100
    {1,IR(960, 4),IR(44333, 21),IR(1, 0)}, // DebugCompilationUnit in opencl_debuginfo_100
    {2,IR(964, 3),IR(44406, 15),IR(1, 0)}, // DebugTypeBasic in opencl_debuginfo_100
    {3,IR(967, 3),IR(44455, 17),IR(1, 0)}, // DebugTypePointer in opencl_debuginfo_100
    {4,IR(970, 2),IR(44510, 19),IR(1, 0)}, // DebugTypeQualifier in opencl_debuginfo_100
    {5,IR(168, 2),IR(44529, 15),IR(1, 0)}, // DebugTypeArray in opencl_debuginfo_100
    {6,IR(261, 2),IR(44544, 16),IR(1, 0)}, // DebugTypeVector in opencl_debuginfo_100
    {7,IR(722, 6),IR(44560, 13),IR(1, 0)}, // DebugTypedef in opencl_debuginfo_100
    {8,IR(972, 3),IR(44573, 18),IR(1, 0)}, // DebugTypeFunction in opencl_debuginfo_100
    {9,IR(975, 9),IR(44591, 14),IR(1, 0)}, // DebugTypeEnum in opencl_debuginfo_100
    {10,IR(984, 10),IR(44643, 19),IR(1, 0)}, // DebugTypeComposite in opencl_debuginfo_100
    {11,IR(994, 10),IR(44662, 16),IR(1, 0)}, // DebugTypeMember in opencl_debuginfo_100
    {12,IR(1004, 5),IR(44678, 21),IR(1, 0)}, // DebugTypeInheritance in opencl_debuginfo_100
    {13,IR(36, 2),IR(44699, 21),IR(1, 0)}, // DebugTypePtrToMember in opencl_debuginfo_100
    {14,IR(168, 2),IR(44720, 18),IR(1, 0)}, // DebugTypeTemplate in opencl_debuginfo_100
    {15,IR(761, 6),IR(44738, 27),IR(1, 0)}, // DebugTypeTemplateParameter in opencl_debuginfo_100
    {16,IR(767, 5),IR(44765, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in opencl_debuginfo_100
    {17,IR(772, 5),IR(44800, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in opencl_debuginfo_100
    {18,IR(994, 10),IR(44831, 20),IR(1, 0)}, // DebugGlobalVariable in opencl_debuginfo_100
    {19,IR(1009, 8),IR(44851, 25),IR(1, 0)}, // DebugFunctionDeclaration in opencl_debuginfo_100
    {20,IR(1017, 11),IR(44876, 14),IR(1, 0)}, // DebugFunction in opencl_debuginfo_100
    {21,IR(796, 5),IR(44890, 18),IR(1, 0)}, // DebugLexicalBlock in opencl_debuginfo_100
    {22,IR(801, 3),IR(44908, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in opencl_debuginfo_100
    {23,IR(804, 2),IR(44939, 11),IR(1, 0)}, // DebugScope in opencl_debuginfo_100
    {24,IR(0, 0),IR(44950, 13),IR(1, 0)}, // DebugNoScope in opencl_debuginfo_100
    {25,IR(806, 3),IR(44963, 15),IR(1, 0)}, // DebugInlinedAt in opencl_debuginfo_100
    {26,IR(1028, 8),IR(45020, 19),IR(1, 0)}, // DebugLocalVariable in opencl_debuginfo_100
    {27,IR(36, 2),IR(45039, 21),IR(1, 0)}, // DebugInlinedVariable in opencl_debuginfo_100
    {28,IR(33, 3),IR(45060, 13),IR(1, 0)}, // DebugDeclare in opencl_debuginfo_100
    {29,IR(889, 4),IR(45073, 11),IR(1, 0)}, // DebugValue in opencl_debuginfo_100
    {30,IR(1036, 2),IR(45117, 15),IR(1, 0)}, // DebugOperation in opencl_debuginfo_100
    {31,IR(670, 1),IR(45132, 16),IR(1, 0)}, // DebugExpression in opencl_debuginfo_100
    {32,IR(821, 4),IR(45148, 14),IR(1, 0)}, // DebugMacroDef in opencl_debuginfo_100
    {33,IR(801, 3),IR(45162, 16),IR(1, 0)}, // DebugMacroUndef in opencl_debuginfo_100
    {34,IR(1038, 7),IR(46917, 20),IR(1, 0)}, // DebugImportedEntity in opencl_debuginfo_100
    {35,IR(804, 2),IR(46937, 12),IR(1, 0)}, // DebugSource in opencl_debuginfo_100
    {36,IR(1045, 8),IR(47522, 17),IR(1, 0)}, // DebugModuleINTEL in opencl_debuginfo_100
    {0,IR(10, 1),IR(47539, 5),IR(1, 0)}, // acos in opencl_std_100
    {1,IR(10, 1),IR(47544, 6),IR(1, 0)}, // acosh in opencl_std_100
    {2,IR(10, 1),IR(47550, 7),IR(1, 0)}, // acospi in opencl_std_100
    {3,IR(10, 1),IR(47557, 5),IR(1, 0)}, // asin in opencl_std_100
    {4,IR(10, 1),IR(47562, 6),IR(1, 0)}, // asinh in opencl_std_100
    {5,IR(10, 1),IR(47568, 7),IR(1, 0)}, // asinpi in opencl_std_100
    {6,IR(10, 1),IR(47575, 5),IR(1, 0)}, // atan in opencl_std_100
    {7,IR(36, 2),IR(47580, 6),IR(1, 0)}, // atan2 in opencl_std_100
    {8,IR(10, 1),IR(47586, 6),IR(1, 0)}, // atanh in opencl_std_100
    {9,IR(10, 1),IR(47592, 7),IR(1, 0)}, // atanpi in opencl_std_100
    {10,IR(36, 2),IR(47599, 8),IR(1, 0)}, // atan2pi in opencl_std_100
    {11,IR(10, 1),IR(47607, 5),IR(1, 0)}, // cbrt in opencl_std_100
    {12,IR(10, 1),IR(47612, 5),IR(1, 0)}, // ceil in opencl_std_100
    {13,IR(36, 2),IR(47617, 9),IR(1, 0)}, // copysign in opencl_std_100
    {14,IR(10, 1),IR(47626, 4),IR(1, 0)}, // cos in opencl_std_100
    {15,IR(10, 1),IR(47630, 5),IR(1, 0)}, // cosh in opencl_std_100
    {16,IR(10, 1),IR(47635, 6),IR(1, 0)}, // cospi in opencl_std_100
    {17,IR(10, 1),IR(47641, 5),IR(1, 0)}, // erfc in opencl_std_100
    {18,IR(10, 1),IR(47646, 4),IR(1, 0)}, // erf in opencl_std_100
    {19,IR(10, 1),IR(47650, 4),IR(1, 0)}, // exp in opencl_std_100
    {20,IR(10, 1),IR(47654, 5),IR(1, 0)}, // exp2 in opencl_std_100
    {21,IR(10, 1),IR(47659, 6),IR(1, 0)}, // exp10 in opencl_std_100
    {22,IR(10, 1),IR(47665, 6),IR(1, 0)}, // expm1 in opencl_std_100
    {23,IR(10, 1),IR(47671, 5),IR(1, 0)}, // fabs in opencl_std_100
    {24,IR(36, 2),IR(47676, 5),IR(1, 0)}, // fdim in opencl_std_100
    {25,IR(10, 1),IR(47681, 6),IR(1, 0)}, // floor in opencl_std_100
    {26,IR(33, 3),IR(47687, 4),IR(1, 0)}, // fma in opencl_std_100
    {27,IR(36, 2),IR(47691, 5),IR(1, 0)}, // fmax in opencl_std_100
    {28,IR(36, 2),IR(47696, 5),IR(1, 0)}, // fmin in opencl_std_100
    {29,IR(36, 2),IR(47701, 5),IR(1, 0)}, // fmod in opencl_std_100
    {30,IR(36, 2),IR(47706, 6),IR(1, 0)}, // fract in opencl_std_100
    {31,IR(36, 2),IR(47712, 6),IR(1, 0)}, // frexp in opencl_std_100
    {32,IR(36, 2),IR(47718, 6),IR(1, 0)}, // hypot in opencl_std_100
    {33,IR(10, 1),IR(47724, 6),IR(1, 0)}, // ilogb in opencl_std_100
    {34,IR(36, 2),IR(47730, 6),IR(1, 0)}, // ldexp in opencl_std_100
    {35,IR(10, 1),IR(47736, 7),IR(1, 0)}, // lgamma in opencl_std_100
    {36,IR(36, 2),IR(47743, 9),IR(1, 0)}, // lgamma_r in opencl_std_100
    {37,IR(10, 1),IR(47752, 4),IR(1, 0)}, // log in opencl_std_100
    {38,IR(10, 1),IR(47756, 5),IR(1, 0)}, // log2 in opencl_std_100
    {39,IR(10, 1),IR(47761, 6),IR(1, 0)}, // log10 in opencl_std_100
    {40,IR(10, 1),IR(47767, 6),IR(1, 0)}, // log1p in opencl_std_100
    {41,IR(10, 1),IR(47773, 5),IR(1, 0)}, // logb in opencl_std_100
    {42,IR(33, 3),IR(47778, 4),IR(1, 0)}, // mad in opencl_std_100
    {43,IR(36, 2),IR(47782, 7),IR(1, 0)}, // maxmag in opencl_std_100
    {44,IR(36, 2),IR(47789, 7),IR(1, 0)}, // minmag in opencl_std_100
    {45,IR(36, 2),IR(47796, 5),IR(1, 0)}, // modf in opencl_std_100
    {46,IR(10, 1),IR(47801, 4),IR(1, 0)}, // nan in opencl_std_100
    {47,IR(36, 2),IR(47805, 10),IR(1, 0)}, // nextafter in opencl_std_100
    {48,IR(36, 2),IR(47815, 4),IR(1, 0)}, // pow in opencl_std_100
    {49,IR(36, 2),IR(47819, 5),IR(1, 0)}, // pown in opencl_std_100
    {50,IR(36, 2),IR(47824, 5),IR(1, 0)}, // powr in opencl_std_100
    {51,IR(36, 2),IR(47829, 10),IR(1, 0)}, // remainder in opencl_std_100
    {52,IR(33, 3),IR(47839, 7),IR(1, 0)}, // remquo in opencl_std_100
    {53,IR(10, 1),IR(47846, 5),IR(1, 0)}, // rint in opencl_std_100
    {54,IR(36, 2),IR(47851, 6),IR(1, 0)}, // rootn in opencl_std_100
    {55,IR(10, 1),IR(47857, 6),IR(1, 0)}, // round in opencl_std_100
    {56,IR(10, 1),IR(47863, 6),IR(1, 0)}, // rsqrt in opencl_std_100
    {57,IR(10, 1),IR(47869, 4),IR(1, 0)}, // sin in opencl_std_100
    {58,IR(36, 2),IR(47873, 7),IR(1, 0)}, // sincos in opencl_std_100
    {59,IR(10, 1),IR(47880, 5),IR(1, 0)}, // sinh in opencl_std_100
    {60,IR(10, 1),IR(47885, 6),IR(1, 0)}, // sinpi in opencl_std_100
    {61,IR(10, 1),IR(47891, 5),IR(1, 0)}, // sqrt in opencl_std_100
    {62,IR(10, 1),IR(47896, 4),IR(1, 0)}, // tan in opencl_std_100
    {63,IR(10, 1),IR(47900, 5),IR(1, 0)}, // tanh in opencl_std_100
    {64,IR(10, 1),IR(47905, 6),IR(1, 0)}, // tanpi in opencl_std_100
    {65,IR(10, 1),IR(47911, 7),IR(1, 0)}, // tgamma in opencl_std_100
    {66,IR(10, 1),IR(47918, 6),IR(1, 0)}, // trunc in opencl_std_100
    {67,IR(10, 1),IR(47924, 9),IR(1, 0)}, // half_cos in opencl_std_100
    {68,IR(36, 2),IR(47933, 12),IR(1, 0)}, // half_divide in opencl_std_100
    {69,IR(10, 1),IR(47945, 9),IR(1, 0)}, // half_exp in opencl_std_100
    {70,IR(10, 1),IR(47954, 10),IR(1, 0)}, // half_exp2 in opencl_std_100
    {71,IR(10, 1),IR(47964, 11),IR(1, 0)}, // half_exp10 in opencl_std_100
    {72,IR(10, 1),IR(47975, 9),IR(1, 0)}, // half_log in opencl_std_100
    {73,IR(10, 1),IR(47984, 10),IR(1, 0)}, // half_log2 in opencl_std_100
    {74,IR(10, 1),IR(47994, 11),IR(1, 0)}, // half_log10 in opencl_std_100
    {75,IR(36, 2),IR(48005, 10),IR(1, 0)}, // half_powr in opencl_std_100
    {76,IR(10, 1),IR(48015, 11),IR(1, 0)}, // half_recip in opencl_std_100
    {77,IR(10, 1),IR(48026, 11),IR(1, 0)}, // half_rsqrt in opencl_std_100
    {78,IR(10, 1),IR(48037, 9),IR(1, 0)}, // half_sin in opencl_std_100
    {79,IR(10, 1),IR(48046, 10),IR(1, 0)}, // half_sqrt in opencl_std_100
    {80,IR(10, 1),IR(48056, 9),IR(1, 0)}, // half_tan in opencl_std_100
    {81,IR(10, 1),IR(48065, 11),IR(1, 0)}, // native_cos in opencl_std_100
    {82,IR(36, 2),IR(48076, 14),IR(1, 0)}, // native_divide in opencl_std_100
    {83,IR(10, 1),IR(48090, 11),IR(1, 0)}, // native_exp in opencl_std_100
    {84,IR(10, 1),IR(48101, 12),IR(1, 0)}, // native_exp2 in opencl_std_100
    {85,IR(10, 1),IR(48113, 13),IR(1, 0)}, // native_exp10 in opencl_std_100
    {86,IR(10, 1),IR(48126, 11),IR(1, 0)}, // native_log in opencl_std_100
    {87,IR(10, 1),IR(48137, 12),IR(1, 0)}, // native_log2 in opencl_std_100
    {88,IR(10, 1),IR(48149, 13),IR(1, 0)}, // native_log10 in opencl_std_100
    {89,IR(36, 2),IR(48162, 12),IR(1, 0)}, // native_powr in opencl_std_100
    {90,IR(10, 1),IR(48174, 13),IR(1, 0)}, // native_recip in opencl_std_100
    {91,IR(10, 1),IR(48187, 13),IR(1, 0)}, // native_rsqrt in opencl_std_100
    {92,IR(10, 1),IR(48200, 11),IR(1, 0)}, // native_sin in opencl_std_100
    {93,IR(10, 1),IR(48211, 12),IR(1, 0)}, // native_sqrt in opencl_std_100
    {94,IR(10, 1),IR(48223, 11),IR(1, 0)}, // native_tan in opencl_std_100
    {95,IR(33, 3),IR(48234, 7),IR(1, 0)}, // fclamp in opencl_std_100
    {96,IR(10, 1),IR(48241, 8),IR(1, 0)}, // degrees in opencl_std_100
    {97,IR(36, 2),IR(48249, 12),IR(1, 0)}, // fmax_common in opencl_std_100
    {98,IR(36, 2),IR(48261, 12),IR(1, 0)}, // fmin_common in opencl_std_100
    {99,IR(33, 3),IR(48273, 4),IR(1, 0)}, // mix in opencl_std_100
    {100,IR(10, 1),IR(48277, 8),IR(1, 0)}, // radians in opencl_std_100
    {101,IR(36, 2),IR(48285, 5),IR(1, 0)}, // step in opencl_std_100
    {102,IR(33, 3),IR(48290, 11),IR(1, 0)}, // smoothstep in opencl_std_100
    {103,IR(10, 1),IR(48301, 5),IR(1, 0)}, // sign in opencl_std_100
    {104,IR(36, 2),IR(48306, 6),IR(1, 0)}, // cross in opencl_std_100
    {105,IR(36, 2),IR(48312, 9),IR(1, 0)}, // distance in opencl_std_100
    {106,IR(10, 1),IR(48321, 7),IR(1, 0)}, // length in opencl_std_100
    {107,IR(10, 1),IR(48328, 10),IR(1, 0)}, // normalize in opencl_std_100
    {108,IR(36, 2),IR(48338, 14),IR(1, 0)}, // fast_distance in opencl_std_100
    {109,IR(10, 1),IR(48352, 12),IR(1, 0)}, // fast_length in opencl_std_100
    {110,IR(10, 1),IR(48364, 15),IR(1, 0)}, // fast_normalize in opencl_std_100
    {141,IR(10, 1),IR(48379, 6),IR(1, 0)}, // s_abs in opencl_std_100
    {142,IR(36, 2),IR(48385, 11),IR(1, 0)}, // s_abs_diff in opencl_std_100
    {143,IR(36, 2),IR(48396, 10),IR(1, 0)}, // s_add_sat in opencl_std_100
    {144,IR(36, 2),IR(48406, 10),IR(1, 0)}, // u_add_sat in opencl_std_100
    {145,IR(36, 2),IR(48416, 7),IR(1, 0)}, // s_hadd in opencl_std_100
    {146,IR(36, 2),IR(48423, 7),IR(1, 0)}, // u_hadd in opencl_std_100
    {147,IR(36, 2),IR(48430, 8),IR(1, 0)}, // s_rhadd in opencl_std_100
    {148,IR(36, 2),IR(48438, 8),IR(1, 0)}, // u_rhadd in opencl_std_100
    {149,IR(33, 3),IR(48446, 8),IR(1, 0)}, // s_clamp in opencl_std_100
    {150,IR(33, 3),IR(48454, 8),IR(1, 0)}, // u_clamp in opencl_std_100
    {151,IR(10, 1),IR(48462, 4),IR(1, 0)}, // clz in opencl_std_100
    {152,IR(10, 1),IR(48466, 4),IR(1, 0)}, // ctz in opencl_std_100
    {153,IR(33, 3),IR(48470, 9),IR(1, 0)}, // s_mad_hi in opencl_std_100
    {154,IR(33, 3),IR(48479, 10),IR(1, 0)}, // u_mad_sat in opencl_std_100
    {155,IR(33, 3),IR(48489, 10),IR(1, 0)}, // s_mad_sat in opencl_std_100
    {156,IR(36, 2),IR(48499, 6),IR(1, 0)}, // s_max in opencl_std_100
    {157,IR(36, 2),IR(48505, 6),IR(1, 0)}, // u_max in opencl_std_100
    {158,IR(36, 2),IR(48511, 6),IR(1, 0)}, // s_min in opencl_std_100
    {159,IR(36, 2),IR(48517, 6),IR(1, 0)}, // u_min in opencl_std_100
    {160,IR(36, 2),IR(48523, 9),IR(1, 0)}, // s_mul_hi in opencl_std_100
    {161,IR(36, 2),IR(48532, 7),IR(1, 0)}, // rotate in opencl_std_100
    {162,IR(36, 2),IR(48539, 10),IR(1, 0)}, // s_sub_sat in opencl_std_100
    {163,IR(36, 2),IR(48549, 10),IR(1, 0)}, // u_sub_sat in opencl_std_100
    {164,IR(36, 2),IR(48559, 11),IR(1, 0)}, // u_upsample in opencl_std_100
    {165,IR(36, 2),IR(48570, 11),IR(1, 0)}, // s_upsample in opencl_std_100
    {166,IR(10, 1),IR(48581, 9),IR(1, 0)}, // popcount in opencl_std_100
    {167,IR(33, 3),IR(48590, 8),IR(1, 0)}, // s_mad24 in opencl_std_100
    {168,IR(33, 3),IR(48598, 8),IR(1, 0)}, // u_mad24 in opencl_std_100
    {169,IR(36, 2),IR(48606, 8),IR(1, 0)}, // s_mul24 in opencl_std_100
    {170,IR(36, 2),IR(48614, 8),IR(1, 0)}, // u_mul24 in opencl_std_100
    {171,IR(1053, 3),IR(48622, 7),IR(1, 0)}, // vloadn in opencl_std_100
    {172,IR(33, 3),IR(48629, 8),IR(1, 0)}, // vstoren in opencl_std_100
    {173,IR(36, 2),IR(48637, 11),IR(1, 0)}, // vload_half in opencl_std_100
    {174,IR(1053, 3),IR(48648, 12),IR(1, 0)}, // vload_halfn in opencl_std_100
    {175,IR(33, 3),IR(48660, 12),IR(1, 0)}, // vstore_half in opencl_std_100
    {176,IR(1056, 4),IR(48672, 14),IR(1, 0)}, // vstore_half_r in opencl_std_100
    {177,IR(33, 3),IR(48686, 13),IR(1, 0)}, // vstore_halfn in opencl_std_100
    {178,IR(1056, 4),IR(48699, 15),IR(1, 0)}, // vstore_halfn_r in opencl_std_100
    {179,IR(1053, 3),IR(48714, 13),IR(1, 0)}, // vloada_halfn in opencl_std_100
    {180,IR(33, 3),IR(48727, 14),IR(1, 0)}, // vstorea_halfn in opencl_std_100
    {181,IR(1056, 4),IR(48741, 16),IR(1, 0)}, // vstorea_halfn_r in opencl_std_100
    {182,IR(36, 2),IR(48757, 8),IR(1, 0)}, // shuffle in opencl_std_100
    {183,IR(33, 3),IR(48765, 9),IR(1, 0)}, // shuffle2 in opencl_std_100
    {184,IR(168, 2),IR(48774, 7),IR(1, 0)}, // printf in opencl_std_100
    {185,IR(36, 2),IR(48781, 9),IR(1, 0)}, // prefetch in opencl_std_100
    {186,IR(33, 3),IR(48790, 10),IR(1, 0)}, // bitselect in opencl_std_100
    {187,IR(33, 3),IR(48800, 7),IR(1, 0)}, // select in opencl_std_100
    {201,IR(10, 1),IR(48807, 6),IR(1, 0)}, // u_abs in opencl_std_100
    {202,IR(36, 2),IR(48813, 11),IR(1, 0)}, // u_abs_diff in opencl_std_100
    {203,IR(36, 2),IR(48824, 9),IR(1, 0)}, // u_mul_hi in opencl_std_100
    {204,IR(33, 3),IR(48833, 9),IR(1, 0)}, // u_mad_hi in opencl_std_100
    {1,IR(10, 1),IR(48842, 17),IR(1, 0)}, // CubeFaceIndexAMD in spv_amd_gcn_shader
    {2,IR(10, 1),IR(48859, 17),IR(1, 0)}, // CubeFaceCoordAMD in spv_amd_gcn_shader
    {3,IR(0, 0),IR(48876, 8),IR(1, 0)}, // TimeAMD in spv_amd_gcn_shader
    {1,IR(36, 2),IR(48884, 22),IR(1, 0)}, // SwizzleInvocationsAMD in spv_amd_shader_ballot
    {2,IR(36, 2),IR(48906, 28),IR(1, 0)}, // SwizzleInvocationsMaskedAMD in spv_amd_shader_ballot
    {3,IR(33, 3),IR(48934, 19),IR(1, 0)}, // WriteInvocationAMD in spv_amd_shader_ballot
    {4,IR(10, 1),IR(48953, 9),IR(1, 0)}, // MbcntAMD in spv_amd_shader_ballot
    {1,IR(36, 2),IR(48962, 23),IR(1, 0)}, // InterpolateAtVertexAMD in spv_amd_shader_explicit_vertex_parameter
    {1,IR(33, 3),IR(48985, 9),IR(1, 0)}, // FMin3AMD in spv_amd_shader_trinary_minmax
    {2,IR(33, 3),IR(48994, 9),IR(1, 0)}, // UMin3AMD in spv_amd_shader_trinary_minmax
    {3,IR(33, 3),IR(49003, 9),IR(1, 0)}, // SMin3AMD in spv_amd_shader_trinary_minmax
    {4,IR(33, 3),IR(49012, 9),IR(1, 0)}, // FMax3AMD in spv_amd_shader_trinary_minmax
    {5,IR(33, 3),IR(49021, 9),IR(1, 0)}, // UMax3AMD in spv_amd_shader_trinary_minmax
    {6,IR(33, 3),IR(49030, 9),IR(1, 0)}, // SMax3AMD in spv_amd_shader_trinary_minmax
    {7,IR(33, 3),IR(49039, 9),IR(1, 0)}, // FMid3AMD in spv_amd_shader_trinary_minmax
    {8,IR(33, 3),IR(49048, 9),IR(1, 0)}, // UMid3AMD in spv_amd_shader_trinary_minmax
    {9,IR(33, 3),IR(49057, 9),IR(1, 0)}, // SMid3AMD in spv_amd_shader_trinary_minmax
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
    {IR(44333, 21), 1}, // DebugCompilationUnit in debuginfo
    {IR(45060, 13), 28}, // DebugDeclare in debuginfo
    {IR(45132, 16), 31}, // DebugExpression in debuginfo
    {IR(44876, 14), 20}, // DebugFunction in debuginfo
    {IR(44851, 25), 19}, // DebugFunctionDeclaration in debuginfo
    {IR(44831, 20), 18}, // DebugGlobalVariable in debuginfo
    {IR(44319, 14), 0}, // DebugInfoNone in debuginfo
    {IR(44963, 15), 25}, // DebugInlinedAt in debuginfo
    {IR(45039, 21), 27}, // DebugInlinedVariable in debuginfo
    {IR(44890, 18), 21}, // DebugLexicalBlock in debuginfo
    {IR(44908, 31), 22}, // DebugLexicalBlockDiscriminator in debuginfo
    {IR(45020, 19), 26}, // DebugLocalVariable in debuginfo
    {IR(45148, 14), 32}, // DebugMacroDef in debuginfo
    {IR(45162, 16), 33}, // DebugMacroUndef in debuginfo
    {IR(44950, 13), 24}, // DebugNoScope in debuginfo
    {IR(45117, 15), 30}, // DebugOperation in debuginfo
    {IR(44939, 11), 23}, // DebugScope in debuginfo
    {IR(44529, 15), 5}, // DebugTypeArray in debuginfo
    {IR(44406, 15), 2}, // DebugTypeBasic in debuginfo
    {IR(44643, 19), 10}, // DebugTypeComposite in debuginfo
    {IR(44591, 14), 9}, // DebugTypeEnum in debuginfo
    {IR(44573, 18), 8}, // DebugTypeFunction in debuginfo
    {IR(44678, 21), 12}, // DebugTypeInheritance in debuginfo
    {IR(44662, 16), 11}, // DebugTypeMember in debuginfo
    {IR(44455, 17), 3}, // DebugTypePointer in debuginfo
    {IR(44699, 21), 13}, // DebugTypePtrToMember in debuginfo
    {IR(44510, 19), 4}, // DebugTypeQualifier in debuginfo
    {IR(44720, 18), 14}, // DebugTypeTemplate in debuginfo
    {IR(44738, 27), 15}, // DebugTypeTemplateParameter in debuginfo
    {IR(44800, 31), 17}, // DebugTypeTemplateParameterPack in debuginfo
    {IR(44765, 35), 16}, // DebugTypeTemplateTemplateParameter in debuginfo
    {IR(44544, 16), 6}, // DebugTypeVector in debuginfo
    {IR(44560, 13), 7}, // DebugTypedef in debuginfo
    {IR(45073, 11), 29}, // DebugValue in debuginfo
    {IR(45272, 5), 50}, // Acos in glsl_std_450
    {IR(45303, 6), 56}, // Acosh in glsl_std_450
    {IR(45267, 5), 49}, // Asin in glsl_std_450
    {IR(45297, 6), 55}, // Asinh in glsl_std_450
    {IR(45277, 5), 51}, // Atan in glsl_std_450
    {IR(45315, 6), 58}, // Atan2 in glsl_std_450
    {IR(45309, 6), 57}, // Atanh in glsl_std_450
    {IR(45228, 5), 42}, // Ceil in glsl_std_450
    {IR(45259, 4), 47}, // Cos in glsl_std_450
    {IR(45287, 5), 53}, // Cosh in glsl_std_450
    {IR(45699, 6), 101}, // Cross in glsl_std_450
    {IR(45247, 8), 45}, // Degrees in glsl_std_450
    {IR(45360, 12), 66}, // Determinant in glsl_std_450
    {IR(45690, 9), 100}, // Distance in glsl_std_450
    {IR(45325, 4), 60}, // Exp in glsl_std_450
    {IR(45333, 5), 62}, // Exp2 in glsl_std_450
    {IR(45200, 5), 37}, // FAbs in glsl_std_450
    {IR(45432, 7), 76}, // FClamp in glsl_std_450
    {IR(45417, 5), 73}, // FMax in glsl_std_450
    {IR(45402, 5), 70}, // FMin in glsl_std_450
    {IR(45453, 5), 79}, // FMix in glsl_std_450
    {IR(45210, 6), 39}, // FSign in glsl_std_450
    {IR(45715, 12), 103}, // FaceForward in glsl_std_450
    {IR(45743, 9), 106}, // FindILsb in glsl_std_450
    {IR(45752, 9), 107}, // FindSMsb in glsl_std_450
    {IR(45761, 9), 108}, // FindUMsb in glsl_std_450
    {IR(45222, 6), 41}, // Floor in glsl_std_450
    {IR(45479, 4), 83}, // Fma in glsl_std_450
    {IR(45233, 6), 43}, // Fract in glsl_std_450
    {IR(45483, 6), 84}, // Frexp in glsl_std_450
    {IR(45489, 12), 85}, // FrexpStruct in glsl_std_450
    {IR(45458, 5), 80}, // IMix in glsl_std_450
    {IR(45770, 22), 109}, // InterpolateAtCentroid in glsl_std_450
    {IR(45812, 20), 111}, // InterpolateAtOffset in glsl_std_450
    {IR(45792, 20), 110}, // InterpolateAtSample in glsl_std_450
    {IR(45348, 12), 65}, // InverseSqrt in glsl_std_450
    {IR(45501, 6), 86}, // Ldexp in glsl_std_450
    {IR(45683, 7), 99}, // Length in glsl_std_450
    {IR(45329, 4), 61}, // Log in glsl_std_450
    {IR(45338, 5), 63}, // Log2 in glsl_std_450
    {IR(45372, 14), 67}, // MatrixInverse in glsl_std_450
    {IR(45386, 5), 68}, // Modf in glsl_std_450
    {IR(45391, 11), 69}, // ModfStruct in glsl_std_450
    {IR(45842, 7), 114}, // NClamp in glsl_std_450
    {IR(45837, 5), 113}, // NMax in glsl_std_450
    {IR(45832, 5), 112}, // NMin in glsl_std_450
    {IR(45705, 10), 102}, // Normalize in glsl_std_450
    {IR(45574, 15), 92}, // PackDouble2x32 in glsl_std_450
    {IR(45561, 13), 91}, // PackHalf2x16 in glsl_std_450
    {IR(45533, 14), 89}, // PackSnorm2x16 in glsl_std_450
    {IR(45507, 13), 87}, // PackSnorm4x8 in glsl_std_450
    {IR(45547, 14), 90}, // PackUnorm2x16 in glsl_std_450
    {IR(45520, 13), 88}, // PackUnorm4x8 in glsl_std_450
    {IR(45321, 4), 59}, // Pow in glsl_std_450
    {IR(45239, 8), 44}, // Radians in glsl_std_450
    {IR(45727, 8), 104}, // Reflect in glsl_std_450
    {IR(45735, 8), 105}, // Refract in glsl_std_450
    {IR(45178, 6), 34}, // Round in glsl_std_450
    {IR(45184, 10), 35}, // RoundEven in glsl_std_450
    {IR(45205, 5), 38}, // SAbs in glsl_std_450
    {IR(45446, 7), 78}, // SClamp in glsl_std_450
    {IR(45427, 5), 75}, // SMax in glsl_std_450
    {IR(45412, 5), 72}, // SMin in glsl_std_450
    {IR(45216, 6), 40}, // SSign in glsl_std_450
    {IR(45255, 4), 46}, // Sin in glsl_std_450
    {IR(45282, 5), 52}, // Sinh in glsl_std_450
    {IR(45468, 11), 82}, // SmoothStep in glsl_std_450
    {IR(45343, 5), 64}, // Sqrt in glsl_std_450
    {IR(45463, 5), 81}, // Step in glsl_std_450
    {IR(45263, 4), 48}, // Tan in glsl_std_450
    {IR(45292, 5), 54}, // Tanh in glsl_std_450
    {IR(45194, 6), 36}, // Trunc in glsl_std_450
    {IR(45439, 7), 77}, // UClamp in glsl_std_450
    {IR(45422, 5), 74}, // UMax in glsl_std_450
    {IR(45407, 5), 71}, // UMin in glsl_std_450
    {IR(45666, 17), 98}, // UnpackDouble2x32 in glsl_std_450
    {IR(45621, 15), 95}, // UnpackHalf2x16 in glsl_std_450
    {IR(45589, 16), 93}, // UnpackSnorm2x16 in glsl_std_450
    {IR(45636, 15), 96}, // UnpackSnorm4x8 in glsl_std_450
    {IR(45605, 16), 94}, // UnpackUnorm2x16 in glsl_std_450
    {IR(45651, 15), 97}, // UnpackUnorm4x8 in glsl_std_450
    {IR(45849, 13), 116}, // ArgumentInfo in nonsemantic_clspvreflection
    {IR(45944, 24), 121}, // ArgumentPodPushConstant in nonsemantic_clspvreflection
    {IR(45900, 25), 119}, // ArgumentPodStorageBuffer in nonsemantic_clspvreflection
    {IR(45925, 19), 120}, // ArgumentPodUniform in nonsemantic_clspvreflection
    {IR(46378, 28), 140}, // ArgumentPointerPushConstant in nonsemantic_clspvreflection
    {IR(46406, 23), 141}, // ArgumentPointerUniform in nonsemantic_clspvreflection
    {IR(45968, 21), 122}, // ArgumentSampledImage in nonsemantic_clspvreflection
    {IR(46010, 16), 124}, // ArgumentSampler in nonsemantic_clspvreflection
    {IR(45862, 22), 117}, // ArgumentStorageBuffer in nonsemantic_clspvreflection
    {IR(45989, 21), 123}, // ArgumentStorageImage in nonsemantic_clspvreflection
    {IR(46666, 27), 148}, // ArgumentStorageTexelBuffer in nonsemantic_clspvreflection
    {IR(45884, 16), 118}, // ArgumentUniform in nonsemantic_clspvreflection
    {IR(46693, 27), 149}, // ArgumentUniformTexelBuffer in nonsemantic_clspvreflection
    {IR(46026, 18), 125}, // ArgumentWorkgroup in nonsemantic_clspvreflection
    {IR(46720, 32), 150}, // ConstantDataPointerPushConstant in nonsemantic_clspvreflection
    {IR(46274, 26), 135}, // ConstantDataStorageBuffer in nonsemantic_clspvreflection
    {IR(46300, 20), 136}, // ConstantDataUniform in nonsemantic_clspvreflection
    {IR(46544, 45), 145}, // ImageArgumentInfoChannelDataTypePushConstant in nonsemantic_clspvreflection
    {IR(46626, 40), 147}, // ImageArgumentInfoChannelDataTypeUniform in nonsemantic_clspvreflection
    {IR(46502, 42), 144}, // ImageArgumentInfoChannelOrderPushConstant in nonsemantic_clspvreflection
    {IR(46589, 37), 146}, // ImageArgumentInfoChannelOrderUniform in nonsemantic_clspvreflection
    {IR(4492, 7), 115}, // Kernel in nonsemantic_clspvreflection
    {IR(7917, 15), 137}, // LiteralSampler in nonsemantic_clspvreflection
    {IR(46861, 34), 155}, // NormalizedSamplerMaskPushConstant in nonsemantic_clspvreflection
    {IR(46829, 32), 154}, // PrintfBufferPointerPushConstant in nonsemantic_clspvreflection
    {IR(46803, 26), 153}, // PrintfBufferStorageBuffer in nonsemantic_clspvreflection
    {IR(46792, 11), 152}, // PrintfInfo in nonsemantic_clspvreflection
    {IR(46752, 40), 151}, // ProgramScopeVariablePointerPushConstant in nonsemantic_clspvreflection
    {IR(46464, 38), 143}, // ProgramScopeVariablePointerRelocation in nonsemantic_clspvreflection
    {IR(46429, 35), 142}, // ProgramScopeVariablesStorageBuffer in nonsemantic_clspvreflection
    {IR(46320, 30), 138}, // PropertyRequiredWorkgroupSize in nonsemantic_clspvreflection
    {IR(46140, 30), 130}, // PushConstantEnqueuedLocalSize in nonsemantic_clspvreflection
    {IR(46115, 25), 129}, // PushConstantGlobalOffset in nonsemantic_clspvreflection
    {IR(46170, 23), 131}, // PushConstantGlobalSize in nonsemantic_clspvreflection
    {IR(46218, 26), 133}, // PushConstantNumWorkgroups in nonsemantic_clspvreflection
    {IR(46244, 30), 134}, // PushConstantRegionGroupOffset in nonsemantic_clspvreflection
    {IR(46193, 25), 132}, // PushConstantRegionOffset in nonsemantic_clspvreflection
    {IR(46070, 25), 127}, // SpecConstantGlobalOffset in nonsemantic_clspvreflection
    {IR(46350, 28), 139}, // SpecConstantSubgroupMaxSize in nonsemantic_clspvreflection
    {IR(46095, 20), 128}, // SpecConstantWorkDim in nonsemantic_clspvreflection
    {IR(46044, 26), 126}, // SpecConstantWorkgroupSize in nonsemantic_clspvreflection
    {IR(46895, 22), 156}, // WorkgroupVariableSize in nonsemantic_clspvreflection
    {IR(47016, 21), 197}, // DebugBuildIdentifier in nonsemantic_shader_debuginfo_100
    {IR(44333, 21), 158}, // DebugCompilationUnit in nonsemantic_shader_debuginfo_100
    {IR(45060, 13), 185}, // DebugDeclare in nonsemantic_shader_debuginfo_100
    {IR(47054, 16), 199}, // DebugEntryPoint in nonsemantic_shader_debuginfo_100
    {IR(45132, 16), 188}, // DebugExpression in nonsemantic_shader_debuginfo_100
    {IR(44876, 14), 177}, // DebugFunction in nonsemantic_shader_debuginfo_100
    {IR(44851, 25), 176}, // DebugFunctionDeclaration in nonsemantic_shader_debuginfo_100
    {IR(46949, 24), 193}, // DebugFunctionDefinition in nonsemantic_shader_debuginfo_100
    {IR(44831, 20), 175}, // DebugGlobalVariable in nonsemantic_shader_debuginfo_100
    {IR(46917, 20), 191}, // DebugImportedEntity in nonsemantic_shader_debuginfo_100
    {IR(44319, 14), 157}, // DebugInfoNone in nonsemantic_shader_debuginfo_100
    {IR(44963, 15), 182}, // DebugInlinedAt in nonsemantic_shader_debuginfo_100
    {IR(45039, 21), 184}, // DebugInlinedVariable in nonsemantic_shader_debuginfo_100
    {IR(44890, 18), 178}, // DebugLexicalBlock in nonsemantic_shader_debuginfo_100
    {IR(44908, 31), 179}, // DebugLexicalBlockDiscriminator in nonsemantic_shader_debuginfo_100
    {IR(46994, 10), 195}, // DebugLine in nonsemantic_shader_debuginfo_100
    {IR(45020, 19), 183}, // DebugLocalVariable in nonsemantic_shader_debuginfo_100
    {IR(45148, 14), 189}, // DebugMacroDef in nonsemantic_shader_debuginfo_100
    {IR(45162, 16), 190}, // DebugMacroUndef in nonsemantic_shader_debuginfo_100
    {IR(47004, 12), 196}, // DebugNoLine in nonsemantic_shader_debuginfo_100
    {IR(44950, 13), 181}, // DebugNoScope in nonsemantic_shader_debuginfo_100
    {IR(45117, 15), 187}, // DebugOperation in nonsemantic_shader_debuginfo_100
    {IR(44939, 11), 180}, // DebugScope in nonsemantic_shader_debuginfo_100
    {IR(46937, 12), 192}, // DebugSource in nonsemantic_shader_debuginfo_100
    {IR(46973, 21), 194}, // DebugSourceContinued in nonsemantic_shader_debuginfo_100
    {IR(47037, 17), 198}, // DebugStoragePath in nonsemantic_shader_debuginfo_100
    {IR(44529, 15), 162}, // DebugTypeArray in nonsemantic_shader_debuginfo_100
    {IR(44406, 15), 159}, // DebugTypeBasic in nonsemantic_shader_debuginfo_100
    {IR(44643, 19), 167}, // DebugTypeComposite in nonsemantic_shader_debuginfo_100
    {IR(44591, 14), 166}, // DebugTypeEnum in nonsemantic_shader_debuginfo_100
    {IR(44573, 18), 165}, // DebugTypeFunction in nonsemantic_shader_debuginfo_100
    {IR(44678, 21), 169}, // DebugTypeInheritance in nonsemantic_shader_debuginfo_100
    {IR(47070, 16), 200}, // DebugTypeMatrix in nonsemantic_shader_debuginfo_100
    {IR(44662, 16), 168}, // DebugTypeMember in nonsemantic_shader_debuginfo_100
    {IR(44455, 17), 160}, // DebugTypePointer in nonsemantic_shader_debuginfo_100
    {IR(44699, 21), 170}, // DebugTypePtrToMember in nonsemantic_shader_debuginfo_100
    {IR(44510, 19), 161}, // DebugTypeQualifier in nonsemantic_shader_debuginfo_100
    {IR(44720, 18), 171}, // DebugTypeTemplate in nonsemantic_shader_debuginfo_100
    {IR(44738, 27), 172}, // DebugTypeTemplateParameter in nonsemantic_shader_debuginfo_100
    {IR(44800, 31), 174}, // DebugTypeTemplateParameterPack in nonsemantic_shader_debuginfo_100
    {IR(44765, 35), 173}, // DebugTypeTemplateTemplateParameter in nonsemantic_shader_debuginfo_100
    {IR(44544, 16), 163}, // DebugTypeVector in nonsemantic_shader_debuginfo_100
    {IR(44560, 13), 164}, // DebugTypedef in nonsemantic_shader_debuginfo_100
    {IR(45073, 11), 186}, // DebugValue in nonsemantic_shader_debuginfo_100
    {IR(47086, 14), 201}, // Configuration in nonsemantic_vkspreflection
    {IR(47162, 20), 206}, // DescriptorSetBuffer in nonsemantic_vkspreflection
    {IR(47182, 19), 207}, // DescriptorSetImage in nonsemantic_vkspreflection
    {IR(47201, 21), 208}, // DescriptorSetSampler in nonsemantic_vkspreflection
    {IR(47125, 14), 204}, // PushConstants in nonsemantic_vkspreflection
    {IR(47139, 23), 205}, // SpecializationMapEntry in nonsemantic_vkspreflection
    {IR(47100, 13), 202}, // StartCounter in nonsemantic_vkspreflection
    {IR(47113, 12), 203}, // StopCounter in nonsemantic_vkspreflection
    {IR(44333, 21), 210}, // DebugCompilationUnit in opencl_debuginfo_100
    {IR(45060, 13), 237}, // DebugDeclare in opencl_debuginfo_100
    {IR(45132, 16), 240}, // DebugExpression in opencl_debuginfo_100
    {IR(44876, 14), 229}, // DebugFunction in opencl_debuginfo_100
    {IR(44851, 25), 228}, // DebugFunctionDeclaration in opencl_debuginfo_100
    {IR(44831, 20), 227}, // DebugGlobalVariable in opencl_debuginfo_100
    {IR(46917, 20), 243}, // DebugImportedEntity in opencl_debuginfo_100
    {IR(44319, 14), 209}, // DebugInfoNone in opencl_debuginfo_100
    {IR(44963, 15), 234}, // DebugInlinedAt in opencl_debuginfo_100
    {IR(45039, 21), 236}, // DebugInlinedVariable in opencl_debuginfo_100
    {IR(44890, 18), 230}, // DebugLexicalBlock in opencl_debuginfo_100
    {IR(44908, 31), 231}, // DebugLexicalBlockDiscriminator in opencl_debuginfo_100
    {IR(45020, 19), 235}, // DebugLocalVariable in opencl_debuginfo_100
    {IR(45148, 14), 241}, // DebugMacroDef in opencl_debuginfo_100
    {IR(45162, 16), 242}, // DebugMacroUndef in opencl_debuginfo_100
    {IR(47522, 17), 245}, // DebugModuleINTEL in opencl_debuginfo_100
    {IR(44950, 13), 233}, // DebugNoScope in opencl_debuginfo_100
    {IR(45117, 15), 239}, // DebugOperation in opencl_debuginfo_100
    {IR(44939, 11), 232}, // DebugScope in opencl_debuginfo_100
    {IR(46937, 12), 244}, // DebugSource in opencl_debuginfo_100
    {IR(44529, 15), 214}, // DebugTypeArray in opencl_debuginfo_100
    {IR(44406, 15), 211}, // DebugTypeBasic in opencl_debuginfo_100
    {IR(44643, 19), 219}, // DebugTypeComposite in opencl_debuginfo_100
    {IR(44591, 14), 218}, // DebugTypeEnum in opencl_debuginfo_100
    {IR(44573, 18), 217}, // DebugTypeFunction in opencl_debuginfo_100
    {IR(44678, 21), 221}, // DebugTypeInheritance in opencl_debuginfo_100
    {IR(44662, 16), 220}, // DebugTypeMember in opencl_debuginfo_100
    {IR(44455, 17), 212}, // DebugTypePointer in opencl_debuginfo_100
    {IR(44699, 21), 222}, // DebugTypePtrToMember in opencl_debuginfo_100
    {IR(44510, 19), 213}, // DebugTypeQualifier in opencl_debuginfo_100
    {IR(44720, 18), 223}, // DebugTypeTemplate in opencl_debuginfo_100
    {IR(44738, 27), 224}, // DebugTypeTemplateParameter in opencl_debuginfo_100
    {IR(44800, 31), 226}, // DebugTypeTemplateParameterPack in opencl_debuginfo_100
    {IR(44765, 35), 225}, // DebugTypeTemplateTemplateParameter in opencl_debuginfo_100
    {IR(44544, 16), 215}, // DebugTypeVector in opencl_debuginfo_100
    {IR(44560, 13), 216}, // DebugTypedef in opencl_debuginfo_100
    {IR(45073, 11), 238}, // DebugValue in opencl_debuginfo_100
    {IR(47539, 5), 246}, // acos in opencl_std_100
    {IR(47544, 6), 247}, // acosh in opencl_std_100
    {IR(47550, 7), 248}, // acospi in opencl_std_100
    {IR(47557, 5), 249}, // asin in opencl_std_100
    {IR(47562, 6), 250}, // asinh in opencl_std_100
    {IR(47568, 7), 251}, // asinpi in opencl_std_100
    {IR(47575, 5), 252}, // atan in opencl_std_100
    {IR(47580, 6), 253}, // atan2 in opencl_std_100
    {IR(47599, 8), 256}, // atan2pi in opencl_std_100
    {IR(47586, 6), 254}, // atanh in opencl_std_100
    {IR(47592, 7), 255}, // atanpi in opencl_std_100
    {IR(48790, 10), 402}, // bitselect in opencl_std_100
    {IR(47607, 5), 257}, // cbrt in opencl_std_100
    {IR(47612, 5), 258}, // ceil in opencl_std_100
    {IR(48462, 4), 367}, // clz in opencl_std_100
    {IR(47617, 9), 259}, // copysign in opencl_std_100
    {IR(47626, 4), 260}, // cos in opencl_std_100
    {IR(47630, 5), 261}, // cosh in opencl_std_100
    {IR(47635, 6), 262}, // cospi in opencl_std_100
    {IR(48306, 6), 350}, // cross in opencl_std_100
    {IR(48466, 4), 368}, // ctz in opencl_std_100
    {IR(48241, 8), 342}, // degrees in opencl_std_100
    {IR(48312, 9), 351}, // distance in opencl_std_100
    {IR(47646, 4), 264}, // erf in opencl_std_100
    {IR(47641, 5), 263}, // erfc in opencl_std_100
    {IR(47650, 4), 265}, // exp in opencl_std_100
    {IR(47659, 6), 267}, // exp10 in opencl_std_100
    {IR(47654, 5), 266}, // exp2 in opencl_std_100
    {IR(47665, 6), 268}, // expm1 in opencl_std_100
    {IR(47671, 5), 269}, // fabs in opencl_std_100
    {IR(48338, 14), 354}, // fast_distance in opencl_std_100
    {IR(48352, 12), 355}, // fast_length in opencl_std_100
    {IR(48364, 15), 356}, // fast_normalize in opencl_std_100
    {IR(48234, 7), 341}, // fclamp in opencl_std_100
    {IR(47676, 5), 270}, // fdim in opencl_std_100
    {IR(47681, 6), 271}, // floor in opencl_std_100
    {IR(47687, 4), 272}, // fma in opencl_std_100
    {IR(47691, 5), 273}, // fmax in opencl_std_100
    {IR(48249, 12), 343}, // fmax_common in opencl_std_100
    {IR(47696, 5), 274}, // fmin in opencl_std_100
    {IR(48261, 12), 344}, // fmin_common in opencl_std_100
    {IR(47701, 5), 275}, // fmod in opencl_std_100
    {IR(47706, 6), 276}, // fract in opencl_std_100
    {IR(47712, 6), 277}, // frexp in opencl_std_100
    {IR(47924, 9), 313}, // half_cos in opencl_std_100
    {IR(47933, 12), 314}, // half_divide in opencl_std_100
    {IR(47945, 9), 315}, // half_exp in opencl_std_100
    {IR(47964, 11), 317}, // half_exp10 in opencl_std_100
    {IR(47954, 10), 316}, // half_exp2 in opencl_std_100
    {IR(47975, 9), 318}, // half_log in opencl_std_100
    {IR(47994, 11), 320}, // half_log10 in opencl_std_100
    {IR(47984, 10), 319}, // half_log2 in opencl_std_100
    {IR(48005, 10), 321}, // half_powr in opencl_std_100
    {IR(48015, 11), 322}, // half_recip in opencl_std_100
    {IR(48026, 11), 323}, // half_rsqrt in opencl_std_100
    {IR(48037, 9), 324}, // half_sin in opencl_std_100
    {IR(48046, 10), 325}, // half_sqrt in opencl_std_100
    {IR(48056, 9), 326}, // half_tan in opencl_std_100
    {IR(47718, 6), 278}, // hypot in opencl_std_100
    {IR(47724, 6), 279}, // ilogb in opencl_std_100
    {IR(47730, 6), 280}, // ldexp in opencl_std_100
    {IR(48321, 7), 352}, // length in opencl_std_100
    {IR(47736, 7), 281}, // lgamma in opencl_std_100
    {IR(47743, 9), 282}, // lgamma_r in opencl_std_100
    {IR(47752, 4), 283}, // log in opencl_std_100
    {IR(47761, 6), 285}, // log10 in opencl_std_100
    {IR(47767, 6), 286}, // log1p in opencl_std_100
    {IR(47756, 5), 284}, // log2 in opencl_std_100
    {IR(47773, 5), 287}, // logb in opencl_std_100
    {IR(47778, 4), 288}, // mad in opencl_std_100
    {IR(47782, 7), 289}, // maxmag in opencl_std_100
    {IR(47789, 7), 290}, // minmag in opencl_std_100
    {IR(48273, 4), 345}, // mix in opencl_std_100
    {IR(47796, 5), 291}, // modf in opencl_std_100
    {IR(47801, 4), 292}, // nan in opencl_std_100
    {IR(48065, 11), 327}, // native_cos in opencl_std_100
    {IR(48076, 14), 328}, // native_divide in opencl_std_100
    {IR(48090, 11), 329}, // native_exp in opencl_std_100
    {IR(48113, 13), 331}, // native_exp10 in opencl_std_100
    {IR(48101, 12), 330}, // native_exp2 in opencl_std_100
    {IR(48126, 11), 332}, // native_log in opencl_std_100
    {IR(48149, 13), 334}, // native_log10 in opencl_std_100
    {IR(48137, 12), 333}, // native_log2 in opencl_std_100
    {IR(48162, 12), 335}, // native_powr in opencl_std_100
    {IR(48174, 13), 336}, // native_recip in opencl_std_100
    {IR(48187, 13), 337}, // native_rsqrt in opencl_std_100
    {IR(48200, 11), 338}, // native_sin in opencl_std_100
    {IR(48211, 12), 339}, // native_sqrt in opencl_std_100
    {IR(48223, 11), 340}, // native_tan in opencl_std_100
    {IR(47805, 10), 293}, // nextafter in opencl_std_100
    {IR(48328, 10), 353}, // normalize in opencl_std_100
    {IR(48581, 9), 382}, // popcount in opencl_std_100
    {IR(47815, 4), 294}, // pow in opencl_std_100
    {IR(47819, 5), 295}, // pown in opencl_std_100
    {IR(47824, 5), 296}, // powr in opencl_std_100
    {IR(48781, 9), 401}, // prefetch in opencl_std_100
    {IR(48774, 7), 400}, // printf in opencl_std_100
    {IR(48277, 8), 346}, // radians in opencl_std_100
    {IR(47829, 10), 297}, // remainder in opencl_std_100
    {IR(47839, 7), 298}, // remquo in opencl_std_100
    {IR(47846, 5), 299}, // rint in opencl_std_100
    {IR(47851, 6), 300}, // rootn in opencl_std_100
    {IR(48532, 7), 377}, // rotate in opencl_std_100
    {IR(47857, 6), 301}, // round in opencl_std_100
    {IR(47863, 6), 302}, // rsqrt in opencl_std_100
    {IR(48379, 6), 357}, // s_abs in opencl_std_100
    {IR(48385, 11), 358}, // s_abs_diff in opencl_std_100
    {IR(48396, 10), 359}, // s_add_sat in opencl_std_100
    {IR(48446, 8), 365}, // s_clamp in opencl_std_100
    {IR(48416, 7), 361}, // s_hadd in opencl_std_100
    {IR(48590, 8), 383}, // s_mad24 in opencl_std_100
    {IR(48470, 9), 369}, // s_mad_hi in opencl_std_100
    {IR(48489, 10), 371}, // s_mad_sat in opencl_std_100
    {IR(48499, 6), 372}, // s_max in opencl_std_100
    {IR(48511, 6), 374}, // s_min in opencl_std_100
    {IR(48606, 8), 385}, // s_mul24 in opencl_std_100
    {IR(48523, 9), 376}, // s_mul_hi in opencl_std_100
    {IR(48430, 8), 363}, // s_rhadd in opencl_std_100
    {IR(48539, 10), 378}, // s_sub_sat in opencl_std_100
    {IR(48570, 11), 381}, // s_upsample in opencl_std_100
    {IR(48800, 7), 403}, // select in opencl_std_100
    {IR(48757, 8), 398}, // shuffle in opencl_std_100
    {IR(48765, 9), 399}, // shuffle2 in opencl_std_100
    {IR(48301, 5), 349}, // sign in opencl_std_100
    {IR(47869, 4), 303}, // sin in opencl_std_100
    {IR(47873, 7), 304}, // sincos in opencl_std_100
    {IR(47880, 5), 305}, // sinh in opencl_std_100
    {IR(47885, 6), 306}, // sinpi in opencl_std_100
    {IR(48290, 11), 348}, // smoothstep in opencl_std_100
    {IR(47891, 5), 307}, // sqrt in opencl_std_100
    {IR(48285, 5), 347}, // step in opencl_std_100
    {IR(47896, 4), 308}, // tan in opencl_std_100
    {IR(47900, 5), 309}, // tanh in opencl_std_100
    {IR(47905, 6), 310}, // tanpi in opencl_std_100
    {IR(47911, 7), 311}, // tgamma in opencl_std_100
    {IR(47918, 6), 312}, // trunc in opencl_std_100
    {IR(48807, 6), 404}, // u_abs in opencl_std_100
    {IR(48813, 11), 405}, // u_abs_diff in opencl_std_100
    {IR(48406, 10), 360}, // u_add_sat in opencl_std_100
    {IR(48454, 8), 366}, // u_clamp in opencl_std_100
    {IR(48423, 7), 362}, // u_hadd in opencl_std_100
    {IR(48598, 8), 384}, // u_mad24 in opencl_std_100
    {IR(48833, 9), 407}, // u_mad_hi in opencl_std_100
    {IR(48479, 10), 370}, // u_mad_sat in opencl_std_100
    {IR(48505, 6), 373}, // u_max in opencl_std_100
    {IR(48517, 6), 375}, // u_min in opencl_std_100
    {IR(48614, 8), 386}, // u_mul24 in opencl_std_100
    {IR(48824, 9), 406}, // u_mul_hi in opencl_std_100
    {IR(48438, 8), 364}, // u_rhadd in opencl_std_100
    {IR(48549, 10), 379}, // u_sub_sat in opencl_std_100
    {IR(48559, 11), 380}, // u_upsample in opencl_std_100
    {IR(48637, 11), 389}, // vload_half in opencl_std_100
    {IR(48648, 12), 390}, // vload_halfn in opencl_std_100
    {IR(48714, 13), 395}, // vloada_halfn in opencl_std_100
    {IR(48622, 7), 387}, // vloadn in opencl_std_100
    {IR(48660, 12), 391}, // vstore_half in opencl_std_100
    {IR(48672, 14), 392}, // vstore_half_r in opencl_std_100
    {IR(48686, 13), 393}, // vstore_halfn in opencl_std_100
    {IR(48699, 15), 394}, // vstore_halfn_r in opencl_std_100
    {IR(48727, 14), 396}, // vstorea_halfn in opencl_std_100
    {IR(48741, 16), 397}, // vstorea_halfn_r in opencl_std_100
    {IR(48629, 8), 388}, // vstoren in opencl_std_100
    {IR(48859, 17), 409}, // CubeFaceCoordAMD in spv_amd_gcn_shader
    {IR(48842, 17), 408}, // CubeFaceIndexAMD in spv_amd_gcn_shader
    {IR(48876, 8), 410}, // TimeAMD in spv_amd_gcn_shader
    {IR(48953, 9), 414}, // MbcntAMD in spv_amd_shader_ballot
    {IR(48884, 22), 411}, // SwizzleInvocationsAMD in spv_amd_shader_ballot
    {IR(48906, 28), 412}, // SwizzleInvocationsMaskedAMD in spv_amd_shader_ballot
    {IR(48934, 19), 413}, // WriteInvocationAMD in spv_amd_shader_ballot
    {IR(48962, 23), 415}, // InterpolateAtVertexAMD in spv_amd_shader_explicit_vertex_parameter
    {IR(49012, 9), 419}, // FMax3AMD in spv_amd_shader_trinary_minmax
    {IR(49039, 9), 422}, // FMid3AMD in spv_amd_shader_trinary_minmax
    {IR(48985, 9), 416}, // FMin3AMD in spv_amd_shader_trinary_minmax
    {IR(49030, 9), 421}, // SMax3AMD in spv_amd_shader_trinary_minmax
    {IR(49057, 9), 424}, // SMid3AMD in spv_amd_shader_trinary_minmax
    {IR(49003, 9), 418}, // SMin3AMD in spv_amd_shader_trinary_minmax
    {IR(49021, 9), 420}, // UMax3AMD in spv_amd_shader_trinary_minmax
    {IR(49048, 9), 423}, // UMid3AMD in spv_amd_shader_trinary_minmax
    {IR(48994, 9), 417}, // UMin3AMD in spv_amd_shader_trinary_minmax
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
  "SPV_AMDX_shader_enqueue\0" // IR(0, 24)
  "SPV_AMD_gcn_shader\0" // IR(24, 19)
  "SPV_AMD_gpu_shader_half_float\0" // IR(43, 30)
  "SPV_AMD_gpu_shader_half_float_fetch\0" // IR(73, 36)
  "SPV_AMD_gpu_shader_int16\0" // IR(109, 25)
  "SPV_AMD_shader_ballot\0" // IR(134, 22)
  "SPV_AMD_shader_early_and_late_fragment_tests\0" // IR(156, 45)
  "SPV_AMD_shader_explicit_vertex_parameter\0" // IR(201, 41)
  "SPV_AMD_shader_fragment_mask\0" // IR(242, 29)
  "SPV_AMD_shader_image_load_store_lod\0" // IR(271, 36)
  "SPV_AMD_shader_trinary_minmax\0" // IR(307, 30)
  "SPV_AMD_texture_gather_bias_lod\0" // IR(337, 32)
  "SPV_ARM_cooperative_matrix_layouts\0" // IR(369, 35)
  "SPV_ARM_core_builtins\0" // IR(404, 22)
  "SPV_EXT_arithmetic_fence\0" // IR(426, 25)
  "SPV_EXT_demote_to_helper_invocation\0" // IR(451, 36)
  "SPV_EXT_descriptor_indexing\0" // IR(487, 28)
  "SPV_EXT_fragment_fully_covered\0" // IR(515, 31)
  "SPV_EXT_fragment_invocation_density\0" // IR(546, 36)
  "SPV_EXT_fragment_shader_interlock\0" // IR(582, 34)
  "SPV_EXT_mesh_shader\0" // IR(616, 20)
  "SPV_EXT_opacity_micromap\0" // IR(636, 25)
  "SPV_EXT_optnone\0" // IR(661, 16)
  "SPV_EXT_physical_storage_buffer\0" // IR(677, 32)
  "SPV_EXT_relaxed_printf_string_address_space\0" // IR(709, 44)
  "SPV_EXT_replicated_composites\0" // IR(753, 30)
  "SPV_EXT_shader_atomic_float16_add\0" // IR(783, 34)
  "SPV_EXT_shader_atomic_float_add\0" // IR(817, 32)
  "SPV_EXT_shader_atomic_float_min_max\0" // IR(849, 36)
  "SPV_EXT_shader_image_int64\0" // IR(885, 27)
  "SPV_EXT_shader_stencil_export\0" // IR(912, 30)
  "SPV_EXT_shader_tile_image\0" // IR(942, 26)
  "SPV_EXT_shader_viewport_index_layer\0" // IR(968, 36)
  "SPV_GOOGLE_decorate_string\0" // IR(1004, 27)
  "SPV_GOOGLE_hlsl_functionality1\0" // IR(1031, 31)
  "SPV_GOOGLE_user_type\0" // IR(1062, 21)
  "SPV_INTEL_2d_block_io\0" // IR(1083, 22)
  "SPV_INTEL_arbitrary_precision_fixed_point\0" // IR(1105, 42)
  "SPV_INTEL_arbitrary_precision_floating_point\0" // IR(1147, 45)
  "SPV_INTEL_arbitrary_precision_integers\0" // IR(1192, 39)
  "SPV_INTEL_bfloat16_conversion\0" // IR(1231, 30)
  "SPV_INTEL_blocking_pipes\0" // IR(1261, 25)
  "SPV_INTEL_cache_controls\0" // IR(1286, 25)
  "SPV_INTEL_debug_module\0" // IR(1311, 23)
  "SPV_INTEL_device_side_avc_motion_estimation\0" // IR(1334, 44)
  "SPV_INTEL_float_controls2\0" // IR(1378, 26)
  "SPV_INTEL_fp_fast_math_mode\0" // IR(1404, 28)
  "SPV_INTEL_fp_max_error\0" // IR(1432, 23)
  "SPV_INTEL_fpga_argument_interfaces\0" // IR(1455, 35)
  "SPV_INTEL_fpga_buffer_location\0" // IR(1490, 31)
  "SPV_INTEL_fpga_cluster_attributes\0" // IR(1521, 34)
  "SPV_INTEL_fpga_dsp_control\0" // IR(1555, 27)
  "SPV_INTEL_fpga_invocation_pipelining_attributes\0" // IR(1582, 48)
  "SPV_INTEL_fpga_latency_control\0" // IR(1630, 31)
  "SPV_INTEL_fpga_loop_controls\0" // IR(1661, 29)
  "SPV_INTEL_fpga_memory_accesses\0" // IR(1690, 31)
  "SPV_INTEL_fpga_memory_attributes\0" // IR(1721, 33)
  "SPV_INTEL_fpga_reg\0" // IR(1754, 19)
  "SPV_INTEL_function_pointers\0" // IR(1773, 28)
  "SPV_INTEL_global_variable_fpga_decorations\0" // IR(1801, 43)
  "SPV_INTEL_global_variable_host_access\0" // IR(1844, 38)
  "SPV_INTEL_inline_assembly\0" // IR(1882, 26)
  "SPV_INTEL_int4\0" // IR(1908, 15)
  "SPV_INTEL_io_pipes\0" // IR(1923, 19)
  "SPV_INTEL_kernel_attributes\0" // IR(1942, 28)
  "SPV_INTEL_long_composites\0" // IR(1970, 26)
  "SPV_INTEL_loop_fuse\0" // IR(1996, 20)
  "SPV_INTEL_masked_gather_scatter\0" // IR(2016, 32)
  "SPV_INTEL_maximum_registers\0" // IR(2048, 28)
  "SPV_INTEL_media_block_io\0" // IR(2076, 25)
  "SPV_INTEL_memory_access_aliasing\0" // IR(2101, 33)
  "SPV_INTEL_optnone\0" // IR(2134, 18)
  "SPV_INTEL_runtime_aligned\0" // IR(2152, 26)
  "SPV_INTEL_shader_integer_functions2\0" // IR(2178, 36)
  "SPV_INTEL_split_barrier\0" // IR(2214, 24)
  "SPV_INTEL_subgroup_buffer_prefetch\0" // IR(2238, 35)
  "SPV_INTEL_subgroup_matrix_multiply_accumulate\0" // IR(2273, 46)
  "SPV_INTEL_subgroups\0" // IR(2319, 20)
  "SPV_INTEL_task_sequence\0" // IR(2339, 24)
  "SPV_INTEL_tensor_float32_conversion\0" // IR(2363, 36)
  "SPV_INTEL_ternary_bitwise_function\0" // IR(2399, 35)
  "SPV_INTEL_unstructured_loop_controls\0" // IR(2434, 37)
  "SPV_INTEL_usm_storage_classes\0" // IR(2471, 30)
  "SPV_INTEL_variable_length_array\0" // IR(2501, 32)
  "SPV_INTEL_vector_compute\0" // IR(2533, 25)
  "SPV_KHR_16bit_storage\0" // IR(2558, 22)
  "SPV_KHR_8bit_storage\0" // IR(2580, 21)
  "SPV_KHR_bfloat16\0" // IR(2601, 17)
  "SPV_KHR_bit_instructions\0" // IR(2618, 25)
  "SPV_KHR_compute_shader_derivatives\0" // IR(2643, 35)
  "SPV_KHR_cooperative_matrix\0" // IR(2678, 27)
  "SPV_KHR_device_group\0" // IR(2705, 21)
  "SPV_KHR_expect_assume\0" // IR(2726, 22)
  "SPV_KHR_float_controls\0" // IR(2748, 23)
  "SPV_KHR_float_controls2\0" // IR(2771, 24)
  "SPV_KHR_fragment_shader_barycentric\0" // IR(2795, 36)
  "SPV_KHR_fragment_shading_rate\0" // IR(2831, 30)
  "SPV_KHR_integer_dot_product\0" // IR(2861, 28)
  "SPV_KHR_linkonce_odr\0" // IR(2889, 21)
  "SPV_KHR_maximal_reconvergence\0" // IR(2910, 30)
  "SPV_KHR_multiview\0" // IR(2940, 18)
  "SPV_KHR_no_integer_wrap_decoration\0" // IR(2958, 35)
  "SPV_KHR_non_semantic_info\0" // IR(2993, 26)
  "SPV_KHR_physical_storage_buffer\0" // IR(3019, 32)
  "SPV_KHR_post_depth_coverage\0" // IR(3051, 28)
  "SPV_KHR_quad_control\0" // IR(3079, 21)
  "SPV_KHR_ray_cull_mask\0" // IR(3100, 22)
  "SPV_KHR_ray_query\0" // IR(3122, 18)
  "SPV_KHR_ray_tracing\0" // IR(3140, 20)
  "SPV_KHR_ray_tracing_position_fetch\0" // IR(3160, 35)
  "SPV_KHR_relaxed_extended_instruction\0" // IR(3195, 37)
  "SPV_KHR_shader_atomic_counter_ops\0" // IR(3232, 34)
  "SPV_KHR_shader_ballot\0" // IR(3266, 22)
  "SPV_KHR_shader_clock\0" // IR(3288, 21)
  "SPV_KHR_shader_draw_parameters\0" // IR(3309, 31)
  "SPV_KHR_storage_buffer_storage_class\0" // IR(3340, 37)
  "SPV_KHR_subgroup_rotate\0" // IR(3377, 24)
  "SPV_KHR_subgroup_uniform_control_flow\0" // IR(3401, 38)
  "SPV_KHR_subgroup_vote\0" // IR(3439, 22)
  "SPV_KHR_terminate_invocation\0" // IR(3461, 29)
  "SPV_KHR_uniform_group_instructions\0" // IR(3490, 35)
  "SPV_KHR_untyped_pointers\0" // IR(3525, 25)
  "SPV_KHR_variable_pointers\0" // IR(3550, 26)
  "SPV_KHR_vulkan_memory_model\0" // IR(3576, 28)
  "SPV_KHR_workgroup_memory_explicit_layout\0" // IR(3604, 41)
  "SPV_NVX_multiview_per_view_attributes\0" // IR(3645, 38)
  "SPV_NV_bindless_texture\0" // IR(3683, 24)
  "SPV_NV_cluster_acceleration_structure\0" // IR(3707, 38)
  "SPV_NV_compute_shader_derivatives\0" // IR(3745, 34)
  "SPV_NV_cooperative_matrix\0" // IR(3779, 26)
  "SPV_NV_cooperative_matrix2\0" // IR(3805, 27)
  "SPV_NV_cooperative_vector\0" // IR(3832, 26)
  "SPV_NV_displacement_micromap\0" // IR(3858, 29)
  "SPV_NV_fragment_shader_barycentric\0" // IR(3887, 35)
  "SPV_NV_geometry_shader_passthrough\0" // IR(3922, 35)
  "SPV_NV_linear_swept_spheres\0" // IR(3957, 28)
  "SPV_NV_mesh_shader\0" // IR(3985, 19)
  "SPV_NV_raw_access_chains\0" // IR(4004, 25)
  "SPV_NV_ray_tracing\0" // IR(4029, 19)
  "SPV_NV_ray_tracing_motion_blur\0" // IR(4048, 31)
  "SPV_NV_sample_mask_override_coverage\0" // IR(4079, 37)
  "SPV_NV_shader_atomic_fp16_vector\0" // IR(4116, 33)
  "SPV_NV_shader_image_footprint\0" // IR(4149, 30)
  "SPV_NV_shader_invocation_reorder\0" // IR(4179, 33)
  "SPV_NV_shader_sm_builtins\0" // IR(4212, 26)
  "SPV_NV_shader_subgroup_partitioned\0" // IR(4238, 35)
  "SPV_NV_shading_rate\0" // IR(4273, 20)
  "SPV_NV_stereo_view_rendering\0" // IR(4293, 29)
  "SPV_NV_tensor_addressing\0" // IR(4322, 25)
  "SPV_NV_viewport_array2\0" // IR(4347, 23)
  "SPV_QCOM_image_processing\0" // IR(4370, 26)
  "SPV_QCOM_image_processing2\0" // IR(4396, 27)
  "SPV_QCOM_tile_shading\0" // IR(4423, 22)
  "SPV_VALIDATOR_ignore_type_decl_unique\0" // IR(4445, 38)
  "ReadOnly\0" // IR(4483, 9)
  "Kernel\0" // IR(4492, 7)
  "WriteOnly\0" // IR(4499, 10)
  "ReadWrite\0" // IR(4509, 10)
  "Logical\0" // IR(4519, 8)
  "Physical32\0" // IR(4527, 11)
  "Addresses\0" // IR(4538, 10)
  "Physical64\0" // IR(4548, 11)
  "PhysicalStorageBuffer64\0" // IR(4559, 24)
  "PhysicalStorageBuffer64EXT\0" // IR(4583, 27)
  "PhysicalStorageBufferAddresses\0" // IR(4610, 31)
  "Position\0" // IR(4641, 9)
  "Shader\0" // IR(4650, 7)
  "PointSize\0" // IR(4657, 10)
  "ClipDistance\0" // IR(4667, 13)
  "CullDistance\0" // IR(4680, 13)
  "VertexId\0" // IR(4693, 9)
  "InstanceId\0" // IR(4702, 11)
  "PrimitiveId\0" // IR(4713, 12)
  "Geometry\0" // IR(4725, 9)
  "Tessellation\0" // IR(4734, 13)
  "RayTracingNV\0" // IR(4747, 13)
  "RayTracingKHR\0" // IR(4760, 14)
  "MeshShadingNV\0" // IR(4774, 14)
  "MeshShadingEXT\0" // IR(4788, 15)
  "InvocationId\0" // IR(4803, 13)
  "Layer\0" // IR(4816, 6)
  "ShaderLayer\0" // IR(4822, 12)
  "ShaderViewportIndexLayerEXT\0" // IR(4834, 28)
  "ViewportIndex\0" // IR(4862, 14)
  "MultiViewport\0" // IR(4876, 14)
  "ShaderViewportIndex\0" // IR(4890, 20)
  "TessLevelOuter\0" // IR(4910, 15)
  "TessLevelInner\0" // IR(4925, 15)
  "TessCoord\0" // IR(4940, 10)
  "PatchVertices\0" // IR(4950, 14)
  "FragCoord\0" // IR(4964, 10)
  "PointCoord\0" // IR(4974, 11)
  "FrontFacing\0" // IR(4985, 12)
  "SampleId\0" // IR(4997, 9)
  "SampleRateShading\0" // IR(5006, 18)
  "SamplePosition\0" // IR(5024, 15)
  "SampleMask\0" // IR(5039, 11)
  "FragDepth\0" // IR(5050, 10)
  "HelperInvocation\0" // IR(5060, 17)
  "NumWorkgroups\0" // IR(5077, 14)
  "WorkgroupSize\0" // IR(5091, 14)
  "WorkgroupId\0" // IR(5105, 12)
  "LocalInvocationId\0" // IR(5117, 18)
  "GlobalInvocationId\0" // IR(5135, 19)
  "LocalInvocationIndex\0" // IR(5154, 21)
  "WorkDim\0" // IR(5175, 8)
  "GlobalSize\0" // IR(5183, 11)
  "EnqueuedWorkgroupSize\0" // IR(5194, 22)
  "GlobalOffset\0" // IR(5216, 13)
  "GlobalLinearId\0" // IR(5229, 15)
  "SubgroupSize\0" // IR(5244, 13)
  "GroupNonUniform\0" // IR(5257, 16)
  "SubgroupBallotKHR\0" // IR(5273, 18)
  "SubgroupMaxSize\0" // IR(5291, 16)
  "NumSubgroups\0" // IR(5307, 13)
  "NumEnqueuedSubgroups\0" // IR(5320, 21)
  "SubgroupId\0" // IR(5341, 11)
  "SubgroupLocalInvocationId\0" // IR(5352, 26)
  "VertexIndex\0" // IR(5378, 12)
  "InstanceIndex\0" // IR(5390, 14)
  "CoreIDARM\0" // IR(5404, 10)
  "CoreBuiltinsARM\0" // IR(5414, 16)
  "CoreCountARM\0" // IR(5430, 13)
  "CoreMaxIDARM\0" // IR(5443, 13)
  "WarpIDARM\0" // IR(5456, 10)
  "WarpMaxIDARM\0" // IR(5466, 13)
  "SubgroupEqMask\0" // IR(5479, 15)
  "SubgroupEqMaskKHR\0" // IR(5494, 18)
  "GroupNonUniformBallot\0" // IR(5512, 22)
  "SubgroupGeMask\0" // IR(5534, 15)
  "SubgroupGeMaskKHR\0" // IR(5549, 18)
  "SubgroupGtMask\0" // IR(5567, 15)
  "SubgroupGtMaskKHR\0" // IR(5582, 18)
  "SubgroupLeMask\0" // IR(5600, 15)
  "SubgroupLeMaskKHR\0" // IR(5615, 18)
  "SubgroupLtMask\0" // IR(5633, 15)
  "SubgroupLtMaskKHR\0" // IR(5648, 18)
  "BaseVertex\0" // IR(5666, 11)
  "DrawParameters\0" // IR(5677, 15)
  "BaseInstance\0" // IR(5692, 13)
  "DrawIndex\0" // IR(5705, 10)
  "PrimitiveShadingRateKHR\0" // IR(5715, 24)
  "FragmentShadingRateKHR\0" // IR(5739, 23)
  "DeviceIndex\0" // IR(5762, 12)
  "DeviceGroup\0" // IR(5774, 12)
  "ViewIndex\0" // IR(5786, 10)
  "MultiView\0" // IR(5796, 10)
  "ShadingRateKHR\0" // IR(5806, 15)
  "TileOffsetQCOM\0" // IR(5821, 15)
  "TileShadingQCOM\0" // IR(5836, 16)
  "TileDimensionQCOM\0" // IR(5852, 18)
  "TileApronSizeQCOM\0" // IR(5870, 18)
  "BaryCoordNoPerspAMD\0" // IR(5888, 20)
  "BaryCoordNoPerspCentroidAMD\0" // IR(5908, 28)
  "BaryCoordNoPerspSampleAMD\0" // IR(5936, 26)
  "BaryCoordSmoothAMD\0" // IR(5962, 19)
  "BaryCoordSmoothCentroidAMD\0" // IR(5981, 27)
  "BaryCoordSmoothSampleAMD\0" // IR(6008, 25)
  "BaryCoordPullModelAMD\0" // IR(6033, 22)
  "FragStencilRefEXT\0" // IR(6055, 18)
  "StencilExportEXT\0" // IR(6073, 17)
  "RemainingRecursionLevelsAMDX\0" // IR(6090, 29)
  "ShaderEnqueueAMDX\0" // IR(6119, 18)
  "ShaderIndexAMDX\0" // IR(6137, 16)
  "ViewportMaskNV\0" // IR(6153, 15)
  "ShaderViewportMaskNV\0" // IR(6168, 21)
  "SecondaryPositionNV\0" // IR(6189, 20)
  "ShaderStereoViewNV\0" // IR(6209, 19)
  "SecondaryViewportMaskNV\0" // IR(6228, 24)
  "PositionPerViewNV\0" // IR(6252, 18)
  "PerViewAttributesNV\0" // IR(6270, 20)
  "ViewportMaskPerViewNV\0" // IR(6290, 22)
  "FullyCoveredEXT\0" // IR(6312, 16)
  "FragmentFullyCoveredEXT\0" // IR(6328, 24)
  "TaskCountNV\0" // IR(6352, 12)
  "PrimitiveCountNV\0" // IR(6364, 17)
  "PrimitiveIndicesNV\0" // IR(6381, 19)
  "ClipDistancePerViewNV\0" // IR(6400, 22)
  "CullDistancePerViewNV\0" // IR(6422, 22)
  "LayerPerViewNV\0" // IR(6444, 15)
  "MeshViewCountNV\0" // IR(6459, 16)
  "MeshViewIndicesNV\0" // IR(6475, 18)
  "BaryCoordKHR\0" // IR(6493, 13)
  "BaryCoordNV\0" // IR(6506, 12)
  "FragmentBarycentricKHR\0" // IR(6518, 23)
  "BaryCoordNoPerspKHR\0" // IR(6541, 20)
  "BaryCoordNoPerspNV\0" // IR(6561, 19)
  "FragSizeEXT\0" // IR(6580, 12)
  "FragmentSizeNV\0" // IR(6592, 15)
  "FragmentDensityEXT\0" // IR(6607, 19)
  "FragInvocationCountEXT\0" // IR(6626, 23)
  "InvocationsPerPixelNV\0" // IR(6649, 22)
  "PrimitivePointIndicesEXT\0" // IR(6671, 25)
  "PrimitiveLineIndicesEXT\0" // IR(6696, 24)
  "PrimitiveTriangleIndicesEXT\0" // IR(6720, 28)
  "CullPrimitiveEXT\0" // IR(6748, 17)
  "LaunchIdKHR\0" // IR(6765, 12)
  "LaunchIdNV\0" // IR(6777, 11)
  "LaunchSizeKHR\0" // IR(6788, 14)
  "LaunchSizeNV\0" // IR(6802, 13)
  "WorldRayOriginKHR\0" // IR(6815, 18)
  "WorldRayOriginNV\0" // IR(6833, 17)
  "WorldRayDirectionKHR\0" // IR(6850, 21)
  "WorldRayDirectionNV\0" // IR(6871, 20)
  "ObjectRayOriginKHR\0" // IR(6891, 19)
  "ObjectRayOriginNV\0" // IR(6910, 18)
  "ObjectRayDirectionKHR\0" // IR(6928, 22)
  "ObjectRayDirectionNV\0" // IR(6950, 21)
  "RayTminKHR\0" // IR(6971, 11)
  "RayTminNV\0" // IR(6982, 10)
  "RayTmaxKHR\0" // IR(6992, 11)
  "RayTmaxNV\0" // IR(7003, 10)
  "InstanceCustomIndexKHR\0" // IR(7013, 23)
  "InstanceCustomIndexNV\0" // IR(7036, 22)
  "ObjectToWorldKHR\0" // IR(7058, 17)
  "ObjectToWorldNV\0" // IR(7075, 16)
  "WorldToObjectKHR\0" // IR(7091, 17)
  "WorldToObjectNV\0" // IR(7108, 16)
  "HitTNV\0" // IR(7124, 7)
  "HitKindKHR\0" // IR(7131, 11)
  "HitKindNV\0" // IR(7142, 10)
  "CurrentRayTimeNV\0" // IR(7152, 17)
  "RayTracingMotionBlurNV\0" // IR(7169, 23)
  "HitTriangleVertexPositionsKHR\0" // IR(7192, 30)
  "RayTracingPositionFetchKHR\0" // IR(7222, 27)
  "HitMicroTriangleVertexPositionsNV\0" // IR(7249, 34)
  "RayTracingDisplacementMicromapNV\0" // IR(7283, 33)
  "HitMicroTriangleVertexBarycentricsNV\0" // IR(7316, 37)
  "IncomingRayFlagsKHR\0" // IR(7353, 20)
  "IncomingRayFlagsNV\0" // IR(7373, 19)
  "RayGeometryIndexKHR\0" // IR(7392, 20)
  "HitIsSphereNV\0" // IR(7412, 14)
  "RayTracingSpheresGeometryNV\0" // IR(7426, 28)
  "HitIsLSSNV\0" // IR(7454, 11)
  "RayTracingLinearSweptSpheresGeometryNV\0" // IR(7465, 39)
  "HitSpherePositionNV\0" // IR(7504, 20)
  "WarpsPerSMNV\0" // IR(7524, 13)
  "ShaderSMBuiltinsNV\0" // IR(7537, 19)
  "SMCountNV\0" // IR(7556, 10)
  "WarpIDNV\0" // IR(7566, 9)
  "SMIDNV\0" // IR(7575, 7)
  "HitLSSPositionsNV\0" // IR(7582, 18)
  "HitKindFrontFacingMicroTriangleNV\0" // IR(7600, 34)
  "HitKindBackFacingMicroTriangleNV\0" // IR(7634, 33)
  "HitSphereRadiusNV\0" // IR(7667, 18)
  "HitLSSRadiiNV\0" // IR(7685, 14)
  "ClusterIDNV\0" // IR(7699, 12)
  "RayTracingClusterAccelerationStructureNV\0" // IR(7711, 41)
  "CullMaskKHR\0" // IR(7752, 12)
  "RayCullMaskKHR\0" // IR(7764, 15)
  "Matrix\0" // IR(7779, 7)
  "Linkage\0" // IR(7786, 8)
  "Vector16\0" // IR(7794, 9)
  "Float16Buffer\0" // IR(7803, 14)
  "Float16\0" // IR(7817, 8)
  "Float64\0" // IR(7825, 8)
  "Int64\0" // IR(7833, 6)
  "Int64Atomics\0" // IR(7839, 13)
  "ImageBasic\0" // IR(7852, 11)
  "ImageReadWrite\0" // IR(7863, 15)
  "ImageMipmap\0" // IR(7878, 12)
  "Pipes\0" // IR(7890, 6)
  "Groups\0" // IR(7896, 7)
  "DeviceEnqueue\0" // IR(7903, 14)
  "LiteralSampler\0" // IR(7917, 15)
  "AtomicStorage\0" // IR(7932, 14)
  "Int16\0" // IR(7946, 6)
  "TessellationPointSize\0" // IR(7952, 22)
  "GeometryPointSize\0" // IR(7974, 18)
  "ImageGatherExtended\0" // IR(7992, 20)
  "StorageImageMultisample\0" // IR(8012, 24)
  "UniformBufferArrayDynamicIndexing\0" // IR(8036, 34)
  "SampledImageArrayDynamicIndexing\0" // IR(8070, 33)
  "StorageBufferArrayDynamicIndexing\0" // IR(8103, 34)
  "StorageImageArrayDynamicIndexing\0" // IR(8137, 33)
  "ImageCubeArray\0" // IR(8170, 15)
  "SampledCubeArray\0" // IR(8185, 17)
  "ImageRect\0" // IR(8202, 10)
  "SampledRect\0" // IR(8212, 12)
  "GenericPointer\0" // IR(8224, 15)
  "Int8\0" // IR(8239, 5)
  "InputAttachment\0" // IR(8244, 16)
  "SparseResidency\0" // IR(8260, 16)
  "MinLod\0" // IR(8276, 7)
  "Sampled1D\0" // IR(8283, 10)
  "Image1D\0" // IR(8293, 8)
  "SampledBuffer\0" // IR(8301, 14)
  "ImageBuffer\0" // IR(8315, 12)
  "ImageMSArray\0" // IR(8327, 13)
  "StorageImageExtendedFormats\0" // IR(8340, 28)
  "ImageQuery\0" // IR(8368, 11)
  "DerivativeControl\0" // IR(8379, 18)
  "InterpolationFunction\0" // IR(8397, 22)
  "TransformFeedback\0" // IR(8419, 18)
  "GeometryStreams\0" // IR(8437, 16)
  "StorageImageReadWithoutFormat\0" // IR(8453, 30)
  "StorageImageWriteWithoutFormat\0" // IR(8483, 31)
  "SubgroupDispatch\0" // IR(8514, 17)
  "NamedBarrier\0" // IR(8531, 13)
  "PipeStorage\0" // IR(8544, 12)
  "GroupNonUniformVote\0" // IR(8556, 20)
  "GroupNonUniformArithmetic\0" // IR(8576, 26)
  "GroupNonUniformShuffle\0" // IR(8602, 23)
  "GroupNonUniformShuffleRelative\0" // IR(8625, 31)
  "GroupNonUniformClustered\0" // IR(8656, 25)
  "GroupNonUniformQuad\0" // IR(8681, 20)
  "UniformDecoration\0" // IR(8701, 18)
  "TileImageColorReadAccessEXT\0" // IR(8719, 28)
  "TileImageDepthReadAccessEXT\0" // IR(8747, 28)
  "TileImageStencilReadAccessEXT\0" // IR(8775, 30)
  "CooperativeMatrixLayoutsARM\0" // IR(8805, 28)
  "WorkgroupMemoryExplicitLayoutKHR\0" // IR(8833, 33)
  "WorkgroupMemoryExplicitLayout8BitAccessKHR\0" // IR(8866, 43)
  "WorkgroupMemoryExplicitLayout16BitAccessKHR\0" // IR(8909, 44)
  "SubgroupVoteKHR\0" // IR(8953, 16)
  "StorageBuffer16BitAccess\0" // IR(8969, 25)
  "StorageUniformBufferBlock16\0" // IR(8994, 28)
  "UniformAndStorageBuffer16BitAccess\0" // IR(9022, 35)
  "StorageUniform16\0" // IR(9057, 17)
  "StoragePushConstant16\0" // IR(9074, 22)
  "StorageInputOutput16\0" // IR(9096, 21)
  "VariablePointersStorageBuffer\0" // IR(9117, 30)
  "VariablePointers\0" // IR(9147, 17)
  "AtomicStorageOps\0" // IR(9164, 17)
  "SampleMaskPostDepthCoverage\0" // IR(9181, 28)
  "StorageBuffer8BitAccess\0" // IR(9209, 24)
  "UniformAndStorageBuffer8BitAccess\0" // IR(9233, 34)
  "StoragePushConstant8\0" // IR(9267, 21)
  "DenormPreserve\0" // IR(9288, 15)
  "DenormFlushToZero\0" // IR(9303, 18)
  "SignedZeroInfNanPreserve\0" // IR(9321, 25)
  "RoundingModeRTE\0" // IR(9346, 16)
  "RoundingModeRTZ\0" // IR(9362, 16)
  "RayQueryProvisionalKHR\0" // IR(9378, 23)
  "RayQueryKHR\0" // IR(9401, 12)
  "UntypedPointersKHR\0" // IR(9413, 19)
  "RayTraversalPrimitiveCullingKHR\0" // IR(9432, 32)
  "TextureSampleWeightedQCOM\0" // IR(9464, 26)
  "TextureBoxFilterQCOM\0" // IR(9490, 21)
  "TextureBlockMatchQCOM\0" // IR(9511, 22)
  "TextureBlockMatch2QCOM\0" // IR(9533, 23)
  "Float16ImageAMD\0" // IR(9556, 16)
  "ImageGatherBiasLodAMD\0" // IR(9572, 22)
  "FragmentMaskAMD\0" // IR(9594, 16)
  "ImageReadWriteLodAMD\0" // IR(9610, 21)
  "Int64ImageEXT\0" // IR(9631, 14)
  "ShaderClockKHR\0" // IR(9645, 15)
  "QuadControlKHR\0" // IR(9660, 15)
  "Int4TypeINTEL\0" // IR(9675, 14)
  "Int4CooperativeMatrixINTEL\0" // IR(9689, 27)
  "CooperativeMatrixKHR\0" // IR(9716, 21)
  "BFloat16TypeKHR\0" // IR(9737, 16)
  "BFloat16DotProductKHR\0" // IR(9753, 22)
  "BFloat16CooperativeMatrixKHR\0" // IR(9775, 29)
  "SampleMaskOverrideCoverageNV\0" // IR(9804, 29)
  "GeometryShaderPassthroughNV\0" // IR(9833, 28)
  "ShaderViewportIndexLayerNV\0" // IR(9861, 27)
  "ImageFootprintNV\0" // IR(9888, 17)
  "FragmentBarycentricNV\0" // IR(9905, 22)
  "ComputeDerivativeGroupQuadsKHR\0" // IR(9927, 31)
  "ComputeDerivativeGroupQuadsNV\0" // IR(9958, 30)
  "ShadingRateNV\0" // IR(9988, 14)
  "GroupNonUniformPartitionedNV\0" // IR(10002, 29)
  "ShaderNonUniform\0" // IR(10031, 17)
  "ShaderNonUniformEXT\0" // IR(10048, 20)
  "RuntimeDescriptorArray\0" // IR(10068, 23)
  "RuntimeDescriptorArrayEXT\0" // IR(10091, 26)
  "InputAttachmentArrayDynamicIndexing\0" // IR(10117, 36)
  "InputAttachmentArrayDynamicIndexingEXT\0" // IR(10153, 39)
  "UniformTexelBufferArrayDynamicIndexing\0" // IR(10192, 39)
  "UniformTexelBufferArrayDynamicIndexingEXT\0" // IR(10231, 42)
  "StorageTexelBufferArrayDynamicIndexing\0" // IR(10273, 39)
  "StorageTexelBufferArrayDynamicIndexingEXT\0" // IR(10312, 42)
  "UniformBufferArrayNonUniformIndexing\0" // IR(10354, 37)
  "UniformBufferArrayNonUniformIndexingEXT\0" // IR(10391, 40)
  "SampledImageArrayNonUniformIndexing\0" // IR(10431, 36)
  "SampledImageArrayNonUniformIndexingEXT\0" // IR(10467, 39)
  "StorageBufferArrayNonUniformIndexing\0" // IR(10506, 37)
  "StorageBufferArrayNonUniformIndexingEXT\0" // IR(10543, 40)
  "StorageImageArrayNonUniformIndexing\0" // IR(10583, 36)
  "StorageImageArrayNonUniformIndexingEXT\0" // IR(10619, 39)
  "InputAttachmentArrayNonUniformIndexing\0" // IR(10658, 39)
  "InputAttachmentArrayNonUniformIndexingEXT\0" // IR(10697, 42)
  "UniformTexelBufferArrayNonUniformIndexing\0" // IR(10739, 42)
  "UniformTexelBufferArrayNonUniformIndexingEXT\0" // IR(10781, 45)
  "StorageTexelBufferArrayNonUniformIndexing\0" // IR(10826, 42)
  "StorageTexelBufferArrayNonUniformIndexingEXT\0" // IR(10868, 45)
  "VulkanMemoryModel\0" // IR(10913, 18)
  "VulkanMemoryModelKHR\0" // IR(10931, 21)
  "VulkanMemoryModelDeviceScope\0" // IR(10952, 29)
  "VulkanMemoryModelDeviceScopeKHR\0" // IR(10981, 32)
  "PhysicalStorageBufferAddressesEXT\0" // IR(11013, 34)
  "ComputeDerivativeGroupLinearKHR\0" // IR(11047, 32)
  "ComputeDerivativeGroupLinearNV\0" // IR(11079, 31)
  "RayTracingProvisionalKHR\0" // IR(11110, 25)
  "CooperativeMatrixNV\0" // IR(11135, 20)
  "FragmentShaderSampleInterlockEXT\0" // IR(11155, 33)
  "FragmentShaderShadingRateInterlockEXT\0" // IR(11188, 38)
  "FragmentShaderPixelInterlockEXT\0" // IR(11226, 32)
  "DemoteToHelperInvocation\0" // IR(11258, 25)
  "DemoteToHelperInvocationEXT\0" // IR(11283, 28)
  "DisplacementMicromapNV\0" // IR(11311, 23)
  "RayTracingOpacityMicromapEXT\0" // IR(11334, 29)
  "ShaderInvocationReorderNV\0" // IR(11363, 26)
  "BindlessTextureNV\0" // IR(11389, 18)
  "RayQueryPositionFetchKHR\0" // IR(11407, 25)
  "CooperativeVectorNV\0" // IR(11432, 20)
  "AtomicFloat16VectorNV\0" // IR(11452, 22)
  "RawAccessChainsNV\0" // IR(11474, 18)
  "CooperativeMatrixReductionsNV\0" // IR(11492, 30)
  "CooperativeMatrixConversionsNV\0" // IR(11522, 31)
  "CooperativeMatrixPerElementOperationsNV\0" // IR(11553, 40)
  "CooperativeMatrixTensorAddressingNV\0" // IR(11593, 36)
  "CooperativeMatrixBlockLoadsNV\0" // IR(11629, 30)
  "CooperativeVectorTrainingNV\0" // IR(11659, 28)
  "TensorAddressingNV\0" // IR(11687, 19)
  "SubgroupShuffleINTEL\0" // IR(11706, 21)
  "SubgroupBufferBlockIOINTEL\0" // IR(11727, 27)
  "SubgroupImageBlockIOINTEL\0" // IR(11754, 26)
  "SubgroupImageMediaBlockIOINTEL\0" // IR(11780, 31)
  "RoundToInfinityINTEL\0" // IR(11811, 21)
  "FloatingPointModeINTEL\0" // IR(11832, 23)
  "IntegerFunctions2INTEL\0" // IR(11855, 23)
  "FunctionPointersINTEL\0" // IR(11878, 22)
  "IndirectReferencesINTEL\0" // IR(11900, 24)
  "AsmINTEL\0" // IR(11924, 9)
  "AtomicFloat32MinMaxEXT\0" // IR(11933, 23)
  "AtomicFloat64MinMaxEXT\0" // IR(11956, 23)
  "AtomicFloat16MinMaxEXT\0" // IR(11979, 23)
  "VectorComputeINTEL\0" // IR(12002, 19)
  "VectorAnyINTEL\0" // IR(12021, 15)
  "ExpectAssumeKHR\0" // IR(12036, 16)
  "SubgroupAvcMotionEstimationINTEL\0" // IR(12052, 33)
  "SubgroupAvcMotionEstimationIntraINTEL\0" // IR(12085, 38)
  "SubgroupAvcMotionEstimationChromaINTEL\0" // IR(12123, 39)
  "VariableLengthArrayINTEL\0" // IR(12162, 25)
  "FunctionFloatControlINTEL\0" // IR(12187, 26)
  "FPGAMemoryAttributesINTEL\0" // IR(12213, 26)
  "FPFastMathModeINTEL\0" // IR(12239, 20)
  "ArbitraryPrecisionIntegersINTEL\0" // IR(12259, 32)
  "ArbitraryPrecisionFloatingPointINTEL\0" // IR(12291, 37)
  "UnstructuredLoopControlsINTEL\0" // IR(12328, 30)
  "FPGALoopControlsINTEL\0" // IR(12358, 22)
  "KernelAttributesINTEL\0" // IR(12380, 22)
  "FPGAKernelAttributesINTEL\0" // IR(12402, 26)
  "FPGAMemoryAccessesINTEL\0" // IR(12428, 24)
  "FPGAClusterAttributesINTEL\0" // IR(12452, 27)
  "LoopFuseINTEL\0" // IR(12479, 14)
  "FPGADSPControlINTEL\0" // IR(12493, 20)
  "MemoryAccessAliasingINTEL\0" // IR(12513, 26)
  "FPGAInvocationPipeliningAttributesINTEL\0" // IR(12539, 40)
  "FPGABufferLocationINTEL\0" // IR(12579, 24)
  "ArbitraryPrecisionFixedPointINTEL\0" // IR(12603, 34)
  "USMStorageClassesINTEL\0" // IR(12637, 23)
  "RuntimeAlignedAttributeINTEL\0" // IR(12660, 29)
  "IOPipesINTEL\0" // IR(12689, 13)
  "BlockingPipesINTEL\0" // IR(12702, 19)
  "FPGARegINTEL\0" // IR(12721, 13)
  "DotProductInputAll\0" // IR(12734, 19)
  "DotProductInputAllKHR\0" // IR(12753, 22)
  "DotProductInput4x8Bit\0" // IR(12775, 22)
  "DotProductInput4x8BitKHR\0" // IR(12797, 25)
  "DotProductInput4x8BitPacked\0" // IR(12822, 28)
  "DotProductInput4x8BitPackedKHR\0" // IR(12850, 31)
  "DotProduct\0" // IR(12881, 11)
  "DotProductKHR\0" // IR(12892, 14)
  "ReplicatedCompositesEXT\0" // IR(12906, 24)
  "BitInstructions\0" // IR(12930, 16)
  "GroupNonUniformRotateKHR\0" // IR(12946, 25)
  "FloatControls2\0" // IR(12971, 15)
  "AtomicFloat32AddEXT\0" // IR(12986, 20)
  "AtomicFloat64AddEXT\0" // IR(13006, 20)
  "LongCompositesINTEL\0" // IR(13026, 20)
  "OptNoneEXT\0" // IR(13046, 11)
  "OptNoneINTEL\0" // IR(13057, 13)
  "AtomicFloat16AddEXT\0" // IR(13070, 20)
  "DebugInfoModuleINTEL\0" // IR(13090, 21)
  "BFloat16ConversionINTEL\0" // IR(13111, 24)
  "SplitBarrierINTEL\0" // IR(13135, 18)
  "ArithmeticFenceEXT\0" // IR(13153, 19)
  "FPGAClusterAttributesV2INTEL\0" // IR(13172, 29)
  "FPGAKernelAttributesv2INTEL\0" // IR(13201, 28)
  "TaskSequenceINTEL\0" // IR(13229, 18)
  "FPMaxErrorINTEL\0" // IR(13247, 16)
  "FPGALatencyControlINTEL\0" // IR(13263, 24)
  "FPGAArgumentInterfacesINTEL\0" // IR(13287, 28)
  "GlobalVariableHostAccessINTEL\0" // IR(13315, 30)
  "GlobalVariableFPGADecorationsINTEL\0" // IR(13345, 35)
  "SubgroupBufferPrefetchINTEL\0" // IR(13380, 28)
  "Subgroup2DBlockIOINTEL\0" // IR(13408, 23)
  "Subgroup2DBlockTransformINTEL\0" // IR(13431, 30)
  "Subgroup2DBlockTransposeINTEL\0" // IR(13461, 30)
  "SubgroupMatrixMultiplyAccumulateINTEL\0" // IR(13491, 38)
  "TernaryBitwiseFunctionINTEL\0" // IR(13529, 28)
  "GroupUniformArithmeticKHR\0" // IR(13557, 26)
  "TensorFloat32RoundingINTEL\0" // IR(13583, 27)
  "MaskedGatherScatterINTEL\0" // IR(13610, 25)
  "CacheControlsINTEL\0" // IR(13635, 19)
  "RegisterLimitsINTEL\0" // IR(13654, 20)
  "Unspecified\0" // IR(13674, 12)
  "Address\0" // IR(13686, 8)
  "Boolean\0" // IR(13694, 8)
  "Float\0" // IR(13702, 6)
  "Signed\0" // IR(13708, 7)
  "SignedChar\0" // IR(13715, 11)
  "Unsigned\0" // IR(13726, 9)
  "UnsignedChar\0" // IR(13735, 13)
  "Class\0" // IR(13748, 6)
  "Structure\0" // IR(13754, 10)
  "Union\0" // IR(13764, 6)
  "ImportedModule\0" // IR(13770, 15)
  "ImportedDeclaration\0" // IR(13785, 20)
  "None\0" // IR(13805, 5)
  "FlagIsProtected\0" // IR(13810, 16)
  "FlagIsPrivate\0" // IR(13826, 14)
  "FlagIsPublic\0" // IR(13840, 13)
  "FlagIsLocal\0" // IR(13853, 12)
  "FlagIsDefinition\0" // IR(13865, 17)
  "FlagFwdDecl\0" // IR(13882, 12)
  "FlagArtificial\0" // IR(13894, 15)
  "FlagExplicit\0" // IR(13909, 13)
  "FlagPrototyped\0" // IR(13922, 15)
  "FlagObjectPointer\0" // IR(13937, 18)
  "FlagStaticMember\0" // IR(13955, 17)
  "FlagIndirectVariable\0" // IR(13972, 21)
  "FlagLValueReference\0" // IR(13993, 20)
  "FlagRValueReference\0" // IR(14013, 20)
  "FlagIsOptimized\0" // IR(14033, 16)
  "FlagIsEnumClass\0" // IR(14049, 16)
  "FlagTypePassByValue\0" // IR(14065, 20)
  "FlagTypePassByReference\0" // IR(14085, 24)
  "Deref\0" // IR(14109, 6)
  "Plus\0" // IR(14115, 5)
  "Minus\0" // IR(14120, 6)
  "SPV_OPERAND_TYPE_LITERAL_INTEGER\0" // IR(14126, 33)
  "PlusUconst\0" // IR(14159, 11)
  "BitPiece\0" // IR(14170, 9)
  "Swap\0" // IR(14179, 5)
  "Xderef\0" // IR(14184, 7)
  "StackValue\0" // IR(14191, 11)
  "Constu\0" // IR(14202, 7)
  "Fragment\0" // IR(14209, 9)
  "ConstType\0" // IR(14218, 10)
  "VolatileType\0" // IR(14228, 13)
  "RestrictType\0" // IR(14241, 13)
  "AtomicType\0" // IR(14254, 11)
  "Float16NV\0" // IR(14265, 10)
  "Float32NV\0" // IR(14275, 10)
  "Float64NV\0" // IR(14285, 10)
  "SignedInt8NV\0" // IR(14295, 13)
  "SignedInt16NV\0" // IR(14308, 14)
  "SignedInt32NV\0" // IR(14322, 14)
  "SignedInt64NV\0" // IR(14336, 14)
  "UnsignedInt8NV\0" // IR(14350, 15)
  "UnsignedInt16NV\0" // IR(14365, 16)
  "UnsignedInt32NV\0" // IR(14381, 16)
  "UnsignedInt64NV\0" // IR(14397, 16)
  "SignedInt8PackedNV\0" // IR(14413, 19)
  "UnsignedInt8PackedNV\0" // IR(14432, 21)
  "FloatE4M3NV\0" // IR(14453, 12)
  "FloatE5M2NV\0" // IR(14465, 12)
  "RowMajorKHR\0" // IR(14477, 12)
  "ColumnMajorKHR\0" // IR(14489, 15)
  "RowBlockedInterleavedARM\0" // IR(14504, 25)
  "ColumnBlockedInterleavedARM\0" // IR(14529, 28)
  "NoneKHR\0" // IR(14557, 8)
  "MatrixASignedComponentsKHR\0" // IR(14565, 27)
  "MatrixBSignedComponentsKHR\0" // IR(14592, 27)
  "MatrixCSignedComponentsKHR\0" // IR(14619, 27)
  "MatrixResultSignedComponentsKHR\0" // IR(14646, 32)
  "SaturatingAccumulationKHR\0" // IR(14678, 26)
  "Row\0" // IR(14704, 4)
  "Column\0" // IR(14708, 7)
  "2x2\0" // IR(14715, 4)
  "MatrixAKHR\0" // IR(14719, 11)
  "MatrixBKHR\0" // IR(14730, 11)
  "MatrixAccumulatorKHR\0" // IR(14741, 21)
  "RowMajorNV\0" // IR(14762, 11)
  "ColumnMajorNV\0" // IR(14773, 14)
  "InferencingOptimalNV\0" // IR(14787, 21)
  "TrainingOptimalNV\0" // IR(14808, 18)
  "RelaxedPrecision\0" // IR(14826, 17)
  "SpecId\0" // IR(14843, 7)
  "Block\0" // IR(14850, 6)
  "BufferBlock\0" // IR(14856, 12)
  "RowMajor\0" // IR(14868, 9)
  "ColMajor\0" // IR(14877, 9)
  "ArrayStride\0" // IR(14886, 12)
  "MatrixStride\0" // IR(14898, 13)
  "GLSLShared\0" // IR(14911, 11)
  "GLSLPacked\0" // IR(14922, 11)
  "CPacked\0" // IR(14933, 8)
  "SPV_OPERAND_TYPE_BUILT_IN\0" // IR(14941, 26)
  "BuiltIn\0" // IR(14967, 8)
  "NoPerspective\0" // IR(14975, 14)
  "Flat\0" // IR(14989, 5)
  "Patch\0" // IR(14994, 6)
  "Centroid\0" // IR(15000, 9)
  "Sample\0" // IR(15009, 7)
  "Invariant\0" // IR(15016, 10)
  "Restrict\0" // IR(15026, 9)
  "Aliased\0" // IR(15035, 8)
  "Volatile\0" // IR(15043, 9)
  "Constant\0" // IR(15052, 9)
  "Coherent\0" // IR(15061, 9)
  "NonWritable\0" // IR(15070, 12)
  "NonReadable\0" // IR(15082, 12)
  "Uniform\0" // IR(15094, 8)
  "SPV_OPERAND_TYPE_SCOPE_ID\0" // IR(15102, 26)
  "UniformId\0" // IR(15128, 10)
  "SaturatedConversion\0" // IR(15138, 20)
  "Stream\0" // IR(15158, 7)
  "Location\0" // IR(15165, 9)
  "Component\0" // IR(15174, 10)
  "Index\0" // IR(15184, 6)
  "Binding\0" // IR(15190, 8)
  "DescriptorSet\0" // IR(15198, 14)
  "Offset\0" // IR(15212, 7)
  "XfbBuffer\0" // IR(15219, 10)
  "XfbStride\0" // IR(15229, 10)
  "SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE\0" // IR(15239, 46)
  "FuncParamAttr\0" // IR(15285, 14)
  "SPV_OPERAND_TYPE_FP_ROUNDING_MODE\0" // IR(15299, 34)
  "FPRoundingMode\0" // IR(15333, 15)
  "SPV_OPERAND_TYPE_FP_FAST_MATH_MODE\0" // IR(15348, 35)
  "FPFastMathMode\0" // IR(15383, 15)
  "SPV_OPERAND_TYPE_LITERAL_STRING\0" // IR(15398, 32)
  "SPV_OPERAND_TYPE_LINKAGE_TYPE\0" // IR(15430, 30)
  "LinkageAttributes\0" // IR(15460, 18)
  "NoContraction\0" // IR(15478, 14)
  "InputAttachmentIndex\0" // IR(15492, 21)
  "Alignment\0" // IR(15513, 10)
  "MaxByteOffset\0" // IR(15523, 14)
  "SPV_OPERAND_TYPE_ID\0" // IR(15537, 20)
  "AlignmentId\0" // IR(15557, 12)
  "MaxByteOffsetId\0" // IR(15569, 16)
  "NoSignedWrap\0" // IR(15585, 13)
  "NoUnsignedWrap\0" // IR(15598, 15)
  "WeightTextureQCOM\0" // IR(15613, 18)
  "BlockMatchTextureQCOM\0" // IR(15631, 22)
  "BlockMatchSamplerQCOM\0" // IR(15653, 22)
  "ExplicitInterpAMD\0" // IR(15675, 18)
  "NodeSharesPayloadLimitsWithAMDX\0" // IR(15693, 32)
  "NodeMaxPayloadsAMDX\0" // IR(15725, 20)
  "TrackFinishWritingAMDX\0" // IR(15745, 23)
  "PayloadNodeNameAMDX\0" // IR(15768, 20)
  "PayloadNodeBaseIndexAMDX\0" // IR(15788, 25)
  "PayloadNodeSparseArrayAMDX\0" // IR(15813, 27)
  "PayloadNodeArraySizeAMDX\0" // IR(15840, 25)
  "PayloadDispatchIndirectAMDX\0" // IR(15865, 28)
  "OverrideCoverageNV\0" // IR(15893, 19)
  "PassthroughNV\0" // IR(15912, 14)
  "ViewportRelativeNV\0" // IR(15926, 19)
  "SecondaryViewportRelativeNV\0" // IR(15945, 28)
  "PerPrimitiveEXT\0" // IR(15973, 16)
  "PerPrimitiveNV\0" // IR(15989, 15)
  "PerViewNV\0" // IR(16004, 10)
  "PerTaskNV\0" // IR(16014, 10)
  "PerVertexKHR\0" // IR(16024, 13)
  "PerVertexNV\0" // IR(16037, 12)
  "NonUniform\0" // IR(16049, 11)
  "NonUniformEXT\0" // IR(16060, 14)
  "RestrictPointer\0" // IR(16074, 16)
  "RestrictPointerEXT\0" // IR(16090, 19)
  "AliasedPointer\0" // IR(16109, 15)
  "AliasedPointerEXT\0" // IR(16124, 18)
  "HitObjectShaderRecordBufferNV\0" // IR(16142, 30)
  "BindlessSamplerNV\0" // IR(16172, 18)
  "BindlessImageNV\0" // IR(16190, 16)
  "BoundSamplerNV\0" // IR(16206, 15)
  "BoundImageNV\0" // IR(16221, 13)
  "SIMTCallINTEL\0" // IR(16234, 14)
  "ReferencedIndirectlyINTEL\0" // IR(16248, 26)
  "ClobberINTEL\0" // IR(16274, 13)
  "SideEffectsINTEL\0" // IR(16287, 17)
  "VectorComputeVariableINTEL\0" // IR(16304, 27)
  "FuncParamIOKindINTEL\0" // IR(16331, 21)
  "VectorComputeFunctionINTEL\0" // IR(16352, 27)
  "StackCallINTEL\0" // IR(16379, 15)
  "GlobalVariableOffsetINTEL\0" // IR(16394, 26)
  "CounterBuffer\0" // IR(16420, 14)
  "HlslCounterBufferGOOGLE\0" // IR(16434, 24)
  "UserSemantic\0" // IR(16458, 13)
  "HlslSemanticGOOGLE\0" // IR(16471, 19)
  "UserTypeGOOGLE\0" // IR(16490, 15)
  "FunctionRoundingModeINTEL\0" // IR(16505, 26)
  "SPV_OPERAND_TYPE_FPDENORM_MODE\0" // IR(16531, 31)
  "FunctionDenormModeINTEL\0" // IR(16562, 24)
  "RegisterINTEL\0" // IR(16586, 14)
  "MemoryINTEL\0" // IR(16600, 12)
  "NumbanksINTEL\0" // IR(16612, 14)
  "BankwidthINTEL\0" // IR(16626, 15)
  "MaxPrivateCopiesINTEL\0" // IR(16641, 22)
  "SinglepumpINTEL\0" // IR(16663, 16)
  "DoublepumpINTEL\0" // IR(16679, 16)
  "MaxReplicatesINTEL\0" // IR(16695, 19)
  "SimpleDualPortINTEL\0" // IR(16714, 20)
  "MergeINTEL\0" // IR(16734, 11)
  "SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER\0" // IR(16745, 42)
  "BankBitsINTEL\0" // IR(16787, 14)
  "ForcePow2DepthINTEL\0" // IR(16801, 20)
  "StridesizeINTEL\0" // IR(16821, 16)
  "WordsizeINTEL\0" // IR(16837, 14)
  "TrueDualPortINTEL\0" // IR(16851, 18)
  "BurstCoalesceINTEL\0" // IR(16869, 19)
  "CacheSizeINTEL\0" // IR(16888, 15)
  "DontStaticallyCoalesceINTEL\0" // IR(16903, 28)
  "PrefetchINTEL\0" // IR(16931, 14)
  "StallEnableINTEL\0" // IR(16945, 17)
  "FuseLoopsInFunctionINTEL\0" // IR(16962, 25)
  "MathOpDSPModeINTEL\0" // IR(16987, 19)
  "AliasScopeINTEL\0" // IR(17006, 16)
  "NoAliasINTEL\0" // IR(17022, 13)
  "InitiationIntervalINTEL\0" // IR(17035, 24)
  "MaxConcurrencyINTEL\0" // IR(17059, 20)
  "PipelineEnableINTEL\0" // IR(17079, 20)
  "BufferLocationINTEL\0" // IR(17099, 20)
  "IOPipeStorageINTEL\0" // IR(17119, 19)
  "SPV_OPERAND_TYPE_FPOPERATION_MODE\0" // IR(17138, 34)
  "FunctionFloatingPointModeINTEL\0" // IR(17172, 31)
  "SingleElementVectorINTEL\0" // IR(17203, 25)
  "VectorComputeCallableFunctionINTEL\0" // IR(17228, 35)
  "MediaBlockIOINTEL\0" // IR(17263, 18)
  "StallFreeINTEL\0" // IR(17281, 15)
  "SPV_OPERAND_TYPE_LITERAL_FLOAT\0" // IR(17296, 31)
  "FPMaxErrorDecorationINTEL\0" // IR(17327, 26)
  "LatencyControlLabelINTEL\0" // IR(17353, 25)
  "LatencyControlConstraintINTEL\0" // IR(17378, 30)
  "ConduitKernelArgumentINTEL\0" // IR(17408, 27)
  "RegisterMapKernelArgumentINTEL\0" // IR(17435, 31)
  "MMHostInterfaceAddressWidthINTEL\0" // IR(17466, 33)
  "MMHostInterfaceDataWidthINTEL\0" // IR(17499, 30)
  "MMHostInterfaceLatencyINTEL\0" // IR(17529, 28)
  "SPV_OPERAND_TYPE_ACCESS_QUALIFIER\0" // IR(17557, 34)
  "MMHostInterfaceReadWriteModeINTEL\0" // IR(17591, 34)
  "MMHostInterfaceMaxBurstINTEL\0" // IR(17625, 29)
  "MMHostInterfaceWaitRequestINTEL\0" // IR(17654, 32)
  "StableKernelArgumentINTEL\0" // IR(17686, 26)
  "SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER\0" // IR(17712, 39)
  "HostAccessINTEL\0" // IR(17751, 16)
  "SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER\0" // IR(17767, 47)
  "InitModeINTEL\0" // IR(17814, 14)
  "ImplementInRegisterMapINTEL\0" // IR(17828, 28)
  "SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL\0" // IR(17856, 36)
  "CacheControlLoadINTEL\0" // IR(17892, 22)
  "SPV_OPERAND_TYPE_STORE_CACHE_CONTROL\0" // IR(17914, 37)
  "CacheControlStoreINTEL\0" // IR(17951, 23)
  "1D\0" // IR(17974, 3)
  "2D\0" // IR(17977, 3)
  "3D\0" // IR(17980, 3)
  "Cube\0" // IR(17983, 5)
  "Rect\0" // IR(17988, 5)
  "Buffer\0" // IR(17993, 7)
  "SubpassData\0" // IR(18000, 12)
  "TileImageDataEXT\0" // IR(18012, 17)
  "Invocations\0" // IR(18029, 12)
  "SpacingEqual\0" // IR(18041, 13)
  "SpacingFractionalEven\0" // IR(18054, 22)
  "SpacingFractionalOdd\0" // IR(18076, 21)
  "VertexOrderCw\0" // IR(18097, 14)
  "VertexOrderCcw\0" // IR(18111, 15)
  "PixelCenterInteger\0" // IR(18126, 19)
  "OriginUpperLeft\0" // IR(18145, 16)
  "OriginLowerLeft\0" // IR(18161, 16)
  "EarlyFragmentTests\0" // IR(18177, 19)
  "PointMode\0" // IR(18196, 10)
  "Xfb\0" // IR(18206, 4)
  "DepthReplacing\0" // IR(18210, 15)
  "DepthGreater\0" // IR(18225, 13)
  "DepthLess\0" // IR(18238, 10)
  "DepthUnchanged\0" // IR(18248, 15)
  "LocalSize\0" // IR(18263, 10)
  "LocalSizeHint\0" // IR(18273, 14)
  "InputPoints\0" // IR(18287, 12)
  "InputLines\0" // IR(18299, 11)
  "InputLinesAdjacency\0" // IR(18310, 20)
  "Triangles\0" // IR(18330, 10)
  "InputTrianglesAdjacency\0" // IR(18340, 24)
  "Quads\0" // IR(18364, 6)
  "Isolines\0" // IR(18370, 9)
  "OutputVertices\0" // IR(18379, 15)
  "OutputPoints\0" // IR(18394, 13)
  "OutputLineStrip\0" // IR(18407, 16)
  "OutputTriangleStrip\0" // IR(18423, 20)
  "VecTypeHint\0" // IR(18443, 12)
  "ContractionOff\0" // IR(18455, 15)
  "Initializer\0" // IR(18470, 12)
  "Finalizer\0" // IR(18482, 10)
  "SubgroupsPerWorkgroup\0" // IR(18492, 22)
  "SubgroupsPerWorkgroupId\0" // IR(18514, 24)
  "LocalSizeId\0" // IR(18538, 12)
  "LocalSizeHintId\0" // IR(18550, 16)
  "NonCoherentColorAttachmentReadEXT\0" // IR(18566, 34)
  "NonCoherentDepthAttachmentReadEXT\0" // IR(18600, 34)
  "NonCoherentStencilAttachmentReadEXT\0" // IR(18634, 36)
  "SubgroupUniformControlFlowKHR\0" // IR(18670, 30)
  "PostDepthCoverage\0" // IR(18700, 18)
  "NonCoherentTileAttachmentReadQCOM\0" // IR(18718, 34)
  "TileShadingRateQCOM\0" // IR(18752, 20)
  "EarlyAndLateFragmentTestsAMD\0" // IR(18772, 29)
  "StencilRefReplacingEXT\0" // IR(18801, 23)
  "CoalescingAMDX\0" // IR(18824, 15)
  "IsApiEntryAMDX\0" // IR(18839, 15)
  "MaxNodeRecursionAMDX\0" // IR(18854, 21)
  "StaticNumWorkgroupsAMDX\0" // IR(18875, 24)
  "MaxNumWorkgroupsAMDX\0" // IR(18899, 21)
  "StencilRefUnchangedFrontAMD\0" // IR(18920, 28)
  "StencilRefGreaterFrontAMD\0" // IR(18948, 26)
  "StencilRefLessFrontAMD\0" // IR(18974, 23)
  "StencilRefUnchangedBackAMD\0" // IR(18997, 27)
  "StencilRefGreaterBackAMD\0" // IR(19024, 25)
  "StencilRefLessBackAMD\0" // IR(19049, 22)
  "QuadDerivativesKHR\0" // IR(19071, 19)
  "RequireFullQuadsKHR\0" // IR(19090, 20)
  "SharesInputWithAMDX\0" // IR(19110, 20)
  "OutputLinesEXT\0" // IR(19130, 15)
  "OutputLinesNV\0" // IR(19145, 14)
  "OutputPrimitivesEXT\0" // IR(19159, 20)
  "OutputPrimitivesNV\0" // IR(19179, 19)
  "DerivativeGroupQuadsKHR\0" // IR(19198, 24)
  "DerivativeGroupQuadsNV\0" // IR(19222, 23)
  "DerivativeGroupLinearKHR\0" // IR(19245, 25)
  "DerivativeGroupLinearNV\0" // IR(19270, 24)
  "OutputTrianglesEXT\0" // IR(19294, 19)
  "OutputTrianglesNV\0" // IR(19313, 18)
  "PixelInterlockOrderedEXT\0" // IR(19331, 25)
  "PixelInterlockUnorderedEXT\0" // IR(19356, 27)
  "SampleInterlockOrderedEXT\0" // IR(19383, 26)
  "SampleInterlockUnorderedEXT\0" // IR(19409, 28)
  "ShadingRateInterlockOrderedEXT\0" // IR(19437, 31)
  "ShadingRateInterlockUnorderedEXT\0" // IR(19468, 33)
  "SharedLocalMemorySizeINTEL\0" // IR(19501, 27)
  "RoundingModeRTPINTEL\0" // IR(19528, 21)
  "RoundingModeRTNINTEL\0" // IR(19549, 21)
  "FloatingPointModeALTINTEL\0" // IR(19570, 26)
  "FloatingPointModeIEEEINTEL\0" // IR(19596, 27)
  "MaxWorkgroupSizeINTEL\0" // IR(19623, 22)
  "MaxWorkDimINTEL\0" // IR(19645, 16)
  "NoGlobalOffsetINTEL\0" // IR(19661, 20)
  "NumSIMDWorkitemsINTEL\0" // IR(19681, 22)
  "SchedulerTargetFmaxMhzINTEL\0" // IR(19703, 28)
  "MaximallyReconvergesKHR\0" // IR(19731, 24)
  "FPFastMathDefault\0" // IR(19755, 18)
  "StreamingInterfaceINTEL\0" // IR(19773, 24)
  "RegisterMapInterfaceINTEL\0" // IR(19797, 26)
  "NamedBarrierCountINTEL\0" // IR(19823, 23)
  "MaximumRegistersINTEL\0" // IR(19846, 22)
  "MaximumRegistersIdINTEL\0" // IR(19868, 24)
  "SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS\0" // IR(19892, 51)
  "NamedMaximumRegistersINTEL\0" // IR(19943, 27)
  "Vertex\0" // IR(19970, 7)
  "TessellationControl\0" // IR(19977, 20)
  "TessellationEvaluation\0" // IR(19997, 23)
  "GLCompute\0" // IR(20020, 10)
  "TaskNV\0" // IR(20030, 7)
  "MeshNV\0" // IR(20037, 7)
  "RayGenerationKHR\0" // IR(20044, 17)
  "RayGenerationNV\0" // IR(20061, 16)
  "IntersectionKHR\0" // IR(20077, 16)
  "IntersectionNV\0" // IR(20093, 15)
  "AnyHitKHR\0" // IR(20108, 10)
  "AnyHitNV\0" // IR(20118, 9)
  "ClosestHitKHR\0" // IR(20127, 14)
  "ClosestHitNV\0" // IR(20141, 13)
  "MissKHR\0" // IR(20154, 8)
  "MissNV\0" // IR(20162, 7)
  "CallableKHR\0" // IR(20169, 12)
  "CallableNV\0" // IR(20181, 11)
  "TaskEXT\0" // IR(20192, 8)
  "MeshEXT\0" // IR(20200, 8)
  "Preserve\0" // IR(20208, 9)
  "FlushToZero\0" // IR(20217, 12)
  "BFloat16KHR\0" // IR(20229, 12)
  "IEEE\0" // IR(20241, 5)
  "ALT\0" // IR(20246, 4)
  "NotNaN\0" // IR(20250, 7)
  "NotInf\0" // IR(20257, 7)
  "NSZ\0" // IR(20264, 4)
  "AllowRecip\0" // IR(20268, 11)
  "Fast\0" // IR(20279, 5)
  "AllowContract\0" // IR(20284, 14)
  "AllowContractFastINTEL\0" // IR(20298, 23)
  "AllowReassoc\0" // IR(20321, 13)
  "AllowReassocINTEL\0" // IR(20334, 18)
  "AllowTransform\0" // IR(20352, 15)
  "RTE\0" // IR(20367, 4)
  "RTZ\0" // IR(20371, 4)
  "RTP\0" // IR(20375, 4)
  "RTN\0" // IR(20379, 4)
  "Vertical2Pixels\0" // IR(20383, 16)
  "Vertical4Pixels\0" // IR(20399, 16)
  "Horizontal2Pixels\0" // IR(20415, 18)
  "Horizontal4Pixels\0" // IR(20433, 18)
  "Inline\0" // IR(20451, 7)
  "DontInline\0" // IR(20458, 11)
  "Pure\0" // IR(20469, 5)
  "Const\0" // IR(20474, 6)
  "Zext\0" // IR(20480, 5)
  "Sext\0" // IR(20485, 5)
  "ByVal\0" // IR(20490, 6)
  "Sret\0" // IR(20496, 5)
  "NoAlias\0" // IR(20501, 8)
  "NoCapture\0" // IR(20509, 10)
  "NoWrite\0" // IR(20519, 8)
  "NoReadWrite\0" // IR(20527, 12)
  "RuntimeAlignedINTEL\0" // IR(20539, 20)
  "Reduce\0" // IR(20559, 7)
  "InclusiveScan\0" // IR(20566, 14)
  "ExclusiveScan\0" // IR(20580, 14)
  "ClusteredReduce\0" // IR(20594, 16)
  "PartitionedReduceNV\0" // IR(20610, 20)
  "PartitionedInclusiveScanNV\0" // IR(20630, 27)
  "PartitionedExclusiveScanNV\0" // IR(20657, 27)
  "NoneINTEL\0" // IR(20684, 10)
  "ReadINTEL\0" // IR(20694, 10)
  "WriteINTEL\0" // IR(20704, 11)
  "ReadWriteINTEL\0" // IR(20715, 15)
  "Bias\0" // IR(20730, 5)
  "Lod\0" // IR(20735, 4)
  "Grad\0" // IR(20739, 5)
  "ConstOffset\0" // IR(20744, 12)
  "ConstOffsets\0" // IR(20756, 13)
  "MakeTexelAvailable\0" // IR(20769, 19)
  "MakeTexelAvailableKHR\0" // IR(20788, 22)
  "MakeTexelVisible\0" // IR(20810, 17)
  "MakeTexelVisibleKHR\0" // IR(20827, 20)
  "NonPrivateTexel\0" // IR(20847, 16)
  "NonPrivateTexelKHR\0" // IR(20863, 19)
  "VolatileTexel\0" // IR(20882, 14)
  "VolatileTexelKHR\0" // IR(20896, 17)
  "SignExtend\0" // IR(20913, 11)
  "ZeroExtend\0" // IR(20924, 11)
  "Nontemporal\0" // IR(20935, 12)
  "Offsets\0" // IR(20947, 8)
  "SnormInt8\0" // IR(20955, 10)
  "SnormInt16\0" // IR(20965, 11)
  "UnormInt8\0" // IR(20976, 10)
  "UnormInt16\0" // IR(20986, 11)
  "UnormShort565\0" // IR(20997, 14)
  "UnormShort555\0" // IR(21011, 14)
  "UnormInt101010\0" // IR(21025, 15)
  "SignedInt8\0" // IR(21040, 11)
  "SignedInt16\0" // IR(21051, 12)
  "SignedInt32\0" // IR(21063, 12)
  "UnsignedInt8\0" // IR(21075, 13)
  "UnsignedInt16\0" // IR(21088, 14)
  "UnsignedInt32\0" // IR(21102, 14)
  "HalfFloat\0" // IR(21116, 10)
  "UnormInt24\0" // IR(21126, 11)
  "UnormInt101010_2\0" // IR(21137, 17)
  "UnormInt10X6EXT\0" // IR(21154, 16)
  "UnsignedIntRaw10EXT\0" // IR(21170, 20)
  "UnsignedIntRaw12EXT\0" // IR(21190, 20)
  "UnormInt2_101010EXT\0" // IR(21210, 20)
  "UnsignedInt10X6EXT\0" // IR(21230, 19)
  "UnsignedInt12X4EXT\0" // IR(21249, 19)
  "UnsignedInt14X2EXT\0" // IR(21268, 19)
  "UnormInt12X4EXT\0" // IR(21287, 16)
  "UnormInt14X2EXT\0" // IR(21303, 16)
  "R\0" // IR(21319, 2)
  "A\0" // IR(21321, 2)
  "RG\0" // IR(21323, 3)
  "RA\0" // IR(21326, 3)
  "RGB\0" // IR(21329, 4)
  "RGBA\0" // IR(21333, 5)
  "BGRA\0" // IR(21338, 5)
  "ARGB\0" // IR(21343, 5)
  "Intensity\0" // IR(21348, 10)
  "Luminance\0" // IR(21358, 10)
  "Rx\0" // IR(21368, 3)
  "RGx\0" // IR(21371, 4)
  "RGBx\0" // IR(21375, 5)
  "Depth\0" // IR(21380, 6)
  "DepthStencil\0" // IR(21386, 13)
  "sRGB\0" // IR(21399, 5)
  "sRGBx\0" // IR(21404, 6)
  "sRGBA\0" // IR(21410, 6)
  "sBGRA\0" // IR(21416, 6)
  "ABGR\0" // IR(21422, 5)
  "InitOnDeviceReprogramINTEL\0" // IR(21427, 27)
  "InitOnDeviceResetINTEL\0" // IR(21454, 23)
  "NoWait\0" // IR(21477, 7)
  "WaitKernel\0" // IR(21484, 11)
  "WaitWorkGroup\0" // IR(21495, 14)
  "CmdExecTime\0" // IR(21509, 12)
  "MayUsePrintf\0" // IR(21521, 13)
  "Export\0" // IR(21534, 7)
  "Import\0" // IR(21541, 7)
  "LinkOnceODR\0" // IR(21548, 12)
  "UncachedINTEL\0" // IR(21560, 14)
  "CachedINTEL\0" // IR(21574, 12)
  "StreamingINTEL\0" // IR(21586, 15)
  "InvalidateAfterReadINTEL\0" // IR(21601, 25)
  "ConstCachedINTEL\0" // IR(21626, 17)
  "Unroll\0" // IR(21643, 7)
  "DontUnroll\0" // IR(21650, 11)
  "DependencyInfinite\0" // IR(21661, 19)
  "DependencyLength\0" // IR(21680, 17)
  "MinIterations\0" // IR(21697, 14)
  "MaxIterations\0" // IR(21711, 14)
  "IterationMultiple\0" // IR(21725, 18)
  "PeelCount\0" // IR(21743, 10)
  "PartialCount\0" // IR(21753, 13)
  "DependencyArrayINTEL\0" // IR(21766, 21)
  "LoopCoalesceINTEL\0" // IR(21787, 18)
  "MaxInterleavingINTEL\0" // IR(21805, 21)
  "SpeculatedIterationsINTEL\0" // IR(21826, 26)
  "NoFusionINTEL\0" // IR(21852, 14)
  "LoopCountINTEL\0" // IR(21866, 15)
  "MaxReinvocationDelayINTEL\0" // IR(21881, 26)
  "MatrixASignedComponentsINTEL\0" // IR(21907, 29)
  "MatrixBSignedComponentsINTEL\0" // IR(21936, 29)
  "MatrixCBFloat16INTEL\0" // IR(21965, 21)
  "MatrixResultBFloat16INTEL\0" // IR(21986, 26)
  "MatrixAPackedInt8INTEL\0" // IR(22012, 23)
  "MatrixBPackedInt8INTEL\0" // IR(22035, 23)
  "MatrixAPackedInt4INTEL\0" // IR(22058, 23)
  "MatrixBPackedInt4INTEL\0" // IR(22081, 23)
  "MatrixATF32INTEL\0" // IR(22104, 17)
  "MatrixBTF32INTEL\0" // IR(22121, 17)
  "MatrixAPackedFloat16INTEL\0" // IR(22138, 26)
  "MatrixBPackedFloat16INTEL\0" // IR(22164, 26)
  "MatrixAPackedBFloat16INTEL\0" // IR(22190, 27)
  "MatrixBPackedBFloat16INTEL\0" // IR(22217, 27)
  "Aligned\0" // IR(22244, 8)
  "MakePointerAvailable\0" // IR(22252, 21)
  "MakePointerAvailableKHR\0" // IR(22273, 24)
  "MakePointerVisible\0" // IR(22297, 19)
  "MakePointerVisibleKHR\0" // IR(22316, 22)
  "NonPrivatePointer\0" // IR(22338, 18)
  "NonPrivatePointerKHR\0" // IR(22356, 21)
  "AliasScopeINTELMask\0" // IR(22377, 20)
  "NoAliasINTELMask\0" // IR(22397, 17)
  "Simple\0" // IR(22414, 7)
  "GLSL450\0" // IR(22421, 8)
  "OpenCL\0" // IR(22429, 7)
  "Vulkan\0" // IR(22436, 7)
  "VulkanKHR\0" // IR(22443, 10)
  "Relaxed\0" // IR(22453, 8)
  "Acquire\0" // IR(22461, 8)
  "Release\0" // IR(22469, 8)
  "AcquireRelease\0" // IR(22477, 15)
  "SequentiallyConsistent\0" // IR(22492, 23)
  "UniformMemory\0" // IR(22515, 14)
  "SubgroupMemory\0" // IR(22529, 15)
  "WorkgroupMemory\0" // IR(22544, 16)
  "CrossWorkgroupMemory\0" // IR(22560, 21)
  "AtomicCounterMemory\0" // IR(22581, 20)
  "ImageMemory\0" // IR(22601, 12)
  "OutputMemory\0" // IR(22613, 13)
  "OutputMemoryKHR\0" // IR(22626, 16)
  "MakeAvailable\0" // IR(22642, 14)
  "MakeAvailableKHR\0" // IR(22656, 17)
  "MakeVisible\0" // IR(22673, 12)
  "MakeVisibleKHR\0" // IR(22685, 15)
  "AutoINTEL\0" // IR(22700, 10)
  "WRAP\0" // IR(22710, 5)
  "SAT\0" // IR(22715, 4)
  "SAT_ZERO\0" // IR(22719, 9)
  "SAT_SYM\0" // IR(22728, 8)
  "PackedVectorFormat4x8Bit\0" // IR(22736, 25)
  "PackedVectorFormat4x8BitKHR\0" // IR(22761, 28)
  "TRN\0" // IR(22789, 4)
  "TRN_ZERO\0" // IR(22793, 9)
  "RND\0" // IR(22802, 4)
  "RND_ZERO\0" // IR(22806, 9)
  "RND_INF\0" // IR(22815, 8)
  "RND_MIN_INF\0" // IR(22823, 12)
  "RND_CONV\0" // IR(22835, 9)
  "RND_CONV_ODD\0" // IR(22844, 13)
  "RobustnessPerComponentNV\0" // IR(22857, 25)
  "RobustnessPerElementNV\0" // IR(22882, 23)
  "OpaqueKHR\0" // IR(22905, 10)
  "NoOpaqueKHR\0" // IR(22915, 12)
  "TerminateOnFirstHitKHR\0" // IR(22927, 23)
  "SkipClosestHitShaderKHR\0" // IR(22950, 24)
  "CullBackFacingTrianglesKHR\0" // IR(22974, 27)
  "CullFrontFacingTrianglesKHR\0" // IR(23001, 28)
  "CullOpaqueKHR\0" // IR(23029, 14)
  "CullNoOpaqueKHR\0" // IR(23043, 16)
  "SkipTrianglesKHR\0" // IR(23059, 17)
  "SkipBuiltinPrimitivesNV\0" // IR(23076, 24)
  "SkipAABBsKHR\0" // IR(23100, 13)
  "ForceOpacityMicromap2StateEXT\0" // IR(23113, 30)
  "RayQueryCandidateIntersectionTriangleKHR\0" // IR(23143, 41)
  "RayQueryCandidateIntersectionAABBKHR\0" // IR(23184, 37)
  "RayQueryCommittedIntersectionNoneKHR\0" // IR(23221, 37)
  "RayQueryCommittedIntersectionTriangleKHR\0" // IR(23258, 41)
  "RayQueryCommittedIntersectionGeneratedKHR\0" // IR(23299, 42)
  "RayQueryCandidateIntersectionKHR\0" // IR(23341, 33)
  "RayQueryCommittedIntersectionKHR\0" // IR(23374, 33)
  "ClampToEdge\0" // IR(23407, 12)
  "Clamp\0" // IR(23419, 6)
  "Repeat\0" // IR(23425, 7)
  "RepeatMirrored\0" // IR(23432, 15)
  "Nearest\0" // IR(23447, 8)
  "Linear\0" // IR(23455, 7)
  "Unknown\0" // IR(23462, 8)
  "Rgba32f\0" // IR(23470, 8)
  "Rgba16f\0" // IR(23478, 8)
  "R32f\0" // IR(23486, 5)
  "Rgba8\0" // IR(23491, 6)
  "Rgba8Snorm\0" // IR(23497, 11)
  "Rg32f\0" // IR(23508, 6)
  "Rg16f\0" // IR(23514, 6)
  "R11fG11fB10f\0" // IR(23520, 13)
  "R16f\0" // IR(23533, 5)
  "Rgba16\0" // IR(23538, 7)
  "Rgb10A2\0" // IR(23545, 8)
  "Rg16\0" // IR(23553, 5)
  "Rg8\0" // IR(23558, 4)
  "R16\0" // IR(23562, 4)
  "R8\0" // IR(23566, 3)
  "Rgba16Snorm\0" // IR(23569, 12)
  "Rg16Snorm\0" // IR(23581, 10)
  "Rg8Snorm\0" // IR(23591, 9)
  "R16Snorm\0" // IR(23600, 9)
  "R8Snorm\0" // IR(23609, 8)
  "Rgba32i\0" // IR(23617, 8)
  "Rgba16i\0" // IR(23625, 8)
  "Rgba8i\0" // IR(23633, 7)
  "R32i\0" // IR(23640, 5)
  "Rg32i\0" // IR(23645, 6)
  "Rg16i\0" // IR(23651, 6)
  "Rg8i\0" // IR(23657, 5)
  "R16i\0" // IR(23662, 5)
  "R8i\0" // IR(23667, 4)
  "Rgba32ui\0" // IR(23671, 9)
  "Rgba16ui\0" // IR(23680, 9)
  "Rgba8ui\0" // IR(23689, 8)
  "R32ui\0" // IR(23697, 6)
  "Rgb10a2ui\0" // IR(23703, 10)
  "Rg32ui\0" // IR(23713, 7)
  "Rg16ui\0" // IR(23720, 7)
  "Rg8ui\0" // IR(23727, 6)
  "R16ui\0" // IR(23733, 6)
  "R8ui\0" // IR(23739, 5)
  "R64ui\0" // IR(23744, 6)
  "R64i\0" // IR(23750, 5)
  "CrossDevice\0" // IR(23755, 12)
  "Device\0" // IR(23767, 7)
  "Workgroup\0" // IR(23774, 10)
  "Subgroup\0" // IR(23784, 9)
  "Invocation\0" // IR(23793, 11)
  "QueueFamily\0" // IR(23804, 12)
  "QueueFamilyKHR\0" // IR(23816, 15)
  "ShaderCallKHR\0" // IR(23831, 14)
  "Flatten\0" // IR(23845, 8)
  "DontFlatten\0" // IR(23853, 12)
  "IdentifierPossibleDuplicates\0" // IR(23865, 29)
  "FlagUnknownPhysicalLayout\0" // IR(23894, 26)
  "ESSL\0" // IR(23920, 5)
  "GLSL\0" // IR(23925, 5)
  "OpenCL_C\0" // IR(23930, 9)
  "OpenCL_CPP\0" // IR(23939, 11)
  "HLSL\0" // IR(23950, 5)
  "CPP_for_OpenCL\0" // IR(23955, 15)
  "SYCL\0" // IR(23970, 5)
  "HERO_C\0" // IR(23975, 7)
  "NZSL\0" // IR(23982, 5)
  "WGSL\0" // IR(23987, 5)
  "Slang\0" // IR(23992, 6)
  "Zig\0" // IR(23998, 4)
  "Rust\0" // IR(24002, 5)
  "UniformConstant\0" // IR(24007, 16)
  "Input\0" // IR(24023, 6)
  "Output\0" // IR(24029, 7)
  "CrossWorkgroup\0" // IR(24036, 15)
  "Private\0" // IR(24051, 8)
  "Function\0" // IR(24059, 9)
  "Generic\0" // IR(24068, 8)
  "PushConstant\0" // IR(24076, 13)
  "AtomicCounter\0" // IR(24089, 14)
  "Image\0" // IR(24103, 6)
  "StorageBuffer\0" // IR(24109, 14)
  "TileImageEXT\0" // IR(24123, 13)
  "TileAttachmentQCOM\0" // IR(24136, 19)
  "NodePayloadAMDX\0" // IR(24155, 16)
  "CallableDataKHR\0" // IR(24171, 16)
  "CallableDataNV\0" // IR(24187, 15)
  "IncomingCallableDataKHR\0" // IR(24202, 24)
  "IncomingCallableDataNV\0" // IR(24226, 23)
  "RayPayloadKHR\0" // IR(24249, 14)
  "RayPayloadNV\0" // IR(24263, 13)
  "HitAttributeKHR\0" // IR(24276, 16)
  "HitAttributeNV\0" // IR(24292, 15)
  "IncomingRayPayloadKHR\0" // IR(24307, 22)
  "IncomingRayPayloadNV\0" // IR(24329, 21)
  "ShaderRecordBufferKHR\0" // IR(24350, 22)
  "ShaderRecordBufferNV\0" // IR(24372, 21)
  "PhysicalStorageBuffer\0" // IR(24393, 22)
  "PhysicalStorageBufferEXT\0" // IR(24415, 25)
  "HitObjectAttributeNV\0" // IR(24440, 21)
  "TaskPayloadWorkgroupEXT\0" // IR(24461, 24)
  "CodeSectionINTEL\0" // IR(24485, 17)
  "DeviceOnlyINTEL\0" // IR(24502, 16)
  "HostOnlyINTEL\0" // IR(24518, 14)
  "WriteThroughINTEL\0" // IR(24532, 18)
  "WriteBackINTEL\0" // IR(24550, 15)
  "TensorView\0" // IR(24565, 11)
  "DecodeFunc\0" // IR(24576, 11)
  "Undefined\0" // IR(24587, 10)
  "Nop\0" // IR(24597, 4)
  "SPV_OPERAND_TYPE_TYPE_ID\0" // IR(24601, 25)
  "SPV_OPERAND_TYPE_RESULT_ID\0" // IR(24626, 27)
  "Undef\0" // IR(24653, 6)
  "SourceContinued\0" // IR(24659, 16)
  "SPV_OPERAND_TYPE_SOURCE_LANGUAGE\0" // IR(24675, 33)
  "SPV_OPERAND_TYPE_OPTIONAL_ID\0" // IR(24708, 29)
  "SPV_OPERAND_TYPE_OPTIONAL_LITERAL_STRING\0" // IR(24737, 41)
  "Source\0" // IR(24778, 7)
  "SourceExtension\0" // IR(24785, 16)
  "Name\0" // IR(24801, 5)
  "MemberName\0" // IR(24806, 11)
  "String\0" // IR(24817, 7)
  "Line\0" // IR(24824, 5)
  "Extension\0" // IR(24829, 10)
  "ExtInstImport\0" // IR(24839, 14)
  "SPV_OPERAND_TYPE_EXTENSION_INSTRUCTION_NUMBER\0" // IR(24853, 46)
  "ExtInst\0" // IR(24899, 8)
  "SPV_OPERAND_TYPE_ADDRESSING_MODEL\0" // IR(24907, 34)
  "SPV_OPERAND_TYPE_MEMORY_MODEL\0" // IR(24941, 30)
  "MemoryModel\0" // IR(24971, 12)
  "SPV_OPERAND_TYPE_EXECUTION_MODEL\0" // IR(24983, 33)
  "SPV_OPERAND_TYPE_VARIABLE_ID\0" // IR(25016, 29)
  "EntryPoint\0" // IR(25045, 11)
  "SPV_OPERAND_TYPE_EXECUTION_MODE\0" // IR(25056, 32)
  "ExecutionMode\0" // IR(25088, 14)
  "SPV_OPERAND_TYPE_CAPABILITY\0" // IR(25102, 28)
  "Capability\0" // IR(25130, 11)
  "TypeVoid\0" // IR(25141, 9)
  "TypeBool\0" // IR(25150, 9)
  "TypeInt\0" // IR(25159, 8)
  "SPV_OPERAND_TYPE_OPTIONAL_FPENCODING\0" // IR(25167, 37)
  "TypeFloat\0" // IR(25204, 10)
  "TypeVector\0" // IR(25214, 11)
  "TypeMatrix\0" // IR(25225, 11)
  "SPV_OPERAND_TYPE_DIMENSIONALITY\0" // IR(25236, 32)
  "SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT\0" // IR(25268, 38)
  "SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER\0" // IR(25306, 43)
  "TypeImage\0" // IR(25349, 10)
  "TypeSampler\0" // IR(25359, 12)
  "TypeSampledImage\0" // IR(25371, 17)
  "TypeArray\0" // IR(25388, 10)
  "TypeRuntimeArray\0" // IR(25398, 17)
  "TypeStruct\0" // IR(25415, 11)
  "TypeOpaque\0" // IR(25426, 11)
  "SPV_OPERAND_TYPE_STORAGE_CLASS\0" // IR(25437, 31)
  "TypePointer\0" // IR(25468, 12)
  "TypeFunction\0" // IR(25480, 13)
  "TypeEvent\0" // IR(25493, 10)
  "TypeDeviceEvent\0" // IR(25503, 16)
  "TypeReserveId\0" // IR(25519, 14)
  "TypeQueue\0" // IR(25533, 10)
  "TypePipe\0" // IR(25543, 9)
  "TypeForwardPointer\0" // IR(25552, 19)
  "ConstantTrue\0" // IR(25571, 13)
  "ConstantFalse\0" // IR(25584, 14)
  "SPV_OPERAND_TYPE_TYPED_LITERAL_NUMBER\0" // IR(25598, 38)
  "ConstantComposite\0" // IR(25636, 18)
  "SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE\0" // IR(25654, 41)
  "SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE\0" // IR(25695, 37)
  "ConstantSampler\0" // IR(25732, 16)
  "ConstantNull\0" // IR(25748, 13)
  "SpecConstantTrue\0" // IR(25761, 17)
  "SpecConstantFalse\0" // IR(25778, 18)
  "SpecConstant\0" // IR(25796, 13)
  "SpecConstantComposite\0" // IR(25809, 22)
  "SPV_OPERAND_TYPE_SPEC_CONSTANT_OP_NUMBER\0" // IR(25831, 41)
  "SpecConstantOp\0" // IR(25872, 15)
  "SPV_OPERAND_TYPE_FUNCTION_CONTROL\0" // IR(25887, 34)
  "FunctionParameter\0" // IR(25921, 18)
  "FunctionEnd\0" // IR(25939, 12)
  "FunctionCall\0" // IR(25951, 13)
  "Variable\0" // IR(25964, 9)
  "ImageTexelPointer\0" // IR(25973, 18)
  "SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS\0" // IR(25991, 40)
  "Load\0" // IR(26031, 5)
  "Store\0" // IR(26036, 6)
  "CopyMemory\0" // IR(26042, 11)
  "CopyMemorySized\0" // IR(26053, 16)
  "AccessChain\0" // IR(26069, 12)
  "InBoundsAccessChain\0" // IR(26081, 20)
  "PtrAccessChain\0" // IR(26101, 15)
  "ArrayLength\0" // IR(26116, 12)
  "GenericPtrMemSemantics\0" // IR(26128, 23)
  "InBoundsPtrAccessChain\0" // IR(26151, 23)
  "SPV_OPERAND_TYPE_DECORATION\0" // IR(26174, 28)
  "Decorate\0" // IR(26202, 9)
  "MemberDecorate\0" // IR(26211, 15)
  "DecorationGroup\0" // IR(26226, 16)
  "GroupDecorate\0" // IR(26242, 14)
  "SPV_OPERAND_TYPE_VARIABLE_ID_LITERAL_INTEGER\0" // IR(26256, 45)
  "GroupMemberDecorate\0" // IR(26301, 20)
  "VectorExtractDynamic\0" // IR(26321, 21)
  "VectorInsertDynamic\0" // IR(26342, 20)
  "VectorShuffle\0" // IR(26362, 14)
  "CompositeConstruct\0" // IR(26376, 19)
  "CompositeExtract\0" // IR(26395, 17)
  "CompositeInsert\0" // IR(26412, 16)
  "CopyObject\0" // IR(26428, 11)
  "Transpose\0" // IR(26439, 10)
  "SampledImage\0" // IR(26449, 13)
  "SPV_OPERAND_TYPE_OPTIONAL_IMAGE\0" // IR(26462, 32)
  "ImageSampleImplicitLod\0" // IR(26494, 23)
  "SPV_OPERAND_TYPE_IMAGE\0" // IR(26517, 23)
  "ImageSampleExplicitLod\0" // IR(26540, 23)
  "ImageSampleDrefImplicitLod\0" // IR(26563, 27)
  "ImageSampleDrefExplicitLod\0" // IR(26590, 27)
  "ImageSampleProjImplicitLod\0" // IR(26617, 27)
  "ImageSampleProjExplicitLod\0" // IR(26644, 27)
  "ImageSampleProjDrefImplicitLod\0" // IR(26671, 31)
  "ImageSampleProjDrefExplicitLod\0" // IR(26702, 31)
  "ImageFetch\0" // IR(26733, 11)
  "ImageGather\0" // IR(26744, 12)
  "ImageDrefGather\0" // IR(26756, 16)
  "ImageRead\0" // IR(26772, 10)
  "ImageWrite\0" // IR(26782, 11)
  "ImageQueryFormat\0" // IR(26793, 17)
  "ImageQueryOrder\0" // IR(26810, 16)
  "ImageQuerySizeLod\0" // IR(26826, 18)
  "ImageQuerySize\0" // IR(26844, 15)
  "ImageQueryLod\0" // IR(26859, 14)
  "ImageQueryLevels\0" // IR(26873, 17)
  "ImageQuerySamples\0" // IR(26890, 18)
  "ConvertFToU\0" // IR(26908, 12)
  "ConvertFToS\0" // IR(26920, 12)
  "ConvertSToF\0" // IR(26932, 12)
  "ConvertUToF\0" // IR(26944, 12)
  "UConvert\0" // IR(26956, 9)
  "SConvert\0" // IR(26965, 9)
  "FConvert\0" // IR(26974, 9)
  "QuantizeToF16\0" // IR(26983, 14)
  "ConvertPtrToU\0" // IR(26997, 14)
  "SatConvertSToU\0" // IR(27011, 15)
  "SatConvertUToS\0" // IR(27026, 15)
  "ConvertUToPtr\0" // IR(27041, 14)
  "PtrCastToGeneric\0" // IR(27055, 17)
  "GenericCastToPtr\0" // IR(27072, 17)
  "GenericCastToPtrExplicit\0" // IR(27089, 25)
  "Bitcast\0" // IR(27114, 8)
  "SNegate\0" // IR(27122, 8)
  "FNegate\0" // IR(27130, 8)
  "IAdd\0" // IR(27138, 5)
  "FAdd\0" // IR(27143, 5)
  "ISub\0" // IR(27148, 5)
  "FSub\0" // IR(27153, 5)
  "IMul\0" // IR(27158, 5)
  "FMul\0" // IR(27163, 5)
  "UDiv\0" // IR(27168, 5)
  "SDiv\0" // IR(27173, 5)
  "FDiv\0" // IR(27178, 5)
  "UMod\0" // IR(27183, 5)
  "SRem\0" // IR(27188, 5)
  "SMod\0" // IR(27193, 5)
  "FRem\0" // IR(27198, 5)
  "FMod\0" // IR(27203, 5)
  "VectorTimesScalar\0" // IR(27208, 18)
  "MatrixTimesScalar\0" // IR(27226, 18)
  "VectorTimesMatrix\0" // IR(27244, 18)
  "MatrixTimesVector\0" // IR(27262, 18)
  "MatrixTimesMatrix\0" // IR(27280, 18)
  "OuterProduct\0" // IR(27298, 13)
  "Dot\0" // IR(27311, 4)
  "IAddCarry\0" // IR(27315, 10)
  "ISubBorrow\0" // IR(27325, 11)
  "UMulExtended\0" // IR(27336, 13)
  "SMulExtended\0" // IR(27349, 13)
  "Any\0" // IR(27362, 4)
  "All\0" // IR(27366, 4)
  "IsNan\0" // IR(27370, 6)
  "IsInf\0" // IR(27376, 6)
  "IsFinite\0" // IR(27382, 9)
  "IsNormal\0" // IR(27391, 9)
  "SignBitSet\0" // IR(27400, 11)
  "LessOrGreater\0" // IR(27411, 14)
  "Ordered\0" // IR(27425, 8)
  "Unordered\0" // IR(27433, 10)
  "LogicalEqual\0" // IR(27443, 13)
  "LogicalNotEqual\0" // IR(27456, 16)
  "LogicalOr\0" // IR(27472, 10)
  "LogicalAnd\0" // IR(27482, 11)
  "LogicalNot\0" // IR(27493, 11)
  "Select\0" // IR(27504, 7)
  "IEqual\0" // IR(27511, 7)
  "INotEqual\0" // IR(27518, 10)
  "UGreaterThan\0" // IR(27528, 13)
  "SGreaterThan\0" // IR(27541, 13)
  "UGreaterThanEqual\0" // IR(27554, 18)
  "SGreaterThanEqual\0" // IR(27572, 18)
  "ULessThan\0" // IR(27590, 10)
  "SLessThan\0" // IR(27600, 10)
  "ULessThanEqual\0" // IR(27610, 15)
  "SLessThanEqual\0" // IR(27625, 15)
  "FOrdEqual\0" // IR(27640, 10)
  "FUnordEqual\0" // IR(27650, 12)
  "FOrdNotEqual\0" // IR(27662, 13)
  "FUnordNotEqual\0" // IR(27675, 15)
  "FOrdLessThan\0" // IR(27690, 13)
  "FUnordLessThan\0" // IR(27703, 15)
  "FOrdGreaterThan\0" // IR(27718, 16)
  "FUnordGreaterThan\0" // IR(27734, 18)
  "FOrdLessThanEqual\0" // IR(27752, 18)
  "FUnordLessThanEqual\0" // IR(27770, 20)
  "FOrdGreaterThanEqual\0" // IR(27790, 21)
  "FUnordGreaterThanEqual\0" // IR(27811, 23)
  "ShiftRightLogical\0" // IR(27834, 18)
  "ShiftRightArithmetic\0" // IR(27852, 21)
  "ShiftLeftLogical\0" // IR(27873, 17)
  "BitwiseOr\0" // IR(27890, 10)
  "BitwiseXor\0" // IR(27900, 11)
  "BitwiseAnd\0" // IR(27911, 11)
  "Not\0" // IR(27922, 4)
  "BitFieldInsert\0" // IR(27926, 15)
  "BitFieldSExtract\0" // IR(27941, 17)
  "BitFieldUExtract\0" // IR(27958, 17)
  "BitReverse\0" // IR(27975, 11)
  "BitCount\0" // IR(27986, 9)
  "DPdx\0" // IR(27995, 5)
  "DPdy\0" // IR(28000, 5)
  "Fwidth\0" // IR(28005, 7)
  "DPdxFine\0" // IR(28012, 9)
  "DPdyFine\0" // IR(28021, 9)
  "FwidthFine\0" // IR(28030, 11)
  "DPdxCoarse\0" // IR(28041, 11)
  "DPdyCoarse\0" // IR(28052, 11)
  "FwidthCoarse\0" // IR(28063, 13)
  "EmitVertex\0" // IR(28076, 11)
  "EndPrimitive\0" // IR(28087, 13)
  "EmitStreamVertex\0" // IR(28100, 17)
  "EndStreamPrimitive\0" // IR(28117, 19)
  "SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID\0" // IR(28136, 37)
  "ControlBarrier\0" // IR(28173, 15)
  "MemoryBarrier\0" // IR(28188, 14)
  "AtomicLoad\0" // IR(28202, 11)
  "AtomicStore\0" // IR(28213, 12)
  "AtomicExchange\0" // IR(28225, 15)
  "AtomicCompareExchange\0" // IR(28240, 22)
  "AtomicCompareExchangeWeak\0" // IR(28262, 26)
  "AtomicIIncrement\0" // IR(28288, 17)
  "AtomicIDecrement\0" // IR(28305, 17)
  "AtomicIAdd\0" // IR(28322, 11)
  "AtomicISub\0" // IR(28333, 11)
  "AtomicSMin\0" // IR(28344, 11)
  "AtomicUMin\0" // IR(28355, 11)
  "AtomicSMax\0" // IR(28366, 11)
  "AtomicUMax\0" // IR(28377, 11)
  "AtomicAnd\0" // IR(28388, 10)
  "AtomicOr\0" // IR(28398, 9)
  "AtomicXor\0" // IR(28407, 10)
  "Phi\0" // IR(28417, 4)
  "SPV_OPERAND_TYPE_LOOP_CONTROL\0" // IR(28421, 30)
  "LoopMerge\0" // IR(28451, 10)
  "SPV_OPERAND_TYPE_SELECTION_CONTROL\0" // IR(28461, 35)
  "SelectionMerge\0" // IR(28496, 15)
  "Label\0" // IR(28511, 6)
  "Branch\0" // IR(28517, 7)
  "BranchConditional\0" // IR(28524, 18)
  "SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER_ID\0" // IR(28542, 45)
  "Switch\0" // IR(28587, 7)
  "Kill\0" // IR(28594, 5)
  "Return\0" // IR(28599, 7)
  "ReturnValue\0" // IR(28606, 12)
  "Unreachable\0" // IR(28618, 12)
  "LifetimeStart\0" // IR(28630, 14)
  "LifetimeStop\0" // IR(28644, 13)
  "GroupAsyncCopy\0" // IR(28657, 15)
  "GroupWaitEvents\0" // IR(28672, 16)
  "GroupAll\0" // IR(28688, 9)
  "GroupAny\0" // IR(28697, 9)
  "GroupBroadcast\0" // IR(28706, 15)
  "SPV_OPERAND_TYPE_GROUP_OPERATION\0" // IR(28721, 33)
  "GroupIAdd\0" // IR(28754, 10)
  "GroupFAdd\0" // IR(28764, 10)
  "GroupFMin\0" // IR(28774, 10)
  "GroupUMin\0" // IR(28784, 10)
  "GroupSMin\0" // IR(28794, 10)
  "GroupFMax\0" // IR(28804, 10)
  "GroupUMax\0" // IR(28814, 10)
  "GroupSMax\0" // IR(28824, 10)
  "ReadPipe\0" // IR(28834, 9)
  "WritePipe\0" // IR(28843, 10)
  "ReservedReadPipe\0" // IR(28853, 17)
  "ReservedWritePipe\0" // IR(28870, 18)
  "ReserveReadPipePackets\0" // IR(28888, 23)
  "ReserveWritePipePackets\0" // IR(28911, 24)
  "CommitReadPipe\0" // IR(28935, 15)
  "CommitWritePipe\0" // IR(28950, 16)
  "IsValidReserveId\0" // IR(28966, 17)
  "GetNumPipePackets\0" // IR(28983, 18)
  "GetMaxPipePackets\0" // IR(29001, 18)
  "GroupReserveReadPipePackets\0" // IR(29019, 28)
  "GroupReserveWritePipePackets\0" // IR(29047, 29)
  "GroupCommitReadPipe\0" // IR(29076, 20)
  "GroupCommitWritePipe\0" // IR(29096, 21)
  "EnqueueMarker\0" // IR(29117, 14)
  "EnqueueKernel\0" // IR(29131, 14)
  "GetKernelNDrangeSubGroupCount\0" // IR(29145, 30)
  "GetKernelNDrangeMaxSubGroupSize\0" // IR(29175, 32)
  "GetKernelWorkGroupSize\0" // IR(29207, 23)
  "GetKernelPreferredWorkGroupSizeMultiple\0" // IR(29230, 40)
  "RetainEvent\0" // IR(29270, 12)
  "ReleaseEvent\0" // IR(29282, 13)
  "CreateUserEvent\0" // IR(29295, 16)
  "IsValidEvent\0" // IR(29311, 13)
  "SetUserEventStatus\0" // IR(29324, 19)
  "CaptureEventProfilingInfo\0" // IR(29343, 26)
  "GetDefaultQueue\0" // IR(29369, 16)
  "BuildNDRange\0" // IR(29385, 13)
  "ImageSparseSampleImplicitLod\0" // IR(29398, 29)
  "ImageSparseSampleExplicitLod\0" // IR(29427, 29)
  "ImageSparseSampleDrefImplicitLod\0" // IR(29456, 33)
  "ImageSparseSampleDrefExplicitLod\0" // IR(29489, 33)
  "ImageSparseSampleProjImplicitLod\0" // IR(29522, 33)
  "ImageSparseSampleProjExplicitLod\0" // IR(29555, 33)
  "ImageSparseSampleProjDrefImplicitLod\0" // IR(29588, 37)
  "ImageSparseSampleProjDrefExplicitLod\0" // IR(29625, 37)
  "ImageSparseFetch\0" // IR(29662, 17)
  "ImageSparseGather\0" // IR(29679, 18)
  "ImageSparseDrefGather\0" // IR(29697, 22)
  "ImageSparseTexelsResident\0" // IR(29719, 26)
  "NoLine\0" // IR(29745, 7)
  "AtomicFlagTestAndSet\0" // IR(29752, 21)
  "AtomicFlagClear\0" // IR(29773, 16)
  "ImageSparseRead\0" // IR(29789, 16)
  "SizeOf\0" // IR(29805, 7)
  "TypePipeStorage\0" // IR(29812, 16)
  "ConstantPipeStorage\0" // IR(29828, 20)
  "CreatePipeFromPipeStorage\0" // IR(29848, 26)
  "GetKernelLocalSizeForSubgroupCount\0" // IR(29874, 35)
  "GetKernelMaxNumSubgroups\0" // IR(29909, 25)
  "TypeNamedBarrier\0" // IR(29934, 17)
  "NamedBarrierInitialize\0" // IR(29951, 23)
  "MemoryNamedBarrier\0" // IR(29974, 19)
  "ModuleProcessed\0" // IR(29993, 16)
  "ExecutionModeId\0" // IR(30009, 16)
  "DecorateId\0" // IR(30025, 11)
  "GroupNonUniformElect\0" // IR(30036, 21)
  "GroupNonUniformAll\0" // IR(30057, 19)
  "GroupNonUniformAny\0" // IR(30076, 19)
  "GroupNonUniformAllEqual\0" // IR(30095, 24)
  "GroupNonUniformBroadcast\0" // IR(30119, 25)
  "GroupNonUniformBroadcastFirst\0" // IR(30144, 30)
  "GroupNonUniformInverseBallot\0" // IR(30174, 29)
  "GroupNonUniformBallotBitExtract\0" // IR(30203, 32)
  "GroupNonUniformBallotBitCount\0" // IR(30235, 30)
  "GroupNonUniformBallotFindLSB\0" // IR(30265, 29)
  "GroupNonUniformBallotFindMSB\0" // IR(30294, 29)
  "GroupNonUniformShuffleXor\0" // IR(30323, 26)
  "GroupNonUniformShuffleUp\0" // IR(30349, 25)
  "GroupNonUniformShuffleDown\0" // IR(30374, 27)
  "GroupNonUniformIAdd\0" // IR(30401, 20)
  "GroupNonUniformFAdd\0" // IR(30421, 20)
  "GroupNonUniformIMul\0" // IR(30441, 20)
  "GroupNonUniformFMul\0" // IR(30461, 20)
  "GroupNonUniformSMin\0" // IR(30481, 20)
  "GroupNonUniformUMin\0" // IR(30501, 20)
  "GroupNonUniformFMin\0" // IR(30521, 20)
  "GroupNonUniformSMax\0" // IR(30541, 20)
  "GroupNonUniformUMax\0" // IR(30561, 20)
  "GroupNonUniformFMax\0" // IR(30581, 20)
  "GroupNonUniformBitwiseAnd\0" // IR(30601, 26)
  "GroupNonUniformBitwiseOr\0" // IR(30627, 25)
  "GroupNonUniformBitwiseXor\0" // IR(30652, 26)
  "GroupNonUniformLogicalAnd\0" // IR(30678, 26)
  "GroupNonUniformLogicalOr\0" // IR(30704, 25)
  "GroupNonUniformLogicalXor\0" // IR(30729, 26)
  "GroupNonUniformQuadBroadcast\0" // IR(30755, 29)
  "GroupNonUniformQuadSwap\0" // IR(30784, 24)
  "CopyLogical\0" // IR(30808, 12)
  "PtrEqual\0" // IR(30820, 9)
  "PtrNotEqual\0" // IR(30829, 12)
  "PtrDiff\0" // IR(30841, 8)
  "ColorAttachmentReadEXT\0" // IR(30849, 23)
  "DepthAttachmentReadEXT\0" // IR(30872, 23)
  "StencilAttachmentReadEXT\0" // IR(30895, 25)
  "TerminateInvocation\0" // IR(30920, 20)
  "TypeUntypedPointerKHR\0" // IR(30940, 22)
  "UntypedVariableKHR\0" // IR(30962, 19)
  "UntypedAccessChainKHR\0" // IR(30981, 22)
  "UntypedInBoundsAccessChainKHR\0" // IR(31003, 30)
  "SubgroupFirstInvocationKHR\0" // IR(31033, 27)
  "UntypedPtrAccessChainKHR\0" // IR(31060, 25)
  "UntypedInBoundsPtrAccessChainKHR\0" // IR(31085, 33)
  "UntypedArrayLengthKHR\0" // IR(31118, 22)
  "UntypedPrefetchKHR\0" // IR(31140, 19)
  "SubgroupAllKHR\0" // IR(31159, 15)
  "SubgroupAnyKHR\0" // IR(31174, 15)
  "SubgroupAllEqualKHR\0" // IR(31189, 20)
  "SubgroupReadInvocationKHR\0" // IR(31209, 26)
  "ExtInstWithForwardRefsKHR\0" // IR(31235, 26)
  "TraceRayKHR\0" // IR(31261, 12)
  "ExecuteCallableKHR\0" // IR(31273, 19)
  "ConvertUToAccelerationStructureKHR\0" // IR(31292, 35)
  "IgnoreIntersectionKHR\0" // IR(31327, 22)
  "TerminateRayKHR\0" // IR(31349, 16)
  "SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT\0" // IR(31365, 47)
  "SDot\0" // IR(31412, 5)
  "SDotKHR\0" // IR(31417, 8)
  "UDot\0" // IR(31425, 5)
  "UDotKHR\0" // IR(31430, 8)
  "SUDot\0" // IR(31438, 6)
  "SUDotKHR\0" // IR(31444, 9)
  "SDotAccSat\0" // IR(31453, 11)
  "SDotAccSatKHR\0" // IR(31464, 14)
  "UDotAccSat\0" // IR(31478, 11)
  "UDotAccSatKHR\0" // IR(31489, 14)
  "SUDotAccSat\0" // IR(31503, 12)
  "SUDotAccSatKHR\0" // IR(31515, 15)
  "TypeCooperativeMatrixKHR\0" // IR(31530, 25)
  "CooperativeMatrixLoadKHR\0" // IR(31555, 25)
  "CooperativeMatrixStoreKHR\0" // IR(31580, 26)
  "SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS\0" // IR(31606, 54)
  "CooperativeMatrixMulAddKHR\0" // IR(31660, 27)
  "CooperativeMatrixLengthKHR\0" // IR(31687, 27)
  "ConstantCompositeReplicateEXT\0" // IR(31714, 30)
  "SpecConstantCompositeReplicateEXT\0" // IR(31744, 34)
  "CompositeConstructReplicateEXT\0" // IR(31778, 31)
  "TypeRayQueryKHR\0" // IR(31809, 16)
  "RayQueryInitializeKHR\0" // IR(31825, 22)
  "RayQueryTerminateKHR\0" // IR(31847, 21)
  "RayQueryGenerateIntersectionKHR\0" // IR(31868, 32)
  "RayQueryConfirmIntersectionKHR\0" // IR(31900, 31)
  "RayQueryProceedKHR\0" // IR(31931, 19)
  "RayQueryGetIntersectionTypeKHR\0" // IR(31950, 31)
  "ImageSampleWeightedQCOM\0" // IR(31981, 24)
  "ImageBoxFilterQCOM\0" // IR(32005, 19)
  "ImageBlockMatchSSDQCOM\0" // IR(32024, 23)
  "ImageBlockMatchSADQCOM\0" // IR(32047, 23)
  "ImageBlockMatchWindowSSDQCOM\0" // IR(32070, 29)
  "ImageBlockMatchWindowSADQCOM\0" // IR(32099, 29)
  "ImageBlockMatchGatherSSDQCOM\0" // IR(32128, 29)
  "ImageBlockMatchGatherSADQCOM\0" // IR(32157, 29)
  "GroupIAddNonUniformAMD\0" // IR(32186, 23)
  "GroupFAddNonUniformAMD\0" // IR(32209, 23)
  "GroupFMinNonUniformAMD\0" // IR(32232, 23)
  "GroupUMinNonUniformAMD\0" // IR(32255, 23)
  "GroupSMinNonUniformAMD\0" // IR(32278, 23)
  "GroupFMaxNonUniformAMD\0" // IR(32301, 23)
  "GroupUMaxNonUniformAMD\0" // IR(32324, 23)
  "GroupSMaxNonUniformAMD\0" // IR(32347, 23)
  "FragmentMaskFetchAMD\0" // IR(32370, 21)
  "FragmentFetchAMD\0" // IR(32391, 17)
  "ReadClockKHR\0" // IR(32408, 13)
  "AllocateNodePayloadsAMDX\0" // IR(32421, 25)
  "EnqueueNodePayloadsAMDX\0" // IR(32446, 24)
  "TypeNodePayloadArrayAMDX\0" // IR(32470, 25)
  "FinishWritingNodePayloadAMDX\0" // IR(32495, 29)
  "NodePayloadArrayLengthAMDX\0" // IR(32524, 27)
  "IsNodePayloadValidAMDX\0" // IR(32551, 23)
  "ConstantStringAMDX\0" // IR(32574, 19)
  "SpecConstantStringAMDX\0" // IR(32593, 23)
  "GroupNonUniformQuadAllKHR\0" // IR(32616, 26)
  "GroupNonUniformQuadAnyKHR\0" // IR(32642, 26)
  "HitObjectRecordHitMotionNV\0" // IR(32668, 27)
  "HitObjectRecordHitWithIndexMotionNV\0" // IR(32695, 36)
  "HitObjectRecordMissMotionNV\0" // IR(32731, 28)
  "HitObjectGetWorldToObjectNV\0" // IR(32759, 28)
  "HitObjectGetObjectToWorldNV\0" // IR(32787, 28)
  "HitObjectGetObjectRayDirectionNV\0" // IR(32815, 33)
  "HitObjectGetObjectRayOriginNV\0" // IR(32848, 30)
  "HitObjectTraceRayMotionNV\0" // IR(32878, 26)
  "HitObjectGetShaderRecordBufferHandleNV\0" // IR(32904, 39)
  "HitObjectGetShaderBindingTableRecordIndexNV\0" // IR(32943, 44)
  "HitObjectRecordEmptyNV\0" // IR(32987, 23)
  "HitObjectTraceRayNV\0" // IR(33010, 20)
  "HitObjectRecordHitNV\0" // IR(33030, 21)
  "HitObjectRecordHitWithIndexNV\0" // IR(33051, 30)
  "HitObjectRecordMissNV\0" // IR(33081, 22)
  "HitObjectExecuteShaderNV\0" // IR(33103, 25)
  "HitObjectGetCurrentTimeNV\0" // IR(33128, 26)
  "HitObjectGetAttributesNV\0" // IR(33154, 25)
  "HitObjectGetHitKindNV\0" // IR(33179, 22)
  "HitObjectGetPrimitiveIndexNV\0" // IR(33201, 29)
  "HitObjectGetGeometryIndexNV\0" // IR(33230, 28)
  "HitObjectGetInstanceIdNV\0" // IR(33258, 25)
  "HitObjectGetInstanceCustomIndexNV\0" // IR(33283, 34)
  "HitObjectGetWorldRayDirectionNV\0" // IR(33317, 32)
  "HitObjectGetWorldRayOriginNV\0" // IR(33349, 29)
  "HitObjectGetRayTMaxNV\0" // IR(33378, 22)
  "HitObjectGetRayTMinNV\0" // IR(33400, 22)
  "HitObjectIsEmptyNV\0" // IR(33422, 19)
  "HitObjectIsHitNV\0" // IR(33441, 17)
  "HitObjectIsMissNV\0" // IR(33458, 18)
  "ReorderThreadWithHitObjectNV\0" // IR(33476, 29)
  "ReorderThreadWithHintNV\0" // IR(33505, 24)
  "TypeHitObjectNV\0" // IR(33529, 16)
  "ImageSampleFootprintNV\0" // IR(33545, 23)
  "TypeCooperativeVectorNV\0" // IR(33568, 24)
  "CooperativeVectorMatrixMulNV\0" // IR(33592, 29)
  "CooperativeVectorOuterProductAccumulateNV\0" // IR(33621, 42)
  "CooperativeVectorReduceSumAccumulateNV\0" // IR(33663, 39)
  "CooperativeVectorMatrixMulAddNV\0" // IR(33702, 32)
  "CooperativeMatrixConvertNV\0" // IR(33734, 27)
  "EmitMeshTasksEXT\0" // IR(33761, 17)
  "SetMeshOutputsEXT\0" // IR(33778, 18)
  "GroupNonUniformPartitionNV\0" // IR(33796, 27)
  "WritePackedPrimitiveIndices4x8NV\0" // IR(33823, 33)
  "FetchMicroTriangleVertexPositionNV\0" // IR(33856, 35)
  "FetchMicroTriangleVertexBarycentricNV\0" // IR(33891, 38)
  "CooperativeVectorLoadNV\0" // IR(33929, 24)
  "CooperativeVectorStoreNV\0" // IR(33953, 25)
  "ReportIntersectionKHR\0" // IR(33978, 22)
  "ReportIntersectionNV\0" // IR(34000, 21)
  "IgnoreIntersectionNV\0" // IR(34021, 21)
  "TerminateRayNV\0" // IR(34042, 15)
  "TraceNV\0" // IR(34057, 8)
  "TraceMotionNV\0" // IR(34065, 14)
  "TraceRayMotionNV\0" // IR(34079, 17)
  "RayQueryGetIntersectionTriangleVertexPositionsKHR\0" // IR(34096, 50)
  "TypeAccelerationStructureKHR\0" // IR(34146, 29)
  "TypeAccelerationStructureNV\0" // IR(34175, 28)
  "ExecuteCallableNV\0" // IR(34203, 18)
  "RayQueryGetClusterIdNV\0" // IR(34221, 23)
  "HitObjectGetClusterIdNV\0" // IR(34244, 24)
  "TypeCooperativeMatrixNV\0" // IR(34268, 24)
  "CooperativeMatrixLoadNV\0" // IR(34292, 24)
  "CooperativeMatrixStoreNV\0" // IR(34316, 25)
  "CooperativeMatrixMulAddNV\0" // IR(34341, 26)
  "CooperativeMatrixLengthNV\0" // IR(34367, 26)
  "BeginInvocationInterlockEXT\0" // IR(34393, 28)
  "EndInvocationInterlockEXT\0" // IR(34421, 26)
  "SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE\0" // IR(34447, 43)
  "CooperativeMatrixReduceNV\0" // IR(34490, 26)
  "SPV_OPERAND_TYPE_MEMORY_ACCESS\0" // IR(34516, 31)
  "SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS\0" // IR(34547, 44)
  "CooperativeMatrixLoadTensorNV\0" // IR(34591, 30)
  "CooperativeMatrixStoreTensorNV\0" // IR(34621, 31)
  "CooperativeMatrixPerElementOpNV\0" // IR(34652, 32)
  "TypeTensorLayoutNV\0" // IR(34684, 19)
  "TypeTensorViewNV\0" // IR(34703, 17)
  "CreateTensorLayoutNV\0" // IR(34720, 21)
  "TensorLayoutSetDimensionNV\0" // IR(34741, 27)
  "TensorLayoutSetStrideNV\0" // IR(34768, 24)
  "TensorLayoutSliceNV\0" // IR(34792, 20)
  "TensorLayoutSetClampValueNV\0" // IR(34812, 28)
  "CreateTensorViewNV\0" // IR(34840, 19)
  "TensorViewSetDimensionNV\0" // IR(34859, 25)
  "TensorViewSetStrideNV\0" // IR(34884, 22)
  "IsHelperInvocationEXT\0" // IR(34906, 22)
  "TensorViewSetClipNV\0" // IR(34928, 20)
  "TensorLayoutSetBlockSizeNV\0" // IR(34948, 27)
  "CooperativeMatrixTransposeNV\0" // IR(34975, 29)
  "ConvertUToImageNV\0" // IR(35004, 18)
  "ConvertUToSamplerNV\0" // IR(35022, 20)
  "ConvertImageToUNV\0" // IR(35042, 18)
  "ConvertSamplerToUNV\0" // IR(35060, 20)
  "ConvertUToSampledImageNV\0" // IR(35080, 25)
  "ConvertSampledImageToUNV\0" // IR(35105, 25)
  "SamplerImageAddressingModeNV\0" // IR(35130, 29)
  "SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS\0" // IR(35159, 52)
  "RawAccessChainNV\0" // IR(35211, 17)
  "RayQueryGetIntersectionSpherePositionNV\0" // IR(35228, 40)
  "RayQueryGetIntersectionSphereRadiusNV\0" // IR(35268, 38)
  "RayQueryGetIntersectionLSSPositionsNV\0" // IR(35306, 38)
  "RayQueryGetIntersectionLSSRadiiNV\0" // IR(35344, 34)
  "RayQueryGetIntersectionLSSHitValueNV\0" // IR(35378, 37)
  "HitObjectGetSpherePositionNV\0" // IR(35415, 29)
  "HitObjectGetSphereRadiusNV\0" // IR(35444, 27)
  "HitObjectGetLSSPositionsNV\0" // IR(35471, 27)
  "HitObjectGetLSSRadiiNV\0" // IR(35498, 23)
  "HitObjectIsSphereHitNV\0" // IR(35521, 23)
  "HitObjectIsLSSHitNV\0" // IR(35544, 20)
  "RayQueryIsSphereHitNV\0" // IR(35564, 22)
  "RayQueryIsLSSHitNV\0" // IR(35586, 19)
  "SubgroupShuffleDownINTEL\0" // IR(35605, 25)
  "SubgroupShuffleUpINTEL\0" // IR(35630, 23)
  "SubgroupShuffleXorINTEL\0" // IR(35653, 24)
  "SubgroupBlockReadINTEL\0" // IR(35677, 23)
  "SubgroupBlockWriteINTEL\0" // IR(35700, 24)
  "SubgroupImageBlockReadINTEL\0" // IR(35724, 28)
  "SubgroupImageBlockWriteINTEL\0" // IR(35752, 29)
  "SubgroupImageMediaBlockReadINTEL\0" // IR(35781, 33)
  "SubgroupImageMediaBlockWriteINTEL\0" // IR(35814, 34)
  "UCountLeadingZerosINTEL\0" // IR(35848, 24)
  "UCountTrailingZerosINTEL\0" // IR(35872, 25)
  "AbsISubINTEL\0" // IR(35897, 13)
  "AbsUSubINTEL\0" // IR(35910, 13)
  "IAddSatINTEL\0" // IR(35923, 13)
  "UAddSatINTEL\0" // IR(35936, 13)
  "IAverageINTEL\0" // IR(35949, 14)
  "UAverageINTEL\0" // IR(35963, 14)
  "IAverageRoundedINTEL\0" // IR(35977, 21)
  "UAverageRoundedINTEL\0" // IR(35998, 21)
  "ISubSatINTEL\0" // IR(36019, 13)
  "USubSatINTEL\0" // IR(36032, 13)
  "IMul32x16INTEL\0" // IR(36045, 15)
  "UMul32x16INTEL\0" // IR(36060, 15)
  "ConstantFunctionPointerINTEL\0" // IR(36075, 29)
  "FunctionPointerCallINTEL\0" // IR(36104, 25)
  "AsmTargetINTEL\0" // IR(36129, 15)
  "AsmCallINTEL\0" // IR(36144, 13)
  "AtomicFMinEXT\0" // IR(36157, 14)
  "AtomicFMaxEXT\0" // IR(36171, 14)
  "AssumeTrueKHR\0" // IR(36185, 14)
  "ExpectKHR\0" // IR(36199, 10)
  "DecorateString\0" // IR(36209, 15)
  "DecorateStringGOOGLE\0" // IR(36224, 21)
  "MemberDecorateString\0" // IR(36245, 21)
  "MemberDecorateStringGOOGLE\0" // IR(36266, 27)
  "VmeImageINTEL\0" // IR(36293, 14)
  "TypeVmeImageINTEL\0" // IR(36307, 18)
  "TypeAvcImePayloadINTEL\0" // IR(36325, 23)
  "TypeAvcRefPayloadINTEL\0" // IR(36348, 23)
  "TypeAvcSicPayloadINTEL\0" // IR(36371, 23)
  "TypeAvcMcePayloadINTEL\0" // IR(36394, 23)
  "TypeAvcMceResultINTEL\0" // IR(36417, 22)
  "TypeAvcImeResultINTEL\0" // IR(36439, 22)
  "TypeAvcImeResultSingleReferenceStreamoutINTEL\0" // IR(36461, 46)
  "TypeAvcImeResultDualReferenceStreamoutINTEL\0" // IR(36507, 44)
  "TypeAvcImeSingleReferenceStreaminINTEL\0" // IR(36551, 39)
  "TypeAvcImeDualReferenceStreaminINTEL\0" // IR(36590, 37)
  "TypeAvcRefResultINTEL\0" // IR(36627, 22)
  "TypeAvcSicResultINTEL\0" // IR(36649, 22)
  "SubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL\0" // IR(36671, 60)
  "SubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL\0" // IR(36731, 53)
  "SubgroupAvcMceGetDefaultInterShapePenaltyINTEL\0" // IR(36784, 47)
  "SubgroupAvcMceSetInterShapePenaltyINTEL\0" // IR(36831, 40)
  "SubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL\0" // IR(36871, 51)
  "SubgroupAvcMceSetInterDirectionPenaltyINTEL\0" // IR(36922, 44)
  "SubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL\0" // IR(36966, 51)
  "SubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL\0" // IR(37017, 56)
  "SubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL\0" // IR(37073, 50)
  "SubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL\0" // IR(37123, 52)
  "SubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL\0" // IR(37175, 49)
  "SubgroupAvcMceSetMotionVectorCostFunctionINTEL\0" // IR(37224, 47)
  "SubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL\0" // IR(37271, 50)
  "SubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL\0" // IR(37321, 51)
  "SubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL\0" // IR(37372, 56)
  "SubgroupAvcMceSetAcOnlyHaarINTEL\0" // IR(37428, 33)
  "SubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL\0" // IR(37461, 52)
  "SubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL\0" // IR(37513, 61)
  "SubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL\0" // IR(37574, 61)
  "SubgroupAvcMceConvertToImePayloadINTEL\0" // IR(37635, 39)
  "SubgroupAvcMceConvertToImeResultINTEL\0" // IR(37674, 38)
  "SubgroupAvcMceConvertToRefPayloadINTEL\0" // IR(37712, 39)
  "SubgroupAvcMceConvertToRefResultINTEL\0" // IR(37751, 38)
  "SubgroupAvcMceConvertToSicPayloadINTEL\0" // IR(37789, 39)
  "SubgroupAvcMceConvertToSicResultINTEL\0" // IR(37828, 38)
  "SubgroupAvcMceGetMotionVectorsINTEL\0" // IR(37866, 36)
  "SubgroupAvcMceGetInterDistortionsINTEL\0" // IR(37902, 39)
  "SubgroupAvcMceGetBestInterDistortionsINTEL\0" // IR(37941, 43)
  "SubgroupAvcMceGetInterMajorShapeINTEL\0" // IR(37984, 38)
  "SubgroupAvcMceGetInterMinorShapeINTEL\0" // IR(38022, 38)
  "SubgroupAvcMceGetInterDirectionsINTEL\0" // IR(38060, 38)
  "SubgroupAvcMceGetInterMotionVectorCountINTEL\0" // IR(38098, 45)
  "SubgroupAvcMceGetInterReferenceIdsINTEL\0" // IR(38143, 40)
  "SubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL\0" // IR(38183, 62)
  "SubgroupAvcImeInitializeINTEL\0" // IR(38245, 30)
  "SubgroupAvcImeSetSingleReferenceINTEL\0" // IR(38275, 38)
  "SubgroupAvcImeSetDualReferenceINTEL\0" // IR(38313, 36)
  "SubgroupAvcImeRefWindowSizeINTEL\0" // IR(38349, 33)
  "SubgroupAvcImeAdjustRefOffsetINTEL\0" // IR(38382, 35)
  "SubgroupAvcImeConvertToMcePayloadINTEL\0" // IR(38417, 39)
  "SubgroupAvcImeSetMaxMotionVectorCountINTEL\0" // IR(38456, 43)
  "SubgroupAvcImeSetUnidirectionalMixDisableINTEL\0" // IR(38499, 47)
  "SubgroupAvcImeSetEarlySearchTerminationThresholdINTEL\0" // IR(38546, 54)
  "SubgroupAvcImeSetWeightedSadINTEL\0" // IR(38600, 34)
  "SubgroupAvcImeEvaluateWithSingleReferenceINTEL\0" // IR(38634, 47)
  "SubgroupAvcImeEvaluateWithDualReferenceINTEL\0" // IR(38681, 45)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL\0" // IR(38726, 55)
  "SubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL\0" // IR(38781, 53)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL\0" // IR(38834, 56)
  "SubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL\0" // IR(38890, 54)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL\0" // IR(38944, 58)
  "SubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL\0" // IR(39002, 56)
  "SubgroupAvcImeConvertToMceResultINTEL\0" // IR(39058, 38)
  "SubgroupAvcImeGetSingleReferenceStreaminINTEL\0" // IR(39096, 46)
  "SubgroupAvcImeGetDualReferenceStreaminINTEL\0" // IR(39142, 44)
  "SubgroupAvcImeStripSingleReferenceStreamoutINTEL\0" // IR(39186, 49)
  "SubgroupAvcImeStripDualReferenceStreamoutINTEL\0" // IR(39235, 47)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL\0" // IR(39282, 70)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL\0" // IR(39352, 68)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL\0" // IR(39420, 69)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL\0" // IR(39489, 68)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL\0" // IR(39557, 66)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL\0" // IR(39623, 67)
  "SubgroupAvcImeGetBorderReachedINTEL\0" // IR(39690, 36)
  "SubgroupAvcImeGetTruncatedSearchIndicationINTEL\0" // IR(39726, 48)
  "SubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL\0" // IR(39774, 59)
  "SubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL\0" // IR(39833, 58)
  "SubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL\0" // IR(39891, 56)
  "SubgroupAvcFmeInitializeINTEL\0" // IR(39947, 30)
  "SubgroupAvcBmeInitializeINTEL\0" // IR(39977, 30)
  "SubgroupAvcRefConvertToMcePayloadINTEL\0" // IR(40007, 39)
  "SubgroupAvcRefSetBidirectionalMixDisableINTEL\0" // IR(40046, 46)
  "SubgroupAvcRefSetBilinearFilterEnableINTEL\0" // IR(40092, 43)
  "SubgroupAvcRefEvaluateWithSingleReferenceINTEL\0" // IR(40135, 47)
  "SubgroupAvcRefEvaluateWithDualReferenceINTEL\0" // IR(40182, 45)
  "SubgroupAvcRefEvaluateWithMultiReferenceINTEL\0" // IR(40227, 46)
  "SubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL\0" // IR(40273, 56)
  "SubgroupAvcRefConvertToMceResultINTEL\0" // IR(40329, 38)
  "SubgroupAvcSicInitializeINTEL\0" // IR(40367, 30)
  "SubgroupAvcSicConfigureSkcINTEL\0" // IR(40397, 32)
  "SubgroupAvcSicConfigureIpeLumaINTEL\0" // IR(40429, 36)
  "SubgroupAvcSicConfigureIpeLumaChromaINTEL\0" // IR(40465, 42)
  "SubgroupAvcSicGetMotionVectorMaskINTEL\0" // IR(40507, 39)
  "SubgroupAvcSicConvertToMcePayloadINTEL\0" // IR(40546, 39)
  "SubgroupAvcSicSetIntraLumaShapePenaltyINTEL\0" // IR(40585, 44)
  "SubgroupAvcSicSetIntraLumaModeCostFunctionINTEL\0" // IR(40629, 48)
  "SubgroupAvcSicSetIntraChromaModeCostFunctionINTEL\0" // IR(40677, 50)
  "SubgroupAvcSicSetBilinearFilterEnableINTEL\0" // IR(40727, 43)
  "SubgroupAvcSicSetSkcForwardTransformEnableINTEL\0" // IR(40770, 48)
  "SubgroupAvcSicSetBlockBasedRawSkipSadINTEL\0" // IR(40818, 43)
  "SubgroupAvcSicEvaluateIpeINTEL\0" // IR(40861, 31)
  "SubgroupAvcSicEvaluateWithSingleReferenceINTEL\0" // IR(40892, 47)
  "SubgroupAvcSicEvaluateWithDualReferenceINTEL\0" // IR(40939, 45)
  "SubgroupAvcSicEvaluateWithMultiReferenceINTEL\0" // IR(40984, 46)
  "SubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL\0" // IR(41030, 56)
  "SubgroupAvcSicConvertToMceResultINTEL\0" // IR(41086, 38)
  "SubgroupAvcSicGetIpeLumaShapeINTEL\0" // IR(41124, 35)
  "SubgroupAvcSicGetBestIpeLumaDistortionINTEL\0" // IR(41159, 44)
  "SubgroupAvcSicGetBestIpeChromaDistortionINTEL\0" // IR(41203, 46)
  "SubgroupAvcSicGetPackedIpeLumaModesINTEL\0" // IR(41249, 41)
  "SubgroupAvcSicGetIpeChromaModeINTEL\0" // IR(41290, 36)
  "SubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL\0" // IR(41326, 50)
  "SubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL\0" // IR(41376, 48)
  "SubgroupAvcSicGetInterRawSadsINTEL\0" // IR(41424, 35)
  "SaveMemoryINTEL\0" // IR(41459, 16)
  "RestoreMemoryINTEL\0" // IR(41475, 19)
  "ArbitraryFloatSinCosPiINTEL\0" // IR(41494, 28)
  "ArbitraryFloatCastINTEL\0" // IR(41522, 24)
  "ArbitraryFloatCastFromIntINTEL\0" // IR(41546, 31)
  "ArbitraryFloatCastToIntINTEL\0" // IR(41577, 29)
  "ArbitraryFloatAddINTEL\0" // IR(41606, 23)
  "ArbitraryFloatSubINTEL\0" // IR(41629, 23)
  "ArbitraryFloatMulINTEL\0" // IR(41652, 23)
  "ArbitraryFloatDivINTEL\0" // IR(41675, 23)
  "ArbitraryFloatGTINTEL\0" // IR(41698, 22)
  "ArbitraryFloatGEINTEL\0" // IR(41720, 22)
  "ArbitraryFloatLTINTEL\0" // IR(41742, 22)
  "ArbitraryFloatLEINTEL\0" // IR(41764, 22)
  "ArbitraryFloatEQINTEL\0" // IR(41786, 22)
  "ArbitraryFloatRecipINTEL\0" // IR(41808, 25)
  "ArbitraryFloatRSqrtINTEL\0" // IR(41833, 25)
  "ArbitraryFloatCbrtINTEL\0" // IR(41858, 24)
  "ArbitraryFloatHypotINTEL\0" // IR(41882, 25)
  "ArbitraryFloatSqrtINTEL\0" // IR(41907, 24)
  "ArbitraryFloatLogINTEL\0" // IR(41931, 23)
  "ArbitraryFloatLog2INTEL\0" // IR(41954, 24)
  "ArbitraryFloatLog10INTEL\0" // IR(41978, 25)
  "ArbitraryFloatLog1pINTEL\0" // IR(42003, 25)
  "ArbitraryFloatExpINTEL\0" // IR(42028, 23)
  "ArbitraryFloatExp2INTEL\0" // IR(42051, 24)
  "ArbitraryFloatExp10INTEL\0" // IR(42075, 25)
  "ArbitraryFloatExpm1INTEL\0" // IR(42100, 25)
  "ArbitraryFloatSinINTEL\0" // IR(42125, 23)
  "ArbitraryFloatCosINTEL\0" // IR(42148, 23)
  "ArbitraryFloatSinCosINTEL\0" // IR(42171, 26)
  "ArbitraryFloatSinPiINTEL\0" // IR(42197, 25)
  "ArbitraryFloatCosPiINTEL\0" // IR(42222, 25)
  "ArbitraryFloatASinINTEL\0" // IR(42247, 24)
  "ArbitraryFloatASinPiINTEL\0" // IR(42271, 26)
  "ArbitraryFloatACosINTEL\0" // IR(42297, 24)
  "ArbitraryFloatACosPiINTEL\0" // IR(42321, 26)
  "ArbitraryFloatATanINTEL\0" // IR(42347, 24)
  "ArbitraryFloatATanPiINTEL\0" // IR(42371, 26)
  "ArbitraryFloatATan2INTEL\0" // IR(42397, 25)
  "ArbitraryFloatPowINTEL\0" // IR(42422, 23)
  "ArbitraryFloatPowRINTEL\0" // IR(42445, 24)
  "ArbitraryFloatPowNINTEL\0" // IR(42469, 24)
  "LoopControlINTEL\0" // IR(42493, 17)
  "AliasDomainDeclINTEL\0" // IR(42510, 21)
  "AliasScopeDeclINTEL\0" // IR(42531, 20)
  "AliasScopeListDeclINTEL\0" // IR(42551, 24)
  "FixedSqrtINTEL\0" // IR(42575, 15)
  "FixedRecipINTEL\0" // IR(42590, 16)
  "FixedRsqrtINTEL\0" // IR(42606, 16)
  "FixedSinINTEL\0" // IR(42622, 14)
  "FixedCosINTEL\0" // IR(42636, 14)
  "FixedSinCosINTEL\0" // IR(42650, 17)
  "FixedSinPiINTEL\0" // IR(42667, 16)
  "FixedCosPiINTEL\0" // IR(42683, 16)
  "FixedSinCosPiINTEL\0" // IR(42699, 19)
  "FixedLogINTEL\0" // IR(42718, 14)
  "FixedExpINTEL\0" // IR(42732, 14)
  "PtrCastToCrossWorkgroupINTEL\0" // IR(42746, 29)
  "CrossWorkgroupCastToPtrINTEL\0" // IR(42775, 29)
  "ReadPipeBlockingINTEL\0" // IR(42804, 22)
  "WritePipeBlockingINTEL\0" // IR(42826, 23)
  "RayQueryGetRayTMinKHR\0" // IR(42849, 22)
  "RayQueryGetRayFlagsKHR\0" // IR(42871, 23)
  "RayQueryGetIntersectionTKHR\0" // IR(42894, 28)
  "RayQueryGetIntersectionInstanceCustomIndexKHR\0" // IR(42922, 46)
  "RayQueryGetIntersectionInstanceIdKHR\0" // IR(42968, 37)
  "RayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR\0" // IR(43005, 65)
  "RayQueryGetIntersectionGeometryIndexKHR\0" // IR(43070, 40)
  "RayQueryGetIntersectionPrimitiveIndexKHR\0" // IR(43110, 41)
  "RayQueryGetIntersectionBarycentricsKHR\0" // IR(43151, 39)
  "RayQueryGetIntersectionFrontFaceKHR\0" // IR(43190, 36)
  "RayQueryGetIntersectionCandidateAABBOpaqueKHR\0" // IR(43226, 46)
  "RayQueryGetIntersectionObjectRayDirectionKHR\0" // IR(43272, 45)
  "RayQueryGetIntersectionObjectRayOriginKHR\0" // IR(43317, 42)
  "RayQueryGetWorldRayDirectionKHR\0" // IR(43359, 32)
  "RayQueryGetWorldRayOriginKHR\0" // IR(43391, 29)
  "RayQueryGetIntersectionObjectToWorldKHR\0" // IR(43420, 40)
  "RayQueryGetIntersectionWorldToObjectKHR\0" // IR(43460, 40)
  "AtomicFAddEXT\0" // IR(43500, 14)
  "TypeBufferSurfaceINTEL\0" // IR(43514, 23)
  "TypeStructContinuedINTEL\0" // IR(43537, 25)
  "ConstantCompositeContinuedINTEL\0" // IR(43562, 32)
  "SpecConstantCompositeContinuedINTEL\0" // IR(43594, 36)
  "CompositeConstructContinuedINTEL\0" // IR(43630, 33)
  "ConvertFToBF16INTEL\0" // IR(43663, 20)
  "ConvertBF16ToFINTEL\0" // IR(43683, 20)
  "ControlBarrierArriveINTEL\0" // IR(43703, 26)
  "ControlBarrierWaitINTEL\0" // IR(43729, 24)
  "TaskSequenceCreateINTEL\0" // IR(43753, 24)
  "TaskSequenceAsyncINTEL\0" // IR(43777, 23)
  "TaskSequenceGetINTEL\0" // IR(43800, 21)
  "TaskSequenceReleaseINTEL\0" // IR(43821, 25)
  "TypeTaskSequenceINTEL\0" // IR(43846, 22)
  "SubgroupBlockPrefetchINTEL\0" // IR(43868, 27)
  "Subgroup2DBlockLoadINTEL\0" // IR(43895, 25)
  "Subgroup2DBlockLoadTransformINTEL\0" // IR(43920, 34)
  "Subgroup2DBlockLoadTransposeINTEL\0" // IR(43954, 34)
  "Subgroup2DBlockPrefetchINTEL\0" // IR(43988, 29)
  "Subgroup2DBlockStoreINTEL\0" // IR(44017, 26)
  "SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS\0" // IR(44043, 62)
  "BitwiseFunctionINTEL\0" // IR(44105, 21)
  "GroupIMulKHR\0" // IR(44126, 13)
  "GroupFMulKHR\0" // IR(44139, 13)
  "GroupBitwiseAndKHR\0" // IR(44152, 19)
  "GroupBitwiseOrKHR\0" // IR(44171, 18)
  "GroupBitwiseXorKHR\0" // IR(44189, 19)
  "GroupLogicalAndKHR\0" // IR(44208, 19)
  "GroupLogicalOrKHR\0" // IR(44227, 18)
  "GroupLogicalXorKHR\0" // IR(44245, 19)
  "RoundFToTF32INTEL\0" // IR(44264, 18)
  "MaskedGatherINTEL\0" // IR(44282, 18)
  "MaskedScatterINTEL\0" // IR(44300, 19)
  "DebugInfoNone\0" // IR(44319, 14)
  "DebugCompilationUnit\0" // IR(44333, 21)
  "SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING\0" // IR(44354, 52)
  "DebugTypeBasic\0" // IR(44406, 15)
  "SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS\0" // IR(44421, 34)
  "DebugTypePointer\0" // IR(44455, 17)
  "SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER\0" // IR(44472, 38)
  "DebugTypeQualifier\0" // IR(44510, 19)
  "DebugTypeArray\0" // IR(44529, 15)
  "DebugTypeVector\0" // IR(44544, 16)
  "DebugTypedef\0" // IR(44560, 13)
  "DebugTypeFunction\0" // IR(44573, 18)
  "DebugTypeEnum\0" // IR(44591, 14)
  "SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE\0" // IR(44605, 38)
  "DebugTypeComposite\0" // IR(44643, 19)
  "DebugTypeMember\0" // IR(44662, 16)
  "DebugTypeInheritance\0" // IR(44678, 21)
  "DebugTypePtrToMember\0" // IR(44699, 21)
  "DebugTypeTemplate\0" // IR(44720, 18)
  "DebugTypeTemplateParameter\0" // IR(44738, 27)
  "DebugTypeTemplateTemplateParameter\0" // IR(44765, 35)
  "DebugTypeTemplateParameterPack\0" // IR(44800, 31)
  "DebugGlobalVariable\0" // IR(44831, 20)
  "DebugFunctionDeclaration\0" // IR(44851, 25)
  "DebugFunction\0" // IR(44876, 14)
  "DebugLexicalBlock\0" // IR(44890, 18)
  "DebugLexicalBlockDiscriminator\0" // IR(44908, 31)
  "DebugScope\0" // IR(44939, 11)
  "DebugNoScope\0" // IR(44950, 13)
  "DebugInlinedAt\0" // IR(44963, 15)
  "SPV_OPERAND_TYPE_OPTIONAL_LITERAL_INTEGER\0" // IR(44978, 42)
  "DebugLocalVariable\0" // IR(45020, 19)
  "DebugInlinedVariable\0" // IR(45039, 21)
  "DebugDeclare\0" // IR(45060, 13)
  "DebugValue\0" // IR(45073, 11)
  "SPV_OPERAND_TYPE_DEBUG_OPERATION\0" // IR(45084, 33)
  "DebugOperation\0" // IR(45117, 15)
  "DebugExpression\0" // IR(45132, 16)
  "DebugMacroDef\0" // IR(45148, 14)
  "DebugMacroUndef\0" // IR(45162, 16)
  "Round\0" // IR(45178, 6)
  "RoundEven\0" // IR(45184, 10)
  "Trunc\0" // IR(45194, 6)
  "FAbs\0" // IR(45200, 5)
  "SAbs\0" // IR(45205, 5)
  "FSign\0" // IR(45210, 6)
  "SSign\0" // IR(45216, 6)
  "Floor\0" // IR(45222, 6)
  "Ceil\0" // IR(45228, 5)
  "Fract\0" // IR(45233, 6)
  "Radians\0" // IR(45239, 8)
  "Degrees\0" // IR(45247, 8)
  "Sin\0" // IR(45255, 4)
  "Cos\0" // IR(45259, 4)
  "Tan\0" // IR(45263, 4)
  "Asin\0" // IR(45267, 5)
  "Acos\0" // IR(45272, 5)
  "Atan\0" // IR(45277, 5)
  "Sinh\0" // IR(45282, 5)
  "Cosh\0" // IR(45287, 5)
  "Tanh\0" // IR(45292, 5)
  "Asinh\0" // IR(45297, 6)
  "Acosh\0" // IR(45303, 6)
  "Atanh\0" // IR(45309, 6)
  "Atan2\0" // IR(45315, 6)
  "Pow\0" // IR(45321, 4)
  "Exp\0" // IR(45325, 4)
  "Log\0" // IR(45329, 4)
  "Exp2\0" // IR(45333, 5)
  "Log2\0" // IR(45338, 5)
  "Sqrt\0" // IR(45343, 5)
  "InverseSqrt\0" // IR(45348, 12)
  "Determinant\0" // IR(45360, 12)
  "MatrixInverse\0" // IR(45372, 14)
  "Modf\0" // IR(45386, 5)
  "ModfStruct\0" // IR(45391, 11)
  "FMin\0" // IR(45402, 5)
  "UMin\0" // IR(45407, 5)
  "SMin\0" // IR(45412, 5)
  "FMax\0" // IR(45417, 5)
  "UMax\0" // IR(45422, 5)
  "SMax\0" // IR(45427, 5)
  "FClamp\0" // IR(45432, 7)
  "UClamp\0" // IR(45439, 7)
  "SClamp\0" // IR(45446, 7)
  "FMix\0" // IR(45453, 5)
  "IMix\0" // IR(45458, 5)
  "Step\0" // IR(45463, 5)
  "SmoothStep\0" // IR(45468, 11)
  "Fma\0" // IR(45479, 4)
  "Frexp\0" // IR(45483, 6)
  "FrexpStruct\0" // IR(45489, 12)
  "Ldexp\0" // IR(45501, 6)
  "PackSnorm4x8\0" // IR(45507, 13)
  "PackUnorm4x8\0" // IR(45520, 13)
  "PackSnorm2x16\0" // IR(45533, 14)
  "PackUnorm2x16\0" // IR(45547, 14)
  "PackHalf2x16\0" // IR(45561, 13)
  "PackDouble2x32\0" // IR(45574, 15)
  "UnpackSnorm2x16\0" // IR(45589, 16)
  "UnpackUnorm2x16\0" // IR(45605, 16)
  "UnpackHalf2x16\0" // IR(45621, 15)
  "UnpackSnorm4x8\0" // IR(45636, 15)
  "UnpackUnorm4x8\0" // IR(45651, 15)
  "UnpackDouble2x32\0" // IR(45666, 17)
  "Length\0" // IR(45683, 7)
  "Distance\0" // IR(45690, 9)
  "Cross\0" // IR(45699, 6)
  "Normalize\0" // IR(45705, 10)
  "FaceForward\0" // IR(45715, 12)
  "Reflect\0" // IR(45727, 8)
  "Refract\0" // IR(45735, 8)
  "FindILsb\0" // IR(45743, 9)
  "FindSMsb\0" // IR(45752, 9)
  "FindUMsb\0" // IR(45761, 9)
  "InterpolateAtCentroid\0" // IR(45770, 22)
  "InterpolateAtSample\0" // IR(45792, 20)
  "InterpolateAtOffset\0" // IR(45812, 20)
  "NMin\0" // IR(45832, 5)
  "NMax\0" // IR(45837, 5)
  "NClamp\0" // IR(45842, 7)
  "ArgumentInfo\0" // IR(45849, 13)
  "ArgumentStorageBuffer\0" // IR(45862, 22)
  "ArgumentUniform\0" // IR(45884, 16)
  "ArgumentPodStorageBuffer\0" // IR(45900, 25)
  "ArgumentPodUniform\0" // IR(45925, 19)
  "ArgumentPodPushConstant\0" // IR(45944, 24)
  "ArgumentSampledImage\0" // IR(45968, 21)
  "ArgumentStorageImage\0" // IR(45989, 21)
  "ArgumentSampler\0" // IR(46010, 16)
  "ArgumentWorkgroup\0" // IR(46026, 18)
  "SpecConstantWorkgroupSize\0" // IR(46044, 26)
  "SpecConstantGlobalOffset\0" // IR(46070, 25)
  "SpecConstantWorkDim\0" // IR(46095, 20)
  "PushConstantGlobalOffset\0" // IR(46115, 25)
  "PushConstantEnqueuedLocalSize\0" // IR(46140, 30)
  "PushConstantGlobalSize\0" // IR(46170, 23)
  "PushConstantRegionOffset\0" // IR(46193, 25)
  "PushConstantNumWorkgroups\0" // IR(46218, 26)
  "PushConstantRegionGroupOffset\0" // IR(46244, 30)
  "ConstantDataStorageBuffer\0" // IR(46274, 26)
  "ConstantDataUniform\0" // IR(46300, 20)
  "PropertyRequiredWorkgroupSize\0" // IR(46320, 30)
  "SpecConstantSubgroupMaxSize\0" // IR(46350, 28)
  "ArgumentPointerPushConstant\0" // IR(46378, 28)
  "ArgumentPointerUniform\0" // IR(46406, 23)
  "ProgramScopeVariablesStorageBuffer\0" // IR(46429, 35)
  "ProgramScopeVariablePointerRelocation\0" // IR(46464, 38)
  "ImageArgumentInfoChannelOrderPushConstant\0" // IR(46502, 42)
  "ImageArgumentInfoChannelDataTypePushConstant\0" // IR(46544, 45)
  "ImageArgumentInfoChannelOrderUniform\0" // IR(46589, 37)
  "ImageArgumentInfoChannelDataTypeUniform\0" // IR(46626, 40)
  "ArgumentStorageTexelBuffer\0" // IR(46666, 27)
  "ArgumentUniformTexelBuffer\0" // IR(46693, 27)
  "ConstantDataPointerPushConstant\0" // IR(46720, 32)
  "ProgramScopeVariablePointerPushConstant\0" // IR(46752, 40)
  "PrintfInfo\0" // IR(46792, 11)
  "PrintfBufferStorageBuffer\0" // IR(46803, 26)
  "PrintfBufferPointerPushConstant\0" // IR(46829, 32)
  "NormalizedSamplerMaskPushConstant\0" // IR(46861, 34)
  "WorkgroupVariableSize\0" // IR(46895, 22)
  "DebugImportedEntity\0" // IR(46917, 20)
  "DebugSource\0" // IR(46937, 12)
  "DebugFunctionDefinition\0" // IR(46949, 24)
  "DebugSourceContinued\0" // IR(46973, 21)
  "DebugLine\0" // IR(46994, 10)
  "DebugNoLine\0" // IR(47004, 12)
  "DebugBuildIdentifier\0" // IR(47016, 21)
  "DebugStoragePath\0" // IR(47037, 17)
  "DebugEntryPoint\0" // IR(47054, 16)
  "DebugTypeMatrix\0" // IR(47070, 16)
  "Configuration\0" // IR(47086, 14)
  "StartCounter\0" // IR(47100, 13)
  "StopCounter\0" // IR(47113, 12)
  "PushConstants\0" // IR(47125, 14)
  "SpecializationMapEntry\0" // IR(47139, 23)
  "DescriptorSetBuffer\0" // IR(47162, 20)
  "DescriptorSetImage\0" // IR(47182, 19)
  "DescriptorSetSampler\0" // IR(47201, 21)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING\0" // IR(47222, 63)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS\0" // IR(47285, 45)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER\0" // IR(47330, 49)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE\0" // IR(47379, 49)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION\0" // IR(47428, 44)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY\0" // IR(47472, 50)
  "DebugModuleINTEL\0" // IR(47522, 17)
  "acos\0" // IR(47539, 5)
  "acosh\0" // IR(47544, 6)
  "acospi\0" // IR(47550, 7)
  "asin\0" // IR(47557, 5)
  "asinh\0" // IR(47562, 6)
  "asinpi\0" // IR(47568, 7)
  "atan\0" // IR(47575, 5)
  "atan2\0" // IR(47580, 6)
  "atanh\0" // IR(47586, 6)
  "atanpi\0" // IR(47592, 7)
  "atan2pi\0" // IR(47599, 8)
  "cbrt\0" // IR(47607, 5)
  "ceil\0" // IR(47612, 5)
  "copysign\0" // IR(47617, 9)
  "cos\0" // IR(47626, 4)
  "cosh\0" // IR(47630, 5)
  "cospi\0" // IR(47635, 6)
  "erfc\0" // IR(47641, 5)
  "erf\0" // IR(47646, 4)
  "exp\0" // IR(47650, 4)
  "exp2\0" // IR(47654, 5)
  "exp10\0" // IR(47659, 6)
  "expm1\0" // IR(47665, 6)
  "fabs\0" // IR(47671, 5)
  "fdim\0" // IR(47676, 5)
  "floor\0" // IR(47681, 6)
  "fma\0" // IR(47687, 4)
  "fmax\0" // IR(47691, 5)
  "fmin\0" // IR(47696, 5)
  "fmod\0" // IR(47701, 5)
  "fract\0" // IR(47706, 6)
  "frexp\0" // IR(47712, 6)
  "hypot\0" // IR(47718, 6)
  "ilogb\0" // IR(47724, 6)
  "ldexp\0" // IR(47730, 6)
  "lgamma\0" // IR(47736, 7)
  "lgamma_r\0" // IR(47743, 9)
  "log\0" // IR(47752, 4)
  "log2\0" // IR(47756, 5)
  "log10\0" // IR(47761, 6)
  "log1p\0" // IR(47767, 6)
  "logb\0" // IR(47773, 5)
  "mad\0" // IR(47778, 4)
  "maxmag\0" // IR(47782, 7)
  "minmag\0" // IR(47789, 7)
  "modf\0" // IR(47796, 5)
  "nan\0" // IR(47801, 4)
  "nextafter\0" // IR(47805, 10)
  "pow\0" // IR(47815, 4)
  "pown\0" // IR(47819, 5)
  "powr\0" // IR(47824, 5)
  "remainder\0" // IR(47829, 10)
  "remquo\0" // IR(47839, 7)
  "rint\0" // IR(47846, 5)
  "rootn\0" // IR(47851, 6)
  "round\0" // IR(47857, 6)
  "rsqrt\0" // IR(47863, 6)
  "sin\0" // IR(47869, 4)
  "sincos\0" // IR(47873, 7)
  "sinh\0" // IR(47880, 5)
  "sinpi\0" // IR(47885, 6)
  "sqrt\0" // IR(47891, 5)
  "tan\0" // IR(47896, 4)
  "tanh\0" // IR(47900, 5)
  "tanpi\0" // IR(47905, 6)
  "tgamma\0" // IR(47911, 7)
  "trunc\0" // IR(47918, 6)
  "half_cos\0" // IR(47924, 9)
  "half_divide\0" // IR(47933, 12)
  "half_exp\0" // IR(47945, 9)
  "half_exp2\0" // IR(47954, 10)
  "half_exp10\0" // IR(47964, 11)
  "half_log\0" // IR(47975, 9)
  "half_log2\0" // IR(47984, 10)
  "half_log10\0" // IR(47994, 11)
  "half_powr\0" // IR(48005, 10)
  "half_recip\0" // IR(48015, 11)
  "half_rsqrt\0" // IR(48026, 11)
  "half_sin\0" // IR(48037, 9)
  "half_sqrt\0" // IR(48046, 10)
  "half_tan\0" // IR(48056, 9)
  "native_cos\0" // IR(48065, 11)
  "native_divide\0" // IR(48076, 14)
  "native_exp\0" // IR(48090, 11)
  "native_exp2\0" // IR(48101, 12)
  "native_exp10\0" // IR(48113, 13)
  "native_log\0" // IR(48126, 11)
  "native_log2\0" // IR(48137, 12)
  "native_log10\0" // IR(48149, 13)
  "native_powr\0" // IR(48162, 12)
  "native_recip\0" // IR(48174, 13)
  "native_rsqrt\0" // IR(48187, 13)
  "native_sin\0" // IR(48200, 11)
  "native_sqrt\0" // IR(48211, 12)
  "native_tan\0" // IR(48223, 11)
  "fclamp\0" // IR(48234, 7)
  "degrees\0" // IR(48241, 8)
  "fmax_common\0" // IR(48249, 12)
  "fmin_common\0" // IR(48261, 12)
  "mix\0" // IR(48273, 4)
  "radians\0" // IR(48277, 8)
  "step\0" // IR(48285, 5)
  "smoothstep\0" // IR(48290, 11)
  "sign\0" // IR(48301, 5)
  "cross\0" // IR(48306, 6)
  "distance\0" // IR(48312, 9)
  "length\0" // IR(48321, 7)
  "normalize\0" // IR(48328, 10)
  "fast_distance\0" // IR(48338, 14)
  "fast_length\0" // IR(48352, 12)
  "fast_normalize\0" // IR(48364, 15)
  "s_abs\0" // IR(48379, 6)
  "s_abs_diff\0" // IR(48385, 11)
  "s_add_sat\0" // IR(48396, 10)
  "u_add_sat\0" // IR(48406, 10)
  "s_hadd\0" // IR(48416, 7)
  "u_hadd\0" // IR(48423, 7)
  "s_rhadd\0" // IR(48430, 8)
  "u_rhadd\0" // IR(48438, 8)
  "s_clamp\0" // IR(48446, 8)
  "u_clamp\0" // IR(48454, 8)
  "clz\0" // IR(48462, 4)
  "ctz\0" // IR(48466, 4)
  "s_mad_hi\0" // IR(48470, 9)
  "u_mad_sat\0" // IR(48479, 10)
  "s_mad_sat\0" // IR(48489, 10)
  "s_max\0" // IR(48499, 6)
  "u_max\0" // IR(48505, 6)
  "s_min\0" // IR(48511, 6)
  "u_min\0" // IR(48517, 6)
  "s_mul_hi\0" // IR(48523, 9)
  "rotate\0" // IR(48532, 7)
  "s_sub_sat\0" // IR(48539, 10)
  "u_sub_sat\0" // IR(48549, 10)
  "u_upsample\0" // IR(48559, 11)
  "s_upsample\0" // IR(48570, 11)
  "popcount\0" // IR(48581, 9)
  "s_mad24\0" // IR(48590, 8)
  "u_mad24\0" // IR(48598, 8)
  "s_mul24\0" // IR(48606, 8)
  "u_mul24\0" // IR(48614, 8)
  "vloadn\0" // IR(48622, 7)
  "vstoren\0" // IR(48629, 8)
  "vload_half\0" // IR(48637, 11)
  "vload_halfn\0" // IR(48648, 12)
  "vstore_half\0" // IR(48660, 12)
  "vstore_half_r\0" // IR(48672, 14)
  "vstore_halfn\0" // IR(48686, 13)
  "vstore_halfn_r\0" // IR(48699, 15)
  "vloada_halfn\0" // IR(48714, 13)
  "vstorea_halfn\0" // IR(48727, 14)
  "vstorea_halfn_r\0" // IR(48741, 16)
  "shuffle\0" // IR(48757, 8)
  "shuffle2\0" // IR(48765, 9)
  "printf\0" // IR(48774, 7)
  "prefetch\0" // IR(48781, 9)
  "bitselect\0" // IR(48790, 10)
  "select\0" // IR(48800, 7)
  "u_abs\0" // IR(48807, 6)
  "u_abs_diff\0" // IR(48813, 11)
  "u_mul_hi\0" // IR(48824, 9)
  "u_mad_hi\0" // IR(48833, 9)
  "CubeFaceIndexAMD\0" // IR(48842, 17)
  "CubeFaceCoordAMD\0" // IR(48859, 17)
  "TimeAMD\0" // IR(48876, 8)
  "SwizzleInvocationsAMD\0" // IR(48884, 22)
  "SwizzleInvocationsMaskedAMD\0" // IR(48906, 28)
  "WriteInvocationAMD\0" // IR(48934, 19)
  "MbcntAMD\0" // IR(48953, 9)
  "InterpolateAtVertexAMD\0" // IR(48962, 23)
  "FMin3AMD\0" // IR(48985, 9)
  "UMin3AMD\0" // IR(48994, 9)
  "SMin3AMD\0" // IR(49003, 9)
  "FMax3AMD\0" // IR(49012, 9)
  "UMax3AMD\0" // IR(49021, 9)
  "SMax3AMD\0" // IR(49030, 9)
  "FMid3AMD\0" // IR(49039, 9)
  "UMid3AMD\0" // IR(49048, 9)
  "SMid3AMD\0" // IR(49057, 9)
;

// Array of IndexRanges, where each represents a string by referencing
// the kStrings table.
// This array contains all sequences of alias strings used in the grammar.
// This table is referenced by an IndexRange elsewhere, i.e. by the 'aliases'
// field of an instruction or operand description.
static const IndexRange kAliasSpans[] = {
  IR(4583, 27), // 0 PhysicalStorageBuffer64EXT
  IR(5494, 18), // 1 SubgroupEqMaskKHR
  IR(5549, 18), // 2 SubgroupGeMaskKHR
  IR(5582, 18), // 3 SubgroupGtMaskKHR
  IR(5615, 18), // 4 SubgroupLeMaskKHR
  IR(5648, 18), // 5 SubgroupLtMaskKHR
  IR(6506, 12), // 6 BaryCoordNV
  IR(6561, 19), // 7 BaryCoordNoPerspNV
  IR(6592, 15), // 8 FragmentSizeNV
  IR(6649, 22), // 9 InvocationsPerPixelNV
  IR(6777, 11), // 10 LaunchIdNV
  IR(6802, 13), // 11 LaunchSizeNV
  IR(6833, 17), // 12 WorldRayOriginNV
  IR(6871, 20), // 13 WorldRayDirectionNV
  IR(6910, 18), // 14 ObjectRayOriginNV
  IR(6950, 21), // 15 ObjectRayDirectionNV
  IR(6982, 10), // 16 RayTminNV
  IR(7003, 10), // 17 RayTmaxNV
  IR(7036, 22), // 18 InstanceCustomIndexNV
  IR(7075, 16), // 19 ObjectToWorldNV
  IR(7108, 16), // 20 WorldToObjectNV
  IR(7142, 10), // 21 HitKindNV
  IR(7373, 19), // 22 IncomingRayFlagsNV
  IR(8994, 28), // 23 StorageUniformBufferBlock16
  IR(9057, 17), // 24 StorageUniform16
  IR(9861, 27), // 25 ShaderViewportIndexLayerNV
  IR(9905, 22), // 26 FragmentBarycentricNV
  IR(9958, 30), // 27 ComputeDerivativeGroupQuadsNV
  IR(9988, 14), // 28 ShadingRateNV
  IR(10048, 20), // 29 ShaderNonUniformEXT
  IR(10091, 26), // 30 RuntimeDescriptorArrayEXT
  IR(10153, 39), // 31 InputAttachmentArrayDynamicIndexingEXT
  IR(10231, 42), // 32 UniformTexelBufferArrayDynamicIndexingEXT
  IR(10312, 42), // 33 StorageTexelBufferArrayDynamicIndexingEXT
  IR(10391, 40), // 34 UniformBufferArrayNonUniformIndexingEXT
  IR(10467, 39), // 35 SampledImageArrayNonUniformIndexingEXT
  IR(10543, 40), // 36 StorageBufferArrayNonUniformIndexingEXT
  IR(10619, 39), // 37 StorageImageArrayNonUniformIndexingEXT
  IR(10697, 42), // 38 InputAttachmentArrayNonUniformIndexingEXT
  IR(10781, 45), // 39 UniformTexelBufferArrayNonUniformIndexingEXT
  IR(10868, 45), // 40 StorageTexelBufferArrayNonUniformIndexingEXT
  IR(10931, 21), // 41 VulkanMemoryModelKHR
  IR(10981, 32), // 42 VulkanMemoryModelDeviceScopeKHR
  IR(11013, 34), // 43 PhysicalStorageBufferAddressesEXT
  IR(11079, 31), // 44 ComputeDerivativeGroupLinearNV
  IR(11283, 28), // 45 DemoteToHelperInvocationEXT
  IR(12753, 22), // 46 DotProductInputAllKHR
  IR(12797, 25), // 47 DotProductInput4x8BitKHR
  IR(12850, 31), // 48 DotProductInput4x8BitPackedKHR
  IR(12892, 14), // 49 DotProductKHR
  IR(13057, 13), // 50 OptNoneINTEL
  IR(15989, 15), // 51 PerPrimitiveNV
  IR(16037, 12), // 52 PerVertexNV
  IR(16060, 14), // 53 NonUniformEXT
  IR(16090, 19), // 54 RestrictPointerEXT
  IR(16124, 18), // 55 AliasedPointerEXT
  IR(16434, 24), // 56 HlslCounterBufferGOOGLE
  IR(16471, 19), // 57 HlslSemanticGOOGLE
  IR(19145, 14), // 58 OutputLinesNV
  IR(19179, 19), // 59 OutputPrimitivesNV
  IR(19222, 23), // 60 DerivativeGroupQuadsNV
  IR(19270, 24), // 61 DerivativeGroupLinearNV
  IR(19313, 18), // 62 OutputTrianglesNV
  IR(20061, 16), // 63 RayGenerationNV
  IR(20093, 15), // 64 IntersectionNV
  IR(20118, 9), // 65 AnyHitNV
  IR(20141, 13), // 66 ClosestHitNV
  IR(20162, 7), // 67 MissNV
  IR(20181, 11), // 68 CallableNV
  IR(20298, 23), // 69 AllowContractFastINTEL
  IR(20334, 18), // 70 AllowReassocINTEL
  IR(20788, 22), // 71 MakeTexelAvailableKHR
  IR(20827, 20), // 72 MakeTexelVisibleKHR
  IR(20863, 19), // 73 NonPrivateTexelKHR
  IR(20896, 17), // 74 VolatileTexelKHR
  IR(22273, 24), // 75 MakePointerAvailableKHR
  IR(22316, 22), // 76 MakePointerVisibleKHR
  IR(22356, 21), // 77 NonPrivatePointerKHR
  IR(22443, 10), // 78 VulkanKHR
  IR(13805, 5), // 79 None
  IR(22626, 16), // 80 OutputMemoryKHR
  IR(22656, 17), // 81 MakeAvailableKHR
  IR(22685, 15), // 82 MakeVisibleKHR
  IR(22761, 28), // 83 PackedVectorFormat4x8BitKHR
  IR(23076, 24), // 84 SkipBuiltinPrimitivesNV
  IR(23816, 15), // 85 QueueFamilyKHR
  IR(24187, 15), // 86 CallableDataNV
  IR(24226, 23), // 87 IncomingCallableDataNV
  IR(24263, 13), // 88 RayPayloadNV
  IR(24292, 15), // 89 HitAttributeNV
  IR(24329, 21), // 90 IncomingRayPayloadNV
  IR(24372, 21), // 91 ShaderRecordBufferNV
  IR(24415, 25), // 92 PhysicalStorageBufferEXT
  IR(31417, 8), // 93 SDotKHR
  IR(31430, 8), // 94 UDotKHR
  IR(31444, 9), // 95 SUDotKHR
  IR(31464, 14), // 96 SDotAccSatKHR
  IR(31489, 14), // 97 UDotAccSatKHR
  IR(31515, 15), // 98 SUDotAccSatKHR
  IR(34000, 21), // 99 ReportIntersectionNV
  IR(34175, 28), // 100 TypeAccelerationStructureNV
  IR(36224, 21), // 101 DecorateStringGOOGLE
  IR(36266, 27), // 102 MemberDecorateStringGOOGLE
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
  spv::Capability::ShaderViewportMaskNV, // 44
  spv::Capability::MeshShadingNV, // 45
  spv::Capability::ShaderStereoViewNV, // 46
  spv::Capability::PerViewAttributesNV, // 47
  spv::Capability::MeshShadingNV, // 48
  spv::Capability::FragmentFullyCoveredEXT, // 49
  spv::Capability::MeshShadingNV, // 50
  spv::Capability::FragmentBarycentricKHR, // 51
  spv::Capability::FragmentDensityEXT, // 52
  spv::Capability::MeshShadingEXT, // 53
  spv::Capability::RayTracingNV, // 54
  spv::Capability::RayTracingKHR, // 55
  spv::Capability::RayTracingNV, // 56
  spv::Capability::RayTracingMotionBlurNV, // 57
  spv::Capability::RayTracingPositionFetchKHR, // 58
  spv::Capability::RayTracingDisplacementMicromapNV, // 59
  spv::Capability::RayTracingKHR, // 60
  spv::Capability::RayTracingSpheresGeometryNV, // 61
  spv::Capability::RayTracingLinearSweptSpheresGeometryNV, // 62
  spv::Capability::ShaderSMBuiltinsNV, // 63
  spv::Capability::RayTracingClusterAccelerationStructureNV, // 64
  spv::Capability::RayCullMaskKHR, // 65
  spv::Capability::Matrix, // 66
  spv::Capability::Int64, // 67
  spv::Capability::ImageBasic, // 68
  spv::Capability::Geometry, // 69
  spv::Capability::SampledCubeArray, // 70
  spv::Capability::SampledRect, // 71
  spv::Capability::Sampled1D, // 72
  spv::Capability::SampledBuffer, // 73
  spv::Capability::DeviceEnqueue, // 74
  spv::Capability::Pipes, // 75
  spv::Capability::GroupNonUniform, // 76
  spv::Capability::WorkgroupMemoryExplicitLayoutKHR, // 77
  spv::Capability::StorageBuffer16BitAccess, // 78
  spv::Capability::VariablePointersStorageBuffer, // 79
  spv::Capability::AtomicStorage, // 80
  spv::Capability::StorageBuffer8BitAccess, // 81
  spv::Capability::RayQueryKHR, // 82
  spv::Capability::RayTracingKHR, // 83
  spv::Capability::Int4TypeINTEL, // 84
  spv::Capability::CooperativeMatrixKHR, // 85
  spv::Capability::BFloat16TypeKHR, // 86
  spv::Capability::BFloat16TypeKHR, // 87
  spv::Capability::CooperativeMatrixKHR, // 88
  spv::Capability::MultiViewport, // 89
  spv::Capability::ShaderViewportIndexLayerEXT, // 90
  spv::Capability::ShaderViewportMaskNV, // 91
  spv::Capability::InputAttachment, // 92
  spv::Capability::ImageBuffer, // 93
  spv::Capability::ShaderNonUniform, // 94
  spv::Capability::InputAttachment, // 95
  spv::Capability::ShaderNonUniform, // 96
  spv::Capability::SampledBuffer, // 97
  spv::Capability::ShaderNonUniform, // 98
  spv::Capability::ImageBuffer, // 99
  spv::Capability::ShaderNonUniform, // 100
  spv::Capability::VectorAnyINTEL, // 101
  spv::Capability::Int8, // 102
  spv::Capability::FPGAClusterAttributesINTEL, // 103
  spv::Capability::FPGAKernelAttributesINTEL, // 104
  spv::Capability::Subgroup2DBlockIOINTEL, // 105
  spv::Capability::Shader, // 106
  spv::Capability::Kernel, // 107
  spv::Capability::Shader, // 108
  spv::Capability::UniformDecoration, // 109
  spv::Capability::GeometryStreams, // 110
  spv::Capability::TransformFeedback, // 111
  spv::Capability::Kernel, // 112
  spv::Capability::FloatControls2, // 113
  spv::Capability::Linkage, // 114
  spv::Capability::SampleMaskOverrideCoverageNV, // 115
  spv::Capability::GeometryShaderPassthroughNV, // 116
  spv::Capability::MeshShadingNV, // 117
  spv::Capability::MeshShadingEXT, // 118
  spv::Capability::ShaderInvocationReorderNV, // 119
  spv::Capability::BindlessTextureNV, // 120
  spv::Capability::VectorComputeINTEL, // 121
  spv::Capability::IndirectReferencesINTEL, // 122
  spv::Capability::AsmINTEL, // 123
  spv::Capability::FunctionFloatControlINTEL, // 124
  spv::Capability::FPGAMemoryAttributesINTEL, // 125
  spv::Capability::FPGAMemoryAccessesINTEL, // 126
  spv::Capability::LoopFuseINTEL, // 127
  spv::Capability::FPGADSPControlINTEL, // 128
  spv::Capability::MemoryAccessAliasingINTEL, // 129
  spv::Capability::FPGAInvocationPipeliningAttributesINTEL, // 130
  spv::Capability::FPGABufferLocationINTEL, // 131
  spv::Capability::IOPipesINTEL, // 132
  spv::Capability::FPGAClusterAttributesV2INTEL, // 133
  spv::Capability::FPMaxErrorINTEL, // 134
  spv::Capability::FPGALatencyControlINTEL, // 135
  spv::Capability::FPGAArgumentInterfacesINTEL, // 136
  spv::Capability::GlobalVariableHostAccessINTEL, // 137
  spv::Capability::GlobalVariableFPGADecorationsINTEL, // 138
  spv::Capability::CacheControlsINTEL, // 139
  spv::Capability::TileImageColorReadAccessEXT, // 140
  spv::Capability::Geometry, // 141
  spv::Capability::Tessellation, // 142
  spv::Capability::MeshShadingNV, // 143
  spv::Capability::MeshShadingEXT, // 144
  spv::Capability::Geometry, // 145
  spv::Capability::MeshShadingNV, // 146
  spv::Capability::MeshShadingEXT, // 147
  spv::Capability::SubgroupDispatch, // 148
  spv::Capability::TileImageDepthReadAccessEXT, // 149
  spv::Capability::TileImageStencilReadAccessEXT, // 150
  spv::Capability::SampleMaskPostDepthCoverage, // 151
  spv::Capability::DenormPreserve, // 152
  spv::Capability::DenormFlushToZero, // 153
  spv::Capability::SignedZeroInfNanPreserve, // 154
  spv::Capability::RoundingModeRTE, // 155
  spv::Capability::RoundingModeRTZ, // 156
  spv::Capability::QuadControlKHR, // 157
  spv::Capability::ComputeDerivativeGroupQuadsNV, // 158
  spv::Capability::ComputeDerivativeGroupQuadsKHR, // 159
  spv::Capability::ComputeDerivativeGroupLinearNV, // 160
  spv::Capability::ComputeDerivativeGroupLinearKHR, // 161
  spv::Capability::FragmentShaderPixelInterlockEXT, // 162
  spv::Capability::FragmentShaderSampleInterlockEXT, // 163
  spv::Capability::FragmentShaderShadingRateInterlockEXT, // 164
  spv::Capability::RoundToInfinityINTEL, // 165
  spv::Capability::KernelAttributesINTEL, // 166
  spv::Capability::FloatControls2, // 167
  spv::Capability::FPGAKernelAttributesv2INTEL, // 168
  spv::Capability::RegisterLimitsINTEL, // 169
  spv::Capability::FloatControls2, // 170
  spv::Capability::FPFastMathModeINTEL, // 171
  spv::Capability::OptNoneEXT, // 172
  spv::Capability::RuntimeAlignedAttributeINTEL, // 173
  spv::Capability::Kernel, // 174
  spv::Capability::GroupNonUniformArithmetic, // 175
  spv::Capability::GroupNonUniformBallot, // 176
  spv::Capability::GroupNonUniformClustered, // 177
  spv::Capability::GroupNonUniformPartitionedNV, // 178
  spv::Capability::ImageGatherExtended, // 179
  spv::Capability::MinLod, // 180
  spv::Capability::VulkanMemoryModel, // 181
  spv::Capability::FPGALoopControlsINTEL, // 182
  spv::Capability::ArbitraryPrecisionFixedPointINTEL, // 183
  spv::Capability::RawAccessChainsNV, // 184
  spv::Capability::RayTraversalPrimitiveCullingKHR, // 185
  spv::Capability::RayTracingOpacityMicromapEXT, // 186
  spv::Capability::RayQueryKHR, // 187
  spv::Capability::StorageImageExtendedFormats, // 188
  spv::Capability::Int64ImageEXT, // 189
  spv::Capability::Shader, // 190
  spv::Capability::VectorComputeINTEL, // 191
  spv::Capability::GenericPointer, // 192
  spv::Capability::FunctionPointersINTEL, // 193
  spv::Capability::USMStorageClassesINTEL, // 194
  spv::Capability::CooperativeMatrixTensorAddressingNV, // 195
  spv::Capability::CooperativeMatrixBlockLoadsNV, // 196
  spv::Capability::Addresses, // 197
  spv::Capability::PhysicalStorageBufferAddresses, // 198
  spv::Capability::LiteralSampler, // 199
  spv::Capability::Addresses, // 200
  spv::Capability::UntypedPointersKHR, // 201
  spv::Capability::Addresses, // 202
  spv::Capability::VariablePointers, // 203
  spv::Capability::VariablePointersStorageBuffer, // 204
  spv::Capability::PhysicalStorageBufferAddresses, // 205
  spv::Capability::Kernel, // 206
  spv::Capability::ImageQuery, // 207
  spv::Capability::ImageQuery, // 208
  spv::Capability::Shader, // 209
  spv::Capability::BitInstructions, // 210
  spv::Capability::DerivativeControl, // 211
  spv::Capability::Groups, // 212
  spv::Capability::SparseResidency, // 213
  spv::Capability::PipeStorage, // 214
  spv::Capability::NamedBarrier, // 215
  spv::Capability::GroupNonUniformVote, // 216
  spv::Capability::GroupNonUniformBallot, // 217
  spv::Capability::GroupNonUniformShuffle, // 218
  spv::Capability::GroupNonUniformShuffleRelative, // 219
  spv::Capability::GroupNonUniformArithmetic, // 220
  spv::Capability::GroupNonUniformClustered, // 221
  spv::Capability::GroupNonUniformPartitionedNV, // 222
  spv::Capability::GroupNonUniformQuad, // 223
  spv::Capability::Addresses, // 224
  spv::Capability::VariablePointers, // 225
  spv::Capability::VariablePointersStorageBuffer, // 226
  spv::Capability::UntypedPointersKHR, // 227
  spv::Capability::SubgroupBallotKHR, // 228
  spv::Capability::SubgroupVoteKHR, // 229
  spv::Capability::GroupNonUniformRotateKHR, // 230
  spv::Capability::RayTracingKHR, // 231
  spv::Capability::RayQueryKHR, // 232
  spv::Capability::DotProduct, // 233
  spv::Capability::CooperativeMatrixKHR, // 234
  spv::Capability::ReplicatedCompositesEXT, // 235
  spv::Capability::TextureSampleWeightedQCOM, // 236
  spv::Capability::TextureBoxFilterQCOM, // 237
  spv::Capability::TextureBlockMatchQCOM, // 238
  spv::Capability::TextureBlockMatch2QCOM, // 239
  spv::Capability::FragmentMaskAMD, // 240
  spv::Capability::ShaderClockKHR, // 241
  spv::Capability::ShaderInvocationReorderNV, // 242
  spv::Capability::RayTracingMotionBlurNV, // 243
  spv::Capability::ImageFootprintNV, // 244
  spv::Capability::CooperativeVectorNV, // 245
  spv::Capability::CooperativeVectorTrainingNV, // 246
  spv::Capability::CooperativeMatrixConversionsNV, // 247
  spv::Capability::DisplacementMicromapNV, // 248
  spv::Capability::RayQueryPositionFetchKHR, // 249
  spv::Capability::RayTracingNV, // 250
  spv::Capability::RayTracingKHR, // 251
  spv::Capability::RayQueryKHR, // 252
  spv::Capability::DisplacementMicromapNV, // 253
  spv::Capability::CooperativeMatrixNV, // 254
  spv::Capability::FragmentShaderSampleInterlockEXT, // 255
  spv::Capability::FragmentShaderPixelInterlockEXT, // 256
  spv::Capability::FragmentShaderShadingRateInterlockEXT, // 257
  spv::Capability::CooperativeMatrixReductionsNV, // 258
  spv::Capability::CooperativeMatrixPerElementOperationsNV, // 259
  spv::Capability::TensorAddressingNV, // 260
  spv::Capability::DemoteToHelperInvocation, // 261
  spv::Capability::SubgroupShuffleINTEL, // 262
  spv::Capability::SubgroupBufferBlockIOINTEL, // 263
  spv::Capability::SubgroupImageBlockIOINTEL, // 264
  spv::Capability::SubgroupImageMediaBlockIOINTEL, // 265
  spv::Capability::IntegerFunctions2INTEL, // 266
  spv::Capability::AtomicFloat16MinMaxEXT, // 267
  spv::Capability::AtomicFloat32MinMaxEXT, // 268
  spv::Capability::AtomicFloat64MinMaxEXT, // 269
  spv::Capability::AtomicFloat16VectorNV, // 270
  spv::Capability::ExpectAssumeKHR, // 271
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 272
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 273
  spv::Capability::SubgroupAvcMotionEstimationIntraINTEL, // 274
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 275
  spv::Capability::SubgroupAvcMotionEstimationChromaINTEL, // 276
  spv::Capability::VariableLengthArrayINTEL, // 277
  spv::Capability::ArbitraryPrecisionFloatingPointINTEL, // 278
  spv::Capability::UnstructuredLoopControlsINTEL, // 279
  spv::Capability::BlockingPipesINTEL, // 280
  spv::Capability::FPGARegINTEL, // 281
  spv::Capability::AtomicFloat16AddEXT, // 282
  spv::Capability::AtomicFloat32AddEXT, // 283
  spv::Capability::AtomicFloat64AddEXT, // 284
  spv::Capability::AtomicFloat16VectorNV, // 285
  spv::Capability::LongCompositesINTEL, // 286
  spv::Capability::BFloat16ConversionINTEL, // 287
  spv::Capability::SplitBarrierINTEL, // 288
  spv::Capability::ArithmeticFenceEXT, // 289
  spv::Capability::TaskSequenceINTEL, // 290
  spv::Capability::SubgroupBufferPrefetchINTEL, // 291
  spv::Capability::Subgroup2DBlockTransformINTEL, // 292
  spv::Capability::Subgroup2DBlockTransposeINTEL, // 293
  spv::Capability::SubgroupMatrixMultiplyAccumulateINTEL, // 294
  spv::Capability::TernaryBitwiseFunctionINTEL, // 295
  spv::Capability::GroupUniformArithmeticKHR, // 296
  spv::Capability::TensorFloat32RoundingINTEL, // 297
  spv::Capability::MaskedGatherScatterINTEL, // 298
  spv::Capability::Float64, // 299
  spv::Capability::InterpolationFunction, // 300
};

// Array of extensions, referenced by IndexRanges elsewhere.
// Contains all sequences of extensions used in the grammar.
static const spvtools::Extension kExtensionSpans[] = {
  spvtools::Extension::kSPV_EXT_physical_storage_buffer, // 0
  spvtools::Extension::kSPV_KHR_physical_storage_buffer, // 1
  spvtools::Extension::kSPV_KHR_shader_ballot, // 2
  spvtools::Extension::kSPV_KHR_shader_draw_parameters, // 3
  spvtools::Extension::kSPV_EXT_mesh_shader, // 4
  spvtools::Extension::kSPV_KHR_shader_draw_parameters, // 5
  spvtools::Extension::kSPV_NV_mesh_shader, // 6
  spvtools::Extension::kSPV_KHR_fragment_shading_rate, // 7
  spvtools::Extension::kSPV_KHR_device_group, // 8
  spvtools::Extension::kSPV_KHR_multiview, // 9
  spvtools::Extension::kSPV_AMD_shader_explicit_vertex_parameter, // 10
  spvtools::Extension::kSPV_EXT_shader_stencil_export, // 11
  spvtools::Extension::kSPV_NV_mesh_shader, // 12
  spvtools::Extension::kSPV_NV_viewport_array2, // 13
  spvtools::Extension::kSPV_NV_stereo_view_rendering, // 14
  spvtools::Extension::kSPV_NVX_multiview_per_view_attributes, // 15
  spvtools::Extension::kSPV_NV_mesh_shader, // 16
  spvtools::Extension::kSPV_EXT_fragment_fully_covered, // 17
  spvtools::Extension::kSPV_NV_mesh_shader, // 18
  spvtools::Extension::kSPV_KHR_fragment_shader_barycentric, // 19
  spvtools::Extension::kSPV_NV_fragment_shader_barycentric, // 20
  spvtools::Extension::kSPV_EXT_fragment_invocation_density, // 21
  spvtools::Extension::kSPV_NV_shading_rate, // 22
  spvtools::Extension::kSPV_EXT_mesh_shader, // 23
  spvtools::Extension::kSPV_KHR_ray_tracing, // 24
  spvtools::Extension::kSPV_NV_ray_tracing, // 25
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
  spvtools::Extension::kSPV_ARM_cooperative_matrix_layouts, // 36
  spvtools::Extension::kSPV_KHR_workgroup_memory_explicit_layout, // 37
  spvtools::Extension::kSPV_KHR_subgroup_vote, // 38
  spvtools::Extension::kSPV_KHR_16bit_storage, // 39
  spvtools::Extension::kSPV_KHR_variable_pointers, // 40
  spvtools::Extension::kSPV_KHR_shader_atomic_counter_ops, // 41
  spvtools::Extension::kSPV_KHR_post_depth_coverage, // 42
  spvtools::Extension::kSPV_KHR_8bit_storage, // 43
  spvtools::Extension::kSPV_KHR_float_controls, // 44
  spvtools::Extension::kSPV_KHR_ray_query, // 45
  spvtools::Extension::kSPV_KHR_untyped_pointers, // 46
  spvtools::Extension::kSPV_KHR_ray_query, // 47
  spvtools::Extension::kSPV_KHR_ray_tracing, // 48
  spvtools::Extension::kSPV_QCOM_image_processing, // 49
  spvtools::Extension::kSPV_QCOM_tile_shading, // 50
  spvtools::Extension::kSPV_QCOM_image_processing2, // 51
  spvtools::Extension::kSPV_AMD_gpu_shader_half_float_fetch, // 52
  spvtools::Extension::kSPV_AMD_texture_gather_bias_lod, // 53
  spvtools::Extension::kSPV_AMD_shader_fragment_mask, // 54
  spvtools::Extension::kSPV_AMD_shader_image_load_store_lod, // 55
  spvtools::Extension::kSPV_EXT_shader_image_int64, // 56
  spvtools::Extension::kSPV_KHR_shader_clock, // 57
  spvtools::Extension::kSPV_AMDX_shader_enqueue, // 58
  spvtools::Extension::kSPV_KHR_quad_control, // 59
  spvtools::Extension::kSPV_INTEL_int4, // 60
  spvtools::Extension::kSPV_KHR_bfloat16, // 61
  spvtools::Extension::kSPV_NV_sample_mask_override_coverage, // 62
  spvtools::Extension::kSPV_NV_geometry_shader_passthrough, // 63
  spvtools::Extension::kSPV_EXT_shader_viewport_index_layer, // 64
  spvtools::Extension::kSPV_NV_viewport_array2, // 65
  spvtools::Extension::kSPV_NV_viewport_array2, // 66
  spvtools::Extension::kSPV_NVX_multiview_per_view_attributes, // 67
  spvtools::Extension::kSPV_NV_shader_image_footprint, // 68
  spvtools::Extension::kSPV_KHR_compute_shader_derivatives, // 69
  spvtools::Extension::kSPV_NV_compute_shader_derivatives, // 70
  spvtools::Extension::kSPV_NV_shader_subgroup_partitioned, // 71
  spvtools::Extension::kSPV_EXT_descriptor_indexing, // 72
  spvtools::Extension::kSPV_KHR_ray_tracing_position_fetch, // 73
  spvtools::Extension::kSPV_KHR_vulkan_memory_model, // 74
  spvtools::Extension::kSPV_NV_cooperative_matrix, // 75
  spvtools::Extension::kSPV_EXT_fragment_shader_interlock, // 76
  spvtools::Extension::kSPV_EXT_demote_to_helper_invocation, // 77
  spvtools::Extension::kSPV_NV_displacement_micromap, // 78
  spvtools::Extension::kSPV_EXT_opacity_micromap, // 79
  spvtools::Extension::kSPV_NV_shader_invocation_reorder, // 80
  spvtools::Extension::kSPV_NV_bindless_texture, // 81
  spvtools::Extension::kSPV_NV_cooperative_vector, // 82
  spvtools::Extension::kSPV_NV_shader_atomic_fp16_vector, // 83
  spvtools::Extension::kSPV_NV_raw_access_chains, // 84
  spvtools::Extension::kSPV_NV_cooperative_matrix2, // 85
  spvtools::Extension::kSPV_NV_tensor_addressing, // 86
  spvtools::Extension::kSPV_INTEL_subgroups, // 87
  spvtools::Extension::kSPV_INTEL_media_block_io, // 88
  spvtools::Extension::kSPV_INTEL_float_controls2, // 89
  spvtools::Extension::kSPV_INTEL_shader_integer_functions2, // 90
  spvtools::Extension::kSPV_INTEL_function_pointers, // 91
  spvtools::Extension::kSPV_INTEL_inline_assembly, // 92
  spvtools::Extension::kSPV_EXT_shader_atomic_float_min_max, // 93
  spvtools::Extension::kSPV_INTEL_vector_compute, // 94
  spvtools::Extension::kSPV_KHR_expect_assume, // 95
  spvtools::Extension::kSPV_INTEL_device_side_avc_motion_estimation, // 96
  spvtools::Extension::kSPV_INTEL_variable_length_array, // 97
  spvtools::Extension::kSPV_INTEL_fpga_memory_attributes, // 98
  spvtools::Extension::kSPV_INTEL_fp_fast_math_mode, // 99
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_integers, // 100
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_floating_point, // 101
  spvtools::Extension::kSPV_INTEL_unstructured_loop_controls, // 102
  spvtools::Extension::kSPV_INTEL_fpga_loop_controls, // 103
  spvtools::Extension::kSPV_INTEL_kernel_attributes, // 104
  spvtools::Extension::kSPV_INTEL_fpga_memory_accesses, // 105
  spvtools::Extension::kSPV_INTEL_fpga_cluster_attributes, // 106
  spvtools::Extension::kSPV_INTEL_loop_fuse, // 107
  spvtools::Extension::kSPV_INTEL_fpga_dsp_control, // 108
  spvtools::Extension::kSPV_INTEL_memory_access_aliasing, // 109
  spvtools::Extension::kSPV_INTEL_fpga_invocation_pipelining_attributes, // 110
  spvtools::Extension::kSPV_INTEL_fpga_buffer_location, // 111
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_fixed_point, // 112
  spvtools::Extension::kSPV_INTEL_usm_storage_classes, // 113
  spvtools::Extension::kSPV_INTEL_runtime_aligned, // 114
  spvtools::Extension::kSPV_INTEL_io_pipes, // 115
  spvtools::Extension::kSPV_INTEL_blocking_pipes, // 116
  spvtools::Extension::kSPV_INTEL_fpga_reg, // 117
  spvtools::Extension::kSPV_KHR_integer_dot_product, // 118
  spvtools::Extension::kSPV_KHR_cooperative_matrix, // 119
  spvtools::Extension::kSPV_EXT_replicated_composites, // 120
  spvtools::Extension::kSPV_KHR_bit_instructions, // 121
  spvtools::Extension::kSPV_KHR_subgroup_rotate, // 122
  spvtools::Extension::kSPV_KHR_float_controls2, // 123
  spvtools::Extension::kSPV_EXT_shader_atomic_float_add, // 124
  spvtools::Extension::kSPV_INTEL_long_composites, // 125
  spvtools::Extension::kSPV_EXT_optnone, // 126
  spvtools::Extension::kSPV_INTEL_optnone, // 127
  spvtools::Extension::kSPV_EXT_shader_atomic_float16_add, // 128
  spvtools::Extension::kSPV_INTEL_debug_module, // 129
  spvtools::Extension::kSPV_INTEL_bfloat16_conversion, // 130
  spvtools::Extension::kSPV_INTEL_split_barrier, // 131
  spvtools::Extension::kSPV_EXT_arithmetic_fence, // 132
  spvtools::Extension::kSPV_INTEL_task_sequence, // 133
  spvtools::Extension::kSPV_INTEL_fp_max_error, // 134
  spvtools::Extension::kSPV_INTEL_fpga_latency_control, // 135
  spvtools::Extension::kSPV_INTEL_fpga_argument_interfaces, // 136
  spvtools::Extension::kSPV_INTEL_global_variable_host_access, // 137
  spvtools::Extension::kSPV_INTEL_global_variable_fpga_decorations, // 138
  spvtools::Extension::kSPV_INTEL_subgroup_buffer_prefetch, // 139
  spvtools::Extension::kSPV_INTEL_2d_block_io, // 140
  spvtools::Extension::kSPV_INTEL_subgroup_matrix_multiply_accumulate, // 141
  spvtools::Extension::kSPV_INTEL_ternary_bitwise_function, // 142
  spvtools::Extension::kSPV_KHR_uniform_group_instructions, // 143
  spvtools::Extension::kSPV_INTEL_tensor_float32_conversion, // 144
  spvtools::Extension::kSPV_INTEL_masked_gather_scatter, // 145
  spvtools::Extension::kSPV_INTEL_cache_controls, // 146
  spvtools::Extension::kSPV_INTEL_maximum_registers, // 147
  spvtools::Extension::kSPV_KHR_no_integer_wrap_decoration, // 148
  spvtools::Extension::kSPV_EXT_mesh_shader, // 149
  spvtools::Extension::kSPV_NV_mesh_shader, // 150
  spvtools::Extension::kSPV_GOOGLE_hlsl_functionality1, // 151
  spvtools::Extension::kSPV_GOOGLE_user_type, // 152
  spvtools::Extension::kSPV_KHR_subgroup_uniform_control_flow, // 153
  spvtools::Extension::kSPV_AMD_shader_early_and_late_fragment_tests, // 154
  spvtools::Extension::kSPV_AMD_shader_early_and_late_fragment_tests, // 155
  spvtools::Extension::kSPV_EXT_shader_stencil_export, // 156
  spvtools::Extension::kSPV_KHR_maximal_reconvergence, // 157
  spvtools::Extension::kSPV_KHR_linkonce_odr, // 158
  spvtools::Extension::kSPV_KHR_storage_buffer_storage_class, // 159
  spvtools::Extension::kSPV_KHR_variable_pointers, // 160
  spvtools::Extension::kSPV_KHR_terminate_invocation, // 161
  spvtools::Extension::kSPV_KHR_relaxed_extended_instruction, // 162
  spvtools::Extension::kSPV_KHR_ray_tracing, // 163
  spvtools::Extension::kSPV_KHR_ray_query, // 164
  spvtools::Extension::kSPV_NV_ray_tracing, // 165
  spvtools::Extension::kSPV_KHR_ray_tracing, // 166
  spvtools::Extension::kSPV_NV_ray_tracing, // 167
  spvtools::Extension::kSPV_KHR_ray_tracing, // 168
  spvtools::Extension::kSPV_KHR_ray_query, // 169
  spvtools::Extension::kSPV_NV_displacement_micromap, // 170
  spvtools::Extension::kSPV_GOOGLE_decorate_string, // 171
  spvtools::Extension::kSPV_GOOGLE_hlsl_functionality1, // 172
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
  SPV_OPERAND_TYPE_STORAGE_CLASS, // 357
  SPV_OPERAND_TYPE_TYPE_ID, // 358
  SPV_OPERAND_TYPE_RESULT_ID, // 359
  SPV_OPERAND_TYPE_STORAGE_CLASS, // 360
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 361
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 362
  SPV_OPERAND_TYPE_TYPE_ID, // 363
  SPV_OPERAND_TYPE_RESULT_ID, // 364
  SPV_OPERAND_TYPE_ID, // 365
  SPV_OPERAND_TYPE_ID, // 366
  SPV_OPERAND_TYPE_ID, // 367
  SPV_OPERAND_TYPE_VARIABLE_ID, // 368
  SPV_OPERAND_TYPE_TYPE_ID, // 369
  SPV_OPERAND_TYPE_RESULT_ID, // 370
  SPV_OPERAND_TYPE_ID, // 371
  SPV_OPERAND_TYPE_ID, // 372
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 373
  SPV_OPERAND_TYPE_ID, // 374
  SPV_OPERAND_TYPE_ID, // 375
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 376
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 377
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 378
  SPV_OPERAND_TYPE_TYPE_ID, // 379
  SPV_OPERAND_TYPE_RESULT_ID, // 380
  SPV_OPERAND_TYPE_SCOPE_ID, // 381
  SPV_OPERAND_TYPE_ID, // 382
  SPV_OPERAND_TYPE_ID, // 383
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 384
  SPV_OPERAND_TYPE_TYPE_ID, // 385
  SPV_OPERAND_TYPE_RESULT_ID, // 386
  SPV_OPERAND_TYPE_ID, // 387
  SPV_OPERAND_TYPE_EXTENSION_INSTRUCTION_NUMBER, // 388
  SPV_OPERAND_TYPE_VARIABLE_ID, // 389
  SPV_OPERAND_TYPE_ID, // 390
  SPV_OPERAND_TYPE_ID, // 391
  SPV_OPERAND_TYPE_ID, // 392
  SPV_OPERAND_TYPE_ID, // 393
  SPV_OPERAND_TYPE_ID, // 394
  SPV_OPERAND_TYPE_ID, // 395
  SPV_OPERAND_TYPE_ID, // 396
  SPV_OPERAND_TYPE_ID, // 397
  SPV_OPERAND_TYPE_ID, // 398
  SPV_OPERAND_TYPE_ID, // 399
  SPV_OPERAND_TYPE_ID, // 400
  SPV_OPERAND_TYPE_TYPE_ID, // 401
  SPV_OPERAND_TYPE_RESULT_ID, // 402
  SPV_OPERAND_TYPE_ID, // 403
  SPV_OPERAND_TYPE_ID, // 404
  SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT, // 405
  SPV_OPERAND_TYPE_TYPE_ID, // 406
  SPV_OPERAND_TYPE_RESULT_ID, // 407
  SPV_OPERAND_TYPE_ID, // 408
  SPV_OPERAND_TYPE_ID, // 409
  SPV_OPERAND_TYPE_ID, // 410
  SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT, // 411
  SPV_OPERAND_TYPE_RESULT_ID, // 412
  SPV_OPERAND_TYPE_ID, // 413
  SPV_OPERAND_TYPE_SCOPE_ID, // 414
  SPV_OPERAND_TYPE_ID, // 415
  SPV_OPERAND_TYPE_ID, // 416
  SPV_OPERAND_TYPE_ID, // 417
  SPV_OPERAND_TYPE_TYPE_ID, // 418
  SPV_OPERAND_TYPE_RESULT_ID, // 419
  SPV_OPERAND_TYPE_ID, // 420
  SPV_OPERAND_TYPE_ID, // 421
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 422
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 423
  SPV_OPERAND_TYPE_ID, // 424
  SPV_OPERAND_TYPE_ID, // 425
  SPV_OPERAND_TYPE_ID, // 426
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 427
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 428
  SPV_OPERAND_TYPE_TYPE_ID, // 429
  SPV_OPERAND_TYPE_RESULT_ID, // 430
  SPV_OPERAND_TYPE_ID, // 431
  SPV_OPERAND_TYPE_ID, // 432
  SPV_OPERAND_TYPE_ID, // 433
  SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS, // 434
  SPV_OPERAND_TYPE_ID, // 435
  SPV_OPERAND_TYPE_ID, // 436
  SPV_OPERAND_TYPE_ID, // 437
  SPV_OPERAND_TYPE_ID, // 438
  SPV_OPERAND_TYPE_ID, // 439
  SPV_OPERAND_TYPE_ID, // 440
  SPV_OPERAND_TYPE_ID, // 441
  SPV_OPERAND_TYPE_ID, // 442
  SPV_OPERAND_TYPE_ID, // 443
  SPV_OPERAND_TYPE_ID, // 444
  SPV_OPERAND_TYPE_ID, // 445
  SPV_OPERAND_TYPE_ID, // 446
  SPV_OPERAND_TYPE_ID, // 447
  SPV_OPERAND_TYPE_ID, // 448
  SPV_OPERAND_TYPE_ID, // 449
  SPV_OPERAND_TYPE_ID, // 450
  SPV_OPERAND_TYPE_ID, // 451
  SPV_OPERAND_TYPE_ID, // 452
  SPV_OPERAND_TYPE_ID, // 453
  SPV_OPERAND_TYPE_ID, // 454
  SPV_OPERAND_TYPE_ID, // 455
  SPV_OPERAND_TYPE_ID, // 456
  SPV_OPERAND_TYPE_ID, // 457
  SPV_OPERAND_TYPE_ID, // 458
  SPV_OPERAND_TYPE_ID, // 459
  SPV_OPERAND_TYPE_ID, // 460
  SPV_OPERAND_TYPE_ID, // 461
  SPV_OPERAND_TYPE_ID, // 462
  SPV_OPERAND_TYPE_ID, // 463
  SPV_OPERAND_TYPE_ID, // 464
  SPV_OPERAND_TYPE_ID, // 465
  SPV_OPERAND_TYPE_ID, // 466
  SPV_OPERAND_TYPE_ID, // 467
  SPV_OPERAND_TYPE_ID, // 468
  SPV_OPERAND_TYPE_ID, // 469
  SPV_OPERAND_TYPE_ID, // 470
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
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 496
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 497
  SPV_OPERAND_TYPE_TYPE_ID, // 498
  SPV_OPERAND_TYPE_RESULT_ID, // 499
  SPV_OPERAND_TYPE_ID, // 500
  SPV_OPERAND_TYPE_ID, // 501
  SPV_OPERAND_TYPE_ID, // 502
  SPV_OPERAND_TYPE_ID, // 503
  SPV_OPERAND_TYPE_OPTIONAL_IMAGE, // 504
  SPV_OPERAND_TYPE_TYPE_ID, // 505
  SPV_OPERAND_TYPE_RESULT_ID, // 506
  SPV_OPERAND_TYPE_ID, // 507
  SPV_OPERAND_TYPE_ID, // 508
  SPV_OPERAND_TYPE_ID, // 509
  SPV_OPERAND_TYPE_ID, // 510
  SPV_OPERAND_TYPE_ID, // 511
  SPV_OPERAND_TYPE_ID, // 512
  SPV_OPERAND_TYPE_ID, // 513
  SPV_OPERAND_TYPE_ID, // 514
  SPV_OPERAND_TYPE_ID, // 515
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 516
  SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS, // 517
  SPV_OPERAND_TYPE_ID, // 518
  SPV_OPERAND_TYPE_ID, // 519
  SPV_OPERAND_TYPE_ID, // 520
  SPV_OPERAND_TYPE_ID, // 521
  SPV_OPERAND_TYPE_ID, // 522
  SPV_OPERAND_TYPE_ID, // 523
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 524
  SPV_OPERAND_TYPE_TYPE_ID, // 525
  SPV_OPERAND_TYPE_RESULT_ID, // 526
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
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 539
  SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS, // 540
  SPV_OPERAND_TYPE_ID, // 541
  SPV_OPERAND_TYPE_ID, // 542
  SPV_OPERAND_TYPE_ID, // 543
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 544
  SPV_OPERAND_TYPE_TYPE_ID, // 545
  SPV_OPERAND_TYPE_RESULT_ID, // 546
  SPV_OPERAND_TYPE_ID, // 547
  SPV_OPERAND_TYPE_ID, // 548
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 549
  SPV_OPERAND_TYPE_ID, // 550
  SPV_OPERAND_TYPE_ID, // 551
  SPV_OPERAND_TYPE_ID, // 552
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 553
  SPV_OPERAND_TYPE_RESULT_ID, // 554
  SPV_OPERAND_TYPE_ID, // 555
  SPV_OPERAND_TYPE_SCOPE_ID, // 556
  SPV_OPERAND_TYPE_ID, // 557
  SPV_OPERAND_TYPE_ID, // 558
  SPV_OPERAND_TYPE_TYPE_ID, // 559
  SPV_OPERAND_TYPE_RESULT_ID, // 560
  SPV_OPERAND_TYPE_ID, // 561
  SPV_OPERAND_TYPE_ID, // 562
  SPV_OPERAND_TYPE_ID, // 563
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 564
  SPV_OPERAND_TYPE_ID, // 565
  SPV_OPERAND_TYPE_ID, // 566
  SPV_OPERAND_TYPE_ID, // 567
  SPV_OPERAND_TYPE_ID, // 568
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 569
  SPV_OPERAND_TYPE_TYPE_ID, // 570
  SPV_OPERAND_TYPE_RESULT_ID, // 571
  SPV_OPERAND_TYPE_ID, // 572
  SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE, // 573
  SPV_OPERAND_TYPE_ID, // 574
  SPV_OPERAND_TYPE_TYPE_ID, // 575
  SPV_OPERAND_TYPE_RESULT_ID, // 576
  SPV_OPERAND_TYPE_ID, // 577
  SPV_OPERAND_TYPE_ID, // 578
  SPV_OPERAND_TYPE_ID, // 579
  SPV_OPERAND_TYPE_MEMORY_ACCESS, // 580
  SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS, // 581
  SPV_OPERAND_TYPE_ID, // 582
  SPV_OPERAND_TYPE_ID, // 583
  SPV_OPERAND_TYPE_ID, // 584
  SPV_OPERAND_TYPE_MEMORY_ACCESS, // 585
  SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS, // 586
  SPV_OPERAND_TYPE_RESULT_ID, // 587
  SPV_OPERAND_TYPE_ID, // 588
  SPV_OPERAND_TYPE_ID, // 589
  SPV_OPERAND_TYPE_VARIABLE_ID, // 590
  SPV_OPERAND_TYPE_TYPE_ID, // 591
  SPV_OPERAND_TYPE_RESULT_ID, // 592
  SPV_OPERAND_TYPE_ID, // 593
  SPV_OPERAND_TYPE_ID, // 594
  SPV_OPERAND_TYPE_ID, // 595
  SPV_OPERAND_TYPE_ID, // 596
  SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS, // 597
  SPV_OPERAND_TYPE_ID, // 598
  SPV_OPERAND_TYPE_ID, // 599
  SPV_OPERAND_TYPE_ID, // 600
  SPV_OPERAND_TYPE_ID, // 601
  SPV_OPERAND_TYPE_ID, // 602
  SPV_OPERAND_TYPE_TYPE_ID, // 603
  SPV_OPERAND_TYPE_RESULT_ID, // 604
  SPV_OPERAND_TYPE_ID, // 605
  SPV_OPERAND_TYPE_ID, // 606
  SPV_OPERAND_TYPE_LITERAL_STRING, // 607
  SPV_OPERAND_TYPE_LITERAL_STRING, // 608
  SPV_OPERAND_TYPE_TYPE_ID, // 609
  SPV_OPERAND_TYPE_RESULT_ID, // 610
  SPV_OPERAND_TYPE_ID, // 611
  SPV_OPERAND_TYPE_ID, // 612
  SPV_OPERAND_TYPE_ID, // 613
  SPV_OPERAND_TYPE_ID, // 614
  SPV_OPERAND_TYPE_ID, // 615
  SPV_OPERAND_TYPE_ID, // 616
  SPV_OPERAND_TYPE_ID, // 617
  SPV_OPERAND_TYPE_TYPE_ID, // 618
  SPV_OPERAND_TYPE_RESULT_ID, // 619
  SPV_OPERAND_TYPE_ID, // 620
  SPV_OPERAND_TYPE_ID, // 621
  SPV_OPERAND_TYPE_ID, // 622
  SPV_OPERAND_TYPE_ID, // 623
  SPV_OPERAND_TYPE_ID, // 624
  SPV_OPERAND_TYPE_ID, // 625
  SPV_OPERAND_TYPE_ID, // 626
  SPV_OPERAND_TYPE_ID, // 627
  SPV_OPERAND_TYPE_TYPE_ID, // 628
  SPV_OPERAND_TYPE_RESULT_ID, // 629
  SPV_OPERAND_TYPE_ID, // 630
  SPV_OPERAND_TYPE_ID, // 631
  SPV_OPERAND_TYPE_ID, // 632
  SPV_OPERAND_TYPE_ID, // 633
  SPV_OPERAND_TYPE_ID, // 634
  SPV_OPERAND_TYPE_ID, // 635
  SPV_OPERAND_TYPE_ID, // 636
  SPV_OPERAND_TYPE_ID, // 637
  SPV_OPERAND_TYPE_ID, // 638
  SPV_OPERAND_TYPE_ID, // 639
  SPV_OPERAND_TYPE_ID, // 640
  SPV_OPERAND_TYPE_TYPE_ID, // 641
  SPV_OPERAND_TYPE_RESULT_ID, // 642
  SPV_OPERAND_TYPE_ID, // 643
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 644
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 645
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 646
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 647
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 648
  SPV_OPERAND_TYPE_TYPE_ID, // 649
  SPV_OPERAND_TYPE_RESULT_ID, // 650
  SPV_OPERAND_TYPE_ID, // 651
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 652
  SPV_OPERAND_TYPE_ID, // 653
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 654
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 655
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 656
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 657
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 658
  SPV_OPERAND_TYPE_TYPE_ID, // 659
  SPV_OPERAND_TYPE_RESULT_ID, // 660
  SPV_OPERAND_TYPE_ID, // 661
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 662
  SPV_OPERAND_TYPE_ID, // 663
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 664
  SPV_OPERAND_TYPE_RESULT_ID, // 665
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 666
  SPV_OPERAND_TYPE_RESULT_ID, // 667
  SPV_OPERAND_TYPE_ID, // 668
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 669
  SPV_OPERAND_TYPE_VARIABLE_ID, // 670
  SPV_OPERAND_TYPE_TYPE_ID, // 671
  SPV_OPERAND_TYPE_RESULT_ID, // 672
  SPV_OPERAND_TYPE_ID, // 673
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 674
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 675
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 676
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 677
  SPV_OPERAND_TYPE_ID, // 678
  SPV_OPERAND_TYPE_ID, // 679
  SPV_OPERAND_TYPE_ID, // 680
  SPV_OPERAND_TYPE_ID, // 681
  SPV_OPERAND_TYPE_ID, // 682
  SPV_OPERAND_TYPE_ID, // 683
  SPV_OPERAND_TYPE_ID, // 684
  SPV_OPERAND_TYPE_ID, // 685
  SPV_OPERAND_TYPE_ID, // 686
  SPV_OPERAND_TYPE_ID, // 687
  SPV_OPERAND_TYPE_ID, // 688
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
  SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS, // 703
  SPV_OPERAND_TYPE_TYPE_ID, // 704
  SPV_OPERAND_TYPE_RESULT_ID, // 705
  SPV_OPERAND_TYPE_ID, // 706
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 707
  SPV_OPERAND_TYPE_ID, // 708
  SPV_OPERAND_TYPE_ID, // 709
  SPV_OPERAND_TYPE_ID, // 710
  SPV_OPERAND_TYPE_ID, // 711
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 712
  SPV_OPERAND_TYPE_ID, // 713
  SPV_OPERAND_TYPE_ID, // 714
  SPV_OPERAND_TYPE_ID, // 715
  SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING, // 716
  SPV_OPERAND_TYPE_ID, // 717
  SPV_OPERAND_TYPE_STORAGE_CLASS, // 718
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 719
  SPV_OPERAND_TYPE_ID, // 720
  SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER, // 721
  SPV_OPERAND_TYPE_ID, // 722
  SPV_OPERAND_TYPE_ID, // 723
  SPV_OPERAND_TYPE_ID, // 724
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 725
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 726
  SPV_OPERAND_TYPE_ID, // 727
  SPV_OPERAND_TYPE_ID, // 728
  SPV_OPERAND_TYPE_ID, // 729
  SPV_OPERAND_TYPE_ID, // 730
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 731
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 732
  SPV_OPERAND_TYPE_ID, // 733
  SPV_OPERAND_TYPE_ID, // 734
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 735
  SPV_OPERAND_TYPE_VARIABLE_ID, // 736
  SPV_OPERAND_TYPE_ID, // 737
  SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE, // 738
  SPV_OPERAND_TYPE_ID, // 739
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 740
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 741
  SPV_OPERAND_TYPE_ID, // 742
  SPV_OPERAND_TYPE_ID, // 743
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 744
  SPV_OPERAND_TYPE_VARIABLE_ID, // 745
  SPV_OPERAND_TYPE_ID, // 746
  SPV_OPERAND_TYPE_ID, // 747
  SPV_OPERAND_TYPE_ID, // 748
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 749
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 750
  SPV_OPERAND_TYPE_ID, // 751
  SPV_OPERAND_TYPE_ID, // 752
  SPV_OPERAND_TYPE_ID, // 753
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 754
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 755
  SPV_OPERAND_TYPE_ID, // 756
  SPV_OPERAND_TYPE_ID, // 757
  SPV_OPERAND_TYPE_ID, // 758
  SPV_OPERAND_TYPE_ID, // 759
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 760
  SPV_OPERAND_TYPE_ID, // 761
  SPV_OPERAND_TYPE_ID, // 762
  SPV_OPERAND_TYPE_ID, // 763
  SPV_OPERAND_TYPE_ID, // 764
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 765
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 766
  SPV_OPERAND_TYPE_ID, // 767
  SPV_OPERAND_TYPE_ID, // 768
  SPV_OPERAND_TYPE_ID, // 769
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 770
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 771
  SPV_OPERAND_TYPE_ID, // 772
  SPV_OPERAND_TYPE_ID, // 773
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 774
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 775
  SPV_OPERAND_TYPE_VARIABLE_ID, // 776
  SPV_OPERAND_TYPE_ID, // 777
  SPV_OPERAND_TYPE_ID, // 778
  SPV_OPERAND_TYPE_ID, // 779
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 780
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 781
  SPV_OPERAND_TYPE_ID, // 782
  SPV_OPERAND_TYPE_ID, // 783
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 784
  SPV_OPERAND_TYPE_ID, // 785
  SPV_OPERAND_TYPE_ID, // 786
  SPV_OPERAND_TYPE_ID, // 787
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 788
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 789
  SPV_OPERAND_TYPE_ID, // 790
  SPV_OPERAND_TYPE_ID, // 791
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 792
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 793
  SPV_OPERAND_TYPE_ID, // 794
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 795
  SPV_OPERAND_TYPE_ID, // 796
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 797
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 798
  SPV_OPERAND_TYPE_ID, // 799
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 800
  SPV_OPERAND_TYPE_ID, // 801
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 802
  SPV_OPERAND_TYPE_ID, // 803
  SPV_OPERAND_TYPE_ID, // 804
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 805
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 806
  SPV_OPERAND_TYPE_ID, // 807
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 808
  SPV_OPERAND_TYPE_ID, // 809
  SPV_OPERAND_TYPE_ID, // 810
  SPV_OPERAND_TYPE_ID, // 811
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 812
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 813
  SPV_OPERAND_TYPE_ID, // 814
  SPV_OPERAND_TYPE_OPTIONAL_LITERAL_INTEGER, // 815
  SPV_OPERAND_TYPE_ID, // 816
  SPV_OPERAND_TYPE_ID, // 817
  SPV_OPERAND_TYPE_VARIABLE_ID, // 818
  SPV_OPERAND_TYPE_DEBUG_OPERATION, // 819
  SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER, // 820
  SPV_OPERAND_TYPE_ID, // 821
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 822
  SPV_OPERAND_TYPE_ID, // 823
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 824
  SPV_OPERAND_TYPE_ID, // 825
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 826
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 827
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 828
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 829
  SPV_OPERAND_TYPE_ID, // 830
  SPV_OPERAND_TYPE_ID, // 831
  SPV_OPERAND_TYPE_ID, // 832
  SPV_OPERAND_TYPE_ID, // 833
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 834
  SPV_OPERAND_TYPE_ID, // 835
  SPV_OPERAND_TYPE_ID, // 836
  SPV_OPERAND_TYPE_ID, // 837
  SPV_OPERAND_TYPE_ID, // 838
  SPV_OPERAND_TYPE_ID, // 839
  SPV_OPERAND_TYPE_ID, // 840
  SPV_OPERAND_TYPE_ID, // 841
  SPV_OPERAND_TYPE_ID, // 842
  SPV_OPERAND_TYPE_VARIABLE_ID, // 843
  SPV_OPERAND_TYPE_ID, // 844
  SPV_OPERAND_TYPE_ID, // 845
  SPV_OPERAND_TYPE_ID, // 846
  SPV_OPERAND_TYPE_ID, // 847
  SPV_OPERAND_TYPE_ID, // 848
  SPV_OPERAND_TYPE_ID, // 849
  SPV_OPERAND_TYPE_ID, // 850
  SPV_OPERAND_TYPE_ID, // 851
  SPV_OPERAND_TYPE_ID, // 852
  SPV_OPERAND_TYPE_VARIABLE_ID, // 853
  SPV_OPERAND_TYPE_ID, // 854
  SPV_OPERAND_TYPE_ID, // 855
  SPV_OPERAND_TYPE_ID, // 856
  SPV_OPERAND_TYPE_ID, // 857
  SPV_OPERAND_TYPE_ID, // 858
  SPV_OPERAND_TYPE_ID, // 859
  SPV_OPERAND_TYPE_ID, // 860
  SPV_OPERAND_TYPE_ID, // 861
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 862
  SPV_OPERAND_TYPE_ID, // 863
  SPV_OPERAND_TYPE_ID, // 864
  SPV_OPERAND_TYPE_ID, // 865
  SPV_OPERAND_TYPE_ID, // 866
  SPV_OPERAND_TYPE_VARIABLE_ID, // 867
  SPV_OPERAND_TYPE_ID, // 868
  SPV_OPERAND_TYPE_ID, // 869
  SPV_OPERAND_TYPE_ID, // 870
  SPV_OPERAND_TYPE_ID, // 871
  SPV_OPERAND_TYPE_ID, // 872
  SPV_OPERAND_TYPE_ID, // 873
  SPV_OPERAND_TYPE_ID, // 874
  SPV_OPERAND_TYPE_ID, // 875
  SPV_OPERAND_TYPE_ID, // 876
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 877
  SPV_OPERAND_TYPE_ID, // 878
  SPV_OPERAND_TYPE_ID, // 879
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 880
  SPV_OPERAND_TYPE_ID, // 881
  SPV_OPERAND_TYPE_ID, // 882
  SPV_OPERAND_TYPE_ID, // 883
  SPV_OPERAND_TYPE_ID, // 884
  SPV_OPERAND_TYPE_ID, // 885
  SPV_OPERAND_TYPE_ID, // 886
  SPV_OPERAND_TYPE_ID, // 887
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 888
  SPV_OPERAND_TYPE_ID, // 889
  SPV_OPERAND_TYPE_ID, // 890
  SPV_OPERAND_TYPE_ID, // 891
  SPV_OPERAND_TYPE_VARIABLE_ID, // 892
  SPV_OPERAND_TYPE_ID, // 893
  SPV_OPERAND_TYPE_ID, // 894
  SPV_OPERAND_TYPE_ID, // 895
  SPV_OPERAND_TYPE_ID, // 896
  SPV_OPERAND_TYPE_ID, // 897
  SPV_OPERAND_TYPE_ID, // 898
  SPV_OPERAND_TYPE_ID, // 899
  SPV_OPERAND_TYPE_ID, // 900
  SPV_OPERAND_TYPE_ID, // 901
  SPV_OPERAND_TYPE_ID, // 902
  SPV_OPERAND_TYPE_ID, // 903
  SPV_OPERAND_TYPE_ID, // 904
  SPV_OPERAND_TYPE_ID, // 905
  SPV_OPERAND_TYPE_ID, // 906
  SPV_OPERAND_TYPE_ID, // 907
  SPV_OPERAND_TYPE_ID, // 908
  SPV_OPERAND_TYPE_ID, // 909
  SPV_OPERAND_TYPE_ID, // 910
  SPV_OPERAND_TYPE_ID, // 911
  SPV_OPERAND_TYPE_ID, // 912
  SPV_OPERAND_TYPE_ID, // 913
  SPV_OPERAND_TYPE_ID, // 914
  SPV_OPERAND_TYPE_ID, // 915
  SPV_OPERAND_TYPE_ID, // 916
  SPV_OPERAND_TYPE_ID, // 917
  SPV_OPERAND_TYPE_ID, // 918
  SPV_OPERAND_TYPE_ID, // 919
  SPV_OPERAND_TYPE_ID, // 920
  SPV_OPERAND_TYPE_ID, // 921
  SPV_OPERAND_TYPE_ID, // 922
  SPV_OPERAND_TYPE_ID, // 923
  SPV_OPERAND_TYPE_ID, // 924
  SPV_OPERAND_TYPE_ID, // 925
  SPV_OPERAND_TYPE_ID, // 926
  SPV_OPERAND_TYPE_ID, // 927
  SPV_OPERAND_TYPE_ID, // 928
  SPV_OPERAND_TYPE_ID, // 929
  SPV_OPERAND_TYPE_ID, // 930
  SPV_OPERAND_TYPE_ID, // 931
  SPV_OPERAND_TYPE_ID, // 932
  SPV_OPERAND_TYPE_ID, // 933
  SPV_OPERAND_TYPE_ID, // 934
  SPV_OPERAND_TYPE_ID, // 935
  SPV_OPERAND_TYPE_ID, // 936
  SPV_OPERAND_TYPE_ID, // 937
  SPV_OPERAND_TYPE_ID, // 938
  SPV_OPERAND_TYPE_ID, // 939
  SPV_OPERAND_TYPE_ID, // 940
  SPV_OPERAND_TYPE_ID, // 941
  SPV_OPERAND_TYPE_ID, // 942
  SPV_OPERAND_TYPE_ID, // 943
  SPV_OPERAND_TYPE_ID, // 944
  SPV_OPERAND_TYPE_ID, // 945
  SPV_OPERAND_TYPE_ID, // 946
  SPV_OPERAND_TYPE_ID, // 947
  SPV_OPERAND_TYPE_ID, // 948
  SPV_OPERAND_TYPE_ID, // 949
  SPV_OPERAND_TYPE_ID, // 950
  SPV_OPERAND_TYPE_ID, // 951
  SPV_OPERAND_TYPE_ID, // 952
  SPV_OPERAND_TYPE_ID, // 953
  SPV_OPERAND_TYPE_ID, // 954
  SPV_OPERAND_TYPE_ID, // 955
  SPV_OPERAND_TYPE_ID, // 956
  SPV_OPERAND_TYPE_ID, // 957
  SPV_OPERAND_TYPE_ID, // 958
  SPV_OPERAND_TYPE_ID, // 959
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 960
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 961
  SPV_OPERAND_TYPE_ID, // 962
  SPV_OPERAND_TYPE_SOURCE_LANGUAGE, // 963
  SPV_OPERAND_TYPE_ID, // 964
  SPV_OPERAND_TYPE_ID, // 965
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING, // 966
  SPV_OPERAND_TYPE_ID, // 967
  SPV_OPERAND_TYPE_STORAGE_CLASS, // 968
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 969
  SPV_OPERAND_TYPE_ID, // 970
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER, // 971
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 972
  SPV_OPERAND_TYPE_ID, // 973
  SPV_OPERAND_TYPE_VARIABLE_ID, // 974
  SPV_OPERAND_TYPE_ID, // 975
  SPV_OPERAND_TYPE_ID, // 976
  SPV_OPERAND_TYPE_ID, // 977
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 978
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 979
  SPV_OPERAND_TYPE_ID, // 980
  SPV_OPERAND_TYPE_ID, // 981
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 982
  SPV_OPERAND_TYPE_VARIABLE_ID, // 983
  SPV_OPERAND_TYPE_ID, // 984
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE, // 985
  SPV_OPERAND_TYPE_ID, // 986
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 987
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 988
  SPV_OPERAND_TYPE_ID, // 989
  SPV_OPERAND_TYPE_ID, // 990
  SPV_OPERAND_TYPE_ID, // 991
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 992
  SPV_OPERAND_TYPE_VARIABLE_ID, // 993
  SPV_OPERAND_TYPE_ID, // 994
  SPV_OPERAND_TYPE_ID, // 995
  SPV_OPERAND_TYPE_ID, // 996
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 997
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 998
  SPV_OPERAND_TYPE_ID, // 999
  SPV_OPERAND_TYPE_ID, // 1000
  SPV_OPERAND_TYPE_ID, // 1001
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1002
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 1003
  SPV_OPERAND_TYPE_ID, // 1004
  SPV_OPERAND_TYPE_ID, // 1005
  SPV_OPERAND_TYPE_ID, // 1006
  SPV_OPERAND_TYPE_ID, // 1007
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1008
  SPV_OPERAND_TYPE_ID, // 1009
  SPV_OPERAND_TYPE_ID, // 1010
  SPV_OPERAND_TYPE_ID, // 1011
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1012
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1013
  SPV_OPERAND_TYPE_ID, // 1014
  SPV_OPERAND_TYPE_ID, // 1015
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1016
  SPV_OPERAND_TYPE_ID, // 1017
  SPV_OPERAND_TYPE_ID, // 1018
  SPV_OPERAND_TYPE_ID, // 1019
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1020
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1021
  SPV_OPERAND_TYPE_ID, // 1022
  SPV_OPERAND_TYPE_ID, // 1023
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1024
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1025
  SPV_OPERAND_TYPE_ID, // 1026
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 1027
  SPV_OPERAND_TYPE_ID, // 1028
  SPV_OPERAND_TYPE_ID, // 1029
  SPV_OPERAND_TYPE_ID, // 1030
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1031
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1032
  SPV_OPERAND_TYPE_ID, // 1033
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1034
  SPV_OPERAND_TYPE_OPTIONAL_LITERAL_INTEGER, // 1035
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION, // 1036
  SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER, // 1037
  SPV_OPERAND_TYPE_ID, // 1038
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY, // 1039
  SPV_OPERAND_TYPE_ID, // 1040
  SPV_OPERAND_TYPE_ID, // 1041
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1042
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1043
  SPV_OPERAND_TYPE_ID, // 1044
  SPV_OPERAND_TYPE_ID, // 1045
  SPV_OPERAND_TYPE_ID, // 1046
  SPV_OPERAND_TYPE_ID, // 1047
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1048
  SPV_OPERAND_TYPE_ID, // 1049
  SPV_OPERAND_TYPE_ID, // 1050
  SPV_OPERAND_TYPE_ID, // 1051
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1052
  SPV_OPERAND_TYPE_ID, // 1053
  SPV_OPERAND_TYPE_ID, // 1054
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1055
  SPV_OPERAND_TYPE_ID, // 1056
  SPV_OPERAND_TYPE_ID, // 1057
  SPV_OPERAND_TYPE_ID, // 1058
  SPV_OPERAND_TYPE_FP_ROUNDING_MODE, // 1059
};
