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
    case Extension::kSPV_KHR_fma: return IR(2894, 12);
    case Extension::kSPV_KHR_fragment_shader_barycentric: return IR(2906, 36);
    case Extension::kSPV_KHR_fragment_shading_rate: return IR(2942, 30);
    case Extension::kSPV_KHR_integer_dot_product: return IR(2972, 28);
    case Extension::kSPV_KHR_linkonce_odr: return IR(3000, 21);
    case Extension::kSPV_KHR_maximal_reconvergence: return IR(3021, 30);
    case Extension::kSPV_KHR_multiview: return IR(3051, 18);
    case Extension::kSPV_KHR_no_integer_wrap_decoration: return IR(3069, 35);
    case Extension::kSPV_KHR_non_semantic_info: return IR(3104, 26);
    case Extension::kSPV_KHR_physical_storage_buffer: return IR(3130, 32);
    case Extension::kSPV_KHR_post_depth_coverage: return IR(3162, 28);
    case Extension::kSPV_KHR_quad_control: return IR(3190, 21);
    case Extension::kSPV_KHR_ray_cull_mask: return IR(3211, 22);
    case Extension::kSPV_KHR_ray_query: return IR(3233, 18);
    case Extension::kSPV_KHR_ray_tracing: return IR(3251, 20);
    case Extension::kSPV_KHR_ray_tracing_position_fetch: return IR(3271, 35);
    case Extension::kSPV_KHR_relaxed_extended_instruction: return IR(3306, 37);
    case Extension::kSPV_KHR_shader_atomic_counter_ops: return IR(3343, 34);
    case Extension::kSPV_KHR_shader_ballot: return IR(3377, 22);
    case Extension::kSPV_KHR_shader_clock: return IR(3399, 21);
    case Extension::kSPV_KHR_shader_draw_parameters: return IR(3420, 31);
    case Extension::kSPV_KHR_storage_buffer_storage_class: return IR(3451, 37);
    case Extension::kSPV_KHR_subgroup_rotate: return IR(3488, 24);
    case Extension::kSPV_KHR_subgroup_uniform_control_flow: return IR(3512, 38);
    case Extension::kSPV_KHR_subgroup_vote: return IR(3550, 22);
    case Extension::kSPV_KHR_terminate_invocation: return IR(3572, 29);
    case Extension::kSPV_KHR_uniform_group_instructions: return IR(3601, 35);
    case Extension::kSPV_KHR_untyped_pointers: return IR(3636, 25);
    case Extension::kSPV_KHR_variable_pointers: return IR(3661, 26);
    case Extension::kSPV_KHR_vulkan_memory_model: return IR(3687, 28);
    case Extension::kSPV_KHR_workgroup_memory_explicit_layout: return IR(3715, 41);
    case Extension::kSPV_NVX_multiview_per_view_attributes: return IR(3756, 38);
    case Extension::kSPV_NV_bindless_texture: return IR(3794, 24);
    case Extension::kSPV_NV_cluster_acceleration_structure: return IR(3818, 38);
    case Extension::kSPV_NV_compute_shader_derivatives: return IR(3856, 34);
    case Extension::kSPV_NV_cooperative_matrix: return IR(3890, 26);
    case Extension::kSPV_NV_cooperative_matrix2: return IR(3916, 27);
    case Extension::kSPV_NV_cooperative_vector: return IR(3943, 26);
    case Extension::kSPV_NV_displacement_micromap: return IR(3969, 29);
    case Extension::kSPV_NV_fragment_shader_barycentric: return IR(3998, 35);
    case Extension::kSPV_NV_geometry_shader_passthrough: return IR(4033, 35);
    case Extension::kSPV_NV_linear_swept_spheres: return IR(4068, 28);
    case Extension::kSPV_NV_mesh_shader: return IR(4096, 19);
    case Extension::kSPV_NV_raw_access_chains: return IR(4115, 25);
    case Extension::kSPV_NV_ray_tracing: return IR(4140, 19);
    case Extension::kSPV_NV_ray_tracing_motion_blur: return IR(4159, 31);
    case Extension::kSPV_NV_sample_mask_override_coverage: return IR(4190, 37);
    case Extension::kSPV_NV_shader_atomic_fp16_vector: return IR(4227, 33);
    case Extension::kSPV_NV_shader_image_footprint: return IR(4260, 30);
    case Extension::kSPV_NV_shader_invocation_reorder: return IR(4290, 33);
    case Extension::kSPV_NV_shader_sm_builtins: return IR(4323, 26);
    case Extension::kSPV_NV_shader_subgroup_partitioned: return IR(4349, 35);
    case Extension::kSPV_NV_shading_rate: return IR(4384, 20);
    case Extension::kSPV_NV_stereo_view_rendering: return IR(4404, 29);
    case Extension::kSPV_NV_tensor_addressing: return IR(4433, 25);
    case Extension::kSPV_NV_viewport_array2: return IR(4458, 23);
    case Extension::kSPV_QCOM_cooperative_matrix_conversion: return IR(4481, 39);
    case Extension::kSPV_QCOM_image_processing: return IR(4520, 26);
    case Extension::kSPV_QCOM_image_processing2: return IR(4546, 27);
    case Extension::kSPV_QCOM_tile_shading: return IR(4573, 22);
    case Extension::kSPV_VALIDATOR_ignore_type_decl_unique: return IR(4595, 38);
    default: break;
  }
  return {};
}

// Extension names and values, ordered by name
// The fields in order are:
//   name, indexing into kStrings
//   enum value
static const std::array<NameValue,161> kExtensionNames{{
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
    {IR(2894, 12), static_cast<uint32_t>(kSPV_KHR_fma)},
    {IR(2906, 36), static_cast<uint32_t>(kSPV_KHR_fragment_shader_barycentric)},
    {IR(2942, 30), static_cast<uint32_t>(kSPV_KHR_fragment_shading_rate)},
    {IR(2972, 28), static_cast<uint32_t>(kSPV_KHR_integer_dot_product)},
    {IR(3000, 21), static_cast<uint32_t>(kSPV_KHR_linkonce_odr)},
    {IR(3021, 30), static_cast<uint32_t>(kSPV_KHR_maximal_reconvergence)},
    {IR(3051, 18), static_cast<uint32_t>(kSPV_KHR_multiview)},
    {IR(3069, 35), static_cast<uint32_t>(kSPV_KHR_no_integer_wrap_decoration)},
    {IR(3104, 26), static_cast<uint32_t>(kSPV_KHR_non_semantic_info)},
    {IR(3130, 32), static_cast<uint32_t>(kSPV_KHR_physical_storage_buffer)},
    {IR(3162, 28), static_cast<uint32_t>(kSPV_KHR_post_depth_coverage)},
    {IR(3190, 21), static_cast<uint32_t>(kSPV_KHR_quad_control)},
    {IR(3211, 22), static_cast<uint32_t>(kSPV_KHR_ray_cull_mask)},
    {IR(3233, 18), static_cast<uint32_t>(kSPV_KHR_ray_query)},
    {IR(3251, 20), static_cast<uint32_t>(kSPV_KHR_ray_tracing)},
    {IR(3271, 35), static_cast<uint32_t>(kSPV_KHR_ray_tracing_position_fetch)},
    {IR(3306, 37), static_cast<uint32_t>(kSPV_KHR_relaxed_extended_instruction)},
    {IR(3343, 34), static_cast<uint32_t>(kSPV_KHR_shader_atomic_counter_ops)},
    {IR(3377, 22), static_cast<uint32_t>(kSPV_KHR_shader_ballot)},
    {IR(3399, 21), static_cast<uint32_t>(kSPV_KHR_shader_clock)},
    {IR(3420, 31), static_cast<uint32_t>(kSPV_KHR_shader_draw_parameters)},
    {IR(3451, 37), static_cast<uint32_t>(kSPV_KHR_storage_buffer_storage_class)},
    {IR(3488, 24), static_cast<uint32_t>(kSPV_KHR_subgroup_rotate)},
    {IR(3512, 38), static_cast<uint32_t>(kSPV_KHR_subgroup_uniform_control_flow)},
    {IR(3550, 22), static_cast<uint32_t>(kSPV_KHR_subgroup_vote)},
    {IR(3572, 29), static_cast<uint32_t>(kSPV_KHR_terminate_invocation)},
    {IR(3601, 35), static_cast<uint32_t>(kSPV_KHR_uniform_group_instructions)},
    {IR(3636, 25), static_cast<uint32_t>(kSPV_KHR_untyped_pointers)},
    {IR(3661, 26), static_cast<uint32_t>(kSPV_KHR_variable_pointers)},
    {IR(3687, 28), static_cast<uint32_t>(kSPV_KHR_vulkan_memory_model)},
    {IR(3715, 41), static_cast<uint32_t>(kSPV_KHR_workgroup_memory_explicit_layout)},
    {IR(3756, 38), static_cast<uint32_t>(kSPV_NVX_multiview_per_view_attributes)},
    {IR(3794, 24), static_cast<uint32_t>(kSPV_NV_bindless_texture)},
    {IR(3818, 38), static_cast<uint32_t>(kSPV_NV_cluster_acceleration_structure)},
    {IR(3856, 34), static_cast<uint32_t>(kSPV_NV_compute_shader_derivatives)},
    {IR(3890, 26), static_cast<uint32_t>(kSPV_NV_cooperative_matrix)},
    {IR(3916, 27), static_cast<uint32_t>(kSPV_NV_cooperative_matrix2)},
    {IR(3943, 26), static_cast<uint32_t>(kSPV_NV_cooperative_vector)},
    {IR(3969, 29), static_cast<uint32_t>(kSPV_NV_displacement_micromap)},
    {IR(3998, 35), static_cast<uint32_t>(kSPV_NV_fragment_shader_barycentric)},
    {IR(4033, 35), static_cast<uint32_t>(kSPV_NV_geometry_shader_passthrough)},
    {IR(4068, 28), static_cast<uint32_t>(kSPV_NV_linear_swept_spheres)},
    {IR(4096, 19), static_cast<uint32_t>(kSPV_NV_mesh_shader)},
    {IR(4115, 25), static_cast<uint32_t>(kSPV_NV_raw_access_chains)},
    {IR(4140, 19), static_cast<uint32_t>(kSPV_NV_ray_tracing)},
    {IR(4159, 31), static_cast<uint32_t>(kSPV_NV_ray_tracing_motion_blur)},
    {IR(4190, 37), static_cast<uint32_t>(kSPV_NV_sample_mask_override_coverage)},
    {IR(4227, 33), static_cast<uint32_t>(kSPV_NV_shader_atomic_fp16_vector)},
    {IR(4260, 30), static_cast<uint32_t>(kSPV_NV_shader_image_footprint)},
    {IR(4290, 33), static_cast<uint32_t>(kSPV_NV_shader_invocation_reorder)},
    {IR(4323, 26), static_cast<uint32_t>(kSPV_NV_shader_sm_builtins)},
    {IR(4349, 35), static_cast<uint32_t>(kSPV_NV_shader_subgroup_partitioned)},
    {IR(4384, 20), static_cast<uint32_t>(kSPV_NV_shading_rate)},
    {IR(4404, 29), static_cast<uint32_t>(kSPV_NV_stereo_view_rendering)},
    {IR(4433, 25), static_cast<uint32_t>(kSPV_NV_tensor_addressing)},
    {IR(4458, 23), static_cast<uint32_t>(kSPV_NV_viewport_array2)},
    {IR(4481, 39), static_cast<uint32_t>(kSPV_QCOM_cooperative_matrix_conversion)},
    {IR(4520, 26), static_cast<uint32_t>(kSPV_QCOM_image_processing)},
    {IR(4546, 27), static_cast<uint32_t>(kSPV_QCOM_image_processing2)},
    {IR(4573, 22), static_cast<uint32_t>(kSPV_QCOM_tile_shading)},
    {IR(4595, 38), static_cast<uint32_t>(kSPV_VALIDATOR_ignore_type_decl_unique)},
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
static const std::array<OperandDesc, 1189> kOperandsByValue{{
  {0,IR(0, 0),IR(4633, 9)/* ReadOnly */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {1,IR(0, 0),IR(4649, 10)/* WriteOnly */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {2,IR(0, 0),IR(4659, 10)/* ReadWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {0,IR(0, 0),IR(4669, 8)/* Logical */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {1,IR(0, 0),IR(4677, 11)/* Physical32 */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {2,IR(0, 0),IR(4698, 11)/* Physical64 */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {5348,IR(0, 0),IR(4709, 24)/* PhysicalStorageBuffer64 */,IR(0, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {0,IR(0, 0),IR(4791, 9)/* Position */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {1,IR(0, 0),IR(4807, 10)/* PointSize */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {3,IR(0, 0),IR(4817, 13)/* ClipDistance */,IR(0, 0),IR(4, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4,IR(0, 0),IR(4830, 13)/* CullDistance */,IR(0, 0),IR(5, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5,IR(0, 0),IR(4843, 9)/* VertexId */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {6,IR(0, 0),IR(4852, 11)/* InstanceId */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {7,IR(0, 0),IR(4863, 12)/* PrimitiveId */,IR(0, 0),IR(6, 6),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {8,IR(0, 0),IR(4953, 13)/* InvocationId */,IR(0, 0),IR(12, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {9,IR(0, 0),IR(4966, 6)/* Layer */,IR(0, 0),IR(14, 5),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {10,IR(0, 0),IR(5012, 14)/* ViewportIndex */,IR(0, 0),IR(19, 5),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {11,IR(0, 0),IR(5060, 15)/* TessLevelOuter */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {12,IR(0, 0),IR(5075, 15)/* TessLevelInner */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {13,IR(0, 0),IR(5090, 10)/* TessCoord */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {14,IR(0, 0),IR(5100, 14)/* PatchVertices */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {15,IR(0, 0),IR(5114, 10)/* FragCoord */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {16,IR(0, 0),IR(5124, 11)/* PointCoord */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {17,IR(0, 0),IR(5135, 12)/* FrontFacing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {18,IR(0, 0),IR(5147, 9)/* SampleId */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {19,IR(0, 0),IR(5174, 15)/* SamplePosition */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {20,IR(0, 0),IR(5189, 11)/* SampleMask */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {22,IR(0, 0),IR(5200, 10)/* FragDepth */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {23,IR(0, 0),IR(5210, 17)/* HelperInvocation */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {24,IR(0, 0),IR(5227, 14)/* NumWorkgroups */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {25,IR(0, 0),IR(5241, 14)/* WorkgroupSize */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {26,IR(0, 0),IR(5255, 12)/* WorkgroupId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {27,IR(0, 0),IR(5267, 18)/* LocalInvocationId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {28,IR(0, 0),IR(5285, 19)/* GlobalInvocationId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {29,IR(0, 0),IR(5304, 21)/* LocalInvocationIndex */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {30,IR(0, 0),IR(5325, 8)/* WorkDim */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {31,IR(0, 0),IR(5333, 11)/* GlobalSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {32,IR(0, 0),IR(5344, 22)/* EnqueuedWorkgroupSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {33,IR(0, 0),IR(5366, 13)/* GlobalOffset */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {34,IR(0, 0),IR(5379, 15)/* GlobalLinearId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {36,IR(0, 0),IR(5394, 13)/* SubgroupSize */,IR(0, 0),IR(26, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {37,IR(0, 0),IR(5441, 16)/* SubgroupMaxSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {38,IR(0, 0),IR(5457, 13)/* NumSubgroups */,IR(0, 0),IR(29, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {39,IR(0, 0),IR(5470, 21)/* NumEnqueuedSubgroups */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {40,IR(0, 0),IR(5491, 11)/* SubgroupId */,IR(0, 0),IR(29, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {41,IR(0, 0),IR(5502, 26)/* SubgroupLocalInvocationId */,IR(0, 0),IR(26, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {42,IR(0, 0),IR(5528, 12)/* VertexIndex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {43,IR(0, 0),IR(5540, 14)/* InstanceIndex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4160,IR(0, 0),IR(5554, 10)/* CoreIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4161,IR(0, 0),IR(5580, 13)/* CoreCountARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4162,IR(0, 0),IR(5593, 13)/* CoreMaxIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4163,IR(0, 0),IR(5606, 10)/* WarpIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4164,IR(0, 0),IR(5616, 13)/* WarpMaxIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4416,IR(0, 0),IR(5629, 15)/* SubgroupEqMask */,IR(1, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4417,IR(0, 0),IR(5684, 15)/* SubgroupGeMask */,IR(2, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4418,IR(0, 0),IR(5717, 15)/* SubgroupGtMask */,IR(3, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4419,IR(0, 0),IR(5750, 15)/* SubgroupLeMask */,IR(4, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4420,IR(0, 0),IR(5783, 15)/* SubgroupLtMask */,IR(5, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4424,IR(0, 0),IR(5816, 11)/* BaseVertex */,IR(0, 0),IR(34, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4425,IR(0, 0),IR(5842, 13)/* BaseInstance */,IR(0, 0),IR(34, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4426,IR(0, 0),IR(5855, 10)/* DrawIndex */,IR(0, 0),IR(35, 3),IR(4, 3),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4432,IR(0, 0),IR(5865, 24)/* PrimitiveShadingRateKHR */,IR(0, 0),IR(38, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4438,IR(0, 0),IR(5912, 12)/* DeviceIndex */,IR(0, 0),IR(39, 1),IR(8, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4440,IR(0, 0),IR(5936, 10)/* ViewIndex */,IR(0, 0),IR(40, 1),IR(9, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4444,IR(0, 0),IR(5956, 15)/* ShadingRateKHR */,IR(0, 0),IR(38, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4492,IR(0, 0),IR(5971, 15)/* TileOffsetQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4493,IR(0, 0),IR(6002, 18)/* TileDimensionQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4494,IR(0, 0),IR(6020, 18)/* TileApronSizeQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4992,IR(0, 0),IR(6038, 20)/* BaryCoordNoPerspAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4993,IR(0, 0),IR(6058, 28)/* BaryCoordNoPerspCentroidAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4994,IR(0, 0),IR(6086, 26)/* BaryCoordNoPerspSampleAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4995,IR(0, 0),IR(6112, 19)/* BaryCoordSmoothAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4996,IR(0, 0),IR(6131, 27)/* BaryCoordSmoothCentroidAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4997,IR(0, 0),IR(6158, 25)/* BaryCoordSmoothSampleAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4998,IR(0, 0),IR(6183, 22)/* BaryCoordPullModelAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5014,IR(0, 0),IR(6205, 18)/* FragStencilRefEXT */,IR(0, 0),IR(42, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5021,IR(0, 0),IR(6240, 29)/* RemainingRecursionLevelsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5073,IR(0, 0),IR(6287, 16)/* ShaderIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5253,IR(0, 0),IR(6303, 15)/* ViewportMaskNV */,IR(0, 0),IR(44, 2),IR(12, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5257,IR(0, 0),IR(6339, 20)/* SecondaryPositionNV */,IR(0, 0),IR(46, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5258,IR(0, 0),IR(6378, 24)/* SecondaryViewportMaskNV */,IR(0, 0),IR(46, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5261,IR(0, 0),IR(6402, 18)/* PositionPerViewNV */,IR(0, 0),IR(47, 2),IR(15, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5262,IR(0, 0),IR(6440, 22)/* ViewportMaskPerViewNV */,IR(0, 0),IR(47, 2),IR(15, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5264,IR(0, 0),IR(6462, 16)/* FullyCoveredEXT */,IR(0, 0),IR(49, 1),IR(17, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5274,IR(0, 0),IR(6502, 12)/* TaskCountNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5275,IR(0, 0),IR(6514, 17)/* PrimitiveCountNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5276,IR(0, 0),IR(6531, 19)/* PrimitiveIndicesNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5277,IR(0, 0),IR(6550, 22)/* ClipDistancePerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5278,IR(0, 0),IR(6572, 22)/* CullDistancePerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5279,IR(0, 0),IR(6594, 15)/* LayerPerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5280,IR(0, 0),IR(6609, 16)/* MeshViewCountNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5281,IR(0, 0),IR(6625, 18)/* MeshViewIndicesNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5286,IR(0, 0),IR(6643, 13)/* BaryCoordKHR */,IR(6, 1),IR(51, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5287,IR(0, 0),IR(6691, 20)/* BaryCoordNoPerspKHR */,IR(7, 1),IR(51, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5292,IR(0, 0),IR(6730, 12)/* FragSizeEXT */,IR(8, 1),IR(52, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5293,IR(0, 0),IR(6776, 23)/* FragInvocationCountEXT */,IR(9, 1),IR(52, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5294,IR(0, 0),IR(6821, 25)/* PrimitivePointIndicesEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5295,IR(0, 0),IR(6846, 24)/* PrimitiveLineIndicesEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5296,IR(0, 0),IR(6870, 28)/* PrimitiveTriangleIndicesEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5299,IR(0, 0),IR(6898, 17)/* CullPrimitiveEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5319,IR(0, 0),IR(6915, 12)/* LaunchIdKHR */,IR(10, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5320,IR(0, 0),IR(6938, 14)/* LaunchSizeKHR */,IR(11, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5321,IR(0, 0),IR(6965, 18)/* WorldRayOriginKHR */,IR(12, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5322,IR(0, 0),IR(7000, 21)/* WorldRayDirectionKHR */,IR(13, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5323,IR(0, 0),IR(7041, 19)/* ObjectRayOriginKHR */,IR(14, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5324,IR(0, 0),IR(7078, 22)/* ObjectRayDirectionKHR */,IR(15, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5325,IR(0, 0),IR(7121, 11)/* RayTminKHR */,IR(16, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5326,IR(0, 0),IR(7142, 11)/* RayTmaxKHR */,IR(17, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5327,IR(0, 0),IR(7163, 23)/* InstanceCustomIndexKHR */,IR(18, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5330,IR(0, 0),IR(7208, 17)/* ObjectToWorldKHR */,IR(19, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5331,IR(0, 0),IR(7241, 17)/* WorldToObjectKHR */,IR(20, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5332,IR(0, 0),IR(7274, 7)/* HitTNV */,IR(0, 0),IR(56, 1),IR(26, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5333,IR(0, 0),IR(7281, 11)/* HitKindKHR */,IR(21, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5334,IR(0, 0),IR(7302, 17)/* CurrentRayTimeNV */,IR(0, 0),IR(57, 1),IR(27, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5335,IR(0, 0),IR(7342, 30)/* HitTriangleVertexPositionsKHR */,IR(0, 0),IR(58, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5337,IR(0, 0),IR(7399, 34)/* HitMicroTriangleVertexPositionsNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5344,IR(0, 0),IR(7466, 37)/* HitMicroTriangleVertexBarycentricsNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5351,IR(0, 0),IR(7503, 20)/* IncomingRayFlagsKHR */,IR(22, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5352,IR(0, 0),IR(7542, 20)/* RayGeometryIndexKHR */,IR(0, 0),IR(60, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5359,IR(0, 0),IR(7562, 14)/* HitIsSphereNV */,IR(0, 0),IR(61, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5360,IR(0, 0),IR(7604, 11)/* HitIsLSSNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5361,IR(0, 0),IR(7654, 20)/* HitSpherePositionNV */,IR(0, 0),IR(61, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5374,IR(0, 0),IR(7674, 13)/* WarpsPerSMNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5375,IR(0, 0),IR(7706, 10)/* SMCountNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5376,IR(0, 0),IR(7716, 9)/* WarpIDNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5377,IR(0, 0),IR(7725, 7)/* SMIDNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5396,IR(0, 0),IR(7732, 18)/* HitLSSPositionsNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5405,IR(0, 0),IR(7750, 34)/* HitKindFrontFacingMicroTriangleNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5406,IR(0, 0),IR(7784, 33)/* HitKindBackFacingMicroTriangleNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5420,IR(0, 0),IR(7817, 18)/* HitSphereRadiusNV */,IR(0, 0),IR(61, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5421,IR(0, 0),IR(7835, 14)/* HitLSSRadiiNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5436,IR(0, 0),IR(7849, 12)/* ClusterIDNV */,IR(0, 0),IR(64, 1),IR(31, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {6021,IR(0, 0),IR(7902, 12)/* CullMaskKHR */,IR(0, 0),IR(65, 1),IR(32, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {0,IR(0, 0),IR(7929, 7)/* Matrix */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {1,IR(0, 0),IR(4800, 7)/* Shader */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {2,IR(0, 0),IR(4875, 9)/* Geometry */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {3,IR(0, 0),IR(4884, 13)/* Tessellation */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4,IR(0, 0),IR(4688, 10)/* Addresses */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5,IR(0, 0),IR(7936, 8)/* Linkage */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6,IR(0, 0),IR(4642, 7)/* Kernel */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {7,IR(0, 0),IR(7944, 9)/* Vector16 */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {8,IR(0, 0),IR(7953, 14)/* Float16Buffer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {9,IR(0, 0),IR(7967, 8)/* Float16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {10,IR(0, 0),IR(7975, 8)/* Float64 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {11,IR(0, 0),IR(7983, 6)/* Int64 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {12,IR(0, 0),IR(7989, 13)/* Int64Atomics */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {13,IR(0, 0),IR(8002, 11)/* ImageBasic */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {14,IR(0, 0),IR(8013, 15)/* ImageReadWrite */,IR(0, 0),IR(68, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {15,IR(0, 0),IR(8028, 12)/* ImageMipmap */,IR(0, 0),IR(68, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {17,IR(0, 0),IR(8040, 6)/* Pipes */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {18,IR(0, 0),IR(8046, 7)/* Groups */,IR(0, 0),IR(1, 0),IR(33, 1),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {19,IR(0, 0),IR(8053, 14)/* DeviceEnqueue */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {20,IR(0, 0),IR(8067, 15)/* LiteralSampler */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {21,IR(0, 0),IR(8082, 14)/* AtomicStorage */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {22,IR(0, 0),IR(8096, 6)/* Int16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {23,IR(0, 0),IR(8102, 22)/* TessellationPointSize */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {24,IR(0, 0),IR(8124, 18)/* GeometryPointSize */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {25,IR(0, 0),IR(8142, 20)/* ImageGatherExtended */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {27,IR(0, 0),IR(8162, 24)/* StorageImageMultisample */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {28,IR(0, 0),IR(8186, 34)/* UniformBufferArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {29,IR(0, 0),IR(8220, 33)/* SampledImageArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {30,IR(0, 0),IR(8253, 34)/* StorageBufferArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {31,IR(0, 0),IR(8287, 33)/* StorageImageArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {32,IR(0, 0),IR(4817, 13)/* ClipDistance */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {33,IR(0, 0),IR(4830, 13)/* CullDistance */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {34,IR(0, 0),IR(8320, 15)/* ImageCubeArray */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {35,IR(0, 0),IR(5156, 18)/* SampleRateShading */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {36,IR(0, 0),IR(8352, 10)/* ImageRect */,IR(0, 0),IR(71, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {37,IR(0, 0),IR(8362, 12)/* SampledRect */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {38,IR(0, 0),IR(8374, 15)/* GenericPointer */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {39,IR(0, 0),IR(8389, 5)/* Int8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {40,IR(0, 0),IR(8394, 16)/* InputAttachment */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {41,IR(0, 0),IR(8410, 16)/* SparseResidency */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {42,IR(0, 0),IR(8426, 7)/* MinLod */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {43,IR(0, 0),IR(8433, 10)/* Sampled1D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {44,IR(0, 0),IR(8443, 8)/* Image1D */,IR(0, 0),IR(72, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {45,IR(0, 0),IR(8335, 17)/* SampledCubeArray */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {46,IR(0, 0),IR(8451, 14)/* SampledBuffer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {47,IR(0, 0),IR(8465, 12)/* ImageBuffer */,IR(0, 0),IR(73, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {48,IR(0, 0),IR(8477, 13)/* ImageMSArray */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {49,IR(0, 0),IR(8490, 28)/* StorageImageExtendedFormats */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {50,IR(0, 0),IR(8518, 11)/* ImageQuery */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {51,IR(0, 0),IR(8529, 18)/* DerivativeControl */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {52,IR(0, 0),IR(8547, 22)/* InterpolationFunction */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {53,IR(0, 0),IR(8569, 18)/* TransformFeedback */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {54,IR(0, 0),IR(8587, 16)/* GeometryStreams */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {55,IR(0, 0),IR(8603, 30)/* StorageImageReadWithoutFormat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {56,IR(0, 0),IR(8633, 31)/* StorageImageWriteWithoutFormat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {57,IR(0, 0),IR(5026, 14)/* MultiViewport */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {58,IR(0, 0),IR(8664, 17)/* SubgroupDispatch */,IR(0, 0),IR(74, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {59,IR(0, 0),IR(8681, 13)/* NamedBarrier */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {60,IR(0, 0),IR(8694, 12)/* PipeStorage */,IR(0, 0),IR(75, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {61,IR(0, 0),IR(5407, 16)/* GroupNonUniform */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {62,IR(0, 0),IR(8706, 20)/* GroupNonUniformVote */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {63,IR(0, 0),IR(8726, 26)/* GroupNonUniformArithmetic */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {64,IR(0, 0),IR(5662, 22)/* GroupNonUniformBallot */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {65,IR(0, 0),IR(8752, 23)/* GroupNonUniformShuffle */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {66,IR(0, 0),IR(8775, 31)/* GroupNonUniformShuffleRelative */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {67,IR(0, 0),IR(8806, 25)/* GroupNonUniformClustered */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {68,IR(0, 0),IR(8831, 20)/* GroupNonUniformQuad */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {69,IR(0, 0),IR(4972, 12)/* ShaderLayer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {70,IR(0, 0),IR(5040, 20)/* ShaderViewportIndex */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {71,IR(0, 0),IR(8851, 18)/* UniformDecoration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4165,IR(0, 0),IR(5564, 16)/* CoreBuiltinsARM */,IR(0, 0),IR(1, 0),IR(34, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4166,IR(0, 0),IR(8869, 28)/* TileImageColorReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4167,IR(0, 0),IR(8897, 28)/* TileImageDepthReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4168,IR(0, 0),IR(8925, 30)/* TileImageStencilReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4174,IR(0, 0),IR(8955, 11)/* TensorsARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4175,IR(0, 0),IR(8966, 37)/* StorageTensorArrayDynamicIndexingARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4176,IR(0, 0),IR(9003, 40)/* StorageTensorArrayNonUniformIndexingARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4191,IR(0, 0),IR(9043, 9)/* GraphARM */,IR(0, 0),IR(1, 0),IR(37, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4201,IR(0, 0),IR(9052, 28)/* CooperativeMatrixLayoutsARM */,IR(0, 0),IR(1, 0),IR(38, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4212,IR(0, 0),IR(9080, 10)/* Float8EXT */,IR(0, 0),IR(1, 0),IR(39, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4213,IR(0, 0),IR(9090, 27)/* Float8CooperativeMatrixEXT */,IR(0, 0),IR(77, 2),IR(39, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4422,IR(0, 0),IR(5889, 23)/* FragmentShadingRateKHR */,IR(0, 0),IR(3, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4423,IR(0, 0),IR(5423, 18)/* SubgroupBallotKHR */,IR(0, 0),IR(1, 0),IR(2, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4427,IR(0, 0),IR(5827, 15)/* DrawParameters */,IR(0, 0),IR(3, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4428,IR(0, 0),IR(9138, 33)/* WorkgroupMemoryExplicitLayoutKHR */,IR(0, 0),IR(3, 1),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4429,IR(0, 0),IR(9171, 43)/* WorkgroupMemoryExplicitLayout8BitAccessKHR */,IR(0, 0),IR(79, 1),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4430,IR(0, 0),IR(9214, 44)/* WorkgroupMemoryExplicitLayout16BitAccessKHR */,IR(0, 0),IR(79, 1),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4431,IR(0, 0),IR(9258, 16)/* SubgroupVoteKHR */,IR(0, 0),IR(1, 0),IR(41, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4433,IR(0, 0),IR(9274, 25)/* StorageBuffer16BitAccess */,IR(23, 1),IR(1, 0),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4434,IR(0, 0),IR(9327, 35)/* UniformAndStorageBuffer16BitAccess */,IR(24, 1),IR(80, 1),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4435,IR(0, 0),IR(9379, 22)/* StoragePushConstant16 */,IR(0, 0),IR(1, 0),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4436,IR(0, 0),IR(9401, 21)/* StorageInputOutput16 */,IR(0, 0),IR(1, 0),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4437,IR(0, 0),IR(5924, 12)/* DeviceGroup */,IR(0, 0),IR(1, 0),IR(8, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4439,IR(0, 0),IR(5946, 10)/* MultiView */,IR(0, 0),IR(3, 1),IR(9, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4441,IR(0, 0),IR(9422, 30)/* VariablePointersStorageBuffer */,IR(0, 0),IR(3, 1),IR(43, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4442,IR(0, 0),IR(9452, 17)/* VariablePointers */,IR(0, 0),IR(81, 1),IR(43, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4445,IR(0, 0),IR(9469, 17)/* AtomicStorageOps */,IR(0, 0),IR(82, 1),IR(44, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4447,IR(0, 0),IR(9486, 28)/* SampleMaskPostDepthCoverage */,IR(0, 0),IR(1, 0),IR(45, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4448,IR(0, 0),IR(9514, 24)/* StorageBuffer8BitAccess */,IR(0, 0),IR(1, 0),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4449,IR(0, 0),IR(9538, 34)/* UniformAndStorageBuffer8BitAccess */,IR(0, 0),IR(83, 1),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4450,IR(0, 0),IR(9572, 21)/* StoragePushConstant8 */,IR(0, 0),IR(1, 0),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4464,IR(0, 0),IR(9593, 15)/* DenormPreserve */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4465,IR(0, 0),IR(9608, 18)/* DenormFlushToZero */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4466,IR(0, 0),IR(9626, 25)/* SignedZeroInfNanPreserve */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4467,IR(0, 0),IR(9651, 16)/* RoundingModeRTE */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4468,IR(0, 0),IR(9667, 16)/* RoundingModeRTZ */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4471,IR(0, 0),IR(9683, 23)/* RayQueryProvisionalKHR */,IR(0, 0),IR(3, 1),IR(48, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4472,IR(0, 0),IR(9706, 12)/* RayQueryKHR */,IR(0, 0),IR(3, 1),IR(48, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4473,IR(0, 0),IR(9718, 19)/* UntypedPointersKHR */,IR(0, 0),IR(1, 0),IR(49, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4478,IR(0, 0),IR(9737, 32)/* RayTraversalPrimitiveCullingKHR */,IR(0, 0),IR(84, 2),IR(50, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4479,IR(0, 0),IR(4910, 14)/* RayTracingKHR */,IR(0, 0),IR(3, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4484,IR(0, 0),IR(9769, 26)/* TextureSampleWeightedQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4485,IR(0, 0),IR(9795, 21)/* TextureBoxFilterQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4486,IR(0, 0),IR(9816, 22)/* TextureBlockMatchQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4495,IR(0, 0),IR(5986, 16)/* TileShadingQCOM */,IR(0, 0),IR(3, 1),IR(53, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4496,IR(0, 0),IR(9838, 32)/* CooperativeMatrixConversionQCOM */,IR(0, 0),IR(86, 1),IR(54, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4498,IR(0, 0),IR(9870, 23)/* TextureBlockMatch2QCOM */,IR(0, 0),IR(1, 0),IR(55, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5008,IR(0, 0),IR(9893, 16)/* Float16ImageAMD */,IR(0, 0),IR(3, 1),IR(56, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5009,IR(0, 0),IR(9909, 22)/* ImageGatherBiasLodAMD */,IR(0, 0),IR(3, 1),IR(57, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5010,IR(0, 0),IR(9931, 16)/* FragmentMaskAMD */,IR(0, 0),IR(3, 1),IR(58, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5013,IR(0, 0),IR(6223, 17)/* StencilExportEXT */,IR(0, 0),IR(3, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5015,IR(0, 0),IR(9947, 21)/* ImageReadWriteLodAMD */,IR(0, 0),IR(3, 1),IR(59, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5016,IR(0, 0),IR(9968, 14)/* Int64ImageEXT */,IR(0, 0),IR(3, 1),IR(60, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5055,IR(0, 0),IR(9982, 15)/* ShaderClockKHR */,IR(0, 0),IR(1, 0),IR(61, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5067,IR(0, 0),IR(6269, 18)/* ShaderEnqueueAMDX */,IR(0, 0),IR(3, 1),IR(62, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5087,IR(0, 0),IR(9997, 15)/* QuadControlKHR */,IR(0, 0),IR(1, 0),IR(63, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5112,IR(0, 0),IR(10012, 14)/* Int4TypeINTEL */,IR(0, 0),IR(1, 0),IR(64, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5114,IR(0, 0),IR(10026, 27)/* Int4CooperativeMatrixINTEL */,IR(0, 0),IR(87, 2),IR(64, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5116,IR(0, 0),IR(10053, 16)/* BFloat16TypeKHR */,IR(0, 0),IR(1, 0),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5117,IR(0, 0),IR(10069, 22)/* BFloat16DotProductKHR */,IR(0, 0),IR(89, 1),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5118,IR(0, 0),IR(10091, 29)/* BFloat16CooperativeMatrixKHR */,IR(0, 0),IR(90, 2),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5249,IR(0, 0),IR(10120, 29)/* SampleMaskOverrideCoverageNV */,IR(0, 0),IR(25, 1),IR(66, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5251,IR(0, 0),IR(10149, 28)/* GeometryShaderPassthroughNV */,IR(0, 0),IR(69, 1),IR(67, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5254,IR(0, 0),IR(4984, 28)/* ShaderViewportIndexLayerEXT */,IR(25, 1),IR(92, 1),IR(68, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5255,IR(0, 0),IR(6318, 21)/* ShaderViewportMaskNV */,IR(0, 0),IR(93, 1),IR(70, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5259,IR(0, 0),IR(6359, 19)/* ShaderStereoViewNV */,IR(0, 0),IR(94, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5260,IR(0, 0),IR(6420, 20)/* PerViewAttributesNV */,IR(0, 0),IR(40, 1),IR(71, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5265,IR(0, 0),IR(6478, 24)/* FragmentFullyCoveredEXT */,IR(0, 0),IR(3, 1),IR(17, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5266,IR(0, 0),IR(4924, 14)/* MeshShadingNV */,IR(0, 0),IR(3, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5282,IR(0, 0),IR(10204, 17)/* ImageFootprintNV */,IR(0, 0),IR(1, 0),IR(72, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5283,IR(0, 0),IR(4938, 15)/* MeshShadingEXT */,IR(0, 0),IR(3, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5284,IR(0, 0),IR(6668, 23)/* FragmentBarycentricKHR */,IR(26, 1),IR(1, 0),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5288,IR(0, 0),IR(10243, 31)/* ComputeDerivativeGroupQuadsKHR */,IR(27, 1),IR(3, 1),IR(73, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5291,IR(0, 0),IR(6757, 19)/* FragmentDensityEXT */,IR(28, 1),IR(3, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5297,IR(0, 0),IR(10318, 29)/* GroupNonUniformPartitionedNV */,IR(0, 0),IR(1, 0),IR(75, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5301,IR(0, 0),IR(10347, 17)/* ShaderNonUniform */,IR(29, 1),IR(3, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5302,IR(0, 0),IR(10384, 23)/* RuntimeDescriptorArray */,IR(30, 1),IR(3, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5303,IR(0, 0),IR(10433, 36)/* InputAttachmentArrayDynamicIndexing */,IR(31, 1),IR(95, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5304,IR(0, 0),IR(10508, 39)/* UniformTexelBufferArrayDynamicIndexing */,IR(32, 1),IR(73, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5305,IR(0, 0),IR(10589, 39)/* StorageTexelBufferArrayDynamicIndexing */,IR(33, 1),IR(96, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5306,IR(0, 0),IR(10670, 37)/* UniformBufferArrayNonUniformIndexing */,IR(34, 1),IR(97, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5307,IR(0, 0),IR(10747, 36)/* SampledImageArrayNonUniformIndexing */,IR(35, 1),IR(97, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5308,IR(0, 0),IR(10822, 37)/* StorageBufferArrayNonUniformIndexing */,IR(36, 1),IR(97, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5309,IR(0, 0),IR(10899, 36)/* StorageImageArrayNonUniformIndexing */,IR(37, 1),IR(97, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5310,IR(0, 0),IR(10974, 39)/* InputAttachmentArrayNonUniformIndexing */,IR(38, 1),IR(98, 2),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5311,IR(0, 0),IR(11055, 42)/* UniformTexelBufferArrayNonUniformIndexing */,IR(39, 1),IR(100, 2),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5312,IR(0, 0),IR(11142, 42)/* StorageTexelBufferArrayNonUniformIndexing */,IR(40, 1),IR(102, 2),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5336,IR(0, 0),IR(7372, 27)/* RayTracingPositionFetchKHR */,IR(0, 0),IR(3, 1),IR(77, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5340,IR(0, 0),IR(4897, 13)/* RayTracingNV */,IR(0, 0),IR(3, 1),IR(26, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5341,IR(0, 0),IR(7319, 23)/* RayTracingMotionBlurNV */,IR(0, 0),IR(3, 1),IR(27, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5345,IR(0, 0),IR(11229, 18)/* VulkanMemoryModel */,IR(41, 1),IR(1, 0),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5346,IR(0, 0),IR(11268, 29)/* VulkanMemoryModelDeviceScope */,IR(42, 1),IR(1, 0),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5347,IR(0, 0),IR(4760, 31)/* PhysicalStorageBufferAddresses */,IR(43, 1),IR(3, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5350,IR(0, 0),IR(11363, 32)/* ComputeDerivativeGroupLinearKHR */,IR(44, 1),IR(3, 1),IR(73, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5353,IR(0, 0),IR(11426, 25)/* RayTracingProvisionalKHR */,IR(0, 0),IR(3, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5357,IR(0, 0),IR(11451, 20)/* CooperativeMatrixNV */,IR(0, 0),IR(3, 1),IR(79, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5363,IR(0, 0),IR(11471, 33)/* FragmentShaderSampleInterlockEXT */,IR(0, 0),IR(3, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5372,IR(0, 0),IR(11504, 38)/* FragmentShaderShadingRateInterlockEXT */,IR(0, 0),IR(3, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5373,IR(0, 0),IR(7687, 19)/* ShaderSMBuiltinsNV */,IR(0, 0),IR(3, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5378,IR(0, 0),IR(11542, 32)/* FragmentShaderPixelInterlockEXT */,IR(0, 0),IR(3, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5379,IR(0, 0),IR(11574, 25)/* DemoteToHelperInvocation */,IR(45, 1),IR(3, 1),IR(81, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5380,IR(0, 0),IR(11627, 23)/* DisplacementMicromapNV */,IR(0, 0),IR(3, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5381,IR(0, 0),IR(11650, 29)/* RayTracingOpacityMicromapEXT */,IR(0, 0),IR(3, 1),IR(83, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5383,IR(0, 0),IR(11679, 26)/* ShaderInvocationReorderNV */,IR(0, 0),IR(60, 1),IR(84, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5390,IR(0, 0),IR(11705, 18)/* BindlessTextureNV */,IR(0, 0),IR(1, 0),IR(85, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5391,IR(0, 0),IR(11723, 25)/* RayQueryPositionFetchKHR */,IR(0, 0),IR(3, 1),IR(77, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5394,IR(0, 0),IR(11748, 20)/* CooperativeVectorNV */,IR(0, 0),IR(1, 0),IR(86, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5404,IR(0, 0),IR(11768, 22)/* AtomicFloat16VectorNV */,IR(0, 0),IR(1, 0),IR(87, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5409,IR(0, 0),IR(7433, 33)/* RayTracingDisplacementMicromapNV */,IR(0, 0),IR(60, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5414,IR(0, 0),IR(11790, 18)/* RawAccessChainsNV */,IR(0, 0),IR(1, 0),IR(88, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5418,IR(0, 0),IR(7576, 28)/* RayTracingSpheresGeometryNV */,IR(0, 0),IR(1, 0),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5419,IR(0, 0),IR(7615, 39)/* RayTracingLinearSweptSpheresGeometryNV */,IR(0, 0),IR(1, 0),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5430,IR(0, 0),IR(11808, 30)/* CooperativeMatrixReductionsNV */,IR(0, 0),IR(1, 0),IR(89, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5431,IR(0, 0),IR(11838, 31)/* CooperativeMatrixConversionsNV */,IR(0, 0),IR(1, 0),IR(89, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5432,IR(0, 0),IR(11869, 40)/* CooperativeMatrixPerElementOperationsNV */,IR(0, 0),IR(1, 0),IR(89, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5433,IR(0, 0),IR(11909, 36)/* CooperativeMatrixTensorAddressingNV */,IR(0, 0),IR(1, 0),IR(89, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5434,IR(0, 0),IR(11945, 30)/* CooperativeMatrixBlockLoadsNV */,IR(0, 0),IR(1, 0),IR(89, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5435,IR(0, 0),IR(11975, 28)/* CooperativeVectorTrainingNV */,IR(0, 0),IR(1, 0),IR(86, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5437,IR(0, 0),IR(7861, 41)/* RayTracingClusterAccelerationStructureNV */,IR(0, 0),IR(60, 1),IR(31, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5439,IR(0, 0),IR(12003, 19)/* TensorAddressingNV */,IR(0, 0),IR(1, 0),IR(90, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5568,IR(0, 0),IR(12022, 21)/* SubgroupShuffleINTEL */,IR(0, 0),IR(1, 0),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5569,IR(0, 0),IR(12043, 27)/* SubgroupBufferBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5570,IR(0, 0),IR(12070, 26)/* SubgroupImageBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5579,IR(0, 0),IR(12096, 31)/* SubgroupImageMediaBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(92, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5582,IR(0, 0),IR(12127, 21)/* RoundToInfinityINTEL */,IR(0, 0),IR(1, 0),IR(93, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5583,IR(0, 0),IR(12148, 23)/* FloatingPointModeINTEL */,IR(0, 0),IR(1, 0),IR(93, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5584,IR(0, 0),IR(12171, 23)/* IntegerFunctions2INTEL */,IR(0, 0),IR(1, 0),IR(94, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5603,IR(0, 0),IR(12194, 22)/* FunctionPointersINTEL */,IR(0, 0),IR(1, 0),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5604,IR(0, 0),IR(12216, 24)/* IndirectReferencesINTEL */,IR(0, 0),IR(1, 0),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5606,IR(0, 0),IR(12240, 9)/* AsmINTEL */,IR(0, 0),IR(1, 0),IR(96, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5612,IR(0, 0),IR(12249, 23)/* AtomicFloat32MinMaxEXT */,IR(0, 0),IR(1, 0),IR(97, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5613,IR(0, 0),IR(12272, 23)/* AtomicFloat64MinMaxEXT */,IR(0, 0),IR(1, 0),IR(97, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5616,IR(0, 0),IR(12295, 23)/* AtomicFloat16MinMaxEXT */,IR(0, 0),IR(1, 0),IR(97, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5617,IR(0, 0),IR(12318, 19)/* VectorComputeINTEL */,IR(0, 0),IR(104, 1),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5619,IR(0, 0),IR(12337, 15)/* VectorAnyINTEL */,IR(0, 0),IR(1, 0),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5629,IR(0, 0),IR(12352, 16)/* ExpectAssumeKHR */,IR(0, 0),IR(1, 0),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5696,IR(0, 0),IR(12368, 33)/* SubgroupAvcMotionEstimationINTEL */,IR(0, 0),IR(1, 0),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5697,IR(0, 0),IR(12401, 38)/* SubgroupAvcMotionEstimationIntraINTEL */,IR(0, 0),IR(1, 0),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5698,IR(0, 0),IR(12439, 39)/* SubgroupAvcMotionEstimationChromaINTEL */,IR(0, 0),IR(1, 0),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5817,IR(0, 0),IR(12478, 25)/* VariableLengthArrayINTEL */,IR(0, 0),IR(1, 0),IR(101, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5821,IR(0, 0),IR(12503, 26)/* FunctionFloatControlINTEL */,IR(0, 0),IR(1, 0),IR(93, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5824,IR(0, 0),IR(12529, 26)/* FPGAMemoryAttributesINTEL */,IR(0, 0),IR(1, 0),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5837,IR(0, 0),IR(12555, 20)/* FPFastMathModeINTEL */,IR(0, 0),IR(0, 1),IR(103, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5844,IR(0, 0),IR(12575, 32)/* ArbitraryPrecisionIntegersINTEL */,IR(0, 0),IR(1, 0),IR(104, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5845,IR(0, 0),IR(12607, 37)/* ArbitraryPrecisionFloatingPointINTEL */,IR(0, 0),IR(1, 0),IR(105, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5886,IR(0, 0),IR(12644, 30)/* UnstructuredLoopControlsINTEL */,IR(0, 0),IR(1, 0),IR(106, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5888,IR(0, 0),IR(12674, 22)/* FPGALoopControlsINTEL */,IR(0, 0),IR(1, 0),IR(107, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5892,IR(0, 0),IR(12696, 22)/* KernelAttributesINTEL */,IR(0, 0),IR(1, 0),IR(108, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5897,IR(0, 0),IR(12718, 26)/* FPGAKernelAttributesINTEL */,IR(0, 0),IR(1, 0),IR(108, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5898,IR(0, 0),IR(12744, 24)/* FPGAMemoryAccessesINTEL */,IR(0, 0),IR(1, 0),IR(109, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5904,IR(0, 0),IR(12768, 27)/* FPGAClusterAttributesINTEL */,IR(0, 0),IR(1, 0),IR(110, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5906,IR(0, 0),IR(12795, 14)/* LoopFuseINTEL */,IR(0, 0),IR(1, 0),IR(111, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5908,IR(0, 0),IR(12809, 20)/* FPGADSPControlINTEL */,IR(0, 0),IR(1, 0),IR(112, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5910,IR(0, 0),IR(12829, 26)/* MemoryAccessAliasingINTEL */,IR(0, 0),IR(1, 0),IR(113, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5916,IR(0, 0),IR(12855, 40)/* FPGAInvocationPipeliningAttributesINTEL */,IR(0, 0),IR(1, 0),IR(114, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5920,IR(0, 0),IR(12895, 24)/* FPGABufferLocationINTEL */,IR(0, 0),IR(1, 0),IR(115, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5922,IR(0, 0),IR(12919, 34)/* ArbitraryPrecisionFixedPointINTEL */,IR(0, 0),IR(1, 0),IR(116, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5935,IR(0, 0),IR(12953, 23)/* USMStorageClassesINTEL */,IR(0, 0),IR(1, 0),IR(117, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5939,IR(0, 0),IR(12976, 29)/* RuntimeAlignedAttributeINTEL */,IR(0, 0),IR(1, 0),IR(118, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5943,IR(0, 0),IR(13005, 13)/* IOPipesINTEL */,IR(0, 0),IR(1, 0),IR(119, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5945,IR(0, 0),IR(13018, 19)/* BlockingPipesINTEL */,IR(0, 0),IR(1, 0),IR(120, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5948,IR(0, 0),IR(13037, 13)/* FPGARegINTEL */,IR(0, 0),IR(1, 0),IR(121, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6016,IR(0, 0),IR(13050, 19)/* DotProductInputAll */,IR(46, 1),IR(1, 0),IR(122, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6017,IR(0, 0),IR(13091, 22)/* DotProductInput4x8Bit */,IR(47, 1),IR(105, 1),IR(122, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6018,IR(0, 0),IR(13138, 28)/* DotProductInput4x8BitPacked */,IR(48, 1),IR(1, 0),IR(122, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6019,IR(0, 0),IR(13197, 11)/* DotProduct */,IR(49, 1),IR(1, 0),IR(122, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6020,IR(0, 0),IR(7914, 15)/* RayCullMaskKHR */,IR(0, 0),IR(1, 0),IR(32, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6022,IR(0, 0),IR(9117, 21)/* CooperativeMatrixKHR */,IR(0, 0),IR(1, 0),IR(123, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6024,IR(0, 0),IR(13222, 24)/* ReplicatedCompositesEXT */,IR(0, 0),IR(1, 0),IR(124, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6025,IR(0, 0),IR(13246, 16)/* BitInstructions */,IR(0, 0),IR(1, 0),IR(125, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6026,IR(0, 0),IR(13262, 25)/* GroupNonUniformRotateKHR */,IR(0, 0),IR(76, 1),IR(126, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6029,IR(0, 0),IR(13287, 15)/* FloatControls2 */,IR(0, 0),IR(1, 0),IR(127, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6030,IR(0, 0),IR(13302, 7)/* FMAKHR */,IR(0, 0),IR(1, 0),IR(128, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6033,IR(0, 0),IR(13309, 20)/* AtomicFloat32AddEXT */,IR(0, 0),IR(1, 0),IR(129, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6034,IR(0, 0),IR(13329, 20)/* AtomicFloat64AddEXT */,IR(0, 0),IR(1, 0),IR(129, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6089,IR(0, 0),IR(13349, 20)/* LongCompositesINTEL */,IR(0, 0),IR(1, 0),IR(130, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6094,IR(0, 0),IR(13369, 11)/* OptNoneEXT */,IR(50, 1),IR(1, 0),IR(131, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6095,IR(0, 0),IR(13393, 20)/* AtomicFloat16AddEXT */,IR(0, 0),IR(1, 0),IR(133, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6114,IR(0, 0),IR(13413, 21)/* DebugInfoModuleINTEL */,IR(0, 0),IR(1, 0),IR(134, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6115,IR(0, 0),IR(13434, 24)/* BFloat16ConversionINTEL */,IR(0, 0),IR(1, 0),IR(135, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6141,IR(0, 0),IR(13458, 18)/* SplitBarrierINTEL */,IR(0, 0),IR(1, 0),IR(136, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6144,IR(0, 0),IR(13476, 19)/* ArithmeticFenceEXT */,IR(0, 0),IR(1, 0),IR(137, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6150,IR(0, 0),IR(13495, 29)/* FPGAClusterAttributesV2INTEL */,IR(0, 0),IR(106, 1),IR(110, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6161,IR(0, 0),IR(13524, 28)/* FPGAKernelAttributesv2INTEL */,IR(0, 0),IR(107, 1),IR(108, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6162,IR(0, 0),IR(13552, 18)/* TaskSequenceINTEL */,IR(0, 0),IR(1, 0),IR(138, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6169,IR(0, 0),IR(13570, 16)/* FPMaxErrorINTEL */,IR(0, 0),IR(1, 0),IR(139, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6171,IR(0, 0),IR(13586, 24)/* FPGALatencyControlINTEL */,IR(0, 0),IR(1, 0),IR(140, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6174,IR(0, 0),IR(13610, 28)/* FPGAArgumentInterfacesINTEL */,IR(0, 0),IR(1, 0),IR(141, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6187,IR(0, 0),IR(13638, 30)/* GlobalVariableHostAccessINTEL */,IR(0, 0),IR(1, 0),IR(142, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6189,IR(0, 0),IR(13668, 35)/* GlobalVariableFPGADecorationsINTEL */,IR(0, 0),IR(1, 0),IR(143, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6220,IR(0, 0),IR(13703, 28)/* SubgroupBufferPrefetchINTEL */,IR(0, 0),IR(1, 0),IR(144, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6228,IR(0, 0),IR(13731, 23)/* Subgroup2DBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(145, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6229,IR(0, 0),IR(13754, 30)/* Subgroup2DBlockTransformINTEL */,IR(0, 0),IR(108, 1),IR(145, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6230,IR(0, 0),IR(13784, 30)/* Subgroup2DBlockTransposeINTEL */,IR(0, 0),IR(108, 1),IR(145, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6236,IR(0, 0),IR(13814, 38)/* SubgroupMatrixMultiplyAccumulateINTEL */,IR(0, 0),IR(1, 0),IR(146, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6241,IR(0, 0),IR(13852, 28)/* TernaryBitwiseFunctionINTEL */,IR(0, 0),IR(1, 0),IR(147, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6243,IR(0, 0),IR(13880, 32)/* UntypedVariableLengthArrayINTEL */,IR(0, 0),IR(109, 2),IR(101, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6245,IR(0, 0),IR(13912, 21)/* SpecConditionalINTEL */,IR(0, 0),IR(1, 0),IR(148, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6246,IR(0, 0),IR(13933, 22)/* FunctionVariantsINTEL */,IR(0, 0),IR(111, 1),IR(148, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6400,IR(0, 0),IR(13955, 26)/* GroupUniformArithmeticKHR */,IR(0, 0),IR(1, 0),IR(149, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6425,IR(0, 0),IR(13981, 27)/* TensorFloat32RoundingINTEL */,IR(0, 0),IR(1, 0),IR(150, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6427,IR(0, 0),IR(14008, 25)/* MaskedGatherScatterINTEL */,IR(0, 0),IR(1, 0),IR(151, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6441,IR(0, 0),IR(14033, 19)/* CacheControlsINTEL */,IR(0, 0),IR(1, 0),IR(152, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6460,IR(0, 0),IR(14052, 20)/* RegisterLimitsINTEL */,IR(0, 0),IR(1, 0),IR(153, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6528,IR(0, 0),IR(14072, 20)/* BindlessImagesINTEL */,IR(0, 0),IR(1, 0),IR(154, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {0,IR(0, 0),IR(14092, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(14104, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(14112, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {3,IR(0, 0),IR(14120, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(14126, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(14133, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(14144, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(14153, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(14166, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(14172, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(14182, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(14188, 15)/* ImportedModule */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {1,IR(0, 0),IR(14203, 20)/* ImportedDeclaration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {0,IR(0, 0),IR(14223, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(14228, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(14244, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(14258, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(14271, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(14283, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(14300, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(14312, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(14327, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(14340, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(14355, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(14373, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(14390, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(14411, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(14431, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(14451, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {16384,IR(0, 0),IR(14467, 16)/* FlagIsEnumClass */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {32768,IR(0, 0),IR(14483, 20)/* FlagTypePassByValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {65536,IR(0, 0),IR(14503, 24)/* FlagTypePassByReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(14527, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {1,IR(0, 0),IR(14533, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {2,IR(0, 0),IR(14538, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {3,IR(0, 1),IR(14577, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {4,IR(1, 2),IR(14588, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {5,IR(0, 0),IR(14597, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {6,IR(0, 0),IR(14602, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {7,IR(0, 0),IR(14609, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {8,IR(0, 1),IR(14620, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {9,IR(1, 2),IR(14627, 9)/* Fragment */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {0,IR(0, 0),IR(14636, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(14646, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(14659, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {3,IR(0, 0),IR(14672, 11)/* AtomicType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(14683, 10)/* Float16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1,IR(0, 0),IR(14693, 10)/* Float32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {2,IR(0, 0),IR(14703, 10)/* Float64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {3,IR(0, 0),IR(14713, 13)/* SignedInt8NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {4,IR(0, 0),IR(14726, 14)/* SignedInt16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {5,IR(0, 0),IR(14740, 14)/* SignedInt32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {6,IR(0, 0),IR(14754, 14)/* SignedInt64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {7,IR(0, 0),IR(14768, 15)/* UnsignedInt8NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {8,IR(0, 0),IR(14783, 16)/* UnsignedInt16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {9,IR(0, 0),IR(14799, 16)/* UnsignedInt32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {10,IR(0, 0),IR(14815, 16)/* UnsignedInt64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491000,IR(0, 0),IR(14831, 19)/* SignedInt8PackedNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491001,IR(0, 0),IR(14850, 21)/* UnsignedInt8PackedNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491002,IR(0, 0),IR(14871, 12)/* FloatE4M3NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491003,IR(0, 0),IR(14883, 12)/* FloatE5M2NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {0,IR(0, 0),IR(14895, 12)/* RowMajorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {1,IR(0, 0),IR(14907, 15)/* ColumnMajorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {4202,IR(0, 0),IR(14922, 25)/* RowBlockedInterleavedARM */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {4203,IR(0, 0),IR(14947, 28)/* ColumnBlockedInterleavedARM */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {0,IR(0, 0),IR(14975, 8)/* NoneKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {1,IR(0, 0),IR(14983, 27)/* MatrixASignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {2,IR(0, 0),IR(15010, 27)/* MatrixBSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {4,IR(0, 0),IR(15037, 27)/* MatrixCSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {8,IR(0, 0),IR(15064, 32)/* MatrixResultSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {16,IR(0, 0),IR(15096, 26)/* SaturatingAccumulationKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {1,IR(0, 0),IR(15122, 4)/* Row */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {2,IR(0, 0),IR(15126, 7)/* Column */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {4,IR(0, 0),IR(15133, 4)/* 2x2 */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {0,IR(0, 0),IR(15137, 11)/* MatrixAKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {1,IR(0, 0),IR(15148, 11)/* MatrixBKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {2,IR(0, 0),IR(15159, 21)/* MatrixAccumulatorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {0,IR(0, 0),IR(15180, 11)/* RowMajorNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {1,IR(0, 0),IR(15191, 14)/* ColumnMajorNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {2,IR(0, 0),IR(15205, 21)/* InferencingOptimalNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {3,IR(0, 0),IR(15226, 18)/* TrainingOptimalNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {0,IR(0, 0),IR(14092, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(14104, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(14112, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(14120, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(14126, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(14133, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(14144, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {8,IR(0, 0),IR(14153, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(14166, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(14172, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(14182, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(14223, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(14228, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(14244, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(14258, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(14271, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(14283, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(14300, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(14312, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(14327, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(14340, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(14355, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(14373, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(14390, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(14411, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(14431, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(14451, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(14527, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {1,IR(0, 0),IR(14533, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {2,IR(0, 0),IR(14538, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {3,IR(0, 1),IR(14577, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {4,IR(1, 2),IR(14588, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {5,IR(0, 0),IR(14597, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {6,IR(0, 0),IR(14602, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {7,IR(0, 0),IR(14609, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {8,IR(0, 1),IR(14620, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {0,IR(0, 0),IR(14636, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(14646, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(14659, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(15244, 17)/* RelaxedPrecision */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {1,IR(0, 1),IR(15261, 7)/* SpecId */,IR(0, 0),IR(112, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {2,IR(0, 0),IR(15268, 6)/* Block */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {3,IR(0, 0),IR(15274, 12)/* BufferBlock */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),SPV_SPIRV_VERSION_WORD(1,3)}, // SPV_OPERAND_TYPE_DECORATION
  {4,IR(0, 0),IR(15286, 9)/* RowMajor */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5,IR(0, 0),IR(15295, 9)/* ColMajor */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6,IR(0, 1),IR(15304, 12)/* ArrayStride */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {7,IR(0, 1),IR(15316, 13)/* MatrixStride */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {8,IR(0, 0),IR(15329, 11)/* GLSLShared */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {9,IR(0, 0),IR(15340, 11)/* GLSLPacked */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {10,IR(0, 0),IR(15351, 8)/* CPacked */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {11,IR(3, 1),IR(15385, 8)/* BuiltIn */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {13,IR(0, 0),IR(15393, 14)/* NoPerspective */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {14,IR(0, 0),IR(15407, 5)/* Flat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {15,IR(0, 0),IR(15412, 6)/* Patch */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {16,IR(0, 0),IR(15418, 9)/* Centroid */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {17,IR(0, 0),IR(15427, 7)/* Sample */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {18,IR(0, 0),IR(15434, 10)/* Invariant */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {19,IR(0, 0),IR(15444, 9)/* Restrict */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {20,IR(0, 0),IR(15453, 8)/* Aliased */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {21,IR(0, 0),IR(15461, 9)/* Volatile */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {22,IR(0, 0),IR(15470, 9)/* Constant */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {23,IR(0, 0),IR(15479, 9)/* Coherent */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {24,IR(0, 0),IR(15488, 12)/* NonWritable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {25,IR(0, 0),IR(15500, 12)/* NonReadable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {26,IR(0, 0),IR(15512, 8)/* Uniform */,IR(0, 0),IR(114, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {27,IR(4, 1),IR(15546, 10)/* UniformId */,IR(0, 0),IR(114, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {28,IR(0, 0),IR(15556, 20)/* SaturatedConversion */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {29,IR(0, 1),IR(15576, 7)/* Stream */,IR(0, 0),IR(116, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {30,IR(0, 1),IR(15583, 9)/* Location */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {31,IR(0, 1),IR(15592, 10)/* Component */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {32,IR(0, 1),IR(15602, 6)/* Index */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {33,IR(0, 1),IR(15608, 8)/* Binding */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {34,IR(0, 1),IR(15616, 14)/* DescriptorSet */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {35,IR(0, 1),IR(15630, 7)/* Offset */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {36,IR(0, 1),IR(15637, 10)/* XfbBuffer */,IR(0, 0),IR(117, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {37,IR(0, 1),IR(15647, 10)/* XfbStride */,IR(0, 0),IR(117, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {38,IR(5, 1),IR(15703, 14)/* FuncParamAttr */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {39,IR(6, 1),IR(15751, 15)/* FPRoundingMode */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {40,IR(7, 1),IR(15801, 15)/* FPFastMathMode */,IR(0, 0),IR(118, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {41,IR(8, 2),IR(15878, 18)/* LinkageAttributes */,IR(0, 0),IR(120, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {42,IR(0, 0),IR(15896, 14)/* NoContraction */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {43,IR(0, 1),IR(15910, 21)/* InputAttachmentIndex */,IR(0, 0),IR(95, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {44,IR(0, 1),IR(15931, 10)/* Alignment */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {45,IR(0, 1),IR(15941, 14)/* MaxByteOffset */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {46,IR(10, 1),IR(15975, 12)/* AlignmentId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {47,IR(10, 1),IR(15987, 16)/* MaxByteOffsetId */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4216,IR(0, 0),IR(16003, 44)/* SaturatedToLargestFloat8NormalConversionEXT */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4469,IR(0, 0),IR(16047, 13)/* NoSignedWrap */,IR(0, 0),IR(1, 0),IR(155, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4470,IR(0, 0),IR(16060, 15)/* NoUnsignedWrap */,IR(0, 0),IR(1, 0),IR(155, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4487,IR(0, 0),IR(16075, 18)/* WeightTextureQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4488,IR(0, 0),IR(16093, 22)/* BlockMatchTextureQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4499,IR(0, 0),IR(16115, 22)/* BlockMatchSamplerQCOM */,IR(0, 0),IR(1, 0),IR(55, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4999,IR(0, 0),IR(16137, 18)/* ExplicitInterpAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5019,IR(10, 1),IR(16155, 32)/* NodeSharesPayloadLimitsWithAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5020,IR(10, 1),IR(16187, 20)/* NodeMaxPayloadsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5078,IR(0, 0),IR(16207, 23)/* TrackFinishWritingAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5091,IR(10, 1),IR(16230, 20)/* PayloadNodeNameAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5098,IR(10, 1),IR(16250, 25)/* PayloadNodeBaseIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5099,IR(0, 0),IR(16275, 27)/* PayloadNodeSparseArrayAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5100,IR(10, 1),IR(16302, 25)/* PayloadNodeArraySizeAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5105,IR(0, 0),IR(16327, 28)/* PayloadDispatchIndirectAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5248,IR(0, 0),IR(16355, 19)/* OverrideCoverageNV */,IR(0, 0),IR(122, 1),IR(66, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5250,IR(0, 0),IR(16374, 14)/* PassthroughNV */,IR(0, 0),IR(123, 1),IR(67, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5252,IR(0, 0),IR(16388, 19)/* ViewportRelativeNV */,IR(0, 0),IR(94, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5256,IR(0, 1),IR(16407, 28)/* SecondaryViewportRelativeNV */,IR(0, 0),IR(46, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5271,IR(0, 0),IR(16435, 16)/* PerPrimitiveEXT */,IR(51, 1),IR(124, 2),IR(156, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5272,IR(0, 0),IR(16466, 10)/* PerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5273,IR(0, 0),IR(16476, 10)/* PerTaskNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5285,IR(0, 0),IR(16486, 13)/* PerVertexKHR */,IR(52, 1),IR(51, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5300,IR(0, 0),IR(16511, 11)/* NonUniform */,IR(53, 1),IR(97, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5355,IR(0, 0),IR(16536, 16)/* RestrictPointer */,IR(54, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5356,IR(0, 0),IR(16571, 15)/* AliasedPointer */,IR(55, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5386,IR(0, 0),IR(16604, 30)/* HitObjectShaderRecordBufferNV */,IR(0, 0),IR(126, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5398,IR(0, 0),IR(16634, 18)/* BindlessSamplerNV */,IR(0, 0),IR(127, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5399,IR(0, 0),IR(16652, 16)/* BindlessImageNV */,IR(0, 0),IR(127, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5400,IR(0, 0),IR(16668, 15)/* BoundSamplerNV */,IR(0, 0),IR(127, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5401,IR(0, 0),IR(16683, 13)/* BoundImageNV */,IR(0, 0),IR(127, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5599,IR(0, 1),IR(16696, 14)/* SIMTCallINTEL */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5602,IR(0, 0),IR(16710, 26)/* ReferencedIndirectlyINTEL */,IR(0, 0),IR(129, 1),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5607,IR(11, 1),IR(16736, 13)/* ClobberINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5608,IR(0, 0),IR(16749, 17)/* SideEffectsINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5624,IR(0, 0),IR(16766, 27)/* VectorComputeVariableINTEL */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5625,IR(0, 1),IR(16793, 21)/* FuncParamIOKindINTEL */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5626,IR(0, 0),IR(16814, 27)/* VectorComputeFunctionINTEL */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5627,IR(0, 0),IR(16841, 15)/* StackCallINTEL */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5628,IR(0, 1),IR(16856, 26)/* GlobalVariableOffsetINTEL */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5634,IR(10, 1),IR(16882, 14)/* CounterBuffer */,IR(56, 1),IR(1, 0),IR(158, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5635,IR(11, 1),IR(16920, 13)/* UserSemantic */,IR(57, 1),IR(1, 0),IR(158, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5636,IR(11, 1),IR(16952, 15)/* UserTypeGOOGLE */,IR(0, 0),IR(1, 0),IR(159, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5822,IR(12, 2),IR(16967, 26)/* FunctionRoundingModeINTEL */,IR(0, 0),IR(131, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5823,IR(14, 2),IR(17024, 24)/* FunctionDenormModeINTEL */,IR(0, 0),IR(131, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5825,IR(0, 0),IR(17048, 14)/* RegisterINTEL */,IR(0, 0),IR(132, 1),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5826,IR(11, 1),IR(17062, 12)/* MemoryINTEL */,IR(0, 0),IR(132, 1),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5827,IR(0, 1),IR(17074, 14)/* NumbanksINTEL */,IR(0, 0),IR(132, 1),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5828,IR(0, 1),IR(17088, 15)/* BankwidthINTEL */,IR(0, 0),IR(132, 1),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5829,IR(0, 1),IR(17103, 22)/* MaxPrivateCopiesINTEL */,IR(0, 0),IR(132, 1),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5830,IR(0, 0),IR(17125, 16)/* SinglepumpINTEL */,IR(0, 0),IR(132, 1),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5831,IR(0, 0),IR(17141, 16)/* DoublepumpINTEL */,IR(0, 0),IR(132, 1),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5832,IR(0, 1),IR(17157, 19)/* MaxReplicatesINTEL */,IR(0, 0),IR(132, 1),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5833,IR(0, 0),IR(17176, 20)/* SimpleDualPortINTEL */,IR(0, 0),IR(132, 1),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5834,IR(16, 2),IR(17196, 11)/* MergeINTEL */,IR(0, 0),IR(132, 1),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5835,IR(18, 1),IR(17249, 14)/* BankBitsINTEL */,IR(0, 0),IR(132, 1),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5836,IR(0, 1),IR(17263, 20)/* ForcePow2DepthINTEL */,IR(0, 0),IR(132, 1),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5883,IR(0, 1),IR(17283, 16)/* StridesizeINTEL */,IR(0, 0),IR(132, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5884,IR(0, 1),IR(17299, 14)/* WordsizeINTEL */,IR(0, 0),IR(132, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5885,IR(0, 0),IR(17313, 18)/* TrueDualPortINTEL */,IR(0, 0),IR(132, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5899,IR(0, 0),IR(17331, 19)/* BurstCoalesceINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5900,IR(0, 1),IR(17350, 15)/* CacheSizeINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5901,IR(0, 0),IR(17365, 28)/* DontStaticallyCoalesceINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5902,IR(0, 1),IR(17393, 14)/* PrefetchINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5905,IR(0, 0),IR(17407, 17)/* StallEnableINTEL */,IR(0, 0),IR(106, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5907,IR(0, 0),IR(17424, 25)/* FuseLoopsInFunctionINTEL */,IR(0, 0),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5909,IR(1, 2),IR(17449, 19)/* MathOpDSPModeINTEL */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5914,IR(10, 1),IR(17468, 16)/* AliasScopeINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5915,IR(10, 1),IR(17484, 13)/* NoAliasINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5917,IR(0, 1),IR(17497, 24)/* InitiationIntervalINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5918,IR(0, 1),IR(17521, 20)/* MaxConcurrencyINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5919,IR(0, 1),IR(17541, 20)/* PipelineEnableINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5921,IR(0, 1),IR(17561, 20)/* BufferLocationINTEL */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5944,IR(0, 1),IR(17581, 19)/* IOPipeStorageINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6080,IR(19, 2),IR(17634, 31)/* FunctionFloatingPointModeINTEL */,IR(0, 0),IR(131, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6085,IR(0, 0),IR(17665, 25)/* SingleElementVectorINTEL */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6087,IR(0, 0),IR(17690, 35)/* VectorComputeCallableFunctionINTEL */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6140,IR(0, 0),IR(17725, 18)/* MediaBlockIOINTEL */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6151,IR(0, 0),IR(17743, 15)/* StallFreeINTEL */,IR(0, 0),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6170,IR(21, 1),IR(17789, 26)/* FPMaxErrorDecorationINTEL */,IR(0, 0),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6172,IR(0, 1),IR(17815, 25)/* LatencyControlLabelINTEL */,IR(0, 0),IR(142, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6173,IR(22, 3),IR(17840, 30)/* LatencyControlConstraintINTEL */,IR(0, 0),IR(142, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6175,IR(0, 0),IR(17870, 27)/* ConduitKernelArgumentINTEL */,IR(0, 0),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6176,IR(0, 0),IR(17897, 31)/* RegisterMapKernelArgumentINTEL */,IR(0, 0),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6177,IR(0, 1),IR(17928, 33)/* MMHostInterfaceAddressWidthINTEL */,IR(0, 0),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6178,IR(0, 1),IR(17961, 30)/* MMHostInterfaceDataWidthINTEL */,IR(0, 0),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6179,IR(0, 1),IR(17991, 28)/* MMHostInterfaceLatencyINTEL */,IR(0, 0),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6180,IR(25, 1),IR(18053, 34)/* MMHostInterfaceReadWriteModeINTEL */,IR(0, 0),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6181,IR(0, 1),IR(18087, 29)/* MMHostInterfaceMaxBurstINTEL */,IR(0, 0),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6182,IR(0, 1),IR(18116, 32)/* MMHostInterfaceWaitRequestINTEL */,IR(0, 0),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6183,IR(0, 0),IR(18148, 26)/* StableKernelArgumentINTEL */,IR(0, 0),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6188,IR(26, 2),IR(18213, 16)/* HostAccessINTEL */,IR(0, 0),IR(144, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6190,IR(28, 1),IR(18276, 14)/* InitModeINTEL */,IR(0, 0),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6191,IR(0, 1),IR(18290, 28)/* ImplementInRegisterMapINTEL */,IR(0, 0),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6247,IR(10, 1),IR(18318, 17)/* ConditionalINTEL */,IR(0, 0),IR(111, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6442,IR(29, 2),IR(18371, 22)/* CacheControlLoadINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6443,IR(31, 2),IR(18430, 23)/* CacheControlStoreINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {0,IR(0, 0),IR(18453, 3)/* 1D */,IR(0, 0),IR(72, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {1,IR(0, 0),IR(18456, 3)/* 2D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {2,IR(0, 0),IR(18459, 3)/* 3D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {3,IR(0, 0),IR(18462, 5)/* Cube */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {4,IR(0, 0),IR(18467, 5)/* Rect */,IR(0, 0),IR(71, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {5,IR(0, 0),IR(18472, 7)/* Buffer */,IR(0, 0),IR(73, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {6,IR(0, 0),IR(18479, 12)/* SubpassData */,IR(0, 0),IR(95, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {4173,IR(0, 0),IR(18491, 17)/* TileImageDataEXT */,IR(0, 0),IR(147, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {0,IR(0, 1),IR(18508, 12)/* Invocations */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {1,IR(0, 0),IR(18520, 13)/* SpacingEqual */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {2,IR(0, 0),IR(18533, 22)/* SpacingFractionalEven */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {3,IR(0, 0),IR(18555, 21)/* SpacingFractionalOdd */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4,IR(0, 0),IR(18576, 14)/* VertexOrderCw */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5,IR(0, 0),IR(18590, 15)/* VertexOrderCcw */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6,IR(0, 0),IR(18605, 19)/* PixelCenterInteger */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {7,IR(0, 0),IR(18624, 16)/* OriginUpperLeft */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {8,IR(0, 0),IR(18640, 16)/* OriginLowerLeft */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {9,IR(0, 0),IR(18656, 19)/* EarlyFragmentTests */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {10,IR(0, 0),IR(18675, 10)/* PointMode */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {11,IR(0, 0),IR(18685, 4)/* Xfb */,IR(0, 0),IR(117, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {12,IR(0, 0),IR(18689, 15)/* DepthReplacing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {14,IR(0, 0),IR(18704, 13)/* DepthGreater */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {15,IR(0, 0),IR(18717, 10)/* DepthLess */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {16,IR(0, 0),IR(18727, 15)/* DepthUnchanged */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {17,IR(22, 3),IR(18742, 10)/* LocalSize */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {18,IR(22, 3),IR(18752, 14)/* LocalSizeHint */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {19,IR(0, 0),IR(18766, 12)/* InputPoints */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {20,IR(0, 0),IR(18778, 11)/* InputLines */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {21,IR(0, 0),IR(18789, 20)/* InputLinesAdjacency */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {22,IR(0, 0),IR(18809, 10)/* Triangles */,IR(0, 0),IR(12, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {23,IR(0, 0),IR(18819, 24)/* InputTrianglesAdjacency */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {24,IR(0, 0),IR(18843, 6)/* Quads */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {25,IR(0, 0),IR(18849, 9)/* Isolines */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {26,IR(0, 1),IR(18858, 15)/* OutputVertices */,IR(0, 0),IR(148, 4),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {27,IR(0, 0),IR(18873, 13)/* OutputPoints */,IR(0, 0),IR(152, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {28,IR(0, 0),IR(18886, 16)/* OutputLineStrip */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {29,IR(0, 0),IR(18902, 20)/* OutputTriangleStrip */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {30,IR(0, 1),IR(18922, 12)/* VecTypeHint */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {31,IR(0, 0),IR(18934, 15)/* ContractionOff */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {33,IR(0, 0),IR(18949, 12)/* Initializer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {34,IR(0, 0),IR(18961, 10)/* Finalizer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {35,IR(0, 1),IR(5394, 13)/* SubgroupSize */,IR(0, 0),IR(155, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {36,IR(0, 1),IR(18971, 22)/* SubgroupsPerWorkgroup */,IR(0, 0),IR(155, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {37,IR(10, 1),IR(18993, 24)/* SubgroupsPerWorkgroupId */,IR(0, 0),IR(155, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {38,IR(33, 3),IR(19017, 12)/* LocalSizeId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {39,IR(33, 3),IR(19029, 16)/* LocalSizeHintId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4169,IR(0, 0),IR(19045, 34)/* NonCoherentColorAttachmentReadEXT */,IR(0, 0),IR(147, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4170,IR(0, 0),IR(19079, 34)/* NonCoherentDepthAttachmentReadEXT */,IR(0, 0),IR(156, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4171,IR(0, 0),IR(19113, 36)/* NonCoherentStencilAttachmentReadEXT */,IR(0, 0),IR(157, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4421,IR(0, 0),IR(19149, 30)/* SubgroupUniformControlFlowKHR */,IR(0, 0),IR(3, 1),IR(160, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4446,IR(0, 0),IR(19179, 18)/* PostDepthCoverage */,IR(0, 0),IR(158, 1),IR(45, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4459,IR(0, 1),IR(9593, 15)/* DenormPreserve */,IR(0, 0),IR(159, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4460,IR(0, 1),IR(9608, 18)/* DenormFlushToZero */,IR(0, 0),IR(160, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4461,IR(0, 1),IR(9626, 25)/* SignedZeroInfNanPreserve */,IR(0, 0),IR(161, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4462,IR(0, 1),IR(9651, 16)/* RoundingModeRTE */,IR(0, 0),IR(162, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4463,IR(0, 1),IR(9667, 16)/* RoundingModeRTZ */,IR(0, 0),IR(163, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4489,IR(0, 0),IR(19197, 34)/* NonCoherentTileAttachmentReadQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4490,IR(22, 3),IR(19231, 20)/* TileShadingRateQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5017,IR(0, 0),IR(19251, 29)/* EarlyAndLateFragmentTestsAMD */,IR(0, 0),IR(3, 1),IR(161, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5027,IR(0, 0),IR(19280, 23)/* StencilRefReplacingEXT */,IR(0, 0),IR(42, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5069,IR(0, 0),IR(19303, 15)/* CoalescingAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5070,IR(10, 1),IR(19318, 15)/* IsApiEntryAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5071,IR(10, 1),IR(19333, 21)/* MaxNodeRecursionAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5072,IR(33, 3),IR(19354, 24)/* StaticNumWorkgroupsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5073,IR(10, 1),IR(6287, 16)/* ShaderIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5077,IR(33, 3),IR(19378, 21)/* MaxNumWorkgroupsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5079,IR(0, 0),IR(19399, 28)/* StencilRefUnchangedFrontAMD */,IR(0, 0),IR(42, 1),IR(162, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5080,IR(0, 0),IR(19427, 26)/* StencilRefGreaterFrontAMD */,IR(0, 0),IR(42, 1),IR(162, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5081,IR(0, 0),IR(19453, 23)/* StencilRefLessFrontAMD */,IR(0, 0),IR(42, 1),IR(162, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5082,IR(0, 0),IR(19476, 27)/* StencilRefUnchangedBackAMD */,IR(0, 0),IR(42, 1),IR(162, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5083,IR(0, 0),IR(19503, 25)/* StencilRefGreaterBackAMD */,IR(0, 0),IR(42, 1),IR(162, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5084,IR(0, 0),IR(19528, 22)/* StencilRefLessBackAMD */,IR(0, 0),IR(42, 1),IR(162, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5088,IR(0, 0),IR(19550, 19)/* QuadDerivativesKHR */,IR(0, 0),IR(164, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5089,IR(0, 0),IR(19569, 20)/* RequireFullQuadsKHR */,IR(0, 0),IR(164, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5102,IR(36, 2),IR(19589, 20)/* SharesInputWithAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5269,IR(0, 0),IR(19609, 15)/* OutputLinesEXT */,IR(58, 1),IR(124, 2),IR(156, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5270,IR(0, 1),IR(19638, 20)/* OutputPrimitivesEXT */,IR(59, 1),IR(124, 2),IR(156, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5289,IR(0, 0),IR(19677, 24)/* DerivativeGroupQuadsKHR */,IR(60, 1),IR(165, 1),IR(73, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5290,IR(0, 0),IR(19724, 25)/* DerivativeGroupLinearKHR */,IR(61, 1),IR(166, 1),IR(73, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5298,IR(0, 0),IR(19773, 19)/* OutputTrianglesEXT */,IR(62, 1),IR(124, 2),IR(156, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5366,IR(0, 0),IR(19810, 25)/* PixelInterlockOrderedEXT */,IR(0, 0),IR(167, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5367,IR(0, 0),IR(19835, 27)/* PixelInterlockUnorderedEXT */,IR(0, 0),IR(167, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5368,IR(0, 0),IR(19862, 26)/* SampleInterlockOrderedEXT */,IR(0, 0),IR(168, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5369,IR(0, 0),IR(19888, 28)/* SampleInterlockUnorderedEXT */,IR(0, 0),IR(168, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5370,IR(0, 0),IR(19916, 31)/* ShadingRateInterlockOrderedEXT */,IR(0, 0),IR(169, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5371,IR(0, 0),IR(19947, 33)/* ShadingRateInterlockUnorderedEXT */,IR(0, 0),IR(169, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5618,IR(0, 1),IR(19980, 27)/* SharedLocalMemorySizeINTEL */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5620,IR(0, 1),IR(20007, 21)/* RoundingModeRTPINTEL */,IR(0, 0),IR(170, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5621,IR(0, 1),IR(20028, 21)/* RoundingModeRTNINTEL */,IR(0, 0),IR(170, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5622,IR(0, 1),IR(20049, 26)/* FloatingPointModeALTINTEL */,IR(0, 0),IR(170, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5623,IR(0, 1),IR(20075, 27)/* FloatingPointModeIEEEINTEL */,IR(0, 0),IR(170, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5893,IR(22, 3),IR(20102, 22)/* MaxWorkgroupSizeINTEL */,IR(0, 0),IR(171, 1),IR(108, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5894,IR(0, 1),IR(20124, 16)/* MaxWorkDimINTEL */,IR(0, 0),IR(171, 1),IR(108, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5895,IR(0, 0),IR(20140, 20)/* NoGlobalOffsetINTEL */,IR(0, 0),IR(171, 1),IR(108, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5896,IR(0, 1),IR(20160, 22)/* NumSIMDWorkitemsINTEL */,IR(0, 0),IR(107, 1),IR(108, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5903,IR(0, 1),IR(20182, 28)/* SchedulerTargetFmaxMhzINTEL */,IR(0, 0),IR(107, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6023,IR(0, 0),IR(20210, 24)/* MaximallyReconvergesKHR */,IR(0, 0),IR(3, 1),IR(164, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6028,IR(36, 2),IR(20234, 18)/* FPFastMathDefault */,IR(0, 0),IR(172, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6154,IR(0, 1),IR(20252, 24)/* StreamingInterfaceINTEL */,IR(0, 0),IR(107, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6160,IR(0, 1),IR(20276, 26)/* RegisterMapInterfaceINTEL */,IR(0, 0),IR(173, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6417,IR(0, 1),IR(20302, 23)/* NamedBarrierCountINTEL */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6461,IR(0, 1),IR(20325, 22)/* MaximumRegistersINTEL */,IR(0, 0),IR(174, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6462,IR(10, 1),IR(20347, 24)/* MaximumRegistersIdINTEL */,IR(0, 0),IR(174, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6463,IR(38, 1),IR(20422, 27)/* NamedMaximumRegistersINTEL */,IR(0, 0),IR(174, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {0,IR(0, 0),IR(20449, 7)/* Vertex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {1,IR(0, 0),IR(20456, 20)/* TessellationControl */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {2,IR(0, 0),IR(20476, 23)/* TessellationEvaluation */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {3,IR(0, 0),IR(4875, 9)/* Geometry */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {4,IR(0, 0),IR(14627, 9)/* Fragment */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5,IR(0, 0),IR(20499, 10)/* GLCompute */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {6,IR(0, 0),IR(4642, 7)/* Kernel */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5267,IR(0, 0),IR(20509, 7)/* TaskNV */,IR(0, 0),IR(50, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5268,IR(0, 0),IR(20516, 7)/* MeshNV */,IR(0, 0),IR(50, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5313,IR(0, 0),IR(20523, 17)/* RayGenerationKHR */,IR(63, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5314,IR(0, 0),IR(20556, 16)/* IntersectionKHR */,IR(64, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5315,IR(0, 0),IR(20587, 10)/* AnyHitKHR */,IR(65, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5316,IR(0, 0),IR(20606, 14)/* ClosestHitKHR */,IR(66, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5317,IR(0, 0),IR(20633, 8)/* MissKHR */,IR(67, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5318,IR(0, 0),IR(20648, 12)/* CallableKHR */,IR(68, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5364,IR(0, 0),IR(20671, 8)/* TaskEXT */,IR(0, 0),IR(53, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5365,IR(0, 0),IR(20679, 8)/* MeshEXT */,IR(0, 0),IR(53, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {0,IR(0, 0),IR(20687, 9)/* Preserve */,IR(0, 0),IR(131, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPDENORM_MODE
  {1,IR(0, 0),IR(20696, 12)/* FlushToZero */,IR(0, 0),IR(131, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPDENORM_MODE
  {0,IR(0, 0),IR(20708, 12)/* BFloat16KHR */,IR(0, 0),IR(89, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {4214,IR(0, 0),IR(20720, 14)/* Float8E4M3EXT */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {4215,IR(0, 0),IR(20734, 14)/* Float8E5M2EXT */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {0,IR(0, 0),IR(20748, 5)/* IEEE */,IR(0, 0),IR(131, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPOPERATION_MODE
  {1,IR(0, 0),IR(20753, 4)/* ALT */,IR(0, 0),IR(131, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPOPERATION_MODE
  {0,IR(0, 0),IR(14223, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {1,IR(0, 0),IR(20757, 7)/* NotNaN */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {2,IR(0, 0),IR(20764, 7)/* NotInf */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {4,IR(0, 0),IR(20771, 4)/* NSZ */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {8,IR(0, 0),IR(20775, 11)/* AllowRecip */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {16,IR(0, 0),IR(20786, 5)/* Fast */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {65536,IR(0, 0),IR(20791, 14)/* AllowContract */,IR(69, 1),IR(175, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {131072,IR(0, 0),IR(20828, 13)/* AllowReassoc */,IR(70, 1),IR(175, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {262144,IR(0, 0),IR(20859, 15)/* AllowTransform */,IR(0, 0),IR(172, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {0,IR(0, 0),IR(20874, 4)/* RTE */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {1,IR(0, 0),IR(20878, 4)/* RTZ */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {2,IR(0, 0),IR(20882, 4)/* RTP */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {3,IR(0, 0),IR(20886, 4)/* RTN */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {1,IR(0, 0),IR(20890, 16)/* Vertical2Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {2,IR(0, 0),IR(20906, 16)/* Vertical4Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {4,IR(0, 0),IR(20922, 18)/* Horizontal2Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {8,IR(0, 0),IR(20940, 18)/* Horizontal4Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {0,IR(0, 0),IR(14223, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {1,IR(0, 0),IR(20958, 7)/* Inline */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {2,IR(0, 0),IR(20965, 11)/* DontInline */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {4,IR(0, 0),IR(20976, 5)/* Pure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {8,IR(0, 0),IR(20981, 6)/* Const */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {65536,IR(0, 0),IR(13369, 11)/* OptNoneEXT */,IR(50, 1),IR(177, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {0,IR(0, 0),IR(20987, 5)/* Zext */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {1,IR(0, 0),IR(20992, 5)/* Sext */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {2,IR(0, 0),IR(20997, 6)/* ByVal */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {3,IR(0, 0),IR(21003, 5)/* Sret */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {4,IR(0, 0),IR(21008, 8)/* NoAlias */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {5,IR(0, 0),IR(21016, 10)/* NoCapture */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {6,IR(0, 0),IR(21026, 8)/* NoWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {7,IR(0, 0),IR(21034, 12)/* NoReadWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {5940,IR(0, 0),IR(21046, 20)/* RuntimeAlignedINTEL */,IR(0, 0),IR(178, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {0,IR(0, 0),IR(21066, 7)/* Reduce */,IR(0, 0),IR(179, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {1,IR(0, 0),IR(21073, 14)/* InclusiveScan */,IR(0, 0),IR(179, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {2,IR(0, 0),IR(21087, 14)/* ExclusiveScan */,IR(0, 0),IR(179, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {3,IR(0, 0),IR(21101, 16)/* ClusteredReduce */,IR(0, 0),IR(182, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {6,IR(0, 0),IR(21117, 20)/* PartitionedReduceNV */,IR(0, 0),IR(183, 1),IR(75, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {7,IR(0, 0),IR(21137, 27)/* PartitionedInclusiveScanNV */,IR(0, 0),IR(183, 1),IR(75, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {8,IR(0, 0),IR(21164, 27)/* PartitionedExclusiveScanNV */,IR(0, 0),IR(183, 1),IR(75, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {0,IR(0, 0),IR(21191, 10)/* NoneINTEL */,IR(0, 0),IR(144, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {1,IR(0, 0),IR(21201, 10)/* ReadINTEL */,IR(0, 0),IR(144, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {2,IR(0, 0),IR(21211, 11)/* WriteINTEL */,IR(0, 0),IR(144, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {3,IR(0, 0),IR(21222, 15)/* ReadWriteINTEL */,IR(0, 0),IR(144, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {0,IR(0, 0),IR(14223, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {1,IR(10, 1),IR(21237, 5)/* Bias */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {2,IR(10, 1),IR(21242, 4)/* Lod */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {4,IR(36, 2),IR(21246, 5)/* Grad */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {8,IR(10, 1),IR(21251, 12)/* ConstOffset */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {16,IR(10, 1),IR(15630, 7)/* Offset */,IR(0, 0),IR(184, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {32,IR(10, 1),IR(21263, 13)/* ConstOffsets */,IR(0, 0),IR(184, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {64,IR(10, 1),IR(15427, 7)/* Sample */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {128,IR(10, 1),IR(8426, 7)/* MinLod */,IR(0, 0),IR(185, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {256,IR(4, 1),IR(21276, 19)/* MakeTexelAvailable */,IR(71, 1),IR(186, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {512,IR(4, 1),IR(21317, 17)/* MakeTexelVisible */,IR(72, 1),IR(186, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {1024,IR(0, 0),IR(21354, 16)/* NonPrivateTexel */,IR(73, 1),IR(186, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {2048,IR(0, 0),IR(21389, 14)/* VolatileTexel */,IR(74, 1),IR(186, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {4096,IR(0, 0),IR(21420, 11)/* SignExtend */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {8192,IR(0, 0),IR(21431, 11)/* ZeroExtend */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {16384,IR(0, 0),IR(21442, 12)/* Nontemporal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {65536,IR(10, 1),IR(21454, 8)/* Offsets */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {0,IR(0, 0),IR(21462, 10)/* SnormInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {1,IR(0, 0),IR(21472, 11)/* SnormInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {2,IR(0, 0),IR(21483, 10)/* UnormInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {3,IR(0, 0),IR(21493, 11)/* UnormInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {4,IR(0, 0),IR(21504, 14)/* UnormShort565 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {5,IR(0, 0),IR(21518, 14)/* UnormShort555 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {6,IR(0, 0),IR(21532, 15)/* UnormInt101010 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {7,IR(0, 0),IR(21547, 11)/* SignedInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {8,IR(0, 0),IR(21558, 12)/* SignedInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {9,IR(0, 0),IR(21570, 12)/* SignedInt32 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {10,IR(0, 0),IR(21582, 13)/* UnsignedInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {11,IR(0, 0),IR(21595, 14)/* UnsignedInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {12,IR(0, 0),IR(21609, 14)/* UnsignedInt32 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {13,IR(0, 0),IR(21623, 10)/* HalfFloat */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {14,IR(0, 0),IR(14120, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {15,IR(0, 0),IR(21633, 11)/* UnormInt24 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {16,IR(0, 0),IR(21644, 17)/* UnormInt101010_2 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {17,IR(0, 0),IR(21661, 16)/* UnormInt10X6EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {19,IR(0, 0),IR(21677, 20)/* UnsignedIntRaw10EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {20,IR(0, 0),IR(21697, 20)/* UnsignedIntRaw12EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {21,IR(0, 0),IR(21717, 20)/* UnormInt2_101010EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {22,IR(0, 0),IR(21737, 19)/* UnsignedInt10X6EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {23,IR(0, 0),IR(21756, 19)/* UnsignedInt12X4EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {24,IR(0, 0),IR(21775, 19)/* UnsignedInt14X2EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {25,IR(0, 0),IR(21794, 16)/* UnormInt12X4EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {26,IR(0, 0),IR(21810, 16)/* UnormInt14X2EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {0,IR(0, 0),IR(21826, 2)/* R */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {1,IR(0, 0),IR(21828, 2)/* A */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {2,IR(0, 0),IR(21830, 3)/* RG */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {3,IR(0, 0),IR(21833, 3)/* RA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {4,IR(0, 0),IR(21836, 4)/* RGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {5,IR(0, 0),IR(21840, 5)/* RGBA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {6,IR(0, 0),IR(21845, 5)/* BGRA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {7,IR(0, 0),IR(21850, 5)/* ARGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {8,IR(0, 0),IR(21855, 10)/* Intensity */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {9,IR(0, 0),IR(21865, 10)/* Luminance */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {10,IR(0, 0),IR(21875, 3)/* Rx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {11,IR(0, 0),IR(21878, 4)/* RGx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {12,IR(0, 0),IR(21882, 5)/* RGBx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {13,IR(0, 0),IR(21887, 6)/* Depth */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {14,IR(0, 0),IR(21893, 13)/* DepthStencil */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {15,IR(0, 0),IR(21906, 5)/* sRGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {16,IR(0, 0),IR(21911, 6)/* sRGBx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {17,IR(0, 0),IR(21917, 6)/* sRGBA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {18,IR(0, 0),IR(21923, 6)/* sBGRA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {19,IR(0, 0),IR(21929, 5)/* ABGR */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {0,IR(0, 0),IR(21934, 27)/* InitOnDeviceReprogramINTEL */,IR(0, 0),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {1,IR(0, 0),IR(21961, 23)/* InitOnDeviceResetINTEL */,IR(0, 0),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {0,IR(0, 0),IR(21984, 7)/* NoWait */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {1,IR(0, 0),IR(21991, 11)/* WaitKernel */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {2,IR(0, 0),IR(22002, 14)/* WaitWorkGroup */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {0,IR(0, 0),IR(14223, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {1,IR(0, 0),IR(22016, 12)/* CmdExecTime */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {0,IR(0, 0),IR(14223, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {1,IR(0, 0),IR(22028, 13)/* MayUsePrintf */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {0,IR(0, 0),IR(22041, 7)/* Export */,IR(0, 0),IR(120, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {1,IR(0, 0),IR(22048, 7)/* Import */,IR(0, 0),IR(120, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {2,IR(0, 0),IR(22055, 12)/* LinkOnceODR */,IR(0, 0),IR(120, 1),IR(165, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {0,IR(0, 0),IR(22067, 14)/* UncachedINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {1,IR(0, 0),IR(22081, 12)/* CachedINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {2,IR(0, 0),IR(22093, 15)/* StreamingINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {3,IR(0, 0),IR(22108, 25)/* InvalidateAfterReadINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {4,IR(0, 0),IR(22133, 17)/* ConstCachedINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {0,IR(0, 0),IR(14223, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {1,IR(0, 0),IR(22150, 7)/* Unroll */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {2,IR(0, 0),IR(22157, 11)/* DontUnroll */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {4,IR(0, 0),IR(22168, 19)/* DependencyInfinite */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {8,IR(0, 1),IR(22187, 17)/* DependencyLength */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {16,IR(0, 1),IR(22204, 14)/* MinIterations */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {32,IR(0, 1),IR(22218, 14)/* MaxIterations */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {64,IR(0, 1),IR(22232, 18)/* IterationMultiple */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {128,IR(0, 1),IR(22250, 10)/* PeelCount */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {256,IR(0, 1),IR(22260, 13)/* PartialCount */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {65536,IR(0, 1),IR(17497, 24)/* InitiationIntervalINTEL */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {131072,IR(0, 1),IR(17521, 20)/* MaxConcurrencyINTEL */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {262144,IR(0, 1),IR(22273, 21)/* DependencyArrayINTEL */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {524288,IR(0, 1),IR(17541, 20)/* PipelineEnableINTEL */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {1048576,IR(0, 1),IR(22294, 18)/* LoopCoalesceINTEL */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {2097152,IR(0, 1),IR(22312, 21)/* MaxInterleavingINTEL */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {4194304,IR(0, 1),IR(22333, 26)/* SpeculatedIterationsINTEL */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {8388608,IR(0, 0),IR(22359, 14)/* NoFusionINTEL */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {16777216,IR(0, 1),IR(22373, 15)/* LoopCountINTEL */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {33554432,IR(0, 1),IR(22388, 26)/* MaxReinvocationDelayINTEL */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {0,IR(0, 0),IR(14223, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {1,IR(0, 0),IR(22414, 29)/* MatrixASignedComponentsINTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {2,IR(0, 0),IR(22443, 29)/* MatrixBSignedComponentsINTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {4,IR(0, 0),IR(22472, 21)/* MatrixCBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {8,IR(0, 0),IR(22493, 26)/* MatrixResultBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {16,IR(0, 0),IR(22519, 23)/* MatrixAPackedInt8INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {32,IR(0, 0),IR(22542, 23)/* MatrixBPackedInt8INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {64,IR(0, 0),IR(22565, 23)/* MatrixAPackedInt4INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {128,IR(0, 0),IR(22588, 23)/* MatrixBPackedInt4INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {256,IR(0, 0),IR(22611, 17)/* MatrixATF32INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {512,IR(0, 0),IR(22628, 17)/* MatrixBTF32INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {1024,IR(0, 0),IR(22645, 26)/* MatrixAPackedFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {2048,IR(0, 0),IR(22671, 26)/* MatrixBPackedFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {4096,IR(0, 0),IR(22697, 27)/* MatrixAPackedBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {8192,IR(0, 0),IR(22724, 27)/* MatrixBPackedBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {0,IR(0, 0),IR(14223, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {1,IR(0, 0),IR(15461, 9)/* Volatile */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {2,IR(0, 1),IR(22751, 8)/* Aligned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {4,IR(0, 0),IR(21442, 12)/* Nontemporal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {8,IR(4, 1),IR(22759, 21)/* MakePointerAvailable */,IR(75, 1),IR(186, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {16,IR(4, 1),IR(22804, 19)/* MakePointerVisible */,IR(76, 1),IR(186, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {32,IR(0, 0),IR(22845, 18)/* NonPrivatePointer */,IR(77, 1),IR(186, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {65536,IR(10, 1),IR(22884, 20)/* AliasScopeINTELMask */,IR(0, 0),IR(136, 1),IR(113, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {131072,IR(10, 1),IR(22904, 17)/* NoAliasINTELMask */,IR(0, 0),IR(136, 1),IR(113, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {0,IR(0, 0),IR(22921, 7)/* Simple */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {1,IR(0, 0),IR(22928, 8)/* GLSL450 */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {2,IR(0, 0),IR(22936, 7)/* OpenCL */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {3,IR(0, 0),IR(22943, 7)/* Vulkan */,IR(78, 1),IR(186, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {0,IR(0, 0),IR(22960, 8)/* Relaxed */,IR(79, 1),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {2,IR(0, 0),IR(22968, 8)/* Acquire */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {4,IR(0, 0),IR(22976, 8)/* Release */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {8,IR(0, 0),IR(22984, 15)/* AcquireRelease */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {16,IR(0, 0),IR(22999, 23)/* SequentiallyConsistent */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {64,IR(0, 0),IR(23022, 14)/* UniformMemory */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {128,IR(0, 0),IR(23036, 15)/* SubgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {256,IR(0, 0),IR(23051, 16)/* WorkgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {512,IR(0, 0),IR(23067, 21)/* CrossWorkgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {1024,IR(0, 0),IR(23088, 20)/* AtomicCounterMemory */,IR(0, 0),IR(82, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {2048,IR(0, 0),IR(23108, 12)/* ImageMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {4096,IR(0, 0),IR(23120, 13)/* OutputMemory */,IR(80, 1),IR(186, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {8192,IR(0, 0),IR(23149, 14)/* MakeAvailable */,IR(81, 1),IR(186, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {16384,IR(0, 0),IR(23180, 12)/* MakeVisible */,IR(82, 1),IR(186, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {32768,IR(0, 0),IR(15461, 9)/* Volatile */,IR(0, 0),IR(186, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {0,IR(0, 0),IR(23207, 10)/* AutoINTEL */,IR(0, 0),IR(174, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS
  {0,IR(0, 0),IR(23217, 5)/* WRAP */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {1,IR(0, 0),IR(23222, 4)/* SAT */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {2,IR(0, 0),IR(23226, 9)/* SAT_ZERO */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {3,IR(0, 0),IR(23235, 8)/* SAT_SYM */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {0,IR(0, 0),IR(23243, 25)/* PackedVectorFormat4x8Bit */,IR(83, 1),IR(1, 0),IR(122, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {0,IR(0, 0),IR(23296, 4)/* TRN */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {1,IR(0, 0),IR(23300, 9)/* TRN_ZERO */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {2,IR(0, 0),IR(23309, 4)/* RND */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {3,IR(0, 0),IR(23313, 9)/* RND_ZERO */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {4,IR(0, 0),IR(23322, 8)/* RND_INF */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {5,IR(0, 0),IR(23330, 12)/* RND_MIN_INF */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {6,IR(0, 0),IR(23342, 9)/* RND_CONV */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {7,IR(0, 0),IR(23351, 13)/* RND_CONV_ODD */,IR(0, 0),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {0,IR(0, 0),IR(14223, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {1,IR(0, 0),IR(23364, 25)/* RobustnessPerComponentNV */,IR(0, 0),IR(189, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {2,IR(0, 0),IR(23389, 23)/* RobustnessPerElementNV */,IR(0, 0),IR(189, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {0,IR(0, 0),IR(14975, 8)/* NoneKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {1,IR(0, 0),IR(23412, 10)/* OpaqueKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {2,IR(0, 0),IR(23422, 12)/* NoOpaqueKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {4,IR(0, 0),IR(23434, 23)/* TerminateOnFirstHitKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {8,IR(0, 0),IR(23457, 24)/* SkipClosestHitShaderKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {16,IR(0, 0),IR(23481, 27)/* CullBackFacingTrianglesKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {32,IR(0, 0),IR(23508, 28)/* CullFrontFacingTrianglesKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {64,IR(0, 0),IR(23536, 14)/* CullOpaqueKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {128,IR(0, 0),IR(23550, 16)/* CullNoOpaqueKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {256,IR(0, 0),IR(23566, 17)/* SkipTrianglesKHR */,IR(84, 1),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {512,IR(0, 0),IR(23607, 13)/* SkipAABBsKHR */,IR(0, 0),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {1024,IR(0, 0),IR(23620, 30)/* ForceOpacityMicromap2StateEXT */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {0,IR(0, 0),IR(23650, 41)/* RayQueryCandidateIntersectionTriangleKHR */,IR(0, 0),IR(192, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {1,IR(0, 0),IR(23691, 37)/* RayQueryCandidateIntersectionAABBKHR */,IR(0, 0),IR(192, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {0,IR(0, 0),IR(23728, 37)/* RayQueryCommittedIntersectionNoneKHR */,IR(0, 0),IR(192, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {1,IR(0, 0),IR(23765, 41)/* RayQueryCommittedIntersectionTriangleKHR */,IR(0, 0),IR(192, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {2,IR(0, 0),IR(23806, 42)/* RayQueryCommittedIntersectionGeneratedKHR */,IR(0, 0),IR(192, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {0,IR(0, 0),IR(23848, 33)/* RayQueryCandidateIntersectionKHR */,IR(0, 0),IR(192, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {1,IR(0, 0),IR(23881, 33)/* RayQueryCommittedIntersectionKHR */,IR(0, 0),IR(192, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {0,IR(0, 0),IR(14223, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {1,IR(0, 0),IR(23914, 12)/* ClampToEdge */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {2,IR(0, 0),IR(23926, 6)/* Clamp */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {3,IR(0, 0),IR(23932, 7)/* Repeat */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {4,IR(0, 0),IR(23939, 15)/* RepeatMirrored */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {0,IR(0, 0),IR(23954, 8)/* Nearest */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {1,IR(0, 0),IR(23962, 7)/* Linear */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {0,IR(0, 0),IR(23969, 8)/* Unknown */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {1,IR(0, 0),IR(23977, 8)/* Rgba32f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {2,IR(0, 0),IR(23985, 8)/* Rgba16f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {3,IR(0, 0),IR(23993, 5)/* R32f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {4,IR(0, 0),IR(23998, 6)/* Rgba8 */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {5,IR(0, 0),IR(24004, 11)/* Rgba8Snorm */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {6,IR(0, 0),IR(24015, 6)/* Rg32f */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {7,IR(0, 0),IR(24021, 6)/* Rg16f */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {8,IR(0, 0),IR(24027, 13)/* R11fG11fB10f */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {9,IR(0, 0),IR(24040, 5)/* R16f */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {10,IR(0, 0),IR(24045, 7)/* Rgba16 */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {11,IR(0, 0),IR(24052, 8)/* Rgb10A2 */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {12,IR(0, 0),IR(24060, 5)/* Rg16 */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {13,IR(0, 0),IR(24065, 4)/* Rg8 */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {14,IR(0, 0),IR(24069, 4)/* R16 */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {15,IR(0, 0),IR(24073, 3)/* R8 */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {16,IR(0, 0),IR(24076, 12)/* Rgba16Snorm */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {17,IR(0, 0),IR(24088, 10)/* Rg16Snorm */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {18,IR(0, 0),IR(24098, 9)/* Rg8Snorm */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {19,IR(0, 0),IR(24107, 9)/* R16Snorm */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {20,IR(0, 0),IR(24116, 8)/* R8Snorm */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {21,IR(0, 0),IR(24124, 8)/* Rgba32i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {22,IR(0, 0),IR(24132, 8)/* Rgba16i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {23,IR(0, 0),IR(24140, 7)/* Rgba8i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {24,IR(0, 0),IR(24147, 5)/* R32i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {25,IR(0, 0),IR(24152, 6)/* Rg32i */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {26,IR(0, 0),IR(24158, 6)/* Rg16i */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {27,IR(0, 0),IR(24164, 5)/* Rg8i */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {28,IR(0, 0),IR(24169, 5)/* R16i */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {29,IR(0, 0),IR(24174, 4)/* R8i */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {30,IR(0, 0),IR(24178, 9)/* Rgba32ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {31,IR(0, 0),IR(24187, 9)/* Rgba16ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {32,IR(0, 0),IR(24196, 8)/* Rgba8ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {33,IR(0, 0),IR(24204, 6)/* R32ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {34,IR(0, 0),IR(24210, 10)/* Rgb10a2ui */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {35,IR(0, 0),IR(24220, 7)/* Rg32ui */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {36,IR(0, 0),IR(24227, 7)/* Rg16ui */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {37,IR(0, 0),IR(24234, 6)/* Rg8ui */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {38,IR(0, 0),IR(24240, 6)/* R16ui */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {39,IR(0, 0),IR(24246, 5)/* R8ui */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {40,IR(0, 0),IR(24251, 6)/* R64ui */,IR(0, 0),IR(194, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {41,IR(0, 0),IR(24257, 5)/* R64i */,IR(0, 0),IR(194, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {0,IR(0, 0),IR(24262, 12)/* CrossDevice */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {1,IR(0, 0),IR(24274, 7)/* Device */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {2,IR(0, 0),IR(24281, 10)/* Workgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {3,IR(0, 0),IR(24291, 9)/* Subgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {4,IR(0, 0),IR(24300, 11)/* Invocation */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {5,IR(0, 0),IR(24311, 12)/* QueueFamily */,IR(85, 1),IR(186, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {6,IR(0, 0),IR(24338, 14)/* ShaderCallKHR */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {0,IR(0, 0),IR(14223, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {1,IR(0, 0),IR(24352, 8)/* Flatten */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {2,IR(0, 0),IR(24360, 12)/* DontFlatten */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {1,IR(0, 0),IR(24372, 29)/* IdentifierPossibleDuplicates */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS
  {0,IR(0, 0),IR(14092, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(14104, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(14112, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {3,IR(0, 0),IR(14120, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(14126, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(14133, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(14144, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(14153, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(14166, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(14172, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(14182, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(14188, 15)/* ImportedModule */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {1,IR(0, 0),IR(14203, 20)/* ImportedDeclaration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {0,IR(0, 0),IR(14223, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(14228, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(14244, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(14258, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(14271, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(14283, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(14300, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(14312, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(14327, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(14340, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(14355, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(14373, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(14390, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(14411, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(14431, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(14451, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {16384,IR(0, 0),IR(14467, 16)/* FlagIsEnumClass */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {32768,IR(0, 0),IR(14483, 20)/* FlagTypePassByValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {65536,IR(0, 0),IR(14503, 24)/* FlagTypePassByReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {131072,IR(0, 0),IR(24401, 26)/* FlagUnknownPhysicalLayout */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(14527, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {1,IR(0, 0),IR(14533, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {2,IR(0, 0),IR(14538, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {3,IR(10, 1),IR(14577, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {4,IR(36, 2),IR(14588, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {5,IR(0, 0),IR(14597, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {6,IR(0, 0),IR(14602, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {7,IR(0, 0),IR(14609, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {8,IR(10, 1),IR(14620, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {9,IR(36, 2),IR(14627, 9)/* Fragment */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {0,IR(0, 0),IR(14636, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(14646, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(14659, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {3,IR(0, 0),IR(14672, 11)/* AtomicType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(23969, 8)/* Unknown */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {1,IR(0, 0),IR(24427, 5)/* ESSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {2,IR(0, 0),IR(24432, 5)/* GLSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {3,IR(0, 0),IR(24437, 9)/* OpenCL_C */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {4,IR(0, 0),IR(24446, 11)/* OpenCL_CPP */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {5,IR(0, 0),IR(24457, 5)/* HLSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {6,IR(0, 0),IR(24462, 15)/* CPP_for_OpenCL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {7,IR(0, 0),IR(24477, 5)/* SYCL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {8,IR(0, 0),IR(24482, 7)/* HERO_C */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {9,IR(0, 0),IR(24489, 5)/* NZSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {10,IR(0, 0),IR(24494, 5)/* WGSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {11,IR(0, 0),IR(24499, 6)/* Slang */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {12,IR(0, 0),IR(24505, 4)/* Zig */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {13,IR(0, 0),IR(24509, 5)/* Rust */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {0,IR(0, 0),IR(24514, 16)/* UniformConstant */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {1,IR(0, 0),IR(24530, 6)/* Input */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {2,IR(0, 0),IR(15512, 8)/* Uniform */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {3,IR(0, 0),IR(24536, 7)/* Output */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4,IR(0, 0),IR(24281, 10)/* Workgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5,IR(0, 0),IR(24543, 15)/* CrossWorkgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {6,IR(0, 0),IR(24558, 8)/* Private */,IR(0, 0),IR(195, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {7,IR(0, 0),IR(24566, 9)/* Function */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {8,IR(0, 0),IR(24575, 8)/* Generic */,IR(0, 0),IR(197, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {9,IR(0, 0),IR(24583, 13)/* PushConstant */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {10,IR(0, 0),IR(24596, 14)/* AtomicCounter */,IR(0, 0),IR(82, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {11,IR(0, 0),IR(24610, 6)/* Image */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {12,IR(0, 0),IR(24616, 14)/* StorageBuffer */,IR(0, 0),IR(3, 1),IR(166, 2),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4172,IR(0, 0),IR(24630, 13)/* TileImageEXT */,IR(0, 0),IR(147, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4491,IR(0, 0),IR(24643, 19)/* TileAttachmentQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5068,IR(0, 0),IR(24662, 16)/* NodePayloadAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5328,IR(0, 0),IR(24678, 16)/* CallableDataKHR */,IR(86, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5329,IR(0, 0),IR(24709, 24)/* IncomingCallableDataKHR */,IR(87, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5338,IR(0, 0),IR(24756, 14)/* RayPayloadKHR */,IR(88, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5339,IR(0, 0),IR(24783, 16)/* HitAttributeKHR */,IR(89, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5342,IR(0, 0),IR(24814, 22)/* IncomingRayPayloadKHR */,IR(90, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5343,IR(0, 0),IR(24857, 22)/* ShaderRecordBufferKHR */,IR(91, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5349,IR(0, 0),IR(24900, 22)/* PhysicalStorageBuffer */,IR(92, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5385,IR(0, 0),IR(24947, 21)/* HitObjectAttributeNV */,IR(0, 0),IR(126, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5402,IR(0, 0),IR(24968, 24)/* TaskPayloadWorkgroupEXT */,IR(0, 0),IR(53, 1),IR(23, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5605,IR(0, 0),IR(24992, 17)/* CodeSectionINTEL */,IR(0, 0),IR(198, 1),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5936,IR(0, 0),IR(25009, 16)/* DeviceOnlyINTEL */,IR(0, 0),IR(199, 1),IR(117, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5937,IR(0, 0),IR(25025, 14)/* HostOnlyINTEL */,IR(0, 0),IR(199, 1),IR(117, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {0,IR(0, 0),IR(22067, 14)/* UncachedINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {1,IR(0, 0),IR(25039, 18)/* WriteThroughINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {2,IR(0, 0),IR(25057, 15)/* WriteBackINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {3,IR(0, 0),IR(22093, 15)/* StreamingINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {0,IR(0, 0),IR(14223, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {1,IR(10, 1),IR(25072, 11)/* TensorView */,IR(0, 0),IR(200, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {2,IR(10, 1),IR(25083, 11)/* DecodeFunc */,IR(0, 0),IR(201, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {0,IR(0, 0),IR(25094, 10)/* Undefined */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {1,IR(0, 0),IR(15470, 9)/* Constant */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {2,IR(0, 0),IR(23914, 12)/* ClampToEdge */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {3,IR(0, 0),IR(23932, 7)/* Repeat */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {4,IR(0, 0),IR(23939, 15)/* RepeatMirrored */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {0,IR(0, 0),IR(25104, 8)/* NoneARM */,IR(0, 0),IR(202, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {1,IR(0, 0),IR(25112, 15)/* NontemporalARM */,IR(0, 0),IR(202, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {2,IR(10, 1),IR(25127, 20)/* OutOfBoundsValueARM */,IR(0, 0),IR(202, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {4,IR(10, 1),IR(25147, 24)/* MakeElementAvailableARM */,IR(0, 0),IR(202, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {8,IR(10, 1),IR(25171, 22)/* MakeElementVisibleARM */,IR(0, 0),IR(202, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {16,IR(0, 0),IR(25193, 21)/* NonPrivateElementARM */,IR(0, 0),IR(202, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
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
    case SPV_OPERAND_TYPE_CAPABILITY: return IR(133, 275);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(408, 8);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(416, 3);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(419, 2);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS: return IR(421, 19);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION: return IR(440, 10);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(450, 4);
    case SPV_OPERAND_TYPE_COMPONENT_TYPE: return IR(454, 15);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT: return IR(469, 4);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS: return IR(473, 6);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE: return IR(479, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE: return IR(482, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT: return IR(485, 4);
    case SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(489, 8);
    case SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE: return IR(497, 3);
    case SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS: return IR(500, 16);
    case SPV_OPERAND_TYPE_DEBUG_OPERATION: return IR(516, 9);
    case SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER: return IR(525, 3);
    case SPV_OPERAND_TYPE_DECORATION: return IR(528, 144);
    case SPV_OPERAND_TYPE_DIMENSIONALITY: return IR(672, 8);
    case SPV_OPERAND_TYPE_EXECUTION_MODE: return IR(680, 96);
    case SPV_OPERAND_TYPE_EXECUTION_MODEL: return IR(776, 17);
    case SPV_OPERAND_TYPE_FPDENORM_MODE: return IR(793, 2);
    case SPV_OPERAND_TYPE_FPENCODING: return IR(795, 3);
    case SPV_OPERAND_TYPE_FPOPERATION_MODE: return IR(798, 2);
    case SPV_OPERAND_TYPE_FP_FAST_MATH_MODE: return IR(800, 9);
    case SPV_OPERAND_TYPE_FP_ROUNDING_MODE: return IR(809, 4);
    case SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE: return IR(813, 4);
    case SPV_OPERAND_TYPE_FUNCTION_CONTROL: return IR(817, 6);
    case SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE: return IR(823, 9);
    case SPV_OPERAND_TYPE_GROUP_OPERATION: return IR(832, 7);
    case SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER: return IR(839, 4);
    case SPV_OPERAND_TYPE_IMAGE: return IR(843, 17);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE: return IR(860, 26);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER: return IR(886, 20);
    case SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER: return IR(906, 2);
    case SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS: return IR(908, 3);
    case SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO: return IR(911, 2);
    case SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS: return IR(913, 2);
    case SPV_OPERAND_TYPE_LINKAGE_TYPE: return IR(915, 3);
    case SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL: return IR(918, 5);
    case SPV_OPERAND_TYPE_LOOP_CONTROL: return IR(923, 20);
    case SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(943, 15);
    case SPV_OPERAND_TYPE_MEMORY_ACCESS: return IR(958, 9);
    case SPV_OPERAND_TYPE_MEMORY_MODEL: return IR(967, 4);
    case SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID: return IR(971, 15);
    case SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS: return IR(986, 1);
    case SPV_OPERAND_TYPE_OVERFLOW_MODES: return IR(987, 4);
    case SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT: return IR(991, 1);
    case SPV_OPERAND_TYPE_QUANTIZATION_MODES: return IR(992, 8);
    case SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS: return IR(1000, 3);
    case SPV_OPERAND_TYPE_RAY_FLAGS: return IR(1003, 12);
    case SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE: return IR(1015, 2);
    case SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE: return IR(1017, 3);
    case SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION: return IR(1020, 2);
    case SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE: return IR(1022, 5);
    case SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE: return IR(1027, 2);
    case SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT: return IR(1029, 42);
    case SPV_OPERAND_TYPE_SCOPE_ID: return IR(1071, 7);
    case SPV_OPERAND_TYPE_SELECTION_CONTROL: return IR(1078, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS: return IR(1081, 1);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(1082, 8);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(1090, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(1093, 2);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS: return IR(1095, 20);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION: return IR(1115, 10);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(1125, 4);
    case SPV_OPERAND_TYPE_SOURCE_LANGUAGE: return IR(1129, 14);
    case SPV_OPERAND_TYPE_STORAGE_CLASS: return IR(1143, 28);
    case SPV_OPERAND_TYPE_STORE_CACHE_CONTROL: return IR(1171, 4);
    case SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS: return IR(1175, 3);
    case SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE: return IR(1178, 5);
    case SPV_OPERAND_TYPE_TENSOR_OPERANDS: return IR(1183, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_IMAGE: return IR(843, 17);
    case SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS: return IR(958, 9);
    case SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT: return IR(991, 1);
    case SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS: return IR(473, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(943, 15);
    case SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS: return IR(1000, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_FPENCODING: return IR(795, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS: return IR(1183, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_CAPABILITY: return IR(133, 275);
    default: break;
  }
  return IR(0,0);
}

// Operand names and index into kOperandsByValue, ordered by (operand kind, name)
// The fields in order are:
//   name, either the primary name or an alias, indexing into kStrings
//   index into the kOperandsByValue array
static const std::array<NameIndex, 1283> kOperandNames{{
  {IR(4633, 9), 0}, // 0 ReadOnly in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(4659, 10), 2}, // 1 ReadWrite in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(4649, 10), 1}, // 2 WriteOnly in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(4669, 8), 3}, // 3 Logical in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(4677, 11), 4}, // 4 Physical32 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(4698, 11), 5}, // 5 Physical64 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(4709, 24), 6}, // 6 PhysicalStorageBuffer64 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(4733, 27), 6}, // 7 PhysicalStorageBuffer64EXT in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(6643, 13), 92}, // 8 BaryCoordKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6656, 12), 92}, // 9 BaryCoordNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6038, 20), 68}, // 10 BaryCoordNoPerspAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6058, 28), 69}, // 11 BaryCoordNoPerspCentroidAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6691, 20), 93}, // 12 BaryCoordNoPerspKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6711, 19), 93}, // 13 BaryCoordNoPerspNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6086, 26), 70}, // 14 BaryCoordNoPerspSampleAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6183, 22), 74}, // 15 BaryCoordPullModelAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6112, 19), 71}, // 16 BaryCoordSmoothAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6131, 27), 72}, // 17 BaryCoordSmoothCentroidAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6158, 25), 73}, // 18 BaryCoordSmoothSampleAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5842, 13), 59}, // 19 BaseInstance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5816, 11), 58}, // 20 BaseVertex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4817, 13), 9}, // 21 ClipDistance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6550, 22), 87}, // 22 ClipDistancePerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7849, 12), 131}, // 23 ClusterIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5580, 13), 49}, // 24 CoreCountARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5554, 10), 48}, // 25 CoreIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5593, 13), 50}, // 26 CoreMaxIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4830, 13), 10}, // 27 CullDistance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6572, 22), 88}, // 28 CullDistancePerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7902, 12), 132}, // 29 CullMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6898, 17), 99}, // 30 CullPrimitiveEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7302, 17), 113}, // 31 CurrentRayTimeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5912, 12), 62}, // 32 DeviceIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5855, 10), 60}, // 33 DrawIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5344, 22), 37}, // 34 EnqueuedWorkgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5114, 10), 21}, // 35 FragCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5200, 10), 27}, // 36 FragDepth in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6776, 23), 95}, // 37 FragInvocationCountEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6730, 12), 94}, // 38 FragSizeEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6205, 18), 75}, // 39 FragStencilRefEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6742, 15), 94}, // 40 FragmentSizeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5135, 12), 23}, // 41 FrontFacing in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6462, 16), 83}, // 42 FullyCoveredEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5285, 19), 33}, // 43 GlobalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5379, 15), 39}, // 44 GlobalLinearId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5366, 13), 38}, // 45 GlobalOffset in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5333, 11), 36}, // 46 GlobalSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5210, 17), 28}, // 47 HelperInvocation in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7604, 11), 120}, // 48 HitIsLSSNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7562, 14), 119}, // 49 HitIsSphereNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7784, 33), 128}, // 50 HitKindBackFacingMicroTriangleNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7750, 34), 127}, // 51 HitKindFrontFacingMicroTriangleNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7281, 11), 112}, // 52 HitKindKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7292, 10), 112}, // 53 HitKindNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7732, 18), 126}, // 54 HitLSSPositionsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7835, 14), 130}, // 55 HitLSSRadiiNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7466, 37), 116}, // 56 HitMicroTriangleVertexBarycentricsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7399, 34), 115}, // 57 HitMicroTriangleVertexPositionsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7654, 20), 121}, // 58 HitSpherePositionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7817, 18), 129}, // 59 HitSphereRadiusNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7274, 7), 111}, // 60 HitTNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7342, 30), 114}, // 61 HitTriangleVertexPositionsKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7503, 20), 117}, // 62 IncomingRayFlagsKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7523, 19), 117}, // 63 IncomingRayFlagsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7163, 23), 108}, // 64 InstanceCustomIndexKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7186, 22), 108}, // 65 InstanceCustomIndexNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4852, 11), 12}, // 66 InstanceId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5540, 14), 47}, // 67 InstanceIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4953, 13), 14}, // 68 InvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6799, 22), 95}, // 69 InvocationsPerPixelNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6915, 12), 100}, // 70 LaunchIdKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6927, 11), 100}, // 71 LaunchIdNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6938, 14), 101}, // 72 LaunchSizeKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6952, 13), 101}, // 73 LaunchSizeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4966, 6), 15}, // 74 Layer in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6594, 15), 89}, // 75 LayerPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5267, 18), 32}, // 76 LocalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5304, 21), 34}, // 77 LocalInvocationIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6609, 16), 90}, // 78 MeshViewCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6625, 18), 91}, // 79 MeshViewIndicesNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5470, 21), 43}, // 80 NumEnqueuedSubgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5457, 13), 42}, // 81 NumSubgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5227, 14), 29}, // 82 NumWorkgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7078, 22), 105}, // 83 ObjectRayDirectionKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7100, 21), 105}, // 84 ObjectRayDirectionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7041, 19), 104}, // 85 ObjectRayOriginKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7060, 18), 104}, // 86 ObjectRayOriginNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7208, 17), 109}, // 87 ObjectToWorldKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7225, 16), 109}, // 88 ObjectToWorldNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5100, 14), 20}, // 89 PatchVertices in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5124, 11), 22}, // 90 PointCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4807, 10), 8}, // 91 PointSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4791, 9), 7}, // 92 Position in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6402, 18), 81}, // 93 PositionPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6514, 17), 85}, // 94 PrimitiveCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4863, 12), 13}, // 95 PrimitiveId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6531, 19), 86}, // 96 PrimitiveIndicesNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6846, 24), 97}, // 97 PrimitiveLineIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6821, 25), 96}, // 98 PrimitivePointIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5865, 24), 61}, // 99 PrimitiveShadingRateKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6870, 28), 98}, // 100 PrimitiveTriangleIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7542, 20), 118}, // 101 RayGeometryIndexKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7142, 11), 107}, // 102 RayTmaxKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7153, 10), 107}, // 103 RayTmaxNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7121, 11), 106}, // 104 RayTminKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7132, 10), 106}, // 105 RayTminNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6240, 29), 76}, // 106 RemainingRecursionLevelsAMDX in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7706, 10), 123}, // 107 SMCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7725, 7), 125}, // 108 SMIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5147, 9), 24}, // 109 SampleId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5189, 11), 26}, // 110 SampleMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5174, 15), 25}, // 111 SamplePosition in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6339, 20), 79}, // 112 SecondaryPositionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6378, 24), 80}, // 113 SecondaryViewportMaskNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6287, 16), 77}, // 114 ShaderIndexAMDX in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5956, 15), 64}, // 115 ShadingRateKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5629, 15), 53}, // 116 SubgroupEqMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5644, 18), 53}, // 117 SubgroupEqMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5684, 15), 54}, // 118 SubgroupGeMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5699, 18), 54}, // 119 SubgroupGeMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5717, 15), 55}, // 120 SubgroupGtMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5732, 18), 55}, // 121 SubgroupGtMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5491, 11), 44}, // 122 SubgroupId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5750, 15), 56}, // 123 SubgroupLeMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5765, 18), 56}, // 124 SubgroupLeMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5502, 26), 45}, // 125 SubgroupLocalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5783, 15), 57}, // 126 SubgroupLtMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5798, 18), 57}, // 127 SubgroupLtMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5441, 16), 41}, // 128 SubgroupMaxSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5394, 13), 40}, // 129 SubgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6502, 12), 84}, // 130 TaskCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5090, 10), 19}, // 131 TessCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5075, 15), 18}, // 132 TessLevelInner in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5060, 15), 17}, // 133 TessLevelOuter in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6020, 18), 67}, // 134 TileApronSizeQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6002, 18), 66}, // 135 TileDimensionQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5971, 15), 65}, // 136 TileOffsetQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4843, 9), 11}, // 137 VertexId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5528, 12), 46}, // 138 VertexIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5936, 10), 63}, // 139 ViewIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5012, 14), 16}, // 140 ViewportIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6303, 15), 78}, // 141 ViewportMaskNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6440, 22), 82}, // 142 ViewportMaskPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5606, 10), 51}, // 143 WarpIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7716, 9), 124}, // 144 WarpIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5616, 13), 52}, // 145 WarpMaxIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7674, 13), 122}, // 146 WarpsPerSMNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5325, 8), 35}, // 147 WorkDim in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5255, 12), 31}, // 148 WorkgroupId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5241, 14), 30}, // 149 WorkgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7000, 21), 103}, // 150 WorldRayDirectionKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7021, 20), 103}, // 151 WorldRayDirectionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6965, 18), 102}, // 152 WorldRayOriginKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6983, 17), 102}, // 153 WorldRayOriginNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7241, 17), 110}, // 154 WorldToObjectKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7258, 16), 110}, // 155 WorldToObjectNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4688, 10), 137}, // 156 Addresses in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12919, 34), 359}, // 157 ArbitraryPrecisionFixedPointINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12607, 37), 347}, // 158 ArbitraryPrecisionFloatingPointINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12575, 32), 346}, // 159 ArbitraryPrecisionIntegersINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13476, 19), 384}, // 160 ArithmeticFenceEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12240, 9), 332}, // 161 AsmINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13393, 20), 380}, // 162 AtomicFloat16AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12295, 23), 335}, // 163 AtomicFloat16MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11768, 22), 310}, // 164 AtomicFloat16VectorNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13309, 20), 376}, // 165 AtomicFloat32AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12249, 23), 333}, // 166 AtomicFloat32MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13329, 20), 377}, // 167 AtomicFloat64AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12272, 23), 334}, // 168 AtomicFloat64MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8082, 14), 153}, // 169 AtomicStorage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9469, 17), 229}, // 170 AtomicStorageOps in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13434, 24), 382}, // 171 BFloat16ConversionINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10091, 29), 263}, // 172 BFloat16CooperativeMatrixKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10069, 22), 262}, // 173 BFloat16DotProductKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10053, 16), 261}, // 174 BFloat16TypeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14072, 20), 407}, // 175 BindlessImagesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11705, 18), 307}, // 176 BindlessTextureNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13246, 16), 372}, // 177 BitInstructions in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13018, 19), 363}, // 178 BlockingPipesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14033, 19), 405}, // 179 CacheControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4817, 13), 163}, // 180 ClipDistance in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11363, 32), 296}, // 181 ComputeDerivativeGroupLinearKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11395, 31), 296}, // 182 ComputeDerivativeGroupLinearNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10243, 31), 275}, // 183 ComputeDerivativeGroupQuadsKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10274, 30), 275}, // 184 ComputeDerivativeGroupQuadsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11945, 30), 319}, // 185 CooperativeMatrixBlockLoadsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9838, 32), 248}, // 186 CooperativeMatrixConversionQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11838, 31), 316}, // 187 CooperativeMatrixConversionsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9117, 21), 370}, // 188 CooperativeMatrixKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9052, 28), 211}, // 189 CooperativeMatrixLayoutsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11451, 20), 298}, // 190 CooperativeMatrixNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11869, 40), 317}, // 191 CooperativeMatrixPerElementOperationsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11808, 30), 315}, // 192 CooperativeMatrixReductionsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11909, 36), 318}, // 193 CooperativeMatrixTensorAddressingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11748, 20), 309}, // 194 CooperativeVectorNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11975, 28), 320}, // 195 CooperativeVectorTrainingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5564, 16), 203}, // 196 CoreBuiltinsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4830, 13), 164}, // 197 CullDistance in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13413, 21), 381}, // 198 DebugInfoModuleINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11574, 25), 303}, // 199 DemoteToHelperInvocation in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11599, 28), 303}, // 200 DemoteToHelperInvocationEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9608, 18), 235}, // 201 DenormFlushToZero in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9593, 15), 234}, // 202 DenormPreserve in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8529, 18), 182}, // 203 DerivativeControl in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8053, 14), 151}, // 204 DeviceEnqueue in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5924, 12), 225}, // 205 DeviceGroup in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11627, 23), 304}, // 206 DisplacementMicromapNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13197, 11), 368}, // 207 DotProduct in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13091, 22), 366}, // 208 DotProductInput4x8Bit in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13113, 25), 366}, // 209 DotProductInput4x8BitKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13138, 28), 367}, // 210 DotProductInput4x8BitPacked in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13166, 31), 367}, // 211 DotProductInput4x8BitPackedKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13050, 19), 365}, // 212 DotProductInputAll in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13069, 22), 365}, // 213 DotProductInputAllKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13208, 14), 368}, // 214 DotProductKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5827, 15), 216}, // 215 DrawParameters in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12352, 16), 338}, // 216 ExpectAssumeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13302, 7), 375}, // 217 FMAKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12555, 20), 345}, // 218 FPFastMathModeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13610, 28), 390}, // 219 FPGAArgumentInterfacesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12895, 24), 358}, // 220 FPGABufferLocationINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12768, 27), 353}, // 221 FPGAClusterAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13495, 29), 385}, // 222 FPGAClusterAttributesV2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12809, 20), 355}, // 223 FPGADSPControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12855, 40), 357}, // 224 FPGAInvocationPipeliningAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12718, 26), 351}, // 225 FPGAKernelAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13524, 28), 386}, // 226 FPGAKernelAttributesv2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13586, 24), 389}, // 227 FPGALatencyControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12674, 22), 349}, // 228 FPGALoopControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12744, 24), 352}, // 229 FPGAMemoryAccessesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12529, 26), 344}, // 230 FPGAMemoryAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13037, 13), 364}, // 231 FPGARegINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13570, 16), 388}, // 232 FPMaxErrorINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7967, 8), 142}, // 233 Float16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7953, 14), 141}, // 234 Float16Buffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9893, 16), 250}, // 235 Float16ImageAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7975, 8), 143}, // 236 Float64 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9090, 27), 213}, // 237 Float8CooperativeMatrixEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9080, 10), 212}, // 238 Float8EXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13287, 15), 374}, // 239 FloatControls2 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12148, 23), 328}, // 240 FloatingPointModeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6668, 23), 274}, // 241 FragmentBarycentricKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10221, 22), 274}, // 242 FragmentBarycentricNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6757, 19), 276}, // 243 FragmentDensityEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6478, 24), 270}, // 244 FragmentFullyCoveredEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9931, 16), 252}, // 245 FragmentMaskAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11542, 32), 302}, // 246 FragmentShaderPixelInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11471, 33), 299}, // 247 FragmentShaderSampleInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11504, 38), 300}, // 248 FragmentShaderShadingRateInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5889, 23), 214}, // 249 FragmentShadingRateKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12503, 26), 343}, // 250 FunctionFloatControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12194, 22), 330}, // 251 FunctionPointersINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13933, 22), 401}, // 252 FunctionVariantsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8374, 15), 169}, // 253 GenericPointer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4875, 9), 135}, // 254 Geometry in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8124, 18), 156}, // 255 GeometryPointSize in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10149, 28), 265}, // 256 GeometryShaderPassthroughNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8587, 16), 185}, // 257 GeometryStreams in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13668, 35), 392}, // 258 GlobalVariableFPGADecorationsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13638, 30), 391}, // 259 GlobalVariableHostAccessINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9043, 9), 210}, // 260 GraphARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5407, 16), 192}, // 261 GroupNonUniform in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8726, 26), 194}, // 262 GroupNonUniformArithmetic in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5662, 22), 195}, // 263 GroupNonUniformBallot in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8806, 25), 198}, // 264 GroupNonUniformClustered in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10318, 29), 277}, // 265 GroupNonUniformPartitionedNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8831, 20), 199}, // 266 GroupNonUniformQuad in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13262, 25), 373}, // 267 GroupNonUniformRotateKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8752, 23), 196}, // 268 GroupNonUniformShuffle in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8775, 31), 197}, // 269 GroupNonUniformShuffleRelative in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8706, 20), 193}, // 270 GroupNonUniformVote in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13955, 26), 402}, // 271 GroupUniformArithmeticKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8046, 7), 150}, // 272 Groups in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13005, 13), 362}, // 273 IOPipesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8443, 8), 175}, // 274 Image1D in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8002, 11), 146}, // 275 ImageBasic in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8465, 12), 178}, // 276 ImageBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8320, 15), 165}, // 277 ImageCubeArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10204, 17), 272}, // 278 ImageFootprintNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9909, 22), 251}, // 279 ImageGatherBiasLodAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8142, 20), 157}, // 280 ImageGatherExtended in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8477, 13), 179}, // 281 ImageMSArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8028, 12), 148}, // 282 ImageMipmap in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8518, 11), 181}, // 283 ImageQuery in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8013, 15), 147}, // 284 ImageReadWrite in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9947, 21), 254}, // 285 ImageReadWriteLodAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8352, 10), 167}, // 286 ImageRect in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12216, 24), 331}, // 287 IndirectReferencesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8394, 16), 171}, // 288 InputAttachment in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10433, 36), 280}, // 289 InputAttachmentArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10469, 39), 280}, // 290 InputAttachmentArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10974, 39), 287}, // 291 InputAttachmentArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11013, 42), 287}, // 292 InputAttachmentArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8096, 6), 154}, // 293 Int16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10026, 27), 260}, // 294 Int4CooperativeMatrixINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10012, 14), 259}, // 295 Int4TypeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7983, 6), 144}, // 296 Int64 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7989, 13), 145}, // 297 Int64Atomics in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9968, 14), 255}, // 298 Int64ImageEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8389, 5), 170}, // 299 Int8 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12171, 23), 329}, // 300 IntegerFunctions2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8547, 22), 183}, // 301 InterpolationFunction in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4642, 7), 139}, // 302 Kernel in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12696, 22), 350}, // 303 KernelAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7936, 8), 138}, // 304 Linkage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8067, 15), 152}, // 305 LiteralSampler in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13349, 20), 378}, // 306 LongCompositesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12795, 14), 354}, // 307 LoopFuseINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14008, 25), 404}, // 308 MaskedGatherScatterINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7929, 7), 133}, // 309 Matrix in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12829, 26), 356}, // 310 MemoryAccessAliasingINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4938, 15), 273}, // 311 MeshShadingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4924, 14), 271}, // 312 MeshShadingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8426, 7), 173}, // 313 MinLod in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5946, 10), 226}, // 314 MultiView in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5026, 14), 188}, // 315 MultiViewport in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8681, 13), 190}, // 316 NamedBarrier in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13369, 11), 379}, // 317 OptNoneEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13380, 13), 379}, // 318 OptNoneINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6420, 20), 269}, // 319 PerViewAttributesNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4760, 31), 295}, // 320 PhysicalStorageBufferAddresses in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11329, 34), 295}, // 321 PhysicalStorageBufferAddressesEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8694, 12), 191}, // 322 PipeStorage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8040, 6), 149}, // 323 Pipes in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9997, 15), 258}, // 324 QuadControlKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11790, 18), 312}, // 325 RawAccessChainsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7914, 15), 369}, // 326 RayCullMaskKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9706, 12), 240}, // 327 RayQueryKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11723, 25), 308}, // 328 RayQueryPositionFetchKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9683, 23), 239}, // 329 RayQueryProvisionalKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7861, 41), 321}, // 330 RayTracingClusterAccelerationStructureNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7433, 33), 311}, // 331 RayTracingDisplacementMicromapNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4910, 14), 243}, // 332 RayTracingKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7615, 39), 314}, // 333 RayTracingLinearSweptSpheresGeometryNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7319, 23), 292}, // 334 RayTracingMotionBlurNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4897, 13), 291}, // 335 RayTracingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11650, 29), 305}, // 336 RayTracingOpacityMicromapEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7372, 27), 290}, // 337 RayTracingPositionFetchKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11426, 25), 297}, // 338 RayTracingProvisionalKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7576, 28), 313}, // 339 RayTracingSpheresGeometryNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9737, 32), 242}, // 340 RayTraversalPrimitiveCullingKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14052, 20), 406}, // 341 RegisterLimitsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13222, 24), 371}, // 342 ReplicatedCompositesEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12127, 21), 327}, // 343 RoundToInfinityINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9651, 16), 237}, // 344 RoundingModeRTE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9667, 16), 238}, // 345 RoundingModeRTZ in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12976, 29), 361}, // 346 RuntimeAlignedAttributeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10384, 23), 279}, // 347 RuntimeDescriptorArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10407, 26), 279}, // 348 RuntimeDescriptorArrayEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10120, 29), 264}, // 349 SampleMaskOverrideCoverageNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9486, 28), 230}, // 350 SampleMaskPostDepthCoverage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5156, 18), 166}, // 351 SampleRateShading in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8433, 10), 174}, // 352 Sampled1D in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8451, 14), 177}, // 353 SampledBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8335, 17), 176}, // 354 SampledCubeArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8220, 33), 160}, // 355 SampledImageArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10747, 36), 284}, // 356 SampledImageArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10783, 39), 284}, // 357 SampledImageArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8362, 12), 168}, // 358 SampledRect in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4800, 7), 134}, // 359 Shader in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9982, 15), 256}, // 360 ShaderClockKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6269, 18), 257}, // 361 ShaderEnqueueAMDX in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11679, 26), 306}, // 362 ShaderInvocationReorderNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4972, 12), 200}, // 363 ShaderLayer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10347, 17), 278}, // 364 ShaderNonUniform in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10364, 20), 278}, // 365 ShaderNonUniformEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7687, 19), 301}, // 366 ShaderSMBuiltinsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6359, 19), 268}, // 367 ShaderStereoViewNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5040, 20), 201}, // 368 ShaderViewportIndex in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4984, 28), 266}, // 369 ShaderViewportIndexLayerEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10177, 27), 266}, // 370 ShaderViewportIndexLayerNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6318, 21), 267}, // 371 ShaderViewportMaskNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10304, 14), 276}, // 372 ShadingRateNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9626, 25), 236}, // 373 SignedZeroInfNanPreserve in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8410, 16), 172}, // 374 SparseResidency in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13912, 21), 400}, // 375 SpecConditionalINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13458, 18), 383}, // 376 SplitBarrierINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6223, 17), 253}, // 377 StencilExportEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9274, 25), 221}, // 378 StorageBuffer16BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9514, 24), 231}, // 379 StorageBuffer8BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8253, 34), 161}, // 380 StorageBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10822, 37), 285}, // 381 StorageBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10859, 40), 285}, // 382 StorageBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8287, 33), 162}, // 383 StorageImageArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10899, 36), 286}, // 384 StorageImageArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10935, 39), 286}, // 385 StorageImageArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8490, 28), 180}, // 386 StorageImageExtendedFormats in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8162, 24), 158}, // 387 StorageImageMultisample in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8603, 30), 186}, // 388 StorageImageReadWithoutFormat in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8633, 31), 187}, // 389 StorageImageWriteWithoutFormat in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9401, 21), 224}, // 390 StorageInputOutput16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9379, 22), 223}, // 391 StoragePushConstant16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9572, 21), 233}, // 392 StoragePushConstant8 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8966, 37), 208}, // 393 StorageTensorArrayDynamicIndexingARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9003, 40), 209}, // 394 StorageTensorArrayNonUniformIndexingARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10589, 39), 282}, // 395 StorageTexelBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10628, 42), 282}, // 396 StorageTexelBufferArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11142, 42), 289}, // 397 StorageTexelBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11184, 45), 289}, // 398 StorageTexelBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9362, 17), 222}, // 399 StorageUniform16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9299, 28), 221}, // 400 StorageUniformBufferBlock16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13731, 23), 394}, // 401 Subgroup2DBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13754, 30), 395}, // 402 Subgroup2DBlockTransformINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13784, 30), 396}, // 403 Subgroup2DBlockTransposeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12439, 39), 341}, // 404 SubgroupAvcMotionEstimationChromaINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12368, 33), 339}, // 405 SubgroupAvcMotionEstimationINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12401, 38), 340}, // 406 SubgroupAvcMotionEstimationIntraINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5423, 18), 215}, // 407 SubgroupBallotKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12043, 27), 324}, // 408 SubgroupBufferBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13703, 28), 393}, // 409 SubgroupBufferPrefetchINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8664, 17), 189}, // 410 SubgroupDispatch in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12070, 26), 325}, // 411 SubgroupImageBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12096, 31), 326}, // 412 SubgroupImageMediaBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13814, 38), 397}, // 413 SubgroupMatrixMultiplyAccumulateINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12022, 21), 323}, // 414 SubgroupShuffleINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9258, 16), 220}, // 415 SubgroupVoteKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13552, 18), 387}, // 416 TaskSequenceINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12003, 19), 322}, // 417 TensorAddressingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13981, 27), 403}, // 418 TensorFloat32RoundingINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8955, 11), 207}, // 419 TensorsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13852, 28), 398}, // 420 TernaryBitwiseFunctionINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4884, 13), 136}, // 421 Tessellation in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8102, 22), 155}, // 422 TessellationPointSize in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9870, 23), 249}, // 423 TextureBlockMatch2QCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9816, 22), 246}, // 424 TextureBlockMatchQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9795, 21), 245}, // 425 TextureBoxFilterQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9769, 26), 244}, // 426 TextureSampleWeightedQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8869, 28), 204}, // 427 TileImageColorReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8897, 28), 205}, // 428 TileImageDepthReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8925, 30), 206}, // 429 TileImageStencilReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5986, 16), 247}, // 430 TileShadingQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8569, 18), 184}, // 431 TransformFeedback in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12953, 23), 360}, // 432 USMStorageClassesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9327, 35), 222}, // 433 UniformAndStorageBuffer16BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9538, 34), 232}, // 434 UniformAndStorageBuffer8BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8186, 34), 159}, // 435 UniformBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10670, 37), 283}, // 436 UniformBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10707, 40), 283}, // 437 UniformBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8851, 18), 202}, // 438 UniformDecoration in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10508, 39), 281}, // 439 UniformTexelBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10547, 42), 281}, // 440 UniformTexelBufferArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11055, 42), 288}, // 441 UniformTexelBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11097, 45), 288}, // 442 UniformTexelBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12644, 30), 348}, // 443 UnstructuredLoopControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9718, 19), 241}, // 444 UntypedPointersKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13880, 32), 399}, // 445 UntypedVariableLengthArrayINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12478, 25), 342}, // 446 VariableLengthArrayINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9452, 17), 228}, // 447 VariablePointers in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9422, 30), 227}, // 448 VariablePointersStorageBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7944, 9), 140}, // 449 Vector16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12337, 15), 337}, // 450 VectorAnyINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12318, 19), 336}, // 451 VectorComputeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11229, 18), 293}, // 452 VulkanMemoryModel in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11268, 29), 294}, // 453 VulkanMemoryModelDeviceScope in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11297, 32), 294}, // 454 VulkanMemoryModelDeviceScopeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11247, 21), 293}, // 455 VulkanMemoryModelKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9214, 44), 219}, // 456 WorkgroupMemoryExplicitLayout16BitAccessKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9171, 43), 218}, // 457 WorkgroupMemoryExplicitLayout8BitAccessKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9138, 33), 217}, // 458 WorkgroupMemoryExplicitLayoutKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14104, 8), 409}, // 459 Address in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14112, 8), 410}, // 460 Boolean in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14120, 6), 411}, // 461 Float in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14126, 7), 412}, // 462 Signed in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14133, 11), 413}, // 463 SignedChar in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14144, 9), 414}, // 464 Unsigned in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14153, 13), 415}, // 465 UnsignedChar in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14092, 12), 408}, // 466 Unspecified in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14166, 6), 416}, // 467 Class in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(14172, 10), 417}, // 468 Structure in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(14182, 6), 418}, // 469 Union in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(14203, 20), 420}, // 470 ImportedDeclaration in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(14188, 15), 419}, // 471 ImportedModule in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(14312, 15), 428}, // 472 FlagArtificial in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14327, 13), 429}, // 473 FlagExplicit in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14300, 12), 427}, // 474 FlagFwdDecl in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14390, 21), 433}, // 475 FlagIndirectVariable in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14283, 17), 426}, // 476 FlagIsDefinition in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14467, 16), 437}, // 477 FlagIsEnumClass in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14271, 12), 425}, // 478 FlagIsLocal in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14451, 16), 436}, // 479 FlagIsOptimized in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14244, 14), 423}, // 480 FlagIsPrivate in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14228, 16), 422}, // 481 FlagIsProtected in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14258, 13), 424}, // 482 FlagIsPublic in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14411, 20), 434}, // 483 FlagLValueReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14355, 18), 431}, // 484 FlagObjectPointer in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14340, 15), 430}, // 485 FlagPrototyped in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14431, 20), 435}, // 486 FlagRValueReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14373, 17), 432}, // 487 FlagStaticMember in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14503, 24), 439}, // 488 FlagTypePassByReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14483, 20), 438}, // 489 FlagTypePassByValue in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14223, 5), 421}, // 490 None in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14588, 9), 444}, // 491 BitPiece in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14620, 7), 448}, // 492 Constu in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14527, 6), 440}, // 493 Deref in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14627, 9), 449}, // 494 Fragment in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14538, 6), 442}, // 495 Minus in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14533, 5), 441}, // 496 Plus in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14577, 11), 443}, // 497 PlusUconst in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14609, 11), 447}, // 498 StackValue in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14597, 5), 445}, // 499 Swap in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14602, 7), 446}, // 500 Xderef in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14672, 11), 453}, // 501 AtomicType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14636, 10), 450}, // 502 ConstType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14659, 13), 452}, // 503 RestrictType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14646, 13), 451}, // 504 VolatileType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14683, 10), 454}, // 505 Float16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14693, 10), 455}, // 506 Float32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14703, 10), 456}, // 507 Float64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14871, 12), 467}, // 508 FloatE4M3NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14883, 12), 468}, // 509 FloatE5M2NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14726, 14), 458}, // 510 SignedInt16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14740, 14), 459}, // 511 SignedInt32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14754, 14), 460}, // 512 SignedInt64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14713, 13), 457}, // 513 SignedInt8NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14831, 19), 465}, // 514 SignedInt8PackedNV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14783, 16), 462}, // 515 UnsignedInt16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14799, 16), 463}, // 516 UnsignedInt32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14815, 16), 464}, // 517 UnsignedInt64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14768, 15), 461}, // 518 UnsignedInt8NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14850, 21), 466}, // 519 UnsignedInt8PackedNV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14947, 28), 472}, // 520 ColumnBlockedInterleavedARM in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(14907, 15), 470}, // 521 ColumnMajorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(14922, 25), 471}, // 522 RowBlockedInterleavedARM in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(14895, 12), 469}, // 523 RowMajorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(14983, 27), 474}, // 524 MatrixASignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(15010, 27), 475}, // 525 MatrixBSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(15037, 27), 476}, // 526 MatrixCSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(15064, 32), 477}, // 527 MatrixResultSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(14975, 8), 473}, // 528 NoneKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(15096, 26), 478}, // 529 SaturatingAccumulationKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(15133, 4), 481}, // 530 2x2 in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(15126, 7), 480}, // 531 Column in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(15122, 4), 479}, // 532 Row in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(15137, 11), 482}, // 533 MatrixAKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(15159, 21), 484}, // 534 MatrixAccumulatorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(15148, 11), 483}, // 535 MatrixBKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(15191, 14), 486}, // 536 ColumnMajorNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(15205, 21), 487}, // 537 InferencingOptimalNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(15180, 11), 485}, // 538 RowMajorNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(15226, 18), 488}, // 539 TrainingOptimalNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(14104, 8), 490}, // 540 Address in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14112, 8), 491}, // 541 Boolean in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14120, 6), 492}, // 542 Float in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14126, 7), 493}, // 543 Signed in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14133, 11), 494}, // 544 SignedChar in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14144, 9), 495}, // 545 Unsigned in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14153, 13), 496}, // 546 UnsignedChar in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14092, 12), 489}, // 547 Unspecified in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14166, 6), 497}, // 548 Class in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(14172, 10), 498}, // 549 Structure in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(14182, 6), 499}, // 550 Union in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(14312, 15), 507}, // 551 FlagArtificial in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14327, 13), 508}, // 552 FlagExplicit in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14300, 12), 506}, // 553 FlagFwdDecl in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14390, 21), 512}, // 554 FlagIndirectVariable in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14283, 17), 505}, // 555 FlagIsDefinition in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14271, 12), 504}, // 556 FlagIsLocal in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14451, 16), 515}, // 557 FlagIsOptimized in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14244, 14), 502}, // 558 FlagIsPrivate in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14228, 16), 501}, // 559 FlagIsProtected in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14258, 13), 503}, // 560 FlagIsPublic in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14411, 20), 513}, // 561 FlagLValueReference in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14355, 18), 510}, // 562 FlagObjectPointer in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14340, 15), 509}, // 563 FlagPrototyped in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14431, 20), 514}, // 564 FlagRValueReference in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14373, 17), 511}, // 565 FlagStaticMember in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14223, 5), 500}, // 566 None in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14588, 9), 520}, // 567 BitPiece in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14620, 7), 524}, // 568 Constu in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14527, 6), 516}, // 569 Deref in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14538, 6), 518}, // 570 Minus in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14533, 5), 517}, // 571 Plus in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14577, 11), 519}, // 572 PlusUconst in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14609, 11), 523}, // 573 StackValue in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14597, 5), 521}, // 574 Swap in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14602, 7), 522}, // 575 Xderef in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14636, 10), 525}, // 576 ConstType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(14659, 13), 527}, // 577 RestrictType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(14646, 13), 526}, // 578 VolatileType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(17468, 16), 642}, // 579 AliasScopeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15453, 8), 547}, // 580 Aliased in SPV_OPERAND_TYPE_DECORATION
  {IR(16571, 15), 600}, // 581 AliasedPointer in SPV_OPERAND_TYPE_DECORATION
  {IR(16586, 18), 600}, // 582 AliasedPointerEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(15931, 10), 571}, // 583 Alignment in SPV_OPERAND_TYPE_DECORATION
  {IR(15975, 12), 573}, // 584 AlignmentId in SPV_OPERAND_TYPE_DECORATION
  {IR(15304, 12), 534}, // 585 ArrayStride in SPV_OPERAND_TYPE_DECORATION
  {IR(17249, 14), 630}, // 586 BankBitsINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17088, 15), 623}, // 587 BankwidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15608, 8), 560}, // 588 Binding in SPV_OPERAND_TYPE_DECORATION
  {IR(16652, 16), 603}, // 589 BindlessImageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16634, 18), 602}, // 590 BindlessSamplerNV in SPV_OPERAND_TYPE_DECORATION
  {IR(15268, 6), 530}, // 591 Block in SPV_OPERAND_TYPE_DECORATION
  {IR(16115, 22), 580}, // 592 BlockMatchSamplerQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(16093, 22), 579}, // 593 BlockMatchTextureQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(16683, 13), 605}, // 594 BoundImageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16668, 15), 604}, // 595 BoundSamplerNV in SPV_OPERAND_TYPE_DECORATION
  {IR(15274, 12), 531}, // 596 BufferBlock in SPV_OPERAND_TYPE_DECORATION
  {IR(17561, 20), 647}, // 597 BufferLocationINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15385, 8), 539}, // 598 BuiltIn in SPV_OPERAND_TYPE_DECORATION
  {IR(17331, 19), 635}, // 599 BurstCoalesceINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15351, 8), 538}, // 600 CPacked in SPV_OPERAND_TYPE_DECORATION
  {IR(18371, 22), 670}, // 601 CacheControlLoadINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18430, 23), 671}, // 602 CacheControlStoreINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17350, 15), 636}, // 603 CacheSizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15418, 9), 543}, // 604 Centroid in SPV_OPERAND_TYPE_DECORATION
  {IR(16736, 13), 608}, // 605 ClobberINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15479, 9), 550}, // 606 Coherent in SPV_OPERAND_TYPE_DECORATION
  {IR(15295, 9), 533}, // 607 ColMajor in SPV_OPERAND_TYPE_DECORATION
  {IR(15592, 10), 558}, // 608 Component in SPV_OPERAND_TYPE_DECORATION
  {IR(18318, 17), 669}, // 609 ConditionalINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17870, 27), 657}, // 610 ConduitKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15470, 9), 549}, // 611 Constant in SPV_OPERAND_TYPE_DECORATION
  {IR(16882, 14), 615}, // 612 CounterBuffer in SPV_OPERAND_TYPE_DECORATION
  {IR(15616, 14), 561}, // 613 DescriptorSet in SPV_OPERAND_TYPE_DECORATION
  {IR(17365, 28), 637}, // 614 DontStaticallyCoalesceINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17141, 16), 626}, // 615 DoublepumpINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16137, 18), 581}, // 616 ExplicitInterpAMD in SPV_OPERAND_TYPE_DECORATION
  {IR(15801, 15), 567}, // 617 FPFastMathMode in SPV_OPERAND_TYPE_DECORATION
  {IR(17789, 26), 654}, // 618 FPMaxErrorDecorationINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15751, 15), 566}, // 619 FPRoundingMode in SPV_OPERAND_TYPE_DECORATION
  {IR(15407, 5), 541}, // 620 Flat in SPV_OPERAND_TYPE_DECORATION
  {IR(17263, 20), 631}, // 621 ForcePow2DepthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15703, 14), 565}, // 622 FuncParamAttr in SPV_OPERAND_TYPE_DECORATION
  {IR(16793, 21), 611}, // 623 FuncParamIOKindINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17024, 24), 619}, // 624 FunctionDenormModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17634, 31), 649}, // 625 FunctionFloatingPointModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16967, 26), 618}, // 626 FunctionRoundingModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17424, 25), 640}, // 627 FuseLoopsInFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15340, 11), 537}, // 628 GLSLPacked in SPV_OPERAND_TYPE_DECORATION
  {IR(15329, 11), 536}, // 629 GLSLShared in SPV_OPERAND_TYPE_DECORATION
  {IR(16856, 26), 614}, // 630 GlobalVariableOffsetINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16604, 30), 601}, // 631 HitObjectShaderRecordBufferNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16896, 24), 615}, // 632 HlslCounterBufferGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(16933, 19), 616}, // 633 HlslSemanticGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(18213, 16), 666}, // 634 HostAccessINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17581, 19), 648}, // 635 IOPipeStorageINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18290, 28), 668}, // 636 ImplementInRegisterMapINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15602, 6), 559}, // 637 Index in SPV_OPERAND_TYPE_DECORATION
  {IR(18276, 14), 667}, // 638 InitModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17497, 24), 644}, // 639 InitiationIntervalINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15910, 21), 570}, // 640 InputAttachmentIndex in SPV_OPERAND_TYPE_DECORATION
  {IR(15434, 10), 545}, // 641 Invariant in SPV_OPERAND_TYPE_DECORATION
  {IR(17840, 30), 656}, // 642 LatencyControlConstraintINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17815, 25), 655}, // 643 LatencyControlLabelINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15878, 18), 568}, // 644 LinkageAttributes in SPV_OPERAND_TYPE_DECORATION
  {IR(15583, 9), 557}, // 645 Location in SPV_OPERAND_TYPE_DECORATION
  {IR(17928, 33), 659}, // 646 MMHostInterfaceAddressWidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17961, 30), 660}, // 647 MMHostInterfaceDataWidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17991, 28), 661}, // 648 MMHostInterfaceLatencyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18087, 29), 663}, // 649 MMHostInterfaceMaxBurstINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18053, 34), 662}, // 650 MMHostInterfaceReadWriteModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18116, 32), 664}, // 651 MMHostInterfaceWaitRequestINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17449, 19), 641}, // 652 MathOpDSPModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15316, 13), 535}, // 653 MatrixStride in SPV_OPERAND_TYPE_DECORATION
  {IR(15941, 14), 572}, // 654 MaxByteOffset in SPV_OPERAND_TYPE_DECORATION
  {IR(15987, 16), 574}, // 655 MaxByteOffsetId in SPV_OPERAND_TYPE_DECORATION
  {IR(17521, 20), 645}, // 656 MaxConcurrencyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17103, 22), 624}, // 657 MaxPrivateCopiesINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17157, 19), 627}, // 658 MaxReplicatesINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17725, 18), 652}, // 659 MediaBlockIOINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17062, 12), 621}, // 660 MemoryINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17196, 11), 629}, // 661 MergeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17484, 13), 643}, // 662 NoAliasINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15896, 14), 569}, // 663 NoContraction in SPV_OPERAND_TYPE_DECORATION
  {IR(15393, 14), 540}, // 664 NoPerspective in SPV_OPERAND_TYPE_DECORATION
  {IR(16047, 13), 576}, // 665 NoSignedWrap in SPV_OPERAND_TYPE_DECORATION
  {IR(16060, 15), 577}, // 666 NoUnsignedWrap in SPV_OPERAND_TYPE_DECORATION
  {IR(16187, 20), 583}, // 667 NodeMaxPayloadsAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(16155, 32), 582}, // 668 NodeSharesPayloadLimitsWithAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(15500, 12), 552}, // 669 NonReadable in SPV_OPERAND_TYPE_DECORATION
  {IR(16511, 11), 598}, // 670 NonUniform in SPV_OPERAND_TYPE_DECORATION
  {IR(16522, 14), 598}, // 671 NonUniformEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(15488, 12), 551}, // 672 NonWritable in SPV_OPERAND_TYPE_DECORATION
  {IR(17074, 14), 622}, // 673 NumbanksINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15630, 7), 562}, // 674 Offset in SPV_OPERAND_TYPE_DECORATION
  {IR(16355, 19), 590}, // 675 OverrideCoverageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16374, 14), 591}, // 676 PassthroughNV in SPV_OPERAND_TYPE_DECORATION
  {IR(15412, 6), 542}, // 677 Patch in SPV_OPERAND_TYPE_DECORATION
  {IR(16327, 28), 589}, // 678 PayloadDispatchIndirectAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(16302, 25), 588}, // 679 PayloadNodeArraySizeAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(16250, 25), 586}, // 680 PayloadNodeBaseIndexAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(16230, 20), 585}, // 681 PayloadNodeNameAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(16275, 27), 587}, // 682 PayloadNodeSparseArrayAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(16435, 16), 594}, // 683 PerPrimitiveEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(16451, 15), 594}, // 684 PerPrimitiveNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16476, 10), 596}, // 685 PerTaskNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16486, 13), 597}, // 686 PerVertexKHR in SPV_OPERAND_TYPE_DECORATION
  {IR(16499, 12), 597}, // 687 PerVertexNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16466, 10), 595}, // 688 PerViewNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17541, 20), 646}, // 689 PipelineEnableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17393, 14), 638}, // 690 PrefetchINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16710, 26), 607}, // 691 ReferencedIndirectlyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17048, 14), 620}, // 692 RegisterINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17897, 31), 658}, // 693 RegisterMapKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15244, 17), 528}, // 694 RelaxedPrecision in SPV_OPERAND_TYPE_DECORATION
  {IR(15444, 9), 546}, // 695 Restrict in SPV_OPERAND_TYPE_DECORATION
  {IR(16536, 16), 599}, // 696 RestrictPointer in SPV_OPERAND_TYPE_DECORATION
  {IR(16552, 19), 599}, // 697 RestrictPointerEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(15286, 9), 532}, // 698 RowMajor in SPV_OPERAND_TYPE_DECORATION
  {IR(16696, 14), 606}, // 699 SIMTCallINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15427, 7), 544}, // 700 Sample in SPV_OPERAND_TYPE_DECORATION
  {IR(15556, 20), 555}, // 701 SaturatedConversion in SPV_OPERAND_TYPE_DECORATION
  {IR(16003, 44), 575}, // 702 SaturatedToLargestFloat8NormalConversionEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(16407, 28), 593}, // 703 SecondaryViewportRelativeNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16749, 17), 609}, // 704 SideEffectsINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17176, 20), 628}, // 705 SimpleDualPortINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17665, 25), 650}, // 706 SingleElementVectorINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17125, 16), 625}, // 707 SinglepumpINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15261, 7), 529}, // 708 SpecId in SPV_OPERAND_TYPE_DECORATION
  {IR(18148, 26), 665}, // 709 StableKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16841, 15), 613}, // 710 StackCallINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17407, 17), 639}, // 711 StallEnableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17743, 15), 653}, // 712 StallFreeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15576, 7), 556}, // 713 Stream in SPV_OPERAND_TYPE_DECORATION
  {IR(17283, 16), 632}, // 714 StridesizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16207, 23), 584}, // 715 TrackFinishWritingAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17313, 18), 634}, // 716 TrueDualPortINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15512, 8), 553}, // 717 Uniform in SPV_OPERAND_TYPE_DECORATION
  {IR(15546, 10), 554}, // 718 UniformId in SPV_OPERAND_TYPE_DECORATION
  {IR(16920, 13), 616}, // 719 UserSemantic in SPV_OPERAND_TYPE_DECORATION
  {IR(16952, 15), 617}, // 720 UserTypeGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(17690, 35), 651}, // 721 VectorComputeCallableFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16814, 27), 612}, // 722 VectorComputeFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16766, 27), 610}, // 723 VectorComputeVariableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16388, 19), 592}, // 724 ViewportRelativeNV in SPV_OPERAND_TYPE_DECORATION
  {IR(15461, 9), 548}, // 725 Volatile in SPV_OPERAND_TYPE_DECORATION
  {IR(16075, 18), 578}, // 726 WeightTextureQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(17299, 14), 633}, // 727 WordsizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15637, 10), 563}, // 728 XfbBuffer in SPV_OPERAND_TYPE_DECORATION
  {IR(15647, 10), 564}, // 729 XfbStride in SPV_OPERAND_TYPE_DECORATION
  {IR(18453, 3), 672}, // 730 1D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18456, 3), 673}, // 731 2D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18459, 3), 674}, // 732 3D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18472, 7), 677}, // 733 Buffer in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18462, 5), 675}, // 734 Cube in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18467, 5), 676}, // 735 Rect in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18479, 12), 678}, // 736 SubpassData in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18491, 17), 679}, // 737 TileImageDataEXT in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(19303, 15), 732}, // 738 CoalescingAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18934, 15), 710}, // 739 ContractionOff in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(9608, 18), 724}, // 740 DenormFlushToZero in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(9593, 15), 723}, // 741 DenormPreserve in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18704, 13), 693}, // 742 DepthGreater in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18717, 10), 694}, // 743 DepthLess in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18689, 15), 692}, // 744 DepthReplacing in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18727, 15), 695}, // 745 DepthUnchanged in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19724, 25), 750}, // 746 DerivativeGroupLinearKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19749, 24), 750}, // 747 DerivativeGroupLinearNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19677, 24), 749}, // 748 DerivativeGroupQuadsKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19701, 23), 749}, // 749 DerivativeGroupQuadsNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19251, 29), 730}, // 750 EarlyAndLateFragmentTestsAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18656, 19), 689}, // 751 EarlyFragmentTests in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20234, 18), 769}, // 752 FPFastMathDefault in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18961, 10), 712}, // 753 Finalizer in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20049, 26), 761}, // 754 FloatingPointModeALTINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20075, 27), 762}, // 755 FloatingPointModeIEEEINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18949, 12), 711}, // 756 Initializer in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18778, 11), 699}, // 757 InputLines in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18789, 20), 700}, // 758 InputLinesAdjacency in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18766, 12), 698}, // 759 InputPoints in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18819, 24), 702}, // 760 InputTrianglesAdjacency in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18508, 12), 680}, // 761 Invocations in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19318, 15), 733}, // 762 IsApiEntryAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18849, 9), 704}, // 763 Isolines in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18742, 10), 696}, // 764 LocalSize in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18752, 14), 697}, // 765 LocalSizeHint in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19029, 16), 717}, // 766 LocalSizeHintId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19017, 12), 716}, // 767 LocalSizeId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19333, 21), 734}, // 768 MaxNodeRecursionAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19378, 21), 737}, // 769 MaxNumWorkgroupsAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20124, 16), 764}, // 770 MaxWorkDimINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20102, 22), 763}, // 771 MaxWorkgroupSizeINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20210, 24), 768}, // 772 MaximallyReconvergesKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20325, 22), 773}, // 773 MaximumRegistersINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20347, 24), 774}, // 774 MaximumRegistersIdINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20302, 23), 772}, // 775 NamedBarrierCountINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20422, 27), 775}, // 776 NamedMaximumRegistersINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20140, 20), 765}, // 777 NoGlobalOffsetINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19045, 34), 718}, // 778 NonCoherentColorAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19079, 34), 719}, // 779 NonCoherentDepthAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19113, 36), 720}, // 780 NonCoherentStencilAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19197, 34), 728}, // 781 NonCoherentTileAttachmentReadQCOM in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20160, 22), 766}, // 782 NumSIMDWorkitemsINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18640, 16), 688}, // 783 OriginLowerLeft in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18624, 16), 687}, // 784 OriginUpperLeft in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18886, 16), 707}, // 785 OutputLineStrip in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19609, 15), 747}, // 786 OutputLinesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19624, 14), 747}, // 787 OutputLinesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18873, 13), 706}, // 788 OutputPoints in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19638, 20), 748}, // 789 OutputPrimitivesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19658, 19), 748}, // 790 OutputPrimitivesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18902, 20), 708}, // 791 OutputTriangleStrip in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19773, 19), 751}, // 792 OutputTrianglesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19792, 18), 751}, // 793 OutputTrianglesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18858, 15), 705}, // 794 OutputVertices in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18605, 19), 686}, // 795 PixelCenterInteger in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19810, 25), 752}, // 796 PixelInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19835, 27), 753}, // 797 PixelInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18675, 10), 690}, // 798 PointMode in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19179, 18), 722}, // 799 PostDepthCoverage in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19550, 19), 744}, // 800 QuadDerivativesKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18843, 6), 703}, // 801 Quads in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20276, 26), 771}, // 802 RegisterMapInterfaceINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19569, 20), 745}, // 803 RequireFullQuadsKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(9651, 16), 726}, // 804 RoundingModeRTE in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20028, 21), 760}, // 805 RoundingModeRTNINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20007, 21), 759}, // 806 RoundingModeRTPINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(9667, 16), 727}, // 807 RoundingModeRTZ in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19862, 26), 754}, // 808 SampleInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19888, 28), 755}, // 809 SampleInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20182, 28), 767}, // 810 SchedulerTargetFmaxMhzINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(6287, 16), 736}, // 811 ShaderIndexAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19916, 31), 756}, // 812 ShadingRateInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19947, 33), 757}, // 813 ShadingRateInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19980, 27), 758}, // 814 SharedLocalMemorySizeINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19589, 20), 746}, // 815 SharesInputWithAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(9626, 25), 725}, // 816 SignedZeroInfNanPreserve in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18520, 13), 681}, // 817 SpacingEqual in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18533, 22), 682}, // 818 SpacingFractionalEven in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18555, 21), 683}, // 819 SpacingFractionalOdd in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19354, 24), 735}, // 820 StaticNumWorkgroupsAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19503, 25), 742}, // 821 StencilRefGreaterBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19427, 26), 739}, // 822 StencilRefGreaterFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19528, 22), 743}, // 823 StencilRefLessBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19453, 23), 740}, // 824 StencilRefLessFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19280, 23), 731}, // 825 StencilRefReplacingEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19476, 27), 741}, // 826 StencilRefUnchangedBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19399, 28), 738}, // 827 StencilRefUnchangedFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20252, 24), 770}, // 828 StreamingInterfaceINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(5394, 13), 713}, // 829 SubgroupSize in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19149, 30), 721}, // 830 SubgroupUniformControlFlowKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18971, 22), 714}, // 831 SubgroupsPerWorkgroup in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18993, 24), 715}, // 832 SubgroupsPerWorkgroupId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19231, 20), 729}, // 833 TileShadingRateQCOM in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18809, 10), 701}, // 834 Triangles in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18922, 12), 709}, // 835 VecTypeHint in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18590, 15), 685}, // 836 VertexOrderCcw in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18576, 14), 684}, // 837 VertexOrderCw in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18685, 4), 691}, // 838 Xfb in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20587, 10), 787}, // 839 AnyHitKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20597, 9), 787}, // 840 AnyHitNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20648, 12), 790}, // 841 CallableKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20660, 11), 790}, // 842 CallableNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20606, 14), 788}, // 843 ClosestHitKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20620, 13), 788}, // 844 ClosestHitNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(14627, 9), 780}, // 845 Fragment in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20499, 10), 781}, // 846 GLCompute in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(4875, 9), 779}, // 847 Geometry in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20556, 16), 786}, // 848 IntersectionKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20572, 15), 786}, // 849 IntersectionNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(4642, 7), 782}, // 850 Kernel in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20679, 8), 792}, // 851 MeshEXT in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20516, 7), 784}, // 852 MeshNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20633, 8), 789}, // 853 MissKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20641, 7), 789}, // 854 MissNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20523, 17), 785}, // 855 RayGenerationKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20540, 16), 785}, // 856 RayGenerationNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20671, 8), 791}, // 857 TaskEXT in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20509, 7), 783}, // 858 TaskNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20456, 20), 777}, // 859 TessellationControl in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20476, 23), 778}, // 860 TessellationEvaluation in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20449, 7), 776}, // 861 Vertex in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20696, 12), 794}, // 862 FlushToZero in SPV_OPERAND_TYPE_FPDENORM_MODE
  {IR(20687, 9), 793}, // 863 Preserve in SPV_OPERAND_TYPE_FPDENORM_MODE
  {IR(20708, 12), 795}, // 864 BFloat16KHR in SPV_OPERAND_TYPE_FPENCODING
  {IR(20720, 14), 796}, // 865 Float8E4M3EXT in SPV_OPERAND_TYPE_FPENCODING
  {IR(20734, 14), 797}, // 866 Float8E5M2EXT in SPV_OPERAND_TYPE_FPENCODING
  {IR(20753, 4), 799}, // 867 ALT in SPV_OPERAND_TYPE_FPOPERATION_MODE
  {IR(20748, 5), 798}, // 868 IEEE in SPV_OPERAND_TYPE_FPOPERATION_MODE
  {IR(20791, 14), 806}, // 869 AllowContract in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20805, 23), 806}, // 870 AllowContractFastINTEL in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20828, 13), 807}, // 871 AllowReassoc in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20841, 18), 807}, // 872 AllowReassocINTEL in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20775, 11), 804}, // 873 AllowRecip in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20859, 15), 808}, // 874 AllowTransform in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20786, 5), 805}, // 875 Fast in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20771, 4), 803}, // 876 NSZ in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(14223, 5), 800}, // 877 None in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20764, 7), 802}, // 878 NotInf in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20757, 7), 801}, // 879 NotNaN in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20874, 4), 809}, // 880 RTE in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(20886, 4), 812}, // 881 RTN in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(20882, 4), 811}, // 882 RTP in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(20878, 4), 810}, // 883 RTZ in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(20922, 18), 815}, // 884 Horizontal2Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(20940, 18), 816}, // 885 Horizontal4Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(20890, 16), 813}, // 886 Vertical2Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(20906, 16), 814}, // 887 Vertical4Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(20981, 6), 821}, // 888 Const in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(20965, 11), 819}, // 889 DontInline in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(20958, 7), 818}, // 890 Inline in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(14223, 5), 817}, // 891 None in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(13369, 11), 822}, // 892 OptNoneEXT in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(13380, 13), 822}, // 893 OptNoneINTEL in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(20976, 5), 820}, // 894 Pure in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(20997, 6), 825}, // 895 ByVal in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(21008, 8), 827}, // 896 NoAlias in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(21016, 10), 828}, // 897 NoCapture in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(21034, 12), 830}, // 898 NoReadWrite in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(21026, 8), 829}, // 899 NoWrite in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(21046, 20), 831}, // 900 RuntimeAlignedINTEL in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20992, 5), 824}, // 901 Sext in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(21003, 5), 826}, // 902 Sret in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20987, 5), 823}, // 903 Zext in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(21101, 16), 835}, // 904 ClusteredReduce in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(21087, 14), 834}, // 905 ExclusiveScan in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(21073, 14), 833}, // 906 InclusiveScan in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(21164, 27), 838}, // 907 PartitionedExclusiveScanNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(21137, 27), 837}, // 908 PartitionedInclusiveScanNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(21117, 20), 836}, // 909 PartitionedReduceNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(21066, 7), 832}, // 910 Reduce in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(21191, 10), 839}, // 911 NoneINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(21201, 10), 840}, // 912 ReadINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(21222, 15), 842}, // 913 ReadWriteINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(21211, 11), 841}, // 914 WriteINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(21237, 5), 844}, // 915 Bias in SPV_OPERAND_TYPE_IMAGE
  {IR(21251, 12), 847}, // 916 ConstOffset in SPV_OPERAND_TYPE_IMAGE
  {IR(21263, 13), 849}, // 917 ConstOffsets in SPV_OPERAND_TYPE_IMAGE
  {IR(21246, 5), 846}, // 918 Grad in SPV_OPERAND_TYPE_IMAGE
  {IR(21242, 4), 845}, // 919 Lod in SPV_OPERAND_TYPE_IMAGE
  {IR(21276, 19), 852}, // 920 MakeTexelAvailable in SPV_OPERAND_TYPE_IMAGE
  {IR(21295, 22), 852}, // 921 MakeTexelAvailableKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(21317, 17), 853}, // 922 MakeTexelVisible in SPV_OPERAND_TYPE_IMAGE
  {IR(21334, 20), 853}, // 923 MakeTexelVisibleKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(8426, 7), 851}, // 924 MinLod in SPV_OPERAND_TYPE_IMAGE
  {IR(21354, 16), 854}, // 925 NonPrivateTexel in SPV_OPERAND_TYPE_IMAGE
  {IR(21370, 19), 854}, // 926 NonPrivateTexelKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(14223, 5), 843}, // 927 None in SPV_OPERAND_TYPE_IMAGE
  {IR(21442, 12), 858}, // 928 Nontemporal in SPV_OPERAND_TYPE_IMAGE
  {IR(15630, 7), 848}, // 929 Offset in SPV_OPERAND_TYPE_IMAGE
  {IR(21454, 8), 859}, // 930 Offsets in SPV_OPERAND_TYPE_IMAGE
  {IR(15427, 7), 850}, // 931 Sample in SPV_OPERAND_TYPE_IMAGE
  {IR(21420, 11), 856}, // 932 SignExtend in SPV_OPERAND_TYPE_IMAGE
  {IR(21389, 14), 855}, // 933 VolatileTexel in SPV_OPERAND_TYPE_IMAGE
  {IR(21403, 17), 855}, // 934 VolatileTexelKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(21431, 11), 857}, // 935 ZeroExtend in SPV_OPERAND_TYPE_IMAGE
  {IR(14120, 6), 874}, // 936 Float in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21623, 10), 873}, // 937 HalfFloat in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21558, 12), 868}, // 938 SignedInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21570, 12), 869}, // 939 SignedInt32 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21547, 11), 867}, // 940 SignedInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21472, 11), 861}, // 941 SnormInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21462, 10), 860}, // 942 SnormInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21532, 15), 866}, // 943 UnormInt101010 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21644, 17), 876}, // 944 UnormInt101010_2 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21661, 16), 877}, // 945 UnormInt10X6EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21794, 16), 884}, // 946 UnormInt12X4EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21810, 16), 885}, // 947 UnormInt14X2EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21493, 11), 863}, // 948 UnormInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21633, 11), 875}, // 949 UnormInt24 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21717, 20), 880}, // 950 UnormInt2_101010EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21483, 10), 862}, // 951 UnormInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21518, 14), 865}, // 952 UnormShort555 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21504, 14), 864}, // 953 UnormShort565 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21737, 19), 881}, // 954 UnsignedInt10X6EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21756, 19), 882}, // 955 UnsignedInt12X4EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21775, 19), 883}, // 956 UnsignedInt14X2EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21595, 14), 871}, // 957 UnsignedInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21609, 14), 872}, // 958 UnsignedInt32 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21582, 13), 870}, // 959 UnsignedInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21677, 20), 878}, // 960 UnsignedIntRaw10EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21697, 20), 879}, // 961 UnsignedIntRaw12EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21828, 2), 887}, // 962 A in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21929, 5), 905}, // 963 ABGR in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21850, 5), 893}, // 964 ARGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21845, 5), 892}, // 965 BGRA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21887, 6), 899}, // 966 Depth in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21893, 13), 900}, // 967 DepthStencil in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21855, 10), 894}, // 968 Intensity in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21865, 10), 895}, // 969 Luminance in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21826, 2), 886}, // 970 R in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21833, 3), 889}, // 971 RA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21830, 3), 888}, // 972 RG in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21836, 4), 890}, // 973 RGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21840, 5), 891}, // 974 RGBA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21882, 5), 898}, // 975 RGBx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21878, 4), 897}, // 976 RGx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21875, 3), 896}, // 977 Rx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21923, 6), 904}, // 978 sBGRA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21906, 5), 901}, // 979 sRGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21917, 6), 903}, // 980 sRGBA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21911, 6), 902}, // 981 sRGBx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21934, 27), 906}, // 982 InitOnDeviceReprogramINTEL in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(21961, 23), 907}, // 983 InitOnDeviceResetINTEL in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(21984, 7), 908}, // 984 NoWait in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(21991, 11), 909}, // 985 WaitKernel in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(22002, 14), 910}, // 986 WaitWorkGroup in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(22016, 12), 912}, // 987 CmdExecTime in SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {IR(14223, 5), 911}, // 988 None in SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {IR(22028, 13), 914}, // 989 MayUsePrintf in SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {IR(14223, 5), 913}, // 990 None in SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {IR(22041, 7), 915}, // 991 Export in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(22048, 7), 916}, // 992 Import in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(22055, 12), 917}, // 993 LinkOnceODR in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(22081, 12), 919}, // 994 CachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(22133, 17), 922}, // 995 ConstCachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(22108, 25), 921}, // 996 InvalidateAfterReadINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(22093, 15), 920}, // 997 StreamingINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(22067, 14), 918}, // 998 UncachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(22273, 21), 935}, // 999 DependencyArrayINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22168, 19), 926}, // 1000 DependencyInfinite in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22187, 17), 927}, // 1001 DependencyLength in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22157, 11), 925}, // 1002 DontUnroll in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(17497, 24), 933}, // 1003 InitiationIntervalINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22232, 18), 930}, // 1004 IterationMultiple in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22294, 18), 937}, // 1005 LoopCoalesceINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22373, 15), 941}, // 1006 LoopCountINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(17521, 20), 934}, // 1007 MaxConcurrencyINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22312, 21), 938}, // 1008 MaxInterleavingINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22218, 14), 929}, // 1009 MaxIterations in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22388, 26), 942}, // 1010 MaxReinvocationDelayINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22204, 14), 928}, // 1011 MinIterations in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22359, 14), 940}, // 1012 NoFusionINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(14223, 5), 923}, // 1013 None in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22260, 13), 932}, // 1014 PartialCount in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22250, 10), 931}, // 1015 PeelCount in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(17541, 20), 936}, // 1016 PipelineEnableINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22333, 26), 939}, // 1017 SpeculatedIterationsINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22150, 7), 924}, // 1018 Unroll in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22697, 27), 956}, // 1019 MatrixAPackedBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22645, 26), 954}, // 1020 MatrixAPackedFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22565, 23), 950}, // 1021 MatrixAPackedInt4INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22519, 23), 948}, // 1022 MatrixAPackedInt8INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22414, 29), 944}, // 1023 MatrixASignedComponentsINTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22611, 17), 952}, // 1024 MatrixATF32INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22724, 27), 957}, // 1025 MatrixBPackedBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22671, 26), 955}, // 1026 MatrixBPackedFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22588, 23), 951}, // 1027 MatrixBPackedInt4INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22542, 23), 949}, // 1028 MatrixBPackedInt8INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22443, 29), 945}, // 1029 MatrixBSignedComponentsINTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22628, 17), 953}, // 1030 MatrixBTF32INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22472, 21), 946}, // 1031 MatrixCBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22493, 26), 947}, // 1032 MatrixResultBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(14223, 5), 943}, // 1033 None in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22884, 20), 965}, // 1034 AliasScopeINTELMask in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22751, 8), 960}, // 1035 Aligned in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22759, 21), 962}, // 1036 MakePointerAvailable in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22780, 24), 962}, // 1037 MakePointerAvailableKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22804, 19), 963}, // 1038 MakePointerVisible in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22823, 22), 963}, // 1039 MakePointerVisibleKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22904, 17), 966}, // 1040 NoAliasINTELMask in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22845, 18), 964}, // 1041 NonPrivatePointer in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22863, 21), 964}, // 1042 NonPrivatePointerKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(14223, 5), 958}, // 1043 None in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(21442, 12), 961}, // 1044 Nontemporal in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(15461, 9), 959}, // 1045 Volatile in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22928, 8), 968}, // 1046 GLSL450 in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(22936, 7), 969}, // 1047 OpenCL in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(22921, 7), 967}, // 1048 Simple in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(22943, 7), 970}, // 1049 Vulkan in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(22950, 10), 970}, // 1050 VulkanKHR in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(22968, 8), 972}, // 1051 Acquire in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22984, 15), 974}, // 1052 AcquireRelease in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(23088, 20), 980}, // 1053 AtomicCounterMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(23067, 21), 979}, // 1054 CrossWorkgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(23108, 12), 981}, // 1055 ImageMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(23149, 14), 983}, // 1056 MakeAvailable in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(23163, 17), 983}, // 1057 MakeAvailableKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(23180, 12), 984}, // 1058 MakeVisible in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(23192, 15), 984}, // 1059 MakeVisibleKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(14223, 5), 971}, // 1060 None in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(23120, 13), 982}, // 1061 OutputMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(23133, 16), 982}, // 1062 OutputMemoryKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22960, 8), 971}, // 1063 Relaxed in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22976, 8), 973}, // 1064 Release in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22999, 23), 975}, // 1065 SequentiallyConsistent in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(23036, 15), 977}, // 1066 SubgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(23022, 14), 976}, // 1067 UniformMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(15461, 9), 985}, // 1068 Volatile in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(23051, 16), 978}, // 1069 WorkgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(23207, 10), 986}, // 1070 AutoINTEL in SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS
  {IR(23222, 4), 988}, // 1071 SAT in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(23235, 8), 990}, // 1072 SAT_SYM in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(23226, 9), 989}, // 1073 SAT_ZERO in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(23217, 5), 987}, // 1074 WRAP in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(23243, 25), 991}, // 1075 PackedVectorFormat4x8Bit in SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {IR(23268, 28), 991}, // 1076 PackedVectorFormat4x8BitKHR in SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {IR(23309, 4), 994}, // 1077 RND in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(23342, 9), 998}, // 1078 RND_CONV in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(23351, 13), 999}, // 1079 RND_CONV_ODD in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(23322, 8), 996}, // 1080 RND_INF in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(23330, 12), 997}, // 1081 RND_MIN_INF in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(23313, 9), 995}, // 1082 RND_ZERO in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(23296, 4), 992}, // 1083 TRN in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(23300, 9), 993}, // 1084 TRN_ZERO in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(14223, 5), 1000}, // 1085 None in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(23364, 25), 1001}, // 1086 RobustnessPerComponentNV in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(23389, 23), 1002}, // 1087 RobustnessPerElementNV in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(23481, 27), 1008}, // 1088 CullBackFacingTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23508, 28), 1009}, // 1089 CullFrontFacingTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23550, 16), 1011}, // 1090 CullNoOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23536, 14), 1010}, // 1091 CullOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23620, 30), 1014}, // 1092 ForceOpacityMicromap2StateEXT in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23422, 12), 1005}, // 1093 NoOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(14975, 8), 1003}, // 1094 NoneKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23412, 10), 1004}, // 1095 OpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23607, 13), 1013}, // 1096 SkipAABBsKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23583, 24), 1012}, // 1097 SkipBuiltinPrimitivesNV in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23457, 24), 1007}, // 1098 SkipClosestHitShaderKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23566, 17), 1012}, // 1099 SkipTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23434, 23), 1006}, // 1100 TerminateOnFirstHitKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23691, 37), 1016}, // 1101 RayQueryCandidateIntersectionAABBKHR in SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {IR(23650, 41), 1015}, // 1102 RayQueryCandidateIntersectionTriangleKHR in SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {IR(23806, 42), 1019}, // 1103 RayQueryCommittedIntersectionGeneratedKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(23728, 37), 1017}, // 1104 RayQueryCommittedIntersectionNoneKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(23765, 41), 1018}, // 1105 RayQueryCommittedIntersectionTriangleKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(23848, 33), 1020}, // 1106 RayQueryCandidateIntersectionKHR in SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {IR(23881, 33), 1021}, // 1107 RayQueryCommittedIntersectionKHR in SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {IR(23926, 6), 1024}, // 1108 Clamp in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(23914, 12), 1023}, // 1109 ClampToEdge in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(14223, 5), 1022}, // 1110 None in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(23932, 7), 1025}, // 1111 Repeat in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(23939, 15), 1026}, // 1112 RepeatMirrored in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(23962, 7), 1028}, // 1113 Linear in SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {IR(23954, 8), 1027}, // 1114 Nearest in SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {IR(24027, 13), 1037}, // 1115 R11fG11fB10f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24069, 4), 1043}, // 1116 R16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24107, 9), 1048}, // 1117 R16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24040, 5), 1038}, // 1118 R16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24169, 5), 1057}, // 1119 R16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24240, 6), 1067}, // 1120 R16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23993, 5), 1032}, // 1121 R32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24147, 5), 1053}, // 1122 R32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24204, 6), 1062}, // 1123 R32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24257, 5), 1070}, // 1124 R64i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24251, 6), 1069}, // 1125 R64ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24073, 3), 1044}, // 1126 R8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24116, 8), 1049}, // 1127 R8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24174, 4), 1058}, // 1128 R8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24246, 5), 1068}, // 1129 R8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24060, 5), 1041}, // 1130 Rg16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24088, 10), 1046}, // 1131 Rg16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24021, 6), 1036}, // 1132 Rg16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24158, 6), 1055}, // 1133 Rg16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24227, 7), 1065}, // 1134 Rg16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24015, 6), 1035}, // 1135 Rg32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24152, 6), 1054}, // 1136 Rg32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24220, 7), 1064}, // 1137 Rg32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24065, 4), 1042}, // 1138 Rg8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24098, 9), 1047}, // 1139 Rg8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24164, 5), 1056}, // 1140 Rg8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24234, 6), 1066}, // 1141 Rg8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24052, 8), 1040}, // 1142 Rgb10A2 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24210, 10), 1063}, // 1143 Rgb10a2ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24045, 7), 1039}, // 1144 Rgba16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24076, 12), 1045}, // 1145 Rgba16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23985, 8), 1031}, // 1146 Rgba16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24132, 8), 1051}, // 1147 Rgba16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24187, 9), 1060}, // 1148 Rgba16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23977, 8), 1030}, // 1149 Rgba32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24124, 8), 1050}, // 1150 Rgba32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24178, 9), 1059}, // 1151 Rgba32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23998, 6), 1033}, // 1152 Rgba8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24004, 11), 1034}, // 1153 Rgba8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24140, 7), 1052}, // 1154 Rgba8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24196, 8), 1061}, // 1155 Rgba8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23969, 8), 1029}, // 1156 Unknown in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(24262, 12), 1071}, // 1157 CrossDevice in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(24274, 7), 1072}, // 1158 Device in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(24300, 11), 1075}, // 1159 Invocation in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(24311, 12), 1076}, // 1160 QueueFamily in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(24323, 15), 1076}, // 1161 QueueFamilyKHR in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(24338, 14), 1077}, // 1162 ShaderCallKHR in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(24291, 9), 1074}, // 1163 Subgroup in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(24281, 10), 1073}, // 1164 Workgroup in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(24360, 12), 1080}, // 1165 DontFlatten in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(24352, 8), 1079}, // 1166 Flatten in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(14223, 5), 1078}, // 1167 None in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(24372, 29), 1081}, // 1168 IdentifierPossibleDuplicates in SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS
  {IR(14104, 8), 1083}, // 1169 Address in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14112, 8), 1084}, // 1170 Boolean in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14120, 6), 1085}, // 1171 Float in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14126, 7), 1086}, // 1172 Signed in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14133, 11), 1087}, // 1173 SignedChar in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14144, 9), 1088}, // 1174 Unsigned in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14153, 13), 1089}, // 1175 UnsignedChar in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14092, 12), 1082}, // 1176 Unspecified in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(14166, 6), 1090}, // 1177 Class in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(14172, 10), 1091}, // 1178 Structure in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(14182, 6), 1092}, // 1179 Union in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(14203, 20), 1094}, // 1180 ImportedDeclaration in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(14188, 15), 1093}, // 1181 ImportedModule in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(14312, 15), 1102}, // 1182 FlagArtificial in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14327, 13), 1103}, // 1183 FlagExplicit in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14300, 12), 1101}, // 1184 FlagFwdDecl in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14390, 21), 1107}, // 1185 FlagIndirectVariable in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14283, 17), 1100}, // 1186 FlagIsDefinition in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14467, 16), 1111}, // 1187 FlagIsEnumClass in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14271, 12), 1099}, // 1188 FlagIsLocal in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14451, 16), 1110}, // 1189 FlagIsOptimized in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14244, 14), 1097}, // 1190 FlagIsPrivate in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14228, 16), 1096}, // 1191 FlagIsProtected in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14258, 13), 1098}, // 1192 FlagIsPublic in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14411, 20), 1108}, // 1193 FlagLValueReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14355, 18), 1105}, // 1194 FlagObjectPointer in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14340, 15), 1104}, // 1195 FlagPrototyped in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14431, 20), 1109}, // 1196 FlagRValueReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14373, 17), 1106}, // 1197 FlagStaticMember in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14503, 24), 1113}, // 1198 FlagTypePassByReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14483, 20), 1112}, // 1199 FlagTypePassByValue in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(24401, 26), 1114}, // 1200 FlagUnknownPhysicalLayout in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14223, 5), 1095}, // 1201 None in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14588, 9), 1119}, // 1202 BitPiece in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14620, 7), 1123}, // 1203 Constu in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14527, 6), 1115}, // 1204 Deref in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14627, 9), 1124}, // 1205 Fragment in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14538, 6), 1117}, // 1206 Minus in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14533, 5), 1116}, // 1207 Plus in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14577, 11), 1118}, // 1208 PlusUconst in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14609, 11), 1122}, // 1209 StackValue in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14597, 5), 1120}, // 1210 Swap in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14602, 7), 1121}, // 1211 Xderef in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14672, 11), 1128}, // 1212 AtomicType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14636, 10), 1125}, // 1213 ConstType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14659, 13), 1127}, // 1214 RestrictType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14646, 13), 1126}, // 1215 VolatileType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(24462, 15), 1135}, // 1216 CPP_for_OpenCL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24427, 5), 1130}, // 1217 ESSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24432, 5), 1131}, // 1218 GLSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24482, 7), 1137}, // 1219 HERO_C in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24457, 5), 1134}, // 1220 HLSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24489, 5), 1138}, // 1221 NZSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24437, 9), 1132}, // 1222 OpenCL_C in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24446, 11), 1133}, // 1223 OpenCL_CPP in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24509, 5), 1142}, // 1224 Rust in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24477, 5), 1136}, // 1225 SYCL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24499, 6), 1140}, // 1226 Slang in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(23969, 8), 1129}, // 1227 Unknown in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24494, 5), 1139}, // 1228 WGSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24505, 4), 1141}, // 1229 Zig in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24596, 14), 1153}, // 1230 AtomicCounter in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24678, 16), 1159}, // 1231 CallableDataKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24694, 15), 1159}, // 1232 CallableDataNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24992, 17), 1168}, // 1233 CodeSectionINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24543, 15), 1148}, // 1234 CrossWorkgroup in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(25009, 16), 1169}, // 1235 DeviceOnlyINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24566, 9), 1150}, // 1236 Function in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24575, 8), 1151}, // 1237 Generic in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24783, 16), 1162}, // 1238 HitAttributeKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24799, 15), 1162}, // 1239 HitAttributeNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24947, 21), 1166}, // 1240 HitObjectAttributeNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(25025, 14), 1170}, // 1241 HostOnlyINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24610, 6), 1154}, // 1242 Image in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24709, 24), 1160}, // 1243 IncomingCallableDataKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24733, 23), 1160}, // 1244 IncomingCallableDataNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24814, 22), 1163}, // 1245 IncomingRayPayloadKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24836, 21), 1163}, // 1246 IncomingRayPayloadNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24530, 6), 1144}, // 1247 Input in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24662, 16), 1158}, // 1248 NodePayloadAMDX in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24536, 7), 1146}, // 1249 Output in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24900, 22), 1165}, // 1250 PhysicalStorageBuffer in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24922, 25), 1165}, // 1251 PhysicalStorageBufferEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24558, 8), 1149}, // 1252 Private in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24583, 13), 1152}, // 1253 PushConstant in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24756, 14), 1161}, // 1254 RayPayloadKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24770, 13), 1161}, // 1255 RayPayloadNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24857, 22), 1164}, // 1256 ShaderRecordBufferKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24879, 21), 1164}, // 1257 ShaderRecordBufferNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24616, 14), 1155}, // 1258 StorageBuffer in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24968, 24), 1167}, // 1259 TaskPayloadWorkgroupEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24643, 19), 1157}, // 1260 TileAttachmentQCOM in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24630, 13), 1156}, // 1261 TileImageEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(15512, 8), 1145}, // 1262 Uniform in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24514, 16), 1143}, // 1263 UniformConstant in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24281, 10), 1147}, // 1264 Workgroup in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(22093, 15), 1174}, // 1265 StreamingINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(22067, 14), 1171}, // 1266 UncachedINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(25057, 15), 1173}, // 1267 WriteBackINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(25039, 18), 1172}, // 1268 WriteThroughINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(25083, 11), 1177}, // 1269 DecodeFunc in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(14223, 5), 1175}, // 1270 None in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(25072, 11), 1176}, // 1271 TensorView in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(23914, 12), 1180}, // 1272 ClampToEdge in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(15470, 9), 1179}, // 1273 Constant in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(23932, 7), 1181}, // 1274 Repeat in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(23939, 15), 1182}, // 1275 RepeatMirrored in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(25094, 10), 1178}, // 1276 Undefined in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(25147, 24), 1186}, // 1277 MakeElementAvailableARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(25171, 22), 1187}, // 1278 MakeElementVisibleARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(25193, 21), 1188}, // 1279 NonPrivateElementARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(25104, 8), 1183}, // 1280 NoneARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(25112, 15), 1184}, // 1281 NontemporalARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(25127, 20), 1185}, // 1282 OutOfBoundsValueARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
}};

IndexRange OperandNameRangeForKind(spv_operand_type_t type) {
  switch(type) {
    case SPV_OPERAND_TYPE_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_ADDRESSING_MODEL: return IR(3, 5);
    case SPV_OPERAND_TYPE_BUILT_IN: return IR(8, 148);
    case SPV_OPERAND_TYPE_CAPABILITY: return IR(156, 303);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(459, 8);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(467, 3);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(470, 2);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS: return IR(472, 19);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION: return IR(491, 10);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(501, 4);
    case SPV_OPERAND_TYPE_COMPONENT_TYPE: return IR(505, 15);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT: return IR(520, 4);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS: return IR(524, 6);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE: return IR(530, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE: return IR(533, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT: return IR(536, 4);
    case SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(540, 8);
    case SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE: return IR(548, 3);
    case SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS: return IR(551, 16);
    case SPV_OPERAND_TYPE_DEBUG_OPERATION: return IR(567, 9);
    case SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER: return IR(576, 3);
    case SPV_OPERAND_TYPE_DECORATION: return IR(579, 151);
    case SPV_OPERAND_TYPE_DIMENSIONALITY: return IR(730, 8);
    case SPV_OPERAND_TYPE_EXECUTION_MODE: return IR(738, 101);
    case SPV_OPERAND_TYPE_EXECUTION_MODEL: return IR(839, 23);
    case SPV_OPERAND_TYPE_FPDENORM_MODE: return IR(862, 2);
    case SPV_OPERAND_TYPE_FPENCODING: return IR(864, 3);
    case SPV_OPERAND_TYPE_FPOPERATION_MODE: return IR(867, 2);
    case SPV_OPERAND_TYPE_FP_FAST_MATH_MODE: return IR(869, 11);
    case SPV_OPERAND_TYPE_FP_ROUNDING_MODE: return IR(880, 4);
    case SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE: return IR(884, 4);
    case SPV_OPERAND_TYPE_FUNCTION_CONTROL: return IR(888, 7);
    case SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE: return IR(895, 9);
    case SPV_OPERAND_TYPE_GROUP_OPERATION: return IR(904, 7);
    case SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER: return IR(911, 4);
    case SPV_OPERAND_TYPE_IMAGE: return IR(915, 21);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE: return IR(936, 26);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER: return IR(962, 20);
    case SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER: return IR(982, 2);
    case SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS: return IR(984, 3);
    case SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO: return IR(987, 2);
    case SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS: return IR(989, 2);
    case SPV_OPERAND_TYPE_LINKAGE_TYPE: return IR(991, 3);
    case SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL: return IR(994, 5);
    case SPV_OPERAND_TYPE_LOOP_CONTROL: return IR(999, 20);
    case SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(1019, 15);
    case SPV_OPERAND_TYPE_MEMORY_ACCESS: return IR(1034, 12);
    case SPV_OPERAND_TYPE_MEMORY_MODEL: return IR(1046, 5);
    case SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID: return IR(1051, 19);
    case SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS: return IR(1070, 1);
    case SPV_OPERAND_TYPE_OVERFLOW_MODES: return IR(1071, 4);
    case SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT: return IR(1075, 2);
    case SPV_OPERAND_TYPE_QUANTIZATION_MODES: return IR(1077, 8);
    case SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS: return IR(1085, 3);
    case SPV_OPERAND_TYPE_RAY_FLAGS: return IR(1088, 13);
    case SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE: return IR(1101, 2);
    case SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE: return IR(1103, 3);
    case SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION: return IR(1106, 2);
    case SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE: return IR(1108, 5);
    case SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE: return IR(1113, 2);
    case SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT: return IR(1115, 42);
    case SPV_OPERAND_TYPE_SCOPE_ID: return IR(1157, 8);
    case SPV_OPERAND_TYPE_SELECTION_CONTROL: return IR(1165, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS: return IR(1168, 1);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(1169, 8);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(1177, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(1180, 2);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS: return IR(1182, 20);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION: return IR(1202, 10);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(1212, 4);
    case SPV_OPERAND_TYPE_SOURCE_LANGUAGE: return IR(1216, 14);
    case SPV_OPERAND_TYPE_STORAGE_CLASS: return IR(1230, 35);
    case SPV_OPERAND_TYPE_STORE_CACHE_CONTROL: return IR(1265, 4);
    case SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS: return IR(1269, 3);
    case SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE: return IR(1272, 5);
    case SPV_OPERAND_TYPE_TENSOR_OPERANDS: return IR(1277, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_IMAGE: return IR(915, 21);
    case SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS: return IR(1034, 12);
    case SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT: return IR(1075, 2);
    case SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS: return IR(524, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(1019, 15);
    case SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS: return IR(1085, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_FPENCODING: return IR(864, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS: return IR(1277, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_CAPABILITY: return IR(156, 303);
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
static const std::array<InstructionDesc, 822> kInstructionDesc{{
  {spv::Op::OpNop, false, false, IR(0, 0), IR(25214, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpUndef, true, true, IR(39, 2), IR(25270, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpSourceContinued, false, false, IR(11, 1), IR(25276, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpSource, false, false, IR(41, 4), IR(25395, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpSourceExtension, false, false, IR(11, 1), IR(25402, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpName, false, false, IR(45, 2), IR(25418, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpMemberName, false, false, IR(47, 3), IR(25423, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpString, true, false, IR(50, 2), IR(25434, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpLine, false, false, IR(52, 3), IR(25441, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpExtension, false, false, IR(11, 1), IR(25446, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpExtInstImport, true, false, IR(50, 2), IR(25456, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpExtInst, true, true, IR(55, 4), IR(25516, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpMemoryModel, false, false, IR(59, 2), IR(25588, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpEntryPoint, false, false, IR(61, 4), IR(25662, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpExecutionMode, false, false, IR(65, 2), IR(25705, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpCapability, false, false, IR(67, 1), IR(25747, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpTypeVoid, true, false, IR(68, 1), IR(25758, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeBool, true, false, IR(68, 1), IR(25767, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeInt, true, false, IR(69, 3), IR(25776, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeFloat, true, false, IR(72, 3), IR(25821, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeVector, true, false, IR(75, 3), IR(25831, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeMatrix, true, false, IR(75, 3), IR(25842, 11), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeImage, true, false, IR(78, 9), IR(25966, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeSampler, true, false, IR(68, 1), IR(25976, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeSampledImage, true, false, IR(87, 2), IR(25988, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeArray, true, false, IR(89, 3), IR(26005, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeRuntimeArray, true, false, IR(87, 2), IR(26015, 17), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeStruct, true, false, IR(92, 2), IR(26032, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeOpaque, true, false, IR(50, 2), IR(26043, 11), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypePointer, true, false, IR(94, 3), IR(26085, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeFunction, true, false, IR(97, 3), IR(26097, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeEvent, true, false, IR(68, 1), IR(26110, 10), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeDeviceEvent, true, false, IR(68, 1), IR(26120, 16), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeReserveId, true, false, IR(68, 1), IR(26136, 14), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeQueue, true, false, IR(68, 1), IR(26150, 10), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypePipe, true, false, IR(100, 2), IR(26160, 9), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeForwardPointer, false, false, IR(102, 2), IR(26169, 19), IR(0, 0), IR(203, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantTrue, true, true, IR(39, 2), IR(26188, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantFalse, true, true, IR(39, 2), IR(26201, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstant, true, true, IR(104, 3), IR(15470, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantComposite, true, true, IR(107, 3), IR(26253, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantSampler, true, true, IR(110, 5), IR(26349, 16), IR(0, 0), IR(205, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantNull, true, true, IR(39, 2), IR(26365, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantTrue, true, true, IR(39, 2), IR(26378, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantFalse, true, true, IR(39, 2), IR(26395, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstant, true, true, IR(104, 3), IR(26413, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantComposite, true, true, IR(107, 3), IR(26426, 22), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantOp, true, true, IR(115, 3), IR(26489, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpFunction, true, true, IR(118, 4), IR(24566, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionParameter, true, true, IR(39, 2), IR(26538, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionEnd, false, false, IR(0, 0), IR(26556, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionCall, true, true, IR(122, 4), IR(26568, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpVariable, true, true, IR(126, 4), IR(26581, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpImageTexelPointer, true, true, IR(130, 5), IR(26590, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpLoad, true, true, IR(135, 4), IR(26648, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpStore, false, false, IR(139, 3), IR(26653, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCopyMemory, false, false, IR(142, 4), IR(26659, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCopyMemorySized, false, false, IR(146, 5), IR(26670, 16), IR(0, 0), IR(206, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpAccessChain, true, true, IR(122, 4), IR(26686, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpInBoundsAccessChain, true, true, IR(122, 4), IR(26698, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrAccessChain, true, true, IR(151, 5), IR(26718, 15), IR(0, 0), IR(208, 4), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpArrayLength, true, true, IR(156, 4), IR(26733, 12), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpGenericPtrMemSemantics, true, true, IR(160, 3), IR(26745, 23), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpInBoundsPtrAccessChain, true, true, IR(151, 5), IR(26768, 23), IR(0, 0), IR(1, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpDecorate, false, false, IR(163, 2), IR(26819, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpMemberDecorate, false, false, IR(165, 3), IR(26828, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpDecorationGroup, true, false, IR(68, 1), IR(26843, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupDecorate, false, false, IR(168, 2), IR(26859, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupMemberDecorate, false, false, IR(170, 2), IR(26918, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpVectorExtractDynamic, true, true, IR(172, 4), IR(26938, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpVectorInsertDynamic, true, true, IR(130, 5), IR(26959, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpVectorShuffle, true, true, IR(176, 5), IR(26979, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeConstruct, true, true, IR(107, 3), IR(26993, 19), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeExtract, true, true, IR(181, 4), IR(27012, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeInsert, true, true, IR(176, 5), IR(27029, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCopyObject, true, true, IR(160, 3), IR(27045, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpTranspose, true, true, IR(160, 3), IR(27056, 10), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpSampledImage, true, true, IR(172, 4), IR(27066, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleImplicitLod, true, true, IR(185, 5), IR(27111, 23), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleExplicitLod, true, true, IR(190, 5), IR(27157, 23), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleDrefImplicitLod, true, true, IR(195, 6), IR(27180, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleDrefExplicitLod, true, true, IR(201, 6), IR(27207, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjImplicitLod, true, true, IR(185, 5), IR(27234, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjExplicitLod, true, true, IR(190, 5), IR(27261, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjDrefImplicitLod, true, true, IR(195, 6), IR(27288, 31), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjDrefExplicitLod, true, true, IR(201, 6), IR(27319, 31), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageFetch, true, true, IR(185, 5), IR(27350, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageGather, true, true, IR(195, 6), IR(27361, 12), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageDrefGather, true, true, IR(195, 6), IR(27373, 16), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageRead, true, true, IR(185, 5), IR(27389, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageWrite, false, false, IR(207, 4), IR(27399, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImage, true, true, IR(160, 3), IR(24610, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryFormat, true, true, IR(160, 3), IR(27410, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryOrder, true, true, IR(160, 3), IR(27427, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySizeLod, true, true, IR(172, 4), IR(27443, 18), IR(0, 0), IR(212, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySize, true, true, IR(160, 3), IR(27461, 15), IR(0, 0), IR(212, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryLod, true, true, IR(172, 4), IR(27476, 14), IR(0, 0), IR(214, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryLevels, true, true, IR(160, 3), IR(27490, 17), IR(0, 0), IR(212, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySamples, true, true, IR(160, 3), IR(27507, 18), IR(0, 0), IR(212, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertFToU, true, true, IR(160, 3), IR(27525, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertFToS, true, true, IR(160, 3), IR(27537, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertSToF, true, true, IR(160, 3), IR(27549, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToF, true, true, IR(160, 3), IR(27561, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpUConvert, true, true, IR(160, 3), IR(27573, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSConvert, true, true, IR(160, 3), IR(27582, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpFConvert, true, true, IR(160, 3), IR(27591, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpQuantizeToF16, true, true, IR(160, 3), IR(27600, 14), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertPtrToU, true, true, IR(160, 3), IR(27614, 14), IR(0, 0), IR(203, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSatConvertSToU, true, true, IR(160, 3), IR(27628, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSatConvertUToS, true, true, IR(160, 3), IR(27643, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToPtr, true, true, IR(160, 3), IR(27658, 14), IR(0, 0), IR(203, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpPtrCastToGeneric, true, true, IR(160, 3), IR(27672, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpGenericCastToPtr, true, true, IR(160, 3), IR(27689, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpGenericCastToPtrExplicit, true, true, IR(211, 4), IR(27706, 25), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpBitcast, true, true, IR(160, 3), IR(27731, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSNegate, true, true, IR(160, 3), IR(27739, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFNegate, true, true, IR(160, 3), IR(27747, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIAdd, true, true, IR(172, 4), IR(27755, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFAdd, true, true, IR(172, 4), IR(27760, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpISub, true, true, IR(172, 4), IR(27765, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFSub, true, true, IR(172, 4), IR(27770, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIMul, true, true, IR(172, 4), IR(27775, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFMul, true, true, IR(172, 4), IR(27780, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDiv, true, true, IR(172, 4), IR(27785, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSDiv, true, true, IR(172, 4), IR(27790, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFDiv, true, true, IR(172, 4), IR(27795, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUMod, true, true, IR(172, 4), IR(27800, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSRem, true, true, IR(172, 4), IR(27805, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSMod, true, true, IR(172, 4), IR(27810, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFRem, true, true, IR(172, 4), IR(27815, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFMod, true, true, IR(172, 4), IR(27820, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpVectorTimesScalar, true, true, IR(172, 4), IR(27825, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesScalar, true, true, IR(172, 4), IR(27843, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpVectorTimesMatrix, true, true, IR(172, 4), IR(27861, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesVector, true, true, IR(172, 4), IR(27879, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesMatrix, true, true, IR(172, 4), IR(27897, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpOuterProduct, true, true, IR(172, 4), IR(27915, 13), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpDot, true, true, IR(172, 4), IR(27928, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIAddCarry, true, true, IR(172, 4), IR(27932, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpISubBorrow, true, true, IR(172, 4), IR(27942, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUMulExtended, true, true, IR(172, 4), IR(27953, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSMulExtended, true, true, IR(172, 4), IR(27966, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpAny, true, true, IR(160, 3), IR(27979, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpAll, true, true, IR(160, 3), IR(27983, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsNan, true, true, IR(160, 3), IR(27987, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsInf, true, true, IR(160, 3), IR(27993, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsFinite, true, true, IR(160, 3), IR(27999, 9), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsNormal, true, true, IR(160, 3), IR(28008, 9), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSignBitSet, true, true, IR(160, 3), IR(28017, 11), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLessOrGreater, true, true, IR(172, 4), IR(28028, 14), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), SPV_SPIRV_VERSION_WORD(1,5), PrintingClass::kRelational_and_Logical},
  {spv::Op::OpOrdered, true, true, IR(172, 4), IR(28042, 8), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUnordered, true, true, IR(172, 4), IR(28050, 10), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalEqual, true, true, IR(172, 4), IR(28060, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalNotEqual, true, true, IR(172, 4), IR(28073, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalOr, true, true, IR(172, 4), IR(28089, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalAnd, true, true, IR(172, 4), IR(28099, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalNot, true, true, IR(160, 3), IR(28110, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSelect, true, true, IR(130, 5), IR(28121, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIEqual, true, true, IR(172, 4), IR(28128, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpINotEqual, true, true, IR(172, 4), IR(28135, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUGreaterThan, true, true, IR(172, 4), IR(28145, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSGreaterThan, true, true, IR(172, 4), IR(28158, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUGreaterThanEqual, true, true, IR(172, 4), IR(28171, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSGreaterThanEqual, true, true, IR(172, 4), IR(28189, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpULessThan, true, true, IR(172, 4), IR(28207, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSLessThan, true, true, IR(172, 4), IR(28217, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpULessThanEqual, true, true, IR(172, 4), IR(28227, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSLessThanEqual, true, true, IR(172, 4), IR(28242, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdEqual, true, true, IR(172, 4), IR(28257, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordEqual, true, true, IR(172, 4), IR(28267, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdNotEqual, true, true, IR(172, 4), IR(28279, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordNotEqual, true, true, IR(172, 4), IR(28292, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdLessThan, true, true, IR(172, 4), IR(28307, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordLessThan, true, true, IR(172, 4), IR(28320, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdGreaterThan, true, true, IR(172, 4), IR(28335, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordGreaterThan, true, true, IR(172, 4), IR(28351, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdLessThanEqual, true, true, IR(172, 4), IR(28369, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordLessThanEqual, true, true, IR(172, 4), IR(28387, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdGreaterThanEqual, true, true, IR(172, 4), IR(28407, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordGreaterThanEqual, true, true, IR(172, 4), IR(28428, 23), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpShiftRightLogical, true, true, IR(172, 4), IR(28451, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpShiftRightArithmetic, true, true, IR(172, 4), IR(28469, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpShiftLeftLogical, true, true, IR(172, 4), IR(28490, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseOr, true, true, IR(172, 4), IR(28507, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseXor, true, true, IR(172, 4), IR(28517, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseAnd, true, true, IR(172, 4), IR(28528, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpNot, true, true, IR(160, 3), IR(28539, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldInsert, true, true, IR(215, 6), IR(28543, 15), IR(0, 0), IR(215, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldSExtract, true, true, IR(130, 5), IR(28558, 17), IR(0, 0), IR(215, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldUExtract, true, true, IR(130, 5), IR(28575, 17), IR(0, 0), IR(215, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitReverse, true, true, IR(160, 3), IR(28592, 11), IR(0, 0), IR(215, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitCount, true, true, IR(160, 3), IR(28603, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpDPdx, true, true, IR(160, 3), IR(28612, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdy, true, true, IR(160, 3), IR(28617, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidth, true, true, IR(160, 3), IR(28622, 7), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdxFine, true, true, IR(160, 3), IR(28629, 9), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdyFine, true, true, IR(160, 3), IR(28638, 9), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidthFine, true, true, IR(160, 3), IR(28647, 11), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdxCoarse, true, true, IR(160, 3), IR(28658, 11), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdyCoarse, true, true, IR(160, 3), IR(28669, 11), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidthCoarse, true, true, IR(160, 3), IR(28680, 13), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpEmitVertex, false, false, IR(0, 0), IR(28693, 11), IR(0, 0), IR(69, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEndPrimitive, false, false, IR(0, 0), IR(28704, 13), IR(0, 0), IR(69, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEmitStreamVertex, false, false, IR(10, 1), IR(28717, 17), IR(0, 0), IR(116, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEndStreamPrimitive, false, false, IR(10, 1), IR(28734, 19), IR(0, 0), IR(116, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpControlBarrier, false, false, IR(221, 3), IR(28790, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpMemoryBarrier, false, false, IR(224, 2), IR(28805, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpAtomicLoad, true, true, IR(226, 5), IR(28819, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicStore, false, false, IR(231, 4), IR(28830, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicExchange, true, true, IR(235, 6), IR(28842, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicCompareExchange, true, true, IR(241, 8), IR(28857, 22), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicCompareExchangeWeak, true, true, IR(241, 8), IR(28879, 26), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), SPV_SPIRV_VERSION_WORD(1,3), PrintingClass::kAtomic},
  {spv::Op::OpAtomicIIncrement, true, true, IR(226, 5), IR(28905, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicIDecrement, true, true, IR(226, 5), IR(28922, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicIAdd, true, true, IR(235, 6), IR(28939, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicISub, true, true, IR(235, 6), IR(28950, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicSMin, true, true, IR(235, 6), IR(28961, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicUMin, true, true, IR(235, 6), IR(28972, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicSMax, true, true, IR(235, 6), IR(28983, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicUMax, true, true, IR(235, 6), IR(28994, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicAnd, true, true, IR(235, 6), IR(29005, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicOr, true, true, IR(235, 6), IR(29015, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicXor, true, true, IR(235, 6), IR(29024, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpPhi, true, true, IR(107, 3), IR(29034, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLoopMerge, false, false, IR(249, 3), IR(29068, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpSelectionMerge, false, false, IR(252, 2), IR(29113, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLabel, true, false, IR(68, 1), IR(29128, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpBranch, false, false, IR(10, 1), IR(29134, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpBranchConditional, false, false, IR(254, 4), IR(29141, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpSwitch, false, false, IR(258, 3), IR(29204, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpKill, false, false, IR(0, 0), IR(29211, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpReturn, false, false, IR(0, 0), IR(29216, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpReturnValue, false, false, IR(10, 1), IR(29223, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpUnreachable, false, false, IR(0, 0), IR(29235, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLifetimeStart, false, false, IR(261, 2), IR(29247, 14), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLifetimeStop, false, false, IR(261, 2), IR(29261, 13), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpGroupAsyncCopy, true, true, IR(263, 8), IR(29274, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupWaitEvents, false, false, IR(271, 3), IR(29289, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupAll, true, true, IR(274, 4), IR(29305, 9), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupAny, true, true, IR(274, 4), IR(29314, 9), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBroadcast, true, true, IR(278, 5), IR(29323, 15), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupIAdd, true, true, IR(283, 5), IR(29371, 10), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFAdd, true, true, IR(283, 5), IR(29381, 10), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMin, true, true, IR(283, 5), IR(29391, 10), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMin, true, true, IR(283, 5), IR(29401, 10), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMin, true, true, IR(283, 5), IR(29411, 10), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMax, true, true, IR(283, 5), IR(29421, 10), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMax, true, true, IR(283, 5), IR(29431, 10), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMax, true, true, IR(283, 5), IR(29441, 10), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpReadPipe, true, true, IR(215, 6), IR(29451, 9), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpWritePipe, true, true, IR(215, 6), IR(29460, 10), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReservedReadPipe, true, true, IR(288, 8), IR(29470, 17), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReservedWritePipe, true, true, IR(288, 8), IR(29487, 18), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReserveReadPipePackets, true, true, IR(215, 6), IR(29505, 23), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReserveWritePipePackets, true, true, IR(215, 6), IR(29528, 24), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCommitReadPipe, false, false, IR(296, 4), IR(29552, 15), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCommitWritePipe, false, false, IR(296, 4), IR(29567, 16), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpIsValidReserveId, true, true, IR(160, 3), IR(29583, 17), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetNumPipePackets, true, true, IR(130, 5), IR(29600, 18), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetMaxPipePackets, true, true, IR(130, 5), IR(29618, 18), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupReserveReadPipePackets, true, true, IR(300, 7), IR(29636, 28), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupReserveWritePipePackets, true, true, IR(300, 7), IR(29664, 29), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupCommitReadPipe, false, false, IR(307, 5), IR(29693, 20), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupCommitWritePipe, false, false, IR(307, 5), IR(29713, 21), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpEnqueueMarker, true, true, IR(215, 6), IR(29734, 14), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpEnqueueKernel, true, true, IR(312, 13), IR(29748, 14), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelNDrangeSubGroupCount, true, true, IR(325, 7), IR(29762, 30), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelNDrangeMaxSubGroupSize, true, true, IR(325, 7), IR(29792, 32), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelWorkGroupSize, true, true, IR(215, 6), IR(29824, 23), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelPreferredWorkGroupSizeMultiple, true, true, IR(215, 6), IR(29847, 40), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpRetainEvent, false, false, IR(10, 1), IR(29887, 12), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpReleaseEvent, false, false, IR(10, 1), IR(29899, 13), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpCreateUserEvent, true, true, IR(39, 2), IR(29912, 16), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpIsValidEvent, true, true, IR(160, 3), IR(29928, 13), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpSetUserEventStatus, false, false, IR(36, 2), IR(29941, 19), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpCaptureEventProfilingInfo, false, false, IR(33, 3), IR(29960, 26), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetDefaultQueue, true, true, IR(39, 2), IR(29986, 16), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpBuildNDRange, true, true, IR(130, 5), IR(30002, 13), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpImageSparseSampleImplicitLod, true, true, IR(185, 5), IR(30015, 29), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleExplicitLod, true, true, IR(190, 5), IR(30044, 29), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleDrefImplicitLod, true, true, IR(195, 6), IR(30073, 33), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleDrefExplicitLod, true, true, IR(201, 6), IR(30106, 33), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjImplicitLod, true, true, IR(185, 5), IR(30139, 33), IR(0, 0), IR(219, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjExplicitLod, true, true, IR(190, 5), IR(30172, 33), IR(0, 0), IR(219, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjDrefImplicitLod, true, true, IR(195, 6), IR(30205, 37), IR(0, 0), IR(219, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjDrefExplicitLod, true, true, IR(201, 6), IR(30242, 37), IR(0, 0), IR(219, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseFetch, true, true, IR(185, 5), IR(30279, 17), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseGather, true, true, IR(195, 6), IR(30296, 18), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseDrefGather, true, true, IR(195, 6), IR(30314, 22), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseTexelsResident, true, true, IR(160, 3), IR(30336, 26), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpNoLine, false, false, IR(0, 0), IR(30362, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpAtomicFlagTestAndSet, true, true, IR(226, 5), IR(30369, 21), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicFlagClear, false, false, IR(332, 3), IR(30390, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpImageSparseRead, true, true, IR(185, 5), IR(30406, 16), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpSizeOf, true, true, IR(160, 3), IR(30422, 7), IR(0, 0), IR(1, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpTypePipeStorage, true, false, IR(68, 1), IR(30429, 16), IR(0, 0), IR(220, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantPipeStorage, true, true, IR(335, 5), IR(30445, 20), IR(0, 0), IR(220, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCreatePipeFromPipeStorage, true, true, IR(160, 3), IR(30465, 26), IR(0, 0), IR(220, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetKernelLocalSizeForSubgroupCount, true, true, IR(325, 7), IR(30491, 35), IR(0, 0), IR(155, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelMaxNumSubgroups, true, true, IR(215, 6), IR(30526, 25), IR(0, 0), IR(155, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpTypeNamedBarrier, true, false, IR(68, 1), IR(30551, 17), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpNamedBarrierInitialize, true, true, IR(160, 3), IR(30568, 23), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpMemoryNamedBarrier, false, false, IR(332, 3), IR(30591, 19), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpModuleProcessed, false, false, IR(11, 1), IR(30610, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpExecutionModeId, false, false, IR(65, 2), IR(30626, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,2), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpDecorateId, false, false, IR(163, 2), IR(30642, 11), IR(0, 0), IR(1, 0), IR(158, 1), SPV_SPIRV_VERSION_WORD(1,2), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupNonUniformElect, true, true, IR(340, 3), IR(30653, 21), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAll, true, true, IR(274, 4), IR(30674, 19), IR(0, 0), IR(222, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAny, true, true, IR(274, 4), IR(30693, 19), IR(0, 0), IR(222, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAllEqual, true, true, IR(274, 4), IR(30712, 24), IR(0, 0), IR(222, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBroadcast, true, true, IR(278, 5), IR(30736, 25), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBroadcastFirst, true, true, IR(274, 4), IR(30761, 30), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallot, true, true, IR(274, 4), IR(5662, 22), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformInverseBallot, true, true, IR(274, 4), IR(30791, 29), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotBitExtract, true, true, IR(278, 5), IR(30820, 32), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotBitCount, true, true, IR(283, 5), IR(30852, 30), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotFindLSB, true, true, IR(274, 4), IR(30882, 29), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotFindMSB, true, true, IR(274, 4), IR(30911, 29), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffle, true, true, IR(278, 5), IR(8752, 23), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleXor, true, true, IR(278, 5), IR(30940, 26), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleUp, true, true, IR(278, 5), IR(30966, 25), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleDown, true, true, IR(278, 5), IR(30991, 27), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformIAdd, true, true, IR(343, 6), IR(31018, 20), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFAdd, true, true, IR(343, 6), IR(31038, 20), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformIMul, true, true, IR(343, 6), IR(31058, 20), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMul, true, true, IR(343, 6), IR(31078, 20), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformSMin, true, true, IR(343, 6), IR(31098, 20), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformUMin, true, true, IR(343, 6), IR(31118, 20), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMin, true, true, IR(343, 6), IR(31138, 20), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformSMax, true, true, IR(343, 6), IR(31158, 20), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformUMax, true, true, IR(343, 6), IR(31178, 20), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMax, true, true, IR(343, 6), IR(31198, 20), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseAnd, true, true, IR(343, 6), IR(31218, 26), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseOr, true, true, IR(343, 6), IR(31244, 25), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseXor, true, true, IR(343, 6), IR(31269, 26), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalAnd, true, true, IR(343, 6), IR(31295, 26), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalOr, true, true, IR(343, 6), IR(31321, 25), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalXor, true, true, IR(343, 6), IR(31346, 26), IR(0, 0), IR(226, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadBroadcast, true, true, IR(278, 5), IR(31372, 29), IR(0, 0), IR(229, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadSwap, true, true, IR(278, 5), IR(31401, 24), IR(0, 0), IR(229, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpCopyLogical, true, true, IR(160, 3), IR(31425, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpPtrEqual, true, true, IR(172, 4), IR(31437, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrNotEqual, true, true, IR(172, 4), IR(31446, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrDiff, true, true, IR(172, 4), IR(31458, 8), IR(0, 0), IR(230, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpColorAttachmentReadEXT, true, true, IR(349, 4), IR(31466, 23), IR(0, 0), IR(147, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpDepthAttachmentReadEXT, true, true, IR(353, 3), IR(31489, 23), IR(0, 0), IR(156, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpStencilAttachmentReadEXT, true, true, IR(353, 3), IR(31512, 25), IR(0, 0), IR(157, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpTypeTensorARM, true, false, IR(356, 4), IR(31537, 14), IR(0, 0), IR(202, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTensorReadARM, true, true, IR(360, 5), IR(31593, 14), IR(0, 0), IR(202, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpTensorWriteARM, false, false, IR(365, 4), IR(31607, 15), IR(0, 0), IR(202, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpTensorQuerySizeARM, true, true, IR(172, 4), IR(31622, 19), IR(0, 0), IR(202, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpGraphConstantARM, true, true, IR(369, 3), IR(31641, 17), IR(0, 0), IR(233, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphEntryPointARM, false, false, IR(372, 3), IR(31658, 19), IR(0, 0), IR(233, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphARM, true, true, IR(39, 2), IR(9043, 9), IR(0, 0), IR(233, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphInputARM, true, true, IR(122, 4), IR(31677, 14), IR(0, 0), IR(233, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphSetOutputARM, false, false, IR(375, 3), IR(31691, 18), IR(0, 0), IR(233, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphEndARM, false, false, IR(0, 0), IR(31709, 12), IR(0, 0), IR(233, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpTypeGraphARM, true, false, IR(378, 3), IR(31721, 13), IR(0, 0), IR(233, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTerminateInvocation, false, false, IR(0, 0), IR(31734, 20), IR(0, 0), IR(3, 1), IR(168, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpTypeUntypedPointerKHR, true, false, IR(381, 2), IR(31754, 22), IR(0, 0), IR(234, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpUntypedVariableKHR, true, true, IR(383, 5), IR(31776, 19), IR(0, 0), IR(234, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedAccessChainKHR, true, true, IR(151, 5), IR(31795, 22), IR(0, 0), IR(234, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedInBoundsAccessChainKHR, true, true, IR(151, 5), IR(31817, 30), IR(0, 0), IR(234, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpSubgroupBallotKHR, true, true, IR(160, 3), IR(5423, 18), IR(0, 0), IR(235, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupFirstInvocationKHR, true, true, IR(160, 3), IR(31847, 27), IR(0, 0), IR(235, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpUntypedPtrAccessChainKHR, true, true, IR(388, 6), IR(31874, 25), IR(0, 0), IR(234, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedInBoundsPtrAccessChainKHR, true, true, IR(388, 6), IR(31899, 33), IR(0, 0), IR(234, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedArrayLengthKHR, true, true, IR(394, 5), IR(31932, 22), IR(0, 0), IR(234, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedPrefetchKHR, false, false, IR(399, 5), IR(31954, 19), IR(0, 0), IR(234, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpFmaKHR, true, true, IR(130, 5), IR(31973, 7), IR(0, 0), IR(236, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSubgroupAllKHR, true, true, IR(160, 3), IR(31980, 15), IR(0, 0), IR(237, 1), IR(41, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupAnyKHR, true, true, IR(160, 3), IR(31995, 15), IR(0, 0), IR(237, 1), IR(41, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupAllEqualKHR, true, true, IR(160, 3), IR(32010, 20), IR(0, 0), IR(237, 1), IR(41, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupNonUniformRotateKHR, true, true, IR(404, 6), IR(13262, 25), IR(0, 0), IR(238, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupReadInvocationKHR, true, true, IR(172, 4), IR(32030, 26), IR(0, 0), IR(235, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpExtInstWithForwardRefsKHR, true, true, IR(410, 5), IR(32056, 26), IR(0, 0), IR(1, 0), IR(169, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpUntypedGroupAsyncCopyKHR, true, true, IR(415, 11), IR(32082, 25), IR(0, 0), IR(234, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpTraceRayKHR, false, false, IR(426, 11), IR(32107, 12), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpExecuteCallableKHR, false, false, IR(36, 2), IR(32119, 19), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToAccelerationStructureKHR, true, true, IR(160, 3), IR(32138, 35), IR(0, 0), IR(239, 2), IR(170, 2), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIgnoreIntersectionKHR, false, false, IR(0, 0), IR(32173, 22), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTerminateRayKHR, false, false, IR(0, 0), IR(32195, 16), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSDot, true, true, IR(437, 5), IR(32258, 5), IR(93, 1), IR(241, 1), IR(122, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDot, true, true, IR(437, 5), IR(32271, 5), IR(94, 1), IR(241, 1), IR(122, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSUDot, true, true, IR(437, 5), IR(32284, 6), IR(95, 1), IR(241, 1), IR(122, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSDotAccSat, true, true, IR(442, 6), IR(32299, 11), IR(96, 1), IR(241, 1), IR(122, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDotAccSat, true, true, IR(442, 6), IR(32324, 11), IR(97, 1), IR(241, 1), IR(122, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSUDotAccSat, true, true, IR(442, 6), IR(32349, 12), IR(98, 1), IR(241, 1), IR(122, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpTypeCooperativeMatrixKHR, true, false, IR(448, 6), IR(32376, 25), IR(0, 0), IR(86, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeMatrixLoadKHR, true, true, IR(454, 6), IR(32401, 25), IR(0, 0), IR(86, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixStoreKHR, false, false, IR(460, 5), IR(32426, 26), IR(0, 0), IR(86, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixMulAddKHR, true, true, IR(465, 6), IR(32506, 27), IR(0, 0), IR(86, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpCooperativeMatrixLengthKHR, true, true, IR(160, 3), IR(32533, 27), IR(0, 0), IR(86, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpConstantCompositeReplicateEXT, true, true, IR(160, 3), IR(32560, 30), IR(0, 0), IR(242, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCompositeReplicateEXT, true, true, IR(160, 3), IR(32590, 34), IR(0, 0), IR(242, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpCompositeConstructReplicateEXT, true, true, IR(160, 3), IR(32624, 31), IR(0, 0), IR(242, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpTypeRayQueryKHR, true, false, IR(68, 1), IR(32655, 16), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpRayQueryInitializeKHR, false, false, IR(471, 8), IR(32671, 22), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryTerminateKHR, false, false, IR(10, 1), IR(32693, 21), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGenerateIntersectionKHR, false, false, IR(36, 2), IR(32714, 32), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryConfirmIntersectionKHR, false, false, IR(10, 1), IR(32746, 31), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryProceedKHR, true, true, IR(160, 3), IR(32777, 19), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTypeKHR, true, true, IR(172, 4), IR(32796, 31), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpImageSampleWeightedQCOM, true, true, IR(130, 5), IR(32827, 24), IR(0, 0), IR(243, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBoxFilterQCOM, true, true, IR(130, 5), IR(32851, 19), IR(0, 0), IR(244, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchSSDQCOM, true, true, IR(325, 7), IR(32870, 23), IR(0, 0), IR(245, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchSADQCOM, true, true, IR(325, 7), IR(32893, 23), IR(0, 0), IR(245, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpBitCastArrayQCOM, true, true, IR(160, 3), IR(32916, 17), IR(0, 0), IR(246, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpImageBlockMatchWindowSSDQCOM, true, true, IR(325, 7), IR(32933, 29), IR(0, 0), IR(247, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchWindowSADQCOM, true, true, IR(325, 7), IR(32962, 29), IR(0, 0), IR(247, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchGatherSSDQCOM, true, true, IR(325, 7), IR(32991, 29), IR(0, 0), IR(247, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchGatherSADQCOM, true, true, IR(325, 7), IR(33020, 29), IR(0, 0), IR(247, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpCompositeConstructCoopMatQCOM, true, true, IR(160, 3), IR(33049, 30), IR(0, 0), IR(246, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeExtractCoopMatQCOM, true, true, IR(160, 3), IR(33079, 28), IR(0, 0), IR(246, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpExtractSubArrayQCOM, true, true, IR(172, 4), IR(33107, 20), IR(0, 0), IR(246, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpGroupIAddNonUniformAMD, true, true, IR(283, 5), IR(33127, 23), IR(0, 0), IR(218, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFAddNonUniformAMD, true, true, IR(283, 5), IR(33150, 23), IR(0, 0), IR(218, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMinNonUniformAMD, true, true, IR(283, 5), IR(33173, 23), IR(0, 0), IR(218, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMinNonUniformAMD, true, true, IR(283, 5), IR(33196, 23), IR(0, 0), IR(218, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMinNonUniformAMD, true, true, IR(283, 5), IR(33219, 23), IR(0, 0), IR(218, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMaxNonUniformAMD, true, true, IR(283, 5), IR(33242, 23), IR(0, 0), IR(218, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMaxNonUniformAMD, true, true, IR(283, 5), IR(33265, 23), IR(0, 0), IR(218, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMaxNonUniformAMD, true, true, IR(283, 5), IR(33288, 23), IR(0, 0), IR(218, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpFragmentMaskFetchAMD, true, true, IR(172, 4), IR(33311, 21), IR(0, 0), IR(248, 1), IR(58, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFragmentFetchAMD, true, true, IR(130, 5), IR(33332, 17), IR(0, 0), IR(248, 1), IR(58, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReadClockKHR, true, true, IR(340, 3), IR(33349, 13), IR(0, 0), IR(249, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAllocateNodePayloadsAMDX, true, true, IR(278, 5), IR(33362, 25), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpEnqueueNodePayloadsAMDX, false, false, IR(10, 1), IR(33387, 24), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeNodePayloadArrayAMDX, true, false, IR(87, 2), IR(33411, 25), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFinishWritingNodePayloadAMDX, true, true, IR(160, 3), IR(33436, 29), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpNodePayloadArrayLengthAMDX, true, true, IR(160, 3), IR(33465, 27), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIsNodePayloadValidAMDX, true, true, IR(172, 4), IR(33492, 23), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConstantStringAMDX, true, false, IR(50, 2), IR(33515, 19), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSpecConstantStringAMDX, true, false, IR(50, 2), IR(33534, 23), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpGroupNonUniformQuadAllKHR, true, true, IR(160, 3), IR(33557, 26), IR(0, 0), IR(164, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadAnyKHR, true, true, IR(160, 3), IR(33583, 26), IR(0, 0), IR(164, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpHitObjectRecordHitMotionNV, false, false, IR(479, 14), IR(33609, 27), IR(0, 0), IR(250, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitWithIndexMotionNV, false, false, IR(493, 13), IR(33636, 36), IR(0, 0), IR(250, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissMotionNV, false, false, IR(506, 7), IR(33672, 28), IR(0, 0), IR(250, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldToObjectNV, true, true, IR(160, 3), IR(33700, 28), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectToWorldNV, true, true, IR(160, 3), IR(33728, 28), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayDirectionNV, true, true, IR(160, 3), IR(33756, 33), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayOriginNV, true, true, IR(160, 3), IR(33789, 30), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayMotionNV, false, false, IR(493, 13), IR(33819, 26), IR(0, 0), IR(250, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderRecordBufferHandleNV, true, true, IR(160, 3), IR(33845, 39), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderBindingTableRecordIndexNV, true, true, IR(160, 3), IR(33884, 44), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordEmptyNV, false, false, IR(10, 1), IR(33928, 23), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayNV, false, false, IR(513, 12), IR(33951, 20), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitNV, false, false, IR(493, 13), IR(33971, 21), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitWithIndexNV, false, false, IR(513, 12), IR(33992, 30), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissNV, false, false, IR(525, 6), IR(34022, 22), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectExecuteShaderNV, false, false, IR(36, 2), IR(34044, 25), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetCurrentTimeNV, true, true, IR(160, 3), IR(34069, 26), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetAttributesNV, false, false, IR(36, 2), IR(34095, 25), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetHitKindNV, true, true, IR(160, 3), IR(34120, 22), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetPrimitiveIndexNV, true, true, IR(160, 3), IR(34142, 29), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetGeometryIndexNV, true, true, IR(160, 3), IR(34171, 28), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceIdNV, true, true, IR(160, 3), IR(34199, 25), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceCustomIndexNV, true, true, IR(160, 3), IR(34224, 34), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayDirectionNV, true, true, IR(160, 3), IR(34258, 32), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayOriginNV, true, true, IR(160, 3), IR(34290, 29), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMaxNV, true, true, IR(160, 3), IR(34319, 22), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMinNV, true, true, IR(160, 3), IR(34341, 22), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsEmptyNV, true, true, IR(160, 3), IR(34363, 19), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsHitNV, true, true, IR(160, 3), IR(34382, 17), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsMissNV, true, true, IR(160, 3), IR(34399, 18), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHitObjectNV, false, false, IR(531, 3), IR(34417, 29), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHintNV, false, false, IR(36, 2), IR(34446, 24), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeHitObjectNV, true, false, IR(68, 1), IR(34470, 16), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpImageSampleFootprintNV, true, true, IR(534, 7), IR(34486, 23), IR(0, 0), IR(252, 1), IR(72, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpTypeCooperativeVectorNV, true, false, IR(89, 3), IR(34509, 24), IR(0, 0), IR(253, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeVectorMatrixMulNV, true, true, IR(541, 13), IR(34533, 29), IR(0, 0), IR(253, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorOuterProductAccumulateNV, false, false, IR(554, 7), IR(34562, 42), IR(0, 0), IR(254, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorReduceSumAccumulateNV, false, false, IR(33, 3), IR(34604, 39), IR(0, 0), IR(254, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorMatrixMulAddNV, true, true, IR(561, 16), IR(34643, 32), IR(0, 0), IR(253, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixConvertNV, true, true, IR(160, 3), IR(34675, 27), IR(0, 0), IR(255, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpEmitMeshTasksEXT, false, false, IR(577, 4), IR(34702, 17), IR(0, 0), IR(53, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSetMeshOutputsEXT, false, false, IR(36, 2), IR(34719, 18), IR(0, 0), IR(53, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpGroupNonUniformPartitionNV, true, true, IR(160, 3), IR(34737, 27), IR(0, 0), IR(183, 1), IR(75, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpWritePackedPrimitiveIndices4x8NV, false, false, IR(36, 2), IR(34764, 33), IR(0, 0), IR(50, 1), IR(18, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFetchMicroTriangleVertexPositionNV, true, true, IR(325, 7), IR(34797, 35), IR(0, 0), IR(256, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFetchMicroTriangleVertexBarycentricNV, true, true, IR(325, 7), IR(34832, 38), IR(0, 0), IR(256, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorLoadNV, true, true, IR(581, 5), IR(34870, 24), IR(0, 0), IR(253, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeVectorStoreNV, false, false, IR(586, 4), IR(34894, 25), IR(0, 0), IR(253, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpReportIntersectionKHR, true, true, IR(172, 4), IR(34919, 22), IR(99, 1), IR(54, 2), IR(24, 2), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIgnoreIntersectionNV, false, false, IR(0, 0), IR(34962, 21), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTerminateRayNV, false, false, IR(0, 0), IR(34983, 15), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceNV, false, false, IR(426, 11), IR(34998, 8), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceMotionNV, false, false, IR(513, 12), IR(35006, 14), IR(0, 0), IR(57, 1), IR(27, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceRayMotionNV, false, false, IR(513, 12), IR(35020, 17), IR(0, 0), IR(57, 1), IR(27, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTriangleVertexPositionsKHR, true, true, IR(172, 4), IR(35037, 50), IR(0, 0), IR(257, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeAccelerationStructureKHR, true, false, IR(68, 1), IR(35087, 29), IR(100, 1), IR(258, 4), IR(172, 4), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpExecuteCallableNV, false, false, IR(36, 2), IR(35144, 18), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionClusterIdNV, true, true, IR(172, 4), IR(35162, 35), IR(101, 1), IR(64, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetClusterIdNV, true, true, IR(160, 3), IR(35220, 24), IR(0, 0), IR(64, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeCooperativeMatrixNV, true, false, IR(590, 5), IR(35244, 24), IR(0, 0), IR(262, 1), IR(79, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeMatrixLoadNV, true, true, IR(595, 6), IR(35268, 24), IR(0, 0), IR(262, 1), IR(79, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixStoreNV, false, false, IR(601, 5), IR(35292, 25), IR(0, 0), IR(262, 1), IR(79, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixMulAddNV, true, true, IR(130, 5), IR(35317, 26), IR(0, 0), IR(262, 1), IR(79, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixLengthNV, true, true, IR(160, 3), IR(35343, 26), IR(0, 0), IR(262, 1), IR(79, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpBeginInvocationInterlockEXT, false, false, IR(0, 0), IR(35369, 28), IR(0, 0), IR(263, 3), IR(80, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpEndInvocationInterlockEXT, false, false, IR(0, 0), IR(35397, 26), IR(0, 0), IR(263, 3), IR(80, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixReduceNV, true, true, IR(606, 5), IR(35466, 26), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpCooperativeMatrixLoadTensorNV, true, true, IR(611, 7), IR(35567, 30), IR(0, 0), IR(200, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixStoreTensorNV, false, false, IR(618, 5), IR(35597, 31), IR(0, 0), IR(200, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixPerElementOpNV, true, true, IR(151, 5), IR(35628, 32), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpTypeTensorLayoutNV, true, false, IR(89, 3), IR(35660, 19), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeTensorViewNV, true, false, IR(623, 4), IR(35679, 17), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCreateTensorLayoutNV, true, true, IR(39, 2), IR(35696, 21), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetDimensionNV, true, true, IR(122, 4), IR(35717, 27), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetStrideNV, true, true, IR(122, 4), IR(35744, 24), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSliceNV, true, true, IR(122, 4), IR(35768, 20), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetClampValueNV, true, true, IR(172, 4), IR(35788, 28), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCreateTensorViewNV, true, true, IR(39, 2), IR(35816, 19), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetDimensionNV, true, true, IR(122, 4), IR(35835, 25), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetStrideNV, true, true, IR(122, 4), IR(35860, 22), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpDemoteToHelperInvocation, false, false, IR(0, 0), IR(11574, 25), IR(45, 1), IR(269, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpIsHelperInvocationEXT, true, true, IR(39, 2), IR(35882, 22), IR(0, 0), IR(269, 1), IR(81, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetClipNV, true, true, IR(325, 7), IR(35904, 20), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetBlockSizeNV, true, true, IR(122, 4), IR(35924, 27), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixTransposeNV, true, true, IR(160, 3), IR(35951, 29), IR(0, 0), IR(255, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToImageNV, true, true, IR(160, 3), IR(35980, 18), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToSamplerNV, true, true, IR(160, 3), IR(35998, 20), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertImageToUNV, true, true, IR(160, 3), IR(36018, 18), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertSamplerToUNV, true, true, IR(160, 3), IR(36036, 20), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToSampledImageNV, true, true, IR(160, 3), IR(36056, 25), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertSampledImageToUNV, true, true, IR(160, 3), IR(36081, 25), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSamplerImageAddressingModeNV, false, false, IR(0, 1), IR(36106, 29), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRawAccessChainNV, true, true, IR(627, 7), IR(36187, 17), IR(0, 0), IR(189, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpRayQueryGetIntersectionSpherePositionNV, true, true, IR(172, 4), IR(36204, 40), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionSphereRadiusNV, true, true, IR(172, 4), IR(36244, 38), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSPositionsNV, true, true, IR(172, 4), IR(36282, 38), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSRadiiNV, true, true, IR(172, 4), IR(36320, 34), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSHitValueNV, true, true, IR(172, 4), IR(36354, 37), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetSpherePositionNV, true, true, IR(160, 3), IR(36391, 29), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetSphereRadiusNV, true, true, IR(160, 3), IR(36420, 27), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetLSSPositionsNV, true, true, IR(160, 3), IR(36447, 27), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetLSSRadiiNV, true, true, IR(160, 3), IR(36474, 23), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsSphereHitNV, true, true, IR(160, 3), IR(36497, 23), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsLSSHitNV, true, true, IR(160, 3), IR(36520, 20), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryIsSphereHitNV, true, true, IR(172, 4), IR(36540, 22), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryIsLSSHitNV, true, true, IR(172, 4), IR(36562, 19), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSubgroupShuffleINTEL, true, true, IR(172, 4), IR(12022, 21), IR(0, 0), IR(270, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleDownINTEL, true, true, IR(130, 5), IR(36581, 25), IR(0, 0), IR(270, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleUpINTEL, true, true, IR(130, 5), IR(36606, 23), IR(0, 0), IR(270, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleXorINTEL, true, true, IR(172, 4), IR(36629, 24), IR(0, 0), IR(270, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupBlockReadINTEL, true, true, IR(160, 3), IR(36653, 23), IR(0, 0), IR(271, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupBlockWriteINTEL, false, false, IR(36, 2), IR(36676, 24), IR(0, 0), IR(271, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageBlockReadINTEL, true, true, IR(172, 4), IR(36700, 28), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageBlockWriteINTEL, false, false, IR(33, 3), IR(36728, 29), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageMediaBlockReadINTEL, true, true, IR(215, 6), IR(36757, 33), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageMediaBlockWriteINTEL, false, false, IR(634, 5), IR(36790, 34), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpUCountLeadingZerosINTEL, true, true, IR(160, 3), IR(36824, 24), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUCountTrailingZerosINTEL, true, true, IR(160, 3), IR(36848, 25), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAbsISubINTEL, true, true, IR(172, 4), IR(36873, 13), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAbsUSubINTEL, true, true, IR(172, 4), IR(36886, 13), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAddSatINTEL, true, true, IR(172, 4), IR(36899, 13), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAddSatINTEL, true, true, IR(172, 4), IR(36912, 13), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAverageINTEL, true, true, IR(172, 4), IR(36925, 14), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAverageINTEL, true, true, IR(172, 4), IR(36939, 14), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAverageRoundedINTEL, true, true, IR(172, 4), IR(36953, 21), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAverageRoundedINTEL, true, true, IR(172, 4), IR(36974, 21), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpISubSatINTEL, true, true, IR(172, 4), IR(36995, 13), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUSubSatINTEL, true, true, IR(172, 4), IR(37008, 13), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIMul32x16INTEL, true, true, IR(172, 4), IR(37021, 15), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUMul32x16INTEL, true, true, IR(172, 4), IR(37036, 15), IR(0, 0), IR(274, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConstantFunctionPointerINTEL, true, true, IR(160, 3), IR(37051, 29), IR(0, 0), IR(198, 1), IR(95, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFunctionPointerCallINTEL, true, true, IR(107, 3), IR(37080, 25), IR(0, 0), IR(198, 1), IR(95, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmTargetINTEL, true, false, IR(50, 2), IR(37105, 15), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmINTEL, true, true, IR(639, 6), IR(12240, 9), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmCallINTEL, true, true, IR(122, 4), IR(37120, 13), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAtomicFMinEXT, true, true, IR(235, 6), IR(37133, 14), IR(0, 0), IR(275, 4), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicFMaxEXT, true, true, IR(235, 6), IR(37147, 14), IR(0, 0), IR(275, 4), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAssumeTrueKHR, false, false, IR(10, 1), IR(37161, 14), IR(0, 0), IR(279, 1), IR(99, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpExpectKHR, true, true, IR(172, 4), IR(37175, 10), IR(0, 0), IR(279, 1), IR(99, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpDecorateString, false, false, IR(163, 2), IR(37185, 15), IR(102, 1), IR(1, 0), IR(176, 2), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpMemberDecorateString, false, false, IR(165, 3), IR(37221, 21), IR(103, 1), IR(1, 0), IR(176, 2), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpVmeImageINTEL, true, true, IR(172, 4), IR(37269, 14), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeVmeImageINTEL, true, false, IR(87, 2), IR(37283, 18), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImePayloadINTEL, true, false, IR(68, 1), IR(37301, 23), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcRefPayloadINTEL, true, false, IR(68, 1), IR(37324, 23), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcSicPayloadINTEL, true, false, IR(68, 1), IR(37347, 23), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcMcePayloadINTEL, true, false, IR(68, 1), IR(37370, 23), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcMceResultINTEL, true, false, IR(68, 1), IR(37393, 22), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultINTEL, true, false, IR(68, 1), IR(37415, 22), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultSingleReferenceStreamoutINTEL, true, false, IR(68, 1), IR(37437, 46), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultDualReferenceStreamoutINTEL, true, false, IR(68, 1), IR(37483, 44), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeSingleReferenceStreaminINTEL, true, false, IR(68, 1), IR(37527, 39), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeDualReferenceStreaminINTEL, true, false, IR(68, 1), IR(37566, 37), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcRefResultINTEL, true, false, IR(68, 1), IR(37603, 22), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcSicResultINTEL, true, false, IR(68, 1), IR(37625, 22), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL, true, true, IR(172, 4), IR(37647, 60), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL, true, true, IR(172, 4), IR(37707, 53), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterShapePenaltyINTEL, true, true, IR(172, 4), IR(37760, 47), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterShapePenaltyINTEL, true, true, IR(172, 4), IR(37807, 40), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL, true, true, IR(172, 4), IR(37847, 51), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterDirectionPenaltyINTEL, true, true, IR(172, 4), IR(37898, 44), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL, true, true, IR(172, 4), IR(37942, 51), IR(0, 0), IR(281, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL, true, true, IR(172, 4), IR(37993, 56), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL, true, true, IR(39, 2), IR(38049, 50), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL, true, true, IR(39, 2), IR(38099, 52), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL, true, true, IR(39, 2), IR(38151, 49), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetMotionVectorCostFunctionINTEL, true, true, IR(215, 6), IR(38200, 47), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL, true, true, IR(172, 4), IR(38247, 50), IR(0, 0), IR(281, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL, true, true, IR(39, 2), IR(38297, 51), IR(0, 0), IR(281, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL, true, true, IR(39, 2), IR(38348, 56), IR(0, 0), IR(283, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetAcOnlyHaarINTEL, true, true, IR(160, 3), IR(38404, 33), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL, true, true, IR(172, 4), IR(38437, 52), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL, true, true, IR(172, 4), IR(38489, 61), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL, true, true, IR(130, 5), IR(38550, 61), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToImePayloadINTEL, true, true, IR(160, 3), IR(38611, 39), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToImeResultINTEL, true, true, IR(160, 3), IR(38650, 38), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToRefPayloadINTEL, true, true, IR(160, 3), IR(38688, 39), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToRefResultINTEL, true, true, IR(160, 3), IR(38727, 38), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToSicPayloadINTEL, true, true, IR(160, 3), IR(38765, 39), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToSicResultINTEL, true, true, IR(160, 3), IR(38804, 38), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetMotionVectorsINTEL, true, true, IR(160, 3), IR(38842, 36), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterDistortionsINTEL, true, true, IR(160, 3), IR(38878, 39), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetBestInterDistortionsINTEL, true, true, IR(160, 3), IR(38917, 43), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMajorShapeINTEL, true, true, IR(160, 3), IR(38960, 38), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMinorShapeINTEL, true, true, IR(160, 3), IR(38998, 38), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterDirectionsINTEL, true, true, IR(160, 3), IR(39036, 38), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMotionVectorCountINTEL, true, true, IR(160, 3), IR(39074, 45), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterReferenceIdsINTEL, true, true, IR(160, 3), IR(39119, 40), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL, true, true, IR(130, 5), IR(39159, 62), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeInitializeINTEL, true, true, IR(130, 5), IR(39221, 30), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetSingleReferenceINTEL, true, true, IR(130, 5), IR(39251, 38), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetDualReferenceINTEL, true, true, IR(215, 6), IR(39289, 36), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeRefWindowSizeINTEL, true, true, IR(172, 4), IR(39325, 33), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeAdjustRefOffsetINTEL, true, true, IR(215, 6), IR(39358, 35), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(39393, 39), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetMaxMotionVectorCountINTEL, true, true, IR(172, 4), IR(39432, 43), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetUnidirectionalMixDisableINTEL, true, true, IR(160, 3), IR(39475, 47), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetEarlySearchTerminationThresholdINTEL, true, true, IR(172, 4), IR(39522, 54), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetWeightedSadINTEL, true, true, IR(172, 4), IR(39576, 34), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(39610, 47), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(39657, 45), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL, true, true, IR(215, 6), IR(39702, 55), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL, true, true, IR(325, 7), IR(39757, 53), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL, true, true, IR(130, 5), IR(39810, 56), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL, true, true, IR(215, 6), IR(39866, 54), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL, true, true, IR(215, 6), IR(39920, 58), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL, true, true, IR(325, 7), IR(39978, 56), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeConvertToMceResultINTEL, true, true, IR(160, 3), IR(40034, 38), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetSingleReferenceStreaminINTEL, true, true, IR(160, 3), IR(40072, 46), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetDualReferenceStreaminINTEL, true, true, IR(160, 3), IR(40118, 44), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeStripSingleReferenceStreamoutINTEL, true, true, IR(160, 3), IR(40162, 49), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeStripDualReferenceStreamoutINTEL, true, true, IR(160, 3), IR(40211, 47), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL, true, true, IR(172, 4), IR(40258, 70), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL, true, true, IR(172, 4), IR(40328, 68), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL, true, true, IR(172, 4), IR(40396, 69), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL, true, true, IR(130, 5), IR(40465, 68), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL, true, true, IR(130, 5), IR(40533, 66), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL, true, true, IR(130, 5), IR(40599, 67), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetBorderReachedINTEL, true, true, IR(172, 4), IR(40666, 36), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetTruncatedSearchIndicationINTEL, true, true, IR(160, 3), IR(40702, 48), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL, true, true, IR(160, 3), IR(40750, 59), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL, true, true, IR(160, 3), IR(40809, 58), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL, true, true, IR(160, 3), IR(40867, 56), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcFmeInitializeINTEL, true, true, IR(645, 9), IR(40923, 30), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcBmeInitializeINTEL, true, true, IR(654, 10), IR(40953, 30), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(40983, 39), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefSetBidirectionalMixDisableINTEL, true, true, IR(160, 3), IR(41022, 46), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefSetBilinearFilterEnableINTEL, true, true, IR(160, 3), IR(41068, 43), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(41111, 47), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(41158, 45), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithMultiReferenceINTEL, true, true, IR(130, 5), IR(41203, 46), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL, true, true, IR(215, 6), IR(41249, 56), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefConvertToMceResultINTEL, true, true, IR(160, 3), IR(41305, 38), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicInitializeINTEL, true, true, IR(160, 3), IR(41343, 30), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureSkcINTEL, true, true, IR(288, 8), IR(41373, 32), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureIpeLumaINTEL, true, true, IR(654, 10), IR(41405, 36), IR(0, 0), IR(281, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureIpeLumaChromaINTEL, true, true, IR(664, 13), IR(41441, 42), IR(0, 0), IR(283, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetMotionVectorMaskINTEL, true, true, IR(172, 4), IR(41483, 39), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(41522, 39), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraLumaShapePenaltyINTEL, true, true, IR(172, 4), IR(41561, 44), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraLumaModeCostFunctionINTEL, true, true, IR(215, 6), IR(41605, 48), IR(0, 0), IR(281, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraChromaModeCostFunctionINTEL, true, true, IR(172, 4), IR(41653, 50), IR(0, 0), IR(283, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetBilinearFilterEnableINTEL, true, true, IR(160, 3), IR(41703, 43), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetSkcForwardTransformEnableINTEL, true, true, IR(172, 4), IR(41746, 48), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetBlockBasedRawSkipSadINTEL, true, true, IR(172, 4), IR(41794, 43), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateIpeINTEL, true, true, IR(172, 4), IR(41837, 31), IR(0, 0), IR(281, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(41868, 47), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(41915, 45), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithMultiReferenceINTEL, true, true, IR(130, 5), IR(41960, 46), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL, true, true, IR(215, 6), IR(42006, 56), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConvertToMceResultINTEL, true, true, IR(160, 3), IR(42062, 38), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetIpeLumaShapeINTEL, true, true, IR(160, 3), IR(42100, 35), IR(0, 0), IR(281, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetBestIpeLumaDistortionINTEL, true, true, IR(160, 3), IR(42135, 44), IR(0, 0), IR(281, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetBestIpeChromaDistortionINTEL, true, true, IR(160, 3), IR(42179, 46), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedIpeLumaModesINTEL, true, true, IR(160, 3), IR(42225, 41), IR(0, 0), IR(281, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetIpeChromaModeINTEL, true, true, IR(160, 3), IR(42266, 36), IR(0, 0), IR(283, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL, true, true, IR(160, 3), IR(42302, 50), IR(0, 0), IR(281, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL, true, true, IR(160, 3), IR(42352, 48), IR(0, 0), IR(281, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetInterRawSadsINTEL, true, true, IR(160, 3), IR(42400, 35), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpVariableLengthArrayINTEL, true, true, IR(160, 3), IR(12478, 25), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpSaveMemoryINTEL, true, true, IR(39, 2), IR(42435, 16), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpRestoreMemoryINTEL, false, false, IR(10, 1), IR(42451, 19), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpArbitraryFloatSinCosPiINTEL, true, true, IR(677, 8), IR(42470, 28), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastINTEL, true, true, IR(677, 8), IR(42498, 24), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastFromIntINTEL, true, true, IR(677, 8), IR(42522, 31), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastToIntINTEL, true, true, IR(677, 8), IR(42553, 29), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatAddINTEL, true, true, IR(685, 10), IR(42582, 23), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSubINTEL, true, true, IR(685, 10), IR(42605, 23), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatMulINTEL, true, true, IR(685, 10), IR(42628, 23), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatDivINTEL, true, true, IR(685, 10), IR(42651, 23), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatGTINTEL, true, true, IR(695, 6), IR(42674, 22), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatGEINTEL, true, true, IR(695, 6), IR(42696, 22), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLTINTEL, true, true, IR(695, 6), IR(42718, 22), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLEINTEL, true, true, IR(695, 6), IR(42740, 22), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatEQINTEL, true, true, IR(695, 6), IR(42762, 22), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatRecipINTEL, true, true, IR(677, 8), IR(42784, 25), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatRSqrtINTEL, true, true, IR(677, 8), IR(42809, 25), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCbrtINTEL, true, true, IR(677, 8), IR(42834, 24), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatHypotINTEL, true, true, IR(685, 10), IR(42858, 25), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSqrtINTEL, true, true, IR(677, 8), IR(42883, 24), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLogINTEL, true, true, IR(677, 8), IR(42907, 23), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog2INTEL, true, true, IR(677, 8), IR(42930, 24), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog10INTEL, true, true, IR(677, 8), IR(42954, 25), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog1pINTEL, true, true, IR(677, 8), IR(42979, 25), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExpINTEL, true, true, IR(677, 8), IR(43004, 23), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExp2INTEL, true, true, IR(677, 8), IR(43027, 24), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExp10INTEL, true, true, IR(677, 8), IR(43051, 25), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExpm1INTEL, true, true, IR(677, 8), IR(43076, 25), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinINTEL, true, true, IR(677, 8), IR(43101, 23), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCosINTEL, true, true, IR(677, 8), IR(43124, 23), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinCosINTEL, true, true, IR(677, 8), IR(43147, 26), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinPiINTEL, true, true, IR(677, 8), IR(43173, 25), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCosPiINTEL, true, true, IR(677, 8), IR(43198, 25), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatASinINTEL, true, true, IR(677, 8), IR(43223, 24), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatASinPiINTEL, true, true, IR(677, 8), IR(43247, 26), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatACosINTEL, true, true, IR(677, 8), IR(43273, 24), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatACosPiINTEL, true, true, IR(677, 8), IR(43297, 26), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATanINTEL, true, true, IR(677, 8), IR(43323, 24), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATanPiINTEL, true, true, IR(677, 8), IR(43347, 26), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATan2INTEL, true, true, IR(685, 10), IR(43373, 25), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowINTEL, true, true, IR(685, 10), IR(43398, 23), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowRINTEL, true, true, IR(685, 10), IR(43421, 24), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowNINTEL, true, true, IR(685, 10), IR(43445, 24), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpLoopControlINTEL, false, false, IR(18, 1), IR(43469, 17), IR(0, 0), IR(287, 1), IR(106, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAliasDomainDeclINTEL, true, false, IR(701, 2), IR(43486, 21), IR(0, 0), IR(136, 1), IR(113, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAliasScopeDeclINTEL, true, false, IR(703, 3), IR(43507, 20), IR(0, 0), IR(136, 1), IR(113, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAliasScopeListDeclINTEL, true, false, IR(92, 2), IR(43527, 24), IR(0, 0), IR(136, 1), IR(113, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSqrtINTEL, true, true, IR(677, 8), IR(43551, 15), IR(0, 0), IR(188, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedRecipINTEL, true, true, IR(677, 8), IR(43566, 16), IR(0, 0), IR(188, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedRsqrtINTEL, true, true, IR(677, 8), IR(43582, 16), IR(0, 0), IR(188, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinINTEL, true, true, IR(677, 8), IR(43598, 14), IR(0, 0), IR(188, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedCosINTEL, true, true, IR(677, 8), IR(43612, 14), IR(0, 0), IR(188, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinCosINTEL, true, true, IR(677, 8), IR(43626, 17), IR(0, 0), IR(188, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinPiINTEL, true, true, IR(677, 8), IR(43643, 16), IR(0, 0), IR(188, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedCosPiINTEL, true, true, IR(677, 8), IR(43659, 16), IR(0, 0), IR(188, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinCosPiINTEL, true, true, IR(677, 8), IR(43675, 19), IR(0, 0), IR(188, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedLogINTEL, true, true, IR(677, 8), IR(43694, 14), IR(0, 0), IR(188, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedExpINTEL, true, true, IR(677, 8), IR(43708, 14), IR(0, 0), IR(188, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpPtrCastToCrossWorkgroupINTEL, true, true, IR(160, 3), IR(43722, 29), IR(0, 0), IR(199, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpCrossWorkgroupCastToPtrINTEL, true, true, IR(160, 3), IR(43751, 29), IR(0, 0), IR(199, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpReadPipeBlockingINTEL, true, true, IR(172, 4), IR(43780, 22), IR(0, 0), IR(288, 1), IR(120, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpWritePipeBlockingINTEL, true, true, IR(172, 4), IR(43802, 23), IR(0, 0), IR(288, 1), IR(120, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpFPGARegINTEL, true, true, IR(160, 3), IR(13037, 13), IR(0, 0), IR(289, 1), IR(121, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetRayTMinKHR, true, true, IR(160, 3), IR(43825, 22), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetRayFlagsKHR, true, true, IR(160, 3), IR(43847, 23), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTKHR, true, true, IR(172, 4), IR(43870, 28), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceCustomIndexKHR, true, true, IR(172, 4), IR(43898, 46), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceIdKHR, true, true, IR(172, 4), IR(43944, 37), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR, true, true, IR(172, 4), IR(43981, 65), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionGeometryIndexKHR, true, true, IR(172, 4), IR(44046, 40), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionPrimitiveIndexKHR, true, true, IR(172, 4), IR(44086, 41), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionBarycentricsKHR, true, true, IR(172, 4), IR(44127, 39), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionFrontFaceKHR, true, true, IR(172, 4), IR(44166, 36), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionCandidateAABBOpaqueKHR, true, true, IR(160, 3), IR(44202, 46), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectRayDirectionKHR, true, true, IR(172, 4), IR(44248, 45), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectRayOriginKHR, true, true, IR(172, 4), IR(44293, 42), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetWorldRayDirectionKHR, true, true, IR(160, 3), IR(44335, 32), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetWorldRayOriginKHR, true, true, IR(160, 3), IR(44367, 29), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectToWorldKHR, true, true, IR(172, 4), IR(44396, 40), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionWorldToObjectKHR, true, true, IR(172, 4), IR(44436, 40), IR(0, 0), IR(192, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAtomicFAddEXT, true, true, IR(235, 6), IR(44476, 14), IR(0, 0), IR(290, 4), IR(129, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpTypeBufferSurfaceINTEL, true, false, IR(100, 2), IR(44490, 23), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeStructContinuedINTEL, false, false, IR(706, 1), IR(44513, 25), IR(0, 0), IR(294, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantCompositeContinuedINTEL, false, false, IR(706, 1), IR(44538, 32), IR(0, 0), IR(294, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCompositeContinuedINTEL, false, false, IR(706, 1), IR(44570, 36), IR(0, 0), IR(294, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpCompositeConstructContinuedINTEL, true, true, IR(107, 3), IR(44606, 33), IR(0, 0), IR(294, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpConvertFToBF16INTEL, true, true, IR(160, 3), IR(44639, 20), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertBF16ToFINTEL, true, true, IR(160, 3), IR(44659, 20), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpControlBarrierArriveINTEL, false, false, IR(221, 3), IR(44679, 26), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpControlBarrierWaitINTEL, false, false, IR(221, 3), IR(44705, 24), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpArithmeticFenceEXT, true, true, IR(160, 3), IR(13476, 19), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpTaskSequenceCreateINTEL, true, true, IR(707, 7), IR(44729, 24), IR(0, 0), IR(298, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTaskSequenceAsyncINTEL, false, false, IR(168, 2), IR(44753, 23), IR(0, 0), IR(298, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTaskSequenceGetINTEL, true, true, IR(160, 3), IR(44776, 21), IR(0, 0), IR(298, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTaskSequenceReleaseINTEL, false, false, IR(10, 1), IR(44797, 25), IR(0, 0), IR(298, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeTaskSequenceINTEL, true, false, IR(68, 1), IR(44822, 22), IR(0, 0), IR(298, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpSubgroupBlockPrefetchINTEL, false, false, IR(139, 3), IR(44844, 27), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadINTEL, false, false, IR(714, 10), IR(44871, 25), IR(0, 0), IR(108, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadTransformINTEL, false, false, IR(714, 10), IR(44896, 34), IR(0, 0), IR(300, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadTransposeINTEL, false, false, IR(714, 10), IR(44930, 34), IR(0, 0), IR(301, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockPrefetchINTEL, false, false, IR(724, 9), IR(44964, 29), IR(0, 0), IR(108, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockStoreINTEL, false, false, IR(714, 10), IR(44993, 26), IR(0, 0), IR(108, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupMatrixMultiplyAccumulateINTEL, true, true, IR(733, 7), IR(13814, 38), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpBitwiseFunctionINTEL, true, true, IR(215, 6), IR(45081, 21), IR(0, 0), IR(303, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpUntypedVariableLengthArrayINTEL, true, true, IR(172, 4), IR(13880, 32), IR(0, 0), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpConditionalExtensionINTEL, false, false, IR(45, 2), IR(45102, 26), IR(0, 0), IR(111, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpConditionalEntryPointINTEL, false, false, IR(740, 5), IR(45128, 27), IR(0, 0), IR(111, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpConditionalCapabilityINTEL, false, false, IR(745, 2), IR(45155, 27), IR(0, 0), IR(111, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpSpecConstantTargetINTEL, true, true, IR(747, 4), IR(45182, 24), IR(0, 0), IR(305, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantArchitectureINTEL, true, true, IR(751, 6), IR(45206, 30), IR(0, 0), IR(305, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCapabilitiesINTEL, true, true, IR(757, 3), IR(45273, 30), IR(0, 0), IR(305, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConditionalCopyObjectINTEL, true, true, IR(107, 3), IR(45303, 27), IR(0, 0), IR(111, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpGroupIMulKHR, true, true, IR(283, 5), IR(45330, 13), IR(0, 0), IR(306, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMulKHR, true, true, IR(283, 5), IR(45343, 13), IR(0, 0), IR(306, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseAndKHR, true, true, IR(283, 5), IR(45356, 19), IR(0, 0), IR(306, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseOrKHR, true, true, IR(283, 5), IR(45375, 18), IR(0, 0), IR(306, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseXorKHR, true, true, IR(283, 5), IR(45393, 19), IR(0, 0), IR(306, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalAndKHR, true, true, IR(283, 5), IR(45412, 19), IR(0, 0), IR(306, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalOrKHR, true, true, IR(283, 5), IR(45431, 18), IR(0, 0), IR(306, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalXorKHR, true, true, IR(283, 5), IR(45449, 19), IR(0, 0), IR(306, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpRoundFToTF32INTEL, true, true, IR(160, 3), IR(45468, 18), IR(0, 0), IR(307, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpMaskedGatherINTEL, true, true, IR(760, 6), IR(45486, 18), IR(0, 0), IR(308, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpMaskedScatterINTEL, false, false, IR(766, 4), IR(45504, 19), IR(0, 0), IR(308, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpConvertHandleToImageINTEL, true, true, IR(160, 3), IR(45523, 26), IR(0, 0), IR(309, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertHandleToSamplerINTEL, true, true, IR(160, 3), IR(45549, 28), IR(0, 0), IR(309, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertHandleToSampledImageINTEL, true, true, IR(160, 3), IR(45577, 33), IR(0, 0), IR(309, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
}};

// Opcode strings (without the 'Op' prefix) and opcode values, ordered by name.
// The fields in order are:
//   name, either the primary name or an alias, indexing into kStrings
//   index into kInstructionDesc
static const std::array<NameIndex, 834> kInstructionNames{{
  {IR(36873, 13), 554}, // 0 AbsISubINTEL
  {IR(36886, 13), 555}, // 1 AbsUSubINTEL
  {IR(26686, 12), 58}, // 2 AccessChain
  {IR(43486, 21), 740}, // 3 AliasDomainDeclINTEL
  {IR(43507, 20), 741}, // 4 AliasScopeDeclINTEL
  {IR(43527, 24), 742}, // 5 AliasScopeListDeclINTEL
  {IR(27983, 4), 143}, // 6 All
  {IR(33362, 25), 426}, // 7 AllocateNodePayloadsAMDX
  {IR(27979, 4), 142}, // 8 Any
  {IR(43273, 24), 731}, // 9 ArbitraryFloatACosINTEL
  {IR(43297, 26), 732}, // 10 ArbitraryFloatACosPiINTEL
  {IR(43223, 24), 729}, // 11 ArbitraryFloatASinINTEL
  {IR(43247, 26), 730}, // 12 ArbitraryFloatASinPiINTEL
  {IR(43373, 25), 735}, // 13 ArbitraryFloatATan2INTEL
  {IR(43323, 24), 733}, // 14 ArbitraryFloatATanINTEL
  {IR(43347, 26), 734}, // 15 ArbitraryFloatATanPiINTEL
  {IR(42582, 23), 702}, // 16 ArbitraryFloatAddINTEL
  {IR(42522, 31), 700}, // 17 ArbitraryFloatCastFromIntINTEL
  {IR(42498, 24), 699}, // 18 ArbitraryFloatCastINTEL
  {IR(42553, 29), 701}, // 19 ArbitraryFloatCastToIntINTEL
  {IR(42834, 24), 713}, // 20 ArbitraryFloatCbrtINTEL
  {IR(43124, 23), 725}, // 21 ArbitraryFloatCosINTEL
  {IR(43198, 25), 728}, // 22 ArbitraryFloatCosPiINTEL
  {IR(42651, 23), 705}, // 23 ArbitraryFloatDivINTEL
  {IR(42762, 22), 710}, // 24 ArbitraryFloatEQINTEL
  {IR(43051, 25), 722}, // 25 ArbitraryFloatExp10INTEL
  {IR(43027, 24), 721}, // 26 ArbitraryFloatExp2INTEL
  {IR(43004, 23), 720}, // 27 ArbitraryFloatExpINTEL
  {IR(43076, 25), 723}, // 28 ArbitraryFloatExpm1INTEL
  {IR(42696, 22), 707}, // 29 ArbitraryFloatGEINTEL
  {IR(42674, 22), 706}, // 30 ArbitraryFloatGTINTEL
  {IR(42858, 25), 714}, // 31 ArbitraryFloatHypotINTEL
  {IR(42740, 22), 709}, // 32 ArbitraryFloatLEINTEL
  {IR(42718, 22), 708}, // 33 ArbitraryFloatLTINTEL
  {IR(42954, 25), 718}, // 34 ArbitraryFloatLog10INTEL
  {IR(42979, 25), 719}, // 35 ArbitraryFloatLog1pINTEL
  {IR(42930, 24), 717}, // 36 ArbitraryFloatLog2INTEL
  {IR(42907, 23), 716}, // 37 ArbitraryFloatLogINTEL
  {IR(42628, 23), 704}, // 38 ArbitraryFloatMulINTEL
  {IR(43398, 23), 736}, // 39 ArbitraryFloatPowINTEL
  {IR(43445, 24), 738}, // 40 ArbitraryFloatPowNINTEL
  {IR(43421, 24), 737}, // 41 ArbitraryFloatPowRINTEL
  {IR(42809, 25), 712}, // 42 ArbitraryFloatRSqrtINTEL
  {IR(42784, 25), 711}, // 43 ArbitraryFloatRecipINTEL
  {IR(43147, 26), 726}, // 44 ArbitraryFloatSinCosINTEL
  {IR(42470, 28), 698}, // 45 ArbitraryFloatSinCosPiINTEL
  {IR(43101, 23), 724}, // 46 ArbitraryFloatSinINTEL
  {IR(43173, 25), 727}, // 47 ArbitraryFloatSinPiINTEL
  {IR(42883, 24), 715}, // 48 ArbitraryFloatSqrtINTEL
  {IR(42605, 23), 703}, // 49 ArbitraryFloatSubINTEL
  {IR(13476, 19), 786}, // 50 ArithmeticFenceEXT
  {IR(26733, 12), 61}, // 51 ArrayLength
  {IR(37120, 13), 570}, // 52 AsmCallINTEL
  {IR(12240, 9), 569}, // 53 AsmINTEL
  {IR(37105, 15), 568}, // 54 AsmTargetINTEL
  {IR(37161, 14), 573}, // 55 AssumeTrueKHR
  {IR(29005, 10), 220}, // 56 AtomicAnd
  {IR(28857, 22), 210}, // 57 AtomicCompareExchange
  {IR(28879, 26), 211}, // 58 AtomicCompareExchangeWeak
  {IR(28842, 15), 209}, // 59 AtomicExchange
  {IR(44476, 14), 776}, // 60 AtomicFAddEXT
  {IR(37147, 14), 572}, // 61 AtomicFMaxEXT
  {IR(37133, 14), 571}, // 62 AtomicFMinEXT
  {IR(30390, 16), 292}, // 63 AtomicFlagClear
  {IR(30369, 21), 291}, // 64 AtomicFlagTestAndSet
  {IR(28939, 11), 214}, // 65 AtomicIAdd
  {IR(28922, 17), 213}, // 66 AtomicIDecrement
  {IR(28905, 17), 212}, // 67 AtomicIIncrement
  {IR(28950, 11), 215}, // 68 AtomicISub
  {IR(28819, 11), 207}, // 69 AtomicLoad
  {IR(29015, 9), 221}, // 70 AtomicOr
  {IR(28983, 11), 218}, // 71 AtomicSMax
  {IR(28961, 11), 216}, // 72 AtomicSMin
  {IR(28830, 12), 208}, // 73 AtomicStore
  {IR(28994, 11), 219}, // 74 AtomicUMax
  {IR(28972, 11), 217}, // 75 AtomicUMin
  {IR(29024, 10), 222}, // 76 AtomicXor
  {IR(35369, 28), 500}, // 77 BeginInvocationInterlockEXT
  {IR(32916, 17), 407}, // 78 BitCastArrayQCOM
  {IR(28603, 9), 191}, // 79 BitCount
  {IR(28543, 15), 187}, // 80 BitFieldInsert
  {IR(28558, 17), 188}, // 81 BitFieldSExtract
  {IR(28575, 17), 189}, // 82 BitFieldUExtract
  {IR(28592, 11), 190}, // 83 BitReverse
  {IR(27731, 8), 114}, // 84 Bitcast
  {IR(28528, 11), 185}, // 85 BitwiseAnd
  {IR(45081, 21), 799}, // 86 BitwiseFunctionINTEL
  {IR(28507, 10), 183}, // 87 BitwiseOr
  {IR(28517, 11), 184}, // 88 BitwiseXor
  {IR(29134, 7), 227}, // 89 Branch
  {IR(29141, 18), 228}, // 90 BranchConditional
  {IR(30002, 13), 277}, // 91 BuildNDRange
  {IR(25747, 11), 15}, // 92 Capability
  {IR(29960, 26), 275}, // 93 CaptureEventProfilingInfo
  {IR(31466, 23), 344}, // 94 ColorAttachmentReadEXT
  {IR(29552, 15), 255}, // 95 CommitReadPipe
  {IR(29567, 16), 256}, // 96 CommitWritePipe
  {IR(26993, 19), 72}, // 97 CompositeConstruct
  {IR(44606, 33), 781}, // 98 CompositeConstructContinuedINTEL
  {IR(33049, 30), 412}, // 99 CompositeConstructCoopMatQCOM
  {IR(32624, 31), 395}, // 100 CompositeConstructReplicateEXT
  {IR(27012, 17), 73}, // 101 CompositeExtract
  {IR(33079, 28), 413}, // 102 CompositeExtractCoopMatQCOM
  {IR(27029, 16), 74}, // 103 CompositeInsert
  {IR(45155, 27), 803}, // 104 ConditionalCapabilityINTEL
  {IR(45303, 27), 807}, // 105 ConditionalCopyObjectINTEL
  {IR(45128, 27), 802}, // 106 ConditionalEntryPointINTEL
  {IR(45102, 26), 801}, // 107 ConditionalExtensionINTEL
  {IR(15470, 9), 39}, // 108 Constant
  {IR(26253, 18), 40}, // 109 ConstantComposite
  {IR(44538, 32), 779}, // 110 ConstantCompositeContinuedINTEL
  {IR(32560, 30), 393}, // 111 ConstantCompositeReplicateEXT
  {IR(26201, 14), 38}, // 112 ConstantFalse
  {IR(37051, 29), 566}, // 113 ConstantFunctionPointerINTEL
  {IR(26365, 13), 42}, // 114 ConstantNull
  {IR(30445, 20), 296}, // 115 ConstantPipeStorage
  {IR(26349, 16), 41}, // 116 ConstantSampler
  {IR(33515, 19), 432}, // 117 ConstantStringAMDX
  {IR(26188, 13), 37}, // 118 ConstantTrue
  {IR(28790, 15), 205}, // 119 ControlBarrier
  {IR(44679, 26), 784}, // 120 ControlBarrierArriveINTEL
  {IR(44705, 24), 785}, // 121 ControlBarrierWaitINTEL
  {IR(44659, 20), 783}, // 122 ConvertBF16ToFINTEL
  {IR(44639, 20), 782}, // 123 ConvertFToBF16INTEL
  {IR(27537, 12), 100}, // 124 ConvertFToS
  {IR(27525, 12), 99}, // 125 ConvertFToU
  {IR(45523, 26), 819}, // 126 ConvertHandleToImageINTEL
  {IR(45577, 33), 821}, // 127 ConvertHandleToSampledImageINTEL
  {IR(45549, 28), 820}, // 128 ConvertHandleToSamplerINTEL
  {IR(36018, 18), 523}, // 129 ConvertImageToUNV
  {IR(27614, 14), 107}, // 130 ConvertPtrToU
  {IR(27549, 12), 101}, // 131 ConvertSToF
  {IR(36081, 25), 526}, // 132 ConvertSampledImageToUNV
  {IR(36036, 20), 524}, // 133 ConvertSamplerToUNV
  {IR(32138, 35), 379}, // 134 ConvertUToAccelerationStructureKHR
  {IR(27561, 12), 102}, // 135 ConvertUToF
  {IR(35980, 18), 521}, // 136 ConvertUToImageNV
  {IR(27658, 14), 110}, // 137 ConvertUToPtr
  {IR(36056, 25), 525}, // 138 ConvertUToSampledImageNV
  {IR(35998, 20), 522}, // 139 ConvertUToSamplerNV
  {IR(34675, 27), 475}, // 140 CooperativeMatrixConvertNV
  {IR(32533, 27), 392}, // 141 CooperativeMatrixLengthKHR
  {IR(35343, 26), 499}, // 142 CooperativeMatrixLengthNV
  {IR(32401, 25), 389}, // 143 CooperativeMatrixLoadKHR
  {IR(35268, 24), 496}, // 144 CooperativeMatrixLoadNV
  {IR(35567, 30), 503}, // 145 CooperativeMatrixLoadTensorNV
  {IR(32506, 27), 391}, // 146 CooperativeMatrixMulAddKHR
  {IR(35317, 26), 498}, // 147 CooperativeMatrixMulAddNV
  {IR(35628, 32), 505}, // 148 CooperativeMatrixPerElementOpNV
  {IR(35466, 26), 502}, // 149 CooperativeMatrixReduceNV
  {IR(32426, 26), 390}, // 150 CooperativeMatrixStoreKHR
  {IR(35292, 25), 497}, // 151 CooperativeMatrixStoreNV
  {IR(35597, 31), 504}, // 152 CooperativeMatrixStoreTensorNV
  {IR(35951, 29), 520}, // 153 CooperativeMatrixTransposeNV
  {IR(34870, 24), 482}, // 154 CooperativeVectorLoadNV
  {IR(34643, 32), 474}, // 155 CooperativeVectorMatrixMulAddNV
  {IR(34533, 29), 471}, // 156 CooperativeVectorMatrixMulNV
  {IR(34562, 42), 472}, // 157 CooperativeVectorOuterProductAccumulateNV
  {IR(34604, 39), 473}, // 158 CooperativeVectorReduceSumAccumulateNV
  {IR(34894, 25), 483}, // 159 CooperativeVectorStoreNV
  {IR(31425, 12), 340}, // 160 CopyLogical
  {IR(26659, 11), 56}, // 161 CopyMemory
  {IR(26670, 16), 57}, // 162 CopyMemorySized
  {IR(27045, 11), 75}, // 163 CopyObject
  {IR(30465, 26), 297}, // 164 CreatePipeFromPipeStorage
  {IR(35696, 21), 508}, // 165 CreateTensorLayoutNV
  {IR(35816, 19), 513}, // 166 CreateTensorViewNV
  {IR(29912, 16), 272}, // 167 CreateUserEvent
  {IR(43751, 29), 755}, // 168 CrossWorkgroupCastToPtrINTEL
  {IR(28612, 5), 192}, // 169 DPdx
  {IR(28658, 11), 198}, // 170 DPdxCoarse
  {IR(28629, 9), 195}, // 171 DPdxFine
  {IR(28617, 5), 193}, // 172 DPdy
  {IR(28669, 11), 199}, // 173 DPdyCoarse
  {IR(28638, 9), 196}, // 174 DPdyFine
  {IR(26819, 9), 64}, // 175 Decorate
  {IR(30642, 11), 305}, // 176 DecorateId
  {IR(37185, 15), 575}, // 177 DecorateString
  {IR(37200, 21), 575}, // 178 DecorateStringGOOGLE
  {IR(26843, 16), 66}, // 179 DecorationGroup
  {IR(11574, 25), 516}, // 180 DemoteToHelperInvocation
  {IR(11599, 28), 516}, // 181 DemoteToHelperInvocationEXT
  {IR(31489, 23), 345}, // 182 DepthAttachmentReadEXT
  {IR(27928, 4), 137}, // 183 Dot
  {IR(34702, 17), 476}, // 184 EmitMeshTasksEXT
  {IR(28717, 17), 203}, // 185 EmitStreamVertex
  {IR(28693, 11), 201}, // 186 EmitVertex
  {IR(35397, 26), 501}, // 187 EndInvocationInterlockEXT
  {IR(28704, 13), 202}, // 188 EndPrimitive
  {IR(28734, 19), 204}, // 189 EndStreamPrimitive
  {IR(29748, 14), 265}, // 190 EnqueueKernel
  {IR(29734, 14), 264}, // 191 EnqueueMarker
  {IR(33387, 24), 427}, // 192 EnqueueNodePayloadsAMDX
  {IR(25662, 11), 13}, // 193 EntryPoint
  {IR(32119, 19), 378}, // 194 ExecuteCallableKHR
  {IR(35144, 18), 492}, // 195 ExecuteCallableNV
  {IR(25705, 14), 14}, // 196 ExecutionMode
  {IR(30626, 16), 304}, // 197 ExecutionModeId
  {IR(37175, 10), 574}, // 198 ExpectKHR
  {IR(25516, 8), 11}, // 199 ExtInst
  {IR(25456, 14), 10}, // 200 ExtInstImport
  {IR(32056, 26), 375}, // 201 ExtInstWithForwardRefsKHR
  {IR(25446, 10), 9}, // 202 Extension
  {IR(33107, 20), 414}, // 203 ExtractSubArrayQCOM
  {IR(27760, 5), 118}, // 204 FAdd
  {IR(27591, 9), 105}, // 205 FConvert
  {IR(27795, 5), 125}, // 206 FDiv
  {IR(27820, 5), 130}, // 207 FMod
  {IR(27780, 5), 122}, // 208 FMul
  {IR(27747, 8), 116}, // 209 FNegate
  {IR(28257, 10), 168}, // 210 FOrdEqual
  {IR(28335, 16), 174}, // 211 FOrdGreaterThan
  {IR(28407, 21), 178}, // 212 FOrdGreaterThanEqual
  {IR(28307, 13), 172}, // 213 FOrdLessThan
  {IR(28369, 18), 176}, // 214 FOrdLessThanEqual
  {IR(28279, 13), 170}, // 215 FOrdNotEqual
  {IR(13037, 13), 758}, // 216 FPGARegINTEL
  {IR(27815, 5), 129}, // 217 FRem
  {IR(27770, 5), 120}, // 218 FSub
  {IR(28267, 12), 169}, // 219 FUnordEqual
  {IR(28351, 18), 175}, // 220 FUnordGreaterThan
  {IR(28428, 23), 179}, // 221 FUnordGreaterThanEqual
  {IR(28320, 15), 173}, // 222 FUnordLessThan
  {IR(28387, 20), 177}, // 223 FUnordLessThanEqual
  {IR(28292, 15), 171}, // 224 FUnordNotEqual
  {IR(34832, 38), 481}, // 225 FetchMicroTriangleVertexBarycentricNV
  {IR(34797, 35), 480}, // 226 FetchMicroTriangleVertexPositionNV
  {IR(33436, 29), 429}, // 227 FinishWritingNodePayloadAMDX
  {IR(43612, 14), 747}, // 228 FixedCosINTEL
  {IR(43659, 16), 750}, // 229 FixedCosPiINTEL
  {IR(43708, 14), 753}, // 230 FixedExpINTEL
  {IR(43694, 14), 752}, // 231 FixedLogINTEL
  {IR(43566, 16), 744}, // 232 FixedRecipINTEL
  {IR(43582, 16), 745}, // 233 FixedRsqrtINTEL
  {IR(43626, 17), 748}, // 234 FixedSinCosINTEL
  {IR(43675, 19), 751}, // 235 FixedSinCosPiINTEL
  {IR(43598, 14), 746}, // 236 FixedSinINTEL
  {IR(43643, 16), 749}, // 237 FixedSinPiINTEL
  {IR(43551, 15), 743}, // 238 FixedSqrtINTEL
  {IR(31973, 7), 369}, // 239 FmaKHR
  {IR(33332, 17), 424}, // 240 FragmentFetchAMD
  {IR(33311, 21), 423}, // 241 FragmentMaskFetchAMD
  {IR(24566, 9), 48}, // 242 Function
  {IR(26568, 13), 51}, // 243 FunctionCall
  {IR(26556, 12), 50}, // 244 FunctionEnd
  {IR(26538, 18), 49}, // 245 FunctionParameter
  {IR(37080, 25), 567}, // 246 FunctionPointerCallINTEL
  {IR(28622, 7), 194}, // 247 Fwidth
  {IR(28680, 13), 200}, // 248 FwidthCoarse
  {IR(28647, 11), 197}, // 249 FwidthFine
  {IR(27689, 17), 112}, // 250 GenericCastToPtr
  {IR(27706, 25), 113}, // 251 GenericCastToPtrExplicit
  {IR(26745, 23), 62}, // 252 GenericPtrMemSemantics
  {IR(29986, 16), 276}, // 253 GetDefaultQueue
  {IR(30491, 35), 298}, // 254 GetKernelLocalSizeForSubgroupCount
  {IR(30526, 25), 299}, // 255 GetKernelMaxNumSubgroups
  {IR(29792, 32), 267}, // 256 GetKernelNDrangeMaxSubGroupSize
  {IR(29762, 30), 266}, // 257 GetKernelNDrangeSubGroupCount
  {IR(29847, 40), 269}, // 258 GetKernelPreferredWorkGroupSizeMultiple
  {IR(29824, 23), 268}, // 259 GetKernelWorkGroupSize
  {IR(29618, 18), 259}, // 260 GetMaxPipePackets
  {IR(29600, 18), 258}, // 261 GetNumPipePackets
  {IR(9043, 9), 353}, // 262 GraphARM
  {IR(31641, 17), 351}, // 263 GraphConstantARM
  {IR(31709, 12), 356}, // 264 GraphEndARM
  {IR(31658, 19), 352}, // 265 GraphEntryPointARM
  {IR(31677, 14), 354}, // 266 GraphInputARM
  {IR(31691, 18), 355}, // 267 GraphSetOutputARM
  {IR(29305, 9), 238}, // 268 GroupAll
  {IR(29314, 9), 239}, // 269 GroupAny
  {IR(29274, 15), 236}, // 270 GroupAsyncCopy
  {IR(45356, 19), 810}, // 271 GroupBitwiseAndKHR
  {IR(45375, 18), 811}, // 272 GroupBitwiseOrKHR
  {IR(45393, 19), 812}, // 273 GroupBitwiseXorKHR
  {IR(29323, 15), 240}, // 274 GroupBroadcast
  {IR(29693, 20), 262}, // 275 GroupCommitReadPipe
  {IR(29713, 21), 263}, // 276 GroupCommitWritePipe
  {IR(26859, 14), 67}, // 277 GroupDecorate
  {IR(29381, 10), 242}, // 278 GroupFAdd
  {IR(33150, 23), 416}, // 279 GroupFAddNonUniformAMD
  {IR(29421, 10), 246}, // 280 GroupFMax
  {IR(33242, 23), 420}, // 281 GroupFMaxNonUniformAMD
  {IR(29391, 10), 243}, // 282 GroupFMin
  {IR(33173, 23), 417}, // 283 GroupFMinNonUniformAMD
  {IR(45343, 13), 809}, // 284 GroupFMulKHR
  {IR(29371, 10), 241}, // 285 GroupIAdd
  {IR(33127, 23), 415}, // 286 GroupIAddNonUniformAMD
  {IR(45330, 13), 808}, // 287 GroupIMulKHR
  {IR(45412, 19), 813}, // 288 GroupLogicalAndKHR
  {IR(45431, 18), 814}, // 289 GroupLogicalOrKHR
  {IR(45449, 19), 815}, // 290 GroupLogicalXorKHR
  {IR(26918, 20), 68}, // 291 GroupMemberDecorate
  {IR(30674, 19), 307}, // 292 GroupNonUniformAll
  {IR(30712, 24), 309}, // 293 GroupNonUniformAllEqual
  {IR(30693, 19), 308}, // 294 GroupNonUniformAny
  {IR(5662, 22), 312}, // 295 GroupNonUniformBallot
  {IR(30852, 30), 315}, // 296 GroupNonUniformBallotBitCount
  {IR(30820, 32), 314}, // 297 GroupNonUniformBallotBitExtract
  {IR(30882, 29), 316}, // 298 GroupNonUniformBallotFindLSB
  {IR(30911, 29), 317}, // 299 GroupNonUniformBallotFindMSB
  {IR(31218, 26), 332}, // 300 GroupNonUniformBitwiseAnd
  {IR(31244, 25), 333}, // 301 GroupNonUniformBitwiseOr
  {IR(31269, 26), 334}, // 302 GroupNonUniformBitwiseXor
  {IR(30736, 25), 310}, // 303 GroupNonUniformBroadcast
  {IR(30761, 30), 311}, // 304 GroupNonUniformBroadcastFirst
  {IR(30653, 21), 306}, // 305 GroupNonUniformElect
  {IR(31038, 20), 323}, // 306 GroupNonUniformFAdd
  {IR(31198, 20), 331}, // 307 GroupNonUniformFMax
  {IR(31138, 20), 328}, // 308 GroupNonUniformFMin
  {IR(31078, 20), 325}, // 309 GroupNonUniformFMul
  {IR(31018, 20), 322}, // 310 GroupNonUniformIAdd
  {IR(31058, 20), 324}, // 311 GroupNonUniformIMul
  {IR(30791, 29), 313}, // 312 GroupNonUniformInverseBallot
  {IR(31295, 26), 335}, // 313 GroupNonUniformLogicalAnd
  {IR(31321, 25), 336}, // 314 GroupNonUniformLogicalOr
  {IR(31346, 26), 337}, // 315 GroupNonUniformLogicalXor
  {IR(34737, 27), 478}, // 316 GroupNonUniformPartitionNV
  {IR(33557, 26), 434}, // 317 GroupNonUniformQuadAllKHR
  {IR(33583, 26), 435}, // 318 GroupNonUniformQuadAnyKHR
  {IR(31372, 29), 338}, // 319 GroupNonUniformQuadBroadcast
  {IR(31401, 24), 339}, // 320 GroupNonUniformQuadSwap
  {IR(13262, 25), 373}, // 321 GroupNonUniformRotateKHR
  {IR(31158, 20), 329}, // 322 GroupNonUniformSMax
  {IR(31098, 20), 326}, // 323 GroupNonUniformSMin
  {IR(8752, 23), 318}, // 324 GroupNonUniformShuffle
  {IR(30991, 27), 321}, // 325 GroupNonUniformShuffleDown
  {IR(30966, 25), 320}, // 326 GroupNonUniformShuffleUp
  {IR(30940, 26), 319}, // 327 GroupNonUniformShuffleXor
  {IR(31178, 20), 330}, // 328 GroupNonUniformUMax
  {IR(31118, 20), 327}, // 329 GroupNonUniformUMin
  {IR(29636, 28), 260}, // 330 GroupReserveReadPipePackets
  {IR(29664, 29), 261}, // 331 GroupReserveWritePipePackets
  {IR(29441, 10), 248}, // 332 GroupSMax
  {IR(33288, 23), 422}, // 333 GroupSMaxNonUniformAMD
  {IR(29411, 10), 245}, // 334 GroupSMin
  {IR(33219, 23), 419}, // 335 GroupSMinNonUniformAMD
  {IR(29431, 10), 247}, // 336 GroupUMax
  {IR(33265, 23), 421}, // 337 GroupUMaxNonUniformAMD
  {IR(29401, 10), 244}, // 338 GroupUMin
  {IR(33196, 23), 418}, // 339 GroupUMinNonUniformAMD
  {IR(29289, 16), 237}, // 340 GroupWaitEvents
  {IR(34044, 25), 451}, // 341 HitObjectExecuteShaderNV
  {IR(34095, 25), 453}, // 342 HitObjectGetAttributesNV
  {IR(35220, 24), 494}, // 343 HitObjectGetClusterIdNV
  {IR(34069, 26), 452}, // 344 HitObjectGetCurrentTimeNV
  {IR(34171, 28), 456}, // 345 HitObjectGetGeometryIndexNV
  {IR(34120, 22), 454}, // 346 HitObjectGetHitKindNV
  {IR(34224, 34), 458}, // 347 HitObjectGetInstanceCustomIndexNV
  {IR(34199, 25), 457}, // 348 HitObjectGetInstanceIdNV
  {IR(36447, 27), 536}, // 349 HitObjectGetLSSPositionsNV
  {IR(36474, 23), 537}, // 350 HitObjectGetLSSRadiiNV
  {IR(33756, 33), 441}, // 351 HitObjectGetObjectRayDirectionNV
  {IR(33789, 30), 442}, // 352 HitObjectGetObjectRayOriginNV
  {IR(33728, 28), 440}, // 353 HitObjectGetObjectToWorldNV
  {IR(34142, 29), 455}, // 354 HitObjectGetPrimitiveIndexNV
  {IR(34319, 22), 461}, // 355 HitObjectGetRayTMaxNV
  {IR(34341, 22), 462}, // 356 HitObjectGetRayTMinNV
  {IR(33884, 44), 445}, // 357 HitObjectGetShaderBindingTableRecordIndexNV
  {IR(33845, 39), 444}, // 358 HitObjectGetShaderRecordBufferHandleNV
  {IR(36391, 29), 534}, // 359 HitObjectGetSpherePositionNV
  {IR(36420, 27), 535}, // 360 HitObjectGetSphereRadiusNV
  {IR(34258, 32), 459}, // 361 HitObjectGetWorldRayDirectionNV
  {IR(34290, 29), 460}, // 362 HitObjectGetWorldRayOriginNV
  {IR(33700, 28), 439}, // 363 HitObjectGetWorldToObjectNV
  {IR(34363, 19), 463}, // 364 HitObjectIsEmptyNV
  {IR(34382, 17), 464}, // 365 HitObjectIsHitNV
  {IR(36520, 20), 539}, // 366 HitObjectIsLSSHitNV
  {IR(34399, 18), 465}, // 367 HitObjectIsMissNV
  {IR(36497, 23), 538}, // 368 HitObjectIsSphereHitNV
  {IR(33928, 23), 446}, // 369 HitObjectRecordEmptyNV
  {IR(33609, 27), 436}, // 370 HitObjectRecordHitMotionNV
  {IR(33971, 21), 448}, // 371 HitObjectRecordHitNV
  {IR(33636, 36), 437}, // 372 HitObjectRecordHitWithIndexMotionNV
  {IR(33992, 30), 449}, // 373 HitObjectRecordHitWithIndexNV
  {IR(33672, 28), 438}, // 374 HitObjectRecordMissMotionNV
  {IR(34022, 22), 450}, // 375 HitObjectRecordMissNV
  {IR(33819, 26), 443}, // 376 HitObjectTraceRayMotionNV
  {IR(33951, 20), 447}, // 377 HitObjectTraceRayNV
  {IR(27755, 5), 117}, // 378 IAdd
  {IR(27932, 10), 138}, // 379 IAddCarry
  {IR(36899, 13), 556}, // 380 IAddSatINTEL
  {IR(36925, 14), 558}, // 381 IAverageINTEL
  {IR(36953, 21), 560}, // 382 IAverageRoundedINTEL
  {IR(28128, 7), 158}, // 383 IEqual
  {IR(27775, 5), 121}, // 384 IMul
  {IR(37021, 15), 564}, // 385 IMul32x16INTEL
  {IR(28135, 10), 159}, // 386 INotEqual
  {IR(27765, 5), 119}, // 387 ISub
  {IR(27942, 11), 139}, // 388 ISubBorrow
  {IR(36995, 13), 562}, // 389 ISubSatINTEL
  {IR(32173, 22), 380}, // 390 IgnoreIntersectionKHR
  {IR(34962, 21), 485}, // 391 IgnoreIntersectionNV
  {IR(24610, 6), 91}, // 392 Image
  {IR(33020, 29), 411}, // 393 ImageBlockMatchGatherSADQCOM
  {IR(32991, 29), 410}, // 394 ImageBlockMatchGatherSSDQCOM
  {IR(32893, 23), 406}, // 395 ImageBlockMatchSADQCOM
  {IR(32870, 23), 405}, // 396 ImageBlockMatchSSDQCOM
  {IR(32962, 29), 409}, // 397 ImageBlockMatchWindowSADQCOM
  {IR(32933, 29), 408}, // 398 ImageBlockMatchWindowSSDQCOM
  {IR(32851, 19), 404}, // 399 ImageBoxFilterQCOM
  {IR(27373, 16), 88}, // 400 ImageDrefGather
  {IR(27350, 11), 86}, // 401 ImageFetch
  {IR(27361, 12), 87}, // 402 ImageGather
  {IR(27410, 17), 92}, // 403 ImageQueryFormat
  {IR(27490, 17), 97}, // 404 ImageQueryLevels
  {IR(27476, 14), 96}, // 405 ImageQueryLod
  {IR(27427, 16), 93}, // 406 ImageQueryOrder
  {IR(27507, 18), 98}, // 407 ImageQuerySamples
  {IR(27461, 15), 95}, // 408 ImageQuerySize
  {IR(27443, 18), 94}, // 409 ImageQuerySizeLod
  {IR(27389, 10), 89}, // 410 ImageRead
  {IR(27207, 27), 81}, // 411 ImageSampleDrefExplicitLod
  {IR(27180, 27), 80}, // 412 ImageSampleDrefImplicitLod
  {IR(27157, 23), 79}, // 413 ImageSampleExplicitLod
  {IR(34486, 23), 469}, // 414 ImageSampleFootprintNV
  {IR(27111, 23), 78}, // 415 ImageSampleImplicitLod
  {IR(27319, 31), 85}, // 416 ImageSampleProjDrefExplicitLod
  {IR(27288, 31), 84}, // 417 ImageSampleProjDrefImplicitLod
  {IR(27261, 27), 83}, // 418 ImageSampleProjExplicitLod
  {IR(27234, 27), 82}, // 419 ImageSampleProjImplicitLod
  {IR(32827, 24), 403}, // 420 ImageSampleWeightedQCOM
  {IR(30314, 22), 288}, // 421 ImageSparseDrefGather
  {IR(30279, 17), 286}, // 422 ImageSparseFetch
  {IR(30296, 18), 287}, // 423 ImageSparseGather
  {IR(30406, 16), 293}, // 424 ImageSparseRead
  {IR(30106, 33), 281}, // 425 ImageSparseSampleDrefExplicitLod
  {IR(30073, 33), 280}, // 426 ImageSparseSampleDrefImplicitLod
  {IR(30044, 29), 279}, // 427 ImageSparseSampleExplicitLod
  {IR(30015, 29), 278}, // 428 ImageSparseSampleImplicitLod
  {IR(30242, 37), 285}, // 429 ImageSparseSampleProjDrefExplicitLod
  {IR(30205, 37), 284}, // 430 ImageSparseSampleProjDrefImplicitLod
  {IR(30172, 33), 283}, // 431 ImageSparseSampleProjExplicitLod
  {IR(30139, 33), 282}, // 432 ImageSparseSampleProjImplicitLod
  {IR(30336, 26), 289}, // 433 ImageSparseTexelsResident
  {IR(26590, 18), 53}, // 434 ImageTexelPointer
  {IR(27399, 11), 90}, // 435 ImageWrite
  {IR(26698, 20), 59}, // 436 InBoundsAccessChain
  {IR(26768, 23), 63}, // 437 InBoundsPtrAccessChain
  {IR(27999, 9), 146}, // 438 IsFinite
  {IR(35882, 22), 517}, // 439 IsHelperInvocationEXT
  {IR(27993, 6), 145}, // 440 IsInf
  {IR(27987, 6), 144}, // 441 IsNan
  {IR(33492, 23), 431}, // 442 IsNodePayloadValidAMDX
  {IR(28008, 9), 147}, // 443 IsNormal
  {IR(29928, 13), 273}, // 444 IsValidEvent
  {IR(29583, 17), 257}, // 445 IsValidReserveId
  {IR(29211, 5), 230}, // 446 Kill
  {IR(29128, 6), 226}, // 447 Label
  {IR(28028, 14), 149}, // 448 LessOrGreater
  {IR(29247, 14), 234}, // 449 LifetimeStart
  {IR(29261, 13), 235}, // 450 LifetimeStop
  {IR(25441, 5), 8}, // 451 Line
  {IR(26648, 5), 54}, // 452 Load
  {IR(28099, 11), 155}, // 453 LogicalAnd
  {IR(28060, 13), 152}, // 454 LogicalEqual
  {IR(28110, 11), 156}, // 455 LogicalNot
  {IR(28073, 16), 153}, // 456 LogicalNotEqual
  {IR(28089, 10), 154}, // 457 LogicalOr
  {IR(43469, 17), 739}, // 458 LoopControlINTEL
  {IR(29068, 10), 224}, // 459 LoopMerge
  {IR(45486, 18), 817}, // 460 MaskedGatherINTEL
  {IR(45504, 19), 818}, // 461 MaskedScatterINTEL
  {IR(27897, 18), 135}, // 462 MatrixTimesMatrix
  {IR(27843, 18), 132}, // 463 MatrixTimesScalar
  {IR(27879, 18), 134}, // 464 MatrixTimesVector
  {IR(26828, 15), 65}, // 465 MemberDecorate
  {IR(37221, 21), 576}, // 466 MemberDecorateString
  {IR(37242, 27), 576}, // 467 MemberDecorateStringGOOGLE
  {IR(25423, 11), 6}, // 468 MemberName
  {IR(28805, 14), 206}, // 469 MemoryBarrier
  {IR(25588, 12), 12}, // 470 MemoryModel
  {IR(30591, 19), 302}, // 471 MemoryNamedBarrier
  {IR(30610, 16), 303}, // 472 ModuleProcessed
  {IR(25418, 5), 5}, // 473 Name
  {IR(30568, 23), 301}, // 474 NamedBarrierInitialize
  {IR(30362, 7), 290}, // 475 NoLine
  {IR(33465, 27), 430}, // 476 NodePayloadArrayLengthAMDX
  {IR(25214, 4), 0}, // 477 Nop
  {IR(28539, 4), 186}, // 478 Not
  {IR(28042, 8), 150}, // 479 Ordered
  {IR(27915, 13), 136}, // 480 OuterProduct
  {IR(29034, 4), 223}, // 481 Phi
  {IR(26718, 15), 60}, // 482 PtrAccessChain
  {IR(43722, 29), 754}, // 483 PtrCastToCrossWorkgroupINTEL
  {IR(27672, 17), 111}, // 484 PtrCastToGeneric
  {IR(31458, 8), 343}, // 485 PtrDiff
  {IR(31437, 9), 341}, // 486 PtrEqual
  {IR(31446, 12), 342}, // 487 PtrNotEqual
  {IR(27600, 14), 106}, // 488 QuantizeToF16
  {IR(36187, 17), 528}, // 489 RawAccessChainNV
  {IR(32746, 31), 400}, // 490 RayQueryConfirmIntersectionKHR
  {IR(32714, 32), 399}, // 491 RayQueryGenerateIntersectionKHR
  {IR(35197, 23), 493}, // 492 RayQueryGetClusterIdNV
  {IR(44127, 39), 767}, // 493 RayQueryGetIntersectionBarycentricsKHR
  {IR(44202, 46), 769}, // 494 RayQueryGetIntersectionCandidateAABBOpaqueKHR
  {IR(35162, 35), 493}, // 495 RayQueryGetIntersectionClusterIdNV
  {IR(44166, 36), 768}, // 496 RayQueryGetIntersectionFrontFaceKHR
  {IR(44046, 40), 765}, // 497 RayQueryGetIntersectionGeometryIndexKHR
  {IR(43898, 46), 762}, // 498 RayQueryGetIntersectionInstanceCustomIndexKHR
  {IR(43944, 37), 763}, // 499 RayQueryGetIntersectionInstanceIdKHR
  {IR(43981, 65), 764}, // 500 RayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR
  {IR(36354, 37), 533}, // 501 RayQueryGetIntersectionLSSHitValueNV
  {IR(36282, 38), 531}, // 502 RayQueryGetIntersectionLSSPositionsNV
  {IR(36320, 34), 532}, // 503 RayQueryGetIntersectionLSSRadiiNV
  {IR(44248, 45), 770}, // 504 RayQueryGetIntersectionObjectRayDirectionKHR
  {IR(44293, 42), 771}, // 505 RayQueryGetIntersectionObjectRayOriginKHR
  {IR(44396, 40), 774}, // 506 RayQueryGetIntersectionObjectToWorldKHR
  {IR(44086, 41), 766}, // 507 RayQueryGetIntersectionPrimitiveIndexKHR
  {IR(36204, 40), 529}, // 508 RayQueryGetIntersectionSpherePositionNV
  {IR(36244, 38), 530}, // 509 RayQueryGetIntersectionSphereRadiusNV
  {IR(43870, 28), 761}, // 510 RayQueryGetIntersectionTKHR
  {IR(35037, 50), 490}, // 511 RayQueryGetIntersectionTriangleVertexPositionsKHR
  {IR(32796, 31), 402}, // 512 RayQueryGetIntersectionTypeKHR
  {IR(44436, 40), 775}, // 513 RayQueryGetIntersectionWorldToObjectKHR
  {IR(43847, 23), 760}, // 514 RayQueryGetRayFlagsKHR
  {IR(43825, 22), 759}, // 515 RayQueryGetRayTMinKHR
  {IR(44335, 32), 772}, // 516 RayQueryGetWorldRayDirectionKHR
  {IR(44367, 29), 773}, // 517 RayQueryGetWorldRayOriginKHR
  {IR(32671, 22), 397}, // 518 RayQueryInitializeKHR
  {IR(36562, 19), 541}, // 519 RayQueryIsLSSHitNV
  {IR(36540, 22), 540}, // 520 RayQueryIsSphereHitNV
  {IR(32777, 19), 401}, // 521 RayQueryProceedKHR
  {IR(32693, 21), 398}, // 522 RayQueryTerminateKHR
  {IR(33349, 13), 425}, // 523 ReadClockKHR
  {IR(29451, 9), 249}, // 524 ReadPipe
  {IR(43780, 22), 756}, // 525 ReadPipeBlockingINTEL
  {IR(29899, 13), 271}, // 526 ReleaseEvent
  {IR(34446, 24), 467}, // 527 ReorderThreadWithHintNV
  {IR(34417, 29), 466}, // 528 ReorderThreadWithHitObjectNV
  {IR(34919, 22), 484}, // 529 ReportIntersectionKHR
  {IR(34941, 21), 484}, // 530 ReportIntersectionNV
  {IR(29505, 23), 253}, // 531 ReserveReadPipePackets
  {IR(29528, 24), 254}, // 532 ReserveWritePipePackets
  {IR(29470, 17), 251}, // 533 ReservedReadPipe
  {IR(29487, 18), 252}, // 534 ReservedWritePipe
  {IR(42451, 19), 697}, // 535 RestoreMemoryINTEL
  {IR(29887, 12), 270}, // 536 RetainEvent
  {IR(29216, 7), 231}, // 537 Return
  {IR(29223, 12), 232}, // 538 ReturnValue
  {IR(45468, 18), 816}, // 539 RoundFToTF32INTEL
  {IR(27582, 9), 104}, // 540 SConvert
  {IR(27790, 5), 124}, // 541 SDiv
  {IR(32258, 5), 382}, // 542 SDot
  {IR(32299, 11), 385}, // 543 SDotAccSat
  {IR(32310, 14), 385}, // 544 SDotAccSatKHR
  {IR(32263, 8), 382}, // 545 SDotKHR
  {IR(28158, 13), 161}, // 546 SGreaterThan
  {IR(28189, 18), 163}, // 547 SGreaterThanEqual
  {IR(28217, 10), 165}, // 548 SLessThan
  {IR(28242, 15), 167}, // 549 SLessThanEqual
  {IR(27810, 5), 128}, // 550 SMod
  {IR(27966, 13), 141}, // 551 SMulExtended
  {IR(27739, 8), 115}, // 552 SNegate
  {IR(27805, 5), 127}, // 553 SRem
  {IR(32284, 6), 384}, // 554 SUDot
  {IR(32349, 12), 387}, // 555 SUDotAccSat
  {IR(32361, 15), 387}, // 556 SUDotAccSatKHR
  {IR(32290, 9), 384}, // 557 SUDotKHR
  {IR(27066, 13), 77}, // 558 SampledImage
  {IR(36106, 29), 527}, // 559 SamplerImageAddressingModeNV
  {IR(27628, 15), 108}, // 560 SatConvertSToU
  {IR(27643, 15), 109}, // 561 SatConvertUToS
  {IR(42435, 16), 696}, // 562 SaveMemoryINTEL
  {IR(28121, 7), 157}, // 563 Select
  {IR(29113, 15), 225}, // 564 SelectionMerge
  {IR(34719, 18), 477}, // 565 SetMeshOutputsEXT
  {IR(29941, 19), 274}, // 566 SetUserEventStatus
  {IR(28490, 17), 182}, // 567 ShiftLeftLogical
  {IR(28469, 21), 181}, // 568 ShiftRightArithmetic
  {IR(28451, 18), 180}, // 569 ShiftRightLogical
  {IR(28017, 11), 148}, // 570 SignBitSet
  {IR(30422, 7), 294}, // 571 SizeOf
  {IR(25395, 7), 3}, // 572 Source
  {IR(25276, 16), 2}, // 573 SourceContinued
  {IR(25402, 16), 4}, // 574 SourceExtension
  {IR(26413, 13), 45}, // 575 SpecConstant
  {IR(45206, 30), 805}, // 576 SpecConstantArchitectureINTEL
  {IR(45273, 30), 806}, // 577 SpecConstantCapabilitiesINTEL
  {IR(26426, 22), 46}, // 578 SpecConstantComposite
  {IR(44570, 36), 780}, // 579 SpecConstantCompositeContinuedINTEL
  {IR(32590, 34), 394}, // 580 SpecConstantCompositeReplicateEXT
  {IR(26395, 18), 44}, // 581 SpecConstantFalse
  {IR(26489, 15), 47}, // 582 SpecConstantOp
  {IR(33534, 23), 433}, // 583 SpecConstantStringAMDX
  {IR(45182, 24), 804}, // 584 SpecConstantTargetINTEL
  {IR(26378, 17), 43}, // 585 SpecConstantTrue
  {IR(31512, 25), 346}, // 586 StencilAttachmentReadEXT
  {IR(26653, 6), 55}, // 587 Store
  {IR(25434, 7), 7}, // 588 String
  {IR(44871, 25), 793}, // 589 Subgroup2DBlockLoadINTEL
  {IR(44896, 34), 794}, // 590 Subgroup2DBlockLoadTransformINTEL
  {IR(44930, 34), 795}, // 591 Subgroup2DBlockLoadTransposeINTEL
  {IR(44964, 29), 796}, // 592 Subgroup2DBlockPrefetchINTEL
  {IR(44993, 26), 797}, // 593 Subgroup2DBlockStoreINTEL
  {IR(32010, 20), 372}, // 594 SubgroupAllEqualKHR
  {IR(31980, 15), 370}, // 595 SubgroupAllKHR
  {IR(31995, 15), 371}, // 596 SubgroupAnyKHR
  {IR(40953, 30), 660}, // 597 SubgroupAvcBmeInitializeINTEL
  {IR(40923, 30), 659}, // 598 SubgroupAvcFmeInitializeINTEL
  {IR(39358, 35), 629}, // 599 SubgroupAvcImeAdjustRefOffsetINTEL
  {IR(39393, 39), 630}, // 600 SubgroupAvcImeConvertToMcePayloadINTEL
  {IR(40034, 38), 643}, // 601 SubgroupAvcImeConvertToMceResultINTEL
  {IR(39657, 45), 636}, // 602 SubgroupAvcImeEvaluateWithDualReferenceINTEL
  {IR(39757, 53), 638}, // 603 SubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL
  {IR(39978, 56), 642}, // 604 SubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL
  {IR(39866, 54), 640}, // 605 SubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL
  {IR(39610, 47), 635}, // 606 SubgroupAvcImeEvaluateWithSingleReferenceINTEL
  {IR(39702, 55), 637}, // 607 SubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL
  {IR(39920, 58), 641}, // 608 SubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL
  {IR(39810, 56), 639}, // 609 SubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL
  {IR(40666, 36), 654}, // 610 SubgroupAvcImeGetBorderReachedINTEL
  {IR(40118, 44), 645}, // 611 SubgroupAvcImeGetDualReferenceStreaminINTEL
  {IR(40072, 46), 644}, // 612 SubgroupAvcImeGetSingleReferenceStreaminINTEL
  {IR(40533, 66), 652}, // 613 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL
  {IR(40465, 68), 651}, // 614 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL
  {IR(40599, 67), 653}, // 615 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL
  {IR(40328, 68), 649}, // 616 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL
  {IR(40258, 70), 648}, // 617 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL
  {IR(40396, 69), 650}, // 618 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL
  {IR(40702, 48), 655}, // 619 SubgroupAvcImeGetTruncatedSearchIndicationINTEL
  {IR(40750, 59), 656}, // 620 SubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL
  {IR(40867, 56), 658}, // 621 SubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL
  {IR(40809, 58), 657}, // 622 SubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL
  {IR(39221, 30), 625}, // 623 SubgroupAvcImeInitializeINTEL
  {IR(39325, 33), 628}, // 624 SubgroupAvcImeRefWindowSizeINTEL
  {IR(39289, 36), 627}, // 625 SubgroupAvcImeSetDualReferenceINTEL
  {IR(39522, 54), 633}, // 626 SubgroupAvcImeSetEarlySearchTerminationThresholdINTEL
  {IR(39432, 43), 631}, // 627 SubgroupAvcImeSetMaxMotionVectorCountINTEL
  {IR(39251, 38), 626}, // 628 SubgroupAvcImeSetSingleReferenceINTEL
  {IR(39475, 47), 632}, // 629 SubgroupAvcImeSetUnidirectionalMixDisableINTEL
  {IR(39576, 34), 634}, // 630 SubgroupAvcImeSetWeightedSadINTEL
  {IR(40211, 47), 647}, // 631 SubgroupAvcImeStripDualReferenceStreamoutINTEL
  {IR(40162, 49), 646}, // 632 SubgroupAvcImeStripSingleReferenceStreamoutINTEL
  {IR(38611, 39), 610}, // 633 SubgroupAvcMceConvertToImePayloadINTEL
  {IR(38650, 38), 611}, // 634 SubgroupAvcMceConvertToImeResultINTEL
  {IR(38688, 39), 612}, // 635 SubgroupAvcMceConvertToRefPayloadINTEL
  {IR(38727, 38), 613}, // 636 SubgroupAvcMceConvertToRefResultINTEL
  {IR(38765, 39), 614}, // 637 SubgroupAvcMceConvertToSicPayloadINTEL
  {IR(38804, 38), 615}, // 638 SubgroupAvcMceConvertToSicResultINTEL
  {IR(38917, 43), 618}, // 639 SubgroupAvcMceGetBestInterDistortionsINTEL
  {IR(38049, 50), 599}, // 640 SubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL
  {IR(37647, 60), 591}, // 641 SubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL
  {IR(37847, 51), 595}, // 642 SubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL
  {IR(37993, 56), 598}, // 643 SubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL
  {IR(37760, 47), 593}, // 644 SubgroupAvcMceGetDefaultInterShapePenaltyINTEL
  {IR(38348, 56), 605}, // 645 SubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL
  {IR(38247, 50), 603}, // 646 SubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL
  {IR(37942, 51), 597}, // 647 SubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL
  {IR(38151, 49), 601}, // 648 SubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL
  {IR(38099, 52), 600}, // 649 SubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL
  {IR(38297, 51), 604}, // 650 SubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL
  {IR(39036, 38), 621}, // 651 SubgroupAvcMceGetInterDirectionsINTEL
  {IR(38878, 39), 617}, // 652 SubgroupAvcMceGetInterDistortionsINTEL
  {IR(38960, 38), 619}, // 653 SubgroupAvcMceGetInterMajorShapeINTEL
  {IR(38998, 38), 620}, // 654 SubgroupAvcMceGetInterMinorShapeINTEL
  {IR(39074, 45), 622}, // 655 SubgroupAvcMceGetInterMotionVectorCountINTEL
  {IR(39119, 40), 623}, // 656 SubgroupAvcMceGetInterReferenceIdsINTEL
  {IR(39159, 62), 624}, // 657 SubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL
  {IR(38842, 36), 616}, // 658 SubgroupAvcMceGetMotionVectorsINTEL
  {IR(38404, 33), 606}, // 659 SubgroupAvcMceSetAcOnlyHaarINTEL
  {IR(38550, 61), 609}, // 660 SubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL
  {IR(37707, 53), 592}, // 661 SubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL
  {IR(37898, 44), 596}, // 662 SubgroupAvcMceSetInterDirectionPenaltyINTEL
  {IR(37807, 40), 594}, // 663 SubgroupAvcMceSetInterShapePenaltyINTEL
  {IR(38200, 47), 602}, // 664 SubgroupAvcMceSetMotionVectorCostFunctionINTEL
  {IR(38489, 61), 608}, // 665 SubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL
  {IR(38437, 52), 607}, // 666 SubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL
  {IR(40983, 39), 661}, // 667 SubgroupAvcRefConvertToMcePayloadINTEL
  {IR(41305, 38), 668}, // 668 SubgroupAvcRefConvertToMceResultINTEL
  {IR(41158, 45), 665}, // 669 SubgroupAvcRefEvaluateWithDualReferenceINTEL
  {IR(41203, 46), 666}, // 670 SubgroupAvcRefEvaluateWithMultiReferenceINTEL
  {IR(41249, 56), 667}, // 671 SubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL
  {IR(41111, 47), 664}, // 672 SubgroupAvcRefEvaluateWithSingleReferenceINTEL
  {IR(41022, 46), 662}, // 673 SubgroupAvcRefSetBidirectionalMixDisableINTEL
  {IR(41068, 43), 663}, // 674 SubgroupAvcRefSetBilinearFilterEnableINTEL
  {IR(41441, 42), 672}, // 675 SubgroupAvcSicConfigureIpeLumaChromaINTEL
  {IR(41405, 36), 671}, // 676 SubgroupAvcSicConfigureIpeLumaINTEL
  {IR(41373, 32), 670}, // 677 SubgroupAvcSicConfigureSkcINTEL
  {IR(41522, 39), 674}, // 678 SubgroupAvcSicConvertToMcePayloadINTEL
  {IR(42062, 38), 686}, // 679 SubgroupAvcSicConvertToMceResultINTEL
  {IR(41837, 31), 681}, // 680 SubgroupAvcSicEvaluateIpeINTEL
  {IR(41915, 45), 683}, // 681 SubgroupAvcSicEvaluateWithDualReferenceINTEL
  {IR(41960, 46), 684}, // 682 SubgroupAvcSicEvaluateWithMultiReferenceINTEL
  {IR(42006, 56), 685}, // 683 SubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL
  {IR(41868, 47), 682}, // 684 SubgroupAvcSicEvaluateWithSingleReferenceINTEL
  {IR(42179, 46), 689}, // 685 SubgroupAvcSicGetBestIpeChromaDistortionINTEL
  {IR(42135, 44), 688}, // 686 SubgroupAvcSicGetBestIpeLumaDistortionINTEL
  {IR(42400, 35), 694}, // 687 SubgroupAvcSicGetInterRawSadsINTEL
  {IR(42266, 36), 691}, // 688 SubgroupAvcSicGetIpeChromaModeINTEL
  {IR(42100, 35), 687}, // 689 SubgroupAvcSicGetIpeLumaShapeINTEL
  {IR(41483, 39), 673}, // 690 SubgroupAvcSicGetMotionVectorMaskINTEL
  {IR(42225, 41), 690}, // 691 SubgroupAvcSicGetPackedIpeLumaModesINTEL
  {IR(42302, 50), 692}, // 692 SubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL
  {IR(42352, 48), 693}, // 693 SubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL
  {IR(41343, 30), 669}, // 694 SubgroupAvcSicInitializeINTEL
  {IR(41703, 43), 678}, // 695 SubgroupAvcSicSetBilinearFilterEnableINTEL
  {IR(41794, 43), 680}, // 696 SubgroupAvcSicSetBlockBasedRawSkipSadINTEL
  {IR(41653, 50), 677}, // 697 SubgroupAvcSicSetIntraChromaModeCostFunctionINTEL
  {IR(41605, 48), 676}, // 698 SubgroupAvcSicSetIntraLumaModeCostFunctionINTEL
  {IR(41561, 44), 675}, // 699 SubgroupAvcSicSetIntraLumaShapePenaltyINTEL
  {IR(41746, 48), 679}, // 700 SubgroupAvcSicSetSkcForwardTransformEnableINTEL
  {IR(5423, 18), 363}, // 701 SubgroupBallotKHR
  {IR(44844, 27), 792}, // 702 SubgroupBlockPrefetchINTEL
  {IR(36653, 23), 546}, // 703 SubgroupBlockReadINTEL
  {IR(36676, 24), 547}, // 704 SubgroupBlockWriteINTEL
  {IR(31847, 27), 364}, // 705 SubgroupFirstInvocationKHR
  {IR(36700, 28), 548}, // 706 SubgroupImageBlockReadINTEL
  {IR(36728, 29), 549}, // 707 SubgroupImageBlockWriteINTEL
  {IR(36757, 33), 550}, // 708 SubgroupImageMediaBlockReadINTEL
  {IR(36790, 34), 551}, // 709 SubgroupImageMediaBlockWriteINTEL
  {IR(13814, 38), 798}, // 710 SubgroupMatrixMultiplyAccumulateINTEL
  {IR(32030, 26), 374}, // 711 SubgroupReadInvocationKHR
  {IR(36581, 25), 543}, // 712 SubgroupShuffleDownINTEL
  {IR(12022, 21), 542}, // 713 SubgroupShuffleINTEL
  {IR(36606, 23), 544}, // 714 SubgroupShuffleUpINTEL
  {IR(36629, 24), 545}, // 715 SubgroupShuffleXorINTEL
  {IR(29204, 7), 229}, // 716 Switch
  {IR(44753, 23), 788}, // 717 TaskSequenceAsyncINTEL
  {IR(44729, 24), 787}, // 718 TaskSequenceCreateINTEL
  {IR(44776, 21), 789}, // 719 TaskSequenceGetINTEL
  {IR(44797, 25), 790}, // 720 TaskSequenceReleaseINTEL
  {IR(35924, 27), 519}, // 721 TensorLayoutSetBlockSizeNV
  {IR(35788, 28), 512}, // 722 TensorLayoutSetClampValueNV
  {IR(35717, 27), 509}, // 723 TensorLayoutSetDimensionNV
  {IR(35744, 24), 510}, // 724 TensorLayoutSetStrideNV
  {IR(35768, 20), 511}, // 725 TensorLayoutSliceNV
  {IR(31622, 19), 350}, // 726 TensorQuerySizeARM
  {IR(31593, 14), 348}, // 727 TensorReadARM
  {IR(35904, 20), 518}, // 728 TensorViewSetClipNV
  {IR(35835, 25), 514}, // 729 TensorViewSetDimensionNV
  {IR(35860, 22), 515}, // 730 TensorViewSetStrideNV
  {IR(31607, 15), 349}, // 731 TensorWriteARM
  {IR(31734, 20), 358}, // 732 TerminateInvocation
  {IR(32195, 16), 381}, // 733 TerminateRayKHR
  {IR(34983, 15), 486}, // 734 TerminateRayNV
  {IR(35006, 14), 488}, // 735 TraceMotionNV
  {IR(34998, 8), 487}, // 736 TraceNV
  {IR(32107, 12), 377}, // 737 TraceRayKHR
  {IR(35020, 17), 489}, // 738 TraceRayMotionNV
  {IR(27056, 10), 76}, // 739 Transpose
  {IR(35087, 29), 491}, // 740 TypeAccelerationStructureKHR
  {IR(35116, 28), 491}, // 741 TypeAccelerationStructureNV
  {IR(26005, 10), 25}, // 742 TypeArray
  {IR(37566, 37), 588}, // 743 TypeAvcImeDualReferenceStreaminINTEL
  {IR(37301, 23), 579}, // 744 TypeAvcImePayloadINTEL
  {IR(37483, 44), 586}, // 745 TypeAvcImeResultDualReferenceStreamoutINTEL
  {IR(37415, 22), 584}, // 746 TypeAvcImeResultINTEL
  {IR(37437, 46), 585}, // 747 TypeAvcImeResultSingleReferenceStreamoutINTEL
  {IR(37527, 39), 587}, // 748 TypeAvcImeSingleReferenceStreaminINTEL
  {IR(37370, 23), 582}, // 749 TypeAvcMcePayloadINTEL
  {IR(37393, 22), 583}, // 750 TypeAvcMceResultINTEL
  {IR(37324, 23), 580}, // 751 TypeAvcRefPayloadINTEL
  {IR(37603, 22), 589}, // 752 TypeAvcRefResultINTEL
  {IR(37347, 23), 581}, // 753 TypeAvcSicPayloadINTEL
  {IR(37625, 22), 590}, // 754 TypeAvcSicResultINTEL
  {IR(25767, 9), 17}, // 755 TypeBool
  {IR(44490, 23), 777}, // 756 TypeBufferSurfaceINTEL
  {IR(32376, 25), 388}, // 757 TypeCooperativeMatrixKHR
  {IR(35244, 24), 495}, // 758 TypeCooperativeMatrixNV
  {IR(34509, 24), 470}, // 759 TypeCooperativeVectorNV
  {IR(26120, 16), 32}, // 760 TypeDeviceEvent
  {IR(26110, 10), 31}, // 761 TypeEvent
  {IR(25821, 10), 19}, // 762 TypeFloat
  {IR(26169, 19), 36}, // 763 TypeForwardPointer
  {IR(26097, 13), 30}, // 764 TypeFunction
  {IR(31721, 13), 357}, // 765 TypeGraphARM
  {IR(34470, 16), 468}, // 766 TypeHitObjectNV
  {IR(25966, 10), 22}, // 767 TypeImage
  {IR(25776, 8), 18}, // 768 TypeInt
  {IR(25842, 11), 21}, // 769 TypeMatrix
  {IR(30551, 17), 300}, // 770 TypeNamedBarrier
  {IR(33411, 25), 428}, // 771 TypeNodePayloadArrayAMDX
  {IR(26043, 11), 28}, // 772 TypeOpaque
  {IR(26160, 9), 35}, // 773 TypePipe
  {IR(30429, 16), 295}, // 774 TypePipeStorage
  {IR(26085, 12), 29}, // 775 TypePointer
  {IR(26150, 10), 34}, // 776 TypeQueue
  {IR(32655, 16), 396}, // 777 TypeRayQueryKHR
  {IR(26136, 14), 33}, // 778 TypeReserveId
  {IR(26015, 17), 26}, // 779 TypeRuntimeArray
  {IR(25988, 17), 24}, // 780 TypeSampledImage
  {IR(25976, 12), 23}, // 781 TypeSampler
  {IR(26032, 11), 27}, // 782 TypeStruct
  {IR(44513, 25), 778}, // 783 TypeStructContinuedINTEL
  {IR(44822, 22), 791}, // 784 TypeTaskSequenceINTEL
  {IR(31537, 14), 347}, // 785 TypeTensorARM
  {IR(35660, 19), 506}, // 786 TypeTensorLayoutNV
  {IR(35679, 17), 507}, // 787 TypeTensorViewNV
  {IR(31754, 22), 359}, // 788 TypeUntypedPointerKHR
  {IR(25831, 11), 20}, // 789 TypeVector
  {IR(37283, 18), 578}, // 790 TypeVmeImageINTEL
  {IR(25758, 9), 16}, // 791 TypeVoid
  {IR(36912, 13), 557}, // 792 UAddSatINTEL
  {IR(36939, 14), 559}, // 793 UAverageINTEL
  {IR(36974, 21), 561}, // 794 UAverageRoundedINTEL
  {IR(27573, 9), 103}, // 795 UConvert
  {IR(36824, 24), 552}, // 796 UCountLeadingZerosINTEL
  {IR(36848, 25), 553}, // 797 UCountTrailingZerosINTEL
  {IR(27785, 5), 123}, // 798 UDiv
  {IR(32271, 5), 383}, // 799 UDot
  {IR(32324, 11), 386}, // 800 UDotAccSat
  {IR(32335, 14), 386}, // 801 UDotAccSatKHR
  {IR(32276, 8), 383}, // 802 UDotKHR
  {IR(28145, 13), 160}, // 803 UGreaterThan
  {IR(28171, 18), 162}, // 804 UGreaterThanEqual
  {IR(28207, 10), 164}, // 805 ULessThan
  {IR(28227, 15), 166}, // 806 ULessThanEqual
  {IR(27800, 5), 126}, // 807 UMod
  {IR(37036, 15), 565}, // 808 UMul32x16INTEL
  {IR(27953, 13), 140}, // 809 UMulExtended
  {IR(37008, 13), 563}, // 810 USubSatINTEL
  {IR(25270, 6), 1}, // 811 Undef
  {IR(28050, 10), 151}, // 812 Unordered
  {IR(29235, 12), 233}, // 813 Unreachable
  {IR(31795, 22), 361}, // 814 UntypedAccessChainKHR
  {IR(31932, 22), 367}, // 815 UntypedArrayLengthKHR
  {IR(32082, 25), 376}, // 816 UntypedGroupAsyncCopyKHR
  {IR(31817, 30), 362}, // 817 UntypedInBoundsAccessChainKHR
  {IR(31899, 33), 366}, // 818 UntypedInBoundsPtrAccessChainKHR
  {IR(31954, 19), 368}, // 819 UntypedPrefetchKHR
  {IR(31874, 25), 365}, // 820 UntypedPtrAccessChainKHR
  {IR(31776, 19), 360}, // 821 UntypedVariableKHR
  {IR(13880, 32), 800}, // 822 UntypedVariableLengthArrayINTEL
  {IR(26581, 9), 52}, // 823 Variable
  {IR(12478, 25), 695}, // 824 VariableLengthArrayINTEL
  {IR(26938, 21), 69}, // 825 VectorExtractDynamic
  {IR(26959, 20), 70}, // 826 VectorInsertDynamic
  {IR(26979, 14), 71}, // 827 VectorShuffle
  {IR(27861, 18), 133}, // 828 VectorTimesMatrix
  {IR(27825, 18), 131}, // 829 VectorTimesScalar
  {IR(37269, 14), 577}, // 830 VmeImageINTEL
  {IR(34764, 33), 479}, // 831 WritePackedPrimitiveIndices4x8NV
  {IR(29460, 10), 250}, // 832 WritePipe
  {IR(43802, 23), 757}, // 833 WritePipeBlockingINTEL
}};

// Extended instruction descriptions, ordered by (extinst enum, opcode value).
// The fields in order are:
//   enum value
//   operands, an IndexRange into kOperandSpans
//   name, a character-counting IndexRange into kStrings
//   capabilities, an IndexRange into kCapabilitySpans
static const std::array<ExtInstDesc, 425> kExtInstByValue{{
    {0,IR(0, 0),IR(45610, 14),IR(1, 0)}, // DebugInfoNone in debuginfo
    {1,IR(52, 3),IR(45624, 21),IR(1, 0)}, // DebugCompilationUnit in debuginfo
    {2,IR(770, 3),IR(45697, 15),IR(1, 0)}, // DebugTypeBasic in debuginfo
    {3,IR(773, 3),IR(45746, 17),IR(1, 0)}, // DebugTypePointer in debuginfo
    {4,IR(776, 2),IR(45801, 19),IR(1, 0)}, // DebugTypeQualifier in debuginfo
    {5,IR(168, 2),IR(45820, 15),IR(1, 0)}, // DebugTypeArray in debuginfo
    {6,IR(261, 2),IR(45835, 16),IR(1, 0)}, // DebugTypeVector in debuginfo
    {7,IR(778, 6),IR(45851, 13),IR(1, 0)}, // DebugTypedef in debuginfo
    {8,IR(168, 2),IR(45864, 18),IR(1, 0)}, // DebugTypeFunction in debuginfo
    {9,IR(784, 9),IR(45882, 14),IR(1, 0)}, // DebugTypeEnum in debuginfo
    {10,IR(793, 9),IR(45934, 19),IR(1, 0)}, // DebugTypeComposite in debuginfo
    {11,IR(802, 10),IR(45953, 16),IR(1, 0)}, // DebugTypeMember in debuginfo
    {12,IR(812, 5),IR(45969, 21),IR(1, 0)}, // DebugTypeInheritance in debuginfo
    {13,IR(36, 2),IR(45990, 21),IR(1, 0)}, // DebugTypePtrToMember in debuginfo
    {14,IR(168, 2),IR(46011, 18),IR(1, 0)}, // DebugTypeTemplate in debuginfo
    {15,IR(817, 6),IR(46029, 27),IR(1, 0)}, // DebugTypeTemplateParameter in debuginfo
    {16,IR(823, 5),IR(46056, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in debuginfo
    {17,IR(828, 5),IR(46091, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in debuginfo
    {18,IR(802, 10),IR(46122, 20),IR(1, 0)}, // DebugGlobalVariable in debuginfo
    {19,IR(833, 8),IR(46142, 25),IR(1, 0)}, // DebugFunctionDeclaration in debuginfo
    {20,IR(841, 11),IR(46167, 14),IR(1, 0)}, // DebugFunction in debuginfo
    {21,IR(852, 5),IR(46181, 18),IR(1, 0)}, // DebugLexicalBlock in debuginfo
    {22,IR(857, 3),IR(46199, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in debuginfo
    {23,IR(860, 2),IR(46230, 11),IR(1, 0)}, // DebugScope in debuginfo
    {24,IR(0, 0),IR(46241, 13),IR(1, 0)}, // DebugNoScope in debuginfo
    {25,IR(862, 3),IR(46254, 15),IR(1, 0)}, // DebugInlinedAt in debuginfo
    {26,IR(865, 7),IR(46311, 19),IR(1, 0)}, // DebugLocalVariable in debuginfo
    {27,IR(36, 2),IR(46330, 21),IR(1, 0)}, // DebugInlinedVariable in debuginfo
    {28,IR(33, 3),IR(46351, 13),IR(1, 0)}, // DebugDeclare in debuginfo
    {29,IR(375, 3),IR(46364, 11),IR(1, 0)}, // DebugValue in debuginfo
    {30,IR(872, 2),IR(46408, 15),IR(1, 0)}, // DebugOperation in debuginfo
    {31,IR(706, 1),IR(46423, 16),IR(1, 0)}, // DebugExpression in debuginfo
    {32,IR(874, 4),IR(46439, 14),IR(1, 0)}, // DebugMacroDef in debuginfo
    {33,IR(857, 3),IR(46453, 16),IR(1, 0)}, // DebugMacroUndef in debuginfo
    {1,IR(10, 1),IR(46469, 6),IR(1, 0)}, // Round in glsl_std_450
    {2,IR(10, 1),IR(46475, 10),IR(1, 0)}, // RoundEven in glsl_std_450
    {3,IR(10, 1),IR(46485, 6),IR(1, 0)}, // Trunc in glsl_std_450
    {4,IR(10, 1),IR(46491, 5),IR(1, 0)}, // FAbs in glsl_std_450
    {5,IR(10, 1),IR(46496, 5),IR(1, 0)}, // SAbs in glsl_std_450
    {6,IR(10, 1),IR(46501, 6),IR(1, 0)}, // FSign in glsl_std_450
    {7,IR(10, 1),IR(46507, 6),IR(1, 0)}, // SSign in glsl_std_450
    {8,IR(10, 1),IR(46513, 6),IR(1, 0)}, // Floor in glsl_std_450
    {9,IR(10, 1),IR(46519, 5),IR(1, 0)}, // Ceil in glsl_std_450
    {10,IR(10, 1),IR(46524, 6),IR(1, 0)}, // Fract in glsl_std_450
    {11,IR(10, 1),IR(46530, 8),IR(1, 0)}, // Radians in glsl_std_450
    {12,IR(10, 1),IR(46538, 8),IR(1, 0)}, // Degrees in glsl_std_450
    {13,IR(10, 1),IR(46546, 4),IR(1, 0)}, // Sin in glsl_std_450
    {14,IR(10, 1),IR(46550, 4),IR(1, 0)}, // Cos in glsl_std_450
    {15,IR(10, 1),IR(46554, 4),IR(1, 0)}, // Tan in glsl_std_450
    {16,IR(10, 1),IR(46558, 5),IR(1, 0)}, // Asin in glsl_std_450
    {17,IR(10, 1),IR(46563, 5),IR(1, 0)}, // Acos in glsl_std_450
    {18,IR(10, 1),IR(46568, 5),IR(1, 0)}, // Atan in glsl_std_450
    {19,IR(10, 1),IR(46573, 5),IR(1, 0)}, // Sinh in glsl_std_450
    {20,IR(10, 1),IR(46578, 5),IR(1, 0)}, // Cosh in glsl_std_450
    {21,IR(10, 1),IR(46583, 5),IR(1, 0)}, // Tanh in glsl_std_450
    {22,IR(10, 1),IR(46588, 6),IR(1, 0)}, // Asinh in glsl_std_450
    {23,IR(10, 1),IR(46594, 6),IR(1, 0)}, // Acosh in glsl_std_450
    {24,IR(10, 1),IR(46600, 6),IR(1, 0)}, // Atanh in glsl_std_450
    {25,IR(36, 2),IR(46606, 6),IR(1, 0)}, // Atan2 in glsl_std_450
    {26,IR(36, 2),IR(46612, 4),IR(1, 0)}, // Pow in glsl_std_450
    {27,IR(10, 1),IR(46616, 4),IR(1, 0)}, // Exp in glsl_std_450
    {28,IR(10, 1),IR(46620, 4),IR(1, 0)}, // Log in glsl_std_450
    {29,IR(10, 1),IR(46624, 5),IR(1, 0)}, // Exp2 in glsl_std_450
    {30,IR(10, 1),IR(46629, 5),IR(1, 0)}, // Log2 in glsl_std_450
    {31,IR(10, 1),IR(46634, 5),IR(1, 0)}, // Sqrt in glsl_std_450
    {32,IR(10, 1),IR(46639, 12),IR(1, 0)}, // InverseSqrt in glsl_std_450
    {33,IR(10, 1),IR(46651, 12),IR(1, 0)}, // Determinant in glsl_std_450
    {34,IR(10, 1),IR(46663, 14),IR(1, 0)}, // MatrixInverse in glsl_std_450
    {35,IR(36, 2),IR(46677, 5),IR(1, 0)}, // Modf in glsl_std_450
    {36,IR(10, 1),IR(46682, 11),IR(1, 0)}, // ModfStruct in glsl_std_450
    {37,IR(36, 2),IR(46693, 5),IR(1, 0)}, // FMin in glsl_std_450
    {38,IR(36, 2),IR(46698, 5),IR(1, 0)}, // UMin in glsl_std_450
    {39,IR(36, 2),IR(46703, 5),IR(1, 0)}, // SMin in glsl_std_450
    {40,IR(36, 2),IR(46708, 5),IR(1, 0)}, // FMax in glsl_std_450
    {41,IR(36, 2),IR(46713, 5),IR(1, 0)}, // UMax in glsl_std_450
    {42,IR(36, 2),IR(46718, 5),IR(1, 0)}, // SMax in glsl_std_450
    {43,IR(33, 3),IR(46723, 7),IR(1, 0)}, // FClamp in glsl_std_450
    {44,IR(33, 3),IR(46730, 7),IR(1, 0)}, // UClamp in glsl_std_450
    {45,IR(33, 3),IR(46737, 7),IR(1, 0)}, // SClamp in glsl_std_450
    {46,IR(33, 3),IR(46744, 5),IR(1, 0)}, // FMix in glsl_std_450
    {47,IR(33, 3),IR(46749, 5),IR(1, 0)}, // IMix in glsl_std_450
    {48,IR(36, 2),IR(46754, 5),IR(1, 0)}, // Step in glsl_std_450
    {49,IR(33, 3),IR(46759, 11),IR(1, 0)}, // SmoothStep in glsl_std_450
    {50,IR(33, 3),IR(46770, 4),IR(1, 0)}, // Fma in glsl_std_450
    {51,IR(36, 2),IR(46774, 6),IR(1, 0)}, // Frexp in glsl_std_450
    {52,IR(10, 1),IR(46780, 12),IR(1, 0)}, // FrexpStruct in glsl_std_450
    {53,IR(36, 2),IR(46792, 6),IR(1, 0)}, // Ldexp in glsl_std_450
    {54,IR(10, 1),IR(46798, 13),IR(1, 0)}, // PackSnorm4x8 in glsl_std_450
    {55,IR(10, 1),IR(46811, 13),IR(1, 0)}, // PackUnorm4x8 in glsl_std_450
    {56,IR(10, 1),IR(46824, 14),IR(1, 0)}, // PackSnorm2x16 in glsl_std_450
    {57,IR(10, 1),IR(46838, 14),IR(1, 0)}, // PackUnorm2x16 in glsl_std_450
    {58,IR(10, 1),IR(46852, 13),IR(1, 0)}, // PackHalf2x16 in glsl_std_450
    {59,IR(10, 1),IR(46865, 15),IR(310, 1)}, // PackDouble2x32 in glsl_std_450
    {60,IR(10, 1),IR(46880, 16),IR(1, 0)}, // UnpackSnorm2x16 in glsl_std_450
    {61,IR(10, 1),IR(46896, 16),IR(1, 0)}, // UnpackUnorm2x16 in glsl_std_450
    {62,IR(10, 1),IR(46912, 15),IR(1, 0)}, // UnpackHalf2x16 in glsl_std_450
    {63,IR(10, 1),IR(46927, 15),IR(1, 0)}, // UnpackSnorm4x8 in glsl_std_450
    {64,IR(10, 1),IR(46942, 15),IR(1, 0)}, // UnpackUnorm4x8 in glsl_std_450
    {65,IR(10, 1),IR(46957, 17),IR(310, 1)}, // UnpackDouble2x32 in glsl_std_450
    {66,IR(10, 1),IR(46974, 7),IR(1, 0)}, // Length in glsl_std_450
    {67,IR(36, 2),IR(46981, 9),IR(1, 0)}, // Distance in glsl_std_450
    {68,IR(36, 2),IR(46990, 6),IR(1, 0)}, // Cross in glsl_std_450
    {69,IR(10, 1),IR(46996, 10),IR(1, 0)}, // Normalize in glsl_std_450
    {70,IR(33, 3),IR(47006, 12),IR(1, 0)}, // FaceForward in glsl_std_450
    {71,IR(36, 2),IR(47018, 8),IR(1, 0)}, // Reflect in glsl_std_450
    {72,IR(33, 3),IR(47026, 8),IR(1, 0)}, // Refract in glsl_std_450
    {73,IR(10, 1),IR(47034, 9),IR(1, 0)}, // FindILsb in glsl_std_450
    {74,IR(10, 1),IR(47043, 9),IR(1, 0)}, // FindSMsb in glsl_std_450
    {75,IR(10, 1),IR(47052, 9),IR(1, 0)}, // FindUMsb in glsl_std_450
    {76,IR(10, 1),IR(47061, 22),IR(311, 1)}, // InterpolateAtCentroid in glsl_std_450
    {77,IR(36, 2),IR(47083, 20),IR(311, 1)}, // InterpolateAtSample in glsl_std_450
    {78,IR(36, 2),IR(47103, 20),IR(311, 1)}, // InterpolateAtOffset in glsl_std_450
    {79,IR(36, 2),IR(47123, 5),IR(1, 0)}, // NMin in glsl_std_450
    {80,IR(36, 2),IR(47128, 5),IR(1, 0)}, // NMax in glsl_std_450
    {81,IR(33, 3),IR(47133, 7),IR(1, 0)}, // NClamp in glsl_std_450
    {1,IR(399, 5),IR(4642, 7),IR(1, 0)}, // Kernel in nonsemantic_clspvreflection
    {2,IR(878, 5),IR(47140, 13),IR(1, 0)}, // ArgumentInfo in nonsemantic_clspvreflection
    {3,IR(883, 5),IR(47153, 22),IR(1, 0)}, // ArgumentStorageBuffer in nonsemantic_clspvreflection
    {4,IR(883, 5),IR(47175, 16),IR(1, 0)}, // ArgumentUniform in nonsemantic_clspvreflection
    {5,IR(554, 7),IR(47191, 25),IR(1, 0)}, // ArgumentPodStorageBuffer in nonsemantic_clspvreflection
    {6,IR(554, 7),IR(47216, 19),IR(1, 0)}, // ArgumentPodUniform in nonsemantic_clspvreflection
    {7,IR(883, 5),IR(47235, 24),IR(1, 0)}, // ArgumentPodPushConstant in nonsemantic_clspvreflection
    {8,IR(883, 5),IR(47259, 21),IR(1, 0)}, // ArgumentSampledImage in nonsemantic_clspvreflection
    {9,IR(883, 5),IR(47280, 21),IR(1, 0)}, // ArgumentStorageImage in nonsemantic_clspvreflection
    {10,IR(883, 5),IR(47301, 16),IR(1, 0)}, // ArgumentSampler in nonsemantic_clspvreflection
    {11,IR(883, 5),IR(47317, 18),IR(1, 0)}, // ArgumentWorkgroup in nonsemantic_clspvreflection
    {12,IR(33, 3),IR(47335, 26),IR(1, 0)}, // SpecConstantWorkgroupSize in nonsemantic_clspvreflection
    {13,IR(33, 3),IR(47361, 25),IR(1, 0)}, // SpecConstantGlobalOffset in nonsemantic_clspvreflection
    {14,IR(10, 1),IR(47386, 20),IR(1, 0)}, // SpecConstantWorkDim in nonsemantic_clspvreflection
    {15,IR(36, 2),IR(47406, 25),IR(1, 0)}, // PushConstantGlobalOffset in nonsemantic_clspvreflection
    {16,IR(36, 2),IR(47431, 30),IR(1, 0)}, // PushConstantEnqueuedLocalSize in nonsemantic_clspvreflection
    {17,IR(36, 2),IR(47461, 23),IR(1, 0)}, // PushConstantGlobalSize in nonsemantic_clspvreflection
    {18,IR(36, 2),IR(47484, 25),IR(1, 0)}, // PushConstantRegionOffset in nonsemantic_clspvreflection
    {19,IR(36, 2),IR(47509, 26),IR(1, 0)}, // PushConstantNumWorkgroups in nonsemantic_clspvreflection
    {20,IR(36, 2),IR(47535, 30),IR(1, 0)}, // PushConstantRegionGroupOffset in nonsemantic_clspvreflection
    {21,IR(33, 3),IR(47565, 26),IR(1, 0)}, // ConstantDataStorageBuffer in nonsemantic_clspvreflection
    {22,IR(33, 3),IR(47591, 20),IR(1, 0)}, // ConstantDataUniform in nonsemantic_clspvreflection
    {23,IR(33, 3),IR(8067, 15),IR(1, 0)}, // LiteralSampler in nonsemantic_clspvreflection
    {24,IR(296, 4),IR(47611, 30),IR(1, 0)}, // PropertyRequiredWorkgroupSize in nonsemantic_clspvreflection
    {25,IR(10, 1),IR(47641, 28),IR(1, 0)}, // SpecConstantSubgroupMaxSize in nonsemantic_clspvreflection
    {26,IR(883, 5),IR(47669, 28),IR(1, 0)}, // ArgumentPointerPushConstant in nonsemantic_clspvreflection
    {27,IR(554, 7),IR(47697, 23),IR(1, 0)}, // ArgumentPointerUniform in nonsemantic_clspvreflection
    {28,IR(33, 3),IR(47720, 35),IR(1, 0)}, // ProgramScopeVariablesStorageBuffer in nonsemantic_clspvreflection
    {29,IR(33, 3),IR(47755, 38),IR(1, 0)}, // ProgramScopeVariablePointerRelocation in nonsemantic_clspvreflection
    {30,IR(296, 4),IR(47793, 42),IR(1, 0)}, // ImageArgumentInfoChannelOrderPushConstant in nonsemantic_clspvreflection
    {31,IR(296, 4),IR(47835, 45),IR(1, 0)}, // ImageArgumentInfoChannelDataTypePushConstant in nonsemantic_clspvreflection
    {32,IR(525, 6),IR(47880, 37),IR(1, 0)}, // ImageArgumentInfoChannelOrderUniform in nonsemantic_clspvreflection
    {33,IR(525, 6),IR(47917, 40),IR(1, 0)}, // ImageArgumentInfoChannelDataTypeUniform in nonsemantic_clspvreflection
    {34,IR(883, 5),IR(47957, 27),IR(1, 0)}, // ArgumentStorageTexelBuffer in nonsemantic_clspvreflection
    {35,IR(883, 5),IR(47984, 27),IR(1, 0)}, // ArgumentUniformTexelBuffer in nonsemantic_clspvreflection
    {36,IR(33, 3),IR(48011, 32),IR(1, 0)}, // ConstantDataPointerPushConstant in nonsemantic_clspvreflection
    {37,IR(33, 3),IR(48043, 40),IR(1, 0)}, // ProgramScopeVariablePointerPushConstant in nonsemantic_clspvreflection
    {38,IR(375, 3),IR(48083, 11),IR(1, 0)}, // PrintfInfo in nonsemantic_clspvreflection
    {39,IR(33, 3),IR(48094, 26),IR(1, 0)}, // PrintfBufferStorageBuffer in nonsemantic_clspvreflection
    {40,IR(33, 3),IR(48120, 32),IR(1, 0)}, // PrintfBufferPointerPushConstant in nonsemantic_clspvreflection
    {41,IR(296, 4),IR(48152, 34),IR(1, 0)}, // NormalizedSamplerMaskPushConstant in nonsemantic_clspvreflection
    {42,IR(36, 2),IR(48186, 22),IR(1, 0)}, // WorkgroupVariableSize in nonsemantic_clspvreflection
    {0,IR(0, 0),IR(45610, 14),IR(1, 0)}, // DebugInfoNone in nonsemantic_shader_debuginfo_100
    {1,IR(296, 4),IR(45624, 21),IR(1, 0)}, // DebugCompilationUnit in nonsemantic_shader_debuginfo_100
    {2,IR(296, 4),IR(45697, 15),IR(1, 0)}, // DebugTypeBasic in nonsemantic_shader_debuginfo_100
    {3,IR(33, 3),IR(45746, 17),IR(1, 0)}, // DebugTypePointer in nonsemantic_shader_debuginfo_100
    {4,IR(36, 2),IR(45801, 19),IR(1, 0)}, // DebugTypeQualifier in nonsemantic_shader_debuginfo_100
    {5,IR(168, 2),IR(45820, 15),IR(1, 0)}, // DebugTypeArray in nonsemantic_shader_debuginfo_100
    {6,IR(36, 2),IR(45835, 16),IR(1, 0)}, // DebugTypeVector in nonsemantic_shader_debuginfo_100
    {7,IR(525, 6),IR(45851, 13),IR(1, 0)}, // DebugTypedef in nonsemantic_shader_debuginfo_100
    {8,IR(375, 3),IR(45864, 18),IR(1, 0)}, // DebugTypeFunction in nonsemantic_shader_debuginfo_100
    {9,IR(888, 9),IR(45882, 14),IR(1, 0)}, // DebugTypeEnum in nonsemantic_shader_debuginfo_100
    {10,IR(897, 10),IR(45934, 19),IR(1, 0)}, // DebugTypeComposite in nonsemantic_shader_debuginfo_100
    {11,IR(907, 9),IR(45953, 16),IR(1, 0)}, // DebugTypeMember in nonsemantic_shader_debuginfo_100
    {12,IR(296, 4),IR(45969, 21),IR(1, 0)}, // DebugTypeInheritance in nonsemantic_shader_debuginfo_100
    {13,IR(36, 2),IR(45990, 21),IR(1, 0)}, // DebugTypePtrToMember in nonsemantic_shader_debuginfo_100
    {14,IR(168, 2),IR(46011, 18),IR(1, 0)}, // DebugTypeTemplate in nonsemantic_shader_debuginfo_100
    {15,IR(525, 6),IR(46029, 27),IR(1, 0)}, // DebugTypeTemplateParameter in nonsemantic_shader_debuginfo_100
    {16,IR(634, 5),IR(46056, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in nonsemantic_shader_debuginfo_100
    {17,IR(916, 5),IR(46091, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in nonsemantic_shader_debuginfo_100
    {18,IR(921, 10),IR(46122, 20),IR(1, 0)}, // DebugGlobalVariable in nonsemantic_shader_debuginfo_100
    {19,IR(471, 8),IR(46142, 25),IR(1, 0)}, // DebugFunctionDeclaration in nonsemantic_shader_debuginfo_100
    {20,IR(921, 10),IR(46167, 14),IR(1, 0)}, // DebugFunction in nonsemantic_shader_debuginfo_100
    {21,IR(883, 5),IR(46181, 18),IR(1, 0)}, // DebugLexicalBlock in nonsemantic_shader_debuginfo_100
    {22,IR(33, 3),IR(46199, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in nonsemantic_shader_debuginfo_100
    {23,IR(860, 2),IR(46230, 11),IR(1, 0)}, // DebugScope in nonsemantic_shader_debuginfo_100
    {24,IR(0, 0),IR(46241, 13),IR(1, 0)}, // DebugNoScope in nonsemantic_shader_debuginfo_100
    {25,IR(931, 3),IR(46254, 15),IR(1, 0)}, // DebugInlinedAt in nonsemantic_shader_debuginfo_100
    {26,IR(934, 8),IR(46311, 19),IR(1, 0)}, // DebugLocalVariable in nonsemantic_shader_debuginfo_100
    {27,IR(36, 2),IR(46330, 21),IR(1, 0)}, // DebugInlinedVariable in nonsemantic_shader_debuginfo_100
    {28,IR(942, 4),IR(46351, 13),IR(1, 0)}, // DebugDeclare in nonsemantic_shader_debuginfo_100
    {29,IR(942, 4),IR(46364, 11),IR(1, 0)}, // DebugValue in nonsemantic_shader_debuginfo_100
    {30,IR(168, 2),IR(46408, 15),IR(1, 0)}, // DebugOperation in nonsemantic_shader_debuginfo_100
    {31,IR(706, 1),IR(46423, 16),IR(1, 0)}, // DebugExpression in nonsemantic_shader_debuginfo_100
    {32,IR(577, 4),IR(46439, 14),IR(1, 0)}, // DebugMacroDef in nonsemantic_shader_debuginfo_100
    {33,IR(33, 3),IR(46453, 16),IR(1, 0)}, // DebugMacroUndef in nonsemantic_shader_debuginfo_100
    {34,IR(506, 7),IR(48208, 20),IR(1, 0)}, // DebugImportedEntity in nonsemantic_shader_debuginfo_100
    {35,IR(860, 2),IR(48228, 12),IR(1, 0)}, // DebugSource in nonsemantic_shader_debuginfo_100
    {101,IR(36, 2),IR(48240, 24),IR(1, 0)}, // DebugFunctionDefinition in nonsemantic_shader_debuginfo_100
    {102,IR(10, 1),IR(48264, 21),IR(1, 0)}, // DebugSourceContinued in nonsemantic_shader_debuginfo_100
    {103,IR(634, 5),IR(48285, 10),IR(1, 0)}, // DebugLine in nonsemantic_shader_debuginfo_100
    {104,IR(0, 0),IR(48295, 12),IR(1, 0)}, // DebugNoLine in nonsemantic_shader_debuginfo_100
    {105,IR(36, 2),IR(48307, 21),IR(1, 0)}, // DebugBuildIdentifier in nonsemantic_shader_debuginfo_100
    {106,IR(10, 1),IR(48328, 17),IR(1, 0)}, // DebugStoragePath in nonsemantic_shader_debuginfo_100
    {107,IR(296, 4),IR(48345, 16),IR(1, 0)}, // DebugEntryPoint in nonsemantic_shader_debuginfo_100
    {108,IR(33, 3),IR(48361, 16),IR(1, 0)}, // DebugTypeMatrix in nonsemantic_shader_debuginfo_100
    {1,IR(724, 9),IR(48377, 14),IR(1, 0)}, // Configuration in nonsemantic_vkspreflection
    {2,IR(10, 1),IR(48391, 13),IR(1, 0)}, // StartCounter in nonsemantic_vkspreflection
    {3,IR(10, 1),IR(48404, 12),IR(1, 0)}, // StopCounter in nonsemantic_vkspreflection
    {4,IR(296, 4),IR(48416, 14),IR(1, 0)}, // PushConstants in nonsemantic_vkspreflection
    {5,IR(33, 3),IR(48430, 23),IR(1, 0)}, // SpecializationMapEntry in nonsemantic_vkspreflection
    {6,IR(946, 15),IR(48453, 20),IR(1, 0)}, // DescriptorSetBuffer in nonsemantic_vkspreflection
    {7,IR(961, 33),IR(48473, 19),IR(1, 0)}, // DescriptorSetImage in nonsemantic_vkspreflection
    {8,IR(994, 19),IR(48492, 21),IR(1, 0)}, // DescriptorSetSampler in nonsemantic_vkspreflection
    {0,IR(0, 0),IR(45610, 14),IR(1, 0)}, // DebugInfoNone in opencl_debuginfo_100
    {1,IR(1013, 4),IR(45624, 21),IR(1, 0)}, // DebugCompilationUnit in opencl_debuginfo_100
    {2,IR(1017, 3),IR(45697, 15),IR(1, 0)}, // DebugTypeBasic in opencl_debuginfo_100
    {3,IR(1020, 3),IR(45746, 17),IR(1, 0)}, // DebugTypePointer in opencl_debuginfo_100
    {4,IR(1023, 2),IR(45801, 19),IR(1, 0)}, // DebugTypeQualifier in opencl_debuginfo_100
    {5,IR(168, 2),IR(45820, 15),IR(1, 0)}, // DebugTypeArray in opencl_debuginfo_100
    {6,IR(261, 2),IR(45835, 16),IR(1, 0)}, // DebugTypeVector in opencl_debuginfo_100
    {7,IR(778, 6),IR(45851, 13),IR(1, 0)}, // DebugTypedef in opencl_debuginfo_100
    {8,IR(1025, 3),IR(45864, 18),IR(1, 0)}, // DebugTypeFunction in opencl_debuginfo_100
    {9,IR(1028, 9),IR(45882, 14),IR(1, 0)}, // DebugTypeEnum in opencl_debuginfo_100
    {10,IR(1037, 10),IR(45934, 19),IR(1, 0)}, // DebugTypeComposite in opencl_debuginfo_100
    {11,IR(1047, 10),IR(45953, 16),IR(1, 0)}, // DebugTypeMember in opencl_debuginfo_100
    {12,IR(1057, 5),IR(45969, 21),IR(1, 0)}, // DebugTypeInheritance in opencl_debuginfo_100
    {13,IR(36, 2),IR(45990, 21),IR(1, 0)}, // DebugTypePtrToMember in opencl_debuginfo_100
    {14,IR(168, 2),IR(46011, 18),IR(1, 0)}, // DebugTypeTemplate in opencl_debuginfo_100
    {15,IR(817, 6),IR(46029, 27),IR(1, 0)}, // DebugTypeTemplateParameter in opencl_debuginfo_100
    {16,IR(823, 5),IR(46056, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in opencl_debuginfo_100
    {17,IR(828, 5),IR(46091, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in opencl_debuginfo_100
    {18,IR(1047, 10),IR(46122, 20),IR(1, 0)}, // DebugGlobalVariable in opencl_debuginfo_100
    {19,IR(1062, 8),IR(46142, 25),IR(1, 0)}, // DebugFunctionDeclaration in opencl_debuginfo_100
    {20,IR(1070, 11),IR(46167, 14),IR(1, 0)}, // DebugFunction in opencl_debuginfo_100
    {21,IR(852, 5),IR(46181, 18),IR(1, 0)}, // DebugLexicalBlock in opencl_debuginfo_100
    {22,IR(857, 3),IR(46199, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in opencl_debuginfo_100
    {23,IR(860, 2),IR(46230, 11),IR(1, 0)}, // DebugScope in opencl_debuginfo_100
    {24,IR(0, 0),IR(46241, 13),IR(1, 0)}, // DebugNoScope in opencl_debuginfo_100
    {25,IR(862, 3),IR(46254, 15),IR(1, 0)}, // DebugInlinedAt in opencl_debuginfo_100
    {26,IR(1081, 8),IR(46311, 19),IR(1, 0)}, // DebugLocalVariable in opencl_debuginfo_100
    {27,IR(36, 2),IR(46330, 21),IR(1, 0)}, // DebugInlinedVariable in opencl_debuginfo_100
    {28,IR(33, 3),IR(46351, 13),IR(1, 0)}, // DebugDeclare in opencl_debuginfo_100
    {29,IR(942, 4),IR(46364, 11),IR(1, 0)}, // DebugValue in opencl_debuginfo_100
    {30,IR(1089, 2),IR(46408, 15),IR(1, 0)}, // DebugOperation in opencl_debuginfo_100
    {31,IR(706, 1),IR(46423, 16),IR(1, 0)}, // DebugExpression in opencl_debuginfo_100
    {32,IR(874, 4),IR(46439, 14),IR(1, 0)}, // DebugMacroDef in opencl_debuginfo_100
    {33,IR(857, 3),IR(46453, 16),IR(1, 0)}, // DebugMacroUndef in opencl_debuginfo_100
    {34,IR(1091, 7),IR(48208, 20),IR(1, 0)}, // DebugImportedEntity in opencl_debuginfo_100
    {35,IR(860, 2),IR(48228, 12),IR(1, 0)}, // DebugSource in opencl_debuginfo_100
    {36,IR(1098, 8),IR(48813, 17),IR(1, 0)}, // DebugModuleINTEL in opencl_debuginfo_100
    {0,IR(10, 1),IR(48830, 5),IR(1, 0)}, // acos in opencl_std_100
    {1,IR(10, 1),IR(48835, 6),IR(1, 0)}, // acosh in opencl_std_100
    {2,IR(10, 1),IR(48841, 7),IR(1, 0)}, // acospi in opencl_std_100
    {3,IR(10, 1),IR(48848, 5),IR(1, 0)}, // asin in opencl_std_100
    {4,IR(10, 1),IR(48853, 6),IR(1, 0)}, // asinh in opencl_std_100
    {5,IR(10, 1),IR(48859, 7),IR(1, 0)}, // asinpi in opencl_std_100
    {6,IR(10, 1),IR(48866, 5),IR(1, 0)}, // atan in opencl_std_100
    {7,IR(36, 2),IR(48871, 6),IR(1, 0)}, // atan2 in opencl_std_100
    {8,IR(10, 1),IR(48877, 6),IR(1, 0)}, // atanh in opencl_std_100
    {9,IR(10, 1),IR(48883, 7),IR(1, 0)}, // atanpi in opencl_std_100
    {10,IR(36, 2),IR(48890, 8),IR(1, 0)}, // atan2pi in opencl_std_100
    {11,IR(10, 1),IR(48898, 5),IR(1, 0)}, // cbrt in opencl_std_100
    {12,IR(10, 1),IR(48903, 5),IR(1, 0)}, // ceil in opencl_std_100
    {13,IR(36, 2),IR(48908, 9),IR(1, 0)}, // copysign in opencl_std_100
    {14,IR(10, 1),IR(48917, 4),IR(1, 0)}, // cos in opencl_std_100
    {15,IR(10, 1),IR(48921, 5),IR(1, 0)}, // cosh in opencl_std_100
    {16,IR(10, 1),IR(48926, 6),IR(1, 0)}, // cospi in opencl_std_100
    {17,IR(10, 1),IR(48932, 5),IR(1, 0)}, // erfc in opencl_std_100
    {18,IR(10, 1),IR(48937, 4),IR(1, 0)}, // erf in opencl_std_100
    {19,IR(10, 1),IR(48941, 4),IR(1, 0)}, // exp in opencl_std_100
    {20,IR(10, 1),IR(48945, 5),IR(1, 0)}, // exp2 in opencl_std_100
    {21,IR(10, 1),IR(48950, 6),IR(1, 0)}, // exp10 in opencl_std_100
    {22,IR(10, 1),IR(48956, 6),IR(1, 0)}, // expm1 in opencl_std_100
    {23,IR(10, 1),IR(48962, 5),IR(1, 0)}, // fabs in opencl_std_100
    {24,IR(36, 2),IR(48967, 5),IR(1, 0)}, // fdim in opencl_std_100
    {25,IR(10, 1),IR(48972, 6),IR(1, 0)}, // floor in opencl_std_100
    {26,IR(33, 3),IR(48978, 4),IR(1, 0)}, // fma in opencl_std_100
    {27,IR(36, 2),IR(48982, 5),IR(1, 0)}, // fmax in opencl_std_100
    {28,IR(36, 2),IR(48987, 5),IR(1, 0)}, // fmin in opencl_std_100
    {29,IR(36, 2),IR(48992, 5),IR(1, 0)}, // fmod in opencl_std_100
    {30,IR(36, 2),IR(48997, 6),IR(1, 0)}, // fract in opencl_std_100
    {31,IR(36, 2),IR(49003, 6),IR(1, 0)}, // frexp in opencl_std_100
    {32,IR(36, 2),IR(49009, 6),IR(1, 0)}, // hypot in opencl_std_100
    {33,IR(10, 1),IR(49015, 6),IR(1, 0)}, // ilogb in opencl_std_100
    {34,IR(36, 2),IR(49021, 6),IR(1, 0)}, // ldexp in opencl_std_100
    {35,IR(10, 1),IR(49027, 7),IR(1, 0)}, // lgamma in opencl_std_100
    {36,IR(36, 2),IR(49034, 9),IR(1, 0)}, // lgamma_r in opencl_std_100
    {37,IR(10, 1),IR(49043, 4),IR(1, 0)}, // log in opencl_std_100
    {38,IR(10, 1),IR(49047, 5),IR(1, 0)}, // log2 in opencl_std_100
    {39,IR(10, 1),IR(49052, 6),IR(1, 0)}, // log10 in opencl_std_100
    {40,IR(10, 1),IR(49058, 6),IR(1, 0)}, // log1p in opencl_std_100
    {41,IR(10, 1),IR(49064, 5),IR(1, 0)}, // logb in opencl_std_100
    {42,IR(33, 3),IR(49069, 4),IR(1, 0)}, // mad in opencl_std_100
    {43,IR(36, 2),IR(49073, 7),IR(1, 0)}, // maxmag in opencl_std_100
    {44,IR(36, 2),IR(49080, 7),IR(1, 0)}, // minmag in opencl_std_100
    {45,IR(36, 2),IR(49087, 5),IR(1, 0)}, // modf in opencl_std_100
    {46,IR(10, 1),IR(49092, 4),IR(1, 0)}, // nan in opencl_std_100
    {47,IR(36, 2),IR(49096, 10),IR(1, 0)}, // nextafter in opencl_std_100
    {48,IR(36, 2),IR(49106, 4),IR(1, 0)}, // pow in opencl_std_100
    {49,IR(36, 2),IR(49110, 5),IR(1, 0)}, // pown in opencl_std_100
    {50,IR(36, 2),IR(49115, 5),IR(1, 0)}, // powr in opencl_std_100
    {51,IR(36, 2),IR(49120, 10),IR(1, 0)}, // remainder in opencl_std_100
    {52,IR(33, 3),IR(49130, 7),IR(1, 0)}, // remquo in opencl_std_100
    {53,IR(10, 1),IR(49137, 5),IR(1, 0)}, // rint in opencl_std_100
    {54,IR(36, 2),IR(49142, 6),IR(1, 0)}, // rootn in opencl_std_100
    {55,IR(10, 1),IR(49148, 6),IR(1, 0)}, // round in opencl_std_100
    {56,IR(10, 1),IR(49154, 6),IR(1, 0)}, // rsqrt in opencl_std_100
    {57,IR(10, 1),IR(49160, 4),IR(1, 0)}, // sin in opencl_std_100
    {58,IR(36, 2),IR(49164, 7),IR(1, 0)}, // sincos in opencl_std_100
    {59,IR(10, 1),IR(49171, 5),IR(1, 0)}, // sinh in opencl_std_100
    {60,IR(10, 1),IR(49176, 6),IR(1, 0)}, // sinpi in opencl_std_100
    {61,IR(10, 1),IR(49182, 5),IR(1, 0)}, // sqrt in opencl_std_100
    {62,IR(10, 1),IR(49187, 4),IR(1, 0)}, // tan in opencl_std_100
    {63,IR(10, 1),IR(49191, 5),IR(1, 0)}, // tanh in opencl_std_100
    {64,IR(10, 1),IR(49196, 6),IR(1, 0)}, // tanpi in opencl_std_100
    {65,IR(10, 1),IR(49202, 7),IR(1, 0)}, // tgamma in opencl_std_100
    {66,IR(10, 1),IR(49209, 6),IR(1, 0)}, // trunc in opencl_std_100
    {67,IR(10, 1),IR(49215, 9),IR(1, 0)}, // half_cos in opencl_std_100
    {68,IR(36, 2),IR(49224, 12),IR(1, 0)}, // half_divide in opencl_std_100
    {69,IR(10, 1),IR(49236, 9),IR(1, 0)}, // half_exp in opencl_std_100
    {70,IR(10, 1),IR(49245, 10),IR(1, 0)}, // half_exp2 in opencl_std_100
    {71,IR(10, 1),IR(49255, 11),IR(1, 0)}, // half_exp10 in opencl_std_100
    {72,IR(10, 1),IR(49266, 9),IR(1, 0)}, // half_log in opencl_std_100
    {73,IR(10, 1),IR(49275, 10),IR(1, 0)}, // half_log2 in opencl_std_100
    {74,IR(10, 1),IR(49285, 11),IR(1, 0)}, // half_log10 in opencl_std_100
    {75,IR(36, 2),IR(49296, 10),IR(1, 0)}, // half_powr in opencl_std_100
    {76,IR(10, 1),IR(49306, 11),IR(1, 0)}, // half_recip in opencl_std_100
    {77,IR(10, 1),IR(49317, 11),IR(1, 0)}, // half_rsqrt in opencl_std_100
    {78,IR(10, 1),IR(49328, 9),IR(1, 0)}, // half_sin in opencl_std_100
    {79,IR(10, 1),IR(49337, 10),IR(1, 0)}, // half_sqrt in opencl_std_100
    {80,IR(10, 1),IR(49347, 9),IR(1, 0)}, // half_tan in opencl_std_100
    {81,IR(10, 1),IR(49356, 11),IR(1, 0)}, // native_cos in opencl_std_100
    {82,IR(36, 2),IR(49367, 14),IR(1, 0)}, // native_divide in opencl_std_100
    {83,IR(10, 1),IR(49381, 11),IR(1, 0)}, // native_exp in opencl_std_100
    {84,IR(10, 1),IR(49392, 12),IR(1, 0)}, // native_exp2 in opencl_std_100
    {85,IR(10, 1),IR(49404, 13),IR(1, 0)}, // native_exp10 in opencl_std_100
    {86,IR(10, 1),IR(49417, 11),IR(1, 0)}, // native_log in opencl_std_100
    {87,IR(10, 1),IR(49428, 12),IR(1, 0)}, // native_log2 in opencl_std_100
    {88,IR(10, 1),IR(49440, 13),IR(1, 0)}, // native_log10 in opencl_std_100
    {89,IR(36, 2),IR(49453, 12),IR(1, 0)}, // native_powr in opencl_std_100
    {90,IR(10, 1),IR(49465, 13),IR(1, 0)}, // native_recip in opencl_std_100
    {91,IR(10, 1),IR(49478, 13),IR(1, 0)}, // native_rsqrt in opencl_std_100
    {92,IR(10, 1),IR(49491, 11),IR(1, 0)}, // native_sin in opencl_std_100
    {93,IR(10, 1),IR(49502, 12),IR(1, 0)}, // native_sqrt in opencl_std_100
    {94,IR(10, 1),IR(49514, 11),IR(1, 0)}, // native_tan in opencl_std_100
    {95,IR(33, 3),IR(49525, 7),IR(1, 0)}, // fclamp in opencl_std_100
    {96,IR(10, 1),IR(49532, 8),IR(1, 0)}, // degrees in opencl_std_100
    {97,IR(36, 2),IR(49540, 12),IR(1, 0)}, // fmax_common in opencl_std_100
    {98,IR(36, 2),IR(49552, 12),IR(1, 0)}, // fmin_common in opencl_std_100
    {99,IR(33, 3),IR(49564, 4),IR(1, 0)}, // mix in opencl_std_100
    {100,IR(10, 1),IR(49568, 8),IR(1, 0)}, // radians in opencl_std_100
    {101,IR(36, 2),IR(49576, 5),IR(1, 0)}, // step in opencl_std_100
    {102,IR(33, 3),IR(49581, 11),IR(1, 0)}, // smoothstep in opencl_std_100
    {103,IR(10, 1),IR(49592, 5),IR(1, 0)}, // sign in opencl_std_100
    {104,IR(36, 2),IR(49597, 6),IR(1, 0)}, // cross in opencl_std_100
    {105,IR(36, 2),IR(49603, 9),IR(1, 0)}, // distance in opencl_std_100
    {106,IR(10, 1),IR(49612, 7),IR(1, 0)}, // length in opencl_std_100
    {107,IR(10, 1),IR(49619, 10),IR(1, 0)}, // normalize in opencl_std_100
    {108,IR(36, 2),IR(49629, 14),IR(1, 0)}, // fast_distance in opencl_std_100
    {109,IR(10, 1),IR(49643, 12),IR(1, 0)}, // fast_length in opencl_std_100
    {110,IR(10, 1),IR(49655, 15),IR(1, 0)}, // fast_normalize in opencl_std_100
    {141,IR(10, 1),IR(49670, 6),IR(1, 0)}, // s_abs in opencl_std_100
    {142,IR(36, 2),IR(49676, 11),IR(1, 0)}, // s_abs_diff in opencl_std_100
    {143,IR(36, 2),IR(49687, 10),IR(1, 0)}, // s_add_sat in opencl_std_100
    {144,IR(36, 2),IR(49697, 10),IR(1, 0)}, // u_add_sat in opencl_std_100
    {145,IR(36, 2),IR(49707, 7),IR(1, 0)}, // s_hadd in opencl_std_100
    {146,IR(36, 2),IR(49714, 7),IR(1, 0)}, // u_hadd in opencl_std_100
    {147,IR(36, 2),IR(49721, 8),IR(1, 0)}, // s_rhadd in opencl_std_100
    {148,IR(36, 2),IR(49729, 8),IR(1, 0)}, // u_rhadd in opencl_std_100
    {149,IR(33, 3),IR(49737, 8),IR(1, 0)}, // s_clamp in opencl_std_100
    {150,IR(33, 3),IR(49745, 8),IR(1, 0)}, // u_clamp in opencl_std_100
    {151,IR(10, 1),IR(49753, 4),IR(1, 0)}, // clz in opencl_std_100
    {152,IR(10, 1),IR(49757, 4),IR(1, 0)}, // ctz in opencl_std_100
    {153,IR(33, 3),IR(49761, 9),IR(1, 0)}, // s_mad_hi in opencl_std_100
    {154,IR(33, 3),IR(49770, 10),IR(1, 0)}, // u_mad_sat in opencl_std_100
    {155,IR(33, 3),IR(49780, 10),IR(1, 0)}, // s_mad_sat in opencl_std_100
    {156,IR(36, 2),IR(49790, 6),IR(1, 0)}, // s_max in opencl_std_100
    {157,IR(36, 2),IR(49796, 6),IR(1, 0)}, // u_max in opencl_std_100
    {158,IR(36, 2),IR(49802, 6),IR(1, 0)}, // s_min in opencl_std_100
    {159,IR(36, 2),IR(49808, 6),IR(1, 0)}, // u_min in opencl_std_100
    {160,IR(36, 2),IR(49814, 9),IR(1, 0)}, // s_mul_hi in opencl_std_100
    {161,IR(36, 2),IR(49823, 7),IR(1, 0)}, // rotate in opencl_std_100
    {162,IR(36, 2),IR(49830, 10),IR(1, 0)}, // s_sub_sat in opencl_std_100
    {163,IR(36, 2),IR(49840, 10),IR(1, 0)}, // u_sub_sat in opencl_std_100
    {164,IR(36, 2),IR(49850, 11),IR(1, 0)}, // u_upsample in opencl_std_100
    {165,IR(36, 2),IR(49861, 11),IR(1, 0)}, // s_upsample in opencl_std_100
    {166,IR(10, 1),IR(49872, 9),IR(1, 0)}, // popcount in opencl_std_100
    {167,IR(33, 3),IR(49881, 8),IR(1, 0)}, // s_mad24 in opencl_std_100
    {168,IR(33, 3),IR(49889, 8),IR(1, 0)}, // u_mad24 in opencl_std_100
    {169,IR(36, 2),IR(49897, 8),IR(1, 0)}, // s_mul24 in opencl_std_100
    {170,IR(36, 2),IR(49905, 8),IR(1, 0)}, // u_mul24 in opencl_std_100
    {171,IR(1106, 3),IR(49913, 7),IR(1, 0)}, // vloadn in opencl_std_100
    {172,IR(33, 3),IR(49920, 8),IR(1, 0)}, // vstoren in opencl_std_100
    {173,IR(36, 2),IR(49928, 11),IR(1, 0)}, // vload_half in opencl_std_100
    {174,IR(1106, 3),IR(49939, 12),IR(1, 0)}, // vload_halfn in opencl_std_100
    {175,IR(33, 3),IR(49951, 12),IR(1, 0)}, // vstore_half in opencl_std_100
    {176,IR(1109, 4),IR(49963, 14),IR(1, 0)}, // vstore_half_r in opencl_std_100
    {177,IR(33, 3),IR(49977, 13),IR(1, 0)}, // vstore_halfn in opencl_std_100
    {178,IR(1109, 4),IR(49990, 15),IR(1, 0)}, // vstore_halfn_r in opencl_std_100
    {179,IR(1106, 3),IR(50005, 13),IR(1, 0)}, // vloada_halfn in opencl_std_100
    {180,IR(33, 3),IR(50018, 14),IR(1, 0)}, // vstorea_halfn in opencl_std_100
    {181,IR(1109, 4),IR(50032, 16),IR(1, 0)}, // vstorea_halfn_r in opencl_std_100
    {182,IR(36, 2),IR(50048, 8),IR(1, 0)}, // shuffle in opencl_std_100
    {183,IR(33, 3),IR(50056, 9),IR(1, 0)}, // shuffle2 in opencl_std_100
    {184,IR(168, 2),IR(50065, 7),IR(1, 0)}, // printf in opencl_std_100
    {185,IR(36, 2),IR(50072, 9),IR(1, 0)}, // prefetch in opencl_std_100
    {186,IR(33, 3),IR(50081, 10),IR(1, 0)}, // bitselect in opencl_std_100
    {187,IR(33, 3),IR(50091, 7),IR(1, 0)}, // select in opencl_std_100
    {201,IR(10, 1),IR(50098, 6),IR(1, 0)}, // u_abs in opencl_std_100
    {202,IR(36, 2),IR(50104, 11),IR(1, 0)}, // u_abs_diff in opencl_std_100
    {203,IR(36, 2),IR(50115, 9),IR(1, 0)}, // u_mul_hi in opencl_std_100
    {204,IR(33, 3),IR(50124, 9),IR(1, 0)}, // u_mad_hi in opencl_std_100
    {1,IR(10, 1),IR(50133, 17),IR(1, 0)}, // CubeFaceIndexAMD in spv_amd_gcn_shader
    {2,IR(10, 1),IR(50150, 17),IR(1, 0)}, // CubeFaceCoordAMD in spv_amd_gcn_shader
    {3,IR(0, 0),IR(50167, 8),IR(1, 0)}, // TimeAMD in spv_amd_gcn_shader
    {1,IR(36, 2),IR(50175, 22),IR(1, 0)}, // SwizzleInvocationsAMD in spv_amd_shader_ballot
    {2,IR(36, 2),IR(50197, 28),IR(1, 0)}, // SwizzleInvocationsMaskedAMD in spv_amd_shader_ballot
    {3,IR(33, 3),IR(50225, 19),IR(1, 0)}, // WriteInvocationAMD in spv_amd_shader_ballot
    {4,IR(10, 1),IR(50244, 9),IR(1, 0)}, // MbcntAMD in spv_amd_shader_ballot
    {1,IR(36, 2),IR(50253, 23),IR(1, 0)}, // InterpolateAtVertexAMD in spv_amd_shader_explicit_vertex_parameter
    {1,IR(33, 3),IR(50276, 9),IR(1, 0)}, // FMin3AMD in spv_amd_shader_trinary_minmax
    {2,IR(33, 3),IR(50285, 9),IR(1, 0)}, // UMin3AMD in spv_amd_shader_trinary_minmax
    {3,IR(33, 3),IR(50294, 9),IR(1, 0)}, // SMin3AMD in spv_amd_shader_trinary_minmax
    {4,IR(33, 3),IR(50303, 9),IR(1, 0)}, // FMax3AMD in spv_amd_shader_trinary_minmax
    {5,IR(33, 3),IR(50312, 9),IR(1, 0)}, // UMax3AMD in spv_amd_shader_trinary_minmax
    {6,IR(33, 3),IR(50321, 9),IR(1, 0)}, // SMax3AMD in spv_amd_shader_trinary_minmax
    {7,IR(33, 3),IR(50330, 9),IR(1, 0)}, // FMid3AMD in spv_amd_shader_trinary_minmax
    {8,IR(33, 3),IR(50339, 9),IR(1, 0)}, // UMid3AMD in spv_amd_shader_trinary_minmax
    {9,IR(33, 3),IR(50348, 9),IR(1, 0)}, // SMid3AMD in spv_amd_shader_trinary_minmax
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
    {IR(45624, 21), 1}, // DebugCompilationUnit in debuginfo
    {IR(46351, 13), 28}, // DebugDeclare in debuginfo
    {IR(46423, 16), 31}, // DebugExpression in debuginfo
    {IR(46167, 14), 20}, // DebugFunction in debuginfo
    {IR(46142, 25), 19}, // DebugFunctionDeclaration in debuginfo
    {IR(46122, 20), 18}, // DebugGlobalVariable in debuginfo
    {IR(45610, 14), 0}, // DebugInfoNone in debuginfo
    {IR(46254, 15), 25}, // DebugInlinedAt in debuginfo
    {IR(46330, 21), 27}, // DebugInlinedVariable in debuginfo
    {IR(46181, 18), 21}, // DebugLexicalBlock in debuginfo
    {IR(46199, 31), 22}, // DebugLexicalBlockDiscriminator in debuginfo
    {IR(46311, 19), 26}, // DebugLocalVariable in debuginfo
    {IR(46439, 14), 32}, // DebugMacroDef in debuginfo
    {IR(46453, 16), 33}, // DebugMacroUndef in debuginfo
    {IR(46241, 13), 24}, // DebugNoScope in debuginfo
    {IR(46408, 15), 30}, // DebugOperation in debuginfo
    {IR(46230, 11), 23}, // DebugScope in debuginfo
    {IR(45820, 15), 5}, // DebugTypeArray in debuginfo
    {IR(45697, 15), 2}, // DebugTypeBasic in debuginfo
    {IR(45934, 19), 10}, // DebugTypeComposite in debuginfo
    {IR(45882, 14), 9}, // DebugTypeEnum in debuginfo
    {IR(45864, 18), 8}, // DebugTypeFunction in debuginfo
    {IR(45969, 21), 12}, // DebugTypeInheritance in debuginfo
    {IR(45953, 16), 11}, // DebugTypeMember in debuginfo
    {IR(45746, 17), 3}, // DebugTypePointer in debuginfo
    {IR(45990, 21), 13}, // DebugTypePtrToMember in debuginfo
    {IR(45801, 19), 4}, // DebugTypeQualifier in debuginfo
    {IR(46011, 18), 14}, // DebugTypeTemplate in debuginfo
    {IR(46029, 27), 15}, // DebugTypeTemplateParameter in debuginfo
    {IR(46091, 31), 17}, // DebugTypeTemplateParameterPack in debuginfo
    {IR(46056, 35), 16}, // DebugTypeTemplateTemplateParameter in debuginfo
    {IR(45835, 16), 6}, // DebugTypeVector in debuginfo
    {IR(45851, 13), 7}, // DebugTypedef in debuginfo
    {IR(46364, 11), 29}, // DebugValue in debuginfo
    {IR(46563, 5), 50}, // Acos in glsl_std_450
    {IR(46594, 6), 56}, // Acosh in glsl_std_450
    {IR(46558, 5), 49}, // Asin in glsl_std_450
    {IR(46588, 6), 55}, // Asinh in glsl_std_450
    {IR(46568, 5), 51}, // Atan in glsl_std_450
    {IR(46606, 6), 58}, // Atan2 in glsl_std_450
    {IR(46600, 6), 57}, // Atanh in glsl_std_450
    {IR(46519, 5), 42}, // Ceil in glsl_std_450
    {IR(46550, 4), 47}, // Cos in glsl_std_450
    {IR(46578, 5), 53}, // Cosh in glsl_std_450
    {IR(46990, 6), 101}, // Cross in glsl_std_450
    {IR(46538, 8), 45}, // Degrees in glsl_std_450
    {IR(46651, 12), 66}, // Determinant in glsl_std_450
    {IR(46981, 9), 100}, // Distance in glsl_std_450
    {IR(46616, 4), 60}, // Exp in glsl_std_450
    {IR(46624, 5), 62}, // Exp2 in glsl_std_450
    {IR(46491, 5), 37}, // FAbs in glsl_std_450
    {IR(46723, 7), 76}, // FClamp in glsl_std_450
    {IR(46708, 5), 73}, // FMax in glsl_std_450
    {IR(46693, 5), 70}, // FMin in glsl_std_450
    {IR(46744, 5), 79}, // FMix in glsl_std_450
    {IR(46501, 6), 39}, // FSign in glsl_std_450
    {IR(47006, 12), 103}, // FaceForward in glsl_std_450
    {IR(47034, 9), 106}, // FindILsb in glsl_std_450
    {IR(47043, 9), 107}, // FindSMsb in glsl_std_450
    {IR(47052, 9), 108}, // FindUMsb in glsl_std_450
    {IR(46513, 6), 41}, // Floor in glsl_std_450
    {IR(46770, 4), 83}, // Fma in glsl_std_450
    {IR(46524, 6), 43}, // Fract in glsl_std_450
    {IR(46774, 6), 84}, // Frexp in glsl_std_450
    {IR(46780, 12), 85}, // FrexpStruct in glsl_std_450
    {IR(46749, 5), 80}, // IMix in glsl_std_450
    {IR(47061, 22), 109}, // InterpolateAtCentroid in glsl_std_450
    {IR(47103, 20), 111}, // InterpolateAtOffset in glsl_std_450
    {IR(47083, 20), 110}, // InterpolateAtSample in glsl_std_450
    {IR(46639, 12), 65}, // InverseSqrt in glsl_std_450
    {IR(46792, 6), 86}, // Ldexp in glsl_std_450
    {IR(46974, 7), 99}, // Length in glsl_std_450
    {IR(46620, 4), 61}, // Log in glsl_std_450
    {IR(46629, 5), 63}, // Log2 in glsl_std_450
    {IR(46663, 14), 67}, // MatrixInverse in glsl_std_450
    {IR(46677, 5), 68}, // Modf in glsl_std_450
    {IR(46682, 11), 69}, // ModfStruct in glsl_std_450
    {IR(47133, 7), 114}, // NClamp in glsl_std_450
    {IR(47128, 5), 113}, // NMax in glsl_std_450
    {IR(47123, 5), 112}, // NMin in glsl_std_450
    {IR(46996, 10), 102}, // Normalize in glsl_std_450
    {IR(46865, 15), 92}, // PackDouble2x32 in glsl_std_450
    {IR(46852, 13), 91}, // PackHalf2x16 in glsl_std_450
    {IR(46824, 14), 89}, // PackSnorm2x16 in glsl_std_450
    {IR(46798, 13), 87}, // PackSnorm4x8 in glsl_std_450
    {IR(46838, 14), 90}, // PackUnorm2x16 in glsl_std_450
    {IR(46811, 13), 88}, // PackUnorm4x8 in glsl_std_450
    {IR(46612, 4), 59}, // Pow in glsl_std_450
    {IR(46530, 8), 44}, // Radians in glsl_std_450
    {IR(47018, 8), 104}, // Reflect in glsl_std_450
    {IR(47026, 8), 105}, // Refract in glsl_std_450
    {IR(46469, 6), 34}, // Round in glsl_std_450
    {IR(46475, 10), 35}, // RoundEven in glsl_std_450
    {IR(46496, 5), 38}, // SAbs in glsl_std_450
    {IR(46737, 7), 78}, // SClamp in glsl_std_450
    {IR(46718, 5), 75}, // SMax in glsl_std_450
    {IR(46703, 5), 72}, // SMin in glsl_std_450
    {IR(46507, 6), 40}, // SSign in glsl_std_450
    {IR(46546, 4), 46}, // Sin in glsl_std_450
    {IR(46573, 5), 52}, // Sinh in glsl_std_450
    {IR(46759, 11), 82}, // SmoothStep in glsl_std_450
    {IR(46634, 5), 64}, // Sqrt in glsl_std_450
    {IR(46754, 5), 81}, // Step in glsl_std_450
    {IR(46554, 4), 48}, // Tan in glsl_std_450
    {IR(46583, 5), 54}, // Tanh in glsl_std_450
    {IR(46485, 6), 36}, // Trunc in glsl_std_450
    {IR(46730, 7), 77}, // UClamp in glsl_std_450
    {IR(46713, 5), 74}, // UMax in glsl_std_450
    {IR(46698, 5), 71}, // UMin in glsl_std_450
    {IR(46957, 17), 98}, // UnpackDouble2x32 in glsl_std_450
    {IR(46912, 15), 95}, // UnpackHalf2x16 in glsl_std_450
    {IR(46880, 16), 93}, // UnpackSnorm2x16 in glsl_std_450
    {IR(46927, 15), 96}, // UnpackSnorm4x8 in glsl_std_450
    {IR(46896, 16), 94}, // UnpackUnorm2x16 in glsl_std_450
    {IR(46942, 15), 97}, // UnpackUnorm4x8 in glsl_std_450
    {IR(47140, 13), 116}, // ArgumentInfo in nonsemantic_clspvreflection
    {IR(47235, 24), 121}, // ArgumentPodPushConstant in nonsemantic_clspvreflection
    {IR(47191, 25), 119}, // ArgumentPodStorageBuffer in nonsemantic_clspvreflection
    {IR(47216, 19), 120}, // ArgumentPodUniform in nonsemantic_clspvreflection
    {IR(47669, 28), 140}, // ArgumentPointerPushConstant in nonsemantic_clspvreflection
    {IR(47697, 23), 141}, // ArgumentPointerUniform in nonsemantic_clspvreflection
    {IR(47259, 21), 122}, // ArgumentSampledImage in nonsemantic_clspvreflection
    {IR(47301, 16), 124}, // ArgumentSampler in nonsemantic_clspvreflection
    {IR(47153, 22), 117}, // ArgumentStorageBuffer in nonsemantic_clspvreflection
    {IR(47280, 21), 123}, // ArgumentStorageImage in nonsemantic_clspvreflection
    {IR(47957, 27), 148}, // ArgumentStorageTexelBuffer in nonsemantic_clspvreflection
    {IR(47175, 16), 118}, // ArgumentUniform in nonsemantic_clspvreflection
    {IR(47984, 27), 149}, // ArgumentUniformTexelBuffer in nonsemantic_clspvreflection
    {IR(47317, 18), 125}, // ArgumentWorkgroup in nonsemantic_clspvreflection
    {IR(48011, 32), 150}, // ConstantDataPointerPushConstant in nonsemantic_clspvreflection
    {IR(47565, 26), 135}, // ConstantDataStorageBuffer in nonsemantic_clspvreflection
    {IR(47591, 20), 136}, // ConstantDataUniform in nonsemantic_clspvreflection
    {IR(47835, 45), 145}, // ImageArgumentInfoChannelDataTypePushConstant in nonsemantic_clspvreflection
    {IR(47917, 40), 147}, // ImageArgumentInfoChannelDataTypeUniform in nonsemantic_clspvreflection
    {IR(47793, 42), 144}, // ImageArgumentInfoChannelOrderPushConstant in nonsemantic_clspvreflection
    {IR(47880, 37), 146}, // ImageArgumentInfoChannelOrderUniform in nonsemantic_clspvreflection
    {IR(4642, 7), 115}, // Kernel in nonsemantic_clspvreflection
    {IR(8067, 15), 137}, // LiteralSampler in nonsemantic_clspvreflection
    {IR(48152, 34), 155}, // NormalizedSamplerMaskPushConstant in nonsemantic_clspvreflection
    {IR(48120, 32), 154}, // PrintfBufferPointerPushConstant in nonsemantic_clspvreflection
    {IR(48094, 26), 153}, // PrintfBufferStorageBuffer in nonsemantic_clspvreflection
    {IR(48083, 11), 152}, // PrintfInfo in nonsemantic_clspvreflection
    {IR(48043, 40), 151}, // ProgramScopeVariablePointerPushConstant in nonsemantic_clspvreflection
    {IR(47755, 38), 143}, // ProgramScopeVariablePointerRelocation in nonsemantic_clspvreflection
    {IR(47720, 35), 142}, // ProgramScopeVariablesStorageBuffer in nonsemantic_clspvreflection
    {IR(47611, 30), 138}, // PropertyRequiredWorkgroupSize in nonsemantic_clspvreflection
    {IR(47431, 30), 130}, // PushConstantEnqueuedLocalSize in nonsemantic_clspvreflection
    {IR(47406, 25), 129}, // PushConstantGlobalOffset in nonsemantic_clspvreflection
    {IR(47461, 23), 131}, // PushConstantGlobalSize in nonsemantic_clspvreflection
    {IR(47509, 26), 133}, // PushConstantNumWorkgroups in nonsemantic_clspvreflection
    {IR(47535, 30), 134}, // PushConstantRegionGroupOffset in nonsemantic_clspvreflection
    {IR(47484, 25), 132}, // PushConstantRegionOffset in nonsemantic_clspvreflection
    {IR(47361, 25), 127}, // SpecConstantGlobalOffset in nonsemantic_clspvreflection
    {IR(47641, 28), 139}, // SpecConstantSubgroupMaxSize in nonsemantic_clspvreflection
    {IR(47386, 20), 128}, // SpecConstantWorkDim in nonsemantic_clspvreflection
    {IR(47335, 26), 126}, // SpecConstantWorkgroupSize in nonsemantic_clspvreflection
    {IR(48186, 22), 156}, // WorkgroupVariableSize in nonsemantic_clspvreflection
    {IR(48307, 21), 197}, // DebugBuildIdentifier in nonsemantic_shader_debuginfo_100
    {IR(45624, 21), 158}, // DebugCompilationUnit in nonsemantic_shader_debuginfo_100
    {IR(46351, 13), 185}, // DebugDeclare in nonsemantic_shader_debuginfo_100
    {IR(48345, 16), 199}, // DebugEntryPoint in nonsemantic_shader_debuginfo_100
    {IR(46423, 16), 188}, // DebugExpression in nonsemantic_shader_debuginfo_100
    {IR(46167, 14), 177}, // DebugFunction in nonsemantic_shader_debuginfo_100
    {IR(46142, 25), 176}, // DebugFunctionDeclaration in nonsemantic_shader_debuginfo_100
    {IR(48240, 24), 193}, // DebugFunctionDefinition in nonsemantic_shader_debuginfo_100
    {IR(46122, 20), 175}, // DebugGlobalVariable in nonsemantic_shader_debuginfo_100
    {IR(48208, 20), 191}, // DebugImportedEntity in nonsemantic_shader_debuginfo_100
    {IR(45610, 14), 157}, // DebugInfoNone in nonsemantic_shader_debuginfo_100
    {IR(46254, 15), 182}, // DebugInlinedAt in nonsemantic_shader_debuginfo_100
    {IR(46330, 21), 184}, // DebugInlinedVariable in nonsemantic_shader_debuginfo_100
    {IR(46181, 18), 178}, // DebugLexicalBlock in nonsemantic_shader_debuginfo_100
    {IR(46199, 31), 179}, // DebugLexicalBlockDiscriminator in nonsemantic_shader_debuginfo_100
    {IR(48285, 10), 195}, // DebugLine in nonsemantic_shader_debuginfo_100
    {IR(46311, 19), 183}, // DebugLocalVariable in nonsemantic_shader_debuginfo_100
    {IR(46439, 14), 189}, // DebugMacroDef in nonsemantic_shader_debuginfo_100
    {IR(46453, 16), 190}, // DebugMacroUndef in nonsemantic_shader_debuginfo_100
    {IR(48295, 12), 196}, // DebugNoLine in nonsemantic_shader_debuginfo_100
    {IR(46241, 13), 181}, // DebugNoScope in nonsemantic_shader_debuginfo_100
    {IR(46408, 15), 187}, // DebugOperation in nonsemantic_shader_debuginfo_100
    {IR(46230, 11), 180}, // DebugScope in nonsemantic_shader_debuginfo_100
    {IR(48228, 12), 192}, // DebugSource in nonsemantic_shader_debuginfo_100
    {IR(48264, 21), 194}, // DebugSourceContinued in nonsemantic_shader_debuginfo_100
    {IR(48328, 17), 198}, // DebugStoragePath in nonsemantic_shader_debuginfo_100
    {IR(45820, 15), 162}, // DebugTypeArray in nonsemantic_shader_debuginfo_100
    {IR(45697, 15), 159}, // DebugTypeBasic in nonsemantic_shader_debuginfo_100
    {IR(45934, 19), 167}, // DebugTypeComposite in nonsemantic_shader_debuginfo_100
    {IR(45882, 14), 166}, // DebugTypeEnum in nonsemantic_shader_debuginfo_100
    {IR(45864, 18), 165}, // DebugTypeFunction in nonsemantic_shader_debuginfo_100
    {IR(45969, 21), 169}, // DebugTypeInheritance in nonsemantic_shader_debuginfo_100
    {IR(48361, 16), 200}, // DebugTypeMatrix in nonsemantic_shader_debuginfo_100
    {IR(45953, 16), 168}, // DebugTypeMember in nonsemantic_shader_debuginfo_100
    {IR(45746, 17), 160}, // DebugTypePointer in nonsemantic_shader_debuginfo_100
    {IR(45990, 21), 170}, // DebugTypePtrToMember in nonsemantic_shader_debuginfo_100
    {IR(45801, 19), 161}, // DebugTypeQualifier in nonsemantic_shader_debuginfo_100
    {IR(46011, 18), 171}, // DebugTypeTemplate in nonsemantic_shader_debuginfo_100
    {IR(46029, 27), 172}, // DebugTypeTemplateParameter in nonsemantic_shader_debuginfo_100
    {IR(46091, 31), 174}, // DebugTypeTemplateParameterPack in nonsemantic_shader_debuginfo_100
    {IR(46056, 35), 173}, // DebugTypeTemplateTemplateParameter in nonsemantic_shader_debuginfo_100
    {IR(45835, 16), 163}, // DebugTypeVector in nonsemantic_shader_debuginfo_100
    {IR(45851, 13), 164}, // DebugTypedef in nonsemantic_shader_debuginfo_100
    {IR(46364, 11), 186}, // DebugValue in nonsemantic_shader_debuginfo_100
    {IR(48377, 14), 201}, // Configuration in nonsemantic_vkspreflection
    {IR(48453, 20), 206}, // DescriptorSetBuffer in nonsemantic_vkspreflection
    {IR(48473, 19), 207}, // DescriptorSetImage in nonsemantic_vkspreflection
    {IR(48492, 21), 208}, // DescriptorSetSampler in nonsemantic_vkspreflection
    {IR(48416, 14), 204}, // PushConstants in nonsemantic_vkspreflection
    {IR(48430, 23), 205}, // SpecializationMapEntry in nonsemantic_vkspreflection
    {IR(48391, 13), 202}, // StartCounter in nonsemantic_vkspreflection
    {IR(48404, 12), 203}, // StopCounter in nonsemantic_vkspreflection
    {IR(45624, 21), 210}, // DebugCompilationUnit in opencl_debuginfo_100
    {IR(46351, 13), 237}, // DebugDeclare in opencl_debuginfo_100
    {IR(46423, 16), 240}, // DebugExpression in opencl_debuginfo_100
    {IR(46167, 14), 229}, // DebugFunction in opencl_debuginfo_100
    {IR(46142, 25), 228}, // DebugFunctionDeclaration in opencl_debuginfo_100
    {IR(46122, 20), 227}, // DebugGlobalVariable in opencl_debuginfo_100
    {IR(48208, 20), 243}, // DebugImportedEntity in opencl_debuginfo_100
    {IR(45610, 14), 209}, // DebugInfoNone in opencl_debuginfo_100
    {IR(46254, 15), 234}, // DebugInlinedAt in opencl_debuginfo_100
    {IR(46330, 21), 236}, // DebugInlinedVariable in opencl_debuginfo_100
    {IR(46181, 18), 230}, // DebugLexicalBlock in opencl_debuginfo_100
    {IR(46199, 31), 231}, // DebugLexicalBlockDiscriminator in opencl_debuginfo_100
    {IR(46311, 19), 235}, // DebugLocalVariable in opencl_debuginfo_100
    {IR(46439, 14), 241}, // DebugMacroDef in opencl_debuginfo_100
    {IR(46453, 16), 242}, // DebugMacroUndef in opencl_debuginfo_100
    {IR(48813, 17), 245}, // DebugModuleINTEL in opencl_debuginfo_100
    {IR(46241, 13), 233}, // DebugNoScope in opencl_debuginfo_100
    {IR(46408, 15), 239}, // DebugOperation in opencl_debuginfo_100
    {IR(46230, 11), 232}, // DebugScope in opencl_debuginfo_100
    {IR(48228, 12), 244}, // DebugSource in opencl_debuginfo_100
    {IR(45820, 15), 214}, // DebugTypeArray in opencl_debuginfo_100
    {IR(45697, 15), 211}, // DebugTypeBasic in opencl_debuginfo_100
    {IR(45934, 19), 219}, // DebugTypeComposite in opencl_debuginfo_100
    {IR(45882, 14), 218}, // DebugTypeEnum in opencl_debuginfo_100
    {IR(45864, 18), 217}, // DebugTypeFunction in opencl_debuginfo_100
    {IR(45969, 21), 221}, // DebugTypeInheritance in opencl_debuginfo_100
    {IR(45953, 16), 220}, // DebugTypeMember in opencl_debuginfo_100
    {IR(45746, 17), 212}, // DebugTypePointer in opencl_debuginfo_100
    {IR(45990, 21), 222}, // DebugTypePtrToMember in opencl_debuginfo_100
    {IR(45801, 19), 213}, // DebugTypeQualifier in opencl_debuginfo_100
    {IR(46011, 18), 223}, // DebugTypeTemplate in opencl_debuginfo_100
    {IR(46029, 27), 224}, // DebugTypeTemplateParameter in opencl_debuginfo_100
    {IR(46091, 31), 226}, // DebugTypeTemplateParameterPack in opencl_debuginfo_100
    {IR(46056, 35), 225}, // DebugTypeTemplateTemplateParameter in opencl_debuginfo_100
    {IR(45835, 16), 215}, // DebugTypeVector in opencl_debuginfo_100
    {IR(45851, 13), 216}, // DebugTypedef in opencl_debuginfo_100
    {IR(46364, 11), 238}, // DebugValue in opencl_debuginfo_100
    {IR(48830, 5), 246}, // acos in opencl_std_100
    {IR(48835, 6), 247}, // acosh in opencl_std_100
    {IR(48841, 7), 248}, // acospi in opencl_std_100
    {IR(48848, 5), 249}, // asin in opencl_std_100
    {IR(48853, 6), 250}, // asinh in opencl_std_100
    {IR(48859, 7), 251}, // asinpi in opencl_std_100
    {IR(48866, 5), 252}, // atan in opencl_std_100
    {IR(48871, 6), 253}, // atan2 in opencl_std_100
    {IR(48890, 8), 256}, // atan2pi in opencl_std_100
    {IR(48877, 6), 254}, // atanh in opencl_std_100
    {IR(48883, 7), 255}, // atanpi in opencl_std_100
    {IR(50081, 10), 402}, // bitselect in opencl_std_100
    {IR(48898, 5), 257}, // cbrt in opencl_std_100
    {IR(48903, 5), 258}, // ceil in opencl_std_100
    {IR(49753, 4), 367}, // clz in opencl_std_100
    {IR(48908, 9), 259}, // copysign in opencl_std_100
    {IR(48917, 4), 260}, // cos in opencl_std_100
    {IR(48921, 5), 261}, // cosh in opencl_std_100
    {IR(48926, 6), 262}, // cospi in opencl_std_100
    {IR(49597, 6), 350}, // cross in opencl_std_100
    {IR(49757, 4), 368}, // ctz in opencl_std_100
    {IR(49532, 8), 342}, // degrees in opencl_std_100
    {IR(49603, 9), 351}, // distance in opencl_std_100
    {IR(48937, 4), 264}, // erf in opencl_std_100
    {IR(48932, 5), 263}, // erfc in opencl_std_100
    {IR(48941, 4), 265}, // exp in opencl_std_100
    {IR(48950, 6), 267}, // exp10 in opencl_std_100
    {IR(48945, 5), 266}, // exp2 in opencl_std_100
    {IR(48956, 6), 268}, // expm1 in opencl_std_100
    {IR(48962, 5), 269}, // fabs in opencl_std_100
    {IR(49629, 14), 354}, // fast_distance in opencl_std_100
    {IR(49643, 12), 355}, // fast_length in opencl_std_100
    {IR(49655, 15), 356}, // fast_normalize in opencl_std_100
    {IR(49525, 7), 341}, // fclamp in opencl_std_100
    {IR(48967, 5), 270}, // fdim in opencl_std_100
    {IR(48972, 6), 271}, // floor in opencl_std_100
    {IR(48978, 4), 272}, // fma in opencl_std_100
    {IR(48982, 5), 273}, // fmax in opencl_std_100
    {IR(49540, 12), 343}, // fmax_common in opencl_std_100
    {IR(48987, 5), 274}, // fmin in opencl_std_100
    {IR(49552, 12), 344}, // fmin_common in opencl_std_100
    {IR(48992, 5), 275}, // fmod in opencl_std_100
    {IR(48997, 6), 276}, // fract in opencl_std_100
    {IR(49003, 6), 277}, // frexp in opencl_std_100
    {IR(49215, 9), 313}, // half_cos in opencl_std_100
    {IR(49224, 12), 314}, // half_divide in opencl_std_100
    {IR(49236, 9), 315}, // half_exp in opencl_std_100
    {IR(49255, 11), 317}, // half_exp10 in opencl_std_100
    {IR(49245, 10), 316}, // half_exp2 in opencl_std_100
    {IR(49266, 9), 318}, // half_log in opencl_std_100
    {IR(49285, 11), 320}, // half_log10 in opencl_std_100
    {IR(49275, 10), 319}, // half_log2 in opencl_std_100
    {IR(49296, 10), 321}, // half_powr in opencl_std_100
    {IR(49306, 11), 322}, // half_recip in opencl_std_100
    {IR(49317, 11), 323}, // half_rsqrt in opencl_std_100
    {IR(49328, 9), 324}, // half_sin in opencl_std_100
    {IR(49337, 10), 325}, // half_sqrt in opencl_std_100
    {IR(49347, 9), 326}, // half_tan in opencl_std_100
    {IR(49009, 6), 278}, // hypot in opencl_std_100
    {IR(49015, 6), 279}, // ilogb in opencl_std_100
    {IR(49021, 6), 280}, // ldexp in opencl_std_100
    {IR(49612, 7), 352}, // length in opencl_std_100
    {IR(49027, 7), 281}, // lgamma in opencl_std_100
    {IR(49034, 9), 282}, // lgamma_r in opencl_std_100
    {IR(49043, 4), 283}, // log in opencl_std_100
    {IR(49052, 6), 285}, // log10 in opencl_std_100
    {IR(49058, 6), 286}, // log1p in opencl_std_100
    {IR(49047, 5), 284}, // log2 in opencl_std_100
    {IR(49064, 5), 287}, // logb in opencl_std_100
    {IR(49069, 4), 288}, // mad in opencl_std_100
    {IR(49073, 7), 289}, // maxmag in opencl_std_100
    {IR(49080, 7), 290}, // minmag in opencl_std_100
    {IR(49564, 4), 345}, // mix in opencl_std_100
    {IR(49087, 5), 291}, // modf in opencl_std_100
    {IR(49092, 4), 292}, // nan in opencl_std_100
    {IR(49356, 11), 327}, // native_cos in opencl_std_100
    {IR(49367, 14), 328}, // native_divide in opencl_std_100
    {IR(49381, 11), 329}, // native_exp in opencl_std_100
    {IR(49404, 13), 331}, // native_exp10 in opencl_std_100
    {IR(49392, 12), 330}, // native_exp2 in opencl_std_100
    {IR(49417, 11), 332}, // native_log in opencl_std_100
    {IR(49440, 13), 334}, // native_log10 in opencl_std_100
    {IR(49428, 12), 333}, // native_log2 in opencl_std_100
    {IR(49453, 12), 335}, // native_powr in opencl_std_100
    {IR(49465, 13), 336}, // native_recip in opencl_std_100
    {IR(49478, 13), 337}, // native_rsqrt in opencl_std_100
    {IR(49491, 11), 338}, // native_sin in opencl_std_100
    {IR(49502, 12), 339}, // native_sqrt in opencl_std_100
    {IR(49514, 11), 340}, // native_tan in opencl_std_100
    {IR(49096, 10), 293}, // nextafter in opencl_std_100
    {IR(49619, 10), 353}, // normalize in opencl_std_100
    {IR(49872, 9), 382}, // popcount in opencl_std_100
    {IR(49106, 4), 294}, // pow in opencl_std_100
    {IR(49110, 5), 295}, // pown in opencl_std_100
    {IR(49115, 5), 296}, // powr in opencl_std_100
    {IR(50072, 9), 401}, // prefetch in opencl_std_100
    {IR(50065, 7), 400}, // printf in opencl_std_100
    {IR(49568, 8), 346}, // radians in opencl_std_100
    {IR(49120, 10), 297}, // remainder in opencl_std_100
    {IR(49130, 7), 298}, // remquo in opencl_std_100
    {IR(49137, 5), 299}, // rint in opencl_std_100
    {IR(49142, 6), 300}, // rootn in opencl_std_100
    {IR(49823, 7), 377}, // rotate in opencl_std_100
    {IR(49148, 6), 301}, // round in opencl_std_100
    {IR(49154, 6), 302}, // rsqrt in opencl_std_100
    {IR(49670, 6), 357}, // s_abs in opencl_std_100
    {IR(49676, 11), 358}, // s_abs_diff in opencl_std_100
    {IR(49687, 10), 359}, // s_add_sat in opencl_std_100
    {IR(49737, 8), 365}, // s_clamp in opencl_std_100
    {IR(49707, 7), 361}, // s_hadd in opencl_std_100
    {IR(49881, 8), 383}, // s_mad24 in opencl_std_100
    {IR(49761, 9), 369}, // s_mad_hi in opencl_std_100
    {IR(49780, 10), 371}, // s_mad_sat in opencl_std_100
    {IR(49790, 6), 372}, // s_max in opencl_std_100
    {IR(49802, 6), 374}, // s_min in opencl_std_100
    {IR(49897, 8), 385}, // s_mul24 in opencl_std_100
    {IR(49814, 9), 376}, // s_mul_hi in opencl_std_100
    {IR(49721, 8), 363}, // s_rhadd in opencl_std_100
    {IR(49830, 10), 378}, // s_sub_sat in opencl_std_100
    {IR(49861, 11), 381}, // s_upsample in opencl_std_100
    {IR(50091, 7), 403}, // select in opencl_std_100
    {IR(50048, 8), 398}, // shuffle in opencl_std_100
    {IR(50056, 9), 399}, // shuffle2 in opencl_std_100
    {IR(49592, 5), 349}, // sign in opencl_std_100
    {IR(49160, 4), 303}, // sin in opencl_std_100
    {IR(49164, 7), 304}, // sincos in opencl_std_100
    {IR(49171, 5), 305}, // sinh in opencl_std_100
    {IR(49176, 6), 306}, // sinpi in opencl_std_100
    {IR(49581, 11), 348}, // smoothstep in opencl_std_100
    {IR(49182, 5), 307}, // sqrt in opencl_std_100
    {IR(49576, 5), 347}, // step in opencl_std_100
    {IR(49187, 4), 308}, // tan in opencl_std_100
    {IR(49191, 5), 309}, // tanh in opencl_std_100
    {IR(49196, 6), 310}, // tanpi in opencl_std_100
    {IR(49202, 7), 311}, // tgamma in opencl_std_100
    {IR(49209, 6), 312}, // trunc in opencl_std_100
    {IR(50098, 6), 404}, // u_abs in opencl_std_100
    {IR(50104, 11), 405}, // u_abs_diff in opencl_std_100
    {IR(49697, 10), 360}, // u_add_sat in opencl_std_100
    {IR(49745, 8), 366}, // u_clamp in opencl_std_100
    {IR(49714, 7), 362}, // u_hadd in opencl_std_100
    {IR(49889, 8), 384}, // u_mad24 in opencl_std_100
    {IR(50124, 9), 407}, // u_mad_hi in opencl_std_100
    {IR(49770, 10), 370}, // u_mad_sat in opencl_std_100
    {IR(49796, 6), 373}, // u_max in opencl_std_100
    {IR(49808, 6), 375}, // u_min in opencl_std_100
    {IR(49905, 8), 386}, // u_mul24 in opencl_std_100
    {IR(50115, 9), 406}, // u_mul_hi in opencl_std_100
    {IR(49729, 8), 364}, // u_rhadd in opencl_std_100
    {IR(49840, 10), 379}, // u_sub_sat in opencl_std_100
    {IR(49850, 11), 380}, // u_upsample in opencl_std_100
    {IR(49928, 11), 389}, // vload_half in opencl_std_100
    {IR(49939, 12), 390}, // vload_halfn in opencl_std_100
    {IR(50005, 13), 395}, // vloada_halfn in opencl_std_100
    {IR(49913, 7), 387}, // vloadn in opencl_std_100
    {IR(49951, 12), 391}, // vstore_half in opencl_std_100
    {IR(49963, 14), 392}, // vstore_half_r in opencl_std_100
    {IR(49977, 13), 393}, // vstore_halfn in opencl_std_100
    {IR(49990, 15), 394}, // vstore_halfn_r in opencl_std_100
    {IR(50018, 14), 396}, // vstorea_halfn in opencl_std_100
    {IR(50032, 16), 397}, // vstorea_halfn_r in opencl_std_100
    {IR(49920, 8), 388}, // vstoren in opencl_std_100
    {IR(50150, 17), 409}, // CubeFaceCoordAMD in spv_amd_gcn_shader
    {IR(50133, 17), 408}, // CubeFaceIndexAMD in spv_amd_gcn_shader
    {IR(50167, 8), 410}, // TimeAMD in spv_amd_gcn_shader
    {IR(50244, 9), 414}, // MbcntAMD in spv_amd_shader_ballot
    {IR(50175, 22), 411}, // SwizzleInvocationsAMD in spv_amd_shader_ballot
    {IR(50197, 28), 412}, // SwizzleInvocationsMaskedAMD in spv_amd_shader_ballot
    {IR(50225, 19), 413}, // WriteInvocationAMD in spv_amd_shader_ballot
    {IR(50253, 23), 415}, // InterpolateAtVertexAMD in spv_amd_shader_explicit_vertex_parameter
    {IR(50303, 9), 419}, // FMax3AMD in spv_amd_shader_trinary_minmax
    {IR(50330, 9), 422}, // FMid3AMD in spv_amd_shader_trinary_minmax
    {IR(50276, 9), 416}, // FMin3AMD in spv_amd_shader_trinary_minmax
    {IR(50321, 9), 421}, // SMax3AMD in spv_amd_shader_trinary_minmax
    {IR(50348, 9), 424}, // SMid3AMD in spv_amd_shader_trinary_minmax
    {IR(50294, 9), 418}, // SMin3AMD in spv_amd_shader_trinary_minmax
    {IR(50312, 9), 420}, // UMax3AMD in spv_amd_shader_trinary_minmax
    {IR(50339, 9), 423}, // UMid3AMD in spv_amd_shader_trinary_minmax
    {IR(50285, 9), 417}, // UMin3AMD in spv_amd_shader_trinary_minmax
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
  "SPV_KHR_fma\0" // IR(2894, 12)
  "SPV_KHR_fragment_shader_barycentric\0" // IR(2906, 36)
  "SPV_KHR_fragment_shading_rate\0" // IR(2942, 30)
  "SPV_KHR_integer_dot_product\0" // IR(2972, 28)
  "SPV_KHR_linkonce_odr\0" // IR(3000, 21)
  "SPV_KHR_maximal_reconvergence\0" // IR(3021, 30)
  "SPV_KHR_multiview\0" // IR(3051, 18)
  "SPV_KHR_no_integer_wrap_decoration\0" // IR(3069, 35)
  "SPV_KHR_non_semantic_info\0" // IR(3104, 26)
  "SPV_KHR_physical_storage_buffer\0" // IR(3130, 32)
  "SPV_KHR_post_depth_coverage\0" // IR(3162, 28)
  "SPV_KHR_quad_control\0" // IR(3190, 21)
  "SPV_KHR_ray_cull_mask\0" // IR(3211, 22)
  "SPV_KHR_ray_query\0" // IR(3233, 18)
  "SPV_KHR_ray_tracing\0" // IR(3251, 20)
  "SPV_KHR_ray_tracing_position_fetch\0" // IR(3271, 35)
  "SPV_KHR_relaxed_extended_instruction\0" // IR(3306, 37)
  "SPV_KHR_shader_atomic_counter_ops\0" // IR(3343, 34)
  "SPV_KHR_shader_ballot\0" // IR(3377, 22)
  "SPV_KHR_shader_clock\0" // IR(3399, 21)
  "SPV_KHR_shader_draw_parameters\0" // IR(3420, 31)
  "SPV_KHR_storage_buffer_storage_class\0" // IR(3451, 37)
  "SPV_KHR_subgroup_rotate\0" // IR(3488, 24)
  "SPV_KHR_subgroup_uniform_control_flow\0" // IR(3512, 38)
  "SPV_KHR_subgroup_vote\0" // IR(3550, 22)
  "SPV_KHR_terminate_invocation\0" // IR(3572, 29)
  "SPV_KHR_uniform_group_instructions\0" // IR(3601, 35)
  "SPV_KHR_untyped_pointers\0" // IR(3636, 25)
  "SPV_KHR_variable_pointers\0" // IR(3661, 26)
  "SPV_KHR_vulkan_memory_model\0" // IR(3687, 28)
  "SPV_KHR_workgroup_memory_explicit_layout\0" // IR(3715, 41)
  "SPV_NVX_multiview_per_view_attributes\0" // IR(3756, 38)
  "SPV_NV_bindless_texture\0" // IR(3794, 24)
  "SPV_NV_cluster_acceleration_structure\0" // IR(3818, 38)
  "SPV_NV_compute_shader_derivatives\0" // IR(3856, 34)
  "SPV_NV_cooperative_matrix\0" // IR(3890, 26)
  "SPV_NV_cooperative_matrix2\0" // IR(3916, 27)
  "SPV_NV_cooperative_vector\0" // IR(3943, 26)
  "SPV_NV_displacement_micromap\0" // IR(3969, 29)
  "SPV_NV_fragment_shader_barycentric\0" // IR(3998, 35)
  "SPV_NV_geometry_shader_passthrough\0" // IR(4033, 35)
  "SPV_NV_linear_swept_spheres\0" // IR(4068, 28)
  "SPV_NV_mesh_shader\0" // IR(4096, 19)
  "SPV_NV_raw_access_chains\0" // IR(4115, 25)
  "SPV_NV_ray_tracing\0" // IR(4140, 19)
  "SPV_NV_ray_tracing_motion_blur\0" // IR(4159, 31)
  "SPV_NV_sample_mask_override_coverage\0" // IR(4190, 37)
  "SPV_NV_shader_atomic_fp16_vector\0" // IR(4227, 33)
  "SPV_NV_shader_image_footprint\0" // IR(4260, 30)
  "SPV_NV_shader_invocation_reorder\0" // IR(4290, 33)
  "SPV_NV_shader_sm_builtins\0" // IR(4323, 26)
  "SPV_NV_shader_subgroup_partitioned\0" // IR(4349, 35)
  "SPV_NV_shading_rate\0" // IR(4384, 20)
  "SPV_NV_stereo_view_rendering\0" // IR(4404, 29)
  "SPV_NV_tensor_addressing\0" // IR(4433, 25)
  "SPV_NV_viewport_array2\0" // IR(4458, 23)
  "SPV_QCOM_cooperative_matrix_conversion\0" // IR(4481, 39)
  "SPV_QCOM_image_processing\0" // IR(4520, 26)
  "SPV_QCOM_image_processing2\0" // IR(4546, 27)
  "SPV_QCOM_tile_shading\0" // IR(4573, 22)
  "SPV_VALIDATOR_ignore_type_decl_unique\0" // IR(4595, 38)
  "ReadOnly\0" // IR(4633, 9)
  "Kernel\0" // IR(4642, 7)
  "WriteOnly\0" // IR(4649, 10)
  "ReadWrite\0" // IR(4659, 10)
  "Logical\0" // IR(4669, 8)
  "Physical32\0" // IR(4677, 11)
  "Addresses\0" // IR(4688, 10)
  "Physical64\0" // IR(4698, 11)
  "PhysicalStorageBuffer64\0" // IR(4709, 24)
  "PhysicalStorageBuffer64EXT\0" // IR(4733, 27)
  "PhysicalStorageBufferAddresses\0" // IR(4760, 31)
  "Position\0" // IR(4791, 9)
  "Shader\0" // IR(4800, 7)
  "PointSize\0" // IR(4807, 10)
  "ClipDistance\0" // IR(4817, 13)
  "CullDistance\0" // IR(4830, 13)
  "VertexId\0" // IR(4843, 9)
  "InstanceId\0" // IR(4852, 11)
  "PrimitiveId\0" // IR(4863, 12)
  "Geometry\0" // IR(4875, 9)
  "Tessellation\0" // IR(4884, 13)
  "RayTracingNV\0" // IR(4897, 13)
  "RayTracingKHR\0" // IR(4910, 14)
  "MeshShadingNV\0" // IR(4924, 14)
  "MeshShadingEXT\0" // IR(4938, 15)
  "InvocationId\0" // IR(4953, 13)
  "Layer\0" // IR(4966, 6)
  "ShaderLayer\0" // IR(4972, 12)
  "ShaderViewportIndexLayerEXT\0" // IR(4984, 28)
  "ViewportIndex\0" // IR(5012, 14)
  "MultiViewport\0" // IR(5026, 14)
  "ShaderViewportIndex\0" // IR(5040, 20)
  "TessLevelOuter\0" // IR(5060, 15)
  "TessLevelInner\0" // IR(5075, 15)
  "TessCoord\0" // IR(5090, 10)
  "PatchVertices\0" // IR(5100, 14)
  "FragCoord\0" // IR(5114, 10)
  "PointCoord\0" // IR(5124, 11)
  "FrontFacing\0" // IR(5135, 12)
  "SampleId\0" // IR(5147, 9)
  "SampleRateShading\0" // IR(5156, 18)
  "SamplePosition\0" // IR(5174, 15)
  "SampleMask\0" // IR(5189, 11)
  "FragDepth\0" // IR(5200, 10)
  "HelperInvocation\0" // IR(5210, 17)
  "NumWorkgroups\0" // IR(5227, 14)
  "WorkgroupSize\0" // IR(5241, 14)
  "WorkgroupId\0" // IR(5255, 12)
  "LocalInvocationId\0" // IR(5267, 18)
  "GlobalInvocationId\0" // IR(5285, 19)
  "LocalInvocationIndex\0" // IR(5304, 21)
  "WorkDim\0" // IR(5325, 8)
  "GlobalSize\0" // IR(5333, 11)
  "EnqueuedWorkgroupSize\0" // IR(5344, 22)
  "GlobalOffset\0" // IR(5366, 13)
  "GlobalLinearId\0" // IR(5379, 15)
  "SubgroupSize\0" // IR(5394, 13)
  "GroupNonUniform\0" // IR(5407, 16)
  "SubgroupBallotKHR\0" // IR(5423, 18)
  "SubgroupMaxSize\0" // IR(5441, 16)
  "NumSubgroups\0" // IR(5457, 13)
  "NumEnqueuedSubgroups\0" // IR(5470, 21)
  "SubgroupId\0" // IR(5491, 11)
  "SubgroupLocalInvocationId\0" // IR(5502, 26)
  "VertexIndex\0" // IR(5528, 12)
  "InstanceIndex\0" // IR(5540, 14)
  "CoreIDARM\0" // IR(5554, 10)
  "CoreBuiltinsARM\0" // IR(5564, 16)
  "CoreCountARM\0" // IR(5580, 13)
  "CoreMaxIDARM\0" // IR(5593, 13)
  "WarpIDARM\0" // IR(5606, 10)
  "WarpMaxIDARM\0" // IR(5616, 13)
  "SubgroupEqMask\0" // IR(5629, 15)
  "SubgroupEqMaskKHR\0" // IR(5644, 18)
  "GroupNonUniformBallot\0" // IR(5662, 22)
  "SubgroupGeMask\0" // IR(5684, 15)
  "SubgroupGeMaskKHR\0" // IR(5699, 18)
  "SubgroupGtMask\0" // IR(5717, 15)
  "SubgroupGtMaskKHR\0" // IR(5732, 18)
  "SubgroupLeMask\0" // IR(5750, 15)
  "SubgroupLeMaskKHR\0" // IR(5765, 18)
  "SubgroupLtMask\0" // IR(5783, 15)
  "SubgroupLtMaskKHR\0" // IR(5798, 18)
  "BaseVertex\0" // IR(5816, 11)
  "DrawParameters\0" // IR(5827, 15)
  "BaseInstance\0" // IR(5842, 13)
  "DrawIndex\0" // IR(5855, 10)
  "PrimitiveShadingRateKHR\0" // IR(5865, 24)
  "FragmentShadingRateKHR\0" // IR(5889, 23)
  "DeviceIndex\0" // IR(5912, 12)
  "DeviceGroup\0" // IR(5924, 12)
  "ViewIndex\0" // IR(5936, 10)
  "MultiView\0" // IR(5946, 10)
  "ShadingRateKHR\0" // IR(5956, 15)
  "TileOffsetQCOM\0" // IR(5971, 15)
  "TileShadingQCOM\0" // IR(5986, 16)
  "TileDimensionQCOM\0" // IR(6002, 18)
  "TileApronSizeQCOM\0" // IR(6020, 18)
  "BaryCoordNoPerspAMD\0" // IR(6038, 20)
  "BaryCoordNoPerspCentroidAMD\0" // IR(6058, 28)
  "BaryCoordNoPerspSampleAMD\0" // IR(6086, 26)
  "BaryCoordSmoothAMD\0" // IR(6112, 19)
  "BaryCoordSmoothCentroidAMD\0" // IR(6131, 27)
  "BaryCoordSmoothSampleAMD\0" // IR(6158, 25)
  "BaryCoordPullModelAMD\0" // IR(6183, 22)
  "FragStencilRefEXT\0" // IR(6205, 18)
  "StencilExportEXT\0" // IR(6223, 17)
  "RemainingRecursionLevelsAMDX\0" // IR(6240, 29)
  "ShaderEnqueueAMDX\0" // IR(6269, 18)
  "ShaderIndexAMDX\0" // IR(6287, 16)
  "ViewportMaskNV\0" // IR(6303, 15)
  "ShaderViewportMaskNV\0" // IR(6318, 21)
  "SecondaryPositionNV\0" // IR(6339, 20)
  "ShaderStereoViewNV\0" // IR(6359, 19)
  "SecondaryViewportMaskNV\0" // IR(6378, 24)
  "PositionPerViewNV\0" // IR(6402, 18)
  "PerViewAttributesNV\0" // IR(6420, 20)
  "ViewportMaskPerViewNV\0" // IR(6440, 22)
  "FullyCoveredEXT\0" // IR(6462, 16)
  "FragmentFullyCoveredEXT\0" // IR(6478, 24)
  "TaskCountNV\0" // IR(6502, 12)
  "PrimitiveCountNV\0" // IR(6514, 17)
  "PrimitiveIndicesNV\0" // IR(6531, 19)
  "ClipDistancePerViewNV\0" // IR(6550, 22)
  "CullDistancePerViewNV\0" // IR(6572, 22)
  "LayerPerViewNV\0" // IR(6594, 15)
  "MeshViewCountNV\0" // IR(6609, 16)
  "MeshViewIndicesNV\0" // IR(6625, 18)
  "BaryCoordKHR\0" // IR(6643, 13)
  "BaryCoordNV\0" // IR(6656, 12)
  "FragmentBarycentricKHR\0" // IR(6668, 23)
  "BaryCoordNoPerspKHR\0" // IR(6691, 20)
  "BaryCoordNoPerspNV\0" // IR(6711, 19)
  "FragSizeEXT\0" // IR(6730, 12)
  "FragmentSizeNV\0" // IR(6742, 15)
  "FragmentDensityEXT\0" // IR(6757, 19)
  "FragInvocationCountEXT\0" // IR(6776, 23)
  "InvocationsPerPixelNV\0" // IR(6799, 22)
  "PrimitivePointIndicesEXT\0" // IR(6821, 25)
  "PrimitiveLineIndicesEXT\0" // IR(6846, 24)
  "PrimitiveTriangleIndicesEXT\0" // IR(6870, 28)
  "CullPrimitiveEXT\0" // IR(6898, 17)
  "LaunchIdKHR\0" // IR(6915, 12)
  "LaunchIdNV\0" // IR(6927, 11)
  "LaunchSizeKHR\0" // IR(6938, 14)
  "LaunchSizeNV\0" // IR(6952, 13)
  "WorldRayOriginKHR\0" // IR(6965, 18)
  "WorldRayOriginNV\0" // IR(6983, 17)
  "WorldRayDirectionKHR\0" // IR(7000, 21)
  "WorldRayDirectionNV\0" // IR(7021, 20)
  "ObjectRayOriginKHR\0" // IR(7041, 19)
  "ObjectRayOriginNV\0" // IR(7060, 18)
  "ObjectRayDirectionKHR\0" // IR(7078, 22)
  "ObjectRayDirectionNV\0" // IR(7100, 21)
  "RayTminKHR\0" // IR(7121, 11)
  "RayTminNV\0" // IR(7132, 10)
  "RayTmaxKHR\0" // IR(7142, 11)
  "RayTmaxNV\0" // IR(7153, 10)
  "InstanceCustomIndexKHR\0" // IR(7163, 23)
  "InstanceCustomIndexNV\0" // IR(7186, 22)
  "ObjectToWorldKHR\0" // IR(7208, 17)
  "ObjectToWorldNV\0" // IR(7225, 16)
  "WorldToObjectKHR\0" // IR(7241, 17)
  "WorldToObjectNV\0" // IR(7258, 16)
  "HitTNV\0" // IR(7274, 7)
  "HitKindKHR\0" // IR(7281, 11)
  "HitKindNV\0" // IR(7292, 10)
  "CurrentRayTimeNV\0" // IR(7302, 17)
  "RayTracingMotionBlurNV\0" // IR(7319, 23)
  "HitTriangleVertexPositionsKHR\0" // IR(7342, 30)
  "RayTracingPositionFetchKHR\0" // IR(7372, 27)
  "HitMicroTriangleVertexPositionsNV\0" // IR(7399, 34)
  "RayTracingDisplacementMicromapNV\0" // IR(7433, 33)
  "HitMicroTriangleVertexBarycentricsNV\0" // IR(7466, 37)
  "IncomingRayFlagsKHR\0" // IR(7503, 20)
  "IncomingRayFlagsNV\0" // IR(7523, 19)
  "RayGeometryIndexKHR\0" // IR(7542, 20)
  "HitIsSphereNV\0" // IR(7562, 14)
  "RayTracingSpheresGeometryNV\0" // IR(7576, 28)
  "HitIsLSSNV\0" // IR(7604, 11)
  "RayTracingLinearSweptSpheresGeometryNV\0" // IR(7615, 39)
  "HitSpherePositionNV\0" // IR(7654, 20)
  "WarpsPerSMNV\0" // IR(7674, 13)
  "ShaderSMBuiltinsNV\0" // IR(7687, 19)
  "SMCountNV\0" // IR(7706, 10)
  "WarpIDNV\0" // IR(7716, 9)
  "SMIDNV\0" // IR(7725, 7)
  "HitLSSPositionsNV\0" // IR(7732, 18)
  "HitKindFrontFacingMicroTriangleNV\0" // IR(7750, 34)
  "HitKindBackFacingMicroTriangleNV\0" // IR(7784, 33)
  "HitSphereRadiusNV\0" // IR(7817, 18)
  "HitLSSRadiiNV\0" // IR(7835, 14)
  "ClusterIDNV\0" // IR(7849, 12)
  "RayTracingClusterAccelerationStructureNV\0" // IR(7861, 41)
  "CullMaskKHR\0" // IR(7902, 12)
  "RayCullMaskKHR\0" // IR(7914, 15)
  "Matrix\0" // IR(7929, 7)
  "Linkage\0" // IR(7936, 8)
  "Vector16\0" // IR(7944, 9)
  "Float16Buffer\0" // IR(7953, 14)
  "Float16\0" // IR(7967, 8)
  "Float64\0" // IR(7975, 8)
  "Int64\0" // IR(7983, 6)
  "Int64Atomics\0" // IR(7989, 13)
  "ImageBasic\0" // IR(8002, 11)
  "ImageReadWrite\0" // IR(8013, 15)
  "ImageMipmap\0" // IR(8028, 12)
  "Pipes\0" // IR(8040, 6)
  "Groups\0" // IR(8046, 7)
  "DeviceEnqueue\0" // IR(8053, 14)
  "LiteralSampler\0" // IR(8067, 15)
  "AtomicStorage\0" // IR(8082, 14)
  "Int16\0" // IR(8096, 6)
  "TessellationPointSize\0" // IR(8102, 22)
  "GeometryPointSize\0" // IR(8124, 18)
  "ImageGatherExtended\0" // IR(8142, 20)
  "StorageImageMultisample\0" // IR(8162, 24)
  "UniformBufferArrayDynamicIndexing\0" // IR(8186, 34)
  "SampledImageArrayDynamicIndexing\0" // IR(8220, 33)
  "StorageBufferArrayDynamicIndexing\0" // IR(8253, 34)
  "StorageImageArrayDynamicIndexing\0" // IR(8287, 33)
  "ImageCubeArray\0" // IR(8320, 15)
  "SampledCubeArray\0" // IR(8335, 17)
  "ImageRect\0" // IR(8352, 10)
  "SampledRect\0" // IR(8362, 12)
  "GenericPointer\0" // IR(8374, 15)
  "Int8\0" // IR(8389, 5)
  "InputAttachment\0" // IR(8394, 16)
  "SparseResidency\0" // IR(8410, 16)
  "MinLod\0" // IR(8426, 7)
  "Sampled1D\0" // IR(8433, 10)
  "Image1D\0" // IR(8443, 8)
  "SampledBuffer\0" // IR(8451, 14)
  "ImageBuffer\0" // IR(8465, 12)
  "ImageMSArray\0" // IR(8477, 13)
  "StorageImageExtendedFormats\0" // IR(8490, 28)
  "ImageQuery\0" // IR(8518, 11)
  "DerivativeControl\0" // IR(8529, 18)
  "InterpolationFunction\0" // IR(8547, 22)
  "TransformFeedback\0" // IR(8569, 18)
  "GeometryStreams\0" // IR(8587, 16)
  "StorageImageReadWithoutFormat\0" // IR(8603, 30)
  "StorageImageWriteWithoutFormat\0" // IR(8633, 31)
  "SubgroupDispatch\0" // IR(8664, 17)
  "NamedBarrier\0" // IR(8681, 13)
  "PipeStorage\0" // IR(8694, 12)
  "GroupNonUniformVote\0" // IR(8706, 20)
  "GroupNonUniformArithmetic\0" // IR(8726, 26)
  "GroupNonUniformShuffle\0" // IR(8752, 23)
  "GroupNonUniformShuffleRelative\0" // IR(8775, 31)
  "GroupNonUniformClustered\0" // IR(8806, 25)
  "GroupNonUniformQuad\0" // IR(8831, 20)
  "UniformDecoration\0" // IR(8851, 18)
  "TileImageColorReadAccessEXT\0" // IR(8869, 28)
  "TileImageDepthReadAccessEXT\0" // IR(8897, 28)
  "TileImageStencilReadAccessEXT\0" // IR(8925, 30)
  "TensorsARM\0" // IR(8955, 11)
  "StorageTensorArrayDynamicIndexingARM\0" // IR(8966, 37)
  "StorageTensorArrayNonUniformIndexingARM\0" // IR(9003, 40)
  "GraphARM\0" // IR(9043, 9)
  "CooperativeMatrixLayoutsARM\0" // IR(9052, 28)
  "Float8EXT\0" // IR(9080, 10)
  "Float8CooperativeMatrixEXT\0" // IR(9090, 27)
  "CooperativeMatrixKHR\0" // IR(9117, 21)
  "WorkgroupMemoryExplicitLayoutKHR\0" // IR(9138, 33)
  "WorkgroupMemoryExplicitLayout8BitAccessKHR\0" // IR(9171, 43)
  "WorkgroupMemoryExplicitLayout16BitAccessKHR\0" // IR(9214, 44)
  "SubgroupVoteKHR\0" // IR(9258, 16)
  "StorageBuffer16BitAccess\0" // IR(9274, 25)
  "StorageUniformBufferBlock16\0" // IR(9299, 28)
  "UniformAndStorageBuffer16BitAccess\0" // IR(9327, 35)
  "StorageUniform16\0" // IR(9362, 17)
  "StoragePushConstant16\0" // IR(9379, 22)
  "StorageInputOutput16\0" // IR(9401, 21)
  "VariablePointersStorageBuffer\0" // IR(9422, 30)
  "VariablePointers\0" // IR(9452, 17)
  "AtomicStorageOps\0" // IR(9469, 17)
  "SampleMaskPostDepthCoverage\0" // IR(9486, 28)
  "StorageBuffer8BitAccess\0" // IR(9514, 24)
  "UniformAndStorageBuffer8BitAccess\0" // IR(9538, 34)
  "StoragePushConstant8\0" // IR(9572, 21)
  "DenormPreserve\0" // IR(9593, 15)
  "DenormFlushToZero\0" // IR(9608, 18)
  "SignedZeroInfNanPreserve\0" // IR(9626, 25)
  "RoundingModeRTE\0" // IR(9651, 16)
  "RoundingModeRTZ\0" // IR(9667, 16)
  "RayQueryProvisionalKHR\0" // IR(9683, 23)
  "RayQueryKHR\0" // IR(9706, 12)
  "UntypedPointersKHR\0" // IR(9718, 19)
  "RayTraversalPrimitiveCullingKHR\0" // IR(9737, 32)
  "TextureSampleWeightedQCOM\0" // IR(9769, 26)
  "TextureBoxFilterQCOM\0" // IR(9795, 21)
  "TextureBlockMatchQCOM\0" // IR(9816, 22)
  "CooperativeMatrixConversionQCOM\0" // IR(9838, 32)
  "TextureBlockMatch2QCOM\0" // IR(9870, 23)
  "Float16ImageAMD\0" // IR(9893, 16)
  "ImageGatherBiasLodAMD\0" // IR(9909, 22)
  "FragmentMaskAMD\0" // IR(9931, 16)
  "ImageReadWriteLodAMD\0" // IR(9947, 21)
  "Int64ImageEXT\0" // IR(9968, 14)
  "ShaderClockKHR\0" // IR(9982, 15)
  "QuadControlKHR\0" // IR(9997, 15)
  "Int4TypeINTEL\0" // IR(10012, 14)
  "Int4CooperativeMatrixINTEL\0" // IR(10026, 27)
  "BFloat16TypeKHR\0" // IR(10053, 16)
  "BFloat16DotProductKHR\0" // IR(10069, 22)
  "BFloat16CooperativeMatrixKHR\0" // IR(10091, 29)
  "SampleMaskOverrideCoverageNV\0" // IR(10120, 29)
  "GeometryShaderPassthroughNV\0" // IR(10149, 28)
  "ShaderViewportIndexLayerNV\0" // IR(10177, 27)
  "ImageFootprintNV\0" // IR(10204, 17)
  "FragmentBarycentricNV\0" // IR(10221, 22)
  "ComputeDerivativeGroupQuadsKHR\0" // IR(10243, 31)
  "ComputeDerivativeGroupQuadsNV\0" // IR(10274, 30)
  "ShadingRateNV\0" // IR(10304, 14)
  "GroupNonUniformPartitionedNV\0" // IR(10318, 29)
  "ShaderNonUniform\0" // IR(10347, 17)
  "ShaderNonUniformEXT\0" // IR(10364, 20)
  "RuntimeDescriptorArray\0" // IR(10384, 23)
  "RuntimeDescriptorArrayEXT\0" // IR(10407, 26)
  "InputAttachmentArrayDynamicIndexing\0" // IR(10433, 36)
  "InputAttachmentArrayDynamicIndexingEXT\0" // IR(10469, 39)
  "UniformTexelBufferArrayDynamicIndexing\0" // IR(10508, 39)
  "UniformTexelBufferArrayDynamicIndexingEXT\0" // IR(10547, 42)
  "StorageTexelBufferArrayDynamicIndexing\0" // IR(10589, 39)
  "StorageTexelBufferArrayDynamicIndexingEXT\0" // IR(10628, 42)
  "UniformBufferArrayNonUniformIndexing\0" // IR(10670, 37)
  "UniformBufferArrayNonUniformIndexingEXT\0" // IR(10707, 40)
  "SampledImageArrayNonUniformIndexing\0" // IR(10747, 36)
  "SampledImageArrayNonUniformIndexingEXT\0" // IR(10783, 39)
  "StorageBufferArrayNonUniformIndexing\0" // IR(10822, 37)
  "StorageBufferArrayNonUniformIndexingEXT\0" // IR(10859, 40)
  "StorageImageArrayNonUniformIndexing\0" // IR(10899, 36)
  "StorageImageArrayNonUniformIndexingEXT\0" // IR(10935, 39)
  "InputAttachmentArrayNonUniformIndexing\0" // IR(10974, 39)
  "InputAttachmentArrayNonUniformIndexingEXT\0" // IR(11013, 42)
  "UniformTexelBufferArrayNonUniformIndexing\0" // IR(11055, 42)
  "UniformTexelBufferArrayNonUniformIndexingEXT\0" // IR(11097, 45)
  "StorageTexelBufferArrayNonUniformIndexing\0" // IR(11142, 42)
  "StorageTexelBufferArrayNonUniformIndexingEXT\0" // IR(11184, 45)
  "VulkanMemoryModel\0" // IR(11229, 18)
  "VulkanMemoryModelKHR\0" // IR(11247, 21)
  "VulkanMemoryModelDeviceScope\0" // IR(11268, 29)
  "VulkanMemoryModelDeviceScopeKHR\0" // IR(11297, 32)
  "PhysicalStorageBufferAddressesEXT\0" // IR(11329, 34)
  "ComputeDerivativeGroupLinearKHR\0" // IR(11363, 32)
  "ComputeDerivativeGroupLinearNV\0" // IR(11395, 31)
  "RayTracingProvisionalKHR\0" // IR(11426, 25)
  "CooperativeMatrixNV\0" // IR(11451, 20)
  "FragmentShaderSampleInterlockEXT\0" // IR(11471, 33)
  "FragmentShaderShadingRateInterlockEXT\0" // IR(11504, 38)
  "FragmentShaderPixelInterlockEXT\0" // IR(11542, 32)
  "DemoteToHelperInvocation\0" // IR(11574, 25)
  "DemoteToHelperInvocationEXT\0" // IR(11599, 28)
  "DisplacementMicromapNV\0" // IR(11627, 23)
  "RayTracingOpacityMicromapEXT\0" // IR(11650, 29)
  "ShaderInvocationReorderNV\0" // IR(11679, 26)
  "BindlessTextureNV\0" // IR(11705, 18)
  "RayQueryPositionFetchKHR\0" // IR(11723, 25)
  "CooperativeVectorNV\0" // IR(11748, 20)
  "AtomicFloat16VectorNV\0" // IR(11768, 22)
  "RawAccessChainsNV\0" // IR(11790, 18)
  "CooperativeMatrixReductionsNV\0" // IR(11808, 30)
  "CooperativeMatrixConversionsNV\0" // IR(11838, 31)
  "CooperativeMatrixPerElementOperationsNV\0" // IR(11869, 40)
  "CooperativeMatrixTensorAddressingNV\0" // IR(11909, 36)
  "CooperativeMatrixBlockLoadsNV\0" // IR(11945, 30)
  "CooperativeVectorTrainingNV\0" // IR(11975, 28)
  "TensorAddressingNV\0" // IR(12003, 19)
  "SubgroupShuffleINTEL\0" // IR(12022, 21)
  "SubgroupBufferBlockIOINTEL\0" // IR(12043, 27)
  "SubgroupImageBlockIOINTEL\0" // IR(12070, 26)
  "SubgroupImageMediaBlockIOINTEL\0" // IR(12096, 31)
  "RoundToInfinityINTEL\0" // IR(12127, 21)
  "FloatingPointModeINTEL\0" // IR(12148, 23)
  "IntegerFunctions2INTEL\0" // IR(12171, 23)
  "FunctionPointersINTEL\0" // IR(12194, 22)
  "IndirectReferencesINTEL\0" // IR(12216, 24)
  "AsmINTEL\0" // IR(12240, 9)
  "AtomicFloat32MinMaxEXT\0" // IR(12249, 23)
  "AtomicFloat64MinMaxEXT\0" // IR(12272, 23)
  "AtomicFloat16MinMaxEXT\0" // IR(12295, 23)
  "VectorComputeINTEL\0" // IR(12318, 19)
  "VectorAnyINTEL\0" // IR(12337, 15)
  "ExpectAssumeKHR\0" // IR(12352, 16)
  "SubgroupAvcMotionEstimationINTEL\0" // IR(12368, 33)
  "SubgroupAvcMotionEstimationIntraINTEL\0" // IR(12401, 38)
  "SubgroupAvcMotionEstimationChromaINTEL\0" // IR(12439, 39)
  "VariableLengthArrayINTEL\0" // IR(12478, 25)
  "FunctionFloatControlINTEL\0" // IR(12503, 26)
  "FPGAMemoryAttributesINTEL\0" // IR(12529, 26)
  "FPFastMathModeINTEL\0" // IR(12555, 20)
  "ArbitraryPrecisionIntegersINTEL\0" // IR(12575, 32)
  "ArbitraryPrecisionFloatingPointINTEL\0" // IR(12607, 37)
  "UnstructuredLoopControlsINTEL\0" // IR(12644, 30)
  "FPGALoopControlsINTEL\0" // IR(12674, 22)
  "KernelAttributesINTEL\0" // IR(12696, 22)
  "FPGAKernelAttributesINTEL\0" // IR(12718, 26)
  "FPGAMemoryAccessesINTEL\0" // IR(12744, 24)
  "FPGAClusterAttributesINTEL\0" // IR(12768, 27)
  "LoopFuseINTEL\0" // IR(12795, 14)
  "FPGADSPControlINTEL\0" // IR(12809, 20)
  "MemoryAccessAliasingINTEL\0" // IR(12829, 26)
  "FPGAInvocationPipeliningAttributesINTEL\0" // IR(12855, 40)
  "FPGABufferLocationINTEL\0" // IR(12895, 24)
  "ArbitraryPrecisionFixedPointINTEL\0" // IR(12919, 34)
  "USMStorageClassesINTEL\0" // IR(12953, 23)
  "RuntimeAlignedAttributeINTEL\0" // IR(12976, 29)
  "IOPipesINTEL\0" // IR(13005, 13)
  "BlockingPipesINTEL\0" // IR(13018, 19)
  "FPGARegINTEL\0" // IR(13037, 13)
  "DotProductInputAll\0" // IR(13050, 19)
  "DotProductInputAllKHR\0" // IR(13069, 22)
  "DotProductInput4x8Bit\0" // IR(13091, 22)
  "DotProductInput4x8BitKHR\0" // IR(13113, 25)
  "DotProductInput4x8BitPacked\0" // IR(13138, 28)
  "DotProductInput4x8BitPackedKHR\0" // IR(13166, 31)
  "DotProduct\0" // IR(13197, 11)
  "DotProductKHR\0" // IR(13208, 14)
  "ReplicatedCompositesEXT\0" // IR(13222, 24)
  "BitInstructions\0" // IR(13246, 16)
  "GroupNonUniformRotateKHR\0" // IR(13262, 25)
  "FloatControls2\0" // IR(13287, 15)
  "FMAKHR\0" // IR(13302, 7)
  "AtomicFloat32AddEXT\0" // IR(13309, 20)
  "AtomicFloat64AddEXT\0" // IR(13329, 20)
  "LongCompositesINTEL\0" // IR(13349, 20)
  "OptNoneEXT\0" // IR(13369, 11)
  "OptNoneINTEL\0" // IR(13380, 13)
  "AtomicFloat16AddEXT\0" // IR(13393, 20)
  "DebugInfoModuleINTEL\0" // IR(13413, 21)
  "BFloat16ConversionINTEL\0" // IR(13434, 24)
  "SplitBarrierINTEL\0" // IR(13458, 18)
  "ArithmeticFenceEXT\0" // IR(13476, 19)
  "FPGAClusterAttributesV2INTEL\0" // IR(13495, 29)
  "FPGAKernelAttributesv2INTEL\0" // IR(13524, 28)
  "TaskSequenceINTEL\0" // IR(13552, 18)
  "FPMaxErrorINTEL\0" // IR(13570, 16)
  "FPGALatencyControlINTEL\0" // IR(13586, 24)
  "FPGAArgumentInterfacesINTEL\0" // IR(13610, 28)
  "GlobalVariableHostAccessINTEL\0" // IR(13638, 30)
  "GlobalVariableFPGADecorationsINTEL\0" // IR(13668, 35)
  "SubgroupBufferPrefetchINTEL\0" // IR(13703, 28)
  "Subgroup2DBlockIOINTEL\0" // IR(13731, 23)
  "Subgroup2DBlockTransformINTEL\0" // IR(13754, 30)
  "Subgroup2DBlockTransposeINTEL\0" // IR(13784, 30)
  "SubgroupMatrixMultiplyAccumulateINTEL\0" // IR(13814, 38)
  "TernaryBitwiseFunctionINTEL\0" // IR(13852, 28)
  "UntypedVariableLengthArrayINTEL\0" // IR(13880, 32)
  "SpecConditionalINTEL\0" // IR(13912, 21)
  "FunctionVariantsINTEL\0" // IR(13933, 22)
  "GroupUniformArithmeticKHR\0" // IR(13955, 26)
  "TensorFloat32RoundingINTEL\0" // IR(13981, 27)
  "MaskedGatherScatterINTEL\0" // IR(14008, 25)
  "CacheControlsINTEL\0" // IR(14033, 19)
  "RegisterLimitsINTEL\0" // IR(14052, 20)
  "BindlessImagesINTEL\0" // IR(14072, 20)
  "Unspecified\0" // IR(14092, 12)
  "Address\0" // IR(14104, 8)
  "Boolean\0" // IR(14112, 8)
  "Float\0" // IR(14120, 6)
  "Signed\0" // IR(14126, 7)
  "SignedChar\0" // IR(14133, 11)
  "Unsigned\0" // IR(14144, 9)
  "UnsignedChar\0" // IR(14153, 13)
  "Class\0" // IR(14166, 6)
  "Structure\0" // IR(14172, 10)
  "Union\0" // IR(14182, 6)
  "ImportedModule\0" // IR(14188, 15)
  "ImportedDeclaration\0" // IR(14203, 20)
  "None\0" // IR(14223, 5)
  "FlagIsProtected\0" // IR(14228, 16)
  "FlagIsPrivate\0" // IR(14244, 14)
  "FlagIsPublic\0" // IR(14258, 13)
  "FlagIsLocal\0" // IR(14271, 12)
  "FlagIsDefinition\0" // IR(14283, 17)
  "FlagFwdDecl\0" // IR(14300, 12)
  "FlagArtificial\0" // IR(14312, 15)
  "FlagExplicit\0" // IR(14327, 13)
  "FlagPrototyped\0" // IR(14340, 15)
  "FlagObjectPointer\0" // IR(14355, 18)
  "FlagStaticMember\0" // IR(14373, 17)
  "FlagIndirectVariable\0" // IR(14390, 21)
  "FlagLValueReference\0" // IR(14411, 20)
  "FlagRValueReference\0" // IR(14431, 20)
  "FlagIsOptimized\0" // IR(14451, 16)
  "FlagIsEnumClass\0" // IR(14467, 16)
  "FlagTypePassByValue\0" // IR(14483, 20)
  "FlagTypePassByReference\0" // IR(14503, 24)
  "Deref\0" // IR(14527, 6)
  "Plus\0" // IR(14533, 5)
  "Minus\0" // IR(14538, 6)
  "SPV_OPERAND_TYPE_LITERAL_INTEGER\0" // IR(14544, 33)
  "PlusUconst\0" // IR(14577, 11)
  "BitPiece\0" // IR(14588, 9)
  "Swap\0" // IR(14597, 5)
  "Xderef\0" // IR(14602, 7)
  "StackValue\0" // IR(14609, 11)
  "Constu\0" // IR(14620, 7)
  "Fragment\0" // IR(14627, 9)
  "ConstType\0" // IR(14636, 10)
  "VolatileType\0" // IR(14646, 13)
  "RestrictType\0" // IR(14659, 13)
  "AtomicType\0" // IR(14672, 11)
  "Float16NV\0" // IR(14683, 10)
  "Float32NV\0" // IR(14693, 10)
  "Float64NV\0" // IR(14703, 10)
  "SignedInt8NV\0" // IR(14713, 13)
  "SignedInt16NV\0" // IR(14726, 14)
  "SignedInt32NV\0" // IR(14740, 14)
  "SignedInt64NV\0" // IR(14754, 14)
  "UnsignedInt8NV\0" // IR(14768, 15)
  "UnsignedInt16NV\0" // IR(14783, 16)
  "UnsignedInt32NV\0" // IR(14799, 16)
  "UnsignedInt64NV\0" // IR(14815, 16)
  "SignedInt8PackedNV\0" // IR(14831, 19)
  "UnsignedInt8PackedNV\0" // IR(14850, 21)
  "FloatE4M3NV\0" // IR(14871, 12)
  "FloatE5M2NV\0" // IR(14883, 12)
  "RowMajorKHR\0" // IR(14895, 12)
  "ColumnMajorKHR\0" // IR(14907, 15)
  "RowBlockedInterleavedARM\0" // IR(14922, 25)
  "ColumnBlockedInterleavedARM\0" // IR(14947, 28)
  "NoneKHR\0" // IR(14975, 8)
  "MatrixASignedComponentsKHR\0" // IR(14983, 27)
  "MatrixBSignedComponentsKHR\0" // IR(15010, 27)
  "MatrixCSignedComponentsKHR\0" // IR(15037, 27)
  "MatrixResultSignedComponentsKHR\0" // IR(15064, 32)
  "SaturatingAccumulationKHR\0" // IR(15096, 26)
  "Row\0" // IR(15122, 4)
  "Column\0" // IR(15126, 7)
  "2x2\0" // IR(15133, 4)
  "MatrixAKHR\0" // IR(15137, 11)
  "MatrixBKHR\0" // IR(15148, 11)
  "MatrixAccumulatorKHR\0" // IR(15159, 21)
  "RowMajorNV\0" // IR(15180, 11)
  "ColumnMajorNV\0" // IR(15191, 14)
  "InferencingOptimalNV\0" // IR(15205, 21)
  "TrainingOptimalNV\0" // IR(15226, 18)
  "RelaxedPrecision\0" // IR(15244, 17)
  "SpecId\0" // IR(15261, 7)
  "Block\0" // IR(15268, 6)
  "BufferBlock\0" // IR(15274, 12)
  "RowMajor\0" // IR(15286, 9)
  "ColMajor\0" // IR(15295, 9)
  "ArrayStride\0" // IR(15304, 12)
  "MatrixStride\0" // IR(15316, 13)
  "GLSLShared\0" // IR(15329, 11)
  "GLSLPacked\0" // IR(15340, 11)
  "CPacked\0" // IR(15351, 8)
  "SPV_OPERAND_TYPE_BUILT_IN\0" // IR(15359, 26)
  "BuiltIn\0" // IR(15385, 8)
  "NoPerspective\0" // IR(15393, 14)
  "Flat\0" // IR(15407, 5)
  "Patch\0" // IR(15412, 6)
  "Centroid\0" // IR(15418, 9)
  "Sample\0" // IR(15427, 7)
  "Invariant\0" // IR(15434, 10)
  "Restrict\0" // IR(15444, 9)
  "Aliased\0" // IR(15453, 8)
  "Volatile\0" // IR(15461, 9)
  "Constant\0" // IR(15470, 9)
  "Coherent\0" // IR(15479, 9)
  "NonWritable\0" // IR(15488, 12)
  "NonReadable\0" // IR(15500, 12)
  "Uniform\0" // IR(15512, 8)
  "SPV_OPERAND_TYPE_SCOPE_ID\0" // IR(15520, 26)
  "UniformId\0" // IR(15546, 10)
  "SaturatedConversion\0" // IR(15556, 20)
  "Stream\0" // IR(15576, 7)
  "Location\0" // IR(15583, 9)
  "Component\0" // IR(15592, 10)
  "Index\0" // IR(15602, 6)
  "Binding\0" // IR(15608, 8)
  "DescriptorSet\0" // IR(15616, 14)
  "Offset\0" // IR(15630, 7)
  "XfbBuffer\0" // IR(15637, 10)
  "XfbStride\0" // IR(15647, 10)
  "SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE\0" // IR(15657, 46)
  "FuncParamAttr\0" // IR(15703, 14)
  "SPV_OPERAND_TYPE_FP_ROUNDING_MODE\0" // IR(15717, 34)
  "FPRoundingMode\0" // IR(15751, 15)
  "SPV_OPERAND_TYPE_FP_FAST_MATH_MODE\0" // IR(15766, 35)
  "FPFastMathMode\0" // IR(15801, 15)
  "SPV_OPERAND_TYPE_LITERAL_STRING\0" // IR(15816, 32)
  "SPV_OPERAND_TYPE_LINKAGE_TYPE\0" // IR(15848, 30)
  "LinkageAttributes\0" // IR(15878, 18)
  "NoContraction\0" // IR(15896, 14)
  "InputAttachmentIndex\0" // IR(15910, 21)
  "Alignment\0" // IR(15931, 10)
  "MaxByteOffset\0" // IR(15941, 14)
  "SPV_OPERAND_TYPE_ID\0" // IR(15955, 20)
  "AlignmentId\0" // IR(15975, 12)
  "MaxByteOffsetId\0" // IR(15987, 16)
  "SaturatedToLargestFloat8NormalConversionEXT\0" // IR(16003, 44)
  "NoSignedWrap\0" // IR(16047, 13)
  "NoUnsignedWrap\0" // IR(16060, 15)
  "WeightTextureQCOM\0" // IR(16075, 18)
  "BlockMatchTextureQCOM\0" // IR(16093, 22)
  "BlockMatchSamplerQCOM\0" // IR(16115, 22)
  "ExplicitInterpAMD\0" // IR(16137, 18)
  "NodeSharesPayloadLimitsWithAMDX\0" // IR(16155, 32)
  "NodeMaxPayloadsAMDX\0" // IR(16187, 20)
  "TrackFinishWritingAMDX\0" // IR(16207, 23)
  "PayloadNodeNameAMDX\0" // IR(16230, 20)
  "PayloadNodeBaseIndexAMDX\0" // IR(16250, 25)
  "PayloadNodeSparseArrayAMDX\0" // IR(16275, 27)
  "PayloadNodeArraySizeAMDX\0" // IR(16302, 25)
  "PayloadDispatchIndirectAMDX\0" // IR(16327, 28)
  "OverrideCoverageNV\0" // IR(16355, 19)
  "PassthroughNV\0" // IR(16374, 14)
  "ViewportRelativeNV\0" // IR(16388, 19)
  "SecondaryViewportRelativeNV\0" // IR(16407, 28)
  "PerPrimitiveEXT\0" // IR(16435, 16)
  "PerPrimitiveNV\0" // IR(16451, 15)
  "PerViewNV\0" // IR(16466, 10)
  "PerTaskNV\0" // IR(16476, 10)
  "PerVertexKHR\0" // IR(16486, 13)
  "PerVertexNV\0" // IR(16499, 12)
  "NonUniform\0" // IR(16511, 11)
  "NonUniformEXT\0" // IR(16522, 14)
  "RestrictPointer\0" // IR(16536, 16)
  "RestrictPointerEXT\0" // IR(16552, 19)
  "AliasedPointer\0" // IR(16571, 15)
  "AliasedPointerEXT\0" // IR(16586, 18)
  "HitObjectShaderRecordBufferNV\0" // IR(16604, 30)
  "BindlessSamplerNV\0" // IR(16634, 18)
  "BindlessImageNV\0" // IR(16652, 16)
  "BoundSamplerNV\0" // IR(16668, 15)
  "BoundImageNV\0" // IR(16683, 13)
  "SIMTCallINTEL\0" // IR(16696, 14)
  "ReferencedIndirectlyINTEL\0" // IR(16710, 26)
  "ClobberINTEL\0" // IR(16736, 13)
  "SideEffectsINTEL\0" // IR(16749, 17)
  "VectorComputeVariableINTEL\0" // IR(16766, 27)
  "FuncParamIOKindINTEL\0" // IR(16793, 21)
  "VectorComputeFunctionINTEL\0" // IR(16814, 27)
  "StackCallINTEL\0" // IR(16841, 15)
  "GlobalVariableOffsetINTEL\0" // IR(16856, 26)
  "CounterBuffer\0" // IR(16882, 14)
  "HlslCounterBufferGOOGLE\0" // IR(16896, 24)
  "UserSemantic\0" // IR(16920, 13)
  "HlslSemanticGOOGLE\0" // IR(16933, 19)
  "UserTypeGOOGLE\0" // IR(16952, 15)
  "FunctionRoundingModeINTEL\0" // IR(16967, 26)
  "SPV_OPERAND_TYPE_FPDENORM_MODE\0" // IR(16993, 31)
  "FunctionDenormModeINTEL\0" // IR(17024, 24)
  "RegisterINTEL\0" // IR(17048, 14)
  "MemoryINTEL\0" // IR(17062, 12)
  "NumbanksINTEL\0" // IR(17074, 14)
  "BankwidthINTEL\0" // IR(17088, 15)
  "MaxPrivateCopiesINTEL\0" // IR(17103, 22)
  "SinglepumpINTEL\0" // IR(17125, 16)
  "DoublepumpINTEL\0" // IR(17141, 16)
  "MaxReplicatesINTEL\0" // IR(17157, 19)
  "SimpleDualPortINTEL\0" // IR(17176, 20)
  "MergeINTEL\0" // IR(17196, 11)
  "SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER\0" // IR(17207, 42)
  "BankBitsINTEL\0" // IR(17249, 14)
  "ForcePow2DepthINTEL\0" // IR(17263, 20)
  "StridesizeINTEL\0" // IR(17283, 16)
  "WordsizeINTEL\0" // IR(17299, 14)
  "TrueDualPortINTEL\0" // IR(17313, 18)
  "BurstCoalesceINTEL\0" // IR(17331, 19)
  "CacheSizeINTEL\0" // IR(17350, 15)
  "DontStaticallyCoalesceINTEL\0" // IR(17365, 28)
  "PrefetchINTEL\0" // IR(17393, 14)
  "StallEnableINTEL\0" // IR(17407, 17)
  "FuseLoopsInFunctionINTEL\0" // IR(17424, 25)
  "MathOpDSPModeINTEL\0" // IR(17449, 19)
  "AliasScopeINTEL\0" // IR(17468, 16)
  "NoAliasINTEL\0" // IR(17484, 13)
  "InitiationIntervalINTEL\0" // IR(17497, 24)
  "MaxConcurrencyINTEL\0" // IR(17521, 20)
  "PipelineEnableINTEL\0" // IR(17541, 20)
  "BufferLocationINTEL\0" // IR(17561, 20)
  "IOPipeStorageINTEL\0" // IR(17581, 19)
  "SPV_OPERAND_TYPE_FPOPERATION_MODE\0" // IR(17600, 34)
  "FunctionFloatingPointModeINTEL\0" // IR(17634, 31)
  "SingleElementVectorINTEL\0" // IR(17665, 25)
  "VectorComputeCallableFunctionINTEL\0" // IR(17690, 35)
  "MediaBlockIOINTEL\0" // IR(17725, 18)
  "StallFreeINTEL\0" // IR(17743, 15)
  "SPV_OPERAND_TYPE_LITERAL_FLOAT\0" // IR(17758, 31)
  "FPMaxErrorDecorationINTEL\0" // IR(17789, 26)
  "LatencyControlLabelINTEL\0" // IR(17815, 25)
  "LatencyControlConstraintINTEL\0" // IR(17840, 30)
  "ConduitKernelArgumentINTEL\0" // IR(17870, 27)
  "RegisterMapKernelArgumentINTEL\0" // IR(17897, 31)
  "MMHostInterfaceAddressWidthINTEL\0" // IR(17928, 33)
  "MMHostInterfaceDataWidthINTEL\0" // IR(17961, 30)
  "MMHostInterfaceLatencyINTEL\0" // IR(17991, 28)
  "SPV_OPERAND_TYPE_ACCESS_QUALIFIER\0" // IR(18019, 34)
  "MMHostInterfaceReadWriteModeINTEL\0" // IR(18053, 34)
  "MMHostInterfaceMaxBurstINTEL\0" // IR(18087, 29)
  "MMHostInterfaceWaitRequestINTEL\0" // IR(18116, 32)
  "StableKernelArgumentINTEL\0" // IR(18148, 26)
  "SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER\0" // IR(18174, 39)
  "HostAccessINTEL\0" // IR(18213, 16)
  "SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER\0" // IR(18229, 47)
  "InitModeINTEL\0" // IR(18276, 14)
  "ImplementInRegisterMapINTEL\0" // IR(18290, 28)
  "ConditionalINTEL\0" // IR(18318, 17)
  "SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL\0" // IR(18335, 36)
  "CacheControlLoadINTEL\0" // IR(18371, 22)
  "SPV_OPERAND_TYPE_STORE_CACHE_CONTROL\0" // IR(18393, 37)
  "CacheControlStoreINTEL\0" // IR(18430, 23)
  "1D\0" // IR(18453, 3)
  "2D\0" // IR(18456, 3)
  "3D\0" // IR(18459, 3)
  "Cube\0" // IR(18462, 5)
  "Rect\0" // IR(18467, 5)
  "Buffer\0" // IR(18472, 7)
  "SubpassData\0" // IR(18479, 12)
  "TileImageDataEXT\0" // IR(18491, 17)
  "Invocations\0" // IR(18508, 12)
  "SpacingEqual\0" // IR(18520, 13)
  "SpacingFractionalEven\0" // IR(18533, 22)
  "SpacingFractionalOdd\0" // IR(18555, 21)
  "VertexOrderCw\0" // IR(18576, 14)
  "VertexOrderCcw\0" // IR(18590, 15)
  "PixelCenterInteger\0" // IR(18605, 19)
  "OriginUpperLeft\0" // IR(18624, 16)
  "OriginLowerLeft\0" // IR(18640, 16)
  "EarlyFragmentTests\0" // IR(18656, 19)
  "PointMode\0" // IR(18675, 10)
  "Xfb\0" // IR(18685, 4)
  "DepthReplacing\0" // IR(18689, 15)
  "DepthGreater\0" // IR(18704, 13)
  "DepthLess\0" // IR(18717, 10)
  "DepthUnchanged\0" // IR(18727, 15)
  "LocalSize\0" // IR(18742, 10)
  "LocalSizeHint\0" // IR(18752, 14)
  "InputPoints\0" // IR(18766, 12)
  "InputLines\0" // IR(18778, 11)
  "InputLinesAdjacency\0" // IR(18789, 20)
  "Triangles\0" // IR(18809, 10)
  "InputTrianglesAdjacency\0" // IR(18819, 24)
  "Quads\0" // IR(18843, 6)
  "Isolines\0" // IR(18849, 9)
  "OutputVertices\0" // IR(18858, 15)
  "OutputPoints\0" // IR(18873, 13)
  "OutputLineStrip\0" // IR(18886, 16)
  "OutputTriangleStrip\0" // IR(18902, 20)
  "VecTypeHint\0" // IR(18922, 12)
  "ContractionOff\0" // IR(18934, 15)
  "Initializer\0" // IR(18949, 12)
  "Finalizer\0" // IR(18961, 10)
  "SubgroupsPerWorkgroup\0" // IR(18971, 22)
  "SubgroupsPerWorkgroupId\0" // IR(18993, 24)
  "LocalSizeId\0" // IR(19017, 12)
  "LocalSizeHintId\0" // IR(19029, 16)
  "NonCoherentColorAttachmentReadEXT\0" // IR(19045, 34)
  "NonCoherentDepthAttachmentReadEXT\0" // IR(19079, 34)
  "NonCoherentStencilAttachmentReadEXT\0" // IR(19113, 36)
  "SubgroupUniformControlFlowKHR\0" // IR(19149, 30)
  "PostDepthCoverage\0" // IR(19179, 18)
  "NonCoherentTileAttachmentReadQCOM\0" // IR(19197, 34)
  "TileShadingRateQCOM\0" // IR(19231, 20)
  "EarlyAndLateFragmentTestsAMD\0" // IR(19251, 29)
  "StencilRefReplacingEXT\0" // IR(19280, 23)
  "CoalescingAMDX\0" // IR(19303, 15)
  "IsApiEntryAMDX\0" // IR(19318, 15)
  "MaxNodeRecursionAMDX\0" // IR(19333, 21)
  "StaticNumWorkgroupsAMDX\0" // IR(19354, 24)
  "MaxNumWorkgroupsAMDX\0" // IR(19378, 21)
  "StencilRefUnchangedFrontAMD\0" // IR(19399, 28)
  "StencilRefGreaterFrontAMD\0" // IR(19427, 26)
  "StencilRefLessFrontAMD\0" // IR(19453, 23)
  "StencilRefUnchangedBackAMD\0" // IR(19476, 27)
  "StencilRefGreaterBackAMD\0" // IR(19503, 25)
  "StencilRefLessBackAMD\0" // IR(19528, 22)
  "QuadDerivativesKHR\0" // IR(19550, 19)
  "RequireFullQuadsKHR\0" // IR(19569, 20)
  "SharesInputWithAMDX\0" // IR(19589, 20)
  "OutputLinesEXT\0" // IR(19609, 15)
  "OutputLinesNV\0" // IR(19624, 14)
  "OutputPrimitivesEXT\0" // IR(19638, 20)
  "OutputPrimitivesNV\0" // IR(19658, 19)
  "DerivativeGroupQuadsKHR\0" // IR(19677, 24)
  "DerivativeGroupQuadsNV\0" // IR(19701, 23)
  "DerivativeGroupLinearKHR\0" // IR(19724, 25)
  "DerivativeGroupLinearNV\0" // IR(19749, 24)
  "OutputTrianglesEXT\0" // IR(19773, 19)
  "OutputTrianglesNV\0" // IR(19792, 18)
  "PixelInterlockOrderedEXT\0" // IR(19810, 25)
  "PixelInterlockUnorderedEXT\0" // IR(19835, 27)
  "SampleInterlockOrderedEXT\0" // IR(19862, 26)
  "SampleInterlockUnorderedEXT\0" // IR(19888, 28)
  "ShadingRateInterlockOrderedEXT\0" // IR(19916, 31)
  "ShadingRateInterlockUnorderedEXT\0" // IR(19947, 33)
  "SharedLocalMemorySizeINTEL\0" // IR(19980, 27)
  "RoundingModeRTPINTEL\0" // IR(20007, 21)
  "RoundingModeRTNINTEL\0" // IR(20028, 21)
  "FloatingPointModeALTINTEL\0" // IR(20049, 26)
  "FloatingPointModeIEEEINTEL\0" // IR(20075, 27)
  "MaxWorkgroupSizeINTEL\0" // IR(20102, 22)
  "MaxWorkDimINTEL\0" // IR(20124, 16)
  "NoGlobalOffsetINTEL\0" // IR(20140, 20)
  "NumSIMDWorkitemsINTEL\0" // IR(20160, 22)
  "SchedulerTargetFmaxMhzINTEL\0" // IR(20182, 28)
  "MaximallyReconvergesKHR\0" // IR(20210, 24)
  "FPFastMathDefault\0" // IR(20234, 18)
  "StreamingInterfaceINTEL\0" // IR(20252, 24)
  "RegisterMapInterfaceINTEL\0" // IR(20276, 26)
  "NamedBarrierCountINTEL\0" // IR(20302, 23)
  "MaximumRegistersINTEL\0" // IR(20325, 22)
  "MaximumRegistersIdINTEL\0" // IR(20347, 24)
  "SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS\0" // IR(20371, 51)
  "NamedMaximumRegistersINTEL\0" // IR(20422, 27)
  "Vertex\0" // IR(20449, 7)
  "TessellationControl\0" // IR(20456, 20)
  "TessellationEvaluation\0" // IR(20476, 23)
  "GLCompute\0" // IR(20499, 10)
  "TaskNV\0" // IR(20509, 7)
  "MeshNV\0" // IR(20516, 7)
  "RayGenerationKHR\0" // IR(20523, 17)
  "RayGenerationNV\0" // IR(20540, 16)
  "IntersectionKHR\0" // IR(20556, 16)
  "IntersectionNV\0" // IR(20572, 15)
  "AnyHitKHR\0" // IR(20587, 10)
  "AnyHitNV\0" // IR(20597, 9)
  "ClosestHitKHR\0" // IR(20606, 14)
  "ClosestHitNV\0" // IR(20620, 13)
  "MissKHR\0" // IR(20633, 8)
  "MissNV\0" // IR(20641, 7)
  "CallableKHR\0" // IR(20648, 12)
  "CallableNV\0" // IR(20660, 11)
  "TaskEXT\0" // IR(20671, 8)
  "MeshEXT\0" // IR(20679, 8)
  "Preserve\0" // IR(20687, 9)
  "FlushToZero\0" // IR(20696, 12)
  "BFloat16KHR\0" // IR(20708, 12)
  "Float8E4M3EXT\0" // IR(20720, 14)
  "Float8E5M2EXT\0" // IR(20734, 14)
  "IEEE\0" // IR(20748, 5)
  "ALT\0" // IR(20753, 4)
  "NotNaN\0" // IR(20757, 7)
  "NotInf\0" // IR(20764, 7)
  "NSZ\0" // IR(20771, 4)
  "AllowRecip\0" // IR(20775, 11)
  "Fast\0" // IR(20786, 5)
  "AllowContract\0" // IR(20791, 14)
  "AllowContractFastINTEL\0" // IR(20805, 23)
  "AllowReassoc\0" // IR(20828, 13)
  "AllowReassocINTEL\0" // IR(20841, 18)
  "AllowTransform\0" // IR(20859, 15)
  "RTE\0" // IR(20874, 4)
  "RTZ\0" // IR(20878, 4)
  "RTP\0" // IR(20882, 4)
  "RTN\0" // IR(20886, 4)
  "Vertical2Pixels\0" // IR(20890, 16)
  "Vertical4Pixels\0" // IR(20906, 16)
  "Horizontal2Pixels\0" // IR(20922, 18)
  "Horizontal4Pixels\0" // IR(20940, 18)
  "Inline\0" // IR(20958, 7)
  "DontInline\0" // IR(20965, 11)
  "Pure\0" // IR(20976, 5)
  "Const\0" // IR(20981, 6)
  "Zext\0" // IR(20987, 5)
  "Sext\0" // IR(20992, 5)
  "ByVal\0" // IR(20997, 6)
  "Sret\0" // IR(21003, 5)
  "NoAlias\0" // IR(21008, 8)
  "NoCapture\0" // IR(21016, 10)
  "NoWrite\0" // IR(21026, 8)
  "NoReadWrite\0" // IR(21034, 12)
  "RuntimeAlignedINTEL\0" // IR(21046, 20)
  "Reduce\0" // IR(21066, 7)
  "InclusiveScan\0" // IR(21073, 14)
  "ExclusiveScan\0" // IR(21087, 14)
  "ClusteredReduce\0" // IR(21101, 16)
  "PartitionedReduceNV\0" // IR(21117, 20)
  "PartitionedInclusiveScanNV\0" // IR(21137, 27)
  "PartitionedExclusiveScanNV\0" // IR(21164, 27)
  "NoneINTEL\0" // IR(21191, 10)
  "ReadINTEL\0" // IR(21201, 10)
  "WriteINTEL\0" // IR(21211, 11)
  "ReadWriteINTEL\0" // IR(21222, 15)
  "Bias\0" // IR(21237, 5)
  "Lod\0" // IR(21242, 4)
  "Grad\0" // IR(21246, 5)
  "ConstOffset\0" // IR(21251, 12)
  "ConstOffsets\0" // IR(21263, 13)
  "MakeTexelAvailable\0" // IR(21276, 19)
  "MakeTexelAvailableKHR\0" // IR(21295, 22)
  "MakeTexelVisible\0" // IR(21317, 17)
  "MakeTexelVisibleKHR\0" // IR(21334, 20)
  "NonPrivateTexel\0" // IR(21354, 16)
  "NonPrivateTexelKHR\0" // IR(21370, 19)
  "VolatileTexel\0" // IR(21389, 14)
  "VolatileTexelKHR\0" // IR(21403, 17)
  "SignExtend\0" // IR(21420, 11)
  "ZeroExtend\0" // IR(21431, 11)
  "Nontemporal\0" // IR(21442, 12)
  "Offsets\0" // IR(21454, 8)
  "SnormInt8\0" // IR(21462, 10)
  "SnormInt16\0" // IR(21472, 11)
  "UnormInt8\0" // IR(21483, 10)
  "UnormInt16\0" // IR(21493, 11)
  "UnormShort565\0" // IR(21504, 14)
  "UnormShort555\0" // IR(21518, 14)
  "UnormInt101010\0" // IR(21532, 15)
  "SignedInt8\0" // IR(21547, 11)
  "SignedInt16\0" // IR(21558, 12)
  "SignedInt32\0" // IR(21570, 12)
  "UnsignedInt8\0" // IR(21582, 13)
  "UnsignedInt16\0" // IR(21595, 14)
  "UnsignedInt32\0" // IR(21609, 14)
  "HalfFloat\0" // IR(21623, 10)
  "UnormInt24\0" // IR(21633, 11)
  "UnormInt101010_2\0" // IR(21644, 17)
  "UnormInt10X6EXT\0" // IR(21661, 16)
  "UnsignedIntRaw10EXT\0" // IR(21677, 20)
  "UnsignedIntRaw12EXT\0" // IR(21697, 20)
  "UnormInt2_101010EXT\0" // IR(21717, 20)
  "UnsignedInt10X6EXT\0" // IR(21737, 19)
  "UnsignedInt12X4EXT\0" // IR(21756, 19)
  "UnsignedInt14X2EXT\0" // IR(21775, 19)
  "UnormInt12X4EXT\0" // IR(21794, 16)
  "UnormInt14X2EXT\0" // IR(21810, 16)
  "R\0" // IR(21826, 2)
  "A\0" // IR(21828, 2)
  "RG\0" // IR(21830, 3)
  "RA\0" // IR(21833, 3)
  "RGB\0" // IR(21836, 4)
  "RGBA\0" // IR(21840, 5)
  "BGRA\0" // IR(21845, 5)
  "ARGB\0" // IR(21850, 5)
  "Intensity\0" // IR(21855, 10)
  "Luminance\0" // IR(21865, 10)
  "Rx\0" // IR(21875, 3)
  "RGx\0" // IR(21878, 4)
  "RGBx\0" // IR(21882, 5)
  "Depth\0" // IR(21887, 6)
  "DepthStencil\0" // IR(21893, 13)
  "sRGB\0" // IR(21906, 5)
  "sRGBx\0" // IR(21911, 6)
  "sRGBA\0" // IR(21917, 6)
  "sBGRA\0" // IR(21923, 6)
  "ABGR\0" // IR(21929, 5)
  "InitOnDeviceReprogramINTEL\0" // IR(21934, 27)
  "InitOnDeviceResetINTEL\0" // IR(21961, 23)
  "NoWait\0" // IR(21984, 7)
  "WaitKernel\0" // IR(21991, 11)
  "WaitWorkGroup\0" // IR(22002, 14)
  "CmdExecTime\0" // IR(22016, 12)
  "MayUsePrintf\0" // IR(22028, 13)
  "Export\0" // IR(22041, 7)
  "Import\0" // IR(22048, 7)
  "LinkOnceODR\0" // IR(22055, 12)
  "UncachedINTEL\0" // IR(22067, 14)
  "CachedINTEL\0" // IR(22081, 12)
  "StreamingINTEL\0" // IR(22093, 15)
  "InvalidateAfterReadINTEL\0" // IR(22108, 25)
  "ConstCachedINTEL\0" // IR(22133, 17)
  "Unroll\0" // IR(22150, 7)
  "DontUnroll\0" // IR(22157, 11)
  "DependencyInfinite\0" // IR(22168, 19)
  "DependencyLength\0" // IR(22187, 17)
  "MinIterations\0" // IR(22204, 14)
  "MaxIterations\0" // IR(22218, 14)
  "IterationMultiple\0" // IR(22232, 18)
  "PeelCount\0" // IR(22250, 10)
  "PartialCount\0" // IR(22260, 13)
  "DependencyArrayINTEL\0" // IR(22273, 21)
  "LoopCoalesceINTEL\0" // IR(22294, 18)
  "MaxInterleavingINTEL\0" // IR(22312, 21)
  "SpeculatedIterationsINTEL\0" // IR(22333, 26)
  "NoFusionINTEL\0" // IR(22359, 14)
  "LoopCountINTEL\0" // IR(22373, 15)
  "MaxReinvocationDelayINTEL\0" // IR(22388, 26)
  "MatrixASignedComponentsINTEL\0" // IR(22414, 29)
  "MatrixBSignedComponentsINTEL\0" // IR(22443, 29)
  "MatrixCBFloat16INTEL\0" // IR(22472, 21)
  "MatrixResultBFloat16INTEL\0" // IR(22493, 26)
  "MatrixAPackedInt8INTEL\0" // IR(22519, 23)
  "MatrixBPackedInt8INTEL\0" // IR(22542, 23)
  "MatrixAPackedInt4INTEL\0" // IR(22565, 23)
  "MatrixBPackedInt4INTEL\0" // IR(22588, 23)
  "MatrixATF32INTEL\0" // IR(22611, 17)
  "MatrixBTF32INTEL\0" // IR(22628, 17)
  "MatrixAPackedFloat16INTEL\0" // IR(22645, 26)
  "MatrixBPackedFloat16INTEL\0" // IR(22671, 26)
  "MatrixAPackedBFloat16INTEL\0" // IR(22697, 27)
  "MatrixBPackedBFloat16INTEL\0" // IR(22724, 27)
  "Aligned\0" // IR(22751, 8)
  "MakePointerAvailable\0" // IR(22759, 21)
  "MakePointerAvailableKHR\0" // IR(22780, 24)
  "MakePointerVisible\0" // IR(22804, 19)
  "MakePointerVisibleKHR\0" // IR(22823, 22)
  "NonPrivatePointer\0" // IR(22845, 18)
  "NonPrivatePointerKHR\0" // IR(22863, 21)
  "AliasScopeINTELMask\0" // IR(22884, 20)
  "NoAliasINTELMask\0" // IR(22904, 17)
  "Simple\0" // IR(22921, 7)
  "GLSL450\0" // IR(22928, 8)
  "OpenCL\0" // IR(22936, 7)
  "Vulkan\0" // IR(22943, 7)
  "VulkanKHR\0" // IR(22950, 10)
  "Relaxed\0" // IR(22960, 8)
  "Acquire\0" // IR(22968, 8)
  "Release\0" // IR(22976, 8)
  "AcquireRelease\0" // IR(22984, 15)
  "SequentiallyConsistent\0" // IR(22999, 23)
  "UniformMemory\0" // IR(23022, 14)
  "SubgroupMemory\0" // IR(23036, 15)
  "WorkgroupMemory\0" // IR(23051, 16)
  "CrossWorkgroupMemory\0" // IR(23067, 21)
  "AtomicCounterMemory\0" // IR(23088, 20)
  "ImageMemory\0" // IR(23108, 12)
  "OutputMemory\0" // IR(23120, 13)
  "OutputMemoryKHR\0" // IR(23133, 16)
  "MakeAvailable\0" // IR(23149, 14)
  "MakeAvailableKHR\0" // IR(23163, 17)
  "MakeVisible\0" // IR(23180, 12)
  "MakeVisibleKHR\0" // IR(23192, 15)
  "AutoINTEL\0" // IR(23207, 10)
  "WRAP\0" // IR(23217, 5)
  "SAT\0" // IR(23222, 4)
  "SAT_ZERO\0" // IR(23226, 9)
  "SAT_SYM\0" // IR(23235, 8)
  "PackedVectorFormat4x8Bit\0" // IR(23243, 25)
  "PackedVectorFormat4x8BitKHR\0" // IR(23268, 28)
  "TRN\0" // IR(23296, 4)
  "TRN_ZERO\0" // IR(23300, 9)
  "RND\0" // IR(23309, 4)
  "RND_ZERO\0" // IR(23313, 9)
  "RND_INF\0" // IR(23322, 8)
  "RND_MIN_INF\0" // IR(23330, 12)
  "RND_CONV\0" // IR(23342, 9)
  "RND_CONV_ODD\0" // IR(23351, 13)
  "RobustnessPerComponentNV\0" // IR(23364, 25)
  "RobustnessPerElementNV\0" // IR(23389, 23)
  "OpaqueKHR\0" // IR(23412, 10)
  "NoOpaqueKHR\0" // IR(23422, 12)
  "TerminateOnFirstHitKHR\0" // IR(23434, 23)
  "SkipClosestHitShaderKHR\0" // IR(23457, 24)
  "CullBackFacingTrianglesKHR\0" // IR(23481, 27)
  "CullFrontFacingTrianglesKHR\0" // IR(23508, 28)
  "CullOpaqueKHR\0" // IR(23536, 14)
  "CullNoOpaqueKHR\0" // IR(23550, 16)
  "SkipTrianglesKHR\0" // IR(23566, 17)
  "SkipBuiltinPrimitivesNV\0" // IR(23583, 24)
  "SkipAABBsKHR\0" // IR(23607, 13)
  "ForceOpacityMicromap2StateEXT\0" // IR(23620, 30)
  "RayQueryCandidateIntersectionTriangleKHR\0" // IR(23650, 41)
  "RayQueryCandidateIntersectionAABBKHR\0" // IR(23691, 37)
  "RayQueryCommittedIntersectionNoneKHR\0" // IR(23728, 37)
  "RayQueryCommittedIntersectionTriangleKHR\0" // IR(23765, 41)
  "RayQueryCommittedIntersectionGeneratedKHR\0" // IR(23806, 42)
  "RayQueryCandidateIntersectionKHR\0" // IR(23848, 33)
  "RayQueryCommittedIntersectionKHR\0" // IR(23881, 33)
  "ClampToEdge\0" // IR(23914, 12)
  "Clamp\0" // IR(23926, 6)
  "Repeat\0" // IR(23932, 7)
  "RepeatMirrored\0" // IR(23939, 15)
  "Nearest\0" // IR(23954, 8)
  "Linear\0" // IR(23962, 7)
  "Unknown\0" // IR(23969, 8)
  "Rgba32f\0" // IR(23977, 8)
  "Rgba16f\0" // IR(23985, 8)
  "R32f\0" // IR(23993, 5)
  "Rgba8\0" // IR(23998, 6)
  "Rgba8Snorm\0" // IR(24004, 11)
  "Rg32f\0" // IR(24015, 6)
  "Rg16f\0" // IR(24021, 6)
  "R11fG11fB10f\0" // IR(24027, 13)
  "R16f\0" // IR(24040, 5)
  "Rgba16\0" // IR(24045, 7)
  "Rgb10A2\0" // IR(24052, 8)
  "Rg16\0" // IR(24060, 5)
  "Rg8\0" // IR(24065, 4)
  "R16\0" // IR(24069, 4)
  "R8\0" // IR(24073, 3)
  "Rgba16Snorm\0" // IR(24076, 12)
  "Rg16Snorm\0" // IR(24088, 10)
  "Rg8Snorm\0" // IR(24098, 9)
  "R16Snorm\0" // IR(24107, 9)
  "R8Snorm\0" // IR(24116, 8)
  "Rgba32i\0" // IR(24124, 8)
  "Rgba16i\0" // IR(24132, 8)
  "Rgba8i\0" // IR(24140, 7)
  "R32i\0" // IR(24147, 5)
  "Rg32i\0" // IR(24152, 6)
  "Rg16i\0" // IR(24158, 6)
  "Rg8i\0" // IR(24164, 5)
  "R16i\0" // IR(24169, 5)
  "R8i\0" // IR(24174, 4)
  "Rgba32ui\0" // IR(24178, 9)
  "Rgba16ui\0" // IR(24187, 9)
  "Rgba8ui\0" // IR(24196, 8)
  "R32ui\0" // IR(24204, 6)
  "Rgb10a2ui\0" // IR(24210, 10)
  "Rg32ui\0" // IR(24220, 7)
  "Rg16ui\0" // IR(24227, 7)
  "Rg8ui\0" // IR(24234, 6)
  "R16ui\0" // IR(24240, 6)
  "R8ui\0" // IR(24246, 5)
  "R64ui\0" // IR(24251, 6)
  "R64i\0" // IR(24257, 5)
  "CrossDevice\0" // IR(24262, 12)
  "Device\0" // IR(24274, 7)
  "Workgroup\0" // IR(24281, 10)
  "Subgroup\0" // IR(24291, 9)
  "Invocation\0" // IR(24300, 11)
  "QueueFamily\0" // IR(24311, 12)
  "QueueFamilyKHR\0" // IR(24323, 15)
  "ShaderCallKHR\0" // IR(24338, 14)
  "Flatten\0" // IR(24352, 8)
  "DontFlatten\0" // IR(24360, 12)
  "IdentifierPossibleDuplicates\0" // IR(24372, 29)
  "FlagUnknownPhysicalLayout\0" // IR(24401, 26)
  "ESSL\0" // IR(24427, 5)
  "GLSL\0" // IR(24432, 5)
  "OpenCL_C\0" // IR(24437, 9)
  "OpenCL_CPP\0" // IR(24446, 11)
  "HLSL\0" // IR(24457, 5)
  "CPP_for_OpenCL\0" // IR(24462, 15)
  "SYCL\0" // IR(24477, 5)
  "HERO_C\0" // IR(24482, 7)
  "NZSL\0" // IR(24489, 5)
  "WGSL\0" // IR(24494, 5)
  "Slang\0" // IR(24499, 6)
  "Zig\0" // IR(24505, 4)
  "Rust\0" // IR(24509, 5)
  "UniformConstant\0" // IR(24514, 16)
  "Input\0" // IR(24530, 6)
  "Output\0" // IR(24536, 7)
  "CrossWorkgroup\0" // IR(24543, 15)
  "Private\0" // IR(24558, 8)
  "Function\0" // IR(24566, 9)
  "Generic\0" // IR(24575, 8)
  "PushConstant\0" // IR(24583, 13)
  "AtomicCounter\0" // IR(24596, 14)
  "Image\0" // IR(24610, 6)
  "StorageBuffer\0" // IR(24616, 14)
  "TileImageEXT\0" // IR(24630, 13)
  "TileAttachmentQCOM\0" // IR(24643, 19)
  "NodePayloadAMDX\0" // IR(24662, 16)
  "CallableDataKHR\0" // IR(24678, 16)
  "CallableDataNV\0" // IR(24694, 15)
  "IncomingCallableDataKHR\0" // IR(24709, 24)
  "IncomingCallableDataNV\0" // IR(24733, 23)
  "RayPayloadKHR\0" // IR(24756, 14)
  "RayPayloadNV\0" // IR(24770, 13)
  "HitAttributeKHR\0" // IR(24783, 16)
  "HitAttributeNV\0" // IR(24799, 15)
  "IncomingRayPayloadKHR\0" // IR(24814, 22)
  "IncomingRayPayloadNV\0" // IR(24836, 21)
  "ShaderRecordBufferKHR\0" // IR(24857, 22)
  "ShaderRecordBufferNV\0" // IR(24879, 21)
  "PhysicalStorageBuffer\0" // IR(24900, 22)
  "PhysicalStorageBufferEXT\0" // IR(24922, 25)
  "HitObjectAttributeNV\0" // IR(24947, 21)
  "TaskPayloadWorkgroupEXT\0" // IR(24968, 24)
  "CodeSectionINTEL\0" // IR(24992, 17)
  "DeviceOnlyINTEL\0" // IR(25009, 16)
  "HostOnlyINTEL\0" // IR(25025, 14)
  "WriteThroughINTEL\0" // IR(25039, 18)
  "WriteBackINTEL\0" // IR(25057, 15)
  "TensorView\0" // IR(25072, 11)
  "DecodeFunc\0" // IR(25083, 11)
  "Undefined\0" // IR(25094, 10)
  "NoneARM\0" // IR(25104, 8)
  "NontemporalARM\0" // IR(25112, 15)
  "OutOfBoundsValueARM\0" // IR(25127, 20)
  "MakeElementAvailableARM\0" // IR(25147, 24)
  "MakeElementVisibleARM\0" // IR(25171, 22)
  "NonPrivateElementARM\0" // IR(25193, 21)
  "Nop\0" // IR(25214, 4)
  "SPV_OPERAND_TYPE_TYPE_ID\0" // IR(25218, 25)
  "SPV_OPERAND_TYPE_RESULT_ID\0" // IR(25243, 27)
  "Undef\0" // IR(25270, 6)
  "SourceContinued\0" // IR(25276, 16)
  "SPV_OPERAND_TYPE_SOURCE_LANGUAGE\0" // IR(25292, 33)
  "SPV_OPERAND_TYPE_OPTIONAL_ID\0" // IR(25325, 29)
  "SPV_OPERAND_TYPE_OPTIONAL_LITERAL_STRING\0" // IR(25354, 41)
  "Source\0" // IR(25395, 7)
  "SourceExtension\0" // IR(25402, 16)
  "Name\0" // IR(25418, 5)
  "MemberName\0" // IR(25423, 11)
  "String\0" // IR(25434, 7)
  "Line\0" // IR(25441, 5)
  "Extension\0" // IR(25446, 10)
  "ExtInstImport\0" // IR(25456, 14)
  "SPV_OPERAND_TYPE_EXTENSION_INSTRUCTION_NUMBER\0" // IR(25470, 46)
  "ExtInst\0" // IR(25516, 8)
  "SPV_OPERAND_TYPE_ADDRESSING_MODEL\0" // IR(25524, 34)
  "SPV_OPERAND_TYPE_MEMORY_MODEL\0" // IR(25558, 30)
  "MemoryModel\0" // IR(25588, 12)
  "SPV_OPERAND_TYPE_EXECUTION_MODEL\0" // IR(25600, 33)
  "SPV_OPERAND_TYPE_VARIABLE_ID\0" // IR(25633, 29)
  "EntryPoint\0" // IR(25662, 11)
  "SPV_OPERAND_TYPE_EXECUTION_MODE\0" // IR(25673, 32)
  "ExecutionMode\0" // IR(25705, 14)
  "SPV_OPERAND_TYPE_CAPABILITY\0" // IR(25719, 28)
  "Capability\0" // IR(25747, 11)
  "TypeVoid\0" // IR(25758, 9)
  "TypeBool\0" // IR(25767, 9)
  "TypeInt\0" // IR(25776, 8)
  "SPV_OPERAND_TYPE_OPTIONAL_FPENCODING\0" // IR(25784, 37)
  "TypeFloat\0" // IR(25821, 10)
  "TypeVector\0" // IR(25831, 11)
  "TypeMatrix\0" // IR(25842, 11)
  "SPV_OPERAND_TYPE_DIMENSIONALITY\0" // IR(25853, 32)
  "SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT\0" // IR(25885, 38)
  "SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER\0" // IR(25923, 43)
  "TypeImage\0" // IR(25966, 10)
  "TypeSampler\0" // IR(25976, 12)
  "TypeSampledImage\0" // IR(25988, 17)
  "TypeArray\0" // IR(26005, 10)
  "TypeRuntimeArray\0" // IR(26015, 17)
  "TypeStruct\0" // IR(26032, 11)
  "TypeOpaque\0" // IR(26043, 11)
  "SPV_OPERAND_TYPE_STORAGE_CLASS\0" // IR(26054, 31)
  "TypePointer\0" // IR(26085, 12)
  "TypeFunction\0" // IR(26097, 13)
  "TypeEvent\0" // IR(26110, 10)
  "TypeDeviceEvent\0" // IR(26120, 16)
  "TypeReserveId\0" // IR(26136, 14)
  "TypeQueue\0" // IR(26150, 10)
  "TypePipe\0" // IR(26160, 9)
  "TypeForwardPointer\0" // IR(26169, 19)
  "ConstantTrue\0" // IR(26188, 13)
  "ConstantFalse\0" // IR(26201, 14)
  "SPV_OPERAND_TYPE_TYPED_LITERAL_NUMBER\0" // IR(26215, 38)
  "ConstantComposite\0" // IR(26253, 18)
  "SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE\0" // IR(26271, 41)
  "SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE\0" // IR(26312, 37)
  "ConstantSampler\0" // IR(26349, 16)
  "ConstantNull\0" // IR(26365, 13)
  "SpecConstantTrue\0" // IR(26378, 17)
  "SpecConstantFalse\0" // IR(26395, 18)
  "SpecConstant\0" // IR(26413, 13)
  "SpecConstantComposite\0" // IR(26426, 22)
  "SPV_OPERAND_TYPE_SPEC_CONSTANT_OP_NUMBER\0" // IR(26448, 41)
  "SpecConstantOp\0" // IR(26489, 15)
  "SPV_OPERAND_TYPE_FUNCTION_CONTROL\0" // IR(26504, 34)
  "FunctionParameter\0" // IR(26538, 18)
  "FunctionEnd\0" // IR(26556, 12)
  "FunctionCall\0" // IR(26568, 13)
  "Variable\0" // IR(26581, 9)
  "ImageTexelPointer\0" // IR(26590, 18)
  "SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS\0" // IR(26608, 40)
  "Load\0" // IR(26648, 5)
  "Store\0" // IR(26653, 6)
  "CopyMemory\0" // IR(26659, 11)
  "CopyMemorySized\0" // IR(26670, 16)
  "AccessChain\0" // IR(26686, 12)
  "InBoundsAccessChain\0" // IR(26698, 20)
  "PtrAccessChain\0" // IR(26718, 15)
  "ArrayLength\0" // IR(26733, 12)
  "GenericPtrMemSemantics\0" // IR(26745, 23)
  "InBoundsPtrAccessChain\0" // IR(26768, 23)
  "SPV_OPERAND_TYPE_DECORATION\0" // IR(26791, 28)
  "Decorate\0" // IR(26819, 9)
  "MemberDecorate\0" // IR(26828, 15)
  "DecorationGroup\0" // IR(26843, 16)
  "GroupDecorate\0" // IR(26859, 14)
  "SPV_OPERAND_TYPE_VARIABLE_ID_LITERAL_INTEGER\0" // IR(26873, 45)
  "GroupMemberDecorate\0" // IR(26918, 20)
  "VectorExtractDynamic\0" // IR(26938, 21)
  "VectorInsertDynamic\0" // IR(26959, 20)
  "VectorShuffle\0" // IR(26979, 14)
  "CompositeConstruct\0" // IR(26993, 19)
  "CompositeExtract\0" // IR(27012, 17)
  "CompositeInsert\0" // IR(27029, 16)
  "CopyObject\0" // IR(27045, 11)
  "Transpose\0" // IR(27056, 10)
  "SampledImage\0" // IR(27066, 13)
  "SPV_OPERAND_TYPE_OPTIONAL_IMAGE\0" // IR(27079, 32)
  "ImageSampleImplicitLod\0" // IR(27111, 23)
  "SPV_OPERAND_TYPE_IMAGE\0" // IR(27134, 23)
  "ImageSampleExplicitLod\0" // IR(27157, 23)
  "ImageSampleDrefImplicitLod\0" // IR(27180, 27)
  "ImageSampleDrefExplicitLod\0" // IR(27207, 27)
  "ImageSampleProjImplicitLod\0" // IR(27234, 27)
  "ImageSampleProjExplicitLod\0" // IR(27261, 27)
  "ImageSampleProjDrefImplicitLod\0" // IR(27288, 31)
  "ImageSampleProjDrefExplicitLod\0" // IR(27319, 31)
  "ImageFetch\0" // IR(27350, 11)
  "ImageGather\0" // IR(27361, 12)
  "ImageDrefGather\0" // IR(27373, 16)
  "ImageRead\0" // IR(27389, 10)
  "ImageWrite\0" // IR(27399, 11)
  "ImageQueryFormat\0" // IR(27410, 17)
  "ImageQueryOrder\0" // IR(27427, 16)
  "ImageQuerySizeLod\0" // IR(27443, 18)
  "ImageQuerySize\0" // IR(27461, 15)
  "ImageQueryLod\0" // IR(27476, 14)
  "ImageQueryLevels\0" // IR(27490, 17)
  "ImageQuerySamples\0" // IR(27507, 18)
  "ConvertFToU\0" // IR(27525, 12)
  "ConvertFToS\0" // IR(27537, 12)
  "ConvertSToF\0" // IR(27549, 12)
  "ConvertUToF\0" // IR(27561, 12)
  "UConvert\0" // IR(27573, 9)
  "SConvert\0" // IR(27582, 9)
  "FConvert\0" // IR(27591, 9)
  "QuantizeToF16\0" // IR(27600, 14)
  "ConvertPtrToU\0" // IR(27614, 14)
  "SatConvertSToU\0" // IR(27628, 15)
  "SatConvertUToS\0" // IR(27643, 15)
  "ConvertUToPtr\0" // IR(27658, 14)
  "PtrCastToGeneric\0" // IR(27672, 17)
  "GenericCastToPtr\0" // IR(27689, 17)
  "GenericCastToPtrExplicit\0" // IR(27706, 25)
  "Bitcast\0" // IR(27731, 8)
  "SNegate\0" // IR(27739, 8)
  "FNegate\0" // IR(27747, 8)
  "IAdd\0" // IR(27755, 5)
  "FAdd\0" // IR(27760, 5)
  "ISub\0" // IR(27765, 5)
  "FSub\0" // IR(27770, 5)
  "IMul\0" // IR(27775, 5)
  "FMul\0" // IR(27780, 5)
  "UDiv\0" // IR(27785, 5)
  "SDiv\0" // IR(27790, 5)
  "FDiv\0" // IR(27795, 5)
  "UMod\0" // IR(27800, 5)
  "SRem\0" // IR(27805, 5)
  "SMod\0" // IR(27810, 5)
  "FRem\0" // IR(27815, 5)
  "FMod\0" // IR(27820, 5)
  "VectorTimesScalar\0" // IR(27825, 18)
  "MatrixTimesScalar\0" // IR(27843, 18)
  "VectorTimesMatrix\0" // IR(27861, 18)
  "MatrixTimesVector\0" // IR(27879, 18)
  "MatrixTimesMatrix\0" // IR(27897, 18)
  "OuterProduct\0" // IR(27915, 13)
  "Dot\0" // IR(27928, 4)
  "IAddCarry\0" // IR(27932, 10)
  "ISubBorrow\0" // IR(27942, 11)
  "UMulExtended\0" // IR(27953, 13)
  "SMulExtended\0" // IR(27966, 13)
  "Any\0" // IR(27979, 4)
  "All\0" // IR(27983, 4)
  "IsNan\0" // IR(27987, 6)
  "IsInf\0" // IR(27993, 6)
  "IsFinite\0" // IR(27999, 9)
  "IsNormal\0" // IR(28008, 9)
  "SignBitSet\0" // IR(28017, 11)
  "LessOrGreater\0" // IR(28028, 14)
  "Ordered\0" // IR(28042, 8)
  "Unordered\0" // IR(28050, 10)
  "LogicalEqual\0" // IR(28060, 13)
  "LogicalNotEqual\0" // IR(28073, 16)
  "LogicalOr\0" // IR(28089, 10)
  "LogicalAnd\0" // IR(28099, 11)
  "LogicalNot\0" // IR(28110, 11)
  "Select\0" // IR(28121, 7)
  "IEqual\0" // IR(28128, 7)
  "INotEqual\0" // IR(28135, 10)
  "UGreaterThan\0" // IR(28145, 13)
  "SGreaterThan\0" // IR(28158, 13)
  "UGreaterThanEqual\0" // IR(28171, 18)
  "SGreaterThanEqual\0" // IR(28189, 18)
  "ULessThan\0" // IR(28207, 10)
  "SLessThan\0" // IR(28217, 10)
  "ULessThanEqual\0" // IR(28227, 15)
  "SLessThanEqual\0" // IR(28242, 15)
  "FOrdEqual\0" // IR(28257, 10)
  "FUnordEqual\0" // IR(28267, 12)
  "FOrdNotEqual\0" // IR(28279, 13)
  "FUnordNotEqual\0" // IR(28292, 15)
  "FOrdLessThan\0" // IR(28307, 13)
  "FUnordLessThan\0" // IR(28320, 15)
  "FOrdGreaterThan\0" // IR(28335, 16)
  "FUnordGreaterThan\0" // IR(28351, 18)
  "FOrdLessThanEqual\0" // IR(28369, 18)
  "FUnordLessThanEqual\0" // IR(28387, 20)
  "FOrdGreaterThanEqual\0" // IR(28407, 21)
  "FUnordGreaterThanEqual\0" // IR(28428, 23)
  "ShiftRightLogical\0" // IR(28451, 18)
  "ShiftRightArithmetic\0" // IR(28469, 21)
  "ShiftLeftLogical\0" // IR(28490, 17)
  "BitwiseOr\0" // IR(28507, 10)
  "BitwiseXor\0" // IR(28517, 11)
  "BitwiseAnd\0" // IR(28528, 11)
  "Not\0" // IR(28539, 4)
  "BitFieldInsert\0" // IR(28543, 15)
  "BitFieldSExtract\0" // IR(28558, 17)
  "BitFieldUExtract\0" // IR(28575, 17)
  "BitReverse\0" // IR(28592, 11)
  "BitCount\0" // IR(28603, 9)
  "DPdx\0" // IR(28612, 5)
  "DPdy\0" // IR(28617, 5)
  "Fwidth\0" // IR(28622, 7)
  "DPdxFine\0" // IR(28629, 9)
  "DPdyFine\0" // IR(28638, 9)
  "FwidthFine\0" // IR(28647, 11)
  "DPdxCoarse\0" // IR(28658, 11)
  "DPdyCoarse\0" // IR(28669, 11)
  "FwidthCoarse\0" // IR(28680, 13)
  "EmitVertex\0" // IR(28693, 11)
  "EndPrimitive\0" // IR(28704, 13)
  "EmitStreamVertex\0" // IR(28717, 17)
  "EndStreamPrimitive\0" // IR(28734, 19)
  "SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID\0" // IR(28753, 37)
  "ControlBarrier\0" // IR(28790, 15)
  "MemoryBarrier\0" // IR(28805, 14)
  "AtomicLoad\0" // IR(28819, 11)
  "AtomicStore\0" // IR(28830, 12)
  "AtomicExchange\0" // IR(28842, 15)
  "AtomicCompareExchange\0" // IR(28857, 22)
  "AtomicCompareExchangeWeak\0" // IR(28879, 26)
  "AtomicIIncrement\0" // IR(28905, 17)
  "AtomicIDecrement\0" // IR(28922, 17)
  "AtomicIAdd\0" // IR(28939, 11)
  "AtomicISub\0" // IR(28950, 11)
  "AtomicSMin\0" // IR(28961, 11)
  "AtomicUMin\0" // IR(28972, 11)
  "AtomicSMax\0" // IR(28983, 11)
  "AtomicUMax\0" // IR(28994, 11)
  "AtomicAnd\0" // IR(29005, 10)
  "AtomicOr\0" // IR(29015, 9)
  "AtomicXor\0" // IR(29024, 10)
  "Phi\0" // IR(29034, 4)
  "SPV_OPERAND_TYPE_LOOP_CONTROL\0" // IR(29038, 30)
  "LoopMerge\0" // IR(29068, 10)
  "SPV_OPERAND_TYPE_SELECTION_CONTROL\0" // IR(29078, 35)
  "SelectionMerge\0" // IR(29113, 15)
  "Label\0" // IR(29128, 6)
  "Branch\0" // IR(29134, 7)
  "BranchConditional\0" // IR(29141, 18)
  "SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER_ID\0" // IR(29159, 45)
  "Switch\0" // IR(29204, 7)
  "Kill\0" // IR(29211, 5)
  "Return\0" // IR(29216, 7)
  "ReturnValue\0" // IR(29223, 12)
  "Unreachable\0" // IR(29235, 12)
  "LifetimeStart\0" // IR(29247, 14)
  "LifetimeStop\0" // IR(29261, 13)
  "GroupAsyncCopy\0" // IR(29274, 15)
  "GroupWaitEvents\0" // IR(29289, 16)
  "GroupAll\0" // IR(29305, 9)
  "GroupAny\0" // IR(29314, 9)
  "GroupBroadcast\0" // IR(29323, 15)
  "SPV_OPERAND_TYPE_GROUP_OPERATION\0" // IR(29338, 33)
  "GroupIAdd\0" // IR(29371, 10)
  "GroupFAdd\0" // IR(29381, 10)
  "GroupFMin\0" // IR(29391, 10)
  "GroupUMin\0" // IR(29401, 10)
  "GroupSMin\0" // IR(29411, 10)
  "GroupFMax\0" // IR(29421, 10)
  "GroupUMax\0" // IR(29431, 10)
  "GroupSMax\0" // IR(29441, 10)
  "ReadPipe\0" // IR(29451, 9)
  "WritePipe\0" // IR(29460, 10)
  "ReservedReadPipe\0" // IR(29470, 17)
  "ReservedWritePipe\0" // IR(29487, 18)
  "ReserveReadPipePackets\0" // IR(29505, 23)
  "ReserveWritePipePackets\0" // IR(29528, 24)
  "CommitReadPipe\0" // IR(29552, 15)
  "CommitWritePipe\0" // IR(29567, 16)
  "IsValidReserveId\0" // IR(29583, 17)
  "GetNumPipePackets\0" // IR(29600, 18)
  "GetMaxPipePackets\0" // IR(29618, 18)
  "GroupReserveReadPipePackets\0" // IR(29636, 28)
  "GroupReserveWritePipePackets\0" // IR(29664, 29)
  "GroupCommitReadPipe\0" // IR(29693, 20)
  "GroupCommitWritePipe\0" // IR(29713, 21)
  "EnqueueMarker\0" // IR(29734, 14)
  "EnqueueKernel\0" // IR(29748, 14)
  "GetKernelNDrangeSubGroupCount\0" // IR(29762, 30)
  "GetKernelNDrangeMaxSubGroupSize\0" // IR(29792, 32)
  "GetKernelWorkGroupSize\0" // IR(29824, 23)
  "GetKernelPreferredWorkGroupSizeMultiple\0" // IR(29847, 40)
  "RetainEvent\0" // IR(29887, 12)
  "ReleaseEvent\0" // IR(29899, 13)
  "CreateUserEvent\0" // IR(29912, 16)
  "IsValidEvent\0" // IR(29928, 13)
  "SetUserEventStatus\0" // IR(29941, 19)
  "CaptureEventProfilingInfo\0" // IR(29960, 26)
  "GetDefaultQueue\0" // IR(29986, 16)
  "BuildNDRange\0" // IR(30002, 13)
  "ImageSparseSampleImplicitLod\0" // IR(30015, 29)
  "ImageSparseSampleExplicitLod\0" // IR(30044, 29)
  "ImageSparseSampleDrefImplicitLod\0" // IR(30073, 33)
  "ImageSparseSampleDrefExplicitLod\0" // IR(30106, 33)
  "ImageSparseSampleProjImplicitLod\0" // IR(30139, 33)
  "ImageSparseSampleProjExplicitLod\0" // IR(30172, 33)
  "ImageSparseSampleProjDrefImplicitLod\0" // IR(30205, 37)
  "ImageSparseSampleProjDrefExplicitLod\0" // IR(30242, 37)
  "ImageSparseFetch\0" // IR(30279, 17)
  "ImageSparseGather\0" // IR(30296, 18)
  "ImageSparseDrefGather\0" // IR(30314, 22)
  "ImageSparseTexelsResident\0" // IR(30336, 26)
  "NoLine\0" // IR(30362, 7)
  "AtomicFlagTestAndSet\0" // IR(30369, 21)
  "AtomicFlagClear\0" // IR(30390, 16)
  "ImageSparseRead\0" // IR(30406, 16)
  "SizeOf\0" // IR(30422, 7)
  "TypePipeStorage\0" // IR(30429, 16)
  "ConstantPipeStorage\0" // IR(30445, 20)
  "CreatePipeFromPipeStorage\0" // IR(30465, 26)
  "GetKernelLocalSizeForSubgroupCount\0" // IR(30491, 35)
  "GetKernelMaxNumSubgroups\0" // IR(30526, 25)
  "TypeNamedBarrier\0" // IR(30551, 17)
  "NamedBarrierInitialize\0" // IR(30568, 23)
  "MemoryNamedBarrier\0" // IR(30591, 19)
  "ModuleProcessed\0" // IR(30610, 16)
  "ExecutionModeId\0" // IR(30626, 16)
  "DecorateId\0" // IR(30642, 11)
  "GroupNonUniformElect\0" // IR(30653, 21)
  "GroupNonUniformAll\0" // IR(30674, 19)
  "GroupNonUniformAny\0" // IR(30693, 19)
  "GroupNonUniformAllEqual\0" // IR(30712, 24)
  "GroupNonUniformBroadcast\0" // IR(30736, 25)
  "GroupNonUniformBroadcastFirst\0" // IR(30761, 30)
  "GroupNonUniformInverseBallot\0" // IR(30791, 29)
  "GroupNonUniformBallotBitExtract\0" // IR(30820, 32)
  "GroupNonUniformBallotBitCount\0" // IR(30852, 30)
  "GroupNonUniformBallotFindLSB\0" // IR(30882, 29)
  "GroupNonUniformBallotFindMSB\0" // IR(30911, 29)
  "GroupNonUniformShuffleXor\0" // IR(30940, 26)
  "GroupNonUniformShuffleUp\0" // IR(30966, 25)
  "GroupNonUniformShuffleDown\0" // IR(30991, 27)
  "GroupNonUniformIAdd\0" // IR(31018, 20)
  "GroupNonUniformFAdd\0" // IR(31038, 20)
  "GroupNonUniformIMul\0" // IR(31058, 20)
  "GroupNonUniformFMul\0" // IR(31078, 20)
  "GroupNonUniformSMin\0" // IR(31098, 20)
  "GroupNonUniformUMin\0" // IR(31118, 20)
  "GroupNonUniformFMin\0" // IR(31138, 20)
  "GroupNonUniformSMax\0" // IR(31158, 20)
  "GroupNonUniformUMax\0" // IR(31178, 20)
  "GroupNonUniformFMax\0" // IR(31198, 20)
  "GroupNonUniformBitwiseAnd\0" // IR(31218, 26)
  "GroupNonUniformBitwiseOr\0" // IR(31244, 25)
  "GroupNonUniformBitwiseXor\0" // IR(31269, 26)
  "GroupNonUniformLogicalAnd\0" // IR(31295, 26)
  "GroupNonUniformLogicalOr\0" // IR(31321, 25)
  "GroupNonUniformLogicalXor\0" // IR(31346, 26)
  "GroupNonUniformQuadBroadcast\0" // IR(31372, 29)
  "GroupNonUniformQuadSwap\0" // IR(31401, 24)
  "CopyLogical\0" // IR(31425, 12)
  "PtrEqual\0" // IR(31437, 9)
  "PtrNotEqual\0" // IR(31446, 12)
  "PtrDiff\0" // IR(31458, 8)
  "ColorAttachmentReadEXT\0" // IR(31466, 23)
  "DepthAttachmentReadEXT\0" // IR(31489, 23)
  "StencilAttachmentReadEXT\0" // IR(31512, 25)
  "TypeTensorARM\0" // IR(31537, 14)
  "SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS\0" // IR(31551, 42)
  "TensorReadARM\0" // IR(31593, 14)
  "TensorWriteARM\0" // IR(31607, 15)
  "TensorQuerySizeARM\0" // IR(31622, 19)
  "GraphConstantARM\0" // IR(31641, 17)
  "GraphEntryPointARM\0" // IR(31658, 19)
  "GraphInputARM\0" // IR(31677, 14)
  "GraphSetOutputARM\0" // IR(31691, 18)
  "GraphEndARM\0" // IR(31709, 12)
  "TypeGraphARM\0" // IR(31721, 13)
  "TerminateInvocation\0" // IR(31734, 20)
  "TypeUntypedPointerKHR\0" // IR(31754, 22)
  "UntypedVariableKHR\0" // IR(31776, 19)
  "UntypedAccessChainKHR\0" // IR(31795, 22)
  "UntypedInBoundsAccessChainKHR\0" // IR(31817, 30)
  "SubgroupFirstInvocationKHR\0" // IR(31847, 27)
  "UntypedPtrAccessChainKHR\0" // IR(31874, 25)
  "UntypedInBoundsPtrAccessChainKHR\0" // IR(31899, 33)
  "UntypedArrayLengthKHR\0" // IR(31932, 22)
  "UntypedPrefetchKHR\0" // IR(31954, 19)
  "FmaKHR\0" // IR(31973, 7)
  "SubgroupAllKHR\0" // IR(31980, 15)
  "SubgroupAnyKHR\0" // IR(31995, 15)
  "SubgroupAllEqualKHR\0" // IR(32010, 20)
  "SubgroupReadInvocationKHR\0" // IR(32030, 26)
  "ExtInstWithForwardRefsKHR\0" // IR(32056, 26)
  "UntypedGroupAsyncCopyKHR\0" // IR(32082, 25)
  "TraceRayKHR\0" // IR(32107, 12)
  "ExecuteCallableKHR\0" // IR(32119, 19)
  "ConvertUToAccelerationStructureKHR\0" // IR(32138, 35)
  "IgnoreIntersectionKHR\0" // IR(32173, 22)
  "TerminateRayKHR\0" // IR(32195, 16)
  "SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT\0" // IR(32211, 47)
  "SDot\0" // IR(32258, 5)
  "SDotKHR\0" // IR(32263, 8)
  "UDot\0" // IR(32271, 5)
  "UDotKHR\0" // IR(32276, 8)
  "SUDot\0" // IR(32284, 6)
  "SUDotKHR\0" // IR(32290, 9)
  "SDotAccSat\0" // IR(32299, 11)
  "SDotAccSatKHR\0" // IR(32310, 14)
  "UDotAccSat\0" // IR(32324, 11)
  "UDotAccSatKHR\0" // IR(32335, 14)
  "SUDotAccSat\0" // IR(32349, 12)
  "SUDotAccSatKHR\0" // IR(32361, 15)
  "TypeCooperativeMatrixKHR\0" // IR(32376, 25)
  "CooperativeMatrixLoadKHR\0" // IR(32401, 25)
  "CooperativeMatrixStoreKHR\0" // IR(32426, 26)
  "SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS\0" // IR(32452, 54)
  "CooperativeMatrixMulAddKHR\0" // IR(32506, 27)
  "CooperativeMatrixLengthKHR\0" // IR(32533, 27)
  "ConstantCompositeReplicateEXT\0" // IR(32560, 30)
  "SpecConstantCompositeReplicateEXT\0" // IR(32590, 34)
  "CompositeConstructReplicateEXT\0" // IR(32624, 31)
  "TypeRayQueryKHR\0" // IR(32655, 16)
  "RayQueryInitializeKHR\0" // IR(32671, 22)
  "RayQueryTerminateKHR\0" // IR(32693, 21)
  "RayQueryGenerateIntersectionKHR\0" // IR(32714, 32)
  "RayQueryConfirmIntersectionKHR\0" // IR(32746, 31)
  "RayQueryProceedKHR\0" // IR(32777, 19)
  "RayQueryGetIntersectionTypeKHR\0" // IR(32796, 31)
  "ImageSampleWeightedQCOM\0" // IR(32827, 24)
  "ImageBoxFilterQCOM\0" // IR(32851, 19)
  "ImageBlockMatchSSDQCOM\0" // IR(32870, 23)
  "ImageBlockMatchSADQCOM\0" // IR(32893, 23)
  "BitCastArrayQCOM\0" // IR(32916, 17)
  "ImageBlockMatchWindowSSDQCOM\0" // IR(32933, 29)
  "ImageBlockMatchWindowSADQCOM\0" // IR(32962, 29)
  "ImageBlockMatchGatherSSDQCOM\0" // IR(32991, 29)
  "ImageBlockMatchGatherSADQCOM\0" // IR(33020, 29)
  "CompositeConstructCoopMatQCOM\0" // IR(33049, 30)
  "CompositeExtractCoopMatQCOM\0" // IR(33079, 28)
  "ExtractSubArrayQCOM\0" // IR(33107, 20)
  "GroupIAddNonUniformAMD\0" // IR(33127, 23)
  "GroupFAddNonUniformAMD\0" // IR(33150, 23)
  "GroupFMinNonUniformAMD\0" // IR(33173, 23)
  "GroupUMinNonUniformAMD\0" // IR(33196, 23)
  "GroupSMinNonUniformAMD\0" // IR(33219, 23)
  "GroupFMaxNonUniformAMD\0" // IR(33242, 23)
  "GroupUMaxNonUniformAMD\0" // IR(33265, 23)
  "GroupSMaxNonUniformAMD\0" // IR(33288, 23)
  "FragmentMaskFetchAMD\0" // IR(33311, 21)
  "FragmentFetchAMD\0" // IR(33332, 17)
  "ReadClockKHR\0" // IR(33349, 13)
  "AllocateNodePayloadsAMDX\0" // IR(33362, 25)
  "EnqueueNodePayloadsAMDX\0" // IR(33387, 24)
  "TypeNodePayloadArrayAMDX\0" // IR(33411, 25)
  "FinishWritingNodePayloadAMDX\0" // IR(33436, 29)
  "NodePayloadArrayLengthAMDX\0" // IR(33465, 27)
  "IsNodePayloadValidAMDX\0" // IR(33492, 23)
  "ConstantStringAMDX\0" // IR(33515, 19)
  "SpecConstantStringAMDX\0" // IR(33534, 23)
  "GroupNonUniformQuadAllKHR\0" // IR(33557, 26)
  "GroupNonUniformQuadAnyKHR\0" // IR(33583, 26)
  "HitObjectRecordHitMotionNV\0" // IR(33609, 27)
  "HitObjectRecordHitWithIndexMotionNV\0" // IR(33636, 36)
  "HitObjectRecordMissMotionNV\0" // IR(33672, 28)
  "HitObjectGetWorldToObjectNV\0" // IR(33700, 28)
  "HitObjectGetObjectToWorldNV\0" // IR(33728, 28)
  "HitObjectGetObjectRayDirectionNV\0" // IR(33756, 33)
  "HitObjectGetObjectRayOriginNV\0" // IR(33789, 30)
  "HitObjectTraceRayMotionNV\0" // IR(33819, 26)
  "HitObjectGetShaderRecordBufferHandleNV\0" // IR(33845, 39)
  "HitObjectGetShaderBindingTableRecordIndexNV\0" // IR(33884, 44)
  "HitObjectRecordEmptyNV\0" // IR(33928, 23)
  "HitObjectTraceRayNV\0" // IR(33951, 20)
  "HitObjectRecordHitNV\0" // IR(33971, 21)
  "HitObjectRecordHitWithIndexNV\0" // IR(33992, 30)
  "HitObjectRecordMissNV\0" // IR(34022, 22)
  "HitObjectExecuteShaderNV\0" // IR(34044, 25)
  "HitObjectGetCurrentTimeNV\0" // IR(34069, 26)
  "HitObjectGetAttributesNV\0" // IR(34095, 25)
  "HitObjectGetHitKindNV\0" // IR(34120, 22)
  "HitObjectGetPrimitiveIndexNV\0" // IR(34142, 29)
  "HitObjectGetGeometryIndexNV\0" // IR(34171, 28)
  "HitObjectGetInstanceIdNV\0" // IR(34199, 25)
  "HitObjectGetInstanceCustomIndexNV\0" // IR(34224, 34)
  "HitObjectGetWorldRayDirectionNV\0" // IR(34258, 32)
  "HitObjectGetWorldRayOriginNV\0" // IR(34290, 29)
  "HitObjectGetRayTMaxNV\0" // IR(34319, 22)
  "HitObjectGetRayTMinNV\0" // IR(34341, 22)
  "HitObjectIsEmptyNV\0" // IR(34363, 19)
  "HitObjectIsHitNV\0" // IR(34382, 17)
  "HitObjectIsMissNV\0" // IR(34399, 18)
  "ReorderThreadWithHitObjectNV\0" // IR(34417, 29)
  "ReorderThreadWithHintNV\0" // IR(34446, 24)
  "TypeHitObjectNV\0" // IR(34470, 16)
  "ImageSampleFootprintNV\0" // IR(34486, 23)
  "TypeCooperativeVectorNV\0" // IR(34509, 24)
  "CooperativeVectorMatrixMulNV\0" // IR(34533, 29)
  "CooperativeVectorOuterProductAccumulateNV\0" // IR(34562, 42)
  "CooperativeVectorReduceSumAccumulateNV\0" // IR(34604, 39)
  "CooperativeVectorMatrixMulAddNV\0" // IR(34643, 32)
  "CooperativeMatrixConvertNV\0" // IR(34675, 27)
  "EmitMeshTasksEXT\0" // IR(34702, 17)
  "SetMeshOutputsEXT\0" // IR(34719, 18)
  "GroupNonUniformPartitionNV\0" // IR(34737, 27)
  "WritePackedPrimitiveIndices4x8NV\0" // IR(34764, 33)
  "FetchMicroTriangleVertexPositionNV\0" // IR(34797, 35)
  "FetchMicroTriangleVertexBarycentricNV\0" // IR(34832, 38)
  "CooperativeVectorLoadNV\0" // IR(34870, 24)
  "CooperativeVectorStoreNV\0" // IR(34894, 25)
  "ReportIntersectionKHR\0" // IR(34919, 22)
  "ReportIntersectionNV\0" // IR(34941, 21)
  "IgnoreIntersectionNV\0" // IR(34962, 21)
  "TerminateRayNV\0" // IR(34983, 15)
  "TraceNV\0" // IR(34998, 8)
  "TraceMotionNV\0" // IR(35006, 14)
  "TraceRayMotionNV\0" // IR(35020, 17)
  "RayQueryGetIntersectionTriangleVertexPositionsKHR\0" // IR(35037, 50)
  "TypeAccelerationStructureKHR\0" // IR(35087, 29)
  "TypeAccelerationStructureNV\0" // IR(35116, 28)
  "ExecuteCallableNV\0" // IR(35144, 18)
  "RayQueryGetIntersectionClusterIdNV\0" // IR(35162, 35)
  "RayQueryGetClusterIdNV\0" // IR(35197, 23)
  "HitObjectGetClusterIdNV\0" // IR(35220, 24)
  "TypeCooperativeMatrixNV\0" // IR(35244, 24)
  "CooperativeMatrixLoadNV\0" // IR(35268, 24)
  "CooperativeMatrixStoreNV\0" // IR(35292, 25)
  "CooperativeMatrixMulAddNV\0" // IR(35317, 26)
  "CooperativeMatrixLengthNV\0" // IR(35343, 26)
  "BeginInvocationInterlockEXT\0" // IR(35369, 28)
  "EndInvocationInterlockEXT\0" // IR(35397, 26)
  "SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE\0" // IR(35423, 43)
  "CooperativeMatrixReduceNV\0" // IR(35466, 26)
  "SPV_OPERAND_TYPE_MEMORY_ACCESS\0" // IR(35492, 31)
  "SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS\0" // IR(35523, 44)
  "CooperativeMatrixLoadTensorNV\0" // IR(35567, 30)
  "CooperativeMatrixStoreTensorNV\0" // IR(35597, 31)
  "CooperativeMatrixPerElementOpNV\0" // IR(35628, 32)
  "TypeTensorLayoutNV\0" // IR(35660, 19)
  "TypeTensorViewNV\0" // IR(35679, 17)
  "CreateTensorLayoutNV\0" // IR(35696, 21)
  "TensorLayoutSetDimensionNV\0" // IR(35717, 27)
  "TensorLayoutSetStrideNV\0" // IR(35744, 24)
  "TensorLayoutSliceNV\0" // IR(35768, 20)
  "TensorLayoutSetClampValueNV\0" // IR(35788, 28)
  "CreateTensorViewNV\0" // IR(35816, 19)
  "TensorViewSetDimensionNV\0" // IR(35835, 25)
  "TensorViewSetStrideNV\0" // IR(35860, 22)
  "IsHelperInvocationEXT\0" // IR(35882, 22)
  "TensorViewSetClipNV\0" // IR(35904, 20)
  "TensorLayoutSetBlockSizeNV\0" // IR(35924, 27)
  "CooperativeMatrixTransposeNV\0" // IR(35951, 29)
  "ConvertUToImageNV\0" // IR(35980, 18)
  "ConvertUToSamplerNV\0" // IR(35998, 20)
  "ConvertImageToUNV\0" // IR(36018, 18)
  "ConvertSamplerToUNV\0" // IR(36036, 20)
  "ConvertUToSampledImageNV\0" // IR(36056, 25)
  "ConvertSampledImageToUNV\0" // IR(36081, 25)
  "SamplerImageAddressingModeNV\0" // IR(36106, 29)
  "SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS\0" // IR(36135, 52)
  "RawAccessChainNV\0" // IR(36187, 17)
  "RayQueryGetIntersectionSpherePositionNV\0" // IR(36204, 40)
  "RayQueryGetIntersectionSphereRadiusNV\0" // IR(36244, 38)
  "RayQueryGetIntersectionLSSPositionsNV\0" // IR(36282, 38)
  "RayQueryGetIntersectionLSSRadiiNV\0" // IR(36320, 34)
  "RayQueryGetIntersectionLSSHitValueNV\0" // IR(36354, 37)
  "HitObjectGetSpherePositionNV\0" // IR(36391, 29)
  "HitObjectGetSphereRadiusNV\0" // IR(36420, 27)
  "HitObjectGetLSSPositionsNV\0" // IR(36447, 27)
  "HitObjectGetLSSRadiiNV\0" // IR(36474, 23)
  "HitObjectIsSphereHitNV\0" // IR(36497, 23)
  "HitObjectIsLSSHitNV\0" // IR(36520, 20)
  "RayQueryIsSphereHitNV\0" // IR(36540, 22)
  "RayQueryIsLSSHitNV\0" // IR(36562, 19)
  "SubgroupShuffleDownINTEL\0" // IR(36581, 25)
  "SubgroupShuffleUpINTEL\0" // IR(36606, 23)
  "SubgroupShuffleXorINTEL\0" // IR(36629, 24)
  "SubgroupBlockReadINTEL\0" // IR(36653, 23)
  "SubgroupBlockWriteINTEL\0" // IR(36676, 24)
  "SubgroupImageBlockReadINTEL\0" // IR(36700, 28)
  "SubgroupImageBlockWriteINTEL\0" // IR(36728, 29)
  "SubgroupImageMediaBlockReadINTEL\0" // IR(36757, 33)
  "SubgroupImageMediaBlockWriteINTEL\0" // IR(36790, 34)
  "UCountLeadingZerosINTEL\0" // IR(36824, 24)
  "UCountTrailingZerosINTEL\0" // IR(36848, 25)
  "AbsISubINTEL\0" // IR(36873, 13)
  "AbsUSubINTEL\0" // IR(36886, 13)
  "IAddSatINTEL\0" // IR(36899, 13)
  "UAddSatINTEL\0" // IR(36912, 13)
  "IAverageINTEL\0" // IR(36925, 14)
  "UAverageINTEL\0" // IR(36939, 14)
  "IAverageRoundedINTEL\0" // IR(36953, 21)
  "UAverageRoundedINTEL\0" // IR(36974, 21)
  "ISubSatINTEL\0" // IR(36995, 13)
  "USubSatINTEL\0" // IR(37008, 13)
  "IMul32x16INTEL\0" // IR(37021, 15)
  "UMul32x16INTEL\0" // IR(37036, 15)
  "ConstantFunctionPointerINTEL\0" // IR(37051, 29)
  "FunctionPointerCallINTEL\0" // IR(37080, 25)
  "AsmTargetINTEL\0" // IR(37105, 15)
  "AsmCallINTEL\0" // IR(37120, 13)
  "AtomicFMinEXT\0" // IR(37133, 14)
  "AtomicFMaxEXT\0" // IR(37147, 14)
  "AssumeTrueKHR\0" // IR(37161, 14)
  "ExpectKHR\0" // IR(37175, 10)
  "DecorateString\0" // IR(37185, 15)
  "DecorateStringGOOGLE\0" // IR(37200, 21)
  "MemberDecorateString\0" // IR(37221, 21)
  "MemberDecorateStringGOOGLE\0" // IR(37242, 27)
  "VmeImageINTEL\0" // IR(37269, 14)
  "TypeVmeImageINTEL\0" // IR(37283, 18)
  "TypeAvcImePayloadINTEL\0" // IR(37301, 23)
  "TypeAvcRefPayloadINTEL\0" // IR(37324, 23)
  "TypeAvcSicPayloadINTEL\0" // IR(37347, 23)
  "TypeAvcMcePayloadINTEL\0" // IR(37370, 23)
  "TypeAvcMceResultINTEL\0" // IR(37393, 22)
  "TypeAvcImeResultINTEL\0" // IR(37415, 22)
  "TypeAvcImeResultSingleReferenceStreamoutINTEL\0" // IR(37437, 46)
  "TypeAvcImeResultDualReferenceStreamoutINTEL\0" // IR(37483, 44)
  "TypeAvcImeSingleReferenceStreaminINTEL\0" // IR(37527, 39)
  "TypeAvcImeDualReferenceStreaminINTEL\0" // IR(37566, 37)
  "TypeAvcRefResultINTEL\0" // IR(37603, 22)
  "TypeAvcSicResultINTEL\0" // IR(37625, 22)
  "SubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL\0" // IR(37647, 60)
  "SubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL\0" // IR(37707, 53)
  "SubgroupAvcMceGetDefaultInterShapePenaltyINTEL\0" // IR(37760, 47)
  "SubgroupAvcMceSetInterShapePenaltyINTEL\0" // IR(37807, 40)
  "SubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL\0" // IR(37847, 51)
  "SubgroupAvcMceSetInterDirectionPenaltyINTEL\0" // IR(37898, 44)
  "SubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL\0" // IR(37942, 51)
  "SubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL\0" // IR(37993, 56)
  "SubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL\0" // IR(38049, 50)
  "SubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL\0" // IR(38099, 52)
  "SubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL\0" // IR(38151, 49)
  "SubgroupAvcMceSetMotionVectorCostFunctionINTEL\0" // IR(38200, 47)
  "SubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL\0" // IR(38247, 50)
  "SubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL\0" // IR(38297, 51)
  "SubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL\0" // IR(38348, 56)
  "SubgroupAvcMceSetAcOnlyHaarINTEL\0" // IR(38404, 33)
  "SubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL\0" // IR(38437, 52)
  "SubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL\0" // IR(38489, 61)
  "SubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL\0" // IR(38550, 61)
  "SubgroupAvcMceConvertToImePayloadINTEL\0" // IR(38611, 39)
  "SubgroupAvcMceConvertToImeResultINTEL\0" // IR(38650, 38)
  "SubgroupAvcMceConvertToRefPayloadINTEL\0" // IR(38688, 39)
  "SubgroupAvcMceConvertToRefResultINTEL\0" // IR(38727, 38)
  "SubgroupAvcMceConvertToSicPayloadINTEL\0" // IR(38765, 39)
  "SubgroupAvcMceConvertToSicResultINTEL\0" // IR(38804, 38)
  "SubgroupAvcMceGetMotionVectorsINTEL\0" // IR(38842, 36)
  "SubgroupAvcMceGetInterDistortionsINTEL\0" // IR(38878, 39)
  "SubgroupAvcMceGetBestInterDistortionsINTEL\0" // IR(38917, 43)
  "SubgroupAvcMceGetInterMajorShapeINTEL\0" // IR(38960, 38)
  "SubgroupAvcMceGetInterMinorShapeINTEL\0" // IR(38998, 38)
  "SubgroupAvcMceGetInterDirectionsINTEL\0" // IR(39036, 38)
  "SubgroupAvcMceGetInterMotionVectorCountINTEL\0" // IR(39074, 45)
  "SubgroupAvcMceGetInterReferenceIdsINTEL\0" // IR(39119, 40)
  "SubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL\0" // IR(39159, 62)
  "SubgroupAvcImeInitializeINTEL\0" // IR(39221, 30)
  "SubgroupAvcImeSetSingleReferenceINTEL\0" // IR(39251, 38)
  "SubgroupAvcImeSetDualReferenceINTEL\0" // IR(39289, 36)
  "SubgroupAvcImeRefWindowSizeINTEL\0" // IR(39325, 33)
  "SubgroupAvcImeAdjustRefOffsetINTEL\0" // IR(39358, 35)
  "SubgroupAvcImeConvertToMcePayloadINTEL\0" // IR(39393, 39)
  "SubgroupAvcImeSetMaxMotionVectorCountINTEL\0" // IR(39432, 43)
  "SubgroupAvcImeSetUnidirectionalMixDisableINTEL\0" // IR(39475, 47)
  "SubgroupAvcImeSetEarlySearchTerminationThresholdINTEL\0" // IR(39522, 54)
  "SubgroupAvcImeSetWeightedSadINTEL\0" // IR(39576, 34)
  "SubgroupAvcImeEvaluateWithSingleReferenceINTEL\0" // IR(39610, 47)
  "SubgroupAvcImeEvaluateWithDualReferenceINTEL\0" // IR(39657, 45)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL\0" // IR(39702, 55)
  "SubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL\0" // IR(39757, 53)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL\0" // IR(39810, 56)
  "SubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL\0" // IR(39866, 54)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL\0" // IR(39920, 58)
  "SubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL\0" // IR(39978, 56)
  "SubgroupAvcImeConvertToMceResultINTEL\0" // IR(40034, 38)
  "SubgroupAvcImeGetSingleReferenceStreaminINTEL\0" // IR(40072, 46)
  "SubgroupAvcImeGetDualReferenceStreaminINTEL\0" // IR(40118, 44)
  "SubgroupAvcImeStripSingleReferenceStreamoutINTEL\0" // IR(40162, 49)
  "SubgroupAvcImeStripDualReferenceStreamoutINTEL\0" // IR(40211, 47)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL\0" // IR(40258, 70)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL\0" // IR(40328, 68)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL\0" // IR(40396, 69)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL\0" // IR(40465, 68)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL\0" // IR(40533, 66)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL\0" // IR(40599, 67)
  "SubgroupAvcImeGetBorderReachedINTEL\0" // IR(40666, 36)
  "SubgroupAvcImeGetTruncatedSearchIndicationINTEL\0" // IR(40702, 48)
  "SubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL\0" // IR(40750, 59)
  "SubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL\0" // IR(40809, 58)
  "SubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL\0" // IR(40867, 56)
  "SubgroupAvcFmeInitializeINTEL\0" // IR(40923, 30)
  "SubgroupAvcBmeInitializeINTEL\0" // IR(40953, 30)
  "SubgroupAvcRefConvertToMcePayloadINTEL\0" // IR(40983, 39)
  "SubgroupAvcRefSetBidirectionalMixDisableINTEL\0" // IR(41022, 46)
  "SubgroupAvcRefSetBilinearFilterEnableINTEL\0" // IR(41068, 43)
  "SubgroupAvcRefEvaluateWithSingleReferenceINTEL\0" // IR(41111, 47)
  "SubgroupAvcRefEvaluateWithDualReferenceINTEL\0" // IR(41158, 45)
  "SubgroupAvcRefEvaluateWithMultiReferenceINTEL\0" // IR(41203, 46)
  "SubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL\0" // IR(41249, 56)
  "SubgroupAvcRefConvertToMceResultINTEL\0" // IR(41305, 38)
  "SubgroupAvcSicInitializeINTEL\0" // IR(41343, 30)
  "SubgroupAvcSicConfigureSkcINTEL\0" // IR(41373, 32)
  "SubgroupAvcSicConfigureIpeLumaINTEL\0" // IR(41405, 36)
  "SubgroupAvcSicConfigureIpeLumaChromaINTEL\0" // IR(41441, 42)
  "SubgroupAvcSicGetMotionVectorMaskINTEL\0" // IR(41483, 39)
  "SubgroupAvcSicConvertToMcePayloadINTEL\0" // IR(41522, 39)
  "SubgroupAvcSicSetIntraLumaShapePenaltyINTEL\0" // IR(41561, 44)
  "SubgroupAvcSicSetIntraLumaModeCostFunctionINTEL\0" // IR(41605, 48)
  "SubgroupAvcSicSetIntraChromaModeCostFunctionINTEL\0" // IR(41653, 50)
  "SubgroupAvcSicSetBilinearFilterEnableINTEL\0" // IR(41703, 43)
  "SubgroupAvcSicSetSkcForwardTransformEnableINTEL\0" // IR(41746, 48)
  "SubgroupAvcSicSetBlockBasedRawSkipSadINTEL\0" // IR(41794, 43)
  "SubgroupAvcSicEvaluateIpeINTEL\0" // IR(41837, 31)
  "SubgroupAvcSicEvaluateWithSingleReferenceINTEL\0" // IR(41868, 47)
  "SubgroupAvcSicEvaluateWithDualReferenceINTEL\0" // IR(41915, 45)
  "SubgroupAvcSicEvaluateWithMultiReferenceINTEL\0" // IR(41960, 46)
  "SubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL\0" // IR(42006, 56)
  "SubgroupAvcSicConvertToMceResultINTEL\0" // IR(42062, 38)
  "SubgroupAvcSicGetIpeLumaShapeINTEL\0" // IR(42100, 35)
  "SubgroupAvcSicGetBestIpeLumaDistortionINTEL\0" // IR(42135, 44)
  "SubgroupAvcSicGetBestIpeChromaDistortionINTEL\0" // IR(42179, 46)
  "SubgroupAvcSicGetPackedIpeLumaModesINTEL\0" // IR(42225, 41)
  "SubgroupAvcSicGetIpeChromaModeINTEL\0" // IR(42266, 36)
  "SubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL\0" // IR(42302, 50)
  "SubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL\0" // IR(42352, 48)
  "SubgroupAvcSicGetInterRawSadsINTEL\0" // IR(42400, 35)
  "SaveMemoryINTEL\0" // IR(42435, 16)
  "RestoreMemoryINTEL\0" // IR(42451, 19)
  "ArbitraryFloatSinCosPiINTEL\0" // IR(42470, 28)
  "ArbitraryFloatCastINTEL\0" // IR(42498, 24)
  "ArbitraryFloatCastFromIntINTEL\0" // IR(42522, 31)
  "ArbitraryFloatCastToIntINTEL\0" // IR(42553, 29)
  "ArbitraryFloatAddINTEL\0" // IR(42582, 23)
  "ArbitraryFloatSubINTEL\0" // IR(42605, 23)
  "ArbitraryFloatMulINTEL\0" // IR(42628, 23)
  "ArbitraryFloatDivINTEL\0" // IR(42651, 23)
  "ArbitraryFloatGTINTEL\0" // IR(42674, 22)
  "ArbitraryFloatGEINTEL\0" // IR(42696, 22)
  "ArbitraryFloatLTINTEL\0" // IR(42718, 22)
  "ArbitraryFloatLEINTEL\0" // IR(42740, 22)
  "ArbitraryFloatEQINTEL\0" // IR(42762, 22)
  "ArbitraryFloatRecipINTEL\0" // IR(42784, 25)
  "ArbitraryFloatRSqrtINTEL\0" // IR(42809, 25)
  "ArbitraryFloatCbrtINTEL\0" // IR(42834, 24)
  "ArbitraryFloatHypotINTEL\0" // IR(42858, 25)
  "ArbitraryFloatSqrtINTEL\0" // IR(42883, 24)
  "ArbitraryFloatLogINTEL\0" // IR(42907, 23)
  "ArbitraryFloatLog2INTEL\0" // IR(42930, 24)
  "ArbitraryFloatLog10INTEL\0" // IR(42954, 25)
  "ArbitraryFloatLog1pINTEL\0" // IR(42979, 25)
  "ArbitraryFloatExpINTEL\0" // IR(43004, 23)
  "ArbitraryFloatExp2INTEL\0" // IR(43027, 24)
  "ArbitraryFloatExp10INTEL\0" // IR(43051, 25)
  "ArbitraryFloatExpm1INTEL\0" // IR(43076, 25)
  "ArbitraryFloatSinINTEL\0" // IR(43101, 23)
  "ArbitraryFloatCosINTEL\0" // IR(43124, 23)
  "ArbitraryFloatSinCosINTEL\0" // IR(43147, 26)
  "ArbitraryFloatSinPiINTEL\0" // IR(43173, 25)
  "ArbitraryFloatCosPiINTEL\0" // IR(43198, 25)
  "ArbitraryFloatASinINTEL\0" // IR(43223, 24)
  "ArbitraryFloatASinPiINTEL\0" // IR(43247, 26)
  "ArbitraryFloatACosINTEL\0" // IR(43273, 24)
  "ArbitraryFloatACosPiINTEL\0" // IR(43297, 26)
  "ArbitraryFloatATanINTEL\0" // IR(43323, 24)
  "ArbitraryFloatATanPiINTEL\0" // IR(43347, 26)
  "ArbitraryFloatATan2INTEL\0" // IR(43373, 25)
  "ArbitraryFloatPowINTEL\0" // IR(43398, 23)
  "ArbitraryFloatPowRINTEL\0" // IR(43421, 24)
  "ArbitraryFloatPowNINTEL\0" // IR(43445, 24)
  "LoopControlINTEL\0" // IR(43469, 17)
  "AliasDomainDeclINTEL\0" // IR(43486, 21)
  "AliasScopeDeclINTEL\0" // IR(43507, 20)
  "AliasScopeListDeclINTEL\0" // IR(43527, 24)
  "FixedSqrtINTEL\0" // IR(43551, 15)
  "FixedRecipINTEL\0" // IR(43566, 16)
  "FixedRsqrtINTEL\0" // IR(43582, 16)
  "FixedSinINTEL\0" // IR(43598, 14)
  "FixedCosINTEL\0" // IR(43612, 14)
  "FixedSinCosINTEL\0" // IR(43626, 17)
  "FixedSinPiINTEL\0" // IR(43643, 16)
  "FixedCosPiINTEL\0" // IR(43659, 16)
  "FixedSinCosPiINTEL\0" // IR(43675, 19)
  "FixedLogINTEL\0" // IR(43694, 14)
  "FixedExpINTEL\0" // IR(43708, 14)
  "PtrCastToCrossWorkgroupINTEL\0" // IR(43722, 29)
  "CrossWorkgroupCastToPtrINTEL\0" // IR(43751, 29)
  "ReadPipeBlockingINTEL\0" // IR(43780, 22)
  "WritePipeBlockingINTEL\0" // IR(43802, 23)
  "RayQueryGetRayTMinKHR\0" // IR(43825, 22)
  "RayQueryGetRayFlagsKHR\0" // IR(43847, 23)
  "RayQueryGetIntersectionTKHR\0" // IR(43870, 28)
  "RayQueryGetIntersectionInstanceCustomIndexKHR\0" // IR(43898, 46)
  "RayQueryGetIntersectionInstanceIdKHR\0" // IR(43944, 37)
  "RayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR\0" // IR(43981, 65)
  "RayQueryGetIntersectionGeometryIndexKHR\0" // IR(44046, 40)
  "RayQueryGetIntersectionPrimitiveIndexKHR\0" // IR(44086, 41)
  "RayQueryGetIntersectionBarycentricsKHR\0" // IR(44127, 39)
  "RayQueryGetIntersectionFrontFaceKHR\0" // IR(44166, 36)
  "RayQueryGetIntersectionCandidateAABBOpaqueKHR\0" // IR(44202, 46)
  "RayQueryGetIntersectionObjectRayDirectionKHR\0" // IR(44248, 45)
  "RayQueryGetIntersectionObjectRayOriginKHR\0" // IR(44293, 42)
  "RayQueryGetWorldRayDirectionKHR\0" // IR(44335, 32)
  "RayQueryGetWorldRayOriginKHR\0" // IR(44367, 29)
  "RayQueryGetIntersectionObjectToWorldKHR\0" // IR(44396, 40)
  "RayQueryGetIntersectionWorldToObjectKHR\0" // IR(44436, 40)
  "AtomicFAddEXT\0" // IR(44476, 14)
  "TypeBufferSurfaceINTEL\0" // IR(44490, 23)
  "TypeStructContinuedINTEL\0" // IR(44513, 25)
  "ConstantCompositeContinuedINTEL\0" // IR(44538, 32)
  "SpecConstantCompositeContinuedINTEL\0" // IR(44570, 36)
  "CompositeConstructContinuedINTEL\0" // IR(44606, 33)
  "ConvertFToBF16INTEL\0" // IR(44639, 20)
  "ConvertBF16ToFINTEL\0" // IR(44659, 20)
  "ControlBarrierArriveINTEL\0" // IR(44679, 26)
  "ControlBarrierWaitINTEL\0" // IR(44705, 24)
  "TaskSequenceCreateINTEL\0" // IR(44729, 24)
  "TaskSequenceAsyncINTEL\0" // IR(44753, 23)
  "TaskSequenceGetINTEL\0" // IR(44776, 21)
  "TaskSequenceReleaseINTEL\0" // IR(44797, 25)
  "TypeTaskSequenceINTEL\0" // IR(44822, 22)
  "SubgroupBlockPrefetchINTEL\0" // IR(44844, 27)
  "Subgroup2DBlockLoadINTEL\0" // IR(44871, 25)
  "Subgroup2DBlockLoadTransformINTEL\0" // IR(44896, 34)
  "Subgroup2DBlockLoadTransposeINTEL\0" // IR(44930, 34)
  "Subgroup2DBlockPrefetchINTEL\0" // IR(44964, 29)
  "Subgroup2DBlockStoreINTEL\0" // IR(44993, 26)
  "SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS\0" // IR(45019, 62)
  "BitwiseFunctionINTEL\0" // IR(45081, 21)
  "ConditionalExtensionINTEL\0" // IR(45102, 26)
  "ConditionalEntryPointINTEL\0" // IR(45128, 27)
  "ConditionalCapabilityINTEL\0" // IR(45155, 27)
  "SpecConstantTargetINTEL\0" // IR(45182, 24)
  "SpecConstantArchitectureINTEL\0" // IR(45206, 30)
  "SPV_OPERAND_TYPE_VARIABLE_CAPABILITY\0" // IR(45236, 37)
  "SpecConstantCapabilitiesINTEL\0" // IR(45273, 30)
  "ConditionalCopyObjectINTEL\0" // IR(45303, 27)
  "GroupIMulKHR\0" // IR(45330, 13)
  "GroupFMulKHR\0" // IR(45343, 13)
  "GroupBitwiseAndKHR\0" // IR(45356, 19)
  "GroupBitwiseOrKHR\0" // IR(45375, 18)
  "GroupBitwiseXorKHR\0" // IR(45393, 19)
  "GroupLogicalAndKHR\0" // IR(45412, 19)
  "GroupLogicalOrKHR\0" // IR(45431, 18)
  "GroupLogicalXorKHR\0" // IR(45449, 19)
  "RoundFToTF32INTEL\0" // IR(45468, 18)
  "MaskedGatherINTEL\0" // IR(45486, 18)
  "MaskedScatterINTEL\0" // IR(45504, 19)
  "ConvertHandleToImageINTEL\0" // IR(45523, 26)
  "ConvertHandleToSamplerINTEL\0" // IR(45549, 28)
  "ConvertHandleToSampledImageINTEL\0" // IR(45577, 33)
  "DebugInfoNone\0" // IR(45610, 14)
  "DebugCompilationUnit\0" // IR(45624, 21)
  "SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING\0" // IR(45645, 52)
  "DebugTypeBasic\0" // IR(45697, 15)
  "SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS\0" // IR(45712, 34)
  "DebugTypePointer\0" // IR(45746, 17)
  "SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER\0" // IR(45763, 38)
  "DebugTypeQualifier\0" // IR(45801, 19)
  "DebugTypeArray\0" // IR(45820, 15)
  "DebugTypeVector\0" // IR(45835, 16)
  "DebugTypedef\0" // IR(45851, 13)
  "DebugTypeFunction\0" // IR(45864, 18)
  "DebugTypeEnum\0" // IR(45882, 14)
  "SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE\0" // IR(45896, 38)
  "DebugTypeComposite\0" // IR(45934, 19)
  "DebugTypeMember\0" // IR(45953, 16)
  "DebugTypeInheritance\0" // IR(45969, 21)
  "DebugTypePtrToMember\0" // IR(45990, 21)
  "DebugTypeTemplate\0" // IR(46011, 18)
  "DebugTypeTemplateParameter\0" // IR(46029, 27)
  "DebugTypeTemplateTemplateParameter\0" // IR(46056, 35)
  "DebugTypeTemplateParameterPack\0" // IR(46091, 31)
  "DebugGlobalVariable\0" // IR(46122, 20)
  "DebugFunctionDeclaration\0" // IR(46142, 25)
  "DebugFunction\0" // IR(46167, 14)
  "DebugLexicalBlock\0" // IR(46181, 18)
  "DebugLexicalBlockDiscriminator\0" // IR(46199, 31)
  "DebugScope\0" // IR(46230, 11)
  "DebugNoScope\0" // IR(46241, 13)
  "DebugInlinedAt\0" // IR(46254, 15)
  "SPV_OPERAND_TYPE_OPTIONAL_LITERAL_INTEGER\0" // IR(46269, 42)
  "DebugLocalVariable\0" // IR(46311, 19)
  "DebugInlinedVariable\0" // IR(46330, 21)
  "DebugDeclare\0" // IR(46351, 13)
  "DebugValue\0" // IR(46364, 11)
  "SPV_OPERAND_TYPE_DEBUG_OPERATION\0" // IR(46375, 33)
  "DebugOperation\0" // IR(46408, 15)
  "DebugExpression\0" // IR(46423, 16)
  "DebugMacroDef\0" // IR(46439, 14)
  "DebugMacroUndef\0" // IR(46453, 16)
  "Round\0" // IR(46469, 6)
  "RoundEven\0" // IR(46475, 10)
  "Trunc\0" // IR(46485, 6)
  "FAbs\0" // IR(46491, 5)
  "SAbs\0" // IR(46496, 5)
  "FSign\0" // IR(46501, 6)
  "SSign\0" // IR(46507, 6)
  "Floor\0" // IR(46513, 6)
  "Ceil\0" // IR(46519, 5)
  "Fract\0" // IR(46524, 6)
  "Radians\0" // IR(46530, 8)
  "Degrees\0" // IR(46538, 8)
  "Sin\0" // IR(46546, 4)
  "Cos\0" // IR(46550, 4)
  "Tan\0" // IR(46554, 4)
  "Asin\0" // IR(46558, 5)
  "Acos\0" // IR(46563, 5)
  "Atan\0" // IR(46568, 5)
  "Sinh\0" // IR(46573, 5)
  "Cosh\0" // IR(46578, 5)
  "Tanh\0" // IR(46583, 5)
  "Asinh\0" // IR(46588, 6)
  "Acosh\0" // IR(46594, 6)
  "Atanh\0" // IR(46600, 6)
  "Atan2\0" // IR(46606, 6)
  "Pow\0" // IR(46612, 4)
  "Exp\0" // IR(46616, 4)
  "Log\0" // IR(46620, 4)
  "Exp2\0" // IR(46624, 5)
  "Log2\0" // IR(46629, 5)
  "Sqrt\0" // IR(46634, 5)
  "InverseSqrt\0" // IR(46639, 12)
  "Determinant\0" // IR(46651, 12)
  "MatrixInverse\0" // IR(46663, 14)
  "Modf\0" // IR(46677, 5)
  "ModfStruct\0" // IR(46682, 11)
  "FMin\0" // IR(46693, 5)
  "UMin\0" // IR(46698, 5)
  "SMin\0" // IR(46703, 5)
  "FMax\0" // IR(46708, 5)
  "UMax\0" // IR(46713, 5)
  "SMax\0" // IR(46718, 5)
  "FClamp\0" // IR(46723, 7)
  "UClamp\0" // IR(46730, 7)
  "SClamp\0" // IR(46737, 7)
  "FMix\0" // IR(46744, 5)
  "IMix\0" // IR(46749, 5)
  "Step\0" // IR(46754, 5)
  "SmoothStep\0" // IR(46759, 11)
  "Fma\0" // IR(46770, 4)
  "Frexp\0" // IR(46774, 6)
  "FrexpStruct\0" // IR(46780, 12)
  "Ldexp\0" // IR(46792, 6)
  "PackSnorm4x8\0" // IR(46798, 13)
  "PackUnorm4x8\0" // IR(46811, 13)
  "PackSnorm2x16\0" // IR(46824, 14)
  "PackUnorm2x16\0" // IR(46838, 14)
  "PackHalf2x16\0" // IR(46852, 13)
  "PackDouble2x32\0" // IR(46865, 15)
  "UnpackSnorm2x16\0" // IR(46880, 16)
  "UnpackUnorm2x16\0" // IR(46896, 16)
  "UnpackHalf2x16\0" // IR(46912, 15)
  "UnpackSnorm4x8\0" // IR(46927, 15)
  "UnpackUnorm4x8\0" // IR(46942, 15)
  "UnpackDouble2x32\0" // IR(46957, 17)
  "Length\0" // IR(46974, 7)
  "Distance\0" // IR(46981, 9)
  "Cross\0" // IR(46990, 6)
  "Normalize\0" // IR(46996, 10)
  "FaceForward\0" // IR(47006, 12)
  "Reflect\0" // IR(47018, 8)
  "Refract\0" // IR(47026, 8)
  "FindILsb\0" // IR(47034, 9)
  "FindSMsb\0" // IR(47043, 9)
  "FindUMsb\0" // IR(47052, 9)
  "InterpolateAtCentroid\0" // IR(47061, 22)
  "InterpolateAtSample\0" // IR(47083, 20)
  "InterpolateAtOffset\0" // IR(47103, 20)
  "NMin\0" // IR(47123, 5)
  "NMax\0" // IR(47128, 5)
  "NClamp\0" // IR(47133, 7)
  "ArgumentInfo\0" // IR(47140, 13)
  "ArgumentStorageBuffer\0" // IR(47153, 22)
  "ArgumentUniform\0" // IR(47175, 16)
  "ArgumentPodStorageBuffer\0" // IR(47191, 25)
  "ArgumentPodUniform\0" // IR(47216, 19)
  "ArgumentPodPushConstant\0" // IR(47235, 24)
  "ArgumentSampledImage\0" // IR(47259, 21)
  "ArgumentStorageImage\0" // IR(47280, 21)
  "ArgumentSampler\0" // IR(47301, 16)
  "ArgumentWorkgroup\0" // IR(47317, 18)
  "SpecConstantWorkgroupSize\0" // IR(47335, 26)
  "SpecConstantGlobalOffset\0" // IR(47361, 25)
  "SpecConstantWorkDim\0" // IR(47386, 20)
  "PushConstantGlobalOffset\0" // IR(47406, 25)
  "PushConstantEnqueuedLocalSize\0" // IR(47431, 30)
  "PushConstantGlobalSize\0" // IR(47461, 23)
  "PushConstantRegionOffset\0" // IR(47484, 25)
  "PushConstantNumWorkgroups\0" // IR(47509, 26)
  "PushConstantRegionGroupOffset\0" // IR(47535, 30)
  "ConstantDataStorageBuffer\0" // IR(47565, 26)
  "ConstantDataUniform\0" // IR(47591, 20)
  "PropertyRequiredWorkgroupSize\0" // IR(47611, 30)
  "SpecConstantSubgroupMaxSize\0" // IR(47641, 28)
  "ArgumentPointerPushConstant\0" // IR(47669, 28)
  "ArgumentPointerUniform\0" // IR(47697, 23)
  "ProgramScopeVariablesStorageBuffer\0" // IR(47720, 35)
  "ProgramScopeVariablePointerRelocation\0" // IR(47755, 38)
  "ImageArgumentInfoChannelOrderPushConstant\0" // IR(47793, 42)
  "ImageArgumentInfoChannelDataTypePushConstant\0" // IR(47835, 45)
  "ImageArgumentInfoChannelOrderUniform\0" // IR(47880, 37)
  "ImageArgumentInfoChannelDataTypeUniform\0" // IR(47917, 40)
  "ArgumentStorageTexelBuffer\0" // IR(47957, 27)
  "ArgumentUniformTexelBuffer\0" // IR(47984, 27)
  "ConstantDataPointerPushConstant\0" // IR(48011, 32)
  "ProgramScopeVariablePointerPushConstant\0" // IR(48043, 40)
  "PrintfInfo\0" // IR(48083, 11)
  "PrintfBufferStorageBuffer\0" // IR(48094, 26)
  "PrintfBufferPointerPushConstant\0" // IR(48120, 32)
  "NormalizedSamplerMaskPushConstant\0" // IR(48152, 34)
  "WorkgroupVariableSize\0" // IR(48186, 22)
  "DebugImportedEntity\0" // IR(48208, 20)
  "DebugSource\0" // IR(48228, 12)
  "DebugFunctionDefinition\0" // IR(48240, 24)
  "DebugSourceContinued\0" // IR(48264, 21)
  "DebugLine\0" // IR(48285, 10)
  "DebugNoLine\0" // IR(48295, 12)
  "DebugBuildIdentifier\0" // IR(48307, 21)
  "DebugStoragePath\0" // IR(48328, 17)
  "DebugEntryPoint\0" // IR(48345, 16)
  "DebugTypeMatrix\0" // IR(48361, 16)
  "Configuration\0" // IR(48377, 14)
  "StartCounter\0" // IR(48391, 13)
  "StopCounter\0" // IR(48404, 12)
  "PushConstants\0" // IR(48416, 14)
  "SpecializationMapEntry\0" // IR(48430, 23)
  "DescriptorSetBuffer\0" // IR(48453, 20)
  "DescriptorSetImage\0" // IR(48473, 19)
  "DescriptorSetSampler\0" // IR(48492, 21)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING\0" // IR(48513, 63)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS\0" // IR(48576, 45)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER\0" // IR(48621, 49)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE\0" // IR(48670, 49)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION\0" // IR(48719, 44)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY\0" // IR(48763, 50)
  "DebugModuleINTEL\0" // IR(48813, 17)
  "acos\0" // IR(48830, 5)
  "acosh\0" // IR(48835, 6)
  "acospi\0" // IR(48841, 7)
  "asin\0" // IR(48848, 5)
  "asinh\0" // IR(48853, 6)
  "asinpi\0" // IR(48859, 7)
  "atan\0" // IR(48866, 5)
  "atan2\0" // IR(48871, 6)
  "atanh\0" // IR(48877, 6)
  "atanpi\0" // IR(48883, 7)
  "atan2pi\0" // IR(48890, 8)
  "cbrt\0" // IR(48898, 5)
  "ceil\0" // IR(48903, 5)
  "copysign\0" // IR(48908, 9)
  "cos\0" // IR(48917, 4)
  "cosh\0" // IR(48921, 5)
  "cospi\0" // IR(48926, 6)
  "erfc\0" // IR(48932, 5)
  "erf\0" // IR(48937, 4)
  "exp\0" // IR(48941, 4)
  "exp2\0" // IR(48945, 5)
  "exp10\0" // IR(48950, 6)
  "expm1\0" // IR(48956, 6)
  "fabs\0" // IR(48962, 5)
  "fdim\0" // IR(48967, 5)
  "floor\0" // IR(48972, 6)
  "fma\0" // IR(48978, 4)
  "fmax\0" // IR(48982, 5)
  "fmin\0" // IR(48987, 5)
  "fmod\0" // IR(48992, 5)
  "fract\0" // IR(48997, 6)
  "frexp\0" // IR(49003, 6)
  "hypot\0" // IR(49009, 6)
  "ilogb\0" // IR(49015, 6)
  "ldexp\0" // IR(49021, 6)
  "lgamma\0" // IR(49027, 7)
  "lgamma_r\0" // IR(49034, 9)
  "log\0" // IR(49043, 4)
  "log2\0" // IR(49047, 5)
  "log10\0" // IR(49052, 6)
  "log1p\0" // IR(49058, 6)
  "logb\0" // IR(49064, 5)
  "mad\0" // IR(49069, 4)
  "maxmag\0" // IR(49073, 7)
  "minmag\0" // IR(49080, 7)
  "modf\0" // IR(49087, 5)
  "nan\0" // IR(49092, 4)
  "nextafter\0" // IR(49096, 10)
  "pow\0" // IR(49106, 4)
  "pown\0" // IR(49110, 5)
  "powr\0" // IR(49115, 5)
  "remainder\0" // IR(49120, 10)
  "remquo\0" // IR(49130, 7)
  "rint\0" // IR(49137, 5)
  "rootn\0" // IR(49142, 6)
  "round\0" // IR(49148, 6)
  "rsqrt\0" // IR(49154, 6)
  "sin\0" // IR(49160, 4)
  "sincos\0" // IR(49164, 7)
  "sinh\0" // IR(49171, 5)
  "sinpi\0" // IR(49176, 6)
  "sqrt\0" // IR(49182, 5)
  "tan\0" // IR(49187, 4)
  "tanh\0" // IR(49191, 5)
  "tanpi\0" // IR(49196, 6)
  "tgamma\0" // IR(49202, 7)
  "trunc\0" // IR(49209, 6)
  "half_cos\0" // IR(49215, 9)
  "half_divide\0" // IR(49224, 12)
  "half_exp\0" // IR(49236, 9)
  "half_exp2\0" // IR(49245, 10)
  "half_exp10\0" // IR(49255, 11)
  "half_log\0" // IR(49266, 9)
  "half_log2\0" // IR(49275, 10)
  "half_log10\0" // IR(49285, 11)
  "half_powr\0" // IR(49296, 10)
  "half_recip\0" // IR(49306, 11)
  "half_rsqrt\0" // IR(49317, 11)
  "half_sin\0" // IR(49328, 9)
  "half_sqrt\0" // IR(49337, 10)
  "half_tan\0" // IR(49347, 9)
  "native_cos\0" // IR(49356, 11)
  "native_divide\0" // IR(49367, 14)
  "native_exp\0" // IR(49381, 11)
  "native_exp2\0" // IR(49392, 12)
  "native_exp10\0" // IR(49404, 13)
  "native_log\0" // IR(49417, 11)
  "native_log2\0" // IR(49428, 12)
  "native_log10\0" // IR(49440, 13)
  "native_powr\0" // IR(49453, 12)
  "native_recip\0" // IR(49465, 13)
  "native_rsqrt\0" // IR(49478, 13)
  "native_sin\0" // IR(49491, 11)
  "native_sqrt\0" // IR(49502, 12)
  "native_tan\0" // IR(49514, 11)
  "fclamp\0" // IR(49525, 7)
  "degrees\0" // IR(49532, 8)
  "fmax_common\0" // IR(49540, 12)
  "fmin_common\0" // IR(49552, 12)
  "mix\0" // IR(49564, 4)
  "radians\0" // IR(49568, 8)
  "step\0" // IR(49576, 5)
  "smoothstep\0" // IR(49581, 11)
  "sign\0" // IR(49592, 5)
  "cross\0" // IR(49597, 6)
  "distance\0" // IR(49603, 9)
  "length\0" // IR(49612, 7)
  "normalize\0" // IR(49619, 10)
  "fast_distance\0" // IR(49629, 14)
  "fast_length\0" // IR(49643, 12)
  "fast_normalize\0" // IR(49655, 15)
  "s_abs\0" // IR(49670, 6)
  "s_abs_diff\0" // IR(49676, 11)
  "s_add_sat\0" // IR(49687, 10)
  "u_add_sat\0" // IR(49697, 10)
  "s_hadd\0" // IR(49707, 7)
  "u_hadd\0" // IR(49714, 7)
  "s_rhadd\0" // IR(49721, 8)
  "u_rhadd\0" // IR(49729, 8)
  "s_clamp\0" // IR(49737, 8)
  "u_clamp\0" // IR(49745, 8)
  "clz\0" // IR(49753, 4)
  "ctz\0" // IR(49757, 4)
  "s_mad_hi\0" // IR(49761, 9)
  "u_mad_sat\0" // IR(49770, 10)
  "s_mad_sat\0" // IR(49780, 10)
  "s_max\0" // IR(49790, 6)
  "u_max\0" // IR(49796, 6)
  "s_min\0" // IR(49802, 6)
  "u_min\0" // IR(49808, 6)
  "s_mul_hi\0" // IR(49814, 9)
  "rotate\0" // IR(49823, 7)
  "s_sub_sat\0" // IR(49830, 10)
  "u_sub_sat\0" // IR(49840, 10)
  "u_upsample\0" // IR(49850, 11)
  "s_upsample\0" // IR(49861, 11)
  "popcount\0" // IR(49872, 9)
  "s_mad24\0" // IR(49881, 8)
  "u_mad24\0" // IR(49889, 8)
  "s_mul24\0" // IR(49897, 8)
  "u_mul24\0" // IR(49905, 8)
  "vloadn\0" // IR(49913, 7)
  "vstoren\0" // IR(49920, 8)
  "vload_half\0" // IR(49928, 11)
  "vload_halfn\0" // IR(49939, 12)
  "vstore_half\0" // IR(49951, 12)
  "vstore_half_r\0" // IR(49963, 14)
  "vstore_halfn\0" // IR(49977, 13)
  "vstore_halfn_r\0" // IR(49990, 15)
  "vloada_halfn\0" // IR(50005, 13)
  "vstorea_halfn\0" // IR(50018, 14)
  "vstorea_halfn_r\0" // IR(50032, 16)
  "shuffle\0" // IR(50048, 8)
  "shuffle2\0" // IR(50056, 9)
  "printf\0" // IR(50065, 7)
  "prefetch\0" // IR(50072, 9)
  "bitselect\0" // IR(50081, 10)
  "select\0" // IR(50091, 7)
  "u_abs\0" // IR(50098, 6)
  "u_abs_diff\0" // IR(50104, 11)
  "u_mul_hi\0" // IR(50115, 9)
  "u_mad_hi\0" // IR(50124, 9)
  "CubeFaceIndexAMD\0" // IR(50133, 17)
  "CubeFaceCoordAMD\0" // IR(50150, 17)
  "TimeAMD\0" // IR(50167, 8)
  "SwizzleInvocationsAMD\0" // IR(50175, 22)
  "SwizzleInvocationsMaskedAMD\0" // IR(50197, 28)
  "WriteInvocationAMD\0" // IR(50225, 19)
  "MbcntAMD\0" // IR(50244, 9)
  "InterpolateAtVertexAMD\0" // IR(50253, 23)
  "FMin3AMD\0" // IR(50276, 9)
  "UMin3AMD\0" // IR(50285, 9)
  "SMin3AMD\0" // IR(50294, 9)
  "FMax3AMD\0" // IR(50303, 9)
  "UMax3AMD\0" // IR(50312, 9)
  "SMax3AMD\0" // IR(50321, 9)
  "FMid3AMD\0" // IR(50330, 9)
  "UMid3AMD\0" // IR(50339, 9)
  "SMid3AMD\0" // IR(50348, 9)
;

// Array of IndexRanges, where each represents a string by referencing
// the kStrings table.
// This array contains all sequences of alias strings used in the grammar.
// This table is referenced by an IndexRange elsewhere, i.e. by the 'aliases'
// field of an instruction or operand description.
static const IndexRange kAliasSpans[] = {
  IR(4733, 27), // 0 PhysicalStorageBuffer64EXT
  IR(5644, 18), // 1 SubgroupEqMaskKHR
  IR(5699, 18), // 2 SubgroupGeMaskKHR
  IR(5732, 18), // 3 SubgroupGtMaskKHR
  IR(5765, 18), // 4 SubgroupLeMaskKHR
  IR(5798, 18), // 5 SubgroupLtMaskKHR
  IR(6656, 12), // 6 BaryCoordNV
  IR(6711, 19), // 7 BaryCoordNoPerspNV
  IR(6742, 15), // 8 FragmentSizeNV
  IR(6799, 22), // 9 InvocationsPerPixelNV
  IR(6927, 11), // 10 LaunchIdNV
  IR(6952, 13), // 11 LaunchSizeNV
  IR(6983, 17), // 12 WorldRayOriginNV
  IR(7021, 20), // 13 WorldRayDirectionNV
  IR(7060, 18), // 14 ObjectRayOriginNV
  IR(7100, 21), // 15 ObjectRayDirectionNV
  IR(7132, 10), // 16 RayTminNV
  IR(7153, 10), // 17 RayTmaxNV
  IR(7186, 22), // 18 InstanceCustomIndexNV
  IR(7225, 16), // 19 ObjectToWorldNV
  IR(7258, 16), // 20 WorldToObjectNV
  IR(7292, 10), // 21 HitKindNV
  IR(7523, 19), // 22 IncomingRayFlagsNV
  IR(9299, 28), // 23 StorageUniformBufferBlock16
  IR(9362, 17), // 24 StorageUniform16
  IR(10177, 27), // 25 ShaderViewportIndexLayerNV
  IR(10221, 22), // 26 FragmentBarycentricNV
  IR(10274, 30), // 27 ComputeDerivativeGroupQuadsNV
  IR(10304, 14), // 28 ShadingRateNV
  IR(10364, 20), // 29 ShaderNonUniformEXT
  IR(10407, 26), // 30 RuntimeDescriptorArrayEXT
  IR(10469, 39), // 31 InputAttachmentArrayDynamicIndexingEXT
  IR(10547, 42), // 32 UniformTexelBufferArrayDynamicIndexingEXT
  IR(10628, 42), // 33 StorageTexelBufferArrayDynamicIndexingEXT
  IR(10707, 40), // 34 UniformBufferArrayNonUniformIndexingEXT
  IR(10783, 39), // 35 SampledImageArrayNonUniformIndexingEXT
  IR(10859, 40), // 36 StorageBufferArrayNonUniformIndexingEXT
  IR(10935, 39), // 37 StorageImageArrayNonUniformIndexingEXT
  IR(11013, 42), // 38 InputAttachmentArrayNonUniformIndexingEXT
  IR(11097, 45), // 39 UniformTexelBufferArrayNonUniformIndexingEXT
  IR(11184, 45), // 40 StorageTexelBufferArrayNonUniformIndexingEXT
  IR(11247, 21), // 41 VulkanMemoryModelKHR
  IR(11297, 32), // 42 VulkanMemoryModelDeviceScopeKHR
  IR(11329, 34), // 43 PhysicalStorageBufferAddressesEXT
  IR(11395, 31), // 44 ComputeDerivativeGroupLinearNV
  IR(11599, 28), // 45 DemoteToHelperInvocationEXT
  IR(13069, 22), // 46 DotProductInputAllKHR
  IR(13113, 25), // 47 DotProductInput4x8BitKHR
  IR(13166, 31), // 48 DotProductInput4x8BitPackedKHR
  IR(13208, 14), // 49 DotProductKHR
  IR(13380, 13), // 50 OptNoneINTEL
  IR(16451, 15), // 51 PerPrimitiveNV
  IR(16499, 12), // 52 PerVertexNV
  IR(16522, 14), // 53 NonUniformEXT
  IR(16552, 19), // 54 RestrictPointerEXT
  IR(16586, 18), // 55 AliasedPointerEXT
  IR(16896, 24), // 56 HlslCounterBufferGOOGLE
  IR(16933, 19), // 57 HlslSemanticGOOGLE
  IR(19624, 14), // 58 OutputLinesNV
  IR(19658, 19), // 59 OutputPrimitivesNV
  IR(19701, 23), // 60 DerivativeGroupQuadsNV
  IR(19749, 24), // 61 DerivativeGroupLinearNV
  IR(19792, 18), // 62 OutputTrianglesNV
  IR(20540, 16), // 63 RayGenerationNV
  IR(20572, 15), // 64 IntersectionNV
  IR(20597, 9), // 65 AnyHitNV
  IR(20620, 13), // 66 ClosestHitNV
  IR(20641, 7), // 67 MissNV
  IR(20660, 11), // 68 CallableNV
  IR(20805, 23), // 69 AllowContractFastINTEL
  IR(20841, 18), // 70 AllowReassocINTEL
  IR(21295, 22), // 71 MakeTexelAvailableKHR
  IR(21334, 20), // 72 MakeTexelVisibleKHR
  IR(21370, 19), // 73 NonPrivateTexelKHR
  IR(21403, 17), // 74 VolatileTexelKHR
  IR(22780, 24), // 75 MakePointerAvailableKHR
  IR(22823, 22), // 76 MakePointerVisibleKHR
  IR(22863, 21), // 77 NonPrivatePointerKHR
  IR(22950, 10), // 78 VulkanKHR
  IR(14223, 5), // 79 None
  IR(23133, 16), // 80 OutputMemoryKHR
  IR(23163, 17), // 81 MakeAvailableKHR
  IR(23192, 15), // 82 MakeVisibleKHR
  IR(23268, 28), // 83 PackedVectorFormat4x8BitKHR
  IR(23583, 24), // 84 SkipBuiltinPrimitivesNV
  IR(24323, 15), // 85 QueueFamilyKHR
  IR(24694, 15), // 86 CallableDataNV
  IR(24733, 23), // 87 IncomingCallableDataNV
  IR(24770, 13), // 88 RayPayloadNV
  IR(24799, 15), // 89 HitAttributeNV
  IR(24836, 21), // 90 IncomingRayPayloadNV
  IR(24879, 21), // 91 ShaderRecordBufferNV
  IR(24922, 25), // 92 PhysicalStorageBufferEXT
  IR(32263, 8), // 93 SDotKHR
  IR(32276, 8), // 94 UDotKHR
  IR(32290, 9), // 95 SUDotKHR
  IR(32310, 14), // 96 SDotAccSatKHR
  IR(32335, 14), // 97 UDotAccSatKHR
  IR(32361, 15), // 98 SUDotAccSatKHR
  IR(34941, 21), // 99 ReportIntersectionNV
  IR(35116, 28), // 100 TypeAccelerationStructureNV
  IR(35197, 23), // 101 RayQueryGetClusterIdNV
  IR(37200, 21), // 102 DecorateStringGOOGLE
  IR(37242, 27), // 103 MemberDecorateStringGOOGLE
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
  spv::Capability::FMAKHR, // 236
  spv::Capability::SubgroupVoteKHR, // 237
  spv::Capability::GroupNonUniformRotateKHR, // 238
  spv::Capability::RayTracingKHR, // 239
  spv::Capability::RayQueryKHR, // 240
  spv::Capability::DotProduct, // 241
  spv::Capability::ReplicatedCompositesEXT, // 242
  spv::Capability::TextureSampleWeightedQCOM, // 243
  spv::Capability::TextureBoxFilterQCOM, // 244
  spv::Capability::TextureBlockMatchQCOM, // 245
  spv::Capability::CooperativeMatrixConversionQCOM, // 246
  spv::Capability::TextureBlockMatch2QCOM, // 247
  spv::Capability::FragmentMaskAMD, // 248
  spv::Capability::ShaderClockKHR, // 249
  spv::Capability::ShaderInvocationReorderNV, // 250
  spv::Capability::RayTracingMotionBlurNV, // 251
  spv::Capability::ImageFootprintNV, // 252
  spv::Capability::CooperativeVectorNV, // 253
  spv::Capability::CooperativeVectorTrainingNV, // 254
  spv::Capability::CooperativeMatrixConversionsNV, // 255
  spv::Capability::DisplacementMicromapNV, // 256
  spv::Capability::RayQueryPositionFetchKHR, // 257
  spv::Capability::RayTracingNV, // 258
  spv::Capability::RayTracingKHR, // 259
  spv::Capability::RayQueryKHR, // 260
  spv::Capability::DisplacementMicromapNV, // 261
  spv::Capability::CooperativeMatrixNV, // 262
  spv::Capability::FragmentShaderSampleInterlockEXT, // 263
  spv::Capability::FragmentShaderPixelInterlockEXT, // 264
  spv::Capability::FragmentShaderShadingRateInterlockEXT, // 265
  spv::Capability::CooperativeMatrixReductionsNV, // 266
  spv::Capability::CooperativeMatrixPerElementOperationsNV, // 267
  spv::Capability::TensorAddressingNV, // 268
  spv::Capability::DemoteToHelperInvocation, // 269
  spv::Capability::SubgroupShuffleINTEL, // 270
  spv::Capability::SubgroupBufferBlockIOINTEL, // 271
  spv::Capability::SubgroupImageBlockIOINTEL, // 272
  spv::Capability::SubgroupImageMediaBlockIOINTEL, // 273
  spv::Capability::IntegerFunctions2INTEL, // 274
  spv::Capability::AtomicFloat16MinMaxEXT, // 275
  spv::Capability::AtomicFloat32MinMaxEXT, // 276
  spv::Capability::AtomicFloat64MinMaxEXT, // 277
  spv::Capability::AtomicFloat16VectorNV, // 278
  spv::Capability::ExpectAssumeKHR, // 279
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 280
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 281
  spv::Capability::SubgroupAvcMotionEstimationIntraINTEL, // 282
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 283
  spv::Capability::SubgroupAvcMotionEstimationChromaINTEL, // 284
  spv::Capability::VariableLengthArrayINTEL, // 285
  spv::Capability::ArbitraryPrecisionFloatingPointINTEL, // 286
  spv::Capability::UnstructuredLoopControlsINTEL, // 287
  spv::Capability::BlockingPipesINTEL, // 288
  spv::Capability::FPGARegINTEL, // 289
  spv::Capability::AtomicFloat16AddEXT, // 290
  spv::Capability::AtomicFloat32AddEXT, // 291
  spv::Capability::AtomicFloat64AddEXT, // 292
  spv::Capability::AtomicFloat16VectorNV, // 293
  spv::Capability::LongCompositesINTEL, // 294
  spv::Capability::BFloat16ConversionINTEL, // 295
  spv::Capability::SplitBarrierINTEL, // 296
  spv::Capability::ArithmeticFenceEXT, // 297
  spv::Capability::TaskSequenceINTEL, // 298
  spv::Capability::SubgroupBufferPrefetchINTEL, // 299
  spv::Capability::Subgroup2DBlockTransformINTEL, // 300
  spv::Capability::Subgroup2DBlockTransposeINTEL, // 301
  spv::Capability::SubgroupMatrixMultiplyAccumulateINTEL, // 302
  spv::Capability::TernaryBitwiseFunctionINTEL, // 303
  spv::Capability::UntypedVariableLengthArrayINTEL, // 304
  spv::Capability::FunctionVariantsINTEL, // 305
  spv::Capability::GroupUniformArithmeticKHR, // 306
  spv::Capability::TensorFloat32RoundingINTEL, // 307
  spv::Capability::MaskedGatherScatterINTEL, // 308
  spv::Capability::BindlessImagesINTEL, // 309
  spv::Capability::Float64, // 310
  spv::Capability::InterpolationFunction, // 311
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
  spvtools::Extension::kSPV_KHR_fma, // 128
  spvtools::Extension::kSPV_EXT_shader_atomic_float_add, // 129
  spvtools::Extension::kSPV_INTEL_long_composites, // 130
  spvtools::Extension::kSPV_EXT_optnone, // 131
  spvtools::Extension::kSPV_INTEL_optnone, // 132
  spvtools::Extension::kSPV_EXT_shader_atomic_float16_add, // 133
  spvtools::Extension::kSPV_INTEL_debug_module, // 134
  spvtools::Extension::kSPV_INTEL_bfloat16_conversion, // 135
  spvtools::Extension::kSPV_INTEL_split_barrier, // 136
  spvtools::Extension::kSPV_EXT_arithmetic_fence, // 137
  spvtools::Extension::kSPV_INTEL_task_sequence, // 138
  spvtools::Extension::kSPV_INTEL_fp_max_error, // 139
  spvtools::Extension::kSPV_INTEL_fpga_latency_control, // 140
  spvtools::Extension::kSPV_INTEL_fpga_argument_interfaces, // 141
  spvtools::Extension::kSPV_INTEL_global_variable_host_access, // 142
  spvtools::Extension::kSPV_INTEL_global_variable_fpga_decorations, // 143
  spvtools::Extension::kSPV_INTEL_subgroup_buffer_prefetch, // 144
  spvtools::Extension::kSPV_INTEL_2d_block_io, // 145
  spvtools::Extension::kSPV_INTEL_subgroup_matrix_multiply_accumulate, // 146
  spvtools::Extension::kSPV_INTEL_ternary_bitwise_function, // 147
  spvtools::Extension::kSPV_INTEL_function_variants, // 148
  spvtools::Extension::kSPV_KHR_uniform_group_instructions, // 149
  spvtools::Extension::kSPV_INTEL_tensor_float32_conversion, // 150
  spvtools::Extension::kSPV_INTEL_masked_gather_scatter, // 151
  spvtools::Extension::kSPV_INTEL_cache_controls, // 152
  spvtools::Extension::kSPV_INTEL_maximum_registers, // 153
  spvtools::Extension::kSPV_INTEL_bindless_images, // 154
  spvtools::Extension::kSPV_KHR_no_integer_wrap_decoration, // 155
  spvtools::Extension::kSPV_NV_mesh_shader, // 156
  spvtools::Extension::kSPV_EXT_mesh_shader, // 157
  spvtools::Extension::kSPV_GOOGLE_hlsl_functionality1, // 158
  spvtools::Extension::kSPV_GOOGLE_user_type, // 159
  spvtools::Extension::kSPV_KHR_subgroup_uniform_control_flow, // 160
  spvtools::Extension::kSPV_AMD_shader_early_and_late_fragment_tests, // 161
  spvtools::Extension::kSPV_AMD_shader_early_and_late_fragment_tests, // 162
  spvtools::Extension::kSPV_EXT_shader_stencil_export, // 163
  spvtools::Extension::kSPV_KHR_maximal_reconvergence, // 164
  spvtools::Extension::kSPV_KHR_linkonce_odr, // 165
  spvtools::Extension::kSPV_KHR_storage_buffer_storage_class, // 166
  spvtools::Extension::kSPV_KHR_variable_pointers, // 167
  spvtools::Extension::kSPV_KHR_terminate_invocation, // 168
  spvtools::Extension::kSPV_KHR_relaxed_extended_instruction, // 169
  spvtools::Extension::kSPV_KHR_ray_tracing, // 170
  spvtools::Extension::kSPV_KHR_ray_query, // 171
  spvtools::Extension::kSPV_NV_ray_tracing, // 172
  spvtools::Extension::kSPV_KHR_ray_tracing, // 173
  spvtools::Extension::kSPV_KHR_ray_query, // 174
  spvtools::Extension::kSPV_NV_displacement_micromap, // 175
  spvtools::Extension::kSPV_GOOGLE_decorate_string, // 176
  spvtools::Extension::kSPV_GOOGLE_hlsl_functionality1, // 177
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
