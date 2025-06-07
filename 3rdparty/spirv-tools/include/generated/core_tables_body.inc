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
    case Extension::kSPV_ARM_tensors: return IR(426, 16);
    case Extension::kSPV_EXT_arithmetic_fence: return IR(442, 25);
    case Extension::kSPV_EXT_demote_to_helper_invocation: return IR(467, 36);
    case Extension::kSPV_EXT_descriptor_indexing: return IR(503, 28);
    case Extension::kSPV_EXT_float8: return IR(531, 15);
    case Extension::kSPV_EXT_fragment_fully_covered: return IR(546, 31);
    case Extension::kSPV_EXT_fragment_invocation_density: return IR(577, 36);
    case Extension::kSPV_EXT_fragment_shader_interlock: return IR(613, 34);
    case Extension::kSPV_EXT_mesh_shader: return IR(647, 20);
    case Extension::kSPV_EXT_opacity_micromap: return IR(667, 25);
    case Extension::kSPV_EXT_optnone: return IR(692, 16);
    case Extension::kSPV_EXT_physical_storage_buffer: return IR(708, 32);
    case Extension::kSPV_EXT_relaxed_printf_string_address_space: return IR(740, 44);
    case Extension::kSPV_EXT_replicated_composites: return IR(784, 30);
    case Extension::kSPV_EXT_shader_atomic_float16_add: return IR(814, 34);
    case Extension::kSPV_EXT_shader_atomic_float_add: return IR(848, 32);
    case Extension::kSPV_EXT_shader_atomic_float_min_max: return IR(880, 36);
    case Extension::kSPV_EXT_shader_image_int64: return IR(916, 27);
    case Extension::kSPV_EXT_shader_stencil_export: return IR(943, 30);
    case Extension::kSPV_EXT_shader_tile_image: return IR(973, 26);
    case Extension::kSPV_EXT_shader_viewport_index_layer: return IR(999, 36);
    case Extension::kSPV_GOOGLE_decorate_string: return IR(1035, 27);
    case Extension::kSPV_GOOGLE_hlsl_functionality1: return IR(1062, 31);
    case Extension::kSPV_GOOGLE_user_type: return IR(1093, 21);
    case Extension::kSPV_INTEL_2d_block_io: return IR(1114, 22);
    case Extension::kSPV_INTEL_arbitrary_precision_fixed_point: return IR(1136, 42);
    case Extension::kSPV_INTEL_arbitrary_precision_floating_point: return IR(1178, 45);
    case Extension::kSPV_INTEL_arbitrary_precision_integers: return IR(1223, 39);
    case Extension::kSPV_INTEL_bfloat16_conversion: return IR(1262, 30);
    case Extension::kSPV_INTEL_bindless_images: return IR(1292, 26);
    case Extension::kSPV_INTEL_blocking_pipes: return IR(1318, 25);
    case Extension::kSPV_INTEL_cache_controls: return IR(1343, 25);
    case Extension::kSPV_INTEL_debug_module: return IR(1368, 23);
    case Extension::kSPV_INTEL_device_side_avc_motion_estimation: return IR(1391, 44);
    case Extension::kSPV_INTEL_float_controls2: return IR(1435, 26);
    case Extension::kSPV_INTEL_fp_fast_math_mode: return IR(1461, 28);
    case Extension::kSPV_INTEL_fp_max_error: return IR(1489, 23);
    case Extension::kSPV_INTEL_fpga_argument_interfaces: return IR(1512, 35);
    case Extension::kSPV_INTEL_fpga_buffer_location: return IR(1547, 31);
    case Extension::kSPV_INTEL_fpga_cluster_attributes: return IR(1578, 34);
    case Extension::kSPV_INTEL_fpga_dsp_control: return IR(1612, 27);
    case Extension::kSPV_INTEL_fpga_invocation_pipelining_attributes: return IR(1639, 48);
    case Extension::kSPV_INTEL_fpga_latency_control: return IR(1687, 31);
    case Extension::kSPV_INTEL_fpga_loop_controls: return IR(1718, 29);
    case Extension::kSPV_INTEL_fpga_memory_accesses: return IR(1747, 31);
    case Extension::kSPV_INTEL_fpga_memory_attributes: return IR(1778, 33);
    case Extension::kSPV_INTEL_fpga_reg: return IR(1811, 19);
    case Extension::kSPV_INTEL_function_pointers: return IR(1830, 28);
    case Extension::kSPV_INTEL_global_variable_fpga_decorations: return IR(1858, 43);
    case Extension::kSPV_INTEL_global_variable_host_access: return IR(1901, 38);
    case Extension::kSPV_INTEL_inline_assembly: return IR(1939, 26);
    case Extension::kSPV_INTEL_int4: return IR(1965, 15);
    case Extension::kSPV_INTEL_io_pipes: return IR(1980, 19);
    case Extension::kSPV_INTEL_kernel_attributes: return IR(1999, 28);
    case Extension::kSPV_INTEL_long_composites: return IR(2027, 26);
    case Extension::kSPV_INTEL_loop_fuse: return IR(2053, 20);
    case Extension::kSPV_INTEL_masked_gather_scatter: return IR(2073, 32);
    case Extension::kSPV_INTEL_maximum_registers: return IR(2105, 28);
    case Extension::kSPV_INTEL_media_block_io: return IR(2133, 25);
    case Extension::kSPV_INTEL_memory_access_aliasing: return IR(2158, 33);
    case Extension::kSPV_INTEL_optnone: return IR(2191, 18);
    case Extension::kSPV_INTEL_runtime_aligned: return IR(2209, 26);
    case Extension::kSPV_INTEL_shader_integer_functions2: return IR(2235, 36);
    case Extension::kSPV_INTEL_split_barrier: return IR(2271, 24);
    case Extension::kSPV_INTEL_subgroup_buffer_prefetch: return IR(2295, 35);
    case Extension::kSPV_INTEL_subgroup_matrix_multiply_accumulate: return IR(2330, 46);
    case Extension::kSPV_INTEL_subgroups: return IR(2376, 20);
    case Extension::kSPV_INTEL_task_sequence: return IR(2396, 24);
    case Extension::kSPV_INTEL_tensor_float32_conversion: return IR(2420, 36);
    case Extension::kSPV_INTEL_ternary_bitwise_function: return IR(2456, 35);
    case Extension::kSPV_INTEL_unstructured_loop_controls: return IR(2491, 37);
    case Extension::kSPV_INTEL_usm_storage_classes: return IR(2528, 30);
    case Extension::kSPV_INTEL_variable_length_array: return IR(2558, 32);
    case Extension::kSPV_INTEL_vector_compute: return IR(2590, 25);
    case Extension::kSPV_KHR_16bit_storage: return IR(2615, 22);
    case Extension::kSPV_KHR_8bit_storage: return IR(2637, 21);
    case Extension::kSPV_KHR_bfloat16: return IR(2658, 17);
    case Extension::kSPV_KHR_bit_instructions: return IR(2675, 25);
    case Extension::kSPV_KHR_compute_shader_derivatives: return IR(2700, 35);
    case Extension::kSPV_KHR_cooperative_matrix: return IR(2735, 27);
    case Extension::kSPV_KHR_device_group: return IR(2762, 21);
    case Extension::kSPV_KHR_expect_assume: return IR(2783, 22);
    case Extension::kSPV_KHR_float_controls: return IR(2805, 23);
    case Extension::kSPV_KHR_float_controls2: return IR(2828, 24);
    case Extension::kSPV_KHR_fragment_shader_barycentric: return IR(2852, 36);
    case Extension::kSPV_KHR_fragment_shading_rate: return IR(2888, 30);
    case Extension::kSPV_KHR_integer_dot_product: return IR(2918, 28);
    case Extension::kSPV_KHR_linkonce_odr: return IR(2946, 21);
    case Extension::kSPV_KHR_maximal_reconvergence: return IR(2967, 30);
    case Extension::kSPV_KHR_multiview: return IR(2997, 18);
    case Extension::kSPV_KHR_no_integer_wrap_decoration: return IR(3015, 35);
    case Extension::kSPV_KHR_non_semantic_info: return IR(3050, 26);
    case Extension::kSPV_KHR_physical_storage_buffer: return IR(3076, 32);
    case Extension::kSPV_KHR_post_depth_coverage: return IR(3108, 28);
    case Extension::kSPV_KHR_quad_control: return IR(3136, 21);
    case Extension::kSPV_KHR_ray_cull_mask: return IR(3157, 22);
    case Extension::kSPV_KHR_ray_query: return IR(3179, 18);
    case Extension::kSPV_KHR_ray_tracing: return IR(3197, 20);
    case Extension::kSPV_KHR_ray_tracing_position_fetch: return IR(3217, 35);
    case Extension::kSPV_KHR_relaxed_extended_instruction: return IR(3252, 37);
    case Extension::kSPV_KHR_shader_atomic_counter_ops: return IR(3289, 34);
    case Extension::kSPV_KHR_shader_ballot: return IR(3323, 22);
    case Extension::kSPV_KHR_shader_clock: return IR(3345, 21);
    case Extension::kSPV_KHR_shader_draw_parameters: return IR(3366, 31);
    case Extension::kSPV_KHR_storage_buffer_storage_class: return IR(3397, 37);
    case Extension::kSPV_KHR_subgroup_rotate: return IR(3434, 24);
    case Extension::kSPV_KHR_subgroup_uniform_control_flow: return IR(3458, 38);
    case Extension::kSPV_KHR_subgroup_vote: return IR(3496, 22);
    case Extension::kSPV_KHR_terminate_invocation: return IR(3518, 29);
    case Extension::kSPV_KHR_uniform_group_instructions: return IR(3547, 35);
    case Extension::kSPV_KHR_untyped_pointers: return IR(3582, 25);
    case Extension::kSPV_KHR_variable_pointers: return IR(3607, 26);
    case Extension::kSPV_KHR_vulkan_memory_model: return IR(3633, 28);
    case Extension::kSPV_KHR_workgroup_memory_explicit_layout: return IR(3661, 41);
    case Extension::kSPV_NVX_multiview_per_view_attributes: return IR(3702, 38);
    case Extension::kSPV_NV_bindless_texture: return IR(3740, 24);
    case Extension::kSPV_NV_cluster_acceleration_structure: return IR(3764, 38);
    case Extension::kSPV_NV_compute_shader_derivatives: return IR(3802, 34);
    case Extension::kSPV_NV_cooperative_matrix: return IR(3836, 26);
    case Extension::kSPV_NV_cooperative_matrix2: return IR(3862, 27);
    case Extension::kSPV_NV_cooperative_vector: return IR(3889, 26);
    case Extension::kSPV_NV_displacement_micromap: return IR(3915, 29);
    case Extension::kSPV_NV_fragment_shader_barycentric: return IR(3944, 35);
    case Extension::kSPV_NV_geometry_shader_passthrough: return IR(3979, 35);
    case Extension::kSPV_NV_linear_swept_spheres: return IR(4014, 28);
    case Extension::kSPV_NV_mesh_shader: return IR(4042, 19);
    case Extension::kSPV_NV_raw_access_chains: return IR(4061, 25);
    case Extension::kSPV_NV_ray_tracing: return IR(4086, 19);
    case Extension::kSPV_NV_ray_tracing_motion_blur: return IR(4105, 31);
    case Extension::kSPV_NV_sample_mask_override_coverage: return IR(4136, 37);
    case Extension::kSPV_NV_shader_atomic_fp16_vector: return IR(4173, 33);
    case Extension::kSPV_NV_shader_image_footprint: return IR(4206, 30);
    case Extension::kSPV_NV_shader_invocation_reorder: return IR(4236, 33);
    case Extension::kSPV_NV_shader_sm_builtins: return IR(4269, 26);
    case Extension::kSPV_NV_shader_subgroup_partitioned: return IR(4295, 35);
    case Extension::kSPV_NV_shading_rate: return IR(4330, 20);
    case Extension::kSPV_NV_stereo_view_rendering: return IR(4350, 29);
    case Extension::kSPV_NV_tensor_addressing: return IR(4379, 25);
    case Extension::kSPV_NV_viewport_array2: return IR(4404, 23);
    case Extension::kSPV_QCOM_image_processing: return IR(4427, 26);
    case Extension::kSPV_QCOM_image_processing2: return IR(4453, 27);
    case Extension::kSPV_QCOM_tile_shading: return IR(4480, 22);
    case Extension::kSPV_VALIDATOR_ignore_type_decl_unique: return IR(4502, 38);
    default: break;
  }
  return {};
}

// Extension names and values, ordered by name
// The fields in order are:
//   name, indexing into kStrings
//   enum value
static const std::array<NameValue,157> kExtensionNames{{
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
    {IR(426, 16), static_cast<uint32_t>(kSPV_ARM_tensors)},
    {IR(442, 25), static_cast<uint32_t>(kSPV_EXT_arithmetic_fence)},
    {IR(467, 36), static_cast<uint32_t>(kSPV_EXT_demote_to_helper_invocation)},
    {IR(503, 28), static_cast<uint32_t>(kSPV_EXT_descriptor_indexing)},
    {IR(531, 15), static_cast<uint32_t>(kSPV_EXT_float8)},
    {IR(546, 31), static_cast<uint32_t>(kSPV_EXT_fragment_fully_covered)},
    {IR(577, 36), static_cast<uint32_t>(kSPV_EXT_fragment_invocation_density)},
    {IR(613, 34), static_cast<uint32_t>(kSPV_EXT_fragment_shader_interlock)},
    {IR(647, 20), static_cast<uint32_t>(kSPV_EXT_mesh_shader)},
    {IR(667, 25), static_cast<uint32_t>(kSPV_EXT_opacity_micromap)},
    {IR(692, 16), static_cast<uint32_t>(kSPV_EXT_optnone)},
    {IR(708, 32), static_cast<uint32_t>(kSPV_EXT_physical_storage_buffer)},
    {IR(740, 44), static_cast<uint32_t>(kSPV_EXT_relaxed_printf_string_address_space)},
    {IR(784, 30), static_cast<uint32_t>(kSPV_EXT_replicated_composites)},
    {IR(814, 34), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float16_add)},
    {IR(848, 32), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float_add)},
    {IR(880, 36), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float_min_max)},
    {IR(916, 27), static_cast<uint32_t>(kSPV_EXT_shader_image_int64)},
    {IR(943, 30), static_cast<uint32_t>(kSPV_EXT_shader_stencil_export)},
    {IR(973, 26), static_cast<uint32_t>(kSPV_EXT_shader_tile_image)},
    {IR(999, 36), static_cast<uint32_t>(kSPV_EXT_shader_viewport_index_layer)},
    {IR(1035, 27), static_cast<uint32_t>(kSPV_GOOGLE_decorate_string)},
    {IR(1062, 31), static_cast<uint32_t>(kSPV_GOOGLE_hlsl_functionality1)},
    {IR(1093, 21), static_cast<uint32_t>(kSPV_GOOGLE_user_type)},
    {IR(1114, 22), static_cast<uint32_t>(kSPV_INTEL_2d_block_io)},
    {IR(1136, 42), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_fixed_point)},
    {IR(1178, 45), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_floating_point)},
    {IR(1223, 39), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_integers)},
    {IR(1262, 30), static_cast<uint32_t>(kSPV_INTEL_bfloat16_conversion)},
    {IR(1292, 26), static_cast<uint32_t>(kSPV_INTEL_bindless_images)},
    {IR(1318, 25), static_cast<uint32_t>(kSPV_INTEL_blocking_pipes)},
    {IR(1343, 25), static_cast<uint32_t>(kSPV_INTEL_cache_controls)},
    {IR(1368, 23), static_cast<uint32_t>(kSPV_INTEL_debug_module)},
    {IR(1391, 44), static_cast<uint32_t>(kSPV_INTEL_device_side_avc_motion_estimation)},
    {IR(1435, 26), static_cast<uint32_t>(kSPV_INTEL_float_controls2)},
    {IR(1461, 28), static_cast<uint32_t>(kSPV_INTEL_fp_fast_math_mode)},
    {IR(1489, 23), static_cast<uint32_t>(kSPV_INTEL_fp_max_error)},
    {IR(1512, 35), static_cast<uint32_t>(kSPV_INTEL_fpga_argument_interfaces)},
    {IR(1547, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_buffer_location)},
    {IR(1578, 34), static_cast<uint32_t>(kSPV_INTEL_fpga_cluster_attributes)},
    {IR(1612, 27), static_cast<uint32_t>(kSPV_INTEL_fpga_dsp_control)},
    {IR(1639, 48), static_cast<uint32_t>(kSPV_INTEL_fpga_invocation_pipelining_attributes)},
    {IR(1687, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_latency_control)},
    {IR(1718, 29), static_cast<uint32_t>(kSPV_INTEL_fpga_loop_controls)},
    {IR(1747, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_memory_accesses)},
    {IR(1778, 33), static_cast<uint32_t>(kSPV_INTEL_fpga_memory_attributes)},
    {IR(1811, 19), static_cast<uint32_t>(kSPV_INTEL_fpga_reg)},
    {IR(1830, 28), static_cast<uint32_t>(kSPV_INTEL_function_pointers)},
    {IR(1858, 43), static_cast<uint32_t>(kSPV_INTEL_global_variable_fpga_decorations)},
    {IR(1901, 38), static_cast<uint32_t>(kSPV_INTEL_global_variable_host_access)},
    {IR(1939, 26), static_cast<uint32_t>(kSPV_INTEL_inline_assembly)},
    {IR(1965, 15), static_cast<uint32_t>(kSPV_INTEL_int4)},
    {IR(1980, 19), static_cast<uint32_t>(kSPV_INTEL_io_pipes)},
    {IR(1999, 28), static_cast<uint32_t>(kSPV_INTEL_kernel_attributes)},
    {IR(2027, 26), static_cast<uint32_t>(kSPV_INTEL_long_composites)},
    {IR(2053, 20), static_cast<uint32_t>(kSPV_INTEL_loop_fuse)},
    {IR(2073, 32), static_cast<uint32_t>(kSPV_INTEL_masked_gather_scatter)},
    {IR(2105, 28), static_cast<uint32_t>(kSPV_INTEL_maximum_registers)},
    {IR(2133, 25), static_cast<uint32_t>(kSPV_INTEL_media_block_io)},
    {IR(2158, 33), static_cast<uint32_t>(kSPV_INTEL_memory_access_aliasing)},
    {IR(2191, 18), static_cast<uint32_t>(kSPV_INTEL_optnone)},
    {IR(2209, 26), static_cast<uint32_t>(kSPV_INTEL_runtime_aligned)},
    {IR(2235, 36), static_cast<uint32_t>(kSPV_INTEL_shader_integer_functions2)},
    {IR(2271, 24), static_cast<uint32_t>(kSPV_INTEL_split_barrier)},
    {IR(2295, 35), static_cast<uint32_t>(kSPV_INTEL_subgroup_buffer_prefetch)},
    {IR(2330, 46), static_cast<uint32_t>(kSPV_INTEL_subgroup_matrix_multiply_accumulate)},
    {IR(2376, 20), static_cast<uint32_t>(kSPV_INTEL_subgroups)},
    {IR(2396, 24), static_cast<uint32_t>(kSPV_INTEL_task_sequence)},
    {IR(2420, 36), static_cast<uint32_t>(kSPV_INTEL_tensor_float32_conversion)},
    {IR(2456, 35), static_cast<uint32_t>(kSPV_INTEL_ternary_bitwise_function)},
    {IR(2491, 37), static_cast<uint32_t>(kSPV_INTEL_unstructured_loop_controls)},
    {IR(2528, 30), static_cast<uint32_t>(kSPV_INTEL_usm_storage_classes)},
    {IR(2558, 32), static_cast<uint32_t>(kSPV_INTEL_variable_length_array)},
    {IR(2590, 25), static_cast<uint32_t>(kSPV_INTEL_vector_compute)},
    {IR(2615, 22), static_cast<uint32_t>(kSPV_KHR_16bit_storage)},
    {IR(2637, 21), static_cast<uint32_t>(kSPV_KHR_8bit_storage)},
    {IR(2658, 17), static_cast<uint32_t>(kSPV_KHR_bfloat16)},
    {IR(2675, 25), static_cast<uint32_t>(kSPV_KHR_bit_instructions)},
    {IR(2700, 35), static_cast<uint32_t>(kSPV_KHR_compute_shader_derivatives)},
    {IR(2735, 27), static_cast<uint32_t>(kSPV_KHR_cooperative_matrix)},
    {IR(2762, 21), static_cast<uint32_t>(kSPV_KHR_device_group)},
    {IR(2783, 22), static_cast<uint32_t>(kSPV_KHR_expect_assume)},
    {IR(2805, 23), static_cast<uint32_t>(kSPV_KHR_float_controls)},
    {IR(2828, 24), static_cast<uint32_t>(kSPV_KHR_float_controls2)},
    {IR(2852, 36), static_cast<uint32_t>(kSPV_KHR_fragment_shader_barycentric)},
    {IR(2888, 30), static_cast<uint32_t>(kSPV_KHR_fragment_shading_rate)},
    {IR(2918, 28), static_cast<uint32_t>(kSPV_KHR_integer_dot_product)},
    {IR(2946, 21), static_cast<uint32_t>(kSPV_KHR_linkonce_odr)},
    {IR(2967, 30), static_cast<uint32_t>(kSPV_KHR_maximal_reconvergence)},
    {IR(2997, 18), static_cast<uint32_t>(kSPV_KHR_multiview)},
    {IR(3015, 35), static_cast<uint32_t>(kSPV_KHR_no_integer_wrap_decoration)},
    {IR(3050, 26), static_cast<uint32_t>(kSPV_KHR_non_semantic_info)},
    {IR(3076, 32), static_cast<uint32_t>(kSPV_KHR_physical_storage_buffer)},
    {IR(3108, 28), static_cast<uint32_t>(kSPV_KHR_post_depth_coverage)},
    {IR(3136, 21), static_cast<uint32_t>(kSPV_KHR_quad_control)},
    {IR(3157, 22), static_cast<uint32_t>(kSPV_KHR_ray_cull_mask)},
    {IR(3179, 18), static_cast<uint32_t>(kSPV_KHR_ray_query)},
    {IR(3197, 20), static_cast<uint32_t>(kSPV_KHR_ray_tracing)},
    {IR(3217, 35), static_cast<uint32_t>(kSPV_KHR_ray_tracing_position_fetch)},
    {IR(3252, 37), static_cast<uint32_t>(kSPV_KHR_relaxed_extended_instruction)},
    {IR(3289, 34), static_cast<uint32_t>(kSPV_KHR_shader_atomic_counter_ops)},
    {IR(3323, 22), static_cast<uint32_t>(kSPV_KHR_shader_ballot)},
    {IR(3345, 21), static_cast<uint32_t>(kSPV_KHR_shader_clock)},
    {IR(3366, 31), static_cast<uint32_t>(kSPV_KHR_shader_draw_parameters)},
    {IR(3397, 37), static_cast<uint32_t>(kSPV_KHR_storage_buffer_storage_class)},
    {IR(3434, 24), static_cast<uint32_t>(kSPV_KHR_subgroup_rotate)},
    {IR(3458, 38), static_cast<uint32_t>(kSPV_KHR_subgroup_uniform_control_flow)},
    {IR(3496, 22), static_cast<uint32_t>(kSPV_KHR_subgroup_vote)},
    {IR(3518, 29), static_cast<uint32_t>(kSPV_KHR_terminate_invocation)},
    {IR(3547, 35), static_cast<uint32_t>(kSPV_KHR_uniform_group_instructions)},
    {IR(3582, 25), static_cast<uint32_t>(kSPV_KHR_untyped_pointers)},
    {IR(3607, 26), static_cast<uint32_t>(kSPV_KHR_variable_pointers)},
    {IR(3633, 28), static_cast<uint32_t>(kSPV_KHR_vulkan_memory_model)},
    {IR(3661, 41), static_cast<uint32_t>(kSPV_KHR_workgroup_memory_explicit_layout)},
    {IR(3702, 38), static_cast<uint32_t>(kSPV_NVX_multiview_per_view_attributes)},
    {IR(3740, 24), static_cast<uint32_t>(kSPV_NV_bindless_texture)},
    {IR(3764, 38), static_cast<uint32_t>(kSPV_NV_cluster_acceleration_structure)},
    {IR(3802, 34), static_cast<uint32_t>(kSPV_NV_compute_shader_derivatives)},
    {IR(3836, 26), static_cast<uint32_t>(kSPV_NV_cooperative_matrix)},
    {IR(3862, 27), static_cast<uint32_t>(kSPV_NV_cooperative_matrix2)},
    {IR(3889, 26), static_cast<uint32_t>(kSPV_NV_cooperative_vector)},
    {IR(3915, 29), static_cast<uint32_t>(kSPV_NV_displacement_micromap)},
    {IR(3944, 35), static_cast<uint32_t>(kSPV_NV_fragment_shader_barycentric)},
    {IR(3979, 35), static_cast<uint32_t>(kSPV_NV_geometry_shader_passthrough)},
    {IR(4014, 28), static_cast<uint32_t>(kSPV_NV_linear_swept_spheres)},
    {IR(4042, 19), static_cast<uint32_t>(kSPV_NV_mesh_shader)},
    {IR(4061, 25), static_cast<uint32_t>(kSPV_NV_raw_access_chains)},
    {IR(4086, 19), static_cast<uint32_t>(kSPV_NV_ray_tracing)},
    {IR(4105, 31), static_cast<uint32_t>(kSPV_NV_ray_tracing_motion_blur)},
    {IR(4136, 37), static_cast<uint32_t>(kSPV_NV_sample_mask_override_coverage)},
    {IR(4173, 33), static_cast<uint32_t>(kSPV_NV_shader_atomic_fp16_vector)},
    {IR(4206, 30), static_cast<uint32_t>(kSPV_NV_shader_image_footprint)},
    {IR(4236, 33), static_cast<uint32_t>(kSPV_NV_shader_invocation_reorder)},
    {IR(4269, 26), static_cast<uint32_t>(kSPV_NV_shader_sm_builtins)},
    {IR(4295, 35), static_cast<uint32_t>(kSPV_NV_shader_subgroup_partitioned)},
    {IR(4330, 20), static_cast<uint32_t>(kSPV_NV_shading_rate)},
    {IR(4350, 29), static_cast<uint32_t>(kSPV_NV_stereo_view_rendering)},
    {IR(4379, 25), static_cast<uint32_t>(kSPV_NV_tensor_addressing)},
    {IR(4404, 23), static_cast<uint32_t>(kSPV_NV_viewport_array2)},
    {IR(4427, 26), static_cast<uint32_t>(kSPV_QCOM_image_processing)},
    {IR(4453, 27), static_cast<uint32_t>(kSPV_QCOM_image_processing2)},
    {IR(4480, 22), static_cast<uint32_t>(kSPV_QCOM_tile_shading)},
    {IR(4502, 38), static_cast<uint32_t>(kSPV_VALIDATOR_ignore_type_decl_unique)},
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
static const std::array<OperandDesc, 1182> kOperandsByValue{{
  {0,IR(0, 0),IR(4540, 9)/* ReadOnly */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {1,IR(0, 0),IR(4556, 10)/* WriteOnly */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {2,IR(0, 0),IR(4566, 10)/* ReadWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {0,IR(0, 0),IR(4576, 8)/* Logical */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {1,IR(0, 0),IR(4584, 11)/* Physical32 */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {2,IR(0, 0),IR(4605, 11)/* Physical64 */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {5348,IR(0, 0),IR(4616, 24)/* PhysicalStorageBuffer64 */,IR(0, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {0,IR(0, 0),IR(4698, 9)/* Position */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {1,IR(0, 0),IR(4714, 10)/* PointSize */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {3,IR(0, 0),IR(4724, 13)/* ClipDistance */,IR(0, 0),IR(4, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4,IR(0, 0),IR(4737, 13)/* CullDistance */,IR(0, 0),IR(5, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5,IR(0, 0),IR(4750, 9)/* VertexId */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {6,IR(0, 0),IR(4759, 11)/* InstanceId */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {7,IR(0, 0),IR(4770, 12)/* PrimitiveId */,IR(0, 0),IR(6, 6),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {8,IR(0, 0),IR(4860, 13)/* InvocationId */,IR(0, 0),IR(12, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {9,IR(0, 0),IR(4873, 6)/* Layer */,IR(0, 0),IR(14, 5),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {10,IR(0, 0),IR(4919, 14)/* ViewportIndex */,IR(0, 0),IR(19, 5),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {11,IR(0, 0),IR(4967, 15)/* TessLevelOuter */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {12,IR(0, 0),IR(4982, 15)/* TessLevelInner */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {13,IR(0, 0),IR(4997, 10)/* TessCoord */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {14,IR(0, 0),IR(5007, 14)/* PatchVertices */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {15,IR(0, 0),IR(5021, 10)/* FragCoord */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {16,IR(0, 0),IR(5031, 11)/* PointCoord */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {17,IR(0, 0),IR(5042, 12)/* FrontFacing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {18,IR(0, 0),IR(5054, 9)/* SampleId */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {19,IR(0, 0),IR(5081, 15)/* SamplePosition */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {20,IR(0, 0),IR(5096, 11)/* SampleMask */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {22,IR(0, 0),IR(5107, 10)/* FragDepth */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {23,IR(0, 0),IR(5117, 17)/* HelperInvocation */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {24,IR(0, 0),IR(5134, 14)/* NumWorkgroups */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {25,IR(0, 0),IR(5148, 14)/* WorkgroupSize */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {26,IR(0, 0),IR(5162, 12)/* WorkgroupId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {27,IR(0, 0),IR(5174, 18)/* LocalInvocationId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {28,IR(0, 0),IR(5192, 19)/* GlobalInvocationId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {29,IR(0, 0),IR(5211, 21)/* LocalInvocationIndex */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {30,IR(0, 0),IR(5232, 8)/* WorkDim */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {31,IR(0, 0),IR(5240, 11)/* GlobalSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {32,IR(0, 0),IR(5251, 22)/* EnqueuedWorkgroupSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {33,IR(0, 0),IR(5273, 13)/* GlobalOffset */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {34,IR(0, 0),IR(5286, 15)/* GlobalLinearId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {36,IR(0, 0),IR(5301, 13)/* SubgroupSize */,IR(0, 0),IR(26, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {37,IR(0, 0),IR(5348, 16)/* SubgroupMaxSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {38,IR(0, 0),IR(5364, 13)/* NumSubgroups */,IR(0, 0),IR(29, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {39,IR(0, 0),IR(5377, 21)/* NumEnqueuedSubgroups */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {40,IR(0, 0),IR(5398, 11)/* SubgroupId */,IR(0, 0),IR(29, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {41,IR(0, 0),IR(5409, 26)/* SubgroupLocalInvocationId */,IR(0, 0),IR(26, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {42,IR(0, 0),IR(5435, 12)/* VertexIndex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {43,IR(0, 0),IR(5447, 14)/* InstanceIndex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4160,IR(0, 0),IR(5461, 10)/* CoreIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4161,IR(0, 0),IR(5487, 13)/* CoreCountARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4162,IR(0, 0),IR(5500, 13)/* CoreMaxIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4163,IR(0, 0),IR(5513, 10)/* WarpIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4164,IR(0, 0),IR(5523, 13)/* WarpMaxIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4416,IR(0, 0),IR(5536, 15)/* SubgroupEqMask */,IR(1, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4417,IR(0, 0),IR(5591, 15)/* SubgroupGeMask */,IR(2, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4418,IR(0, 0),IR(5624, 15)/* SubgroupGtMask */,IR(3, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4419,IR(0, 0),IR(5657, 15)/* SubgroupLeMask */,IR(4, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4420,IR(0, 0),IR(5690, 15)/* SubgroupLtMask */,IR(5, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4424,IR(0, 0),IR(5723, 11)/* BaseVertex */,IR(0, 0),IR(34, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4425,IR(0, 0),IR(5749, 13)/* BaseInstance */,IR(0, 0),IR(34, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4426,IR(0, 0),IR(5762, 10)/* DrawIndex */,IR(0, 0),IR(35, 3),IR(4, 3),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4432,IR(0, 0),IR(5772, 24)/* PrimitiveShadingRateKHR */,IR(0, 0),IR(38, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4438,IR(0, 0),IR(5819, 12)/* DeviceIndex */,IR(0, 0),IR(39, 1),IR(8, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4440,IR(0, 0),IR(5843, 10)/* ViewIndex */,IR(0, 0),IR(40, 1),IR(9, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4444,IR(0, 0),IR(5863, 15)/* ShadingRateKHR */,IR(0, 0),IR(38, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4492,IR(0, 0),IR(5878, 15)/* TileOffsetQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4493,IR(0, 0),IR(5909, 18)/* TileDimensionQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4494,IR(0, 0),IR(5927, 18)/* TileApronSizeQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4992,IR(0, 0),IR(5945, 20)/* BaryCoordNoPerspAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4993,IR(0, 0),IR(5965, 28)/* BaryCoordNoPerspCentroidAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4994,IR(0, 0),IR(5993, 26)/* BaryCoordNoPerspSampleAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4995,IR(0, 0),IR(6019, 19)/* BaryCoordSmoothAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4996,IR(0, 0),IR(6038, 27)/* BaryCoordSmoothCentroidAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4997,IR(0, 0),IR(6065, 25)/* BaryCoordSmoothSampleAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4998,IR(0, 0),IR(6090, 22)/* BaryCoordPullModelAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5014,IR(0, 0),IR(6112, 18)/* FragStencilRefEXT */,IR(0, 0),IR(42, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5021,IR(0, 0),IR(6147, 29)/* RemainingRecursionLevelsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5073,IR(0, 0),IR(6194, 16)/* ShaderIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5253,IR(0, 0),IR(6210, 15)/* ViewportMaskNV */,IR(0, 0),IR(44, 2),IR(12, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5257,IR(0, 0),IR(6246, 20)/* SecondaryPositionNV */,IR(0, 0),IR(46, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5258,IR(0, 0),IR(6285, 24)/* SecondaryViewportMaskNV */,IR(0, 0),IR(46, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5261,IR(0, 0),IR(6309, 18)/* PositionPerViewNV */,IR(0, 0),IR(47, 2),IR(15, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5262,IR(0, 0),IR(6347, 22)/* ViewportMaskPerViewNV */,IR(0, 0),IR(47, 2),IR(15, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5264,IR(0, 0),IR(6369, 16)/* FullyCoveredEXT */,IR(0, 0),IR(49, 1),IR(17, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5274,IR(0, 0),IR(6409, 12)/* TaskCountNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5275,IR(0, 0),IR(6421, 17)/* PrimitiveCountNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5276,IR(0, 0),IR(6438, 19)/* PrimitiveIndicesNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5277,IR(0, 0),IR(6457, 22)/* ClipDistancePerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5278,IR(0, 0),IR(6479, 22)/* CullDistancePerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5279,IR(0, 0),IR(6501, 15)/* LayerPerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5280,IR(0, 0),IR(6516, 16)/* MeshViewCountNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5281,IR(0, 0),IR(6532, 18)/* MeshViewIndicesNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5286,IR(0, 0),IR(6550, 13)/* BaryCoordKHR */,IR(6, 1),IR(51, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5287,IR(0, 0),IR(6598, 20)/* BaryCoordNoPerspKHR */,IR(7, 1),IR(51, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5292,IR(0, 0),IR(6637, 12)/* FragSizeEXT */,IR(8, 1),IR(52, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5293,IR(0, 0),IR(6683, 23)/* FragInvocationCountEXT */,IR(9, 1),IR(52, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5294,IR(0, 0),IR(6728, 25)/* PrimitivePointIndicesEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5295,IR(0, 0),IR(6753, 24)/* PrimitiveLineIndicesEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5296,IR(0, 0),IR(6777, 28)/* PrimitiveTriangleIndicesEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5299,IR(0, 0),IR(6805, 17)/* CullPrimitiveEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5319,IR(0, 0),IR(6822, 12)/* LaunchIdKHR */,IR(10, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5320,IR(0, 0),IR(6845, 14)/* LaunchSizeKHR */,IR(11, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5321,IR(0, 0),IR(6872, 18)/* WorldRayOriginKHR */,IR(12, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5322,IR(0, 0),IR(6907, 21)/* WorldRayDirectionKHR */,IR(13, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5323,IR(0, 0),IR(6948, 19)/* ObjectRayOriginKHR */,IR(14, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5324,IR(0, 0),IR(6985, 22)/* ObjectRayDirectionKHR */,IR(15, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5325,IR(0, 0),IR(7028, 11)/* RayTminKHR */,IR(16, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5326,IR(0, 0),IR(7049, 11)/* RayTmaxKHR */,IR(17, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5327,IR(0, 0),IR(7070, 23)/* InstanceCustomIndexKHR */,IR(18, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5330,IR(0, 0),IR(7115, 17)/* ObjectToWorldKHR */,IR(19, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5331,IR(0, 0),IR(7148, 17)/* WorldToObjectKHR */,IR(20, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5332,IR(0, 0),IR(7181, 7)/* HitTNV */,IR(0, 0),IR(56, 1),IR(26, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5333,IR(0, 0),IR(7188, 11)/* HitKindKHR */,IR(21, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5334,IR(0, 0),IR(7209, 17)/* CurrentRayTimeNV */,IR(0, 0),IR(57, 1),IR(27, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5335,IR(0, 0),IR(7249, 30)/* HitTriangleVertexPositionsKHR */,IR(0, 0),IR(58, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5337,IR(0, 0),IR(7306, 34)/* HitMicroTriangleVertexPositionsNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5344,IR(0, 0),IR(7373, 37)/* HitMicroTriangleVertexBarycentricsNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5351,IR(0, 0),IR(7410, 20)/* IncomingRayFlagsKHR */,IR(22, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5352,IR(0, 0),IR(7449, 20)/* RayGeometryIndexKHR */,IR(0, 0),IR(60, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5359,IR(0, 0),IR(7469, 14)/* HitIsSphereNV */,IR(0, 0),IR(61, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5360,IR(0, 0),IR(7511, 11)/* HitIsLSSNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5361,IR(0, 0),IR(7561, 20)/* HitSpherePositionNV */,IR(0, 0),IR(61, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5374,IR(0, 0),IR(7581, 13)/* WarpsPerSMNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5375,IR(0, 0),IR(7613, 10)/* SMCountNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5376,IR(0, 0),IR(7623, 9)/* WarpIDNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5377,IR(0, 0),IR(7632, 7)/* SMIDNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5396,IR(0, 0),IR(7639, 18)/* HitLSSPositionsNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5405,IR(0, 0),IR(7657, 34)/* HitKindFrontFacingMicroTriangleNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5406,IR(0, 0),IR(7691, 33)/* HitKindBackFacingMicroTriangleNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5420,IR(0, 0),IR(7724, 18)/* HitSphereRadiusNV */,IR(0, 0),IR(61, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5421,IR(0, 0),IR(7742, 14)/* HitLSSRadiiNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5436,IR(0, 0),IR(7756, 12)/* ClusterIDNV */,IR(0, 0),IR(64, 1),IR(31, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {6021,IR(0, 0),IR(7809, 12)/* CullMaskKHR */,IR(0, 0),IR(65, 1),IR(32, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {0,IR(0, 0),IR(7836, 7)/* Matrix */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {1,IR(0, 0),IR(4707, 7)/* Shader */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {2,IR(0, 0),IR(4782, 9)/* Geometry */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {3,IR(0, 0),IR(4791, 13)/* Tessellation */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4,IR(0, 0),IR(4595, 10)/* Addresses */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5,IR(0, 0),IR(7843, 8)/* Linkage */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6,IR(0, 0),IR(4549, 7)/* Kernel */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {7,IR(0, 0),IR(7851, 9)/* Vector16 */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {8,IR(0, 0),IR(7860, 14)/* Float16Buffer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {9,IR(0, 0),IR(7874, 8)/* Float16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {10,IR(0, 0),IR(7882, 8)/* Float64 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {11,IR(0, 0),IR(7890, 6)/* Int64 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {12,IR(0, 0),IR(7896, 13)/* Int64Atomics */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {13,IR(0, 0),IR(7909, 11)/* ImageBasic */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {14,IR(0, 0),IR(7920, 15)/* ImageReadWrite */,IR(0, 0),IR(68, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {15,IR(0, 0),IR(7935, 12)/* ImageMipmap */,IR(0, 0),IR(68, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {17,IR(0, 0),IR(7947, 6)/* Pipes */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {18,IR(0, 0),IR(7953, 7)/* Groups */,IR(0, 0),IR(1, 0),IR(33, 1),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {19,IR(0, 0),IR(7960, 14)/* DeviceEnqueue */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {20,IR(0, 0),IR(7974, 15)/* LiteralSampler */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {21,IR(0, 0),IR(7989, 14)/* AtomicStorage */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {22,IR(0, 0),IR(8003, 6)/* Int16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {23,IR(0, 0),IR(8009, 22)/* TessellationPointSize */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {24,IR(0, 0),IR(8031, 18)/* GeometryPointSize */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {25,IR(0, 0),IR(8049, 20)/* ImageGatherExtended */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {27,IR(0, 0),IR(8069, 24)/* StorageImageMultisample */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {28,IR(0, 0),IR(8093, 34)/* UniformBufferArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {29,IR(0, 0),IR(8127, 33)/* SampledImageArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {30,IR(0, 0),IR(8160, 34)/* StorageBufferArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {31,IR(0, 0),IR(8194, 33)/* StorageImageArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {32,IR(0, 0),IR(4724, 13)/* ClipDistance */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {33,IR(0, 0),IR(4737, 13)/* CullDistance */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {34,IR(0, 0),IR(8227, 15)/* ImageCubeArray */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {35,IR(0, 0),IR(5063, 18)/* SampleRateShading */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {36,IR(0, 0),IR(8259, 10)/* ImageRect */,IR(0, 0),IR(71, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {37,IR(0, 0),IR(8269, 12)/* SampledRect */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {38,IR(0, 0),IR(8281, 15)/* GenericPointer */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {39,IR(0, 0),IR(8296, 5)/* Int8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {40,IR(0, 0),IR(8301, 16)/* InputAttachment */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {41,IR(0, 0),IR(8317, 16)/* SparseResidency */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {42,IR(0, 0),IR(8333, 7)/* MinLod */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {43,IR(0, 0),IR(8340, 10)/* Sampled1D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {44,IR(0, 0),IR(8350, 8)/* Image1D */,IR(0, 0),IR(72, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {45,IR(0, 0),IR(8242, 17)/* SampledCubeArray */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {46,IR(0, 0),IR(8358, 14)/* SampledBuffer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {47,IR(0, 0),IR(8372, 12)/* ImageBuffer */,IR(0, 0),IR(73, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {48,IR(0, 0),IR(8384, 13)/* ImageMSArray */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {49,IR(0, 0),IR(8397, 28)/* StorageImageExtendedFormats */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {50,IR(0, 0),IR(8425, 11)/* ImageQuery */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {51,IR(0, 0),IR(8436, 18)/* DerivativeControl */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {52,IR(0, 0),IR(8454, 22)/* InterpolationFunction */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {53,IR(0, 0),IR(8476, 18)/* TransformFeedback */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {54,IR(0, 0),IR(8494, 16)/* GeometryStreams */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {55,IR(0, 0),IR(8510, 30)/* StorageImageReadWithoutFormat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {56,IR(0, 0),IR(8540, 31)/* StorageImageWriteWithoutFormat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {57,IR(0, 0),IR(4933, 14)/* MultiViewport */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {58,IR(0, 0),IR(8571, 17)/* SubgroupDispatch */,IR(0, 0),IR(74, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {59,IR(0, 0),IR(8588, 13)/* NamedBarrier */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {60,IR(0, 0),IR(8601, 12)/* PipeStorage */,IR(0, 0),IR(75, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {61,IR(0, 0),IR(5314, 16)/* GroupNonUniform */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {62,IR(0, 0),IR(8613, 20)/* GroupNonUniformVote */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {63,IR(0, 0),IR(8633, 26)/* GroupNonUniformArithmetic */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {64,IR(0, 0),IR(5569, 22)/* GroupNonUniformBallot */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {65,IR(0, 0),IR(8659, 23)/* GroupNonUniformShuffle */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {66,IR(0, 0),IR(8682, 31)/* GroupNonUniformShuffleRelative */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {67,IR(0, 0),IR(8713, 25)/* GroupNonUniformClustered */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {68,IR(0, 0),IR(8738, 20)/* GroupNonUniformQuad */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {69,IR(0, 0),IR(4879, 12)/* ShaderLayer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {70,IR(0, 0),IR(4947, 20)/* ShaderViewportIndex */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {71,IR(0, 0),IR(8758, 18)/* UniformDecoration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4165,IR(0, 0),IR(5471, 16)/* CoreBuiltinsARM */,IR(0, 0),IR(1, 0),IR(34, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4166,IR(0, 0),IR(8776, 28)/* TileImageColorReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4167,IR(0, 0),IR(8804, 28)/* TileImageDepthReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4168,IR(0, 0),IR(8832, 30)/* TileImageStencilReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4174,IR(0, 0),IR(8862, 11)/* TensorsARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4175,IR(0, 0),IR(8873, 37)/* StorageTensorArrayDynamicIndexingARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4176,IR(0, 0),IR(8910, 40)/* StorageTensorArrayNonUniformIndexingARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4201,IR(0, 0),IR(8950, 28)/* CooperativeMatrixLayoutsARM */,IR(0, 0),IR(1, 0),IR(37, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4212,IR(0, 0),IR(8978, 10)/* Float8EXT */,IR(0, 0),IR(1, 0),IR(38, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4213,IR(0, 0),IR(8988, 27)/* Float8CooperativeMatrixEXT */,IR(0, 0),IR(1, 0),IR(38, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4422,IR(0, 0),IR(5796, 23)/* FragmentShadingRateKHR */,IR(0, 0),IR(3, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4423,IR(0, 0),IR(5330, 18)/* SubgroupBallotKHR */,IR(0, 0),IR(1, 0),IR(2, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4427,IR(0, 0),IR(5734, 15)/* DrawParameters */,IR(0, 0),IR(3, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4428,IR(0, 0),IR(9015, 33)/* WorkgroupMemoryExplicitLayoutKHR */,IR(0, 0),IR(3, 1),IR(39, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4429,IR(0, 0),IR(9048, 43)/* WorkgroupMemoryExplicitLayout8BitAccessKHR */,IR(0, 0),IR(77, 1),IR(39, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4430,IR(0, 0),IR(9091, 44)/* WorkgroupMemoryExplicitLayout16BitAccessKHR */,IR(0, 0),IR(77, 1),IR(39, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4431,IR(0, 0),IR(9135, 16)/* SubgroupVoteKHR */,IR(0, 0),IR(1, 0),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4433,IR(0, 0),IR(9151, 25)/* StorageBuffer16BitAccess */,IR(23, 1),IR(1, 0),IR(41, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4434,IR(0, 0),IR(9204, 35)/* UniformAndStorageBuffer16BitAccess */,IR(24, 1),IR(78, 1),IR(41, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4435,IR(0, 0),IR(9256, 22)/* StoragePushConstant16 */,IR(0, 0),IR(1, 0),IR(41, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4436,IR(0, 0),IR(9278, 21)/* StorageInputOutput16 */,IR(0, 0),IR(1, 0),IR(41, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4437,IR(0, 0),IR(5831, 12)/* DeviceGroup */,IR(0, 0),IR(1, 0),IR(8, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4439,IR(0, 0),IR(5853, 10)/* MultiView */,IR(0, 0),IR(3, 1),IR(9, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4441,IR(0, 0),IR(9299, 30)/* VariablePointersStorageBuffer */,IR(0, 0),IR(3, 1),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4442,IR(0, 0),IR(9329, 17)/* VariablePointers */,IR(0, 0),IR(79, 1),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4445,IR(0, 0),IR(9346, 17)/* AtomicStorageOps */,IR(0, 0),IR(80, 1),IR(43, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4447,IR(0, 0),IR(9363, 28)/* SampleMaskPostDepthCoverage */,IR(0, 0),IR(1, 0),IR(44, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4448,IR(0, 0),IR(9391, 24)/* StorageBuffer8BitAccess */,IR(0, 0),IR(1, 0),IR(45, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4449,IR(0, 0),IR(9415, 34)/* UniformAndStorageBuffer8BitAccess */,IR(0, 0),IR(81, 1),IR(45, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4450,IR(0, 0),IR(9449, 21)/* StoragePushConstant8 */,IR(0, 0),IR(1, 0),IR(45, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4464,IR(0, 0),IR(9470, 15)/* DenormPreserve */,IR(0, 0),IR(1, 0),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4465,IR(0, 0),IR(9485, 18)/* DenormFlushToZero */,IR(0, 0),IR(1, 0),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4466,IR(0, 0),IR(9503, 25)/* SignedZeroInfNanPreserve */,IR(0, 0),IR(1, 0),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4467,IR(0, 0),IR(9528, 16)/* RoundingModeRTE */,IR(0, 0),IR(1, 0),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4468,IR(0, 0),IR(9544, 16)/* RoundingModeRTZ */,IR(0, 0),IR(1, 0),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4471,IR(0, 0),IR(9560, 23)/* RayQueryProvisionalKHR */,IR(0, 0),IR(3, 1),IR(47, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4472,IR(0, 0),IR(9583, 12)/* RayQueryKHR */,IR(0, 0),IR(3, 1),IR(47, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4473,IR(0, 0),IR(9595, 19)/* UntypedPointersKHR */,IR(0, 0),IR(1, 0),IR(48, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4478,IR(0, 0),IR(9614, 32)/* RayTraversalPrimitiveCullingKHR */,IR(0, 0),IR(82, 2),IR(49, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4479,IR(0, 0),IR(4817, 14)/* RayTracingKHR */,IR(0, 0),IR(3, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4484,IR(0, 0),IR(9646, 26)/* TextureSampleWeightedQCOM */,IR(0, 0),IR(1, 0),IR(51, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4485,IR(0, 0),IR(9672, 21)/* TextureBoxFilterQCOM */,IR(0, 0),IR(1, 0),IR(51, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4486,IR(0, 0),IR(9693, 22)/* TextureBlockMatchQCOM */,IR(0, 0),IR(1, 0),IR(51, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4495,IR(0, 0),IR(5893, 16)/* TileShadingQCOM */,IR(0, 0),IR(3, 1),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4498,IR(0, 0),IR(9715, 23)/* TextureBlockMatch2QCOM */,IR(0, 0),IR(1, 0),IR(53, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5008,IR(0, 0),IR(9738, 16)/* Float16ImageAMD */,IR(0, 0),IR(3, 1),IR(54, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5009,IR(0, 0),IR(9754, 22)/* ImageGatherBiasLodAMD */,IR(0, 0),IR(3, 1),IR(55, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5010,IR(0, 0),IR(9776, 16)/* FragmentMaskAMD */,IR(0, 0),IR(3, 1),IR(56, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5013,IR(0, 0),IR(6130, 17)/* StencilExportEXT */,IR(0, 0),IR(3, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5015,IR(0, 0),IR(9792, 21)/* ImageReadWriteLodAMD */,IR(0, 0),IR(3, 1),IR(57, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5016,IR(0, 0),IR(9813, 14)/* Int64ImageEXT */,IR(0, 0),IR(3, 1),IR(58, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5055,IR(0, 0),IR(9827, 15)/* ShaderClockKHR */,IR(0, 0),IR(1, 0),IR(59, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5067,IR(0, 0),IR(6176, 18)/* ShaderEnqueueAMDX */,IR(0, 0),IR(3, 1),IR(60, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5087,IR(0, 0),IR(9842, 15)/* QuadControlKHR */,IR(0, 0),IR(1, 0),IR(61, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5112,IR(0, 0),IR(9857, 14)/* Int4TypeINTEL */,IR(0, 0),IR(1, 0),IR(62, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5114,IR(0, 0),IR(9871, 27)/* Int4CooperativeMatrixINTEL */,IR(0, 0),IR(84, 2),IR(62, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5116,IR(0, 0),IR(9919, 16)/* BFloat16TypeKHR */,IR(0, 0),IR(1, 0),IR(63, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5117,IR(0, 0),IR(9935, 22)/* BFloat16DotProductKHR */,IR(0, 0),IR(86, 1),IR(63, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5118,IR(0, 0),IR(9957, 29)/* BFloat16CooperativeMatrixKHR */,IR(0, 0),IR(87, 2),IR(63, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5249,IR(0, 0),IR(9986, 29)/* SampleMaskOverrideCoverageNV */,IR(0, 0),IR(25, 1),IR(64, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5251,IR(0, 0),IR(10015, 28)/* GeometryShaderPassthroughNV */,IR(0, 0),IR(69, 1),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5254,IR(0, 0),IR(4891, 28)/* ShaderViewportIndexLayerEXT */,IR(25, 1),IR(89, 1),IR(66, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5255,IR(0, 0),IR(6225, 21)/* ShaderViewportMaskNV */,IR(0, 0),IR(90, 1),IR(68, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5259,IR(0, 0),IR(6266, 19)/* ShaderStereoViewNV */,IR(0, 0),IR(91, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5260,IR(0, 0),IR(6327, 20)/* PerViewAttributesNV */,IR(0, 0),IR(40, 1),IR(69, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5265,IR(0, 0),IR(6385, 24)/* FragmentFullyCoveredEXT */,IR(0, 0),IR(3, 1),IR(17, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5266,IR(0, 0),IR(4831, 14)/* MeshShadingNV */,IR(0, 0),IR(3, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5282,IR(0, 0),IR(10070, 17)/* ImageFootprintNV */,IR(0, 0),IR(1, 0),IR(70, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5283,IR(0, 0),IR(4845, 15)/* MeshShadingEXT */,IR(0, 0),IR(3, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5284,IR(0, 0),IR(6575, 23)/* FragmentBarycentricKHR */,IR(26, 1),IR(1, 0),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5288,IR(0, 0),IR(10109, 31)/* ComputeDerivativeGroupQuadsKHR */,IR(27, 1),IR(3, 1),IR(71, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5291,IR(0, 0),IR(6664, 19)/* FragmentDensityEXT */,IR(28, 1),IR(3, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5297,IR(0, 0),IR(10184, 29)/* GroupNonUniformPartitionedNV */,IR(0, 0),IR(1, 0),IR(73, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5301,IR(0, 0),IR(10213, 17)/* ShaderNonUniform */,IR(29, 1),IR(3, 1),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5302,IR(0, 0),IR(10250, 23)/* RuntimeDescriptorArray */,IR(30, 1),IR(3, 1),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5303,IR(0, 0),IR(10299, 36)/* InputAttachmentArrayDynamicIndexing */,IR(31, 1),IR(92, 1),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5304,IR(0, 0),IR(10374, 39)/* UniformTexelBufferArrayDynamicIndexing */,IR(32, 1),IR(73, 1),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5305,IR(0, 0),IR(10455, 39)/* StorageTexelBufferArrayDynamicIndexing */,IR(33, 1),IR(93, 1),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5306,IR(0, 0),IR(10536, 37)/* UniformBufferArrayNonUniformIndexing */,IR(34, 1),IR(94, 1),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5307,IR(0, 0),IR(10613, 36)/* SampledImageArrayNonUniformIndexing */,IR(35, 1),IR(94, 1),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5308,IR(0, 0),IR(10688, 37)/* StorageBufferArrayNonUniformIndexing */,IR(36, 1),IR(94, 1),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5309,IR(0, 0),IR(10765, 36)/* StorageImageArrayNonUniformIndexing */,IR(37, 1),IR(94, 1),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5310,IR(0, 0),IR(10840, 39)/* InputAttachmentArrayNonUniformIndexing */,IR(38, 1),IR(95, 2),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5311,IR(0, 0),IR(10921, 42)/* UniformTexelBufferArrayNonUniformIndexing */,IR(39, 1),IR(97, 2),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5312,IR(0, 0),IR(11008, 42)/* StorageTexelBufferArrayNonUniformIndexing */,IR(40, 1),IR(99, 2),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5336,IR(0, 0),IR(7279, 27)/* RayTracingPositionFetchKHR */,IR(0, 0),IR(3, 1),IR(75, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5340,IR(0, 0),IR(4804, 13)/* RayTracingNV */,IR(0, 0),IR(3, 1),IR(26, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5341,IR(0, 0),IR(7226, 23)/* RayTracingMotionBlurNV */,IR(0, 0),IR(3, 1),IR(27, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5345,IR(0, 0),IR(11095, 18)/* VulkanMemoryModel */,IR(41, 1),IR(1, 0),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5346,IR(0, 0),IR(11134, 29)/* VulkanMemoryModelDeviceScope */,IR(42, 1),IR(1, 0),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5347,IR(0, 0),IR(4667, 31)/* PhysicalStorageBufferAddresses */,IR(43, 1),IR(3, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5350,IR(0, 0),IR(11229, 32)/* ComputeDerivativeGroupLinearKHR */,IR(44, 1),IR(3, 1),IR(71, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5353,IR(0, 0),IR(11292, 25)/* RayTracingProvisionalKHR */,IR(0, 0),IR(3, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5357,IR(0, 0),IR(11317, 20)/* CooperativeMatrixNV */,IR(0, 0),IR(3, 1),IR(77, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5363,IR(0, 0),IR(11337, 33)/* FragmentShaderSampleInterlockEXT */,IR(0, 0),IR(3, 1),IR(78, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5372,IR(0, 0),IR(11370, 38)/* FragmentShaderShadingRateInterlockEXT */,IR(0, 0),IR(3, 1),IR(78, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5373,IR(0, 0),IR(7594, 19)/* ShaderSMBuiltinsNV */,IR(0, 0),IR(3, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5378,IR(0, 0),IR(11408, 32)/* FragmentShaderPixelInterlockEXT */,IR(0, 0),IR(3, 1),IR(78, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5379,IR(0, 0),IR(11440, 25)/* DemoteToHelperInvocation */,IR(45, 1),IR(3, 1),IR(79, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5380,IR(0, 0),IR(11493, 23)/* DisplacementMicromapNV */,IR(0, 0),IR(3, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5381,IR(0, 0),IR(11516, 29)/* RayTracingOpacityMicromapEXT */,IR(0, 0),IR(3, 1),IR(81, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5383,IR(0, 0),IR(11545, 26)/* ShaderInvocationReorderNV */,IR(0, 0),IR(60, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5390,IR(0, 0),IR(11571, 18)/* BindlessTextureNV */,IR(0, 0),IR(1, 0),IR(83, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5391,IR(0, 0),IR(11589, 25)/* RayQueryPositionFetchKHR */,IR(0, 0),IR(3, 1),IR(75, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5394,IR(0, 0),IR(11614, 20)/* CooperativeVectorNV */,IR(0, 0),IR(1, 0),IR(84, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5404,IR(0, 0),IR(11634, 22)/* AtomicFloat16VectorNV */,IR(0, 0),IR(1, 0),IR(85, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5409,IR(0, 0),IR(7340, 33)/* RayTracingDisplacementMicromapNV */,IR(0, 0),IR(60, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5414,IR(0, 0),IR(11656, 18)/* RawAccessChainsNV */,IR(0, 0),IR(1, 0),IR(86, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5418,IR(0, 0),IR(7483, 28)/* RayTracingSpheresGeometryNV */,IR(0, 0),IR(1, 0),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5419,IR(0, 0),IR(7522, 39)/* RayTracingLinearSweptSpheresGeometryNV */,IR(0, 0),IR(1, 0),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5430,IR(0, 0),IR(11674, 30)/* CooperativeMatrixReductionsNV */,IR(0, 0),IR(1, 0),IR(87, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5431,IR(0, 0),IR(11704, 31)/* CooperativeMatrixConversionsNV */,IR(0, 0),IR(1, 0),IR(87, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5432,IR(0, 0),IR(11735, 40)/* CooperativeMatrixPerElementOperationsNV */,IR(0, 0),IR(1, 0),IR(87, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5433,IR(0, 0),IR(11775, 36)/* CooperativeMatrixTensorAddressingNV */,IR(0, 0),IR(1, 0),IR(87, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5434,IR(0, 0),IR(11811, 30)/* CooperativeMatrixBlockLoadsNV */,IR(0, 0),IR(1, 0),IR(87, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5435,IR(0, 0),IR(11841, 28)/* CooperativeVectorTrainingNV */,IR(0, 0),IR(1, 0),IR(84, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5437,IR(0, 0),IR(7768, 41)/* RayTracingClusterAccelerationStructureNV */,IR(0, 0),IR(60, 1),IR(31, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5439,IR(0, 0),IR(11869, 19)/* TensorAddressingNV */,IR(0, 0),IR(1, 0),IR(88, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5568,IR(0, 0),IR(11888, 21)/* SubgroupShuffleINTEL */,IR(0, 0),IR(1, 0),IR(89, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5569,IR(0, 0),IR(11909, 27)/* SubgroupBufferBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(89, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5570,IR(0, 0),IR(11936, 26)/* SubgroupImageBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(89, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5579,IR(0, 0),IR(11962, 31)/* SubgroupImageMediaBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(90, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5582,IR(0, 0),IR(11993, 21)/* RoundToInfinityINTEL */,IR(0, 0),IR(1, 0),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5583,IR(0, 0),IR(12014, 23)/* FloatingPointModeINTEL */,IR(0, 0),IR(1, 0),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5584,IR(0, 0),IR(12037, 23)/* IntegerFunctions2INTEL */,IR(0, 0),IR(1, 0),IR(92, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5603,IR(0, 0),IR(12060, 22)/* FunctionPointersINTEL */,IR(0, 0),IR(1, 0),IR(93, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5604,IR(0, 0),IR(12082, 24)/* IndirectReferencesINTEL */,IR(0, 0),IR(1, 0),IR(93, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5606,IR(0, 0),IR(12106, 9)/* AsmINTEL */,IR(0, 0),IR(1, 0),IR(94, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5612,IR(0, 0),IR(12115, 23)/* AtomicFloat32MinMaxEXT */,IR(0, 0),IR(1, 0),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5613,IR(0, 0),IR(12138, 23)/* AtomicFloat64MinMaxEXT */,IR(0, 0),IR(1, 0),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5616,IR(0, 0),IR(12161, 23)/* AtomicFloat16MinMaxEXT */,IR(0, 0),IR(1, 0),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5617,IR(0, 0),IR(12184, 19)/* VectorComputeINTEL */,IR(0, 0),IR(101, 1),IR(96, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5619,IR(0, 0),IR(12203, 15)/* VectorAnyINTEL */,IR(0, 0),IR(1, 0),IR(96, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5629,IR(0, 0),IR(12218, 16)/* ExpectAssumeKHR */,IR(0, 0),IR(1, 0),IR(97, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5696,IR(0, 0),IR(12234, 33)/* SubgroupAvcMotionEstimationINTEL */,IR(0, 0),IR(1, 0),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5697,IR(0, 0),IR(12267, 38)/* SubgroupAvcMotionEstimationIntraINTEL */,IR(0, 0),IR(1, 0),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5698,IR(0, 0),IR(12305, 39)/* SubgroupAvcMotionEstimationChromaINTEL */,IR(0, 0),IR(1, 0),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5817,IR(0, 0),IR(12344, 25)/* VariableLengthArrayINTEL */,IR(0, 0),IR(1, 0),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5821,IR(0, 0),IR(12369, 26)/* FunctionFloatControlINTEL */,IR(0, 0),IR(1, 0),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5824,IR(0, 0),IR(12395, 26)/* FPGAMemoryAttributesINTEL */,IR(0, 0),IR(1, 0),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5837,IR(0, 0),IR(12421, 20)/* FPFastMathModeINTEL */,IR(0, 0),IR(0, 1),IR(101, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5844,IR(0, 0),IR(12441, 32)/* ArbitraryPrecisionIntegersINTEL */,IR(0, 0),IR(1, 0),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5845,IR(0, 0),IR(12473, 37)/* ArbitraryPrecisionFloatingPointINTEL */,IR(0, 0),IR(1, 0),IR(103, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5886,IR(0, 0),IR(12510, 30)/* UnstructuredLoopControlsINTEL */,IR(0, 0),IR(1, 0),IR(104, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5888,IR(0, 0),IR(12540, 22)/* FPGALoopControlsINTEL */,IR(0, 0),IR(1, 0),IR(105, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5892,IR(0, 0),IR(12562, 22)/* KernelAttributesINTEL */,IR(0, 0),IR(1, 0),IR(106, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5897,IR(0, 0),IR(12584, 26)/* FPGAKernelAttributesINTEL */,IR(0, 0),IR(1, 0),IR(106, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5898,IR(0, 0),IR(12610, 24)/* FPGAMemoryAccessesINTEL */,IR(0, 0),IR(1, 0),IR(107, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5904,IR(0, 0),IR(12634, 27)/* FPGAClusterAttributesINTEL */,IR(0, 0),IR(1, 0),IR(108, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5906,IR(0, 0),IR(12661, 14)/* LoopFuseINTEL */,IR(0, 0),IR(1, 0),IR(109, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5908,IR(0, 0),IR(12675, 20)/* FPGADSPControlINTEL */,IR(0, 0),IR(1, 0),IR(110, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5910,IR(0, 0),IR(12695, 26)/* MemoryAccessAliasingINTEL */,IR(0, 0),IR(1, 0),IR(111, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5916,IR(0, 0),IR(12721, 40)/* FPGAInvocationPipeliningAttributesINTEL */,IR(0, 0),IR(1, 0),IR(112, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5920,IR(0, 0),IR(12761, 24)/* FPGABufferLocationINTEL */,IR(0, 0),IR(1, 0),IR(113, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5922,IR(0, 0),IR(12785, 34)/* ArbitraryPrecisionFixedPointINTEL */,IR(0, 0),IR(1, 0),IR(114, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5935,IR(0, 0),IR(12819, 23)/* USMStorageClassesINTEL */,IR(0, 0),IR(1, 0),IR(115, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5939,IR(0, 0),IR(12842, 29)/* RuntimeAlignedAttributeINTEL */,IR(0, 0),IR(1, 0),IR(116, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5943,IR(0, 0),IR(12871, 13)/* IOPipesINTEL */,IR(0, 0),IR(1, 0),IR(117, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5945,IR(0, 0),IR(12884, 19)/* BlockingPipesINTEL */,IR(0, 0),IR(1, 0),IR(118, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5948,IR(0, 0),IR(12903, 13)/* FPGARegINTEL */,IR(0, 0),IR(1, 0),IR(119, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6016,IR(0, 0),IR(12916, 19)/* DotProductInputAll */,IR(46, 1),IR(1, 0),IR(120, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6017,IR(0, 0),IR(12957, 22)/* DotProductInput4x8Bit */,IR(47, 1),IR(102, 1),IR(120, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6018,IR(0, 0),IR(13004, 28)/* DotProductInput4x8BitPacked */,IR(48, 1),IR(1, 0),IR(120, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6019,IR(0, 0),IR(13063, 11)/* DotProduct */,IR(49, 1),IR(1, 0),IR(120, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6020,IR(0, 0),IR(7821, 15)/* RayCullMaskKHR */,IR(0, 0),IR(1, 0),IR(32, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6022,IR(0, 0),IR(9898, 21)/* CooperativeMatrixKHR */,IR(0, 0),IR(1, 0),IR(121, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6024,IR(0, 0),IR(13088, 24)/* ReplicatedCompositesEXT */,IR(0, 0),IR(1, 0),IR(122, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6025,IR(0, 0),IR(13112, 16)/* BitInstructions */,IR(0, 0),IR(1, 0),IR(123, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6026,IR(0, 0),IR(13128, 25)/* GroupNonUniformRotateKHR */,IR(0, 0),IR(76, 1),IR(124, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6029,IR(0, 0),IR(13153, 15)/* FloatControls2 */,IR(0, 0),IR(1, 0),IR(125, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6033,IR(0, 0),IR(13168, 20)/* AtomicFloat32AddEXT */,IR(0, 0),IR(1, 0),IR(126, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6034,IR(0, 0),IR(13188, 20)/* AtomicFloat64AddEXT */,IR(0, 0),IR(1, 0),IR(126, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6089,IR(0, 0),IR(13208, 20)/* LongCompositesINTEL */,IR(0, 0),IR(1, 0),IR(127, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6094,IR(0, 0),IR(13228, 11)/* OptNoneEXT */,IR(50, 1),IR(1, 0),IR(128, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6095,IR(0, 0),IR(13252, 20)/* AtomicFloat16AddEXT */,IR(0, 0),IR(1, 0),IR(130, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6114,IR(0, 0),IR(13272, 21)/* DebugInfoModuleINTEL */,IR(0, 0),IR(1, 0),IR(131, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6115,IR(0, 0),IR(13293, 24)/* BFloat16ConversionINTEL */,IR(0, 0),IR(1, 0),IR(132, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6141,IR(0, 0),IR(13317, 18)/* SplitBarrierINTEL */,IR(0, 0),IR(1, 0),IR(133, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6144,IR(0, 0),IR(13335, 19)/* ArithmeticFenceEXT */,IR(0, 0),IR(1, 0),IR(134, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6150,IR(0, 0),IR(13354, 29)/* FPGAClusterAttributesV2INTEL */,IR(0, 0),IR(103, 1),IR(108, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6161,IR(0, 0),IR(13383, 28)/* FPGAKernelAttributesv2INTEL */,IR(0, 0),IR(104, 1),IR(106, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6162,IR(0, 0),IR(13411, 18)/* TaskSequenceINTEL */,IR(0, 0),IR(1, 0),IR(135, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6169,IR(0, 0),IR(13429, 16)/* FPMaxErrorINTEL */,IR(0, 0),IR(1, 0),IR(136, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6171,IR(0, 0),IR(13445, 24)/* FPGALatencyControlINTEL */,IR(0, 0),IR(1, 0),IR(137, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6174,IR(0, 0),IR(13469, 28)/* FPGAArgumentInterfacesINTEL */,IR(0, 0),IR(1, 0),IR(138, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6187,IR(0, 0),IR(13497, 30)/* GlobalVariableHostAccessINTEL */,IR(0, 0),IR(1, 0),IR(139, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6189,IR(0, 0),IR(13527, 35)/* GlobalVariableFPGADecorationsINTEL */,IR(0, 0),IR(1, 0),IR(140, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6220,IR(0, 0),IR(13562, 28)/* SubgroupBufferPrefetchINTEL */,IR(0, 0),IR(1, 0),IR(141, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6228,IR(0, 0),IR(13590, 23)/* Subgroup2DBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(142, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6229,IR(0, 0),IR(13613, 30)/* Subgroup2DBlockTransformINTEL */,IR(0, 0),IR(105, 1),IR(142, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6230,IR(0, 0),IR(13643, 30)/* Subgroup2DBlockTransposeINTEL */,IR(0, 0),IR(105, 1),IR(142, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6236,IR(0, 0),IR(13673, 38)/* SubgroupMatrixMultiplyAccumulateINTEL */,IR(0, 0),IR(1, 0),IR(143, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6241,IR(0, 0),IR(13711, 28)/* TernaryBitwiseFunctionINTEL */,IR(0, 0),IR(1, 0),IR(144, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6400,IR(0, 0),IR(13739, 26)/* GroupUniformArithmeticKHR */,IR(0, 0),IR(1, 0),IR(145, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6425,IR(0, 0),IR(13765, 27)/* TensorFloat32RoundingINTEL */,IR(0, 0),IR(1, 0),IR(146, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6427,IR(0, 0),IR(13792, 25)/* MaskedGatherScatterINTEL */,IR(0, 0),IR(1, 0),IR(147, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6441,IR(0, 0),IR(13817, 19)/* CacheControlsINTEL */,IR(0, 0),IR(1, 0),IR(148, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6460,IR(0, 0),IR(13836, 20)/* RegisterLimitsINTEL */,IR(0, 0),IR(1, 0),IR(149, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6528,IR(0, 0),IR(13856, 20)/* BindlessImagesINTEL */,IR(0, 0),IR(1, 0),IR(150, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {0,IR(0, 0),IR(13876, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(13888, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(13896, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {3,IR(0, 0),IR(13904, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(13910, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(13917, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(13928, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(13937, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(13950, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(13956, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(13966, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(13972, 15)/* ImportedModule */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {1,IR(0, 0),IR(13987, 20)/* ImportedDeclaration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {0,IR(0, 0),IR(14007, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(14012, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(14028, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(14042, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(14055, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(14067, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(14084, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(14096, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(14111, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(14124, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(14139, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(14157, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(14174, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(14195, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(14215, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(14235, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {16384,IR(0, 0),IR(14251, 16)/* FlagIsEnumClass */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {32768,IR(0, 0),IR(14267, 20)/* FlagTypePassByValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {65536,IR(0, 0),IR(14287, 24)/* FlagTypePassByReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(14311, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {1,IR(0, 0),IR(14317, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {2,IR(0, 0),IR(14322, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {3,IR(0, 1),IR(14361, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {4,IR(1, 2),IR(14372, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {5,IR(0, 0),IR(14381, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {6,IR(0, 0),IR(14386, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {7,IR(0, 0),IR(14393, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {8,IR(0, 1),IR(14404, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {9,IR(1, 2),IR(14411, 9)/* Fragment */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {0,IR(0, 0),IR(14420, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(14430, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(14443, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {3,IR(0, 0),IR(14456, 11)/* AtomicType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(14467, 10)/* Float16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1,IR(0, 0),IR(14477, 10)/* Float32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {2,IR(0, 0),IR(14487, 10)/* Float64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {3,IR(0, 0),IR(14497, 13)/* SignedInt8NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {4,IR(0, 0),IR(14510, 14)/* SignedInt16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {5,IR(0, 0),IR(14524, 14)/* SignedInt32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {6,IR(0, 0),IR(14538, 14)/* SignedInt64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {7,IR(0, 0),IR(14552, 15)/* UnsignedInt8NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {8,IR(0, 0),IR(14567, 16)/* UnsignedInt16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {9,IR(0, 0),IR(14583, 16)/* UnsignedInt32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {10,IR(0, 0),IR(14599, 16)/* UnsignedInt64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491000,IR(0, 0),IR(14615, 19)/* SignedInt8PackedNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491001,IR(0, 0),IR(14634, 21)/* UnsignedInt8PackedNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491002,IR(0, 0),IR(14655, 12)/* FloatE4M3NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491003,IR(0, 0),IR(14667, 12)/* FloatE5M2NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {0,IR(0, 0),IR(14679, 12)/* RowMajorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {1,IR(0, 0),IR(14691, 15)/* ColumnMajorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {4202,IR(0, 0),IR(14706, 25)/* RowBlockedInterleavedARM */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {4203,IR(0, 0),IR(14731, 28)/* ColumnBlockedInterleavedARM */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {0,IR(0, 0),IR(14759, 8)/* NoneKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {1,IR(0, 0),IR(14767, 27)/* MatrixASignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {2,IR(0, 0),IR(14794, 27)/* MatrixBSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {4,IR(0, 0),IR(14821, 27)/* MatrixCSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {8,IR(0, 0),IR(14848, 32)/* MatrixResultSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {16,IR(0, 0),IR(14880, 26)/* SaturatingAccumulationKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {1,IR(0, 0),IR(14906, 4)/* Row */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {2,IR(0, 0),IR(14910, 7)/* Column */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {4,IR(0, 0),IR(14917, 4)/* 2x2 */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {0,IR(0, 0),IR(14921, 11)/* MatrixAKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {1,IR(0, 0),IR(14932, 11)/* MatrixBKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {2,IR(0, 0),IR(14943, 21)/* MatrixAccumulatorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {0,IR(0, 0),IR(14964, 11)/* RowMajorNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {1,IR(0, 0),IR(14975, 14)/* ColumnMajorNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {2,IR(0, 0),IR(14989, 21)/* InferencingOptimalNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {3,IR(0, 0),IR(15010, 18)/* TrainingOptimalNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {0,IR(0, 0),IR(13876, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(13888, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(13896, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(13904, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(13910, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(13917, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(13928, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {8,IR(0, 0),IR(13937, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(13950, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(13956, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(13966, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(14007, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(14012, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(14028, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(14042, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(14055, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(14067, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(14084, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(14096, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(14111, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(14124, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(14139, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(14157, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(14174, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(14195, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(14215, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(14235, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(14311, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {1,IR(0, 0),IR(14317, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {2,IR(0, 0),IR(14322, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {3,IR(0, 1),IR(14361, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {4,IR(1, 2),IR(14372, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {5,IR(0, 0),IR(14381, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {6,IR(0, 0),IR(14386, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {7,IR(0, 0),IR(14393, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {8,IR(0, 1),IR(14404, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {0,IR(0, 0),IR(14420, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(14430, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(14443, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(15028, 17)/* RelaxedPrecision */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {1,IR(0, 1),IR(15045, 7)/* SpecId */,IR(0, 0),IR(106, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {2,IR(0, 0),IR(15052, 6)/* Block */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {3,IR(0, 0),IR(15058, 12)/* BufferBlock */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),SPV_SPIRV_VERSION_WORD(1,3)}, // SPV_OPERAND_TYPE_DECORATION
  {4,IR(0, 0),IR(15070, 9)/* RowMajor */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5,IR(0, 0),IR(15079, 9)/* ColMajor */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6,IR(0, 1),IR(15088, 12)/* ArrayStride */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {7,IR(0, 1),IR(15100, 13)/* MatrixStride */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {8,IR(0, 0),IR(15113, 11)/* GLSLShared */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {9,IR(0, 0),IR(15124, 11)/* GLSLPacked */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {10,IR(0, 0),IR(15135, 8)/* CPacked */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {11,IR(3, 1),IR(15169, 8)/* BuiltIn */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {13,IR(0, 0),IR(15177, 14)/* NoPerspective */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {14,IR(0, 0),IR(15191, 5)/* Flat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {15,IR(0, 0),IR(15196, 6)/* Patch */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {16,IR(0, 0),IR(15202, 9)/* Centroid */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {17,IR(0, 0),IR(15211, 7)/* Sample */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {18,IR(0, 0),IR(15218, 10)/* Invariant */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {19,IR(0, 0),IR(15228, 9)/* Restrict */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {20,IR(0, 0),IR(15237, 8)/* Aliased */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {21,IR(0, 0),IR(15245, 9)/* Volatile */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {22,IR(0, 0),IR(15254, 9)/* Constant */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {23,IR(0, 0),IR(15263, 9)/* Coherent */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {24,IR(0, 0),IR(15272, 12)/* NonWritable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {25,IR(0, 0),IR(15284, 12)/* NonReadable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {26,IR(0, 0),IR(15296, 8)/* Uniform */,IR(0, 0),IR(108, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {27,IR(4, 1),IR(15330, 10)/* UniformId */,IR(0, 0),IR(108, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {28,IR(0, 0),IR(15340, 20)/* SaturatedConversion */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {29,IR(0, 1),IR(15360, 7)/* Stream */,IR(0, 0),IR(110, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {30,IR(0, 1),IR(15367, 9)/* Location */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {31,IR(0, 1),IR(15376, 10)/* Component */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {32,IR(0, 1),IR(15386, 6)/* Index */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {33,IR(0, 1),IR(15392, 8)/* Binding */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {34,IR(0, 1),IR(15400, 14)/* DescriptorSet */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {35,IR(0, 1),IR(15414, 7)/* Offset */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {36,IR(0, 1),IR(15421, 10)/* XfbBuffer */,IR(0, 0),IR(111, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {37,IR(0, 1),IR(15431, 10)/* XfbStride */,IR(0, 0),IR(111, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {38,IR(5, 1),IR(15487, 14)/* FuncParamAttr */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {39,IR(6, 1),IR(15535, 15)/* FPRoundingMode */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {40,IR(7, 1),IR(15585, 15)/* FPFastMathMode */,IR(0, 0),IR(112, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {41,IR(8, 2),IR(15662, 18)/* LinkageAttributes */,IR(0, 0),IR(114, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {42,IR(0, 0),IR(15680, 14)/* NoContraction */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {43,IR(0, 1),IR(15694, 21)/* InputAttachmentIndex */,IR(0, 0),IR(92, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {44,IR(0, 1),IR(15715, 10)/* Alignment */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {45,IR(0, 1),IR(15725, 14)/* MaxByteOffset */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {46,IR(10, 1),IR(15759, 12)/* AlignmentId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {47,IR(10, 1),IR(15771, 16)/* MaxByteOffsetId */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4216,IR(0, 0),IR(15787, 44)/* SaturatedToLargestFloat8NormalConversionEXT */,IR(0, 0),IR(115, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4469,IR(0, 0),IR(15831, 13)/* NoSignedWrap */,IR(0, 0),IR(1, 0),IR(151, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4470,IR(0, 0),IR(15844, 15)/* NoUnsignedWrap */,IR(0, 0),IR(1, 0),IR(151, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4487,IR(0, 0),IR(15859, 18)/* WeightTextureQCOM */,IR(0, 0),IR(1, 0),IR(51, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4488,IR(0, 0),IR(15877, 22)/* BlockMatchTextureQCOM */,IR(0, 0),IR(1, 0),IR(51, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4499,IR(0, 0),IR(15899, 22)/* BlockMatchSamplerQCOM */,IR(0, 0),IR(1, 0),IR(53, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4999,IR(0, 0),IR(15921, 18)/* ExplicitInterpAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5019,IR(10, 1),IR(15939, 32)/* NodeSharesPayloadLimitsWithAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5020,IR(10, 1),IR(15971, 20)/* NodeMaxPayloadsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5078,IR(0, 0),IR(15991, 23)/* TrackFinishWritingAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5091,IR(10, 1),IR(16014, 20)/* PayloadNodeNameAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5098,IR(10, 1),IR(16034, 25)/* PayloadNodeBaseIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5099,IR(0, 0),IR(16059, 27)/* PayloadNodeSparseArrayAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5100,IR(10, 1),IR(16086, 25)/* PayloadNodeArraySizeAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5105,IR(0, 0),IR(16111, 28)/* PayloadDispatchIndirectAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5248,IR(0, 0),IR(16139, 19)/* OverrideCoverageNV */,IR(0, 0),IR(116, 1),IR(64, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5250,IR(0, 0),IR(16158, 14)/* PassthroughNV */,IR(0, 0),IR(117, 1),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5252,IR(0, 0),IR(16172, 19)/* ViewportRelativeNV */,IR(0, 0),IR(91, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5256,IR(0, 1),IR(16191, 28)/* SecondaryViewportRelativeNV */,IR(0, 0),IR(46, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5271,IR(0, 0),IR(16219, 16)/* PerPrimitiveEXT */,IR(51, 1),IR(118, 2),IR(152, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5272,IR(0, 0),IR(16250, 10)/* PerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5273,IR(0, 0),IR(16260, 10)/* PerTaskNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5285,IR(0, 0),IR(16270, 13)/* PerVertexKHR */,IR(52, 1),IR(51, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5300,IR(0, 0),IR(16295, 11)/* NonUniform */,IR(53, 1),IR(94, 1),IR(74, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5355,IR(0, 0),IR(16320, 16)/* RestrictPointer */,IR(54, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5356,IR(0, 0),IR(16355, 15)/* AliasedPointer */,IR(55, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5386,IR(0, 0),IR(16388, 30)/* HitObjectShaderRecordBufferNV */,IR(0, 0),IR(120, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5398,IR(0, 0),IR(16418, 18)/* BindlessSamplerNV */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5399,IR(0, 0),IR(16436, 16)/* BindlessImageNV */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5400,IR(0, 0),IR(16452, 15)/* BoundSamplerNV */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5401,IR(0, 0),IR(16467, 13)/* BoundImageNV */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5599,IR(0, 1),IR(16480, 14)/* SIMTCallINTEL */,IR(0, 0),IR(122, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5602,IR(0, 0),IR(16494, 26)/* ReferencedIndirectlyINTEL */,IR(0, 0),IR(123, 1),IR(93, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5607,IR(11, 1),IR(16520, 13)/* ClobberINTEL */,IR(0, 0),IR(124, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5608,IR(0, 0),IR(16533, 17)/* SideEffectsINTEL */,IR(0, 0),IR(124, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5624,IR(0, 0),IR(16550, 27)/* VectorComputeVariableINTEL */,IR(0, 0),IR(122, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5625,IR(0, 1),IR(16577, 21)/* FuncParamIOKindINTEL */,IR(0, 0),IR(122, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5626,IR(0, 0),IR(16598, 27)/* VectorComputeFunctionINTEL */,IR(0, 0),IR(122, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5627,IR(0, 0),IR(16625, 15)/* StackCallINTEL */,IR(0, 0),IR(122, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5628,IR(0, 1),IR(16640, 26)/* GlobalVariableOffsetINTEL */,IR(0, 0),IR(122, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5634,IR(10, 1),IR(16666, 14)/* CounterBuffer */,IR(56, 1),IR(1, 0),IR(154, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5635,IR(11, 1),IR(16704, 13)/* UserSemantic */,IR(57, 1),IR(1, 0),IR(154, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5636,IR(11, 1),IR(16736, 15)/* UserTypeGOOGLE */,IR(0, 0),IR(1, 0),IR(155, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5822,IR(12, 2),IR(16751, 26)/* FunctionRoundingModeINTEL */,IR(0, 0),IR(125, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5823,IR(14, 2),IR(16808, 24)/* FunctionDenormModeINTEL */,IR(0, 0),IR(125, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5825,IR(0, 0),IR(16832, 14)/* RegisterINTEL */,IR(0, 0),IR(126, 1),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5826,IR(11, 1),IR(16846, 12)/* MemoryINTEL */,IR(0, 0),IR(126, 1),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5827,IR(0, 1),IR(16858, 14)/* NumbanksINTEL */,IR(0, 0),IR(126, 1),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5828,IR(0, 1),IR(16872, 15)/* BankwidthINTEL */,IR(0, 0),IR(126, 1),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5829,IR(0, 1),IR(16887, 22)/* MaxPrivateCopiesINTEL */,IR(0, 0),IR(126, 1),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5830,IR(0, 0),IR(16909, 16)/* SinglepumpINTEL */,IR(0, 0),IR(126, 1),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5831,IR(0, 0),IR(16925, 16)/* DoublepumpINTEL */,IR(0, 0),IR(126, 1),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5832,IR(0, 1),IR(16941, 19)/* MaxReplicatesINTEL */,IR(0, 0),IR(126, 1),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5833,IR(0, 0),IR(16960, 20)/* SimpleDualPortINTEL */,IR(0, 0),IR(126, 1),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5834,IR(16, 2),IR(16980, 11)/* MergeINTEL */,IR(0, 0),IR(126, 1),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5835,IR(18, 1),IR(17033, 14)/* BankBitsINTEL */,IR(0, 0),IR(126, 1),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5836,IR(0, 1),IR(17047, 20)/* ForcePow2DepthINTEL */,IR(0, 0),IR(126, 1),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5883,IR(0, 1),IR(17067, 16)/* StridesizeINTEL */,IR(0, 0),IR(126, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5884,IR(0, 1),IR(17083, 14)/* WordsizeINTEL */,IR(0, 0),IR(126, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5885,IR(0, 0),IR(17097, 18)/* TrueDualPortINTEL */,IR(0, 0),IR(126, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5899,IR(0, 0),IR(17115, 19)/* BurstCoalesceINTEL */,IR(0, 0),IR(127, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5900,IR(0, 1),IR(17134, 15)/* CacheSizeINTEL */,IR(0, 0),IR(127, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5901,IR(0, 0),IR(17149, 28)/* DontStaticallyCoalesceINTEL */,IR(0, 0),IR(127, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5902,IR(0, 1),IR(17177, 14)/* PrefetchINTEL */,IR(0, 0),IR(127, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5905,IR(0, 0),IR(17191, 17)/* StallEnableINTEL */,IR(0, 0),IR(103, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5907,IR(0, 0),IR(17208, 25)/* FuseLoopsInFunctionINTEL */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5909,IR(1, 2),IR(17233, 19)/* MathOpDSPModeINTEL */,IR(0, 0),IR(129, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5914,IR(10, 1),IR(17252, 16)/* AliasScopeINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5915,IR(10, 1),IR(17268, 13)/* NoAliasINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5917,IR(0, 1),IR(17281, 24)/* InitiationIntervalINTEL */,IR(0, 0),IR(131, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5918,IR(0, 1),IR(17305, 20)/* MaxConcurrencyINTEL */,IR(0, 0),IR(131, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5919,IR(0, 1),IR(17325, 20)/* PipelineEnableINTEL */,IR(0, 0),IR(131, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5921,IR(0, 1),IR(17345, 20)/* BufferLocationINTEL */,IR(0, 0),IR(132, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5944,IR(0, 1),IR(17365, 19)/* IOPipeStorageINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6080,IR(19, 2),IR(17418, 31)/* FunctionFloatingPointModeINTEL */,IR(0, 0),IR(125, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6085,IR(0, 0),IR(17449, 25)/* SingleElementVectorINTEL */,IR(0, 0),IR(122, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6087,IR(0, 0),IR(17474, 35)/* VectorComputeCallableFunctionINTEL */,IR(0, 0),IR(122, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6140,IR(0, 0),IR(17509, 18)/* MediaBlockIOINTEL */,IR(0, 0),IR(122, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6151,IR(0, 0),IR(17527, 15)/* StallFreeINTEL */,IR(0, 0),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6170,IR(21, 1),IR(17573, 26)/* FPMaxErrorDecorationINTEL */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6172,IR(0, 1),IR(17599, 25)/* LatencyControlLabelINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6173,IR(22, 3),IR(17624, 30)/* LatencyControlConstraintINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6175,IR(0, 0),IR(17654, 27)/* ConduitKernelArgumentINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6176,IR(0, 0),IR(17681, 31)/* RegisterMapKernelArgumentINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6177,IR(0, 1),IR(17712, 33)/* MMHostInterfaceAddressWidthINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6178,IR(0, 1),IR(17745, 30)/* MMHostInterfaceDataWidthINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6179,IR(0, 1),IR(17775, 28)/* MMHostInterfaceLatencyINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6180,IR(25, 1),IR(17837, 34)/* MMHostInterfaceReadWriteModeINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6181,IR(0, 1),IR(17871, 29)/* MMHostInterfaceMaxBurstINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6182,IR(0, 1),IR(17900, 32)/* MMHostInterfaceWaitRequestINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6183,IR(0, 0),IR(17932, 26)/* StableKernelArgumentINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6188,IR(26, 2),IR(17997, 16)/* HostAccessINTEL */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6190,IR(28, 1),IR(18060, 14)/* InitModeINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6191,IR(0, 1),IR(18074, 28)/* ImplementInRegisterMapINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6442,IR(29, 2),IR(18138, 22)/* CacheControlLoadINTEL */,IR(0, 0),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6443,IR(31, 2),IR(18197, 23)/* CacheControlStoreINTEL */,IR(0, 0),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {0,IR(0, 0),IR(18220, 3)/* 1D */,IR(0, 0),IR(72, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {1,IR(0, 0),IR(18223, 3)/* 2D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {2,IR(0, 0),IR(18226, 3)/* 3D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {3,IR(0, 0),IR(18229, 5)/* Cube */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {4,IR(0, 0),IR(18234, 5)/* Rect */,IR(0, 0),IR(71, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {5,IR(0, 0),IR(18239, 7)/* Buffer */,IR(0, 0),IR(73, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {6,IR(0, 0),IR(18246, 12)/* SubpassData */,IR(0, 0),IR(92, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {4173,IR(0, 0),IR(18258, 17)/* TileImageDataEXT */,IR(0, 0),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {0,IR(0, 1),IR(18275, 12)/* Invocations */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {1,IR(0, 0),IR(18287, 13)/* SpacingEqual */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {2,IR(0, 0),IR(18300, 22)/* SpacingFractionalEven */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {3,IR(0, 0),IR(18322, 21)/* SpacingFractionalOdd */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4,IR(0, 0),IR(18343, 14)/* VertexOrderCw */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5,IR(0, 0),IR(18357, 15)/* VertexOrderCcw */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6,IR(0, 0),IR(18372, 19)/* PixelCenterInteger */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {7,IR(0, 0),IR(18391, 16)/* OriginUpperLeft */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {8,IR(0, 0),IR(18407, 16)/* OriginLowerLeft */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {9,IR(0, 0),IR(18423, 19)/* EarlyFragmentTests */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {10,IR(0, 0),IR(18442, 10)/* PointMode */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {11,IR(0, 0),IR(18452, 4)/* Xfb */,IR(0, 0),IR(111, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {12,IR(0, 0),IR(18456, 15)/* DepthReplacing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {14,IR(0, 0),IR(18471, 13)/* DepthGreater */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {15,IR(0, 0),IR(18484, 10)/* DepthLess */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {16,IR(0, 0),IR(18494, 15)/* DepthUnchanged */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {17,IR(22, 3),IR(18509, 10)/* LocalSize */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {18,IR(22, 3),IR(18519, 14)/* LocalSizeHint */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {19,IR(0, 0),IR(18533, 12)/* InputPoints */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {20,IR(0, 0),IR(18545, 11)/* InputLines */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {21,IR(0, 0),IR(18556, 20)/* InputLinesAdjacency */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {22,IR(0, 0),IR(18576, 10)/* Triangles */,IR(0, 0),IR(12, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {23,IR(0, 0),IR(18586, 24)/* InputTrianglesAdjacency */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {24,IR(0, 0),IR(18610, 6)/* Quads */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {25,IR(0, 0),IR(18616, 9)/* Isolines */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {26,IR(0, 1),IR(18625, 15)/* OutputVertices */,IR(0, 0),IR(142, 4),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {27,IR(0, 0),IR(18640, 13)/* OutputPoints */,IR(0, 0),IR(146, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {28,IR(0, 0),IR(18653, 16)/* OutputLineStrip */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {29,IR(0, 0),IR(18669, 20)/* OutputTriangleStrip */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {30,IR(0, 1),IR(18689, 12)/* VecTypeHint */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {31,IR(0, 0),IR(18701, 15)/* ContractionOff */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {33,IR(0, 0),IR(18716, 12)/* Initializer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {34,IR(0, 0),IR(18728, 10)/* Finalizer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {35,IR(0, 1),IR(5301, 13)/* SubgroupSize */,IR(0, 0),IR(149, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {36,IR(0, 1),IR(18738, 22)/* SubgroupsPerWorkgroup */,IR(0, 0),IR(149, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {37,IR(10, 1),IR(18760, 24)/* SubgroupsPerWorkgroupId */,IR(0, 0),IR(149, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {38,IR(33, 3),IR(18784, 12)/* LocalSizeId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {39,IR(33, 3),IR(18796, 16)/* LocalSizeHintId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4169,IR(0, 0),IR(18812, 34)/* NonCoherentColorAttachmentReadEXT */,IR(0, 0),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4170,IR(0, 0),IR(18846, 34)/* NonCoherentDepthAttachmentReadEXT */,IR(0, 0),IR(150, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4171,IR(0, 0),IR(18880, 36)/* NonCoherentStencilAttachmentReadEXT */,IR(0, 0),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4421,IR(0, 0),IR(18916, 30)/* SubgroupUniformControlFlowKHR */,IR(0, 0),IR(3, 1),IR(156, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4446,IR(0, 0),IR(18946, 18)/* PostDepthCoverage */,IR(0, 0),IR(152, 1),IR(44, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4459,IR(0, 1),IR(9470, 15)/* DenormPreserve */,IR(0, 0),IR(153, 1),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4460,IR(0, 1),IR(9485, 18)/* DenormFlushToZero */,IR(0, 0),IR(154, 1),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4461,IR(0, 1),IR(9503, 25)/* SignedZeroInfNanPreserve */,IR(0, 0),IR(155, 1),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4462,IR(0, 1),IR(9528, 16)/* RoundingModeRTE */,IR(0, 0),IR(156, 1),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4463,IR(0, 1),IR(9544, 16)/* RoundingModeRTZ */,IR(0, 0),IR(157, 1),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4489,IR(0, 0),IR(18964, 34)/* NonCoherentTileAttachmentReadQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4490,IR(22, 3),IR(18998, 20)/* TileShadingRateQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5017,IR(0, 0),IR(19018, 29)/* EarlyAndLateFragmentTestsAMD */,IR(0, 0),IR(3, 1),IR(157, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5027,IR(0, 0),IR(19047, 23)/* StencilRefReplacingEXT */,IR(0, 0),IR(42, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5069,IR(0, 0),IR(19070, 15)/* CoalescingAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5070,IR(10, 1),IR(19085, 15)/* IsApiEntryAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5071,IR(10, 1),IR(19100, 21)/* MaxNodeRecursionAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5072,IR(33, 3),IR(19121, 24)/* StaticNumWorkgroupsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5073,IR(10, 1),IR(6194, 16)/* ShaderIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5077,IR(33, 3),IR(19145, 21)/* MaxNumWorkgroupsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5079,IR(0, 0),IR(19166, 28)/* StencilRefUnchangedFrontAMD */,IR(0, 0),IR(42, 1),IR(158, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5080,IR(0, 0),IR(19194, 26)/* StencilRefGreaterFrontAMD */,IR(0, 0),IR(42, 1),IR(158, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5081,IR(0, 0),IR(19220, 23)/* StencilRefLessFrontAMD */,IR(0, 0),IR(42, 1),IR(158, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5082,IR(0, 0),IR(19243, 27)/* StencilRefUnchangedBackAMD */,IR(0, 0),IR(42, 1),IR(158, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5083,IR(0, 0),IR(19270, 25)/* StencilRefGreaterBackAMD */,IR(0, 0),IR(42, 1),IR(158, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5084,IR(0, 0),IR(19295, 22)/* StencilRefLessBackAMD */,IR(0, 0),IR(42, 1),IR(158, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5088,IR(0, 0),IR(19317, 19)/* QuadDerivativesKHR */,IR(0, 0),IR(158, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5089,IR(0, 0),IR(19336, 20)/* RequireFullQuadsKHR */,IR(0, 0),IR(158, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5102,IR(36, 2),IR(19356, 20)/* SharesInputWithAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5269,IR(0, 0),IR(19376, 15)/* OutputLinesEXT */,IR(58, 1),IR(118, 2),IR(152, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5270,IR(0, 1),IR(19405, 20)/* OutputPrimitivesEXT */,IR(59, 1),IR(118, 2),IR(152, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5289,IR(0, 0),IR(19444, 24)/* DerivativeGroupQuadsKHR */,IR(60, 1),IR(159, 2),IR(71, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5290,IR(0, 0),IR(19491, 25)/* DerivativeGroupLinearKHR */,IR(61, 1),IR(161, 2),IR(71, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5298,IR(0, 0),IR(19540, 19)/* OutputTrianglesEXT */,IR(62, 1),IR(118, 2),IR(152, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5366,IR(0, 0),IR(19577, 25)/* PixelInterlockOrderedEXT */,IR(0, 0),IR(163, 1),IR(78, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5367,IR(0, 0),IR(19602, 27)/* PixelInterlockUnorderedEXT */,IR(0, 0),IR(163, 1),IR(78, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5368,IR(0, 0),IR(19629, 26)/* SampleInterlockOrderedEXT */,IR(0, 0),IR(164, 1),IR(78, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5369,IR(0, 0),IR(19655, 28)/* SampleInterlockUnorderedEXT */,IR(0, 0),IR(164, 1),IR(78, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5370,IR(0, 0),IR(19683, 31)/* ShadingRateInterlockOrderedEXT */,IR(0, 0),IR(165, 1),IR(78, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5371,IR(0, 0),IR(19714, 33)/* ShadingRateInterlockUnorderedEXT */,IR(0, 0),IR(165, 1),IR(78, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5618,IR(0, 1),IR(19747, 27)/* SharedLocalMemorySizeINTEL */,IR(0, 0),IR(122, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5620,IR(0, 1),IR(19774, 21)/* RoundingModeRTPINTEL */,IR(0, 0),IR(166, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5621,IR(0, 1),IR(19795, 21)/* RoundingModeRTNINTEL */,IR(0, 0),IR(166, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5622,IR(0, 1),IR(19816, 26)/* FloatingPointModeALTINTEL */,IR(0, 0),IR(166, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5623,IR(0, 1),IR(19842, 27)/* FloatingPointModeIEEEINTEL */,IR(0, 0),IR(166, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5893,IR(22, 3),IR(19869, 22)/* MaxWorkgroupSizeINTEL */,IR(0, 0),IR(167, 1),IR(106, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5894,IR(0, 1),IR(19891, 16)/* MaxWorkDimINTEL */,IR(0, 0),IR(167, 1),IR(106, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5895,IR(0, 0),IR(19907, 20)/* NoGlobalOffsetINTEL */,IR(0, 0),IR(167, 1),IR(106, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5896,IR(0, 1),IR(19927, 22)/* NumSIMDWorkitemsINTEL */,IR(0, 0),IR(104, 1),IR(106, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5903,IR(0, 1),IR(19949, 28)/* SchedulerTargetFmaxMhzINTEL */,IR(0, 0),IR(104, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6023,IR(0, 0),IR(19977, 24)/* MaximallyReconvergesKHR */,IR(0, 0),IR(3, 1),IR(160, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6028,IR(36, 2),IR(20001, 18)/* FPFastMathDefault */,IR(0, 0),IR(168, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6154,IR(0, 1),IR(20019, 24)/* StreamingInterfaceINTEL */,IR(0, 0),IR(104, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6160,IR(0, 1),IR(20043, 26)/* RegisterMapInterfaceINTEL */,IR(0, 0),IR(169, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6417,IR(0, 1),IR(20069, 23)/* NamedBarrierCountINTEL */,IR(0, 0),IR(122, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6461,IR(0, 1),IR(20092, 22)/* MaximumRegistersINTEL */,IR(0, 0),IR(170, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6462,IR(10, 1),IR(20114, 24)/* MaximumRegistersIdINTEL */,IR(0, 0),IR(170, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6463,IR(38, 1),IR(20189, 27)/* NamedMaximumRegistersINTEL */,IR(0, 0),IR(170, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {0,IR(0, 0),IR(20216, 7)/* Vertex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {1,IR(0, 0),IR(20223, 20)/* TessellationControl */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {2,IR(0, 0),IR(20243, 23)/* TessellationEvaluation */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {3,IR(0, 0),IR(4782, 9)/* Geometry */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {4,IR(0, 0),IR(14411, 9)/* Fragment */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5,IR(0, 0),IR(20266, 10)/* GLCompute */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {6,IR(0, 0),IR(4549, 7)/* Kernel */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5267,IR(0, 0),IR(20276, 7)/* TaskNV */,IR(0, 0),IR(50, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5268,IR(0, 0),IR(20283, 7)/* MeshNV */,IR(0, 0),IR(50, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5313,IR(0, 0),IR(20290, 17)/* RayGenerationKHR */,IR(63, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5314,IR(0, 0),IR(20323, 16)/* IntersectionKHR */,IR(64, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5315,IR(0, 0),IR(20354, 10)/* AnyHitKHR */,IR(65, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5316,IR(0, 0),IR(20373, 14)/* ClosestHitKHR */,IR(66, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5317,IR(0, 0),IR(20400, 8)/* MissKHR */,IR(67, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5318,IR(0, 0),IR(20415, 12)/* CallableKHR */,IR(68, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5364,IR(0, 0),IR(20438, 8)/* TaskEXT */,IR(0, 0),IR(53, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5365,IR(0, 0),IR(20446, 8)/* MeshEXT */,IR(0, 0),IR(53, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {0,IR(0, 0),IR(20454, 9)/* Preserve */,IR(0, 0),IR(125, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPDENORM_MODE
  {1,IR(0, 0),IR(20463, 12)/* FlushToZero */,IR(0, 0),IR(125, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPDENORM_MODE
  {0,IR(0, 0),IR(20475, 12)/* BFloat16KHR */,IR(0, 0),IR(86, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {4214,IR(0, 0),IR(20487, 14)/* Float8E4M3EXT */,IR(0, 0),IR(115, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {4215,IR(0, 0),IR(20501, 14)/* Float8E5M2EXT */,IR(0, 0),IR(115, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {0,IR(0, 0),IR(20515, 5)/* IEEE */,IR(0, 0),IR(125, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPOPERATION_MODE
  {1,IR(0, 0),IR(20520, 4)/* ALT */,IR(0, 0),IR(125, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPOPERATION_MODE
  {0,IR(0, 0),IR(14007, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {1,IR(0, 0),IR(20524, 7)/* NotNaN */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {2,IR(0, 0),IR(20531, 7)/* NotInf */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {4,IR(0, 0),IR(20538, 4)/* NSZ */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {8,IR(0, 0),IR(20542, 11)/* AllowRecip */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {16,IR(0, 0),IR(20553, 5)/* Fast */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {65536,IR(0, 0),IR(20558, 14)/* AllowContract */,IR(69, 1),IR(171, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {131072,IR(0, 0),IR(20595, 13)/* AllowReassoc */,IR(70, 1),IR(171, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {262144,IR(0, 0),IR(20626, 15)/* AllowTransform */,IR(0, 0),IR(168, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {0,IR(0, 0),IR(20641, 4)/* RTE */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {1,IR(0, 0),IR(20645, 4)/* RTZ */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {2,IR(0, 0),IR(20649, 4)/* RTP */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {3,IR(0, 0),IR(20653, 4)/* RTN */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {1,IR(0, 0),IR(20657, 16)/* Vertical2Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {2,IR(0, 0),IR(20673, 16)/* Vertical4Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {4,IR(0, 0),IR(20689, 18)/* Horizontal2Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {8,IR(0, 0),IR(20707, 18)/* Horizontal4Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {0,IR(0, 0),IR(14007, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {1,IR(0, 0),IR(20725, 7)/* Inline */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {2,IR(0, 0),IR(20732, 11)/* DontInline */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {4,IR(0, 0),IR(20743, 5)/* Pure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {8,IR(0, 0),IR(20748, 6)/* Const */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {65536,IR(0, 0),IR(13228, 11)/* OptNoneEXT */,IR(50, 1),IR(173, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {0,IR(0, 0),IR(20754, 5)/* Zext */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {1,IR(0, 0),IR(20759, 5)/* Sext */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {2,IR(0, 0),IR(20764, 6)/* ByVal */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {3,IR(0, 0),IR(20770, 5)/* Sret */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {4,IR(0, 0),IR(20775, 8)/* NoAlias */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {5,IR(0, 0),IR(20783, 10)/* NoCapture */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {6,IR(0, 0),IR(20793, 8)/* NoWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {7,IR(0, 0),IR(20801, 12)/* NoReadWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {5940,IR(0, 0),IR(20813, 20)/* RuntimeAlignedINTEL */,IR(0, 0),IR(174, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {0,IR(0, 0),IR(20833, 7)/* Reduce */,IR(0, 0),IR(175, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {1,IR(0, 0),IR(20840, 14)/* InclusiveScan */,IR(0, 0),IR(175, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {2,IR(0, 0),IR(20854, 14)/* ExclusiveScan */,IR(0, 0),IR(175, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {3,IR(0, 0),IR(20868, 16)/* ClusteredReduce */,IR(0, 0),IR(178, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {6,IR(0, 0),IR(20884, 20)/* PartitionedReduceNV */,IR(0, 0),IR(179, 1),IR(73, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {7,IR(0, 0),IR(20904, 27)/* PartitionedInclusiveScanNV */,IR(0, 0),IR(179, 1),IR(73, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {8,IR(0, 0),IR(20931, 27)/* PartitionedExclusiveScanNV */,IR(0, 0),IR(179, 1),IR(73, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {0,IR(0, 0),IR(20958, 10)/* NoneINTEL */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {1,IR(0, 0),IR(20968, 10)/* ReadINTEL */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {2,IR(0, 0),IR(20978, 11)/* WriteINTEL */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {3,IR(0, 0),IR(20989, 15)/* ReadWriteINTEL */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {0,IR(0, 0),IR(14007, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {1,IR(10, 1),IR(21004, 5)/* Bias */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {2,IR(10, 1),IR(21009, 4)/* Lod */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {4,IR(36, 2),IR(21013, 5)/* Grad */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {8,IR(10, 1),IR(21018, 12)/* ConstOffset */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {16,IR(10, 1),IR(15414, 7)/* Offset */,IR(0, 0),IR(180, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {32,IR(10, 1),IR(21030, 13)/* ConstOffsets */,IR(0, 0),IR(180, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {64,IR(10, 1),IR(15211, 7)/* Sample */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {128,IR(10, 1),IR(8333, 7)/* MinLod */,IR(0, 0),IR(181, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {256,IR(4, 1),IR(21043, 19)/* MakeTexelAvailable */,IR(71, 1),IR(182, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {512,IR(4, 1),IR(21084, 17)/* MakeTexelVisible */,IR(72, 1),IR(182, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {1024,IR(0, 0),IR(21121, 16)/* NonPrivateTexel */,IR(73, 1),IR(182, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {2048,IR(0, 0),IR(21156, 14)/* VolatileTexel */,IR(74, 1),IR(182, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {4096,IR(0, 0),IR(21187, 11)/* SignExtend */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {8192,IR(0, 0),IR(21198, 11)/* ZeroExtend */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {16384,IR(0, 0),IR(21209, 12)/* Nontemporal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {65536,IR(10, 1),IR(21221, 8)/* Offsets */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {0,IR(0, 0),IR(21229, 10)/* SnormInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {1,IR(0, 0),IR(21239, 11)/* SnormInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {2,IR(0, 0),IR(21250, 10)/* UnormInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {3,IR(0, 0),IR(21260, 11)/* UnormInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {4,IR(0, 0),IR(21271, 14)/* UnormShort565 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {5,IR(0, 0),IR(21285, 14)/* UnormShort555 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {6,IR(0, 0),IR(21299, 15)/* UnormInt101010 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {7,IR(0, 0),IR(21314, 11)/* SignedInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {8,IR(0, 0),IR(21325, 12)/* SignedInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {9,IR(0, 0),IR(21337, 12)/* SignedInt32 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {10,IR(0, 0),IR(21349, 13)/* UnsignedInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {11,IR(0, 0),IR(21362, 14)/* UnsignedInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {12,IR(0, 0),IR(21376, 14)/* UnsignedInt32 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {13,IR(0, 0),IR(21390, 10)/* HalfFloat */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {14,IR(0, 0),IR(13904, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {15,IR(0, 0),IR(21400, 11)/* UnormInt24 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {16,IR(0, 0),IR(21411, 17)/* UnormInt101010_2 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {17,IR(0, 0),IR(21428, 16)/* UnormInt10X6EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {19,IR(0, 0),IR(21444, 20)/* UnsignedIntRaw10EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {20,IR(0, 0),IR(21464, 20)/* UnsignedIntRaw12EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {21,IR(0, 0),IR(21484, 20)/* UnormInt2_101010EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {22,IR(0, 0),IR(21504, 19)/* UnsignedInt10X6EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {23,IR(0, 0),IR(21523, 19)/* UnsignedInt12X4EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {24,IR(0, 0),IR(21542, 19)/* UnsignedInt14X2EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {25,IR(0, 0),IR(21561, 16)/* UnormInt12X4EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {26,IR(0, 0),IR(21577, 16)/* UnormInt14X2EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {0,IR(0, 0),IR(21593, 2)/* R */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {1,IR(0, 0),IR(21595, 2)/* A */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {2,IR(0, 0),IR(21597, 3)/* RG */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {3,IR(0, 0),IR(21600, 3)/* RA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {4,IR(0, 0),IR(21603, 4)/* RGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {5,IR(0, 0),IR(21607, 5)/* RGBA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {6,IR(0, 0),IR(21612, 5)/* BGRA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {7,IR(0, 0),IR(21617, 5)/* ARGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {8,IR(0, 0),IR(21622, 10)/* Intensity */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {9,IR(0, 0),IR(21632, 10)/* Luminance */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {10,IR(0, 0),IR(21642, 3)/* Rx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {11,IR(0, 0),IR(21645, 4)/* RGx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {12,IR(0, 0),IR(21649, 5)/* RGBx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {13,IR(0, 0),IR(21654, 6)/* Depth */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {14,IR(0, 0),IR(21660, 13)/* DepthStencil */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {15,IR(0, 0),IR(21673, 5)/* sRGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {16,IR(0, 0),IR(21678, 6)/* sRGBx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {17,IR(0, 0),IR(21684, 6)/* sRGBA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {18,IR(0, 0),IR(21690, 6)/* sBGRA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {19,IR(0, 0),IR(21696, 5)/* ABGR */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {0,IR(0, 0),IR(21701, 27)/* InitOnDeviceReprogramINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {1,IR(0, 0),IR(21728, 23)/* InitOnDeviceResetINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {0,IR(0, 0),IR(21751, 7)/* NoWait */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {1,IR(0, 0),IR(21758, 11)/* WaitKernel */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {2,IR(0, 0),IR(21769, 14)/* WaitWorkGroup */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {0,IR(0, 0),IR(14007, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {1,IR(0, 0),IR(21783, 12)/* CmdExecTime */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {0,IR(0, 0),IR(14007, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {1,IR(0, 0),IR(21795, 13)/* MayUsePrintf */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {0,IR(0, 0),IR(21808, 7)/* Export */,IR(0, 0),IR(114, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {1,IR(0, 0),IR(21815, 7)/* Import */,IR(0, 0),IR(114, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {2,IR(0, 0),IR(21822, 12)/* LinkOnceODR */,IR(0, 0),IR(114, 1),IR(161, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {0,IR(0, 0),IR(21834, 14)/* UncachedINTEL */,IR(0, 0),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {1,IR(0, 0),IR(21848, 12)/* CachedINTEL */,IR(0, 0),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {2,IR(0, 0),IR(21860, 15)/* StreamingINTEL */,IR(0, 0),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {3,IR(0, 0),IR(21875, 25)/* InvalidateAfterReadINTEL */,IR(0, 0),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {4,IR(0, 0),IR(21900, 17)/* ConstCachedINTEL */,IR(0, 0),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {0,IR(0, 0),IR(14007, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {1,IR(0, 0),IR(21917, 7)/* Unroll */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {2,IR(0, 0),IR(21924, 11)/* DontUnroll */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {4,IR(0, 0),IR(21935, 19)/* DependencyInfinite */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {8,IR(0, 1),IR(21954, 17)/* DependencyLength */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {16,IR(0, 1),IR(21971, 14)/* MinIterations */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {32,IR(0, 1),IR(21985, 14)/* MaxIterations */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {64,IR(0, 1),IR(21999, 18)/* IterationMultiple */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {128,IR(0, 1),IR(22017, 10)/* PeelCount */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {256,IR(0, 1),IR(22027, 13)/* PartialCount */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {65536,IR(0, 1),IR(17281, 24)/* InitiationIntervalINTEL */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {131072,IR(0, 1),IR(17305, 20)/* MaxConcurrencyINTEL */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {262144,IR(0, 1),IR(22040, 21)/* DependencyArrayINTEL */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {524288,IR(0, 1),IR(17325, 20)/* PipelineEnableINTEL */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {1048576,IR(0, 1),IR(22061, 18)/* LoopCoalesceINTEL */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {2097152,IR(0, 1),IR(22079, 21)/* MaxInterleavingINTEL */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {4194304,IR(0, 1),IR(22100, 26)/* SpeculatedIterationsINTEL */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {8388608,IR(0, 0),IR(22126, 14)/* NoFusionINTEL */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {16777216,IR(0, 1),IR(22140, 15)/* LoopCountINTEL */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {33554432,IR(0, 1),IR(22155, 26)/* MaxReinvocationDelayINTEL */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {0,IR(0, 0),IR(14007, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {1,IR(0, 0),IR(22181, 29)/* MatrixASignedComponentsINTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {2,IR(0, 0),IR(22210, 29)/* MatrixBSignedComponentsINTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {4,IR(0, 0),IR(22239, 21)/* MatrixCBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {8,IR(0, 0),IR(22260, 26)/* MatrixResultBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {16,IR(0, 0),IR(22286, 23)/* MatrixAPackedInt8INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {32,IR(0, 0),IR(22309, 23)/* MatrixBPackedInt8INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {64,IR(0, 0),IR(22332, 23)/* MatrixAPackedInt4INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {128,IR(0, 0),IR(22355, 23)/* MatrixBPackedInt4INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {256,IR(0, 0),IR(22378, 17)/* MatrixATF32INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {512,IR(0, 0),IR(22395, 17)/* MatrixBTF32INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {1024,IR(0, 0),IR(22412, 26)/* MatrixAPackedFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {2048,IR(0, 0),IR(22438, 26)/* MatrixBPackedFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {4096,IR(0, 0),IR(22464, 27)/* MatrixAPackedBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {8192,IR(0, 0),IR(22491, 27)/* MatrixBPackedBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {0,IR(0, 0),IR(14007, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {1,IR(0, 0),IR(15245, 9)/* Volatile */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {2,IR(0, 1),IR(22518, 8)/* Aligned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {4,IR(0, 0),IR(21209, 12)/* Nontemporal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {8,IR(4, 1),IR(22526, 21)/* MakePointerAvailable */,IR(75, 1),IR(182, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {16,IR(4, 1),IR(22571, 19)/* MakePointerVisible */,IR(76, 1),IR(182, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {32,IR(0, 0),IR(22612, 18)/* NonPrivatePointer */,IR(77, 1),IR(182, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {65536,IR(10, 1),IR(22651, 20)/* AliasScopeINTELMask */,IR(0, 0),IR(130, 1),IR(111, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {131072,IR(10, 1),IR(22671, 17)/* NoAliasINTELMask */,IR(0, 0),IR(130, 1),IR(111, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {0,IR(0, 0),IR(22688, 7)/* Simple */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {1,IR(0, 0),IR(22695, 8)/* GLSL450 */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {2,IR(0, 0),IR(22703, 7)/* OpenCL */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {3,IR(0, 0),IR(22710, 7)/* Vulkan */,IR(78, 1),IR(182, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {0,IR(0, 0),IR(22727, 8)/* Relaxed */,IR(79, 1),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {2,IR(0, 0),IR(22735, 8)/* Acquire */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {4,IR(0, 0),IR(22743, 8)/* Release */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {8,IR(0, 0),IR(22751, 15)/* AcquireRelease */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {16,IR(0, 0),IR(22766, 23)/* SequentiallyConsistent */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {64,IR(0, 0),IR(22789, 14)/* UniformMemory */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {128,IR(0, 0),IR(22803, 15)/* SubgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {256,IR(0, 0),IR(22818, 16)/* WorkgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {512,IR(0, 0),IR(22834, 21)/* CrossWorkgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {1024,IR(0, 0),IR(22855, 20)/* AtomicCounterMemory */,IR(0, 0),IR(80, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {2048,IR(0, 0),IR(22875, 12)/* ImageMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {4096,IR(0, 0),IR(22887, 13)/* OutputMemory */,IR(80, 1),IR(182, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {8192,IR(0, 0),IR(22916, 14)/* MakeAvailable */,IR(81, 1),IR(182, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {16384,IR(0, 0),IR(22947, 12)/* MakeVisible */,IR(82, 1),IR(182, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {32768,IR(0, 0),IR(15245, 9)/* Volatile */,IR(0, 0),IR(182, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {0,IR(0, 0),IR(22974, 10)/* AutoINTEL */,IR(0, 0),IR(170, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS
  {0,IR(0, 0),IR(22984, 5)/* WRAP */,IR(0, 0),IR(184, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {1,IR(0, 0),IR(22989, 4)/* SAT */,IR(0, 0),IR(184, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {2,IR(0, 0),IR(22993, 9)/* SAT_ZERO */,IR(0, 0),IR(184, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {3,IR(0, 0),IR(23002, 8)/* SAT_SYM */,IR(0, 0),IR(184, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {0,IR(0, 0),IR(23010, 25)/* PackedVectorFormat4x8Bit */,IR(83, 1),IR(1, 0),IR(120, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {0,IR(0, 0),IR(23063, 4)/* TRN */,IR(0, 0),IR(184, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {1,IR(0, 0),IR(23067, 9)/* TRN_ZERO */,IR(0, 0),IR(184, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {2,IR(0, 0),IR(23076, 4)/* RND */,IR(0, 0),IR(184, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {3,IR(0, 0),IR(23080, 9)/* RND_ZERO */,IR(0, 0),IR(184, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {4,IR(0, 0),IR(23089, 8)/* RND_INF */,IR(0, 0),IR(184, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {5,IR(0, 0),IR(23097, 12)/* RND_MIN_INF */,IR(0, 0),IR(184, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {6,IR(0, 0),IR(23109, 9)/* RND_CONV */,IR(0, 0),IR(184, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {7,IR(0, 0),IR(23118, 13)/* RND_CONV_ODD */,IR(0, 0),IR(184, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {0,IR(0, 0),IR(14007, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {1,IR(0, 0),IR(23131, 25)/* RobustnessPerComponentNV */,IR(0, 0),IR(185, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {2,IR(0, 0),IR(23156, 23)/* RobustnessPerElementNV */,IR(0, 0),IR(185, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {0,IR(0, 0),IR(14759, 8)/* NoneKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {1,IR(0, 0),IR(23179, 10)/* OpaqueKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {2,IR(0, 0),IR(23189, 12)/* NoOpaqueKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {4,IR(0, 0),IR(23201, 23)/* TerminateOnFirstHitKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {8,IR(0, 0),IR(23224, 24)/* SkipClosestHitShaderKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {16,IR(0, 0),IR(23248, 27)/* CullBackFacingTrianglesKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {32,IR(0, 0),IR(23275, 28)/* CullFrontFacingTrianglesKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {64,IR(0, 0),IR(23303, 14)/* CullOpaqueKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {128,IR(0, 0),IR(23317, 16)/* CullNoOpaqueKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {256,IR(0, 0),IR(23333, 17)/* SkipTrianglesKHR */,IR(84, 1),IR(186, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {512,IR(0, 0),IR(23374, 13)/* SkipAABBsKHR */,IR(0, 0),IR(186, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {1024,IR(0, 0),IR(23387, 30)/* ForceOpacityMicromap2StateEXT */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {0,IR(0, 0),IR(23417, 41)/* RayQueryCandidateIntersectionTriangleKHR */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {1,IR(0, 0),IR(23458, 37)/* RayQueryCandidateIntersectionAABBKHR */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {0,IR(0, 0),IR(23495, 37)/* RayQueryCommittedIntersectionNoneKHR */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {1,IR(0, 0),IR(23532, 41)/* RayQueryCommittedIntersectionTriangleKHR */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {2,IR(0, 0),IR(23573, 42)/* RayQueryCommittedIntersectionGeneratedKHR */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {0,IR(0, 0),IR(23615, 33)/* RayQueryCandidateIntersectionKHR */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {1,IR(0, 0),IR(23648, 33)/* RayQueryCommittedIntersectionKHR */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {0,IR(0, 0),IR(14007, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {1,IR(0, 0),IR(23681, 12)/* ClampToEdge */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {2,IR(0, 0),IR(23693, 6)/* Clamp */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {3,IR(0, 0),IR(23699, 7)/* Repeat */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {4,IR(0, 0),IR(23706, 15)/* RepeatMirrored */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {0,IR(0, 0),IR(23721, 8)/* Nearest */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {1,IR(0, 0),IR(23729, 7)/* Linear */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {0,IR(0, 0),IR(23736, 8)/* Unknown */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {1,IR(0, 0),IR(23744, 8)/* Rgba32f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {2,IR(0, 0),IR(23752, 8)/* Rgba16f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {3,IR(0, 0),IR(23760, 5)/* R32f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {4,IR(0, 0),IR(23765, 6)/* Rgba8 */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {5,IR(0, 0),IR(23771, 11)/* Rgba8Snorm */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {6,IR(0, 0),IR(23782, 6)/* Rg32f */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {7,IR(0, 0),IR(23788, 6)/* Rg16f */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {8,IR(0, 0),IR(23794, 13)/* R11fG11fB10f */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {9,IR(0, 0),IR(23807, 5)/* R16f */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {10,IR(0, 0),IR(23812, 7)/* Rgba16 */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {11,IR(0, 0),IR(23819, 8)/* Rgb10A2 */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {12,IR(0, 0),IR(23827, 5)/* Rg16 */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {13,IR(0, 0),IR(23832, 4)/* Rg8 */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {14,IR(0, 0),IR(23836, 4)/* R16 */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {15,IR(0, 0),IR(23840, 3)/* R8 */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {16,IR(0, 0),IR(23843, 12)/* Rgba16Snorm */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {17,IR(0, 0),IR(23855, 10)/* Rg16Snorm */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {18,IR(0, 0),IR(23865, 9)/* Rg8Snorm */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {19,IR(0, 0),IR(23874, 9)/* R16Snorm */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {20,IR(0, 0),IR(23883, 8)/* R8Snorm */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {21,IR(0, 0),IR(23891, 8)/* Rgba32i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {22,IR(0, 0),IR(23899, 8)/* Rgba16i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {23,IR(0, 0),IR(23907, 7)/* Rgba8i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {24,IR(0, 0),IR(23914, 5)/* R32i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {25,IR(0, 0),IR(23919, 6)/* Rg32i */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {26,IR(0, 0),IR(23925, 6)/* Rg16i */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {27,IR(0, 0),IR(23931, 5)/* Rg8i */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {28,IR(0, 0),IR(23936, 5)/* R16i */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {29,IR(0, 0),IR(23941, 4)/* R8i */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {30,IR(0, 0),IR(23945, 9)/* Rgba32ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {31,IR(0, 0),IR(23954, 9)/* Rgba16ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {32,IR(0, 0),IR(23963, 8)/* Rgba8ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {33,IR(0, 0),IR(23971, 6)/* R32ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {34,IR(0, 0),IR(23977, 10)/* Rgb10a2ui */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {35,IR(0, 0),IR(23987, 7)/* Rg32ui */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {36,IR(0, 0),IR(23994, 7)/* Rg16ui */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {37,IR(0, 0),IR(24001, 6)/* Rg8ui */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {38,IR(0, 0),IR(24007, 6)/* R16ui */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {39,IR(0, 0),IR(24013, 5)/* R8ui */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {40,IR(0, 0),IR(24018, 6)/* R64ui */,IR(0, 0),IR(190, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {41,IR(0, 0),IR(24024, 5)/* R64i */,IR(0, 0),IR(190, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {0,IR(0, 0),IR(24029, 12)/* CrossDevice */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {1,IR(0, 0),IR(24041, 7)/* Device */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {2,IR(0, 0),IR(24048, 10)/* Workgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {3,IR(0, 0),IR(24058, 9)/* Subgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {4,IR(0, 0),IR(24067, 11)/* Invocation */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {5,IR(0, 0),IR(24078, 12)/* QueueFamily */,IR(85, 1),IR(182, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {6,IR(0, 0),IR(24105, 14)/* ShaderCallKHR */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {0,IR(0, 0),IR(14007, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {1,IR(0, 0),IR(24119, 8)/* Flatten */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {2,IR(0, 0),IR(24127, 12)/* DontFlatten */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {1,IR(0, 0),IR(24139, 29)/* IdentifierPossibleDuplicates */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS
  {0,IR(0, 0),IR(13876, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(13888, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(13896, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {3,IR(0, 0),IR(13904, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(13910, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(13917, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(13928, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(13937, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(13950, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(13956, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(13966, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(13972, 15)/* ImportedModule */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {1,IR(0, 0),IR(13987, 20)/* ImportedDeclaration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {0,IR(0, 0),IR(14007, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(14012, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(14028, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(14042, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(14055, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(14067, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(14084, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(14096, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(14111, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(14124, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(14139, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(14157, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(14174, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(14195, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(14215, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(14235, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {16384,IR(0, 0),IR(14251, 16)/* FlagIsEnumClass */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {32768,IR(0, 0),IR(14267, 20)/* FlagTypePassByValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {65536,IR(0, 0),IR(14287, 24)/* FlagTypePassByReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {131072,IR(0, 0),IR(24168, 26)/* FlagUnknownPhysicalLayout */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(14311, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {1,IR(0, 0),IR(14317, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {2,IR(0, 0),IR(14322, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {3,IR(10, 1),IR(14361, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {4,IR(36, 2),IR(14372, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {5,IR(0, 0),IR(14381, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {6,IR(0, 0),IR(14386, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {7,IR(0, 0),IR(14393, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {8,IR(10, 1),IR(14404, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {9,IR(36, 2),IR(14411, 9)/* Fragment */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {0,IR(0, 0),IR(14420, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(14430, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(14443, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {3,IR(0, 0),IR(14456, 11)/* AtomicType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(23736, 8)/* Unknown */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {1,IR(0, 0),IR(24194, 5)/* ESSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {2,IR(0, 0),IR(24199, 5)/* GLSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {3,IR(0, 0),IR(24204, 9)/* OpenCL_C */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {4,IR(0, 0),IR(24213, 11)/* OpenCL_CPP */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {5,IR(0, 0),IR(24224, 5)/* HLSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {6,IR(0, 0),IR(24229, 15)/* CPP_for_OpenCL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {7,IR(0, 0),IR(24244, 5)/* SYCL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {8,IR(0, 0),IR(24249, 7)/* HERO_C */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {9,IR(0, 0),IR(24256, 5)/* NZSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {10,IR(0, 0),IR(24261, 5)/* WGSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {11,IR(0, 0),IR(24266, 6)/* Slang */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {12,IR(0, 0),IR(24272, 4)/* Zig */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {13,IR(0, 0),IR(24276, 5)/* Rust */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {0,IR(0, 0),IR(24281, 16)/* UniformConstant */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {1,IR(0, 0),IR(24297, 6)/* Input */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {2,IR(0, 0),IR(15296, 8)/* Uniform */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {3,IR(0, 0),IR(24303, 7)/* Output */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4,IR(0, 0),IR(24048, 10)/* Workgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5,IR(0, 0),IR(24310, 15)/* CrossWorkgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {6,IR(0, 0),IR(24325, 8)/* Private */,IR(0, 0),IR(191, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {7,IR(0, 0),IR(24333, 9)/* Function */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {8,IR(0, 0),IR(24342, 8)/* Generic */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {9,IR(0, 0),IR(24350, 13)/* PushConstant */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {10,IR(0, 0),IR(24363, 14)/* AtomicCounter */,IR(0, 0),IR(80, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {11,IR(0, 0),IR(24377, 6)/* Image */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {12,IR(0, 0),IR(24383, 14)/* StorageBuffer */,IR(0, 0),IR(3, 1),IR(162, 2),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4172,IR(0, 0),IR(24397, 13)/* TileImageEXT */,IR(0, 0),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4491,IR(0, 0),IR(24410, 19)/* TileAttachmentQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5068,IR(0, 0),IR(24429, 16)/* NodePayloadAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5328,IR(0, 0),IR(24445, 16)/* CallableDataKHR */,IR(86, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5329,IR(0, 0),IR(24476, 24)/* IncomingCallableDataKHR */,IR(87, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5338,IR(0, 0),IR(24523, 14)/* RayPayloadKHR */,IR(88, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5339,IR(0, 0),IR(24550, 16)/* HitAttributeKHR */,IR(89, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5342,IR(0, 0),IR(24581, 22)/* IncomingRayPayloadKHR */,IR(90, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5343,IR(0, 0),IR(24624, 22)/* ShaderRecordBufferKHR */,IR(91, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5349,IR(0, 0),IR(24667, 22)/* PhysicalStorageBuffer */,IR(92, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5385,IR(0, 0),IR(24714, 21)/* HitObjectAttributeNV */,IR(0, 0),IR(120, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5402,IR(0, 0),IR(24735, 24)/* TaskPayloadWorkgroupEXT */,IR(0, 0),IR(53, 1),IR(23, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5605,IR(0, 0),IR(24759, 17)/* CodeSectionINTEL */,IR(0, 0),IR(194, 1),IR(93, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5936,IR(0, 0),IR(24776, 16)/* DeviceOnlyINTEL */,IR(0, 0),IR(195, 1),IR(115, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5937,IR(0, 0),IR(24792, 14)/* HostOnlyINTEL */,IR(0, 0),IR(195, 1),IR(115, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {0,IR(0, 0),IR(21834, 14)/* UncachedINTEL */,IR(0, 0),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {1,IR(0, 0),IR(24806, 18)/* WriteThroughINTEL */,IR(0, 0),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {2,IR(0, 0),IR(24824, 15)/* WriteBackINTEL */,IR(0, 0),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {3,IR(0, 0),IR(21860, 15)/* StreamingINTEL */,IR(0, 0),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {0,IR(0, 0),IR(14007, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {1,IR(10, 1),IR(24839, 11)/* TensorView */,IR(0, 0),IR(196, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {2,IR(10, 1),IR(24850, 11)/* DecodeFunc */,IR(0, 0),IR(197, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {0,IR(0, 0),IR(24861, 10)/* Undefined */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {1,IR(0, 0),IR(15254, 9)/* Constant */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {2,IR(0, 0),IR(23681, 12)/* ClampToEdge */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {3,IR(0, 0),IR(23699, 7)/* Repeat */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {4,IR(0, 0),IR(23706, 15)/* RepeatMirrored */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {0,IR(0, 0),IR(24871, 8)/* NoneARM */,IR(0, 0),IR(198, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {1,IR(0, 0),IR(24879, 15)/* NontemporalARM */,IR(0, 0),IR(198, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {2,IR(10, 1),IR(24894, 20)/* OutOfBoundsValueARM */,IR(0, 0),IR(198, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {4,IR(10, 1),IR(24914, 24)/* MakeElementAvailableARM */,IR(0, 0),IR(198, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {8,IR(10, 1),IR(24938, 22)/* MakeElementVisibleARM */,IR(0, 0),IR(198, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {16,IR(0, 0),IR(24960, 21)/* NonPrivateElementARM */,IR(0, 0),IR(198, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
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
    case SPV_OPERAND_TYPE_CAPABILITY: return IR(133, 269);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(402, 8);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(410, 3);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(413, 2);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS: return IR(415, 19);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION: return IR(434, 10);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(444, 4);
    case SPV_OPERAND_TYPE_COMPONENT_TYPE: return IR(448, 15);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT: return IR(463, 4);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS: return IR(467, 6);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE: return IR(473, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE: return IR(476, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT: return IR(479, 4);
    case SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(483, 8);
    case SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE: return IR(491, 3);
    case SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS: return IR(494, 16);
    case SPV_OPERAND_TYPE_DEBUG_OPERATION: return IR(510, 9);
    case SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER: return IR(519, 3);
    case SPV_OPERAND_TYPE_DECORATION: return IR(522, 143);
    case SPV_OPERAND_TYPE_DIMENSIONALITY: return IR(665, 8);
    case SPV_OPERAND_TYPE_EXECUTION_MODE: return IR(673, 96);
    case SPV_OPERAND_TYPE_EXECUTION_MODEL: return IR(769, 17);
    case SPV_OPERAND_TYPE_FPDENORM_MODE: return IR(786, 2);
    case SPV_OPERAND_TYPE_FPENCODING: return IR(788, 3);
    case SPV_OPERAND_TYPE_FPOPERATION_MODE: return IR(791, 2);
    case SPV_OPERAND_TYPE_FP_FAST_MATH_MODE: return IR(793, 9);
    case SPV_OPERAND_TYPE_FP_ROUNDING_MODE: return IR(802, 4);
    case SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE: return IR(806, 4);
    case SPV_OPERAND_TYPE_FUNCTION_CONTROL: return IR(810, 6);
    case SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE: return IR(816, 9);
    case SPV_OPERAND_TYPE_GROUP_OPERATION: return IR(825, 7);
    case SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER: return IR(832, 4);
    case SPV_OPERAND_TYPE_IMAGE: return IR(836, 17);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE: return IR(853, 26);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER: return IR(879, 20);
    case SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER: return IR(899, 2);
    case SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS: return IR(901, 3);
    case SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO: return IR(904, 2);
    case SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS: return IR(906, 2);
    case SPV_OPERAND_TYPE_LINKAGE_TYPE: return IR(908, 3);
    case SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL: return IR(911, 5);
    case SPV_OPERAND_TYPE_LOOP_CONTROL: return IR(916, 20);
    case SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(936, 15);
    case SPV_OPERAND_TYPE_MEMORY_ACCESS: return IR(951, 9);
    case SPV_OPERAND_TYPE_MEMORY_MODEL: return IR(960, 4);
    case SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID: return IR(964, 15);
    case SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS: return IR(979, 1);
    case SPV_OPERAND_TYPE_OVERFLOW_MODES: return IR(980, 4);
    case SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT: return IR(984, 1);
    case SPV_OPERAND_TYPE_QUANTIZATION_MODES: return IR(985, 8);
    case SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS: return IR(993, 3);
    case SPV_OPERAND_TYPE_RAY_FLAGS: return IR(996, 12);
    case SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE: return IR(1008, 2);
    case SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE: return IR(1010, 3);
    case SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION: return IR(1013, 2);
    case SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE: return IR(1015, 5);
    case SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE: return IR(1020, 2);
    case SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT: return IR(1022, 42);
    case SPV_OPERAND_TYPE_SCOPE_ID: return IR(1064, 7);
    case SPV_OPERAND_TYPE_SELECTION_CONTROL: return IR(1071, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS: return IR(1074, 1);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(1075, 8);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(1083, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(1086, 2);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS: return IR(1088, 20);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION: return IR(1108, 10);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(1118, 4);
    case SPV_OPERAND_TYPE_SOURCE_LANGUAGE: return IR(1122, 14);
    case SPV_OPERAND_TYPE_STORAGE_CLASS: return IR(1136, 28);
    case SPV_OPERAND_TYPE_STORE_CACHE_CONTROL: return IR(1164, 4);
    case SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS: return IR(1168, 3);
    case SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE: return IR(1171, 5);
    case SPV_OPERAND_TYPE_TENSOR_OPERANDS: return IR(1176, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_IMAGE: return IR(836, 17);
    case SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS: return IR(951, 9);
    case SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT: return IR(984, 1);
    case SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS: return IR(467, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(936, 15);
    case SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS: return IR(993, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_FPENCODING: return IR(788, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS: return IR(1176, 6);
    default: break;
  }
  return IR(0,0);
}

// Operand names and index into kOperandsByValue, ordered by (operand kind, name)
// The fields in order are:
//   name, either the primary name or an alias, indexing into kStrings
//   index into the kOperandsByValue array
static const std::array<NameIndex, 1276> kOperandNames{{
  {IR(4540, 9), 0}, // 0 ReadOnly in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(4566, 10), 2}, // 1 ReadWrite in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(4556, 10), 1}, // 2 WriteOnly in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(4576, 8), 3}, // 3 Logical in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(4584, 11), 4}, // 4 Physical32 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(4605, 11), 5}, // 5 Physical64 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(4616, 24), 6}, // 6 PhysicalStorageBuffer64 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(4640, 27), 6}, // 7 PhysicalStorageBuffer64EXT in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(6550, 13), 92}, // 8 BaryCoordKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6563, 12), 92}, // 9 BaryCoordNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5945, 20), 68}, // 10 BaryCoordNoPerspAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5965, 28), 69}, // 11 BaryCoordNoPerspCentroidAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6598, 20), 93}, // 12 BaryCoordNoPerspKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6618, 19), 93}, // 13 BaryCoordNoPerspNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5993, 26), 70}, // 14 BaryCoordNoPerspSampleAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6090, 22), 74}, // 15 BaryCoordPullModelAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6019, 19), 71}, // 16 BaryCoordSmoothAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6038, 27), 72}, // 17 BaryCoordSmoothCentroidAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6065, 25), 73}, // 18 BaryCoordSmoothSampleAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5749, 13), 59}, // 19 BaseInstance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5723, 11), 58}, // 20 BaseVertex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4724, 13), 9}, // 21 ClipDistance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6457, 22), 87}, // 22 ClipDistancePerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7756, 12), 131}, // 23 ClusterIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5487, 13), 49}, // 24 CoreCountARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5461, 10), 48}, // 25 CoreIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5500, 13), 50}, // 26 CoreMaxIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4737, 13), 10}, // 27 CullDistance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6479, 22), 88}, // 28 CullDistancePerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7809, 12), 132}, // 29 CullMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6805, 17), 99}, // 30 CullPrimitiveEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7209, 17), 113}, // 31 CurrentRayTimeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5819, 12), 62}, // 32 DeviceIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5762, 10), 60}, // 33 DrawIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5251, 22), 37}, // 34 EnqueuedWorkgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5021, 10), 21}, // 35 FragCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5107, 10), 27}, // 36 FragDepth in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6683, 23), 95}, // 37 FragInvocationCountEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6637, 12), 94}, // 38 FragSizeEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6112, 18), 75}, // 39 FragStencilRefEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6649, 15), 94}, // 40 FragmentSizeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5042, 12), 23}, // 41 FrontFacing in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6369, 16), 83}, // 42 FullyCoveredEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5192, 19), 33}, // 43 GlobalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5286, 15), 39}, // 44 GlobalLinearId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5273, 13), 38}, // 45 GlobalOffset in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5240, 11), 36}, // 46 GlobalSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5117, 17), 28}, // 47 HelperInvocation in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7511, 11), 120}, // 48 HitIsLSSNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7469, 14), 119}, // 49 HitIsSphereNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7691, 33), 128}, // 50 HitKindBackFacingMicroTriangleNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7657, 34), 127}, // 51 HitKindFrontFacingMicroTriangleNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7188, 11), 112}, // 52 HitKindKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7199, 10), 112}, // 53 HitKindNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7639, 18), 126}, // 54 HitLSSPositionsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7742, 14), 130}, // 55 HitLSSRadiiNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7373, 37), 116}, // 56 HitMicroTriangleVertexBarycentricsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7306, 34), 115}, // 57 HitMicroTriangleVertexPositionsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7561, 20), 121}, // 58 HitSpherePositionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7724, 18), 129}, // 59 HitSphereRadiusNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7181, 7), 111}, // 60 HitTNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7249, 30), 114}, // 61 HitTriangleVertexPositionsKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7410, 20), 117}, // 62 IncomingRayFlagsKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7430, 19), 117}, // 63 IncomingRayFlagsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7070, 23), 108}, // 64 InstanceCustomIndexKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7093, 22), 108}, // 65 InstanceCustomIndexNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4759, 11), 12}, // 66 InstanceId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5447, 14), 47}, // 67 InstanceIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4860, 13), 14}, // 68 InvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6706, 22), 95}, // 69 InvocationsPerPixelNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6822, 12), 100}, // 70 LaunchIdKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6834, 11), 100}, // 71 LaunchIdNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6845, 14), 101}, // 72 LaunchSizeKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6859, 13), 101}, // 73 LaunchSizeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4873, 6), 15}, // 74 Layer in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6501, 15), 89}, // 75 LayerPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5174, 18), 32}, // 76 LocalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5211, 21), 34}, // 77 LocalInvocationIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6516, 16), 90}, // 78 MeshViewCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6532, 18), 91}, // 79 MeshViewIndicesNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5377, 21), 43}, // 80 NumEnqueuedSubgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5364, 13), 42}, // 81 NumSubgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5134, 14), 29}, // 82 NumWorkgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6985, 22), 105}, // 83 ObjectRayDirectionKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7007, 21), 105}, // 84 ObjectRayDirectionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6948, 19), 104}, // 85 ObjectRayOriginKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6967, 18), 104}, // 86 ObjectRayOriginNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7115, 17), 109}, // 87 ObjectToWorldKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7132, 16), 109}, // 88 ObjectToWorldNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5007, 14), 20}, // 89 PatchVertices in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5031, 11), 22}, // 90 PointCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4714, 10), 8}, // 91 PointSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4698, 9), 7}, // 92 Position in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6309, 18), 81}, // 93 PositionPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6421, 17), 85}, // 94 PrimitiveCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4770, 12), 13}, // 95 PrimitiveId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6438, 19), 86}, // 96 PrimitiveIndicesNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6753, 24), 97}, // 97 PrimitiveLineIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6728, 25), 96}, // 98 PrimitivePointIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5772, 24), 61}, // 99 PrimitiveShadingRateKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6777, 28), 98}, // 100 PrimitiveTriangleIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7449, 20), 118}, // 101 RayGeometryIndexKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7049, 11), 107}, // 102 RayTmaxKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7060, 10), 107}, // 103 RayTmaxNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7028, 11), 106}, // 104 RayTminKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7039, 10), 106}, // 105 RayTminNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6147, 29), 76}, // 106 RemainingRecursionLevelsAMDX in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7613, 10), 123}, // 107 SMCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7632, 7), 125}, // 108 SMIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5054, 9), 24}, // 109 SampleId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5096, 11), 26}, // 110 SampleMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5081, 15), 25}, // 111 SamplePosition in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6246, 20), 79}, // 112 SecondaryPositionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6285, 24), 80}, // 113 SecondaryViewportMaskNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6194, 16), 77}, // 114 ShaderIndexAMDX in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5863, 15), 64}, // 115 ShadingRateKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5536, 15), 53}, // 116 SubgroupEqMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5551, 18), 53}, // 117 SubgroupEqMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5591, 15), 54}, // 118 SubgroupGeMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5606, 18), 54}, // 119 SubgroupGeMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5624, 15), 55}, // 120 SubgroupGtMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5639, 18), 55}, // 121 SubgroupGtMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5398, 11), 44}, // 122 SubgroupId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5657, 15), 56}, // 123 SubgroupLeMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5672, 18), 56}, // 124 SubgroupLeMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5409, 26), 45}, // 125 SubgroupLocalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5690, 15), 57}, // 126 SubgroupLtMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5705, 18), 57}, // 127 SubgroupLtMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5348, 16), 41}, // 128 SubgroupMaxSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5301, 13), 40}, // 129 SubgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6409, 12), 84}, // 130 TaskCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4997, 10), 19}, // 131 TessCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4982, 15), 18}, // 132 TessLevelInner in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4967, 15), 17}, // 133 TessLevelOuter in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5927, 18), 67}, // 134 TileApronSizeQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5909, 18), 66}, // 135 TileDimensionQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5878, 15), 65}, // 136 TileOffsetQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4750, 9), 11}, // 137 VertexId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5435, 12), 46}, // 138 VertexIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5843, 10), 63}, // 139 ViewIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4919, 14), 16}, // 140 ViewportIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6210, 15), 78}, // 141 ViewportMaskNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6347, 22), 82}, // 142 ViewportMaskPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5513, 10), 51}, // 143 WarpIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7623, 9), 124}, // 144 WarpIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5523, 13), 52}, // 145 WarpMaxIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7581, 13), 122}, // 146 WarpsPerSMNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5232, 8), 35}, // 147 WorkDim in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5162, 12), 31}, // 148 WorkgroupId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5148, 14), 30}, // 149 WorkgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6907, 21), 103}, // 150 WorldRayDirectionKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6928, 20), 103}, // 151 WorldRayDirectionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6872, 18), 102}, // 152 WorldRayOriginKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6890, 17), 102}, // 153 WorldRayOriginNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7148, 17), 110}, // 154 WorldToObjectKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7165, 16), 110}, // 155 WorldToObjectNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4595, 10), 137}, // 156 Addresses in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12785, 34), 357}, // 157 ArbitraryPrecisionFixedPointINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12473, 37), 345}, // 158 ArbitraryPrecisionFloatingPointINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12441, 32), 344}, // 159 ArbitraryPrecisionIntegersINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13335, 19), 381}, // 160 ArithmeticFenceEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12106, 9), 330}, // 161 AsmINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13252, 20), 377}, // 162 AtomicFloat16AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12161, 23), 333}, // 163 AtomicFloat16MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11634, 22), 308}, // 164 AtomicFloat16VectorNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13168, 20), 373}, // 165 AtomicFloat32AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12115, 23), 331}, // 166 AtomicFloat32MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13188, 20), 374}, // 167 AtomicFloat64AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12138, 23), 332}, // 168 AtomicFloat64MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7989, 14), 153}, // 169 AtomicStorage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9346, 17), 228}, // 170 AtomicStorageOps in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13293, 24), 379}, // 171 BFloat16ConversionINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9957, 29), 261}, // 172 BFloat16CooperativeMatrixKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9935, 22), 260}, // 173 BFloat16DotProductKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9919, 16), 259}, // 174 BFloat16TypeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13856, 20), 401}, // 175 BindlessImagesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11571, 18), 305}, // 176 BindlessTextureNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13112, 16), 370}, // 177 BitInstructions in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12884, 19), 361}, // 178 BlockingPipesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13817, 19), 399}, // 179 CacheControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4724, 13), 163}, // 180 ClipDistance in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11229, 32), 294}, // 181 ComputeDerivativeGroupLinearKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11261, 31), 294}, // 182 ComputeDerivativeGroupLinearNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10109, 31), 273}, // 183 ComputeDerivativeGroupQuadsKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10140, 30), 273}, // 184 ComputeDerivativeGroupQuadsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11811, 30), 317}, // 185 CooperativeMatrixBlockLoadsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11704, 31), 314}, // 186 CooperativeMatrixConversionsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9898, 21), 368}, // 187 CooperativeMatrixKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8950, 28), 210}, // 188 CooperativeMatrixLayoutsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11317, 20), 296}, // 189 CooperativeMatrixNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11735, 40), 315}, // 190 CooperativeMatrixPerElementOperationsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11674, 30), 313}, // 191 CooperativeMatrixReductionsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11775, 36), 316}, // 192 CooperativeMatrixTensorAddressingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11614, 20), 307}, // 193 CooperativeVectorNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11841, 28), 318}, // 194 CooperativeVectorTrainingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5471, 16), 203}, // 195 CoreBuiltinsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4737, 13), 164}, // 196 CullDistance in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13272, 21), 378}, // 197 DebugInfoModuleINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11440, 25), 301}, // 198 DemoteToHelperInvocation in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11465, 28), 301}, // 199 DemoteToHelperInvocationEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9485, 18), 234}, // 200 DenormFlushToZero in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9470, 15), 233}, // 201 DenormPreserve in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8436, 18), 182}, // 202 DerivativeControl in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7960, 14), 151}, // 203 DeviceEnqueue in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5831, 12), 224}, // 204 DeviceGroup in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11493, 23), 302}, // 205 DisplacementMicromapNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13063, 11), 366}, // 206 DotProduct in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12957, 22), 364}, // 207 DotProductInput4x8Bit in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12979, 25), 364}, // 208 DotProductInput4x8BitKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13004, 28), 365}, // 209 DotProductInput4x8BitPacked in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13032, 31), 365}, // 210 DotProductInput4x8BitPackedKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12916, 19), 363}, // 211 DotProductInputAll in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12935, 22), 363}, // 212 DotProductInputAllKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13074, 14), 366}, // 213 DotProductKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5734, 15), 215}, // 214 DrawParameters in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12218, 16), 336}, // 215 ExpectAssumeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12421, 20), 343}, // 216 FPFastMathModeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13469, 28), 387}, // 217 FPGAArgumentInterfacesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12761, 24), 356}, // 218 FPGABufferLocationINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12634, 27), 351}, // 219 FPGAClusterAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13354, 29), 382}, // 220 FPGAClusterAttributesV2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12675, 20), 353}, // 221 FPGADSPControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12721, 40), 355}, // 222 FPGAInvocationPipeliningAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12584, 26), 349}, // 223 FPGAKernelAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13383, 28), 383}, // 224 FPGAKernelAttributesv2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13445, 24), 386}, // 225 FPGALatencyControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12540, 22), 347}, // 226 FPGALoopControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12610, 24), 350}, // 227 FPGAMemoryAccessesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12395, 26), 342}, // 228 FPGAMemoryAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12903, 13), 362}, // 229 FPGARegINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13429, 16), 385}, // 230 FPMaxErrorINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7874, 8), 142}, // 231 Float16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7860, 14), 141}, // 232 Float16Buffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9738, 16), 248}, // 233 Float16ImageAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7882, 8), 143}, // 234 Float64 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8988, 27), 212}, // 235 Float8CooperativeMatrixEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8978, 10), 211}, // 236 Float8EXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13153, 15), 372}, // 237 FloatControls2 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12014, 23), 326}, // 238 FloatingPointModeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6575, 23), 272}, // 239 FragmentBarycentricKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10087, 22), 272}, // 240 FragmentBarycentricNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6664, 19), 274}, // 241 FragmentDensityEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6385, 24), 268}, // 242 FragmentFullyCoveredEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9776, 16), 250}, // 243 FragmentMaskAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11408, 32), 300}, // 244 FragmentShaderPixelInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11337, 33), 297}, // 245 FragmentShaderSampleInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11370, 38), 298}, // 246 FragmentShaderShadingRateInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5796, 23), 213}, // 247 FragmentShadingRateKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12369, 26), 341}, // 248 FunctionFloatControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12060, 22), 328}, // 249 FunctionPointersINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8281, 15), 169}, // 250 GenericPointer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4782, 9), 135}, // 251 Geometry in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8031, 18), 156}, // 252 GeometryPointSize in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10015, 28), 263}, // 253 GeometryShaderPassthroughNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8494, 16), 185}, // 254 GeometryStreams in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13527, 35), 389}, // 255 GlobalVariableFPGADecorationsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13497, 30), 388}, // 256 GlobalVariableHostAccessINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5314, 16), 192}, // 257 GroupNonUniform in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8633, 26), 194}, // 258 GroupNonUniformArithmetic in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5569, 22), 195}, // 259 GroupNonUniformBallot in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8713, 25), 198}, // 260 GroupNonUniformClustered in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10184, 29), 275}, // 261 GroupNonUniformPartitionedNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8738, 20), 199}, // 262 GroupNonUniformQuad in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13128, 25), 371}, // 263 GroupNonUniformRotateKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8659, 23), 196}, // 264 GroupNonUniformShuffle in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8682, 31), 197}, // 265 GroupNonUniformShuffleRelative in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8613, 20), 193}, // 266 GroupNonUniformVote in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13739, 26), 396}, // 267 GroupUniformArithmeticKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7953, 7), 150}, // 268 Groups in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12871, 13), 360}, // 269 IOPipesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8350, 8), 175}, // 270 Image1D in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7909, 11), 146}, // 271 ImageBasic in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8372, 12), 178}, // 272 ImageBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8227, 15), 165}, // 273 ImageCubeArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10070, 17), 270}, // 274 ImageFootprintNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9754, 22), 249}, // 275 ImageGatherBiasLodAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8049, 20), 157}, // 276 ImageGatherExtended in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8384, 13), 179}, // 277 ImageMSArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7935, 12), 148}, // 278 ImageMipmap in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8425, 11), 181}, // 279 ImageQuery in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7920, 15), 147}, // 280 ImageReadWrite in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9792, 21), 252}, // 281 ImageReadWriteLodAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8259, 10), 167}, // 282 ImageRect in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12082, 24), 329}, // 283 IndirectReferencesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8301, 16), 171}, // 284 InputAttachment in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10299, 36), 278}, // 285 InputAttachmentArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10335, 39), 278}, // 286 InputAttachmentArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10840, 39), 285}, // 287 InputAttachmentArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10879, 42), 285}, // 288 InputAttachmentArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8003, 6), 154}, // 289 Int16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9871, 27), 258}, // 290 Int4CooperativeMatrixINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9857, 14), 257}, // 291 Int4TypeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7890, 6), 144}, // 292 Int64 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7896, 13), 145}, // 293 Int64Atomics in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9813, 14), 253}, // 294 Int64ImageEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8296, 5), 170}, // 295 Int8 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12037, 23), 327}, // 296 IntegerFunctions2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8454, 22), 183}, // 297 InterpolationFunction in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4549, 7), 139}, // 298 Kernel in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12562, 22), 348}, // 299 KernelAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7843, 8), 138}, // 300 Linkage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7974, 15), 152}, // 301 LiteralSampler in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13208, 20), 375}, // 302 LongCompositesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12661, 14), 352}, // 303 LoopFuseINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13792, 25), 398}, // 304 MaskedGatherScatterINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7836, 7), 133}, // 305 Matrix in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12695, 26), 354}, // 306 MemoryAccessAliasingINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4845, 15), 271}, // 307 MeshShadingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4831, 14), 269}, // 308 MeshShadingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8333, 7), 173}, // 309 MinLod in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5853, 10), 225}, // 310 MultiView in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4933, 14), 188}, // 311 MultiViewport in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8588, 13), 190}, // 312 NamedBarrier in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13228, 11), 376}, // 313 OptNoneEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13239, 13), 376}, // 314 OptNoneINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6327, 20), 267}, // 315 PerViewAttributesNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4667, 31), 293}, // 316 PhysicalStorageBufferAddresses in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11195, 34), 293}, // 317 PhysicalStorageBufferAddressesEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8601, 12), 191}, // 318 PipeStorage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7947, 6), 149}, // 319 Pipes in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9842, 15), 256}, // 320 QuadControlKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11656, 18), 310}, // 321 RawAccessChainsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7821, 15), 367}, // 322 RayCullMaskKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9583, 12), 239}, // 323 RayQueryKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11589, 25), 306}, // 324 RayQueryPositionFetchKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9560, 23), 238}, // 325 RayQueryProvisionalKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7768, 41), 319}, // 326 RayTracingClusterAccelerationStructureNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7340, 33), 309}, // 327 RayTracingDisplacementMicromapNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4817, 14), 242}, // 328 RayTracingKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7522, 39), 312}, // 329 RayTracingLinearSweptSpheresGeometryNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7226, 23), 290}, // 330 RayTracingMotionBlurNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4804, 13), 289}, // 331 RayTracingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11516, 29), 303}, // 332 RayTracingOpacityMicromapEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7279, 27), 288}, // 333 RayTracingPositionFetchKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11292, 25), 295}, // 334 RayTracingProvisionalKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7483, 28), 311}, // 335 RayTracingSpheresGeometryNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9614, 32), 241}, // 336 RayTraversalPrimitiveCullingKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13836, 20), 400}, // 337 RegisterLimitsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13088, 24), 369}, // 338 ReplicatedCompositesEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11993, 21), 325}, // 339 RoundToInfinityINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9528, 16), 236}, // 340 RoundingModeRTE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9544, 16), 237}, // 341 RoundingModeRTZ in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12842, 29), 359}, // 342 RuntimeAlignedAttributeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10250, 23), 277}, // 343 RuntimeDescriptorArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10273, 26), 277}, // 344 RuntimeDescriptorArrayEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9986, 29), 262}, // 345 SampleMaskOverrideCoverageNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9363, 28), 229}, // 346 SampleMaskPostDepthCoverage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5063, 18), 166}, // 347 SampleRateShading in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8340, 10), 174}, // 348 Sampled1D in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8358, 14), 177}, // 349 SampledBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8242, 17), 176}, // 350 SampledCubeArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8127, 33), 160}, // 351 SampledImageArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10613, 36), 282}, // 352 SampledImageArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10649, 39), 282}, // 353 SampledImageArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8269, 12), 168}, // 354 SampledRect in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4707, 7), 134}, // 355 Shader in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9827, 15), 254}, // 356 ShaderClockKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6176, 18), 255}, // 357 ShaderEnqueueAMDX in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11545, 26), 304}, // 358 ShaderInvocationReorderNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4879, 12), 200}, // 359 ShaderLayer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10213, 17), 276}, // 360 ShaderNonUniform in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10230, 20), 276}, // 361 ShaderNonUniformEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7594, 19), 299}, // 362 ShaderSMBuiltinsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6266, 19), 266}, // 363 ShaderStereoViewNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4947, 20), 201}, // 364 ShaderViewportIndex in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4891, 28), 264}, // 365 ShaderViewportIndexLayerEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10043, 27), 264}, // 366 ShaderViewportIndexLayerNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6225, 21), 265}, // 367 ShaderViewportMaskNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10170, 14), 274}, // 368 ShadingRateNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9503, 25), 235}, // 369 SignedZeroInfNanPreserve in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8317, 16), 172}, // 370 SparseResidency in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13317, 18), 380}, // 371 SplitBarrierINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6130, 17), 251}, // 372 StencilExportEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9151, 25), 220}, // 373 StorageBuffer16BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9391, 24), 230}, // 374 StorageBuffer8BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8160, 34), 161}, // 375 StorageBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10688, 37), 283}, // 376 StorageBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10725, 40), 283}, // 377 StorageBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8194, 33), 162}, // 378 StorageImageArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10765, 36), 284}, // 379 StorageImageArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10801, 39), 284}, // 380 StorageImageArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8397, 28), 180}, // 381 StorageImageExtendedFormats in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8069, 24), 158}, // 382 StorageImageMultisample in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8510, 30), 186}, // 383 StorageImageReadWithoutFormat in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8540, 31), 187}, // 384 StorageImageWriteWithoutFormat in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9278, 21), 223}, // 385 StorageInputOutput16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9256, 22), 222}, // 386 StoragePushConstant16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9449, 21), 232}, // 387 StoragePushConstant8 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8873, 37), 208}, // 388 StorageTensorArrayDynamicIndexingARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8910, 40), 209}, // 389 StorageTensorArrayNonUniformIndexingARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10455, 39), 280}, // 390 StorageTexelBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10494, 42), 280}, // 391 StorageTexelBufferArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11008, 42), 287}, // 392 StorageTexelBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11050, 45), 287}, // 393 StorageTexelBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9239, 17), 221}, // 394 StorageUniform16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9176, 28), 220}, // 395 StorageUniformBufferBlock16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13590, 23), 391}, // 396 Subgroup2DBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13613, 30), 392}, // 397 Subgroup2DBlockTransformINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13643, 30), 393}, // 398 Subgroup2DBlockTransposeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12305, 39), 339}, // 399 SubgroupAvcMotionEstimationChromaINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12234, 33), 337}, // 400 SubgroupAvcMotionEstimationINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12267, 38), 338}, // 401 SubgroupAvcMotionEstimationIntraINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5330, 18), 214}, // 402 SubgroupBallotKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11909, 27), 322}, // 403 SubgroupBufferBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13562, 28), 390}, // 404 SubgroupBufferPrefetchINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8571, 17), 189}, // 405 SubgroupDispatch in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11936, 26), 323}, // 406 SubgroupImageBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11962, 31), 324}, // 407 SubgroupImageMediaBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13673, 38), 394}, // 408 SubgroupMatrixMultiplyAccumulateINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11888, 21), 321}, // 409 SubgroupShuffleINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9135, 16), 219}, // 410 SubgroupVoteKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13411, 18), 384}, // 411 TaskSequenceINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11869, 19), 320}, // 412 TensorAddressingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13765, 27), 397}, // 413 TensorFloat32RoundingINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8862, 11), 207}, // 414 TensorsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13711, 28), 395}, // 415 TernaryBitwiseFunctionINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4791, 13), 136}, // 416 Tessellation in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8009, 22), 155}, // 417 TessellationPointSize in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9715, 23), 247}, // 418 TextureBlockMatch2QCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9693, 22), 245}, // 419 TextureBlockMatchQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9672, 21), 244}, // 420 TextureBoxFilterQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9646, 26), 243}, // 421 TextureSampleWeightedQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8776, 28), 204}, // 422 TileImageColorReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8804, 28), 205}, // 423 TileImageDepthReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8832, 30), 206}, // 424 TileImageStencilReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5893, 16), 246}, // 425 TileShadingQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8476, 18), 184}, // 426 TransformFeedback in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12819, 23), 358}, // 427 USMStorageClassesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9204, 35), 221}, // 428 UniformAndStorageBuffer16BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9415, 34), 231}, // 429 UniformAndStorageBuffer8BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8093, 34), 159}, // 430 UniformBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10536, 37), 281}, // 431 UniformBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10573, 40), 281}, // 432 UniformBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8758, 18), 202}, // 433 UniformDecoration in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10374, 39), 279}, // 434 UniformTexelBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10413, 42), 279}, // 435 UniformTexelBufferArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10921, 42), 286}, // 436 UniformTexelBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10963, 45), 286}, // 437 UniformTexelBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12510, 30), 346}, // 438 UnstructuredLoopControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9595, 19), 240}, // 439 UntypedPointersKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12344, 25), 340}, // 440 VariableLengthArrayINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9329, 17), 227}, // 441 VariablePointers in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9299, 30), 226}, // 442 VariablePointersStorageBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7851, 9), 140}, // 443 Vector16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12203, 15), 335}, // 444 VectorAnyINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12184, 19), 334}, // 445 VectorComputeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11095, 18), 291}, // 446 VulkanMemoryModel in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11134, 29), 292}, // 447 VulkanMemoryModelDeviceScope in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11163, 32), 292}, // 448 VulkanMemoryModelDeviceScopeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11113, 21), 291}, // 449 VulkanMemoryModelKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9091, 44), 218}, // 450 WorkgroupMemoryExplicitLayout16BitAccessKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9048, 43), 217}, // 451 WorkgroupMemoryExplicitLayout8BitAccessKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9015, 33), 216}, // 452 WorkgroupMemoryExplicitLayoutKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13888, 8), 403}, // 453 Address in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13896, 8), 404}, // 454 Boolean in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13904, 6), 405}, // 455 Float in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13910, 7), 406}, // 456 Signed in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13917, 11), 407}, // 457 SignedChar in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13928, 9), 408}, // 458 Unsigned in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13937, 13), 409}, // 459 UnsignedChar in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13876, 12), 402}, // 460 Unspecified in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13950, 6), 410}, // 461 Class in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(13956, 10), 411}, // 462 Structure in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(13966, 6), 412}, // 463 Union in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(13987, 20), 414}, // 464 ImportedDeclaration in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(13972, 15), 413}, // 465 ImportedModule in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(14096, 15), 422}, // 466 FlagArtificial in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14111, 13), 423}, // 467 FlagExplicit in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14084, 12), 421}, // 468 FlagFwdDecl in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14174, 21), 427}, // 469 FlagIndirectVariable in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14067, 17), 420}, // 470 FlagIsDefinition in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14251, 16), 431}, // 471 FlagIsEnumClass in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14055, 12), 419}, // 472 FlagIsLocal in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14235, 16), 430}, // 473 FlagIsOptimized in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14028, 14), 417}, // 474 FlagIsPrivate in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14012, 16), 416}, // 475 FlagIsProtected in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14042, 13), 418}, // 476 FlagIsPublic in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14195, 20), 428}, // 477 FlagLValueReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14139, 18), 425}, // 478 FlagObjectPointer in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14124, 15), 424}, // 479 FlagPrototyped in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14215, 20), 429}, // 480 FlagRValueReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14157, 17), 426}, // 481 FlagStaticMember in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14287, 24), 433}, // 482 FlagTypePassByReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14267, 20), 432}, // 483 FlagTypePassByValue in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14007, 5), 415}, // 484 None in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14372, 9), 438}, // 485 BitPiece in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14404, 7), 442}, // 486 Constu in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14311, 6), 434}, // 487 Deref in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14411, 9), 443}, // 488 Fragment in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14322, 6), 436}, // 489 Minus in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14317, 5), 435}, // 490 Plus in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14361, 11), 437}, // 491 PlusUconst in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14393, 11), 441}, // 492 StackValue in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14381, 5), 439}, // 493 Swap in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14386, 7), 440}, // 494 Xderef in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14456, 11), 447}, // 495 AtomicType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14420, 10), 444}, // 496 ConstType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14443, 13), 446}, // 497 RestrictType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14430, 13), 445}, // 498 VolatileType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14467, 10), 448}, // 499 Float16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14477, 10), 449}, // 500 Float32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14487, 10), 450}, // 501 Float64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14655, 12), 461}, // 502 FloatE4M3NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14667, 12), 462}, // 503 FloatE5M2NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14510, 14), 452}, // 504 SignedInt16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14524, 14), 453}, // 505 SignedInt32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14538, 14), 454}, // 506 SignedInt64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14497, 13), 451}, // 507 SignedInt8NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14615, 19), 459}, // 508 SignedInt8PackedNV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14567, 16), 456}, // 509 UnsignedInt16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14583, 16), 457}, // 510 UnsignedInt32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14599, 16), 458}, // 511 UnsignedInt64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14552, 15), 455}, // 512 UnsignedInt8NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14634, 21), 460}, // 513 UnsignedInt8PackedNV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14731, 28), 466}, // 514 ColumnBlockedInterleavedARM in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(14691, 15), 464}, // 515 ColumnMajorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(14706, 25), 465}, // 516 RowBlockedInterleavedARM in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(14679, 12), 463}, // 517 RowMajorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(14767, 27), 468}, // 518 MatrixASignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(14794, 27), 469}, // 519 MatrixBSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(14821, 27), 470}, // 520 MatrixCSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(14848, 32), 471}, // 521 MatrixResultSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(14759, 8), 467}, // 522 NoneKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(14880, 26), 472}, // 523 SaturatingAccumulationKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(14917, 4), 475}, // 524 2x2 in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(14910, 7), 474}, // 525 Column in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(14906, 4), 473}, // 526 Row in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(14921, 11), 476}, // 527 MatrixAKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(14943, 21), 478}, // 528 MatrixAccumulatorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(14932, 11), 477}, // 529 MatrixBKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(14975, 14), 480}, // 530 ColumnMajorNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(14989, 21), 481}, // 531 InferencingOptimalNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(14964, 11), 479}, // 532 RowMajorNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(15010, 18), 482}, // 533 TrainingOptimalNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(13888, 8), 484}, // 534 Address in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13896, 8), 485}, // 535 Boolean in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13904, 6), 486}, // 536 Float in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13910, 7), 487}, // 537 Signed in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13917, 11), 488}, // 538 SignedChar in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13928, 9), 489}, // 539 Unsigned in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13937, 13), 490}, // 540 UnsignedChar in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13876, 12), 483}, // 541 Unspecified in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13950, 6), 491}, // 542 Class in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(13956, 10), 492}, // 543 Structure in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(13966, 6), 493}, // 544 Union in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(14096, 15), 501}, // 545 FlagArtificial in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14111, 13), 502}, // 546 FlagExplicit in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14084, 12), 500}, // 547 FlagFwdDecl in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14174, 21), 506}, // 548 FlagIndirectVariable in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14067, 17), 499}, // 549 FlagIsDefinition in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14055, 12), 498}, // 550 FlagIsLocal in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14235, 16), 509}, // 551 FlagIsOptimized in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14028, 14), 496}, // 552 FlagIsPrivate in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14012, 16), 495}, // 553 FlagIsProtected in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14042, 13), 497}, // 554 FlagIsPublic in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14195, 20), 507}, // 555 FlagLValueReference in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14139, 18), 504}, // 556 FlagObjectPointer in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14124, 15), 503}, // 557 FlagPrototyped in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14215, 20), 508}, // 558 FlagRValueReference in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14157, 17), 505}, // 559 FlagStaticMember in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14007, 5), 494}, // 560 None in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14372, 9), 514}, // 561 BitPiece in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14404, 7), 518}, // 562 Constu in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14311, 6), 510}, // 563 Deref in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14322, 6), 512}, // 564 Minus in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14317, 5), 511}, // 565 Plus in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14361, 11), 513}, // 566 PlusUconst in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14393, 11), 517}, // 567 StackValue in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14381, 5), 515}, // 568 Swap in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14386, 7), 516}, // 569 Xderef in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14420, 10), 519}, // 570 ConstType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(14443, 13), 521}, // 571 RestrictType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(14430, 13), 520}, // 572 VolatileType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(17252, 16), 636}, // 573 AliasScopeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15237, 8), 541}, // 574 Aliased in SPV_OPERAND_TYPE_DECORATION
  {IR(16355, 15), 594}, // 575 AliasedPointer in SPV_OPERAND_TYPE_DECORATION
  {IR(16370, 18), 594}, // 576 AliasedPointerEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(15715, 10), 565}, // 577 Alignment in SPV_OPERAND_TYPE_DECORATION
  {IR(15759, 12), 567}, // 578 AlignmentId in SPV_OPERAND_TYPE_DECORATION
  {IR(15088, 12), 528}, // 579 ArrayStride in SPV_OPERAND_TYPE_DECORATION
  {IR(17033, 14), 624}, // 580 BankBitsINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16872, 15), 617}, // 581 BankwidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15392, 8), 554}, // 582 Binding in SPV_OPERAND_TYPE_DECORATION
  {IR(16436, 16), 597}, // 583 BindlessImageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16418, 18), 596}, // 584 BindlessSamplerNV in SPV_OPERAND_TYPE_DECORATION
  {IR(15052, 6), 524}, // 585 Block in SPV_OPERAND_TYPE_DECORATION
  {IR(15899, 22), 574}, // 586 BlockMatchSamplerQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(15877, 22), 573}, // 587 BlockMatchTextureQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(16467, 13), 599}, // 588 BoundImageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16452, 15), 598}, // 589 BoundSamplerNV in SPV_OPERAND_TYPE_DECORATION
  {IR(15058, 12), 525}, // 590 BufferBlock in SPV_OPERAND_TYPE_DECORATION
  {IR(17345, 20), 641}, // 591 BufferLocationINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15169, 8), 533}, // 592 BuiltIn in SPV_OPERAND_TYPE_DECORATION
  {IR(17115, 19), 629}, // 593 BurstCoalesceINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15135, 8), 532}, // 594 CPacked in SPV_OPERAND_TYPE_DECORATION
  {IR(18138, 22), 663}, // 595 CacheControlLoadINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18197, 23), 664}, // 596 CacheControlStoreINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17134, 15), 630}, // 597 CacheSizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15202, 9), 537}, // 598 Centroid in SPV_OPERAND_TYPE_DECORATION
  {IR(16520, 13), 602}, // 599 ClobberINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15263, 9), 544}, // 600 Coherent in SPV_OPERAND_TYPE_DECORATION
  {IR(15079, 9), 527}, // 601 ColMajor in SPV_OPERAND_TYPE_DECORATION
  {IR(15376, 10), 552}, // 602 Component in SPV_OPERAND_TYPE_DECORATION
  {IR(17654, 27), 651}, // 603 ConduitKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15254, 9), 543}, // 604 Constant in SPV_OPERAND_TYPE_DECORATION
  {IR(16666, 14), 609}, // 605 CounterBuffer in SPV_OPERAND_TYPE_DECORATION
  {IR(15400, 14), 555}, // 606 DescriptorSet in SPV_OPERAND_TYPE_DECORATION
  {IR(17149, 28), 631}, // 607 DontStaticallyCoalesceINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16925, 16), 620}, // 608 DoublepumpINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15921, 18), 575}, // 609 ExplicitInterpAMD in SPV_OPERAND_TYPE_DECORATION
  {IR(15585, 15), 561}, // 610 FPFastMathMode in SPV_OPERAND_TYPE_DECORATION
  {IR(17573, 26), 648}, // 611 FPMaxErrorDecorationINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15535, 15), 560}, // 612 FPRoundingMode in SPV_OPERAND_TYPE_DECORATION
  {IR(15191, 5), 535}, // 613 Flat in SPV_OPERAND_TYPE_DECORATION
  {IR(17047, 20), 625}, // 614 ForcePow2DepthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15487, 14), 559}, // 615 FuncParamAttr in SPV_OPERAND_TYPE_DECORATION
  {IR(16577, 21), 605}, // 616 FuncParamIOKindINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16808, 24), 613}, // 617 FunctionDenormModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17418, 31), 643}, // 618 FunctionFloatingPointModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16751, 26), 612}, // 619 FunctionRoundingModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17208, 25), 634}, // 620 FuseLoopsInFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15124, 11), 531}, // 621 GLSLPacked in SPV_OPERAND_TYPE_DECORATION
  {IR(15113, 11), 530}, // 622 GLSLShared in SPV_OPERAND_TYPE_DECORATION
  {IR(16640, 26), 608}, // 623 GlobalVariableOffsetINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16388, 30), 595}, // 624 HitObjectShaderRecordBufferNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16680, 24), 609}, // 625 HlslCounterBufferGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(16717, 19), 610}, // 626 HlslSemanticGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(17997, 16), 660}, // 627 HostAccessINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17365, 19), 642}, // 628 IOPipeStorageINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18074, 28), 662}, // 629 ImplementInRegisterMapINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15386, 6), 553}, // 630 Index in SPV_OPERAND_TYPE_DECORATION
  {IR(18060, 14), 661}, // 631 InitModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17281, 24), 638}, // 632 InitiationIntervalINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15694, 21), 564}, // 633 InputAttachmentIndex in SPV_OPERAND_TYPE_DECORATION
  {IR(15218, 10), 539}, // 634 Invariant in SPV_OPERAND_TYPE_DECORATION
  {IR(17624, 30), 650}, // 635 LatencyControlConstraintINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17599, 25), 649}, // 636 LatencyControlLabelINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15662, 18), 562}, // 637 LinkageAttributes in SPV_OPERAND_TYPE_DECORATION
  {IR(15367, 9), 551}, // 638 Location in SPV_OPERAND_TYPE_DECORATION
  {IR(17712, 33), 653}, // 639 MMHostInterfaceAddressWidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17745, 30), 654}, // 640 MMHostInterfaceDataWidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17775, 28), 655}, // 641 MMHostInterfaceLatencyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17871, 29), 657}, // 642 MMHostInterfaceMaxBurstINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17837, 34), 656}, // 643 MMHostInterfaceReadWriteModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17900, 32), 658}, // 644 MMHostInterfaceWaitRequestINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17233, 19), 635}, // 645 MathOpDSPModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15100, 13), 529}, // 646 MatrixStride in SPV_OPERAND_TYPE_DECORATION
  {IR(15725, 14), 566}, // 647 MaxByteOffset in SPV_OPERAND_TYPE_DECORATION
  {IR(15771, 16), 568}, // 648 MaxByteOffsetId in SPV_OPERAND_TYPE_DECORATION
  {IR(17305, 20), 639}, // 649 MaxConcurrencyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16887, 22), 618}, // 650 MaxPrivateCopiesINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16941, 19), 621}, // 651 MaxReplicatesINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17509, 18), 646}, // 652 MediaBlockIOINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16846, 12), 615}, // 653 MemoryINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16980, 11), 623}, // 654 MergeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17268, 13), 637}, // 655 NoAliasINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15680, 14), 563}, // 656 NoContraction in SPV_OPERAND_TYPE_DECORATION
  {IR(15177, 14), 534}, // 657 NoPerspective in SPV_OPERAND_TYPE_DECORATION
  {IR(15831, 13), 570}, // 658 NoSignedWrap in SPV_OPERAND_TYPE_DECORATION
  {IR(15844, 15), 571}, // 659 NoUnsignedWrap in SPV_OPERAND_TYPE_DECORATION
  {IR(15971, 20), 577}, // 660 NodeMaxPayloadsAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(15939, 32), 576}, // 661 NodeSharesPayloadLimitsWithAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(15284, 12), 546}, // 662 NonReadable in SPV_OPERAND_TYPE_DECORATION
  {IR(16295, 11), 592}, // 663 NonUniform in SPV_OPERAND_TYPE_DECORATION
  {IR(16306, 14), 592}, // 664 NonUniformEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(15272, 12), 545}, // 665 NonWritable in SPV_OPERAND_TYPE_DECORATION
  {IR(16858, 14), 616}, // 666 NumbanksINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15414, 7), 556}, // 667 Offset in SPV_OPERAND_TYPE_DECORATION
  {IR(16139, 19), 584}, // 668 OverrideCoverageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16158, 14), 585}, // 669 PassthroughNV in SPV_OPERAND_TYPE_DECORATION
  {IR(15196, 6), 536}, // 670 Patch in SPV_OPERAND_TYPE_DECORATION
  {IR(16111, 28), 583}, // 671 PayloadDispatchIndirectAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(16086, 25), 582}, // 672 PayloadNodeArraySizeAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(16034, 25), 580}, // 673 PayloadNodeBaseIndexAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(16014, 20), 579}, // 674 PayloadNodeNameAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(16059, 27), 581}, // 675 PayloadNodeSparseArrayAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(16219, 16), 588}, // 676 PerPrimitiveEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(16235, 15), 588}, // 677 PerPrimitiveNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16260, 10), 590}, // 678 PerTaskNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16270, 13), 591}, // 679 PerVertexKHR in SPV_OPERAND_TYPE_DECORATION
  {IR(16283, 12), 591}, // 680 PerVertexNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16250, 10), 589}, // 681 PerViewNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17325, 20), 640}, // 682 PipelineEnableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17177, 14), 632}, // 683 PrefetchINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16494, 26), 601}, // 684 ReferencedIndirectlyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16832, 14), 614}, // 685 RegisterINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17681, 31), 652}, // 686 RegisterMapKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15028, 17), 522}, // 687 RelaxedPrecision in SPV_OPERAND_TYPE_DECORATION
  {IR(15228, 9), 540}, // 688 Restrict in SPV_OPERAND_TYPE_DECORATION
  {IR(16320, 16), 593}, // 689 RestrictPointer in SPV_OPERAND_TYPE_DECORATION
  {IR(16336, 19), 593}, // 690 RestrictPointerEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(15070, 9), 526}, // 691 RowMajor in SPV_OPERAND_TYPE_DECORATION
  {IR(16480, 14), 600}, // 692 SIMTCallINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15211, 7), 538}, // 693 Sample in SPV_OPERAND_TYPE_DECORATION
  {IR(15340, 20), 549}, // 694 SaturatedConversion in SPV_OPERAND_TYPE_DECORATION
  {IR(15787, 44), 569}, // 695 SaturatedToLargestFloat8NormalConversionEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(16191, 28), 587}, // 696 SecondaryViewportRelativeNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16533, 17), 603}, // 697 SideEffectsINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16960, 20), 622}, // 698 SimpleDualPortINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17449, 25), 644}, // 699 SingleElementVectorINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16909, 16), 619}, // 700 SinglepumpINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15045, 7), 523}, // 701 SpecId in SPV_OPERAND_TYPE_DECORATION
  {IR(17932, 26), 659}, // 702 StableKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16625, 15), 607}, // 703 StackCallINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17191, 17), 633}, // 704 StallEnableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17527, 15), 647}, // 705 StallFreeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15360, 7), 550}, // 706 Stream in SPV_OPERAND_TYPE_DECORATION
  {IR(17067, 16), 626}, // 707 StridesizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15991, 23), 578}, // 708 TrackFinishWritingAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17097, 18), 628}, // 709 TrueDualPortINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15296, 8), 547}, // 710 Uniform in SPV_OPERAND_TYPE_DECORATION
  {IR(15330, 10), 548}, // 711 UniformId in SPV_OPERAND_TYPE_DECORATION
  {IR(16704, 13), 610}, // 712 UserSemantic in SPV_OPERAND_TYPE_DECORATION
  {IR(16736, 15), 611}, // 713 UserTypeGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(17474, 35), 645}, // 714 VectorComputeCallableFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16598, 27), 606}, // 715 VectorComputeFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16550, 27), 604}, // 716 VectorComputeVariableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16172, 19), 586}, // 717 ViewportRelativeNV in SPV_OPERAND_TYPE_DECORATION
  {IR(15245, 9), 542}, // 718 Volatile in SPV_OPERAND_TYPE_DECORATION
  {IR(15859, 18), 572}, // 719 WeightTextureQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(17083, 14), 627}, // 720 WordsizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15421, 10), 557}, // 721 XfbBuffer in SPV_OPERAND_TYPE_DECORATION
  {IR(15431, 10), 558}, // 722 XfbStride in SPV_OPERAND_TYPE_DECORATION
  {IR(18220, 3), 665}, // 723 1D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18223, 3), 666}, // 724 2D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18226, 3), 667}, // 725 3D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18239, 7), 670}, // 726 Buffer in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18229, 5), 668}, // 727 Cube in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18234, 5), 669}, // 728 Rect in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18246, 12), 671}, // 729 SubpassData in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18258, 17), 672}, // 730 TileImageDataEXT in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(19070, 15), 725}, // 731 CoalescingAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18701, 15), 703}, // 732 ContractionOff in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(9485, 18), 717}, // 733 DenormFlushToZero in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(9470, 15), 716}, // 734 DenormPreserve in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18471, 13), 686}, // 735 DepthGreater in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18484, 10), 687}, // 736 DepthLess in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18456, 15), 685}, // 737 DepthReplacing in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18494, 15), 688}, // 738 DepthUnchanged in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19491, 25), 743}, // 739 DerivativeGroupLinearKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19516, 24), 743}, // 740 DerivativeGroupLinearNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19444, 24), 742}, // 741 DerivativeGroupQuadsKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19468, 23), 742}, // 742 DerivativeGroupQuadsNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19018, 29), 723}, // 743 EarlyAndLateFragmentTestsAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18423, 19), 682}, // 744 EarlyFragmentTests in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20001, 18), 762}, // 745 FPFastMathDefault in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18728, 10), 705}, // 746 Finalizer in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19816, 26), 754}, // 747 FloatingPointModeALTINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19842, 27), 755}, // 748 FloatingPointModeIEEEINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18716, 12), 704}, // 749 Initializer in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18545, 11), 692}, // 750 InputLines in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18556, 20), 693}, // 751 InputLinesAdjacency in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18533, 12), 691}, // 752 InputPoints in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18586, 24), 695}, // 753 InputTrianglesAdjacency in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18275, 12), 673}, // 754 Invocations in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19085, 15), 726}, // 755 IsApiEntryAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18616, 9), 697}, // 756 Isolines in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18509, 10), 689}, // 757 LocalSize in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18519, 14), 690}, // 758 LocalSizeHint in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18796, 16), 710}, // 759 LocalSizeHintId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18784, 12), 709}, // 760 LocalSizeId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19100, 21), 727}, // 761 MaxNodeRecursionAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19145, 21), 730}, // 762 MaxNumWorkgroupsAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19891, 16), 757}, // 763 MaxWorkDimINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19869, 22), 756}, // 764 MaxWorkgroupSizeINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19977, 24), 761}, // 765 MaximallyReconvergesKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20092, 22), 766}, // 766 MaximumRegistersINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20114, 24), 767}, // 767 MaximumRegistersIdINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20069, 23), 765}, // 768 NamedBarrierCountINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20189, 27), 768}, // 769 NamedMaximumRegistersINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19907, 20), 758}, // 770 NoGlobalOffsetINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18812, 34), 711}, // 771 NonCoherentColorAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18846, 34), 712}, // 772 NonCoherentDepthAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18880, 36), 713}, // 773 NonCoherentStencilAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18964, 34), 721}, // 774 NonCoherentTileAttachmentReadQCOM in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19927, 22), 759}, // 775 NumSIMDWorkitemsINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18407, 16), 681}, // 776 OriginLowerLeft in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18391, 16), 680}, // 777 OriginUpperLeft in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18653, 16), 700}, // 778 OutputLineStrip in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19376, 15), 740}, // 779 OutputLinesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19391, 14), 740}, // 780 OutputLinesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18640, 13), 699}, // 781 OutputPoints in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19405, 20), 741}, // 782 OutputPrimitivesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19425, 19), 741}, // 783 OutputPrimitivesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18669, 20), 701}, // 784 OutputTriangleStrip in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19540, 19), 744}, // 785 OutputTrianglesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19559, 18), 744}, // 786 OutputTrianglesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18625, 15), 698}, // 787 OutputVertices in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18372, 19), 679}, // 788 PixelCenterInteger in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19577, 25), 745}, // 789 PixelInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19602, 27), 746}, // 790 PixelInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18442, 10), 683}, // 791 PointMode in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18946, 18), 715}, // 792 PostDepthCoverage in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19317, 19), 737}, // 793 QuadDerivativesKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18610, 6), 696}, // 794 Quads in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20043, 26), 764}, // 795 RegisterMapInterfaceINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19336, 20), 738}, // 796 RequireFullQuadsKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(9528, 16), 719}, // 797 RoundingModeRTE in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19795, 21), 753}, // 798 RoundingModeRTNINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19774, 21), 752}, // 799 RoundingModeRTPINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(9544, 16), 720}, // 800 RoundingModeRTZ in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19629, 26), 747}, // 801 SampleInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19655, 28), 748}, // 802 SampleInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19949, 28), 760}, // 803 SchedulerTargetFmaxMhzINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(6194, 16), 729}, // 804 ShaderIndexAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19683, 31), 749}, // 805 ShadingRateInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19714, 33), 750}, // 806 ShadingRateInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19747, 27), 751}, // 807 SharedLocalMemorySizeINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19356, 20), 739}, // 808 SharesInputWithAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(9503, 25), 718}, // 809 SignedZeroInfNanPreserve in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18287, 13), 674}, // 810 SpacingEqual in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18300, 22), 675}, // 811 SpacingFractionalEven in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18322, 21), 676}, // 812 SpacingFractionalOdd in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19121, 24), 728}, // 813 StaticNumWorkgroupsAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19270, 25), 735}, // 814 StencilRefGreaterBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19194, 26), 732}, // 815 StencilRefGreaterFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19295, 22), 736}, // 816 StencilRefLessBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19220, 23), 733}, // 817 StencilRefLessFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19047, 23), 724}, // 818 StencilRefReplacingEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19243, 27), 734}, // 819 StencilRefUnchangedBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19166, 28), 731}, // 820 StencilRefUnchangedFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20019, 24), 763}, // 821 StreamingInterfaceINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(5301, 13), 706}, // 822 SubgroupSize in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18916, 30), 714}, // 823 SubgroupUniformControlFlowKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18738, 22), 707}, // 824 SubgroupsPerWorkgroup in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18760, 24), 708}, // 825 SubgroupsPerWorkgroupId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18998, 20), 722}, // 826 TileShadingRateQCOM in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18576, 10), 694}, // 827 Triangles in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18689, 12), 702}, // 828 VecTypeHint in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18357, 15), 678}, // 829 VertexOrderCcw in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18343, 14), 677}, // 830 VertexOrderCw in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18452, 4), 684}, // 831 Xfb in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20354, 10), 780}, // 832 AnyHitKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20364, 9), 780}, // 833 AnyHitNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20415, 12), 783}, // 834 CallableKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20427, 11), 783}, // 835 CallableNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20373, 14), 781}, // 836 ClosestHitKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20387, 13), 781}, // 837 ClosestHitNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(14411, 9), 773}, // 838 Fragment in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20266, 10), 774}, // 839 GLCompute in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(4782, 9), 772}, // 840 Geometry in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20323, 16), 779}, // 841 IntersectionKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20339, 15), 779}, // 842 IntersectionNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(4549, 7), 775}, // 843 Kernel in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20446, 8), 785}, // 844 MeshEXT in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20283, 7), 777}, // 845 MeshNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20400, 8), 782}, // 846 MissKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20408, 7), 782}, // 847 MissNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20290, 17), 778}, // 848 RayGenerationKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20307, 16), 778}, // 849 RayGenerationNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20438, 8), 784}, // 850 TaskEXT in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20276, 7), 776}, // 851 TaskNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20223, 20), 770}, // 852 TessellationControl in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20243, 23), 771}, // 853 TessellationEvaluation in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20216, 7), 769}, // 854 Vertex in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20463, 12), 787}, // 855 FlushToZero in SPV_OPERAND_TYPE_FPDENORM_MODE
  {IR(20454, 9), 786}, // 856 Preserve in SPV_OPERAND_TYPE_FPDENORM_MODE
  {IR(20475, 12), 788}, // 857 BFloat16KHR in SPV_OPERAND_TYPE_FPENCODING
  {IR(20487, 14), 789}, // 858 Float8E4M3EXT in SPV_OPERAND_TYPE_FPENCODING
  {IR(20501, 14), 790}, // 859 Float8E5M2EXT in SPV_OPERAND_TYPE_FPENCODING
  {IR(20520, 4), 792}, // 860 ALT in SPV_OPERAND_TYPE_FPOPERATION_MODE
  {IR(20515, 5), 791}, // 861 IEEE in SPV_OPERAND_TYPE_FPOPERATION_MODE
  {IR(20558, 14), 799}, // 862 AllowContract in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20572, 23), 799}, // 863 AllowContractFastINTEL in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20595, 13), 800}, // 864 AllowReassoc in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20608, 18), 800}, // 865 AllowReassocINTEL in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20542, 11), 797}, // 866 AllowRecip in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20626, 15), 801}, // 867 AllowTransform in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20553, 5), 798}, // 868 Fast in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20538, 4), 796}, // 869 NSZ in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(14007, 5), 793}, // 870 None in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20531, 7), 795}, // 871 NotInf in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20524, 7), 794}, // 872 NotNaN in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20641, 4), 802}, // 873 RTE in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(20653, 4), 805}, // 874 RTN in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(20649, 4), 804}, // 875 RTP in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(20645, 4), 803}, // 876 RTZ in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(20689, 18), 808}, // 877 Horizontal2Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(20707, 18), 809}, // 878 Horizontal4Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(20657, 16), 806}, // 879 Vertical2Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(20673, 16), 807}, // 880 Vertical4Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(20748, 6), 814}, // 881 Const in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(20732, 11), 812}, // 882 DontInline in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(20725, 7), 811}, // 883 Inline in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(14007, 5), 810}, // 884 None in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(13228, 11), 815}, // 885 OptNoneEXT in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(13239, 13), 815}, // 886 OptNoneINTEL in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(20743, 5), 813}, // 887 Pure in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(20764, 6), 818}, // 888 ByVal in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20775, 8), 820}, // 889 NoAlias in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20783, 10), 821}, // 890 NoCapture in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20801, 12), 823}, // 891 NoReadWrite in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20793, 8), 822}, // 892 NoWrite in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20813, 20), 824}, // 893 RuntimeAlignedINTEL in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20759, 5), 817}, // 894 Sext in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20770, 5), 819}, // 895 Sret in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20754, 5), 816}, // 896 Zext in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20868, 16), 828}, // 897 ClusteredReduce in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(20854, 14), 827}, // 898 ExclusiveScan in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(20840, 14), 826}, // 899 InclusiveScan in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(20931, 27), 831}, // 900 PartitionedExclusiveScanNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(20904, 27), 830}, // 901 PartitionedInclusiveScanNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(20884, 20), 829}, // 902 PartitionedReduceNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(20833, 7), 825}, // 903 Reduce in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(20958, 10), 832}, // 904 NoneINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(20968, 10), 833}, // 905 ReadINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(20989, 15), 835}, // 906 ReadWriteINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(20978, 11), 834}, // 907 WriteINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(21004, 5), 837}, // 908 Bias in SPV_OPERAND_TYPE_IMAGE
  {IR(21018, 12), 840}, // 909 ConstOffset in SPV_OPERAND_TYPE_IMAGE
  {IR(21030, 13), 842}, // 910 ConstOffsets in SPV_OPERAND_TYPE_IMAGE
  {IR(21013, 5), 839}, // 911 Grad in SPV_OPERAND_TYPE_IMAGE
  {IR(21009, 4), 838}, // 912 Lod in SPV_OPERAND_TYPE_IMAGE
  {IR(21043, 19), 845}, // 913 MakeTexelAvailable in SPV_OPERAND_TYPE_IMAGE
  {IR(21062, 22), 845}, // 914 MakeTexelAvailableKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(21084, 17), 846}, // 915 MakeTexelVisible in SPV_OPERAND_TYPE_IMAGE
  {IR(21101, 20), 846}, // 916 MakeTexelVisibleKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(8333, 7), 844}, // 917 MinLod in SPV_OPERAND_TYPE_IMAGE
  {IR(21121, 16), 847}, // 918 NonPrivateTexel in SPV_OPERAND_TYPE_IMAGE
  {IR(21137, 19), 847}, // 919 NonPrivateTexelKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(14007, 5), 836}, // 920 None in SPV_OPERAND_TYPE_IMAGE
  {IR(21209, 12), 851}, // 921 Nontemporal in SPV_OPERAND_TYPE_IMAGE
  {IR(15414, 7), 841}, // 922 Offset in SPV_OPERAND_TYPE_IMAGE
  {IR(21221, 8), 852}, // 923 Offsets in SPV_OPERAND_TYPE_IMAGE
  {IR(15211, 7), 843}, // 924 Sample in SPV_OPERAND_TYPE_IMAGE
  {IR(21187, 11), 849}, // 925 SignExtend in SPV_OPERAND_TYPE_IMAGE
  {IR(21156, 14), 848}, // 926 VolatileTexel in SPV_OPERAND_TYPE_IMAGE
  {IR(21170, 17), 848}, // 927 VolatileTexelKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(21198, 11), 850}, // 928 ZeroExtend in SPV_OPERAND_TYPE_IMAGE
  {IR(13904, 6), 867}, // 929 Float in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21390, 10), 866}, // 930 HalfFloat in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21325, 12), 861}, // 931 SignedInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21337, 12), 862}, // 932 SignedInt32 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21314, 11), 860}, // 933 SignedInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21239, 11), 854}, // 934 SnormInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21229, 10), 853}, // 935 SnormInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21299, 15), 859}, // 936 UnormInt101010 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21411, 17), 869}, // 937 UnormInt101010_2 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21428, 16), 870}, // 938 UnormInt10X6EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21561, 16), 877}, // 939 UnormInt12X4EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21577, 16), 878}, // 940 UnormInt14X2EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21260, 11), 856}, // 941 UnormInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21400, 11), 868}, // 942 UnormInt24 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21484, 20), 873}, // 943 UnormInt2_101010EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21250, 10), 855}, // 944 UnormInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21285, 14), 858}, // 945 UnormShort555 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21271, 14), 857}, // 946 UnormShort565 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21504, 19), 874}, // 947 UnsignedInt10X6EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21523, 19), 875}, // 948 UnsignedInt12X4EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21542, 19), 876}, // 949 UnsignedInt14X2EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21362, 14), 864}, // 950 UnsignedInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21376, 14), 865}, // 951 UnsignedInt32 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21349, 13), 863}, // 952 UnsignedInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21444, 20), 871}, // 953 UnsignedIntRaw10EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21464, 20), 872}, // 954 UnsignedIntRaw12EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21595, 2), 880}, // 955 A in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21696, 5), 898}, // 956 ABGR in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21617, 5), 886}, // 957 ARGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21612, 5), 885}, // 958 BGRA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21654, 6), 892}, // 959 Depth in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21660, 13), 893}, // 960 DepthStencil in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21622, 10), 887}, // 961 Intensity in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21632, 10), 888}, // 962 Luminance in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21593, 2), 879}, // 963 R in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21600, 3), 882}, // 964 RA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21597, 3), 881}, // 965 RG in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21603, 4), 883}, // 966 RGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21607, 5), 884}, // 967 RGBA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21649, 5), 891}, // 968 RGBx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21645, 4), 890}, // 969 RGx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21642, 3), 889}, // 970 Rx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21690, 6), 897}, // 971 sBGRA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21673, 5), 894}, // 972 sRGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21684, 6), 896}, // 973 sRGBA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21678, 6), 895}, // 974 sRGBx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21701, 27), 899}, // 975 InitOnDeviceReprogramINTEL in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(21728, 23), 900}, // 976 InitOnDeviceResetINTEL in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(21751, 7), 901}, // 977 NoWait in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(21758, 11), 902}, // 978 WaitKernel in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(21769, 14), 903}, // 979 WaitWorkGroup in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(21783, 12), 905}, // 980 CmdExecTime in SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {IR(14007, 5), 904}, // 981 None in SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {IR(21795, 13), 907}, // 982 MayUsePrintf in SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {IR(14007, 5), 906}, // 983 None in SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {IR(21808, 7), 908}, // 984 Export in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(21815, 7), 909}, // 985 Import in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(21822, 12), 910}, // 986 LinkOnceODR in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(21848, 12), 912}, // 987 CachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(21900, 17), 915}, // 988 ConstCachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(21875, 25), 914}, // 989 InvalidateAfterReadINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(21860, 15), 913}, // 990 StreamingINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(21834, 14), 911}, // 991 UncachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(22040, 21), 928}, // 992 DependencyArrayINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21935, 19), 919}, // 993 DependencyInfinite in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21954, 17), 920}, // 994 DependencyLength in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21924, 11), 918}, // 995 DontUnroll in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(17281, 24), 926}, // 996 InitiationIntervalINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21999, 18), 923}, // 997 IterationMultiple in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22061, 18), 930}, // 998 LoopCoalesceINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22140, 15), 934}, // 999 LoopCountINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(17305, 20), 927}, // 1000 MaxConcurrencyINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22079, 21), 931}, // 1001 MaxInterleavingINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21985, 14), 922}, // 1002 MaxIterations in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22155, 26), 935}, // 1003 MaxReinvocationDelayINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21971, 14), 921}, // 1004 MinIterations in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22126, 14), 933}, // 1005 NoFusionINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(14007, 5), 916}, // 1006 None in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22027, 13), 925}, // 1007 PartialCount in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22017, 10), 924}, // 1008 PeelCount in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(17325, 20), 929}, // 1009 PipelineEnableINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22100, 26), 932}, // 1010 SpeculatedIterationsINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21917, 7), 917}, // 1011 Unroll in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22464, 27), 949}, // 1012 MatrixAPackedBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22412, 26), 947}, // 1013 MatrixAPackedFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22332, 23), 943}, // 1014 MatrixAPackedInt4INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22286, 23), 941}, // 1015 MatrixAPackedInt8INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22181, 29), 937}, // 1016 MatrixASignedComponentsINTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22378, 17), 945}, // 1017 MatrixATF32INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22491, 27), 950}, // 1018 MatrixBPackedBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22438, 26), 948}, // 1019 MatrixBPackedFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22355, 23), 944}, // 1020 MatrixBPackedInt4INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22309, 23), 942}, // 1021 MatrixBPackedInt8INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22210, 29), 938}, // 1022 MatrixBSignedComponentsINTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22395, 17), 946}, // 1023 MatrixBTF32INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22239, 21), 939}, // 1024 MatrixCBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22260, 26), 940}, // 1025 MatrixResultBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(14007, 5), 936}, // 1026 None in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22651, 20), 958}, // 1027 AliasScopeINTELMask in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22518, 8), 953}, // 1028 Aligned in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22526, 21), 955}, // 1029 MakePointerAvailable in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22547, 24), 955}, // 1030 MakePointerAvailableKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22571, 19), 956}, // 1031 MakePointerVisible in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22590, 22), 956}, // 1032 MakePointerVisibleKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22671, 17), 959}, // 1033 NoAliasINTELMask in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22612, 18), 957}, // 1034 NonPrivatePointer in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22630, 21), 957}, // 1035 NonPrivatePointerKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(14007, 5), 951}, // 1036 None in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(21209, 12), 954}, // 1037 Nontemporal in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(15245, 9), 952}, // 1038 Volatile in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22695, 8), 961}, // 1039 GLSL450 in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(22703, 7), 962}, // 1040 OpenCL in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(22688, 7), 960}, // 1041 Simple in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(22710, 7), 963}, // 1042 Vulkan in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(22717, 10), 963}, // 1043 VulkanKHR in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(22735, 8), 965}, // 1044 Acquire in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22751, 15), 967}, // 1045 AcquireRelease in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22855, 20), 973}, // 1046 AtomicCounterMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22834, 21), 972}, // 1047 CrossWorkgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22875, 12), 974}, // 1048 ImageMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22916, 14), 976}, // 1049 MakeAvailable in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22930, 17), 976}, // 1050 MakeAvailableKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22947, 12), 977}, // 1051 MakeVisible in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22959, 15), 977}, // 1052 MakeVisibleKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(14007, 5), 964}, // 1053 None in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22887, 13), 975}, // 1054 OutputMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22900, 16), 975}, // 1055 OutputMemoryKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22727, 8), 964}, // 1056 Relaxed in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22743, 8), 966}, // 1057 Release in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22766, 23), 968}, // 1058 SequentiallyConsistent in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22803, 15), 970}, // 1059 SubgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22789, 14), 969}, // 1060 UniformMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(15245, 9), 978}, // 1061 Volatile in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22818, 16), 971}, // 1062 WorkgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22974, 10), 979}, // 1063 AutoINTEL in SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS
  {IR(22989, 4), 981}, // 1064 SAT in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(23002, 8), 983}, // 1065 SAT_SYM in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(22993, 9), 982}, // 1066 SAT_ZERO in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(22984, 5), 980}, // 1067 WRAP in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(23010, 25), 984}, // 1068 PackedVectorFormat4x8Bit in SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {IR(23035, 28), 984}, // 1069 PackedVectorFormat4x8BitKHR in SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {IR(23076, 4), 987}, // 1070 RND in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(23109, 9), 991}, // 1071 RND_CONV in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(23118, 13), 992}, // 1072 RND_CONV_ODD in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(23089, 8), 989}, // 1073 RND_INF in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(23097, 12), 990}, // 1074 RND_MIN_INF in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(23080, 9), 988}, // 1075 RND_ZERO in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(23063, 4), 985}, // 1076 TRN in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(23067, 9), 986}, // 1077 TRN_ZERO in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(14007, 5), 993}, // 1078 None in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(23131, 25), 994}, // 1079 RobustnessPerComponentNV in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(23156, 23), 995}, // 1080 RobustnessPerElementNV in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(23248, 27), 1001}, // 1081 CullBackFacingTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23275, 28), 1002}, // 1082 CullFrontFacingTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23317, 16), 1004}, // 1083 CullNoOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23303, 14), 1003}, // 1084 CullOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23387, 30), 1007}, // 1085 ForceOpacityMicromap2StateEXT in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23189, 12), 998}, // 1086 NoOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(14759, 8), 996}, // 1087 NoneKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23179, 10), 997}, // 1088 OpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23374, 13), 1006}, // 1089 SkipAABBsKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23350, 24), 1005}, // 1090 SkipBuiltinPrimitivesNV in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23224, 24), 1000}, // 1091 SkipClosestHitShaderKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23333, 17), 1005}, // 1092 SkipTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23201, 23), 999}, // 1093 TerminateOnFirstHitKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23458, 37), 1009}, // 1094 RayQueryCandidateIntersectionAABBKHR in SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {IR(23417, 41), 1008}, // 1095 RayQueryCandidateIntersectionTriangleKHR in SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {IR(23573, 42), 1012}, // 1096 RayQueryCommittedIntersectionGeneratedKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(23495, 37), 1010}, // 1097 RayQueryCommittedIntersectionNoneKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(23532, 41), 1011}, // 1098 RayQueryCommittedIntersectionTriangleKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(23615, 33), 1013}, // 1099 RayQueryCandidateIntersectionKHR in SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {IR(23648, 33), 1014}, // 1100 RayQueryCommittedIntersectionKHR in SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {IR(23693, 6), 1017}, // 1101 Clamp in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(23681, 12), 1016}, // 1102 ClampToEdge in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(14007, 5), 1015}, // 1103 None in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(23699, 7), 1018}, // 1104 Repeat in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(23706, 15), 1019}, // 1105 RepeatMirrored in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(23729, 7), 1021}, // 1106 Linear in SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {IR(23721, 8), 1020}, // 1107 Nearest in SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {IR(23794, 13), 1030}, // 1108 R11fG11fB10f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23836, 4), 1036}, // 1109 R16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23874, 9), 1041}, // 1110 R16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23807, 5), 1031}, // 1111 R16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23936, 5), 1050}, // 1112 R16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24007, 6), 1060}, // 1113 R16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23760, 5), 1025}, // 1114 R32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23914, 5), 1046}, // 1115 R32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23971, 6), 1055}, // 1116 R32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24024, 5), 1063}, // 1117 R64i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24018, 6), 1062}, // 1118 R64ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23840, 3), 1037}, // 1119 R8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23883, 8), 1042}, // 1120 R8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23941, 4), 1051}, // 1121 R8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24013, 5), 1061}, // 1122 R8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23827, 5), 1034}, // 1123 Rg16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23855, 10), 1039}, // 1124 Rg16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23788, 6), 1029}, // 1125 Rg16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23925, 6), 1048}, // 1126 Rg16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23994, 7), 1058}, // 1127 Rg16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23782, 6), 1028}, // 1128 Rg32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23919, 6), 1047}, // 1129 Rg32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23987, 7), 1057}, // 1130 Rg32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23832, 4), 1035}, // 1131 Rg8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23865, 9), 1040}, // 1132 Rg8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23931, 5), 1049}, // 1133 Rg8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24001, 6), 1059}, // 1134 Rg8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23819, 8), 1033}, // 1135 Rgb10A2 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23977, 10), 1056}, // 1136 Rgb10a2ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23812, 7), 1032}, // 1137 Rgba16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23843, 12), 1038}, // 1138 Rgba16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23752, 8), 1024}, // 1139 Rgba16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23899, 8), 1044}, // 1140 Rgba16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23954, 9), 1053}, // 1141 Rgba16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23744, 8), 1023}, // 1142 Rgba32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23891, 8), 1043}, // 1143 Rgba32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23945, 9), 1052}, // 1144 Rgba32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23765, 6), 1026}, // 1145 Rgba8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23771, 11), 1027}, // 1146 Rgba8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23907, 7), 1045}, // 1147 Rgba8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23963, 8), 1054}, // 1148 Rgba8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23736, 8), 1022}, // 1149 Unknown in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24029, 12), 1064}, // 1150 CrossDevice in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(24041, 7), 1065}, // 1151 Device in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(24067, 11), 1068}, // 1152 Invocation in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(24078, 12), 1069}, // 1153 QueueFamily in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(24090, 15), 1069}, // 1154 QueueFamilyKHR in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(24105, 14), 1070}, // 1155 ShaderCallKHR in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(24058, 9), 1067}, // 1156 Subgroup in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(24048, 10), 1066}, // 1157 Workgroup in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(24127, 12), 1073}, // 1158 DontFlatten in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(24119, 8), 1072}, // 1159 Flatten in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(14007, 5), 1071}, // 1160 None in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(24139, 29), 1074}, // 1161 IdentifierPossibleDuplicates in SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS
  {IR(13888, 8), 1076}, // 1162 Address in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13896, 8), 1077}, // 1163 Boolean in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13904, 6), 1078}, // 1164 Float in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13910, 7), 1079}, // 1165 Signed in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13917, 11), 1080}, // 1166 SignedChar in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13928, 9), 1081}, // 1167 Unsigned in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13937, 13), 1082}, // 1168 UnsignedChar in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13876, 12), 1075}, // 1169 Unspecified in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13950, 6), 1083}, // 1170 Class in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(13956, 10), 1084}, // 1171 Structure in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(13966, 6), 1085}, // 1172 Union in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(13987, 20), 1087}, // 1173 ImportedDeclaration in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(13972, 15), 1086}, // 1174 ImportedModule in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(14096, 15), 1095}, // 1175 FlagArtificial in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14111, 13), 1096}, // 1176 FlagExplicit in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14084, 12), 1094}, // 1177 FlagFwdDecl in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14174, 21), 1100}, // 1178 FlagIndirectVariable in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14067, 17), 1093}, // 1179 FlagIsDefinition in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14251, 16), 1104}, // 1180 FlagIsEnumClass in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14055, 12), 1092}, // 1181 FlagIsLocal in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14235, 16), 1103}, // 1182 FlagIsOptimized in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14028, 14), 1090}, // 1183 FlagIsPrivate in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14012, 16), 1089}, // 1184 FlagIsProtected in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14042, 13), 1091}, // 1185 FlagIsPublic in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14195, 20), 1101}, // 1186 FlagLValueReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14139, 18), 1098}, // 1187 FlagObjectPointer in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14124, 15), 1097}, // 1188 FlagPrototyped in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14215, 20), 1102}, // 1189 FlagRValueReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14157, 17), 1099}, // 1190 FlagStaticMember in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14287, 24), 1106}, // 1191 FlagTypePassByReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14267, 20), 1105}, // 1192 FlagTypePassByValue in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(24168, 26), 1107}, // 1193 FlagUnknownPhysicalLayout in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14007, 5), 1088}, // 1194 None in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14372, 9), 1112}, // 1195 BitPiece in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14404, 7), 1116}, // 1196 Constu in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14311, 6), 1108}, // 1197 Deref in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14411, 9), 1117}, // 1198 Fragment in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14322, 6), 1110}, // 1199 Minus in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14317, 5), 1109}, // 1200 Plus in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14361, 11), 1111}, // 1201 PlusUconst in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14393, 11), 1115}, // 1202 StackValue in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14381, 5), 1113}, // 1203 Swap in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14386, 7), 1114}, // 1204 Xderef in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14456, 11), 1121}, // 1205 AtomicType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14420, 10), 1118}, // 1206 ConstType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14443, 13), 1120}, // 1207 RestrictType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14430, 13), 1119}, // 1208 VolatileType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(24229, 15), 1128}, // 1209 CPP_for_OpenCL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24194, 5), 1123}, // 1210 ESSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24199, 5), 1124}, // 1211 GLSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24249, 7), 1130}, // 1212 HERO_C in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24224, 5), 1127}, // 1213 HLSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24256, 5), 1131}, // 1214 NZSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24204, 9), 1125}, // 1215 OpenCL_C in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24213, 11), 1126}, // 1216 OpenCL_CPP in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24276, 5), 1135}, // 1217 Rust in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24244, 5), 1129}, // 1218 SYCL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24266, 6), 1133}, // 1219 Slang in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(23736, 8), 1122}, // 1220 Unknown in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24261, 5), 1132}, // 1221 WGSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24272, 4), 1134}, // 1222 Zig in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24363, 14), 1146}, // 1223 AtomicCounter in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24445, 16), 1152}, // 1224 CallableDataKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24461, 15), 1152}, // 1225 CallableDataNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24759, 17), 1161}, // 1226 CodeSectionINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24310, 15), 1141}, // 1227 CrossWorkgroup in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24776, 16), 1162}, // 1228 DeviceOnlyINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24333, 9), 1143}, // 1229 Function in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24342, 8), 1144}, // 1230 Generic in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24550, 16), 1155}, // 1231 HitAttributeKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24566, 15), 1155}, // 1232 HitAttributeNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24714, 21), 1159}, // 1233 HitObjectAttributeNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24792, 14), 1163}, // 1234 HostOnlyINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24377, 6), 1147}, // 1235 Image in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24476, 24), 1153}, // 1236 IncomingCallableDataKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24500, 23), 1153}, // 1237 IncomingCallableDataNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24581, 22), 1156}, // 1238 IncomingRayPayloadKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24603, 21), 1156}, // 1239 IncomingRayPayloadNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24297, 6), 1137}, // 1240 Input in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24429, 16), 1151}, // 1241 NodePayloadAMDX in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24303, 7), 1139}, // 1242 Output in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24667, 22), 1158}, // 1243 PhysicalStorageBuffer in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24689, 25), 1158}, // 1244 PhysicalStorageBufferEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24325, 8), 1142}, // 1245 Private in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24350, 13), 1145}, // 1246 PushConstant in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24523, 14), 1154}, // 1247 RayPayloadKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24537, 13), 1154}, // 1248 RayPayloadNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24624, 22), 1157}, // 1249 ShaderRecordBufferKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24646, 21), 1157}, // 1250 ShaderRecordBufferNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24383, 14), 1148}, // 1251 StorageBuffer in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24735, 24), 1160}, // 1252 TaskPayloadWorkgroupEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24410, 19), 1150}, // 1253 TileAttachmentQCOM in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24397, 13), 1149}, // 1254 TileImageEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(15296, 8), 1138}, // 1255 Uniform in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24281, 16), 1136}, // 1256 UniformConstant in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24048, 10), 1140}, // 1257 Workgroup in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(21860, 15), 1167}, // 1258 StreamingINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(21834, 14), 1164}, // 1259 UncachedINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(24824, 15), 1166}, // 1260 WriteBackINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(24806, 18), 1165}, // 1261 WriteThroughINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(24850, 11), 1170}, // 1262 DecodeFunc in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(14007, 5), 1168}, // 1263 None in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(24839, 11), 1169}, // 1264 TensorView in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(23681, 12), 1173}, // 1265 ClampToEdge in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(15254, 9), 1172}, // 1266 Constant in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(23699, 7), 1174}, // 1267 Repeat in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(23706, 15), 1175}, // 1268 RepeatMirrored in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(24861, 10), 1171}, // 1269 Undefined in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(24914, 24), 1179}, // 1270 MakeElementAvailableARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(24938, 22), 1180}, // 1271 MakeElementVisibleARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(24960, 21), 1181}, // 1272 NonPrivateElementARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(24871, 8), 1176}, // 1273 NoneARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(24879, 15), 1177}, // 1274 NontemporalARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(24894, 20), 1178}, // 1275 OutOfBoundsValueARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
}};

IndexRange OperandNameRangeForKind(spv_operand_type_t type) {
  switch(type) {
    case SPV_OPERAND_TYPE_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_ADDRESSING_MODEL: return IR(3, 5);
    case SPV_OPERAND_TYPE_BUILT_IN: return IR(8, 148);
    case SPV_OPERAND_TYPE_CAPABILITY: return IR(156, 297);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(453, 8);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(461, 3);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(464, 2);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS: return IR(466, 19);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION: return IR(485, 10);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(495, 4);
    case SPV_OPERAND_TYPE_COMPONENT_TYPE: return IR(499, 15);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT: return IR(514, 4);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS: return IR(518, 6);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE: return IR(524, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE: return IR(527, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT: return IR(530, 4);
    case SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(534, 8);
    case SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE: return IR(542, 3);
    case SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS: return IR(545, 16);
    case SPV_OPERAND_TYPE_DEBUG_OPERATION: return IR(561, 9);
    case SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER: return IR(570, 3);
    case SPV_OPERAND_TYPE_DECORATION: return IR(573, 150);
    case SPV_OPERAND_TYPE_DIMENSIONALITY: return IR(723, 8);
    case SPV_OPERAND_TYPE_EXECUTION_MODE: return IR(731, 101);
    case SPV_OPERAND_TYPE_EXECUTION_MODEL: return IR(832, 23);
    case SPV_OPERAND_TYPE_FPDENORM_MODE: return IR(855, 2);
    case SPV_OPERAND_TYPE_FPENCODING: return IR(857, 3);
    case SPV_OPERAND_TYPE_FPOPERATION_MODE: return IR(860, 2);
    case SPV_OPERAND_TYPE_FP_FAST_MATH_MODE: return IR(862, 11);
    case SPV_OPERAND_TYPE_FP_ROUNDING_MODE: return IR(873, 4);
    case SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE: return IR(877, 4);
    case SPV_OPERAND_TYPE_FUNCTION_CONTROL: return IR(881, 7);
    case SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE: return IR(888, 9);
    case SPV_OPERAND_TYPE_GROUP_OPERATION: return IR(897, 7);
    case SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER: return IR(904, 4);
    case SPV_OPERAND_TYPE_IMAGE: return IR(908, 21);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE: return IR(929, 26);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER: return IR(955, 20);
    case SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER: return IR(975, 2);
    case SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS: return IR(977, 3);
    case SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO: return IR(980, 2);
    case SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS: return IR(982, 2);
    case SPV_OPERAND_TYPE_LINKAGE_TYPE: return IR(984, 3);
    case SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL: return IR(987, 5);
    case SPV_OPERAND_TYPE_LOOP_CONTROL: return IR(992, 20);
    case SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(1012, 15);
    case SPV_OPERAND_TYPE_MEMORY_ACCESS: return IR(1027, 12);
    case SPV_OPERAND_TYPE_MEMORY_MODEL: return IR(1039, 5);
    case SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID: return IR(1044, 19);
    case SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS: return IR(1063, 1);
    case SPV_OPERAND_TYPE_OVERFLOW_MODES: return IR(1064, 4);
    case SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT: return IR(1068, 2);
    case SPV_OPERAND_TYPE_QUANTIZATION_MODES: return IR(1070, 8);
    case SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS: return IR(1078, 3);
    case SPV_OPERAND_TYPE_RAY_FLAGS: return IR(1081, 13);
    case SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE: return IR(1094, 2);
    case SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE: return IR(1096, 3);
    case SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION: return IR(1099, 2);
    case SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE: return IR(1101, 5);
    case SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE: return IR(1106, 2);
    case SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT: return IR(1108, 42);
    case SPV_OPERAND_TYPE_SCOPE_ID: return IR(1150, 8);
    case SPV_OPERAND_TYPE_SELECTION_CONTROL: return IR(1158, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS: return IR(1161, 1);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(1162, 8);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(1170, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(1173, 2);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS: return IR(1175, 20);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION: return IR(1195, 10);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(1205, 4);
    case SPV_OPERAND_TYPE_SOURCE_LANGUAGE: return IR(1209, 14);
    case SPV_OPERAND_TYPE_STORAGE_CLASS: return IR(1223, 35);
    case SPV_OPERAND_TYPE_STORE_CACHE_CONTROL: return IR(1258, 4);
    case SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS: return IR(1262, 3);
    case SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE: return IR(1265, 5);
    case SPV_OPERAND_TYPE_TENSOR_OPERANDS: return IR(1270, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_IMAGE: return IR(908, 21);
    case SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS: return IR(1027, 12);
    case SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT: return IR(1068, 2);
    case SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS: return IR(518, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(1012, 15);
    case SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS: return IR(1078, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_FPENCODING: return IR(857, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS: return IR(1270, 6);
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
static const std::array<InstructionDesc, 801> kInstructionDesc{{
  {spv::Op::OpNop, false, false, IR(0, 0), IR(24981, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpUndef, true, true, IR(39, 2), IR(25037, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpSourceContinued, false, false, IR(11, 1), IR(25043, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpSource, false, false, IR(41, 4), IR(25162, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpSourceExtension, false, false, IR(11, 1), IR(25169, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpName, false, false, IR(45, 2), IR(25185, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpMemberName, false, false, IR(47, 3), IR(25190, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpString, true, false, IR(50, 2), IR(25201, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpLine, false, false, IR(52, 3), IR(25208, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpExtension, false, false, IR(11, 1), IR(25213, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpExtInstImport, true, false, IR(50, 2), IR(25223, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpExtInst, true, true, IR(55, 4), IR(25283, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpMemoryModel, false, false, IR(59, 2), IR(25355, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpEntryPoint, false, false, IR(61, 4), IR(25429, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpExecutionMode, false, false, IR(65, 2), IR(25472, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpCapability, false, false, IR(67, 1), IR(25514, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpTypeVoid, true, false, IR(68, 1), IR(25525, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeBool, true, false, IR(68, 1), IR(25534, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeInt, true, false, IR(69, 3), IR(25543, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeFloat, true, false, IR(72, 3), IR(25588, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeVector, true, false, IR(75, 3), IR(25598, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeMatrix, true, false, IR(75, 3), IR(25609, 11), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeImage, true, false, IR(78, 9), IR(25733, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeSampler, true, false, IR(68, 1), IR(25743, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeSampledImage, true, false, IR(87, 2), IR(25755, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeArray, true, false, IR(89, 3), IR(25772, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeRuntimeArray, true, false, IR(87, 2), IR(25782, 17), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeStruct, true, false, IR(92, 2), IR(25799, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeOpaque, true, false, IR(50, 2), IR(25810, 11), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypePointer, true, false, IR(94, 3), IR(25852, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeFunction, true, false, IR(97, 3), IR(25864, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeEvent, true, false, IR(68, 1), IR(25877, 10), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeDeviceEvent, true, false, IR(68, 1), IR(25887, 16), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeReserveId, true, false, IR(68, 1), IR(25903, 14), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeQueue, true, false, IR(68, 1), IR(25917, 10), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypePipe, true, false, IR(100, 2), IR(25927, 9), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeForwardPointer, false, false, IR(102, 2), IR(25936, 19), IR(0, 0), IR(199, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantTrue, true, true, IR(39, 2), IR(25955, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantFalse, true, true, IR(39, 2), IR(25968, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstant, true, true, IR(104, 3), IR(15254, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantComposite, true, true, IR(107, 3), IR(26020, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantSampler, true, true, IR(110, 5), IR(26116, 16), IR(0, 0), IR(201, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantNull, true, true, IR(39, 2), IR(26132, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantTrue, true, true, IR(39, 2), IR(26145, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantFalse, true, true, IR(39, 2), IR(26162, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstant, true, true, IR(104, 3), IR(26180, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantComposite, true, true, IR(107, 3), IR(26193, 22), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantOp, true, true, IR(115, 3), IR(26256, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpFunction, true, true, IR(118, 4), IR(24333, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionParameter, true, true, IR(39, 2), IR(26305, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionEnd, false, false, IR(0, 0), IR(26323, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionCall, true, true, IR(122, 4), IR(26335, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpVariable, true, true, IR(126, 4), IR(26348, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpImageTexelPointer, true, true, IR(130, 5), IR(26357, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpLoad, true, true, IR(135, 4), IR(26415, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpStore, false, false, IR(139, 3), IR(26420, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCopyMemory, false, false, IR(142, 4), IR(26426, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCopyMemorySized, false, false, IR(146, 5), IR(26437, 16), IR(0, 0), IR(202, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpAccessChain, true, true, IR(122, 4), IR(26453, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpInBoundsAccessChain, true, true, IR(122, 4), IR(26465, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrAccessChain, true, true, IR(151, 5), IR(26485, 15), IR(0, 0), IR(204, 4), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpArrayLength, true, true, IR(156, 4), IR(26500, 12), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpGenericPtrMemSemantics, true, true, IR(160, 3), IR(26512, 23), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpInBoundsPtrAccessChain, true, true, IR(151, 5), IR(26535, 23), IR(0, 0), IR(1, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpDecorate, false, false, IR(163, 2), IR(26586, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpMemberDecorate, false, false, IR(165, 3), IR(26595, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpDecorationGroup, true, false, IR(68, 1), IR(26610, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupDecorate, false, false, IR(168, 2), IR(26626, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupMemberDecorate, false, false, IR(170, 2), IR(26685, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpVectorExtractDynamic, true, true, IR(172, 4), IR(26705, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpVectorInsertDynamic, true, true, IR(130, 5), IR(26726, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpVectorShuffle, true, true, IR(176, 5), IR(26746, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeConstruct, true, true, IR(107, 3), IR(26760, 19), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeExtract, true, true, IR(181, 4), IR(26779, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeInsert, true, true, IR(176, 5), IR(26796, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCopyObject, true, true, IR(160, 3), IR(26812, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpTranspose, true, true, IR(160, 3), IR(26823, 10), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpSampledImage, true, true, IR(172, 4), IR(26833, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleImplicitLod, true, true, IR(185, 5), IR(26878, 23), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleExplicitLod, true, true, IR(190, 5), IR(26924, 23), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleDrefImplicitLod, true, true, IR(195, 6), IR(26947, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleDrefExplicitLod, true, true, IR(201, 6), IR(26974, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjImplicitLod, true, true, IR(185, 5), IR(27001, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjExplicitLod, true, true, IR(190, 5), IR(27028, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjDrefImplicitLod, true, true, IR(195, 6), IR(27055, 31), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjDrefExplicitLod, true, true, IR(201, 6), IR(27086, 31), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageFetch, true, true, IR(185, 5), IR(27117, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageGather, true, true, IR(195, 6), IR(27128, 12), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageDrefGather, true, true, IR(195, 6), IR(27140, 16), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageRead, true, true, IR(185, 5), IR(27156, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageWrite, false, false, IR(207, 4), IR(27166, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImage, true, true, IR(160, 3), IR(24377, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryFormat, true, true, IR(160, 3), IR(27177, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryOrder, true, true, IR(160, 3), IR(27194, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySizeLod, true, true, IR(172, 4), IR(27210, 18), IR(0, 0), IR(208, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySize, true, true, IR(160, 3), IR(27228, 15), IR(0, 0), IR(208, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryLod, true, true, IR(172, 4), IR(27243, 14), IR(0, 0), IR(210, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryLevels, true, true, IR(160, 3), IR(27257, 17), IR(0, 0), IR(208, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySamples, true, true, IR(160, 3), IR(27274, 18), IR(0, 0), IR(208, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertFToU, true, true, IR(160, 3), IR(27292, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertFToS, true, true, IR(160, 3), IR(27304, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertSToF, true, true, IR(160, 3), IR(27316, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToF, true, true, IR(160, 3), IR(27328, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpUConvert, true, true, IR(160, 3), IR(27340, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSConvert, true, true, IR(160, 3), IR(27349, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpFConvert, true, true, IR(160, 3), IR(27358, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpQuantizeToF16, true, true, IR(160, 3), IR(27367, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertPtrToU, true, true, IR(160, 3), IR(27381, 14), IR(0, 0), IR(199, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSatConvertSToU, true, true, IR(160, 3), IR(27395, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSatConvertUToS, true, true, IR(160, 3), IR(27410, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToPtr, true, true, IR(160, 3), IR(27425, 14), IR(0, 0), IR(199, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpPtrCastToGeneric, true, true, IR(160, 3), IR(27439, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpGenericCastToPtr, true, true, IR(160, 3), IR(27456, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpGenericCastToPtrExplicit, true, true, IR(211, 4), IR(27473, 25), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpBitcast, true, true, IR(160, 3), IR(27498, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSNegate, true, true, IR(160, 3), IR(27506, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFNegate, true, true, IR(160, 3), IR(27514, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIAdd, true, true, IR(172, 4), IR(27522, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFAdd, true, true, IR(172, 4), IR(27527, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpISub, true, true, IR(172, 4), IR(27532, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFSub, true, true, IR(172, 4), IR(27537, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIMul, true, true, IR(172, 4), IR(27542, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFMul, true, true, IR(172, 4), IR(27547, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDiv, true, true, IR(172, 4), IR(27552, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSDiv, true, true, IR(172, 4), IR(27557, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFDiv, true, true, IR(172, 4), IR(27562, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUMod, true, true, IR(172, 4), IR(27567, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSRem, true, true, IR(172, 4), IR(27572, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSMod, true, true, IR(172, 4), IR(27577, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFRem, true, true, IR(172, 4), IR(27582, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFMod, true, true, IR(172, 4), IR(27587, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpVectorTimesScalar, true, true, IR(172, 4), IR(27592, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesScalar, true, true, IR(172, 4), IR(27610, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpVectorTimesMatrix, true, true, IR(172, 4), IR(27628, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesVector, true, true, IR(172, 4), IR(27646, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesMatrix, true, true, IR(172, 4), IR(27664, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpOuterProduct, true, true, IR(172, 4), IR(27682, 13), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpDot, true, true, IR(172, 4), IR(27695, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIAddCarry, true, true, IR(172, 4), IR(27699, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpISubBorrow, true, true, IR(172, 4), IR(27709, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUMulExtended, true, true, IR(172, 4), IR(27720, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSMulExtended, true, true, IR(172, 4), IR(27733, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpAny, true, true, IR(160, 3), IR(27746, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpAll, true, true, IR(160, 3), IR(27750, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsNan, true, true, IR(160, 3), IR(27754, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsInf, true, true, IR(160, 3), IR(27760, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsFinite, true, true, IR(160, 3), IR(27766, 9), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsNormal, true, true, IR(160, 3), IR(27775, 9), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSignBitSet, true, true, IR(160, 3), IR(27784, 11), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLessOrGreater, true, true, IR(172, 4), IR(27795, 14), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), SPV_SPIRV_VERSION_WORD(1,5), PrintingClass::kRelational_and_Logical},
  {spv::Op::OpOrdered, true, true, IR(172, 4), IR(27809, 8), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUnordered, true, true, IR(172, 4), IR(27817, 10), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalEqual, true, true, IR(172, 4), IR(27827, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalNotEqual, true, true, IR(172, 4), IR(27840, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalOr, true, true, IR(172, 4), IR(27856, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalAnd, true, true, IR(172, 4), IR(27866, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalNot, true, true, IR(160, 3), IR(27877, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSelect, true, true, IR(130, 5), IR(27888, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIEqual, true, true, IR(172, 4), IR(27895, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpINotEqual, true, true, IR(172, 4), IR(27902, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUGreaterThan, true, true, IR(172, 4), IR(27912, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSGreaterThan, true, true, IR(172, 4), IR(27925, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUGreaterThanEqual, true, true, IR(172, 4), IR(27938, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSGreaterThanEqual, true, true, IR(172, 4), IR(27956, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpULessThan, true, true, IR(172, 4), IR(27974, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSLessThan, true, true, IR(172, 4), IR(27984, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpULessThanEqual, true, true, IR(172, 4), IR(27994, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSLessThanEqual, true, true, IR(172, 4), IR(28009, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdEqual, true, true, IR(172, 4), IR(28024, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordEqual, true, true, IR(172, 4), IR(28034, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdNotEqual, true, true, IR(172, 4), IR(28046, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordNotEqual, true, true, IR(172, 4), IR(28059, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdLessThan, true, true, IR(172, 4), IR(28074, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordLessThan, true, true, IR(172, 4), IR(28087, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdGreaterThan, true, true, IR(172, 4), IR(28102, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordGreaterThan, true, true, IR(172, 4), IR(28118, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdLessThanEqual, true, true, IR(172, 4), IR(28136, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordLessThanEqual, true, true, IR(172, 4), IR(28154, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdGreaterThanEqual, true, true, IR(172, 4), IR(28174, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordGreaterThanEqual, true, true, IR(172, 4), IR(28195, 23), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpShiftRightLogical, true, true, IR(172, 4), IR(28218, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpShiftRightArithmetic, true, true, IR(172, 4), IR(28236, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpShiftLeftLogical, true, true, IR(172, 4), IR(28257, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseOr, true, true, IR(172, 4), IR(28274, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseXor, true, true, IR(172, 4), IR(28284, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseAnd, true, true, IR(172, 4), IR(28295, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpNot, true, true, IR(160, 3), IR(28306, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldInsert, true, true, IR(215, 6), IR(28310, 15), IR(0, 0), IR(211, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldSExtract, true, true, IR(130, 5), IR(28325, 17), IR(0, 0), IR(211, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldUExtract, true, true, IR(130, 5), IR(28342, 17), IR(0, 0), IR(211, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitReverse, true, true, IR(160, 3), IR(28359, 11), IR(0, 0), IR(211, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitCount, true, true, IR(160, 3), IR(28370, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpDPdx, true, true, IR(160, 3), IR(28379, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdy, true, true, IR(160, 3), IR(28384, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidth, true, true, IR(160, 3), IR(28389, 7), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdxFine, true, true, IR(160, 3), IR(28396, 9), IR(0, 0), IR(213, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdyFine, true, true, IR(160, 3), IR(28405, 9), IR(0, 0), IR(213, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidthFine, true, true, IR(160, 3), IR(28414, 11), IR(0, 0), IR(213, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdxCoarse, true, true, IR(160, 3), IR(28425, 11), IR(0, 0), IR(213, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdyCoarse, true, true, IR(160, 3), IR(28436, 11), IR(0, 0), IR(213, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidthCoarse, true, true, IR(160, 3), IR(28447, 13), IR(0, 0), IR(213, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpEmitVertex, false, false, IR(0, 0), IR(28460, 11), IR(0, 0), IR(69, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEndPrimitive, false, false, IR(0, 0), IR(28471, 13), IR(0, 0), IR(69, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEmitStreamVertex, false, false, IR(10, 1), IR(28484, 17), IR(0, 0), IR(110, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEndStreamPrimitive, false, false, IR(10, 1), IR(28501, 19), IR(0, 0), IR(110, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpControlBarrier, false, false, IR(221, 3), IR(28557, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpMemoryBarrier, false, false, IR(224, 2), IR(28572, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpAtomicLoad, true, true, IR(226, 5), IR(28586, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicStore, false, false, IR(231, 4), IR(28597, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicExchange, true, true, IR(235, 6), IR(28609, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicCompareExchange, true, true, IR(241, 8), IR(28624, 22), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicCompareExchangeWeak, true, true, IR(241, 8), IR(28646, 26), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), SPV_SPIRV_VERSION_WORD(1,3), PrintingClass::kAtomic},
  {spv::Op::OpAtomicIIncrement, true, true, IR(226, 5), IR(28672, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicIDecrement, true, true, IR(226, 5), IR(28689, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicIAdd, true, true, IR(235, 6), IR(28706, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicISub, true, true, IR(235, 6), IR(28717, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicSMin, true, true, IR(235, 6), IR(28728, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicUMin, true, true, IR(235, 6), IR(28739, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicSMax, true, true, IR(235, 6), IR(28750, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicUMax, true, true, IR(235, 6), IR(28761, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicAnd, true, true, IR(235, 6), IR(28772, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicOr, true, true, IR(235, 6), IR(28782, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicXor, true, true, IR(235, 6), IR(28791, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpPhi, true, true, IR(107, 3), IR(28801, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLoopMerge, false, false, IR(249, 3), IR(28835, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpSelectionMerge, false, false, IR(252, 2), IR(28880, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLabel, true, false, IR(68, 1), IR(28895, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpBranch, false, false, IR(10, 1), IR(28901, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpBranchConditional, false, false, IR(254, 4), IR(28908, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpSwitch, false, false, IR(258, 3), IR(28971, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpKill, false, false, IR(0, 0), IR(28978, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpReturn, false, false, IR(0, 0), IR(28983, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpReturnValue, false, false, IR(10, 1), IR(28990, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpUnreachable, false, false, IR(0, 0), IR(29002, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLifetimeStart, false, false, IR(261, 2), IR(29014, 14), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLifetimeStop, false, false, IR(261, 2), IR(29028, 13), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpGroupAsyncCopy, true, true, IR(263, 8), IR(29041, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupWaitEvents, false, false, IR(271, 3), IR(29056, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupAll, true, true, IR(274, 4), IR(29072, 9), IR(0, 0), IR(214, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupAny, true, true, IR(274, 4), IR(29081, 9), IR(0, 0), IR(214, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBroadcast, true, true, IR(278, 5), IR(29090, 15), IR(0, 0), IR(214, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupIAdd, true, true, IR(283, 5), IR(29138, 10), IR(0, 0), IR(214, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFAdd, true, true, IR(283, 5), IR(29148, 10), IR(0, 0), IR(214, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMin, true, true, IR(283, 5), IR(29158, 10), IR(0, 0), IR(214, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMin, true, true, IR(283, 5), IR(29168, 10), IR(0, 0), IR(214, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMin, true, true, IR(283, 5), IR(29178, 10), IR(0, 0), IR(214, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMax, true, true, IR(283, 5), IR(29188, 10), IR(0, 0), IR(214, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMax, true, true, IR(283, 5), IR(29198, 10), IR(0, 0), IR(214, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMax, true, true, IR(283, 5), IR(29208, 10), IR(0, 0), IR(214, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpReadPipe, true, true, IR(215, 6), IR(29218, 9), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpWritePipe, true, true, IR(215, 6), IR(29227, 10), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReservedReadPipe, true, true, IR(288, 8), IR(29237, 17), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReservedWritePipe, true, true, IR(288, 8), IR(29254, 18), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReserveReadPipePackets, true, true, IR(215, 6), IR(29272, 23), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReserveWritePipePackets, true, true, IR(215, 6), IR(29295, 24), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCommitReadPipe, false, false, IR(296, 4), IR(29319, 15), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCommitWritePipe, false, false, IR(296, 4), IR(29334, 16), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpIsValidReserveId, true, true, IR(160, 3), IR(29350, 17), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetNumPipePackets, true, true, IR(130, 5), IR(29367, 18), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetMaxPipePackets, true, true, IR(130, 5), IR(29385, 18), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupReserveReadPipePackets, true, true, IR(300, 7), IR(29403, 28), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupReserveWritePipePackets, true, true, IR(300, 7), IR(29431, 29), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupCommitReadPipe, false, false, IR(307, 5), IR(29460, 20), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupCommitWritePipe, false, false, IR(307, 5), IR(29480, 21), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpEnqueueMarker, true, true, IR(215, 6), IR(29501, 14), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpEnqueueKernel, true, true, IR(312, 13), IR(29515, 14), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelNDrangeSubGroupCount, true, true, IR(325, 7), IR(29529, 30), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelNDrangeMaxSubGroupSize, true, true, IR(325, 7), IR(29559, 32), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelWorkGroupSize, true, true, IR(215, 6), IR(29591, 23), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelPreferredWorkGroupSizeMultiple, true, true, IR(215, 6), IR(29614, 40), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpRetainEvent, false, false, IR(10, 1), IR(29654, 12), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpReleaseEvent, false, false, IR(10, 1), IR(29666, 13), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpCreateUserEvent, true, true, IR(39, 2), IR(29679, 16), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpIsValidEvent, true, true, IR(160, 3), IR(29695, 13), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpSetUserEventStatus, false, false, IR(36, 2), IR(29708, 19), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpCaptureEventProfilingInfo, false, false, IR(33, 3), IR(29727, 26), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetDefaultQueue, true, true, IR(39, 2), IR(29753, 16), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpBuildNDRange, true, true, IR(130, 5), IR(29769, 13), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpImageSparseSampleImplicitLod, true, true, IR(185, 5), IR(29782, 29), IR(0, 0), IR(215, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleExplicitLod, true, true, IR(190, 5), IR(29811, 29), IR(0, 0), IR(215, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleDrefImplicitLod, true, true, IR(195, 6), IR(29840, 33), IR(0, 0), IR(215, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleDrefExplicitLod, true, true, IR(201, 6), IR(29873, 33), IR(0, 0), IR(215, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjImplicitLod, true, true, IR(185, 5), IR(29906, 33), IR(0, 0), IR(215, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjExplicitLod, true, true, IR(190, 5), IR(29939, 33), IR(0, 0), IR(215, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjDrefImplicitLod, true, true, IR(195, 6), IR(29972, 37), IR(0, 0), IR(215, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjDrefExplicitLod, true, true, IR(201, 6), IR(30009, 37), IR(0, 0), IR(215, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseFetch, true, true, IR(185, 5), IR(30046, 17), IR(0, 0), IR(215, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseGather, true, true, IR(195, 6), IR(30063, 18), IR(0, 0), IR(215, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseDrefGather, true, true, IR(195, 6), IR(30081, 22), IR(0, 0), IR(215, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseTexelsResident, true, true, IR(160, 3), IR(30103, 26), IR(0, 0), IR(215, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpNoLine, false, false, IR(0, 0), IR(30129, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpAtomicFlagTestAndSet, true, true, IR(226, 5), IR(30136, 21), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicFlagClear, false, false, IR(332, 3), IR(30157, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpImageSparseRead, true, true, IR(185, 5), IR(30173, 16), IR(0, 0), IR(215, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpSizeOf, true, true, IR(160, 3), IR(30189, 7), IR(0, 0), IR(1, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpTypePipeStorage, true, false, IR(68, 1), IR(30196, 16), IR(0, 0), IR(216, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantPipeStorage, true, true, IR(335, 5), IR(30212, 20), IR(0, 0), IR(216, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCreatePipeFromPipeStorage, true, true, IR(160, 3), IR(30232, 26), IR(0, 0), IR(216, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetKernelLocalSizeForSubgroupCount, true, true, IR(325, 7), IR(30258, 35), IR(0, 0), IR(149, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelMaxNumSubgroups, true, true, IR(215, 6), IR(30293, 25), IR(0, 0), IR(149, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpTypeNamedBarrier, true, false, IR(68, 1), IR(30318, 17), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpNamedBarrierInitialize, true, true, IR(160, 3), IR(30335, 23), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpMemoryNamedBarrier, false, false, IR(332, 3), IR(30358, 19), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpModuleProcessed, false, false, IR(11, 1), IR(30377, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpExecutionModeId, false, false, IR(65, 2), IR(30393, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,2), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpDecorateId, false, false, IR(163, 2), IR(30409, 11), IR(0, 0), IR(1, 0), IR(154, 1), SPV_SPIRV_VERSION_WORD(1,2), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupNonUniformElect, true, true, IR(340, 3), IR(30420, 21), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAll, true, true, IR(274, 4), IR(30441, 19), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAny, true, true, IR(274, 4), IR(30460, 19), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAllEqual, true, true, IR(274, 4), IR(30479, 24), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBroadcast, true, true, IR(278, 5), IR(30503, 25), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBroadcastFirst, true, true, IR(274, 4), IR(30528, 30), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallot, true, true, IR(274, 4), IR(5569, 22), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformInverseBallot, true, true, IR(274, 4), IR(30558, 29), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotBitExtract, true, true, IR(278, 5), IR(30587, 32), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotBitCount, true, true, IR(283, 5), IR(30619, 30), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotFindLSB, true, true, IR(274, 4), IR(30649, 29), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotFindMSB, true, true, IR(274, 4), IR(30678, 29), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffle, true, true, IR(278, 5), IR(8659, 23), IR(0, 0), IR(220, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleXor, true, true, IR(278, 5), IR(30707, 26), IR(0, 0), IR(220, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleUp, true, true, IR(278, 5), IR(30733, 25), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleDown, true, true, IR(278, 5), IR(30758, 27), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformIAdd, true, true, IR(343, 6), IR(30785, 20), IR(0, 0), IR(222, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFAdd, true, true, IR(343, 6), IR(30805, 20), IR(0, 0), IR(222, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformIMul, true, true, IR(343, 6), IR(30825, 20), IR(0, 0), IR(222, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMul, true, true, IR(343, 6), IR(30845, 20), IR(0, 0), IR(222, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformSMin, true, true, IR(343, 6), IR(30865, 20), IR(0, 0), IR(222, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformUMin, true, true, IR(343, 6), IR(30885, 20), IR(0, 0), IR(222, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMin, true, true, IR(343, 6), IR(30905, 20), IR(0, 0), IR(222, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformSMax, true, true, IR(343, 6), IR(30925, 20), IR(0, 0), IR(222, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformUMax, true, true, IR(343, 6), IR(30945, 20), IR(0, 0), IR(222, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMax, true, true, IR(343, 6), IR(30965, 20), IR(0, 0), IR(222, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseAnd, true, true, IR(343, 6), IR(30985, 26), IR(0, 0), IR(222, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseOr, true, true, IR(343, 6), IR(31011, 25), IR(0, 0), IR(222, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseXor, true, true, IR(343, 6), IR(31036, 26), IR(0, 0), IR(222, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalAnd, true, true, IR(343, 6), IR(31062, 26), IR(0, 0), IR(222, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalOr, true, true, IR(343, 6), IR(31088, 25), IR(0, 0), IR(222, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalXor, true, true, IR(343, 6), IR(31113, 26), IR(0, 0), IR(222, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadBroadcast, true, true, IR(278, 5), IR(31139, 29), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadSwap, true, true, IR(278, 5), IR(31168, 24), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpCopyLogical, true, true, IR(160, 3), IR(31192, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpPtrEqual, true, true, IR(172, 4), IR(31204, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrNotEqual, true, true, IR(172, 4), IR(31213, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrDiff, true, true, IR(172, 4), IR(31225, 8), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpColorAttachmentReadEXT, true, true, IR(349, 4), IR(31233, 23), IR(0, 0), IR(141, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpDepthAttachmentReadEXT, true, true, IR(353, 3), IR(31256, 23), IR(0, 0), IR(150, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpStencilAttachmentReadEXT, true, true, IR(353, 3), IR(31279, 25), IR(0, 0), IR(151, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpTypeTensorARM, true, false, IR(356, 4), IR(31304, 14), IR(0, 0), IR(198, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTensorReadARM, true, true, IR(360, 5), IR(31360, 14), IR(0, 0), IR(198, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpTensorWriteARM, false, false, IR(365, 4), IR(31374, 15), IR(0, 0), IR(198, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpTensorQuerySizeARM, true, true, IR(172, 4), IR(31389, 19), IR(0, 0), IR(198, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpTerminateInvocation, false, false, IR(0, 0), IR(31408, 20), IR(0, 0), IR(3, 1), IR(164, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpTypeUntypedPointerKHR, true, false, IR(369, 2), IR(31428, 22), IR(0, 0), IR(229, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpUntypedVariableKHR, true, true, IR(371, 5), IR(31450, 19), IR(0, 0), IR(229, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedAccessChainKHR, true, true, IR(151, 5), IR(31469, 22), IR(0, 0), IR(229, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedInBoundsAccessChainKHR, true, true, IR(151, 5), IR(31491, 30), IR(0, 0), IR(229, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpSubgroupBallotKHR, true, true, IR(160, 3), IR(5330, 18), IR(0, 0), IR(230, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupFirstInvocationKHR, true, true, IR(160, 3), IR(31521, 27), IR(0, 0), IR(230, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpUntypedPtrAccessChainKHR, true, true, IR(376, 6), IR(31548, 25), IR(0, 0), IR(229, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedInBoundsPtrAccessChainKHR, true, true, IR(376, 6), IR(31573, 33), IR(0, 0), IR(229, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedArrayLengthKHR, true, true, IR(382, 5), IR(31606, 22), IR(0, 0), IR(229, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedPrefetchKHR, false, false, IR(387, 5), IR(31628, 19), IR(0, 0), IR(229, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpSubgroupAllKHR, true, true, IR(160, 3), IR(31647, 15), IR(0, 0), IR(231, 1), IR(40, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupAnyKHR, true, true, IR(160, 3), IR(31662, 15), IR(0, 0), IR(231, 1), IR(40, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupAllEqualKHR, true, true, IR(160, 3), IR(31677, 20), IR(0, 0), IR(231, 1), IR(40, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupNonUniformRotateKHR, true, true, IR(392, 6), IR(13128, 25), IR(0, 0), IR(232, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupReadInvocationKHR, true, true, IR(172, 4), IR(31697, 26), IR(0, 0), IR(230, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpExtInstWithForwardRefsKHR, true, true, IR(398, 5), IR(31723, 26), IR(0, 0), IR(1, 0), IR(165, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpTraceRayKHR, false, false, IR(403, 11), IR(31749, 12), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpExecuteCallableKHR, false, false, IR(36, 2), IR(31761, 19), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToAccelerationStructureKHR, true, true, IR(160, 3), IR(31780, 35), IR(0, 0), IR(233, 2), IR(166, 2), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIgnoreIntersectionKHR, false, false, IR(0, 0), IR(31815, 22), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTerminateRayKHR, false, false, IR(0, 0), IR(31837, 16), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSDot, true, true, IR(414, 5), IR(31900, 5), IR(93, 1), IR(235, 1), IR(120, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDot, true, true, IR(414, 5), IR(31913, 5), IR(94, 1), IR(235, 1), IR(120, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSUDot, true, true, IR(414, 5), IR(31926, 6), IR(95, 1), IR(235, 1), IR(120, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSDotAccSat, true, true, IR(419, 6), IR(31941, 11), IR(96, 1), IR(235, 1), IR(120, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDotAccSat, true, true, IR(419, 6), IR(31966, 11), IR(97, 1), IR(235, 1), IR(120, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSUDotAccSat, true, true, IR(419, 6), IR(31991, 12), IR(98, 1), IR(235, 1), IR(120, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpTypeCooperativeMatrixKHR, true, false, IR(425, 6), IR(32018, 25), IR(0, 0), IR(236, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeMatrixLoadKHR, true, true, IR(431, 6), IR(32043, 25), IR(0, 0), IR(236, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixStoreKHR, false, false, IR(437, 5), IR(32068, 26), IR(0, 0), IR(236, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixMulAddKHR, true, true, IR(442, 6), IR(32148, 27), IR(0, 0), IR(236, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpCooperativeMatrixLengthKHR, true, true, IR(160, 3), IR(32175, 27), IR(0, 0), IR(236, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpConstantCompositeReplicateEXT, true, true, IR(160, 3), IR(32202, 30), IR(0, 0), IR(237, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCompositeReplicateEXT, true, true, IR(160, 3), IR(32232, 34), IR(0, 0), IR(237, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpCompositeConstructReplicateEXT, true, true, IR(160, 3), IR(32266, 31), IR(0, 0), IR(237, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpTypeRayQueryKHR, true, false, IR(68, 1), IR(32297, 16), IR(0, 0), IR(188, 1), IR(47, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpRayQueryInitializeKHR, false, false, IR(448, 8), IR(32313, 22), IR(0, 0), IR(188, 1), IR(47, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryTerminateKHR, false, false, IR(10, 1), IR(32335, 21), IR(0, 0), IR(188, 1), IR(47, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGenerateIntersectionKHR, false, false, IR(36, 2), IR(32356, 32), IR(0, 0), IR(188, 1), IR(47, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryConfirmIntersectionKHR, false, false, IR(10, 1), IR(32388, 31), IR(0, 0), IR(188, 1), IR(47, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryProceedKHR, true, true, IR(160, 3), IR(32419, 19), IR(0, 0), IR(188, 1), IR(47, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTypeKHR, true, true, IR(172, 4), IR(32438, 31), IR(0, 0), IR(188, 1), IR(47, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpImageSampleWeightedQCOM, true, true, IR(130, 5), IR(32469, 24), IR(0, 0), IR(238, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBoxFilterQCOM, true, true, IR(130, 5), IR(32493, 19), IR(0, 0), IR(239, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchSSDQCOM, true, true, IR(325, 7), IR(32512, 23), IR(0, 0), IR(240, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchSADQCOM, true, true, IR(325, 7), IR(32535, 23), IR(0, 0), IR(240, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchWindowSSDQCOM, true, true, IR(325, 7), IR(32558, 29), IR(0, 0), IR(241, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchWindowSADQCOM, true, true, IR(325, 7), IR(32587, 29), IR(0, 0), IR(241, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchGatherSSDQCOM, true, true, IR(325, 7), IR(32616, 29), IR(0, 0), IR(241, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchGatherSADQCOM, true, true, IR(325, 7), IR(32645, 29), IR(0, 0), IR(241, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpGroupIAddNonUniformAMD, true, true, IR(283, 5), IR(32674, 23), IR(0, 0), IR(214, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFAddNonUniformAMD, true, true, IR(283, 5), IR(32697, 23), IR(0, 0), IR(214, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMinNonUniformAMD, true, true, IR(283, 5), IR(32720, 23), IR(0, 0), IR(214, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMinNonUniformAMD, true, true, IR(283, 5), IR(32743, 23), IR(0, 0), IR(214, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMinNonUniformAMD, true, true, IR(283, 5), IR(32766, 23), IR(0, 0), IR(214, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMaxNonUniformAMD, true, true, IR(283, 5), IR(32789, 23), IR(0, 0), IR(214, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMaxNonUniformAMD, true, true, IR(283, 5), IR(32812, 23), IR(0, 0), IR(214, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMaxNonUniformAMD, true, true, IR(283, 5), IR(32835, 23), IR(0, 0), IR(214, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpFragmentMaskFetchAMD, true, true, IR(172, 4), IR(32858, 21), IR(0, 0), IR(242, 1), IR(56, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFragmentFetchAMD, true, true, IR(130, 5), IR(32879, 17), IR(0, 0), IR(242, 1), IR(56, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReadClockKHR, true, true, IR(340, 3), IR(32896, 13), IR(0, 0), IR(243, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAllocateNodePayloadsAMDX, true, true, IR(278, 5), IR(32909, 25), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpEnqueueNodePayloadsAMDX, false, false, IR(10, 1), IR(32934, 24), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeNodePayloadArrayAMDX, true, false, IR(87, 2), IR(32958, 25), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFinishWritingNodePayloadAMDX, true, true, IR(160, 3), IR(32983, 29), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpNodePayloadArrayLengthAMDX, true, true, IR(160, 3), IR(33012, 27), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIsNodePayloadValidAMDX, true, true, IR(172, 4), IR(33039, 23), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConstantStringAMDX, true, false, IR(50, 2), IR(33062, 19), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSpecConstantStringAMDX, true, false, IR(50, 2), IR(33081, 23), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpGroupNonUniformQuadAllKHR, true, true, IR(160, 3), IR(33104, 26), IR(0, 0), IR(158, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadAnyKHR, true, true, IR(160, 3), IR(33130, 26), IR(0, 0), IR(158, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpHitObjectRecordHitMotionNV, false, false, IR(456, 14), IR(33156, 27), IR(0, 0), IR(244, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitWithIndexMotionNV, false, false, IR(470, 13), IR(33183, 36), IR(0, 0), IR(244, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissMotionNV, false, false, IR(483, 7), IR(33219, 28), IR(0, 0), IR(244, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldToObjectNV, true, true, IR(160, 3), IR(33247, 28), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectToWorldNV, true, true, IR(160, 3), IR(33275, 28), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayDirectionNV, true, true, IR(160, 3), IR(33303, 33), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayOriginNV, true, true, IR(160, 3), IR(33336, 30), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayMotionNV, false, false, IR(470, 13), IR(33366, 26), IR(0, 0), IR(244, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderRecordBufferHandleNV, true, true, IR(160, 3), IR(33392, 39), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderBindingTableRecordIndexNV, true, true, IR(160, 3), IR(33431, 44), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordEmptyNV, false, false, IR(10, 1), IR(33475, 23), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayNV, false, false, IR(490, 12), IR(33498, 20), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitNV, false, false, IR(470, 13), IR(33518, 21), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitWithIndexNV, false, false, IR(490, 12), IR(33539, 30), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissNV, false, false, IR(502, 6), IR(33569, 22), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectExecuteShaderNV, false, false, IR(36, 2), IR(33591, 25), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetCurrentTimeNV, true, true, IR(160, 3), IR(33616, 26), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetAttributesNV, false, false, IR(36, 2), IR(33642, 25), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetHitKindNV, true, true, IR(160, 3), IR(33667, 22), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetPrimitiveIndexNV, true, true, IR(160, 3), IR(33689, 29), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetGeometryIndexNV, true, true, IR(160, 3), IR(33718, 28), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceIdNV, true, true, IR(160, 3), IR(33746, 25), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceCustomIndexNV, true, true, IR(160, 3), IR(33771, 34), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayDirectionNV, true, true, IR(160, 3), IR(33805, 32), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayOriginNV, true, true, IR(160, 3), IR(33837, 29), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMaxNV, true, true, IR(160, 3), IR(33866, 22), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMinNV, true, true, IR(160, 3), IR(33888, 22), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsEmptyNV, true, true, IR(160, 3), IR(33910, 19), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsHitNV, true, true, IR(160, 3), IR(33929, 17), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsMissNV, true, true, IR(160, 3), IR(33946, 18), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHitObjectNV, false, false, IR(508, 3), IR(33964, 29), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHintNV, false, false, IR(36, 2), IR(33993, 24), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeHitObjectNV, true, false, IR(68, 1), IR(34017, 16), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpImageSampleFootprintNV, true, true, IR(511, 7), IR(34033, 23), IR(0, 0), IR(246, 1), IR(70, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpTypeCooperativeVectorNV, true, false, IR(89, 3), IR(34056, 24), IR(0, 0), IR(247, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeVectorMatrixMulNV, true, true, IR(518, 13), IR(34080, 29), IR(0, 0), IR(247, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorOuterProductAccumulateNV, false, false, IR(531, 7), IR(34109, 42), IR(0, 0), IR(248, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorReduceSumAccumulateNV, false, false, IR(33, 3), IR(34151, 39), IR(0, 0), IR(248, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorMatrixMulAddNV, true, true, IR(538, 16), IR(34190, 32), IR(0, 0), IR(247, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixConvertNV, true, true, IR(160, 3), IR(34222, 27), IR(0, 0), IR(249, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpEmitMeshTasksEXT, false, false, IR(554, 4), IR(34249, 17), IR(0, 0), IR(53, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSetMeshOutputsEXT, false, false, IR(36, 2), IR(34266, 18), IR(0, 0), IR(53, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpGroupNonUniformPartitionNV, true, true, IR(160, 3), IR(34284, 27), IR(0, 0), IR(179, 1), IR(73, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpWritePackedPrimitiveIndices4x8NV, false, false, IR(36, 2), IR(34311, 33), IR(0, 0), IR(50, 1), IR(18, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFetchMicroTriangleVertexPositionNV, true, true, IR(325, 7), IR(34344, 35), IR(0, 0), IR(250, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFetchMicroTriangleVertexBarycentricNV, true, true, IR(325, 7), IR(34379, 38), IR(0, 0), IR(250, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorLoadNV, true, true, IR(558, 5), IR(34417, 24), IR(0, 0), IR(247, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeVectorStoreNV, false, false, IR(563, 4), IR(34441, 25), IR(0, 0), IR(247, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpReportIntersectionKHR, true, true, IR(172, 4), IR(34466, 22), IR(99, 1), IR(54, 2), IR(24, 2), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIgnoreIntersectionNV, false, false, IR(0, 0), IR(34509, 21), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTerminateRayNV, false, false, IR(0, 0), IR(34530, 15), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceNV, false, false, IR(403, 11), IR(34545, 8), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceMotionNV, false, false, IR(490, 12), IR(34553, 14), IR(0, 0), IR(57, 1), IR(27, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceRayMotionNV, false, false, IR(490, 12), IR(34567, 17), IR(0, 0), IR(57, 1), IR(27, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTriangleVertexPositionsKHR, true, true, IR(172, 4), IR(34584, 50), IR(0, 0), IR(251, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeAccelerationStructureKHR, true, false, IR(68, 1), IR(34634, 29), IR(100, 1), IR(252, 4), IR(168, 4), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpExecuteCallableNV, false, false, IR(36, 2), IR(34691, 18), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetClusterIdNV, true, true, IR(172, 4), IR(34709, 23), IR(0, 0), IR(64, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetClusterIdNV, true, true, IR(160, 3), IR(34732, 24), IR(0, 0), IR(64, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeCooperativeMatrixNV, true, false, IR(567, 5), IR(34756, 24), IR(0, 0), IR(256, 1), IR(77, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeMatrixLoadNV, true, true, IR(572, 6), IR(34780, 24), IR(0, 0), IR(256, 1), IR(77, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixStoreNV, false, false, IR(578, 5), IR(34804, 25), IR(0, 0), IR(256, 1), IR(77, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixMulAddNV, true, true, IR(130, 5), IR(34829, 26), IR(0, 0), IR(256, 1), IR(77, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixLengthNV, true, true, IR(160, 3), IR(34855, 26), IR(0, 0), IR(256, 1), IR(77, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpBeginInvocationInterlockEXT, false, false, IR(0, 0), IR(34881, 28), IR(0, 0), IR(257, 3), IR(78, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpEndInvocationInterlockEXT, false, false, IR(0, 0), IR(34909, 26), IR(0, 0), IR(257, 3), IR(78, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixReduceNV, true, true, IR(583, 5), IR(34978, 26), IR(0, 0), IR(260, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpCooperativeMatrixLoadTensorNV, true, true, IR(588, 7), IR(35079, 30), IR(0, 0), IR(196, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixStoreTensorNV, false, false, IR(595, 5), IR(35109, 31), IR(0, 0), IR(196, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixPerElementOpNV, true, true, IR(151, 5), IR(35140, 32), IR(0, 0), IR(261, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpTypeTensorLayoutNV, true, false, IR(89, 3), IR(35172, 19), IR(0, 0), IR(262, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeTensorViewNV, true, false, IR(600, 4), IR(35191, 17), IR(0, 0), IR(262, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCreateTensorLayoutNV, true, true, IR(39, 2), IR(35208, 21), IR(0, 0), IR(262, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetDimensionNV, true, true, IR(122, 4), IR(35229, 27), IR(0, 0), IR(262, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetStrideNV, true, true, IR(122, 4), IR(35256, 24), IR(0, 0), IR(262, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSliceNV, true, true, IR(122, 4), IR(35280, 20), IR(0, 0), IR(262, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetClampValueNV, true, true, IR(172, 4), IR(35300, 28), IR(0, 0), IR(262, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCreateTensorViewNV, true, true, IR(39, 2), IR(35328, 19), IR(0, 0), IR(262, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetDimensionNV, true, true, IR(122, 4), IR(35347, 25), IR(0, 0), IR(262, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetStrideNV, true, true, IR(122, 4), IR(35372, 22), IR(0, 0), IR(262, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpDemoteToHelperInvocation, false, false, IR(0, 0), IR(11440, 25), IR(45, 1), IR(263, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpIsHelperInvocationEXT, true, true, IR(39, 2), IR(35394, 22), IR(0, 0), IR(263, 1), IR(79, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetClipNV, true, true, IR(325, 7), IR(35416, 20), IR(0, 0), IR(262, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetBlockSizeNV, true, true, IR(122, 4), IR(35436, 27), IR(0, 0), IR(262, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixTransposeNV, true, true, IR(160, 3), IR(35463, 29), IR(0, 0), IR(249, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToImageNV, true, true, IR(160, 3), IR(35492, 18), IR(0, 0), IR(121, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToSamplerNV, true, true, IR(160, 3), IR(35510, 20), IR(0, 0), IR(121, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertImageToUNV, true, true, IR(160, 3), IR(35530, 18), IR(0, 0), IR(121, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertSamplerToUNV, true, true, IR(160, 3), IR(35548, 20), IR(0, 0), IR(121, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToSampledImageNV, true, true, IR(160, 3), IR(35568, 25), IR(0, 0), IR(121, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertSampledImageToUNV, true, true, IR(160, 3), IR(35593, 25), IR(0, 0), IR(121, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSamplerImageAddressingModeNV, false, false, IR(0, 1), IR(35618, 29), IR(0, 0), IR(121, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRawAccessChainNV, true, true, IR(604, 7), IR(35699, 17), IR(0, 0), IR(185, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpRayQueryGetIntersectionSpherePositionNV, true, true, IR(172, 4), IR(35716, 40), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionSphereRadiusNV, true, true, IR(172, 4), IR(35756, 38), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSPositionsNV, true, true, IR(172, 4), IR(35794, 38), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSRadiiNV, true, true, IR(172, 4), IR(35832, 34), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSHitValueNV, true, true, IR(172, 4), IR(35866, 37), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetSpherePositionNV, true, true, IR(160, 3), IR(35903, 29), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetSphereRadiusNV, true, true, IR(160, 3), IR(35932, 27), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetLSSPositionsNV, true, true, IR(160, 3), IR(35959, 27), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetLSSRadiiNV, true, true, IR(160, 3), IR(35986, 23), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsSphereHitNV, true, true, IR(160, 3), IR(36009, 23), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsLSSHitNV, true, true, IR(160, 3), IR(36032, 20), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryIsSphereHitNV, true, true, IR(172, 4), IR(36052, 22), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryIsLSSHitNV, true, true, IR(172, 4), IR(36074, 19), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSubgroupShuffleINTEL, true, true, IR(172, 4), IR(11888, 21), IR(0, 0), IR(264, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleDownINTEL, true, true, IR(130, 5), IR(36093, 25), IR(0, 0), IR(264, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleUpINTEL, true, true, IR(130, 5), IR(36118, 23), IR(0, 0), IR(264, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleXorINTEL, true, true, IR(172, 4), IR(36141, 24), IR(0, 0), IR(264, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupBlockReadINTEL, true, true, IR(160, 3), IR(36165, 23), IR(0, 0), IR(265, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupBlockWriteINTEL, false, false, IR(36, 2), IR(36188, 24), IR(0, 0), IR(265, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageBlockReadINTEL, true, true, IR(172, 4), IR(36212, 28), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageBlockWriteINTEL, false, false, IR(33, 3), IR(36240, 29), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageMediaBlockReadINTEL, true, true, IR(215, 6), IR(36269, 33), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageMediaBlockWriteINTEL, false, false, IR(611, 5), IR(36302, 34), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpUCountLeadingZerosINTEL, true, true, IR(160, 3), IR(36336, 24), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUCountTrailingZerosINTEL, true, true, IR(160, 3), IR(36360, 25), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAbsISubINTEL, true, true, IR(172, 4), IR(36385, 13), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAbsUSubINTEL, true, true, IR(172, 4), IR(36398, 13), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAddSatINTEL, true, true, IR(172, 4), IR(36411, 13), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAddSatINTEL, true, true, IR(172, 4), IR(36424, 13), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAverageINTEL, true, true, IR(172, 4), IR(36437, 14), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAverageINTEL, true, true, IR(172, 4), IR(36451, 14), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAverageRoundedINTEL, true, true, IR(172, 4), IR(36465, 21), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAverageRoundedINTEL, true, true, IR(172, 4), IR(36486, 21), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpISubSatINTEL, true, true, IR(172, 4), IR(36507, 13), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUSubSatINTEL, true, true, IR(172, 4), IR(36520, 13), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIMul32x16INTEL, true, true, IR(172, 4), IR(36533, 15), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUMul32x16INTEL, true, true, IR(172, 4), IR(36548, 15), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConstantFunctionPointerINTEL, true, true, IR(160, 3), IR(36563, 29), IR(0, 0), IR(194, 1), IR(93, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFunctionPointerCallINTEL, true, true, IR(107, 3), IR(36592, 25), IR(0, 0), IR(194, 1), IR(93, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmTargetINTEL, true, false, IR(50, 2), IR(36617, 15), IR(0, 0), IR(124, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmINTEL, true, true, IR(616, 6), IR(12106, 9), IR(0, 0), IR(124, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmCallINTEL, true, true, IR(122, 4), IR(36632, 13), IR(0, 0), IR(124, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAtomicFMinEXT, true, true, IR(235, 6), IR(36645, 14), IR(0, 0), IR(269, 4), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicFMaxEXT, true, true, IR(235, 6), IR(36659, 14), IR(0, 0), IR(269, 4), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAssumeTrueKHR, false, false, IR(10, 1), IR(36673, 14), IR(0, 0), IR(273, 1), IR(97, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpExpectKHR, true, true, IR(172, 4), IR(36687, 10), IR(0, 0), IR(273, 1), IR(97, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpDecorateString, false, false, IR(163, 2), IR(36697, 15), IR(101, 1), IR(1, 0), IR(172, 2), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpMemberDecorateString, false, false, IR(165, 3), IR(36733, 21), IR(102, 1), IR(1, 0), IR(172, 2), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpVmeImageINTEL, true, true, IR(172, 4), IR(36781, 14), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeVmeImageINTEL, true, false, IR(87, 2), IR(36795, 18), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImePayloadINTEL, true, false, IR(68, 1), IR(36813, 23), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcRefPayloadINTEL, true, false, IR(68, 1), IR(36836, 23), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcSicPayloadINTEL, true, false, IR(68, 1), IR(36859, 23), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcMcePayloadINTEL, true, false, IR(68, 1), IR(36882, 23), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcMceResultINTEL, true, false, IR(68, 1), IR(36905, 22), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultINTEL, true, false, IR(68, 1), IR(36927, 22), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultSingleReferenceStreamoutINTEL, true, false, IR(68, 1), IR(36949, 46), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultDualReferenceStreamoutINTEL, true, false, IR(68, 1), IR(36995, 44), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeSingleReferenceStreaminINTEL, true, false, IR(68, 1), IR(37039, 39), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeDualReferenceStreaminINTEL, true, false, IR(68, 1), IR(37078, 37), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcRefResultINTEL, true, false, IR(68, 1), IR(37115, 22), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcSicResultINTEL, true, false, IR(68, 1), IR(37137, 22), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL, true, true, IR(172, 4), IR(37159, 60), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL, true, true, IR(172, 4), IR(37219, 53), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterShapePenaltyINTEL, true, true, IR(172, 4), IR(37272, 47), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterShapePenaltyINTEL, true, true, IR(172, 4), IR(37319, 40), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL, true, true, IR(172, 4), IR(37359, 51), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterDirectionPenaltyINTEL, true, true, IR(172, 4), IR(37410, 44), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL, true, true, IR(172, 4), IR(37454, 51), IR(0, 0), IR(275, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL, true, true, IR(172, 4), IR(37505, 56), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL, true, true, IR(39, 2), IR(37561, 50), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL, true, true, IR(39, 2), IR(37611, 52), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL, true, true, IR(39, 2), IR(37663, 49), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetMotionVectorCostFunctionINTEL, true, true, IR(215, 6), IR(37712, 47), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL, true, true, IR(172, 4), IR(37759, 50), IR(0, 0), IR(275, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL, true, true, IR(39, 2), IR(37809, 51), IR(0, 0), IR(275, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL, true, true, IR(39, 2), IR(37860, 56), IR(0, 0), IR(277, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetAcOnlyHaarINTEL, true, true, IR(160, 3), IR(37916, 33), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL, true, true, IR(172, 4), IR(37949, 52), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL, true, true, IR(172, 4), IR(38001, 61), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL, true, true, IR(130, 5), IR(38062, 61), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToImePayloadINTEL, true, true, IR(160, 3), IR(38123, 39), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToImeResultINTEL, true, true, IR(160, 3), IR(38162, 38), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToRefPayloadINTEL, true, true, IR(160, 3), IR(38200, 39), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToRefResultINTEL, true, true, IR(160, 3), IR(38239, 38), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToSicPayloadINTEL, true, true, IR(160, 3), IR(38277, 39), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToSicResultINTEL, true, true, IR(160, 3), IR(38316, 38), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetMotionVectorsINTEL, true, true, IR(160, 3), IR(38354, 36), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterDistortionsINTEL, true, true, IR(160, 3), IR(38390, 39), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetBestInterDistortionsINTEL, true, true, IR(160, 3), IR(38429, 43), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMajorShapeINTEL, true, true, IR(160, 3), IR(38472, 38), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMinorShapeINTEL, true, true, IR(160, 3), IR(38510, 38), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterDirectionsINTEL, true, true, IR(160, 3), IR(38548, 38), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMotionVectorCountINTEL, true, true, IR(160, 3), IR(38586, 45), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterReferenceIdsINTEL, true, true, IR(160, 3), IR(38631, 40), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL, true, true, IR(130, 5), IR(38671, 62), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeInitializeINTEL, true, true, IR(130, 5), IR(38733, 30), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetSingleReferenceINTEL, true, true, IR(130, 5), IR(38763, 38), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetDualReferenceINTEL, true, true, IR(215, 6), IR(38801, 36), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeRefWindowSizeINTEL, true, true, IR(172, 4), IR(38837, 33), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeAdjustRefOffsetINTEL, true, true, IR(215, 6), IR(38870, 35), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(38905, 39), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetMaxMotionVectorCountINTEL, true, true, IR(172, 4), IR(38944, 43), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetUnidirectionalMixDisableINTEL, true, true, IR(160, 3), IR(38987, 47), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetEarlySearchTerminationThresholdINTEL, true, true, IR(172, 4), IR(39034, 54), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetWeightedSadINTEL, true, true, IR(172, 4), IR(39088, 34), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(39122, 47), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(39169, 45), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL, true, true, IR(215, 6), IR(39214, 55), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL, true, true, IR(325, 7), IR(39269, 53), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL, true, true, IR(130, 5), IR(39322, 56), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL, true, true, IR(215, 6), IR(39378, 54), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL, true, true, IR(215, 6), IR(39432, 58), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL, true, true, IR(325, 7), IR(39490, 56), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeConvertToMceResultINTEL, true, true, IR(160, 3), IR(39546, 38), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetSingleReferenceStreaminINTEL, true, true, IR(160, 3), IR(39584, 46), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetDualReferenceStreaminINTEL, true, true, IR(160, 3), IR(39630, 44), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeStripSingleReferenceStreamoutINTEL, true, true, IR(160, 3), IR(39674, 49), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeStripDualReferenceStreamoutINTEL, true, true, IR(160, 3), IR(39723, 47), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL, true, true, IR(172, 4), IR(39770, 70), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL, true, true, IR(172, 4), IR(39840, 68), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL, true, true, IR(172, 4), IR(39908, 69), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL, true, true, IR(130, 5), IR(39977, 68), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL, true, true, IR(130, 5), IR(40045, 66), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL, true, true, IR(130, 5), IR(40111, 67), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetBorderReachedINTEL, true, true, IR(172, 4), IR(40178, 36), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetTruncatedSearchIndicationINTEL, true, true, IR(160, 3), IR(40214, 48), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL, true, true, IR(160, 3), IR(40262, 59), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL, true, true, IR(160, 3), IR(40321, 58), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL, true, true, IR(160, 3), IR(40379, 56), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcFmeInitializeINTEL, true, true, IR(622, 9), IR(40435, 30), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcBmeInitializeINTEL, true, true, IR(631, 10), IR(40465, 30), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(40495, 39), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefSetBidirectionalMixDisableINTEL, true, true, IR(160, 3), IR(40534, 46), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefSetBilinearFilterEnableINTEL, true, true, IR(160, 3), IR(40580, 43), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(40623, 47), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(40670, 45), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithMultiReferenceINTEL, true, true, IR(130, 5), IR(40715, 46), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL, true, true, IR(215, 6), IR(40761, 56), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefConvertToMceResultINTEL, true, true, IR(160, 3), IR(40817, 38), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicInitializeINTEL, true, true, IR(160, 3), IR(40855, 30), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureSkcINTEL, true, true, IR(288, 8), IR(40885, 32), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureIpeLumaINTEL, true, true, IR(631, 10), IR(40917, 36), IR(0, 0), IR(275, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureIpeLumaChromaINTEL, true, true, IR(641, 13), IR(40953, 42), IR(0, 0), IR(277, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetMotionVectorMaskINTEL, true, true, IR(172, 4), IR(40995, 39), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(41034, 39), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraLumaShapePenaltyINTEL, true, true, IR(172, 4), IR(41073, 44), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraLumaModeCostFunctionINTEL, true, true, IR(215, 6), IR(41117, 48), IR(0, 0), IR(275, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraChromaModeCostFunctionINTEL, true, true, IR(172, 4), IR(41165, 50), IR(0, 0), IR(277, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetBilinearFilterEnableINTEL, true, true, IR(160, 3), IR(41215, 43), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetSkcForwardTransformEnableINTEL, true, true, IR(172, 4), IR(41258, 48), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetBlockBasedRawSkipSadINTEL, true, true, IR(172, 4), IR(41306, 43), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateIpeINTEL, true, true, IR(172, 4), IR(41349, 31), IR(0, 0), IR(275, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(41380, 47), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(41427, 45), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithMultiReferenceINTEL, true, true, IR(130, 5), IR(41472, 46), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL, true, true, IR(215, 6), IR(41518, 56), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConvertToMceResultINTEL, true, true, IR(160, 3), IR(41574, 38), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetIpeLumaShapeINTEL, true, true, IR(160, 3), IR(41612, 35), IR(0, 0), IR(275, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetBestIpeLumaDistortionINTEL, true, true, IR(160, 3), IR(41647, 44), IR(0, 0), IR(275, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetBestIpeChromaDistortionINTEL, true, true, IR(160, 3), IR(41691, 46), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedIpeLumaModesINTEL, true, true, IR(160, 3), IR(41737, 41), IR(0, 0), IR(275, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetIpeChromaModeINTEL, true, true, IR(160, 3), IR(41778, 36), IR(0, 0), IR(277, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL, true, true, IR(160, 3), IR(41814, 50), IR(0, 0), IR(275, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL, true, true, IR(160, 3), IR(41864, 48), IR(0, 0), IR(275, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetInterRawSadsINTEL, true, true, IR(160, 3), IR(41912, 35), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpVariableLengthArrayINTEL, true, true, IR(160, 3), IR(12344, 25), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSaveMemoryINTEL, true, true, IR(39, 2), IR(41947, 16), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpRestoreMemoryINTEL, false, false, IR(10, 1), IR(41963, 19), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinCosPiINTEL, true, true, IR(654, 8), IR(41982, 28), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastINTEL, true, true, IR(654, 8), IR(42010, 24), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastFromIntINTEL, true, true, IR(654, 8), IR(42034, 31), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastToIntINTEL, true, true, IR(654, 8), IR(42065, 29), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatAddINTEL, true, true, IR(662, 10), IR(42094, 23), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSubINTEL, true, true, IR(662, 10), IR(42117, 23), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatMulINTEL, true, true, IR(662, 10), IR(42140, 23), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatDivINTEL, true, true, IR(662, 10), IR(42163, 23), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatGTINTEL, true, true, IR(672, 6), IR(42186, 22), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatGEINTEL, true, true, IR(672, 6), IR(42208, 22), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLTINTEL, true, true, IR(672, 6), IR(42230, 22), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLEINTEL, true, true, IR(672, 6), IR(42252, 22), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatEQINTEL, true, true, IR(672, 6), IR(42274, 22), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatRecipINTEL, true, true, IR(654, 8), IR(42296, 25), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatRSqrtINTEL, true, true, IR(654, 8), IR(42321, 25), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCbrtINTEL, true, true, IR(654, 8), IR(42346, 24), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatHypotINTEL, true, true, IR(662, 10), IR(42370, 25), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSqrtINTEL, true, true, IR(654, 8), IR(42395, 24), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLogINTEL, true, true, IR(654, 8), IR(42419, 23), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog2INTEL, true, true, IR(654, 8), IR(42442, 24), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog10INTEL, true, true, IR(654, 8), IR(42466, 25), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog1pINTEL, true, true, IR(654, 8), IR(42491, 25), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExpINTEL, true, true, IR(654, 8), IR(42516, 23), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExp2INTEL, true, true, IR(654, 8), IR(42539, 24), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExp10INTEL, true, true, IR(654, 8), IR(42563, 25), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExpm1INTEL, true, true, IR(654, 8), IR(42588, 25), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinINTEL, true, true, IR(654, 8), IR(42613, 23), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCosINTEL, true, true, IR(654, 8), IR(42636, 23), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinCosINTEL, true, true, IR(654, 8), IR(42659, 26), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinPiINTEL, true, true, IR(654, 8), IR(42685, 25), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCosPiINTEL, true, true, IR(654, 8), IR(42710, 25), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatASinINTEL, true, true, IR(654, 8), IR(42735, 24), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatASinPiINTEL, true, true, IR(654, 8), IR(42759, 26), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatACosINTEL, true, true, IR(654, 8), IR(42785, 24), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatACosPiINTEL, true, true, IR(654, 8), IR(42809, 26), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATanINTEL, true, true, IR(654, 8), IR(42835, 24), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATanPiINTEL, true, true, IR(654, 8), IR(42859, 26), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATan2INTEL, true, true, IR(662, 10), IR(42885, 25), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowINTEL, true, true, IR(662, 10), IR(42910, 23), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowRINTEL, true, true, IR(662, 10), IR(42933, 24), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowNINTEL, true, true, IR(662, 10), IR(42957, 24), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpLoopControlINTEL, false, false, IR(18, 1), IR(42981, 17), IR(0, 0), IR(281, 1), IR(104, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAliasDomainDeclINTEL, true, false, IR(678, 2), IR(42998, 21), IR(0, 0), IR(130, 1), IR(111, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAliasScopeDeclINTEL, true, false, IR(680, 3), IR(43019, 20), IR(0, 0), IR(130, 1), IR(111, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAliasScopeListDeclINTEL, true, false, IR(92, 2), IR(43039, 24), IR(0, 0), IR(130, 1), IR(111, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSqrtINTEL, true, true, IR(654, 8), IR(43063, 15), IR(0, 0), IR(184, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedRecipINTEL, true, true, IR(654, 8), IR(43078, 16), IR(0, 0), IR(184, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedRsqrtINTEL, true, true, IR(654, 8), IR(43094, 16), IR(0, 0), IR(184, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinINTEL, true, true, IR(654, 8), IR(43110, 14), IR(0, 0), IR(184, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedCosINTEL, true, true, IR(654, 8), IR(43124, 14), IR(0, 0), IR(184, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinCosINTEL, true, true, IR(654, 8), IR(43138, 17), IR(0, 0), IR(184, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinPiINTEL, true, true, IR(654, 8), IR(43155, 16), IR(0, 0), IR(184, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedCosPiINTEL, true, true, IR(654, 8), IR(43171, 16), IR(0, 0), IR(184, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinCosPiINTEL, true, true, IR(654, 8), IR(43187, 19), IR(0, 0), IR(184, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedLogINTEL, true, true, IR(654, 8), IR(43206, 14), IR(0, 0), IR(184, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedExpINTEL, true, true, IR(654, 8), IR(43220, 14), IR(0, 0), IR(184, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpPtrCastToCrossWorkgroupINTEL, true, true, IR(160, 3), IR(43234, 29), IR(0, 0), IR(195, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpCrossWorkgroupCastToPtrINTEL, true, true, IR(160, 3), IR(43263, 29), IR(0, 0), IR(195, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpReadPipeBlockingINTEL, true, true, IR(172, 4), IR(43292, 22), IR(0, 0), IR(282, 1), IR(118, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpWritePipeBlockingINTEL, true, true, IR(172, 4), IR(43314, 23), IR(0, 0), IR(282, 1), IR(118, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpFPGARegINTEL, true, true, IR(160, 3), IR(12903, 13), IR(0, 0), IR(283, 1), IR(119, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetRayTMinKHR, true, true, IR(160, 3), IR(43337, 22), IR(0, 0), IR(188, 1), IR(47, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetRayFlagsKHR, true, true, IR(160, 3), IR(43359, 23), IR(0, 0), IR(188, 1), IR(47, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTKHR, true, true, IR(172, 4), IR(43382, 28), IR(0, 0), IR(188, 1), IR(47, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceCustomIndexKHR, true, true, IR(172, 4), IR(43410, 46), IR(0, 0), IR(188, 1), IR(47, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceIdKHR, true, true, IR(172, 4), IR(43456, 37), IR(0, 0), IR(188, 1), IR(47, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR, true, true, IR(172, 4), IR(43493, 65), IR(0, 0), IR(188, 1), IR(47, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionGeometryIndexKHR, true, true, IR(172, 4), IR(43558, 40), IR(0, 0), IR(188, 1), IR(47, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionPrimitiveIndexKHR, true, true, IR(172, 4), IR(43598, 41), IR(0, 0), IR(188, 1), IR(47, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionBarycentricsKHR, true, true, IR(172, 4), IR(43639, 39), IR(0, 0), IR(188, 1), IR(47, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionFrontFaceKHR, true, true, IR(172, 4), IR(43678, 36), IR(0, 0), IR(188, 1), IR(47, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionCandidateAABBOpaqueKHR, true, true, IR(160, 3), IR(43714, 46), IR(0, 0), IR(188, 1), IR(47, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectRayDirectionKHR, true, true, IR(172, 4), IR(43760, 45), IR(0, 0), IR(188, 1), IR(47, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectRayOriginKHR, true, true, IR(172, 4), IR(43805, 42), IR(0, 0), IR(188, 1), IR(47, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetWorldRayDirectionKHR, true, true, IR(160, 3), IR(43847, 32), IR(0, 0), IR(188, 1), IR(47, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetWorldRayOriginKHR, true, true, IR(160, 3), IR(43879, 29), IR(0, 0), IR(188, 1), IR(47, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectToWorldKHR, true, true, IR(172, 4), IR(43908, 40), IR(0, 0), IR(188, 1), IR(47, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionWorldToObjectKHR, true, true, IR(172, 4), IR(43948, 40), IR(0, 0), IR(188, 1), IR(47, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAtomicFAddEXT, true, true, IR(235, 6), IR(43988, 14), IR(0, 0), IR(284, 4), IR(126, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpTypeBufferSurfaceINTEL, true, false, IR(100, 2), IR(44002, 23), IR(0, 0), IR(122, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeStructContinuedINTEL, false, false, IR(683, 1), IR(44025, 25), IR(0, 0), IR(288, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantCompositeContinuedINTEL, false, false, IR(683, 1), IR(44050, 32), IR(0, 0), IR(288, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCompositeContinuedINTEL, false, false, IR(683, 1), IR(44082, 36), IR(0, 0), IR(288, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpCompositeConstructContinuedINTEL, true, true, IR(107, 3), IR(44118, 33), IR(0, 0), IR(288, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpConvertFToBF16INTEL, true, true, IR(160, 3), IR(44151, 20), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertBF16ToFINTEL, true, true, IR(160, 3), IR(44171, 20), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpControlBarrierArriveINTEL, false, false, IR(221, 3), IR(44191, 26), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpControlBarrierWaitINTEL, false, false, IR(221, 3), IR(44217, 24), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpArithmeticFenceEXT, true, true, IR(160, 3), IR(13335, 19), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpTaskSequenceCreateINTEL, true, true, IR(684, 7), IR(44241, 24), IR(0, 0), IR(292, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTaskSequenceAsyncINTEL, false, false, IR(168, 2), IR(44265, 23), IR(0, 0), IR(292, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTaskSequenceGetINTEL, true, true, IR(160, 3), IR(44288, 21), IR(0, 0), IR(292, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTaskSequenceReleaseINTEL, false, false, IR(10, 1), IR(44309, 25), IR(0, 0), IR(292, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeTaskSequenceINTEL, true, false, IR(68, 1), IR(44334, 22), IR(0, 0), IR(292, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpSubgroupBlockPrefetchINTEL, false, false, IR(139, 3), IR(44356, 27), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadINTEL, false, false, IR(691, 10), IR(44383, 25), IR(0, 0), IR(105, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadTransformINTEL, false, false, IR(691, 10), IR(44408, 34), IR(0, 0), IR(294, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadTransposeINTEL, false, false, IR(691, 10), IR(44442, 34), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockPrefetchINTEL, false, false, IR(701, 9), IR(44476, 29), IR(0, 0), IR(105, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockStoreINTEL, false, false, IR(691, 10), IR(44505, 26), IR(0, 0), IR(105, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupMatrixMultiplyAccumulateINTEL, true, true, IR(710, 7), IR(13673, 38), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpBitwiseFunctionINTEL, true, true, IR(215, 6), IR(44593, 21), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpGroupIMulKHR, true, true, IR(283, 5), IR(44614, 13), IR(0, 0), IR(298, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMulKHR, true, true, IR(283, 5), IR(44627, 13), IR(0, 0), IR(298, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseAndKHR, true, true, IR(283, 5), IR(44640, 19), IR(0, 0), IR(298, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseOrKHR, true, true, IR(283, 5), IR(44659, 18), IR(0, 0), IR(298, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseXorKHR, true, true, IR(283, 5), IR(44677, 19), IR(0, 0), IR(298, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalAndKHR, true, true, IR(283, 5), IR(44696, 19), IR(0, 0), IR(298, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalOrKHR, true, true, IR(283, 5), IR(44715, 18), IR(0, 0), IR(298, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalXorKHR, true, true, IR(283, 5), IR(44733, 19), IR(0, 0), IR(298, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpRoundFToTF32INTEL, true, true, IR(160, 3), IR(44752, 18), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpMaskedGatherINTEL, true, true, IR(717, 6), IR(44770, 18), IR(0, 0), IR(300, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpMaskedScatterINTEL, false, false, IR(723, 4), IR(44788, 19), IR(0, 0), IR(300, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpConvertHandleToImageINTEL, true, true, IR(160, 3), IR(44807, 26), IR(0, 0), IR(301, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertHandleToSamplerINTEL, true, true, IR(160, 3), IR(44833, 28), IR(0, 0), IR(301, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertHandleToSampledImageINTEL, true, true, IR(160, 3), IR(44861, 33), IR(0, 0), IR(301, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
}};

// Opcode strings (without the 'Op' prefix) and opcode values, ordered by name.
// The fields in order are:
//   name, either the primary name or an alias, indexing into kStrings
//   index into kInstructionDesc
static const std::array<NameIndex, 812> kInstructionNames{{
  {IR(36385, 13), 541}, // 0 AbsISubINTEL
  {IR(36398, 13), 542}, // 1 AbsUSubINTEL
  {IR(26453, 12), 58}, // 2 AccessChain
  {IR(42998, 21), 727}, // 3 AliasDomainDeclINTEL
  {IR(43019, 20), 728}, // 4 AliasScopeDeclINTEL
  {IR(43039, 24), 729}, // 5 AliasScopeListDeclINTEL
  {IR(27750, 4), 143}, // 6 All
  {IR(32909, 25), 413}, // 7 AllocateNodePayloadsAMDX
  {IR(27746, 4), 142}, // 8 Any
  {IR(42785, 24), 718}, // 9 ArbitraryFloatACosINTEL
  {IR(42809, 26), 719}, // 10 ArbitraryFloatACosPiINTEL
  {IR(42735, 24), 716}, // 11 ArbitraryFloatASinINTEL
  {IR(42759, 26), 717}, // 12 ArbitraryFloatASinPiINTEL
  {IR(42885, 25), 722}, // 13 ArbitraryFloatATan2INTEL
  {IR(42835, 24), 720}, // 14 ArbitraryFloatATanINTEL
  {IR(42859, 26), 721}, // 15 ArbitraryFloatATanPiINTEL
  {IR(42094, 23), 689}, // 16 ArbitraryFloatAddINTEL
  {IR(42034, 31), 687}, // 17 ArbitraryFloatCastFromIntINTEL
  {IR(42010, 24), 686}, // 18 ArbitraryFloatCastINTEL
  {IR(42065, 29), 688}, // 19 ArbitraryFloatCastToIntINTEL
  {IR(42346, 24), 700}, // 20 ArbitraryFloatCbrtINTEL
  {IR(42636, 23), 712}, // 21 ArbitraryFloatCosINTEL
  {IR(42710, 25), 715}, // 22 ArbitraryFloatCosPiINTEL
  {IR(42163, 23), 692}, // 23 ArbitraryFloatDivINTEL
  {IR(42274, 22), 697}, // 24 ArbitraryFloatEQINTEL
  {IR(42563, 25), 709}, // 25 ArbitraryFloatExp10INTEL
  {IR(42539, 24), 708}, // 26 ArbitraryFloatExp2INTEL
  {IR(42516, 23), 707}, // 27 ArbitraryFloatExpINTEL
  {IR(42588, 25), 710}, // 28 ArbitraryFloatExpm1INTEL
  {IR(42208, 22), 694}, // 29 ArbitraryFloatGEINTEL
  {IR(42186, 22), 693}, // 30 ArbitraryFloatGTINTEL
  {IR(42370, 25), 701}, // 31 ArbitraryFloatHypotINTEL
  {IR(42252, 22), 696}, // 32 ArbitraryFloatLEINTEL
  {IR(42230, 22), 695}, // 33 ArbitraryFloatLTINTEL
  {IR(42466, 25), 705}, // 34 ArbitraryFloatLog10INTEL
  {IR(42491, 25), 706}, // 35 ArbitraryFloatLog1pINTEL
  {IR(42442, 24), 704}, // 36 ArbitraryFloatLog2INTEL
  {IR(42419, 23), 703}, // 37 ArbitraryFloatLogINTEL
  {IR(42140, 23), 691}, // 38 ArbitraryFloatMulINTEL
  {IR(42910, 23), 723}, // 39 ArbitraryFloatPowINTEL
  {IR(42957, 24), 725}, // 40 ArbitraryFloatPowNINTEL
  {IR(42933, 24), 724}, // 41 ArbitraryFloatPowRINTEL
  {IR(42321, 25), 699}, // 42 ArbitraryFloatRSqrtINTEL
  {IR(42296, 25), 698}, // 43 ArbitraryFloatRecipINTEL
  {IR(42659, 26), 713}, // 44 ArbitraryFloatSinCosINTEL
  {IR(41982, 28), 685}, // 45 ArbitraryFloatSinCosPiINTEL
  {IR(42613, 23), 711}, // 46 ArbitraryFloatSinINTEL
  {IR(42685, 25), 714}, // 47 ArbitraryFloatSinPiINTEL
  {IR(42395, 24), 702}, // 48 ArbitraryFloatSqrtINTEL
  {IR(42117, 23), 690}, // 49 ArbitraryFloatSubINTEL
  {IR(13335, 19), 773}, // 50 ArithmeticFenceEXT
  {IR(26500, 12), 61}, // 51 ArrayLength
  {IR(36632, 13), 557}, // 52 AsmCallINTEL
  {IR(12106, 9), 556}, // 53 AsmINTEL
  {IR(36617, 15), 555}, // 54 AsmTargetINTEL
  {IR(36673, 14), 560}, // 55 AssumeTrueKHR
  {IR(28772, 10), 220}, // 56 AtomicAnd
  {IR(28624, 22), 210}, // 57 AtomicCompareExchange
  {IR(28646, 26), 211}, // 58 AtomicCompareExchangeWeak
  {IR(28609, 15), 209}, // 59 AtomicExchange
  {IR(43988, 14), 763}, // 60 AtomicFAddEXT
  {IR(36659, 14), 559}, // 61 AtomicFMaxEXT
  {IR(36645, 14), 558}, // 62 AtomicFMinEXT
  {IR(30157, 16), 292}, // 63 AtomicFlagClear
  {IR(30136, 21), 291}, // 64 AtomicFlagTestAndSet
  {IR(28706, 11), 214}, // 65 AtomicIAdd
  {IR(28689, 17), 213}, // 66 AtomicIDecrement
  {IR(28672, 17), 212}, // 67 AtomicIIncrement
  {IR(28717, 11), 215}, // 68 AtomicISub
  {IR(28586, 11), 207}, // 69 AtomicLoad
  {IR(28782, 9), 221}, // 70 AtomicOr
  {IR(28750, 11), 218}, // 71 AtomicSMax
  {IR(28728, 11), 216}, // 72 AtomicSMin
  {IR(28597, 12), 208}, // 73 AtomicStore
  {IR(28761, 11), 219}, // 74 AtomicUMax
  {IR(28739, 11), 217}, // 75 AtomicUMin
  {IR(28791, 10), 222}, // 76 AtomicXor
  {IR(34881, 28), 487}, // 77 BeginInvocationInterlockEXT
  {IR(28370, 9), 191}, // 78 BitCount
  {IR(28310, 15), 187}, // 79 BitFieldInsert
  {IR(28325, 17), 188}, // 80 BitFieldSExtract
  {IR(28342, 17), 189}, // 81 BitFieldUExtract
  {IR(28359, 11), 190}, // 82 BitReverse
  {IR(27498, 8), 114}, // 83 Bitcast
  {IR(28295, 11), 185}, // 84 BitwiseAnd
  {IR(44593, 21), 786}, // 85 BitwiseFunctionINTEL
  {IR(28274, 10), 183}, // 86 BitwiseOr
  {IR(28284, 11), 184}, // 87 BitwiseXor
  {IR(28901, 7), 227}, // 88 Branch
  {IR(28908, 18), 228}, // 89 BranchConditional
  {IR(29769, 13), 277}, // 90 BuildNDRange
  {IR(25514, 11), 15}, // 91 Capability
  {IR(29727, 26), 275}, // 92 CaptureEventProfilingInfo
  {IR(31233, 23), 344}, // 93 ColorAttachmentReadEXT
  {IR(29319, 15), 255}, // 94 CommitReadPipe
  {IR(29334, 16), 256}, // 95 CommitWritePipe
  {IR(26760, 19), 72}, // 96 CompositeConstruct
  {IR(44118, 33), 768}, // 97 CompositeConstructContinuedINTEL
  {IR(32266, 31), 386}, // 98 CompositeConstructReplicateEXT
  {IR(26779, 17), 73}, // 99 CompositeExtract
  {IR(26796, 16), 74}, // 100 CompositeInsert
  {IR(15254, 9), 39}, // 101 Constant
  {IR(26020, 18), 40}, // 102 ConstantComposite
  {IR(44050, 32), 766}, // 103 ConstantCompositeContinuedINTEL
  {IR(32202, 30), 384}, // 104 ConstantCompositeReplicateEXT
  {IR(25968, 14), 38}, // 105 ConstantFalse
  {IR(36563, 29), 553}, // 106 ConstantFunctionPointerINTEL
  {IR(26132, 13), 42}, // 107 ConstantNull
  {IR(30212, 20), 296}, // 108 ConstantPipeStorage
  {IR(26116, 16), 41}, // 109 ConstantSampler
  {IR(33062, 19), 419}, // 110 ConstantStringAMDX
  {IR(25955, 13), 37}, // 111 ConstantTrue
  {IR(28557, 15), 205}, // 112 ControlBarrier
  {IR(44191, 26), 771}, // 113 ControlBarrierArriveINTEL
  {IR(44217, 24), 772}, // 114 ControlBarrierWaitINTEL
  {IR(44171, 20), 770}, // 115 ConvertBF16ToFINTEL
  {IR(44151, 20), 769}, // 116 ConvertFToBF16INTEL
  {IR(27304, 12), 100}, // 117 ConvertFToS
  {IR(27292, 12), 99}, // 118 ConvertFToU
  {IR(44807, 26), 798}, // 119 ConvertHandleToImageINTEL
  {IR(44861, 33), 800}, // 120 ConvertHandleToSampledImageINTEL
  {IR(44833, 28), 799}, // 121 ConvertHandleToSamplerINTEL
  {IR(35530, 18), 510}, // 122 ConvertImageToUNV
  {IR(27381, 14), 107}, // 123 ConvertPtrToU
  {IR(27316, 12), 101}, // 124 ConvertSToF
  {IR(35593, 25), 513}, // 125 ConvertSampledImageToUNV
  {IR(35548, 20), 511}, // 126 ConvertSamplerToUNV
  {IR(31780, 35), 370}, // 127 ConvertUToAccelerationStructureKHR
  {IR(27328, 12), 102}, // 128 ConvertUToF
  {IR(35492, 18), 508}, // 129 ConvertUToImageNV
  {IR(27425, 14), 110}, // 130 ConvertUToPtr
  {IR(35568, 25), 512}, // 131 ConvertUToSampledImageNV
  {IR(35510, 20), 509}, // 132 ConvertUToSamplerNV
  {IR(34222, 27), 462}, // 133 CooperativeMatrixConvertNV
  {IR(32175, 27), 383}, // 134 CooperativeMatrixLengthKHR
  {IR(34855, 26), 486}, // 135 CooperativeMatrixLengthNV
  {IR(32043, 25), 380}, // 136 CooperativeMatrixLoadKHR
  {IR(34780, 24), 483}, // 137 CooperativeMatrixLoadNV
  {IR(35079, 30), 490}, // 138 CooperativeMatrixLoadTensorNV
  {IR(32148, 27), 382}, // 139 CooperativeMatrixMulAddKHR
  {IR(34829, 26), 485}, // 140 CooperativeMatrixMulAddNV
  {IR(35140, 32), 492}, // 141 CooperativeMatrixPerElementOpNV
  {IR(34978, 26), 489}, // 142 CooperativeMatrixReduceNV
  {IR(32068, 26), 381}, // 143 CooperativeMatrixStoreKHR
  {IR(34804, 25), 484}, // 144 CooperativeMatrixStoreNV
  {IR(35109, 31), 491}, // 145 CooperativeMatrixStoreTensorNV
  {IR(35463, 29), 507}, // 146 CooperativeMatrixTransposeNV
  {IR(34417, 24), 469}, // 147 CooperativeVectorLoadNV
  {IR(34190, 32), 461}, // 148 CooperativeVectorMatrixMulAddNV
  {IR(34080, 29), 458}, // 149 CooperativeVectorMatrixMulNV
  {IR(34109, 42), 459}, // 150 CooperativeVectorOuterProductAccumulateNV
  {IR(34151, 39), 460}, // 151 CooperativeVectorReduceSumAccumulateNV
  {IR(34441, 25), 470}, // 152 CooperativeVectorStoreNV
  {IR(31192, 12), 340}, // 153 CopyLogical
  {IR(26426, 11), 56}, // 154 CopyMemory
  {IR(26437, 16), 57}, // 155 CopyMemorySized
  {IR(26812, 11), 75}, // 156 CopyObject
  {IR(30232, 26), 297}, // 157 CreatePipeFromPipeStorage
  {IR(35208, 21), 495}, // 158 CreateTensorLayoutNV
  {IR(35328, 19), 500}, // 159 CreateTensorViewNV
  {IR(29679, 16), 272}, // 160 CreateUserEvent
  {IR(43263, 29), 742}, // 161 CrossWorkgroupCastToPtrINTEL
  {IR(28379, 5), 192}, // 162 DPdx
  {IR(28425, 11), 198}, // 163 DPdxCoarse
  {IR(28396, 9), 195}, // 164 DPdxFine
  {IR(28384, 5), 193}, // 165 DPdy
  {IR(28436, 11), 199}, // 166 DPdyCoarse
  {IR(28405, 9), 196}, // 167 DPdyFine
  {IR(26586, 9), 64}, // 168 Decorate
  {IR(30409, 11), 305}, // 169 DecorateId
  {IR(36697, 15), 562}, // 170 DecorateString
  {IR(36712, 21), 562}, // 171 DecorateStringGOOGLE
  {IR(26610, 16), 66}, // 172 DecorationGroup
  {IR(11440, 25), 503}, // 173 DemoteToHelperInvocation
  {IR(11465, 28), 503}, // 174 DemoteToHelperInvocationEXT
  {IR(31256, 23), 345}, // 175 DepthAttachmentReadEXT
  {IR(27695, 4), 137}, // 176 Dot
  {IR(34249, 17), 463}, // 177 EmitMeshTasksEXT
  {IR(28484, 17), 203}, // 178 EmitStreamVertex
  {IR(28460, 11), 201}, // 179 EmitVertex
  {IR(34909, 26), 488}, // 180 EndInvocationInterlockEXT
  {IR(28471, 13), 202}, // 181 EndPrimitive
  {IR(28501, 19), 204}, // 182 EndStreamPrimitive
  {IR(29515, 14), 265}, // 183 EnqueueKernel
  {IR(29501, 14), 264}, // 184 EnqueueMarker
  {IR(32934, 24), 414}, // 185 EnqueueNodePayloadsAMDX
  {IR(25429, 11), 13}, // 186 EntryPoint
  {IR(31761, 19), 369}, // 187 ExecuteCallableKHR
  {IR(34691, 18), 479}, // 188 ExecuteCallableNV
  {IR(25472, 14), 14}, // 189 ExecutionMode
  {IR(30393, 16), 304}, // 190 ExecutionModeId
  {IR(36687, 10), 561}, // 191 ExpectKHR
  {IR(25283, 8), 11}, // 192 ExtInst
  {IR(25223, 14), 10}, // 193 ExtInstImport
  {IR(31723, 26), 367}, // 194 ExtInstWithForwardRefsKHR
  {IR(25213, 10), 9}, // 195 Extension
  {IR(27527, 5), 118}, // 196 FAdd
  {IR(27358, 9), 105}, // 197 FConvert
  {IR(27562, 5), 125}, // 198 FDiv
  {IR(27587, 5), 130}, // 199 FMod
  {IR(27547, 5), 122}, // 200 FMul
  {IR(27514, 8), 116}, // 201 FNegate
  {IR(28024, 10), 168}, // 202 FOrdEqual
  {IR(28102, 16), 174}, // 203 FOrdGreaterThan
  {IR(28174, 21), 178}, // 204 FOrdGreaterThanEqual
  {IR(28074, 13), 172}, // 205 FOrdLessThan
  {IR(28136, 18), 176}, // 206 FOrdLessThanEqual
  {IR(28046, 13), 170}, // 207 FOrdNotEqual
  {IR(12903, 13), 745}, // 208 FPGARegINTEL
  {IR(27582, 5), 129}, // 209 FRem
  {IR(27537, 5), 120}, // 210 FSub
  {IR(28034, 12), 169}, // 211 FUnordEqual
  {IR(28118, 18), 175}, // 212 FUnordGreaterThan
  {IR(28195, 23), 179}, // 213 FUnordGreaterThanEqual
  {IR(28087, 15), 173}, // 214 FUnordLessThan
  {IR(28154, 20), 177}, // 215 FUnordLessThanEqual
  {IR(28059, 15), 171}, // 216 FUnordNotEqual
  {IR(34379, 38), 468}, // 217 FetchMicroTriangleVertexBarycentricNV
  {IR(34344, 35), 467}, // 218 FetchMicroTriangleVertexPositionNV
  {IR(32983, 29), 416}, // 219 FinishWritingNodePayloadAMDX
  {IR(43124, 14), 734}, // 220 FixedCosINTEL
  {IR(43171, 16), 737}, // 221 FixedCosPiINTEL
  {IR(43220, 14), 740}, // 222 FixedExpINTEL
  {IR(43206, 14), 739}, // 223 FixedLogINTEL
  {IR(43078, 16), 731}, // 224 FixedRecipINTEL
  {IR(43094, 16), 732}, // 225 FixedRsqrtINTEL
  {IR(43138, 17), 735}, // 226 FixedSinCosINTEL
  {IR(43187, 19), 738}, // 227 FixedSinCosPiINTEL
  {IR(43110, 14), 733}, // 228 FixedSinINTEL
  {IR(43155, 16), 736}, // 229 FixedSinPiINTEL
  {IR(43063, 15), 730}, // 230 FixedSqrtINTEL
  {IR(32879, 17), 411}, // 231 FragmentFetchAMD
  {IR(32858, 21), 410}, // 232 FragmentMaskFetchAMD
  {IR(24333, 9), 48}, // 233 Function
  {IR(26335, 13), 51}, // 234 FunctionCall
  {IR(26323, 12), 50}, // 235 FunctionEnd
  {IR(26305, 18), 49}, // 236 FunctionParameter
  {IR(36592, 25), 554}, // 237 FunctionPointerCallINTEL
  {IR(28389, 7), 194}, // 238 Fwidth
  {IR(28447, 13), 200}, // 239 FwidthCoarse
  {IR(28414, 11), 197}, // 240 FwidthFine
  {IR(27456, 17), 112}, // 241 GenericCastToPtr
  {IR(27473, 25), 113}, // 242 GenericCastToPtrExplicit
  {IR(26512, 23), 62}, // 243 GenericPtrMemSemantics
  {IR(29753, 16), 276}, // 244 GetDefaultQueue
  {IR(30258, 35), 298}, // 245 GetKernelLocalSizeForSubgroupCount
  {IR(30293, 25), 299}, // 246 GetKernelMaxNumSubgroups
  {IR(29559, 32), 267}, // 247 GetKernelNDrangeMaxSubGroupSize
  {IR(29529, 30), 266}, // 248 GetKernelNDrangeSubGroupCount
  {IR(29614, 40), 269}, // 249 GetKernelPreferredWorkGroupSizeMultiple
  {IR(29591, 23), 268}, // 250 GetKernelWorkGroupSize
  {IR(29385, 18), 259}, // 251 GetMaxPipePackets
  {IR(29367, 18), 258}, // 252 GetNumPipePackets
  {IR(29072, 9), 238}, // 253 GroupAll
  {IR(29081, 9), 239}, // 254 GroupAny
  {IR(29041, 15), 236}, // 255 GroupAsyncCopy
  {IR(44640, 19), 789}, // 256 GroupBitwiseAndKHR
  {IR(44659, 18), 790}, // 257 GroupBitwiseOrKHR
  {IR(44677, 19), 791}, // 258 GroupBitwiseXorKHR
  {IR(29090, 15), 240}, // 259 GroupBroadcast
  {IR(29460, 20), 262}, // 260 GroupCommitReadPipe
  {IR(29480, 21), 263}, // 261 GroupCommitWritePipe
  {IR(26626, 14), 67}, // 262 GroupDecorate
  {IR(29148, 10), 242}, // 263 GroupFAdd
  {IR(32697, 23), 403}, // 264 GroupFAddNonUniformAMD
  {IR(29188, 10), 246}, // 265 GroupFMax
  {IR(32789, 23), 407}, // 266 GroupFMaxNonUniformAMD
  {IR(29158, 10), 243}, // 267 GroupFMin
  {IR(32720, 23), 404}, // 268 GroupFMinNonUniformAMD
  {IR(44627, 13), 788}, // 269 GroupFMulKHR
  {IR(29138, 10), 241}, // 270 GroupIAdd
  {IR(32674, 23), 402}, // 271 GroupIAddNonUniformAMD
  {IR(44614, 13), 787}, // 272 GroupIMulKHR
  {IR(44696, 19), 792}, // 273 GroupLogicalAndKHR
  {IR(44715, 18), 793}, // 274 GroupLogicalOrKHR
  {IR(44733, 19), 794}, // 275 GroupLogicalXorKHR
  {IR(26685, 20), 68}, // 276 GroupMemberDecorate
  {IR(30441, 19), 307}, // 277 GroupNonUniformAll
  {IR(30479, 24), 309}, // 278 GroupNonUniformAllEqual
  {IR(30460, 19), 308}, // 279 GroupNonUniformAny
  {IR(5569, 22), 312}, // 280 GroupNonUniformBallot
  {IR(30619, 30), 315}, // 281 GroupNonUniformBallotBitCount
  {IR(30587, 32), 314}, // 282 GroupNonUniformBallotBitExtract
  {IR(30649, 29), 316}, // 283 GroupNonUniformBallotFindLSB
  {IR(30678, 29), 317}, // 284 GroupNonUniformBallotFindMSB
  {IR(30985, 26), 332}, // 285 GroupNonUniformBitwiseAnd
  {IR(31011, 25), 333}, // 286 GroupNonUniformBitwiseOr
  {IR(31036, 26), 334}, // 287 GroupNonUniformBitwiseXor
  {IR(30503, 25), 310}, // 288 GroupNonUniformBroadcast
  {IR(30528, 30), 311}, // 289 GroupNonUniformBroadcastFirst
  {IR(30420, 21), 306}, // 290 GroupNonUniformElect
  {IR(30805, 20), 323}, // 291 GroupNonUniformFAdd
  {IR(30965, 20), 331}, // 292 GroupNonUniformFMax
  {IR(30905, 20), 328}, // 293 GroupNonUniformFMin
  {IR(30845, 20), 325}, // 294 GroupNonUniformFMul
  {IR(30785, 20), 322}, // 295 GroupNonUniformIAdd
  {IR(30825, 20), 324}, // 296 GroupNonUniformIMul
  {IR(30558, 29), 313}, // 297 GroupNonUniformInverseBallot
  {IR(31062, 26), 335}, // 298 GroupNonUniformLogicalAnd
  {IR(31088, 25), 336}, // 299 GroupNonUniformLogicalOr
  {IR(31113, 26), 337}, // 300 GroupNonUniformLogicalXor
  {IR(34284, 27), 465}, // 301 GroupNonUniformPartitionNV
  {IR(33104, 26), 421}, // 302 GroupNonUniformQuadAllKHR
  {IR(33130, 26), 422}, // 303 GroupNonUniformQuadAnyKHR
  {IR(31139, 29), 338}, // 304 GroupNonUniformQuadBroadcast
  {IR(31168, 24), 339}, // 305 GroupNonUniformQuadSwap
  {IR(13128, 25), 365}, // 306 GroupNonUniformRotateKHR
  {IR(30925, 20), 329}, // 307 GroupNonUniformSMax
  {IR(30865, 20), 326}, // 308 GroupNonUniformSMin
  {IR(8659, 23), 318}, // 309 GroupNonUniformShuffle
  {IR(30758, 27), 321}, // 310 GroupNonUniformShuffleDown
  {IR(30733, 25), 320}, // 311 GroupNonUniformShuffleUp
  {IR(30707, 26), 319}, // 312 GroupNonUniformShuffleXor
  {IR(30945, 20), 330}, // 313 GroupNonUniformUMax
  {IR(30885, 20), 327}, // 314 GroupNonUniformUMin
  {IR(29403, 28), 260}, // 315 GroupReserveReadPipePackets
  {IR(29431, 29), 261}, // 316 GroupReserveWritePipePackets
  {IR(29208, 10), 248}, // 317 GroupSMax
  {IR(32835, 23), 409}, // 318 GroupSMaxNonUniformAMD
  {IR(29178, 10), 245}, // 319 GroupSMin
  {IR(32766, 23), 406}, // 320 GroupSMinNonUniformAMD
  {IR(29198, 10), 247}, // 321 GroupUMax
  {IR(32812, 23), 408}, // 322 GroupUMaxNonUniformAMD
  {IR(29168, 10), 244}, // 323 GroupUMin
  {IR(32743, 23), 405}, // 324 GroupUMinNonUniformAMD
  {IR(29056, 16), 237}, // 325 GroupWaitEvents
  {IR(33591, 25), 438}, // 326 HitObjectExecuteShaderNV
  {IR(33642, 25), 440}, // 327 HitObjectGetAttributesNV
  {IR(34732, 24), 481}, // 328 HitObjectGetClusterIdNV
  {IR(33616, 26), 439}, // 329 HitObjectGetCurrentTimeNV
  {IR(33718, 28), 443}, // 330 HitObjectGetGeometryIndexNV
  {IR(33667, 22), 441}, // 331 HitObjectGetHitKindNV
  {IR(33771, 34), 445}, // 332 HitObjectGetInstanceCustomIndexNV
  {IR(33746, 25), 444}, // 333 HitObjectGetInstanceIdNV
  {IR(35959, 27), 523}, // 334 HitObjectGetLSSPositionsNV
  {IR(35986, 23), 524}, // 335 HitObjectGetLSSRadiiNV
  {IR(33303, 33), 428}, // 336 HitObjectGetObjectRayDirectionNV
  {IR(33336, 30), 429}, // 337 HitObjectGetObjectRayOriginNV
  {IR(33275, 28), 427}, // 338 HitObjectGetObjectToWorldNV
  {IR(33689, 29), 442}, // 339 HitObjectGetPrimitiveIndexNV
  {IR(33866, 22), 448}, // 340 HitObjectGetRayTMaxNV
  {IR(33888, 22), 449}, // 341 HitObjectGetRayTMinNV
  {IR(33431, 44), 432}, // 342 HitObjectGetShaderBindingTableRecordIndexNV
  {IR(33392, 39), 431}, // 343 HitObjectGetShaderRecordBufferHandleNV
  {IR(35903, 29), 521}, // 344 HitObjectGetSpherePositionNV
  {IR(35932, 27), 522}, // 345 HitObjectGetSphereRadiusNV
  {IR(33805, 32), 446}, // 346 HitObjectGetWorldRayDirectionNV
  {IR(33837, 29), 447}, // 347 HitObjectGetWorldRayOriginNV
  {IR(33247, 28), 426}, // 348 HitObjectGetWorldToObjectNV
  {IR(33910, 19), 450}, // 349 HitObjectIsEmptyNV
  {IR(33929, 17), 451}, // 350 HitObjectIsHitNV
  {IR(36032, 20), 526}, // 351 HitObjectIsLSSHitNV
  {IR(33946, 18), 452}, // 352 HitObjectIsMissNV
  {IR(36009, 23), 525}, // 353 HitObjectIsSphereHitNV
  {IR(33475, 23), 433}, // 354 HitObjectRecordEmptyNV
  {IR(33156, 27), 423}, // 355 HitObjectRecordHitMotionNV
  {IR(33518, 21), 435}, // 356 HitObjectRecordHitNV
  {IR(33183, 36), 424}, // 357 HitObjectRecordHitWithIndexMotionNV
  {IR(33539, 30), 436}, // 358 HitObjectRecordHitWithIndexNV
  {IR(33219, 28), 425}, // 359 HitObjectRecordMissMotionNV
  {IR(33569, 22), 437}, // 360 HitObjectRecordMissNV
  {IR(33366, 26), 430}, // 361 HitObjectTraceRayMotionNV
  {IR(33498, 20), 434}, // 362 HitObjectTraceRayNV
  {IR(27522, 5), 117}, // 363 IAdd
  {IR(27699, 10), 138}, // 364 IAddCarry
  {IR(36411, 13), 543}, // 365 IAddSatINTEL
  {IR(36437, 14), 545}, // 366 IAverageINTEL
  {IR(36465, 21), 547}, // 367 IAverageRoundedINTEL
  {IR(27895, 7), 158}, // 368 IEqual
  {IR(27542, 5), 121}, // 369 IMul
  {IR(36533, 15), 551}, // 370 IMul32x16INTEL
  {IR(27902, 10), 159}, // 371 INotEqual
  {IR(27532, 5), 119}, // 372 ISub
  {IR(27709, 11), 139}, // 373 ISubBorrow
  {IR(36507, 13), 549}, // 374 ISubSatINTEL
  {IR(31815, 22), 371}, // 375 IgnoreIntersectionKHR
  {IR(34509, 21), 472}, // 376 IgnoreIntersectionNV
  {IR(24377, 6), 91}, // 377 Image
  {IR(32645, 29), 401}, // 378 ImageBlockMatchGatherSADQCOM
  {IR(32616, 29), 400}, // 379 ImageBlockMatchGatherSSDQCOM
  {IR(32535, 23), 397}, // 380 ImageBlockMatchSADQCOM
  {IR(32512, 23), 396}, // 381 ImageBlockMatchSSDQCOM
  {IR(32587, 29), 399}, // 382 ImageBlockMatchWindowSADQCOM
  {IR(32558, 29), 398}, // 383 ImageBlockMatchWindowSSDQCOM
  {IR(32493, 19), 395}, // 384 ImageBoxFilterQCOM
  {IR(27140, 16), 88}, // 385 ImageDrefGather
  {IR(27117, 11), 86}, // 386 ImageFetch
  {IR(27128, 12), 87}, // 387 ImageGather
  {IR(27177, 17), 92}, // 388 ImageQueryFormat
  {IR(27257, 17), 97}, // 389 ImageQueryLevels
  {IR(27243, 14), 96}, // 390 ImageQueryLod
  {IR(27194, 16), 93}, // 391 ImageQueryOrder
  {IR(27274, 18), 98}, // 392 ImageQuerySamples
  {IR(27228, 15), 95}, // 393 ImageQuerySize
  {IR(27210, 18), 94}, // 394 ImageQuerySizeLod
  {IR(27156, 10), 89}, // 395 ImageRead
  {IR(26974, 27), 81}, // 396 ImageSampleDrefExplicitLod
  {IR(26947, 27), 80}, // 397 ImageSampleDrefImplicitLod
  {IR(26924, 23), 79}, // 398 ImageSampleExplicitLod
  {IR(34033, 23), 456}, // 399 ImageSampleFootprintNV
  {IR(26878, 23), 78}, // 400 ImageSampleImplicitLod
  {IR(27086, 31), 85}, // 401 ImageSampleProjDrefExplicitLod
  {IR(27055, 31), 84}, // 402 ImageSampleProjDrefImplicitLod
  {IR(27028, 27), 83}, // 403 ImageSampleProjExplicitLod
  {IR(27001, 27), 82}, // 404 ImageSampleProjImplicitLod
  {IR(32469, 24), 394}, // 405 ImageSampleWeightedQCOM
  {IR(30081, 22), 288}, // 406 ImageSparseDrefGather
  {IR(30046, 17), 286}, // 407 ImageSparseFetch
  {IR(30063, 18), 287}, // 408 ImageSparseGather
  {IR(30173, 16), 293}, // 409 ImageSparseRead
  {IR(29873, 33), 281}, // 410 ImageSparseSampleDrefExplicitLod
  {IR(29840, 33), 280}, // 411 ImageSparseSampleDrefImplicitLod
  {IR(29811, 29), 279}, // 412 ImageSparseSampleExplicitLod
  {IR(29782, 29), 278}, // 413 ImageSparseSampleImplicitLod
  {IR(30009, 37), 285}, // 414 ImageSparseSampleProjDrefExplicitLod
  {IR(29972, 37), 284}, // 415 ImageSparseSampleProjDrefImplicitLod
  {IR(29939, 33), 283}, // 416 ImageSparseSampleProjExplicitLod
  {IR(29906, 33), 282}, // 417 ImageSparseSampleProjImplicitLod
  {IR(30103, 26), 289}, // 418 ImageSparseTexelsResident
  {IR(26357, 18), 53}, // 419 ImageTexelPointer
  {IR(27166, 11), 90}, // 420 ImageWrite
  {IR(26465, 20), 59}, // 421 InBoundsAccessChain
  {IR(26535, 23), 63}, // 422 InBoundsPtrAccessChain
  {IR(27766, 9), 146}, // 423 IsFinite
  {IR(35394, 22), 504}, // 424 IsHelperInvocationEXT
  {IR(27760, 6), 145}, // 425 IsInf
  {IR(27754, 6), 144}, // 426 IsNan
  {IR(33039, 23), 418}, // 427 IsNodePayloadValidAMDX
  {IR(27775, 9), 147}, // 428 IsNormal
  {IR(29695, 13), 273}, // 429 IsValidEvent
  {IR(29350, 17), 257}, // 430 IsValidReserveId
  {IR(28978, 5), 230}, // 431 Kill
  {IR(28895, 6), 226}, // 432 Label
  {IR(27795, 14), 149}, // 433 LessOrGreater
  {IR(29014, 14), 234}, // 434 LifetimeStart
  {IR(29028, 13), 235}, // 435 LifetimeStop
  {IR(25208, 5), 8}, // 436 Line
  {IR(26415, 5), 54}, // 437 Load
  {IR(27866, 11), 155}, // 438 LogicalAnd
  {IR(27827, 13), 152}, // 439 LogicalEqual
  {IR(27877, 11), 156}, // 440 LogicalNot
  {IR(27840, 16), 153}, // 441 LogicalNotEqual
  {IR(27856, 10), 154}, // 442 LogicalOr
  {IR(42981, 17), 726}, // 443 LoopControlINTEL
  {IR(28835, 10), 224}, // 444 LoopMerge
  {IR(44770, 18), 796}, // 445 MaskedGatherINTEL
  {IR(44788, 19), 797}, // 446 MaskedScatterINTEL
  {IR(27664, 18), 135}, // 447 MatrixTimesMatrix
  {IR(27610, 18), 132}, // 448 MatrixTimesScalar
  {IR(27646, 18), 134}, // 449 MatrixTimesVector
  {IR(26595, 15), 65}, // 450 MemberDecorate
  {IR(36733, 21), 563}, // 451 MemberDecorateString
  {IR(36754, 27), 563}, // 452 MemberDecorateStringGOOGLE
  {IR(25190, 11), 6}, // 453 MemberName
  {IR(28572, 14), 206}, // 454 MemoryBarrier
  {IR(25355, 12), 12}, // 455 MemoryModel
  {IR(30358, 19), 302}, // 456 MemoryNamedBarrier
  {IR(30377, 16), 303}, // 457 ModuleProcessed
  {IR(25185, 5), 5}, // 458 Name
  {IR(30335, 23), 301}, // 459 NamedBarrierInitialize
  {IR(30129, 7), 290}, // 460 NoLine
  {IR(33012, 27), 417}, // 461 NodePayloadArrayLengthAMDX
  {IR(24981, 4), 0}, // 462 Nop
  {IR(28306, 4), 186}, // 463 Not
  {IR(27809, 8), 150}, // 464 Ordered
  {IR(27682, 13), 136}, // 465 OuterProduct
  {IR(28801, 4), 223}, // 466 Phi
  {IR(26485, 15), 60}, // 467 PtrAccessChain
  {IR(43234, 29), 741}, // 468 PtrCastToCrossWorkgroupINTEL
  {IR(27439, 17), 111}, // 469 PtrCastToGeneric
  {IR(31225, 8), 343}, // 470 PtrDiff
  {IR(31204, 9), 341}, // 471 PtrEqual
  {IR(31213, 12), 342}, // 472 PtrNotEqual
  {IR(27367, 14), 106}, // 473 QuantizeToF16
  {IR(35699, 17), 515}, // 474 RawAccessChainNV
  {IR(32388, 31), 391}, // 475 RayQueryConfirmIntersectionKHR
  {IR(32356, 32), 390}, // 476 RayQueryGenerateIntersectionKHR
  {IR(34709, 23), 480}, // 477 RayQueryGetClusterIdNV
  {IR(43639, 39), 754}, // 478 RayQueryGetIntersectionBarycentricsKHR
  {IR(43714, 46), 756}, // 479 RayQueryGetIntersectionCandidateAABBOpaqueKHR
  {IR(43678, 36), 755}, // 480 RayQueryGetIntersectionFrontFaceKHR
  {IR(43558, 40), 752}, // 481 RayQueryGetIntersectionGeometryIndexKHR
  {IR(43410, 46), 749}, // 482 RayQueryGetIntersectionInstanceCustomIndexKHR
  {IR(43456, 37), 750}, // 483 RayQueryGetIntersectionInstanceIdKHR
  {IR(43493, 65), 751}, // 484 RayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR
  {IR(35866, 37), 520}, // 485 RayQueryGetIntersectionLSSHitValueNV
  {IR(35794, 38), 518}, // 486 RayQueryGetIntersectionLSSPositionsNV
  {IR(35832, 34), 519}, // 487 RayQueryGetIntersectionLSSRadiiNV
  {IR(43760, 45), 757}, // 488 RayQueryGetIntersectionObjectRayDirectionKHR
  {IR(43805, 42), 758}, // 489 RayQueryGetIntersectionObjectRayOriginKHR
  {IR(43908, 40), 761}, // 490 RayQueryGetIntersectionObjectToWorldKHR
  {IR(43598, 41), 753}, // 491 RayQueryGetIntersectionPrimitiveIndexKHR
  {IR(35716, 40), 516}, // 492 RayQueryGetIntersectionSpherePositionNV
  {IR(35756, 38), 517}, // 493 RayQueryGetIntersectionSphereRadiusNV
  {IR(43382, 28), 748}, // 494 RayQueryGetIntersectionTKHR
  {IR(34584, 50), 477}, // 495 RayQueryGetIntersectionTriangleVertexPositionsKHR
  {IR(32438, 31), 393}, // 496 RayQueryGetIntersectionTypeKHR
  {IR(43948, 40), 762}, // 497 RayQueryGetIntersectionWorldToObjectKHR
  {IR(43359, 23), 747}, // 498 RayQueryGetRayFlagsKHR
  {IR(43337, 22), 746}, // 499 RayQueryGetRayTMinKHR
  {IR(43847, 32), 759}, // 500 RayQueryGetWorldRayDirectionKHR
  {IR(43879, 29), 760}, // 501 RayQueryGetWorldRayOriginKHR
  {IR(32313, 22), 388}, // 502 RayQueryInitializeKHR
  {IR(36074, 19), 528}, // 503 RayQueryIsLSSHitNV
  {IR(36052, 22), 527}, // 504 RayQueryIsSphereHitNV
  {IR(32419, 19), 392}, // 505 RayQueryProceedKHR
  {IR(32335, 21), 389}, // 506 RayQueryTerminateKHR
  {IR(32896, 13), 412}, // 507 ReadClockKHR
  {IR(29218, 9), 249}, // 508 ReadPipe
  {IR(43292, 22), 743}, // 509 ReadPipeBlockingINTEL
  {IR(29666, 13), 271}, // 510 ReleaseEvent
  {IR(33993, 24), 454}, // 511 ReorderThreadWithHintNV
  {IR(33964, 29), 453}, // 512 ReorderThreadWithHitObjectNV
  {IR(34466, 22), 471}, // 513 ReportIntersectionKHR
  {IR(34488, 21), 471}, // 514 ReportIntersectionNV
  {IR(29272, 23), 253}, // 515 ReserveReadPipePackets
  {IR(29295, 24), 254}, // 516 ReserveWritePipePackets
  {IR(29237, 17), 251}, // 517 ReservedReadPipe
  {IR(29254, 18), 252}, // 518 ReservedWritePipe
  {IR(41963, 19), 684}, // 519 RestoreMemoryINTEL
  {IR(29654, 12), 270}, // 520 RetainEvent
  {IR(28983, 7), 231}, // 521 Return
  {IR(28990, 12), 232}, // 522 ReturnValue
  {IR(44752, 18), 795}, // 523 RoundFToTF32INTEL
  {IR(27349, 9), 104}, // 524 SConvert
  {IR(27557, 5), 124}, // 525 SDiv
  {IR(31900, 5), 373}, // 526 SDot
  {IR(31941, 11), 376}, // 527 SDotAccSat
  {IR(31952, 14), 376}, // 528 SDotAccSatKHR
  {IR(31905, 8), 373}, // 529 SDotKHR
  {IR(27925, 13), 161}, // 530 SGreaterThan
  {IR(27956, 18), 163}, // 531 SGreaterThanEqual
  {IR(27984, 10), 165}, // 532 SLessThan
  {IR(28009, 15), 167}, // 533 SLessThanEqual
  {IR(27577, 5), 128}, // 534 SMod
  {IR(27733, 13), 141}, // 535 SMulExtended
  {IR(27506, 8), 115}, // 536 SNegate
  {IR(27572, 5), 127}, // 537 SRem
  {IR(31926, 6), 375}, // 538 SUDot
  {IR(31991, 12), 378}, // 539 SUDotAccSat
  {IR(32003, 15), 378}, // 540 SUDotAccSatKHR
  {IR(31932, 9), 375}, // 541 SUDotKHR
  {IR(26833, 13), 77}, // 542 SampledImage
  {IR(35618, 29), 514}, // 543 SamplerImageAddressingModeNV
  {IR(27395, 15), 108}, // 544 SatConvertSToU
  {IR(27410, 15), 109}, // 545 SatConvertUToS
  {IR(41947, 16), 683}, // 546 SaveMemoryINTEL
  {IR(27888, 7), 157}, // 547 Select
  {IR(28880, 15), 225}, // 548 SelectionMerge
  {IR(34266, 18), 464}, // 549 SetMeshOutputsEXT
  {IR(29708, 19), 274}, // 550 SetUserEventStatus
  {IR(28257, 17), 182}, // 551 ShiftLeftLogical
  {IR(28236, 21), 181}, // 552 ShiftRightArithmetic
  {IR(28218, 18), 180}, // 553 ShiftRightLogical
  {IR(27784, 11), 148}, // 554 SignBitSet
  {IR(30189, 7), 294}, // 555 SizeOf
  {IR(25162, 7), 3}, // 556 Source
  {IR(25043, 16), 2}, // 557 SourceContinued
  {IR(25169, 16), 4}, // 558 SourceExtension
  {IR(26180, 13), 45}, // 559 SpecConstant
  {IR(26193, 22), 46}, // 560 SpecConstantComposite
  {IR(44082, 36), 767}, // 561 SpecConstantCompositeContinuedINTEL
  {IR(32232, 34), 385}, // 562 SpecConstantCompositeReplicateEXT
  {IR(26162, 18), 44}, // 563 SpecConstantFalse
  {IR(26256, 15), 47}, // 564 SpecConstantOp
  {IR(33081, 23), 420}, // 565 SpecConstantStringAMDX
  {IR(26145, 17), 43}, // 566 SpecConstantTrue
  {IR(31279, 25), 346}, // 567 StencilAttachmentReadEXT
  {IR(26420, 6), 55}, // 568 Store
  {IR(25201, 7), 7}, // 569 String
  {IR(44383, 25), 780}, // 570 Subgroup2DBlockLoadINTEL
  {IR(44408, 34), 781}, // 571 Subgroup2DBlockLoadTransformINTEL
  {IR(44442, 34), 782}, // 572 Subgroup2DBlockLoadTransposeINTEL
  {IR(44476, 29), 783}, // 573 Subgroup2DBlockPrefetchINTEL
  {IR(44505, 26), 784}, // 574 Subgroup2DBlockStoreINTEL
  {IR(31677, 20), 364}, // 575 SubgroupAllEqualKHR
  {IR(31647, 15), 362}, // 576 SubgroupAllKHR
  {IR(31662, 15), 363}, // 577 SubgroupAnyKHR
  {IR(40465, 30), 647}, // 578 SubgroupAvcBmeInitializeINTEL
  {IR(40435, 30), 646}, // 579 SubgroupAvcFmeInitializeINTEL
  {IR(38870, 35), 616}, // 580 SubgroupAvcImeAdjustRefOffsetINTEL
  {IR(38905, 39), 617}, // 581 SubgroupAvcImeConvertToMcePayloadINTEL
  {IR(39546, 38), 630}, // 582 SubgroupAvcImeConvertToMceResultINTEL
  {IR(39169, 45), 623}, // 583 SubgroupAvcImeEvaluateWithDualReferenceINTEL
  {IR(39269, 53), 625}, // 584 SubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL
  {IR(39490, 56), 629}, // 585 SubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL
  {IR(39378, 54), 627}, // 586 SubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL
  {IR(39122, 47), 622}, // 587 SubgroupAvcImeEvaluateWithSingleReferenceINTEL
  {IR(39214, 55), 624}, // 588 SubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL
  {IR(39432, 58), 628}, // 589 SubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL
  {IR(39322, 56), 626}, // 590 SubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL
  {IR(40178, 36), 641}, // 591 SubgroupAvcImeGetBorderReachedINTEL
  {IR(39630, 44), 632}, // 592 SubgroupAvcImeGetDualReferenceStreaminINTEL
  {IR(39584, 46), 631}, // 593 SubgroupAvcImeGetSingleReferenceStreaminINTEL
  {IR(40045, 66), 639}, // 594 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL
  {IR(39977, 68), 638}, // 595 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL
  {IR(40111, 67), 640}, // 596 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL
  {IR(39840, 68), 636}, // 597 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL
  {IR(39770, 70), 635}, // 598 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL
  {IR(39908, 69), 637}, // 599 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL
  {IR(40214, 48), 642}, // 600 SubgroupAvcImeGetTruncatedSearchIndicationINTEL
  {IR(40262, 59), 643}, // 601 SubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL
  {IR(40379, 56), 645}, // 602 SubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL
  {IR(40321, 58), 644}, // 603 SubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL
  {IR(38733, 30), 612}, // 604 SubgroupAvcImeInitializeINTEL
  {IR(38837, 33), 615}, // 605 SubgroupAvcImeRefWindowSizeINTEL
  {IR(38801, 36), 614}, // 606 SubgroupAvcImeSetDualReferenceINTEL
  {IR(39034, 54), 620}, // 607 SubgroupAvcImeSetEarlySearchTerminationThresholdINTEL
  {IR(38944, 43), 618}, // 608 SubgroupAvcImeSetMaxMotionVectorCountINTEL
  {IR(38763, 38), 613}, // 609 SubgroupAvcImeSetSingleReferenceINTEL
  {IR(38987, 47), 619}, // 610 SubgroupAvcImeSetUnidirectionalMixDisableINTEL
  {IR(39088, 34), 621}, // 611 SubgroupAvcImeSetWeightedSadINTEL
  {IR(39723, 47), 634}, // 612 SubgroupAvcImeStripDualReferenceStreamoutINTEL
  {IR(39674, 49), 633}, // 613 SubgroupAvcImeStripSingleReferenceStreamoutINTEL
  {IR(38123, 39), 597}, // 614 SubgroupAvcMceConvertToImePayloadINTEL
  {IR(38162, 38), 598}, // 615 SubgroupAvcMceConvertToImeResultINTEL
  {IR(38200, 39), 599}, // 616 SubgroupAvcMceConvertToRefPayloadINTEL
  {IR(38239, 38), 600}, // 617 SubgroupAvcMceConvertToRefResultINTEL
  {IR(38277, 39), 601}, // 618 SubgroupAvcMceConvertToSicPayloadINTEL
  {IR(38316, 38), 602}, // 619 SubgroupAvcMceConvertToSicResultINTEL
  {IR(38429, 43), 605}, // 620 SubgroupAvcMceGetBestInterDistortionsINTEL
  {IR(37561, 50), 586}, // 621 SubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL
  {IR(37159, 60), 578}, // 622 SubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL
  {IR(37359, 51), 582}, // 623 SubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL
  {IR(37505, 56), 585}, // 624 SubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL
  {IR(37272, 47), 580}, // 625 SubgroupAvcMceGetDefaultInterShapePenaltyINTEL
  {IR(37860, 56), 592}, // 626 SubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL
  {IR(37759, 50), 590}, // 627 SubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL
  {IR(37454, 51), 584}, // 628 SubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL
  {IR(37663, 49), 588}, // 629 SubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL
  {IR(37611, 52), 587}, // 630 SubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL
  {IR(37809, 51), 591}, // 631 SubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL
  {IR(38548, 38), 608}, // 632 SubgroupAvcMceGetInterDirectionsINTEL
  {IR(38390, 39), 604}, // 633 SubgroupAvcMceGetInterDistortionsINTEL
  {IR(38472, 38), 606}, // 634 SubgroupAvcMceGetInterMajorShapeINTEL
  {IR(38510, 38), 607}, // 635 SubgroupAvcMceGetInterMinorShapeINTEL
  {IR(38586, 45), 609}, // 636 SubgroupAvcMceGetInterMotionVectorCountINTEL
  {IR(38631, 40), 610}, // 637 SubgroupAvcMceGetInterReferenceIdsINTEL
  {IR(38671, 62), 611}, // 638 SubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL
  {IR(38354, 36), 603}, // 639 SubgroupAvcMceGetMotionVectorsINTEL
  {IR(37916, 33), 593}, // 640 SubgroupAvcMceSetAcOnlyHaarINTEL
  {IR(38062, 61), 596}, // 641 SubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL
  {IR(37219, 53), 579}, // 642 SubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL
  {IR(37410, 44), 583}, // 643 SubgroupAvcMceSetInterDirectionPenaltyINTEL
  {IR(37319, 40), 581}, // 644 SubgroupAvcMceSetInterShapePenaltyINTEL
  {IR(37712, 47), 589}, // 645 SubgroupAvcMceSetMotionVectorCostFunctionINTEL
  {IR(38001, 61), 595}, // 646 SubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL
  {IR(37949, 52), 594}, // 647 SubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL
  {IR(40495, 39), 648}, // 648 SubgroupAvcRefConvertToMcePayloadINTEL
  {IR(40817, 38), 655}, // 649 SubgroupAvcRefConvertToMceResultINTEL
  {IR(40670, 45), 652}, // 650 SubgroupAvcRefEvaluateWithDualReferenceINTEL
  {IR(40715, 46), 653}, // 651 SubgroupAvcRefEvaluateWithMultiReferenceINTEL
  {IR(40761, 56), 654}, // 652 SubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL
  {IR(40623, 47), 651}, // 653 SubgroupAvcRefEvaluateWithSingleReferenceINTEL
  {IR(40534, 46), 649}, // 654 SubgroupAvcRefSetBidirectionalMixDisableINTEL
  {IR(40580, 43), 650}, // 655 SubgroupAvcRefSetBilinearFilterEnableINTEL
  {IR(40953, 42), 659}, // 656 SubgroupAvcSicConfigureIpeLumaChromaINTEL
  {IR(40917, 36), 658}, // 657 SubgroupAvcSicConfigureIpeLumaINTEL
  {IR(40885, 32), 657}, // 658 SubgroupAvcSicConfigureSkcINTEL
  {IR(41034, 39), 661}, // 659 SubgroupAvcSicConvertToMcePayloadINTEL
  {IR(41574, 38), 673}, // 660 SubgroupAvcSicConvertToMceResultINTEL
  {IR(41349, 31), 668}, // 661 SubgroupAvcSicEvaluateIpeINTEL
  {IR(41427, 45), 670}, // 662 SubgroupAvcSicEvaluateWithDualReferenceINTEL
  {IR(41472, 46), 671}, // 663 SubgroupAvcSicEvaluateWithMultiReferenceINTEL
  {IR(41518, 56), 672}, // 664 SubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL
  {IR(41380, 47), 669}, // 665 SubgroupAvcSicEvaluateWithSingleReferenceINTEL
  {IR(41691, 46), 676}, // 666 SubgroupAvcSicGetBestIpeChromaDistortionINTEL
  {IR(41647, 44), 675}, // 667 SubgroupAvcSicGetBestIpeLumaDistortionINTEL
  {IR(41912, 35), 681}, // 668 SubgroupAvcSicGetInterRawSadsINTEL
  {IR(41778, 36), 678}, // 669 SubgroupAvcSicGetIpeChromaModeINTEL
  {IR(41612, 35), 674}, // 670 SubgroupAvcSicGetIpeLumaShapeINTEL
  {IR(40995, 39), 660}, // 671 SubgroupAvcSicGetMotionVectorMaskINTEL
  {IR(41737, 41), 677}, // 672 SubgroupAvcSicGetPackedIpeLumaModesINTEL
  {IR(41814, 50), 679}, // 673 SubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL
  {IR(41864, 48), 680}, // 674 SubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL
  {IR(40855, 30), 656}, // 675 SubgroupAvcSicInitializeINTEL
  {IR(41215, 43), 665}, // 676 SubgroupAvcSicSetBilinearFilterEnableINTEL
  {IR(41306, 43), 667}, // 677 SubgroupAvcSicSetBlockBasedRawSkipSadINTEL
  {IR(41165, 50), 664}, // 678 SubgroupAvcSicSetIntraChromaModeCostFunctionINTEL
  {IR(41117, 48), 663}, // 679 SubgroupAvcSicSetIntraLumaModeCostFunctionINTEL
  {IR(41073, 44), 662}, // 680 SubgroupAvcSicSetIntraLumaShapePenaltyINTEL
  {IR(41258, 48), 666}, // 681 SubgroupAvcSicSetSkcForwardTransformEnableINTEL
  {IR(5330, 18), 356}, // 682 SubgroupBallotKHR
  {IR(44356, 27), 779}, // 683 SubgroupBlockPrefetchINTEL
  {IR(36165, 23), 533}, // 684 SubgroupBlockReadINTEL
  {IR(36188, 24), 534}, // 685 SubgroupBlockWriteINTEL
  {IR(31521, 27), 357}, // 686 SubgroupFirstInvocationKHR
  {IR(36212, 28), 535}, // 687 SubgroupImageBlockReadINTEL
  {IR(36240, 29), 536}, // 688 SubgroupImageBlockWriteINTEL
  {IR(36269, 33), 537}, // 689 SubgroupImageMediaBlockReadINTEL
  {IR(36302, 34), 538}, // 690 SubgroupImageMediaBlockWriteINTEL
  {IR(13673, 38), 785}, // 691 SubgroupMatrixMultiplyAccumulateINTEL
  {IR(31697, 26), 366}, // 692 SubgroupReadInvocationKHR
  {IR(36093, 25), 530}, // 693 SubgroupShuffleDownINTEL
  {IR(11888, 21), 529}, // 694 SubgroupShuffleINTEL
  {IR(36118, 23), 531}, // 695 SubgroupShuffleUpINTEL
  {IR(36141, 24), 532}, // 696 SubgroupShuffleXorINTEL
  {IR(28971, 7), 229}, // 697 Switch
  {IR(44265, 23), 775}, // 698 TaskSequenceAsyncINTEL
  {IR(44241, 24), 774}, // 699 TaskSequenceCreateINTEL
  {IR(44288, 21), 776}, // 700 TaskSequenceGetINTEL
  {IR(44309, 25), 777}, // 701 TaskSequenceReleaseINTEL
  {IR(35436, 27), 506}, // 702 TensorLayoutSetBlockSizeNV
  {IR(35300, 28), 499}, // 703 TensorLayoutSetClampValueNV
  {IR(35229, 27), 496}, // 704 TensorLayoutSetDimensionNV
  {IR(35256, 24), 497}, // 705 TensorLayoutSetStrideNV
  {IR(35280, 20), 498}, // 706 TensorLayoutSliceNV
  {IR(31389, 19), 350}, // 707 TensorQuerySizeARM
  {IR(31360, 14), 348}, // 708 TensorReadARM
  {IR(35416, 20), 505}, // 709 TensorViewSetClipNV
  {IR(35347, 25), 501}, // 710 TensorViewSetDimensionNV
  {IR(35372, 22), 502}, // 711 TensorViewSetStrideNV
  {IR(31374, 15), 349}, // 712 TensorWriteARM
  {IR(31408, 20), 351}, // 713 TerminateInvocation
  {IR(31837, 16), 372}, // 714 TerminateRayKHR
  {IR(34530, 15), 473}, // 715 TerminateRayNV
  {IR(34553, 14), 475}, // 716 TraceMotionNV
  {IR(34545, 8), 474}, // 717 TraceNV
  {IR(31749, 12), 368}, // 718 TraceRayKHR
  {IR(34567, 17), 476}, // 719 TraceRayMotionNV
  {IR(26823, 10), 76}, // 720 Transpose
  {IR(34634, 29), 478}, // 721 TypeAccelerationStructureKHR
  {IR(34663, 28), 478}, // 722 TypeAccelerationStructureNV
  {IR(25772, 10), 25}, // 723 TypeArray
  {IR(37078, 37), 575}, // 724 TypeAvcImeDualReferenceStreaminINTEL
  {IR(36813, 23), 566}, // 725 TypeAvcImePayloadINTEL
  {IR(36995, 44), 573}, // 726 TypeAvcImeResultDualReferenceStreamoutINTEL
  {IR(36927, 22), 571}, // 727 TypeAvcImeResultINTEL
  {IR(36949, 46), 572}, // 728 TypeAvcImeResultSingleReferenceStreamoutINTEL
  {IR(37039, 39), 574}, // 729 TypeAvcImeSingleReferenceStreaminINTEL
  {IR(36882, 23), 569}, // 730 TypeAvcMcePayloadINTEL
  {IR(36905, 22), 570}, // 731 TypeAvcMceResultINTEL
  {IR(36836, 23), 567}, // 732 TypeAvcRefPayloadINTEL
  {IR(37115, 22), 576}, // 733 TypeAvcRefResultINTEL
  {IR(36859, 23), 568}, // 734 TypeAvcSicPayloadINTEL
  {IR(37137, 22), 577}, // 735 TypeAvcSicResultINTEL
  {IR(25534, 9), 17}, // 736 TypeBool
  {IR(44002, 23), 764}, // 737 TypeBufferSurfaceINTEL
  {IR(32018, 25), 379}, // 738 TypeCooperativeMatrixKHR
  {IR(34756, 24), 482}, // 739 TypeCooperativeMatrixNV
  {IR(34056, 24), 457}, // 740 TypeCooperativeVectorNV
  {IR(25887, 16), 32}, // 741 TypeDeviceEvent
  {IR(25877, 10), 31}, // 742 TypeEvent
  {IR(25588, 10), 19}, // 743 TypeFloat
  {IR(25936, 19), 36}, // 744 TypeForwardPointer
  {IR(25864, 13), 30}, // 745 TypeFunction
  {IR(34017, 16), 455}, // 746 TypeHitObjectNV
  {IR(25733, 10), 22}, // 747 TypeImage
  {IR(25543, 8), 18}, // 748 TypeInt
  {IR(25609, 11), 21}, // 749 TypeMatrix
  {IR(30318, 17), 300}, // 750 TypeNamedBarrier
  {IR(32958, 25), 415}, // 751 TypeNodePayloadArrayAMDX
  {IR(25810, 11), 28}, // 752 TypeOpaque
  {IR(25927, 9), 35}, // 753 TypePipe
  {IR(30196, 16), 295}, // 754 TypePipeStorage
  {IR(25852, 12), 29}, // 755 TypePointer
  {IR(25917, 10), 34}, // 756 TypeQueue
  {IR(32297, 16), 387}, // 757 TypeRayQueryKHR
  {IR(25903, 14), 33}, // 758 TypeReserveId
  {IR(25782, 17), 26}, // 759 TypeRuntimeArray
  {IR(25755, 17), 24}, // 760 TypeSampledImage
  {IR(25743, 12), 23}, // 761 TypeSampler
  {IR(25799, 11), 27}, // 762 TypeStruct
  {IR(44025, 25), 765}, // 763 TypeStructContinuedINTEL
  {IR(44334, 22), 778}, // 764 TypeTaskSequenceINTEL
  {IR(31304, 14), 347}, // 765 TypeTensorARM
  {IR(35172, 19), 493}, // 766 TypeTensorLayoutNV
  {IR(35191, 17), 494}, // 767 TypeTensorViewNV
  {IR(31428, 22), 352}, // 768 TypeUntypedPointerKHR
  {IR(25598, 11), 20}, // 769 TypeVector
  {IR(36795, 18), 565}, // 770 TypeVmeImageINTEL
  {IR(25525, 9), 16}, // 771 TypeVoid
  {IR(36424, 13), 544}, // 772 UAddSatINTEL
  {IR(36451, 14), 546}, // 773 UAverageINTEL
  {IR(36486, 21), 548}, // 774 UAverageRoundedINTEL
  {IR(27340, 9), 103}, // 775 UConvert
  {IR(36336, 24), 539}, // 776 UCountLeadingZerosINTEL
  {IR(36360, 25), 540}, // 777 UCountTrailingZerosINTEL
  {IR(27552, 5), 123}, // 778 UDiv
  {IR(31913, 5), 374}, // 779 UDot
  {IR(31966, 11), 377}, // 780 UDotAccSat
  {IR(31977, 14), 377}, // 781 UDotAccSatKHR
  {IR(31918, 8), 374}, // 782 UDotKHR
  {IR(27912, 13), 160}, // 783 UGreaterThan
  {IR(27938, 18), 162}, // 784 UGreaterThanEqual
  {IR(27974, 10), 164}, // 785 ULessThan
  {IR(27994, 15), 166}, // 786 ULessThanEqual
  {IR(27567, 5), 126}, // 787 UMod
  {IR(36548, 15), 552}, // 788 UMul32x16INTEL
  {IR(27720, 13), 140}, // 789 UMulExtended
  {IR(36520, 13), 550}, // 790 USubSatINTEL
  {IR(25037, 6), 1}, // 791 Undef
  {IR(27817, 10), 151}, // 792 Unordered
  {IR(29002, 12), 233}, // 793 Unreachable
  {IR(31469, 22), 354}, // 794 UntypedAccessChainKHR
  {IR(31606, 22), 360}, // 795 UntypedArrayLengthKHR
  {IR(31491, 30), 355}, // 796 UntypedInBoundsAccessChainKHR
  {IR(31573, 33), 359}, // 797 UntypedInBoundsPtrAccessChainKHR
  {IR(31628, 19), 361}, // 798 UntypedPrefetchKHR
  {IR(31548, 25), 358}, // 799 UntypedPtrAccessChainKHR
  {IR(31450, 19), 353}, // 800 UntypedVariableKHR
  {IR(26348, 9), 52}, // 801 Variable
  {IR(12344, 25), 682}, // 802 VariableLengthArrayINTEL
  {IR(26705, 21), 69}, // 803 VectorExtractDynamic
  {IR(26726, 20), 70}, // 804 VectorInsertDynamic
  {IR(26746, 14), 71}, // 805 VectorShuffle
  {IR(27628, 18), 133}, // 806 VectorTimesMatrix
  {IR(27592, 18), 131}, // 807 VectorTimesScalar
  {IR(36781, 14), 564}, // 808 VmeImageINTEL
  {IR(34311, 33), 466}, // 809 WritePackedPrimitiveIndices4x8NV
  {IR(29227, 10), 250}, // 810 WritePipe
  {IR(43314, 23), 744}, // 811 WritePipeBlockingINTEL
}};

// Extended instruction descriptions, ordered by (extinst enum, opcode value).
// The fields in order are:
//   enum value
//   operands, an IndexRange into kOperandSpans
//   name, a character-counting IndexRange into kStrings
//   capabilities, an IndexRange into kCapabilitySpans
static const std::array<ExtInstDesc, 425> kExtInstByValue{{
    {0,IR(0, 0),IR(44894, 14),IR(1, 0)}, // DebugInfoNone in debuginfo
    {1,IR(52, 3),IR(44908, 21),IR(1, 0)}, // DebugCompilationUnit in debuginfo
    {2,IR(727, 3),IR(44981, 15),IR(1, 0)}, // DebugTypeBasic in debuginfo
    {3,IR(730, 3),IR(45030, 17),IR(1, 0)}, // DebugTypePointer in debuginfo
    {4,IR(733, 2),IR(45085, 19),IR(1, 0)}, // DebugTypeQualifier in debuginfo
    {5,IR(168, 2),IR(45104, 15),IR(1, 0)}, // DebugTypeArray in debuginfo
    {6,IR(261, 2),IR(45119, 16),IR(1, 0)}, // DebugTypeVector in debuginfo
    {7,IR(735, 6),IR(45135, 13),IR(1, 0)}, // DebugTypedef in debuginfo
    {8,IR(168, 2),IR(45148, 18),IR(1, 0)}, // DebugTypeFunction in debuginfo
    {9,IR(741, 9),IR(45166, 14),IR(1, 0)}, // DebugTypeEnum in debuginfo
    {10,IR(750, 9),IR(45218, 19),IR(1, 0)}, // DebugTypeComposite in debuginfo
    {11,IR(759, 10),IR(45237, 16),IR(1, 0)}, // DebugTypeMember in debuginfo
    {12,IR(769, 5),IR(45253, 21),IR(1, 0)}, // DebugTypeInheritance in debuginfo
    {13,IR(36, 2),IR(45274, 21),IR(1, 0)}, // DebugTypePtrToMember in debuginfo
    {14,IR(168, 2),IR(45295, 18),IR(1, 0)}, // DebugTypeTemplate in debuginfo
    {15,IR(774, 6),IR(45313, 27),IR(1, 0)}, // DebugTypeTemplateParameter in debuginfo
    {16,IR(780, 5),IR(45340, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in debuginfo
    {17,IR(785, 5),IR(45375, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in debuginfo
    {18,IR(759, 10),IR(45406, 20),IR(1, 0)}, // DebugGlobalVariable in debuginfo
    {19,IR(790, 8),IR(45426, 25),IR(1, 0)}, // DebugFunctionDeclaration in debuginfo
    {20,IR(798, 11),IR(45451, 14),IR(1, 0)}, // DebugFunction in debuginfo
    {21,IR(809, 5),IR(45465, 18),IR(1, 0)}, // DebugLexicalBlock in debuginfo
    {22,IR(814, 3),IR(45483, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in debuginfo
    {23,IR(817, 2),IR(45514, 11),IR(1, 0)}, // DebugScope in debuginfo
    {24,IR(0, 0),IR(45525, 13),IR(1, 0)}, // DebugNoScope in debuginfo
    {25,IR(819, 3),IR(45538, 15),IR(1, 0)}, // DebugInlinedAt in debuginfo
    {26,IR(822, 7),IR(45595, 19),IR(1, 0)}, // DebugLocalVariable in debuginfo
    {27,IR(36, 2),IR(45614, 21),IR(1, 0)}, // DebugInlinedVariable in debuginfo
    {28,IR(33, 3),IR(45635, 13),IR(1, 0)}, // DebugDeclare in debuginfo
    {29,IR(829, 3),IR(45648, 11),IR(1, 0)}, // DebugValue in debuginfo
    {30,IR(832, 2),IR(45692, 15),IR(1, 0)}, // DebugOperation in debuginfo
    {31,IR(683, 1),IR(45707, 16),IR(1, 0)}, // DebugExpression in debuginfo
    {32,IR(834, 4),IR(45723, 14),IR(1, 0)}, // DebugMacroDef in debuginfo
    {33,IR(814, 3),IR(45737, 16),IR(1, 0)}, // DebugMacroUndef in debuginfo
    {1,IR(10, 1),IR(45753, 6),IR(1, 0)}, // Round in glsl_std_450
    {2,IR(10, 1),IR(45759, 10),IR(1, 0)}, // RoundEven in glsl_std_450
    {3,IR(10, 1),IR(45769, 6),IR(1, 0)}, // Trunc in glsl_std_450
    {4,IR(10, 1),IR(45775, 5),IR(1, 0)}, // FAbs in glsl_std_450
    {5,IR(10, 1),IR(45780, 5),IR(1, 0)}, // SAbs in glsl_std_450
    {6,IR(10, 1),IR(45785, 6),IR(1, 0)}, // FSign in glsl_std_450
    {7,IR(10, 1),IR(45791, 6),IR(1, 0)}, // SSign in glsl_std_450
    {8,IR(10, 1),IR(45797, 6),IR(1, 0)}, // Floor in glsl_std_450
    {9,IR(10, 1),IR(45803, 5),IR(1, 0)}, // Ceil in glsl_std_450
    {10,IR(10, 1),IR(45808, 6),IR(1, 0)}, // Fract in glsl_std_450
    {11,IR(10, 1),IR(45814, 8),IR(1, 0)}, // Radians in glsl_std_450
    {12,IR(10, 1),IR(45822, 8),IR(1, 0)}, // Degrees in glsl_std_450
    {13,IR(10, 1),IR(45830, 4),IR(1, 0)}, // Sin in glsl_std_450
    {14,IR(10, 1),IR(45834, 4),IR(1, 0)}, // Cos in glsl_std_450
    {15,IR(10, 1),IR(45838, 4),IR(1, 0)}, // Tan in glsl_std_450
    {16,IR(10, 1),IR(45842, 5),IR(1, 0)}, // Asin in glsl_std_450
    {17,IR(10, 1),IR(45847, 5),IR(1, 0)}, // Acos in glsl_std_450
    {18,IR(10, 1),IR(45852, 5),IR(1, 0)}, // Atan in glsl_std_450
    {19,IR(10, 1),IR(45857, 5),IR(1, 0)}, // Sinh in glsl_std_450
    {20,IR(10, 1),IR(45862, 5),IR(1, 0)}, // Cosh in glsl_std_450
    {21,IR(10, 1),IR(45867, 5),IR(1, 0)}, // Tanh in glsl_std_450
    {22,IR(10, 1),IR(45872, 6),IR(1, 0)}, // Asinh in glsl_std_450
    {23,IR(10, 1),IR(45878, 6),IR(1, 0)}, // Acosh in glsl_std_450
    {24,IR(10, 1),IR(45884, 6),IR(1, 0)}, // Atanh in glsl_std_450
    {25,IR(36, 2),IR(45890, 6),IR(1, 0)}, // Atan2 in glsl_std_450
    {26,IR(36, 2),IR(45896, 4),IR(1, 0)}, // Pow in glsl_std_450
    {27,IR(10, 1),IR(45900, 4),IR(1, 0)}, // Exp in glsl_std_450
    {28,IR(10, 1),IR(45904, 4),IR(1, 0)}, // Log in glsl_std_450
    {29,IR(10, 1),IR(45908, 5),IR(1, 0)}, // Exp2 in glsl_std_450
    {30,IR(10, 1),IR(45913, 5),IR(1, 0)}, // Log2 in glsl_std_450
    {31,IR(10, 1),IR(45918, 5),IR(1, 0)}, // Sqrt in glsl_std_450
    {32,IR(10, 1),IR(45923, 12),IR(1, 0)}, // InverseSqrt in glsl_std_450
    {33,IR(10, 1),IR(45935, 12),IR(1, 0)}, // Determinant in glsl_std_450
    {34,IR(10, 1),IR(45947, 14),IR(1, 0)}, // MatrixInverse in glsl_std_450
    {35,IR(36, 2),IR(45961, 5),IR(1, 0)}, // Modf in glsl_std_450
    {36,IR(10, 1),IR(45966, 11),IR(1, 0)}, // ModfStruct in glsl_std_450
    {37,IR(36, 2),IR(45977, 5),IR(1, 0)}, // FMin in glsl_std_450
    {38,IR(36, 2),IR(45982, 5),IR(1, 0)}, // UMin in glsl_std_450
    {39,IR(36, 2),IR(45987, 5),IR(1, 0)}, // SMin in glsl_std_450
    {40,IR(36, 2),IR(45992, 5),IR(1, 0)}, // FMax in glsl_std_450
    {41,IR(36, 2),IR(45997, 5),IR(1, 0)}, // UMax in glsl_std_450
    {42,IR(36, 2),IR(46002, 5),IR(1, 0)}, // SMax in glsl_std_450
    {43,IR(33, 3),IR(46007, 7),IR(1, 0)}, // FClamp in glsl_std_450
    {44,IR(33, 3),IR(46014, 7),IR(1, 0)}, // UClamp in glsl_std_450
    {45,IR(33, 3),IR(46021, 7),IR(1, 0)}, // SClamp in glsl_std_450
    {46,IR(33, 3),IR(46028, 5),IR(1, 0)}, // FMix in glsl_std_450
    {47,IR(33, 3),IR(46033, 5),IR(1, 0)}, // IMix in glsl_std_450
    {48,IR(36, 2),IR(46038, 5),IR(1, 0)}, // Step in glsl_std_450
    {49,IR(33, 3),IR(46043, 11),IR(1, 0)}, // SmoothStep in glsl_std_450
    {50,IR(33, 3),IR(46054, 4),IR(1, 0)}, // Fma in glsl_std_450
    {51,IR(36, 2),IR(46058, 6),IR(1, 0)}, // Frexp in glsl_std_450
    {52,IR(10, 1),IR(46064, 12),IR(1, 0)}, // FrexpStruct in glsl_std_450
    {53,IR(36, 2),IR(46076, 6),IR(1, 0)}, // Ldexp in glsl_std_450
    {54,IR(10, 1),IR(46082, 13),IR(1, 0)}, // PackSnorm4x8 in glsl_std_450
    {55,IR(10, 1),IR(46095, 13),IR(1, 0)}, // PackUnorm4x8 in glsl_std_450
    {56,IR(10, 1),IR(46108, 14),IR(1, 0)}, // PackSnorm2x16 in glsl_std_450
    {57,IR(10, 1),IR(46122, 14),IR(1, 0)}, // PackUnorm2x16 in glsl_std_450
    {58,IR(10, 1),IR(46136, 13),IR(1, 0)}, // PackHalf2x16 in glsl_std_450
    {59,IR(10, 1),IR(46149, 15),IR(302, 1)}, // PackDouble2x32 in glsl_std_450
    {60,IR(10, 1),IR(46164, 16),IR(1, 0)}, // UnpackSnorm2x16 in glsl_std_450
    {61,IR(10, 1),IR(46180, 16),IR(1, 0)}, // UnpackUnorm2x16 in glsl_std_450
    {62,IR(10, 1),IR(46196, 15),IR(1, 0)}, // UnpackHalf2x16 in glsl_std_450
    {63,IR(10, 1),IR(46211, 15),IR(1, 0)}, // UnpackSnorm4x8 in glsl_std_450
    {64,IR(10, 1),IR(46226, 15),IR(1, 0)}, // UnpackUnorm4x8 in glsl_std_450
    {65,IR(10, 1),IR(46241, 17),IR(302, 1)}, // UnpackDouble2x32 in glsl_std_450
    {66,IR(10, 1),IR(46258, 7),IR(1, 0)}, // Length in glsl_std_450
    {67,IR(36, 2),IR(46265, 9),IR(1, 0)}, // Distance in glsl_std_450
    {68,IR(36, 2),IR(46274, 6),IR(1, 0)}, // Cross in glsl_std_450
    {69,IR(10, 1),IR(46280, 10),IR(1, 0)}, // Normalize in glsl_std_450
    {70,IR(33, 3),IR(46290, 12),IR(1, 0)}, // FaceForward in glsl_std_450
    {71,IR(36, 2),IR(46302, 8),IR(1, 0)}, // Reflect in glsl_std_450
    {72,IR(33, 3),IR(46310, 8),IR(1, 0)}, // Refract in glsl_std_450
    {73,IR(10, 1),IR(46318, 9),IR(1, 0)}, // FindILsb in glsl_std_450
    {74,IR(10, 1),IR(46327, 9),IR(1, 0)}, // FindSMsb in glsl_std_450
    {75,IR(10, 1),IR(46336, 9),IR(1, 0)}, // FindUMsb in glsl_std_450
    {76,IR(10, 1),IR(46345, 22),IR(303, 1)}, // InterpolateAtCentroid in glsl_std_450
    {77,IR(36, 2),IR(46367, 20),IR(303, 1)}, // InterpolateAtSample in glsl_std_450
    {78,IR(36, 2),IR(46387, 20),IR(303, 1)}, // InterpolateAtOffset in glsl_std_450
    {79,IR(36, 2),IR(46407, 5),IR(1, 0)}, // NMin in glsl_std_450
    {80,IR(36, 2),IR(46412, 5),IR(1, 0)}, // NMax in glsl_std_450
    {81,IR(33, 3),IR(46417, 7),IR(1, 0)}, // NClamp in glsl_std_450
    {1,IR(387, 5),IR(4549, 7),IR(1, 0)}, // Kernel in nonsemantic_clspvreflection
    {2,IR(838, 5),IR(46424, 13),IR(1, 0)}, // ArgumentInfo in nonsemantic_clspvreflection
    {3,IR(843, 5),IR(46437, 22),IR(1, 0)}, // ArgumentStorageBuffer in nonsemantic_clspvreflection
    {4,IR(843, 5),IR(46459, 16),IR(1, 0)}, // ArgumentUniform in nonsemantic_clspvreflection
    {5,IR(531, 7),IR(46475, 25),IR(1, 0)}, // ArgumentPodStorageBuffer in nonsemantic_clspvreflection
    {6,IR(531, 7),IR(46500, 19),IR(1, 0)}, // ArgumentPodUniform in nonsemantic_clspvreflection
    {7,IR(843, 5),IR(46519, 24),IR(1, 0)}, // ArgumentPodPushConstant in nonsemantic_clspvreflection
    {8,IR(843, 5),IR(46543, 21),IR(1, 0)}, // ArgumentSampledImage in nonsemantic_clspvreflection
    {9,IR(843, 5),IR(46564, 21),IR(1, 0)}, // ArgumentStorageImage in nonsemantic_clspvreflection
    {10,IR(843, 5),IR(46585, 16),IR(1, 0)}, // ArgumentSampler in nonsemantic_clspvreflection
    {11,IR(843, 5),IR(46601, 18),IR(1, 0)}, // ArgumentWorkgroup in nonsemantic_clspvreflection
    {12,IR(33, 3),IR(46619, 26),IR(1, 0)}, // SpecConstantWorkgroupSize in nonsemantic_clspvreflection
    {13,IR(33, 3),IR(46645, 25),IR(1, 0)}, // SpecConstantGlobalOffset in nonsemantic_clspvreflection
    {14,IR(10, 1),IR(46670, 20),IR(1, 0)}, // SpecConstantWorkDim in nonsemantic_clspvreflection
    {15,IR(36, 2),IR(46690, 25),IR(1, 0)}, // PushConstantGlobalOffset in nonsemantic_clspvreflection
    {16,IR(36, 2),IR(46715, 30),IR(1, 0)}, // PushConstantEnqueuedLocalSize in nonsemantic_clspvreflection
    {17,IR(36, 2),IR(46745, 23),IR(1, 0)}, // PushConstantGlobalSize in nonsemantic_clspvreflection
    {18,IR(36, 2),IR(46768, 25),IR(1, 0)}, // PushConstantRegionOffset in nonsemantic_clspvreflection
    {19,IR(36, 2),IR(46793, 26),IR(1, 0)}, // PushConstantNumWorkgroups in nonsemantic_clspvreflection
    {20,IR(36, 2),IR(46819, 30),IR(1, 0)}, // PushConstantRegionGroupOffset in nonsemantic_clspvreflection
    {21,IR(33, 3),IR(46849, 26),IR(1, 0)}, // ConstantDataStorageBuffer in nonsemantic_clspvreflection
    {22,IR(33, 3),IR(46875, 20),IR(1, 0)}, // ConstantDataUniform in nonsemantic_clspvreflection
    {23,IR(33, 3),IR(7974, 15),IR(1, 0)}, // LiteralSampler in nonsemantic_clspvreflection
    {24,IR(296, 4),IR(46895, 30),IR(1, 0)}, // PropertyRequiredWorkgroupSize in nonsemantic_clspvreflection
    {25,IR(10, 1),IR(46925, 28),IR(1, 0)}, // SpecConstantSubgroupMaxSize in nonsemantic_clspvreflection
    {26,IR(843, 5),IR(46953, 28),IR(1, 0)}, // ArgumentPointerPushConstant in nonsemantic_clspvreflection
    {27,IR(531, 7),IR(46981, 23),IR(1, 0)}, // ArgumentPointerUniform in nonsemantic_clspvreflection
    {28,IR(33, 3),IR(47004, 35),IR(1, 0)}, // ProgramScopeVariablesStorageBuffer in nonsemantic_clspvreflection
    {29,IR(33, 3),IR(47039, 38),IR(1, 0)}, // ProgramScopeVariablePointerRelocation in nonsemantic_clspvreflection
    {30,IR(296, 4),IR(47077, 42),IR(1, 0)}, // ImageArgumentInfoChannelOrderPushConstant in nonsemantic_clspvreflection
    {31,IR(296, 4),IR(47119, 45),IR(1, 0)}, // ImageArgumentInfoChannelDataTypePushConstant in nonsemantic_clspvreflection
    {32,IR(502, 6),IR(47164, 37),IR(1, 0)}, // ImageArgumentInfoChannelOrderUniform in nonsemantic_clspvreflection
    {33,IR(502, 6),IR(47201, 40),IR(1, 0)}, // ImageArgumentInfoChannelDataTypeUniform in nonsemantic_clspvreflection
    {34,IR(843, 5),IR(47241, 27),IR(1, 0)}, // ArgumentStorageTexelBuffer in nonsemantic_clspvreflection
    {35,IR(843, 5),IR(47268, 27),IR(1, 0)}, // ArgumentUniformTexelBuffer in nonsemantic_clspvreflection
    {36,IR(33, 3),IR(47295, 32),IR(1, 0)}, // ConstantDataPointerPushConstant in nonsemantic_clspvreflection
    {37,IR(33, 3),IR(47327, 40),IR(1, 0)}, // ProgramScopeVariablePointerPushConstant in nonsemantic_clspvreflection
    {38,IR(829, 3),IR(47367, 11),IR(1, 0)}, // PrintfInfo in nonsemantic_clspvreflection
    {39,IR(33, 3),IR(47378, 26),IR(1, 0)}, // PrintfBufferStorageBuffer in nonsemantic_clspvreflection
    {40,IR(33, 3),IR(47404, 32),IR(1, 0)}, // PrintfBufferPointerPushConstant in nonsemantic_clspvreflection
    {41,IR(296, 4),IR(47436, 34),IR(1, 0)}, // NormalizedSamplerMaskPushConstant in nonsemantic_clspvreflection
    {42,IR(36, 2),IR(47470, 22),IR(1, 0)}, // WorkgroupVariableSize in nonsemantic_clspvreflection
    {0,IR(0, 0),IR(44894, 14),IR(1, 0)}, // DebugInfoNone in nonsemantic_shader_debuginfo_100
    {1,IR(296, 4),IR(44908, 21),IR(1, 0)}, // DebugCompilationUnit in nonsemantic_shader_debuginfo_100
    {2,IR(296, 4),IR(44981, 15),IR(1, 0)}, // DebugTypeBasic in nonsemantic_shader_debuginfo_100
    {3,IR(33, 3),IR(45030, 17),IR(1, 0)}, // DebugTypePointer in nonsemantic_shader_debuginfo_100
    {4,IR(36, 2),IR(45085, 19),IR(1, 0)}, // DebugTypeQualifier in nonsemantic_shader_debuginfo_100
    {5,IR(168, 2),IR(45104, 15),IR(1, 0)}, // DebugTypeArray in nonsemantic_shader_debuginfo_100
    {6,IR(36, 2),IR(45119, 16),IR(1, 0)}, // DebugTypeVector in nonsemantic_shader_debuginfo_100
    {7,IR(502, 6),IR(45135, 13),IR(1, 0)}, // DebugTypedef in nonsemantic_shader_debuginfo_100
    {8,IR(829, 3),IR(45148, 18),IR(1, 0)}, // DebugTypeFunction in nonsemantic_shader_debuginfo_100
    {9,IR(848, 9),IR(45166, 14),IR(1, 0)}, // DebugTypeEnum in nonsemantic_shader_debuginfo_100
    {10,IR(857, 10),IR(45218, 19),IR(1, 0)}, // DebugTypeComposite in nonsemantic_shader_debuginfo_100
    {11,IR(867, 9),IR(45237, 16),IR(1, 0)}, // DebugTypeMember in nonsemantic_shader_debuginfo_100
    {12,IR(296, 4),IR(45253, 21),IR(1, 0)}, // DebugTypeInheritance in nonsemantic_shader_debuginfo_100
    {13,IR(36, 2),IR(45274, 21),IR(1, 0)}, // DebugTypePtrToMember in nonsemantic_shader_debuginfo_100
    {14,IR(168, 2),IR(45295, 18),IR(1, 0)}, // DebugTypeTemplate in nonsemantic_shader_debuginfo_100
    {15,IR(502, 6),IR(45313, 27),IR(1, 0)}, // DebugTypeTemplateParameter in nonsemantic_shader_debuginfo_100
    {16,IR(611, 5),IR(45340, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in nonsemantic_shader_debuginfo_100
    {17,IR(876, 5),IR(45375, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in nonsemantic_shader_debuginfo_100
    {18,IR(881, 10),IR(45406, 20),IR(1, 0)}, // DebugGlobalVariable in nonsemantic_shader_debuginfo_100
    {19,IR(448, 8),IR(45426, 25),IR(1, 0)}, // DebugFunctionDeclaration in nonsemantic_shader_debuginfo_100
    {20,IR(881, 10),IR(45451, 14),IR(1, 0)}, // DebugFunction in nonsemantic_shader_debuginfo_100
    {21,IR(843, 5),IR(45465, 18),IR(1, 0)}, // DebugLexicalBlock in nonsemantic_shader_debuginfo_100
    {22,IR(33, 3),IR(45483, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in nonsemantic_shader_debuginfo_100
    {23,IR(817, 2),IR(45514, 11),IR(1, 0)}, // DebugScope in nonsemantic_shader_debuginfo_100
    {24,IR(0, 0),IR(45525, 13),IR(1, 0)}, // DebugNoScope in nonsemantic_shader_debuginfo_100
    {25,IR(891, 3),IR(45538, 15),IR(1, 0)}, // DebugInlinedAt in nonsemantic_shader_debuginfo_100
    {26,IR(894, 8),IR(45595, 19),IR(1, 0)}, // DebugLocalVariable in nonsemantic_shader_debuginfo_100
    {27,IR(36, 2),IR(45614, 21),IR(1, 0)}, // DebugInlinedVariable in nonsemantic_shader_debuginfo_100
    {28,IR(902, 4),IR(45635, 13),IR(1, 0)}, // DebugDeclare in nonsemantic_shader_debuginfo_100
    {29,IR(902, 4),IR(45648, 11),IR(1, 0)}, // DebugValue in nonsemantic_shader_debuginfo_100
    {30,IR(168, 2),IR(45692, 15),IR(1, 0)}, // DebugOperation in nonsemantic_shader_debuginfo_100
    {31,IR(683, 1),IR(45707, 16),IR(1, 0)}, // DebugExpression in nonsemantic_shader_debuginfo_100
    {32,IR(554, 4),IR(45723, 14),IR(1, 0)}, // DebugMacroDef in nonsemantic_shader_debuginfo_100
    {33,IR(33, 3),IR(45737, 16),IR(1, 0)}, // DebugMacroUndef in nonsemantic_shader_debuginfo_100
    {34,IR(483, 7),IR(47492, 20),IR(1, 0)}, // DebugImportedEntity in nonsemantic_shader_debuginfo_100
    {35,IR(817, 2),IR(47512, 12),IR(1, 0)}, // DebugSource in nonsemantic_shader_debuginfo_100
    {101,IR(36, 2),IR(47524, 24),IR(1, 0)}, // DebugFunctionDefinition in nonsemantic_shader_debuginfo_100
    {102,IR(10, 1),IR(47548, 21),IR(1, 0)}, // DebugSourceContinued in nonsemantic_shader_debuginfo_100
    {103,IR(611, 5),IR(47569, 10),IR(1, 0)}, // DebugLine in nonsemantic_shader_debuginfo_100
    {104,IR(0, 0),IR(47579, 12),IR(1, 0)}, // DebugNoLine in nonsemantic_shader_debuginfo_100
    {105,IR(36, 2),IR(47591, 21),IR(1, 0)}, // DebugBuildIdentifier in nonsemantic_shader_debuginfo_100
    {106,IR(10, 1),IR(47612, 17),IR(1, 0)}, // DebugStoragePath in nonsemantic_shader_debuginfo_100
    {107,IR(296, 4),IR(47629, 16),IR(1, 0)}, // DebugEntryPoint in nonsemantic_shader_debuginfo_100
    {108,IR(33, 3),IR(47645, 16),IR(1, 0)}, // DebugTypeMatrix in nonsemantic_shader_debuginfo_100
    {1,IR(701, 9),IR(47661, 14),IR(1, 0)}, // Configuration in nonsemantic_vkspreflection
    {2,IR(10, 1),IR(47675, 13),IR(1, 0)}, // StartCounter in nonsemantic_vkspreflection
    {3,IR(10, 1),IR(47688, 12),IR(1, 0)}, // StopCounter in nonsemantic_vkspreflection
    {4,IR(296, 4),IR(47700, 14),IR(1, 0)}, // PushConstants in nonsemantic_vkspreflection
    {5,IR(33, 3),IR(47714, 23),IR(1, 0)}, // SpecializationMapEntry in nonsemantic_vkspreflection
    {6,IR(906, 15),IR(47737, 20),IR(1, 0)}, // DescriptorSetBuffer in nonsemantic_vkspreflection
    {7,IR(921, 33),IR(47757, 19),IR(1, 0)}, // DescriptorSetImage in nonsemantic_vkspreflection
    {8,IR(954, 19),IR(47776, 21),IR(1, 0)}, // DescriptorSetSampler in nonsemantic_vkspreflection
    {0,IR(0, 0),IR(44894, 14),IR(1, 0)}, // DebugInfoNone in opencl_debuginfo_100
    {1,IR(973, 4),IR(44908, 21),IR(1, 0)}, // DebugCompilationUnit in opencl_debuginfo_100
    {2,IR(977, 3),IR(44981, 15),IR(1, 0)}, // DebugTypeBasic in opencl_debuginfo_100
    {3,IR(980, 3),IR(45030, 17),IR(1, 0)}, // DebugTypePointer in opencl_debuginfo_100
    {4,IR(983, 2),IR(45085, 19),IR(1, 0)}, // DebugTypeQualifier in opencl_debuginfo_100
    {5,IR(168, 2),IR(45104, 15),IR(1, 0)}, // DebugTypeArray in opencl_debuginfo_100
    {6,IR(261, 2),IR(45119, 16),IR(1, 0)}, // DebugTypeVector in opencl_debuginfo_100
    {7,IR(735, 6),IR(45135, 13),IR(1, 0)}, // DebugTypedef in opencl_debuginfo_100
    {8,IR(985, 3),IR(45148, 18),IR(1, 0)}, // DebugTypeFunction in opencl_debuginfo_100
    {9,IR(988, 9),IR(45166, 14),IR(1, 0)}, // DebugTypeEnum in opencl_debuginfo_100
    {10,IR(997, 10),IR(45218, 19),IR(1, 0)}, // DebugTypeComposite in opencl_debuginfo_100
    {11,IR(1007, 10),IR(45237, 16),IR(1, 0)}, // DebugTypeMember in opencl_debuginfo_100
    {12,IR(1017, 5),IR(45253, 21),IR(1, 0)}, // DebugTypeInheritance in opencl_debuginfo_100
    {13,IR(36, 2),IR(45274, 21),IR(1, 0)}, // DebugTypePtrToMember in opencl_debuginfo_100
    {14,IR(168, 2),IR(45295, 18),IR(1, 0)}, // DebugTypeTemplate in opencl_debuginfo_100
    {15,IR(774, 6),IR(45313, 27),IR(1, 0)}, // DebugTypeTemplateParameter in opencl_debuginfo_100
    {16,IR(780, 5),IR(45340, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in opencl_debuginfo_100
    {17,IR(785, 5),IR(45375, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in opencl_debuginfo_100
    {18,IR(1007, 10),IR(45406, 20),IR(1, 0)}, // DebugGlobalVariable in opencl_debuginfo_100
    {19,IR(1022, 8),IR(45426, 25),IR(1, 0)}, // DebugFunctionDeclaration in opencl_debuginfo_100
    {20,IR(1030, 11),IR(45451, 14),IR(1, 0)}, // DebugFunction in opencl_debuginfo_100
    {21,IR(809, 5),IR(45465, 18),IR(1, 0)}, // DebugLexicalBlock in opencl_debuginfo_100
    {22,IR(814, 3),IR(45483, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in opencl_debuginfo_100
    {23,IR(817, 2),IR(45514, 11),IR(1, 0)}, // DebugScope in opencl_debuginfo_100
    {24,IR(0, 0),IR(45525, 13),IR(1, 0)}, // DebugNoScope in opencl_debuginfo_100
    {25,IR(819, 3),IR(45538, 15),IR(1, 0)}, // DebugInlinedAt in opencl_debuginfo_100
    {26,IR(1041, 8),IR(45595, 19),IR(1, 0)}, // DebugLocalVariable in opencl_debuginfo_100
    {27,IR(36, 2),IR(45614, 21),IR(1, 0)}, // DebugInlinedVariable in opencl_debuginfo_100
    {28,IR(33, 3),IR(45635, 13),IR(1, 0)}, // DebugDeclare in opencl_debuginfo_100
    {29,IR(902, 4),IR(45648, 11),IR(1, 0)}, // DebugValue in opencl_debuginfo_100
    {30,IR(1049, 2),IR(45692, 15),IR(1, 0)}, // DebugOperation in opencl_debuginfo_100
    {31,IR(683, 1),IR(45707, 16),IR(1, 0)}, // DebugExpression in opencl_debuginfo_100
    {32,IR(834, 4),IR(45723, 14),IR(1, 0)}, // DebugMacroDef in opencl_debuginfo_100
    {33,IR(814, 3),IR(45737, 16),IR(1, 0)}, // DebugMacroUndef in opencl_debuginfo_100
    {34,IR(1051, 7),IR(47492, 20),IR(1, 0)}, // DebugImportedEntity in opencl_debuginfo_100
    {35,IR(817, 2),IR(47512, 12),IR(1, 0)}, // DebugSource in opencl_debuginfo_100
    {36,IR(1058, 8),IR(48097, 17),IR(1, 0)}, // DebugModuleINTEL in opencl_debuginfo_100
    {0,IR(10, 1),IR(48114, 5),IR(1, 0)}, // acos in opencl_std_100
    {1,IR(10, 1),IR(48119, 6),IR(1, 0)}, // acosh in opencl_std_100
    {2,IR(10, 1),IR(48125, 7),IR(1, 0)}, // acospi in opencl_std_100
    {3,IR(10, 1),IR(48132, 5),IR(1, 0)}, // asin in opencl_std_100
    {4,IR(10, 1),IR(48137, 6),IR(1, 0)}, // asinh in opencl_std_100
    {5,IR(10, 1),IR(48143, 7),IR(1, 0)}, // asinpi in opencl_std_100
    {6,IR(10, 1),IR(48150, 5),IR(1, 0)}, // atan in opencl_std_100
    {7,IR(36, 2),IR(48155, 6),IR(1, 0)}, // atan2 in opencl_std_100
    {8,IR(10, 1),IR(48161, 6),IR(1, 0)}, // atanh in opencl_std_100
    {9,IR(10, 1),IR(48167, 7),IR(1, 0)}, // atanpi in opencl_std_100
    {10,IR(36, 2),IR(48174, 8),IR(1, 0)}, // atan2pi in opencl_std_100
    {11,IR(10, 1),IR(48182, 5),IR(1, 0)}, // cbrt in opencl_std_100
    {12,IR(10, 1),IR(48187, 5),IR(1, 0)}, // ceil in opencl_std_100
    {13,IR(36, 2),IR(48192, 9),IR(1, 0)}, // copysign in opencl_std_100
    {14,IR(10, 1),IR(48201, 4),IR(1, 0)}, // cos in opencl_std_100
    {15,IR(10, 1),IR(48205, 5),IR(1, 0)}, // cosh in opencl_std_100
    {16,IR(10, 1),IR(48210, 6),IR(1, 0)}, // cospi in opencl_std_100
    {17,IR(10, 1),IR(48216, 5),IR(1, 0)}, // erfc in opencl_std_100
    {18,IR(10, 1),IR(48221, 4),IR(1, 0)}, // erf in opencl_std_100
    {19,IR(10, 1),IR(48225, 4),IR(1, 0)}, // exp in opencl_std_100
    {20,IR(10, 1),IR(48229, 5),IR(1, 0)}, // exp2 in opencl_std_100
    {21,IR(10, 1),IR(48234, 6),IR(1, 0)}, // exp10 in opencl_std_100
    {22,IR(10, 1),IR(48240, 6),IR(1, 0)}, // expm1 in opencl_std_100
    {23,IR(10, 1),IR(48246, 5),IR(1, 0)}, // fabs in opencl_std_100
    {24,IR(36, 2),IR(48251, 5),IR(1, 0)}, // fdim in opencl_std_100
    {25,IR(10, 1),IR(48256, 6),IR(1, 0)}, // floor in opencl_std_100
    {26,IR(33, 3),IR(48262, 4),IR(1, 0)}, // fma in opencl_std_100
    {27,IR(36, 2),IR(48266, 5),IR(1, 0)}, // fmax in opencl_std_100
    {28,IR(36, 2),IR(48271, 5),IR(1, 0)}, // fmin in opencl_std_100
    {29,IR(36, 2),IR(48276, 5),IR(1, 0)}, // fmod in opencl_std_100
    {30,IR(36, 2),IR(48281, 6),IR(1, 0)}, // fract in opencl_std_100
    {31,IR(36, 2),IR(48287, 6),IR(1, 0)}, // frexp in opencl_std_100
    {32,IR(36, 2),IR(48293, 6),IR(1, 0)}, // hypot in opencl_std_100
    {33,IR(10, 1),IR(48299, 6),IR(1, 0)}, // ilogb in opencl_std_100
    {34,IR(36, 2),IR(48305, 6),IR(1, 0)}, // ldexp in opencl_std_100
    {35,IR(10, 1),IR(48311, 7),IR(1, 0)}, // lgamma in opencl_std_100
    {36,IR(36, 2),IR(48318, 9),IR(1, 0)}, // lgamma_r in opencl_std_100
    {37,IR(10, 1),IR(48327, 4),IR(1, 0)}, // log in opencl_std_100
    {38,IR(10, 1),IR(48331, 5),IR(1, 0)}, // log2 in opencl_std_100
    {39,IR(10, 1),IR(48336, 6),IR(1, 0)}, // log10 in opencl_std_100
    {40,IR(10, 1),IR(48342, 6),IR(1, 0)}, // log1p in opencl_std_100
    {41,IR(10, 1),IR(48348, 5),IR(1, 0)}, // logb in opencl_std_100
    {42,IR(33, 3),IR(48353, 4),IR(1, 0)}, // mad in opencl_std_100
    {43,IR(36, 2),IR(48357, 7),IR(1, 0)}, // maxmag in opencl_std_100
    {44,IR(36, 2),IR(48364, 7),IR(1, 0)}, // minmag in opencl_std_100
    {45,IR(36, 2),IR(48371, 5),IR(1, 0)}, // modf in opencl_std_100
    {46,IR(10, 1),IR(48376, 4),IR(1, 0)}, // nan in opencl_std_100
    {47,IR(36, 2),IR(48380, 10),IR(1, 0)}, // nextafter in opencl_std_100
    {48,IR(36, 2),IR(48390, 4),IR(1, 0)}, // pow in opencl_std_100
    {49,IR(36, 2),IR(48394, 5),IR(1, 0)}, // pown in opencl_std_100
    {50,IR(36, 2),IR(48399, 5),IR(1, 0)}, // powr in opencl_std_100
    {51,IR(36, 2),IR(48404, 10),IR(1, 0)}, // remainder in opencl_std_100
    {52,IR(33, 3),IR(48414, 7),IR(1, 0)}, // remquo in opencl_std_100
    {53,IR(10, 1),IR(48421, 5),IR(1, 0)}, // rint in opencl_std_100
    {54,IR(36, 2),IR(48426, 6),IR(1, 0)}, // rootn in opencl_std_100
    {55,IR(10, 1),IR(48432, 6),IR(1, 0)}, // round in opencl_std_100
    {56,IR(10, 1),IR(48438, 6),IR(1, 0)}, // rsqrt in opencl_std_100
    {57,IR(10, 1),IR(48444, 4),IR(1, 0)}, // sin in opencl_std_100
    {58,IR(36, 2),IR(48448, 7),IR(1, 0)}, // sincos in opencl_std_100
    {59,IR(10, 1),IR(48455, 5),IR(1, 0)}, // sinh in opencl_std_100
    {60,IR(10, 1),IR(48460, 6),IR(1, 0)}, // sinpi in opencl_std_100
    {61,IR(10, 1),IR(48466, 5),IR(1, 0)}, // sqrt in opencl_std_100
    {62,IR(10, 1),IR(48471, 4),IR(1, 0)}, // tan in opencl_std_100
    {63,IR(10, 1),IR(48475, 5),IR(1, 0)}, // tanh in opencl_std_100
    {64,IR(10, 1),IR(48480, 6),IR(1, 0)}, // tanpi in opencl_std_100
    {65,IR(10, 1),IR(48486, 7),IR(1, 0)}, // tgamma in opencl_std_100
    {66,IR(10, 1),IR(48493, 6),IR(1, 0)}, // trunc in opencl_std_100
    {67,IR(10, 1),IR(48499, 9),IR(1, 0)}, // half_cos in opencl_std_100
    {68,IR(36, 2),IR(48508, 12),IR(1, 0)}, // half_divide in opencl_std_100
    {69,IR(10, 1),IR(48520, 9),IR(1, 0)}, // half_exp in opencl_std_100
    {70,IR(10, 1),IR(48529, 10),IR(1, 0)}, // half_exp2 in opencl_std_100
    {71,IR(10, 1),IR(48539, 11),IR(1, 0)}, // half_exp10 in opencl_std_100
    {72,IR(10, 1),IR(48550, 9),IR(1, 0)}, // half_log in opencl_std_100
    {73,IR(10, 1),IR(48559, 10),IR(1, 0)}, // half_log2 in opencl_std_100
    {74,IR(10, 1),IR(48569, 11),IR(1, 0)}, // half_log10 in opencl_std_100
    {75,IR(36, 2),IR(48580, 10),IR(1, 0)}, // half_powr in opencl_std_100
    {76,IR(10, 1),IR(48590, 11),IR(1, 0)}, // half_recip in opencl_std_100
    {77,IR(10, 1),IR(48601, 11),IR(1, 0)}, // half_rsqrt in opencl_std_100
    {78,IR(10, 1),IR(48612, 9),IR(1, 0)}, // half_sin in opencl_std_100
    {79,IR(10, 1),IR(48621, 10),IR(1, 0)}, // half_sqrt in opencl_std_100
    {80,IR(10, 1),IR(48631, 9),IR(1, 0)}, // half_tan in opencl_std_100
    {81,IR(10, 1),IR(48640, 11),IR(1, 0)}, // native_cos in opencl_std_100
    {82,IR(36, 2),IR(48651, 14),IR(1, 0)}, // native_divide in opencl_std_100
    {83,IR(10, 1),IR(48665, 11),IR(1, 0)}, // native_exp in opencl_std_100
    {84,IR(10, 1),IR(48676, 12),IR(1, 0)}, // native_exp2 in opencl_std_100
    {85,IR(10, 1),IR(48688, 13),IR(1, 0)}, // native_exp10 in opencl_std_100
    {86,IR(10, 1),IR(48701, 11),IR(1, 0)}, // native_log in opencl_std_100
    {87,IR(10, 1),IR(48712, 12),IR(1, 0)}, // native_log2 in opencl_std_100
    {88,IR(10, 1),IR(48724, 13),IR(1, 0)}, // native_log10 in opencl_std_100
    {89,IR(36, 2),IR(48737, 12),IR(1, 0)}, // native_powr in opencl_std_100
    {90,IR(10, 1),IR(48749, 13),IR(1, 0)}, // native_recip in opencl_std_100
    {91,IR(10, 1),IR(48762, 13),IR(1, 0)}, // native_rsqrt in opencl_std_100
    {92,IR(10, 1),IR(48775, 11),IR(1, 0)}, // native_sin in opencl_std_100
    {93,IR(10, 1),IR(48786, 12),IR(1, 0)}, // native_sqrt in opencl_std_100
    {94,IR(10, 1),IR(48798, 11),IR(1, 0)}, // native_tan in opencl_std_100
    {95,IR(33, 3),IR(48809, 7),IR(1, 0)}, // fclamp in opencl_std_100
    {96,IR(10, 1),IR(48816, 8),IR(1, 0)}, // degrees in opencl_std_100
    {97,IR(36, 2),IR(48824, 12),IR(1, 0)}, // fmax_common in opencl_std_100
    {98,IR(36, 2),IR(48836, 12),IR(1, 0)}, // fmin_common in opencl_std_100
    {99,IR(33, 3),IR(48848, 4),IR(1, 0)}, // mix in opencl_std_100
    {100,IR(10, 1),IR(48852, 8),IR(1, 0)}, // radians in opencl_std_100
    {101,IR(36, 2),IR(48860, 5),IR(1, 0)}, // step in opencl_std_100
    {102,IR(33, 3),IR(48865, 11),IR(1, 0)}, // smoothstep in opencl_std_100
    {103,IR(10, 1),IR(48876, 5),IR(1, 0)}, // sign in opencl_std_100
    {104,IR(36, 2),IR(48881, 6),IR(1, 0)}, // cross in opencl_std_100
    {105,IR(36, 2),IR(48887, 9),IR(1, 0)}, // distance in opencl_std_100
    {106,IR(10, 1),IR(48896, 7),IR(1, 0)}, // length in opencl_std_100
    {107,IR(10, 1),IR(48903, 10),IR(1, 0)}, // normalize in opencl_std_100
    {108,IR(36, 2),IR(48913, 14),IR(1, 0)}, // fast_distance in opencl_std_100
    {109,IR(10, 1),IR(48927, 12),IR(1, 0)}, // fast_length in opencl_std_100
    {110,IR(10, 1),IR(48939, 15),IR(1, 0)}, // fast_normalize in opencl_std_100
    {141,IR(10, 1),IR(48954, 6),IR(1, 0)}, // s_abs in opencl_std_100
    {142,IR(36, 2),IR(48960, 11),IR(1, 0)}, // s_abs_diff in opencl_std_100
    {143,IR(36, 2),IR(48971, 10),IR(1, 0)}, // s_add_sat in opencl_std_100
    {144,IR(36, 2),IR(48981, 10),IR(1, 0)}, // u_add_sat in opencl_std_100
    {145,IR(36, 2),IR(48991, 7),IR(1, 0)}, // s_hadd in opencl_std_100
    {146,IR(36, 2),IR(48998, 7),IR(1, 0)}, // u_hadd in opencl_std_100
    {147,IR(36, 2),IR(49005, 8),IR(1, 0)}, // s_rhadd in opencl_std_100
    {148,IR(36, 2),IR(49013, 8),IR(1, 0)}, // u_rhadd in opencl_std_100
    {149,IR(33, 3),IR(49021, 8),IR(1, 0)}, // s_clamp in opencl_std_100
    {150,IR(33, 3),IR(49029, 8),IR(1, 0)}, // u_clamp in opencl_std_100
    {151,IR(10, 1),IR(49037, 4),IR(1, 0)}, // clz in opencl_std_100
    {152,IR(10, 1),IR(49041, 4),IR(1, 0)}, // ctz in opencl_std_100
    {153,IR(33, 3),IR(49045, 9),IR(1, 0)}, // s_mad_hi in opencl_std_100
    {154,IR(33, 3),IR(49054, 10),IR(1, 0)}, // u_mad_sat in opencl_std_100
    {155,IR(33, 3),IR(49064, 10),IR(1, 0)}, // s_mad_sat in opencl_std_100
    {156,IR(36, 2),IR(49074, 6),IR(1, 0)}, // s_max in opencl_std_100
    {157,IR(36, 2),IR(49080, 6),IR(1, 0)}, // u_max in opencl_std_100
    {158,IR(36, 2),IR(49086, 6),IR(1, 0)}, // s_min in opencl_std_100
    {159,IR(36, 2),IR(49092, 6),IR(1, 0)}, // u_min in opencl_std_100
    {160,IR(36, 2),IR(49098, 9),IR(1, 0)}, // s_mul_hi in opencl_std_100
    {161,IR(36, 2),IR(49107, 7),IR(1, 0)}, // rotate in opencl_std_100
    {162,IR(36, 2),IR(49114, 10),IR(1, 0)}, // s_sub_sat in opencl_std_100
    {163,IR(36, 2),IR(49124, 10),IR(1, 0)}, // u_sub_sat in opencl_std_100
    {164,IR(36, 2),IR(49134, 11),IR(1, 0)}, // u_upsample in opencl_std_100
    {165,IR(36, 2),IR(49145, 11),IR(1, 0)}, // s_upsample in opencl_std_100
    {166,IR(10, 1),IR(49156, 9),IR(1, 0)}, // popcount in opencl_std_100
    {167,IR(33, 3),IR(49165, 8),IR(1, 0)}, // s_mad24 in opencl_std_100
    {168,IR(33, 3),IR(49173, 8),IR(1, 0)}, // u_mad24 in opencl_std_100
    {169,IR(36, 2),IR(49181, 8),IR(1, 0)}, // s_mul24 in opencl_std_100
    {170,IR(36, 2),IR(49189, 8),IR(1, 0)}, // u_mul24 in opencl_std_100
    {171,IR(1066, 3),IR(49197, 7),IR(1, 0)}, // vloadn in opencl_std_100
    {172,IR(33, 3),IR(49204, 8),IR(1, 0)}, // vstoren in opencl_std_100
    {173,IR(36, 2),IR(49212, 11),IR(1, 0)}, // vload_half in opencl_std_100
    {174,IR(1066, 3),IR(49223, 12),IR(1, 0)}, // vload_halfn in opencl_std_100
    {175,IR(33, 3),IR(49235, 12),IR(1, 0)}, // vstore_half in opencl_std_100
    {176,IR(1069, 4),IR(49247, 14),IR(1, 0)}, // vstore_half_r in opencl_std_100
    {177,IR(33, 3),IR(49261, 13),IR(1, 0)}, // vstore_halfn in opencl_std_100
    {178,IR(1069, 4),IR(49274, 15),IR(1, 0)}, // vstore_halfn_r in opencl_std_100
    {179,IR(1066, 3),IR(49289, 13),IR(1, 0)}, // vloada_halfn in opencl_std_100
    {180,IR(33, 3),IR(49302, 14),IR(1, 0)}, // vstorea_halfn in opencl_std_100
    {181,IR(1069, 4),IR(49316, 16),IR(1, 0)}, // vstorea_halfn_r in opencl_std_100
    {182,IR(36, 2),IR(49332, 8),IR(1, 0)}, // shuffle in opencl_std_100
    {183,IR(33, 3),IR(49340, 9),IR(1, 0)}, // shuffle2 in opencl_std_100
    {184,IR(168, 2),IR(49349, 7),IR(1, 0)}, // printf in opencl_std_100
    {185,IR(36, 2),IR(49356, 9),IR(1, 0)}, // prefetch in opencl_std_100
    {186,IR(33, 3),IR(49365, 10),IR(1, 0)}, // bitselect in opencl_std_100
    {187,IR(33, 3),IR(49375, 7),IR(1, 0)}, // select in opencl_std_100
    {201,IR(10, 1),IR(49382, 6),IR(1, 0)}, // u_abs in opencl_std_100
    {202,IR(36, 2),IR(49388, 11),IR(1, 0)}, // u_abs_diff in opencl_std_100
    {203,IR(36, 2),IR(49399, 9),IR(1, 0)}, // u_mul_hi in opencl_std_100
    {204,IR(33, 3),IR(49408, 9),IR(1, 0)}, // u_mad_hi in opencl_std_100
    {1,IR(10, 1),IR(49417, 17),IR(1, 0)}, // CubeFaceIndexAMD in spv_amd_gcn_shader
    {2,IR(10, 1),IR(49434, 17),IR(1, 0)}, // CubeFaceCoordAMD in spv_amd_gcn_shader
    {3,IR(0, 0),IR(49451, 8),IR(1, 0)}, // TimeAMD in spv_amd_gcn_shader
    {1,IR(36, 2),IR(49459, 22),IR(1, 0)}, // SwizzleInvocationsAMD in spv_amd_shader_ballot
    {2,IR(36, 2),IR(49481, 28),IR(1, 0)}, // SwizzleInvocationsMaskedAMD in spv_amd_shader_ballot
    {3,IR(33, 3),IR(49509, 19),IR(1, 0)}, // WriteInvocationAMD in spv_amd_shader_ballot
    {4,IR(10, 1),IR(49528, 9),IR(1, 0)}, // MbcntAMD in spv_amd_shader_ballot
    {1,IR(36, 2),IR(49537, 23),IR(1, 0)}, // InterpolateAtVertexAMD in spv_amd_shader_explicit_vertex_parameter
    {1,IR(33, 3),IR(49560, 9),IR(1, 0)}, // FMin3AMD in spv_amd_shader_trinary_minmax
    {2,IR(33, 3),IR(49569, 9),IR(1, 0)}, // UMin3AMD in spv_amd_shader_trinary_minmax
    {3,IR(33, 3),IR(49578, 9),IR(1, 0)}, // SMin3AMD in spv_amd_shader_trinary_minmax
    {4,IR(33, 3),IR(49587, 9),IR(1, 0)}, // FMax3AMD in spv_amd_shader_trinary_minmax
    {5,IR(33, 3),IR(49596, 9),IR(1, 0)}, // UMax3AMD in spv_amd_shader_trinary_minmax
    {6,IR(33, 3),IR(49605, 9),IR(1, 0)}, // SMax3AMD in spv_amd_shader_trinary_minmax
    {7,IR(33, 3),IR(49614, 9),IR(1, 0)}, // FMid3AMD in spv_amd_shader_trinary_minmax
    {8,IR(33, 3),IR(49623, 9),IR(1, 0)}, // UMid3AMD in spv_amd_shader_trinary_minmax
    {9,IR(33, 3),IR(49632, 9),IR(1, 0)}, // SMid3AMD in spv_amd_shader_trinary_minmax
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
    {IR(44908, 21), 1}, // DebugCompilationUnit in debuginfo
    {IR(45635, 13), 28}, // DebugDeclare in debuginfo
    {IR(45707, 16), 31}, // DebugExpression in debuginfo
    {IR(45451, 14), 20}, // DebugFunction in debuginfo
    {IR(45426, 25), 19}, // DebugFunctionDeclaration in debuginfo
    {IR(45406, 20), 18}, // DebugGlobalVariable in debuginfo
    {IR(44894, 14), 0}, // DebugInfoNone in debuginfo
    {IR(45538, 15), 25}, // DebugInlinedAt in debuginfo
    {IR(45614, 21), 27}, // DebugInlinedVariable in debuginfo
    {IR(45465, 18), 21}, // DebugLexicalBlock in debuginfo
    {IR(45483, 31), 22}, // DebugLexicalBlockDiscriminator in debuginfo
    {IR(45595, 19), 26}, // DebugLocalVariable in debuginfo
    {IR(45723, 14), 32}, // DebugMacroDef in debuginfo
    {IR(45737, 16), 33}, // DebugMacroUndef in debuginfo
    {IR(45525, 13), 24}, // DebugNoScope in debuginfo
    {IR(45692, 15), 30}, // DebugOperation in debuginfo
    {IR(45514, 11), 23}, // DebugScope in debuginfo
    {IR(45104, 15), 5}, // DebugTypeArray in debuginfo
    {IR(44981, 15), 2}, // DebugTypeBasic in debuginfo
    {IR(45218, 19), 10}, // DebugTypeComposite in debuginfo
    {IR(45166, 14), 9}, // DebugTypeEnum in debuginfo
    {IR(45148, 18), 8}, // DebugTypeFunction in debuginfo
    {IR(45253, 21), 12}, // DebugTypeInheritance in debuginfo
    {IR(45237, 16), 11}, // DebugTypeMember in debuginfo
    {IR(45030, 17), 3}, // DebugTypePointer in debuginfo
    {IR(45274, 21), 13}, // DebugTypePtrToMember in debuginfo
    {IR(45085, 19), 4}, // DebugTypeQualifier in debuginfo
    {IR(45295, 18), 14}, // DebugTypeTemplate in debuginfo
    {IR(45313, 27), 15}, // DebugTypeTemplateParameter in debuginfo
    {IR(45375, 31), 17}, // DebugTypeTemplateParameterPack in debuginfo
    {IR(45340, 35), 16}, // DebugTypeTemplateTemplateParameter in debuginfo
    {IR(45119, 16), 6}, // DebugTypeVector in debuginfo
    {IR(45135, 13), 7}, // DebugTypedef in debuginfo
    {IR(45648, 11), 29}, // DebugValue in debuginfo
    {IR(45847, 5), 50}, // Acos in glsl_std_450
    {IR(45878, 6), 56}, // Acosh in glsl_std_450
    {IR(45842, 5), 49}, // Asin in glsl_std_450
    {IR(45872, 6), 55}, // Asinh in glsl_std_450
    {IR(45852, 5), 51}, // Atan in glsl_std_450
    {IR(45890, 6), 58}, // Atan2 in glsl_std_450
    {IR(45884, 6), 57}, // Atanh in glsl_std_450
    {IR(45803, 5), 42}, // Ceil in glsl_std_450
    {IR(45834, 4), 47}, // Cos in glsl_std_450
    {IR(45862, 5), 53}, // Cosh in glsl_std_450
    {IR(46274, 6), 101}, // Cross in glsl_std_450
    {IR(45822, 8), 45}, // Degrees in glsl_std_450
    {IR(45935, 12), 66}, // Determinant in glsl_std_450
    {IR(46265, 9), 100}, // Distance in glsl_std_450
    {IR(45900, 4), 60}, // Exp in glsl_std_450
    {IR(45908, 5), 62}, // Exp2 in glsl_std_450
    {IR(45775, 5), 37}, // FAbs in glsl_std_450
    {IR(46007, 7), 76}, // FClamp in glsl_std_450
    {IR(45992, 5), 73}, // FMax in glsl_std_450
    {IR(45977, 5), 70}, // FMin in glsl_std_450
    {IR(46028, 5), 79}, // FMix in glsl_std_450
    {IR(45785, 6), 39}, // FSign in glsl_std_450
    {IR(46290, 12), 103}, // FaceForward in glsl_std_450
    {IR(46318, 9), 106}, // FindILsb in glsl_std_450
    {IR(46327, 9), 107}, // FindSMsb in glsl_std_450
    {IR(46336, 9), 108}, // FindUMsb in glsl_std_450
    {IR(45797, 6), 41}, // Floor in glsl_std_450
    {IR(46054, 4), 83}, // Fma in glsl_std_450
    {IR(45808, 6), 43}, // Fract in glsl_std_450
    {IR(46058, 6), 84}, // Frexp in glsl_std_450
    {IR(46064, 12), 85}, // FrexpStruct in glsl_std_450
    {IR(46033, 5), 80}, // IMix in glsl_std_450
    {IR(46345, 22), 109}, // InterpolateAtCentroid in glsl_std_450
    {IR(46387, 20), 111}, // InterpolateAtOffset in glsl_std_450
    {IR(46367, 20), 110}, // InterpolateAtSample in glsl_std_450
    {IR(45923, 12), 65}, // InverseSqrt in glsl_std_450
    {IR(46076, 6), 86}, // Ldexp in glsl_std_450
    {IR(46258, 7), 99}, // Length in glsl_std_450
    {IR(45904, 4), 61}, // Log in glsl_std_450
    {IR(45913, 5), 63}, // Log2 in glsl_std_450
    {IR(45947, 14), 67}, // MatrixInverse in glsl_std_450
    {IR(45961, 5), 68}, // Modf in glsl_std_450
    {IR(45966, 11), 69}, // ModfStruct in glsl_std_450
    {IR(46417, 7), 114}, // NClamp in glsl_std_450
    {IR(46412, 5), 113}, // NMax in glsl_std_450
    {IR(46407, 5), 112}, // NMin in glsl_std_450
    {IR(46280, 10), 102}, // Normalize in glsl_std_450
    {IR(46149, 15), 92}, // PackDouble2x32 in glsl_std_450
    {IR(46136, 13), 91}, // PackHalf2x16 in glsl_std_450
    {IR(46108, 14), 89}, // PackSnorm2x16 in glsl_std_450
    {IR(46082, 13), 87}, // PackSnorm4x8 in glsl_std_450
    {IR(46122, 14), 90}, // PackUnorm2x16 in glsl_std_450
    {IR(46095, 13), 88}, // PackUnorm4x8 in glsl_std_450
    {IR(45896, 4), 59}, // Pow in glsl_std_450
    {IR(45814, 8), 44}, // Radians in glsl_std_450
    {IR(46302, 8), 104}, // Reflect in glsl_std_450
    {IR(46310, 8), 105}, // Refract in glsl_std_450
    {IR(45753, 6), 34}, // Round in glsl_std_450
    {IR(45759, 10), 35}, // RoundEven in glsl_std_450
    {IR(45780, 5), 38}, // SAbs in glsl_std_450
    {IR(46021, 7), 78}, // SClamp in glsl_std_450
    {IR(46002, 5), 75}, // SMax in glsl_std_450
    {IR(45987, 5), 72}, // SMin in glsl_std_450
    {IR(45791, 6), 40}, // SSign in glsl_std_450
    {IR(45830, 4), 46}, // Sin in glsl_std_450
    {IR(45857, 5), 52}, // Sinh in glsl_std_450
    {IR(46043, 11), 82}, // SmoothStep in glsl_std_450
    {IR(45918, 5), 64}, // Sqrt in glsl_std_450
    {IR(46038, 5), 81}, // Step in glsl_std_450
    {IR(45838, 4), 48}, // Tan in glsl_std_450
    {IR(45867, 5), 54}, // Tanh in glsl_std_450
    {IR(45769, 6), 36}, // Trunc in glsl_std_450
    {IR(46014, 7), 77}, // UClamp in glsl_std_450
    {IR(45997, 5), 74}, // UMax in glsl_std_450
    {IR(45982, 5), 71}, // UMin in glsl_std_450
    {IR(46241, 17), 98}, // UnpackDouble2x32 in glsl_std_450
    {IR(46196, 15), 95}, // UnpackHalf2x16 in glsl_std_450
    {IR(46164, 16), 93}, // UnpackSnorm2x16 in glsl_std_450
    {IR(46211, 15), 96}, // UnpackSnorm4x8 in glsl_std_450
    {IR(46180, 16), 94}, // UnpackUnorm2x16 in glsl_std_450
    {IR(46226, 15), 97}, // UnpackUnorm4x8 in glsl_std_450
    {IR(46424, 13), 116}, // ArgumentInfo in nonsemantic_clspvreflection
    {IR(46519, 24), 121}, // ArgumentPodPushConstant in nonsemantic_clspvreflection
    {IR(46475, 25), 119}, // ArgumentPodStorageBuffer in nonsemantic_clspvreflection
    {IR(46500, 19), 120}, // ArgumentPodUniform in nonsemantic_clspvreflection
    {IR(46953, 28), 140}, // ArgumentPointerPushConstant in nonsemantic_clspvreflection
    {IR(46981, 23), 141}, // ArgumentPointerUniform in nonsemantic_clspvreflection
    {IR(46543, 21), 122}, // ArgumentSampledImage in nonsemantic_clspvreflection
    {IR(46585, 16), 124}, // ArgumentSampler in nonsemantic_clspvreflection
    {IR(46437, 22), 117}, // ArgumentStorageBuffer in nonsemantic_clspvreflection
    {IR(46564, 21), 123}, // ArgumentStorageImage in nonsemantic_clspvreflection
    {IR(47241, 27), 148}, // ArgumentStorageTexelBuffer in nonsemantic_clspvreflection
    {IR(46459, 16), 118}, // ArgumentUniform in nonsemantic_clspvreflection
    {IR(47268, 27), 149}, // ArgumentUniformTexelBuffer in nonsemantic_clspvreflection
    {IR(46601, 18), 125}, // ArgumentWorkgroup in nonsemantic_clspvreflection
    {IR(47295, 32), 150}, // ConstantDataPointerPushConstant in nonsemantic_clspvreflection
    {IR(46849, 26), 135}, // ConstantDataStorageBuffer in nonsemantic_clspvreflection
    {IR(46875, 20), 136}, // ConstantDataUniform in nonsemantic_clspvreflection
    {IR(47119, 45), 145}, // ImageArgumentInfoChannelDataTypePushConstant in nonsemantic_clspvreflection
    {IR(47201, 40), 147}, // ImageArgumentInfoChannelDataTypeUniform in nonsemantic_clspvreflection
    {IR(47077, 42), 144}, // ImageArgumentInfoChannelOrderPushConstant in nonsemantic_clspvreflection
    {IR(47164, 37), 146}, // ImageArgumentInfoChannelOrderUniform in nonsemantic_clspvreflection
    {IR(4549, 7), 115}, // Kernel in nonsemantic_clspvreflection
    {IR(7974, 15), 137}, // LiteralSampler in nonsemantic_clspvreflection
    {IR(47436, 34), 155}, // NormalizedSamplerMaskPushConstant in nonsemantic_clspvreflection
    {IR(47404, 32), 154}, // PrintfBufferPointerPushConstant in nonsemantic_clspvreflection
    {IR(47378, 26), 153}, // PrintfBufferStorageBuffer in nonsemantic_clspvreflection
    {IR(47367, 11), 152}, // PrintfInfo in nonsemantic_clspvreflection
    {IR(47327, 40), 151}, // ProgramScopeVariablePointerPushConstant in nonsemantic_clspvreflection
    {IR(47039, 38), 143}, // ProgramScopeVariablePointerRelocation in nonsemantic_clspvreflection
    {IR(47004, 35), 142}, // ProgramScopeVariablesStorageBuffer in nonsemantic_clspvreflection
    {IR(46895, 30), 138}, // PropertyRequiredWorkgroupSize in nonsemantic_clspvreflection
    {IR(46715, 30), 130}, // PushConstantEnqueuedLocalSize in nonsemantic_clspvreflection
    {IR(46690, 25), 129}, // PushConstantGlobalOffset in nonsemantic_clspvreflection
    {IR(46745, 23), 131}, // PushConstantGlobalSize in nonsemantic_clspvreflection
    {IR(46793, 26), 133}, // PushConstantNumWorkgroups in nonsemantic_clspvreflection
    {IR(46819, 30), 134}, // PushConstantRegionGroupOffset in nonsemantic_clspvreflection
    {IR(46768, 25), 132}, // PushConstantRegionOffset in nonsemantic_clspvreflection
    {IR(46645, 25), 127}, // SpecConstantGlobalOffset in nonsemantic_clspvreflection
    {IR(46925, 28), 139}, // SpecConstantSubgroupMaxSize in nonsemantic_clspvreflection
    {IR(46670, 20), 128}, // SpecConstantWorkDim in nonsemantic_clspvreflection
    {IR(46619, 26), 126}, // SpecConstantWorkgroupSize in nonsemantic_clspvreflection
    {IR(47470, 22), 156}, // WorkgroupVariableSize in nonsemantic_clspvreflection
    {IR(47591, 21), 197}, // DebugBuildIdentifier in nonsemantic_shader_debuginfo_100
    {IR(44908, 21), 158}, // DebugCompilationUnit in nonsemantic_shader_debuginfo_100
    {IR(45635, 13), 185}, // DebugDeclare in nonsemantic_shader_debuginfo_100
    {IR(47629, 16), 199}, // DebugEntryPoint in nonsemantic_shader_debuginfo_100
    {IR(45707, 16), 188}, // DebugExpression in nonsemantic_shader_debuginfo_100
    {IR(45451, 14), 177}, // DebugFunction in nonsemantic_shader_debuginfo_100
    {IR(45426, 25), 176}, // DebugFunctionDeclaration in nonsemantic_shader_debuginfo_100
    {IR(47524, 24), 193}, // DebugFunctionDefinition in nonsemantic_shader_debuginfo_100
    {IR(45406, 20), 175}, // DebugGlobalVariable in nonsemantic_shader_debuginfo_100
    {IR(47492, 20), 191}, // DebugImportedEntity in nonsemantic_shader_debuginfo_100
    {IR(44894, 14), 157}, // DebugInfoNone in nonsemantic_shader_debuginfo_100
    {IR(45538, 15), 182}, // DebugInlinedAt in nonsemantic_shader_debuginfo_100
    {IR(45614, 21), 184}, // DebugInlinedVariable in nonsemantic_shader_debuginfo_100
    {IR(45465, 18), 178}, // DebugLexicalBlock in nonsemantic_shader_debuginfo_100
    {IR(45483, 31), 179}, // DebugLexicalBlockDiscriminator in nonsemantic_shader_debuginfo_100
    {IR(47569, 10), 195}, // DebugLine in nonsemantic_shader_debuginfo_100
    {IR(45595, 19), 183}, // DebugLocalVariable in nonsemantic_shader_debuginfo_100
    {IR(45723, 14), 189}, // DebugMacroDef in nonsemantic_shader_debuginfo_100
    {IR(45737, 16), 190}, // DebugMacroUndef in nonsemantic_shader_debuginfo_100
    {IR(47579, 12), 196}, // DebugNoLine in nonsemantic_shader_debuginfo_100
    {IR(45525, 13), 181}, // DebugNoScope in nonsemantic_shader_debuginfo_100
    {IR(45692, 15), 187}, // DebugOperation in nonsemantic_shader_debuginfo_100
    {IR(45514, 11), 180}, // DebugScope in nonsemantic_shader_debuginfo_100
    {IR(47512, 12), 192}, // DebugSource in nonsemantic_shader_debuginfo_100
    {IR(47548, 21), 194}, // DebugSourceContinued in nonsemantic_shader_debuginfo_100
    {IR(47612, 17), 198}, // DebugStoragePath in nonsemantic_shader_debuginfo_100
    {IR(45104, 15), 162}, // DebugTypeArray in nonsemantic_shader_debuginfo_100
    {IR(44981, 15), 159}, // DebugTypeBasic in nonsemantic_shader_debuginfo_100
    {IR(45218, 19), 167}, // DebugTypeComposite in nonsemantic_shader_debuginfo_100
    {IR(45166, 14), 166}, // DebugTypeEnum in nonsemantic_shader_debuginfo_100
    {IR(45148, 18), 165}, // DebugTypeFunction in nonsemantic_shader_debuginfo_100
    {IR(45253, 21), 169}, // DebugTypeInheritance in nonsemantic_shader_debuginfo_100
    {IR(47645, 16), 200}, // DebugTypeMatrix in nonsemantic_shader_debuginfo_100
    {IR(45237, 16), 168}, // DebugTypeMember in nonsemantic_shader_debuginfo_100
    {IR(45030, 17), 160}, // DebugTypePointer in nonsemantic_shader_debuginfo_100
    {IR(45274, 21), 170}, // DebugTypePtrToMember in nonsemantic_shader_debuginfo_100
    {IR(45085, 19), 161}, // DebugTypeQualifier in nonsemantic_shader_debuginfo_100
    {IR(45295, 18), 171}, // DebugTypeTemplate in nonsemantic_shader_debuginfo_100
    {IR(45313, 27), 172}, // DebugTypeTemplateParameter in nonsemantic_shader_debuginfo_100
    {IR(45375, 31), 174}, // DebugTypeTemplateParameterPack in nonsemantic_shader_debuginfo_100
    {IR(45340, 35), 173}, // DebugTypeTemplateTemplateParameter in nonsemantic_shader_debuginfo_100
    {IR(45119, 16), 163}, // DebugTypeVector in nonsemantic_shader_debuginfo_100
    {IR(45135, 13), 164}, // DebugTypedef in nonsemantic_shader_debuginfo_100
    {IR(45648, 11), 186}, // DebugValue in nonsemantic_shader_debuginfo_100
    {IR(47661, 14), 201}, // Configuration in nonsemantic_vkspreflection
    {IR(47737, 20), 206}, // DescriptorSetBuffer in nonsemantic_vkspreflection
    {IR(47757, 19), 207}, // DescriptorSetImage in nonsemantic_vkspreflection
    {IR(47776, 21), 208}, // DescriptorSetSampler in nonsemantic_vkspreflection
    {IR(47700, 14), 204}, // PushConstants in nonsemantic_vkspreflection
    {IR(47714, 23), 205}, // SpecializationMapEntry in nonsemantic_vkspreflection
    {IR(47675, 13), 202}, // StartCounter in nonsemantic_vkspreflection
    {IR(47688, 12), 203}, // StopCounter in nonsemantic_vkspreflection
    {IR(44908, 21), 210}, // DebugCompilationUnit in opencl_debuginfo_100
    {IR(45635, 13), 237}, // DebugDeclare in opencl_debuginfo_100
    {IR(45707, 16), 240}, // DebugExpression in opencl_debuginfo_100
    {IR(45451, 14), 229}, // DebugFunction in opencl_debuginfo_100
    {IR(45426, 25), 228}, // DebugFunctionDeclaration in opencl_debuginfo_100
    {IR(45406, 20), 227}, // DebugGlobalVariable in opencl_debuginfo_100
    {IR(47492, 20), 243}, // DebugImportedEntity in opencl_debuginfo_100
    {IR(44894, 14), 209}, // DebugInfoNone in opencl_debuginfo_100
    {IR(45538, 15), 234}, // DebugInlinedAt in opencl_debuginfo_100
    {IR(45614, 21), 236}, // DebugInlinedVariable in opencl_debuginfo_100
    {IR(45465, 18), 230}, // DebugLexicalBlock in opencl_debuginfo_100
    {IR(45483, 31), 231}, // DebugLexicalBlockDiscriminator in opencl_debuginfo_100
    {IR(45595, 19), 235}, // DebugLocalVariable in opencl_debuginfo_100
    {IR(45723, 14), 241}, // DebugMacroDef in opencl_debuginfo_100
    {IR(45737, 16), 242}, // DebugMacroUndef in opencl_debuginfo_100
    {IR(48097, 17), 245}, // DebugModuleINTEL in opencl_debuginfo_100
    {IR(45525, 13), 233}, // DebugNoScope in opencl_debuginfo_100
    {IR(45692, 15), 239}, // DebugOperation in opencl_debuginfo_100
    {IR(45514, 11), 232}, // DebugScope in opencl_debuginfo_100
    {IR(47512, 12), 244}, // DebugSource in opencl_debuginfo_100
    {IR(45104, 15), 214}, // DebugTypeArray in opencl_debuginfo_100
    {IR(44981, 15), 211}, // DebugTypeBasic in opencl_debuginfo_100
    {IR(45218, 19), 219}, // DebugTypeComposite in opencl_debuginfo_100
    {IR(45166, 14), 218}, // DebugTypeEnum in opencl_debuginfo_100
    {IR(45148, 18), 217}, // DebugTypeFunction in opencl_debuginfo_100
    {IR(45253, 21), 221}, // DebugTypeInheritance in opencl_debuginfo_100
    {IR(45237, 16), 220}, // DebugTypeMember in opencl_debuginfo_100
    {IR(45030, 17), 212}, // DebugTypePointer in opencl_debuginfo_100
    {IR(45274, 21), 222}, // DebugTypePtrToMember in opencl_debuginfo_100
    {IR(45085, 19), 213}, // DebugTypeQualifier in opencl_debuginfo_100
    {IR(45295, 18), 223}, // DebugTypeTemplate in opencl_debuginfo_100
    {IR(45313, 27), 224}, // DebugTypeTemplateParameter in opencl_debuginfo_100
    {IR(45375, 31), 226}, // DebugTypeTemplateParameterPack in opencl_debuginfo_100
    {IR(45340, 35), 225}, // DebugTypeTemplateTemplateParameter in opencl_debuginfo_100
    {IR(45119, 16), 215}, // DebugTypeVector in opencl_debuginfo_100
    {IR(45135, 13), 216}, // DebugTypedef in opencl_debuginfo_100
    {IR(45648, 11), 238}, // DebugValue in opencl_debuginfo_100
    {IR(48114, 5), 246}, // acos in opencl_std_100
    {IR(48119, 6), 247}, // acosh in opencl_std_100
    {IR(48125, 7), 248}, // acospi in opencl_std_100
    {IR(48132, 5), 249}, // asin in opencl_std_100
    {IR(48137, 6), 250}, // asinh in opencl_std_100
    {IR(48143, 7), 251}, // asinpi in opencl_std_100
    {IR(48150, 5), 252}, // atan in opencl_std_100
    {IR(48155, 6), 253}, // atan2 in opencl_std_100
    {IR(48174, 8), 256}, // atan2pi in opencl_std_100
    {IR(48161, 6), 254}, // atanh in opencl_std_100
    {IR(48167, 7), 255}, // atanpi in opencl_std_100
    {IR(49365, 10), 402}, // bitselect in opencl_std_100
    {IR(48182, 5), 257}, // cbrt in opencl_std_100
    {IR(48187, 5), 258}, // ceil in opencl_std_100
    {IR(49037, 4), 367}, // clz in opencl_std_100
    {IR(48192, 9), 259}, // copysign in opencl_std_100
    {IR(48201, 4), 260}, // cos in opencl_std_100
    {IR(48205, 5), 261}, // cosh in opencl_std_100
    {IR(48210, 6), 262}, // cospi in opencl_std_100
    {IR(48881, 6), 350}, // cross in opencl_std_100
    {IR(49041, 4), 368}, // ctz in opencl_std_100
    {IR(48816, 8), 342}, // degrees in opencl_std_100
    {IR(48887, 9), 351}, // distance in opencl_std_100
    {IR(48221, 4), 264}, // erf in opencl_std_100
    {IR(48216, 5), 263}, // erfc in opencl_std_100
    {IR(48225, 4), 265}, // exp in opencl_std_100
    {IR(48234, 6), 267}, // exp10 in opencl_std_100
    {IR(48229, 5), 266}, // exp2 in opencl_std_100
    {IR(48240, 6), 268}, // expm1 in opencl_std_100
    {IR(48246, 5), 269}, // fabs in opencl_std_100
    {IR(48913, 14), 354}, // fast_distance in opencl_std_100
    {IR(48927, 12), 355}, // fast_length in opencl_std_100
    {IR(48939, 15), 356}, // fast_normalize in opencl_std_100
    {IR(48809, 7), 341}, // fclamp in opencl_std_100
    {IR(48251, 5), 270}, // fdim in opencl_std_100
    {IR(48256, 6), 271}, // floor in opencl_std_100
    {IR(48262, 4), 272}, // fma in opencl_std_100
    {IR(48266, 5), 273}, // fmax in opencl_std_100
    {IR(48824, 12), 343}, // fmax_common in opencl_std_100
    {IR(48271, 5), 274}, // fmin in opencl_std_100
    {IR(48836, 12), 344}, // fmin_common in opencl_std_100
    {IR(48276, 5), 275}, // fmod in opencl_std_100
    {IR(48281, 6), 276}, // fract in opencl_std_100
    {IR(48287, 6), 277}, // frexp in opencl_std_100
    {IR(48499, 9), 313}, // half_cos in opencl_std_100
    {IR(48508, 12), 314}, // half_divide in opencl_std_100
    {IR(48520, 9), 315}, // half_exp in opencl_std_100
    {IR(48539, 11), 317}, // half_exp10 in opencl_std_100
    {IR(48529, 10), 316}, // half_exp2 in opencl_std_100
    {IR(48550, 9), 318}, // half_log in opencl_std_100
    {IR(48569, 11), 320}, // half_log10 in opencl_std_100
    {IR(48559, 10), 319}, // half_log2 in opencl_std_100
    {IR(48580, 10), 321}, // half_powr in opencl_std_100
    {IR(48590, 11), 322}, // half_recip in opencl_std_100
    {IR(48601, 11), 323}, // half_rsqrt in opencl_std_100
    {IR(48612, 9), 324}, // half_sin in opencl_std_100
    {IR(48621, 10), 325}, // half_sqrt in opencl_std_100
    {IR(48631, 9), 326}, // half_tan in opencl_std_100
    {IR(48293, 6), 278}, // hypot in opencl_std_100
    {IR(48299, 6), 279}, // ilogb in opencl_std_100
    {IR(48305, 6), 280}, // ldexp in opencl_std_100
    {IR(48896, 7), 352}, // length in opencl_std_100
    {IR(48311, 7), 281}, // lgamma in opencl_std_100
    {IR(48318, 9), 282}, // lgamma_r in opencl_std_100
    {IR(48327, 4), 283}, // log in opencl_std_100
    {IR(48336, 6), 285}, // log10 in opencl_std_100
    {IR(48342, 6), 286}, // log1p in opencl_std_100
    {IR(48331, 5), 284}, // log2 in opencl_std_100
    {IR(48348, 5), 287}, // logb in opencl_std_100
    {IR(48353, 4), 288}, // mad in opencl_std_100
    {IR(48357, 7), 289}, // maxmag in opencl_std_100
    {IR(48364, 7), 290}, // minmag in opencl_std_100
    {IR(48848, 4), 345}, // mix in opencl_std_100
    {IR(48371, 5), 291}, // modf in opencl_std_100
    {IR(48376, 4), 292}, // nan in opencl_std_100
    {IR(48640, 11), 327}, // native_cos in opencl_std_100
    {IR(48651, 14), 328}, // native_divide in opencl_std_100
    {IR(48665, 11), 329}, // native_exp in opencl_std_100
    {IR(48688, 13), 331}, // native_exp10 in opencl_std_100
    {IR(48676, 12), 330}, // native_exp2 in opencl_std_100
    {IR(48701, 11), 332}, // native_log in opencl_std_100
    {IR(48724, 13), 334}, // native_log10 in opencl_std_100
    {IR(48712, 12), 333}, // native_log2 in opencl_std_100
    {IR(48737, 12), 335}, // native_powr in opencl_std_100
    {IR(48749, 13), 336}, // native_recip in opencl_std_100
    {IR(48762, 13), 337}, // native_rsqrt in opencl_std_100
    {IR(48775, 11), 338}, // native_sin in opencl_std_100
    {IR(48786, 12), 339}, // native_sqrt in opencl_std_100
    {IR(48798, 11), 340}, // native_tan in opencl_std_100
    {IR(48380, 10), 293}, // nextafter in opencl_std_100
    {IR(48903, 10), 353}, // normalize in opencl_std_100
    {IR(49156, 9), 382}, // popcount in opencl_std_100
    {IR(48390, 4), 294}, // pow in opencl_std_100
    {IR(48394, 5), 295}, // pown in opencl_std_100
    {IR(48399, 5), 296}, // powr in opencl_std_100
    {IR(49356, 9), 401}, // prefetch in opencl_std_100
    {IR(49349, 7), 400}, // printf in opencl_std_100
    {IR(48852, 8), 346}, // radians in opencl_std_100
    {IR(48404, 10), 297}, // remainder in opencl_std_100
    {IR(48414, 7), 298}, // remquo in opencl_std_100
    {IR(48421, 5), 299}, // rint in opencl_std_100
    {IR(48426, 6), 300}, // rootn in opencl_std_100
    {IR(49107, 7), 377}, // rotate in opencl_std_100
    {IR(48432, 6), 301}, // round in opencl_std_100
    {IR(48438, 6), 302}, // rsqrt in opencl_std_100
    {IR(48954, 6), 357}, // s_abs in opencl_std_100
    {IR(48960, 11), 358}, // s_abs_diff in opencl_std_100
    {IR(48971, 10), 359}, // s_add_sat in opencl_std_100
    {IR(49021, 8), 365}, // s_clamp in opencl_std_100
    {IR(48991, 7), 361}, // s_hadd in opencl_std_100
    {IR(49165, 8), 383}, // s_mad24 in opencl_std_100
    {IR(49045, 9), 369}, // s_mad_hi in opencl_std_100
    {IR(49064, 10), 371}, // s_mad_sat in opencl_std_100
    {IR(49074, 6), 372}, // s_max in opencl_std_100
    {IR(49086, 6), 374}, // s_min in opencl_std_100
    {IR(49181, 8), 385}, // s_mul24 in opencl_std_100
    {IR(49098, 9), 376}, // s_mul_hi in opencl_std_100
    {IR(49005, 8), 363}, // s_rhadd in opencl_std_100
    {IR(49114, 10), 378}, // s_sub_sat in opencl_std_100
    {IR(49145, 11), 381}, // s_upsample in opencl_std_100
    {IR(49375, 7), 403}, // select in opencl_std_100
    {IR(49332, 8), 398}, // shuffle in opencl_std_100
    {IR(49340, 9), 399}, // shuffle2 in opencl_std_100
    {IR(48876, 5), 349}, // sign in opencl_std_100
    {IR(48444, 4), 303}, // sin in opencl_std_100
    {IR(48448, 7), 304}, // sincos in opencl_std_100
    {IR(48455, 5), 305}, // sinh in opencl_std_100
    {IR(48460, 6), 306}, // sinpi in opencl_std_100
    {IR(48865, 11), 348}, // smoothstep in opencl_std_100
    {IR(48466, 5), 307}, // sqrt in opencl_std_100
    {IR(48860, 5), 347}, // step in opencl_std_100
    {IR(48471, 4), 308}, // tan in opencl_std_100
    {IR(48475, 5), 309}, // tanh in opencl_std_100
    {IR(48480, 6), 310}, // tanpi in opencl_std_100
    {IR(48486, 7), 311}, // tgamma in opencl_std_100
    {IR(48493, 6), 312}, // trunc in opencl_std_100
    {IR(49382, 6), 404}, // u_abs in opencl_std_100
    {IR(49388, 11), 405}, // u_abs_diff in opencl_std_100
    {IR(48981, 10), 360}, // u_add_sat in opencl_std_100
    {IR(49029, 8), 366}, // u_clamp in opencl_std_100
    {IR(48998, 7), 362}, // u_hadd in opencl_std_100
    {IR(49173, 8), 384}, // u_mad24 in opencl_std_100
    {IR(49408, 9), 407}, // u_mad_hi in opencl_std_100
    {IR(49054, 10), 370}, // u_mad_sat in opencl_std_100
    {IR(49080, 6), 373}, // u_max in opencl_std_100
    {IR(49092, 6), 375}, // u_min in opencl_std_100
    {IR(49189, 8), 386}, // u_mul24 in opencl_std_100
    {IR(49399, 9), 406}, // u_mul_hi in opencl_std_100
    {IR(49013, 8), 364}, // u_rhadd in opencl_std_100
    {IR(49124, 10), 379}, // u_sub_sat in opencl_std_100
    {IR(49134, 11), 380}, // u_upsample in opencl_std_100
    {IR(49212, 11), 389}, // vload_half in opencl_std_100
    {IR(49223, 12), 390}, // vload_halfn in opencl_std_100
    {IR(49289, 13), 395}, // vloada_halfn in opencl_std_100
    {IR(49197, 7), 387}, // vloadn in opencl_std_100
    {IR(49235, 12), 391}, // vstore_half in opencl_std_100
    {IR(49247, 14), 392}, // vstore_half_r in opencl_std_100
    {IR(49261, 13), 393}, // vstore_halfn in opencl_std_100
    {IR(49274, 15), 394}, // vstore_halfn_r in opencl_std_100
    {IR(49302, 14), 396}, // vstorea_halfn in opencl_std_100
    {IR(49316, 16), 397}, // vstorea_halfn_r in opencl_std_100
    {IR(49204, 8), 388}, // vstoren in opencl_std_100
    {IR(49434, 17), 409}, // CubeFaceCoordAMD in spv_amd_gcn_shader
    {IR(49417, 17), 408}, // CubeFaceIndexAMD in spv_amd_gcn_shader
    {IR(49451, 8), 410}, // TimeAMD in spv_amd_gcn_shader
    {IR(49528, 9), 414}, // MbcntAMD in spv_amd_shader_ballot
    {IR(49459, 22), 411}, // SwizzleInvocationsAMD in spv_amd_shader_ballot
    {IR(49481, 28), 412}, // SwizzleInvocationsMaskedAMD in spv_amd_shader_ballot
    {IR(49509, 19), 413}, // WriteInvocationAMD in spv_amd_shader_ballot
    {IR(49537, 23), 415}, // InterpolateAtVertexAMD in spv_amd_shader_explicit_vertex_parameter
    {IR(49587, 9), 419}, // FMax3AMD in spv_amd_shader_trinary_minmax
    {IR(49614, 9), 422}, // FMid3AMD in spv_amd_shader_trinary_minmax
    {IR(49560, 9), 416}, // FMin3AMD in spv_amd_shader_trinary_minmax
    {IR(49605, 9), 421}, // SMax3AMD in spv_amd_shader_trinary_minmax
    {IR(49632, 9), 424}, // SMid3AMD in spv_amd_shader_trinary_minmax
    {IR(49578, 9), 418}, // SMin3AMD in spv_amd_shader_trinary_minmax
    {IR(49596, 9), 420}, // UMax3AMD in spv_amd_shader_trinary_minmax
    {IR(49623, 9), 423}, // UMid3AMD in spv_amd_shader_trinary_minmax
    {IR(49569, 9), 417}, // UMin3AMD in spv_amd_shader_trinary_minmax
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
  "SPV_ARM_tensors\0" // IR(426, 16)
  "SPV_EXT_arithmetic_fence\0" // IR(442, 25)
  "SPV_EXT_demote_to_helper_invocation\0" // IR(467, 36)
  "SPV_EXT_descriptor_indexing\0" // IR(503, 28)
  "SPV_EXT_float8\0" // IR(531, 15)
  "SPV_EXT_fragment_fully_covered\0" // IR(546, 31)
  "SPV_EXT_fragment_invocation_density\0" // IR(577, 36)
  "SPV_EXT_fragment_shader_interlock\0" // IR(613, 34)
  "SPV_EXT_mesh_shader\0" // IR(647, 20)
  "SPV_EXT_opacity_micromap\0" // IR(667, 25)
  "SPV_EXT_optnone\0" // IR(692, 16)
  "SPV_EXT_physical_storage_buffer\0" // IR(708, 32)
  "SPV_EXT_relaxed_printf_string_address_space\0" // IR(740, 44)
  "SPV_EXT_replicated_composites\0" // IR(784, 30)
  "SPV_EXT_shader_atomic_float16_add\0" // IR(814, 34)
  "SPV_EXT_shader_atomic_float_add\0" // IR(848, 32)
  "SPV_EXT_shader_atomic_float_min_max\0" // IR(880, 36)
  "SPV_EXT_shader_image_int64\0" // IR(916, 27)
  "SPV_EXT_shader_stencil_export\0" // IR(943, 30)
  "SPV_EXT_shader_tile_image\0" // IR(973, 26)
  "SPV_EXT_shader_viewport_index_layer\0" // IR(999, 36)
  "SPV_GOOGLE_decorate_string\0" // IR(1035, 27)
  "SPV_GOOGLE_hlsl_functionality1\0" // IR(1062, 31)
  "SPV_GOOGLE_user_type\0" // IR(1093, 21)
  "SPV_INTEL_2d_block_io\0" // IR(1114, 22)
  "SPV_INTEL_arbitrary_precision_fixed_point\0" // IR(1136, 42)
  "SPV_INTEL_arbitrary_precision_floating_point\0" // IR(1178, 45)
  "SPV_INTEL_arbitrary_precision_integers\0" // IR(1223, 39)
  "SPV_INTEL_bfloat16_conversion\0" // IR(1262, 30)
  "SPV_INTEL_bindless_images\0" // IR(1292, 26)
  "SPV_INTEL_blocking_pipes\0" // IR(1318, 25)
  "SPV_INTEL_cache_controls\0" // IR(1343, 25)
  "SPV_INTEL_debug_module\0" // IR(1368, 23)
  "SPV_INTEL_device_side_avc_motion_estimation\0" // IR(1391, 44)
  "SPV_INTEL_float_controls2\0" // IR(1435, 26)
  "SPV_INTEL_fp_fast_math_mode\0" // IR(1461, 28)
  "SPV_INTEL_fp_max_error\0" // IR(1489, 23)
  "SPV_INTEL_fpga_argument_interfaces\0" // IR(1512, 35)
  "SPV_INTEL_fpga_buffer_location\0" // IR(1547, 31)
  "SPV_INTEL_fpga_cluster_attributes\0" // IR(1578, 34)
  "SPV_INTEL_fpga_dsp_control\0" // IR(1612, 27)
  "SPV_INTEL_fpga_invocation_pipelining_attributes\0" // IR(1639, 48)
  "SPV_INTEL_fpga_latency_control\0" // IR(1687, 31)
  "SPV_INTEL_fpga_loop_controls\0" // IR(1718, 29)
  "SPV_INTEL_fpga_memory_accesses\0" // IR(1747, 31)
  "SPV_INTEL_fpga_memory_attributes\0" // IR(1778, 33)
  "SPV_INTEL_fpga_reg\0" // IR(1811, 19)
  "SPV_INTEL_function_pointers\0" // IR(1830, 28)
  "SPV_INTEL_global_variable_fpga_decorations\0" // IR(1858, 43)
  "SPV_INTEL_global_variable_host_access\0" // IR(1901, 38)
  "SPV_INTEL_inline_assembly\0" // IR(1939, 26)
  "SPV_INTEL_int4\0" // IR(1965, 15)
  "SPV_INTEL_io_pipes\0" // IR(1980, 19)
  "SPV_INTEL_kernel_attributes\0" // IR(1999, 28)
  "SPV_INTEL_long_composites\0" // IR(2027, 26)
  "SPV_INTEL_loop_fuse\0" // IR(2053, 20)
  "SPV_INTEL_masked_gather_scatter\0" // IR(2073, 32)
  "SPV_INTEL_maximum_registers\0" // IR(2105, 28)
  "SPV_INTEL_media_block_io\0" // IR(2133, 25)
  "SPV_INTEL_memory_access_aliasing\0" // IR(2158, 33)
  "SPV_INTEL_optnone\0" // IR(2191, 18)
  "SPV_INTEL_runtime_aligned\0" // IR(2209, 26)
  "SPV_INTEL_shader_integer_functions2\0" // IR(2235, 36)
  "SPV_INTEL_split_barrier\0" // IR(2271, 24)
  "SPV_INTEL_subgroup_buffer_prefetch\0" // IR(2295, 35)
  "SPV_INTEL_subgroup_matrix_multiply_accumulate\0" // IR(2330, 46)
  "SPV_INTEL_subgroups\0" // IR(2376, 20)
  "SPV_INTEL_task_sequence\0" // IR(2396, 24)
  "SPV_INTEL_tensor_float32_conversion\0" // IR(2420, 36)
  "SPV_INTEL_ternary_bitwise_function\0" // IR(2456, 35)
  "SPV_INTEL_unstructured_loop_controls\0" // IR(2491, 37)
  "SPV_INTEL_usm_storage_classes\0" // IR(2528, 30)
  "SPV_INTEL_variable_length_array\0" // IR(2558, 32)
  "SPV_INTEL_vector_compute\0" // IR(2590, 25)
  "SPV_KHR_16bit_storage\0" // IR(2615, 22)
  "SPV_KHR_8bit_storage\0" // IR(2637, 21)
  "SPV_KHR_bfloat16\0" // IR(2658, 17)
  "SPV_KHR_bit_instructions\0" // IR(2675, 25)
  "SPV_KHR_compute_shader_derivatives\0" // IR(2700, 35)
  "SPV_KHR_cooperative_matrix\0" // IR(2735, 27)
  "SPV_KHR_device_group\0" // IR(2762, 21)
  "SPV_KHR_expect_assume\0" // IR(2783, 22)
  "SPV_KHR_float_controls\0" // IR(2805, 23)
  "SPV_KHR_float_controls2\0" // IR(2828, 24)
  "SPV_KHR_fragment_shader_barycentric\0" // IR(2852, 36)
  "SPV_KHR_fragment_shading_rate\0" // IR(2888, 30)
  "SPV_KHR_integer_dot_product\0" // IR(2918, 28)
  "SPV_KHR_linkonce_odr\0" // IR(2946, 21)
  "SPV_KHR_maximal_reconvergence\0" // IR(2967, 30)
  "SPV_KHR_multiview\0" // IR(2997, 18)
  "SPV_KHR_no_integer_wrap_decoration\0" // IR(3015, 35)
  "SPV_KHR_non_semantic_info\0" // IR(3050, 26)
  "SPV_KHR_physical_storage_buffer\0" // IR(3076, 32)
  "SPV_KHR_post_depth_coverage\0" // IR(3108, 28)
  "SPV_KHR_quad_control\0" // IR(3136, 21)
  "SPV_KHR_ray_cull_mask\0" // IR(3157, 22)
  "SPV_KHR_ray_query\0" // IR(3179, 18)
  "SPV_KHR_ray_tracing\0" // IR(3197, 20)
  "SPV_KHR_ray_tracing_position_fetch\0" // IR(3217, 35)
  "SPV_KHR_relaxed_extended_instruction\0" // IR(3252, 37)
  "SPV_KHR_shader_atomic_counter_ops\0" // IR(3289, 34)
  "SPV_KHR_shader_ballot\0" // IR(3323, 22)
  "SPV_KHR_shader_clock\0" // IR(3345, 21)
  "SPV_KHR_shader_draw_parameters\0" // IR(3366, 31)
  "SPV_KHR_storage_buffer_storage_class\0" // IR(3397, 37)
  "SPV_KHR_subgroup_rotate\0" // IR(3434, 24)
  "SPV_KHR_subgroup_uniform_control_flow\0" // IR(3458, 38)
  "SPV_KHR_subgroup_vote\0" // IR(3496, 22)
  "SPV_KHR_terminate_invocation\0" // IR(3518, 29)
  "SPV_KHR_uniform_group_instructions\0" // IR(3547, 35)
  "SPV_KHR_untyped_pointers\0" // IR(3582, 25)
  "SPV_KHR_variable_pointers\0" // IR(3607, 26)
  "SPV_KHR_vulkan_memory_model\0" // IR(3633, 28)
  "SPV_KHR_workgroup_memory_explicit_layout\0" // IR(3661, 41)
  "SPV_NVX_multiview_per_view_attributes\0" // IR(3702, 38)
  "SPV_NV_bindless_texture\0" // IR(3740, 24)
  "SPV_NV_cluster_acceleration_structure\0" // IR(3764, 38)
  "SPV_NV_compute_shader_derivatives\0" // IR(3802, 34)
  "SPV_NV_cooperative_matrix\0" // IR(3836, 26)
  "SPV_NV_cooperative_matrix2\0" // IR(3862, 27)
  "SPV_NV_cooperative_vector\0" // IR(3889, 26)
  "SPV_NV_displacement_micromap\0" // IR(3915, 29)
  "SPV_NV_fragment_shader_barycentric\0" // IR(3944, 35)
  "SPV_NV_geometry_shader_passthrough\0" // IR(3979, 35)
  "SPV_NV_linear_swept_spheres\0" // IR(4014, 28)
  "SPV_NV_mesh_shader\0" // IR(4042, 19)
  "SPV_NV_raw_access_chains\0" // IR(4061, 25)
  "SPV_NV_ray_tracing\0" // IR(4086, 19)
  "SPV_NV_ray_tracing_motion_blur\0" // IR(4105, 31)
  "SPV_NV_sample_mask_override_coverage\0" // IR(4136, 37)
  "SPV_NV_shader_atomic_fp16_vector\0" // IR(4173, 33)
  "SPV_NV_shader_image_footprint\0" // IR(4206, 30)
  "SPV_NV_shader_invocation_reorder\0" // IR(4236, 33)
  "SPV_NV_shader_sm_builtins\0" // IR(4269, 26)
  "SPV_NV_shader_subgroup_partitioned\0" // IR(4295, 35)
  "SPV_NV_shading_rate\0" // IR(4330, 20)
  "SPV_NV_stereo_view_rendering\0" // IR(4350, 29)
  "SPV_NV_tensor_addressing\0" // IR(4379, 25)
  "SPV_NV_viewport_array2\0" // IR(4404, 23)
  "SPV_QCOM_image_processing\0" // IR(4427, 26)
  "SPV_QCOM_image_processing2\0" // IR(4453, 27)
  "SPV_QCOM_tile_shading\0" // IR(4480, 22)
  "SPV_VALIDATOR_ignore_type_decl_unique\0" // IR(4502, 38)
  "ReadOnly\0" // IR(4540, 9)
  "Kernel\0" // IR(4549, 7)
  "WriteOnly\0" // IR(4556, 10)
  "ReadWrite\0" // IR(4566, 10)
  "Logical\0" // IR(4576, 8)
  "Physical32\0" // IR(4584, 11)
  "Addresses\0" // IR(4595, 10)
  "Physical64\0" // IR(4605, 11)
  "PhysicalStorageBuffer64\0" // IR(4616, 24)
  "PhysicalStorageBuffer64EXT\0" // IR(4640, 27)
  "PhysicalStorageBufferAddresses\0" // IR(4667, 31)
  "Position\0" // IR(4698, 9)
  "Shader\0" // IR(4707, 7)
  "PointSize\0" // IR(4714, 10)
  "ClipDistance\0" // IR(4724, 13)
  "CullDistance\0" // IR(4737, 13)
  "VertexId\0" // IR(4750, 9)
  "InstanceId\0" // IR(4759, 11)
  "PrimitiveId\0" // IR(4770, 12)
  "Geometry\0" // IR(4782, 9)
  "Tessellation\0" // IR(4791, 13)
  "RayTracingNV\0" // IR(4804, 13)
  "RayTracingKHR\0" // IR(4817, 14)
  "MeshShadingNV\0" // IR(4831, 14)
  "MeshShadingEXT\0" // IR(4845, 15)
  "InvocationId\0" // IR(4860, 13)
  "Layer\0" // IR(4873, 6)
  "ShaderLayer\0" // IR(4879, 12)
  "ShaderViewportIndexLayerEXT\0" // IR(4891, 28)
  "ViewportIndex\0" // IR(4919, 14)
  "MultiViewport\0" // IR(4933, 14)
  "ShaderViewportIndex\0" // IR(4947, 20)
  "TessLevelOuter\0" // IR(4967, 15)
  "TessLevelInner\0" // IR(4982, 15)
  "TessCoord\0" // IR(4997, 10)
  "PatchVertices\0" // IR(5007, 14)
  "FragCoord\0" // IR(5021, 10)
  "PointCoord\0" // IR(5031, 11)
  "FrontFacing\0" // IR(5042, 12)
  "SampleId\0" // IR(5054, 9)
  "SampleRateShading\0" // IR(5063, 18)
  "SamplePosition\0" // IR(5081, 15)
  "SampleMask\0" // IR(5096, 11)
  "FragDepth\0" // IR(5107, 10)
  "HelperInvocation\0" // IR(5117, 17)
  "NumWorkgroups\0" // IR(5134, 14)
  "WorkgroupSize\0" // IR(5148, 14)
  "WorkgroupId\0" // IR(5162, 12)
  "LocalInvocationId\0" // IR(5174, 18)
  "GlobalInvocationId\0" // IR(5192, 19)
  "LocalInvocationIndex\0" // IR(5211, 21)
  "WorkDim\0" // IR(5232, 8)
  "GlobalSize\0" // IR(5240, 11)
  "EnqueuedWorkgroupSize\0" // IR(5251, 22)
  "GlobalOffset\0" // IR(5273, 13)
  "GlobalLinearId\0" // IR(5286, 15)
  "SubgroupSize\0" // IR(5301, 13)
  "GroupNonUniform\0" // IR(5314, 16)
  "SubgroupBallotKHR\0" // IR(5330, 18)
  "SubgroupMaxSize\0" // IR(5348, 16)
  "NumSubgroups\0" // IR(5364, 13)
  "NumEnqueuedSubgroups\0" // IR(5377, 21)
  "SubgroupId\0" // IR(5398, 11)
  "SubgroupLocalInvocationId\0" // IR(5409, 26)
  "VertexIndex\0" // IR(5435, 12)
  "InstanceIndex\0" // IR(5447, 14)
  "CoreIDARM\0" // IR(5461, 10)
  "CoreBuiltinsARM\0" // IR(5471, 16)
  "CoreCountARM\0" // IR(5487, 13)
  "CoreMaxIDARM\0" // IR(5500, 13)
  "WarpIDARM\0" // IR(5513, 10)
  "WarpMaxIDARM\0" // IR(5523, 13)
  "SubgroupEqMask\0" // IR(5536, 15)
  "SubgroupEqMaskKHR\0" // IR(5551, 18)
  "GroupNonUniformBallot\0" // IR(5569, 22)
  "SubgroupGeMask\0" // IR(5591, 15)
  "SubgroupGeMaskKHR\0" // IR(5606, 18)
  "SubgroupGtMask\0" // IR(5624, 15)
  "SubgroupGtMaskKHR\0" // IR(5639, 18)
  "SubgroupLeMask\0" // IR(5657, 15)
  "SubgroupLeMaskKHR\0" // IR(5672, 18)
  "SubgroupLtMask\0" // IR(5690, 15)
  "SubgroupLtMaskKHR\0" // IR(5705, 18)
  "BaseVertex\0" // IR(5723, 11)
  "DrawParameters\0" // IR(5734, 15)
  "BaseInstance\0" // IR(5749, 13)
  "DrawIndex\0" // IR(5762, 10)
  "PrimitiveShadingRateKHR\0" // IR(5772, 24)
  "FragmentShadingRateKHR\0" // IR(5796, 23)
  "DeviceIndex\0" // IR(5819, 12)
  "DeviceGroup\0" // IR(5831, 12)
  "ViewIndex\0" // IR(5843, 10)
  "MultiView\0" // IR(5853, 10)
  "ShadingRateKHR\0" // IR(5863, 15)
  "TileOffsetQCOM\0" // IR(5878, 15)
  "TileShadingQCOM\0" // IR(5893, 16)
  "TileDimensionQCOM\0" // IR(5909, 18)
  "TileApronSizeQCOM\0" // IR(5927, 18)
  "BaryCoordNoPerspAMD\0" // IR(5945, 20)
  "BaryCoordNoPerspCentroidAMD\0" // IR(5965, 28)
  "BaryCoordNoPerspSampleAMD\0" // IR(5993, 26)
  "BaryCoordSmoothAMD\0" // IR(6019, 19)
  "BaryCoordSmoothCentroidAMD\0" // IR(6038, 27)
  "BaryCoordSmoothSampleAMD\0" // IR(6065, 25)
  "BaryCoordPullModelAMD\0" // IR(6090, 22)
  "FragStencilRefEXT\0" // IR(6112, 18)
  "StencilExportEXT\0" // IR(6130, 17)
  "RemainingRecursionLevelsAMDX\0" // IR(6147, 29)
  "ShaderEnqueueAMDX\0" // IR(6176, 18)
  "ShaderIndexAMDX\0" // IR(6194, 16)
  "ViewportMaskNV\0" // IR(6210, 15)
  "ShaderViewportMaskNV\0" // IR(6225, 21)
  "SecondaryPositionNV\0" // IR(6246, 20)
  "ShaderStereoViewNV\0" // IR(6266, 19)
  "SecondaryViewportMaskNV\0" // IR(6285, 24)
  "PositionPerViewNV\0" // IR(6309, 18)
  "PerViewAttributesNV\0" // IR(6327, 20)
  "ViewportMaskPerViewNV\0" // IR(6347, 22)
  "FullyCoveredEXT\0" // IR(6369, 16)
  "FragmentFullyCoveredEXT\0" // IR(6385, 24)
  "TaskCountNV\0" // IR(6409, 12)
  "PrimitiveCountNV\0" // IR(6421, 17)
  "PrimitiveIndicesNV\0" // IR(6438, 19)
  "ClipDistancePerViewNV\0" // IR(6457, 22)
  "CullDistancePerViewNV\0" // IR(6479, 22)
  "LayerPerViewNV\0" // IR(6501, 15)
  "MeshViewCountNV\0" // IR(6516, 16)
  "MeshViewIndicesNV\0" // IR(6532, 18)
  "BaryCoordKHR\0" // IR(6550, 13)
  "BaryCoordNV\0" // IR(6563, 12)
  "FragmentBarycentricKHR\0" // IR(6575, 23)
  "BaryCoordNoPerspKHR\0" // IR(6598, 20)
  "BaryCoordNoPerspNV\0" // IR(6618, 19)
  "FragSizeEXT\0" // IR(6637, 12)
  "FragmentSizeNV\0" // IR(6649, 15)
  "FragmentDensityEXT\0" // IR(6664, 19)
  "FragInvocationCountEXT\0" // IR(6683, 23)
  "InvocationsPerPixelNV\0" // IR(6706, 22)
  "PrimitivePointIndicesEXT\0" // IR(6728, 25)
  "PrimitiveLineIndicesEXT\0" // IR(6753, 24)
  "PrimitiveTriangleIndicesEXT\0" // IR(6777, 28)
  "CullPrimitiveEXT\0" // IR(6805, 17)
  "LaunchIdKHR\0" // IR(6822, 12)
  "LaunchIdNV\0" // IR(6834, 11)
  "LaunchSizeKHR\0" // IR(6845, 14)
  "LaunchSizeNV\0" // IR(6859, 13)
  "WorldRayOriginKHR\0" // IR(6872, 18)
  "WorldRayOriginNV\0" // IR(6890, 17)
  "WorldRayDirectionKHR\0" // IR(6907, 21)
  "WorldRayDirectionNV\0" // IR(6928, 20)
  "ObjectRayOriginKHR\0" // IR(6948, 19)
  "ObjectRayOriginNV\0" // IR(6967, 18)
  "ObjectRayDirectionKHR\0" // IR(6985, 22)
  "ObjectRayDirectionNV\0" // IR(7007, 21)
  "RayTminKHR\0" // IR(7028, 11)
  "RayTminNV\0" // IR(7039, 10)
  "RayTmaxKHR\0" // IR(7049, 11)
  "RayTmaxNV\0" // IR(7060, 10)
  "InstanceCustomIndexKHR\0" // IR(7070, 23)
  "InstanceCustomIndexNV\0" // IR(7093, 22)
  "ObjectToWorldKHR\0" // IR(7115, 17)
  "ObjectToWorldNV\0" // IR(7132, 16)
  "WorldToObjectKHR\0" // IR(7148, 17)
  "WorldToObjectNV\0" // IR(7165, 16)
  "HitTNV\0" // IR(7181, 7)
  "HitKindKHR\0" // IR(7188, 11)
  "HitKindNV\0" // IR(7199, 10)
  "CurrentRayTimeNV\0" // IR(7209, 17)
  "RayTracingMotionBlurNV\0" // IR(7226, 23)
  "HitTriangleVertexPositionsKHR\0" // IR(7249, 30)
  "RayTracingPositionFetchKHR\0" // IR(7279, 27)
  "HitMicroTriangleVertexPositionsNV\0" // IR(7306, 34)
  "RayTracingDisplacementMicromapNV\0" // IR(7340, 33)
  "HitMicroTriangleVertexBarycentricsNV\0" // IR(7373, 37)
  "IncomingRayFlagsKHR\0" // IR(7410, 20)
  "IncomingRayFlagsNV\0" // IR(7430, 19)
  "RayGeometryIndexKHR\0" // IR(7449, 20)
  "HitIsSphereNV\0" // IR(7469, 14)
  "RayTracingSpheresGeometryNV\0" // IR(7483, 28)
  "HitIsLSSNV\0" // IR(7511, 11)
  "RayTracingLinearSweptSpheresGeometryNV\0" // IR(7522, 39)
  "HitSpherePositionNV\0" // IR(7561, 20)
  "WarpsPerSMNV\0" // IR(7581, 13)
  "ShaderSMBuiltinsNV\0" // IR(7594, 19)
  "SMCountNV\0" // IR(7613, 10)
  "WarpIDNV\0" // IR(7623, 9)
  "SMIDNV\0" // IR(7632, 7)
  "HitLSSPositionsNV\0" // IR(7639, 18)
  "HitKindFrontFacingMicroTriangleNV\0" // IR(7657, 34)
  "HitKindBackFacingMicroTriangleNV\0" // IR(7691, 33)
  "HitSphereRadiusNV\0" // IR(7724, 18)
  "HitLSSRadiiNV\0" // IR(7742, 14)
  "ClusterIDNV\0" // IR(7756, 12)
  "RayTracingClusterAccelerationStructureNV\0" // IR(7768, 41)
  "CullMaskKHR\0" // IR(7809, 12)
  "RayCullMaskKHR\0" // IR(7821, 15)
  "Matrix\0" // IR(7836, 7)
  "Linkage\0" // IR(7843, 8)
  "Vector16\0" // IR(7851, 9)
  "Float16Buffer\0" // IR(7860, 14)
  "Float16\0" // IR(7874, 8)
  "Float64\0" // IR(7882, 8)
  "Int64\0" // IR(7890, 6)
  "Int64Atomics\0" // IR(7896, 13)
  "ImageBasic\0" // IR(7909, 11)
  "ImageReadWrite\0" // IR(7920, 15)
  "ImageMipmap\0" // IR(7935, 12)
  "Pipes\0" // IR(7947, 6)
  "Groups\0" // IR(7953, 7)
  "DeviceEnqueue\0" // IR(7960, 14)
  "LiteralSampler\0" // IR(7974, 15)
  "AtomicStorage\0" // IR(7989, 14)
  "Int16\0" // IR(8003, 6)
  "TessellationPointSize\0" // IR(8009, 22)
  "GeometryPointSize\0" // IR(8031, 18)
  "ImageGatherExtended\0" // IR(8049, 20)
  "StorageImageMultisample\0" // IR(8069, 24)
  "UniformBufferArrayDynamicIndexing\0" // IR(8093, 34)
  "SampledImageArrayDynamicIndexing\0" // IR(8127, 33)
  "StorageBufferArrayDynamicIndexing\0" // IR(8160, 34)
  "StorageImageArrayDynamicIndexing\0" // IR(8194, 33)
  "ImageCubeArray\0" // IR(8227, 15)
  "SampledCubeArray\0" // IR(8242, 17)
  "ImageRect\0" // IR(8259, 10)
  "SampledRect\0" // IR(8269, 12)
  "GenericPointer\0" // IR(8281, 15)
  "Int8\0" // IR(8296, 5)
  "InputAttachment\0" // IR(8301, 16)
  "SparseResidency\0" // IR(8317, 16)
  "MinLod\0" // IR(8333, 7)
  "Sampled1D\0" // IR(8340, 10)
  "Image1D\0" // IR(8350, 8)
  "SampledBuffer\0" // IR(8358, 14)
  "ImageBuffer\0" // IR(8372, 12)
  "ImageMSArray\0" // IR(8384, 13)
  "StorageImageExtendedFormats\0" // IR(8397, 28)
  "ImageQuery\0" // IR(8425, 11)
  "DerivativeControl\0" // IR(8436, 18)
  "InterpolationFunction\0" // IR(8454, 22)
  "TransformFeedback\0" // IR(8476, 18)
  "GeometryStreams\0" // IR(8494, 16)
  "StorageImageReadWithoutFormat\0" // IR(8510, 30)
  "StorageImageWriteWithoutFormat\0" // IR(8540, 31)
  "SubgroupDispatch\0" // IR(8571, 17)
  "NamedBarrier\0" // IR(8588, 13)
  "PipeStorage\0" // IR(8601, 12)
  "GroupNonUniformVote\0" // IR(8613, 20)
  "GroupNonUniformArithmetic\0" // IR(8633, 26)
  "GroupNonUniformShuffle\0" // IR(8659, 23)
  "GroupNonUniformShuffleRelative\0" // IR(8682, 31)
  "GroupNonUniformClustered\0" // IR(8713, 25)
  "GroupNonUniformQuad\0" // IR(8738, 20)
  "UniformDecoration\0" // IR(8758, 18)
  "TileImageColorReadAccessEXT\0" // IR(8776, 28)
  "TileImageDepthReadAccessEXT\0" // IR(8804, 28)
  "TileImageStencilReadAccessEXT\0" // IR(8832, 30)
  "TensorsARM\0" // IR(8862, 11)
  "StorageTensorArrayDynamicIndexingARM\0" // IR(8873, 37)
  "StorageTensorArrayNonUniformIndexingARM\0" // IR(8910, 40)
  "CooperativeMatrixLayoutsARM\0" // IR(8950, 28)
  "Float8EXT\0" // IR(8978, 10)
  "Float8CooperativeMatrixEXT\0" // IR(8988, 27)
  "WorkgroupMemoryExplicitLayoutKHR\0" // IR(9015, 33)
  "WorkgroupMemoryExplicitLayout8BitAccessKHR\0" // IR(9048, 43)
  "WorkgroupMemoryExplicitLayout16BitAccessKHR\0" // IR(9091, 44)
  "SubgroupVoteKHR\0" // IR(9135, 16)
  "StorageBuffer16BitAccess\0" // IR(9151, 25)
  "StorageUniformBufferBlock16\0" // IR(9176, 28)
  "UniformAndStorageBuffer16BitAccess\0" // IR(9204, 35)
  "StorageUniform16\0" // IR(9239, 17)
  "StoragePushConstant16\0" // IR(9256, 22)
  "StorageInputOutput16\0" // IR(9278, 21)
  "VariablePointersStorageBuffer\0" // IR(9299, 30)
  "VariablePointers\0" // IR(9329, 17)
  "AtomicStorageOps\0" // IR(9346, 17)
  "SampleMaskPostDepthCoverage\0" // IR(9363, 28)
  "StorageBuffer8BitAccess\0" // IR(9391, 24)
  "UniformAndStorageBuffer8BitAccess\0" // IR(9415, 34)
  "StoragePushConstant8\0" // IR(9449, 21)
  "DenormPreserve\0" // IR(9470, 15)
  "DenormFlushToZero\0" // IR(9485, 18)
  "SignedZeroInfNanPreserve\0" // IR(9503, 25)
  "RoundingModeRTE\0" // IR(9528, 16)
  "RoundingModeRTZ\0" // IR(9544, 16)
  "RayQueryProvisionalKHR\0" // IR(9560, 23)
  "RayQueryKHR\0" // IR(9583, 12)
  "UntypedPointersKHR\0" // IR(9595, 19)
  "RayTraversalPrimitiveCullingKHR\0" // IR(9614, 32)
  "TextureSampleWeightedQCOM\0" // IR(9646, 26)
  "TextureBoxFilterQCOM\0" // IR(9672, 21)
  "TextureBlockMatchQCOM\0" // IR(9693, 22)
  "TextureBlockMatch2QCOM\0" // IR(9715, 23)
  "Float16ImageAMD\0" // IR(9738, 16)
  "ImageGatherBiasLodAMD\0" // IR(9754, 22)
  "FragmentMaskAMD\0" // IR(9776, 16)
  "ImageReadWriteLodAMD\0" // IR(9792, 21)
  "Int64ImageEXT\0" // IR(9813, 14)
  "ShaderClockKHR\0" // IR(9827, 15)
  "QuadControlKHR\0" // IR(9842, 15)
  "Int4TypeINTEL\0" // IR(9857, 14)
  "Int4CooperativeMatrixINTEL\0" // IR(9871, 27)
  "CooperativeMatrixKHR\0" // IR(9898, 21)
  "BFloat16TypeKHR\0" // IR(9919, 16)
  "BFloat16DotProductKHR\0" // IR(9935, 22)
  "BFloat16CooperativeMatrixKHR\0" // IR(9957, 29)
  "SampleMaskOverrideCoverageNV\0" // IR(9986, 29)
  "GeometryShaderPassthroughNV\0" // IR(10015, 28)
  "ShaderViewportIndexLayerNV\0" // IR(10043, 27)
  "ImageFootprintNV\0" // IR(10070, 17)
  "FragmentBarycentricNV\0" // IR(10087, 22)
  "ComputeDerivativeGroupQuadsKHR\0" // IR(10109, 31)
  "ComputeDerivativeGroupQuadsNV\0" // IR(10140, 30)
  "ShadingRateNV\0" // IR(10170, 14)
  "GroupNonUniformPartitionedNV\0" // IR(10184, 29)
  "ShaderNonUniform\0" // IR(10213, 17)
  "ShaderNonUniformEXT\0" // IR(10230, 20)
  "RuntimeDescriptorArray\0" // IR(10250, 23)
  "RuntimeDescriptorArrayEXT\0" // IR(10273, 26)
  "InputAttachmentArrayDynamicIndexing\0" // IR(10299, 36)
  "InputAttachmentArrayDynamicIndexingEXT\0" // IR(10335, 39)
  "UniformTexelBufferArrayDynamicIndexing\0" // IR(10374, 39)
  "UniformTexelBufferArrayDynamicIndexingEXT\0" // IR(10413, 42)
  "StorageTexelBufferArrayDynamicIndexing\0" // IR(10455, 39)
  "StorageTexelBufferArrayDynamicIndexingEXT\0" // IR(10494, 42)
  "UniformBufferArrayNonUniformIndexing\0" // IR(10536, 37)
  "UniformBufferArrayNonUniformIndexingEXT\0" // IR(10573, 40)
  "SampledImageArrayNonUniformIndexing\0" // IR(10613, 36)
  "SampledImageArrayNonUniformIndexingEXT\0" // IR(10649, 39)
  "StorageBufferArrayNonUniformIndexing\0" // IR(10688, 37)
  "StorageBufferArrayNonUniformIndexingEXT\0" // IR(10725, 40)
  "StorageImageArrayNonUniformIndexing\0" // IR(10765, 36)
  "StorageImageArrayNonUniformIndexingEXT\0" // IR(10801, 39)
  "InputAttachmentArrayNonUniformIndexing\0" // IR(10840, 39)
  "InputAttachmentArrayNonUniformIndexingEXT\0" // IR(10879, 42)
  "UniformTexelBufferArrayNonUniformIndexing\0" // IR(10921, 42)
  "UniformTexelBufferArrayNonUniformIndexingEXT\0" // IR(10963, 45)
  "StorageTexelBufferArrayNonUniformIndexing\0" // IR(11008, 42)
  "StorageTexelBufferArrayNonUniformIndexingEXT\0" // IR(11050, 45)
  "VulkanMemoryModel\0" // IR(11095, 18)
  "VulkanMemoryModelKHR\0" // IR(11113, 21)
  "VulkanMemoryModelDeviceScope\0" // IR(11134, 29)
  "VulkanMemoryModelDeviceScopeKHR\0" // IR(11163, 32)
  "PhysicalStorageBufferAddressesEXT\0" // IR(11195, 34)
  "ComputeDerivativeGroupLinearKHR\0" // IR(11229, 32)
  "ComputeDerivativeGroupLinearNV\0" // IR(11261, 31)
  "RayTracingProvisionalKHR\0" // IR(11292, 25)
  "CooperativeMatrixNV\0" // IR(11317, 20)
  "FragmentShaderSampleInterlockEXT\0" // IR(11337, 33)
  "FragmentShaderShadingRateInterlockEXT\0" // IR(11370, 38)
  "FragmentShaderPixelInterlockEXT\0" // IR(11408, 32)
  "DemoteToHelperInvocation\0" // IR(11440, 25)
  "DemoteToHelperInvocationEXT\0" // IR(11465, 28)
  "DisplacementMicromapNV\0" // IR(11493, 23)
  "RayTracingOpacityMicromapEXT\0" // IR(11516, 29)
  "ShaderInvocationReorderNV\0" // IR(11545, 26)
  "BindlessTextureNV\0" // IR(11571, 18)
  "RayQueryPositionFetchKHR\0" // IR(11589, 25)
  "CooperativeVectorNV\0" // IR(11614, 20)
  "AtomicFloat16VectorNV\0" // IR(11634, 22)
  "RawAccessChainsNV\0" // IR(11656, 18)
  "CooperativeMatrixReductionsNV\0" // IR(11674, 30)
  "CooperativeMatrixConversionsNV\0" // IR(11704, 31)
  "CooperativeMatrixPerElementOperationsNV\0" // IR(11735, 40)
  "CooperativeMatrixTensorAddressingNV\0" // IR(11775, 36)
  "CooperativeMatrixBlockLoadsNV\0" // IR(11811, 30)
  "CooperativeVectorTrainingNV\0" // IR(11841, 28)
  "TensorAddressingNV\0" // IR(11869, 19)
  "SubgroupShuffleINTEL\0" // IR(11888, 21)
  "SubgroupBufferBlockIOINTEL\0" // IR(11909, 27)
  "SubgroupImageBlockIOINTEL\0" // IR(11936, 26)
  "SubgroupImageMediaBlockIOINTEL\0" // IR(11962, 31)
  "RoundToInfinityINTEL\0" // IR(11993, 21)
  "FloatingPointModeINTEL\0" // IR(12014, 23)
  "IntegerFunctions2INTEL\0" // IR(12037, 23)
  "FunctionPointersINTEL\0" // IR(12060, 22)
  "IndirectReferencesINTEL\0" // IR(12082, 24)
  "AsmINTEL\0" // IR(12106, 9)
  "AtomicFloat32MinMaxEXT\0" // IR(12115, 23)
  "AtomicFloat64MinMaxEXT\0" // IR(12138, 23)
  "AtomicFloat16MinMaxEXT\0" // IR(12161, 23)
  "VectorComputeINTEL\0" // IR(12184, 19)
  "VectorAnyINTEL\0" // IR(12203, 15)
  "ExpectAssumeKHR\0" // IR(12218, 16)
  "SubgroupAvcMotionEstimationINTEL\0" // IR(12234, 33)
  "SubgroupAvcMotionEstimationIntraINTEL\0" // IR(12267, 38)
  "SubgroupAvcMotionEstimationChromaINTEL\0" // IR(12305, 39)
  "VariableLengthArrayINTEL\0" // IR(12344, 25)
  "FunctionFloatControlINTEL\0" // IR(12369, 26)
  "FPGAMemoryAttributesINTEL\0" // IR(12395, 26)
  "FPFastMathModeINTEL\0" // IR(12421, 20)
  "ArbitraryPrecisionIntegersINTEL\0" // IR(12441, 32)
  "ArbitraryPrecisionFloatingPointINTEL\0" // IR(12473, 37)
  "UnstructuredLoopControlsINTEL\0" // IR(12510, 30)
  "FPGALoopControlsINTEL\0" // IR(12540, 22)
  "KernelAttributesINTEL\0" // IR(12562, 22)
  "FPGAKernelAttributesINTEL\0" // IR(12584, 26)
  "FPGAMemoryAccessesINTEL\0" // IR(12610, 24)
  "FPGAClusterAttributesINTEL\0" // IR(12634, 27)
  "LoopFuseINTEL\0" // IR(12661, 14)
  "FPGADSPControlINTEL\0" // IR(12675, 20)
  "MemoryAccessAliasingINTEL\0" // IR(12695, 26)
  "FPGAInvocationPipeliningAttributesINTEL\0" // IR(12721, 40)
  "FPGABufferLocationINTEL\0" // IR(12761, 24)
  "ArbitraryPrecisionFixedPointINTEL\0" // IR(12785, 34)
  "USMStorageClassesINTEL\0" // IR(12819, 23)
  "RuntimeAlignedAttributeINTEL\0" // IR(12842, 29)
  "IOPipesINTEL\0" // IR(12871, 13)
  "BlockingPipesINTEL\0" // IR(12884, 19)
  "FPGARegINTEL\0" // IR(12903, 13)
  "DotProductInputAll\0" // IR(12916, 19)
  "DotProductInputAllKHR\0" // IR(12935, 22)
  "DotProductInput4x8Bit\0" // IR(12957, 22)
  "DotProductInput4x8BitKHR\0" // IR(12979, 25)
  "DotProductInput4x8BitPacked\0" // IR(13004, 28)
  "DotProductInput4x8BitPackedKHR\0" // IR(13032, 31)
  "DotProduct\0" // IR(13063, 11)
  "DotProductKHR\0" // IR(13074, 14)
  "ReplicatedCompositesEXT\0" // IR(13088, 24)
  "BitInstructions\0" // IR(13112, 16)
  "GroupNonUniformRotateKHR\0" // IR(13128, 25)
  "FloatControls2\0" // IR(13153, 15)
  "AtomicFloat32AddEXT\0" // IR(13168, 20)
  "AtomicFloat64AddEXT\0" // IR(13188, 20)
  "LongCompositesINTEL\0" // IR(13208, 20)
  "OptNoneEXT\0" // IR(13228, 11)
  "OptNoneINTEL\0" // IR(13239, 13)
  "AtomicFloat16AddEXT\0" // IR(13252, 20)
  "DebugInfoModuleINTEL\0" // IR(13272, 21)
  "BFloat16ConversionINTEL\0" // IR(13293, 24)
  "SplitBarrierINTEL\0" // IR(13317, 18)
  "ArithmeticFenceEXT\0" // IR(13335, 19)
  "FPGAClusterAttributesV2INTEL\0" // IR(13354, 29)
  "FPGAKernelAttributesv2INTEL\0" // IR(13383, 28)
  "TaskSequenceINTEL\0" // IR(13411, 18)
  "FPMaxErrorINTEL\0" // IR(13429, 16)
  "FPGALatencyControlINTEL\0" // IR(13445, 24)
  "FPGAArgumentInterfacesINTEL\0" // IR(13469, 28)
  "GlobalVariableHostAccessINTEL\0" // IR(13497, 30)
  "GlobalVariableFPGADecorationsINTEL\0" // IR(13527, 35)
  "SubgroupBufferPrefetchINTEL\0" // IR(13562, 28)
  "Subgroup2DBlockIOINTEL\0" // IR(13590, 23)
  "Subgroup2DBlockTransformINTEL\0" // IR(13613, 30)
  "Subgroup2DBlockTransposeINTEL\0" // IR(13643, 30)
  "SubgroupMatrixMultiplyAccumulateINTEL\0" // IR(13673, 38)
  "TernaryBitwiseFunctionINTEL\0" // IR(13711, 28)
  "GroupUniformArithmeticKHR\0" // IR(13739, 26)
  "TensorFloat32RoundingINTEL\0" // IR(13765, 27)
  "MaskedGatherScatterINTEL\0" // IR(13792, 25)
  "CacheControlsINTEL\0" // IR(13817, 19)
  "RegisterLimitsINTEL\0" // IR(13836, 20)
  "BindlessImagesINTEL\0" // IR(13856, 20)
  "Unspecified\0" // IR(13876, 12)
  "Address\0" // IR(13888, 8)
  "Boolean\0" // IR(13896, 8)
  "Float\0" // IR(13904, 6)
  "Signed\0" // IR(13910, 7)
  "SignedChar\0" // IR(13917, 11)
  "Unsigned\0" // IR(13928, 9)
  "UnsignedChar\0" // IR(13937, 13)
  "Class\0" // IR(13950, 6)
  "Structure\0" // IR(13956, 10)
  "Union\0" // IR(13966, 6)
  "ImportedModule\0" // IR(13972, 15)
  "ImportedDeclaration\0" // IR(13987, 20)
  "None\0" // IR(14007, 5)
  "FlagIsProtected\0" // IR(14012, 16)
  "FlagIsPrivate\0" // IR(14028, 14)
  "FlagIsPublic\0" // IR(14042, 13)
  "FlagIsLocal\0" // IR(14055, 12)
  "FlagIsDefinition\0" // IR(14067, 17)
  "FlagFwdDecl\0" // IR(14084, 12)
  "FlagArtificial\0" // IR(14096, 15)
  "FlagExplicit\0" // IR(14111, 13)
  "FlagPrototyped\0" // IR(14124, 15)
  "FlagObjectPointer\0" // IR(14139, 18)
  "FlagStaticMember\0" // IR(14157, 17)
  "FlagIndirectVariable\0" // IR(14174, 21)
  "FlagLValueReference\0" // IR(14195, 20)
  "FlagRValueReference\0" // IR(14215, 20)
  "FlagIsOptimized\0" // IR(14235, 16)
  "FlagIsEnumClass\0" // IR(14251, 16)
  "FlagTypePassByValue\0" // IR(14267, 20)
  "FlagTypePassByReference\0" // IR(14287, 24)
  "Deref\0" // IR(14311, 6)
  "Plus\0" // IR(14317, 5)
  "Minus\0" // IR(14322, 6)
  "SPV_OPERAND_TYPE_LITERAL_INTEGER\0" // IR(14328, 33)
  "PlusUconst\0" // IR(14361, 11)
  "BitPiece\0" // IR(14372, 9)
  "Swap\0" // IR(14381, 5)
  "Xderef\0" // IR(14386, 7)
  "StackValue\0" // IR(14393, 11)
  "Constu\0" // IR(14404, 7)
  "Fragment\0" // IR(14411, 9)
  "ConstType\0" // IR(14420, 10)
  "VolatileType\0" // IR(14430, 13)
  "RestrictType\0" // IR(14443, 13)
  "AtomicType\0" // IR(14456, 11)
  "Float16NV\0" // IR(14467, 10)
  "Float32NV\0" // IR(14477, 10)
  "Float64NV\0" // IR(14487, 10)
  "SignedInt8NV\0" // IR(14497, 13)
  "SignedInt16NV\0" // IR(14510, 14)
  "SignedInt32NV\0" // IR(14524, 14)
  "SignedInt64NV\0" // IR(14538, 14)
  "UnsignedInt8NV\0" // IR(14552, 15)
  "UnsignedInt16NV\0" // IR(14567, 16)
  "UnsignedInt32NV\0" // IR(14583, 16)
  "UnsignedInt64NV\0" // IR(14599, 16)
  "SignedInt8PackedNV\0" // IR(14615, 19)
  "UnsignedInt8PackedNV\0" // IR(14634, 21)
  "FloatE4M3NV\0" // IR(14655, 12)
  "FloatE5M2NV\0" // IR(14667, 12)
  "RowMajorKHR\0" // IR(14679, 12)
  "ColumnMajorKHR\0" // IR(14691, 15)
  "RowBlockedInterleavedARM\0" // IR(14706, 25)
  "ColumnBlockedInterleavedARM\0" // IR(14731, 28)
  "NoneKHR\0" // IR(14759, 8)
  "MatrixASignedComponentsKHR\0" // IR(14767, 27)
  "MatrixBSignedComponentsKHR\0" // IR(14794, 27)
  "MatrixCSignedComponentsKHR\0" // IR(14821, 27)
  "MatrixResultSignedComponentsKHR\0" // IR(14848, 32)
  "SaturatingAccumulationKHR\0" // IR(14880, 26)
  "Row\0" // IR(14906, 4)
  "Column\0" // IR(14910, 7)
  "2x2\0" // IR(14917, 4)
  "MatrixAKHR\0" // IR(14921, 11)
  "MatrixBKHR\0" // IR(14932, 11)
  "MatrixAccumulatorKHR\0" // IR(14943, 21)
  "RowMajorNV\0" // IR(14964, 11)
  "ColumnMajorNV\0" // IR(14975, 14)
  "InferencingOptimalNV\0" // IR(14989, 21)
  "TrainingOptimalNV\0" // IR(15010, 18)
  "RelaxedPrecision\0" // IR(15028, 17)
  "SpecId\0" // IR(15045, 7)
  "Block\0" // IR(15052, 6)
  "BufferBlock\0" // IR(15058, 12)
  "RowMajor\0" // IR(15070, 9)
  "ColMajor\0" // IR(15079, 9)
  "ArrayStride\0" // IR(15088, 12)
  "MatrixStride\0" // IR(15100, 13)
  "GLSLShared\0" // IR(15113, 11)
  "GLSLPacked\0" // IR(15124, 11)
  "CPacked\0" // IR(15135, 8)
  "SPV_OPERAND_TYPE_BUILT_IN\0" // IR(15143, 26)
  "BuiltIn\0" // IR(15169, 8)
  "NoPerspective\0" // IR(15177, 14)
  "Flat\0" // IR(15191, 5)
  "Patch\0" // IR(15196, 6)
  "Centroid\0" // IR(15202, 9)
  "Sample\0" // IR(15211, 7)
  "Invariant\0" // IR(15218, 10)
  "Restrict\0" // IR(15228, 9)
  "Aliased\0" // IR(15237, 8)
  "Volatile\0" // IR(15245, 9)
  "Constant\0" // IR(15254, 9)
  "Coherent\0" // IR(15263, 9)
  "NonWritable\0" // IR(15272, 12)
  "NonReadable\0" // IR(15284, 12)
  "Uniform\0" // IR(15296, 8)
  "SPV_OPERAND_TYPE_SCOPE_ID\0" // IR(15304, 26)
  "UniformId\0" // IR(15330, 10)
  "SaturatedConversion\0" // IR(15340, 20)
  "Stream\0" // IR(15360, 7)
  "Location\0" // IR(15367, 9)
  "Component\0" // IR(15376, 10)
  "Index\0" // IR(15386, 6)
  "Binding\0" // IR(15392, 8)
  "DescriptorSet\0" // IR(15400, 14)
  "Offset\0" // IR(15414, 7)
  "XfbBuffer\0" // IR(15421, 10)
  "XfbStride\0" // IR(15431, 10)
  "SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE\0" // IR(15441, 46)
  "FuncParamAttr\0" // IR(15487, 14)
  "SPV_OPERAND_TYPE_FP_ROUNDING_MODE\0" // IR(15501, 34)
  "FPRoundingMode\0" // IR(15535, 15)
  "SPV_OPERAND_TYPE_FP_FAST_MATH_MODE\0" // IR(15550, 35)
  "FPFastMathMode\0" // IR(15585, 15)
  "SPV_OPERAND_TYPE_LITERAL_STRING\0" // IR(15600, 32)
  "SPV_OPERAND_TYPE_LINKAGE_TYPE\0" // IR(15632, 30)
  "LinkageAttributes\0" // IR(15662, 18)
  "NoContraction\0" // IR(15680, 14)
  "InputAttachmentIndex\0" // IR(15694, 21)
  "Alignment\0" // IR(15715, 10)
  "MaxByteOffset\0" // IR(15725, 14)
  "SPV_OPERAND_TYPE_ID\0" // IR(15739, 20)
  "AlignmentId\0" // IR(15759, 12)
  "MaxByteOffsetId\0" // IR(15771, 16)
  "SaturatedToLargestFloat8NormalConversionEXT\0" // IR(15787, 44)
  "NoSignedWrap\0" // IR(15831, 13)
  "NoUnsignedWrap\0" // IR(15844, 15)
  "WeightTextureQCOM\0" // IR(15859, 18)
  "BlockMatchTextureQCOM\0" // IR(15877, 22)
  "BlockMatchSamplerQCOM\0" // IR(15899, 22)
  "ExplicitInterpAMD\0" // IR(15921, 18)
  "NodeSharesPayloadLimitsWithAMDX\0" // IR(15939, 32)
  "NodeMaxPayloadsAMDX\0" // IR(15971, 20)
  "TrackFinishWritingAMDX\0" // IR(15991, 23)
  "PayloadNodeNameAMDX\0" // IR(16014, 20)
  "PayloadNodeBaseIndexAMDX\0" // IR(16034, 25)
  "PayloadNodeSparseArrayAMDX\0" // IR(16059, 27)
  "PayloadNodeArraySizeAMDX\0" // IR(16086, 25)
  "PayloadDispatchIndirectAMDX\0" // IR(16111, 28)
  "OverrideCoverageNV\0" // IR(16139, 19)
  "PassthroughNV\0" // IR(16158, 14)
  "ViewportRelativeNV\0" // IR(16172, 19)
  "SecondaryViewportRelativeNV\0" // IR(16191, 28)
  "PerPrimitiveEXT\0" // IR(16219, 16)
  "PerPrimitiveNV\0" // IR(16235, 15)
  "PerViewNV\0" // IR(16250, 10)
  "PerTaskNV\0" // IR(16260, 10)
  "PerVertexKHR\0" // IR(16270, 13)
  "PerVertexNV\0" // IR(16283, 12)
  "NonUniform\0" // IR(16295, 11)
  "NonUniformEXT\0" // IR(16306, 14)
  "RestrictPointer\0" // IR(16320, 16)
  "RestrictPointerEXT\0" // IR(16336, 19)
  "AliasedPointer\0" // IR(16355, 15)
  "AliasedPointerEXT\0" // IR(16370, 18)
  "HitObjectShaderRecordBufferNV\0" // IR(16388, 30)
  "BindlessSamplerNV\0" // IR(16418, 18)
  "BindlessImageNV\0" // IR(16436, 16)
  "BoundSamplerNV\0" // IR(16452, 15)
  "BoundImageNV\0" // IR(16467, 13)
  "SIMTCallINTEL\0" // IR(16480, 14)
  "ReferencedIndirectlyINTEL\0" // IR(16494, 26)
  "ClobberINTEL\0" // IR(16520, 13)
  "SideEffectsINTEL\0" // IR(16533, 17)
  "VectorComputeVariableINTEL\0" // IR(16550, 27)
  "FuncParamIOKindINTEL\0" // IR(16577, 21)
  "VectorComputeFunctionINTEL\0" // IR(16598, 27)
  "StackCallINTEL\0" // IR(16625, 15)
  "GlobalVariableOffsetINTEL\0" // IR(16640, 26)
  "CounterBuffer\0" // IR(16666, 14)
  "HlslCounterBufferGOOGLE\0" // IR(16680, 24)
  "UserSemantic\0" // IR(16704, 13)
  "HlslSemanticGOOGLE\0" // IR(16717, 19)
  "UserTypeGOOGLE\0" // IR(16736, 15)
  "FunctionRoundingModeINTEL\0" // IR(16751, 26)
  "SPV_OPERAND_TYPE_FPDENORM_MODE\0" // IR(16777, 31)
  "FunctionDenormModeINTEL\0" // IR(16808, 24)
  "RegisterINTEL\0" // IR(16832, 14)
  "MemoryINTEL\0" // IR(16846, 12)
  "NumbanksINTEL\0" // IR(16858, 14)
  "BankwidthINTEL\0" // IR(16872, 15)
  "MaxPrivateCopiesINTEL\0" // IR(16887, 22)
  "SinglepumpINTEL\0" // IR(16909, 16)
  "DoublepumpINTEL\0" // IR(16925, 16)
  "MaxReplicatesINTEL\0" // IR(16941, 19)
  "SimpleDualPortINTEL\0" // IR(16960, 20)
  "MergeINTEL\0" // IR(16980, 11)
  "SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER\0" // IR(16991, 42)
  "BankBitsINTEL\0" // IR(17033, 14)
  "ForcePow2DepthINTEL\0" // IR(17047, 20)
  "StridesizeINTEL\0" // IR(17067, 16)
  "WordsizeINTEL\0" // IR(17083, 14)
  "TrueDualPortINTEL\0" // IR(17097, 18)
  "BurstCoalesceINTEL\0" // IR(17115, 19)
  "CacheSizeINTEL\0" // IR(17134, 15)
  "DontStaticallyCoalesceINTEL\0" // IR(17149, 28)
  "PrefetchINTEL\0" // IR(17177, 14)
  "StallEnableINTEL\0" // IR(17191, 17)
  "FuseLoopsInFunctionINTEL\0" // IR(17208, 25)
  "MathOpDSPModeINTEL\0" // IR(17233, 19)
  "AliasScopeINTEL\0" // IR(17252, 16)
  "NoAliasINTEL\0" // IR(17268, 13)
  "InitiationIntervalINTEL\0" // IR(17281, 24)
  "MaxConcurrencyINTEL\0" // IR(17305, 20)
  "PipelineEnableINTEL\0" // IR(17325, 20)
  "BufferLocationINTEL\0" // IR(17345, 20)
  "IOPipeStorageINTEL\0" // IR(17365, 19)
  "SPV_OPERAND_TYPE_FPOPERATION_MODE\0" // IR(17384, 34)
  "FunctionFloatingPointModeINTEL\0" // IR(17418, 31)
  "SingleElementVectorINTEL\0" // IR(17449, 25)
  "VectorComputeCallableFunctionINTEL\0" // IR(17474, 35)
  "MediaBlockIOINTEL\0" // IR(17509, 18)
  "StallFreeINTEL\0" // IR(17527, 15)
  "SPV_OPERAND_TYPE_LITERAL_FLOAT\0" // IR(17542, 31)
  "FPMaxErrorDecorationINTEL\0" // IR(17573, 26)
  "LatencyControlLabelINTEL\0" // IR(17599, 25)
  "LatencyControlConstraintINTEL\0" // IR(17624, 30)
  "ConduitKernelArgumentINTEL\0" // IR(17654, 27)
  "RegisterMapKernelArgumentINTEL\0" // IR(17681, 31)
  "MMHostInterfaceAddressWidthINTEL\0" // IR(17712, 33)
  "MMHostInterfaceDataWidthINTEL\0" // IR(17745, 30)
  "MMHostInterfaceLatencyINTEL\0" // IR(17775, 28)
  "SPV_OPERAND_TYPE_ACCESS_QUALIFIER\0" // IR(17803, 34)
  "MMHostInterfaceReadWriteModeINTEL\0" // IR(17837, 34)
  "MMHostInterfaceMaxBurstINTEL\0" // IR(17871, 29)
  "MMHostInterfaceWaitRequestINTEL\0" // IR(17900, 32)
  "StableKernelArgumentINTEL\0" // IR(17932, 26)
  "SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER\0" // IR(17958, 39)
  "HostAccessINTEL\0" // IR(17997, 16)
  "SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER\0" // IR(18013, 47)
  "InitModeINTEL\0" // IR(18060, 14)
  "ImplementInRegisterMapINTEL\0" // IR(18074, 28)
  "SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL\0" // IR(18102, 36)
  "CacheControlLoadINTEL\0" // IR(18138, 22)
  "SPV_OPERAND_TYPE_STORE_CACHE_CONTROL\0" // IR(18160, 37)
  "CacheControlStoreINTEL\0" // IR(18197, 23)
  "1D\0" // IR(18220, 3)
  "2D\0" // IR(18223, 3)
  "3D\0" // IR(18226, 3)
  "Cube\0" // IR(18229, 5)
  "Rect\0" // IR(18234, 5)
  "Buffer\0" // IR(18239, 7)
  "SubpassData\0" // IR(18246, 12)
  "TileImageDataEXT\0" // IR(18258, 17)
  "Invocations\0" // IR(18275, 12)
  "SpacingEqual\0" // IR(18287, 13)
  "SpacingFractionalEven\0" // IR(18300, 22)
  "SpacingFractionalOdd\0" // IR(18322, 21)
  "VertexOrderCw\0" // IR(18343, 14)
  "VertexOrderCcw\0" // IR(18357, 15)
  "PixelCenterInteger\0" // IR(18372, 19)
  "OriginUpperLeft\0" // IR(18391, 16)
  "OriginLowerLeft\0" // IR(18407, 16)
  "EarlyFragmentTests\0" // IR(18423, 19)
  "PointMode\0" // IR(18442, 10)
  "Xfb\0" // IR(18452, 4)
  "DepthReplacing\0" // IR(18456, 15)
  "DepthGreater\0" // IR(18471, 13)
  "DepthLess\0" // IR(18484, 10)
  "DepthUnchanged\0" // IR(18494, 15)
  "LocalSize\0" // IR(18509, 10)
  "LocalSizeHint\0" // IR(18519, 14)
  "InputPoints\0" // IR(18533, 12)
  "InputLines\0" // IR(18545, 11)
  "InputLinesAdjacency\0" // IR(18556, 20)
  "Triangles\0" // IR(18576, 10)
  "InputTrianglesAdjacency\0" // IR(18586, 24)
  "Quads\0" // IR(18610, 6)
  "Isolines\0" // IR(18616, 9)
  "OutputVertices\0" // IR(18625, 15)
  "OutputPoints\0" // IR(18640, 13)
  "OutputLineStrip\0" // IR(18653, 16)
  "OutputTriangleStrip\0" // IR(18669, 20)
  "VecTypeHint\0" // IR(18689, 12)
  "ContractionOff\0" // IR(18701, 15)
  "Initializer\0" // IR(18716, 12)
  "Finalizer\0" // IR(18728, 10)
  "SubgroupsPerWorkgroup\0" // IR(18738, 22)
  "SubgroupsPerWorkgroupId\0" // IR(18760, 24)
  "LocalSizeId\0" // IR(18784, 12)
  "LocalSizeHintId\0" // IR(18796, 16)
  "NonCoherentColorAttachmentReadEXT\0" // IR(18812, 34)
  "NonCoherentDepthAttachmentReadEXT\0" // IR(18846, 34)
  "NonCoherentStencilAttachmentReadEXT\0" // IR(18880, 36)
  "SubgroupUniformControlFlowKHR\0" // IR(18916, 30)
  "PostDepthCoverage\0" // IR(18946, 18)
  "NonCoherentTileAttachmentReadQCOM\0" // IR(18964, 34)
  "TileShadingRateQCOM\0" // IR(18998, 20)
  "EarlyAndLateFragmentTestsAMD\0" // IR(19018, 29)
  "StencilRefReplacingEXT\0" // IR(19047, 23)
  "CoalescingAMDX\0" // IR(19070, 15)
  "IsApiEntryAMDX\0" // IR(19085, 15)
  "MaxNodeRecursionAMDX\0" // IR(19100, 21)
  "StaticNumWorkgroupsAMDX\0" // IR(19121, 24)
  "MaxNumWorkgroupsAMDX\0" // IR(19145, 21)
  "StencilRefUnchangedFrontAMD\0" // IR(19166, 28)
  "StencilRefGreaterFrontAMD\0" // IR(19194, 26)
  "StencilRefLessFrontAMD\0" // IR(19220, 23)
  "StencilRefUnchangedBackAMD\0" // IR(19243, 27)
  "StencilRefGreaterBackAMD\0" // IR(19270, 25)
  "StencilRefLessBackAMD\0" // IR(19295, 22)
  "QuadDerivativesKHR\0" // IR(19317, 19)
  "RequireFullQuadsKHR\0" // IR(19336, 20)
  "SharesInputWithAMDX\0" // IR(19356, 20)
  "OutputLinesEXT\0" // IR(19376, 15)
  "OutputLinesNV\0" // IR(19391, 14)
  "OutputPrimitivesEXT\0" // IR(19405, 20)
  "OutputPrimitivesNV\0" // IR(19425, 19)
  "DerivativeGroupQuadsKHR\0" // IR(19444, 24)
  "DerivativeGroupQuadsNV\0" // IR(19468, 23)
  "DerivativeGroupLinearKHR\0" // IR(19491, 25)
  "DerivativeGroupLinearNV\0" // IR(19516, 24)
  "OutputTrianglesEXT\0" // IR(19540, 19)
  "OutputTrianglesNV\0" // IR(19559, 18)
  "PixelInterlockOrderedEXT\0" // IR(19577, 25)
  "PixelInterlockUnorderedEXT\0" // IR(19602, 27)
  "SampleInterlockOrderedEXT\0" // IR(19629, 26)
  "SampleInterlockUnorderedEXT\0" // IR(19655, 28)
  "ShadingRateInterlockOrderedEXT\0" // IR(19683, 31)
  "ShadingRateInterlockUnorderedEXT\0" // IR(19714, 33)
  "SharedLocalMemorySizeINTEL\0" // IR(19747, 27)
  "RoundingModeRTPINTEL\0" // IR(19774, 21)
  "RoundingModeRTNINTEL\0" // IR(19795, 21)
  "FloatingPointModeALTINTEL\0" // IR(19816, 26)
  "FloatingPointModeIEEEINTEL\0" // IR(19842, 27)
  "MaxWorkgroupSizeINTEL\0" // IR(19869, 22)
  "MaxWorkDimINTEL\0" // IR(19891, 16)
  "NoGlobalOffsetINTEL\0" // IR(19907, 20)
  "NumSIMDWorkitemsINTEL\0" // IR(19927, 22)
  "SchedulerTargetFmaxMhzINTEL\0" // IR(19949, 28)
  "MaximallyReconvergesKHR\0" // IR(19977, 24)
  "FPFastMathDefault\0" // IR(20001, 18)
  "StreamingInterfaceINTEL\0" // IR(20019, 24)
  "RegisterMapInterfaceINTEL\0" // IR(20043, 26)
  "NamedBarrierCountINTEL\0" // IR(20069, 23)
  "MaximumRegistersINTEL\0" // IR(20092, 22)
  "MaximumRegistersIdINTEL\0" // IR(20114, 24)
  "SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS\0" // IR(20138, 51)
  "NamedMaximumRegistersINTEL\0" // IR(20189, 27)
  "Vertex\0" // IR(20216, 7)
  "TessellationControl\0" // IR(20223, 20)
  "TessellationEvaluation\0" // IR(20243, 23)
  "GLCompute\0" // IR(20266, 10)
  "TaskNV\0" // IR(20276, 7)
  "MeshNV\0" // IR(20283, 7)
  "RayGenerationKHR\0" // IR(20290, 17)
  "RayGenerationNV\0" // IR(20307, 16)
  "IntersectionKHR\0" // IR(20323, 16)
  "IntersectionNV\0" // IR(20339, 15)
  "AnyHitKHR\0" // IR(20354, 10)
  "AnyHitNV\0" // IR(20364, 9)
  "ClosestHitKHR\0" // IR(20373, 14)
  "ClosestHitNV\0" // IR(20387, 13)
  "MissKHR\0" // IR(20400, 8)
  "MissNV\0" // IR(20408, 7)
  "CallableKHR\0" // IR(20415, 12)
  "CallableNV\0" // IR(20427, 11)
  "TaskEXT\0" // IR(20438, 8)
  "MeshEXT\0" // IR(20446, 8)
  "Preserve\0" // IR(20454, 9)
  "FlushToZero\0" // IR(20463, 12)
  "BFloat16KHR\0" // IR(20475, 12)
  "Float8E4M3EXT\0" // IR(20487, 14)
  "Float8E5M2EXT\0" // IR(20501, 14)
  "IEEE\0" // IR(20515, 5)
  "ALT\0" // IR(20520, 4)
  "NotNaN\0" // IR(20524, 7)
  "NotInf\0" // IR(20531, 7)
  "NSZ\0" // IR(20538, 4)
  "AllowRecip\0" // IR(20542, 11)
  "Fast\0" // IR(20553, 5)
  "AllowContract\0" // IR(20558, 14)
  "AllowContractFastINTEL\0" // IR(20572, 23)
  "AllowReassoc\0" // IR(20595, 13)
  "AllowReassocINTEL\0" // IR(20608, 18)
  "AllowTransform\0" // IR(20626, 15)
  "RTE\0" // IR(20641, 4)
  "RTZ\0" // IR(20645, 4)
  "RTP\0" // IR(20649, 4)
  "RTN\0" // IR(20653, 4)
  "Vertical2Pixels\0" // IR(20657, 16)
  "Vertical4Pixels\0" // IR(20673, 16)
  "Horizontal2Pixels\0" // IR(20689, 18)
  "Horizontal4Pixels\0" // IR(20707, 18)
  "Inline\0" // IR(20725, 7)
  "DontInline\0" // IR(20732, 11)
  "Pure\0" // IR(20743, 5)
  "Const\0" // IR(20748, 6)
  "Zext\0" // IR(20754, 5)
  "Sext\0" // IR(20759, 5)
  "ByVal\0" // IR(20764, 6)
  "Sret\0" // IR(20770, 5)
  "NoAlias\0" // IR(20775, 8)
  "NoCapture\0" // IR(20783, 10)
  "NoWrite\0" // IR(20793, 8)
  "NoReadWrite\0" // IR(20801, 12)
  "RuntimeAlignedINTEL\0" // IR(20813, 20)
  "Reduce\0" // IR(20833, 7)
  "InclusiveScan\0" // IR(20840, 14)
  "ExclusiveScan\0" // IR(20854, 14)
  "ClusteredReduce\0" // IR(20868, 16)
  "PartitionedReduceNV\0" // IR(20884, 20)
  "PartitionedInclusiveScanNV\0" // IR(20904, 27)
  "PartitionedExclusiveScanNV\0" // IR(20931, 27)
  "NoneINTEL\0" // IR(20958, 10)
  "ReadINTEL\0" // IR(20968, 10)
  "WriteINTEL\0" // IR(20978, 11)
  "ReadWriteINTEL\0" // IR(20989, 15)
  "Bias\0" // IR(21004, 5)
  "Lod\0" // IR(21009, 4)
  "Grad\0" // IR(21013, 5)
  "ConstOffset\0" // IR(21018, 12)
  "ConstOffsets\0" // IR(21030, 13)
  "MakeTexelAvailable\0" // IR(21043, 19)
  "MakeTexelAvailableKHR\0" // IR(21062, 22)
  "MakeTexelVisible\0" // IR(21084, 17)
  "MakeTexelVisibleKHR\0" // IR(21101, 20)
  "NonPrivateTexel\0" // IR(21121, 16)
  "NonPrivateTexelKHR\0" // IR(21137, 19)
  "VolatileTexel\0" // IR(21156, 14)
  "VolatileTexelKHR\0" // IR(21170, 17)
  "SignExtend\0" // IR(21187, 11)
  "ZeroExtend\0" // IR(21198, 11)
  "Nontemporal\0" // IR(21209, 12)
  "Offsets\0" // IR(21221, 8)
  "SnormInt8\0" // IR(21229, 10)
  "SnormInt16\0" // IR(21239, 11)
  "UnormInt8\0" // IR(21250, 10)
  "UnormInt16\0" // IR(21260, 11)
  "UnormShort565\0" // IR(21271, 14)
  "UnormShort555\0" // IR(21285, 14)
  "UnormInt101010\0" // IR(21299, 15)
  "SignedInt8\0" // IR(21314, 11)
  "SignedInt16\0" // IR(21325, 12)
  "SignedInt32\0" // IR(21337, 12)
  "UnsignedInt8\0" // IR(21349, 13)
  "UnsignedInt16\0" // IR(21362, 14)
  "UnsignedInt32\0" // IR(21376, 14)
  "HalfFloat\0" // IR(21390, 10)
  "UnormInt24\0" // IR(21400, 11)
  "UnormInt101010_2\0" // IR(21411, 17)
  "UnormInt10X6EXT\0" // IR(21428, 16)
  "UnsignedIntRaw10EXT\0" // IR(21444, 20)
  "UnsignedIntRaw12EXT\0" // IR(21464, 20)
  "UnormInt2_101010EXT\0" // IR(21484, 20)
  "UnsignedInt10X6EXT\0" // IR(21504, 19)
  "UnsignedInt12X4EXT\0" // IR(21523, 19)
  "UnsignedInt14X2EXT\0" // IR(21542, 19)
  "UnormInt12X4EXT\0" // IR(21561, 16)
  "UnormInt14X2EXT\0" // IR(21577, 16)
  "R\0" // IR(21593, 2)
  "A\0" // IR(21595, 2)
  "RG\0" // IR(21597, 3)
  "RA\0" // IR(21600, 3)
  "RGB\0" // IR(21603, 4)
  "RGBA\0" // IR(21607, 5)
  "BGRA\0" // IR(21612, 5)
  "ARGB\0" // IR(21617, 5)
  "Intensity\0" // IR(21622, 10)
  "Luminance\0" // IR(21632, 10)
  "Rx\0" // IR(21642, 3)
  "RGx\0" // IR(21645, 4)
  "RGBx\0" // IR(21649, 5)
  "Depth\0" // IR(21654, 6)
  "DepthStencil\0" // IR(21660, 13)
  "sRGB\0" // IR(21673, 5)
  "sRGBx\0" // IR(21678, 6)
  "sRGBA\0" // IR(21684, 6)
  "sBGRA\0" // IR(21690, 6)
  "ABGR\0" // IR(21696, 5)
  "InitOnDeviceReprogramINTEL\0" // IR(21701, 27)
  "InitOnDeviceResetINTEL\0" // IR(21728, 23)
  "NoWait\0" // IR(21751, 7)
  "WaitKernel\0" // IR(21758, 11)
  "WaitWorkGroup\0" // IR(21769, 14)
  "CmdExecTime\0" // IR(21783, 12)
  "MayUsePrintf\0" // IR(21795, 13)
  "Export\0" // IR(21808, 7)
  "Import\0" // IR(21815, 7)
  "LinkOnceODR\0" // IR(21822, 12)
  "UncachedINTEL\0" // IR(21834, 14)
  "CachedINTEL\0" // IR(21848, 12)
  "StreamingINTEL\0" // IR(21860, 15)
  "InvalidateAfterReadINTEL\0" // IR(21875, 25)
  "ConstCachedINTEL\0" // IR(21900, 17)
  "Unroll\0" // IR(21917, 7)
  "DontUnroll\0" // IR(21924, 11)
  "DependencyInfinite\0" // IR(21935, 19)
  "DependencyLength\0" // IR(21954, 17)
  "MinIterations\0" // IR(21971, 14)
  "MaxIterations\0" // IR(21985, 14)
  "IterationMultiple\0" // IR(21999, 18)
  "PeelCount\0" // IR(22017, 10)
  "PartialCount\0" // IR(22027, 13)
  "DependencyArrayINTEL\0" // IR(22040, 21)
  "LoopCoalesceINTEL\0" // IR(22061, 18)
  "MaxInterleavingINTEL\0" // IR(22079, 21)
  "SpeculatedIterationsINTEL\0" // IR(22100, 26)
  "NoFusionINTEL\0" // IR(22126, 14)
  "LoopCountINTEL\0" // IR(22140, 15)
  "MaxReinvocationDelayINTEL\0" // IR(22155, 26)
  "MatrixASignedComponentsINTEL\0" // IR(22181, 29)
  "MatrixBSignedComponentsINTEL\0" // IR(22210, 29)
  "MatrixCBFloat16INTEL\0" // IR(22239, 21)
  "MatrixResultBFloat16INTEL\0" // IR(22260, 26)
  "MatrixAPackedInt8INTEL\0" // IR(22286, 23)
  "MatrixBPackedInt8INTEL\0" // IR(22309, 23)
  "MatrixAPackedInt4INTEL\0" // IR(22332, 23)
  "MatrixBPackedInt4INTEL\0" // IR(22355, 23)
  "MatrixATF32INTEL\0" // IR(22378, 17)
  "MatrixBTF32INTEL\0" // IR(22395, 17)
  "MatrixAPackedFloat16INTEL\0" // IR(22412, 26)
  "MatrixBPackedFloat16INTEL\0" // IR(22438, 26)
  "MatrixAPackedBFloat16INTEL\0" // IR(22464, 27)
  "MatrixBPackedBFloat16INTEL\0" // IR(22491, 27)
  "Aligned\0" // IR(22518, 8)
  "MakePointerAvailable\0" // IR(22526, 21)
  "MakePointerAvailableKHR\0" // IR(22547, 24)
  "MakePointerVisible\0" // IR(22571, 19)
  "MakePointerVisibleKHR\0" // IR(22590, 22)
  "NonPrivatePointer\0" // IR(22612, 18)
  "NonPrivatePointerKHR\0" // IR(22630, 21)
  "AliasScopeINTELMask\0" // IR(22651, 20)
  "NoAliasINTELMask\0" // IR(22671, 17)
  "Simple\0" // IR(22688, 7)
  "GLSL450\0" // IR(22695, 8)
  "OpenCL\0" // IR(22703, 7)
  "Vulkan\0" // IR(22710, 7)
  "VulkanKHR\0" // IR(22717, 10)
  "Relaxed\0" // IR(22727, 8)
  "Acquire\0" // IR(22735, 8)
  "Release\0" // IR(22743, 8)
  "AcquireRelease\0" // IR(22751, 15)
  "SequentiallyConsistent\0" // IR(22766, 23)
  "UniformMemory\0" // IR(22789, 14)
  "SubgroupMemory\0" // IR(22803, 15)
  "WorkgroupMemory\0" // IR(22818, 16)
  "CrossWorkgroupMemory\0" // IR(22834, 21)
  "AtomicCounterMemory\0" // IR(22855, 20)
  "ImageMemory\0" // IR(22875, 12)
  "OutputMemory\0" // IR(22887, 13)
  "OutputMemoryKHR\0" // IR(22900, 16)
  "MakeAvailable\0" // IR(22916, 14)
  "MakeAvailableKHR\0" // IR(22930, 17)
  "MakeVisible\0" // IR(22947, 12)
  "MakeVisibleKHR\0" // IR(22959, 15)
  "AutoINTEL\0" // IR(22974, 10)
  "WRAP\0" // IR(22984, 5)
  "SAT\0" // IR(22989, 4)
  "SAT_ZERO\0" // IR(22993, 9)
  "SAT_SYM\0" // IR(23002, 8)
  "PackedVectorFormat4x8Bit\0" // IR(23010, 25)
  "PackedVectorFormat4x8BitKHR\0" // IR(23035, 28)
  "TRN\0" // IR(23063, 4)
  "TRN_ZERO\0" // IR(23067, 9)
  "RND\0" // IR(23076, 4)
  "RND_ZERO\0" // IR(23080, 9)
  "RND_INF\0" // IR(23089, 8)
  "RND_MIN_INF\0" // IR(23097, 12)
  "RND_CONV\0" // IR(23109, 9)
  "RND_CONV_ODD\0" // IR(23118, 13)
  "RobustnessPerComponentNV\0" // IR(23131, 25)
  "RobustnessPerElementNV\0" // IR(23156, 23)
  "OpaqueKHR\0" // IR(23179, 10)
  "NoOpaqueKHR\0" // IR(23189, 12)
  "TerminateOnFirstHitKHR\0" // IR(23201, 23)
  "SkipClosestHitShaderKHR\0" // IR(23224, 24)
  "CullBackFacingTrianglesKHR\0" // IR(23248, 27)
  "CullFrontFacingTrianglesKHR\0" // IR(23275, 28)
  "CullOpaqueKHR\0" // IR(23303, 14)
  "CullNoOpaqueKHR\0" // IR(23317, 16)
  "SkipTrianglesKHR\0" // IR(23333, 17)
  "SkipBuiltinPrimitivesNV\0" // IR(23350, 24)
  "SkipAABBsKHR\0" // IR(23374, 13)
  "ForceOpacityMicromap2StateEXT\0" // IR(23387, 30)
  "RayQueryCandidateIntersectionTriangleKHR\0" // IR(23417, 41)
  "RayQueryCandidateIntersectionAABBKHR\0" // IR(23458, 37)
  "RayQueryCommittedIntersectionNoneKHR\0" // IR(23495, 37)
  "RayQueryCommittedIntersectionTriangleKHR\0" // IR(23532, 41)
  "RayQueryCommittedIntersectionGeneratedKHR\0" // IR(23573, 42)
  "RayQueryCandidateIntersectionKHR\0" // IR(23615, 33)
  "RayQueryCommittedIntersectionKHR\0" // IR(23648, 33)
  "ClampToEdge\0" // IR(23681, 12)
  "Clamp\0" // IR(23693, 6)
  "Repeat\0" // IR(23699, 7)
  "RepeatMirrored\0" // IR(23706, 15)
  "Nearest\0" // IR(23721, 8)
  "Linear\0" // IR(23729, 7)
  "Unknown\0" // IR(23736, 8)
  "Rgba32f\0" // IR(23744, 8)
  "Rgba16f\0" // IR(23752, 8)
  "R32f\0" // IR(23760, 5)
  "Rgba8\0" // IR(23765, 6)
  "Rgba8Snorm\0" // IR(23771, 11)
  "Rg32f\0" // IR(23782, 6)
  "Rg16f\0" // IR(23788, 6)
  "R11fG11fB10f\0" // IR(23794, 13)
  "R16f\0" // IR(23807, 5)
  "Rgba16\0" // IR(23812, 7)
  "Rgb10A2\0" // IR(23819, 8)
  "Rg16\0" // IR(23827, 5)
  "Rg8\0" // IR(23832, 4)
  "R16\0" // IR(23836, 4)
  "R8\0" // IR(23840, 3)
  "Rgba16Snorm\0" // IR(23843, 12)
  "Rg16Snorm\0" // IR(23855, 10)
  "Rg8Snorm\0" // IR(23865, 9)
  "R16Snorm\0" // IR(23874, 9)
  "R8Snorm\0" // IR(23883, 8)
  "Rgba32i\0" // IR(23891, 8)
  "Rgba16i\0" // IR(23899, 8)
  "Rgba8i\0" // IR(23907, 7)
  "R32i\0" // IR(23914, 5)
  "Rg32i\0" // IR(23919, 6)
  "Rg16i\0" // IR(23925, 6)
  "Rg8i\0" // IR(23931, 5)
  "R16i\0" // IR(23936, 5)
  "R8i\0" // IR(23941, 4)
  "Rgba32ui\0" // IR(23945, 9)
  "Rgba16ui\0" // IR(23954, 9)
  "Rgba8ui\0" // IR(23963, 8)
  "R32ui\0" // IR(23971, 6)
  "Rgb10a2ui\0" // IR(23977, 10)
  "Rg32ui\0" // IR(23987, 7)
  "Rg16ui\0" // IR(23994, 7)
  "Rg8ui\0" // IR(24001, 6)
  "R16ui\0" // IR(24007, 6)
  "R8ui\0" // IR(24013, 5)
  "R64ui\0" // IR(24018, 6)
  "R64i\0" // IR(24024, 5)
  "CrossDevice\0" // IR(24029, 12)
  "Device\0" // IR(24041, 7)
  "Workgroup\0" // IR(24048, 10)
  "Subgroup\0" // IR(24058, 9)
  "Invocation\0" // IR(24067, 11)
  "QueueFamily\0" // IR(24078, 12)
  "QueueFamilyKHR\0" // IR(24090, 15)
  "ShaderCallKHR\0" // IR(24105, 14)
  "Flatten\0" // IR(24119, 8)
  "DontFlatten\0" // IR(24127, 12)
  "IdentifierPossibleDuplicates\0" // IR(24139, 29)
  "FlagUnknownPhysicalLayout\0" // IR(24168, 26)
  "ESSL\0" // IR(24194, 5)
  "GLSL\0" // IR(24199, 5)
  "OpenCL_C\0" // IR(24204, 9)
  "OpenCL_CPP\0" // IR(24213, 11)
  "HLSL\0" // IR(24224, 5)
  "CPP_for_OpenCL\0" // IR(24229, 15)
  "SYCL\0" // IR(24244, 5)
  "HERO_C\0" // IR(24249, 7)
  "NZSL\0" // IR(24256, 5)
  "WGSL\0" // IR(24261, 5)
  "Slang\0" // IR(24266, 6)
  "Zig\0" // IR(24272, 4)
  "Rust\0" // IR(24276, 5)
  "UniformConstant\0" // IR(24281, 16)
  "Input\0" // IR(24297, 6)
  "Output\0" // IR(24303, 7)
  "CrossWorkgroup\0" // IR(24310, 15)
  "Private\0" // IR(24325, 8)
  "Function\0" // IR(24333, 9)
  "Generic\0" // IR(24342, 8)
  "PushConstant\0" // IR(24350, 13)
  "AtomicCounter\0" // IR(24363, 14)
  "Image\0" // IR(24377, 6)
  "StorageBuffer\0" // IR(24383, 14)
  "TileImageEXT\0" // IR(24397, 13)
  "TileAttachmentQCOM\0" // IR(24410, 19)
  "NodePayloadAMDX\0" // IR(24429, 16)
  "CallableDataKHR\0" // IR(24445, 16)
  "CallableDataNV\0" // IR(24461, 15)
  "IncomingCallableDataKHR\0" // IR(24476, 24)
  "IncomingCallableDataNV\0" // IR(24500, 23)
  "RayPayloadKHR\0" // IR(24523, 14)
  "RayPayloadNV\0" // IR(24537, 13)
  "HitAttributeKHR\0" // IR(24550, 16)
  "HitAttributeNV\0" // IR(24566, 15)
  "IncomingRayPayloadKHR\0" // IR(24581, 22)
  "IncomingRayPayloadNV\0" // IR(24603, 21)
  "ShaderRecordBufferKHR\0" // IR(24624, 22)
  "ShaderRecordBufferNV\0" // IR(24646, 21)
  "PhysicalStorageBuffer\0" // IR(24667, 22)
  "PhysicalStorageBufferEXT\0" // IR(24689, 25)
  "HitObjectAttributeNV\0" // IR(24714, 21)
  "TaskPayloadWorkgroupEXT\0" // IR(24735, 24)
  "CodeSectionINTEL\0" // IR(24759, 17)
  "DeviceOnlyINTEL\0" // IR(24776, 16)
  "HostOnlyINTEL\0" // IR(24792, 14)
  "WriteThroughINTEL\0" // IR(24806, 18)
  "WriteBackINTEL\0" // IR(24824, 15)
  "TensorView\0" // IR(24839, 11)
  "DecodeFunc\0" // IR(24850, 11)
  "Undefined\0" // IR(24861, 10)
  "NoneARM\0" // IR(24871, 8)
  "NontemporalARM\0" // IR(24879, 15)
  "OutOfBoundsValueARM\0" // IR(24894, 20)
  "MakeElementAvailableARM\0" // IR(24914, 24)
  "MakeElementVisibleARM\0" // IR(24938, 22)
  "NonPrivateElementARM\0" // IR(24960, 21)
  "Nop\0" // IR(24981, 4)
  "SPV_OPERAND_TYPE_TYPE_ID\0" // IR(24985, 25)
  "SPV_OPERAND_TYPE_RESULT_ID\0" // IR(25010, 27)
  "Undef\0" // IR(25037, 6)
  "SourceContinued\0" // IR(25043, 16)
  "SPV_OPERAND_TYPE_SOURCE_LANGUAGE\0" // IR(25059, 33)
  "SPV_OPERAND_TYPE_OPTIONAL_ID\0" // IR(25092, 29)
  "SPV_OPERAND_TYPE_OPTIONAL_LITERAL_STRING\0" // IR(25121, 41)
  "Source\0" // IR(25162, 7)
  "SourceExtension\0" // IR(25169, 16)
  "Name\0" // IR(25185, 5)
  "MemberName\0" // IR(25190, 11)
  "String\0" // IR(25201, 7)
  "Line\0" // IR(25208, 5)
  "Extension\0" // IR(25213, 10)
  "ExtInstImport\0" // IR(25223, 14)
  "SPV_OPERAND_TYPE_EXTENSION_INSTRUCTION_NUMBER\0" // IR(25237, 46)
  "ExtInst\0" // IR(25283, 8)
  "SPV_OPERAND_TYPE_ADDRESSING_MODEL\0" // IR(25291, 34)
  "SPV_OPERAND_TYPE_MEMORY_MODEL\0" // IR(25325, 30)
  "MemoryModel\0" // IR(25355, 12)
  "SPV_OPERAND_TYPE_EXECUTION_MODEL\0" // IR(25367, 33)
  "SPV_OPERAND_TYPE_VARIABLE_ID\0" // IR(25400, 29)
  "EntryPoint\0" // IR(25429, 11)
  "SPV_OPERAND_TYPE_EXECUTION_MODE\0" // IR(25440, 32)
  "ExecutionMode\0" // IR(25472, 14)
  "SPV_OPERAND_TYPE_CAPABILITY\0" // IR(25486, 28)
  "Capability\0" // IR(25514, 11)
  "TypeVoid\0" // IR(25525, 9)
  "TypeBool\0" // IR(25534, 9)
  "TypeInt\0" // IR(25543, 8)
  "SPV_OPERAND_TYPE_OPTIONAL_FPENCODING\0" // IR(25551, 37)
  "TypeFloat\0" // IR(25588, 10)
  "TypeVector\0" // IR(25598, 11)
  "TypeMatrix\0" // IR(25609, 11)
  "SPV_OPERAND_TYPE_DIMENSIONALITY\0" // IR(25620, 32)
  "SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT\0" // IR(25652, 38)
  "SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER\0" // IR(25690, 43)
  "TypeImage\0" // IR(25733, 10)
  "TypeSampler\0" // IR(25743, 12)
  "TypeSampledImage\0" // IR(25755, 17)
  "TypeArray\0" // IR(25772, 10)
  "TypeRuntimeArray\0" // IR(25782, 17)
  "TypeStruct\0" // IR(25799, 11)
  "TypeOpaque\0" // IR(25810, 11)
  "SPV_OPERAND_TYPE_STORAGE_CLASS\0" // IR(25821, 31)
  "TypePointer\0" // IR(25852, 12)
  "TypeFunction\0" // IR(25864, 13)
  "TypeEvent\0" // IR(25877, 10)
  "TypeDeviceEvent\0" // IR(25887, 16)
  "TypeReserveId\0" // IR(25903, 14)
  "TypeQueue\0" // IR(25917, 10)
  "TypePipe\0" // IR(25927, 9)
  "TypeForwardPointer\0" // IR(25936, 19)
  "ConstantTrue\0" // IR(25955, 13)
  "ConstantFalse\0" // IR(25968, 14)
  "SPV_OPERAND_TYPE_TYPED_LITERAL_NUMBER\0" // IR(25982, 38)
  "ConstantComposite\0" // IR(26020, 18)
  "SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE\0" // IR(26038, 41)
  "SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE\0" // IR(26079, 37)
  "ConstantSampler\0" // IR(26116, 16)
  "ConstantNull\0" // IR(26132, 13)
  "SpecConstantTrue\0" // IR(26145, 17)
  "SpecConstantFalse\0" // IR(26162, 18)
  "SpecConstant\0" // IR(26180, 13)
  "SpecConstantComposite\0" // IR(26193, 22)
  "SPV_OPERAND_TYPE_SPEC_CONSTANT_OP_NUMBER\0" // IR(26215, 41)
  "SpecConstantOp\0" // IR(26256, 15)
  "SPV_OPERAND_TYPE_FUNCTION_CONTROL\0" // IR(26271, 34)
  "FunctionParameter\0" // IR(26305, 18)
  "FunctionEnd\0" // IR(26323, 12)
  "FunctionCall\0" // IR(26335, 13)
  "Variable\0" // IR(26348, 9)
  "ImageTexelPointer\0" // IR(26357, 18)
  "SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS\0" // IR(26375, 40)
  "Load\0" // IR(26415, 5)
  "Store\0" // IR(26420, 6)
  "CopyMemory\0" // IR(26426, 11)
  "CopyMemorySized\0" // IR(26437, 16)
  "AccessChain\0" // IR(26453, 12)
  "InBoundsAccessChain\0" // IR(26465, 20)
  "PtrAccessChain\0" // IR(26485, 15)
  "ArrayLength\0" // IR(26500, 12)
  "GenericPtrMemSemantics\0" // IR(26512, 23)
  "InBoundsPtrAccessChain\0" // IR(26535, 23)
  "SPV_OPERAND_TYPE_DECORATION\0" // IR(26558, 28)
  "Decorate\0" // IR(26586, 9)
  "MemberDecorate\0" // IR(26595, 15)
  "DecorationGroup\0" // IR(26610, 16)
  "GroupDecorate\0" // IR(26626, 14)
  "SPV_OPERAND_TYPE_VARIABLE_ID_LITERAL_INTEGER\0" // IR(26640, 45)
  "GroupMemberDecorate\0" // IR(26685, 20)
  "VectorExtractDynamic\0" // IR(26705, 21)
  "VectorInsertDynamic\0" // IR(26726, 20)
  "VectorShuffle\0" // IR(26746, 14)
  "CompositeConstruct\0" // IR(26760, 19)
  "CompositeExtract\0" // IR(26779, 17)
  "CompositeInsert\0" // IR(26796, 16)
  "CopyObject\0" // IR(26812, 11)
  "Transpose\0" // IR(26823, 10)
  "SampledImage\0" // IR(26833, 13)
  "SPV_OPERAND_TYPE_OPTIONAL_IMAGE\0" // IR(26846, 32)
  "ImageSampleImplicitLod\0" // IR(26878, 23)
  "SPV_OPERAND_TYPE_IMAGE\0" // IR(26901, 23)
  "ImageSampleExplicitLod\0" // IR(26924, 23)
  "ImageSampleDrefImplicitLod\0" // IR(26947, 27)
  "ImageSampleDrefExplicitLod\0" // IR(26974, 27)
  "ImageSampleProjImplicitLod\0" // IR(27001, 27)
  "ImageSampleProjExplicitLod\0" // IR(27028, 27)
  "ImageSampleProjDrefImplicitLod\0" // IR(27055, 31)
  "ImageSampleProjDrefExplicitLod\0" // IR(27086, 31)
  "ImageFetch\0" // IR(27117, 11)
  "ImageGather\0" // IR(27128, 12)
  "ImageDrefGather\0" // IR(27140, 16)
  "ImageRead\0" // IR(27156, 10)
  "ImageWrite\0" // IR(27166, 11)
  "ImageQueryFormat\0" // IR(27177, 17)
  "ImageQueryOrder\0" // IR(27194, 16)
  "ImageQuerySizeLod\0" // IR(27210, 18)
  "ImageQuerySize\0" // IR(27228, 15)
  "ImageQueryLod\0" // IR(27243, 14)
  "ImageQueryLevels\0" // IR(27257, 17)
  "ImageQuerySamples\0" // IR(27274, 18)
  "ConvertFToU\0" // IR(27292, 12)
  "ConvertFToS\0" // IR(27304, 12)
  "ConvertSToF\0" // IR(27316, 12)
  "ConvertUToF\0" // IR(27328, 12)
  "UConvert\0" // IR(27340, 9)
  "SConvert\0" // IR(27349, 9)
  "FConvert\0" // IR(27358, 9)
  "QuantizeToF16\0" // IR(27367, 14)
  "ConvertPtrToU\0" // IR(27381, 14)
  "SatConvertSToU\0" // IR(27395, 15)
  "SatConvertUToS\0" // IR(27410, 15)
  "ConvertUToPtr\0" // IR(27425, 14)
  "PtrCastToGeneric\0" // IR(27439, 17)
  "GenericCastToPtr\0" // IR(27456, 17)
  "GenericCastToPtrExplicit\0" // IR(27473, 25)
  "Bitcast\0" // IR(27498, 8)
  "SNegate\0" // IR(27506, 8)
  "FNegate\0" // IR(27514, 8)
  "IAdd\0" // IR(27522, 5)
  "FAdd\0" // IR(27527, 5)
  "ISub\0" // IR(27532, 5)
  "FSub\0" // IR(27537, 5)
  "IMul\0" // IR(27542, 5)
  "FMul\0" // IR(27547, 5)
  "UDiv\0" // IR(27552, 5)
  "SDiv\0" // IR(27557, 5)
  "FDiv\0" // IR(27562, 5)
  "UMod\0" // IR(27567, 5)
  "SRem\0" // IR(27572, 5)
  "SMod\0" // IR(27577, 5)
  "FRem\0" // IR(27582, 5)
  "FMod\0" // IR(27587, 5)
  "VectorTimesScalar\0" // IR(27592, 18)
  "MatrixTimesScalar\0" // IR(27610, 18)
  "VectorTimesMatrix\0" // IR(27628, 18)
  "MatrixTimesVector\0" // IR(27646, 18)
  "MatrixTimesMatrix\0" // IR(27664, 18)
  "OuterProduct\0" // IR(27682, 13)
  "Dot\0" // IR(27695, 4)
  "IAddCarry\0" // IR(27699, 10)
  "ISubBorrow\0" // IR(27709, 11)
  "UMulExtended\0" // IR(27720, 13)
  "SMulExtended\0" // IR(27733, 13)
  "Any\0" // IR(27746, 4)
  "All\0" // IR(27750, 4)
  "IsNan\0" // IR(27754, 6)
  "IsInf\0" // IR(27760, 6)
  "IsFinite\0" // IR(27766, 9)
  "IsNormal\0" // IR(27775, 9)
  "SignBitSet\0" // IR(27784, 11)
  "LessOrGreater\0" // IR(27795, 14)
  "Ordered\0" // IR(27809, 8)
  "Unordered\0" // IR(27817, 10)
  "LogicalEqual\0" // IR(27827, 13)
  "LogicalNotEqual\0" // IR(27840, 16)
  "LogicalOr\0" // IR(27856, 10)
  "LogicalAnd\0" // IR(27866, 11)
  "LogicalNot\0" // IR(27877, 11)
  "Select\0" // IR(27888, 7)
  "IEqual\0" // IR(27895, 7)
  "INotEqual\0" // IR(27902, 10)
  "UGreaterThan\0" // IR(27912, 13)
  "SGreaterThan\0" // IR(27925, 13)
  "UGreaterThanEqual\0" // IR(27938, 18)
  "SGreaterThanEqual\0" // IR(27956, 18)
  "ULessThan\0" // IR(27974, 10)
  "SLessThan\0" // IR(27984, 10)
  "ULessThanEqual\0" // IR(27994, 15)
  "SLessThanEqual\0" // IR(28009, 15)
  "FOrdEqual\0" // IR(28024, 10)
  "FUnordEqual\0" // IR(28034, 12)
  "FOrdNotEqual\0" // IR(28046, 13)
  "FUnordNotEqual\0" // IR(28059, 15)
  "FOrdLessThan\0" // IR(28074, 13)
  "FUnordLessThan\0" // IR(28087, 15)
  "FOrdGreaterThan\0" // IR(28102, 16)
  "FUnordGreaterThan\0" // IR(28118, 18)
  "FOrdLessThanEqual\0" // IR(28136, 18)
  "FUnordLessThanEqual\0" // IR(28154, 20)
  "FOrdGreaterThanEqual\0" // IR(28174, 21)
  "FUnordGreaterThanEqual\0" // IR(28195, 23)
  "ShiftRightLogical\0" // IR(28218, 18)
  "ShiftRightArithmetic\0" // IR(28236, 21)
  "ShiftLeftLogical\0" // IR(28257, 17)
  "BitwiseOr\0" // IR(28274, 10)
  "BitwiseXor\0" // IR(28284, 11)
  "BitwiseAnd\0" // IR(28295, 11)
  "Not\0" // IR(28306, 4)
  "BitFieldInsert\0" // IR(28310, 15)
  "BitFieldSExtract\0" // IR(28325, 17)
  "BitFieldUExtract\0" // IR(28342, 17)
  "BitReverse\0" // IR(28359, 11)
  "BitCount\0" // IR(28370, 9)
  "DPdx\0" // IR(28379, 5)
  "DPdy\0" // IR(28384, 5)
  "Fwidth\0" // IR(28389, 7)
  "DPdxFine\0" // IR(28396, 9)
  "DPdyFine\0" // IR(28405, 9)
  "FwidthFine\0" // IR(28414, 11)
  "DPdxCoarse\0" // IR(28425, 11)
  "DPdyCoarse\0" // IR(28436, 11)
  "FwidthCoarse\0" // IR(28447, 13)
  "EmitVertex\0" // IR(28460, 11)
  "EndPrimitive\0" // IR(28471, 13)
  "EmitStreamVertex\0" // IR(28484, 17)
  "EndStreamPrimitive\0" // IR(28501, 19)
  "SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID\0" // IR(28520, 37)
  "ControlBarrier\0" // IR(28557, 15)
  "MemoryBarrier\0" // IR(28572, 14)
  "AtomicLoad\0" // IR(28586, 11)
  "AtomicStore\0" // IR(28597, 12)
  "AtomicExchange\0" // IR(28609, 15)
  "AtomicCompareExchange\0" // IR(28624, 22)
  "AtomicCompareExchangeWeak\0" // IR(28646, 26)
  "AtomicIIncrement\0" // IR(28672, 17)
  "AtomicIDecrement\0" // IR(28689, 17)
  "AtomicIAdd\0" // IR(28706, 11)
  "AtomicISub\0" // IR(28717, 11)
  "AtomicSMin\0" // IR(28728, 11)
  "AtomicUMin\0" // IR(28739, 11)
  "AtomicSMax\0" // IR(28750, 11)
  "AtomicUMax\0" // IR(28761, 11)
  "AtomicAnd\0" // IR(28772, 10)
  "AtomicOr\0" // IR(28782, 9)
  "AtomicXor\0" // IR(28791, 10)
  "Phi\0" // IR(28801, 4)
  "SPV_OPERAND_TYPE_LOOP_CONTROL\0" // IR(28805, 30)
  "LoopMerge\0" // IR(28835, 10)
  "SPV_OPERAND_TYPE_SELECTION_CONTROL\0" // IR(28845, 35)
  "SelectionMerge\0" // IR(28880, 15)
  "Label\0" // IR(28895, 6)
  "Branch\0" // IR(28901, 7)
  "BranchConditional\0" // IR(28908, 18)
  "SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER_ID\0" // IR(28926, 45)
  "Switch\0" // IR(28971, 7)
  "Kill\0" // IR(28978, 5)
  "Return\0" // IR(28983, 7)
  "ReturnValue\0" // IR(28990, 12)
  "Unreachable\0" // IR(29002, 12)
  "LifetimeStart\0" // IR(29014, 14)
  "LifetimeStop\0" // IR(29028, 13)
  "GroupAsyncCopy\0" // IR(29041, 15)
  "GroupWaitEvents\0" // IR(29056, 16)
  "GroupAll\0" // IR(29072, 9)
  "GroupAny\0" // IR(29081, 9)
  "GroupBroadcast\0" // IR(29090, 15)
  "SPV_OPERAND_TYPE_GROUP_OPERATION\0" // IR(29105, 33)
  "GroupIAdd\0" // IR(29138, 10)
  "GroupFAdd\0" // IR(29148, 10)
  "GroupFMin\0" // IR(29158, 10)
  "GroupUMin\0" // IR(29168, 10)
  "GroupSMin\0" // IR(29178, 10)
  "GroupFMax\0" // IR(29188, 10)
  "GroupUMax\0" // IR(29198, 10)
  "GroupSMax\0" // IR(29208, 10)
  "ReadPipe\0" // IR(29218, 9)
  "WritePipe\0" // IR(29227, 10)
  "ReservedReadPipe\0" // IR(29237, 17)
  "ReservedWritePipe\0" // IR(29254, 18)
  "ReserveReadPipePackets\0" // IR(29272, 23)
  "ReserveWritePipePackets\0" // IR(29295, 24)
  "CommitReadPipe\0" // IR(29319, 15)
  "CommitWritePipe\0" // IR(29334, 16)
  "IsValidReserveId\0" // IR(29350, 17)
  "GetNumPipePackets\0" // IR(29367, 18)
  "GetMaxPipePackets\0" // IR(29385, 18)
  "GroupReserveReadPipePackets\0" // IR(29403, 28)
  "GroupReserveWritePipePackets\0" // IR(29431, 29)
  "GroupCommitReadPipe\0" // IR(29460, 20)
  "GroupCommitWritePipe\0" // IR(29480, 21)
  "EnqueueMarker\0" // IR(29501, 14)
  "EnqueueKernel\0" // IR(29515, 14)
  "GetKernelNDrangeSubGroupCount\0" // IR(29529, 30)
  "GetKernelNDrangeMaxSubGroupSize\0" // IR(29559, 32)
  "GetKernelWorkGroupSize\0" // IR(29591, 23)
  "GetKernelPreferredWorkGroupSizeMultiple\0" // IR(29614, 40)
  "RetainEvent\0" // IR(29654, 12)
  "ReleaseEvent\0" // IR(29666, 13)
  "CreateUserEvent\0" // IR(29679, 16)
  "IsValidEvent\0" // IR(29695, 13)
  "SetUserEventStatus\0" // IR(29708, 19)
  "CaptureEventProfilingInfo\0" // IR(29727, 26)
  "GetDefaultQueue\0" // IR(29753, 16)
  "BuildNDRange\0" // IR(29769, 13)
  "ImageSparseSampleImplicitLod\0" // IR(29782, 29)
  "ImageSparseSampleExplicitLod\0" // IR(29811, 29)
  "ImageSparseSampleDrefImplicitLod\0" // IR(29840, 33)
  "ImageSparseSampleDrefExplicitLod\0" // IR(29873, 33)
  "ImageSparseSampleProjImplicitLod\0" // IR(29906, 33)
  "ImageSparseSampleProjExplicitLod\0" // IR(29939, 33)
  "ImageSparseSampleProjDrefImplicitLod\0" // IR(29972, 37)
  "ImageSparseSampleProjDrefExplicitLod\0" // IR(30009, 37)
  "ImageSparseFetch\0" // IR(30046, 17)
  "ImageSparseGather\0" // IR(30063, 18)
  "ImageSparseDrefGather\0" // IR(30081, 22)
  "ImageSparseTexelsResident\0" // IR(30103, 26)
  "NoLine\0" // IR(30129, 7)
  "AtomicFlagTestAndSet\0" // IR(30136, 21)
  "AtomicFlagClear\0" // IR(30157, 16)
  "ImageSparseRead\0" // IR(30173, 16)
  "SizeOf\0" // IR(30189, 7)
  "TypePipeStorage\0" // IR(30196, 16)
  "ConstantPipeStorage\0" // IR(30212, 20)
  "CreatePipeFromPipeStorage\0" // IR(30232, 26)
  "GetKernelLocalSizeForSubgroupCount\0" // IR(30258, 35)
  "GetKernelMaxNumSubgroups\0" // IR(30293, 25)
  "TypeNamedBarrier\0" // IR(30318, 17)
  "NamedBarrierInitialize\0" // IR(30335, 23)
  "MemoryNamedBarrier\0" // IR(30358, 19)
  "ModuleProcessed\0" // IR(30377, 16)
  "ExecutionModeId\0" // IR(30393, 16)
  "DecorateId\0" // IR(30409, 11)
  "GroupNonUniformElect\0" // IR(30420, 21)
  "GroupNonUniformAll\0" // IR(30441, 19)
  "GroupNonUniformAny\0" // IR(30460, 19)
  "GroupNonUniformAllEqual\0" // IR(30479, 24)
  "GroupNonUniformBroadcast\0" // IR(30503, 25)
  "GroupNonUniformBroadcastFirst\0" // IR(30528, 30)
  "GroupNonUniformInverseBallot\0" // IR(30558, 29)
  "GroupNonUniformBallotBitExtract\0" // IR(30587, 32)
  "GroupNonUniformBallotBitCount\0" // IR(30619, 30)
  "GroupNonUniformBallotFindLSB\0" // IR(30649, 29)
  "GroupNonUniformBallotFindMSB\0" // IR(30678, 29)
  "GroupNonUniformShuffleXor\0" // IR(30707, 26)
  "GroupNonUniformShuffleUp\0" // IR(30733, 25)
  "GroupNonUniformShuffleDown\0" // IR(30758, 27)
  "GroupNonUniformIAdd\0" // IR(30785, 20)
  "GroupNonUniformFAdd\0" // IR(30805, 20)
  "GroupNonUniformIMul\0" // IR(30825, 20)
  "GroupNonUniformFMul\0" // IR(30845, 20)
  "GroupNonUniformSMin\0" // IR(30865, 20)
  "GroupNonUniformUMin\0" // IR(30885, 20)
  "GroupNonUniformFMin\0" // IR(30905, 20)
  "GroupNonUniformSMax\0" // IR(30925, 20)
  "GroupNonUniformUMax\0" // IR(30945, 20)
  "GroupNonUniformFMax\0" // IR(30965, 20)
  "GroupNonUniformBitwiseAnd\0" // IR(30985, 26)
  "GroupNonUniformBitwiseOr\0" // IR(31011, 25)
  "GroupNonUniformBitwiseXor\0" // IR(31036, 26)
  "GroupNonUniformLogicalAnd\0" // IR(31062, 26)
  "GroupNonUniformLogicalOr\0" // IR(31088, 25)
  "GroupNonUniformLogicalXor\0" // IR(31113, 26)
  "GroupNonUniformQuadBroadcast\0" // IR(31139, 29)
  "GroupNonUniformQuadSwap\0" // IR(31168, 24)
  "CopyLogical\0" // IR(31192, 12)
  "PtrEqual\0" // IR(31204, 9)
  "PtrNotEqual\0" // IR(31213, 12)
  "PtrDiff\0" // IR(31225, 8)
  "ColorAttachmentReadEXT\0" // IR(31233, 23)
  "DepthAttachmentReadEXT\0" // IR(31256, 23)
  "StencilAttachmentReadEXT\0" // IR(31279, 25)
  "TypeTensorARM\0" // IR(31304, 14)
  "SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS\0" // IR(31318, 42)
  "TensorReadARM\0" // IR(31360, 14)
  "TensorWriteARM\0" // IR(31374, 15)
  "TensorQuerySizeARM\0" // IR(31389, 19)
  "TerminateInvocation\0" // IR(31408, 20)
  "TypeUntypedPointerKHR\0" // IR(31428, 22)
  "UntypedVariableKHR\0" // IR(31450, 19)
  "UntypedAccessChainKHR\0" // IR(31469, 22)
  "UntypedInBoundsAccessChainKHR\0" // IR(31491, 30)
  "SubgroupFirstInvocationKHR\0" // IR(31521, 27)
  "UntypedPtrAccessChainKHR\0" // IR(31548, 25)
  "UntypedInBoundsPtrAccessChainKHR\0" // IR(31573, 33)
  "UntypedArrayLengthKHR\0" // IR(31606, 22)
  "UntypedPrefetchKHR\0" // IR(31628, 19)
  "SubgroupAllKHR\0" // IR(31647, 15)
  "SubgroupAnyKHR\0" // IR(31662, 15)
  "SubgroupAllEqualKHR\0" // IR(31677, 20)
  "SubgroupReadInvocationKHR\0" // IR(31697, 26)
  "ExtInstWithForwardRefsKHR\0" // IR(31723, 26)
  "TraceRayKHR\0" // IR(31749, 12)
  "ExecuteCallableKHR\0" // IR(31761, 19)
  "ConvertUToAccelerationStructureKHR\0" // IR(31780, 35)
  "IgnoreIntersectionKHR\0" // IR(31815, 22)
  "TerminateRayKHR\0" // IR(31837, 16)
  "SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT\0" // IR(31853, 47)
  "SDot\0" // IR(31900, 5)
  "SDotKHR\0" // IR(31905, 8)
  "UDot\0" // IR(31913, 5)
  "UDotKHR\0" // IR(31918, 8)
  "SUDot\0" // IR(31926, 6)
  "SUDotKHR\0" // IR(31932, 9)
  "SDotAccSat\0" // IR(31941, 11)
  "SDotAccSatKHR\0" // IR(31952, 14)
  "UDotAccSat\0" // IR(31966, 11)
  "UDotAccSatKHR\0" // IR(31977, 14)
  "SUDotAccSat\0" // IR(31991, 12)
  "SUDotAccSatKHR\0" // IR(32003, 15)
  "TypeCooperativeMatrixKHR\0" // IR(32018, 25)
  "CooperativeMatrixLoadKHR\0" // IR(32043, 25)
  "CooperativeMatrixStoreKHR\0" // IR(32068, 26)
  "SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS\0" // IR(32094, 54)
  "CooperativeMatrixMulAddKHR\0" // IR(32148, 27)
  "CooperativeMatrixLengthKHR\0" // IR(32175, 27)
  "ConstantCompositeReplicateEXT\0" // IR(32202, 30)
  "SpecConstantCompositeReplicateEXT\0" // IR(32232, 34)
  "CompositeConstructReplicateEXT\0" // IR(32266, 31)
  "TypeRayQueryKHR\0" // IR(32297, 16)
  "RayQueryInitializeKHR\0" // IR(32313, 22)
  "RayQueryTerminateKHR\0" // IR(32335, 21)
  "RayQueryGenerateIntersectionKHR\0" // IR(32356, 32)
  "RayQueryConfirmIntersectionKHR\0" // IR(32388, 31)
  "RayQueryProceedKHR\0" // IR(32419, 19)
  "RayQueryGetIntersectionTypeKHR\0" // IR(32438, 31)
  "ImageSampleWeightedQCOM\0" // IR(32469, 24)
  "ImageBoxFilterQCOM\0" // IR(32493, 19)
  "ImageBlockMatchSSDQCOM\0" // IR(32512, 23)
  "ImageBlockMatchSADQCOM\0" // IR(32535, 23)
  "ImageBlockMatchWindowSSDQCOM\0" // IR(32558, 29)
  "ImageBlockMatchWindowSADQCOM\0" // IR(32587, 29)
  "ImageBlockMatchGatherSSDQCOM\0" // IR(32616, 29)
  "ImageBlockMatchGatherSADQCOM\0" // IR(32645, 29)
  "GroupIAddNonUniformAMD\0" // IR(32674, 23)
  "GroupFAddNonUniformAMD\0" // IR(32697, 23)
  "GroupFMinNonUniformAMD\0" // IR(32720, 23)
  "GroupUMinNonUniformAMD\0" // IR(32743, 23)
  "GroupSMinNonUniformAMD\0" // IR(32766, 23)
  "GroupFMaxNonUniformAMD\0" // IR(32789, 23)
  "GroupUMaxNonUniformAMD\0" // IR(32812, 23)
  "GroupSMaxNonUniformAMD\0" // IR(32835, 23)
  "FragmentMaskFetchAMD\0" // IR(32858, 21)
  "FragmentFetchAMD\0" // IR(32879, 17)
  "ReadClockKHR\0" // IR(32896, 13)
  "AllocateNodePayloadsAMDX\0" // IR(32909, 25)
  "EnqueueNodePayloadsAMDX\0" // IR(32934, 24)
  "TypeNodePayloadArrayAMDX\0" // IR(32958, 25)
  "FinishWritingNodePayloadAMDX\0" // IR(32983, 29)
  "NodePayloadArrayLengthAMDX\0" // IR(33012, 27)
  "IsNodePayloadValidAMDX\0" // IR(33039, 23)
  "ConstantStringAMDX\0" // IR(33062, 19)
  "SpecConstantStringAMDX\0" // IR(33081, 23)
  "GroupNonUniformQuadAllKHR\0" // IR(33104, 26)
  "GroupNonUniformQuadAnyKHR\0" // IR(33130, 26)
  "HitObjectRecordHitMotionNV\0" // IR(33156, 27)
  "HitObjectRecordHitWithIndexMotionNV\0" // IR(33183, 36)
  "HitObjectRecordMissMotionNV\0" // IR(33219, 28)
  "HitObjectGetWorldToObjectNV\0" // IR(33247, 28)
  "HitObjectGetObjectToWorldNV\0" // IR(33275, 28)
  "HitObjectGetObjectRayDirectionNV\0" // IR(33303, 33)
  "HitObjectGetObjectRayOriginNV\0" // IR(33336, 30)
  "HitObjectTraceRayMotionNV\0" // IR(33366, 26)
  "HitObjectGetShaderRecordBufferHandleNV\0" // IR(33392, 39)
  "HitObjectGetShaderBindingTableRecordIndexNV\0" // IR(33431, 44)
  "HitObjectRecordEmptyNV\0" // IR(33475, 23)
  "HitObjectTraceRayNV\0" // IR(33498, 20)
  "HitObjectRecordHitNV\0" // IR(33518, 21)
  "HitObjectRecordHitWithIndexNV\0" // IR(33539, 30)
  "HitObjectRecordMissNV\0" // IR(33569, 22)
  "HitObjectExecuteShaderNV\0" // IR(33591, 25)
  "HitObjectGetCurrentTimeNV\0" // IR(33616, 26)
  "HitObjectGetAttributesNV\0" // IR(33642, 25)
  "HitObjectGetHitKindNV\0" // IR(33667, 22)
  "HitObjectGetPrimitiveIndexNV\0" // IR(33689, 29)
  "HitObjectGetGeometryIndexNV\0" // IR(33718, 28)
  "HitObjectGetInstanceIdNV\0" // IR(33746, 25)
  "HitObjectGetInstanceCustomIndexNV\0" // IR(33771, 34)
  "HitObjectGetWorldRayDirectionNV\0" // IR(33805, 32)
  "HitObjectGetWorldRayOriginNV\0" // IR(33837, 29)
  "HitObjectGetRayTMaxNV\0" // IR(33866, 22)
  "HitObjectGetRayTMinNV\0" // IR(33888, 22)
  "HitObjectIsEmptyNV\0" // IR(33910, 19)
  "HitObjectIsHitNV\0" // IR(33929, 17)
  "HitObjectIsMissNV\0" // IR(33946, 18)
  "ReorderThreadWithHitObjectNV\0" // IR(33964, 29)
  "ReorderThreadWithHintNV\0" // IR(33993, 24)
  "TypeHitObjectNV\0" // IR(34017, 16)
  "ImageSampleFootprintNV\0" // IR(34033, 23)
  "TypeCooperativeVectorNV\0" // IR(34056, 24)
  "CooperativeVectorMatrixMulNV\0" // IR(34080, 29)
  "CooperativeVectorOuterProductAccumulateNV\0" // IR(34109, 42)
  "CooperativeVectorReduceSumAccumulateNV\0" // IR(34151, 39)
  "CooperativeVectorMatrixMulAddNV\0" // IR(34190, 32)
  "CooperativeMatrixConvertNV\0" // IR(34222, 27)
  "EmitMeshTasksEXT\0" // IR(34249, 17)
  "SetMeshOutputsEXT\0" // IR(34266, 18)
  "GroupNonUniformPartitionNV\0" // IR(34284, 27)
  "WritePackedPrimitiveIndices4x8NV\0" // IR(34311, 33)
  "FetchMicroTriangleVertexPositionNV\0" // IR(34344, 35)
  "FetchMicroTriangleVertexBarycentricNV\0" // IR(34379, 38)
  "CooperativeVectorLoadNV\0" // IR(34417, 24)
  "CooperativeVectorStoreNV\0" // IR(34441, 25)
  "ReportIntersectionKHR\0" // IR(34466, 22)
  "ReportIntersectionNV\0" // IR(34488, 21)
  "IgnoreIntersectionNV\0" // IR(34509, 21)
  "TerminateRayNV\0" // IR(34530, 15)
  "TraceNV\0" // IR(34545, 8)
  "TraceMotionNV\0" // IR(34553, 14)
  "TraceRayMotionNV\0" // IR(34567, 17)
  "RayQueryGetIntersectionTriangleVertexPositionsKHR\0" // IR(34584, 50)
  "TypeAccelerationStructureKHR\0" // IR(34634, 29)
  "TypeAccelerationStructureNV\0" // IR(34663, 28)
  "ExecuteCallableNV\0" // IR(34691, 18)
  "RayQueryGetClusterIdNV\0" // IR(34709, 23)
  "HitObjectGetClusterIdNV\0" // IR(34732, 24)
  "TypeCooperativeMatrixNV\0" // IR(34756, 24)
  "CooperativeMatrixLoadNV\0" // IR(34780, 24)
  "CooperativeMatrixStoreNV\0" // IR(34804, 25)
  "CooperativeMatrixMulAddNV\0" // IR(34829, 26)
  "CooperativeMatrixLengthNV\0" // IR(34855, 26)
  "BeginInvocationInterlockEXT\0" // IR(34881, 28)
  "EndInvocationInterlockEXT\0" // IR(34909, 26)
  "SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE\0" // IR(34935, 43)
  "CooperativeMatrixReduceNV\0" // IR(34978, 26)
  "SPV_OPERAND_TYPE_MEMORY_ACCESS\0" // IR(35004, 31)
  "SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS\0" // IR(35035, 44)
  "CooperativeMatrixLoadTensorNV\0" // IR(35079, 30)
  "CooperativeMatrixStoreTensorNV\0" // IR(35109, 31)
  "CooperativeMatrixPerElementOpNV\0" // IR(35140, 32)
  "TypeTensorLayoutNV\0" // IR(35172, 19)
  "TypeTensorViewNV\0" // IR(35191, 17)
  "CreateTensorLayoutNV\0" // IR(35208, 21)
  "TensorLayoutSetDimensionNV\0" // IR(35229, 27)
  "TensorLayoutSetStrideNV\0" // IR(35256, 24)
  "TensorLayoutSliceNV\0" // IR(35280, 20)
  "TensorLayoutSetClampValueNV\0" // IR(35300, 28)
  "CreateTensorViewNV\0" // IR(35328, 19)
  "TensorViewSetDimensionNV\0" // IR(35347, 25)
  "TensorViewSetStrideNV\0" // IR(35372, 22)
  "IsHelperInvocationEXT\0" // IR(35394, 22)
  "TensorViewSetClipNV\0" // IR(35416, 20)
  "TensorLayoutSetBlockSizeNV\0" // IR(35436, 27)
  "CooperativeMatrixTransposeNV\0" // IR(35463, 29)
  "ConvertUToImageNV\0" // IR(35492, 18)
  "ConvertUToSamplerNV\0" // IR(35510, 20)
  "ConvertImageToUNV\0" // IR(35530, 18)
  "ConvertSamplerToUNV\0" // IR(35548, 20)
  "ConvertUToSampledImageNV\0" // IR(35568, 25)
  "ConvertSampledImageToUNV\0" // IR(35593, 25)
  "SamplerImageAddressingModeNV\0" // IR(35618, 29)
  "SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS\0" // IR(35647, 52)
  "RawAccessChainNV\0" // IR(35699, 17)
  "RayQueryGetIntersectionSpherePositionNV\0" // IR(35716, 40)
  "RayQueryGetIntersectionSphereRadiusNV\0" // IR(35756, 38)
  "RayQueryGetIntersectionLSSPositionsNV\0" // IR(35794, 38)
  "RayQueryGetIntersectionLSSRadiiNV\0" // IR(35832, 34)
  "RayQueryGetIntersectionLSSHitValueNV\0" // IR(35866, 37)
  "HitObjectGetSpherePositionNV\0" // IR(35903, 29)
  "HitObjectGetSphereRadiusNV\0" // IR(35932, 27)
  "HitObjectGetLSSPositionsNV\0" // IR(35959, 27)
  "HitObjectGetLSSRadiiNV\0" // IR(35986, 23)
  "HitObjectIsSphereHitNV\0" // IR(36009, 23)
  "HitObjectIsLSSHitNV\0" // IR(36032, 20)
  "RayQueryIsSphereHitNV\0" // IR(36052, 22)
  "RayQueryIsLSSHitNV\0" // IR(36074, 19)
  "SubgroupShuffleDownINTEL\0" // IR(36093, 25)
  "SubgroupShuffleUpINTEL\0" // IR(36118, 23)
  "SubgroupShuffleXorINTEL\0" // IR(36141, 24)
  "SubgroupBlockReadINTEL\0" // IR(36165, 23)
  "SubgroupBlockWriteINTEL\0" // IR(36188, 24)
  "SubgroupImageBlockReadINTEL\0" // IR(36212, 28)
  "SubgroupImageBlockWriteINTEL\0" // IR(36240, 29)
  "SubgroupImageMediaBlockReadINTEL\0" // IR(36269, 33)
  "SubgroupImageMediaBlockWriteINTEL\0" // IR(36302, 34)
  "UCountLeadingZerosINTEL\0" // IR(36336, 24)
  "UCountTrailingZerosINTEL\0" // IR(36360, 25)
  "AbsISubINTEL\0" // IR(36385, 13)
  "AbsUSubINTEL\0" // IR(36398, 13)
  "IAddSatINTEL\0" // IR(36411, 13)
  "UAddSatINTEL\0" // IR(36424, 13)
  "IAverageINTEL\0" // IR(36437, 14)
  "UAverageINTEL\0" // IR(36451, 14)
  "IAverageRoundedINTEL\0" // IR(36465, 21)
  "UAverageRoundedINTEL\0" // IR(36486, 21)
  "ISubSatINTEL\0" // IR(36507, 13)
  "USubSatINTEL\0" // IR(36520, 13)
  "IMul32x16INTEL\0" // IR(36533, 15)
  "UMul32x16INTEL\0" // IR(36548, 15)
  "ConstantFunctionPointerINTEL\0" // IR(36563, 29)
  "FunctionPointerCallINTEL\0" // IR(36592, 25)
  "AsmTargetINTEL\0" // IR(36617, 15)
  "AsmCallINTEL\0" // IR(36632, 13)
  "AtomicFMinEXT\0" // IR(36645, 14)
  "AtomicFMaxEXT\0" // IR(36659, 14)
  "AssumeTrueKHR\0" // IR(36673, 14)
  "ExpectKHR\0" // IR(36687, 10)
  "DecorateString\0" // IR(36697, 15)
  "DecorateStringGOOGLE\0" // IR(36712, 21)
  "MemberDecorateString\0" // IR(36733, 21)
  "MemberDecorateStringGOOGLE\0" // IR(36754, 27)
  "VmeImageINTEL\0" // IR(36781, 14)
  "TypeVmeImageINTEL\0" // IR(36795, 18)
  "TypeAvcImePayloadINTEL\0" // IR(36813, 23)
  "TypeAvcRefPayloadINTEL\0" // IR(36836, 23)
  "TypeAvcSicPayloadINTEL\0" // IR(36859, 23)
  "TypeAvcMcePayloadINTEL\0" // IR(36882, 23)
  "TypeAvcMceResultINTEL\0" // IR(36905, 22)
  "TypeAvcImeResultINTEL\0" // IR(36927, 22)
  "TypeAvcImeResultSingleReferenceStreamoutINTEL\0" // IR(36949, 46)
  "TypeAvcImeResultDualReferenceStreamoutINTEL\0" // IR(36995, 44)
  "TypeAvcImeSingleReferenceStreaminINTEL\0" // IR(37039, 39)
  "TypeAvcImeDualReferenceStreaminINTEL\0" // IR(37078, 37)
  "TypeAvcRefResultINTEL\0" // IR(37115, 22)
  "TypeAvcSicResultINTEL\0" // IR(37137, 22)
  "SubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL\0" // IR(37159, 60)
  "SubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL\0" // IR(37219, 53)
  "SubgroupAvcMceGetDefaultInterShapePenaltyINTEL\0" // IR(37272, 47)
  "SubgroupAvcMceSetInterShapePenaltyINTEL\0" // IR(37319, 40)
  "SubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL\0" // IR(37359, 51)
  "SubgroupAvcMceSetInterDirectionPenaltyINTEL\0" // IR(37410, 44)
  "SubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL\0" // IR(37454, 51)
  "SubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL\0" // IR(37505, 56)
  "SubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL\0" // IR(37561, 50)
  "SubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL\0" // IR(37611, 52)
  "SubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL\0" // IR(37663, 49)
  "SubgroupAvcMceSetMotionVectorCostFunctionINTEL\0" // IR(37712, 47)
  "SubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL\0" // IR(37759, 50)
  "SubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL\0" // IR(37809, 51)
  "SubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL\0" // IR(37860, 56)
  "SubgroupAvcMceSetAcOnlyHaarINTEL\0" // IR(37916, 33)
  "SubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL\0" // IR(37949, 52)
  "SubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL\0" // IR(38001, 61)
  "SubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL\0" // IR(38062, 61)
  "SubgroupAvcMceConvertToImePayloadINTEL\0" // IR(38123, 39)
  "SubgroupAvcMceConvertToImeResultINTEL\0" // IR(38162, 38)
  "SubgroupAvcMceConvertToRefPayloadINTEL\0" // IR(38200, 39)
  "SubgroupAvcMceConvertToRefResultINTEL\0" // IR(38239, 38)
  "SubgroupAvcMceConvertToSicPayloadINTEL\0" // IR(38277, 39)
  "SubgroupAvcMceConvertToSicResultINTEL\0" // IR(38316, 38)
  "SubgroupAvcMceGetMotionVectorsINTEL\0" // IR(38354, 36)
  "SubgroupAvcMceGetInterDistortionsINTEL\0" // IR(38390, 39)
  "SubgroupAvcMceGetBestInterDistortionsINTEL\0" // IR(38429, 43)
  "SubgroupAvcMceGetInterMajorShapeINTEL\0" // IR(38472, 38)
  "SubgroupAvcMceGetInterMinorShapeINTEL\0" // IR(38510, 38)
  "SubgroupAvcMceGetInterDirectionsINTEL\0" // IR(38548, 38)
  "SubgroupAvcMceGetInterMotionVectorCountINTEL\0" // IR(38586, 45)
  "SubgroupAvcMceGetInterReferenceIdsINTEL\0" // IR(38631, 40)
  "SubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL\0" // IR(38671, 62)
  "SubgroupAvcImeInitializeINTEL\0" // IR(38733, 30)
  "SubgroupAvcImeSetSingleReferenceINTEL\0" // IR(38763, 38)
  "SubgroupAvcImeSetDualReferenceINTEL\0" // IR(38801, 36)
  "SubgroupAvcImeRefWindowSizeINTEL\0" // IR(38837, 33)
  "SubgroupAvcImeAdjustRefOffsetINTEL\0" // IR(38870, 35)
  "SubgroupAvcImeConvertToMcePayloadINTEL\0" // IR(38905, 39)
  "SubgroupAvcImeSetMaxMotionVectorCountINTEL\0" // IR(38944, 43)
  "SubgroupAvcImeSetUnidirectionalMixDisableINTEL\0" // IR(38987, 47)
  "SubgroupAvcImeSetEarlySearchTerminationThresholdINTEL\0" // IR(39034, 54)
  "SubgroupAvcImeSetWeightedSadINTEL\0" // IR(39088, 34)
  "SubgroupAvcImeEvaluateWithSingleReferenceINTEL\0" // IR(39122, 47)
  "SubgroupAvcImeEvaluateWithDualReferenceINTEL\0" // IR(39169, 45)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL\0" // IR(39214, 55)
  "SubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL\0" // IR(39269, 53)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL\0" // IR(39322, 56)
  "SubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL\0" // IR(39378, 54)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL\0" // IR(39432, 58)
  "SubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL\0" // IR(39490, 56)
  "SubgroupAvcImeConvertToMceResultINTEL\0" // IR(39546, 38)
  "SubgroupAvcImeGetSingleReferenceStreaminINTEL\0" // IR(39584, 46)
  "SubgroupAvcImeGetDualReferenceStreaminINTEL\0" // IR(39630, 44)
  "SubgroupAvcImeStripSingleReferenceStreamoutINTEL\0" // IR(39674, 49)
  "SubgroupAvcImeStripDualReferenceStreamoutINTEL\0" // IR(39723, 47)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL\0" // IR(39770, 70)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL\0" // IR(39840, 68)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL\0" // IR(39908, 69)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL\0" // IR(39977, 68)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL\0" // IR(40045, 66)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL\0" // IR(40111, 67)
  "SubgroupAvcImeGetBorderReachedINTEL\0" // IR(40178, 36)
  "SubgroupAvcImeGetTruncatedSearchIndicationINTEL\0" // IR(40214, 48)
  "SubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL\0" // IR(40262, 59)
  "SubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL\0" // IR(40321, 58)
  "SubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL\0" // IR(40379, 56)
  "SubgroupAvcFmeInitializeINTEL\0" // IR(40435, 30)
  "SubgroupAvcBmeInitializeINTEL\0" // IR(40465, 30)
  "SubgroupAvcRefConvertToMcePayloadINTEL\0" // IR(40495, 39)
  "SubgroupAvcRefSetBidirectionalMixDisableINTEL\0" // IR(40534, 46)
  "SubgroupAvcRefSetBilinearFilterEnableINTEL\0" // IR(40580, 43)
  "SubgroupAvcRefEvaluateWithSingleReferenceINTEL\0" // IR(40623, 47)
  "SubgroupAvcRefEvaluateWithDualReferenceINTEL\0" // IR(40670, 45)
  "SubgroupAvcRefEvaluateWithMultiReferenceINTEL\0" // IR(40715, 46)
  "SubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL\0" // IR(40761, 56)
  "SubgroupAvcRefConvertToMceResultINTEL\0" // IR(40817, 38)
  "SubgroupAvcSicInitializeINTEL\0" // IR(40855, 30)
  "SubgroupAvcSicConfigureSkcINTEL\0" // IR(40885, 32)
  "SubgroupAvcSicConfigureIpeLumaINTEL\0" // IR(40917, 36)
  "SubgroupAvcSicConfigureIpeLumaChromaINTEL\0" // IR(40953, 42)
  "SubgroupAvcSicGetMotionVectorMaskINTEL\0" // IR(40995, 39)
  "SubgroupAvcSicConvertToMcePayloadINTEL\0" // IR(41034, 39)
  "SubgroupAvcSicSetIntraLumaShapePenaltyINTEL\0" // IR(41073, 44)
  "SubgroupAvcSicSetIntraLumaModeCostFunctionINTEL\0" // IR(41117, 48)
  "SubgroupAvcSicSetIntraChromaModeCostFunctionINTEL\0" // IR(41165, 50)
  "SubgroupAvcSicSetBilinearFilterEnableINTEL\0" // IR(41215, 43)
  "SubgroupAvcSicSetSkcForwardTransformEnableINTEL\0" // IR(41258, 48)
  "SubgroupAvcSicSetBlockBasedRawSkipSadINTEL\0" // IR(41306, 43)
  "SubgroupAvcSicEvaluateIpeINTEL\0" // IR(41349, 31)
  "SubgroupAvcSicEvaluateWithSingleReferenceINTEL\0" // IR(41380, 47)
  "SubgroupAvcSicEvaluateWithDualReferenceINTEL\0" // IR(41427, 45)
  "SubgroupAvcSicEvaluateWithMultiReferenceINTEL\0" // IR(41472, 46)
  "SubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL\0" // IR(41518, 56)
  "SubgroupAvcSicConvertToMceResultINTEL\0" // IR(41574, 38)
  "SubgroupAvcSicGetIpeLumaShapeINTEL\0" // IR(41612, 35)
  "SubgroupAvcSicGetBestIpeLumaDistortionINTEL\0" // IR(41647, 44)
  "SubgroupAvcSicGetBestIpeChromaDistortionINTEL\0" // IR(41691, 46)
  "SubgroupAvcSicGetPackedIpeLumaModesINTEL\0" // IR(41737, 41)
  "SubgroupAvcSicGetIpeChromaModeINTEL\0" // IR(41778, 36)
  "SubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL\0" // IR(41814, 50)
  "SubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL\0" // IR(41864, 48)
  "SubgroupAvcSicGetInterRawSadsINTEL\0" // IR(41912, 35)
  "SaveMemoryINTEL\0" // IR(41947, 16)
  "RestoreMemoryINTEL\0" // IR(41963, 19)
  "ArbitraryFloatSinCosPiINTEL\0" // IR(41982, 28)
  "ArbitraryFloatCastINTEL\0" // IR(42010, 24)
  "ArbitraryFloatCastFromIntINTEL\0" // IR(42034, 31)
  "ArbitraryFloatCastToIntINTEL\0" // IR(42065, 29)
  "ArbitraryFloatAddINTEL\0" // IR(42094, 23)
  "ArbitraryFloatSubINTEL\0" // IR(42117, 23)
  "ArbitraryFloatMulINTEL\0" // IR(42140, 23)
  "ArbitraryFloatDivINTEL\0" // IR(42163, 23)
  "ArbitraryFloatGTINTEL\0" // IR(42186, 22)
  "ArbitraryFloatGEINTEL\0" // IR(42208, 22)
  "ArbitraryFloatLTINTEL\0" // IR(42230, 22)
  "ArbitraryFloatLEINTEL\0" // IR(42252, 22)
  "ArbitraryFloatEQINTEL\0" // IR(42274, 22)
  "ArbitraryFloatRecipINTEL\0" // IR(42296, 25)
  "ArbitraryFloatRSqrtINTEL\0" // IR(42321, 25)
  "ArbitraryFloatCbrtINTEL\0" // IR(42346, 24)
  "ArbitraryFloatHypotINTEL\0" // IR(42370, 25)
  "ArbitraryFloatSqrtINTEL\0" // IR(42395, 24)
  "ArbitraryFloatLogINTEL\0" // IR(42419, 23)
  "ArbitraryFloatLog2INTEL\0" // IR(42442, 24)
  "ArbitraryFloatLog10INTEL\0" // IR(42466, 25)
  "ArbitraryFloatLog1pINTEL\0" // IR(42491, 25)
  "ArbitraryFloatExpINTEL\0" // IR(42516, 23)
  "ArbitraryFloatExp2INTEL\0" // IR(42539, 24)
  "ArbitraryFloatExp10INTEL\0" // IR(42563, 25)
  "ArbitraryFloatExpm1INTEL\0" // IR(42588, 25)
  "ArbitraryFloatSinINTEL\0" // IR(42613, 23)
  "ArbitraryFloatCosINTEL\0" // IR(42636, 23)
  "ArbitraryFloatSinCosINTEL\0" // IR(42659, 26)
  "ArbitraryFloatSinPiINTEL\0" // IR(42685, 25)
  "ArbitraryFloatCosPiINTEL\0" // IR(42710, 25)
  "ArbitraryFloatASinINTEL\0" // IR(42735, 24)
  "ArbitraryFloatASinPiINTEL\0" // IR(42759, 26)
  "ArbitraryFloatACosINTEL\0" // IR(42785, 24)
  "ArbitraryFloatACosPiINTEL\0" // IR(42809, 26)
  "ArbitraryFloatATanINTEL\0" // IR(42835, 24)
  "ArbitraryFloatATanPiINTEL\0" // IR(42859, 26)
  "ArbitraryFloatATan2INTEL\0" // IR(42885, 25)
  "ArbitraryFloatPowINTEL\0" // IR(42910, 23)
  "ArbitraryFloatPowRINTEL\0" // IR(42933, 24)
  "ArbitraryFloatPowNINTEL\0" // IR(42957, 24)
  "LoopControlINTEL\0" // IR(42981, 17)
  "AliasDomainDeclINTEL\0" // IR(42998, 21)
  "AliasScopeDeclINTEL\0" // IR(43019, 20)
  "AliasScopeListDeclINTEL\0" // IR(43039, 24)
  "FixedSqrtINTEL\0" // IR(43063, 15)
  "FixedRecipINTEL\0" // IR(43078, 16)
  "FixedRsqrtINTEL\0" // IR(43094, 16)
  "FixedSinINTEL\0" // IR(43110, 14)
  "FixedCosINTEL\0" // IR(43124, 14)
  "FixedSinCosINTEL\0" // IR(43138, 17)
  "FixedSinPiINTEL\0" // IR(43155, 16)
  "FixedCosPiINTEL\0" // IR(43171, 16)
  "FixedSinCosPiINTEL\0" // IR(43187, 19)
  "FixedLogINTEL\0" // IR(43206, 14)
  "FixedExpINTEL\0" // IR(43220, 14)
  "PtrCastToCrossWorkgroupINTEL\0" // IR(43234, 29)
  "CrossWorkgroupCastToPtrINTEL\0" // IR(43263, 29)
  "ReadPipeBlockingINTEL\0" // IR(43292, 22)
  "WritePipeBlockingINTEL\0" // IR(43314, 23)
  "RayQueryGetRayTMinKHR\0" // IR(43337, 22)
  "RayQueryGetRayFlagsKHR\0" // IR(43359, 23)
  "RayQueryGetIntersectionTKHR\0" // IR(43382, 28)
  "RayQueryGetIntersectionInstanceCustomIndexKHR\0" // IR(43410, 46)
  "RayQueryGetIntersectionInstanceIdKHR\0" // IR(43456, 37)
  "RayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR\0" // IR(43493, 65)
  "RayQueryGetIntersectionGeometryIndexKHR\0" // IR(43558, 40)
  "RayQueryGetIntersectionPrimitiveIndexKHR\0" // IR(43598, 41)
  "RayQueryGetIntersectionBarycentricsKHR\0" // IR(43639, 39)
  "RayQueryGetIntersectionFrontFaceKHR\0" // IR(43678, 36)
  "RayQueryGetIntersectionCandidateAABBOpaqueKHR\0" // IR(43714, 46)
  "RayQueryGetIntersectionObjectRayDirectionKHR\0" // IR(43760, 45)
  "RayQueryGetIntersectionObjectRayOriginKHR\0" // IR(43805, 42)
  "RayQueryGetWorldRayDirectionKHR\0" // IR(43847, 32)
  "RayQueryGetWorldRayOriginKHR\0" // IR(43879, 29)
  "RayQueryGetIntersectionObjectToWorldKHR\0" // IR(43908, 40)
  "RayQueryGetIntersectionWorldToObjectKHR\0" // IR(43948, 40)
  "AtomicFAddEXT\0" // IR(43988, 14)
  "TypeBufferSurfaceINTEL\0" // IR(44002, 23)
  "TypeStructContinuedINTEL\0" // IR(44025, 25)
  "ConstantCompositeContinuedINTEL\0" // IR(44050, 32)
  "SpecConstantCompositeContinuedINTEL\0" // IR(44082, 36)
  "CompositeConstructContinuedINTEL\0" // IR(44118, 33)
  "ConvertFToBF16INTEL\0" // IR(44151, 20)
  "ConvertBF16ToFINTEL\0" // IR(44171, 20)
  "ControlBarrierArriveINTEL\0" // IR(44191, 26)
  "ControlBarrierWaitINTEL\0" // IR(44217, 24)
  "TaskSequenceCreateINTEL\0" // IR(44241, 24)
  "TaskSequenceAsyncINTEL\0" // IR(44265, 23)
  "TaskSequenceGetINTEL\0" // IR(44288, 21)
  "TaskSequenceReleaseINTEL\0" // IR(44309, 25)
  "TypeTaskSequenceINTEL\0" // IR(44334, 22)
  "SubgroupBlockPrefetchINTEL\0" // IR(44356, 27)
  "Subgroup2DBlockLoadINTEL\0" // IR(44383, 25)
  "Subgroup2DBlockLoadTransformINTEL\0" // IR(44408, 34)
  "Subgroup2DBlockLoadTransposeINTEL\0" // IR(44442, 34)
  "Subgroup2DBlockPrefetchINTEL\0" // IR(44476, 29)
  "Subgroup2DBlockStoreINTEL\0" // IR(44505, 26)
  "SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS\0" // IR(44531, 62)
  "BitwiseFunctionINTEL\0" // IR(44593, 21)
  "GroupIMulKHR\0" // IR(44614, 13)
  "GroupFMulKHR\0" // IR(44627, 13)
  "GroupBitwiseAndKHR\0" // IR(44640, 19)
  "GroupBitwiseOrKHR\0" // IR(44659, 18)
  "GroupBitwiseXorKHR\0" // IR(44677, 19)
  "GroupLogicalAndKHR\0" // IR(44696, 19)
  "GroupLogicalOrKHR\0" // IR(44715, 18)
  "GroupLogicalXorKHR\0" // IR(44733, 19)
  "RoundFToTF32INTEL\0" // IR(44752, 18)
  "MaskedGatherINTEL\0" // IR(44770, 18)
  "MaskedScatterINTEL\0" // IR(44788, 19)
  "ConvertHandleToImageINTEL\0" // IR(44807, 26)
  "ConvertHandleToSamplerINTEL\0" // IR(44833, 28)
  "ConvertHandleToSampledImageINTEL\0" // IR(44861, 33)
  "DebugInfoNone\0" // IR(44894, 14)
  "DebugCompilationUnit\0" // IR(44908, 21)
  "SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING\0" // IR(44929, 52)
  "DebugTypeBasic\0" // IR(44981, 15)
  "SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS\0" // IR(44996, 34)
  "DebugTypePointer\0" // IR(45030, 17)
  "SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER\0" // IR(45047, 38)
  "DebugTypeQualifier\0" // IR(45085, 19)
  "DebugTypeArray\0" // IR(45104, 15)
  "DebugTypeVector\0" // IR(45119, 16)
  "DebugTypedef\0" // IR(45135, 13)
  "DebugTypeFunction\0" // IR(45148, 18)
  "DebugTypeEnum\0" // IR(45166, 14)
  "SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE\0" // IR(45180, 38)
  "DebugTypeComposite\0" // IR(45218, 19)
  "DebugTypeMember\0" // IR(45237, 16)
  "DebugTypeInheritance\0" // IR(45253, 21)
  "DebugTypePtrToMember\0" // IR(45274, 21)
  "DebugTypeTemplate\0" // IR(45295, 18)
  "DebugTypeTemplateParameter\0" // IR(45313, 27)
  "DebugTypeTemplateTemplateParameter\0" // IR(45340, 35)
  "DebugTypeTemplateParameterPack\0" // IR(45375, 31)
  "DebugGlobalVariable\0" // IR(45406, 20)
  "DebugFunctionDeclaration\0" // IR(45426, 25)
  "DebugFunction\0" // IR(45451, 14)
  "DebugLexicalBlock\0" // IR(45465, 18)
  "DebugLexicalBlockDiscriminator\0" // IR(45483, 31)
  "DebugScope\0" // IR(45514, 11)
  "DebugNoScope\0" // IR(45525, 13)
  "DebugInlinedAt\0" // IR(45538, 15)
  "SPV_OPERAND_TYPE_OPTIONAL_LITERAL_INTEGER\0" // IR(45553, 42)
  "DebugLocalVariable\0" // IR(45595, 19)
  "DebugInlinedVariable\0" // IR(45614, 21)
  "DebugDeclare\0" // IR(45635, 13)
  "DebugValue\0" // IR(45648, 11)
  "SPV_OPERAND_TYPE_DEBUG_OPERATION\0" // IR(45659, 33)
  "DebugOperation\0" // IR(45692, 15)
  "DebugExpression\0" // IR(45707, 16)
  "DebugMacroDef\0" // IR(45723, 14)
  "DebugMacroUndef\0" // IR(45737, 16)
  "Round\0" // IR(45753, 6)
  "RoundEven\0" // IR(45759, 10)
  "Trunc\0" // IR(45769, 6)
  "FAbs\0" // IR(45775, 5)
  "SAbs\0" // IR(45780, 5)
  "FSign\0" // IR(45785, 6)
  "SSign\0" // IR(45791, 6)
  "Floor\0" // IR(45797, 6)
  "Ceil\0" // IR(45803, 5)
  "Fract\0" // IR(45808, 6)
  "Radians\0" // IR(45814, 8)
  "Degrees\0" // IR(45822, 8)
  "Sin\0" // IR(45830, 4)
  "Cos\0" // IR(45834, 4)
  "Tan\0" // IR(45838, 4)
  "Asin\0" // IR(45842, 5)
  "Acos\0" // IR(45847, 5)
  "Atan\0" // IR(45852, 5)
  "Sinh\0" // IR(45857, 5)
  "Cosh\0" // IR(45862, 5)
  "Tanh\0" // IR(45867, 5)
  "Asinh\0" // IR(45872, 6)
  "Acosh\0" // IR(45878, 6)
  "Atanh\0" // IR(45884, 6)
  "Atan2\0" // IR(45890, 6)
  "Pow\0" // IR(45896, 4)
  "Exp\0" // IR(45900, 4)
  "Log\0" // IR(45904, 4)
  "Exp2\0" // IR(45908, 5)
  "Log2\0" // IR(45913, 5)
  "Sqrt\0" // IR(45918, 5)
  "InverseSqrt\0" // IR(45923, 12)
  "Determinant\0" // IR(45935, 12)
  "MatrixInverse\0" // IR(45947, 14)
  "Modf\0" // IR(45961, 5)
  "ModfStruct\0" // IR(45966, 11)
  "FMin\0" // IR(45977, 5)
  "UMin\0" // IR(45982, 5)
  "SMin\0" // IR(45987, 5)
  "FMax\0" // IR(45992, 5)
  "UMax\0" // IR(45997, 5)
  "SMax\0" // IR(46002, 5)
  "FClamp\0" // IR(46007, 7)
  "UClamp\0" // IR(46014, 7)
  "SClamp\0" // IR(46021, 7)
  "FMix\0" // IR(46028, 5)
  "IMix\0" // IR(46033, 5)
  "Step\0" // IR(46038, 5)
  "SmoothStep\0" // IR(46043, 11)
  "Fma\0" // IR(46054, 4)
  "Frexp\0" // IR(46058, 6)
  "FrexpStruct\0" // IR(46064, 12)
  "Ldexp\0" // IR(46076, 6)
  "PackSnorm4x8\0" // IR(46082, 13)
  "PackUnorm4x8\0" // IR(46095, 13)
  "PackSnorm2x16\0" // IR(46108, 14)
  "PackUnorm2x16\0" // IR(46122, 14)
  "PackHalf2x16\0" // IR(46136, 13)
  "PackDouble2x32\0" // IR(46149, 15)
  "UnpackSnorm2x16\0" // IR(46164, 16)
  "UnpackUnorm2x16\0" // IR(46180, 16)
  "UnpackHalf2x16\0" // IR(46196, 15)
  "UnpackSnorm4x8\0" // IR(46211, 15)
  "UnpackUnorm4x8\0" // IR(46226, 15)
  "UnpackDouble2x32\0" // IR(46241, 17)
  "Length\0" // IR(46258, 7)
  "Distance\0" // IR(46265, 9)
  "Cross\0" // IR(46274, 6)
  "Normalize\0" // IR(46280, 10)
  "FaceForward\0" // IR(46290, 12)
  "Reflect\0" // IR(46302, 8)
  "Refract\0" // IR(46310, 8)
  "FindILsb\0" // IR(46318, 9)
  "FindSMsb\0" // IR(46327, 9)
  "FindUMsb\0" // IR(46336, 9)
  "InterpolateAtCentroid\0" // IR(46345, 22)
  "InterpolateAtSample\0" // IR(46367, 20)
  "InterpolateAtOffset\0" // IR(46387, 20)
  "NMin\0" // IR(46407, 5)
  "NMax\0" // IR(46412, 5)
  "NClamp\0" // IR(46417, 7)
  "ArgumentInfo\0" // IR(46424, 13)
  "ArgumentStorageBuffer\0" // IR(46437, 22)
  "ArgumentUniform\0" // IR(46459, 16)
  "ArgumentPodStorageBuffer\0" // IR(46475, 25)
  "ArgumentPodUniform\0" // IR(46500, 19)
  "ArgumentPodPushConstant\0" // IR(46519, 24)
  "ArgumentSampledImage\0" // IR(46543, 21)
  "ArgumentStorageImage\0" // IR(46564, 21)
  "ArgumentSampler\0" // IR(46585, 16)
  "ArgumentWorkgroup\0" // IR(46601, 18)
  "SpecConstantWorkgroupSize\0" // IR(46619, 26)
  "SpecConstantGlobalOffset\0" // IR(46645, 25)
  "SpecConstantWorkDim\0" // IR(46670, 20)
  "PushConstantGlobalOffset\0" // IR(46690, 25)
  "PushConstantEnqueuedLocalSize\0" // IR(46715, 30)
  "PushConstantGlobalSize\0" // IR(46745, 23)
  "PushConstantRegionOffset\0" // IR(46768, 25)
  "PushConstantNumWorkgroups\0" // IR(46793, 26)
  "PushConstantRegionGroupOffset\0" // IR(46819, 30)
  "ConstantDataStorageBuffer\0" // IR(46849, 26)
  "ConstantDataUniform\0" // IR(46875, 20)
  "PropertyRequiredWorkgroupSize\0" // IR(46895, 30)
  "SpecConstantSubgroupMaxSize\0" // IR(46925, 28)
  "ArgumentPointerPushConstant\0" // IR(46953, 28)
  "ArgumentPointerUniform\0" // IR(46981, 23)
  "ProgramScopeVariablesStorageBuffer\0" // IR(47004, 35)
  "ProgramScopeVariablePointerRelocation\0" // IR(47039, 38)
  "ImageArgumentInfoChannelOrderPushConstant\0" // IR(47077, 42)
  "ImageArgumentInfoChannelDataTypePushConstant\0" // IR(47119, 45)
  "ImageArgumentInfoChannelOrderUniform\0" // IR(47164, 37)
  "ImageArgumentInfoChannelDataTypeUniform\0" // IR(47201, 40)
  "ArgumentStorageTexelBuffer\0" // IR(47241, 27)
  "ArgumentUniformTexelBuffer\0" // IR(47268, 27)
  "ConstantDataPointerPushConstant\0" // IR(47295, 32)
  "ProgramScopeVariablePointerPushConstant\0" // IR(47327, 40)
  "PrintfInfo\0" // IR(47367, 11)
  "PrintfBufferStorageBuffer\0" // IR(47378, 26)
  "PrintfBufferPointerPushConstant\0" // IR(47404, 32)
  "NormalizedSamplerMaskPushConstant\0" // IR(47436, 34)
  "WorkgroupVariableSize\0" // IR(47470, 22)
  "DebugImportedEntity\0" // IR(47492, 20)
  "DebugSource\0" // IR(47512, 12)
  "DebugFunctionDefinition\0" // IR(47524, 24)
  "DebugSourceContinued\0" // IR(47548, 21)
  "DebugLine\0" // IR(47569, 10)
  "DebugNoLine\0" // IR(47579, 12)
  "DebugBuildIdentifier\0" // IR(47591, 21)
  "DebugStoragePath\0" // IR(47612, 17)
  "DebugEntryPoint\0" // IR(47629, 16)
  "DebugTypeMatrix\0" // IR(47645, 16)
  "Configuration\0" // IR(47661, 14)
  "StartCounter\0" // IR(47675, 13)
  "StopCounter\0" // IR(47688, 12)
  "PushConstants\0" // IR(47700, 14)
  "SpecializationMapEntry\0" // IR(47714, 23)
  "DescriptorSetBuffer\0" // IR(47737, 20)
  "DescriptorSetImage\0" // IR(47757, 19)
  "DescriptorSetSampler\0" // IR(47776, 21)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING\0" // IR(47797, 63)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS\0" // IR(47860, 45)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER\0" // IR(47905, 49)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE\0" // IR(47954, 49)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION\0" // IR(48003, 44)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY\0" // IR(48047, 50)
  "DebugModuleINTEL\0" // IR(48097, 17)
  "acos\0" // IR(48114, 5)
  "acosh\0" // IR(48119, 6)
  "acospi\0" // IR(48125, 7)
  "asin\0" // IR(48132, 5)
  "asinh\0" // IR(48137, 6)
  "asinpi\0" // IR(48143, 7)
  "atan\0" // IR(48150, 5)
  "atan2\0" // IR(48155, 6)
  "atanh\0" // IR(48161, 6)
  "atanpi\0" // IR(48167, 7)
  "atan2pi\0" // IR(48174, 8)
  "cbrt\0" // IR(48182, 5)
  "ceil\0" // IR(48187, 5)
  "copysign\0" // IR(48192, 9)
  "cos\0" // IR(48201, 4)
  "cosh\0" // IR(48205, 5)
  "cospi\0" // IR(48210, 6)
  "erfc\0" // IR(48216, 5)
  "erf\0" // IR(48221, 4)
  "exp\0" // IR(48225, 4)
  "exp2\0" // IR(48229, 5)
  "exp10\0" // IR(48234, 6)
  "expm1\0" // IR(48240, 6)
  "fabs\0" // IR(48246, 5)
  "fdim\0" // IR(48251, 5)
  "floor\0" // IR(48256, 6)
  "fma\0" // IR(48262, 4)
  "fmax\0" // IR(48266, 5)
  "fmin\0" // IR(48271, 5)
  "fmod\0" // IR(48276, 5)
  "fract\0" // IR(48281, 6)
  "frexp\0" // IR(48287, 6)
  "hypot\0" // IR(48293, 6)
  "ilogb\0" // IR(48299, 6)
  "ldexp\0" // IR(48305, 6)
  "lgamma\0" // IR(48311, 7)
  "lgamma_r\0" // IR(48318, 9)
  "log\0" // IR(48327, 4)
  "log2\0" // IR(48331, 5)
  "log10\0" // IR(48336, 6)
  "log1p\0" // IR(48342, 6)
  "logb\0" // IR(48348, 5)
  "mad\0" // IR(48353, 4)
  "maxmag\0" // IR(48357, 7)
  "minmag\0" // IR(48364, 7)
  "modf\0" // IR(48371, 5)
  "nan\0" // IR(48376, 4)
  "nextafter\0" // IR(48380, 10)
  "pow\0" // IR(48390, 4)
  "pown\0" // IR(48394, 5)
  "powr\0" // IR(48399, 5)
  "remainder\0" // IR(48404, 10)
  "remquo\0" // IR(48414, 7)
  "rint\0" // IR(48421, 5)
  "rootn\0" // IR(48426, 6)
  "round\0" // IR(48432, 6)
  "rsqrt\0" // IR(48438, 6)
  "sin\0" // IR(48444, 4)
  "sincos\0" // IR(48448, 7)
  "sinh\0" // IR(48455, 5)
  "sinpi\0" // IR(48460, 6)
  "sqrt\0" // IR(48466, 5)
  "tan\0" // IR(48471, 4)
  "tanh\0" // IR(48475, 5)
  "tanpi\0" // IR(48480, 6)
  "tgamma\0" // IR(48486, 7)
  "trunc\0" // IR(48493, 6)
  "half_cos\0" // IR(48499, 9)
  "half_divide\0" // IR(48508, 12)
  "half_exp\0" // IR(48520, 9)
  "half_exp2\0" // IR(48529, 10)
  "half_exp10\0" // IR(48539, 11)
  "half_log\0" // IR(48550, 9)
  "half_log2\0" // IR(48559, 10)
  "half_log10\0" // IR(48569, 11)
  "half_powr\0" // IR(48580, 10)
  "half_recip\0" // IR(48590, 11)
  "half_rsqrt\0" // IR(48601, 11)
  "half_sin\0" // IR(48612, 9)
  "half_sqrt\0" // IR(48621, 10)
  "half_tan\0" // IR(48631, 9)
  "native_cos\0" // IR(48640, 11)
  "native_divide\0" // IR(48651, 14)
  "native_exp\0" // IR(48665, 11)
  "native_exp2\0" // IR(48676, 12)
  "native_exp10\0" // IR(48688, 13)
  "native_log\0" // IR(48701, 11)
  "native_log2\0" // IR(48712, 12)
  "native_log10\0" // IR(48724, 13)
  "native_powr\0" // IR(48737, 12)
  "native_recip\0" // IR(48749, 13)
  "native_rsqrt\0" // IR(48762, 13)
  "native_sin\0" // IR(48775, 11)
  "native_sqrt\0" // IR(48786, 12)
  "native_tan\0" // IR(48798, 11)
  "fclamp\0" // IR(48809, 7)
  "degrees\0" // IR(48816, 8)
  "fmax_common\0" // IR(48824, 12)
  "fmin_common\0" // IR(48836, 12)
  "mix\0" // IR(48848, 4)
  "radians\0" // IR(48852, 8)
  "step\0" // IR(48860, 5)
  "smoothstep\0" // IR(48865, 11)
  "sign\0" // IR(48876, 5)
  "cross\0" // IR(48881, 6)
  "distance\0" // IR(48887, 9)
  "length\0" // IR(48896, 7)
  "normalize\0" // IR(48903, 10)
  "fast_distance\0" // IR(48913, 14)
  "fast_length\0" // IR(48927, 12)
  "fast_normalize\0" // IR(48939, 15)
  "s_abs\0" // IR(48954, 6)
  "s_abs_diff\0" // IR(48960, 11)
  "s_add_sat\0" // IR(48971, 10)
  "u_add_sat\0" // IR(48981, 10)
  "s_hadd\0" // IR(48991, 7)
  "u_hadd\0" // IR(48998, 7)
  "s_rhadd\0" // IR(49005, 8)
  "u_rhadd\0" // IR(49013, 8)
  "s_clamp\0" // IR(49021, 8)
  "u_clamp\0" // IR(49029, 8)
  "clz\0" // IR(49037, 4)
  "ctz\0" // IR(49041, 4)
  "s_mad_hi\0" // IR(49045, 9)
  "u_mad_sat\0" // IR(49054, 10)
  "s_mad_sat\0" // IR(49064, 10)
  "s_max\0" // IR(49074, 6)
  "u_max\0" // IR(49080, 6)
  "s_min\0" // IR(49086, 6)
  "u_min\0" // IR(49092, 6)
  "s_mul_hi\0" // IR(49098, 9)
  "rotate\0" // IR(49107, 7)
  "s_sub_sat\0" // IR(49114, 10)
  "u_sub_sat\0" // IR(49124, 10)
  "u_upsample\0" // IR(49134, 11)
  "s_upsample\0" // IR(49145, 11)
  "popcount\0" // IR(49156, 9)
  "s_mad24\0" // IR(49165, 8)
  "u_mad24\0" // IR(49173, 8)
  "s_mul24\0" // IR(49181, 8)
  "u_mul24\0" // IR(49189, 8)
  "vloadn\0" // IR(49197, 7)
  "vstoren\0" // IR(49204, 8)
  "vload_half\0" // IR(49212, 11)
  "vload_halfn\0" // IR(49223, 12)
  "vstore_half\0" // IR(49235, 12)
  "vstore_half_r\0" // IR(49247, 14)
  "vstore_halfn\0" // IR(49261, 13)
  "vstore_halfn_r\0" // IR(49274, 15)
  "vloada_halfn\0" // IR(49289, 13)
  "vstorea_halfn\0" // IR(49302, 14)
  "vstorea_halfn_r\0" // IR(49316, 16)
  "shuffle\0" // IR(49332, 8)
  "shuffle2\0" // IR(49340, 9)
  "printf\0" // IR(49349, 7)
  "prefetch\0" // IR(49356, 9)
  "bitselect\0" // IR(49365, 10)
  "select\0" // IR(49375, 7)
  "u_abs\0" // IR(49382, 6)
  "u_abs_diff\0" // IR(49388, 11)
  "u_mul_hi\0" // IR(49399, 9)
  "u_mad_hi\0" // IR(49408, 9)
  "CubeFaceIndexAMD\0" // IR(49417, 17)
  "CubeFaceCoordAMD\0" // IR(49434, 17)
  "TimeAMD\0" // IR(49451, 8)
  "SwizzleInvocationsAMD\0" // IR(49459, 22)
  "SwizzleInvocationsMaskedAMD\0" // IR(49481, 28)
  "WriteInvocationAMD\0" // IR(49509, 19)
  "MbcntAMD\0" // IR(49528, 9)
  "InterpolateAtVertexAMD\0" // IR(49537, 23)
  "FMin3AMD\0" // IR(49560, 9)
  "UMin3AMD\0" // IR(49569, 9)
  "SMin3AMD\0" // IR(49578, 9)
  "FMax3AMD\0" // IR(49587, 9)
  "UMax3AMD\0" // IR(49596, 9)
  "SMax3AMD\0" // IR(49605, 9)
  "FMid3AMD\0" // IR(49614, 9)
  "UMid3AMD\0" // IR(49623, 9)
  "SMid3AMD\0" // IR(49632, 9)
;

// Array of IndexRanges, where each represents a string by referencing
// the kStrings table.
// This array contains all sequences of alias strings used in the grammar.
// This table is referenced by an IndexRange elsewhere, i.e. by the 'aliases'
// field of an instruction or operand description.
static const IndexRange kAliasSpans[] = {
  IR(4640, 27), // 0 PhysicalStorageBuffer64EXT
  IR(5551, 18), // 1 SubgroupEqMaskKHR
  IR(5606, 18), // 2 SubgroupGeMaskKHR
  IR(5639, 18), // 3 SubgroupGtMaskKHR
  IR(5672, 18), // 4 SubgroupLeMaskKHR
  IR(5705, 18), // 5 SubgroupLtMaskKHR
  IR(6563, 12), // 6 BaryCoordNV
  IR(6618, 19), // 7 BaryCoordNoPerspNV
  IR(6649, 15), // 8 FragmentSizeNV
  IR(6706, 22), // 9 InvocationsPerPixelNV
  IR(6834, 11), // 10 LaunchIdNV
  IR(6859, 13), // 11 LaunchSizeNV
  IR(6890, 17), // 12 WorldRayOriginNV
  IR(6928, 20), // 13 WorldRayDirectionNV
  IR(6967, 18), // 14 ObjectRayOriginNV
  IR(7007, 21), // 15 ObjectRayDirectionNV
  IR(7039, 10), // 16 RayTminNV
  IR(7060, 10), // 17 RayTmaxNV
  IR(7093, 22), // 18 InstanceCustomIndexNV
  IR(7132, 16), // 19 ObjectToWorldNV
  IR(7165, 16), // 20 WorldToObjectNV
  IR(7199, 10), // 21 HitKindNV
  IR(7430, 19), // 22 IncomingRayFlagsNV
  IR(9176, 28), // 23 StorageUniformBufferBlock16
  IR(9239, 17), // 24 StorageUniform16
  IR(10043, 27), // 25 ShaderViewportIndexLayerNV
  IR(10087, 22), // 26 FragmentBarycentricNV
  IR(10140, 30), // 27 ComputeDerivativeGroupQuadsNV
  IR(10170, 14), // 28 ShadingRateNV
  IR(10230, 20), // 29 ShaderNonUniformEXT
  IR(10273, 26), // 30 RuntimeDescriptorArrayEXT
  IR(10335, 39), // 31 InputAttachmentArrayDynamicIndexingEXT
  IR(10413, 42), // 32 UniformTexelBufferArrayDynamicIndexingEXT
  IR(10494, 42), // 33 StorageTexelBufferArrayDynamicIndexingEXT
  IR(10573, 40), // 34 UniformBufferArrayNonUniformIndexingEXT
  IR(10649, 39), // 35 SampledImageArrayNonUniformIndexingEXT
  IR(10725, 40), // 36 StorageBufferArrayNonUniformIndexingEXT
  IR(10801, 39), // 37 StorageImageArrayNonUniformIndexingEXT
  IR(10879, 42), // 38 InputAttachmentArrayNonUniformIndexingEXT
  IR(10963, 45), // 39 UniformTexelBufferArrayNonUniformIndexingEXT
  IR(11050, 45), // 40 StorageTexelBufferArrayNonUniformIndexingEXT
  IR(11113, 21), // 41 VulkanMemoryModelKHR
  IR(11163, 32), // 42 VulkanMemoryModelDeviceScopeKHR
  IR(11195, 34), // 43 PhysicalStorageBufferAddressesEXT
  IR(11261, 31), // 44 ComputeDerivativeGroupLinearNV
  IR(11465, 28), // 45 DemoteToHelperInvocationEXT
  IR(12935, 22), // 46 DotProductInputAllKHR
  IR(12979, 25), // 47 DotProductInput4x8BitKHR
  IR(13032, 31), // 48 DotProductInput4x8BitPackedKHR
  IR(13074, 14), // 49 DotProductKHR
  IR(13239, 13), // 50 OptNoneINTEL
  IR(16235, 15), // 51 PerPrimitiveNV
  IR(16283, 12), // 52 PerVertexNV
  IR(16306, 14), // 53 NonUniformEXT
  IR(16336, 19), // 54 RestrictPointerEXT
  IR(16370, 18), // 55 AliasedPointerEXT
  IR(16680, 24), // 56 HlslCounterBufferGOOGLE
  IR(16717, 19), // 57 HlslSemanticGOOGLE
  IR(19391, 14), // 58 OutputLinesNV
  IR(19425, 19), // 59 OutputPrimitivesNV
  IR(19468, 23), // 60 DerivativeGroupQuadsNV
  IR(19516, 24), // 61 DerivativeGroupLinearNV
  IR(19559, 18), // 62 OutputTrianglesNV
  IR(20307, 16), // 63 RayGenerationNV
  IR(20339, 15), // 64 IntersectionNV
  IR(20364, 9), // 65 AnyHitNV
  IR(20387, 13), // 66 ClosestHitNV
  IR(20408, 7), // 67 MissNV
  IR(20427, 11), // 68 CallableNV
  IR(20572, 23), // 69 AllowContractFastINTEL
  IR(20608, 18), // 70 AllowReassocINTEL
  IR(21062, 22), // 71 MakeTexelAvailableKHR
  IR(21101, 20), // 72 MakeTexelVisibleKHR
  IR(21137, 19), // 73 NonPrivateTexelKHR
  IR(21170, 17), // 74 VolatileTexelKHR
  IR(22547, 24), // 75 MakePointerAvailableKHR
  IR(22590, 22), // 76 MakePointerVisibleKHR
  IR(22630, 21), // 77 NonPrivatePointerKHR
  IR(22717, 10), // 78 VulkanKHR
  IR(14007, 5), // 79 None
  IR(22900, 16), // 80 OutputMemoryKHR
  IR(22930, 17), // 81 MakeAvailableKHR
  IR(22959, 15), // 82 MakeVisibleKHR
  IR(23035, 28), // 83 PackedVectorFormat4x8BitKHR
  IR(23350, 24), // 84 SkipBuiltinPrimitivesNV
  IR(24090, 15), // 85 QueueFamilyKHR
  IR(24461, 15), // 86 CallableDataNV
  IR(24500, 23), // 87 IncomingCallableDataNV
  IR(24537, 13), // 88 RayPayloadNV
  IR(24566, 15), // 89 HitAttributeNV
  IR(24603, 21), // 90 IncomingRayPayloadNV
  IR(24646, 21), // 91 ShaderRecordBufferNV
  IR(24689, 25), // 92 PhysicalStorageBufferEXT
  IR(31905, 8), // 93 SDotKHR
  IR(31918, 8), // 94 UDotKHR
  IR(31932, 9), // 95 SUDotKHR
  IR(31952, 14), // 96 SDotAccSatKHR
  IR(31977, 14), // 97 UDotAccSatKHR
  IR(32003, 15), // 98 SUDotAccSatKHR
  IR(34488, 21), // 99 ReportIntersectionNV
  IR(34663, 28), // 100 TypeAccelerationStructureNV
  IR(36712, 21), // 101 DecorateStringGOOGLE
  IR(36754, 27), // 102 MemberDecorateStringGOOGLE
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
  spv::Capability::Float8EXT, // 115
  spv::Capability::SampleMaskOverrideCoverageNV, // 116
  spv::Capability::GeometryShaderPassthroughNV, // 117
  spv::Capability::MeshShadingNV, // 118
  spv::Capability::MeshShadingEXT, // 119
  spv::Capability::ShaderInvocationReorderNV, // 120
  spv::Capability::BindlessTextureNV, // 121
  spv::Capability::VectorComputeINTEL, // 122
  spv::Capability::IndirectReferencesINTEL, // 123
  spv::Capability::AsmINTEL, // 124
  spv::Capability::FunctionFloatControlINTEL, // 125
  spv::Capability::FPGAMemoryAttributesINTEL, // 126
  spv::Capability::FPGAMemoryAccessesINTEL, // 127
  spv::Capability::LoopFuseINTEL, // 128
  spv::Capability::FPGADSPControlINTEL, // 129
  spv::Capability::MemoryAccessAliasingINTEL, // 130
  spv::Capability::FPGAInvocationPipeliningAttributesINTEL, // 131
  spv::Capability::FPGABufferLocationINTEL, // 132
  spv::Capability::IOPipesINTEL, // 133
  spv::Capability::FPGAClusterAttributesV2INTEL, // 134
  spv::Capability::FPMaxErrorINTEL, // 135
  spv::Capability::FPGALatencyControlINTEL, // 136
  spv::Capability::FPGAArgumentInterfacesINTEL, // 137
  spv::Capability::GlobalVariableHostAccessINTEL, // 138
  spv::Capability::GlobalVariableFPGADecorationsINTEL, // 139
  spv::Capability::CacheControlsINTEL, // 140
  spv::Capability::TileImageColorReadAccessEXT, // 141
  spv::Capability::Geometry, // 142
  spv::Capability::Tessellation, // 143
  spv::Capability::MeshShadingNV, // 144
  spv::Capability::MeshShadingEXT, // 145
  spv::Capability::Geometry, // 146
  spv::Capability::MeshShadingNV, // 147
  spv::Capability::MeshShadingEXT, // 148
  spv::Capability::SubgroupDispatch, // 149
  spv::Capability::TileImageDepthReadAccessEXT, // 150
  spv::Capability::TileImageStencilReadAccessEXT, // 151
  spv::Capability::SampleMaskPostDepthCoverage, // 152
  spv::Capability::DenormPreserve, // 153
  spv::Capability::DenormFlushToZero, // 154
  spv::Capability::SignedZeroInfNanPreserve, // 155
  spv::Capability::RoundingModeRTE, // 156
  spv::Capability::RoundingModeRTZ, // 157
  spv::Capability::QuadControlKHR, // 158
  spv::Capability::ComputeDerivativeGroupQuadsNV, // 159
  spv::Capability::ComputeDerivativeGroupQuadsKHR, // 160
  spv::Capability::ComputeDerivativeGroupLinearNV, // 161
  spv::Capability::ComputeDerivativeGroupLinearKHR, // 162
  spv::Capability::FragmentShaderPixelInterlockEXT, // 163
  spv::Capability::FragmentShaderSampleInterlockEXT, // 164
  spv::Capability::FragmentShaderShadingRateInterlockEXT, // 165
  spv::Capability::RoundToInfinityINTEL, // 166
  spv::Capability::KernelAttributesINTEL, // 167
  spv::Capability::FloatControls2, // 168
  spv::Capability::FPGAKernelAttributesv2INTEL, // 169
  spv::Capability::RegisterLimitsINTEL, // 170
  spv::Capability::FloatControls2, // 171
  spv::Capability::FPFastMathModeINTEL, // 172
  spv::Capability::OptNoneEXT, // 173
  spv::Capability::RuntimeAlignedAttributeINTEL, // 174
  spv::Capability::Kernel, // 175
  spv::Capability::GroupNonUniformArithmetic, // 176
  spv::Capability::GroupNonUniformBallot, // 177
  spv::Capability::GroupNonUniformClustered, // 178
  spv::Capability::GroupNonUniformPartitionedNV, // 179
  spv::Capability::ImageGatherExtended, // 180
  spv::Capability::MinLod, // 181
  spv::Capability::VulkanMemoryModel, // 182
  spv::Capability::FPGALoopControlsINTEL, // 183
  spv::Capability::ArbitraryPrecisionFixedPointINTEL, // 184
  spv::Capability::RawAccessChainsNV, // 185
  spv::Capability::RayTraversalPrimitiveCullingKHR, // 186
  spv::Capability::RayTracingOpacityMicromapEXT, // 187
  spv::Capability::RayQueryKHR, // 188
  spv::Capability::StorageImageExtendedFormats, // 189
  spv::Capability::Int64ImageEXT, // 190
  spv::Capability::Shader, // 191
  spv::Capability::VectorComputeINTEL, // 192
  spv::Capability::GenericPointer, // 193
  spv::Capability::FunctionPointersINTEL, // 194
  spv::Capability::USMStorageClassesINTEL, // 195
  spv::Capability::CooperativeMatrixTensorAddressingNV, // 196
  spv::Capability::CooperativeMatrixBlockLoadsNV, // 197
  spv::Capability::TensorsARM, // 198
  spv::Capability::Addresses, // 199
  spv::Capability::PhysicalStorageBufferAddresses, // 200
  spv::Capability::LiteralSampler, // 201
  spv::Capability::Addresses, // 202
  spv::Capability::UntypedPointersKHR, // 203
  spv::Capability::Addresses, // 204
  spv::Capability::VariablePointers, // 205
  spv::Capability::VariablePointersStorageBuffer, // 206
  spv::Capability::PhysicalStorageBufferAddresses, // 207
  spv::Capability::Kernel, // 208
  spv::Capability::ImageQuery, // 209
  spv::Capability::ImageQuery, // 210
  spv::Capability::Shader, // 211
  spv::Capability::BitInstructions, // 212
  spv::Capability::DerivativeControl, // 213
  spv::Capability::Groups, // 214
  spv::Capability::SparseResidency, // 215
  spv::Capability::PipeStorage, // 216
  spv::Capability::NamedBarrier, // 217
  spv::Capability::GroupNonUniformVote, // 218
  spv::Capability::GroupNonUniformBallot, // 219
  spv::Capability::GroupNonUniformShuffle, // 220
  spv::Capability::GroupNonUniformShuffleRelative, // 221
  spv::Capability::GroupNonUniformArithmetic, // 222
  spv::Capability::GroupNonUniformClustered, // 223
  spv::Capability::GroupNonUniformPartitionedNV, // 224
  spv::Capability::GroupNonUniformQuad, // 225
  spv::Capability::Addresses, // 226
  spv::Capability::VariablePointers, // 227
  spv::Capability::VariablePointersStorageBuffer, // 228
  spv::Capability::UntypedPointersKHR, // 229
  spv::Capability::SubgroupBallotKHR, // 230
  spv::Capability::SubgroupVoteKHR, // 231
  spv::Capability::GroupNonUniformRotateKHR, // 232
  spv::Capability::RayTracingKHR, // 233
  spv::Capability::RayQueryKHR, // 234
  spv::Capability::DotProduct, // 235
  spv::Capability::CooperativeMatrixKHR, // 236
  spv::Capability::ReplicatedCompositesEXT, // 237
  spv::Capability::TextureSampleWeightedQCOM, // 238
  spv::Capability::TextureBoxFilterQCOM, // 239
  spv::Capability::TextureBlockMatchQCOM, // 240
  spv::Capability::TextureBlockMatch2QCOM, // 241
  spv::Capability::FragmentMaskAMD, // 242
  spv::Capability::ShaderClockKHR, // 243
  spv::Capability::ShaderInvocationReorderNV, // 244
  spv::Capability::RayTracingMotionBlurNV, // 245
  spv::Capability::ImageFootprintNV, // 246
  spv::Capability::CooperativeVectorNV, // 247
  spv::Capability::CooperativeVectorTrainingNV, // 248
  spv::Capability::CooperativeMatrixConversionsNV, // 249
  spv::Capability::DisplacementMicromapNV, // 250
  spv::Capability::RayQueryPositionFetchKHR, // 251
  spv::Capability::RayTracingNV, // 252
  spv::Capability::RayTracingKHR, // 253
  spv::Capability::RayQueryKHR, // 254
  spv::Capability::DisplacementMicromapNV, // 255
  spv::Capability::CooperativeMatrixNV, // 256
  spv::Capability::FragmentShaderSampleInterlockEXT, // 257
  spv::Capability::FragmentShaderPixelInterlockEXT, // 258
  spv::Capability::FragmentShaderShadingRateInterlockEXT, // 259
  spv::Capability::CooperativeMatrixReductionsNV, // 260
  spv::Capability::CooperativeMatrixPerElementOperationsNV, // 261
  spv::Capability::TensorAddressingNV, // 262
  spv::Capability::DemoteToHelperInvocation, // 263
  spv::Capability::SubgroupShuffleINTEL, // 264
  spv::Capability::SubgroupBufferBlockIOINTEL, // 265
  spv::Capability::SubgroupImageBlockIOINTEL, // 266
  spv::Capability::SubgroupImageMediaBlockIOINTEL, // 267
  spv::Capability::IntegerFunctions2INTEL, // 268
  spv::Capability::AtomicFloat16MinMaxEXT, // 269
  spv::Capability::AtomicFloat32MinMaxEXT, // 270
  spv::Capability::AtomicFloat64MinMaxEXT, // 271
  spv::Capability::AtomicFloat16VectorNV, // 272
  spv::Capability::ExpectAssumeKHR, // 273
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 274
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 275
  spv::Capability::SubgroupAvcMotionEstimationIntraINTEL, // 276
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 277
  spv::Capability::SubgroupAvcMotionEstimationChromaINTEL, // 278
  spv::Capability::VariableLengthArrayINTEL, // 279
  spv::Capability::ArbitraryPrecisionFloatingPointINTEL, // 280
  spv::Capability::UnstructuredLoopControlsINTEL, // 281
  spv::Capability::BlockingPipesINTEL, // 282
  spv::Capability::FPGARegINTEL, // 283
  spv::Capability::AtomicFloat16AddEXT, // 284
  spv::Capability::AtomicFloat32AddEXT, // 285
  spv::Capability::AtomicFloat64AddEXT, // 286
  spv::Capability::AtomicFloat16VectorNV, // 287
  spv::Capability::LongCompositesINTEL, // 288
  spv::Capability::BFloat16ConversionINTEL, // 289
  spv::Capability::SplitBarrierINTEL, // 290
  spv::Capability::ArithmeticFenceEXT, // 291
  spv::Capability::TaskSequenceINTEL, // 292
  spv::Capability::SubgroupBufferPrefetchINTEL, // 293
  spv::Capability::Subgroup2DBlockTransformINTEL, // 294
  spv::Capability::Subgroup2DBlockTransposeINTEL, // 295
  spv::Capability::SubgroupMatrixMultiplyAccumulateINTEL, // 296
  spv::Capability::TernaryBitwiseFunctionINTEL, // 297
  spv::Capability::GroupUniformArithmeticKHR, // 298
  spv::Capability::TensorFloat32RoundingINTEL, // 299
  spv::Capability::MaskedGatherScatterINTEL, // 300
  spv::Capability::BindlessImagesINTEL, // 301
  spv::Capability::Float64, // 302
  spv::Capability::InterpolationFunction, // 303
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
  spvtools::Extension::kSPV_ARM_cooperative_matrix_layouts, // 37
  spvtools::Extension::kSPV_EXT_float8, // 38
  spvtools::Extension::kSPV_KHR_workgroup_memory_explicit_layout, // 39
  spvtools::Extension::kSPV_KHR_subgroup_vote, // 40
  spvtools::Extension::kSPV_KHR_16bit_storage, // 41
  spvtools::Extension::kSPV_KHR_variable_pointers, // 42
  spvtools::Extension::kSPV_KHR_shader_atomic_counter_ops, // 43
  spvtools::Extension::kSPV_KHR_post_depth_coverage, // 44
  spvtools::Extension::kSPV_KHR_8bit_storage, // 45
  spvtools::Extension::kSPV_KHR_float_controls, // 46
  spvtools::Extension::kSPV_KHR_ray_query, // 47
  spvtools::Extension::kSPV_KHR_untyped_pointers, // 48
  spvtools::Extension::kSPV_KHR_ray_query, // 49
  spvtools::Extension::kSPV_KHR_ray_tracing, // 50
  spvtools::Extension::kSPV_QCOM_image_processing, // 51
  spvtools::Extension::kSPV_QCOM_tile_shading, // 52
  spvtools::Extension::kSPV_QCOM_image_processing2, // 53
  spvtools::Extension::kSPV_AMD_gpu_shader_half_float_fetch, // 54
  spvtools::Extension::kSPV_AMD_texture_gather_bias_lod, // 55
  spvtools::Extension::kSPV_AMD_shader_fragment_mask, // 56
  spvtools::Extension::kSPV_AMD_shader_image_load_store_lod, // 57
  spvtools::Extension::kSPV_EXT_shader_image_int64, // 58
  spvtools::Extension::kSPV_KHR_shader_clock, // 59
  spvtools::Extension::kSPV_AMDX_shader_enqueue, // 60
  spvtools::Extension::kSPV_KHR_quad_control, // 61
  spvtools::Extension::kSPV_INTEL_int4, // 62
  spvtools::Extension::kSPV_KHR_bfloat16, // 63
  spvtools::Extension::kSPV_NV_sample_mask_override_coverage, // 64
  spvtools::Extension::kSPV_NV_geometry_shader_passthrough, // 65
  spvtools::Extension::kSPV_EXT_shader_viewport_index_layer, // 66
  spvtools::Extension::kSPV_NV_viewport_array2, // 67
  spvtools::Extension::kSPV_NV_viewport_array2, // 68
  spvtools::Extension::kSPV_NVX_multiview_per_view_attributes, // 69
  spvtools::Extension::kSPV_NV_shader_image_footprint, // 70
  spvtools::Extension::kSPV_NV_compute_shader_derivatives, // 71
  spvtools::Extension::kSPV_KHR_compute_shader_derivatives, // 72
  spvtools::Extension::kSPV_NV_shader_subgroup_partitioned, // 73
  spvtools::Extension::kSPV_EXT_descriptor_indexing, // 74
  spvtools::Extension::kSPV_KHR_ray_tracing_position_fetch, // 75
  spvtools::Extension::kSPV_KHR_vulkan_memory_model, // 76
  spvtools::Extension::kSPV_NV_cooperative_matrix, // 77
  spvtools::Extension::kSPV_EXT_fragment_shader_interlock, // 78
  spvtools::Extension::kSPV_EXT_demote_to_helper_invocation, // 79
  spvtools::Extension::kSPV_NV_displacement_micromap, // 80
  spvtools::Extension::kSPV_EXT_opacity_micromap, // 81
  spvtools::Extension::kSPV_NV_shader_invocation_reorder, // 82
  spvtools::Extension::kSPV_NV_bindless_texture, // 83
  spvtools::Extension::kSPV_NV_cooperative_vector, // 84
  spvtools::Extension::kSPV_NV_shader_atomic_fp16_vector, // 85
  spvtools::Extension::kSPV_NV_raw_access_chains, // 86
  spvtools::Extension::kSPV_NV_cooperative_matrix2, // 87
  spvtools::Extension::kSPV_NV_tensor_addressing, // 88
  spvtools::Extension::kSPV_INTEL_subgroups, // 89
  spvtools::Extension::kSPV_INTEL_media_block_io, // 90
  spvtools::Extension::kSPV_INTEL_float_controls2, // 91
  spvtools::Extension::kSPV_INTEL_shader_integer_functions2, // 92
  spvtools::Extension::kSPV_INTEL_function_pointers, // 93
  spvtools::Extension::kSPV_INTEL_inline_assembly, // 94
  spvtools::Extension::kSPV_EXT_shader_atomic_float_min_max, // 95
  spvtools::Extension::kSPV_INTEL_vector_compute, // 96
  spvtools::Extension::kSPV_KHR_expect_assume, // 97
  spvtools::Extension::kSPV_INTEL_device_side_avc_motion_estimation, // 98
  spvtools::Extension::kSPV_INTEL_variable_length_array, // 99
  spvtools::Extension::kSPV_INTEL_fpga_memory_attributes, // 100
  spvtools::Extension::kSPV_INTEL_fp_fast_math_mode, // 101
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_integers, // 102
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_floating_point, // 103
  spvtools::Extension::kSPV_INTEL_unstructured_loop_controls, // 104
  spvtools::Extension::kSPV_INTEL_fpga_loop_controls, // 105
  spvtools::Extension::kSPV_INTEL_kernel_attributes, // 106
  spvtools::Extension::kSPV_INTEL_fpga_memory_accesses, // 107
  spvtools::Extension::kSPV_INTEL_fpga_cluster_attributes, // 108
  spvtools::Extension::kSPV_INTEL_loop_fuse, // 109
  spvtools::Extension::kSPV_INTEL_fpga_dsp_control, // 110
  spvtools::Extension::kSPV_INTEL_memory_access_aliasing, // 111
  spvtools::Extension::kSPV_INTEL_fpga_invocation_pipelining_attributes, // 112
  spvtools::Extension::kSPV_INTEL_fpga_buffer_location, // 113
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_fixed_point, // 114
  spvtools::Extension::kSPV_INTEL_usm_storage_classes, // 115
  spvtools::Extension::kSPV_INTEL_runtime_aligned, // 116
  spvtools::Extension::kSPV_INTEL_io_pipes, // 117
  spvtools::Extension::kSPV_INTEL_blocking_pipes, // 118
  spvtools::Extension::kSPV_INTEL_fpga_reg, // 119
  spvtools::Extension::kSPV_KHR_integer_dot_product, // 120
  spvtools::Extension::kSPV_KHR_cooperative_matrix, // 121
  spvtools::Extension::kSPV_EXT_replicated_composites, // 122
  spvtools::Extension::kSPV_KHR_bit_instructions, // 123
  spvtools::Extension::kSPV_KHR_subgroup_rotate, // 124
  spvtools::Extension::kSPV_KHR_float_controls2, // 125
  spvtools::Extension::kSPV_EXT_shader_atomic_float_add, // 126
  spvtools::Extension::kSPV_INTEL_long_composites, // 127
  spvtools::Extension::kSPV_EXT_optnone, // 128
  spvtools::Extension::kSPV_INTEL_optnone, // 129
  spvtools::Extension::kSPV_EXT_shader_atomic_float16_add, // 130
  spvtools::Extension::kSPV_INTEL_debug_module, // 131
  spvtools::Extension::kSPV_INTEL_bfloat16_conversion, // 132
  spvtools::Extension::kSPV_INTEL_split_barrier, // 133
  spvtools::Extension::kSPV_EXT_arithmetic_fence, // 134
  spvtools::Extension::kSPV_INTEL_task_sequence, // 135
  spvtools::Extension::kSPV_INTEL_fp_max_error, // 136
  spvtools::Extension::kSPV_INTEL_fpga_latency_control, // 137
  spvtools::Extension::kSPV_INTEL_fpga_argument_interfaces, // 138
  spvtools::Extension::kSPV_INTEL_global_variable_host_access, // 139
  spvtools::Extension::kSPV_INTEL_global_variable_fpga_decorations, // 140
  spvtools::Extension::kSPV_INTEL_subgroup_buffer_prefetch, // 141
  spvtools::Extension::kSPV_INTEL_2d_block_io, // 142
  spvtools::Extension::kSPV_INTEL_subgroup_matrix_multiply_accumulate, // 143
  spvtools::Extension::kSPV_INTEL_ternary_bitwise_function, // 144
  spvtools::Extension::kSPV_KHR_uniform_group_instructions, // 145
  spvtools::Extension::kSPV_INTEL_tensor_float32_conversion, // 146
  spvtools::Extension::kSPV_INTEL_masked_gather_scatter, // 147
  spvtools::Extension::kSPV_INTEL_cache_controls, // 148
  spvtools::Extension::kSPV_INTEL_maximum_registers, // 149
  spvtools::Extension::kSPV_INTEL_bindless_images, // 150
  spvtools::Extension::kSPV_KHR_no_integer_wrap_decoration, // 151
  spvtools::Extension::kSPV_NV_mesh_shader, // 152
  spvtools::Extension::kSPV_EXT_mesh_shader, // 153
  spvtools::Extension::kSPV_GOOGLE_hlsl_functionality1, // 154
  spvtools::Extension::kSPV_GOOGLE_user_type, // 155
  spvtools::Extension::kSPV_KHR_subgroup_uniform_control_flow, // 156
  spvtools::Extension::kSPV_AMD_shader_early_and_late_fragment_tests, // 157
  spvtools::Extension::kSPV_AMD_shader_early_and_late_fragment_tests, // 158
  spvtools::Extension::kSPV_EXT_shader_stencil_export, // 159
  spvtools::Extension::kSPV_KHR_maximal_reconvergence, // 160
  spvtools::Extension::kSPV_KHR_linkonce_odr, // 161
  spvtools::Extension::kSPV_KHR_storage_buffer_storage_class, // 162
  spvtools::Extension::kSPV_KHR_variable_pointers, // 163
  spvtools::Extension::kSPV_KHR_terminate_invocation, // 164
  spvtools::Extension::kSPV_KHR_relaxed_extended_instruction, // 165
  spvtools::Extension::kSPV_KHR_ray_tracing, // 166
  spvtools::Extension::kSPV_KHR_ray_query, // 167
  spvtools::Extension::kSPV_NV_ray_tracing, // 168
  spvtools::Extension::kSPV_KHR_ray_tracing, // 169
  spvtools::Extension::kSPV_KHR_ray_query, // 170
  spvtools::Extension::kSPV_NV_displacement_micromap, // 171
  spvtools::Extension::kSPV_GOOGLE_decorate_string, // 172
  spvtools::Extension::kSPV_GOOGLE_hlsl_functionality1, // 173
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
  SPV_OPERAND_TYPE_RESULT_ID, // 369
  SPV_OPERAND_TYPE_STORAGE_CLASS, // 370
  SPV_OPERAND_TYPE_TYPE_ID, // 371
  SPV_OPERAND_TYPE_RESULT_ID, // 372
  SPV_OPERAND_TYPE_STORAGE_CLASS, // 373
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 374
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 375
  SPV_OPERAND_TYPE_TYPE_ID, // 376
  SPV_OPERAND_TYPE_RESULT_ID, // 377
  SPV_OPERAND_TYPE_ID, // 378
  SPV_OPERAND_TYPE_ID, // 379
  SPV_OPERAND_TYPE_ID, // 380
  SPV_OPERAND_TYPE_VARIABLE_ID, // 381
  SPV_OPERAND_TYPE_TYPE_ID, // 382
  SPV_OPERAND_TYPE_RESULT_ID, // 383
  SPV_OPERAND_TYPE_ID, // 384
  SPV_OPERAND_TYPE_ID, // 385
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 386
  SPV_OPERAND_TYPE_ID, // 387
  SPV_OPERAND_TYPE_ID, // 388
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 389
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 390
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 391
  SPV_OPERAND_TYPE_TYPE_ID, // 392
  SPV_OPERAND_TYPE_RESULT_ID, // 393
  SPV_OPERAND_TYPE_SCOPE_ID, // 394
  SPV_OPERAND_TYPE_ID, // 395
  SPV_OPERAND_TYPE_ID, // 396
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 397
  SPV_OPERAND_TYPE_TYPE_ID, // 398
  SPV_OPERAND_TYPE_RESULT_ID, // 399
  SPV_OPERAND_TYPE_ID, // 400
  SPV_OPERAND_TYPE_EXTENSION_INSTRUCTION_NUMBER, // 401
  SPV_OPERAND_TYPE_VARIABLE_ID, // 402
  SPV_OPERAND_TYPE_ID, // 403
  SPV_OPERAND_TYPE_ID, // 404
  SPV_OPERAND_TYPE_ID, // 405
  SPV_OPERAND_TYPE_ID, // 406
  SPV_OPERAND_TYPE_ID, // 407
  SPV_OPERAND_TYPE_ID, // 408
  SPV_OPERAND_TYPE_ID, // 409
  SPV_OPERAND_TYPE_ID, // 410
  SPV_OPERAND_TYPE_ID, // 411
  SPV_OPERAND_TYPE_ID, // 412
  SPV_OPERAND_TYPE_ID, // 413
  SPV_OPERAND_TYPE_TYPE_ID, // 414
  SPV_OPERAND_TYPE_RESULT_ID, // 415
  SPV_OPERAND_TYPE_ID, // 416
  SPV_OPERAND_TYPE_ID, // 417
  SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT, // 418
  SPV_OPERAND_TYPE_TYPE_ID, // 419
  SPV_OPERAND_TYPE_RESULT_ID, // 420
  SPV_OPERAND_TYPE_ID, // 421
  SPV_OPERAND_TYPE_ID, // 422
  SPV_OPERAND_TYPE_ID, // 423
  SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT, // 424
  SPV_OPERAND_TYPE_RESULT_ID, // 425
  SPV_OPERAND_TYPE_ID, // 426
  SPV_OPERAND_TYPE_SCOPE_ID, // 427
  SPV_OPERAND_TYPE_ID, // 428
  SPV_OPERAND_TYPE_ID, // 429
  SPV_OPERAND_TYPE_ID, // 430
  SPV_OPERAND_TYPE_TYPE_ID, // 431
  SPV_OPERAND_TYPE_RESULT_ID, // 432
  SPV_OPERAND_TYPE_ID, // 433
  SPV_OPERAND_TYPE_ID, // 434
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 435
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 436
  SPV_OPERAND_TYPE_ID, // 437
  SPV_OPERAND_TYPE_ID, // 438
  SPV_OPERAND_TYPE_ID, // 439
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 440
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 441
  SPV_OPERAND_TYPE_TYPE_ID, // 442
  SPV_OPERAND_TYPE_RESULT_ID, // 443
  SPV_OPERAND_TYPE_ID, // 444
  SPV_OPERAND_TYPE_ID, // 445
  SPV_OPERAND_TYPE_ID, // 446
  SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS, // 447
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
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 509
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 510
  SPV_OPERAND_TYPE_TYPE_ID, // 511
  SPV_OPERAND_TYPE_RESULT_ID, // 512
  SPV_OPERAND_TYPE_ID, // 513
  SPV_OPERAND_TYPE_ID, // 514
  SPV_OPERAND_TYPE_ID, // 515
  SPV_OPERAND_TYPE_ID, // 516
  SPV_OPERAND_TYPE_OPTIONAL_IMAGE, // 517
  SPV_OPERAND_TYPE_TYPE_ID, // 518
  SPV_OPERAND_TYPE_RESULT_ID, // 519
  SPV_OPERAND_TYPE_ID, // 520
  SPV_OPERAND_TYPE_ID, // 521
  SPV_OPERAND_TYPE_ID, // 522
  SPV_OPERAND_TYPE_ID, // 523
  SPV_OPERAND_TYPE_ID, // 524
  SPV_OPERAND_TYPE_ID, // 525
  SPV_OPERAND_TYPE_ID, // 526
  SPV_OPERAND_TYPE_ID, // 527
  SPV_OPERAND_TYPE_ID, // 528
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 529
  SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS, // 530
  SPV_OPERAND_TYPE_ID, // 531
  SPV_OPERAND_TYPE_ID, // 532
  SPV_OPERAND_TYPE_ID, // 533
  SPV_OPERAND_TYPE_ID, // 534
  SPV_OPERAND_TYPE_ID, // 535
  SPV_OPERAND_TYPE_ID, // 536
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 537
  SPV_OPERAND_TYPE_TYPE_ID, // 538
  SPV_OPERAND_TYPE_RESULT_ID, // 539
  SPV_OPERAND_TYPE_ID, // 540
  SPV_OPERAND_TYPE_ID, // 541
  SPV_OPERAND_TYPE_ID, // 542
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
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 557
  SPV_OPERAND_TYPE_TYPE_ID, // 558
  SPV_OPERAND_TYPE_RESULT_ID, // 559
  SPV_OPERAND_TYPE_ID, // 560
  SPV_OPERAND_TYPE_ID, // 561
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 562
  SPV_OPERAND_TYPE_ID, // 563
  SPV_OPERAND_TYPE_ID, // 564
  SPV_OPERAND_TYPE_ID, // 565
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 566
  SPV_OPERAND_TYPE_RESULT_ID, // 567
  SPV_OPERAND_TYPE_ID, // 568
  SPV_OPERAND_TYPE_SCOPE_ID, // 569
  SPV_OPERAND_TYPE_ID, // 570
  SPV_OPERAND_TYPE_ID, // 571
  SPV_OPERAND_TYPE_TYPE_ID, // 572
  SPV_OPERAND_TYPE_RESULT_ID, // 573
  SPV_OPERAND_TYPE_ID, // 574
  SPV_OPERAND_TYPE_ID, // 575
  SPV_OPERAND_TYPE_ID, // 576
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 577
  SPV_OPERAND_TYPE_ID, // 578
  SPV_OPERAND_TYPE_ID, // 579
  SPV_OPERAND_TYPE_ID, // 580
  SPV_OPERAND_TYPE_ID, // 581
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 582
  SPV_OPERAND_TYPE_TYPE_ID, // 583
  SPV_OPERAND_TYPE_RESULT_ID, // 584
  SPV_OPERAND_TYPE_ID, // 585
  SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE, // 586
  SPV_OPERAND_TYPE_ID, // 587
  SPV_OPERAND_TYPE_TYPE_ID, // 588
  SPV_OPERAND_TYPE_RESULT_ID, // 589
  SPV_OPERAND_TYPE_ID, // 590
  SPV_OPERAND_TYPE_ID, // 591
  SPV_OPERAND_TYPE_ID, // 592
  SPV_OPERAND_TYPE_MEMORY_ACCESS, // 593
  SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS, // 594
  SPV_OPERAND_TYPE_ID, // 595
  SPV_OPERAND_TYPE_ID, // 596
  SPV_OPERAND_TYPE_ID, // 597
  SPV_OPERAND_TYPE_MEMORY_ACCESS, // 598
  SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS, // 599
  SPV_OPERAND_TYPE_RESULT_ID, // 600
  SPV_OPERAND_TYPE_ID, // 601
  SPV_OPERAND_TYPE_ID, // 602
  SPV_OPERAND_TYPE_VARIABLE_ID, // 603
  SPV_OPERAND_TYPE_TYPE_ID, // 604
  SPV_OPERAND_TYPE_RESULT_ID, // 605
  SPV_OPERAND_TYPE_ID, // 606
  SPV_OPERAND_TYPE_ID, // 607
  SPV_OPERAND_TYPE_ID, // 608
  SPV_OPERAND_TYPE_ID, // 609
  SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS, // 610
  SPV_OPERAND_TYPE_ID, // 611
  SPV_OPERAND_TYPE_ID, // 612
  SPV_OPERAND_TYPE_ID, // 613
  SPV_OPERAND_TYPE_ID, // 614
  SPV_OPERAND_TYPE_ID, // 615
  SPV_OPERAND_TYPE_TYPE_ID, // 616
  SPV_OPERAND_TYPE_RESULT_ID, // 617
  SPV_OPERAND_TYPE_ID, // 618
  SPV_OPERAND_TYPE_ID, // 619
  SPV_OPERAND_TYPE_LITERAL_STRING, // 620
  SPV_OPERAND_TYPE_LITERAL_STRING, // 621
  SPV_OPERAND_TYPE_TYPE_ID, // 622
  SPV_OPERAND_TYPE_RESULT_ID, // 623
  SPV_OPERAND_TYPE_ID, // 624
  SPV_OPERAND_TYPE_ID, // 625
  SPV_OPERAND_TYPE_ID, // 626
  SPV_OPERAND_TYPE_ID, // 627
  SPV_OPERAND_TYPE_ID, // 628
  SPV_OPERAND_TYPE_ID, // 629
  SPV_OPERAND_TYPE_ID, // 630
  SPV_OPERAND_TYPE_TYPE_ID, // 631
  SPV_OPERAND_TYPE_RESULT_ID, // 632
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
  SPV_OPERAND_TYPE_ID, // 644
  SPV_OPERAND_TYPE_ID, // 645
  SPV_OPERAND_TYPE_ID, // 646
  SPV_OPERAND_TYPE_ID, // 647
  SPV_OPERAND_TYPE_ID, // 648
  SPV_OPERAND_TYPE_ID, // 649
  SPV_OPERAND_TYPE_ID, // 650
  SPV_OPERAND_TYPE_ID, // 651
  SPV_OPERAND_TYPE_ID, // 652
  SPV_OPERAND_TYPE_ID, // 653
  SPV_OPERAND_TYPE_TYPE_ID, // 654
  SPV_OPERAND_TYPE_RESULT_ID, // 655
  SPV_OPERAND_TYPE_ID, // 656
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 657
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 658
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 659
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 660
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 661
  SPV_OPERAND_TYPE_TYPE_ID, // 662
  SPV_OPERAND_TYPE_RESULT_ID, // 663
  SPV_OPERAND_TYPE_ID, // 664
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 665
  SPV_OPERAND_TYPE_ID, // 666
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 667
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 668
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 669
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 670
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 671
  SPV_OPERAND_TYPE_TYPE_ID, // 672
  SPV_OPERAND_TYPE_RESULT_ID, // 673
  SPV_OPERAND_TYPE_ID, // 674
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 675
  SPV_OPERAND_TYPE_ID, // 676
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 677
  SPV_OPERAND_TYPE_RESULT_ID, // 678
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 679
  SPV_OPERAND_TYPE_RESULT_ID, // 680
  SPV_OPERAND_TYPE_ID, // 681
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 682
  SPV_OPERAND_TYPE_VARIABLE_ID, // 683
  SPV_OPERAND_TYPE_TYPE_ID, // 684
  SPV_OPERAND_TYPE_RESULT_ID, // 685
  SPV_OPERAND_TYPE_ID, // 686
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 687
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 688
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 689
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 690
  SPV_OPERAND_TYPE_ID, // 691
  SPV_OPERAND_TYPE_ID, // 692
  SPV_OPERAND_TYPE_ID, // 693
  SPV_OPERAND_TYPE_ID, // 694
  SPV_OPERAND_TYPE_ID, // 695
  SPV_OPERAND_TYPE_ID, // 696
  SPV_OPERAND_TYPE_ID, // 697
  SPV_OPERAND_TYPE_ID, // 698
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
  SPV_OPERAND_TYPE_ID, // 713
  SPV_OPERAND_TYPE_ID, // 714
  SPV_OPERAND_TYPE_ID, // 715
  SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS, // 716
  SPV_OPERAND_TYPE_TYPE_ID, // 717
  SPV_OPERAND_TYPE_RESULT_ID, // 718
  SPV_OPERAND_TYPE_ID, // 719
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 720
  SPV_OPERAND_TYPE_ID, // 721
  SPV_OPERAND_TYPE_ID, // 722
  SPV_OPERAND_TYPE_ID, // 723
  SPV_OPERAND_TYPE_ID, // 724
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 725
  SPV_OPERAND_TYPE_ID, // 726
  SPV_OPERAND_TYPE_ID, // 727
  SPV_OPERAND_TYPE_ID, // 728
  SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING, // 729
  SPV_OPERAND_TYPE_ID, // 730
  SPV_OPERAND_TYPE_STORAGE_CLASS, // 731
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 732
  SPV_OPERAND_TYPE_ID, // 733
  SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER, // 734
  SPV_OPERAND_TYPE_ID, // 735
  SPV_OPERAND_TYPE_ID, // 736
  SPV_OPERAND_TYPE_ID, // 737
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 738
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 739
  SPV_OPERAND_TYPE_ID, // 740
  SPV_OPERAND_TYPE_ID, // 741
  SPV_OPERAND_TYPE_ID, // 742
  SPV_OPERAND_TYPE_ID, // 743
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 744
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 745
  SPV_OPERAND_TYPE_ID, // 746
  SPV_OPERAND_TYPE_ID, // 747
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 748
  SPV_OPERAND_TYPE_VARIABLE_ID, // 749
  SPV_OPERAND_TYPE_ID, // 750
  SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE, // 751
  SPV_OPERAND_TYPE_ID, // 752
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 753
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 754
  SPV_OPERAND_TYPE_ID, // 755
  SPV_OPERAND_TYPE_ID, // 756
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 757
  SPV_OPERAND_TYPE_VARIABLE_ID, // 758
  SPV_OPERAND_TYPE_ID, // 759
  SPV_OPERAND_TYPE_ID, // 760
  SPV_OPERAND_TYPE_ID, // 761
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 762
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 763
  SPV_OPERAND_TYPE_ID, // 764
  SPV_OPERAND_TYPE_ID, // 765
  SPV_OPERAND_TYPE_ID, // 766
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 767
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 768
  SPV_OPERAND_TYPE_ID, // 769
  SPV_OPERAND_TYPE_ID, // 770
  SPV_OPERAND_TYPE_ID, // 771
  SPV_OPERAND_TYPE_ID, // 772
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 773
  SPV_OPERAND_TYPE_ID, // 774
  SPV_OPERAND_TYPE_ID, // 775
  SPV_OPERAND_TYPE_ID, // 776
  SPV_OPERAND_TYPE_ID, // 777
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 778
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 779
  SPV_OPERAND_TYPE_ID, // 780
  SPV_OPERAND_TYPE_ID, // 781
  SPV_OPERAND_TYPE_ID, // 782
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 783
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 784
  SPV_OPERAND_TYPE_ID, // 785
  SPV_OPERAND_TYPE_ID, // 786
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 787
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 788
  SPV_OPERAND_TYPE_VARIABLE_ID, // 789
  SPV_OPERAND_TYPE_ID, // 790
  SPV_OPERAND_TYPE_ID, // 791
  SPV_OPERAND_TYPE_ID, // 792
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 793
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 794
  SPV_OPERAND_TYPE_ID, // 795
  SPV_OPERAND_TYPE_ID, // 796
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 797
  SPV_OPERAND_TYPE_ID, // 798
  SPV_OPERAND_TYPE_ID, // 799
  SPV_OPERAND_TYPE_ID, // 800
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 801
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 802
  SPV_OPERAND_TYPE_ID, // 803
  SPV_OPERAND_TYPE_ID, // 804
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 805
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 806
  SPV_OPERAND_TYPE_ID, // 807
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 808
  SPV_OPERAND_TYPE_ID, // 809
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 810
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 811
  SPV_OPERAND_TYPE_ID, // 812
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 813
  SPV_OPERAND_TYPE_ID, // 814
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 815
  SPV_OPERAND_TYPE_ID, // 816
  SPV_OPERAND_TYPE_ID, // 817
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 818
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 819
  SPV_OPERAND_TYPE_ID, // 820
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 821
  SPV_OPERAND_TYPE_ID, // 822
  SPV_OPERAND_TYPE_ID, // 823
  SPV_OPERAND_TYPE_ID, // 824
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 825
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 826
  SPV_OPERAND_TYPE_ID, // 827
  SPV_OPERAND_TYPE_OPTIONAL_LITERAL_INTEGER, // 828
  SPV_OPERAND_TYPE_ID, // 829
  SPV_OPERAND_TYPE_ID, // 830
  SPV_OPERAND_TYPE_VARIABLE_ID, // 831
  SPV_OPERAND_TYPE_DEBUG_OPERATION, // 832
  SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER, // 833
  SPV_OPERAND_TYPE_ID, // 834
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 835
  SPV_OPERAND_TYPE_ID, // 836
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 837
  SPV_OPERAND_TYPE_ID, // 838
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 839
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 840
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 841
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 842
  SPV_OPERAND_TYPE_ID, // 843
  SPV_OPERAND_TYPE_ID, // 844
  SPV_OPERAND_TYPE_ID, // 845
  SPV_OPERAND_TYPE_ID, // 846
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 847
  SPV_OPERAND_TYPE_ID, // 848
  SPV_OPERAND_TYPE_ID, // 849
  SPV_OPERAND_TYPE_ID, // 850
  SPV_OPERAND_TYPE_ID, // 851
  SPV_OPERAND_TYPE_ID, // 852
  SPV_OPERAND_TYPE_ID, // 853
  SPV_OPERAND_TYPE_ID, // 854
  SPV_OPERAND_TYPE_ID, // 855
  SPV_OPERAND_TYPE_VARIABLE_ID, // 856
  SPV_OPERAND_TYPE_ID, // 857
  SPV_OPERAND_TYPE_ID, // 858
  SPV_OPERAND_TYPE_ID, // 859
  SPV_OPERAND_TYPE_ID, // 860
  SPV_OPERAND_TYPE_ID, // 861
  SPV_OPERAND_TYPE_ID, // 862
  SPV_OPERAND_TYPE_ID, // 863
  SPV_OPERAND_TYPE_ID, // 864
  SPV_OPERAND_TYPE_ID, // 865
  SPV_OPERAND_TYPE_VARIABLE_ID, // 866
  SPV_OPERAND_TYPE_ID, // 867
  SPV_OPERAND_TYPE_ID, // 868
  SPV_OPERAND_TYPE_ID, // 869
  SPV_OPERAND_TYPE_ID, // 870
  SPV_OPERAND_TYPE_ID, // 871
  SPV_OPERAND_TYPE_ID, // 872
  SPV_OPERAND_TYPE_ID, // 873
  SPV_OPERAND_TYPE_ID, // 874
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 875
  SPV_OPERAND_TYPE_ID, // 876
  SPV_OPERAND_TYPE_ID, // 877
  SPV_OPERAND_TYPE_ID, // 878
  SPV_OPERAND_TYPE_ID, // 879
  SPV_OPERAND_TYPE_VARIABLE_ID, // 880
  SPV_OPERAND_TYPE_ID, // 881
  SPV_OPERAND_TYPE_ID, // 882
  SPV_OPERAND_TYPE_ID, // 883
  SPV_OPERAND_TYPE_ID, // 884
  SPV_OPERAND_TYPE_ID, // 885
  SPV_OPERAND_TYPE_ID, // 886
  SPV_OPERAND_TYPE_ID, // 887
  SPV_OPERAND_TYPE_ID, // 888
  SPV_OPERAND_TYPE_ID, // 889
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 890
  SPV_OPERAND_TYPE_ID, // 891
  SPV_OPERAND_TYPE_ID, // 892
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 893
  SPV_OPERAND_TYPE_ID, // 894
  SPV_OPERAND_TYPE_ID, // 895
  SPV_OPERAND_TYPE_ID, // 896
  SPV_OPERAND_TYPE_ID, // 897
  SPV_OPERAND_TYPE_ID, // 898
  SPV_OPERAND_TYPE_ID, // 899
  SPV_OPERAND_TYPE_ID, // 900
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 901
  SPV_OPERAND_TYPE_ID, // 902
  SPV_OPERAND_TYPE_ID, // 903
  SPV_OPERAND_TYPE_ID, // 904
  SPV_OPERAND_TYPE_VARIABLE_ID, // 905
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
  SPV_OPERAND_TYPE_ID, // 960
  SPV_OPERAND_TYPE_ID, // 961
  SPV_OPERAND_TYPE_ID, // 962
  SPV_OPERAND_TYPE_ID, // 963
  SPV_OPERAND_TYPE_ID, // 964
  SPV_OPERAND_TYPE_ID, // 965
  SPV_OPERAND_TYPE_ID, // 966
  SPV_OPERAND_TYPE_ID, // 967
  SPV_OPERAND_TYPE_ID, // 968
  SPV_OPERAND_TYPE_ID, // 969
  SPV_OPERAND_TYPE_ID, // 970
  SPV_OPERAND_TYPE_ID, // 971
  SPV_OPERAND_TYPE_ID, // 972
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 973
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 974
  SPV_OPERAND_TYPE_ID, // 975
  SPV_OPERAND_TYPE_SOURCE_LANGUAGE, // 976
  SPV_OPERAND_TYPE_ID, // 977
  SPV_OPERAND_TYPE_ID, // 978
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING, // 979
  SPV_OPERAND_TYPE_ID, // 980
  SPV_OPERAND_TYPE_STORAGE_CLASS, // 981
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 982
  SPV_OPERAND_TYPE_ID, // 983
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER, // 984
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 985
  SPV_OPERAND_TYPE_ID, // 986
  SPV_OPERAND_TYPE_VARIABLE_ID, // 987
  SPV_OPERAND_TYPE_ID, // 988
  SPV_OPERAND_TYPE_ID, // 989
  SPV_OPERAND_TYPE_ID, // 990
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 991
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 992
  SPV_OPERAND_TYPE_ID, // 993
  SPV_OPERAND_TYPE_ID, // 994
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 995
  SPV_OPERAND_TYPE_VARIABLE_ID, // 996
  SPV_OPERAND_TYPE_ID, // 997
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE, // 998
  SPV_OPERAND_TYPE_ID, // 999
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1000
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1001
  SPV_OPERAND_TYPE_ID, // 1002
  SPV_OPERAND_TYPE_ID, // 1003
  SPV_OPERAND_TYPE_ID, // 1004
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1005
  SPV_OPERAND_TYPE_VARIABLE_ID, // 1006
  SPV_OPERAND_TYPE_ID, // 1007
  SPV_OPERAND_TYPE_ID, // 1008
  SPV_OPERAND_TYPE_ID, // 1009
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1010
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1011
  SPV_OPERAND_TYPE_ID, // 1012
  SPV_OPERAND_TYPE_ID, // 1013
  SPV_OPERAND_TYPE_ID, // 1014
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1015
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 1016
  SPV_OPERAND_TYPE_ID, // 1017
  SPV_OPERAND_TYPE_ID, // 1018
  SPV_OPERAND_TYPE_ID, // 1019
  SPV_OPERAND_TYPE_ID, // 1020
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1021
  SPV_OPERAND_TYPE_ID, // 1022
  SPV_OPERAND_TYPE_ID, // 1023
  SPV_OPERAND_TYPE_ID, // 1024
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1025
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1026
  SPV_OPERAND_TYPE_ID, // 1027
  SPV_OPERAND_TYPE_ID, // 1028
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1029
  SPV_OPERAND_TYPE_ID, // 1030
  SPV_OPERAND_TYPE_ID, // 1031
  SPV_OPERAND_TYPE_ID, // 1032
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1033
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1034
  SPV_OPERAND_TYPE_ID, // 1035
  SPV_OPERAND_TYPE_ID, // 1036
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1037
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1038
  SPV_OPERAND_TYPE_ID, // 1039
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 1040
  SPV_OPERAND_TYPE_ID, // 1041
  SPV_OPERAND_TYPE_ID, // 1042
  SPV_OPERAND_TYPE_ID, // 1043
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1044
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1045
  SPV_OPERAND_TYPE_ID, // 1046
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1047
  SPV_OPERAND_TYPE_OPTIONAL_LITERAL_INTEGER, // 1048
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION, // 1049
  SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER, // 1050
  SPV_OPERAND_TYPE_ID, // 1051
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY, // 1052
  SPV_OPERAND_TYPE_ID, // 1053
  SPV_OPERAND_TYPE_ID, // 1054
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1055
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1056
  SPV_OPERAND_TYPE_ID, // 1057
  SPV_OPERAND_TYPE_ID, // 1058
  SPV_OPERAND_TYPE_ID, // 1059
  SPV_OPERAND_TYPE_ID, // 1060
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1061
  SPV_OPERAND_TYPE_ID, // 1062
  SPV_OPERAND_TYPE_ID, // 1063
  SPV_OPERAND_TYPE_ID, // 1064
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1065
  SPV_OPERAND_TYPE_ID, // 1066
  SPV_OPERAND_TYPE_ID, // 1067
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1068
  SPV_OPERAND_TYPE_ID, // 1069
  SPV_OPERAND_TYPE_ID, // 1070
  SPV_OPERAND_TYPE_ID, // 1071
  SPV_OPERAND_TYPE_FP_ROUNDING_MODE, // 1072
};
