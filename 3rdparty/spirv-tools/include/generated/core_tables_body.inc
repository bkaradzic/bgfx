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
    case Extension::kSPV_ARM_graph: return IR(426, 14);
    case Extension::kSPV_ARM_tensors: return IR(440, 16);
    case Extension::kSPV_EXT_arithmetic_fence: return IR(456, 25);
    case Extension::kSPV_EXT_demote_to_helper_invocation: return IR(481, 36);
    case Extension::kSPV_EXT_descriptor_indexing: return IR(517, 28);
    case Extension::kSPV_EXT_float8: return IR(545, 15);
    case Extension::kSPV_EXT_fragment_fully_covered: return IR(560, 31);
    case Extension::kSPV_EXT_fragment_invocation_density: return IR(591, 36);
    case Extension::kSPV_EXT_fragment_shader_interlock: return IR(627, 34);
    case Extension::kSPV_EXT_mesh_shader: return IR(661, 20);
    case Extension::kSPV_EXT_opacity_micromap: return IR(681, 25);
    case Extension::kSPV_EXT_optnone: return IR(706, 16);
    case Extension::kSPV_EXT_physical_storage_buffer: return IR(722, 32);
    case Extension::kSPV_EXT_relaxed_printf_string_address_space: return IR(754, 44);
    case Extension::kSPV_EXT_replicated_composites: return IR(798, 30);
    case Extension::kSPV_EXT_shader_atomic_float16_add: return IR(828, 34);
    case Extension::kSPV_EXT_shader_atomic_float_add: return IR(862, 32);
    case Extension::kSPV_EXT_shader_atomic_float_min_max: return IR(894, 36);
    case Extension::kSPV_EXT_shader_image_int64: return IR(930, 27);
    case Extension::kSPV_EXT_shader_stencil_export: return IR(957, 30);
    case Extension::kSPV_EXT_shader_tile_image: return IR(987, 26);
    case Extension::kSPV_EXT_shader_viewport_index_layer: return IR(1013, 36);
    case Extension::kSPV_GOOGLE_decorate_string: return IR(1049, 27);
    case Extension::kSPV_GOOGLE_hlsl_functionality1: return IR(1076, 31);
    case Extension::kSPV_GOOGLE_user_type: return IR(1107, 21);
    case Extension::kSPV_INTEL_2d_block_io: return IR(1128, 22);
    case Extension::kSPV_INTEL_arbitrary_precision_fixed_point: return IR(1150, 42);
    case Extension::kSPV_INTEL_arbitrary_precision_floating_point: return IR(1192, 45);
    case Extension::kSPV_INTEL_arbitrary_precision_integers: return IR(1237, 39);
    case Extension::kSPV_INTEL_bfloat16_conversion: return IR(1276, 30);
    case Extension::kSPV_INTEL_bindless_images: return IR(1306, 26);
    case Extension::kSPV_INTEL_blocking_pipes: return IR(1332, 25);
    case Extension::kSPV_INTEL_cache_controls: return IR(1357, 25);
    case Extension::kSPV_INTEL_debug_module: return IR(1382, 23);
    case Extension::kSPV_INTEL_device_side_avc_motion_estimation: return IR(1405, 44);
    case Extension::kSPV_INTEL_float_controls2: return IR(1449, 26);
    case Extension::kSPV_INTEL_fp_fast_math_mode: return IR(1475, 28);
    case Extension::kSPV_INTEL_fp_max_error: return IR(1503, 23);
    case Extension::kSPV_INTEL_fpga_argument_interfaces: return IR(1526, 35);
    case Extension::kSPV_INTEL_fpga_buffer_location: return IR(1561, 31);
    case Extension::kSPV_INTEL_fpga_cluster_attributes: return IR(1592, 34);
    case Extension::kSPV_INTEL_fpga_dsp_control: return IR(1626, 27);
    case Extension::kSPV_INTEL_fpga_invocation_pipelining_attributes: return IR(1653, 48);
    case Extension::kSPV_INTEL_fpga_latency_control: return IR(1701, 31);
    case Extension::kSPV_INTEL_fpga_loop_controls: return IR(1732, 29);
    case Extension::kSPV_INTEL_fpga_memory_accesses: return IR(1761, 31);
    case Extension::kSPV_INTEL_fpga_memory_attributes: return IR(1792, 33);
    case Extension::kSPV_INTEL_fpga_reg: return IR(1825, 19);
    case Extension::kSPV_INTEL_function_pointers: return IR(1844, 28);
    case Extension::kSPV_INTEL_function_variants: return IR(1872, 28);
    case Extension::kSPV_INTEL_global_variable_fpga_decorations: return IR(1900, 43);
    case Extension::kSPV_INTEL_global_variable_host_access: return IR(1943, 38);
    case Extension::kSPV_INTEL_inline_assembly: return IR(1981, 26);
    case Extension::kSPV_INTEL_int4: return IR(2007, 15);
    case Extension::kSPV_INTEL_io_pipes: return IR(2022, 19);
    case Extension::kSPV_INTEL_kernel_attributes: return IR(2041, 28);
    case Extension::kSPV_INTEL_long_composites: return IR(2069, 26);
    case Extension::kSPV_INTEL_loop_fuse: return IR(2095, 20);
    case Extension::kSPV_INTEL_masked_gather_scatter: return IR(2115, 32);
    case Extension::kSPV_INTEL_maximum_registers: return IR(2147, 28);
    case Extension::kSPV_INTEL_media_block_io: return IR(2175, 25);
    case Extension::kSPV_INTEL_memory_access_aliasing: return IR(2200, 33);
    case Extension::kSPV_INTEL_optnone: return IR(2233, 18);
    case Extension::kSPV_INTEL_runtime_aligned: return IR(2251, 26);
    case Extension::kSPV_INTEL_shader_integer_functions2: return IR(2277, 36);
    case Extension::kSPV_INTEL_split_barrier: return IR(2313, 24);
    case Extension::kSPV_INTEL_subgroup_buffer_prefetch: return IR(2337, 35);
    case Extension::kSPV_INTEL_subgroup_matrix_multiply_accumulate: return IR(2372, 46);
    case Extension::kSPV_INTEL_subgroups: return IR(2418, 20);
    case Extension::kSPV_INTEL_task_sequence: return IR(2438, 24);
    case Extension::kSPV_INTEL_tensor_float32_conversion: return IR(2462, 36);
    case Extension::kSPV_INTEL_ternary_bitwise_function: return IR(2498, 35);
    case Extension::kSPV_INTEL_unstructured_loop_controls: return IR(2533, 37);
    case Extension::kSPV_INTEL_usm_storage_classes: return IR(2570, 30);
    case Extension::kSPV_INTEL_variable_length_array: return IR(2600, 32);
    case Extension::kSPV_INTEL_vector_compute: return IR(2632, 25);
    case Extension::kSPV_KHR_16bit_storage: return IR(2657, 22);
    case Extension::kSPV_KHR_8bit_storage: return IR(2679, 21);
    case Extension::kSPV_KHR_bfloat16: return IR(2700, 17);
    case Extension::kSPV_KHR_bit_instructions: return IR(2717, 25);
    case Extension::kSPV_KHR_compute_shader_derivatives: return IR(2742, 35);
    case Extension::kSPV_KHR_cooperative_matrix: return IR(2777, 27);
    case Extension::kSPV_KHR_device_group: return IR(2804, 21);
    case Extension::kSPV_KHR_expect_assume: return IR(2825, 22);
    case Extension::kSPV_KHR_float_controls: return IR(2847, 23);
    case Extension::kSPV_KHR_float_controls2: return IR(2870, 24);
    case Extension::kSPV_KHR_fragment_shader_barycentric: return IR(2894, 36);
    case Extension::kSPV_KHR_fragment_shading_rate: return IR(2930, 30);
    case Extension::kSPV_KHR_integer_dot_product: return IR(2960, 28);
    case Extension::kSPV_KHR_linkonce_odr: return IR(2988, 21);
    case Extension::kSPV_KHR_maximal_reconvergence: return IR(3009, 30);
    case Extension::kSPV_KHR_multiview: return IR(3039, 18);
    case Extension::kSPV_KHR_no_integer_wrap_decoration: return IR(3057, 35);
    case Extension::kSPV_KHR_non_semantic_info: return IR(3092, 26);
    case Extension::kSPV_KHR_physical_storage_buffer: return IR(3118, 32);
    case Extension::kSPV_KHR_post_depth_coverage: return IR(3150, 28);
    case Extension::kSPV_KHR_quad_control: return IR(3178, 21);
    case Extension::kSPV_KHR_ray_cull_mask: return IR(3199, 22);
    case Extension::kSPV_KHR_ray_query: return IR(3221, 18);
    case Extension::kSPV_KHR_ray_tracing: return IR(3239, 20);
    case Extension::kSPV_KHR_ray_tracing_position_fetch: return IR(3259, 35);
    case Extension::kSPV_KHR_relaxed_extended_instruction: return IR(3294, 37);
    case Extension::kSPV_KHR_shader_atomic_counter_ops: return IR(3331, 34);
    case Extension::kSPV_KHR_shader_ballot: return IR(3365, 22);
    case Extension::kSPV_KHR_shader_clock: return IR(3387, 21);
    case Extension::kSPV_KHR_shader_draw_parameters: return IR(3408, 31);
    case Extension::kSPV_KHR_storage_buffer_storage_class: return IR(3439, 37);
    case Extension::kSPV_KHR_subgroup_rotate: return IR(3476, 24);
    case Extension::kSPV_KHR_subgroup_uniform_control_flow: return IR(3500, 38);
    case Extension::kSPV_KHR_subgroup_vote: return IR(3538, 22);
    case Extension::kSPV_KHR_terminate_invocation: return IR(3560, 29);
    case Extension::kSPV_KHR_uniform_group_instructions: return IR(3589, 35);
    case Extension::kSPV_KHR_untyped_pointers: return IR(3624, 25);
    case Extension::kSPV_KHR_variable_pointers: return IR(3649, 26);
    case Extension::kSPV_KHR_vulkan_memory_model: return IR(3675, 28);
    case Extension::kSPV_KHR_workgroup_memory_explicit_layout: return IR(3703, 41);
    case Extension::kSPV_NVX_multiview_per_view_attributes: return IR(3744, 38);
    case Extension::kSPV_NV_bindless_texture: return IR(3782, 24);
    case Extension::kSPV_NV_cluster_acceleration_structure: return IR(3806, 38);
    case Extension::kSPV_NV_compute_shader_derivatives: return IR(3844, 34);
    case Extension::kSPV_NV_cooperative_matrix: return IR(3878, 26);
    case Extension::kSPV_NV_cooperative_matrix2: return IR(3904, 27);
    case Extension::kSPV_NV_cooperative_vector: return IR(3931, 26);
    case Extension::kSPV_NV_displacement_micromap: return IR(3957, 29);
    case Extension::kSPV_NV_fragment_shader_barycentric: return IR(3986, 35);
    case Extension::kSPV_NV_geometry_shader_passthrough: return IR(4021, 35);
    case Extension::kSPV_NV_linear_swept_spheres: return IR(4056, 28);
    case Extension::kSPV_NV_mesh_shader: return IR(4084, 19);
    case Extension::kSPV_NV_raw_access_chains: return IR(4103, 25);
    case Extension::kSPV_NV_ray_tracing: return IR(4128, 19);
    case Extension::kSPV_NV_ray_tracing_motion_blur: return IR(4147, 31);
    case Extension::kSPV_NV_sample_mask_override_coverage: return IR(4178, 37);
    case Extension::kSPV_NV_shader_atomic_fp16_vector: return IR(4215, 33);
    case Extension::kSPV_NV_shader_image_footprint: return IR(4248, 30);
    case Extension::kSPV_NV_shader_invocation_reorder: return IR(4278, 33);
    case Extension::kSPV_NV_shader_sm_builtins: return IR(4311, 26);
    case Extension::kSPV_NV_shader_subgroup_partitioned: return IR(4337, 35);
    case Extension::kSPV_NV_shading_rate: return IR(4372, 20);
    case Extension::kSPV_NV_stereo_view_rendering: return IR(4392, 29);
    case Extension::kSPV_NV_tensor_addressing: return IR(4421, 25);
    case Extension::kSPV_NV_viewport_array2: return IR(4446, 23);
    case Extension::kSPV_QCOM_cooperative_matrix_conversion: return IR(4469, 39);
    case Extension::kSPV_QCOM_image_processing: return IR(4508, 26);
    case Extension::kSPV_QCOM_image_processing2: return IR(4534, 27);
    case Extension::kSPV_QCOM_tile_shading: return IR(4561, 22);
    case Extension::kSPV_VALIDATOR_ignore_type_decl_unique: return IR(4583, 38);
    default: break;
  }
  return {};
}

// Extension names and values, ordered by name
// The fields in order are:
//   name, indexing into kStrings
//   enum value
static const std::array<NameValue,160> kExtensionNames{{
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
    {IR(426, 14), static_cast<uint32_t>(kSPV_ARM_graph)},
    {IR(440, 16), static_cast<uint32_t>(kSPV_ARM_tensors)},
    {IR(456, 25), static_cast<uint32_t>(kSPV_EXT_arithmetic_fence)},
    {IR(481, 36), static_cast<uint32_t>(kSPV_EXT_demote_to_helper_invocation)},
    {IR(517, 28), static_cast<uint32_t>(kSPV_EXT_descriptor_indexing)},
    {IR(545, 15), static_cast<uint32_t>(kSPV_EXT_float8)},
    {IR(560, 31), static_cast<uint32_t>(kSPV_EXT_fragment_fully_covered)},
    {IR(591, 36), static_cast<uint32_t>(kSPV_EXT_fragment_invocation_density)},
    {IR(627, 34), static_cast<uint32_t>(kSPV_EXT_fragment_shader_interlock)},
    {IR(661, 20), static_cast<uint32_t>(kSPV_EXT_mesh_shader)},
    {IR(681, 25), static_cast<uint32_t>(kSPV_EXT_opacity_micromap)},
    {IR(706, 16), static_cast<uint32_t>(kSPV_EXT_optnone)},
    {IR(722, 32), static_cast<uint32_t>(kSPV_EXT_physical_storage_buffer)},
    {IR(754, 44), static_cast<uint32_t>(kSPV_EXT_relaxed_printf_string_address_space)},
    {IR(798, 30), static_cast<uint32_t>(kSPV_EXT_replicated_composites)},
    {IR(828, 34), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float16_add)},
    {IR(862, 32), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float_add)},
    {IR(894, 36), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float_min_max)},
    {IR(930, 27), static_cast<uint32_t>(kSPV_EXT_shader_image_int64)},
    {IR(957, 30), static_cast<uint32_t>(kSPV_EXT_shader_stencil_export)},
    {IR(987, 26), static_cast<uint32_t>(kSPV_EXT_shader_tile_image)},
    {IR(1013, 36), static_cast<uint32_t>(kSPV_EXT_shader_viewport_index_layer)},
    {IR(1049, 27), static_cast<uint32_t>(kSPV_GOOGLE_decorate_string)},
    {IR(1076, 31), static_cast<uint32_t>(kSPV_GOOGLE_hlsl_functionality1)},
    {IR(1107, 21), static_cast<uint32_t>(kSPV_GOOGLE_user_type)},
    {IR(1128, 22), static_cast<uint32_t>(kSPV_INTEL_2d_block_io)},
    {IR(1150, 42), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_fixed_point)},
    {IR(1192, 45), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_floating_point)},
    {IR(1237, 39), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_integers)},
    {IR(1276, 30), static_cast<uint32_t>(kSPV_INTEL_bfloat16_conversion)},
    {IR(1306, 26), static_cast<uint32_t>(kSPV_INTEL_bindless_images)},
    {IR(1332, 25), static_cast<uint32_t>(kSPV_INTEL_blocking_pipes)},
    {IR(1357, 25), static_cast<uint32_t>(kSPV_INTEL_cache_controls)},
    {IR(1382, 23), static_cast<uint32_t>(kSPV_INTEL_debug_module)},
    {IR(1405, 44), static_cast<uint32_t>(kSPV_INTEL_device_side_avc_motion_estimation)},
    {IR(1449, 26), static_cast<uint32_t>(kSPV_INTEL_float_controls2)},
    {IR(1475, 28), static_cast<uint32_t>(kSPV_INTEL_fp_fast_math_mode)},
    {IR(1503, 23), static_cast<uint32_t>(kSPV_INTEL_fp_max_error)},
    {IR(1526, 35), static_cast<uint32_t>(kSPV_INTEL_fpga_argument_interfaces)},
    {IR(1561, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_buffer_location)},
    {IR(1592, 34), static_cast<uint32_t>(kSPV_INTEL_fpga_cluster_attributes)},
    {IR(1626, 27), static_cast<uint32_t>(kSPV_INTEL_fpga_dsp_control)},
    {IR(1653, 48), static_cast<uint32_t>(kSPV_INTEL_fpga_invocation_pipelining_attributes)},
    {IR(1701, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_latency_control)},
    {IR(1732, 29), static_cast<uint32_t>(kSPV_INTEL_fpga_loop_controls)},
    {IR(1761, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_memory_accesses)},
    {IR(1792, 33), static_cast<uint32_t>(kSPV_INTEL_fpga_memory_attributes)},
    {IR(1825, 19), static_cast<uint32_t>(kSPV_INTEL_fpga_reg)},
    {IR(1844, 28), static_cast<uint32_t>(kSPV_INTEL_function_pointers)},
    {IR(1872, 28), static_cast<uint32_t>(kSPV_INTEL_function_variants)},
    {IR(1900, 43), static_cast<uint32_t>(kSPV_INTEL_global_variable_fpga_decorations)},
    {IR(1943, 38), static_cast<uint32_t>(kSPV_INTEL_global_variable_host_access)},
    {IR(1981, 26), static_cast<uint32_t>(kSPV_INTEL_inline_assembly)},
    {IR(2007, 15), static_cast<uint32_t>(kSPV_INTEL_int4)},
    {IR(2022, 19), static_cast<uint32_t>(kSPV_INTEL_io_pipes)},
    {IR(2041, 28), static_cast<uint32_t>(kSPV_INTEL_kernel_attributes)},
    {IR(2069, 26), static_cast<uint32_t>(kSPV_INTEL_long_composites)},
    {IR(2095, 20), static_cast<uint32_t>(kSPV_INTEL_loop_fuse)},
    {IR(2115, 32), static_cast<uint32_t>(kSPV_INTEL_masked_gather_scatter)},
    {IR(2147, 28), static_cast<uint32_t>(kSPV_INTEL_maximum_registers)},
    {IR(2175, 25), static_cast<uint32_t>(kSPV_INTEL_media_block_io)},
    {IR(2200, 33), static_cast<uint32_t>(kSPV_INTEL_memory_access_aliasing)},
    {IR(2233, 18), static_cast<uint32_t>(kSPV_INTEL_optnone)},
    {IR(2251, 26), static_cast<uint32_t>(kSPV_INTEL_runtime_aligned)},
    {IR(2277, 36), static_cast<uint32_t>(kSPV_INTEL_shader_integer_functions2)},
    {IR(2313, 24), static_cast<uint32_t>(kSPV_INTEL_split_barrier)},
    {IR(2337, 35), static_cast<uint32_t>(kSPV_INTEL_subgroup_buffer_prefetch)},
    {IR(2372, 46), static_cast<uint32_t>(kSPV_INTEL_subgroup_matrix_multiply_accumulate)},
    {IR(2418, 20), static_cast<uint32_t>(kSPV_INTEL_subgroups)},
    {IR(2438, 24), static_cast<uint32_t>(kSPV_INTEL_task_sequence)},
    {IR(2462, 36), static_cast<uint32_t>(kSPV_INTEL_tensor_float32_conversion)},
    {IR(2498, 35), static_cast<uint32_t>(kSPV_INTEL_ternary_bitwise_function)},
    {IR(2533, 37), static_cast<uint32_t>(kSPV_INTEL_unstructured_loop_controls)},
    {IR(2570, 30), static_cast<uint32_t>(kSPV_INTEL_usm_storage_classes)},
    {IR(2600, 32), static_cast<uint32_t>(kSPV_INTEL_variable_length_array)},
    {IR(2632, 25), static_cast<uint32_t>(kSPV_INTEL_vector_compute)},
    {IR(2657, 22), static_cast<uint32_t>(kSPV_KHR_16bit_storage)},
    {IR(2679, 21), static_cast<uint32_t>(kSPV_KHR_8bit_storage)},
    {IR(2700, 17), static_cast<uint32_t>(kSPV_KHR_bfloat16)},
    {IR(2717, 25), static_cast<uint32_t>(kSPV_KHR_bit_instructions)},
    {IR(2742, 35), static_cast<uint32_t>(kSPV_KHR_compute_shader_derivatives)},
    {IR(2777, 27), static_cast<uint32_t>(kSPV_KHR_cooperative_matrix)},
    {IR(2804, 21), static_cast<uint32_t>(kSPV_KHR_device_group)},
    {IR(2825, 22), static_cast<uint32_t>(kSPV_KHR_expect_assume)},
    {IR(2847, 23), static_cast<uint32_t>(kSPV_KHR_float_controls)},
    {IR(2870, 24), static_cast<uint32_t>(kSPV_KHR_float_controls2)},
    {IR(2894, 36), static_cast<uint32_t>(kSPV_KHR_fragment_shader_barycentric)},
    {IR(2930, 30), static_cast<uint32_t>(kSPV_KHR_fragment_shading_rate)},
    {IR(2960, 28), static_cast<uint32_t>(kSPV_KHR_integer_dot_product)},
    {IR(2988, 21), static_cast<uint32_t>(kSPV_KHR_linkonce_odr)},
    {IR(3009, 30), static_cast<uint32_t>(kSPV_KHR_maximal_reconvergence)},
    {IR(3039, 18), static_cast<uint32_t>(kSPV_KHR_multiview)},
    {IR(3057, 35), static_cast<uint32_t>(kSPV_KHR_no_integer_wrap_decoration)},
    {IR(3092, 26), static_cast<uint32_t>(kSPV_KHR_non_semantic_info)},
    {IR(3118, 32), static_cast<uint32_t>(kSPV_KHR_physical_storage_buffer)},
    {IR(3150, 28), static_cast<uint32_t>(kSPV_KHR_post_depth_coverage)},
    {IR(3178, 21), static_cast<uint32_t>(kSPV_KHR_quad_control)},
    {IR(3199, 22), static_cast<uint32_t>(kSPV_KHR_ray_cull_mask)},
    {IR(3221, 18), static_cast<uint32_t>(kSPV_KHR_ray_query)},
    {IR(3239, 20), static_cast<uint32_t>(kSPV_KHR_ray_tracing)},
    {IR(3259, 35), static_cast<uint32_t>(kSPV_KHR_ray_tracing_position_fetch)},
    {IR(3294, 37), static_cast<uint32_t>(kSPV_KHR_relaxed_extended_instruction)},
    {IR(3331, 34), static_cast<uint32_t>(kSPV_KHR_shader_atomic_counter_ops)},
    {IR(3365, 22), static_cast<uint32_t>(kSPV_KHR_shader_ballot)},
    {IR(3387, 21), static_cast<uint32_t>(kSPV_KHR_shader_clock)},
    {IR(3408, 31), static_cast<uint32_t>(kSPV_KHR_shader_draw_parameters)},
    {IR(3439, 37), static_cast<uint32_t>(kSPV_KHR_storage_buffer_storage_class)},
    {IR(3476, 24), static_cast<uint32_t>(kSPV_KHR_subgroup_rotate)},
    {IR(3500, 38), static_cast<uint32_t>(kSPV_KHR_subgroup_uniform_control_flow)},
    {IR(3538, 22), static_cast<uint32_t>(kSPV_KHR_subgroup_vote)},
    {IR(3560, 29), static_cast<uint32_t>(kSPV_KHR_terminate_invocation)},
    {IR(3589, 35), static_cast<uint32_t>(kSPV_KHR_uniform_group_instructions)},
    {IR(3624, 25), static_cast<uint32_t>(kSPV_KHR_untyped_pointers)},
    {IR(3649, 26), static_cast<uint32_t>(kSPV_KHR_variable_pointers)},
    {IR(3675, 28), static_cast<uint32_t>(kSPV_KHR_vulkan_memory_model)},
    {IR(3703, 41), static_cast<uint32_t>(kSPV_KHR_workgroup_memory_explicit_layout)},
    {IR(3744, 38), static_cast<uint32_t>(kSPV_NVX_multiview_per_view_attributes)},
    {IR(3782, 24), static_cast<uint32_t>(kSPV_NV_bindless_texture)},
    {IR(3806, 38), static_cast<uint32_t>(kSPV_NV_cluster_acceleration_structure)},
    {IR(3844, 34), static_cast<uint32_t>(kSPV_NV_compute_shader_derivatives)},
    {IR(3878, 26), static_cast<uint32_t>(kSPV_NV_cooperative_matrix)},
    {IR(3904, 27), static_cast<uint32_t>(kSPV_NV_cooperative_matrix2)},
    {IR(3931, 26), static_cast<uint32_t>(kSPV_NV_cooperative_vector)},
    {IR(3957, 29), static_cast<uint32_t>(kSPV_NV_displacement_micromap)},
    {IR(3986, 35), static_cast<uint32_t>(kSPV_NV_fragment_shader_barycentric)},
    {IR(4021, 35), static_cast<uint32_t>(kSPV_NV_geometry_shader_passthrough)},
    {IR(4056, 28), static_cast<uint32_t>(kSPV_NV_linear_swept_spheres)},
    {IR(4084, 19), static_cast<uint32_t>(kSPV_NV_mesh_shader)},
    {IR(4103, 25), static_cast<uint32_t>(kSPV_NV_raw_access_chains)},
    {IR(4128, 19), static_cast<uint32_t>(kSPV_NV_ray_tracing)},
    {IR(4147, 31), static_cast<uint32_t>(kSPV_NV_ray_tracing_motion_blur)},
    {IR(4178, 37), static_cast<uint32_t>(kSPV_NV_sample_mask_override_coverage)},
    {IR(4215, 33), static_cast<uint32_t>(kSPV_NV_shader_atomic_fp16_vector)},
    {IR(4248, 30), static_cast<uint32_t>(kSPV_NV_shader_image_footprint)},
    {IR(4278, 33), static_cast<uint32_t>(kSPV_NV_shader_invocation_reorder)},
    {IR(4311, 26), static_cast<uint32_t>(kSPV_NV_shader_sm_builtins)},
    {IR(4337, 35), static_cast<uint32_t>(kSPV_NV_shader_subgroup_partitioned)},
    {IR(4372, 20), static_cast<uint32_t>(kSPV_NV_shading_rate)},
    {IR(4392, 29), static_cast<uint32_t>(kSPV_NV_stereo_view_rendering)},
    {IR(4421, 25), static_cast<uint32_t>(kSPV_NV_tensor_addressing)},
    {IR(4446, 23), static_cast<uint32_t>(kSPV_NV_viewport_array2)},
    {IR(4469, 39), static_cast<uint32_t>(kSPV_QCOM_cooperative_matrix_conversion)},
    {IR(4508, 26), static_cast<uint32_t>(kSPV_QCOM_image_processing)},
    {IR(4534, 27), static_cast<uint32_t>(kSPV_QCOM_image_processing2)},
    {IR(4561, 22), static_cast<uint32_t>(kSPV_QCOM_tile_shading)},
    {IR(4583, 38), static_cast<uint32_t>(kSPV_VALIDATOR_ignore_type_decl_unique)},
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
static const std::array<OperandDesc, 1188> kOperandsByValue{{
  {0,IR(0, 0),IR(4621, 9)/* ReadOnly */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {1,IR(0, 0),IR(4637, 10)/* WriteOnly */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {2,IR(0, 0),IR(4647, 10)/* ReadWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {0,IR(0, 0),IR(4657, 8)/* Logical */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {1,IR(0, 0),IR(4665, 11)/* Physical32 */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {2,IR(0, 0),IR(4686, 11)/* Physical64 */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {5348,IR(0, 0),IR(4697, 24)/* PhysicalStorageBuffer64 */,IR(0, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {0,IR(0, 0),IR(4779, 9)/* Position */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {1,IR(0, 0),IR(4795, 10)/* PointSize */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {3,IR(0, 0),IR(4805, 13)/* ClipDistance */,IR(0, 0),IR(4, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4,IR(0, 0),IR(4818, 13)/* CullDistance */,IR(0, 0),IR(5, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5,IR(0, 0),IR(4831, 9)/* VertexId */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {6,IR(0, 0),IR(4840, 11)/* InstanceId */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {7,IR(0, 0),IR(4851, 12)/* PrimitiveId */,IR(0, 0),IR(6, 6),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {8,IR(0, 0),IR(4941, 13)/* InvocationId */,IR(0, 0),IR(12, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {9,IR(0, 0),IR(4954, 6)/* Layer */,IR(0, 0),IR(14, 5),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {10,IR(0, 0),IR(5000, 14)/* ViewportIndex */,IR(0, 0),IR(19, 5),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {11,IR(0, 0),IR(5048, 15)/* TessLevelOuter */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {12,IR(0, 0),IR(5063, 15)/* TessLevelInner */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {13,IR(0, 0),IR(5078, 10)/* TessCoord */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {14,IR(0, 0),IR(5088, 14)/* PatchVertices */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {15,IR(0, 0),IR(5102, 10)/* FragCoord */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {16,IR(0, 0),IR(5112, 11)/* PointCoord */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {17,IR(0, 0),IR(5123, 12)/* FrontFacing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {18,IR(0, 0),IR(5135, 9)/* SampleId */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {19,IR(0, 0),IR(5162, 15)/* SamplePosition */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {20,IR(0, 0),IR(5177, 11)/* SampleMask */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {22,IR(0, 0),IR(5188, 10)/* FragDepth */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {23,IR(0, 0),IR(5198, 17)/* HelperInvocation */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {24,IR(0, 0),IR(5215, 14)/* NumWorkgroups */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {25,IR(0, 0),IR(5229, 14)/* WorkgroupSize */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {26,IR(0, 0),IR(5243, 12)/* WorkgroupId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {27,IR(0, 0),IR(5255, 18)/* LocalInvocationId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {28,IR(0, 0),IR(5273, 19)/* GlobalInvocationId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {29,IR(0, 0),IR(5292, 21)/* LocalInvocationIndex */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {30,IR(0, 0),IR(5313, 8)/* WorkDim */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {31,IR(0, 0),IR(5321, 11)/* GlobalSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {32,IR(0, 0),IR(5332, 22)/* EnqueuedWorkgroupSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {33,IR(0, 0),IR(5354, 13)/* GlobalOffset */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {34,IR(0, 0),IR(5367, 15)/* GlobalLinearId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {36,IR(0, 0),IR(5382, 13)/* SubgroupSize */,IR(0, 0),IR(26, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {37,IR(0, 0),IR(5429, 16)/* SubgroupMaxSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {38,IR(0, 0),IR(5445, 13)/* NumSubgroups */,IR(0, 0),IR(29, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {39,IR(0, 0),IR(5458, 21)/* NumEnqueuedSubgroups */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {40,IR(0, 0),IR(5479, 11)/* SubgroupId */,IR(0, 0),IR(29, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {41,IR(0, 0),IR(5490, 26)/* SubgroupLocalInvocationId */,IR(0, 0),IR(26, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {42,IR(0, 0),IR(5516, 12)/* VertexIndex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {43,IR(0, 0),IR(5528, 14)/* InstanceIndex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4160,IR(0, 0),IR(5542, 10)/* CoreIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4161,IR(0, 0),IR(5568, 13)/* CoreCountARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4162,IR(0, 0),IR(5581, 13)/* CoreMaxIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4163,IR(0, 0),IR(5594, 10)/* WarpIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4164,IR(0, 0),IR(5604, 13)/* WarpMaxIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4416,IR(0, 0),IR(5617, 15)/* SubgroupEqMask */,IR(1, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4417,IR(0, 0),IR(5672, 15)/* SubgroupGeMask */,IR(2, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4418,IR(0, 0),IR(5705, 15)/* SubgroupGtMask */,IR(3, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4419,IR(0, 0),IR(5738, 15)/* SubgroupLeMask */,IR(4, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4420,IR(0, 0),IR(5771, 15)/* SubgroupLtMask */,IR(5, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4424,IR(0, 0),IR(5804, 11)/* BaseVertex */,IR(0, 0),IR(34, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4425,IR(0, 0),IR(5830, 13)/* BaseInstance */,IR(0, 0),IR(34, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4426,IR(0, 0),IR(5843, 10)/* DrawIndex */,IR(0, 0),IR(35, 3),IR(4, 3),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4432,IR(0, 0),IR(5853, 24)/* PrimitiveShadingRateKHR */,IR(0, 0),IR(38, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4438,IR(0, 0),IR(5900, 12)/* DeviceIndex */,IR(0, 0),IR(39, 1),IR(8, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4440,IR(0, 0),IR(5924, 10)/* ViewIndex */,IR(0, 0),IR(40, 1),IR(9, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4444,IR(0, 0),IR(5944, 15)/* ShadingRateKHR */,IR(0, 0),IR(38, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4492,IR(0, 0),IR(5959, 15)/* TileOffsetQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4493,IR(0, 0),IR(5990, 18)/* TileDimensionQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4494,IR(0, 0),IR(6008, 18)/* TileApronSizeQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4992,IR(0, 0),IR(6026, 20)/* BaryCoordNoPerspAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4993,IR(0, 0),IR(6046, 28)/* BaryCoordNoPerspCentroidAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4994,IR(0, 0),IR(6074, 26)/* BaryCoordNoPerspSampleAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4995,IR(0, 0),IR(6100, 19)/* BaryCoordSmoothAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4996,IR(0, 0),IR(6119, 27)/* BaryCoordSmoothCentroidAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4997,IR(0, 0),IR(6146, 25)/* BaryCoordSmoothSampleAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4998,IR(0, 0),IR(6171, 22)/* BaryCoordPullModelAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5014,IR(0, 0),IR(6193, 18)/* FragStencilRefEXT */,IR(0, 0),IR(42, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5021,IR(0, 0),IR(6228, 29)/* RemainingRecursionLevelsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5073,IR(0, 0),IR(6275, 16)/* ShaderIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5253,IR(0, 0),IR(6291, 15)/* ViewportMaskNV */,IR(0, 0),IR(44, 2),IR(12, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5257,IR(0, 0),IR(6327, 20)/* SecondaryPositionNV */,IR(0, 0),IR(46, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5258,IR(0, 0),IR(6366, 24)/* SecondaryViewportMaskNV */,IR(0, 0),IR(46, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5261,IR(0, 0),IR(6390, 18)/* PositionPerViewNV */,IR(0, 0),IR(47, 2),IR(15, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5262,IR(0, 0),IR(6428, 22)/* ViewportMaskPerViewNV */,IR(0, 0),IR(47, 2),IR(15, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5264,IR(0, 0),IR(6450, 16)/* FullyCoveredEXT */,IR(0, 0),IR(49, 1),IR(17, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5274,IR(0, 0),IR(6490, 12)/* TaskCountNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5275,IR(0, 0),IR(6502, 17)/* PrimitiveCountNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5276,IR(0, 0),IR(6519, 19)/* PrimitiveIndicesNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5277,IR(0, 0),IR(6538, 22)/* ClipDistancePerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5278,IR(0, 0),IR(6560, 22)/* CullDistancePerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5279,IR(0, 0),IR(6582, 15)/* LayerPerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5280,IR(0, 0),IR(6597, 16)/* MeshViewCountNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5281,IR(0, 0),IR(6613, 18)/* MeshViewIndicesNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5286,IR(0, 0),IR(6631, 13)/* BaryCoordKHR */,IR(6, 1),IR(51, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5287,IR(0, 0),IR(6679, 20)/* BaryCoordNoPerspKHR */,IR(7, 1),IR(51, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5292,IR(0, 0),IR(6718, 12)/* FragSizeEXT */,IR(8, 1),IR(52, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5293,IR(0, 0),IR(6764, 23)/* FragInvocationCountEXT */,IR(9, 1),IR(52, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5294,IR(0, 0),IR(6809, 25)/* PrimitivePointIndicesEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5295,IR(0, 0),IR(6834, 24)/* PrimitiveLineIndicesEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5296,IR(0, 0),IR(6858, 28)/* PrimitiveTriangleIndicesEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5299,IR(0, 0),IR(6886, 17)/* CullPrimitiveEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5319,IR(0, 0),IR(6903, 12)/* LaunchIdKHR */,IR(10, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5320,IR(0, 0),IR(6926, 14)/* LaunchSizeKHR */,IR(11, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5321,IR(0, 0),IR(6953, 18)/* WorldRayOriginKHR */,IR(12, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5322,IR(0, 0),IR(6988, 21)/* WorldRayDirectionKHR */,IR(13, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5323,IR(0, 0),IR(7029, 19)/* ObjectRayOriginKHR */,IR(14, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5324,IR(0, 0),IR(7066, 22)/* ObjectRayDirectionKHR */,IR(15, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5325,IR(0, 0),IR(7109, 11)/* RayTminKHR */,IR(16, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5326,IR(0, 0),IR(7130, 11)/* RayTmaxKHR */,IR(17, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5327,IR(0, 0),IR(7151, 23)/* InstanceCustomIndexKHR */,IR(18, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5330,IR(0, 0),IR(7196, 17)/* ObjectToWorldKHR */,IR(19, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5331,IR(0, 0),IR(7229, 17)/* WorldToObjectKHR */,IR(20, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5332,IR(0, 0),IR(7262, 7)/* HitTNV */,IR(0, 0),IR(56, 1),IR(26, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5333,IR(0, 0),IR(7269, 11)/* HitKindKHR */,IR(21, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5334,IR(0, 0),IR(7290, 17)/* CurrentRayTimeNV */,IR(0, 0),IR(57, 1),IR(27, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5335,IR(0, 0),IR(7330, 30)/* HitTriangleVertexPositionsKHR */,IR(0, 0),IR(58, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5337,IR(0, 0),IR(7387, 34)/* HitMicroTriangleVertexPositionsNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5344,IR(0, 0),IR(7454, 37)/* HitMicroTriangleVertexBarycentricsNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5351,IR(0, 0),IR(7491, 20)/* IncomingRayFlagsKHR */,IR(22, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5352,IR(0, 0),IR(7530, 20)/* RayGeometryIndexKHR */,IR(0, 0),IR(60, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5359,IR(0, 0),IR(7550, 14)/* HitIsSphereNV */,IR(0, 0),IR(61, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5360,IR(0, 0),IR(7592, 11)/* HitIsLSSNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5361,IR(0, 0),IR(7642, 20)/* HitSpherePositionNV */,IR(0, 0),IR(61, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5374,IR(0, 0),IR(7662, 13)/* WarpsPerSMNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5375,IR(0, 0),IR(7694, 10)/* SMCountNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5376,IR(0, 0),IR(7704, 9)/* WarpIDNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5377,IR(0, 0),IR(7713, 7)/* SMIDNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5396,IR(0, 0),IR(7720, 18)/* HitLSSPositionsNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5405,IR(0, 0),IR(7738, 34)/* HitKindFrontFacingMicroTriangleNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5406,IR(0, 0),IR(7772, 33)/* HitKindBackFacingMicroTriangleNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5420,IR(0, 0),IR(7805, 18)/* HitSphereRadiusNV */,IR(0, 0),IR(61, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5421,IR(0, 0),IR(7823, 14)/* HitLSSRadiiNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5436,IR(0, 0),IR(7837, 12)/* ClusterIDNV */,IR(0, 0),IR(64, 1),IR(31, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {6021,IR(0, 0),IR(7890, 12)/* CullMaskKHR */,IR(0, 0),IR(65, 1),IR(32, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {0,IR(0, 0),IR(7917, 7)/* Matrix */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {1,IR(0, 0),IR(4788, 7)/* Shader */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {2,IR(0, 0),IR(4863, 9)/* Geometry */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {3,IR(0, 0),IR(4872, 13)/* Tessellation */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4,IR(0, 0),IR(4676, 10)/* Addresses */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5,IR(0, 0),IR(7924, 8)/* Linkage */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6,IR(0, 0),IR(4630, 7)/* Kernel */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {7,IR(0, 0),IR(7932, 9)/* Vector16 */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {8,IR(0, 0),IR(7941, 14)/* Float16Buffer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {9,IR(0, 0),IR(7955, 8)/* Float16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {10,IR(0, 0),IR(7963, 8)/* Float64 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {11,IR(0, 0),IR(7971, 6)/* Int64 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {12,IR(0, 0),IR(7977, 13)/* Int64Atomics */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {13,IR(0, 0),IR(7990, 11)/* ImageBasic */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {14,IR(0, 0),IR(8001, 15)/* ImageReadWrite */,IR(0, 0),IR(68, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {15,IR(0, 0),IR(8016, 12)/* ImageMipmap */,IR(0, 0),IR(68, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {17,IR(0, 0),IR(8028, 6)/* Pipes */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {18,IR(0, 0),IR(8034, 7)/* Groups */,IR(0, 0),IR(1, 0),IR(33, 1),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {19,IR(0, 0),IR(8041, 14)/* DeviceEnqueue */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {20,IR(0, 0),IR(8055, 15)/* LiteralSampler */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {21,IR(0, 0),IR(8070, 14)/* AtomicStorage */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {22,IR(0, 0),IR(8084, 6)/* Int16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {23,IR(0, 0),IR(8090, 22)/* TessellationPointSize */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {24,IR(0, 0),IR(8112, 18)/* GeometryPointSize */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {25,IR(0, 0),IR(8130, 20)/* ImageGatherExtended */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {27,IR(0, 0),IR(8150, 24)/* StorageImageMultisample */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {28,IR(0, 0),IR(8174, 34)/* UniformBufferArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {29,IR(0, 0),IR(8208, 33)/* SampledImageArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {30,IR(0, 0),IR(8241, 34)/* StorageBufferArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {31,IR(0, 0),IR(8275, 33)/* StorageImageArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {32,IR(0, 0),IR(4805, 13)/* ClipDistance */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {33,IR(0, 0),IR(4818, 13)/* CullDistance */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {34,IR(0, 0),IR(8308, 15)/* ImageCubeArray */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {35,IR(0, 0),IR(5144, 18)/* SampleRateShading */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {36,IR(0, 0),IR(8340, 10)/* ImageRect */,IR(0, 0),IR(71, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {37,IR(0, 0),IR(8350, 12)/* SampledRect */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {38,IR(0, 0),IR(8362, 15)/* GenericPointer */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {39,IR(0, 0),IR(8377, 5)/* Int8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {40,IR(0, 0),IR(8382, 16)/* InputAttachment */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {41,IR(0, 0),IR(8398, 16)/* SparseResidency */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {42,IR(0, 0),IR(8414, 7)/* MinLod */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {43,IR(0, 0),IR(8421, 10)/* Sampled1D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {44,IR(0, 0),IR(8431, 8)/* Image1D */,IR(0, 0),IR(72, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {45,IR(0, 0),IR(8323, 17)/* SampledCubeArray */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {46,IR(0, 0),IR(8439, 14)/* SampledBuffer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {47,IR(0, 0),IR(8453, 12)/* ImageBuffer */,IR(0, 0),IR(73, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {48,IR(0, 0),IR(8465, 13)/* ImageMSArray */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {49,IR(0, 0),IR(8478, 28)/* StorageImageExtendedFormats */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {50,IR(0, 0),IR(8506, 11)/* ImageQuery */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {51,IR(0, 0),IR(8517, 18)/* DerivativeControl */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {52,IR(0, 0),IR(8535, 22)/* InterpolationFunction */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {53,IR(0, 0),IR(8557, 18)/* TransformFeedback */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {54,IR(0, 0),IR(8575, 16)/* GeometryStreams */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {55,IR(0, 0),IR(8591, 30)/* StorageImageReadWithoutFormat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {56,IR(0, 0),IR(8621, 31)/* StorageImageWriteWithoutFormat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {57,IR(0, 0),IR(5014, 14)/* MultiViewport */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {58,IR(0, 0),IR(8652, 17)/* SubgroupDispatch */,IR(0, 0),IR(74, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {59,IR(0, 0),IR(8669, 13)/* NamedBarrier */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {60,IR(0, 0),IR(8682, 12)/* PipeStorage */,IR(0, 0),IR(75, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {61,IR(0, 0),IR(5395, 16)/* GroupNonUniform */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {62,IR(0, 0),IR(8694, 20)/* GroupNonUniformVote */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {63,IR(0, 0),IR(8714, 26)/* GroupNonUniformArithmetic */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {64,IR(0, 0),IR(5650, 22)/* GroupNonUniformBallot */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {65,IR(0, 0),IR(8740, 23)/* GroupNonUniformShuffle */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {66,IR(0, 0),IR(8763, 31)/* GroupNonUniformShuffleRelative */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {67,IR(0, 0),IR(8794, 25)/* GroupNonUniformClustered */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {68,IR(0, 0),IR(8819, 20)/* GroupNonUniformQuad */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {69,IR(0, 0),IR(4960, 12)/* ShaderLayer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {70,IR(0, 0),IR(5028, 20)/* ShaderViewportIndex */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {71,IR(0, 0),IR(8839, 18)/* UniformDecoration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4165,IR(0, 0),IR(5552, 16)/* CoreBuiltinsARM */,IR(0, 0),IR(1, 0),IR(34, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4166,IR(0, 0),IR(8857, 28)/* TileImageColorReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4167,IR(0, 0),IR(8885, 28)/* TileImageDepthReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4168,IR(0, 0),IR(8913, 30)/* TileImageStencilReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4174,IR(0, 0),IR(8943, 11)/* TensorsARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4175,IR(0, 0),IR(8954, 37)/* StorageTensorArrayDynamicIndexingARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4176,IR(0, 0),IR(8991, 40)/* StorageTensorArrayNonUniformIndexingARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4191,IR(0, 0),IR(9031, 9)/* GraphARM */,IR(0, 0),IR(1, 0),IR(37, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4201,IR(0, 0),IR(9040, 28)/* CooperativeMatrixLayoutsARM */,IR(0, 0),IR(1, 0),IR(38, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4212,IR(0, 0),IR(9068, 10)/* Float8EXT */,IR(0, 0),IR(1, 0),IR(39, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4213,IR(0, 0),IR(9078, 27)/* Float8CooperativeMatrixEXT */,IR(0, 0),IR(77, 2),IR(39, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4422,IR(0, 0),IR(5877, 23)/* FragmentShadingRateKHR */,IR(0, 0),IR(3, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4423,IR(0, 0),IR(5411, 18)/* SubgroupBallotKHR */,IR(0, 0),IR(1, 0),IR(2, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4427,IR(0, 0),IR(5815, 15)/* DrawParameters */,IR(0, 0),IR(3, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4428,IR(0, 0),IR(9126, 33)/* WorkgroupMemoryExplicitLayoutKHR */,IR(0, 0),IR(3, 1),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4429,IR(0, 0),IR(9159, 43)/* WorkgroupMemoryExplicitLayout8BitAccessKHR */,IR(0, 0),IR(79, 1),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4430,IR(0, 0),IR(9202, 44)/* WorkgroupMemoryExplicitLayout16BitAccessKHR */,IR(0, 0),IR(79, 1),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4431,IR(0, 0),IR(9246, 16)/* SubgroupVoteKHR */,IR(0, 0),IR(1, 0),IR(41, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4433,IR(0, 0),IR(9262, 25)/* StorageBuffer16BitAccess */,IR(23, 1),IR(1, 0),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4434,IR(0, 0),IR(9315, 35)/* UniformAndStorageBuffer16BitAccess */,IR(24, 1),IR(80, 1),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4435,IR(0, 0),IR(9367, 22)/* StoragePushConstant16 */,IR(0, 0),IR(1, 0),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4436,IR(0, 0),IR(9389, 21)/* StorageInputOutput16 */,IR(0, 0),IR(1, 0),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4437,IR(0, 0),IR(5912, 12)/* DeviceGroup */,IR(0, 0),IR(1, 0),IR(8, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4439,IR(0, 0),IR(5934, 10)/* MultiView */,IR(0, 0),IR(3, 1),IR(9, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4441,IR(0, 0),IR(9410, 30)/* VariablePointersStorageBuffer */,IR(0, 0),IR(3, 1),IR(43, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4442,IR(0, 0),IR(9440, 17)/* VariablePointers */,IR(0, 0),IR(81, 1),IR(43, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4445,IR(0, 0),IR(9457, 17)/* AtomicStorageOps */,IR(0, 0),IR(82, 1),IR(44, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4447,IR(0, 0),IR(9474, 28)/* SampleMaskPostDepthCoverage */,IR(0, 0),IR(1, 0),IR(45, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4448,IR(0, 0),IR(9502, 24)/* StorageBuffer8BitAccess */,IR(0, 0),IR(1, 0),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4449,IR(0, 0),IR(9526, 34)/* UniformAndStorageBuffer8BitAccess */,IR(0, 0),IR(83, 1),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4450,IR(0, 0),IR(9560, 21)/* StoragePushConstant8 */,IR(0, 0),IR(1, 0),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4464,IR(0, 0),IR(9581, 15)/* DenormPreserve */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4465,IR(0, 0),IR(9596, 18)/* DenormFlushToZero */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4466,IR(0, 0),IR(9614, 25)/* SignedZeroInfNanPreserve */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4467,IR(0, 0),IR(9639, 16)/* RoundingModeRTE */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4468,IR(0, 0),IR(9655, 16)/* RoundingModeRTZ */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4471,IR(0, 0),IR(9671, 23)/* RayQueryProvisionalKHR */,IR(0, 0),IR(3, 1),IR(48, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4472,IR(0, 0),IR(9694, 12)/* RayQueryKHR */,IR(0, 0),IR(3, 1),IR(48, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4473,IR(0, 0),IR(9706, 19)/* UntypedPointersKHR */,IR(0, 0),IR(1, 0),IR(49, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4478,IR(0, 0),IR(9725, 32)/* RayTraversalPrimitiveCullingKHR */,IR(0, 0),IR(84, 2),IR(50, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4479,IR(0, 0),IR(4898, 14)/* RayTracingKHR */,IR(0, 0),IR(3, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4484,IR(0, 0),IR(9757, 26)/* TextureSampleWeightedQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4485,IR(0, 0),IR(9783, 21)/* TextureBoxFilterQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4486,IR(0, 0),IR(9804, 22)/* TextureBlockMatchQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4495,IR(0, 0),IR(5974, 16)/* TileShadingQCOM */,IR(0, 0),IR(3, 1),IR(53, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4496,IR(0, 0),IR(9826, 32)/* CooperativeMatrixConversionQCOM */,IR(0, 0),IR(86, 1),IR(54, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4498,IR(0, 0),IR(9858, 23)/* TextureBlockMatch2QCOM */,IR(0, 0),IR(1, 0),IR(55, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5008,IR(0, 0),IR(9881, 16)/* Float16ImageAMD */,IR(0, 0),IR(3, 1),IR(56, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5009,IR(0, 0),IR(9897, 22)/* ImageGatherBiasLodAMD */,IR(0, 0),IR(3, 1),IR(57, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5010,IR(0, 0),IR(9919, 16)/* FragmentMaskAMD */,IR(0, 0),IR(3, 1),IR(58, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5013,IR(0, 0),IR(6211, 17)/* StencilExportEXT */,IR(0, 0),IR(3, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5015,IR(0, 0),IR(9935, 21)/* ImageReadWriteLodAMD */,IR(0, 0),IR(3, 1),IR(59, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5016,IR(0, 0),IR(9956, 14)/* Int64ImageEXT */,IR(0, 0),IR(3, 1),IR(60, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5055,IR(0, 0),IR(9970, 15)/* ShaderClockKHR */,IR(0, 0),IR(1, 0),IR(61, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5067,IR(0, 0),IR(6257, 18)/* ShaderEnqueueAMDX */,IR(0, 0),IR(3, 1),IR(62, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5087,IR(0, 0),IR(9985, 15)/* QuadControlKHR */,IR(0, 0),IR(1, 0),IR(63, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5112,IR(0, 0),IR(10000, 14)/* Int4TypeINTEL */,IR(0, 0),IR(1, 0),IR(64, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5114,IR(0, 0),IR(10014, 27)/* Int4CooperativeMatrixINTEL */,IR(0, 0),IR(87, 2),IR(64, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5116,IR(0, 0),IR(10041, 16)/* BFloat16TypeKHR */,IR(0, 0),IR(1, 0),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5117,IR(0, 0),IR(10057, 22)/* BFloat16DotProductKHR */,IR(0, 0),IR(89, 1),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5118,IR(0, 0),IR(10079, 29)/* BFloat16CooperativeMatrixKHR */,IR(0, 0),IR(90, 2),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5249,IR(0, 0),IR(10108, 29)/* SampleMaskOverrideCoverageNV */,IR(0, 0),IR(25, 1),IR(66, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5251,IR(0, 0),IR(10137, 28)/* GeometryShaderPassthroughNV */,IR(0, 0),IR(69, 1),IR(67, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5254,IR(0, 0),IR(4972, 28)/* ShaderViewportIndexLayerEXT */,IR(25, 1),IR(92, 1),IR(68, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5255,IR(0, 0),IR(6306, 21)/* ShaderViewportMaskNV */,IR(0, 0),IR(93, 1),IR(70, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5259,IR(0, 0),IR(6347, 19)/* ShaderStereoViewNV */,IR(0, 0),IR(94, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5260,IR(0, 0),IR(6408, 20)/* PerViewAttributesNV */,IR(0, 0),IR(40, 1),IR(71, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5265,IR(0, 0),IR(6466, 24)/* FragmentFullyCoveredEXT */,IR(0, 0),IR(3, 1),IR(17, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5266,IR(0, 0),IR(4912, 14)/* MeshShadingNV */,IR(0, 0),IR(3, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5282,IR(0, 0),IR(10192, 17)/* ImageFootprintNV */,IR(0, 0),IR(1, 0),IR(72, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5283,IR(0, 0),IR(4926, 15)/* MeshShadingEXT */,IR(0, 0),IR(3, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5284,IR(0, 0),IR(6656, 23)/* FragmentBarycentricKHR */,IR(26, 1),IR(1, 0),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5288,IR(0, 0),IR(10231, 31)/* ComputeDerivativeGroupQuadsKHR */,IR(27, 1),IR(3, 1),IR(73, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5291,IR(0, 0),IR(6745, 19)/* FragmentDensityEXT */,IR(28, 1),IR(3, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5297,IR(0, 0),IR(10306, 29)/* GroupNonUniformPartitionedNV */,IR(0, 0),IR(1, 0),IR(75, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5301,IR(0, 0),IR(10335, 17)/* ShaderNonUniform */,IR(29, 1),IR(3, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5302,IR(0, 0),IR(10372, 23)/* RuntimeDescriptorArray */,IR(30, 1),IR(3, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5303,IR(0, 0),IR(10421, 36)/* InputAttachmentArrayDynamicIndexing */,IR(31, 1),IR(95, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5304,IR(0, 0),IR(10496, 39)/* UniformTexelBufferArrayDynamicIndexing */,IR(32, 1),IR(73, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5305,IR(0, 0),IR(10577, 39)/* StorageTexelBufferArrayDynamicIndexing */,IR(33, 1),IR(96, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5306,IR(0, 0),IR(10658, 37)/* UniformBufferArrayNonUniformIndexing */,IR(34, 1),IR(97, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5307,IR(0, 0),IR(10735, 36)/* SampledImageArrayNonUniformIndexing */,IR(35, 1),IR(97, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5308,IR(0, 0),IR(10810, 37)/* StorageBufferArrayNonUniformIndexing */,IR(36, 1),IR(97, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5309,IR(0, 0),IR(10887, 36)/* StorageImageArrayNonUniformIndexing */,IR(37, 1),IR(97, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5310,IR(0, 0),IR(10962, 39)/* InputAttachmentArrayNonUniformIndexing */,IR(38, 1),IR(98, 2),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5311,IR(0, 0),IR(11043, 42)/* UniformTexelBufferArrayNonUniformIndexing */,IR(39, 1),IR(100, 2),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5312,IR(0, 0),IR(11130, 42)/* StorageTexelBufferArrayNonUniformIndexing */,IR(40, 1),IR(102, 2),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5336,IR(0, 0),IR(7360, 27)/* RayTracingPositionFetchKHR */,IR(0, 0),IR(3, 1),IR(77, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5340,IR(0, 0),IR(4885, 13)/* RayTracingNV */,IR(0, 0),IR(3, 1),IR(26, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5341,IR(0, 0),IR(7307, 23)/* RayTracingMotionBlurNV */,IR(0, 0),IR(3, 1),IR(27, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5345,IR(0, 0),IR(11217, 18)/* VulkanMemoryModel */,IR(41, 1),IR(1, 0),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5346,IR(0, 0),IR(11256, 29)/* VulkanMemoryModelDeviceScope */,IR(42, 1),IR(1, 0),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5347,IR(0, 0),IR(4748, 31)/* PhysicalStorageBufferAddresses */,IR(43, 1),IR(3, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5350,IR(0, 0),IR(11351, 32)/* ComputeDerivativeGroupLinearKHR */,IR(44, 1),IR(3, 1),IR(73, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5353,IR(0, 0),IR(11414, 25)/* RayTracingProvisionalKHR */,IR(0, 0),IR(3, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5357,IR(0, 0),IR(11439, 20)/* CooperativeMatrixNV */,IR(0, 0),IR(3, 1),IR(79, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5363,IR(0, 0),IR(11459, 33)/* FragmentShaderSampleInterlockEXT */,IR(0, 0),IR(3, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5372,IR(0, 0),IR(11492, 38)/* FragmentShaderShadingRateInterlockEXT */,IR(0, 0),IR(3, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5373,IR(0, 0),IR(7675, 19)/* ShaderSMBuiltinsNV */,IR(0, 0),IR(3, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5378,IR(0, 0),IR(11530, 32)/* FragmentShaderPixelInterlockEXT */,IR(0, 0),IR(3, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5379,IR(0, 0),IR(11562, 25)/* DemoteToHelperInvocation */,IR(45, 1),IR(3, 1),IR(81, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5380,IR(0, 0),IR(11615, 23)/* DisplacementMicromapNV */,IR(0, 0),IR(3, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5381,IR(0, 0),IR(11638, 29)/* RayTracingOpacityMicromapEXT */,IR(0, 0),IR(3, 1),IR(83, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5383,IR(0, 0),IR(11667, 26)/* ShaderInvocationReorderNV */,IR(0, 0),IR(60, 1),IR(84, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5390,IR(0, 0),IR(11693, 18)/* BindlessTextureNV */,IR(0, 0),IR(1, 0),IR(85, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5391,IR(0, 0),IR(11711, 25)/* RayQueryPositionFetchKHR */,IR(0, 0),IR(3, 1),IR(77, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5394,IR(0, 0),IR(11736, 20)/* CooperativeVectorNV */,IR(0, 0),IR(1, 0),IR(86, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5404,IR(0, 0),IR(11756, 22)/* AtomicFloat16VectorNV */,IR(0, 0),IR(1, 0),IR(87, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5409,IR(0, 0),IR(7421, 33)/* RayTracingDisplacementMicromapNV */,IR(0, 0),IR(60, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5414,IR(0, 0),IR(11778, 18)/* RawAccessChainsNV */,IR(0, 0),IR(1, 0),IR(88, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5418,IR(0, 0),IR(7564, 28)/* RayTracingSpheresGeometryNV */,IR(0, 0),IR(1, 0),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5419,IR(0, 0),IR(7603, 39)/* RayTracingLinearSweptSpheresGeometryNV */,IR(0, 0),IR(1, 0),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5430,IR(0, 0),IR(11796, 30)/* CooperativeMatrixReductionsNV */,IR(0, 0),IR(1, 0),IR(89, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5431,IR(0, 0),IR(11826, 31)/* CooperativeMatrixConversionsNV */,IR(0, 0),IR(1, 0),IR(89, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5432,IR(0, 0),IR(11857, 40)/* CooperativeMatrixPerElementOperationsNV */,IR(0, 0),IR(1, 0),IR(89, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5433,IR(0, 0),IR(11897, 36)/* CooperativeMatrixTensorAddressingNV */,IR(0, 0),IR(1, 0),IR(89, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5434,IR(0, 0),IR(11933, 30)/* CooperativeMatrixBlockLoadsNV */,IR(0, 0),IR(1, 0),IR(89, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5435,IR(0, 0),IR(11963, 28)/* CooperativeVectorTrainingNV */,IR(0, 0),IR(1, 0),IR(86, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5437,IR(0, 0),IR(7849, 41)/* RayTracingClusterAccelerationStructureNV */,IR(0, 0),IR(60, 1),IR(31, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5439,IR(0, 0),IR(11991, 19)/* TensorAddressingNV */,IR(0, 0),IR(1, 0),IR(90, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5568,IR(0, 0),IR(12010, 21)/* SubgroupShuffleINTEL */,IR(0, 0),IR(1, 0),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5569,IR(0, 0),IR(12031, 27)/* SubgroupBufferBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5570,IR(0, 0),IR(12058, 26)/* SubgroupImageBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5579,IR(0, 0),IR(12084, 31)/* SubgroupImageMediaBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(92, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5582,IR(0, 0),IR(12115, 21)/* RoundToInfinityINTEL */,IR(0, 0),IR(1, 0),IR(93, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5583,IR(0, 0),IR(12136, 23)/* FloatingPointModeINTEL */,IR(0, 0),IR(1, 0),IR(93, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5584,IR(0, 0),IR(12159, 23)/* IntegerFunctions2INTEL */,IR(0, 0),IR(1, 0),IR(94, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5603,IR(0, 0),IR(12182, 22)/* FunctionPointersINTEL */,IR(0, 0),IR(1, 0),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5604,IR(0, 0),IR(12204, 24)/* IndirectReferencesINTEL */,IR(0, 0),IR(1, 0),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5606,IR(0, 0),IR(12228, 9)/* AsmINTEL */,IR(0, 0),IR(1, 0),IR(96, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5612,IR(0, 0),IR(12237, 23)/* AtomicFloat32MinMaxEXT */,IR(0, 0),IR(1, 0),IR(97, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5613,IR(0, 0),IR(12260, 23)/* AtomicFloat64MinMaxEXT */,IR(0, 0),IR(1, 0),IR(97, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5616,IR(0, 0),IR(12283, 23)/* AtomicFloat16MinMaxEXT */,IR(0, 0),IR(1, 0),IR(97, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5617,IR(0, 0),IR(12306, 19)/* VectorComputeINTEL */,IR(0, 0),IR(104, 1),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5619,IR(0, 0),IR(12325, 15)/* VectorAnyINTEL */,IR(0, 0),IR(1, 0),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5629,IR(0, 0),IR(12340, 16)/* ExpectAssumeKHR */,IR(0, 0),IR(1, 0),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5696,IR(0, 0),IR(12356, 33)/* SubgroupAvcMotionEstimationINTEL */,IR(0, 0),IR(1, 0),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5697,IR(0, 0),IR(12389, 38)/* SubgroupAvcMotionEstimationIntraINTEL */,IR(0, 0),IR(1, 0),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5698,IR(0, 0),IR(12427, 39)/* SubgroupAvcMotionEstimationChromaINTEL */,IR(0, 0),IR(1, 0),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5817,IR(0, 0),IR(12466, 25)/* VariableLengthArrayINTEL */,IR(0, 0),IR(1, 0),IR(101, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5821,IR(0, 0),IR(12491, 26)/* FunctionFloatControlINTEL */,IR(0, 0),IR(1, 0),IR(93, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5824,IR(0, 0),IR(12517, 26)/* FPGAMemoryAttributesINTEL */,IR(0, 0),IR(1, 0),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5837,IR(0, 0),IR(12543, 20)/* FPFastMathModeINTEL */,IR(0, 0),IR(0, 1),IR(103, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5844,IR(0, 0),IR(12563, 32)/* ArbitraryPrecisionIntegersINTEL */,IR(0, 0),IR(1, 0),IR(104, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5845,IR(0, 0),IR(12595, 37)/* ArbitraryPrecisionFloatingPointINTEL */,IR(0, 0),IR(1, 0),IR(105, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5886,IR(0, 0),IR(12632, 30)/* UnstructuredLoopControlsINTEL */,IR(0, 0),IR(1, 0),IR(106, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5888,IR(0, 0),IR(12662, 22)/* FPGALoopControlsINTEL */,IR(0, 0),IR(1, 0),IR(107, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5892,IR(0, 0),IR(12684, 22)/* KernelAttributesINTEL */,IR(0, 0),IR(1, 0),IR(108, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5897,IR(0, 0),IR(12706, 26)/* FPGAKernelAttributesINTEL */,IR(0, 0),IR(1, 0),IR(108, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5898,IR(0, 0),IR(12732, 24)/* FPGAMemoryAccessesINTEL */,IR(0, 0),IR(1, 0),IR(109, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5904,IR(0, 0),IR(12756, 27)/* FPGAClusterAttributesINTEL */,IR(0, 0),IR(1, 0),IR(110, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5906,IR(0, 0),IR(12783, 14)/* LoopFuseINTEL */,IR(0, 0),IR(1, 0),IR(111, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5908,IR(0, 0),IR(12797, 20)/* FPGADSPControlINTEL */,IR(0, 0),IR(1, 0),IR(112, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5910,IR(0, 0),IR(12817, 26)/* MemoryAccessAliasingINTEL */,IR(0, 0),IR(1, 0),IR(113, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5916,IR(0, 0),IR(12843, 40)/* FPGAInvocationPipeliningAttributesINTEL */,IR(0, 0),IR(1, 0),IR(114, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5920,IR(0, 0),IR(12883, 24)/* FPGABufferLocationINTEL */,IR(0, 0),IR(1, 0),IR(115, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5922,IR(0, 0),IR(12907, 34)/* ArbitraryPrecisionFixedPointINTEL */,IR(0, 0),IR(1, 0),IR(116, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5935,IR(0, 0),IR(12941, 23)/* USMStorageClassesINTEL */,IR(0, 0),IR(1, 0),IR(117, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5939,IR(0, 0),IR(12964, 29)/* RuntimeAlignedAttributeINTEL */,IR(0, 0),IR(1, 0),IR(118, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5943,IR(0, 0),IR(12993, 13)/* IOPipesINTEL */,IR(0, 0),IR(1, 0),IR(119, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5945,IR(0, 0),IR(13006, 19)/* BlockingPipesINTEL */,IR(0, 0),IR(1, 0),IR(120, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5948,IR(0, 0),IR(13025, 13)/* FPGARegINTEL */,IR(0, 0),IR(1, 0),IR(121, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6016,IR(0, 0),IR(13038, 19)/* DotProductInputAll */,IR(46, 1),IR(1, 0),IR(122, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6017,IR(0, 0),IR(13079, 22)/* DotProductInput4x8Bit */,IR(47, 1),IR(105, 1),IR(122, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6018,IR(0, 0),IR(13126, 28)/* DotProductInput4x8BitPacked */,IR(48, 1),IR(1, 0),IR(122, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6019,IR(0, 0),IR(13185, 11)/* DotProduct */,IR(49, 1),IR(1, 0),IR(122, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6020,IR(0, 0),IR(7902, 15)/* RayCullMaskKHR */,IR(0, 0),IR(1, 0),IR(32, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6022,IR(0, 0),IR(9105, 21)/* CooperativeMatrixKHR */,IR(0, 0),IR(1, 0),IR(123, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6024,IR(0, 0),IR(13210, 24)/* ReplicatedCompositesEXT */,IR(0, 0),IR(1, 0),IR(124, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6025,IR(0, 0),IR(13234, 16)/* BitInstructions */,IR(0, 0),IR(1, 0),IR(125, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6026,IR(0, 0),IR(13250, 25)/* GroupNonUniformRotateKHR */,IR(0, 0),IR(76, 1),IR(126, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6029,IR(0, 0),IR(13275, 15)/* FloatControls2 */,IR(0, 0),IR(1, 0),IR(127, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6033,IR(0, 0),IR(13290, 20)/* AtomicFloat32AddEXT */,IR(0, 0),IR(1, 0),IR(128, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6034,IR(0, 0),IR(13310, 20)/* AtomicFloat64AddEXT */,IR(0, 0),IR(1, 0),IR(128, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6089,IR(0, 0),IR(13330, 20)/* LongCompositesINTEL */,IR(0, 0),IR(1, 0),IR(129, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6094,IR(0, 0),IR(13350, 11)/* OptNoneEXT */,IR(50, 1),IR(1, 0),IR(130, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6095,IR(0, 0),IR(13374, 20)/* AtomicFloat16AddEXT */,IR(0, 0),IR(1, 0),IR(132, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6114,IR(0, 0),IR(13394, 21)/* DebugInfoModuleINTEL */,IR(0, 0),IR(1, 0),IR(133, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6115,IR(0, 0),IR(13415, 24)/* BFloat16ConversionINTEL */,IR(0, 0),IR(1, 0),IR(134, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6141,IR(0, 0),IR(13439, 18)/* SplitBarrierINTEL */,IR(0, 0),IR(1, 0),IR(135, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6144,IR(0, 0),IR(13457, 19)/* ArithmeticFenceEXT */,IR(0, 0),IR(1, 0),IR(136, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6150,IR(0, 0),IR(13476, 29)/* FPGAClusterAttributesV2INTEL */,IR(0, 0),IR(106, 1),IR(110, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6161,IR(0, 0),IR(13505, 28)/* FPGAKernelAttributesv2INTEL */,IR(0, 0),IR(107, 1),IR(108, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6162,IR(0, 0),IR(13533, 18)/* TaskSequenceINTEL */,IR(0, 0),IR(1, 0),IR(137, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6169,IR(0, 0),IR(13551, 16)/* FPMaxErrorINTEL */,IR(0, 0),IR(1, 0),IR(138, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6171,IR(0, 0),IR(13567, 24)/* FPGALatencyControlINTEL */,IR(0, 0),IR(1, 0),IR(139, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6174,IR(0, 0),IR(13591, 28)/* FPGAArgumentInterfacesINTEL */,IR(0, 0),IR(1, 0),IR(140, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6187,IR(0, 0),IR(13619, 30)/* GlobalVariableHostAccessINTEL */,IR(0, 0),IR(1, 0),IR(141, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6189,IR(0, 0),IR(13649, 35)/* GlobalVariableFPGADecorationsINTEL */,IR(0, 0),IR(1, 0),IR(142, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6220,IR(0, 0),IR(13684, 28)/* SubgroupBufferPrefetchINTEL */,IR(0, 0),IR(1, 0),IR(143, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6228,IR(0, 0),IR(13712, 23)/* Subgroup2DBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(144, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6229,IR(0, 0),IR(13735, 30)/* Subgroup2DBlockTransformINTEL */,IR(0, 0),IR(108, 1),IR(144, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6230,IR(0, 0),IR(13765, 30)/* Subgroup2DBlockTransposeINTEL */,IR(0, 0),IR(108, 1),IR(144, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6236,IR(0, 0),IR(13795, 38)/* SubgroupMatrixMultiplyAccumulateINTEL */,IR(0, 0),IR(1, 0),IR(145, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6241,IR(0, 0),IR(13833, 28)/* TernaryBitwiseFunctionINTEL */,IR(0, 0),IR(1, 0),IR(146, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6243,IR(0, 0),IR(13861, 32)/* UntypedVariableLengthArrayINTEL */,IR(0, 0),IR(109, 2),IR(101, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6245,IR(0, 0),IR(13893, 21)/* SpecConditionalINTEL */,IR(0, 0),IR(1, 0),IR(147, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6246,IR(0, 0),IR(13914, 22)/* FunctionVariantsINTEL */,IR(0, 0),IR(111, 1),IR(147, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6400,IR(0, 0),IR(13936, 26)/* GroupUniformArithmeticKHR */,IR(0, 0),IR(1, 0),IR(148, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6425,IR(0, 0),IR(13962, 27)/* TensorFloat32RoundingINTEL */,IR(0, 0),IR(1, 0),IR(149, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6427,IR(0, 0),IR(13989, 25)/* MaskedGatherScatterINTEL */,IR(0, 0),IR(1, 0),IR(150, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6441,IR(0, 0),IR(14014, 19)/* CacheControlsINTEL */,IR(0, 0),IR(1, 0),IR(151, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6460,IR(0, 0),IR(14033, 20)/* RegisterLimitsINTEL */,IR(0, 0),IR(1, 0),IR(152, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6528,IR(0, 0),IR(14053, 20)/* BindlessImagesINTEL */,IR(0, 0),IR(1, 0),IR(153, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {0,IR(0, 0),IR(14073, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(14085, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(14093, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {3,IR(0, 0),IR(14101, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(14107, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(14114, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(14125, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(14134, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(14147, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(14153, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(14163, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(14169, 15)/* ImportedModule */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {1,IR(0, 0),IR(14184, 20)/* ImportedDeclaration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {0,IR(0, 0),IR(14204, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(14209, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(14225, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(14239, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(14252, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(14264, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(14281, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(14293, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(14308, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(14321, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(14336, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(14354, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(14371, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(14392, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(14412, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(14432, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {16384,IR(0, 0),IR(14448, 16)/* FlagIsEnumClass */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {32768,IR(0, 0),IR(14464, 20)/* FlagTypePassByValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {65536,IR(0, 0),IR(14484, 24)/* FlagTypePassByReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(14508, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {1,IR(0, 0),IR(14514, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {2,IR(0, 0),IR(14519, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {3,IR(0, 1),IR(14558, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {4,IR(1, 2),IR(14569, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {5,IR(0, 0),IR(14578, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {6,IR(0, 0),IR(14583, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {7,IR(0, 0),IR(14590, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {8,IR(0, 1),IR(14601, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {9,IR(1, 2),IR(14608, 9)/* Fragment */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {0,IR(0, 0),IR(14617, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(14627, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(14640, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {3,IR(0, 0),IR(14653, 11)/* AtomicType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(14664, 10)/* Float16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1,IR(0, 0),IR(14674, 10)/* Float32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {2,IR(0, 0),IR(14684, 10)/* Float64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {3,IR(0, 0),IR(14694, 13)/* SignedInt8NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {4,IR(0, 0),IR(14707, 14)/* SignedInt16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {5,IR(0, 0),IR(14721, 14)/* SignedInt32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {6,IR(0, 0),IR(14735, 14)/* SignedInt64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {7,IR(0, 0),IR(14749, 15)/* UnsignedInt8NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {8,IR(0, 0),IR(14764, 16)/* UnsignedInt16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {9,IR(0, 0),IR(14780, 16)/* UnsignedInt32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {10,IR(0, 0),IR(14796, 16)/* UnsignedInt64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491000,IR(0, 0),IR(14812, 19)/* SignedInt8PackedNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491001,IR(0, 0),IR(14831, 21)/* UnsignedInt8PackedNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491002,IR(0, 0),IR(14852, 12)/* FloatE4M3NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491003,IR(0, 0),IR(14864, 12)/* FloatE5M2NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {0,IR(0, 0),IR(14876, 12)/* RowMajorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {1,IR(0, 0),IR(14888, 15)/* ColumnMajorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {4202,IR(0, 0),IR(14903, 25)/* RowBlockedInterleavedARM */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {4203,IR(0, 0),IR(14928, 28)/* ColumnBlockedInterleavedARM */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {0,IR(0, 0),IR(14956, 8)/* NoneKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {1,IR(0, 0),IR(14964, 27)/* MatrixASignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {2,IR(0, 0),IR(14991, 27)/* MatrixBSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {4,IR(0, 0),IR(15018, 27)/* MatrixCSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {8,IR(0, 0),IR(15045, 32)/* MatrixResultSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {16,IR(0, 0),IR(15077, 26)/* SaturatingAccumulationKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {1,IR(0, 0),IR(15103, 4)/* Row */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {2,IR(0, 0),IR(15107, 7)/* Column */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {4,IR(0, 0),IR(15114, 4)/* 2x2 */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {0,IR(0, 0),IR(15118, 11)/* MatrixAKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {1,IR(0, 0),IR(15129, 11)/* MatrixBKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {2,IR(0, 0),IR(15140, 21)/* MatrixAccumulatorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {0,IR(0, 0),IR(15161, 11)/* RowMajorNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {1,IR(0, 0),IR(15172, 14)/* ColumnMajorNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {2,IR(0, 0),IR(15186, 21)/* InferencingOptimalNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {3,IR(0, 0),IR(15207, 18)/* TrainingOptimalNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {0,IR(0, 0),IR(14073, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(14085, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(14093, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(14101, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(14107, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(14114, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(14125, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {8,IR(0, 0),IR(14134, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(14147, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(14153, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(14163, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(14204, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(14209, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(14225, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(14239, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(14252, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(14264, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(14281, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(14293, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(14308, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(14321, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(14336, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(14354, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(14371, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(14392, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(14412, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(14432, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(14508, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {1,IR(0, 0),IR(14514, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {2,IR(0, 0),IR(14519, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {3,IR(0, 1),IR(14558, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {4,IR(1, 2),IR(14569, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {5,IR(0, 0),IR(14578, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {6,IR(0, 0),IR(14583, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {7,IR(0, 0),IR(14590, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {8,IR(0, 1),IR(14601, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {0,IR(0, 0),IR(14617, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(14627, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(14640, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(15225, 17)/* RelaxedPrecision */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {1,IR(0, 1),IR(15242, 7)/* SpecId */,IR(0, 0),IR(112, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {2,IR(0, 0),IR(15249, 6)/* Block */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {3,IR(0, 0),IR(15255, 12)/* BufferBlock */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),SPV_SPIRV_VERSION_WORD(1,3)}, // SPV_OPERAND_TYPE_DECORATION
  {4,IR(0, 0),IR(15267, 9)/* RowMajor */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5,IR(0, 0),IR(15276, 9)/* ColMajor */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6,IR(0, 1),IR(15285, 12)/* ArrayStride */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {7,IR(0, 1),IR(15297, 13)/* MatrixStride */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {8,IR(0, 0),IR(15310, 11)/* GLSLShared */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {9,IR(0, 0),IR(15321, 11)/* GLSLPacked */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {10,IR(0, 0),IR(15332, 8)/* CPacked */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {11,IR(3, 1),IR(15366, 8)/* BuiltIn */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {13,IR(0, 0),IR(15374, 14)/* NoPerspective */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {14,IR(0, 0),IR(15388, 5)/* Flat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {15,IR(0, 0),IR(15393, 6)/* Patch */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {16,IR(0, 0),IR(15399, 9)/* Centroid */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {17,IR(0, 0),IR(15408, 7)/* Sample */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {18,IR(0, 0),IR(15415, 10)/* Invariant */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {19,IR(0, 0),IR(15425, 9)/* Restrict */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {20,IR(0, 0),IR(15434, 8)/* Aliased */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {21,IR(0, 0),IR(15442, 9)/* Volatile */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {22,IR(0, 0),IR(15451, 9)/* Constant */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {23,IR(0, 0),IR(15460, 9)/* Coherent */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {24,IR(0, 0),IR(15469, 12)/* NonWritable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {25,IR(0, 0),IR(15481, 12)/* NonReadable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {26,IR(0, 0),IR(15493, 8)/* Uniform */,IR(0, 0),IR(114, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {27,IR(4, 1),IR(15527, 10)/* UniformId */,IR(0, 0),IR(114, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {28,IR(0, 0),IR(15537, 20)/* SaturatedConversion */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {29,IR(0, 1),IR(15557, 7)/* Stream */,IR(0, 0),IR(116, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {30,IR(0, 1),IR(15564, 9)/* Location */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {31,IR(0, 1),IR(15573, 10)/* Component */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {32,IR(0, 1),IR(15583, 6)/* Index */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {33,IR(0, 1),IR(15589, 8)/* Binding */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {34,IR(0, 1),IR(15597, 14)/* DescriptorSet */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {35,IR(0, 1),IR(15611, 7)/* Offset */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {36,IR(0, 1),IR(15618, 10)/* XfbBuffer */,IR(0, 0),IR(117, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {37,IR(0, 1),IR(15628, 10)/* XfbStride */,IR(0, 0),IR(117, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {38,IR(5, 1),IR(15684, 14)/* FuncParamAttr */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {39,IR(6, 1),IR(15732, 15)/* FPRoundingMode */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {40,IR(7, 1),IR(15782, 15)/* FPFastMathMode */,IR(0, 0),IR(118, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {41,IR(8, 2),IR(15859, 18)/* LinkageAttributes */,IR(0, 0),IR(120, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {42,IR(0, 0),IR(15877, 14)/* NoContraction */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {43,IR(0, 1),IR(15891, 21)/* InputAttachmentIndex */,IR(0, 0),IR(95, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {44,IR(0, 1),IR(15912, 10)/* Alignment */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {45,IR(0, 1),IR(15922, 14)/* MaxByteOffset */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {46,IR(10, 1),IR(15956, 12)/* AlignmentId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {47,IR(10, 1),IR(15968, 16)/* MaxByteOffsetId */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4216,IR(0, 0),IR(15984, 44)/* SaturatedToLargestFloat8NormalConversionEXT */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4469,IR(0, 0),IR(16028, 13)/* NoSignedWrap */,IR(0, 0),IR(1, 0),IR(154, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4470,IR(0, 0),IR(16041, 15)/* NoUnsignedWrap */,IR(0, 0),IR(1, 0),IR(154, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4487,IR(0, 0),IR(16056, 18)/* WeightTextureQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4488,IR(0, 0),IR(16074, 22)/* BlockMatchTextureQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4499,IR(0, 0),IR(16096, 22)/* BlockMatchSamplerQCOM */,IR(0, 0),IR(1, 0),IR(55, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4999,IR(0, 0),IR(16118, 18)/* ExplicitInterpAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5019,IR(10, 1),IR(16136, 32)/* NodeSharesPayloadLimitsWithAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5020,IR(10, 1),IR(16168, 20)/* NodeMaxPayloadsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5078,IR(0, 0),IR(16188, 23)/* TrackFinishWritingAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5091,IR(10, 1),IR(16211, 20)/* PayloadNodeNameAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5098,IR(10, 1),IR(16231, 25)/* PayloadNodeBaseIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5099,IR(0, 0),IR(16256, 27)/* PayloadNodeSparseArrayAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5100,IR(10, 1),IR(16283, 25)/* PayloadNodeArraySizeAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5105,IR(0, 0),IR(16308, 28)/* PayloadDispatchIndirectAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5248,IR(0, 0),IR(16336, 19)/* OverrideCoverageNV */,IR(0, 0),IR(122, 1),IR(66, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5250,IR(0, 0),IR(16355, 14)/* PassthroughNV */,IR(0, 0),IR(123, 1),IR(67, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5252,IR(0, 0),IR(16369, 19)/* ViewportRelativeNV */,IR(0, 0),IR(94, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5256,IR(0, 1),IR(16388, 28)/* SecondaryViewportRelativeNV */,IR(0, 0),IR(46, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5271,IR(0, 0),IR(16416, 16)/* PerPrimitiveEXT */,IR(51, 1),IR(124, 2),IR(155, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5272,IR(0, 0),IR(16447, 10)/* PerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5273,IR(0, 0),IR(16457, 10)/* PerTaskNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5285,IR(0, 0),IR(16467, 13)/* PerVertexKHR */,IR(52, 1),IR(51, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5300,IR(0, 0),IR(16492, 11)/* NonUniform */,IR(53, 1),IR(97, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5355,IR(0, 0),IR(16517, 16)/* RestrictPointer */,IR(54, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5356,IR(0, 0),IR(16552, 15)/* AliasedPointer */,IR(55, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5386,IR(0, 0),IR(16585, 30)/* HitObjectShaderRecordBufferNV */,IR(0, 0),IR(126, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5398,IR(0, 0),IR(16615, 18)/* BindlessSamplerNV */,IR(0, 0),IR(127, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5399,IR(0, 0),IR(16633, 16)/* BindlessImageNV */,IR(0, 0),IR(127, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5400,IR(0, 0),IR(16649, 15)/* BoundSamplerNV */,IR(0, 0),IR(127, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5401,IR(0, 0),IR(16664, 13)/* BoundImageNV */,IR(0, 0),IR(127, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5599,IR(0, 1),IR(16677, 14)/* SIMTCallINTEL */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5602,IR(0, 0),IR(16691, 26)/* ReferencedIndirectlyINTEL */,IR(0, 0),IR(129, 1),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5607,IR(11, 1),IR(16717, 13)/* ClobberINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5608,IR(0, 0),IR(16730, 17)/* SideEffectsINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5624,IR(0, 0),IR(16747, 27)/* VectorComputeVariableINTEL */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5625,IR(0, 1),IR(16774, 21)/* FuncParamIOKindINTEL */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5626,IR(0, 0),IR(16795, 27)/* VectorComputeFunctionINTEL */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5627,IR(0, 0),IR(16822, 15)/* StackCallINTEL */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5628,IR(0, 1),IR(16837, 26)/* GlobalVariableOffsetINTEL */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5634,IR(10, 1),IR(16863, 14)/* CounterBuffer */,IR(56, 1),IR(1, 0),IR(157, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5635,IR(11, 1),IR(16901, 13)/* UserSemantic */,IR(57, 1),IR(1, 0),IR(157, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5636,IR(11, 1),IR(16933, 15)/* UserTypeGOOGLE */,IR(0, 0),IR(1, 0),IR(158, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5822,IR(12, 2),IR(16948, 26)/* FunctionRoundingModeINTEL */,IR(0, 0),IR(131, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5823,IR(14, 2),IR(17005, 24)/* FunctionDenormModeINTEL */,IR(0, 0),IR(131, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5825,IR(0, 0),IR(17029, 14)/* RegisterINTEL */,IR(0, 0),IR(132, 1),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5826,IR(11, 1),IR(17043, 12)/* MemoryINTEL */,IR(0, 0),IR(132, 1),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5827,IR(0, 1),IR(17055, 14)/* NumbanksINTEL */,IR(0, 0),IR(132, 1),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5828,IR(0, 1),IR(17069, 15)/* BankwidthINTEL */,IR(0, 0),IR(132, 1),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5829,IR(0, 1),IR(17084, 22)/* MaxPrivateCopiesINTEL */,IR(0, 0),IR(132, 1),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5830,IR(0, 0),IR(17106, 16)/* SinglepumpINTEL */,IR(0, 0),IR(132, 1),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5831,IR(0, 0),IR(17122, 16)/* DoublepumpINTEL */,IR(0, 0),IR(132, 1),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5832,IR(0, 1),IR(17138, 19)/* MaxReplicatesINTEL */,IR(0, 0),IR(132, 1),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5833,IR(0, 0),IR(17157, 20)/* SimpleDualPortINTEL */,IR(0, 0),IR(132, 1),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5834,IR(16, 2),IR(17177, 11)/* MergeINTEL */,IR(0, 0),IR(132, 1),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5835,IR(18, 1),IR(17230, 14)/* BankBitsINTEL */,IR(0, 0),IR(132, 1),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5836,IR(0, 1),IR(17244, 20)/* ForcePow2DepthINTEL */,IR(0, 0),IR(132, 1),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5883,IR(0, 1),IR(17264, 16)/* StridesizeINTEL */,IR(0, 0),IR(132, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5884,IR(0, 1),IR(17280, 14)/* WordsizeINTEL */,IR(0, 0),IR(132, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5885,IR(0, 0),IR(17294, 18)/* TrueDualPortINTEL */,IR(0, 0),IR(132, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5899,IR(0, 0),IR(17312, 19)/* BurstCoalesceINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5900,IR(0, 1),IR(17331, 15)/* CacheSizeINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5901,IR(0, 0),IR(17346, 28)/* DontStaticallyCoalesceINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5902,IR(0, 1),IR(17374, 14)/* PrefetchINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5905,IR(0, 0),IR(17388, 17)/* StallEnableINTEL */,IR(0, 0),IR(106, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5907,IR(0, 0),IR(17405, 25)/* FuseLoopsInFunctionINTEL */,IR(0, 0),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5909,IR(1, 2),IR(17430, 19)/* MathOpDSPModeINTEL */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5914,IR(10, 1),IR(17449, 16)/* AliasScopeINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5915,IR(10, 1),IR(17465, 13)/* NoAliasINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5917,IR(0, 1),IR(17478, 24)/* InitiationIntervalINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5918,IR(0, 1),IR(17502, 20)/* MaxConcurrencyINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5919,IR(0, 1),IR(17522, 20)/* PipelineEnableINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5921,IR(0, 1),IR(17542, 20)/* BufferLocationINTEL */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5944,IR(0, 1),IR(17562, 19)/* IOPipeStorageINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6080,IR(19, 2),IR(17615, 31)/* FunctionFloatingPointModeINTEL */,IR(0, 0),IR(131, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6085,IR(0, 0),IR(17646, 25)/* SingleElementVectorINTEL */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6087,IR(0, 0),IR(17671, 35)/* VectorComputeCallableFunctionINTEL */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6140,IR(0, 0),IR(17706, 18)/* MediaBlockIOINTEL */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6151,IR(0, 0),IR(17724, 15)/* StallFreeINTEL */,IR(0, 0),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6170,IR(21, 1),IR(17770, 26)/* FPMaxErrorDecorationINTEL */,IR(0, 0),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6172,IR(0, 1),IR(17796, 25)/* LatencyControlLabelINTEL */,IR(0, 0),IR(142, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6173,IR(22, 3),IR(17821, 30)/* LatencyControlConstraintINTEL */,IR(0, 0),IR(142, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6175,IR(0, 0),IR(17851, 27)/* ConduitKernelArgumentINTEL */,IR(0, 0),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6176,IR(0, 0),IR(17878, 31)/* RegisterMapKernelArgumentINTEL */,IR(0, 0),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6177,IR(0, 1),IR(17909, 33)/* MMHostInterfaceAddressWidthINTEL */,IR(0, 0),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6178,IR(0, 1),IR(17942, 30)/* MMHostInterfaceDataWidthINTEL */,IR(0, 0),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6179,IR(0, 1),IR(17972, 28)/* MMHostInterfaceLatencyINTEL */,IR(0, 0),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6180,IR(25, 1),IR(18034, 34)/* MMHostInterfaceReadWriteModeINTEL */,IR(0, 0),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6181,IR(0, 1),IR(18068, 29)/* MMHostInterfaceMaxBurstINTEL */,IR(0, 0),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6182,IR(0, 1),IR(18097, 32)/* MMHostInterfaceWaitRequestINTEL */,IR(0, 0),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6183,IR(0, 0),IR(18129, 26)/* StableKernelArgumentINTEL */,IR(0, 0),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6188,IR(26, 2),IR(18194, 16)/* HostAccessINTEL */,IR(0, 0),IR(144, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6190,IR(28, 1),IR(18257, 14)/* InitModeINTEL */,IR(0, 0),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6191,IR(0, 1),IR(18271, 28)/* ImplementInRegisterMapINTEL */,IR(0, 0),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6247,IR(10, 1),IR(18299, 17)/* ConditionalINTEL */,IR(0, 0),IR(111, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6442,IR(29, 2),IR(18352, 22)/* CacheControlLoadINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6443,IR(31, 2),IR(18411, 23)/* CacheControlStoreINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {0,IR(0, 0),IR(18434, 3)/* 1D */,IR(0, 0),IR(72, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {1,IR(0, 0),IR(18437, 3)/* 2D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {2,IR(0, 0),IR(18440, 3)/* 3D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {3,IR(0, 0),IR(18443, 5)/* Cube */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {4,IR(0, 0),IR(18448, 5)/* Rect */,IR(0, 0),IR(71, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {5,IR(0, 0),IR(18453, 7)/* Buffer */,IR(0, 0),IR(73, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {6,IR(0, 0),IR(18460, 12)/* SubpassData */,IR(0, 0),IR(95, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {4173,IR(0, 0),IR(18472, 17)/* TileImageDataEXT */,IR(0, 0),IR(147, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {0,IR(0, 1),IR(18489, 12)/* Invocations */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {1,IR(0, 0),IR(18501, 13)/* SpacingEqual */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {2,IR(0, 0),IR(18514, 22)/* SpacingFractionalEven */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {3,IR(0, 0),IR(18536, 21)/* SpacingFractionalOdd */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4,IR(0, 0),IR(18557, 14)/* VertexOrderCw */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5,IR(0, 0),IR(18571, 15)/* VertexOrderCcw */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6,IR(0, 0),IR(18586, 19)/* PixelCenterInteger */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {7,IR(0, 0),IR(18605, 16)/* OriginUpperLeft */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {8,IR(0, 0),IR(18621, 16)/* OriginLowerLeft */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {9,IR(0, 0),IR(18637, 19)/* EarlyFragmentTests */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {10,IR(0, 0),IR(18656, 10)/* PointMode */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {11,IR(0, 0),IR(18666, 4)/* Xfb */,IR(0, 0),IR(117, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {12,IR(0, 0),IR(18670, 15)/* DepthReplacing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {14,IR(0, 0),IR(18685, 13)/* DepthGreater */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {15,IR(0, 0),IR(18698, 10)/* DepthLess */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {16,IR(0, 0),IR(18708, 15)/* DepthUnchanged */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {17,IR(22, 3),IR(18723, 10)/* LocalSize */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {18,IR(22, 3),IR(18733, 14)/* LocalSizeHint */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {19,IR(0, 0),IR(18747, 12)/* InputPoints */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {20,IR(0, 0),IR(18759, 11)/* InputLines */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {21,IR(0, 0),IR(18770, 20)/* InputLinesAdjacency */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {22,IR(0, 0),IR(18790, 10)/* Triangles */,IR(0, 0),IR(12, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {23,IR(0, 0),IR(18800, 24)/* InputTrianglesAdjacency */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {24,IR(0, 0),IR(18824, 6)/* Quads */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {25,IR(0, 0),IR(18830, 9)/* Isolines */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {26,IR(0, 1),IR(18839, 15)/* OutputVertices */,IR(0, 0),IR(148, 4),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {27,IR(0, 0),IR(18854, 13)/* OutputPoints */,IR(0, 0),IR(152, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {28,IR(0, 0),IR(18867, 16)/* OutputLineStrip */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {29,IR(0, 0),IR(18883, 20)/* OutputTriangleStrip */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {30,IR(0, 1),IR(18903, 12)/* VecTypeHint */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {31,IR(0, 0),IR(18915, 15)/* ContractionOff */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {33,IR(0, 0),IR(18930, 12)/* Initializer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {34,IR(0, 0),IR(18942, 10)/* Finalizer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {35,IR(0, 1),IR(5382, 13)/* SubgroupSize */,IR(0, 0),IR(155, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {36,IR(0, 1),IR(18952, 22)/* SubgroupsPerWorkgroup */,IR(0, 0),IR(155, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {37,IR(10, 1),IR(18974, 24)/* SubgroupsPerWorkgroupId */,IR(0, 0),IR(155, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {38,IR(33, 3),IR(18998, 12)/* LocalSizeId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {39,IR(33, 3),IR(19010, 16)/* LocalSizeHintId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4169,IR(0, 0),IR(19026, 34)/* NonCoherentColorAttachmentReadEXT */,IR(0, 0),IR(147, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4170,IR(0, 0),IR(19060, 34)/* NonCoherentDepthAttachmentReadEXT */,IR(0, 0),IR(156, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4171,IR(0, 0),IR(19094, 36)/* NonCoherentStencilAttachmentReadEXT */,IR(0, 0),IR(157, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4421,IR(0, 0),IR(19130, 30)/* SubgroupUniformControlFlowKHR */,IR(0, 0),IR(3, 1),IR(159, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4446,IR(0, 0),IR(19160, 18)/* PostDepthCoverage */,IR(0, 0),IR(158, 1),IR(45, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4459,IR(0, 1),IR(9581, 15)/* DenormPreserve */,IR(0, 0),IR(159, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4460,IR(0, 1),IR(9596, 18)/* DenormFlushToZero */,IR(0, 0),IR(160, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4461,IR(0, 1),IR(9614, 25)/* SignedZeroInfNanPreserve */,IR(0, 0),IR(161, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4462,IR(0, 1),IR(9639, 16)/* RoundingModeRTE */,IR(0, 0),IR(162, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4463,IR(0, 1),IR(9655, 16)/* RoundingModeRTZ */,IR(0, 0),IR(163, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4489,IR(0, 0),IR(19178, 34)/* NonCoherentTileAttachmentReadQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4490,IR(22, 3),IR(19212, 20)/* TileShadingRateQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5017,IR(0, 0),IR(19232, 29)/* EarlyAndLateFragmentTestsAMD */,IR(0, 0),IR(3, 1),IR(160, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5027,IR(0, 0),IR(19261, 23)/* StencilRefReplacingEXT */,IR(0, 0),IR(42, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5069,IR(0, 0),IR(19284, 15)/* CoalescingAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5070,IR(10, 1),IR(19299, 15)/* IsApiEntryAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5071,IR(10, 1),IR(19314, 21)/* MaxNodeRecursionAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5072,IR(33, 3),IR(19335, 24)/* StaticNumWorkgroupsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5073,IR(10, 1),IR(6275, 16)/* ShaderIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5077,IR(33, 3),IR(19359, 21)/* MaxNumWorkgroupsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5079,IR(0, 0),IR(19380, 28)/* StencilRefUnchangedFrontAMD */,IR(0, 0),IR(42, 1),IR(161, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5080,IR(0, 0),IR(19408, 26)/* StencilRefGreaterFrontAMD */,IR(0, 0),IR(42, 1),IR(161, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5081,IR(0, 0),IR(19434, 23)/* StencilRefLessFrontAMD */,IR(0, 0),IR(42, 1),IR(161, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5082,IR(0, 0),IR(19457, 27)/* StencilRefUnchangedBackAMD */,IR(0, 0),IR(42, 1),IR(161, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5083,IR(0, 0),IR(19484, 25)/* StencilRefGreaterBackAMD */,IR(0, 0),IR(42, 1),IR(161, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5084,IR(0, 0),IR(19509, 22)/* StencilRefLessBackAMD */,IR(0, 0),IR(42, 1),IR(161, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5088,IR(0, 0),IR(19531, 19)/* QuadDerivativesKHR */,IR(0, 0),IR(164, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5089,IR(0, 0),IR(19550, 20)/* RequireFullQuadsKHR */,IR(0, 0),IR(164, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5102,IR(36, 2),IR(19570, 20)/* SharesInputWithAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5269,IR(0, 0),IR(19590, 15)/* OutputLinesEXT */,IR(58, 1),IR(124, 2),IR(155, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5270,IR(0, 1),IR(19619, 20)/* OutputPrimitivesEXT */,IR(59, 1),IR(124, 2),IR(155, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5289,IR(0, 0),IR(19658, 24)/* DerivativeGroupQuadsKHR */,IR(60, 1),IR(165, 1),IR(73, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5290,IR(0, 0),IR(19705, 25)/* DerivativeGroupLinearKHR */,IR(61, 1),IR(166, 1),IR(73, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5298,IR(0, 0),IR(19754, 19)/* OutputTrianglesEXT */,IR(62, 1),IR(124, 2),IR(155, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5366,IR(0, 0),IR(19791, 25)/* PixelInterlockOrderedEXT */,IR(0, 0),IR(167, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5367,IR(0, 0),IR(19816, 27)/* PixelInterlockUnorderedEXT */,IR(0, 0),IR(167, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5368,IR(0, 0),IR(19843, 26)/* SampleInterlockOrderedEXT */,IR(0, 0),IR(168, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5369,IR(0, 0),IR(19869, 28)/* SampleInterlockUnorderedEXT */,IR(0, 0),IR(168, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5370,IR(0, 0),IR(19897, 31)/* ShadingRateInterlockOrderedEXT */,IR(0, 0),IR(169, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5371,IR(0, 0),IR(19928, 33)/* ShadingRateInterlockUnorderedEXT */,IR(0, 0),IR(169, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5618,IR(0, 1),IR(19961, 27)/* SharedLocalMemorySizeINTEL */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5620,IR(0, 1),IR(19988, 21)/* RoundingModeRTPINTEL */,IR(0, 0),IR(170, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5621,IR(0, 1),IR(20009, 21)/* RoundingModeRTNINTEL */,IR(0, 0),IR(170, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5622,IR(0, 1),IR(20030, 26)/* FloatingPointModeALTINTEL */,IR(0, 0),IR(170, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5623,IR(0, 1),IR(20056, 27)/* FloatingPointModeIEEEINTEL */,IR(0, 0),IR(170, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5893,IR(22, 3),IR(20083, 22)/* MaxWorkgroupSizeINTEL */,IR(0, 0),IR(171, 1),IR(108, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5894,IR(0, 1),IR(20105, 16)/* MaxWorkDimINTEL */,IR(0, 0),IR(171, 1),IR(108, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5895,IR(0, 0),IR(20121, 20)/* NoGlobalOffsetINTEL */,IR(0, 0),IR(171, 1),IR(108, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5896,IR(0, 1),IR(20141, 22)/* NumSIMDWorkitemsINTEL */,IR(0, 0),IR(107, 1),IR(108, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5903,IR(0, 1),IR(20163, 28)/* SchedulerTargetFmaxMhzINTEL */,IR(0, 0),IR(107, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6023,IR(0, 0),IR(20191, 24)/* MaximallyReconvergesKHR */,IR(0, 0),IR(3, 1),IR(163, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6028,IR(36, 2),IR(20215, 18)/* FPFastMathDefault */,IR(0, 0),IR(172, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6154,IR(0, 1),IR(20233, 24)/* StreamingInterfaceINTEL */,IR(0, 0),IR(107, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6160,IR(0, 1),IR(20257, 26)/* RegisterMapInterfaceINTEL */,IR(0, 0),IR(173, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6417,IR(0, 1),IR(20283, 23)/* NamedBarrierCountINTEL */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6461,IR(0, 1),IR(20306, 22)/* MaximumRegistersINTEL */,IR(0, 0),IR(174, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6462,IR(10, 1),IR(20328, 24)/* MaximumRegistersIdINTEL */,IR(0, 0),IR(174, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6463,IR(38, 1),IR(20403, 27)/* NamedMaximumRegistersINTEL */,IR(0, 0),IR(174, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {0,IR(0, 0),IR(20430, 7)/* Vertex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {1,IR(0, 0),IR(20437, 20)/* TessellationControl */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {2,IR(0, 0),IR(20457, 23)/* TessellationEvaluation */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {3,IR(0, 0),IR(4863, 9)/* Geometry */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {4,IR(0, 0),IR(14608, 9)/* Fragment */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5,IR(0, 0),IR(20480, 10)/* GLCompute */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {6,IR(0, 0),IR(4630, 7)/* Kernel */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5267,IR(0, 0),IR(20490, 7)/* TaskNV */,IR(0, 0),IR(50, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5268,IR(0, 0),IR(20497, 7)/* MeshNV */,IR(0, 0),IR(50, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5313,IR(0, 0),IR(20504, 17)/* RayGenerationKHR */,IR(63, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5314,IR(0, 0),IR(20537, 16)/* IntersectionKHR */,IR(64, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5315,IR(0, 0),IR(20568, 10)/* AnyHitKHR */,IR(65, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5316,IR(0, 0),IR(20587, 14)/* ClosestHitKHR */,IR(66, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5317,IR(0, 0),IR(20614, 8)/* MissKHR */,IR(67, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5318,IR(0, 0),IR(20629, 12)/* CallableKHR */,IR(68, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5364,IR(0, 0),IR(20652, 8)/* TaskEXT */,IR(0, 0),IR(53, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5365,IR(0, 0),IR(20660, 8)/* MeshEXT */,IR(0, 0),IR(53, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {0,IR(0, 0),IR(20668, 9)/* Preserve */,IR(0, 0),IR(131, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPDENORM_MODE
  {1,IR(0, 0),IR(20677, 12)/* FlushToZero */,IR(0, 0),IR(131, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPDENORM_MODE
  {0,IR(0, 0),IR(20689, 12)/* BFloat16KHR */,IR(0, 0),IR(89, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {4214,IR(0, 0),IR(20701, 14)/* Float8E4M3EXT */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {4215,IR(0, 0),IR(20715, 14)/* Float8E5M2EXT */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {0,IR(0, 0),IR(20729, 5)/* IEEE */,IR(0, 0),IR(131, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPOPERATION_MODE
  {1,IR(0, 0),IR(20734, 4)/* ALT */,IR(0, 0),IR(131, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPOPERATION_MODE
  {0,IR(0, 0),IR(14204, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {1,IR(0, 0),IR(20738, 7)/* NotNaN */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {2,IR(0, 0),IR(20745, 7)/* NotInf */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {4,IR(0, 0),IR(20752, 4)/* NSZ */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {8,IR(0, 0),IR(20756, 11)/* AllowRecip */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {16,IR(0, 0),IR(20767, 5)/* Fast */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {65536,IR(0, 0),IR(20772, 14)/* AllowContract */,IR(69, 1),IR(175, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {131072,IR(0, 0),IR(20809, 13)/* AllowReassoc */,IR(70, 1),IR(175, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {262144,IR(0, 0),IR(20840, 15)/* AllowTransform */,IR(0, 0),IR(172, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {0,IR(0, 0),IR(20855, 4)/* RTE */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {1,IR(0, 0),IR(20859, 4)/* RTZ */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {2,IR(0, 0),IR(20863, 4)/* RTP */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {3,IR(0, 0),IR(20867, 4)/* RTN */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {1,IR(0, 0),IR(20871, 16)/* Vertical2Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {2,IR(0, 0),IR(20887, 16)/* Vertical4Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {4,IR(0, 0),IR(20903, 18)/* Horizontal2Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {8,IR(0, 0),IR(20921, 18)/* Horizontal4Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {0,IR(0, 0),IR(14204, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {1,IR(0, 0),IR(20939, 7)/* Inline */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {2,IR(0, 0),IR(20946, 11)/* DontInline */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {4,IR(0, 0),IR(20957, 5)/* Pure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {8,IR(0, 0),IR(20962, 6)/* Const */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {65536,IR(0, 0),IR(13350, 11)/* OptNoneEXT */,IR(50, 1),IR(177, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {0,IR(0, 0),IR(20968, 5)/* Zext */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {1,IR(0, 0),IR(20973, 5)/* Sext */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {2,IR(0, 0),IR(20978, 6)/* ByVal */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {3,IR(0, 0),IR(20984, 5)/* Sret */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {4,IR(0, 0),IR(20989, 8)/* NoAlias */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {5,IR(0, 0),IR(20997, 10)/* NoCapture */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {6,IR(0, 0),IR(21007, 8)/* NoWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {7,IR(0, 0),IR(21015, 12)/* NoReadWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {5940,IR(0, 0),IR(21027, 20)/* RuntimeAlignedINTEL */,IR(0, 0),IR(178, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {0,IR(0, 0),IR(21047, 7)/* Reduce */,IR(0, 0),IR(179, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {1,IR(0, 0),IR(21054, 14)/* InclusiveScan */,IR(0, 0),IR(179, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {2,IR(0, 0),IR(21068, 14)/* ExclusiveScan */,IR(0, 0),IR(179, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {3,IR(0, 0),IR(21082, 16)/* ClusteredReduce */,IR(0, 0),IR(182, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {6,IR(0, 0),IR(21098, 20)/* PartitionedReduceNV */,IR(0, 0),IR(183, 1),IR(75, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {7,IR(0, 0),IR(21118, 27)/* PartitionedInclusiveScanNV */,IR(0, 0),IR(183, 1),IR(75, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {8,IR(0, 0),IR(21145, 27)/* PartitionedExclusiveScanNV */,IR(0, 0),IR(183, 1),IR(75, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {0,IR(0, 0),IR(21172, 10)/* NoneINTEL */,IR(0, 0),IR(144, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {1,IR(0, 0),IR(21182, 10)/* ReadINTEL */,IR(0, 0),IR(144, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {2,IR(0, 0),IR(21192, 11)/* WriteINTEL */,IR(0, 0),IR(144, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {3,IR(0, 0),IR(21203, 15)/* ReadWriteINTEL */,IR(0, 0),IR(144, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {0,IR(0, 0),IR(14204, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {1,IR(10, 1),IR(21218, 5)/* Bias */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {2,IR(10, 1),IR(21223, 4)/* Lod */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {4,IR(36, 2),IR(21227, 5)/* Grad */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {8,IR(10, 1),IR(21232, 12)/* ConstOffset */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {16,IR(10, 1),IR(15611, 7)/* Offset */,IR(0, 0),IR(184, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {32,IR(10, 1),IR(21244, 13)/* ConstOffsets */,IR(0, 0),IR(184, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {64,IR(10, 1),IR(15408, 7)/* Sample */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {128,IR(10, 1),IR(8414, 7)/* MinLod */,IR(0, 0),IR(185, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {256,IR(4, 1),IR(21257, 19)/* MakeTexelAvailable */,IR(71, 1),IR(186, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {512,IR(4, 1),IR(21298, 17)/* MakeTexelVisible */,IR(72, 1),IR(186, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {1024,IR(0, 0),IR(21335, 16)/* NonPrivateTexel */,IR(73, 1),IR(186, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {2048,IR(0, 0),IR(21370, 14)/* VolatileTexel */,IR(74, 1),IR(186, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {4096,IR(0, 0),IR(21401, 11)/* SignExtend */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {8192,IR(0, 0),IR(21412, 11)/* ZeroExtend */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {16384,IR(0, 0),IR(21423, 12)/* Nontemporal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {65536,IR(10, 1),IR(21435, 8)/* Offsets */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {0,IR(0, 0),IR(21443, 10)/* SnormInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {1,IR(0, 0),IR(21453, 11)/* SnormInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {2,IR(0, 0),IR(21464, 10)/* UnormInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {3,IR(0, 0),IR(21474, 11)/* UnormInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {4,IR(0, 0),IR(21485, 14)/* UnormShort565 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {5,IR(0, 0),IR(21499, 14)/* UnormShort555 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {6,IR(0, 0),IR(21513, 15)/* UnormInt101010 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {7,IR(0, 0),IR(21528, 11)/* SignedInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {8,IR(0, 0),IR(21539, 12)/* SignedInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {9,IR(0, 0),IR(21551, 12)/* SignedInt32 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {10,IR(0, 0),IR(21563, 13)/* UnsignedInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {11,IR(0, 0),IR(21576, 14)/* UnsignedInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {12,IR(0, 0),IR(21590, 14)/* UnsignedInt32 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {13,IR(0, 0),IR(21604, 10)/* HalfFloat */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {14,IR(0, 0),IR(14101, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {15,IR(0, 0),IR(21614, 11)/* UnormInt24 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {16,IR(0, 0),IR(21625, 17)/* UnormInt101010_2 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {17,IR(0, 0),IR(21642, 16)/* UnormInt10X6EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {19,IR(0, 0),IR(21658, 20)/* UnsignedIntRaw10EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {20,IR(0, 0),IR(21678, 20)/* UnsignedIntRaw12EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {21,IR(0, 0),IR(21698, 20)/* UnormInt2_101010EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {22,IR(0, 0),IR(21718, 19)/* UnsignedInt10X6EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {23,IR(0, 0),IR(21737, 19)/* UnsignedInt12X4EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {24,IR(0, 0),IR(21756, 19)/* UnsignedInt14X2EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {25,IR(0, 0),IR(21775, 16)/* UnormInt12X4EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {26,IR(0, 0),IR(21791, 16)/* UnormInt14X2EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {0,IR(0, 0),IR(21807, 2)/* R */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {1,IR(0, 0),IR(21809, 2)/* A */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {2,IR(0, 0),IR(21811, 3)/* RG */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {3,IR(0, 0),IR(21814, 3)/* RA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {4,IR(0, 0),IR(21817, 4)/* RGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {5,IR(0, 0),IR(21821, 5)/* RGBA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {6,IR(0, 0),IR(21826, 5)/* BGRA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {7,IR(0, 0),IR(21831, 5)/* ARGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {8,IR(0, 0),IR(21836, 10)/* Intensity */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {9,IR(0, 0),IR(21846, 10)/* Luminance */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {10,IR(0, 0),IR(21856, 3)/* Rx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {11,IR(0, 0),IR(21859, 4)/* RGx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {12,IR(0, 0),IR(21863, 5)/* RGBx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {13,IR(0, 0),IR(21868, 6)/* Depth */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {14,IR(0, 0),IR(21874, 13)/* DepthStencil */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {15,IR(0, 0),IR(21887, 5)/* sRGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {16,IR(0, 0),IR(21892, 6)/* sRGBx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {17,IR(0, 0),IR(21898, 6)/* sRGBA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {18,IR(0, 0),IR(21904, 6)/* sBGRA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {19,IR(0, 0),IR(21910, 5)/* ABGR */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {0,IR(0, 0),IR(21915, 27)/* InitOnDeviceReprogramINTEL */,IR(0, 0),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {1,IR(0, 0),IR(21942, 23)/* InitOnDeviceResetINTEL */,IR(0, 0),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {0,IR(0, 0),IR(21965, 7)/* NoWait */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {1,IR(0, 0),IR(21972, 11)/* WaitKernel */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {2,IR(0, 0),IR(21983, 14)/* WaitWorkGroup */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {0,IR(0, 0),IR(14204, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {1,IR(0, 0),IR(21997, 12)/* CmdExecTime */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {0,IR(0, 0),IR(14204, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {1,IR(0, 0),IR(22009, 13)/* MayUsePrintf */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {0,IR(0, 0),IR(22022, 7)/* Export */,IR(0, 0),IR(120, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {1,IR(0, 0),IR(22029, 7)/* Import */,IR(0, 0),IR(120, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {2,IR(0, 0),IR(22036, 12)/* LinkOnceODR */,IR(0, 0),IR(120, 1),IR(164, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {0,IR(0, 0),IR(22048, 14)/* UncachedINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {1,IR(0, 0),IR(22062, 12)/* CachedINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {2,IR(0, 0),IR(22074, 15)/* StreamingINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {3,IR(0, 0),IR(22089, 25)/* InvalidateAfterReadINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {4,IR(0, 0),IR(22114, 17)/* ConstCachedINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {0,IR(0, 0),IR(14204, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {1,IR(0, 0),IR(22131, 7)/* Unroll */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {2,IR(0, 0),IR(22138, 11)/* DontUnroll */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {4,IR(0, 0),IR(22149, 19)/* DependencyInfinite */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {8,IR(0, 1),IR(22168, 17)/* DependencyLength */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {16,IR(0, 1),IR(22185, 14)/* MinIterations */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {32,IR(0, 1),IR(22199, 14)/* MaxIterations */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {64,IR(0, 1),IR(22213, 18)/* IterationMultiple */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {128,IR(0, 1),IR(22231, 10)/* PeelCount */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {256,IR(0, 1),IR(22241, 13)/* PartialCount */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {65536,IR(0, 1),IR(17478, 24)/* InitiationIntervalINTEL */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {131072,IR(0, 1),IR(17502, 20)/* MaxConcurrencyINTEL */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {262144,IR(0, 1),IR(22254, 21)/* DependencyArrayINTEL */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {524288,IR(0, 1),IR(17522, 20)/* PipelineEnableINTEL */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {1048576,IR(0, 1),IR(22275, 18)/* LoopCoalesceINTEL */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {2097152,IR(0, 1),IR(22293, 21)/* MaxInterleavingINTEL */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {4194304,IR(0, 1),IR(22314, 26)/* SpeculatedIterationsINTEL */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {8388608,IR(0, 0),IR(22340, 14)/* NoFusionINTEL */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {16777216,IR(0, 1),IR(22354, 15)/* LoopCountINTEL */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {33554432,IR(0, 1),IR(22369, 26)/* MaxReinvocationDelayINTEL */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {0,IR(0, 0),IR(14204, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {1,IR(0, 0),IR(22395, 29)/* MatrixASignedComponentsINTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {2,IR(0, 0),IR(22424, 29)/* MatrixBSignedComponentsINTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {4,IR(0, 0),IR(22453, 21)/* MatrixCBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {8,IR(0, 0),IR(22474, 26)/* MatrixResultBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {16,IR(0, 0),IR(22500, 23)/* MatrixAPackedInt8INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {32,IR(0, 0),IR(22523, 23)/* MatrixBPackedInt8INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {64,IR(0, 0),IR(22546, 23)/* MatrixAPackedInt4INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {128,IR(0, 0),IR(22569, 23)/* MatrixBPackedInt4INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {256,IR(0, 0),IR(22592, 17)/* MatrixATF32INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {512,IR(0, 0),IR(22609, 17)/* MatrixBTF32INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {1024,IR(0, 0),IR(22626, 26)/* MatrixAPackedFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {2048,IR(0, 0),IR(22652, 26)/* MatrixBPackedFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {4096,IR(0, 0),IR(22678, 27)/* MatrixAPackedBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {8192,IR(0, 0),IR(22705, 27)/* MatrixBPackedBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {0,IR(0, 0),IR(14204, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {1,IR(0, 0),IR(15442, 9)/* Volatile */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {2,IR(0, 1),IR(22732, 8)/* Aligned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {4,IR(0, 0),IR(21423, 12)/* Nontemporal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {8,IR(4, 1),IR(22740, 21)/* MakePointerAvailable */,IR(75, 1),IR(186, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {16,IR(4, 1),IR(22785, 19)/* MakePointerVisible */,IR(76, 1),IR(186, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {32,IR(0, 0),IR(22826, 18)/* NonPrivatePointer */,IR(77, 1),IR(186, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {65536,IR(10, 1),IR(22865, 20)/* AliasScopeINTELMask */,IR(0, 0),IR(136, 1),IR(113, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {131072,IR(10, 1),IR(22885, 17)/* NoAliasINTELMask */,IR(0, 0),IR(136, 1),IR(113, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {0,IR(0, 0),IR(22902, 7)/* Simple */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {1,IR(0, 0),IR(22909, 8)/* GLSL450 */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {2,IR(0, 0),IR(22917, 7)/* OpenCL */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {3,IR(0, 0),IR(22924, 7)/* Vulkan */,IR(78, 1),IR(186, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {0,IR(0, 0),IR(22941, 8)/* Relaxed */,IR(79, 1),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {2,IR(0, 0),IR(22949, 8)/* Acquire */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {4,IR(0, 0),IR(22957, 8)/* Release */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {8,IR(0, 0),IR(22965, 15)/* AcquireRelease */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {16,IR(0, 0),IR(22980, 23)/* SequentiallyConsistent */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {64,IR(0, 0),IR(23003, 14)/* UniformMemory */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {128,IR(0, 0),IR(23017, 15)/* SubgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {256,IR(0, 0),IR(23032, 16)/* WorkgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {512,IR(0, 0),IR(23048, 21)/* CrossWorkgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {1024,IR(0, 0),IR(23069, 20)/* AtomicCounterMemory */,IR(0, 0),IR(82, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {2048,IR(0, 0),IR(23089, 12)/* ImageMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {4096,IR(0, 0),IR(23101, 13)/* OutputMemory */,IR(80, 1),IR(186, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {8192,IR(0, 0),IR(23130, 14)/* MakeAvailable */,IR(81, 1),IR(186, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {16384,IR(0, 0),IR(23161, 12)/* MakeVisible */,IR(82, 1),IR(186, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {32768,IR(0, 0),IR(15442, 9)/* Volatile */,IR(0, 0),IR(186, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {0,IR(0, 0),IR(23188, 10)/* AutoINTEL */,IR(0, 0),IR(174, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS
  {0,IR(0, 0),IR(23198, 5)/* WRAP */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {1,IR(0, 0),IR(23203, 4)/* SAT */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {2,IR(0, 0),IR(23207, 9)/* SAT_ZERO */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {3,IR(0, 0),IR(23216, 8)/* SAT_SYM */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {0,IR(0, 0),IR(23224, 25)/* PackedVectorFormat4x8Bit */,IR(83, 1),IR(1, 0),IR(122, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {0,IR(0, 0),IR(23277, 4)/* TRN */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {1,IR(0, 0),IR(23281, 9)/* TRN_ZERO */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {2,IR(0, 0),IR(23290, 4)/* RND */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {3,IR(0, 0),IR(23294, 9)/* RND_ZERO */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {4,IR(0, 0),IR(23303, 8)/* RND_INF */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {5,IR(0, 0),IR(23311, 12)/* RND_MIN_INF */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {6,IR(0, 0),IR(23323, 9)/* RND_CONV */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {7,IR(0, 0),IR(23332, 13)/* RND_CONV_ODD */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {0,IR(0, 0),IR(14204, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {1,IR(0, 0),IR(23345, 25)/* RobustnessPerComponentNV */,IR(0, 0),IR(189, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {2,IR(0, 0),IR(23370, 23)/* RobustnessPerElementNV */,IR(0, 0),IR(189, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {0,IR(0, 0),IR(14956, 8)/* NoneKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {1,IR(0, 0),IR(23393, 10)/* OpaqueKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {2,IR(0, 0),IR(23403, 12)/* NoOpaqueKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {4,IR(0, 0),IR(23415, 23)/* TerminateOnFirstHitKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {8,IR(0, 0),IR(23438, 24)/* SkipClosestHitShaderKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {16,IR(0, 0),IR(23462, 27)/* CullBackFacingTrianglesKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {32,IR(0, 0),IR(23489, 28)/* CullFrontFacingTrianglesKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {64,IR(0, 0),IR(23517, 14)/* CullOpaqueKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {128,IR(0, 0),IR(23531, 16)/* CullNoOpaqueKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {256,IR(0, 0),IR(23547, 17)/* SkipTrianglesKHR */,IR(84, 1),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {512,IR(0, 0),IR(23588, 13)/* SkipAABBsKHR */,IR(0, 0),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {1024,IR(0, 0),IR(23601, 30)/* ForceOpacityMicromap2StateEXT */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {0,IR(0, 0),IR(23631, 41)/* RayQueryCandidateIntersectionTriangleKHR */,IR(0, 0),IR(192, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {1,IR(0, 0),IR(23672, 37)/* RayQueryCandidateIntersectionAABBKHR */,IR(0, 0),IR(192, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {0,IR(0, 0),IR(23709, 37)/* RayQueryCommittedIntersectionNoneKHR */,IR(0, 0),IR(192, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {1,IR(0, 0),IR(23746, 41)/* RayQueryCommittedIntersectionTriangleKHR */,IR(0, 0),IR(192, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {2,IR(0, 0),IR(23787, 42)/* RayQueryCommittedIntersectionGeneratedKHR */,IR(0, 0),IR(192, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {0,IR(0, 0),IR(23829, 33)/* RayQueryCandidateIntersectionKHR */,IR(0, 0),IR(192, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {1,IR(0, 0),IR(23862, 33)/* RayQueryCommittedIntersectionKHR */,IR(0, 0),IR(192, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {0,IR(0, 0),IR(14204, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {1,IR(0, 0),IR(23895, 12)/* ClampToEdge */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {2,IR(0, 0),IR(23907, 6)/* Clamp */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {3,IR(0, 0),IR(23913, 7)/* Repeat */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {4,IR(0, 0),IR(23920, 15)/* RepeatMirrored */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {0,IR(0, 0),IR(23935, 8)/* Nearest */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {1,IR(0, 0),IR(23943, 7)/* Linear */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {0,IR(0, 0),IR(23950, 8)/* Unknown */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {1,IR(0, 0),IR(23958, 8)/* Rgba32f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {2,IR(0, 0),IR(23966, 8)/* Rgba16f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {3,IR(0, 0),IR(23974, 5)/* R32f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {4,IR(0, 0),IR(23979, 6)/* Rgba8 */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {5,IR(0, 0),IR(23985, 11)/* Rgba8Snorm */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {6,IR(0, 0),IR(23996, 6)/* Rg32f */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {7,IR(0, 0),IR(24002, 6)/* Rg16f */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {8,IR(0, 0),IR(24008, 13)/* R11fG11fB10f */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {9,IR(0, 0),IR(24021, 5)/* R16f */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {10,IR(0, 0),IR(24026, 7)/* Rgba16 */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {11,IR(0, 0),IR(24033, 8)/* Rgb10A2 */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {12,IR(0, 0),IR(24041, 5)/* Rg16 */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {13,IR(0, 0),IR(24046, 4)/* Rg8 */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {14,IR(0, 0),IR(24050, 4)/* R16 */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {15,IR(0, 0),IR(24054, 3)/* R8 */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {16,IR(0, 0),IR(24057, 12)/* Rgba16Snorm */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {17,IR(0, 0),IR(24069, 10)/* Rg16Snorm */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {18,IR(0, 0),IR(24079, 9)/* Rg8Snorm */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {19,IR(0, 0),IR(24088, 9)/* R16Snorm */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {20,IR(0, 0),IR(24097, 8)/* R8Snorm */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {21,IR(0, 0),IR(24105, 8)/* Rgba32i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {22,IR(0, 0),IR(24113, 8)/* Rgba16i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {23,IR(0, 0),IR(24121, 7)/* Rgba8i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {24,IR(0, 0),IR(24128, 5)/* R32i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {25,IR(0, 0),IR(24133, 6)/* Rg32i */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {26,IR(0, 0),IR(24139, 6)/* Rg16i */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {27,IR(0, 0),IR(24145, 5)/* Rg8i */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {28,IR(0, 0),IR(24150, 5)/* R16i */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {29,IR(0, 0),IR(24155, 4)/* R8i */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {30,IR(0, 0),IR(24159, 9)/* Rgba32ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {31,IR(0, 0),IR(24168, 9)/* Rgba16ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {32,IR(0, 0),IR(24177, 8)/* Rgba8ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {33,IR(0, 0),IR(24185, 6)/* R32ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {34,IR(0, 0),IR(24191, 10)/* Rgb10a2ui */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {35,IR(0, 0),IR(24201, 7)/* Rg32ui */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {36,IR(0, 0),IR(24208, 7)/* Rg16ui */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {37,IR(0, 0),IR(24215, 6)/* Rg8ui */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {38,IR(0, 0),IR(24221, 6)/* R16ui */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {39,IR(0, 0),IR(24227, 5)/* R8ui */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {40,IR(0, 0),IR(24232, 6)/* R64ui */,IR(0, 0),IR(194, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {41,IR(0, 0),IR(24238, 5)/* R64i */,IR(0, 0),IR(194, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {0,IR(0, 0),IR(24243, 12)/* CrossDevice */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {1,IR(0, 0),IR(24255, 7)/* Device */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {2,IR(0, 0),IR(24262, 10)/* Workgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {3,IR(0, 0),IR(24272, 9)/* Subgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {4,IR(0, 0),IR(24281, 11)/* Invocation */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {5,IR(0, 0),IR(24292, 12)/* QueueFamily */,IR(85, 1),IR(186, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {6,IR(0, 0),IR(24319, 14)/* ShaderCallKHR */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {0,IR(0, 0),IR(14204, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {1,IR(0, 0),IR(24333, 8)/* Flatten */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {2,IR(0, 0),IR(24341, 12)/* DontFlatten */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {1,IR(0, 0),IR(24353, 29)/* IdentifierPossibleDuplicates */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS
  {0,IR(0, 0),IR(14073, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(14085, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(14093, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {3,IR(0, 0),IR(14101, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(14107, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(14114, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(14125, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(14134, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(14147, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(14153, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(14163, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(14169, 15)/* ImportedModule */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {1,IR(0, 0),IR(14184, 20)/* ImportedDeclaration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {0,IR(0, 0),IR(14204, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(14209, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(14225, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(14239, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(14252, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(14264, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(14281, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(14293, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(14308, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(14321, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(14336, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(14354, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(14371, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(14392, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(14412, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(14432, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {16384,IR(0, 0),IR(14448, 16)/* FlagIsEnumClass */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {32768,IR(0, 0),IR(14464, 20)/* FlagTypePassByValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {65536,IR(0, 0),IR(14484, 24)/* FlagTypePassByReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {131072,IR(0, 0),IR(24382, 26)/* FlagUnknownPhysicalLayout */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(14508, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {1,IR(0, 0),IR(14514, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {2,IR(0, 0),IR(14519, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {3,IR(10, 1),IR(14558, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {4,IR(36, 2),IR(14569, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {5,IR(0, 0),IR(14578, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {6,IR(0, 0),IR(14583, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {7,IR(0, 0),IR(14590, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {8,IR(10, 1),IR(14601, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {9,IR(36, 2),IR(14608, 9)/* Fragment */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {0,IR(0, 0),IR(14617, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(14627, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(14640, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {3,IR(0, 0),IR(14653, 11)/* AtomicType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(23950, 8)/* Unknown */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {1,IR(0, 0),IR(24408, 5)/* ESSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {2,IR(0, 0),IR(24413, 5)/* GLSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {3,IR(0, 0),IR(24418, 9)/* OpenCL_C */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {4,IR(0, 0),IR(24427, 11)/* OpenCL_CPP */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {5,IR(0, 0),IR(24438, 5)/* HLSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {6,IR(0, 0),IR(24443, 15)/* CPP_for_OpenCL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {7,IR(0, 0),IR(24458, 5)/* SYCL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {8,IR(0, 0),IR(24463, 7)/* HERO_C */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {9,IR(0, 0),IR(24470, 5)/* NZSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {10,IR(0, 0),IR(24475, 5)/* WGSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {11,IR(0, 0),IR(24480, 6)/* Slang */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {12,IR(0, 0),IR(24486, 4)/* Zig */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {13,IR(0, 0),IR(24490, 5)/* Rust */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {0,IR(0, 0),IR(24495, 16)/* UniformConstant */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {1,IR(0, 0),IR(24511, 6)/* Input */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {2,IR(0, 0),IR(15493, 8)/* Uniform */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {3,IR(0, 0),IR(24517, 7)/* Output */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4,IR(0, 0),IR(24262, 10)/* Workgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5,IR(0, 0),IR(24524, 15)/* CrossWorkgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {6,IR(0, 0),IR(24539, 8)/* Private */,IR(0, 0),IR(195, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {7,IR(0, 0),IR(24547, 9)/* Function */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {8,IR(0, 0),IR(24556, 8)/* Generic */,IR(0, 0),IR(197, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {9,IR(0, 0),IR(24564, 13)/* PushConstant */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {10,IR(0, 0),IR(24577, 14)/* AtomicCounter */,IR(0, 0),IR(82, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {11,IR(0, 0),IR(24591, 6)/* Image */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {12,IR(0, 0),IR(24597, 14)/* StorageBuffer */,IR(0, 0),IR(3, 1),IR(165, 2),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4172,IR(0, 0),IR(24611, 13)/* TileImageEXT */,IR(0, 0),IR(147, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4491,IR(0, 0),IR(24624, 19)/* TileAttachmentQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5068,IR(0, 0),IR(24643, 16)/* NodePayloadAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5328,IR(0, 0),IR(24659, 16)/* CallableDataKHR */,IR(86, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5329,IR(0, 0),IR(24690, 24)/* IncomingCallableDataKHR */,IR(87, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5338,IR(0, 0),IR(24737, 14)/* RayPayloadKHR */,IR(88, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5339,IR(0, 0),IR(24764, 16)/* HitAttributeKHR */,IR(89, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5342,IR(0, 0),IR(24795, 22)/* IncomingRayPayloadKHR */,IR(90, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5343,IR(0, 0),IR(24838, 22)/* ShaderRecordBufferKHR */,IR(91, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5349,IR(0, 0),IR(24881, 22)/* PhysicalStorageBuffer */,IR(92, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5385,IR(0, 0),IR(24928, 21)/* HitObjectAttributeNV */,IR(0, 0),IR(126, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5402,IR(0, 0),IR(24949, 24)/* TaskPayloadWorkgroupEXT */,IR(0, 0),IR(53, 1),IR(23, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5605,IR(0, 0),IR(24973, 17)/* CodeSectionINTEL */,IR(0, 0),IR(198, 1),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5936,IR(0, 0),IR(24990, 16)/* DeviceOnlyINTEL */,IR(0, 0),IR(199, 1),IR(117, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5937,IR(0, 0),IR(25006, 14)/* HostOnlyINTEL */,IR(0, 0),IR(199, 1),IR(117, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {0,IR(0, 0),IR(22048, 14)/* UncachedINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {1,IR(0, 0),IR(25020, 18)/* WriteThroughINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {2,IR(0, 0),IR(25038, 15)/* WriteBackINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {3,IR(0, 0),IR(22074, 15)/* StreamingINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {0,IR(0, 0),IR(14204, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {1,IR(10, 1),IR(25053, 11)/* TensorView */,IR(0, 0),IR(200, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {2,IR(10, 1),IR(25064, 11)/* DecodeFunc */,IR(0, 0),IR(201, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {0,IR(0, 0),IR(25075, 10)/* Undefined */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {1,IR(0, 0),IR(15451, 9)/* Constant */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {2,IR(0, 0),IR(23895, 12)/* ClampToEdge */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {3,IR(0, 0),IR(23913, 7)/* Repeat */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {4,IR(0, 0),IR(23920, 15)/* RepeatMirrored */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {0,IR(0, 0),IR(25085, 8)/* NoneARM */,IR(0, 0),IR(202, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {1,IR(0, 0),IR(25093, 15)/* NontemporalARM */,IR(0, 0),IR(202, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {2,IR(10, 1),IR(25108, 20)/* OutOfBoundsValueARM */,IR(0, 0),IR(202, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {4,IR(10, 1),IR(25128, 24)/* MakeElementAvailableARM */,IR(0, 0),IR(202, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {8,IR(10, 1),IR(25152, 22)/* MakeElementVisibleARM */,IR(0, 0),IR(202, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {16,IR(0, 0),IR(25174, 21)/* NonPrivateElementARM */,IR(0, 0),IR(202, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
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
    case SPV_OPERAND_TYPE_CAPABILITY: return IR(133, 274);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(407, 8);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(415, 3);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(418, 2);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS: return IR(420, 19);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION: return IR(439, 10);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(449, 4);
    case SPV_OPERAND_TYPE_COMPONENT_TYPE: return IR(453, 15);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT: return IR(468, 4);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS: return IR(472, 6);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE: return IR(478, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE: return IR(481, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT: return IR(484, 4);
    case SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(488, 8);
    case SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE: return IR(496, 3);
    case SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS: return IR(499, 16);
    case SPV_OPERAND_TYPE_DEBUG_OPERATION: return IR(515, 9);
    case SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER: return IR(524, 3);
    case SPV_OPERAND_TYPE_DECORATION: return IR(527, 144);
    case SPV_OPERAND_TYPE_DIMENSIONALITY: return IR(671, 8);
    case SPV_OPERAND_TYPE_EXECUTION_MODE: return IR(679, 96);
    case SPV_OPERAND_TYPE_EXECUTION_MODEL: return IR(775, 17);
    case SPV_OPERAND_TYPE_FPDENORM_MODE: return IR(792, 2);
    case SPV_OPERAND_TYPE_FPENCODING: return IR(794, 3);
    case SPV_OPERAND_TYPE_FPOPERATION_MODE: return IR(797, 2);
    case SPV_OPERAND_TYPE_FP_FAST_MATH_MODE: return IR(799, 9);
    case SPV_OPERAND_TYPE_FP_ROUNDING_MODE: return IR(808, 4);
    case SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE: return IR(812, 4);
    case SPV_OPERAND_TYPE_FUNCTION_CONTROL: return IR(816, 6);
    case SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE: return IR(822, 9);
    case SPV_OPERAND_TYPE_GROUP_OPERATION: return IR(831, 7);
    case SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER: return IR(838, 4);
    case SPV_OPERAND_TYPE_IMAGE: return IR(842, 17);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE: return IR(859, 26);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER: return IR(885, 20);
    case SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER: return IR(905, 2);
    case SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS: return IR(907, 3);
    case SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO: return IR(910, 2);
    case SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS: return IR(912, 2);
    case SPV_OPERAND_TYPE_LINKAGE_TYPE: return IR(914, 3);
    case SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL: return IR(917, 5);
    case SPV_OPERAND_TYPE_LOOP_CONTROL: return IR(922, 20);
    case SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(942, 15);
    case SPV_OPERAND_TYPE_MEMORY_ACCESS: return IR(957, 9);
    case SPV_OPERAND_TYPE_MEMORY_MODEL: return IR(966, 4);
    case SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID: return IR(970, 15);
    case SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS: return IR(985, 1);
    case SPV_OPERAND_TYPE_OVERFLOW_MODES: return IR(986, 4);
    case SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT: return IR(990, 1);
    case SPV_OPERAND_TYPE_QUANTIZATION_MODES: return IR(991, 8);
    case SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS: return IR(999, 3);
    case SPV_OPERAND_TYPE_RAY_FLAGS: return IR(1002, 12);
    case SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE: return IR(1014, 2);
    case SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE: return IR(1016, 3);
    case SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION: return IR(1019, 2);
    case SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE: return IR(1021, 5);
    case SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE: return IR(1026, 2);
    case SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT: return IR(1028, 42);
    case SPV_OPERAND_TYPE_SCOPE_ID: return IR(1070, 7);
    case SPV_OPERAND_TYPE_SELECTION_CONTROL: return IR(1077, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS: return IR(1080, 1);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(1081, 8);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(1089, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(1092, 2);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS: return IR(1094, 20);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION: return IR(1114, 10);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(1124, 4);
    case SPV_OPERAND_TYPE_SOURCE_LANGUAGE: return IR(1128, 14);
    case SPV_OPERAND_TYPE_STORAGE_CLASS: return IR(1142, 28);
    case SPV_OPERAND_TYPE_STORE_CACHE_CONTROL: return IR(1170, 4);
    case SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS: return IR(1174, 3);
    case SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE: return IR(1177, 5);
    case SPV_OPERAND_TYPE_TENSOR_OPERANDS: return IR(1182, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_IMAGE: return IR(842, 17);
    case SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS: return IR(957, 9);
    case SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT: return IR(990, 1);
    case SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS: return IR(472, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(942, 15);
    case SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS: return IR(999, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_FPENCODING: return IR(794, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS: return IR(1182, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_CAPABILITY: return IR(133, 274);
    default: break;
  }
  return IR(0,0);
}

// Operand names and index into kOperandsByValue, ordered by (operand kind, name)
// The fields in order are:
//   name, either the primary name or an alias, indexing into kStrings
//   index into the kOperandsByValue array
static const std::array<NameIndex, 1282> kOperandNames{{
  {IR(4621, 9), 0}, // 0 ReadOnly in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(4647, 10), 2}, // 1 ReadWrite in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(4637, 10), 1}, // 2 WriteOnly in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(4657, 8), 3}, // 3 Logical in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(4665, 11), 4}, // 4 Physical32 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(4686, 11), 5}, // 5 Physical64 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(4697, 24), 6}, // 6 PhysicalStorageBuffer64 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(4721, 27), 6}, // 7 PhysicalStorageBuffer64EXT in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(6631, 13), 92}, // 8 BaryCoordKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6644, 12), 92}, // 9 BaryCoordNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6026, 20), 68}, // 10 BaryCoordNoPerspAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6046, 28), 69}, // 11 BaryCoordNoPerspCentroidAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6679, 20), 93}, // 12 BaryCoordNoPerspKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6699, 19), 93}, // 13 BaryCoordNoPerspNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6074, 26), 70}, // 14 BaryCoordNoPerspSampleAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6171, 22), 74}, // 15 BaryCoordPullModelAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6100, 19), 71}, // 16 BaryCoordSmoothAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6119, 27), 72}, // 17 BaryCoordSmoothCentroidAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6146, 25), 73}, // 18 BaryCoordSmoothSampleAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5830, 13), 59}, // 19 BaseInstance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5804, 11), 58}, // 20 BaseVertex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4805, 13), 9}, // 21 ClipDistance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6538, 22), 87}, // 22 ClipDistancePerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7837, 12), 131}, // 23 ClusterIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5568, 13), 49}, // 24 CoreCountARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5542, 10), 48}, // 25 CoreIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5581, 13), 50}, // 26 CoreMaxIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4818, 13), 10}, // 27 CullDistance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6560, 22), 88}, // 28 CullDistancePerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7890, 12), 132}, // 29 CullMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6886, 17), 99}, // 30 CullPrimitiveEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7290, 17), 113}, // 31 CurrentRayTimeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5900, 12), 62}, // 32 DeviceIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5843, 10), 60}, // 33 DrawIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5332, 22), 37}, // 34 EnqueuedWorkgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5102, 10), 21}, // 35 FragCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5188, 10), 27}, // 36 FragDepth in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6764, 23), 95}, // 37 FragInvocationCountEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6718, 12), 94}, // 38 FragSizeEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6193, 18), 75}, // 39 FragStencilRefEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6730, 15), 94}, // 40 FragmentSizeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5123, 12), 23}, // 41 FrontFacing in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6450, 16), 83}, // 42 FullyCoveredEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5273, 19), 33}, // 43 GlobalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5367, 15), 39}, // 44 GlobalLinearId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5354, 13), 38}, // 45 GlobalOffset in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5321, 11), 36}, // 46 GlobalSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5198, 17), 28}, // 47 HelperInvocation in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7592, 11), 120}, // 48 HitIsLSSNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7550, 14), 119}, // 49 HitIsSphereNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7772, 33), 128}, // 50 HitKindBackFacingMicroTriangleNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7738, 34), 127}, // 51 HitKindFrontFacingMicroTriangleNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7269, 11), 112}, // 52 HitKindKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7280, 10), 112}, // 53 HitKindNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7720, 18), 126}, // 54 HitLSSPositionsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7823, 14), 130}, // 55 HitLSSRadiiNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7454, 37), 116}, // 56 HitMicroTriangleVertexBarycentricsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7387, 34), 115}, // 57 HitMicroTriangleVertexPositionsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7642, 20), 121}, // 58 HitSpherePositionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7805, 18), 129}, // 59 HitSphereRadiusNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7262, 7), 111}, // 60 HitTNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7330, 30), 114}, // 61 HitTriangleVertexPositionsKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7491, 20), 117}, // 62 IncomingRayFlagsKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7511, 19), 117}, // 63 IncomingRayFlagsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7151, 23), 108}, // 64 InstanceCustomIndexKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7174, 22), 108}, // 65 InstanceCustomIndexNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4840, 11), 12}, // 66 InstanceId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5528, 14), 47}, // 67 InstanceIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4941, 13), 14}, // 68 InvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6787, 22), 95}, // 69 InvocationsPerPixelNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6903, 12), 100}, // 70 LaunchIdKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6915, 11), 100}, // 71 LaunchIdNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6926, 14), 101}, // 72 LaunchSizeKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6940, 13), 101}, // 73 LaunchSizeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4954, 6), 15}, // 74 Layer in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6582, 15), 89}, // 75 LayerPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5255, 18), 32}, // 76 LocalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5292, 21), 34}, // 77 LocalInvocationIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6597, 16), 90}, // 78 MeshViewCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6613, 18), 91}, // 79 MeshViewIndicesNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5458, 21), 43}, // 80 NumEnqueuedSubgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5445, 13), 42}, // 81 NumSubgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5215, 14), 29}, // 82 NumWorkgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7066, 22), 105}, // 83 ObjectRayDirectionKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7088, 21), 105}, // 84 ObjectRayDirectionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7029, 19), 104}, // 85 ObjectRayOriginKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7048, 18), 104}, // 86 ObjectRayOriginNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7196, 17), 109}, // 87 ObjectToWorldKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7213, 16), 109}, // 88 ObjectToWorldNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5088, 14), 20}, // 89 PatchVertices in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5112, 11), 22}, // 90 PointCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4795, 10), 8}, // 91 PointSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4779, 9), 7}, // 92 Position in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6390, 18), 81}, // 93 PositionPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6502, 17), 85}, // 94 PrimitiveCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4851, 12), 13}, // 95 PrimitiveId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6519, 19), 86}, // 96 PrimitiveIndicesNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6834, 24), 97}, // 97 PrimitiveLineIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6809, 25), 96}, // 98 PrimitivePointIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5853, 24), 61}, // 99 PrimitiveShadingRateKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6858, 28), 98}, // 100 PrimitiveTriangleIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7530, 20), 118}, // 101 RayGeometryIndexKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7130, 11), 107}, // 102 RayTmaxKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7141, 10), 107}, // 103 RayTmaxNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7109, 11), 106}, // 104 RayTminKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7120, 10), 106}, // 105 RayTminNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6228, 29), 76}, // 106 RemainingRecursionLevelsAMDX in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7694, 10), 123}, // 107 SMCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7713, 7), 125}, // 108 SMIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5135, 9), 24}, // 109 SampleId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5177, 11), 26}, // 110 SampleMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5162, 15), 25}, // 111 SamplePosition in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6327, 20), 79}, // 112 SecondaryPositionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6366, 24), 80}, // 113 SecondaryViewportMaskNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6275, 16), 77}, // 114 ShaderIndexAMDX in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5944, 15), 64}, // 115 ShadingRateKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5617, 15), 53}, // 116 SubgroupEqMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5632, 18), 53}, // 117 SubgroupEqMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5672, 15), 54}, // 118 SubgroupGeMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5687, 18), 54}, // 119 SubgroupGeMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5705, 15), 55}, // 120 SubgroupGtMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5720, 18), 55}, // 121 SubgroupGtMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5479, 11), 44}, // 122 SubgroupId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5738, 15), 56}, // 123 SubgroupLeMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5753, 18), 56}, // 124 SubgroupLeMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5490, 26), 45}, // 125 SubgroupLocalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5771, 15), 57}, // 126 SubgroupLtMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5786, 18), 57}, // 127 SubgroupLtMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5429, 16), 41}, // 128 SubgroupMaxSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5382, 13), 40}, // 129 SubgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6490, 12), 84}, // 130 TaskCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5078, 10), 19}, // 131 TessCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5063, 15), 18}, // 132 TessLevelInner in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5048, 15), 17}, // 133 TessLevelOuter in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6008, 18), 67}, // 134 TileApronSizeQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5990, 18), 66}, // 135 TileDimensionQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5959, 15), 65}, // 136 TileOffsetQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4831, 9), 11}, // 137 VertexId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5516, 12), 46}, // 138 VertexIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5924, 10), 63}, // 139 ViewIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5000, 14), 16}, // 140 ViewportIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6291, 15), 78}, // 141 ViewportMaskNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6428, 22), 82}, // 142 ViewportMaskPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5594, 10), 51}, // 143 WarpIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7704, 9), 124}, // 144 WarpIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5604, 13), 52}, // 145 WarpMaxIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7662, 13), 122}, // 146 WarpsPerSMNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5313, 8), 35}, // 147 WorkDim in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5243, 12), 31}, // 148 WorkgroupId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5229, 14), 30}, // 149 WorkgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6988, 21), 103}, // 150 WorldRayDirectionKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7009, 20), 103}, // 151 WorldRayDirectionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6953, 18), 102}, // 152 WorldRayOriginKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6971, 17), 102}, // 153 WorldRayOriginNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7229, 17), 110}, // 154 WorldToObjectKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7246, 16), 110}, // 155 WorldToObjectNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4676, 10), 137}, // 156 Addresses in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12907, 34), 359}, // 157 ArbitraryPrecisionFixedPointINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12595, 37), 347}, // 158 ArbitraryPrecisionFloatingPointINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12563, 32), 346}, // 159 ArbitraryPrecisionIntegersINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13457, 19), 383}, // 160 ArithmeticFenceEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12228, 9), 332}, // 161 AsmINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13374, 20), 379}, // 162 AtomicFloat16AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12283, 23), 335}, // 163 AtomicFloat16MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11756, 22), 310}, // 164 AtomicFloat16VectorNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13290, 20), 375}, // 165 AtomicFloat32AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12237, 23), 333}, // 166 AtomicFloat32MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13310, 20), 376}, // 167 AtomicFloat64AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12260, 23), 334}, // 168 AtomicFloat64MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8070, 14), 153}, // 169 AtomicStorage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9457, 17), 229}, // 170 AtomicStorageOps in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13415, 24), 381}, // 171 BFloat16ConversionINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10079, 29), 263}, // 172 BFloat16CooperativeMatrixKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10057, 22), 262}, // 173 BFloat16DotProductKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10041, 16), 261}, // 174 BFloat16TypeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14053, 20), 406}, // 175 BindlessImagesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11693, 18), 307}, // 176 BindlessTextureNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13234, 16), 372}, // 177 BitInstructions in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13006, 19), 363}, // 178 BlockingPipesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14014, 19), 404}, // 179 CacheControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4805, 13), 163}, // 180 ClipDistance in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11351, 32), 296}, // 181 ComputeDerivativeGroupLinearKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11383, 31), 296}, // 182 ComputeDerivativeGroupLinearNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10231, 31), 275}, // 183 ComputeDerivativeGroupQuadsKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10262, 30), 275}, // 184 ComputeDerivativeGroupQuadsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11933, 30), 319}, // 185 CooperativeMatrixBlockLoadsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9826, 32), 248}, // 186 CooperativeMatrixConversionQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11826, 31), 316}, // 187 CooperativeMatrixConversionsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9105, 21), 370}, // 188 CooperativeMatrixKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9040, 28), 211}, // 189 CooperativeMatrixLayoutsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11439, 20), 298}, // 190 CooperativeMatrixNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11857, 40), 317}, // 191 CooperativeMatrixPerElementOperationsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11796, 30), 315}, // 192 CooperativeMatrixReductionsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11897, 36), 318}, // 193 CooperativeMatrixTensorAddressingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11736, 20), 309}, // 194 CooperativeVectorNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11963, 28), 320}, // 195 CooperativeVectorTrainingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5552, 16), 203}, // 196 CoreBuiltinsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4818, 13), 164}, // 197 CullDistance in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13394, 21), 380}, // 198 DebugInfoModuleINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11562, 25), 303}, // 199 DemoteToHelperInvocation in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11587, 28), 303}, // 200 DemoteToHelperInvocationEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9596, 18), 235}, // 201 DenormFlushToZero in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9581, 15), 234}, // 202 DenormPreserve in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8517, 18), 182}, // 203 DerivativeControl in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8041, 14), 151}, // 204 DeviceEnqueue in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5912, 12), 225}, // 205 DeviceGroup in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11615, 23), 304}, // 206 DisplacementMicromapNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13185, 11), 368}, // 207 DotProduct in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13079, 22), 366}, // 208 DotProductInput4x8Bit in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13101, 25), 366}, // 209 DotProductInput4x8BitKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13126, 28), 367}, // 210 DotProductInput4x8BitPacked in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13154, 31), 367}, // 211 DotProductInput4x8BitPackedKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13038, 19), 365}, // 212 DotProductInputAll in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13057, 22), 365}, // 213 DotProductInputAllKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13196, 14), 368}, // 214 DotProductKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5815, 15), 216}, // 215 DrawParameters in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12340, 16), 338}, // 216 ExpectAssumeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12543, 20), 345}, // 217 FPFastMathModeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13591, 28), 389}, // 218 FPGAArgumentInterfacesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12883, 24), 358}, // 219 FPGABufferLocationINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12756, 27), 353}, // 220 FPGAClusterAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13476, 29), 384}, // 221 FPGAClusterAttributesV2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12797, 20), 355}, // 222 FPGADSPControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12843, 40), 357}, // 223 FPGAInvocationPipeliningAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12706, 26), 351}, // 224 FPGAKernelAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13505, 28), 385}, // 225 FPGAKernelAttributesv2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13567, 24), 388}, // 226 FPGALatencyControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12662, 22), 349}, // 227 FPGALoopControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12732, 24), 352}, // 228 FPGAMemoryAccessesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12517, 26), 344}, // 229 FPGAMemoryAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13025, 13), 364}, // 230 FPGARegINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13551, 16), 387}, // 231 FPMaxErrorINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7955, 8), 142}, // 232 Float16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7941, 14), 141}, // 233 Float16Buffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9881, 16), 250}, // 234 Float16ImageAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7963, 8), 143}, // 235 Float64 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9078, 27), 213}, // 236 Float8CooperativeMatrixEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9068, 10), 212}, // 237 Float8EXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13275, 15), 374}, // 238 FloatControls2 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12136, 23), 328}, // 239 FloatingPointModeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6656, 23), 274}, // 240 FragmentBarycentricKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10209, 22), 274}, // 241 FragmentBarycentricNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6745, 19), 276}, // 242 FragmentDensityEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6466, 24), 270}, // 243 FragmentFullyCoveredEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9919, 16), 252}, // 244 FragmentMaskAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11530, 32), 302}, // 245 FragmentShaderPixelInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11459, 33), 299}, // 246 FragmentShaderSampleInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11492, 38), 300}, // 247 FragmentShaderShadingRateInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5877, 23), 214}, // 248 FragmentShadingRateKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12491, 26), 343}, // 249 FunctionFloatControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12182, 22), 330}, // 250 FunctionPointersINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13914, 22), 400}, // 251 FunctionVariantsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8362, 15), 169}, // 252 GenericPointer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4863, 9), 135}, // 253 Geometry in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8112, 18), 156}, // 254 GeometryPointSize in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10137, 28), 265}, // 255 GeometryShaderPassthroughNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8575, 16), 185}, // 256 GeometryStreams in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13649, 35), 391}, // 257 GlobalVariableFPGADecorationsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13619, 30), 390}, // 258 GlobalVariableHostAccessINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9031, 9), 210}, // 259 GraphARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5395, 16), 192}, // 260 GroupNonUniform in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8714, 26), 194}, // 261 GroupNonUniformArithmetic in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5650, 22), 195}, // 262 GroupNonUniformBallot in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8794, 25), 198}, // 263 GroupNonUniformClustered in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10306, 29), 277}, // 264 GroupNonUniformPartitionedNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8819, 20), 199}, // 265 GroupNonUniformQuad in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13250, 25), 373}, // 266 GroupNonUniformRotateKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8740, 23), 196}, // 267 GroupNonUniformShuffle in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8763, 31), 197}, // 268 GroupNonUniformShuffleRelative in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8694, 20), 193}, // 269 GroupNonUniformVote in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13936, 26), 401}, // 270 GroupUniformArithmeticKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8034, 7), 150}, // 271 Groups in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12993, 13), 362}, // 272 IOPipesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8431, 8), 175}, // 273 Image1D in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7990, 11), 146}, // 274 ImageBasic in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8453, 12), 178}, // 275 ImageBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8308, 15), 165}, // 276 ImageCubeArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10192, 17), 272}, // 277 ImageFootprintNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9897, 22), 251}, // 278 ImageGatherBiasLodAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8130, 20), 157}, // 279 ImageGatherExtended in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8465, 13), 179}, // 280 ImageMSArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8016, 12), 148}, // 281 ImageMipmap in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8506, 11), 181}, // 282 ImageQuery in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8001, 15), 147}, // 283 ImageReadWrite in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9935, 21), 254}, // 284 ImageReadWriteLodAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8340, 10), 167}, // 285 ImageRect in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12204, 24), 331}, // 286 IndirectReferencesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8382, 16), 171}, // 287 InputAttachment in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10421, 36), 280}, // 288 InputAttachmentArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10457, 39), 280}, // 289 InputAttachmentArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10962, 39), 287}, // 290 InputAttachmentArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11001, 42), 287}, // 291 InputAttachmentArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8084, 6), 154}, // 292 Int16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10014, 27), 260}, // 293 Int4CooperativeMatrixINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10000, 14), 259}, // 294 Int4TypeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7971, 6), 144}, // 295 Int64 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7977, 13), 145}, // 296 Int64Atomics in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9956, 14), 255}, // 297 Int64ImageEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8377, 5), 170}, // 298 Int8 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12159, 23), 329}, // 299 IntegerFunctions2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8535, 22), 183}, // 300 InterpolationFunction in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4630, 7), 139}, // 301 Kernel in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12684, 22), 350}, // 302 KernelAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7924, 8), 138}, // 303 Linkage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8055, 15), 152}, // 304 LiteralSampler in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13330, 20), 377}, // 305 LongCompositesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12783, 14), 354}, // 306 LoopFuseINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13989, 25), 403}, // 307 MaskedGatherScatterINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7917, 7), 133}, // 308 Matrix in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12817, 26), 356}, // 309 MemoryAccessAliasingINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4926, 15), 273}, // 310 MeshShadingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4912, 14), 271}, // 311 MeshShadingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8414, 7), 173}, // 312 MinLod in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5934, 10), 226}, // 313 MultiView in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5014, 14), 188}, // 314 MultiViewport in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8669, 13), 190}, // 315 NamedBarrier in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13350, 11), 378}, // 316 OptNoneEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13361, 13), 378}, // 317 OptNoneINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6408, 20), 269}, // 318 PerViewAttributesNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4748, 31), 295}, // 319 PhysicalStorageBufferAddresses in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11317, 34), 295}, // 320 PhysicalStorageBufferAddressesEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8682, 12), 191}, // 321 PipeStorage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8028, 6), 149}, // 322 Pipes in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9985, 15), 258}, // 323 QuadControlKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11778, 18), 312}, // 324 RawAccessChainsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7902, 15), 369}, // 325 RayCullMaskKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9694, 12), 240}, // 326 RayQueryKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11711, 25), 308}, // 327 RayQueryPositionFetchKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9671, 23), 239}, // 328 RayQueryProvisionalKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7849, 41), 321}, // 329 RayTracingClusterAccelerationStructureNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7421, 33), 311}, // 330 RayTracingDisplacementMicromapNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4898, 14), 243}, // 331 RayTracingKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7603, 39), 314}, // 332 RayTracingLinearSweptSpheresGeometryNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7307, 23), 292}, // 333 RayTracingMotionBlurNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4885, 13), 291}, // 334 RayTracingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11638, 29), 305}, // 335 RayTracingOpacityMicromapEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7360, 27), 290}, // 336 RayTracingPositionFetchKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11414, 25), 297}, // 337 RayTracingProvisionalKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7564, 28), 313}, // 338 RayTracingSpheresGeometryNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9725, 32), 242}, // 339 RayTraversalPrimitiveCullingKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14033, 20), 405}, // 340 RegisterLimitsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13210, 24), 371}, // 341 ReplicatedCompositesEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12115, 21), 327}, // 342 RoundToInfinityINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9639, 16), 237}, // 343 RoundingModeRTE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9655, 16), 238}, // 344 RoundingModeRTZ in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12964, 29), 361}, // 345 RuntimeAlignedAttributeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10372, 23), 279}, // 346 RuntimeDescriptorArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10395, 26), 279}, // 347 RuntimeDescriptorArrayEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10108, 29), 264}, // 348 SampleMaskOverrideCoverageNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9474, 28), 230}, // 349 SampleMaskPostDepthCoverage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5144, 18), 166}, // 350 SampleRateShading in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8421, 10), 174}, // 351 Sampled1D in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8439, 14), 177}, // 352 SampledBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8323, 17), 176}, // 353 SampledCubeArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8208, 33), 160}, // 354 SampledImageArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10735, 36), 284}, // 355 SampledImageArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10771, 39), 284}, // 356 SampledImageArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8350, 12), 168}, // 357 SampledRect in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4788, 7), 134}, // 358 Shader in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9970, 15), 256}, // 359 ShaderClockKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6257, 18), 257}, // 360 ShaderEnqueueAMDX in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11667, 26), 306}, // 361 ShaderInvocationReorderNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4960, 12), 200}, // 362 ShaderLayer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10335, 17), 278}, // 363 ShaderNonUniform in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10352, 20), 278}, // 364 ShaderNonUniformEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7675, 19), 301}, // 365 ShaderSMBuiltinsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6347, 19), 268}, // 366 ShaderStereoViewNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5028, 20), 201}, // 367 ShaderViewportIndex in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4972, 28), 266}, // 368 ShaderViewportIndexLayerEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10165, 27), 266}, // 369 ShaderViewportIndexLayerNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6306, 21), 267}, // 370 ShaderViewportMaskNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10292, 14), 276}, // 371 ShadingRateNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9614, 25), 236}, // 372 SignedZeroInfNanPreserve in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8398, 16), 172}, // 373 SparseResidency in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13893, 21), 399}, // 374 SpecConditionalINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13439, 18), 382}, // 375 SplitBarrierINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6211, 17), 253}, // 376 StencilExportEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9262, 25), 221}, // 377 StorageBuffer16BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9502, 24), 231}, // 378 StorageBuffer8BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8241, 34), 161}, // 379 StorageBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10810, 37), 285}, // 380 StorageBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10847, 40), 285}, // 381 StorageBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8275, 33), 162}, // 382 StorageImageArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10887, 36), 286}, // 383 StorageImageArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10923, 39), 286}, // 384 StorageImageArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8478, 28), 180}, // 385 StorageImageExtendedFormats in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8150, 24), 158}, // 386 StorageImageMultisample in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8591, 30), 186}, // 387 StorageImageReadWithoutFormat in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8621, 31), 187}, // 388 StorageImageWriteWithoutFormat in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9389, 21), 224}, // 389 StorageInputOutput16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9367, 22), 223}, // 390 StoragePushConstant16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9560, 21), 233}, // 391 StoragePushConstant8 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8954, 37), 208}, // 392 StorageTensorArrayDynamicIndexingARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8991, 40), 209}, // 393 StorageTensorArrayNonUniformIndexingARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10577, 39), 282}, // 394 StorageTexelBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10616, 42), 282}, // 395 StorageTexelBufferArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11130, 42), 289}, // 396 StorageTexelBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11172, 45), 289}, // 397 StorageTexelBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9350, 17), 222}, // 398 StorageUniform16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9287, 28), 221}, // 399 StorageUniformBufferBlock16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13712, 23), 393}, // 400 Subgroup2DBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13735, 30), 394}, // 401 Subgroup2DBlockTransformINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13765, 30), 395}, // 402 Subgroup2DBlockTransposeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12427, 39), 341}, // 403 SubgroupAvcMotionEstimationChromaINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12356, 33), 339}, // 404 SubgroupAvcMotionEstimationINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12389, 38), 340}, // 405 SubgroupAvcMotionEstimationIntraINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5411, 18), 215}, // 406 SubgroupBallotKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12031, 27), 324}, // 407 SubgroupBufferBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13684, 28), 392}, // 408 SubgroupBufferPrefetchINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8652, 17), 189}, // 409 SubgroupDispatch in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12058, 26), 325}, // 410 SubgroupImageBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12084, 31), 326}, // 411 SubgroupImageMediaBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13795, 38), 396}, // 412 SubgroupMatrixMultiplyAccumulateINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12010, 21), 323}, // 413 SubgroupShuffleINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9246, 16), 220}, // 414 SubgroupVoteKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13533, 18), 386}, // 415 TaskSequenceINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11991, 19), 322}, // 416 TensorAddressingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13962, 27), 402}, // 417 TensorFloat32RoundingINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8943, 11), 207}, // 418 TensorsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13833, 28), 397}, // 419 TernaryBitwiseFunctionINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4872, 13), 136}, // 420 Tessellation in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8090, 22), 155}, // 421 TessellationPointSize in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9858, 23), 249}, // 422 TextureBlockMatch2QCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9804, 22), 246}, // 423 TextureBlockMatchQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9783, 21), 245}, // 424 TextureBoxFilterQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9757, 26), 244}, // 425 TextureSampleWeightedQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8857, 28), 204}, // 426 TileImageColorReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8885, 28), 205}, // 427 TileImageDepthReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8913, 30), 206}, // 428 TileImageStencilReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5974, 16), 247}, // 429 TileShadingQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8557, 18), 184}, // 430 TransformFeedback in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12941, 23), 360}, // 431 USMStorageClassesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9315, 35), 222}, // 432 UniformAndStorageBuffer16BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9526, 34), 232}, // 433 UniformAndStorageBuffer8BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8174, 34), 159}, // 434 UniformBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10658, 37), 283}, // 435 UniformBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10695, 40), 283}, // 436 UniformBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8839, 18), 202}, // 437 UniformDecoration in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10496, 39), 281}, // 438 UniformTexelBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10535, 42), 281}, // 439 UniformTexelBufferArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11043, 42), 288}, // 440 UniformTexelBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11085, 45), 288}, // 441 UniformTexelBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12632, 30), 348}, // 442 UnstructuredLoopControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9706, 19), 241}, // 443 UntypedPointersKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13861, 32), 398}, // 444 UntypedVariableLengthArrayINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12466, 25), 342}, // 445 VariableLengthArrayINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9440, 17), 228}, // 446 VariablePointers in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9410, 30), 227}, // 447 VariablePointersStorageBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7932, 9), 140}, // 448 Vector16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12325, 15), 337}, // 449 VectorAnyINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12306, 19), 336}, // 450 VectorComputeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11217, 18), 293}, // 451 VulkanMemoryModel in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11256, 29), 294}, // 452 VulkanMemoryModelDeviceScope in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11285, 32), 294}, // 453 VulkanMemoryModelDeviceScopeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11235, 21), 293}, // 454 VulkanMemoryModelKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9202, 44), 219}, // 455 WorkgroupMemoryExplicitLayout16BitAccessKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9159, 43), 218}, // 456 WorkgroupMemoryExplicitLayout8BitAccessKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9126, 33), 217}, // 457 WorkgroupMemoryExplicitLayoutKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14085, 8), 408}, // 458 Address in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14093, 8), 409}, // 459 Boolean in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14101, 6), 410}, // 460 Float in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14107, 7), 411}, // 461 Signed in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14114, 11), 412}, // 462 SignedChar in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14125, 9), 413}, // 463 Unsigned in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14134, 13), 414}, // 464 UnsignedChar in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14073, 12), 407}, // 465 Unspecified in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14147, 6), 415}, // 466 Class in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(14153, 10), 416}, // 467 Structure in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(14163, 6), 417}, // 468 Union in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(14184, 20), 419}, // 469 ImportedDeclaration in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(14169, 15), 418}, // 470 ImportedModule in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(14293, 15), 427}, // 471 FlagArtificial in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14308, 13), 428}, // 472 FlagExplicit in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14281, 12), 426}, // 473 FlagFwdDecl in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14371, 21), 432}, // 474 FlagIndirectVariable in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14264, 17), 425}, // 475 FlagIsDefinition in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14448, 16), 436}, // 476 FlagIsEnumClass in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14252, 12), 424}, // 477 FlagIsLocal in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14432, 16), 435}, // 478 FlagIsOptimized in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14225, 14), 422}, // 479 FlagIsPrivate in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14209, 16), 421}, // 480 FlagIsProtected in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14239, 13), 423}, // 481 FlagIsPublic in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14392, 20), 433}, // 482 FlagLValueReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14336, 18), 430}, // 483 FlagObjectPointer in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14321, 15), 429}, // 484 FlagPrototyped in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14412, 20), 434}, // 485 FlagRValueReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14354, 17), 431}, // 486 FlagStaticMember in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14484, 24), 438}, // 487 FlagTypePassByReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14464, 20), 437}, // 488 FlagTypePassByValue in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14204, 5), 420}, // 489 None in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14569, 9), 443}, // 490 BitPiece in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14601, 7), 447}, // 491 Constu in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14508, 6), 439}, // 492 Deref in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14608, 9), 448}, // 493 Fragment in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14519, 6), 441}, // 494 Minus in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14514, 5), 440}, // 495 Plus in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14558, 11), 442}, // 496 PlusUconst in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14590, 11), 446}, // 497 StackValue in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14578, 5), 444}, // 498 Swap in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14583, 7), 445}, // 499 Xderef in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14653, 11), 452}, // 500 AtomicType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14617, 10), 449}, // 501 ConstType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14640, 13), 451}, // 502 RestrictType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14627, 13), 450}, // 503 VolatileType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14664, 10), 453}, // 504 Float16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14674, 10), 454}, // 505 Float32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14684, 10), 455}, // 506 Float64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14852, 12), 466}, // 507 FloatE4M3NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14864, 12), 467}, // 508 FloatE5M2NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14707, 14), 457}, // 509 SignedInt16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14721, 14), 458}, // 510 SignedInt32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14735, 14), 459}, // 511 SignedInt64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14694, 13), 456}, // 512 SignedInt8NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14812, 19), 464}, // 513 SignedInt8PackedNV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14764, 16), 461}, // 514 UnsignedInt16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14780, 16), 462}, // 515 UnsignedInt32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14796, 16), 463}, // 516 UnsignedInt64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14749, 15), 460}, // 517 UnsignedInt8NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14831, 21), 465}, // 518 UnsignedInt8PackedNV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14928, 28), 471}, // 519 ColumnBlockedInterleavedARM in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(14888, 15), 469}, // 520 ColumnMajorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(14903, 25), 470}, // 521 RowBlockedInterleavedARM in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(14876, 12), 468}, // 522 RowMajorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(14964, 27), 473}, // 523 MatrixASignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(14991, 27), 474}, // 524 MatrixBSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(15018, 27), 475}, // 525 MatrixCSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(15045, 32), 476}, // 526 MatrixResultSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(14956, 8), 472}, // 527 NoneKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(15077, 26), 477}, // 528 SaturatingAccumulationKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(15114, 4), 480}, // 529 2x2 in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(15107, 7), 479}, // 530 Column in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(15103, 4), 478}, // 531 Row in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(15118, 11), 481}, // 532 MatrixAKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(15140, 21), 483}, // 533 MatrixAccumulatorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(15129, 11), 482}, // 534 MatrixBKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(15172, 14), 485}, // 535 ColumnMajorNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(15186, 21), 486}, // 536 InferencingOptimalNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(15161, 11), 484}, // 537 RowMajorNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(15207, 18), 487}, // 538 TrainingOptimalNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(14085, 8), 489}, // 539 Address in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14093, 8), 490}, // 540 Boolean in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14101, 6), 491}, // 541 Float in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14107, 7), 492}, // 542 Signed in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14114, 11), 493}, // 543 SignedChar in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14125, 9), 494}, // 544 Unsigned in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14134, 13), 495}, // 545 UnsignedChar in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14073, 12), 488}, // 546 Unspecified in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14147, 6), 496}, // 547 Class in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(14153, 10), 497}, // 548 Structure in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(14163, 6), 498}, // 549 Union in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(14293, 15), 506}, // 550 FlagArtificial in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14308, 13), 507}, // 551 FlagExplicit in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14281, 12), 505}, // 552 FlagFwdDecl in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14371, 21), 511}, // 553 FlagIndirectVariable in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14264, 17), 504}, // 554 FlagIsDefinition in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14252, 12), 503}, // 555 FlagIsLocal in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14432, 16), 514}, // 556 FlagIsOptimized in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14225, 14), 501}, // 557 FlagIsPrivate in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14209, 16), 500}, // 558 FlagIsProtected in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14239, 13), 502}, // 559 FlagIsPublic in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14392, 20), 512}, // 560 FlagLValueReference in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14336, 18), 509}, // 561 FlagObjectPointer in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14321, 15), 508}, // 562 FlagPrototyped in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14412, 20), 513}, // 563 FlagRValueReference in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14354, 17), 510}, // 564 FlagStaticMember in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14204, 5), 499}, // 565 None in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14569, 9), 519}, // 566 BitPiece in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14601, 7), 523}, // 567 Constu in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14508, 6), 515}, // 568 Deref in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14519, 6), 517}, // 569 Minus in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14514, 5), 516}, // 570 Plus in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14558, 11), 518}, // 571 PlusUconst in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14590, 11), 522}, // 572 StackValue in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14578, 5), 520}, // 573 Swap in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14583, 7), 521}, // 574 Xderef in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14617, 10), 524}, // 575 ConstType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(14640, 13), 526}, // 576 RestrictType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(14627, 13), 525}, // 577 VolatileType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(17449, 16), 641}, // 578 AliasScopeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15434, 8), 546}, // 579 Aliased in SPV_OPERAND_TYPE_DECORATION
  {IR(16552, 15), 599}, // 580 AliasedPointer in SPV_OPERAND_TYPE_DECORATION
  {IR(16567, 18), 599}, // 581 AliasedPointerEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(15912, 10), 570}, // 582 Alignment in SPV_OPERAND_TYPE_DECORATION
  {IR(15956, 12), 572}, // 583 AlignmentId in SPV_OPERAND_TYPE_DECORATION
  {IR(15285, 12), 533}, // 584 ArrayStride in SPV_OPERAND_TYPE_DECORATION
  {IR(17230, 14), 629}, // 585 BankBitsINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17069, 15), 622}, // 586 BankwidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15589, 8), 559}, // 587 Binding in SPV_OPERAND_TYPE_DECORATION
  {IR(16633, 16), 602}, // 588 BindlessImageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16615, 18), 601}, // 589 BindlessSamplerNV in SPV_OPERAND_TYPE_DECORATION
  {IR(15249, 6), 529}, // 590 Block in SPV_OPERAND_TYPE_DECORATION
  {IR(16096, 22), 579}, // 591 BlockMatchSamplerQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(16074, 22), 578}, // 592 BlockMatchTextureQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(16664, 13), 604}, // 593 BoundImageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16649, 15), 603}, // 594 BoundSamplerNV in SPV_OPERAND_TYPE_DECORATION
  {IR(15255, 12), 530}, // 595 BufferBlock in SPV_OPERAND_TYPE_DECORATION
  {IR(17542, 20), 646}, // 596 BufferLocationINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15366, 8), 538}, // 597 BuiltIn in SPV_OPERAND_TYPE_DECORATION
  {IR(17312, 19), 634}, // 598 BurstCoalesceINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15332, 8), 537}, // 599 CPacked in SPV_OPERAND_TYPE_DECORATION
  {IR(18352, 22), 669}, // 600 CacheControlLoadINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18411, 23), 670}, // 601 CacheControlStoreINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17331, 15), 635}, // 602 CacheSizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15399, 9), 542}, // 603 Centroid in SPV_OPERAND_TYPE_DECORATION
  {IR(16717, 13), 607}, // 604 ClobberINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15460, 9), 549}, // 605 Coherent in SPV_OPERAND_TYPE_DECORATION
  {IR(15276, 9), 532}, // 606 ColMajor in SPV_OPERAND_TYPE_DECORATION
  {IR(15573, 10), 557}, // 607 Component in SPV_OPERAND_TYPE_DECORATION
  {IR(18299, 17), 668}, // 608 ConditionalINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17851, 27), 656}, // 609 ConduitKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15451, 9), 548}, // 610 Constant in SPV_OPERAND_TYPE_DECORATION
  {IR(16863, 14), 614}, // 611 CounterBuffer in SPV_OPERAND_TYPE_DECORATION
  {IR(15597, 14), 560}, // 612 DescriptorSet in SPV_OPERAND_TYPE_DECORATION
  {IR(17346, 28), 636}, // 613 DontStaticallyCoalesceINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17122, 16), 625}, // 614 DoublepumpINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16118, 18), 580}, // 615 ExplicitInterpAMD in SPV_OPERAND_TYPE_DECORATION
  {IR(15782, 15), 566}, // 616 FPFastMathMode in SPV_OPERAND_TYPE_DECORATION
  {IR(17770, 26), 653}, // 617 FPMaxErrorDecorationINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15732, 15), 565}, // 618 FPRoundingMode in SPV_OPERAND_TYPE_DECORATION
  {IR(15388, 5), 540}, // 619 Flat in SPV_OPERAND_TYPE_DECORATION
  {IR(17244, 20), 630}, // 620 ForcePow2DepthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15684, 14), 564}, // 621 FuncParamAttr in SPV_OPERAND_TYPE_DECORATION
  {IR(16774, 21), 610}, // 622 FuncParamIOKindINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17005, 24), 618}, // 623 FunctionDenormModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17615, 31), 648}, // 624 FunctionFloatingPointModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16948, 26), 617}, // 625 FunctionRoundingModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17405, 25), 639}, // 626 FuseLoopsInFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15321, 11), 536}, // 627 GLSLPacked in SPV_OPERAND_TYPE_DECORATION
  {IR(15310, 11), 535}, // 628 GLSLShared in SPV_OPERAND_TYPE_DECORATION
  {IR(16837, 26), 613}, // 629 GlobalVariableOffsetINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16585, 30), 600}, // 630 HitObjectShaderRecordBufferNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16877, 24), 614}, // 631 HlslCounterBufferGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(16914, 19), 615}, // 632 HlslSemanticGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(18194, 16), 665}, // 633 HostAccessINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17562, 19), 647}, // 634 IOPipeStorageINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18271, 28), 667}, // 635 ImplementInRegisterMapINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15583, 6), 558}, // 636 Index in SPV_OPERAND_TYPE_DECORATION
  {IR(18257, 14), 666}, // 637 InitModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17478, 24), 643}, // 638 InitiationIntervalINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15891, 21), 569}, // 639 InputAttachmentIndex in SPV_OPERAND_TYPE_DECORATION
  {IR(15415, 10), 544}, // 640 Invariant in SPV_OPERAND_TYPE_DECORATION
  {IR(17821, 30), 655}, // 641 LatencyControlConstraintINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17796, 25), 654}, // 642 LatencyControlLabelINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15859, 18), 567}, // 643 LinkageAttributes in SPV_OPERAND_TYPE_DECORATION
  {IR(15564, 9), 556}, // 644 Location in SPV_OPERAND_TYPE_DECORATION
  {IR(17909, 33), 658}, // 645 MMHostInterfaceAddressWidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17942, 30), 659}, // 646 MMHostInterfaceDataWidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17972, 28), 660}, // 647 MMHostInterfaceLatencyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18068, 29), 662}, // 648 MMHostInterfaceMaxBurstINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18034, 34), 661}, // 649 MMHostInterfaceReadWriteModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18097, 32), 663}, // 650 MMHostInterfaceWaitRequestINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17430, 19), 640}, // 651 MathOpDSPModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15297, 13), 534}, // 652 MatrixStride in SPV_OPERAND_TYPE_DECORATION
  {IR(15922, 14), 571}, // 653 MaxByteOffset in SPV_OPERAND_TYPE_DECORATION
  {IR(15968, 16), 573}, // 654 MaxByteOffsetId in SPV_OPERAND_TYPE_DECORATION
  {IR(17502, 20), 644}, // 655 MaxConcurrencyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17084, 22), 623}, // 656 MaxPrivateCopiesINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17138, 19), 626}, // 657 MaxReplicatesINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17706, 18), 651}, // 658 MediaBlockIOINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17043, 12), 620}, // 659 MemoryINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17177, 11), 628}, // 660 MergeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17465, 13), 642}, // 661 NoAliasINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15877, 14), 568}, // 662 NoContraction in SPV_OPERAND_TYPE_DECORATION
  {IR(15374, 14), 539}, // 663 NoPerspective in SPV_OPERAND_TYPE_DECORATION
  {IR(16028, 13), 575}, // 664 NoSignedWrap in SPV_OPERAND_TYPE_DECORATION
  {IR(16041, 15), 576}, // 665 NoUnsignedWrap in SPV_OPERAND_TYPE_DECORATION
  {IR(16168, 20), 582}, // 666 NodeMaxPayloadsAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(16136, 32), 581}, // 667 NodeSharesPayloadLimitsWithAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(15481, 12), 551}, // 668 NonReadable in SPV_OPERAND_TYPE_DECORATION
  {IR(16492, 11), 597}, // 669 NonUniform in SPV_OPERAND_TYPE_DECORATION
  {IR(16503, 14), 597}, // 670 NonUniformEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(15469, 12), 550}, // 671 NonWritable in SPV_OPERAND_TYPE_DECORATION
  {IR(17055, 14), 621}, // 672 NumbanksINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15611, 7), 561}, // 673 Offset in SPV_OPERAND_TYPE_DECORATION
  {IR(16336, 19), 589}, // 674 OverrideCoverageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16355, 14), 590}, // 675 PassthroughNV in SPV_OPERAND_TYPE_DECORATION
  {IR(15393, 6), 541}, // 676 Patch in SPV_OPERAND_TYPE_DECORATION
  {IR(16308, 28), 588}, // 677 PayloadDispatchIndirectAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(16283, 25), 587}, // 678 PayloadNodeArraySizeAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(16231, 25), 585}, // 679 PayloadNodeBaseIndexAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(16211, 20), 584}, // 680 PayloadNodeNameAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(16256, 27), 586}, // 681 PayloadNodeSparseArrayAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(16416, 16), 593}, // 682 PerPrimitiveEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(16432, 15), 593}, // 683 PerPrimitiveNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16457, 10), 595}, // 684 PerTaskNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16467, 13), 596}, // 685 PerVertexKHR in SPV_OPERAND_TYPE_DECORATION
  {IR(16480, 12), 596}, // 686 PerVertexNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16447, 10), 594}, // 687 PerViewNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17522, 20), 645}, // 688 PipelineEnableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17374, 14), 637}, // 689 PrefetchINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16691, 26), 606}, // 690 ReferencedIndirectlyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17029, 14), 619}, // 691 RegisterINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17878, 31), 657}, // 692 RegisterMapKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15225, 17), 527}, // 693 RelaxedPrecision in SPV_OPERAND_TYPE_DECORATION
  {IR(15425, 9), 545}, // 694 Restrict in SPV_OPERAND_TYPE_DECORATION
  {IR(16517, 16), 598}, // 695 RestrictPointer in SPV_OPERAND_TYPE_DECORATION
  {IR(16533, 19), 598}, // 696 RestrictPointerEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(15267, 9), 531}, // 697 RowMajor in SPV_OPERAND_TYPE_DECORATION
  {IR(16677, 14), 605}, // 698 SIMTCallINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15408, 7), 543}, // 699 Sample in SPV_OPERAND_TYPE_DECORATION
  {IR(15537, 20), 554}, // 700 SaturatedConversion in SPV_OPERAND_TYPE_DECORATION
  {IR(15984, 44), 574}, // 701 SaturatedToLargestFloat8NormalConversionEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(16388, 28), 592}, // 702 SecondaryViewportRelativeNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16730, 17), 608}, // 703 SideEffectsINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17157, 20), 627}, // 704 SimpleDualPortINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17646, 25), 649}, // 705 SingleElementVectorINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17106, 16), 624}, // 706 SinglepumpINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15242, 7), 528}, // 707 SpecId in SPV_OPERAND_TYPE_DECORATION
  {IR(18129, 26), 664}, // 708 StableKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16822, 15), 612}, // 709 StackCallINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17388, 17), 638}, // 710 StallEnableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17724, 15), 652}, // 711 StallFreeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15557, 7), 555}, // 712 Stream in SPV_OPERAND_TYPE_DECORATION
  {IR(17264, 16), 631}, // 713 StridesizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16188, 23), 583}, // 714 TrackFinishWritingAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17294, 18), 633}, // 715 TrueDualPortINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15493, 8), 552}, // 716 Uniform in SPV_OPERAND_TYPE_DECORATION
  {IR(15527, 10), 553}, // 717 UniformId in SPV_OPERAND_TYPE_DECORATION
  {IR(16901, 13), 615}, // 718 UserSemantic in SPV_OPERAND_TYPE_DECORATION
  {IR(16933, 15), 616}, // 719 UserTypeGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(17671, 35), 650}, // 720 VectorComputeCallableFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16795, 27), 611}, // 721 VectorComputeFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16747, 27), 609}, // 722 VectorComputeVariableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16369, 19), 591}, // 723 ViewportRelativeNV in SPV_OPERAND_TYPE_DECORATION
  {IR(15442, 9), 547}, // 724 Volatile in SPV_OPERAND_TYPE_DECORATION
  {IR(16056, 18), 577}, // 725 WeightTextureQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(17280, 14), 632}, // 726 WordsizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15618, 10), 562}, // 727 XfbBuffer in SPV_OPERAND_TYPE_DECORATION
  {IR(15628, 10), 563}, // 728 XfbStride in SPV_OPERAND_TYPE_DECORATION
  {IR(18434, 3), 671}, // 729 1D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18437, 3), 672}, // 730 2D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18440, 3), 673}, // 731 3D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18453, 7), 676}, // 732 Buffer in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18443, 5), 674}, // 733 Cube in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18448, 5), 675}, // 734 Rect in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18460, 12), 677}, // 735 SubpassData in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18472, 17), 678}, // 736 TileImageDataEXT in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(19284, 15), 731}, // 737 CoalescingAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18915, 15), 709}, // 738 ContractionOff in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(9596, 18), 723}, // 739 DenormFlushToZero in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(9581, 15), 722}, // 740 DenormPreserve in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18685, 13), 692}, // 741 DepthGreater in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18698, 10), 693}, // 742 DepthLess in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18670, 15), 691}, // 743 DepthReplacing in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18708, 15), 694}, // 744 DepthUnchanged in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19705, 25), 749}, // 745 DerivativeGroupLinearKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19730, 24), 749}, // 746 DerivativeGroupLinearNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19658, 24), 748}, // 747 DerivativeGroupQuadsKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19682, 23), 748}, // 748 DerivativeGroupQuadsNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19232, 29), 729}, // 749 EarlyAndLateFragmentTestsAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18637, 19), 688}, // 750 EarlyFragmentTests in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20215, 18), 768}, // 751 FPFastMathDefault in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18942, 10), 711}, // 752 Finalizer in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20030, 26), 760}, // 753 FloatingPointModeALTINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20056, 27), 761}, // 754 FloatingPointModeIEEEINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18930, 12), 710}, // 755 Initializer in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18759, 11), 698}, // 756 InputLines in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18770, 20), 699}, // 757 InputLinesAdjacency in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18747, 12), 697}, // 758 InputPoints in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18800, 24), 701}, // 759 InputTrianglesAdjacency in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18489, 12), 679}, // 760 Invocations in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19299, 15), 732}, // 761 IsApiEntryAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18830, 9), 703}, // 762 Isolines in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18723, 10), 695}, // 763 LocalSize in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18733, 14), 696}, // 764 LocalSizeHint in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19010, 16), 716}, // 765 LocalSizeHintId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18998, 12), 715}, // 766 LocalSizeId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19314, 21), 733}, // 767 MaxNodeRecursionAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19359, 21), 736}, // 768 MaxNumWorkgroupsAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20105, 16), 763}, // 769 MaxWorkDimINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20083, 22), 762}, // 770 MaxWorkgroupSizeINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20191, 24), 767}, // 771 MaximallyReconvergesKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20306, 22), 772}, // 772 MaximumRegistersINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20328, 24), 773}, // 773 MaximumRegistersIdINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20283, 23), 771}, // 774 NamedBarrierCountINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20403, 27), 774}, // 775 NamedMaximumRegistersINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20121, 20), 764}, // 776 NoGlobalOffsetINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19026, 34), 717}, // 777 NonCoherentColorAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19060, 34), 718}, // 778 NonCoherentDepthAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19094, 36), 719}, // 779 NonCoherentStencilAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19178, 34), 727}, // 780 NonCoherentTileAttachmentReadQCOM in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20141, 22), 765}, // 781 NumSIMDWorkitemsINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18621, 16), 687}, // 782 OriginLowerLeft in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18605, 16), 686}, // 783 OriginUpperLeft in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18867, 16), 706}, // 784 OutputLineStrip in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19590, 15), 746}, // 785 OutputLinesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19605, 14), 746}, // 786 OutputLinesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18854, 13), 705}, // 787 OutputPoints in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19619, 20), 747}, // 788 OutputPrimitivesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19639, 19), 747}, // 789 OutputPrimitivesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18883, 20), 707}, // 790 OutputTriangleStrip in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19754, 19), 750}, // 791 OutputTrianglesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19773, 18), 750}, // 792 OutputTrianglesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18839, 15), 704}, // 793 OutputVertices in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18586, 19), 685}, // 794 PixelCenterInteger in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19791, 25), 751}, // 795 PixelInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19816, 27), 752}, // 796 PixelInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18656, 10), 689}, // 797 PointMode in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19160, 18), 721}, // 798 PostDepthCoverage in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19531, 19), 743}, // 799 QuadDerivativesKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18824, 6), 702}, // 800 Quads in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20257, 26), 770}, // 801 RegisterMapInterfaceINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19550, 20), 744}, // 802 RequireFullQuadsKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(9639, 16), 725}, // 803 RoundingModeRTE in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20009, 21), 759}, // 804 RoundingModeRTNINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19988, 21), 758}, // 805 RoundingModeRTPINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(9655, 16), 726}, // 806 RoundingModeRTZ in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19843, 26), 753}, // 807 SampleInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19869, 28), 754}, // 808 SampleInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20163, 28), 766}, // 809 SchedulerTargetFmaxMhzINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(6275, 16), 735}, // 810 ShaderIndexAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19897, 31), 755}, // 811 ShadingRateInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19928, 33), 756}, // 812 ShadingRateInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19961, 27), 757}, // 813 SharedLocalMemorySizeINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19570, 20), 745}, // 814 SharesInputWithAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(9614, 25), 724}, // 815 SignedZeroInfNanPreserve in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18501, 13), 680}, // 816 SpacingEqual in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18514, 22), 681}, // 817 SpacingFractionalEven in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18536, 21), 682}, // 818 SpacingFractionalOdd in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19335, 24), 734}, // 819 StaticNumWorkgroupsAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19484, 25), 741}, // 820 StencilRefGreaterBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19408, 26), 738}, // 821 StencilRefGreaterFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19509, 22), 742}, // 822 StencilRefLessBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19434, 23), 739}, // 823 StencilRefLessFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19261, 23), 730}, // 824 StencilRefReplacingEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19457, 27), 740}, // 825 StencilRefUnchangedBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19380, 28), 737}, // 826 StencilRefUnchangedFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20233, 24), 769}, // 827 StreamingInterfaceINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(5382, 13), 712}, // 828 SubgroupSize in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19130, 30), 720}, // 829 SubgroupUniformControlFlowKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18952, 22), 713}, // 830 SubgroupsPerWorkgroup in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18974, 24), 714}, // 831 SubgroupsPerWorkgroupId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19212, 20), 728}, // 832 TileShadingRateQCOM in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18790, 10), 700}, // 833 Triangles in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18903, 12), 708}, // 834 VecTypeHint in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18571, 15), 684}, // 835 VertexOrderCcw in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18557, 14), 683}, // 836 VertexOrderCw in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18666, 4), 690}, // 837 Xfb in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20568, 10), 786}, // 838 AnyHitKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20578, 9), 786}, // 839 AnyHitNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20629, 12), 789}, // 840 CallableKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20641, 11), 789}, // 841 CallableNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20587, 14), 787}, // 842 ClosestHitKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20601, 13), 787}, // 843 ClosestHitNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(14608, 9), 779}, // 844 Fragment in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20480, 10), 780}, // 845 GLCompute in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(4863, 9), 778}, // 846 Geometry in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20537, 16), 785}, // 847 IntersectionKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20553, 15), 785}, // 848 IntersectionNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(4630, 7), 781}, // 849 Kernel in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20660, 8), 791}, // 850 MeshEXT in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20497, 7), 783}, // 851 MeshNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20614, 8), 788}, // 852 MissKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20622, 7), 788}, // 853 MissNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20504, 17), 784}, // 854 RayGenerationKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20521, 16), 784}, // 855 RayGenerationNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20652, 8), 790}, // 856 TaskEXT in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20490, 7), 782}, // 857 TaskNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20437, 20), 776}, // 858 TessellationControl in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20457, 23), 777}, // 859 TessellationEvaluation in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20430, 7), 775}, // 860 Vertex in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20677, 12), 793}, // 861 FlushToZero in SPV_OPERAND_TYPE_FPDENORM_MODE
  {IR(20668, 9), 792}, // 862 Preserve in SPV_OPERAND_TYPE_FPDENORM_MODE
  {IR(20689, 12), 794}, // 863 BFloat16KHR in SPV_OPERAND_TYPE_FPENCODING
  {IR(20701, 14), 795}, // 864 Float8E4M3EXT in SPV_OPERAND_TYPE_FPENCODING
  {IR(20715, 14), 796}, // 865 Float8E5M2EXT in SPV_OPERAND_TYPE_FPENCODING
  {IR(20734, 4), 798}, // 866 ALT in SPV_OPERAND_TYPE_FPOPERATION_MODE
  {IR(20729, 5), 797}, // 867 IEEE in SPV_OPERAND_TYPE_FPOPERATION_MODE
  {IR(20772, 14), 805}, // 868 AllowContract in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20786, 23), 805}, // 869 AllowContractFastINTEL in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20809, 13), 806}, // 870 AllowReassoc in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20822, 18), 806}, // 871 AllowReassocINTEL in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20756, 11), 803}, // 872 AllowRecip in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20840, 15), 807}, // 873 AllowTransform in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20767, 5), 804}, // 874 Fast in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20752, 4), 802}, // 875 NSZ in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(14204, 5), 799}, // 876 None in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20745, 7), 801}, // 877 NotInf in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20738, 7), 800}, // 878 NotNaN in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20855, 4), 808}, // 879 RTE in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(20867, 4), 811}, // 880 RTN in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(20863, 4), 810}, // 881 RTP in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(20859, 4), 809}, // 882 RTZ in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(20903, 18), 814}, // 883 Horizontal2Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(20921, 18), 815}, // 884 Horizontal4Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(20871, 16), 812}, // 885 Vertical2Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(20887, 16), 813}, // 886 Vertical4Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(20962, 6), 820}, // 887 Const in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(20946, 11), 818}, // 888 DontInline in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(20939, 7), 817}, // 889 Inline in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(14204, 5), 816}, // 890 None in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(13350, 11), 821}, // 891 OptNoneEXT in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(13361, 13), 821}, // 892 OptNoneINTEL in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(20957, 5), 819}, // 893 Pure in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(20978, 6), 824}, // 894 ByVal in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20989, 8), 826}, // 895 NoAlias in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20997, 10), 827}, // 896 NoCapture in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(21015, 12), 829}, // 897 NoReadWrite in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(21007, 8), 828}, // 898 NoWrite in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(21027, 20), 830}, // 899 RuntimeAlignedINTEL in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20973, 5), 823}, // 900 Sext in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20984, 5), 825}, // 901 Sret in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20968, 5), 822}, // 902 Zext in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(21082, 16), 834}, // 903 ClusteredReduce in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(21068, 14), 833}, // 904 ExclusiveScan in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(21054, 14), 832}, // 905 InclusiveScan in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(21145, 27), 837}, // 906 PartitionedExclusiveScanNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(21118, 27), 836}, // 907 PartitionedInclusiveScanNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(21098, 20), 835}, // 908 PartitionedReduceNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(21047, 7), 831}, // 909 Reduce in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(21172, 10), 838}, // 910 NoneINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(21182, 10), 839}, // 911 ReadINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(21203, 15), 841}, // 912 ReadWriteINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(21192, 11), 840}, // 913 WriteINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(21218, 5), 843}, // 914 Bias in SPV_OPERAND_TYPE_IMAGE
  {IR(21232, 12), 846}, // 915 ConstOffset in SPV_OPERAND_TYPE_IMAGE
  {IR(21244, 13), 848}, // 916 ConstOffsets in SPV_OPERAND_TYPE_IMAGE
  {IR(21227, 5), 845}, // 917 Grad in SPV_OPERAND_TYPE_IMAGE
  {IR(21223, 4), 844}, // 918 Lod in SPV_OPERAND_TYPE_IMAGE
  {IR(21257, 19), 851}, // 919 MakeTexelAvailable in SPV_OPERAND_TYPE_IMAGE
  {IR(21276, 22), 851}, // 920 MakeTexelAvailableKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(21298, 17), 852}, // 921 MakeTexelVisible in SPV_OPERAND_TYPE_IMAGE
  {IR(21315, 20), 852}, // 922 MakeTexelVisibleKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(8414, 7), 850}, // 923 MinLod in SPV_OPERAND_TYPE_IMAGE
  {IR(21335, 16), 853}, // 924 NonPrivateTexel in SPV_OPERAND_TYPE_IMAGE
  {IR(21351, 19), 853}, // 925 NonPrivateTexelKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(14204, 5), 842}, // 926 None in SPV_OPERAND_TYPE_IMAGE
  {IR(21423, 12), 857}, // 927 Nontemporal in SPV_OPERAND_TYPE_IMAGE
  {IR(15611, 7), 847}, // 928 Offset in SPV_OPERAND_TYPE_IMAGE
  {IR(21435, 8), 858}, // 929 Offsets in SPV_OPERAND_TYPE_IMAGE
  {IR(15408, 7), 849}, // 930 Sample in SPV_OPERAND_TYPE_IMAGE
  {IR(21401, 11), 855}, // 931 SignExtend in SPV_OPERAND_TYPE_IMAGE
  {IR(21370, 14), 854}, // 932 VolatileTexel in SPV_OPERAND_TYPE_IMAGE
  {IR(21384, 17), 854}, // 933 VolatileTexelKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(21412, 11), 856}, // 934 ZeroExtend in SPV_OPERAND_TYPE_IMAGE
  {IR(14101, 6), 873}, // 935 Float in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21604, 10), 872}, // 936 HalfFloat in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21539, 12), 867}, // 937 SignedInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21551, 12), 868}, // 938 SignedInt32 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21528, 11), 866}, // 939 SignedInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21453, 11), 860}, // 940 SnormInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21443, 10), 859}, // 941 SnormInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21513, 15), 865}, // 942 UnormInt101010 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21625, 17), 875}, // 943 UnormInt101010_2 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21642, 16), 876}, // 944 UnormInt10X6EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21775, 16), 883}, // 945 UnormInt12X4EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21791, 16), 884}, // 946 UnormInt14X2EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21474, 11), 862}, // 947 UnormInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21614, 11), 874}, // 948 UnormInt24 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21698, 20), 879}, // 949 UnormInt2_101010EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21464, 10), 861}, // 950 UnormInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21499, 14), 864}, // 951 UnormShort555 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21485, 14), 863}, // 952 UnormShort565 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21718, 19), 880}, // 953 UnsignedInt10X6EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21737, 19), 881}, // 954 UnsignedInt12X4EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21756, 19), 882}, // 955 UnsignedInt14X2EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21576, 14), 870}, // 956 UnsignedInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21590, 14), 871}, // 957 UnsignedInt32 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21563, 13), 869}, // 958 UnsignedInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21658, 20), 877}, // 959 UnsignedIntRaw10EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21678, 20), 878}, // 960 UnsignedIntRaw12EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21809, 2), 886}, // 961 A in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21910, 5), 904}, // 962 ABGR in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21831, 5), 892}, // 963 ARGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21826, 5), 891}, // 964 BGRA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21868, 6), 898}, // 965 Depth in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21874, 13), 899}, // 966 DepthStencil in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21836, 10), 893}, // 967 Intensity in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21846, 10), 894}, // 968 Luminance in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21807, 2), 885}, // 969 R in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21814, 3), 888}, // 970 RA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21811, 3), 887}, // 971 RG in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21817, 4), 889}, // 972 RGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21821, 5), 890}, // 973 RGBA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21863, 5), 897}, // 974 RGBx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21859, 4), 896}, // 975 RGx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21856, 3), 895}, // 976 Rx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21904, 6), 903}, // 977 sBGRA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21887, 5), 900}, // 978 sRGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21898, 6), 902}, // 979 sRGBA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21892, 6), 901}, // 980 sRGBx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21915, 27), 905}, // 981 InitOnDeviceReprogramINTEL in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(21942, 23), 906}, // 982 InitOnDeviceResetINTEL in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(21965, 7), 907}, // 983 NoWait in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(21972, 11), 908}, // 984 WaitKernel in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(21983, 14), 909}, // 985 WaitWorkGroup in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(21997, 12), 911}, // 986 CmdExecTime in SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {IR(14204, 5), 910}, // 987 None in SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {IR(22009, 13), 913}, // 988 MayUsePrintf in SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {IR(14204, 5), 912}, // 989 None in SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {IR(22022, 7), 914}, // 990 Export in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(22029, 7), 915}, // 991 Import in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(22036, 12), 916}, // 992 LinkOnceODR in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(22062, 12), 918}, // 993 CachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(22114, 17), 921}, // 994 ConstCachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(22089, 25), 920}, // 995 InvalidateAfterReadINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(22074, 15), 919}, // 996 StreamingINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(22048, 14), 917}, // 997 UncachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(22254, 21), 934}, // 998 DependencyArrayINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22149, 19), 925}, // 999 DependencyInfinite in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22168, 17), 926}, // 1000 DependencyLength in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22138, 11), 924}, // 1001 DontUnroll in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(17478, 24), 932}, // 1002 InitiationIntervalINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22213, 18), 929}, // 1003 IterationMultiple in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22275, 18), 936}, // 1004 LoopCoalesceINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22354, 15), 940}, // 1005 LoopCountINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(17502, 20), 933}, // 1006 MaxConcurrencyINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22293, 21), 937}, // 1007 MaxInterleavingINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22199, 14), 928}, // 1008 MaxIterations in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22369, 26), 941}, // 1009 MaxReinvocationDelayINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22185, 14), 927}, // 1010 MinIterations in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22340, 14), 939}, // 1011 NoFusionINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(14204, 5), 922}, // 1012 None in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22241, 13), 931}, // 1013 PartialCount in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22231, 10), 930}, // 1014 PeelCount in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(17522, 20), 935}, // 1015 PipelineEnableINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22314, 26), 938}, // 1016 SpeculatedIterationsINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22131, 7), 923}, // 1017 Unroll in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22678, 27), 955}, // 1018 MatrixAPackedBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22626, 26), 953}, // 1019 MatrixAPackedFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22546, 23), 949}, // 1020 MatrixAPackedInt4INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22500, 23), 947}, // 1021 MatrixAPackedInt8INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22395, 29), 943}, // 1022 MatrixASignedComponentsINTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22592, 17), 951}, // 1023 MatrixATF32INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22705, 27), 956}, // 1024 MatrixBPackedBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22652, 26), 954}, // 1025 MatrixBPackedFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22569, 23), 950}, // 1026 MatrixBPackedInt4INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22523, 23), 948}, // 1027 MatrixBPackedInt8INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22424, 29), 944}, // 1028 MatrixBSignedComponentsINTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22609, 17), 952}, // 1029 MatrixBTF32INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22453, 21), 945}, // 1030 MatrixCBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22474, 26), 946}, // 1031 MatrixResultBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(14204, 5), 942}, // 1032 None in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22865, 20), 964}, // 1033 AliasScopeINTELMask in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22732, 8), 959}, // 1034 Aligned in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22740, 21), 961}, // 1035 MakePointerAvailable in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22761, 24), 961}, // 1036 MakePointerAvailableKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22785, 19), 962}, // 1037 MakePointerVisible in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22804, 22), 962}, // 1038 MakePointerVisibleKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22885, 17), 965}, // 1039 NoAliasINTELMask in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22826, 18), 963}, // 1040 NonPrivatePointer in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22844, 21), 963}, // 1041 NonPrivatePointerKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(14204, 5), 957}, // 1042 None in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(21423, 12), 960}, // 1043 Nontemporal in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(15442, 9), 958}, // 1044 Volatile in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22909, 8), 967}, // 1045 GLSL450 in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(22917, 7), 968}, // 1046 OpenCL in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(22902, 7), 966}, // 1047 Simple in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(22924, 7), 969}, // 1048 Vulkan in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(22931, 10), 969}, // 1049 VulkanKHR in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(22949, 8), 971}, // 1050 Acquire in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22965, 15), 973}, // 1051 AcquireRelease in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(23069, 20), 979}, // 1052 AtomicCounterMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(23048, 21), 978}, // 1053 CrossWorkgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(23089, 12), 980}, // 1054 ImageMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(23130, 14), 982}, // 1055 MakeAvailable in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(23144, 17), 982}, // 1056 MakeAvailableKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(23161, 12), 983}, // 1057 MakeVisible in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(23173, 15), 983}, // 1058 MakeVisibleKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(14204, 5), 970}, // 1059 None in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(23101, 13), 981}, // 1060 OutputMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(23114, 16), 981}, // 1061 OutputMemoryKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22941, 8), 970}, // 1062 Relaxed in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22957, 8), 972}, // 1063 Release in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22980, 23), 974}, // 1064 SequentiallyConsistent in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(23017, 15), 976}, // 1065 SubgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(23003, 14), 975}, // 1066 UniformMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(15442, 9), 984}, // 1067 Volatile in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(23032, 16), 977}, // 1068 WorkgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(23188, 10), 985}, // 1069 AutoINTEL in SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS
  {IR(23203, 4), 987}, // 1070 SAT in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(23216, 8), 989}, // 1071 SAT_SYM in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(23207, 9), 988}, // 1072 SAT_ZERO in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(23198, 5), 986}, // 1073 WRAP in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(23224, 25), 990}, // 1074 PackedVectorFormat4x8Bit in SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {IR(23249, 28), 990}, // 1075 PackedVectorFormat4x8BitKHR in SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {IR(23290, 4), 993}, // 1076 RND in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(23323, 9), 997}, // 1077 RND_CONV in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(23332, 13), 998}, // 1078 RND_CONV_ODD in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(23303, 8), 995}, // 1079 RND_INF in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(23311, 12), 996}, // 1080 RND_MIN_INF in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(23294, 9), 994}, // 1081 RND_ZERO in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(23277, 4), 991}, // 1082 TRN in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(23281, 9), 992}, // 1083 TRN_ZERO in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(14204, 5), 999}, // 1084 None in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(23345, 25), 1000}, // 1085 RobustnessPerComponentNV in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(23370, 23), 1001}, // 1086 RobustnessPerElementNV in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(23462, 27), 1007}, // 1087 CullBackFacingTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23489, 28), 1008}, // 1088 CullFrontFacingTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23531, 16), 1010}, // 1089 CullNoOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23517, 14), 1009}, // 1090 CullOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23601, 30), 1013}, // 1091 ForceOpacityMicromap2StateEXT in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23403, 12), 1004}, // 1092 NoOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(14956, 8), 1002}, // 1093 NoneKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23393, 10), 1003}, // 1094 OpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23588, 13), 1012}, // 1095 SkipAABBsKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23564, 24), 1011}, // 1096 SkipBuiltinPrimitivesNV in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23438, 24), 1006}, // 1097 SkipClosestHitShaderKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23547, 17), 1011}, // 1098 SkipTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23415, 23), 1005}, // 1099 TerminateOnFirstHitKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23672, 37), 1015}, // 1100 RayQueryCandidateIntersectionAABBKHR in SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {IR(23631, 41), 1014}, // 1101 RayQueryCandidateIntersectionTriangleKHR in SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {IR(23787, 42), 1018}, // 1102 RayQueryCommittedIntersectionGeneratedKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(23709, 37), 1016}, // 1103 RayQueryCommittedIntersectionNoneKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(23746, 41), 1017}, // 1104 RayQueryCommittedIntersectionTriangleKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(23829, 33), 1019}, // 1105 RayQueryCandidateIntersectionKHR in SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {IR(23862, 33), 1020}, // 1106 RayQueryCommittedIntersectionKHR in SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {IR(23907, 6), 1023}, // 1107 Clamp in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(23895, 12), 1022}, // 1108 ClampToEdge in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(14204, 5), 1021}, // 1109 None in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(23913, 7), 1024}, // 1110 Repeat in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(23920, 15), 1025}, // 1111 RepeatMirrored in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(23943, 7), 1027}, // 1112 Linear in SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {IR(23935, 8), 1026}, // 1113 Nearest in SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {IR(24008, 13), 1036}, // 1114 R11fG11fB10f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24050, 4), 1042}, // 1115 R16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24088, 9), 1047}, // 1116 R16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24021, 5), 1037}, // 1117 R16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24150, 5), 1056}, // 1118 R16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24221, 6), 1066}, // 1119 R16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23974, 5), 1031}, // 1120 R32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24128, 5), 1052}, // 1121 R32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24185, 6), 1061}, // 1122 R32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24238, 5), 1069}, // 1123 R64i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24232, 6), 1068}, // 1124 R64ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24054, 3), 1043}, // 1125 R8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24097, 8), 1048}, // 1126 R8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24155, 4), 1057}, // 1127 R8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24227, 5), 1067}, // 1128 R8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24041, 5), 1040}, // 1129 Rg16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24069, 10), 1045}, // 1130 Rg16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24002, 6), 1035}, // 1131 Rg16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24139, 6), 1054}, // 1132 Rg16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24208, 7), 1064}, // 1133 Rg16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23996, 6), 1034}, // 1134 Rg32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24133, 6), 1053}, // 1135 Rg32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24201, 7), 1063}, // 1136 Rg32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24046, 4), 1041}, // 1137 Rg8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24079, 9), 1046}, // 1138 Rg8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24145, 5), 1055}, // 1139 Rg8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24215, 6), 1065}, // 1140 Rg8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24033, 8), 1039}, // 1141 Rgb10A2 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24191, 10), 1062}, // 1142 Rgb10a2ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24026, 7), 1038}, // 1143 Rgba16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24057, 12), 1044}, // 1144 Rgba16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23966, 8), 1030}, // 1145 Rgba16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24113, 8), 1050}, // 1146 Rgba16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24168, 9), 1059}, // 1147 Rgba16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23958, 8), 1029}, // 1148 Rgba32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24105, 8), 1049}, // 1149 Rgba32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24159, 9), 1058}, // 1150 Rgba32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23979, 6), 1032}, // 1151 Rgba8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23985, 11), 1033}, // 1152 Rgba8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24121, 7), 1051}, // 1153 Rgba8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24177, 8), 1060}, // 1154 Rgba8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23950, 8), 1028}, // 1155 Unknown in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24243, 12), 1070}, // 1156 CrossDevice in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(24255, 7), 1071}, // 1157 Device in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(24281, 11), 1074}, // 1158 Invocation in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(24292, 12), 1075}, // 1159 QueueFamily in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(24304, 15), 1075}, // 1160 QueueFamilyKHR in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(24319, 14), 1076}, // 1161 ShaderCallKHR in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(24272, 9), 1073}, // 1162 Subgroup in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(24262, 10), 1072}, // 1163 Workgroup in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(24341, 12), 1079}, // 1164 DontFlatten in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(24333, 8), 1078}, // 1165 Flatten in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(14204, 5), 1077}, // 1166 None in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(24353, 29), 1080}, // 1167 IdentifierPossibleDuplicates in SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS
  {IR(14085, 8), 1082}, // 1168 Address in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14093, 8), 1083}, // 1169 Boolean in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14101, 6), 1084}, // 1170 Float in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14107, 7), 1085}, // 1171 Signed in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14114, 11), 1086}, // 1172 SignedChar in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14125, 9), 1087}, // 1173 Unsigned in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14134, 13), 1088}, // 1174 UnsignedChar in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14073, 12), 1081}, // 1175 Unspecified in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14147, 6), 1089}, // 1176 Class in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(14153, 10), 1090}, // 1177 Structure in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(14163, 6), 1091}, // 1178 Union in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(14184, 20), 1093}, // 1179 ImportedDeclaration in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(14169, 15), 1092}, // 1180 ImportedModule in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(14293, 15), 1101}, // 1181 FlagArtificial in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14308, 13), 1102}, // 1182 FlagExplicit in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14281, 12), 1100}, // 1183 FlagFwdDecl in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14371, 21), 1106}, // 1184 FlagIndirectVariable in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14264, 17), 1099}, // 1185 FlagIsDefinition in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14448, 16), 1110}, // 1186 FlagIsEnumClass in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14252, 12), 1098}, // 1187 FlagIsLocal in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14432, 16), 1109}, // 1188 FlagIsOptimized in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14225, 14), 1096}, // 1189 FlagIsPrivate in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14209, 16), 1095}, // 1190 FlagIsProtected in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14239, 13), 1097}, // 1191 FlagIsPublic in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14392, 20), 1107}, // 1192 FlagLValueReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14336, 18), 1104}, // 1193 FlagObjectPointer in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14321, 15), 1103}, // 1194 FlagPrototyped in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14412, 20), 1108}, // 1195 FlagRValueReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14354, 17), 1105}, // 1196 FlagStaticMember in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14484, 24), 1112}, // 1197 FlagTypePassByReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14464, 20), 1111}, // 1198 FlagTypePassByValue in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(24382, 26), 1113}, // 1199 FlagUnknownPhysicalLayout in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14204, 5), 1094}, // 1200 None in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14569, 9), 1118}, // 1201 BitPiece in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14601, 7), 1122}, // 1202 Constu in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14508, 6), 1114}, // 1203 Deref in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14608, 9), 1123}, // 1204 Fragment in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14519, 6), 1116}, // 1205 Minus in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14514, 5), 1115}, // 1206 Plus in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14558, 11), 1117}, // 1207 PlusUconst in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14590, 11), 1121}, // 1208 StackValue in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14578, 5), 1119}, // 1209 Swap in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14583, 7), 1120}, // 1210 Xderef in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14653, 11), 1127}, // 1211 AtomicType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14617, 10), 1124}, // 1212 ConstType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14640, 13), 1126}, // 1213 RestrictType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14627, 13), 1125}, // 1214 VolatileType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(24443, 15), 1134}, // 1215 CPP_for_OpenCL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24408, 5), 1129}, // 1216 ESSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24413, 5), 1130}, // 1217 GLSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24463, 7), 1136}, // 1218 HERO_C in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24438, 5), 1133}, // 1219 HLSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24470, 5), 1137}, // 1220 NZSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24418, 9), 1131}, // 1221 OpenCL_C in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24427, 11), 1132}, // 1222 OpenCL_CPP in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24490, 5), 1141}, // 1223 Rust in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24458, 5), 1135}, // 1224 SYCL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24480, 6), 1139}, // 1225 Slang in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(23950, 8), 1128}, // 1226 Unknown in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24475, 5), 1138}, // 1227 WGSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24486, 4), 1140}, // 1228 Zig in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24577, 14), 1152}, // 1229 AtomicCounter in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24659, 16), 1158}, // 1230 CallableDataKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24675, 15), 1158}, // 1231 CallableDataNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24973, 17), 1167}, // 1232 CodeSectionINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24524, 15), 1147}, // 1233 CrossWorkgroup in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24990, 16), 1168}, // 1234 DeviceOnlyINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24547, 9), 1149}, // 1235 Function in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24556, 8), 1150}, // 1236 Generic in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24764, 16), 1161}, // 1237 HitAttributeKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24780, 15), 1161}, // 1238 HitAttributeNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24928, 21), 1165}, // 1239 HitObjectAttributeNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(25006, 14), 1169}, // 1240 HostOnlyINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24591, 6), 1153}, // 1241 Image in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24690, 24), 1159}, // 1242 IncomingCallableDataKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24714, 23), 1159}, // 1243 IncomingCallableDataNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24795, 22), 1162}, // 1244 IncomingRayPayloadKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24817, 21), 1162}, // 1245 IncomingRayPayloadNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24511, 6), 1143}, // 1246 Input in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24643, 16), 1157}, // 1247 NodePayloadAMDX in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24517, 7), 1145}, // 1248 Output in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24881, 22), 1164}, // 1249 PhysicalStorageBuffer in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24903, 25), 1164}, // 1250 PhysicalStorageBufferEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24539, 8), 1148}, // 1251 Private in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24564, 13), 1151}, // 1252 PushConstant in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24737, 14), 1160}, // 1253 RayPayloadKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24751, 13), 1160}, // 1254 RayPayloadNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24838, 22), 1163}, // 1255 ShaderRecordBufferKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24860, 21), 1163}, // 1256 ShaderRecordBufferNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24597, 14), 1154}, // 1257 StorageBuffer in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24949, 24), 1166}, // 1258 TaskPayloadWorkgroupEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24624, 19), 1156}, // 1259 TileAttachmentQCOM in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24611, 13), 1155}, // 1260 TileImageEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(15493, 8), 1144}, // 1261 Uniform in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24495, 16), 1142}, // 1262 UniformConstant in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24262, 10), 1146}, // 1263 Workgroup in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(22074, 15), 1173}, // 1264 StreamingINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(22048, 14), 1170}, // 1265 UncachedINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(25038, 15), 1172}, // 1266 WriteBackINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(25020, 18), 1171}, // 1267 WriteThroughINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(25064, 11), 1176}, // 1268 DecodeFunc in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(14204, 5), 1174}, // 1269 None in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(25053, 11), 1175}, // 1270 TensorView in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(23895, 12), 1179}, // 1271 ClampToEdge in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(15451, 9), 1178}, // 1272 Constant in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(23913, 7), 1180}, // 1273 Repeat in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(23920, 15), 1181}, // 1274 RepeatMirrored in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(25075, 10), 1177}, // 1275 Undefined in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(25128, 24), 1185}, // 1276 MakeElementAvailableARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(25152, 22), 1186}, // 1277 MakeElementVisibleARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(25174, 21), 1187}, // 1278 NonPrivateElementARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(25085, 8), 1182}, // 1279 NoneARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(25093, 15), 1183}, // 1280 NontemporalARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(25108, 20), 1184}, // 1281 OutOfBoundsValueARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
}};

IndexRange OperandNameRangeForKind(spv_operand_type_t type) {
  switch(type) {
    case SPV_OPERAND_TYPE_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_ADDRESSING_MODEL: return IR(3, 5);
    case SPV_OPERAND_TYPE_BUILT_IN: return IR(8, 148);
    case SPV_OPERAND_TYPE_CAPABILITY: return IR(156, 302);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(458, 8);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(466, 3);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(469, 2);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS: return IR(471, 19);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION: return IR(490, 10);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(500, 4);
    case SPV_OPERAND_TYPE_COMPONENT_TYPE: return IR(504, 15);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT: return IR(519, 4);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS: return IR(523, 6);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE: return IR(529, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE: return IR(532, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT: return IR(535, 4);
    case SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(539, 8);
    case SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE: return IR(547, 3);
    case SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS: return IR(550, 16);
    case SPV_OPERAND_TYPE_DEBUG_OPERATION: return IR(566, 9);
    case SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER: return IR(575, 3);
    case SPV_OPERAND_TYPE_DECORATION: return IR(578, 151);
    case SPV_OPERAND_TYPE_DIMENSIONALITY: return IR(729, 8);
    case SPV_OPERAND_TYPE_EXECUTION_MODE: return IR(737, 101);
    case SPV_OPERAND_TYPE_EXECUTION_MODEL: return IR(838, 23);
    case SPV_OPERAND_TYPE_FPDENORM_MODE: return IR(861, 2);
    case SPV_OPERAND_TYPE_FPENCODING: return IR(863, 3);
    case SPV_OPERAND_TYPE_FPOPERATION_MODE: return IR(866, 2);
    case SPV_OPERAND_TYPE_FP_FAST_MATH_MODE: return IR(868, 11);
    case SPV_OPERAND_TYPE_FP_ROUNDING_MODE: return IR(879, 4);
    case SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE: return IR(883, 4);
    case SPV_OPERAND_TYPE_FUNCTION_CONTROL: return IR(887, 7);
    case SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE: return IR(894, 9);
    case SPV_OPERAND_TYPE_GROUP_OPERATION: return IR(903, 7);
    case SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER: return IR(910, 4);
    case SPV_OPERAND_TYPE_IMAGE: return IR(914, 21);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE: return IR(935, 26);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER: return IR(961, 20);
    case SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER: return IR(981, 2);
    case SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS: return IR(983, 3);
    case SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO: return IR(986, 2);
    case SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS: return IR(988, 2);
    case SPV_OPERAND_TYPE_LINKAGE_TYPE: return IR(990, 3);
    case SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL: return IR(993, 5);
    case SPV_OPERAND_TYPE_LOOP_CONTROL: return IR(998, 20);
    case SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(1018, 15);
    case SPV_OPERAND_TYPE_MEMORY_ACCESS: return IR(1033, 12);
    case SPV_OPERAND_TYPE_MEMORY_MODEL: return IR(1045, 5);
    case SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID: return IR(1050, 19);
    case SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS: return IR(1069, 1);
    case SPV_OPERAND_TYPE_OVERFLOW_MODES: return IR(1070, 4);
    case SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT: return IR(1074, 2);
    case SPV_OPERAND_TYPE_QUANTIZATION_MODES: return IR(1076, 8);
    case SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS: return IR(1084, 3);
    case SPV_OPERAND_TYPE_RAY_FLAGS: return IR(1087, 13);
    case SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE: return IR(1100, 2);
    case SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE: return IR(1102, 3);
    case SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION: return IR(1105, 2);
    case SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE: return IR(1107, 5);
    case SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE: return IR(1112, 2);
    case SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT: return IR(1114, 42);
    case SPV_OPERAND_TYPE_SCOPE_ID: return IR(1156, 8);
    case SPV_OPERAND_TYPE_SELECTION_CONTROL: return IR(1164, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS: return IR(1167, 1);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(1168, 8);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(1176, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(1179, 2);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS: return IR(1181, 20);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION: return IR(1201, 10);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(1211, 4);
    case SPV_OPERAND_TYPE_SOURCE_LANGUAGE: return IR(1215, 14);
    case SPV_OPERAND_TYPE_STORAGE_CLASS: return IR(1229, 35);
    case SPV_OPERAND_TYPE_STORE_CACHE_CONTROL: return IR(1264, 4);
    case SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS: return IR(1268, 3);
    case SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE: return IR(1271, 5);
    case SPV_OPERAND_TYPE_TENSOR_OPERANDS: return IR(1276, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_IMAGE: return IR(914, 21);
    case SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS: return IR(1033, 12);
    case SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT: return IR(1074, 2);
    case SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS: return IR(523, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(1018, 15);
    case SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS: return IR(1084, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_FPENCODING: return IR(863, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS: return IR(1276, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_CAPABILITY: return IR(156, 302);
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
static const std::array<InstructionDesc, 821> kInstructionDesc{{
  {spv::Op::OpNop, false, false, IR(0, 0), IR(25195, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpUndef, true, true, IR(39, 2), IR(25251, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpSourceContinued, false, false, IR(11, 1), IR(25257, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpSource, false, false, IR(41, 4), IR(25376, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpSourceExtension, false, false, IR(11, 1), IR(25383, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpName, false, false, IR(45, 2), IR(25399, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpMemberName, false, false, IR(47, 3), IR(25404, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpString, true, false, IR(50, 2), IR(25415, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpLine, false, false, IR(52, 3), IR(25422, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpExtension, false, false, IR(11, 1), IR(25427, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpExtInstImport, true, false, IR(50, 2), IR(25437, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpExtInst, true, true, IR(55, 4), IR(25497, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpMemoryModel, false, false, IR(59, 2), IR(25569, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpEntryPoint, false, false, IR(61, 4), IR(25643, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpExecutionMode, false, false, IR(65, 2), IR(25686, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpCapability, false, false, IR(67, 1), IR(25728, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpTypeVoid, true, false, IR(68, 1), IR(25739, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeBool, true, false, IR(68, 1), IR(25748, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeInt, true, false, IR(69, 3), IR(25757, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeFloat, true, false, IR(72, 3), IR(25802, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeVector, true, false, IR(75, 3), IR(25812, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeMatrix, true, false, IR(75, 3), IR(25823, 11), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeImage, true, false, IR(78, 9), IR(25947, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeSampler, true, false, IR(68, 1), IR(25957, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeSampledImage, true, false, IR(87, 2), IR(25969, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeArray, true, false, IR(89, 3), IR(25986, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeRuntimeArray, true, false, IR(87, 2), IR(25996, 17), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeStruct, true, false, IR(92, 2), IR(26013, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeOpaque, true, false, IR(50, 2), IR(26024, 11), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypePointer, true, false, IR(94, 3), IR(26066, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeFunction, true, false, IR(97, 3), IR(26078, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeEvent, true, false, IR(68, 1), IR(26091, 10), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeDeviceEvent, true, false, IR(68, 1), IR(26101, 16), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeReserveId, true, false, IR(68, 1), IR(26117, 14), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeQueue, true, false, IR(68, 1), IR(26131, 10), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypePipe, true, false, IR(100, 2), IR(26141, 9), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeForwardPointer, false, false, IR(102, 2), IR(26150, 19), IR(0, 0), IR(203, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantTrue, true, true, IR(39, 2), IR(26169, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantFalse, true, true, IR(39, 2), IR(26182, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstant, true, true, IR(104, 3), IR(15451, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantComposite, true, true, IR(107, 3), IR(26234, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantSampler, true, true, IR(110, 5), IR(26330, 16), IR(0, 0), IR(205, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantNull, true, true, IR(39, 2), IR(26346, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantTrue, true, true, IR(39, 2), IR(26359, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantFalse, true, true, IR(39, 2), IR(26376, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstant, true, true, IR(104, 3), IR(26394, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantComposite, true, true, IR(107, 3), IR(26407, 22), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantOp, true, true, IR(115, 3), IR(26470, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpFunction, true, true, IR(118, 4), IR(24547, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionParameter, true, true, IR(39, 2), IR(26519, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionEnd, false, false, IR(0, 0), IR(26537, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionCall, true, true, IR(122, 4), IR(26549, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpVariable, true, true, IR(126, 4), IR(26562, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpImageTexelPointer, true, true, IR(130, 5), IR(26571, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpLoad, true, true, IR(135, 4), IR(26629, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpStore, false, false, IR(139, 3), IR(26634, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCopyMemory, false, false, IR(142, 4), IR(26640, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCopyMemorySized, false, false, IR(146, 5), IR(26651, 16), IR(0, 0), IR(206, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpAccessChain, true, true, IR(122, 4), IR(26667, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpInBoundsAccessChain, true, true, IR(122, 4), IR(26679, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrAccessChain, true, true, IR(151, 5), IR(26699, 15), IR(0, 0), IR(208, 4), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpArrayLength, true, true, IR(156, 4), IR(26714, 12), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpGenericPtrMemSemantics, true, true, IR(160, 3), IR(26726, 23), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpInBoundsPtrAccessChain, true, true, IR(151, 5), IR(26749, 23), IR(0, 0), IR(1, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpDecorate, false, false, IR(163, 2), IR(26800, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpMemberDecorate, false, false, IR(165, 3), IR(26809, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpDecorationGroup, true, false, IR(68, 1), IR(26824, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupDecorate, false, false, IR(168, 2), IR(26840, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupMemberDecorate, false, false, IR(170, 2), IR(26899, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpVectorExtractDynamic, true, true, IR(172, 4), IR(26919, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpVectorInsertDynamic, true, true, IR(130, 5), IR(26940, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpVectorShuffle, true, true, IR(176, 5), IR(26960, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeConstruct, true, true, IR(107, 3), IR(26974, 19), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeExtract, true, true, IR(181, 4), IR(26993, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeInsert, true, true, IR(176, 5), IR(27010, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCopyObject, true, true, IR(160, 3), IR(27026, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpTranspose, true, true, IR(160, 3), IR(27037, 10), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpSampledImage, true, true, IR(172, 4), IR(27047, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleImplicitLod, true, true, IR(185, 5), IR(27092, 23), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleExplicitLod, true, true, IR(190, 5), IR(27138, 23), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleDrefImplicitLod, true, true, IR(195, 6), IR(27161, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleDrefExplicitLod, true, true, IR(201, 6), IR(27188, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjImplicitLod, true, true, IR(185, 5), IR(27215, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjExplicitLod, true, true, IR(190, 5), IR(27242, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjDrefImplicitLod, true, true, IR(195, 6), IR(27269, 31), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjDrefExplicitLod, true, true, IR(201, 6), IR(27300, 31), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageFetch, true, true, IR(185, 5), IR(27331, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageGather, true, true, IR(195, 6), IR(27342, 12), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageDrefGather, true, true, IR(195, 6), IR(27354, 16), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageRead, true, true, IR(185, 5), IR(27370, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageWrite, false, false, IR(207, 4), IR(27380, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImage, true, true, IR(160, 3), IR(24591, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryFormat, true, true, IR(160, 3), IR(27391, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryOrder, true, true, IR(160, 3), IR(27408, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySizeLod, true, true, IR(172, 4), IR(27424, 18), IR(0, 0), IR(212, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySize, true, true, IR(160, 3), IR(27442, 15), IR(0, 0), IR(212, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryLod, true, true, IR(172, 4), IR(27457, 14), IR(0, 0), IR(214, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryLevels, true, true, IR(160, 3), IR(27471, 17), IR(0, 0), IR(212, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySamples, true, true, IR(160, 3), IR(27488, 18), IR(0, 0), IR(212, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertFToU, true, true, IR(160, 3), IR(27506, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertFToS, true, true, IR(160, 3), IR(27518, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertSToF, true, true, IR(160, 3), IR(27530, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToF, true, true, IR(160, 3), IR(27542, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpUConvert, true, true, IR(160, 3), IR(27554, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSConvert, true, true, IR(160, 3), IR(27563, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpFConvert, true, true, IR(160, 3), IR(27572, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpQuantizeToF16, true, true, IR(160, 3), IR(27581, 14), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertPtrToU, true, true, IR(160, 3), IR(27595, 14), IR(0, 0), IR(203, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSatConvertSToU, true, true, IR(160, 3), IR(27609, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSatConvertUToS, true, true, IR(160, 3), IR(27624, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToPtr, true, true, IR(160, 3), IR(27639, 14), IR(0, 0), IR(203, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpPtrCastToGeneric, true, true, IR(160, 3), IR(27653, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpGenericCastToPtr, true, true, IR(160, 3), IR(27670, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpGenericCastToPtrExplicit, true, true, IR(211, 4), IR(27687, 25), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpBitcast, true, true, IR(160, 3), IR(27712, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSNegate, true, true, IR(160, 3), IR(27720, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFNegate, true, true, IR(160, 3), IR(27728, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIAdd, true, true, IR(172, 4), IR(27736, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFAdd, true, true, IR(172, 4), IR(27741, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpISub, true, true, IR(172, 4), IR(27746, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFSub, true, true, IR(172, 4), IR(27751, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIMul, true, true, IR(172, 4), IR(27756, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFMul, true, true, IR(172, 4), IR(27761, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDiv, true, true, IR(172, 4), IR(27766, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSDiv, true, true, IR(172, 4), IR(27771, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFDiv, true, true, IR(172, 4), IR(27776, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUMod, true, true, IR(172, 4), IR(27781, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSRem, true, true, IR(172, 4), IR(27786, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSMod, true, true, IR(172, 4), IR(27791, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFRem, true, true, IR(172, 4), IR(27796, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFMod, true, true, IR(172, 4), IR(27801, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpVectorTimesScalar, true, true, IR(172, 4), IR(27806, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesScalar, true, true, IR(172, 4), IR(27824, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpVectorTimesMatrix, true, true, IR(172, 4), IR(27842, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesVector, true, true, IR(172, 4), IR(27860, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesMatrix, true, true, IR(172, 4), IR(27878, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpOuterProduct, true, true, IR(172, 4), IR(27896, 13), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpDot, true, true, IR(172, 4), IR(27909, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIAddCarry, true, true, IR(172, 4), IR(27913, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpISubBorrow, true, true, IR(172, 4), IR(27923, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUMulExtended, true, true, IR(172, 4), IR(27934, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSMulExtended, true, true, IR(172, 4), IR(27947, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpAny, true, true, IR(160, 3), IR(27960, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpAll, true, true, IR(160, 3), IR(27964, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsNan, true, true, IR(160, 3), IR(27968, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsInf, true, true, IR(160, 3), IR(27974, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsFinite, true, true, IR(160, 3), IR(27980, 9), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsNormal, true, true, IR(160, 3), IR(27989, 9), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSignBitSet, true, true, IR(160, 3), IR(27998, 11), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLessOrGreater, true, true, IR(172, 4), IR(28009, 14), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), SPV_SPIRV_VERSION_WORD(1,5), PrintingClass::kRelational_and_Logical},
  {spv::Op::OpOrdered, true, true, IR(172, 4), IR(28023, 8), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUnordered, true, true, IR(172, 4), IR(28031, 10), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalEqual, true, true, IR(172, 4), IR(28041, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalNotEqual, true, true, IR(172, 4), IR(28054, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalOr, true, true, IR(172, 4), IR(28070, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalAnd, true, true, IR(172, 4), IR(28080, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalNot, true, true, IR(160, 3), IR(28091, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSelect, true, true, IR(130, 5), IR(28102, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIEqual, true, true, IR(172, 4), IR(28109, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpINotEqual, true, true, IR(172, 4), IR(28116, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUGreaterThan, true, true, IR(172, 4), IR(28126, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSGreaterThan, true, true, IR(172, 4), IR(28139, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUGreaterThanEqual, true, true, IR(172, 4), IR(28152, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSGreaterThanEqual, true, true, IR(172, 4), IR(28170, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpULessThan, true, true, IR(172, 4), IR(28188, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSLessThan, true, true, IR(172, 4), IR(28198, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpULessThanEqual, true, true, IR(172, 4), IR(28208, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSLessThanEqual, true, true, IR(172, 4), IR(28223, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdEqual, true, true, IR(172, 4), IR(28238, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordEqual, true, true, IR(172, 4), IR(28248, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdNotEqual, true, true, IR(172, 4), IR(28260, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordNotEqual, true, true, IR(172, 4), IR(28273, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdLessThan, true, true, IR(172, 4), IR(28288, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordLessThan, true, true, IR(172, 4), IR(28301, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdGreaterThan, true, true, IR(172, 4), IR(28316, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordGreaterThan, true, true, IR(172, 4), IR(28332, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdLessThanEqual, true, true, IR(172, 4), IR(28350, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordLessThanEqual, true, true, IR(172, 4), IR(28368, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdGreaterThanEqual, true, true, IR(172, 4), IR(28388, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordGreaterThanEqual, true, true, IR(172, 4), IR(28409, 23), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpShiftRightLogical, true, true, IR(172, 4), IR(28432, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpShiftRightArithmetic, true, true, IR(172, 4), IR(28450, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpShiftLeftLogical, true, true, IR(172, 4), IR(28471, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseOr, true, true, IR(172, 4), IR(28488, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseXor, true, true, IR(172, 4), IR(28498, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseAnd, true, true, IR(172, 4), IR(28509, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpNot, true, true, IR(160, 3), IR(28520, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldInsert, true, true, IR(215, 6), IR(28524, 15), IR(0, 0), IR(215, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldSExtract, true, true, IR(130, 5), IR(28539, 17), IR(0, 0), IR(215, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldUExtract, true, true, IR(130, 5), IR(28556, 17), IR(0, 0), IR(215, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitReverse, true, true, IR(160, 3), IR(28573, 11), IR(0, 0), IR(215, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitCount, true, true, IR(160, 3), IR(28584, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpDPdx, true, true, IR(160, 3), IR(28593, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdy, true, true, IR(160, 3), IR(28598, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidth, true, true, IR(160, 3), IR(28603, 7), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdxFine, true, true, IR(160, 3), IR(28610, 9), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdyFine, true, true, IR(160, 3), IR(28619, 9), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidthFine, true, true, IR(160, 3), IR(28628, 11), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdxCoarse, true, true, IR(160, 3), IR(28639, 11), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdyCoarse, true, true, IR(160, 3), IR(28650, 11), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidthCoarse, true, true, IR(160, 3), IR(28661, 13), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpEmitVertex, false, false, IR(0, 0), IR(28674, 11), IR(0, 0), IR(69, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEndPrimitive, false, false, IR(0, 0), IR(28685, 13), IR(0, 0), IR(69, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEmitStreamVertex, false, false, IR(10, 1), IR(28698, 17), IR(0, 0), IR(116, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEndStreamPrimitive, false, false, IR(10, 1), IR(28715, 19), IR(0, 0), IR(116, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpControlBarrier, false, false, IR(221, 3), IR(28771, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpMemoryBarrier, false, false, IR(224, 2), IR(28786, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpAtomicLoad, true, true, IR(226, 5), IR(28800, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicStore, false, false, IR(231, 4), IR(28811, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicExchange, true, true, IR(235, 6), IR(28823, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicCompareExchange, true, true, IR(241, 8), IR(28838, 22), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicCompareExchangeWeak, true, true, IR(241, 8), IR(28860, 26), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), SPV_SPIRV_VERSION_WORD(1,3), PrintingClass::kAtomic},
  {spv::Op::OpAtomicIIncrement, true, true, IR(226, 5), IR(28886, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicIDecrement, true, true, IR(226, 5), IR(28903, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicIAdd, true, true, IR(235, 6), IR(28920, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicISub, true, true, IR(235, 6), IR(28931, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicSMin, true, true, IR(235, 6), IR(28942, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicUMin, true, true, IR(235, 6), IR(28953, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicSMax, true, true, IR(235, 6), IR(28964, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicUMax, true, true, IR(235, 6), IR(28975, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicAnd, true, true, IR(235, 6), IR(28986, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicOr, true, true, IR(235, 6), IR(28996, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicXor, true, true, IR(235, 6), IR(29005, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpPhi, true, true, IR(107, 3), IR(29015, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLoopMerge, false, false, IR(249, 3), IR(29049, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpSelectionMerge, false, false, IR(252, 2), IR(29094, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLabel, true, false, IR(68, 1), IR(29109, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpBranch, false, false, IR(10, 1), IR(29115, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpBranchConditional, false, false, IR(254, 4), IR(29122, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpSwitch, false, false, IR(258, 3), IR(29185, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpKill, false, false, IR(0, 0), IR(29192, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpReturn, false, false, IR(0, 0), IR(29197, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpReturnValue, false, false, IR(10, 1), IR(29204, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpUnreachable, false, false, IR(0, 0), IR(29216, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLifetimeStart, false, false, IR(261, 2), IR(29228, 14), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLifetimeStop, false, false, IR(261, 2), IR(29242, 13), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpGroupAsyncCopy, true, true, IR(263, 8), IR(29255, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupWaitEvents, false, false, IR(271, 3), IR(29270, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupAll, true, true, IR(274, 4), IR(29286, 9), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupAny, true, true, IR(274, 4), IR(29295, 9), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBroadcast, true, true, IR(278, 5), IR(29304, 15), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupIAdd, true, true, IR(283, 5), IR(29352, 10), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFAdd, true, true, IR(283, 5), IR(29362, 10), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMin, true, true, IR(283, 5), IR(29372, 10), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMin, true, true, IR(283, 5), IR(29382, 10), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMin, true, true, IR(283, 5), IR(29392, 10), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMax, true, true, IR(283, 5), IR(29402, 10), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMax, true, true, IR(283, 5), IR(29412, 10), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMax, true, true, IR(283, 5), IR(29422, 10), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpReadPipe, true, true, IR(215, 6), IR(29432, 9), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpWritePipe, true, true, IR(215, 6), IR(29441, 10), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReservedReadPipe, true, true, IR(288, 8), IR(29451, 17), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReservedWritePipe, true, true, IR(288, 8), IR(29468, 18), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReserveReadPipePackets, true, true, IR(215, 6), IR(29486, 23), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReserveWritePipePackets, true, true, IR(215, 6), IR(29509, 24), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCommitReadPipe, false, false, IR(296, 4), IR(29533, 15), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCommitWritePipe, false, false, IR(296, 4), IR(29548, 16), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpIsValidReserveId, true, true, IR(160, 3), IR(29564, 17), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetNumPipePackets, true, true, IR(130, 5), IR(29581, 18), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetMaxPipePackets, true, true, IR(130, 5), IR(29599, 18), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupReserveReadPipePackets, true, true, IR(300, 7), IR(29617, 28), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupReserveWritePipePackets, true, true, IR(300, 7), IR(29645, 29), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupCommitReadPipe, false, false, IR(307, 5), IR(29674, 20), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupCommitWritePipe, false, false, IR(307, 5), IR(29694, 21), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpEnqueueMarker, true, true, IR(215, 6), IR(29715, 14), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpEnqueueKernel, true, true, IR(312, 13), IR(29729, 14), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelNDrangeSubGroupCount, true, true, IR(325, 7), IR(29743, 30), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelNDrangeMaxSubGroupSize, true, true, IR(325, 7), IR(29773, 32), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelWorkGroupSize, true, true, IR(215, 6), IR(29805, 23), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelPreferredWorkGroupSizeMultiple, true, true, IR(215, 6), IR(29828, 40), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpRetainEvent, false, false, IR(10, 1), IR(29868, 12), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpReleaseEvent, false, false, IR(10, 1), IR(29880, 13), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpCreateUserEvent, true, true, IR(39, 2), IR(29893, 16), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpIsValidEvent, true, true, IR(160, 3), IR(29909, 13), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpSetUserEventStatus, false, false, IR(36, 2), IR(29922, 19), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpCaptureEventProfilingInfo, false, false, IR(33, 3), IR(29941, 26), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetDefaultQueue, true, true, IR(39, 2), IR(29967, 16), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpBuildNDRange, true, true, IR(130, 5), IR(29983, 13), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpImageSparseSampleImplicitLod, true, true, IR(185, 5), IR(29996, 29), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleExplicitLod, true, true, IR(190, 5), IR(30025, 29), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleDrefImplicitLod, true, true, IR(195, 6), IR(30054, 33), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleDrefExplicitLod, true, true, IR(201, 6), IR(30087, 33), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjImplicitLod, true, true, IR(185, 5), IR(30120, 33), IR(0, 0), IR(219, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjExplicitLod, true, true, IR(190, 5), IR(30153, 33), IR(0, 0), IR(219, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjDrefImplicitLod, true, true, IR(195, 6), IR(30186, 37), IR(0, 0), IR(219, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjDrefExplicitLod, true, true, IR(201, 6), IR(30223, 37), IR(0, 0), IR(219, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseFetch, true, true, IR(185, 5), IR(30260, 17), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseGather, true, true, IR(195, 6), IR(30277, 18), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseDrefGather, true, true, IR(195, 6), IR(30295, 22), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseTexelsResident, true, true, IR(160, 3), IR(30317, 26), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpNoLine, false, false, IR(0, 0), IR(30343, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpAtomicFlagTestAndSet, true, true, IR(226, 5), IR(30350, 21), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicFlagClear, false, false, IR(332, 3), IR(30371, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpImageSparseRead, true, true, IR(185, 5), IR(30387, 16), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpSizeOf, true, true, IR(160, 3), IR(30403, 7), IR(0, 0), IR(1, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpTypePipeStorage, true, false, IR(68, 1), IR(30410, 16), IR(0, 0), IR(220, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantPipeStorage, true, true, IR(335, 5), IR(30426, 20), IR(0, 0), IR(220, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCreatePipeFromPipeStorage, true, true, IR(160, 3), IR(30446, 26), IR(0, 0), IR(220, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetKernelLocalSizeForSubgroupCount, true, true, IR(325, 7), IR(30472, 35), IR(0, 0), IR(155, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelMaxNumSubgroups, true, true, IR(215, 6), IR(30507, 25), IR(0, 0), IR(155, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpTypeNamedBarrier, true, false, IR(68, 1), IR(30532, 17), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpNamedBarrierInitialize, true, true, IR(160, 3), IR(30549, 23), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpMemoryNamedBarrier, false, false, IR(332, 3), IR(30572, 19), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpModuleProcessed, false, false, IR(11, 1), IR(30591, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpExecutionModeId, false, false, IR(65, 2), IR(30607, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,2), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpDecorateId, false, false, IR(163, 2), IR(30623, 11), IR(0, 0), IR(1, 0), IR(157, 1), SPV_SPIRV_VERSION_WORD(1,2), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupNonUniformElect, true, true, IR(340, 3), IR(30634, 21), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAll, true, true, IR(274, 4), IR(30655, 19), IR(0, 0), IR(222, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAny, true, true, IR(274, 4), IR(30674, 19), IR(0, 0), IR(222, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAllEqual, true, true, IR(274, 4), IR(30693, 24), IR(0, 0), IR(222, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBroadcast, true, true, IR(278, 5), IR(30717, 25), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBroadcastFirst, true, true, IR(274, 4), IR(30742, 30), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallot, true, true, IR(274, 4), IR(5650, 22), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformInverseBallot, true, true, IR(274, 4), IR(30772, 29), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotBitExtract, true, true, IR(278, 5), IR(30801, 32), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotBitCount, true, true, IR(283, 5), IR(30833, 30), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotFindLSB, true, true, IR(274, 4), IR(30863, 29), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotFindMSB, true, true, IR(274, 4), IR(30892, 29), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffle, true, true, IR(278, 5), IR(8740, 23), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleXor, true, true, IR(278, 5), IR(30921, 26), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleUp, true, true, IR(278, 5), IR(30947, 25), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleDown, true, true, IR(278, 5), IR(30972, 27), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformIAdd, true, true, IR(343, 6), IR(30999, 20), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFAdd, true, true, IR(343, 6), IR(31019, 20), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformIMul, true, true, IR(343, 6), IR(31039, 20), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMul, true, true, IR(343, 6), IR(31059, 20), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformSMin, true, true, IR(343, 6), IR(31079, 20), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformUMin, true, true, IR(343, 6), IR(31099, 20), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMin, true, true, IR(343, 6), IR(31119, 20), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformSMax, true, true, IR(343, 6), IR(31139, 20), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformUMax, true, true, IR(343, 6), IR(31159, 20), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMax, true, true, IR(343, 6), IR(31179, 20), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseAnd, true, true, IR(343, 6), IR(31199, 26), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseOr, true, true, IR(343, 6), IR(31225, 25), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseXor, true, true, IR(343, 6), IR(31250, 26), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalAnd, true, true, IR(343, 6), IR(31276, 26), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalOr, true, true, IR(343, 6), IR(31302, 25), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalXor, true, true, IR(343, 6), IR(31327, 26), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadBroadcast, true, true, IR(278, 5), IR(31353, 29), IR(0, 0), IR(229, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadSwap, true, true, IR(278, 5), IR(31382, 24), IR(0, 0), IR(229, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpCopyLogical, true, true, IR(160, 3), IR(31406, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpPtrEqual, true, true, IR(172, 4), IR(31418, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrNotEqual, true, true, IR(172, 4), IR(31427, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrDiff, true, true, IR(172, 4), IR(31439, 8), IR(0, 0), IR(230, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpColorAttachmentReadEXT, true, true, IR(349, 4), IR(31447, 23), IR(0, 0), IR(147, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpDepthAttachmentReadEXT, true, true, IR(353, 3), IR(31470, 23), IR(0, 0), IR(156, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpStencilAttachmentReadEXT, true, true, IR(353, 3), IR(31493, 25), IR(0, 0), IR(157, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpTypeTensorARM, true, false, IR(356, 4), IR(31518, 14), IR(0, 0), IR(202, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTensorReadARM, true, true, IR(360, 5), IR(31574, 14), IR(0, 0), IR(202, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpTensorWriteARM, false, false, IR(365, 4), IR(31588, 15), IR(0, 0), IR(202, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpTensorQuerySizeARM, true, true, IR(172, 4), IR(31603, 19), IR(0, 0), IR(202, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpGraphConstantARM, true, true, IR(369, 3), IR(31622, 17), IR(0, 0), IR(233, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphEntryPointARM, false, false, IR(372, 3), IR(31639, 19), IR(0, 0), IR(233, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphARM, true, true, IR(39, 2), IR(9031, 9), IR(0, 0), IR(233, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphInputARM, true, true, IR(122, 4), IR(31658, 14), IR(0, 0), IR(233, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphSetOutputARM, false, false, IR(375, 3), IR(31672, 18), IR(0, 0), IR(233, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphEndARM, false, false, IR(0, 0), IR(31690, 12), IR(0, 0), IR(233, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpTypeGraphARM, true, false, IR(378, 3), IR(31702, 13), IR(0, 0), IR(233, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTerminateInvocation, false, false, IR(0, 0), IR(31715, 20), IR(0, 0), IR(3, 1), IR(167, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpTypeUntypedPointerKHR, true, false, IR(381, 2), IR(31735, 22), IR(0, 0), IR(234, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpUntypedVariableKHR, true, true, IR(383, 5), IR(31757, 19), IR(0, 0), IR(234, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedAccessChainKHR, true, true, IR(151, 5), IR(31776, 22), IR(0, 0), IR(234, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedInBoundsAccessChainKHR, true, true, IR(151, 5), IR(31798, 30), IR(0, 0), IR(234, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpSubgroupBallotKHR, true, true, IR(160, 3), IR(5411, 18), IR(0, 0), IR(235, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupFirstInvocationKHR, true, true, IR(160, 3), IR(31828, 27), IR(0, 0), IR(235, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpUntypedPtrAccessChainKHR, true, true, IR(388, 6), IR(31855, 25), IR(0, 0), IR(234, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedInBoundsPtrAccessChainKHR, true, true, IR(388, 6), IR(31880, 33), IR(0, 0), IR(234, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedArrayLengthKHR, true, true, IR(394, 5), IR(31913, 22), IR(0, 0), IR(234, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedPrefetchKHR, false, false, IR(399, 5), IR(31935, 19), IR(0, 0), IR(234, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpSubgroupAllKHR, true, true, IR(160, 3), IR(31954, 15), IR(0, 0), IR(236, 1), IR(41, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupAnyKHR, true, true, IR(160, 3), IR(31969, 15), IR(0, 0), IR(236, 1), IR(41, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupAllEqualKHR, true, true, IR(160, 3), IR(31984, 20), IR(0, 0), IR(236, 1), IR(41, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupNonUniformRotateKHR, true, true, IR(404, 6), IR(13250, 25), IR(0, 0), IR(237, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupReadInvocationKHR, true, true, IR(172, 4), IR(32004, 26), IR(0, 0), IR(235, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpExtInstWithForwardRefsKHR, true, true, IR(410, 5), IR(32030, 26), IR(0, 0), IR(1, 0), IR(168, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpUntypedGroupAsyncCopyKHR, true, true, IR(415, 11), IR(32056, 25), IR(0, 0), IR(234, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpTraceRayKHR, false, false, IR(426, 11), IR(32081, 12), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpExecuteCallableKHR, false, false, IR(36, 2), IR(32093, 19), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToAccelerationStructureKHR, true, true, IR(160, 3), IR(32112, 35), IR(0, 0), IR(238, 2), IR(169, 2), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIgnoreIntersectionKHR, false, false, IR(0, 0), IR(32147, 22), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTerminateRayKHR, false, false, IR(0, 0), IR(32169, 16), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSDot, true, true, IR(437, 5), IR(32232, 5), IR(93, 1), IR(240, 1), IR(122, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDot, true, true, IR(437, 5), IR(32245, 5), IR(94, 1), IR(240, 1), IR(122, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSUDot, true, true, IR(437, 5), IR(32258, 6), IR(95, 1), IR(240, 1), IR(122, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSDotAccSat, true, true, IR(442, 6), IR(32273, 11), IR(96, 1), IR(240, 1), IR(122, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDotAccSat, true, true, IR(442, 6), IR(32298, 11), IR(97, 1), IR(240, 1), IR(122, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSUDotAccSat, true, true, IR(442, 6), IR(32323, 12), IR(98, 1), IR(240, 1), IR(122, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpTypeCooperativeMatrixKHR, true, false, IR(448, 6), IR(32350, 25), IR(0, 0), IR(86, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeMatrixLoadKHR, true, true, IR(454, 6), IR(32375, 25), IR(0, 0), IR(86, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixStoreKHR, false, false, IR(460, 5), IR(32400, 26), IR(0, 0), IR(86, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixMulAddKHR, true, true, IR(465, 6), IR(32480, 27), IR(0, 0), IR(86, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpCooperativeMatrixLengthKHR, true, true, IR(160, 3), IR(32507, 27), IR(0, 0), IR(86, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpConstantCompositeReplicateEXT, true, true, IR(160, 3), IR(32534, 30), IR(0, 0), IR(241, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCompositeReplicateEXT, true, true, IR(160, 3), IR(32564, 34), IR(0, 0), IR(241, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpCompositeConstructReplicateEXT, true, true, IR(160, 3), IR(32598, 31), IR(0, 0), IR(241, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpTypeRayQueryKHR, true, false, IR(68, 1), IR(32629, 16), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpRayQueryInitializeKHR, false, false, IR(471, 8), IR(32645, 22), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryTerminateKHR, false, false, IR(10, 1), IR(32667, 21), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGenerateIntersectionKHR, false, false, IR(36, 2), IR(32688, 32), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryConfirmIntersectionKHR, false, false, IR(10, 1), IR(32720, 31), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryProceedKHR, true, true, IR(160, 3), IR(32751, 19), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTypeKHR, true, true, IR(172, 4), IR(32770, 31), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpImageSampleWeightedQCOM, true, true, IR(130, 5), IR(32801, 24), IR(0, 0), IR(242, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBoxFilterQCOM, true, true, IR(130, 5), IR(32825, 19), IR(0, 0), IR(243, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchSSDQCOM, true, true, IR(325, 7), IR(32844, 23), IR(0, 0), IR(244, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchSADQCOM, true, true, IR(325, 7), IR(32867, 23), IR(0, 0), IR(244, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpBitCastArrayQCOM, true, true, IR(160, 3), IR(32890, 17), IR(0, 0), IR(245, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpImageBlockMatchWindowSSDQCOM, true, true, IR(325, 7), IR(32907, 29), IR(0, 0), IR(246, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchWindowSADQCOM, true, true, IR(325, 7), IR(32936, 29), IR(0, 0), IR(246, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchGatherSSDQCOM, true, true, IR(325, 7), IR(32965, 29), IR(0, 0), IR(246, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchGatherSADQCOM, true, true, IR(325, 7), IR(32994, 29), IR(0, 0), IR(246, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpCompositeConstructCoopMatQCOM, true, true, IR(160, 3), IR(33023, 30), IR(0, 0), IR(245, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeExtractCoopMatQCOM, true, true, IR(160, 3), IR(33053, 28), IR(0, 0), IR(245, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpExtractSubArrayQCOM, true, true, IR(172, 4), IR(33081, 20), IR(0, 0), IR(245, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpGroupIAddNonUniformAMD, true, true, IR(283, 5), IR(33101, 23), IR(0, 0), IR(218, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFAddNonUniformAMD, true, true, IR(283, 5), IR(33124, 23), IR(0, 0), IR(218, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMinNonUniformAMD, true, true, IR(283, 5), IR(33147, 23), IR(0, 0), IR(218, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMinNonUniformAMD, true, true, IR(283, 5), IR(33170, 23), IR(0, 0), IR(218, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMinNonUniformAMD, true, true, IR(283, 5), IR(33193, 23), IR(0, 0), IR(218, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMaxNonUniformAMD, true, true, IR(283, 5), IR(33216, 23), IR(0, 0), IR(218, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMaxNonUniformAMD, true, true, IR(283, 5), IR(33239, 23), IR(0, 0), IR(218, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMaxNonUniformAMD, true, true, IR(283, 5), IR(33262, 23), IR(0, 0), IR(218, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpFragmentMaskFetchAMD, true, true, IR(172, 4), IR(33285, 21), IR(0, 0), IR(247, 1), IR(58, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFragmentFetchAMD, true, true, IR(130, 5), IR(33306, 17), IR(0, 0), IR(247, 1), IR(58, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReadClockKHR, true, true, IR(340, 3), IR(33323, 13), IR(0, 0), IR(248, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAllocateNodePayloadsAMDX, true, true, IR(278, 5), IR(33336, 25), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpEnqueueNodePayloadsAMDX, false, false, IR(10, 1), IR(33361, 24), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeNodePayloadArrayAMDX, true, false, IR(87, 2), IR(33385, 25), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFinishWritingNodePayloadAMDX, true, true, IR(160, 3), IR(33410, 29), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpNodePayloadArrayLengthAMDX, true, true, IR(160, 3), IR(33439, 27), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIsNodePayloadValidAMDX, true, true, IR(172, 4), IR(33466, 23), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConstantStringAMDX, true, false, IR(50, 2), IR(33489, 19), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSpecConstantStringAMDX, true, false, IR(50, 2), IR(33508, 23), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpGroupNonUniformQuadAllKHR, true, true, IR(160, 3), IR(33531, 26), IR(0, 0), IR(164, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadAnyKHR, true, true, IR(160, 3), IR(33557, 26), IR(0, 0), IR(164, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpHitObjectRecordHitMotionNV, false, false, IR(479, 14), IR(33583, 27), IR(0, 0), IR(249, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitWithIndexMotionNV, false, false, IR(493, 13), IR(33610, 36), IR(0, 0), IR(249, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissMotionNV, false, false, IR(506, 7), IR(33646, 28), IR(0, 0), IR(249, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldToObjectNV, true, true, IR(160, 3), IR(33674, 28), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectToWorldNV, true, true, IR(160, 3), IR(33702, 28), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayDirectionNV, true, true, IR(160, 3), IR(33730, 33), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayOriginNV, true, true, IR(160, 3), IR(33763, 30), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayMotionNV, false, false, IR(493, 13), IR(33793, 26), IR(0, 0), IR(249, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderRecordBufferHandleNV, true, true, IR(160, 3), IR(33819, 39), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderBindingTableRecordIndexNV, true, true, IR(160, 3), IR(33858, 44), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordEmptyNV, false, false, IR(10, 1), IR(33902, 23), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayNV, false, false, IR(513, 12), IR(33925, 20), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitNV, false, false, IR(493, 13), IR(33945, 21), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitWithIndexNV, false, false, IR(513, 12), IR(33966, 30), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissNV, false, false, IR(525, 6), IR(33996, 22), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectExecuteShaderNV, false, false, IR(36, 2), IR(34018, 25), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetCurrentTimeNV, true, true, IR(160, 3), IR(34043, 26), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetAttributesNV, false, false, IR(36, 2), IR(34069, 25), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetHitKindNV, true, true, IR(160, 3), IR(34094, 22), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetPrimitiveIndexNV, true, true, IR(160, 3), IR(34116, 29), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetGeometryIndexNV, true, true, IR(160, 3), IR(34145, 28), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceIdNV, true, true, IR(160, 3), IR(34173, 25), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceCustomIndexNV, true, true, IR(160, 3), IR(34198, 34), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayDirectionNV, true, true, IR(160, 3), IR(34232, 32), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayOriginNV, true, true, IR(160, 3), IR(34264, 29), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMaxNV, true, true, IR(160, 3), IR(34293, 22), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMinNV, true, true, IR(160, 3), IR(34315, 22), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsEmptyNV, true, true, IR(160, 3), IR(34337, 19), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsHitNV, true, true, IR(160, 3), IR(34356, 17), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsMissNV, true, true, IR(160, 3), IR(34373, 18), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHitObjectNV, false, false, IR(531, 3), IR(34391, 29), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHintNV, false, false, IR(36, 2), IR(34420, 24), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeHitObjectNV, true, false, IR(68, 1), IR(34444, 16), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpImageSampleFootprintNV, true, true, IR(534, 7), IR(34460, 23), IR(0, 0), IR(251, 1), IR(72, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpTypeCooperativeVectorNV, true, false, IR(89, 3), IR(34483, 24), IR(0, 0), IR(252, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeVectorMatrixMulNV, true, true, IR(541, 13), IR(34507, 29), IR(0, 0), IR(252, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorOuterProductAccumulateNV, false, false, IR(554, 7), IR(34536, 42), IR(0, 0), IR(253, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorReduceSumAccumulateNV, false, false, IR(33, 3), IR(34578, 39), IR(0, 0), IR(253, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorMatrixMulAddNV, true, true, IR(561, 16), IR(34617, 32), IR(0, 0), IR(252, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixConvertNV, true, true, IR(160, 3), IR(34649, 27), IR(0, 0), IR(254, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpEmitMeshTasksEXT, false, false, IR(577, 4), IR(34676, 17), IR(0, 0), IR(53, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSetMeshOutputsEXT, false, false, IR(36, 2), IR(34693, 18), IR(0, 0), IR(53, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpGroupNonUniformPartitionNV, true, true, IR(160, 3), IR(34711, 27), IR(0, 0), IR(183, 1), IR(75, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpWritePackedPrimitiveIndices4x8NV, false, false, IR(36, 2), IR(34738, 33), IR(0, 0), IR(50, 1), IR(18, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFetchMicroTriangleVertexPositionNV, true, true, IR(325, 7), IR(34771, 35), IR(0, 0), IR(255, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFetchMicroTriangleVertexBarycentricNV, true, true, IR(325, 7), IR(34806, 38), IR(0, 0), IR(255, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorLoadNV, true, true, IR(581, 5), IR(34844, 24), IR(0, 0), IR(252, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeVectorStoreNV, false, false, IR(586, 4), IR(34868, 25), IR(0, 0), IR(252, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpReportIntersectionKHR, true, true, IR(172, 4), IR(34893, 22), IR(99, 1), IR(54, 2), IR(24, 2), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIgnoreIntersectionNV, false, false, IR(0, 0), IR(34936, 21), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTerminateRayNV, false, false, IR(0, 0), IR(34957, 15), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceNV, false, false, IR(426, 11), IR(34972, 8), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceMotionNV, false, false, IR(513, 12), IR(34980, 14), IR(0, 0), IR(57, 1), IR(27, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceRayMotionNV, false, false, IR(513, 12), IR(34994, 17), IR(0, 0), IR(57, 1), IR(27, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTriangleVertexPositionsKHR, true, true, IR(172, 4), IR(35011, 50), IR(0, 0), IR(256, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeAccelerationStructureKHR, true, false, IR(68, 1), IR(35061, 29), IR(100, 1), IR(257, 4), IR(171, 4), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpExecuteCallableNV, false, false, IR(36, 2), IR(35118, 18), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionClusterIdNV, true, true, IR(172, 4), IR(35136, 35), IR(101, 1), IR(64, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetClusterIdNV, true, true, IR(160, 3), IR(35194, 24), IR(0, 0), IR(64, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeCooperativeMatrixNV, true, false, IR(590, 5), IR(35218, 24), IR(0, 0), IR(261, 1), IR(79, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeMatrixLoadNV, true, true, IR(595, 6), IR(35242, 24), IR(0, 0), IR(261, 1), IR(79, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixStoreNV, false, false, IR(601, 5), IR(35266, 25), IR(0, 0), IR(261, 1), IR(79, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixMulAddNV, true, true, IR(130, 5), IR(35291, 26), IR(0, 0), IR(261, 1), IR(79, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixLengthNV, true, true, IR(160, 3), IR(35317, 26), IR(0, 0), IR(261, 1), IR(79, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpBeginInvocationInterlockEXT, false, false, IR(0, 0), IR(35343, 28), IR(0, 0), IR(262, 3), IR(80, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpEndInvocationInterlockEXT, false, false, IR(0, 0), IR(35371, 26), IR(0, 0), IR(262, 3), IR(80, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixReduceNV, true, true, IR(606, 5), IR(35440, 26), IR(0, 0), IR(265, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpCooperativeMatrixLoadTensorNV, true, true, IR(611, 7), IR(35541, 30), IR(0, 0), IR(200, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixStoreTensorNV, false, false, IR(618, 5), IR(35571, 31), IR(0, 0), IR(200, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixPerElementOpNV, true, true, IR(151, 5), IR(35602, 32), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpTypeTensorLayoutNV, true, false, IR(89, 3), IR(35634, 19), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeTensorViewNV, true, false, IR(623, 4), IR(35653, 17), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCreateTensorLayoutNV, true, true, IR(39, 2), IR(35670, 21), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetDimensionNV, true, true, IR(122, 4), IR(35691, 27), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetStrideNV, true, true, IR(122, 4), IR(35718, 24), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSliceNV, true, true, IR(122, 4), IR(35742, 20), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetClampValueNV, true, true, IR(172, 4), IR(35762, 28), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCreateTensorViewNV, true, true, IR(39, 2), IR(35790, 19), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetDimensionNV, true, true, IR(122, 4), IR(35809, 25), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetStrideNV, true, true, IR(122, 4), IR(35834, 22), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpDemoteToHelperInvocation, false, false, IR(0, 0), IR(11562, 25), IR(45, 1), IR(268, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpIsHelperInvocationEXT, true, true, IR(39, 2), IR(35856, 22), IR(0, 0), IR(268, 1), IR(81, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetClipNV, true, true, IR(325, 7), IR(35878, 20), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetBlockSizeNV, true, true, IR(122, 4), IR(35898, 27), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixTransposeNV, true, true, IR(160, 3), IR(35925, 29), IR(0, 0), IR(254, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToImageNV, true, true, IR(160, 3), IR(35954, 18), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToSamplerNV, true, true, IR(160, 3), IR(35972, 20), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertImageToUNV, true, true, IR(160, 3), IR(35992, 18), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertSamplerToUNV, true, true, IR(160, 3), IR(36010, 20), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToSampledImageNV, true, true, IR(160, 3), IR(36030, 25), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertSampledImageToUNV, true, true, IR(160, 3), IR(36055, 25), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSamplerImageAddressingModeNV, false, false, IR(0, 1), IR(36080, 29), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRawAccessChainNV, true, true, IR(627, 7), IR(36161, 17), IR(0, 0), IR(189, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpRayQueryGetIntersectionSpherePositionNV, true, true, IR(172, 4), IR(36178, 40), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionSphereRadiusNV, true, true, IR(172, 4), IR(36218, 38), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSPositionsNV, true, true, IR(172, 4), IR(36256, 38), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSRadiiNV, true, true, IR(172, 4), IR(36294, 34), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSHitValueNV, true, true, IR(172, 4), IR(36328, 37), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetSpherePositionNV, true, true, IR(160, 3), IR(36365, 29), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetSphereRadiusNV, true, true, IR(160, 3), IR(36394, 27), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetLSSPositionsNV, true, true, IR(160, 3), IR(36421, 27), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetLSSRadiiNV, true, true, IR(160, 3), IR(36448, 23), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsSphereHitNV, true, true, IR(160, 3), IR(36471, 23), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsLSSHitNV, true, true, IR(160, 3), IR(36494, 20), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryIsSphereHitNV, true, true, IR(172, 4), IR(36514, 22), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryIsLSSHitNV, true, true, IR(172, 4), IR(36536, 19), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSubgroupShuffleINTEL, true, true, IR(172, 4), IR(12010, 21), IR(0, 0), IR(269, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleDownINTEL, true, true, IR(130, 5), IR(36555, 25), IR(0, 0), IR(269, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleUpINTEL, true, true, IR(130, 5), IR(36580, 23), IR(0, 0), IR(269, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleXorINTEL, true, true, IR(172, 4), IR(36603, 24), IR(0, 0), IR(269, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupBlockReadINTEL, true, true, IR(160, 3), IR(36627, 23), IR(0, 0), IR(270, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupBlockWriteINTEL, false, false, IR(36, 2), IR(36650, 24), IR(0, 0), IR(270, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageBlockReadINTEL, true, true, IR(172, 4), IR(36674, 28), IR(0, 0), IR(271, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageBlockWriteINTEL, false, false, IR(33, 3), IR(36702, 29), IR(0, 0), IR(271, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageMediaBlockReadINTEL, true, true, IR(215, 6), IR(36731, 33), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageMediaBlockWriteINTEL, false, false, IR(634, 5), IR(36764, 34), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpUCountLeadingZerosINTEL, true, true, IR(160, 3), IR(36798, 24), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUCountTrailingZerosINTEL, true, true, IR(160, 3), IR(36822, 25), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAbsISubINTEL, true, true, IR(172, 4), IR(36847, 13), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAbsUSubINTEL, true, true, IR(172, 4), IR(36860, 13), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAddSatINTEL, true, true, IR(172, 4), IR(36873, 13), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAddSatINTEL, true, true, IR(172, 4), IR(36886, 13), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAverageINTEL, true, true, IR(172, 4), IR(36899, 14), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAverageINTEL, true, true, IR(172, 4), IR(36913, 14), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAverageRoundedINTEL, true, true, IR(172, 4), IR(36927, 21), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAverageRoundedINTEL, true, true, IR(172, 4), IR(36948, 21), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpISubSatINTEL, true, true, IR(172, 4), IR(36969, 13), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUSubSatINTEL, true, true, IR(172, 4), IR(36982, 13), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIMul32x16INTEL, true, true, IR(172, 4), IR(36995, 15), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUMul32x16INTEL, true, true, IR(172, 4), IR(37010, 15), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConstantFunctionPointerINTEL, true, true, IR(160, 3), IR(37025, 29), IR(0, 0), IR(198, 1), IR(95, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFunctionPointerCallINTEL, true, true, IR(107, 3), IR(37054, 25), IR(0, 0), IR(198, 1), IR(95, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmTargetINTEL, true, false, IR(50, 2), IR(37079, 15), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmINTEL, true, true, IR(639, 6), IR(12228, 9), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmCallINTEL, true, true, IR(122, 4), IR(37094, 13), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAtomicFMinEXT, true, true, IR(235, 6), IR(37107, 14), IR(0, 0), IR(274, 4), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicFMaxEXT, true, true, IR(235, 6), IR(37121, 14), IR(0, 0), IR(274, 4), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAssumeTrueKHR, false, false, IR(10, 1), IR(37135, 14), IR(0, 0), IR(278, 1), IR(99, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpExpectKHR, true, true, IR(172, 4), IR(37149, 10), IR(0, 0), IR(278, 1), IR(99, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpDecorateString, false, false, IR(163, 2), IR(37159, 15), IR(102, 1), IR(1, 0), IR(175, 2), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpMemberDecorateString, false, false, IR(165, 3), IR(37195, 21), IR(103, 1), IR(1, 0), IR(175, 2), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpVmeImageINTEL, true, true, IR(172, 4), IR(37243, 14), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeVmeImageINTEL, true, false, IR(87, 2), IR(37257, 18), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImePayloadINTEL, true, false, IR(68, 1), IR(37275, 23), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcRefPayloadINTEL, true, false, IR(68, 1), IR(37298, 23), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcSicPayloadINTEL, true, false, IR(68, 1), IR(37321, 23), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcMcePayloadINTEL, true, false, IR(68, 1), IR(37344, 23), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcMceResultINTEL, true, false, IR(68, 1), IR(37367, 22), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultINTEL, true, false, IR(68, 1), IR(37389, 22), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultSingleReferenceStreamoutINTEL, true, false, IR(68, 1), IR(37411, 46), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultDualReferenceStreamoutINTEL, true, false, IR(68, 1), IR(37457, 44), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeSingleReferenceStreaminINTEL, true, false, IR(68, 1), IR(37501, 39), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeDualReferenceStreaminINTEL, true, false, IR(68, 1), IR(37540, 37), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcRefResultINTEL, true, false, IR(68, 1), IR(37577, 22), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcSicResultINTEL, true, false, IR(68, 1), IR(37599, 22), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL, true, true, IR(172, 4), IR(37621, 60), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL, true, true, IR(172, 4), IR(37681, 53), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterShapePenaltyINTEL, true, true, IR(172, 4), IR(37734, 47), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterShapePenaltyINTEL, true, true, IR(172, 4), IR(37781, 40), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL, true, true, IR(172, 4), IR(37821, 51), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterDirectionPenaltyINTEL, true, true, IR(172, 4), IR(37872, 44), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL, true, true, IR(172, 4), IR(37916, 51), IR(0, 0), IR(280, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL, true, true, IR(172, 4), IR(37967, 56), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL, true, true, IR(39, 2), IR(38023, 50), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL, true, true, IR(39, 2), IR(38073, 52), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL, true, true, IR(39, 2), IR(38125, 49), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetMotionVectorCostFunctionINTEL, true, true, IR(215, 6), IR(38174, 47), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL, true, true, IR(172, 4), IR(38221, 50), IR(0, 0), IR(280, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL, true, true, IR(39, 2), IR(38271, 51), IR(0, 0), IR(280, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL, true, true, IR(39, 2), IR(38322, 56), IR(0, 0), IR(282, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetAcOnlyHaarINTEL, true, true, IR(160, 3), IR(38378, 33), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL, true, true, IR(172, 4), IR(38411, 52), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL, true, true, IR(172, 4), IR(38463, 61), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL, true, true, IR(130, 5), IR(38524, 61), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToImePayloadINTEL, true, true, IR(160, 3), IR(38585, 39), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToImeResultINTEL, true, true, IR(160, 3), IR(38624, 38), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToRefPayloadINTEL, true, true, IR(160, 3), IR(38662, 39), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToRefResultINTEL, true, true, IR(160, 3), IR(38701, 38), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToSicPayloadINTEL, true, true, IR(160, 3), IR(38739, 39), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToSicResultINTEL, true, true, IR(160, 3), IR(38778, 38), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetMotionVectorsINTEL, true, true, IR(160, 3), IR(38816, 36), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterDistortionsINTEL, true, true, IR(160, 3), IR(38852, 39), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetBestInterDistortionsINTEL, true, true, IR(160, 3), IR(38891, 43), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMajorShapeINTEL, true, true, IR(160, 3), IR(38934, 38), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMinorShapeINTEL, true, true, IR(160, 3), IR(38972, 38), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterDirectionsINTEL, true, true, IR(160, 3), IR(39010, 38), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMotionVectorCountINTEL, true, true, IR(160, 3), IR(39048, 45), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterReferenceIdsINTEL, true, true, IR(160, 3), IR(39093, 40), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL, true, true, IR(130, 5), IR(39133, 62), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeInitializeINTEL, true, true, IR(130, 5), IR(39195, 30), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetSingleReferenceINTEL, true, true, IR(130, 5), IR(39225, 38), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetDualReferenceINTEL, true, true, IR(215, 6), IR(39263, 36), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeRefWindowSizeINTEL, true, true, IR(172, 4), IR(39299, 33), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeAdjustRefOffsetINTEL, true, true, IR(215, 6), IR(39332, 35), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(39367, 39), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetMaxMotionVectorCountINTEL, true, true, IR(172, 4), IR(39406, 43), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetUnidirectionalMixDisableINTEL, true, true, IR(160, 3), IR(39449, 47), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetEarlySearchTerminationThresholdINTEL, true, true, IR(172, 4), IR(39496, 54), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetWeightedSadINTEL, true, true, IR(172, 4), IR(39550, 34), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(39584, 47), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(39631, 45), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL, true, true, IR(215, 6), IR(39676, 55), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL, true, true, IR(325, 7), IR(39731, 53), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL, true, true, IR(130, 5), IR(39784, 56), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL, true, true, IR(215, 6), IR(39840, 54), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL, true, true, IR(215, 6), IR(39894, 58), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL, true, true, IR(325, 7), IR(39952, 56), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeConvertToMceResultINTEL, true, true, IR(160, 3), IR(40008, 38), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetSingleReferenceStreaminINTEL, true, true, IR(160, 3), IR(40046, 46), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetDualReferenceStreaminINTEL, true, true, IR(160, 3), IR(40092, 44), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeStripSingleReferenceStreamoutINTEL, true, true, IR(160, 3), IR(40136, 49), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeStripDualReferenceStreamoutINTEL, true, true, IR(160, 3), IR(40185, 47), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL, true, true, IR(172, 4), IR(40232, 70), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL, true, true, IR(172, 4), IR(40302, 68), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL, true, true, IR(172, 4), IR(40370, 69), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL, true, true, IR(130, 5), IR(40439, 68), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL, true, true, IR(130, 5), IR(40507, 66), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL, true, true, IR(130, 5), IR(40573, 67), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetBorderReachedINTEL, true, true, IR(172, 4), IR(40640, 36), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetTruncatedSearchIndicationINTEL, true, true, IR(160, 3), IR(40676, 48), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL, true, true, IR(160, 3), IR(40724, 59), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL, true, true, IR(160, 3), IR(40783, 58), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL, true, true, IR(160, 3), IR(40841, 56), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcFmeInitializeINTEL, true, true, IR(645, 9), IR(40897, 30), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcBmeInitializeINTEL, true, true, IR(654, 10), IR(40927, 30), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(40957, 39), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefSetBidirectionalMixDisableINTEL, true, true, IR(160, 3), IR(40996, 46), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefSetBilinearFilterEnableINTEL, true, true, IR(160, 3), IR(41042, 43), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(41085, 47), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(41132, 45), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithMultiReferenceINTEL, true, true, IR(130, 5), IR(41177, 46), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL, true, true, IR(215, 6), IR(41223, 56), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefConvertToMceResultINTEL, true, true, IR(160, 3), IR(41279, 38), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicInitializeINTEL, true, true, IR(160, 3), IR(41317, 30), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureSkcINTEL, true, true, IR(288, 8), IR(41347, 32), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureIpeLumaINTEL, true, true, IR(654, 10), IR(41379, 36), IR(0, 0), IR(280, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureIpeLumaChromaINTEL, true, true, IR(664, 13), IR(41415, 42), IR(0, 0), IR(282, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetMotionVectorMaskINTEL, true, true, IR(172, 4), IR(41457, 39), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(41496, 39), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraLumaShapePenaltyINTEL, true, true, IR(172, 4), IR(41535, 44), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraLumaModeCostFunctionINTEL, true, true, IR(215, 6), IR(41579, 48), IR(0, 0), IR(280, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraChromaModeCostFunctionINTEL, true, true, IR(172, 4), IR(41627, 50), IR(0, 0), IR(282, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetBilinearFilterEnableINTEL, true, true, IR(160, 3), IR(41677, 43), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetSkcForwardTransformEnableINTEL, true, true, IR(172, 4), IR(41720, 48), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetBlockBasedRawSkipSadINTEL, true, true, IR(172, 4), IR(41768, 43), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateIpeINTEL, true, true, IR(172, 4), IR(41811, 31), IR(0, 0), IR(280, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(41842, 47), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(41889, 45), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithMultiReferenceINTEL, true, true, IR(130, 5), IR(41934, 46), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL, true, true, IR(215, 6), IR(41980, 56), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConvertToMceResultINTEL, true, true, IR(160, 3), IR(42036, 38), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetIpeLumaShapeINTEL, true, true, IR(160, 3), IR(42074, 35), IR(0, 0), IR(280, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetBestIpeLumaDistortionINTEL, true, true, IR(160, 3), IR(42109, 44), IR(0, 0), IR(280, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetBestIpeChromaDistortionINTEL, true, true, IR(160, 3), IR(42153, 46), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedIpeLumaModesINTEL, true, true, IR(160, 3), IR(42199, 41), IR(0, 0), IR(280, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetIpeChromaModeINTEL, true, true, IR(160, 3), IR(42240, 36), IR(0, 0), IR(282, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL, true, true, IR(160, 3), IR(42276, 50), IR(0, 0), IR(280, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL, true, true, IR(160, 3), IR(42326, 48), IR(0, 0), IR(280, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetInterRawSadsINTEL, true, true, IR(160, 3), IR(42374, 35), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpVariableLengthArrayINTEL, true, true, IR(160, 3), IR(12466, 25), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpSaveMemoryINTEL, true, true, IR(39, 2), IR(42409, 16), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpRestoreMemoryINTEL, false, false, IR(10, 1), IR(42425, 19), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpArbitraryFloatSinCosPiINTEL, true, true, IR(677, 8), IR(42444, 28), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastINTEL, true, true, IR(677, 8), IR(42472, 24), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastFromIntINTEL, true, true, IR(677, 8), IR(42496, 31), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastToIntINTEL, true, true, IR(677, 8), IR(42527, 29), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatAddINTEL, true, true, IR(685, 10), IR(42556, 23), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSubINTEL, true, true, IR(685, 10), IR(42579, 23), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatMulINTEL, true, true, IR(685, 10), IR(42602, 23), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatDivINTEL, true, true, IR(685, 10), IR(42625, 23), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatGTINTEL, true, true, IR(695, 6), IR(42648, 22), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatGEINTEL, true, true, IR(695, 6), IR(42670, 22), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLTINTEL, true, true, IR(695, 6), IR(42692, 22), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLEINTEL, true, true, IR(695, 6), IR(42714, 22), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatEQINTEL, true, true, IR(695, 6), IR(42736, 22), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatRecipINTEL, true, true, IR(677, 8), IR(42758, 25), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatRSqrtINTEL, true, true, IR(677, 8), IR(42783, 25), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCbrtINTEL, true, true, IR(677, 8), IR(42808, 24), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatHypotINTEL, true, true, IR(685, 10), IR(42832, 25), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSqrtINTEL, true, true, IR(677, 8), IR(42857, 24), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLogINTEL, true, true, IR(677, 8), IR(42881, 23), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog2INTEL, true, true, IR(677, 8), IR(42904, 24), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog10INTEL, true, true, IR(677, 8), IR(42928, 25), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog1pINTEL, true, true, IR(677, 8), IR(42953, 25), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExpINTEL, true, true, IR(677, 8), IR(42978, 23), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExp2INTEL, true, true, IR(677, 8), IR(43001, 24), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExp10INTEL, true, true, IR(677, 8), IR(43025, 25), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExpm1INTEL, true, true, IR(677, 8), IR(43050, 25), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinINTEL, true, true, IR(677, 8), IR(43075, 23), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCosINTEL, true, true, IR(677, 8), IR(43098, 23), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinCosINTEL, true, true, IR(677, 8), IR(43121, 26), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinPiINTEL, true, true, IR(677, 8), IR(43147, 25), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCosPiINTEL, true, true, IR(677, 8), IR(43172, 25), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatASinINTEL, true, true, IR(677, 8), IR(43197, 24), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatASinPiINTEL, true, true, IR(677, 8), IR(43221, 26), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatACosINTEL, true, true, IR(677, 8), IR(43247, 24), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatACosPiINTEL, true, true, IR(677, 8), IR(43271, 26), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATanINTEL, true, true, IR(677, 8), IR(43297, 24), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATanPiINTEL, true, true, IR(677, 8), IR(43321, 26), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATan2INTEL, true, true, IR(685, 10), IR(43347, 25), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowINTEL, true, true, IR(685, 10), IR(43372, 23), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowRINTEL, true, true, IR(685, 10), IR(43395, 24), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowNINTEL, true, true, IR(685, 10), IR(43419, 24), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpLoopControlINTEL, false, false, IR(18, 1), IR(43443, 17), IR(0, 0), IR(286, 1), IR(106, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAliasDomainDeclINTEL, true, false, IR(701, 2), IR(43460, 21), IR(0, 0), IR(136, 1), IR(113, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAliasScopeDeclINTEL, true, false, IR(703, 3), IR(43481, 20), IR(0, 0), IR(136, 1), IR(113, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAliasScopeListDeclINTEL, true, false, IR(92, 2), IR(43501, 24), IR(0, 0), IR(136, 1), IR(113, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSqrtINTEL, true, true, IR(677, 8), IR(43525, 15), IR(0, 0), IR(188, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedRecipINTEL, true, true, IR(677, 8), IR(43540, 16), IR(0, 0), IR(188, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedRsqrtINTEL, true, true, IR(677, 8), IR(43556, 16), IR(0, 0), IR(188, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinINTEL, true, true, IR(677, 8), IR(43572, 14), IR(0, 0), IR(188, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedCosINTEL, true, true, IR(677, 8), IR(43586, 14), IR(0, 0), IR(188, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinCosINTEL, true, true, IR(677, 8), IR(43600, 17), IR(0, 0), IR(188, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinPiINTEL, true, true, IR(677, 8), IR(43617, 16), IR(0, 0), IR(188, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedCosPiINTEL, true, true, IR(677, 8), IR(43633, 16), IR(0, 0), IR(188, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinCosPiINTEL, true, true, IR(677, 8), IR(43649, 19), IR(0, 0), IR(188, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedLogINTEL, true, true, IR(677, 8), IR(43668, 14), IR(0, 0), IR(188, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedExpINTEL, true, true, IR(677, 8), IR(43682, 14), IR(0, 0), IR(188, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpPtrCastToCrossWorkgroupINTEL, true, true, IR(160, 3), IR(43696, 29), IR(0, 0), IR(199, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpCrossWorkgroupCastToPtrINTEL, true, true, IR(160, 3), IR(43725, 29), IR(0, 0), IR(199, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpReadPipeBlockingINTEL, true, true, IR(172, 4), IR(43754, 22), IR(0, 0), IR(287, 1), IR(120, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpWritePipeBlockingINTEL, true, true, IR(172, 4), IR(43776, 23), IR(0, 0), IR(287, 1), IR(120, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpFPGARegINTEL, true, true, IR(160, 3), IR(13025, 13), IR(0, 0), IR(288, 1), IR(121, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetRayTMinKHR, true, true, IR(160, 3), IR(43799, 22), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetRayFlagsKHR, true, true, IR(160, 3), IR(43821, 23), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTKHR, true, true, IR(172, 4), IR(43844, 28), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceCustomIndexKHR, true, true, IR(172, 4), IR(43872, 46), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceIdKHR, true, true, IR(172, 4), IR(43918, 37), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR, true, true, IR(172, 4), IR(43955, 65), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionGeometryIndexKHR, true, true, IR(172, 4), IR(44020, 40), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionPrimitiveIndexKHR, true, true, IR(172, 4), IR(44060, 41), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionBarycentricsKHR, true, true, IR(172, 4), IR(44101, 39), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionFrontFaceKHR, true, true, IR(172, 4), IR(44140, 36), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionCandidateAABBOpaqueKHR, true, true, IR(160, 3), IR(44176, 46), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectRayDirectionKHR, true, true, IR(172, 4), IR(44222, 45), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectRayOriginKHR, true, true, IR(172, 4), IR(44267, 42), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetWorldRayDirectionKHR, true, true, IR(160, 3), IR(44309, 32), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetWorldRayOriginKHR, true, true, IR(160, 3), IR(44341, 29), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectToWorldKHR, true, true, IR(172, 4), IR(44370, 40), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionWorldToObjectKHR, true, true, IR(172, 4), IR(44410, 40), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAtomicFAddEXT, true, true, IR(235, 6), IR(44450, 14), IR(0, 0), IR(289, 4), IR(128, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpTypeBufferSurfaceINTEL, true, false, IR(100, 2), IR(44464, 23), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeStructContinuedINTEL, false, false, IR(706, 1), IR(44487, 25), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantCompositeContinuedINTEL, false, false, IR(706, 1), IR(44512, 32), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCompositeContinuedINTEL, false, false, IR(706, 1), IR(44544, 36), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpCompositeConstructContinuedINTEL, true, true, IR(107, 3), IR(44580, 33), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpConvertFToBF16INTEL, true, true, IR(160, 3), IR(44613, 20), IR(0, 0), IR(294, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertBF16ToFINTEL, true, true, IR(160, 3), IR(44633, 20), IR(0, 0), IR(294, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpControlBarrierArriveINTEL, false, false, IR(221, 3), IR(44653, 26), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpControlBarrierWaitINTEL, false, false, IR(221, 3), IR(44679, 24), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpArithmeticFenceEXT, true, true, IR(160, 3), IR(13457, 19), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpTaskSequenceCreateINTEL, true, true, IR(707, 7), IR(44703, 24), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTaskSequenceAsyncINTEL, false, false, IR(168, 2), IR(44727, 23), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTaskSequenceGetINTEL, true, true, IR(160, 3), IR(44750, 21), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTaskSequenceReleaseINTEL, false, false, IR(10, 1), IR(44771, 25), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeTaskSequenceINTEL, true, false, IR(68, 1), IR(44796, 22), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpSubgroupBlockPrefetchINTEL, false, false, IR(139, 3), IR(44818, 27), IR(0, 0), IR(298, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadINTEL, false, false, IR(714, 10), IR(44845, 25), IR(0, 0), IR(108, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadTransformINTEL, false, false, IR(714, 10), IR(44870, 34), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadTransposeINTEL, false, false, IR(714, 10), IR(44904, 34), IR(0, 0), IR(300, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockPrefetchINTEL, false, false, IR(724, 9), IR(44938, 29), IR(0, 0), IR(108, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockStoreINTEL, false, false, IR(714, 10), IR(44967, 26), IR(0, 0), IR(108, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupMatrixMultiplyAccumulateINTEL, true, true, IR(733, 7), IR(13795, 38), IR(0, 0), IR(301, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpBitwiseFunctionINTEL, true, true, IR(215, 6), IR(45055, 21), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpUntypedVariableLengthArrayINTEL, true, true, IR(172, 4), IR(13861, 32), IR(0, 0), IR(303, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpConditionalExtensionINTEL, false, false, IR(45, 2), IR(45076, 26), IR(0, 0), IR(111, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpConditionalEntryPointINTEL, false, false, IR(740, 5), IR(45102, 27), IR(0, 0), IR(111, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpConditionalCapabilityINTEL, false, false, IR(745, 2), IR(45129, 27), IR(0, 0), IR(111, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpSpecConstantTargetINTEL, true, true, IR(747, 4), IR(45156, 24), IR(0, 0), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantArchitectureINTEL, true, true, IR(751, 6), IR(45180, 30), IR(0, 0), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCapabilitiesINTEL, true, true, IR(757, 3), IR(45247, 30), IR(0, 0), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConditionalCopyObjectINTEL, true, true, IR(107, 3), IR(45277, 27), IR(0, 0), IR(111, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpGroupIMulKHR, true, true, IR(283, 5), IR(45304, 13), IR(0, 0), IR(305, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMulKHR, true, true, IR(283, 5), IR(45317, 13), IR(0, 0), IR(305, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseAndKHR, true, true, IR(283, 5), IR(45330, 19), IR(0, 0), IR(305, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseOrKHR, true, true, IR(283, 5), IR(45349, 18), IR(0, 0), IR(305, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseXorKHR, true, true, IR(283, 5), IR(45367, 19), IR(0, 0), IR(305, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalAndKHR, true, true, IR(283, 5), IR(45386, 19), IR(0, 0), IR(305, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalOrKHR, true, true, IR(283, 5), IR(45405, 18), IR(0, 0), IR(305, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalXorKHR, true, true, IR(283, 5), IR(45423, 19), IR(0, 0), IR(305, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpRoundFToTF32INTEL, true, true, IR(160, 3), IR(45442, 18), IR(0, 0), IR(306, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpMaskedGatherINTEL, true, true, IR(760, 6), IR(45460, 18), IR(0, 0), IR(307, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpMaskedScatterINTEL, false, false, IR(766, 4), IR(45478, 19), IR(0, 0), IR(307, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpConvertHandleToImageINTEL, true, true, IR(160, 3), IR(45497, 26), IR(0, 0), IR(308, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertHandleToSamplerINTEL, true, true, IR(160, 3), IR(45523, 28), IR(0, 0), IR(308, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertHandleToSampledImageINTEL, true, true, IR(160, 3), IR(45551, 33), IR(0, 0), IR(308, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
}};

// Opcode strings (without the 'Op' prefix) and opcode values, ordered by name.
// The fields in order are:
//   name, either the primary name or an alias, indexing into kStrings
//   index into kInstructionDesc
static const std::array<NameIndex, 833> kInstructionNames{{
  {IR(36847, 13), 553}, // 0 AbsISubINTEL
  {IR(36860, 13), 554}, // 1 AbsUSubINTEL
  {IR(26667, 12), 58}, // 2 AccessChain
  {IR(43460, 21), 739}, // 3 AliasDomainDeclINTEL
  {IR(43481, 20), 740}, // 4 AliasScopeDeclINTEL
  {IR(43501, 24), 741}, // 5 AliasScopeListDeclINTEL
  {IR(27964, 4), 143}, // 6 All
  {IR(33336, 25), 425}, // 7 AllocateNodePayloadsAMDX
  {IR(27960, 4), 142}, // 8 Any
  {IR(43247, 24), 730}, // 9 ArbitraryFloatACosINTEL
  {IR(43271, 26), 731}, // 10 ArbitraryFloatACosPiINTEL
  {IR(43197, 24), 728}, // 11 ArbitraryFloatASinINTEL
  {IR(43221, 26), 729}, // 12 ArbitraryFloatASinPiINTEL
  {IR(43347, 25), 734}, // 13 ArbitraryFloatATan2INTEL
  {IR(43297, 24), 732}, // 14 ArbitraryFloatATanINTEL
  {IR(43321, 26), 733}, // 15 ArbitraryFloatATanPiINTEL
  {IR(42556, 23), 701}, // 16 ArbitraryFloatAddINTEL
  {IR(42496, 31), 699}, // 17 ArbitraryFloatCastFromIntINTEL
  {IR(42472, 24), 698}, // 18 ArbitraryFloatCastINTEL
  {IR(42527, 29), 700}, // 19 ArbitraryFloatCastToIntINTEL
  {IR(42808, 24), 712}, // 20 ArbitraryFloatCbrtINTEL
  {IR(43098, 23), 724}, // 21 ArbitraryFloatCosINTEL
  {IR(43172, 25), 727}, // 22 ArbitraryFloatCosPiINTEL
  {IR(42625, 23), 704}, // 23 ArbitraryFloatDivINTEL
  {IR(42736, 22), 709}, // 24 ArbitraryFloatEQINTEL
  {IR(43025, 25), 721}, // 25 ArbitraryFloatExp10INTEL
  {IR(43001, 24), 720}, // 26 ArbitraryFloatExp2INTEL
  {IR(42978, 23), 719}, // 27 ArbitraryFloatExpINTEL
  {IR(43050, 25), 722}, // 28 ArbitraryFloatExpm1INTEL
  {IR(42670, 22), 706}, // 29 ArbitraryFloatGEINTEL
  {IR(42648, 22), 705}, // 30 ArbitraryFloatGTINTEL
  {IR(42832, 25), 713}, // 31 ArbitraryFloatHypotINTEL
  {IR(42714, 22), 708}, // 32 ArbitraryFloatLEINTEL
  {IR(42692, 22), 707}, // 33 ArbitraryFloatLTINTEL
  {IR(42928, 25), 717}, // 34 ArbitraryFloatLog10INTEL
  {IR(42953, 25), 718}, // 35 ArbitraryFloatLog1pINTEL
  {IR(42904, 24), 716}, // 36 ArbitraryFloatLog2INTEL
  {IR(42881, 23), 715}, // 37 ArbitraryFloatLogINTEL
  {IR(42602, 23), 703}, // 38 ArbitraryFloatMulINTEL
  {IR(43372, 23), 735}, // 39 ArbitraryFloatPowINTEL
  {IR(43419, 24), 737}, // 40 ArbitraryFloatPowNINTEL
  {IR(43395, 24), 736}, // 41 ArbitraryFloatPowRINTEL
  {IR(42783, 25), 711}, // 42 ArbitraryFloatRSqrtINTEL
  {IR(42758, 25), 710}, // 43 ArbitraryFloatRecipINTEL
  {IR(43121, 26), 725}, // 44 ArbitraryFloatSinCosINTEL
  {IR(42444, 28), 697}, // 45 ArbitraryFloatSinCosPiINTEL
  {IR(43075, 23), 723}, // 46 ArbitraryFloatSinINTEL
  {IR(43147, 25), 726}, // 47 ArbitraryFloatSinPiINTEL
  {IR(42857, 24), 714}, // 48 ArbitraryFloatSqrtINTEL
  {IR(42579, 23), 702}, // 49 ArbitraryFloatSubINTEL
  {IR(13457, 19), 785}, // 50 ArithmeticFenceEXT
  {IR(26714, 12), 61}, // 51 ArrayLength
  {IR(37094, 13), 569}, // 52 AsmCallINTEL
  {IR(12228, 9), 568}, // 53 AsmINTEL
  {IR(37079, 15), 567}, // 54 AsmTargetINTEL
  {IR(37135, 14), 572}, // 55 AssumeTrueKHR
  {IR(28986, 10), 220}, // 56 AtomicAnd
  {IR(28838, 22), 210}, // 57 AtomicCompareExchange
  {IR(28860, 26), 211}, // 58 AtomicCompareExchangeWeak
  {IR(28823, 15), 209}, // 59 AtomicExchange
  {IR(44450, 14), 775}, // 60 AtomicFAddEXT
  {IR(37121, 14), 571}, // 61 AtomicFMaxEXT
  {IR(37107, 14), 570}, // 62 AtomicFMinEXT
  {IR(30371, 16), 292}, // 63 AtomicFlagClear
  {IR(30350, 21), 291}, // 64 AtomicFlagTestAndSet
  {IR(28920, 11), 214}, // 65 AtomicIAdd
  {IR(28903, 17), 213}, // 66 AtomicIDecrement
  {IR(28886, 17), 212}, // 67 AtomicIIncrement
  {IR(28931, 11), 215}, // 68 AtomicISub
  {IR(28800, 11), 207}, // 69 AtomicLoad
  {IR(28996, 9), 221}, // 70 AtomicOr
  {IR(28964, 11), 218}, // 71 AtomicSMax
  {IR(28942, 11), 216}, // 72 AtomicSMin
  {IR(28811, 12), 208}, // 73 AtomicStore
  {IR(28975, 11), 219}, // 74 AtomicUMax
  {IR(28953, 11), 217}, // 75 AtomicUMin
  {IR(29005, 10), 222}, // 76 AtomicXor
  {IR(35343, 28), 499}, // 77 BeginInvocationInterlockEXT
  {IR(32890, 17), 406}, // 78 BitCastArrayQCOM
  {IR(28584, 9), 191}, // 79 BitCount
  {IR(28524, 15), 187}, // 80 BitFieldInsert
  {IR(28539, 17), 188}, // 81 BitFieldSExtract
  {IR(28556, 17), 189}, // 82 BitFieldUExtract
  {IR(28573, 11), 190}, // 83 BitReverse
  {IR(27712, 8), 114}, // 84 Bitcast
  {IR(28509, 11), 185}, // 85 BitwiseAnd
  {IR(45055, 21), 798}, // 86 BitwiseFunctionINTEL
  {IR(28488, 10), 183}, // 87 BitwiseOr
  {IR(28498, 11), 184}, // 88 BitwiseXor
  {IR(29115, 7), 227}, // 89 Branch
  {IR(29122, 18), 228}, // 90 BranchConditional
  {IR(29983, 13), 277}, // 91 BuildNDRange
  {IR(25728, 11), 15}, // 92 Capability
  {IR(29941, 26), 275}, // 93 CaptureEventProfilingInfo
  {IR(31447, 23), 344}, // 94 ColorAttachmentReadEXT
  {IR(29533, 15), 255}, // 95 CommitReadPipe
  {IR(29548, 16), 256}, // 96 CommitWritePipe
  {IR(26974, 19), 72}, // 97 CompositeConstruct
  {IR(44580, 33), 780}, // 98 CompositeConstructContinuedINTEL
  {IR(33023, 30), 411}, // 99 CompositeConstructCoopMatQCOM
  {IR(32598, 31), 394}, // 100 CompositeConstructReplicateEXT
  {IR(26993, 17), 73}, // 101 CompositeExtract
  {IR(33053, 28), 412}, // 102 CompositeExtractCoopMatQCOM
  {IR(27010, 16), 74}, // 103 CompositeInsert
  {IR(45129, 27), 802}, // 104 ConditionalCapabilityINTEL
  {IR(45277, 27), 806}, // 105 ConditionalCopyObjectINTEL
  {IR(45102, 27), 801}, // 106 ConditionalEntryPointINTEL
  {IR(45076, 26), 800}, // 107 ConditionalExtensionINTEL
  {IR(15451, 9), 39}, // 108 Constant
  {IR(26234, 18), 40}, // 109 ConstantComposite
  {IR(44512, 32), 778}, // 110 ConstantCompositeContinuedINTEL
  {IR(32534, 30), 392}, // 111 ConstantCompositeReplicateEXT
  {IR(26182, 14), 38}, // 112 ConstantFalse
  {IR(37025, 29), 565}, // 113 ConstantFunctionPointerINTEL
  {IR(26346, 13), 42}, // 114 ConstantNull
  {IR(30426, 20), 296}, // 115 ConstantPipeStorage
  {IR(26330, 16), 41}, // 116 ConstantSampler
  {IR(33489, 19), 431}, // 117 ConstantStringAMDX
  {IR(26169, 13), 37}, // 118 ConstantTrue
  {IR(28771, 15), 205}, // 119 ControlBarrier
  {IR(44653, 26), 783}, // 120 ControlBarrierArriveINTEL
  {IR(44679, 24), 784}, // 121 ControlBarrierWaitINTEL
  {IR(44633, 20), 782}, // 122 ConvertBF16ToFINTEL
  {IR(44613, 20), 781}, // 123 ConvertFToBF16INTEL
  {IR(27518, 12), 100}, // 124 ConvertFToS
  {IR(27506, 12), 99}, // 125 ConvertFToU
  {IR(45497, 26), 818}, // 126 ConvertHandleToImageINTEL
  {IR(45551, 33), 820}, // 127 ConvertHandleToSampledImageINTEL
  {IR(45523, 28), 819}, // 128 ConvertHandleToSamplerINTEL
  {IR(35992, 18), 522}, // 129 ConvertImageToUNV
  {IR(27595, 14), 107}, // 130 ConvertPtrToU
  {IR(27530, 12), 101}, // 131 ConvertSToF
  {IR(36055, 25), 525}, // 132 ConvertSampledImageToUNV
  {IR(36010, 20), 523}, // 133 ConvertSamplerToUNV
  {IR(32112, 35), 378}, // 134 ConvertUToAccelerationStructureKHR
  {IR(27542, 12), 102}, // 135 ConvertUToF
  {IR(35954, 18), 520}, // 136 ConvertUToImageNV
  {IR(27639, 14), 110}, // 137 ConvertUToPtr
  {IR(36030, 25), 524}, // 138 ConvertUToSampledImageNV
  {IR(35972, 20), 521}, // 139 ConvertUToSamplerNV
  {IR(34649, 27), 474}, // 140 CooperativeMatrixConvertNV
  {IR(32507, 27), 391}, // 141 CooperativeMatrixLengthKHR
  {IR(35317, 26), 498}, // 142 CooperativeMatrixLengthNV
  {IR(32375, 25), 388}, // 143 CooperativeMatrixLoadKHR
  {IR(35242, 24), 495}, // 144 CooperativeMatrixLoadNV
  {IR(35541, 30), 502}, // 145 CooperativeMatrixLoadTensorNV
  {IR(32480, 27), 390}, // 146 CooperativeMatrixMulAddKHR
  {IR(35291, 26), 497}, // 147 CooperativeMatrixMulAddNV
  {IR(35602, 32), 504}, // 148 CooperativeMatrixPerElementOpNV
  {IR(35440, 26), 501}, // 149 CooperativeMatrixReduceNV
  {IR(32400, 26), 389}, // 150 CooperativeMatrixStoreKHR
  {IR(35266, 25), 496}, // 151 CooperativeMatrixStoreNV
  {IR(35571, 31), 503}, // 152 CooperativeMatrixStoreTensorNV
  {IR(35925, 29), 519}, // 153 CooperativeMatrixTransposeNV
  {IR(34844, 24), 481}, // 154 CooperativeVectorLoadNV
  {IR(34617, 32), 473}, // 155 CooperativeVectorMatrixMulAddNV
  {IR(34507, 29), 470}, // 156 CooperativeVectorMatrixMulNV
  {IR(34536, 42), 471}, // 157 CooperativeVectorOuterProductAccumulateNV
  {IR(34578, 39), 472}, // 158 CooperativeVectorReduceSumAccumulateNV
  {IR(34868, 25), 482}, // 159 CooperativeVectorStoreNV
  {IR(31406, 12), 340}, // 160 CopyLogical
  {IR(26640, 11), 56}, // 161 CopyMemory
  {IR(26651, 16), 57}, // 162 CopyMemorySized
  {IR(27026, 11), 75}, // 163 CopyObject
  {IR(30446, 26), 297}, // 164 CreatePipeFromPipeStorage
  {IR(35670, 21), 507}, // 165 CreateTensorLayoutNV
  {IR(35790, 19), 512}, // 166 CreateTensorViewNV
  {IR(29893, 16), 272}, // 167 CreateUserEvent
  {IR(43725, 29), 754}, // 168 CrossWorkgroupCastToPtrINTEL
  {IR(28593, 5), 192}, // 169 DPdx
  {IR(28639, 11), 198}, // 170 DPdxCoarse
  {IR(28610, 9), 195}, // 171 DPdxFine
  {IR(28598, 5), 193}, // 172 DPdy
  {IR(28650, 11), 199}, // 173 DPdyCoarse
  {IR(28619, 9), 196}, // 174 DPdyFine
  {IR(26800, 9), 64}, // 175 Decorate
  {IR(30623, 11), 305}, // 176 DecorateId
  {IR(37159, 15), 574}, // 177 DecorateString
  {IR(37174, 21), 574}, // 178 DecorateStringGOOGLE
  {IR(26824, 16), 66}, // 179 DecorationGroup
  {IR(11562, 25), 515}, // 180 DemoteToHelperInvocation
  {IR(11587, 28), 515}, // 181 DemoteToHelperInvocationEXT
  {IR(31470, 23), 345}, // 182 DepthAttachmentReadEXT
  {IR(27909, 4), 137}, // 183 Dot
  {IR(34676, 17), 475}, // 184 EmitMeshTasksEXT
  {IR(28698, 17), 203}, // 185 EmitStreamVertex
  {IR(28674, 11), 201}, // 186 EmitVertex
  {IR(35371, 26), 500}, // 187 EndInvocationInterlockEXT
  {IR(28685, 13), 202}, // 188 EndPrimitive
  {IR(28715, 19), 204}, // 189 EndStreamPrimitive
  {IR(29729, 14), 265}, // 190 EnqueueKernel
  {IR(29715, 14), 264}, // 191 EnqueueMarker
  {IR(33361, 24), 426}, // 192 EnqueueNodePayloadsAMDX
  {IR(25643, 11), 13}, // 193 EntryPoint
  {IR(32093, 19), 377}, // 194 ExecuteCallableKHR
  {IR(35118, 18), 491}, // 195 ExecuteCallableNV
  {IR(25686, 14), 14}, // 196 ExecutionMode
  {IR(30607, 16), 304}, // 197 ExecutionModeId
  {IR(37149, 10), 573}, // 198 ExpectKHR
  {IR(25497, 8), 11}, // 199 ExtInst
  {IR(25437, 14), 10}, // 200 ExtInstImport
  {IR(32030, 26), 374}, // 201 ExtInstWithForwardRefsKHR
  {IR(25427, 10), 9}, // 202 Extension
  {IR(33081, 20), 413}, // 203 ExtractSubArrayQCOM
  {IR(27741, 5), 118}, // 204 FAdd
  {IR(27572, 9), 105}, // 205 FConvert
  {IR(27776, 5), 125}, // 206 FDiv
  {IR(27801, 5), 130}, // 207 FMod
  {IR(27761, 5), 122}, // 208 FMul
  {IR(27728, 8), 116}, // 209 FNegate
  {IR(28238, 10), 168}, // 210 FOrdEqual
  {IR(28316, 16), 174}, // 211 FOrdGreaterThan
  {IR(28388, 21), 178}, // 212 FOrdGreaterThanEqual
  {IR(28288, 13), 172}, // 213 FOrdLessThan
  {IR(28350, 18), 176}, // 214 FOrdLessThanEqual
  {IR(28260, 13), 170}, // 215 FOrdNotEqual
  {IR(13025, 13), 757}, // 216 FPGARegINTEL
  {IR(27796, 5), 129}, // 217 FRem
  {IR(27751, 5), 120}, // 218 FSub
  {IR(28248, 12), 169}, // 219 FUnordEqual
  {IR(28332, 18), 175}, // 220 FUnordGreaterThan
  {IR(28409, 23), 179}, // 221 FUnordGreaterThanEqual
  {IR(28301, 15), 173}, // 222 FUnordLessThan
  {IR(28368, 20), 177}, // 223 FUnordLessThanEqual
  {IR(28273, 15), 171}, // 224 FUnordNotEqual
  {IR(34806, 38), 480}, // 225 FetchMicroTriangleVertexBarycentricNV
  {IR(34771, 35), 479}, // 226 FetchMicroTriangleVertexPositionNV
  {IR(33410, 29), 428}, // 227 FinishWritingNodePayloadAMDX
  {IR(43586, 14), 746}, // 228 FixedCosINTEL
  {IR(43633, 16), 749}, // 229 FixedCosPiINTEL
  {IR(43682, 14), 752}, // 230 FixedExpINTEL
  {IR(43668, 14), 751}, // 231 FixedLogINTEL
  {IR(43540, 16), 743}, // 232 FixedRecipINTEL
  {IR(43556, 16), 744}, // 233 FixedRsqrtINTEL
  {IR(43600, 17), 747}, // 234 FixedSinCosINTEL
  {IR(43649, 19), 750}, // 235 FixedSinCosPiINTEL
  {IR(43572, 14), 745}, // 236 FixedSinINTEL
  {IR(43617, 16), 748}, // 237 FixedSinPiINTEL
  {IR(43525, 15), 742}, // 238 FixedSqrtINTEL
  {IR(33306, 17), 423}, // 239 FragmentFetchAMD
  {IR(33285, 21), 422}, // 240 FragmentMaskFetchAMD
  {IR(24547, 9), 48}, // 241 Function
  {IR(26549, 13), 51}, // 242 FunctionCall
  {IR(26537, 12), 50}, // 243 FunctionEnd
  {IR(26519, 18), 49}, // 244 FunctionParameter
  {IR(37054, 25), 566}, // 245 FunctionPointerCallINTEL
  {IR(28603, 7), 194}, // 246 Fwidth
  {IR(28661, 13), 200}, // 247 FwidthCoarse
  {IR(28628, 11), 197}, // 248 FwidthFine
  {IR(27670, 17), 112}, // 249 GenericCastToPtr
  {IR(27687, 25), 113}, // 250 GenericCastToPtrExplicit
  {IR(26726, 23), 62}, // 251 GenericPtrMemSemantics
  {IR(29967, 16), 276}, // 252 GetDefaultQueue
  {IR(30472, 35), 298}, // 253 GetKernelLocalSizeForSubgroupCount
  {IR(30507, 25), 299}, // 254 GetKernelMaxNumSubgroups
  {IR(29773, 32), 267}, // 255 GetKernelNDrangeMaxSubGroupSize
  {IR(29743, 30), 266}, // 256 GetKernelNDrangeSubGroupCount
  {IR(29828, 40), 269}, // 257 GetKernelPreferredWorkGroupSizeMultiple
  {IR(29805, 23), 268}, // 258 GetKernelWorkGroupSize
  {IR(29599, 18), 259}, // 259 GetMaxPipePackets
  {IR(29581, 18), 258}, // 260 GetNumPipePackets
  {IR(9031, 9), 353}, // 261 GraphARM
  {IR(31622, 17), 351}, // 262 GraphConstantARM
  {IR(31690, 12), 356}, // 263 GraphEndARM
  {IR(31639, 19), 352}, // 264 GraphEntryPointARM
  {IR(31658, 14), 354}, // 265 GraphInputARM
  {IR(31672, 18), 355}, // 266 GraphSetOutputARM
  {IR(29286, 9), 238}, // 267 GroupAll
  {IR(29295, 9), 239}, // 268 GroupAny
  {IR(29255, 15), 236}, // 269 GroupAsyncCopy
  {IR(45330, 19), 809}, // 270 GroupBitwiseAndKHR
  {IR(45349, 18), 810}, // 271 GroupBitwiseOrKHR
  {IR(45367, 19), 811}, // 272 GroupBitwiseXorKHR
  {IR(29304, 15), 240}, // 273 GroupBroadcast
  {IR(29674, 20), 262}, // 274 GroupCommitReadPipe
  {IR(29694, 21), 263}, // 275 GroupCommitWritePipe
  {IR(26840, 14), 67}, // 276 GroupDecorate
  {IR(29362, 10), 242}, // 277 GroupFAdd
  {IR(33124, 23), 415}, // 278 GroupFAddNonUniformAMD
  {IR(29402, 10), 246}, // 279 GroupFMax
  {IR(33216, 23), 419}, // 280 GroupFMaxNonUniformAMD
  {IR(29372, 10), 243}, // 281 GroupFMin
  {IR(33147, 23), 416}, // 282 GroupFMinNonUniformAMD
  {IR(45317, 13), 808}, // 283 GroupFMulKHR
  {IR(29352, 10), 241}, // 284 GroupIAdd
  {IR(33101, 23), 414}, // 285 GroupIAddNonUniformAMD
  {IR(45304, 13), 807}, // 286 GroupIMulKHR
  {IR(45386, 19), 812}, // 287 GroupLogicalAndKHR
  {IR(45405, 18), 813}, // 288 GroupLogicalOrKHR
  {IR(45423, 19), 814}, // 289 GroupLogicalXorKHR
  {IR(26899, 20), 68}, // 290 GroupMemberDecorate
  {IR(30655, 19), 307}, // 291 GroupNonUniformAll
  {IR(30693, 24), 309}, // 292 GroupNonUniformAllEqual
  {IR(30674, 19), 308}, // 293 GroupNonUniformAny
  {IR(5650, 22), 312}, // 294 GroupNonUniformBallot
  {IR(30833, 30), 315}, // 295 GroupNonUniformBallotBitCount
  {IR(30801, 32), 314}, // 296 GroupNonUniformBallotBitExtract
  {IR(30863, 29), 316}, // 297 GroupNonUniformBallotFindLSB
  {IR(30892, 29), 317}, // 298 GroupNonUniformBallotFindMSB
  {IR(31199, 26), 332}, // 299 GroupNonUniformBitwiseAnd
  {IR(31225, 25), 333}, // 300 GroupNonUniformBitwiseOr
  {IR(31250, 26), 334}, // 301 GroupNonUniformBitwiseXor
  {IR(30717, 25), 310}, // 302 GroupNonUniformBroadcast
  {IR(30742, 30), 311}, // 303 GroupNonUniformBroadcastFirst
  {IR(30634, 21), 306}, // 304 GroupNonUniformElect
  {IR(31019, 20), 323}, // 305 GroupNonUniformFAdd
  {IR(31179, 20), 331}, // 306 GroupNonUniformFMax
  {IR(31119, 20), 328}, // 307 GroupNonUniformFMin
  {IR(31059, 20), 325}, // 308 GroupNonUniformFMul
  {IR(30999, 20), 322}, // 309 GroupNonUniformIAdd
  {IR(31039, 20), 324}, // 310 GroupNonUniformIMul
  {IR(30772, 29), 313}, // 311 GroupNonUniformInverseBallot
  {IR(31276, 26), 335}, // 312 GroupNonUniformLogicalAnd
  {IR(31302, 25), 336}, // 313 GroupNonUniformLogicalOr
  {IR(31327, 26), 337}, // 314 GroupNonUniformLogicalXor
  {IR(34711, 27), 477}, // 315 GroupNonUniformPartitionNV
  {IR(33531, 26), 433}, // 316 GroupNonUniformQuadAllKHR
  {IR(33557, 26), 434}, // 317 GroupNonUniformQuadAnyKHR
  {IR(31353, 29), 338}, // 318 GroupNonUniformQuadBroadcast
  {IR(31382, 24), 339}, // 319 GroupNonUniformQuadSwap
  {IR(13250, 25), 372}, // 320 GroupNonUniformRotateKHR
  {IR(31139, 20), 329}, // 321 GroupNonUniformSMax
  {IR(31079, 20), 326}, // 322 GroupNonUniformSMin
  {IR(8740, 23), 318}, // 323 GroupNonUniformShuffle
  {IR(30972, 27), 321}, // 324 GroupNonUniformShuffleDown
  {IR(30947, 25), 320}, // 325 GroupNonUniformShuffleUp
  {IR(30921, 26), 319}, // 326 GroupNonUniformShuffleXor
  {IR(31159, 20), 330}, // 327 GroupNonUniformUMax
  {IR(31099, 20), 327}, // 328 GroupNonUniformUMin
  {IR(29617, 28), 260}, // 329 GroupReserveReadPipePackets
  {IR(29645, 29), 261}, // 330 GroupReserveWritePipePackets
  {IR(29422, 10), 248}, // 331 GroupSMax
  {IR(33262, 23), 421}, // 332 GroupSMaxNonUniformAMD
  {IR(29392, 10), 245}, // 333 GroupSMin
  {IR(33193, 23), 418}, // 334 GroupSMinNonUniformAMD
  {IR(29412, 10), 247}, // 335 GroupUMax
  {IR(33239, 23), 420}, // 336 GroupUMaxNonUniformAMD
  {IR(29382, 10), 244}, // 337 GroupUMin
  {IR(33170, 23), 417}, // 338 GroupUMinNonUniformAMD
  {IR(29270, 16), 237}, // 339 GroupWaitEvents
  {IR(34018, 25), 450}, // 340 HitObjectExecuteShaderNV
  {IR(34069, 25), 452}, // 341 HitObjectGetAttributesNV
  {IR(35194, 24), 493}, // 342 HitObjectGetClusterIdNV
  {IR(34043, 26), 451}, // 343 HitObjectGetCurrentTimeNV
  {IR(34145, 28), 455}, // 344 HitObjectGetGeometryIndexNV
  {IR(34094, 22), 453}, // 345 HitObjectGetHitKindNV
  {IR(34198, 34), 457}, // 346 HitObjectGetInstanceCustomIndexNV
  {IR(34173, 25), 456}, // 347 HitObjectGetInstanceIdNV
  {IR(36421, 27), 535}, // 348 HitObjectGetLSSPositionsNV
  {IR(36448, 23), 536}, // 349 HitObjectGetLSSRadiiNV
  {IR(33730, 33), 440}, // 350 HitObjectGetObjectRayDirectionNV
  {IR(33763, 30), 441}, // 351 HitObjectGetObjectRayOriginNV
  {IR(33702, 28), 439}, // 352 HitObjectGetObjectToWorldNV
  {IR(34116, 29), 454}, // 353 HitObjectGetPrimitiveIndexNV
  {IR(34293, 22), 460}, // 354 HitObjectGetRayTMaxNV
  {IR(34315, 22), 461}, // 355 HitObjectGetRayTMinNV
  {IR(33858, 44), 444}, // 356 HitObjectGetShaderBindingTableRecordIndexNV
  {IR(33819, 39), 443}, // 357 HitObjectGetShaderRecordBufferHandleNV
  {IR(36365, 29), 533}, // 358 HitObjectGetSpherePositionNV
  {IR(36394, 27), 534}, // 359 HitObjectGetSphereRadiusNV
  {IR(34232, 32), 458}, // 360 HitObjectGetWorldRayDirectionNV
  {IR(34264, 29), 459}, // 361 HitObjectGetWorldRayOriginNV
  {IR(33674, 28), 438}, // 362 HitObjectGetWorldToObjectNV
  {IR(34337, 19), 462}, // 363 HitObjectIsEmptyNV
  {IR(34356, 17), 463}, // 364 HitObjectIsHitNV
  {IR(36494, 20), 538}, // 365 HitObjectIsLSSHitNV
  {IR(34373, 18), 464}, // 366 HitObjectIsMissNV
  {IR(36471, 23), 537}, // 367 HitObjectIsSphereHitNV
  {IR(33902, 23), 445}, // 368 HitObjectRecordEmptyNV
  {IR(33583, 27), 435}, // 369 HitObjectRecordHitMotionNV
  {IR(33945, 21), 447}, // 370 HitObjectRecordHitNV
  {IR(33610, 36), 436}, // 371 HitObjectRecordHitWithIndexMotionNV
  {IR(33966, 30), 448}, // 372 HitObjectRecordHitWithIndexNV
  {IR(33646, 28), 437}, // 373 HitObjectRecordMissMotionNV
  {IR(33996, 22), 449}, // 374 HitObjectRecordMissNV
  {IR(33793, 26), 442}, // 375 HitObjectTraceRayMotionNV
  {IR(33925, 20), 446}, // 376 HitObjectTraceRayNV
  {IR(27736, 5), 117}, // 377 IAdd
  {IR(27913, 10), 138}, // 378 IAddCarry
  {IR(36873, 13), 555}, // 379 IAddSatINTEL
  {IR(36899, 14), 557}, // 380 IAverageINTEL
  {IR(36927, 21), 559}, // 381 IAverageRoundedINTEL
  {IR(28109, 7), 158}, // 382 IEqual
  {IR(27756, 5), 121}, // 383 IMul
  {IR(36995, 15), 563}, // 384 IMul32x16INTEL
  {IR(28116, 10), 159}, // 385 INotEqual
  {IR(27746, 5), 119}, // 386 ISub
  {IR(27923, 11), 139}, // 387 ISubBorrow
  {IR(36969, 13), 561}, // 388 ISubSatINTEL
  {IR(32147, 22), 379}, // 389 IgnoreIntersectionKHR
  {IR(34936, 21), 484}, // 390 IgnoreIntersectionNV
  {IR(24591, 6), 91}, // 391 Image
  {IR(32994, 29), 410}, // 392 ImageBlockMatchGatherSADQCOM
  {IR(32965, 29), 409}, // 393 ImageBlockMatchGatherSSDQCOM
  {IR(32867, 23), 405}, // 394 ImageBlockMatchSADQCOM
  {IR(32844, 23), 404}, // 395 ImageBlockMatchSSDQCOM
  {IR(32936, 29), 408}, // 396 ImageBlockMatchWindowSADQCOM
  {IR(32907, 29), 407}, // 397 ImageBlockMatchWindowSSDQCOM
  {IR(32825, 19), 403}, // 398 ImageBoxFilterQCOM
  {IR(27354, 16), 88}, // 399 ImageDrefGather
  {IR(27331, 11), 86}, // 400 ImageFetch
  {IR(27342, 12), 87}, // 401 ImageGather
  {IR(27391, 17), 92}, // 402 ImageQueryFormat
  {IR(27471, 17), 97}, // 403 ImageQueryLevels
  {IR(27457, 14), 96}, // 404 ImageQueryLod
  {IR(27408, 16), 93}, // 405 ImageQueryOrder
  {IR(27488, 18), 98}, // 406 ImageQuerySamples
  {IR(27442, 15), 95}, // 407 ImageQuerySize
  {IR(27424, 18), 94}, // 408 ImageQuerySizeLod
  {IR(27370, 10), 89}, // 409 ImageRead
  {IR(27188, 27), 81}, // 410 ImageSampleDrefExplicitLod
  {IR(27161, 27), 80}, // 411 ImageSampleDrefImplicitLod
  {IR(27138, 23), 79}, // 412 ImageSampleExplicitLod
  {IR(34460, 23), 468}, // 413 ImageSampleFootprintNV
  {IR(27092, 23), 78}, // 414 ImageSampleImplicitLod
  {IR(27300, 31), 85}, // 415 ImageSampleProjDrefExplicitLod
  {IR(27269, 31), 84}, // 416 ImageSampleProjDrefImplicitLod
  {IR(27242, 27), 83}, // 417 ImageSampleProjExplicitLod
  {IR(27215, 27), 82}, // 418 ImageSampleProjImplicitLod
  {IR(32801, 24), 402}, // 419 ImageSampleWeightedQCOM
  {IR(30295, 22), 288}, // 420 ImageSparseDrefGather
  {IR(30260, 17), 286}, // 421 ImageSparseFetch
  {IR(30277, 18), 287}, // 422 ImageSparseGather
  {IR(30387, 16), 293}, // 423 ImageSparseRead
  {IR(30087, 33), 281}, // 424 ImageSparseSampleDrefExplicitLod
  {IR(30054, 33), 280}, // 425 ImageSparseSampleDrefImplicitLod
  {IR(30025, 29), 279}, // 426 ImageSparseSampleExplicitLod
  {IR(29996, 29), 278}, // 427 ImageSparseSampleImplicitLod
  {IR(30223, 37), 285}, // 428 ImageSparseSampleProjDrefExplicitLod
  {IR(30186, 37), 284}, // 429 ImageSparseSampleProjDrefImplicitLod
  {IR(30153, 33), 283}, // 430 ImageSparseSampleProjExplicitLod
  {IR(30120, 33), 282}, // 431 ImageSparseSampleProjImplicitLod
  {IR(30317, 26), 289}, // 432 ImageSparseTexelsResident
  {IR(26571, 18), 53}, // 433 ImageTexelPointer
  {IR(27380, 11), 90}, // 434 ImageWrite
  {IR(26679, 20), 59}, // 435 InBoundsAccessChain
  {IR(26749, 23), 63}, // 436 InBoundsPtrAccessChain
  {IR(27980, 9), 146}, // 437 IsFinite
  {IR(35856, 22), 516}, // 438 IsHelperInvocationEXT
  {IR(27974, 6), 145}, // 439 IsInf
  {IR(27968, 6), 144}, // 440 IsNan
  {IR(33466, 23), 430}, // 441 IsNodePayloadValidAMDX
  {IR(27989, 9), 147}, // 442 IsNormal
  {IR(29909, 13), 273}, // 443 IsValidEvent
  {IR(29564, 17), 257}, // 444 IsValidReserveId
  {IR(29192, 5), 230}, // 445 Kill
  {IR(29109, 6), 226}, // 446 Label
  {IR(28009, 14), 149}, // 447 LessOrGreater
  {IR(29228, 14), 234}, // 448 LifetimeStart
  {IR(29242, 13), 235}, // 449 LifetimeStop
  {IR(25422, 5), 8}, // 450 Line
  {IR(26629, 5), 54}, // 451 Load
  {IR(28080, 11), 155}, // 452 LogicalAnd
  {IR(28041, 13), 152}, // 453 LogicalEqual
  {IR(28091, 11), 156}, // 454 LogicalNot
  {IR(28054, 16), 153}, // 455 LogicalNotEqual
  {IR(28070, 10), 154}, // 456 LogicalOr
  {IR(43443, 17), 738}, // 457 LoopControlINTEL
  {IR(29049, 10), 224}, // 458 LoopMerge
  {IR(45460, 18), 816}, // 459 MaskedGatherINTEL
  {IR(45478, 19), 817}, // 460 MaskedScatterINTEL
  {IR(27878, 18), 135}, // 461 MatrixTimesMatrix
  {IR(27824, 18), 132}, // 462 MatrixTimesScalar
  {IR(27860, 18), 134}, // 463 MatrixTimesVector
  {IR(26809, 15), 65}, // 464 MemberDecorate
  {IR(37195, 21), 575}, // 465 MemberDecorateString
  {IR(37216, 27), 575}, // 466 MemberDecorateStringGOOGLE
  {IR(25404, 11), 6}, // 467 MemberName
  {IR(28786, 14), 206}, // 468 MemoryBarrier
  {IR(25569, 12), 12}, // 469 MemoryModel
  {IR(30572, 19), 302}, // 470 MemoryNamedBarrier
  {IR(30591, 16), 303}, // 471 ModuleProcessed
  {IR(25399, 5), 5}, // 472 Name
  {IR(30549, 23), 301}, // 473 NamedBarrierInitialize
  {IR(30343, 7), 290}, // 474 NoLine
  {IR(33439, 27), 429}, // 475 NodePayloadArrayLengthAMDX
  {IR(25195, 4), 0}, // 476 Nop
  {IR(28520, 4), 186}, // 477 Not
  {IR(28023, 8), 150}, // 478 Ordered
  {IR(27896, 13), 136}, // 479 OuterProduct
  {IR(29015, 4), 223}, // 480 Phi
  {IR(26699, 15), 60}, // 481 PtrAccessChain
  {IR(43696, 29), 753}, // 482 PtrCastToCrossWorkgroupINTEL
  {IR(27653, 17), 111}, // 483 PtrCastToGeneric
  {IR(31439, 8), 343}, // 484 PtrDiff
  {IR(31418, 9), 341}, // 485 PtrEqual
  {IR(31427, 12), 342}, // 486 PtrNotEqual
  {IR(27581, 14), 106}, // 487 QuantizeToF16
  {IR(36161, 17), 527}, // 488 RawAccessChainNV
  {IR(32720, 31), 399}, // 489 RayQueryConfirmIntersectionKHR
  {IR(32688, 32), 398}, // 490 RayQueryGenerateIntersectionKHR
  {IR(35171, 23), 492}, // 491 RayQueryGetClusterIdNV
  {IR(44101, 39), 766}, // 492 RayQueryGetIntersectionBarycentricsKHR
  {IR(44176, 46), 768}, // 493 RayQueryGetIntersectionCandidateAABBOpaqueKHR
  {IR(35136, 35), 492}, // 494 RayQueryGetIntersectionClusterIdNV
  {IR(44140, 36), 767}, // 495 RayQueryGetIntersectionFrontFaceKHR
  {IR(44020, 40), 764}, // 496 RayQueryGetIntersectionGeometryIndexKHR
  {IR(43872, 46), 761}, // 497 RayQueryGetIntersectionInstanceCustomIndexKHR
  {IR(43918, 37), 762}, // 498 RayQueryGetIntersectionInstanceIdKHR
  {IR(43955, 65), 763}, // 499 RayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR
  {IR(36328, 37), 532}, // 500 RayQueryGetIntersectionLSSHitValueNV
  {IR(36256, 38), 530}, // 501 RayQueryGetIntersectionLSSPositionsNV
  {IR(36294, 34), 531}, // 502 RayQueryGetIntersectionLSSRadiiNV
  {IR(44222, 45), 769}, // 503 RayQueryGetIntersectionObjectRayDirectionKHR
  {IR(44267, 42), 770}, // 504 RayQueryGetIntersectionObjectRayOriginKHR
  {IR(44370, 40), 773}, // 505 RayQueryGetIntersectionObjectToWorldKHR
  {IR(44060, 41), 765}, // 506 RayQueryGetIntersectionPrimitiveIndexKHR
  {IR(36178, 40), 528}, // 507 RayQueryGetIntersectionSpherePositionNV
  {IR(36218, 38), 529}, // 508 RayQueryGetIntersectionSphereRadiusNV
  {IR(43844, 28), 760}, // 509 RayQueryGetIntersectionTKHR
  {IR(35011, 50), 489}, // 510 RayQueryGetIntersectionTriangleVertexPositionsKHR
  {IR(32770, 31), 401}, // 511 RayQueryGetIntersectionTypeKHR
  {IR(44410, 40), 774}, // 512 RayQueryGetIntersectionWorldToObjectKHR
  {IR(43821, 23), 759}, // 513 RayQueryGetRayFlagsKHR
  {IR(43799, 22), 758}, // 514 RayQueryGetRayTMinKHR
  {IR(44309, 32), 771}, // 515 RayQueryGetWorldRayDirectionKHR
  {IR(44341, 29), 772}, // 516 RayQueryGetWorldRayOriginKHR
  {IR(32645, 22), 396}, // 517 RayQueryInitializeKHR
  {IR(36536, 19), 540}, // 518 RayQueryIsLSSHitNV
  {IR(36514, 22), 539}, // 519 RayQueryIsSphereHitNV
  {IR(32751, 19), 400}, // 520 RayQueryProceedKHR
  {IR(32667, 21), 397}, // 521 RayQueryTerminateKHR
  {IR(33323, 13), 424}, // 522 ReadClockKHR
  {IR(29432, 9), 249}, // 523 ReadPipe
  {IR(43754, 22), 755}, // 524 ReadPipeBlockingINTEL
  {IR(29880, 13), 271}, // 525 ReleaseEvent
  {IR(34420, 24), 466}, // 526 ReorderThreadWithHintNV
  {IR(34391, 29), 465}, // 527 ReorderThreadWithHitObjectNV
  {IR(34893, 22), 483}, // 528 ReportIntersectionKHR
  {IR(34915, 21), 483}, // 529 ReportIntersectionNV
  {IR(29486, 23), 253}, // 530 ReserveReadPipePackets
  {IR(29509, 24), 254}, // 531 ReserveWritePipePackets
  {IR(29451, 17), 251}, // 532 ReservedReadPipe
  {IR(29468, 18), 252}, // 533 ReservedWritePipe
  {IR(42425, 19), 696}, // 534 RestoreMemoryINTEL
  {IR(29868, 12), 270}, // 535 RetainEvent
  {IR(29197, 7), 231}, // 536 Return
  {IR(29204, 12), 232}, // 537 ReturnValue
  {IR(45442, 18), 815}, // 538 RoundFToTF32INTEL
  {IR(27563, 9), 104}, // 539 SConvert
  {IR(27771, 5), 124}, // 540 SDiv
  {IR(32232, 5), 381}, // 541 SDot
  {IR(32273, 11), 384}, // 542 SDotAccSat
  {IR(32284, 14), 384}, // 543 SDotAccSatKHR
  {IR(32237, 8), 381}, // 544 SDotKHR
  {IR(28139, 13), 161}, // 545 SGreaterThan
  {IR(28170, 18), 163}, // 546 SGreaterThanEqual
  {IR(28198, 10), 165}, // 547 SLessThan
  {IR(28223, 15), 167}, // 548 SLessThanEqual
  {IR(27791, 5), 128}, // 549 SMod
  {IR(27947, 13), 141}, // 550 SMulExtended
  {IR(27720, 8), 115}, // 551 SNegate
  {IR(27786, 5), 127}, // 552 SRem
  {IR(32258, 6), 383}, // 553 SUDot
  {IR(32323, 12), 386}, // 554 SUDotAccSat
  {IR(32335, 15), 386}, // 555 SUDotAccSatKHR
  {IR(32264, 9), 383}, // 556 SUDotKHR
  {IR(27047, 13), 77}, // 557 SampledImage
  {IR(36080, 29), 526}, // 558 SamplerImageAddressingModeNV
  {IR(27609, 15), 108}, // 559 SatConvertSToU
  {IR(27624, 15), 109}, // 560 SatConvertUToS
  {IR(42409, 16), 695}, // 561 SaveMemoryINTEL
  {IR(28102, 7), 157}, // 562 Select
  {IR(29094, 15), 225}, // 563 SelectionMerge
  {IR(34693, 18), 476}, // 564 SetMeshOutputsEXT
  {IR(29922, 19), 274}, // 565 SetUserEventStatus
  {IR(28471, 17), 182}, // 566 ShiftLeftLogical
  {IR(28450, 21), 181}, // 567 ShiftRightArithmetic
  {IR(28432, 18), 180}, // 568 ShiftRightLogical
  {IR(27998, 11), 148}, // 569 SignBitSet
  {IR(30403, 7), 294}, // 570 SizeOf
  {IR(25376, 7), 3}, // 571 Source
  {IR(25257, 16), 2}, // 572 SourceContinued
  {IR(25383, 16), 4}, // 573 SourceExtension
  {IR(26394, 13), 45}, // 574 SpecConstant
  {IR(45180, 30), 804}, // 575 SpecConstantArchitectureINTEL
  {IR(45247, 30), 805}, // 576 SpecConstantCapabilitiesINTEL
  {IR(26407, 22), 46}, // 577 SpecConstantComposite
  {IR(44544, 36), 779}, // 578 SpecConstantCompositeContinuedINTEL
  {IR(32564, 34), 393}, // 579 SpecConstantCompositeReplicateEXT
  {IR(26376, 18), 44}, // 580 SpecConstantFalse
  {IR(26470, 15), 47}, // 581 SpecConstantOp
  {IR(33508, 23), 432}, // 582 SpecConstantStringAMDX
  {IR(45156, 24), 803}, // 583 SpecConstantTargetINTEL
  {IR(26359, 17), 43}, // 584 SpecConstantTrue
  {IR(31493, 25), 346}, // 585 StencilAttachmentReadEXT
  {IR(26634, 6), 55}, // 586 Store
  {IR(25415, 7), 7}, // 587 String
  {IR(44845, 25), 792}, // 588 Subgroup2DBlockLoadINTEL
  {IR(44870, 34), 793}, // 589 Subgroup2DBlockLoadTransformINTEL
  {IR(44904, 34), 794}, // 590 Subgroup2DBlockLoadTransposeINTEL
  {IR(44938, 29), 795}, // 591 Subgroup2DBlockPrefetchINTEL
  {IR(44967, 26), 796}, // 592 Subgroup2DBlockStoreINTEL
  {IR(31984, 20), 371}, // 593 SubgroupAllEqualKHR
  {IR(31954, 15), 369}, // 594 SubgroupAllKHR
  {IR(31969, 15), 370}, // 595 SubgroupAnyKHR
  {IR(40927, 30), 659}, // 596 SubgroupAvcBmeInitializeINTEL
  {IR(40897, 30), 658}, // 597 SubgroupAvcFmeInitializeINTEL
  {IR(39332, 35), 628}, // 598 SubgroupAvcImeAdjustRefOffsetINTEL
  {IR(39367, 39), 629}, // 599 SubgroupAvcImeConvertToMcePayloadINTEL
  {IR(40008, 38), 642}, // 600 SubgroupAvcImeConvertToMceResultINTEL
  {IR(39631, 45), 635}, // 601 SubgroupAvcImeEvaluateWithDualReferenceINTEL
  {IR(39731, 53), 637}, // 602 SubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL
  {IR(39952, 56), 641}, // 603 SubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL
  {IR(39840, 54), 639}, // 604 SubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL
  {IR(39584, 47), 634}, // 605 SubgroupAvcImeEvaluateWithSingleReferenceINTEL
  {IR(39676, 55), 636}, // 606 SubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL
  {IR(39894, 58), 640}, // 607 SubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL
  {IR(39784, 56), 638}, // 608 SubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL
  {IR(40640, 36), 653}, // 609 SubgroupAvcImeGetBorderReachedINTEL
  {IR(40092, 44), 644}, // 610 SubgroupAvcImeGetDualReferenceStreaminINTEL
  {IR(40046, 46), 643}, // 611 SubgroupAvcImeGetSingleReferenceStreaminINTEL
  {IR(40507, 66), 651}, // 612 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL
  {IR(40439, 68), 650}, // 613 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL
  {IR(40573, 67), 652}, // 614 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL
  {IR(40302, 68), 648}, // 615 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL
  {IR(40232, 70), 647}, // 616 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL
  {IR(40370, 69), 649}, // 617 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL
  {IR(40676, 48), 654}, // 618 SubgroupAvcImeGetTruncatedSearchIndicationINTEL
  {IR(40724, 59), 655}, // 619 SubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL
  {IR(40841, 56), 657}, // 620 SubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL
  {IR(40783, 58), 656}, // 621 SubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL
  {IR(39195, 30), 624}, // 622 SubgroupAvcImeInitializeINTEL
  {IR(39299, 33), 627}, // 623 SubgroupAvcImeRefWindowSizeINTEL
  {IR(39263, 36), 626}, // 624 SubgroupAvcImeSetDualReferenceINTEL
  {IR(39496, 54), 632}, // 625 SubgroupAvcImeSetEarlySearchTerminationThresholdINTEL
  {IR(39406, 43), 630}, // 626 SubgroupAvcImeSetMaxMotionVectorCountINTEL
  {IR(39225, 38), 625}, // 627 SubgroupAvcImeSetSingleReferenceINTEL
  {IR(39449, 47), 631}, // 628 SubgroupAvcImeSetUnidirectionalMixDisableINTEL
  {IR(39550, 34), 633}, // 629 SubgroupAvcImeSetWeightedSadINTEL
  {IR(40185, 47), 646}, // 630 SubgroupAvcImeStripDualReferenceStreamoutINTEL
  {IR(40136, 49), 645}, // 631 SubgroupAvcImeStripSingleReferenceStreamoutINTEL
  {IR(38585, 39), 609}, // 632 SubgroupAvcMceConvertToImePayloadINTEL
  {IR(38624, 38), 610}, // 633 SubgroupAvcMceConvertToImeResultINTEL
  {IR(38662, 39), 611}, // 634 SubgroupAvcMceConvertToRefPayloadINTEL
  {IR(38701, 38), 612}, // 635 SubgroupAvcMceConvertToRefResultINTEL
  {IR(38739, 39), 613}, // 636 SubgroupAvcMceConvertToSicPayloadINTEL
  {IR(38778, 38), 614}, // 637 SubgroupAvcMceConvertToSicResultINTEL
  {IR(38891, 43), 617}, // 638 SubgroupAvcMceGetBestInterDistortionsINTEL
  {IR(38023, 50), 598}, // 639 SubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL
  {IR(37621, 60), 590}, // 640 SubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL
  {IR(37821, 51), 594}, // 641 SubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL
  {IR(37967, 56), 597}, // 642 SubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL
  {IR(37734, 47), 592}, // 643 SubgroupAvcMceGetDefaultInterShapePenaltyINTEL
  {IR(38322, 56), 604}, // 644 SubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL
  {IR(38221, 50), 602}, // 645 SubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL
  {IR(37916, 51), 596}, // 646 SubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL
  {IR(38125, 49), 600}, // 647 SubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL
  {IR(38073, 52), 599}, // 648 SubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL
  {IR(38271, 51), 603}, // 649 SubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL
  {IR(39010, 38), 620}, // 650 SubgroupAvcMceGetInterDirectionsINTEL
  {IR(38852, 39), 616}, // 651 SubgroupAvcMceGetInterDistortionsINTEL
  {IR(38934, 38), 618}, // 652 SubgroupAvcMceGetInterMajorShapeINTEL
  {IR(38972, 38), 619}, // 653 SubgroupAvcMceGetInterMinorShapeINTEL
  {IR(39048, 45), 621}, // 654 SubgroupAvcMceGetInterMotionVectorCountINTEL
  {IR(39093, 40), 622}, // 655 SubgroupAvcMceGetInterReferenceIdsINTEL
  {IR(39133, 62), 623}, // 656 SubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL
  {IR(38816, 36), 615}, // 657 SubgroupAvcMceGetMotionVectorsINTEL
  {IR(38378, 33), 605}, // 658 SubgroupAvcMceSetAcOnlyHaarINTEL
  {IR(38524, 61), 608}, // 659 SubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL
  {IR(37681, 53), 591}, // 660 SubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL
  {IR(37872, 44), 595}, // 661 SubgroupAvcMceSetInterDirectionPenaltyINTEL
  {IR(37781, 40), 593}, // 662 SubgroupAvcMceSetInterShapePenaltyINTEL
  {IR(38174, 47), 601}, // 663 SubgroupAvcMceSetMotionVectorCostFunctionINTEL
  {IR(38463, 61), 607}, // 664 SubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL
  {IR(38411, 52), 606}, // 665 SubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL
  {IR(40957, 39), 660}, // 666 SubgroupAvcRefConvertToMcePayloadINTEL
  {IR(41279, 38), 667}, // 667 SubgroupAvcRefConvertToMceResultINTEL
  {IR(41132, 45), 664}, // 668 SubgroupAvcRefEvaluateWithDualReferenceINTEL
  {IR(41177, 46), 665}, // 669 SubgroupAvcRefEvaluateWithMultiReferenceINTEL
  {IR(41223, 56), 666}, // 670 SubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL
  {IR(41085, 47), 663}, // 671 SubgroupAvcRefEvaluateWithSingleReferenceINTEL
  {IR(40996, 46), 661}, // 672 SubgroupAvcRefSetBidirectionalMixDisableINTEL
  {IR(41042, 43), 662}, // 673 SubgroupAvcRefSetBilinearFilterEnableINTEL
  {IR(41415, 42), 671}, // 674 SubgroupAvcSicConfigureIpeLumaChromaINTEL
  {IR(41379, 36), 670}, // 675 SubgroupAvcSicConfigureIpeLumaINTEL
  {IR(41347, 32), 669}, // 676 SubgroupAvcSicConfigureSkcINTEL
  {IR(41496, 39), 673}, // 677 SubgroupAvcSicConvertToMcePayloadINTEL
  {IR(42036, 38), 685}, // 678 SubgroupAvcSicConvertToMceResultINTEL
  {IR(41811, 31), 680}, // 679 SubgroupAvcSicEvaluateIpeINTEL
  {IR(41889, 45), 682}, // 680 SubgroupAvcSicEvaluateWithDualReferenceINTEL
  {IR(41934, 46), 683}, // 681 SubgroupAvcSicEvaluateWithMultiReferenceINTEL
  {IR(41980, 56), 684}, // 682 SubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL
  {IR(41842, 47), 681}, // 683 SubgroupAvcSicEvaluateWithSingleReferenceINTEL
  {IR(42153, 46), 688}, // 684 SubgroupAvcSicGetBestIpeChromaDistortionINTEL
  {IR(42109, 44), 687}, // 685 SubgroupAvcSicGetBestIpeLumaDistortionINTEL
  {IR(42374, 35), 693}, // 686 SubgroupAvcSicGetInterRawSadsINTEL
  {IR(42240, 36), 690}, // 687 SubgroupAvcSicGetIpeChromaModeINTEL
  {IR(42074, 35), 686}, // 688 SubgroupAvcSicGetIpeLumaShapeINTEL
  {IR(41457, 39), 672}, // 689 SubgroupAvcSicGetMotionVectorMaskINTEL
  {IR(42199, 41), 689}, // 690 SubgroupAvcSicGetPackedIpeLumaModesINTEL
  {IR(42276, 50), 691}, // 691 SubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL
  {IR(42326, 48), 692}, // 692 SubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL
  {IR(41317, 30), 668}, // 693 SubgroupAvcSicInitializeINTEL
  {IR(41677, 43), 677}, // 694 SubgroupAvcSicSetBilinearFilterEnableINTEL
  {IR(41768, 43), 679}, // 695 SubgroupAvcSicSetBlockBasedRawSkipSadINTEL
  {IR(41627, 50), 676}, // 696 SubgroupAvcSicSetIntraChromaModeCostFunctionINTEL
  {IR(41579, 48), 675}, // 697 SubgroupAvcSicSetIntraLumaModeCostFunctionINTEL
  {IR(41535, 44), 674}, // 698 SubgroupAvcSicSetIntraLumaShapePenaltyINTEL
  {IR(41720, 48), 678}, // 699 SubgroupAvcSicSetSkcForwardTransformEnableINTEL
  {IR(5411, 18), 363}, // 700 SubgroupBallotKHR
  {IR(44818, 27), 791}, // 701 SubgroupBlockPrefetchINTEL
  {IR(36627, 23), 545}, // 702 SubgroupBlockReadINTEL
  {IR(36650, 24), 546}, // 703 SubgroupBlockWriteINTEL
  {IR(31828, 27), 364}, // 704 SubgroupFirstInvocationKHR
  {IR(36674, 28), 547}, // 705 SubgroupImageBlockReadINTEL
  {IR(36702, 29), 548}, // 706 SubgroupImageBlockWriteINTEL
  {IR(36731, 33), 549}, // 707 SubgroupImageMediaBlockReadINTEL
  {IR(36764, 34), 550}, // 708 SubgroupImageMediaBlockWriteINTEL
  {IR(13795, 38), 797}, // 709 SubgroupMatrixMultiplyAccumulateINTEL
  {IR(32004, 26), 373}, // 710 SubgroupReadInvocationKHR
  {IR(36555, 25), 542}, // 711 SubgroupShuffleDownINTEL
  {IR(12010, 21), 541}, // 712 SubgroupShuffleINTEL
  {IR(36580, 23), 543}, // 713 SubgroupShuffleUpINTEL
  {IR(36603, 24), 544}, // 714 SubgroupShuffleXorINTEL
  {IR(29185, 7), 229}, // 715 Switch
  {IR(44727, 23), 787}, // 716 TaskSequenceAsyncINTEL
  {IR(44703, 24), 786}, // 717 TaskSequenceCreateINTEL
  {IR(44750, 21), 788}, // 718 TaskSequenceGetINTEL
  {IR(44771, 25), 789}, // 719 TaskSequenceReleaseINTEL
  {IR(35898, 27), 518}, // 720 TensorLayoutSetBlockSizeNV
  {IR(35762, 28), 511}, // 721 TensorLayoutSetClampValueNV
  {IR(35691, 27), 508}, // 722 TensorLayoutSetDimensionNV
  {IR(35718, 24), 509}, // 723 TensorLayoutSetStrideNV
  {IR(35742, 20), 510}, // 724 TensorLayoutSliceNV
  {IR(31603, 19), 350}, // 725 TensorQuerySizeARM
  {IR(31574, 14), 348}, // 726 TensorReadARM
  {IR(35878, 20), 517}, // 727 TensorViewSetClipNV
  {IR(35809, 25), 513}, // 728 TensorViewSetDimensionNV
  {IR(35834, 22), 514}, // 729 TensorViewSetStrideNV
  {IR(31588, 15), 349}, // 730 TensorWriteARM
  {IR(31715, 20), 358}, // 731 TerminateInvocation
  {IR(32169, 16), 380}, // 732 TerminateRayKHR
  {IR(34957, 15), 485}, // 733 TerminateRayNV
  {IR(34980, 14), 487}, // 734 TraceMotionNV
  {IR(34972, 8), 486}, // 735 TraceNV
  {IR(32081, 12), 376}, // 736 TraceRayKHR
  {IR(34994, 17), 488}, // 737 TraceRayMotionNV
  {IR(27037, 10), 76}, // 738 Transpose
  {IR(35061, 29), 490}, // 739 TypeAccelerationStructureKHR
  {IR(35090, 28), 490}, // 740 TypeAccelerationStructureNV
  {IR(25986, 10), 25}, // 741 TypeArray
  {IR(37540, 37), 587}, // 742 TypeAvcImeDualReferenceStreaminINTEL
  {IR(37275, 23), 578}, // 743 TypeAvcImePayloadINTEL
  {IR(37457, 44), 585}, // 744 TypeAvcImeResultDualReferenceStreamoutINTEL
  {IR(37389, 22), 583}, // 745 TypeAvcImeResultINTEL
  {IR(37411, 46), 584}, // 746 TypeAvcImeResultSingleReferenceStreamoutINTEL
  {IR(37501, 39), 586}, // 747 TypeAvcImeSingleReferenceStreaminINTEL
  {IR(37344, 23), 581}, // 748 TypeAvcMcePayloadINTEL
  {IR(37367, 22), 582}, // 749 TypeAvcMceResultINTEL
  {IR(37298, 23), 579}, // 750 TypeAvcRefPayloadINTEL
  {IR(37577, 22), 588}, // 751 TypeAvcRefResultINTEL
  {IR(37321, 23), 580}, // 752 TypeAvcSicPayloadINTEL
  {IR(37599, 22), 589}, // 753 TypeAvcSicResultINTEL
  {IR(25748, 9), 17}, // 754 TypeBool
  {IR(44464, 23), 776}, // 755 TypeBufferSurfaceINTEL
  {IR(32350, 25), 387}, // 756 TypeCooperativeMatrixKHR
  {IR(35218, 24), 494}, // 757 TypeCooperativeMatrixNV
  {IR(34483, 24), 469}, // 758 TypeCooperativeVectorNV
  {IR(26101, 16), 32}, // 759 TypeDeviceEvent
  {IR(26091, 10), 31}, // 760 TypeEvent
  {IR(25802, 10), 19}, // 761 TypeFloat
  {IR(26150, 19), 36}, // 762 TypeForwardPointer
  {IR(26078, 13), 30}, // 763 TypeFunction
  {IR(31702, 13), 357}, // 764 TypeGraphARM
  {IR(34444, 16), 467}, // 765 TypeHitObjectNV
  {IR(25947, 10), 22}, // 766 TypeImage
  {IR(25757, 8), 18}, // 767 TypeInt
  {IR(25823, 11), 21}, // 768 TypeMatrix
  {IR(30532, 17), 300}, // 769 TypeNamedBarrier
  {IR(33385, 25), 427}, // 770 TypeNodePayloadArrayAMDX
  {IR(26024, 11), 28}, // 771 TypeOpaque
  {IR(26141, 9), 35}, // 772 TypePipe
  {IR(30410, 16), 295}, // 773 TypePipeStorage
  {IR(26066, 12), 29}, // 774 TypePointer
  {IR(26131, 10), 34}, // 775 TypeQueue
  {IR(32629, 16), 395}, // 776 TypeRayQueryKHR
  {IR(26117, 14), 33}, // 777 TypeReserveId
  {IR(25996, 17), 26}, // 778 TypeRuntimeArray
  {IR(25969, 17), 24}, // 779 TypeSampledImage
  {IR(25957, 12), 23}, // 780 TypeSampler
  {IR(26013, 11), 27}, // 781 TypeStruct
  {IR(44487, 25), 777}, // 782 TypeStructContinuedINTEL
  {IR(44796, 22), 790}, // 783 TypeTaskSequenceINTEL
  {IR(31518, 14), 347}, // 784 TypeTensorARM
  {IR(35634, 19), 505}, // 785 TypeTensorLayoutNV
  {IR(35653, 17), 506}, // 786 TypeTensorViewNV
  {IR(31735, 22), 359}, // 787 TypeUntypedPointerKHR
  {IR(25812, 11), 20}, // 788 TypeVector
  {IR(37257, 18), 577}, // 789 TypeVmeImageINTEL
  {IR(25739, 9), 16}, // 790 TypeVoid
  {IR(36886, 13), 556}, // 791 UAddSatINTEL
  {IR(36913, 14), 558}, // 792 UAverageINTEL
  {IR(36948, 21), 560}, // 793 UAverageRoundedINTEL
  {IR(27554, 9), 103}, // 794 UConvert
  {IR(36798, 24), 551}, // 795 UCountLeadingZerosINTEL
  {IR(36822, 25), 552}, // 796 UCountTrailingZerosINTEL
  {IR(27766, 5), 123}, // 797 UDiv
  {IR(32245, 5), 382}, // 798 UDot
  {IR(32298, 11), 385}, // 799 UDotAccSat
  {IR(32309, 14), 385}, // 800 UDotAccSatKHR
  {IR(32250, 8), 382}, // 801 UDotKHR
  {IR(28126, 13), 160}, // 802 UGreaterThan
  {IR(28152, 18), 162}, // 803 UGreaterThanEqual
  {IR(28188, 10), 164}, // 804 ULessThan
  {IR(28208, 15), 166}, // 805 ULessThanEqual
  {IR(27781, 5), 126}, // 806 UMod
  {IR(37010, 15), 564}, // 807 UMul32x16INTEL
  {IR(27934, 13), 140}, // 808 UMulExtended
  {IR(36982, 13), 562}, // 809 USubSatINTEL
  {IR(25251, 6), 1}, // 810 Undef
  {IR(28031, 10), 151}, // 811 Unordered
  {IR(29216, 12), 233}, // 812 Unreachable
  {IR(31776, 22), 361}, // 813 UntypedAccessChainKHR
  {IR(31913, 22), 367}, // 814 UntypedArrayLengthKHR
  {IR(32056, 25), 375}, // 815 UntypedGroupAsyncCopyKHR
  {IR(31798, 30), 362}, // 816 UntypedInBoundsAccessChainKHR
  {IR(31880, 33), 366}, // 817 UntypedInBoundsPtrAccessChainKHR
  {IR(31935, 19), 368}, // 818 UntypedPrefetchKHR
  {IR(31855, 25), 365}, // 819 UntypedPtrAccessChainKHR
  {IR(31757, 19), 360}, // 820 UntypedVariableKHR
  {IR(13861, 32), 799}, // 821 UntypedVariableLengthArrayINTEL
  {IR(26562, 9), 52}, // 822 Variable
  {IR(12466, 25), 694}, // 823 VariableLengthArrayINTEL
  {IR(26919, 21), 69}, // 824 VectorExtractDynamic
  {IR(26940, 20), 70}, // 825 VectorInsertDynamic
  {IR(26960, 14), 71}, // 826 VectorShuffle
  {IR(27842, 18), 133}, // 827 VectorTimesMatrix
  {IR(27806, 18), 131}, // 828 VectorTimesScalar
  {IR(37243, 14), 576}, // 829 VmeImageINTEL
  {IR(34738, 33), 478}, // 830 WritePackedPrimitiveIndices4x8NV
  {IR(29441, 10), 250}, // 831 WritePipe
  {IR(43776, 23), 756}, // 832 WritePipeBlockingINTEL
}};

// Extended instruction descriptions, ordered by (extinst enum, opcode value).
// The fields in order are:
//   enum value
//   operands, an IndexRange into kOperandSpans
//   name, a character-counting IndexRange into kStrings
//   capabilities, an IndexRange into kCapabilitySpans
static const std::array<ExtInstDesc, 425> kExtInstByValue{{
    {0,IR(0, 0),IR(45584, 14),IR(1, 0)}, // DebugInfoNone in debuginfo
    {1,IR(52, 3),IR(45598, 21),IR(1, 0)}, // DebugCompilationUnit in debuginfo
    {2,IR(770, 3),IR(45671, 15),IR(1, 0)}, // DebugTypeBasic in debuginfo
    {3,IR(773, 3),IR(45720, 17),IR(1, 0)}, // DebugTypePointer in debuginfo
    {4,IR(776, 2),IR(45775, 19),IR(1, 0)}, // DebugTypeQualifier in debuginfo
    {5,IR(168, 2),IR(45794, 15),IR(1, 0)}, // DebugTypeArray in debuginfo
    {6,IR(261, 2),IR(45809, 16),IR(1, 0)}, // DebugTypeVector in debuginfo
    {7,IR(778, 6),IR(45825, 13),IR(1, 0)}, // DebugTypedef in debuginfo
    {8,IR(168, 2),IR(45838, 18),IR(1, 0)}, // DebugTypeFunction in debuginfo
    {9,IR(784, 9),IR(45856, 14),IR(1, 0)}, // DebugTypeEnum in debuginfo
    {10,IR(793, 9),IR(45908, 19),IR(1, 0)}, // DebugTypeComposite in debuginfo
    {11,IR(802, 10),IR(45927, 16),IR(1, 0)}, // DebugTypeMember in debuginfo
    {12,IR(812, 5),IR(45943, 21),IR(1, 0)}, // DebugTypeInheritance in debuginfo
    {13,IR(36, 2),IR(45964, 21),IR(1, 0)}, // DebugTypePtrToMember in debuginfo
    {14,IR(168, 2),IR(45985, 18),IR(1, 0)}, // DebugTypeTemplate in debuginfo
    {15,IR(817, 6),IR(46003, 27),IR(1, 0)}, // DebugTypeTemplateParameter in debuginfo
    {16,IR(823, 5),IR(46030, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in debuginfo
    {17,IR(828, 5),IR(46065, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in debuginfo
    {18,IR(802, 10),IR(46096, 20),IR(1, 0)}, // DebugGlobalVariable in debuginfo
    {19,IR(833, 8),IR(46116, 25),IR(1, 0)}, // DebugFunctionDeclaration in debuginfo
    {20,IR(841, 11),IR(46141, 14),IR(1, 0)}, // DebugFunction in debuginfo
    {21,IR(852, 5),IR(46155, 18),IR(1, 0)}, // DebugLexicalBlock in debuginfo
    {22,IR(857, 3),IR(46173, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in debuginfo
    {23,IR(860, 2),IR(46204, 11),IR(1, 0)}, // DebugScope in debuginfo
    {24,IR(0, 0),IR(46215, 13),IR(1, 0)}, // DebugNoScope in debuginfo
    {25,IR(862, 3),IR(46228, 15),IR(1, 0)}, // DebugInlinedAt in debuginfo
    {26,IR(865, 7),IR(46285, 19),IR(1, 0)}, // DebugLocalVariable in debuginfo
    {27,IR(36, 2),IR(46304, 21),IR(1, 0)}, // DebugInlinedVariable in debuginfo
    {28,IR(33, 3),IR(46325, 13),IR(1, 0)}, // DebugDeclare in debuginfo
    {29,IR(375, 3),IR(46338, 11),IR(1, 0)}, // DebugValue in debuginfo
    {30,IR(872, 2),IR(46382, 15),IR(1, 0)}, // DebugOperation in debuginfo
    {31,IR(706, 1),IR(46397, 16),IR(1, 0)}, // DebugExpression in debuginfo
    {32,IR(874, 4),IR(46413, 14),IR(1, 0)}, // DebugMacroDef in debuginfo
    {33,IR(857, 3),IR(46427, 16),IR(1, 0)}, // DebugMacroUndef in debuginfo
    {1,IR(10, 1),IR(46443, 6),IR(1, 0)}, // Round in glsl_std_450
    {2,IR(10, 1),IR(46449, 10),IR(1, 0)}, // RoundEven in glsl_std_450
    {3,IR(10, 1),IR(46459, 6),IR(1, 0)}, // Trunc in glsl_std_450
    {4,IR(10, 1),IR(46465, 5),IR(1, 0)}, // FAbs in glsl_std_450
    {5,IR(10, 1),IR(46470, 5),IR(1, 0)}, // SAbs in glsl_std_450
    {6,IR(10, 1),IR(46475, 6),IR(1, 0)}, // FSign in glsl_std_450
    {7,IR(10, 1),IR(46481, 6),IR(1, 0)}, // SSign in glsl_std_450
    {8,IR(10, 1),IR(46487, 6),IR(1, 0)}, // Floor in glsl_std_450
    {9,IR(10, 1),IR(46493, 5),IR(1, 0)}, // Ceil in glsl_std_450
    {10,IR(10, 1),IR(46498, 6),IR(1, 0)}, // Fract in glsl_std_450
    {11,IR(10, 1),IR(46504, 8),IR(1, 0)}, // Radians in glsl_std_450
    {12,IR(10, 1),IR(46512, 8),IR(1, 0)}, // Degrees in glsl_std_450
    {13,IR(10, 1),IR(46520, 4),IR(1, 0)}, // Sin in glsl_std_450
    {14,IR(10, 1),IR(46524, 4),IR(1, 0)}, // Cos in glsl_std_450
    {15,IR(10, 1),IR(46528, 4),IR(1, 0)}, // Tan in glsl_std_450
    {16,IR(10, 1),IR(46532, 5),IR(1, 0)}, // Asin in glsl_std_450
    {17,IR(10, 1),IR(46537, 5),IR(1, 0)}, // Acos in glsl_std_450
    {18,IR(10, 1),IR(46542, 5),IR(1, 0)}, // Atan in glsl_std_450
    {19,IR(10, 1),IR(46547, 5),IR(1, 0)}, // Sinh in glsl_std_450
    {20,IR(10, 1),IR(46552, 5),IR(1, 0)}, // Cosh in glsl_std_450
    {21,IR(10, 1),IR(46557, 5),IR(1, 0)}, // Tanh in glsl_std_450
    {22,IR(10, 1),IR(46562, 6),IR(1, 0)}, // Asinh in glsl_std_450
    {23,IR(10, 1),IR(46568, 6),IR(1, 0)}, // Acosh in glsl_std_450
    {24,IR(10, 1),IR(46574, 6),IR(1, 0)}, // Atanh in glsl_std_450
    {25,IR(36, 2),IR(46580, 6),IR(1, 0)}, // Atan2 in glsl_std_450
    {26,IR(36, 2),IR(46586, 4),IR(1, 0)}, // Pow in glsl_std_450
    {27,IR(10, 1),IR(46590, 4),IR(1, 0)}, // Exp in glsl_std_450
    {28,IR(10, 1),IR(46594, 4),IR(1, 0)}, // Log in glsl_std_450
    {29,IR(10, 1),IR(46598, 5),IR(1, 0)}, // Exp2 in glsl_std_450
    {30,IR(10, 1),IR(46603, 5),IR(1, 0)}, // Log2 in glsl_std_450
    {31,IR(10, 1),IR(46608, 5),IR(1, 0)}, // Sqrt in glsl_std_450
    {32,IR(10, 1),IR(46613, 12),IR(1, 0)}, // InverseSqrt in glsl_std_450
    {33,IR(10, 1),IR(46625, 12),IR(1, 0)}, // Determinant in glsl_std_450
    {34,IR(10, 1),IR(46637, 14),IR(1, 0)}, // MatrixInverse in glsl_std_450
    {35,IR(36, 2),IR(46651, 5),IR(1, 0)}, // Modf in glsl_std_450
    {36,IR(10, 1),IR(46656, 11),IR(1, 0)}, // ModfStruct in glsl_std_450
    {37,IR(36, 2),IR(46667, 5),IR(1, 0)}, // FMin in glsl_std_450
    {38,IR(36, 2),IR(46672, 5),IR(1, 0)}, // UMin in glsl_std_450
    {39,IR(36, 2),IR(46677, 5),IR(1, 0)}, // SMin in glsl_std_450
    {40,IR(36, 2),IR(46682, 5),IR(1, 0)}, // FMax in glsl_std_450
    {41,IR(36, 2),IR(46687, 5),IR(1, 0)}, // UMax in glsl_std_450
    {42,IR(36, 2),IR(46692, 5),IR(1, 0)}, // SMax in glsl_std_450
    {43,IR(33, 3),IR(46697, 7),IR(1, 0)}, // FClamp in glsl_std_450
    {44,IR(33, 3),IR(46704, 7),IR(1, 0)}, // UClamp in glsl_std_450
    {45,IR(33, 3),IR(46711, 7),IR(1, 0)}, // SClamp in glsl_std_450
    {46,IR(33, 3),IR(46718, 5),IR(1, 0)}, // FMix in glsl_std_450
    {47,IR(33, 3),IR(46723, 5),IR(1, 0)}, // IMix in glsl_std_450
    {48,IR(36, 2),IR(46728, 5),IR(1, 0)}, // Step in glsl_std_450
    {49,IR(33, 3),IR(46733, 11),IR(1, 0)}, // SmoothStep in glsl_std_450
    {50,IR(33, 3),IR(46744, 4),IR(1, 0)}, // Fma in glsl_std_450
    {51,IR(36, 2),IR(46748, 6),IR(1, 0)}, // Frexp in glsl_std_450
    {52,IR(10, 1),IR(46754, 12),IR(1, 0)}, // FrexpStruct in glsl_std_450
    {53,IR(36, 2),IR(46766, 6),IR(1, 0)}, // Ldexp in glsl_std_450
    {54,IR(10, 1),IR(46772, 13),IR(1, 0)}, // PackSnorm4x8 in glsl_std_450
    {55,IR(10, 1),IR(46785, 13),IR(1, 0)}, // PackUnorm4x8 in glsl_std_450
    {56,IR(10, 1),IR(46798, 14),IR(1, 0)}, // PackSnorm2x16 in glsl_std_450
    {57,IR(10, 1),IR(46812, 14),IR(1, 0)}, // PackUnorm2x16 in glsl_std_450
    {58,IR(10, 1),IR(46826, 13),IR(1, 0)}, // PackHalf2x16 in glsl_std_450
    {59,IR(10, 1),IR(46839, 15),IR(309, 1)}, // PackDouble2x32 in glsl_std_450
    {60,IR(10, 1),IR(46854, 16),IR(1, 0)}, // UnpackSnorm2x16 in glsl_std_450
    {61,IR(10, 1),IR(46870, 16),IR(1, 0)}, // UnpackUnorm2x16 in glsl_std_450
    {62,IR(10, 1),IR(46886, 15),IR(1, 0)}, // UnpackHalf2x16 in glsl_std_450
    {63,IR(10, 1),IR(46901, 15),IR(1, 0)}, // UnpackSnorm4x8 in glsl_std_450
    {64,IR(10, 1),IR(46916, 15),IR(1, 0)}, // UnpackUnorm4x8 in glsl_std_450
    {65,IR(10, 1),IR(46931, 17),IR(309, 1)}, // UnpackDouble2x32 in glsl_std_450
    {66,IR(10, 1),IR(46948, 7),IR(1, 0)}, // Length in glsl_std_450
    {67,IR(36, 2),IR(46955, 9),IR(1, 0)}, // Distance in glsl_std_450
    {68,IR(36, 2),IR(46964, 6),IR(1, 0)}, // Cross in glsl_std_450
    {69,IR(10, 1),IR(46970, 10),IR(1, 0)}, // Normalize in glsl_std_450
    {70,IR(33, 3),IR(46980, 12),IR(1, 0)}, // FaceForward in glsl_std_450
    {71,IR(36, 2),IR(46992, 8),IR(1, 0)}, // Reflect in glsl_std_450
    {72,IR(33, 3),IR(47000, 8),IR(1, 0)}, // Refract in glsl_std_450
    {73,IR(10, 1),IR(47008, 9),IR(1, 0)}, // FindILsb in glsl_std_450
    {74,IR(10, 1),IR(47017, 9),IR(1, 0)}, // FindSMsb in glsl_std_450
    {75,IR(10, 1),IR(47026, 9),IR(1, 0)}, // FindUMsb in glsl_std_450
    {76,IR(10, 1),IR(47035, 22),IR(310, 1)}, // InterpolateAtCentroid in glsl_std_450
    {77,IR(36, 2),IR(47057, 20),IR(310, 1)}, // InterpolateAtSample in glsl_std_450
    {78,IR(36, 2),IR(47077, 20),IR(310, 1)}, // InterpolateAtOffset in glsl_std_450
    {79,IR(36, 2),IR(47097, 5),IR(1, 0)}, // NMin in glsl_std_450
    {80,IR(36, 2),IR(47102, 5),IR(1, 0)}, // NMax in glsl_std_450
    {81,IR(33, 3),IR(47107, 7),IR(1, 0)}, // NClamp in glsl_std_450
    {1,IR(399, 5),IR(4630, 7),IR(1, 0)}, // Kernel in nonsemantic_clspvreflection
    {2,IR(878, 5),IR(47114, 13),IR(1, 0)}, // ArgumentInfo in nonsemantic_clspvreflection
    {3,IR(883, 5),IR(47127, 22),IR(1, 0)}, // ArgumentStorageBuffer in nonsemantic_clspvreflection
    {4,IR(883, 5),IR(47149, 16),IR(1, 0)}, // ArgumentUniform in nonsemantic_clspvreflection
    {5,IR(554, 7),IR(47165, 25),IR(1, 0)}, // ArgumentPodStorageBuffer in nonsemantic_clspvreflection
    {6,IR(554, 7),IR(47190, 19),IR(1, 0)}, // ArgumentPodUniform in nonsemantic_clspvreflection
    {7,IR(883, 5),IR(47209, 24),IR(1, 0)}, // ArgumentPodPushConstant in nonsemantic_clspvreflection
    {8,IR(883, 5),IR(47233, 21),IR(1, 0)}, // ArgumentSampledImage in nonsemantic_clspvreflection
    {9,IR(883, 5),IR(47254, 21),IR(1, 0)}, // ArgumentStorageImage in nonsemantic_clspvreflection
    {10,IR(883, 5),IR(47275, 16),IR(1, 0)}, // ArgumentSampler in nonsemantic_clspvreflection
    {11,IR(883, 5),IR(47291, 18),IR(1, 0)}, // ArgumentWorkgroup in nonsemantic_clspvreflection
    {12,IR(33, 3),IR(47309, 26),IR(1, 0)}, // SpecConstantWorkgroupSize in nonsemantic_clspvreflection
    {13,IR(33, 3),IR(47335, 25),IR(1, 0)}, // SpecConstantGlobalOffset in nonsemantic_clspvreflection
    {14,IR(10, 1),IR(47360, 20),IR(1, 0)}, // SpecConstantWorkDim in nonsemantic_clspvreflection
    {15,IR(36, 2),IR(47380, 25),IR(1, 0)}, // PushConstantGlobalOffset in nonsemantic_clspvreflection
    {16,IR(36, 2),IR(47405, 30),IR(1, 0)}, // PushConstantEnqueuedLocalSize in nonsemantic_clspvreflection
    {17,IR(36, 2),IR(47435, 23),IR(1, 0)}, // PushConstantGlobalSize in nonsemantic_clspvreflection
    {18,IR(36, 2),IR(47458, 25),IR(1, 0)}, // PushConstantRegionOffset in nonsemantic_clspvreflection
    {19,IR(36, 2),IR(47483, 26),IR(1, 0)}, // PushConstantNumWorkgroups in nonsemantic_clspvreflection
    {20,IR(36, 2),IR(47509, 30),IR(1, 0)}, // PushConstantRegionGroupOffset in nonsemantic_clspvreflection
    {21,IR(33, 3),IR(47539, 26),IR(1, 0)}, // ConstantDataStorageBuffer in nonsemantic_clspvreflection
    {22,IR(33, 3),IR(47565, 20),IR(1, 0)}, // ConstantDataUniform in nonsemantic_clspvreflection
    {23,IR(33, 3),IR(8055, 15),IR(1, 0)}, // LiteralSampler in nonsemantic_clspvreflection
    {24,IR(296, 4),IR(47585, 30),IR(1, 0)}, // PropertyRequiredWorkgroupSize in nonsemantic_clspvreflection
    {25,IR(10, 1),IR(47615, 28),IR(1, 0)}, // SpecConstantSubgroupMaxSize in nonsemantic_clspvreflection
    {26,IR(883, 5),IR(47643, 28),IR(1, 0)}, // ArgumentPointerPushConstant in nonsemantic_clspvreflection
    {27,IR(554, 7),IR(47671, 23),IR(1, 0)}, // ArgumentPointerUniform in nonsemantic_clspvreflection
    {28,IR(33, 3),IR(47694, 35),IR(1, 0)}, // ProgramScopeVariablesStorageBuffer in nonsemantic_clspvreflection
    {29,IR(33, 3),IR(47729, 38),IR(1, 0)}, // ProgramScopeVariablePointerRelocation in nonsemantic_clspvreflection
    {30,IR(296, 4),IR(47767, 42),IR(1, 0)}, // ImageArgumentInfoChannelOrderPushConstant in nonsemantic_clspvreflection
    {31,IR(296, 4),IR(47809, 45),IR(1, 0)}, // ImageArgumentInfoChannelDataTypePushConstant in nonsemantic_clspvreflection
    {32,IR(525, 6),IR(47854, 37),IR(1, 0)}, // ImageArgumentInfoChannelOrderUniform in nonsemantic_clspvreflection
    {33,IR(525, 6),IR(47891, 40),IR(1, 0)}, // ImageArgumentInfoChannelDataTypeUniform in nonsemantic_clspvreflection
    {34,IR(883, 5),IR(47931, 27),IR(1, 0)}, // ArgumentStorageTexelBuffer in nonsemantic_clspvreflection
    {35,IR(883, 5),IR(47958, 27),IR(1, 0)}, // ArgumentUniformTexelBuffer in nonsemantic_clspvreflection
    {36,IR(33, 3),IR(47985, 32),IR(1, 0)}, // ConstantDataPointerPushConstant in nonsemantic_clspvreflection
    {37,IR(33, 3),IR(48017, 40),IR(1, 0)}, // ProgramScopeVariablePointerPushConstant in nonsemantic_clspvreflection
    {38,IR(375, 3),IR(48057, 11),IR(1, 0)}, // PrintfInfo in nonsemantic_clspvreflection
    {39,IR(33, 3),IR(48068, 26),IR(1, 0)}, // PrintfBufferStorageBuffer in nonsemantic_clspvreflection
    {40,IR(33, 3),IR(48094, 32),IR(1, 0)}, // PrintfBufferPointerPushConstant in nonsemantic_clspvreflection
    {41,IR(296, 4),IR(48126, 34),IR(1, 0)}, // NormalizedSamplerMaskPushConstant in nonsemantic_clspvreflection
    {42,IR(36, 2),IR(48160, 22),IR(1, 0)}, // WorkgroupVariableSize in nonsemantic_clspvreflection
    {0,IR(0, 0),IR(45584, 14),IR(1, 0)}, // DebugInfoNone in nonsemantic_shader_debuginfo_100
    {1,IR(296, 4),IR(45598, 21),IR(1, 0)}, // DebugCompilationUnit in nonsemantic_shader_debuginfo_100
    {2,IR(296, 4),IR(45671, 15),IR(1, 0)}, // DebugTypeBasic in nonsemantic_shader_debuginfo_100
    {3,IR(33, 3),IR(45720, 17),IR(1, 0)}, // DebugTypePointer in nonsemantic_shader_debuginfo_100
    {4,IR(36, 2),IR(45775, 19),IR(1, 0)}, // DebugTypeQualifier in nonsemantic_shader_debuginfo_100
    {5,IR(168, 2),IR(45794, 15),IR(1, 0)}, // DebugTypeArray in nonsemantic_shader_debuginfo_100
    {6,IR(36, 2),IR(45809, 16),IR(1, 0)}, // DebugTypeVector in nonsemantic_shader_debuginfo_100
    {7,IR(525, 6),IR(45825, 13),IR(1, 0)}, // DebugTypedef in nonsemantic_shader_debuginfo_100
    {8,IR(375, 3),IR(45838, 18),IR(1, 0)}, // DebugTypeFunction in nonsemantic_shader_debuginfo_100
    {9,IR(888, 9),IR(45856, 14),IR(1, 0)}, // DebugTypeEnum in nonsemantic_shader_debuginfo_100
    {10,IR(897, 10),IR(45908, 19),IR(1, 0)}, // DebugTypeComposite in nonsemantic_shader_debuginfo_100
    {11,IR(907, 9),IR(45927, 16),IR(1, 0)}, // DebugTypeMember in nonsemantic_shader_debuginfo_100
    {12,IR(296, 4),IR(45943, 21),IR(1, 0)}, // DebugTypeInheritance in nonsemantic_shader_debuginfo_100
    {13,IR(36, 2),IR(45964, 21),IR(1, 0)}, // DebugTypePtrToMember in nonsemantic_shader_debuginfo_100
    {14,IR(168, 2),IR(45985, 18),IR(1, 0)}, // DebugTypeTemplate in nonsemantic_shader_debuginfo_100
    {15,IR(525, 6),IR(46003, 27),IR(1, 0)}, // DebugTypeTemplateParameter in nonsemantic_shader_debuginfo_100
    {16,IR(634, 5),IR(46030, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in nonsemantic_shader_debuginfo_100
    {17,IR(916, 5),IR(46065, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in nonsemantic_shader_debuginfo_100
    {18,IR(921, 10),IR(46096, 20),IR(1, 0)}, // DebugGlobalVariable in nonsemantic_shader_debuginfo_100
    {19,IR(471, 8),IR(46116, 25),IR(1, 0)}, // DebugFunctionDeclaration in nonsemantic_shader_debuginfo_100
    {20,IR(921, 10),IR(46141, 14),IR(1, 0)}, // DebugFunction in nonsemantic_shader_debuginfo_100
    {21,IR(883, 5),IR(46155, 18),IR(1, 0)}, // DebugLexicalBlock in nonsemantic_shader_debuginfo_100
    {22,IR(33, 3),IR(46173, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in nonsemantic_shader_debuginfo_100
    {23,IR(860, 2),IR(46204, 11),IR(1, 0)}, // DebugScope in nonsemantic_shader_debuginfo_100
    {24,IR(0, 0),IR(46215, 13),IR(1, 0)}, // DebugNoScope in nonsemantic_shader_debuginfo_100
    {25,IR(931, 3),IR(46228, 15),IR(1, 0)}, // DebugInlinedAt in nonsemantic_shader_debuginfo_100
    {26,IR(934, 8),IR(46285, 19),IR(1, 0)}, // DebugLocalVariable in nonsemantic_shader_debuginfo_100
    {27,IR(36, 2),IR(46304, 21),IR(1, 0)}, // DebugInlinedVariable in nonsemantic_shader_debuginfo_100
    {28,IR(942, 4),IR(46325, 13),IR(1, 0)}, // DebugDeclare in nonsemantic_shader_debuginfo_100
    {29,IR(942, 4),IR(46338, 11),IR(1, 0)}, // DebugValue in nonsemantic_shader_debuginfo_100
    {30,IR(168, 2),IR(46382, 15),IR(1, 0)}, // DebugOperation in nonsemantic_shader_debuginfo_100
    {31,IR(706, 1),IR(46397, 16),IR(1, 0)}, // DebugExpression in nonsemantic_shader_debuginfo_100
    {32,IR(577, 4),IR(46413, 14),IR(1, 0)}, // DebugMacroDef in nonsemantic_shader_debuginfo_100
    {33,IR(33, 3),IR(46427, 16),IR(1, 0)}, // DebugMacroUndef in nonsemantic_shader_debuginfo_100
    {34,IR(506, 7),IR(48182, 20),IR(1, 0)}, // DebugImportedEntity in nonsemantic_shader_debuginfo_100
    {35,IR(860, 2),IR(48202, 12),IR(1, 0)}, // DebugSource in nonsemantic_shader_debuginfo_100
    {101,IR(36, 2),IR(48214, 24),IR(1, 0)}, // DebugFunctionDefinition in nonsemantic_shader_debuginfo_100
    {102,IR(10, 1),IR(48238, 21),IR(1, 0)}, // DebugSourceContinued in nonsemantic_shader_debuginfo_100
    {103,IR(634, 5),IR(48259, 10),IR(1, 0)}, // DebugLine in nonsemantic_shader_debuginfo_100
    {104,IR(0, 0),IR(48269, 12),IR(1, 0)}, // DebugNoLine in nonsemantic_shader_debuginfo_100
    {105,IR(36, 2),IR(48281, 21),IR(1, 0)}, // DebugBuildIdentifier in nonsemantic_shader_debuginfo_100
    {106,IR(10, 1),IR(48302, 17),IR(1, 0)}, // DebugStoragePath in nonsemantic_shader_debuginfo_100
    {107,IR(296, 4),IR(48319, 16),IR(1, 0)}, // DebugEntryPoint in nonsemantic_shader_debuginfo_100
    {108,IR(33, 3),IR(48335, 16),IR(1, 0)}, // DebugTypeMatrix in nonsemantic_shader_debuginfo_100
    {1,IR(724, 9),IR(48351, 14),IR(1, 0)}, // Configuration in nonsemantic_vkspreflection
    {2,IR(10, 1),IR(48365, 13),IR(1, 0)}, // StartCounter in nonsemantic_vkspreflection
    {3,IR(10, 1),IR(48378, 12),IR(1, 0)}, // StopCounter in nonsemantic_vkspreflection
    {4,IR(296, 4),IR(48390, 14),IR(1, 0)}, // PushConstants in nonsemantic_vkspreflection
    {5,IR(33, 3),IR(48404, 23),IR(1, 0)}, // SpecializationMapEntry in nonsemantic_vkspreflection
    {6,IR(946, 15),IR(48427, 20),IR(1, 0)}, // DescriptorSetBuffer in nonsemantic_vkspreflection
    {7,IR(961, 33),IR(48447, 19),IR(1, 0)}, // DescriptorSetImage in nonsemantic_vkspreflection
    {8,IR(994, 19),IR(48466, 21),IR(1, 0)}, // DescriptorSetSampler in nonsemantic_vkspreflection
    {0,IR(0, 0),IR(45584, 14),IR(1, 0)}, // DebugInfoNone in opencl_debuginfo_100
    {1,IR(1013, 4),IR(45598, 21),IR(1, 0)}, // DebugCompilationUnit in opencl_debuginfo_100
    {2,IR(1017, 3),IR(45671, 15),IR(1, 0)}, // DebugTypeBasic in opencl_debuginfo_100
    {3,IR(1020, 3),IR(45720, 17),IR(1, 0)}, // DebugTypePointer in opencl_debuginfo_100
    {4,IR(1023, 2),IR(45775, 19),IR(1, 0)}, // DebugTypeQualifier in opencl_debuginfo_100
    {5,IR(168, 2),IR(45794, 15),IR(1, 0)}, // DebugTypeArray in opencl_debuginfo_100
    {6,IR(261, 2),IR(45809, 16),IR(1, 0)}, // DebugTypeVector in opencl_debuginfo_100
    {7,IR(778, 6),IR(45825, 13),IR(1, 0)}, // DebugTypedef in opencl_debuginfo_100
    {8,IR(1025, 3),IR(45838, 18),IR(1, 0)}, // DebugTypeFunction in opencl_debuginfo_100
    {9,IR(1028, 9),IR(45856, 14),IR(1, 0)}, // DebugTypeEnum in opencl_debuginfo_100
    {10,IR(1037, 10),IR(45908, 19),IR(1, 0)}, // DebugTypeComposite in opencl_debuginfo_100
    {11,IR(1047, 10),IR(45927, 16),IR(1, 0)}, // DebugTypeMember in opencl_debuginfo_100
    {12,IR(1057, 5),IR(45943, 21),IR(1, 0)}, // DebugTypeInheritance in opencl_debuginfo_100
    {13,IR(36, 2),IR(45964, 21),IR(1, 0)}, // DebugTypePtrToMember in opencl_debuginfo_100
    {14,IR(168, 2),IR(45985, 18),IR(1, 0)}, // DebugTypeTemplate in opencl_debuginfo_100
    {15,IR(817, 6),IR(46003, 27),IR(1, 0)}, // DebugTypeTemplateParameter in opencl_debuginfo_100
    {16,IR(823, 5),IR(46030, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in opencl_debuginfo_100
    {17,IR(828, 5),IR(46065, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in opencl_debuginfo_100
    {18,IR(1047, 10),IR(46096, 20),IR(1, 0)}, // DebugGlobalVariable in opencl_debuginfo_100
    {19,IR(1062, 8),IR(46116, 25),IR(1, 0)}, // DebugFunctionDeclaration in opencl_debuginfo_100
    {20,IR(1070, 11),IR(46141, 14),IR(1, 0)}, // DebugFunction in opencl_debuginfo_100
    {21,IR(852, 5),IR(46155, 18),IR(1, 0)}, // DebugLexicalBlock in opencl_debuginfo_100
    {22,IR(857, 3),IR(46173, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in opencl_debuginfo_100
    {23,IR(860, 2),IR(46204, 11),IR(1, 0)}, // DebugScope in opencl_debuginfo_100
    {24,IR(0, 0),IR(46215, 13),IR(1, 0)}, // DebugNoScope in opencl_debuginfo_100
    {25,IR(862, 3),IR(46228, 15),IR(1, 0)}, // DebugInlinedAt in opencl_debuginfo_100
    {26,IR(1081, 8),IR(46285, 19),IR(1, 0)}, // DebugLocalVariable in opencl_debuginfo_100
    {27,IR(36, 2),IR(46304, 21),IR(1, 0)}, // DebugInlinedVariable in opencl_debuginfo_100
    {28,IR(33, 3),IR(46325, 13),IR(1, 0)}, // DebugDeclare in opencl_debuginfo_100
    {29,IR(942, 4),IR(46338, 11),IR(1, 0)}, // DebugValue in opencl_debuginfo_100
    {30,IR(1089, 2),IR(46382, 15),IR(1, 0)}, // DebugOperation in opencl_debuginfo_100
    {31,IR(706, 1),IR(46397, 16),IR(1, 0)}, // DebugExpression in opencl_debuginfo_100
    {32,IR(874, 4),IR(46413, 14),IR(1, 0)}, // DebugMacroDef in opencl_debuginfo_100
    {33,IR(857, 3),IR(46427, 16),IR(1, 0)}, // DebugMacroUndef in opencl_debuginfo_100
    {34,IR(1091, 7),IR(48182, 20),IR(1, 0)}, // DebugImportedEntity in opencl_debuginfo_100
    {35,IR(860, 2),IR(48202, 12),IR(1, 0)}, // DebugSource in opencl_debuginfo_100
    {36,IR(1098, 8),IR(48787, 17),IR(1, 0)}, // DebugModuleINTEL in opencl_debuginfo_100
    {0,IR(10, 1),IR(48804, 5),IR(1, 0)}, // acos in opencl_std_100
    {1,IR(10, 1),IR(48809, 6),IR(1, 0)}, // acosh in opencl_std_100
    {2,IR(10, 1),IR(48815, 7),IR(1, 0)}, // acospi in opencl_std_100
    {3,IR(10, 1),IR(48822, 5),IR(1, 0)}, // asin in opencl_std_100
    {4,IR(10, 1),IR(48827, 6),IR(1, 0)}, // asinh in opencl_std_100
    {5,IR(10, 1),IR(48833, 7),IR(1, 0)}, // asinpi in opencl_std_100
    {6,IR(10, 1),IR(48840, 5),IR(1, 0)}, // atan in opencl_std_100
    {7,IR(36, 2),IR(48845, 6),IR(1, 0)}, // atan2 in opencl_std_100
    {8,IR(10, 1),IR(48851, 6),IR(1, 0)}, // atanh in opencl_std_100
    {9,IR(10, 1),IR(48857, 7),IR(1, 0)}, // atanpi in opencl_std_100
    {10,IR(36, 2),IR(48864, 8),IR(1, 0)}, // atan2pi in opencl_std_100
    {11,IR(10, 1),IR(48872, 5),IR(1, 0)}, // cbrt in opencl_std_100
    {12,IR(10, 1),IR(48877, 5),IR(1, 0)}, // ceil in opencl_std_100
    {13,IR(36, 2),IR(48882, 9),IR(1, 0)}, // copysign in opencl_std_100
    {14,IR(10, 1),IR(48891, 4),IR(1, 0)}, // cos in opencl_std_100
    {15,IR(10, 1),IR(48895, 5),IR(1, 0)}, // cosh in opencl_std_100
    {16,IR(10, 1),IR(48900, 6),IR(1, 0)}, // cospi in opencl_std_100
    {17,IR(10, 1),IR(48906, 5),IR(1, 0)}, // erfc in opencl_std_100
    {18,IR(10, 1),IR(48911, 4),IR(1, 0)}, // erf in opencl_std_100
    {19,IR(10, 1),IR(48915, 4),IR(1, 0)}, // exp in opencl_std_100
    {20,IR(10, 1),IR(48919, 5),IR(1, 0)}, // exp2 in opencl_std_100
    {21,IR(10, 1),IR(48924, 6),IR(1, 0)}, // exp10 in opencl_std_100
    {22,IR(10, 1),IR(48930, 6),IR(1, 0)}, // expm1 in opencl_std_100
    {23,IR(10, 1),IR(48936, 5),IR(1, 0)}, // fabs in opencl_std_100
    {24,IR(36, 2),IR(48941, 5),IR(1, 0)}, // fdim in opencl_std_100
    {25,IR(10, 1),IR(48946, 6),IR(1, 0)}, // floor in opencl_std_100
    {26,IR(33, 3),IR(48952, 4),IR(1, 0)}, // fma in opencl_std_100
    {27,IR(36, 2),IR(48956, 5),IR(1, 0)}, // fmax in opencl_std_100
    {28,IR(36, 2),IR(48961, 5),IR(1, 0)}, // fmin in opencl_std_100
    {29,IR(36, 2),IR(48966, 5),IR(1, 0)}, // fmod in opencl_std_100
    {30,IR(36, 2),IR(48971, 6),IR(1, 0)}, // fract in opencl_std_100
    {31,IR(36, 2),IR(48977, 6),IR(1, 0)}, // frexp in opencl_std_100
    {32,IR(36, 2),IR(48983, 6),IR(1, 0)}, // hypot in opencl_std_100
    {33,IR(10, 1),IR(48989, 6),IR(1, 0)}, // ilogb in opencl_std_100
    {34,IR(36, 2),IR(48995, 6),IR(1, 0)}, // ldexp in opencl_std_100
    {35,IR(10, 1),IR(49001, 7),IR(1, 0)}, // lgamma in opencl_std_100
    {36,IR(36, 2),IR(49008, 9),IR(1, 0)}, // lgamma_r in opencl_std_100
    {37,IR(10, 1),IR(49017, 4),IR(1, 0)}, // log in opencl_std_100
    {38,IR(10, 1),IR(49021, 5),IR(1, 0)}, // log2 in opencl_std_100
    {39,IR(10, 1),IR(49026, 6),IR(1, 0)}, // log10 in opencl_std_100
    {40,IR(10, 1),IR(49032, 6),IR(1, 0)}, // log1p in opencl_std_100
    {41,IR(10, 1),IR(49038, 5),IR(1, 0)}, // logb in opencl_std_100
    {42,IR(33, 3),IR(49043, 4),IR(1, 0)}, // mad in opencl_std_100
    {43,IR(36, 2),IR(49047, 7),IR(1, 0)}, // maxmag in opencl_std_100
    {44,IR(36, 2),IR(49054, 7),IR(1, 0)}, // minmag in opencl_std_100
    {45,IR(36, 2),IR(49061, 5),IR(1, 0)}, // modf in opencl_std_100
    {46,IR(10, 1),IR(49066, 4),IR(1, 0)}, // nan in opencl_std_100
    {47,IR(36, 2),IR(49070, 10),IR(1, 0)}, // nextafter in opencl_std_100
    {48,IR(36, 2),IR(49080, 4),IR(1, 0)}, // pow in opencl_std_100
    {49,IR(36, 2),IR(49084, 5),IR(1, 0)}, // pown in opencl_std_100
    {50,IR(36, 2),IR(49089, 5),IR(1, 0)}, // powr in opencl_std_100
    {51,IR(36, 2),IR(49094, 10),IR(1, 0)}, // remainder in opencl_std_100
    {52,IR(33, 3),IR(49104, 7),IR(1, 0)}, // remquo in opencl_std_100
    {53,IR(10, 1),IR(49111, 5),IR(1, 0)}, // rint in opencl_std_100
    {54,IR(36, 2),IR(49116, 6),IR(1, 0)}, // rootn in opencl_std_100
    {55,IR(10, 1),IR(49122, 6),IR(1, 0)}, // round in opencl_std_100
    {56,IR(10, 1),IR(49128, 6),IR(1, 0)}, // rsqrt in opencl_std_100
    {57,IR(10, 1),IR(49134, 4),IR(1, 0)}, // sin in opencl_std_100
    {58,IR(36, 2),IR(49138, 7),IR(1, 0)}, // sincos in opencl_std_100
    {59,IR(10, 1),IR(49145, 5),IR(1, 0)}, // sinh in opencl_std_100
    {60,IR(10, 1),IR(49150, 6),IR(1, 0)}, // sinpi in opencl_std_100
    {61,IR(10, 1),IR(49156, 5),IR(1, 0)}, // sqrt in opencl_std_100
    {62,IR(10, 1),IR(49161, 4),IR(1, 0)}, // tan in opencl_std_100
    {63,IR(10, 1),IR(49165, 5),IR(1, 0)}, // tanh in opencl_std_100
    {64,IR(10, 1),IR(49170, 6),IR(1, 0)}, // tanpi in opencl_std_100
    {65,IR(10, 1),IR(49176, 7),IR(1, 0)}, // tgamma in opencl_std_100
    {66,IR(10, 1),IR(49183, 6),IR(1, 0)}, // trunc in opencl_std_100
    {67,IR(10, 1),IR(49189, 9),IR(1, 0)}, // half_cos in opencl_std_100
    {68,IR(36, 2),IR(49198, 12),IR(1, 0)}, // half_divide in opencl_std_100
    {69,IR(10, 1),IR(49210, 9),IR(1, 0)}, // half_exp in opencl_std_100
    {70,IR(10, 1),IR(49219, 10),IR(1, 0)}, // half_exp2 in opencl_std_100
    {71,IR(10, 1),IR(49229, 11),IR(1, 0)}, // half_exp10 in opencl_std_100
    {72,IR(10, 1),IR(49240, 9),IR(1, 0)}, // half_log in opencl_std_100
    {73,IR(10, 1),IR(49249, 10),IR(1, 0)}, // half_log2 in opencl_std_100
    {74,IR(10, 1),IR(49259, 11),IR(1, 0)}, // half_log10 in opencl_std_100
    {75,IR(36, 2),IR(49270, 10),IR(1, 0)}, // half_powr in opencl_std_100
    {76,IR(10, 1),IR(49280, 11),IR(1, 0)}, // half_recip in opencl_std_100
    {77,IR(10, 1),IR(49291, 11),IR(1, 0)}, // half_rsqrt in opencl_std_100
    {78,IR(10, 1),IR(49302, 9),IR(1, 0)}, // half_sin in opencl_std_100
    {79,IR(10, 1),IR(49311, 10),IR(1, 0)}, // half_sqrt in opencl_std_100
    {80,IR(10, 1),IR(49321, 9),IR(1, 0)}, // half_tan in opencl_std_100
    {81,IR(10, 1),IR(49330, 11),IR(1, 0)}, // native_cos in opencl_std_100
    {82,IR(36, 2),IR(49341, 14),IR(1, 0)}, // native_divide in opencl_std_100
    {83,IR(10, 1),IR(49355, 11),IR(1, 0)}, // native_exp in opencl_std_100
    {84,IR(10, 1),IR(49366, 12),IR(1, 0)}, // native_exp2 in opencl_std_100
    {85,IR(10, 1),IR(49378, 13),IR(1, 0)}, // native_exp10 in opencl_std_100
    {86,IR(10, 1),IR(49391, 11),IR(1, 0)}, // native_log in opencl_std_100
    {87,IR(10, 1),IR(49402, 12),IR(1, 0)}, // native_log2 in opencl_std_100
    {88,IR(10, 1),IR(49414, 13),IR(1, 0)}, // native_log10 in opencl_std_100
    {89,IR(36, 2),IR(49427, 12),IR(1, 0)}, // native_powr in opencl_std_100
    {90,IR(10, 1),IR(49439, 13),IR(1, 0)}, // native_recip in opencl_std_100
    {91,IR(10, 1),IR(49452, 13),IR(1, 0)}, // native_rsqrt in opencl_std_100
    {92,IR(10, 1),IR(49465, 11),IR(1, 0)}, // native_sin in opencl_std_100
    {93,IR(10, 1),IR(49476, 12),IR(1, 0)}, // native_sqrt in opencl_std_100
    {94,IR(10, 1),IR(49488, 11),IR(1, 0)}, // native_tan in opencl_std_100
    {95,IR(33, 3),IR(49499, 7),IR(1, 0)}, // fclamp in opencl_std_100
    {96,IR(10, 1),IR(49506, 8),IR(1, 0)}, // degrees in opencl_std_100
    {97,IR(36, 2),IR(49514, 12),IR(1, 0)}, // fmax_common in opencl_std_100
    {98,IR(36, 2),IR(49526, 12),IR(1, 0)}, // fmin_common in opencl_std_100
    {99,IR(33, 3),IR(49538, 4),IR(1, 0)}, // mix in opencl_std_100
    {100,IR(10, 1),IR(49542, 8),IR(1, 0)}, // radians in opencl_std_100
    {101,IR(36, 2),IR(49550, 5),IR(1, 0)}, // step in opencl_std_100
    {102,IR(33, 3),IR(49555, 11),IR(1, 0)}, // smoothstep in opencl_std_100
    {103,IR(10, 1),IR(49566, 5),IR(1, 0)}, // sign in opencl_std_100
    {104,IR(36, 2),IR(49571, 6),IR(1, 0)}, // cross in opencl_std_100
    {105,IR(36, 2),IR(49577, 9),IR(1, 0)}, // distance in opencl_std_100
    {106,IR(10, 1),IR(49586, 7),IR(1, 0)}, // length in opencl_std_100
    {107,IR(10, 1),IR(49593, 10),IR(1, 0)}, // normalize in opencl_std_100
    {108,IR(36, 2),IR(49603, 14),IR(1, 0)}, // fast_distance in opencl_std_100
    {109,IR(10, 1),IR(49617, 12),IR(1, 0)}, // fast_length in opencl_std_100
    {110,IR(10, 1),IR(49629, 15),IR(1, 0)}, // fast_normalize in opencl_std_100
    {141,IR(10, 1),IR(49644, 6),IR(1, 0)}, // s_abs in opencl_std_100
    {142,IR(36, 2),IR(49650, 11),IR(1, 0)}, // s_abs_diff in opencl_std_100
    {143,IR(36, 2),IR(49661, 10),IR(1, 0)}, // s_add_sat in opencl_std_100
    {144,IR(36, 2),IR(49671, 10),IR(1, 0)}, // u_add_sat in opencl_std_100
    {145,IR(36, 2),IR(49681, 7),IR(1, 0)}, // s_hadd in opencl_std_100
    {146,IR(36, 2),IR(49688, 7),IR(1, 0)}, // u_hadd in opencl_std_100
    {147,IR(36, 2),IR(49695, 8),IR(1, 0)}, // s_rhadd in opencl_std_100
    {148,IR(36, 2),IR(49703, 8),IR(1, 0)}, // u_rhadd in opencl_std_100
    {149,IR(33, 3),IR(49711, 8),IR(1, 0)}, // s_clamp in opencl_std_100
    {150,IR(33, 3),IR(49719, 8),IR(1, 0)}, // u_clamp in opencl_std_100
    {151,IR(10, 1),IR(49727, 4),IR(1, 0)}, // clz in opencl_std_100
    {152,IR(10, 1),IR(49731, 4),IR(1, 0)}, // ctz in opencl_std_100
    {153,IR(33, 3),IR(49735, 9),IR(1, 0)}, // s_mad_hi in opencl_std_100
    {154,IR(33, 3),IR(49744, 10),IR(1, 0)}, // u_mad_sat in opencl_std_100
    {155,IR(33, 3),IR(49754, 10),IR(1, 0)}, // s_mad_sat in opencl_std_100
    {156,IR(36, 2),IR(49764, 6),IR(1, 0)}, // s_max in opencl_std_100
    {157,IR(36, 2),IR(49770, 6),IR(1, 0)}, // u_max in opencl_std_100
    {158,IR(36, 2),IR(49776, 6),IR(1, 0)}, // s_min in opencl_std_100
    {159,IR(36, 2),IR(49782, 6),IR(1, 0)}, // u_min in opencl_std_100
    {160,IR(36, 2),IR(49788, 9),IR(1, 0)}, // s_mul_hi in opencl_std_100
    {161,IR(36, 2),IR(49797, 7),IR(1, 0)}, // rotate in opencl_std_100
    {162,IR(36, 2),IR(49804, 10),IR(1, 0)}, // s_sub_sat in opencl_std_100
    {163,IR(36, 2),IR(49814, 10),IR(1, 0)}, // u_sub_sat in opencl_std_100
    {164,IR(36, 2),IR(49824, 11),IR(1, 0)}, // u_upsample in opencl_std_100
    {165,IR(36, 2),IR(49835, 11),IR(1, 0)}, // s_upsample in opencl_std_100
    {166,IR(10, 1),IR(49846, 9),IR(1, 0)}, // popcount in opencl_std_100
    {167,IR(33, 3),IR(49855, 8),IR(1, 0)}, // s_mad24 in opencl_std_100
    {168,IR(33, 3),IR(49863, 8),IR(1, 0)}, // u_mad24 in opencl_std_100
    {169,IR(36, 2),IR(49871, 8),IR(1, 0)}, // s_mul24 in opencl_std_100
    {170,IR(36, 2),IR(49879, 8),IR(1, 0)}, // u_mul24 in opencl_std_100
    {171,IR(1106, 3),IR(49887, 7),IR(1, 0)}, // vloadn in opencl_std_100
    {172,IR(33, 3),IR(49894, 8),IR(1, 0)}, // vstoren in opencl_std_100
    {173,IR(36, 2),IR(49902, 11),IR(1, 0)}, // vload_half in opencl_std_100
    {174,IR(1106, 3),IR(49913, 12),IR(1, 0)}, // vload_halfn in opencl_std_100
    {175,IR(33, 3),IR(49925, 12),IR(1, 0)}, // vstore_half in opencl_std_100
    {176,IR(1109, 4),IR(49937, 14),IR(1, 0)}, // vstore_half_r in opencl_std_100
    {177,IR(33, 3),IR(49951, 13),IR(1, 0)}, // vstore_halfn in opencl_std_100
    {178,IR(1109, 4),IR(49964, 15),IR(1, 0)}, // vstore_halfn_r in opencl_std_100
    {179,IR(1106, 3),IR(49979, 13),IR(1, 0)}, // vloada_halfn in opencl_std_100
    {180,IR(33, 3),IR(49992, 14),IR(1, 0)}, // vstorea_halfn in opencl_std_100
    {181,IR(1109, 4),IR(50006, 16),IR(1, 0)}, // vstorea_halfn_r in opencl_std_100
    {182,IR(36, 2),IR(50022, 8),IR(1, 0)}, // shuffle in opencl_std_100
    {183,IR(33, 3),IR(50030, 9),IR(1, 0)}, // shuffle2 in opencl_std_100
    {184,IR(168, 2),IR(50039, 7),IR(1, 0)}, // printf in opencl_std_100
    {185,IR(36, 2),IR(50046, 9),IR(1, 0)}, // prefetch in opencl_std_100
    {186,IR(33, 3),IR(50055, 10),IR(1, 0)}, // bitselect in opencl_std_100
    {187,IR(33, 3),IR(50065, 7),IR(1, 0)}, // select in opencl_std_100
    {201,IR(10, 1),IR(50072, 6),IR(1, 0)}, // u_abs in opencl_std_100
    {202,IR(36, 2),IR(50078, 11),IR(1, 0)}, // u_abs_diff in opencl_std_100
    {203,IR(36, 2),IR(50089, 9),IR(1, 0)}, // u_mul_hi in opencl_std_100
    {204,IR(33, 3),IR(50098, 9),IR(1, 0)}, // u_mad_hi in opencl_std_100
    {1,IR(10, 1),IR(50107, 17),IR(1, 0)}, // CubeFaceIndexAMD in spv_amd_gcn_shader
    {2,IR(10, 1),IR(50124, 17),IR(1, 0)}, // CubeFaceCoordAMD in spv_amd_gcn_shader
    {3,IR(0, 0),IR(50141, 8),IR(1, 0)}, // TimeAMD in spv_amd_gcn_shader
    {1,IR(36, 2),IR(50149, 22),IR(1, 0)}, // SwizzleInvocationsAMD in spv_amd_shader_ballot
    {2,IR(36, 2),IR(50171, 28),IR(1, 0)}, // SwizzleInvocationsMaskedAMD in spv_amd_shader_ballot
    {3,IR(33, 3),IR(50199, 19),IR(1, 0)}, // WriteInvocationAMD in spv_amd_shader_ballot
    {4,IR(10, 1),IR(50218, 9),IR(1, 0)}, // MbcntAMD in spv_amd_shader_ballot
    {1,IR(36, 2),IR(50227, 23),IR(1, 0)}, // InterpolateAtVertexAMD in spv_amd_shader_explicit_vertex_parameter
    {1,IR(33, 3),IR(50250, 9),IR(1, 0)}, // FMin3AMD in spv_amd_shader_trinary_minmax
    {2,IR(33, 3),IR(50259, 9),IR(1, 0)}, // UMin3AMD in spv_amd_shader_trinary_minmax
    {3,IR(33, 3),IR(50268, 9),IR(1, 0)}, // SMin3AMD in spv_amd_shader_trinary_minmax
    {4,IR(33, 3),IR(50277, 9),IR(1, 0)}, // FMax3AMD in spv_amd_shader_trinary_minmax
    {5,IR(33, 3),IR(50286, 9),IR(1, 0)}, // UMax3AMD in spv_amd_shader_trinary_minmax
    {6,IR(33, 3),IR(50295, 9),IR(1, 0)}, // SMax3AMD in spv_amd_shader_trinary_minmax
    {7,IR(33, 3),IR(50304, 9),IR(1, 0)}, // FMid3AMD in spv_amd_shader_trinary_minmax
    {8,IR(33, 3),IR(50313, 9),IR(1, 0)}, // UMid3AMD in spv_amd_shader_trinary_minmax
    {9,IR(33, 3),IR(50322, 9),IR(1, 0)}, // SMid3AMD in spv_amd_shader_trinary_minmax
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
    {IR(45598, 21), 1}, // DebugCompilationUnit in debuginfo
    {IR(46325, 13), 28}, // DebugDeclare in debuginfo
    {IR(46397, 16), 31}, // DebugExpression in debuginfo
    {IR(46141, 14), 20}, // DebugFunction in debuginfo
    {IR(46116, 25), 19}, // DebugFunctionDeclaration in debuginfo
    {IR(46096, 20), 18}, // DebugGlobalVariable in debuginfo
    {IR(45584, 14), 0}, // DebugInfoNone in debuginfo
    {IR(46228, 15), 25}, // DebugInlinedAt in debuginfo
    {IR(46304, 21), 27}, // DebugInlinedVariable in debuginfo
    {IR(46155, 18), 21}, // DebugLexicalBlock in debuginfo
    {IR(46173, 31), 22}, // DebugLexicalBlockDiscriminator in debuginfo
    {IR(46285, 19), 26}, // DebugLocalVariable in debuginfo
    {IR(46413, 14), 32}, // DebugMacroDef in debuginfo
    {IR(46427, 16), 33}, // DebugMacroUndef in debuginfo
    {IR(46215, 13), 24}, // DebugNoScope in debuginfo
    {IR(46382, 15), 30}, // DebugOperation in debuginfo
    {IR(46204, 11), 23}, // DebugScope in debuginfo
    {IR(45794, 15), 5}, // DebugTypeArray in debuginfo
    {IR(45671, 15), 2}, // DebugTypeBasic in debuginfo
    {IR(45908, 19), 10}, // DebugTypeComposite in debuginfo
    {IR(45856, 14), 9}, // DebugTypeEnum in debuginfo
    {IR(45838, 18), 8}, // DebugTypeFunction in debuginfo
    {IR(45943, 21), 12}, // DebugTypeInheritance in debuginfo
    {IR(45927, 16), 11}, // DebugTypeMember in debuginfo
    {IR(45720, 17), 3}, // DebugTypePointer in debuginfo
    {IR(45964, 21), 13}, // DebugTypePtrToMember in debuginfo
    {IR(45775, 19), 4}, // DebugTypeQualifier in debuginfo
    {IR(45985, 18), 14}, // DebugTypeTemplate in debuginfo
    {IR(46003, 27), 15}, // DebugTypeTemplateParameter in debuginfo
    {IR(46065, 31), 17}, // DebugTypeTemplateParameterPack in debuginfo
    {IR(46030, 35), 16}, // DebugTypeTemplateTemplateParameter in debuginfo
    {IR(45809, 16), 6}, // DebugTypeVector in debuginfo
    {IR(45825, 13), 7}, // DebugTypedef in debuginfo
    {IR(46338, 11), 29}, // DebugValue in debuginfo
    {IR(46537, 5), 50}, // Acos in glsl_std_450
    {IR(46568, 6), 56}, // Acosh in glsl_std_450
    {IR(46532, 5), 49}, // Asin in glsl_std_450
    {IR(46562, 6), 55}, // Asinh in glsl_std_450
    {IR(46542, 5), 51}, // Atan in glsl_std_450
    {IR(46580, 6), 58}, // Atan2 in glsl_std_450
    {IR(46574, 6), 57}, // Atanh in glsl_std_450
    {IR(46493, 5), 42}, // Ceil in glsl_std_450
    {IR(46524, 4), 47}, // Cos in glsl_std_450
    {IR(46552, 5), 53}, // Cosh in glsl_std_450
    {IR(46964, 6), 101}, // Cross in glsl_std_450
    {IR(46512, 8), 45}, // Degrees in glsl_std_450
    {IR(46625, 12), 66}, // Determinant in glsl_std_450
    {IR(46955, 9), 100}, // Distance in glsl_std_450
    {IR(46590, 4), 60}, // Exp in glsl_std_450
    {IR(46598, 5), 62}, // Exp2 in glsl_std_450
    {IR(46465, 5), 37}, // FAbs in glsl_std_450
    {IR(46697, 7), 76}, // FClamp in glsl_std_450
    {IR(46682, 5), 73}, // FMax in glsl_std_450
    {IR(46667, 5), 70}, // FMin in glsl_std_450
    {IR(46718, 5), 79}, // FMix in glsl_std_450
    {IR(46475, 6), 39}, // FSign in glsl_std_450
    {IR(46980, 12), 103}, // FaceForward in glsl_std_450
    {IR(47008, 9), 106}, // FindILsb in glsl_std_450
    {IR(47017, 9), 107}, // FindSMsb in glsl_std_450
    {IR(47026, 9), 108}, // FindUMsb in glsl_std_450
    {IR(46487, 6), 41}, // Floor in glsl_std_450
    {IR(46744, 4), 83}, // Fma in glsl_std_450
    {IR(46498, 6), 43}, // Fract in glsl_std_450
    {IR(46748, 6), 84}, // Frexp in glsl_std_450
    {IR(46754, 12), 85}, // FrexpStruct in glsl_std_450
    {IR(46723, 5), 80}, // IMix in glsl_std_450
    {IR(47035, 22), 109}, // InterpolateAtCentroid in glsl_std_450
    {IR(47077, 20), 111}, // InterpolateAtOffset in glsl_std_450
    {IR(47057, 20), 110}, // InterpolateAtSample in glsl_std_450
    {IR(46613, 12), 65}, // InverseSqrt in glsl_std_450
    {IR(46766, 6), 86}, // Ldexp in glsl_std_450
    {IR(46948, 7), 99}, // Length in glsl_std_450
    {IR(46594, 4), 61}, // Log in glsl_std_450
    {IR(46603, 5), 63}, // Log2 in glsl_std_450
    {IR(46637, 14), 67}, // MatrixInverse in glsl_std_450
    {IR(46651, 5), 68}, // Modf in glsl_std_450
    {IR(46656, 11), 69}, // ModfStruct in glsl_std_450
    {IR(47107, 7), 114}, // NClamp in glsl_std_450
    {IR(47102, 5), 113}, // NMax in glsl_std_450
    {IR(47097, 5), 112}, // NMin in glsl_std_450
    {IR(46970, 10), 102}, // Normalize in glsl_std_450
    {IR(46839, 15), 92}, // PackDouble2x32 in glsl_std_450
    {IR(46826, 13), 91}, // PackHalf2x16 in glsl_std_450
    {IR(46798, 14), 89}, // PackSnorm2x16 in glsl_std_450
    {IR(46772, 13), 87}, // PackSnorm4x8 in glsl_std_450
    {IR(46812, 14), 90}, // PackUnorm2x16 in glsl_std_450
    {IR(46785, 13), 88}, // PackUnorm4x8 in glsl_std_450
    {IR(46586, 4), 59}, // Pow in glsl_std_450
    {IR(46504, 8), 44}, // Radians in glsl_std_450
    {IR(46992, 8), 104}, // Reflect in glsl_std_450
    {IR(47000, 8), 105}, // Refract in glsl_std_450
    {IR(46443, 6), 34}, // Round in glsl_std_450
    {IR(46449, 10), 35}, // RoundEven in glsl_std_450
    {IR(46470, 5), 38}, // SAbs in glsl_std_450
    {IR(46711, 7), 78}, // SClamp in glsl_std_450
    {IR(46692, 5), 75}, // SMax in glsl_std_450
    {IR(46677, 5), 72}, // SMin in glsl_std_450
    {IR(46481, 6), 40}, // SSign in glsl_std_450
    {IR(46520, 4), 46}, // Sin in glsl_std_450
    {IR(46547, 5), 52}, // Sinh in glsl_std_450
    {IR(46733, 11), 82}, // SmoothStep in glsl_std_450
    {IR(46608, 5), 64}, // Sqrt in glsl_std_450
    {IR(46728, 5), 81}, // Step in glsl_std_450
    {IR(46528, 4), 48}, // Tan in glsl_std_450
    {IR(46557, 5), 54}, // Tanh in glsl_std_450
    {IR(46459, 6), 36}, // Trunc in glsl_std_450
    {IR(46704, 7), 77}, // UClamp in glsl_std_450
    {IR(46687, 5), 74}, // UMax in glsl_std_450
    {IR(46672, 5), 71}, // UMin in glsl_std_450
    {IR(46931, 17), 98}, // UnpackDouble2x32 in glsl_std_450
    {IR(46886, 15), 95}, // UnpackHalf2x16 in glsl_std_450
    {IR(46854, 16), 93}, // UnpackSnorm2x16 in glsl_std_450
    {IR(46901, 15), 96}, // UnpackSnorm4x8 in glsl_std_450
    {IR(46870, 16), 94}, // UnpackUnorm2x16 in glsl_std_450
    {IR(46916, 15), 97}, // UnpackUnorm4x8 in glsl_std_450
    {IR(47114, 13), 116}, // ArgumentInfo in nonsemantic_clspvreflection
    {IR(47209, 24), 121}, // ArgumentPodPushConstant in nonsemantic_clspvreflection
    {IR(47165, 25), 119}, // ArgumentPodStorageBuffer in nonsemantic_clspvreflection
    {IR(47190, 19), 120}, // ArgumentPodUniform in nonsemantic_clspvreflection
    {IR(47643, 28), 140}, // ArgumentPointerPushConstant in nonsemantic_clspvreflection
    {IR(47671, 23), 141}, // ArgumentPointerUniform in nonsemantic_clspvreflection
    {IR(47233, 21), 122}, // ArgumentSampledImage in nonsemantic_clspvreflection
    {IR(47275, 16), 124}, // ArgumentSampler in nonsemantic_clspvreflection
    {IR(47127, 22), 117}, // ArgumentStorageBuffer in nonsemantic_clspvreflection
    {IR(47254, 21), 123}, // ArgumentStorageImage in nonsemantic_clspvreflection
    {IR(47931, 27), 148}, // ArgumentStorageTexelBuffer in nonsemantic_clspvreflection
    {IR(47149, 16), 118}, // ArgumentUniform in nonsemantic_clspvreflection
    {IR(47958, 27), 149}, // ArgumentUniformTexelBuffer in nonsemantic_clspvreflection
    {IR(47291, 18), 125}, // ArgumentWorkgroup in nonsemantic_clspvreflection
    {IR(47985, 32), 150}, // ConstantDataPointerPushConstant in nonsemantic_clspvreflection
    {IR(47539, 26), 135}, // ConstantDataStorageBuffer in nonsemantic_clspvreflection
    {IR(47565, 20), 136}, // ConstantDataUniform in nonsemantic_clspvreflection
    {IR(47809, 45), 145}, // ImageArgumentInfoChannelDataTypePushConstant in nonsemantic_clspvreflection
    {IR(47891, 40), 147}, // ImageArgumentInfoChannelDataTypeUniform in nonsemantic_clspvreflection
    {IR(47767, 42), 144}, // ImageArgumentInfoChannelOrderPushConstant in nonsemantic_clspvreflection
    {IR(47854, 37), 146}, // ImageArgumentInfoChannelOrderUniform in nonsemantic_clspvreflection
    {IR(4630, 7), 115}, // Kernel in nonsemantic_clspvreflection
    {IR(8055, 15), 137}, // LiteralSampler in nonsemantic_clspvreflection
    {IR(48126, 34), 155}, // NormalizedSamplerMaskPushConstant in nonsemantic_clspvreflection
    {IR(48094, 32), 154}, // PrintfBufferPointerPushConstant in nonsemantic_clspvreflection
    {IR(48068, 26), 153}, // PrintfBufferStorageBuffer in nonsemantic_clspvreflection
    {IR(48057, 11), 152}, // PrintfInfo in nonsemantic_clspvreflection
    {IR(48017, 40), 151}, // ProgramScopeVariablePointerPushConstant in nonsemantic_clspvreflection
    {IR(47729, 38), 143}, // ProgramScopeVariablePointerRelocation in nonsemantic_clspvreflection
    {IR(47694, 35), 142}, // ProgramScopeVariablesStorageBuffer in nonsemantic_clspvreflection
    {IR(47585, 30), 138}, // PropertyRequiredWorkgroupSize in nonsemantic_clspvreflection
    {IR(47405, 30), 130}, // PushConstantEnqueuedLocalSize in nonsemantic_clspvreflection
    {IR(47380, 25), 129}, // PushConstantGlobalOffset in nonsemantic_clspvreflection
    {IR(47435, 23), 131}, // PushConstantGlobalSize in nonsemantic_clspvreflection
    {IR(47483, 26), 133}, // PushConstantNumWorkgroups in nonsemantic_clspvreflection
    {IR(47509, 30), 134}, // PushConstantRegionGroupOffset in nonsemantic_clspvreflection
    {IR(47458, 25), 132}, // PushConstantRegionOffset in nonsemantic_clspvreflection
    {IR(47335, 25), 127}, // SpecConstantGlobalOffset in nonsemantic_clspvreflection
    {IR(47615, 28), 139}, // SpecConstantSubgroupMaxSize in nonsemantic_clspvreflection
    {IR(47360, 20), 128}, // SpecConstantWorkDim in nonsemantic_clspvreflection
    {IR(47309, 26), 126}, // SpecConstantWorkgroupSize in nonsemantic_clspvreflection
    {IR(48160, 22), 156}, // WorkgroupVariableSize in nonsemantic_clspvreflection
    {IR(48281, 21), 197}, // DebugBuildIdentifier in nonsemantic_shader_debuginfo_100
    {IR(45598, 21), 158}, // DebugCompilationUnit in nonsemantic_shader_debuginfo_100
    {IR(46325, 13), 185}, // DebugDeclare in nonsemantic_shader_debuginfo_100
    {IR(48319, 16), 199}, // DebugEntryPoint in nonsemantic_shader_debuginfo_100
    {IR(46397, 16), 188}, // DebugExpression in nonsemantic_shader_debuginfo_100
    {IR(46141, 14), 177}, // DebugFunction in nonsemantic_shader_debuginfo_100
    {IR(46116, 25), 176}, // DebugFunctionDeclaration in nonsemantic_shader_debuginfo_100
    {IR(48214, 24), 193}, // DebugFunctionDefinition in nonsemantic_shader_debuginfo_100
    {IR(46096, 20), 175}, // DebugGlobalVariable in nonsemantic_shader_debuginfo_100
    {IR(48182, 20), 191}, // DebugImportedEntity in nonsemantic_shader_debuginfo_100
    {IR(45584, 14), 157}, // DebugInfoNone in nonsemantic_shader_debuginfo_100
    {IR(46228, 15), 182}, // DebugInlinedAt in nonsemantic_shader_debuginfo_100
    {IR(46304, 21), 184}, // DebugInlinedVariable in nonsemantic_shader_debuginfo_100
    {IR(46155, 18), 178}, // DebugLexicalBlock in nonsemantic_shader_debuginfo_100
    {IR(46173, 31), 179}, // DebugLexicalBlockDiscriminator in nonsemantic_shader_debuginfo_100
    {IR(48259, 10), 195}, // DebugLine in nonsemantic_shader_debuginfo_100
    {IR(46285, 19), 183}, // DebugLocalVariable in nonsemantic_shader_debuginfo_100
    {IR(46413, 14), 189}, // DebugMacroDef in nonsemantic_shader_debuginfo_100
    {IR(46427, 16), 190}, // DebugMacroUndef in nonsemantic_shader_debuginfo_100
    {IR(48269, 12), 196}, // DebugNoLine in nonsemantic_shader_debuginfo_100
    {IR(46215, 13), 181}, // DebugNoScope in nonsemantic_shader_debuginfo_100
    {IR(46382, 15), 187}, // DebugOperation in nonsemantic_shader_debuginfo_100
    {IR(46204, 11), 180}, // DebugScope in nonsemantic_shader_debuginfo_100
    {IR(48202, 12), 192}, // DebugSource in nonsemantic_shader_debuginfo_100
    {IR(48238, 21), 194}, // DebugSourceContinued in nonsemantic_shader_debuginfo_100
    {IR(48302, 17), 198}, // DebugStoragePath in nonsemantic_shader_debuginfo_100
    {IR(45794, 15), 162}, // DebugTypeArray in nonsemantic_shader_debuginfo_100
    {IR(45671, 15), 159}, // DebugTypeBasic in nonsemantic_shader_debuginfo_100
    {IR(45908, 19), 167}, // DebugTypeComposite in nonsemantic_shader_debuginfo_100
    {IR(45856, 14), 166}, // DebugTypeEnum in nonsemantic_shader_debuginfo_100
    {IR(45838, 18), 165}, // DebugTypeFunction in nonsemantic_shader_debuginfo_100
    {IR(45943, 21), 169}, // DebugTypeInheritance in nonsemantic_shader_debuginfo_100
    {IR(48335, 16), 200}, // DebugTypeMatrix in nonsemantic_shader_debuginfo_100
    {IR(45927, 16), 168}, // DebugTypeMember in nonsemantic_shader_debuginfo_100
    {IR(45720, 17), 160}, // DebugTypePointer in nonsemantic_shader_debuginfo_100
    {IR(45964, 21), 170}, // DebugTypePtrToMember in nonsemantic_shader_debuginfo_100
    {IR(45775, 19), 161}, // DebugTypeQualifier in nonsemantic_shader_debuginfo_100
    {IR(45985, 18), 171}, // DebugTypeTemplate in nonsemantic_shader_debuginfo_100
    {IR(46003, 27), 172}, // DebugTypeTemplateParameter in nonsemantic_shader_debuginfo_100
    {IR(46065, 31), 174}, // DebugTypeTemplateParameterPack in nonsemantic_shader_debuginfo_100
    {IR(46030, 35), 173}, // DebugTypeTemplateTemplateParameter in nonsemantic_shader_debuginfo_100
    {IR(45809, 16), 163}, // DebugTypeVector in nonsemantic_shader_debuginfo_100
    {IR(45825, 13), 164}, // DebugTypedef in nonsemantic_shader_debuginfo_100
    {IR(46338, 11), 186}, // DebugValue in nonsemantic_shader_debuginfo_100
    {IR(48351, 14), 201}, // Configuration in nonsemantic_vkspreflection
    {IR(48427, 20), 206}, // DescriptorSetBuffer in nonsemantic_vkspreflection
    {IR(48447, 19), 207}, // DescriptorSetImage in nonsemantic_vkspreflection
    {IR(48466, 21), 208}, // DescriptorSetSampler in nonsemantic_vkspreflection
    {IR(48390, 14), 204}, // PushConstants in nonsemantic_vkspreflection
    {IR(48404, 23), 205}, // SpecializationMapEntry in nonsemantic_vkspreflection
    {IR(48365, 13), 202}, // StartCounter in nonsemantic_vkspreflection
    {IR(48378, 12), 203}, // StopCounter in nonsemantic_vkspreflection
    {IR(45598, 21), 210}, // DebugCompilationUnit in opencl_debuginfo_100
    {IR(46325, 13), 237}, // DebugDeclare in opencl_debuginfo_100
    {IR(46397, 16), 240}, // DebugExpression in opencl_debuginfo_100
    {IR(46141, 14), 229}, // DebugFunction in opencl_debuginfo_100
    {IR(46116, 25), 228}, // DebugFunctionDeclaration in opencl_debuginfo_100
    {IR(46096, 20), 227}, // DebugGlobalVariable in opencl_debuginfo_100
    {IR(48182, 20), 243}, // DebugImportedEntity in opencl_debuginfo_100
    {IR(45584, 14), 209}, // DebugInfoNone in opencl_debuginfo_100
    {IR(46228, 15), 234}, // DebugInlinedAt in opencl_debuginfo_100
    {IR(46304, 21), 236}, // DebugInlinedVariable in opencl_debuginfo_100
    {IR(46155, 18), 230}, // DebugLexicalBlock in opencl_debuginfo_100
    {IR(46173, 31), 231}, // DebugLexicalBlockDiscriminator in opencl_debuginfo_100
    {IR(46285, 19), 235}, // DebugLocalVariable in opencl_debuginfo_100
    {IR(46413, 14), 241}, // DebugMacroDef in opencl_debuginfo_100
    {IR(46427, 16), 242}, // DebugMacroUndef in opencl_debuginfo_100
    {IR(48787, 17), 245}, // DebugModuleINTEL in opencl_debuginfo_100
    {IR(46215, 13), 233}, // DebugNoScope in opencl_debuginfo_100
    {IR(46382, 15), 239}, // DebugOperation in opencl_debuginfo_100
    {IR(46204, 11), 232}, // DebugScope in opencl_debuginfo_100
    {IR(48202, 12), 244}, // DebugSource in opencl_debuginfo_100
    {IR(45794, 15), 214}, // DebugTypeArray in opencl_debuginfo_100
    {IR(45671, 15), 211}, // DebugTypeBasic in opencl_debuginfo_100
    {IR(45908, 19), 219}, // DebugTypeComposite in opencl_debuginfo_100
    {IR(45856, 14), 218}, // DebugTypeEnum in opencl_debuginfo_100
    {IR(45838, 18), 217}, // DebugTypeFunction in opencl_debuginfo_100
    {IR(45943, 21), 221}, // DebugTypeInheritance in opencl_debuginfo_100
    {IR(45927, 16), 220}, // DebugTypeMember in opencl_debuginfo_100
    {IR(45720, 17), 212}, // DebugTypePointer in opencl_debuginfo_100
    {IR(45964, 21), 222}, // DebugTypePtrToMember in opencl_debuginfo_100
    {IR(45775, 19), 213}, // DebugTypeQualifier in opencl_debuginfo_100
    {IR(45985, 18), 223}, // DebugTypeTemplate in opencl_debuginfo_100
    {IR(46003, 27), 224}, // DebugTypeTemplateParameter in opencl_debuginfo_100
    {IR(46065, 31), 226}, // DebugTypeTemplateParameterPack in opencl_debuginfo_100
    {IR(46030, 35), 225}, // DebugTypeTemplateTemplateParameter in opencl_debuginfo_100
    {IR(45809, 16), 215}, // DebugTypeVector in opencl_debuginfo_100
    {IR(45825, 13), 216}, // DebugTypedef in opencl_debuginfo_100
    {IR(46338, 11), 238}, // DebugValue in opencl_debuginfo_100
    {IR(48804, 5), 246}, // acos in opencl_std_100
    {IR(48809, 6), 247}, // acosh in opencl_std_100
    {IR(48815, 7), 248}, // acospi in opencl_std_100
    {IR(48822, 5), 249}, // asin in opencl_std_100
    {IR(48827, 6), 250}, // asinh in opencl_std_100
    {IR(48833, 7), 251}, // asinpi in opencl_std_100
    {IR(48840, 5), 252}, // atan in opencl_std_100
    {IR(48845, 6), 253}, // atan2 in opencl_std_100
    {IR(48864, 8), 256}, // atan2pi in opencl_std_100
    {IR(48851, 6), 254}, // atanh in opencl_std_100
    {IR(48857, 7), 255}, // atanpi in opencl_std_100
    {IR(50055, 10), 402}, // bitselect in opencl_std_100
    {IR(48872, 5), 257}, // cbrt in opencl_std_100
    {IR(48877, 5), 258}, // ceil in opencl_std_100
    {IR(49727, 4), 367}, // clz in opencl_std_100
    {IR(48882, 9), 259}, // copysign in opencl_std_100
    {IR(48891, 4), 260}, // cos in opencl_std_100
    {IR(48895, 5), 261}, // cosh in opencl_std_100
    {IR(48900, 6), 262}, // cospi in opencl_std_100
    {IR(49571, 6), 350}, // cross in opencl_std_100
    {IR(49731, 4), 368}, // ctz in opencl_std_100
    {IR(49506, 8), 342}, // degrees in opencl_std_100
    {IR(49577, 9), 351}, // distance in opencl_std_100
    {IR(48911, 4), 264}, // erf in opencl_std_100
    {IR(48906, 5), 263}, // erfc in opencl_std_100
    {IR(48915, 4), 265}, // exp in opencl_std_100
    {IR(48924, 6), 267}, // exp10 in opencl_std_100
    {IR(48919, 5), 266}, // exp2 in opencl_std_100
    {IR(48930, 6), 268}, // expm1 in opencl_std_100
    {IR(48936, 5), 269}, // fabs in opencl_std_100
    {IR(49603, 14), 354}, // fast_distance in opencl_std_100
    {IR(49617, 12), 355}, // fast_length in opencl_std_100
    {IR(49629, 15), 356}, // fast_normalize in opencl_std_100
    {IR(49499, 7), 341}, // fclamp in opencl_std_100
    {IR(48941, 5), 270}, // fdim in opencl_std_100
    {IR(48946, 6), 271}, // floor in opencl_std_100
    {IR(48952, 4), 272}, // fma in opencl_std_100
    {IR(48956, 5), 273}, // fmax in opencl_std_100
    {IR(49514, 12), 343}, // fmax_common in opencl_std_100
    {IR(48961, 5), 274}, // fmin in opencl_std_100
    {IR(49526, 12), 344}, // fmin_common in opencl_std_100
    {IR(48966, 5), 275}, // fmod in opencl_std_100
    {IR(48971, 6), 276}, // fract in opencl_std_100
    {IR(48977, 6), 277}, // frexp in opencl_std_100
    {IR(49189, 9), 313}, // half_cos in opencl_std_100
    {IR(49198, 12), 314}, // half_divide in opencl_std_100
    {IR(49210, 9), 315}, // half_exp in opencl_std_100
    {IR(49229, 11), 317}, // half_exp10 in opencl_std_100
    {IR(49219, 10), 316}, // half_exp2 in opencl_std_100
    {IR(49240, 9), 318}, // half_log in opencl_std_100
    {IR(49259, 11), 320}, // half_log10 in opencl_std_100
    {IR(49249, 10), 319}, // half_log2 in opencl_std_100
    {IR(49270, 10), 321}, // half_powr in opencl_std_100
    {IR(49280, 11), 322}, // half_recip in opencl_std_100
    {IR(49291, 11), 323}, // half_rsqrt in opencl_std_100
    {IR(49302, 9), 324}, // half_sin in opencl_std_100
    {IR(49311, 10), 325}, // half_sqrt in opencl_std_100
    {IR(49321, 9), 326}, // half_tan in opencl_std_100
    {IR(48983, 6), 278}, // hypot in opencl_std_100
    {IR(48989, 6), 279}, // ilogb in opencl_std_100
    {IR(48995, 6), 280}, // ldexp in opencl_std_100
    {IR(49586, 7), 352}, // length in opencl_std_100
    {IR(49001, 7), 281}, // lgamma in opencl_std_100
    {IR(49008, 9), 282}, // lgamma_r in opencl_std_100
    {IR(49017, 4), 283}, // log in opencl_std_100
    {IR(49026, 6), 285}, // log10 in opencl_std_100
    {IR(49032, 6), 286}, // log1p in opencl_std_100
    {IR(49021, 5), 284}, // log2 in opencl_std_100
    {IR(49038, 5), 287}, // logb in opencl_std_100
    {IR(49043, 4), 288}, // mad in opencl_std_100
    {IR(49047, 7), 289}, // maxmag in opencl_std_100
    {IR(49054, 7), 290}, // minmag in opencl_std_100
    {IR(49538, 4), 345}, // mix in opencl_std_100
    {IR(49061, 5), 291}, // modf in opencl_std_100
    {IR(49066, 4), 292}, // nan in opencl_std_100
    {IR(49330, 11), 327}, // native_cos in opencl_std_100
    {IR(49341, 14), 328}, // native_divide in opencl_std_100
    {IR(49355, 11), 329}, // native_exp in opencl_std_100
    {IR(49378, 13), 331}, // native_exp10 in opencl_std_100
    {IR(49366, 12), 330}, // native_exp2 in opencl_std_100
    {IR(49391, 11), 332}, // native_log in opencl_std_100
    {IR(49414, 13), 334}, // native_log10 in opencl_std_100
    {IR(49402, 12), 333}, // native_log2 in opencl_std_100
    {IR(49427, 12), 335}, // native_powr in opencl_std_100
    {IR(49439, 13), 336}, // native_recip in opencl_std_100
    {IR(49452, 13), 337}, // native_rsqrt in opencl_std_100
    {IR(49465, 11), 338}, // native_sin in opencl_std_100
    {IR(49476, 12), 339}, // native_sqrt in opencl_std_100
    {IR(49488, 11), 340}, // native_tan in opencl_std_100
    {IR(49070, 10), 293}, // nextafter in opencl_std_100
    {IR(49593, 10), 353}, // normalize in opencl_std_100
    {IR(49846, 9), 382}, // popcount in opencl_std_100
    {IR(49080, 4), 294}, // pow in opencl_std_100
    {IR(49084, 5), 295}, // pown in opencl_std_100
    {IR(49089, 5), 296}, // powr in opencl_std_100
    {IR(50046, 9), 401}, // prefetch in opencl_std_100
    {IR(50039, 7), 400}, // printf in opencl_std_100
    {IR(49542, 8), 346}, // radians in opencl_std_100
    {IR(49094, 10), 297}, // remainder in opencl_std_100
    {IR(49104, 7), 298}, // remquo in opencl_std_100
    {IR(49111, 5), 299}, // rint in opencl_std_100
    {IR(49116, 6), 300}, // rootn in opencl_std_100
    {IR(49797, 7), 377}, // rotate in opencl_std_100
    {IR(49122, 6), 301}, // round in opencl_std_100
    {IR(49128, 6), 302}, // rsqrt in opencl_std_100
    {IR(49644, 6), 357}, // s_abs in opencl_std_100
    {IR(49650, 11), 358}, // s_abs_diff in opencl_std_100
    {IR(49661, 10), 359}, // s_add_sat in opencl_std_100
    {IR(49711, 8), 365}, // s_clamp in opencl_std_100
    {IR(49681, 7), 361}, // s_hadd in opencl_std_100
    {IR(49855, 8), 383}, // s_mad24 in opencl_std_100
    {IR(49735, 9), 369}, // s_mad_hi in opencl_std_100
    {IR(49754, 10), 371}, // s_mad_sat in opencl_std_100
    {IR(49764, 6), 372}, // s_max in opencl_std_100
    {IR(49776, 6), 374}, // s_min in opencl_std_100
    {IR(49871, 8), 385}, // s_mul24 in opencl_std_100
    {IR(49788, 9), 376}, // s_mul_hi in opencl_std_100
    {IR(49695, 8), 363}, // s_rhadd in opencl_std_100
    {IR(49804, 10), 378}, // s_sub_sat in opencl_std_100
    {IR(49835, 11), 381}, // s_upsample in opencl_std_100
    {IR(50065, 7), 403}, // select in opencl_std_100
    {IR(50022, 8), 398}, // shuffle in opencl_std_100
    {IR(50030, 9), 399}, // shuffle2 in opencl_std_100
    {IR(49566, 5), 349}, // sign in opencl_std_100
    {IR(49134, 4), 303}, // sin in opencl_std_100
    {IR(49138, 7), 304}, // sincos in opencl_std_100
    {IR(49145, 5), 305}, // sinh in opencl_std_100
    {IR(49150, 6), 306}, // sinpi in opencl_std_100
    {IR(49555, 11), 348}, // smoothstep in opencl_std_100
    {IR(49156, 5), 307}, // sqrt in opencl_std_100
    {IR(49550, 5), 347}, // step in opencl_std_100
    {IR(49161, 4), 308}, // tan in opencl_std_100
    {IR(49165, 5), 309}, // tanh in opencl_std_100
    {IR(49170, 6), 310}, // tanpi in opencl_std_100
    {IR(49176, 7), 311}, // tgamma in opencl_std_100
    {IR(49183, 6), 312}, // trunc in opencl_std_100
    {IR(50072, 6), 404}, // u_abs in opencl_std_100
    {IR(50078, 11), 405}, // u_abs_diff in opencl_std_100
    {IR(49671, 10), 360}, // u_add_sat in opencl_std_100
    {IR(49719, 8), 366}, // u_clamp in opencl_std_100
    {IR(49688, 7), 362}, // u_hadd in opencl_std_100
    {IR(49863, 8), 384}, // u_mad24 in opencl_std_100
    {IR(50098, 9), 407}, // u_mad_hi in opencl_std_100
    {IR(49744, 10), 370}, // u_mad_sat in opencl_std_100
    {IR(49770, 6), 373}, // u_max in opencl_std_100
    {IR(49782, 6), 375}, // u_min in opencl_std_100
    {IR(49879, 8), 386}, // u_mul24 in opencl_std_100
    {IR(50089, 9), 406}, // u_mul_hi in opencl_std_100
    {IR(49703, 8), 364}, // u_rhadd in opencl_std_100
    {IR(49814, 10), 379}, // u_sub_sat in opencl_std_100
    {IR(49824, 11), 380}, // u_upsample in opencl_std_100
    {IR(49902, 11), 389}, // vload_half in opencl_std_100
    {IR(49913, 12), 390}, // vload_halfn in opencl_std_100
    {IR(49979, 13), 395}, // vloada_halfn in opencl_std_100
    {IR(49887, 7), 387}, // vloadn in opencl_std_100
    {IR(49925, 12), 391}, // vstore_half in opencl_std_100
    {IR(49937, 14), 392}, // vstore_half_r in opencl_std_100
    {IR(49951, 13), 393}, // vstore_halfn in opencl_std_100
    {IR(49964, 15), 394}, // vstore_halfn_r in opencl_std_100
    {IR(49992, 14), 396}, // vstorea_halfn in opencl_std_100
    {IR(50006, 16), 397}, // vstorea_halfn_r in opencl_std_100
    {IR(49894, 8), 388}, // vstoren in opencl_std_100
    {IR(50124, 17), 409}, // CubeFaceCoordAMD in spv_amd_gcn_shader
    {IR(50107, 17), 408}, // CubeFaceIndexAMD in spv_amd_gcn_shader
    {IR(50141, 8), 410}, // TimeAMD in spv_amd_gcn_shader
    {IR(50218, 9), 414}, // MbcntAMD in spv_amd_shader_ballot
    {IR(50149, 22), 411}, // SwizzleInvocationsAMD in spv_amd_shader_ballot
    {IR(50171, 28), 412}, // SwizzleInvocationsMaskedAMD in spv_amd_shader_ballot
    {IR(50199, 19), 413}, // WriteInvocationAMD in spv_amd_shader_ballot
    {IR(50227, 23), 415}, // InterpolateAtVertexAMD in spv_amd_shader_explicit_vertex_parameter
    {IR(50277, 9), 419}, // FMax3AMD in spv_amd_shader_trinary_minmax
    {IR(50304, 9), 422}, // FMid3AMD in spv_amd_shader_trinary_minmax
    {IR(50250, 9), 416}, // FMin3AMD in spv_amd_shader_trinary_minmax
    {IR(50295, 9), 421}, // SMax3AMD in spv_amd_shader_trinary_minmax
    {IR(50322, 9), 424}, // SMid3AMD in spv_amd_shader_trinary_minmax
    {IR(50268, 9), 418}, // SMin3AMD in spv_amd_shader_trinary_minmax
    {IR(50286, 9), 420}, // UMax3AMD in spv_amd_shader_trinary_minmax
    {IR(50313, 9), 423}, // UMid3AMD in spv_amd_shader_trinary_minmax
    {IR(50259, 9), 417}, // UMin3AMD in spv_amd_shader_trinary_minmax
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
  "SPV_ARM_graph\0" // IR(426, 14)
  "SPV_ARM_tensors\0" // IR(440, 16)
  "SPV_EXT_arithmetic_fence\0" // IR(456, 25)
  "SPV_EXT_demote_to_helper_invocation\0" // IR(481, 36)
  "SPV_EXT_descriptor_indexing\0" // IR(517, 28)
  "SPV_EXT_float8\0" // IR(545, 15)
  "SPV_EXT_fragment_fully_covered\0" // IR(560, 31)
  "SPV_EXT_fragment_invocation_density\0" // IR(591, 36)
  "SPV_EXT_fragment_shader_interlock\0" // IR(627, 34)
  "SPV_EXT_mesh_shader\0" // IR(661, 20)
  "SPV_EXT_opacity_micromap\0" // IR(681, 25)
  "SPV_EXT_optnone\0" // IR(706, 16)
  "SPV_EXT_physical_storage_buffer\0" // IR(722, 32)
  "SPV_EXT_relaxed_printf_string_address_space\0" // IR(754, 44)
  "SPV_EXT_replicated_composites\0" // IR(798, 30)
  "SPV_EXT_shader_atomic_float16_add\0" // IR(828, 34)
  "SPV_EXT_shader_atomic_float_add\0" // IR(862, 32)
  "SPV_EXT_shader_atomic_float_min_max\0" // IR(894, 36)
  "SPV_EXT_shader_image_int64\0" // IR(930, 27)
  "SPV_EXT_shader_stencil_export\0" // IR(957, 30)
  "SPV_EXT_shader_tile_image\0" // IR(987, 26)
  "SPV_EXT_shader_viewport_index_layer\0" // IR(1013, 36)
  "SPV_GOOGLE_decorate_string\0" // IR(1049, 27)
  "SPV_GOOGLE_hlsl_functionality1\0" // IR(1076, 31)
  "SPV_GOOGLE_user_type\0" // IR(1107, 21)
  "SPV_INTEL_2d_block_io\0" // IR(1128, 22)
  "SPV_INTEL_arbitrary_precision_fixed_point\0" // IR(1150, 42)
  "SPV_INTEL_arbitrary_precision_floating_point\0" // IR(1192, 45)
  "SPV_INTEL_arbitrary_precision_integers\0" // IR(1237, 39)
  "SPV_INTEL_bfloat16_conversion\0" // IR(1276, 30)
  "SPV_INTEL_bindless_images\0" // IR(1306, 26)
  "SPV_INTEL_blocking_pipes\0" // IR(1332, 25)
  "SPV_INTEL_cache_controls\0" // IR(1357, 25)
  "SPV_INTEL_debug_module\0" // IR(1382, 23)
  "SPV_INTEL_device_side_avc_motion_estimation\0" // IR(1405, 44)
  "SPV_INTEL_float_controls2\0" // IR(1449, 26)
  "SPV_INTEL_fp_fast_math_mode\0" // IR(1475, 28)
  "SPV_INTEL_fp_max_error\0" // IR(1503, 23)
  "SPV_INTEL_fpga_argument_interfaces\0" // IR(1526, 35)
  "SPV_INTEL_fpga_buffer_location\0" // IR(1561, 31)
  "SPV_INTEL_fpga_cluster_attributes\0" // IR(1592, 34)
  "SPV_INTEL_fpga_dsp_control\0" // IR(1626, 27)
  "SPV_INTEL_fpga_invocation_pipelining_attributes\0" // IR(1653, 48)
  "SPV_INTEL_fpga_latency_control\0" // IR(1701, 31)
  "SPV_INTEL_fpga_loop_controls\0" // IR(1732, 29)
  "SPV_INTEL_fpga_memory_accesses\0" // IR(1761, 31)
  "SPV_INTEL_fpga_memory_attributes\0" // IR(1792, 33)
  "SPV_INTEL_fpga_reg\0" // IR(1825, 19)
  "SPV_INTEL_function_pointers\0" // IR(1844, 28)
  "SPV_INTEL_function_variants\0" // IR(1872, 28)
  "SPV_INTEL_global_variable_fpga_decorations\0" // IR(1900, 43)
  "SPV_INTEL_global_variable_host_access\0" // IR(1943, 38)
  "SPV_INTEL_inline_assembly\0" // IR(1981, 26)
  "SPV_INTEL_int4\0" // IR(2007, 15)
  "SPV_INTEL_io_pipes\0" // IR(2022, 19)
  "SPV_INTEL_kernel_attributes\0" // IR(2041, 28)
  "SPV_INTEL_long_composites\0" // IR(2069, 26)
  "SPV_INTEL_loop_fuse\0" // IR(2095, 20)
  "SPV_INTEL_masked_gather_scatter\0" // IR(2115, 32)
  "SPV_INTEL_maximum_registers\0" // IR(2147, 28)
  "SPV_INTEL_media_block_io\0" // IR(2175, 25)
  "SPV_INTEL_memory_access_aliasing\0" // IR(2200, 33)
  "SPV_INTEL_optnone\0" // IR(2233, 18)
  "SPV_INTEL_runtime_aligned\0" // IR(2251, 26)
  "SPV_INTEL_shader_integer_functions2\0" // IR(2277, 36)
  "SPV_INTEL_split_barrier\0" // IR(2313, 24)
  "SPV_INTEL_subgroup_buffer_prefetch\0" // IR(2337, 35)
  "SPV_INTEL_subgroup_matrix_multiply_accumulate\0" // IR(2372, 46)
  "SPV_INTEL_subgroups\0" // IR(2418, 20)
  "SPV_INTEL_task_sequence\0" // IR(2438, 24)
  "SPV_INTEL_tensor_float32_conversion\0" // IR(2462, 36)
  "SPV_INTEL_ternary_bitwise_function\0" // IR(2498, 35)
  "SPV_INTEL_unstructured_loop_controls\0" // IR(2533, 37)
  "SPV_INTEL_usm_storage_classes\0" // IR(2570, 30)
  "SPV_INTEL_variable_length_array\0" // IR(2600, 32)
  "SPV_INTEL_vector_compute\0" // IR(2632, 25)
  "SPV_KHR_16bit_storage\0" // IR(2657, 22)
  "SPV_KHR_8bit_storage\0" // IR(2679, 21)
  "SPV_KHR_bfloat16\0" // IR(2700, 17)
  "SPV_KHR_bit_instructions\0" // IR(2717, 25)
  "SPV_KHR_compute_shader_derivatives\0" // IR(2742, 35)
  "SPV_KHR_cooperative_matrix\0" // IR(2777, 27)
  "SPV_KHR_device_group\0" // IR(2804, 21)
  "SPV_KHR_expect_assume\0" // IR(2825, 22)
  "SPV_KHR_float_controls\0" // IR(2847, 23)
  "SPV_KHR_float_controls2\0" // IR(2870, 24)
  "SPV_KHR_fragment_shader_barycentric\0" // IR(2894, 36)
  "SPV_KHR_fragment_shading_rate\0" // IR(2930, 30)
  "SPV_KHR_integer_dot_product\0" // IR(2960, 28)
  "SPV_KHR_linkonce_odr\0" // IR(2988, 21)
  "SPV_KHR_maximal_reconvergence\0" // IR(3009, 30)
  "SPV_KHR_multiview\0" // IR(3039, 18)
  "SPV_KHR_no_integer_wrap_decoration\0" // IR(3057, 35)
  "SPV_KHR_non_semantic_info\0" // IR(3092, 26)
  "SPV_KHR_physical_storage_buffer\0" // IR(3118, 32)
  "SPV_KHR_post_depth_coverage\0" // IR(3150, 28)
  "SPV_KHR_quad_control\0" // IR(3178, 21)
  "SPV_KHR_ray_cull_mask\0" // IR(3199, 22)
  "SPV_KHR_ray_query\0" // IR(3221, 18)
  "SPV_KHR_ray_tracing\0" // IR(3239, 20)
  "SPV_KHR_ray_tracing_position_fetch\0" // IR(3259, 35)
  "SPV_KHR_relaxed_extended_instruction\0" // IR(3294, 37)
  "SPV_KHR_shader_atomic_counter_ops\0" // IR(3331, 34)
  "SPV_KHR_shader_ballot\0" // IR(3365, 22)
  "SPV_KHR_shader_clock\0" // IR(3387, 21)
  "SPV_KHR_shader_draw_parameters\0" // IR(3408, 31)
  "SPV_KHR_storage_buffer_storage_class\0" // IR(3439, 37)
  "SPV_KHR_subgroup_rotate\0" // IR(3476, 24)
  "SPV_KHR_subgroup_uniform_control_flow\0" // IR(3500, 38)
  "SPV_KHR_subgroup_vote\0" // IR(3538, 22)
  "SPV_KHR_terminate_invocation\0" // IR(3560, 29)
  "SPV_KHR_uniform_group_instructions\0" // IR(3589, 35)
  "SPV_KHR_untyped_pointers\0" // IR(3624, 25)
  "SPV_KHR_variable_pointers\0" // IR(3649, 26)
  "SPV_KHR_vulkan_memory_model\0" // IR(3675, 28)
  "SPV_KHR_workgroup_memory_explicit_layout\0" // IR(3703, 41)
  "SPV_NVX_multiview_per_view_attributes\0" // IR(3744, 38)
  "SPV_NV_bindless_texture\0" // IR(3782, 24)
  "SPV_NV_cluster_acceleration_structure\0" // IR(3806, 38)
  "SPV_NV_compute_shader_derivatives\0" // IR(3844, 34)
  "SPV_NV_cooperative_matrix\0" // IR(3878, 26)
  "SPV_NV_cooperative_matrix2\0" // IR(3904, 27)
  "SPV_NV_cooperative_vector\0" // IR(3931, 26)
  "SPV_NV_displacement_micromap\0" // IR(3957, 29)
  "SPV_NV_fragment_shader_barycentric\0" // IR(3986, 35)
  "SPV_NV_geometry_shader_passthrough\0" // IR(4021, 35)
  "SPV_NV_linear_swept_spheres\0" // IR(4056, 28)
  "SPV_NV_mesh_shader\0" // IR(4084, 19)
  "SPV_NV_raw_access_chains\0" // IR(4103, 25)
  "SPV_NV_ray_tracing\0" // IR(4128, 19)
  "SPV_NV_ray_tracing_motion_blur\0" // IR(4147, 31)
  "SPV_NV_sample_mask_override_coverage\0" // IR(4178, 37)
  "SPV_NV_shader_atomic_fp16_vector\0" // IR(4215, 33)
  "SPV_NV_shader_image_footprint\0" // IR(4248, 30)
  "SPV_NV_shader_invocation_reorder\0" // IR(4278, 33)
  "SPV_NV_shader_sm_builtins\0" // IR(4311, 26)
  "SPV_NV_shader_subgroup_partitioned\0" // IR(4337, 35)
  "SPV_NV_shading_rate\0" // IR(4372, 20)
  "SPV_NV_stereo_view_rendering\0" // IR(4392, 29)
  "SPV_NV_tensor_addressing\0" // IR(4421, 25)
  "SPV_NV_viewport_array2\0" // IR(4446, 23)
  "SPV_QCOM_cooperative_matrix_conversion\0" // IR(4469, 39)
  "SPV_QCOM_image_processing\0" // IR(4508, 26)
  "SPV_QCOM_image_processing2\0" // IR(4534, 27)
  "SPV_QCOM_tile_shading\0" // IR(4561, 22)
  "SPV_VALIDATOR_ignore_type_decl_unique\0" // IR(4583, 38)
  "ReadOnly\0" // IR(4621, 9)
  "Kernel\0" // IR(4630, 7)
  "WriteOnly\0" // IR(4637, 10)
  "ReadWrite\0" // IR(4647, 10)
  "Logical\0" // IR(4657, 8)
  "Physical32\0" // IR(4665, 11)
  "Addresses\0" // IR(4676, 10)
  "Physical64\0" // IR(4686, 11)
  "PhysicalStorageBuffer64\0" // IR(4697, 24)
  "PhysicalStorageBuffer64EXT\0" // IR(4721, 27)
  "PhysicalStorageBufferAddresses\0" // IR(4748, 31)
  "Position\0" // IR(4779, 9)
  "Shader\0" // IR(4788, 7)
  "PointSize\0" // IR(4795, 10)
  "ClipDistance\0" // IR(4805, 13)
  "CullDistance\0" // IR(4818, 13)
  "VertexId\0" // IR(4831, 9)
  "InstanceId\0" // IR(4840, 11)
  "PrimitiveId\0" // IR(4851, 12)
  "Geometry\0" // IR(4863, 9)
  "Tessellation\0" // IR(4872, 13)
  "RayTracingNV\0" // IR(4885, 13)
  "RayTracingKHR\0" // IR(4898, 14)
  "MeshShadingNV\0" // IR(4912, 14)
  "MeshShadingEXT\0" // IR(4926, 15)
  "InvocationId\0" // IR(4941, 13)
  "Layer\0" // IR(4954, 6)
  "ShaderLayer\0" // IR(4960, 12)
  "ShaderViewportIndexLayerEXT\0" // IR(4972, 28)
  "ViewportIndex\0" // IR(5000, 14)
  "MultiViewport\0" // IR(5014, 14)
  "ShaderViewportIndex\0" // IR(5028, 20)
  "TessLevelOuter\0" // IR(5048, 15)
  "TessLevelInner\0" // IR(5063, 15)
  "TessCoord\0" // IR(5078, 10)
  "PatchVertices\0" // IR(5088, 14)
  "FragCoord\0" // IR(5102, 10)
  "PointCoord\0" // IR(5112, 11)
  "FrontFacing\0" // IR(5123, 12)
  "SampleId\0" // IR(5135, 9)
  "SampleRateShading\0" // IR(5144, 18)
  "SamplePosition\0" // IR(5162, 15)
  "SampleMask\0" // IR(5177, 11)
  "FragDepth\0" // IR(5188, 10)
  "HelperInvocation\0" // IR(5198, 17)
  "NumWorkgroups\0" // IR(5215, 14)
  "WorkgroupSize\0" // IR(5229, 14)
  "WorkgroupId\0" // IR(5243, 12)
  "LocalInvocationId\0" // IR(5255, 18)
  "GlobalInvocationId\0" // IR(5273, 19)
  "LocalInvocationIndex\0" // IR(5292, 21)
  "WorkDim\0" // IR(5313, 8)
  "GlobalSize\0" // IR(5321, 11)
  "EnqueuedWorkgroupSize\0" // IR(5332, 22)
  "GlobalOffset\0" // IR(5354, 13)
  "GlobalLinearId\0" // IR(5367, 15)
  "SubgroupSize\0" // IR(5382, 13)
  "GroupNonUniform\0" // IR(5395, 16)
  "SubgroupBallotKHR\0" // IR(5411, 18)
  "SubgroupMaxSize\0" // IR(5429, 16)
  "NumSubgroups\0" // IR(5445, 13)
  "NumEnqueuedSubgroups\0" // IR(5458, 21)
  "SubgroupId\0" // IR(5479, 11)
  "SubgroupLocalInvocationId\0" // IR(5490, 26)
  "VertexIndex\0" // IR(5516, 12)
  "InstanceIndex\0" // IR(5528, 14)
  "CoreIDARM\0" // IR(5542, 10)
  "CoreBuiltinsARM\0" // IR(5552, 16)
  "CoreCountARM\0" // IR(5568, 13)
  "CoreMaxIDARM\0" // IR(5581, 13)
  "WarpIDARM\0" // IR(5594, 10)
  "WarpMaxIDARM\0" // IR(5604, 13)
  "SubgroupEqMask\0" // IR(5617, 15)
  "SubgroupEqMaskKHR\0" // IR(5632, 18)
  "GroupNonUniformBallot\0" // IR(5650, 22)
  "SubgroupGeMask\0" // IR(5672, 15)
  "SubgroupGeMaskKHR\0" // IR(5687, 18)
  "SubgroupGtMask\0" // IR(5705, 15)
  "SubgroupGtMaskKHR\0" // IR(5720, 18)
  "SubgroupLeMask\0" // IR(5738, 15)
  "SubgroupLeMaskKHR\0" // IR(5753, 18)
  "SubgroupLtMask\0" // IR(5771, 15)
  "SubgroupLtMaskKHR\0" // IR(5786, 18)
  "BaseVertex\0" // IR(5804, 11)
  "DrawParameters\0" // IR(5815, 15)
  "BaseInstance\0" // IR(5830, 13)
  "DrawIndex\0" // IR(5843, 10)
  "PrimitiveShadingRateKHR\0" // IR(5853, 24)
  "FragmentShadingRateKHR\0" // IR(5877, 23)
  "DeviceIndex\0" // IR(5900, 12)
  "DeviceGroup\0" // IR(5912, 12)
  "ViewIndex\0" // IR(5924, 10)
  "MultiView\0" // IR(5934, 10)
  "ShadingRateKHR\0" // IR(5944, 15)
  "TileOffsetQCOM\0" // IR(5959, 15)
  "TileShadingQCOM\0" // IR(5974, 16)
  "TileDimensionQCOM\0" // IR(5990, 18)
  "TileApronSizeQCOM\0" // IR(6008, 18)
  "BaryCoordNoPerspAMD\0" // IR(6026, 20)
  "BaryCoordNoPerspCentroidAMD\0" // IR(6046, 28)
  "BaryCoordNoPerspSampleAMD\0" // IR(6074, 26)
  "BaryCoordSmoothAMD\0" // IR(6100, 19)
  "BaryCoordSmoothCentroidAMD\0" // IR(6119, 27)
  "BaryCoordSmoothSampleAMD\0" // IR(6146, 25)
  "BaryCoordPullModelAMD\0" // IR(6171, 22)
  "FragStencilRefEXT\0" // IR(6193, 18)
  "StencilExportEXT\0" // IR(6211, 17)
  "RemainingRecursionLevelsAMDX\0" // IR(6228, 29)
  "ShaderEnqueueAMDX\0" // IR(6257, 18)
  "ShaderIndexAMDX\0" // IR(6275, 16)
  "ViewportMaskNV\0" // IR(6291, 15)
  "ShaderViewportMaskNV\0" // IR(6306, 21)
  "SecondaryPositionNV\0" // IR(6327, 20)
  "ShaderStereoViewNV\0" // IR(6347, 19)
  "SecondaryViewportMaskNV\0" // IR(6366, 24)
  "PositionPerViewNV\0" // IR(6390, 18)
  "PerViewAttributesNV\0" // IR(6408, 20)
  "ViewportMaskPerViewNV\0" // IR(6428, 22)
  "FullyCoveredEXT\0" // IR(6450, 16)
  "FragmentFullyCoveredEXT\0" // IR(6466, 24)
  "TaskCountNV\0" // IR(6490, 12)
  "PrimitiveCountNV\0" // IR(6502, 17)
  "PrimitiveIndicesNV\0" // IR(6519, 19)
  "ClipDistancePerViewNV\0" // IR(6538, 22)
  "CullDistancePerViewNV\0" // IR(6560, 22)
  "LayerPerViewNV\0" // IR(6582, 15)
  "MeshViewCountNV\0" // IR(6597, 16)
  "MeshViewIndicesNV\0" // IR(6613, 18)
  "BaryCoordKHR\0" // IR(6631, 13)
  "BaryCoordNV\0" // IR(6644, 12)
  "FragmentBarycentricKHR\0" // IR(6656, 23)
  "BaryCoordNoPerspKHR\0" // IR(6679, 20)
  "BaryCoordNoPerspNV\0" // IR(6699, 19)
  "FragSizeEXT\0" // IR(6718, 12)
  "FragmentSizeNV\0" // IR(6730, 15)
  "FragmentDensityEXT\0" // IR(6745, 19)
  "FragInvocationCountEXT\0" // IR(6764, 23)
  "InvocationsPerPixelNV\0" // IR(6787, 22)
  "PrimitivePointIndicesEXT\0" // IR(6809, 25)
  "PrimitiveLineIndicesEXT\0" // IR(6834, 24)
  "PrimitiveTriangleIndicesEXT\0" // IR(6858, 28)
  "CullPrimitiveEXT\0" // IR(6886, 17)
  "LaunchIdKHR\0" // IR(6903, 12)
  "LaunchIdNV\0" // IR(6915, 11)
  "LaunchSizeKHR\0" // IR(6926, 14)
  "LaunchSizeNV\0" // IR(6940, 13)
  "WorldRayOriginKHR\0" // IR(6953, 18)
  "WorldRayOriginNV\0" // IR(6971, 17)
  "WorldRayDirectionKHR\0" // IR(6988, 21)
  "WorldRayDirectionNV\0" // IR(7009, 20)
  "ObjectRayOriginKHR\0" // IR(7029, 19)
  "ObjectRayOriginNV\0" // IR(7048, 18)
  "ObjectRayDirectionKHR\0" // IR(7066, 22)
  "ObjectRayDirectionNV\0" // IR(7088, 21)
  "RayTminKHR\0" // IR(7109, 11)
  "RayTminNV\0" // IR(7120, 10)
  "RayTmaxKHR\0" // IR(7130, 11)
  "RayTmaxNV\0" // IR(7141, 10)
  "InstanceCustomIndexKHR\0" // IR(7151, 23)
  "InstanceCustomIndexNV\0" // IR(7174, 22)
  "ObjectToWorldKHR\0" // IR(7196, 17)
  "ObjectToWorldNV\0" // IR(7213, 16)
  "WorldToObjectKHR\0" // IR(7229, 17)
  "WorldToObjectNV\0" // IR(7246, 16)
  "HitTNV\0" // IR(7262, 7)
  "HitKindKHR\0" // IR(7269, 11)
  "HitKindNV\0" // IR(7280, 10)
  "CurrentRayTimeNV\0" // IR(7290, 17)
  "RayTracingMotionBlurNV\0" // IR(7307, 23)
  "HitTriangleVertexPositionsKHR\0" // IR(7330, 30)
  "RayTracingPositionFetchKHR\0" // IR(7360, 27)
  "HitMicroTriangleVertexPositionsNV\0" // IR(7387, 34)
  "RayTracingDisplacementMicromapNV\0" // IR(7421, 33)
  "HitMicroTriangleVertexBarycentricsNV\0" // IR(7454, 37)
  "IncomingRayFlagsKHR\0" // IR(7491, 20)
  "IncomingRayFlagsNV\0" // IR(7511, 19)
  "RayGeometryIndexKHR\0" // IR(7530, 20)
  "HitIsSphereNV\0" // IR(7550, 14)
  "RayTracingSpheresGeometryNV\0" // IR(7564, 28)
  "HitIsLSSNV\0" // IR(7592, 11)
  "RayTracingLinearSweptSpheresGeometryNV\0" // IR(7603, 39)
  "HitSpherePositionNV\0" // IR(7642, 20)
  "WarpsPerSMNV\0" // IR(7662, 13)
  "ShaderSMBuiltinsNV\0" // IR(7675, 19)
  "SMCountNV\0" // IR(7694, 10)
  "WarpIDNV\0" // IR(7704, 9)
  "SMIDNV\0" // IR(7713, 7)
  "HitLSSPositionsNV\0" // IR(7720, 18)
  "HitKindFrontFacingMicroTriangleNV\0" // IR(7738, 34)
  "HitKindBackFacingMicroTriangleNV\0" // IR(7772, 33)
  "HitSphereRadiusNV\0" // IR(7805, 18)
  "HitLSSRadiiNV\0" // IR(7823, 14)
  "ClusterIDNV\0" // IR(7837, 12)
  "RayTracingClusterAccelerationStructureNV\0" // IR(7849, 41)
  "CullMaskKHR\0" // IR(7890, 12)
  "RayCullMaskKHR\0" // IR(7902, 15)
  "Matrix\0" // IR(7917, 7)
  "Linkage\0" // IR(7924, 8)
  "Vector16\0" // IR(7932, 9)
  "Float16Buffer\0" // IR(7941, 14)
  "Float16\0" // IR(7955, 8)
  "Float64\0" // IR(7963, 8)
  "Int64\0" // IR(7971, 6)
  "Int64Atomics\0" // IR(7977, 13)
  "ImageBasic\0" // IR(7990, 11)
  "ImageReadWrite\0" // IR(8001, 15)
  "ImageMipmap\0" // IR(8016, 12)
  "Pipes\0" // IR(8028, 6)
  "Groups\0" // IR(8034, 7)
  "DeviceEnqueue\0" // IR(8041, 14)
  "LiteralSampler\0" // IR(8055, 15)
  "AtomicStorage\0" // IR(8070, 14)
  "Int16\0" // IR(8084, 6)
  "TessellationPointSize\0" // IR(8090, 22)
  "GeometryPointSize\0" // IR(8112, 18)
  "ImageGatherExtended\0" // IR(8130, 20)
  "StorageImageMultisample\0" // IR(8150, 24)
  "UniformBufferArrayDynamicIndexing\0" // IR(8174, 34)
  "SampledImageArrayDynamicIndexing\0" // IR(8208, 33)
  "StorageBufferArrayDynamicIndexing\0" // IR(8241, 34)
  "StorageImageArrayDynamicIndexing\0" // IR(8275, 33)
  "ImageCubeArray\0" // IR(8308, 15)
  "SampledCubeArray\0" // IR(8323, 17)
  "ImageRect\0" // IR(8340, 10)
  "SampledRect\0" // IR(8350, 12)
  "GenericPointer\0" // IR(8362, 15)
  "Int8\0" // IR(8377, 5)
  "InputAttachment\0" // IR(8382, 16)
  "SparseResidency\0" // IR(8398, 16)
  "MinLod\0" // IR(8414, 7)
  "Sampled1D\0" // IR(8421, 10)
  "Image1D\0" // IR(8431, 8)
  "SampledBuffer\0" // IR(8439, 14)
  "ImageBuffer\0" // IR(8453, 12)
  "ImageMSArray\0" // IR(8465, 13)
  "StorageImageExtendedFormats\0" // IR(8478, 28)
  "ImageQuery\0" // IR(8506, 11)
  "DerivativeControl\0" // IR(8517, 18)
  "InterpolationFunction\0" // IR(8535, 22)
  "TransformFeedback\0" // IR(8557, 18)
  "GeometryStreams\0" // IR(8575, 16)
  "StorageImageReadWithoutFormat\0" // IR(8591, 30)
  "StorageImageWriteWithoutFormat\0" // IR(8621, 31)
  "SubgroupDispatch\0" // IR(8652, 17)
  "NamedBarrier\0" // IR(8669, 13)
  "PipeStorage\0" // IR(8682, 12)
  "GroupNonUniformVote\0" // IR(8694, 20)
  "GroupNonUniformArithmetic\0" // IR(8714, 26)
  "GroupNonUniformShuffle\0" // IR(8740, 23)
  "GroupNonUniformShuffleRelative\0" // IR(8763, 31)
  "GroupNonUniformClustered\0" // IR(8794, 25)
  "GroupNonUniformQuad\0" // IR(8819, 20)
  "UniformDecoration\0" // IR(8839, 18)
  "TileImageColorReadAccessEXT\0" // IR(8857, 28)
  "TileImageDepthReadAccessEXT\0" // IR(8885, 28)
  "TileImageStencilReadAccessEXT\0" // IR(8913, 30)
  "TensorsARM\0" // IR(8943, 11)
  "StorageTensorArrayDynamicIndexingARM\0" // IR(8954, 37)
  "StorageTensorArrayNonUniformIndexingARM\0" // IR(8991, 40)
  "GraphARM\0" // IR(9031, 9)
  "CooperativeMatrixLayoutsARM\0" // IR(9040, 28)
  "Float8EXT\0" // IR(9068, 10)
  "Float8CooperativeMatrixEXT\0" // IR(9078, 27)
  "CooperativeMatrixKHR\0" // IR(9105, 21)
  "WorkgroupMemoryExplicitLayoutKHR\0" // IR(9126, 33)
  "WorkgroupMemoryExplicitLayout8BitAccessKHR\0" // IR(9159, 43)
  "WorkgroupMemoryExplicitLayout16BitAccessKHR\0" // IR(9202, 44)
  "SubgroupVoteKHR\0" // IR(9246, 16)
  "StorageBuffer16BitAccess\0" // IR(9262, 25)
  "StorageUniformBufferBlock16\0" // IR(9287, 28)
  "UniformAndStorageBuffer16BitAccess\0" // IR(9315, 35)
  "StorageUniform16\0" // IR(9350, 17)
  "StoragePushConstant16\0" // IR(9367, 22)
  "StorageInputOutput16\0" // IR(9389, 21)
  "VariablePointersStorageBuffer\0" // IR(9410, 30)
  "VariablePointers\0" // IR(9440, 17)
  "AtomicStorageOps\0" // IR(9457, 17)
  "SampleMaskPostDepthCoverage\0" // IR(9474, 28)
  "StorageBuffer8BitAccess\0" // IR(9502, 24)
  "UniformAndStorageBuffer8BitAccess\0" // IR(9526, 34)
  "StoragePushConstant8\0" // IR(9560, 21)
  "DenormPreserve\0" // IR(9581, 15)
  "DenormFlushToZero\0" // IR(9596, 18)
  "SignedZeroInfNanPreserve\0" // IR(9614, 25)
  "RoundingModeRTE\0" // IR(9639, 16)
  "RoundingModeRTZ\0" // IR(9655, 16)
  "RayQueryProvisionalKHR\0" // IR(9671, 23)
  "RayQueryKHR\0" // IR(9694, 12)
  "UntypedPointersKHR\0" // IR(9706, 19)
  "RayTraversalPrimitiveCullingKHR\0" // IR(9725, 32)
  "TextureSampleWeightedQCOM\0" // IR(9757, 26)
  "TextureBoxFilterQCOM\0" // IR(9783, 21)
  "TextureBlockMatchQCOM\0" // IR(9804, 22)
  "CooperativeMatrixConversionQCOM\0" // IR(9826, 32)
  "TextureBlockMatch2QCOM\0" // IR(9858, 23)
  "Float16ImageAMD\0" // IR(9881, 16)
  "ImageGatherBiasLodAMD\0" // IR(9897, 22)
  "FragmentMaskAMD\0" // IR(9919, 16)
  "ImageReadWriteLodAMD\0" // IR(9935, 21)
  "Int64ImageEXT\0" // IR(9956, 14)
  "ShaderClockKHR\0" // IR(9970, 15)
  "QuadControlKHR\0" // IR(9985, 15)
  "Int4TypeINTEL\0" // IR(10000, 14)
  "Int4CooperativeMatrixINTEL\0" // IR(10014, 27)
  "BFloat16TypeKHR\0" // IR(10041, 16)
  "BFloat16DotProductKHR\0" // IR(10057, 22)
  "BFloat16CooperativeMatrixKHR\0" // IR(10079, 29)
  "SampleMaskOverrideCoverageNV\0" // IR(10108, 29)
  "GeometryShaderPassthroughNV\0" // IR(10137, 28)
  "ShaderViewportIndexLayerNV\0" // IR(10165, 27)
  "ImageFootprintNV\0" // IR(10192, 17)
  "FragmentBarycentricNV\0" // IR(10209, 22)
  "ComputeDerivativeGroupQuadsKHR\0" // IR(10231, 31)
  "ComputeDerivativeGroupQuadsNV\0" // IR(10262, 30)
  "ShadingRateNV\0" // IR(10292, 14)
  "GroupNonUniformPartitionedNV\0" // IR(10306, 29)
  "ShaderNonUniform\0" // IR(10335, 17)
  "ShaderNonUniformEXT\0" // IR(10352, 20)
  "RuntimeDescriptorArray\0" // IR(10372, 23)
  "RuntimeDescriptorArrayEXT\0" // IR(10395, 26)
  "InputAttachmentArrayDynamicIndexing\0" // IR(10421, 36)
  "InputAttachmentArrayDynamicIndexingEXT\0" // IR(10457, 39)
  "UniformTexelBufferArrayDynamicIndexing\0" // IR(10496, 39)
  "UniformTexelBufferArrayDynamicIndexingEXT\0" // IR(10535, 42)
  "StorageTexelBufferArrayDynamicIndexing\0" // IR(10577, 39)
  "StorageTexelBufferArrayDynamicIndexingEXT\0" // IR(10616, 42)
  "UniformBufferArrayNonUniformIndexing\0" // IR(10658, 37)
  "UniformBufferArrayNonUniformIndexingEXT\0" // IR(10695, 40)
  "SampledImageArrayNonUniformIndexing\0" // IR(10735, 36)
  "SampledImageArrayNonUniformIndexingEXT\0" // IR(10771, 39)
  "StorageBufferArrayNonUniformIndexing\0" // IR(10810, 37)
  "StorageBufferArrayNonUniformIndexingEXT\0" // IR(10847, 40)
  "StorageImageArrayNonUniformIndexing\0" // IR(10887, 36)
  "StorageImageArrayNonUniformIndexingEXT\0" // IR(10923, 39)
  "InputAttachmentArrayNonUniformIndexing\0" // IR(10962, 39)
  "InputAttachmentArrayNonUniformIndexingEXT\0" // IR(11001, 42)
  "UniformTexelBufferArrayNonUniformIndexing\0" // IR(11043, 42)
  "UniformTexelBufferArrayNonUniformIndexingEXT\0" // IR(11085, 45)
  "StorageTexelBufferArrayNonUniformIndexing\0" // IR(11130, 42)
  "StorageTexelBufferArrayNonUniformIndexingEXT\0" // IR(11172, 45)
  "VulkanMemoryModel\0" // IR(11217, 18)
  "VulkanMemoryModelKHR\0" // IR(11235, 21)
  "VulkanMemoryModelDeviceScope\0" // IR(11256, 29)
  "VulkanMemoryModelDeviceScopeKHR\0" // IR(11285, 32)
  "PhysicalStorageBufferAddressesEXT\0" // IR(11317, 34)
  "ComputeDerivativeGroupLinearKHR\0" // IR(11351, 32)
  "ComputeDerivativeGroupLinearNV\0" // IR(11383, 31)
  "RayTracingProvisionalKHR\0" // IR(11414, 25)
  "CooperativeMatrixNV\0" // IR(11439, 20)
  "FragmentShaderSampleInterlockEXT\0" // IR(11459, 33)
  "FragmentShaderShadingRateInterlockEXT\0" // IR(11492, 38)
  "FragmentShaderPixelInterlockEXT\0" // IR(11530, 32)
  "DemoteToHelperInvocation\0" // IR(11562, 25)
  "DemoteToHelperInvocationEXT\0" // IR(11587, 28)
  "DisplacementMicromapNV\0" // IR(11615, 23)
  "RayTracingOpacityMicromapEXT\0" // IR(11638, 29)
  "ShaderInvocationReorderNV\0" // IR(11667, 26)
  "BindlessTextureNV\0" // IR(11693, 18)
  "RayQueryPositionFetchKHR\0" // IR(11711, 25)
  "CooperativeVectorNV\0" // IR(11736, 20)
  "AtomicFloat16VectorNV\0" // IR(11756, 22)
  "RawAccessChainsNV\0" // IR(11778, 18)
  "CooperativeMatrixReductionsNV\0" // IR(11796, 30)
  "CooperativeMatrixConversionsNV\0" // IR(11826, 31)
  "CooperativeMatrixPerElementOperationsNV\0" // IR(11857, 40)
  "CooperativeMatrixTensorAddressingNV\0" // IR(11897, 36)
  "CooperativeMatrixBlockLoadsNV\0" // IR(11933, 30)
  "CooperativeVectorTrainingNV\0" // IR(11963, 28)
  "TensorAddressingNV\0" // IR(11991, 19)
  "SubgroupShuffleINTEL\0" // IR(12010, 21)
  "SubgroupBufferBlockIOINTEL\0" // IR(12031, 27)
  "SubgroupImageBlockIOINTEL\0" // IR(12058, 26)
  "SubgroupImageMediaBlockIOINTEL\0" // IR(12084, 31)
  "RoundToInfinityINTEL\0" // IR(12115, 21)
  "FloatingPointModeINTEL\0" // IR(12136, 23)
  "IntegerFunctions2INTEL\0" // IR(12159, 23)
  "FunctionPointersINTEL\0" // IR(12182, 22)
  "IndirectReferencesINTEL\0" // IR(12204, 24)
  "AsmINTEL\0" // IR(12228, 9)
  "AtomicFloat32MinMaxEXT\0" // IR(12237, 23)
  "AtomicFloat64MinMaxEXT\0" // IR(12260, 23)
  "AtomicFloat16MinMaxEXT\0" // IR(12283, 23)
  "VectorComputeINTEL\0" // IR(12306, 19)
  "VectorAnyINTEL\0" // IR(12325, 15)
  "ExpectAssumeKHR\0" // IR(12340, 16)
  "SubgroupAvcMotionEstimationINTEL\0" // IR(12356, 33)
  "SubgroupAvcMotionEstimationIntraINTEL\0" // IR(12389, 38)
  "SubgroupAvcMotionEstimationChromaINTEL\0" // IR(12427, 39)
  "VariableLengthArrayINTEL\0" // IR(12466, 25)
  "FunctionFloatControlINTEL\0" // IR(12491, 26)
  "FPGAMemoryAttributesINTEL\0" // IR(12517, 26)
  "FPFastMathModeINTEL\0" // IR(12543, 20)
  "ArbitraryPrecisionIntegersINTEL\0" // IR(12563, 32)
  "ArbitraryPrecisionFloatingPointINTEL\0" // IR(12595, 37)
  "UnstructuredLoopControlsINTEL\0" // IR(12632, 30)
  "FPGALoopControlsINTEL\0" // IR(12662, 22)
  "KernelAttributesINTEL\0" // IR(12684, 22)
  "FPGAKernelAttributesINTEL\0" // IR(12706, 26)
  "FPGAMemoryAccessesINTEL\0" // IR(12732, 24)
  "FPGAClusterAttributesINTEL\0" // IR(12756, 27)
  "LoopFuseINTEL\0" // IR(12783, 14)
  "FPGADSPControlINTEL\0" // IR(12797, 20)
  "MemoryAccessAliasingINTEL\0" // IR(12817, 26)
  "FPGAInvocationPipeliningAttributesINTEL\0" // IR(12843, 40)
  "FPGABufferLocationINTEL\0" // IR(12883, 24)
  "ArbitraryPrecisionFixedPointINTEL\0" // IR(12907, 34)
  "USMStorageClassesINTEL\0" // IR(12941, 23)
  "RuntimeAlignedAttributeINTEL\0" // IR(12964, 29)
  "IOPipesINTEL\0" // IR(12993, 13)
  "BlockingPipesINTEL\0" // IR(13006, 19)
  "FPGARegINTEL\0" // IR(13025, 13)
  "DotProductInputAll\0" // IR(13038, 19)
  "DotProductInputAllKHR\0" // IR(13057, 22)
  "DotProductInput4x8Bit\0" // IR(13079, 22)
  "DotProductInput4x8BitKHR\0" // IR(13101, 25)
  "DotProductInput4x8BitPacked\0" // IR(13126, 28)
  "DotProductInput4x8BitPackedKHR\0" // IR(13154, 31)
  "DotProduct\0" // IR(13185, 11)
  "DotProductKHR\0" // IR(13196, 14)
  "ReplicatedCompositesEXT\0" // IR(13210, 24)
  "BitInstructions\0" // IR(13234, 16)
  "GroupNonUniformRotateKHR\0" // IR(13250, 25)
  "FloatControls2\0" // IR(13275, 15)
  "AtomicFloat32AddEXT\0" // IR(13290, 20)
  "AtomicFloat64AddEXT\0" // IR(13310, 20)
  "LongCompositesINTEL\0" // IR(13330, 20)
  "OptNoneEXT\0" // IR(13350, 11)
  "OptNoneINTEL\0" // IR(13361, 13)
  "AtomicFloat16AddEXT\0" // IR(13374, 20)
  "DebugInfoModuleINTEL\0" // IR(13394, 21)
  "BFloat16ConversionINTEL\0" // IR(13415, 24)
  "SplitBarrierINTEL\0" // IR(13439, 18)
  "ArithmeticFenceEXT\0" // IR(13457, 19)
  "FPGAClusterAttributesV2INTEL\0" // IR(13476, 29)
  "FPGAKernelAttributesv2INTEL\0" // IR(13505, 28)
  "TaskSequenceINTEL\0" // IR(13533, 18)
  "FPMaxErrorINTEL\0" // IR(13551, 16)
  "FPGALatencyControlINTEL\0" // IR(13567, 24)
  "FPGAArgumentInterfacesINTEL\0" // IR(13591, 28)
  "GlobalVariableHostAccessINTEL\0" // IR(13619, 30)
  "GlobalVariableFPGADecorationsINTEL\0" // IR(13649, 35)
  "SubgroupBufferPrefetchINTEL\0" // IR(13684, 28)
  "Subgroup2DBlockIOINTEL\0" // IR(13712, 23)
  "Subgroup2DBlockTransformINTEL\0" // IR(13735, 30)
  "Subgroup2DBlockTransposeINTEL\0" // IR(13765, 30)
  "SubgroupMatrixMultiplyAccumulateINTEL\0" // IR(13795, 38)
  "TernaryBitwiseFunctionINTEL\0" // IR(13833, 28)
  "UntypedVariableLengthArrayINTEL\0" // IR(13861, 32)
  "SpecConditionalINTEL\0" // IR(13893, 21)
  "FunctionVariantsINTEL\0" // IR(13914, 22)
  "GroupUniformArithmeticKHR\0" // IR(13936, 26)
  "TensorFloat32RoundingINTEL\0" // IR(13962, 27)
  "MaskedGatherScatterINTEL\0" // IR(13989, 25)
  "CacheControlsINTEL\0" // IR(14014, 19)
  "RegisterLimitsINTEL\0" // IR(14033, 20)
  "BindlessImagesINTEL\0" // IR(14053, 20)
  "Unspecified\0" // IR(14073, 12)
  "Address\0" // IR(14085, 8)
  "Boolean\0" // IR(14093, 8)
  "Float\0" // IR(14101, 6)
  "Signed\0" // IR(14107, 7)
  "SignedChar\0" // IR(14114, 11)
  "Unsigned\0" // IR(14125, 9)
  "UnsignedChar\0" // IR(14134, 13)
  "Class\0" // IR(14147, 6)
  "Structure\0" // IR(14153, 10)
  "Union\0" // IR(14163, 6)
  "ImportedModule\0" // IR(14169, 15)
  "ImportedDeclaration\0" // IR(14184, 20)
  "None\0" // IR(14204, 5)
  "FlagIsProtected\0" // IR(14209, 16)
  "FlagIsPrivate\0" // IR(14225, 14)
  "FlagIsPublic\0" // IR(14239, 13)
  "FlagIsLocal\0" // IR(14252, 12)
  "FlagIsDefinition\0" // IR(14264, 17)
  "FlagFwdDecl\0" // IR(14281, 12)
  "FlagArtificial\0" // IR(14293, 15)
  "FlagExplicit\0" // IR(14308, 13)
  "FlagPrototyped\0" // IR(14321, 15)
  "FlagObjectPointer\0" // IR(14336, 18)
  "FlagStaticMember\0" // IR(14354, 17)
  "FlagIndirectVariable\0" // IR(14371, 21)
  "FlagLValueReference\0" // IR(14392, 20)
  "FlagRValueReference\0" // IR(14412, 20)
  "FlagIsOptimized\0" // IR(14432, 16)
  "FlagIsEnumClass\0" // IR(14448, 16)
  "FlagTypePassByValue\0" // IR(14464, 20)
  "FlagTypePassByReference\0" // IR(14484, 24)
  "Deref\0" // IR(14508, 6)
  "Plus\0" // IR(14514, 5)
  "Minus\0" // IR(14519, 6)
  "SPV_OPERAND_TYPE_LITERAL_INTEGER\0" // IR(14525, 33)
  "PlusUconst\0" // IR(14558, 11)
  "BitPiece\0" // IR(14569, 9)
  "Swap\0" // IR(14578, 5)
  "Xderef\0" // IR(14583, 7)
  "StackValue\0" // IR(14590, 11)
  "Constu\0" // IR(14601, 7)
  "Fragment\0" // IR(14608, 9)
  "ConstType\0" // IR(14617, 10)
  "VolatileType\0" // IR(14627, 13)
  "RestrictType\0" // IR(14640, 13)
  "AtomicType\0" // IR(14653, 11)
  "Float16NV\0" // IR(14664, 10)
  "Float32NV\0" // IR(14674, 10)
  "Float64NV\0" // IR(14684, 10)
  "SignedInt8NV\0" // IR(14694, 13)
  "SignedInt16NV\0" // IR(14707, 14)
  "SignedInt32NV\0" // IR(14721, 14)
  "SignedInt64NV\0" // IR(14735, 14)
  "UnsignedInt8NV\0" // IR(14749, 15)
  "UnsignedInt16NV\0" // IR(14764, 16)
  "UnsignedInt32NV\0" // IR(14780, 16)
  "UnsignedInt64NV\0" // IR(14796, 16)
  "SignedInt8PackedNV\0" // IR(14812, 19)
  "UnsignedInt8PackedNV\0" // IR(14831, 21)
  "FloatE4M3NV\0" // IR(14852, 12)
  "FloatE5M2NV\0" // IR(14864, 12)
  "RowMajorKHR\0" // IR(14876, 12)
  "ColumnMajorKHR\0" // IR(14888, 15)
  "RowBlockedInterleavedARM\0" // IR(14903, 25)
  "ColumnBlockedInterleavedARM\0" // IR(14928, 28)
  "NoneKHR\0" // IR(14956, 8)
  "MatrixASignedComponentsKHR\0" // IR(14964, 27)
  "MatrixBSignedComponentsKHR\0" // IR(14991, 27)
  "MatrixCSignedComponentsKHR\0" // IR(15018, 27)
  "MatrixResultSignedComponentsKHR\0" // IR(15045, 32)
  "SaturatingAccumulationKHR\0" // IR(15077, 26)
  "Row\0" // IR(15103, 4)
  "Column\0" // IR(15107, 7)
  "2x2\0" // IR(15114, 4)
  "MatrixAKHR\0" // IR(15118, 11)
  "MatrixBKHR\0" // IR(15129, 11)
  "MatrixAccumulatorKHR\0" // IR(15140, 21)
  "RowMajorNV\0" // IR(15161, 11)
  "ColumnMajorNV\0" // IR(15172, 14)
  "InferencingOptimalNV\0" // IR(15186, 21)
  "TrainingOptimalNV\0" // IR(15207, 18)
  "RelaxedPrecision\0" // IR(15225, 17)
  "SpecId\0" // IR(15242, 7)
  "Block\0" // IR(15249, 6)
  "BufferBlock\0" // IR(15255, 12)
  "RowMajor\0" // IR(15267, 9)
  "ColMajor\0" // IR(15276, 9)
  "ArrayStride\0" // IR(15285, 12)
  "MatrixStride\0" // IR(15297, 13)
  "GLSLShared\0" // IR(15310, 11)
  "GLSLPacked\0" // IR(15321, 11)
  "CPacked\0" // IR(15332, 8)
  "SPV_OPERAND_TYPE_BUILT_IN\0" // IR(15340, 26)
  "BuiltIn\0" // IR(15366, 8)
  "NoPerspective\0" // IR(15374, 14)
  "Flat\0" // IR(15388, 5)
  "Patch\0" // IR(15393, 6)
  "Centroid\0" // IR(15399, 9)
  "Sample\0" // IR(15408, 7)
  "Invariant\0" // IR(15415, 10)
  "Restrict\0" // IR(15425, 9)
  "Aliased\0" // IR(15434, 8)
  "Volatile\0" // IR(15442, 9)
  "Constant\0" // IR(15451, 9)
  "Coherent\0" // IR(15460, 9)
  "NonWritable\0" // IR(15469, 12)
  "NonReadable\0" // IR(15481, 12)
  "Uniform\0" // IR(15493, 8)
  "SPV_OPERAND_TYPE_SCOPE_ID\0" // IR(15501, 26)
  "UniformId\0" // IR(15527, 10)
  "SaturatedConversion\0" // IR(15537, 20)
  "Stream\0" // IR(15557, 7)
  "Location\0" // IR(15564, 9)
  "Component\0" // IR(15573, 10)
  "Index\0" // IR(15583, 6)
  "Binding\0" // IR(15589, 8)
  "DescriptorSet\0" // IR(15597, 14)
  "Offset\0" // IR(15611, 7)
  "XfbBuffer\0" // IR(15618, 10)
  "XfbStride\0" // IR(15628, 10)
  "SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE\0" // IR(15638, 46)
  "FuncParamAttr\0" // IR(15684, 14)
  "SPV_OPERAND_TYPE_FP_ROUNDING_MODE\0" // IR(15698, 34)
  "FPRoundingMode\0" // IR(15732, 15)
  "SPV_OPERAND_TYPE_FP_FAST_MATH_MODE\0" // IR(15747, 35)
  "FPFastMathMode\0" // IR(15782, 15)
  "SPV_OPERAND_TYPE_LITERAL_STRING\0" // IR(15797, 32)
  "SPV_OPERAND_TYPE_LINKAGE_TYPE\0" // IR(15829, 30)
  "LinkageAttributes\0" // IR(15859, 18)
  "NoContraction\0" // IR(15877, 14)
  "InputAttachmentIndex\0" // IR(15891, 21)
  "Alignment\0" // IR(15912, 10)
  "MaxByteOffset\0" // IR(15922, 14)
  "SPV_OPERAND_TYPE_ID\0" // IR(15936, 20)
  "AlignmentId\0" // IR(15956, 12)
  "MaxByteOffsetId\0" // IR(15968, 16)
  "SaturatedToLargestFloat8NormalConversionEXT\0" // IR(15984, 44)
  "NoSignedWrap\0" // IR(16028, 13)
  "NoUnsignedWrap\0" // IR(16041, 15)
  "WeightTextureQCOM\0" // IR(16056, 18)
  "BlockMatchTextureQCOM\0" // IR(16074, 22)
  "BlockMatchSamplerQCOM\0" // IR(16096, 22)
  "ExplicitInterpAMD\0" // IR(16118, 18)
  "NodeSharesPayloadLimitsWithAMDX\0" // IR(16136, 32)
  "NodeMaxPayloadsAMDX\0" // IR(16168, 20)
  "TrackFinishWritingAMDX\0" // IR(16188, 23)
  "PayloadNodeNameAMDX\0" // IR(16211, 20)
  "PayloadNodeBaseIndexAMDX\0" // IR(16231, 25)
  "PayloadNodeSparseArrayAMDX\0" // IR(16256, 27)
  "PayloadNodeArraySizeAMDX\0" // IR(16283, 25)
  "PayloadDispatchIndirectAMDX\0" // IR(16308, 28)
  "OverrideCoverageNV\0" // IR(16336, 19)
  "PassthroughNV\0" // IR(16355, 14)
  "ViewportRelativeNV\0" // IR(16369, 19)
  "SecondaryViewportRelativeNV\0" // IR(16388, 28)
  "PerPrimitiveEXT\0" // IR(16416, 16)
  "PerPrimitiveNV\0" // IR(16432, 15)
  "PerViewNV\0" // IR(16447, 10)
  "PerTaskNV\0" // IR(16457, 10)
  "PerVertexKHR\0" // IR(16467, 13)
  "PerVertexNV\0" // IR(16480, 12)
  "NonUniform\0" // IR(16492, 11)
  "NonUniformEXT\0" // IR(16503, 14)
  "RestrictPointer\0" // IR(16517, 16)
  "RestrictPointerEXT\0" // IR(16533, 19)
  "AliasedPointer\0" // IR(16552, 15)
  "AliasedPointerEXT\0" // IR(16567, 18)
  "HitObjectShaderRecordBufferNV\0" // IR(16585, 30)
  "BindlessSamplerNV\0" // IR(16615, 18)
  "BindlessImageNV\0" // IR(16633, 16)
  "BoundSamplerNV\0" // IR(16649, 15)
  "BoundImageNV\0" // IR(16664, 13)
  "SIMTCallINTEL\0" // IR(16677, 14)
  "ReferencedIndirectlyINTEL\0" // IR(16691, 26)
  "ClobberINTEL\0" // IR(16717, 13)
  "SideEffectsINTEL\0" // IR(16730, 17)
  "VectorComputeVariableINTEL\0" // IR(16747, 27)
  "FuncParamIOKindINTEL\0" // IR(16774, 21)
  "VectorComputeFunctionINTEL\0" // IR(16795, 27)
  "StackCallINTEL\0" // IR(16822, 15)
  "GlobalVariableOffsetINTEL\0" // IR(16837, 26)
  "CounterBuffer\0" // IR(16863, 14)
  "HlslCounterBufferGOOGLE\0" // IR(16877, 24)
  "UserSemantic\0" // IR(16901, 13)
  "HlslSemanticGOOGLE\0" // IR(16914, 19)
  "UserTypeGOOGLE\0" // IR(16933, 15)
  "FunctionRoundingModeINTEL\0" // IR(16948, 26)
  "SPV_OPERAND_TYPE_FPDENORM_MODE\0" // IR(16974, 31)
  "FunctionDenormModeINTEL\0" // IR(17005, 24)
  "RegisterINTEL\0" // IR(17029, 14)
  "MemoryINTEL\0" // IR(17043, 12)
  "NumbanksINTEL\0" // IR(17055, 14)
  "BankwidthINTEL\0" // IR(17069, 15)
  "MaxPrivateCopiesINTEL\0" // IR(17084, 22)
  "SinglepumpINTEL\0" // IR(17106, 16)
  "DoublepumpINTEL\0" // IR(17122, 16)
  "MaxReplicatesINTEL\0" // IR(17138, 19)
  "SimpleDualPortINTEL\0" // IR(17157, 20)
  "MergeINTEL\0" // IR(17177, 11)
  "SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER\0" // IR(17188, 42)
  "BankBitsINTEL\0" // IR(17230, 14)
  "ForcePow2DepthINTEL\0" // IR(17244, 20)
  "StridesizeINTEL\0" // IR(17264, 16)
  "WordsizeINTEL\0" // IR(17280, 14)
  "TrueDualPortINTEL\0" // IR(17294, 18)
  "BurstCoalesceINTEL\0" // IR(17312, 19)
  "CacheSizeINTEL\0" // IR(17331, 15)
  "DontStaticallyCoalesceINTEL\0" // IR(17346, 28)
  "PrefetchINTEL\0" // IR(17374, 14)
  "StallEnableINTEL\0" // IR(17388, 17)
  "FuseLoopsInFunctionINTEL\0" // IR(17405, 25)
  "MathOpDSPModeINTEL\0" // IR(17430, 19)
  "AliasScopeINTEL\0" // IR(17449, 16)
  "NoAliasINTEL\0" // IR(17465, 13)
  "InitiationIntervalINTEL\0" // IR(17478, 24)
  "MaxConcurrencyINTEL\0" // IR(17502, 20)
  "PipelineEnableINTEL\0" // IR(17522, 20)
  "BufferLocationINTEL\0" // IR(17542, 20)
  "IOPipeStorageINTEL\0" // IR(17562, 19)
  "SPV_OPERAND_TYPE_FPOPERATION_MODE\0" // IR(17581, 34)
  "FunctionFloatingPointModeINTEL\0" // IR(17615, 31)
  "SingleElementVectorINTEL\0" // IR(17646, 25)
  "VectorComputeCallableFunctionINTEL\0" // IR(17671, 35)
  "MediaBlockIOINTEL\0" // IR(17706, 18)
  "StallFreeINTEL\0" // IR(17724, 15)
  "SPV_OPERAND_TYPE_LITERAL_FLOAT\0" // IR(17739, 31)
  "FPMaxErrorDecorationINTEL\0" // IR(17770, 26)
  "LatencyControlLabelINTEL\0" // IR(17796, 25)
  "LatencyControlConstraintINTEL\0" // IR(17821, 30)
  "ConduitKernelArgumentINTEL\0" // IR(17851, 27)
  "RegisterMapKernelArgumentINTEL\0" // IR(17878, 31)
  "MMHostInterfaceAddressWidthINTEL\0" // IR(17909, 33)
  "MMHostInterfaceDataWidthINTEL\0" // IR(17942, 30)
  "MMHostInterfaceLatencyINTEL\0" // IR(17972, 28)
  "SPV_OPERAND_TYPE_ACCESS_QUALIFIER\0" // IR(18000, 34)
  "MMHostInterfaceReadWriteModeINTEL\0" // IR(18034, 34)
  "MMHostInterfaceMaxBurstINTEL\0" // IR(18068, 29)
  "MMHostInterfaceWaitRequestINTEL\0" // IR(18097, 32)
  "StableKernelArgumentINTEL\0" // IR(18129, 26)
  "SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER\0" // IR(18155, 39)
  "HostAccessINTEL\0" // IR(18194, 16)
  "SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER\0" // IR(18210, 47)
  "InitModeINTEL\0" // IR(18257, 14)
  "ImplementInRegisterMapINTEL\0" // IR(18271, 28)
  "ConditionalINTEL\0" // IR(18299, 17)
  "SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL\0" // IR(18316, 36)
  "CacheControlLoadINTEL\0" // IR(18352, 22)
  "SPV_OPERAND_TYPE_STORE_CACHE_CONTROL\0" // IR(18374, 37)
  "CacheControlStoreINTEL\0" // IR(18411, 23)
  "1D\0" // IR(18434, 3)
  "2D\0" // IR(18437, 3)
  "3D\0" // IR(18440, 3)
  "Cube\0" // IR(18443, 5)
  "Rect\0" // IR(18448, 5)
  "Buffer\0" // IR(18453, 7)
  "SubpassData\0" // IR(18460, 12)
  "TileImageDataEXT\0" // IR(18472, 17)
  "Invocations\0" // IR(18489, 12)
  "SpacingEqual\0" // IR(18501, 13)
  "SpacingFractionalEven\0" // IR(18514, 22)
  "SpacingFractionalOdd\0" // IR(18536, 21)
  "VertexOrderCw\0" // IR(18557, 14)
  "VertexOrderCcw\0" // IR(18571, 15)
  "PixelCenterInteger\0" // IR(18586, 19)
  "OriginUpperLeft\0" // IR(18605, 16)
  "OriginLowerLeft\0" // IR(18621, 16)
  "EarlyFragmentTests\0" // IR(18637, 19)
  "PointMode\0" // IR(18656, 10)
  "Xfb\0" // IR(18666, 4)
  "DepthReplacing\0" // IR(18670, 15)
  "DepthGreater\0" // IR(18685, 13)
  "DepthLess\0" // IR(18698, 10)
  "DepthUnchanged\0" // IR(18708, 15)
  "LocalSize\0" // IR(18723, 10)
  "LocalSizeHint\0" // IR(18733, 14)
  "InputPoints\0" // IR(18747, 12)
  "InputLines\0" // IR(18759, 11)
  "InputLinesAdjacency\0" // IR(18770, 20)
  "Triangles\0" // IR(18790, 10)
  "InputTrianglesAdjacency\0" // IR(18800, 24)
  "Quads\0" // IR(18824, 6)
  "Isolines\0" // IR(18830, 9)
  "OutputVertices\0" // IR(18839, 15)
  "OutputPoints\0" // IR(18854, 13)
  "OutputLineStrip\0" // IR(18867, 16)
  "OutputTriangleStrip\0" // IR(18883, 20)
  "VecTypeHint\0" // IR(18903, 12)
  "ContractionOff\0" // IR(18915, 15)
  "Initializer\0" // IR(18930, 12)
  "Finalizer\0" // IR(18942, 10)
  "SubgroupsPerWorkgroup\0" // IR(18952, 22)
  "SubgroupsPerWorkgroupId\0" // IR(18974, 24)
  "LocalSizeId\0" // IR(18998, 12)
  "LocalSizeHintId\0" // IR(19010, 16)
  "NonCoherentColorAttachmentReadEXT\0" // IR(19026, 34)
  "NonCoherentDepthAttachmentReadEXT\0" // IR(19060, 34)
  "NonCoherentStencilAttachmentReadEXT\0" // IR(19094, 36)
  "SubgroupUniformControlFlowKHR\0" // IR(19130, 30)
  "PostDepthCoverage\0" // IR(19160, 18)
  "NonCoherentTileAttachmentReadQCOM\0" // IR(19178, 34)
  "TileShadingRateQCOM\0" // IR(19212, 20)
  "EarlyAndLateFragmentTestsAMD\0" // IR(19232, 29)
  "StencilRefReplacingEXT\0" // IR(19261, 23)
  "CoalescingAMDX\0" // IR(19284, 15)
  "IsApiEntryAMDX\0" // IR(19299, 15)
  "MaxNodeRecursionAMDX\0" // IR(19314, 21)
  "StaticNumWorkgroupsAMDX\0" // IR(19335, 24)
  "MaxNumWorkgroupsAMDX\0" // IR(19359, 21)
  "StencilRefUnchangedFrontAMD\0" // IR(19380, 28)
  "StencilRefGreaterFrontAMD\0" // IR(19408, 26)
  "StencilRefLessFrontAMD\0" // IR(19434, 23)
  "StencilRefUnchangedBackAMD\0" // IR(19457, 27)
  "StencilRefGreaterBackAMD\0" // IR(19484, 25)
  "StencilRefLessBackAMD\0" // IR(19509, 22)
  "QuadDerivativesKHR\0" // IR(19531, 19)
  "RequireFullQuadsKHR\0" // IR(19550, 20)
  "SharesInputWithAMDX\0" // IR(19570, 20)
  "OutputLinesEXT\0" // IR(19590, 15)
  "OutputLinesNV\0" // IR(19605, 14)
  "OutputPrimitivesEXT\0" // IR(19619, 20)
  "OutputPrimitivesNV\0" // IR(19639, 19)
  "DerivativeGroupQuadsKHR\0" // IR(19658, 24)
  "DerivativeGroupQuadsNV\0" // IR(19682, 23)
  "DerivativeGroupLinearKHR\0" // IR(19705, 25)
  "DerivativeGroupLinearNV\0" // IR(19730, 24)
  "OutputTrianglesEXT\0" // IR(19754, 19)
  "OutputTrianglesNV\0" // IR(19773, 18)
  "PixelInterlockOrderedEXT\0" // IR(19791, 25)
  "PixelInterlockUnorderedEXT\0" // IR(19816, 27)
  "SampleInterlockOrderedEXT\0" // IR(19843, 26)
  "SampleInterlockUnorderedEXT\0" // IR(19869, 28)
  "ShadingRateInterlockOrderedEXT\0" // IR(19897, 31)
  "ShadingRateInterlockUnorderedEXT\0" // IR(19928, 33)
  "SharedLocalMemorySizeINTEL\0" // IR(19961, 27)
  "RoundingModeRTPINTEL\0" // IR(19988, 21)
  "RoundingModeRTNINTEL\0" // IR(20009, 21)
  "FloatingPointModeALTINTEL\0" // IR(20030, 26)
  "FloatingPointModeIEEEINTEL\0" // IR(20056, 27)
  "MaxWorkgroupSizeINTEL\0" // IR(20083, 22)
  "MaxWorkDimINTEL\0" // IR(20105, 16)
  "NoGlobalOffsetINTEL\0" // IR(20121, 20)
  "NumSIMDWorkitemsINTEL\0" // IR(20141, 22)
  "SchedulerTargetFmaxMhzINTEL\0" // IR(20163, 28)
  "MaximallyReconvergesKHR\0" // IR(20191, 24)
  "FPFastMathDefault\0" // IR(20215, 18)
  "StreamingInterfaceINTEL\0" // IR(20233, 24)
  "RegisterMapInterfaceINTEL\0" // IR(20257, 26)
  "NamedBarrierCountINTEL\0" // IR(20283, 23)
  "MaximumRegistersINTEL\0" // IR(20306, 22)
  "MaximumRegistersIdINTEL\0" // IR(20328, 24)
  "SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS\0" // IR(20352, 51)
  "NamedMaximumRegistersINTEL\0" // IR(20403, 27)
  "Vertex\0" // IR(20430, 7)
  "TessellationControl\0" // IR(20437, 20)
  "TessellationEvaluation\0" // IR(20457, 23)
  "GLCompute\0" // IR(20480, 10)
  "TaskNV\0" // IR(20490, 7)
  "MeshNV\0" // IR(20497, 7)
  "RayGenerationKHR\0" // IR(20504, 17)
  "RayGenerationNV\0" // IR(20521, 16)
  "IntersectionKHR\0" // IR(20537, 16)
  "IntersectionNV\0" // IR(20553, 15)
  "AnyHitKHR\0" // IR(20568, 10)
  "AnyHitNV\0" // IR(20578, 9)
  "ClosestHitKHR\0" // IR(20587, 14)
  "ClosestHitNV\0" // IR(20601, 13)
  "MissKHR\0" // IR(20614, 8)
  "MissNV\0" // IR(20622, 7)
  "CallableKHR\0" // IR(20629, 12)
  "CallableNV\0" // IR(20641, 11)
  "TaskEXT\0" // IR(20652, 8)
  "MeshEXT\0" // IR(20660, 8)
  "Preserve\0" // IR(20668, 9)
  "FlushToZero\0" // IR(20677, 12)
  "BFloat16KHR\0" // IR(20689, 12)
  "Float8E4M3EXT\0" // IR(20701, 14)
  "Float8E5M2EXT\0" // IR(20715, 14)
  "IEEE\0" // IR(20729, 5)
  "ALT\0" // IR(20734, 4)
  "NotNaN\0" // IR(20738, 7)
  "NotInf\0" // IR(20745, 7)
  "NSZ\0" // IR(20752, 4)
  "AllowRecip\0" // IR(20756, 11)
  "Fast\0" // IR(20767, 5)
  "AllowContract\0" // IR(20772, 14)
  "AllowContractFastINTEL\0" // IR(20786, 23)
  "AllowReassoc\0" // IR(20809, 13)
  "AllowReassocINTEL\0" // IR(20822, 18)
  "AllowTransform\0" // IR(20840, 15)
  "RTE\0" // IR(20855, 4)
  "RTZ\0" // IR(20859, 4)
  "RTP\0" // IR(20863, 4)
  "RTN\0" // IR(20867, 4)
  "Vertical2Pixels\0" // IR(20871, 16)
  "Vertical4Pixels\0" // IR(20887, 16)
  "Horizontal2Pixels\0" // IR(20903, 18)
  "Horizontal4Pixels\0" // IR(20921, 18)
  "Inline\0" // IR(20939, 7)
  "DontInline\0" // IR(20946, 11)
  "Pure\0" // IR(20957, 5)
  "Const\0" // IR(20962, 6)
  "Zext\0" // IR(20968, 5)
  "Sext\0" // IR(20973, 5)
  "ByVal\0" // IR(20978, 6)
  "Sret\0" // IR(20984, 5)
  "NoAlias\0" // IR(20989, 8)
  "NoCapture\0" // IR(20997, 10)
  "NoWrite\0" // IR(21007, 8)
  "NoReadWrite\0" // IR(21015, 12)
  "RuntimeAlignedINTEL\0" // IR(21027, 20)
  "Reduce\0" // IR(21047, 7)
  "InclusiveScan\0" // IR(21054, 14)
  "ExclusiveScan\0" // IR(21068, 14)
  "ClusteredReduce\0" // IR(21082, 16)
  "PartitionedReduceNV\0" // IR(21098, 20)
  "PartitionedInclusiveScanNV\0" // IR(21118, 27)
  "PartitionedExclusiveScanNV\0" // IR(21145, 27)
  "NoneINTEL\0" // IR(21172, 10)
  "ReadINTEL\0" // IR(21182, 10)
  "WriteINTEL\0" // IR(21192, 11)
  "ReadWriteINTEL\0" // IR(21203, 15)
  "Bias\0" // IR(21218, 5)
  "Lod\0" // IR(21223, 4)
  "Grad\0" // IR(21227, 5)
  "ConstOffset\0" // IR(21232, 12)
  "ConstOffsets\0" // IR(21244, 13)
  "MakeTexelAvailable\0" // IR(21257, 19)
  "MakeTexelAvailableKHR\0" // IR(21276, 22)
  "MakeTexelVisible\0" // IR(21298, 17)
  "MakeTexelVisibleKHR\0" // IR(21315, 20)
  "NonPrivateTexel\0" // IR(21335, 16)
  "NonPrivateTexelKHR\0" // IR(21351, 19)
  "VolatileTexel\0" // IR(21370, 14)
  "VolatileTexelKHR\0" // IR(21384, 17)
  "SignExtend\0" // IR(21401, 11)
  "ZeroExtend\0" // IR(21412, 11)
  "Nontemporal\0" // IR(21423, 12)
  "Offsets\0" // IR(21435, 8)
  "SnormInt8\0" // IR(21443, 10)
  "SnormInt16\0" // IR(21453, 11)
  "UnormInt8\0" // IR(21464, 10)
  "UnormInt16\0" // IR(21474, 11)
  "UnormShort565\0" // IR(21485, 14)
  "UnormShort555\0" // IR(21499, 14)
  "UnormInt101010\0" // IR(21513, 15)
  "SignedInt8\0" // IR(21528, 11)
  "SignedInt16\0" // IR(21539, 12)
  "SignedInt32\0" // IR(21551, 12)
  "UnsignedInt8\0" // IR(21563, 13)
  "UnsignedInt16\0" // IR(21576, 14)
  "UnsignedInt32\0" // IR(21590, 14)
  "HalfFloat\0" // IR(21604, 10)
  "UnormInt24\0" // IR(21614, 11)
  "UnormInt101010_2\0" // IR(21625, 17)
  "UnormInt10X6EXT\0" // IR(21642, 16)
  "UnsignedIntRaw10EXT\0" // IR(21658, 20)
  "UnsignedIntRaw12EXT\0" // IR(21678, 20)
  "UnormInt2_101010EXT\0" // IR(21698, 20)
  "UnsignedInt10X6EXT\0" // IR(21718, 19)
  "UnsignedInt12X4EXT\0" // IR(21737, 19)
  "UnsignedInt14X2EXT\0" // IR(21756, 19)
  "UnormInt12X4EXT\0" // IR(21775, 16)
  "UnormInt14X2EXT\0" // IR(21791, 16)
  "R\0" // IR(21807, 2)
  "A\0" // IR(21809, 2)
  "RG\0" // IR(21811, 3)
  "RA\0" // IR(21814, 3)
  "RGB\0" // IR(21817, 4)
  "RGBA\0" // IR(21821, 5)
  "BGRA\0" // IR(21826, 5)
  "ARGB\0" // IR(21831, 5)
  "Intensity\0" // IR(21836, 10)
  "Luminance\0" // IR(21846, 10)
  "Rx\0" // IR(21856, 3)
  "RGx\0" // IR(21859, 4)
  "RGBx\0" // IR(21863, 5)
  "Depth\0" // IR(21868, 6)
  "DepthStencil\0" // IR(21874, 13)
  "sRGB\0" // IR(21887, 5)
  "sRGBx\0" // IR(21892, 6)
  "sRGBA\0" // IR(21898, 6)
  "sBGRA\0" // IR(21904, 6)
  "ABGR\0" // IR(21910, 5)
  "InitOnDeviceReprogramINTEL\0" // IR(21915, 27)
  "InitOnDeviceResetINTEL\0" // IR(21942, 23)
  "NoWait\0" // IR(21965, 7)
  "WaitKernel\0" // IR(21972, 11)
  "WaitWorkGroup\0" // IR(21983, 14)
  "CmdExecTime\0" // IR(21997, 12)
  "MayUsePrintf\0" // IR(22009, 13)
  "Export\0" // IR(22022, 7)
  "Import\0" // IR(22029, 7)
  "LinkOnceODR\0" // IR(22036, 12)
  "UncachedINTEL\0" // IR(22048, 14)
  "CachedINTEL\0" // IR(22062, 12)
  "StreamingINTEL\0" // IR(22074, 15)
  "InvalidateAfterReadINTEL\0" // IR(22089, 25)
  "ConstCachedINTEL\0" // IR(22114, 17)
  "Unroll\0" // IR(22131, 7)
  "DontUnroll\0" // IR(22138, 11)
  "DependencyInfinite\0" // IR(22149, 19)
  "DependencyLength\0" // IR(22168, 17)
  "MinIterations\0" // IR(22185, 14)
  "MaxIterations\0" // IR(22199, 14)
  "IterationMultiple\0" // IR(22213, 18)
  "PeelCount\0" // IR(22231, 10)
  "PartialCount\0" // IR(22241, 13)
  "DependencyArrayINTEL\0" // IR(22254, 21)
  "LoopCoalesceINTEL\0" // IR(22275, 18)
  "MaxInterleavingINTEL\0" // IR(22293, 21)
  "SpeculatedIterationsINTEL\0" // IR(22314, 26)
  "NoFusionINTEL\0" // IR(22340, 14)
  "LoopCountINTEL\0" // IR(22354, 15)
  "MaxReinvocationDelayINTEL\0" // IR(22369, 26)
  "MatrixASignedComponentsINTEL\0" // IR(22395, 29)
  "MatrixBSignedComponentsINTEL\0" // IR(22424, 29)
  "MatrixCBFloat16INTEL\0" // IR(22453, 21)
  "MatrixResultBFloat16INTEL\0" // IR(22474, 26)
  "MatrixAPackedInt8INTEL\0" // IR(22500, 23)
  "MatrixBPackedInt8INTEL\0" // IR(22523, 23)
  "MatrixAPackedInt4INTEL\0" // IR(22546, 23)
  "MatrixBPackedInt4INTEL\0" // IR(22569, 23)
  "MatrixATF32INTEL\0" // IR(22592, 17)
  "MatrixBTF32INTEL\0" // IR(22609, 17)
  "MatrixAPackedFloat16INTEL\0" // IR(22626, 26)
  "MatrixBPackedFloat16INTEL\0" // IR(22652, 26)
  "MatrixAPackedBFloat16INTEL\0" // IR(22678, 27)
  "MatrixBPackedBFloat16INTEL\0" // IR(22705, 27)
  "Aligned\0" // IR(22732, 8)
  "MakePointerAvailable\0" // IR(22740, 21)
  "MakePointerAvailableKHR\0" // IR(22761, 24)
  "MakePointerVisible\0" // IR(22785, 19)
  "MakePointerVisibleKHR\0" // IR(22804, 22)
  "NonPrivatePointer\0" // IR(22826, 18)
  "NonPrivatePointerKHR\0" // IR(22844, 21)
  "AliasScopeINTELMask\0" // IR(22865, 20)
  "NoAliasINTELMask\0" // IR(22885, 17)
  "Simple\0" // IR(22902, 7)
  "GLSL450\0" // IR(22909, 8)
  "OpenCL\0" // IR(22917, 7)
  "Vulkan\0" // IR(22924, 7)
  "VulkanKHR\0" // IR(22931, 10)
  "Relaxed\0" // IR(22941, 8)
  "Acquire\0" // IR(22949, 8)
  "Release\0" // IR(22957, 8)
  "AcquireRelease\0" // IR(22965, 15)
  "SequentiallyConsistent\0" // IR(22980, 23)
  "UniformMemory\0" // IR(23003, 14)
  "SubgroupMemory\0" // IR(23017, 15)
  "WorkgroupMemory\0" // IR(23032, 16)
  "CrossWorkgroupMemory\0" // IR(23048, 21)
  "AtomicCounterMemory\0" // IR(23069, 20)
  "ImageMemory\0" // IR(23089, 12)
  "OutputMemory\0" // IR(23101, 13)
  "OutputMemoryKHR\0" // IR(23114, 16)
  "MakeAvailable\0" // IR(23130, 14)
  "MakeAvailableKHR\0" // IR(23144, 17)
  "MakeVisible\0" // IR(23161, 12)
  "MakeVisibleKHR\0" // IR(23173, 15)
  "AutoINTEL\0" // IR(23188, 10)
  "WRAP\0" // IR(23198, 5)
  "SAT\0" // IR(23203, 4)
  "SAT_ZERO\0" // IR(23207, 9)
  "SAT_SYM\0" // IR(23216, 8)
  "PackedVectorFormat4x8Bit\0" // IR(23224, 25)
  "PackedVectorFormat4x8BitKHR\0" // IR(23249, 28)
  "TRN\0" // IR(23277, 4)
  "TRN_ZERO\0" // IR(23281, 9)
  "RND\0" // IR(23290, 4)
  "RND_ZERO\0" // IR(23294, 9)
  "RND_INF\0" // IR(23303, 8)
  "RND_MIN_INF\0" // IR(23311, 12)
  "RND_CONV\0" // IR(23323, 9)
  "RND_CONV_ODD\0" // IR(23332, 13)
  "RobustnessPerComponentNV\0" // IR(23345, 25)
  "RobustnessPerElementNV\0" // IR(23370, 23)
  "OpaqueKHR\0" // IR(23393, 10)
  "NoOpaqueKHR\0" // IR(23403, 12)
  "TerminateOnFirstHitKHR\0" // IR(23415, 23)
  "SkipClosestHitShaderKHR\0" // IR(23438, 24)
  "CullBackFacingTrianglesKHR\0" // IR(23462, 27)
  "CullFrontFacingTrianglesKHR\0" // IR(23489, 28)
  "CullOpaqueKHR\0" // IR(23517, 14)
  "CullNoOpaqueKHR\0" // IR(23531, 16)
  "SkipTrianglesKHR\0" // IR(23547, 17)
  "SkipBuiltinPrimitivesNV\0" // IR(23564, 24)
  "SkipAABBsKHR\0" // IR(23588, 13)
  "ForceOpacityMicromap2StateEXT\0" // IR(23601, 30)
  "RayQueryCandidateIntersectionTriangleKHR\0" // IR(23631, 41)
  "RayQueryCandidateIntersectionAABBKHR\0" // IR(23672, 37)
  "RayQueryCommittedIntersectionNoneKHR\0" // IR(23709, 37)
  "RayQueryCommittedIntersectionTriangleKHR\0" // IR(23746, 41)
  "RayQueryCommittedIntersectionGeneratedKHR\0" // IR(23787, 42)
  "RayQueryCandidateIntersectionKHR\0" // IR(23829, 33)
  "RayQueryCommittedIntersectionKHR\0" // IR(23862, 33)
  "ClampToEdge\0" // IR(23895, 12)
  "Clamp\0" // IR(23907, 6)
  "Repeat\0" // IR(23913, 7)
  "RepeatMirrored\0" // IR(23920, 15)
  "Nearest\0" // IR(23935, 8)
  "Linear\0" // IR(23943, 7)
  "Unknown\0" // IR(23950, 8)
  "Rgba32f\0" // IR(23958, 8)
  "Rgba16f\0" // IR(23966, 8)
  "R32f\0" // IR(23974, 5)
  "Rgba8\0" // IR(23979, 6)
  "Rgba8Snorm\0" // IR(23985, 11)
  "Rg32f\0" // IR(23996, 6)
  "Rg16f\0" // IR(24002, 6)
  "R11fG11fB10f\0" // IR(24008, 13)
  "R16f\0" // IR(24021, 5)
  "Rgba16\0" // IR(24026, 7)
  "Rgb10A2\0" // IR(24033, 8)
  "Rg16\0" // IR(24041, 5)
  "Rg8\0" // IR(24046, 4)
  "R16\0" // IR(24050, 4)
  "R8\0" // IR(24054, 3)
  "Rgba16Snorm\0" // IR(24057, 12)
  "Rg16Snorm\0" // IR(24069, 10)
  "Rg8Snorm\0" // IR(24079, 9)
  "R16Snorm\0" // IR(24088, 9)
  "R8Snorm\0" // IR(24097, 8)
  "Rgba32i\0" // IR(24105, 8)
  "Rgba16i\0" // IR(24113, 8)
  "Rgba8i\0" // IR(24121, 7)
  "R32i\0" // IR(24128, 5)
  "Rg32i\0" // IR(24133, 6)
  "Rg16i\0" // IR(24139, 6)
  "Rg8i\0" // IR(24145, 5)
  "R16i\0" // IR(24150, 5)
  "R8i\0" // IR(24155, 4)
  "Rgba32ui\0" // IR(24159, 9)
  "Rgba16ui\0" // IR(24168, 9)
  "Rgba8ui\0" // IR(24177, 8)
  "R32ui\0" // IR(24185, 6)
  "Rgb10a2ui\0" // IR(24191, 10)
  "Rg32ui\0" // IR(24201, 7)
  "Rg16ui\0" // IR(24208, 7)
  "Rg8ui\0" // IR(24215, 6)
  "R16ui\0" // IR(24221, 6)
  "R8ui\0" // IR(24227, 5)
  "R64ui\0" // IR(24232, 6)
  "R64i\0" // IR(24238, 5)
  "CrossDevice\0" // IR(24243, 12)
  "Device\0" // IR(24255, 7)
  "Workgroup\0" // IR(24262, 10)
  "Subgroup\0" // IR(24272, 9)
  "Invocation\0" // IR(24281, 11)
  "QueueFamily\0" // IR(24292, 12)
  "QueueFamilyKHR\0" // IR(24304, 15)
  "ShaderCallKHR\0" // IR(24319, 14)
  "Flatten\0" // IR(24333, 8)
  "DontFlatten\0" // IR(24341, 12)
  "IdentifierPossibleDuplicates\0" // IR(24353, 29)
  "FlagUnknownPhysicalLayout\0" // IR(24382, 26)
  "ESSL\0" // IR(24408, 5)
  "GLSL\0" // IR(24413, 5)
  "OpenCL_C\0" // IR(24418, 9)
  "OpenCL_CPP\0" // IR(24427, 11)
  "HLSL\0" // IR(24438, 5)
  "CPP_for_OpenCL\0" // IR(24443, 15)
  "SYCL\0" // IR(24458, 5)
  "HERO_C\0" // IR(24463, 7)
  "NZSL\0" // IR(24470, 5)
  "WGSL\0" // IR(24475, 5)
  "Slang\0" // IR(24480, 6)
  "Zig\0" // IR(24486, 4)
  "Rust\0" // IR(24490, 5)
  "UniformConstant\0" // IR(24495, 16)
  "Input\0" // IR(24511, 6)
  "Output\0" // IR(24517, 7)
  "CrossWorkgroup\0" // IR(24524, 15)
  "Private\0" // IR(24539, 8)
  "Function\0" // IR(24547, 9)
  "Generic\0" // IR(24556, 8)
  "PushConstant\0" // IR(24564, 13)
  "AtomicCounter\0" // IR(24577, 14)
  "Image\0" // IR(24591, 6)
  "StorageBuffer\0" // IR(24597, 14)
  "TileImageEXT\0" // IR(24611, 13)
  "TileAttachmentQCOM\0" // IR(24624, 19)
  "NodePayloadAMDX\0" // IR(24643, 16)
  "CallableDataKHR\0" // IR(24659, 16)
  "CallableDataNV\0" // IR(24675, 15)
  "IncomingCallableDataKHR\0" // IR(24690, 24)
  "IncomingCallableDataNV\0" // IR(24714, 23)
  "RayPayloadKHR\0" // IR(24737, 14)
  "RayPayloadNV\0" // IR(24751, 13)
  "HitAttributeKHR\0" // IR(24764, 16)
  "HitAttributeNV\0" // IR(24780, 15)
  "IncomingRayPayloadKHR\0" // IR(24795, 22)
  "IncomingRayPayloadNV\0" // IR(24817, 21)
  "ShaderRecordBufferKHR\0" // IR(24838, 22)
  "ShaderRecordBufferNV\0" // IR(24860, 21)
  "PhysicalStorageBuffer\0" // IR(24881, 22)
  "PhysicalStorageBufferEXT\0" // IR(24903, 25)
  "HitObjectAttributeNV\0" // IR(24928, 21)
  "TaskPayloadWorkgroupEXT\0" // IR(24949, 24)
  "CodeSectionINTEL\0" // IR(24973, 17)
  "DeviceOnlyINTEL\0" // IR(24990, 16)
  "HostOnlyINTEL\0" // IR(25006, 14)
  "WriteThroughINTEL\0" // IR(25020, 18)
  "WriteBackINTEL\0" // IR(25038, 15)
  "TensorView\0" // IR(25053, 11)
  "DecodeFunc\0" // IR(25064, 11)
  "Undefined\0" // IR(25075, 10)
  "NoneARM\0" // IR(25085, 8)
  "NontemporalARM\0" // IR(25093, 15)
  "OutOfBoundsValueARM\0" // IR(25108, 20)
  "MakeElementAvailableARM\0" // IR(25128, 24)
  "MakeElementVisibleARM\0" // IR(25152, 22)
  "NonPrivateElementARM\0" // IR(25174, 21)
  "Nop\0" // IR(25195, 4)
  "SPV_OPERAND_TYPE_TYPE_ID\0" // IR(25199, 25)
  "SPV_OPERAND_TYPE_RESULT_ID\0" // IR(25224, 27)
  "Undef\0" // IR(25251, 6)
  "SourceContinued\0" // IR(25257, 16)
  "SPV_OPERAND_TYPE_SOURCE_LANGUAGE\0" // IR(25273, 33)
  "SPV_OPERAND_TYPE_OPTIONAL_ID\0" // IR(25306, 29)
  "SPV_OPERAND_TYPE_OPTIONAL_LITERAL_STRING\0" // IR(25335, 41)
  "Source\0" // IR(25376, 7)
  "SourceExtension\0" // IR(25383, 16)
  "Name\0" // IR(25399, 5)
  "MemberName\0" // IR(25404, 11)
  "String\0" // IR(25415, 7)
  "Line\0" // IR(25422, 5)
  "Extension\0" // IR(25427, 10)
  "ExtInstImport\0" // IR(25437, 14)
  "SPV_OPERAND_TYPE_EXTENSION_INSTRUCTION_NUMBER\0" // IR(25451, 46)
  "ExtInst\0" // IR(25497, 8)
  "SPV_OPERAND_TYPE_ADDRESSING_MODEL\0" // IR(25505, 34)
  "SPV_OPERAND_TYPE_MEMORY_MODEL\0" // IR(25539, 30)
  "MemoryModel\0" // IR(25569, 12)
  "SPV_OPERAND_TYPE_EXECUTION_MODEL\0" // IR(25581, 33)
  "SPV_OPERAND_TYPE_VARIABLE_ID\0" // IR(25614, 29)
  "EntryPoint\0" // IR(25643, 11)
  "SPV_OPERAND_TYPE_EXECUTION_MODE\0" // IR(25654, 32)
  "ExecutionMode\0" // IR(25686, 14)
  "SPV_OPERAND_TYPE_CAPABILITY\0" // IR(25700, 28)
  "Capability\0" // IR(25728, 11)
  "TypeVoid\0" // IR(25739, 9)
  "TypeBool\0" // IR(25748, 9)
  "TypeInt\0" // IR(25757, 8)
  "SPV_OPERAND_TYPE_OPTIONAL_FPENCODING\0" // IR(25765, 37)
  "TypeFloat\0" // IR(25802, 10)
  "TypeVector\0" // IR(25812, 11)
  "TypeMatrix\0" // IR(25823, 11)
  "SPV_OPERAND_TYPE_DIMENSIONALITY\0" // IR(25834, 32)
  "SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT\0" // IR(25866, 38)
  "SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER\0" // IR(25904, 43)
  "TypeImage\0" // IR(25947, 10)
  "TypeSampler\0" // IR(25957, 12)
  "TypeSampledImage\0" // IR(25969, 17)
  "TypeArray\0" // IR(25986, 10)
  "TypeRuntimeArray\0" // IR(25996, 17)
  "TypeStruct\0" // IR(26013, 11)
  "TypeOpaque\0" // IR(26024, 11)
  "SPV_OPERAND_TYPE_STORAGE_CLASS\0" // IR(26035, 31)
  "TypePointer\0" // IR(26066, 12)
  "TypeFunction\0" // IR(26078, 13)
  "TypeEvent\0" // IR(26091, 10)
  "TypeDeviceEvent\0" // IR(26101, 16)
  "TypeReserveId\0" // IR(26117, 14)
  "TypeQueue\0" // IR(26131, 10)
  "TypePipe\0" // IR(26141, 9)
  "TypeForwardPointer\0" // IR(26150, 19)
  "ConstantTrue\0" // IR(26169, 13)
  "ConstantFalse\0" // IR(26182, 14)
  "SPV_OPERAND_TYPE_TYPED_LITERAL_NUMBER\0" // IR(26196, 38)
  "ConstantComposite\0" // IR(26234, 18)
  "SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE\0" // IR(26252, 41)
  "SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE\0" // IR(26293, 37)
  "ConstantSampler\0" // IR(26330, 16)
  "ConstantNull\0" // IR(26346, 13)
  "SpecConstantTrue\0" // IR(26359, 17)
  "SpecConstantFalse\0" // IR(26376, 18)
  "SpecConstant\0" // IR(26394, 13)
  "SpecConstantComposite\0" // IR(26407, 22)
  "SPV_OPERAND_TYPE_SPEC_CONSTANT_OP_NUMBER\0" // IR(26429, 41)
  "SpecConstantOp\0" // IR(26470, 15)
  "SPV_OPERAND_TYPE_FUNCTION_CONTROL\0" // IR(26485, 34)
  "FunctionParameter\0" // IR(26519, 18)
  "FunctionEnd\0" // IR(26537, 12)
  "FunctionCall\0" // IR(26549, 13)
  "Variable\0" // IR(26562, 9)
  "ImageTexelPointer\0" // IR(26571, 18)
  "SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS\0" // IR(26589, 40)
  "Load\0" // IR(26629, 5)
  "Store\0" // IR(26634, 6)
  "CopyMemory\0" // IR(26640, 11)
  "CopyMemorySized\0" // IR(26651, 16)
  "AccessChain\0" // IR(26667, 12)
  "InBoundsAccessChain\0" // IR(26679, 20)
  "PtrAccessChain\0" // IR(26699, 15)
  "ArrayLength\0" // IR(26714, 12)
  "GenericPtrMemSemantics\0" // IR(26726, 23)
  "InBoundsPtrAccessChain\0" // IR(26749, 23)
  "SPV_OPERAND_TYPE_DECORATION\0" // IR(26772, 28)
  "Decorate\0" // IR(26800, 9)
  "MemberDecorate\0" // IR(26809, 15)
  "DecorationGroup\0" // IR(26824, 16)
  "GroupDecorate\0" // IR(26840, 14)
  "SPV_OPERAND_TYPE_VARIABLE_ID_LITERAL_INTEGER\0" // IR(26854, 45)
  "GroupMemberDecorate\0" // IR(26899, 20)
  "VectorExtractDynamic\0" // IR(26919, 21)
  "VectorInsertDynamic\0" // IR(26940, 20)
  "VectorShuffle\0" // IR(26960, 14)
  "CompositeConstruct\0" // IR(26974, 19)
  "CompositeExtract\0" // IR(26993, 17)
  "CompositeInsert\0" // IR(27010, 16)
  "CopyObject\0" // IR(27026, 11)
  "Transpose\0" // IR(27037, 10)
  "SampledImage\0" // IR(27047, 13)
  "SPV_OPERAND_TYPE_OPTIONAL_IMAGE\0" // IR(27060, 32)
  "ImageSampleImplicitLod\0" // IR(27092, 23)
  "SPV_OPERAND_TYPE_IMAGE\0" // IR(27115, 23)
  "ImageSampleExplicitLod\0" // IR(27138, 23)
  "ImageSampleDrefImplicitLod\0" // IR(27161, 27)
  "ImageSampleDrefExplicitLod\0" // IR(27188, 27)
  "ImageSampleProjImplicitLod\0" // IR(27215, 27)
  "ImageSampleProjExplicitLod\0" // IR(27242, 27)
  "ImageSampleProjDrefImplicitLod\0" // IR(27269, 31)
  "ImageSampleProjDrefExplicitLod\0" // IR(27300, 31)
  "ImageFetch\0" // IR(27331, 11)
  "ImageGather\0" // IR(27342, 12)
  "ImageDrefGather\0" // IR(27354, 16)
  "ImageRead\0" // IR(27370, 10)
  "ImageWrite\0" // IR(27380, 11)
  "ImageQueryFormat\0" // IR(27391, 17)
  "ImageQueryOrder\0" // IR(27408, 16)
  "ImageQuerySizeLod\0" // IR(27424, 18)
  "ImageQuerySize\0" // IR(27442, 15)
  "ImageQueryLod\0" // IR(27457, 14)
  "ImageQueryLevels\0" // IR(27471, 17)
  "ImageQuerySamples\0" // IR(27488, 18)
  "ConvertFToU\0" // IR(27506, 12)
  "ConvertFToS\0" // IR(27518, 12)
  "ConvertSToF\0" // IR(27530, 12)
  "ConvertUToF\0" // IR(27542, 12)
  "UConvert\0" // IR(27554, 9)
  "SConvert\0" // IR(27563, 9)
  "FConvert\0" // IR(27572, 9)
  "QuantizeToF16\0" // IR(27581, 14)
  "ConvertPtrToU\0" // IR(27595, 14)
  "SatConvertSToU\0" // IR(27609, 15)
  "SatConvertUToS\0" // IR(27624, 15)
  "ConvertUToPtr\0" // IR(27639, 14)
  "PtrCastToGeneric\0" // IR(27653, 17)
  "GenericCastToPtr\0" // IR(27670, 17)
  "GenericCastToPtrExplicit\0" // IR(27687, 25)
  "Bitcast\0" // IR(27712, 8)
  "SNegate\0" // IR(27720, 8)
  "FNegate\0" // IR(27728, 8)
  "IAdd\0" // IR(27736, 5)
  "FAdd\0" // IR(27741, 5)
  "ISub\0" // IR(27746, 5)
  "FSub\0" // IR(27751, 5)
  "IMul\0" // IR(27756, 5)
  "FMul\0" // IR(27761, 5)
  "UDiv\0" // IR(27766, 5)
  "SDiv\0" // IR(27771, 5)
  "FDiv\0" // IR(27776, 5)
  "UMod\0" // IR(27781, 5)
  "SRem\0" // IR(27786, 5)
  "SMod\0" // IR(27791, 5)
  "FRem\0" // IR(27796, 5)
  "FMod\0" // IR(27801, 5)
  "VectorTimesScalar\0" // IR(27806, 18)
  "MatrixTimesScalar\0" // IR(27824, 18)
  "VectorTimesMatrix\0" // IR(27842, 18)
  "MatrixTimesVector\0" // IR(27860, 18)
  "MatrixTimesMatrix\0" // IR(27878, 18)
  "OuterProduct\0" // IR(27896, 13)
  "Dot\0" // IR(27909, 4)
  "IAddCarry\0" // IR(27913, 10)
  "ISubBorrow\0" // IR(27923, 11)
  "UMulExtended\0" // IR(27934, 13)
  "SMulExtended\0" // IR(27947, 13)
  "Any\0" // IR(27960, 4)
  "All\0" // IR(27964, 4)
  "IsNan\0" // IR(27968, 6)
  "IsInf\0" // IR(27974, 6)
  "IsFinite\0" // IR(27980, 9)
  "IsNormal\0" // IR(27989, 9)
  "SignBitSet\0" // IR(27998, 11)
  "LessOrGreater\0" // IR(28009, 14)
  "Ordered\0" // IR(28023, 8)
  "Unordered\0" // IR(28031, 10)
  "LogicalEqual\0" // IR(28041, 13)
  "LogicalNotEqual\0" // IR(28054, 16)
  "LogicalOr\0" // IR(28070, 10)
  "LogicalAnd\0" // IR(28080, 11)
  "LogicalNot\0" // IR(28091, 11)
  "Select\0" // IR(28102, 7)
  "IEqual\0" // IR(28109, 7)
  "INotEqual\0" // IR(28116, 10)
  "UGreaterThan\0" // IR(28126, 13)
  "SGreaterThan\0" // IR(28139, 13)
  "UGreaterThanEqual\0" // IR(28152, 18)
  "SGreaterThanEqual\0" // IR(28170, 18)
  "ULessThan\0" // IR(28188, 10)
  "SLessThan\0" // IR(28198, 10)
  "ULessThanEqual\0" // IR(28208, 15)
  "SLessThanEqual\0" // IR(28223, 15)
  "FOrdEqual\0" // IR(28238, 10)
  "FUnordEqual\0" // IR(28248, 12)
  "FOrdNotEqual\0" // IR(28260, 13)
  "FUnordNotEqual\0" // IR(28273, 15)
  "FOrdLessThan\0" // IR(28288, 13)
  "FUnordLessThan\0" // IR(28301, 15)
  "FOrdGreaterThan\0" // IR(28316, 16)
  "FUnordGreaterThan\0" // IR(28332, 18)
  "FOrdLessThanEqual\0" // IR(28350, 18)
  "FUnordLessThanEqual\0" // IR(28368, 20)
  "FOrdGreaterThanEqual\0" // IR(28388, 21)
  "FUnordGreaterThanEqual\0" // IR(28409, 23)
  "ShiftRightLogical\0" // IR(28432, 18)
  "ShiftRightArithmetic\0" // IR(28450, 21)
  "ShiftLeftLogical\0" // IR(28471, 17)
  "BitwiseOr\0" // IR(28488, 10)
  "BitwiseXor\0" // IR(28498, 11)
  "BitwiseAnd\0" // IR(28509, 11)
  "Not\0" // IR(28520, 4)
  "BitFieldInsert\0" // IR(28524, 15)
  "BitFieldSExtract\0" // IR(28539, 17)
  "BitFieldUExtract\0" // IR(28556, 17)
  "BitReverse\0" // IR(28573, 11)
  "BitCount\0" // IR(28584, 9)
  "DPdx\0" // IR(28593, 5)
  "DPdy\0" // IR(28598, 5)
  "Fwidth\0" // IR(28603, 7)
  "DPdxFine\0" // IR(28610, 9)
  "DPdyFine\0" // IR(28619, 9)
  "FwidthFine\0" // IR(28628, 11)
  "DPdxCoarse\0" // IR(28639, 11)
  "DPdyCoarse\0" // IR(28650, 11)
  "FwidthCoarse\0" // IR(28661, 13)
  "EmitVertex\0" // IR(28674, 11)
  "EndPrimitive\0" // IR(28685, 13)
  "EmitStreamVertex\0" // IR(28698, 17)
  "EndStreamPrimitive\0" // IR(28715, 19)
  "SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID\0" // IR(28734, 37)
  "ControlBarrier\0" // IR(28771, 15)
  "MemoryBarrier\0" // IR(28786, 14)
  "AtomicLoad\0" // IR(28800, 11)
  "AtomicStore\0" // IR(28811, 12)
  "AtomicExchange\0" // IR(28823, 15)
  "AtomicCompareExchange\0" // IR(28838, 22)
  "AtomicCompareExchangeWeak\0" // IR(28860, 26)
  "AtomicIIncrement\0" // IR(28886, 17)
  "AtomicIDecrement\0" // IR(28903, 17)
  "AtomicIAdd\0" // IR(28920, 11)
  "AtomicISub\0" // IR(28931, 11)
  "AtomicSMin\0" // IR(28942, 11)
  "AtomicUMin\0" // IR(28953, 11)
  "AtomicSMax\0" // IR(28964, 11)
  "AtomicUMax\0" // IR(28975, 11)
  "AtomicAnd\0" // IR(28986, 10)
  "AtomicOr\0" // IR(28996, 9)
  "AtomicXor\0" // IR(29005, 10)
  "Phi\0" // IR(29015, 4)
  "SPV_OPERAND_TYPE_LOOP_CONTROL\0" // IR(29019, 30)
  "LoopMerge\0" // IR(29049, 10)
  "SPV_OPERAND_TYPE_SELECTION_CONTROL\0" // IR(29059, 35)
  "SelectionMerge\0" // IR(29094, 15)
  "Label\0" // IR(29109, 6)
  "Branch\0" // IR(29115, 7)
  "BranchConditional\0" // IR(29122, 18)
  "SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER_ID\0" // IR(29140, 45)
  "Switch\0" // IR(29185, 7)
  "Kill\0" // IR(29192, 5)
  "Return\0" // IR(29197, 7)
  "ReturnValue\0" // IR(29204, 12)
  "Unreachable\0" // IR(29216, 12)
  "LifetimeStart\0" // IR(29228, 14)
  "LifetimeStop\0" // IR(29242, 13)
  "GroupAsyncCopy\0" // IR(29255, 15)
  "GroupWaitEvents\0" // IR(29270, 16)
  "GroupAll\0" // IR(29286, 9)
  "GroupAny\0" // IR(29295, 9)
  "GroupBroadcast\0" // IR(29304, 15)
  "SPV_OPERAND_TYPE_GROUP_OPERATION\0" // IR(29319, 33)
  "GroupIAdd\0" // IR(29352, 10)
  "GroupFAdd\0" // IR(29362, 10)
  "GroupFMin\0" // IR(29372, 10)
  "GroupUMin\0" // IR(29382, 10)
  "GroupSMin\0" // IR(29392, 10)
  "GroupFMax\0" // IR(29402, 10)
  "GroupUMax\0" // IR(29412, 10)
  "GroupSMax\0" // IR(29422, 10)
  "ReadPipe\0" // IR(29432, 9)
  "WritePipe\0" // IR(29441, 10)
  "ReservedReadPipe\0" // IR(29451, 17)
  "ReservedWritePipe\0" // IR(29468, 18)
  "ReserveReadPipePackets\0" // IR(29486, 23)
  "ReserveWritePipePackets\0" // IR(29509, 24)
  "CommitReadPipe\0" // IR(29533, 15)
  "CommitWritePipe\0" // IR(29548, 16)
  "IsValidReserveId\0" // IR(29564, 17)
  "GetNumPipePackets\0" // IR(29581, 18)
  "GetMaxPipePackets\0" // IR(29599, 18)
  "GroupReserveReadPipePackets\0" // IR(29617, 28)
  "GroupReserveWritePipePackets\0" // IR(29645, 29)
  "GroupCommitReadPipe\0" // IR(29674, 20)
  "GroupCommitWritePipe\0" // IR(29694, 21)
  "EnqueueMarker\0" // IR(29715, 14)
  "EnqueueKernel\0" // IR(29729, 14)
  "GetKernelNDrangeSubGroupCount\0" // IR(29743, 30)
  "GetKernelNDrangeMaxSubGroupSize\0" // IR(29773, 32)
  "GetKernelWorkGroupSize\0" // IR(29805, 23)
  "GetKernelPreferredWorkGroupSizeMultiple\0" // IR(29828, 40)
  "RetainEvent\0" // IR(29868, 12)
  "ReleaseEvent\0" // IR(29880, 13)
  "CreateUserEvent\0" // IR(29893, 16)
  "IsValidEvent\0" // IR(29909, 13)
  "SetUserEventStatus\0" // IR(29922, 19)
  "CaptureEventProfilingInfo\0" // IR(29941, 26)
  "GetDefaultQueue\0" // IR(29967, 16)
  "BuildNDRange\0" // IR(29983, 13)
  "ImageSparseSampleImplicitLod\0" // IR(29996, 29)
  "ImageSparseSampleExplicitLod\0" // IR(30025, 29)
  "ImageSparseSampleDrefImplicitLod\0" // IR(30054, 33)
  "ImageSparseSampleDrefExplicitLod\0" // IR(30087, 33)
  "ImageSparseSampleProjImplicitLod\0" // IR(30120, 33)
  "ImageSparseSampleProjExplicitLod\0" // IR(30153, 33)
  "ImageSparseSampleProjDrefImplicitLod\0" // IR(30186, 37)
  "ImageSparseSampleProjDrefExplicitLod\0" // IR(30223, 37)
  "ImageSparseFetch\0" // IR(30260, 17)
  "ImageSparseGather\0" // IR(30277, 18)
  "ImageSparseDrefGather\0" // IR(30295, 22)
  "ImageSparseTexelsResident\0" // IR(30317, 26)
  "NoLine\0" // IR(30343, 7)
  "AtomicFlagTestAndSet\0" // IR(30350, 21)
  "AtomicFlagClear\0" // IR(30371, 16)
  "ImageSparseRead\0" // IR(30387, 16)
  "SizeOf\0" // IR(30403, 7)
  "TypePipeStorage\0" // IR(30410, 16)
  "ConstantPipeStorage\0" // IR(30426, 20)
  "CreatePipeFromPipeStorage\0" // IR(30446, 26)
  "GetKernelLocalSizeForSubgroupCount\0" // IR(30472, 35)
  "GetKernelMaxNumSubgroups\0" // IR(30507, 25)
  "TypeNamedBarrier\0" // IR(30532, 17)
  "NamedBarrierInitialize\0" // IR(30549, 23)
  "MemoryNamedBarrier\0" // IR(30572, 19)
  "ModuleProcessed\0" // IR(30591, 16)
  "ExecutionModeId\0" // IR(30607, 16)
  "DecorateId\0" // IR(30623, 11)
  "GroupNonUniformElect\0" // IR(30634, 21)
  "GroupNonUniformAll\0" // IR(30655, 19)
  "GroupNonUniformAny\0" // IR(30674, 19)
  "GroupNonUniformAllEqual\0" // IR(30693, 24)
  "GroupNonUniformBroadcast\0" // IR(30717, 25)
  "GroupNonUniformBroadcastFirst\0" // IR(30742, 30)
  "GroupNonUniformInverseBallot\0" // IR(30772, 29)
  "GroupNonUniformBallotBitExtract\0" // IR(30801, 32)
  "GroupNonUniformBallotBitCount\0" // IR(30833, 30)
  "GroupNonUniformBallotFindLSB\0" // IR(30863, 29)
  "GroupNonUniformBallotFindMSB\0" // IR(30892, 29)
  "GroupNonUniformShuffleXor\0" // IR(30921, 26)
  "GroupNonUniformShuffleUp\0" // IR(30947, 25)
  "GroupNonUniformShuffleDown\0" // IR(30972, 27)
  "GroupNonUniformIAdd\0" // IR(30999, 20)
  "GroupNonUniformFAdd\0" // IR(31019, 20)
  "GroupNonUniformIMul\0" // IR(31039, 20)
  "GroupNonUniformFMul\0" // IR(31059, 20)
  "GroupNonUniformSMin\0" // IR(31079, 20)
  "GroupNonUniformUMin\0" // IR(31099, 20)
  "GroupNonUniformFMin\0" // IR(31119, 20)
  "GroupNonUniformSMax\0" // IR(31139, 20)
  "GroupNonUniformUMax\0" // IR(31159, 20)
  "GroupNonUniformFMax\0" // IR(31179, 20)
  "GroupNonUniformBitwiseAnd\0" // IR(31199, 26)
  "GroupNonUniformBitwiseOr\0" // IR(31225, 25)
  "GroupNonUniformBitwiseXor\0" // IR(31250, 26)
  "GroupNonUniformLogicalAnd\0" // IR(31276, 26)
  "GroupNonUniformLogicalOr\0" // IR(31302, 25)
  "GroupNonUniformLogicalXor\0" // IR(31327, 26)
  "GroupNonUniformQuadBroadcast\0" // IR(31353, 29)
  "GroupNonUniformQuadSwap\0" // IR(31382, 24)
  "CopyLogical\0" // IR(31406, 12)
  "PtrEqual\0" // IR(31418, 9)
  "PtrNotEqual\0" // IR(31427, 12)
  "PtrDiff\0" // IR(31439, 8)
  "ColorAttachmentReadEXT\0" // IR(31447, 23)
  "DepthAttachmentReadEXT\0" // IR(31470, 23)
  "StencilAttachmentReadEXT\0" // IR(31493, 25)
  "TypeTensorARM\0" // IR(31518, 14)
  "SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS\0" // IR(31532, 42)
  "TensorReadARM\0" // IR(31574, 14)
  "TensorWriteARM\0" // IR(31588, 15)
  "TensorQuerySizeARM\0" // IR(31603, 19)
  "GraphConstantARM\0" // IR(31622, 17)
  "GraphEntryPointARM\0" // IR(31639, 19)
  "GraphInputARM\0" // IR(31658, 14)
  "GraphSetOutputARM\0" // IR(31672, 18)
  "GraphEndARM\0" // IR(31690, 12)
  "TypeGraphARM\0" // IR(31702, 13)
  "TerminateInvocation\0" // IR(31715, 20)
  "TypeUntypedPointerKHR\0" // IR(31735, 22)
  "UntypedVariableKHR\0" // IR(31757, 19)
  "UntypedAccessChainKHR\0" // IR(31776, 22)
  "UntypedInBoundsAccessChainKHR\0" // IR(31798, 30)
  "SubgroupFirstInvocationKHR\0" // IR(31828, 27)
  "UntypedPtrAccessChainKHR\0" // IR(31855, 25)
  "UntypedInBoundsPtrAccessChainKHR\0" // IR(31880, 33)
  "UntypedArrayLengthKHR\0" // IR(31913, 22)
  "UntypedPrefetchKHR\0" // IR(31935, 19)
  "SubgroupAllKHR\0" // IR(31954, 15)
  "SubgroupAnyKHR\0" // IR(31969, 15)
  "SubgroupAllEqualKHR\0" // IR(31984, 20)
  "SubgroupReadInvocationKHR\0" // IR(32004, 26)
  "ExtInstWithForwardRefsKHR\0" // IR(32030, 26)
  "UntypedGroupAsyncCopyKHR\0" // IR(32056, 25)
  "TraceRayKHR\0" // IR(32081, 12)
  "ExecuteCallableKHR\0" // IR(32093, 19)
  "ConvertUToAccelerationStructureKHR\0" // IR(32112, 35)
  "IgnoreIntersectionKHR\0" // IR(32147, 22)
  "TerminateRayKHR\0" // IR(32169, 16)
  "SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT\0" // IR(32185, 47)
  "SDot\0" // IR(32232, 5)
  "SDotKHR\0" // IR(32237, 8)
  "UDot\0" // IR(32245, 5)
  "UDotKHR\0" // IR(32250, 8)
  "SUDot\0" // IR(32258, 6)
  "SUDotKHR\0" // IR(32264, 9)
  "SDotAccSat\0" // IR(32273, 11)
  "SDotAccSatKHR\0" // IR(32284, 14)
  "UDotAccSat\0" // IR(32298, 11)
  "UDotAccSatKHR\0" // IR(32309, 14)
  "SUDotAccSat\0" // IR(32323, 12)
  "SUDotAccSatKHR\0" // IR(32335, 15)
  "TypeCooperativeMatrixKHR\0" // IR(32350, 25)
  "CooperativeMatrixLoadKHR\0" // IR(32375, 25)
  "CooperativeMatrixStoreKHR\0" // IR(32400, 26)
  "SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS\0" // IR(32426, 54)
  "CooperativeMatrixMulAddKHR\0" // IR(32480, 27)
  "CooperativeMatrixLengthKHR\0" // IR(32507, 27)
  "ConstantCompositeReplicateEXT\0" // IR(32534, 30)
  "SpecConstantCompositeReplicateEXT\0" // IR(32564, 34)
  "CompositeConstructReplicateEXT\0" // IR(32598, 31)
  "TypeRayQueryKHR\0" // IR(32629, 16)
  "RayQueryInitializeKHR\0" // IR(32645, 22)
  "RayQueryTerminateKHR\0" // IR(32667, 21)
  "RayQueryGenerateIntersectionKHR\0" // IR(32688, 32)
  "RayQueryConfirmIntersectionKHR\0" // IR(32720, 31)
  "RayQueryProceedKHR\0" // IR(32751, 19)
  "RayQueryGetIntersectionTypeKHR\0" // IR(32770, 31)
  "ImageSampleWeightedQCOM\0" // IR(32801, 24)
  "ImageBoxFilterQCOM\0" // IR(32825, 19)
  "ImageBlockMatchSSDQCOM\0" // IR(32844, 23)
  "ImageBlockMatchSADQCOM\0" // IR(32867, 23)
  "BitCastArrayQCOM\0" // IR(32890, 17)
  "ImageBlockMatchWindowSSDQCOM\0" // IR(32907, 29)
  "ImageBlockMatchWindowSADQCOM\0" // IR(32936, 29)
  "ImageBlockMatchGatherSSDQCOM\0" // IR(32965, 29)
  "ImageBlockMatchGatherSADQCOM\0" // IR(32994, 29)
  "CompositeConstructCoopMatQCOM\0" // IR(33023, 30)
  "CompositeExtractCoopMatQCOM\0" // IR(33053, 28)
  "ExtractSubArrayQCOM\0" // IR(33081, 20)
  "GroupIAddNonUniformAMD\0" // IR(33101, 23)
  "GroupFAddNonUniformAMD\0" // IR(33124, 23)
  "GroupFMinNonUniformAMD\0" // IR(33147, 23)
  "GroupUMinNonUniformAMD\0" // IR(33170, 23)
  "GroupSMinNonUniformAMD\0" // IR(33193, 23)
  "GroupFMaxNonUniformAMD\0" // IR(33216, 23)
  "GroupUMaxNonUniformAMD\0" // IR(33239, 23)
  "GroupSMaxNonUniformAMD\0" // IR(33262, 23)
  "FragmentMaskFetchAMD\0" // IR(33285, 21)
  "FragmentFetchAMD\0" // IR(33306, 17)
  "ReadClockKHR\0" // IR(33323, 13)
  "AllocateNodePayloadsAMDX\0" // IR(33336, 25)
  "EnqueueNodePayloadsAMDX\0" // IR(33361, 24)
  "TypeNodePayloadArrayAMDX\0" // IR(33385, 25)
  "FinishWritingNodePayloadAMDX\0" // IR(33410, 29)
  "NodePayloadArrayLengthAMDX\0" // IR(33439, 27)
  "IsNodePayloadValidAMDX\0" // IR(33466, 23)
  "ConstantStringAMDX\0" // IR(33489, 19)
  "SpecConstantStringAMDX\0" // IR(33508, 23)
  "GroupNonUniformQuadAllKHR\0" // IR(33531, 26)
  "GroupNonUniformQuadAnyKHR\0" // IR(33557, 26)
  "HitObjectRecordHitMotionNV\0" // IR(33583, 27)
  "HitObjectRecordHitWithIndexMotionNV\0" // IR(33610, 36)
  "HitObjectRecordMissMotionNV\0" // IR(33646, 28)
  "HitObjectGetWorldToObjectNV\0" // IR(33674, 28)
  "HitObjectGetObjectToWorldNV\0" // IR(33702, 28)
  "HitObjectGetObjectRayDirectionNV\0" // IR(33730, 33)
  "HitObjectGetObjectRayOriginNV\0" // IR(33763, 30)
  "HitObjectTraceRayMotionNV\0" // IR(33793, 26)
  "HitObjectGetShaderRecordBufferHandleNV\0" // IR(33819, 39)
  "HitObjectGetShaderBindingTableRecordIndexNV\0" // IR(33858, 44)
  "HitObjectRecordEmptyNV\0" // IR(33902, 23)
  "HitObjectTraceRayNV\0" // IR(33925, 20)
  "HitObjectRecordHitNV\0" // IR(33945, 21)
  "HitObjectRecordHitWithIndexNV\0" // IR(33966, 30)
  "HitObjectRecordMissNV\0" // IR(33996, 22)
  "HitObjectExecuteShaderNV\0" // IR(34018, 25)
  "HitObjectGetCurrentTimeNV\0" // IR(34043, 26)
  "HitObjectGetAttributesNV\0" // IR(34069, 25)
  "HitObjectGetHitKindNV\0" // IR(34094, 22)
  "HitObjectGetPrimitiveIndexNV\0" // IR(34116, 29)
  "HitObjectGetGeometryIndexNV\0" // IR(34145, 28)
  "HitObjectGetInstanceIdNV\0" // IR(34173, 25)
  "HitObjectGetInstanceCustomIndexNV\0" // IR(34198, 34)
  "HitObjectGetWorldRayDirectionNV\0" // IR(34232, 32)
  "HitObjectGetWorldRayOriginNV\0" // IR(34264, 29)
  "HitObjectGetRayTMaxNV\0" // IR(34293, 22)
  "HitObjectGetRayTMinNV\0" // IR(34315, 22)
  "HitObjectIsEmptyNV\0" // IR(34337, 19)
  "HitObjectIsHitNV\0" // IR(34356, 17)
  "HitObjectIsMissNV\0" // IR(34373, 18)
  "ReorderThreadWithHitObjectNV\0" // IR(34391, 29)
  "ReorderThreadWithHintNV\0" // IR(34420, 24)
  "TypeHitObjectNV\0" // IR(34444, 16)
  "ImageSampleFootprintNV\0" // IR(34460, 23)
  "TypeCooperativeVectorNV\0" // IR(34483, 24)
  "CooperativeVectorMatrixMulNV\0" // IR(34507, 29)
  "CooperativeVectorOuterProductAccumulateNV\0" // IR(34536, 42)
  "CooperativeVectorReduceSumAccumulateNV\0" // IR(34578, 39)
  "CooperativeVectorMatrixMulAddNV\0" // IR(34617, 32)
  "CooperativeMatrixConvertNV\0" // IR(34649, 27)
  "EmitMeshTasksEXT\0" // IR(34676, 17)
  "SetMeshOutputsEXT\0" // IR(34693, 18)
  "GroupNonUniformPartitionNV\0" // IR(34711, 27)
  "WritePackedPrimitiveIndices4x8NV\0" // IR(34738, 33)
  "FetchMicroTriangleVertexPositionNV\0" // IR(34771, 35)
  "FetchMicroTriangleVertexBarycentricNV\0" // IR(34806, 38)
  "CooperativeVectorLoadNV\0" // IR(34844, 24)
  "CooperativeVectorStoreNV\0" // IR(34868, 25)
  "ReportIntersectionKHR\0" // IR(34893, 22)
  "ReportIntersectionNV\0" // IR(34915, 21)
  "IgnoreIntersectionNV\0" // IR(34936, 21)
  "TerminateRayNV\0" // IR(34957, 15)
  "TraceNV\0" // IR(34972, 8)
  "TraceMotionNV\0" // IR(34980, 14)
  "TraceRayMotionNV\0" // IR(34994, 17)
  "RayQueryGetIntersectionTriangleVertexPositionsKHR\0" // IR(35011, 50)
  "TypeAccelerationStructureKHR\0" // IR(35061, 29)
  "TypeAccelerationStructureNV\0" // IR(35090, 28)
  "ExecuteCallableNV\0" // IR(35118, 18)
  "RayQueryGetIntersectionClusterIdNV\0" // IR(35136, 35)
  "RayQueryGetClusterIdNV\0" // IR(35171, 23)
  "HitObjectGetClusterIdNV\0" // IR(35194, 24)
  "TypeCooperativeMatrixNV\0" // IR(35218, 24)
  "CooperativeMatrixLoadNV\0" // IR(35242, 24)
  "CooperativeMatrixStoreNV\0" // IR(35266, 25)
  "CooperativeMatrixMulAddNV\0" // IR(35291, 26)
  "CooperativeMatrixLengthNV\0" // IR(35317, 26)
  "BeginInvocationInterlockEXT\0" // IR(35343, 28)
  "EndInvocationInterlockEXT\0" // IR(35371, 26)
  "SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE\0" // IR(35397, 43)
  "CooperativeMatrixReduceNV\0" // IR(35440, 26)
  "SPV_OPERAND_TYPE_MEMORY_ACCESS\0" // IR(35466, 31)
  "SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS\0" // IR(35497, 44)
  "CooperativeMatrixLoadTensorNV\0" // IR(35541, 30)
  "CooperativeMatrixStoreTensorNV\0" // IR(35571, 31)
  "CooperativeMatrixPerElementOpNV\0" // IR(35602, 32)
  "TypeTensorLayoutNV\0" // IR(35634, 19)
  "TypeTensorViewNV\0" // IR(35653, 17)
  "CreateTensorLayoutNV\0" // IR(35670, 21)
  "TensorLayoutSetDimensionNV\0" // IR(35691, 27)
  "TensorLayoutSetStrideNV\0" // IR(35718, 24)
  "TensorLayoutSliceNV\0" // IR(35742, 20)
  "TensorLayoutSetClampValueNV\0" // IR(35762, 28)
  "CreateTensorViewNV\0" // IR(35790, 19)
  "TensorViewSetDimensionNV\0" // IR(35809, 25)
  "TensorViewSetStrideNV\0" // IR(35834, 22)
  "IsHelperInvocationEXT\0" // IR(35856, 22)
  "TensorViewSetClipNV\0" // IR(35878, 20)
  "TensorLayoutSetBlockSizeNV\0" // IR(35898, 27)
  "CooperativeMatrixTransposeNV\0" // IR(35925, 29)
  "ConvertUToImageNV\0" // IR(35954, 18)
  "ConvertUToSamplerNV\0" // IR(35972, 20)
  "ConvertImageToUNV\0" // IR(35992, 18)
  "ConvertSamplerToUNV\0" // IR(36010, 20)
  "ConvertUToSampledImageNV\0" // IR(36030, 25)
  "ConvertSampledImageToUNV\0" // IR(36055, 25)
  "SamplerImageAddressingModeNV\0" // IR(36080, 29)
  "SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS\0" // IR(36109, 52)
  "RawAccessChainNV\0" // IR(36161, 17)
  "RayQueryGetIntersectionSpherePositionNV\0" // IR(36178, 40)
  "RayQueryGetIntersectionSphereRadiusNV\0" // IR(36218, 38)
  "RayQueryGetIntersectionLSSPositionsNV\0" // IR(36256, 38)
  "RayQueryGetIntersectionLSSRadiiNV\0" // IR(36294, 34)
  "RayQueryGetIntersectionLSSHitValueNV\0" // IR(36328, 37)
  "HitObjectGetSpherePositionNV\0" // IR(36365, 29)
  "HitObjectGetSphereRadiusNV\0" // IR(36394, 27)
  "HitObjectGetLSSPositionsNV\0" // IR(36421, 27)
  "HitObjectGetLSSRadiiNV\0" // IR(36448, 23)
  "HitObjectIsSphereHitNV\0" // IR(36471, 23)
  "HitObjectIsLSSHitNV\0" // IR(36494, 20)
  "RayQueryIsSphereHitNV\0" // IR(36514, 22)
  "RayQueryIsLSSHitNV\0" // IR(36536, 19)
  "SubgroupShuffleDownINTEL\0" // IR(36555, 25)
  "SubgroupShuffleUpINTEL\0" // IR(36580, 23)
  "SubgroupShuffleXorINTEL\0" // IR(36603, 24)
  "SubgroupBlockReadINTEL\0" // IR(36627, 23)
  "SubgroupBlockWriteINTEL\0" // IR(36650, 24)
  "SubgroupImageBlockReadINTEL\0" // IR(36674, 28)
  "SubgroupImageBlockWriteINTEL\0" // IR(36702, 29)
  "SubgroupImageMediaBlockReadINTEL\0" // IR(36731, 33)
  "SubgroupImageMediaBlockWriteINTEL\0" // IR(36764, 34)
  "UCountLeadingZerosINTEL\0" // IR(36798, 24)
  "UCountTrailingZerosINTEL\0" // IR(36822, 25)
  "AbsISubINTEL\0" // IR(36847, 13)
  "AbsUSubINTEL\0" // IR(36860, 13)
  "IAddSatINTEL\0" // IR(36873, 13)
  "UAddSatINTEL\0" // IR(36886, 13)
  "IAverageINTEL\0" // IR(36899, 14)
  "UAverageINTEL\0" // IR(36913, 14)
  "IAverageRoundedINTEL\0" // IR(36927, 21)
  "UAverageRoundedINTEL\0" // IR(36948, 21)
  "ISubSatINTEL\0" // IR(36969, 13)
  "USubSatINTEL\0" // IR(36982, 13)
  "IMul32x16INTEL\0" // IR(36995, 15)
  "UMul32x16INTEL\0" // IR(37010, 15)
  "ConstantFunctionPointerINTEL\0" // IR(37025, 29)
  "FunctionPointerCallINTEL\0" // IR(37054, 25)
  "AsmTargetINTEL\0" // IR(37079, 15)
  "AsmCallINTEL\0" // IR(37094, 13)
  "AtomicFMinEXT\0" // IR(37107, 14)
  "AtomicFMaxEXT\0" // IR(37121, 14)
  "AssumeTrueKHR\0" // IR(37135, 14)
  "ExpectKHR\0" // IR(37149, 10)
  "DecorateString\0" // IR(37159, 15)
  "DecorateStringGOOGLE\0" // IR(37174, 21)
  "MemberDecorateString\0" // IR(37195, 21)
  "MemberDecorateStringGOOGLE\0" // IR(37216, 27)
  "VmeImageINTEL\0" // IR(37243, 14)
  "TypeVmeImageINTEL\0" // IR(37257, 18)
  "TypeAvcImePayloadINTEL\0" // IR(37275, 23)
  "TypeAvcRefPayloadINTEL\0" // IR(37298, 23)
  "TypeAvcSicPayloadINTEL\0" // IR(37321, 23)
  "TypeAvcMcePayloadINTEL\0" // IR(37344, 23)
  "TypeAvcMceResultINTEL\0" // IR(37367, 22)
  "TypeAvcImeResultINTEL\0" // IR(37389, 22)
  "TypeAvcImeResultSingleReferenceStreamoutINTEL\0" // IR(37411, 46)
  "TypeAvcImeResultDualReferenceStreamoutINTEL\0" // IR(37457, 44)
  "TypeAvcImeSingleReferenceStreaminINTEL\0" // IR(37501, 39)
  "TypeAvcImeDualReferenceStreaminINTEL\0" // IR(37540, 37)
  "TypeAvcRefResultINTEL\0" // IR(37577, 22)
  "TypeAvcSicResultINTEL\0" // IR(37599, 22)
  "SubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL\0" // IR(37621, 60)
  "SubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL\0" // IR(37681, 53)
  "SubgroupAvcMceGetDefaultInterShapePenaltyINTEL\0" // IR(37734, 47)
  "SubgroupAvcMceSetInterShapePenaltyINTEL\0" // IR(37781, 40)
  "SubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL\0" // IR(37821, 51)
  "SubgroupAvcMceSetInterDirectionPenaltyINTEL\0" // IR(37872, 44)
  "SubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL\0" // IR(37916, 51)
  "SubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL\0" // IR(37967, 56)
  "SubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL\0" // IR(38023, 50)
  "SubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL\0" // IR(38073, 52)
  "SubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL\0" // IR(38125, 49)
  "SubgroupAvcMceSetMotionVectorCostFunctionINTEL\0" // IR(38174, 47)
  "SubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL\0" // IR(38221, 50)
  "SubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL\0" // IR(38271, 51)
  "SubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL\0" // IR(38322, 56)
  "SubgroupAvcMceSetAcOnlyHaarINTEL\0" // IR(38378, 33)
  "SubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL\0" // IR(38411, 52)
  "SubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL\0" // IR(38463, 61)
  "SubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL\0" // IR(38524, 61)
  "SubgroupAvcMceConvertToImePayloadINTEL\0" // IR(38585, 39)
  "SubgroupAvcMceConvertToImeResultINTEL\0" // IR(38624, 38)
  "SubgroupAvcMceConvertToRefPayloadINTEL\0" // IR(38662, 39)
  "SubgroupAvcMceConvertToRefResultINTEL\0" // IR(38701, 38)
  "SubgroupAvcMceConvertToSicPayloadINTEL\0" // IR(38739, 39)
  "SubgroupAvcMceConvertToSicResultINTEL\0" // IR(38778, 38)
  "SubgroupAvcMceGetMotionVectorsINTEL\0" // IR(38816, 36)
  "SubgroupAvcMceGetInterDistortionsINTEL\0" // IR(38852, 39)
  "SubgroupAvcMceGetBestInterDistortionsINTEL\0" // IR(38891, 43)
  "SubgroupAvcMceGetInterMajorShapeINTEL\0" // IR(38934, 38)
  "SubgroupAvcMceGetInterMinorShapeINTEL\0" // IR(38972, 38)
  "SubgroupAvcMceGetInterDirectionsINTEL\0" // IR(39010, 38)
  "SubgroupAvcMceGetInterMotionVectorCountINTEL\0" // IR(39048, 45)
  "SubgroupAvcMceGetInterReferenceIdsINTEL\0" // IR(39093, 40)
  "SubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL\0" // IR(39133, 62)
  "SubgroupAvcImeInitializeINTEL\0" // IR(39195, 30)
  "SubgroupAvcImeSetSingleReferenceINTEL\0" // IR(39225, 38)
  "SubgroupAvcImeSetDualReferenceINTEL\0" // IR(39263, 36)
  "SubgroupAvcImeRefWindowSizeINTEL\0" // IR(39299, 33)
  "SubgroupAvcImeAdjustRefOffsetINTEL\0" // IR(39332, 35)
  "SubgroupAvcImeConvertToMcePayloadINTEL\0" // IR(39367, 39)
  "SubgroupAvcImeSetMaxMotionVectorCountINTEL\0" // IR(39406, 43)
  "SubgroupAvcImeSetUnidirectionalMixDisableINTEL\0" // IR(39449, 47)
  "SubgroupAvcImeSetEarlySearchTerminationThresholdINTEL\0" // IR(39496, 54)
  "SubgroupAvcImeSetWeightedSadINTEL\0" // IR(39550, 34)
  "SubgroupAvcImeEvaluateWithSingleReferenceINTEL\0" // IR(39584, 47)
  "SubgroupAvcImeEvaluateWithDualReferenceINTEL\0" // IR(39631, 45)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL\0" // IR(39676, 55)
  "SubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL\0" // IR(39731, 53)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL\0" // IR(39784, 56)
  "SubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL\0" // IR(39840, 54)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL\0" // IR(39894, 58)
  "SubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL\0" // IR(39952, 56)
  "SubgroupAvcImeConvertToMceResultINTEL\0" // IR(40008, 38)
  "SubgroupAvcImeGetSingleReferenceStreaminINTEL\0" // IR(40046, 46)
  "SubgroupAvcImeGetDualReferenceStreaminINTEL\0" // IR(40092, 44)
  "SubgroupAvcImeStripSingleReferenceStreamoutINTEL\0" // IR(40136, 49)
  "SubgroupAvcImeStripDualReferenceStreamoutINTEL\0" // IR(40185, 47)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL\0" // IR(40232, 70)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL\0" // IR(40302, 68)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL\0" // IR(40370, 69)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL\0" // IR(40439, 68)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL\0" // IR(40507, 66)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL\0" // IR(40573, 67)
  "SubgroupAvcImeGetBorderReachedINTEL\0" // IR(40640, 36)
  "SubgroupAvcImeGetTruncatedSearchIndicationINTEL\0" // IR(40676, 48)
  "SubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL\0" // IR(40724, 59)
  "SubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL\0" // IR(40783, 58)
  "SubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL\0" // IR(40841, 56)
  "SubgroupAvcFmeInitializeINTEL\0" // IR(40897, 30)
  "SubgroupAvcBmeInitializeINTEL\0" // IR(40927, 30)
  "SubgroupAvcRefConvertToMcePayloadINTEL\0" // IR(40957, 39)
  "SubgroupAvcRefSetBidirectionalMixDisableINTEL\0" // IR(40996, 46)
  "SubgroupAvcRefSetBilinearFilterEnableINTEL\0" // IR(41042, 43)
  "SubgroupAvcRefEvaluateWithSingleReferenceINTEL\0" // IR(41085, 47)
  "SubgroupAvcRefEvaluateWithDualReferenceINTEL\0" // IR(41132, 45)
  "SubgroupAvcRefEvaluateWithMultiReferenceINTEL\0" // IR(41177, 46)
  "SubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL\0" // IR(41223, 56)
  "SubgroupAvcRefConvertToMceResultINTEL\0" // IR(41279, 38)
  "SubgroupAvcSicInitializeINTEL\0" // IR(41317, 30)
  "SubgroupAvcSicConfigureSkcINTEL\0" // IR(41347, 32)
  "SubgroupAvcSicConfigureIpeLumaINTEL\0" // IR(41379, 36)
  "SubgroupAvcSicConfigureIpeLumaChromaINTEL\0" // IR(41415, 42)
  "SubgroupAvcSicGetMotionVectorMaskINTEL\0" // IR(41457, 39)
  "SubgroupAvcSicConvertToMcePayloadINTEL\0" // IR(41496, 39)
  "SubgroupAvcSicSetIntraLumaShapePenaltyINTEL\0" // IR(41535, 44)
  "SubgroupAvcSicSetIntraLumaModeCostFunctionINTEL\0" // IR(41579, 48)
  "SubgroupAvcSicSetIntraChromaModeCostFunctionINTEL\0" // IR(41627, 50)
  "SubgroupAvcSicSetBilinearFilterEnableINTEL\0" // IR(41677, 43)
  "SubgroupAvcSicSetSkcForwardTransformEnableINTEL\0" // IR(41720, 48)
  "SubgroupAvcSicSetBlockBasedRawSkipSadINTEL\0" // IR(41768, 43)
  "SubgroupAvcSicEvaluateIpeINTEL\0" // IR(41811, 31)
  "SubgroupAvcSicEvaluateWithSingleReferenceINTEL\0" // IR(41842, 47)
  "SubgroupAvcSicEvaluateWithDualReferenceINTEL\0" // IR(41889, 45)
  "SubgroupAvcSicEvaluateWithMultiReferenceINTEL\0" // IR(41934, 46)
  "SubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL\0" // IR(41980, 56)
  "SubgroupAvcSicConvertToMceResultINTEL\0" // IR(42036, 38)
  "SubgroupAvcSicGetIpeLumaShapeINTEL\0" // IR(42074, 35)
  "SubgroupAvcSicGetBestIpeLumaDistortionINTEL\0" // IR(42109, 44)
  "SubgroupAvcSicGetBestIpeChromaDistortionINTEL\0" // IR(42153, 46)
  "SubgroupAvcSicGetPackedIpeLumaModesINTEL\0" // IR(42199, 41)
  "SubgroupAvcSicGetIpeChromaModeINTEL\0" // IR(42240, 36)
  "SubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL\0" // IR(42276, 50)
  "SubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL\0" // IR(42326, 48)
  "SubgroupAvcSicGetInterRawSadsINTEL\0" // IR(42374, 35)
  "SaveMemoryINTEL\0" // IR(42409, 16)
  "RestoreMemoryINTEL\0" // IR(42425, 19)
  "ArbitraryFloatSinCosPiINTEL\0" // IR(42444, 28)
  "ArbitraryFloatCastINTEL\0" // IR(42472, 24)
  "ArbitraryFloatCastFromIntINTEL\0" // IR(42496, 31)
  "ArbitraryFloatCastToIntINTEL\0" // IR(42527, 29)
  "ArbitraryFloatAddINTEL\0" // IR(42556, 23)
  "ArbitraryFloatSubINTEL\0" // IR(42579, 23)
  "ArbitraryFloatMulINTEL\0" // IR(42602, 23)
  "ArbitraryFloatDivINTEL\0" // IR(42625, 23)
  "ArbitraryFloatGTINTEL\0" // IR(42648, 22)
  "ArbitraryFloatGEINTEL\0" // IR(42670, 22)
  "ArbitraryFloatLTINTEL\0" // IR(42692, 22)
  "ArbitraryFloatLEINTEL\0" // IR(42714, 22)
  "ArbitraryFloatEQINTEL\0" // IR(42736, 22)
  "ArbitraryFloatRecipINTEL\0" // IR(42758, 25)
  "ArbitraryFloatRSqrtINTEL\0" // IR(42783, 25)
  "ArbitraryFloatCbrtINTEL\0" // IR(42808, 24)
  "ArbitraryFloatHypotINTEL\0" // IR(42832, 25)
  "ArbitraryFloatSqrtINTEL\0" // IR(42857, 24)
  "ArbitraryFloatLogINTEL\0" // IR(42881, 23)
  "ArbitraryFloatLog2INTEL\0" // IR(42904, 24)
  "ArbitraryFloatLog10INTEL\0" // IR(42928, 25)
  "ArbitraryFloatLog1pINTEL\0" // IR(42953, 25)
  "ArbitraryFloatExpINTEL\0" // IR(42978, 23)
  "ArbitraryFloatExp2INTEL\0" // IR(43001, 24)
  "ArbitraryFloatExp10INTEL\0" // IR(43025, 25)
  "ArbitraryFloatExpm1INTEL\0" // IR(43050, 25)
  "ArbitraryFloatSinINTEL\0" // IR(43075, 23)
  "ArbitraryFloatCosINTEL\0" // IR(43098, 23)
  "ArbitraryFloatSinCosINTEL\0" // IR(43121, 26)
  "ArbitraryFloatSinPiINTEL\0" // IR(43147, 25)
  "ArbitraryFloatCosPiINTEL\0" // IR(43172, 25)
  "ArbitraryFloatASinINTEL\0" // IR(43197, 24)
  "ArbitraryFloatASinPiINTEL\0" // IR(43221, 26)
  "ArbitraryFloatACosINTEL\0" // IR(43247, 24)
  "ArbitraryFloatACosPiINTEL\0" // IR(43271, 26)
  "ArbitraryFloatATanINTEL\0" // IR(43297, 24)
  "ArbitraryFloatATanPiINTEL\0" // IR(43321, 26)
  "ArbitraryFloatATan2INTEL\0" // IR(43347, 25)
  "ArbitraryFloatPowINTEL\0" // IR(43372, 23)
  "ArbitraryFloatPowRINTEL\0" // IR(43395, 24)
  "ArbitraryFloatPowNINTEL\0" // IR(43419, 24)
  "LoopControlINTEL\0" // IR(43443, 17)
  "AliasDomainDeclINTEL\0" // IR(43460, 21)
  "AliasScopeDeclINTEL\0" // IR(43481, 20)
  "AliasScopeListDeclINTEL\0" // IR(43501, 24)
  "FixedSqrtINTEL\0" // IR(43525, 15)
  "FixedRecipINTEL\0" // IR(43540, 16)
  "FixedRsqrtINTEL\0" // IR(43556, 16)
  "FixedSinINTEL\0" // IR(43572, 14)
  "FixedCosINTEL\0" // IR(43586, 14)
  "FixedSinCosINTEL\0" // IR(43600, 17)
  "FixedSinPiINTEL\0" // IR(43617, 16)
  "FixedCosPiINTEL\0" // IR(43633, 16)
  "FixedSinCosPiINTEL\0" // IR(43649, 19)
  "FixedLogINTEL\0" // IR(43668, 14)
  "FixedExpINTEL\0" // IR(43682, 14)
  "PtrCastToCrossWorkgroupINTEL\0" // IR(43696, 29)
  "CrossWorkgroupCastToPtrINTEL\0" // IR(43725, 29)
  "ReadPipeBlockingINTEL\0" // IR(43754, 22)
  "WritePipeBlockingINTEL\0" // IR(43776, 23)
  "RayQueryGetRayTMinKHR\0" // IR(43799, 22)
  "RayQueryGetRayFlagsKHR\0" // IR(43821, 23)
  "RayQueryGetIntersectionTKHR\0" // IR(43844, 28)
  "RayQueryGetIntersectionInstanceCustomIndexKHR\0" // IR(43872, 46)
  "RayQueryGetIntersectionInstanceIdKHR\0" // IR(43918, 37)
  "RayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR\0" // IR(43955, 65)
  "RayQueryGetIntersectionGeometryIndexKHR\0" // IR(44020, 40)
  "RayQueryGetIntersectionPrimitiveIndexKHR\0" // IR(44060, 41)
  "RayQueryGetIntersectionBarycentricsKHR\0" // IR(44101, 39)
  "RayQueryGetIntersectionFrontFaceKHR\0" // IR(44140, 36)
  "RayQueryGetIntersectionCandidateAABBOpaqueKHR\0" // IR(44176, 46)
  "RayQueryGetIntersectionObjectRayDirectionKHR\0" // IR(44222, 45)
  "RayQueryGetIntersectionObjectRayOriginKHR\0" // IR(44267, 42)
  "RayQueryGetWorldRayDirectionKHR\0" // IR(44309, 32)
  "RayQueryGetWorldRayOriginKHR\0" // IR(44341, 29)
  "RayQueryGetIntersectionObjectToWorldKHR\0" // IR(44370, 40)
  "RayQueryGetIntersectionWorldToObjectKHR\0" // IR(44410, 40)
  "AtomicFAddEXT\0" // IR(44450, 14)
  "TypeBufferSurfaceINTEL\0" // IR(44464, 23)
  "TypeStructContinuedINTEL\0" // IR(44487, 25)
  "ConstantCompositeContinuedINTEL\0" // IR(44512, 32)
  "SpecConstantCompositeContinuedINTEL\0" // IR(44544, 36)
  "CompositeConstructContinuedINTEL\0" // IR(44580, 33)
  "ConvertFToBF16INTEL\0" // IR(44613, 20)
  "ConvertBF16ToFINTEL\0" // IR(44633, 20)
  "ControlBarrierArriveINTEL\0" // IR(44653, 26)
  "ControlBarrierWaitINTEL\0" // IR(44679, 24)
  "TaskSequenceCreateINTEL\0" // IR(44703, 24)
  "TaskSequenceAsyncINTEL\0" // IR(44727, 23)
  "TaskSequenceGetINTEL\0" // IR(44750, 21)
  "TaskSequenceReleaseINTEL\0" // IR(44771, 25)
  "TypeTaskSequenceINTEL\0" // IR(44796, 22)
  "SubgroupBlockPrefetchINTEL\0" // IR(44818, 27)
  "Subgroup2DBlockLoadINTEL\0" // IR(44845, 25)
  "Subgroup2DBlockLoadTransformINTEL\0" // IR(44870, 34)
  "Subgroup2DBlockLoadTransposeINTEL\0" // IR(44904, 34)
  "Subgroup2DBlockPrefetchINTEL\0" // IR(44938, 29)
  "Subgroup2DBlockStoreINTEL\0" // IR(44967, 26)
  "SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS\0" // IR(44993, 62)
  "BitwiseFunctionINTEL\0" // IR(45055, 21)
  "ConditionalExtensionINTEL\0" // IR(45076, 26)
  "ConditionalEntryPointINTEL\0" // IR(45102, 27)
  "ConditionalCapabilityINTEL\0" // IR(45129, 27)
  "SpecConstantTargetINTEL\0" // IR(45156, 24)
  "SpecConstantArchitectureINTEL\0" // IR(45180, 30)
  "SPV_OPERAND_TYPE_VARIABLE_CAPABILITY\0" // IR(45210, 37)
  "SpecConstantCapabilitiesINTEL\0" // IR(45247, 30)
  "ConditionalCopyObjectINTEL\0" // IR(45277, 27)
  "GroupIMulKHR\0" // IR(45304, 13)
  "GroupFMulKHR\0" // IR(45317, 13)
  "GroupBitwiseAndKHR\0" // IR(45330, 19)
  "GroupBitwiseOrKHR\0" // IR(45349, 18)
  "GroupBitwiseXorKHR\0" // IR(45367, 19)
  "GroupLogicalAndKHR\0" // IR(45386, 19)
  "GroupLogicalOrKHR\0" // IR(45405, 18)
  "GroupLogicalXorKHR\0" // IR(45423, 19)
  "RoundFToTF32INTEL\0" // IR(45442, 18)
  "MaskedGatherINTEL\0" // IR(45460, 18)
  "MaskedScatterINTEL\0" // IR(45478, 19)
  "ConvertHandleToImageINTEL\0" // IR(45497, 26)
  "ConvertHandleToSamplerINTEL\0" // IR(45523, 28)
  "ConvertHandleToSampledImageINTEL\0" // IR(45551, 33)
  "DebugInfoNone\0" // IR(45584, 14)
  "DebugCompilationUnit\0" // IR(45598, 21)
  "SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING\0" // IR(45619, 52)
  "DebugTypeBasic\0" // IR(45671, 15)
  "SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS\0" // IR(45686, 34)
  "DebugTypePointer\0" // IR(45720, 17)
  "SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER\0" // IR(45737, 38)
  "DebugTypeQualifier\0" // IR(45775, 19)
  "DebugTypeArray\0" // IR(45794, 15)
  "DebugTypeVector\0" // IR(45809, 16)
  "DebugTypedef\0" // IR(45825, 13)
  "DebugTypeFunction\0" // IR(45838, 18)
  "DebugTypeEnum\0" // IR(45856, 14)
  "SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE\0" // IR(45870, 38)
  "DebugTypeComposite\0" // IR(45908, 19)
  "DebugTypeMember\0" // IR(45927, 16)
  "DebugTypeInheritance\0" // IR(45943, 21)
  "DebugTypePtrToMember\0" // IR(45964, 21)
  "DebugTypeTemplate\0" // IR(45985, 18)
  "DebugTypeTemplateParameter\0" // IR(46003, 27)
  "DebugTypeTemplateTemplateParameter\0" // IR(46030, 35)
  "DebugTypeTemplateParameterPack\0" // IR(46065, 31)
  "DebugGlobalVariable\0" // IR(46096, 20)
  "DebugFunctionDeclaration\0" // IR(46116, 25)
  "DebugFunction\0" // IR(46141, 14)
  "DebugLexicalBlock\0" // IR(46155, 18)
  "DebugLexicalBlockDiscriminator\0" // IR(46173, 31)
  "DebugScope\0" // IR(46204, 11)
  "DebugNoScope\0" // IR(46215, 13)
  "DebugInlinedAt\0" // IR(46228, 15)
  "SPV_OPERAND_TYPE_OPTIONAL_LITERAL_INTEGER\0" // IR(46243, 42)
  "DebugLocalVariable\0" // IR(46285, 19)
  "DebugInlinedVariable\0" // IR(46304, 21)
  "DebugDeclare\0" // IR(46325, 13)
  "DebugValue\0" // IR(46338, 11)
  "SPV_OPERAND_TYPE_DEBUG_OPERATION\0" // IR(46349, 33)
  "DebugOperation\0" // IR(46382, 15)
  "DebugExpression\0" // IR(46397, 16)
  "DebugMacroDef\0" // IR(46413, 14)
  "DebugMacroUndef\0" // IR(46427, 16)
  "Round\0" // IR(46443, 6)
  "RoundEven\0" // IR(46449, 10)
  "Trunc\0" // IR(46459, 6)
  "FAbs\0" // IR(46465, 5)
  "SAbs\0" // IR(46470, 5)
  "FSign\0" // IR(46475, 6)
  "SSign\0" // IR(46481, 6)
  "Floor\0" // IR(46487, 6)
  "Ceil\0" // IR(46493, 5)
  "Fract\0" // IR(46498, 6)
  "Radians\0" // IR(46504, 8)
  "Degrees\0" // IR(46512, 8)
  "Sin\0" // IR(46520, 4)
  "Cos\0" // IR(46524, 4)
  "Tan\0" // IR(46528, 4)
  "Asin\0" // IR(46532, 5)
  "Acos\0" // IR(46537, 5)
  "Atan\0" // IR(46542, 5)
  "Sinh\0" // IR(46547, 5)
  "Cosh\0" // IR(46552, 5)
  "Tanh\0" // IR(46557, 5)
  "Asinh\0" // IR(46562, 6)
  "Acosh\0" // IR(46568, 6)
  "Atanh\0" // IR(46574, 6)
  "Atan2\0" // IR(46580, 6)
  "Pow\0" // IR(46586, 4)
  "Exp\0" // IR(46590, 4)
  "Log\0" // IR(46594, 4)
  "Exp2\0" // IR(46598, 5)
  "Log2\0" // IR(46603, 5)
  "Sqrt\0" // IR(46608, 5)
  "InverseSqrt\0" // IR(46613, 12)
  "Determinant\0" // IR(46625, 12)
  "MatrixInverse\0" // IR(46637, 14)
  "Modf\0" // IR(46651, 5)
  "ModfStruct\0" // IR(46656, 11)
  "FMin\0" // IR(46667, 5)
  "UMin\0" // IR(46672, 5)
  "SMin\0" // IR(46677, 5)
  "FMax\0" // IR(46682, 5)
  "UMax\0" // IR(46687, 5)
  "SMax\0" // IR(46692, 5)
  "FClamp\0" // IR(46697, 7)
  "UClamp\0" // IR(46704, 7)
  "SClamp\0" // IR(46711, 7)
  "FMix\0" // IR(46718, 5)
  "IMix\0" // IR(46723, 5)
  "Step\0" // IR(46728, 5)
  "SmoothStep\0" // IR(46733, 11)
  "Fma\0" // IR(46744, 4)
  "Frexp\0" // IR(46748, 6)
  "FrexpStruct\0" // IR(46754, 12)
  "Ldexp\0" // IR(46766, 6)
  "PackSnorm4x8\0" // IR(46772, 13)
  "PackUnorm4x8\0" // IR(46785, 13)
  "PackSnorm2x16\0" // IR(46798, 14)
  "PackUnorm2x16\0" // IR(46812, 14)
  "PackHalf2x16\0" // IR(46826, 13)
  "PackDouble2x32\0" // IR(46839, 15)
  "UnpackSnorm2x16\0" // IR(46854, 16)
  "UnpackUnorm2x16\0" // IR(46870, 16)
  "UnpackHalf2x16\0" // IR(46886, 15)
  "UnpackSnorm4x8\0" // IR(46901, 15)
  "UnpackUnorm4x8\0" // IR(46916, 15)
  "UnpackDouble2x32\0" // IR(46931, 17)
  "Length\0" // IR(46948, 7)
  "Distance\0" // IR(46955, 9)
  "Cross\0" // IR(46964, 6)
  "Normalize\0" // IR(46970, 10)
  "FaceForward\0" // IR(46980, 12)
  "Reflect\0" // IR(46992, 8)
  "Refract\0" // IR(47000, 8)
  "FindILsb\0" // IR(47008, 9)
  "FindSMsb\0" // IR(47017, 9)
  "FindUMsb\0" // IR(47026, 9)
  "InterpolateAtCentroid\0" // IR(47035, 22)
  "InterpolateAtSample\0" // IR(47057, 20)
  "InterpolateAtOffset\0" // IR(47077, 20)
  "NMin\0" // IR(47097, 5)
  "NMax\0" // IR(47102, 5)
  "NClamp\0" // IR(47107, 7)
  "ArgumentInfo\0" // IR(47114, 13)
  "ArgumentStorageBuffer\0" // IR(47127, 22)
  "ArgumentUniform\0" // IR(47149, 16)
  "ArgumentPodStorageBuffer\0" // IR(47165, 25)
  "ArgumentPodUniform\0" // IR(47190, 19)
  "ArgumentPodPushConstant\0" // IR(47209, 24)
  "ArgumentSampledImage\0" // IR(47233, 21)
  "ArgumentStorageImage\0" // IR(47254, 21)
  "ArgumentSampler\0" // IR(47275, 16)
  "ArgumentWorkgroup\0" // IR(47291, 18)
  "SpecConstantWorkgroupSize\0" // IR(47309, 26)
  "SpecConstantGlobalOffset\0" // IR(47335, 25)
  "SpecConstantWorkDim\0" // IR(47360, 20)
  "PushConstantGlobalOffset\0" // IR(47380, 25)
  "PushConstantEnqueuedLocalSize\0" // IR(47405, 30)
  "PushConstantGlobalSize\0" // IR(47435, 23)
  "PushConstantRegionOffset\0" // IR(47458, 25)
  "PushConstantNumWorkgroups\0" // IR(47483, 26)
  "PushConstantRegionGroupOffset\0" // IR(47509, 30)
  "ConstantDataStorageBuffer\0" // IR(47539, 26)
  "ConstantDataUniform\0" // IR(47565, 20)
  "PropertyRequiredWorkgroupSize\0" // IR(47585, 30)
  "SpecConstantSubgroupMaxSize\0" // IR(47615, 28)
  "ArgumentPointerPushConstant\0" // IR(47643, 28)
  "ArgumentPointerUniform\0" // IR(47671, 23)
  "ProgramScopeVariablesStorageBuffer\0" // IR(47694, 35)
  "ProgramScopeVariablePointerRelocation\0" // IR(47729, 38)
  "ImageArgumentInfoChannelOrderPushConstant\0" // IR(47767, 42)
  "ImageArgumentInfoChannelDataTypePushConstant\0" // IR(47809, 45)
  "ImageArgumentInfoChannelOrderUniform\0" // IR(47854, 37)
  "ImageArgumentInfoChannelDataTypeUniform\0" // IR(47891, 40)
  "ArgumentStorageTexelBuffer\0" // IR(47931, 27)
  "ArgumentUniformTexelBuffer\0" // IR(47958, 27)
  "ConstantDataPointerPushConstant\0" // IR(47985, 32)
  "ProgramScopeVariablePointerPushConstant\0" // IR(48017, 40)
  "PrintfInfo\0" // IR(48057, 11)
  "PrintfBufferStorageBuffer\0" // IR(48068, 26)
  "PrintfBufferPointerPushConstant\0" // IR(48094, 32)
  "NormalizedSamplerMaskPushConstant\0" // IR(48126, 34)
  "WorkgroupVariableSize\0" // IR(48160, 22)
  "DebugImportedEntity\0" // IR(48182, 20)
  "DebugSource\0" // IR(48202, 12)
  "DebugFunctionDefinition\0" // IR(48214, 24)
  "DebugSourceContinued\0" // IR(48238, 21)
  "DebugLine\0" // IR(48259, 10)
  "DebugNoLine\0" // IR(48269, 12)
  "DebugBuildIdentifier\0" // IR(48281, 21)
  "DebugStoragePath\0" // IR(48302, 17)
  "DebugEntryPoint\0" // IR(48319, 16)
  "DebugTypeMatrix\0" // IR(48335, 16)
  "Configuration\0" // IR(48351, 14)
  "StartCounter\0" // IR(48365, 13)
  "StopCounter\0" // IR(48378, 12)
  "PushConstants\0" // IR(48390, 14)
  "SpecializationMapEntry\0" // IR(48404, 23)
  "DescriptorSetBuffer\0" // IR(48427, 20)
  "DescriptorSetImage\0" // IR(48447, 19)
  "DescriptorSetSampler\0" // IR(48466, 21)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING\0" // IR(48487, 63)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS\0" // IR(48550, 45)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER\0" // IR(48595, 49)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE\0" // IR(48644, 49)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION\0" // IR(48693, 44)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY\0" // IR(48737, 50)
  "DebugModuleINTEL\0" // IR(48787, 17)
  "acos\0" // IR(48804, 5)
  "acosh\0" // IR(48809, 6)
  "acospi\0" // IR(48815, 7)
  "asin\0" // IR(48822, 5)
  "asinh\0" // IR(48827, 6)
  "asinpi\0" // IR(48833, 7)
  "atan\0" // IR(48840, 5)
  "atan2\0" // IR(48845, 6)
  "atanh\0" // IR(48851, 6)
  "atanpi\0" // IR(48857, 7)
  "atan2pi\0" // IR(48864, 8)
  "cbrt\0" // IR(48872, 5)
  "ceil\0" // IR(48877, 5)
  "copysign\0" // IR(48882, 9)
  "cos\0" // IR(48891, 4)
  "cosh\0" // IR(48895, 5)
  "cospi\0" // IR(48900, 6)
  "erfc\0" // IR(48906, 5)
  "erf\0" // IR(48911, 4)
  "exp\0" // IR(48915, 4)
  "exp2\0" // IR(48919, 5)
  "exp10\0" // IR(48924, 6)
  "expm1\0" // IR(48930, 6)
  "fabs\0" // IR(48936, 5)
  "fdim\0" // IR(48941, 5)
  "floor\0" // IR(48946, 6)
  "fma\0" // IR(48952, 4)
  "fmax\0" // IR(48956, 5)
  "fmin\0" // IR(48961, 5)
  "fmod\0" // IR(48966, 5)
  "fract\0" // IR(48971, 6)
  "frexp\0" // IR(48977, 6)
  "hypot\0" // IR(48983, 6)
  "ilogb\0" // IR(48989, 6)
  "ldexp\0" // IR(48995, 6)
  "lgamma\0" // IR(49001, 7)
  "lgamma_r\0" // IR(49008, 9)
  "log\0" // IR(49017, 4)
  "log2\0" // IR(49021, 5)
  "log10\0" // IR(49026, 6)
  "log1p\0" // IR(49032, 6)
  "logb\0" // IR(49038, 5)
  "mad\0" // IR(49043, 4)
  "maxmag\0" // IR(49047, 7)
  "minmag\0" // IR(49054, 7)
  "modf\0" // IR(49061, 5)
  "nan\0" // IR(49066, 4)
  "nextafter\0" // IR(49070, 10)
  "pow\0" // IR(49080, 4)
  "pown\0" // IR(49084, 5)
  "powr\0" // IR(49089, 5)
  "remainder\0" // IR(49094, 10)
  "remquo\0" // IR(49104, 7)
  "rint\0" // IR(49111, 5)
  "rootn\0" // IR(49116, 6)
  "round\0" // IR(49122, 6)
  "rsqrt\0" // IR(49128, 6)
  "sin\0" // IR(49134, 4)
  "sincos\0" // IR(49138, 7)
  "sinh\0" // IR(49145, 5)
  "sinpi\0" // IR(49150, 6)
  "sqrt\0" // IR(49156, 5)
  "tan\0" // IR(49161, 4)
  "tanh\0" // IR(49165, 5)
  "tanpi\0" // IR(49170, 6)
  "tgamma\0" // IR(49176, 7)
  "trunc\0" // IR(49183, 6)
  "half_cos\0" // IR(49189, 9)
  "half_divide\0" // IR(49198, 12)
  "half_exp\0" // IR(49210, 9)
  "half_exp2\0" // IR(49219, 10)
  "half_exp10\0" // IR(49229, 11)
  "half_log\0" // IR(49240, 9)
  "half_log2\0" // IR(49249, 10)
  "half_log10\0" // IR(49259, 11)
  "half_powr\0" // IR(49270, 10)
  "half_recip\0" // IR(49280, 11)
  "half_rsqrt\0" // IR(49291, 11)
  "half_sin\0" // IR(49302, 9)
  "half_sqrt\0" // IR(49311, 10)
  "half_tan\0" // IR(49321, 9)
  "native_cos\0" // IR(49330, 11)
  "native_divide\0" // IR(49341, 14)
  "native_exp\0" // IR(49355, 11)
  "native_exp2\0" // IR(49366, 12)
  "native_exp10\0" // IR(49378, 13)
  "native_log\0" // IR(49391, 11)
  "native_log2\0" // IR(49402, 12)
  "native_log10\0" // IR(49414, 13)
  "native_powr\0" // IR(49427, 12)
  "native_recip\0" // IR(49439, 13)
  "native_rsqrt\0" // IR(49452, 13)
  "native_sin\0" // IR(49465, 11)
  "native_sqrt\0" // IR(49476, 12)
  "native_tan\0" // IR(49488, 11)
  "fclamp\0" // IR(49499, 7)
  "degrees\0" // IR(49506, 8)
  "fmax_common\0" // IR(49514, 12)
  "fmin_common\0" // IR(49526, 12)
  "mix\0" // IR(49538, 4)
  "radians\0" // IR(49542, 8)
  "step\0" // IR(49550, 5)
  "smoothstep\0" // IR(49555, 11)
  "sign\0" // IR(49566, 5)
  "cross\0" // IR(49571, 6)
  "distance\0" // IR(49577, 9)
  "length\0" // IR(49586, 7)
  "normalize\0" // IR(49593, 10)
  "fast_distance\0" // IR(49603, 14)
  "fast_length\0" // IR(49617, 12)
  "fast_normalize\0" // IR(49629, 15)
  "s_abs\0" // IR(49644, 6)
  "s_abs_diff\0" // IR(49650, 11)
  "s_add_sat\0" // IR(49661, 10)
  "u_add_sat\0" // IR(49671, 10)
  "s_hadd\0" // IR(49681, 7)
  "u_hadd\0" // IR(49688, 7)
  "s_rhadd\0" // IR(49695, 8)
  "u_rhadd\0" // IR(49703, 8)
  "s_clamp\0" // IR(49711, 8)
  "u_clamp\0" // IR(49719, 8)
  "clz\0" // IR(49727, 4)
  "ctz\0" // IR(49731, 4)
  "s_mad_hi\0" // IR(49735, 9)
  "u_mad_sat\0" // IR(49744, 10)
  "s_mad_sat\0" // IR(49754, 10)
  "s_max\0" // IR(49764, 6)
  "u_max\0" // IR(49770, 6)
  "s_min\0" // IR(49776, 6)
  "u_min\0" // IR(49782, 6)
  "s_mul_hi\0" // IR(49788, 9)
  "rotate\0" // IR(49797, 7)
  "s_sub_sat\0" // IR(49804, 10)
  "u_sub_sat\0" // IR(49814, 10)
  "u_upsample\0" // IR(49824, 11)
  "s_upsample\0" // IR(49835, 11)
  "popcount\0" // IR(49846, 9)
  "s_mad24\0" // IR(49855, 8)
  "u_mad24\0" // IR(49863, 8)
  "s_mul24\0" // IR(49871, 8)
  "u_mul24\0" // IR(49879, 8)
  "vloadn\0" // IR(49887, 7)
  "vstoren\0" // IR(49894, 8)
  "vload_half\0" // IR(49902, 11)
  "vload_halfn\0" // IR(49913, 12)
  "vstore_half\0" // IR(49925, 12)
  "vstore_half_r\0" // IR(49937, 14)
  "vstore_halfn\0" // IR(49951, 13)
  "vstore_halfn_r\0" // IR(49964, 15)
  "vloada_halfn\0" // IR(49979, 13)
  "vstorea_halfn\0" // IR(49992, 14)
  "vstorea_halfn_r\0" // IR(50006, 16)
  "shuffle\0" // IR(50022, 8)
  "shuffle2\0" // IR(50030, 9)
  "printf\0" // IR(50039, 7)
  "prefetch\0" // IR(50046, 9)
  "bitselect\0" // IR(50055, 10)
  "select\0" // IR(50065, 7)
  "u_abs\0" // IR(50072, 6)
  "u_abs_diff\0" // IR(50078, 11)
  "u_mul_hi\0" // IR(50089, 9)
  "u_mad_hi\0" // IR(50098, 9)
  "CubeFaceIndexAMD\0" // IR(50107, 17)
  "CubeFaceCoordAMD\0" // IR(50124, 17)
  "TimeAMD\0" // IR(50141, 8)
  "SwizzleInvocationsAMD\0" // IR(50149, 22)
  "SwizzleInvocationsMaskedAMD\0" // IR(50171, 28)
  "WriteInvocationAMD\0" // IR(50199, 19)
  "MbcntAMD\0" // IR(50218, 9)
  "InterpolateAtVertexAMD\0" // IR(50227, 23)
  "FMin3AMD\0" // IR(50250, 9)
  "UMin3AMD\0" // IR(50259, 9)
  "SMin3AMD\0" // IR(50268, 9)
  "FMax3AMD\0" // IR(50277, 9)
  "UMax3AMD\0" // IR(50286, 9)
  "SMax3AMD\0" // IR(50295, 9)
  "FMid3AMD\0" // IR(50304, 9)
  "UMid3AMD\0" // IR(50313, 9)
  "SMid3AMD\0" // IR(50322, 9)
;

// Array of IndexRanges, where each represents a string by referencing
// the kStrings table.
// This array contains all sequences of alias strings used in the grammar.
// This table is referenced by an IndexRange elsewhere, i.e. by the 'aliases'
// field of an instruction or operand description.
static const IndexRange kAliasSpans[] = {
  IR(4721, 27), // 0 PhysicalStorageBuffer64EXT
  IR(5632, 18), // 1 SubgroupEqMaskKHR
  IR(5687, 18), // 2 SubgroupGeMaskKHR
  IR(5720, 18), // 3 SubgroupGtMaskKHR
  IR(5753, 18), // 4 SubgroupLeMaskKHR
  IR(5786, 18), // 5 SubgroupLtMaskKHR
  IR(6644, 12), // 6 BaryCoordNV
  IR(6699, 19), // 7 BaryCoordNoPerspNV
  IR(6730, 15), // 8 FragmentSizeNV
  IR(6787, 22), // 9 InvocationsPerPixelNV
  IR(6915, 11), // 10 LaunchIdNV
  IR(6940, 13), // 11 LaunchSizeNV
  IR(6971, 17), // 12 WorldRayOriginNV
  IR(7009, 20), // 13 WorldRayDirectionNV
  IR(7048, 18), // 14 ObjectRayOriginNV
  IR(7088, 21), // 15 ObjectRayDirectionNV
  IR(7120, 10), // 16 RayTminNV
  IR(7141, 10), // 17 RayTmaxNV
  IR(7174, 22), // 18 InstanceCustomIndexNV
  IR(7213, 16), // 19 ObjectToWorldNV
  IR(7246, 16), // 20 WorldToObjectNV
  IR(7280, 10), // 21 HitKindNV
  IR(7511, 19), // 22 IncomingRayFlagsNV
  IR(9287, 28), // 23 StorageUniformBufferBlock16
  IR(9350, 17), // 24 StorageUniform16
  IR(10165, 27), // 25 ShaderViewportIndexLayerNV
  IR(10209, 22), // 26 FragmentBarycentricNV
  IR(10262, 30), // 27 ComputeDerivativeGroupQuadsNV
  IR(10292, 14), // 28 ShadingRateNV
  IR(10352, 20), // 29 ShaderNonUniformEXT
  IR(10395, 26), // 30 RuntimeDescriptorArrayEXT
  IR(10457, 39), // 31 InputAttachmentArrayDynamicIndexingEXT
  IR(10535, 42), // 32 UniformTexelBufferArrayDynamicIndexingEXT
  IR(10616, 42), // 33 StorageTexelBufferArrayDynamicIndexingEXT
  IR(10695, 40), // 34 UniformBufferArrayNonUniformIndexingEXT
  IR(10771, 39), // 35 SampledImageArrayNonUniformIndexingEXT
  IR(10847, 40), // 36 StorageBufferArrayNonUniformIndexingEXT
  IR(10923, 39), // 37 StorageImageArrayNonUniformIndexingEXT
  IR(11001, 42), // 38 InputAttachmentArrayNonUniformIndexingEXT
  IR(11085, 45), // 39 UniformTexelBufferArrayNonUniformIndexingEXT
  IR(11172, 45), // 40 StorageTexelBufferArrayNonUniformIndexingEXT
  IR(11235, 21), // 41 VulkanMemoryModelKHR
  IR(11285, 32), // 42 VulkanMemoryModelDeviceScopeKHR
  IR(11317, 34), // 43 PhysicalStorageBufferAddressesEXT
  IR(11383, 31), // 44 ComputeDerivativeGroupLinearNV
  IR(11587, 28), // 45 DemoteToHelperInvocationEXT
  IR(13057, 22), // 46 DotProductInputAllKHR
  IR(13101, 25), // 47 DotProductInput4x8BitKHR
  IR(13154, 31), // 48 DotProductInput4x8BitPackedKHR
  IR(13196, 14), // 49 DotProductKHR
  IR(13361, 13), // 50 OptNoneINTEL
  IR(16432, 15), // 51 PerPrimitiveNV
  IR(16480, 12), // 52 PerVertexNV
  IR(16503, 14), // 53 NonUniformEXT
  IR(16533, 19), // 54 RestrictPointerEXT
  IR(16567, 18), // 55 AliasedPointerEXT
  IR(16877, 24), // 56 HlslCounterBufferGOOGLE
  IR(16914, 19), // 57 HlslSemanticGOOGLE
  IR(19605, 14), // 58 OutputLinesNV
  IR(19639, 19), // 59 OutputPrimitivesNV
  IR(19682, 23), // 60 DerivativeGroupQuadsNV
  IR(19730, 24), // 61 DerivativeGroupLinearNV
  IR(19773, 18), // 62 OutputTrianglesNV
  IR(20521, 16), // 63 RayGenerationNV
  IR(20553, 15), // 64 IntersectionNV
  IR(20578, 9), // 65 AnyHitNV
  IR(20601, 13), // 66 ClosestHitNV
  IR(20622, 7), // 67 MissNV
  IR(20641, 11), // 68 CallableNV
  IR(20786, 23), // 69 AllowContractFastINTEL
  IR(20822, 18), // 70 AllowReassocINTEL
  IR(21276, 22), // 71 MakeTexelAvailableKHR
  IR(21315, 20), // 72 MakeTexelVisibleKHR
  IR(21351, 19), // 73 NonPrivateTexelKHR
  IR(21384, 17), // 74 VolatileTexelKHR
  IR(22761, 24), // 75 MakePointerAvailableKHR
  IR(22804, 22), // 76 MakePointerVisibleKHR
  IR(22844, 21), // 77 NonPrivatePointerKHR
  IR(22931, 10), // 78 VulkanKHR
  IR(14204, 5), // 79 None
  IR(23114, 16), // 80 OutputMemoryKHR
  IR(23144, 17), // 81 MakeAvailableKHR
  IR(23173, 15), // 82 MakeVisibleKHR
  IR(23249, 28), // 83 PackedVectorFormat4x8BitKHR
  IR(23564, 24), // 84 SkipBuiltinPrimitivesNV
  IR(24304, 15), // 85 QueueFamilyKHR
  IR(24675, 15), // 86 CallableDataNV
  IR(24714, 23), // 87 IncomingCallableDataNV
  IR(24751, 13), // 88 RayPayloadNV
  IR(24780, 15), // 89 HitAttributeNV
  IR(24817, 21), // 90 IncomingRayPayloadNV
  IR(24860, 21), // 91 ShaderRecordBufferNV
  IR(24903, 25), // 92 PhysicalStorageBufferEXT
  IR(32237, 8), // 93 SDotKHR
  IR(32250, 8), // 94 UDotKHR
  IR(32264, 9), // 95 SUDotKHR
  IR(32284, 14), // 96 SDotAccSatKHR
  IR(32309, 14), // 97 UDotAccSatKHR
  IR(32335, 15), // 98 SUDotAccSatKHR
  IR(34915, 21), // 99 ReportIntersectionNV
  IR(35090, 28), // 100 TypeAccelerationStructureNV
  IR(35171, 23), // 101 RayQueryGetClusterIdNV
  IR(37174, 21), // 102 DecorateStringGOOGLE
  IR(37216, 27), // 103 MemberDecorateStringGOOGLE
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
  spv::Capability::FPGAClusterAttributesINTEL, // 106
  spv::Capability::FPGAKernelAttributesINTEL, // 107
  spv::Capability::Subgroup2DBlockIOINTEL, // 108
  spv::Capability::VariableLengthArrayINTEL, // 109
  spv::Capability::UntypedPointersKHR, // 110
  spv::Capability::SpecConditionalINTEL, // 111
  spv::Capability::Shader, // 112
  spv::Capability::Kernel, // 113
  spv::Capability::Shader, // 114
  spv::Capability::UniformDecoration, // 115
  spv::Capability::GeometryStreams, // 116
  spv::Capability::TransformFeedback, // 117
  spv::Capability::Kernel, // 118
  spv::Capability::FloatControls2, // 119
  spv::Capability::Linkage, // 120
  spv::Capability::Float8EXT, // 121
  spv::Capability::SampleMaskOverrideCoverageNV, // 122
  spv::Capability::GeometryShaderPassthroughNV, // 123
  spv::Capability::MeshShadingNV, // 124
  spv::Capability::MeshShadingEXT, // 125
  spv::Capability::ShaderInvocationReorderNV, // 126
  spv::Capability::BindlessTextureNV, // 127
  spv::Capability::VectorComputeINTEL, // 128
  spv::Capability::IndirectReferencesINTEL, // 129
  spv::Capability::AsmINTEL, // 130
  spv::Capability::FunctionFloatControlINTEL, // 131
  spv::Capability::FPGAMemoryAttributesINTEL, // 132
  spv::Capability::FPGAMemoryAccessesINTEL, // 133
  spv::Capability::LoopFuseINTEL, // 134
  spv::Capability::FPGADSPControlINTEL, // 135
  spv::Capability::MemoryAccessAliasingINTEL, // 136
  spv::Capability::FPGAInvocationPipeliningAttributesINTEL, // 137
  spv::Capability::FPGABufferLocationINTEL, // 138
  spv::Capability::IOPipesINTEL, // 139
  spv::Capability::FPGAClusterAttributesV2INTEL, // 140
  spv::Capability::FPMaxErrorINTEL, // 141
  spv::Capability::FPGALatencyControlINTEL, // 142
  spv::Capability::FPGAArgumentInterfacesINTEL, // 143
  spv::Capability::GlobalVariableHostAccessINTEL, // 144
  spv::Capability::GlobalVariableFPGADecorationsINTEL, // 145
  spv::Capability::CacheControlsINTEL, // 146
  spv::Capability::TileImageColorReadAccessEXT, // 147
  spv::Capability::Geometry, // 148
  spv::Capability::Tessellation, // 149
  spv::Capability::MeshShadingNV, // 150
  spv::Capability::MeshShadingEXT, // 151
  spv::Capability::Geometry, // 152
  spv::Capability::MeshShadingNV, // 153
  spv::Capability::MeshShadingEXT, // 154
  spv::Capability::SubgroupDispatch, // 155
  spv::Capability::TileImageDepthReadAccessEXT, // 156
  spv::Capability::TileImageStencilReadAccessEXT, // 157
  spv::Capability::SampleMaskPostDepthCoverage, // 158
  spv::Capability::DenormPreserve, // 159
  spv::Capability::DenormFlushToZero, // 160
  spv::Capability::SignedZeroInfNanPreserve, // 161
  spv::Capability::RoundingModeRTE, // 162
  spv::Capability::RoundingModeRTZ, // 163
  spv::Capability::QuadControlKHR, // 164
  spv::Capability::ComputeDerivativeGroupQuadsKHR, // 165
  spv::Capability::ComputeDerivativeGroupLinearKHR, // 166
  spv::Capability::FragmentShaderPixelInterlockEXT, // 167
  spv::Capability::FragmentShaderSampleInterlockEXT, // 168
  spv::Capability::FragmentShaderShadingRateInterlockEXT, // 169
  spv::Capability::RoundToInfinityINTEL, // 170
  spv::Capability::KernelAttributesINTEL, // 171
  spv::Capability::FloatControls2, // 172
  spv::Capability::FPGAKernelAttributesv2INTEL, // 173
  spv::Capability::RegisterLimitsINTEL, // 174
  spv::Capability::FloatControls2, // 175
  spv::Capability::FPFastMathModeINTEL, // 176
  spv::Capability::OptNoneEXT, // 177
  spv::Capability::RuntimeAlignedAttributeINTEL, // 178
  spv::Capability::Kernel, // 179
  spv::Capability::GroupNonUniformArithmetic, // 180
  spv::Capability::GroupNonUniformBallot, // 181
  spv::Capability::GroupNonUniformClustered, // 182
  spv::Capability::GroupNonUniformPartitionedNV, // 183
  spv::Capability::ImageGatherExtended, // 184
  spv::Capability::MinLod, // 185
  spv::Capability::VulkanMemoryModel, // 186
  spv::Capability::FPGALoopControlsINTEL, // 187
  spv::Capability::ArbitraryPrecisionFixedPointINTEL, // 188
  spv::Capability::RawAccessChainsNV, // 189
  spv::Capability::RayTraversalPrimitiveCullingKHR, // 190
  spv::Capability::RayTracingOpacityMicromapEXT, // 191
  spv::Capability::RayQueryKHR, // 192
  spv::Capability::StorageImageExtendedFormats, // 193
  spv::Capability::Int64ImageEXT, // 194
  spv::Capability::Shader, // 195
  spv::Capability::VectorComputeINTEL, // 196
  spv::Capability::GenericPointer, // 197
  spv::Capability::FunctionPointersINTEL, // 198
  spv::Capability::USMStorageClassesINTEL, // 199
  spv::Capability::CooperativeMatrixTensorAddressingNV, // 200
  spv::Capability::CooperativeMatrixBlockLoadsNV, // 201
  spv::Capability::TensorsARM, // 202
  spv::Capability::Addresses, // 203
  spv::Capability::PhysicalStorageBufferAddresses, // 204
  spv::Capability::LiteralSampler, // 205
  spv::Capability::Addresses, // 206
  spv::Capability::UntypedPointersKHR, // 207
  spv::Capability::Addresses, // 208
  spv::Capability::VariablePointers, // 209
  spv::Capability::VariablePointersStorageBuffer, // 210
  spv::Capability::PhysicalStorageBufferAddresses, // 211
  spv::Capability::Kernel, // 212
  spv::Capability::ImageQuery, // 213
  spv::Capability::ImageQuery, // 214
  spv::Capability::Shader, // 215
  spv::Capability::BitInstructions, // 216
  spv::Capability::DerivativeControl, // 217
  spv::Capability::Groups, // 218
  spv::Capability::SparseResidency, // 219
  spv::Capability::PipeStorage, // 220
  spv::Capability::NamedBarrier, // 221
  spv::Capability::GroupNonUniformVote, // 222
  spv::Capability::GroupNonUniformBallot, // 223
  spv::Capability::GroupNonUniformShuffle, // 224
  spv::Capability::GroupNonUniformShuffleRelative, // 225
  spv::Capability::GroupNonUniformArithmetic, // 226
  spv::Capability::GroupNonUniformClustered, // 227
  spv::Capability::GroupNonUniformPartitionedNV, // 228
  spv::Capability::GroupNonUniformQuad, // 229
  spv::Capability::Addresses, // 230
  spv::Capability::VariablePointers, // 231
  spv::Capability::VariablePointersStorageBuffer, // 232
  spv::Capability::GraphARM, // 233
  spv::Capability::UntypedPointersKHR, // 234
  spv::Capability::SubgroupBallotKHR, // 235
  spv::Capability::SubgroupVoteKHR, // 236
  spv::Capability::GroupNonUniformRotateKHR, // 237
  spv::Capability::RayTracingKHR, // 238
  spv::Capability::RayQueryKHR, // 239
  spv::Capability::DotProduct, // 240
  spv::Capability::ReplicatedCompositesEXT, // 241
  spv::Capability::TextureSampleWeightedQCOM, // 242
  spv::Capability::TextureBoxFilterQCOM, // 243
  spv::Capability::TextureBlockMatchQCOM, // 244
  spv::Capability::CooperativeMatrixConversionQCOM, // 245
  spv::Capability::TextureBlockMatch2QCOM, // 246
  spv::Capability::FragmentMaskAMD, // 247
  spv::Capability::ShaderClockKHR, // 248
  spv::Capability::ShaderInvocationReorderNV, // 249
  spv::Capability::RayTracingMotionBlurNV, // 250
  spv::Capability::ImageFootprintNV, // 251
  spv::Capability::CooperativeVectorNV, // 252
  spv::Capability::CooperativeVectorTrainingNV, // 253
  spv::Capability::CooperativeMatrixConversionsNV, // 254
  spv::Capability::DisplacementMicromapNV, // 255
  spv::Capability::RayQueryPositionFetchKHR, // 256
  spv::Capability::RayTracingNV, // 257
  spv::Capability::RayTracingKHR, // 258
  spv::Capability::RayQueryKHR, // 259
  spv::Capability::DisplacementMicromapNV, // 260
  spv::Capability::CooperativeMatrixNV, // 261
  spv::Capability::FragmentShaderSampleInterlockEXT, // 262
  spv::Capability::FragmentShaderPixelInterlockEXT, // 263
  spv::Capability::FragmentShaderShadingRateInterlockEXT, // 264
  spv::Capability::CooperativeMatrixReductionsNV, // 265
  spv::Capability::CooperativeMatrixPerElementOperationsNV, // 266
  spv::Capability::TensorAddressingNV, // 267
  spv::Capability::DemoteToHelperInvocation, // 268
  spv::Capability::SubgroupShuffleINTEL, // 269
  spv::Capability::SubgroupBufferBlockIOINTEL, // 270
  spv::Capability::SubgroupImageBlockIOINTEL, // 271
  spv::Capability::SubgroupImageMediaBlockIOINTEL, // 272
  spv::Capability::IntegerFunctions2INTEL, // 273
  spv::Capability::AtomicFloat16MinMaxEXT, // 274
  spv::Capability::AtomicFloat32MinMaxEXT, // 275
  spv::Capability::AtomicFloat64MinMaxEXT, // 276
  spv::Capability::AtomicFloat16VectorNV, // 277
  spv::Capability::ExpectAssumeKHR, // 278
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 279
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 280
  spv::Capability::SubgroupAvcMotionEstimationIntraINTEL, // 281
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 282
  spv::Capability::SubgroupAvcMotionEstimationChromaINTEL, // 283
  spv::Capability::VariableLengthArrayINTEL, // 284
  spv::Capability::ArbitraryPrecisionFloatingPointINTEL, // 285
  spv::Capability::UnstructuredLoopControlsINTEL, // 286
  spv::Capability::BlockingPipesINTEL, // 287
  spv::Capability::FPGARegINTEL, // 288
  spv::Capability::AtomicFloat16AddEXT, // 289
  spv::Capability::AtomicFloat32AddEXT, // 290
  spv::Capability::AtomicFloat64AddEXT, // 291
  spv::Capability::AtomicFloat16VectorNV, // 292
  spv::Capability::LongCompositesINTEL, // 293
  spv::Capability::BFloat16ConversionINTEL, // 294
  spv::Capability::SplitBarrierINTEL, // 295
  spv::Capability::ArithmeticFenceEXT, // 296
  spv::Capability::TaskSequenceINTEL, // 297
  spv::Capability::SubgroupBufferPrefetchINTEL, // 298
  spv::Capability::Subgroup2DBlockTransformINTEL, // 299
  spv::Capability::Subgroup2DBlockTransposeINTEL, // 300
  spv::Capability::SubgroupMatrixMultiplyAccumulateINTEL, // 301
  spv::Capability::TernaryBitwiseFunctionINTEL, // 302
  spv::Capability::UntypedVariableLengthArrayINTEL, // 303
  spv::Capability::FunctionVariantsINTEL, // 304
  spv::Capability::GroupUniformArithmeticKHR, // 305
  spv::Capability::TensorFloat32RoundingINTEL, // 306
  spv::Capability::MaskedGatherScatterINTEL, // 307
  spv::Capability::BindlessImagesINTEL, // 308
  spv::Capability::Float64, // 309
  spv::Capability::InterpolationFunction, // 310
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
  spvtools::Extension::kSPV_NV_bindless_texture, // 85
  spvtools::Extension::kSPV_NV_cooperative_vector, // 86
  spvtools::Extension::kSPV_NV_shader_atomic_fp16_vector, // 87
  spvtools::Extension::kSPV_NV_raw_access_chains, // 88
  spvtools::Extension::kSPV_NV_cooperative_matrix2, // 89
  spvtools::Extension::kSPV_NV_tensor_addressing, // 90
  spvtools::Extension::kSPV_INTEL_subgroups, // 91
  spvtools::Extension::kSPV_INTEL_media_block_io, // 92
  spvtools::Extension::kSPV_INTEL_float_controls2, // 93
  spvtools::Extension::kSPV_INTEL_shader_integer_functions2, // 94
  spvtools::Extension::kSPV_INTEL_function_pointers, // 95
  spvtools::Extension::kSPV_INTEL_inline_assembly, // 96
  spvtools::Extension::kSPV_EXT_shader_atomic_float_min_max, // 97
  spvtools::Extension::kSPV_INTEL_vector_compute, // 98
  spvtools::Extension::kSPV_KHR_expect_assume, // 99
  spvtools::Extension::kSPV_INTEL_device_side_avc_motion_estimation, // 100
  spvtools::Extension::kSPV_INTEL_variable_length_array, // 101
  spvtools::Extension::kSPV_INTEL_fpga_memory_attributes, // 102
  spvtools::Extension::kSPV_INTEL_fp_fast_math_mode, // 103
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_integers, // 104
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_floating_point, // 105
  spvtools::Extension::kSPV_INTEL_unstructured_loop_controls, // 106
  spvtools::Extension::kSPV_INTEL_fpga_loop_controls, // 107
  spvtools::Extension::kSPV_INTEL_kernel_attributes, // 108
  spvtools::Extension::kSPV_INTEL_fpga_memory_accesses, // 109
  spvtools::Extension::kSPV_INTEL_fpga_cluster_attributes, // 110
  spvtools::Extension::kSPV_INTEL_loop_fuse, // 111
  spvtools::Extension::kSPV_INTEL_fpga_dsp_control, // 112
  spvtools::Extension::kSPV_INTEL_memory_access_aliasing, // 113
  spvtools::Extension::kSPV_INTEL_fpga_invocation_pipelining_attributes, // 114
  spvtools::Extension::kSPV_INTEL_fpga_buffer_location, // 115
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_fixed_point, // 116
  spvtools::Extension::kSPV_INTEL_usm_storage_classes, // 117
  spvtools::Extension::kSPV_INTEL_runtime_aligned, // 118
  spvtools::Extension::kSPV_INTEL_io_pipes, // 119
  spvtools::Extension::kSPV_INTEL_blocking_pipes, // 120
  spvtools::Extension::kSPV_INTEL_fpga_reg, // 121
  spvtools::Extension::kSPV_KHR_integer_dot_product, // 122
  spvtools::Extension::kSPV_KHR_cooperative_matrix, // 123
  spvtools::Extension::kSPV_EXT_replicated_composites, // 124
  spvtools::Extension::kSPV_KHR_bit_instructions, // 125
  spvtools::Extension::kSPV_KHR_subgroup_rotate, // 126
  spvtools::Extension::kSPV_KHR_float_controls2, // 127
  spvtools::Extension::kSPV_EXT_shader_atomic_float_add, // 128
  spvtools::Extension::kSPV_INTEL_long_composites, // 129
  spvtools::Extension::kSPV_EXT_optnone, // 130
  spvtools::Extension::kSPV_INTEL_optnone, // 131
  spvtools::Extension::kSPV_EXT_shader_atomic_float16_add, // 132
  spvtools::Extension::kSPV_INTEL_debug_module, // 133
  spvtools::Extension::kSPV_INTEL_bfloat16_conversion, // 134
  spvtools::Extension::kSPV_INTEL_split_barrier, // 135
  spvtools::Extension::kSPV_EXT_arithmetic_fence, // 136
  spvtools::Extension::kSPV_INTEL_task_sequence, // 137
  spvtools::Extension::kSPV_INTEL_fp_max_error, // 138
  spvtools::Extension::kSPV_INTEL_fpga_latency_control, // 139
  spvtools::Extension::kSPV_INTEL_fpga_argument_interfaces, // 140
  spvtools::Extension::kSPV_INTEL_global_variable_host_access, // 141
  spvtools::Extension::kSPV_INTEL_global_variable_fpga_decorations, // 142
  spvtools::Extension::kSPV_INTEL_subgroup_buffer_prefetch, // 143
  spvtools::Extension::kSPV_INTEL_2d_block_io, // 144
  spvtools::Extension::kSPV_INTEL_subgroup_matrix_multiply_accumulate, // 145
  spvtools::Extension::kSPV_INTEL_ternary_bitwise_function, // 146
  spvtools::Extension::kSPV_INTEL_function_variants, // 147
  spvtools::Extension::kSPV_KHR_uniform_group_instructions, // 148
  spvtools::Extension::kSPV_INTEL_tensor_float32_conversion, // 149
  spvtools::Extension::kSPV_INTEL_masked_gather_scatter, // 150
  spvtools::Extension::kSPV_INTEL_cache_controls, // 151
  spvtools::Extension::kSPV_INTEL_maximum_registers, // 152
  spvtools::Extension::kSPV_INTEL_bindless_images, // 153
  spvtools::Extension::kSPV_KHR_no_integer_wrap_decoration, // 154
  spvtools::Extension::kSPV_NV_mesh_shader, // 155
  spvtools::Extension::kSPV_EXT_mesh_shader, // 156
  spvtools::Extension::kSPV_GOOGLE_hlsl_functionality1, // 157
  spvtools::Extension::kSPV_GOOGLE_user_type, // 158
  spvtools::Extension::kSPV_KHR_subgroup_uniform_control_flow, // 159
  spvtools::Extension::kSPV_AMD_shader_early_and_late_fragment_tests, // 160
  spvtools::Extension::kSPV_AMD_shader_early_and_late_fragment_tests, // 161
  spvtools::Extension::kSPV_EXT_shader_stencil_export, // 162
  spvtools::Extension::kSPV_KHR_maximal_reconvergence, // 163
  spvtools::Extension::kSPV_KHR_linkonce_odr, // 164
  spvtools::Extension::kSPV_KHR_storage_buffer_storage_class, // 165
  spvtools::Extension::kSPV_KHR_variable_pointers, // 166
  spvtools::Extension::kSPV_KHR_terminate_invocation, // 167
  spvtools::Extension::kSPV_KHR_relaxed_extended_instruction, // 168
  spvtools::Extension::kSPV_KHR_ray_tracing, // 169
  spvtools::Extension::kSPV_KHR_ray_query, // 170
  spvtools::Extension::kSPV_NV_ray_tracing, // 171
  spvtools::Extension::kSPV_KHR_ray_tracing, // 172
  spvtools::Extension::kSPV_KHR_ray_query, // 173
  spvtools::Extension::kSPV_NV_displacement_micromap, // 174
  spvtools::Extension::kSPV_GOOGLE_decorate_string, // 175
  spvtools::Extension::kSPV_GOOGLE_hlsl_functionality1, // 176
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
  SPV_OPERAND_TYPE_RESULT_ID, // 590
  SPV_OPERAND_TYPE_ID, // 591
  SPV_OPERAND_TYPE_SCOPE_ID, // 592
  SPV_OPERAND_TYPE_ID, // 593
  SPV_OPERAND_TYPE_ID, // 594
  SPV_OPERAND_TYPE_TYPE_ID, // 595
  SPV_OPERAND_TYPE_RESULT_ID, // 596
  SPV_OPERAND_TYPE_ID, // 597
  SPV_OPERAND_TYPE_ID, // 598
  SPV_OPERAND_TYPE_ID, // 599
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 600
  SPV_OPERAND_TYPE_ID, // 601
  SPV_OPERAND_TYPE_ID, // 602
  SPV_OPERAND_TYPE_ID, // 603
  SPV_OPERAND_TYPE_ID, // 604
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 605
  SPV_OPERAND_TYPE_TYPE_ID, // 606
  SPV_OPERAND_TYPE_RESULT_ID, // 607
  SPV_OPERAND_TYPE_ID, // 608
  SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE, // 609
  SPV_OPERAND_TYPE_ID, // 610
  SPV_OPERAND_TYPE_TYPE_ID, // 611
  SPV_OPERAND_TYPE_RESULT_ID, // 612
  SPV_OPERAND_TYPE_ID, // 613
  SPV_OPERAND_TYPE_ID, // 614
  SPV_OPERAND_TYPE_ID, // 615
  SPV_OPERAND_TYPE_MEMORY_ACCESS, // 616
  SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS, // 617
  SPV_OPERAND_TYPE_ID, // 618
  SPV_OPERAND_TYPE_ID, // 619
  SPV_OPERAND_TYPE_ID, // 620
  SPV_OPERAND_TYPE_MEMORY_ACCESS, // 621
  SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS, // 622
  SPV_OPERAND_TYPE_RESULT_ID, // 623
  SPV_OPERAND_TYPE_ID, // 624
  SPV_OPERAND_TYPE_ID, // 625
  SPV_OPERAND_TYPE_VARIABLE_ID, // 626
  SPV_OPERAND_TYPE_TYPE_ID, // 627
  SPV_OPERAND_TYPE_RESULT_ID, // 628
  SPV_OPERAND_TYPE_ID, // 629
  SPV_OPERAND_TYPE_ID, // 630
  SPV_OPERAND_TYPE_ID, // 631
  SPV_OPERAND_TYPE_ID, // 632
  SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS, // 633
  SPV_OPERAND_TYPE_ID, // 634
  SPV_OPERAND_TYPE_ID, // 635
  SPV_OPERAND_TYPE_ID, // 636
  SPV_OPERAND_TYPE_ID, // 637
  SPV_OPERAND_TYPE_ID, // 638
  SPV_OPERAND_TYPE_TYPE_ID, // 639
  SPV_OPERAND_TYPE_RESULT_ID, // 640
  SPV_OPERAND_TYPE_ID, // 641
  SPV_OPERAND_TYPE_ID, // 642
  SPV_OPERAND_TYPE_LITERAL_STRING, // 643
  SPV_OPERAND_TYPE_LITERAL_STRING, // 644
  SPV_OPERAND_TYPE_TYPE_ID, // 645
  SPV_OPERAND_TYPE_RESULT_ID, // 646
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
  SPV_OPERAND_TYPE_ID, // 657
  SPV_OPERAND_TYPE_ID, // 658
  SPV_OPERAND_TYPE_ID, // 659
  SPV_OPERAND_TYPE_ID, // 660
  SPV_OPERAND_TYPE_ID, // 661
  SPV_OPERAND_TYPE_ID, // 662
  SPV_OPERAND_TYPE_ID, // 663
  SPV_OPERAND_TYPE_TYPE_ID, // 664
  SPV_OPERAND_TYPE_RESULT_ID, // 665
  SPV_OPERAND_TYPE_ID, // 666
  SPV_OPERAND_TYPE_ID, // 667
  SPV_OPERAND_TYPE_ID, // 668
  SPV_OPERAND_TYPE_ID, // 669
  SPV_OPERAND_TYPE_ID, // 670
  SPV_OPERAND_TYPE_ID, // 671
  SPV_OPERAND_TYPE_ID, // 672
  SPV_OPERAND_TYPE_ID, // 673
  SPV_OPERAND_TYPE_ID, // 674
  SPV_OPERAND_TYPE_ID, // 675
  SPV_OPERAND_TYPE_ID, // 676
  SPV_OPERAND_TYPE_TYPE_ID, // 677
  SPV_OPERAND_TYPE_RESULT_ID, // 678
  SPV_OPERAND_TYPE_ID, // 679
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 680
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 681
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 682
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 683
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 684
  SPV_OPERAND_TYPE_TYPE_ID, // 685
  SPV_OPERAND_TYPE_RESULT_ID, // 686
  SPV_OPERAND_TYPE_ID, // 687
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 688
  SPV_OPERAND_TYPE_ID, // 689
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 690
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 691
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 692
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 693
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 694
  SPV_OPERAND_TYPE_TYPE_ID, // 695
  SPV_OPERAND_TYPE_RESULT_ID, // 696
  SPV_OPERAND_TYPE_ID, // 697
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 698
  SPV_OPERAND_TYPE_ID, // 699
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 700
  SPV_OPERAND_TYPE_RESULT_ID, // 701
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 702
  SPV_OPERAND_TYPE_RESULT_ID, // 703
  SPV_OPERAND_TYPE_ID, // 704
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 705
  SPV_OPERAND_TYPE_VARIABLE_ID, // 706
  SPV_OPERAND_TYPE_TYPE_ID, // 707
  SPV_OPERAND_TYPE_RESULT_ID, // 708
  SPV_OPERAND_TYPE_ID, // 709
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 710
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 711
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 712
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 713
  SPV_OPERAND_TYPE_ID, // 714
  SPV_OPERAND_TYPE_ID, // 715
  SPV_OPERAND_TYPE_ID, // 716
  SPV_OPERAND_TYPE_ID, // 717
  SPV_OPERAND_TYPE_ID, // 718
  SPV_OPERAND_TYPE_ID, // 719
  SPV_OPERAND_TYPE_ID, // 720
  SPV_OPERAND_TYPE_ID, // 721
  SPV_OPERAND_TYPE_ID, // 722
  SPV_OPERAND_TYPE_ID, // 723
  SPV_OPERAND_TYPE_ID, // 724
  SPV_OPERAND_TYPE_ID, // 725
  SPV_OPERAND_TYPE_ID, // 726
  SPV_OPERAND_TYPE_ID, // 727
  SPV_OPERAND_TYPE_ID, // 728
  SPV_OPERAND_TYPE_ID, // 729
  SPV_OPERAND_TYPE_ID, // 730
  SPV_OPERAND_TYPE_ID, // 731
  SPV_OPERAND_TYPE_ID, // 732
  SPV_OPERAND_TYPE_TYPE_ID, // 733
  SPV_OPERAND_TYPE_RESULT_ID, // 734
  SPV_OPERAND_TYPE_ID, // 735
  SPV_OPERAND_TYPE_ID, // 736
  SPV_OPERAND_TYPE_ID, // 737
  SPV_OPERAND_TYPE_ID, // 738
  SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS, // 739
  SPV_OPERAND_TYPE_ID, // 740
  SPV_OPERAND_TYPE_EXECUTION_MODEL, // 741
  SPV_OPERAND_TYPE_ID, // 742
  SPV_OPERAND_TYPE_LITERAL_STRING, // 743
  SPV_OPERAND_TYPE_VARIABLE_ID, // 744
  SPV_OPERAND_TYPE_ID, // 745
  SPV_OPERAND_TYPE_CAPABILITY, // 746
  SPV_OPERAND_TYPE_TYPE_ID, // 747
  SPV_OPERAND_TYPE_RESULT_ID, // 748
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 749
  SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER, // 750
  SPV_OPERAND_TYPE_TYPE_ID, // 751
  SPV_OPERAND_TYPE_RESULT_ID, // 752
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 753
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 754
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 755
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 756
  SPV_OPERAND_TYPE_TYPE_ID, // 757
  SPV_OPERAND_TYPE_RESULT_ID, // 758
  SPV_OPERAND_TYPE_VARIABLE_CAPABILITY, // 759
  SPV_OPERAND_TYPE_TYPE_ID, // 760
  SPV_OPERAND_TYPE_RESULT_ID, // 761
  SPV_OPERAND_TYPE_ID, // 762
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 763
  SPV_OPERAND_TYPE_ID, // 764
  SPV_OPERAND_TYPE_ID, // 765
  SPV_OPERAND_TYPE_ID, // 766
  SPV_OPERAND_TYPE_ID, // 767
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 768
  SPV_OPERAND_TYPE_ID, // 769
  SPV_OPERAND_TYPE_ID, // 770
  SPV_OPERAND_TYPE_ID, // 771
  SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING, // 772
  SPV_OPERAND_TYPE_ID, // 773
  SPV_OPERAND_TYPE_STORAGE_CLASS, // 774
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 775
  SPV_OPERAND_TYPE_ID, // 776
  SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER, // 777
  SPV_OPERAND_TYPE_ID, // 778
  SPV_OPERAND_TYPE_ID, // 779
  SPV_OPERAND_TYPE_ID, // 780
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 781
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 782
  SPV_OPERAND_TYPE_ID, // 783
  SPV_OPERAND_TYPE_ID, // 784
  SPV_OPERAND_TYPE_ID, // 785
  SPV_OPERAND_TYPE_ID, // 786
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 787
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 788
  SPV_OPERAND_TYPE_ID, // 789
  SPV_OPERAND_TYPE_ID, // 790
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 791
  SPV_OPERAND_TYPE_VARIABLE_ID, // 792
  SPV_OPERAND_TYPE_ID, // 793
  SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE, // 794
  SPV_OPERAND_TYPE_ID, // 795
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 796
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 797
  SPV_OPERAND_TYPE_ID, // 798
  SPV_OPERAND_TYPE_ID, // 799
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 800
  SPV_OPERAND_TYPE_VARIABLE_ID, // 801
  SPV_OPERAND_TYPE_ID, // 802
  SPV_OPERAND_TYPE_ID, // 803
  SPV_OPERAND_TYPE_ID, // 804
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 805
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 806
  SPV_OPERAND_TYPE_ID, // 807
  SPV_OPERAND_TYPE_ID, // 808
  SPV_OPERAND_TYPE_ID, // 809
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 810
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 811
  SPV_OPERAND_TYPE_ID, // 812
  SPV_OPERAND_TYPE_ID, // 813
  SPV_OPERAND_TYPE_ID, // 814
  SPV_OPERAND_TYPE_ID, // 815
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 816
  SPV_OPERAND_TYPE_ID, // 817
  SPV_OPERAND_TYPE_ID, // 818
  SPV_OPERAND_TYPE_ID, // 819
  SPV_OPERAND_TYPE_ID, // 820
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 821
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 822
  SPV_OPERAND_TYPE_ID, // 823
  SPV_OPERAND_TYPE_ID, // 824
  SPV_OPERAND_TYPE_ID, // 825
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 826
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 827
  SPV_OPERAND_TYPE_ID, // 828
  SPV_OPERAND_TYPE_ID, // 829
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 830
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 831
  SPV_OPERAND_TYPE_VARIABLE_ID, // 832
  SPV_OPERAND_TYPE_ID, // 833
  SPV_OPERAND_TYPE_ID, // 834
  SPV_OPERAND_TYPE_ID, // 835
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 836
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 837
  SPV_OPERAND_TYPE_ID, // 838
  SPV_OPERAND_TYPE_ID, // 839
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 840
  SPV_OPERAND_TYPE_ID, // 841
  SPV_OPERAND_TYPE_ID, // 842
  SPV_OPERAND_TYPE_ID, // 843
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 844
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 845
  SPV_OPERAND_TYPE_ID, // 846
  SPV_OPERAND_TYPE_ID, // 847
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 848
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 849
  SPV_OPERAND_TYPE_ID, // 850
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 851
  SPV_OPERAND_TYPE_ID, // 852
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 853
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 854
  SPV_OPERAND_TYPE_ID, // 855
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 856
  SPV_OPERAND_TYPE_ID, // 857
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 858
  SPV_OPERAND_TYPE_ID, // 859
  SPV_OPERAND_TYPE_ID, // 860
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 861
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 862
  SPV_OPERAND_TYPE_ID, // 863
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 864
  SPV_OPERAND_TYPE_ID, // 865
  SPV_OPERAND_TYPE_ID, // 866
  SPV_OPERAND_TYPE_ID, // 867
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 868
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 869
  SPV_OPERAND_TYPE_ID, // 870
  SPV_OPERAND_TYPE_OPTIONAL_LITERAL_INTEGER, // 871
  SPV_OPERAND_TYPE_DEBUG_OPERATION, // 872
  SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER, // 873
  SPV_OPERAND_TYPE_ID, // 874
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 875
  SPV_OPERAND_TYPE_ID, // 876
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 877
  SPV_OPERAND_TYPE_ID, // 878
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 879
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 880
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 881
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 882
  SPV_OPERAND_TYPE_ID, // 883
  SPV_OPERAND_TYPE_ID, // 884
  SPV_OPERAND_TYPE_ID, // 885
  SPV_OPERAND_TYPE_ID, // 886
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 887
  SPV_OPERAND_TYPE_ID, // 888
  SPV_OPERAND_TYPE_ID, // 889
  SPV_OPERAND_TYPE_ID, // 890
  SPV_OPERAND_TYPE_ID, // 891
  SPV_OPERAND_TYPE_ID, // 892
  SPV_OPERAND_TYPE_ID, // 893
  SPV_OPERAND_TYPE_ID, // 894
  SPV_OPERAND_TYPE_ID, // 895
  SPV_OPERAND_TYPE_VARIABLE_ID, // 896
  SPV_OPERAND_TYPE_ID, // 897
  SPV_OPERAND_TYPE_ID, // 898
  SPV_OPERAND_TYPE_ID, // 899
  SPV_OPERAND_TYPE_ID, // 900
  SPV_OPERAND_TYPE_ID, // 901
  SPV_OPERAND_TYPE_ID, // 902
  SPV_OPERAND_TYPE_ID, // 903
  SPV_OPERAND_TYPE_ID, // 904
  SPV_OPERAND_TYPE_ID, // 905
  SPV_OPERAND_TYPE_VARIABLE_ID, // 906
  SPV_OPERAND_TYPE_ID, // 907
  SPV_OPERAND_TYPE_ID, // 908
  SPV_OPERAND_TYPE_ID, // 909
  SPV_OPERAND_TYPE_ID, // 910
  SPV_OPERAND_TYPE_ID, // 911
  SPV_OPERAND_TYPE_ID, // 912
  SPV_OPERAND_TYPE_ID, // 913
  SPV_OPERAND_TYPE_ID, // 914
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 915
  SPV_OPERAND_TYPE_ID, // 916
  SPV_OPERAND_TYPE_ID, // 917
  SPV_OPERAND_TYPE_ID, // 918
  SPV_OPERAND_TYPE_ID, // 919
  SPV_OPERAND_TYPE_VARIABLE_ID, // 920
  SPV_OPERAND_TYPE_ID, // 921
  SPV_OPERAND_TYPE_ID, // 922
  SPV_OPERAND_TYPE_ID, // 923
  SPV_OPERAND_TYPE_ID, // 924
  SPV_OPERAND_TYPE_ID, // 925
  SPV_OPERAND_TYPE_ID, // 926
  SPV_OPERAND_TYPE_ID, // 927
  SPV_OPERAND_TYPE_ID, // 928
  SPV_OPERAND_TYPE_ID, // 929
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 930
  SPV_OPERAND_TYPE_ID, // 931
  SPV_OPERAND_TYPE_ID, // 932
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 933
  SPV_OPERAND_TYPE_ID, // 934
  SPV_OPERAND_TYPE_ID, // 935
  SPV_OPERAND_TYPE_ID, // 936
  SPV_OPERAND_TYPE_ID, // 937
  SPV_OPERAND_TYPE_ID, // 938
  SPV_OPERAND_TYPE_ID, // 939
  SPV_OPERAND_TYPE_ID, // 940
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 941
  SPV_OPERAND_TYPE_ID, // 942
  SPV_OPERAND_TYPE_ID, // 943
  SPV_OPERAND_TYPE_ID, // 944
  SPV_OPERAND_TYPE_VARIABLE_ID, // 945
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
  SPV_OPERAND_TYPE_ID, // 973
  SPV_OPERAND_TYPE_ID, // 974
  SPV_OPERAND_TYPE_ID, // 975
  SPV_OPERAND_TYPE_ID, // 976
  SPV_OPERAND_TYPE_ID, // 977
  SPV_OPERAND_TYPE_ID, // 978
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
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1013
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1014
  SPV_OPERAND_TYPE_ID, // 1015
  SPV_OPERAND_TYPE_SOURCE_LANGUAGE, // 1016
  SPV_OPERAND_TYPE_ID, // 1017
  SPV_OPERAND_TYPE_ID, // 1018
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING, // 1019
  SPV_OPERAND_TYPE_ID, // 1020
  SPV_OPERAND_TYPE_STORAGE_CLASS, // 1021
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1022
  SPV_OPERAND_TYPE_ID, // 1023
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER, // 1024
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1025
  SPV_OPERAND_TYPE_ID, // 1026
  SPV_OPERAND_TYPE_VARIABLE_ID, // 1027
  SPV_OPERAND_TYPE_ID, // 1028
  SPV_OPERAND_TYPE_ID, // 1029
  SPV_OPERAND_TYPE_ID, // 1030
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1031
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1032
  SPV_OPERAND_TYPE_ID, // 1033
  SPV_OPERAND_TYPE_ID, // 1034
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1035
  SPV_OPERAND_TYPE_VARIABLE_ID, // 1036
  SPV_OPERAND_TYPE_ID, // 1037
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE, // 1038
  SPV_OPERAND_TYPE_ID, // 1039
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1040
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1041
  SPV_OPERAND_TYPE_ID, // 1042
  SPV_OPERAND_TYPE_ID, // 1043
  SPV_OPERAND_TYPE_ID, // 1044
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1045
  SPV_OPERAND_TYPE_VARIABLE_ID, // 1046
  SPV_OPERAND_TYPE_ID, // 1047
  SPV_OPERAND_TYPE_ID, // 1048
  SPV_OPERAND_TYPE_ID, // 1049
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1050
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1051
  SPV_OPERAND_TYPE_ID, // 1052
  SPV_OPERAND_TYPE_ID, // 1053
  SPV_OPERAND_TYPE_ID, // 1054
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1055
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 1056
  SPV_OPERAND_TYPE_ID, // 1057
  SPV_OPERAND_TYPE_ID, // 1058
  SPV_OPERAND_TYPE_ID, // 1059
  SPV_OPERAND_TYPE_ID, // 1060
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1061
  SPV_OPERAND_TYPE_ID, // 1062
  SPV_OPERAND_TYPE_ID, // 1063
  SPV_OPERAND_TYPE_ID, // 1064
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1065
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1066
  SPV_OPERAND_TYPE_ID, // 1067
  SPV_OPERAND_TYPE_ID, // 1068
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1069
  SPV_OPERAND_TYPE_ID, // 1070
  SPV_OPERAND_TYPE_ID, // 1071
  SPV_OPERAND_TYPE_ID, // 1072
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1073
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1074
  SPV_OPERAND_TYPE_ID, // 1075
  SPV_OPERAND_TYPE_ID, // 1076
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1077
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1078
  SPV_OPERAND_TYPE_ID, // 1079
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 1080
  SPV_OPERAND_TYPE_ID, // 1081
  SPV_OPERAND_TYPE_ID, // 1082
  SPV_OPERAND_TYPE_ID, // 1083
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1084
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1085
  SPV_OPERAND_TYPE_ID, // 1086
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS, // 1087
  SPV_OPERAND_TYPE_OPTIONAL_LITERAL_INTEGER, // 1088
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION, // 1089
  SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER, // 1090
  SPV_OPERAND_TYPE_ID, // 1091
  SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY, // 1092
  SPV_OPERAND_TYPE_ID, // 1093
  SPV_OPERAND_TYPE_ID, // 1094
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1095
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1096
  SPV_OPERAND_TYPE_ID, // 1097
  SPV_OPERAND_TYPE_ID, // 1098
  SPV_OPERAND_TYPE_ID, // 1099
  SPV_OPERAND_TYPE_ID, // 1100
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1101
  SPV_OPERAND_TYPE_ID, // 1102
  SPV_OPERAND_TYPE_ID, // 1103
  SPV_OPERAND_TYPE_ID, // 1104
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1105
  SPV_OPERAND_TYPE_ID, // 1106
  SPV_OPERAND_TYPE_ID, // 1107
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 1108
  SPV_OPERAND_TYPE_ID, // 1109
  SPV_OPERAND_TYPE_ID, // 1110
  SPV_OPERAND_TYPE_ID, // 1111
  SPV_OPERAND_TYPE_FP_ROUNDING_MODE, // 1112
};
