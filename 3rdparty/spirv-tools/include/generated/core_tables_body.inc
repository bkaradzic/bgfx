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
    case Extension::kSPV_EXT_descriptor_indexing: return IR(1168, 28);
    case Extension::kSPV_EXT_float8: return IR(1196, 15);
    case Extension::kSPV_EXT_fragment_fully_covered: return IR(1211, 31);
    case Extension::kSPV_EXT_fragment_invocation_density: return IR(1242, 36);
    case Extension::kSPV_EXT_fragment_shader_interlock: return IR(1278, 34);
    case Extension::kSPV_EXT_long_vector: return IR(1312, 20);
    case Extension::kSPV_EXT_mesh_shader: return IR(1332, 20);
    case Extension::kSPV_EXT_opacity_micromap: return IR(1352, 25);
    case Extension::kSPV_EXT_optnone: return IR(1377, 16);
    case Extension::kSPV_EXT_physical_storage_buffer: return IR(1393, 32);
    case Extension::kSPV_EXT_relaxed_printf_string_address_space: return IR(1425, 44);
    case Extension::kSPV_EXT_replicated_composites: return IR(1469, 30);
    case Extension::kSPV_EXT_shader_64bit_indexing: return IR(1499, 30);
    case Extension::kSPV_EXT_shader_atomic_float16_add: return IR(1529, 34);
    case Extension::kSPV_EXT_shader_atomic_float_add: return IR(1563, 32);
    case Extension::kSPV_EXT_shader_atomic_float_min_max: return IR(1595, 36);
    case Extension::kSPV_EXT_shader_image_int64: return IR(1631, 27);
    case Extension::kSPV_EXT_shader_invocation_reorder: return IR(1658, 34);
    case Extension::kSPV_EXT_shader_stencil_export: return IR(1692, 30);
    case Extension::kSPV_EXT_shader_tile_image: return IR(1722, 26);
    case Extension::kSPV_EXT_shader_viewport_index_layer: return IR(1748, 36);
    case Extension::kSPV_GOOGLE_decorate_string: return IR(1784, 27);
    case Extension::kSPV_GOOGLE_hlsl_functionality1: return IR(1811, 31);
    case Extension::kSPV_GOOGLE_user_type: return IR(1842, 21);
    case Extension::kSPV_INTEL_2d_block_io: return IR(1863, 22);
    case Extension::kSPV_INTEL_arbitrary_precision_fixed_point: return IR(1885, 42);
    case Extension::kSPV_INTEL_arbitrary_precision_floating_point: return IR(1927, 45);
    case Extension::kSPV_INTEL_arbitrary_precision_integers: return IR(1972, 39);
    case Extension::kSPV_INTEL_bfloat16_conversion: return IR(2011, 30);
    case Extension::kSPV_INTEL_bindless_images: return IR(2041, 26);
    case Extension::kSPV_INTEL_blocking_pipes: return IR(2067, 25);
    case Extension::kSPV_INTEL_cache_controls: return IR(2092, 25);
    case Extension::kSPV_INTEL_debug_module: return IR(2117, 23);
    case Extension::kSPV_INTEL_device_side_avc_motion_estimation: return IR(2140, 44);
    case Extension::kSPV_INTEL_float_controls2: return IR(2184, 26);
    case Extension::kSPV_INTEL_fp_fast_math_mode: return IR(2210, 28);
    case Extension::kSPV_INTEL_fp_max_error: return IR(2238, 23);
    case Extension::kSPV_INTEL_fpga_argument_interfaces: return IR(2261, 35);
    case Extension::kSPV_INTEL_fpga_buffer_location: return IR(2296, 31);
    case Extension::kSPV_INTEL_fpga_cluster_attributes: return IR(2327, 34);
    case Extension::kSPV_INTEL_fpga_dsp_control: return IR(2361, 27);
    case Extension::kSPV_INTEL_fpga_invocation_pipelining_attributes: return IR(2388, 48);
    case Extension::kSPV_INTEL_fpga_latency_control: return IR(2436, 31);
    case Extension::kSPV_INTEL_fpga_loop_controls: return IR(2467, 29);
    case Extension::kSPV_INTEL_fpga_memory_accesses: return IR(2496, 31);
    case Extension::kSPV_INTEL_fpga_memory_attributes: return IR(2527, 33);
    case Extension::kSPV_INTEL_fpga_reg: return IR(2560, 19);
    case Extension::kSPV_INTEL_function_pointers: return IR(2579, 28);
    case Extension::kSPV_INTEL_function_variants: return IR(2607, 28);
    case Extension::kSPV_INTEL_global_variable_fpga_decorations: return IR(2635, 43);
    case Extension::kSPV_INTEL_global_variable_host_access: return IR(2678, 38);
    case Extension::kSPV_INTEL_inline_assembly: return IR(2716, 26);
    case Extension::kSPV_INTEL_int4: return IR(2742, 15);
    case Extension::kSPV_INTEL_io_pipes: return IR(2757, 19);
    case Extension::kSPV_INTEL_kernel_attributes: return IR(2776, 28);
    case Extension::kSPV_INTEL_long_composites: return IR(2804, 26);
    case Extension::kSPV_INTEL_loop_fuse: return IR(2830, 20);
    case Extension::kSPV_INTEL_masked_gather_scatter: return IR(2850, 32);
    case Extension::kSPV_INTEL_maximum_registers: return IR(2882, 28);
    case Extension::kSPV_INTEL_media_block_io: return IR(2910, 25);
    case Extension::kSPV_INTEL_memory_access_aliasing: return IR(2935, 33);
    case Extension::kSPV_INTEL_optnone: return IR(2968, 18);
    case Extension::kSPV_INTEL_runtime_aligned: return IR(2986, 26);
    case Extension::kSPV_INTEL_shader_integer_functions2: return IR(3012, 36);
    case Extension::kSPV_INTEL_split_barrier: return IR(3048, 24);
    case Extension::kSPV_INTEL_subgroup_buffer_prefetch: return IR(3072, 35);
    case Extension::kSPV_INTEL_subgroup_matrix_multiply_accumulate: return IR(3107, 46);
    case Extension::kSPV_INTEL_subgroups: return IR(3153, 20);
    case Extension::kSPV_INTEL_task_sequence: return IR(3173, 24);
    case Extension::kSPV_INTEL_tensor_float32_conversion: return IR(3197, 36);
    case Extension::kSPV_INTEL_ternary_bitwise_function: return IR(3233, 35);
    case Extension::kSPV_INTEL_unstructured_loop_controls: return IR(3268, 37);
    case Extension::kSPV_INTEL_usm_storage_classes: return IR(3305, 30);
    case Extension::kSPV_INTEL_variable_length_array: return IR(3335, 32);
    case Extension::kSPV_INTEL_vector_compute: return IR(3367, 25);
    case Extension::kSPV_KHR_16bit_storage: return IR(3392, 22);
    case Extension::kSPV_KHR_8bit_storage: return IR(3414, 21);
    case Extension::kSPV_KHR_bfloat16: return IR(3435, 17);
    case Extension::kSPV_KHR_bit_instructions: return IR(3452, 25);
    case Extension::kSPV_KHR_compute_shader_derivatives: return IR(3477, 35);
    case Extension::kSPV_KHR_cooperative_matrix: return IR(3512, 27);
    case Extension::kSPV_KHR_device_group: return IR(3539, 21);
    case Extension::kSPV_KHR_expect_assume: return IR(3560, 22);
    case Extension::kSPV_KHR_float_controls: return IR(3582, 23);
    case Extension::kSPV_KHR_float_controls2: return IR(3605, 24);
    case Extension::kSPV_KHR_fma: return IR(3629, 12);
    case Extension::kSPV_KHR_fragment_shader_barycentric: return IR(3641, 36);
    case Extension::kSPV_KHR_fragment_shading_rate: return IR(3677, 30);
    case Extension::kSPV_KHR_integer_dot_product: return IR(3707, 28);
    case Extension::kSPV_KHR_linkonce_odr: return IR(3735, 21);
    case Extension::kSPV_KHR_maximal_reconvergence: return IR(3756, 30);
    case Extension::kSPV_KHR_multiview: return IR(3786, 18);
    case Extension::kSPV_KHR_no_integer_wrap_decoration: return IR(3804, 35);
    case Extension::kSPV_KHR_non_semantic_info: return IR(3839, 26);
    case Extension::kSPV_KHR_physical_storage_buffer: return IR(3865, 32);
    case Extension::kSPV_KHR_post_depth_coverage: return IR(3897, 28);
    case Extension::kSPV_KHR_quad_control: return IR(3925, 21);
    case Extension::kSPV_KHR_ray_cull_mask: return IR(3946, 22);
    case Extension::kSPV_KHR_ray_query: return IR(3968, 18);
    case Extension::kSPV_KHR_ray_tracing: return IR(3986, 20);
    case Extension::kSPV_KHR_ray_tracing_position_fetch: return IR(4006, 35);
    case Extension::kSPV_KHR_relaxed_extended_instruction: return IR(4041, 37);
    case Extension::kSPV_KHR_shader_atomic_counter_ops: return IR(4078, 34);
    case Extension::kSPV_KHR_shader_ballot: return IR(4112, 22);
    case Extension::kSPV_KHR_shader_clock: return IR(4134, 21);
    case Extension::kSPV_KHR_shader_draw_parameters: return IR(4155, 31);
    case Extension::kSPV_KHR_storage_buffer_storage_class: return IR(4186, 37);
    case Extension::kSPV_KHR_subgroup_rotate: return IR(4223, 24);
    case Extension::kSPV_KHR_subgroup_uniform_control_flow: return IR(4247, 38);
    case Extension::kSPV_KHR_subgroup_vote: return IR(4285, 22);
    case Extension::kSPV_KHR_terminate_invocation: return IR(4307, 29);
    case Extension::kSPV_KHR_uniform_group_instructions: return IR(4336, 35);
    case Extension::kSPV_KHR_untyped_pointers: return IR(4371, 25);
    case Extension::kSPV_KHR_variable_pointers: return IR(4396, 26);
    case Extension::kSPV_KHR_vulkan_memory_model: return IR(4422, 28);
    case Extension::kSPV_KHR_workgroup_memory_explicit_layout: return IR(4450, 41);
    case Extension::kSPV_NVX_multiview_per_view_attributes: return IR(4491, 38);
    case Extension::kSPV_NV_bindless_texture: return IR(4529, 24);
    case Extension::kSPV_NV_cluster_acceleration_structure: return IR(4553, 38);
    case Extension::kSPV_NV_compute_shader_derivatives: return IR(4591, 34);
    case Extension::kSPV_NV_cooperative_matrix: return IR(4625, 26);
    case Extension::kSPV_NV_cooperative_matrix2: return IR(4651, 27);
    case Extension::kSPV_NV_cooperative_vector: return IR(4678, 26);
    case Extension::kSPV_NV_displacement_micromap: return IR(4704, 29);
    case Extension::kSPV_NV_fragment_shader_barycentric: return IR(4733, 35);
    case Extension::kSPV_NV_geometry_shader_passthrough: return IR(4768, 35);
    case Extension::kSPV_NV_linear_swept_spheres: return IR(4803, 28);
    case Extension::kSPV_NV_mesh_shader: return IR(4831, 19);
    case Extension::kSPV_NV_raw_access_chains: return IR(4850, 25);
    case Extension::kSPV_NV_ray_tracing: return IR(4875, 19);
    case Extension::kSPV_NV_ray_tracing_motion_blur: return IR(4894, 31);
    case Extension::kSPV_NV_sample_mask_override_coverage: return IR(4925, 37);
    case Extension::kSPV_NV_shader_atomic_fp16_vector: return IR(4962, 33);
    case Extension::kSPV_NV_shader_image_footprint: return IR(4995, 30);
    case Extension::kSPV_NV_shader_invocation_reorder: return IR(5025, 33);
    case Extension::kSPV_NV_shader_sm_builtins: return IR(5058, 26);
    case Extension::kSPV_NV_shader_subgroup_partitioned: return IR(5084, 35);
    case Extension::kSPV_NV_shading_rate: return IR(5119, 20);
    case Extension::kSPV_NV_stereo_view_rendering: return IR(5139, 29);
    case Extension::kSPV_NV_tensor_addressing: return IR(5168, 25);
    case Extension::kSPV_NV_viewport_array2: return IR(5193, 23);
    case Extension::kSPV_QCOM_cooperative_matrix_conversion: return IR(5216, 39);
    case Extension::kSPV_QCOM_image_processing: return IR(5255, 26);
    case Extension::kSPV_QCOM_image_processing2: return IR(5281, 27);
    case Extension::kSPV_QCOM_tile_shading: return IR(5308, 22);
    case Extension::kSPV_VALIDATOR_ignore_type_decl_unique: return IR(5330, 38);
    default: break;
  }
  return {};
}

// Extension names and values, ordered by name
// The fields in order are:
//   name, indexing into kStrings
//   enum value
static const std::array<NameValue,184> kExtensionNames{{
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
    {IR(1168, 28), static_cast<uint32_t>(kSPV_EXT_descriptor_indexing)},
    {IR(1196, 15), static_cast<uint32_t>(kSPV_EXT_float8)},
    {IR(1211, 31), static_cast<uint32_t>(kSPV_EXT_fragment_fully_covered)},
    {IR(1242, 36), static_cast<uint32_t>(kSPV_EXT_fragment_invocation_density)},
    {IR(1278, 34), static_cast<uint32_t>(kSPV_EXT_fragment_shader_interlock)},
    {IR(1312, 20), static_cast<uint32_t>(kSPV_EXT_long_vector)},
    {IR(1332, 20), static_cast<uint32_t>(kSPV_EXT_mesh_shader)},
    {IR(1352, 25), static_cast<uint32_t>(kSPV_EXT_opacity_micromap)},
    {IR(1377, 16), static_cast<uint32_t>(kSPV_EXT_optnone)},
    {IR(1393, 32), static_cast<uint32_t>(kSPV_EXT_physical_storage_buffer)},
    {IR(1425, 44), static_cast<uint32_t>(kSPV_EXT_relaxed_printf_string_address_space)},
    {IR(1469, 30), static_cast<uint32_t>(kSPV_EXT_replicated_composites)},
    {IR(1499, 30), static_cast<uint32_t>(kSPV_EXT_shader_64bit_indexing)},
    {IR(1529, 34), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float16_add)},
    {IR(1563, 32), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float_add)},
    {IR(1595, 36), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float_min_max)},
    {IR(1631, 27), static_cast<uint32_t>(kSPV_EXT_shader_image_int64)},
    {IR(1658, 34), static_cast<uint32_t>(kSPV_EXT_shader_invocation_reorder)},
    {IR(1692, 30), static_cast<uint32_t>(kSPV_EXT_shader_stencil_export)},
    {IR(1722, 26), static_cast<uint32_t>(kSPV_EXT_shader_tile_image)},
    {IR(1748, 36), static_cast<uint32_t>(kSPV_EXT_shader_viewport_index_layer)},
    {IR(1784, 27), static_cast<uint32_t>(kSPV_GOOGLE_decorate_string)},
    {IR(1811, 31), static_cast<uint32_t>(kSPV_GOOGLE_hlsl_functionality1)},
    {IR(1842, 21), static_cast<uint32_t>(kSPV_GOOGLE_user_type)},
    {IR(1863, 22), static_cast<uint32_t>(kSPV_INTEL_2d_block_io)},
    {IR(1885, 42), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_fixed_point)},
    {IR(1927, 45), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_floating_point)},
    {IR(1972, 39), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_integers)},
    {IR(2011, 30), static_cast<uint32_t>(kSPV_INTEL_bfloat16_conversion)},
    {IR(2041, 26), static_cast<uint32_t>(kSPV_INTEL_bindless_images)},
    {IR(2067, 25), static_cast<uint32_t>(kSPV_INTEL_blocking_pipes)},
    {IR(2092, 25), static_cast<uint32_t>(kSPV_INTEL_cache_controls)},
    {IR(2117, 23), static_cast<uint32_t>(kSPV_INTEL_debug_module)},
    {IR(2140, 44), static_cast<uint32_t>(kSPV_INTEL_device_side_avc_motion_estimation)},
    {IR(2184, 26), static_cast<uint32_t>(kSPV_INTEL_float_controls2)},
    {IR(2210, 28), static_cast<uint32_t>(kSPV_INTEL_fp_fast_math_mode)},
    {IR(2238, 23), static_cast<uint32_t>(kSPV_INTEL_fp_max_error)},
    {IR(2261, 35), static_cast<uint32_t>(kSPV_INTEL_fpga_argument_interfaces)},
    {IR(2296, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_buffer_location)},
    {IR(2327, 34), static_cast<uint32_t>(kSPV_INTEL_fpga_cluster_attributes)},
    {IR(2361, 27), static_cast<uint32_t>(kSPV_INTEL_fpga_dsp_control)},
    {IR(2388, 48), static_cast<uint32_t>(kSPV_INTEL_fpga_invocation_pipelining_attributes)},
    {IR(2436, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_latency_control)},
    {IR(2467, 29), static_cast<uint32_t>(kSPV_INTEL_fpga_loop_controls)},
    {IR(2496, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_memory_accesses)},
    {IR(2527, 33), static_cast<uint32_t>(kSPV_INTEL_fpga_memory_attributes)},
    {IR(2560, 19), static_cast<uint32_t>(kSPV_INTEL_fpga_reg)},
    {IR(2579, 28), static_cast<uint32_t>(kSPV_INTEL_function_pointers)},
    {IR(2607, 28), static_cast<uint32_t>(kSPV_INTEL_function_variants)},
    {IR(2635, 43), static_cast<uint32_t>(kSPV_INTEL_global_variable_fpga_decorations)},
    {IR(2678, 38), static_cast<uint32_t>(kSPV_INTEL_global_variable_host_access)},
    {IR(2716, 26), static_cast<uint32_t>(kSPV_INTEL_inline_assembly)},
    {IR(2742, 15), static_cast<uint32_t>(kSPV_INTEL_int4)},
    {IR(2757, 19), static_cast<uint32_t>(kSPV_INTEL_io_pipes)},
    {IR(2776, 28), static_cast<uint32_t>(kSPV_INTEL_kernel_attributes)},
    {IR(2804, 26), static_cast<uint32_t>(kSPV_INTEL_long_composites)},
    {IR(2830, 20), static_cast<uint32_t>(kSPV_INTEL_loop_fuse)},
    {IR(2850, 32), static_cast<uint32_t>(kSPV_INTEL_masked_gather_scatter)},
    {IR(2882, 28), static_cast<uint32_t>(kSPV_INTEL_maximum_registers)},
    {IR(2910, 25), static_cast<uint32_t>(kSPV_INTEL_media_block_io)},
    {IR(2935, 33), static_cast<uint32_t>(kSPV_INTEL_memory_access_aliasing)},
    {IR(2968, 18), static_cast<uint32_t>(kSPV_INTEL_optnone)},
    {IR(2986, 26), static_cast<uint32_t>(kSPV_INTEL_runtime_aligned)},
    {IR(3012, 36), static_cast<uint32_t>(kSPV_INTEL_shader_integer_functions2)},
    {IR(3048, 24), static_cast<uint32_t>(kSPV_INTEL_split_barrier)},
    {IR(3072, 35), static_cast<uint32_t>(kSPV_INTEL_subgroup_buffer_prefetch)},
    {IR(3107, 46), static_cast<uint32_t>(kSPV_INTEL_subgroup_matrix_multiply_accumulate)},
    {IR(3153, 20), static_cast<uint32_t>(kSPV_INTEL_subgroups)},
    {IR(3173, 24), static_cast<uint32_t>(kSPV_INTEL_task_sequence)},
    {IR(3197, 36), static_cast<uint32_t>(kSPV_INTEL_tensor_float32_conversion)},
    {IR(3233, 35), static_cast<uint32_t>(kSPV_INTEL_ternary_bitwise_function)},
    {IR(3268, 37), static_cast<uint32_t>(kSPV_INTEL_unstructured_loop_controls)},
    {IR(3305, 30), static_cast<uint32_t>(kSPV_INTEL_usm_storage_classes)},
    {IR(3335, 32), static_cast<uint32_t>(kSPV_INTEL_variable_length_array)},
    {IR(3367, 25), static_cast<uint32_t>(kSPV_INTEL_vector_compute)},
    {IR(3392, 22), static_cast<uint32_t>(kSPV_KHR_16bit_storage)},
    {IR(3414, 21), static_cast<uint32_t>(kSPV_KHR_8bit_storage)},
    {IR(3435, 17), static_cast<uint32_t>(kSPV_KHR_bfloat16)},
    {IR(3452, 25), static_cast<uint32_t>(kSPV_KHR_bit_instructions)},
    {IR(3477, 35), static_cast<uint32_t>(kSPV_KHR_compute_shader_derivatives)},
    {IR(3512, 27), static_cast<uint32_t>(kSPV_KHR_cooperative_matrix)},
    {IR(3539, 21), static_cast<uint32_t>(kSPV_KHR_device_group)},
    {IR(3560, 22), static_cast<uint32_t>(kSPV_KHR_expect_assume)},
    {IR(3582, 23), static_cast<uint32_t>(kSPV_KHR_float_controls)},
    {IR(3605, 24), static_cast<uint32_t>(kSPV_KHR_float_controls2)},
    {IR(3629, 12), static_cast<uint32_t>(kSPV_KHR_fma)},
    {IR(3641, 36), static_cast<uint32_t>(kSPV_KHR_fragment_shader_barycentric)},
    {IR(3677, 30), static_cast<uint32_t>(kSPV_KHR_fragment_shading_rate)},
    {IR(3707, 28), static_cast<uint32_t>(kSPV_KHR_integer_dot_product)},
    {IR(3735, 21), static_cast<uint32_t>(kSPV_KHR_linkonce_odr)},
    {IR(3756, 30), static_cast<uint32_t>(kSPV_KHR_maximal_reconvergence)},
    {IR(3786, 18), static_cast<uint32_t>(kSPV_KHR_multiview)},
    {IR(3804, 35), static_cast<uint32_t>(kSPV_KHR_no_integer_wrap_decoration)},
    {IR(3839, 26), static_cast<uint32_t>(kSPV_KHR_non_semantic_info)},
    {IR(3865, 32), static_cast<uint32_t>(kSPV_KHR_physical_storage_buffer)},
    {IR(3897, 28), static_cast<uint32_t>(kSPV_KHR_post_depth_coverage)},
    {IR(3925, 21), static_cast<uint32_t>(kSPV_KHR_quad_control)},
    {IR(3946, 22), static_cast<uint32_t>(kSPV_KHR_ray_cull_mask)},
    {IR(3968, 18), static_cast<uint32_t>(kSPV_KHR_ray_query)},
    {IR(3986, 20), static_cast<uint32_t>(kSPV_KHR_ray_tracing)},
    {IR(4006, 35), static_cast<uint32_t>(kSPV_KHR_ray_tracing_position_fetch)},
    {IR(4041, 37), static_cast<uint32_t>(kSPV_KHR_relaxed_extended_instruction)},
    {IR(4078, 34), static_cast<uint32_t>(kSPV_KHR_shader_atomic_counter_ops)},
    {IR(4112, 22), static_cast<uint32_t>(kSPV_KHR_shader_ballot)},
    {IR(4134, 21), static_cast<uint32_t>(kSPV_KHR_shader_clock)},
    {IR(4155, 31), static_cast<uint32_t>(kSPV_KHR_shader_draw_parameters)},
    {IR(4186, 37), static_cast<uint32_t>(kSPV_KHR_storage_buffer_storage_class)},
    {IR(4223, 24), static_cast<uint32_t>(kSPV_KHR_subgroup_rotate)},
    {IR(4247, 38), static_cast<uint32_t>(kSPV_KHR_subgroup_uniform_control_flow)},
    {IR(4285, 22), static_cast<uint32_t>(kSPV_KHR_subgroup_vote)},
    {IR(4307, 29), static_cast<uint32_t>(kSPV_KHR_terminate_invocation)},
    {IR(4336, 35), static_cast<uint32_t>(kSPV_KHR_uniform_group_instructions)},
    {IR(4371, 25), static_cast<uint32_t>(kSPV_KHR_untyped_pointers)},
    {IR(4396, 26), static_cast<uint32_t>(kSPV_KHR_variable_pointers)},
    {IR(4422, 28), static_cast<uint32_t>(kSPV_KHR_vulkan_memory_model)},
    {IR(4450, 41), static_cast<uint32_t>(kSPV_KHR_workgroup_memory_explicit_layout)},
    {IR(4491, 38), static_cast<uint32_t>(kSPV_NVX_multiview_per_view_attributes)},
    {IR(4529, 24), static_cast<uint32_t>(kSPV_NV_bindless_texture)},
    {IR(4553, 38), static_cast<uint32_t>(kSPV_NV_cluster_acceleration_structure)},
    {IR(4591, 34), static_cast<uint32_t>(kSPV_NV_compute_shader_derivatives)},
    {IR(4625, 26), static_cast<uint32_t>(kSPV_NV_cooperative_matrix)},
    {IR(4651, 27), static_cast<uint32_t>(kSPV_NV_cooperative_matrix2)},
    {IR(4678, 26), static_cast<uint32_t>(kSPV_NV_cooperative_vector)},
    {IR(4704, 29), static_cast<uint32_t>(kSPV_NV_displacement_micromap)},
    {IR(4733, 35), static_cast<uint32_t>(kSPV_NV_fragment_shader_barycentric)},
    {IR(4768, 35), static_cast<uint32_t>(kSPV_NV_geometry_shader_passthrough)},
    {IR(4803, 28), static_cast<uint32_t>(kSPV_NV_linear_swept_spheres)},
    {IR(4831, 19), static_cast<uint32_t>(kSPV_NV_mesh_shader)},
    {IR(4850, 25), static_cast<uint32_t>(kSPV_NV_raw_access_chains)},
    {IR(4875, 19), static_cast<uint32_t>(kSPV_NV_ray_tracing)},
    {IR(4894, 31), static_cast<uint32_t>(kSPV_NV_ray_tracing_motion_blur)},
    {IR(4925, 37), static_cast<uint32_t>(kSPV_NV_sample_mask_override_coverage)},
    {IR(4962, 33), static_cast<uint32_t>(kSPV_NV_shader_atomic_fp16_vector)},
    {IR(4995, 30), static_cast<uint32_t>(kSPV_NV_shader_image_footprint)},
    {IR(5025, 33), static_cast<uint32_t>(kSPV_NV_shader_invocation_reorder)},
    {IR(5058, 26), static_cast<uint32_t>(kSPV_NV_shader_sm_builtins)},
    {IR(5084, 35), static_cast<uint32_t>(kSPV_NV_shader_subgroup_partitioned)},
    {IR(5119, 20), static_cast<uint32_t>(kSPV_NV_shading_rate)},
    {IR(5139, 29), static_cast<uint32_t>(kSPV_NV_stereo_view_rendering)},
    {IR(5168, 25), static_cast<uint32_t>(kSPV_NV_tensor_addressing)},
    {IR(5193, 23), static_cast<uint32_t>(kSPV_NV_viewport_array2)},
    {IR(5216, 39), static_cast<uint32_t>(kSPV_QCOM_cooperative_matrix_conversion)},
    {IR(5255, 26), static_cast<uint32_t>(kSPV_QCOM_image_processing)},
    {IR(5281, 27), static_cast<uint32_t>(kSPV_QCOM_image_processing2)},
    {IR(5308, 22), static_cast<uint32_t>(kSPV_QCOM_tile_shading)},
    {IR(5330, 38), static_cast<uint32_t>(kSPV_VALIDATOR_ignore_type_decl_unique)},
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
static const std::array<OperandDesc, 1195> kOperandsByValue{{
  {0,IR(0, 0),IR(5368, 9)/* ReadOnly */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {1,IR(0, 0),IR(5384, 10)/* WriteOnly */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {2,IR(0, 0),IR(5394, 10)/* ReadWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {0,IR(0, 0),IR(5404, 8)/* Logical */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {1,IR(0, 0),IR(5412, 11)/* Physical32 */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {2,IR(0, 0),IR(5433, 11)/* Physical64 */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {5348,IR(0, 0),IR(5444, 24)/* PhysicalStorageBuffer64 */,IR(0, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {0,IR(0, 0),IR(5526, 9)/* Position */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {1,IR(0, 0),IR(5542, 10)/* PointSize */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {3,IR(0, 0),IR(5552, 13)/* ClipDistance */,IR(0, 0),IR(4, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4,IR(0, 0),IR(5565, 13)/* CullDistance */,IR(0, 0),IR(5, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5,IR(0, 0),IR(5578, 9)/* VertexId */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {6,IR(0, 0),IR(5587, 11)/* InstanceId */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {7,IR(0, 0),IR(5598, 12)/* PrimitiveId */,IR(0, 0),IR(6, 6),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {8,IR(0, 0),IR(5688, 13)/* InvocationId */,IR(0, 0),IR(12, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {9,IR(0, 0),IR(5701, 6)/* Layer */,IR(0, 0),IR(14, 5),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {10,IR(0, 0),IR(5747, 14)/* ViewportIndex */,IR(0, 0),IR(19, 5),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {11,IR(0, 0),IR(5795, 15)/* TessLevelOuter */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {12,IR(0, 0),IR(5810, 15)/* TessLevelInner */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {13,IR(0, 0),IR(5825, 10)/* TessCoord */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {14,IR(0, 0),IR(5835, 14)/* PatchVertices */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {15,IR(0, 0),IR(5849, 10)/* FragCoord */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {16,IR(0, 0),IR(5859, 11)/* PointCoord */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {17,IR(0, 0),IR(5870, 12)/* FrontFacing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {18,IR(0, 0),IR(5882, 9)/* SampleId */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {19,IR(0, 0),IR(5909, 15)/* SamplePosition */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {20,IR(0, 0),IR(5924, 11)/* SampleMask */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {22,IR(0, 0),IR(5935, 10)/* FragDepth */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {23,IR(0, 0),IR(5945, 17)/* HelperInvocation */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {24,IR(0, 0),IR(5962, 14)/* NumWorkgroups */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {25,IR(0, 0),IR(5976, 14)/* WorkgroupSize */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {26,IR(0, 0),IR(5990, 12)/* WorkgroupId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {27,IR(0, 0),IR(6002, 18)/* LocalInvocationId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {28,IR(0, 0),IR(6020, 19)/* GlobalInvocationId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {29,IR(0, 0),IR(6039, 21)/* LocalInvocationIndex */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {30,IR(0, 0),IR(6060, 8)/* WorkDim */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {31,IR(0, 0),IR(6068, 11)/* GlobalSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {32,IR(0, 0),IR(6079, 22)/* EnqueuedWorkgroupSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {33,IR(0, 0),IR(6101, 13)/* GlobalOffset */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {34,IR(0, 0),IR(6114, 15)/* GlobalLinearId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {36,IR(0, 0),IR(6129, 13)/* SubgroupSize */,IR(0, 0),IR(26, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {37,IR(0, 0),IR(6176, 16)/* SubgroupMaxSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {38,IR(0, 0),IR(6192, 13)/* NumSubgroups */,IR(0, 0),IR(29, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {39,IR(0, 0),IR(6205, 21)/* NumEnqueuedSubgroups */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {40,IR(0, 0),IR(6226, 11)/* SubgroupId */,IR(0, 0),IR(29, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {41,IR(0, 0),IR(6237, 26)/* SubgroupLocalInvocationId */,IR(0, 0),IR(26, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {42,IR(0, 0),IR(6263, 12)/* VertexIndex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {43,IR(0, 0),IR(6275, 14)/* InstanceIndex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4160,IR(0, 0),IR(6289, 10)/* CoreIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4161,IR(0, 0),IR(6315, 13)/* CoreCountARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4162,IR(0, 0),IR(6328, 13)/* CoreMaxIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4163,IR(0, 0),IR(6341, 10)/* WarpIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4164,IR(0, 0),IR(6351, 13)/* WarpMaxIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4416,IR(0, 0),IR(6364, 15)/* SubgroupEqMask */,IR(1, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4417,IR(0, 0),IR(6419, 15)/* SubgroupGeMask */,IR(2, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4418,IR(0, 0),IR(6452, 15)/* SubgroupGtMask */,IR(3, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4419,IR(0, 0),IR(6485, 15)/* SubgroupLeMask */,IR(4, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4420,IR(0, 0),IR(6518, 15)/* SubgroupLtMask */,IR(5, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4424,IR(0, 0),IR(6551, 11)/* BaseVertex */,IR(0, 0),IR(34, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4425,IR(0, 0),IR(6577, 13)/* BaseInstance */,IR(0, 0),IR(34, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4426,IR(0, 0),IR(6590, 10)/* DrawIndex */,IR(0, 0),IR(35, 3),IR(4, 3),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4432,IR(0, 0),IR(6600, 24)/* PrimitiveShadingRateKHR */,IR(0, 0),IR(38, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4438,IR(0, 0),IR(6647, 12)/* DeviceIndex */,IR(0, 0),IR(39, 1),IR(8, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4440,IR(0, 0),IR(6671, 10)/* ViewIndex */,IR(0, 0),IR(40, 1),IR(9, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4444,IR(0, 0),IR(6691, 15)/* ShadingRateKHR */,IR(0, 0),IR(38, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4492,IR(0, 0),IR(6706, 15)/* TileOffsetQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4493,IR(0, 0),IR(6737, 18)/* TileDimensionQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4494,IR(0, 0),IR(6755, 18)/* TileApronSizeQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4992,IR(0, 0),IR(6773, 20)/* BaryCoordNoPerspAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4993,IR(0, 0),IR(6793, 28)/* BaryCoordNoPerspCentroidAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4994,IR(0, 0),IR(6821, 26)/* BaryCoordNoPerspSampleAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4995,IR(0, 0),IR(6847, 19)/* BaryCoordSmoothAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4996,IR(0, 0),IR(6866, 27)/* BaryCoordSmoothCentroidAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4997,IR(0, 0),IR(6893, 25)/* BaryCoordSmoothSampleAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4998,IR(0, 0),IR(6918, 22)/* BaryCoordPullModelAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5014,IR(0, 0),IR(6940, 18)/* FragStencilRefEXT */,IR(0, 0),IR(42, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5021,IR(0, 0),IR(6975, 29)/* RemainingRecursionLevelsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5073,IR(0, 0),IR(7022, 16)/* ShaderIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5253,IR(0, 0),IR(7038, 15)/* ViewportMaskNV */,IR(0, 0),IR(44, 2),IR(12, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5257,IR(0, 0),IR(7074, 20)/* SecondaryPositionNV */,IR(0, 0),IR(46, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5258,IR(0, 0),IR(7113, 24)/* SecondaryViewportMaskNV */,IR(0, 0),IR(46, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5261,IR(0, 0),IR(7137, 18)/* PositionPerViewNV */,IR(0, 0),IR(47, 2),IR(15, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5262,IR(0, 0),IR(7175, 22)/* ViewportMaskPerViewNV */,IR(0, 0),IR(47, 2),IR(15, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5264,IR(0, 0),IR(7197, 16)/* FullyCoveredEXT */,IR(0, 0),IR(49, 1),IR(17, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5274,IR(0, 0),IR(7237, 12)/* TaskCountNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5275,IR(0, 0),IR(7249, 17)/* PrimitiveCountNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5276,IR(0, 0),IR(7266, 19)/* PrimitiveIndicesNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5277,IR(0, 0),IR(7285, 22)/* ClipDistancePerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5278,IR(0, 0),IR(7307, 22)/* CullDistancePerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5279,IR(0, 0),IR(7329, 15)/* LayerPerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5280,IR(0, 0),IR(7344, 16)/* MeshViewCountNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5281,IR(0, 0),IR(7360, 18)/* MeshViewIndicesNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5286,IR(0, 0),IR(7378, 13)/* BaryCoordKHR */,IR(6, 1),IR(51, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5287,IR(0, 0),IR(7426, 20)/* BaryCoordNoPerspKHR */,IR(7, 1),IR(51, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5292,IR(0, 0),IR(7465, 12)/* FragSizeEXT */,IR(8, 1),IR(52, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5293,IR(0, 0),IR(7511, 23)/* FragInvocationCountEXT */,IR(9, 1),IR(52, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5294,IR(0, 0),IR(7556, 25)/* PrimitivePointIndicesEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5295,IR(0, 0),IR(7581, 24)/* PrimitiveLineIndicesEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5296,IR(0, 0),IR(7605, 28)/* PrimitiveTriangleIndicesEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5299,IR(0, 0),IR(7633, 17)/* CullPrimitiveEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5319,IR(0, 0),IR(7650, 12)/* LaunchIdKHR */,IR(10, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5320,IR(0, 0),IR(7673, 14)/* LaunchSizeKHR */,IR(11, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5321,IR(0, 0),IR(7700, 18)/* WorldRayOriginKHR */,IR(12, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5322,IR(0, 0),IR(7735, 21)/* WorldRayDirectionKHR */,IR(13, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5323,IR(0, 0),IR(7776, 19)/* ObjectRayOriginKHR */,IR(14, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5324,IR(0, 0),IR(7813, 22)/* ObjectRayDirectionKHR */,IR(15, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5325,IR(0, 0),IR(7856, 11)/* RayTminKHR */,IR(16, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5326,IR(0, 0),IR(7877, 11)/* RayTmaxKHR */,IR(17, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5327,IR(0, 0),IR(7898, 23)/* InstanceCustomIndexKHR */,IR(18, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5330,IR(0, 0),IR(7943, 17)/* ObjectToWorldKHR */,IR(19, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5331,IR(0, 0),IR(7976, 17)/* WorldToObjectKHR */,IR(20, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5332,IR(0, 0),IR(8009, 7)/* HitTNV */,IR(0, 0),IR(56, 1),IR(26, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5333,IR(0, 0),IR(8016, 11)/* HitKindKHR */,IR(21, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5334,IR(0, 0),IR(8037, 17)/* CurrentRayTimeNV */,IR(0, 0),IR(57, 1),IR(27, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5335,IR(0, 0),IR(8077, 30)/* HitTriangleVertexPositionsKHR */,IR(0, 0),IR(58, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5337,IR(0, 0),IR(8134, 34)/* HitMicroTriangleVertexPositionsNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5344,IR(0, 0),IR(8201, 37)/* HitMicroTriangleVertexBarycentricsNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5351,IR(0, 0),IR(8238, 20)/* IncomingRayFlagsKHR */,IR(22, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5352,IR(0, 0),IR(8277, 20)/* RayGeometryIndexKHR */,IR(0, 0),IR(60, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5359,IR(0, 0),IR(8297, 14)/* HitIsSphereNV */,IR(0, 0),IR(61, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5360,IR(0, 0),IR(8339, 11)/* HitIsLSSNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5361,IR(0, 0),IR(8389, 20)/* HitSpherePositionNV */,IR(0, 0),IR(61, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5374,IR(0, 0),IR(8409, 13)/* WarpsPerSMNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5375,IR(0, 0),IR(8441, 10)/* SMCountNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5376,IR(0, 0),IR(8451, 9)/* WarpIDNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5377,IR(0, 0),IR(8460, 7)/* SMIDNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5396,IR(0, 0),IR(8467, 18)/* HitLSSPositionsNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5405,IR(0, 0),IR(8485, 34)/* HitKindFrontFacingMicroTriangleNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5406,IR(0, 0),IR(8519, 33)/* HitKindBackFacingMicroTriangleNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5420,IR(0, 0),IR(8552, 18)/* HitSphereRadiusNV */,IR(0, 0),IR(61, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5421,IR(0, 0),IR(8570, 14)/* HitLSSRadiiNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5436,IR(0, 0),IR(8584, 12)/* ClusterIDNV */,IR(0, 0),IR(64, 1),IR(31, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {6021,IR(0, 0),IR(8637, 12)/* CullMaskKHR */,IR(0, 0),IR(65, 1),IR(32, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {0,IR(0, 0),IR(8664, 7)/* Matrix */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {1,IR(0, 0),IR(5535, 7)/* Shader */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {2,IR(0, 0),IR(5610, 9)/* Geometry */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {3,IR(0, 0),IR(5619, 13)/* Tessellation */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4,IR(0, 0),IR(5423, 10)/* Addresses */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5,IR(0, 0),IR(8671, 8)/* Linkage */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6,IR(0, 0),IR(5377, 7)/* Kernel */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {7,IR(0, 0),IR(8679, 9)/* Vector16 */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {8,IR(0, 0),IR(8688, 14)/* Float16Buffer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {9,IR(0, 0),IR(8702, 8)/* Float16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {10,IR(0, 0),IR(8710, 8)/* Float64 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {11,IR(0, 0),IR(8718, 6)/* Int64 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {12,IR(0, 0),IR(8724, 13)/* Int64Atomics */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {13,IR(0, 0),IR(8737, 11)/* ImageBasic */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {14,IR(0, 0),IR(8748, 15)/* ImageReadWrite */,IR(0, 0),IR(68, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {15,IR(0, 0),IR(8763, 12)/* ImageMipmap */,IR(0, 0),IR(68, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {17,IR(0, 0),IR(8775, 6)/* Pipes */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {18,IR(0, 0),IR(8781, 7)/* Groups */,IR(0, 0),IR(1, 0),IR(33, 1),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {19,IR(0, 0),IR(8788, 14)/* DeviceEnqueue */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {20,IR(0, 0),IR(8802, 15)/* LiteralSampler */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {21,IR(0, 0),IR(8817, 14)/* AtomicStorage */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {22,IR(0, 0),IR(8831, 6)/* Int16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {23,IR(0, 0),IR(8837, 22)/* TessellationPointSize */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {24,IR(0, 0),IR(8859, 18)/* GeometryPointSize */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {25,IR(0, 0),IR(8877, 20)/* ImageGatherExtended */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {27,IR(0, 0),IR(8897, 24)/* StorageImageMultisample */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {28,IR(0, 0),IR(8921, 34)/* UniformBufferArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {29,IR(0, 0),IR(8955, 33)/* SampledImageArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {30,IR(0, 0),IR(8988, 34)/* StorageBufferArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {31,IR(0, 0),IR(9022, 33)/* StorageImageArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {32,IR(0, 0),IR(5552, 13)/* ClipDistance */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {33,IR(0, 0),IR(5565, 13)/* CullDistance */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {34,IR(0, 0),IR(9055, 15)/* ImageCubeArray */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {35,IR(0, 0),IR(5891, 18)/* SampleRateShading */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {36,IR(0, 0),IR(9087, 10)/* ImageRect */,IR(0, 0),IR(71, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {37,IR(0, 0),IR(9097, 12)/* SampledRect */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {38,IR(0, 0),IR(9109, 15)/* GenericPointer */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {39,IR(0, 0),IR(9124, 5)/* Int8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {40,IR(0, 0),IR(9129, 16)/* InputAttachment */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {41,IR(0, 0),IR(9145, 16)/* SparseResidency */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {42,IR(0, 0),IR(9161, 7)/* MinLod */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {43,IR(0, 0),IR(9168, 10)/* Sampled1D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {44,IR(0, 0),IR(9178, 8)/* Image1D */,IR(0, 0),IR(72, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {45,IR(0, 0),IR(9070, 17)/* SampledCubeArray */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {46,IR(0, 0),IR(9186, 14)/* SampledBuffer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {47,IR(0, 0),IR(9200, 12)/* ImageBuffer */,IR(0, 0),IR(73, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {48,IR(0, 0),IR(9212, 13)/* ImageMSArray */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {49,IR(0, 0),IR(9225, 28)/* StorageImageExtendedFormats */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {50,IR(0, 0),IR(9253, 11)/* ImageQuery */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {51,IR(0, 0),IR(9264, 18)/* DerivativeControl */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {52,IR(0, 0),IR(9282, 22)/* InterpolationFunction */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {53,IR(0, 0),IR(9304, 18)/* TransformFeedback */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {54,IR(0, 0),IR(9322, 16)/* GeometryStreams */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {55,IR(0, 0),IR(9338, 30)/* StorageImageReadWithoutFormat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {56,IR(0, 0),IR(9368, 31)/* StorageImageWriteWithoutFormat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {57,IR(0, 0),IR(5761, 14)/* MultiViewport */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {58,IR(0, 0),IR(9399, 17)/* SubgroupDispatch */,IR(0, 0),IR(74, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {59,IR(0, 0),IR(9416, 13)/* NamedBarrier */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {60,IR(0, 0),IR(9429, 12)/* PipeStorage */,IR(0, 0),IR(75, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {61,IR(0, 0),IR(6142, 16)/* GroupNonUniform */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {62,IR(0, 0),IR(9441, 20)/* GroupNonUniformVote */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {63,IR(0, 0),IR(9461, 26)/* GroupNonUniformArithmetic */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {64,IR(0, 0),IR(6397, 22)/* GroupNonUniformBallot */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {65,IR(0, 0),IR(9487, 23)/* GroupNonUniformShuffle */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {66,IR(0, 0),IR(9510, 31)/* GroupNonUniformShuffleRelative */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {67,IR(0, 0),IR(9541, 25)/* GroupNonUniformClustered */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {68,IR(0, 0),IR(9566, 20)/* GroupNonUniformQuad */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {69,IR(0, 0),IR(5707, 12)/* ShaderLayer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {70,IR(0, 0),IR(5775, 20)/* ShaderViewportIndex */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {71,IR(0, 0),IR(9586, 18)/* UniformDecoration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4165,IR(0, 0),IR(6299, 16)/* CoreBuiltinsARM */,IR(0, 0),IR(1, 0),IR(34, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4166,IR(0, 0),IR(9604, 28)/* TileImageColorReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4167,IR(0, 0),IR(9632, 28)/* TileImageDepthReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4168,IR(0, 0),IR(9660, 30)/* TileImageStencilReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4174,IR(0, 0),IR(9690, 11)/* TensorsARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4175,IR(0, 0),IR(9701, 37)/* StorageTensorArrayDynamicIndexingARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4176,IR(0, 0),IR(9738, 40)/* StorageTensorArrayNonUniformIndexingARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4191,IR(0, 0),IR(9778, 9)/* GraphARM */,IR(0, 0),IR(1, 0),IR(37, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4201,IR(0, 0),IR(9787, 28)/* CooperativeMatrixLayoutsARM */,IR(0, 0),IR(1, 0),IR(38, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4212,IR(0, 0),IR(9815, 10)/* Float8EXT */,IR(0, 0),IR(1, 0),IR(39, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4213,IR(0, 0),IR(9825, 27)/* Float8CooperativeMatrixEXT */,IR(0, 0),IR(77, 2),IR(39, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4422,IR(0, 0),IR(6624, 23)/* FragmentShadingRateKHR */,IR(0, 0),IR(3, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4423,IR(0, 0),IR(6158, 18)/* SubgroupBallotKHR */,IR(0, 0),IR(1, 0),IR(2, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4427,IR(0, 0),IR(6562, 15)/* DrawParameters */,IR(0, 0),IR(3, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4428,IR(0, 0),IR(9873, 33)/* WorkgroupMemoryExplicitLayoutKHR */,IR(0, 0),IR(3, 1),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4429,IR(0, 0),IR(9906, 43)/* WorkgroupMemoryExplicitLayout8BitAccessKHR */,IR(0, 0),IR(79, 1),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4430,IR(0, 0),IR(9949, 44)/* WorkgroupMemoryExplicitLayout16BitAccessKHR */,IR(0, 0),IR(79, 1),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4431,IR(0, 0),IR(9993, 16)/* SubgroupVoteKHR */,IR(0, 0),IR(1, 0),IR(41, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4433,IR(0, 0),IR(10009, 25)/* StorageBuffer16BitAccess */,IR(23, 1),IR(1, 0),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4434,IR(0, 0),IR(10062, 35)/* UniformAndStorageBuffer16BitAccess */,IR(24, 1),IR(80, 1),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4435,IR(0, 0),IR(10114, 22)/* StoragePushConstant16 */,IR(0, 0),IR(1, 0),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4436,IR(0, 0),IR(10136, 21)/* StorageInputOutput16 */,IR(0, 0),IR(1, 0),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4437,IR(0, 0),IR(6659, 12)/* DeviceGroup */,IR(0, 0),IR(1, 0),IR(8, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4439,IR(0, 0),IR(6681, 10)/* MultiView */,IR(0, 0),IR(3, 1),IR(9, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4441,IR(0, 0),IR(10157, 30)/* VariablePointersStorageBuffer */,IR(0, 0),IR(3, 1),IR(43, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4442,IR(0, 0),IR(10187, 17)/* VariablePointers */,IR(0, 0),IR(81, 1),IR(43, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4445,IR(0, 0),IR(10204, 17)/* AtomicStorageOps */,IR(0, 0),IR(82, 1),IR(44, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4447,IR(0, 0),IR(10221, 28)/* SampleMaskPostDepthCoverage */,IR(0, 0),IR(1, 0),IR(45, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4448,IR(0, 0),IR(10249, 24)/* StorageBuffer8BitAccess */,IR(0, 0),IR(1, 0),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4449,IR(0, 0),IR(10273, 34)/* UniformAndStorageBuffer8BitAccess */,IR(0, 0),IR(83, 1),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4450,IR(0, 0),IR(10307, 21)/* StoragePushConstant8 */,IR(0, 0),IR(1, 0),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4464,IR(0, 0),IR(10328, 15)/* DenormPreserve */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4465,IR(0, 0),IR(10343, 18)/* DenormFlushToZero */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4466,IR(0, 0),IR(10361, 25)/* SignedZeroInfNanPreserve */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4467,IR(0, 0),IR(10386, 16)/* RoundingModeRTE */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4468,IR(0, 0),IR(10402, 16)/* RoundingModeRTZ */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4471,IR(0, 0),IR(10418, 23)/* RayQueryProvisionalKHR */,IR(0, 0),IR(3, 1),IR(48, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4472,IR(0, 0),IR(10441, 12)/* RayQueryKHR */,IR(0, 0),IR(3, 1),IR(48, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4473,IR(0, 0),IR(10453, 19)/* UntypedPointersKHR */,IR(0, 0),IR(1, 0),IR(49, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4478,IR(0, 0),IR(10472, 32)/* RayTraversalPrimitiveCullingKHR */,IR(0, 0),IR(84, 2),IR(50, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4479,IR(0, 0),IR(5645, 14)/* RayTracingKHR */,IR(0, 0),IR(3, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4484,IR(0, 0),IR(10504, 26)/* TextureSampleWeightedQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4485,IR(0, 0),IR(10530, 21)/* TextureBoxFilterQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4486,IR(0, 0),IR(10551, 22)/* TextureBlockMatchQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4495,IR(0, 0),IR(6721, 16)/* TileShadingQCOM */,IR(0, 0),IR(3, 1),IR(53, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4496,IR(0, 0),IR(10573, 32)/* CooperativeMatrixConversionQCOM */,IR(0, 0),IR(86, 1),IR(54, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4498,IR(0, 0),IR(10605, 23)/* TextureBlockMatch2QCOM */,IR(0, 0),IR(1, 0),IR(55, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5008,IR(0, 0),IR(10628, 16)/* Float16ImageAMD */,IR(0, 0),IR(3, 1),IR(56, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5009,IR(0, 0),IR(10644, 22)/* ImageGatherBiasLodAMD */,IR(0, 0),IR(3, 1),IR(57, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5010,IR(0, 0),IR(10666, 16)/* FragmentMaskAMD */,IR(0, 0),IR(3, 1),IR(58, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5013,IR(0, 0),IR(6958, 17)/* StencilExportEXT */,IR(0, 0),IR(3, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5015,IR(0, 0),IR(10682, 21)/* ImageReadWriteLodAMD */,IR(0, 0),IR(3, 1),IR(59, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5016,IR(0, 0),IR(10703, 14)/* Int64ImageEXT */,IR(0, 0),IR(3, 1),IR(60, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5055,IR(0, 0),IR(10717, 15)/* ShaderClockKHR */,IR(0, 0),IR(1, 0),IR(61, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5067,IR(0, 0),IR(7004, 18)/* ShaderEnqueueAMDX */,IR(0, 0),IR(3, 1),IR(62, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5087,IR(0, 0),IR(10732, 15)/* QuadControlKHR */,IR(0, 0),IR(1, 0),IR(63, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5112,IR(0, 0),IR(10747, 14)/* Int4TypeINTEL */,IR(0, 0),IR(1, 0),IR(64, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5114,IR(0, 0),IR(10761, 27)/* Int4CooperativeMatrixINTEL */,IR(0, 0),IR(87, 2),IR(64, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5116,IR(0, 0),IR(10788, 16)/* BFloat16TypeKHR */,IR(0, 0),IR(1, 0),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5117,IR(0, 0),IR(10804, 22)/* BFloat16DotProductKHR */,IR(0, 0),IR(89, 1),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5118,IR(0, 0),IR(10826, 29)/* BFloat16CooperativeMatrixKHR */,IR(0, 0),IR(90, 2),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5249,IR(0, 0),IR(10855, 29)/* SampleMaskOverrideCoverageNV */,IR(0, 0),IR(25, 1),IR(66, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5251,IR(0, 0),IR(10884, 28)/* GeometryShaderPassthroughNV */,IR(0, 0),IR(69, 1),IR(67, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5254,IR(0, 0),IR(5719, 28)/* ShaderViewportIndexLayerEXT */,IR(25, 1),IR(92, 1),IR(68, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5255,IR(0, 0),IR(7053, 21)/* ShaderViewportMaskNV */,IR(0, 0),IR(93, 1),IR(70, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5259,IR(0, 0),IR(7094, 19)/* ShaderStereoViewNV */,IR(0, 0),IR(94, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5260,IR(0, 0),IR(7155, 20)/* PerViewAttributesNV */,IR(0, 0),IR(40, 1),IR(71, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5265,IR(0, 0),IR(7213, 24)/* FragmentFullyCoveredEXT */,IR(0, 0),IR(3, 1),IR(17, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5266,IR(0, 0),IR(5659, 14)/* MeshShadingNV */,IR(0, 0),IR(3, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5282,IR(0, 0),IR(10939, 17)/* ImageFootprintNV */,IR(0, 0),IR(1, 0),IR(72, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5283,IR(0, 0),IR(5673, 15)/* MeshShadingEXT */,IR(0, 0),IR(3, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5284,IR(0, 0),IR(7403, 23)/* FragmentBarycentricKHR */,IR(26, 1),IR(1, 0),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5288,IR(0, 0),IR(10978, 31)/* ComputeDerivativeGroupQuadsKHR */,IR(27, 1),IR(3, 1),IR(73, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5291,IR(0, 0),IR(7492, 19)/* FragmentDensityEXT */,IR(28, 1),IR(3, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5297,IR(0, 0),IR(11053, 29)/* GroupNonUniformPartitionedNV */,IR(0, 0),IR(1, 0),IR(75, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5301,IR(0, 0),IR(11082, 17)/* ShaderNonUniform */,IR(29, 1),IR(3, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5302,IR(0, 0),IR(11119, 23)/* RuntimeDescriptorArray */,IR(30, 1),IR(3, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5303,IR(0, 0),IR(11168, 36)/* InputAttachmentArrayDynamicIndexing */,IR(31, 1),IR(95, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5304,IR(0, 0),IR(11243, 39)/* UniformTexelBufferArrayDynamicIndexing */,IR(32, 1),IR(73, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5305,IR(0, 0),IR(11324, 39)/* StorageTexelBufferArrayDynamicIndexing */,IR(33, 1),IR(96, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5306,IR(0, 0),IR(11405, 37)/* UniformBufferArrayNonUniformIndexing */,IR(34, 1),IR(97, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5307,IR(0, 0),IR(11482, 36)/* SampledImageArrayNonUniformIndexing */,IR(35, 1),IR(97, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5308,IR(0, 0),IR(11557, 37)/* StorageBufferArrayNonUniformIndexing */,IR(36, 1),IR(97, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5309,IR(0, 0),IR(11634, 36)/* StorageImageArrayNonUniformIndexing */,IR(37, 1),IR(97, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5310,IR(0, 0),IR(11709, 39)/* InputAttachmentArrayNonUniformIndexing */,IR(38, 1),IR(98, 2),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5311,IR(0, 0),IR(11790, 42)/* UniformTexelBufferArrayNonUniformIndexing */,IR(39, 1),IR(100, 2),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5312,IR(0, 0),IR(11877, 42)/* StorageTexelBufferArrayNonUniformIndexing */,IR(40, 1),IR(102, 2),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5336,IR(0, 0),IR(8107, 27)/* RayTracingPositionFetchKHR */,IR(0, 0),IR(3, 1),IR(77, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5340,IR(0, 0),IR(5632, 13)/* RayTracingNV */,IR(0, 0),IR(3, 1),IR(26, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5341,IR(0, 0),IR(8054, 23)/* RayTracingMotionBlurNV */,IR(0, 0),IR(3, 1),IR(27, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5345,IR(0, 0),IR(11964, 18)/* VulkanMemoryModel */,IR(41, 1),IR(1, 0),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5346,IR(0, 0),IR(12003, 29)/* VulkanMemoryModelDeviceScope */,IR(42, 1),IR(1, 0),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5347,IR(0, 0),IR(5495, 31)/* PhysicalStorageBufferAddresses */,IR(43, 1),IR(3, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5350,IR(0, 0),IR(12098, 32)/* ComputeDerivativeGroupLinearKHR */,IR(44, 1),IR(3, 1),IR(73, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5353,IR(0, 0),IR(12161, 25)/* RayTracingProvisionalKHR */,IR(0, 0),IR(3, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5357,IR(0, 0),IR(12186, 20)/* CooperativeMatrixNV */,IR(0, 0),IR(3, 1),IR(79, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5363,IR(0, 0),IR(12206, 33)/* FragmentShaderSampleInterlockEXT */,IR(0, 0),IR(3, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5372,IR(0, 0),IR(12239, 38)/* FragmentShaderShadingRateInterlockEXT */,IR(0, 0),IR(3, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5373,IR(0, 0),IR(8422, 19)/* ShaderSMBuiltinsNV */,IR(0, 0),IR(3, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5378,IR(0, 0),IR(12277, 32)/* FragmentShaderPixelInterlockEXT */,IR(0, 0),IR(3, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5379,IR(0, 0),IR(12309, 25)/* DemoteToHelperInvocation */,IR(45, 1),IR(3, 1),IR(81, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5380,IR(0, 0),IR(12362, 23)/* DisplacementMicromapNV */,IR(0, 0),IR(3, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5381,IR(0, 0),IR(12385, 29)/* RayTracingOpacityMicromapEXT */,IR(0, 0),IR(3, 1),IR(83, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5383,IR(0, 0),IR(12414, 26)/* ShaderInvocationReorderNV */,IR(0, 0),IR(60, 1),IR(84, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5388,IR(0, 0),IR(12440, 27)/* ShaderInvocationReorderEXT */,IR(0, 0),IR(60, 1),IR(85, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5390,IR(0, 0),IR(12467, 18)/* BindlessTextureNV */,IR(0, 0),IR(1, 0),IR(86, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5391,IR(0, 0),IR(12485, 25)/* RayQueryPositionFetchKHR */,IR(0, 0),IR(3, 1),IR(77, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5394,IR(0, 0),IR(12510, 20)/* CooperativeVectorNV */,IR(0, 0),IR(1, 0),IR(87, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5404,IR(0, 0),IR(12530, 22)/* AtomicFloat16VectorNV */,IR(0, 0),IR(1, 0),IR(88, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5409,IR(0, 0),IR(8168, 33)/* RayTracingDisplacementMicromapNV */,IR(0, 0),IR(60, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5414,IR(0, 0),IR(12552, 18)/* RawAccessChainsNV */,IR(0, 0),IR(1, 0),IR(89, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5418,IR(0, 0),IR(8311, 28)/* RayTracingSpheresGeometryNV */,IR(0, 0),IR(1, 0),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5419,IR(0, 0),IR(8350, 39)/* RayTracingLinearSweptSpheresGeometryNV */,IR(0, 0),IR(1, 0),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5425,IR(0, 0),IR(12570, 14)/* LongVectorEXT */,IR(0, 0),IR(1, 0),IR(90, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5426,IR(0, 0),IR(12584, 23)/* Shader64BitIndexingEXT */,IR(0, 0),IR(1, 0),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5430,IR(0, 0),IR(12607, 30)/* CooperativeMatrixReductionsNV */,IR(0, 0),IR(1, 0),IR(92, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5431,IR(0, 0),IR(12637, 31)/* CooperativeMatrixConversionsNV */,IR(0, 0),IR(1, 0),IR(92, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5432,IR(0, 0),IR(12668, 40)/* CooperativeMatrixPerElementOperationsNV */,IR(0, 0),IR(1, 0),IR(92, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5433,IR(0, 0),IR(12708, 36)/* CooperativeMatrixTensorAddressingNV */,IR(0, 0),IR(1, 0),IR(92, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5434,IR(0, 0),IR(12744, 30)/* CooperativeMatrixBlockLoadsNV */,IR(0, 0),IR(1, 0),IR(92, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5435,IR(0, 0),IR(12774, 28)/* CooperativeVectorTrainingNV */,IR(0, 0),IR(1, 0),IR(87, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5437,IR(0, 0),IR(8596, 41)/* RayTracingClusterAccelerationStructureNV */,IR(0, 0),IR(60, 1),IR(31, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5439,IR(0, 0),IR(12802, 19)/* TensorAddressingNV */,IR(0, 0),IR(1, 0),IR(93, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5568,IR(0, 0),IR(12821, 21)/* SubgroupShuffleINTEL */,IR(0, 0),IR(1, 0),IR(94, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5569,IR(0, 0),IR(12842, 27)/* SubgroupBufferBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(94, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5570,IR(0, 0),IR(12869, 26)/* SubgroupImageBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(94, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5579,IR(0, 0),IR(12895, 31)/* SubgroupImageMediaBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5582,IR(0, 0),IR(12926, 21)/* RoundToInfinityINTEL */,IR(0, 0),IR(1, 0),IR(96, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5583,IR(0, 0),IR(12947, 23)/* FloatingPointModeINTEL */,IR(0, 0),IR(1, 0),IR(96, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5584,IR(0, 0),IR(12970, 23)/* IntegerFunctions2INTEL */,IR(0, 0),IR(1, 0),IR(97, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5603,IR(0, 0),IR(12993, 22)/* FunctionPointersINTEL */,IR(0, 0),IR(1, 0),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5604,IR(0, 0),IR(13015, 24)/* IndirectReferencesINTEL */,IR(0, 0),IR(1, 0),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5606,IR(0, 0),IR(13039, 9)/* AsmINTEL */,IR(0, 0),IR(1, 0),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5612,IR(0, 0),IR(13048, 23)/* AtomicFloat32MinMaxEXT */,IR(0, 0),IR(1, 0),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5613,IR(0, 0),IR(13071, 23)/* AtomicFloat64MinMaxEXT */,IR(0, 0),IR(1, 0),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5616,IR(0, 0),IR(13094, 23)/* AtomicFloat16MinMaxEXT */,IR(0, 0),IR(1, 0),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5617,IR(0, 0),IR(13117, 19)/* VectorComputeINTEL */,IR(0, 0),IR(104, 1),IR(101, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5619,IR(0, 0),IR(13136, 15)/* VectorAnyINTEL */,IR(0, 0),IR(1, 0),IR(101, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5629,IR(0, 0),IR(13151, 16)/* ExpectAssumeKHR */,IR(0, 0),IR(1, 0),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5696,IR(0, 0),IR(13167, 33)/* SubgroupAvcMotionEstimationINTEL */,IR(0, 0),IR(1, 0),IR(103, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5697,IR(0, 0),IR(13200, 38)/* SubgroupAvcMotionEstimationIntraINTEL */,IR(0, 0),IR(1, 0),IR(103, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5698,IR(0, 0),IR(13238, 39)/* SubgroupAvcMotionEstimationChromaINTEL */,IR(0, 0),IR(1, 0),IR(103, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5817,IR(0, 0),IR(13277, 25)/* VariableLengthArrayINTEL */,IR(0, 0),IR(1, 0),IR(104, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5821,IR(0, 0),IR(13302, 26)/* FunctionFloatControlINTEL */,IR(0, 0),IR(1, 0),IR(96, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5824,IR(0, 0),IR(13328, 27)/* FPGAMemoryAttributesALTERA */,IR(46, 1),IR(1, 0),IR(105, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5837,IR(0, 0),IR(13381, 20)/* FPFastMathModeINTEL */,IR(0, 0),IR(0, 1),IR(107, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5844,IR(0, 0),IR(13401, 33)/* ArbitraryPrecisionIntegersALTERA */,IR(47, 1),IR(1, 0),IR(108, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5845,IR(0, 0),IR(13466, 38)/* ArbitraryPrecisionFloatingPointALTERA */,IR(48, 1),IR(1, 0),IR(110, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5886,IR(0, 0),IR(13541, 30)/* UnstructuredLoopControlsINTEL */,IR(0, 0),IR(1, 0),IR(112, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5888,IR(0, 0),IR(13571, 23)/* FPGALoopControlsALTERA */,IR(49, 1),IR(1, 0),IR(113, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5892,IR(0, 0),IR(13616, 22)/* KernelAttributesINTEL */,IR(0, 0),IR(1, 0),IR(115, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5897,IR(0, 0),IR(13638, 26)/* FPGAKernelAttributesINTEL */,IR(0, 0),IR(1, 0),IR(115, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5898,IR(0, 0),IR(13664, 25)/* FPGAMemoryAccessesALTERA */,IR(50, 1),IR(1, 0),IR(116, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5904,IR(0, 0),IR(13713, 28)/* FPGAClusterAttributesALTERA */,IR(51, 1),IR(1, 0),IR(118, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5906,IR(0, 0),IR(13768, 15)/* LoopFuseALTERA */,IR(52, 1),IR(1, 0),IR(120, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5908,IR(0, 0),IR(13797, 21)/* FPGADSPControlALTERA */,IR(53, 1),IR(1, 0),IR(122, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5910,IR(0, 0),IR(13838, 26)/* MemoryAccessAliasingINTEL */,IR(0, 0),IR(1, 0),IR(124, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5916,IR(0, 0),IR(13864, 41)/* FPGAInvocationPipeliningAttributesALTERA */,IR(54, 1),IR(1, 0),IR(125, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5920,IR(0, 0),IR(13945, 25)/* FPGABufferLocationALTERA */,IR(55, 1),IR(1, 0),IR(127, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5922,IR(0, 0),IR(13994, 35)/* ArbitraryPrecisionFixedPointALTERA */,IR(56, 1),IR(1, 0),IR(129, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5935,IR(0, 0),IR(14063, 24)/* USMStorageClassesALTERA */,IR(57, 1),IR(1, 0),IR(131, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5939,IR(0, 0),IR(14110, 30)/* RuntimeAlignedAttributeALTERA */,IR(58, 1),IR(1, 0),IR(133, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5943,IR(0, 0),IR(14169, 14)/* IOPipesALTERA */,IR(59, 1),IR(1, 0),IR(135, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5945,IR(0, 0),IR(14196, 20)/* BlockingPipesALTERA */,IR(60, 1),IR(1, 0),IR(137, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5948,IR(0, 0),IR(14235, 14)/* FPGARegALTERA */,IR(61, 1),IR(1, 0),IR(139, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6016,IR(0, 0),IR(14262, 19)/* DotProductInputAll */,IR(62, 1),IR(1, 0),IR(141, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6017,IR(0, 0),IR(14303, 22)/* DotProductInput4x8Bit */,IR(63, 1),IR(105, 1),IR(141, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6018,IR(0, 0),IR(14350, 28)/* DotProductInput4x8BitPacked */,IR(64, 1),IR(1, 0),IR(141, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6019,IR(0, 0),IR(14409, 11)/* DotProduct */,IR(65, 1),IR(1, 0),IR(141, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6020,IR(0, 0),IR(8649, 15)/* RayCullMaskKHR */,IR(0, 0),IR(1, 0),IR(32, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6022,IR(0, 0),IR(9852, 21)/* CooperativeMatrixKHR */,IR(0, 0),IR(1, 0),IR(142, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6024,IR(0, 0),IR(14434, 24)/* ReplicatedCompositesEXT */,IR(0, 0),IR(1, 0),IR(143, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6025,IR(0, 0),IR(14458, 16)/* BitInstructions */,IR(0, 0),IR(1, 0),IR(144, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6026,IR(0, 0),IR(14474, 25)/* GroupNonUniformRotateKHR */,IR(0, 0),IR(76, 1),IR(145, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6029,IR(0, 0),IR(14499, 15)/* FloatControls2 */,IR(0, 0),IR(1, 0),IR(146, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6030,IR(0, 0),IR(14514, 7)/* FMAKHR */,IR(0, 0),IR(1, 0),IR(147, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6033,IR(0, 0),IR(14521, 20)/* AtomicFloat32AddEXT */,IR(0, 0),IR(1, 0),IR(148, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6034,IR(0, 0),IR(14541, 20)/* AtomicFloat64AddEXT */,IR(0, 0),IR(1, 0),IR(148, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6089,IR(0, 0),IR(14561, 20)/* LongCompositesINTEL */,IR(0, 0),IR(1, 0),IR(149, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6094,IR(0, 0),IR(14581, 11)/* OptNoneEXT */,IR(66, 1),IR(1, 0),IR(150, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6095,IR(0, 0),IR(14605, 20)/* AtomicFloat16AddEXT */,IR(0, 0),IR(1, 0),IR(152, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6114,IR(0, 0),IR(14625, 21)/* DebugInfoModuleINTEL */,IR(0, 0),IR(1, 0),IR(153, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6115,IR(0, 0),IR(14646, 24)/* BFloat16ConversionINTEL */,IR(0, 0),IR(1, 0),IR(154, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6141,IR(0, 0),IR(14670, 18)/* SplitBarrierINTEL */,IR(0, 0),IR(1, 0),IR(155, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6144,IR(0, 0),IR(14688, 19)/* ArithmeticFenceEXT */,IR(0, 0),IR(1, 0),IR(156, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6150,IR(0, 0),IR(14707, 30)/* FPGAClusterAttributesV2ALTERA */,IR(67, 1),IR(106, 1),IR(118, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6161,IR(0, 0),IR(14766, 28)/* FPGAKernelAttributesv2INTEL */,IR(0, 0),IR(107, 1),IR(115, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6162,IR(0, 0),IR(14794, 19)/* TaskSequenceALTERA */,IR(68, 1),IR(1, 0),IR(157, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6169,IR(0, 0),IR(14831, 16)/* FPMaxErrorINTEL */,IR(0, 0),IR(1, 0),IR(159, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6171,IR(0, 0),IR(14847, 25)/* FPGALatencyControlALTERA */,IR(69, 1),IR(1, 0),IR(160, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6174,IR(0, 0),IR(14896, 29)/* FPGAArgumentInterfacesALTERA */,IR(70, 1),IR(1, 0),IR(162, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6187,IR(0, 0),IR(14953, 30)/* GlobalVariableHostAccessINTEL */,IR(0, 0),IR(1, 0),IR(164, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6189,IR(0, 0),IR(14983, 36)/* GlobalVariableFPGADecorationsALTERA */,IR(71, 1),IR(1, 0),IR(165, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6220,IR(0, 0),IR(15054, 28)/* SubgroupBufferPrefetchINTEL */,IR(0, 0),IR(1, 0),IR(167, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6228,IR(0, 0),IR(15082, 23)/* Subgroup2DBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(168, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6229,IR(0, 0),IR(15105, 30)/* Subgroup2DBlockTransformINTEL */,IR(0, 0),IR(108, 1),IR(168, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6230,IR(0, 0),IR(15135, 30)/* Subgroup2DBlockTransposeINTEL */,IR(0, 0),IR(108, 1),IR(168, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6236,IR(0, 0),IR(15165, 38)/* SubgroupMatrixMultiplyAccumulateINTEL */,IR(0, 0),IR(1, 0),IR(169, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6241,IR(0, 0),IR(15203, 28)/* TernaryBitwiseFunctionINTEL */,IR(0, 0),IR(1, 0),IR(170, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6243,IR(0, 0),IR(15231, 32)/* UntypedVariableLengthArrayINTEL */,IR(0, 0),IR(109, 2),IR(104, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6245,IR(0, 0),IR(15263, 21)/* SpecConditionalINTEL */,IR(0, 0),IR(1, 0),IR(171, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6246,IR(0, 0),IR(15284, 22)/* FunctionVariantsINTEL */,IR(0, 0),IR(111, 1),IR(171, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6400,IR(0, 0),IR(15306, 26)/* GroupUniformArithmeticKHR */,IR(0, 0),IR(1, 0),IR(172, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6425,IR(0, 0),IR(15332, 27)/* TensorFloat32RoundingINTEL */,IR(0, 0),IR(1, 0),IR(173, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6427,IR(0, 0),IR(15359, 25)/* MaskedGatherScatterINTEL */,IR(0, 0),IR(1, 0),IR(174, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6441,IR(0, 0),IR(15384, 19)/* CacheControlsINTEL */,IR(0, 0),IR(1, 0),IR(175, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6460,IR(0, 0),IR(15403, 20)/* RegisterLimitsINTEL */,IR(0, 0),IR(1, 0),IR(176, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6528,IR(0, 0),IR(15423, 20)/* BindlessImagesINTEL */,IR(0, 0),IR(1, 0),IR(177, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {0,IR(0, 0),IR(15443, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(15455, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(15463, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {3,IR(0, 0),IR(15471, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(15477, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(15484, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(15495, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(15504, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(15517, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(15523, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(15533, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(15539, 15)/* ImportedModule */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {1,IR(0, 0),IR(15554, 20)/* ImportedDeclaration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {0,IR(0, 0),IR(15574, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(15579, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(15595, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(15609, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(15622, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(15634, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(15651, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(15663, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(15678, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(15691, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(15706, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(15724, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(15741, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(15762, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(15782, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(15802, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {16384,IR(0, 0),IR(15818, 16)/* FlagIsEnumClass */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {32768,IR(0, 0),IR(15834, 20)/* FlagTypePassByValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {65536,IR(0, 0),IR(15854, 24)/* FlagTypePassByReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(15878, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {1,IR(0, 0),IR(15884, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {2,IR(0, 0),IR(15889, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {3,IR(0, 1),IR(15928, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {4,IR(1, 2),IR(15939, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {5,IR(0, 0),IR(15948, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {6,IR(0, 0),IR(15953, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {7,IR(0, 0),IR(15960, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {8,IR(0, 1),IR(15971, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {9,IR(1, 2),IR(15978, 9)/* Fragment */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {0,IR(0, 0),IR(15987, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(15997, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(16010, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {3,IR(0, 0),IR(16023, 11)/* AtomicType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(16034, 10)/* Float16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1,IR(0, 0),IR(16044, 10)/* Float32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {2,IR(0, 0),IR(16054, 10)/* Float64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {3,IR(0, 0),IR(16064, 13)/* SignedInt8NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {4,IR(0, 0),IR(16077, 14)/* SignedInt16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {5,IR(0, 0),IR(16091, 14)/* SignedInt32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {6,IR(0, 0),IR(16105, 14)/* SignedInt64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {7,IR(0, 0),IR(16119, 15)/* UnsignedInt8NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {8,IR(0, 0),IR(16134, 16)/* UnsignedInt16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {9,IR(0, 0),IR(16150, 16)/* UnsignedInt32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {10,IR(0, 0),IR(16166, 16)/* UnsignedInt64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491000,IR(0, 0),IR(16182, 19)/* SignedInt8PackedNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491001,IR(0, 0),IR(16201, 21)/* UnsignedInt8PackedNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491002,IR(0, 0),IR(16222, 12)/* FloatE4M3NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491003,IR(0, 0),IR(16234, 12)/* FloatE5M2NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {0,IR(0, 0),IR(16246, 12)/* RowMajorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {1,IR(0, 0),IR(16258, 15)/* ColumnMajorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {4202,IR(0, 0),IR(16273, 25)/* RowBlockedInterleavedARM */,IR(0, 0),IR(112, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {4203,IR(0, 0),IR(16298, 28)/* ColumnBlockedInterleavedARM */,IR(0, 0),IR(112, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {0,IR(0, 0),IR(16326, 8)/* NoneKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {1,IR(0, 0),IR(16334, 27)/* MatrixASignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {2,IR(0, 0),IR(16361, 27)/* MatrixBSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {4,IR(0, 0),IR(16388, 27)/* MatrixCSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {8,IR(0, 0),IR(16415, 32)/* MatrixResultSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {16,IR(0, 0),IR(16447, 26)/* SaturatingAccumulationKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {1,IR(0, 0),IR(16473, 4)/* Row */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {2,IR(0, 0),IR(16477, 7)/* Column */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {4,IR(0, 0),IR(16484, 4)/* 2x2 */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {0,IR(0, 0),IR(16488, 11)/* MatrixAKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {1,IR(0, 0),IR(16499, 11)/* MatrixBKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {2,IR(0, 0),IR(16510, 21)/* MatrixAccumulatorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {0,IR(0, 0),IR(16531, 11)/* RowMajorNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {1,IR(0, 0),IR(16542, 14)/* ColumnMajorNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {2,IR(0, 0),IR(16556, 21)/* InferencingOptimalNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {3,IR(0, 0),IR(16577, 18)/* TrainingOptimalNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {0,IR(0, 0),IR(15443, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(15455, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(15463, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(15471, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(15477, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(15484, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(15495, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {8,IR(0, 0),IR(15504, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(15517, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(15523, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(15533, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(15574, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(15579, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(15595, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(15609, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(15622, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(15634, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(15651, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(15663, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(15678, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(15691, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(15706, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(15724, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(15741, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(15762, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(15782, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(15802, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(15878, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {1,IR(0, 0),IR(15884, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {2,IR(0, 0),IR(15889, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {3,IR(0, 1),IR(15928, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {4,IR(1, 2),IR(15939, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {5,IR(0, 0),IR(15948, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {6,IR(0, 0),IR(15953, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {7,IR(0, 0),IR(15960, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {8,IR(0, 1),IR(15971, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {0,IR(0, 0),IR(15987, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(15997, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(16010, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(16595, 17)/* RelaxedPrecision */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {1,IR(0, 1),IR(16612, 7)/* SpecId */,IR(0, 0),IR(113, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {2,IR(0, 0),IR(16619, 6)/* Block */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {3,IR(0, 0),IR(16625, 12)/* BufferBlock */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),SPV_SPIRV_VERSION_WORD(1,3)}, // SPV_OPERAND_TYPE_DECORATION
  {4,IR(0, 0),IR(16637, 9)/* RowMajor */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5,IR(0, 0),IR(16646, 9)/* ColMajor */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6,IR(0, 1),IR(16655, 12)/* ArrayStride */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {7,IR(0, 1),IR(16667, 13)/* MatrixStride */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {8,IR(0, 0),IR(16680, 11)/* GLSLShared */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {9,IR(0, 0),IR(16691, 11)/* GLSLPacked */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {10,IR(0, 0),IR(16702, 8)/* CPacked */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {11,IR(3, 1),IR(16736, 8)/* BuiltIn */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {13,IR(0, 0),IR(16744, 14)/* NoPerspective */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {14,IR(0, 0),IR(16758, 5)/* Flat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {15,IR(0, 0),IR(16763, 6)/* Patch */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {16,IR(0, 0),IR(16769, 9)/* Centroid */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {17,IR(0, 0),IR(16778, 7)/* Sample */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {18,IR(0, 0),IR(16785, 10)/* Invariant */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {19,IR(0, 0),IR(16795, 9)/* Restrict */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {20,IR(0, 0),IR(16804, 8)/* Aliased */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {21,IR(0, 0),IR(16812, 9)/* Volatile */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {22,IR(0, 0),IR(16821, 9)/* Constant */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {23,IR(0, 0),IR(16830, 9)/* Coherent */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {24,IR(0, 0),IR(16839, 12)/* NonWritable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {25,IR(0, 0),IR(16851, 12)/* NonReadable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {26,IR(0, 0),IR(16863, 8)/* Uniform */,IR(0, 0),IR(115, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {27,IR(4, 1),IR(16897, 10)/* UniformId */,IR(0, 0),IR(115, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {28,IR(0, 0),IR(16907, 20)/* SaturatedConversion */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {29,IR(0, 1),IR(16927, 7)/* Stream */,IR(0, 0),IR(117, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {30,IR(0, 1),IR(16934, 9)/* Location */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {31,IR(0, 1),IR(16943, 10)/* Component */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {32,IR(0, 1),IR(16953, 6)/* Index */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {33,IR(0, 1),IR(16959, 8)/* Binding */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {34,IR(0, 1),IR(16967, 14)/* DescriptorSet */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {35,IR(0, 1),IR(16981, 7)/* Offset */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {36,IR(0, 1),IR(16988, 10)/* XfbBuffer */,IR(0, 0),IR(118, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {37,IR(0, 1),IR(16998, 10)/* XfbStride */,IR(0, 0),IR(118, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {38,IR(5, 1),IR(17054, 14)/* FuncParamAttr */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {39,IR(6, 1),IR(17102, 15)/* FPRoundingMode */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {40,IR(7, 1),IR(17152, 15)/* FPFastMathMode */,IR(0, 0),IR(119, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {41,IR(8, 2),IR(17229, 18)/* LinkageAttributes */,IR(0, 0),IR(121, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {42,IR(0, 0),IR(17247, 14)/* NoContraction */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {43,IR(0, 1),IR(17261, 21)/* InputAttachmentIndex */,IR(0, 0),IR(95, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {44,IR(0, 1),IR(17282, 10)/* Alignment */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {45,IR(0, 1),IR(17292, 14)/* MaxByteOffset */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {46,IR(10, 1),IR(17326, 12)/* AlignmentId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {47,IR(10, 1),IR(17338, 16)/* MaxByteOffsetId */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4216,IR(0, 0),IR(17354, 44)/* SaturatedToLargestFloat8NormalConversionEXT */,IR(0, 0),IR(122, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4469,IR(0, 0),IR(17398, 13)/* NoSignedWrap */,IR(0, 0),IR(1, 0),IR(178, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4470,IR(0, 0),IR(17411, 15)/* NoUnsignedWrap */,IR(0, 0),IR(1, 0),IR(178, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4487,IR(0, 0),IR(17426, 18)/* WeightTextureQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4488,IR(0, 0),IR(17444, 22)/* BlockMatchTextureQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4499,IR(0, 0),IR(17466, 22)/* BlockMatchSamplerQCOM */,IR(0, 0),IR(1, 0),IR(55, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4999,IR(0, 0),IR(17488, 18)/* ExplicitInterpAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5019,IR(10, 1),IR(17506, 32)/* NodeSharesPayloadLimitsWithAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5020,IR(10, 1),IR(17538, 20)/* NodeMaxPayloadsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5078,IR(0, 0),IR(17558, 23)/* TrackFinishWritingAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5091,IR(10, 1),IR(17581, 20)/* PayloadNodeNameAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5098,IR(10, 1),IR(17601, 25)/* PayloadNodeBaseIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5099,IR(0, 0),IR(17626, 27)/* PayloadNodeSparseArrayAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5100,IR(10, 1),IR(17653, 25)/* PayloadNodeArraySizeAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5105,IR(0, 0),IR(17678, 28)/* PayloadDispatchIndirectAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5248,IR(0, 0),IR(17706, 19)/* OverrideCoverageNV */,IR(0, 0),IR(123, 1),IR(66, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5250,IR(0, 0),IR(17725, 14)/* PassthroughNV */,IR(0, 0),IR(124, 1),IR(67, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5252,IR(0, 0),IR(17739, 19)/* ViewportRelativeNV */,IR(0, 0),IR(94, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5256,IR(0, 1),IR(17758, 28)/* SecondaryViewportRelativeNV */,IR(0, 0),IR(46, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5271,IR(0, 0),IR(17786, 16)/* PerPrimitiveEXT */,IR(72, 1),IR(125, 2),IR(179, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5272,IR(0, 0),IR(17817, 10)/* PerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5273,IR(0, 0),IR(17827, 10)/* PerTaskNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5285,IR(0, 0),IR(17837, 13)/* PerVertexKHR */,IR(73, 1),IR(51, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5300,IR(0, 0),IR(17862, 11)/* NonUniform */,IR(74, 1),IR(97, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5355,IR(0, 0),IR(17887, 16)/* RestrictPointer */,IR(75, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5356,IR(0, 0),IR(17922, 15)/* AliasedPointer */,IR(76, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5386,IR(0, 0),IR(17955, 30)/* HitObjectShaderRecordBufferNV */,IR(0, 0),IR(127, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5389,IR(0, 0),IR(17985, 31)/* HitObjectShaderRecordBufferEXT */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5398,IR(0, 0),IR(18016, 18)/* BindlessSamplerNV */,IR(0, 0),IR(129, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5399,IR(0, 0),IR(18034, 16)/* BindlessImageNV */,IR(0, 0),IR(129, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5400,IR(0, 0),IR(18050, 15)/* BoundSamplerNV */,IR(0, 0),IR(129, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5401,IR(0, 0),IR(18065, 13)/* BoundImageNV */,IR(0, 0),IR(129, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5599,IR(0, 1),IR(18078, 14)/* SIMTCallINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5602,IR(0, 0),IR(18092, 26)/* ReferencedIndirectlyINTEL */,IR(0, 0),IR(131, 1),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5607,IR(11, 1),IR(18118, 13)/* ClobberINTEL */,IR(0, 0),IR(132, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5608,IR(0, 0),IR(18131, 17)/* SideEffectsINTEL */,IR(0, 0),IR(132, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5624,IR(0, 0),IR(18148, 27)/* VectorComputeVariableINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5625,IR(0, 1),IR(18175, 21)/* FuncParamIOKindINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5626,IR(0, 0),IR(18196, 27)/* VectorComputeFunctionINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5627,IR(0, 0),IR(18223, 15)/* StackCallINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5628,IR(0, 1),IR(18238, 26)/* GlobalVariableOffsetINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5634,IR(10, 1),IR(18264, 14)/* CounterBuffer */,IR(77, 1),IR(1, 0),IR(181, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5635,IR(11, 1),IR(18302, 13)/* UserSemantic */,IR(78, 1),IR(1, 0),IR(181, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5636,IR(11, 1),IR(18334, 15)/* UserTypeGOOGLE */,IR(0, 0),IR(1, 0),IR(182, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5822,IR(12, 2),IR(18349, 26)/* FunctionRoundingModeINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5823,IR(14, 2),IR(18406, 24)/* FunctionDenormModeINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5825,IR(0, 0),IR(18430, 15)/* RegisterALTERA */,IR(79, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5826,IR(11, 1),IR(18459, 13)/* MemoryALTERA */,IR(80, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5827,IR(0, 1),IR(18484, 15)/* NumbanksALTERA */,IR(81, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5828,IR(0, 1),IR(18513, 16)/* BankwidthALTERA */,IR(82, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5829,IR(0, 1),IR(18544, 23)/* MaxPrivateCopiesALTERA */,IR(83, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5830,IR(0, 0),IR(18589, 17)/* SinglepumpALTERA */,IR(84, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5831,IR(0, 0),IR(18622, 17)/* DoublepumpALTERA */,IR(85, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5832,IR(0, 1),IR(18655, 20)/* MaxReplicatesALTERA */,IR(86, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5833,IR(0, 0),IR(18694, 21)/* SimpleDualPortALTERA */,IR(87, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5834,IR(16, 2),IR(18735, 12)/* MergeALTERA */,IR(88, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5835,IR(18, 1),IR(18800, 15)/* BankBitsALTERA */,IR(89, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5836,IR(0, 1),IR(18829, 21)/* ForcePow2DepthALTERA */,IR(90, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5883,IR(0, 1),IR(18870, 17)/* StridesizeALTERA */,IR(91, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5884,IR(0, 1),IR(18903, 15)/* WordsizeALTERA */,IR(92, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5885,IR(0, 0),IR(18932, 19)/* TrueDualPortALTERA */,IR(93, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5899,IR(0, 0),IR(18969, 20)/* BurstCoalesceALTERA */,IR(94, 1),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5900,IR(0, 1),IR(19008, 16)/* CacheSizeALTERA */,IR(95, 1),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5901,IR(0, 0),IR(19039, 29)/* DontStaticallyCoalesceALTERA */,IR(96, 1),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5902,IR(0, 1),IR(19096, 15)/* PrefetchALTERA */,IR(97, 1),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5905,IR(0, 0),IR(19125, 18)/* StallEnableALTERA */,IR(98, 1),IR(106, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5907,IR(0, 0),IR(19160, 26)/* FuseLoopsInFunctionALTERA */,IR(99, 1),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5909,IR(1, 2),IR(19211, 20)/* MathOpDSPModeALTERA */,IR(100, 1),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5914,IR(10, 1),IR(19250, 16)/* AliasScopeINTEL */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5915,IR(10, 1),IR(19266, 13)/* NoAliasINTEL */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5917,IR(0, 1),IR(19279, 25)/* InitiationIntervalALTERA */,IR(101, 1),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5918,IR(0, 1),IR(19328, 21)/* MaxConcurrencyALTERA */,IR(102, 1),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5919,IR(0, 1),IR(19369, 21)/* PipelineEnableALTERA */,IR(103, 1),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5921,IR(0, 1),IR(19410, 21)/* BufferLocationALTERA */,IR(104, 1),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5944,IR(0, 1),IR(19451, 20)/* IOPipeStorageALTERA */,IR(105, 1),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6080,IR(19, 2),IR(19524, 31)/* FunctionFloatingPointModeINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6085,IR(0, 0),IR(19555, 25)/* SingleElementVectorINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6087,IR(0, 0),IR(19580, 35)/* VectorComputeCallableFunctionINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6140,IR(0, 0),IR(19615, 18)/* MediaBlockIOINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6151,IR(0, 0),IR(19633, 16)/* StallFreeALTERA */,IR(106, 1),IR(142, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6170,IR(21, 1),IR(19695, 26)/* FPMaxErrorDecorationINTEL */,IR(0, 0),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6172,IR(0, 1),IR(19721, 26)/* LatencyControlLabelALTERA */,IR(107, 1),IR(144, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6173,IR(22, 3),IR(19772, 31)/* LatencyControlConstraintALTERA */,IR(108, 1),IR(144, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6175,IR(0, 0),IR(19833, 28)/* ConduitKernelArgumentALTERA */,IR(109, 1),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6176,IR(0, 0),IR(19888, 32)/* RegisterMapKernelArgumentALTERA */,IR(110, 1),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6177,IR(0, 1),IR(19951, 34)/* MMHostInterfaceAddressWidthALTERA */,IR(111, 1),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6178,IR(0, 1),IR(20018, 31)/* MMHostInterfaceDataWidthALTERA */,IR(112, 1),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6179,IR(0, 1),IR(20079, 29)/* MMHostInterfaceLatencyALTERA */,IR(113, 1),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6180,IR(25, 1),IR(20170, 35)/* MMHostInterfaceReadWriteModeALTERA */,IR(114, 1),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6181,IR(0, 1),IR(20239, 30)/* MMHostInterfaceMaxBurstALTERA */,IR(115, 1),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6182,IR(0, 1),IR(20298, 33)/* MMHostInterfaceWaitRequestALTERA */,IR(116, 1),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6183,IR(0, 0),IR(20363, 27)/* StableKernelArgumentALTERA */,IR(117, 1),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6188,IR(26, 2),IR(20455, 16)/* HostAccessINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6190,IR(28, 1),IR(20518, 15)/* InitModeALTERA */,IR(118, 1),IR(147, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6191,IR(0, 1),IR(20547, 29)/* ImplementInRegisterMapALTERA */,IR(119, 1),IR(147, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6247,IR(10, 1),IR(20604, 17)/* ConditionalINTEL */,IR(0, 0),IR(111, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6442,IR(29, 2),IR(20657, 22)/* CacheControlLoadINTEL */,IR(0, 0),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6443,IR(31, 2),IR(20716, 23)/* CacheControlStoreINTEL */,IR(0, 0),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {0,IR(0, 0),IR(20739, 3)/* 1D */,IR(0, 0),IR(72, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {1,IR(0, 0),IR(20742, 3)/* 2D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {2,IR(0, 0),IR(20745, 3)/* 3D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {3,IR(0, 0),IR(20748, 5)/* Cube */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {4,IR(0, 0),IR(20753, 5)/* Rect */,IR(0, 0),IR(71, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {5,IR(0, 0),IR(20758, 7)/* Buffer */,IR(0, 0),IR(73, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {6,IR(0, 0),IR(20765, 12)/* SubpassData */,IR(0, 0),IR(95, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {4173,IR(0, 0),IR(20777, 17)/* TileImageDataEXT */,IR(0, 0),IR(149, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {0,IR(0, 1),IR(20794, 12)/* Invocations */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {1,IR(0, 0),IR(20806, 13)/* SpacingEqual */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {2,IR(0, 0),IR(20819, 22)/* SpacingFractionalEven */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {3,IR(0, 0),IR(20841, 21)/* SpacingFractionalOdd */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4,IR(0, 0),IR(20862, 14)/* VertexOrderCw */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5,IR(0, 0),IR(20876, 15)/* VertexOrderCcw */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6,IR(0, 0),IR(20891, 19)/* PixelCenterInteger */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {7,IR(0, 0),IR(20910, 16)/* OriginUpperLeft */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {8,IR(0, 0),IR(20926, 16)/* OriginLowerLeft */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {9,IR(0, 0),IR(20942, 19)/* EarlyFragmentTests */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {10,IR(0, 0),IR(20961, 10)/* PointMode */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {11,IR(0, 0),IR(20971, 4)/* Xfb */,IR(0, 0),IR(118, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {12,IR(0, 0),IR(20975, 15)/* DepthReplacing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {14,IR(0, 0),IR(20990, 13)/* DepthGreater */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {15,IR(0, 0),IR(21003, 10)/* DepthLess */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {16,IR(0, 0),IR(21013, 15)/* DepthUnchanged */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {17,IR(22, 3),IR(21028, 10)/* LocalSize */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {18,IR(22, 3),IR(21038, 14)/* LocalSizeHint */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {19,IR(0, 0),IR(21052, 12)/* InputPoints */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {20,IR(0, 0),IR(21064, 11)/* InputLines */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {21,IR(0, 0),IR(21075, 20)/* InputLinesAdjacency */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {22,IR(0, 0),IR(21095, 10)/* Triangles */,IR(0, 0),IR(12, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {23,IR(0, 0),IR(21105, 24)/* InputTrianglesAdjacency */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {24,IR(0, 0),IR(21129, 6)/* Quads */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {25,IR(0, 0),IR(21135, 9)/* Isolines */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {26,IR(0, 1),IR(21144, 15)/* OutputVertices */,IR(0, 0),IR(150, 4),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {27,IR(0, 0),IR(21159, 13)/* OutputPoints */,IR(0, 0),IR(154, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {28,IR(0, 0),IR(21172, 16)/* OutputLineStrip */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {29,IR(0, 0),IR(21188, 20)/* OutputTriangleStrip */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {30,IR(0, 1),IR(21208, 12)/* VecTypeHint */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {31,IR(0, 0),IR(21220, 15)/* ContractionOff */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {33,IR(0, 0),IR(21235, 12)/* Initializer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {34,IR(0, 0),IR(21247, 10)/* Finalizer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {35,IR(0, 1),IR(6129, 13)/* SubgroupSize */,IR(0, 0),IR(157, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {36,IR(0, 1),IR(21257, 22)/* SubgroupsPerWorkgroup */,IR(0, 0),IR(157, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {37,IR(10, 1),IR(21279, 24)/* SubgroupsPerWorkgroupId */,IR(0, 0),IR(157, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {38,IR(33, 3),IR(21303, 12)/* LocalSizeId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {39,IR(33, 3),IR(21315, 16)/* LocalSizeHintId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4169,IR(0, 0),IR(21331, 34)/* NonCoherentColorAttachmentReadEXT */,IR(0, 0),IR(149, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4170,IR(0, 0),IR(21365, 34)/* NonCoherentDepthAttachmentReadEXT */,IR(0, 0),IR(158, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4171,IR(0, 0),IR(21399, 36)/* NonCoherentStencilAttachmentReadEXT */,IR(0, 0),IR(159, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4421,IR(0, 0),IR(21435, 30)/* SubgroupUniformControlFlowKHR */,IR(0, 0),IR(3, 1),IR(183, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4446,IR(0, 0),IR(21465, 18)/* PostDepthCoverage */,IR(0, 0),IR(160, 1),IR(45, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4459,IR(0, 1),IR(10328, 15)/* DenormPreserve */,IR(0, 0),IR(161, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4460,IR(0, 1),IR(10343, 18)/* DenormFlushToZero */,IR(0, 0),IR(162, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4461,IR(0, 1),IR(10361, 25)/* SignedZeroInfNanPreserve */,IR(0, 0),IR(163, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4462,IR(0, 1),IR(10386, 16)/* RoundingModeRTE */,IR(0, 0),IR(164, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4463,IR(0, 1),IR(10402, 16)/* RoundingModeRTZ */,IR(0, 0),IR(165, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4489,IR(0, 0),IR(21483, 34)/* NonCoherentTileAttachmentReadQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4490,IR(22, 3),IR(21517, 20)/* TileShadingRateQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5017,IR(0, 0),IR(21537, 29)/* EarlyAndLateFragmentTestsAMD */,IR(0, 0),IR(3, 1),IR(184, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5027,IR(0, 0),IR(21566, 23)/* StencilRefReplacingEXT */,IR(0, 0),IR(42, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5069,IR(0, 0),IR(21589, 15)/* CoalescingAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5070,IR(10, 1),IR(21604, 15)/* IsApiEntryAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5071,IR(10, 1),IR(21619, 21)/* MaxNodeRecursionAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5072,IR(33, 3),IR(21640, 24)/* StaticNumWorkgroupsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5073,IR(10, 1),IR(7022, 16)/* ShaderIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5077,IR(33, 3),IR(21664, 21)/* MaxNumWorkgroupsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5079,IR(0, 0),IR(21685, 28)/* StencilRefUnchangedFrontAMD */,IR(0, 0),IR(42, 1),IR(185, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5080,IR(0, 0),IR(21713, 26)/* StencilRefGreaterFrontAMD */,IR(0, 0),IR(42, 1),IR(185, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5081,IR(0, 0),IR(21739, 23)/* StencilRefLessFrontAMD */,IR(0, 0),IR(42, 1),IR(185, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5082,IR(0, 0),IR(21762, 27)/* StencilRefUnchangedBackAMD */,IR(0, 0),IR(42, 1),IR(185, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5083,IR(0, 0),IR(21789, 25)/* StencilRefGreaterBackAMD */,IR(0, 0),IR(42, 1),IR(185, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5084,IR(0, 0),IR(21814, 22)/* StencilRefLessBackAMD */,IR(0, 0),IR(42, 1),IR(185, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5088,IR(0, 0),IR(21836, 19)/* QuadDerivativesKHR */,IR(0, 0),IR(166, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5089,IR(0, 0),IR(21855, 20)/* RequireFullQuadsKHR */,IR(0, 0),IR(166, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5102,IR(36, 2),IR(21875, 20)/* SharesInputWithAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5269,IR(0, 0),IR(21895, 15)/* OutputLinesEXT */,IR(120, 1),IR(125, 2),IR(179, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5270,IR(0, 1),IR(21924, 20)/* OutputPrimitivesEXT */,IR(121, 1),IR(125, 2),IR(179, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5289,IR(0, 0),IR(21963, 24)/* DerivativeGroupQuadsKHR */,IR(122, 1),IR(167, 1),IR(73, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5290,IR(0, 0),IR(22010, 25)/* DerivativeGroupLinearKHR */,IR(123, 1),IR(168, 1),IR(73, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5298,IR(0, 0),IR(22059, 19)/* OutputTrianglesEXT */,IR(124, 1),IR(125, 2),IR(179, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5366,IR(0, 0),IR(22096, 25)/* PixelInterlockOrderedEXT */,IR(0, 0),IR(169, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5367,IR(0, 0),IR(22121, 27)/* PixelInterlockUnorderedEXT */,IR(0, 0),IR(169, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5368,IR(0, 0),IR(22148, 26)/* SampleInterlockOrderedEXT */,IR(0, 0),IR(170, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5369,IR(0, 0),IR(22174, 28)/* SampleInterlockUnorderedEXT */,IR(0, 0),IR(170, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5370,IR(0, 0),IR(22202, 31)/* ShadingRateInterlockOrderedEXT */,IR(0, 0),IR(171, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5371,IR(0, 0),IR(22233, 33)/* ShadingRateInterlockUnorderedEXT */,IR(0, 0),IR(171, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5427,IR(0, 0),IR(12584, 23)/* Shader64BitIndexingEXT */,IR(0, 0),IR(172, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5618,IR(0, 1),IR(22266, 27)/* SharedLocalMemorySizeINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5620,IR(0, 1),IR(22293, 21)/* RoundingModeRTPINTEL */,IR(0, 0),IR(173, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5621,IR(0, 1),IR(22314, 21)/* RoundingModeRTNINTEL */,IR(0, 0),IR(173, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5622,IR(0, 1),IR(22335, 26)/* FloatingPointModeALTINTEL */,IR(0, 0),IR(173, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5623,IR(0, 1),IR(22361, 27)/* FloatingPointModeIEEEINTEL */,IR(0, 0),IR(173, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5893,IR(22, 3),IR(22388, 22)/* MaxWorkgroupSizeINTEL */,IR(0, 0),IR(174, 1),IR(115, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5894,IR(0, 1),IR(22410, 16)/* MaxWorkDimINTEL */,IR(0, 0),IR(174, 1),IR(115, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5895,IR(0, 0),IR(22426, 20)/* NoGlobalOffsetINTEL */,IR(0, 0),IR(174, 1),IR(115, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5896,IR(0, 1),IR(22446, 22)/* NumSIMDWorkitemsINTEL */,IR(0, 0),IR(107, 1),IR(115, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5903,IR(0, 1),IR(22468, 28)/* SchedulerTargetFmaxMhzINTEL */,IR(0, 0),IR(107, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6023,IR(0, 0),IR(22496, 24)/* MaximallyReconvergesKHR */,IR(0, 0),IR(3, 1),IR(187, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6028,IR(36, 2),IR(22520, 18)/* FPFastMathDefault */,IR(0, 0),IR(175, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6154,IR(0, 1),IR(22538, 24)/* StreamingInterfaceINTEL */,IR(0, 0),IR(107, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6160,IR(0, 1),IR(22562, 26)/* RegisterMapInterfaceINTEL */,IR(0, 0),IR(176, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6417,IR(0, 1),IR(22588, 23)/* NamedBarrierCountINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6461,IR(0, 1),IR(22611, 22)/* MaximumRegistersINTEL */,IR(0, 0),IR(177, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6462,IR(10, 1),IR(22633, 24)/* MaximumRegistersIdINTEL */,IR(0, 0),IR(177, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6463,IR(38, 1),IR(22708, 27)/* NamedMaximumRegistersINTEL */,IR(0, 0),IR(177, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {0,IR(0, 0),IR(22735, 7)/* Vertex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {1,IR(0, 0),IR(22742, 20)/* TessellationControl */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {2,IR(0, 0),IR(22762, 23)/* TessellationEvaluation */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {3,IR(0, 0),IR(5610, 9)/* Geometry */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {4,IR(0, 0),IR(15978, 9)/* Fragment */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5,IR(0, 0),IR(22785, 10)/* GLCompute */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {6,IR(0, 0),IR(5377, 7)/* Kernel */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5267,IR(0, 0),IR(22795, 7)/* TaskNV */,IR(0, 0),IR(50, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5268,IR(0, 0),IR(22802, 7)/* MeshNV */,IR(0, 0),IR(50, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5313,IR(0, 0),IR(22809, 17)/* RayGenerationKHR */,IR(125, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5314,IR(0, 0),IR(22842, 16)/* IntersectionKHR */,IR(126, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5315,IR(0, 0),IR(22873, 10)/* AnyHitKHR */,IR(127, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5316,IR(0, 0),IR(22892, 14)/* ClosestHitKHR */,IR(128, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5317,IR(0, 0),IR(22919, 8)/* MissKHR */,IR(129, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5318,IR(0, 0),IR(22934, 12)/* CallableKHR */,IR(130, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5364,IR(0, 0),IR(22957, 8)/* TaskEXT */,IR(0, 0),IR(53, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5365,IR(0, 0),IR(22965, 8)/* MeshEXT */,IR(0, 0),IR(53, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {0,IR(0, 0),IR(22973, 9)/* Preserve */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPDENORM_MODE
  {1,IR(0, 0),IR(22982, 12)/* FlushToZero */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPDENORM_MODE
  {0,IR(0, 0),IR(22994, 12)/* BFloat16KHR */,IR(0, 0),IR(89, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {4214,IR(0, 0),IR(23006, 14)/* Float8E4M3EXT */,IR(0, 0),IR(122, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {4215,IR(0, 0),IR(23020, 14)/* Float8E5M2EXT */,IR(0, 0),IR(122, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {0,IR(0, 0),IR(23034, 5)/* IEEE */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPOPERATION_MODE
  {1,IR(0, 0),IR(23039, 4)/* ALT */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPOPERATION_MODE
  {0,IR(0, 0),IR(15574, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {1,IR(0, 0),IR(23043, 7)/* NotNaN */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {2,IR(0, 0),IR(23050, 7)/* NotInf */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {4,IR(0, 0),IR(23057, 4)/* NSZ */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {8,IR(0, 0),IR(23061, 11)/* AllowRecip */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {16,IR(0, 0),IR(23072, 5)/* Fast */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {65536,IR(0, 0),IR(23077, 14)/* AllowContract */,IR(131, 1),IR(178, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {131072,IR(0, 0),IR(23114, 13)/* AllowReassoc */,IR(132, 1),IR(178, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {262144,IR(0, 0),IR(23145, 15)/* AllowTransform */,IR(0, 0),IR(175, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {0,IR(0, 0),IR(23160, 4)/* RTE */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {1,IR(0, 0),IR(23164, 4)/* RTZ */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {2,IR(0, 0),IR(23168, 4)/* RTP */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {3,IR(0, 0),IR(23172, 4)/* RTN */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {1,IR(0, 0),IR(23176, 16)/* Vertical2Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {2,IR(0, 0),IR(23192, 16)/* Vertical4Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {4,IR(0, 0),IR(23208, 18)/* Horizontal2Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {8,IR(0, 0),IR(23226, 18)/* Horizontal4Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {0,IR(0, 0),IR(15574, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {1,IR(0, 0),IR(23244, 7)/* Inline */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {2,IR(0, 0),IR(23251, 11)/* DontInline */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {4,IR(0, 0),IR(23262, 5)/* Pure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {8,IR(0, 0),IR(23267, 6)/* Const */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {65536,IR(0, 0),IR(14581, 11)/* OptNoneEXT */,IR(66, 1),IR(180, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {0,IR(0, 0),IR(23273, 5)/* Zext */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {1,IR(0, 0),IR(23278, 5)/* Sext */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {2,IR(0, 0),IR(23283, 6)/* ByVal */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {3,IR(0, 0),IR(23289, 5)/* Sret */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {4,IR(0, 0),IR(23294, 8)/* NoAlias */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {5,IR(0, 0),IR(23302, 10)/* NoCapture */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {6,IR(0, 0),IR(23312, 8)/* NoWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {7,IR(0, 0),IR(23320, 12)/* NoReadWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {5940,IR(0, 0),IR(23332, 21)/* RuntimeAlignedALTERA */,IR(133, 1),IR(181, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {0,IR(0, 0),IR(23373, 7)/* Reduce */,IR(0, 0),IR(182, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {1,IR(0, 0),IR(23380, 14)/* InclusiveScan */,IR(0, 0),IR(182, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {2,IR(0, 0),IR(23394, 14)/* ExclusiveScan */,IR(0, 0),IR(182, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {3,IR(0, 0),IR(23408, 16)/* ClusteredReduce */,IR(0, 0),IR(185, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {6,IR(0, 0),IR(23424, 20)/* PartitionedReduceNV */,IR(0, 0),IR(186, 1),IR(75, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {7,IR(0, 0),IR(23444, 27)/* PartitionedInclusiveScanNV */,IR(0, 0),IR(186, 1),IR(75, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {8,IR(0, 0),IR(23471, 27)/* PartitionedExclusiveScanNV */,IR(0, 0),IR(186, 1),IR(75, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {0,IR(0, 0),IR(23498, 10)/* NoneINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {1,IR(0, 0),IR(23508, 10)/* ReadINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {2,IR(0, 0),IR(23518, 11)/* WriteINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {3,IR(0, 0),IR(23529, 15)/* ReadWriteINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {0,IR(0, 0),IR(15574, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {1,IR(10, 1),IR(23544, 5)/* Bias */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {2,IR(10, 1),IR(23549, 4)/* Lod */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {4,IR(36, 2),IR(23553, 5)/* Grad */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {8,IR(10, 1),IR(23558, 12)/* ConstOffset */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {16,IR(10, 1),IR(16981, 7)/* Offset */,IR(0, 0),IR(187, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {32,IR(10, 1),IR(23570, 13)/* ConstOffsets */,IR(0, 0),IR(187, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {64,IR(10, 1),IR(16778, 7)/* Sample */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {128,IR(10, 1),IR(9161, 7)/* MinLod */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {256,IR(4, 1),IR(23583, 19)/* MakeTexelAvailable */,IR(134, 1),IR(189, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {512,IR(4, 1),IR(23624, 17)/* MakeTexelVisible */,IR(135, 1),IR(189, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {1024,IR(0, 0),IR(23661, 16)/* NonPrivateTexel */,IR(136, 1),IR(189, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {2048,IR(0, 0),IR(23696, 14)/* VolatileTexel */,IR(137, 1),IR(189, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {4096,IR(0, 0),IR(23727, 11)/* SignExtend */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {8192,IR(0, 0),IR(23738, 11)/* ZeroExtend */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {16384,IR(0, 0),IR(23749, 12)/* Nontemporal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {65536,IR(10, 1),IR(23761, 8)/* Offsets */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {0,IR(0, 0),IR(23769, 10)/* SnormInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {1,IR(0, 0),IR(23779, 11)/* SnormInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {2,IR(0, 0),IR(23790, 10)/* UnormInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {3,IR(0, 0),IR(23800, 11)/* UnormInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {4,IR(0, 0),IR(23811, 14)/* UnormShort565 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {5,IR(0, 0),IR(23825, 14)/* UnormShort555 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {6,IR(0, 0),IR(23839, 15)/* UnormInt101010 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {7,IR(0, 0),IR(23854, 11)/* SignedInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {8,IR(0, 0),IR(23865, 12)/* SignedInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {9,IR(0, 0),IR(23877, 12)/* SignedInt32 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {10,IR(0, 0),IR(23889, 13)/* UnsignedInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {11,IR(0, 0),IR(23902, 14)/* UnsignedInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {12,IR(0, 0),IR(23916, 14)/* UnsignedInt32 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {13,IR(0, 0),IR(23930, 10)/* HalfFloat */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {14,IR(0, 0),IR(15471, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {15,IR(0, 0),IR(23940, 11)/* UnormInt24 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {16,IR(0, 0),IR(23951, 17)/* UnormInt101010_2 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {17,IR(0, 0),IR(23968, 16)/* UnormInt10X6EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {19,IR(0, 0),IR(23984, 20)/* UnsignedIntRaw10EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {20,IR(0, 0),IR(24004, 20)/* UnsignedIntRaw12EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {21,IR(0, 0),IR(24024, 20)/* UnormInt2_101010EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {22,IR(0, 0),IR(24044, 19)/* UnsignedInt10X6EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {23,IR(0, 0),IR(24063, 19)/* UnsignedInt12X4EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {24,IR(0, 0),IR(24082, 19)/* UnsignedInt14X2EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {25,IR(0, 0),IR(24101, 16)/* UnormInt12X4EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {26,IR(0, 0),IR(24117, 16)/* UnormInt14X2EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {0,IR(0, 0),IR(24133, 2)/* R */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {1,IR(0, 0),IR(24135, 2)/* A */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {2,IR(0, 0),IR(24137, 3)/* RG */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {3,IR(0, 0),IR(24140, 3)/* RA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {4,IR(0, 0),IR(24143, 4)/* RGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {5,IR(0, 0),IR(24147, 5)/* RGBA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {6,IR(0, 0),IR(24152, 5)/* BGRA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {7,IR(0, 0),IR(24157, 5)/* ARGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {8,IR(0, 0),IR(24162, 10)/* Intensity */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {9,IR(0, 0),IR(24172, 10)/* Luminance */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {10,IR(0, 0),IR(24182, 3)/* Rx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {11,IR(0, 0),IR(24185, 4)/* RGx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {12,IR(0, 0),IR(24189, 5)/* RGBx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {13,IR(0, 0),IR(24194, 6)/* Depth */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {14,IR(0, 0),IR(24200, 13)/* DepthStencil */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {15,IR(0, 0),IR(24213, 5)/* sRGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {16,IR(0, 0),IR(24218, 6)/* sRGBx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {17,IR(0, 0),IR(24224, 6)/* sRGBA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {18,IR(0, 0),IR(24230, 6)/* sBGRA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {19,IR(0, 0),IR(24236, 5)/* ABGR */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {0,IR(0, 0),IR(24241, 28)/* InitOnDeviceReprogramALTERA */,IR(138, 1),IR(147, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {1,IR(0, 0),IR(24296, 24)/* InitOnDeviceResetALTERA */,IR(139, 1),IR(147, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {0,IR(0, 0),IR(24343, 7)/* NoWait */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {1,IR(0, 0),IR(24350, 11)/* WaitKernel */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {2,IR(0, 0),IR(24361, 14)/* WaitWorkGroup */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {0,IR(0, 0),IR(15574, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {1,IR(0, 0),IR(24375, 12)/* CmdExecTime */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {0,IR(0, 0),IR(15574, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {1,IR(0, 0),IR(24387, 13)/* MayUsePrintf */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {0,IR(0, 0),IR(24400, 7)/* Export */,IR(0, 0),IR(121, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {1,IR(0, 0),IR(24407, 7)/* Import */,IR(0, 0),IR(121, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {2,IR(0, 0),IR(24414, 12)/* LinkOnceODR */,IR(0, 0),IR(121, 1),IR(188, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {0,IR(0, 0),IR(24426, 14)/* UncachedINTEL */,IR(0, 0),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {1,IR(0, 0),IR(24440, 12)/* CachedINTEL */,IR(0, 0),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {2,IR(0, 0),IR(24452, 15)/* StreamingINTEL */,IR(0, 0),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {3,IR(0, 0),IR(24467, 25)/* InvalidateAfterReadINTEL */,IR(0, 0),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {4,IR(0, 0),IR(24492, 17)/* ConstCachedINTEL */,IR(0, 0),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {0,IR(0, 0),IR(15574, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {1,IR(0, 0),IR(24509, 7)/* Unroll */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {2,IR(0, 0),IR(24516, 11)/* DontUnroll */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {4,IR(0, 0),IR(24527, 19)/* DependencyInfinite */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {8,IR(0, 1),IR(24546, 17)/* DependencyLength */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {16,IR(0, 1),IR(24563, 14)/* MinIterations */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {32,IR(0, 1),IR(24577, 14)/* MaxIterations */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {64,IR(0, 1),IR(24591, 18)/* IterationMultiple */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {128,IR(0, 1),IR(24609, 10)/* PeelCount */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {256,IR(0, 1),IR(24619, 13)/* PartialCount */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {65536,IR(0, 1),IR(19279, 25)/* InitiationIntervalALTERA */,IR(101, 1),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {131072,IR(0, 1),IR(19328, 21)/* MaxConcurrencyALTERA */,IR(102, 1),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {262144,IR(0, 1),IR(24632, 22)/* DependencyArrayALTERA */,IR(140, 1),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {524288,IR(0, 1),IR(19369, 21)/* PipelineEnableALTERA */,IR(103, 1),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {1048576,IR(0, 1),IR(24675, 19)/* LoopCoalesceALTERA */,IR(141, 1),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {2097152,IR(0, 1),IR(24712, 22)/* MaxInterleavingALTERA */,IR(142, 1),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {4194304,IR(0, 1),IR(24755, 27)/* SpeculatedIterationsALTERA */,IR(143, 1),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {8388608,IR(0, 0),IR(24808, 15)/* NoFusionALTERA */,IR(144, 1),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {16777216,IR(0, 1),IR(24837, 16)/* LoopCountALTERA */,IR(145, 1),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {33554432,IR(0, 1),IR(24868, 27)/* MaxReinvocationDelayALTERA */,IR(146, 1),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {0,IR(0, 0),IR(15574, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {1,IR(0, 0),IR(24921, 29)/* MatrixASignedComponentsINTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {2,IR(0, 0),IR(24950, 29)/* MatrixBSignedComponentsINTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {4,IR(0, 0),IR(24979, 21)/* MatrixCBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {8,IR(0, 0),IR(25000, 26)/* MatrixResultBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {16,IR(0, 0),IR(25026, 23)/* MatrixAPackedInt8INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {32,IR(0, 0),IR(25049, 23)/* MatrixBPackedInt8INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {64,IR(0, 0),IR(25072, 23)/* MatrixAPackedInt4INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {128,IR(0, 0),IR(25095, 23)/* MatrixBPackedInt4INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {256,IR(0, 0),IR(25118, 17)/* MatrixATF32INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {512,IR(0, 0),IR(25135, 17)/* MatrixBTF32INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {1024,IR(0, 0),IR(25152, 26)/* MatrixAPackedFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {2048,IR(0, 0),IR(25178, 26)/* MatrixBPackedFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {4096,IR(0, 0),IR(25204, 27)/* MatrixAPackedBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {8192,IR(0, 0),IR(25231, 27)/* MatrixBPackedBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {0,IR(0, 0),IR(15574, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {1,IR(0, 0),IR(16812, 9)/* Volatile */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {2,IR(0, 1),IR(25258, 8)/* Aligned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {4,IR(0, 0),IR(23749, 12)/* Nontemporal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {8,IR(4, 1),IR(25266, 21)/* MakePointerAvailable */,IR(147, 1),IR(189, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {16,IR(4, 1),IR(25311, 19)/* MakePointerVisible */,IR(148, 1),IR(189, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {32,IR(0, 0),IR(25352, 18)/* NonPrivatePointer */,IR(149, 1),IR(189, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {65536,IR(10, 1),IR(25391, 20)/* AliasScopeINTELMask */,IR(0, 0),IR(138, 1),IR(124, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {131072,IR(10, 1),IR(25411, 17)/* NoAliasINTELMask */,IR(0, 0),IR(138, 1),IR(124, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {0,IR(0, 0),IR(25428, 7)/* Simple */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {1,IR(0, 0),IR(25435, 8)/* GLSL450 */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {2,IR(0, 0),IR(25443, 7)/* OpenCL */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {3,IR(0, 0),IR(25450, 7)/* Vulkan */,IR(150, 1),IR(189, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {0,IR(0, 0),IR(25467, 8)/* Relaxed */,IR(151, 1),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {2,IR(0, 0),IR(25475, 8)/* Acquire */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {4,IR(0, 0),IR(25483, 8)/* Release */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {8,IR(0, 0),IR(25491, 15)/* AcquireRelease */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {16,IR(0, 0),IR(25506, 23)/* SequentiallyConsistent */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {64,IR(0, 0),IR(25529, 14)/* UniformMemory */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {128,IR(0, 0),IR(25543, 15)/* SubgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {256,IR(0, 0),IR(25558, 16)/* WorkgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {512,IR(0, 0),IR(25574, 21)/* CrossWorkgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {1024,IR(0, 0),IR(25595, 20)/* AtomicCounterMemory */,IR(0, 0),IR(82, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {2048,IR(0, 0),IR(25615, 12)/* ImageMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {4096,IR(0, 0),IR(25627, 13)/* OutputMemory */,IR(152, 1),IR(189, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {8192,IR(0, 0),IR(25656, 14)/* MakeAvailable */,IR(153, 1),IR(189, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {16384,IR(0, 0),IR(25687, 12)/* MakeVisible */,IR(154, 1),IR(189, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {32768,IR(0, 0),IR(16812, 9)/* Volatile */,IR(0, 0),IR(189, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {0,IR(0, 0),IR(25714, 10)/* AutoINTEL */,IR(0, 0),IR(177, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS
  {0,IR(0, 0),IR(25724, 5)/* WRAP */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {1,IR(0, 0),IR(25729, 4)/* SAT */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {2,IR(0, 0),IR(25733, 9)/* SAT_ZERO */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {3,IR(0, 0),IR(25742, 8)/* SAT_SYM */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {0,IR(0, 0),IR(25750, 25)/* PackedVectorFormat4x8Bit */,IR(155, 1),IR(1, 0),IR(141, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {0,IR(0, 0),IR(25803, 4)/* TRN */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {1,IR(0, 0),IR(25807, 9)/* TRN_ZERO */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {2,IR(0, 0),IR(25816, 4)/* RND */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {3,IR(0, 0),IR(25820, 9)/* RND_ZERO */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {4,IR(0, 0),IR(25829, 8)/* RND_INF */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {5,IR(0, 0),IR(25837, 12)/* RND_MIN_INF */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {6,IR(0, 0),IR(25849, 9)/* RND_CONV */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {7,IR(0, 0),IR(25858, 13)/* RND_CONV_ODD */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {0,IR(0, 0),IR(15574, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {1,IR(0, 0),IR(25871, 25)/* RobustnessPerComponentNV */,IR(0, 0),IR(192, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {2,IR(0, 0),IR(25896, 23)/* RobustnessPerElementNV */,IR(0, 0),IR(192, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {0,IR(0, 0),IR(16326, 8)/* NoneKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {1,IR(0, 0),IR(25919, 10)/* OpaqueKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {2,IR(0, 0),IR(25929, 12)/* NoOpaqueKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {4,IR(0, 0),IR(25941, 23)/* TerminateOnFirstHitKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {8,IR(0, 0),IR(25964, 24)/* SkipClosestHitShaderKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {16,IR(0, 0),IR(25988, 27)/* CullBackFacingTrianglesKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {32,IR(0, 0),IR(26015, 28)/* CullFrontFacingTrianglesKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {64,IR(0, 0),IR(26043, 14)/* CullOpaqueKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {128,IR(0, 0),IR(26057, 16)/* CullNoOpaqueKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {256,IR(0, 0),IR(26073, 17)/* SkipTrianglesKHR */,IR(156, 1),IR(193, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {512,IR(0, 0),IR(26114, 13)/* SkipAABBsKHR */,IR(0, 0),IR(193, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {1024,IR(0, 0),IR(26127, 30)/* ForceOpacityMicromap2StateEXT */,IR(0, 0),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {0,IR(0, 0),IR(26157, 41)/* RayQueryCandidateIntersectionTriangleKHR */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {1,IR(0, 0),IR(26198, 37)/* RayQueryCandidateIntersectionAABBKHR */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {0,IR(0, 0),IR(26235, 37)/* RayQueryCommittedIntersectionNoneKHR */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {1,IR(0, 0),IR(26272, 41)/* RayQueryCommittedIntersectionTriangleKHR */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {2,IR(0, 0),IR(26313, 42)/* RayQueryCommittedIntersectionGeneratedKHR */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {0,IR(0, 0),IR(26355, 33)/* RayQueryCandidateIntersectionKHR */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {1,IR(0, 0),IR(26388, 33)/* RayQueryCommittedIntersectionKHR */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {0,IR(0, 0),IR(15574, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {1,IR(0, 0),IR(26421, 12)/* ClampToEdge */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {2,IR(0, 0),IR(26433, 6)/* Clamp */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {3,IR(0, 0),IR(26439, 7)/* Repeat */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {4,IR(0, 0),IR(26446, 15)/* RepeatMirrored */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {0,IR(0, 0),IR(26461, 8)/* Nearest */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {1,IR(0, 0),IR(26469, 7)/* Linear */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {0,IR(0, 0),IR(26476, 8)/* Unknown */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {1,IR(0, 0),IR(26484, 8)/* Rgba32f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {2,IR(0, 0),IR(26492, 8)/* Rgba16f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {3,IR(0, 0),IR(26500, 5)/* R32f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {4,IR(0, 0),IR(26505, 6)/* Rgba8 */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {5,IR(0, 0),IR(26511, 11)/* Rgba8Snorm */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {6,IR(0, 0),IR(26522, 6)/* Rg32f */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {7,IR(0, 0),IR(26528, 6)/* Rg16f */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {8,IR(0, 0),IR(26534, 13)/* R11fG11fB10f */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {9,IR(0, 0),IR(26547, 5)/* R16f */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {10,IR(0, 0),IR(26552, 7)/* Rgba16 */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {11,IR(0, 0),IR(26559, 8)/* Rgb10A2 */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {12,IR(0, 0),IR(26567, 5)/* Rg16 */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {13,IR(0, 0),IR(26572, 4)/* Rg8 */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {14,IR(0, 0),IR(26576, 4)/* R16 */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {15,IR(0, 0),IR(26580, 3)/* R8 */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {16,IR(0, 0),IR(26583, 12)/* Rgba16Snorm */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {17,IR(0, 0),IR(26595, 10)/* Rg16Snorm */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {18,IR(0, 0),IR(26605, 9)/* Rg8Snorm */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {19,IR(0, 0),IR(26614, 9)/* R16Snorm */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {20,IR(0, 0),IR(26623, 8)/* R8Snorm */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {21,IR(0, 0),IR(26631, 8)/* Rgba32i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {22,IR(0, 0),IR(26639, 8)/* Rgba16i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {23,IR(0, 0),IR(26647, 7)/* Rgba8i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {24,IR(0, 0),IR(26654, 5)/* R32i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {25,IR(0, 0),IR(26659, 6)/* Rg32i */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {26,IR(0, 0),IR(26665, 6)/* Rg16i */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {27,IR(0, 0),IR(26671, 5)/* Rg8i */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {28,IR(0, 0),IR(26676, 5)/* R16i */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {29,IR(0, 0),IR(26681, 4)/* R8i */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {30,IR(0, 0),IR(26685, 9)/* Rgba32ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {31,IR(0, 0),IR(26694, 9)/* Rgba16ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {32,IR(0, 0),IR(26703, 8)/* Rgba8ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {33,IR(0, 0),IR(26711, 6)/* R32ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {34,IR(0, 0),IR(26717, 10)/* Rgb10a2ui */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {35,IR(0, 0),IR(26727, 7)/* Rg32ui */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {36,IR(0, 0),IR(26734, 7)/* Rg16ui */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {37,IR(0, 0),IR(26741, 6)/* Rg8ui */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {38,IR(0, 0),IR(26747, 6)/* R16ui */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {39,IR(0, 0),IR(26753, 5)/* R8ui */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {40,IR(0, 0),IR(26758, 6)/* R64ui */,IR(0, 0),IR(197, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {41,IR(0, 0),IR(26764, 5)/* R64i */,IR(0, 0),IR(197, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {0,IR(0, 0),IR(26769, 12)/* CrossDevice */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {1,IR(0, 0),IR(26781, 7)/* Device */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {2,IR(0, 0),IR(26788, 10)/* Workgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {3,IR(0, 0),IR(26798, 9)/* Subgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {4,IR(0, 0),IR(26807, 11)/* Invocation */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {5,IR(0, 0),IR(26818, 12)/* QueueFamily */,IR(157, 1),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {6,IR(0, 0),IR(26845, 14)/* ShaderCallKHR */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {0,IR(0, 0),IR(15574, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {1,IR(0, 0),IR(26859, 8)/* Flatten */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {2,IR(0, 0),IR(26867, 12)/* DontFlatten */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {1,IR(0, 0),IR(26879, 29)/* IdentifierPossibleDuplicates */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS
  {0,IR(0, 0),IR(15443, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(15455, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(15463, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {3,IR(0, 0),IR(15471, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(15477, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(15484, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(15495, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(15504, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(15517, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(15523, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(15533, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(15539, 15)/* ImportedModule */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {1,IR(0, 0),IR(15554, 20)/* ImportedDeclaration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {0,IR(0, 0),IR(15574, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(15579, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(15595, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(15609, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(15622, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(15634, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(15651, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(15663, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(15678, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(15691, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(15706, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(15724, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(15741, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(15762, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(15782, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(15802, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {16384,IR(0, 0),IR(15818, 16)/* FlagIsEnumClass */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {32768,IR(0, 0),IR(15834, 20)/* FlagTypePassByValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {65536,IR(0, 0),IR(15854, 24)/* FlagTypePassByReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {131072,IR(0, 0),IR(26908, 26)/* FlagUnknownPhysicalLayout */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(15878, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {1,IR(0, 0),IR(15884, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {2,IR(0, 0),IR(15889, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {3,IR(10, 1),IR(15928, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {4,IR(36, 2),IR(15939, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {5,IR(0, 0),IR(15948, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {6,IR(0, 0),IR(15953, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {7,IR(0, 0),IR(15960, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {8,IR(10, 1),IR(15971, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {9,IR(36, 2),IR(15978, 9)/* Fragment */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {0,IR(0, 0),IR(15987, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(15997, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(16010, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {3,IR(0, 0),IR(16023, 11)/* AtomicType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(26476, 8)/* Unknown */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {1,IR(0, 0),IR(26934, 5)/* ESSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {2,IR(0, 0),IR(26939, 5)/* GLSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {3,IR(0, 0),IR(26944, 9)/* OpenCL_C */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {4,IR(0, 0),IR(26953, 11)/* OpenCL_CPP */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {5,IR(0, 0),IR(26964, 5)/* HLSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {6,IR(0, 0),IR(26969, 15)/* CPP_for_OpenCL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {7,IR(0, 0),IR(26984, 5)/* SYCL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {8,IR(0, 0),IR(26989, 7)/* HERO_C */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {9,IR(0, 0),IR(26996, 5)/* NZSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {10,IR(0, 0),IR(27001, 5)/* WGSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {11,IR(0, 0),IR(27006, 6)/* Slang */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {12,IR(0, 0),IR(27012, 4)/* Zig */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {13,IR(0, 0),IR(27016, 5)/* Rust */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {0,IR(0, 0),IR(27021, 16)/* UniformConstant */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {1,IR(0, 0),IR(27037, 6)/* Input */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {2,IR(0, 0),IR(16863, 8)/* Uniform */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {3,IR(0, 0),IR(27043, 7)/* Output */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4,IR(0, 0),IR(26788, 10)/* Workgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5,IR(0, 0),IR(27050, 15)/* CrossWorkgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {6,IR(0, 0),IR(27065, 8)/* Private */,IR(0, 0),IR(198, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {7,IR(0, 0),IR(27073, 9)/* Function */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {8,IR(0, 0),IR(27082, 8)/* Generic */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {9,IR(0, 0),IR(27090, 13)/* PushConstant */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {10,IR(0, 0),IR(27103, 14)/* AtomicCounter */,IR(0, 0),IR(82, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {11,IR(0, 0),IR(27117, 6)/* Image */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {12,IR(0, 0),IR(27123, 14)/* StorageBuffer */,IR(0, 0),IR(3, 1),IR(189, 2),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4172,IR(0, 0),IR(27137, 13)/* TileImageEXT */,IR(0, 0),IR(149, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4491,IR(0, 0),IR(27150, 19)/* TileAttachmentQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5068,IR(0, 0),IR(27169, 16)/* NodePayloadAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5328,IR(0, 0),IR(27185, 16)/* CallableDataKHR */,IR(158, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5329,IR(0, 0),IR(27216, 24)/* IncomingCallableDataKHR */,IR(159, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5338,IR(0, 0),IR(27263, 14)/* RayPayloadKHR */,IR(160, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5339,IR(0, 0),IR(27290, 16)/* HitAttributeKHR */,IR(161, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5342,IR(0, 0),IR(27321, 22)/* IncomingRayPayloadKHR */,IR(162, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5343,IR(0, 0),IR(27364, 22)/* ShaderRecordBufferKHR */,IR(163, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5349,IR(0, 0),IR(27407, 22)/* PhysicalStorageBuffer */,IR(164, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5385,IR(0, 0),IR(27454, 21)/* HitObjectAttributeNV */,IR(0, 0),IR(127, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5402,IR(0, 0),IR(27475, 24)/* TaskPayloadWorkgroupEXT */,IR(0, 0),IR(53, 1),IR(23, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5411,IR(0, 0),IR(27499, 22)/* HitObjectAttributeEXT */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5605,IR(0, 0),IR(27521, 17)/* CodeSectionINTEL */,IR(0, 0),IR(201, 1),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5936,IR(0, 0),IR(27538, 17)/* DeviceOnlyALTERA */,IR(165, 1),IR(202, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5937,IR(0, 0),IR(27571, 15)/* HostOnlyALTERA */,IR(166, 1),IR(202, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {0,IR(0, 0),IR(24426, 14)/* UncachedINTEL */,IR(0, 0),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {1,IR(0, 0),IR(27600, 18)/* WriteThroughINTEL */,IR(0, 0),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {2,IR(0, 0),IR(27618, 15)/* WriteBackINTEL */,IR(0, 0),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {3,IR(0, 0),IR(24452, 15)/* StreamingINTEL */,IR(0, 0),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {0,IR(0, 0),IR(15574, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {1,IR(10, 1),IR(27633, 11)/* TensorView */,IR(0, 0),IR(203, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {2,IR(10, 1),IR(27644, 11)/* DecodeFunc */,IR(0, 0),IR(204, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {0,IR(0, 0),IR(27655, 10)/* Undefined */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {1,IR(0, 0),IR(16821, 9)/* Constant */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {2,IR(0, 0),IR(26421, 12)/* ClampToEdge */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {3,IR(0, 0),IR(26439, 7)/* Repeat */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {4,IR(0, 0),IR(26446, 15)/* RepeatMirrored */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {0,IR(0, 0),IR(27665, 8)/* NoneARM */,IR(0, 0),IR(205, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {1,IR(0, 0),IR(27673, 15)/* NontemporalARM */,IR(0, 0),IR(205, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {2,IR(10, 1),IR(27688, 20)/* OutOfBoundsValueARM */,IR(0, 0),IR(205, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {4,IR(10, 1),IR(27708, 24)/* MakeElementAvailableARM */,IR(0, 0),IR(205, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {8,IR(10, 1),IR(27732, 22)/* MakeElementVisibleARM */,IR(0, 0),IR(205, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {16,IR(0, 0),IR(27754, 21)/* NonPrivateElementARM */,IR(0, 0),IR(205, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
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
    case SPV_OPERAND_TYPE_CAPABILITY: return IR(133, 278);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(411, 8);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(419, 3);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(422, 2);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS: return IR(424, 19);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION: return IR(443, 10);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(453, 4);
    case SPV_OPERAND_TYPE_COMPONENT_TYPE: return IR(457, 15);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT: return IR(472, 4);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS: return IR(476, 6);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE: return IR(482, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE: return IR(485, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT: return IR(488, 4);
    case SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(492, 8);
    case SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE: return IR(500, 3);
    case SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS: return IR(503, 16);
    case SPV_OPERAND_TYPE_DEBUG_OPERATION: return IR(519, 9);
    case SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER: return IR(528, 3);
    case SPV_OPERAND_TYPE_DECORATION: return IR(531, 145);
    case SPV_OPERAND_TYPE_DIMENSIONALITY: return IR(676, 8);
    case SPV_OPERAND_TYPE_EXECUTION_MODE: return IR(684, 97);
    case SPV_OPERAND_TYPE_EXECUTION_MODEL: return IR(781, 17);
    case SPV_OPERAND_TYPE_FPDENORM_MODE: return IR(798, 2);
    case SPV_OPERAND_TYPE_FPENCODING: return IR(800, 3);
    case SPV_OPERAND_TYPE_FPOPERATION_MODE: return IR(803, 2);
    case SPV_OPERAND_TYPE_FP_FAST_MATH_MODE: return IR(805, 9);
    case SPV_OPERAND_TYPE_FP_ROUNDING_MODE: return IR(814, 4);
    case SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE: return IR(818, 4);
    case SPV_OPERAND_TYPE_FUNCTION_CONTROL: return IR(822, 6);
    case SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE: return IR(828, 9);
    case SPV_OPERAND_TYPE_GROUP_OPERATION: return IR(837, 7);
    case SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER: return IR(844, 4);
    case SPV_OPERAND_TYPE_IMAGE: return IR(848, 17);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE: return IR(865, 26);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER: return IR(891, 20);
    case SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER: return IR(911, 2);
    case SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS: return IR(913, 3);
    case SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO: return IR(916, 2);
    case SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS: return IR(918, 2);
    case SPV_OPERAND_TYPE_LINKAGE_TYPE: return IR(920, 3);
    case SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL: return IR(923, 5);
    case SPV_OPERAND_TYPE_LOOP_CONTROL: return IR(928, 20);
    case SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(948, 15);
    case SPV_OPERAND_TYPE_MEMORY_ACCESS: return IR(963, 9);
    case SPV_OPERAND_TYPE_MEMORY_MODEL: return IR(972, 4);
    case SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID: return IR(976, 15);
    case SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS: return IR(991, 1);
    case SPV_OPERAND_TYPE_OVERFLOW_MODES: return IR(992, 4);
    case SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT: return IR(996, 1);
    case SPV_OPERAND_TYPE_QUANTIZATION_MODES: return IR(997, 8);
    case SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS: return IR(1005, 3);
    case SPV_OPERAND_TYPE_RAY_FLAGS: return IR(1008, 12);
    case SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE: return IR(1020, 2);
    case SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE: return IR(1022, 3);
    case SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION: return IR(1025, 2);
    case SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE: return IR(1027, 5);
    case SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE: return IR(1032, 2);
    case SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT: return IR(1034, 42);
    case SPV_OPERAND_TYPE_SCOPE_ID: return IR(1076, 7);
    case SPV_OPERAND_TYPE_SELECTION_CONTROL: return IR(1083, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS: return IR(1086, 1);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(1087, 8);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(1095, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(1098, 2);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS: return IR(1100, 20);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION: return IR(1120, 10);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(1130, 4);
    case SPV_OPERAND_TYPE_SOURCE_LANGUAGE: return IR(1134, 14);
    case SPV_OPERAND_TYPE_STORAGE_CLASS: return IR(1148, 29);
    case SPV_OPERAND_TYPE_STORE_CACHE_CONTROL: return IR(1177, 4);
    case SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS: return IR(1181, 3);
    case SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE: return IR(1184, 5);
    case SPV_OPERAND_TYPE_TENSOR_OPERANDS: return IR(1189, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_IMAGE: return IR(848, 17);
    case SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS: return IR(963, 9);
    case SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT: return IR(996, 1);
    case SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS: return IR(476, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(948, 15);
    case SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS: return IR(1005, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_FPENCODING: return IR(800, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS: return IR(1189, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_CAPABILITY: return IR(133, 278);
    default: break;
  }
  return IR(0,0);
}

// Operand names and index into kOperandsByValue, ordered by (operand kind, name)
// The fields in order are:
//   name, either the primary name or an alias, indexing into kStrings
//   index into the kOperandsByValue array
static const std::array<NameIndex, 1366> kOperandNames{{
  {IR(5368, 9), 0}, // 0 ReadOnly in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(5394, 10), 2}, // 1 ReadWrite in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(5384, 10), 1}, // 2 WriteOnly in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(5404, 8), 3}, // 3 Logical in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5412, 11), 4}, // 4 Physical32 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5433, 11), 5}, // 5 Physical64 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5444, 24), 6}, // 6 PhysicalStorageBuffer64 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5468, 27), 6}, // 7 PhysicalStorageBuffer64EXT in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(7378, 13), 92}, // 8 BaryCoordKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7391, 12), 92}, // 9 BaryCoordNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6773, 20), 68}, // 10 BaryCoordNoPerspAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6793, 28), 69}, // 11 BaryCoordNoPerspCentroidAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7426, 20), 93}, // 12 BaryCoordNoPerspKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7446, 19), 93}, // 13 BaryCoordNoPerspNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6821, 26), 70}, // 14 BaryCoordNoPerspSampleAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6918, 22), 74}, // 15 BaryCoordPullModelAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6847, 19), 71}, // 16 BaryCoordSmoothAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6866, 27), 72}, // 17 BaryCoordSmoothCentroidAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6893, 25), 73}, // 18 BaryCoordSmoothSampleAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6577, 13), 59}, // 19 BaseInstance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6551, 11), 58}, // 20 BaseVertex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5552, 13), 9}, // 21 ClipDistance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7285, 22), 87}, // 22 ClipDistancePerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8584, 12), 131}, // 23 ClusterIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6315, 13), 49}, // 24 CoreCountARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6289, 10), 48}, // 25 CoreIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6328, 13), 50}, // 26 CoreMaxIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5565, 13), 10}, // 27 CullDistance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7307, 22), 88}, // 28 CullDistancePerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8637, 12), 132}, // 29 CullMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7633, 17), 99}, // 30 CullPrimitiveEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8037, 17), 113}, // 31 CurrentRayTimeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6647, 12), 62}, // 32 DeviceIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6590, 10), 60}, // 33 DrawIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6079, 22), 37}, // 34 EnqueuedWorkgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5849, 10), 21}, // 35 FragCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5935, 10), 27}, // 36 FragDepth in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7511, 23), 95}, // 37 FragInvocationCountEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7465, 12), 94}, // 38 FragSizeEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6940, 18), 75}, // 39 FragStencilRefEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7477, 15), 94}, // 40 FragmentSizeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5870, 12), 23}, // 41 FrontFacing in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7197, 16), 83}, // 42 FullyCoveredEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6020, 19), 33}, // 43 GlobalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6114, 15), 39}, // 44 GlobalLinearId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6101, 13), 38}, // 45 GlobalOffset in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6068, 11), 36}, // 46 GlobalSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5945, 17), 28}, // 47 HelperInvocation in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8339, 11), 120}, // 48 HitIsLSSNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8297, 14), 119}, // 49 HitIsSphereNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8519, 33), 128}, // 50 HitKindBackFacingMicroTriangleNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8485, 34), 127}, // 51 HitKindFrontFacingMicroTriangleNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8016, 11), 112}, // 52 HitKindKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8027, 10), 112}, // 53 HitKindNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8467, 18), 126}, // 54 HitLSSPositionsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8570, 14), 130}, // 55 HitLSSRadiiNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8201, 37), 116}, // 56 HitMicroTriangleVertexBarycentricsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8134, 34), 115}, // 57 HitMicroTriangleVertexPositionsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8389, 20), 121}, // 58 HitSpherePositionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8552, 18), 129}, // 59 HitSphereRadiusNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8009, 7), 111}, // 60 HitTNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8077, 30), 114}, // 61 HitTriangleVertexPositionsKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8238, 20), 117}, // 62 IncomingRayFlagsKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8258, 19), 117}, // 63 IncomingRayFlagsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7898, 23), 108}, // 64 InstanceCustomIndexKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7921, 22), 108}, // 65 InstanceCustomIndexNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5587, 11), 12}, // 66 InstanceId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6275, 14), 47}, // 67 InstanceIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5688, 13), 14}, // 68 InvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7534, 22), 95}, // 69 InvocationsPerPixelNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7650, 12), 100}, // 70 LaunchIdKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7662, 11), 100}, // 71 LaunchIdNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7673, 14), 101}, // 72 LaunchSizeKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7687, 13), 101}, // 73 LaunchSizeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5701, 6), 15}, // 74 Layer in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7329, 15), 89}, // 75 LayerPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6002, 18), 32}, // 76 LocalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6039, 21), 34}, // 77 LocalInvocationIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7344, 16), 90}, // 78 MeshViewCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7360, 18), 91}, // 79 MeshViewIndicesNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6205, 21), 43}, // 80 NumEnqueuedSubgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6192, 13), 42}, // 81 NumSubgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5962, 14), 29}, // 82 NumWorkgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7813, 22), 105}, // 83 ObjectRayDirectionKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7835, 21), 105}, // 84 ObjectRayDirectionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7776, 19), 104}, // 85 ObjectRayOriginKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7795, 18), 104}, // 86 ObjectRayOriginNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7943, 17), 109}, // 87 ObjectToWorldKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7960, 16), 109}, // 88 ObjectToWorldNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5835, 14), 20}, // 89 PatchVertices in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5859, 11), 22}, // 90 PointCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5542, 10), 8}, // 91 PointSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5526, 9), 7}, // 92 Position in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7137, 18), 81}, // 93 PositionPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7249, 17), 85}, // 94 PrimitiveCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5598, 12), 13}, // 95 PrimitiveId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7266, 19), 86}, // 96 PrimitiveIndicesNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7581, 24), 97}, // 97 PrimitiveLineIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7556, 25), 96}, // 98 PrimitivePointIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6600, 24), 61}, // 99 PrimitiveShadingRateKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7605, 28), 98}, // 100 PrimitiveTriangleIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8277, 20), 118}, // 101 RayGeometryIndexKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7877, 11), 107}, // 102 RayTmaxKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7888, 10), 107}, // 103 RayTmaxNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7856, 11), 106}, // 104 RayTminKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7867, 10), 106}, // 105 RayTminNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6975, 29), 76}, // 106 RemainingRecursionLevelsAMDX in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8441, 10), 123}, // 107 SMCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8460, 7), 125}, // 108 SMIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5882, 9), 24}, // 109 SampleId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5924, 11), 26}, // 110 SampleMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5909, 15), 25}, // 111 SamplePosition in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7074, 20), 79}, // 112 SecondaryPositionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7113, 24), 80}, // 113 SecondaryViewportMaskNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7022, 16), 77}, // 114 ShaderIndexAMDX in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6691, 15), 64}, // 115 ShadingRateKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6364, 15), 53}, // 116 SubgroupEqMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6379, 18), 53}, // 117 SubgroupEqMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6419, 15), 54}, // 118 SubgroupGeMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6434, 18), 54}, // 119 SubgroupGeMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6452, 15), 55}, // 120 SubgroupGtMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6467, 18), 55}, // 121 SubgroupGtMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6226, 11), 44}, // 122 SubgroupId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6485, 15), 56}, // 123 SubgroupLeMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6500, 18), 56}, // 124 SubgroupLeMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6237, 26), 45}, // 125 SubgroupLocalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6518, 15), 57}, // 126 SubgroupLtMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6533, 18), 57}, // 127 SubgroupLtMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6176, 16), 41}, // 128 SubgroupMaxSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6129, 13), 40}, // 129 SubgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7237, 12), 84}, // 130 TaskCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5825, 10), 19}, // 131 TessCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5810, 15), 18}, // 132 TessLevelInner in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5795, 15), 17}, // 133 TessLevelOuter in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6755, 18), 67}, // 134 TileApronSizeQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6737, 18), 66}, // 135 TileDimensionQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6706, 15), 65}, // 136 TileOffsetQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5578, 9), 11}, // 137 VertexId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6263, 12), 46}, // 138 VertexIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6671, 10), 63}, // 139 ViewIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5747, 14), 16}, // 140 ViewportIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7038, 15), 78}, // 141 ViewportMaskNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7175, 22), 82}, // 142 ViewportMaskPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6341, 10), 51}, // 143 WarpIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8451, 9), 124}, // 144 WarpIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6351, 13), 52}, // 145 WarpMaxIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8409, 13), 122}, // 146 WarpsPerSMNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6060, 8), 35}, // 147 WorkDim in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5990, 12), 31}, // 148 WorkgroupId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5976, 14), 30}, // 149 WorkgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7735, 21), 103}, // 150 WorldRayDirectionKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7756, 20), 103}, // 151 WorldRayDirectionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7700, 18), 102}, // 152 WorldRayOriginKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7718, 17), 102}, // 153 WorldRayOriginNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7976, 17), 110}, // 154 WorldToObjectKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7993, 16), 110}, // 155 WorldToObjectNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5423, 10), 137}, // 156 Addresses in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13994, 35), 362}, // 157 ArbitraryPrecisionFixedPointALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14029, 34), 362}, // 158 ArbitraryPrecisionFixedPointINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13466, 38), 350}, // 159 ArbitraryPrecisionFloatingPointALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13504, 37), 350}, // 160 ArbitraryPrecisionFloatingPointINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13401, 33), 349}, // 161 ArbitraryPrecisionIntegersALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13434, 32), 349}, // 162 ArbitraryPrecisionIntegersINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14688, 19), 387}, // 163 ArithmeticFenceEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13039, 9), 335}, // 164 AsmINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14605, 20), 383}, // 165 AtomicFloat16AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13094, 23), 338}, // 166 AtomicFloat16MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12530, 22), 311}, // 167 AtomicFloat16VectorNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14521, 20), 379}, // 168 AtomicFloat32AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13048, 23), 336}, // 169 AtomicFloat32MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14541, 20), 380}, // 170 AtomicFloat64AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13071, 23), 337}, // 171 AtomicFloat64MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8817, 14), 153}, // 172 AtomicStorage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10204, 17), 229}, // 173 AtomicStorageOps in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14646, 24), 385}, // 174 BFloat16ConversionINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10826, 29), 263}, // 175 BFloat16CooperativeMatrixKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10804, 22), 262}, // 176 BFloat16DotProductKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10788, 16), 261}, // 177 BFloat16TypeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15423, 20), 410}, // 178 BindlessImagesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12467, 18), 308}, // 179 BindlessTextureNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14458, 16), 375}, // 180 BitInstructions in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14196, 20), 366}, // 181 BlockingPipesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14216, 19), 366}, // 182 BlockingPipesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15384, 19), 408}, // 183 CacheControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5552, 13), 163}, // 184 ClipDistance in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12098, 32), 296}, // 185 ComputeDerivativeGroupLinearKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12130, 31), 296}, // 186 ComputeDerivativeGroupLinearNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10978, 31), 275}, // 187 ComputeDerivativeGroupQuadsKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11009, 30), 275}, // 188 ComputeDerivativeGroupQuadsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12744, 30), 322}, // 189 CooperativeMatrixBlockLoadsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10573, 32), 248}, // 190 CooperativeMatrixConversionQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12637, 31), 319}, // 191 CooperativeMatrixConversionsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9852, 21), 373}, // 192 CooperativeMatrixKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9787, 28), 211}, // 193 CooperativeMatrixLayoutsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12186, 20), 298}, // 194 CooperativeMatrixNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12668, 40), 320}, // 195 CooperativeMatrixPerElementOperationsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12607, 30), 318}, // 196 CooperativeMatrixReductionsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12708, 36), 321}, // 197 CooperativeMatrixTensorAddressingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12510, 20), 310}, // 198 CooperativeVectorNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12774, 28), 323}, // 199 CooperativeVectorTrainingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6299, 16), 203}, // 200 CoreBuiltinsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5565, 13), 164}, // 201 CullDistance in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14625, 21), 384}, // 202 DebugInfoModuleINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12309, 25), 303}, // 203 DemoteToHelperInvocation in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12334, 28), 303}, // 204 DemoteToHelperInvocationEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10343, 18), 235}, // 205 DenormFlushToZero in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10328, 15), 234}, // 206 DenormPreserve in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9264, 18), 182}, // 207 DerivativeControl in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8788, 14), 151}, // 208 DeviceEnqueue in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6659, 12), 225}, // 209 DeviceGroup in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12362, 23), 304}, // 210 DisplacementMicromapNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14409, 11), 371}, // 211 DotProduct in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14303, 22), 369}, // 212 DotProductInput4x8Bit in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14325, 25), 369}, // 213 DotProductInput4x8BitKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14350, 28), 370}, // 214 DotProductInput4x8BitPacked in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14378, 31), 370}, // 215 DotProductInput4x8BitPackedKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14262, 19), 368}, // 216 DotProductInputAll in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14281, 22), 368}, // 217 DotProductInputAllKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14420, 14), 371}, // 218 DotProductKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6562, 15), 216}, // 219 DrawParameters in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13151, 16), 341}, // 220 ExpectAssumeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14514, 7), 378}, // 221 FMAKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13381, 20), 348}, // 222 FPFastMathModeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14896, 29), 393}, // 223 FPGAArgumentInterfacesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14925, 28), 393}, // 224 FPGAArgumentInterfacesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13945, 25), 361}, // 225 FPGABufferLocationALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13970, 24), 361}, // 226 FPGABufferLocationINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13713, 28), 356}, // 227 FPGAClusterAttributesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13741, 27), 356}, // 228 FPGAClusterAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14707, 30), 388}, // 229 FPGAClusterAttributesV2ALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14737, 29), 388}, // 230 FPGAClusterAttributesV2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13797, 21), 358}, // 231 FPGADSPControlALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13818, 20), 358}, // 232 FPGADSPControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13864, 41), 360}, // 233 FPGAInvocationPipeliningAttributesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13905, 40), 360}, // 234 FPGAInvocationPipeliningAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13638, 26), 354}, // 235 FPGAKernelAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14766, 28), 389}, // 236 FPGAKernelAttributesv2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14847, 25), 392}, // 237 FPGALatencyControlALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14872, 24), 392}, // 238 FPGALatencyControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13571, 23), 352}, // 239 FPGALoopControlsALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13594, 22), 352}, // 240 FPGALoopControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13664, 25), 355}, // 241 FPGAMemoryAccessesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13689, 24), 355}, // 242 FPGAMemoryAccessesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13328, 27), 347}, // 243 FPGAMemoryAttributesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13355, 26), 347}, // 244 FPGAMemoryAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14235, 14), 367}, // 245 FPGARegALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14249, 13), 367}, // 246 FPGARegINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14831, 16), 391}, // 247 FPMaxErrorINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8702, 8), 142}, // 248 Float16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8688, 14), 141}, // 249 Float16Buffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10628, 16), 250}, // 250 Float16ImageAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8710, 8), 143}, // 251 Float64 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9825, 27), 213}, // 252 Float8CooperativeMatrixEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9815, 10), 212}, // 253 Float8EXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14499, 15), 377}, // 254 FloatControls2 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12947, 23), 331}, // 255 FloatingPointModeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7403, 23), 274}, // 256 FragmentBarycentricKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10956, 22), 274}, // 257 FragmentBarycentricNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7492, 19), 276}, // 258 FragmentDensityEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7213, 24), 270}, // 259 FragmentFullyCoveredEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10666, 16), 252}, // 260 FragmentMaskAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12277, 32), 302}, // 261 FragmentShaderPixelInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12206, 33), 299}, // 262 FragmentShaderSampleInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12239, 38), 300}, // 263 FragmentShaderShadingRateInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6624, 23), 214}, // 264 FragmentShadingRateKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13302, 26), 346}, // 265 FunctionFloatControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12993, 22), 333}, // 266 FunctionPointersINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15284, 22), 404}, // 267 FunctionVariantsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9109, 15), 169}, // 268 GenericPointer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5610, 9), 135}, // 269 Geometry in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8859, 18), 156}, // 270 GeometryPointSize in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10884, 28), 265}, // 271 GeometryShaderPassthroughNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9322, 16), 185}, // 272 GeometryStreams in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14983, 36), 395}, // 273 GlobalVariableFPGADecorationsALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15019, 35), 395}, // 274 GlobalVariableFPGADecorationsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14953, 30), 394}, // 275 GlobalVariableHostAccessINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9778, 9), 210}, // 276 GraphARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6142, 16), 192}, // 277 GroupNonUniform in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9461, 26), 194}, // 278 GroupNonUniformArithmetic in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6397, 22), 195}, // 279 GroupNonUniformBallot in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9541, 25), 198}, // 280 GroupNonUniformClustered in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11053, 29), 277}, // 281 GroupNonUniformPartitionedNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9566, 20), 199}, // 282 GroupNonUniformQuad in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14474, 25), 376}, // 283 GroupNonUniformRotateKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9487, 23), 196}, // 284 GroupNonUniformShuffle in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9510, 31), 197}, // 285 GroupNonUniformShuffleRelative in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9441, 20), 193}, // 286 GroupNonUniformVote in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15306, 26), 405}, // 287 GroupUniformArithmeticKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8781, 7), 150}, // 288 Groups in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14169, 14), 365}, // 289 IOPipesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14183, 13), 365}, // 290 IOPipesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9178, 8), 175}, // 291 Image1D in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8737, 11), 146}, // 292 ImageBasic in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9200, 12), 178}, // 293 ImageBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9055, 15), 165}, // 294 ImageCubeArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10939, 17), 272}, // 295 ImageFootprintNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10644, 22), 251}, // 296 ImageGatherBiasLodAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8877, 20), 157}, // 297 ImageGatherExtended in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9212, 13), 179}, // 298 ImageMSArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8763, 12), 148}, // 299 ImageMipmap in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9253, 11), 181}, // 300 ImageQuery in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8748, 15), 147}, // 301 ImageReadWrite in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10682, 21), 254}, // 302 ImageReadWriteLodAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9087, 10), 167}, // 303 ImageRect in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13015, 24), 334}, // 304 IndirectReferencesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9129, 16), 171}, // 305 InputAttachment in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11168, 36), 280}, // 306 InputAttachmentArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11204, 39), 280}, // 307 InputAttachmentArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11709, 39), 287}, // 308 InputAttachmentArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11748, 42), 287}, // 309 InputAttachmentArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8831, 6), 154}, // 310 Int16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10761, 27), 260}, // 311 Int4CooperativeMatrixINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10747, 14), 259}, // 312 Int4TypeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8718, 6), 144}, // 313 Int64 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8724, 13), 145}, // 314 Int64Atomics in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10703, 14), 255}, // 315 Int64ImageEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9124, 5), 170}, // 316 Int8 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12970, 23), 332}, // 317 IntegerFunctions2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9282, 22), 183}, // 318 InterpolationFunction in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5377, 7), 139}, // 319 Kernel in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13616, 22), 353}, // 320 KernelAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8671, 8), 138}, // 321 Linkage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8802, 15), 152}, // 322 LiteralSampler in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14561, 20), 381}, // 323 LongCompositesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12570, 14), 316}, // 324 LongVectorEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13768, 15), 357}, // 325 LoopFuseALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13783, 14), 357}, // 326 LoopFuseINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15359, 25), 407}, // 327 MaskedGatherScatterINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8664, 7), 133}, // 328 Matrix in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13838, 26), 359}, // 329 MemoryAccessAliasingINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5673, 15), 273}, // 330 MeshShadingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5659, 14), 271}, // 331 MeshShadingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9161, 7), 173}, // 332 MinLod in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6681, 10), 226}, // 333 MultiView in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5761, 14), 188}, // 334 MultiViewport in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9416, 13), 190}, // 335 NamedBarrier in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14581, 11), 382}, // 336 OptNoneEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14592, 13), 382}, // 337 OptNoneINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7155, 20), 269}, // 338 PerViewAttributesNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5495, 31), 295}, // 339 PhysicalStorageBufferAddresses in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12064, 34), 295}, // 340 PhysicalStorageBufferAddressesEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9429, 12), 191}, // 341 PipeStorage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8775, 6), 149}, // 342 Pipes in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10732, 15), 258}, // 343 QuadControlKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12552, 18), 313}, // 344 RawAccessChainsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8649, 15), 372}, // 345 RayCullMaskKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10441, 12), 240}, // 346 RayQueryKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12485, 25), 309}, // 347 RayQueryPositionFetchKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10418, 23), 239}, // 348 RayQueryProvisionalKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8596, 41), 324}, // 349 RayTracingClusterAccelerationStructureNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8168, 33), 312}, // 350 RayTracingDisplacementMicromapNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5645, 14), 243}, // 351 RayTracingKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8350, 39), 315}, // 352 RayTracingLinearSweptSpheresGeometryNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8054, 23), 292}, // 353 RayTracingMotionBlurNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5632, 13), 291}, // 354 RayTracingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12385, 29), 305}, // 355 RayTracingOpacityMicromapEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8107, 27), 290}, // 356 RayTracingPositionFetchKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12161, 25), 297}, // 357 RayTracingProvisionalKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8311, 28), 314}, // 358 RayTracingSpheresGeometryNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10472, 32), 242}, // 359 RayTraversalPrimitiveCullingKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15403, 20), 409}, // 360 RegisterLimitsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14434, 24), 374}, // 361 ReplicatedCompositesEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12926, 21), 330}, // 362 RoundToInfinityINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10386, 16), 237}, // 363 RoundingModeRTE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10402, 16), 238}, // 364 RoundingModeRTZ in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14110, 30), 364}, // 365 RuntimeAlignedAttributeALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14140, 29), 364}, // 366 RuntimeAlignedAttributeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11119, 23), 279}, // 367 RuntimeDescriptorArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11142, 26), 279}, // 368 RuntimeDescriptorArrayEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10855, 29), 264}, // 369 SampleMaskOverrideCoverageNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10221, 28), 230}, // 370 SampleMaskPostDepthCoverage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5891, 18), 166}, // 371 SampleRateShading in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9168, 10), 174}, // 372 Sampled1D in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9186, 14), 177}, // 373 SampledBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9070, 17), 176}, // 374 SampledCubeArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8955, 33), 160}, // 375 SampledImageArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11482, 36), 284}, // 376 SampledImageArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11518, 39), 284}, // 377 SampledImageArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9097, 12), 168}, // 378 SampledRect in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5535, 7), 134}, // 379 Shader in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12584, 23), 317}, // 380 Shader64BitIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10717, 15), 256}, // 381 ShaderClockKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7004, 18), 257}, // 382 ShaderEnqueueAMDX in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12440, 27), 307}, // 383 ShaderInvocationReorderEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12414, 26), 306}, // 384 ShaderInvocationReorderNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5707, 12), 200}, // 385 ShaderLayer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11082, 17), 278}, // 386 ShaderNonUniform in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11099, 20), 278}, // 387 ShaderNonUniformEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8422, 19), 301}, // 388 ShaderSMBuiltinsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7094, 19), 268}, // 389 ShaderStereoViewNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5775, 20), 201}, // 390 ShaderViewportIndex in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5719, 28), 266}, // 391 ShaderViewportIndexLayerEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10912, 27), 266}, // 392 ShaderViewportIndexLayerNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7053, 21), 267}, // 393 ShaderViewportMaskNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11039, 14), 276}, // 394 ShadingRateNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10361, 25), 236}, // 395 SignedZeroInfNanPreserve in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9145, 16), 172}, // 396 SparseResidency in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15263, 21), 403}, // 397 SpecConditionalINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14670, 18), 386}, // 398 SplitBarrierINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6958, 17), 253}, // 399 StencilExportEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10009, 25), 221}, // 400 StorageBuffer16BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10249, 24), 231}, // 401 StorageBuffer8BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8988, 34), 161}, // 402 StorageBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11557, 37), 285}, // 403 StorageBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11594, 40), 285}, // 404 StorageBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9022, 33), 162}, // 405 StorageImageArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11634, 36), 286}, // 406 StorageImageArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11670, 39), 286}, // 407 StorageImageArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9225, 28), 180}, // 408 StorageImageExtendedFormats in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8897, 24), 158}, // 409 StorageImageMultisample in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9338, 30), 186}, // 410 StorageImageReadWithoutFormat in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9368, 31), 187}, // 411 StorageImageWriteWithoutFormat in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10136, 21), 224}, // 412 StorageInputOutput16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10114, 22), 223}, // 413 StoragePushConstant16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10307, 21), 233}, // 414 StoragePushConstant8 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9701, 37), 208}, // 415 StorageTensorArrayDynamicIndexingARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9738, 40), 209}, // 416 StorageTensorArrayNonUniformIndexingARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11324, 39), 282}, // 417 StorageTexelBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11363, 42), 282}, // 418 StorageTexelBufferArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11877, 42), 289}, // 419 StorageTexelBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11919, 45), 289}, // 420 StorageTexelBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10097, 17), 222}, // 421 StorageUniform16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10034, 28), 221}, // 422 StorageUniformBufferBlock16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15082, 23), 397}, // 423 Subgroup2DBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15105, 30), 398}, // 424 Subgroup2DBlockTransformINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15135, 30), 399}, // 425 Subgroup2DBlockTransposeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13238, 39), 344}, // 426 SubgroupAvcMotionEstimationChromaINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13167, 33), 342}, // 427 SubgroupAvcMotionEstimationINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13200, 38), 343}, // 428 SubgroupAvcMotionEstimationIntraINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6158, 18), 215}, // 429 SubgroupBallotKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12842, 27), 327}, // 430 SubgroupBufferBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15054, 28), 396}, // 431 SubgroupBufferPrefetchINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9399, 17), 189}, // 432 SubgroupDispatch in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12869, 26), 328}, // 433 SubgroupImageBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12895, 31), 329}, // 434 SubgroupImageMediaBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15165, 38), 400}, // 435 SubgroupMatrixMultiplyAccumulateINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12821, 21), 326}, // 436 SubgroupShuffleINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9993, 16), 220}, // 437 SubgroupVoteKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14794, 19), 390}, // 438 TaskSequenceALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14813, 18), 390}, // 439 TaskSequenceINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12802, 19), 325}, // 440 TensorAddressingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15332, 27), 406}, // 441 TensorFloat32RoundingINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9690, 11), 207}, // 442 TensorsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15203, 28), 401}, // 443 TernaryBitwiseFunctionINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5619, 13), 136}, // 444 Tessellation in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8837, 22), 155}, // 445 TessellationPointSize in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10605, 23), 249}, // 446 TextureBlockMatch2QCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10551, 22), 246}, // 447 TextureBlockMatchQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10530, 21), 245}, // 448 TextureBoxFilterQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10504, 26), 244}, // 449 TextureSampleWeightedQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9604, 28), 204}, // 450 TileImageColorReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9632, 28), 205}, // 451 TileImageDepthReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9660, 30), 206}, // 452 TileImageStencilReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6721, 16), 247}, // 453 TileShadingQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9304, 18), 184}, // 454 TransformFeedback in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14063, 24), 363}, // 455 USMStorageClassesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14087, 23), 363}, // 456 USMStorageClassesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10062, 35), 222}, // 457 UniformAndStorageBuffer16BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10273, 34), 232}, // 458 UniformAndStorageBuffer8BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8921, 34), 159}, // 459 UniformBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11405, 37), 283}, // 460 UniformBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11442, 40), 283}, // 461 UniformBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9586, 18), 202}, // 462 UniformDecoration in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11243, 39), 281}, // 463 UniformTexelBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11282, 42), 281}, // 464 UniformTexelBufferArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11790, 42), 288}, // 465 UniformTexelBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11832, 45), 288}, // 466 UniformTexelBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13541, 30), 351}, // 467 UnstructuredLoopControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10453, 19), 241}, // 468 UntypedPointersKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15231, 32), 402}, // 469 UntypedVariableLengthArrayINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13277, 25), 345}, // 470 VariableLengthArrayINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10187, 17), 228}, // 471 VariablePointers in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10157, 30), 227}, // 472 VariablePointersStorageBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8679, 9), 140}, // 473 Vector16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13136, 15), 340}, // 474 VectorAnyINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13117, 19), 339}, // 475 VectorComputeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11964, 18), 293}, // 476 VulkanMemoryModel in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12003, 29), 294}, // 477 VulkanMemoryModelDeviceScope in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12032, 32), 294}, // 478 VulkanMemoryModelDeviceScopeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11982, 21), 293}, // 479 VulkanMemoryModelKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9949, 44), 219}, // 480 WorkgroupMemoryExplicitLayout16BitAccessKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9906, 43), 218}, // 481 WorkgroupMemoryExplicitLayout8BitAccessKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9873, 33), 217}, // 482 WorkgroupMemoryExplicitLayoutKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15455, 8), 412}, // 483 Address in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15463, 8), 413}, // 484 Boolean in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15471, 6), 414}, // 485 Float in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15477, 7), 415}, // 486 Signed in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15484, 11), 416}, // 487 SignedChar in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15495, 9), 417}, // 488 Unsigned in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15504, 13), 418}, // 489 UnsignedChar in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15443, 12), 411}, // 490 Unspecified in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15517, 6), 419}, // 491 Class in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15523, 10), 420}, // 492 Structure in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15533, 6), 421}, // 493 Union in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15554, 20), 423}, // 494 ImportedDeclaration in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(15539, 15), 422}, // 495 ImportedModule in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(15663, 15), 431}, // 496 FlagArtificial in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15678, 13), 432}, // 497 FlagExplicit in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15651, 12), 430}, // 498 FlagFwdDecl in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15741, 21), 436}, // 499 FlagIndirectVariable in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15634, 17), 429}, // 500 FlagIsDefinition in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15818, 16), 440}, // 501 FlagIsEnumClass in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15622, 12), 428}, // 502 FlagIsLocal in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15802, 16), 439}, // 503 FlagIsOptimized in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15595, 14), 426}, // 504 FlagIsPrivate in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15579, 16), 425}, // 505 FlagIsProtected in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15609, 13), 427}, // 506 FlagIsPublic in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15762, 20), 437}, // 507 FlagLValueReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15706, 18), 434}, // 508 FlagObjectPointer in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15691, 15), 433}, // 509 FlagPrototyped in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15782, 20), 438}, // 510 FlagRValueReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15724, 17), 435}, // 511 FlagStaticMember in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15854, 24), 442}, // 512 FlagTypePassByReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15834, 20), 441}, // 513 FlagTypePassByValue in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15574, 5), 424}, // 514 None in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15939, 9), 447}, // 515 BitPiece in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(15971, 7), 451}, // 516 Constu in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(15878, 6), 443}, // 517 Deref in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(15978, 9), 452}, // 518 Fragment in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(15889, 6), 445}, // 519 Minus in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(15884, 5), 444}, // 520 Plus in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(15928, 11), 446}, // 521 PlusUconst in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(15960, 11), 450}, // 522 StackValue in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(15948, 5), 448}, // 523 Swap in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(15953, 7), 449}, // 524 Xderef in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16023, 11), 456}, // 525 AtomicType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(15987, 10), 453}, // 526 ConstType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16010, 13), 455}, // 527 RestrictType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(15997, 13), 454}, // 528 VolatileType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16034, 10), 457}, // 529 Float16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16044, 10), 458}, // 530 Float32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16054, 10), 459}, // 531 Float64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16222, 12), 470}, // 532 FloatE4M3NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16234, 12), 471}, // 533 FloatE5M2NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16077, 14), 461}, // 534 SignedInt16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16091, 14), 462}, // 535 SignedInt32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16105, 14), 463}, // 536 SignedInt64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16064, 13), 460}, // 537 SignedInt8NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16182, 19), 468}, // 538 SignedInt8PackedNV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16134, 16), 465}, // 539 UnsignedInt16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16150, 16), 466}, // 540 UnsignedInt32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16166, 16), 467}, // 541 UnsignedInt64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16119, 15), 464}, // 542 UnsignedInt8NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16201, 21), 469}, // 543 UnsignedInt8PackedNV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16298, 28), 475}, // 544 ColumnBlockedInterleavedARM in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(16258, 15), 473}, // 545 ColumnMajorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(16273, 25), 474}, // 546 RowBlockedInterleavedARM in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(16246, 12), 472}, // 547 RowMajorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(16334, 27), 477}, // 548 MatrixASignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16361, 27), 478}, // 549 MatrixBSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16388, 27), 479}, // 550 MatrixCSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16415, 32), 480}, // 551 MatrixResultSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16326, 8), 476}, // 552 NoneKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16447, 26), 481}, // 553 SaturatingAccumulationKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16484, 4), 484}, // 554 2x2 in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(16477, 7), 483}, // 555 Column in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(16473, 4), 482}, // 556 Row in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(16488, 11), 485}, // 557 MatrixAKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(16510, 21), 487}, // 558 MatrixAccumulatorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(16499, 11), 486}, // 559 MatrixBKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(16542, 14), 489}, // 560 ColumnMajorNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(16556, 21), 490}, // 561 InferencingOptimalNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(16531, 11), 488}, // 562 RowMajorNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(16577, 18), 491}, // 563 TrainingOptimalNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(15455, 8), 493}, // 564 Address in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15463, 8), 494}, // 565 Boolean in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15471, 6), 495}, // 566 Float in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15477, 7), 496}, // 567 Signed in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15484, 11), 497}, // 568 SignedChar in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15495, 9), 498}, // 569 Unsigned in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15504, 13), 499}, // 570 UnsignedChar in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15443, 12), 492}, // 571 Unspecified in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15517, 6), 500}, // 572 Class in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(15523, 10), 501}, // 573 Structure in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(15533, 6), 502}, // 574 Union in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(15663, 15), 510}, // 575 FlagArtificial in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15678, 13), 511}, // 576 FlagExplicit in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15651, 12), 509}, // 577 FlagFwdDecl in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15741, 21), 515}, // 578 FlagIndirectVariable in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15634, 17), 508}, // 579 FlagIsDefinition in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15622, 12), 507}, // 580 FlagIsLocal in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15802, 16), 518}, // 581 FlagIsOptimized in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15595, 14), 505}, // 582 FlagIsPrivate in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15579, 16), 504}, // 583 FlagIsProtected in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15609, 13), 506}, // 584 FlagIsPublic in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15762, 20), 516}, // 585 FlagLValueReference in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15706, 18), 513}, // 586 FlagObjectPointer in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15691, 15), 512}, // 587 FlagPrototyped in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15782, 20), 517}, // 588 FlagRValueReference in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15724, 17), 514}, // 589 FlagStaticMember in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15574, 5), 503}, // 590 None in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15939, 9), 523}, // 591 BitPiece in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(15971, 7), 527}, // 592 Constu in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(15878, 6), 519}, // 593 Deref in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(15889, 6), 521}, // 594 Minus in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(15884, 5), 520}, // 595 Plus in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(15928, 11), 522}, // 596 PlusUconst in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(15960, 11), 526}, // 597 StackValue in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(15948, 5), 524}, // 598 Swap in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(15953, 7), 525}, // 599 Xderef in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(15987, 10), 528}, // 600 ConstType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(16010, 13), 530}, // 601 RestrictType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(15997, 13), 529}, // 602 VolatileType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(19250, 16), 646}, // 603 AliasScopeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16804, 8), 550}, // 604 Aliased in SPV_OPERAND_TYPE_DECORATION
  {IR(17922, 15), 603}, // 605 AliasedPointer in SPV_OPERAND_TYPE_DECORATION
  {IR(17937, 18), 603}, // 606 AliasedPointerEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(17282, 10), 574}, // 607 Alignment in SPV_OPERAND_TYPE_DECORATION
  {IR(17326, 12), 576}, // 608 AlignmentId in SPV_OPERAND_TYPE_DECORATION
  {IR(16655, 12), 537}, // 609 ArrayStride in SPV_OPERAND_TYPE_DECORATION
  {IR(18800, 15), 634}, // 610 BankBitsALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18815, 14), 634}, // 611 BankBitsINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18513, 16), 627}, // 612 BankwidthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18529, 15), 627}, // 613 BankwidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16959, 8), 563}, // 614 Binding in SPV_OPERAND_TYPE_DECORATION
  {IR(18034, 16), 607}, // 615 BindlessImageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18016, 18), 606}, // 616 BindlessSamplerNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16619, 6), 533}, // 617 Block in SPV_OPERAND_TYPE_DECORATION
  {IR(17466, 22), 583}, // 618 BlockMatchSamplerQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(17444, 22), 582}, // 619 BlockMatchTextureQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(18065, 13), 609}, // 620 BoundImageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18050, 15), 608}, // 621 BoundSamplerNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16625, 12), 534}, // 622 BufferBlock in SPV_OPERAND_TYPE_DECORATION
  {IR(19410, 21), 651}, // 623 BufferLocationALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19431, 20), 651}, // 624 BufferLocationINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16736, 8), 542}, // 625 BuiltIn in SPV_OPERAND_TYPE_DECORATION
  {IR(18969, 20), 639}, // 626 BurstCoalesceALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18989, 19), 639}, // 627 BurstCoalesceINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16702, 8), 541}, // 628 CPacked in SPV_OPERAND_TYPE_DECORATION
  {IR(20657, 22), 674}, // 629 CacheControlLoadINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20716, 23), 675}, // 630 CacheControlStoreINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19008, 16), 640}, // 631 CacheSizeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19024, 15), 640}, // 632 CacheSizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16769, 9), 546}, // 633 Centroid in SPV_OPERAND_TYPE_DECORATION
  {IR(18118, 13), 612}, // 634 ClobberINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16830, 9), 553}, // 635 Coherent in SPV_OPERAND_TYPE_DECORATION
  {IR(16646, 9), 536}, // 636 ColMajor in SPV_OPERAND_TYPE_DECORATION
  {IR(16943, 10), 561}, // 637 Component in SPV_OPERAND_TYPE_DECORATION
  {IR(20604, 17), 673}, // 638 ConditionalINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19833, 28), 661}, // 639 ConduitKernelArgumentALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19861, 27), 661}, // 640 ConduitKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16821, 9), 552}, // 641 Constant in SPV_OPERAND_TYPE_DECORATION
  {IR(18264, 14), 619}, // 642 CounterBuffer in SPV_OPERAND_TYPE_DECORATION
  {IR(16967, 14), 564}, // 643 DescriptorSet in SPV_OPERAND_TYPE_DECORATION
  {IR(19039, 29), 641}, // 644 DontStaticallyCoalesceALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19068, 28), 641}, // 645 DontStaticallyCoalesceINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18622, 17), 630}, // 646 DoublepumpALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18639, 16), 630}, // 647 DoublepumpINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17488, 18), 584}, // 648 ExplicitInterpAMD in SPV_OPERAND_TYPE_DECORATION
  {IR(17152, 15), 570}, // 649 FPFastMathMode in SPV_OPERAND_TYPE_DECORATION
  {IR(19695, 26), 658}, // 650 FPMaxErrorDecorationINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17102, 15), 569}, // 651 FPRoundingMode in SPV_OPERAND_TYPE_DECORATION
  {IR(16758, 5), 544}, // 652 Flat in SPV_OPERAND_TYPE_DECORATION
  {IR(18829, 21), 635}, // 653 ForcePow2DepthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18850, 20), 635}, // 654 ForcePow2DepthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17054, 14), 568}, // 655 FuncParamAttr in SPV_OPERAND_TYPE_DECORATION
  {IR(18175, 21), 615}, // 656 FuncParamIOKindINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18406, 24), 623}, // 657 FunctionDenormModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19524, 31), 653}, // 658 FunctionFloatingPointModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18349, 26), 622}, // 659 FunctionRoundingModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19160, 26), 644}, // 660 FuseLoopsInFunctionALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19186, 25), 644}, // 661 FuseLoopsInFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16691, 11), 540}, // 662 GLSLPacked in SPV_OPERAND_TYPE_DECORATION
  {IR(16680, 11), 539}, // 663 GLSLShared in SPV_OPERAND_TYPE_DECORATION
  {IR(18238, 26), 618}, // 664 GlobalVariableOffsetINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17985, 31), 605}, // 665 HitObjectShaderRecordBufferEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(17955, 30), 604}, // 666 HitObjectShaderRecordBufferNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18278, 24), 619}, // 667 HlslCounterBufferGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(18315, 19), 620}, // 668 HlslSemanticGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(20455, 16), 670}, // 669 HostAccessINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19451, 20), 652}, // 670 IOPipeStorageALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19471, 19), 652}, // 671 IOPipeStorageINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20547, 29), 672}, // 672 ImplementInRegisterMapALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20576, 28), 672}, // 673 ImplementInRegisterMapINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16953, 6), 562}, // 674 Index in SPV_OPERAND_TYPE_DECORATION
  {IR(20518, 15), 671}, // 675 InitModeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20533, 14), 671}, // 676 InitModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19279, 25), 648}, // 677 InitiationIntervalALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19304, 24), 648}, // 678 InitiationIntervalINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17261, 21), 573}, // 679 InputAttachmentIndex in SPV_OPERAND_TYPE_DECORATION
  {IR(16785, 10), 548}, // 680 Invariant in SPV_OPERAND_TYPE_DECORATION
  {IR(19772, 31), 660}, // 681 LatencyControlConstraintALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19803, 30), 660}, // 682 LatencyControlConstraintINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19721, 26), 659}, // 683 LatencyControlLabelALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19747, 25), 659}, // 684 LatencyControlLabelINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17229, 18), 571}, // 685 LinkageAttributes in SPV_OPERAND_TYPE_DECORATION
  {IR(16934, 9), 560}, // 686 Location in SPV_OPERAND_TYPE_DECORATION
  {IR(19951, 34), 663}, // 687 MMHostInterfaceAddressWidthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19985, 33), 663}, // 688 MMHostInterfaceAddressWidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20018, 31), 664}, // 689 MMHostInterfaceDataWidthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20049, 30), 664}, // 690 MMHostInterfaceDataWidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20079, 29), 665}, // 691 MMHostInterfaceLatencyALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20108, 28), 665}, // 692 MMHostInterfaceLatencyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20239, 30), 667}, // 693 MMHostInterfaceMaxBurstALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20269, 29), 667}, // 694 MMHostInterfaceMaxBurstINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20170, 35), 666}, // 695 MMHostInterfaceReadWriteModeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20205, 34), 666}, // 696 MMHostInterfaceReadWriteModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20298, 33), 668}, // 697 MMHostInterfaceWaitRequestALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20331, 32), 668}, // 698 MMHostInterfaceWaitRequestINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19211, 20), 645}, // 699 MathOpDSPModeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19231, 19), 645}, // 700 MathOpDSPModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16667, 13), 538}, // 701 MatrixStride in SPV_OPERAND_TYPE_DECORATION
  {IR(17292, 14), 575}, // 702 MaxByteOffset in SPV_OPERAND_TYPE_DECORATION
  {IR(17338, 16), 577}, // 703 MaxByteOffsetId in SPV_OPERAND_TYPE_DECORATION
  {IR(19328, 21), 649}, // 704 MaxConcurrencyALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19349, 20), 649}, // 705 MaxConcurrencyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18544, 23), 628}, // 706 MaxPrivateCopiesALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18567, 22), 628}, // 707 MaxPrivateCopiesINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18655, 20), 631}, // 708 MaxReplicatesALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18675, 19), 631}, // 709 MaxReplicatesINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19615, 18), 656}, // 710 MediaBlockIOINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18459, 13), 625}, // 711 MemoryALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18472, 12), 625}, // 712 MemoryINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18735, 12), 633}, // 713 MergeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18747, 11), 633}, // 714 MergeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19266, 13), 647}, // 715 NoAliasINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17247, 14), 572}, // 716 NoContraction in SPV_OPERAND_TYPE_DECORATION
  {IR(16744, 14), 543}, // 717 NoPerspective in SPV_OPERAND_TYPE_DECORATION
  {IR(17398, 13), 579}, // 718 NoSignedWrap in SPV_OPERAND_TYPE_DECORATION
  {IR(17411, 15), 580}, // 719 NoUnsignedWrap in SPV_OPERAND_TYPE_DECORATION
  {IR(17538, 20), 586}, // 720 NodeMaxPayloadsAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17506, 32), 585}, // 721 NodeSharesPayloadLimitsWithAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(16851, 12), 555}, // 722 NonReadable in SPV_OPERAND_TYPE_DECORATION
  {IR(17862, 11), 601}, // 723 NonUniform in SPV_OPERAND_TYPE_DECORATION
  {IR(17873, 14), 601}, // 724 NonUniformEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(16839, 12), 554}, // 725 NonWritable in SPV_OPERAND_TYPE_DECORATION
  {IR(18484, 15), 626}, // 726 NumbanksALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18499, 14), 626}, // 727 NumbanksINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16981, 7), 565}, // 728 Offset in SPV_OPERAND_TYPE_DECORATION
  {IR(17706, 19), 593}, // 729 OverrideCoverageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17725, 14), 594}, // 730 PassthroughNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16763, 6), 545}, // 731 Patch in SPV_OPERAND_TYPE_DECORATION
  {IR(17678, 28), 592}, // 732 PayloadDispatchIndirectAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17653, 25), 591}, // 733 PayloadNodeArraySizeAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17601, 25), 589}, // 734 PayloadNodeBaseIndexAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17581, 20), 588}, // 735 PayloadNodeNameAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17626, 27), 590}, // 736 PayloadNodeSparseArrayAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17786, 16), 597}, // 737 PerPrimitiveEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(17802, 15), 597}, // 738 PerPrimitiveNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17827, 10), 599}, // 739 PerTaskNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17837, 13), 600}, // 740 PerVertexKHR in SPV_OPERAND_TYPE_DECORATION
  {IR(17850, 12), 600}, // 741 PerVertexNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17817, 10), 598}, // 742 PerViewNV in SPV_OPERAND_TYPE_DECORATION
  {IR(19369, 21), 650}, // 743 PipelineEnableALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19390, 20), 650}, // 744 PipelineEnableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19096, 15), 642}, // 745 PrefetchALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19111, 14), 642}, // 746 PrefetchINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18092, 26), 611}, // 747 ReferencedIndirectlyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18430, 15), 624}, // 748 RegisterALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18445, 14), 624}, // 749 RegisterINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19888, 32), 662}, // 750 RegisterMapKernelArgumentALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19920, 31), 662}, // 751 RegisterMapKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16595, 17), 531}, // 752 RelaxedPrecision in SPV_OPERAND_TYPE_DECORATION
  {IR(16795, 9), 549}, // 753 Restrict in SPV_OPERAND_TYPE_DECORATION
  {IR(17887, 16), 602}, // 754 RestrictPointer in SPV_OPERAND_TYPE_DECORATION
  {IR(17903, 19), 602}, // 755 RestrictPointerEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(16637, 9), 535}, // 756 RowMajor in SPV_OPERAND_TYPE_DECORATION
  {IR(18078, 14), 610}, // 757 SIMTCallINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16778, 7), 547}, // 758 Sample in SPV_OPERAND_TYPE_DECORATION
  {IR(16907, 20), 558}, // 759 SaturatedConversion in SPV_OPERAND_TYPE_DECORATION
  {IR(17354, 44), 578}, // 760 SaturatedToLargestFloat8NormalConversionEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(17758, 28), 596}, // 761 SecondaryViewportRelativeNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18131, 17), 613}, // 762 SideEffectsINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18694, 21), 632}, // 763 SimpleDualPortALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18715, 20), 632}, // 764 SimpleDualPortINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19555, 25), 654}, // 765 SingleElementVectorINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18589, 17), 629}, // 766 SinglepumpALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18606, 16), 629}, // 767 SinglepumpINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16612, 7), 532}, // 768 SpecId in SPV_OPERAND_TYPE_DECORATION
  {IR(20363, 27), 669}, // 769 StableKernelArgumentALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20390, 26), 669}, // 770 StableKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18223, 15), 617}, // 771 StackCallINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19125, 18), 643}, // 772 StallEnableALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19143, 17), 643}, // 773 StallEnableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19633, 16), 657}, // 774 StallFreeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19649, 15), 657}, // 775 StallFreeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16927, 7), 559}, // 776 Stream in SPV_OPERAND_TYPE_DECORATION
  {IR(18870, 17), 636}, // 777 StridesizeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18887, 16), 636}, // 778 StridesizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17558, 23), 587}, // 779 TrackFinishWritingAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(18932, 19), 638}, // 780 TrueDualPortALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18951, 18), 638}, // 781 TrueDualPortINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16863, 8), 556}, // 782 Uniform in SPV_OPERAND_TYPE_DECORATION
  {IR(16897, 10), 557}, // 783 UniformId in SPV_OPERAND_TYPE_DECORATION
  {IR(18302, 13), 620}, // 784 UserSemantic in SPV_OPERAND_TYPE_DECORATION
  {IR(18334, 15), 621}, // 785 UserTypeGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(19580, 35), 655}, // 786 VectorComputeCallableFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18196, 27), 616}, // 787 VectorComputeFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18148, 27), 614}, // 788 VectorComputeVariableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17739, 19), 595}, // 789 ViewportRelativeNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16812, 9), 551}, // 790 Volatile in SPV_OPERAND_TYPE_DECORATION
  {IR(17426, 18), 581}, // 791 WeightTextureQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(18903, 15), 637}, // 792 WordsizeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18918, 14), 637}, // 793 WordsizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16988, 10), 566}, // 794 XfbBuffer in SPV_OPERAND_TYPE_DECORATION
  {IR(16998, 10), 567}, // 795 XfbStride in SPV_OPERAND_TYPE_DECORATION
  {IR(20739, 3), 676}, // 796 1D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(20742, 3), 677}, // 797 2D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(20745, 3), 678}, // 798 3D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(20758, 7), 681}, // 799 Buffer in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(20748, 5), 679}, // 800 Cube in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(20753, 5), 680}, // 801 Rect in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(20765, 12), 682}, // 802 SubpassData in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(20777, 17), 683}, // 803 TileImageDataEXT in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21589, 15), 736}, // 804 CoalescingAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21220, 15), 714}, // 805 ContractionOff in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10343, 18), 728}, // 806 DenormFlushToZero in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10328, 15), 727}, // 807 DenormPreserve in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20990, 13), 697}, // 808 DepthGreater in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21003, 10), 698}, // 809 DepthLess in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20975, 15), 696}, // 810 DepthReplacing in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21013, 15), 699}, // 811 DepthUnchanged in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22010, 25), 754}, // 812 DerivativeGroupLinearKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22035, 24), 754}, // 813 DerivativeGroupLinearNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21963, 24), 753}, // 814 DerivativeGroupQuadsKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21987, 23), 753}, // 815 DerivativeGroupQuadsNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21537, 29), 734}, // 816 EarlyAndLateFragmentTestsAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20942, 19), 693}, // 817 EarlyFragmentTests in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22520, 18), 774}, // 818 FPFastMathDefault in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21247, 10), 716}, // 819 Finalizer in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22335, 26), 766}, // 820 FloatingPointModeALTINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22361, 27), 767}, // 821 FloatingPointModeIEEEINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21235, 12), 715}, // 822 Initializer in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21064, 11), 703}, // 823 InputLines in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21075, 20), 704}, // 824 InputLinesAdjacency in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21052, 12), 702}, // 825 InputPoints in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21105, 24), 706}, // 826 InputTrianglesAdjacency in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20794, 12), 684}, // 827 Invocations in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21604, 15), 737}, // 828 IsApiEntryAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21135, 9), 708}, // 829 Isolines in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21028, 10), 700}, // 830 LocalSize in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21038, 14), 701}, // 831 LocalSizeHint in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21315, 16), 721}, // 832 LocalSizeHintId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21303, 12), 720}, // 833 LocalSizeId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21619, 21), 738}, // 834 MaxNodeRecursionAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21664, 21), 741}, // 835 MaxNumWorkgroupsAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22410, 16), 769}, // 836 MaxWorkDimINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22388, 22), 768}, // 837 MaxWorkgroupSizeINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22496, 24), 773}, // 838 MaximallyReconvergesKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22611, 22), 778}, // 839 MaximumRegistersINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22633, 24), 779}, // 840 MaximumRegistersIdINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22588, 23), 777}, // 841 NamedBarrierCountINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22708, 27), 780}, // 842 NamedMaximumRegistersINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22426, 20), 770}, // 843 NoGlobalOffsetINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21331, 34), 722}, // 844 NonCoherentColorAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21365, 34), 723}, // 845 NonCoherentDepthAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21399, 36), 724}, // 846 NonCoherentStencilAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21483, 34), 732}, // 847 NonCoherentTileAttachmentReadQCOM in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22446, 22), 771}, // 848 NumSIMDWorkitemsINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20926, 16), 692}, // 849 OriginLowerLeft in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20910, 16), 691}, // 850 OriginUpperLeft in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21172, 16), 711}, // 851 OutputLineStrip in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21895, 15), 751}, // 852 OutputLinesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21910, 14), 751}, // 853 OutputLinesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21159, 13), 710}, // 854 OutputPoints in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21924, 20), 752}, // 855 OutputPrimitivesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21944, 19), 752}, // 856 OutputPrimitivesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21188, 20), 712}, // 857 OutputTriangleStrip in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22059, 19), 755}, // 858 OutputTrianglesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22078, 18), 755}, // 859 OutputTrianglesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21144, 15), 709}, // 860 OutputVertices in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20891, 19), 690}, // 861 PixelCenterInteger in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22096, 25), 756}, // 862 PixelInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22121, 27), 757}, // 863 PixelInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20961, 10), 694}, // 864 PointMode in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21465, 18), 726}, // 865 PostDepthCoverage in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21836, 19), 748}, // 866 QuadDerivativesKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21129, 6), 707}, // 867 Quads in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22562, 26), 776}, // 868 RegisterMapInterfaceINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21855, 20), 749}, // 869 RequireFullQuadsKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10386, 16), 730}, // 870 RoundingModeRTE in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22314, 21), 765}, // 871 RoundingModeRTNINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22293, 21), 764}, // 872 RoundingModeRTPINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10402, 16), 731}, // 873 RoundingModeRTZ in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22148, 26), 758}, // 874 SampleInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22174, 28), 759}, // 875 SampleInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22468, 28), 772}, // 876 SchedulerTargetFmaxMhzINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(12584, 23), 762}, // 877 Shader64BitIndexingEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(7022, 16), 740}, // 878 ShaderIndexAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22202, 31), 760}, // 879 ShadingRateInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22233, 33), 761}, // 880 ShadingRateInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22266, 27), 763}, // 881 SharedLocalMemorySizeINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21875, 20), 750}, // 882 SharesInputWithAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10361, 25), 729}, // 883 SignedZeroInfNanPreserve in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20806, 13), 685}, // 884 SpacingEqual in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20819, 22), 686}, // 885 SpacingFractionalEven in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20841, 21), 687}, // 886 SpacingFractionalOdd in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21640, 24), 739}, // 887 StaticNumWorkgroupsAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21789, 25), 746}, // 888 StencilRefGreaterBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21713, 26), 743}, // 889 StencilRefGreaterFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21814, 22), 747}, // 890 StencilRefLessBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21739, 23), 744}, // 891 StencilRefLessFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21566, 23), 735}, // 892 StencilRefReplacingEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21762, 27), 745}, // 893 StencilRefUnchangedBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21685, 28), 742}, // 894 StencilRefUnchangedFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22538, 24), 775}, // 895 StreamingInterfaceINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(6129, 13), 717}, // 896 SubgroupSize in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21435, 30), 725}, // 897 SubgroupUniformControlFlowKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21257, 22), 718}, // 898 SubgroupsPerWorkgroup in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21279, 24), 719}, // 899 SubgroupsPerWorkgroupId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21517, 20), 733}, // 900 TileShadingRateQCOM in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21095, 10), 705}, // 901 Triangles in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21208, 12), 713}, // 902 VecTypeHint in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20876, 15), 689}, // 903 VertexOrderCcw in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20862, 14), 688}, // 904 VertexOrderCw in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20971, 4), 695}, // 905 Xfb in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22873, 10), 792}, // 906 AnyHitKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22883, 9), 792}, // 907 AnyHitNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22934, 12), 795}, // 908 CallableKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22946, 11), 795}, // 909 CallableNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22892, 14), 793}, // 910 ClosestHitKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22906, 13), 793}, // 911 ClosestHitNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(15978, 9), 785}, // 912 Fragment in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22785, 10), 786}, // 913 GLCompute in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(5610, 9), 784}, // 914 Geometry in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22842, 16), 791}, // 915 IntersectionKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22858, 15), 791}, // 916 IntersectionNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(5377, 7), 787}, // 917 Kernel in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22965, 8), 797}, // 918 MeshEXT in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22802, 7), 789}, // 919 MeshNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22919, 8), 794}, // 920 MissKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22927, 7), 794}, // 921 MissNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22809, 17), 790}, // 922 RayGenerationKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22826, 16), 790}, // 923 RayGenerationNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22957, 8), 796}, // 924 TaskEXT in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22795, 7), 788}, // 925 TaskNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22742, 20), 782}, // 926 TessellationControl in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22762, 23), 783}, // 927 TessellationEvaluation in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22735, 7), 781}, // 928 Vertex in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22982, 12), 799}, // 929 FlushToZero in SPV_OPERAND_TYPE_FPDENORM_MODE
  {IR(22973, 9), 798}, // 930 Preserve in SPV_OPERAND_TYPE_FPDENORM_MODE
  {IR(22994, 12), 800}, // 931 BFloat16KHR in SPV_OPERAND_TYPE_FPENCODING
  {IR(23006, 14), 801}, // 932 Float8E4M3EXT in SPV_OPERAND_TYPE_FPENCODING
  {IR(23020, 14), 802}, // 933 Float8E5M2EXT in SPV_OPERAND_TYPE_FPENCODING
  {IR(23039, 4), 804}, // 934 ALT in SPV_OPERAND_TYPE_FPOPERATION_MODE
  {IR(23034, 5), 803}, // 935 IEEE in SPV_OPERAND_TYPE_FPOPERATION_MODE
  {IR(23077, 14), 811}, // 936 AllowContract in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23091, 23), 811}, // 937 AllowContractFastINTEL in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23114, 13), 812}, // 938 AllowReassoc in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23127, 18), 812}, // 939 AllowReassocINTEL in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23061, 11), 809}, // 940 AllowRecip in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23145, 15), 813}, // 941 AllowTransform in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23072, 5), 810}, // 942 Fast in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23057, 4), 808}, // 943 NSZ in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(15574, 5), 805}, // 944 None in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23050, 7), 807}, // 945 NotInf in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23043, 7), 806}, // 946 NotNaN in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23160, 4), 814}, // 947 RTE in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(23172, 4), 817}, // 948 RTN in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(23168, 4), 816}, // 949 RTP in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(23164, 4), 815}, // 950 RTZ in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(23208, 18), 820}, // 951 Horizontal2Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(23226, 18), 821}, // 952 Horizontal4Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(23176, 16), 818}, // 953 Vertical2Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(23192, 16), 819}, // 954 Vertical4Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(23267, 6), 826}, // 955 Const in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(23251, 11), 824}, // 956 DontInline in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(23244, 7), 823}, // 957 Inline in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(15574, 5), 822}, // 958 None in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(14581, 11), 827}, // 959 OptNoneEXT in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(14592, 13), 827}, // 960 OptNoneINTEL in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(23262, 5), 825}, // 961 Pure in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(23283, 6), 830}, // 962 ByVal in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23294, 8), 832}, // 963 NoAlias in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23302, 10), 833}, // 964 NoCapture in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23320, 12), 835}, // 965 NoReadWrite in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23312, 8), 834}, // 966 NoWrite in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23332, 21), 836}, // 967 RuntimeAlignedALTERA in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23353, 20), 836}, // 968 RuntimeAlignedINTEL in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23278, 5), 829}, // 969 Sext in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23289, 5), 831}, // 970 Sret in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23273, 5), 828}, // 971 Zext in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23408, 16), 840}, // 972 ClusteredReduce in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23394, 14), 839}, // 973 ExclusiveScan in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23380, 14), 838}, // 974 InclusiveScan in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23471, 27), 843}, // 975 PartitionedExclusiveScanNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23444, 27), 842}, // 976 PartitionedInclusiveScanNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23424, 20), 841}, // 977 PartitionedReduceNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23373, 7), 837}, // 978 Reduce in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23498, 10), 844}, // 979 NoneINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(23508, 10), 845}, // 980 ReadINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(23529, 15), 847}, // 981 ReadWriteINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(23518, 11), 846}, // 982 WriteINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(23544, 5), 849}, // 983 Bias in SPV_OPERAND_TYPE_IMAGE
  {IR(23558, 12), 852}, // 984 ConstOffset in SPV_OPERAND_TYPE_IMAGE
  {IR(23570, 13), 854}, // 985 ConstOffsets in SPV_OPERAND_TYPE_IMAGE
  {IR(23553, 5), 851}, // 986 Grad in SPV_OPERAND_TYPE_IMAGE
  {IR(23549, 4), 850}, // 987 Lod in SPV_OPERAND_TYPE_IMAGE
  {IR(23583, 19), 857}, // 988 MakeTexelAvailable in SPV_OPERAND_TYPE_IMAGE
  {IR(23602, 22), 857}, // 989 MakeTexelAvailableKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(23624, 17), 858}, // 990 MakeTexelVisible in SPV_OPERAND_TYPE_IMAGE
  {IR(23641, 20), 858}, // 991 MakeTexelVisibleKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(9161, 7), 856}, // 992 MinLod in SPV_OPERAND_TYPE_IMAGE
  {IR(23661, 16), 859}, // 993 NonPrivateTexel in SPV_OPERAND_TYPE_IMAGE
  {IR(23677, 19), 859}, // 994 NonPrivateTexelKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(15574, 5), 848}, // 995 None in SPV_OPERAND_TYPE_IMAGE
  {IR(23749, 12), 863}, // 996 Nontemporal in SPV_OPERAND_TYPE_IMAGE
  {IR(16981, 7), 853}, // 997 Offset in SPV_OPERAND_TYPE_IMAGE
  {IR(23761, 8), 864}, // 998 Offsets in SPV_OPERAND_TYPE_IMAGE
  {IR(16778, 7), 855}, // 999 Sample in SPV_OPERAND_TYPE_IMAGE
  {IR(23727, 11), 861}, // 1000 SignExtend in SPV_OPERAND_TYPE_IMAGE
  {IR(23696, 14), 860}, // 1001 VolatileTexel in SPV_OPERAND_TYPE_IMAGE
  {IR(23710, 17), 860}, // 1002 VolatileTexelKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(23738, 11), 862}, // 1003 ZeroExtend in SPV_OPERAND_TYPE_IMAGE
  {IR(15471, 6), 879}, // 1004 Float in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23930, 10), 878}, // 1005 HalfFloat in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23865, 12), 873}, // 1006 SignedInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23877, 12), 874}, // 1007 SignedInt32 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23854, 11), 872}, // 1008 SignedInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23779, 11), 866}, // 1009 SnormInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23769, 10), 865}, // 1010 SnormInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23839, 15), 871}, // 1011 UnormInt101010 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23951, 17), 881}, // 1012 UnormInt101010_2 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23968, 16), 882}, // 1013 UnormInt10X6EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24101, 16), 889}, // 1014 UnormInt12X4EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24117, 16), 890}, // 1015 UnormInt14X2EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23800, 11), 868}, // 1016 UnormInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23940, 11), 880}, // 1017 UnormInt24 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24024, 20), 885}, // 1018 UnormInt2_101010EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23790, 10), 867}, // 1019 UnormInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23825, 14), 870}, // 1020 UnormShort555 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23811, 14), 869}, // 1021 UnormShort565 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24044, 19), 886}, // 1022 UnsignedInt10X6EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24063, 19), 887}, // 1023 UnsignedInt12X4EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24082, 19), 888}, // 1024 UnsignedInt14X2EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23902, 14), 876}, // 1025 UnsignedInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23916, 14), 877}, // 1026 UnsignedInt32 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23889, 13), 875}, // 1027 UnsignedInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23984, 20), 883}, // 1028 UnsignedIntRaw10EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24004, 20), 884}, // 1029 UnsignedIntRaw12EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24135, 2), 892}, // 1030 A in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24236, 5), 910}, // 1031 ABGR in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24157, 5), 898}, // 1032 ARGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24152, 5), 897}, // 1033 BGRA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24194, 6), 904}, // 1034 Depth in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24200, 13), 905}, // 1035 DepthStencil in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24162, 10), 899}, // 1036 Intensity in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24172, 10), 900}, // 1037 Luminance in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24133, 2), 891}, // 1038 R in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24140, 3), 894}, // 1039 RA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24137, 3), 893}, // 1040 RG in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24143, 4), 895}, // 1041 RGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24147, 5), 896}, // 1042 RGBA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24189, 5), 903}, // 1043 RGBx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24185, 4), 902}, // 1044 RGx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24182, 3), 901}, // 1045 Rx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24230, 6), 909}, // 1046 sBGRA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24213, 5), 906}, // 1047 sRGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24224, 6), 908}, // 1048 sRGBA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24218, 6), 907}, // 1049 sRGBx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24241, 28), 911}, // 1050 InitOnDeviceReprogramALTERA in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(24269, 27), 911}, // 1051 InitOnDeviceReprogramINTEL in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(24296, 24), 912}, // 1052 InitOnDeviceResetALTERA in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(24320, 23), 912}, // 1053 InitOnDeviceResetINTEL in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(24343, 7), 913}, // 1054 NoWait in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(24350, 11), 914}, // 1055 WaitKernel in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(24361, 14), 915}, // 1056 WaitWorkGroup in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(24375, 12), 917}, // 1057 CmdExecTime in SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {IR(15574, 5), 916}, // 1058 None in SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {IR(24387, 13), 919}, // 1059 MayUsePrintf in SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {IR(15574, 5), 918}, // 1060 None in SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {IR(24400, 7), 920}, // 1061 Export in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(24407, 7), 921}, // 1062 Import in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(24414, 12), 922}, // 1063 LinkOnceODR in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(24440, 12), 924}, // 1064 CachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(24492, 17), 927}, // 1065 ConstCachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(24467, 25), 926}, // 1066 InvalidateAfterReadINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(24452, 15), 925}, // 1067 StreamingINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(24426, 14), 923}, // 1068 UncachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(24632, 22), 940}, // 1069 DependencyArrayALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24654, 21), 940}, // 1070 DependencyArrayINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24527, 19), 931}, // 1071 DependencyInfinite in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24546, 17), 932}, // 1072 DependencyLength in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24516, 11), 930}, // 1073 DontUnroll in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19279, 25), 938}, // 1074 InitiationIntervalALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19304, 24), 938}, // 1075 InitiationIntervalINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24591, 18), 935}, // 1076 IterationMultiple in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24675, 19), 942}, // 1077 LoopCoalesceALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24694, 18), 942}, // 1078 LoopCoalesceINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24837, 16), 946}, // 1079 LoopCountALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24853, 15), 946}, // 1080 LoopCountINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19328, 21), 939}, // 1081 MaxConcurrencyALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19349, 20), 939}, // 1082 MaxConcurrencyINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24712, 22), 943}, // 1083 MaxInterleavingALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24734, 21), 943}, // 1084 MaxInterleavingINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24577, 14), 934}, // 1085 MaxIterations in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24868, 27), 947}, // 1086 MaxReinvocationDelayALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24895, 26), 947}, // 1087 MaxReinvocationDelayINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24563, 14), 933}, // 1088 MinIterations in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24808, 15), 945}, // 1089 NoFusionALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24823, 14), 945}, // 1090 NoFusionINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(15574, 5), 928}, // 1091 None in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24619, 13), 937}, // 1092 PartialCount in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24609, 10), 936}, // 1093 PeelCount in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19369, 21), 941}, // 1094 PipelineEnableALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19390, 20), 941}, // 1095 PipelineEnableINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24755, 27), 944}, // 1096 SpeculatedIterationsALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24782, 26), 944}, // 1097 SpeculatedIterationsINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24509, 7), 929}, // 1098 Unroll in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25204, 27), 961}, // 1099 MatrixAPackedBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25152, 26), 959}, // 1100 MatrixAPackedFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25072, 23), 955}, // 1101 MatrixAPackedInt4INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25026, 23), 953}, // 1102 MatrixAPackedInt8INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(24921, 29), 949}, // 1103 MatrixASignedComponentsINTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25118, 17), 957}, // 1104 MatrixATF32INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25231, 27), 962}, // 1105 MatrixBPackedBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25178, 26), 960}, // 1106 MatrixBPackedFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25095, 23), 956}, // 1107 MatrixBPackedInt4INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25049, 23), 954}, // 1108 MatrixBPackedInt8INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(24950, 29), 950}, // 1109 MatrixBSignedComponentsINTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25135, 17), 958}, // 1110 MatrixBTF32INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(24979, 21), 951}, // 1111 MatrixCBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25000, 26), 952}, // 1112 MatrixResultBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(15574, 5), 948}, // 1113 None in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25391, 20), 970}, // 1114 AliasScopeINTELMask in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25258, 8), 965}, // 1115 Aligned in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25266, 21), 967}, // 1116 MakePointerAvailable in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25287, 24), 967}, // 1117 MakePointerAvailableKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25311, 19), 968}, // 1118 MakePointerVisible in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25330, 22), 968}, // 1119 MakePointerVisibleKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25411, 17), 971}, // 1120 NoAliasINTELMask in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25352, 18), 969}, // 1121 NonPrivatePointer in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25370, 21), 969}, // 1122 NonPrivatePointerKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(15574, 5), 963}, // 1123 None in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(23749, 12), 966}, // 1124 Nontemporal in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(16812, 9), 964}, // 1125 Volatile in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25435, 8), 973}, // 1126 GLSL450 in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(25443, 7), 974}, // 1127 OpenCL in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(25428, 7), 972}, // 1128 Simple in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(25450, 7), 975}, // 1129 Vulkan in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(25457, 10), 975}, // 1130 VulkanKHR in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(25475, 8), 977}, // 1131 Acquire in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25491, 15), 979}, // 1132 AcquireRelease in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25595, 20), 985}, // 1133 AtomicCounterMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25574, 21), 984}, // 1134 CrossWorkgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25615, 12), 986}, // 1135 ImageMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25656, 14), 988}, // 1136 MakeAvailable in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25670, 17), 988}, // 1137 MakeAvailableKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25687, 12), 989}, // 1138 MakeVisible in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25699, 15), 989}, // 1139 MakeVisibleKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(15574, 5), 976}, // 1140 None in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25627, 13), 987}, // 1141 OutputMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25640, 16), 987}, // 1142 OutputMemoryKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25467, 8), 976}, // 1143 Relaxed in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25483, 8), 978}, // 1144 Release in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25506, 23), 980}, // 1145 SequentiallyConsistent in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25543, 15), 982}, // 1146 SubgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25529, 14), 981}, // 1147 UniformMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(16812, 9), 990}, // 1148 Volatile in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25558, 16), 983}, // 1149 WorkgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25714, 10), 991}, // 1150 AutoINTEL in SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS
  {IR(25729, 4), 993}, // 1151 SAT in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(25742, 8), 995}, // 1152 SAT_SYM in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(25733, 9), 994}, // 1153 SAT_ZERO in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(25724, 5), 992}, // 1154 WRAP in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(25750, 25), 996}, // 1155 PackedVectorFormat4x8Bit in SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {IR(25775, 28), 996}, // 1156 PackedVectorFormat4x8BitKHR in SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {IR(25816, 4), 999}, // 1157 RND in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(25849, 9), 1003}, // 1158 RND_CONV in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(25858, 13), 1004}, // 1159 RND_CONV_ODD in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(25829, 8), 1001}, // 1160 RND_INF in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(25837, 12), 1002}, // 1161 RND_MIN_INF in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(25820, 9), 1000}, // 1162 RND_ZERO in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(25803, 4), 997}, // 1163 TRN in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(25807, 9), 998}, // 1164 TRN_ZERO in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(15574, 5), 1005}, // 1165 None in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(25871, 25), 1006}, // 1166 RobustnessPerComponentNV in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(25896, 23), 1007}, // 1167 RobustnessPerElementNV in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(25988, 27), 1013}, // 1168 CullBackFacingTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26015, 28), 1014}, // 1169 CullFrontFacingTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26057, 16), 1016}, // 1170 CullNoOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26043, 14), 1015}, // 1171 CullOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26127, 30), 1019}, // 1172 ForceOpacityMicromap2StateEXT in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(25929, 12), 1010}, // 1173 NoOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(16326, 8), 1008}, // 1174 NoneKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(25919, 10), 1009}, // 1175 OpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26114, 13), 1018}, // 1176 SkipAABBsKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26090, 24), 1017}, // 1177 SkipBuiltinPrimitivesNV in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(25964, 24), 1012}, // 1178 SkipClosestHitShaderKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26073, 17), 1017}, // 1179 SkipTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(25941, 23), 1011}, // 1180 TerminateOnFirstHitKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26198, 37), 1021}, // 1181 RayQueryCandidateIntersectionAABBKHR in SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {IR(26157, 41), 1020}, // 1182 RayQueryCandidateIntersectionTriangleKHR in SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {IR(26313, 42), 1024}, // 1183 RayQueryCommittedIntersectionGeneratedKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(26235, 37), 1022}, // 1184 RayQueryCommittedIntersectionNoneKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(26272, 41), 1023}, // 1185 RayQueryCommittedIntersectionTriangleKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(26355, 33), 1025}, // 1186 RayQueryCandidateIntersectionKHR in SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {IR(26388, 33), 1026}, // 1187 RayQueryCommittedIntersectionKHR in SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {IR(26433, 6), 1029}, // 1188 Clamp in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(26421, 12), 1028}, // 1189 ClampToEdge in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(15574, 5), 1027}, // 1190 None in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(26439, 7), 1030}, // 1191 Repeat in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(26446, 15), 1031}, // 1192 RepeatMirrored in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(26469, 7), 1033}, // 1193 Linear in SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {IR(26461, 8), 1032}, // 1194 Nearest in SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {IR(26534, 13), 1042}, // 1195 R11fG11fB10f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26576, 4), 1048}, // 1196 R16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26614, 9), 1053}, // 1197 R16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26547, 5), 1043}, // 1198 R16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26676, 5), 1062}, // 1199 R16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26747, 6), 1072}, // 1200 R16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26500, 5), 1037}, // 1201 R32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26654, 5), 1058}, // 1202 R32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26711, 6), 1067}, // 1203 R32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26764, 5), 1075}, // 1204 R64i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26758, 6), 1074}, // 1205 R64ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26580, 3), 1049}, // 1206 R8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26623, 8), 1054}, // 1207 R8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26681, 4), 1063}, // 1208 R8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26753, 5), 1073}, // 1209 R8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26567, 5), 1046}, // 1210 Rg16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26595, 10), 1051}, // 1211 Rg16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26528, 6), 1041}, // 1212 Rg16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26665, 6), 1060}, // 1213 Rg16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26734, 7), 1070}, // 1214 Rg16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26522, 6), 1040}, // 1215 Rg32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26659, 6), 1059}, // 1216 Rg32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26727, 7), 1069}, // 1217 Rg32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26572, 4), 1047}, // 1218 Rg8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26605, 9), 1052}, // 1219 Rg8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26671, 5), 1061}, // 1220 Rg8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26741, 6), 1071}, // 1221 Rg8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26559, 8), 1045}, // 1222 Rgb10A2 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26717, 10), 1068}, // 1223 Rgb10a2ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26552, 7), 1044}, // 1224 Rgba16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26583, 12), 1050}, // 1225 Rgba16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26492, 8), 1036}, // 1226 Rgba16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26639, 8), 1056}, // 1227 Rgba16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26694, 9), 1065}, // 1228 Rgba16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26484, 8), 1035}, // 1229 Rgba32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26631, 8), 1055}, // 1230 Rgba32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26685, 9), 1064}, // 1231 Rgba32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26505, 6), 1038}, // 1232 Rgba8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26511, 11), 1039}, // 1233 Rgba8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26647, 7), 1057}, // 1234 Rgba8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26703, 8), 1066}, // 1235 Rgba8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26476, 8), 1034}, // 1236 Unknown in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26769, 12), 1076}, // 1237 CrossDevice in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(26781, 7), 1077}, // 1238 Device in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(26807, 11), 1080}, // 1239 Invocation in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(26818, 12), 1081}, // 1240 QueueFamily in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(26830, 15), 1081}, // 1241 QueueFamilyKHR in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(26845, 14), 1082}, // 1242 ShaderCallKHR in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(26798, 9), 1079}, // 1243 Subgroup in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(26788, 10), 1078}, // 1244 Workgroup in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(26867, 12), 1085}, // 1245 DontFlatten in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(26859, 8), 1084}, // 1246 Flatten in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(15574, 5), 1083}, // 1247 None in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(26879, 29), 1086}, // 1248 IdentifierPossibleDuplicates in SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS
  {IR(15455, 8), 1088}, // 1249 Address in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15463, 8), 1089}, // 1250 Boolean in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15471, 6), 1090}, // 1251 Float in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15477, 7), 1091}, // 1252 Signed in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15484, 11), 1092}, // 1253 SignedChar in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15495, 9), 1093}, // 1254 Unsigned in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15504, 13), 1094}, // 1255 UnsignedChar in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15443, 12), 1087}, // 1256 Unspecified in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15517, 6), 1095}, // 1257 Class in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15523, 10), 1096}, // 1258 Structure in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15533, 6), 1097}, // 1259 Union in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15554, 20), 1099}, // 1260 ImportedDeclaration in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(15539, 15), 1098}, // 1261 ImportedModule in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(15663, 15), 1107}, // 1262 FlagArtificial in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15678, 13), 1108}, // 1263 FlagExplicit in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15651, 12), 1106}, // 1264 FlagFwdDecl in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15741, 21), 1112}, // 1265 FlagIndirectVariable in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15634, 17), 1105}, // 1266 FlagIsDefinition in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15818, 16), 1116}, // 1267 FlagIsEnumClass in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15622, 12), 1104}, // 1268 FlagIsLocal in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15802, 16), 1115}, // 1269 FlagIsOptimized in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15595, 14), 1102}, // 1270 FlagIsPrivate in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15579, 16), 1101}, // 1271 FlagIsProtected in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15609, 13), 1103}, // 1272 FlagIsPublic in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15762, 20), 1113}, // 1273 FlagLValueReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15706, 18), 1110}, // 1274 FlagObjectPointer in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15691, 15), 1109}, // 1275 FlagPrototyped in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15782, 20), 1114}, // 1276 FlagRValueReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15724, 17), 1111}, // 1277 FlagStaticMember in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15854, 24), 1118}, // 1278 FlagTypePassByReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15834, 20), 1117}, // 1279 FlagTypePassByValue in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(26908, 26), 1119}, // 1280 FlagUnknownPhysicalLayout in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15574, 5), 1100}, // 1281 None in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15939, 9), 1124}, // 1282 BitPiece in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(15971, 7), 1128}, // 1283 Constu in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(15878, 6), 1120}, // 1284 Deref in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(15978, 9), 1129}, // 1285 Fragment in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(15889, 6), 1122}, // 1286 Minus in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(15884, 5), 1121}, // 1287 Plus in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(15928, 11), 1123}, // 1288 PlusUconst in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(15960, 11), 1127}, // 1289 StackValue in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(15948, 5), 1125}, // 1290 Swap in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(15953, 7), 1126}, // 1291 Xderef in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16023, 11), 1133}, // 1292 AtomicType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(15987, 10), 1130}, // 1293 ConstType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16010, 13), 1132}, // 1294 RestrictType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(15997, 13), 1131}, // 1295 VolatileType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(26969, 15), 1140}, // 1296 CPP_for_OpenCL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(26934, 5), 1135}, // 1297 ESSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(26939, 5), 1136}, // 1298 GLSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(26989, 7), 1142}, // 1299 HERO_C in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(26964, 5), 1139}, // 1300 HLSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(26996, 5), 1143}, // 1301 NZSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(26944, 9), 1137}, // 1302 OpenCL_C in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(26953, 11), 1138}, // 1303 OpenCL_CPP in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27016, 5), 1147}, // 1304 Rust in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(26984, 5), 1141}, // 1305 SYCL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27006, 6), 1145}, // 1306 Slang in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(26476, 8), 1134}, // 1307 Unknown in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27001, 5), 1144}, // 1308 WGSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27012, 4), 1146}, // 1309 Zig in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27103, 14), 1158}, // 1310 AtomicCounter in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27185, 16), 1164}, // 1311 CallableDataKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27201, 15), 1164}, // 1312 CallableDataNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27521, 17), 1174}, // 1313 CodeSectionINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27050, 15), 1153}, // 1314 CrossWorkgroup in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27538, 17), 1175}, // 1315 DeviceOnlyALTERA in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27555, 16), 1175}, // 1316 DeviceOnlyINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27073, 9), 1155}, // 1317 Function in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27082, 8), 1156}, // 1318 Generic in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27290, 16), 1167}, // 1319 HitAttributeKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27306, 15), 1167}, // 1320 HitAttributeNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27499, 22), 1173}, // 1321 HitObjectAttributeEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27454, 21), 1171}, // 1322 HitObjectAttributeNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27571, 15), 1176}, // 1323 HostOnlyALTERA in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27586, 14), 1176}, // 1324 HostOnlyINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27117, 6), 1159}, // 1325 Image in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27216, 24), 1165}, // 1326 IncomingCallableDataKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27240, 23), 1165}, // 1327 IncomingCallableDataNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27321, 22), 1168}, // 1328 IncomingRayPayloadKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27343, 21), 1168}, // 1329 IncomingRayPayloadNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27037, 6), 1149}, // 1330 Input in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27169, 16), 1163}, // 1331 NodePayloadAMDX in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27043, 7), 1151}, // 1332 Output in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27407, 22), 1170}, // 1333 PhysicalStorageBuffer in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27429, 25), 1170}, // 1334 PhysicalStorageBufferEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27065, 8), 1154}, // 1335 Private in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27090, 13), 1157}, // 1336 PushConstant in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27263, 14), 1166}, // 1337 RayPayloadKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27277, 13), 1166}, // 1338 RayPayloadNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27364, 22), 1169}, // 1339 ShaderRecordBufferKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27386, 21), 1169}, // 1340 ShaderRecordBufferNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27123, 14), 1160}, // 1341 StorageBuffer in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27475, 24), 1172}, // 1342 TaskPayloadWorkgroupEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27150, 19), 1162}, // 1343 TileAttachmentQCOM in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27137, 13), 1161}, // 1344 TileImageEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(16863, 8), 1150}, // 1345 Uniform in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27021, 16), 1148}, // 1346 UniformConstant in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(26788, 10), 1152}, // 1347 Workgroup in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24452, 15), 1180}, // 1348 StreamingINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(24426, 14), 1177}, // 1349 UncachedINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(27618, 15), 1179}, // 1350 WriteBackINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(27600, 18), 1178}, // 1351 WriteThroughINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(27644, 11), 1183}, // 1352 DecodeFunc in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(15574, 5), 1181}, // 1353 None in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(27633, 11), 1182}, // 1354 TensorView in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(26421, 12), 1186}, // 1355 ClampToEdge in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(16821, 9), 1185}, // 1356 Constant in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(26439, 7), 1187}, // 1357 Repeat in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(26446, 15), 1188}, // 1358 RepeatMirrored in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(27655, 10), 1184}, // 1359 Undefined in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(27708, 24), 1192}, // 1360 MakeElementAvailableARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(27732, 22), 1193}, // 1361 MakeElementVisibleARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(27754, 21), 1194}, // 1362 NonPrivateElementARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(27665, 8), 1189}, // 1363 NoneARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(27673, 15), 1190}, // 1364 NontemporalARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(27688, 20), 1191}, // 1365 OutOfBoundsValueARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
}};

IndexRange OperandNameRangeForKind(spv_operand_type_t type) {
  switch(type) {
    case SPV_OPERAND_TYPE_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_ADDRESSING_MODEL: return IR(3, 5);
    case SPV_OPERAND_TYPE_BUILT_IN: return IR(8, 148);
    case SPV_OPERAND_TYPE_CAPABILITY: return IR(156, 327);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(483, 8);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(491, 3);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(494, 2);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS: return IR(496, 19);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION: return IR(515, 10);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(525, 4);
    case SPV_OPERAND_TYPE_COMPONENT_TYPE: return IR(529, 15);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT: return IR(544, 4);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS: return IR(548, 6);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE: return IR(554, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE: return IR(557, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT: return IR(560, 4);
    case SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(564, 8);
    case SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE: return IR(572, 3);
    case SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS: return IR(575, 16);
    case SPV_OPERAND_TYPE_DEBUG_OPERATION: return IR(591, 9);
    case SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER: return IR(600, 3);
    case SPV_OPERAND_TYPE_DECORATION: return IR(603, 193);
    case SPV_OPERAND_TYPE_DIMENSIONALITY: return IR(796, 8);
    case SPV_OPERAND_TYPE_EXECUTION_MODE: return IR(804, 102);
    case SPV_OPERAND_TYPE_EXECUTION_MODEL: return IR(906, 23);
    case SPV_OPERAND_TYPE_FPDENORM_MODE: return IR(929, 2);
    case SPV_OPERAND_TYPE_FPENCODING: return IR(931, 3);
    case SPV_OPERAND_TYPE_FPOPERATION_MODE: return IR(934, 2);
    case SPV_OPERAND_TYPE_FP_FAST_MATH_MODE: return IR(936, 11);
    case SPV_OPERAND_TYPE_FP_ROUNDING_MODE: return IR(947, 4);
    case SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE: return IR(951, 4);
    case SPV_OPERAND_TYPE_FUNCTION_CONTROL: return IR(955, 7);
    case SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE: return IR(962, 10);
    case SPV_OPERAND_TYPE_GROUP_OPERATION: return IR(972, 7);
    case SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER: return IR(979, 4);
    case SPV_OPERAND_TYPE_IMAGE: return IR(983, 21);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE: return IR(1004, 26);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER: return IR(1030, 20);
    case SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER: return IR(1050, 4);
    case SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS: return IR(1054, 3);
    case SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO: return IR(1057, 2);
    case SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS: return IR(1059, 2);
    case SPV_OPERAND_TYPE_LINKAGE_TYPE: return IR(1061, 3);
    case SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL: return IR(1064, 5);
    case SPV_OPERAND_TYPE_LOOP_CONTROL: return IR(1069, 30);
    case SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(1099, 15);
    case SPV_OPERAND_TYPE_MEMORY_ACCESS: return IR(1114, 12);
    case SPV_OPERAND_TYPE_MEMORY_MODEL: return IR(1126, 5);
    case SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID: return IR(1131, 19);
    case SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS: return IR(1150, 1);
    case SPV_OPERAND_TYPE_OVERFLOW_MODES: return IR(1151, 4);
    case SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT: return IR(1155, 2);
    case SPV_OPERAND_TYPE_QUANTIZATION_MODES: return IR(1157, 8);
    case SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS: return IR(1165, 3);
    case SPV_OPERAND_TYPE_RAY_FLAGS: return IR(1168, 13);
    case SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE: return IR(1181, 2);
    case SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE: return IR(1183, 3);
    case SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION: return IR(1186, 2);
    case SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE: return IR(1188, 5);
    case SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE: return IR(1193, 2);
    case SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT: return IR(1195, 42);
    case SPV_OPERAND_TYPE_SCOPE_ID: return IR(1237, 8);
    case SPV_OPERAND_TYPE_SELECTION_CONTROL: return IR(1245, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS: return IR(1248, 1);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(1249, 8);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(1257, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(1260, 2);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS: return IR(1262, 20);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION: return IR(1282, 10);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(1292, 4);
    case SPV_OPERAND_TYPE_SOURCE_LANGUAGE: return IR(1296, 14);
    case SPV_OPERAND_TYPE_STORAGE_CLASS: return IR(1310, 38);
    case SPV_OPERAND_TYPE_STORE_CACHE_CONTROL: return IR(1348, 4);
    case SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS: return IR(1352, 3);
    case SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE: return IR(1355, 5);
    case SPV_OPERAND_TYPE_TENSOR_OPERANDS: return IR(1360, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_IMAGE: return IR(983, 21);
    case SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS: return IR(1114, 12);
    case SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT: return IR(1155, 2);
    case SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS: return IR(548, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(1099, 15);
    case SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS: return IR(1165, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_FPENCODING: return IR(931, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS: return IR(1360, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_CAPABILITY: return IR(156, 327);
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
static const std::array<InstructionDesc, 858> kInstructionDesc{{
  {spv::Op::OpNop, false, false, IR(0, 0), IR(27775, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpUndef, true, true, IR(39, 2), IR(27831, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpSourceContinued, false, false, IR(11, 1), IR(27837, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpSource, false, false, IR(41, 4), IR(27956, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpSourceExtension, false, false, IR(11, 1), IR(27963, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpName, false, false, IR(45, 2), IR(27979, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpMemberName, false, false, IR(47, 3), IR(27984, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpString, true, false, IR(50, 2), IR(27995, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpLine, false, false, IR(52, 3), IR(28002, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpExtension, false, false, IR(11, 1), IR(28007, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpExtInstImport, true, false, IR(50, 2), IR(28017, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpExtInst, true, true, IR(55, 4), IR(28077, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpMemoryModel, false, false, IR(59, 2), IR(28149, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpEntryPoint, false, false, IR(61, 4), IR(28223, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpExecutionMode, false, false, IR(65, 2), IR(28266, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpCapability, false, false, IR(67, 1), IR(28308, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpTypeVoid, true, false, IR(68, 1), IR(28319, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeBool, true, false, IR(68, 1), IR(28328, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeInt, true, false, IR(69, 3), IR(28337, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeFloat, true, false, IR(72, 3), IR(28382, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeVector, true, false, IR(75, 3), IR(28392, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeMatrix, true, false, IR(75, 3), IR(28403, 11), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeImage, true, false, IR(78, 9), IR(28527, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeSampler, true, false, IR(68, 1), IR(28537, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeSampledImage, true, false, IR(87, 2), IR(28549, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeArray, true, false, IR(89, 3), IR(28566, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeRuntimeArray, true, false, IR(87, 2), IR(28576, 17), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeStruct, true, false, IR(92, 2), IR(28593, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeOpaque, true, false, IR(50, 2), IR(28604, 11), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypePointer, true, false, IR(94, 3), IR(28646, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeFunction, true, false, IR(97, 3), IR(28658, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeEvent, true, false, IR(68, 1), IR(28671, 10), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeDeviceEvent, true, false, IR(68, 1), IR(28681, 16), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeReserveId, true, false, IR(68, 1), IR(28697, 14), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeQueue, true, false, IR(68, 1), IR(28711, 10), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypePipe, true, false, IR(100, 2), IR(28721, 9), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeForwardPointer, false, false, IR(102, 2), IR(28730, 19), IR(0, 0), IR(206, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantTrue, true, true, IR(39, 2), IR(28749, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantFalse, true, true, IR(39, 2), IR(28762, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstant, true, true, IR(104, 3), IR(16821, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantComposite, true, true, IR(107, 3), IR(28814, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantSampler, true, true, IR(110, 5), IR(28910, 16), IR(0, 0), IR(208, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantNull, true, true, IR(39, 2), IR(28926, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantTrue, true, true, IR(39, 2), IR(28939, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantFalse, true, true, IR(39, 2), IR(28956, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstant, true, true, IR(104, 3), IR(28974, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantComposite, true, true, IR(107, 3), IR(28987, 22), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantOp, true, true, IR(115, 3), IR(29050, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpFunction, true, true, IR(118, 4), IR(27073, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionParameter, true, true, IR(39, 2), IR(29099, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionEnd, false, false, IR(0, 0), IR(29117, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionCall, true, true, IR(122, 4), IR(29129, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpVariable, true, true, IR(126, 4), IR(29142, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpImageTexelPointer, true, true, IR(130, 5), IR(29151, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpLoad, true, true, IR(135, 4), IR(29209, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpStore, false, false, IR(139, 3), IR(29214, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCopyMemory, false, false, IR(142, 4), IR(29220, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCopyMemorySized, false, false, IR(146, 5), IR(29231, 16), IR(0, 0), IR(209, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpAccessChain, true, true, IR(122, 4), IR(29247, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpInBoundsAccessChain, true, true, IR(122, 4), IR(29259, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrAccessChain, true, true, IR(151, 5), IR(29279, 15), IR(0, 0), IR(211, 4), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpArrayLength, true, true, IR(156, 4), IR(29294, 12), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpGenericPtrMemSemantics, true, true, IR(160, 3), IR(29306, 23), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpInBoundsPtrAccessChain, true, true, IR(151, 5), IR(29329, 23), IR(0, 0), IR(1, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpDecorate, false, false, IR(163, 2), IR(29380, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpMemberDecorate, false, false, IR(165, 3), IR(29389, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpDecorationGroup, true, false, IR(68, 1), IR(29404, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupDecorate, false, false, IR(168, 2), IR(29420, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupMemberDecorate, false, false, IR(170, 2), IR(29479, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpVectorExtractDynamic, true, true, IR(172, 4), IR(29499, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpVectorInsertDynamic, true, true, IR(130, 5), IR(29520, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpVectorShuffle, true, true, IR(176, 5), IR(29540, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeConstruct, true, true, IR(107, 3), IR(29554, 19), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeExtract, true, true, IR(181, 4), IR(29573, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeInsert, true, true, IR(176, 5), IR(29590, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCopyObject, true, true, IR(160, 3), IR(29606, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpTranspose, true, true, IR(160, 3), IR(29617, 10), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpSampledImage, true, true, IR(172, 4), IR(29627, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleImplicitLod, true, true, IR(185, 5), IR(29672, 23), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleExplicitLod, true, true, IR(190, 5), IR(29718, 23), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleDrefImplicitLod, true, true, IR(195, 6), IR(29741, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleDrefExplicitLod, true, true, IR(201, 6), IR(29768, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjImplicitLod, true, true, IR(185, 5), IR(29795, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjExplicitLod, true, true, IR(190, 5), IR(29822, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjDrefImplicitLod, true, true, IR(195, 6), IR(29849, 31), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjDrefExplicitLod, true, true, IR(201, 6), IR(29880, 31), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageFetch, true, true, IR(185, 5), IR(29911, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageGather, true, true, IR(195, 6), IR(29922, 12), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageDrefGather, true, true, IR(195, 6), IR(29934, 16), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageRead, true, true, IR(185, 5), IR(29950, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageWrite, false, false, IR(207, 4), IR(29960, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImage, true, true, IR(160, 3), IR(27117, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryFormat, true, true, IR(160, 3), IR(29971, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryOrder, true, true, IR(160, 3), IR(29988, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySizeLod, true, true, IR(172, 4), IR(30004, 18), IR(0, 0), IR(215, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySize, true, true, IR(160, 3), IR(30022, 15), IR(0, 0), IR(215, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryLod, true, true, IR(172, 4), IR(30037, 14), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryLevels, true, true, IR(160, 3), IR(30051, 17), IR(0, 0), IR(215, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySamples, true, true, IR(160, 3), IR(30068, 18), IR(0, 0), IR(215, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertFToU, true, true, IR(160, 3), IR(30086, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertFToS, true, true, IR(160, 3), IR(30098, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertSToF, true, true, IR(160, 3), IR(30110, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToF, true, true, IR(160, 3), IR(30122, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpUConvert, true, true, IR(160, 3), IR(30134, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSConvert, true, true, IR(160, 3), IR(30143, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpFConvert, true, true, IR(160, 3), IR(30152, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpQuantizeToF16, true, true, IR(160, 3), IR(30161, 14), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertPtrToU, true, true, IR(160, 3), IR(30175, 14), IR(0, 0), IR(206, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSatConvertSToU, true, true, IR(160, 3), IR(30189, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSatConvertUToS, true, true, IR(160, 3), IR(30204, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToPtr, true, true, IR(160, 3), IR(30219, 14), IR(0, 0), IR(206, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpPtrCastToGeneric, true, true, IR(160, 3), IR(30233, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpGenericCastToPtr, true, true, IR(160, 3), IR(30250, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpGenericCastToPtrExplicit, true, true, IR(211, 4), IR(30267, 25), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpBitcast, true, true, IR(160, 3), IR(30292, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSNegate, true, true, IR(160, 3), IR(30300, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFNegate, true, true, IR(160, 3), IR(30308, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIAdd, true, true, IR(172, 4), IR(30316, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFAdd, true, true, IR(172, 4), IR(30321, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpISub, true, true, IR(172, 4), IR(30326, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFSub, true, true, IR(172, 4), IR(30331, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIMul, true, true, IR(172, 4), IR(30336, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFMul, true, true, IR(172, 4), IR(30341, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDiv, true, true, IR(172, 4), IR(30346, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSDiv, true, true, IR(172, 4), IR(30351, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFDiv, true, true, IR(172, 4), IR(30356, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUMod, true, true, IR(172, 4), IR(30361, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSRem, true, true, IR(172, 4), IR(30366, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSMod, true, true, IR(172, 4), IR(30371, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFRem, true, true, IR(172, 4), IR(30376, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFMod, true, true, IR(172, 4), IR(30381, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpVectorTimesScalar, true, true, IR(172, 4), IR(30386, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesScalar, true, true, IR(172, 4), IR(30404, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpVectorTimesMatrix, true, true, IR(172, 4), IR(30422, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesVector, true, true, IR(172, 4), IR(30440, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesMatrix, true, true, IR(172, 4), IR(30458, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpOuterProduct, true, true, IR(172, 4), IR(30476, 13), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpDot, true, true, IR(172, 4), IR(30489, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIAddCarry, true, true, IR(172, 4), IR(30493, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpISubBorrow, true, true, IR(172, 4), IR(30503, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUMulExtended, true, true, IR(172, 4), IR(30514, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSMulExtended, true, true, IR(172, 4), IR(30527, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpAny, true, true, IR(160, 3), IR(30540, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpAll, true, true, IR(160, 3), IR(30544, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsNan, true, true, IR(160, 3), IR(30548, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsInf, true, true, IR(160, 3), IR(30554, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsFinite, true, true, IR(160, 3), IR(30560, 9), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsNormal, true, true, IR(160, 3), IR(30569, 9), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSignBitSet, true, true, IR(160, 3), IR(30578, 11), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLessOrGreater, true, true, IR(172, 4), IR(30589, 14), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), SPV_SPIRV_VERSION_WORD(1,5), PrintingClass::kRelational_and_Logical},
  {spv::Op::OpOrdered, true, true, IR(172, 4), IR(30603, 8), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUnordered, true, true, IR(172, 4), IR(30611, 10), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalEqual, true, true, IR(172, 4), IR(30621, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalNotEqual, true, true, IR(172, 4), IR(30634, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalOr, true, true, IR(172, 4), IR(30650, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalAnd, true, true, IR(172, 4), IR(30660, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalNot, true, true, IR(160, 3), IR(30671, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSelect, true, true, IR(130, 5), IR(30682, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIEqual, true, true, IR(172, 4), IR(30689, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpINotEqual, true, true, IR(172, 4), IR(30696, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUGreaterThan, true, true, IR(172, 4), IR(30706, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSGreaterThan, true, true, IR(172, 4), IR(30719, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUGreaterThanEqual, true, true, IR(172, 4), IR(30732, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSGreaterThanEqual, true, true, IR(172, 4), IR(30750, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpULessThan, true, true, IR(172, 4), IR(30768, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSLessThan, true, true, IR(172, 4), IR(30778, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpULessThanEqual, true, true, IR(172, 4), IR(30788, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSLessThanEqual, true, true, IR(172, 4), IR(30803, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdEqual, true, true, IR(172, 4), IR(30818, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordEqual, true, true, IR(172, 4), IR(30828, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdNotEqual, true, true, IR(172, 4), IR(30840, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordNotEqual, true, true, IR(172, 4), IR(30853, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdLessThan, true, true, IR(172, 4), IR(30868, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordLessThan, true, true, IR(172, 4), IR(30881, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdGreaterThan, true, true, IR(172, 4), IR(30896, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordGreaterThan, true, true, IR(172, 4), IR(30912, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdLessThanEqual, true, true, IR(172, 4), IR(30930, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordLessThanEqual, true, true, IR(172, 4), IR(30948, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdGreaterThanEqual, true, true, IR(172, 4), IR(30968, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordGreaterThanEqual, true, true, IR(172, 4), IR(30989, 23), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpShiftRightLogical, true, true, IR(172, 4), IR(31012, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpShiftRightArithmetic, true, true, IR(172, 4), IR(31030, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpShiftLeftLogical, true, true, IR(172, 4), IR(31051, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseOr, true, true, IR(172, 4), IR(31068, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseXor, true, true, IR(172, 4), IR(31078, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseAnd, true, true, IR(172, 4), IR(31089, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpNot, true, true, IR(160, 3), IR(31100, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldInsert, true, true, IR(215, 6), IR(31104, 15), IR(0, 0), IR(218, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldSExtract, true, true, IR(130, 5), IR(31119, 17), IR(0, 0), IR(218, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldUExtract, true, true, IR(130, 5), IR(31136, 17), IR(0, 0), IR(218, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitReverse, true, true, IR(160, 3), IR(31153, 11), IR(0, 0), IR(218, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitCount, true, true, IR(160, 3), IR(31164, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpDPdx, true, true, IR(160, 3), IR(31173, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdy, true, true, IR(160, 3), IR(31178, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidth, true, true, IR(160, 3), IR(31183, 7), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdxFine, true, true, IR(160, 3), IR(31190, 9), IR(0, 0), IR(220, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdyFine, true, true, IR(160, 3), IR(31199, 9), IR(0, 0), IR(220, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidthFine, true, true, IR(160, 3), IR(31208, 11), IR(0, 0), IR(220, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdxCoarse, true, true, IR(160, 3), IR(31219, 11), IR(0, 0), IR(220, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdyCoarse, true, true, IR(160, 3), IR(31230, 11), IR(0, 0), IR(220, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidthCoarse, true, true, IR(160, 3), IR(31241, 13), IR(0, 0), IR(220, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpEmitVertex, false, false, IR(0, 0), IR(31254, 11), IR(0, 0), IR(69, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEndPrimitive, false, false, IR(0, 0), IR(31265, 13), IR(0, 0), IR(69, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEmitStreamVertex, false, false, IR(10, 1), IR(31278, 17), IR(0, 0), IR(117, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEndStreamPrimitive, false, false, IR(10, 1), IR(31295, 19), IR(0, 0), IR(117, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpControlBarrier, false, false, IR(221, 3), IR(31351, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpMemoryBarrier, false, false, IR(224, 2), IR(31366, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpAtomicLoad, true, true, IR(226, 5), IR(31380, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicStore, false, false, IR(231, 4), IR(31391, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicExchange, true, true, IR(235, 6), IR(31403, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicCompareExchange, true, true, IR(241, 8), IR(31418, 22), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicCompareExchangeWeak, true, true, IR(241, 8), IR(31440, 26), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), SPV_SPIRV_VERSION_WORD(1,3), PrintingClass::kAtomic},
  {spv::Op::OpAtomicIIncrement, true, true, IR(226, 5), IR(31466, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicIDecrement, true, true, IR(226, 5), IR(31483, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicIAdd, true, true, IR(235, 6), IR(31500, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicISub, true, true, IR(235, 6), IR(31511, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicSMin, true, true, IR(235, 6), IR(31522, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicUMin, true, true, IR(235, 6), IR(31533, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicSMax, true, true, IR(235, 6), IR(31544, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicUMax, true, true, IR(235, 6), IR(31555, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicAnd, true, true, IR(235, 6), IR(31566, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicOr, true, true, IR(235, 6), IR(31576, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicXor, true, true, IR(235, 6), IR(31585, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpPhi, true, true, IR(107, 3), IR(31595, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLoopMerge, false, false, IR(249, 3), IR(31629, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpSelectionMerge, false, false, IR(252, 2), IR(31674, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLabel, true, false, IR(68, 1), IR(31689, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpBranch, false, false, IR(10, 1), IR(31695, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpBranchConditional, false, false, IR(254, 4), IR(31702, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpSwitch, false, false, IR(258, 3), IR(31765, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpKill, false, false, IR(0, 0), IR(31772, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpReturn, false, false, IR(0, 0), IR(31777, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpReturnValue, false, false, IR(10, 1), IR(31784, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpUnreachable, false, false, IR(0, 0), IR(31796, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLifetimeStart, false, false, IR(261, 2), IR(31808, 14), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLifetimeStop, false, false, IR(261, 2), IR(31822, 13), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpGroupAsyncCopy, true, true, IR(263, 8), IR(31835, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupWaitEvents, false, false, IR(271, 3), IR(31850, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupAll, true, true, IR(274, 4), IR(31866, 9), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupAny, true, true, IR(274, 4), IR(31875, 9), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBroadcast, true, true, IR(278, 5), IR(31884, 15), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupIAdd, true, true, IR(283, 5), IR(31932, 10), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFAdd, true, true, IR(283, 5), IR(31942, 10), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMin, true, true, IR(283, 5), IR(31952, 10), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMin, true, true, IR(283, 5), IR(31962, 10), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMin, true, true, IR(283, 5), IR(31972, 10), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMax, true, true, IR(283, 5), IR(31982, 10), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMax, true, true, IR(283, 5), IR(31992, 10), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMax, true, true, IR(283, 5), IR(32002, 10), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpReadPipe, true, true, IR(215, 6), IR(32012, 9), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpWritePipe, true, true, IR(215, 6), IR(32021, 10), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReservedReadPipe, true, true, IR(288, 8), IR(32031, 17), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReservedWritePipe, true, true, IR(288, 8), IR(32048, 18), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReserveReadPipePackets, true, true, IR(215, 6), IR(32066, 23), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReserveWritePipePackets, true, true, IR(215, 6), IR(32089, 24), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCommitReadPipe, false, false, IR(296, 4), IR(32113, 15), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCommitWritePipe, false, false, IR(296, 4), IR(32128, 16), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpIsValidReserveId, true, true, IR(160, 3), IR(32144, 17), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetNumPipePackets, true, true, IR(130, 5), IR(32161, 18), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetMaxPipePackets, true, true, IR(130, 5), IR(32179, 18), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupReserveReadPipePackets, true, true, IR(300, 7), IR(32197, 28), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupReserveWritePipePackets, true, true, IR(300, 7), IR(32225, 29), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupCommitReadPipe, false, false, IR(307, 5), IR(32254, 20), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupCommitWritePipe, false, false, IR(307, 5), IR(32274, 21), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpEnqueueMarker, true, true, IR(215, 6), IR(32295, 14), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpEnqueueKernel, true, true, IR(312, 13), IR(32309, 14), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelNDrangeSubGroupCount, true, true, IR(325, 7), IR(32323, 30), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelNDrangeMaxSubGroupSize, true, true, IR(325, 7), IR(32353, 32), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelWorkGroupSize, true, true, IR(215, 6), IR(32385, 23), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelPreferredWorkGroupSizeMultiple, true, true, IR(215, 6), IR(32408, 40), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpRetainEvent, false, false, IR(10, 1), IR(32448, 12), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpReleaseEvent, false, false, IR(10, 1), IR(32460, 13), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpCreateUserEvent, true, true, IR(39, 2), IR(32473, 16), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpIsValidEvent, true, true, IR(160, 3), IR(32489, 13), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpSetUserEventStatus, false, false, IR(36, 2), IR(32502, 19), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpCaptureEventProfilingInfo, false, false, IR(33, 3), IR(32521, 26), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetDefaultQueue, true, true, IR(39, 2), IR(32547, 16), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpBuildNDRange, true, true, IR(130, 5), IR(32563, 13), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpImageSparseSampleImplicitLod, true, true, IR(185, 5), IR(32576, 29), IR(0, 0), IR(222, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleExplicitLod, true, true, IR(190, 5), IR(32605, 29), IR(0, 0), IR(222, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleDrefImplicitLod, true, true, IR(195, 6), IR(32634, 33), IR(0, 0), IR(222, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleDrefExplicitLod, true, true, IR(201, 6), IR(32667, 33), IR(0, 0), IR(222, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjImplicitLod, true, true, IR(185, 5), IR(32700, 33), IR(0, 0), IR(222, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjExplicitLod, true, true, IR(190, 5), IR(32733, 33), IR(0, 0), IR(222, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjDrefImplicitLod, true, true, IR(195, 6), IR(32766, 37), IR(0, 0), IR(222, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjDrefExplicitLod, true, true, IR(201, 6), IR(32803, 37), IR(0, 0), IR(222, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseFetch, true, true, IR(185, 5), IR(32840, 17), IR(0, 0), IR(222, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseGather, true, true, IR(195, 6), IR(32857, 18), IR(0, 0), IR(222, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseDrefGather, true, true, IR(195, 6), IR(32875, 22), IR(0, 0), IR(222, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseTexelsResident, true, true, IR(160, 3), IR(32897, 26), IR(0, 0), IR(222, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpNoLine, false, false, IR(0, 0), IR(32923, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpAtomicFlagTestAndSet, true, true, IR(226, 5), IR(32930, 21), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicFlagClear, false, false, IR(332, 3), IR(32951, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpImageSparseRead, true, true, IR(185, 5), IR(32967, 16), IR(0, 0), IR(222, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpSizeOf, true, true, IR(160, 3), IR(32983, 7), IR(0, 0), IR(1, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpTypePipeStorage, true, false, IR(68, 1), IR(32990, 16), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantPipeStorage, true, true, IR(335, 5), IR(33006, 20), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCreatePipeFromPipeStorage, true, true, IR(160, 3), IR(33026, 26), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetKernelLocalSizeForSubgroupCount, true, true, IR(325, 7), IR(33052, 35), IR(0, 0), IR(157, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelMaxNumSubgroups, true, true, IR(215, 6), IR(33087, 25), IR(0, 0), IR(157, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpTypeNamedBarrier, true, false, IR(68, 1), IR(33112, 17), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpNamedBarrierInitialize, true, true, IR(160, 3), IR(33129, 23), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpMemoryNamedBarrier, false, false, IR(332, 3), IR(33152, 19), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpModuleProcessed, false, false, IR(11, 1), IR(33171, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpExecutionModeId, false, false, IR(65, 2), IR(33187, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,2), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpDecorateId, false, false, IR(163, 2), IR(33203, 11), IR(0, 0), IR(1, 0), IR(181, 1), SPV_SPIRV_VERSION_WORD(1,2), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupNonUniformElect, true, true, IR(340, 3), IR(33214, 21), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAll, true, true, IR(274, 4), IR(33235, 19), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAny, true, true, IR(274, 4), IR(33254, 19), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAllEqual, true, true, IR(274, 4), IR(33273, 24), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBroadcast, true, true, IR(278, 5), IR(33297, 25), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBroadcastFirst, true, true, IR(274, 4), IR(33322, 30), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallot, true, true, IR(274, 4), IR(6397, 22), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformInverseBallot, true, true, IR(274, 4), IR(33352, 29), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotBitExtract, true, true, IR(278, 5), IR(33381, 32), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotBitCount, true, true, IR(283, 5), IR(33413, 30), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotFindLSB, true, true, IR(274, 4), IR(33443, 29), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotFindMSB, true, true, IR(274, 4), IR(33472, 29), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffle, true, true, IR(278, 5), IR(9487, 23), IR(0, 0), IR(227, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleXor, true, true, IR(278, 5), IR(33501, 26), IR(0, 0), IR(227, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleUp, true, true, IR(278, 5), IR(33527, 25), IR(0, 0), IR(228, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleDown, true, true, IR(278, 5), IR(33552, 27), IR(0, 0), IR(228, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformIAdd, true, true, IR(343, 6), IR(33579, 20), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFAdd, true, true, IR(343, 6), IR(33599, 20), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformIMul, true, true, IR(343, 6), IR(33619, 20), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMul, true, true, IR(343, 6), IR(33639, 20), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformSMin, true, true, IR(343, 6), IR(33659, 20), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformUMin, true, true, IR(343, 6), IR(33679, 20), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMin, true, true, IR(343, 6), IR(33699, 20), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformSMax, true, true, IR(343, 6), IR(33719, 20), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformUMax, true, true, IR(343, 6), IR(33739, 20), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMax, true, true, IR(343, 6), IR(33759, 20), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseAnd, true, true, IR(343, 6), IR(33779, 26), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseOr, true, true, IR(343, 6), IR(33805, 25), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseXor, true, true, IR(343, 6), IR(33830, 26), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalAnd, true, true, IR(343, 6), IR(33856, 26), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalOr, true, true, IR(343, 6), IR(33882, 25), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalXor, true, true, IR(343, 6), IR(33907, 26), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadBroadcast, true, true, IR(278, 5), IR(33933, 29), IR(0, 0), IR(232, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadSwap, true, true, IR(278, 5), IR(33962, 24), IR(0, 0), IR(232, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpCopyLogical, true, true, IR(160, 3), IR(33986, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpPtrEqual, true, true, IR(172, 4), IR(33998, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrNotEqual, true, true, IR(172, 4), IR(34007, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrDiff, true, true, IR(172, 4), IR(34019, 8), IR(0, 0), IR(233, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpColorAttachmentReadEXT, true, true, IR(349, 4), IR(34027, 23), IR(0, 0), IR(149, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpDepthAttachmentReadEXT, true, true, IR(353, 3), IR(34050, 23), IR(0, 0), IR(158, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpStencilAttachmentReadEXT, true, true, IR(353, 3), IR(34073, 25), IR(0, 0), IR(159, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpTypeTensorARM, true, false, IR(356, 4), IR(34098, 14), IR(0, 0), IR(205, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTensorReadARM, true, true, IR(360, 5), IR(34154, 14), IR(0, 0), IR(205, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpTensorWriteARM, false, false, IR(365, 4), IR(34168, 15), IR(0, 0), IR(205, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpTensorQuerySizeARM, true, true, IR(172, 4), IR(34183, 19), IR(0, 0), IR(205, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpGraphConstantARM, true, true, IR(369, 3), IR(34202, 17), IR(0, 0), IR(236, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphEntryPointARM, false, false, IR(372, 3), IR(34219, 19), IR(0, 0), IR(236, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphARM, true, true, IR(39, 2), IR(9778, 9), IR(0, 0), IR(236, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphInputARM, true, true, IR(122, 4), IR(34238, 14), IR(0, 0), IR(236, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphSetOutputARM, false, false, IR(375, 3), IR(34252, 18), IR(0, 0), IR(236, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphEndARM, false, false, IR(0, 0), IR(34270, 12), IR(0, 0), IR(236, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpTypeGraphARM, true, false, IR(378, 3), IR(34282, 13), IR(0, 0), IR(236, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTerminateInvocation, false, false, IR(0, 0), IR(34295, 20), IR(0, 0), IR(3, 1), IR(191, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpTypeUntypedPointerKHR, true, false, IR(381, 2), IR(34315, 22), IR(0, 0), IR(237, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpUntypedVariableKHR, true, true, IR(383, 5), IR(34337, 19), IR(0, 0), IR(237, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedAccessChainKHR, true, true, IR(151, 5), IR(34356, 22), IR(0, 0), IR(237, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedInBoundsAccessChainKHR, true, true, IR(151, 5), IR(34378, 30), IR(0, 0), IR(237, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpSubgroupBallotKHR, true, true, IR(160, 3), IR(6158, 18), IR(0, 0), IR(238, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupFirstInvocationKHR, true, true, IR(160, 3), IR(34408, 27), IR(0, 0), IR(238, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpUntypedPtrAccessChainKHR, true, true, IR(388, 6), IR(34435, 25), IR(0, 0), IR(237, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedInBoundsPtrAccessChainKHR, true, true, IR(388, 6), IR(34460, 33), IR(0, 0), IR(237, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedArrayLengthKHR, true, true, IR(394, 5), IR(34493, 22), IR(0, 0), IR(237, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedPrefetchKHR, false, false, IR(399, 5), IR(34515, 19), IR(0, 0), IR(237, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpFmaKHR, true, true, IR(130, 5), IR(34534, 7), IR(0, 0), IR(239, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSubgroupAllKHR, true, true, IR(160, 3), IR(34541, 15), IR(0, 0), IR(240, 1), IR(41, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupAnyKHR, true, true, IR(160, 3), IR(34556, 15), IR(0, 0), IR(240, 1), IR(41, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupAllEqualKHR, true, true, IR(160, 3), IR(34571, 20), IR(0, 0), IR(240, 1), IR(41, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupNonUniformRotateKHR, true, true, IR(404, 6), IR(14474, 25), IR(0, 0), IR(241, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupReadInvocationKHR, true, true, IR(172, 4), IR(34591, 26), IR(0, 0), IR(238, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpExtInstWithForwardRefsKHR, true, true, IR(410, 5), IR(34617, 26), IR(0, 0), IR(1, 0), IR(192, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpUntypedGroupAsyncCopyKHR, true, true, IR(415, 11), IR(34643, 25), IR(0, 0), IR(237, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpTraceRayKHR, false, false, IR(426, 11), IR(34668, 12), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpExecuteCallableKHR, false, false, IR(36, 2), IR(34680, 19), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToAccelerationStructureKHR, true, true, IR(160, 3), IR(34699, 35), IR(0, 0), IR(242, 2), IR(193, 2), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIgnoreIntersectionKHR, false, false, IR(0, 0), IR(34734, 22), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTerminateRayKHR, false, false, IR(0, 0), IR(34756, 16), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSDot, true, true, IR(437, 5), IR(34819, 5), IR(167, 1), IR(244, 1), IR(141, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDot, true, true, IR(437, 5), IR(34832, 5), IR(168, 1), IR(244, 1), IR(141, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSUDot, true, true, IR(437, 5), IR(34845, 6), IR(169, 1), IR(244, 1), IR(141, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSDotAccSat, true, true, IR(442, 6), IR(34860, 11), IR(170, 1), IR(244, 1), IR(141, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDotAccSat, true, true, IR(442, 6), IR(34885, 11), IR(171, 1), IR(244, 1), IR(141, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSUDotAccSat, true, true, IR(442, 6), IR(34910, 12), IR(172, 1), IR(244, 1), IR(141, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpTypeCooperativeMatrixKHR, true, false, IR(448, 6), IR(34937, 25), IR(0, 0), IR(86, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeMatrixLoadKHR, true, true, IR(454, 6), IR(34962, 25), IR(0, 0), IR(86, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixStoreKHR, false, false, IR(460, 5), IR(34987, 26), IR(0, 0), IR(86, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixMulAddKHR, true, true, IR(465, 6), IR(35067, 27), IR(0, 0), IR(86, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpCooperativeMatrixLengthKHR, true, true, IR(160, 3), IR(35094, 27), IR(0, 0), IR(86, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpConstantCompositeReplicateEXT, true, true, IR(160, 3), IR(35121, 30), IR(0, 0), IR(245, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCompositeReplicateEXT, true, true, IR(160, 3), IR(35151, 34), IR(0, 0), IR(245, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpCompositeConstructReplicateEXT, true, true, IR(160, 3), IR(35185, 31), IR(0, 0), IR(245, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpTypeRayQueryKHR, true, false, IR(68, 1), IR(35216, 16), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpRayQueryInitializeKHR, false, false, IR(471, 8), IR(35232, 22), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryTerminateKHR, false, false, IR(10, 1), IR(35254, 21), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGenerateIntersectionKHR, false, false, IR(36, 2), IR(35275, 32), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryConfirmIntersectionKHR, false, false, IR(10, 1), IR(35307, 31), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryProceedKHR, true, true, IR(160, 3), IR(35338, 19), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTypeKHR, true, true, IR(172, 4), IR(35357, 31), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpImageSampleWeightedQCOM, true, true, IR(130, 5), IR(35388, 24), IR(0, 0), IR(246, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBoxFilterQCOM, true, true, IR(130, 5), IR(35412, 19), IR(0, 0), IR(247, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchSSDQCOM, true, true, IR(325, 7), IR(35431, 23), IR(0, 0), IR(248, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchSADQCOM, true, true, IR(325, 7), IR(35454, 23), IR(0, 0), IR(248, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpBitCastArrayQCOM, true, true, IR(160, 3), IR(35477, 17), IR(0, 0), IR(249, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpImageBlockMatchWindowSSDQCOM, true, true, IR(325, 7), IR(35494, 29), IR(0, 0), IR(250, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchWindowSADQCOM, true, true, IR(325, 7), IR(35523, 29), IR(0, 0), IR(250, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchGatherSSDQCOM, true, true, IR(325, 7), IR(35552, 29), IR(0, 0), IR(250, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchGatherSADQCOM, true, true, IR(325, 7), IR(35581, 29), IR(0, 0), IR(250, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpCompositeConstructCoopMatQCOM, true, true, IR(160, 3), IR(35610, 30), IR(0, 0), IR(249, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeExtractCoopMatQCOM, true, true, IR(160, 3), IR(35640, 28), IR(0, 0), IR(249, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpExtractSubArrayQCOM, true, true, IR(172, 4), IR(35668, 20), IR(0, 0), IR(249, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpGroupIAddNonUniformAMD, true, true, IR(283, 5), IR(35688, 23), IR(0, 0), IR(221, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFAddNonUniformAMD, true, true, IR(283, 5), IR(35711, 23), IR(0, 0), IR(221, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMinNonUniformAMD, true, true, IR(283, 5), IR(35734, 23), IR(0, 0), IR(221, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMinNonUniformAMD, true, true, IR(283, 5), IR(35757, 23), IR(0, 0), IR(221, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMinNonUniformAMD, true, true, IR(283, 5), IR(35780, 23), IR(0, 0), IR(221, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMaxNonUniformAMD, true, true, IR(283, 5), IR(35803, 23), IR(0, 0), IR(221, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMaxNonUniformAMD, true, true, IR(283, 5), IR(35826, 23), IR(0, 0), IR(221, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMaxNonUniformAMD, true, true, IR(283, 5), IR(35849, 23), IR(0, 0), IR(221, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpFragmentMaskFetchAMD, true, true, IR(172, 4), IR(35872, 21), IR(0, 0), IR(251, 1), IR(58, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFragmentFetchAMD, true, true, IR(130, 5), IR(35893, 17), IR(0, 0), IR(251, 1), IR(58, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReadClockKHR, true, true, IR(340, 3), IR(35910, 13), IR(0, 0), IR(252, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAllocateNodePayloadsAMDX, true, true, IR(278, 5), IR(35923, 25), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpEnqueueNodePayloadsAMDX, false, false, IR(10, 1), IR(35948, 24), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeNodePayloadArrayAMDX, true, false, IR(87, 2), IR(35972, 25), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFinishWritingNodePayloadAMDX, true, true, IR(160, 3), IR(35997, 29), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpNodePayloadArrayLengthAMDX, true, true, IR(160, 3), IR(36026, 27), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIsNodePayloadValidAMDX, true, true, IR(172, 4), IR(36053, 23), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConstantStringAMDX, true, false, IR(50, 2), IR(36076, 19), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSpecConstantStringAMDX, true, false, IR(50, 2), IR(36095, 23), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpGroupNonUniformQuadAllKHR, true, true, IR(160, 3), IR(36118, 26), IR(0, 0), IR(166, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadAnyKHR, true, true, IR(160, 3), IR(36144, 26), IR(0, 0), IR(166, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpHitObjectRecordHitMotionNV, false, false, IR(479, 14), IR(36170, 27), IR(0, 0), IR(253, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitWithIndexMotionNV, false, false, IR(493, 13), IR(36197, 36), IR(0, 0), IR(253, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissMotionNV, false, false, IR(506, 7), IR(36233, 28), IR(0, 0), IR(253, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldToObjectNV, true, true, IR(160, 3), IR(36261, 28), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectToWorldNV, true, true, IR(160, 3), IR(36289, 28), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayDirectionNV, true, true, IR(160, 3), IR(36317, 33), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayOriginNV, true, true, IR(160, 3), IR(36350, 30), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayMotionNV, false, false, IR(493, 13), IR(36380, 26), IR(0, 0), IR(253, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderRecordBufferHandleNV, true, true, IR(160, 3), IR(36406, 39), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderBindingTableRecordIndexNV, true, true, IR(160, 3), IR(36445, 44), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordEmptyNV, false, false, IR(10, 1), IR(36489, 23), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayNV, false, false, IR(513, 12), IR(36512, 20), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitNV, false, false, IR(493, 13), IR(36532, 21), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitWithIndexNV, false, false, IR(513, 12), IR(36553, 30), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissNV, false, false, IR(525, 6), IR(36583, 22), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectExecuteShaderNV, false, false, IR(36, 2), IR(36605, 25), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetCurrentTimeNV, true, true, IR(160, 3), IR(36630, 26), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetAttributesNV, false, false, IR(36, 2), IR(36656, 25), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetHitKindNV, true, true, IR(160, 3), IR(36681, 22), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetPrimitiveIndexNV, true, true, IR(160, 3), IR(36703, 29), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetGeometryIndexNV, true, true, IR(160, 3), IR(36732, 28), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceIdNV, true, true, IR(160, 3), IR(36760, 25), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceCustomIndexNV, true, true, IR(160, 3), IR(36785, 34), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayDirectionNV, true, true, IR(160, 3), IR(36819, 32), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayOriginNV, true, true, IR(160, 3), IR(36851, 29), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMaxNV, true, true, IR(160, 3), IR(36880, 22), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMinNV, true, true, IR(160, 3), IR(36902, 22), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsEmptyNV, true, true, IR(160, 3), IR(36924, 19), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsHitNV, true, true, IR(160, 3), IR(36943, 17), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsMissNV, true, true, IR(160, 3), IR(36960, 18), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHitObjectNV, false, false, IR(531, 3), IR(36978, 29), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHintNV, false, false, IR(36, 2), IR(37007, 24), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeHitObjectNV, true, false, IR(68, 1), IR(37031, 16), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpImageSampleFootprintNV, true, true, IR(534, 7), IR(37047, 23), IR(0, 0), IR(255, 1), IR(72, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpTypeCooperativeVectorNV, true, false, IR(89, 3), IR(37070, 24), IR(173, 1), IR(256, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeVectorMatrixMulNV, true, true, IR(541, 13), IR(37110, 29), IR(0, 0), IR(258, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorOuterProductAccumulateNV, false, false, IR(554, 7), IR(37139, 42), IR(0, 0), IR(259, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorReduceSumAccumulateNV, false, false, IR(33, 3), IR(37181, 39), IR(0, 0), IR(259, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorMatrixMulAddNV, true, true, IR(561, 16), IR(37220, 32), IR(0, 0), IR(258, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixConvertNV, true, true, IR(160, 3), IR(37252, 27), IR(0, 0), IR(260, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpEmitMeshTasksEXT, false, false, IR(577, 4), IR(37279, 17), IR(0, 0), IR(53, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSetMeshOutputsEXT, false, false, IR(36, 2), IR(37296, 18), IR(0, 0), IR(53, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpGroupNonUniformPartitionNV, true, true, IR(160, 3), IR(37314, 27), IR(0, 0), IR(186, 1), IR(75, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpWritePackedPrimitiveIndices4x8NV, false, false, IR(36, 2), IR(37341, 33), IR(0, 0), IR(50, 1), IR(18, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFetchMicroTriangleVertexPositionNV, true, true, IR(325, 7), IR(37374, 35), IR(0, 0), IR(261, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFetchMicroTriangleVertexBarycentricNV, true, true, IR(325, 7), IR(37409, 38), IR(0, 0), IR(261, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorLoadNV, true, true, IR(581, 5), IR(37447, 24), IR(0, 0), IR(258, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeVectorStoreNV, false, false, IR(586, 4), IR(37471, 25), IR(0, 0), IR(258, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpHitObjectRecordFromQueryEXT, false, false, IR(296, 4), IR(37496, 28), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissEXT, false, false, IR(506, 7), IR(37524, 23), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissMotionEXT, false, false, IR(471, 8), IR(37547, 29), IR(0, 0), IR(262, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetIntersectionTriangleVertexPositionsEXT, true, true, IR(160, 3), IR(37576, 51), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayFlagsEXT, true, true, IR(160, 3), IR(37627, 24), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectSetShaderBindingTableRecordIndexEXT, false, false, IR(36, 2), IR(37651, 45), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectReorderExecuteShaderEXT, false, false, IR(590, 4), IR(37696, 33), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceReorderExecuteEXT, false, false, IR(594, 14), IR(37729, 32), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceMotionReorderExecuteEXT, false, false, IR(608, 15), IR(37761, 38), IR(0, 0), IR(262, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeHitObjectEXT, true, false, IR(68, 1), IR(37799, 17), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpReorderThreadWithHintEXT, false, false, IR(36, 2), IR(37816, 25), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHitObjectEXT, false, false, IR(531, 3), IR(37841, 30), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayEXT, false, false, IR(513, 12), IR(37871, 21), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayMotionEXT, false, false, IR(493, 13), IR(37892, 27), IR(0, 0), IR(262, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordEmptyEXT, false, false, IR(10, 1), IR(37919, 24), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectExecuteShaderEXT, false, false, IR(36, 2), IR(37943, 26), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetCurrentTimeEXT, true, true, IR(160, 3), IR(37969, 27), IR(0, 0), IR(262, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetAttributesEXT, false, false, IR(36, 2), IR(37996, 26), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetHitKindEXT, true, true, IR(160, 3), IR(38022, 23), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetPrimitiveIndexEXT, true, true, IR(160, 3), IR(38045, 30), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetGeometryIndexEXT, true, true, IR(160, 3), IR(38075, 29), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceIdEXT, true, true, IR(160, 3), IR(38104, 26), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceCustomIndexEXT, true, true, IR(160, 3), IR(38130, 35), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayOriginEXT, true, true, IR(160, 3), IR(38165, 31), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayDirectionEXT, true, true, IR(160, 3), IR(38196, 34), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayDirectionEXT, true, true, IR(160, 3), IR(38230, 33), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayOriginEXT, true, true, IR(160, 3), IR(38263, 30), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectToWorldEXT, true, true, IR(160, 3), IR(38293, 29), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldToObjectEXT, true, true, IR(160, 3), IR(38322, 29), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMaxEXT, true, true, IR(160, 3), IR(38351, 23), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReportIntersectionKHR, true, true, IR(172, 4), IR(38374, 22), IR(174, 1), IR(54, 2), IR(24, 2), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIgnoreIntersectionNV, false, false, IR(0, 0), IR(38417, 21), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTerminateRayNV, false, false, IR(0, 0), IR(38438, 15), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceNV, false, false, IR(426, 11), IR(38453, 8), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceMotionNV, false, false, IR(513, 12), IR(38461, 14), IR(0, 0), IR(57, 1), IR(27, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceRayMotionNV, false, false, IR(513, 12), IR(38475, 17), IR(0, 0), IR(57, 1), IR(27, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTriangleVertexPositionsKHR, true, true, IR(172, 4), IR(38492, 50), IR(0, 0), IR(264, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeAccelerationStructureKHR, true, false, IR(68, 1), IR(38542, 29), IR(175, 1), IR(265, 4), IR(195, 4), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpExecuteCallableNV, false, false, IR(36, 2), IR(38599, 18), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionClusterIdNV, true, true, IR(172, 4), IR(38617, 35), IR(176, 1), IR(64, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetClusterIdNV, true, true, IR(160, 3), IR(38675, 24), IR(0, 0), IR(64, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMinEXT, true, true, IR(160, 3), IR(38699, 23), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderBindingTableRecordIndexEXT, true, true, IR(160, 3), IR(38722, 45), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderRecordBufferHandleEXT, true, true, IR(160, 3), IR(38767, 40), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsEmptyEXT, true, true, IR(160, 3), IR(38807, 20), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsHitEXT, true, true, IR(160, 3), IR(38827, 18), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsMissEXT, true, true, IR(160, 3), IR(38845, 19), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeCooperativeMatrixNV, true, false, IR(623, 5), IR(38864, 24), IR(0, 0), IR(269, 1), IR(79, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeMatrixLoadNV, true, true, IR(628, 6), IR(38888, 24), IR(0, 0), IR(269, 1), IR(79, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixStoreNV, false, false, IR(634, 5), IR(38912, 25), IR(0, 0), IR(269, 1), IR(79, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixMulAddNV, true, true, IR(130, 5), IR(38937, 26), IR(0, 0), IR(269, 1), IR(79, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixLengthNV, true, true, IR(160, 3), IR(38963, 26), IR(0, 0), IR(269, 1), IR(79, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpBeginInvocationInterlockEXT, false, false, IR(0, 0), IR(38989, 28), IR(0, 0), IR(270, 3), IR(80, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpEndInvocationInterlockEXT, false, false, IR(0, 0), IR(39017, 26), IR(0, 0), IR(270, 3), IR(80, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixReduceNV, true, true, IR(639, 5), IR(39086, 26), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpCooperativeMatrixLoadTensorNV, true, true, IR(644, 7), IR(39187, 30), IR(0, 0), IR(203, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixStoreTensorNV, false, false, IR(651, 5), IR(39217, 31), IR(0, 0), IR(203, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixPerElementOpNV, true, true, IR(151, 5), IR(39248, 32), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpTypeTensorLayoutNV, true, false, IR(89, 3), IR(39280, 19), IR(0, 0), IR(275, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeTensorViewNV, true, false, IR(656, 4), IR(39299, 17), IR(0, 0), IR(275, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCreateTensorLayoutNV, true, true, IR(39, 2), IR(39316, 21), IR(0, 0), IR(275, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetDimensionNV, true, true, IR(122, 4), IR(39337, 27), IR(0, 0), IR(275, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetStrideNV, true, true, IR(122, 4), IR(39364, 24), IR(0, 0), IR(275, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSliceNV, true, true, IR(122, 4), IR(39388, 20), IR(0, 0), IR(275, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetClampValueNV, true, true, IR(172, 4), IR(39408, 28), IR(0, 0), IR(275, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCreateTensorViewNV, true, true, IR(39, 2), IR(39436, 19), IR(0, 0), IR(275, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetDimensionNV, true, true, IR(122, 4), IR(39455, 25), IR(0, 0), IR(275, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetStrideNV, true, true, IR(122, 4), IR(39480, 22), IR(0, 0), IR(275, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpDemoteToHelperInvocation, false, false, IR(0, 0), IR(12309, 25), IR(45, 1), IR(276, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpIsHelperInvocationEXT, true, true, IR(39, 2), IR(39502, 22), IR(0, 0), IR(276, 1), IR(81, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetClipNV, true, true, IR(325, 7), IR(39524, 20), IR(0, 0), IR(275, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetBlockSizeNV, true, true, IR(122, 4), IR(39544, 27), IR(0, 0), IR(275, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixTransposeNV, true, true, IR(160, 3), IR(39571, 29), IR(0, 0), IR(260, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToImageNV, true, true, IR(160, 3), IR(39600, 18), IR(0, 0), IR(129, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToSamplerNV, true, true, IR(160, 3), IR(39618, 20), IR(0, 0), IR(129, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertImageToUNV, true, true, IR(160, 3), IR(39638, 18), IR(0, 0), IR(129, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertSamplerToUNV, true, true, IR(160, 3), IR(39656, 20), IR(0, 0), IR(129, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToSampledImageNV, true, true, IR(160, 3), IR(39676, 25), IR(0, 0), IR(129, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertSampledImageToUNV, true, true, IR(160, 3), IR(39701, 25), IR(0, 0), IR(129, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSamplerImageAddressingModeNV, false, false, IR(0, 1), IR(39726, 29), IR(0, 0), IR(129, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRawAccessChainNV, true, true, IR(660, 7), IR(39807, 17), IR(0, 0), IR(192, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpRayQueryGetIntersectionSpherePositionNV, true, true, IR(172, 4), IR(39824, 40), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionSphereRadiusNV, true, true, IR(172, 4), IR(39864, 38), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSPositionsNV, true, true, IR(172, 4), IR(39902, 38), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSRadiiNV, true, true, IR(172, 4), IR(39940, 34), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSHitValueNV, true, true, IR(172, 4), IR(39974, 37), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetSpherePositionNV, true, true, IR(160, 3), IR(40011, 29), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetSphereRadiusNV, true, true, IR(160, 3), IR(40040, 27), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetLSSPositionsNV, true, true, IR(160, 3), IR(40067, 27), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetLSSRadiiNV, true, true, IR(160, 3), IR(40094, 23), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsSphereHitNV, true, true, IR(160, 3), IR(40117, 23), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsLSSHitNV, true, true, IR(160, 3), IR(40140, 20), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryIsSphereHitNV, true, true, IR(172, 4), IR(40160, 22), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryIsLSSHitNV, true, true, IR(172, 4), IR(40182, 19), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSubgroupShuffleINTEL, true, true, IR(172, 4), IR(12821, 21), IR(0, 0), IR(277, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleDownINTEL, true, true, IR(130, 5), IR(40201, 25), IR(0, 0), IR(277, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleUpINTEL, true, true, IR(130, 5), IR(40226, 23), IR(0, 0), IR(277, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleXorINTEL, true, true, IR(172, 4), IR(40249, 24), IR(0, 0), IR(277, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupBlockReadINTEL, true, true, IR(160, 3), IR(40273, 23), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupBlockWriteINTEL, false, false, IR(36, 2), IR(40296, 24), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageBlockReadINTEL, true, true, IR(172, 4), IR(40320, 28), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageBlockWriteINTEL, false, false, IR(33, 3), IR(40348, 29), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageMediaBlockReadINTEL, true, true, IR(215, 6), IR(40377, 33), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageMediaBlockWriteINTEL, false, false, IR(667, 5), IR(40410, 34), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpUCountLeadingZerosINTEL, true, true, IR(160, 3), IR(40444, 24), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUCountTrailingZerosINTEL, true, true, IR(160, 3), IR(40468, 25), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAbsISubINTEL, true, true, IR(172, 4), IR(40493, 13), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAbsUSubINTEL, true, true, IR(172, 4), IR(40506, 13), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAddSatINTEL, true, true, IR(172, 4), IR(40519, 13), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAddSatINTEL, true, true, IR(172, 4), IR(40532, 13), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAverageINTEL, true, true, IR(172, 4), IR(40545, 14), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAverageINTEL, true, true, IR(172, 4), IR(40559, 14), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAverageRoundedINTEL, true, true, IR(172, 4), IR(40573, 21), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAverageRoundedINTEL, true, true, IR(172, 4), IR(40594, 21), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpISubSatINTEL, true, true, IR(172, 4), IR(40615, 13), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUSubSatINTEL, true, true, IR(172, 4), IR(40628, 13), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIMul32x16INTEL, true, true, IR(172, 4), IR(40641, 15), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUMul32x16INTEL, true, true, IR(172, 4), IR(40656, 15), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConstantFunctionPointerINTEL, true, true, IR(160, 3), IR(40671, 29), IR(0, 0), IR(201, 1), IR(98, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFunctionPointerCallINTEL, true, true, IR(107, 3), IR(40700, 25), IR(0, 0), IR(201, 1), IR(98, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmTargetINTEL, true, false, IR(50, 2), IR(40725, 15), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmINTEL, true, true, IR(672, 6), IR(13039, 9), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmCallINTEL, true, true, IR(122, 4), IR(40740, 13), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAtomicFMinEXT, true, true, IR(235, 6), IR(40753, 14), IR(0, 0), IR(282, 4), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicFMaxEXT, true, true, IR(235, 6), IR(40767, 14), IR(0, 0), IR(282, 4), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAssumeTrueKHR, false, false, IR(10, 1), IR(40781, 14), IR(0, 0), IR(286, 1), IR(102, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpExpectKHR, true, true, IR(172, 4), IR(40795, 10), IR(0, 0), IR(286, 1), IR(102, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpDecorateString, false, false, IR(163, 2), IR(40805, 15), IR(177, 1), IR(1, 0), IR(199, 2), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpMemberDecorateString, false, false, IR(165, 3), IR(40841, 21), IR(178, 1), IR(1, 0), IR(199, 2), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpVmeImageINTEL, true, true, IR(172, 4), IR(40889, 14), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeVmeImageINTEL, true, false, IR(87, 2), IR(40903, 18), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImePayloadINTEL, true, false, IR(68, 1), IR(40921, 23), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcRefPayloadINTEL, true, false, IR(68, 1), IR(40944, 23), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcSicPayloadINTEL, true, false, IR(68, 1), IR(40967, 23), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcMcePayloadINTEL, true, false, IR(68, 1), IR(40990, 23), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcMceResultINTEL, true, false, IR(68, 1), IR(41013, 22), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultINTEL, true, false, IR(68, 1), IR(41035, 22), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultSingleReferenceStreamoutINTEL, true, false, IR(68, 1), IR(41057, 46), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultDualReferenceStreamoutINTEL, true, false, IR(68, 1), IR(41103, 44), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeSingleReferenceStreaminINTEL, true, false, IR(68, 1), IR(41147, 39), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeDualReferenceStreaminINTEL, true, false, IR(68, 1), IR(41186, 37), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcRefResultINTEL, true, false, IR(68, 1), IR(41223, 22), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcSicResultINTEL, true, false, IR(68, 1), IR(41245, 22), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL, true, true, IR(172, 4), IR(41267, 60), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL, true, true, IR(172, 4), IR(41327, 53), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterShapePenaltyINTEL, true, true, IR(172, 4), IR(41380, 47), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterShapePenaltyINTEL, true, true, IR(172, 4), IR(41427, 40), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL, true, true, IR(172, 4), IR(41467, 51), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterDirectionPenaltyINTEL, true, true, IR(172, 4), IR(41518, 44), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL, true, true, IR(172, 4), IR(41562, 51), IR(0, 0), IR(288, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL, true, true, IR(172, 4), IR(41613, 56), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL, true, true, IR(39, 2), IR(41669, 50), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL, true, true, IR(39, 2), IR(41719, 52), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL, true, true, IR(39, 2), IR(41771, 49), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetMotionVectorCostFunctionINTEL, true, true, IR(215, 6), IR(41820, 47), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL, true, true, IR(172, 4), IR(41867, 50), IR(0, 0), IR(288, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL, true, true, IR(39, 2), IR(41917, 51), IR(0, 0), IR(288, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL, true, true, IR(39, 2), IR(41968, 56), IR(0, 0), IR(290, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetAcOnlyHaarINTEL, true, true, IR(160, 3), IR(42024, 33), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL, true, true, IR(172, 4), IR(42057, 52), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL, true, true, IR(172, 4), IR(42109, 61), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL, true, true, IR(130, 5), IR(42170, 61), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToImePayloadINTEL, true, true, IR(160, 3), IR(42231, 39), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToImeResultINTEL, true, true, IR(160, 3), IR(42270, 38), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToRefPayloadINTEL, true, true, IR(160, 3), IR(42308, 39), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToRefResultINTEL, true, true, IR(160, 3), IR(42347, 38), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToSicPayloadINTEL, true, true, IR(160, 3), IR(42385, 39), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToSicResultINTEL, true, true, IR(160, 3), IR(42424, 38), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetMotionVectorsINTEL, true, true, IR(160, 3), IR(42462, 36), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterDistortionsINTEL, true, true, IR(160, 3), IR(42498, 39), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetBestInterDistortionsINTEL, true, true, IR(160, 3), IR(42537, 43), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMajorShapeINTEL, true, true, IR(160, 3), IR(42580, 38), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMinorShapeINTEL, true, true, IR(160, 3), IR(42618, 38), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterDirectionsINTEL, true, true, IR(160, 3), IR(42656, 38), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMotionVectorCountINTEL, true, true, IR(160, 3), IR(42694, 45), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterReferenceIdsINTEL, true, true, IR(160, 3), IR(42739, 40), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL, true, true, IR(130, 5), IR(42779, 62), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeInitializeINTEL, true, true, IR(130, 5), IR(42841, 30), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetSingleReferenceINTEL, true, true, IR(130, 5), IR(42871, 38), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetDualReferenceINTEL, true, true, IR(215, 6), IR(42909, 36), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeRefWindowSizeINTEL, true, true, IR(172, 4), IR(42945, 33), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeAdjustRefOffsetINTEL, true, true, IR(215, 6), IR(42978, 35), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(43013, 39), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetMaxMotionVectorCountINTEL, true, true, IR(172, 4), IR(43052, 43), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetUnidirectionalMixDisableINTEL, true, true, IR(160, 3), IR(43095, 47), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetEarlySearchTerminationThresholdINTEL, true, true, IR(172, 4), IR(43142, 54), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetWeightedSadINTEL, true, true, IR(172, 4), IR(43196, 34), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(43230, 47), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(43277, 45), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL, true, true, IR(215, 6), IR(43322, 55), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL, true, true, IR(325, 7), IR(43377, 53), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL, true, true, IR(130, 5), IR(43430, 56), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL, true, true, IR(215, 6), IR(43486, 54), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL, true, true, IR(215, 6), IR(43540, 58), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL, true, true, IR(325, 7), IR(43598, 56), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeConvertToMceResultINTEL, true, true, IR(160, 3), IR(43654, 38), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetSingleReferenceStreaminINTEL, true, true, IR(160, 3), IR(43692, 46), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetDualReferenceStreaminINTEL, true, true, IR(160, 3), IR(43738, 44), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeStripSingleReferenceStreamoutINTEL, true, true, IR(160, 3), IR(43782, 49), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeStripDualReferenceStreamoutINTEL, true, true, IR(160, 3), IR(43831, 47), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL, true, true, IR(172, 4), IR(43878, 70), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL, true, true, IR(172, 4), IR(43948, 68), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL, true, true, IR(172, 4), IR(44016, 69), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL, true, true, IR(130, 5), IR(44085, 68), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL, true, true, IR(130, 5), IR(44153, 66), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL, true, true, IR(130, 5), IR(44219, 67), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetBorderReachedINTEL, true, true, IR(172, 4), IR(44286, 36), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetTruncatedSearchIndicationINTEL, true, true, IR(160, 3), IR(44322, 48), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL, true, true, IR(160, 3), IR(44370, 59), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL, true, true, IR(160, 3), IR(44429, 58), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL, true, true, IR(160, 3), IR(44487, 56), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcFmeInitializeINTEL, true, true, IR(678, 9), IR(44543, 30), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcBmeInitializeINTEL, true, true, IR(687, 10), IR(44573, 30), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(44603, 39), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefSetBidirectionalMixDisableINTEL, true, true, IR(160, 3), IR(44642, 46), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefSetBilinearFilterEnableINTEL, true, true, IR(160, 3), IR(44688, 43), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(44731, 47), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(44778, 45), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithMultiReferenceINTEL, true, true, IR(130, 5), IR(44823, 46), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL, true, true, IR(215, 6), IR(44869, 56), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefConvertToMceResultINTEL, true, true, IR(160, 3), IR(44925, 38), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicInitializeINTEL, true, true, IR(160, 3), IR(44963, 30), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureSkcINTEL, true, true, IR(288, 8), IR(44993, 32), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureIpeLumaINTEL, true, true, IR(687, 10), IR(45025, 36), IR(0, 0), IR(288, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureIpeLumaChromaINTEL, true, true, IR(697, 13), IR(45061, 42), IR(0, 0), IR(290, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetMotionVectorMaskINTEL, true, true, IR(172, 4), IR(45103, 39), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(45142, 39), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraLumaShapePenaltyINTEL, true, true, IR(172, 4), IR(45181, 44), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraLumaModeCostFunctionINTEL, true, true, IR(215, 6), IR(45225, 48), IR(0, 0), IR(288, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraChromaModeCostFunctionINTEL, true, true, IR(172, 4), IR(45273, 50), IR(0, 0), IR(290, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetBilinearFilterEnableINTEL, true, true, IR(160, 3), IR(45323, 43), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetSkcForwardTransformEnableINTEL, true, true, IR(172, 4), IR(45366, 48), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetBlockBasedRawSkipSadINTEL, true, true, IR(172, 4), IR(45414, 43), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateIpeINTEL, true, true, IR(172, 4), IR(45457, 31), IR(0, 0), IR(288, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(45488, 47), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(45535, 45), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithMultiReferenceINTEL, true, true, IR(130, 5), IR(45580, 46), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL, true, true, IR(215, 6), IR(45626, 56), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConvertToMceResultINTEL, true, true, IR(160, 3), IR(45682, 38), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetIpeLumaShapeINTEL, true, true, IR(160, 3), IR(45720, 35), IR(0, 0), IR(288, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetBestIpeLumaDistortionINTEL, true, true, IR(160, 3), IR(45755, 44), IR(0, 0), IR(288, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetBestIpeChromaDistortionINTEL, true, true, IR(160, 3), IR(45799, 46), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedIpeLumaModesINTEL, true, true, IR(160, 3), IR(45845, 41), IR(0, 0), IR(288, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetIpeChromaModeINTEL, true, true, IR(160, 3), IR(45886, 36), IR(0, 0), IR(290, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL, true, true, IR(160, 3), IR(45922, 50), IR(0, 0), IR(288, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL, true, true, IR(160, 3), IR(45972, 48), IR(0, 0), IR(288, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetInterRawSadsINTEL, true, true, IR(160, 3), IR(46020, 35), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpVariableLengthArrayINTEL, true, true, IR(160, 3), IR(13277, 25), IR(0, 0), IR(292, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpSaveMemoryINTEL, true, true, IR(39, 2), IR(46055, 16), IR(0, 0), IR(292, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpRestoreMemoryINTEL, false, false, IR(10, 1), IR(46071, 19), IR(0, 0), IR(292, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpArbitraryFloatSinCosPiALTERA, true, true, IR(710, 8), IR(46090, 29), IR(179, 1), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastALTERA, true, true, IR(710, 8), IR(46147, 25), IR(180, 1), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastFromIntALTERA, true, true, IR(710, 8), IR(46196, 32), IR(181, 1), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastToIntALTERA, true, true, IR(710, 8), IR(46259, 30), IR(182, 1), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatAddALTERA, true, true, IR(718, 10), IR(46318, 24), IR(183, 1), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSubALTERA, true, true, IR(718, 10), IR(46365, 24), IR(184, 1), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatMulALTERA, true, true, IR(718, 10), IR(46412, 24), IR(185, 1), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatDivALTERA, true, true, IR(718, 10), IR(46459, 24), IR(186, 1), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatGTALTERA, true, true, IR(728, 6), IR(46506, 23), IR(187, 1), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatGEALTERA, true, true, IR(728, 6), IR(46551, 23), IR(188, 1), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLTALTERA, true, true, IR(728, 6), IR(46596, 23), IR(189, 1), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLEALTERA, true, true, IR(728, 6), IR(46641, 23), IR(190, 1), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatEQALTERA, true, true, IR(728, 6), IR(46686, 23), IR(191, 1), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatRecipALTERA, true, true, IR(710, 8), IR(46731, 26), IR(192, 1), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatRSqrtALTERA, true, true, IR(710, 8), IR(46782, 26), IR(193, 1), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCbrtALTERA, true, true, IR(710, 8), IR(46833, 25), IR(194, 1), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatHypotALTERA, true, true, IR(718, 10), IR(46882, 26), IR(195, 1), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSqrtALTERA, true, true, IR(710, 8), IR(46933, 25), IR(196, 1), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLogINTEL, true, true, IR(710, 8), IR(46982, 23), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog2INTEL, true, true, IR(710, 8), IR(47005, 24), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog10INTEL, true, true, IR(710, 8), IR(47029, 25), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog1pINTEL, true, true, IR(710, 8), IR(47054, 25), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExpINTEL, true, true, IR(710, 8), IR(47079, 23), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExp2INTEL, true, true, IR(710, 8), IR(47102, 24), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExp10INTEL, true, true, IR(710, 8), IR(47126, 25), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExpm1INTEL, true, true, IR(710, 8), IR(47151, 25), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinINTEL, true, true, IR(710, 8), IR(47176, 23), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCosINTEL, true, true, IR(710, 8), IR(47199, 23), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinCosINTEL, true, true, IR(710, 8), IR(47222, 26), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinPiINTEL, true, true, IR(710, 8), IR(47248, 25), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCosPiINTEL, true, true, IR(710, 8), IR(47273, 25), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatASinINTEL, true, true, IR(710, 8), IR(47298, 24), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatASinPiINTEL, true, true, IR(710, 8), IR(47322, 26), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatACosINTEL, true, true, IR(710, 8), IR(47348, 24), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatACosPiINTEL, true, true, IR(710, 8), IR(47372, 26), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATanINTEL, true, true, IR(710, 8), IR(47398, 24), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATanPiINTEL, true, true, IR(710, 8), IR(47422, 26), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATan2INTEL, true, true, IR(718, 10), IR(47448, 25), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowINTEL, true, true, IR(718, 10), IR(47473, 23), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowRINTEL, true, true, IR(718, 10), IR(47496, 24), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowNINTEL, true, true, IR(718, 10), IR(47520, 24), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpLoopControlINTEL, false, false, IR(18, 1), IR(47544, 17), IR(0, 0), IR(294, 1), IR(112, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAliasDomainDeclINTEL, true, false, IR(734, 2), IR(47561, 21), IR(0, 0), IR(138, 1), IR(124, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAliasScopeDeclINTEL, true, false, IR(736, 3), IR(47582, 20), IR(0, 0), IR(138, 1), IR(124, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAliasScopeListDeclINTEL, true, false, IR(92, 2), IR(47602, 24), IR(0, 0), IR(138, 1), IR(124, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSqrtALTERA, true, true, IR(710, 8), IR(47626, 16), IR(197, 1), IR(191, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedRecipALTERA, true, true, IR(710, 8), IR(47657, 17), IR(198, 1), IR(191, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedRsqrtALTERA, true, true, IR(710, 8), IR(47690, 17), IR(199, 1), IR(191, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinALTERA, true, true, IR(710, 8), IR(47723, 15), IR(200, 1), IR(191, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedCosALTERA, true, true, IR(710, 8), IR(47752, 15), IR(201, 1), IR(191, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinCosALTERA, true, true, IR(710, 8), IR(47781, 18), IR(202, 1), IR(191, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinPiALTERA, true, true, IR(710, 8), IR(47816, 17), IR(203, 1), IR(191, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedCosPiALTERA, true, true, IR(710, 8), IR(47849, 17), IR(204, 1), IR(191, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinCosPiALTERA, true, true, IR(710, 8), IR(47882, 20), IR(205, 1), IR(191, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedLogALTERA, true, true, IR(710, 8), IR(47921, 15), IR(206, 1), IR(191, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedExpALTERA, true, true, IR(710, 8), IR(47950, 15), IR(207, 1), IR(191, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpPtrCastToCrossWorkgroupALTERA, true, true, IR(160, 3), IR(47979, 30), IR(208, 1), IR(202, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpCrossWorkgroupCastToPtrALTERA, true, true, IR(160, 3), IR(48038, 30), IR(209, 1), IR(202, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpReadPipeBlockingALTERA, true, true, IR(172, 4), IR(48097, 23), IR(210, 1), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpWritePipeBlockingALTERA, true, true, IR(172, 4), IR(48142, 24), IR(211, 1), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFPGARegALTERA, true, true, IR(160, 3), IR(14235, 14), IR(61, 1), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpRayQueryGetRayTMinKHR, true, true, IR(160, 3), IR(48189, 22), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetRayFlagsKHR, true, true, IR(160, 3), IR(48211, 23), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTKHR, true, true, IR(172, 4), IR(48234, 28), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceCustomIndexKHR, true, true, IR(172, 4), IR(48262, 46), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceIdKHR, true, true, IR(172, 4), IR(48308, 37), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR, true, true, IR(172, 4), IR(48345, 65), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionGeometryIndexKHR, true, true, IR(172, 4), IR(48410, 40), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionPrimitiveIndexKHR, true, true, IR(172, 4), IR(48450, 41), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionBarycentricsKHR, true, true, IR(172, 4), IR(48491, 39), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionFrontFaceKHR, true, true, IR(172, 4), IR(48530, 36), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionCandidateAABBOpaqueKHR, true, true, IR(160, 3), IR(48566, 46), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectRayDirectionKHR, true, true, IR(172, 4), IR(48612, 45), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectRayOriginKHR, true, true, IR(172, 4), IR(48657, 42), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetWorldRayDirectionKHR, true, true, IR(160, 3), IR(48699, 32), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetWorldRayOriginKHR, true, true, IR(160, 3), IR(48731, 29), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectToWorldKHR, true, true, IR(172, 4), IR(48760, 40), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionWorldToObjectKHR, true, true, IR(172, 4), IR(48800, 40), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAtomicFAddEXT, true, true, IR(235, 6), IR(48840, 14), IR(0, 0), IR(297, 4), IR(148, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpTypeBufferSurfaceINTEL, true, false, IR(100, 2), IR(48854, 23), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeStructContinuedINTEL, false, false, IR(739, 1), IR(48877, 25), IR(0, 0), IR(301, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantCompositeContinuedINTEL, false, false, IR(739, 1), IR(48902, 32), IR(0, 0), IR(301, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCompositeContinuedINTEL, false, false, IR(739, 1), IR(48934, 36), IR(0, 0), IR(301, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpCompositeConstructContinuedINTEL, true, true, IR(107, 3), IR(48970, 33), IR(0, 0), IR(301, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpConvertFToBF16INTEL, true, true, IR(160, 3), IR(49003, 20), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertBF16ToFINTEL, true, true, IR(160, 3), IR(49023, 20), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpControlBarrierArriveINTEL, false, false, IR(221, 3), IR(49043, 26), IR(0, 0), IR(303, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpControlBarrierWaitINTEL, false, false, IR(221, 3), IR(49069, 24), IR(0, 0), IR(303, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpArithmeticFenceEXT, true, true, IR(160, 3), IR(14688, 19), IR(0, 0), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpTaskSequenceCreateALTERA, true, true, IR(740, 7), IR(49093, 25), IR(212, 1), IR(305, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTaskSequenceAsyncALTERA, false, false, IR(168, 2), IR(49142, 24), IR(213, 1), IR(305, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTaskSequenceGetALTERA, true, true, IR(160, 3), IR(49189, 22), IR(214, 1), IR(305, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTaskSequenceReleaseALTERA, false, false, IR(10, 1), IR(49232, 26), IR(215, 1), IR(305, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeTaskSequenceALTERA, true, false, IR(68, 1), IR(49283, 23), IR(216, 1), IR(305, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupBlockPrefetchINTEL, false, false, IR(139, 3), IR(49328, 27), IR(0, 0), IR(306, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadINTEL, false, false, IR(747, 10), IR(49355, 25), IR(0, 0), IR(108, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadTransformINTEL, false, false, IR(747, 10), IR(49380, 34), IR(0, 0), IR(307, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadTransposeINTEL, false, false, IR(747, 10), IR(49414, 34), IR(0, 0), IR(308, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockPrefetchINTEL, false, false, IR(757, 9), IR(49448, 29), IR(0, 0), IR(108, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockStoreINTEL, false, false, IR(747, 10), IR(49477, 26), IR(0, 0), IR(108, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupMatrixMultiplyAccumulateINTEL, true, true, IR(766, 7), IR(15165, 38), IR(0, 0), IR(309, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpBitwiseFunctionINTEL, true, true, IR(215, 6), IR(49565, 21), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpUntypedVariableLengthArrayINTEL, true, true, IR(172, 4), IR(15231, 32), IR(0, 0), IR(311, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpConditionalExtensionINTEL, false, false, IR(45, 2), IR(49586, 26), IR(0, 0), IR(111, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpConditionalEntryPointINTEL, false, false, IR(773, 5), IR(49612, 27), IR(0, 0), IR(111, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpConditionalCapabilityINTEL, false, false, IR(778, 2), IR(49639, 27), IR(0, 0), IR(111, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpSpecConstantTargetINTEL, true, true, IR(780, 4), IR(49666, 24), IR(0, 0), IR(312, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantArchitectureINTEL, true, true, IR(784, 6), IR(49690, 30), IR(0, 0), IR(312, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCapabilitiesINTEL, true, true, IR(790, 3), IR(49757, 30), IR(0, 0), IR(312, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConditionalCopyObjectINTEL, true, true, IR(107, 3), IR(49787, 27), IR(0, 0), IR(111, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpGroupIMulKHR, true, true, IR(283, 5), IR(49814, 13), IR(0, 0), IR(313, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMulKHR, true, true, IR(283, 5), IR(49827, 13), IR(0, 0), IR(313, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseAndKHR, true, true, IR(283, 5), IR(49840, 19), IR(0, 0), IR(313, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseOrKHR, true, true, IR(283, 5), IR(49859, 18), IR(0, 0), IR(313, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseXorKHR, true, true, IR(283, 5), IR(49877, 19), IR(0, 0), IR(313, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalAndKHR, true, true, IR(283, 5), IR(49896, 19), IR(0, 0), IR(313, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalOrKHR, true, true, IR(283, 5), IR(49915, 18), IR(0, 0), IR(313, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalXorKHR, true, true, IR(283, 5), IR(49933, 19), IR(0, 0), IR(313, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpRoundFToTF32INTEL, true, true, IR(160, 3), IR(49952, 18), IR(0, 0), IR(314, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpMaskedGatherINTEL, true, true, IR(793, 6), IR(49970, 18), IR(0, 0), IR(315, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpMaskedScatterINTEL, false, false, IR(799, 4), IR(49988, 19), IR(0, 0), IR(315, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpConvertHandleToImageINTEL, true, true, IR(160, 3), IR(50007, 26), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertHandleToSamplerINTEL, true, true, IR(160, 3), IR(50033, 28), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertHandleToSampledImageINTEL, true, true, IR(160, 3), IR(50061, 33), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
}};

// Opcode strings (without the 'Op' prefix) and opcode values, ordered by name.
// The fields in order are:
//   name, either the primary name or an alias, indexing into kStrings
//   index into kInstructionDesc
static const std::array<NameIndex, 910> kInstructionNames{{
  {IR(40493, 13), 590}, // 0 AbsISubINTEL
  {IR(40506, 13), 591}, // 1 AbsUSubINTEL
  {IR(29247, 12), 58}, // 2 AccessChain
  {IR(47561, 21), 776}, // 3 AliasDomainDeclINTEL
  {IR(47582, 20), 777}, // 4 AliasScopeDeclINTEL
  {IR(47602, 24), 778}, // 5 AliasScopeListDeclINTEL
  {IR(30544, 4), 143}, // 6 All
  {IR(35923, 25), 426}, // 7 AllocateNodePayloadsAMDX
  {IR(30540, 4), 142}, // 8 Any
  {IR(47348, 24), 767}, // 9 ArbitraryFloatACosINTEL
  {IR(47372, 26), 768}, // 10 ArbitraryFloatACosPiINTEL
  {IR(47298, 24), 765}, // 11 ArbitraryFloatASinINTEL
  {IR(47322, 26), 766}, // 12 ArbitraryFloatASinPiINTEL
  {IR(47448, 25), 771}, // 13 ArbitraryFloatATan2INTEL
  {IR(47398, 24), 769}, // 14 ArbitraryFloatATanINTEL
  {IR(47422, 26), 770}, // 15 ArbitraryFloatATanPiINTEL
  {IR(46318, 24), 738}, // 16 ArbitraryFloatAddALTERA
  {IR(46342, 23), 738}, // 17 ArbitraryFloatAddINTEL
  {IR(46147, 25), 735}, // 18 ArbitraryFloatCastALTERA
  {IR(46196, 32), 736}, // 19 ArbitraryFloatCastFromIntALTERA
  {IR(46228, 31), 736}, // 20 ArbitraryFloatCastFromIntINTEL
  {IR(46172, 24), 735}, // 21 ArbitraryFloatCastINTEL
  {IR(46259, 30), 737}, // 22 ArbitraryFloatCastToIntALTERA
  {IR(46289, 29), 737}, // 23 ArbitraryFloatCastToIntINTEL
  {IR(46833, 25), 749}, // 24 ArbitraryFloatCbrtALTERA
  {IR(46858, 24), 749}, // 25 ArbitraryFloatCbrtINTEL
  {IR(47199, 23), 761}, // 26 ArbitraryFloatCosINTEL
  {IR(47273, 25), 764}, // 27 ArbitraryFloatCosPiINTEL
  {IR(46459, 24), 741}, // 28 ArbitraryFloatDivALTERA
  {IR(46483, 23), 741}, // 29 ArbitraryFloatDivINTEL
  {IR(46686, 23), 746}, // 30 ArbitraryFloatEQALTERA
  {IR(46709, 22), 746}, // 31 ArbitraryFloatEQINTEL
  {IR(47126, 25), 758}, // 32 ArbitraryFloatExp10INTEL
  {IR(47102, 24), 757}, // 33 ArbitraryFloatExp2INTEL
  {IR(47079, 23), 756}, // 34 ArbitraryFloatExpINTEL
  {IR(47151, 25), 759}, // 35 ArbitraryFloatExpm1INTEL
  {IR(46551, 23), 743}, // 36 ArbitraryFloatGEALTERA
  {IR(46574, 22), 743}, // 37 ArbitraryFloatGEINTEL
  {IR(46506, 23), 742}, // 38 ArbitraryFloatGTALTERA
  {IR(46529, 22), 742}, // 39 ArbitraryFloatGTINTEL
  {IR(46882, 26), 750}, // 40 ArbitraryFloatHypotALTERA
  {IR(46908, 25), 750}, // 41 ArbitraryFloatHypotINTEL
  {IR(46641, 23), 745}, // 42 ArbitraryFloatLEALTERA
  {IR(46664, 22), 745}, // 43 ArbitraryFloatLEINTEL
  {IR(46596, 23), 744}, // 44 ArbitraryFloatLTALTERA
  {IR(46619, 22), 744}, // 45 ArbitraryFloatLTINTEL
  {IR(47029, 25), 754}, // 46 ArbitraryFloatLog10INTEL
  {IR(47054, 25), 755}, // 47 ArbitraryFloatLog1pINTEL
  {IR(47005, 24), 753}, // 48 ArbitraryFloatLog2INTEL
  {IR(46982, 23), 752}, // 49 ArbitraryFloatLogINTEL
  {IR(46412, 24), 740}, // 50 ArbitraryFloatMulALTERA
  {IR(46436, 23), 740}, // 51 ArbitraryFloatMulINTEL
  {IR(47473, 23), 772}, // 52 ArbitraryFloatPowINTEL
  {IR(47520, 24), 774}, // 53 ArbitraryFloatPowNINTEL
  {IR(47496, 24), 773}, // 54 ArbitraryFloatPowRINTEL
  {IR(46782, 26), 748}, // 55 ArbitraryFloatRSqrtALTERA
  {IR(46808, 25), 748}, // 56 ArbitraryFloatRSqrtINTEL
  {IR(46731, 26), 747}, // 57 ArbitraryFloatRecipALTERA
  {IR(46757, 25), 747}, // 58 ArbitraryFloatRecipINTEL
  {IR(47222, 26), 762}, // 59 ArbitraryFloatSinCosINTEL
  {IR(46090, 29), 734}, // 60 ArbitraryFloatSinCosPiALTERA
  {IR(46119, 28), 734}, // 61 ArbitraryFloatSinCosPiINTEL
  {IR(47176, 23), 760}, // 62 ArbitraryFloatSinINTEL
  {IR(47248, 25), 763}, // 63 ArbitraryFloatSinPiINTEL
  {IR(46933, 25), 751}, // 64 ArbitraryFloatSqrtALTERA
  {IR(46958, 24), 751}, // 65 ArbitraryFloatSqrtINTEL
  {IR(46365, 24), 739}, // 66 ArbitraryFloatSubALTERA
  {IR(46389, 23), 739}, // 67 ArbitraryFloatSubINTEL
  {IR(14688, 19), 822}, // 68 ArithmeticFenceEXT
  {IR(29294, 12), 61}, // 69 ArrayLength
  {IR(40740, 13), 606}, // 70 AsmCallINTEL
  {IR(13039, 9), 605}, // 71 AsmINTEL
  {IR(40725, 15), 604}, // 72 AsmTargetINTEL
  {IR(40781, 14), 609}, // 73 AssumeTrueKHR
  {IR(31566, 10), 220}, // 74 AtomicAnd
  {IR(31418, 22), 210}, // 75 AtomicCompareExchange
  {IR(31440, 26), 211}, // 76 AtomicCompareExchangeWeak
  {IR(31403, 15), 209}, // 77 AtomicExchange
  {IR(48840, 14), 812}, // 78 AtomicFAddEXT
  {IR(40767, 14), 608}, // 79 AtomicFMaxEXT
  {IR(40753, 14), 607}, // 80 AtomicFMinEXT
  {IR(32951, 16), 292}, // 81 AtomicFlagClear
  {IR(32930, 21), 291}, // 82 AtomicFlagTestAndSet
  {IR(31500, 11), 214}, // 83 AtomicIAdd
  {IR(31483, 17), 213}, // 84 AtomicIDecrement
  {IR(31466, 17), 212}, // 85 AtomicIIncrement
  {IR(31511, 11), 215}, // 86 AtomicISub
  {IR(31380, 11), 207}, // 87 AtomicLoad
  {IR(31576, 9), 221}, // 88 AtomicOr
  {IR(31544, 11), 218}, // 89 AtomicSMax
  {IR(31522, 11), 216}, // 90 AtomicSMin
  {IR(31391, 12), 208}, // 91 AtomicStore
  {IR(31555, 11), 219}, // 92 AtomicUMax
  {IR(31533, 11), 217}, // 93 AtomicUMin
  {IR(31585, 10), 222}, // 94 AtomicXor
  {IR(38989, 28), 536}, // 95 BeginInvocationInterlockEXT
  {IR(35477, 17), 407}, // 96 BitCastArrayQCOM
  {IR(31164, 9), 191}, // 97 BitCount
  {IR(31104, 15), 187}, // 98 BitFieldInsert
  {IR(31119, 17), 188}, // 99 BitFieldSExtract
  {IR(31136, 17), 189}, // 100 BitFieldUExtract
  {IR(31153, 11), 190}, // 101 BitReverse
  {IR(30292, 8), 114}, // 102 Bitcast
  {IR(31089, 11), 185}, // 103 BitwiseAnd
  {IR(49565, 21), 835}, // 104 BitwiseFunctionINTEL
  {IR(31068, 10), 183}, // 105 BitwiseOr
  {IR(31078, 11), 184}, // 106 BitwiseXor
  {IR(31695, 7), 227}, // 107 Branch
  {IR(31702, 18), 228}, // 108 BranchConditional
  {IR(32563, 13), 277}, // 109 BuildNDRange
  {IR(28308, 11), 15}, // 110 Capability
  {IR(32521, 26), 275}, // 111 CaptureEventProfilingInfo
  {IR(34027, 23), 344}, // 112 ColorAttachmentReadEXT
  {IR(32113, 15), 255}, // 113 CommitReadPipe
  {IR(32128, 16), 256}, // 114 CommitWritePipe
  {IR(29554, 19), 72}, // 115 CompositeConstruct
  {IR(48970, 33), 817}, // 116 CompositeConstructContinuedINTEL
  {IR(35610, 30), 412}, // 117 CompositeConstructCoopMatQCOM
  {IR(35185, 31), 395}, // 118 CompositeConstructReplicateEXT
  {IR(29573, 17), 73}, // 119 CompositeExtract
  {IR(35640, 28), 413}, // 120 CompositeExtractCoopMatQCOM
  {IR(29590, 16), 74}, // 121 CompositeInsert
  {IR(49639, 27), 839}, // 122 ConditionalCapabilityINTEL
  {IR(49787, 27), 843}, // 123 ConditionalCopyObjectINTEL
  {IR(49612, 27), 838}, // 124 ConditionalEntryPointINTEL
  {IR(49586, 26), 837}, // 125 ConditionalExtensionINTEL
  {IR(16821, 9), 39}, // 126 Constant
  {IR(28814, 18), 40}, // 127 ConstantComposite
  {IR(48902, 32), 815}, // 128 ConstantCompositeContinuedINTEL
  {IR(35121, 30), 393}, // 129 ConstantCompositeReplicateEXT
  {IR(28762, 14), 38}, // 130 ConstantFalse
  {IR(40671, 29), 602}, // 131 ConstantFunctionPointerINTEL
  {IR(28926, 13), 42}, // 132 ConstantNull
  {IR(33006, 20), 296}, // 133 ConstantPipeStorage
  {IR(28910, 16), 41}, // 134 ConstantSampler
  {IR(36076, 19), 432}, // 135 ConstantStringAMDX
  {IR(28749, 13), 37}, // 136 ConstantTrue
  {IR(31351, 15), 205}, // 137 ControlBarrier
  {IR(49043, 26), 820}, // 138 ControlBarrierArriveINTEL
  {IR(49069, 24), 821}, // 139 ControlBarrierWaitINTEL
  {IR(49023, 20), 819}, // 140 ConvertBF16ToFINTEL
  {IR(49003, 20), 818}, // 141 ConvertFToBF16INTEL
  {IR(30098, 12), 100}, // 142 ConvertFToS
  {IR(30086, 12), 99}, // 143 ConvertFToU
  {IR(50007, 26), 855}, // 144 ConvertHandleToImageINTEL
  {IR(50061, 33), 857}, // 145 ConvertHandleToSampledImageINTEL
  {IR(50033, 28), 856}, // 146 ConvertHandleToSamplerINTEL
  {IR(39638, 18), 559}, // 147 ConvertImageToUNV
  {IR(30175, 14), 107}, // 148 ConvertPtrToU
  {IR(30110, 12), 101}, // 149 ConvertSToF
  {IR(39701, 25), 562}, // 150 ConvertSampledImageToUNV
  {IR(39656, 20), 560}, // 151 ConvertSamplerToUNV
  {IR(34699, 35), 379}, // 152 ConvertUToAccelerationStructureKHR
  {IR(30122, 12), 102}, // 153 ConvertUToF
  {IR(39600, 18), 557}, // 154 ConvertUToImageNV
  {IR(30219, 14), 110}, // 155 ConvertUToPtr
  {IR(39676, 25), 561}, // 156 ConvertUToSampledImageNV
  {IR(39618, 20), 558}, // 157 ConvertUToSamplerNV
  {IR(37252, 27), 475}, // 158 CooperativeMatrixConvertNV
  {IR(35094, 27), 392}, // 159 CooperativeMatrixLengthKHR
  {IR(38963, 26), 535}, // 160 CooperativeMatrixLengthNV
  {IR(34962, 25), 389}, // 161 CooperativeMatrixLoadKHR
  {IR(38888, 24), 532}, // 162 CooperativeMatrixLoadNV
  {IR(39187, 30), 539}, // 163 CooperativeMatrixLoadTensorNV
  {IR(35067, 27), 391}, // 164 CooperativeMatrixMulAddKHR
  {IR(38937, 26), 534}, // 165 CooperativeMatrixMulAddNV
  {IR(39248, 32), 541}, // 166 CooperativeMatrixPerElementOpNV
  {IR(39086, 26), 538}, // 167 CooperativeMatrixReduceNV
  {IR(34987, 26), 390}, // 168 CooperativeMatrixStoreKHR
  {IR(38912, 25), 533}, // 169 CooperativeMatrixStoreNV
  {IR(39217, 31), 540}, // 170 CooperativeMatrixStoreTensorNV
  {IR(39571, 29), 556}, // 171 CooperativeMatrixTransposeNV
  {IR(37447, 24), 482}, // 172 CooperativeVectorLoadNV
  {IR(37220, 32), 474}, // 173 CooperativeVectorMatrixMulAddNV
  {IR(37110, 29), 471}, // 174 CooperativeVectorMatrixMulNV
  {IR(37139, 42), 472}, // 175 CooperativeVectorOuterProductAccumulateNV
  {IR(37181, 39), 473}, // 176 CooperativeVectorReduceSumAccumulateNV
  {IR(37471, 25), 483}, // 177 CooperativeVectorStoreNV
  {IR(33986, 12), 340}, // 178 CopyLogical
  {IR(29220, 11), 56}, // 179 CopyMemory
  {IR(29231, 16), 57}, // 180 CopyMemorySized
  {IR(29606, 11), 75}, // 181 CopyObject
  {IR(33026, 26), 297}, // 182 CreatePipeFromPipeStorage
  {IR(39316, 21), 544}, // 183 CreateTensorLayoutNV
  {IR(39436, 19), 549}, // 184 CreateTensorViewNV
  {IR(32473, 16), 272}, // 185 CreateUserEvent
  {IR(48038, 30), 791}, // 186 CrossWorkgroupCastToPtrALTERA
  {IR(48068, 29), 791}, // 187 CrossWorkgroupCastToPtrINTEL
  {IR(31173, 5), 192}, // 188 DPdx
  {IR(31219, 11), 198}, // 189 DPdxCoarse
  {IR(31190, 9), 195}, // 190 DPdxFine
  {IR(31178, 5), 193}, // 191 DPdy
  {IR(31230, 11), 199}, // 192 DPdyCoarse
  {IR(31199, 9), 196}, // 193 DPdyFine
  {IR(29380, 9), 64}, // 194 Decorate
  {IR(33203, 11), 305}, // 195 DecorateId
  {IR(40805, 15), 611}, // 196 DecorateString
  {IR(40820, 21), 611}, // 197 DecorateStringGOOGLE
  {IR(29404, 16), 66}, // 198 DecorationGroup
  {IR(12309, 25), 552}, // 199 DemoteToHelperInvocation
  {IR(12334, 28), 552}, // 200 DemoteToHelperInvocationEXT
  {IR(34050, 23), 345}, // 201 DepthAttachmentReadEXT
  {IR(30489, 4), 137}, // 202 Dot
  {IR(37279, 17), 476}, // 203 EmitMeshTasksEXT
  {IR(31278, 17), 203}, // 204 EmitStreamVertex
  {IR(31254, 11), 201}, // 205 EmitVertex
  {IR(39017, 26), 537}, // 206 EndInvocationInterlockEXT
  {IR(31265, 13), 202}, // 207 EndPrimitive
  {IR(31295, 19), 204}, // 208 EndStreamPrimitive
  {IR(32309, 14), 265}, // 209 EnqueueKernel
  {IR(32295, 14), 264}, // 210 EnqueueMarker
  {IR(35948, 24), 427}, // 211 EnqueueNodePayloadsAMDX
  {IR(28223, 11), 13}, // 212 EntryPoint
  {IR(34680, 19), 378}, // 213 ExecuteCallableKHR
  {IR(38599, 18), 522}, // 214 ExecuteCallableNV
  {IR(28266, 14), 14}, // 215 ExecutionMode
  {IR(33187, 16), 304}, // 216 ExecutionModeId
  {IR(40795, 10), 610}, // 217 ExpectKHR
  {IR(28077, 8), 11}, // 218 ExtInst
  {IR(28017, 14), 10}, // 219 ExtInstImport
  {IR(34617, 26), 375}, // 220 ExtInstWithForwardRefsKHR
  {IR(28007, 10), 9}, // 221 Extension
  {IR(35668, 20), 414}, // 222 ExtractSubArrayQCOM
  {IR(30321, 5), 118}, // 223 FAdd
  {IR(30152, 9), 105}, // 224 FConvert
  {IR(30356, 5), 125}, // 225 FDiv
  {IR(30381, 5), 130}, // 226 FMod
  {IR(30341, 5), 122}, // 227 FMul
  {IR(30308, 8), 116}, // 228 FNegate
  {IR(30818, 10), 168}, // 229 FOrdEqual
  {IR(30896, 16), 174}, // 230 FOrdGreaterThan
  {IR(30968, 21), 178}, // 231 FOrdGreaterThanEqual
  {IR(30868, 13), 172}, // 232 FOrdLessThan
  {IR(30930, 18), 176}, // 233 FOrdLessThanEqual
  {IR(30840, 13), 170}, // 234 FOrdNotEqual
  {IR(14235, 14), 794}, // 235 FPGARegALTERA
  {IR(14249, 13), 794}, // 236 FPGARegINTEL
  {IR(30376, 5), 129}, // 237 FRem
  {IR(30331, 5), 120}, // 238 FSub
  {IR(30828, 12), 169}, // 239 FUnordEqual
  {IR(30912, 18), 175}, // 240 FUnordGreaterThan
  {IR(30989, 23), 179}, // 241 FUnordGreaterThanEqual
  {IR(30881, 15), 173}, // 242 FUnordLessThan
  {IR(30948, 20), 177}, // 243 FUnordLessThanEqual
  {IR(30853, 15), 171}, // 244 FUnordNotEqual
  {IR(37409, 38), 481}, // 245 FetchMicroTriangleVertexBarycentricNV
  {IR(37374, 35), 480}, // 246 FetchMicroTriangleVertexPositionNV
  {IR(35997, 29), 429}, // 247 FinishWritingNodePayloadAMDX
  {IR(47752, 15), 783}, // 248 FixedCosALTERA
  {IR(47767, 14), 783}, // 249 FixedCosINTEL
  {IR(47849, 17), 786}, // 250 FixedCosPiALTERA
  {IR(47866, 16), 786}, // 251 FixedCosPiINTEL
  {IR(47950, 15), 789}, // 252 FixedExpALTERA
  {IR(47965, 14), 789}, // 253 FixedExpINTEL
  {IR(47921, 15), 788}, // 254 FixedLogALTERA
  {IR(47936, 14), 788}, // 255 FixedLogINTEL
  {IR(47657, 17), 780}, // 256 FixedRecipALTERA
  {IR(47674, 16), 780}, // 257 FixedRecipINTEL
  {IR(47690, 17), 781}, // 258 FixedRsqrtALTERA
  {IR(47707, 16), 781}, // 259 FixedRsqrtINTEL
  {IR(47723, 15), 782}, // 260 FixedSinALTERA
  {IR(47781, 18), 784}, // 261 FixedSinCosALTERA
  {IR(47799, 17), 784}, // 262 FixedSinCosINTEL
  {IR(47882, 20), 787}, // 263 FixedSinCosPiALTERA
  {IR(47902, 19), 787}, // 264 FixedSinCosPiINTEL
  {IR(47738, 14), 782}, // 265 FixedSinINTEL
  {IR(47816, 17), 785}, // 266 FixedSinPiALTERA
  {IR(47833, 16), 785}, // 267 FixedSinPiINTEL
  {IR(47626, 16), 779}, // 268 FixedSqrtALTERA
  {IR(47642, 15), 779}, // 269 FixedSqrtINTEL
  {IR(34534, 7), 369}, // 270 FmaKHR
  {IR(35893, 17), 424}, // 271 FragmentFetchAMD
  {IR(35872, 21), 423}, // 272 FragmentMaskFetchAMD
  {IR(27073, 9), 48}, // 273 Function
  {IR(29129, 13), 51}, // 274 FunctionCall
  {IR(29117, 12), 50}, // 275 FunctionEnd
  {IR(29099, 18), 49}, // 276 FunctionParameter
  {IR(40700, 25), 603}, // 277 FunctionPointerCallINTEL
  {IR(31183, 7), 194}, // 278 Fwidth
  {IR(31241, 13), 200}, // 279 FwidthCoarse
  {IR(31208, 11), 197}, // 280 FwidthFine
  {IR(30250, 17), 112}, // 281 GenericCastToPtr
  {IR(30267, 25), 113}, // 282 GenericCastToPtrExplicit
  {IR(29306, 23), 62}, // 283 GenericPtrMemSemantics
  {IR(32547, 16), 276}, // 284 GetDefaultQueue
  {IR(33052, 35), 298}, // 285 GetKernelLocalSizeForSubgroupCount
  {IR(33087, 25), 299}, // 286 GetKernelMaxNumSubgroups
  {IR(32353, 32), 267}, // 287 GetKernelNDrangeMaxSubGroupSize
  {IR(32323, 30), 266}, // 288 GetKernelNDrangeSubGroupCount
  {IR(32408, 40), 269}, // 289 GetKernelPreferredWorkGroupSizeMultiple
  {IR(32385, 23), 268}, // 290 GetKernelWorkGroupSize
  {IR(32179, 18), 259}, // 291 GetMaxPipePackets
  {IR(32161, 18), 258}, // 292 GetNumPipePackets
  {IR(9778, 9), 353}, // 293 GraphARM
  {IR(34202, 17), 351}, // 294 GraphConstantARM
  {IR(34270, 12), 356}, // 295 GraphEndARM
  {IR(34219, 19), 352}, // 296 GraphEntryPointARM
  {IR(34238, 14), 354}, // 297 GraphInputARM
  {IR(34252, 18), 355}, // 298 GraphSetOutputARM
  {IR(31866, 9), 238}, // 299 GroupAll
  {IR(31875, 9), 239}, // 300 GroupAny
  {IR(31835, 15), 236}, // 301 GroupAsyncCopy
  {IR(49840, 19), 846}, // 302 GroupBitwiseAndKHR
  {IR(49859, 18), 847}, // 303 GroupBitwiseOrKHR
  {IR(49877, 19), 848}, // 304 GroupBitwiseXorKHR
  {IR(31884, 15), 240}, // 305 GroupBroadcast
  {IR(32254, 20), 262}, // 306 GroupCommitReadPipe
  {IR(32274, 21), 263}, // 307 GroupCommitWritePipe
  {IR(29420, 14), 67}, // 308 GroupDecorate
  {IR(31942, 10), 242}, // 309 GroupFAdd
  {IR(35711, 23), 416}, // 310 GroupFAddNonUniformAMD
  {IR(31982, 10), 246}, // 311 GroupFMax
  {IR(35803, 23), 420}, // 312 GroupFMaxNonUniformAMD
  {IR(31952, 10), 243}, // 313 GroupFMin
  {IR(35734, 23), 417}, // 314 GroupFMinNonUniformAMD
  {IR(49827, 13), 845}, // 315 GroupFMulKHR
  {IR(31932, 10), 241}, // 316 GroupIAdd
  {IR(35688, 23), 415}, // 317 GroupIAddNonUniformAMD
  {IR(49814, 13), 844}, // 318 GroupIMulKHR
  {IR(49896, 19), 849}, // 319 GroupLogicalAndKHR
  {IR(49915, 18), 850}, // 320 GroupLogicalOrKHR
  {IR(49933, 19), 851}, // 321 GroupLogicalXorKHR
  {IR(29479, 20), 68}, // 322 GroupMemberDecorate
  {IR(33235, 19), 307}, // 323 GroupNonUniformAll
  {IR(33273, 24), 309}, // 324 GroupNonUniformAllEqual
  {IR(33254, 19), 308}, // 325 GroupNonUniformAny
  {IR(6397, 22), 312}, // 326 GroupNonUniformBallot
  {IR(33413, 30), 315}, // 327 GroupNonUniformBallotBitCount
  {IR(33381, 32), 314}, // 328 GroupNonUniformBallotBitExtract
  {IR(33443, 29), 316}, // 329 GroupNonUniformBallotFindLSB
  {IR(33472, 29), 317}, // 330 GroupNonUniformBallotFindMSB
  {IR(33779, 26), 332}, // 331 GroupNonUniformBitwiseAnd
  {IR(33805, 25), 333}, // 332 GroupNonUniformBitwiseOr
  {IR(33830, 26), 334}, // 333 GroupNonUniformBitwiseXor
  {IR(33297, 25), 310}, // 334 GroupNonUniformBroadcast
  {IR(33322, 30), 311}, // 335 GroupNonUniformBroadcastFirst
  {IR(33214, 21), 306}, // 336 GroupNonUniformElect
  {IR(33599, 20), 323}, // 337 GroupNonUniformFAdd
  {IR(33759, 20), 331}, // 338 GroupNonUniformFMax
  {IR(33699, 20), 328}, // 339 GroupNonUniformFMin
  {IR(33639, 20), 325}, // 340 GroupNonUniformFMul
  {IR(33579, 20), 322}, // 341 GroupNonUniformIAdd
  {IR(33619, 20), 324}, // 342 GroupNonUniformIMul
  {IR(33352, 29), 313}, // 343 GroupNonUniformInverseBallot
  {IR(33856, 26), 335}, // 344 GroupNonUniformLogicalAnd
  {IR(33882, 25), 336}, // 345 GroupNonUniformLogicalOr
  {IR(33907, 26), 337}, // 346 GroupNonUniformLogicalXor
  {IR(37314, 27), 478}, // 347 GroupNonUniformPartitionNV
  {IR(36118, 26), 434}, // 348 GroupNonUniformQuadAllKHR
  {IR(36144, 26), 435}, // 349 GroupNonUniformQuadAnyKHR
  {IR(33933, 29), 338}, // 350 GroupNonUniformQuadBroadcast
  {IR(33962, 24), 339}, // 351 GroupNonUniformQuadSwap
  {IR(14474, 25), 373}, // 352 GroupNonUniformRotateKHR
  {IR(33719, 20), 329}, // 353 GroupNonUniformSMax
  {IR(33659, 20), 326}, // 354 GroupNonUniformSMin
  {IR(9487, 23), 318}, // 355 GroupNonUniformShuffle
  {IR(33552, 27), 321}, // 356 GroupNonUniformShuffleDown
  {IR(33527, 25), 320}, // 357 GroupNonUniformShuffleUp
  {IR(33501, 26), 319}, // 358 GroupNonUniformShuffleXor
  {IR(33739, 20), 330}, // 359 GroupNonUniformUMax
  {IR(33679, 20), 327}, // 360 GroupNonUniformUMin
  {IR(32197, 28), 260}, // 361 GroupReserveReadPipePackets
  {IR(32225, 29), 261}, // 362 GroupReserveWritePipePackets
  {IR(32002, 10), 248}, // 363 GroupSMax
  {IR(35849, 23), 422}, // 364 GroupSMaxNonUniformAMD
  {IR(31972, 10), 245}, // 365 GroupSMin
  {IR(35780, 23), 419}, // 366 GroupSMinNonUniformAMD
  {IR(31992, 10), 247}, // 367 GroupUMax
  {IR(35826, 23), 421}, // 368 GroupUMaxNonUniformAMD
  {IR(31962, 10), 244}, // 369 GroupUMin
  {IR(35757, 23), 418}, // 370 GroupUMinNonUniformAMD
  {IR(31850, 16), 237}, // 371 GroupWaitEvents
  {IR(37943, 26), 499}, // 372 HitObjectExecuteShaderEXT
  {IR(36605, 25), 451}, // 373 HitObjectExecuteShaderNV
  {IR(37996, 26), 501}, // 374 HitObjectGetAttributesEXT
  {IR(36656, 25), 453}, // 375 HitObjectGetAttributesNV
  {IR(38675, 24), 524}, // 376 HitObjectGetClusterIdNV
  {IR(37969, 27), 500}, // 377 HitObjectGetCurrentTimeEXT
  {IR(36630, 26), 452}, // 378 HitObjectGetCurrentTimeNV
  {IR(38075, 29), 504}, // 379 HitObjectGetGeometryIndexEXT
  {IR(36732, 28), 456}, // 380 HitObjectGetGeometryIndexNV
  {IR(38022, 23), 502}, // 381 HitObjectGetHitKindEXT
  {IR(36681, 22), 454}, // 382 HitObjectGetHitKindNV
  {IR(38130, 35), 506}, // 383 HitObjectGetInstanceCustomIndexEXT
  {IR(36785, 34), 458}, // 384 HitObjectGetInstanceCustomIndexNV
  {IR(38104, 26), 505}, // 385 HitObjectGetInstanceIdEXT
  {IR(36760, 25), 457}, // 386 HitObjectGetInstanceIdNV
  {IR(37576, 51), 487}, // 387 HitObjectGetIntersectionTriangleVertexPositionsEXT
  {IR(40067, 27), 572}, // 388 HitObjectGetLSSPositionsNV
  {IR(40094, 23), 573}, // 389 HitObjectGetLSSRadiiNV
  {IR(38196, 34), 508}, // 390 HitObjectGetObjectRayDirectionEXT
  {IR(36317, 33), 441}, // 391 HitObjectGetObjectRayDirectionNV
  {IR(38165, 31), 507}, // 392 HitObjectGetObjectRayOriginEXT
  {IR(36350, 30), 442}, // 393 HitObjectGetObjectRayOriginNV
  {IR(38293, 29), 511}, // 394 HitObjectGetObjectToWorldEXT
  {IR(36289, 28), 440}, // 395 HitObjectGetObjectToWorldNV
  {IR(38045, 30), 503}, // 396 HitObjectGetPrimitiveIndexEXT
  {IR(36703, 29), 455}, // 397 HitObjectGetPrimitiveIndexNV
  {IR(37627, 24), 488}, // 398 HitObjectGetRayFlagsEXT
  {IR(38351, 23), 513}, // 399 HitObjectGetRayTMaxEXT
  {IR(36880, 22), 461}, // 400 HitObjectGetRayTMaxNV
  {IR(38699, 23), 525}, // 401 HitObjectGetRayTMinEXT
  {IR(36902, 22), 462}, // 402 HitObjectGetRayTMinNV
  {IR(38722, 45), 526}, // 403 HitObjectGetShaderBindingTableRecordIndexEXT
  {IR(36445, 44), 445}, // 404 HitObjectGetShaderBindingTableRecordIndexNV
  {IR(38767, 40), 527}, // 405 HitObjectGetShaderRecordBufferHandleEXT
  {IR(36406, 39), 444}, // 406 HitObjectGetShaderRecordBufferHandleNV
  {IR(40011, 29), 570}, // 407 HitObjectGetSpherePositionNV
  {IR(40040, 27), 571}, // 408 HitObjectGetSphereRadiusNV
  {IR(38230, 33), 509}, // 409 HitObjectGetWorldRayDirectionEXT
  {IR(36819, 32), 459}, // 410 HitObjectGetWorldRayDirectionNV
  {IR(38263, 30), 510}, // 411 HitObjectGetWorldRayOriginEXT
  {IR(36851, 29), 460}, // 412 HitObjectGetWorldRayOriginNV
  {IR(38322, 29), 512}, // 413 HitObjectGetWorldToObjectEXT
  {IR(36261, 28), 439}, // 414 HitObjectGetWorldToObjectNV
  {IR(38807, 20), 528}, // 415 HitObjectIsEmptyEXT
  {IR(36924, 19), 463}, // 416 HitObjectIsEmptyNV
  {IR(38827, 18), 529}, // 417 HitObjectIsHitEXT
  {IR(36943, 17), 464}, // 418 HitObjectIsHitNV
  {IR(40140, 20), 575}, // 419 HitObjectIsLSSHitNV
  {IR(38845, 19), 530}, // 420 HitObjectIsMissEXT
  {IR(36960, 18), 465}, // 421 HitObjectIsMissNV
  {IR(40117, 23), 574}, // 422 HitObjectIsSphereHitNV
  {IR(37919, 24), 498}, // 423 HitObjectRecordEmptyEXT
  {IR(36489, 23), 446}, // 424 HitObjectRecordEmptyNV
  {IR(37496, 28), 484}, // 425 HitObjectRecordFromQueryEXT
  {IR(36170, 27), 436}, // 426 HitObjectRecordHitMotionNV
  {IR(36532, 21), 448}, // 427 HitObjectRecordHitNV
  {IR(36197, 36), 437}, // 428 HitObjectRecordHitWithIndexMotionNV
  {IR(36553, 30), 449}, // 429 HitObjectRecordHitWithIndexNV
  {IR(37524, 23), 485}, // 430 HitObjectRecordMissEXT
  {IR(37547, 29), 486}, // 431 HitObjectRecordMissMotionEXT
  {IR(36233, 28), 438}, // 432 HitObjectRecordMissMotionNV
  {IR(36583, 22), 450}, // 433 HitObjectRecordMissNV
  {IR(37696, 33), 490}, // 434 HitObjectReorderExecuteShaderEXT
  {IR(37651, 45), 489}, // 435 HitObjectSetShaderBindingTableRecordIndexEXT
  {IR(37761, 38), 492}, // 436 HitObjectTraceMotionReorderExecuteEXT
  {IR(37871, 21), 496}, // 437 HitObjectTraceRayEXT
  {IR(37892, 27), 497}, // 438 HitObjectTraceRayMotionEXT
  {IR(36380, 26), 443}, // 439 HitObjectTraceRayMotionNV
  {IR(36512, 20), 447}, // 440 HitObjectTraceRayNV
  {IR(37729, 32), 491}, // 441 HitObjectTraceReorderExecuteEXT
  {IR(30316, 5), 117}, // 442 IAdd
  {IR(30493, 10), 138}, // 443 IAddCarry
  {IR(40519, 13), 592}, // 444 IAddSatINTEL
  {IR(40545, 14), 594}, // 445 IAverageINTEL
  {IR(40573, 21), 596}, // 446 IAverageRoundedINTEL
  {IR(30689, 7), 158}, // 447 IEqual
  {IR(30336, 5), 121}, // 448 IMul
  {IR(40641, 15), 600}, // 449 IMul32x16INTEL
  {IR(30696, 10), 159}, // 450 INotEqual
  {IR(30326, 5), 119}, // 451 ISub
  {IR(30503, 11), 139}, // 452 ISubBorrow
  {IR(40615, 13), 598}, // 453 ISubSatINTEL
  {IR(34734, 22), 380}, // 454 IgnoreIntersectionKHR
  {IR(38417, 21), 515}, // 455 IgnoreIntersectionNV
  {IR(27117, 6), 91}, // 456 Image
  {IR(35581, 29), 411}, // 457 ImageBlockMatchGatherSADQCOM
  {IR(35552, 29), 410}, // 458 ImageBlockMatchGatherSSDQCOM
  {IR(35454, 23), 406}, // 459 ImageBlockMatchSADQCOM
  {IR(35431, 23), 405}, // 460 ImageBlockMatchSSDQCOM
  {IR(35523, 29), 409}, // 461 ImageBlockMatchWindowSADQCOM
  {IR(35494, 29), 408}, // 462 ImageBlockMatchWindowSSDQCOM
  {IR(35412, 19), 404}, // 463 ImageBoxFilterQCOM
  {IR(29934, 16), 88}, // 464 ImageDrefGather
  {IR(29911, 11), 86}, // 465 ImageFetch
  {IR(29922, 12), 87}, // 466 ImageGather
  {IR(29971, 17), 92}, // 467 ImageQueryFormat
  {IR(30051, 17), 97}, // 468 ImageQueryLevels
  {IR(30037, 14), 96}, // 469 ImageQueryLod
  {IR(29988, 16), 93}, // 470 ImageQueryOrder
  {IR(30068, 18), 98}, // 471 ImageQuerySamples
  {IR(30022, 15), 95}, // 472 ImageQuerySize
  {IR(30004, 18), 94}, // 473 ImageQuerySizeLod
  {IR(29950, 10), 89}, // 474 ImageRead
  {IR(29768, 27), 81}, // 475 ImageSampleDrefExplicitLod
  {IR(29741, 27), 80}, // 476 ImageSampleDrefImplicitLod
  {IR(29718, 23), 79}, // 477 ImageSampleExplicitLod
  {IR(37047, 23), 469}, // 478 ImageSampleFootprintNV
  {IR(29672, 23), 78}, // 479 ImageSampleImplicitLod
  {IR(29880, 31), 85}, // 480 ImageSampleProjDrefExplicitLod
  {IR(29849, 31), 84}, // 481 ImageSampleProjDrefImplicitLod
  {IR(29822, 27), 83}, // 482 ImageSampleProjExplicitLod
  {IR(29795, 27), 82}, // 483 ImageSampleProjImplicitLod
  {IR(35388, 24), 403}, // 484 ImageSampleWeightedQCOM
  {IR(32875, 22), 288}, // 485 ImageSparseDrefGather
  {IR(32840, 17), 286}, // 486 ImageSparseFetch
  {IR(32857, 18), 287}, // 487 ImageSparseGather
  {IR(32967, 16), 293}, // 488 ImageSparseRead
  {IR(32667, 33), 281}, // 489 ImageSparseSampleDrefExplicitLod
  {IR(32634, 33), 280}, // 490 ImageSparseSampleDrefImplicitLod
  {IR(32605, 29), 279}, // 491 ImageSparseSampleExplicitLod
  {IR(32576, 29), 278}, // 492 ImageSparseSampleImplicitLod
  {IR(32803, 37), 285}, // 493 ImageSparseSampleProjDrefExplicitLod
  {IR(32766, 37), 284}, // 494 ImageSparseSampleProjDrefImplicitLod
  {IR(32733, 33), 283}, // 495 ImageSparseSampleProjExplicitLod
  {IR(32700, 33), 282}, // 496 ImageSparseSampleProjImplicitLod
  {IR(32897, 26), 289}, // 497 ImageSparseTexelsResident
  {IR(29151, 18), 53}, // 498 ImageTexelPointer
  {IR(29960, 11), 90}, // 499 ImageWrite
  {IR(29259, 20), 59}, // 500 InBoundsAccessChain
  {IR(29329, 23), 63}, // 501 InBoundsPtrAccessChain
  {IR(30560, 9), 146}, // 502 IsFinite
  {IR(39502, 22), 553}, // 503 IsHelperInvocationEXT
  {IR(30554, 6), 145}, // 504 IsInf
  {IR(30548, 6), 144}, // 505 IsNan
  {IR(36053, 23), 431}, // 506 IsNodePayloadValidAMDX
  {IR(30569, 9), 147}, // 507 IsNormal
  {IR(32489, 13), 273}, // 508 IsValidEvent
  {IR(32144, 17), 257}, // 509 IsValidReserveId
  {IR(31772, 5), 230}, // 510 Kill
  {IR(31689, 6), 226}, // 511 Label
  {IR(30589, 14), 149}, // 512 LessOrGreater
  {IR(31808, 14), 234}, // 513 LifetimeStart
  {IR(31822, 13), 235}, // 514 LifetimeStop
  {IR(28002, 5), 8}, // 515 Line
  {IR(29209, 5), 54}, // 516 Load
  {IR(30660, 11), 155}, // 517 LogicalAnd
  {IR(30621, 13), 152}, // 518 LogicalEqual
  {IR(30671, 11), 156}, // 519 LogicalNot
  {IR(30634, 16), 153}, // 520 LogicalNotEqual
  {IR(30650, 10), 154}, // 521 LogicalOr
  {IR(47544, 17), 775}, // 522 LoopControlINTEL
  {IR(31629, 10), 224}, // 523 LoopMerge
  {IR(49970, 18), 853}, // 524 MaskedGatherINTEL
  {IR(49988, 19), 854}, // 525 MaskedScatterINTEL
  {IR(30458, 18), 135}, // 526 MatrixTimesMatrix
  {IR(30404, 18), 132}, // 527 MatrixTimesScalar
  {IR(30440, 18), 134}, // 528 MatrixTimesVector
  {IR(29389, 15), 65}, // 529 MemberDecorate
  {IR(40841, 21), 612}, // 530 MemberDecorateString
  {IR(40862, 27), 612}, // 531 MemberDecorateStringGOOGLE
  {IR(27984, 11), 6}, // 532 MemberName
  {IR(31366, 14), 206}, // 533 MemoryBarrier
  {IR(28149, 12), 12}, // 534 MemoryModel
  {IR(33152, 19), 302}, // 535 MemoryNamedBarrier
  {IR(33171, 16), 303}, // 536 ModuleProcessed
  {IR(27979, 5), 5}, // 537 Name
  {IR(33129, 23), 301}, // 538 NamedBarrierInitialize
  {IR(32923, 7), 290}, // 539 NoLine
  {IR(36026, 27), 430}, // 540 NodePayloadArrayLengthAMDX
  {IR(27775, 4), 0}, // 541 Nop
  {IR(31100, 4), 186}, // 542 Not
  {IR(30603, 8), 150}, // 543 Ordered
  {IR(30476, 13), 136}, // 544 OuterProduct
  {IR(31595, 4), 223}, // 545 Phi
  {IR(29279, 15), 60}, // 546 PtrAccessChain
  {IR(47979, 30), 790}, // 547 PtrCastToCrossWorkgroupALTERA
  {IR(48009, 29), 790}, // 548 PtrCastToCrossWorkgroupINTEL
  {IR(30233, 17), 111}, // 549 PtrCastToGeneric
  {IR(34019, 8), 343}, // 550 PtrDiff
  {IR(33998, 9), 341}, // 551 PtrEqual
  {IR(34007, 12), 342}, // 552 PtrNotEqual
  {IR(30161, 14), 106}, // 553 QuantizeToF16
  {IR(39807, 17), 564}, // 554 RawAccessChainNV
  {IR(35307, 31), 400}, // 555 RayQueryConfirmIntersectionKHR
  {IR(35275, 32), 399}, // 556 RayQueryGenerateIntersectionKHR
  {IR(38652, 23), 523}, // 557 RayQueryGetClusterIdNV
  {IR(48491, 39), 803}, // 558 RayQueryGetIntersectionBarycentricsKHR
  {IR(48566, 46), 805}, // 559 RayQueryGetIntersectionCandidateAABBOpaqueKHR
  {IR(38617, 35), 523}, // 560 RayQueryGetIntersectionClusterIdNV
  {IR(48530, 36), 804}, // 561 RayQueryGetIntersectionFrontFaceKHR
  {IR(48410, 40), 801}, // 562 RayQueryGetIntersectionGeometryIndexKHR
  {IR(48262, 46), 798}, // 563 RayQueryGetIntersectionInstanceCustomIndexKHR
  {IR(48308, 37), 799}, // 564 RayQueryGetIntersectionInstanceIdKHR
  {IR(48345, 65), 800}, // 565 RayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR
  {IR(39974, 37), 569}, // 566 RayQueryGetIntersectionLSSHitValueNV
  {IR(39902, 38), 567}, // 567 RayQueryGetIntersectionLSSPositionsNV
  {IR(39940, 34), 568}, // 568 RayQueryGetIntersectionLSSRadiiNV
  {IR(48612, 45), 806}, // 569 RayQueryGetIntersectionObjectRayDirectionKHR
  {IR(48657, 42), 807}, // 570 RayQueryGetIntersectionObjectRayOriginKHR
  {IR(48760, 40), 810}, // 571 RayQueryGetIntersectionObjectToWorldKHR
  {IR(48450, 41), 802}, // 572 RayQueryGetIntersectionPrimitiveIndexKHR
  {IR(39824, 40), 565}, // 573 RayQueryGetIntersectionSpherePositionNV
  {IR(39864, 38), 566}, // 574 RayQueryGetIntersectionSphereRadiusNV
  {IR(48234, 28), 797}, // 575 RayQueryGetIntersectionTKHR
  {IR(38492, 50), 520}, // 576 RayQueryGetIntersectionTriangleVertexPositionsKHR
  {IR(35357, 31), 402}, // 577 RayQueryGetIntersectionTypeKHR
  {IR(48800, 40), 811}, // 578 RayQueryGetIntersectionWorldToObjectKHR
  {IR(48211, 23), 796}, // 579 RayQueryGetRayFlagsKHR
  {IR(48189, 22), 795}, // 580 RayQueryGetRayTMinKHR
  {IR(48699, 32), 808}, // 581 RayQueryGetWorldRayDirectionKHR
  {IR(48731, 29), 809}, // 582 RayQueryGetWorldRayOriginKHR
  {IR(35232, 22), 397}, // 583 RayQueryInitializeKHR
  {IR(40182, 19), 577}, // 584 RayQueryIsLSSHitNV
  {IR(40160, 22), 576}, // 585 RayQueryIsSphereHitNV
  {IR(35338, 19), 401}, // 586 RayQueryProceedKHR
  {IR(35254, 21), 398}, // 587 RayQueryTerminateKHR
  {IR(35910, 13), 425}, // 588 ReadClockKHR
  {IR(32012, 9), 249}, // 589 ReadPipe
  {IR(48097, 23), 792}, // 590 ReadPipeBlockingALTERA
  {IR(48120, 22), 792}, // 591 ReadPipeBlockingINTEL
  {IR(32460, 13), 271}, // 592 ReleaseEvent
  {IR(37816, 25), 494}, // 593 ReorderThreadWithHintEXT
  {IR(37007, 24), 467}, // 594 ReorderThreadWithHintNV
  {IR(37841, 30), 495}, // 595 ReorderThreadWithHitObjectEXT
  {IR(36978, 29), 466}, // 596 ReorderThreadWithHitObjectNV
  {IR(38374, 22), 514}, // 597 ReportIntersectionKHR
  {IR(38396, 21), 514}, // 598 ReportIntersectionNV
  {IR(32066, 23), 253}, // 599 ReserveReadPipePackets
  {IR(32089, 24), 254}, // 600 ReserveWritePipePackets
  {IR(32031, 17), 251}, // 601 ReservedReadPipe
  {IR(32048, 18), 252}, // 602 ReservedWritePipe
  {IR(46071, 19), 733}, // 603 RestoreMemoryINTEL
  {IR(32448, 12), 270}, // 604 RetainEvent
  {IR(31777, 7), 231}, // 605 Return
  {IR(31784, 12), 232}, // 606 ReturnValue
  {IR(49952, 18), 852}, // 607 RoundFToTF32INTEL
  {IR(30143, 9), 104}, // 608 SConvert
  {IR(30351, 5), 124}, // 609 SDiv
  {IR(34819, 5), 382}, // 610 SDot
  {IR(34860, 11), 385}, // 611 SDotAccSat
  {IR(34871, 14), 385}, // 612 SDotAccSatKHR
  {IR(34824, 8), 382}, // 613 SDotKHR
  {IR(30719, 13), 161}, // 614 SGreaterThan
  {IR(30750, 18), 163}, // 615 SGreaterThanEqual
  {IR(30778, 10), 165}, // 616 SLessThan
  {IR(30803, 15), 167}, // 617 SLessThanEqual
  {IR(30371, 5), 128}, // 618 SMod
  {IR(30527, 13), 141}, // 619 SMulExtended
  {IR(30300, 8), 115}, // 620 SNegate
  {IR(30366, 5), 127}, // 621 SRem
  {IR(34845, 6), 384}, // 622 SUDot
  {IR(34910, 12), 387}, // 623 SUDotAccSat
  {IR(34922, 15), 387}, // 624 SUDotAccSatKHR
  {IR(34851, 9), 384}, // 625 SUDotKHR
  {IR(29627, 13), 77}, // 626 SampledImage
  {IR(39726, 29), 563}, // 627 SamplerImageAddressingModeNV
  {IR(30189, 15), 108}, // 628 SatConvertSToU
  {IR(30204, 15), 109}, // 629 SatConvertUToS
  {IR(46055, 16), 732}, // 630 SaveMemoryINTEL
  {IR(30682, 7), 157}, // 631 Select
  {IR(31674, 15), 225}, // 632 SelectionMerge
  {IR(37296, 18), 477}, // 633 SetMeshOutputsEXT
  {IR(32502, 19), 274}, // 634 SetUserEventStatus
  {IR(31051, 17), 182}, // 635 ShiftLeftLogical
  {IR(31030, 21), 181}, // 636 ShiftRightArithmetic
  {IR(31012, 18), 180}, // 637 ShiftRightLogical
  {IR(30578, 11), 148}, // 638 SignBitSet
  {IR(32983, 7), 294}, // 639 SizeOf
  {IR(27956, 7), 3}, // 640 Source
  {IR(27837, 16), 2}, // 641 SourceContinued
  {IR(27963, 16), 4}, // 642 SourceExtension
  {IR(28974, 13), 45}, // 643 SpecConstant
  {IR(49690, 30), 841}, // 644 SpecConstantArchitectureINTEL
  {IR(49757, 30), 842}, // 645 SpecConstantCapabilitiesINTEL
  {IR(28987, 22), 46}, // 646 SpecConstantComposite
  {IR(48934, 36), 816}, // 647 SpecConstantCompositeContinuedINTEL
  {IR(35151, 34), 394}, // 648 SpecConstantCompositeReplicateEXT
  {IR(28956, 18), 44}, // 649 SpecConstantFalse
  {IR(29050, 15), 47}, // 650 SpecConstantOp
  {IR(36095, 23), 433}, // 651 SpecConstantStringAMDX
  {IR(49666, 24), 840}, // 652 SpecConstantTargetINTEL
  {IR(28939, 17), 43}, // 653 SpecConstantTrue
  {IR(34073, 25), 346}, // 654 StencilAttachmentReadEXT
  {IR(29214, 6), 55}, // 655 Store
  {IR(27995, 7), 7}, // 656 String
  {IR(49355, 25), 829}, // 657 Subgroup2DBlockLoadINTEL
  {IR(49380, 34), 830}, // 658 Subgroup2DBlockLoadTransformINTEL
  {IR(49414, 34), 831}, // 659 Subgroup2DBlockLoadTransposeINTEL
  {IR(49448, 29), 832}, // 660 Subgroup2DBlockPrefetchINTEL
  {IR(49477, 26), 833}, // 661 Subgroup2DBlockStoreINTEL
  {IR(34571, 20), 372}, // 662 SubgroupAllEqualKHR
  {IR(34541, 15), 370}, // 663 SubgroupAllKHR
  {IR(34556, 15), 371}, // 664 SubgroupAnyKHR
  {IR(44573, 30), 696}, // 665 SubgroupAvcBmeInitializeINTEL
  {IR(44543, 30), 695}, // 666 SubgroupAvcFmeInitializeINTEL
  {IR(42978, 35), 665}, // 667 SubgroupAvcImeAdjustRefOffsetINTEL
  {IR(43013, 39), 666}, // 668 SubgroupAvcImeConvertToMcePayloadINTEL
  {IR(43654, 38), 679}, // 669 SubgroupAvcImeConvertToMceResultINTEL
  {IR(43277, 45), 672}, // 670 SubgroupAvcImeEvaluateWithDualReferenceINTEL
  {IR(43377, 53), 674}, // 671 SubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL
  {IR(43598, 56), 678}, // 672 SubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL
  {IR(43486, 54), 676}, // 673 SubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL
  {IR(43230, 47), 671}, // 674 SubgroupAvcImeEvaluateWithSingleReferenceINTEL
  {IR(43322, 55), 673}, // 675 SubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL
  {IR(43540, 58), 677}, // 676 SubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL
  {IR(43430, 56), 675}, // 677 SubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL
  {IR(44286, 36), 690}, // 678 SubgroupAvcImeGetBorderReachedINTEL
  {IR(43738, 44), 681}, // 679 SubgroupAvcImeGetDualReferenceStreaminINTEL
  {IR(43692, 46), 680}, // 680 SubgroupAvcImeGetSingleReferenceStreaminINTEL
  {IR(44153, 66), 688}, // 681 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL
  {IR(44085, 68), 687}, // 682 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL
  {IR(44219, 67), 689}, // 683 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL
  {IR(43948, 68), 685}, // 684 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL
  {IR(43878, 70), 684}, // 685 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL
  {IR(44016, 69), 686}, // 686 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL
  {IR(44322, 48), 691}, // 687 SubgroupAvcImeGetTruncatedSearchIndicationINTEL
  {IR(44370, 59), 692}, // 688 SubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL
  {IR(44487, 56), 694}, // 689 SubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL
  {IR(44429, 58), 693}, // 690 SubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL
  {IR(42841, 30), 661}, // 691 SubgroupAvcImeInitializeINTEL
  {IR(42945, 33), 664}, // 692 SubgroupAvcImeRefWindowSizeINTEL
  {IR(42909, 36), 663}, // 693 SubgroupAvcImeSetDualReferenceINTEL
  {IR(43142, 54), 669}, // 694 SubgroupAvcImeSetEarlySearchTerminationThresholdINTEL
  {IR(43052, 43), 667}, // 695 SubgroupAvcImeSetMaxMotionVectorCountINTEL
  {IR(42871, 38), 662}, // 696 SubgroupAvcImeSetSingleReferenceINTEL
  {IR(43095, 47), 668}, // 697 SubgroupAvcImeSetUnidirectionalMixDisableINTEL
  {IR(43196, 34), 670}, // 698 SubgroupAvcImeSetWeightedSadINTEL
  {IR(43831, 47), 683}, // 699 SubgroupAvcImeStripDualReferenceStreamoutINTEL
  {IR(43782, 49), 682}, // 700 SubgroupAvcImeStripSingleReferenceStreamoutINTEL
  {IR(42231, 39), 646}, // 701 SubgroupAvcMceConvertToImePayloadINTEL
  {IR(42270, 38), 647}, // 702 SubgroupAvcMceConvertToImeResultINTEL
  {IR(42308, 39), 648}, // 703 SubgroupAvcMceConvertToRefPayloadINTEL
  {IR(42347, 38), 649}, // 704 SubgroupAvcMceConvertToRefResultINTEL
  {IR(42385, 39), 650}, // 705 SubgroupAvcMceConvertToSicPayloadINTEL
  {IR(42424, 38), 651}, // 706 SubgroupAvcMceConvertToSicResultINTEL
  {IR(42537, 43), 654}, // 707 SubgroupAvcMceGetBestInterDistortionsINTEL
  {IR(41669, 50), 635}, // 708 SubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL
  {IR(41267, 60), 627}, // 709 SubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL
  {IR(41467, 51), 631}, // 710 SubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL
  {IR(41613, 56), 634}, // 711 SubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL
  {IR(41380, 47), 629}, // 712 SubgroupAvcMceGetDefaultInterShapePenaltyINTEL
  {IR(41968, 56), 641}, // 713 SubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL
  {IR(41867, 50), 639}, // 714 SubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL
  {IR(41562, 51), 633}, // 715 SubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL
  {IR(41771, 49), 637}, // 716 SubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL
  {IR(41719, 52), 636}, // 717 SubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL
  {IR(41917, 51), 640}, // 718 SubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL
  {IR(42656, 38), 657}, // 719 SubgroupAvcMceGetInterDirectionsINTEL
  {IR(42498, 39), 653}, // 720 SubgroupAvcMceGetInterDistortionsINTEL
  {IR(42580, 38), 655}, // 721 SubgroupAvcMceGetInterMajorShapeINTEL
  {IR(42618, 38), 656}, // 722 SubgroupAvcMceGetInterMinorShapeINTEL
  {IR(42694, 45), 658}, // 723 SubgroupAvcMceGetInterMotionVectorCountINTEL
  {IR(42739, 40), 659}, // 724 SubgroupAvcMceGetInterReferenceIdsINTEL
  {IR(42779, 62), 660}, // 725 SubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL
  {IR(42462, 36), 652}, // 726 SubgroupAvcMceGetMotionVectorsINTEL
  {IR(42024, 33), 642}, // 727 SubgroupAvcMceSetAcOnlyHaarINTEL
  {IR(42170, 61), 645}, // 728 SubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL
  {IR(41327, 53), 628}, // 729 SubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL
  {IR(41518, 44), 632}, // 730 SubgroupAvcMceSetInterDirectionPenaltyINTEL
  {IR(41427, 40), 630}, // 731 SubgroupAvcMceSetInterShapePenaltyINTEL
  {IR(41820, 47), 638}, // 732 SubgroupAvcMceSetMotionVectorCostFunctionINTEL
  {IR(42109, 61), 644}, // 733 SubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL
  {IR(42057, 52), 643}, // 734 SubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL
  {IR(44603, 39), 697}, // 735 SubgroupAvcRefConvertToMcePayloadINTEL
  {IR(44925, 38), 704}, // 736 SubgroupAvcRefConvertToMceResultINTEL
  {IR(44778, 45), 701}, // 737 SubgroupAvcRefEvaluateWithDualReferenceINTEL
  {IR(44823, 46), 702}, // 738 SubgroupAvcRefEvaluateWithMultiReferenceINTEL
  {IR(44869, 56), 703}, // 739 SubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL
  {IR(44731, 47), 700}, // 740 SubgroupAvcRefEvaluateWithSingleReferenceINTEL
  {IR(44642, 46), 698}, // 741 SubgroupAvcRefSetBidirectionalMixDisableINTEL
  {IR(44688, 43), 699}, // 742 SubgroupAvcRefSetBilinearFilterEnableINTEL
  {IR(45061, 42), 708}, // 743 SubgroupAvcSicConfigureIpeLumaChromaINTEL
  {IR(45025, 36), 707}, // 744 SubgroupAvcSicConfigureIpeLumaINTEL
  {IR(44993, 32), 706}, // 745 SubgroupAvcSicConfigureSkcINTEL
  {IR(45142, 39), 710}, // 746 SubgroupAvcSicConvertToMcePayloadINTEL
  {IR(45682, 38), 722}, // 747 SubgroupAvcSicConvertToMceResultINTEL
  {IR(45457, 31), 717}, // 748 SubgroupAvcSicEvaluateIpeINTEL
  {IR(45535, 45), 719}, // 749 SubgroupAvcSicEvaluateWithDualReferenceINTEL
  {IR(45580, 46), 720}, // 750 SubgroupAvcSicEvaluateWithMultiReferenceINTEL
  {IR(45626, 56), 721}, // 751 SubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL
  {IR(45488, 47), 718}, // 752 SubgroupAvcSicEvaluateWithSingleReferenceINTEL
  {IR(45799, 46), 725}, // 753 SubgroupAvcSicGetBestIpeChromaDistortionINTEL
  {IR(45755, 44), 724}, // 754 SubgroupAvcSicGetBestIpeLumaDistortionINTEL
  {IR(46020, 35), 730}, // 755 SubgroupAvcSicGetInterRawSadsINTEL
  {IR(45886, 36), 727}, // 756 SubgroupAvcSicGetIpeChromaModeINTEL
  {IR(45720, 35), 723}, // 757 SubgroupAvcSicGetIpeLumaShapeINTEL
  {IR(45103, 39), 709}, // 758 SubgroupAvcSicGetMotionVectorMaskINTEL
  {IR(45845, 41), 726}, // 759 SubgroupAvcSicGetPackedIpeLumaModesINTEL
  {IR(45922, 50), 728}, // 760 SubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL
  {IR(45972, 48), 729}, // 761 SubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL
  {IR(44963, 30), 705}, // 762 SubgroupAvcSicInitializeINTEL
  {IR(45323, 43), 714}, // 763 SubgroupAvcSicSetBilinearFilterEnableINTEL
  {IR(45414, 43), 716}, // 764 SubgroupAvcSicSetBlockBasedRawSkipSadINTEL
  {IR(45273, 50), 713}, // 765 SubgroupAvcSicSetIntraChromaModeCostFunctionINTEL
  {IR(45225, 48), 712}, // 766 SubgroupAvcSicSetIntraLumaModeCostFunctionINTEL
  {IR(45181, 44), 711}, // 767 SubgroupAvcSicSetIntraLumaShapePenaltyINTEL
  {IR(45366, 48), 715}, // 768 SubgroupAvcSicSetSkcForwardTransformEnableINTEL
  {IR(6158, 18), 363}, // 769 SubgroupBallotKHR
  {IR(49328, 27), 828}, // 770 SubgroupBlockPrefetchINTEL
  {IR(40273, 23), 582}, // 771 SubgroupBlockReadINTEL
  {IR(40296, 24), 583}, // 772 SubgroupBlockWriteINTEL
  {IR(34408, 27), 364}, // 773 SubgroupFirstInvocationKHR
  {IR(40320, 28), 584}, // 774 SubgroupImageBlockReadINTEL
  {IR(40348, 29), 585}, // 775 SubgroupImageBlockWriteINTEL
  {IR(40377, 33), 586}, // 776 SubgroupImageMediaBlockReadINTEL
  {IR(40410, 34), 587}, // 777 SubgroupImageMediaBlockWriteINTEL
  {IR(15165, 38), 834}, // 778 SubgroupMatrixMultiplyAccumulateINTEL
  {IR(34591, 26), 374}, // 779 SubgroupReadInvocationKHR
  {IR(40201, 25), 579}, // 780 SubgroupShuffleDownINTEL
  {IR(12821, 21), 578}, // 781 SubgroupShuffleINTEL
  {IR(40226, 23), 580}, // 782 SubgroupShuffleUpINTEL
  {IR(40249, 24), 581}, // 783 SubgroupShuffleXorINTEL
  {IR(31765, 7), 229}, // 784 Switch
  {IR(49142, 24), 824}, // 785 TaskSequenceAsyncALTERA
  {IR(49166, 23), 824}, // 786 TaskSequenceAsyncINTEL
  {IR(49093, 25), 823}, // 787 TaskSequenceCreateALTERA
  {IR(49118, 24), 823}, // 788 TaskSequenceCreateINTEL
  {IR(49189, 22), 825}, // 789 TaskSequenceGetALTERA
  {IR(49211, 21), 825}, // 790 TaskSequenceGetINTEL
  {IR(49232, 26), 826}, // 791 TaskSequenceReleaseALTERA
  {IR(49258, 25), 826}, // 792 TaskSequenceReleaseINTEL
  {IR(39544, 27), 555}, // 793 TensorLayoutSetBlockSizeNV
  {IR(39408, 28), 548}, // 794 TensorLayoutSetClampValueNV
  {IR(39337, 27), 545}, // 795 TensorLayoutSetDimensionNV
  {IR(39364, 24), 546}, // 796 TensorLayoutSetStrideNV
  {IR(39388, 20), 547}, // 797 TensorLayoutSliceNV
  {IR(34183, 19), 350}, // 798 TensorQuerySizeARM
  {IR(34154, 14), 348}, // 799 TensorReadARM
  {IR(39524, 20), 554}, // 800 TensorViewSetClipNV
  {IR(39455, 25), 550}, // 801 TensorViewSetDimensionNV
  {IR(39480, 22), 551}, // 802 TensorViewSetStrideNV
  {IR(34168, 15), 349}, // 803 TensorWriteARM
  {IR(34295, 20), 358}, // 804 TerminateInvocation
  {IR(34756, 16), 381}, // 805 TerminateRayKHR
  {IR(38438, 15), 516}, // 806 TerminateRayNV
  {IR(38461, 14), 518}, // 807 TraceMotionNV
  {IR(38453, 8), 517}, // 808 TraceNV
  {IR(34668, 12), 377}, // 809 TraceRayKHR
  {IR(38475, 17), 519}, // 810 TraceRayMotionNV
  {IR(29617, 10), 76}, // 811 Transpose
  {IR(38542, 29), 521}, // 812 TypeAccelerationStructureKHR
  {IR(38571, 28), 521}, // 813 TypeAccelerationStructureNV
  {IR(28566, 10), 25}, // 814 TypeArray
  {IR(41186, 37), 624}, // 815 TypeAvcImeDualReferenceStreaminINTEL
  {IR(40921, 23), 615}, // 816 TypeAvcImePayloadINTEL
  {IR(41103, 44), 622}, // 817 TypeAvcImeResultDualReferenceStreamoutINTEL
  {IR(41035, 22), 620}, // 818 TypeAvcImeResultINTEL
  {IR(41057, 46), 621}, // 819 TypeAvcImeResultSingleReferenceStreamoutINTEL
  {IR(41147, 39), 623}, // 820 TypeAvcImeSingleReferenceStreaminINTEL
  {IR(40990, 23), 618}, // 821 TypeAvcMcePayloadINTEL
  {IR(41013, 22), 619}, // 822 TypeAvcMceResultINTEL
  {IR(40944, 23), 616}, // 823 TypeAvcRefPayloadINTEL
  {IR(41223, 22), 625}, // 824 TypeAvcRefResultINTEL
  {IR(40967, 23), 617}, // 825 TypeAvcSicPayloadINTEL
  {IR(41245, 22), 626}, // 826 TypeAvcSicResultINTEL
  {IR(28328, 9), 17}, // 827 TypeBool
  {IR(48854, 23), 813}, // 828 TypeBufferSurfaceINTEL
  {IR(34937, 25), 388}, // 829 TypeCooperativeMatrixKHR
  {IR(38864, 24), 531}, // 830 TypeCooperativeMatrixNV
  {IR(37070, 24), 470}, // 831 TypeCooperativeVectorNV
  {IR(28681, 16), 32}, // 832 TypeDeviceEvent
  {IR(28671, 10), 31}, // 833 TypeEvent
  {IR(28382, 10), 19}, // 834 TypeFloat
  {IR(28730, 19), 36}, // 835 TypeForwardPointer
  {IR(28658, 13), 30}, // 836 TypeFunction
  {IR(34282, 13), 357}, // 837 TypeGraphARM
  {IR(37799, 17), 493}, // 838 TypeHitObjectEXT
  {IR(37031, 16), 468}, // 839 TypeHitObjectNV
  {IR(28527, 10), 22}, // 840 TypeImage
  {IR(28337, 8), 18}, // 841 TypeInt
  {IR(28403, 11), 21}, // 842 TypeMatrix
  {IR(33112, 17), 300}, // 843 TypeNamedBarrier
  {IR(35972, 25), 428}, // 844 TypeNodePayloadArrayAMDX
  {IR(28604, 11), 28}, // 845 TypeOpaque
  {IR(28721, 9), 35}, // 846 TypePipe
  {IR(32990, 16), 295}, // 847 TypePipeStorage
  {IR(28646, 12), 29}, // 848 TypePointer
  {IR(28711, 10), 34}, // 849 TypeQueue
  {IR(35216, 16), 396}, // 850 TypeRayQueryKHR
  {IR(28697, 14), 33}, // 851 TypeReserveId
  {IR(28576, 17), 26}, // 852 TypeRuntimeArray
  {IR(28549, 17), 24}, // 853 TypeSampledImage
  {IR(28537, 12), 23}, // 854 TypeSampler
  {IR(28593, 11), 27}, // 855 TypeStruct
  {IR(48877, 25), 814}, // 856 TypeStructContinuedINTEL
  {IR(49283, 23), 827}, // 857 TypeTaskSequenceALTERA
  {IR(49306, 22), 827}, // 858 TypeTaskSequenceINTEL
  {IR(34098, 14), 347}, // 859 TypeTensorARM
  {IR(39280, 19), 542}, // 860 TypeTensorLayoutNV
  {IR(39299, 17), 543}, // 861 TypeTensorViewNV
  {IR(34315, 22), 359}, // 862 TypeUntypedPointerKHR
  {IR(28392, 11), 20}, // 863 TypeVector
  {IR(37094, 16), 470}, // 864 TypeVectorIdEXT
  {IR(40903, 18), 614}, // 865 TypeVmeImageINTEL
  {IR(28319, 9), 16}, // 866 TypeVoid
  {IR(40532, 13), 593}, // 867 UAddSatINTEL
  {IR(40559, 14), 595}, // 868 UAverageINTEL
  {IR(40594, 21), 597}, // 869 UAverageRoundedINTEL
  {IR(30134, 9), 103}, // 870 UConvert
  {IR(40444, 24), 588}, // 871 UCountLeadingZerosINTEL
  {IR(40468, 25), 589}, // 872 UCountTrailingZerosINTEL
  {IR(30346, 5), 123}, // 873 UDiv
  {IR(34832, 5), 383}, // 874 UDot
  {IR(34885, 11), 386}, // 875 UDotAccSat
  {IR(34896, 14), 386}, // 876 UDotAccSatKHR
  {IR(34837, 8), 383}, // 877 UDotKHR
  {IR(30706, 13), 160}, // 878 UGreaterThan
  {IR(30732, 18), 162}, // 879 UGreaterThanEqual
  {IR(30768, 10), 164}, // 880 ULessThan
  {IR(30788, 15), 166}, // 881 ULessThanEqual
  {IR(30361, 5), 126}, // 882 UMod
  {IR(40656, 15), 601}, // 883 UMul32x16INTEL
  {IR(30514, 13), 140}, // 884 UMulExtended
  {IR(40628, 13), 599}, // 885 USubSatINTEL
  {IR(27831, 6), 1}, // 886 Undef
  {IR(30611, 10), 151}, // 887 Unordered
  {IR(31796, 12), 233}, // 888 Unreachable
  {IR(34356, 22), 361}, // 889 UntypedAccessChainKHR
  {IR(34493, 22), 367}, // 890 UntypedArrayLengthKHR
  {IR(34643, 25), 376}, // 891 UntypedGroupAsyncCopyKHR
  {IR(34378, 30), 362}, // 892 UntypedInBoundsAccessChainKHR
  {IR(34460, 33), 366}, // 893 UntypedInBoundsPtrAccessChainKHR
  {IR(34515, 19), 368}, // 894 UntypedPrefetchKHR
  {IR(34435, 25), 365}, // 895 UntypedPtrAccessChainKHR
  {IR(34337, 19), 360}, // 896 UntypedVariableKHR
  {IR(15231, 32), 836}, // 897 UntypedVariableLengthArrayINTEL
  {IR(29142, 9), 52}, // 898 Variable
  {IR(13277, 25), 731}, // 899 VariableLengthArrayINTEL
  {IR(29499, 21), 69}, // 900 VectorExtractDynamic
  {IR(29520, 20), 70}, // 901 VectorInsertDynamic
  {IR(29540, 14), 71}, // 902 VectorShuffle
  {IR(30422, 18), 133}, // 903 VectorTimesMatrix
  {IR(30386, 18), 131}, // 904 VectorTimesScalar
  {IR(40889, 14), 613}, // 905 VmeImageINTEL
  {IR(37341, 33), 479}, // 906 WritePackedPrimitiveIndices4x8NV
  {IR(32021, 10), 250}, // 907 WritePipe
  {IR(48142, 24), 793}, // 908 WritePipeBlockingALTERA
  {IR(48166, 23), 793}, // 909 WritePipeBlockingINTEL
}};

// Extended instruction descriptions, ordered by (extinst enum, opcode value).
// The fields in order are:
//   enum value
//   operands, an IndexRange into kOperandSpans
//   name, a character-counting IndexRange into kStrings
//   capabilities, an IndexRange into kCapabilitySpans
static const std::array<ExtInstDesc, 425> kExtInstByValue{{
    {0,IR(0, 0),IR(50094, 14),IR(1, 0)}, // DebugInfoNone in debuginfo
    {1,IR(52, 3),IR(50108, 21),IR(1, 0)}, // DebugCompilationUnit in debuginfo
    {2,IR(803, 3),IR(50181, 15),IR(1, 0)}, // DebugTypeBasic in debuginfo
    {3,IR(806, 3),IR(50230, 17),IR(1, 0)}, // DebugTypePointer in debuginfo
    {4,IR(809, 2),IR(50285, 19),IR(1, 0)}, // DebugTypeQualifier in debuginfo
    {5,IR(168, 2),IR(50304, 15),IR(1, 0)}, // DebugTypeArray in debuginfo
    {6,IR(261, 2),IR(50319, 16),IR(1, 0)}, // DebugTypeVector in debuginfo
    {7,IR(811, 6),IR(50335, 13),IR(1, 0)}, // DebugTypedef in debuginfo
    {8,IR(168, 2),IR(50348, 18),IR(1, 0)}, // DebugTypeFunction in debuginfo
    {9,IR(817, 9),IR(50366, 14),IR(1, 0)}, // DebugTypeEnum in debuginfo
    {10,IR(826, 9),IR(50418, 19),IR(1, 0)}, // DebugTypeComposite in debuginfo
    {11,IR(835, 10),IR(50437, 16),IR(1, 0)}, // DebugTypeMember in debuginfo
    {12,IR(845, 5),IR(50453, 21),IR(1, 0)}, // DebugTypeInheritance in debuginfo
    {13,IR(36, 2),IR(50474, 21),IR(1, 0)}, // DebugTypePtrToMember in debuginfo
    {14,IR(168, 2),IR(50495, 18),IR(1, 0)}, // DebugTypeTemplate in debuginfo
    {15,IR(850, 6),IR(50513, 27),IR(1, 0)}, // DebugTypeTemplateParameter in debuginfo
    {16,IR(856, 5),IR(50540, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in debuginfo
    {17,IR(861, 5),IR(50575, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in debuginfo
    {18,IR(835, 10),IR(50606, 20),IR(1, 0)}, // DebugGlobalVariable in debuginfo
    {19,IR(866, 8),IR(50626, 25),IR(1, 0)}, // DebugFunctionDeclaration in debuginfo
    {20,IR(874, 11),IR(50651, 14),IR(1, 0)}, // DebugFunction in debuginfo
    {21,IR(885, 5),IR(50665, 18),IR(1, 0)}, // DebugLexicalBlock in debuginfo
    {22,IR(890, 3),IR(50683, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in debuginfo
    {23,IR(893, 2),IR(50714, 11),IR(1, 0)}, // DebugScope in debuginfo
    {24,IR(0, 0),IR(50725, 13),IR(1, 0)}, // DebugNoScope in debuginfo
    {25,IR(895, 3),IR(50738, 15),IR(1, 0)}, // DebugInlinedAt in debuginfo
    {26,IR(898, 7),IR(50795, 19),IR(1, 0)}, // DebugLocalVariable in debuginfo
    {27,IR(36, 2),IR(50814, 21),IR(1, 0)}, // DebugInlinedVariable in debuginfo
    {28,IR(33, 3),IR(50835, 13),IR(1, 0)}, // DebugDeclare in debuginfo
    {29,IR(375, 3),IR(50848, 11),IR(1, 0)}, // DebugValue in debuginfo
    {30,IR(905, 2),IR(50892, 15),IR(1, 0)}, // DebugOperation in debuginfo
    {31,IR(739, 1),IR(50907, 16),IR(1, 0)}, // DebugExpression in debuginfo
    {32,IR(907, 4),IR(50923, 14),IR(1, 0)}, // DebugMacroDef in debuginfo
    {33,IR(890, 3),IR(50937, 16),IR(1, 0)}, // DebugMacroUndef in debuginfo
    {1,IR(10, 1),IR(50953, 6),IR(1, 0)}, // Round in glsl_std_450
    {2,IR(10, 1),IR(50959, 10),IR(1, 0)}, // RoundEven in glsl_std_450
    {3,IR(10, 1),IR(50969, 6),IR(1, 0)}, // Trunc in glsl_std_450
    {4,IR(10, 1),IR(50975, 5),IR(1, 0)}, // FAbs in glsl_std_450
    {5,IR(10, 1),IR(50980, 5),IR(1, 0)}, // SAbs in glsl_std_450
    {6,IR(10, 1),IR(50985, 6),IR(1, 0)}, // FSign in glsl_std_450
    {7,IR(10, 1),IR(50991, 6),IR(1, 0)}, // SSign in glsl_std_450
    {8,IR(10, 1),IR(50997, 6),IR(1, 0)}, // Floor in glsl_std_450
    {9,IR(10, 1),IR(51003, 5),IR(1, 0)}, // Ceil in glsl_std_450
    {10,IR(10, 1),IR(51008, 6),IR(1, 0)}, // Fract in glsl_std_450
    {11,IR(10, 1),IR(51014, 8),IR(1, 0)}, // Radians in glsl_std_450
    {12,IR(10, 1),IR(51022, 8),IR(1, 0)}, // Degrees in glsl_std_450
    {13,IR(10, 1),IR(51030, 4),IR(1, 0)}, // Sin in glsl_std_450
    {14,IR(10, 1),IR(51034, 4),IR(1, 0)}, // Cos in glsl_std_450
    {15,IR(10, 1),IR(51038, 4),IR(1, 0)}, // Tan in glsl_std_450
    {16,IR(10, 1),IR(51042, 5),IR(1, 0)}, // Asin in glsl_std_450
    {17,IR(10, 1),IR(51047, 5),IR(1, 0)}, // Acos in glsl_std_450
    {18,IR(10, 1),IR(51052, 5),IR(1, 0)}, // Atan in glsl_std_450
    {19,IR(10, 1),IR(51057, 5),IR(1, 0)}, // Sinh in glsl_std_450
    {20,IR(10, 1),IR(51062, 5),IR(1, 0)}, // Cosh in glsl_std_450
    {21,IR(10, 1),IR(51067, 5),IR(1, 0)}, // Tanh in glsl_std_450
    {22,IR(10, 1),IR(51072, 6),IR(1, 0)}, // Asinh in glsl_std_450
    {23,IR(10, 1),IR(51078, 6),IR(1, 0)}, // Acosh in glsl_std_450
    {24,IR(10, 1),IR(51084, 6),IR(1, 0)}, // Atanh in glsl_std_450
    {25,IR(36, 2),IR(51090, 6),IR(1, 0)}, // Atan2 in glsl_std_450
    {26,IR(36, 2),IR(51096, 4),IR(1, 0)}, // Pow in glsl_std_450
    {27,IR(10, 1),IR(51100, 4),IR(1, 0)}, // Exp in glsl_std_450
    {28,IR(10, 1),IR(51104, 4),IR(1, 0)}, // Log in glsl_std_450
    {29,IR(10, 1),IR(51108, 5),IR(1, 0)}, // Exp2 in glsl_std_450
    {30,IR(10, 1),IR(51113, 5),IR(1, 0)}, // Log2 in glsl_std_450
    {31,IR(10, 1),IR(51118, 5),IR(1, 0)}, // Sqrt in glsl_std_450
    {32,IR(10, 1),IR(51123, 12),IR(1, 0)}, // InverseSqrt in glsl_std_450
    {33,IR(10, 1),IR(51135, 12),IR(1, 0)}, // Determinant in glsl_std_450
    {34,IR(10, 1),IR(51147, 14),IR(1, 0)}, // MatrixInverse in glsl_std_450
    {35,IR(36, 2),IR(51161, 5),IR(1, 0)}, // Modf in glsl_std_450
    {36,IR(10, 1),IR(51166, 11),IR(1, 0)}, // ModfStruct in glsl_std_450
    {37,IR(36, 2),IR(51177, 5),IR(1, 0)}, // FMin in glsl_std_450
    {38,IR(36, 2),IR(51182, 5),IR(1, 0)}, // UMin in glsl_std_450
    {39,IR(36, 2),IR(51187, 5),IR(1, 0)}, // SMin in glsl_std_450
    {40,IR(36, 2),IR(51192, 5),IR(1, 0)}, // FMax in glsl_std_450
    {41,IR(36, 2),IR(51197, 5),IR(1, 0)}, // UMax in glsl_std_450
    {42,IR(36, 2),IR(51202, 5),IR(1, 0)}, // SMax in glsl_std_450
    {43,IR(33, 3),IR(51207, 7),IR(1, 0)}, // FClamp in glsl_std_450
    {44,IR(33, 3),IR(51214, 7),IR(1, 0)}, // UClamp in glsl_std_450
    {45,IR(33, 3),IR(51221, 7),IR(1, 0)}, // SClamp in glsl_std_450
    {46,IR(33, 3),IR(51228, 5),IR(1, 0)}, // FMix in glsl_std_450
    {47,IR(33, 3),IR(51233, 5),IR(1, 0)}, // IMix in glsl_std_450
    {48,IR(36, 2),IR(51238, 5),IR(1, 0)}, // Step in glsl_std_450
    {49,IR(33, 3),IR(51243, 11),IR(1, 0)}, // SmoothStep in glsl_std_450
    {50,IR(33, 3),IR(51254, 4),IR(1, 0)}, // Fma in glsl_std_450
    {51,IR(36, 2),IR(51258, 6),IR(1, 0)}, // Frexp in glsl_std_450
    {52,IR(10, 1),IR(51264, 12),IR(1, 0)}, // FrexpStruct in glsl_std_450
    {53,IR(36, 2),IR(51276, 6),IR(1, 0)}, // Ldexp in glsl_std_450
    {54,IR(10, 1),IR(51282, 13),IR(1, 0)}, // PackSnorm4x8 in glsl_std_450
    {55,IR(10, 1),IR(51295, 13),IR(1, 0)}, // PackUnorm4x8 in glsl_std_450
    {56,IR(10, 1),IR(51308, 14),IR(1, 0)}, // PackSnorm2x16 in glsl_std_450
    {57,IR(10, 1),IR(51322, 14),IR(1, 0)}, // PackUnorm2x16 in glsl_std_450
    {58,IR(10, 1),IR(51336, 13),IR(1, 0)}, // PackHalf2x16 in glsl_std_450
    {59,IR(10, 1),IR(51349, 15),IR(317, 1)}, // PackDouble2x32 in glsl_std_450
    {60,IR(10, 1),IR(51364, 16),IR(1, 0)}, // UnpackSnorm2x16 in glsl_std_450
    {61,IR(10, 1),IR(51380, 16),IR(1, 0)}, // UnpackUnorm2x16 in glsl_std_450
    {62,IR(10, 1),IR(51396, 15),IR(1, 0)}, // UnpackHalf2x16 in glsl_std_450
    {63,IR(10, 1),IR(51411, 15),IR(1, 0)}, // UnpackSnorm4x8 in glsl_std_450
    {64,IR(10, 1),IR(51426, 15),IR(1, 0)}, // UnpackUnorm4x8 in glsl_std_450
    {65,IR(10, 1),IR(51441, 17),IR(317, 1)}, // UnpackDouble2x32 in glsl_std_450
    {66,IR(10, 1),IR(51458, 7),IR(1, 0)}, // Length in glsl_std_450
    {67,IR(36, 2),IR(51465, 9),IR(1, 0)}, // Distance in glsl_std_450
    {68,IR(36, 2),IR(51474, 6),IR(1, 0)}, // Cross in glsl_std_450
    {69,IR(10, 1),IR(51480, 10),IR(1, 0)}, // Normalize in glsl_std_450
    {70,IR(33, 3),IR(51490, 12),IR(1, 0)}, // FaceForward in glsl_std_450
    {71,IR(36, 2),IR(51502, 8),IR(1, 0)}, // Reflect in glsl_std_450
    {72,IR(33, 3),IR(51510, 8),IR(1, 0)}, // Refract in glsl_std_450
    {73,IR(10, 1),IR(51518, 9),IR(1, 0)}, // FindILsb in glsl_std_450
    {74,IR(10, 1),IR(51527, 9),IR(1, 0)}, // FindSMsb in glsl_std_450
    {75,IR(10, 1),IR(51536, 9),IR(1, 0)}, // FindUMsb in glsl_std_450
    {76,IR(10, 1),IR(51545, 22),IR(318, 1)}, // InterpolateAtCentroid in glsl_std_450
    {77,IR(36, 2),IR(51567, 20),IR(318, 1)}, // InterpolateAtSample in glsl_std_450
    {78,IR(36, 2),IR(51587, 20),IR(318, 1)}, // InterpolateAtOffset in glsl_std_450
    {79,IR(36, 2),IR(51607, 5),IR(1, 0)}, // NMin in glsl_std_450
    {80,IR(36, 2),IR(51612, 5),IR(1, 0)}, // NMax in glsl_std_450
    {81,IR(33, 3),IR(51617, 7),IR(1, 0)}, // NClamp in glsl_std_450
    {1,IR(399, 5),IR(5377, 7),IR(1, 0)}, // Kernel in nonsemantic_clspvreflection
    {2,IR(911, 5),IR(51624, 13),IR(1, 0)}, // ArgumentInfo in nonsemantic_clspvreflection
    {3,IR(916, 5),IR(51637, 22),IR(1, 0)}, // ArgumentStorageBuffer in nonsemantic_clspvreflection
    {4,IR(916, 5),IR(51659, 16),IR(1, 0)}, // ArgumentUniform in nonsemantic_clspvreflection
    {5,IR(554, 7),IR(51675, 25),IR(1, 0)}, // ArgumentPodStorageBuffer in nonsemantic_clspvreflection
    {6,IR(554, 7),IR(51700, 19),IR(1, 0)}, // ArgumentPodUniform in nonsemantic_clspvreflection
    {7,IR(916, 5),IR(51719, 24),IR(1, 0)}, // ArgumentPodPushConstant in nonsemantic_clspvreflection
    {8,IR(916, 5),IR(51743, 21),IR(1, 0)}, // ArgumentSampledImage in nonsemantic_clspvreflection
    {9,IR(916, 5),IR(51764, 21),IR(1, 0)}, // ArgumentStorageImage in nonsemantic_clspvreflection
    {10,IR(916, 5),IR(51785, 16),IR(1, 0)}, // ArgumentSampler in nonsemantic_clspvreflection
    {11,IR(916, 5),IR(51801, 18),IR(1, 0)}, // ArgumentWorkgroup in nonsemantic_clspvreflection
    {12,IR(33, 3),IR(51819, 26),IR(1, 0)}, // SpecConstantWorkgroupSize in nonsemantic_clspvreflection
    {13,IR(33, 3),IR(51845, 25),IR(1, 0)}, // SpecConstantGlobalOffset in nonsemantic_clspvreflection
    {14,IR(10, 1),IR(51870, 20),IR(1, 0)}, // SpecConstantWorkDim in nonsemantic_clspvreflection
    {15,IR(36, 2),IR(51890, 25),IR(1, 0)}, // PushConstantGlobalOffset in nonsemantic_clspvreflection
    {16,IR(36, 2),IR(51915, 30),IR(1, 0)}, // PushConstantEnqueuedLocalSize in nonsemantic_clspvreflection
    {17,IR(36, 2),IR(51945, 23),IR(1, 0)}, // PushConstantGlobalSize in nonsemantic_clspvreflection
    {18,IR(36, 2),IR(51968, 25),IR(1, 0)}, // PushConstantRegionOffset in nonsemantic_clspvreflection
    {19,IR(36, 2),IR(51993, 26),IR(1, 0)}, // PushConstantNumWorkgroups in nonsemantic_clspvreflection
    {20,IR(36, 2),IR(52019, 30),IR(1, 0)}, // PushConstantRegionGroupOffset in nonsemantic_clspvreflection
    {21,IR(33, 3),IR(52049, 26),IR(1, 0)}, // ConstantDataStorageBuffer in nonsemantic_clspvreflection
    {22,IR(33, 3),IR(52075, 20),IR(1, 0)}, // ConstantDataUniform in nonsemantic_clspvreflection
    {23,IR(33, 3),IR(8802, 15),IR(1, 0)}, // LiteralSampler in nonsemantic_clspvreflection
    {24,IR(296, 4),IR(52095, 30),IR(1, 0)}, // PropertyRequiredWorkgroupSize in nonsemantic_clspvreflection
    {25,IR(10, 1),IR(52125, 28),IR(1, 0)}, // SpecConstantSubgroupMaxSize in nonsemantic_clspvreflection
    {26,IR(916, 5),IR(52153, 28),IR(1, 0)}, // ArgumentPointerPushConstant in nonsemantic_clspvreflection
    {27,IR(554, 7),IR(52181, 23),IR(1, 0)}, // ArgumentPointerUniform in nonsemantic_clspvreflection
    {28,IR(33, 3),IR(52204, 35),IR(1, 0)}, // ProgramScopeVariablesStorageBuffer in nonsemantic_clspvreflection
    {29,IR(33, 3),IR(52239, 38),IR(1, 0)}, // ProgramScopeVariablePointerRelocation in nonsemantic_clspvreflection
    {30,IR(296, 4),IR(52277, 42),IR(1, 0)}, // ImageArgumentInfoChannelOrderPushConstant in nonsemantic_clspvreflection
    {31,IR(296, 4),IR(52319, 45),IR(1, 0)}, // ImageArgumentInfoChannelDataTypePushConstant in nonsemantic_clspvreflection
    {32,IR(525, 6),IR(52364, 37),IR(1, 0)}, // ImageArgumentInfoChannelOrderUniform in nonsemantic_clspvreflection
    {33,IR(525, 6),IR(52401, 40),IR(1, 0)}, // ImageArgumentInfoChannelDataTypeUniform in nonsemantic_clspvreflection
    {34,IR(916, 5),IR(52441, 27),IR(1, 0)}, // ArgumentStorageTexelBuffer in nonsemantic_clspvreflection
    {35,IR(916, 5),IR(52468, 27),IR(1, 0)}, // ArgumentUniformTexelBuffer in nonsemantic_clspvreflection
    {36,IR(33, 3),IR(52495, 32),IR(1, 0)}, // ConstantDataPointerPushConstant in nonsemantic_clspvreflection
    {37,IR(33, 3),IR(52527, 40),IR(1, 0)}, // ProgramScopeVariablePointerPushConstant in nonsemantic_clspvreflection
    {38,IR(375, 3),IR(52567, 11),IR(1, 0)}, // PrintfInfo in nonsemantic_clspvreflection
    {39,IR(33, 3),IR(52578, 26),IR(1, 0)}, // PrintfBufferStorageBuffer in nonsemantic_clspvreflection
    {40,IR(33, 3),IR(52604, 32),IR(1, 0)}, // PrintfBufferPointerPushConstant in nonsemantic_clspvreflection
    {41,IR(296, 4),IR(52636, 34),IR(1, 0)}, // NormalizedSamplerMaskPushConstant in nonsemantic_clspvreflection
    {42,IR(36, 2),IR(52670, 22),IR(1, 0)}, // WorkgroupVariableSize in nonsemantic_clspvreflection
    {0,IR(0, 0),IR(50094, 14),IR(1, 0)}, // DebugInfoNone in nonsemantic_shader_debuginfo_100
    {1,IR(296, 4),IR(50108, 21),IR(1, 0)}, // DebugCompilationUnit in nonsemantic_shader_debuginfo_100
    {2,IR(296, 4),IR(50181, 15),IR(1, 0)}, // DebugTypeBasic in nonsemantic_shader_debuginfo_100
    {3,IR(33, 3),IR(50230, 17),IR(1, 0)}, // DebugTypePointer in nonsemantic_shader_debuginfo_100
    {4,IR(36, 2),IR(50285, 19),IR(1, 0)}, // DebugTypeQualifier in nonsemantic_shader_debuginfo_100
    {5,IR(168, 2),IR(50304, 15),IR(1, 0)}, // DebugTypeArray in nonsemantic_shader_debuginfo_100
    {6,IR(36, 2),IR(50319, 16),IR(1, 0)}, // DebugTypeVector in nonsemantic_shader_debuginfo_100
    {7,IR(525, 6),IR(50335, 13),IR(1, 0)}, // DebugTypedef in nonsemantic_shader_debuginfo_100
    {8,IR(375, 3),IR(50348, 18),IR(1, 0)}, // DebugTypeFunction in nonsemantic_shader_debuginfo_100
    {9,IR(921, 9),IR(50366, 14),IR(1, 0)}, // DebugTypeEnum in nonsemantic_shader_debuginfo_100
    {10,IR(930, 10),IR(50418, 19),IR(1, 0)}, // DebugTypeComposite in nonsemantic_shader_debuginfo_100
    {11,IR(940, 9),IR(50437, 16),IR(1, 0)}, // DebugTypeMember in nonsemantic_shader_debuginfo_100
    {12,IR(296, 4),IR(50453, 21),IR(1, 0)}, // DebugTypeInheritance in nonsemantic_shader_debuginfo_100
    {13,IR(36, 2),IR(50474, 21),IR(1, 0)}, // DebugTypePtrToMember in nonsemantic_shader_debuginfo_100
    {14,IR(168, 2),IR(50495, 18),IR(1, 0)}, // DebugTypeTemplate in nonsemantic_shader_debuginfo_100
    {15,IR(525, 6),IR(50513, 27),IR(1, 0)}, // DebugTypeTemplateParameter in nonsemantic_shader_debuginfo_100
    {16,IR(667, 5),IR(50540, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in nonsemantic_shader_debuginfo_100
    {17,IR(949, 5),IR(50575, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in nonsemantic_shader_debuginfo_100
    {18,IR(954, 10),IR(50606, 20),IR(1, 0)}, // DebugGlobalVariable in nonsemantic_shader_debuginfo_100
    {19,IR(471, 8),IR(50626, 25),IR(1, 0)}, // DebugFunctionDeclaration in nonsemantic_shader_debuginfo_100
    {20,IR(954, 10),IR(50651, 14),IR(1, 0)}, // DebugFunction in nonsemantic_shader_debuginfo_100
    {21,IR(916, 5),IR(50665, 18),IR(1, 0)}, // DebugLexicalBlock in nonsemantic_shader_debuginfo_100
    {22,IR(33, 3),IR(50683, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in nonsemantic_shader_debuginfo_100
    {23,IR(893, 2),IR(50714, 11),IR(1, 0)}, // DebugScope in nonsemantic_shader_debuginfo_100
    {24,IR(0, 0),IR(50725, 13),IR(1, 0)}, // DebugNoScope in nonsemantic_shader_debuginfo_100
    {25,IR(964, 3),IR(50738, 15),IR(1, 0)}, // DebugInlinedAt in nonsemantic_shader_debuginfo_100
    {26,IR(967, 8),IR(50795, 19),IR(1, 0)}, // DebugLocalVariable in nonsemantic_shader_debuginfo_100
    {27,IR(36, 2),IR(50814, 21),IR(1, 0)}, // DebugInlinedVariable in nonsemantic_shader_debuginfo_100
    {28,IR(975, 4),IR(50835, 13),IR(1, 0)}, // DebugDeclare in nonsemantic_shader_debuginfo_100
    {29,IR(975, 4),IR(50848, 11),IR(1, 0)}, // DebugValue in nonsemantic_shader_debuginfo_100
    {30,IR(168, 2),IR(50892, 15),IR(1, 0)}, // DebugOperation in nonsemantic_shader_debuginfo_100
    {31,IR(739, 1),IR(50907, 16),IR(1, 0)}, // DebugExpression in nonsemantic_shader_debuginfo_100
    {32,IR(577, 4),IR(50923, 14),IR(1, 0)}, // DebugMacroDef in nonsemantic_shader_debuginfo_100
    {33,IR(33, 3),IR(50937, 16),IR(1, 0)}, // DebugMacroUndef in nonsemantic_shader_debuginfo_100
    {34,IR(506, 7),IR(52692, 20),IR(1, 0)}, // DebugImportedEntity in nonsemantic_shader_debuginfo_100
    {35,IR(893, 2),IR(52712, 12),IR(1, 0)}, // DebugSource in nonsemantic_shader_debuginfo_100
    {101,IR(36, 2),IR(52724, 24),IR(1, 0)}, // DebugFunctionDefinition in nonsemantic_shader_debuginfo_100
    {102,IR(10, 1),IR(52748, 21),IR(1, 0)}, // DebugSourceContinued in nonsemantic_shader_debuginfo_100
    {103,IR(667, 5),IR(52769, 10),IR(1, 0)}, // DebugLine in nonsemantic_shader_debuginfo_100
    {104,IR(0, 0),IR(52779, 12),IR(1, 0)}, // DebugNoLine in nonsemantic_shader_debuginfo_100
    {105,IR(36, 2),IR(52791, 21),IR(1, 0)}, // DebugBuildIdentifier in nonsemantic_shader_debuginfo_100
    {106,IR(10, 1),IR(52812, 17),IR(1, 0)}, // DebugStoragePath in nonsemantic_shader_debuginfo_100
    {107,IR(296, 4),IR(52829, 16),IR(1, 0)}, // DebugEntryPoint in nonsemantic_shader_debuginfo_100
    {108,IR(33, 3),IR(52845, 16),IR(1, 0)}, // DebugTypeMatrix in nonsemantic_shader_debuginfo_100
    {1,IR(757, 9),IR(52861, 14),IR(1, 0)}, // Configuration in nonsemantic_vkspreflection
    {2,IR(10, 1),IR(52875, 13),IR(1, 0)}, // StartCounter in nonsemantic_vkspreflection
    {3,IR(10, 1),IR(52888, 12),IR(1, 0)}, // StopCounter in nonsemantic_vkspreflection
    {4,IR(296, 4),IR(52900, 14),IR(1, 0)}, // PushConstants in nonsemantic_vkspreflection
    {5,IR(33, 3),IR(52914, 23),IR(1, 0)}, // SpecializationMapEntry in nonsemantic_vkspreflection
    {6,IR(979, 15),IR(52937, 20),IR(1, 0)}, // DescriptorSetBuffer in nonsemantic_vkspreflection
    {7,IR(994, 33),IR(52957, 19),IR(1, 0)}, // DescriptorSetImage in nonsemantic_vkspreflection
    {8,IR(1027, 19),IR(52976, 21),IR(1, 0)}, // DescriptorSetSampler in nonsemantic_vkspreflection
    {0,IR(0, 0),IR(50094, 14),IR(1, 0)}, // DebugInfoNone in opencl_debuginfo_100
    {1,IR(1046, 4),IR(50108, 21),IR(1, 0)}, // DebugCompilationUnit in opencl_debuginfo_100
    {2,IR(1050, 3),IR(50181, 15),IR(1, 0)}, // DebugTypeBasic in opencl_debuginfo_100
    {3,IR(1053, 3),IR(50230, 17),IR(1, 0)}, // DebugTypePointer in opencl_debuginfo_100
    {4,IR(1056, 2),IR(50285, 19),IR(1, 0)}, // DebugTypeQualifier in opencl_debuginfo_100
    {5,IR(168, 2),IR(50304, 15),IR(1, 0)}, // DebugTypeArray in opencl_debuginfo_100
    {6,IR(261, 2),IR(50319, 16),IR(1, 0)}, // DebugTypeVector in opencl_debuginfo_100
    {7,IR(811, 6),IR(50335, 13),IR(1, 0)}, // DebugTypedef in opencl_debuginfo_100
    {8,IR(1058, 3),IR(50348, 18),IR(1, 0)}, // DebugTypeFunction in opencl_debuginfo_100
    {9,IR(1061, 9),IR(50366, 14),IR(1, 0)}, // DebugTypeEnum in opencl_debuginfo_100
    {10,IR(1070, 10),IR(50418, 19),IR(1, 0)}, // DebugTypeComposite in opencl_debuginfo_100
    {11,IR(1080, 10),IR(50437, 16),IR(1, 0)}, // DebugTypeMember in opencl_debuginfo_100
    {12,IR(1090, 5),IR(50453, 21),IR(1, 0)}, // DebugTypeInheritance in opencl_debuginfo_100
    {13,IR(36, 2),IR(50474, 21),IR(1, 0)}, // DebugTypePtrToMember in opencl_debuginfo_100
    {14,IR(168, 2),IR(50495, 18),IR(1, 0)}, // DebugTypeTemplate in opencl_debuginfo_100
    {15,IR(850, 6),IR(50513, 27),IR(1, 0)}, // DebugTypeTemplateParameter in opencl_debuginfo_100
    {16,IR(856, 5),IR(50540, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in opencl_debuginfo_100
    {17,IR(861, 5),IR(50575, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in opencl_debuginfo_100
    {18,IR(1080, 10),IR(50606, 20),IR(1, 0)}, // DebugGlobalVariable in opencl_debuginfo_100
    {19,IR(1095, 8),IR(50626, 25),IR(1, 0)}, // DebugFunctionDeclaration in opencl_debuginfo_100
    {20,IR(1103, 11),IR(50651, 14),IR(1, 0)}, // DebugFunction in opencl_debuginfo_100
    {21,IR(885, 5),IR(50665, 18),IR(1, 0)}, // DebugLexicalBlock in opencl_debuginfo_100
    {22,IR(890, 3),IR(50683, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in opencl_debuginfo_100
    {23,IR(893, 2),IR(50714, 11),IR(1, 0)}, // DebugScope in opencl_debuginfo_100
    {24,IR(0, 0),IR(50725, 13),IR(1, 0)}, // DebugNoScope in opencl_debuginfo_100
    {25,IR(895, 3),IR(50738, 15),IR(1, 0)}, // DebugInlinedAt in opencl_debuginfo_100
    {26,IR(1114, 8),IR(50795, 19),IR(1, 0)}, // DebugLocalVariable in opencl_debuginfo_100
    {27,IR(36, 2),IR(50814, 21),IR(1, 0)}, // DebugInlinedVariable in opencl_debuginfo_100
    {28,IR(33, 3),IR(50835, 13),IR(1, 0)}, // DebugDeclare in opencl_debuginfo_100
    {29,IR(975, 4),IR(50848, 11),IR(1, 0)}, // DebugValue in opencl_debuginfo_100
    {30,IR(1122, 2),IR(50892, 15),IR(1, 0)}, // DebugOperation in opencl_debuginfo_100
    {31,IR(739, 1),IR(50907, 16),IR(1, 0)}, // DebugExpression in opencl_debuginfo_100
    {32,IR(907, 4),IR(50923, 14),IR(1, 0)}, // DebugMacroDef in opencl_debuginfo_100
    {33,IR(890, 3),IR(50937, 16),IR(1, 0)}, // DebugMacroUndef in opencl_debuginfo_100
    {34,IR(1124, 7),IR(52692, 20),IR(1, 0)}, // DebugImportedEntity in opencl_debuginfo_100
    {35,IR(893, 2),IR(52712, 12),IR(1, 0)}, // DebugSource in opencl_debuginfo_100
    {36,IR(1131, 8),IR(53297, 17),IR(1, 0)}, // DebugModuleINTEL in opencl_debuginfo_100
    {0,IR(10, 1),IR(53314, 5),IR(1, 0)}, // acos in opencl_std_100
    {1,IR(10, 1),IR(53319, 6),IR(1, 0)}, // acosh in opencl_std_100
    {2,IR(10, 1),IR(53325, 7),IR(1, 0)}, // acospi in opencl_std_100
    {3,IR(10, 1),IR(53332, 5),IR(1, 0)}, // asin in opencl_std_100
    {4,IR(10, 1),IR(53337, 6),IR(1, 0)}, // asinh in opencl_std_100
    {5,IR(10, 1),IR(53343, 7),IR(1, 0)}, // asinpi in opencl_std_100
    {6,IR(10, 1),IR(53350, 5),IR(1, 0)}, // atan in opencl_std_100
    {7,IR(36, 2),IR(53355, 6),IR(1, 0)}, // atan2 in opencl_std_100
    {8,IR(10, 1),IR(53361, 6),IR(1, 0)}, // atanh in opencl_std_100
    {9,IR(10, 1),IR(53367, 7),IR(1, 0)}, // atanpi in opencl_std_100
    {10,IR(36, 2),IR(53374, 8),IR(1, 0)}, // atan2pi in opencl_std_100
    {11,IR(10, 1),IR(53382, 5),IR(1, 0)}, // cbrt in opencl_std_100
    {12,IR(10, 1),IR(53387, 5),IR(1, 0)}, // ceil in opencl_std_100
    {13,IR(36, 2),IR(53392, 9),IR(1, 0)}, // copysign in opencl_std_100
    {14,IR(10, 1),IR(53401, 4),IR(1, 0)}, // cos in opencl_std_100
    {15,IR(10, 1),IR(53405, 5),IR(1, 0)}, // cosh in opencl_std_100
    {16,IR(10, 1),IR(53410, 6),IR(1, 0)}, // cospi in opencl_std_100
    {17,IR(10, 1),IR(53416, 5),IR(1, 0)}, // erfc in opencl_std_100
    {18,IR(10, 1),IR(53421, 4),IR(1, 0)}, // erf in opencl_std_100
    {19,IR(10, 1),IR(53425, 4),IR(1, 0)}, // exp in opencl_std_100
    {20,IR(10, 1),IR(53429, 5),IR(1, 0)}, // exp2 in opencl_std_100
    {21,IR(10, 1),IR(53434, 6),IR(1, 0)}, // exp10 in opencl_std_100
    {22,IR(10, 1),IR(53440, 6),IR(1, 0)}, // expm1 in opencl_std_100
    {23,IR(10, 1),IR(53446, 5),IR(1, 0)}, // fabs in opencl_std_100
    {24,IR(36, 2),IR(53451, 5),IR(1, 0)}, // fdim in opencl_std_100
    {25,IR(10, 1),IR(53456, 6),IR(1, 0)}, // floor in opencl_std_100
    {26,IR(33, 3),IR(53462, 4),IR(1, 0)}, // fma in opencl_std_100
    {27,IR(36, 2),IR(53466, 5),IR(1, 0)}, // fmax in opencl_std_100
    {28,IR(36, 2),IR(53471, 5),IR(1, 0)}, // fmin in opencl_std_100
    {29,IR(36, 2),IR(53476, 5),IR(1, 0)}, // fmod in opencl_std_100
    {30,IR(36, 2),IR(53481, 6),IR(1, 0)}, // fract in opencl_std_100
    {31,IR(36, 2),IR(53487, 6),IR(1, 0)}, // frexp in opencl_std_100
    {32,IR(36, 2),IR(53493, 6),IR(1, 0)}, // hypot in opencl_std_100
    {33,IR(10, 1),IR(53499, 6),IR(1, 0)}, // ilogb in opencl_std_100
    {34,IR(36, 2),IR(53505, 6),IR(1, 0)}, // ldexp in opencl_std_100
    {35,IR(10, 1),IR(53511, 7),IR(1, 0)}, // lgamma in opencl_std_100
    {36,IR(36, 2),IR(53518, 9),IR(1, 0)}, // lgamma_r in opencl_std_100
    {37,IR(10, 1),IR(53527, 4),IR(1, 0)}, // log in opencl_std_100
    {38,IR(10, 1),IR(53531, 5),IR(1, 0)}, // log2 in opencl_std_100
    {39,IR(10, 1),IR(53536, 6),IR(1, 0)}, // log10 in opencl_std_100
    {40,IR(10, 1),IR(53542, 6),IR(1, 0)}, // log1p in opencl_std_100
    {41,IR(10, 1),IR(53548, 5),IR(1, 0)}, // logb in opencl_std_100
    {42,IR(33, 3),IR(53553, 4),IR(1, 0)}, // mad in opencl_std_100
    {43,IR(36, 2),IR(53557, 7),IR(1, 0)}, // maxmag in opencl_std_100
    {44,IR(36, 2),IR(53564, 7),IR(1, 0)}, // minmag in opencl_std_100
    {45,IR(36, 2),IR(53571, 5),IR(1, 0)}, // modf in opencl_std_100
    {46,IR(10, 1),IR(53576, 4),IR(1, 0)}, // nan in opencl_std_100
    {47,IR(36, 2),IR(53580, 10),IR(1, 0)}, // nextafter in opencl_std_100
    {48,IR(36, 2),IR(53590, 4),IR(1, 0)}, // pow in opencl_std_100
    {49,IR(36, 2),IR(53594, 5),IR(1, 0)}, // pown in opencl_std_100
    {50,IR(36, 2),IR(53599, 5),IR(1, 0)}, // powr in opencl_std_100
    {51,IR(36, 2),IR(53604, 10),IR(1, 0)}, // remainder in opencl_std_100
    {52,IR(33, 3),IR(53614, 7),IR(1, 0)}, // remquo in opencl_std_100
    {53,IR(10, 1),IR(53621, 5),IR(1, 0)}, // rint in opencl_std_100
    {54,IR(36, 2),IR(53626, 6),IR(1, 0)}, // rootn in opencl_std_100
    {55,IR(10, 1),IR(53632, 6),IR(1, 0)}, // round in opencl_std_100
    {56,IR(10, 1),IR(53638, 6),IR(1, 0)}, // rsqrt in opencl_std_100
    {57,IR(10, 1),IR(53644, 4),IR(1, 0)}, // sin in opencl_std_100
    {58,IR(36, 2),IR(53648, 7),IR(1, 0)}, // sincos in opencl_std_100
    {59,IR(10, 1),IR(53655, 5),IR(1, 0)}, // sinh in opencl_std_100
    {60,IR(10, 1),IR(53660, 6),IR(1, 0)}, // sinpi in opencl_std_100
    {61,IR(10, 1),IR(53666, 5),IR(1, 0)}, // sqrt in opencl_std_100
    {62,IR(10, 1),IR(53671, 4),IR(1, 0)}, // tan in opencl_std_100
    {63,IR(10, 1),IR(53675, 5),IR(1, 0)}, // tanh in opencl_std_100
    {64,IR(10, 1),IR(53680, 6),IR(1, 0)}, // tanpi in opencl_std_100
    {65,IR(10, 1),IR(53686, 7),IR(1, 0)}, // tgamma in opencl_std_100
    {66,IR(10, 1),IR(53693, 6),IR(1, 0)}, // trunc in opencl_std_100
    {67,IR(10, 1),IR(53699, 9),IR(1, 0)}, // half_cos in opencl_std_100
    {68,IR(36, 2),IR(53708, 12),IR(1, 0)}, // half_divide in opencl_std_100
    {69,IR(10, 1),IR(53720, 9),IR(1, 0)}, // half_exp in opencl_std_100
    {70,IR(10, 1),IR(53729, 10),IR(1, 0)}, // half_exp2 in opencl_std_100
    {71,IR(10, 1),IR(53739, 11),IR(1, 0)}, // half_exp10 in opencl_std_100
    {72,IR(10, 1),IR(53750, 9),IR(1, 0)}, // half_log in opencl_std_100
    {73,IR(10, 1),IR(53759, 10),IR(1, 0)}, // half_log2 in opencl_std_100
    {74,IR(10, 1),IR(53769, 11),IR(1, 0)}, // half_log10 in opencl_std_100
    {75,IR(36, 2),IR(53780, 10),IR(1, 0)}, // half_powr in opencl_std_100
    {76,IR(10, 1),IR(53790, 11),IR(1, 0)}, // half_recip in opencl_std_100
    {77,IR(10, 1),IR(53801, 11),IR(1, 0)}, // half_rsqrt in opencl_std_100
    {78,IR(10, 1),IR(53812, 9),IR(1, 0)}, // half_sin in opencl_std_100
    {79,IR(10, 1),IR(53821, 10),IR(1, 0)}, // half_sqrt in opencl_std_100
    {80,IR(10, 1),IR(53831, 9),IR(1, 0)}, // half_tan in opencl_std_100
    {81,IR(10, 1),IR(53840, 11),IR(1, 0)}, // native_cos in opencl_std_100
    {82,IR(36, 2),IR(53851, 14),IR(1, 0)}, // native_divide in opencl_std_100
    {83,IR(10, 1),IR(53865, 11),IR(1, 0)}, // native_exp in opencl_std_100
    {84,IR(10, 1),IR(53876, 12),IR(1, 0)}, // native_exp2 in opencl_std_100
    {85,IR(10, 1),IR(53888, 13),IR(1, 0)}, // native_exp10 in opencl_std_100
    {86,IR(10, 1),IR(53901, 11),IR(1, 0)}, // native_log in opencl_std_100
    {87,IR(10, 1),IR(53912, 12),IR(1, 0)}, // native_log2 in opencl_std_100
    {88,IR(10, 1),IR(53924, 13),IR(1, 0)}, // native_log10 in opencl_std_100
    {89,IR(36, 2),IR(53937, 12),IR(1, 0)}, // native_powr in opencl_std_100
    {90,IR(10, 1),IR(53949, 13),IR(1, 0)}, // native_recip in opencl_std_100
    {91,IR(10, 1),IR(53962, 13),IR(1, 0)}, // native_rsqrt in opencl_std_100
    {92,IR(10, 1),IR(53975, 11),IR(1, 0)}, // native_sin in opencl_std_100
    {93,IR(10, 1),IR(53986, 12),IR(1, 0)}, // native_sqrt in opencl_std_100
    {94,IR(10, 1),IR(53998, 11),IR(1, 0)}, // native_tan in opencl_std_100
    {95,IR(33, 3),IR(54009, 7),IR(1, 0)}, // fclamp in opencl_std_100
    {96,IR(10, 1),IR(54016, 8),IR(1, 0)}, // degrees in opencl_std_100
    {97,IR(36, 2),IR(54024, 12),IR(1, 0)}, // fmax_common in opencl_std_100
    {98,IR(36, 2),IR(54036, 12),IR(1, 0)}, // fmin_common in opencl_std_100
    {99,IR(33, 3),IR(54048, 4),IR(1, 0)}, // mix in opencl_std_100
    {100,IR(10, 1),IR(54052, 8),IR(1, 0)}, // radians in opencl_std_100
    {101,IR(36, 2),IR(54060, 5),IR(1, 0)}, // step in opencl_std_100
    {102,IR(33, 3),IR(54065, 11),IR(1, 0)}, // smoothstep in opencl_std_100
    {103,IR(10, 1),IR(54076, 5),IR(1, 0)}, // sign in opencl_std_100
    {104,IR(36, 2),IR(54081, 6),IR(1, 0)}, // cross in opencl_std_100
    {105,IR(36, 2),IR(54087, 9),IR(1, 0)}, // distance in opencl_std_100
    {106,IR(10, 1),IR(54096, 7),IR(1, 0)}, // length in opencl_std_100
    {107,IR(10, 1),IR(54103, 10),IR(1, 0)}, // normalize in opencl_std_100
    {108,IR(36, 2),IR(54113, 14),IR(1, 0)}, // fast_distance in opencl_std_100
    {109,IR(10, 1),IR(54127, 12),IR(1, 0)}, // fast_length in opencl_std_100
    {110,IR(10, 1),IR(54139, 15),IR(1, 0)}, // fast_normalize in opencl_std_100
    {141,IR(10, 1),IR(54154, 6),IR(1, 0)}, // s_abs in opencl_std_100
    {142,IR(36, 2),IR(54160, 11),IR(1, 0)}, // s_abs_diff in opencl_std_100
    {143,IR(36, 2),IR(54171, 10),IR(1, 0)}, // s_add_sat in opencl_std_100
    {144,IR(36, 2),IR(54181, 10),IR(1, 0)}, // u_add_sat in opencl_std_100
    {145,IR(36, 2),IR(54191, 7),IR(1, 0)}, // s_hadd in opencl_std_100
    {146,IR(36, 2),IR(54198, 7),IR(1, 0)}, // u_hadd in opencl_std_100
    {147,IR(36, 2),IR(54205, 8),IR(1, 0)}, // s_rhadd in opencl_std_100
    {148,IR(36, 2),IR(54213, 8),IR(1, 0)}, // u_rhadd in opencl_std_100
    {149,IR(33, 3),IR(54221, 8),IR(1, 0)}, // s_clamp in opencl_std_100
    {150,IR(33, 3),IR(54229, 8),IR(1, 0)}, // u_clamp in opencl_std_100
    {151,IR(10, 1),IR(54237, 4),IR(1, 0)}, // clz in opencl_std_100
    {152,IR(10, 1),IR(54241, 4),IR(1, 0)}, // ctz in opencl_std_100
    {153,IR(33, 3),IR(54245, 9),IR(1, 0)}, // s_mad_hi in opencl_std_100
    {154,IR(33, 3),IR(54254, 10),IR(1, 0)}, // u_mad_sat in opencl_std_100
    {155,IR(33, 3),IR(54264, 10),IR(1, 0)}, // s_mad_sat in opencl_std_100
    {156,IR(36, 2),IR(54274, 6),IR(1, 0)}, // s_max in opencl_std_100
    {157,IR(36, 2),IR(54280, 6),IR(1, 0)}, // u_max in opencl_std_100
    {158,IR(36, 2),IR(54286, 6),IR(1, 0)}, // s_min in opencl_std_100
    {159,IR(36, 2),IR(54292, 6),IR(1, 0)}, // u_min in opencl_std_100
    {160,IR(36, 2),IR(54298, 9),IR(1, 0)}, // s_mul_hi in opencl_std_100
    {161,IR(36, 2),IR(54307, 7),IR(1, 0)}, // rotate in opencl_std_100
    {162,IR(36, 2),IR(54314, 10),IR(1, 0)}, // s_sub_sat in opencl_std_100
    {163,IR(36, 2),IR(54324, 10),IR(1, 0)}, // u_sub_sat in opencl_std_100
    {164,IR(36, 2),IR(54334, 11),IR(1, 0)}, // u_upsample in opencl_std_100
    {165,IR(36, 2),IR(54345, 11),IR(1, 0)}, // s_upsample in opencl_std_100
    {166,IR(10, 1),IR(54356, 9),IR(1, 0)}, // popcount in opencl_std_100
    {167,IR(33, 3),IR(54365, 8),IR(1, 0)}, // s_mad24 in opencl_std_100
    {168,IR(33, 3),IR(54373, 8),IR(1, 0)}, // u_mad24 in opencl_std_100
    {169,IR(36, 2),IR(54381, 8),IR(1, 0)}, // s_mul24 in opencl_std_100
    {170,IR(36, 2),IR(54389, 8),IR(1, 0)}, // u_mul24 in opencl_std_100
    {171,IR(1139, 3),IR(54397, 7),IR(1, 0)}, // vloadn in opencl_std_100
    {172,IR(33, 3),IR(54404, 8),IR(1, 0)}, // vstoren in opencl_std_100
    {173,IR(36, 2),IR(54412, 11),IR(1, 0)}, // vload_half in opencl_std_100
    {174,IR(1139, 3),IR(54423, 12),IR(1, 0)}, // vload_halfn in opencl_std_100
    {175,IR(33, 3),IR(54435, 12),IR(1, 0)}, // vstore_half in opencl_std_100
    {176,IR(1142, 4),IR(54447, 14),IR(1, 0)}, // vstore_half_r in opencl_std_100
    {177,IR(33, 3),IR(54461, 13),IR(1, 0)}, // vstore_halfn in opencl_std_100
    {178,IR(1142, 4),IR(54474, 15),IR(1, 0)}, // vstore_halfn_r in opencl_std_100
    {179,IR(1139, 3),IR(54489, 13),IR(1, 0)}, // vloada_halfn in opencl_std_100
    {180,IR(33, 3),IR(54502, 14),IR(1, 0)}, // vstorea_halfn in opencl_std_100
    {181,IR(1142, 4),IR(54516, 16),IR(1, 0)}, // vstorea_halfn_r in opencl_std_100
    {182,IR(36, 2),IR(54532, 8),IR(1, 0)}, // shuffle in opencl_std_100
    {183,IR(33, 3),IR(54540, 9),IR(1, 0)}, // shuffle2 in opencl_std_100
    {184,IR(168, 2),IR(54549, 7),IR(1, 0)}, // printf in opencl_std_100
    {185,IR(36, 2),IR(54556, 9),IR(1, 0)}, // prefetch in opencl_std_100
    {186,IR(33, 3),IR(54565, 10),IR(1, 0)}, // bitselect in opencl_std_100
    {187,IR(33, 3),IR(54575, 7),IR(1, 0)}, // select in opencl_std_100
    {201,IR(10, 1),IR(54582, 6),IR(1, 0)}, // u_abs in opencl_std_100
    {202,IR(36, 2),IR(54588, 11),IR(1, 0)}, // u_abs_diff in opencl_std_100
    {203,IR(36, 2),IR(54599, 9),IR(1, 0)}, // u_mul_hi in opencl_std_100
    {204,IR(33, 3),IR(54608, 9),IR(1, 0)}, // u_mad_hi in opencl_std_100
    {1,IR(10, 1),IR(54617, 17),IR(1, 0)}, // CubeFaceIndexAMD in spv_amd_gcn_shader
    {2,IR(10, 1),IR(54634, 17),IR(1, 0)}, // CubeFaceCoordAMD in spv_amd_gcn_shader
    {3,IR(0, 0),IR(54651, 8),IR(1, 0)}, // TimeAMD in spv_amd_gcn_shader
    {1,IR(36, 2),IR(54659, 22),IR(1, 0)}, // SwizzleInvocationsAMD in spv_amd_shader_ballot
    {2,IR(36, 2),IR(54681, 28),IR(1, 0)}, // SwizzleInvocationsMaskedAMD in spv_amd_shader_ballot
    {3,IR(33, 3),IR(54709, 19),IR(1, 0)}, // WriteInvocationAMD in spv_amd_shader_ballot
    {4,IR(10, 1),IR(54728, 9),IR(1, 0)}, // MbcntAMD in spv_amd_shader_ballot
    {1,IR(36, 2),IR(54737, 23),IR(1, 0)}, // InterpolateAtVertexAMD in spv_amd_shader_explicit_vertex_parameter
    {1,IR(33, 3),IR(54760, 9),IR(1, 0)}, // FMin3AMD in spv_amd_shader_trinary_minmax
    {2,IR(33, 3),IR(54769, 9),IR(1, 0)}, // UMin3AMD in spv_amd_shader_trinary_minmax
    {3,IR(33, 3),IR(54778, 9),IR(1, 0)}, // SMin3AMD in spv_amd_shader_trinary_minmax
    {4,IR(33, 3),IR(54787, 9),IR(1, 0)}, // FMax3AMD in spv_amd_shader_trinary_minmax
    {5,IR(33, 3),IR(54796, 9),IR(1, 0)}, // UMax3AMD in spv_amd_shader_trinary_minmax
    {6,IR(33, 3),IR(54805, 9),IR(1, 0)}, // SMax3AMD in spv_amd_shader_trinary_minmax
    {7,IR(33, 3),IR(54814, 9),IR(1, 0)}, // FMid3AMD in spv_amd_shader_trinary_minmax
    {8,IR(33, 3),IR(54823, 9),IR(1, 0)}, // UMid3AMD in spv_amd_shader_trinary_minmax
    {9,IR(33, 3),IR(54832, 9),IR(1, 0)}, // SMid3AMD in spv_amd_shader_trinary_minmax
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
    {IR(50108, 21), 1}, // DebugCompilationUnit in debuginfo
    {IR(50835, 13), 28}, // DebugDeclare in debuginfo
    {IR(50907, 16), 31}, // DebugExpression in debuginfo
    {IR(50651, 14), 20}, // DebugFunction in debuginfo
    {IR(50626, 25), 19}, // DebugFunctionDeclaration in debuginfo
    {IR(50606, 20), 18}, // DebugGlobalVariable in debuginfo
    {IR(50094, 14), 0}, // DebugInfoNone in debuginfo
    {IR(50738, 15), 25}, // DebugInlinedAt in debuginfo
    {IR(50814, 21), 27}, // DebugInlinedVariable in debuginfo
    {IR(50665, 18), 21}, // DebugLexicalBlock in debuginfo
    {IR(50683, 31), 22}, // DebugLexicalBlockDiscriminator in debuginfo
    {IR(50795, 19), 26}, // DebugLocalVariable in debuginfo
    {IR(50923, 14), 32}, // DebugMacroDef in debuginfo
    {IR(50937, 16), 33}, // DebugMacroUndef in debuginfo
    {IR(50725, 13), 24}, // DebugNoScope in debuginfo
    {IR(50892, 15), 30}, // DebugOperation in debuginfo
    {IR(50714, 11), 23}, // DebugScope in debuginfo
    {IR(50304, 15), 5}, // DebugTypeArray in debuginfo
    {IR(50181, 15), 2}, // DebugTypeBasic in debuginfo
    {IR(50418, 19), 10}, // DebugTypeComposite in debuginfo
    {IR(50366, 14), 9}, // DebugTypeEnum in debuginfo
    {IR(50348, 18), 8}, // DebugTypeFunction in debuginfo
    {IR(50453, 21), 12}, // DebugTypeInheritance in debuginfo
    {IR(50437, 16), 11}, // DebugTypeMember in debuginfo
    {IR(50230, 17), 3}, // DebugTypePointer in debuginfo
    {IR(50474, 21), 13}, // DebugTypePtrToMember in debuginfo
    {IR(50285, 19), 4}, // DebugTypeQualifier in debuginfo
    {IR(50495, 18), 14}, // DebugTypeTemplate in debuginfo
    {IR(50513, 27), 15}, // DebugTypeTemplateParameter in debuginfo
    {IR(50575, 31), 17}, // DebugTypeTemplateParameterPack in debuginfo
    {IR(50540, 35), 16}, // DebugTypeTemplateTemplateParameter in debuginfo
    {IR(50319, 16), 6}, // DebugTypeVector in debuginfo
    {IR(50335, 13), 7}, // DebugTypedef in debuginfo
    {IR(50848, 11), 29}, // DebugValue in debuginfo
    {IR(51047, 5), 50}, // Acos in glsl_std_450
    {IR(51078, 6), 56}, // Acosh in glsl_std_450
    {IR(51042, 5), 49}, // Asin in glsl_std_450
    {IR(51072, 6), 55}, // Asinh in glsl_std_450
    {IR(51052, 5), 51}, // Atan in glsl_std_450
    {IR(51090, 6), 58}, // Atan2 in glsl_std_450
    {IR(51084, 6), 57}, // Atanh in glsl_std_450
    {IR(51003, 5), 42}, // Ceil in glsl_std_450
    {IR(51034, 4), 47}, // Cos in glsl_std_450
    {IR(51062, 5), 53}, // Cosh in glsl_std_450
    {IR(51474, 6), 101}, // Cross in glsl_std_450
    {IR(51022, 8), 45}, // Degrees in glsl_std_450
    {IR(51135, 12), 66}, // Determinant in glsl_std_450
    {IR(51465, 9), 100}, // Distance in glsl_std_450
    {IR(51100, 4), 60}, // Exp in glsl_std_450
    {IR(51108, 5), 62}, // Exp2 in glsl_std_450
    {IR(50975, 5), 37}, // FAbs in glsl_std_450
    {IR(51207, 7), 76}, // FClamp in glsl_std_450
    {IR(51192, 5), 73}, // FMax in glsl_std_450
    {IR(51177, 5), 70}, // FMin in glsl_std_450
    {IR(51228, 5), 79}, // FMix in glsl_std_450
    {IR(50985, 6), 39}, // FSign in glsl_std_450
    {IR(51490, 12), 103}, // FaceForward in glsl_std_450
    {IR(51518, 9), 106}, // FindILsb in glsl_std_450
    {IR(51527, 9), 107}, // FindSMsb in glsl_std_450
    {IR(51536, 9), 108}, // FindUMsb in glsl_std_450
    {IR(50997, 6), 41}, // Floor in glsl_std_450
    {IR(51254, 4), 83}, // Fma in glsl_std_450
    {IR(51008, 6), 43}, // Fract in glsl_std_450
    {IR(51258, 6), 84}, // Frexp in glsl_std_450
    {IR(51264, 12), 85}, // FrexpStruct in glsl_std_450
    {IR(51233, 5), 80}, // IMix in glsl_std_450
    {IR(51545, 22), 109}, // InterpolateAtCentroid in glsl_std_450
    {IR(51587, 20), 111}, // InterpolateAtOffset in glsl_std_450
    {IR(51567, 20), 110}, // InterpolateAtSample in glsl_std_450
    {IR(51123, 12), 65}, // InverseSqrt in glsl_std_450
    {IR(51276, 6), 86}, // Ldexp in glsl_std_450
    {IR(51458, 7), 99}, // Length in glsl_std_450
    {IR(51104, 4), 61}, // Log in glsl_std_450
    {IR(51113, 5), 63}, // Log2 in glsl_std_450
    {IR(51147, 14), 67}, // MatrixInverse in glsl_std_450
    {IR(51161, 5), 68}, // Modf in glsl_std_450
    {IR(51166, 11), 69}, // ModfStruct in glsl_std_450
    {IR(51617, 7), 114}, // NClamp in glsl_std_450
    {IR(51612, 5), 113}, // NMax in glsl_std_450
    {IR(51607, 5), 112}, // NMin in glsl_std_450
    {IR(51480, 10), 102}, // Normalize in glsl_std_450
    {IR(51349, 15), 92}, // PackDouble2x32 in glsl_std_450
    {IR(51336, 13), 91}, // PackHalf2x16 in glsl_std_450
    {IR(51308, 14), 89}, // PackSnorm2x16 in glsl_std_450
    {IR(51282, 13), 87}, // PackSnorm4x8 in glsl_std_450
    {IR(51322, 14), 90}, // PackUnorm2x16 in glsl_std_450
    {IR(51295, 13), 88}, // PackUnorm4x8 in glsl_std_450
    {IR(51096, 4), 59}, // Pow in glsl_std_450
    {IR(51014, 8), 44}, // Radians in glsl_std_450
    {IR(51502, 8), 104}, // Reflect in glsl_std_450
    {IR(51510, 8), 105}, // Refract in glsl_std_450
    {IR(50953, 6), 34}, // Round in glsl_std_450
    {IR(50959, 10), 35}, // RoundEven in glsl_std_450
    {IR(50980, 5), 38}, // SAbs in glsl_std_450
    {IR(51221, 7), 78}, // SClamp in glsl_std_450
    {IR(51202, 5), 75}, // SMax in glsl_std_450
    {IR(51187, 5), 72}, // SMin in glsl_std_450
    {IR(50991, 6), 40}, // SSign in glsl_std_450
    {IR(51030, 4), 46}, // Sin in glsl_std_450
    {IR(51057, 5), 52}, // Sinh in glsl_std_450
    {IR(51243, 11), 82}, // SmoothStep in glsl_std_450
    {IR(51118, 5), 64}, // Sqrt in glsl_std_450
    {IR(51238, 5), 81}, // Step in glsl_std_450
    {IR(51038, 4), 48}, // Tan in glsl_std_450
    {IR(51067, 5), 54}, // Tanh in glsl_std_450
    {IR(50969, 6), 36}, // Trunc in glsl_std_450
    {IR(51214, 7), 77}, // UClamp in glsl_std_450
    {IR(51197, 5), 74}, // UMax in glsl_std_450
    {IR(51182, 5), 71}, // UMin in glsl_std_450
    {IR(51441, 17), 98}, // UnpackDouble2x32 in glsl_std_450
    {IR(51396, 15), 95}, // UnpackHalf2x16 in glsl_std_450
    {IR(51364, 16), 93}, // UnpackSnorm2x16 in glsl_std_450
    {IR(51411, 15), 96}, // UnpackSnorm4x8 in glsl_std_450
    {IR(51380, 16), 94}, // UnpackUnorm2x16 in glsl_std_450
    {IR(51426, 15), 97}, // UnpackUnorm4x8 in glsl_std_450
    {IR(51624, 13), 116}, // ArgumentInfo in nonsemantic_clspvreflection
    {IR(51719, 24), 121}, // ArgumentPodPushConstant in nonsemantic_clspvreflection
    {IR(51675, 25), 119}, // ArgumentPodStorageBuffer in nonsemantic_clspvreflection
    {IR(51700, 19), 120}, // ArgumentPodUniform in nonsemantic_clspvreflection
    {IR(52153, 28), 140}, // ArgumentPointerPushConstant in nonsemantic_clspvreflection
    {IR(52181, 23), 141}, // ArgumentPointerUniform in nonsemantic_clspvreflection
    {IR(51743, 21), 122}, // ArgumentSampledImage in nonsemantic_clspvreflection
    {IR(51785, 16), 124}, // ArgumentSampler in nonsemantic_clspvreflection
    {IR(51637, 22), 117}, // ArgumentStorageBuffer in nonsemantic_clspvreflection
    {IR(51764, 21), 123}, // ArgumentStorageImage in nonsemantic_clspvreflection
    {IR(52441, 27), 148}, // ArgumentStorageTexelBuffer in nonsemantic_clspvreflection
    {IR(51659, 16), 118}, // ArgumentUniform in nonsemantic_clspvreflection
    {IR(52468, 27), 149}, // ArgumentUniformTexelBuffer in nonsemantic_clspvreflection
    {IR(51801, 18), 125}, // ArgumentWorkgroup in nonsemantic_clspvreflection
    {IR(52495, 32), 150}, // ConstantDataPointerPushConstant in nonsemantic_clspvreflection
    {IR(52049, 26), 135}, // ConstantDataStorageBuffer in nonsemantic_clspvreflection
    {IR(52075, 20), 136}, // ConstantDataUniform in nonsemantic_clspvreflection
    {IR(52319, 45), 145}, // ImageArgumentInfoChannelDataTypePushConstant in nonsemantic_clspvreflection
    {IR(52401, 40), 147}, // ImageArgumentInfoChannelDataTypeUniform in nonsemantic_clspvreflection
    {IR(52277, 42), 144}, // ImageArgumentInfoChannelOrderPushConstant in nonsemantic_clspvreflection
    {IR(52364, 37), 146}, // ImageArgumentInfoChannelOrderUniform in nonsemantic_clspvreflection
    {IR(5377, 7), 115}, // Kernel in nonsemantic_clspvreflection
    {IR(8802, 15), 137}, // LiteralSampler in nonsemantic_clspvreflection
    {IR(52636, 34), 155}, // NormalizedSamplerMaskPushConstant in nonsemantic_clspvreflection
    {IR(52604, 32), 154}, // PrintfBufferPointerPushConstant in nonsemantic_clspvreflection
    {IR(52578, 26), 153}, // PrintfBufferStorageBuffer in nonsemantic_clspvreflection
    {IR(52567, 11), 152}, // PrintfInfo in nonsemantic_clspvreflection
    {IR(52527, 40), 151}, // ProgramScopeVariablePointerPushConstant in nonsemantic_clspvreflection
    {IR(52239, 38), 143}, // ProgramScopeVariablePointerRelocation in nonsemantic_clspvreflection
    {IR(52204, 35), 142}, // ProgramScopeVariablesStorageBuffer in nonsemantic_clspvreflection
    {IR(52095, 30), 138}, // PropertyRequiredWorkgroupSize in nonsemantic_clspvreflection
    {IR(51915, 30), 130}, // PushConstantEnqueuedLocalSize in nonsemantic_clspvreflection
    {IR(51890, 25), 129}, // PushConstantGlobalOffset in nonsemantic_clspvreflection
    {IR(51945, 23), 131}, // PushConstantGlobalSize in nonsemantic_clspvreflection
    {IR(51993, 26), 133}, // PushConstantNumWorkgroups in nonsemantic_clspvreflection
    {IR(52019, 30), 134}, // PushConstantRegionGroupOffset in nonsemantic_clspvreflection
    {IR(51968, 25), 132}, // PushConstantRegionOffset in nonsemantic_clspvreflection
    {IR(51845, 25), 127}, // SpecConstantGlobalOffset in nonsemantic_clspvreflection
    {IR(52125, 28), 139}, // SpecConstantSubgroupMaxSize in nonsemantic_clspvreflection
    {IR(51870, 20), 128}, // SpecConstantWorkDim in nonsemantic_clspvreflection
    {IR(51819, 26), 126}, // SpecConstantWorkgroupSize in nonsemantic_clspvreflection
    {IR(52670, 22), 156}, // WorkgroupVariableSize in nonsemantic_clspvreflection
    {IR(52791, 21), 197}, // DebugBuildIdentifier in nonsemantic_shader_debuginfo_100
    {IR(50108, 21), 158}, // DebugCompilationUnit in nonsemantic_shader_debuginfo_100
    {IR(50835, 13), 185}, // DebugDeclare in nonsemantic_shader_debuginfo_100
    {IR(52829, 16), 199}, // DebugEntryPoint in nonsemantic_shader_debuginfo_100
    {IR(50907, 16), 188}, // DebugExpression in nonsemantic_shader_debuginfo_100
    {IR(50651, 14), 177}, // DebugFunction in nonsemantic_shader_debuginfo_100
    {IR(50626, 25), 176}, // DebugFunctionDeclaration in nonsemantic_shader_debuginfo_100
    {IR(52724, 24), 193}, // DebugFunctionDefinition in nonsemantic_shader_debuginfo_100
    {IR(50606, 20), 175}, // DebugGlobalVariable in nonsemantic_shader_debuginfo_100
    {IR(52692, 20), 191}, // DebugImportedEntity in nonsemantic_shader_debuginfo_100
    {IR(50094, 14), 157}, // DebugInfoNone in nonsemantic_shader_debuginfo_100
    {IR(50738, 15), 182}, // DebugInlinedAt in nonsemantic_shader_debuginfo_100
    {IR(50814, 21), 184}, // DebugInlinedVariable in nonsemantic_shader_debuginfo_100
    {IR(50665, 18), 178}, // DebugLexicalBlock in nonsemantic_shader_debuginfo_100
    {IR(50683, 31), 179}, // DebugLexicalBlockDiscriminator in nonsemantic_shader_debuginfo_100
    {IR(52769, 10), 195}, // DebugLine in nonsemantic_shader_debuginfo_100
    {IR(50795, 19), 183}, // DebugLocalVariable in nonsemantic_shader_debuginfo_100
    {IR(50923, 14), 189}, // DebugMacroDef in nonsemantic_shader_debuginfo_100
    {IR(50937, 16), 190}, // DebugMacroUndef in nonsemantic_shader_debuginfo_100
    {IR(52779, 12), 196}, // DebugNoLine in nonsemantic_shader_debuginfo_100
    {IR(50725, 13), 181}, // DebugNoScope in nonsemantic_shader_debuginfo_100
    {IR(50892, 15), 187}, // DebugOperation in nonsemantic_shader_debuginfo_100
    {IR(50714, 11), 180}, // DebugScope in nonsemantic_shader_debuginfo_100
    {IR(52712, 12), 192}, // DebugSource in nonsemantic_shader_debuginfo_100
    {IR(52748, 21), 194}, // DebugSourceContinued in nonsemantic_shader_debuginfo_100
    {IR(52812, 17), 198}, // DebugStoragePath in nonsemantic_shader_debuginfo_100
    {IR(50304, 15), 162}, // DebugTypeArray in nonsemantic_shader_debuginfo_100
    {IR(50181, 15), 159}, // DebugTypeBasic in nonsemantic_shader_debuginfo_100
    {IR(50418, 19), 167}, // DebugTypeComposite in nonsemantic_shader_debuginfo_100
    {IR(50366, 14), 166}, // DebugTypeEnum in nonsemantic_shader_debuginfo_100
    {IR(50348, 18), 165}, // DebugTypeFunction in nonsemantic_shader_debuginfo_100
    {IR(50453, 21), 169}, // DebugTypeInheritance in nonsemantic_shader_debuginfo_100
    {IR(52845, 16), 200}, // DebugTypeMatrix in nonsemantic_shader_debuginfo_100
    {IR(50437, 16), 168}, // DebugTypeMember in nonsemantic_shader_debuginfo_100
    {IR(50230, 17), 160}, // DebugTypePointer in nonsemantic_shader_debuginfo_100
    {IR(50474, 21), 170}, // DebugTypePtrToMember in nonsemantic_shader_debuginfo_100
    {IR(50285, 19), 161}, // DebugTypeQualifier in nonsemantic_shader_debuginfo_100
    {IR(50495, 18), 171}, // DebugTypeTemplate in nonsemantic_shader_debuginfo_100
    {IR(50513, 27), 172}, // DebugTypeTemplateParameter in nonsemantic_shader_debuginfo_100
    {IR(50575, 31), 174}, // DebugTypeTemplateParameterPack in nonsemantic_shader_debuginfo_100
    {IR(50540, 35), 173}, // DebugTypeTemplateTemplateParameter in nonsemantic_shader_debuginfo_100
    {IR(50319, 16), 163}, // DebugTypeVector in nonsemantic_shader_debuginfo_100
    {IR(50335, 13), 164}, // DebugTypedef in nonsemantic_shader_debuginfo_100
    {IR(50848, 11), 186}, // DebugValue in nonsemantic_shader_debuginfo_100
    {IR(52861, 14), 201}, // Configuration in nonsemantic_vkspreflection
    {IR(52937, 20), 206}, // DescriptorSetBuffer in nonsemantic_vkspreflection
    {IR(52957, 19), 207}, // DescriptorSetImage in nonsemantic_vkspreflection
    {IR(52976, 21), 208}, // DescriptorSetSampler in nonsemantic_vkspreflection
    {IR(52900, 14), 204}, // PushConstants in nonsemantic_vkspreflection
    {IR(52914, 23), 205}, // SpecializationMapEntry in nonsemantic_vkspreflection
    {IR(52875, 13), 202}, // StartCounter in nonsemantic_vkspreflection
    {IR(52888, 12), 203}, // StopCounter in nonsemantic_vkspreflection
    {IR(50108, 21), 210}, // DebugCompilationUnit in opencl_debuginfo_100
    {IR(50835, 13), 237}, // DebugDeclare in opencl_debuginfo_100
    {IR(50907, 16), 240}, // DebugExpression in opencl_debuginfo_100
    {IR(50651, 14), 229}, // DebugFunction in opencl_debuginfo_100
    {IR(50626, 25), 228}, // DebugFunctionDeclaration in opencl_debuginfo_100
    {IR(50606, 20), 227}, // DebugGlobalVariable in opencl_debuginfo_100
    {IR(52692, 20), 243}, // DebugImportedEntity in opencl_debuginfo_100
    {IR(50094, 14), 209}, // DebugInfoNone in opencl_debuginfo_100
    {IR(50738, 15), 234}, // DebugInlinedAt in opencl_debuginfo_100
    {IR(50814, 21), 236}, // DebugInlinedVariable in opencl_debuginfo_100
    {IR(50665, 18), 230}, // DebugLexicalBlock in opencl_debuginfo_100
    {IR(50683, 31), 231}, // DebugLexicalBlockDiscriminator in opencl_debuginfo_100
    {IR(50795, 19), 235}, // DebugLocalVariable in opencl_debuginfo_100
    {IR(50923, 14), 241}, // DebugMacroDef in opencl_debuginfo_100
    {IR(50937, 16), 242}, // DebugMacroUndef in opencl_debuginfo_100
    {IR(53297, 17), 245}, // DebugModuleINTEL in opencl_debuginfo_100
    {IR(50725, 13), 233}, // DebugNoScope in opencl_debuginfo_100
    {IR(50892, 15), 239}, // DebugOperation in opencl_debuginfo_100
    {IR(50714, 11), 232}, // DebugScope in opencl_debuginfo_100
    {IR(52712, 12), 244}, // DebugSource in opencl_debuginfo_100
    {IR(50304, 15), 214}, // DebugTypeArray in opencl_debuginfo_100
    {IR(50181, 15), 211}, // DebugTypeBasic in opencl_debuginfo_100
    {IR(50418, 19), 219}, // DebugTypeComposite in opencl_debuginfo_100
    {IR(50366, 14), 218}, // DebugTypeEnum in opencl_debuginfo_100
    {IR(50348, 18), 217}, // DebugTypeFunction in opencl_debuginfo_100
    {IR(50453, 21), 221}, // DebugTypeInheritance in opencl_debuginfo_100
    {IR(50437, 16), 220}, // DebugTypeMember in opencl_debuginfo_100
    {IR(50230, 17), 212}, // DebugTypePointer in opencl_debuginfo_100
    {IR(50474, 21), 222}, // DebugTypePtrToMember in opencl_debuginfo_100
    {IR(50285, 19), 213}, // DebugTypeQualifier in opencl_debuginfo_100
    {IR(50495, 18), 223}, // DebugTypeTemplate in opencl_debuginfo_100
    {IR(50513, 27), 224}, // DebugTypeTemplateParameter in opencl_debuginfo_100
    {IR(50575, 31), 226}, // DebugTypeTemplateParameterPack in opencl_debuginfo_100
    {IR(50540, 35), 225}, // DebugTypeTemplateTemplateParameter in opencl_debuginfo_100
    {IR(50319, 16), 215}, // DebugTypeVector in opencl_debuginfo_100
    {IR(50335, 13), 216}, // DebugTypedef in opencl_debuginfo_100
    {IR(50848, 11), 238}, // DebugValue in opencl_debuginfo_100
    {IR(53314, 5), 246}, // acos in opencl_std_100
    {IR(53319, 6), 247}, // acosh in opencl_std_100
    {IR(53325, 7), 248}, // acospi in opencl_std_100
    {IR(53332, 5), 249}, // asin in opencl_std_100
    {IR(53337, 6), 250}, // asinh in opencl_std_100
    {IR(53343, 7), 251}, // asinpi in opencl_std_100
    {IR(53350, 5), 252}, // atan in opencl_std_100
    {IR(53355, 6), 253}, // atan2 in opencl_std_100
    {IR(53374, 8), 256}, // atan2pi in opencl_std_100
    {IR(53361, 6), 254}, // atanh in opencl_std_100
    {IR(53367, 7), 255}, // atanpi in opencl_std_100
    {IR(54565, 10), 402}, // bitselect in opencl_std_100
    {IR(53382, 5), 257}, // cbrt in opencl_std_100
    {IR(53387, 5), 258}, // ceil in opencl_std_100
    {IR(54237, 4), 367}, // clz in opencl_std_100
    {IR(53392, 9), 259}, // copysign in opencl_std_100
    {IR(53401, 4), 260}, // cos in opencl_std_100
    {IR(53405, 5), 261}, // cosh in opencl_std_100
    {IR(53410, 6), 262}, // cospi in opencl_std_100
    {IR(54081, 6), 350}, // cross in opencl_std_100
    {IR(54241, 4), 368}, // ctz in opencl_std_100
    {IR(54016, 8), 342}, // degrees in opencl_std_100
    {IR(54087, 9), 351}, // distance in opencl_std_100
    {IR(53421, 4), 264}, // erf in opencl_std_100
    {IR(53416, 5), 263}, // erfc in opencl_std_100
    {IR(53425, 4), 265}, // exp in opencl_std_100
    {IR(53434, 6), 267}, // exp10 in opencl_std_100
    {IR(53429, 5), 266}, // exp2 in opencl_std_100
    {IR(53440, 6), 268}, // expm1 in opencl_std_100
    {IR(53446, 5), 269}, // fabs in opencl_std_100
    {IR(54113, 14), 354}, // fast_distance in opencl_std_100
    {IR(54127, 12), 355}, // fast_length in opencl_std_100
    {IR(54139, 15), 356}, // fast_normalize in opencl_std_100
    {IR(54009, 7), 341}, // fclamp in opencl_std_100
    {IR(53451, 5), 270}, // fdim in opencl_std_100
    {IR(53456, 6), 271}, // floor in opencl_std_100
    {IR(53462, 4), 272}, // fma in opencl_std_100
    {IR(53466, 5), 273}, // fmax in opencl_std_100
    {IR(54024, 12), 343}, // fmax_common in opencl_std_100
    {IR(53471, 5), 274}, // fmin in opencl_std_100
    {IR(54036, 12), 344}, // fmin_common in opencl_std_100
    {IR(53476, 5), 275}, // fmod in opencl_std_100
    {IR(53481, 6), 276}, // fract in opencl_std_100
    {IR(53487, 6), 277}, // frexp in opencl_std_100
    {IR(53699, 9), 313}, // half_cos in opencl_std_100
    {IR(53708, 12), 314}, // half_divide in opencl_std_100
    {IR(53720, 9), 315}, // half_exp in opencl_std_100
    {IR(53739, 11), 317}, // half_exp10 in opencl_std_100
    {IR(53729, 10), 316}, // half_exp2 in opencl_std_100
    {IR(53750, 9), 318}, // half_log in opencl_std_100
    {IR(53769, 11), 320}, // half_log10 in opencl_std_100
    {IR(53759, 10), 319}, // half_log2 in opencl_std_100
    {IR(53780, 10), 321}, // half_powr in opencl_std_100
    {IR(53790, 11), 322}, // half_recip in opencl_std_100
    {IR(53801, 11), 323}, // half_rsqrt in opencl_std_100
    {IR(53812, 9), 324}, // half_sin in opencl_std_100
    {IR(53821, 10), 325}, // half_sqrt in opencl_std_100
    {IR(53831, 9), 326}, // half_tan in opencl_std_100
    {IR(53493, 6), 278}, // hypot in opencl_std_100
    {IR(53499, 6), 279}, // ilogb in opencl_std_100
    {IR(53505, 6), 280}, // ldexp in opencl_std_100
    {IR(54096, 7), 352}, // length in opencl_std_100
    {IR(53511, 7), 281}, // lgamma in opencl_std_100
    {IR(53518, 9), 282}, // lgamma_r in opencl_std_100
    {IR(53527, 4), 283}, // log in opencl_std_100
    {IR(53536, 6), 285}, // log10 in opencl_std_100
    {IR(53542, 6), 286}, // log1p in opencl_std_100
    {IR(53531, 5), 284}, // log2 in opencl_std_100
    {IR(53548, 5), 287}, // logb in opencl_std_100
    {IR(53553, 4), 288}, // mad in opencl_std_100
    {IR(53557, 7), 289}, // maxmag in opencl_std_100
    {IR(53564, 7), 290}, // minmag in opencl_std_100
    {IR(54048, 4), 345}, // mix in opencl_std_100
    {IR(53571, 5), 291}, // modf in opencl_std_100
    {IR(53576, 4), 292}, // nan in opencl_std_100
    {IR(53840, 11), 327}, // native_cos in opencl_std_100
    {IR(53851, 14), 328}, // native_divide in opencl_std_100
    {IR(53865, 11), 329}, // native_exp in opencl_std_100
    {IR(53888, 13), 331}, // native_exp10 in opencl_std_100
    {IR(53876, 12), 330}, // native_exp2 in opencl_std_100
    {IR(53901, 11), 332}, // native_log in opencl_std_100
    {IR(53924, 13), 334}, // native_log10 in opencl_std_100
    {IR(53912, 12), 333}, // native_log2 in opencl_std_100
    {IR(53937, 12), 335}, // native_powr in opencl_std_100
    {IR(53949, 13), 336}, // native_recip in opencl_std_100
    {IR(53962, 13), 337}, // native_rsqrt in opencl_std_100
    {IR(53975, 11), 338}, // native_sin in opencl_std_100
    {IR(53986, 12), 339}, // native_sqrt in opencl_std_100
    {IR(53998, 11), 340}, // native_tan in opencl_std_100
    {IR(53580, 10), 293}, // nextafter in opencl_std_100
    {IR(54103, 10), 353}, // normalize in opencl_std_100
    {IR(54356, 9), 382}, // popcount in opencl_std_100
    {IR(53590, 4), 294}, // pow in opencl_std_100
    {IR(53594, 5), 295}, // pown in opencl_std_100
    {IR(53599, 5), 296}, // powr in opencl_std_100
    {IR(54556, 9), 401}, // prefetch in opencl_std_100
    {IR(54549, 7), 400}, // printf in opencl_std_100
    {IR(54052, 8), 346}, // radians in opencl_std_100
    {IR(53604, 10), 297}, // remainder in opencl_std_100
    {IR(53614, 7), 298}, // remquo in opencl_std_100
    {IR(53621, 5), 299}, // rint in opencl_std_100
    {IR(53626, 6), 300}, // rootn in opencl_std_100
    {IR(54307, 7), 377}, // rotate in opencl_std_100
    {IR(53632, 6), 301}, // round in opencl_std_100
    {IR(53638, 6), 302}, // rsqrt in opencl_std_100
    {IR(54154, 6), 357}, // s_abs in opencl_std_100
    {IR(54160, 11), 358}, // s_abs_diff in opencl_std_100
    {IR(54171, 10), 359}, // s_add_sat in opencl_std_100
    {IR(54221, 8), 365}, // s_clamp in opencl_std_100
    {IR(54191, 7), 361}, // s_hadd in opencl_std_100
    {IR(54365, 8), 383}, // s_mad24 in opencl_std_100
    {IR(54245, 9), 369}, // s_mad_hi in opencl_std_100
    {IR(54264, 10), 371}, // s_mad_sat in opencl_std_100
    {IR(54274, 6), 372}, // s_max in opencl_std_100
    {IR(54286, 6), 374}, // s_min in opencl_std_100
    {IR(54381, 8), 385}, // s_mul24 in opencl_std_100
    {IR(54298, 9), 376}, // s_mul_hi in opencl_std_100
    {IR(54205, 8), 363}, // s_rhadd in opencl_std_100
    {IR(54314, 10), 378}, // s_sub_sat in opencl_std_100
    {IR(54345, 11), 381}, // s_upsample in opencl_std_100
    {IR(54575, 7), 403}, // select in opencl_std_100
    {IR(54532, 8), 398}, // shuffle in opencl_std_100
    {IR(54540, 9), 399}, // shuffle2 in opencl_std_100
    {IR(54076, 5), 349}, // sign in opencl_std_100
    {IR(53644, 4), 303}, // sin in opencl_std_100
    {IR(53648, 7), 304}, // sincos in opencl_std_100
    {IR(53655, 5), 305}, // sinh in opencl_std_100
    {IR(53660, 6), 306}, // sinpi in opencl_std_100
    {IR(54065, 11), 348}, // smoothstep in opencl_std_100
    {IR(53666, 5), 307}, // sqrt in opencl_std_100
    {IR(54060, 5), 347}, // step in opencl_std_100
    {IR(53671, 4), 308}, // tan in opencl_std_100
    {IR(53675, 5), 309}, // tanh in opencl_std_100
    {IR(53680, 6), 310}, // tanpi in opencl_std_100
    {IR(53686, 7), 311}, // tgamma in opencl_std_100
    {IR(53693, 6), 312}, // trunc in opencl_std_100
    {IR(54582, 6), 404}, // u_abs in opencl_std_100
    {IR(54588, 11), 405}, // u_abs_diff in opencl_std_100
    {IR(54181, 10), 360}, // u_add_sat in opencl_std_100
    {IR(54229, 8), 366}, // u_clamp in opencl_std_100
    {IR(54198, 7), 362}, // u_hadd in opencl_std_100
    {IR(54373, 8), 384}, // u_mad24 in opencl_std_100
    {IR(54608, 9), 407}, // u_mad_hi in opencl_std_100
    {IR(54254, 10), 370}, // u_mad_sat in opencl_std_100
    {IR(54280, 6), 373}, // u_max in opencl_std_100
    {IR(54292, 6), 375}, // u_min in opencl_std_100
    {IR(54389, 8), 386}, // u_mul24 in opencl_std_100
    {IR(54599, 9), 406}, // u_mul_hi in opencl_std_100
    {IR(54213, 8), 364}, // u_rhadd in opencl_std_100
    {IR(54324, 10), 379}, // u_sub_sat in opencl_std_100
    {IR(54334, 11), 380}, // u_upsample in opencl_std_100
    {IR(54412, 11), 389}, // vload_half in opencl_std_100
    {IR(54423, 12), 390}, // vload_halfn in opencl_std_100
    {IR(54489, 13), 395}, // vloada_halfn in opencl_std_100
    {IR(54397, 7), 387}, // vloadn in opencl_std_100
    {IR(54435, 12), 391}, // vstore_half in opencl_std_100
    {IR(54447, 14), 392}, // vstore_half_r in opencl_std_100
    {IR(54461, 13), 393}, // vstore_halfn in opencl_std_100
    {IR(54474, 15), 394}, // vstore_halfn_r in opencl_std_100
    {IR(54502, 14), 396}, // vstorea_halfn in opencl_std_100
    {IR(54516, 16), 397}, // vstorea_halfn_r in opencl_std_100
    {IR(54404, 8), 388}, // vstoren in opencl_std_100
    {IR(54634, 17), 409}, // CubeFaceCoordAMD in spv_amd_gcn_shader
    {IR(54617, 17), 408}, // CubeFaceIndexAMD in spv_amd_gcn_shader
    {IR(54651, 8), 410}, // TimeAMD in spv_amd_gcn_shader
    {IR(54728, 9), 414}, // MbcntAMD in spv_amd_shader_ballot
    {IR(54659, 22), 411}, // SwizzleInvocationsAMD in spv_amd_shader_ballot
    {IR(54681, 28), 412}, // SwizzleInvocationsMaskedAMD in spv_amd_shader_ballot
    {IR(54709, 19), 413}, // WriteInvocationAMD in spv_amd_shader_ballot
    {IR(54737, 23), 415}, // InterpolateAtVertexAMD in spv_amd_shader_explicit_vertex_parameter
    {IR(54787, 9), 419}, // FMax3AMD in spv_amd_shader_trinary_minmax
    {IR(54814, 9), 422}, // FMid3AMD in spv_amd_shader_trinary_minmax
    {IR(54760, 9), 416}, // FMin3AMD in spv_amd_shader_trinary_minmax
    {IR(54805, 9), 421}, // SMax3AMD in spv_amd_shader_trinary_minmax
    {IR(54832, 9), 424}, // SMid3AMD in spv_amd_shader_trinary_minmax
    {IR(54778, 9), 418}, // SMin3AMD in spv_amd_shader_trinary_minmax
    {IR(54796, 9), 420}, // UMax3AMD in spv_amd_shader_trinary_minmax
    {IR(54823, 9), 423}, // UMid3AMD in spv_amd_shader_trinary_minmax
    {IR(54769, 9), 417}, // UMin3AMD in spv_amd_shader_trinary_minmax
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
  "SPV_EXT_descriptor_indexing\0" // IR(1168, 28)
  "SPV_EXT_float8\0" // IR(1196, 15)
  "SPV_EXT_fragment_fully_covered\0" // IR(1211, 31)
  "SPV_EXT_fragment_invocation_density\0" // IR(1242, 36)
  "SPV_EXT_fragment_shader_interlock\0" // IR(1278, 34)
  "SPV_EXT_long_vector\0" // IR(1312, 20)
  "SPV_EXT_mesh_shader\0" // IR(1332, 20)
  "SPV_EXT_opacity_micromap\0" // IR(1352, 25)
  "SPV_EXT_optnone\0" // IR(1377, 16)
  "SPV_EXT_physical_storage_buffer\0" // IR(1393, 32)
  "SPV_EXT_relaxed_printf_string_address_space\0" // IR(1425, 44)
  "SPV_EXT_replicated_composites\0" // IR(1469, 30)
  "SPV_EXT_shader_64bit_indexing\0" // IR(1499, 30)
  "SPV_EXT_shader_atomic_float16_add\0" // IR(1529, 34)
  "SPV_EXT_shader_atomic_float_add\0" // IR(1563, 32)
  "SPV_EXT_shader_atomic_float_min_max\0" // IR(1595, 36)
  "SPV_EXT_shader_image_int64\0" // IR(1631, 27)
  "SPV_EXT_shader_invocation_reorder\0" // IR(1658, 34)
  "SPV_EXT_shader_stencil_export\0" // IR(1692, 30)
  "SPV_EXT_shader_tile_image\0" // IR(1722, 26)
  "SPV_EXT_shader_viewport_index_layer\0" // IR(1748, 36)
  "SPV_GOOGLE_decorate_string\0" // IR(1784, 27)
  "SPV_GOOGLE_hlsl_functionality1\0" // IR(1811, 31)
  "SPV_GOOGLE_user_type\0" // IR(1842, 21)
  "SPV_INTEL_2d_block_io\0" // IR(1863, 22)
  "SPV_INTEL_arbitrary_precision_fixed_point\0" // IR(1885, 42)
  "SPV_INTEL_arbitrary_precision_floating_point\0" // IR(1927, 45)
  "SPV_INTEL_arbitrary_precision_integers\0" // IR(1972, 39)
  "SPV_INTEL_bfloat16_conversion\0" // IR(2011, 30)
  "SPV_INTEL_bindless_images\0" // IR(2041, 26)
  "SPV_INTEL_blocking_pipes\0" // IR(2067, 25)
  "SPV_INTEL_cache_controls\0" // IR(2092, 25)
  "SPV_INTEL_debug_module\0" // IR(2117, 23)
  "SPV_INTEL_device_side_avc_motion_estimation\0" // IR(2140, 44)
  "SPV_INTEL_float_controls2\0" // IR(2184, 26)
  "SPV_INTEL_fp_fast_math_mode\0" // IR(2210, 28)
  "SPV_INTEL_fp_max_error\0" // IR(2238, 23)
  "SPV_INTEL_fpga_argument_interfaces\0" // IR(2261, 35)
  "SPV_INTEL_fpga_buffer_location\0" // IR(2296, 31)
  "SPV_INTEL_fpga_cluster_attributes\0" // IR(2327, 34)
  "SPV_INTEL_fpga_dsp_control\0" // IR(2361, 27)
  "SPV_INTEL_fpga_invocation_pipelining_attributes\0" // IR(2388, 48)
  "SPV_INTEL_fpga_latency_control\0" // IR(2436, 31)
  "SPV_INTEL_fpga_loop_controls\0" // IR(2467, 29)
  "SPV_INTEL_fpga_memory_accesses\0" // IR(2496, 31)
  "SPV_INTEL_fpga_memory_attributes\0" // IR(2527, 33)
  "SPV_INTEL_fpga_reg\0" // IR(2560, 19)
  "SPV_INTEL_function_pointers\0" // IR(2579, 28)
  "SPV_INTEL_function_variants\0" // IR(2607, 28)
  "SPV_INTEL_global_variable_fpga_decorations\0" // IR(2635, 43)
  "SPV_INTEL_global_variable_host_access\0" // IR(2678, 38)
  "SPV_INTEL_inline_assembly\0" // IR(2716, 26)
  "SPV_INTEL_int4\0" // IR(2742, 15)
  "SPV_INTEL_io_pipes\0" // IR(2757, 19)
  "SPV_INTEL_kernel_attributes\0" // IR(2776, 28)
  "SPV_INTEL_long_composites\0" // IR(2804, 26)
  "SPV_INTEL_loop_fuse\0" // IR(2830, 20)
  "SPV_INTEL_masked_gather_scatter\0" // IR(2850, 32)
  "SPV_INTEL_maximum_registers\0" // IR(2882, 28)
  "SPV_INTEL_media_block_io\0" // IR(2910, 25)
  "SPV_INTEL_memory_access_aliasing\0" // IR(2935, 33)
  "SPV_INTEL_optnone\0" // IR(2968, 18)
  "SPV_INTEL_runtime_aligned\0" // IR(2986, 26)
  "SPV_INTEL_shader_integer_functions2\0" // IR(3012, 36)
  "SPV_INTEL_split_barrier\0" // IR(3048, 24)
  "SPV_INTEL_subgroup_buffer_prefetch\0" // IR(3072, 35)
  "SPV_INTEL_subgroup_matrix_multiply_accumulate\0" // IR(3107, 46)
  "SPV_INTEL_subgroups\0" // IR(3153, 20)
  "SPV_INTEL_task_sequence\0" // IR(3173, 24)
  "SPV_INTEL_tensor_float32_conversion\0" // IR(3197, 36)
  "SPV_INTEL_ternary_bitwise_function\0" // IR(3233, 35)
  "SPV_INTEL_unstructured_loop_controls\0" // IR(3268, 37)
  "SPV_INTEL_usm_storage_classes\0" // IR(3305, 30)
  "SPV_INTEL_variable_length_array\0" // IR(3335, 32)
  "SPV_INTEL_vector_compute\0" // IR(3367, 25)
  "SPV_KHR_16bit_storage\0" // IR(3392, 22)
  "SPV_KHR_8bit_storage\0" // IR(3414, 21)
  "SPV_KHR_bfloat16\0" // IR(3435, 17)
  "SPV_KHR_bit_instructions\0" // IR(3452, 25)
  "SPV_KHR_compute_shader_derivatives\0" // IR(3477, 35)
  "SPV_KHR_cooperative_matrix\0" // IR(3512, 27)
  "SPV_KHR_device_group\0" // IR(3539, 21)
  "SPV_KHR_expect_assume\0" // IR(3560, 22)
  "SPV_KHR_float_controls\0" // IR(3582, 23)
  "SPV_KHR_float_controls2\0" // IR(3605, 24)
  "SPV_KHR_fma\0" // IR(3629, 12)
  "SPV_KHR_fragment_shader_barycentric\0" // IR(3641, 36)
  "SPV_KHR_fragment_shading_rate\0" // IR(3677, 30)
  "SPV_KHR_integer_dot_product\0" // IR(3707, 28)
  "SPV_KHR_linkonce_odr\0" // IR(3735, 21)
  "SPV_KHR_maximal_reconvergence\0" // IR(3756, 30)
  "SPV_KHR_multiview\0" // IR(3786, 18)
  "SPV_KHR_no_integer_wrap_decoration\0" // IR(3804, 35)
  "SPV_KHR_non_semantic_info\0" // IR(3839, 26)
  "SPV_KHR_physical_storage_buffer\0" // IR(3865, 32)
  "SPV_KHR_post_depth_coverage\0" // IR(3897, 28)
  "SPV_KHR_quad_control\0" // IR(3925, 21)
  "SPV_KHR_ray_cull_mask\0" // IR(3946, 22)
  "SPV_KHR_ray_query\0" // IR(3968, 18)
  "SPV_KHR_ray_tracing\0" // IR(3986, 20)
  "SPV_KHR_ray_tracing_position_fetch\0" // IR(4006, 35)
  "SPV_KHR_relaxed_extended_instruction\0" // IR(4041, 37)
  "SPV_KHR_shader_atomic_counter_ops\0" // IR(4078, 34)
  "SPV_KHR_shader_ballot\0" // IR(4112, 22)
  "SPV_KHR_shader_clock\0" // IR(4134, 21)
  "SPV_KHR_shader_draw_parameters\0" // IR(4155, 31)
  "SPV_KHR_storage_buffer_storage_class\0" // IR(4186, 37)
  "SPV_KHR_subgroup_rotate\0" // IR(4223, 24)
  "SPV_KHR_subgroup_uniform_control_flow\0" // IR(4247, 38)
  "SPV_KHR_subgroup_vote\0" // IR(4285, 22)
  "SPV_KHR_terminate_invocation\0" // IR(4307, 29)
  "SPV_KHR_uniform_group_instructions\0" // IR(4336, 35)
  "SPV_KHR_untyped_pointers\0" // IR(4371, 25)
  "SPV_KHR_variable_pointers\0" // IR(4396, 26)
  "SPV_KHR_vulkan_memory_model\0" // IR(4422, 28)
  "SPV_KHR_workgroup_memory_explicit_layout\0" // IR(4450, 41)
  "SPV_NVX_multiview_per_view_attributes\0" // IR(4491, 38)
  "SPV_NV_bindless_texture\0" // IR(4529, 24)
  "SPV_NV_cluster_acceleration_structure\0" // IR(4553, 38)
  "SPV_NV_compute_shader_derivatives\0" // IR(4591, 34)
  "SPV_NV_cooperative_matrix\0" // IR(4625, 26)
  "SPV_NV_cooperative_matrix2\0" // IR(4651, 27)
  "SPV_NV_cooperative_vector\0" // IR(4678, 26)
  "SPV_NV_displacement_micromap\0" // IR(4704, 29)
  "SPV_NV_fragment_shader_barycentric\0" // IR(4733, 35)
  "SPV_NV_geometry_shader_passthrough\0" // IR(4768, 35)
  "SPV_NV_linear_swept_spheres\0" // IR(4803, 28)
  "SPV_NV_mesh_shader\0" // IR(4831, 19)
  "SPV_NV_raw_access_chains\0" // IR(4850, 25)
  "SPV_NV_ray_tracing\0" // IR(4875, 19)
  "SPV_NV_ray_tracing_motion_blur\0" // IR(4894, 31)
  "SPV_NV_sample_mask_override_coverage\0" // IR(4925, 37)
  "SPV_NV_shader_atomic_fp16_vector\0" // IR(4962, 33)
  "SPV_NV_shader_image_footprint\0" // IR(4995, 30)
  "SPV_NV_shader_invocation_reorder\0" // IR(5025, 33)
  "SPV_NV_shader_sm_builtins\0" // IR(5058, 26)
  "SPV_NV_shader_subgroup_partitioned\0" // IR(5084, 35)
  "SPV_NV_shading_rate\0" // IR(5119, 20)
  "SPV_NV_stereo_view_rendering\0" // IR(5139, 29)
  "SPV_NV_tensor_addressing\0" // IR(5168, 25)
  "SPV_NV_viewport_array2\0" // IR(5193, 23)
  "SPV_QCOM_cooperative_matrix_conversion\0" // IR(5216, 39)
  "SPV_QCOM_image_processing\0" // IR(5255, 26)
  "SPV_QCOM_image_processing2\0" // IR(5281, 27)
  "SPV_QCOM_tile_shading\0" // IR(5308, 22)
  "SPV_VALIDATOR_ignore_type_decl_unique\0" // IR(5330, 38)
  "ReadOnly\0" // IR(5368, 9)
  "Kernel\0" // IR(5377, 7)
  "WriteOnly\0" // IR(5384, 10)
  "ReadWrite\0" // IR(5394, 10)
  "Logical\0" // IR(5404, 8)
  "Physical32\0" // IR(5412, 11)
  "Addresses\0" // IR(5423, 10)
  "Physical64\0" // IR(5433, 11)
  "PhysicalStorageBuffer64\0" // IR(5444, 24)
  "PhysicalStorageBuffer64EXT\0" // IR(5468, 27)
  "PhysicalStorageBufferAddresses\0" // IR(5495, 31)
  "Position\0" // IR(5526, 9)
  "Shader\0" // IR(5535, 7)
  "PointSize\0" // IR(5542, 10)
  "ClipDistance\0" // IR(5552, 13)
  "CullDistance\0" // IR(5565, 13)
  "VertexId\0" // IR(5578, 9)
  "InstanceId\0" // IR(5587, 11)
  "PrimitiveId\0" // IR(5598, 12)
  "Geometry\0" // IR(5610, 9)
  "Tessellation\0" // IR(5619, 13)
  "RayTracingNV\0" // IR(5632, 13)
  "RayTracingKHR\0" // IR(5645, 14)
  "MeshShadingNV\0" // IR(5659, 14)
  "MeshShadingEXT\0" // IR(5673, 15)
  "InvocationId\0" // IR(5688, 13)
  "Layer\0" // IR(5701, 6)
  "ShaderLayer\0" // IR(5707, 12)
  "ShaderViewportIndexLayerEXT\0" // IR(5719, 28)
  "ViewportIndex\0" // IR(5747, 14)
  "MultiViewport\0" // IR(5761, 14)
  "ShaderViewportIndex\0" // IR(5775, 20)
  "TessLevelOuter\0" // IR(5795, 15)
  "TessLevelInner\0" // IR(5810, 15)
  "TessCoord\0" // IR(5825, 10)
  "PatchVertices\0" // IR(5835, 14)
  "FragCoord\0" // IR(5849, 10)
  "PointCoord\0" // IR(5859, 11)
  "FrontFacing\0" // IR(5870, 12)
  "SampleId\0" // IR(5882, 9)
  "SampleRateShading\0" // IR(5891, 18)
  "SamplePosition\0" // IR(5909, 15)
  "SampleMask\0" // IR(5924, 11)
  "FragDepth\0" // IR(5935, 10)
  "HelperInvocation\0" // IR(5945, 17)
  "NumWorkgroups\0" // IR(5962, 14)
  "WorkgroupSize\0" // IR(5976, 14)
  "WorkgroupId\0" // IR(5990, 12)
  "LocalInvocationId\0" // IR(6002, 18)
  "GlobalInvocationId\0" // IR(6020, 19)
  "LocalInvocationIndex\0" // IR(6039, 21)
  "WorkDim\0" // IR(6060, 8)
  "GlobalSize\0" // IR(6068, 11)
  "EnqueuedWorkgroupSize\0" // IR(6079, 22)
  "GlobalOffset\0" // IR(6101, 13)
  "GlobalLinearId\0" // IR(6114, 15)
  "SubgroupSize\0" // IR(6129, 13)
  "GroupNonUniform\0" // IR(6142, 16)
  "SubgroupBallotKHR\0" // IR(6158, 18)
  "SubgroupMaxSize\0" // IR(6176, 16)
  "NumSubgroups\0" // IR(6192, 13)
  "NumEnqueuedSubgroups\0" // IR(6205, 21)
  "SubgroupId\0" // IR(6226, 11)
  "SubgroupLocalInvocationId\0" // IR(6237, 26)
  "VertexIndex\0" // IR(6263, 12)
  "InstanceIndex\0" // IR(6275, 14)
  "CoreIDARM\0" // IR(6289, 10)
  "CoreBuiltinsARM\0" // IR(6299, 16)
  "CoreCountARM\0" // IR(6315, 13)
  "CoreMaxIDARM\0" // IR(6328, 13)
  "WarpIDARM\0" // IR(6341, 10)
  "WarpMaxIDARM\0" // IR(6351, 13)
  "SubgroupEqMask\0" // IR(6364, 15)
  "SubgroupEqMaskKHR\0" // IR(6379, 18)
  "GroupNonUniformBallot\0" // IR(6397, 22)
  "SubgroupGeMask\0" // IR(6419, 15)
  "SubgroupGeMaskKHR\0" // IR(6434, 18)
  "SubgroupGtMask\0" // IR(6452, 15)
  "SubgroupGtMaskKHR\0" // IR(6467, 18)
  "SubgroupLeMask\0" // IR(6485, 15)
  "SubgroupLeMaskKHR\0" // IR(6500, 18)
  "SubgroupLtMask\0" // IR(6518, 15)
  "SubgroupLtMaskKHR\0" // IR(6533, 18)
  "BaseVertex\0" // IR(6551, 11)
  "DrawParameters\0" // IR(6562, 15)
  "BaseInstance\0" // IR(6577, 13)
  "DrawIndex\0" // IR(6590, 10)
  "PrimitiveShadingRateKHR\0" // IR(6600, 24)
  "FragmentShadingRateKHR\0" // IR(6624, 23)
  "DeviceIndex\0" // IR(6647, 12)
  "DeviceGroup\0" // IR(6659, 12)
  "ViewIndex\0" // IR(6671, 10)
  "MultiView\0" // IR(6681, 10)
  "ShadingRateKHR\0" // IR(6691, 15)
  "TileOffsetQCOM\0" // IR(6706, 15)
  "TileShadingQCOM\0" // IR(6721, 16)
  "TileDimensionQCOM\0" // IR(6737, 18)
  "TileApronSizeQCOM\0" // IR(6755, 18)
  "BaryCoordNoPerspAMD\0" // IR(6773, 20)
  "BaryCoordNoPerspCentroidAMD\0" // IR(6793, 28)
  "BaryCoordNoPerspSampleAMD\0" // IR(6821, 26)
  "BaryCoordSmoothAMD\0" // IR(6847, 19)
  "BaryCoordSmoothCentroidAMD\0" // IR(6866, 27)
  "BaryCoordSmoothSampleAMD\0" // IR(6893, 25)
  "BaryCoordPullModelAMD\0" // IR(6918, 22)
  "FragStencilRefEXT\0" // IR(6940, 18)
  "StencilExportEXT\0" // IR(6958, 17)
  "RemainingRecursionLevelsAMDX\0" // IR(6975, 29)
  "ShaderEnqueueAMDX\0" // IR(7004, 18)
  "ShaderIndexAMDX\0" // IR(7022, 16)
  "ViewportMaskNV\0" // IR(7038, 15)
  "ShaderViewportMaskNV\0" // IR(7053, 21)
  "SecondaryPositionNV\0" // IR(7074, 20)
  "ShaderStereoViewNV\0" // IR(7094, 19)
  "SecondaryViewportMaskNV\0" // IR(7113, 24)
  "PositionPerViewNV\0" // IR(7137, 18)
  "PerViewAttributesNV\0" // IR(7155, 20)
  "ViewportMaskPerViewNV\0" // IR(7175, 22)
  "FullyCoveredEXT\0" // IR(7197, 16)
  "FragmentFullyCoveredEXT\0" // IR(7213, 24)
  "TaskCountNV\0" // IR(7237, 12)
  "PrimitiveCountNV\0" // IR(7249, 17)
  "PrimitiveIndicesNV\0" // IR(7266, 19)
  "ClipDistancePerViewNV\0" // IR(7285, 22)
  "CullDistancePerViewNV\0" // IR(7307, 22)
  "LayerPerViewNV\0" // IR(7329, 15)
  "MeshViewCountNV\0" // IR(7344, 16)
  "MeshViewIndicesNV\0" // IR(7360, 18)
  "BaryCoordKHR\0" // IR(7378, 13)
  "BaryCoordNV\0" // IR(7391, 12)
  "FragmentBarycentricKHR\0" // IR(7403, 23)
  "BaryCoordNoPerspKHR\0" // IR(7426, 20)
  "BaryCoordNoPerspNV\0" // IR(7446, 19)
  "FragSizeEXT\0" // IR(7465, 12)
  "FragmentSizeNV\0" // IR(7477, 15)
  "FragmentDensityEXT\0" // IR(7492, 19)
  "FragInvocationCountEXT\0" // IR(7511, 23)
  "InvocationsPerPixelNV\0" // IR(7534, 22)
  "PrimitivePointIndicesEXT\0" // IR(7556, 25)
  "PrimitiveLineIndicesEXT\0" // IR(7581, 24)
  "PrimitiveTriangleIndicesEXT\0" // IR(7605, 28)
  "CullPrimitiveEXT\0" // IR(7633, 17)
  "LaunchIdKHR\0" // IR(7650, 12)
  "LaunchIdNV\0" // IR(7662, 11)
  "LaunchSizeKHR\0" // IR(7673, 14)
  "LaunchSizeNV\0" // IR(7687, 13)
  "WorldRayOriginKHR\0" // IR(7700, 18)
  "WorldRayOriginNV\0" // IR(7718, 17)
  "WorldRayDirectionKHR\0" // IR(7735, 21)
  "WorldRayDirectionNV\0" // IR(7756, 20)
  "ObjectRayOriginKHR\0" // IR(7776, 19)
  "ObjectRayOriginNV\0" // IR(7795, 18)
  "ObjectRayDirectionKHR\0" // IR(7813, 22)
  "ObjectRayDirectionNV\0" // IR(7835, 21)
  "RayTminKHR\0" // IR(7856, 11)
  "RayTminNV\0" // IR(7867, 10)
  "RayTmaxKHR\0" // IR(7877, 11)
  "RayTmaxNV\0" // IR(7888, 10)
  "InstanceCustomIndexKHR\0" // IR(7898, 23)
  "InstanceCustomIndexNV\0" // IR(7921, 22)
  "ObjectToWorldKHR\0" // IR(7943, 17)
  "ObjectToWorldNV\0" // IR(7960, 16)
  "WorldToObjectKHR\0" // IR(7976, 17)
  "WorldToObjectNV\0" // IR(7993, 16)
  "HitTNV\0" // IR(8009, 7)
  "HitKindKHR\0" // IR(8016, 11)
  "HitKindNV\0" // IR(8027, 10)
  "CurrentRayTimeNV\0" // IR(8037, 17)
  "RayTracingMotionBlurNV\0" // IR(8054, 23)
  "HitTriangleVertexPositionsKHR\0" // IR(8077, 30)
  "RayTracingPositionFetchKHR\0" // IR(8107, 27)
  "HitMicroTriangleVertexPositionsNV\0" // IR(8134, 34)
  "RayTracingDisplacementMicromapNV\0" // IR(8168, 33)
  "HitMicroTriangleVertexBarycentricsNV\0" // IR(8201, 37)
  "IncomingRayFlagsKHR\0" // IR(8238, 20)
  "IncomingRayFlagsNV\0" // IR(8258, 19)
  "RayGeometryIndexKHR\0" // IR(8277, 20)
  "HitIsSphereNV\0" // IR(8297, 14)
  "RayTracingSpheresGeometryNV\0" // IR(8311, 28)
  "HitIsLSSNV\0" // IR(8339, 11)
  "RayTracingLinearSweptSpheresGeometryNV\0" // IR(8350, 39)
  "HitSpherePositionNV\0" // IR(8389, 20)
  "WarpsPerSMNV\0" // IR(8409, 13)
  "ShaderSMBuiltinsNV\0" // IR(8422, 19)
  "SMCountNV\0" // IR(8441, 10)
  "WarpIDNV\0" // IR(8451, 9)
  "SMIDNV\0" // IR(8460, 7)
  "HitLSSPositionsNV\0" // IR(8467, 18)
  "HitKindFrontFacingMicroTriangleNV\0" // IR(8485, 34)
  "HitKindBackFacingMicroTriangleNV\0" // IR(8519, 33)
  "HitSphereRadiusNV\0" // IR(8552, 18)
  "HitLSSRadiiNV\0" // IR(8570, 14)
  "ClusterIDNV\0" // IR(8584, 12)
  "RayTracingClusterAccelerationStructureNV\0" // IR(8596, 41)
  "CullMaskKHR\0" // IR(8637, 12)
  "RayCullMaskKHR\0" // IR(8649, 15)
  "Matrix\0" // IR(8664, 7)
  "Linkage\0" // IR(8671, 8)
  "Vector16\0" // IR(8679, 9)
  "Float16Buffer\0" // IR(8688, 14)
  "Float16\0" // IR(8702, 8)
  "Float64\0" // IR(8710, 8)
  "Int64\0" // IR(8718, 6)
  "Int64Atomics\0" // IR(8724, 13)
  "ImageBasic\0" // IR(8737, 11)
  "ImageReadWrite\0" // IR(8748, 15)
  "ImageMipmap\0" // IR(8763, 12)
  "Pipes\0" // IR(8775, 6)
  "Groups\0" // IR(8781, 7)
  "DeviceEnqueue\0" // IR(8788, 14)
  "LiteralSampler\0" // IR(8802, 15)
  "AtomicStorage\0" // IR(8817, 14)
  "Int16\0" // IR(8831, 6)
  "TessellationPointSize\0" // IR(8837, 22)
  "GeometryPointSize\0" // IR(8859, 18)
  "ImageGatherExtended\0" // IR(8877, 20)
  "StorageImageMultisample\0" // IR(8897, 24)
  "UniformBufferArrayDynamicIndexing\0" // IR(8921, 34)
  "SampledImageArrayDynamicIndexing\0" // IR(8955, 33)
  "StorageBufferArrayDynamicIndexing\0" // IR(8988, 34)
  "StorageImageArrayDynamicIndexing\0" // IR(9022, 33)
  "ImageCubeArray\0" // IR(9055, 15)
  "SampledCubeArray\0" // IR(9070, 17)
  "ImageRect\0" // IR(9087, 10)
  "SampledRect\0" // IR(9097, 12)
  "GenericPointer\0" // IR(9109, 15)
  "Int8\0" // IR(9124, 5)
  "InputAttachment\0" // IR(9129, 16)
  "SparseResidency\0" // IR(9145, 16)
  "MinLod\0" // IR(9161, 7)
  "Sampled1D\0" // IR(9168, 10)
  "Image1D\0" // IR(9178, 8)
  "SampledBuffer\0" // IR(9186, 14)
  "ImageBuffer\0" // IR(9200, 12)
  "ImageMSArray\0" // IR(9212, 13)
  "StorageImageExtendedFormats\0" // IR(9225, 28)
  "ImageQuery\0" // IR(9253, 11)
  "DerivativeControl\0" // IR(9264, 18)
  "InterpolationFunction\0" // IR(9282, 22)
  "TransformFeedback\0" // IR(9304, 18)
  "GeometryStreams\0" // IR(9322, 16)
  "StorageImageReadWithoutFormat\0" // IR(9338, 30)
  "StorageImageWriteWithoutFormat\0" // IR(9368, 31)
  "SubgroupDispatch\0" // IR(9399, 17)
  "NamedBarrier\0" // IR(9416, 13)
  "PipeStorage\0" // IR(9429, 12)
  "GroupNonUniformVote\0" // IR(9441, 20)
  "GroupNonUniformArithmetic\0" // IR(9461, 26)
  "GroupNonUniformShuffle\0" // IR(9487, 23)
  "GroupNonUniformShuffleRelative\0" // IR(9510, 31)
  "GroupNonUniformClustered\0" // IR(9541, 25)
  "GroupNonUniformQuad\0" // IR(9566, 20)
  "UniformDecoration\0" // IR(9586, 18)
  "TileImageColorReadAccessEXT\0" // IR(9604, 28)
  "TileImageDepthReadAccessEXT\0" // IR(9632, 28)
  "TileImageStencilReadAccessEXT\0" // IR(9660, 30)
  "TensorsARM\0" // IR(9690, 11)
  "StorageTensorArrayDynamicIndexingARM\0" // IR(9701, 37)
  "StorageTensorArrayNonUniformIndexingARM\0" // IR(9738, 40)
  "GraphARM\0" // IR(9778, 9)
  "CooperativeMatrixLayoutsARM\0" // IR(9787, 28)
  "Float8EXT\0" // IR(9815, 10)
  "Float8CooperativeMatrixEXT\0" // IR(9825, 27)
  "CooperativeMatrixKHR\0" // IR(9852, 21)
  "WorkgroupMemoryExplicitLayoutKHR\0" // IR(9873, 33)
  "WorkgroupMemoryExplicitLayout8BitAccessKHR\0" // IR(9906, 43)
  "WorkgroupMemoryExplicitLayout16BitAccessKHR\0" // IR(9949, 44)
  "SubgroupVoteKHR\0" // IR(9993, 16)
  "StorageBuffer16BitAccess\0" // IR(10009, 25)
  "StorageUniformBufferBlock16\0" // IR(10034, 28)
  "UniformAndStorageBuffer16BitAccess\0" // IR(10062, 35)
  "StorageUniform16\0" // IR(10097, 17)
  "StoragePushConstant16\0" // IR(10114, 22)
  "StorageInputOutput16\0" // IR(10136, 21)
  "VariablePointersStorageBuffer\0" // IR(10157, 30)
  "VariablePointers\0" // IR(10187, 17)
  "AtomicStorageOps\0" // IR(10204, 17)
  "SampleMaskPostDepthCoverage\0" // IR(10221, 28)
  "StorageBuffer8BitAccess\0" // IR(10249, 24)
  "UniformAndStorageBuffer8BitAccess\0" // IR(10273, 34)
  "StoragePushConstant8\0" // IR(10307, 21)
  "DenormPreserve\0" // IR(10328, 15)
  "DenormFlushToZero\0" // IR(10343, 18)
  "SignedZeroInfNanPreserve\0" // IR(10361, 25)
  "RoundingModeRTE\0" // IR(10386, 16)
  "RoundingModeRTZ\0" // IR(10402, 16)
  "RayQueryProvisionalKHR\0" // IR(10418, 23)
  "RayQueryKHR\0" // IR(10441, 12)
  "UntypedPointersKHR\0" // IR(10453, 19)
  "RayTraversalPrimitiveCullingKHR\0" // IR(10472, 32)
  "TextureSampleWeightedQCOM\0" // IR(10504, 26)
  "TextureBoxFilterQCOM\0" // IR(10530, 21)
  "TextureBlockMatchQCOM\0" // IR(10551, 22)
  "CooperativeMatrixConversionQCOM\0" // IR(10573, 32)
  "TextureBlockMatch2QCOM\0" // IR(10605, 23)
  "Float16ImageAMD\0" // IR(10628, 16)
  "ImageGatherBiasLodAMD\0" // IR(10644, 22)
  "FragmentMaskAMD\0" // IR(10666, 16)
  "ImageReadWriteLodAMD\0" // IR(10682, 21)
  "Int64ImageEXT\0" // IR(10703, 14)
  "ShaderClockKHR\0" // IR(10717, 15)
  "QuadControlKHR\0" // IR(10732, 15)
  "Int4TypeINTEL\0" // IR(10747, 14)
  "Int4CooperativeMatrixINTEL\0" // IR(10761, 27)
  "BFloat16TypeKHR\0" // IR(10788, 16)
  "BFloat16DotProductKHR\0" // IR(10804, 22)
  "BFloat16CooperativeMatrixKHR\0" // IR(10826, 29)
  "SampleMaskOverrideCoverageNV\0" // IR(10855, 29)
  "GeometryShaderPassthroughNV\0" // IR(10884, 28)
  "ShaderViewportIndexLayerNV\0" // IR(10912, 27)
  "ImageFootprintNV\0" // IR(10939, 17)
  "FragmentBarycentricNV\0" // IR(10956, 22)
  "ComputeDerivativeGroupQuadsKHR\0" // IR(10978, 31)
  "ComputeDerivativeGroupQuadsNV\0" // IR(11009, 30)
  "ShadingRateNV\0" // IR(11039, 14)
  "GroupNonUniformPartitionedNV\0" // IR(11053, 29)
  "ShaderNonUniform\0" // IR(11082, 17)
  "ShaderNonUniformEXT\0" // IR(11099, 20)
  "RuntimeDescriptorArray\0" // IR(11119, 23)
  "RuntimeDescriptorArrayEXT\0" // IR(11142, 26)
  "InputAttachmentArrayDynamicIndexing\0" // IR(11168, 36)
  "InputAttachmentArrayDynamicIndexingEXT\0" // IR(11204, 39)
  "UniformTexelBufferArrayDynamicIndexing\0" // IR(11243, 39)
  "UniformTexelBufferArrayDynamicIndexingEXT\0" // IR(11282, 42)
  "StorageTexelBufferArrayDynamicIndexing\0" // IR(11324, 39)
  "StorageTexelBufferArrayDynamicIndexingEXT\0" // IR(11363, 42)
  "UniformBufferArrayNonUniformIndexing\0" // IR(11405, 37)
  "UniformBufferArrayNonUniformIndexingEXT\0" // IR(11442, 40)
  "SampledImageArrayNonUniformIndexing\0" // IR(11482, 36)
  "SampledImageArrayNonUniformIndexingEXT\0" // IR(11518, 39)
  "StorageBufferArrayNonUniformIndexing\0" // IR(11557, 37)
  "StorageBufferArrayNonUniformIndexingEXT\0" // IR(11594, 40)
  "StorageImageArrayNonUniformIndexing\0" // IR(11634, 36)
  "StorageImageArrayNonUniformIndexingEXT\0" // IR(11670, 39)
  "InputAttachmentArrayNonUniformIndexing\0" // IR(11709, 39)
  "InputAttachmentArrayNonUniformIndexingEXT\0" // IR(11748, 42)
  "UniformTexelBufferArrayNonUniformIndexing\0" // IR(11790, 42)
  "UniformTexelBufferArrayNonUniformIndexingEXT\0" // IR(11832, 45)
  "StorageTexelBufferArrayNonUniformIndexing\0" // IR(11877, 42)
  "StorageTexelBufferArrayNonUniformIndexingEXT\0" // IR(11919, 45)
  "VulkanMemoryModel\0" // IR(11964, 18)
  "VulkanMemoryModelKHR\0" // IR(11982, 21)
  "VulkanMemoryModelDeviceScope\0" // IR(12003, 29)
  "VulkanMemoryModelDeviceScopeKHR\0" // IR(12032, 32)
  "PhysicalStorageBufferAddressesEXT\0" // IR(12064, 34)
  "ComputeDerivativeGroupLinearKHR\0" // IR(12098, 32)
  "ComputeDerivativeGroupLinearNV\0" // IR(12130, 31)
  "RayTracingProvisionalKHR\0" // IR(12161, 25)
  "CooperativeMatrixNV\0" // IR(12186, 20)
  "FragmentShaderSampleInterlockEXT\0" // IR(12206, 33)
  "FragmentShaderShadingRateInterlockEXT\0" // IR(12239, 38)
  "FragmentShaderPixelInterlockEXT\0" // IR(12277, 32)
  "DemoteToHelperInvocation\0" // IR(12309, 25)
  "DemoteToHelperInvocationEXT\0" // IR(12334, 28)
  "DisplacementMicromapNV\0" // IR(12362, 23)
  "RayTracingOpacityMicromapEXT\0" // IR(12385, 29)
  "ShaderInvocationReorderNV\0" // IR(12414, 26)
  "ShaderInvocationReorderEXT\0" // IR(12440, 27)
  "BindlessTextureNV\0" // IR(12467, 18)
  "RayQueryPositionFetchKHR\0" // IR(12485, 25)
  "CooperativeVectorNV\0" // IR(12510, 20)
  "AtomicFloat16VectorNV\0" // IR(12530, 22)
  "RawAccessChainsNV\0" // IR(12552, 18)
  "LongVectorEXT\0" // IR(12570, 14)
  "Shader64BitIndexingEXT\0" // IR(12584, 23)
  "CooperativeMatrixReductionsNV\0" // IR(12607, 30)
  "CooperativeMatrixConversionsNV\0" // IR(12637, 31)
  "CooperativeMatrixPerElementOperationsNV\0" // IR(12668, 40)
  "CooperativeMatrixTensorAddressingNV\0" // IR(12708, 36)
  "CooperativeMatrixBlockLoadsNV\0" // IR(12744, 30)
  "CooperativeVectorTrainingNV\0" // IR(12774, 28)
  "TensorAddressingNV\0" // IR(12802, 19)
  "SubgroupShuffleINTEL\0" // IR(12821, 21)
  "SubgroupBufferBlockIOINTEL\0" // IR(12842, 27)
  "SubgroupImageBlockIOINTEL\0" // IR(12869, 26)
  "SubgroupImageMediaBlockIOINTEL\0" // IR(12895, 31)
  "RoundToInfinityINTEL\0" // IR(12926, 21)
  "FloatingPointModeINTEL\0" // IR(12947, 23)
  "IntegerFunctions2INTEL\0" // IR(12970, 23)
  "FunctionPointersINTEL\0" // IR(12993, 22)
  "IndirectReferencesINTEL\0" // IR(13015, 24)
  "AsmINTEL\0" // IR(13039, 9)
  "AtomicFloat32MinMaxEXT\0" // IR(13048, 23)
  "AtomicFloat64MinMaxEXT\0" // IR(13071, 23)
  "AtomicFloat16MinMaxEXT\0" // IR(13094, 23)
  "VectorComputeINTEL\0" // IR(13117, 19)
  "VectorAnyINTEL\0" // IR(13136, 15)
  "ExpectAssumeKHR\0" // IR(13151, 16)
  "SubgroupAvcMotionEstimationINTEL\0" // IR(13167, 33)
  "SubgroupAvcMotionEstimationIntraINTEL\0" // IR(13200, 38)
  "SubgroupAvcMotionEstimationChromaINTEL\0" // IR(13238, 39)
  "VariableLengthArrayINTEL\0" // IR(13277, 25)
  "FunctionFloatControlINTEL\0" // IR(13302, 26)
  "FPGAMemoryAttributesALTERA\0" // IR(13328, 27)
  "FPGAMemoryAttributesINTEL\0" // IR(13355, 26)
  "FPFastMathModeINTEL\0" // IR(13381, 20)
  "ArbitraryPrecisionIntegersALTERA\0" // IR(13401, 33)
  "ArbitraryPrecisionIntegersINTEL\0" // IR(13434, 32)
  "ArbitraryPrecisionFloatingPointALTERA\0" // IR(13466, 38)
  "ArbitraryPrecisionFloatingPointINTEL\0" // IR(13504, 37)
  "UnstructuredLoopControlsINTEL\0" // IR(13541, 30)
  "FPGALoopControlsALTERA\0" // IR(13571, 23)
  "FPGALoopControlsINTEL\0" // IR(13594, 22)
  "KernelAttributesINTEL\0" // IR(13616, 22)
  "FPGAKernelAttributesINTEL\0" // IR(13638, 26)
  "FPGAMemoryAccessesALTERA\0" // IR(13664, 25)
  "FPGAMemoryAccessesINTEL\0" // IR(13689, 24)
  "FPGAClusterAttributesALTERA\0" // IR(13713, 28)
  "FPGAClusterAttributesINTEL\0" // IR(13741, 27)
  "LoopFuseALTERA\0" // IR(13768, 15)
  "LoopFuseINTEL\0" // IR(13783, 14)
  "FPGADSPControlALTERA\0" // IR(13797, 21)
  "FPGADSPControlINTEL\0" // IR(13818, 20)
  "MemoryAccessAliasingINTEL\0" // IR(13838, 26)
  "FPGAInvocationPipeliningAttributesALTERA\0" // IR(13864, 41)
  "FPGAInvocationPipeliningAttributesINTEL\0" // IR(13905, 40)
  "FPGABufferLocationALTERA\0" // IR(13945, 25)
  "FPGABufferLocationINTEL\0" // IR(13970, 24)
  "ArbitraryPrecisionFixedPointALTERA\0" // IR(13994, 35)
  "ArbitraryPrecisionFixedPointINTEL\0" // IR(14029, 34)
  "USMStorageClassesALTERA\0" // IR(14063, 24)
  "USMStorageClassesINTEL\0" // IR(14087, 23)
  "RuntimeAlignedAttributeALTERA\0" // IR(14110, 30)
  "RuntimeAlignedAttributeINTEL\0" // IR(14140, 29)
  "IOPipesALTERA\0" // IR(14169, 14)
  "IOPipesINTEL\0" // IR(14183, 13)
  "BlockingPipesALTERA\0" // IR(14196, 20)
  "BlockingPipesINTEL\0" // IR(14216, 19)
  "FPGARegALTERA\0" // IR(14235, 14)
  "FPGARegINTEL\0" // IR(14249, 13)
  "DotProductInputAll\0" // IR(14262, 19)
  "DotProductInputAllKHR\0" // IR(14281, 22)
  "DotProductInput4x8Bit\0" // IR(14303, 22)
  "DotProductInput4x8BitKHR\0" // IR(14325, 25)
  "DotProductInput4x8BitPacked\0" // IR(14350, 28)
  "DotProductInput4x8BitPackedKHR\0" // IR(14378, 31)
  "DotProduct\0" // IR(14409, 11)
  "DotProductKHR\0" // IR(14420, 14)
  "ReplicatedCompositesEXT\0" // IR(14434, 24)
  "BitInstructions\0" // IR(14458, 16)
  "GroupNonUniformRotateKHR\0" // IR(14474, 25)
  "FloatControls2\0" // IR(14499, 15)
  "FMAKHR\0" // IR(14514, 7)
  "AtomicFloat32AddEXT\0" // IR(14521, 20)
  "AtomicFloat64AddEXT\0" // IR(14541, 20)
  "LongCompositesINTEL\0" // IR(14561, 20)
  "OptNoneEXT\0" // IR(14581, 11)
  "OptNoneINTEL\0" // IR(14592, 13)
  "AtomicFloat16AddEXT\0" // IR(14605, 20)
  "DebugInfoModuleINTEL\0" // IR(14625, 21)
  "BFloat16ConversionINTEL\0" // IR(14646, 24)
  "SplitBarrierINTEL\0" // IR(14670, 18)
  "ArithmeticFenceEXT\0" // IR(14688, 19)
  "FPGAClusterAttributesV2ALTERA\0" // IR(14707, 30)
  "FPGAClusterAttributesV2INTEL\0" // IR(14737, 29)
  "FPGAKernelAttributesv2INTEL\0" // IR(14766, 28)
  "TaskSequenceALTERA\0" // IR(14794, 19)
  "TaskSequenceINTEL\0" // IR(14813, 18)
  "FPMaxErrorINTEL\0" // IR(14831, 16)
  "FPGALatencyControlALTERA\0" // IR(14847, 25)
  "FPGALatencyControlINTEL\0" // IR(14872, 24)
  "FPGAArgumentInterfacesALTERA\0" // IR(14896, 29)
  "FPGAArgumentInterfacesINTEL\0" // IR(14925, 28)
  "GlobalVariableHostAccessINTEL\0" // IR(14953, 30)
  "GlobalVariableFPGADecorationsALTERA\0" // IR(14983, 36)
  "GlobalVariableFPGADecorationsINTEL\0" // IR(15019, 35)
  "SubgroupBufferPrefetchINTEL\0" // IR(15054, 28)
  "Subgroup2DBlockIOINTEL\0" // IR(15082, 23)
  "Subgroup2DBlockTransformINTEL\0" // IR(15105, 30)
  "Subgroup2DBlockTransposeINTEL\0" // IR(15135, 30)
  "SubgroupMatrixMultiplyAccumulateINTEL\0" // IR(15165, 38)
  "TernaryBitwiseFunctionINTEL\0" // IR(15203, 28)
  "UntypedVariableLengthArrayINTEL\0" // IR(15231, 32)
  "SpecConditionalINTEL\0" // IR(15263, 21)
  "FunctionVariantsINTEL\0" // IR(15284, 22)
  "GroupUniformArithmeticKHR\0" // IR(15306, 26)
  "TensorFloat32RoundingINTEL\0" // IR(15332, 27)
  "MaskedGatherScatterINTEL\0" // IR(15359, 25)
  "CacheControlsINTEL\0" // IR(15384, 19)
  "RegisterLimitsINTEL\0" // IR(15403, 20)
  "BindlessImagesINTEL\0" // IR(15423, 20)
  "Unspecified\0" // IR(15443, 12)
  "Address\0" // IR(15455, 8)
  "Boolean\0" // IR(15463, 8)
  "Float\0" // IR(15471, 6)
  "Signed\0" // IR(15477, 7)
  "SignedChar\0" // IR(15484, 11)
  "Unsigned\0" // IR(15495, 9)
  "UnsignedChar\0" // IR(15504, 13)
  "Class\0" // IR(15517, 6)
  "Structure\0" // IR(15523, 10)
  "Union\0" // IR(15533, 6)
  "ImportedModule\0" // IR(15539, 15)
  "ImportedDeclaration\0" // IR(15554, 20)
  "None\0" // IR(15574, 5)
  "FlagIsProtected\0" // IR(15579, 16)
  "FlagIsPrivate\0" // IR(15595, 14)
  "FlagIsPublic\0" // IR(15609, 13)
  "FlagIsLocal\0" // IR(15622, 12)
  "FlagIsDefinition\0" // IR(15634, 17)
  "FlagFwdDecl\0" // IR(15651, 12)
  "FlagArtificial\0" // IR(15663, 15)
  "FlagExplicit\0" // IR(15678, 13)
  "FlagPrototyped\0" // IR(15691, 15)
  "FlagObjectPointer\0" // IR(15706, 18)
  "FlagStaticMember\0" // IR(15724, 17)
  "FlagIndirectVariable\0" // IR(15741, 21)
  "FlagLValueReference\0" // IR(15762, 20)
  "FlagRValueReference\0" // IR(15782, 20)
  "FlagIsOptimized\0" // IR(15802, 16)
  "FlagIsEnumClass\0" // IR(15818, 16)
  "FlagTypePassByValue\0" // IR(15834, 20)
  "FlagTypePassByReference\0" // IR(15854, 24)
  "Deref\0" // IR(15878, 6)
  "Plus\0" // IR(15884, 5)
  "Minus\0" // IR(15889, 6)
  "SPV_OPERAND_TYPE_LITERAL_INTEGER\0" // IR(15895, 33)
  "PlusUconst\0" // IR(15928, 11)
  "BitPiece\0" // IR(15939, 9)
  "Swap\0" // IR(15948, 5)
  "Xderef\0" // IR(15953, 7)
  "StackValue\0" // IR(15960, 11)
  "Constu\0" // IR(15971, 7)
  "Fragment\0" // IR(15978, 9)
  "ConstType\0" // IR(15987, 10)
  "VolatileType\0" // IR(15997, 13)
  "RestrictType\0" // IR(16010, 13)
  "AtomicType\0" // IR(16023, 11)
  "Float16NV\0" // IR(16034, 10)
  "Float32NV\0" // IR(16044, 10)
  "Float64NV\0" // IR(16054, 10)
  "SignedInt8NV\0" // IR(16064, 13)
  "SignedInt16NV\0" // IR(16077, 14)
  "SignedInt32NV\0" // IR(16091, 14)
  "SignedInt64NV\0" // IR(16105, 14)
  "UnsignedInt8NV\0" // IR(16119, 15)
  "UnsignedInt16NV\0" // IR(16134, 16)
  "UnsignedInt32NV\0" // IR(16150, 16)
  "UnsignedInt64NV\0" // IR(16166, 16)
  "SignedInt8PackedNV\0" // IR(16182, 19)
  "UnsignedInt8PackedNV\0" // IR(16201, 21)
  "FloatE4M3NV\0" // IR(16222, 12)
  "FloatE5M2NV\0" // IR(16234, 12)
  "RowMajorKHR\0" // IR(16246, 12)
  "ColumnMajorKHR\0" // IR(16258, 15)
  "RowBlockedInterleavedARM\0" // IR(16273, 25)
  "ColumnBlockedInterleavedARM\0" // IR(16298, 28)
  "NoneKHR\0" // IR(16326, 8)
  "MatrixASignedComponentsKHR\0" // IR(16334, 27)
  "MatrixBSignedComponentsKHR\0" // IR(16361, 27)
  "MatrixCSignedComponentsKHR\0" // IR(16388, 27)
  "MatrixResultSignedComponentsKHR\0" // IR(16415, 32)
  "SaturatingAccumulationKHR\0" // IR(16447, 26)
  "Row\0" // IR(16473, 4)
  "Column\0" // IR(16477, 7)
  "2x2\0" // IR(16484, 4)
  "MatrixAKHR\0" // IR(16488, 11)
  "MatrixBKHR\0" // IR(16499, 11)
  "MatrixAccumulatorKHR\0" // IR(16510, 21)
  "RowMajorNV\0" // IR(16531, 11)
  "ColumnMajorNV\0" // IR(16542, 14)
  "InferencingOptimalNV\0" // IR(16556, 21)
  "TrainingOptimalNV\0" // IR(16577, 18)
  "RelaxedPrecision\0" // IR(16595, 17)
  "SpecId\0" // IR(16612, 7)
  "Block\0" // IR(16619, 6)
  "BufferBlock\0" // IR(16625, 12)
  "RowMajor\0" // IR(16637, 9)
  "ColMajor\0" // IR(16646, 9)
  "ArrayStride\0" // IR(16655, 12)
  "MatrixStride\0" // IR(16667, 13)
  "GLSLShared\0" // IR(16680, 11)
  "GLSLPacked\0" // IR(16691, 11)
  "CPacked\0" // IR(16702, 8)
  "SPV_OPERAND_TYPE_BUILT_IN\0" // IR(16710, 26)
  "BuiltIn\0" // IR(16736, 8)
  "NoPerspective\0" // IR(16744, 14)
  "Flat\0" // IR(16758, 5)
  "Patch\0" // IR(16763, 6)
  "Centroid\0" // IR(16769, 9)
  "Sample\0" // IR(16778, 7)
  "Invariant\0" // IR(16785, 10)
  "Restrict\0" // IR(16795, 9)
  "Aliased\0" // IR(16804, 8)
  "Volatile\0" // IR(16812, 9)
  "Constant\0" // IR(16821, 9)
  "Coherent\0" // IR(16830, 9)
  "NonWritable\0" // IR(16839, 12)
  "NonReadable\0" // IR(16851, 12)
  "Uniform\0" // IR(16863, 8)
  "SPV_OPERAND_TYPE_SCOPE_ID\0" // IR(16871, 26)
  "UniformId\0" // IR(16897, 10)
  "SaturatedConversion\0" // IR(16907, 20)
  "Stream\0" // IR(16927, 7)
  "Location\0" // IR(16934, 9)
  "Component\0" // IR(16943, 10)
  "Index\0" // IR(16953, 6)
  "Binding\0" // IR(16959, 8)
  "DescriptorSet\0" // IR(16967, 14)
  "Offset\0" // IR(16981, 7)
  "XfbBuffer\0" // IR(16988, 10)
  "XfbStride\0" // IR(16998, 10)
  "SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE\0" // IR(17008, 46)
  "FuncParamAttr\0" // IR(17054, 14)
  "SPV_OPERAND_TYPE_FP_ROUNDING_MODE\0" // IR(17068, 34)
  "FPRoundingMode\0" // IR(17102, 15)
  "SPV_OPERAND_TYPE_FP_FAST_MATH_MODE\0" // IR(17117, 35)
  "FPFastMathMode\0" // IR(17152, 15)
  "SPV_OPERAND_TYPE_LITERAL_STRING\0" // IR(17167, 32)
  "SPV_OPERAND_TYPE_LINKAGE_TYPE\0" // IR(17199, 30)
  "LinkageAttributes\0" // IR(17229, 18)
  "NoContraction\0" // IR(17247, 14)
  "InputAttachmentIndex\0" // IR(17261, 21)
  "Alignment\0" // IR(17282, 10)
  "MaxByteOffset\0" // IR(17292, 14)
  "SPV_OPERAND_TYPE_ID\0" // IR(17306, 20)
  "AlignmentId\0" // IR(17326, 12)
  "MaxByteOffsetId\0" // IR(17338, 16)
  "SaturatedToLargestFloat8NormalConversionEXT\0" // IR(17354, 44)
  "NoSignedWrap\0" // IR(17398, 13)
  "NoUnsignedWrap\0" // IR(17411, 15)
  "WeightTextureQCOM\0" // IR(17426, 18)
  "BlockMatchTextureQCOM\0" // IR(17444, 22)
  "BlockMatchSamplerQCOM\0" // IR(17466, 22)
  "ExplicitInterpAMD\0" // IR(17488, 18)
  "NodeSharesPayloadLimitsWithAMDX\0" // IR(17506, 32)
  "NodeMaxPayloadsAMDX\0" // IR(17538, 20)
  "TrackFinishWritingAMDX\0" // IR(17558, 23)
  "PayloadNodeNameAMDX\0" // IR(17581, 20)
  "PayloadNodeBaseIndexAMDX\0" // IR(17601, 25)
  "PayloadNodeSparseArrayAMDX\0" // IR(17626, 27)
  "PayloadNodeArraySizeAMDX\0" // IR(17653, 25)
  "PayloadDispatchIndirectAMDX\0" // IR(17678, 28)
  "OverrideCoverageNV\0" // IR(17706, 19)
  "PassthroughNV\0" // IR(17725, 14)
  "ViewportRelativeNV\0" // IR(17739, 19)
  "SecondaryViewportRelativeNV\0" // IR(17758, 28)
  "PerPrimitiveEXT\0" // IR(17786, 16)
  "PerPrimitiveNV\0" // IR(17802, 15)
  "PerViewNV\0" // IR(17817, 10)
  "PerTaskNV\0" // IR(17827, 10)
  "PerVertexKHR\0" // IR(17837, 13)
  "PerVertexNV\0" // IR(17850, 12)
  "NonUniform\0" // IR(17862, 11)
  "NonUniformEXT\0" // IR(17873, 14)
  "RestrictPointer\0" // IR(17887, 16)
  "RestrictPointerEXT\0" // IR(17903, 19)
  "AliasedPointer\0" // IR(17922, 15)
  "AliasedPointerEXT\0" // IR(17937, 18)
  "HitObjectShaderRecordBufferNV\0" // IR(17955, 30)
  "HitObjectShaderRecordBufferEXT\0" // IR(17985, 31)
  "BindlessSamplerNV\0" // IR(18016, 18)
  "BindlessImageNV\0" // IR(18034, 16)
  "BoundSamplerNV\0" // IR(18050, 15)
  "BoundImageNV\0" // IR(18065, 13)
  "SIMTCallINTEL\0" // IR(18078, 14)
  "ReferencedIndirectlyINTEL\0" // IR(18092, 26)
  "ClobberINTEL\0" // IR(18118, 13)
  "SideEffectsINTEL\0" // IR(18131, 17)
  "VectorComputeVariableINTEL\0" // IR(18148, 27)
  "FuncParamIOKindINTEL\0" // IR(18175, 21)
  "VectorComputeFunctionINTEL\0" // IR(18196, 27)
  "StackCallINTEL\0" // IR(18223, 15)
  "GlobalVariableOffsetINTEL\0" // IR(18238, 26)
  "CounterBuffer\0" // IR(18264, 14)
  "HlslCounterBufferGOOGLE\0" // IR(18278, 24)
  "UserSemantic\0" // IR(18302, 13)
  "HlslSemanticGOOGLE\0" // IR(18315, 19)
  "UserTypeGOOGLE\0" // IR(18334, 15)
  "FunctionRoundingModeINTEL\0" // IR(18349, 26)
  "SPV_OPERAND_TYPE_FPDENORM_MODE\0" // IR(18375, 31)
  "FunctionDenormModeINTEL\0" // IR(18406, 24)
  "RegisterALTERA\0" // IR(18430, 15)
  "RegisterINTEL\0" // IR(18445, 14)
  "MemoryALTERA\0" // IR(18459, 13)
  "MemoryINTEL\0" // IR(18472, 12)
  "NumbanksALTERA\0" // IR(18484, 15)
  "NumbanksINTEL\0" // IR(18499, 14)
  "BankwidthALTERA\0" // IR(18513, 16)
  "BankwidthINTEL\0" // IR(18529, 15)
  "MaxPrivateCopiesALTERA\0" // IR(18544, 23)
  "MaxPrivateCopiesINTEL\0" // IR(18567, 22)
  "SinglepumpALTERA\0" // IR(18589, 17)
  "SinglepumpINTEL\0" // IR(18606, 16)
  "DoublepumpALTERA\0" // IR(18622, 17)
  "DoublepumpINTEL\0" // IR(18639, 16)
  "MaxReplicatesALTERA\0" // IR(18655, 20)
  "MaxReplicatesINTEL\0" // IR(18675, 19)
  "SimpleDualPortALTERA\0" // IR(18694, 21)
  "SimpleDualPortINTEL\0" // IR(18715, 20)
  "MergeALTERA\0" // IR(18735, 12)
  "MergeINTEL\0" // IR(18747, 11)
  "SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER\0" // IR(18758, 42)
  "BankBitsALTERA\0" // IR(18800, 15)
  "BankBitsINTEL\0" // IR(18815, 14)
  "ForcePow2DepthALTERA\0" // IR(18829, 21)
  "ForcePow2DepthINTEL\0" // IR(18850, 20)
  "StridesizeALTERA\0" // IR(18870, 17)
  "StridesizeINTEL\0" // IR(18887, 16)
  "WordsizeALTERA\0" // IR(18903, 15)
  "WordsizeINTEL\0" // IR(18918, 14)
  "TrueDualPortALTERA\0" // IR(18932, 19)
  "TrueDualPortINTEL\0" // IR(18951, 18)
  "BurstCoalesceALTERA\0" // IR(18969, 20)
  "BurstCoalesceINTEL\0" // IR(18989, 19)
  "CacheSizeALTERA\0" // IR(19008, 16)
  "CacheSizeINTEL\0" // IR(19024, 15)
  "DontStaticallyCoalesceALTERA\0" // IR(19039, 29)
  "DontStaticallyCoalesceINTEL\0" // IR(19068, 28)
  "PrefetchALTERA\0" // IR(19096, 15)
  "PrefetchINTEL\0" // IR(19111, 14)
  "StallEnableALTERA\0" // IR(19125, 18)
  "StallEnableINTEL\0" // IR(19143, 17)
  "FuseLoopsInFunctionALTERA\0" // IR(19160, 26)
  "FuseLoopsInFunctionINTEL\0" // IR(19186, 25)
  "MathOpDSPModeALTERA\0" // IR(19211, 20)
  "MathOpDSPModeINTEL\0" // IR(19231, 19)
  "AliasScopeINTEL\0" // IR(19250, 16)
  "NoAliasINTEL\0" // IR(19266, 13)
  "InitiationIntervalALTERA\0" // IR(19279, 25)
  "InitiationIntervalINTEL\0" // IR(19304, 24)
  "MaxConcurrencyALTERA\0" // IR(19328, 21)
  "MaxConcurrencyINTEL\0" // IR(19349, 20)
  "PipelineEnableALTERA\0" // IR(19369, 21)
  "PipelineEnableINTEL\0" // IR(19390, 20)
  "BufferLocationALTERA\0" // IR(19410, 21)
  "BufferLocationINTEL\0" // IR(19431, 20)
  "IOPipeStorageALTERA\0" // IR(19451, 20)
  "IOPipeStorageINTEL\0" // IR(19471, 19)
  "SPV_OPERAND_TYPE_FPOPERATION_MODE\0" // IR(19490, 34)
  "FunctionFloatingPointModeINTEL\0" // IR(19524, 31)
  "SingleElementVectorINTEL\0" // IR(19555, 25)
  "VectorComputeCallableFunctionINTEL\0" // IR(19580, 35)
  "MediaBlockIOINTEL\0" // IR(19615, 18)
  "StallFreeALTERA\0" // IR(19633, 16)
  "StallFreeINTEL\0" // IR(19649, 15)
  "SPV_OPERAND_TYPE_LITERAL_FLOAT\0" // IR(19664, 31)
  "FPMaxErrorDecorationINTEL\0" // IR(19695, 26)
  "LatencyControlLabelALTERA\0" // IR(19721, 26)
  "LatencyControlLabelINTEL\0" // IR(19747, 25)
  "LatencyControlConstraintALTERA\0" // IR(19772, 31)
  "LatencyControlConstraintINTEL\0" // IR(19803, 30)
  "ConduitKernelArgumentALTERA\0" // IR(19833, 28)
  "ConduitKernelArgumentINTEL\0" // IR(19861, 27)
  "RegisterMapKernelArgumentALTERA\0" // IR(19888, 32)
  "RegisterMapKernelArgumentINTEL\0" // IR(19920, 31)
  "MMHostInterfaceAddressWidthALTERA\0" // IR(19951, 34)
  "MMHostInterfaceAddressWidthINTEL\0" // IR(19985, 33)
  "MMHostInterfaceDataWidthALTERA\0" // IR(20018, 31)
  "MMHostInterfaceDataWidthINTEL\0" // IR(20049, 30)
  "MMHostInterfaceLatencyALTERA\0" // IR(20079, 29)
  "MMHostInterfaceLatencyINTEL\0" // IR(20108, 28)
  "SPV_OPERAND_TYPE_ACCESS_QUALIFIER\0" // IR(20136, 34)
  "MMHostInterfaceReadWriteModeALTERA\0" // IR(20170, 35)
  "MMHostInterfaceReadWriteModeINTEL\0" // IR(20205, 34)
  "MMHostInterfaceMaxBurstALTERA\0" // IR(20239, 30)
  "MMHostInterfaceMaxBurstINTEL\0" // IR(20269, 29)
  "MMHostInterfaceWaitRequestALTERA\0" // IR(20298, 33)
  "MMHostInterfaceWaitRequestINTEL\0" // IR(20331, 32)
  "StableKernelArgumentALTERA\0" // IR(20363, 27)
  "StableKernelArgumentINTEL\0" // IR(20390, 26)
  "SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER\0" // IR(20416, 39)
  "HostAccessINTEL\0" // IR(20455, 16)
  "SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER\0" // IR(20471, 47)
  "InitModeALTERA\0" // IR(20518, 15)
  "InitModeINTEL\0" // IR(20533, 14)
  "ImplementInRegisterMapALTERA\0" // IR(20547, 29)
  "ImplementInRegisterMapINTEL\0" // IR(20576, 28)
  "ConditionalINTEL\0" // IR(20604, 17)
  "SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL\0" // IR(20621, 36)
  "CacheControlLoadINTEL\0" // IR(20657, 22)
  "SPV_OPERAND_TYPE_STORE_CACHE_CONTROL\0" // IR(20679, 37)
  "CacheControlStoreINTEL\0" // IR(20716, 23)
  "1D\0" // IR(20739, 3)
  "2D\0" // IR(20742, 3)
  "3D\0" // IR(20745, 3)
  "Cube\0" // IR(20748, 5)
  "Rect\0" // IR(20753, 5)
  "Buffer\0" // IR(20758, 7)
  "SubpassData\0" // IR(20765, 12)
  "TileImageDataEXT\0" // IR(20777, 17)
  "Invocations\0" // IR(20794, 12)
  "SpacingEqual\0" // IR(20806, 13)
  "SpacingFractionalEven\0" // IR(20819, 22)
  "SpacingFractionalOdd\0" // IR(20841, 21)
  "VertexOrderCw\0" // IR(20862, 14)
  "VertexOrderCcw\0" // IR(20876, 15)
  "PixelCenterInteger\0" // IR(20891, 19)
  "OriginUpperLeft\0" // IR(20910, 16)
  "OriginLowerLeft\0" // IR(20926, 16)
  "EarlyFragmentTests\0" // IR(20942, 19)
  "PointMode\0" // IR(20961, 10)
  "Xfb\0" // IR(20971, 4)
  "DepthReplacing\0" // IR(20975, 15)
  "DepthGreater\0" // IR(20990, 13)
  "DepthLess\0" // IR(21003, 10)
  "DepthUnchanged\0" // IR(21013, 15)
  "LocalSize\0" // IR(21028, 10)
  "LocalSizeHint\0" // IR(21038, 14)
  "InputPoints\0" // IR(21052, 12)
  "InputLines\0" // IR(21064, 11)
  "InputLinesAdjacency\0" // IR(21075, 20)
  "Triangles\0" // IR(21095, 10)
  "InputTrianglesAdjacency\0" // IR(21105, 24)
  "Quads\0" // IR(21129, 6)
  "Isolines\0" // IR(21135, 9)
  "OutputVertices\0" // IR(21144, 15)
  "OutputPoints\0" // IR(21159, 13)
  "OutputLineStrip\0" // IR(21172, 16)
  "OutputTriangleStrip\0" // IR(21188, 20)
  "VecTypeHint\0" // IR(21208, 12)
  "ContractionOff\0" // IR(21220, 15)
  "Initializer\0" // IR(21235, 12)
  "Finalizer\0" // IR(21247, 10)
  "SubgroupsPerWorkgroup\0" // IR(21257, 22)
  "SubgroupsPerWorkgroupId\0" // IR(21279, 24)
  "LocalSizeId\0" // IR(21303, 12)
  "LocalSizeHintId\0" // IR(21315, 16)
  "NonCoherentColorAttachmentReadEXT\0" // IR(21331, 34)
  "NonCoherentDepthAttachmentReadEXT\0" // IR(21365, 34)
  "NonCoherentStencilAttachmentReadEXT\0" // IR(21399, 36)
  "SubgroupUniformControlFlowKHR\0" // IR(21435, 30)
  "PostDepthCoverage\0" // IR(21465, 18)
  "NonCoherentTileAttachmentReadQCOM\0" // IR(21483, 34)
  "TileShadingRateQCOM\0" // IR(21517, 20)
  "EarlyAndLateFragmentTestsAMD\0" // IR(21537, 29)
  "StencilRefReplacingEXT\0" // IR(21566, 23)
  "CoalescingAMDX\0" // IR(21589, 15)
  "IsApiEntryAMDX\0" // IR(21604, 15)
  "MaxNodeRecursionAMDX\0" // IR(21619, 21)
  "StaticNumWorkgroupsAMDX\0" // IR(21640, 24)
  "MaxNumWorkgroupsAMDX\0" // IR(21664, 21)
  "StencilRefUnchangedFrontAMD\0" // IR(21685, 28)
  "StencilRefGreaterFrontAMD\0" // IR(21713, 26)
  "StencilRefLessFrontAMD\0" // IR(21739, 23)
  "StencilRefUnchangedBackAMD\0" // IR(21762, 27)
  "StencilRefGreaterBackAMD\0" // IR(21789, 25)
  "StencilRefLessBackAMD\0" // IR(21814, 22)
  "QuadDerivativesKHR\0" // IR(21836, 19)
  "RequireFullQuadsKHR\0" // IR(21855, 20)
  "SharesInputWithAMDX\0" // IR(21875, 20)
  "OutputLinesEXT\0" // IR(21895, 15)
  "OutputLinesNV\0" // IR(21910, 14)
  "OutputPrimitivesEXT\0" // IR(21924, 20)
  "OutputPrimitivesNV\0" // IR(21944, 19)
  "DerivativeGroupQuadsKHR\0" // IR(21963, 24)
  "DerivativeGroupQuadsNV\0" // IR(21987, 23)
  "DerivativeGroupLinearKHR\0" // IR(22010, 25)
  "DerivativeGroupLinearNV\0" // IR(22035, 24)
  "OutputTrianglesEXT\0" // IR(22059, 19)
  "OutputTrianglesNV\0" // IR(22078, 18)
  "PixelInterlockOrderedEXT\0" // IR(22096, 25)
  "PixelInterlockUnorderedEXT\0" // IR(22121, 27)
  "SampleInterlockOrderedEXT\0" // IR(22148, 26)
  "SampleInterlockUnorderedEXT\0" // IR(22174, 28)
  "ShadingRateInterlockOrderedEXT\0" // IR(22202, 31)
  "ShadingRateInterlockUnorderedEXT\0" // IR(22233, 33)
  "SharedLocalMemorySizeINTEL\0" // IR(22266, 27)
  "RoundingModeRTPINTEL\0" // IR(22293, 21)
  "RoundingModeRTNINTEL\0" // IR(22314, 21)
  "FloatingPointModeALTINTEL\0" // IR(22335, 26)
  "FloatingPointModeIEEEINTEL\0" // IR(22361, 27)
  "MaxWorkgroupSizeINTEL\0" // IR(22388, 22)
  "MaxWorkDimINTEL\0" // IR(22410, 16)
  "NoGlobalOffsetINTEL\0" // IR(22426, 20)
  "NumSIMDWorkitemsINTEL\0" // IR(22446, 22)
  "SchedulerTargetFmaxMhzINTEL\0" // IR(22468, 28)
  "MaximallyReconvergesKHR\0" // IR(22496, 24)
  "FPFastMathDefault\0" // IR(22520, 18)
  "StreamingInterfaceINTEL\0" // IR(22538, 24)
  "RegisterMapInterfaceINTEL\0" // IR(22562, 26)
  "NamedBarrierCountINTEL\0" // IR(22588, 23)
  "MaximumRegistersINTEL\0" // IR(22611, 22)
  "MaximumRegistersIdINTEL\0" // IR(22633, 24)
  "SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS\0" // IR(22657, 51)
  "NamedMaximumRegistersINTEL\0" // IR(22708, 27)
  "Vertex\0" // IR(22735, 7)
  "TessellationControl\0" // IR(22742, 20)
  "TessellationEvaluation\0" // IR(22762, 23)
  "GLCompute\0" // IR(22785, 10)
  "TaskNV\0" // IR(22795, 7)
  "MeshNV\0" // IR(22802, 7)
  "RayGenerationKHR\0" // IR(22809, 17)
  "RayGenerationNV\0" // IR(22826, 16)
  "IntersectionKHR\0" // IR(22842, 16)
  "IntersectionNV\0" // IR(22858, 15)
  "AnyHitKHR\0" // IR(22873, 10)
  "AnyHitNV\0" // IR(22883, 9)
  "ClosestHitKHR\0" // IR(22892, 14)
  "ClosestHitNV\0" // IR(22906, 13)
  "MissKHR\0" // IR(22919, 8)
  "MissNV\0" // IR(22927, 7)
  "CallableKHR\0" // IR(22934, 12)
  "CallableNV\0" // IR(22946, 11)
  "TaskEXT\0" // IR(22957, 8)
  "MeshEXT\0" // IR(22965, 8)
  "Preserve\0" // IR(22973, 9)
  "FlushToZero\0" // IR(22982, 12)
  "BFloat16KHR\0" // IR(22994, 12)
  "Float8E4M3EXT\0" // IR(23006, 14)
  "Float8E5M2EXT\0" // IR(23020, 14)
  "IEEE\0" // IR(23034, 5)
  "ALT\0" // IR(23039, 4)
  "NotNaN\0" // IR(23043, 7)
  "NotInf\0" // IR(23050, 7)
  "NSZ\0" // IR(23057, 4)
  "AllowRecip\0" // IR(23061, 11)
  "Fast\0" // IR(23072, 5)
  "AllowContract\0" // IR(23077, 14)
  "AllowContractFastINTEL\0" // IR(23091, 23)
  "AllowReassoc\0" // IR(23114, 13)
  "AllowReassocINTEL\0" // IR(23127, 18)
  "AllowTransform\0" // IR(23145, 15)
  "RTE\0" // IR(23160, 4)
  "RTZ\0" // IR(23164, 4)
  "RTP\0" // IR(23168, 4)
  "RTN\0" // IR(23172, 4)
  "Vertical2Pixels\0" // IR(23176, 16)
  "Vertical4Pixels\0" // IR(23192, 16)
  "Horizontal2Pixels\0" // IR(23208, 18)
  "Horizontal4Pixels\0" // IR(23226, 18)
  "Inline\0" // IR(23244, 7)
  "DontInline\0" // IR(23251, 11)
  "Pure\0" // IR(23262, 5)
  "Const\0" // IR(23267, 6)
  "Zext\0" // IR(23273, 5)
  "Sext\0" // IR(23278, 5)
  "ByVal\0" // IR(23283, 6)
  "Sret\0" // IR(23289, 5)
  "NoAlias\0" // IR(23294, 8)
  "NoCapture\0" // IR(23302, 10)
  "NoWrite\0" // IR(23312, 8)
  "NoReadWrite\0" // IR(23320, 12)
  "RuntimeAlignedALTERA\0" // IR(23332, 21)
  "RuntimeAlignedINTEL\0" // IR(23353, 20)
  "Reduce\0" // IR(23373, 7)
  "InclusiveScan\0" // IR(23380, 14)
  "ExclusiveScan\0" // IR(23394, 14)
  "ClusteredReduce\0" // IR(23408, 16)
  "PartitionedReduceNV\0" // IR(23424, 20)
  "PartitionedInclusiveScanNV\0" // IR(23444, 27)
  "PartitionedExclusiveScanNV\0" // IR(23471, 27)
  "NoneINTEL\0" // IR(23498, 10)
  "ReadINTEL\0" // IR(23508, 10)
  "WriteINTEL\0" // IR(23518, 11)
  "ReadWriteINTEL\0" // IR(23529, 15)
  "Bias\0" // IR(23544, 5)
  "Lod\0" // IR(23549, 4)
  "Grad\0" // IR(23553, 5)
  "ConstOffset\0" // IR(23558, 12)
  "ConstOffsets\0" // IR(23570, 13)
  "MakeTexelAvailable\0" // IR(23583, 19)
  "MakeTexelAvailableKHR\0" // IR(23602, 22)
  "MakeTexelVisible\0" // IR(23624, 17)
  "MakeTexelVisibleKHR\0" // IR(23641, 20)
  "NonPrivateTexel\0" // IR(23661, 16)
  "NonPrivateTexelKHR\0" // IR(23677, 19)
  "VolatileTexel\0" // IR(23696, 14)
  "VolatileTexelKHR\0" // IR(23710, 17)
  "SignExtend\0" // IR(23727, 11)
  "ZeroExtend\0" // IR(23738, 11)
  "Nontemporal\0" // IR(23749, 12)
  "Offsets\0" // IR(23761, 8)
  "SnormInt8\0" // IR(23769, 10)
  "SnormInt16\0" // IR(23779, 11)
  "UnormInt8\0" // IR(23790, 10)
  "UnormInt16\0" // IR(23800, 11)
  "UnormShort565\0" // IR(23811, 14)
  "UnormShort555\0" // IR(23825, 14)
  "UnormInt101010\0" // IR(23839, 15)
  "SignedInt8\0" // IR(23854, 11)
  "SignedInt16\0" // IR(23865, 12)
  "SignedInt32\0" // IR(23877, 12)
  "UnsignedInt8\0" // IR(23889, 13)
  "UnsignedInt16\0" // IR(23902, 14)
  "UnsignedInt32\0" // IR(23916, 14)
  "HalfFloat\0" // IR(23930, 10)
  "UnormInt24\0" // IR(23940, 11)
  "UnormInt101010_2\0" // IR(23951, 17)
  "UnormInt10X6EXT\0" // IR(23968, 16)
  "UnsignedIntRaw10EXT\0" // IR(23984, 20)
  "UnsignedIntRaw12EXT\0" // IR(24004, 20)
  "UnormInt2_101010EXT\0" // IR(24024, 20)
  "UnsignedInt10X6EXT\0" // IR(24044, 19)
  "UnsignedInt12X4EXT\0" // IR(24063, 19)
  "UnsignedInt14X2EXT\0" // IR(24082, 19)
  "UnormInt12X4EXT\0" // IR(24101, 16)
  "UnormInt14X2EXT\0" // IR(24117, 16)
  "R\0" // IR(24133, 2)
  "A\0" // IR(24135, 2)
  "RG\0" // IR(24137, 3)
  "RA\0" // IR(24140, 3)
  "RGB\0" // IR(24143, 4)
  "RGBA\0" // IR(24147, 5)
  "BGRA\0" // IR(24152, 5)
  "ARGB\0" // IR(24157, 5)
  "Intensity\0" // IR(24162, 10)
  "Luminance\0" // IR(24172, 10)
  "Rx\0" // IR(24182, 3)
  "RGx\0" // IR(24185, 4)
  "RGBx\0" // IR(24189, 5)
  "Depth\0" // IR(24194, 6)
  "DepthStencil\0" // IR(24200, 13)
  "sRGB\0" // IR(24213, 5)
  "sRGBx\0" // IR(24218, 6)
  "sRGBA\0" // IR(24224, 6)
  "sBGRA\0" // IR(24230, 6)
  "ABGR\0" // IR(24236, 5)
  "InitOnDeviceReprogramALTERA\0" // IR(24241, 28)
  "InitOnDeviceReprogramINTEL\0" // IR(24269, 27)
  "InitOnDeviceResetALTERA\0" // IR(24296, 24)
  "InitOnDeviceResetINTEL\0" // IR(24320, 23)
  "NoWait\0" // IR(24343, 7)
  "WaitKernel\0" // IR(24350, 11)
  "WaitWorkGroup\0" // IR(24361, 14)
  "CmdExecTime\0" // IR(24375, 12)
  "MayUsePrintf\0" // IR(24387, 13)
  "Export\0" // IR(24400, 7)
  "Import\0" // IR(24407, 7)
  "LinkOnceODR\0" // IR(24414, 12)
  "UncachedINTEL\0" // IR(24426, 14)
  "CachedINTEL\0" // IR(24440, 12)
  "StreamingINTEL\0" // IR(24452, 15)
  "InvalidateAfterReadINTEL\0" // IR(24467, 25)
  "ConstCachedINTEL\0" // IR(24492, 17)
  "Unroll\0" // IR(24509, 7)
  "DontUnroll\0" // IR(24516, 11)
  "DependencyInfinite\0" // IR(24527, 19)
  "DependencyLength\0" // IR(24546, 17)
  "MinIterations\0" // IR(24563, 14)
  "MaxIterations\0" // IR(24577, 14)
  "IterationMultiple\0" // IR(24591, 18)
  "PeelCount\0" // IR(24609, 10)
  "PartialCount\0" // IR(24619, 13)
  "DependencyArrayALTERA\0" // IR(24632, 22)
  "DependencyArrayINTEL\0" // IR(24654, 21)
  "LoopCoalesceALTERA\0" // IR(24675, 19)
  "LoopCoalesceINTEL\0" // IR(24694, 18)
  "MaxInterleavingALTERA\0" // IR(24712, 22)
  "MaxInterleavingINTEL\0" // IR(24734, 21)
  "SpeculatedIterationsALTERA\0" // IR(24755, 27)
  "SpeculatedIterationsINTEL\0" // IR(24782, 26)
  "NoFusionALTERA\0" // IR(24808, 15)
  "NoFusionINTEL\0" // IR(24823, 14)
  "LoopCountALTERA\0" // IR(24837, 16)
  "LoopCountINTEL\0" // IR(24853, 15)
  "MaxReinvocationDelayALTERA\0" // IR(24868, 27)
  "MaxReinvocationDelayINTEL\0" // IR(24895, 26)
  "MatrixASignedComponentsINTEL\0" // IR(24921, 29)
  "MatrixBSignedComponentsINTEL\0" // IR(24950, 29)
  "MatrixCBFloat16INTEL\0" // IR(24979, 21)
  "MatrixResultBFloat16INTEL\0" // IR(25000, 26)
  "MatrixAPackedInt8INTEL\0" // IR(25026, 23)
  "MatrixBPackedInt8INTEL\0" // IR(25049, 23)
  "MatrixAPackedInt4INTEL\0" // IR(25072, 23)
  "MatrixBPackedInt4INTEL\0" // IR(25095, 23)
  "MatrixATF32INTEL\0" // IR(25118, 17)
  "MatrixBTF32INTEL\0" // IR(25135, 17)
  "MatrixAPackedFloat16INTEL\0" // IR(25152, 26)
  "MatrixBPackedFloat16INTEL\0" // IR(25178, 26)
  "MatrixAPackedBFloat16INTEL\0" // IR(25204, 27)
  "MatrixBPackedBFloat16INTEL\0" // IR(25231, 27)
  "Aligned\0" // IR(25258, 8)
  "MakePointerAvailable\0" // IR(25266, 21)
  "MakePointerAvailableKHR\0" // IR(25287, 24)
  "MakePointerVisible\0" // IR(25311, 19)
  "MakePointerVisibleKHR\0" // IR(25330, 22)
  "NonPrivatePointer\0" // IR(25352, 18)
  "NonPrivatePointerKHR\0" // IR(25370, 21)
  "AliasScopeINTELMask\0" // IR(25391, 20)
  "NoAliasINTELMask\0" // IR(25411, 17)
  "Simple\0" // IR(25428, 7)
  "GLSL450\0" // IR(25435, 8)
  "OpenCL\0" // IR(25443, 7)
  "Vulkan\0" // IR(25450, 7)
  "VulkanKHR\0" // IR(25457, 10)
  "Relaxed\0" // IR(25467, 8)
  "Acquire\0" // IR(25475, 8)
  "Release\0" // IR(25483, 8)
  "AcquireRelease\0" // IR(25491, 15)
  "SequentiallyConsistent\0" // IR(25506, 23)
  "UniformMemory\0" // IR(25529, 14)
  "SubgroupMemory\0" // IR(25543, 15)
  "WorkgroupMemory\0" // IR(25558, 16)
  "CrossWorkgroupMemory\0" // IR(25574, 21)
  "AtomicCounterMemory\0" // IR(25595, 20)
  "ImageMemory\0" // IR(25615, 12)
  "OutputMemory\0" // IR(25627, 13)
  "OutputMemoryKHR\0" // IR(25640, 16)
  "MakeAvailable\0" // IR(25656, 14)
  "MakeAvailableKHR\0" // IR(25670, 17)
  "MakeVisible\0" // IR(25687, 12)
  "MakeVisibleKHR\0" // IR(25699, 15)
  "AutoINTEL\0" // IR(25714, 10)
  "WRAP\0" // IR(25724, 5)
  "SAT\0" // IR(25729, 4)
  "SAT_ZERO\0" // IR(25733, 9)
  "SAT_SYM\0" // IR(25742, 8)
  "PackedVectorFormat4x8Bit\0" // IR(25750, 25)
  "PackedVectorFormat4x8BitKHR\0" // IR(25775, 28)
  "TRN\0" // IR(25803, 4)
  "TRN_ZERO\0" // IR(25807, 9)
  "RND\0" // IR(25816, 4)
  "RND_ZERO\0" // IR(25820, 9)
  "RND_INF\0" // IR(25829, 8)
  "RND_MIN_INF\0" // IR(25837, 12)
  "RND_CONV\0" // IR(25849, 9)
  "RND_CONV_ODD\0" // IR(25858, 13)
  "RobustnessPerComponentNV\0" // IR(25871, 25)
  "RobustnessPerElementNV\0" // IR(25896, 23)
  "OpaqueKHR\0" // IR(25919, 10)
  "NoOpaqueKHR\0" // IR(25929, 12)
  "TerminateOnFirstHitKHR\0" // IR(25941, 23)
  "SkipClosestHitShaderKHR\0" // IR(25964, 24)
  "CullBackFacingTrianglesKHR\0" // IR(25988, 27)
  "CullFrontFacingTrianglesKHR\0" // IR(26015, 28)
  "CullOpaqueKHR\0" // IR(26043, 14)
  "CullNoOpaqueKHR\0" // IR(26057, 16)
  "SkipTrianglesKHR\0" // IR(26073, 17)
  "SkipBuiltinPrimitivesNV\0" // IR(26090, 24)
  "SkipAABBsKHR\0" // IR(26114, 13)
  "ForceOpacityMicromap2StateEXT\0" // IR(26127, 30)
  "RayQueryCandidateIntersectionTriangleKHR\0" // IR(26157, 41)
  "RayQueryCandidateIntersectionAABBKHR\0" // IR(26198, 37)
  "RayQueryCommittedIntersectionNoneKHR\0" // IR(26235, 37)
  "RayQueryCommittedIntersectionTriangleKHR\0" // IR(26272, 41)
  "RayQueryCommittedIntersectionGeneratedKHR\0" // IR(26313, 42)
  "RayQueryCandidateIntersectionKHR\0" // IR(26355, 33)
  "RayQueryCommittedIntersectionKHR\0" // IR(26388, 33)
  "ClampToEdge\0" // IR(26421, 12)
  "Clamp\0" // IR(26433, 6)
  "Repeat\0" // IR(26439, 7)
  "RepeatMirrored\0" // IR(26446, 15)
  "Nearest\0" // IR(26461, 8)
  "Linear\0" // IR(26469, 7)
  "Unknown\0" // IR(26476, 8)
  "Rgba32f\0" // IR(26484, 8)
  "Rgba16f\0" // IR(26492, 8)
  "R32f\0" // IR(26500, 5)
  "Rgba8\0" // IR(26505, 6)
  "Rgba8Snorm\0" // IR(26511, 11)
  "Rg32f\0" // IR(26522, 6)
  "Rg16f\0" // IR(26528, 6)
  "R11fG11fB10f\0" // IR(26534, 13)
  "R16f\0" // IR(26547, 5)
  "Rgba16\0" // IR(26552, 7)
  "Rgb10A2\0" // IR(26559, 8)
  "Rg16\0" // IR(26567, 5)
  "Rg8\0" // IR(26572, 4)
  "R16\0" // IR(26576, 4)
  "R8\0" // IR(26580, 3)
  "Rgba16Snorm\0" // IR(26583, 12)
  "Rg16Snorm\0" // IR(26595, 10)
  "Rg8Snorm\0" // IR(26605, 9)
  "R16Snorm\0" // IR(26614, 9)
  "R8Snorm\0" // IR(26623, 8)
  "Rgba32i\0" // IR(26631, 8)
  "Rgba16i\0" // IR(26639, 8)
  "Rgba8i\0" // IR(26647, 7)
  "R32i\0" // IR(26654, 5)
  "Rg32i\0" // IR(26659, 6)
  "Rg16i\0" // IR(26665, 6)
  "Rg8i\0" // IR(26671, 5)
  "R16i\0" // IR(26676, 5)
  "R8i\0" // IR(26681, 4)
  "Rgba32ui\0" // IR(26685, 9)
  "Rgba16ui\0" // IR(26694, 9)
  "Rgba8ui\0" // IR(26703, 8)
  "R32ui\0" // IR(26711, 6)
  "Rgb10a2ui\0" // IR(26717, 10)
  "Rg32ui\0" // IR(26727, 7)
  "Rg16ui\0" // IR(26734, 7)
  "Rg8ui\0" // IR(26741, 6)
  "R16ui\0" // IR(26747, 6)
  "R8ui\0" // IR(26753, 5)
  "R64ui\0" // IR(26758, 6)
  "R64i\0" // IR(26764, 5)
  "CrossDevice\0" // IR(26769, 12)
  "Device\0" // IR(26781, 7)
  "Workgroup\0" // IR(26788, 10)
  "Subgroup\0" // IR(26798, 9)
  "Invocation\0" // IR(26807, 11)
  "QueueFamily\0" // IR(26818, 12)
  "QueueFamilyKHR\0" // IR(26830, 15)
  "ShaderCallKHR\0" // IR(26845, 14)
  "Flatten\0" // IR(26859, 8)
  "DontFlatten\0" // IR(26867, 12)
  "IdentifierPossibleDuplicates\0" // IR(26879, 29)
  "FlagUnknownPhysicalLayout\0" // IR(26908, 26)
  "ESSL\0" // IR(26934, 5)
  "GLSL\0" // IR(26939, 5)
  "OpenCL_C\0" // IR(26944, 9)
  "OpenCL_CPP\0" // IR(26953, 11)
  "HLSL\0" // IR(26964, 5)
  "CPP_for_OpenCL\0" // IR(26969, 15)
  "SYCL\0" // IR(26984, 5)
  "HERO_C\0" // IR(26989, 7)
  "NZSL\0" // IR(26996, 5)
  "WGSL\0" // IR(27001, 5)
  "Slang\0" // IR(27006, 6)
  "Zig\0" // IR(27012, 4)
  "Rust\0" // IR(27016, 5)
  "UniformConstant\0" // IR(27021, 16)
  "Input\0" // IR(27037, 6)
  "Output\0" // IR(27043, 7)
  "CrossWorkgroup\0" // IR(27050, 15)
  "Private\0" // IR(27065, 8)
  "Function\0" // IR(27073, 9)
  "Generic\0" // IR(27082, 8)
  "PushConstant\0" // IR(27090, 13)
  "AtomicCounter\0" // IR(27103, 14)
  "Image\0" // IR(27117, 6)
  "StorageBuffer\0" // IR(27123, 14)
  "TileImageEXT\0" // IR(27137, 13)
  "TileAttachmentQCOM\0" // IR(27150, 19)
  "NodePayloadAMDX\0" // IR(27169, 16)
  "CallableDataKHR\0" // IR(27185, 16)
  "CallableDataNV\0" // IR(27201, 15)
  "IncomingCallableDataKHR\0" // IR(27216, 24)
  "IncomingCallableDataNV\0" // IR(27240, 23)
  "RayPayloadKHR\0" // IR(27263, 14)
  "RayPayloadNV\0" // IR(27277, 13)
  "HitAttributeKHR\0" // IR(27290, 16)
  "HitAttributeNV\0" // IR(27306, 15)
  "IncomingRayPayloadKHR\0" // IR(27321, 22)
  "IncomingRayPayloadNV\0" // IR(27343, 21)
  "ShaderRecordBufferKHR\0" // IR(27364, 22)
  "ShaderRecordBufferNV\0" // IR(27386, 21)
  "PhysicalStorageBuffer\0" // IR(27407, 22)
  "PhysicalStorageBufferEXT\0" // IR(27429, 25)
  "HitObjectAttributeNV\0" // IR(27454, 21)
  "TaskPayloadWorkgroupEXT\0" // IR(27475, 24)
  "HitObjectAttributeEXT\0" // IR(27499, 22)
  "CodeSectionINTEL\0" // IR(27521, 17)
  "DeviceOnlyALTERA\0" // IR(27538, 17)
  "DeviceOnlyINTEL\0" // IR(27555, 16)
  "HostOnlyALTERA\0" // IR(27571, 15)
  "HostOnlyINTEL\0" // IR(27586, 14)
  "WriteThroughINTEL\0" // IR(27600, 18)
  "WriteBackINTEL\0" // IR(27618, 15)
  "TensorView\0" // IR(27633, 11)
  "DecodeFunc\0" // IR(27644, 11)
  "Undefined\0" // IR(27655, 10)
  "NoneARM\0" // IR(27665, 8)
  "NontemporalARM\0" // IR(27673, 15)
  "OutOfBoundsValueARM\0" // IR(27688, 20)
  "MakeElementAvailableARM\0" // IR(27708, 24)
  "MakeElementVisibleARM\0" // IR(27732, 22)
  "NonPrivateElementARM\0" // IR(27754, 21)
  "Nop\0" // IR(27775, 4)
  "SPV_OPERAND_TYPE_TYPE_ID\0" // IR(27779, 25)
  "SPV_OPERAND_TYPE_RESULT_ID\0" // IR(27804, 27)
  "Undef\0" // IR(27831, 6)
  "SourceContinued\0" // IR(27837, 16)
  "SPV_OPERAND_TYPE_SOURCE_LANGUAGE\0" // IR(27853, 33)
  "SPV_OPERAND_TYPE_OPTIONAL_ID\0" // IR(27886, 29)
  "SPV_OPERAND_TYPE_OPTIONAL_LITERAL_STRING\0" // IR(27915, 41)
  "Source\0" // IR(27956, 7)
  "SourceExtension\0" // IR(27963, 16)
  "Name\0" // IR(27979, 5)
  "MemberName\0" // IR(27984, 11)
  "String\0" // IR(27995, 7)
  "Line\0" // IR(28002, 5)
  "Extension\0" // IR(28007, 10)
  "ExtInstImport\0" // IR(28017, 14)
  "SPV_OPERAND_TYPE_EXTENSION_INSTRUCTION_NUMBER\0" // IR(28031, 46)
  "ExtInst\0" // IR(28077, 8)
  "SPV_OPERAND_TYPE_ADDRESSING_MODEL\0" // IR(28085, 34)
  "SPV_OPERAND_TYPE_MEMORY_MODEL\0" // IR(28119, 30)
  "MemoryModel\0" // IR(28149, 12)
  "SPV_OPERAND_TYPE_EXECUTION_MODEL\0" // IR(28161, 33)
  "SPV_OPERAND_TYPE_VARIABLE_ID\0" // IR(28194, 29)
  "EntryPoint\0" // IR(28223, 11)
  "SPV_OPERAND_TYPE_EXECUTION_MODE\0" // IR(28234, 32)
  "ExecutionMode\0" // IR(28266, 14)
  "SPV_OPERAND_TYPE_CAPABILITY\0" // IR(28280, 28)
  "Capability\0" // IR(28308, 11)
  "TypeVoid\0" // IR(28319, 9)
  "TypeBool\0" // IR(28328, 9)
  "TypeInt\0" // IR(28337, 8)
  "SPV_OPERAND_TYPE_OPTIONAL_FPENCODING\0" // IR(28345, 37)
  "TypeFloat\0" // IR(28382, 10)
  "TypeVector\0" // IR(28392, 11)
  "TypeMatrix\0" // IR(28403, 11)
  "SPV_OPERAND_TYPE_DIMENSIONALITY\0" // IR(28414, 32)
  "SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT\0" // IR(28446, 38)
  "SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER\0" // IR(28484, 43)
  "TypeImage\0" // IR(28527, 10)
  "TypeSampler\0" // IR(28537, 12)
  "TypeSampledImage\0" // IR(28549, 17)
  "TypeArray\0" // IR(28566, 10)
  "TypeRuntimeArray\0" // IR(28576, 17)
  "TypeStruct\0" // IR(28593, 11)
  "TypeOpaque\0" // IR(28604, 11)
  "SPV_OPERAND_TYPE_STORAGE_CLASS\0" // IR(28615, 31)
  "TypePointer\0" // IR(28646, 12)
  "TypeFunction\0" // IR(28658, 13)
  "TypeEvent\0" // IR(28671, 10)
  "TypeDeviceEvent\0" // IR(28681, 16)
  "TypeReserveId\0" // IR(28697, 14)
  "TypeQueue\0" // IR(28711, 10)
  "TypePipe\0" // IR(28721, 9)
  "TypeForwardPointer\0" // IR(28730, 19)
  "ConstantTrue\0" // IR(28749, 13)
  "ConstantFalse\0" // IR(28762, 14)
  "SPV_OPERAND_TYPE_TYPED_LITERAL_NUMBER\0" // IR(28776, 38)
  "ConstantComposite\0" // IR(28814, 18)
  "SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE\0" // IR(28832, 41)
  "SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE\0" // IR(28873, 37)
  "ConstantSampler\0" // IR(28910, 16)
  "ConstantNull\0" // IR(28926, 13)
  "SpecConstantTrue\0" // IR(28939, 17)
  "SpecConstantFalse\0" // IR(28956, 18)
  "SpecConstant\0" // IR(28974, 13)
  "SpecConstantComposite\0" // IR(28987, 22)
  "SPV_OPERAND_TYPE_SPEC_CONSTANT_OP_NUMBER\0" // IR(29009, 41)
  "SpecConstantOp\0" // IR(29050, 15)
  "SPV_OPERAND_TYPE_FUNCTION_CONTROL\0" // IR(29065, 34)
  "FunctionParameter\0" // IR(29099, 18)
  "FunctionEnd\0" // IR(29117, 12)
  "FunctionCall\0" // IR(29129, 13)
  "Variable\0" // IR(29142, 9)
  "ImageTexelPointer\0" // IR(29151, 18)
  "SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS\0" // IR(29169, 40)
  "Load\0" // IR(29209, 5)
  "Store\0" // IR(29214, 6)
  "CopyMemory\0" // IR(29220, 11)
  "CopyMemorySized\0" // IR(29231, 16)
  "AccessChain\0" // IR(29247, 12)
  "InBoundsAccessChain\0" // IR(29259, 20)
  "PtrAccessChain\0" // IR(29279, 15)
  "ArrayLength\0" // IR(29294, 12)
  "GenericPtrMemSemantics\0" // IR(29306, 23)
  "InBoundsPtrAccessChain\0" // IR(29329, 23)
  "SPV_OPERAND_TYPE_DECORATION\0" // IR(29352, 28)
  "Decorate\0" // IR(29380, 9)
  "MemberDecorate\0" // IR(29389, 15)
  "DecorationGroup\0" // IR(29404, 16)
  "GroupDecorate\0" // IR(29420, 14)
  "SPV_OPERAND_TYPE_VARIABLE_ID_LITERAL_INTEGER\0" // IR(29434, 45)
  "GroupMemberDecorate\0" // IR(29479, 20)
  "VectorExtractDynamic\0" // IR(29499, 21)
  "VectorInsertDynamic\0" // IR(29520, 20)
  "VectorShuffle\0" // IR(29540, 14)
  "CompositeConstruct\0" // IR(29554, 19)
  "CompositeExtract\0" // IR(29573, 17)
  "CompositeInsert\0" // IR(29590, 16)
  "CopyObject\0" // IR(29606, 11)
  "Transpose\0" // IR(29617, 10)
  "SampledImage\0" // IR(29627, 13)
  "SPV_OPERAND_TYPE_OPTIONAL_IMAGE\0" // IR(29640, 32)
  "ImageSampleImplicitLod\0" // IR(29672, 23)
  "SPV_OPERAND_TYPE_IMAGE\0" // IR(29695, 23)
  "ImageSampleExplicitLod\0" // IR(29718, 23)
  "ImageSampleDrefImplicitLod\0" // IR(29741, 27)
  "ImageSampleDrefExplicitLod\0" // IR(29768, 27)
  "ImageSampleProjImplicitLod\0" // IR(29795, 27)
  "ImageSampleProjExplicitLod\0" // IR(29822, 27)
  "ImageSampleProjDrefImplicitLod\0" // IR(29849, 31)
  "ImageSampleProjDrefExplicitLod\0" // IR(29880, 31)
  "ImageFetch\0" // IR(29911, 11)
  "ImageGather\0" // IR(29922, 12)
  "ImageDrefGather\0" // IR(29934, 16)
  "ImageRead\0" // IR(29950, 10)
  "ImageWrite\0" // IR(29960, 11)
  "ImageQueryFormat\0" // IR(29971, 17)
  "ImageQueryOrder\0" // IR(29988, 16)
  "ImageQuerySizeLod\0" // IR(30004, 18)
  "ImageQuerySize\0" // IR(30022, 15)
  "ImageQueryLod\0" // IR(30037, 14)
  "ImageQueryLevels\0" // IR(30051, 17)
  "ImageQuerySamples\0" // IR(30068, 18)
  "ConvertFToU\0" // IR(30086, 12)
  "ConvertFToS\0" // IR(30098, 12)
  "ConvertSToF\0" // IR(30110, 12)
  "ConvertUToF\0" // IR(30122, 12)
  "UConvert\0" // IR(30134, 9)
  "SConvert\0" // IR(30143, 9)
  "FConvert\0" // IR(30152, 9)
  "QuantizeToF16\0" // IR(30161, 14)
  "ConvertPtrToU\0" // IR(30175, 14)
  "SatConvertSToU\0" // IR(30189, 15)
  "SatConvertUToS\0" // IR(30204, 15)
  "ConvertUToPtr\0" // IR(30219, 14)
  "PtrCastToGeneric\0" // IR(30233, 17)
  "GenericCastToPtr\0" // IR(30250, 17)
  "GenericCastToPtrExplicit\0" // IR(30267, 25)
  "Bitcast\0" // IR(30292, 8)
  "SNegate\0" // IR(30300, 8)
  "FNegate\0" // IR(30308, 8)
  "IAdd\0" // IR(30316, 5)
  "FAdd\0" // IR(30321, 5)
  "ISub\0" // IR(30326, 5)
  "FSub\0" // IR(30331, 5)
  "IMul\0" // IR(30336, 5)
  "FMul\0" // IR(30341, 5)
  "UDiv\0" // IR(30346, 5)
  "SDiv\0" // IR(30351, 5)
  "FDiv\0" // IR(30356, 5)
  "UMod\0" // IR(30361, 5)
  "SRem\0" // IR(30366, 5)
  "SMod\0" // IR(30371, 5)
  "FRem\0" // IR(30376, 5)
  "FMod\0" // IR(30381, 5)
  "VectorTimesScalar\0" // IR(30386, 18)
  "MatrixTimesScalar\0" // IR(30404, 18)
  "VectorTimesMatrix\0" // IR(30422, 18)
  "MatrixTimesVector\0" // IR(30440, 18)
  "MatrixTimesMatrix\0" // IR(30458, 18)
  "OuterProduct\0" // IR(30476, 13)
  "Dot\0" // IR(30489, 4)
  "IAddCarry\0" // IR(30493, 10)
  "ISubBorrow\0" // IR(30503, 11)
  "UMulExtended\0" // IR(30514, 13)
  "SMulExtended\0" // IR(30527, 13)
  "Any\0" // IR(30540, 4)
  "All\0" // IR(30544, 4)
  "IsNan\0" // IR(30548, 6)
  "IsInf\0" // IR(30554, 6)
  "IsFinite\0" // IR(30560, 9)
  "IsNormal\0" // IR(30569, 9)
  "SignBitSet\0" // IR(30578, 11)
  "LessOrGreater\0" // IR(30589, 14)
  "Ordered\0" // IR(30603, 8)
  "Unordered\0" // IR(30611, 10)
  "LogicalEqual\0" // IR(30621, 13)
  "LogicalNotEqual\0" // IR(30634, 16)
  "LogicalOr\0" // IR(30650, 10)
  "LogicalAnd\0" // IR(30660, 11)
  "LogicalNot\0" // IR(30671, 11)
  "Select\0" // IR(30682, 7)
  "IEqual\0" // IR(30689, 7)
  "INotEqual\0" // IR(30696, 10)
  "UGreaterThan\0" // IR(30706, 13)
  "SGreaterThan\0" // IR(30719, 13)
  "UGreaterThanEqual\0" // IR(30732, 18)
  "SGreaterThanEqual\0" // IR(30750, 18)
  "ULessThan\0" // IR(30768, 10)
  "SLessThan\0" // IR(30778, 10)
  "ULessThanEqual\0" // IR(30788, 15)
  "SLessThanEqual\0" // IR(30803, 15)
  "FOrdEqual\0" // IR(30818, 10)
  "FUnordEqual\0" // IR(30828, 12)
  "FOrdNotEqual\0" // IR(30840, 13)
  "FUnordNotEqual\0" // IR(30853, 15)
  "FOrdLessThan\0" // IR(30868, 13)
  "FUnordLessThan\0" // IR(30881, 15)
  "FOrdGreaterThan\0" // IR(30896, 16)
  "FUnordGreaterThan\0" // IR(30912, 18)
  "FOrdLessThanEqual\0" // IR(30930, 18)
  "FUnordLessThanEqual\0" // IR(30948, 20)
  "FOrdGreaterThanEqual\0" // IR(30968, 21)
  "FUnordGreaterThanEqual\0" // IR(30989, 23)
  "ShiftRightLogical\0" // IR(31012, 18)
  "ShiftRightArithmetic\0" // IR(31030, 21)
  "ShiftLeftLogical\0" // IR(31051, 17)
  "BitwiseOr\0" // IR(31068, 10)
  "BitwiseXor\0" // IR(31078, 11)
  "BitwiseAnd\0" // IR(31089, 11)
  "Not\0" // IR(31100, 4)
  "BitFieldInsert\0" // IR(31104, 15)
  "BitFieldSExtract\0" // IR(31119, 17)
  "BitFieldUExtract\0" // IR(31136, 17)
  "BitReverse\0" // IR(31153, 11)
  "BitCount\0" // IR(31164, 9)
  "DPdx\0" // IR(31173, 5)
  "DPdy\0" // IR(31178, 5)
  "Fwidth\0" // IR(31183, 7)
  "DPdxFine\0" // IR(31190, 9)
  "DPdyFine\0" // IR(31199, 9)
  "FwidthFine\0" // IR(31208, 11)
  "DPdxCoarse\0" // IR(31219, 11)
  "DPdyCoarse\0" // IR(31230, 11)
  "FwidthCoarse\0" // IR(31241, 13)
  "EmitVertex\0" // IR(31254, 11)
  "EndPrimitive\0" // IR(31265, 13)
  "EmitStreamVertex\0" // IR(31278, 17)
  "EndStreamPrimitive\0" // IR(31295, 19)
  "SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID\0" // IR(31314, 37)
  "ControlBarrier\0" // IR(31351, 15)
  "MemoryBarrier\0" // IR(31366, 14)
  "AtomicLoad\0" // IR(31380, 11)
  "AtomicStore\0" // IR(31391, 12)
  "AtomicExchange\0" // IR(31403, 15)
  "AtomicCompareExchange\0" // IR(31418, 22)
  "AtomicCompareExchangeWeak\0" // IR(31440, 26)
  "AtomicIIncrement\0" // IR(31466, 17)
  "AtomicIDecrement\0" // IR(31483, 17)
  "AtomicIAdd\0" // IR(31500, 11)
  "AtomicISub\0" // IR(31511, 11)
  "AtomicSMin\0" // IR(31522, 11)
  "AtomicUMin\0" // IR(31533, 11)
  "AtomicSMax\0" // IR(31544, 11)
  "AtomicUMax\0" // IR(31555, 11)
  "AtomicAnd\0" // IR(31566, 10)
  "AtomicOr\0" // IR(31576, 9)
  "AtomicXor\0" // IR(31585, 10)
  "Phi\0" // IR(31595, 4)
  "SPV_OPERAND_TYPE_LOOP_CONTROL\0" // IR(31599, 30)
  "LoopMerge\0" // IR(31629, 10)
  "SPV_OPERAND_TYPE_SELECTION_CONTROL\0" // IR(31639, 35)
  "SelectionMerge\0" // IR(31674, 15)
  "Label\0" // IR(31689, 6)
  "Branch\0" // IR(31695, 7)
  "BranchConditional\0" // IR(31702, 18)
  "SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER_ID\0" // IR(31720, 45)
  "Switch\0" // IR(31765, 7)
  "Kill\0" // IR(31772, 5)
  "Return\0" // IR(31777, 7)
  "ReturnValue\0" // IR(31784, 12)
  "Unreachable\0" // IR(31796, 12)
  "LifetimeStart\0" // IR(31808, 14)
  "LifetimeStop\0" // IR(31822, 13)
  "GroupAsyncCopy\0" // IR(31835, 15)
  "GroupWaitEvents\0" // IR(31850, 16)
  "GroupAll\0" // IR(31866, 9)
  "GroupAny\0" // IR(31875, 9)
  "GroupBroadcast\0" // IR(31884, 15)
  "SPV_OPERAND_TYPE_GROUP_OPERATION\0" // IR(31899, 33)
  "GroupIAdd\0" // IR(31932, 10)
  "GroupFAdd\0" // IR(31942, 10)
  "GroupFMin\0" // IR(31952, 10)
  "GroupUMin\0" // IR(31962, 10)
  "GroupSMin\0" // IR(31972, 10)
  "GroupFMax\0" // IR(31982, 10)
  "GroupUMax\0" // IR(31992, 10)
  "GroupSMax\0" // IR(32002, 10)
  "ReadPipe\0" // IR(32012, 9)
  "WritePipe\0" // IR(32021, 10)
  "ReservedReadPipe\0" // IR(32031, 17)
  "ReservedWritePipe\0" // IR(32048, 18)
  "ReserveReadPipePackets\0" // IR(32066, 23)
  "ReserveWritePipePackets\0" // IR(32089, 24)
  "CommitReadPipe\0" // IR(32113, 15)
  "CommitWritePipe\0" // IR(32128, 16)
  "IsValidReserveId\0" // IR(32144, 17)
  "GetNumPipePackets\0" // IR(32161, 18)
  "GetMaxPipePackets\0" // IR(32179, 18)
  "GroupReserveReadPipePackets\0" // IR(32197, 28)
  "GroupReserveWritePipePackets\0" // IR(32225, 29)
  "GroupCommitReadPipe\0" // IR(32254, 20)
  "GroupCommitWritePipe\0" // IR(32274, 21)
  "EnqueueMarker\0" // IR(32295, 14)
  "EnqueueKernel\0" // IR(32309, 14)
  "GetKernelNDrangeSubGroupCount\0" // IR(32323, 30)
  "GetKernelNDrangeMaxSubGroupSize\0" // IR(32353, 32)
  "GetKernelWorkGroupSize\0" // IR(32385, 23)
  "GetKernelPreferredWorkGroupSizeMultiple\0" // IR(32408, 40)
  "RetainEvent\0" // IR(32448, 12)
  "ReleaseEvent\0" // IR(32460, 13)
  "CreateUserEvent\0" // IR(32473, 16)
  "IsValidEvent\0" // IR(32489, 13)
  "SetUserEventStatus\0" // IR(32502, 19)
  "CaptureEventProfilingInfo\0" // IR(32521, 26)
  "GetDefaultQueue\0" // IR(32547, 16)
  "BuildNDRange\0" // IR(32563, 13)
  "ImageSparseSampleImplicitLod\0" // IR(32576, 29)
  "ImageSparseSampleExplicitLod\0" // IR(32605, 29)
  "ImageSparseSampleDrefImplicitLod\0" // IR(32634, 33)
  "ImageSparseSampleDrefExplicitLod\0" // IR(32667, 33)
  "ImageSparseSampleProjImplicitLod\0" // IR(32700, 33)
  "ImageSparseSampleProjExplicitLod\0" // IR(32733, 33)
  "ImageSparseSampleProjDrefImplicitLod\0" // IR(32766, 37)
  "ImageSparseSampleProjDrefExplicitLod\0" // IR(32803, 37)
  "ImageSparseFetch\0" // IR(32840, 17)
  "ImageSparseGather\0" // IR(32857, 18)
  "ImageSparseDrefGather\0" // IR(32875, 22)
  "ImageSparseTexelsResident\0" // IR(32897, 26)
  "NoLine\0" // IR(32923, 7)
  "AtomicFlagTestAndSet\0" // IR(32930, 21)
  "AtomicFlagClear\0" // IR(32951, 16)
  "ImageSparseRead\0" // IR(32967, 16)
  "SizeOf\0" // IR(32983, 7)
  "TypePipeStorage\0" // IR(32990, 16)
  "ConstantPipeStorage\0" // IR(33006, 20)
  "CreatePipeFromPipeStorage\0" // IR(33026, 26)
  "GetKernelLocalSizeForSubgroupCount\0" // IR(33052, 35)
  "GetKernelMaxNumSubgroups\0" // IR(33087, 25)
  "TypeNamedBarrier\0" // IR(33112, 17)
  "NamedBarrierInitialize\0" // IR(33129, 23)
  "MemoryNamedBarrier\0" // IR(33152, 19)
  "ModuleProcessed\0" // IR(33171, 16)
  "ExecutionModeId\0" // IR(33187, 16)
  "DecorateId\0" // IR(33203, 11)
  "GroupNonUniformElect\0" // IR(33214, 21)
  "GroupNonUniformAll\0" // IR(33235, 19)
  "GroupNonUniformAny\0" // IR(33254, 19)
  "GroupNonUniformAllEqual\0" // IR(33273, 24)
  "GroupNonUniformBroadcast\0" // IR(33297, 25)
  "GroupNonUniformBroadcastFirst\0" // IR(33322, 30)
  "GroupNonUniformInverseBallot\0" // IR(33352, 29)
  "GroupNonUniformBallotBitExtract\0" // IR(33381, 32)
  "GroupNonUniformBallotBitCount\0" // IR(33413, 30)
  "GroupNonUniformBallotFindLSB\0" // IR(33443, 29)
  "GroupNonUniformBallotFindMSB\0" // IR(33472, 29)
  "GroupNonUniformShuffleXor\0" // IR(33501, 26)
  "GroupNonUniformShuffleUp\0" // IR(33527, 25)
  "GroupNonUniformShuffleDown\0" // IR(33552, 27)
  "GroupNonUniformIAdd\0" // IR(33579, 20)
  "GroupNonUniformFAdd\0" // IR(33599, 20)
  "GroupNonUniformIMul\0" // IR(33619, 20)
  "GroupNonUniformFMul\0" // IR(33639, 20)
  "GroupNonUniformSMin\0" // IR(33659, 20)
  "GroupNonUniformUMin\0" // IR(33679, 20)
  "GroupNonUniformFMin\0" // IR(33699, 20)
  "GroupNonUniformSMax\0" // IR(33719, 20)
  "GroupNonUniformUMax\0" // IR(33739, 20)
  "GroupNonUniformFMax\0" // IR(33759, 20)
  "GroupNonUniformBitwiseAnd\0" // IR(33779, 26)
  "GroupNonUniformBitwiseOr\0" // IR(33805, 25)
  "GroupNonUniformBitwiseXor\0" // IR(33830, 26)
  "GroupNonUniformLogicalAnd\0" // IR(33856, 26)
  "GroupNonUniformLogicalOr\0" // IR(33882, 25)
  "GroupNonUniformLogicalXor\0" // IR(33907, 26)
  "GroupNonUniformQuadBroadcast\0" // IR(33933, 29)
  "GroupNonUniformQuadSwap\0" // IR(33962, 24)
  "CopyLogical\0" // IR(33986, 12)
  "PtrEqual\0" // IR(33998, 9)
  "PtrNotEqual\0" // IR(34007, 12)
  "PtrDiff\0" // IR(34019, 8)
  "ColorAttachmentReadEXT\0" // IR(34027, 23)
  "DepthAttachmentReadEXT\0" // IR(34050, 23)
  "StencilAttachmentReadEXT\0" // IR(34073, 25)
  "TypeTensorARM\0" // IR(34098, 14)
  "SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS\0" // IR(34112, 42)
  "TensorReadARM\0" // IR(34154, 14)
  "TensorWriteARM\0" // IR(34168, 15)
  "TensorQuerySizeARM\0" // IR(34183, 19)
  "GraphConstantARM\0" // IR(34202, 17)
  "GraphEntryPointARM\0" // IR(34219, 19)
  "GraphInputARM\0" // IR(34238, 14)
  "GraphSetOutputARM\0" // IR(34252, 18)
  "GraphEndARM\0" // IR(34270, 12)
  "TypeGraphARM\0" // IR(34282, 13)
  "TerminateInvocation\0" // IR(34295, 20)
  "TypeUntypedPointerKHR\0" // IR(34315, 22)
  "UntypedVariableKHR\0" // IR(34337, 19)
  "UntypedAccessChainKHR\0" // IR(34356, 22)
  "UntypedInBoundsAccessChainKHR\0" // IR(34378, 30)
  "SubgroupFirstInvocationKHR\0" // IR(34408, 27)
  "UntypedPtrAccessChainKHR\0" // IR(34435, 25)
  "UntypedInBoundsPtrAccessChainKHR\0" // IR(34460, 33)
  "UntypedArrayLengthKHR\0" // IR(34493, 22)
  "UntypedPrefetchKHR\0" // IR(34515, 19)
  "FmaKHR\0" // IR(34534, 7)
  "SubgroupAllKHR\0" // IR(34541, 15)
  "SubgroupAnyKHR\0" // IR(34556, 15)
  "SubgroupAllEqualKHR\0" // IR(34571, 20)
  "SubgroupReadInvocationKHR\0" // IR(34591, 26)
  "ExtInstWithForwardRefsKHR\0" // IR(34617, 26)
  "UntypedGroupAsyncCopyKHR\0" // IR(34643, 25)
  "TraceRayKHR\0" // IR(34668, 12)
  "ExecuteCallableKHR\0" // IR(34680, 19)
  "ConvertUToAccelerationStructureKHR\0" // IR(34699, 35)
  "IgnoreIntersectionKHR\0" // IR(34734, 22)
  "TerminateRayKHR\0" // IR(34756, 16)
  "SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT\0" // IR(34772, 47)
  "SDot\0" // IR(34819, 5)
  "SDotKHR\0" // IR(34824, 8)
  "UDot\0" // IR(34832, 5)
  "UDotKHR\0" // IR(34837, 8)
  "SUDot\0" // IR(34845, 6)
  "SUDotKHR\0" // IR(34851, 9)
  "SDotAccSat\0" // IR(34860, 11)
  "SDotAccSatKHR\0" // IR(34871, 14)
  "UDotAccSat\0" // IR(34885, 11)
  "UDotAccSatKHR\0" // IR(34896, 14)
  "SUDotAccSat\0" // IR(34910, 12)
  "SUDotAccSatKHR\0" // IR(34922, 15)
  "TypeCooperativeMatrixKHR\0" // IR(34937, 25)
  "CooperativeMatrixLoadKHR\0" // IR(34962, 25)
  "CooperativeMatrixStoreKHR\0" // IR(34987, 26)
  "SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS\0" // IR(35013, 54)
  "CooperativeMatrixMulAddKHR\0" // IR(35067, 27)
  "CooperativeMatrixLengthKHR\0" // IR(35094, 27)
  "ConstantCompositeReplicateEXT\0" // IR(35121, 30)
  "SpecConstantCompositeReplicateEXT\0" // IR(35151, 34)
  "CompositeConstructReplicateEXT\0" // IR(35185, 31)
  "TypeRayQueryKHR\0" // IR(35216, 16)
  "RayQueryInitializeKHR\0" // IR(35232, 22)
  "RayQueryTerminateKHR\0" // IR(35254, 21)
  "RayQueryGenerateIntersectionKHR\0" // IR(35275, 32)
  "RayQueryConfirmIntersectionKHR\0" // IR(35307, 31)
  "RayQueryProceedKHR\0" // IR(35338, 19)
  "RayQueryGetIntersectionTypeKHR\0" // IR(35357, 31)
  "ImageSampleWeightedQCOM\0" // IR(35388, 24)
  "ImageBoxFilterQCOM\0" // IR(35412, 19)
  "ImageBlockMatchSSDQCOM\0" // IR(35431, 23)
  "ImageBlockMatchSADQCOM\0" // IR(35454, 23)
  "BitCastArrayQCOM\0" // IR(35477, 17)
  "ImageBlockMatchWindowSSDQCOM\0" // IR(35494, 29)
  "ImageBlockMatchWindowSADQCOM\0" // IR(35523, 29)
  "ImageBlockMatchGatherSSDQCOM\0" // IR(35552, 29)
  "ImageBlockMatchGatherSADQCOM\0" // IR(35581, 29)
  "CompositeConstructCoopMatQCOM\0" // IR(35610, 30)
  "CompositeExtractCoopMatQCOM\0" // IR(35640, 28)
  "ExtractSubArrayQCOM\0" // IR(35668, 20)
  "GroupIAddNonUniformAMD\0" // IR(35688, 23)
  "GroupFAddNonUniformAMD\0" // IR(35711, 23)
  "GroupFMinNonUniformAMD\0" // IR(35734, 23)
  "GroupUMinNonUniformAMD\0" // IR(35757, 23)
  "GroupSMinNonUniformAMD\0" // IR(35780, 23)
  "GroupFMaxNonUniformAMD\0" // IR(35803, 23)
  "GroupUMaxNonUniformAMD\0" // IR(35826, 23)
  "GroupSMaxNonUniformAMD\0" // IR(35849, 23)
  "FragmentMaskFetchAMD\0" // IR(35872, 21)
  "FragmentFetchAMD\0" // IR(35893, 17)
  "ReadClockKHR\0" // IR(35910, 13)
  "AllocateNodePayloadsAMDX\0" // IR(35923, 25)
  "EnqueueNodePayloadsAMDX\0" // IR(35948, 24)
  "TypeNodePayloadArrayAMDX\0" // IR(35972, 25)
  "FinishWritingNodePayloadAMDX\0" // IR(35997, 29)
  "NodePayloadArrayLengthAMDX\0" // IR(36026, 27)
  "IsNodePayloadValidAMDX\0" // IR(36053, 23)
  "ConstantStringAMDX\0" // IR(36076, 19)
  "SpecConstantStringAMDX\0" // IR(36095, 23)
  "GroupNonUniformQuadAllKHR\0" // IR(36118, 26)
  "GroupNonUniformQuadAnyKHR\0" // IR(36144, 26)
  "HitObjectRecordHitMotionNV\0" // IR(36170, 27)
  "HitObjectRecordHitWithIndexMotionNV\0" // IR(36197, 36)
  "HitObjectRecordMissMotionNV\0" // IR(36233, 28)
  "HitObjectGetWorldToObjectNV\0" // IR(36261, 28)
  "HitObjectGetObjectToWorldNV\0" // IR(36289, 28)
  "HitObjectGetObjectRayDirectionNV\0" // IR(36317, 33)
  "HitObjectGetObjectRayOriginNV\0" // IR(36350, 30)
  "HitObjectTraceRayMotionNV\0" // IR(36380, 26)
  "HitObjectGetShaderRecordBufferHandleNV\0" // IR(36406, 39)
  "HitObjectGetShaderBindingTableRecordIndexNV\0" // IR(36445, 44)
  "HitObjectRecordEmptyNV\0" // IR(36489, 23)
  "HitObjectTraceRayNV\0" // IR(36512, 20)
  "HitObjectRecordHitNV\0" // IR(36532, 21)
  "HitObjectRecordHitWithIndexNV\0" // IR(36553, 30)
  "HitObjectRecordMissNV\0" // IR(36583, 22)
  "HitObjectExecuteShaderNV\0" // IR(36605, 25)
  "HitObjectGetCurrentTimeNV\0" // IR(36630, 26)
  "HitObjectGetAttributesNV\0" // IR(36656, 25)
  "HitObjectGetHitKindNV\0" // IR(36681, 22)
  "HitObjectGetPrimitiveIndexNV\0" // IR(36703, 29)
  "HitObjectGetGeometryIndexNV\0" // IR(36732, 28)
  "HitObjectGetInstanceIdNV\0" // IR(36760, 25)
  "HitObjectGetInstanceCustomIndexNV\0" // IR(36785, 34)
  "HitObjectGetWorldRayDirectionNV\0" // IR(36819, 32)
  "HitObjectGetWorldRayOriginNV\0" // IR(36851, 29)
  "HitObjectGetRayTMaxNV\0" // IR(36880, 22)
  "HitObjectGetRayTMinNV\0" // IR(36902, 22)
  "HitObjectIsEmptyNV\0" // IR(36924, 19)
  "HitObjectIsHitNV\0" // IR(36943, 17)
  "HitObjectIsMissNV\0" // IR(36960, 18)
  "ReorderThreadWithHitObjectNV\0" // IR(36978, 29)
  "ReorderThreadWithHintNV\0" // IR(37007, 24)
  "TypeHitObjectNV\0" // IR(37031, 16)
  "ImageSampleFootprintNV\0" // IR(37047, 23)
  "TypeCooperativeVectorNV\0" // IR(37070, 24)
  "TypeVectorIdEXT\0" // IR(37094, 16)
  "CooperativeVectorMatrixMulNV\0" // IR(37110, 29)
  "CooperativeVectorOuterProductAccumulateNV\0" // IR(37139, 42)
  "CooperativeVectorReduceSumAccumulateNV\0" // IR(37181, 39)
  "CooperativeVectorMatrixMulAddNV\0" // IR(37220, 32)
  "CooperativeMatrixConvertNV\0" // IR(37252, 27)
  "EmitMeshTasksEXT\0" // IR(37279, 17)
  "SetMeshOutputsEXT\0" // IR(37296, 18)
  "GroupNonUniformPartitionNV\0" // IR(37314, 27)
  "WritePackedPrimitiveIndices4x8NV\0" // IR(37341, 33)
  "FetchMicroTriangleVertexPositionNV\0" // IR(37374, 35)
  "FetchMicroTriangleVertexBarycentricNV\0" // IR(37409, 38)
  "CooperativeVectorLoadNV\0" // IR(37447, 24)
  "CooperativeVectorStoreNV\0" // IR(37471, 25)
  "HitObjectRecordFromQueryEXT\0" // IR(37496, 28)
  "HitObjectRecordMissEXT\0" // IR(37524, 23)
  "HitObjectRecordMissMotionEXT\0" // IR(37547, 29)
  "HitObjectGetIntersectionTriangleVertexPositionsEXT\0" // IR(37576, 51)
  "HitObjectGetRayFlagsEXT\0" // IR(37627, 24)
  "HitObjectSetShaderBindingTableRecordIndexEXT\0" // IR(37651, 45)
  "HitObjectReorderExecuteShaderEXT\0" // IR(37696, 33)
  "HitObjectTraceReorderExecuteEXT\0" // IR(37729, 32)
  "HitObjectTraceMotionReorderExecuteEXT\0" // IR(37761, 38)
  "TypeHitObjectEXT\0" // IR(37799, 17)
  "ReorderThreadWithHintEXT\0" // IR(37816, 25)
  "ReorderThreadWithHitObjectEXT\0" // IR(37841, 30)
  "HitObjectTraceRayEXT\0" // IR(37871, 21)
  "HitObjectTraceRayMotionEXT\0" // IR(37892, 27)
  "HitObjectRecordEmptyEXT\0" // IR(37919, 24)
  "HitObjectExecuteShaderEXT\0" // IR(37943, 26)
  "HitObjectGetCurrentTimeEXT\0" // IR(37969, 27)
  "HitObjectGetAttributesEXT\0" // IR(37996, 26)
  "HitObjectGetHitKindEXT\0" // IR(38022, 23)
  "HitObjectGetPrimitiveIndexEXT\0" // IR(38045, 30)
  "HitObjectGetGeometryIndexEXT\0" // IR(38075, 29)
  "HitObjectGetInstanceIdEXT\0" // IR(38104, 26)
  "HitObjectGetInstanceCustomIndexEXT\0" // IR(38130, 35)
  "HitObjectGetObjectRayOriginEXT\0" // IR(38165, 31)
  "HitObjectGetObjectRayDirectionEXT\0" // IR(38196, 34)
  "HitObjectGetWorldRayDirectionEXT\0" // IR(38230, 33)
  "HitObjectGetWorldRayOriginEXT\0" // IR(38263, 30)
  "HitObjectGetObjectToWorldEXT\0" // IR(38293, 29)
  "HitObjectGetWorldToObjectEXT\0" // IR(38322, 29)
  "HitObjectGetRayTMaxEXT\0" // IR(38351, 23)
  "ReportIntersectionKHR\0" // IR(38374, 22)
  "ReportIntersectionNV\0" // IR(38396, 21)
  "IgnoreIntersectionNV\0" // IR(38417, 21)
  "TerminateRayNV\0" // IR(38438, 15)
  "TraceNV\0" // IR(38453, 8)
  "TraceMotionNV\0" // IR(38461, 14)
  "TraceRayMotionNV\0" // IR(38475, 17)
  "RayQueryGetIntersectionTriangleVertexPositionsKHR\0" // IR(38492, 50)
  "TypeAccelerationStructureKHR\0" // IR(38542, 29)
  "TypeAccelerationStructureNV\0" // IR(38571, 28)
  "ExecuteCallableNV\0" // IR(38599, 18)
  "RayQueryGetIntersectionClusterIdNV\0" // IR(38617, 35)
  "RayQueryGetClusterIdNV\0" // IR(38652, 23)
  "HitObjectGetClusterIdNV\0" // IR(38675, 24)
  "HitObjectGetRayTMinEXT\0" // IR(38699, 23)
  "HitObjectGetShaderBindingTableRecordIndexEXT\0" // IR(38722, 45)
  "HitObjectGetShaderRecordBufferHandleEXT\0" // IR(38767, 40)
  "HitObjectIsEmptyEXT\0" // IR(38807, 20)
  "HitObjectIsHitEXT\0" // IR(38827, 18)
  "HitObjectIsMissEXT\0" // IR(38845, 19)
  "TypeCooperativeMatrixNV\0" // IR(38864, 24)
  "CooperativeMatrixLoadNV\0" // IR(38888, 24)
  "CooperativeMatrixStoreNV\0" // IR(38912, 25)
  "CooperativeMatrixMulAddNV\0" // IR(38937, 26)
  "CooperativeMatrixLengthNV\0" // IR(38963, 26)
  "BeginInvocationInterlockEXT\0" // IR(38989, 28)
  "EndInvocationInterlockEXT\0" // IR(39017, 26)
  "SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE\0" // IR(39043, 43)
  "CooperativeMatrixReduceNV\0" // IR(39086, 26)
  "SPV_OPERAND_TYPE_MEMORY_ACCESS\0" // IR(39112, 31)
  "SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS\0" // IR(39143, 44)
  "CooperativeMatrixLoadTensorNV\0" // IR(39187, 30)
  "CooperativeMatrixStoreTensorNV\0" // IR(39217, 31)
  "CooperativeMatrixPerElementOpNV\0" // IR(39248, 32)
  "TypeTensorLayoutNV\0" // IR(39280, 19)
  "TypeTensorViewNV\0" // IR(39299, 17)
  "CreateTensorLayoutNV\0" // IR(39316, 21)
  "TensorLayoutSetDimensionNV\0" // IR(39337, 27)
  "TensorLayoutSetStrideNV\0" // IR(39364, 24)
  "TensorLayoutSliceNV\0" // IR(39388, 20)
  "TensorLayoutSetClampValueNV\0" // IR(39408, 28)
  "CreateTensorViewNV\0" // IR(39436, 19)
  "TensorViewSetDimensionNV\0" // IR(39455, 25)
  "TensorViewSetStrideNV\0" // IR(39480, 22)
  "IsHelperInvocationEXT\0" // IR(39502, 22)
  "TensorViewSetClipNV\0" // IR(39524, 20)
  "TensorLayoutSetBlockSizeNV\0" // IR(39544, 27)
  "CooperativeMatrixTransposeNV\0" // IR(39571, 29)
  "ConvertUToImageNV\0" // IR(39600, 18)
  "ConvertUToSamplerNV\0" // IR(39618, 20)
  "ConvertImageToUNV\0" // IR(39638, 18)
  "ConvertSamplerToUNV\0" // IR(39656, 20)
  "ConvertUToSampledImageNV\0" // IR(39676, 25)
  "ConvertSampledImageToUNV\0" // IR(39701, 25)
  "SamplerImageAddressingModeNV\0" // IR(39726, 29)
  "SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS\0" // IR(39755, 52)
  "RawAccessChainNV\0" // IR(39807, 17)
  "RayQueryGetIntersectionSpherePositionNV\0" // IR(39824, 40)
  "RayQueryGetIntersectionSphereRadiusNV\0" // IR(39864, 38)
  "RayQueryGetIntersectionLSSPositionsNV\0" // IR(39902, 38)
  "RayQueryGetIntersectionLSSRadiiNV\0" // IR(39940, 34)
  "RayQueryGetIntersectionLSSHitValueNV\0" // IR(39974, 37)
  "HitObjectGetSpherePositionNV\0" // IR(40011, 29)
  "HitObjectGetSphereRadiusNV\0" // IR(40040, 27)
  "HitObjectGetLSSPositionsNV\0" // IR(40067, 27)
  "HitObjectGetLSSRadiiNV\0" // IR(40094, 23)
  "HitObjectIsSphereHitNV\0" // IR(40117, 23)
  "HitObjectIsLSSHitNV\0" // IR(40140, 20)
  "RayQueryIsSphereHitNV\0" // IR(40160, 22)
  "RayQueryIsLSSHitNV\0" // IR(40182, 19)
  "SubgroupShuffleDownINTEL\0" // IR(40201, 25)
  "SubgroupShuffleUpINTEL\0" // IR(40226, 23)
  "SubgroupShuffleXorINTEL\0" // IR(40249, 24)
  "SubgroupBlockReadINTEL\0" // IR(40273, 23)
  "SubgroupBlockWriteINTEL\0" // IR(40296, 24)
  "SubgroupImageBlockReadINTEL\0" // IR(40320, 28)
  "SubgroupImageBlockWriteINTEL\0" // IR(40348, 29)
  "SubgroupImageMediaBlockReadINTEL\0" // IR(40377, 33)
  "SubgroupImageMediaBlockWriteINTEL\0" // IR(40410, 34)
  "UCountLeadingZerosINTEL\0" // IR(40444, 24)
  "UCountTrailingZerosINTEL\0" // IR(40468, 25)
  "AbsISubINTEL\0" // IR(40493, 13)
  "AbsUSubINTEL\0" // IR(40506, 13)
  "IAddSatINTEL\0" // IR(40519, 13)
  "UAddSatINTEL\0" // IR(40532, 13)
  "IAverageINTEL\0" // IR(40545, 14)
  "UAverageINTEL\0" // IR(40559, 14)
  "IAverageRoundedINTEL\0" // IR(40573, 21)
  "UAverageRoundedINTEL\0" // IR(40594, 21)
  "ISubSatINTEL\0" // IR(40615, 13)
  "USubSatINTEL\0" // IR(40628, 13)
  "IMul32x16INTEL\0" // IR(40641, 15)
  "UMul32x16INTEL\0" // IR(40656, 15)
  "ConstantFunctionPointerINTEL\0" // IR(40671, 29)
  "FunctionPointerCallINTEL\0" // IR(40700, 25)
  "AsmTargetINTEL\0" // IR(40725, 15)
  "AsmCallINTEL\0" // IR(40740, 13)
  "AtomicFMinEXT\0" // IR(40753, 14)
  "AtomicFMaxEXT\0" // IR(40767, 14)
  "AssumeTrueKHR\0" // IR(40781, 14)
  "ExpectKHR\0" // IR(40795, 10)
  "DecorateString\0" // IR(40805, 15)
  "DecorateStringGOOGLE\0" // IR(40820, 21)
  "MemberDecorateString\0" // IR(40841, 21)
  "MemberDecorateStringGOOGLE\0" // IR(40862, 27)
  "VmeImageINTEL\0" // IR(40889, 14)
  "TypeVmeImageINTEL\0" // IR(40903, 18)
  "TypeAvcImePayloadINTEL\0" // IR(40921, 23)
  "TypeAvcRefPayloadINTEL\0" // IR(40944, 23)
  "TypeAvcSicPayloadINTEL\0" // IR(40967, 23)
  "TypeAvcMcePayloadINTEL\0" // IR(40990, 23)
  "TypeAvcMceResultINTEL\0" // IR(41013, 22)
  "TypeAvcImeResultINTEL\0" // IR(41035, 22)
  "TypeAvcImeResultSingleReferenceStreamoutINTEL\0" // IR(41057, 46)
  "TypeAvcImeResultDualReferenceStreamoutINTEL\0" // IR(41103, 44)
  "TypeAvcImeSingleReferenceStreaminINTEL\0" // IR(41147, 39)
  "TypeAvcImeDualReferenceStreaminINTEL\0" // IR(41186, 37)
  "TypeAvcRefResultINTEL\0" // IR(41223, 22)
  "TypeAvcSicResultINTEL\0" // IR(41245, 22)
  "SubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL\0" // IR(41267, 60)
  "SubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL\0" // IR(41327, 53)
  "SubgroupAvcMceGetDefaultInterShapePenaltyINTEL\0" // IR(41380, 47)
  "SubgroupAvcMceSetInterShapePenaltyINTEL\0" // IR(41427, 40)
  "SubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL\0" // IR(41467, 51)
  "SubgroupAvcMceSetInterDirectionPenaltyINTEL\0" // IR(41518, 44)
  "SubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL\0" // IR(41562, 51)
  "SubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL\0" // IR(41613, 56)
  "SubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL\0" // IR(41669, 50)
  "SubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL\0" // IR(41719, 52)
  "SubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL\0" // IR(41771, 49)
  "SubgroupAvcMceSetMotionVectorCostFunctionINTEL\0" // IR(41820, 47)
  "SubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL\0" // IR(41867, 50)
  "SubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL\0" // IR(41917, 51)
  "SubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL\0" // IR(41968, 56)
  "SubgroupAvcMceSetAcOnlyHaarINTEL\0" // IR(42024, 33)
  "SubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL\0" // IR(42057, 52)
  "SubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL\0" // IR(42109, 61)
  "SubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL\0" // IR(42170, 61)
  "SubgroupAvcMceConvertToImePayloadINTEL\0" // IR(42231, 39)
  "SubgroupAvcMceConvertToImeResultINTEL\0" // IR(42270, 38)
  "SubgroupAvcMceConvertToRefPayloadINTEL\0" // IR(42308, 39)
  "SubgroupAvcMceConvertToRefResultINTEL\0" // IR(42347, 38)
  "SubgroupAvcMceConvertToSicPayloadINTEL\0" // IR(42385, 39)
  "SubgroupAvcMceConvertToSicResultINTEL\0" // IR(42424, 38)
  "SubgroupAvcMceGetMotionVectorsINTEL\0" // IR(42462, 36)
  "SubgroupAvcMceGetInterDistortionsINTEL\0" // IR(42498, 39)
  "SubgroupAvcMceGetBestInterDistortionsINTEL\0" // IR(42537, 43)
  "SubgroupAvcMceGetInterMajorShapeINTEL\0" // IR(42580, 38)
  "SubgroupAvcMceGetInterMinorShapeINTEL\0" // IR(42618, 38)
  "SubgroupAvcMceGetInterDirectionsINTEL\0" // IR(42656, 38)
  "SubgroupAvcMceGetInterMotionVectorCountINTEL\0" // IR(42694, 45)
  "SubgroupAvcMceGetInterReferenceIdsINTEL\0" // IR(42739, 40)
  "SubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL\0" // IR(42779, 62)
  "SubgroupAvcImeInitializeINTEL\0" // IR(42841, 30)
  "SubgroupAvcImeSetSingleReferenceINTEL\0" // IR(42871, 38)
  "SubgroupAvcImeSetDualReferenceINTEL\0" // IR(42909, 36)
  "SubgroupAvcImeRefWindowSizeINTEL\0" // IR(42945, 33)
  "SubgroupAvcImeAdjustRefOffsetINTEL\0" // IR(42978, 35)
  "SubgroupAvcImeConvertToMcePayloadINTEL\0" // IR(43013, 39)
  "SubgroupAvcImeSetMaxMotionVectorCountINTEL\0" // IR(43052, 43)
  "SubgroupAvcImeSetUnidirectionalMixDisableINTEL\0" // IR(43095, 47)
  "SubgroupAvcImeSetEarlySearchTerminationThresholdINTEL\0" // IR(43142, 54)
  "SubgroupAvcImeSetWeightedSadINTEL\0" // IR(43196, 34)
  "SubgroupAvcImeEvaluateWithSingleReferenceINTEL\0" // IR(43230, 47)
  "SubgroupAvcImeEvaluateWithDualReferenceINTEL\0" // IR(43277, 45)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL\0" // IR(43322, 55)
  "SubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL\0" // IR(43377, 53)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL\0" // IR(43430, 56)
  "SubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL\0" // IR(43486, 54)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL\0" // IR(43540, 58)
  "SubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL\0" // IR(43598, 56)
  "SubgroupAvcImeConvertToMceResultINTEL\0" // IR(43654, 38)
  "SubgroupAvcImeGetSingleReferenceStreaminINTEL\0" // IR(43692, 46)
  "SubgroupAvcImeGetDualReferenceStreaminINTEL\0" // IR(43738, 44)
  "SubgroupAvcImeStripSingleReferenceStreamoutINTEL\0" // IR(43782, 49)
  "SubgroupAvcImeStripDualReferenceStreamoutINTEL\0" // IR(43831, 47)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL\0" // IR(43878, 70)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL\0" // IR(43948, 68)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL\0" // IR(44016, 69)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL\0" // IR(44085, 68)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL\0" // IR(44153, 66)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL\0" // IR(44219, 67)
  "SubgroupAvcImeGetBorderReachedINTEL\0" // IR(44286, 36)
  "SubgroupAvcImeGetTruncatedSearchIndicationINTEL\0" // IR(44322, 48)
  "SubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL\0" // IR(44370, 59)
  "SubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL\0" // IR(44429, 58)
  "SubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL\0" // IR(44487, 56)
  "SubgroupAvcFmeInitializeINTEL\0" // IR(44543, 30)
  "SubgroupAvcBmeInitializeINTEL\0" // IR(44573, 30)
  "SubgroupAvcRefConvertToMcePayloadINTEL\0" // IR(44603, 39)
  "SubgroupAvcRefSetBidirectionalMixDisableINTEL\0" // IR(44642, 46)
  "SubgroupAvcRefSetBilinearFilterEnableINTEL\0" // IR(44688, 43)
  "SubgroupAvcRefEvaluateWithSingleReferenceINTEL\0" // IR(44731, 47)
  "SubgroupAvcRefEvaluateWithDualReferenceINTEL\0" // IR(44778, 45)
  "SubgroupAvcRefEvaluateWithMultiReferenceINTEL\0" // IR(44823, 46)
  "SubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL\0" // IR(44869, 56)
  "SubgroupAvcRefConvertToMceResultINTEL\0" // IR(44925, 38)
  "SubgroupAvcSicInitializeINTEL\0" // IR(44963, 30)
  "SubgroupAvcSicConfigureSkcINTEL\0" // IR(44993, 32)
  "SubgroupAvcSicConfigureIpeLumaINTEL\0" // IR(45025, 36)
  "SubgroupAvcSicConfigureIpeLumaChromaINTEL\0" // IR(45061, 42)
  "SubgroupAvcSicGetMotionVectorMaskINTEL\0" // IR(45103, 39)
  "SubgroupAvcSicConvertToMcePayloadINTEL\0" // IR(45142, 39)
  "SubgroupAvcSicSetIntraLumaShapePenaltyINTEL\0" // IR(45181, 44)
  "SubgroupAvcSicSetIntraLumaModeCostFunctionINTEL\0" // IR(45225, 48)
  "SubgroupAvcSicSetIntraChromaModeCostFunctionINTEL\0" // IR(45273, 50)
  "SubgroupAvcSicSetBilinearFilterEnableINTEL\0" // IR(45323, 43)
  "SubgroupAvcSicSetSkcForwardTransformEnableINTEL\0" // IR(45366, 48)
  "SubgroupAvcSicSetBlockBasedRawSkipSadINTEL\0" // IR(45414, 43)
  "SubgroupAvcSicEvaluateIpeINTEL\0" // IR(45457, 31)
  "SubgroupAvcSicEvaluateWithSingleReferenceINTEL\0" // IR(45488, 47)
  "SubgroupAvcSicEvaluateWithDualReferenceINTEL\0" // IR(45535, 45)
  "SubgroupAvcSicEvaluateWithMultiReferenceINTEL\0" // IR(45580, 46)
  "SubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL\0" // IR(45626, 56)
  "SubgroupAvcSicConvertToMceResultINTEL\0" // IR(45682, 38)
  "SubgroupAvcSicGetIpeLumaShapeINTEL\0" // IR(45720, 35)
  "SubgroupAvcSicGetBestIpeLumaDistortionINTEL\0" // IR(45755, 44)
  "SubgroupAvcSicGetBestIpeChromaDistortionINTEL\0" // IR(45799, 46)
  "SubgroupAvcSicGetPackedIpeLumaModesINTEL\0" // IR(45845, 41)
  "SubgroupAvcSicGetIpeChromaModeINTEL\0" // IR(45886, 36)
  "SubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL\0" // IR(45922, 50)
  "SubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL\0" // IR(45972, 48)
  "SubgroupAvcSicGetInterRawSadsINTEL\0" // IR(46020, 35)
  "SaveMemoryINTEL\0" // IR(46055, 16)
  "RestoreMemoryINTEL\0" // IR(46071, 19)
  "ArbitraryFloatSinCosPiALTERA\0" // IR(46090, 29)
  "ArbitraryFloatSinCosPiINTEL\0" // IR(46119, 28)
  "ArbitraryFloatCastALTERA\0" // IR(46147, 25)
  "ArbitraryFloatCastINTEL\0" // IR(46172, 24)
  "ArbitraryFloatCastFromIntALTERA\0" // IR(46196, 32)
  "ArbitraryFloatCastFromIntINTEL\0" // IR(46228, 31)
  "ArbitraryFloatCastToIntALTERA\0" // IR(46259, 30)
  "ArbitraryFloatCastToIntINTEL\0" // IR(46289, 29)
  "ArbitraryFloatAddALTERA\0" // IR(46318, 24)
  "ArbitraryFloatAddINTEL\0" // IR(46342, 23)
  "ArbitraryFloatSubALTERA\0" // IR(46365, 24)
  "ArbitraryFloatSubINTEL\0" // IR(46389, 23)
  "ArbitraryFloatMulALTERA\0" // IR(46412, 24)
  "ArbitraryFloatMulINTEL\0" // IR(46436, 23)
  "ArbitraryFloatDivALTERA\0" // IR(46459, 24)
  "ArbitraryFloatDivINTEL\0" // IR(46483, 23)
  "ArbitraryFloatGTALTERA\0" // IR(46506, 23)
  "ArbitraryFloatGTINTEL\0" // IR(46529, 22)
  "ArbitraryFloatGEALTERA\0" // IR(46551, 23)
  "ArbitraryFloatGEINTEL\0" // IR(46574, 22)
  "ArbitraryFloatLTALTERA\0" // IR(46596, 23)
  "ArbitraryFloatLTINTEL\0" // IR(46619, 22)
  "ArbitraryFloatLEALTERA\0" // IR(46641, 23)
  "ArbitraryFloatLEINTEL\0" // IR(46664, 22)
  "ArbitraryFloatEQALTERA\0" // IR(46686, 23)
  "ArbitraryFloatEQINTEL\0" // IR(46709, 22)
  "ArbitraryFloatRecipALTERA\0" // IR(46731, 26)
  "ArbitraryFloatRecipINTEL\0" // IR(46757, 25)
  "ArbitraryFloatRSqrtALTERA\0" // IR(46782, 26)
  "ArbitraryFloatRSqrtINTEL\0" // IR(46808, 25)
  "ArbitraryFloatCbrtALTERA\0" // IR(46833, 25)
  "ArbitraryFloatCbrtINTEL\0" // IR(46858, 24)
  "ArbitraryFloatHypotALTERA\0" // IR(46882, 26)
  "ArbitraryFloatHypotINTEL\0" // IR(46908, 25)
  "ArbitraryFloatSqrtALTERA\0" // IR(46933, 25)
  "ArbitraryFloatSqrtINTEL\0" // IR(46958, 24)
  "ArbitraryFloatLogINTEL\0" // IR(46982, 23)
  "ArbitraryFloatLog2INTEL\0" // IR(47005, 24)
  "ArbitraryFloatLog10INTEL\0" // IR(47029, 25)
  "ArbitraryFloatLog1pINTEL\0" // IR(47054, 25)
  "ArbitraryFloatExpINTEL\0" // IR(47079, 23)
  "ArbitraryFloatExp2INTEL\0" // IR(47102, 24)
  "ArbitraryFloatExp10INTEL\0" // IR(47126, 25)
  "ArbitraryFloatExpm1INTEL\0" // IR(47151, 25)
  "ArbitraryFloatSinINTEL\0" // IR(47176, 23)
  "ArbitraryFloatCosINTEL\0" // IR(47199, 23)
  "ArbitraryFloatSinCosINTEL\0" // IR(47222, 26)
  "ArbitraryFloatSinPiINTEL\0" // IR(47248, 25)
  "ArbitraryFloatCosPiINTEL\0" // IR(47273, 25)
  "ArbitraryFloatASinINTEL\0" // IR(47298, 24)
  "ArbitraryFloatASinPiINTEL\0" // IR(47322, 26)
  "ArbitraryFloatACosINTEL\0" // IR(47348, 24)
  "ArbitraryFloatACosPiINTEL\0" // IR(47372, 26)
  "ArbitraryFloatATanINTEL\0" // IR(47398, 24)
  "ArbitraryFloatATanPiINTEL\0" // IR(47422, 26)
  "ArbitraryFloatATan2INTEL\0" // IR(47448, 25)
  "ArbitraryFloatPowINTEL\0" // IR(47473, 23)
  "ArbitraryFloatPowRINTEL\0" // IR(47496, 24)
  "ArbitraryFloatPowNINTEL\0" // IR(47520, 24)
  "LoopControlINTEL\0" // IR(47544, 17)
  "AliasDomainDeclINTEL\0" // IR(47561, 21)
  "AliasScopeDeclINTEL\0" // IR(47582, 20)
  "AliasScopeListDeclINTEL\0" // IR(47602, 24)
  "FixedSqrtALTERA\0" // IR(47626, 16)
  "FixedSqrtINTEL\0" // IR(47642, 15)
  "FixedRecipALTERA\0" // IR(47657, 17)
  "FixedRecipINTEL\0" // IR(47674, 16)
  "FixedRsqrtALTERA\0" // IR(47690, 17)
  "FixedRsqrtINTEL\0" // IR(47707, 16)
  "FixedSinALTERA\0" // IR(47723, 15)
  "FixedSinINTEL\0" // IR(47738, 14)
  "FixedCosALTERA\0" // IR(47752, 15)
  "FixedCosINTEL\0" // IR(47767, 14)
  "FixedSinCosALTERA\0" // IR(47781, 18)
  "FixedSinCosINTEL\0" // IR(47799, 17)
  "FixedSinPiALTERA\0" // IR(47816, 17)
  "FixedSinPiINTEL\0" // IR(47833, 16)
  "FixedCosPiALTERA\0" // IR(47849, 17)
  "FixedCosPiINTEL\0" // IR(47866, 16)
  "FixedSinCosPiALTERA\0" // IR(47882, 20)
  "FixedSinCosPiINTEL\0" // IR(47902, 19)
  "FixedLogALTERA\0" // IR(47921, 15)
  "FixedLogINTEL\0" // IR(47936, 14)
  "FixedExpALTERA\0" // IR(47950, 15)
  "FixedExpINTEL\0" // IR(47965, 14)
  "PtrCastToCrossWorkgroupALTERA\0" // IR(47979, 30)
  "PtrCastToCrossWorkgroupINTEL\0" // IR(48009, 29)
  "CrossWorkgroupCastToPtrALTERA\0" // IR(48038, 30)
  "CrossWorkgroupCastToPtrINTEL\0" // IR(48068, 29)
  "ReadPipeBlockingALTERA\0" // IR(48097, 23)
  "ReadPipeBlockingINTEL\0" // IR(48120, 22)
  "WritePipeBlockingALTERA\0" // IR(48142, 24)
  "WritePipeBlockingINTEL\0" // IR(48166, 23)
  "RayQueryGetRayTMinKHR\0" // IR(48189, 22)
  "RayQueryGetRayFlagsKHR\0" // IR(48211, 23)
  "RayQueryGetIntersectionTKHR\0" // IR(48234, 28)
  "RayQueryGetIntersectionInstanceCustomIndexKHR\0" // IR(48262, 46)
  "RayQueryGetIntersectionInstanceIdKHR\0" // IR(48308, 37)
  "RayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR\0" // IR(48345, 65)
  "RayQueryGetIntersectionGeometryIndexKHR\0" // IR(48410, 40)
  "RayQueryGetIntersectionPrimitiveIndexKHR\0" // IR(48450, 41)
  "RayQueryGetIntersectionBarycentricsKHR\0" // IR(48491, 39)
  "RayQueryGetIntersectionFrontFaceKHR\0" // IR(48530, 36)
  "RayQueryGetIntersectionCandidateAABBOpaqueKHR\0" // IR(48566, 46)
  "RayQueryGetIntersectionObjectRayDirectionKHR\0" // IR(48612, 45)
  "RayQueryGetIntersectionObjectRayOriginKHR\0" // IR(48657, 42)
  "RayQueryGetWorldRayDirectionKHR\0" // IR(48699, 32)
  "RayQueryGetWorldRayOriginKHR\0" // IR(48731, 29)
  "RayQueryGetIntersectionObjectToWorldKHR\0" // IR(48760, 40)
  "RayQueryGetIntersectionWorldToObjectKHR\0" // IR(48800, 40)
  "AtomicFAddEXT\0" // IR(48840, 14)
  "TypeBufferSurfaceINTEL\0" // IR(48854, 23)
  "TypeStructContinuedINTEL\0" // IR(48877, 25)
  "ConstantCompositeContinuedINTEL\0" // IR(48902, 32)
  "SpecConstantCompositeContinuedINTEL\0" // IR(48934, 36)
  "CompositeConstructContinuedINTEL\0" // IR(48970, 33)
  "ConvertFToBF16INTEL\0" // IR(49003, 20)
  "ConvertBF16ToFINTEL\0" // IR(49023, 20)
  "ControlBarrierArriveINTEL\0" // IR(49043, 26)
  "ControlBarrierWaitINTEL\0" // IR(49069, 24)
  "TaskSequenceCreateALTERA\0" // IR(49093, 25)
  "TaskSequenceCreateINTEL\0" // IR(49118, 24)
  "TaskSequenceAsyncALTERA\0" // IR(49142, 24)
  "TaskSequenceAsyncINTEL\0" // IR(49166, 23)
  "TaskSequenceGetALTERA\0" // IR(49189, 22)
  "TaskSequenceGetINTEL\0" // IR(49211, 21)
  "TaskSequenceReleaseALTERA\0" // IR(49232, 26)
  "TaskSequenceReleaseINTEL\0" // IR(49258, 25)
  "TypeTaskSequenceALTERA\0" // IR(49283, 23)
  "TypeTaskSequenceINTEL\0" // IR(49306, 22)
  "SubgroupBlockPrefetchINTEL\0" // IR(49328, 27)
  "Subgroup2DBlockLoadINTEL\0" // IR(49355, 25)
  "Subgroup2DBlockLoadTransformINTEL\0" // IR(49380, 34)
  "Subgroup2DBlockLoadTransposeINTEL\0" // IR(49414, 34)
  "Subgroup2DBlockPrefetchINTEL\0" // IR(49448, 29)
  "Subgroup2DBlockStoreINTEL\0" // IR(49477, 26)
  "SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS\0" // IR(49503, 62)
  "BitwiseFunctionINTEL\0" // IR(49565, 21)
  "ConditionalExtensionINTEL\0" // IR(49586, 26)
  "ConditionalEntryPointINTEL\0" // IR(49612, 27)
  "ConditionalCapabilityINTEL\0" // IR(49639, 27)
  "SpecConstantTargetINTEL\0" // IR(49666, 24)
  "SpecConstantArchitectureINTEL\0" // IR(49690, 30)
  "SPV_OPERAND_TYPE_VARIABLE_CAPABILITY\0" // IR(49720, 37)
  "SpecConstantCapabilitiesINTEL\0" // IR(49757, 30)
  "ConditionalCopyObjectINTEL\0" // IR(49787, 27)
  "GroupIMulKHR\0" // IR(49814, 13)
  "GroupFMulKHR\0" // IR(49827, 13)
  "GroupBitwiseAndKHR\0" // IR(49840, 19)
  "GroupBitwiseOrKHR\0" // IR(49859, 18)
  "GroupBitwiseXorKHR\0" // IR(49877, 19)
  "GroupLogicalAndKHR\0" // IR(49896, 19)
  "GroupLogicalOrKHR\0" // IR(49915, 18)
  "GroupLogicalXorKHR\0" // IR(49933, 19)
  "RoundFToTF32INTEL\0" // IR(49952, 18)
  "MaskedGatherINTEL\0" // IR(49970, 18)
  "MaskedScatterINTEL\0" // IR(49988, 19)
  "ConvertHandleToImageINTEL\0" // IR(50007, 26)
  "ConvertHandleToSamplerINTEL\0" // IR(50033, 28)
  "ConvertHandleToSampledImageINTEL\0" // IR(50061, 33)
  "DebugInfoNone\0" // IR(50094, 14)
  "DebugCompilationUnit\0" // IR(50108, 21)
  "SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING\0" // IR(50129, 52)
  "DebugTypeBasic\0" // IR(50181, 15)
  "SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS\0" // IR(50196, 34)
  "DebugTypePointer\0" // IR(50230, 17)
  "SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER\0" // IR(50247, 38)
  "DebugTypeQualifier\0" // IR(50285, 19)
  "DebugTypeArray\0" // IR(50304, 15)
  "DebugTypeVector\0" // IR(50319, 16)
  "DebugTypedef\0" // IR(50335, 13)
  "DebugTypeFunction\0" // IR(50348, 18)
  "DebugTypeEnum\0" // IR(50366, 14)
  "SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE\0" // IR(50380, 38)
  "DebugTypeComposite\0" // IR(50418, 19)
  "DebugTypeMember\0" // IR(50437, 16)
  "DebugTypeInheritance\0" // IR(50453, 21)
  "DebugTypePtrToMember\0" // IR(50474, 21)
  "DebugTypeTemplate\0" // IR(50495, 18)
  "DebugTypeTemplateParameter\0" // IR(50513, 27)
  "DebugTypeTemplateTemplateParameter\0" // IR(50540, 35)
  "DebugTypeTemplateParameterPack\0" // IR(50575, 31)
  "DebugGlobalVariable\0" // IR(50606, 20)
  "DebugFunctionDeclaration\0" // IR(50626, 25)
  "DebugFunction\0" // IR(50651, 14)
  "DebugLexicalBlock\0" // IR(50665, 18)
  "DebugLexicalBlockDiscriminator\0" // IR(50683, 31)
  "DebugScope\0" // IR(50714, 11)
  "DebugNoScope\0" // IR(50725, 13)
  "DebugInlinedAt\0" // IR(50738, 15)
  "SPV_OPERAND_TYPE_OPTIONAL_LITERAL_INTEGER\0" // IR(50753, 42)
  "DebugLocalVariable\0" // IR(50795, 19)
  "DebugInlinedVariable\0" // IR(50814, 21)
  "DebugDeclare\0" // IR(50835, 13)
  "DebugValue\0" // IR(50848, 11)
  "SPV_OPERAND_TYPE_DEBUG_OPERATION\0" // IR(50859, 33)
  "DebugOperation\0" // IR(50892, 15)
  "DebugExpression\0" // IR(50907, 16)
  "DebugMacroDef\0" // IR(50923, 14)
  "DebugMacroUndef\0" // IR(50937, 16)
  "Round\0" // IR(50953, 6)
  "RoundEven\0" // IR(50959, 10)
  "Trunc\0" // IR(50969, 6)
  "FAbs\0" // IR(50975, 5)
  "SAbs\0" // IR(50980, 5)
  "FSign\0" // IR(50985, 6)
  "SSign\0" // IR(50991, 6)
  "Floor\0" // IR(50997, 6)
  "Ceil\0" // IR(51003, 5)
  "Fract\0" // IR(51008, 6)
  "Radians\0" // IR(51014, 8)
  "Degrees\0" // IR(51022, 8)
  "Sin\0" // IR(51030, 4)
  "Cos\0" // IR(51034, 4)
  "Tan\0" // IR(51038, 4)
  "Asin\0" // IR(51042, 5)
  "Acos\0" // IR(51047, 5)
  "Atan\0" // IR(51052, 5)
  "Sinh\0" // IR(51057, 5)
  "Cosh\0" // IR(51062, 5)
  "Tanh\0" // IR(51067, 5)
  "Asinh\0" // IR(51072, 6)
  "Acosh\0" // IR(51078, 6)
  "Atanh\0" // IR(51084, 6)
  "Atan2\0" // IR(51090, 6)
  "Pow\0" // IR(51096, 4)
  "Exp\0" // IR(51100, 4)
  "Log\0" // IR(51104, 4)
  "Exp2\0" // IR(51108, 5)
  "Log2\0" // IR(51113, 5)
  "Sqrt\0" // IR(51118, 5)
  "InverseSqrt\0" // IR(51123, 12)
  "Determinant\0" // IR(51135, 12)
  "MatrixInverse\0" // IR(51147, 14)
  "Modf\0" // IR(51161, 5)
  "ModfStruct\0" // IR(51166, 11)
  "FMin\0" // IR(51177, 5)
  "UMin\0" // IR(51182, 5)
  "SMin\0" // IR(51187, 5)
  "FMax\0" // IR(51192, 5)
  "UMax\0" // IR(51197, 5)
  "SMax\0" // IR(51202, 5)
  "FClamp\0" // IR(51207, 7)
  "UClamp\0" // IR(51214, 7)
  "SClamp\0" // IR(51221, 7)
  "FMix\0" // IR(51228, 5)
  "IMix\0" // IR(51233, 5)
  "Step\0" // IR(51238, 5)
  "SmoothStep\0" // IR(51243, 11)
  "Fma\0" // IR(51254, 4)
  "Frexp\0" // IR(51258, 6)
  "FrexpStruct\0" // IR(51264, 12)
  "Ldexp\0" // IR(51276, 6)
  "PackSnorm4x8\0" // IR(51282, 13)
  "PackUnorm4x8\0" // IR(51295, 13)
  "PackSnorm2x16\0" // IR(51308, 14)
  "PackUnorm2x16\0" // IR(51322, 14)
  "PackHalf2x16\0" // IR(51336, 13)
  "PackDouble2x32\0" // IR(51349, 15)
  "UnpackSnorm2x16\0" // IR(51364, 16)
  "UnpackUnorm2x16\0" // IR(51380, 16)
  "UnpackHalf2x16\0" // IR(51396, 15)
  "UnpackSnorm4x8\0" // IR(51411, 15)
  "UnpackUnorm4x8\0" // IR(51426, 15)
  "UnpackDouble2x32\0" // IR(51441, 17)
  "Length\0" // IR(51458, 7)
  "Distance\0" // IR(51465, 9)
  "Cross\0" // IR(51474, 6)
  "Normalize\0" // IR(51480, 10)
  "FaceForward\0" // IR(51490, 12)
  "Reflect\0" // IR(51502, 8)
  "Refract\0" // IR(51510, 8)
  "FindILsb\0" // IR(51518, 9)
  "FindSMsb\0" // IR(51527, 9)
  "FindUMsb\0" // IR(51536, 9)
  "InterpolateAtCentroid\0" // IR(51545, 22)
  "InterpolateAtSample\0" // IR(51567, 20)
  "InterpolateAtOffset\0" // IR(51587, 20)
  "NMin\0" // IR(51607, 5)
  "NMax\0" // IR(51612, 5)
  "NClamp\0" // IR(51617, 7)
  "ArgumentInfo\0" // IR(51624, 13)
  "ArgumentStorageBuffer\0" // IR(51637, 22)
  "ArgumentUniform\0" // IR(51659, 16)
  "ArgumentPodStorageBuffer\0" // IR(51675, 25)
  "ArgumentPodUniform\0" // IR(51700, 19)
  "ArgumentPodPushConstant\0" // IR(51719, 24)
  "ArgumentSampledImage\0" // IR(51743, 21)
  "ArgumentStorageImage\0" // IR(51764, 21)
  "ArgumentSampler\0" // IR(51785, 16)
  "ArgumentWorkgroup\0" // IR(51801, 18)
  "SpecConstantWorkgroupSize\0" // IR(51819, 26)
  "SpecConstantGlobalOffset\0" // IR(51845, 25)
  "SpecConstantWorkDim\0" // IR(51870, 20)
  "PushConstantGlobalOffset\0" // IR(51890, 25)
  "PushConstantEnqueuedLocalSize\0" // IR(51915, 30)
  "PushConstantGlobalSize\0" // IR(51945, 23)
  "PushConstantRegionOffset\0" // IR(51968, 25)
  "PushConstantNumWorkgroups\0" // IR(51993, 26)
  "PushConstantRegionGroupOffset\0" // IR(52019, 30)
  "ConstantDataStorageBuffer\0" // IR(52049, 26)
  "ConstantDataUniform\0" // IR(52075, 20)
  "PropertyRequiredWorkgroupSize\0" // IR(52095, 30)
  "SpecConstantSubgroupMaxSize\0" // IR(52125, 28)
  "ArgumentPointerPushConstant\0" // IR(52153, 28)
  "ArgumentPointerUniform\0" // IR(52181, 23)
  "ProgramScopeVariablesStorageBuffer\0" // IR(52204, 35)
  "ProgramScopeVariablePointerRelocation\0" // IR(52239, 38)
  "ImageArgumentInfoChannelOrderPushConstant\0" // IR(52277, 42)
  "ImageArgumentInfoChannelDataTypePushConstant\0" // IR(52319, 45)
  "ImageArgumentInfoChannelOrderUniform\0" // IR(52364, 37)
  "ImageArgumentInfoChannelDataTypeUniform\0" // IR(52401, 40)
  "ArgumentStorageTexelBuffer\0" // IR(52441, 27)
  "ArgumentUniformTexelBuffer\0" // IR(52468, 27)
  "ConstantDataPointerPushConstant\0" // IR(52495, 32)
  "ProgramScopeVariablePointerPushConstant\0" // IR(52527, 40)
  "PrintfInfo\0" // IR(52567, 11)
  "PrintfBufferStorageBuffer\0" // IR(52578, 26)
  "PrintfBufferPointerPushConstant\0" // IR(52604, 32)
  "NormalizedSamplerMaskPushConstant\0" // IR(52636, 34)
  "WorkgroupVariableSize\0" // IR(52670, 22)
  "DebugImportedEntity\0" // IR(52692, 20)
  "DebugSource\0" // IR(52712, 12)
  "DebugFunctionDefinition\0" // IR(52724, 24)
  "DebugSourceContinued\0" // IR(52748, 21)
  "DebugLine\0" // IR(52769, 10)
  "DebugNoLine\0" // IR(52779, 12)
  "DebugBuildIdentifier\0" // IR(52791, 21)
  "DebugStoragePath\0" // IR(52812, 17)
  "DebugEntryPoint\0" // IR(52829, 16)
  "DebugTypeMatrix\0" // IR(52845, 16)
  "Configuration\0" // IR(52861, 14)
  "StartCounter\0" // IR(52875, 13)
  "StopCounter\0" // IR(52888, 12)
  "PushConstants\0" // IR(52900, 14)
  "SpecializationMapEntry\0" // IR(52914, 23)
  "DescriptorSetBuffer\0" // IR(52937, 20)
  "DescriptorSetImage\0" // IR(52957, 19)
  "DescriptorSetSampler\0" // IR(52976, 21)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING\0" // IR(52997, 63)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS\0" // IR(53060, 45)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER\0" // IR(53105, 49)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE\0" // IR(53154, 49)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION\0" // IR(53203, 44)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY\0" // IR(53247, 50)
  "DebugModuleINTEL\0" // IR(53297, 17)
  "acos\0" // IR(53314, 5)
  "acosh\0" // IR(53319, 6)
  "acospi\0" // IR(53325, 7)
  "asin\0" // IR(53332, 5)
  "asinh\0" // IR(53337, 6)
  "asinpi\0" // IR(53343, 7)
  "atan\0" // IR(53350, 5)
  "atan2\0" // IR(53355, 6)
  "atanh\0" // IR(53361, 6)
  "atanpi\0" // IR(53367, 7)
  "atan2pi\0" // IR(53374, 8)
  "cbrt\0" // IR(53382, 5)
  "ceil\0" // IR(53387, 5)
  "copysign\0" // IR(53392, 9)
  "cos\0" // IR(53401, 4)
  "cosh\0" // IR(53405, 5)
  "cospi\0" // IR(53410, 6)
  "erfc\0" // IR(53416, 5)
  "erf\0" // IR(53421, 4)
  "exp\0" // IR(53425, 4)
  "exp2\0" // IR(53429, 5)
  "exp10\0" // IR(53434, 6)
  "expm1\0" // IR(53440, 6)
  "fabs\0" // IR(53446, 5)
  "fdim\0" // IR(53451, 5)
  "floor\0" // IR(53456, 6)
  "fma\0" // IR(53462, 4)
  "fmax\0" // IR(53466, 5)
  "fmin\0" // IR(53471, 5)
  "fmod\0" // IR(53476, 5)
  "fract\0" // IR(53481, 6)
  "frexp\0" // IR(53487, 6)
  "hypot\0" // IR(53493, 6)
  "ilogb\0" // IR(53499, 6)
  "ldexp\0" // IR(53505, 6)
  "lgamma\0" // IR(53511, 7)
  "lgamma_r\0" // IR(53518, 9)
  "log\0" // IR(53527, 4)
  "log2\0" // IR(53531, 5)
  "log10\0" // IR(53536, 6)
  "log1p\0" // IR(53542, 6)
  "logb\0" // IR(53548, 5)
  "mad\0" // IR(53553, 4)
  "maxmag\0" // IR(53557, 7)
  "minmag\0" // IR(53564, 7)
  "modf\0" // IR(53571, 5)
  "nan\0" // IR(53576, 4)
  "nextafter\0" // IR(53580, 10)
  "pow\0" // IR(53590, 4)
  "pown\0" // IR(53594, 5)
  "powr\0" // IR(53599, 5)
  "remainder\0" // IR(53604, 10)
  "remquo\0" // IR(53614, 7)
  "rint\0" // IR(53621, 5)
  "rootn\0" // IR(53626, 6)
  "round\0" // IR(53632, 6)
  "rsqrt\0" // IR(53638, 6)
  "sin\0" // IR(53644, 4)
  "sincos\0" // IR(53648, 7)
  "sinh\0" // IR(53655, 5)
  "sinpi\0" // IR(53660, 6)
  "sqrt\0" // IR(53666, 5)
  "tan\0" // IR(53671, 4)
  "tanh\0" // IR(53675, 5)
  "tanpi\0" // IR(53680, 6)
  "tgamma\0" // IR(53686, 7)
  "trunc\0" // IR(53693, 6)
  "half_cos\0" // IR(53699, 9)
  "half_divide\0" // IR(53708, 12)
  "half_exp\0" // IR(53720, 9)
  "half_exp2\0" // IR(53729, 10)
  "half_exp10\0" // IR(53739, 11)
  "half_log\0" // IR(53750, 9)
  "half_log2\0" // IR(53759, 10)
  "half_log10\0" // IR(53769, 11)
  "half_powr\0" // IR(53780, 10)
  "half_recip\0" // IR(53790, 11)
  "half_rsqrt\0" // IR(53801, 11)
  "half_sin\0" // IR(53812, 9)
  "half_sqrt\0" // IR(53821, 10)
  "half_tan\0" // IR(53831, 9)
  "native_cos\0" // IR(53840, 11)
  "native_divide\0" // IR(53851, 14)
  "native_exp\0" // IR(53865, 11)
  "native_exp2\0" // IR(53876, 12)
  "native_exp10\0" // IR(53888, 13)
  "native_log\0" // IR(53901, 11)
  "native_log2\0" // IR(53912, 12)
  "native_log10\0" // IR(53924, 13)
  "native_powr\0" // IR(53937, 12)
  "native_recip\0" // IR(53949, 13)
  "native_rsqrt\0" // IR(53962, 13)
  "native_sin\0" // IR(53975, 11)
  "native_sqrt\0" // IR(53986, 12)
  "native_tan\0" // IR(53998, 11)
  "fclamp\0" // IR(54009, 7)
  "degrees\0" // IR(54016, 8)
  "fmax_common\0" // IR(54024, 12)
  "fmin_common\0" // IR(54036, 12)
  "mix\0" // IR(54048, 4)
  "radians\0" // IR(54052, 8)
  "step\0" // IR(54060, 5)
  "smoothstep\0" // IR(54065, 11)
  "sign\0" // IR(54076, 5)
  "cross\0" // IR(54081, 6)
  "distance\0" // IR(54087, 9)
  "length\0" // IR(54096, 7)
  "normalize\0" // IR(54103, 10)
  "fast_distance\0" // IR(54113, 14)
  "fast_length\0" // IR(54127, 12)
  "fast_normalize\0" // IR(54139, 15)
  "s_abs\0" // IR(54154, 6)
  "s_abs_diff\0" // IR(54160, 11)
  "s_add_sat\0" // IR(54171, 10)
  "u_add_sat\0" // IR(54181, 10)
  "s_hadd\0" // IR(54191, 7)
  "u_hadd\0" // IR(54198, 7)
  "s_rhadd\0" // IR(54205, 8)
  "u_rhadd\0" // IR(54213, 8)
  "s_clamp\0" // IR(54221, 8)
  "u_clamp\0" // IR(54229, 8)
  "clz\0" // IR(54237, 4)
  "ctz\0" // IR(54241, 4)
  "s_mad_hi\0" // IR(54245, 9)
  "u_mad_sat\0" // IR(54254, 10)
  "s_mad_sat\0" // IR(54264, 10)
  "s_max\0" // IR(54274, 6)
  "u_max\0" // IR(54280, 6)
  "s_min\0" // IR(54286, 6)
  "u_min\0" // IR(54292, 6)
  "s_mul_hi\0" // IR(54298, 9)
  "rotate\0" // IR(54307, 7)
  "s_sub_sat\0" // IR(54314, 10)
  "u_sub_sat\0" // IR(54324, 10)
  "u_upsample\0" // IR(54334, 11)
  "s_upsample\0" // IR(54345, 11)
  "popcount\0" // IR(54356, 9)
  "s_mad24\0" // IR(54365, 8)
  "u_mad24\0" // IR(54373, 8)
  "s_mul24\0" // IR(54381, 8)
  "u_mul24\0" // IR(54389, 8)
  "vloadn\0" // IR(54397, 7)
  "vstoren\0" // IR(54404, 8)
  "vload_half\0" // IR(54412, 11)
  "vload_halfn\0" // IR(54423, 12)
  "vstore_half\0" // IR(54435, 12)
  "vstore_half_r\0" // IR(54447, 14)
  "vstore_halfn\0" // IR(54461, 13)
  "vstore_halfn_r\0" // IR(54474, 15)
  "vloada_halfn\0" // IR(54489, 13)
  "vstorea_halfn\0" // IR(54502, 14)
  "vstorea_halfn_r\0" // IR(54516, 16)
  "shuffle\0" // IR(54532, 8)
  "shuffle2\0" // IR(54540, 9)
  "printf\0" // IR(54549, 7)
  "prefetch\0" // IR(54556, 9)
  "bitselect\0" // IR(54565, 10)
  "select\0" // IR(54575, 7)
  "u_abs\0" // IR(54582, 6)
  "u_abs_diff\0" // IR(54588, 11)
  "u_mul_hi\0" // IR(54599, 9)
  "u_mad_hi\0" // IR(54608, 9)
  "CubeFaceIndexAMD\0" // IR(54617, 17)
  "CubeFaceCoordAMD\0" // IR(54634, 17)
  "TimeAMD\0" // IR(54651, 8)
  "SwizzleInvocationsAMD\0" // IR(54659, 22)
  "SwizzleInvocationsMaskedAMD\0" // IR(54681, 28)
  "WriteInvocationAMD\0" // IR(54709, 19)
  "MbcntAMD\0" // IR(54728, 9)
  "InterpolateAtVertexAMD\0" // IR(54737, 23)
  "FMin3AMD\0" // IR(54760, 9)
  "UMin3AMD\0" // IR(54769, 9)
  "SMin3AMD\0" // IR(54778, 9)
  "FMax3AMD\0" // IR(54787, 9)
  "UMax3AMD\0" // IR(54796, 9)
  "SMax3AMD\0" // IR(54805, 9)
  "FMid3AMD\0" // IR(54814, 9)
  "UMid3AMD\0" // IR(54823, 9)
  "SMid3AMD\0" // IR(54832, 9)
;

// Array of IndexRanges, where each represents a string by referencing
// the kStrings table.
// This array contains all sequences of alias strings used in the grammar.
// This table is referenced by an IndexRange elsewhere, i.e. by the 'aliases'
// field of an instruction or operand description.
static const IndexRange kAliasSpans[] = {
  IR(5468, 27), // 0 PhysicalStorageBuffer64EXT
  IR(6379, 18), // 1 SubgroupEqMaskKHR
  IR(6434, 18), // 2 SubgroupGeMaskKHR
  IR(6467, 18), // 3 SubgroupGtMaskKHR
  IR(6500, 18), // 4 SubgroupLeMaskKHR
  IR(6533, 18), // 5 SubgroupLtMaskKHR
  IR(7391, 12), // 6 BaryCoordNV
  IR(7446, 19), // 7 BaryCoordNoPerspNV
  IR(7477, 15), // 8 FragmentSizeNV
  IR(7534, 22), // 9 InvocationsPerPixelNV
  IR(7662, 11), // 10 LaunchIdNV
  IR(7687, 13), // 11 LaunchSizeNV
  IR(7718, 17), // 12 WorldRayOriginNV
  IR(7756, 20), // 13 WorldRayDirectionNV
  IR(7795, 18), // 14 ObjectRayOriginNV
  IR(7835, 21), // 15 ObjectRayDirectionNV
  IR(7867, 10), // 16 RayTminNV
  IR(7888, 10), // 17 RayTmaxNV
  IR(7921, 22), // 18 InstanceCustomIndexNV
  IR(7960, 16), // 19 ObjectToWorldNV
  IR(7993, 16), // 20 WorldToObjectNV
  IR(8027, 10), // 21 HitKindNV
  IR(8258, 19), // 22 IncomingRayFlagsNV
  IR(10034, 28), // 23 StorageUniformBufferBlock16
  IR(10097, 17), // 24 StorageUniform16
  IR(10912, 27), // 25 ShaderViewportIndexLayerNV
  IR(10956, 22), // 26 FragmentBarycentricNV
  IR(11009, 30), // 27 ComputeDerivativeGroupQuadsNV
  IR(11039, 14), // 28 ShadingRateNV
  IR(11099, 20), // 29 ShaderNonUniformEXT
  IR(11142, 26), // 30 RuntimeDescriptorArrayEXT
  IR(11204, 39), // 31 InputAttachmentArrayDynamicIndexingEXT
  IR(11282, 42), // 32 UniformTexelBufferArrayDynamicIndexingEXT
  IR(11363, 42), // 33 StorageTexelBufferArrayDynamicIndexingEXT
  IR(11442, 40), // 34 UniformBufferArrayNonUniformIndexingEXT
  IR(11518, 39), // 35 SampledImageArrayNonUniformIndexingEXT
  IR(11594, 40), // 36 StorageBufferArrayNonUniformIndexingEXT
  IR(11670, 39), // 37 StorageImageArrayNonUniformIndexingEXT
  IR(11748, 42), // 38 InputAttachmentArrayNonUniformIndexingEXT
  IR(11832, 45), // 39 UniformTexelBufferArrayNonUniformIndexingEXT
  IR(11919, 45), // 40 StorageTexelBufferArrayNonUniformIndexingEXT
  IR(11982, 21), // 41 VulkanMemoryModelKHR
  IR(12032, 32), // 42 VulkanMemoryModelDeviceScopeKHR
  IR(12064, 34), // 43 PhysicalStorageBufferAddressesEXT
  IR(12130, 31), // 44 ComputeDerivativeGroupLinearNV
  IR(12334, 28), // 45 DemoteToHelperInvocationEXT
  IR(13355, 26), // 46 FPGAMemoryAttributesINTEL
  IR(13434, 32), // 47 ArbitraryPrecisionIntegersINTEL
  IR(13504, 37), // 48 ArbitraryPrecisionFloatingPointINTEL
  IR(13594, 22), // 49 FPGALoopControlsINTEL
  IR(13689, 24), // 50 FPGAMemoryAccessesINTEL
  IR(13741, 27), // 51 FPGAClusterAttributesINTEL
  IR(13783, 14), // 52 LoopFuseINTEL
  IR(13818, 20), // 53 FPGADSPControlINTEL
  IR(13905, 40), // 54 FPGAInvocationPipeliningAttributesINTEL
  IR(13970, 24), // 55 FPGABufferLocationINTEL
  IR(14029, 34), // 56 ArbitraryPrecisionFixedPointINTEL
  IR(14087, 23), // 57 USMStorageClassesINTEL
  IR(14140, 29), // 58 RuntimeAlignedAttributeINTEL
  IR(14183, 13), // 59 IOPipesINTEL
  IR(14216, 19), // 60 BlockingPipesINTEL
  IR(14249, 13), // 61 FPGARegINTEL
  IR(14281, 22), // 62 DotProductInputAllKHR
  IR(14325, 25), // 63 DotProductInput4x8BitKHR
  IR(14378, 31), // 64 DotProductInput4x8BitPackedKHR
  IR(14420, 14), // 65 DotProductKHR
  IR(14592, 13), // 66 OptNoneINTEL
  IR(14737, 29), // 67 FPGAClusterAttributesV2INTEL
  IR(14813, 18), // 68 TaskSequenceINTEL
  IR(14872, 24), // 69 FPGALatencyControlINTEL
  IR(14925, 28), // 70 FPGAArgumentInterfacesINTEL
  IR(15019, 35), // 71 GlobalVariableFPGADecorationsINTEL
  IR(17802, 15), // 72 PerPrimitiveNV
  IR(17850, 12), // 73 PerVertexNV
  IR(17873, 14), // 74 NonUniformEXT
  IR(17903, 19), // 75 RestrictPointerEXT
  IR(17937, 18), // 76 AliasedPointerEXT
  IR(18278, 24), // 77 HlslCounterBufferGOOGLE
  IR(18315, 19), // 78 HlslSemanticGOOGLE
  IR(18445, 14), // 79 RegisterINTEL
  IR(18472, 12), // 80 MemoryINTEL
  IR(18499, 14), // 81 NumbanksINTEL
  IR(18529, 15), // 82 BankwidthINTEL
  IR(18567, 22), // 83 MaxPrivateCopiesINTEL
  IR(18606, 16), // 84 SinglepumpINTEL
  IR(18639, 16), // 85 DoublepumpINTEL
  IR(18675, 19), // 86 MaxReplicatesINTEL
  IR(18715, 20), // 87 SimpleDualPortINTEL
  IR(18747, 11), // 88 MergeINTEL
  IR(18815, 14), // 89 BankBitsINTEL
  IR(18850, 20), // 90 ForcePow2DepthINTEL
  IR(18887, 16), // 91 StridesizeINTEL
  IR(18918, 14), // 92 WordsizeINTEL
  IR(18951, 18), // 93 TrueDualPortINTEL
  IR(18989, 19), // 94 BurstCoalesceINTEL
  IR(19024, 15), // 95 CacheSizeINTEL
  IR(19068, 28), // 96 DontStaticallyCoalesceINTEL
  IR(19111, 14), // 97 PrefetchINTEL
  IR(19143, 17), // 98 StallEnableINTEL
  IR(19186, 25), // 99 FuseLoopsInFunctionINTEL
  IR(19231, 19), // 100 MathOpDSPModeINTEL
  IR(19304, 24), // 101 InitiationIntervalINTEL
  IR(19349, 20), // 102 MaxConcurrencyINTEL
  IR(19390, 20), // 103 PipelineEnableINTEL
  IR(19431, 20), // 104 BufferLocationINTEL
  IR(19471, 19), // 105 IOPipeStorageINTEL
  IR(19649, 15), // 106 StallFreeINTEL
  IR(19747, 25), // 107 LatencyControlLabelINTEL
  IR(19803, 30), // 108 LatencyControlConstraintINTEL
  IR(19861, 27), // 109 ConduitKernelArgumentINTEL
  IR(19920, 31), // 110 RegisterMapKernelArgumentINTEL
  IR(19985, 33), // 111 MMHostInterfaceAddressWidthINTEL
  IR(20049, 30), // 112 MMHostInterfaceDataWidthINTEL
  IR(20108, 28), // 113 MMHostInterfaceLatencyINTEL
  IR(20205, 34), // 114 MMHostInterfaceReadWriteModeINTEL
  IR(20269, 29), // 115 MMHostInterfaceMaxBurstINTEL
  IR(20331, 32), // 116 MMHostInterfaceWaitRequestINTEL
  IR(20390, 26), // 117 StableKernelArgumentINTEL
  IR(20533, 14), // 118 InitModeINTEL
  IR(20576, 28), // 119 ImplementInRegisterMapINTEL
  IR(21910, 14), // 120 OutputLinesNV
  IR(21944, 19), // 121 OutputPrimitivesNV
  IR(21987, 23), // 122 DerivativeGroupQuadsNV
  IR(22035, 24), // 123 DerivativeGroupLinearNV
  IR(22078, 18), // 124 OutputTrianglesNV
  IR(22826, 16), // 125 RayGenerationNV
  IR(22858, 15), // 126 IntersectionNV
  IR(22883, 9), // 127 AnyHitNV
  IR(22906, 13), // 128 ClosestHitNV
  IR(22927, 7), // 129 MissNV
  IR(22946, 11), // 130 CallableNV
  IR(23091, 23), // 131 AllowContractFastINTEL
  IR(23127, 18), // 132 AllowReassocINTEL
  IR(23353, 20), // 133 RuntimeAlignedINTEL
  IR(23602, 22), // 134 MakeTexelAvailableKHR
  IR(23641, 20), // 135 MakeTexelVisibleKHR
  IR(23677, 19), // 136 NonPrivateTexelKHR
  IR(23710, 17), // 137 VolatileTexelKHR
  IR(24269, 27), // 138 InitOnDeviceReprogramINTEL
  IR(24320, 23), // 139 InitOnDeviceResetINTEL
  IR(24654, 21), // 140 DependencyArrayINTEL
  IR(24694, 18), // 141 LoopCoalesceINTEL
  IR(24734, 21), // 142 MaxInterleavingINTEL
  IR(24782, 26), // 143 SpeculatedIterationsINTEL
  IR(24823, 14), // 144 NoFusionINTEL
  IR(24853, 15), // 145 LoopCountINTEL
  IR(24895, 26), // 146 MaxReinvocationDelayINTEL
  IR(25287, 24), // 147 MakePointerAvailableKHR
  IR(25330, 22), // 148 MakePointerVisibleKHR
  IR(25370, 21), // 149 NonPrivatePointerKHR
  IR(25457, 10), // 150 VulkanKHR
  IR(15574, 5), // 151 None
  IR(25640, 16), // 152 OutputMemoryKHR
  IR(25670, 17), // 153 MakeAvailableKHR
  IR(25699, 15), // 154 MakeVisibleKHR
  IR(25775, 28), // 155 PackedVectorFormat4x8BitKHR
  IR(26090, 24), // 156 SkipBuiltinPrimitivesNV
  IR(26830, 15), // 157 QueueFamilyKHR
  IR(27201, 15), // 158 CallableDataNV
  IR(27240, 23), // 159 IncomingCallableDataNV
  IR(27277, 13), // 160 RayPayloadNV
  IR(27306, 15), // 161 HitAttributeNV
  IR(27343, 21), // 162 IncomingRayPayloadNV
  IR(27386, 21), // 163 ShaderRecordBufferNV
  IR(27429, 25), // 164 PhysicalStorageBufferEXT
  IR(27555, 16), // 165 DeviceOnlyINTEL
  IR(27586, 14), // 166 HostOnlyINTEL
  IR(34824, 8), // 167 SDotKHR
  IR(34837, 8), // 168 UDotKHR
  IR(34851, 9), // 169 SUDotKHR
  IR(34871, 14), // 170 SDotAccSatKHR
  IR(34896, 14), // 171 UDotAccSatKHR
  IR(34922, 15), // 172 SUDotAccSatKHR
  IR(37094, 16), // 173 TypeVectorIdEXT
  IR(38396, 21), // 174 ReportIntersectionNV
  IR(38571, 28), // 175 TypeAccelerationStructureNV
  IR(38652, 23), // 176 RayQueryGetClusterIdNV
  IR(40820, 21), // 177 DecorateStringGOOGLE
  IR(40862, 27), // 178 MemberDecorateStringGOOGLE
  IR(46119, 28), // 179 ArbitraryFloatSinCosPiINTEL
  IR(46172, 24), // 180 ArbitraryFloatCastINTEL
  IR(46228, 31), // 181 ArbitraryFloatCastFromIntINTEL
  IR(46289, 29), // 182 ArbitraryFloatCastToIntINTEL
  IR(46342, 23), // 183 ArbitraryFloatAddINTEL
  IR(46389, 23), // 184 ArbitraryFloatSubINTEL
  IR(46436, 23), // 185 ArbitraryFloatMulINTEL
  IR(46483, 23), // 186 ArbitraryFloatDivINTEL
  IR(46529, 22), // 187 ArbitraryFloatGTINTEL
  IR(46574, 22), // 188 ArbitraryFloatGEINTEL
  IR(46619, 22), // 189 ArbitraryFloatLTINTEL
  IR(46664, 22), // 190 ArbitraryFloatLEINTEL
  IR(46709, 22), // 191 ArbitraryFloatEQINTEL
  IR(46757, 25), // 192 ArbitraryFloatRecipINTEL
  IR(46808, 25), // 193 ArbitraryFloatRSqrtINTEL
  IR(46858, 24), // 194 ArbitraryFloatCbrtINTEL
  IR(46908, 25), // 195 ArbitraryFloatHypotINTEL
  IR(46958, 24), // 196 ArbitraryFloatSqrtINTEL
  IR(47642, 15), // 197 FixedSqrtINTEL
  IR(47674, 16), // 198 FixedRecipINTEL
  IR(47707, 16), // 199 FixedRsqrtINTEL
  IR(47738, 14), // 200 FixedSinINTEL
  IR(47767, 14), // 201 FixedCosINTEL
  IR(47799, 17), // 202 FixedSinCosINTEL
  IR(47833, 16), // 203 FixedSinPiINTEL
  IR(47866, 16), // 204 FixedCosPiINTEL
  IR(47902, 19), // 205 FixedSinCosPiINTEL
  IR(47936, 14), // 206 FixedLogINTEL
  IR(47965, 14), // 207 FixedExpINTEL
  IR(48009, 29), // 208 PtrCastToCrossWorkgroupINTEL
  IR(48068, 29), // 209 CrossWorkgroupCastToPtrINTEL
  IR(48120, 22), // 210 ReadPipeBlockingINTEL
  IR(48166, 23), // 211 WritePipeBlockingINTEL
  IR(49118, 24), // 212 TaskSequenceCreateINTEL
  IR(49166, 23), // 213 TaskSequenceAsyncINTEL
  IR(49211, 21), // 214 TaskSequenceGetINTEL
  IR(49258, 25), // 215 TaskSequenceReleaseINTEL
  IR(49306, 22), // 216 TypeTaskSequenceINTEL
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
  spv::Capability::Float8EXT, // 77
  spv::Capability::CooperativeMatrixKHR, // 78
  spv::Capability::WorkgroupMemoryExplicitLayoutKHR, // 79
  spv::Capability::StorageBuffer16BitAccess, // 80
  spv::Capability::VariablePointersStorageBuffer, // 81
  spv::Capability::AtomicStorage, // 82
  spv::Capability::StorageBuffer8BitAccess, // 83
  spv::Capability::RayQueryKHR, // 84
  spv::Capability::RayTracingKHR, // 85
  spv::Capability::CooperativeMatrixKHR, // 86
  spv::Capability::Int4TypeINTEL, // 87
  spv::Capability::CooperativeMatrixKHR, // 88
  spv::Capability::BFloat16TypeKHR, // 89
  spv::Capability::BFloat16TypeKHR, // 90
  spv::Capability::CooperativeMatrixKHR, // 91
  spv::Capability::MultiViewport, // 92
  spv::Capability::ShaderViewportIndexLayerEXT, // 93
  spv::Capability::ShaderViewportMaskNV, // 94
  spv::Capability::InputAttachment, // 95
  spv::Capability::ImageBuffer, // 96
  spv::Capability::ShaderNonUniform, // 97
  spv::Capability::InputAttachment, // 98
  spv::Capability::ShaderNonUniform, // 99
  spv::Capability::SampledBuffer, // 100
  spv::Capability::ShaderNonUniform, // 101
  spv::Capability::ImageBuffer, // 102
  spv::Capability::ShaderNonUniform, // 103
  spv::Capability::VectorAnyINTEL, // 104
  spv::Capability::Int8, // 105
  spv::Capability::FPGAClusterAttributesALTERA, // 106
  spv::Capability::FPGAKernelAttributesINTEL, // 107
  spv::Capability::Subgroup2DBlockIOINTEL, // 108
  spv::Capability::VariableLengthArrayINTEL, // 109
  spv::Capability::UntypedPointersKHR, // 110
  spv::Capability::SpecConditionalINTEL, // 111
  spv::Capability::CooperativeMatrixLayoutsARM, // 112
  spv::Capability::Shader, // 113
  spv::Capability::Kernel, // 114
  spv::Capability::Shader, // 115
  spv::Capability::UniformDecoration, // 116
  spv::Capability::GeometryStreams, // 117
  spv::Capability::TransformFeedback, // 118
  spv::Capability::Kernel, // 119
  spv::Capability::FloatControls2, // 120
  spv::Capability::Linkage, // 121
  spv::Capability::Float8EXT, // 122
  spv::Capability::SampleMaskOverrideCoverageNV, // 123
  spv::Capability::GeometryShaderPassthroughNV, // 124
  spv::Capability::MeshShadingNV, // 125
  spv::Capability::MeshShadingEXT, // 126
  spv::Capability::ShaderInvocationReorderNV, // 127
  spv::Capability::ShaderInvocationReorderEXT, // 128
  spv::Capability::BindlessTextureNV, // 129
  spv::Capability::VectorComputeINTEL, // 130
  spv::Capability::IndirectReferencesINTEL, // 131
  spv::Capability::AsmINTEL, // 132
  spv::Capability::FunctionFloatControlINTEL, // 133
  spv::Capability::FPGAMemoryAttributesALTERA, // 134
  spv::Capability::FPGAMemoryAccessesALTERA, // 135
  spv::Capability::LoopFuseALTERA, // 136
  spv::Capability::FPGADSPControlALTERA, // 137
  spv::Capability::MemoryAccessAliasingINTEL, // 138
  spv::Capability::FPGAInvocationPipeliningAttributesALTERA, // 139
  spv::Capability::FPGABufferLocationALTERA, // 140
  spv::Capability::IOPipesALTERA, // 141
  spv::Capability::FPGAClusterAttributesV2ALTERA, // 142
  spv::Capability::FPMaxErrorINTEL, // 143
  spv::Capability::FPGALatencyControlALTERA, // 144
  spv::Capability::FPGAArgumentInterfacesALTERA, // 145
  spv::Capability::GlobalVariableHostAccessINTEL, // 146
  spv::Capability::GlobalVariableFPGADecorationsALTERA, // 147
  spv::Capability::CacheControlsINTEL, // 148
  spv::Capability::TileImageColorReadAccessEXT, // 149
  spv::Capability::Geometry, // 150
  spv::Capability::Tessellation, // 151
  spv::Capability::MeshShadingNV, // 152
  spv::Capability::MeshShadingEXT, // 153
  spv::Capability::Geometry, // 154
  spv::Capability::MeshShadingNV, // 155
  spv::Capability::MeshShadingEXT, // 156
  spv::Capability::SubgroupDispatch, // 157
  spv::Capability::TileImageDepthReadAccessEXT, // 158
  spv::Capability::TileImageStencilReadAccessEXT, // 159
  spv::Capability::SampleMaskPostDepthCoverage, // 160
  spv::Capability::DenormPreserve, // 161
  spv::Capability::DenormFlushToZero, // 162
  spv::Capability::SignedZeroInfNanPreserve, // 163
  spv::Capability::RoundingModeRTE, // 164
  spv::Capability::RoundingModeRTZ, // 165
  spv::Capability::QuadControlKHR, // 166
  spv::Capability::ComputeDerivativeGroupQuadsKHR, // 167
  spv::Capability::ComputeDerivativeGroupLinearKHR, // 168
  spv::Capability::FragmentShaderPixelInterlockEXT, // 169
  spv::Capability::FragmentShaderSampleInterlockEXT, // 170
  spv::Capability::FragmentShaderShadingRateInterlockEXT, // 171
  spv::Capability::Shader64BitIndexingEXT, // 172
  spv::Capability::RoundToInfinityINTEL, // 173
  spv::Capability::KernelAttributesINTEL, // 174
  spv::Capability::FloatControls2, // 175
  spv::Capability::FPGAKernelAttributesv2INTEL, // 176
  spv::Capability::RegisterLimitsINTEL, // 177
  spv::Capability::FloatControls2, // 178
  spv::Capability::FPFastMathModeINTEL, // 179
  spv::Capability::OptNoneEXT, // 180
  spv::Capability::RuntimeAlignedAttributeALTERA, // 181
  spv::Capability::Kernel, // 182
  spv::Capability::GroupNonUniformArithmetic, // 183
  spv::Capability::GroupNonUniformBallot, // 184
  spv::Capability::GroupNonUniformClustered, // 185
  spv::Capability::GroupNonUniformPartitionedNV, // 186
  spv::Capability::ImageGatherExtended, // 187
  spv::Capability::MinLod, // 188
  spv::Capability::VulkanMemoryModel, // 189
  spv::Capability::FPGALoopControlsALTERA, // 190
  spv::Capability::ArbitraryPrecisionFixedPointALTERA, // 191
  spv::Capability::RawAccessChainsNV, // 192
  spv::Capability::RayTraversalPrimitiveCullingKHR, // 193
  spv::Capability::RayTracingOpacityMicromapEXT, // 194
  spv::Capability::RayQueryKHR, // 195
  spv::Capability::StorageImageExtendedFormats, // 196
  spv::Capability::Int64ImageEXT, // 197
  spv::Capability::Shader, // 198
  spv::Capability::VectorComputeINTEL, // 199
  spv::Capability::GenericPointer, // 200
  spv::Capability::FunctionPointersINTEL, // 201
  spv::Capability::USMStorageClassesALTERA, // 202
  spv::Capability::CooperativeMatrixTensorAddressingNV, // 203
  spv::Capability::CooperativeMatrixBlockLoadsNV, // 204
  spv::Capability::TensorsARM, // 205
  spv::Capability::Addresses, // 206
  spv::Capability::PhysicalStorageBufferAddresses, // 207
  spv::Capability::LiteralSampler, // 208
  spv::Capability::Addresses, // 209
  spv::Capability::UntypedPointersKHR, // 210
  spv::Capability::Addresses, // 211
  spv::Capability::VariablePointers, // 212
  spv::Capability::VariablePointersStorageBuffer, // 213
  spv::Capability::PhysicalStorageBufferAddresses, // 214
  spv::Capability::Kernel, // 215
  spv::Capability::ImageQuery, // 216
  spv::Capability::ImageQuery, // 217
  spv::Capability::Shader, // 218
  spv::Capability::BitInstructions, // 219
  spv::Capability::DerivativeControl, // 220
  spv::Capability::Groups, // 221
  spv::Capability::SparseResidency, // 222
  spv::Capability::PipeStorage, // 223
  spv::Capability::NamedBarrier, // 224
  spv::Capability::GroupNonUniformVote, // 225
  spv::Capability::GroupNonUniformBallot, // 226
  spv::Capability::GroupNonUniformShuffle, // 227
  spv::Capability::GroupNonUniformShuffleRelative, // 228
  spv::Capability::GroupNonUniformArithmetic, // 229
  spv::Capability::GroupNonUniformClustered, // 230
  spv::Capability::GroupNonUniformPartitionedNV, // 231
  spv::Capability::GroupNonUniformQuad, // 232
  spv::Capability::Addresses, // 233
  spv::Capability::VariablePointers, // 234
  spv::Capability::VariablePointersStorageBuffer, // 235
  spv::Capability::GraphARM, // 236
  spv::Capability::UntypedPointersKHR, // 237
  spv::Capability::SubgroupBallotKHR, // 238
  spv::Capability::FMAKHR, // 239
  spv::Capability::SubgroupVoteKHR, // 240
  spv::Capability::GroupNonUniformRotateKHR, // 241
  spv::Capability::RayTracingKHR, // 242
  spv::Capability::RayQueryKHR, // 243
  spv::Capability::DotProduct, // 244
  spv::Capability::ReplicatedCompositesEXT, // 245
  spv::Capability::TextureSampleWeightedQCOM, // 246
  spv::Capability::TextureBoxFilterQCOM, // 247
  spv::Capability::TextureBlockMatchQCOM, // 248
  spv::Capability::CooperativeMatrixConversionQCOM, // 249
  spv::Capability::TextureBlockMatch2QCOM, // 250
  spv::Capability::FragmentMaskAMD, // 251
  spv::Capability::ShaderClockKHR, // 252
  spv::Capability::ShaderInvocationReorderNV, // 253
  spv::Capability::RayTracingMotionBlurNV, // 254
  spv::Capability::ImageFootprintNV, // 255
  spv::Capability::CooperativeVectorNV, // 256
  spv::Capability::LongVectorEXT, // 257
  spv::Capability::CooperativeVectorNV, // 258
  spv::Capability::CooperativeVectorTrainingNV, // 259
  spv::Capability::CooperativeMatrixConversionsNV, // 260
  spv::Capability::DisplacementMicromapNV, // 261
  spv::Capability::ShaderInvocationReorderEXT, // 262
  spv::Capability::RayTracingMotionBlurNV, // 263
  spv::Capability::RayQueryPositionFetchKHR, // 264
  spv::Capability::RayTracingNV, // 265
  spv::Capability::RayTracingKHR, // 266
  spv::Capability::RayQueryKHR, // 267
  spv::Capability::DisplacementMicromapNV, // 268
  spv::Capability::CooperativeMatrixNV, // 269
  spv::Capability::FragmentShaderSampleInterlockEXT, // 270
  spv::Capability::FragmentShaderPixelInterlockEXT, // 271
  spv::Capability::FragmentShaderShadingRateInterlockEXT, // 272
  spv::Capability::CooperativeMatrixReductionsNV, // 273
  spv::Capability::CooperativeMatrixPerElementOperationsNV, // 274
  spv::Capability::TensorAddressingNV, // 275
  spv::Capability::DemoteToHelperInvocation, // 276
  spv::Capability::SubgroupShuffleINTEL, // 277
  spv::Capability::SubgroupBufferBlockIOINTEL, // 278
  spv::Capability::SubgroupImageBlockIOINTEL, // 279
  spv::Capability::SubgroupImageMediaBlockIOINTEL, // 280
  spv::Capability::IntegerFunctions2INTEL, // 281
  spv::Capability::AtomicFloat16MinMaxEXT, // 282
  spv::Capability::AtomicFloat32MinMaxEXT, // 283
  spv::Capability::AtomicFloat64MinMaxEXT, // 284
  spv::Capability::AtomicFloat16VectorNV, // 285
  spv::Capability::ExpectAssumeKHR, // 286
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 287
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 288
  spv::Capability::SubgroupAvcMotionEstimationIntraINTEL, // 289
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 290
  spv::Capability::SubgroupAvcMotionEstimationChromaINTEL, // 291
  spv::Capability::VariableLengthArrayINTEL, // 292
  spv::Capability::ArbitraryPrecisionFloatingPointALTERA, // 293
  spv::Capability::UnstructuredLoopControlsINTEL, // 294
  spv::Capability::BlockingPipesALTERA, // 295
  spv::Capability::FPGARegALTERA, // 296
  spv::Capability::AtomicFloat16AddEXT, // 297
  spv::Capability::AtomicFloat32AddEXT, // 298
  spv::Capability::AtomicFloat64AddEXT, // 299
  spv::Capability::AtomicFloat16VectorNV, // 300
  spv::Capability::LongCompositesINTEL, // 301
  spv::Capability::BFloat16ConversionINTEL, // 302
  spv::Capability::SplitBarrierINTEL, // 303
  spv::Capability::ArithmeticFenceEXT, // 304
  spv::Capability::TaskSequenceALTERA, // 305
  spv::Capability::SubgroupBufferPrefetchINTEL, // 306
  spv::Capability::Subgroup2DBlockTransformINTEL, // 307
  spv::Capability::Subgroup2DBlockTransposeINTEL, // 308
  spv::Capability::SubgroupMatrixMultiplyAccumulateINTEL, // 309
  spv::Capability::TernaryBitwiseFunctionINTEL, // 310
  spv::Capability::UntypedVariableLengthArrayINTEL, // 311
  spv::Capability::FunctionVariantsINTEL, // 312
  spv::Capability::GroupUniformArithmeticKHR, // 313
  spv::Capability::TensorFloat32RoundingINTEL, // 314
  spv::Capability::MaskedGatherScatterINTEL, // 315
  spv::Capability::BindlessImagesINTEL, // 316
  spv::Capability::Float64, // 317
  spv::Capability::InterpolationFunction, // 318
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
  spvtools::Extension::kSPV_NV_sample_mask_override_coverage, // 66
  spvtools::Extension::kSPV_NV_geometry_shader_passthrough, // 67
  spvtools::Extension::kSPV_EXT_shader_viewport_index_layer, // 68
  spvtools::Extension::kSPV_NV_viewport_array2, // 69
  spvtools::Extension::kSPV_NV_viewport_array2, // 70
  spvtools::Extension::kSPV_NVX_multiview_per_view_attributes, // 71
  spvtools::Extension::kSPV_NV_shader_image_footprint, // 72
  spvtools::Extension::kSPV_NV_compute_shader_derivatives, // 73
  spvtools::Extension::kSPV_KHR_compute_shader_derivatives, // 74
  spvtools::Extension::kSPV_NV_shader_subgroup_partitioned, // 75
  spvtools::Extension::kSPV_EXT_descriptor_indexing, // 76
  spvtools::Extension::kSPV_KHR_ray_tracing_position_fetch, // 77
  spvtools::Extension::kSPV_KHR_vulkan_memory_model, // 78
  spvtools::Extension::kSPV_NV_cooperative_matrix, // 79
  spvtools::Extension::kSPV_EXT_fragment_shader_interlock, // 80
  spvtools::Extension::kSPV_EXT_demote_to_helper_invocation, // 81
  spvtools::Extension::kSPV_NV_displacement_micromap, // 82
  spvtools::Extension::kSPV_EXT_opacity_micromap, // 83
  spvtools::Extension::kSPV_NV_shader_invocation_reorder, // 84
  spvtools::Extension::kSPV_EXT_shader_invocation_reorder, // 85
  spvtools::Extension::kSPV_NV_bindless_texture, // 86
  spvtools::Extension::kSPV_NV_cooperative_vector, // 87
  spvtools::Extension::kSPV_NV_shader_atomic_fp16_vector, // 88
  spvtools::Extension::kSPV_NV_raw_access_chains, // 89
  spvtools::Extension::kSPV_EXT_long_vector, // 90
  spvtools::Extension::kSPV_EXT_shader_64bit_indexing, // 91
  spvtools::Extension::kSPV_NV_cooperative_matrix2, // 92
  spvtools::Extension::kSPV_NV_tensor_addressing, // 93
  spvtools::Extension::kSPV_INTEL_subgroups, // 94
  spvtools::Extension::kSPV_INTEL_media_block_io, // 95
  spvtools::Extension::kSPV_INTEL_float_controls2, // 96
  spvtools::Extension::kSPV_INTEL_shader_integer_functions2, // 97
  spvtools::Extension::kSPV_INTEL_function_pointers, // 98
  spvtools::Extension::kSPV_INTEL_inline_assembly, // 99
  spvtools::Extension::kSPV_EXT_shader_atomic_float_min_max, // 100
  spvtools::Extension::kSPV_INTEL_vector_compute, // 101
  spvtools::Extension::kSPV_KHR_expect_assume, // 102
  spvtools::Extension::kSPV_INTEL_device_side_avc_motion_estimation, // 103
  spvtools::Extension::kSPV_INTEL_variable_length_array, // 104
  spvtools::Extension::kSPV_ALTERA_fpga_memory_attributes, // 105
  spvtools::Extension::kSPV_INTEL_fpga_memory_attributes, // 106
  spvtools::Extension::kSPV_INTEL_fp_fast_math_mode, // 107
  spvtools::Extension::kSPV_ALTERA_arbitrary_precision_integers, // 108
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_integers, // 109
  spvtools::Extension::kSPV_ALTERA_arbitrary_precision_floating_point, // 110
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_floating_point, // 111
  spvtools::Extension::kSPV_INTEL_unstructured_loop_controls, // 112
  spvtools::Extension::kSPV_ALTERA_fpga_loop_controls, // 113
  spvtools::Extension::kSPV_INTEL_fpga_loop_controls, // 114
  spvtools::Extension::kSPV_INTEL_kernel_attributes, // 115
  spvtools::Extension::kSPV_ALTERA_fpga_memory_accesses, // 116
  spvtools::Extension::kSPV_INTEL_fpga_memory_accesses, // 117
  spvtools::Extension::kSPV_ALTERA_fpga_cluster_attributes, // 118
  spvtools::Extension::kSPV_INTEL_fpga_cluster_attributes, // 119
  spvtools::Extension::kSPV_ALTERA_loop_fuse, // 120
  spvtools::Extension::kSPV_INTEL_loop_fuse, // 121
  spvtools::Extension::kSPV_ALTERA_fpga_dsp_control, // 122
  spvtools::Extension::kSPV_INTEL_fpga_dsp_control, // 123
  spvtools::Extension::kSPV_INTEL_memory_access_aliasing, // 124
  spvtools::Extension::kSPV_ALTERA_fpga_invocation_pipelining_attributes, // 125
  spvtools::Extension::kSPV_INTEL_fpga_invocation_pipelining_attributes, // 126
  spvtools::Extension::kSPV_ALTERA_fpga_buffer_location, // 127
  spvtools::Extension::kSPV_INTEL_fpga_buffer_location, // 128
  spvtools::Extension::kSPV_ALTERA_arbitrary_precision_fixed_point, // 129
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_fixed_point, // 130
  spvtools::Extension::kSPV_ALTERA_usm_storage_classes, // 131
  spvtools::Extension::kSPV_INTEL_usm_storage_classes, // 132
  spvtools::Extension::kSPV_ALTERA_runtime_aligned, // 133
  spvtools::Extension::kSPV_INTEL_runtime_aligned, // 134
  spvtools::Extension::kSPV_ALTERA_io_pipes, // 135
  spvtools::Extension::kSPV_INTEL_io_pipes, // 136
  spvtools::Extension::kSPV_ALTERA_blocking_pipes, // 137
  spvtools::Extension::kSPV_INTEL_blocking_pipes, // 138
  spvtools::Extension::kSPV_ALTERA_fpga_reg, // 139
  spvtools::Extension::kSPV_INTEL_fpga_reg, // 140
  spvtools::Extension::kSPV_KHR_integer_dot_product, // 141
  spvtools::Extension::kSPV_KHR_cooperative_matrix, // 142
  spvtools::Extension::kSPV_EXT_replicated_composites, // 143
  spvtools::Extension::kSPV_KHR_bit_instructions, // 144
  spvtools::Extension::kSPV_KHR_subgroup_rotate, // 145
  spvtools::Extension::kSPV_KHR_float_controls2, // 146
  spvtools::Extension::kSPV_KHR_fma, // 147
  spvtools::Extension::kSPV_EXT_shader_atomic_float_add, // 148
  spvtools::Extension::kSPV_INTEL_long_composites, // 149
  spvtools::Extension::kSPV_EXT_optnone, // 150
  spvtools::Extension::kSPV_INTEL_optnone, // 151
  spvtools::Extension::kSPV_EXT_shader_atomic_float16_add, // 152
  spvtools::Extension::kSPV_INTEL_debug_module, // 153
  spvtools::Extension::kSPV_INTEL_bfloat16_conversion, // 154
  spvtools::Extension::kSPV_INTEL_split_barrier, // 155
  spvtools::Extension::kSPV_EXT_arithmetic_fence, // 156
  spvtools::Extension::kSPV_ALTERA_task_sequence, // 157
  spvtools::Extension::kSPV_INTEL_task_sequence, // 158
  spvtools::Extension::kSPV_INTEL_fp_max_error, // 159
  spvtools::Extension::kSPV_ALTERA_fpga_latency_control, // 160
  spvtools::Extension::kSPV_INTEL_fpga_latency_control, // 161
  spvtools::Extension::kSPV_ALTERA_fpga_argument_interfaces, // 162
  spvtools::Extension::kSPV_INTEL_fpga_argument_interfaces, // 163
  spvtools::Extension::kSPV_INTEL_global_variable_host_access, // 164
  spvtools::Extension::kSPV_ALTERA_global_variable_fpga_decorations, // 165
  spvtools::Extension::kSPV_INTEL_global_variable_fpga_decorations, // 166
  spvtools::Extension::kSPV_INTEL_subgroup_buffer_prefetch, // 167
  spvtools::Extension::kSPV_INTEL_2d_block_io, // 168
  spvtools::Extension::kSPV_INTEL_subgroup_matrix_multiply_accumulate, // 169
  spvtools::Extension::kSPV_INTEL_ternary_bitwise_function, // 170
  spvtools::Extension::kSPV_INTEL_function_variants, // 171
  spvtools::Extension::kSPV_KHR_uniform_group_instructions, // 172
  spvtools::Extension::kSPV_INTEL_tensor_float32_conversion, // 173
  spvtools::Extension::kSPV_INTEL_masked_gather_scatter, // 174
  spvtools::Extension::kSPV_INTEL_cache_controls, // 175
  spvtools::Extension::kSPV_INTEL_maximum_registers, // 176
  spvtools::Extension::kSPV_INTEL_bindless_images, // 177
  spvtools::Extension::kSPV_KHR_no_integer_wrap_decoration, // 178
  spvtools::Extension::kSPV_NV_mesh_shader, // 179
  spvtools::Extension::kSPV_EXT_mesh_shader, // 180
  spvtools::Extension::kSPV_GOOGLE_hlsl_functionality1, // 181
  spvtools::Extension::kSPV_GOOGLE_user_type, // 182
  spvtools::Extension::kSPV_KHR_subgroup_uniform_control_flow, // 183
  spvtools::Extension::kSPV_AMD_shader_early_and_late_fragment_tests, // 184
  spvtools::Extension::kSPV_AMD_shader_early_and_late_fragment_tests, // 185
  spvtools::Extension::kSPV_EXT_shader_stencil_export, // 186
  spvtools::Extension::kSPV_KHR_maximal_reconvergence, // 187
  spvtools::Extension::kSPV_KHR_linkonce_odr, // 188
  spvtools::Extension::kSPV_KHR_storage_buffer_storage_class, // 189
  spvtools::Extension::kSPV_KHR_variable_pointers, // 190
  spvtools::Extension::kSPV_KHR_terminate_invocation, // 191
  spvtools::Extension::kSPV_KHR_relaxed_extended_instruction, // 192
  spvtools::Extension::kSPV_KHR_ray_tracing, // 193
  spvtools::Extension::kSPV_KHR_ray_query, // 194
  spvtools::Extension::kSPV_NV_ray_tracing, // 195
  spvtools::Extension::kSPV_KHR_ray_tracing, // 196
  spvtools::Extension::kSPV_KHR_ray_query, // 197
  spvtools::Extension::kSPV_NV_displacement_micromap, // 198
  spvtools::Extension::kSPV_GOOGLE_decorate_string, // 199
  spvtools::Extension::kSPV_GOOGLE_hlsl_functionality1, // 200
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
