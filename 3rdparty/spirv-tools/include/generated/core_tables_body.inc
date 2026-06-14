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
    case Extension::kSPV_EXT_demote_to_helper_invocation: return IR(1153, 36);
    case Extension::kSPV_EXT_descriptor_heap: return IR(1189, 24);
    case Extension::kSPV_EXT_descriptor_indexing: return IR(1213, 28);
    case Extension::kSPV_EXT_float8: return IR(1241, 15);
    case Extension::kSPV_EXT_fragment_fully_covered: return IR(1256, 31);
    case Extension::kSPV_EXT_fragment_invocation_density: return IR(1287, 36);
    case Extension::kSPV_EXT_fragment_shader_interlock: return IR(1323, 34);
    case Extension::kSPV_EXT_long_vector: return IR(1357, 20);
    case Extension::kSPV_EXT_mesh_shader: return IR(1377, 20);
    case Extension::kSPV_EXT_opacity_micromap: return IR(1397, 25);
    case Extension::kSPV_EXT_optnone: return IR(1422, 16);
    case Extension::kSPV_EXT_physical_storage_buffer: return IR(1438, 32);
    case Extension::kSPV_EXT_relaxed_printf_string_address_space: return IR(1470, 44);
    case Extension::kSPV_EXT_replicated_composites: return IR(1514, 30);
    case Extension::kSPV_EXT_shader_64bit_indexing: return IR(1544, 30);
    case Extension::kSPV_EXT_shader_atomic_float16_add: return IR(1574, 34);
    case Extension::kSPV_EXT_shader_atomic_float_add: return IR(1608, 32);
    case Extension::kSPV_EXT_shader_atomic_float_min_max: return IR(1640, 36);
    case Extension::kSPV_EXT_shader_image_int64: return IR(1676, 27);
    case Extension::kSPV_EXT_shader_invocation_reorder: return IR(1703, 34);
    case Extension::kSPV_EXT_shader_stencil_export: return IR(1737, 30);
    case Extension::kSPV_EXT_shader_subgroup_partitioned: return IR(1767, 36);
    case Extension::kSPV_EXT_shader_tile_image: return IR(1803, 26);
    case Extension::kSPV_EXT_shader_viewport_index_layer: return IR(1829, 36);
    case Extension::kSPV_EXT_split_barrier: return IR(1865, 22);
    case Extension::kSPV_GOOGLE_decorate_string: return IR(1887, 27);
    case Extension::kSPV_GOOGLE_hlsl_functionality1: return IR(1914, 31);
    case Extension::kSPV_GOOGLE_user_type: return IR(1945, 21);
    case Extension::kSPV_INTEL_2d_block_io: return IR(1966, 22);
    case Extension::kSPV_INTEL_arbitrary_precision_fixed_point: return IR(1988, 42);
    case Extension::kSPV_INTEL_arbitrary_precision_floating_point: return IR(2030, 45);
    case Extension::kSPV_INTEL_arbitrary_precision_integers: return IR(2075, 39);
    case Extension::kSPV_INTEL_bfloat16_conversion: return IR(2114, 30);
    case Extension::kSPV_INTEL_bindless_images: return IR(2144, 26);
    case Extension::kSPV_INTEL_blocking_pipes: return IR(2170, 25);
    case Extension::kSPV_INTEL_cache_controls: return IR(2195, 25);
    case Extension::kSPV_INTEL_debug_module: return IR(2220, 23);
    case Extension::kSPV_INTEL_device_side_avc_motion_estimation: return IR(2243, 44);
    case Extension::kSPV_INTEL_float_controls2: return IR(2287, 26);
    case Extension::kSPV_INTEL_fp_fast_math_mode: return IR(2313, 28);
    case Extension::kSPV_INTEL_fp_max_error: return IR(2341, 23);
    case Extension::kSPV_INTEL_fpga_argument_interfaces: return IR(2364, 35);
    case Extension::kSPV_INTEL_fpga_buffer_location: return IR(2399, 31);
    case Extension::kSPV_INTEL_fpga_cluster_attributes: return IR(2430, 34);
    case Extension::kSPV_INTEL_fpga_dsp_control: return IR(2464, 27);
    case Extension::kSPV_INTEL_fpga_invocation_pipelining_attributes: return IR(2491, 48);
    case Extension::kSPV_INTEL_fpga_latency_control: return IR(2539, 31);
    case Extension::kSPV_INTEL_fpga_loop_controls: return IR(2570, 29);
    case Extension::kSPV_INTEL_fpga_memory_accesses: return IR(2599, 31);
    case Extension::kSPV_INTEL_fpga_memory_attributes: return IR(2630, 33);
    case Extension::kSPV_INTEL_fpga_reg: return IR(2663, 19);
    case Extension::kSPV_INTEL_function_pointers: return IR(2682, 28);
    case Extension::kSPV_INTEL_function_variants: return IR(2710, 28);
    case Extension::kSPV_INTEL_global_variable_fpga_decorations: return IR(2738, 43);
    case Extension::kSPV_INTEL_global_variable_host_access: return IR(2781, 38);
    case Extension::kSPV_INTEL_inline_assembly: return IR(2819, 26);
    case Extension::kSPV_INTEL_int4: return IR(2845, 15);
    case Extension::kSPV_INTEL_io_pipes: return IR(2860, 19);
    case Extension::kSPV_INTEL_kernel_attributes: return IR(2879, 28);
    case Extension::kSPV_INTEL_long_composites: return IR(2907, 26);
    case Extension::kSPV_INTEL_loop_fuse: return IR(2933, 20);
    case Extension::kSPV_INTEL_masked_gather_scatter: return IR(2953, 32);
    case Extension::kSPV_INTEL_maximum_registers: return IR(2985, 28);
    case Extension::kSPV_INTEL_media_block_io: return IR(3013, 25);
    case Extension::kSPV_INTEL_memory_access_aliasing: return IR(3038, 33);
    case Extension::kSPV_INTEL_optnone: return IR(3071, 18);
    case Extension::kSPV_INTEL_predicated_io: return IR(3089, 24);
    case Extension::kSPV_INTEL_rounded_divide_sqrt: return IR(3113, 30);
    case Extension::kSPV_INTEL_runtime_aligned: return IR(3143, 26);
    case Extension::kSPV_INTEL_shader_integer_functions2: return IR(3169, 36);
    case Extension::kSPV_INTEL_split_barrier: return IR(3205, 24);
    case Extension::kSPV_INTEL_subgroup_buffer_prefetch: return IR(3229, 35);
    case Extension::kSPV_INTEL_subgroup_matrix_multiply_accumulate: return IR(3264, 46);
    case Extension::kSPV_INTEL_subgroups: return IR(3310, 20);
    case Extension::kSPV_INTEL_task_sequence: return IR(3330, 24);
    case Extension::kSPV_INTEL_tensor_float32_conversion: return IR(3354, 36);
    case Extension::kSPV_INTEL_ternary_bitwise_function: return IR(3390, 35);
    case Extension::kSPV_INTEL_unstructured_loop_controls: return IR(3425, 37);
    case Extension::kSPV_INTEL_usm_storage_classes: return IR(3462, 30);
    case Extension::kSPV_INTEL_variable_length_array: return IR(3492, 32);
    case Extension::kSPV_INTEL_vector_compute: return IR(3524, 25);
    case Extension::kSPV_KHR_16bit_storage: return IR(3549, 22);
    case Extension::kSPV_KHR_8bit_storage: return IR(3571, 21);
    case Extension::kSPV_KHR_abort: return IR(3592, 14);
    case Extension::kSPV_KHR_bfloat16: return IR(3606, 17);
    case Extension::kSPV_KHR_bit_instructions: return IR(3623, 25);
    case Extension::kSPV_KHR_compute_shader_derivatives: return IR(3648, 35);
    case Extension::kSPV_KHR_constant_data: return IR(3683, 22);
    case Extension::kSPV_KHR_cooperative_matrix: return IR(3705, 27);
    case Extension::kSPV_KHR_device_group: return IR(3732, 21);
    case Extension::kSPV_KHR_expect_assume: return IR(3753, 22);
    case Extension::kSPV_KHR_float_controls: return IR(3775, 23);
    case Extension::kSPV_KHR_float_controls2: return IR(3798, 24);
    case Extension::kSPV_KHR_fma: return IR(3822, 12);
    case Extension::kSPV_KHR_fragment_shader_barycentric: return IR(3834, 36);
    case Extension::kSPV_KHR_fragment_shading_rate: return IR(3870, 30);
    case Extension::kSPV_KHR_integer_dot_product: return IR(3900, 28);
    case Extension::kSPV_KHR_linkonce_odr: return IR(3928, 21);
    case Extension::kSPV_KHR_maximal_reconvergence: return IR(3949, 30);
    case Extension::kSPV_KHR_multiview: return IR(3979, 18);
    case Extension::kSPV_KHR_no_integer_wrap_decoration: return IR(3997, 35);
    case Extension::kSPV_KHR_non_semantic_info: return IR(4032, 26);
    case Extension::kSPV_KHR_opacity_micromap: return IR(4058, 25);
    case Extension::kSPV_KHR_physical_storage_buffer: return IR(4083, 32);
    case Extension::kSPV_KHR_poison_freeze: return IR(4115, 22);
    case Extension::kSPV_KHR_post_depth_coverage: return IR(4137, 28);
    case Extension::kSPV_KHR_quad_control: return IR(4165, 21);
    case Extension::kSPV_KHR_ray_cull_mask: return IR(4186, 22);
    case Extension::kSPV_KHR_ray_query: return IR(4208, 18);
    case Extension::kSPV_KHR_ray_tracing: return IR(4226, 20);
    case Extension::kSPV_KHR_ray_tracing_position_fetch: return IR(4246, 35);
    case Extension::kSPV_KHR_relaxed_extended_instruction: return IR(4281, 37);
    case Extension::kSPV_KHR_shader_atomic_counter_ops: return IR(4318, 34);
    case Extension::kSPV_KHR_shader_ballot: return IR(4352, 22);
    case Extension::kSPV_KHR_shader_clock: return IR(4374, 21);
    case Extension::kSPV_KHR_shader_draw_parameters: return IR(4395, 31);
    case Extension::kSPV_KHR_storage_buffer_storage_class: return IR(4426, 37);
    case Extension::kSPV_KHR_subgroup_rotate: return IR(4463, 24);
    case Extension::kSPV_KHR_subgroup_uniform_control_flow: return IR(4487, 38);
    case Extension::kSPV_KHR_subgroup_vote: return IR(4525, 22);
    case Extension::kSPV_KHR_terminate_invocation: return IR(4547, 29);
    case Extension::kSPV_KHR_uniform_group_instructions: return IR(4576, 35);
    case Extension::kSPV_KHR_untyped_pointers: return IR(4611, 25);
    case Extension::kSPV_KHR_variable_pointers: return IR(4636, 26);
    case Extension::kSPV_KHR_vulkan_memory_model: return IR(4662, 28);
    case Extension::kSPV_KHR_workgroup_memory_explicit_layout: return IR(4690, 41);
    case Extension::kSPV_NVX_multiview_per_view_attributes: return IR(4731, 38);
    case Extension::kSPV_NV_bindless_texture: return IR(4769, 24);
    case Extension::kSPV_NV_cluster_acceleration_structure: return IR(4793, 38);
    case Extension::kSPV_NV_compute_shader_derivatives: return IR(4831, 34);
    case Extension::kSPV_NV_cooperative_matrix: return IR(4865, 26);
    case Extension::kSPV_NV_cooperative_matrix2: return IR(4891, 27);
    case Extension::kSPV_NV_cooperative_matrix_decode_vector: return IR(4918, 40);
    case Extension::kSPV_NV_cooperative_vector: return IR(4958, 26);
    case Extension::kSPV_NV_displacement_micromap: return IR(4984, 29);
    case Extension::kSPV_NV_fragment_shader_barycentric: return IR(5013, 35);
    case Extension::kSPV_NV_geometry_shader_passthrough: return IR(5048, 35);
    case Extension::kSPV_NV_linear_swept_spheres: return IR(5083, 28);
    case Extension::kSPV_NV_mesh_shader: return IR(5111, 19);
    case Extension::kSPV_NV_push_constant_bank: return IR(5130, 26);
    case Extension::kSPV_NV_raw_access_chains: return IR(5156, 25);
    case Extension::kSPV_NV_ray_tracing: return IR(5181, 19);
    case Extension::kSPV_NV_ray_tracing_motion_blur: return IR(5200, 31);
    case Extension::kSPV_NV_sample_mask_override_coverage: return IR(5231, 37);
    case Extension::kSPV_NV_shader_atomic_fp16_vector: return IR(5268, 33);
    case Extension::kSPV_NV_shader_image_footprint: return IR(5301, 30);
    case Extension::kSPV_NV_shader_invocation_reorder: return IR(5331, 33);
    case Extension::kSPV_NV_shader_sm_builtins: return IR(5364, 26);
    case Extension::kSPV_NV_shader_subgroup_partitioned: return IR(5390, 35);
    case Extension::kSPV_NV_shading_rate: return IR(5425, 20);
    case Extension::kSPV_NV_stereo_view_rendering: return IR(5445, 29);
    case Extension::kSPV_NV_tensor_addressing: return IR(5474, 25);
    case Extension::kSPV_NV_viewport_array2: return IR(5499, 23);
    case Extension::kSPV_QCOM_cooperative_matrix_conversion: return IR(5522, 39);
    case Extension::kSPV_QCOM_image_processing: return IR(5561, 26);
    case Extension::kSPV_QCOM_image_processing2: return IR(5587, 27);
    case Extension::kSPV_QCOM_tile_shading: return IR(5614, 22);
    case Extension::kSPV_VALIDATOR_ignore_type_decl_unique: return IR(5636, 38);
    case Extension::kSPV_VALVE_mixed_float_dot_product: return IR(5674, 34);
    default: break;
  }
  return {};
}

// Extension names and values, ordered by name
// The fields in order are:
//   name, indexing into kStrings
//   enum value
static const std::array<NameValue,197> kExtensionNames{{
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
    {IR(1153, 36), static_cast<uint32_t>(kSPV_EXT_demote_to_helper_invocation)},
    {IR(1189, 24), static_cast<uint32_t>(kSPV_EXT_descriptor_heap)},
    {IR(1213, 28), static_cast<uint32_t>(kSPV_EXT_descriptor_indexing)},
    {IR(1241, 15), static_cast<uint32_t>(kSPV_EXT_float8)},
    {IR(1256, 31), static_cast<uint32_t>(kSPV_EXT_fragment_fully_covered)},
    {IR(1287, 36), static_cast<uint32_t>(kSPV_EXT_fragment_invocation_density)},
    {IR(1323, 34), static_cast<uint32_t>(kSPV_EXT_fragment_shader_interlock)},
    {IR(1357, 20), static_cast<uint32_t>(kSPV_EXT_long_vector)},
    {IR(1377, 20), static_cast<uint32_t>(kSPV_EXT_mesh_shader)},
    {IR(1397, 25), static_cast<uint32_t>(kSPV_EXT_opacity_micromap)},
    {IR(1422, 16), static_cast<uint32_t>(kSPV_EXT_optnone)},
    {IR(1438, 32), static_cast<uint32_t>(kSPV_EXT_physical_storage_buffer)},
    {IR(1470, 44), static_cast<uint32_t>(kSPV_EXT_relaxed_printf_string_address_space)},
    {IR(1514, 30), static_cast<uint32_t>(kSPV_EXT_replicated_composites)},
    {IR(1544, 30), static_cast<uint32_t>(kSPV_EXT_shader_64bit_indexing)},
    {IR(1574, 34), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float16_add)},
    {IR(1608, 32), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float_add)},
    {IR(1640, 36), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float_min_max)},
    {IR(1676, 27), static_cast<uint32_t>(kSPV_EXT_shader_image_int64)},
    {IR(1703, 34), static_cast<uint32_t>(kSPV_EXT_shader_invocation_reorder)},
    {IR(1737, 30), static_cast<uint32_t>(kSPV_EXT_shader_stencil_export)},
    {IR(1767, 36), static_cast<uint32_t>(kSPV_EXT_shader_subgroup_partitioned)},
    {IR(1803, 26), static_cast<uint32_t>(kSPV_EXT_shader_tile_image)},
    {IR(1829, 36), static_cast<uint32_t>(kSPV_EXT_shader_viewport_index_layer)},
    {IR(1865, 22), static_cast<uint32_t>(kSPV_EXT_split_barrier)},
    {IR(1887, 27), static_cast<uint32_t>(kSPV_GOOGLE_decorate_string)},
    {IR(1914, 31), static_cast<uint32_t>(kSPV_GOOGLE_hlsl_functionality1)},
    {IR(1945, 21), static_cast<uint32_t>(kSPV_GOOGLE_user_type)},
    {IR(1966, 22), static_cast<uint32_t>(kSPV_INTEL_2d_block_io)},
    {IR(1988, 42), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_fixed_point)},
    {IR(2030, 45), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_floating_point)},
    {IR(2075, 39), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_integers)},
    {IR(2114, 30), static_cast<uint32_t>(kSPV_INTEL_bfloat16_conversion)},
    {IR(2144, 26), static_cast<uint32_t>(kSPV_INTEL_bindless_images)},
    {IR(2170, 25), static_cast<uint32_t>(kSPV_INTEL_blocking_pipes)},
    {IR(2195, 25), static_cast<uint32_t>(kSPV_INTEL_cache_controls)},
    {IR(2220, 23), static_cast<uint32_t>(kSPV_INTEL_debug_module)},
    {IR(2243, 44), static_cast<uint32_t>(kSPV_INTEL_device_side_avc_motion_estimation)},
    {IR(2287, 26), static_cast<uint32_t>(kSPV_INTEL_float_controls2)},
    {IR(2313, 28), static_cast<uint32_t>(kSPV_INTEL_fp_fast_math_mode)},
    {IR(2341, 23), static_cast<uint32_t>(kSPV_INTEL_fp_max_error)},
    {IR(2364, 35), static_cast<uint32_t>(kSPV_INTEL_fpga_argument_interfaces)},
    {IR(2399, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_buffer_location)},
    {IR(2430, 34), static_cast<uint32_t>(kSPV_INTEL_fpga_cluster_attributes)},
    {IR(2464, 27), static_cast<uint32_t>(kSPV_INTEL_fpga_dsp_control)},
    {IR(2491, 48), static_cast<uint32_t>(kSPV_INTEL_fpga_invocation_pipelining_attributes)},
    {IR(2539, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_latency_control)},
    {IR(2570, 29), static_cast<uint32_t>(kSPV_INTEL_fpga_loop_controls)},
    {IR(2599, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_memory_accesses)},
    {IR(2630, 33), static_cast<uint32_t>(kSPV_INTEL_fpga_memory_attributes)},
    {IR(2663, 19), static_cast<uint32_t>(kSPV_INTEL_fpga_reg)},
    {IR(2682, 28), static_cast<uint32_t>(kSPV_INTEL_function_pointers)},
    {IR(2710, 28), static_cast<uint32_t>(kSPV_INTEL_function_variants)},
    {IR(2738, 43), static_cast<uint32_t>(kSPV_INTEL_global_variable_fpga_decorations)},
    {IR(2781, 38), static_cast<uint32_t>(kSPV_INTEL_global_variable_host_access)},
    {IR(2819, 26), static_cast<uint32_t>(kSPV_INTEL_inline_assembly)},
    {IR(2845, 15), static_cast<uint32_t>(kSPV_INTEL_int4)},
    {IR(2860, 19), static_cast<uint32_t>(kSPV_INTEL_io_pipes)},
    {IR(2879, 28), static_cast<uint32_t>(kSPV_INTEL_kernel_attributes)},
    {IR(2907, 26), static_cast<uint32_t>(kSPV_INTEL_long_composites)},
    {IR(2933, 20), static_cast<uint32_t>(kSPV_INTEL_loop_fuse)},
    {IR(2953, 32), static_cast<uint32_t>(kSPV_INTEL_masked_gather_scatter)},
    {IR(2985, 28), static_cast<uint32_t>(kSPV_INTEL_maximum_registers)},
    {IR(3013, 25), static_cast<uint32_t>(kSPV_INTEL_media_block_io)},
    {IR(3038, 33), static_cast<uint32_t>(kSPV_INTEL_memory_access_aliasing)},
    {IR(3071, 18), static_cast<uint32_t>(kSPV_INTEL_optnone)},
    {IR(3089, 24), static_cast<uint32_t>(kSPV_INTEL_predicated_io)},
    {IR(3113, 30), static_cast<uint32_t>(kSPV_INTEL_rounded_divide_sqrt)},
    {IR(3143, 26), static_cast<uint32_t>(kSPV_INTEL_runtime_aligned)},
    {IR(3169, 36), static_cast<uint32_t>(kSPV_INTEL_shader_integer_functions2)},
    {IR(3205, 24), static_cast<uint32_t>(kSPV_INTEL_split_barrier)},
    {IR(3229, 35), static_cast<uint32_t>(kSPV_INTEL_subgroup_buffer_prefetch)},
    {IR(3264, 46), static_cast<uint32_t>(kSPV_INTEL_subgroup_matrix_multiply_accumulate)},
    {IR(3310, 20), static_cast<uint32_t>(kSPV_INTEL_subgroups)},
    {IR(3330, 24), static_cast<uint32_t>(kSPV_INTEL_task_sequence)},
    {IR(3354, 36), static_cast<uint32_t>(kSPV_INTEL_tensor_float32_conversion)},
    {IR(3390, 35), static_cast<uint32_t>(kSPV_INTEL_ternary_bitwise_function)},
    {IR(3425, 37), static_cast<uint32_t>(kSPV_INTEL_unstructured_loop_controls)},
    {IR(3462, 30), static_cast<uint32_t>(kSPV_INTEL_usm_storage_classes)},
    {IR(3492, 32), static_cast<uint32_t>(kSPV_INTEL_variable_length_array)},
    {IR(3524, 25), static_cast<uint32_t>(kSPV_INTEL_vector_compute)},
    {IR(3549, 22), static_cast<uint32_t>(kSPV_KHR_16bit_storage)},
    {IR(3571, 21), static_cast<uint32_t>(kSPV_KHR_8bit_storage)},
    {IR(3592, 14), static_cast<uint32_t>(kSPV_KHR_abort)},
    {IR(3606, 17), static_cast<uint32_t>(kSPV_KHR_bfloat16)},
    {IR(3623, 25), static_cast<uint32_t>(kSPV_KHR_bit_instructions)},
    {IR(3648, 35), static_cast<uint32_t>(kSPV_KHR_compute_shader_derivatives)},
    {IR(3683, 22), static_cast<uint32_t>(kSPV_KHR_constant_data)},
    {IR(3705, 27), static_cast<uint32_t>(kSPV_KHR_cooperative_matrix)},
    {IR(3732, 21), static_cast<uint32_t>(kSPV_KHR_device_group)},
    {IR(3753, 22), static_cast<uint32_t>(kSPV_KHR_expect_assume)},
    {IR(3775, 23), static_cast<uint32_t>(kSPV_KHR_float_controls)},
    {IR(3798, 24), static_cast<uint32_t>(kSPV_KHR_float_controls2)},
    {IR(3822, 12), static_cast<uint32_t>(kSPV_KHR_fma)},
    {IR(3834, 36), static_cast<uint32_t>(kSPV_KHR_fragment_shader_barycentric)},
    {IR(3870, 30), static_cast<uint32_t>(kSPV_KHR_fragment_shading_rate)},
    {IR(3900, 28), static_cast<uint32_t>(kSPV_KHR_integer_dot_product)},
    {IR(3928, 21), static_cast<uint32_t>(kSPV_KHR_linkonce_odr)},
    {IR(3949, 30), static_cast<uint32_t>(kSPV_KHR_maximal_reconvergence)},
    {IR(3979, 18), static_cast<uint32_t>(kSPV_KHR_multiview)},
    {IR(3997, 35), static_cast<uint32_t>(kSPV_KHR_no_integer_wrap_decoration)},
    {IR(4032, 26), static_cast<uint32_t>(kSPV_KHR_non_semantic_info)},
    {IR(4058, 25), static_cast<uint32_t>(kSPV_KHR_opacity_micromap)},
    {IR(4083, 32), static_cast<uint32_t>(kSPV_KHR_physical_storage_buffer)},
    {IR(4115, 22), static_cast<uint32_t>(kSPV_KHR_poison_freeze)},
    {IR(4137, 28), static_cast<uint32_t>(kSPV_KHR_post_depth_coverage)},
    {IR(4165, 21), static_cast<uint32_t>(kSPV_KHR_quad_control)},
    {IR(4186, 22), static_cast<uint32_t>(kSPV_KHR_ray_cull_mask)},
    {IR(4208, 18), static_cast<uint32_t>(kSPV_KHR_ray_query)},
    {IR(4226, 20), static_cast<uint32_t>(kSPV_KHR_ray_tracing)},
    {IR(4246, 35), static_cast<uint32_t>(kSPV_KHR_ray_tracing_position_fetch)},
    {IR(4281, 37), static_cast<uint32_t>(kSPV_KHR_relaxed_extended_instruction)},
    {IR(4318, 34), static_cast<uint32_t>(kSPV_KHR_shader_atomic_counter_ops)},
    {IR(4352, 22), static_cast<uint32_t>(kSPV_KHR_shader_ballot)},
    {IR(4374, 21), static_cast<uint32_t>(kSPV_KHR_shader_clock)},
    {IR(4395, 31), static_cast<uint32_t>(kSPV_KHR_shader_draw_parameters)},
    {IR(4426, 37), static_cast<uint32_t>(kSPV_KHR_storage_buffer_storage_class)},
    {IR(4463, 24), static_cast<uint32_t>(kSPV_KHR_subgroup_rotate)},
    {IR(4487, 38), static_cast<uint32_t>(kSPV_KHR_subgroup_uniform_control_flow)},
    {IR(4525, 22), static_cast<uint32_t>(kSPV_KHR_subgroup_vote)},
    {IR(4547, 29), static_cast<uint32_t>(kSPV_KHR_terminate_invocation)},
    {IR(4576, 35), static_cast<uint32_t>(kSPV_KHR_uniform_group_instructions)},
    {IR(4611, 25), static_cast<uint32_t>(kSPV_KHR_untyped_pointers)},
    {IR(4636, 26), static_cast<uint32_t>(kSPV_KHR_variable_pointers)},
    {IR(4662, 28), static_cast<uint32_t>(kSPV_KHR_vulkan_memory_model)},
    {IR(4690, 41), static_cast<uint32_t>(kSPV_KHR_workgroup_memory_explicit_layout)},
    {IR(4731, 38), static_cast<uint32_t>(kSPV_NVX_multiview_per_view_attributes)},
    {IR(4769, 24), static_cast<uint32_t>(kSPV_NV_bindless_texture)},
    {IR(4793, 38), static_cast<uint32_t>(kSPV_NV_cluster_acceleration_structure)},
    {IR(4831, 34), static_cast<uint32_t>(kSPV_NV_compute_shader_derivatives)},
    {IR(4865, 26), static_cast<uint32_t>(kSPV_NV_cooperative_matrix)},
    {IR(4891, 27), static_cast<uint32_t>(kSPV_NV_cooperative_matrix2)},
    {IR(4918, 40), static_cast<uint32_t>(kSPV_NV_cooperative_matrix_decode_vector)},
    {IR(4958, 26), static_cast<uint32_t>(kSPV_NV_cooperative_vector)},
    {IR(4984, 29), static_cast<uint32_t>(kSPV_NV_displacement_micromap)},
    {IR(5013, 35), static_cast<uint32_t>(kSPV_NV_fragment_shader_barycentric)},
    {IR(5048, 35), static_cast<uint32_t>(kSPV_NV_geometry_shader_passthrough)},
    {IR(5083, 28), static_cast<uint32_t>(kSPV_NV_linear_swept_spheres)},
    {IR(5111, 19), static_cast<uint32_t>(kSPV_NV_mesh_shader)},
    {IR(5130, 26), static_cast<uint32_t>(kSPV_NV_push_constant_bank)},
    {IR(5156, 25), static_cast<uint32_t>(kSPV_NV_raw_access_chains)},
    {IR(5181, 19), static_cast<uint32_t>(kSPV_NV_ray_tracing)},
    {IR(5200, 31), static_cast<uint32_t>(kSPV_NV_ray_tracing_motion_blur)},
    {IR(5231, 37), static_cast<uint32_t>(kSPV_NV_sample_mask_override_coverage)},
    {IR(5268, 33), static_cast<uint32_t>(kSPV_NV_shader_atomic_fp16_vector)},
    {IR(5301, 30), static_cast<uint32_t>(kSPV_NV_shader_image_footprint)},
    {IR(5331, 33), static_cast<uint32_t>(kSPV_NV_shader_invocation_reorder)},
    {IR(5364, 26), static_cast<uint32_t>(kSPV_NV_shader_sm_builtins)},
    {IR(5390, 35), static_cast<uint32_t>(kSPV_NV_shader_subgroup_partitioned)},
    {IR(5425, 20), static_cast<uint32_t>(kSPV_NV_shading_rate)},
    {IR(5445, 29), static_cast<uint32_t>(kSPV_NV_stereo_view_rendering)},
    {IR(5474, 25), static_cast<uint32_t>(kSPV_NV_tensor_addressing)},
    {IR(5499, 23), static_cast<uint32_t>(kSPV_NV_viewport_array2)},
    {IR(5522, 39), static_cast<uint32_t>(kSPV_QCOM_cooperative_matrix_conversion)},
    {IR(5561, 26), static_cast<uint32_t>(kSPV_QCOM_image_processing)},
    {IR(5587, 27), static_cast<uint32_t>(kSPV_QCOM_image_processing2)},
    {IR(5614, 22), static_cast<uint32_t>(kSPV_QCOM_tile_shading)},
    {IR(5636, 38), static_cast<uint32_t>(kSPV_VALIDATOR_ignore_type_decl_unique)},
    {IR(5674, 34), static_cast<uint32_t>(kSPV_VALVE_mixed_float_dot_product)},
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
static const std::array<OperandDesc, 1221> kOperandsByValue{{
  {0,IR(0, 0),IR(5708, 9)/* ReadOnly */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {1,IR(0, 0),IR(5724, 10)/* WriteOnly */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {2,IR(0, 0),IR(5734, 10)/* ReadWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {0,IR(0, 0),IR(5744, 8)/* Logical */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {1,IR(0, 0),IR(5752, 11)/* Physical32 */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {2,IR(0, 0),IR(5773, 11)/* Physical64 */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {5348,IR(0, 0),IR(5784, 24)/* PhysicalStorageBuffer64 */,IR(0, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {0,IR(0, 0),IR(5866, 9)/* Position */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {1,IR(0, 0),IR(5882, 10)/* PointSize */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {3,IR(0, 0),IR(5892, 13)/* ClipDistance */,IR(0, 0),IR(4, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4,IR(0, 0),IR(5905, 13)/* CullDistance */,IR(0, 0),IR(5, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5,IR(0, 0),IR(5918, 9)/* VertexId */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {6,IR(0, 0),IR(5927, 11)/* InstanceId */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {7,IR(0, 0),IR(5938, 12)/* PrimitiveId */,IR(0, 0),IR(6, 6),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {8,IR(0, 0),IR(6028, 13)/* InvocationId */,IR(0, 0),IR(12, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {9,IR(0, 0),IR(6041, 6)/* Layer */,IR(0, 0),IR(14, 5),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {10,IR(0, 0),IR(6087, 14)/* ViewportIndex */,IR(0, 0),IR(19, 5),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {11,IR(0, 0),IR(6135, 15)/* TessLevelOuter */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {12,IR(0, 0),IR(6150, 15)/* TessLevelInner */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {13,IR(0, 0),IR(6165, 10)/* TessCoord */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {14,IR(0, 0),IR(6175, 14)/* PatchVertices */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {15,IR(0, 0),IR(6189, 10)/* FragCoord */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {16,IR(0, 0),IR(6199, 11)/* PointCoord */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {17,IR(0, 0),IR(6210, 12)/* FrontFacing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {18,IR(0, 0),IR(6222, 9)/* SampleId */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {19,IR(0, 0),IR(6249, 15)/* SamplePosition */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {20,IR(0, 0),IR(6264, 11)/* SampleMask */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {22,IR(0, 0),IR(6275, 10)/* FragDepth */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {23,IR(0, 0),IR(6285, 17)/* HelperInvocation */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {24,IR(0, 0),IR(6302, 14)/* NumWorkgroups */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {25,IR(0, 0),IR(6316, 14)/* WorkgroupSize */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {26,IR(0, 0),IR(6330, 12)/* WorkgroupId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {27,IR(0, 0),IR(6342, 18)/* LocalInvocationId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {28,IR(0, 0),IR(6360, 19)/* GlobalInvocationId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {29,IR(0, 0),IR(6379, 21)/* LocalInvocationIndex */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {30,IR(0, 0),IR(6400, 8)/* WorkDim */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {31,IR(0, 0),IR(6408, 11)/* GlobalSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {32,IR(0, 0),IR(6419, 22)/* EnqueuedWorkgroupSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {33,IR(0, 0),IR(6441, 13)/* GlobalOffset */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {34,IR(0, 0),IR(6454, 15)/* GlobalLinearId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {36,IR(0, 0),IR(6469, 13)/* SubgroupSize */,IR(0, 0),IR(26, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {37,IR(0, 0),IR(6516, 16)/* SubgroupMaxSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {38,IR(0, 0),IR(6532, 13)/* NumSubgroups */,IR(0, 0),IR(29, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {39,IR(0, 0),IR(6545, 21)/* NumEnqueuedSubgroups */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {40,IR(0, 0),IR(6566, 11)/* SubgroupId */,IR(0, 0),IR(29, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {41,IR(0, 0),IR(6577, 26)/* SubgroupLocalInvocationId */,IR(0, 0),IR(26, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {42,IR(0, 0),IR(6603, 12)/* VertexIndex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {43,IR(0, 0),IR(6615, 14)/* InstanceIndex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4160,IR(0, 0),IR(6629, 10)/* CoreIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4161,IR(0, 0),IR(6655, 13)/* CoreCountARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4162,IR(0, 0),IR(6668, 13)/* CoreMaxIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4163,IR(0, 0),IR(6681, 10)/* WarpIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4164,IR(0, 0),IR(6691, 13)/* WarpMaxIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4416,IR(0, 0),IR(6704, 15)/* SubgroupEqMask */,IR(1, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4417,IR(0, 0),IR(6759, 15)/* SubgroupGeMask */,IR(2, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4418,IR(0, 0),IR(6792, 15)/* SubgroupGtMask */,IR(3, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4419,IR(0, 0),IR(6825, 15)/* SubgroupLeMask */,IR(4, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4420,IR(0, 0),IR(6858, 15)/* SubgroupLtMask */,IR(5, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4424,IR(0, 0),IR(6891, 11)/* BaseVertex */,IR(0, 0),IR(34, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4425,IR(0, 0),IR(6917, 13)/* BaseInstance */,IR(0, 0),IR(34, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4426,IR(0, 0),IR(6930, 10)/* DrawIndex */,IR(0, 0),IR(35, 3),IR(4, 3),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4432,IR(0, 0),IR(6940, 24)/* PrimitiveShadingRateKHR */,IR(0, 0),IR(38, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4438,IR(0, 0),IR(6987, 12)/* DeviceIndex */,IR(0, 0),IR(39, 1),IR(8, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4440,IR(0, 0),IR(7011, 10)/* ViewIndex */,IR(0, 0),IR(40, 1),IR(9, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4444,IR(0, 0),IR(7031, 15)/* ShadingRateKHR */,IR(0, 0),IR(38, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4492,IR(0, 0),IR(7046, 15)/* TileOffsetQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4493,IR(0, 0),IR(7077, 18)/* TileDimensionQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4494,IR(0, 0),IR(7095, 18)/* TileApronSizeQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4992,IR(0, 0),IR(7113, 20)/* BaryCoordNoPerspAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4993,IR(0, 0),IR(7133, 28)/* BaryCoordNoPerspCentroidAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4994,IR(0, 0),IR(7161, 26)/* BaryCoordNoPerspSampleAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4995,IR(0, 0),IR(7187, 19)/* BaryCoordSmoothAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4996,IR(0, 0),IR(7206, 27)/* BaryCoordSmoothCentroidAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4997,IR(0, 0),IR(7233, 25)/* BaryCoordSmoothSampleAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4998,IR(0, 0),IR(7258, 22)/* BaryCoordPullModelAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5014,IR(0, 0),IR(7280, 18)/* FragStencilRefEXT */,IR(0, 0),IR(42, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5021,IR(0, 0),IR(7315, 29)/* RemainingRecursionLevelsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5073,IR(0, 0),IR(7362, 16)/* ShaderIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5122,IR(0, 0),IR(7378, 15)/* SamplerHeapEXT */,IR(0, 0),IR(44, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5123,IR(0, 0),IR(7411, 16)/* ResourceHeapEXT */,IR(0, 0),IR(44, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5253,IR(0, 0),IR(7427, 15)/* ViewportMaskNV */,IR(0, 0),IR(45, 2),IR(12, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5257,IR(0, 0),IR(7463, 20)/* SecondaryPositionNV */,IR(0, 0),IR(47, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5258,IR(0, 0),IR(7502, 24)/* SecondaryViewportMaskNV */,IR(0, 0),IR(47, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5261,IR(0, 0),IR(7526, 18)/* PositionPerViewNV */,IR(0, 0),IR(48, 2),IR(15, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5262,IR(0, 0),IR(7564, 22)/* ViewportMaskPerViewNV */,IR(0, 0),IR(48, 2),IR(15, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5264,IR(0, 0),IR(7586, 16)/* FullyCoveredEXT */,IR(0, 0),IR(50, 1),IR(17, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5274,IR(0, 0),IR(7626, 12)/* TaskCountNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5275,IR(0, 0),IR(7638, 17)/* PrimitiveCountNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5276,IR(0, 0),IR(7655, 19)/* PrimitiveIndicesNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5277,IR(0, 0),IR(7674, 22)/* ClipDistancePerViewNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5278,IR(0, 0),IR(7696, 22)/* CullDistancePerViewNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5279,IR(0, 0),IR(7718, 15)/* LayerPerViewNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5280,IR(0, 0),IR(7733, 16)/* MeshViewCountNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5281,IR(0, 0),IR(7749, 18)/* MeshViewIndicesNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5286,IR(0, 0),IR(7767, 13)/* BaryCoordKHR */,IR(6, 1),IR(52, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5287,IR(0, 0),IR(7815, 20)/* BaryCoordNoPerspKHR */,IR(7, 1),IR(52, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5292,IR(0, 0),IR(7854, 12)/* FragSizeEXT */,IR(8, 1),IR(53, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5293,IR(0, 0),IR(7900, 23)/* FragInvocationCountEXT */,IR(9, 1),IR(53, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5294,IR(0, 0),IR(7945, 25)/* PrimitivePointIndicesEXT */,IR(0, 0),IR(54, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5295,IR(0, 0),IR(7970, 24)/* PrimitiveLineIndicesEXT */,IR(0, 0),IR(54, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5296,IR(0, 0),IR(7994, 28)/* PrimitiveTriangleIndicesEXT */,IR(0, 0),IR(54, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5299,IR(0, 0),IR(8022, 17)/* CullPrimitiveEXT */,IR(0, 0),IR(54, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5319,IR(0, 0),IR(8039, 12)/* LaunchIdKHR */,IR(10, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5320,IR(0, 0),IR(8062, 14)/* LaunchSizeKHR */,IR(11, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5321,IR(0, 0),IR(8089, 18)/* WorldRayOriginKHR */,IR(12, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5322,IR(0, 0),IR(8124, 21)/* WorldRayDirectionKHR */,IR(13, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5323,IR(0, 0),IR(8165, 19)/* ObjectRayOriginKHR */,IR(14, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5324,IR(0, 0),IR(8202, 22)/* ObjectRayDirectionKHR */,IR(15, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5325,IR(0, 0),IR(8245, 11)/* RayTminKHR */,IR(16, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5326,IR(0, 0),IR(8266, 11)/* RayTmaxKHR */,IR(17, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5327,IR(0, 0),IR(8287, 23)/* InstanceCustomIndexKHR */,IR(18, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5330,IR(0, 0),IR(8332, 17)/* ObjectToWorldKHR */,IR(19, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5331,IR(0, 0),IR(8365, 17)/* WorldToObjectKHR */,IR(20, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5332,IR(0, 0),IR(8398, 7)/* HitTNV */,IR(0, 0),IR(57, 1),IR(26, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5333,IR(0, 0),IR(8405, 11)/* HitKindKHR */,IR(21, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5334,IR(0, 0),IR(8426, 17)/* CurrentRayTimeNV */,IR(0, 0),IR(58, 1),IR(27, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5335,IR(0, 0),IR(8466, 30)/* HitTriangleVertexPositionsKHR */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5337,IR(0, 0),IR(8523, 34)/* HitMicroTriangleVertexPositionsNV */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5344,IR(0, 0),IR(8590, 37)/* HitMicroTriangleVertexBarycentricsNV */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5351,IR(0, 0),IR(8627, 20)/* IncomingRayFlagsKHR */,IR(22, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5352,IR(0, 0),IR(8666, 20)/* RayGeometryIndexKHR */,IR(0, 0),IR(61, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5359,IR(0, 0),IR(8686, 14)/* HitIsSphereNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5360,IR(0, 0),IR(8728, 11)/* HitIsLSSNV */,IR(0, 0),IR(63, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5361,IR(0, 0),IR(8778, 20)/* HitSpherePositionNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5374,IR(0, 0),IR(8798, 13)/* WarpsPerSMNV */,IR(0, 0),IR(64, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5375,IR(0, 0),IR(8830, 10)/* SMCountNV */,IR(0, 0),IR(64, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5376,IR(0, 0),IR(8840, 9)/* WarpIDNV */,IR(0, 0),IR(64, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5377,IR(0, 0),IR(8849, 7)/* SMIDNV */,IR(0, 0),IR(64, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5396,IR(0, 0),IR(8856, 18)/* HitLSSPositionsNV */,IR(0, 0),IR(63, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5405,IR(0, 0),IR(8874, 34)/* HitKindFrontFacingMicroTriangleNV */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5406,IR(0, 0),IR(8908, 33)/* HitKindBackFacingMicroTriangleNV */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5420,IR(0, 0),IR(8941, 18)/* HitSphereRadiusNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5421,IR(0, 0),IR(8959, 14)/* HitLSSRadiiNV */,IR(0, 0),IR(63, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5436,IR(0, 0),IR(8973, 12)/* ClusterIDNV */,IR(0, 0),IR(65, 1),IR(31, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {6021,IR(0, 0),IR(9026, 12)/* CullMaskKHR */,IR(0, 0),IR(66, 1),IR(32, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {0,IR(0, 0),IR(9053, 7)/* Matrix */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {1,IR(0, 0),IR(5875, 7)/* Shader */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {2,IR(0, 0),IR(5950, 9)/* Geometry */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {3,IR(0, 0),IR(5959, 13)/* Tessellation */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4,IR(0, 0),IR(5763, 10)/* Addresses */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5,IR(0, 0),IR(9060, 8)/* Linkage */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6,IR(0, 0),IR(5717, 7)/* Kernel */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {7,IR(0, 0),IR(9068, 9)/* Vector16 */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {8,IR(0, 0),IR(9077, 14)/* Float16Buffer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {9,IR(0, 0),IR(9091, 8)/* Float16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {10,IR(0, 0),IR(9099, 8)/* Float64 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {11,IR(0, 0),IR(9107, 6)/* Int64 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {12,IR(0, 0),IR(9113, 13)/* Int64Atomics */,IR(0, 0),IR(68, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {13,IR(0, 0),IR(9126, 11)/* ImageBasic */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {14,IR(0, 0),IR(9137, 15)/* ImageReadWrite */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {15,IR(0, 0),IR(9152, 12)/* ImageMipmap */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {17,IR(0, 0),IR(9164, 6)/* Pipes */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {18,IR(0, 0),IR(9170, 7)/* Groups */,IR(0, 0),IR(1, 0),IR(33, 1),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {19,IR(0, 0),IR(9177, 14)/* DeviceEnqueue */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {20,IR(0, 0),IR(9191, 15)/* LiteralSampler */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {21,IR(0, 0),IR(9206, 14)/* AtomicStorage */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {22,IR(0, 0),IR(9220, 6)/* Int16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {23,IR(0, 0),IR(9226, 22)/* TessellationPointSize */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {24,IR(0, 0),IR(9248, 18)/* GeometryPointSize */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {25,IR(0, 0),IR(9266, 20)/* ImageGatherExtended */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {27,IR(0, 0),IR(9286, 24)/* StorageImageMultisample */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {28,IR(0, 0),IR(9310, 34)/* UniformBufferArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {29,IR(0, 0),IR(9344, 33)/* SampledImageArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {30,IR(0, 0),IR(9377, 34)/* StorageBufferArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {31,IR(0, 0),IR(9411, 33)/* StorageImageArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {32,IR(0, 0),IR(5892, 13)/* ClipDistance */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {33,IR(0, 0),IR(5905, 13)/* CullDistance */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {34,IR(0, 0),IR(9444, 15)/* ImageCubeArray */,IR(0, 0),IR(71, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {35,IR(0, 0),IR(6231, 18)/* SampleRateShading */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {36,IR(0, 0),IR(9476, 10)/* ImageRect */,IR(0, 0),IR(72, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {37,IR(0, 0),IR(9486, 12)/* SampledRect */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {38,IR(0, 0),IR(9498, 15)/* GenericPointer */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {39,IR(0, 0),IR(9513, 5)/* Int8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {40,IR(0, 0),IR(9518, 16)/* InputAttachment */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {41,IR(0, 0),IR(9534, 16)/* SparseResidency */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {42,IR(0, 0),IR(9550, 7)/* MinLod */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {43,IR(0, 0),IR(9557, 10)/* Sampled1D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {44,IR(0, 0),IR(9567, 8)/* Image1D */,IR(0, 0),IR(73, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {45,IR(0, 0),IR(9459, 17)/* SampledCubeArray */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {46,IR(0, 0),IR(9575, 14)/* SampledBuffer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {47,IR(0, 0),IR(9589, 12)/* ImageBuffer */,IR(0, 0),IR(74, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {48,IR(0, 0),IR(9601, 13)/* ImageMSArray */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {49,IR(0, 0),IR(9614, 28)/* StorageImageExtendedFormats */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {50,IR(0, 0),IR(9642, 11)/* ImageQuery */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {51,IR(0, 0),IR(9653, 18)/* DerivativeControl */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {52,IR(0, 0),IR(9671, 22)/* InterpolationFunction */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {53,IR(0, 0),IR(9693, 18)/* TransformFeedback */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {54,IR(0, 0),IR(9711, 16)/* GeometryStreams */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {55,IR(0, 0),IR(9727, 30)/* StorageImageReadWithoutFormat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {56,IR(0, 0),IR(9757, 31)/* StorageImageWriteWithoutFormat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {57,IR(0, 0),IR(6101, 14)/* MultiViewport */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {58,IR(0, 0),IR(9788, 17)/* SubgroupDispatch */,IR(0, 0),IR(75, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {59,IR(0, 0),IR(9805, 13)/* NamedBarrier */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {60,IR(0, 0),IR(9818, 12)/* PipeStorage */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {61,IR(0, 0),IR(6482, 16)/* GroupNonUniform */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {62,IR(0, 0),IR(9830, 20)/* GroupNonUniformVote */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {63,IR(0, 0),IR(9850, 26)/* GroupNonUniformArithmetic */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {64,IR(0, 0),IR(6737, 22)/* GroupNonUniformBallot */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {65,IR(0, 0),IR(9876, 23)/* GroupNonUniformShuffle */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {66,IR(0, 0),IR(9899, 31)/* GroupNonUniformShuffleRelative */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {67,IR(0, 0),IR(9930, 25)/* GroupNonUniformClustered */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {68,IR(0, 0),IR(9955, 20)/* GroupNonUniformQuad */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {69,IR(0, 0),IR(6047, 12)/* ShaderLayer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {70,IR(0, 0),IR(6115, 20)/* ShaderViewportIndex */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {71,IR(0, 0),IR(9975, 18)/* UniformDecoration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4165,IR(0, 0),IR(6639, 16)/* CoreBuiltinsARM */,IR(0, 0),IR(1, 0),IR(34, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4166,IR(0, 0),IR(9993, 28)/* TileImageColorReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4167,IR(0, 0),IR(10021, 28)/* TileImageDepthReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4168,IR(0, 0),IR(10049, 30)/* TileImageStencilReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4174,IR(0, 0),IR(10079, 11)/* TensorsARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4175,IR(0, 0),IR(10090, 37)/* StorageTensorArrayDynamicIndexingARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4176,IR(0, 0),IR(10127, 40)/* StorageTensorArrayNonUniformIndexingARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4191,IR(0, 0),IR(10167, 9)/* GraphARM */,IR(0, 0),IR(1, 0),IR(37, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4201,IR(0, 0),IR(10176, 28)/* CooperativeMatrixLayoutsARM */,IR(0, 0),IR(1, 0),IR(38, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4212,IR(0, 0),IR(10204, 10)/* Float8EXT */,IR(0, 0),IR(1, 0),IR(39, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4213,IR(0, 0),IR(10214, 27)/* Float8CooperativeMatrixEXT */,IR(0, 0),IR(78, 2),IR(39, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4422,IR(0, 0),IR(6964, 23)/* FragmentShadingRateKHR */,IR(0, 0),IR(3, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4423,IR(0, 0),IR(6498, 18)/* SubgroupBallotKHR */,IR(0, 0),IR(1, 0),IR(2, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4427,IR(0, 0),IR(6902, 15)/* DrawParameters */,IR(0, 0),IR(3, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4428,IR(0, 0),IR(10262, 33)/* WorkgroupMemoryExplicitLayoutKHR */,IR(0, 0),IR(3, 1),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4429,IR(0, 0),IR(10295, 43)/* WorkgroupMemoryExplicitLayout8BitAccessKHR */,IR(0, 0),IR(80, 1),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4430,IR(0, 0),IR(10338, 44)/* WorkgroupMemoryExplicitLayout16BitAccessKHR */,IR(0, 0),IR(80, 1),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4431,IR(0, 0),IR(10382, 16)/* SubgroupVoteKHR */,IR(0, 0),IR(1, 0),IR(41, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4433,IR(0, 0),IR(10398, 25)/* StorageBuffer16BitAccess */,IR(23, 1),IR(1, 0),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4434,IR(0, 0),IR(10451, 35)/* UniformAndStorageBuffer16BitAccess */,IR(24, 1),IR(81, 1),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4435,IR(0, 0),IR(10503, 22)/* StoragePushConstant16 */,IR(0, 0),IR(1, 0),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4436,IR(0, 0),IR(10525, 21)/* StorageInputOutput16 */,IR(0, 0),IR(1, 0),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4437,IR(0, 0),IR(6999, 12)/* DeviceGroup */,IR(0, 0),IR(1, 0),IR(8, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4439,IR(0, 0),IR(7021, 10)/* MultiView */,IR(0, 0),IR(3, 1),IR(9, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4441,IR(0, 0),IR(10546, 30)/* VariablePointersStorageBuffer */,IR(0, 0),IR(3, 1),IR(43, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4442,IR(0, 0),IR(10576, 17)/* VariablePointers */,IR(0, 0),IR(82, 1),IR(43, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4445,IR(0, 0),IR(10593, 17)/* AtomicStorageOps */,IR(0, 0),IR(83, 1),IR(44, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4447,IR(0, 0),IR(10610, 28)/* SampleMaskPostDepthCoverage */,IR(0, 0),IR(1, 0),IR(45, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4448,IR(0, 0),IR(10638, 24)/* StorageBuffer8BitAccess */,IR(0, 0),IR(1, 0),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4449,IR(0, 0),IR(10662, 34)/* UniformAndStorageBuffer8BitAccess */,IR(0, 0),IR(84, 1),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4450,IR(0, 0),IR(10696, 21)/* StoragePushConstant8 */,IR(0, 0),IR(1, 0),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4464,IR(0, 0),IR(10717, 15)/* DenormPreserve */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4465,IR(0, 0),IR(10732, 18)/* DenormFlushToZero */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4466,IR(0, 0),IR(10750, 25)/* SignedZeroInfNanPreserve */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4467,IR(0, 0),IR(10775, 16)/* RoundingModeRTE */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4468,IR(0, 0),IR(10791, 16)/* RoundingModeRTZ */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4471,IR(0, 0),IR(10807, 23)/* RayQueryProvisionalKHR */,IR(0, 0),IR(3, 1),IR(48, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4472,IR(0, 0),IR(10830, 12)/* RayQueryKHR */,IR(0, 0),IR(3, 1),IR(48, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4473,IR(0, 0),IR(10842, 19)/* UntypedPointersKHR */,IR(0, 0),IR(1, 0),IR(49, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4478,IR(0, 0),IR(10861, 32)/* RayTraversalPrimitiveCullingKHR */,IR(0, 0),IR(85, 2),IR(50, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4479,IR(0, 0),IR(5985, 14)/* RayTracingKHR */,IR(0, 0),IR(3, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4484,IR(0, 0),IR(10893, 26)/* TextureSampleWeightedQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4485,IR(0, 0),IR(10919, 21)/* TextureBoxFilterQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4486,IR(0, 0),IR(10940, 22)/* TextureBlockMatchQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4495,IR(0, 0),IR(7061, 16)/* TileShadingQCOM */,IR(0, 0),IR(3, 1),IR(53, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4496,IR(0, 0),IR(10962, 32)/* CooperativeMatrixConversionQCOM */,IR(0, 0),IR(87, 1),IR(54, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4498,IR(0, 0),IR(10994, 23)/* TextureBlockMatch2QCOM */,IR(0, 0),IR(1, 0),IR(55, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5008,IR(0, 0),IR(11017, 16)/* Float16ImageAMD */,IR(0, 0),IR(3, 1),IR(56, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5009,IR(0, 0),IR(11033, 22)/* ImageGatherBiasLodAMD */,IR(0, 0),IR(3, 1),IR(57, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5010,IR(0, 0),IR(11055, 16)/* FragmentMaskAMD */,IR(0, 0),IR(3, 1),IR(58, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5013,IR(0, 0),IR(7298, 17)/* StencilExportEXT */,IR(0, 0),IR(3, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5015,IR(0, 0),IR(11071, 21)/* ImageReadWriteLodAMD */,IR(0, 0),IR(3, 1),IR(59, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5016,IR(0, 0),IR(11092, 14)/* Int64ImageEXT */,IR(0, 0),IR(3, 1),IR(60, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5055,IR(0, 0),IR(11106, 15)/* ShaderClockKHR */,IR(0, 0),IR(1, 0),IR(61, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5067,IR(0, 0),IR(7344, 18)/* ShaderEnqueueAMDX */,IR(0, 0),IR(3, 1),IR(62, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5087,IR(0, 0),IR(11121, 15)/* QuadControlKHR */,IR(0, 0),IR(1, 0),IR(63, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5112,IR(0, 0),IR(11136, 14)/* Int4TypeINTEL */,IR(0, 0),IR(1, 0),IR(64, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5114,IR(0, 0),IR(11150, 27)/* Int4CooperativeMatrixINTEL */,IR(0, 0),IR(88, 2),IR(64, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5116,IR(0, 0),IR(11177, 16)/* BFloat16TypeKHR */,IR(0, 0),IR(1, 0),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5117,IR(0, 0),IR(11193, 22)/* BFloat16DotProductKHR */,IR(0, 0),IR(90, 1),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5118,IR(0, 0),IR(11215, 29)/* BFloat16CooperativeMatrixKHR */,IR(0, 0),IR(91, 2),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5120,IR(0, 0),IR(11244, 9)/* AbortKHR */,IR(0, 0),IR(1, 0),IR(66, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5128,IR(0, 0),IR(7393, 18)/* DescriptorHeapEXT */,IR(0, 0),IR(93, 1),IR(67, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5146,IR(0, 0),IR(11253, 16)/* ConstantDataKHR */,IR(0, 0),IR(1, 0),IR(68, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5156,IR(0, 0),IR(11269, 16)/* PoisonFreezeKHR */,IR(0, 0),IR(1, 0),IR(69, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5181,IR(0, 0),IR(11285, 15)/* WeakLinkageAMD */,IR(0, 0),IR(94, 1),IR(70, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5249,IR(0, 0),IR(11300, 29)/* SampleMaskOverrideCoverageNV */,IR(0, 0),IR(25, 1),IR(71, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5251,IR(0, 0),IR(11329, 28)/* GeometryShaderPassthroughNV */,IR(0, 0),IR(70, 1),IR(72, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5254,IR(0, 0),IR(6059, 28)/* ShaderViewportIndexLayerEXT */,IR(25, 1),IR(95, 1),IR(73, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5255,IR(0, 0),IR(7442, 21)/* ShaderViewportMaskNV */,IR(0, 0),IR(96, 1),IR(75, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5259,IR(0, 0),IR(7483, 19)/* ShaderStereoViewNV */,IR(0, 0),IR(97, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5260,IR(0, 0),IR(7544, 20)/* PerViewAttributesNV */,IR(0, 0),IR(40, 1),IR(76, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5265,IR(0, 0),IR(7602, 24)/* FragmentFullyCoveredEXT */,IR(0, 0),IR(3, 1),IR(17, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5266,IR(0, 0),IR(5999, 14)/* MeshShadingNV */,IR(0, 0),IR(3, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5282,IR(0, 0),IR(11384, 17)/* ImageFootprintNV */,IR(0, 0),IR(1, 0),IR(77, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5283,IR(0, 0),IR(6013, 15)/* MeshShadingEXT */,IR(0, 0),IR(3, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5284,IR(0, 0),IR(7792, 23)/* FragmentBarycentricKHR */,IR(26, 1),IR(1, 0),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5288,IR(0, 0),IR(11423, 31)/* ComputeDerivativeGroupQuadsKHR */,IR(27, 1),IR(3, 1),IR(78, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5291,IR(0, 0),IR(7881, 19)/* FragmentDensityEXT */,IR(28, 1),IR(3, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5297,IR(0, 0),IR(11498, 30)/* GroupNonUniformPartitionedEXT */,IR(29, 1),IR(1, 0),IR(80, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5301,IR(0, 0),IR(11557, 17)/* ShaderNonUniform */,IR(30, 1),IR(3, 1),IR(82, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5302,IR(0, 0),IR(11594, 23)/* RuntimeDescriptorArray */,IR(31, 1),IR(3, 1),IR(82, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5303,IR(0, 0),IR(11643, 36)/* InputAttachmentArrayDynamicIndexing */,IR(32, 1),IR(98, 1),IR(82, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5304,IR(0, 0),IR(11718, 39)/* UniformTexelBufferArrayDynamicIndexing */,IR(33, 1),IR(74, 1),IR(82, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5305,IR(0, 0),IR(11799, 39)/* StorageTexelBufferArrayDynamicIndexing */,IR(34, 1),IR(99, 1),IR(82, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5306,IR(0, 0),IR(11880, 37)/* UniformBufferArrayNonUniformIndexing */,IR(35, 1),IR(100, 1),IR(82, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5307,IR(0, 0),IR(11957, 36)/* SampledImageArrayNonUniformIndexing */,IR(36, 1),IR(100, 1),IR(82, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5308,IR(0, 0),IR(12032, 37)/* StorageBufferArrayNonUniformIndexing */,IR(37, 1),IR(100, 1),IR(82, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5309,IR(0, 0),IR(12109, 36)/* StorageImageArrayNonUniformIndexing */,IR(38, 1),IR(100, 1),IR(82, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5310,IR(0, 0),IR(12184, 39)/* InputAttachmentArrayNonUniformIndexing */,IR(39, 1),IR(101, 2),IR(82, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5311,IR(0, 0),IR(12265, 42)/* UniformTexelBufferArrayNonUniformIndexing */,IR(40, 1),IR(103, 2),IR(82, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5312,IR(0, 0),IR(12352, 42)/* StorageTexelBufferArrayNonUniformIndexing */,IR(41, 1),IR(105, 2),IR(82, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5336,IR(0, 0),IR(8496, 27)/* RayTracingPositionFetchKHR */,IR(0, 0),IR(3, 1),IR(83, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5340,IR(0, 0),IR(5972, 13)/* RayTracingNV */,IR(0, 0),IR(3, 1),IR(26, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5341,IR(0, 0),IR(8443, 23)/* RayTracingMotionBlurNV */,IR(0, 0),IR(3, 1),IR(27, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5345,IR(0, 0),IR(12439, 18)/* VulkanMemoryModel */,IR(42, 1),IR(1, 0),IR(84, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5346,IR(0, 0),IR(12478, 29)/* VulkanMemoryModelDeviceScope */,IR(43, 1),IR(1, 0),IR(84, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5347,IR(0, 0),IR(5835, 31)/* PhysicalStorageBufferAddresses */,IR(44, 1),IR(3, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5350,IR(0, 0),IR(12573, 32)/* ComputeDerivativeGroupLinearKHR */,IR(45, 1),IR(3, 1),IR(78, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5353,IR(0, 0),IR(12636, 25)/* RayTracingProvisionalKHR */,IR(0, 0),IR(3, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5357,IR(0, 0),IR(12661, 20)/* CooperativeMatrixNV */,IR(0, 0),IR(3, 1),IR(85, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5363,IR(0, 0),IR(12681, 33)/* FragmentShaderSampleInterlockEXT */,IR(0, 0),IR(3, 1),IR(86, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5372,IR(0, 0),IR(12714, 38)/* FragmentShaderShadingRateInterlockEXT */,IR(0, 0),IR(3, 1),IR(86, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5373,IR(0, 0),IR(8811, 19)/* ShaderSMBuiltinsNV */,IR(0, 0),IR(3, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5378,IR(0, 0),IR(12752, 32)/* FragmentShaderPixelInterlockEXT */,IR(0, 0),IR(3, 1),IR(86, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5379,IR(0, 0),IR(12784, 25)/* DemoteToHelperInvocation */,IR(46, 1),IR(3, 1),IR(87, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5380,IR(0, 0),IR(12837, 23)/* DisplacementMicromapNV */,IR(0, 0),IR(3, 1),IR(88, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5381,IR(0, 0),IR(12860, 29)/* RayTracingOpacityMicromapKHR */,IR(47, 1),IR(3, 1),IR(89, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5383,IR(0, 0),IR(12918, 26)/* ShaderInvocationReorderNV */,IR(0, 0),IR(61, 1),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5388,IR(0, 0),IR(12944, 27)/* ShaderInvocationReorderEXT */,IR(0, 0),IR(61, 1),IR(92, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5390,IR(0, 0),IR(12971, 18)/* BindlessTextureNV */,IR(0, 0),IR(1, 0),IR(93, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5391,IR(0, 0),IR(12989, 25)/* RayQueryPositionFetchKHR */,IR(0, 0),IR(3, 1),IR(83, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5394,IR(0, 0),IR(13014, 20)/* CooperativeVectorNV */,IR(0, 0),IR(1, 0),IR(94, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5404,IR(0, 0),IR(13034, 22)/* AtomicFloat16VectorNV */,IR(0, 0),IR(1, 0),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5409,IR(0, 0),IR(8557, 33)/* RayTracingDisplacementMicromapNV */,IR(0, 0),IR(61, 1),IR(88, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5414,IR(0, 0),IR(13056, 18)/* RawAccessChainsNV */,IR(0, 0),IR(1, 0),IR(96, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5418,IR(0, 0),IR(8700, 28)/* RayTracingSpheresGeometryNV */,IR(0, 0),IR(1, 0),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5419,IR(0, 0),IR(8739, 39)/* RayTracingLinearSweptSpheresGeometryNV */,IR(0, 0),IR(1, 0),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5423,IR(0, 0),IR(13074, 20)/* PushConstantBanksNV */,IR(0, 0),IR(3, 1),IR(97, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5425,IR(0, 0),IR(13094, 14)/* LongVectorEXT */,IR(0, 0),IR(1, 0),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5426,IR(0, 0),IR(13108, 23)/* Shader64BitIndexingEXT */,IR(0, 0),IR(1, 0),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5430,IR(0, 0),IR(13131, 30)/* CooperativeMatrixReductionsNV */,IR(0, 0),IR(1, 0),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5431,IR(0, 0),IR(13161, 31)/* CooperativeMatrixConversionsNV */,IR(0, 0),IR(1, 0),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5432,IR(0, 0),IR(13192, 40)/* CooperativeMatrixPerElementOperationsNV */,IR(0, 0),IR(1, 0),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5433,IR(0, 0),IR(13232, 36)/* CooperativeMatrixTensorAddressingNV */,IR(0, 0),IR(1, 0),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5434,IR(0, 0),IR(13268, 30)/* CooperativeMatrixBlockLoadsNV */,IR(0, 0),IR(1, 0),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5435,IR(0, 0),IR(13298, 28)/* CooperativeVectorTrainingNV */,IR(0, 0),IR(1, 0),IR(94, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5437,IR(0, 0),IR(8985, 41)/* RayTracingClusterAccelerationStructureNV */,IR(0, 0),IR(61, 1),IR(31, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5439,IR(0, 0),IR(13326, 19)/* TensorAddressingNV */,IR(0, 0),IR(1, 0),IR(101, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5447,IR(0, 0),IR(13345, 32)/* CooperativeMatrixDecodeVectorNV */,IR(0, 0),IR(107, 1),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5568,IR(0, 0),IR(13377, 21)/* SubgroupShuffleINTEL */,IR(0, 0),IR(1, 0),IR(103, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5569,IR(0, 0),IR(13398, 27)/* SubgroupBufferBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(103, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5570,IR(0, 0),IR(13425, 26)/* SubgroupImageBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(103, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5579,IR(0, 0),IR(13451, 31)/* SubgroupImageMediaBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(104, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5582,IR(0, 0),IR(13482, 21)/* RoundToInfinityINTEL */,IR(0, 0),IR(1, 0),IR(105, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5583,IR(0, 0),IR(13503, 23)/* FloatingPointModeINTEL */,IR(0, 0),IR(1, 0),IR(105, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5584,IR(0, 0),IR(13526, 23)/* IntegerFunctions2INTEL */,IR(0, 0),IR(1, 0),IR(106, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5603,IR(0, 0),IR(13549, 22)/* FunctionPointersINTEL */,IR(0, 0),IR(1, 0),IR(107, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5604,IR(0, 0),IR(13571, 24)/* IndirectReferencesINTEL */,IR(0, 0),IR(1, 0),IR(107, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5606,IR(0, 0),IR(13595, 9)/* AsmINTEL */,IR(0, 0),IR(1, 0),IR(108, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5612,IR(0, 0),IR(13604, 23)/* AtomicFloat32MinMaxEXT */,IR(0, 0),IR(1, 0),IR(109, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5613,IR(0, 0),IR(13627, 23)/* AtomicFloat64MinMaxEXT */,IR(0, 0),IR(1, 0),IR(109, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5616,IR(0, 0),IR(13650, 23)/* AtomicFloat16MinMaxEXT */,IR(0, 0),IR(1, 0),IR(109, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5617,IR(0, 0),IR(13673, 19)/* VectorComputeINTEL */,IR(0, 0),IR(108, 1),IR(110, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5619,IR(0, 0),IR(13692, 15)/* VectorAnyINTEL */,IR(0, 0),IR(1, 0),IR(110, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5629,IR(0, 0),IR(13707, 16)/* ExpectAssumeKHR */,IR(0, 0),IR(1, 0),IR(111, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5696,IR(0, 0),IR(13723, 33)/* SubgroupAvcMotionEstimationINTEL */,IR(0, 0),IR(1, 0),IR(112, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5697,IR(0, 0),IR(13756, 38)/* SubgroupAvcMotionEstimationIntraINTEL */,IR(0, 0),IR(1, 0),IR(112, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5698,IR(0, 0),IR(13794, 39)/* SubgroupAvcMotionEstimationChromaINTEL */,IR(0, 0),IR(1, 0),IR(112, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5817,IR(0, 0),IR(13833, 25)/* VariableLengthArrayINTEL */,IR(0, 0),IR(1, 0),IR(113, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5821,IR(0, 0),IR(13858, 26)/* FunctionFloatControlINTEL */,IR(0, 0),IR(1, 0),IR(105, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5824,IR(0, 0),IR(13884, 27)/* FPGAMemoryAttributesALTERA */,IR(48, 1),IR(1, 0),IR(114, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5837,IR(0, 0),IR(13937, 20)/* FPFastMathModeINTEL */,IR(0, 0),IR(0, 1),IR(116, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5844,IR(0, 0),IR(13957, 33)/* ArbitraryPrecisionIntegersALTERA */,IR(49, 1),IR(1, 0),IR(117, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5845,IR(0, 0),IR(14022, 38)/* ArbitraryPrecisionFloatingPointALTERA */,IR(50, 1),IR(1, 0),IR(119, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5886,IR(0, 0),IR(14097, 30)/* UnstructuredLoopControlsINTEL */,IR(0, 0),IR(1, 0),IR(121, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5888,IR(0, 0),IR(14127, 23)/* FPGALoopControlsALTERA */,IR(51, 1),IR(1, 0),IR(122, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5892,IR(0, 0),IR(14172, 22)/* KernelAttributesINTEL */,IR(0, 0),IR(1, 0),IR(124, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5897,IR(0, 0),IR(14194, 26)/* FPGAKernelAttributesINTEL */,IR(0, 0),IR(1, 0),IR(124, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5898,IR(0, 0),IR(14220, 25)/* FPGAMemoryAccessesALTERA */,IR(52, 1),IR(1, 0),IR(125, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5904,IR(0, 0),IR(14269, 28)/* FPGAClusterAttributesALTERA */,IR(53, 1),IR(1, 0),IR(127, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5906,IR(0, 0),IR(14324, 15)/* LoopFuseALTERA */,IR(54, 1),IR(1, 0),IR(129, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5908,IR(0, 0),IR(14353, 21)/* FPGADSPControlALTERA */,IR(55, 1),IR(1, 0),IR(131, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5910,IR(0, 0),IR(14394, 26)/* MemoryAccessAliasingINTEL */,IR(0, 0),IR(1, 0),IR(133, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5916,IR(0, 0),IR(14420, 41)/* FPGAInvocationPipeliningAttributesALTERA */,IR(56, 1),IR(1, 0),IR(134, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5920,IR(0, 0),IR(14501, 25)/* FPGABufferLocationALTERA */,IR(57, 1),IR(1, 0),IR(136, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5922,IR(0, 0),IR(14550, 35)/* ArbitraryPrecisionFixedPointALTERA */,IR(58, 1),IR(1, 0),IR(138, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5935,IR(0, 0),IR(14619, 24)/* USMStorageClassesALTERA */,IR(59, 1),IR(1, 0),IR(140, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5939,IR(0, 0),IR(14666, 30)/* RuntimeAlignedAttributeALTERA */,IR(60, 1),IR(1, 0),IR(142, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5943,IR(0, 0),IR(14725, 14)/* IOPipesALTERA */,IR(61, 1),IR(1, 0),IR(144, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5945,IR(0, 0),IR(14752, 20)/* BlockingPipesALTERA */,IR(62, 1),IR(1, 0),IR(146, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5948,IR(0, 0),IR(14791, 14)/* FPGARegALTERA */,IR(63, 1),IR(1, 0),IR(148, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6016,IR(0, 0),IR(14818, 19)/* DotProductInputAll */,IR(64, 1),IR(1, 0),IR(150, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6017,IR(0, 0),IR(14859, 22)/* DotProductInput4x8Bit */,IR(65, 1),IR(109, 1),IR(150, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6018,IR(0, 0),IR(14906, 28)/* DotProductInput4x8BitPacked */,IR(66, 1),IR(1, 0),IR(150, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6019,IR(0, 0),IR(14965, 11)/* DotProduct */,IR(67, 1),IR(1, 0),IR(150, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6020,IR(0, 0),IR(9038, 15)/* RayCullMaskKHR */,IR(0, 0),IR(1, 0),IR(32, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6022,IR(0, 0),IR(10241, 21)/* CooperativeMatrixKHR */,IR(0, 0),IR(1, 0),IR(151, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6024,IR(0, 0),IR(14990, 24)/* ReplicatedCompositesEXT */,IR(0, 0),IR(1, 0),IR(152, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6025,IR(0, 0),IR(15014, 16)/* BitInstructions */,IR(0, 0),IR(1, 0),IR(153, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6026,IR(0, 0),IR(15030, 25)/* GroupNonUniformRotateKHR */,IR(0, 0),IR(77, 1),IR(154, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6029,IR(0, 0),IR(15055, 15)/* FloatControls2 */,IR(0, 0),IR(1, 0),IR(155, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6030,IR(0, 0),IR(15070, 7)/* FMAKHR */,IR(0, 0),IR(1, 0),IR(156, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6032,IR(0, 0),IR(15077, 42)/* RayTracingOpacityMicromapExecutionModeKHR */,IR(0, 0),IR(3, 1),IR(157, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6033,IR(0, 0),IR(15119, 20)/* AtomicFloat32AddEXT */,IR(0, 0),IR(1, 0),IR(158, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6034,IR(0, 0),IR(15139, 20)/* AtomicFloat64AddEXT */,IR(0, 0),IR(1, 0),IR(158, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6089,IR(0, 0),IR(15159, 20)/* LongCompositesINTEL */,IR(0, 0),IR(1, 0),IR(159, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6094,IR(0, 0),IR(15179, 11)/* OptNoneEXT */,IR(68, 1),IR(1, 0),IR(160, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6095,IR(0, 0),IR(15203, 20)/* AtomicFloat16AddEXT */,IR(0, 0),IR(1, 0),IR(162, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6114,IR(0, 0),IR(15223, 21)/* DebugInfoModuleINTEL */,IR(0, 0),IR(1, 0),IR(163, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6115,IR(0, 0),IR(15244, 24)/* BFloat16ConversionINTEL */,IR(0, 0),IR(1, 0),IR(164, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6141,IR(0, 0),IR(15268, 16)/* SplitBarrierEXT */,IR(69, 1),IR(1, 0),IR(165, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6144,IR(0, 0),IR(15302, 19)/* ArithmeticFenceEXT */,IR(0, 0),IR(1, 0),IR(167, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6150,IR(0, 0),IR(15321, 30)/* FPGAClusterAttributesV2ALTERA */,IR(70, 1),IR(110, 1),IR(127, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6161,IR(0, 0),IR(15380, 28)/* FPGAKernelAttributesv2INTEL */,IR(0, 0),IR(111, 1),IR(124, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6162,IR(0, 0),IR(15408, 19)/* TaskSequenceALTERA */,IR(71, 1),IR(1, 0),IR(168, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6169,IR(0, 0),IR(15445, 16)/* FPMaxErrorINTEL */,IR(0, 0),IR(1, 0),IR(170, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6171,IR(0, 0),IR(15461, 25)/* FPGALatencyControlALTERA */,IR(72, 1),IR(1, 0),IR(171, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6174,IR(0, 0),IR(15510, 29)/* FPGAArgumentInterfacesALTERA */,IR(73, 1),IR(1, 0),IR(173, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6187,IR(0, 0),IR(15567, 30)/* GlobalVariableHostAccessINTEL */,IR(0, 0),IR(1, 0),IR(175, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6189,IR(0, 0),IR(15597, 36)/* GlobalVariableFPGADecorationsALTERA */,IR(74, 1),IR(1, 0),IR(176, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6220,IR(0, 0),IR(15668, 28)/* SubgroupBufferPrefetchINTEL */,IR(0, 0),IR(1, 0),IR(178, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6228,IR(0, 0),IR(15696, 23)/* Subgroup2DBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(179, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6229,IR(0, 0),IR(15719, 30)/* Subgroup2DBlockTransformINTEL */,IR(0, 0),IR(112, 1),IR(179, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6230,IR(0, 0),IR(15749, 30)/* Subgroup2DBlockTransposeINTEL */,IR(0, 0),IR(112, 1),IR(179, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6236,IR(0, 0),IR(15779, 38)/* SubgroupMatrixMultiplyAccumulateINTEL */,IR(0, 0),IR(1, 0),IR(180, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6241,IR(0, 0),IR(15817, 28)/* TernaryBitwiseFunctionINTEL */,IR(0, 0),IR(1, 0),IR(181, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6243,IR(0, 0),IR(15845, 32)/* UntypedVariableLengthArrayINTEL */,IR(0, 0),IR(113, 2),IR(113, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6245,IR(0, 0),IR(15877, 21)/* SpecConditionalINTEL */,IR(0, 0),IR(1, 0),IR(182, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6246,IR(0, 0),IR(15898, 22)/* FunctionVariantsINTEL */,IR(0, 0),IR(115, 1),IR(182, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6257,IR(0, 0),IR(15920, 18)/* PredicatedIOINTEL */,IR(0, 0),IR(1, 0),IR(183, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6265,IR(0, 0),IR(15938, 23)/* RoundedDivideSqrtINTEL */,IR(0, 0),IR(1, 0),IR(184, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6400,IR(0, 0),IR(15961, 26)/* GroupUniformArithmeticKHR */,IR(0, 0),IR(1, 0),IR(185, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6425,IR(0, 0),IR(15987, 27)/* TensorFloat32RoundingINTEL */,IR(0, 0),IR(1, 0),IR(186, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6427,IR(0, 0),IR(16014, 25)/* MaskedGatherScatterINTEL */,IR(0, 0),IR(1, 0),IR(187, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6441,IR(0, 0),IR(16039, 19)/* CacheControlsINTEL */,IR(0, 0),IR(1, 0),IR(188, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6460,IR(0, 0),IR(16058, 20)/* RegisterLimitsINTEL */,IR(0, 0),IR(1, 0),IR(189, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6528,IR(0, 0),IR(16078, 20)/* BindlessImagesINTEL */,IR(0, 0),IR(1, 0),IR(190, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6912,IR(0, 0),IR(16098, 33)/* DotProductFloat16AccFloat32VALVE */,IR(0, 0),IR(116, 1),IR(191, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6913,IR(0, 0),IR(16131, 33)/* DotProductFloat16AccFloat16VALVE */,IR(0, 0),IR(116, 1),IR(191, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6914,IR(0, 0),IR(16164, 27)/* DotProductBFloat16AccVALVE */,IR(0, 0),IR(90, 1),IR(191, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6915,IR(0, 0),IR(16191, 32)/* DotProductFloat8AccFloat32VALVE */,IR(0, 0),IR(117, 1),IR(191, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {0,IR(0, 0),IR(16223, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(16235, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(16243, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {3,IR(0, 0),IR(16251, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(16257, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(16264, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(16275, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(16284, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(16297, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(16303, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(16313, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(16319, 15)/* ImportedModule */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {1,IR(0, 0),IR(16334, 20)/* ImportedDeclaration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {0,IR(0, 0),IR(16354, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(16359, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(16375, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(16389, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(16402, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(16414, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(16431, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(16443, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(16458, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(16471, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(16486, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(16504, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(16521, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(16542, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(16562, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(16582, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {16384,IR(0, 0),IR(16598, 16)/* FlagIsEnumClass */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {32768,IR(0, 0),IR(16614, 20)/* FlagTypePassByValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {65536,IR(0, 0),IR(16634, 24)/* FlagTypePassByReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(16658, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {1,IR(0, 0),IR(16664, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {2,IR(0, 0),IR(16669, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {3,IR(0, 1),IR(16708, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {4,IR(1, 2),IR(16719, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {5,IR(0, 0),IR(16728, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {6,IR(0, 0),IR(16733, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {7,IR(0, 0),IR(16740, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {8,IR(0, 1),IR(16751, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {9,IR(1, 2),IR(16758, 9)/* Fragment */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {0,IR(0, 0),IR(16767, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(16777, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(16790, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {3,IR(0, 0),IR(16803, 11)/* AtomicType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(16814, 10)/* Float16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1,IR(0, 0),IR(16824, 10)/* Float32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {2,IR(0, 0),IR(16834, 10)/* Float64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {3,IR(0, 0),IR(16844, 13)/* SignedInt8NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {4,IR(0, 0),IR(16857, 14)/* SignedInt16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {5,IR(0, 0),IR(16871, 14)/* SignedInt32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {6,IR(0, 0),IR(16885, 14)/* SignedInt64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {7,IR(0, 0),IR(16899, 15)/* UnsignedInt8NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {8,IR(0, 0),IR(16914, 16)/* UnsignedInt16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {9,IR(0, 0),IR(16930, 16)/* UnsignedInt32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {10,IR(0, 0),IR(16946, 16)/* UnsignedInt64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491000,IR(0, 0),IR(16962, 19)/* SignedInt8PackedNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491001,IR(0, 0),IR(16981, 21)/* UnsignedInt8PackedNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491002,IR(0, 0),IR(17002, 12)/* FloatE4M3NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491003,IR(0, 0),IR(17014, 12)/* FloatE5M2NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {0,IR(0, 0),IR(17026, 12)/* RowMajorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {1,IR(0, 0),IR(17038, 15)/* ColumnMajorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {4202,IR(0, 0),IR(17053, 25)/* RowBlockedInterleavedARM */,IR(0, 0),IR(118, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {4203,IR(0, 0),IR(17078, 28)/* ColumnBlockedInterleavedARM */,IR(0, 0),IR(118, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {0,IR(0, 0),IR(17106, 8)/* NoneKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {1,IR(0, 0),IR(17114, 27)/* MatrixASignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {2,IR(0, 0),IR(17141, 27)/* MatrixBSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {4,IR(0, 0),IR(17168, 27)/* MatrixCSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {8,IR(0, 0),IR(17195, 32)/* MatrixResultSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {16,IR(0, 0),IR(17227, 26)/* SaturatingAccumulationKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {1,IR(0, 0),IR(17253, 4)/* Row */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {2,IR(0, 0),IR(17257, 7)/* Column */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {4,IR(0, 0),IR(17264, 4)/* 2x2 */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {0,IR(0, 0),IR(17268, 11)/* MatrixAKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {1,IR(0, 0),IR(17279, 11)/* MatrixBKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {2,IR(0, 0),IR(17290, 21)/* MatrixAccumulatorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {0,IR(0, 0),IR(17311, 11)/* RowMajorNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {1,IR(0, 0),IR(17322, 14)/* ColumnMajorNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {2,IR(0, 0),IR(17336, 21)/* InferencingOptimalNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {3,IR(0, 0),IR(17357, 18)/* TrainingOptimalNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {0,IR(0, 0),IR(16223, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(16235, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(16243, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(16251, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(16257, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(16264, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(16275, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {8,IR(0, 0),IR(16284, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(16297, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(16303, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(16313, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(16354, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(16359, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(16375, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(16389, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(16402, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(16414, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(16431, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(16443, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(16458, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(16471, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(16486, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(16504, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(16521, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(16542, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(16562, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(16582, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(16658, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {1,IR(0, 0),IR(16664, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {2,IR(0, 0),IR(16669, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {3,IR(0, 1),IR(16708, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {4,IR(1, 2),IR(16719, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {5,IR(0, 0),IR(16728, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {6,IR(0, 0),IR(16733, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {7,IR(0, 0),IR(16740, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {8,IR(0, 1),IR(16751, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {0,IR(0, 0),IR(16767, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(16777, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(16790, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(17375, 17)/* RelaxedPrecision */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {1,IR(0, 1),IR(17392, 7)/* SpecId */,IR(0, 0),IR(119, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {2,IR(0, 0),IR(17399, 6)/* Block */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {3,IR(0, 0),IR(17405, 12)/* BufferBlock */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),SPV_SPIRV_VERSION_WORD(1,3)}, // SPV_OPERAND_TYPE_DECORATION
  {4,IR(0, 0),IR(17417, 9)/* RowMajor */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5,IR(0, 0),IR(17426, 9)/* ColMajor */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6,IR(0, 1),IR(17435, 12)/* ArrayStride */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {7,IR(0, 1),IR(17447, 13)/* MatrixStride */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {8,IR(0, 0),IR(17460, 11)/* GLSLShared */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {9,IR(0, 0),IR(17471, 11)/* GLSLPacked */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {10,IR(0, 0),IR(17482, 8)/* CPacked */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {11,IR(3, 1),IR(17516, 8)/* BuiltIn */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {13,IR(0, 0),IR(17524, 14)/* NoPerspective */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {14,IR(0, 0),IR(17538, 5)/* Flat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {15,IR(0, 0),IR(17543, 6)/* Patch */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {16,IR(0, 0),IR(17549, 9)/* Centroid */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {17,IR(0, 0),IR(17558, 7)/* Sample */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {18,IR(0, 0),IR(17565, 10)/* Invariant */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {19,IR(0, 0),IR(17575, 9)/* Restrict */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {20,IR(0, 0),IR(17584, 8)/* Aliased */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {21,IR(0, 0),IR(17592, 9)/* Volatile */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {22,IR(0, 0),IR(17601, 9)/* Constant */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {23,IR(0, 0),IR(17610, 9)/* Coherent */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {24,IR(0, 0),IR(17619, 12)/* NonWritable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {25,IR(0, 0),IR(17631, 12)/* NonReadable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {26,IR(0, 0),IR(17643, 8)/* Uniform */,IR(0, 0),IR(121, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {27,IR(4, 1),IR(17677, 10)/* UniformId */,IR(0, 0),IR(121, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {28,IR(0, 0),IR(17687, 20)/* SaturatedConversion */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {29,IR(0, 1),IR(17707, 7)/* Stream */,IR(0, 0),IR(123, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {30,IR(0, 1),IR(17714, 9)/* Location */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {31,IR(0, 1),IR(17723, 10)/* Component */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {32,IR(0, 1),IR(17733, 6)/* Index */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {33,IR(0, 1),IR(17739, 8)/* Binding */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {34,IR(0, 1),IR(17747, 14)/* DescriptorSet */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {35,IR(0, 1),IR(17761, 7)/* Offset */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {36,IR(0, 1),IR(17768, 10)/* XfbBuffer */,IR(0, 0),IR(124, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {37,IR(0, 1),IR(17778, 10)/* XfbStride */,IR(0, 0),IR(124, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {38,IR(5, 1),IR(17834, 14)/* FuncParamAttr */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {39,IR(6, 1),IR(17882, 15)/* FPRoundingMode */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {40,IR(7, 1),IR(17932, 15)/* FPFastMathMode */,IR(0, 0),IR(125, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {41,IR(8, 2),IR(18009, 18)/* LinkageAttributes */,IR(0, 0),IR(94, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {42,IR(0, 0),IR(18027, 14)/* NoContraction */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {43,IR(0, 1),IR(18041, 21)/* InputAttachmentIndex */,IR(0, 0),IR(98, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {44,IR(0, 1),IR(18062, 10)/* Alignment */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {45,IR(0, 1),IR(18072, 14)/* MaxByteOffset */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {46,IR(10, 1),IR(18106, 12)/* AlignmentId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {47,IR(10, 1),IR(18118, 16)/* MaxByteOffsetId */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4216,IR(0, 0),IR(18134, 44)/* SaturatedToLargestFloat8NormalConversionEXT */,IR(0, 0),IR(117, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4469,IR(0, 0),IR(18178, 13)/* NoSignedWrap */,IR(0, 0),IR(1, 0),IR(192, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4470,IR(0, 0),IR(18191, 15)/* NoUnsignedWrap */,IR(0, 0),IR(1, 0),IR(192, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4487,IR(0, 0),IR(18206, 18)/* WeightTextureQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4488,IR(0, 0),IR(18224, 22)/* BlockMatchTextureQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4499,IR(0, 0),IR(18246, 22)/* BlockMatchSamplerQCOM */,IR(0, 0),IR(1, 0),IR(55, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4999,IR(0, 0),IR(18268, 18)/* ExplicitInterpAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5019,IR(10, 1),IR(18286, 32)/* NodeSharesPayloadLimitsWithAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5020,IR(10, 1),IR(18318, 20)/* NodeMaxPayloadsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5078,IR(0, 0),IR(18338, 23)/* TrackFinishWritingAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5091,IR(10, 1),IR(18361, 20)/* PayloadNodeNameAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5098,IR(10, 1),IR(18381, 25)/* PayloadNodeBaseIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5099,IR(0, 0),IR(18406, 27)/* PayloadNodeSparseArrayAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5100,IR(10, 1),IR(18433, 25)/* PayloadNodeArraySizeAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5105,IR(0, 0),IR(18458, 28)/* PayloadDispatchIndirectAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5124,IR(10, 1),IR(18486, 17)/* ArrayStrideIdEXT */,IR(0, 0),IR(44, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5125,IR(10, 1),IR(18503, 12)/* OffsetIdEXT */,IR(0, 0),IR(44, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5145,IR(0, 0),IR(18515, 14)/* UTFEncodedKHR */,IR(0, 0),IR(127, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5248,IR(0, 0),IR(18529, 19)/* OverrideCoverageNV */,IR(0, 0),IR(128, 1),IR(71, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5250,IR(0, 0),IR(18548, 14)/* PassthroughNV */,IR(0, 0),IR(129, 1),IR(72, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5252,IR(0, 0),IR(18562, 19)/* ViewportRelativeNV */,IR(0, 0),IR(97, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5256,IR(0, 1),IR(18581, 28)/* SecondaryViewportRelativeNV */,IR(0, 0),IR(47, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5271,IR(0, 0),IR(18609, 16)/* PerPrimitiveEXT */,IR(75, 1),IR(130, 2),IR(193, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5272,IR(0, 0),IR(18640, 10)/* PerViewNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5273,IR(0, 0),IR(18650, 10)/* PerTaskNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5285,IR(0, 0),IR(18660, 13)/* PerVertexKHR */,IR(76, 1),IR(52, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5300,IR(0, 0),IR(18685, 11)/* NonUniform */,IR(77, 1),IR(100, 1),IR(82, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5355,IR(0, 0),IR(18710, 16)/* RestrictPointer */,IR(78, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5356,IR(0, 0),IR(18745, 15)/* AliasedPointer */,IR(79, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5358,IR(0, 1),IR(18778, 15)/* MemberOffsetNV */,IR(0, 0),IR(132, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5386,IR(0, 0),IR(18793, 30)/* HitObjectShaderRecordBufferNV */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5389,IR(0, 0),IR(18823, 31)/* HitObjectShaderRecordBufferEXT */,IR(0, 0),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5397,IR(0, 1),IR(18854, 7)/* BankNV */,IR(0, 0),IR(132, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5398,IR(0, 0),IR(18861, 18)/* BindlessSamplerNV */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5399,IR(0, 0),IR(18879, 16)/* BindlessImageNV */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5400,IR(0, 0),IR(18895, 15)/* BoundSamplerNV */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5401,IR(0, 0),IR(18910, 13)/* BoundImageNV */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5599,IR(0, 1),IR(18923, 14)/* SIMTCallINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5602,IR(0, 0),IR(18937, 26)/* ReferencedIndirectlyINTEL */,IR(0, 0),IR(137, 1),IR(107, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5607,IR(11, 1),IR(18963, 13)/* ClobberINTEL */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5608,IR(0, 0),IR(18976, 17)/* SideEffectsINTEL */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5624,IR(0, 0),IR(18993, 27)/* VectorComputeVariableINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5625,IR(0, 1),IR(19020, 21)/* FuncParamIOKindINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5626,IR(0, 0),IR(19041, 27)/* VectorComputeFunctionINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5627,IR(0, 0),IR(19068, 15)/* StackCallINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5628,IR(0, 1),IR(19083, 26)/* GlobalVariableOffsetINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5634,IR(10, 1),IR(19109, 14)/* CounterBuffer */,IR(80, 1),IR(1, 0),IR(195, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5635,IR(11, 1),IR(19147, 13)/* UserSemantic */,IR(81, 1),IR(1, 0),IR(195, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5636,IR(11, 1),IR(19179, 15)/* UserTypeGOOGLE */,IR(0, 0),IR(1, 0),IR(196, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5822,IR(12, 2),IR(19194, 26)/* FunctionRoundingModeINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5823,IR(14, 2),IR(19251, 24)/* FunctionDenormModeINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5825,IR(0, 0),IR(19275, 15)/* RegisterALTERA */,IR(82, 1),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5826,IR(11, 1),IR(19304, 13)/* MemoryALTERA */,IR(83, 1),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5827,IR(0, 1),IR(19329, 15)/* NumbanksALTERA */,IR(84, 1),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5828,IR(0, 1),IR(19358, 16)/* BankwidthALTERA */,IR(85, 1),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5829,IR(0, 1),IR(19389, 23)/* MaxPrivateCopiesALTERA */,IR(86, 1),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5830,IR(0, 0),IR(19434, 17)/* SinglepumpALTERA */,IR(87, 1),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5831,IR(0, 0),IR(19467, 17)/* DoublepumpALTERA */,IR(88, 1),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5832,IR(0, 1),IR(19500, 20)/* MaxReplicatesALTERA */,IR(89, 1),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5833,IR(0, 0),IR(19539, 21)/* SimpleDualPortALTERA */,IR(90, 1),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5834,IR(16, 2),IR(19580, 12)/* MergeALTERA */,IR(91, 1),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5835,IR(18, 1),IR(19645, 15)/* BankBitsALTERA */,IR(92, 1),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5836,IR(0, 1),IR(19674, 21)/* ForcePow2DepthALTERA */,IR(93, 1),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5883,IR(0, 1),IR(19715, 17)/* StridesizeALTERA */,IR(94, 1),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5884,IR(0, 1),IR(19748, 15)/* WordsizeALTERA */,IR(95, 1),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5885,IR(0, 0),IR(19777, 19)/* TrueDualPortALTERA */,IR(96, 1),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5899,IR(0, 0),IR(19814, 20)/* BurstCoalesceALTERA */,IR(97, 1),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5900,IR(0, 1),IR(19853, 16)/* CacheSizeALTERA */,IR(98, 1),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5901,IR(0, 0),IR(19884, 29)/* DontStaticallyCoalesceALTERA */,IR(99, 1),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5902,IR(0, 1),IR(19941, 15)/* PrefetchALTERA */,IR(100, 1),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5905,IR(0, 0),IR(19970, 18)/* StallEnableALTERA */,IR(101, 1),IR(110, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5907,IR(0, 0),IR(20005, 26)/* FuseLoopsInFunctionALTERA */,IR(102, 1),IR(142, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5909,IR(1, 2),IR(20056, 20)/* MathOpDSPModeALTERA */,IR(103, 1),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5914,IR(10, 1),IR(20095, 16)/* AliasScopeINTEL */,IR(0, 0),IR(144, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5915,IR(10, 1),IR(20111, 13)/* NoAliasINTEL */,IR(0, 0),IR(144, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5917,IR(0, 1),IR(20124, 25)/* InitiationIntervalALTERA */,IR(104, 1),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5918,IR(0, 1),IR(20173, 21)/* MaxConcurrencyALTERA */,IR(105, 1),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5919,IR(0, 1),IR(20214, 21)/* PipelineEnableALTERA */,IR(106, 1),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5921,IR(0, 1),IR(20255, 21)/* BufferLocationALTERA */,IR(107, 1),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5944,IR(0, 1),IR(20296, 20)/* IOPipeStorageALTERA */,IR(108, 1),IR(147, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6080,IR(19, 2),IR(20369, 31)/* FunctionFloatingPointModeINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6085,IR(0, 0),IR(20400, 25)/* SingleElementVectorINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6087,IR(0, 0),IR(20425, 35)/* VectorComputeCallableFunctionINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6140,IR(0, 0),IR(20460, 18)/* MediaBlockIOINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6151,IR(0, 0),IR(20478, 16)/* StallFreeALTERA */,IR(109, 1),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6170,IR(21, 1),IR(20540, 26)/* FPMaxErrorDecorationINTEL */,IR(0, 0),IR(149, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6172,IR(0, 1),IR(20566, 26)/* LatencyControlLabelALTERA */,IR(110, 1),IR(150, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6173,IR(22, 3),IR(20617, 31)/* LatencyControlConstraintALTERA */,IR(111, 1),IR(150, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6175,IR(0, 0),IR(20678, 28)/* ConduitKernelArgumentALTERA */,IR(112, 1),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6176,IR(0, 0),IR(20733, 32)/* RegisterMapKernelArgumentALTERA */,IR(113, 1),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6177,IR(0, 1),IR(20796, 34)/* MMHostInterfaceAddressWidthALTERA */,IR(114, 1),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6178,IR(0, 1),IR(20863, 31)/* MMHostInterfaceDataWidthALTERA */,IR(115, 1),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6179,IR(0, 1),IR(20924, 29)/* MMHostInterfaceLatencyALTERA */,IR(116, 1),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6180,IR(25, 1),IR(21015, 35)/* MMHostInterfaceReadWriteModeALTERA */,IR(117, 1),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6181,IR(0, 1),IR(21084, 30)/* MMHostInterfaceMaxBurstALTERA */,IR(118, 1),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6182,IR(0, 1),IR(21143, 33)/* MMHostInterfaceWaitRequestALTERA */,IR(119, 1),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6183,IR(0, 0),IR(21208, 27)/* StableKernelArgumentALTERA */,IR(120, 1),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6188,IR(26, 2),IR(21300, 16)/* HostAccessINTEL */,IR(0, 0),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6190,IR(28, 1),IR(21363, 15)/* InitModeALTERA */,IR(121, 1),IR(153, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6191,IR(0, 1),IR(21392, 29)/* ImplementInRegisterMapALTERA */,IR(122, 1),IR(153, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6247,IR(10, 1),IR(21449, 17)/* ConditionalINTEL */,IR(0, 0),IR(115, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6442,IR(29, 2),IR(21502, 22)/* CacheControlLoadINTEL */,IR(0, 0),IR(154, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6443,IR(31, 2),IR(21561, 23)/* CacheControlStoreINTEL */,IR(0, 0),IR(154, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {0,IR(0, 0),IR(21584, 3)/* 1D */,IR(0, 0),IR(73, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {1,IR(0, 0),IR(21587, 3)/* 2D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {2,IR(0, 0),IR(21590, 3)/* 3D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {3,IR(0, 0),IR(21593, 5)/* Cube */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {4,IR(0, 0),IR(21598, 5)/* Rect */,IR(0, 0),IR(72, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {5,IR(0, 0),IR(21603, 7)/* Buffer */,IR(0, 0),IR(74, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {6,IR(0, 0),IR(21610, 12)/* SubpassData */,IR(0, 0),IR(98, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {4173,IR(0, 0),IR(21622, 17)/* TileImageDataEXT */,IR(0, 0),IR(155, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {0,IR(0, 1),IR(21639, 12)/* Invocations */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {1,IR(0, 0),IR(21651, 13)/* SpacingEqual */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {2,IR(0, 0),IR(21664, 22)/* SpacingFractionalEven */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {3,IR(0, 0),IR(21686, 21)/* SpacingFractionalOdd */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4,IR(0, 0),IR(21707, 14)/* VertexOrderCw */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5,IR(0, 0),IR(21721, 15)/* VertexOrderCcw */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6,IR(0, 0),IR(21736, 19)/* PixelCenterInteger */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {7,IR(0, 0),IR(21755, 16)/* OriginUpperLeft */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {8,IR(0, 0),IR(21771, 16)/* OriginLowerLeft */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {9,IR(0, 0),IR(21787, 19)/* EarlyFragmentTests */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {10,IR(0, 0),IR(21806, 10)/* PointMode */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {11,IR(0, 0),IR(21816, 4)/* Xfb */,IR(0, 0),IR(124, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {12,IR(0, 0),IR(21820, 15)/* DepthReplacing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {14,IR(0, 0),IR(21835, 13)/* DepthGreater */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {15,IR(0, 0),IR(21848, 10)/* DepthLess */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {16,IR(0, 0),IR(21858, 15)/* DepthUnchanged */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {17,IR(22, 3),IR(21873, 10)/* LocalSize */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {18,IR(22, 3),IR(21883, 14)/* LocalSizeHint */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {19,IR(0, 0),IR(21897, 12)/* InputPoints */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {20,IR(0, 0),IR(21909, 11)/* InputLines */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {21,IR(0, 0),IR(21920, 20)/* InputLinesAdjacency */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {22,IR(0, 0),IR(21940, 10)/* Triangles */,IR(0, 0),IR(12, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {23,IR(0, 0),IR(21950, 24)/* InputTrianglesAdjacency */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {24,IR(0, 0),IR(21974, 6)/* Quads */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {25,IR(0, 0),IR(21980, 9)/* Isolines */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {26,IR(0, 1),IR(21989, 15)/* OutputVertices */,IR(0, 0),IR(156, 4),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {27,IR(0, 0),IR(22004, 13)/* OutputPoints */,IR(0, 0),IR(160, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {28,IR(0, 0),IR(22017, 16)/* OutputLineStrip */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {29,IR(0, 0),IR(22033, 20)/* OutputTriangleStrip */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {30,IR(0, 1),IR(22053, 12)/* VecTypeHint */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {31,IR(0, 0),IR(22065, 15)/* ContractionOff */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {33,IR(0, 0),IR(22080, 12)/* Initializer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {34,IR(0, 0),IR(22092, 10)/* Finalizer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {35,IR(0, 1),IR(6469, 13)/* SubgroupSize */,IR(0, 0),IR(163, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {36,IR(0, 1),IR(22102, 22)/* SubgroupsPerWorkgroup */,IR(0, 0),IR(163, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {37,IR(10, 1),IR(22124, 24)/* SubgroupsPerWorkgroupId */,IR(0, 0),IR(163, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {38,IR(33, 3),IR(22148, 12)/* LocalSizeId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {39,IR(33, 3),IR(22160, 16)/* LocalSizeHintId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4169,IR(0, 0),IR(22176, 34)/* NonCoherentColorAttachmentReadEXT */,IR(0, 0),IR(155, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4170,IR(0, 0),IR(22210, 34)/* NonCoherentDepthAttachmentReadEXT */,IR(0, 0),IR(164, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4171,IR(0, 0),IR(22244, 36)/* NonCoherentStencilAttachmentReadEXT */,IR(0, 0),IR(165, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4421,IR(0, 0),IR(22280, 30)/* SubgroupUniformControlFlowKHR */,IR(0, 0),IR(3, 1),IR(197, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4446,IR(0, 0),IR(22310, 18)/* PostDepthCoverage */,IR(0, 0),IR(166, 1),IR(45, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4459,IR(0, 1),IR(10717, 15)/* DenormPreserve */,IR(0, 0),IR(167, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4460,IR(0, 1),IR(10732, 18)/* DenormFlushToZero */,IR(0, 0),IR(168, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4461,IR(0, 1),IR(10750, 25)/* SignedZeroInfNanPreserve */,IR(0, 0),IR(169, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4462,IR(0, 1),IR(10775, 16)/* RoundingModeRTE */,IR(0, 0),IR(170, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4463,IR(0, 1),IR(10791, 16)/* RoundingModeRTZ */,IR(0, 0),IR(171, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4489,IR(0, 0),IR(22328, 34)/* NonCoherentTileAttachmentReadQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4490,IR(22, 3),IR(22362, 20)/* TileShadingRateQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5017,IR(0, 0),IR(22382, 29)/* EarlyAndLateFragmentTestsAMD */,IR(0, 0),IR(3, 1),IR(198, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5027,IR(0, 0),IR(22411, 23)/* StencilRefReplacingEXT */,IR(0, 0),IR(42, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5069,IR(0, 0),IR(22434, 15)/* CoalescingAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5070,IR(10, 1),IR(22449, 15)/* IsApiEntryAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5071,IR(10, 1),IR(22464, 21)/* MaxNodeRecursionAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5072,IR(33, 3),IR(22485, 24)/* StaticNumWorkgroupsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5073,IR(10, 1),IR(7362, 16)/* ShaderIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5077,IR(33, 3),IR(22509, 21)/* MaxNumWorkgroupsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5079,IR(0, 0),IR(22530, 28)/* StencilRefUnchangedFrontAMD */,IR(0, 0),IR(42, 1),IR(199, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5080,IR(0, 0),IR(22558, 26)/* StencilRefGreaterFrontAMD */,IR(0, 0),IR(42, 1),IR(199, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5081,IR(0, 0),IR(22584, 23)/* StencilRefLessFrontAMD */,IR(0, 0),IR(42, 1),IR(199, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5082,IR(0, 0),IR(22607, 27)/* StencilRefUnchangedBackAMD */,IR(0, 0),IR(42, 1),IR(199, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5083,IR(0, 0),IR(22634, 25)/* StencilRefGreaterBackAMD */,IR(0, 0),IR(42, 1),IR(199, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5084,IR(0, 0),IR(22659, 22)/* StencilRefLessBackAMD */,IR(0, 0),IR(42, 1),IR(199, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5088,IR(0, 0),IR(22681, 19)/* QuadDerivativesKHR */,IR(0, 0),IR(172, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5089,IR(0, 0),IR(22700, 20)/* RequireFullQuadsKHR */,IR(0, 0),IR(172, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5102,IR(36, 2),IR(22720, 20)/* SharesInputWithAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5157,IR(0, 0),IR(22740, 20)/* ArithmeticPoisonKHR */,IR(0, 0),IR(173, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5269,IR(0, 0),IR(22760, 15)/* OutputLinesEXT */,IR(123, 1),IR(130, 2),IR(193, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5270,IR(0, 1),IR(22789, 20)/* OutputPrimitivesEXT */,IR(124, 1),IR(130, 2),IR(193, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5289,IR(0, 0),IR(22828, 24)/* DerivativeGroupQuadsKHR */,IR(125, 1),IR(174, 1),IR(78, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5290,IR(0, 0),IR(22875, 25)/* DerivativeGroupLinearKHR */,IR(126, 1),IR(175, 1),IR(78, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5298,IR(0, 0),IR(22924, 19)/* OutputTrianglesEXT */,IR(127, 1),IR(130, 2),IR(193, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5366,IR(0, 0),IR(22961, 25)/* PixelInterlockOrderedEXT */,IR(0, 0),IR(176, 1),IR(86, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5367,IR(0, 0),IR(22986, 27)/* PixelInterlockUnorderedEXT */,IR(0, 0),IR(176, 1),IR(86, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5368,IR(0, 0),IR(23013, 26)/* SampleInterlockOrderedEXT */,IR(0, 0),IR(177, 1),IR(86, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5369,IR(0, 0),IR(23039, 28)/* SampleInterlockUnorderedEXT */,IR(0, 0),IR(177, 1),IR(86, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5370,IR(0, 0),IR(23067, 31)/* ShadingRateInterlockOrderedEXT */,IR(0, 0),IR(178, 1),IR(86, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5371,IR(0, 0),IR(23098, 33)/* ShadingRateInterlockUnorderedEXT */,IR(0, 0),IR(178, 1),IR(86, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5427,IR(0, 0),IR(13108, 23)/* Shader64BitIndexingEXT */,IR(0, 0),IR(179, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5618,IR(0, 1),IR(23131, 27)/* SharedLocalMemorySizeINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5620,IR(0, 1),IR(23158, 21)/* RoundingModeRTPINTEL */,IR(0, 0),IR(180, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5621,IR(0, 1),IR(23179, 21)/* RoundingModeRTNINTEL */,IR(0, 0),IR(180, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5622,IR(0, 1),IR(23200, 26)/* FloatingPointModeALTINTEL */,IR(0, 0),IR(180, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5623,IR(0, 1),IR(23226, 27)/* FloatingPointModeIEEEINTEL */,IR(0, 0),IR(180, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5893,IR(22, 3),IR(23253, 22)/* MaxWorkgroupSizeINTEL */,IR(0, 0),IR(181, 1),IR(124, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5894,IR(0, 1),IR(23275, 16)/* MaxWorkDimINTEL */,IR(0, 0),IR(181, 1),IR(124, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5895,IR(0, 0),IR(23291, 20)/* NoGlobalOffsetINTEL */,IR(0, 0),IR(181, 1),IR(124, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5896,IR(0, 1),IR(23311, 22)/* NumSIMDWorkitemsINTEL */,IR(0, 0),IR(111, 1),IR(124, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5903,IR(0, 1),IR(23333, 28)/* SchedulerTargetFmaxMhzINTEL */,IR(0, 0),IR(111, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6023,IR(0, 0),IR(23361, 24)/* MaximallyReconvergesKHR */,IR(0, 0),IR(3, 1),IR(201, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6028,IR(36, 2),IR(23385, 18)/* FPFastMathDefault */,IR(0, 0),IR(182, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6031,IR(10, 1),IR(23403, 21)/* OpacityMicromapIdKHR */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6154,IR(0, 1),IR(23424, 24)/* StreamingInterfaceINTEL */,IR(0, 0),IR(111, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6160,IR(0, 1),IR(23448, 26)/* RegisterMapInterfaceINTEL */,IR(0, 0),IR(184, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6417,IR(0, 1),IR(23474, 23)/* NamedBarrierCountINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6461,IR(0, 1),IR(23497, 22)/* MaximumRegistersINTEL */,IR(0, 0),IR(185, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6462,IR(10, 1),IR(23519, 24)/* MaximumRegistersIdINTEL */,IR(0, 0),IR(185, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6463,IR(38, 1),IR(23594, 27)/* NamedMaximumRegistersINTEL */,IR(0, 0),IR(185, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {0,IR(0, 0),IR(23621, 7)/* Vertex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {1,IR(0, 0),IR(23628, 20)/* TessellationControl */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {2,IR(0, 0),IR(23648, 23)/* TessellationEvaluation */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {3,IR(0, 0),IR(5950, 9)/* Geometry */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {4,IR(0, 0),IR(16758, 9)/* Fragment */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5,IR(0, 0),IR(23671, 10)/* GLCompute */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {6,IR(0, 0),IR(5717, 7)/* Kernel */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5267,IR(0, 0),IR(23681, 7)/* TaskNV */,IR(0, 0),IR(51, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5268,IR(0, 0),IR(23688, 7)/* MeshNV */,IR(0, 0),IR(51, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5313,IR(0, 0),IR(23695, 17)/* RayGenerationKHR */,IR(128, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5314,IR(0, 0),IR(23728, 16)/* IntersectionKHR */,IR(129, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5315,IR(0, 0),IR(23759, 10)/* AnyHitKHR */,IR(130, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5316,IR(0, 0),IR(23778, 14)/* ClosestHitKHR */,IR(131, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5317,IR(0, 0),IR(23805, 8)/* MissKHR */,IR(132, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5318,IR(0, 0),IR(23820, 12)/* CallableKHR */,IR(133, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5364,IR(0, 0),IR(23843, 8)/* TaskEXT */,IR(0, 0),IR(54, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5365,IR(0, 0),IR(23851, 8)/* MeshEXT */,IR(0, 0),IR(54, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {0,IR(0, 0),IR(23859, 9)/* Preserve */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPDENORM_MODE
  {1,IR(0, 0),IR(23868, 12)/* FlushToZero */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPDENORM_MODE
  {0,IR(0, 0),IR(23880, 12)/* BFloat16KHR */,IR(0, 0),IR(90, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {4214,IR(0, 0),IR(23892, 14)/* Float8E4M3EXT */,IR(0, 0),IR(117, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {4215,IR(0, 0),IR(23906, 14)/* Float8E5M2EXT */,IR(0, 0),IR(117, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {0,IR(0, 0),IR(23920, 5)/* IEEE */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPOPERATION_MODE
  {1,IR(0, 0),IR(23925, 4)/* ALT */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPOPERATION_MODE
  {0,IR(0, 0),IR(16354, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {1,IR(0, 0),IR(23929, 7)/* NotNaN */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {2,IR(0, 0),IR(23936, 7)/* NotInf */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {4,IR(0, 0),IR(23943, 4)/* NSZ */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {8,IR(0, 0),IR(23947, 11)/* AllowRecip */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {16,IR(0, 0),IR(23958, 5)/* Fast */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {65536,IR(0, 0),IR(23963, 14)/* AllowContract */,IR(134, 1),IR(186, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {131072,IR(0, 0),IR(24000, 13)/* AllowReassoc */,IR(135, 1),IR(186, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {262144,IR(0, 0),IR(24031, 15)/* AllowTransform */,IR(0, 0),IR(182, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {0,IR(0, 0),IR(24046, 4)/* RTE */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {1,IR(0, 0),IR(24050, 4)/* RTZ */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {2,IR(0, 0),IR(24054, 4)/* RTP */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {3,IR(0, 0),IR(24058, 4)/* RTN */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {1,IR(0, 0),IR(24062, 16)/* Vertical2Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {2,IR(0, 0),IR(24078, 16)/* Vertical4Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {4,IR(0, 0),IR(24094, 18)/* Horizontal2Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {8,IR(0, 0),IR(24112, 18)/* Horizontal4Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {0,IR(0, 0),IR(16354, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {1,IR(0, 0),IR(24130, 7)/* Inline */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {2,IR(0, 0),IR(24137, 11)/* DontInline */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {4,IR(0, 0),IR(24148, 5)/* Pure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {8,IR(0, 0),IR(24153, 6)/* Const */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {65536,IR(0, 0),IR(15179, 11)/* OptNoneEXT */,IR(68, 1),IR(188, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {0,IR(0, 0),IR(24159, 5)/* Zext */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {1,IR(0, 0),IR(24164, 5)/* Sext */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {2,IR(0, 0),IR(24169, 6)/* ByVal */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {3,IR(0, 0),IR(24175, 5)/* Sret */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {4,IR(0, 0),IR(24180, 8)/* NoAlias */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {5,IR(0, 0),IR(24188, 10)/* NoCapture */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {6,IR(0, 0),IR(24198, 8)/* NoWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {7,IR(0, 0),IR(24206, 12)/* NoReadWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {5940,IR(0, 0),IR(24218, 21)/* RuntimeAlignedALTERA */,IR(136, 1),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {0,IR(0, 0),IR(24259, 7)/* Reduce */,IR(0, 0),IR(190, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {1,IR(0, 0),IR(24266, 14)/* InclusiveScan */,IR(0, 0),IR(190, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {2,IR(0, 0),IR(24280, 14)/* ExclusiveScan */,IR(0, 0),IR(190, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {3,IR(0, 0),IR(24294, 16)/* ClusteredReduce */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {6,IR(0, 0),IR(24310, 21)/* PartitionedReduceEXT */,IR(137, 1),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {7,IR(0, 0),IR(24351, 28)/* PartitionedInclusiveScanEXT */,IR(138, 1),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {8,IR(0, 0),IR(24406, 28)/* PartitionedExclusiveScanEXT */,IR(139, 1),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {0,IR(0, 0),IR(24461, 10)/* NoneINTEL */,IR(0, 0),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {1,IR(0, 0),IR(24471, 10)/* ReadINTEL */,IR(0, 0),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {2,IR(0, 0),IR(24481, 11)/* WriteINTEL */,IR(0, 0),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {3,IR(0, 0),IR(24492, 15)/* ReadWriteINTEL */,IR(0, 0),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {0,IR(0, 0),IR(16354, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {1,IR(10, 1),IR(24507, 5)/* Bias */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {2,IR(10, 1),IR(24512, 4)/* Lod */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {4,IR(36, 2),IR(24516, 5)/* Grad */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {8,IR(10, 1),IR(24521, 12)/* ConstOffset */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {16,IR(10, 1),IR(17761, 7)/* Offset */,IR(0, 0),IR(195, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {32,IR(10, 1),IR(24533, 13)/* ConstOffsets */,IR(0, 0),IR(195, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {64,IR(10, 1),IR(17558, 7)/* Sample */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {128,IR(10, 1),IR(9550, 7)/* MinLod */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {256,IR(4, 1),IR(24546, 19)/* MakeTexelAvailable */,IR(140, 1),IR(197, 1),IR(84, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {512,IR(4, 1),IR(24587, 17)/* MakeTexelVisible */,IR(141, 1),IR(197, 1),IR(84, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {1024,IR(0, 0),IR(24624, 16)/* NonPrivateTexel */,IR(142, 1),IR(197, 1),IR(84, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {2048,IR(0, 0),IR(24659, 14)/* VolatileTexel */,IR(143, 1),IR(197, 1),IR(84, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {4096,IR(0, 0),IR(24690, 11)/* SignExtend */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {8192,IR(0, 0),IR(24701, 11)/* ZeroExtend */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {16384,IR(0, 0),IR(24712, 12)/* Nontemporal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {65536,IR(10, 1),IR(24724, 8)/* Offsets */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {0,IR(0, 0),IR(24732, 10)/* SnormInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {1,IR(0, 0),IR(24742, 11)/* SnormInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {2,IR(0, 0),IR(24753, 10)/* UnormInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {3,IR(0, 0),IR(24763, 11)/* UnormInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {4,IR(0, 0),IR(24774, 14)/* UnormShort565 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {5,IR(0, 0),IR(24788, 14)/* UnormShort555 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {6,IR(0, 0),IR(24802, 15)/* UnormInt101010 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {7,IR(0, 0),IR(24817, 11)/* SignedInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {8,IR(0, 0),IR(24828, 12)/* SignedInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {9,IR(0, 0),IR(24840, 12)/* SignedInt32 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {10,IR(0, 0),IR(24852, 13)/* UnsignedInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {11,IR(0, 0),IR(24865, 14)/* UnsignedInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {12,IR(0, 0),IR(24879, 14)/* UnsignedInt32 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {13,IR(0, 0),IR(24893, 10)/* HalfFloat */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {14,IR(0, 0),IR(16251, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {15,IR(0, 0),IR(24903, 11)/* UnormInt24 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {16,IR(0, 0),IR(24914, 17)/* UnormInt101010_2 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {17,IR(0, 0),IR(24931, 16)/* UnormInt10X6EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {19,IR(0, 0),IR(24947, 20)/* UnsignedIntRaw10EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {20,IR(0, 0),IR(24967, 20)/* UnsignedIntRaw12EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {21,IR(0, 0),IR(24987, 20)/* UnormInt2_101010EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {22,IR(0, 0),IR(25007, 19)/* UnsignedInt10X6EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {23,IR(0, 0),IR(25026, 19)/* UnsignedInt12X4EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {24,IR(0, 0),IR(25045, 19)/* UnsignedInt14X2EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {25,IR(0, 0),IR(25064, 16)/* UnormInt12X4EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {26,IR(0, 0),IR(25080, 16)/* UnormInt14X2EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {0,IR(0, 0),IR(25096, 2)/* R */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {1,IR(0, 0),IR(25098, 2)/* A */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {2,IR(0, 0),IR(25100, 3)/* RG */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {3,IR(0, 0),IR(25103, 3)/* RA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {4,IR(0, 0),IR(25106, 4)/* RGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {5,IR(0, 0),IR(25110, 5)/* RGBA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {6,IR(0, 0),IR(25115, 5)/* BGRA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {7,IR(0, 0),IR(25120, 5)/* ARGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {8,IR(0, 0),IR(25125, 10)/* Intensity */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {9,IR(0, 0),IR(25135, 10)/* Luminance */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {10,IR(0, 0),IR(25145, 3)/* Rx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {11,IR(0, 0),IR(25148, 4)/* RGx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {12,IR(0, 0),IR(25152, 5)/* RGBx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {13,IR(0, 0),IR(25157, 6)/* Depth */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {14,IR(0, 0),IR(25163, 13)/* DepthStencil */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {15,IR(0, 0),IR(25176, 5)/* sRGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {16,IR(0, 0),IR(25181, 6)/* sRGBx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {17,IR(0, 0),IR(25187, 6)/* sRGBA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {18,IR(0, 0),IR(25193, 6)/* sBGRA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {19,IR(0, 0),IR(25199, 5)/* ABGR */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {0,IR(0, 0),IR(25204, 28)/* InitOnDeviceReprogramALTERA */,IR(144, 1),IR(153, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {1,IR(0, 0),IR(25259, 24)/* InitOnDeviceResetALTERA */,IR(145, 1),IR(153, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {0,IR(0, 0),IR(25306, 7)/* NoWait */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {1,IR(0, 0),IR(25313, 11)/* WaitKernel */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {2,IR(0, 0),IR(25324, 14)/* WaitWorkGroup */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {0,IR(0, 0),IR(16354, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {1,IR(0, 0),IR(25338, 12)/* CmdExecTime */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {0,IR(0, 0),IR(16354, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {1,IR(0, 0),IR(25350, 13)/* MayUsePrintf */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {0,IR(0, 0),IR(25363, 7)/* Export */,IR(0, 0),IR(94, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {1,IR(0, 0),IR(25370, 7)/* Import */,IR(0, 0),IR(94, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {2,IR(0, 0),IR(25377, 12)/* LinkOnceODR */,IR(0, 0),IR(94, 1),IR(202, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {3,IR(0, 0),IR(25389, 8)/* WeakAMD */,IR(0, 0),IR(198, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {0,IR(0, 0),IR(25397, 14)/* UncachedINTEL */,IR(0, 0),IR(154, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {1,IR(0, 0),IR(25411, 12)/* CachedINTEL */,IR(0, 0),IR(154, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {2,IR(0, 0),IR(25423, 15)/* StreamingINTEL */,IR(0, 0),IR(154, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {3,IR(0, 0),IR(25438, 25)/* InvalidateAfterReadINTEL */,IR(0, 0),IR(154, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {4,IR(0, 0),IR(25463, 17)/* ConstCachedINTEL */,IR(0, 0),IR(154, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {0,IR(0, 0),IR(16354, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {1,IR(0, 0),IR(25480, 7)/* Unroll */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {2,IR(0, 0),IR(25487, 11)/* DontUnroll */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {4,IR(0, 0),IR(25498, 19)/* DependencyInfinite */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {8,IR(0, 1),IR(25517, 17)/* DependencyLength */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {16,IR(0, 1),IR(25534, 14)/* MinIterations */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {32,IR(0, 1),IR(25548, 14)/* MaxIterations */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {64,IR(0, 1),IR(25562, 18)/* IterationMultiple */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {128,IR(0, 1),IR(25580, 10)/* PeelCount */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {256,IR(0, 1),IR(25590, 13)/* PartialCount */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {65536,IR(0, 1),IR(20124, 25)/* InitiationIntervalALTERA */,IR(104, 1),IR(199, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {131072,IR(0, 1),IR(20173, 21)/* MaxConcurrencyALTERA */,IR(105, 1),IR(199, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {262144,IR(0, 1),IR(25603, 22)/* DependencyArrayALTERA */,IR(146, 1),IR(199, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {524288,IR(0, 1),IR(20214, 21)/* PipelineEnableALTERA */,IR(106, 1),IR(199, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {1048576,IR(0, 1),IR(25646, 19)/* LoopCoalesceALTERA */,IR(147, 1),IR(199, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {2097152,IR(0, 1),IR(25683, 22)/* MaxInterleavingALTERA */,IR(148, 1),IR(199, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {4194304,IR(0, 1),IR(25726, 27)/* SpeculatedIterationsALTERA */,IR(149, 1),IR(199, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {8388608,IR(0, 0),IR(25779, 15)/* NoFusionALTERA */,IR(150, 1),IR(199, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {16777216,IR(0, 1),IR(25808, 16)/* LoopCountALTERA */,IR(151, 1),IR(199, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {33554432,IR(0, 1),IR(25839, 27)/* MaxReinvocationDelayALTERA */,IR(152, 1),IR(199, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {0,IR(0, 0),IR(16354, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {1,IR(0, 0),IR(25892, 29)/* MatrixASignedComponentsINTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {2,IR(0, 0),IR(25921, 29)/* MatrixBSignedComponentsINTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {4,IR(0, 0),IR(25950, 21)/* MatrixCBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {8,IR(0, 0),IR(25971, 26)/* MatrixResultBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {16,IR(0, 0),IR(25997, 23)/* MatrixAPackedInt8INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {32,IR(0, 0),IR(26020, 23)/* MatrixBPackedInt8INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {64,IR(0, 0),IR(26043, 23)/* MatrixAPackedInt4INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {128,IR(0, 0),IR(26066, 23)/* MatrixBPackedInt4INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {256,IR(0, 0),IR(26089, 17)/* MatrixATF32INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {512,IR(0, 0),IR(26106, 17)/* MatrixBTF32INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {1024,IR(0, 0),IR(26123, 26)/* MatrixAPackedFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {2048,IR(0, 0),IR(26149, 26)/* MatrixBPackedFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {4096,IR(0, 0),IR(26175, 27)/* MatrixAPackedBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {8192,IR(0, 0),IR(26202, 27)/* MatrixBPackedBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {0,IR(0, 0),IR(16354, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {1,IR(0, 0),IR(17592, 9)/* Volatile */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {2,IR(0, 1),IR(26229, 8)/* Aligned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {4,IR(0, 0),IR(24712, 12)/* Nontemporal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {8,IR(4, 1),IR(26237, 21)/* MakePointerAvailable */,IR(153, 1),IR(197, 1),IR(84, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {16,IR(4, 1),IR(26282, 19)/* MakePointerVisible */,IR(154, 1),IR(197, 1),IR(84, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {32,IR(0, 0),IR(26323, 18)/* NonPrivatePointer */,IR(155, 1),IR(197, 1),IR(84, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {65536,IR(10, 1),IR(26362, 20)/* AliasScopeINTELMask */,IR(0, 0),IR(144, 1),IR(133, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {131072,IR(10, 1),IR(26382, 17)/* NoAliasINTELMask */,IR(0, 0),IR(144, 1),IR(133, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {0,IR(0, 0),IR(26399, 7)/* Simple */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {1,IR(0, 0),IR(26406, 8)/* GLSL450 */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {2,IR(0, 0),IR(26414, 7)/* OpenCL */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {3,IR(0, 0),IR(26421, 7)/* Vulkan */,IR(156, 1),IR(197, 1),IR(84, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {0,IR(0, 0),IR(26438, 8)/* Relaxed */,IR(157, 1),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {2,IR(0, 0),IR(26446, 8)/* Acquire */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {4,IR(0, 0),IR(26454, 8)/* Release */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {8,IR(0, 0),IR(26462, 15)/* AcquireRelease */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {16,IR(0, 0),IR(26477, 23)/* SequentiallyConsistent */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {64,IR(0, 0),IR(26500, 14)/* UniformMemory */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {128,IR(0, 0),IR(26514, 15)/* SubgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {256,IR(0, 0),IR(26529, 16)/* WorkgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {512,IR(0, 0),IR(26545, 21)/* CrossWorkgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {1024,IR(0, 0),IR(26566, 20)/* AtomicCounterMemory */,IR(0, 0),IR(83, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {2048,IR(0, 0),IR(26586, 12)/* ImageMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {4096,IR(0, 0),IR(26598, 13)/* OutputMemory */,IR(158, 1),IR(197, 1),IR(84, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {8192,IR(0, 0),IR(26627, 14)/* MakeAvailable */,IR(159, 1),IR(197, 1),IR(84, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {16384,IR(0, 0),IR(26658, 12)/* MakeVisible */,IR(160, 1),IR(197, 1),IR(84, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {32768,IR(0, 0),IR(17592, 9)/* Volatile */,IR(0, 0),IR(197, 1),IR(84, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {0,IR(0, 0),IR(26685, 10)/* AutoINTEL */,IR(0, 0),IR(185, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS
  {0,IR(0, 0),IR(26695, 5)/* WRAP */,IR(0, 0),IR(200, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {1,IR(0, 0),IR(26700, 4)/* SAT */,IR(0, 0),IR(200, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {2,IR(0, 0),IR(26704, 9)/* SAT_ZERO */,IR(0, 0),IR(200, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {3,IR(0, 0),IR(26713, 8)/* SAT_SYM */,IR(0, 0),IR(200, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {0,IR(0, 0),IR(26721, 25)/* PackedVectorFormat4x8Bit */,IR(161, 1),IR(1, 0),IR(150, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {0,IR(0, 0),IR(26774, 4)/* TRN */,IR(0, 0),IR(200, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {1,IR(0, 0),IR(26778, 9)/* TRN_ZERO */,IR(0, 0),IR(200, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {2,IR(0, 0),IR(26787, 4)/* RND */,IR(0, 0),IR(200, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {3,IR(0, 0),IR(26791, 9)/* RND_ZERO */,IR(0, 0),IR(200, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {4,IR(0, 0),IR(26800, 8)/* RND_INF */,IR(0, 0),IR(200, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {5,IR(0, 0),IR(26808, 12)/* RND_MIN_INF */,IR(0, 0),IR(200, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {6,IR(0, 0),IR(26820, 9)/* RND_CONV */,IR(0, 0),IR(200, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {7,IR(0, 0),IR(26829, 13)/* RND_CONV_ODD */,IR(0, 0),IR(200, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {0,IR(0, 0),IR(16354, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {1,IR(0, 0),IR(26842, 25)/* RobustnessPerComponentNV */,IR(0, 0),IR(201, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {2,IR(0, 0),IR(26867, 23)/* RobustnessPerElementNV */,IR(0, 0),IR(201, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {0,IR(0, 0),IR(17106, 8)/* NoneKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {1,IR(0, 0),IR(26890, 10)/* OpaqueKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {2,IR(0, 0),IR(26900, 12)/* NoOpaqueKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {4,IR(0, 0),IR(26912, 23)/* TerminateOnFirstHitKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {8,IR(0, 0),IR(26935, 24)/* SkipClosestHitShaderKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {16,IR(0, 0),IR(26959, 27)/* CullBackFacingTrianglesKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {32,IR(0, 0),IR(26986, 28)/* CullFrontFacingTrianglesKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {64,IR(0, 0),IR(27014, 14)/* CullOpaqueKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {128,IR(0, 0),IR(27028, 16)/* CullNoOpaqueKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {256,IR(0, 0),IR(27044, 17)/* SkipTrianglesKHR */,IR(162, 1),IR(202, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {512,IR(0, 0),IR(27085, 13)/* SkipAABBsKHR */,IR(0, 0),IR(202, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {1024,IR(0, 0),IR(27098, 30)/* ForceOpacityMicromap2StateKHR */,IR(163, 1),IR(203, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {0,IR(0, 0),IR(27158, 41)/* RayQueryCandidateIntersectionTriangleKHR */,IR(0, 0),IR(204, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {1,IR(0, 0),IR(27199, 37)/* RayQueryCandidateIntersectionAABBKHR */,IR(0, 0),IR(204, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {0,IR(0, 0),IR(27236, 37)/* RayQueryCommittedIntersectionNoneKHR */,IR(0, 0),IR(204, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {1,IR(0, 0),IR(27273, 41)/* RayQueryCommittedIntersectionTriangleKHR */,IR(0, 0),IR(204, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {2,IR(0, 0),IR(27314, 42)/* RayQueryCommittedIntersectionGeneratedKHR */,IR(0, 0),IR(204, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {0,IR(0, 0),IR(27356, 33)/* RayQueryCandidateIntersectionKHR */,IR(0, 0),IR(204, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {1,IR(0, 0),IR(27389, 33)/* RayQueryCommittedIntersectionKHR */,IR(0, 0),IR(204, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {0,IR(0, 0),IR(16354, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {1,IR(0, 0),IR(27422, 12)/* ClampToEdge */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {2,IR(0, 0),IR(27434, 6)/* Clamp */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {3,IR(0, 0),IR(27440, 7)/* Repeat */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {4,IR(0, 0),IR(27447, 15)/* RepeatMirrored */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {0,IR(0, 0),IR(27462, 8)/* Nearest */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {1,IR(0, 0),IR(27470, 7)/* Linear */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {0,IR(0, 0),IR(27477, 8)/* Unknown */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {1,IR(0, 0),IR(27485, 8)/* Rgba32f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {2,IR(0, 0),IR(27493, 8)/* Rgba16f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {3,IR(0, 0),IR(27501, 5)/* R32f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {4,IR(0, 0),IR(27506, 6)/* Rgba8 */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {5,IR(0, 0),IR(27512, 11)/* Rgba8Snorm */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {6,IR(0, 0),IR(27523, 6)/* Rg32f */,IR(0, 0),IR(205, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {7,IR(0, 0),IR(27529, 6)/* Rg16f */,IR(0, 0),IR(205, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {8,IR(0, 0),IR(27535, 13)/* R11fG11fB10f */,IR(0, 0),IR(205, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {9,IR(0, 0),IR(27548, 5)/* R16f */,IR(0, 0),IR(205, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {10,IR(0, 0),IR(27553, 7)/* Rgba16 */,IR(0, 0),IR(205, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {11,IR(0, 0),IR(27560, 8)/* Rgb10A2 */,IR(0, 0),IR(205, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {12,IR(0, 0),IR(27568, 5)/* Rg16 */,IR(0, 0),IR(205, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {13,IR(0, 0),IR(27573, 4)/* Rg8 */,IR(0, 0),IR(205, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {14,IR(0, 0),IR(27577, 4)/* R16 */,IR(0, 0),IR(205, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {15,IR(0, 0),IR(27581, 3)/* R8 */,IR(0, 0),IR(205, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {16,IR(0, 0),IR(27584, 12)/* Rgba16Snorm */,IR(0, 0),IR(205, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {17,IR(0, 0),IR(27596, 10)/* Rg16Snorm */,IR(0, 0),IR(205, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {18,IR(0, 0),IR(27606, 9)/* Rg8Snorm */,IR(0, 0),IR(205, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {19,IR(0, 0),IR(27615, 9)/* R16Snorm */,IR(0, 0),IR(205, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {20,IR(0, 0),IR(27624, 8)/* R8Snorm */,IR(0, 0),IR(205, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {21,IR(0, 0),IR(27632, 8)/* Rgba32i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {22,IR(0, 0),IR(27640, 8)/* Rgba16i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {23,IR(0, 0),IR(27648, 7)/* Rgba8i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {24,IR(0, 0),IR(27655, 5)/* R32i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {25,IR(0, 0),IR(27660, 6)/* Rg32i */,IR(0, 0),IR(205, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {26,IR(0, 0),IR(27666, 6)/* Rg16i */,IR(0, 0),IR(205, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {27,IR(0, 0),IR(27672, 5)/* Rg8i */,IR(0, 0),IR(205, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {28,IR(0, 0),IR(27677, 5)/* R16i */,IR(0, 0),IR(205, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {29,IR(0, 0),IR(27682, 4)/* R8i */,IR(0, 0),IR(205, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {30,IR(0, 0),IR(27686, 9)/* Rgba32ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {31,IR(0, 0),IR(27695, 9)/* Rgba16ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {32,IR(0, 0),IR(27704, 8)/* Rgba8ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {33,IR(0, 0),IR(27712, 6)/* R32ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {34,IR(0, 0),IR(27718, 10)/* Rgb10a2ui */,IR(0, 0),IR(205, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {35,IR(0, 0),IR(27728, 7)/* Rg32ui */,IR(0, 0),IR(205, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {36,IR(0, 0),IR(27735, 7)/* Rg16ui */,IR(0, 0),IR(205, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {37,IR(0, 0),IR(27742, 6)/* Rg8ui */,IR(0, 0),IR(205, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {38,IR(0, 0),IR(27748, 6)/* R16ui */,IR(0, 0),IR(205, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {39,IR(0, 0),IR(27754, 5)/* R8ui */,IR(0, 0),IR(205, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {40,IR(0, 0),IR(27759, 6)/* R64ui */,IR(0, 0),IR(206, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {41,IR(0, 0),IR(27765, 5)/* R64i */,IR(0, 0),IR(206, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {0,IR(0, 0),IR(27770, 12)/* CrossDevice */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {1,IR(0, 0),IR(27782, 7)/* Device */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {2,IR(0, 0),IR(27789, 10)/* Workgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {3,IR(0, 0),IR(27799, 9)/* Subgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {4,IR(0, 0),IR(27808, 11)/* Invocation */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {5,IR(0, 0),IR(27819, 12)/* QueueFamily */,IR(164, 1),IR(197, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {6,IR(0, 0),IR(27846, 14)/* ShaderCallKHR */,IR(0, 0),IR(61, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {0,IR(0, 0),IR(16354, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {1,IR(0, 0),IR(27860, 8)/* Flatten */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {2,IR(0, 0),IR(27868, 12)/* DontFlatten */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {1,IR(0, 0),IR(27880, 29)/* IdentifierPossibleDuplicates */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS
  {0,IR(0, 0),IR(16223, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(16235, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(16243, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {3,IR(0, 0),IR(16251, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(16257, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(16264, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(16275, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(16284, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(16297, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(16303, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(16313, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(16319, 15)/* ImportedModule */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {1,IR(0, 0),IR(16334, 20)/* ImportedDeclaration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {0,IR(0, 0),IR(16354, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(16359, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(16375, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(16389, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(16402, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(16414, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(16431, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(16443, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(16458, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(16471, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(16486, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(16504, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(16521, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(16542, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(16562, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(16582, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {16384,IR(0, 0),IR(16598, 16)/* FlagIsEnumClass */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {32768,IR(0, 0),IR(16614, 20)/* FlagTypePassByValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {65536,IR(0, 0),IR(16634, 24)/* FlagTypePassByReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {131072,IR(0, 0),IR(27909, 26)/* FlagUnknownPhysicalLayout */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(16658, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {1,IR(0, 0),IR(16664, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {2,IR(0, 0),IR(16669, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {3,IR(10, 1),IR(16708, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {4,IR(36, 2),IR(16719, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {5,IR(0, 0),IR(16728, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {6,IR(0, 0),IR(16733, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {7,IR(0, 0),IR(16740, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {8,IR(10, 1),IR(16751, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {9,IR(36, 2),IR(16758, 9)/* Fragment */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {0,IR(0, 0),IR(16767, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(16777, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(16790, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {3,IR(0, 0),IR(16803, 11)/* AtomicType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(27477, 8)/* Unknown */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {1,IR(0, 0),IR(27935, 5)/* ESSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {2,IR(0, 0),IR(27940, 5)/* GLSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {3,IR(0, 0),IR(27945, 9)/* OpenCL_C */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {4,IR(0, 0),IR(27954, 11)/* OpenCL_CPP */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {5,IR(0, 0),IR(27965, 5)/* HLSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {6,IR(0, 0),IR(27970, 15)/* CPP_for_OpenCL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {7,IR(0, 0),IR(27985, 5)/* SYCL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {8,IR(0, 0),IR(27990, 7)/* HERO_C */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {9,IR(0, 0),IR(27997, 5)/* NZSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {10,IR(0, 0),IR(28002, 5)/* WGSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {11,IR(0, 0),IR(28007, 6)/* Slang */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {12,IR(0, 0),IR(28013, 4)/* Zig */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {13,IR(0, 0),IR(28017, 5)/* Rust */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {14,IR(0, 0),IR(28022, 5)/* Pred */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {0,IR(0, 0),IR(28027, 16)/* UniformConstant */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {1,IR(0, 0),IR(28043, 6)/* Input */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {2,IR(0, 0),IR(17643, 8)/* Uniform */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {3,IR(0, 0),IR(28049, 7)/* Output */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4,IR(0, 0),IR(27789, 10)/* Workgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5,IR(0, 0),IR(28056, 15)/* CrossWorkgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {6,IR(0, 0),IR(28071, 8)/* Private */,IR(0, 0),IR(207, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {7,IR(0, 0),IR(28079, 9)/* Function */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {8,IR(0, 0),IR(28088, 8)/* Generic */,IR(0, 0),IR(209, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {9,IR(0, 0),IR(28096, 13)/* PushConstant */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {10,IR(0, 0),IR(28109, 14)/* AtomicCounter */,IR(0, 0),IR(83, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {11,IR(0, 0),IR(28123, 6)/* Image */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {12,IR(0, 0),IR(28129, 14)/* StorageBuffer */,IR(0, 0),IR(3, 1),IR(203, 2),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4172,IR(0, 0),IR(28143, 13)/* TileImageEXT */,IR(0, 0),IR(155, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4491,IR(0, 0),IR(28156, 19)/* TileAttachmentQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5068,IR(0, 0),IR(28175, 16)/* NodePayloadAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5328,IR(0, 0),IR(28191, 16)/* CallableDataKHR */,IR(165, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5329,IR(0, 0),IR(28222, 24)/* IncomingCallableDataKHR */,IR(166, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5338,IR(0, 0),IR(28269, 14)/* RayPayloadKHR */,IR(167, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5339,IR(0, 0),IR(28296, 16)/* HitAttributeKHR */,IR(168, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5342,IR(0, 0),IR(28327, 22)/* IncomingRayPayloadKHR */,IR(169, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5343,IR(0, 0),IR(28370, 22)/* ShaderRecordBufferKHR */,IR(170, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5349,IR(0, 0),IR(28413, 22)/* PhysicalStorageBuffer */,IR(171, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5385,IR(0, 0),IR(28460, 21)/* HitObjectAttributeNV */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5402,IR(0, 0),IR(28481, 24)/* TaskPayloadWorkgroupEXT */,IR(0, 0),IR(54, 1),IR(23, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5411,IR(0, 0),IR(28505, 22)/* HitObjectAttributeEXT */,IR(0, 0),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5605,IR(0, 0),IR(28527, 17)/* CodeSectionINTEL */,IR(0, 0),IR(210, 1),IR(107, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5936,IR(0, 0),IR(28544, 17)/* DeviceOnlyALTERA */,IR(172, 1),IR(211, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5937,IR(0, 0),IR(28577, 15)/* HostOnlyALTERA */,IR(173, 1),IR(211, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {0,IR(0, 0),IR(25397, 14)/* UncachedINTEL */,IR(0, 0),IR(154, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {1,IR(0, 0),IR(28606, 18)/* WriteThroughINTEL */,IR(0, 0),IR(154, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {2,IR(0, 0),IR(28624, 15)/* WriteBackINTEL */,IR(0, 0),IR(154, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {3,IR(0, 0),IR(25423, 15)/* StreamingINTEL */,IR(0, 0),IR(154, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {0,IR(0, 0),IR(16354, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {1,IR(10, 1),IR(28639, 11)/* TensorView */,IR(0, 0),IR(212, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {2,IR(10, 1),IR(28650, 11)/* DecodeFunc */,IR(0, 0),IR(107, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {4,IR(10, 1),IR(28661, 17)/* DecodeVectorFunc */,IR(0, 0),IR(213, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {0,IR(0, 0),IR(28678, 10)/* Undefined */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {1,IR(0, 0),IR(17601, 9)/* Constant */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {2,IR(0, 0),IR(27422, 12)/* ClampToEdge */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {3,IR(0, 0),IR(27440, 7)/* Repeat */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {4,IR(0, 0),IR(27447, 15)/* RepeatMirrored */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {0,IR(0, 0),IR(28688, 8)/* NoneARM */,IR(0, 0),IR(214, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {1,IR(0, 0),IR(28696, 15)/* NontemporalARM */,IR(0, 0),IR(214, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {2,IR(10, 1),IR(28711, 20)/* OutOfBoundsValueARM */,IR(0, 0),IR(214, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {4,IR(10, 1),IR(28731, 24)/* MakeElementAvailableARM */,IR(0, 0),IR(214, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {8,IR(10, 1),IR(28755, 22)/* MakeElementVisibleARM */,IR(0, 0),IR(214, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {16,IR(0, 0),IR(28777, 21)/* NonPrivateElementARM */,IR(0, 0),IR(214, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
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
    case SPV_OPERAND_TYPE_CAPABILITY: return IR(135, 292);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(427, 8);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(435, 3);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(438, 2);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS: return IR(440, 19);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION: return IR(459, 10);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(469, 4);
    case SPV_OPERAND_TYPE_COMPONENT_TYPE: return IR(473, 15);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT: return IR(488, 4);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS: return IR(492, 6);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE: return IR(498, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE: return IR(501, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT: return IR(504, 4);
    case SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(508, 8);
    case SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE: return IR(516, 3);
    case SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS: return IR(519, 16);
    case SPV_OPERAND_TYPE_DEBUG_OPERATION: return IR(535, 9);
    case SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER: return IR(544, 3);
    case SPV_OPERAND_TYPE_DECORATION: return IR(547, 150);
    case SPV_OPERAND_TYPE_DIMENSIONALITY: return IR(697, 8);
    case SPV_OPERAND_TYPE_EXECUTION_MODE: return IR(705, 99);
    case SPV_OPERAND_TYPE_EXECUTION_MODEL: return IR(804, 17);
    case SPV_OPERAND_TYPE_FPDENORM_MODE: return IR(821, 2);
    case SPV_OPERAND_TYPE_FPENCODING: return IR(823, 3);
    case SPV_OPERAND_TYPE_FPOPERATION_MODE: return IR(826, 2);
    case SPV_OPERAND_TYPE_FP_FAST_MATH_MODE: return IR(828, 9);
    case SPV_OPERAND_TYPE_FP_ROUNDING_MODE: return IR(837, 4);
    case SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE: return IR(841, 4);
    case SPV_OPERAND_TYPE_FUNCTION_CONTROL: return IR(845, 6);
    case SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE: return IR(851, 9);
    case SPV_OPERAND_TYPE_GROUP_OPERATION: return IR(860, 7);
    case SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER: return IR(867, 4);
    case SPV_OPERAND_TYPE_IMAGE: return IR(871, 17);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE: return IR(888, 26);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER: return IR(914, 20);
    case SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER: return IR(934, 2);
    case SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS: return IR(936, 3);
    case SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO: return IR(939, 2);
    case SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS: return IR(941, 2);
    case SPV_OPERAND_TYPE_LINKAGE_TYPE: return IR(943, 4);
    case SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL: return IR(947, 5);
    case SPV_OPERAND_TYPE_LOOP_CONTROL: return IR(952, 20);
    case SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(972, 15);
    case SPV_OPERAND_TYPE_MEMORY_ACCESS: return IR(987, 9);
    case SPV_OPERAND_TYPE_MEMORY_MODEL: return IR(996, 4);
    case SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID: return IR(1000, 15);
    case SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS: return IR(1015, 1);
    case SPV_OPERAND_TYPE_OVERFLOW_MODES: return IR(1016, 4);
    case SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT: return IR(1020, 1);
    case SPV_OPERAND_TYPE_QUANTIZATION_MODES: return IR(1021, 8);
    case SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS: return IR(1029, 3);
    case SPV_OPERAND_TYPE_RAY_FLAGS: return IR(1032, 12);
    case SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE: return IR(1044, 2);
    case SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE: return IR(1046, 3);
    case SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION: return IR(1049, 2);
    case SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE: return IR(1051, 5);
    case SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE: return IR(1056, 2);
    case SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT: return IR(1058, 42);
    case SPV_OPERAND_TYPE_SCOPE_ID: return IR(1100, 7);
    case SPV_OPERAND_TYPE_SELECTION_CONTROL: return IR(1107, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS: return IR(1110, 1);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(1111, 8);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(1119, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(1122, 2);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS: return IR(1124, 20);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION: return IR(1144, 10);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(1154, 4);
    case SPV_OPERAND_TYPE_SOURCE_LANGUAGE: return IR(1158, 15);
    case SPV_OPERAND_TYPE_STORAGE_CLASS: return IR(1173, 29);
    case SPV_OPERAND_TYPE_STORE_CACHE_CONTROL: return IR(1202, 4);
    case SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS: return IR(1206, 4);
    case SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE: return IR(1210, 5);
    case SPV_OPERAND_TYPE_TENSOR_OPERANDS: return IR(1215, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_IMAGE: return IR(871, 17);
    case SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS: return IR(987, 9);
    case SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT: return IR(1020, 1);
    case SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS: return IR(492, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(972, 15);
    case SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS: return IR(1029, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_FPENCODING: return IR(823, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS: return IR(1215, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_CAPABILITY: return IR(135, 292);
    default: break;
  }
  return IR(0,0);
}

// Operand names and index into kOperandsByValue, ordered by (operand kind, name)
// The fields in order are:
//   name, either the primary name or an alias, indexing into kStrings
//   index into the kOperandsByValue array
static const std::array<NameIndex, 1399> kOperandNames{{
  {IR(5708, 9), 0}, // 0 ReadOnly in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(5734, 10), 2}, // 1 ReadWrite in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(5724, 10), 1}, // 2 WriteOnly in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(5744, 8), 3}, // 3 Logical in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5752, 11), 4}, // 4 Physical32 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5773, 11), 5}, // 5 Physical64 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5784, 24), 6}, // 6 PhysicalStorageBuffer64 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5808, 27), 6}, // 7 PhysicalStorageBuffer64EXT in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(7767, 13), 94}, // 8 BaryCoordKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7780, 12), 94}, // 9 BaryCoordNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7113, 20), 68}, // 10 BaryCoordNoPerspAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7133, 28), 69}, // 11 BaryCoordNoPerspCentroidAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7815, 20), 95}, // 12 BaryCoordNoPerspKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7835, 19), 95}, // 13 BaryCoordNoPerspNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7161, 26), 70}, // 14 BaryCoordNoPerspSampleAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7258, 22), 74}, // 15 BaryCoordPullModelAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7187, 19), 71}, // 16 BaryCoordSmoothAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7206, 27), 72}, // 17 BaryCoordSmoothCentroidAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7233, 25), 73}, // 18 BaryCoordSmoothSampleAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6917, 13), 59}, // 19 BaseInstance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6891, 11), 58}, // 20 BaseVertex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5892, 13), 9}, // 21 ClipDistance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7674, 22), 89}, // 22 ClipDistancePerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8973, 12), 133}, // 23 ClusterIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6655, 13), 49}, // 24 CoreCountARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6629, 10), 48}, // 25 CoreIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6668, 13), 50}, // 26 CoreMaxIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5905, 13), 10}, // 27 CullDistance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7696, 22), 90}, // 28 CullDistancePerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(9026, 12), 134}, // 29 CullMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8022, 17), 101}, // 30 CullPrimitiveEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8426, 17), 115}, // 31 CurrentRayTimeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6987, 12), 62}, // 32 DeviceIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6930, 10), 60}, // 33 DrawIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6419, 22), 37}, // 34 EnqueuedWorkgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6189, 10), 21}, // 35 FragCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6275, 10), 27}, // 36 FragDepth in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7900, 23), 97}, // 37 FragInvocationCountEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7854, 12), 96}, // 38 FragSizeEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7280, 18), 75}, // 39 FragStencilRefEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7866, 15), 96}, // 40 FragmentSizeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6210, 12), 23}, // 41 FrontFacing in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7586, 16), 85}, // 42 FullyCoveredEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6360, 19), 33}, // 43 GlobalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6454, 15), 39}, // 44 GlobalLinearId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6441, 13), 38}, // 45 GlobalOffset in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6408, 11), 36}, // 46 GlobalSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6285, 17), 28}, // 47 HelperInvocation in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8728, 11), 122}, // 48 HitIsLSSNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8686, 14), 121}, // 49 HitIsSphereNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8908, 33), 130}, // 50 HitKindBackFacingMicroTriangleNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8874, 34), 129}, // 51 HitKindFrontFacingMicroTriangleNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8405, 11), 114}, // 52 HitKindKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8416, 10), 114}, // 53 HitKindNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8856, 18), 128}, // 54 HitLSSPositionsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8959, 14), 132}, // 55 HitLSSRadiiNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8590, 37), 118}, // 56 HitMicroTriangleVertexBarycentricsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8523, 34), 117}, // 57 HitMicroTriangleVertexPositionsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8778, 20), 123}, // 58 HitSpherePositionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8941, 18), 131}, // 59 HitSphereRadiusNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8398, 7), 113}, // 60 HitTNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8466, 30), 116}, // 61 HitTriangleVertexPositionsKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8627, 20), 119}, // 62 IncomingRayFlagsKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8647, 19), 119}, // 63 IncomingRayFlagsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8287, 23), 110}, // 64 InstanceCustomIndexKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8310, 22), 110}, // 65 InstanceCustomIndexNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5927, 11), 12}, // 66 InstanceId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6615, 14), 47}, // 67 InstanceIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6028, 13), 14}, // 68 InvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7923, 22), 97}, // 69 InvocationsPerPixelNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8039, 12), 102}, // 70 LaunchIdKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8051, 11), 102}, // 71 LaunchIdNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8062, 14), 103}, // 72 LaunchSizeKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8076, 13), 103}, // 73 LaunchSizeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6041, 6), 15}, // 74 Layer in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7718, 15), 91}, // 75 LayerPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6342, 18), 32}, // 76 LocalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6379, 21), 34}, // 77 LocalInvocationIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7733, 16), 92}, // 78 MeshViewCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7749, 18), 93}, // 79 MeshViewIndicesNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6545, 21), 43}, // 80 NumEnqueuedSubgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6532, 13), 42}, // 81 NumSubgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6302, 14), 29}, // 82 NumWorkgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8202, 22), 107}, // 83 ObjectRayDirectionKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8224, 21), 107}, // 84 ObjectRayDirectionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8165, 19), 106}, // 85 ObjectRayOriginKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8184, 18), 106}, // 86 ObjectRayOriginNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8332, 17), 111}, // 87 ObjectToWorldKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8349, 16), 111}, // 88 ObjectToWorldNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6175, 14), 20}, // 89 PatchVertices in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6199, 11), 22}, // 90 PointCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5882, 10), 8}, // 91 PointSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5866, 9), 7}, // 92 Position in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7526, 18), 83}, // 93 PositionPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7638, 17), 87}, // 94 PrimitiveCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5938, 12), 13}, // 95 PrimitiveId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7655, 19), 88}, // 96 PrimitiveIndicesNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7970, 24), 99}, // 97 PrimitiveLineIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7945, 25), 98}, // 98 PrimitivePointIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6940, 24), 61}, // 99 PrimitiveShadingRateKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7994, 28), 100}, // 100 PrimitiveTriangleIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8666, 20), 120}, // 101 RayGeometryIndexKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8266, 11), 109}, // 102 RayTmaxKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8277, 10), 109}, // 103 RayTmaxNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8245, 11), 108}, // 104 RayTminKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8256, 10), 108}, // 105 RayTminNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7315, 29), 76}, // 106 RemainingRecursionLevelsAMDX in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7411, 16), 79}, // 107 ResourceHeapEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8830, 10), 125}, // 108 SMCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8849, 7), 127}, // 109 SMIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6222, 9), 24}, // 110 SampleId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6264, 11), 26}, // 111 SampleMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6249, 15), 25}, // 112 SamplePosition in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7378, 15), 78}, // 113 SamplerHeapEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7463, 20), 81}, // 114 SecondaryPositionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7502, 24), 82}, // 115 SecondaryViewportMaskNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7362, 16), 77}, // 116 ShaderIndexAMDX in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7031, 15), 64}, // 117 ShadingRateKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6704, 15), 53}, // 118 SubgroupEqMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6719, 18), 53}, // 119 SubgroupEqMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6759, 15), 54}, // 120 SubgroupGeMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6774, 18), 54}, // 121 SubgroupGeMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6792, 15), 55}, // 122 SubgroupGtMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6807, 18), 55}, // 123 SubgroupGtMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6566, 11), 44}, // 124 SubgroupId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6825, 15), 56}, // 125 SubgroupLeMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6840, 18), 56}, // 126 SubgroupLeMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6577, 26), 45}, // 127 SubgroupLocalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6858, 15), 57}, // 128 SubgroupLtMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6873, 18), 57}, // 129 SubgroupLtMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6516, 16), 41}, // 130 SubgroupMaxSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6469, 13), 40}, // 131 SubgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7626, 12), 86}, // 132 TaskCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6165, 10), 19}, // 133 TessCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6150, 15), 18}, // 134 TessLevelInner in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6135, 15), 17}, // 135 TessLevelOuter in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7095, 18), 67}, // 136 TileApronSizeQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7077, 18), 66}, // 137 TileDimensionQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7046, 15), 65}, // 138 TileOffsetQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5918, 9), 11}, // 139 VertexId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6603, 12), 46}, // 140 VertexIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7011, 10), 63}, // 141 ViewIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6087, 14), 16}, // 142 ViewportIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7427, 15), 80}, // 143 ViewportMaskNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7564, 22), 84}, // 144 ViewportMaskPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6681, 10), 51}, // 145 WarpIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8840, 9), 126}, // 146 WarpIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6691, 13), 52}, // 147 WarpMaxIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8798, 13), 124}, // 148 WarpsPerSMNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6400, 8), 35}, // 149 WorkDim in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6330, 12), 31}, // 150 WorkgroupId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6316, 14), 30}, // 151 WorkgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8124, 21), 105}, // 152 WorldRayDirectionKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8145, 20), 105}, // 153 WorldRayDirectionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8089, 18), 104}, // 154 WorldRayOriginKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8107, 17), 104}, // 155 WorldRayOriginNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8365, 17), 112}, // 156 WorldToObjectKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8382, 16), 112}, // 157 WorldToObjectNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(11244, 9), 266}, // 158 AbortKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5763, 10), 139}, // 159 Addresses in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14550, 35), 371}, // 160 ArbitraryPrecisionFixedPointALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14585, 34), 371}, // 161 ArbitraryPrecisionFixedPointINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14022, 38), 359}, // 162 ArbitraryPrecisionFloatingPointALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14060, 37), 359}, // 163 ArbitraryPrecisionFloatingPointINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13957, 33), 358}, // 164 ArbitraryPrecisionIntegersALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13990, 32), 358}, // 165 ArbitraryPrecisionIntegersINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15302, 19), 397}, // 166 ArithmeticFenceEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13595, 9), 344}, // 167 AsmINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15203, 20), 393}, // 168 AtomicFloat16AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13650, 23), 347}, // 169 AtomicFloat16MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13034, 22), 318}, // 170 AtomicFloat16VectorNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15119, 20), 389}, // 171 AtomicFloat32AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13604, 23), 345}, // 172 AtomicFloat32MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15139, 20), 390}, // 173 AtomicFloat64AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13627, 23), 346}, // 174 AtomicFloat64MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9206, 14), 155}, // 175 AtomicStorage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10593, 17), 231}, // 176 AtomicStorageOps in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15244, 24), 395}, // 177 BFloat16ConversionINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11215, 29), 265}, // 178 BFloat16CooperativeMatrixKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11193, 22), 264}, // 179 BFloat16DotProductKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11177, 16), 263}, // 180 BFloat16TypeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16078, 20), 422}, // 181 BindlessImagesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12971, 18), 315}, // 182 BindlessTextureNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15014, 16), 384}, // 183 BitInstructions in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14752, 20), 375}, // 184 BlockingPipesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14772, 19), 375}, // 185 BlockingPipesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16039, 19), 420}, // 186 CacheControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5892, 13), 165}, // 187 ClipDistance in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12573, 32), 303}, // 188 ComputeDerivativeGroupLinearKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12605, 31), 303}, // 189 ComputeDerivativeGroupLinearNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11423, 31), 282}, // 190 ComputeDerivativeGroupQuadsKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11454, 30), 282}, // 191 ComputeDerivativeGroupQuadsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11253, 16), 268}, // 192 ConstantDataKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13268, 30), 330}, // 193 CooperativeMatrixBlockLoadsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10962, 32), 250}, // 194 CooperativeMatrixConversionQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13161, 31), 327}, // 195 CooperativeMatrixConversionsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13345, 32), 334}, // 196 CooperativeMatrixDecodeVectorNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10241, 21), 382}, // 197 CooperativeMatrixKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10176, 28), 213}, // 198 CooperativeMatrixLayoutsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12661, 20), 305}, // 199 CooperativeMatrixNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13192, 40), 328}, // 200 CooperativeMatrixPerElementOperationsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13131, 30), 326}, // 201 CooperativeMatrixReductionsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13232, 36), 329}, // 202 CooperativeMatrixTensorAddressingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13014, 20), 317}, // 203 CooperativeVectorNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13298, 28), 331}, // 204 CooperativeVectorTrainingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6639, 16), 205}, // 205 CoreBuiltinsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5905, 13), 166}, // 206 CullDistance in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15223, 21), 394}, // 207 DebugInfoModuleINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12784, 25), 310}, // 208 DemoteToHelperInvocation in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12809, 28), 310}, // 209 DemoteToHelperInvocationEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10732, 18), 237}, // 210 DenormFlushToZero in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10717, 15), 236}, // 211 DenormPreserve in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9653, 18), 184}, // 212 DerivativeControl in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7393, 18), 267}, // 213 DescriptorHeapEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9177, 14), 153}, // 214 DeviceEnqueue in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6999, 12), 227}, // 215 DeviceGroup in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12837, 23), 311}, // 216 DisplacementMicromapNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14965, 11), 380}, // 217 DotProduct in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16164, 27), 425}, // 218 DotProductBFloat16AccVALVE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16131, 33), 424}, // 219 DotProductFloat16AccFloat16VALVE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16098, 33), 423}, // 220 DotProductFloat16AccFloat32VALVE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16191, 32), 426}, // 221 DotProductFloat8AccFloat32VALVE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14859, 22), 378}, // 222 DotProductInput4x8Bit in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14881, 25), 378}, // 223 DotProductInput4x8BitKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14906, 28), 379}, // 224 DotProductInput4x8BitPacked in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14934, 31), 379}, // 225 DotProductInput4x8BitPackedKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14818, 19), 377}, // 226 DotProductInputAll in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14837, 22), 377}, // 227 DotProductInputAllKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14976, 14), 380}, // 228 DotProductKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6902, 15), 218}, // 229 DrawParameters in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13707, 16), 350}, // 230 ExpectAssumeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15070, 7), 387}, // 231 FMAKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13937, 20), 357}, // 232 FPFastMathModeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15510, 29), 403}, // 233 FPGAArgumentInterfacesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15539, 28), 403}, // 234 FPGAArgumentInterfacesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14501, 25), 370}, // 235 FPGABufferLocationALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14526, 24), 370}, // 236 FPGABufferLocationINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14269, 28), 365}, // 237 FPGAClusterAttributesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14297, 27), 365}, // 238 FPGAClusterAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15321, 30), 398}, // 239 FPGAClusterAttributesV2ALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15351, 29), 398}, // 240 FPGAClusterAttributesV2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14353, 21), 367}, // 241 FPGADSPControlALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14374, 20), 367}, // 242 FPGADSPControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14420, 41), 369}, // 243 FPGAInvocationPipeliningAttributesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14461, 40), 369}, // 244 FPGAInvocationPipeliningAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14194, 26), 363}, // 245 FPGAKernelAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15380, 28), 399}, // 246 FPGAKernelAttributesv2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15461, 25), 402}, // 247 FPGALatencyControlALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15486, 24), 402}, // 248 FPGALatencyControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14127, 23), 361}, // 249 FPGALoopControlsALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14150, 22), 361}, // 250 FPGALoopControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14220, 25), 364}, // 251 FPGAMemoryAccessesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14245, 24), 364}, // 252 FPGAMemoryAccessesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13884, 27), 356}, // 253 FPGAMemoryAttributesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13911, 26), 356}, // 254 FPGAMemoryAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14791, 14), 376}, // 255 FPGARegALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14805, 13), 376}, // 256 FPGARegINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15445, 16), 401}, // 257 FPMaxErrorINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9091, 8), 144}, // 258 Float16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9077, 14), 143}, // 259 Float16Buffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11017, 16), 252}, // 260 Float16ImageAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9099, 8), 145}, // 261 Float64 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10214, 27), 215}, // 262 Float8CooperativeMatrixEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10204, 10), 214}, // 263 Float8EXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15055, 15), 386}, // 264 FloatControls2 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13503, 23), 340}, // 265 FloatingPointModeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7792, 23), 281}, // 266 FragmentBarycentricKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11401, 22), 281}, // 267 FragmentBarycentricNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7881, 19), 283}, // 268 FragmentDensityEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7602, 24), 277}, // 269 FragmentFullyCoveredEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11055, 16), 254}, // 270 FragmentMaskAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12752, 32), 309}, // 271 FragmentShaderPixelInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12681, 33), 306}, // 272 FragmentShaderSampleInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12714, 38), 307}, // 273 FragmentShaderShadingRateInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6964, 23), 216}, // 274 FragmentShadingRateKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13858, 26), 355}, // 275 FunctionFloatControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13549, 22), 342}, // 276 FunctionPointersINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15898, 22), 414}, // 277 FunctionVariantsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9498, 15), 171}, // 278 GenericPointer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5950, 9), 137}, // 279 Geometry in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9248, 18), 158}, // 280 GeometryPointSize in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11329, 28), 272}, // 281 GeometryShaderPassthroughNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9711, 16), 187}, // 282 GeometryStreams in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15597, 36), 405}, // 283 GlobalVariableFPGADecorationsALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15633, 35), 405}, // 284 GlobalVariableFPGADecorationsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15567, 30), 404}, // 285 GlobalVariableHostAccessINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10167, 9), 212}, // 286 GraphARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6482, 16), 194}, // 287 GroupNonUniform in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9850, 26), 196}, // 288 GroupNonUniformArithmetic in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6737, 22), 197}, // 289 GroupNonUniformBallot in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9930, 25), 200}, // 290 GroupNonUniformClustered in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11498, 30), 284}, // 291 GroupNonUniformPartitionedEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11528, 29), 284}, // 292 GroupNonUniformPartitionedNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9955, 20), 201}, // 293 GroupNonUniformQuad in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15030, 25), 385}, // 294 GroupNonUniformRotateKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9876, 23), 198}, // 295 GroupNonUniformShuffle in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9899, 31), 199}, // 296 GroupNonUniformShuffleRelative in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9830, 20), 195}, // 297 GroupNonUniformVote in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15961, 26), 417}, // 298 GroupUniformArithmeticKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9170, 7), 152}, // 299 Groups in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14725, 14), 374}, // 300 IOPipesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14739, 13), 374}, // 301 IOPipesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9567, 8), 177}, // 302 Image1D in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9126, 11), 148}, // 303 ImageBasic in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9589, 12), 180}, // 304 ImageBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9444, 15), 167}, // 305 ImageCubeArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11384, 17), 279}, // 306 ImageFootprintNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11033, 22), 253}, // 307 ImageGatherBiasLodAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9266, 20), 159}, // 308 ImageGatherExtended in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9601, 13), 181}, // 309 ImageMSArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9152, 12), 150}, // 310 ImageMipmap in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9642, 11), 183}, // 311 ImageQuery in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9137, 15), 149}, // 312 ImageReadWrite in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11071, 21), 256}, // 313 ImageReadWriteLodAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9476, 10), 169}, // 314 ImageRect in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13571, 24), 343}, // 315 IndirectReferencesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9518, 16), 173}, // 316 InputAttachment in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11643, 36), 287}, // 317 InputAttachmentArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11679, 39), 287}, // 318 InputAttachmentArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12184, 39), 294}, // 319 InputAttachmentArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12223, 42), 294}, // 320 InputAttachmentArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9220, 6), 156}, // 321 Int16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11150, 27), 262}, // 322 Int4CooperativeMatrixINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11136, 14), 261}, // 323 Int4TypeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9107, 6), 146}, // 324 Int64 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9113, 13), 147}, // 325 Int64Atomics in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11092, 14), 257}, // 326 Int64ImageEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9513, 5), 172}, // 327 Int8 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13526, 23), 341}, // 328 IntegerFunctions2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9671, 22), 185}, // 329 InterpolationFunction in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5717, 7), 141}, // 330 Kernel in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14172, 22), 362}, // 331 KernelAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9060, 8), 140}, // 332 Linkage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9191, 15), 154}, // 333 LiteralSampler in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15159, 20), 391}, // 334 LongCompositesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13094, 14), 324}, // 335 LongVectorEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14324, 15), 366}, // 336 LoopFuseALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14339, 14), 366}, // 337 LoopFuseINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16014, 25), 419}, // 338 MaskedGatherScatterINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9053, 7), 135}, // 339 Matrix in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14394, 26), 368}, // 340 MemoryAccessAliasingINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6013, 15), 280}, // 341 MeshShadingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5999, 14), 278}, // 342 MeshShadingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9550, 7), 175}, // 343 MinLod in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7021, 10), 228}, // 344 MultiView in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6101, 14), 190}, // 345 MultiViewport in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9805, 13), 192}, // 346 NamedBarrier in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15179, 11), 392}, // 347 OptNoneEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15190, 13), 392}, // 348 OptNoneINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7544, 20), 276}, // 349 PerViewAttributesNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5835, 31), 302}, // 350 PhysicalStorageBufferAddresses in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12539, 34), 302}, // 351 PhysicalStorageBufferAddressesEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9818, 12), 193}, // 352 PipeStorage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9164, 6), 151}, // 353 Pipes in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11269, 16), 269}, // 354 PoisonFreezeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15920, 18), 415}, // 355 PredicatedIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13074, 20), 323}, // 356 PushConstantBanksNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11121, 15), 260}, // 357 QuadControlKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13056, 18), 320}, // 358 RawAccessChainsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9038, 15), 381}, // 359 RayCullMaskKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10830, 12), 242}, // 360 RayQueryKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12989, 25), 316}, // 361 RayQueryPositionFetchKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10807, 23), 241}, // 362 RayQueryProvisionalKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8985, 41), 332}, // 363 RayTracingClusterAccelerationStructureNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8557, 33), 319}, // 364 RayTracingDisplacementMicromapNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5985, 14), 245}, // 365 RayTracingKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8739, 39), 322}, // 366 RayTracingLinearSweptSpheresGeometryNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8443, 23), 299}, // 367 RayTracingMotionBlurNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5972, 13), 298}, // 368 RayTracingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12889, 29), 312}, // 369 RayTracingOpacityMicromapEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15077, 42), 388}, // 370 RayTracingOpacityMicromapExecutionModeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12860, 29), 312}, // 371 RayTracingOpacityMicromapKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8496, 27), 297}, // 372 RayTracingPositionFetchKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12636, 25), 304}, // 373 RayTracingProvisionalKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8700, 28), 321}, // 374 RayTracingSpheresGeometryNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10861, 32), 244}, // 375 RayTraversalPrimitiveCullingKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16058, 20), 421}, // 376 RegisterLimitsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14990, 24), 383}, // 377 ReplicatedCompositesEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13482, 21), 339}, // 378 RoundToInfinityINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15938, 23), 416}, // 379 RoundedDivideSqrtINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10775, 16), 239}, // 380 RoundingModeRTE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10791, 16), 240}, // 381 RoundingModeRTZ in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14666, 30), 373}, // 382 RuntimeAlignedAttributeALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14696, 29), 373}, // 383 RuntimeAlignedAttributeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11594, 23), 286}, // 384 RuntimeDescriptorArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11617, 26), 286}, // 385 RuntimeDescriptorArrayEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11300, 29), 271}, // 386 SampleMaskOverrideCoverageNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10610, 28), 232}, // 387 SampleMaskPostDepthCoverage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6231, 18), 168}, // 388 SampleRateShading in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9557, 10), 176}, // 389 Sampled1D in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9575, 14), 179}, // 390 SampledBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9459, 17), 178}, // 391 SampledCubeArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9344, 33), 162}, // 392 SampledImageArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11957, 36), 291}, // 393 SampledImageArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11993, 39), 291}, // 394 SampledImageArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9486, 12), 170}, // 395 SampledRect in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5875, 7), 136}, // 396 Shader in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13108, 23), 325}, // 397 Shader64BitIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11106, 15), 258}, // 398 ShaderClockKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7344, 18), 259}, // 399 ShaderEnqueueAMDX in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12944, 27), 314}, // 400 ShaderInvocationReorderEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12918, 26), 313}, // 401 ShaderInvocationReorderNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6047, 12), 202}, // 402 ShaderLayer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11557, 17), 285}, // 403 ShaderNonUniform in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11574, 20), 285}, // 404 ShaderNonUniformEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8811, 19), 308}, // 405 ShaderSMBuiltinsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7483, 19), 275}, // 406 ShaderStereoViewNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6115, 20), 203}, // 407 ShaderViewportIndex in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6059, 28), 273}, // 408 ShaderViewportIndexLayerEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11357, 27), 273}, // 409 ShaderViewportIndexLayerNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7442, 21), 274}, // 410 ShaderViewportMaskNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11484, 14), 283}, // 411 ShadingRateNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10750, 25), 238}, // 412 SignedZeroInfNanPreserve in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9534, 16), 174}, // 413 SparseResidency in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15877, 21), 413}, // 414 SpecConditionalINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15268, 16), 396}, // 415 SplitBarrierEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15284, 18), 396}, // 416 SplitBarrierINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7298, 17), 255}, // 417 StencilExportEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10398, 25), 223}, // 418 StorageBuffer16BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10638, 24), 233}, // 419 StorageBuffer8BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9377, 34), 163}, // 420 StorageBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12032, 37), 292}, // 421 StorageBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12069, 40), 292}, // 422 StorageBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9411, 33), 164}, // 423 StorageImageArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12109, 36), 293}, // 424 StorageImageArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12145, 39), 293}, // 425 StorageImageArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9614, 28), 182}, // 426 StorageImageExtendedFormats in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9286, 24), 160}, // 427 StorageImageMultisample in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9727, 30), 188}, // 428 StorageImageReadWithoutFormat in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9757, 31), 189}, // 429 StorageImageWriteWithoutFormat in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10525, 21), 226}, // 430 StorageInputOutput16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10503, 22), 225}, // 431 StoragePushConstant16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10696, 21), 235}, // 432 StoragePushConstant8 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10090, 37), 210}, // 433 StorageTensorArrayDynamicIndexingARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10127, 40), 211}, // 434 StorageTensorArrayNonUniformIndexingARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11799, 39), 289}, // 435 StorageTexelBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11838, 42), 289}, // 436 StorageTexelBufferArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12352, 42), 296}, // 437 StorageTexelBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12394, 45), 296}, // 438 StorageTexelBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10486, 17), 224}, // 439 StorageUniform16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10423, 28), 223}, // 440 StorageUniformBufferBlock16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15696, 23), 407}, // 441 Subgroup2DBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15719, 30), 408}, // 442 Subgroup2DBlockTransformINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15749, 30), 409}, // 443 Subgroup2DBlockTransposeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13794, 39), 353}, // 444 SubgroupAvcMotionEstimationChromaINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13723, 33), 351}, // 445 SubgroupAvcMotionEstimationINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13756, 38), 352}, // 446 SubgroupAvcMotionEstimationIntraINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6498, 18), 217}, // 447 SubgroupBallotKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13398, 27), 336}, // 448 SubgroupBufferBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15668, 28), 406}, // 449 SubgroupBufferPrefetchINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9788, 17), 191}, // 450 SubgroupDispatch in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13425, 26), 337}, // 451 SubgroupImageBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13451, 31), 338}, // 452 SubgroupImageMediaBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15779, 38), 410}, // 453 SubgroupMatrixMultiplyAccumulateINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13377, 21), 335}, // 454 SubgroupShuffleINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10382, 16), 222}, // 455 SubgroupVoteKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15408, 19), 400}, // 456 TaskSequenceALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15427, 18), 400}, // 457 TaskSequenceINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13326, 19), 333}, // 458 TensorAddressingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15987, 27), 418}, // 459 TensorFloat32RoundingINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10079, 11), 209}, // 460 TensorsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15817, 28), 411}, // 461 TernaryBitwiseFunctionINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5959, 13), 138}, // 462 Tessellation in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9226, 22), 157}, // 463 TessellationPointSize in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10994, 23), 251}, // 464 TextureBlockMatch2QCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10940, 22), 248}, // 465 TextureBlockMatchQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10919, 21), 247}, // 466 TextureBoxFilterQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10893, 26), 246}, // 467 TextureSampleWeightedQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9993, 28), 206}, // 468 TileImageColorReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10021, 28), 207}, // 469 TileImageDepthReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10049, 30), 208}, // 470 TileImageStencilReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7061, 16), 249}, // 471 TileShadingQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9693, 18), 186}, // 472 TransformFeedback in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14619, 24), 372}, // 473 USMStorageClassesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14643, 23), 372}, // 474 USMStorageClassesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10451, 35), 224}, // 475 UniformAndStorageBuffer16BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10662, 34), 234}, // 476 UniformAndStorageBuffer8BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9310, 34), 161}, // 477 UniformBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11880, 37), 290}, // 478 UniformBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11917, 40), 290}, // 479 UniformBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9975, 18), 204}, // 480 UniformDecoration in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11718, 39), 288}, // 481 UniformTexelBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11757, 42), 288}, // 482 UniformTexelBufferArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12265, 42), 295}, // 483 UniformTexelBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12307, 45), 295}, // 484 UniformTexelBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14097, 30), 360}, // 485 UnstructuredLoopControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10842, 19), 243}, // 486 UntypedPointersKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15845, 32), 412}, // 487 UntypedVariableLengthArrayINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13833, 25), 354}, // 488 VariableLengthArrayINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10576, 17), 230}, // 489 VariablePointers in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10546, 30), 229}, // 490 VariablePointersStorageBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9068, 9), 142}, // 491 Vector16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13692, 15), 349}, // 492 VectorAnyINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13673, 19), 348}, // 493 VectorComputeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12439, 18), 300}, // 494 VulkanMemoryModel in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12478, 29), 301}, // 495 VulkanMemoryModelDeviceScope in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12507, 32), 301}, // 496 VulkanMemoryModelDeviceScopeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12457, 21), 300}, // 497 VulkanMemoryModelKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11285, 15), 270}, // 498 WeakLinkageAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10338, 44), 221}, // 499 WorkgroupMemoryExplicitLayout16BitAccessKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10295, 43), 220}, // 500 WorkgroupMemoryExplicitLayout8BitAccessKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10262, 33), 219}, // 501 WorkgroupMemoryExplicitLayoutKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(16235, 8), 428}, // 502 Address in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16243, 8), 429}, // 503 Boolean in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16251, 6), 430}, // 504 Float in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16257, 7), 431}, // 505 Signed in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16264, 11), 432}, // 506 SignedChar in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16275, 9), 433}, // 507 Unsigned in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16284, 13), 434}, // 508 UnsignedChar in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16223, 12), 427}, // 509 Unspecified in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16297, 6), 435}, // 510 Class in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(16303, 10), 436}, // 511 Structure in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(16313, 6), 437}, // 512 Union in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(16334, 20), 439}, // 513 ImportedDeclaration in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(16319, 15), 438}, // 514 ImportedModule in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(16443, 15), 447}, // 515 FlagArtificial in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16458, 13), 448}, // 516 FlagExplicit in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16431, 12), 446}, // 517 FlagFwdDecl in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16521, 21), 452}, // 518 FlagIndirectVariable in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16414, 17), 445}, // 519 FlagIsDefinition in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16598, 16), 456}, // 520 FlagIsEnumClass in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16402, 12), 444}, // 521 FlagIsLocal in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16582, 16), 455}, // 522 FlagIsOptimized in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16375, 14), 442}, // 523 FlagIsPrivate in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16359, 16), 441}, // 524 FlagIsProtected in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16389, 13), 443}, // 525 FlagIsPublic in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16542, 20), 453}, // 526 FlagLValueReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16486, 18), 450}, // 527 FlagObjectPointer in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16471, 15), 449}, // 528 FlagPrototyped in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16562, 20), 454}, // 529 FlagRValueReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16504, 17), 451}, // 530 FlagStaticMember in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16634, 24), 458}, // 531 FlagTypePassByReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16614, 20), 457}, // 532 FlagTypePassByValue in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16354, 5), 440}, // 533 None in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16719, 9), 463}, // 534 BitPiece in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16751, 7), 467}, // 535 Constu in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16658, 6), 459}, // 536 Deref in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16758, 9), 468}, // 537 Fragment in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16669, 6), 461}, // 538 Minus in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16664, 5), 460}, // 539 Plus in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16708, 11), 462}, // 540 PlusUconst in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16740, 11), 466}, // 541 StackValue in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16728, 5), 464}, // 542 Swap in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16733, 7), 465}, // 543 Xderef in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16803, 11), 472}, // 544 AtomicType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16767, 10), 469}, // 545 ConstType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16790, 13), 471}, // 546 RestrictType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16777, 13), 470}, // 547 VolatileType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16814, 10), 473}, // 548 Float16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16824, 10), 474}, // 549 Float32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16834, 10), 475}, // 550 Float64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(17002, 12), 486}, // 551 FloatE4M3NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(17014, 12), 487}, // 552 FloatE5M2NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16857, 14), 477}, // 553 SignedInt16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16871, 14), 478}, // 554 SignedInt32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16885, 14), 479}, // 555 SignedInt64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16844, 13), 476}, // 556 SignedInt8NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16962, 19), 484}, // 557 SignedInt8PackedNV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16914, 16), 481}, // 558 UnsignedInt16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16930, 16), 482}, // 559 UnsignedInt32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16946, 16), 483}, // 560 UnsignedInt64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16899, 15), 480}, // 561 UnsignedInt8NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16981, 21), 485}, // 562 UnsignedInt8PackedNV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(17078, 28), 491}, // 563 ColumnBlockedInterleavedARM in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(17038, 15), 489}, // 564 ColumnMajorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(17053, 25), 490}, // 565 RowBlockedInterleavedARM in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(17026, 12), 488}, // 566 RowMajorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(17114, 27), 493}, // 567 MatrixASignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(17141, 27), 494}, // 568 MatrixBSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(17168, 27), 495}, // 569 MatrixCSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(17195, 32), 496}, // 570 MatrixResultSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(17106, 8), 492}, // 571 NoneKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(17227, 26), 497}, // 572 SaturatingAccumulationKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(17264, 4), 500}, // 573 2x2 in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(17257, 7), 499}, // 574 Column in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(17253, 4), 498}, // 575 Row in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(17268, 11), 501}, // 576 MatrixAKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(17290, 21), 503}, // 577 MatrixAccumulatorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(17279, 11), 502}, // 578 MatrixBKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(17322, 14), 505}, // 579 ColumnMajorNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(17336, 21), 506}, // 580 InferencingOptimalNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(17311, 11), 504}, // 581 RowMajorNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(17357, 18), 507}, // 582 TrainingOptimalNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(16235, 8), 509}, // 583 Address in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16243, 8), 510}, // 584 Boolean in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16251, 6), 511}, // 585 Float in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16257, 7), 512}, // 586 Signed in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16264, 11), 513}, // 587 SignedChar in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16275, 9), 514}, // 588 Unsigned in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16284, 13), 515}, // 589 UnsignedChar in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16223, 12), 508}, // 590 Unspecified in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16297, 6), 516}, // 591 Class in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(16303, 10), 517}, // 592 Structure in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(16313, 6), 518}, // 593 Union in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(16443, 15), 526}, // 594 FlagArtificial in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16458, 13), 527}, // 595 FlagExplicit in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16431, 12), 525}, // 596 FlagFwdDecl in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16521, 21), 531}, // 597 FlagIndirectVariable in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16414, 17), 524}, // 598 FlagIsDefinition in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16402, 12), 523}, // 599 FlagIsLocal in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16582, 16), 534}, // 600 FlagIsOptimized in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16375, 14), 521}, // 601 FlagIsPrivate in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16359, 16), 520}, // 602 FlagIsProtected in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16389, 13), 522}, // 603 FlagIsPublic in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16542, 20), 532}, // 604 FlagLValueReference in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16486, 18), 529}, // 605 FlagObjectPointer in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16471, 15), 528}, // 606 FlagPrototyped in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16562, 20), 533}, // 607 FlagRValueReference in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16504, 17), 530}, // 608 FlagStaticMember in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16354, 5), 519}, // 609 None in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16719, 9), 539}, // 610 BitPiece in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16751, 7), 543}, // 611 Constu in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16658, 6), 535}, // 612 Deref in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16669, 6), 537}, // 613 Minus in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16664, 5), 536}, // 614 Plus in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16708, 11), 538}, // 615 PlusUconst in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16740, 11), 542}, // 616 StackValue in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16728, 5), 540}, // 617 Swap in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16733, 7), 541}, // 618 Xderef in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16767, 10), 544}, // 619 ConstType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(16790, 13), 546}, // 620 RestrictType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(16777, 13), 545}, // 621 VolatileType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(20095, 16), 667}, // 622 AliasScopeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17584, 8), 566}, // 623 Aliased in SPV_OPERAND_TYPE_DECORATION
  {IR(18745, 15), 622}, // 624 AliasedPointer in SPV_OPERAND_TYPE_DECORATION
  {IR(18760, 18), 622}, // 625 AliasedPointerEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(18062, 10), 590}, // 626 Alignment in SPV_OPERAND_TYPE_DECORATION
  {IR(18106, 12), 592}, // 627 AlignmentId in SPV_OPERAND_TYPE_DECORATION
  {IR(17435, 12), 553}, // 628 ArrayStride in SPV_OPERAND_TYPE_DECORATION
  {IR(18486, 17), 609}, // 629 ArrayStrideIdEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(19645, 15), 655}, // 630 BankBitsALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19660, 14), 655}, // 631 BankBitsINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18854, 7), 626}, // 632 BankNV in SPV_OPERAND_TYPE_DECORATION
  {IR(19358, 16), 648}, // 633 BankwidthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19374, 15), 648}, // 634 BankwidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17739, 8), 579}, // 635 Binding in SPV_OPERAND_TYPE_DECORATION
  {IR(18879, 16), 628}, // 636 BindlessImageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18861, 18), 627}, // 637 BindlessSamplerNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17399, 6), 549}, // 638 Block in SPV_OPERAND_TYPE_DECORATION
  {IR(18246, 22), 599}, // 639 BlockMatchSamplerQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(18224, 22), 598}, // 640 BlockMatchTextureQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(18910, 13), 630}, // 641 BoundImageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18895, 15), 629}, // 642 BoundSamplerNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17405, 12), 550}, // 643 BufferBlock in SPV_OPERAND_TYPE_DECORATION
  {IR(20255, 21), 672}, // 644 BufferLocationALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20276, 20), 672}, // 645 BufferLocationINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17516, 8), 558}, // 646 BuiltIn in SPV_OPERAND_TYPE_DECORATION
  {IR(19814, 20), 660}, // 647 BurstCoalesceALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19834, 19), 660}, // 648 BurstCoalesceINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17482, 8), 557}, // 649 CPacked in SPV_OPERAND_TYPE_DECORATION
  {IR(21502, 22), 695}, // 650 CacheControlLoadINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(21561, 23), 696}, // 651 CacheControlStoreINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19853, 16), 661}, // 652 CacheSizeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19869, 15), 661}, // 653 CacheSizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17549, 9), 562}, // 654 Centroid in SPV_OPERAND_TYPE_DECORATION
  {IR(18963, 13), 633}, // 655 ClobberINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17610, 9), 569}, // 656 Coherent in SPV_OPERAND_TYPE_DECORATION
  {IR(17426, 9), 552}, // 657 ColMajor in SPV_OPERAND_TYPE_DECORATION
  {IR(17723, 10), 577}, // 658 Component in SPV_OPERAND_TYPE_DECORATION
  {IR(21449, 17), 694}, // 659 ConditionalINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20678, 28), 682}, // 660 ConduitKernelArgumentALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20706, 27), 682}, // 661 ConduitKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17601, 9), 568}, // 662 Constant in SPV_OPERAND_TYPE_DECORATION
  {IR(19109, 14), 640}, // 663 CounterBuffer in SPV_OPERAND_TYPE_DECORATION
  {IR(17747, 14), 580}, // 664 DescriptorSet in SPV_OPERAND_TYPE_DECORATION
  {IR(19884, 29), 662}, // 665 DontStaticallyCoalesceALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19913, 28), 662}, // 666 DontStaticallyCoalesceINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19467, 17), 651}, // 667 DoublepumpALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19484, 16), 651}, // 668 DoublepumpINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18268, 18), 600}, // 669 ExplicitInterpAMD in SPV_OPERAND_TYPE_DECORATION
  {IR(17932, 15), 586}, // 670 FPFastMathMode in SPV_OPERAND_TYPE_DECORATION
  {IR(20540, 26), 679}, // 671 FPMaxErrorDecorationINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17882, 15), 585}, // 672 FPRoundingMode in SPV_OPERAND_TYPE_DECORATION
  {IR(17538, 5), 560}, // 673 Flat in SPV_OPERAND_TYPE_DECORATION
  {IR(19674, 21), 656}, // 674 ForcePow2DepthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19695, 20), 656}, // 675 ForcePow2DepthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17834, 14), 584}, // 676 FuncParamAttr in SPV_OPERAND_TYPE_DECORATION
  {IR(19020, 21), 636}, // 677 FuncParamIOKindINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19251, 24), 644}, // 678 FunctionDenormModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20369, 31), 674}, // 679 FunctionFloatingPointModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19194, 26), 643}, // 680 FunctionRoundingModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20005, 26), 665}, // 681 FuseLoopsInFunctionALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20031, 25), 665}, // 682 FuseLoopsInFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17471, 11), 556}, // 683 GLSLPacked in SPV_OPERAND_TYPE_DECORATION
  {IR(17460, 11), 555}, // 684 GLSLShared in SPV_OPERAND_TYPE_DECORATION
  {IR(19083, 26), 639}, // 685 GlobalVariableOffsetINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18823, 31), 625}, // 686 HitObjectShaderRecordBufferEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(18793, 30), 624}, // 687 HitObjectShaderRecordBufferNV in SPV_OPERAND_TYPE_DECORATION
  {IR(19123, 24), 640}, // 688 HlslCounterBufferGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(19160, 19), 641}, // 689 HlslSemanticGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(21300, 16), 691}, // 690 HostAccessINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20296, 20), 673}, // 691 IOPipeStorageALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20316, 19), 673}, // 692 IOPipeStorageINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(21392, 29), 693}, // 693 ImplementInRegisterMapALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(21421, 28), 693}, // 694 ImplementInRegisterMapINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17733, 6), 578}, // 695 Index in SPV_OPERAND_TYPE_DECORATION
  {IR(21363, 15), 692}, // 696 InitModeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(21378, 14), 692}, // 697 InitModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20124, 25), 669}, // 698 InitiationIntervalALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20149, 24), 669}, // 699 InitiationIntervalINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18041, 21), 589}, // 700 InputAttachmentIndex in SPV_OPERAND_TYPE_DECORATION
  {IR(17565, 10), 564}, // 701 Invariant in SPV_OPERAND_TYPE_DECORATION
  {IR(20617, 31), 681}, // 702 LatencyControlConstraintALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20648, 30), 681}, // 703 LatencyControlConstraintINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20566, 26), 680}, // 704 LatencyControlLabelALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20592, 25), 680}, // 705 LatencyControlLabelINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18009, 18), 587}, // 706 LinkageAttributes in SPV_OPERAND_TYPE_DECORATION
  {IR(17714, 9), 576}, // 707 Location in SPV_OPERAND_TYPE_DECORATION
  {IR(20796, 34), 684}, // 708 MMHostInterfaceAddressWidthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20830, 33), 684}, // 709 MMHostInterfaceAddressWidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20863, 31), 685}, // 710 MMHostInterfaceDataWidthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20894, 30), 685}, // 711 MMHostInterfaceDataWidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20924, 29), 686}, // 712 MMHostInterfaceLatencyALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20953, 28), 686}, // 713 MMHostInterfaceLatencyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(21084, 30), 688}, // 714 MMHostInterfaceMaxBurstALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(21114, 29), 688}, // 715 MMHostInterfaceMaxBurstINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(21015, 35), 687}, // 716 MMHostInterfaceReadWriteModeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(21050, 34), 687}, // 717 MMHostInterfaceReadWriteModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(21143, 33), 689}, // 718 MMHostInterfaceWaitRequestALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(21176, 32), 689}, // 719 MMHostInterfaceWaitRequestINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20056, 20), 666}, // 720 MathOpDSPModeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20076, 19), 666}, // 721 MathOpDSPModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17447, 13), 554}, // 722 MatrixStride in SPV_OPERAND_TYPE_DECORATION
  {IR(18072, 14), 591}, // 723 MaxByteOffset in SPV_OPERAND_TYPE_DECORATION
  {IR(18118, 16), 593}, // 724 MaxByteOffsetId in SPV_OPERAND_TYPE_DECORATION
  {IR(20173, 21), 670}, // 725 MaxConcurrencyALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20194, 20), 670}, // 726 MaxConcurrencyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19389, 23), 649}, // 727 MaxPrivateCopiesALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19412, 22), 649}, // 728 MaxPrivateCopiesINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19500, 20), 652}, // 729 MaxReplicatesALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19520, 19), 652}, // 730 MaxReplicatesINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20460, 18), 677}, // 731 MediaBlockIOINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18778, 15), 623}, // 732 MemberOffsetNV in SPV_OPERAND_TYPE_DECORATION
  {IR(19304, 13), 646}, // 733 MemoryALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19317, 12), 646}, // 734 MemoryINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19580, 12), 654}, // 735 MergeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19592, 11), 654}, // 736 MergeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20111, 13), 668}, // 737 NoAliasINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18027, 14), 588}, // 738 NoContraction in SPV_OPERAND_TYPE_DECORATION
  {IR(17524, 14), 559}, // 739 NoPerspective in SPV_OPERAND_TYPE_DECORATION
  {IR(18178, 13), 595}, // 740 NoSignedWrap in SPV_OPERAND_TYPE_DECORATION
  {IR(18191, 15), 596}, // 741 NoUnsignedWrap in SPV_OPERAND_TYPE_DECORATION
  {IR(18318, 20), 602}, // 742 NodeMaxPayloadsAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(18286, 32), 601}, // 743 NodeSharesPayloadLimitsWithAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17631, 12), 571}, // 744 NonReadable in SPV_OPERAND_TYPE_DECORATION
  {IR(18685, 11), 620}, // 745 NonUniform in SPV_OPERAND_TYPE_DECORATION
  {IR(18696, 14), 620}, // 746 NonUniformEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(17619, 12), 570}, // 747 NonWritable in SPV_OPERAND_TYPE_DECORATION
  {IR(19329, 15), 647}, // 748 NumbanksALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19344, 14), 647}, // 749 NumbanksINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17761, 7), 581}, // 750 Offset in SPV_OPERAND_TYPE_DECORATION
  {IR(18503, 12), 610}, // 751 OffsetIdEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(18529, 19), 612}, // 752 OverrideCoverageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18548, 14), 613}, // 753 PassthroughNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17543, 6), 561}, // 754 Patch in SPV_OPERAND_TYPE_DECORATION
  {IR(18458, 28), 608}, // 755 PayloadDispatchIndirectAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(18433, 25), 607}, // 756 PayloadNodeArraySizeAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(18381, 25), 605}, // 757 PayloadNodeBaseIndexAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(18361, 20), 604}, // 758 PayloadNodeNameAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(18406, 27), 606}, // 759 PayloadNodeSparseArrayAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(18609, 16), 616}, // 760 PerPrimitiveEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(18625, 15), 616}, // 761 PerPrimitiveNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18650, 10), 618}, // 762 PerTaskNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18660, 13), 619}, // 763 PerVertexKHR in SPV_OPERAND_TYPE_DECORATION
  {IR(18673, 12), 619}, // 764 PerVertexNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18640, 10), 617}, // 765 PerViewNV in SPV_OPERAND_TYPE_DECORATION
  {IR(20214, 21), 671}, // 766 PipelineEnableALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20235, 20), 671}, // 767 PipelineEnableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19941, 15), 663}, // 768 PrefetchALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19956, 14), 663}, // 769 PrefetchINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18937, 26), 632}, // 770 ReferencedIndirectlyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19275, 15), 645}, // 771 RegisterALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19290, 14), 645}, // 772 RegisterINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20733, 32), 683}, // 773 RegisterMapKernelArgumentALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20765, 31), 683}, // 774 RegisterMapKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17375, 17), 547}, // 775 RelaxedPrecision in SPV_OPERAND_TYPE_DECORATION
  {IR(17575, 9), 565}, // 776 Restrict in SPV_OPERAND_TYPE_DECORATION
  {IR(18710, 16), 621}, // 777 RestrictPointer in SPV_OPERAND_TYPE_DECORATION
  {IR(18726, 19), 621}, // 778 RestrictPointerEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(17417, 9), 551}, // 779 RowMajor in SPV_OPERAND_TYPE_DECORATION
  {IR(18923, 14), 631}, // 780 SIMTCallINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17558, 7), 563}, // 781 Sample in SPV_OPERAND_TYPE_DECORATION
  {IR(17687, 20), 574}, // 782 SaturatedConversion in SPV_OPERAND_TYPE_DECORATION
  {IR(18134, 44), 594}, // 783 SaturatedToLargestFloat8NormalConversionEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(18581, 28), 615}, // 784 SecondaryViewportRelativeNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18976, 17), 634}, // 785 SideEffectsINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19539, 21), 653}, // 786 SimpleDualPortALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19560, 20), 653}, // 787 SimpleDualPortINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20400, 25), 675}, // 788 SingleElementVectorINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19434, 17), 650}, // 789 SinglepumpALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19451, 16), 650}, // 790 SinglepumpINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17392, 7), 548}, // 791 SpecId in SPV_OPERAND_TYPE_DECORATION
  {IR(21208, 27), 690}, // 792 StableKernelArgumentALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(21235, 26), 690}, // 793 StableKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19068, 15), 638}, // 794 StackCallINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19970, 18), 664}, // 795 StallEnableALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19988, 17), 664}, // 796 StallEnableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20478, 16), 678}, // 797 StallFreeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20494, 15), 678}, // 798 StallFreeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17707, 7), 575}, // 799 Stream in SPV_OPERAND_TYPE_DECORATION
  {IR(19715, 17), 657}, // 800 StridesizeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19732, 16), 657}, // 801 StridesizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18338, 23), 603}, // 802 TrackFinishWritingAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(19777, 19), 659}, // 803 TrueDualPortALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19796, 18), 659}, // 804 TrueDualPortINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18515, 14), 611}, // 805 UTFEncodedKHR in SPV_OPERAND_TYPE_DECORATION
  {IR(17643, 8), 572}, // 806 Uniform in SPV_OPERAND_TYPE_DECORATION
  {IR(17677, 10), 573}, // 807 UniformId in SPV_OPERAND_TYPE_DECORATION
  {IR(19147, 13), 641}, // 808 UserSemantic in SPV_OPERAND_TYPE_DECORATION
  {IR(19179, 15), 642}, // 809 UserTypeGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(20425, 35), 676}, // 810 VectorComputeCallableFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19041, 27), 637}, // 811 VectorComputeFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18993, 27), 635}, // 812 VectorComputeVariableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18562, 19), 614}, // 813 ViewportRelativeNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17592, 9), 567}, // 814 Volatile in SPV_OPERAND_TYPE_DECORATION
  {IR(18206, 18), 597}, // 815 WeightTextureQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(19748, 15), 658}, // 816 WordsizeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19763, 14), 658}, // 817 WordsizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17768, 10), 582}, // 818 XfbBuffer in SPV_OPERAND_TYPE_DECORATION
  {IR(17778, 10), 583}, // 819 XfbStride in SPV_OPERAND_TYPE_DECORATION
  {IR(21584, 3), 697}, // 820 1D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21587, 3), 698}, // 821 2D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21590, 3), 699}, // 822 3D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21603, 7), 702}, // 823 Buffer in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21593, 5), 700}, // 824 Cube in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21598, 5), 701}, // 825 Rect in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21610, 12), 703}, // 826 SubpassData in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21622, 17), 704}, // 827 TileImageDataEXT in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(22740, 20), 772}, // 828 ArithmeticPoisonKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22434, 15), 757}, // 829 CoalescingAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22065, 15), 735}, // 830 ContractionOff in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10732, 18), 749}, // 831 DenormFlushToZero in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10717, 15), 748}, // 832 DenormPreserve in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21835, 13), 718}, // 833 DepthGreater in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21848, 10), 719}, // 834 DepthLess in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21820, 15), 717}, // 835 DepthReplacing in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21858, 15), 720}, // 836 DepthUnchanged in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22875, 25), 776}, // 837 DerivativeGroupLinearKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22900, 24), 776}, // 838 DerivativeGroupLinearNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22828, 24), 775}, // 839 DerivativeGroupQuadsKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22852, 23), 775}, // 840 DerivativeGroupQuadsNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22382, 29), 755}, // 841 EarlyAndLateFragmentTestsAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21787, 19), 714}, // 842 EarlyFragmentTests in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23385, 18), 796}, // 843 FPFastMathDefault in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22092, 10), 737}, // 844 Finalizer in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23200, 26), 788}, // 845 FloatingPointModeALTINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23226, 27), 789}, // 846 FloatingPointModeIEEEINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22080, 12), 736}, // 847 Initializer in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21909, 11), 724}, // 848 InputLines in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21920, 20), 725}, // 849 InputLinesAdjacency in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21897, 12), 723}, // 850 InputPoints in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21950, 24), 727}, // 851 InputTrianglesAdjacency in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21639, 12), 705}, // 852 Invocations in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22449, 15), 758}, // 853 IsApiEntryAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21980, 9), 729}, // 854 Isolines in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21873, 10), 721}, // 855 LocalSize in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21883, 14), 722}, // 856 LocalSizeHint in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22160, 16), 742}, // 857 LocalSizeHintId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22148, 12), 741}, // 858 LocalSizeId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22464, 21), 759}, // 859 MaxNodeRecursionAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22509, 21), 762}, // 860 MaxNumWorkgroupsAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23275, 16), 791}, // 861 MaxWorkDimINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23253, 22), 790}, // 862 MaxWorkgroupSizeINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23361, 24), 795}, // 863 MaximallyReconvergesKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23497, 22), 801}, // 864 MaximumRegistersINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23519, 24), 802}, // 865 MaximumRegistersIdINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23474, 23), 800}, // 866 NamedBarrierCountINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23594, 27), 803}, // 867 NamedMaximumRegistersINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23291, 20), 792}, // 868 NoGlobalOffsetINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22176, 34), 743}, // 869 NonCoherentColorAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22210, 34), 744}, // 870 NonCoherentDepthAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22244, 36), 745}, // 871 NonCoherentStencilAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22328, 34), 753}, // 872 NonCoherentTileAttachmentReadQCOM in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23311, 22), 793}, // 873 NumSIMDWorkitemsINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23403, 21), 797}, // 874 OpacityMicromapIdKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21771, 16), 713}, // 875 OriginLowerLeft in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21755, 16), 712}, // 876 OriginUpperLeft in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22017, 16), 732}, // 877 OutputLineStrip in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22760, 15), 773}, // 878 OutputLinesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22775, 14), 773}, // 879 OutputLinesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22004, 13), 731}, // 880 OutputPoints in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22789, 20), 774}, // 881 OutputPrimitivesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22809, 19), 774}, // 882 OutputPrimitivesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22033, 20), 733}, // 883 OutputTriangleStrip in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22924, 19), 777}, // 884 OutputTrianglesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22943, 18), 777}, // 885 OutputTrianglesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21989, 15), 730}, // 886 OutputVertices in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21736, 19), 711}, // 887 PixelCenterInteger in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22961, 25), 778}, // 888 PixelInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22986, 27), 779}, // 889 PixelInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21806, 10), 715}, // 890 PointMode in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22310, 18), 747}, // 891 PostDepthCoverage in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22681, 19), 769}, // 892 QuadDerivativesKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21974, 6), 728}, // 893 Quads in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23448, 26), 799}, // 894 RegisterMapInterfaceINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22700, 20), 770}, // 895 RequireFullQuadsKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10775, 16), 751}, // 896 RoundingModeRTE in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23179, 21), 787}, // 897 RoundingModeRTNINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23158, 21), 786}, // 898 RoundingModeRTPINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10791, 16), 752}, // 899 RoundingModeRTZ in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23013, 26), 780}, // 900 SampleInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23039, 28), 781}, // 901 SampleInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23333, 28), 794}, // 902 SchedulerTargetFmaxMhzINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(13108, 23), 784}, // 903 Shader64BitIndexingEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(7362, 16), 761}, // 904 ShaderIndexAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23067, 31), 782}, // 905 ShadingRateInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23098, 33), 783}, // 906 ShadingRateInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23131, 27), 785}, // 907 SharedLocalMemorySizeINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22720, 20), 771}, // 908 SharesInputWithAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10750, 25), 750}, // 909 SignedZeroInfNanPreserve in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21651, 13), 706}, // 910 SpacingEqual in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21664, 22), 707}, // 911 SpacingFractionalEven in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21686, 21), 708}, // 912 SpacingFractionalOdd in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22485, 24), 760}, // 913 StaticNumWorkgroupsAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22634, 25), 767}, // 914 StencilRefGreaterBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22558, 26), 764}, // 915 StencilRefGreaterFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22659, 22), 768}, // 916 StencilRefLessBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22584, 23), 765}, // 917 StencilRefLessFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22411, 23), 756}, // 918 StencilRefReplacingEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22607, 27), 766}, // 919 StencilRefUnchangedBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22530, 28), 763}, // 920 StencilRefUnchangedFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23424, 24), 798}, // 921 StreamingInterfaceINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(6469, 13), 738}, // 922 SubgroupSize in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22280, 30), 746}, // 923 SubgroupUniformControlFlowKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22102, 22), 739}, // 924 SubgroupsPerWorkgroup in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22124, 24), 740}, // 925 SubgroupsPerWorkgroupId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22362, 20), 754}, // 926 TileShadingRateQCOM in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21940, 10), 726}, // 927 Triangles in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22053, 12), 734}, // 928 VecTypeHint in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21721, 15), 710}, // 929 VertexOrderCcw in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21707, 14), 709}, // 930 VertexOrderCw in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21816, 4), 716}, // 931 Xfb in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23759, 10), 815}, // 932 AnyHitKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23769, 9), 815}, // 933 AnyHitNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23820, 12), 818}, // 934 CallableKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23832, 11), 818}, // 935 CallableNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23778, 14), 816}, // 936 ClosestHitKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23792, 13), 816}, // 937 ClosestHitNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(16758, 9), 808}, // 938 Fragment in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23671, 10), 809}, // 939 GLCompute in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(5950, 9), 807}, // 940 Geometry in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23728, 16), 814}, // 941 IntersectionKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23744, 15), 814}, // 942 IntersectionNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(5717, 7), 810}, // 943 Kernel in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23851, 8), 820}, // 944 MeshEXT in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23688, 7), 812}, // 945 MeshNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23805, 8), 817}, // 946 MissKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23813, 7), 817}, // 947 MissNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23695, 17), 813}, // 948 RayGenerationKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23712, 16), 813}, // 949 RayGenerationNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23843, 8), 819}, // 950 TaskEXT in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23681, 7), 811}, // 951 TaskNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23628, 20), 805}, // 952 TessellationControl in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23648, 23), 806}, // 953 TessellationEvaluation in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23621, 7), 804}, // 954 Vertex in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23868, 12), 822}, // 955 FlushToZero in SPV_OPERAND_TYPE_FPDENORM_MODE
  {IR(23859, 9), 821}, // 956 Preserve in SPV_OPERAND_TYPE_FPDENORM_MODE
  {IR(23880, 12), 823}, // 957 BFloat16KHR in SPV_OPERAND_TYPE_FPENCODING
  {IR(23892, 14), 824}, // 958 Float8E4M3EXT in SPV_OPERAND_TYPE_FPENCODING
  {IR(23906, 14), 825}, // 959 Float8E5M2EXT in SPV_OPERAND_TYPE_FPENCODING
  {IR(23925, 4), 827}, // 960 ALT in SPV_OPERAND_TYPE_FPOPERATION_MODE
  {IR(23920, 5), 826}, // 961 IEEE in SPV_OPERAND_TYPE_FPOPERATION_MODE
  {IR(23963, 14), 834}, // 962 AllowContract in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23977, 23), 834}, // 963 AllowContractFastINTEL in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(24000, 13), 835}, // 964 AllowReassoc in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(24013, 18), 835}, // 965 AllowReassocINTEL in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23947, 11), 832}, // 966 AllowRecip in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(24031, 15), 836}, // 967 AllowTransform in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23958, 5), 833}, // 968 Fast in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23943, 4), 831}, // 969 NSZ in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(16354, 5), 828}, // 970 None in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23936, 7), 830}, // 971 NotInf in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23929, 7), 829}, // 972 NotNaN in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(24046, 4), 837}, // 973 RTE in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(24058, 4), 840}, // 974 RTN in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(24054, 4), 839}, // 975 RTP in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(24050, 4), 838}, // 976 RTZ in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(24094, 18), 843}, // 977 Horizontal2Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(24112, 18), 844}, // 978 Horizontal4Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(24062, 16), 841}, // 979 Vertical2Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(24078, 16), 842}, // 980 Vertical4Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(24153, 6), 849}, // 981 Const in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(24137, 11), 847}, // 982 DontInline in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(24130, 7), 846}, // 983 Inline in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(16354, 5), 845}, // 984 None in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(15179, 11), 850}, // 985 OptNoneEXT in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(15190, 13), 850}, // 986 OptNoneINTEL in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(24148, 5), 848}, // 987 Pure in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(24169, 6), 853}, // 988 ByVal in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(24180, 8), 855}, // 989 NoAlias in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(24188, 10), 856}, // 990 NoCapture in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(24206, 12), 858}, // 991 NoReadWrite in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(24198, 8), 857}, // 992 NoWrite in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(24218, 21), 859}, // 993 RuntimeAlignedALTERA in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(24239, 20), 859}, // 994 RuntimeAlignedINTEL in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(24164, 5), 852}, // 995 Sext in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(24175, 5), 854}, // 996 Sret in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(24159, 5), 851}, // 997 Zext in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(24294, 16), 863}, // 998 ClusteredReduce in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(24280, 14), 862}, // 999 ExclusiveScan in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(24266, 14), 861}, // 1000 InclusiveScan in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(24406, 28), 866}, // 1001 PartitionedExclusiveScanEXT in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(24434, 27), 866}, // 1002 PartitionedExclusiveScanNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(24351, 28), 865}, // 1003 PartitionedInclusiveScanEXT in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(24379, 27), 865}, // 1004 PartitionedInclusiveScanNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(24310, 21), 864}, // 1005 PartitionedReduceEXT in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(24331, 20), 864}, // 1006 PartitionedReduceNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(24259, 7), 860}, // 1007 Reduce in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(24461, 10), 867}, // 1008 NoneINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(24471, 10), 868}, // 1009 ReadINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(24492, 15), 870}, // 1010 ReadWriteINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(24481, 11), 869}, // 1011 WriteINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(24507, 5), 872}, // 1012 Bias in SPV_OPERAND_TYPE_IMAGE
  {IR(24521, 12), 875}, // 1013 ConstOffset in SPV_OPERAND_TYPE_IMAGE
  {IR(24533, 13), 877}, // 1014 ConstOffsets in SPV_OPERAND_TYPE_IMAGE
  {IR(24516, 5), 874}, // 1015 Grad in SPV_OPERAND_TYPE_IMAGE
  {IR(24512, 4), 873}, // 1016 Lod in SPV_OPERAND_TYPE_IMAGE
  {IR(24546, 19), 880}, // 1017 MakeTexelAvailable in SPV_OPERAND_TYPE_IMAGE
  {IR(24565, 22), 880}, // 1018 MakeTexelAvailableKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(24587, 17), 881}, // 1019 MakeTexelVisible in SPV_OPERAND_TYPE_IMAGE
  {IR(24604, 20), 881}, // 1020 MakeTexelVisibleKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(9550, 7), 879}, // 1021 MinLod in SPV_OPERAND_TYPE_IMAGE
  {IR(24624, 16), 882}, // 1022 NonPrivateTexel in SPV_OPERAND_TYPE_IMAGE
  {IR(24640, 19), 882}, // 1023 NonPrivateTexelKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(16354, 5), 871}, // 1024 None in SPV_OPERAND_TYPE_IMAGE
  {IR(24712, 12), 886}, // 1025 Nontemporal in SPV_OPERAND_TYPE_IMAGE
  {IR(17761, 7), 876}, // 1026 Offset in SPV_OPERAND_TYPE_IMAGE
  {IR(24724, 8), 887}, // 1027 Offsets in SPV_OPERAND_TYPE_IMAGE
  {IR(17558, 7), 878}, // 1028 Sample in SPV_OPERAND_TYPE_IMAGE
  {IR(24690, 11), 884}, // 1029 SignExtend in SPV_OPERAND_TYPE_IMAGE
  {IR(24659, 14), 883}, // 1030 VolatileTexel in SPV_OPERAND_TYPE_IMAGE
  {IR(24673, 17), 883}, // 1031 VolatileTexelKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(24701, 11), 885}, // 1032 ZeroExtend in SPV_OPERAND_TYPE_IMAGE
  {IR(16251, 6), 902}, // 1033 Float in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24893, 10), 901}, // 1034 HalfFloat in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24828, 12), 896}, // 1035 SignedInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24840, 12), 897}, // 1036 SignedInt32 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24817, 11), 895}, // 1037 SignedInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24742, 11), 889}, // 1038 SnormInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24732, 10), 888}, // 1039 SnormInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24802, 15), 894}, // 1040 UnormInt101010 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24914, 17), 904}, // 1041 UnormInt101010_2 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24931, 16), 905}, // 1042 UnormInt10X6EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25064, 16), 912}, // 1043 UnormInt12X4EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25080, 16), 913}, // 1044 UnormInt14X2EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24763, 11), 891}, // 1045 UnormInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24903, 11), 903}, // 1046 UnormInt24 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24987, 20), 908}, // 1047 UnormInt2_101010EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24753, 10), 890}, // 1048 UnormInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24788, 14), 893}, // 1049 UnormShort555 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24774, 14), 892}, // 1050 UnormShort565 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25007, 19), 909}, // 1051 UnsignedInt10X6EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25026, 19), 910}, // 1052 UnsignedInt12X4EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25045, 19), 911}, // 1053 UnsignedInt14X2EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24865, 14), 899}, // 1054 UnsignedInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24879, 14), 900}, // 1055 UnsignedInt32 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24852, 13), 898}, // 1056 UnsignedInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24947, 20), 906}, // 1057 UnsignedIntRaw10EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24967, 20), 907}, // 1058 UnsignedIntRaw12EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(25098, 2), 915}, // 1059 A in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25199, 5), 933}, // 1060 ABGR in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25120, 5), 921}, // 1061 ARGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25115, 5), 920}, // 1062 BGRA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25157, 6), 927}, // 1063 Depth in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25163, 13), 928}, // 1064 DepthStencil in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25125, 10), 922}, // 1065 Intensity in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25135, 10), 923}, // 1066 Luminance in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25096, 2), 914}, // 1067 R in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25103, 3), 917}, // 1068 RA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25100, 3), 916}, // 1069 RG in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25106, 4), 918}, // 1070 RGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25110, 5), 919}, // 1071 RGBA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25152, 5), 926}, // 1072 RGBx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25148, 4), 925}, // 1073 RGx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25145, 3), 924}, // 1074 Rx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25193, 6), 932}, // 1075 sBGRA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25176, 5), 929}, // 1076 sRGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25187, 6), 931}, // 1077 sRGBA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25181, 6), 930}, // 1078 sRGBx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(25204, 28), 934}, // 1079 InitOnDeviceReprogramALTERA in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(25232, 27), 934}, // 1080 InitOnDeviceReprogramINTEL in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(25259, 24), 935}, // 1081 InitOnDeviceResetALTERA in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(25283, 23), 935}, // 1082 InitOnDeviceResetINTEL in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(25306, 7), 936}, // 1083 NoWait in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(25313, 11), 937}, // 1084 WaitKernel in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(25324, 14), 938}, // 1085 WaitWorkGroup in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(25338, 12), 940}, // 1086 CmdExecTime in SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {IR(16354, 5), 939}, // 1087 None in SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {IR(25350, 13), 942}, // 1088 MayUsePrintf in SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {IR(16354, 5), 941}, // 1089 None in SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {IR(25363, 7), 943}, // 1090 Export in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(25370, 7), 944}, // 1091 Import in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(25377, 12), 945}, // 1092 LinkOnceODR in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(25389, 8), 946}, // 1093 WeakAMD in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(25411, 12), 948}, // 1094 CachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(25463, 17), 951}, // 1095 ConstCachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(25438, 25), 950}, // 1096 InvalidateAfterReadINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(25423, 15), 949}, // 1097 StreamingINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(25397, 14), 947}, // 1098 UncachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(25603, 22), 964}, // 1099 DependencyArrayALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25625, 21), 964}, // 1100 DependencyArrayINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25498, 19), 955}, // 1101 DependencyInfinite in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25517, 17), 956}, // 1102 DependencyLength in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25487, 11), 954}, // 1103 DontUnroll in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(20124, 25), 962}, // 1104 InitiationIntervalALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(20149, 24), 962}, // 1105 InitiationIntervalINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25562, 18), 959}, // 1106 IterationMultiple in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25646, 19), 966}, // 1107 LoopCoalesceALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25665, 18), 966}, // 1108 LoopCoalesceINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25808, 16), 970}, // 1109 LoopCountALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25824, 15), 970}, // 1110 LoopCountINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(20173, 21), 963}, // 1111 MaxConcurrencyALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(20194, 20), 963}, // 1112 MaxConcurrencyINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25683, 22), 967}, // 1113 MaxInterleavingALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25705, 21), 967}, // 1114 MaxInterleavingINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25548, 14), 958}, // 1115 MaxIterations in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25839, 27), 971}, // 1116 MaxReinvocationDelayALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25866, 26), 971}, // 1117 MaxReinvocationDelayINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25534, 14), 957}, // 1118 MinIterations in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25779, 15), 969}, // 1119 NoFusionALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25794, 14), 969}, // 1120 NoFusionINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(16354, 5), 952}, // 1121 None in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25590, 13), 961}, // 1122 PartialCount in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25580, 10), 960}, // 1123 PeelCount in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(20214, 21), 965}, // 1124 PipelineEnableALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(20235, 20), 965}, // 1125 PipelineEnableINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25726, 27), 968}, // 1126 SpeculatedIterationsALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25753, 26), 968}, // 1127 SpeculatedIterationsINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25480, 7), 953}, // 1128 Unroll in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(26175, 27), 985}, // 1129 MatrixAPackedBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(26123, 26), 983}, // 1130 MatrixAPackedFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(26043, 23), 979}, // 1131 MatrixAPackedInt4INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25997, 23), 977}, // 1132 MatrixAPackedInt8INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25892, 29), 973}, // 1133 MatrixASignedComponentsINTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(26089, 17), 981}, // 1134 MatrixATF32INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(26202, 27), 986}, // 1135 MatrixBPackedBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(26149, 26), 984}, // 1136 MatrixBPackedFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(26066, 23), 980}, // 1137 MatrixBPackedInt4INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(26020, 23), 978}, // 1138 MatrixBPackedInt8INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25921, 29), 974}, // 1139 MatrixBSignedComponentsINTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(26106, 17), 982}, // 1140 MatrixBTF32INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25950, 21), 975}, // 1141 MatrixCBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25971, 26), 976}, // 1142 MatrixResultBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(16354, 5), 972}, // 1143 None in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(26362, 20), 994}, // 1144 AliasScopeINTELMask in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(26229, 8), 989}, // 1145 Aligned in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(26237, 21), 991}, // 1146 MakePointerAvailable in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(26258, 24), 991}, // 1147 MakePointerAvailableKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(26282, 19), 992}, // 1148 MakePointerVisible in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(26301, 22), 992}, // 1149 MakePointerVisibleKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(26382, 17), 995}, // 1150 NoAliasINTELMask in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(26323, 18), 993}, // 1151 NonPrivatePointer in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(26341, 21), 993}, // 1152 NonPrivatePointerKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(16354, 5), 987}, // 1153 None in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(24712, 12), 990}, // 1154 Nontemporal in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(17592, 9), 988}, // 1155 Volatile in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(26406, 8), 997}, // 1156 GLSL450 in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(26414, 7), 998}, // 1157 OpenCL in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(26399, 7), 996}, // 1158 Simple in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(26421, 7), 999}, // 1159 Vulkan in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(26428, 10), 999}, // 1160 VulkanKHR in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(26446, 8), 1001}, // 1161 Acquire in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26462, 15), 1003}, // 1162 AcquireRelease in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26566, 20), 1009}, // 1163 AtomicCounterMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26545, 21), 1008}, // 1164 CrossWorkgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26586, 12), 1010}, // 1165 ImageMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26627, 14), 1012}, // 1166 MakeAvailable in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26641, 17), 1012}, // 1167 MakeAvailableKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26658, 12), 1013}, // 1168 MakeVisible in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26670, 15), 1013}, // 1169 MakeVisibleKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(16354, 5), 1000}, // 1170 None in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26598, 13), 1011}, // 1171 OutputMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26611, 16), 1011}, // 1172 OutputMemoryKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26438, 8), 1000}, // 1173 Relaxed in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26454, 8), 1002}, // 1174 Release in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26477, 23), 1004}, // 1175 SequentiallyConsistent in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26514, 15), 1006}, // 1176 SubgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26500, 14), 1005}, // 1177 UniformMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(17592, 9), 1014}, // 1178 Volatile in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26529, 16), 1007}, // 1179 WorkgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26685, 10), 1015}, // 1180 AutoINTEL in SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS
  {IR(26700, 4), 1017}, // 1181 SAT in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(26713, 8), 1019}, // 1182 SAT_SYM in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(26704, 9), 1018}, // 1183 SAT_ZERO in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(26695, 5), 1016}, // 1184 WRAP in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(26721, 25), 1020}, // 1185 PackedVectorFormat4x8Bit in SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {IR(26746, 28), 1020}, // 1186 PackedVectorFormat4x8BitKHR in SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {IR(26787, 4), 1023}, // 1187 RND in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26820, 9), 1027}, // 1188 RND_CONV in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26829, 13), 1028}, // 1189 RND_CONV_ODD in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26800, 8), 1025}, // 1190 RND_INF in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26808, 12), 1026}, // 1191 RND_MIN_INF in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26791, 9), 1024}, // 1192 RND_ZERO in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26774, 4), 1021}, // 1193 TRN in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26778, 9), 1022}, // 1194 TRN_ZERO in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(16354, 5), 1029}, // 1195 None in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(26842, 25), 1030}, // 1196 RobustnessPerComponentNV in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(26867, 23), 1031}, // 1197 RobustnessPerElementNV in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(26959, 27), 1037}, // 1198 CullBackFacingTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26986, 28), 1038}, // 1199 CullFrontFacingTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(27028, 16), 1040}, // 1200 CullNoOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(27014, 14), 1039}, // 1201 CullOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(27128, 30), 1043}, // 1202 ForceOpacityMicromap2StateEXT in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(27098, 30), 1043}, // 1203 ForceOpacityMicromap2StateKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26900, 12), 1034}, // 1204 NoOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(17106, 8), 1032}, // 1205 NoneKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26890, 10), 1033}, // 1206 OpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(27085, 13), 1042}, // 1207 SkipAABBsKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(27061, 24), 1041}, // 1208 SkipBuiltinPrimitivesNV in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26935, 24), 1036}, // 1209 SkipClosestHitShaderKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(27044, 17), 1041}, // 1210 SkipTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26912, 23), 1035}, // 1211 TerminateOnFirstHitKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(27199, 37), 1045}, // 1212 RayQueryCandidateIntersectionAABBKHR in SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {IR(27158, 41), 1044}, // 1213 RayQueryCandidateIntersectionTriangleKHR in SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {IR(27314, 42), 1048}, // 1214 RayQueryCommittedIntersectionGeneratedKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(27236, 37), 1046}, // 1215 RayQueryCommittedIntersectionNoneKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(27273, 41), 1047}, // 1216 RayQueryCommittedIntersectionTriangleKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(27356, 33), 1049}, // 1217 RayQueryCandidateIntersectionKHR in SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {IR(27389, 33), 1050}, // 1218 RayQueryCommittedIntersectionKHR in SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {IR(27434, 6), 1053}, // 1219 Clamp in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(27422, 12), 1052}, // 1220 ClampToEdge in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(16354, 5), 1051}, // 1221 None in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(27440, 7), 1054}, // 1222 Repeat in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(27447, 15), 1055}, // 1223 RepeatMirrored in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(27470, 7), 1057}, // 1224 Linear in SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {IR(27462, 8), 1056}, // 1225 Nearest in SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {IR(27535, 13), 1066}, // 1226 R11fG11fB10f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27577, 4), 1072}, // 1227 R16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27615, 9), 1077}, // 1228 R16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27548, 5), 1067}, // 1229 R16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27677, 5), 1086}, // 1230 R16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27748, 6), 1096}, // 1231 R16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27501, 5), 1061}, // 1232 R32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27655, 5), 1082}, // 1233 R32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27712, 6), 1091}, // 1234 R32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27765, 5), 1099}, // 1235 R64i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27759, 6), 1098}, // 1236 R64ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27581, 3), 1073}, // 1237 R8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27624, 8), 1078}, // 1238 R8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27682, 4), 1087}, // 1239 R8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27754, 5), 1097}, // 1240 R8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27568, 5), 1070}, // 1241 Rg16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27596, 10), 1075}, // 1242 Rg16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27529, 6), 1065}, // 1243 Rg16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27666, 6), 1084}, // 1244 Rg16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27735, 7), 1094}, // 1245 Rg16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27523, 6), 1064}, // 1246 Rg32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27660, 6), 1083}, // 1247 Rg32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27728, 7), 1093}, // 1248 Rg32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27573, 4), 1071}, // 1249 Rg8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27606, 9), 1076}, // 1250 Rg8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27672, 5), 1085}, // 1251 Rg8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27742, 6), 1095}, // 1252 Rg8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27560, 8), 1069}, // 1253 Rgb10A2 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27718, 10), 1092}, // 1254 Rgb10a2ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27553, 7), 1068}, // 1255 Rgba16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27584, 12), 1074}, // 1256 Rgba16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27493, 8), 1060}, // 1257 Rgba16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27640, 8), 1080}, // 1258 Rgba16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27695, 9), 1089}, // 1259 Rgba16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27485, 8), 1059}, // 1260 Rgba32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27632, 8), 1079}, // 1261 Rgba32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27686, 9), 1088}, // 1262 Rgba32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27506, 6), 1062}, // 1263 Rgba8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27512, 11), 1063}, // 1264 Rgba8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27648, 7), 1081}, // 1265 Rgba8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27704, 8), 1090}, // 1266 Rgba8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27477, 8), 1058}, // 1267 Unknown in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27770, 12), 1100}, // 1268 CrossDevice in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27782, 7), 1101}, // 1269 Device in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27808, 11), 1104}, // 1270 Invocation in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27819, 12), 1105}, // 1271 QueueFamily in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27831, 15), 1105}, // 1272 QueueFamilyKHR in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27846, 14), 1106}, // 1273 ShaderCallKHR in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27799, 9), 1103}, // 1274 Subgroup in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27789, 10), 1102}, // 1275 Workgroup in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27868, 12), 1109}, // 1276 DontFlatten in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(27860, 8), 1108}, // 1277 Flatten in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(16354, 5), 1107}, // 1278 None in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(27880, 29), 1110}, // 1279 IdentifierPossibleDuplicates in SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS
  {IR(16235, 8), 1112}, // 1280 Address in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16243, 8), 1113}, // 1281 Boolean in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16251, 6), 1114}, // 1282 Float in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16257, 7), 1115}, // 1283 Signed in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16264, 11), 1116}, // 1284 SignedChar in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16275, 9), 1117}, // 1285 Unsigned in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16284, 13), 1118}, // 1286 UnsignedChar in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16223, 12), 1111}, // 1287 Unspecified in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(16297, 6), 1119}, // 1288 Class in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(16303, 10), 1120}, // 1289 Structure in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(16313, 6), 1121}, // 1290 Union in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(16334, 20), 1123}, // 1291 ImportedDeclaration in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(16319, 15), 1122}, // 1292 ImportedModule in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(16443, 15), 1131}, // 1293 FlagArtificial in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16458, 13), 1132}, // 1294 FlagExplicit in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16431, 12), 1130}, // 1295 FlagFwdDecl in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16521, 21), 1136}, // 1296 FlagIndirectVariable in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16414, 17), 1129}, // 1297 FlagIsDefinition in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16598, 16), 1140}, // 1298 FlagIsEnumClass in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16402, 12), 1128}, // 1299 FlagIsLocal in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16582, 16), 1139}, // 1300 FlagIsOptimized in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16375, 14), 1126}, // 1301 FlagIsPrivate in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16359, 16), 1125}, // 1302 FlagIsProtected in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16389, 13), 1127}, // 1303 FlagIsPublic in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16542, 20), 1137}, // 1304 FlagLValueReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16486, 18), 1134}, // 1305 FlagObjectPointer in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16471, 15), 1133}, // 1306 FlagPrototyped in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16562, 20), 1138}, // 1307 FlagRValueReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16504, 17), 1135}, // 1308 FlagStaticMember in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16634, 24), 1142}, // 1309 FlagTypePassByReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16614, 20), 1141}, // 1310 FlagTypePassByValue in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(27909, 26), 1143}, // 1311 FlagUnknownPhysicalLayout in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16354, 5), 1124}, // 1312 None in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16719, 9), 1148}, // 1313 BitPiece in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16751, 7), 1152}, // 1314 Constu in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16658, 6), 1144}, // 1315 Deref in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16758, 9), 1153}, // 1316 Fragment in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16669, 6), 1146}, // 1317 Minus in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16664, 5), 1145}, // 1318 Plus in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16708, 11), 1147}, // 1319 PlusUconst in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16740, 11), 1151}, // 1320 StackValue in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16728, 5), 1149}, // 1321 Swap in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16733, 7), 1150}, // 1322 Xderef in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16803, 11), 1157}, // 1323 AtomicType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16767, 10), 1154}, // 1324 ConstType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16790, 13), 1156}, // 1325 RestrictType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16777, 13), 1155}, // 1326 VolatileType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(27970, 15), 1164}, // 1327 CPP_for_OpenCL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27935, 5), 1159}, // 1328 ESSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27940, 5), 1160}, // 1329 GLSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27990, 7), 1166}, // 1330 HERO_C in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27965, 5), 1163}, // 1331 HLSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27997, 5), 1167}, // 1332 NZSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27945, 9), 1161}, // 1333 OpenCL_C in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27954, 11), 1162}, // 1334 OpenCL_CPP in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(28022, 5), 1172}, // 1335 Pred in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(28017, 5), 1171}, // 1336 Rust in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27985, 5), 1165}, // 1337 SYCL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(28007, 6), 1169}, // 1338 Slang in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27477, 8), 1158}, // 1339 Unknown in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(28002, 5), 1168}, // 1340 WGSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(28013, 4), 1170}, // 1341 Zig in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(28109, 14), 1183}, // 1342 AtomicCounter in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28191, 16), 1189}, // 1343 CallableDataKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28207, 15), 1189}, // 1344 CallableDataNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28527, 17), 1199}, // 1345 CodeSectionINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28056, 15), 1178}, // 1346 CrossWorkgroup in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28544, 17), 1200}, // 1347 DeviceOnlyALTERA in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28561, 16), 1200}, // 1348 DeviceOnlyINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28079, 9), 1180}, // 1349 Function in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28088, 8), 1181}, // 1350 Generic in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28296, 16), 1192}, // 1351 HitAttributeKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28312, 15), 1192}, // 1352 HitAttributeNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28505, 22), 1198}, // 1353 HitObjectAttributeEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28460, 21), 1196}, // 1354 HitObjectAttributeNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28577, 15), 1201}, // 1355 HostOnlyALTERA in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28592, 14), 1201}, // 1356 HostOnlyINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28123, 6), 1184}, // 1357 Image in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28222, 24), 1190}, // 1358 IncomingCallableDataKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28246, 23), 1190}, // 1359 IncomingCallableDataNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28327, 22), 1193}, // 1360 IncomingRayPayloadKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28349, 21), 1193}, // 1361 IncomingRayPayloadNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28043, 6), 1174}, // 1362 Input in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28175, 16), 1188}, // 1363 NodePayloadAMDX in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28049, 7), 1176}, // 1364 Output in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28413, 22), 1195}, // 1365 PhysicalStorageBuffer in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28435, 25), 1195}, // 1366 PhysicalStorageBufferEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28071, 8), 1179}, // 1367 Private in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28096, 13), 1182}, // 1368 PushConstant in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28269, 14), 1191}, // 1369 RayPayloadKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28283, 13), 1191}, // 1370 RayPayloadNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28370, 22), 1194}, // 1371 ShaderRecordBufferKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28392, 21), 1194}, // 1372 ShaderRecordBufferNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28129, 14), 1185}, // 1373 StorageBuffer in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28481, 24), 1197}, // 1374 TaskPayloadWorkgroupEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28156, 19), 1187}, // 1375 TileAttachmentQCOM in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28143, 13), 1186}, // 1376 TileImageEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(17643, 8), 1175}, // 1377 Uniform in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28027, 16), 1173}, // 1378 UniformConstant in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27789, 10), 1177}, // 1379 Workgroup in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(25423, 15), 1205}, // 1380 StreamingINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(25397, 14), 1202}, // 1381 UncachedINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(28624, 15), 1204}, // 1382 WriteBackINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(28606, 18), 1203}, // 1383 WriteThroughINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(28650, 11), 1208}, // 1384 DecodeFunc in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(28661, 17), 1209}, // 1385 DecodeVectorFunc in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(16354, 5), 1206}, // 1386 None in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(28639, 11), 1207}, // 1387 TensorView in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(27422, 12), 1212}, // 1388 ClampToEdge in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(17601, 9), 1211}, // 1389 Constant in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(27440, 7), 1213}, // 1390 Repeat in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(27447, 15), 1214}, // 1391 RepeatMirrored in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(28678, 10), 1210}, // 1392 Undefined in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(28731, 24), 1218}, // 1393 MakeElementAvailableARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(28755, 22), 1219}, // 1394 MakeElementVisibleARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(28777, 21), 1220}, // 1395 NonPrivateElementARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(28688, 8), 1215}, // 1396 NoneARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(28696, 15), 1216}, // 1397 NontemporalARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(28711, 20), 1217}, // 1398 OutOfBoundsValueARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
}};

IndexRange OperandNameRangeForKind(spv_operand_type_t type) {
  switch(type) {
    case SPV_OPERAND_TYPE_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_ADDRESSING_MODEL: return IR(3, 5);
    case SPV_OPERAND_TYPE_BUILT_IN: return IR(8, 150);
    case SPV_OPERAND_TYPE_CAPABILITY: return IR(158, 344);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(502, 8);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(510, 3);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(513, 2);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS: return IR(515, 19);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION: return IR(534, 10);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(544, 4);
    case SPV_OPERAND_TYPE_COMPONENT_TYPE: return IR(548, 15);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT: return IR(563, 4);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS: return IR(567, 6);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE: return IR(573, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE: return IR(576, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT: return IR(579, 4);
    case SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(583, 8);
    case SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE: return IR(591, 3);
    case SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS: return IR(594, 16);
    case SPV_OPERAND_TYPE_DEBUG_OPERATION: return IR(610, 9);
    case SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER: return IR(619, 3);
    case SPV_OPERAND_TYPE_DECORATION: return IR(622, 198);
    case SPV_OPERAND_TYPE_DIMENSIONALITY: return IR(820, 8);
    case SPV_OPERAND_TYPE_EXECUTION_MODE: return IR(828, 104);
    case SPV_OPERAND_TYPE_EXECUTION_MODEL: return IR(932, 23);
    case SPV_OPERAND_TYPE_FPDENORM_MODE: return IR(955, 2);
    case SPV_OPERAND_TYPE_FPENCODING: return IR(957, 3);
    case SPV_OPERAND_TYPE_FPOPERATION_MODE: return IR(960, 2);
    case SPV_OPERAND_TYPE_FP_FAST_MATH_MODE: return IR(962, 11);
    case SPV_OPERAND_TYPE_FP_ROUNDING_MODE: return IR(973, 4);
    case SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE: return IR(977, 4);
    case SPV_OPERAND_TYPE_FUNCTION_CONTROL: return IR(981, 7);
    case SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE: return IR(988, 10);
    case SPV_OPERAND_TYPE_GROUP_OPERATION: return IR(998, 10);
    case SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER: return IR(1008, 4);
    case SPV_OPERAND_TYPE_IMAGE: return IR(1012, 21);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE: return IR(1033, 26);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER: return IR(1059, 20);
    case SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER: return IR(1079, 4);
    case SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS: return IR(1083, 3);
    case SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO: return IR(1086, 2);
    case SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS: return IR(1088, 2);
    case SPV_OPERAND_TYPE_LINKAGE_TYPE: return IR(1090, 4);
    case SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL: return IR(1094, 5);
    case SPV_OPERAND_TYPE_LOOP_CONTROL: return IR(1099, 30);
    case SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(1129, 15);
    case SPV_OPERAND_TYPE_MEMORY_ACCESS: return IR(1144, 12);
    case SPV_OPERAND_TYPE_MEMORY_MODEL: return IR(1156, 5);
    case SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID: return IR(1161, 19);
    case SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS: return IR(1180, 1);
    case SPV_OPERAND_TYPE_OVERFLOW_MODES: return IR(1181, 4);
    case SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT: return IR(1185, 2);
    case SPV_OPERAND_TYPE_QUANTIZATION_MODES: return IR(1187, 8);
    case SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS: return IR(1195, 3);
    case SPV_OPERAND_TYPE_RAY_FLAGS: return IR(1198, 14);
    case SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE: return IR(1212, 2);
    case SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE: return IR(1214, 3);
    case SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION: return IR(1217, 2);
    case SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE: return IR(1219, 5);
    case SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE: return IR(1224, 2);
    case SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT: return IR(1226, 42);
    case SPV_OPERAND_TYPE_SCOPE_ID: return IR(1268, 8);
    case SPV_OPERAND_TYPE_SELECTION_CONTROL: return IR(1276, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS: return IR(1279, 1);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(1280, 8);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(1288, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(1291, 2);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS: return IR(1293, 20);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION: return IR(1313, 10);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(1323, 4);
    case SPV_OPERAND_TYPE_SOURCE_LANGUAGE: return IR(1327, 15);
    case SPV_OPERAND_TYPE_STORAGE_CLASS: return IR(1342, 38);
    case SPV_OPERAND_TYPE_STORE_CACHE_CONTROL: return IR(1380, 4);
    case SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS: return IR(1384, 4);
    case SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE: return IR(1388, 5);
    case SPV_OPERAND_TYPE_TENSOR_OPERANDS: return IR(1393, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_IMAGE: return IR(1012, 21);
    case SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS: return IR(1144, 12);
    case SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT: return IR(1185, 2);
    case SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS: return IR(567, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(1129, 15);
    case SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS: return IR(1195, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_FPENCODING: return IR(957, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS: return IR(1393, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_CAPABILITY: return IR(158, 344);
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
static const std::array<InstructionDesc, 873> kInstructionDesc{{
  {spv::Op::OpNop, false, false, IR(0, 0), IR(28798, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpUndef, true, true, IR(39, 2), IR(28854, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpSourceContinued, false, false, IR(11, 1), IR(28860, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpSource, false, false, IR(41, 4), IR(28979, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpSourceExtension, false, false, IR(11, 1), IR(28986, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpName, false, false, IR(45, 2), IR(29002, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpMemberName, false, false, IR(47, 3), IR(29007, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpString, true, false, IR(50, 2), IR(29018, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpLine, false, false, IR(52, 3), IR(29025, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpExtension, false, false, IR(11, 1), IR(29030, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpExtInstImport, true, false, IR(50, 2), IR(29040, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpExtInst, true, true, IR(55, 4), IR(29100, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpMemoryModel, false, false, IR(59, 2), IR(29172, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpEntryPoint, false, false, IR(61, 4), IR(29246, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpExecutionMode, false, false, IR(65, 2), IR(29289, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpCapability, false, false, IR(67, 1), IR(29331, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpTypeVoid, true, false, IR(68, 1), IR(29342, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeBool, true, false, IR(68, 1), IR(29351, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeInt, true, false, IR(69, 3), IR(29360, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeFloat, true, false, IR(72, 3), IR(29405, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeVector, true, false, IR(75, 3), IR(29415, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeMatrix, true, false, IR(75, 3), IR(29426, 11), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeImage, true, false, IR(78, 9), IR(29550, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeSampler, true, false, IR(68, 1), IR(29560, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeSampledImage, true, false, IR(87, 2), IR(29572, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeArray, true, false, IR(89, 3), IR(29589, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeRuntimeArray, true, false, IR(87, 2), IR(29599, 17), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeStruct, true, false, IR(92, 2), IR(29616, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeOpaque, true, false, IR(50, 2), IR(29627, 11), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypePointer, true, false, IR(94, 3), IR(29669, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeFunction, true, false, IR(97, 3), IR(29681, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeEvent, true, false, IR(68, 1), IR(29694, 10), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeDeviceEvent, true, false, IR(68, 1), IR(29704, 16), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeReserveId, true, false, IR(68, 1), IR(29720, 14), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeQueue, true, false, IR(68, 1), IR(29734, 10), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypePipe, true, false, IR(100, 2), IR(29744, 9), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeForwardPointer, false, false, IR(102, 2), IR(29753, 19), IR(0, 0), IR(215, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantTrue, true, true, IR(39, 2), IR(29772, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantFalse, true, true, IR(39, 2), IR(29785, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstant, true, true, IR(104, 3), IR(17601, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantComposite, true, true, IR(107, 3), IR(29837, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantSampler, true, true, IR(110, 5), IR(29933, 16), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantNull, true, true, IR(39, 2), IR(29949, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantTrue, true, true, IR(39, 2), IR(29962, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantFalse, true, true, IR(39, 2), IR(29979, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstant, true, true, IR(104, 3), IR(29997, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantComposite, true, true, IR(107, 3), IR(30010, 22), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantOp, true, true, IR(115, 3), IR(30073, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpFunction, true, true, IR(118, 4), IR(28079, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionParameter, true, true, IR(39, 2), IR(30122, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionEnd, false, false, IR(0, 0), IR(30140, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionCall, true, true, IR(122, 4), IR(30152, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpVariable, true, true, IR(126, 4), IR(30165, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpImageTexelPointer, true, true, IR(130, 5), IR(30174, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpLoad, true, true, IR(135, 4), IR(30232, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpStore, false, false, IR(139, 3), IR(30237, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCopyMemory, false, false, IR(142, 4), IR(30243, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCopyMemorySized, false, false, IR(146, 5), IR(30254, 16), IR(0, 0), IR(218, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpAccessChain, true, true, IR(122, 4), IR(30270, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpInBoundsAccessChain, true, true, IR(122, 4), IR(30282, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrAccessChain, true, true, IR(151, 5), IR(30302, 15), IR(0, 0), IR(220, 4), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpArrayLength, true, true, IR(156, 4), IR(30317, 12), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpGenericPtrMemSemantics, true, true, IR(160, 3), IR(30329, 23), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpInBoundsPtrAccessChain, true, true, IR(151, 5), IR(30352, 23), IR(0, 0), IR(1, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpDecorate, false, false, IR(163, 2), IR(30403, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpMemberDecorate, false, false, IR(165, 3), IR(30412, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpDecorationGroup, true, false, IR(68, 1), IR(30427, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupDecorate, false, false, IR(168, 2), IR(30443, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupMemberDecorate, false, false, IR(170, 2), IR(30502, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpVectorExtractDynamic, true, true, IR(172, 4), IR(30522, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpVectorInsertDynamic, true, true, IR(130, 5), IR(30543, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpVectorShuffle, true, true, IR(176, 5), IR(30563, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeConstruct, true, true, IR(107, 3), IR(30577, 19), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeExtract, true, true, IR(181, 4), IR(30596, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeInsert, true, true, IR(176, 5), IR(30613, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCopyObject, true, true, IR(160, 3), IR(30629, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpTranspose, true, true, IR(160, 3), IR(30640, 10), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpSampledImage, true, true, IR(172, 4), IR(30650, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleImplicitLod, true, true, IR(185, 5), IR(30695, 23), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleExplicitLod, true, true, IR(190, 5), IR(30741, 23), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleDrefImplicitLod, true, true, IR(195, 6), IR(30764, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleDrefExplicitLod, true, true, IR(201, 6), IR(30791, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjImplicitLod, true, true, IR(185, 5), IR(30818, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjExplicitLod, true, true, IR(190, 5), IR(30845, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjDrefImplicitLod, true, true, IR(195, 6), IR(30872, 31), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjDrefExplicitLod, true, true, IR(201, 6), IR(30903, 31), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageFetch, true, true, IR(185, 5), IR(30934, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageGather, true, true, IR(195, 6), IR(30945, 12), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageDrefGather, true, true, IR(195, 6), IR(30957, 16), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageRead, true, true, IR(185, 5), IR(30973, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageWrite, false, false, IR(207, 4), IR(30983, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImage, true, true, IR(160, 3), IR(28123, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryFormat, true, true, IR(160, 3), IR(30994, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryOrder, true, true, IR(160, 3), IR(31011, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySizeLod, true, true, IR(172, 4), IR(31027, 18), IR(0, 0), IR(224, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySize, true, true, IR(160, 3), IR(31045, 15), IR(0, 0), IR(224, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryLod, true, true, IR(172, 4), IR(31060, 14), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryLevels, true, true, IR(160, 3), IR(31074, 17), IR(0, 0), IR(224, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySamples, true, true, IR(160, 3), IR(31091, 18), IR(0, 0), IR(224, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertFToU, true, true, IR(160, 3), IR(31109, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertFToS, true, true, IR(160, 3), IR(31121, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertSToF, true, true, IR(160, 3), IR(31133, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToF, true, true, IR(160, 3), IR(31145, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpUConvert, true, true, IR(160, 3), IR(31157, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSConvert, true, true, IR(160, 3), IR(31166, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpFConvert, true, true, IR(160, 3), IR(31175, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpQuantizeToF16, true, true, IR(160, 3), IR(31184, 14), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertPtrToU, true, true, IR(160, 3), IR(31198, 14), IR(0, 0), IR(215, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSatConvertSToU, true, true, IR(160, 3), IR(31212, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSatConvertUToS, true, true, IR(160, 3), IR(31227, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToPtr, true, true, IR(160, 3), IR(31242, 14), IR(0, 0), IR(215, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpPtrCastToGeneric, true, true, IR(160, 3), IR(31256, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpGenericCastToPtr, true, true, IR(160, 3), IR(31273, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpGenericCastToPtrExplicit, true, true, IR(211, 4), IR(31290, 25), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpBitcast, true, true, IR(160, 3), IR(31315, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSNegate, true, true, IR(160, 3), IR(31323, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFNegate, true, true, IR(160, 3), IR(31331, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIAdd, true, true, IR(172, 4), IR(31339, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFAdd, true, true, IR(172, 4), IR(31344, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpISub, true, true, IR(172, 4), IR(31349, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFSub, true, true, IR(172, 4), IR(31354, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIMul, true, true, IR(172, 4), IR(31359, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFMul, true, true, IR(172, 4), IR(31364, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDiv, true, true, IR(172, 4), IR(31369, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSDiv, true, true, IR(172, 4), IR(31374, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFDiv, true, true, IR(172, 4), IR(31379, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUMod, true, true, IR(172, 4), IR(31384, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSRem, true, true, IR(172, 4), IR(31389, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSMod, true, true, IR(172, 4), IR(31394, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFRem, true, true, IR(172, 4), IR(31399, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFMod, true, true, IR(172, 4), IR(31404, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpVectorTimesScalar, true, true, IR(172, 4), IR(31409, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesScalar, true, true, IR(172, 4), IR(31427, 18), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpVectorTimesMatrix, true, true, IR(172, 4), IR(31445, 18), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesVector, true, true, IR(172, 4), IR(31463, 18), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesMatrix, true, true, IR(172, 4), IR(31481, 18), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpOuterProduct, true, true, IR(172, 4), IR(31499, 13), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpDot, true, true, IR(172, 4), IR(31512, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIAddCarry, true, true, IR(172, 4), IR(31516, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpISubBorrow, true, true, IR(172, 4), IR(31526, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUMulExtended, true, true, IR(172, 4), IR(31537, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSMulExtended, true, true, IR(172, 4), IR(31550, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpAny, true, true, IR(160, 3), IR(31563, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpAll, true, true, IR(160, 3), IR(31567, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsNan, true, true, IR(160, 3), IR(31571, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsInf, true, true, IR(160, 3), IR(31577, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsFinite, true, true, IR(160, 3), IR(31583, 9), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsNormal, true, true, IR(160, 3), IR(31592, 9), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSignBitSet, true, true, IR(160, 3), IR(31601, 11), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLessOrGreater, true, true, IR(172, 4), IR(31612, 14), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), SPV_SPIRV_VERSION_WORD(1,5), PrintingClass::kRelational_and_Logical},
  {spv::Op::OpOrdered, true, true, IR(172, 4), IR(31626, 8), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUnordered, true, true, IR(172, 4), IR(31634, 10), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalEqual, true, true, IR(172, 4), IR(31644, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalNotEqual, true, true, IR(172, 4), IR(31657, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalOr, true, true, IR(172, 4), IR(31673, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalAnd, true, true, IR(172, 4), IR(31683, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalNot, true, true, IR(160, 3), IR(31694, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSelect, true, true, IR(130, 5), IR(31705, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIEqual, true, true, IR(172, 4), IR(31712, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpINotEqual, true, true, IR(172, 4), IR(31719, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUGreaterThan, true, true, IR(172, 4), IR(31729, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSGreaterThan, true, true, IR(172, 4), IR(31742, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUGreaterThanEqual, true, true, IR(172, 4), IR(31755, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSGreaterThanEqual, true, true, IR(172, 4), IR(31773, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpULessThan, true, true, IR(172, 4), IR(31791, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSLessThan, true, true, IR(172, 4), IR(31801, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpULessThanEqual, true, true, IR(172, 4), IR(31811, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSLessThanEqual, true, true, IR(172, 4), IR(31826, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdEqual, true, true, IR(172, 4), IR(31841, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordEqual, true, true, IR(172, 4), IR(31851, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdNotEqual, true, true, IR(172, 4), IR(31863, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordNotEqual, true, true, IR(172, 4), IR(31876, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdLessThan, true, true, IR(172, 4), IR(31891, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordLessThan, true, true, IR(172, 4), IR(31904, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdGreaterThan, true, true, IR(172, 4), IR(31919, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordGreaterThan, true, true, IR(172, 4), IR(31935, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdLessThanEqual, true, true, IR(172, 4), IR(31953, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordLessThanEqual, true, true, IR(172, 4), IR(31971, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdGreaterThanEqual, true, true, IR(172, 4), IR(31991, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordGreaterThanEqual, true, true, IR(172, 4), IR(32012, 23), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpShiftRightLogical, true, true, IR(172, 4), IR(32035, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpShiftRightArithmetic, true, true, IR(172, 4), IR(32053, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpShiftLeftLogical, true, true, IR(172, 4), IR(32074, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseOr, true, true, IR(172, 4), IR(32091, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseXor, true, true, IR(172, 4), IR(32101, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseAnd, true, true, IR(172, 4), IR(32112, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpNot, true, true, IR(160, 3), IR(32123, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldInsert, true, true, IR(215, 6), IR(32127, 15), IR(0, 0), IR(227, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldSExtract, true, true, IR(130, 5), IR(32142, 17), IR(0, 0), IR(227, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldUExtract, true, true, IR(130, 5), IR(32159, 17), IR(0, 0), IR(227, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitReverse, true, true, IR(160, 3), IR(32176, 11), IR(0, 0), IR(227, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitCount, true, true, IR(160, 3), IR(32187, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpDPdx, true, true, IR(160, 3), IR(32196, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdy, true, true, IR(160, 3), IR(32201, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidth, true, true, IR(160, 3), IR(32206, 7), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdxFine, true, true, IR(160, 3), IR(32213, 9), IR(0, 0), IR(229, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdyFine, true, true, IR(160, 3), IR(32222, 9), IR(0, 0), IR(229, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidthFine, true, true, IR(160, 3), IR(32231, 11), IR(0, 0), IR(229, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdxCoarse, true, true, IR(160, 3), IR(32242, 11), IR(0, 0), IR(229, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdyCoarse, true, true, IR(160, 3), IR(32253, 11), IR(0, 0), IR(229, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidthCoarse, true, true, IR(160, 3), IR(32264, 13), IR(0, 0), IR(229, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpEmitVertex, false, false, IR(0, 0), IR(32277, 11), IR(0, 0), IR(70, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEndPrimitive, false, false, IR(0, 0), IR(32288, 13), IR(0, 0), IR(70, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEmitStreamVertex, false, false, IR(10, 1), IR(32301, 17), IR(0, 0), IR(123, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEndStreamPrimitive, false, false, IR(10, 1), IR(32318, 19), IR(0, 0), IR(123, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpControlBarrier, false, false, IR(221, 3), IR(32374, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpMemoryBarrier, false, false, IR(224, 2), IR(32389, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpAtomicLoad, true, true, IR(226, 5), IR(32403, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicStore, false, false, IR(231, 4), IR(32414, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicExchange, true, true, IR(235, 6), IR(32426, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicCompareExchange, true, true, IR(241, 8), IR(32441, 22), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicCompareExchangeWeak, true, true, IR(241, 8), IR(32463, 26), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), SPV_SPIRV_VERSION_WORD(1,3), PrintingClass::kAtomic},
  {spv::Op::OpAtomicIIncrement, true, true, IR(226, 5), IR(32489, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicIDecrement, true, true, IR(226, 5), IR(32506, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicIAdd, true, true, IR(235, 6), IR(32523, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicISub, true, true, IR(235, 6), IR(32534, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicSMin, true, true, IR(235, 6), IR(32545, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicUMin, true, true, IR(235, 6), IR(32556, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicSMax, true, true, IR(235, 6), IR(32567, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicUMax, true, true, IR(235, 6), IR(32578, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicAnd, true, true, IR(235, 6), IR(32589, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicOr, true, true, IR(235, 6), IR(32599, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicXor, true, true, IR(235, 6), IR(32608, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpPhi, true, true, IR(107, 3), IR(32618, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLoopMerge, false, false, IR(249, 3), IR(32652, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpSelectionMerge, false, false, IR(252, 2), IR(32697, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLabel, true, false, IR(68, 1), IR(32712, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpBranch, false, false, IR(10, 1), IR(32718, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpBranchConditional, false, false, IR(254, 4), IR(32725, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpSwitch, false, false, IR(258, 3), IR(32788, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpKill, false, false, IR(0, 0), IR(32795, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpReturn, false, false, IR(0, 0), IR(32800, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpReturnValue, false, false, IR(10, 1), IR(32807, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpUnreachable, false, false, IR(0, 0), IR(32819, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLifetimeStart, false, false, IR(261, 2), IR(32831, 14), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLifetimeStop, false, false, IR(261, 2), IR(32845, 13), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpGroupAsyncCopy, true, true, IR(263, 8), IR(32858, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupWaitEvents, false, false, IR(271, 3), IR(32873, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupAll, true, true, IR(274, 4), IR(32889, 9), IR(0, 0), IR(230, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupAny, true, true, IR(274, 4), IR(32898, 9), IR(0, 0), IR(230, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBroadcast, true, true, IR(278, 5), IR(32907, 15), IR(0, 0), IR(230, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupIAdd, true, true, IR(283, 5), IR(32955, 10), IR(0, 0), IR(230, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFAdd, true, true, IR(283, 5), IR(32965, 10), IR(0, 0), IR(230, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMin, true, true, IR(283, 5), IR(32975, 10), IR(0, 0), IR(230, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMin, true, true, IR(283, 5), IR(32985, 10), IR(0, 0), IR(230, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMin, true, true, IR(283, 5), IR(32995, 10), IR(0, 0), IR(230, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMax, true, true, IR(283, 5), IR(33005, 10), IR(0, 0), IR(230, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMax, true, true, IR(283, 5), IR(33015, 10), IR(0, 0), IR(230, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMax, true, true, IR(283, 5), IR(33025, 10), IR(0, 0), IR(230, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpReadPipe, true, true, IR(215, 6), IR(33035, 9), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpWritePipe, true, true, IR(215, 6), IR(33044, 10), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReservedReadPipe, true, true, IR(288, 8), IR(33054, 17), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReservedWritePipe, true, true, IR(288, 8), IR(33071, 18), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReserveReadPipePackets, true, true, IR(215, 6), IR(33089, 23), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReserveWritePipePackets, true, true, IR(215, 6), IR(33112, 24), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCommitReadPipe, false, false, IR(296, 4), IR(33136, 15), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCommitWritePipe, false, false, IR(296, 4), IR(33151, 16), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpIsValidReserveId, true, true, IR(160, 3), IR(33167, 17), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetNumPipePackets, true, true, IR(130, 5), IR(33184, 18), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetMaxPipePackets, true, true, IR(130, 5), IR(33202, 18), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupReserveReadPipePackets, true, true, IR(300, 7), IR(33220, 28), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupReserveWritePipePackets, true, true, IR(300, 7), IR(33248, 29), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupCommitReadPipe, false, false, IR(307, 5), IR(33277, 20), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupCommitWritePipe, false, false, IR(307, 5), IR(33297, 21), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpEnqueueMarker, true, true, IR(215, 6), IR(33318, 14), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpEnqueueKernel, true, true, IR(312, 13), IR(33332, 14), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelNDrangeSubGroupCount, true, true, IR(325, 7), IR(33346, 30), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelNDrangeMaxSubGroupSize, true, true, IR(325, 7), IR(33376, 32), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelWorkGroupSize, true, true, IR(215, 6), IR(33408, 23), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelPreferredWorkGroupSizeMultiple, true, true, IR(215, 6), IR(33431, 40), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpRetainEvent, false, false, IR(10, 1), IR(33471, 12), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpReleaseEvent, false, false, IR(10, 1), IR(33483, 13), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpCreateUserEvent, true, true, IR(39, 2), IR(33496, 16), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpIsValidEvent, true, true, IR(160, 3), IR(33512, 13), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpSetUserEventStatus, false, false, IR(36, 2), IR(33525, 19), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpCaptureEventProfilingInfo, false, false, IR(33, 3), IR(33544, 26), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetDefaultQueue, true, true, IR(39, 2), IR(33570, 16), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpBuildNDRange, true, true, IR(130, 5), IR(33586, 13), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpImageSparseSampleImplicitLod, true, true, IR(185, 5), IR(33599, 29), IR(0, 0), IR(231, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleExplicitLod, true, true, IR(190, 5), IR(33628, 29), IR(0, 0), IR(231, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleDrefImplicitLod, true, true, IR(195, 6), IR(33657, 33), IR(0, 0), IR(231, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleDrefExplicitLod, true, true, IR(201, 6), IR(33690, 33), IR(0, 0), IR(231, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjImplicitLod, true, true, IR(185, 5), IR(33723, 33), IR(0, 0), IR(231, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjExplicitLod, true, true, IR(190, 5), IR(33756, 33), IR(0, 0), IR(231, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjDrefImplicitLod, true, true, IR(195, 6), IR(33789, 37), IR(0, 0), IR(231, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjDrefExplicitLod, true, true, IR(201, 6), IR(33826, 37), IR(0, 0), IR(231, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseFetch, true, true, IR(185, 5), IR(33863, 17), IR(0, 0), IR(231, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseGather, true, true, IR(195, 6), IR(33880, 18), IR(0, 0), IR(231, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseDrefGather, true, true, IR(195, 6), IR(33898, 22), IR(0, 0), IR(231, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseTexelsResident, true, true, IR(160, 3), IR(33920, 26), IR(0, 0), IR(231, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpNoLine, false, false, IR(0, 0), IR(33946, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpAtomicFlagTestAndSet, true, true, IR(226, 5), IR(33953, 21), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicFlagClear, false, false, IR(332, 3), IR(33974, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpImageSparseRead, true, true, IR(185, 5), IR(33990, 16), IR(0, 0), IR(231, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpSizeOf, true, true, IR(160, 3), IR(34006, 7), IR(0, 0), IR(1, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpTypePipeStorage, true, false, IR(68, 1), IR(34013, 16), IR(0, 0), IR(232, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantPipeStorage, true, true, IR(335, 5), IR(34029, 20), IR(0, 0), IR(232, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCreatePipeFromPipeStorage, true, true, IR(160, 3), IR(34049, 26), IR(0, 0), IR(232, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetKernelLocalSizeForSubgroupCount, true, true, IR(325, 7), IR(34075, 35), IR(0, 0), IR(163, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelMaxNumSubgroups, true, true, IR(215, 6), IR(34110, 25), IR(0, 0), IR(163, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpTypeNamedBarrier, true, false, IR(68, 1), IR(34135, 17), IR(0, 0), IR(233, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpNamedBarrierInitialize, true, true, IR(160, 3), IR(34152, 23), IR(0, 0), IR(233, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpMemoryNamedBarrier, false, false, IR(332, 3), IR(34175, 19), IR(0, 0), IR(233, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpModuleProcessed, false, false, IR(11, 1), IR(34194, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpExecutionModeId, false, false, IR(65, 2), IR(34210, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,2), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpDecorateId, false, false, IR(163, 2), IR(34226, 11), IR(0, 0), IR(1, 0), IR(195, 1), SPV_SPIRV_VERSION_WORD(1,2), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupNonUniformElect, true, true, IR(340, 3), IR(34237, 21), IR(0, 0), IR(77, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAll, true, true, IR(274, 4), IR(34258, 19), IR(0, 0), IR(234, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAny, true, true, IR(274, 4), IR(34277, 19), IR(0, 0), IR(234, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAllEqual, true, true, IR(274, 4), IR(34296, 24), IR(0, 0), IR(234, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBroadcast, true, true, IR(278, 5), IR(34320, 25), IR(0, 0), IR(235, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBroadcastFirst, true, true, IR(274, 4), IR(34345, 30), IR(0, 0), IR(235, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallot, true, true, IR(274, 4), IR(6737, 22), IR(0, 0), IR(235, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformInverseBallot, true, true, IR(274, 4), IR(34375, 29), IR(0, 0), IR(235, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotBitExtract, true, true, IR(278, 5), IR(34404, 32), IR(0, 0), IR(235, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotBitCount, true, true, IR(283, 5), IR(34436, 30), IR(0, 0), IR(235, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotFindLSB, true, true, IR(274, 4), IR(34466, 29), IR(0, 0), IR(235, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotFindMSB, true, true, IR(274, 4), IR(34495, 29), IR(0, 0), IR(235, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffle, true, true, IR(278, 5), IR(9876, 23), IR(0, 0), IR(236, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleXor, true, true, IR(278, 5), IR(34524, 26), IR(0, 0), IR(236, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleUp, true, true, IR(278, 5), IR(34550, 25), IR(0, 0), IR(237, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleDown, true, true, IR(278, 5), IR(34575, 27), IR(0, 0), IR(237, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformIAdd, true, true, IR(343, 6), IR(34602, 20), IR(0, 0), IR(238, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFAdd, true, true, IR(343, 6), IR(34622, 20), IR(0, 0), IR(238, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformIMul, true, true, IR(343, 6), IR(34642, 20), IR(0, 0), IR(238, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMul, true, true, IR(343, 6), IR(34662, 20), IR(0, 0), IR(238, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformSMin, true, true, IR(343, 6), IR(34682, 20), IR(0, 0), IR(238, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformUMin, true, true, IR(343, 6), IR(34702, 20), IR(0, 0), IR(238, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMin, true, true, IR(343, 6), IR(34722, 20), IR(0, 0), IR(238, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformSMax, true, true, IR(343, 6), IR(34742, 20), IR(0, 0), IR(238, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformUMax, true, true, IR(343, 6), IR(34762, 20), IR(0, 0), IR(238, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMax, true, true, IR(343, 6), IR(34782, 20), IR(0, 0), IR(238, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseAnd, true, true, IR(343, 6), IR(34802, 26), IR(0, 0), IR(238, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseOr, true, true, IR(343, 6), IR(34828, 25), IR(0, 0), IR(238, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseXor, true, true, IR(343, 6), IR(34853, 26), IR(0, 0), IR(238, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalAnd, true, true, IR(343, 6), IR(34879, 26), IR(0, 0), IR(238, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalOr, true, true, IR(343, 6), IR(34905, 25), IR(0, 0), IR(238, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalXor, true, true, IR(343, 6), IR(34930, 26), IR(0, 0), IR(238, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadBroadcast, true, true, IR(278, 5), IR(34956, 29), IR(0, 0), IR(241, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadSwap, true, true, IR(278, 5), IR(34985, 24), IR(0, 0), IR(241, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpCopyLogical, true, true, IR(160, 3), IR(35009, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpPtrEqual, true, true, IR(172, 4), IR(35021, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrNotEqual, true, true, IR(172, 4), IR(35030, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrDiff, true, true, IR(172, 4), IR(35042, 8), IR(0, 0), IR(242, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpColorAttachmentReadEXT, true, true, IR(349, 4), IR(35050, 23), IR(0, 0), IR(155, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpDepthAttachmentReadEXT, true, true, IR(353, 3), IR(35073, 23), IR(0, 0), IR(164, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpStencilAttachmentReadEXT, true, true, IR(353, 3), IR(35096, 25), IR(0, 0), IR(165, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpTypeTensorARM, true, false, IR(356, 4), IR(35121, 14), IR(0, 0), IR(214, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTensorReadARM, true, true, IR(360, 5), IR(35177, 14), IR(0, 0), IR(214, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpTensorWriteARM, false, false, IR(365, 4), IR(35191, 15), IR(0, 0), IR(214, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpTensorQuerySizeARM, true, true, IR(172, 4), IR(35206, 19), IR(0, 0), IR(214, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpGraphConstantARM, true, true, IR(369, 3), IR(35225, 17), IR(0, 0), IR(245, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphEntryPointARM, false, false, IR(372, 3), IR(35242, 19), IR(0, 0), IR(245, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphARM, true, true, IR(39, 2), IR(10167, 9), IR(0, 0), IR(245, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphInputARM, true, true, IR(122, 4), IR(35261, 14), IR(0, 0), IR(245, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphSetOutputARM, false, false, IR(375, 3), IR(35275, 18), IR(0, 0), IR(245, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphEndARM, false, false, IR(0, 0), IR(35293, 12), IR(0, 0), IR(245, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpTypeGraphARM, true, false, IR(378, 3), IR(35305, 13), IR(0, 0), IR(245, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTerminateInvocation, false, false, IR(0, 0), IR(35318, 20), IR(0, 0), IR(3, 1), IR(205, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpTypeUntypedPointerKHR, true, false, IR(381, 2), IR(35338, 22), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpUntypedVariableKHR, true, true, IR(383, 5), IR(35360, 19), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedAccessChainKHR, true, true, IR(151, 5), IR(35379, 22), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedInBoundsAccessChainKHR, true, true, IR(151, 5), IR(35401, 30), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpSubgroupBallotKHR, true, true, IR(160, 3), IR(6498, 18), IR(0, 0), IR(246, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupFirstInvocationKHR, true, true, IR(160, 3), IR(35431, 27), IR(0, 0), IR(246, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpUntypedPtrAccessChainKHR, true, true, IR(388, 6), IR(35458, 25), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedInBoundsPtrAccessChainKHR, true, true, IR(388, 6), IR(35483, 33), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedArrayLengthKHR, true, true, IR(394, 5), IR(35516, 22), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedPrefetchKHR, false, false, IR(399, 5), IR(35538, 19), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpFmaKHR, true, true, IR(130, 5), IR(35557, 7), IR(0, 0), IR(247, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSubgroupAllKHR, true, true, IR(160, 3), IR(35564, 15), IR(0, 0), IR(248, 1), IR(41, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupAnyKHR, true, true, IR(160, 3), IR(35579, 15), IR(0, 0), IR(248, 1), IR(41, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupAllEqualKHR, true, true, IR(160, 3), IR(35594, 20), IR(0, 0), IR(248, 1), IR(41, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupNonUniformRotateKHR, true, true, IR(404, 6), IR(15030, 25), IR(0, 0), IR(249, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupReadInvocationKHR, true, true, IR(172, 4), IR(35614, 26), IR(0, 0), IR(246, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpExtInstWithForwardRefsKHR, true, true, IR(410, 5), IR(35640, 26), IR(0, 0), IR(1, 0), IR(206, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpUntypedGroupAsyncCopyKHR, true, true, IR(415, 11), IR(35666, 25), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpTraceRayKHR, false, false, IR(426, 11), IR(35691, 12), IR(0, 0), IR(61, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpExecuteCallableKHR, false, false, IR(36, 2), IR(35703, 19), IR(0, 0), IR(61, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToAccelerationStructureKHR, true, true, IR(160, 3), IR(35722, 35), IR(0, 0), IR(250, 2), IR(207, 2), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIgnoreIntersectionKHR, false, false, IR(0, 0), IR(35757, 22), IR(0, 0), IR(61, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTerminateRayKHR, false, false, IR(0, 0), IR(35779, 16), IR(0, 0), IR(61, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSDot, true, true, IR(437, 5), IR(35842, 5), IR(174, 1), IR(252, 1), IR(150, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDot, true, true, IR(437, 5), IR(35855, 5), IR(175, 1), IR(252, 1), IR(150, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSUDot, true, true, IR(437, 5), IR(35868, 6), IR(176, 1), IR(252, 1), IR(150, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSDotAccSat, true, true, IR(442, 6), IR(35883, 11), IR(177, 1), IR(252, 1), IR(150, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDotAccSat, true, true, IR(442, 6), IR(35908, 11), IR(178, 1), IR(252, 1), IR(150, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSUDotAccSat, true, true, IR(442, 6), IR(35933, 12), IR(179, 1), IR(252, 1), IR(150, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpTypeCooperativeMatrixKHR, true, false, IR(448, 6), IR(35960, 25), IR(0, 0), IR(87, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeMatrixLoadKHR, true, true, IR(454, 6), IR(35985, 25), IR(0, 0), IR(87, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixStoreKHR, false, false, IR(460, 5), IR(36010, 26), IR(0, 0), IR(87, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixMulAddKHR, true, true, IR(465, 6), IR(36090, 27), IR(0, 0), IR(87, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpCooperativeMatrixLengthKHR, true, true, IR(160, 3), IR(36117, 27), IR(0, 0), IR(87, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpConstantCompositeReplicateEXT, true, true, IR(160, 3), IR(36144, 30), IR(0, 0), IR(253, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCompositeReplicateEXT, true, true, IR(160, 3), IR(36174, 34), IR(0, 0), IR(253, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpCompositeConstructReplicateEXT, true, true, IR(160, 3), IR(36208, 31), IR(0, 0), IR(253, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpTypeRayQueryKHR, true, false, IR(68, 1), IR(36239, 16), IR(0, 0), IR(204, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpRayQueryInitializeKHR, false, false, IR(471, 8), IR(36255, 22), IR(0, 0), IR(204, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryTerminateKHR, false, false, IR(10, 1), IR(36277, 21), IR(0, 0), IR(204, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGenerateIntersectionKHR, false, false, IR(36, 2), IR(36298, 32), IR(0, 0), IR(204, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryConfirmIntersectionKHR, false, false, IR(10, 1), IR(36330, 31), IR(0, 0), IR(204, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryProceedKHR, true, true, IR(160, 3), IR(36361, 19), IR(0, 0), IR(204, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTypeKHR, true, true, IR(172, 4), IR(36380, 31), IR(0, 0), IR(204, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpImageSampleWeightedQCOM, true, true, IR(130, 5), IR(36411, 24), IR(0, 0), IR(254, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBoxFilterQCOM, true, true, IR(130, 5), IR(36435, 19), IR(0, 0), IR(255, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchSSDQCOM, true, true, IR(325, 7), IR(36454, 23), IR(0, 0), IR(256, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchSADQCOM, true, true, IR(325, 7), IR(36477, 23), IR(0, 0), IR(256, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpBitCastArrayQCOM, true, true, IR(160, 3), IR(36500, 17), IR(0, 0), IR(257, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpImageBlockMatchWindowSSDQCOM, true, true, IR(325, 7), IR(36517, 29), IR(0, 0), IR(258, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchWindowSADQCOM, true, true, IR(325, 7), IR(36546, 29), IR(0, 0), IR(258, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchGatherSSDQCOM, true, true, IR(325, 7), IR(36575, 29), IR(0, 0), IR(258, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchGatherSADQCOM, true, true, IR(325, 7), IR(36604, 29), IR(0, 0), IR(258, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpCompositeConstructCoopMatQCOM, true, true, IR(160, 3), IR(36633, 30), IR(0, 0), IR(257, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeExtractCoopMatQCOM, true, true, IR(160, 3), IR(36663, 28), IR(0, 0), IR(257, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpExtractSubArrayQCOM, true, true, IR(172, 4), IR(36691, 20), IR(0, 0), IR(257, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpGroupIAddNonUniformAMD, true, true, IR(283, 5), IR(36711, 23), IR(0, 0), IR(230, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFAddNonUniformAMD, true, true, IR(283, 5), IR(36734, 23), IR(0, 0), IR(230, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMinNonUniformAMD, true, true, IR(283, 5), IR(36757, 23), IR(0, 0), IR(230, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMinNonUniformAMD, true, true, IR(283, 5), IR(36780, 23), IR(0, 0), IR(230, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMinNonUniformAMD, true, true, IR(283, 5), IR(36803, 23), IR(0, 0), IR(230, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMaxNonUniformAMD, true, true, IR(283, 5), IR(36826, 23), IR(0, 0), IR(230, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMaxNonUniformAMD, true, true, IR(283, 5), IR(36849, 23), IR(0, 0), IR(230, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMaxNonUniformAMD, true, true, IR(283, 5), IR(36872, 23), IR(0, 0), IR(230, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpFragmentMaskFetchAMD, true, true, IR(172, 4), IR(36895, 21), IR(0, 0), IR(259, 1), IR(58, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFragmentFetchAMD, true, true, IR(130, 5), IR(36916, 17), IR(0, 0), IR(259, 1), IR(58, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReadClockKHR, true, true, IR(340, 3), IR(36933, 13), IR(0, 0), IR(260, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAllocateNodePayloadsAMDX, true, true, IR(278, 5), IR(36946, 25), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpEnqueueNodePayloadsAMDX, false, false, IR(10, 1), IR(36971, 24), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeNodePayloadArrayAMDX, true, false, IR(87, 2), IR(36995, 25), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFinishWritingNodePayloadAMDX, true, true, IR(160, 3), IR(37020, 29), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpNodePayloadArrayLengthAMDX, true, true, IR(160, 3), IR(37049, 27), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIsNodePayloadValidAMDX, true, true, IR(172, 4), IR(37076, 23), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConstantStringAMDX, true, false, IR(50, 2), IR(37099, 19), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSpecConstantStringAMDX, true, false, IR(50, 2), IR(37118, 23), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpGroupNonUniformQuadAllKHR, true, true, IR(160, 3), IR(37141, 26), IR(0, 0), IR(172, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadAnyKHR, true, true, IR(160, 3), IR(37167, 26), IR(0, 0), IR(172, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpTypeBufferEXT, true, false, IR(381, 2), IR(37193, 14), IR(0, 0), IR(44, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpBufferPointerEXT, true, true, IR(160, 3), IR(37207, 17), IR(0, 0), IR(44, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpAbortKHR, false, false, IR(36, 2), IR(11244, 9), IR(0, 0), IR(261, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpUntypedImageTexelPointerEXT, true, true, IR(215, 6), IR(37224, 28), IR(0, 0), IR(44, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpMemberDecorateIdEXT, false, false, IR(165, 3), IR(37252, 20), IR(0, 0), IR(44, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpConstantSizeOfEXT, true, true, IR(160, 3), IR(37272, 18), IR(0, 0), IR(44, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantDataKHR, true, true, IR(479, 3), IR(11253, 16), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantDataKHR, true, true, IR(479, 3), IR(37290, 20), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpPoisonKHR, true, true, IR(39, 2), IR(37310, 10), IR(0, 0), IR(173, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpFreezeKHR, true, true, IR(160, 3), IR(37320, 10), IR(0, 0), IR(173, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpHitObjectRecordHitMotionNV, false, false, IR(482, 14), IR(37330, 27), IR(0, 0), IR(262, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitWithIndexMotionNV, false, false, IR(496, 13), IR(37357, 36), IR(0, 0), IR(262, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissMotionNV, false, false, IR(509, 7), IR(37393, 28), IR(0, 0), IR(262, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldToObjectNV, true, true, IR(160, 3), IR(37421, 28), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectToWorldNV, true, true, IR(160, 3), IR(37449, 28), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayDirectionNV, true, true, IR(160, 3), IR(37477, 33), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayOriginNV, true, true, IR(160, 3), IR(37510, 30), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayMotionNV, false, false, IR(496, 13), IR(37540, 26), IR(0, 0), IR(262, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderRecordBufferHandleNV, true, true, IR(160, 3), IR(37566, 39), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderBindingTableRecordIndexNV, true, true, IR(160, 3), IR(37605, 44), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordEmptyNV, false, false, IR(10, 1), IR(37649, 23), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayNV, false, false, IR(516, 12), IR(37672, 20), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitNV, false, false, IR(496, 13), IR(37692, 21), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitWithIndexNV, false, false, IR(516, 12), IR(37713, 30), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissNV, false, false, IR(528, 6), IR(37743, 22), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectExecuteShaderNV, false, false, IR(36, 2), IR(37765, 25), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetCurrentTimeNV, true, true, IR(160, 3), IR(37790, 26), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetAttributesNV, false, false, IR(36, 2), IR(37816, 25), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetHitKindNV, true, true, IR(160, 3), IR(37841, 22), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetPrimitiveIndexNV, true, true, IR(160, 3), IR(37863, 29), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetGeometryIndexNV, true, true, IR(160, 3), IR(37892, 28), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceIdNV, true, true, IR(160, 3), IR(37920, 25), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceCustomIndexNV, true, true, IR(160, 3), IR(37945, 34), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayDirectionNV, true, true, IR(160, 3), IR(37979, 32), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayOriginNV, true, true, IR(160, 3), IR(38011, 29), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMaxNV, true, true, IR(160, 3), IR(38040, 22), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMinNV, true, true, IR(160, 3), IR(38062, 22), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsEmptyNV, true, true, IR(160, 3), IR(38084, 19), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsHitNV, true, true, IR(160, 3), IR(38103, 17), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsMissNV, true, true, IR(160, 3), IR(38120, 18), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHitObjectNV, false, false, IR(534, 3), IR(38138, 29), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHintNV, false, false, IR(36, 2), IR(38167, 24), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeHitObjectNV, true, false, IR(68, 1), IR(38191, 16), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpImageSampleFootprintNV, true, true, IR(537, 7), IR(38207, 23), IR(0, 0), IR(264, 1), IR(77, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpTypeVectorIdEXT, true, false, IR(89, 3), IR(38230, 16), IR(180, 1), IR(265, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeVectorMatrixMulNV, true, true, IR(544, 13), IR(38270, 29), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorOuterProductAccumulateNV, false, false, IR(557, 7), IR(38299, 42), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorReduceSumAccumulateNV, false, false, IR(33, 3), IR(38341, 39), IR(0, 0), IR(268, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorMatrixMulAddNV, true, true, IR(564, 16), IR(38380, 32), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixConvertNV, true, true, IR(160, 3), IR(38412, 27), IR(0, 0), IR(269, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpEmitMeshTasksEXT, false, false, IR(580, 4), IR(38439, 17), IR(0, 0), IR(54, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSetMeshOutputsEXT, false, false, IR(36, 2), IR(38456, 18), IR(0, 0), IR(54, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpGroupNonUniformPartitionEXT, true, true, IR(160, 3), IR(38474, 28), IR(181, 1), IR(194, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpWritePackedPrimitiveIndices4x8NV, false, false, IR(36, 2), IR(38529, 33), IR(0, 0), IR(51, 1), IR(18, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFetchMicroTriangleVertexPositionNV, true, true, IR(325, 7), IR(38562, 35), IR(0, 0), IR(270, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFetchMicroTriangleVertexBarycentricNV, true, true, IR(325, 7), IR(38597, 38), IR(0, 0), IR(270, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorLoadNV, true, true, IR(584, 5), IR(38635, 24), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeVectorStoreNV, false, false, IR(589, 4), IR(38659, 25), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpHitObjectRecordFromQueryEXT, false, false, IR(593, 5), IR(38684, 28), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissEXT, false, false, IR(509, 7), IR(38712, 23), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissMotionEXT, false, false, IR(471, 8), IR(38735, 29), IR(0, 0), IR(271, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetIntersectionTriangleVertexPositionsEXT, true, true, IR(160, 3), IR(38764, 51), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayFlagsEXT, true, true, IR(160, 3), IR(38815, 24), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectSetShaderBindingTableRecordIndexEXT, false, false, IR(36, 2), IR(38839, 45), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectReorderExecuteShaderEXT, false, false, IR(598, 4), IR(38884, 33), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceReorderExecuteEXT, false, false, IR(602, 14), IR(38917, 32), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceMotionReorderExecuteEXT, false, false, IR(616, 15), IR(38949, 38), IR(0, 0), IR(271, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeHitObjectEXT, true, false, IR(68, 1), IR(38987, 17), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpReorderThreadWithHintEXT, false, false, IR(36, 2), IR(39004, 25), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHitObjectEXT, false, false, IR(534, 3), IR(39029, 30), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayEXT, false, false, IR(516, 12), IR(39059, 21), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayMotionEXT, false, false, IR(496, 13), IR(39080, 27), IR(0, 0), IR(271, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordEmptyEXT, false, false, IR(10, 1), IR(39107, 24), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectExecuteShaderEXT, false, false, IR(36, 2), IR(39131, 26), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetCurrentTimeEXT, true, true, IR(160, 3), IR(39157, 27), IR(0, 0), IR(271, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetAttributesEXT, false, false, IR(36, 2), IR(39184, 26), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetHitKindEXT, true, true, IR(160, 3), IR(39210, 23), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetPrimitiveIndexEXT, true, true, IR(160, 3), IR(39233, 30), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetGeometryIndexEXT, true, true, IR(160, 3), IR(39263, 29), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceIdEXT, true, true, IR(160, 3), IR(39292, 26), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceCustomIndexEXT, true, true, IR(160, 3), IR(39318, 35), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayOriginEXT, true, true, IR(160, 3), IR(39353, 31), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayDirectionEXT, true, true, IR(160, 3), IR(39384, 34), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayDirectionEXT, true, true, IR(160, 3), IR(39418, 33), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayOriginEXT, true, true, IR(160, 3), IR(39451, 30), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectToWorldEXT, true, true, IR(160, 3), IR(39481, 29), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldToObjectEXT, true, true, IR(160, 3), IR(39510, 29), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMaxEXT, true, true, IR(160, 3), IR(39539, 23), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReportIntersectionKHR, true, true, IR(172, 4), IR(39562, 22), IR(182, 1), IR(55, 2), IR(24, 2), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIgnoreIntersectionNV, false, false, IR(0, 0), IR(39605, 21), IR(0, 0), IR(57, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTerminateRayNV, false, false, IR(0, 0), IR(39626, 15), IR(0, 0), IR(57, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceNV, false, false, IR(426, 11), IR(39641, 8), IR(0, 0), IR(57, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceMotionNV, false, false, IR(516, 12), IR(39649, 14), IR(0, 0), IR(58, 1), IR(27, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceRayMotionNV, false, false, IR(516, 12), IR(39663, 17), IR(0, 0), IR(58, 1), IR(27, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTriangleVertexPositionsKHR, true, true, IR(172, 4), IR(39680, 50), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeAccelerationStructureKHR, true, false, IR(68, 1), IR(39730, 29), IR(183, 1), IR(274, 4), IR(209, 4), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpExecuteCallableNV, false, false, IR(36, 2), IR(39787, 18), IR(0, 0), IR(57, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionClusterIdNV, true, true, IR(172, 4), IR(39805, 35), IR(184, 1), IR(65, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetClusterIdNV, true, true, IR(160, 3), IR(39863, 24), IR(0, 0), IR(65, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMinEXT, true, true, IR(160, 3), IR(39887, 23), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderBindingTableRecordIndexEXT, true, true, IR(160, 3), IR(39910, 45), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderRecordBufferHandleEXT, true, true, IR(160, 3), IR(39955, 40), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsEmptyEXT, true, true, IR(160, 3), IR(39995, 20), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsHitEXT, true, true, IR(160, 3), IR(40015, 18), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsMissEXT, true, true, IR(160, 3), IR(40033, 19), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeCooperativeMatrixNV, true, false, IR(631, 5), IR(40052, 24), IR(0, 0), IR(278, 1), IR(85, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeMatrixLoadNV, true, true, IR(636, 6), IR(40076, 24), IR(0, 0), IR(278, 1), IR(85, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixStoreNV, false, false, IR(642, 5), IR(40100, 25), IR(0, 0), IR(278, 1), IR(85, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixMulAddNV, true, true, IR(130, 5), IR(40125, 26), IR(0, 0), IR(278, 1), IR(85, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixLengthNV, true, true, IR(160, 3), IR(40151, 26), IR(0, 0), IR(278, 1), IR(85, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpBeginInvocationInterlockEXT, false, false, IR(0, 0), IR(40177, 28), IR(0, 0), IR(279, 3), IR(86, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpEndInvocationInterlockEXT, false, false, IR(0, 0), IR(40205, 26), IR(0, 0), IR(279, 3), IR(86, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixReduceNV, true, true, IR(647, 5), IR(40274, 26), IR(0, 0), IR(282, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpCooperativeMatrixLoadTensorNV, true, true, IR(652, 7), IR(40375, 30), IR(0, 0), IR(212, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixStoreTensorNV, false, false, IR(659, 5), IR(40405, 31), IR(0, 0), IR(212, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixPerElementOpNV, true, true, IR(151, 5), IR(40436, 32), IR(0, 0), IR(283, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpTypeTensorLayoutNV, true, false, IR(89, 3), IR(40468, 19), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeTensorViewNV, true, false, IR(664, 4), IR(40487, 17), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCreateTensorLayoutNV, true, true, IR(39, 2), IR(40504, 21), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetDimensionNV, true, true, IR(122, 4), IR(40525, 27), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetStrideNV, true, true, IR(122, 4), IR(40552, 24), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSliceNV, true, true, IR(122, 4), IR(40576, 20), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetClampValueNV, true, true, IR(172, 4), IR(40596, 28), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCreateTensorViewNV, true, true, IR(39, 2), IR(40624, 19), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetDimensionNV, true, true, IR(122, 4), IR(40643, 25), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetStrideNV, true, true, IR(122, 4), IR(40668, 22), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpDemoteToHelperInvocation, false, false, IR(0, 0), IR(12784, 25), IR(46, 1), IR(285, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpIsHelperInvocationEXT, true, true, IR(39, 2), IR(40690, 22), IR(0, 0), IR(285, 1), IR(87, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetClipNV, true, true, IR(325, 7), IR(40712, 20), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetBlockSizeNV, true, true, IR(122, 4), IR(40732, 27), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixTransposeNV, true, true, IR(160, 3), IR(40759, 29), IR(0, 0), IR(269, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToImageNV, true, true, IR(160, 3), IR(40788, 18), IR(0, 0), IR(135, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToSamplerNV, true, true, IR(160, 3), IR(40806, 20), IR(0, 0), IR(135, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertImageToUNV, true, true, IR(160, 3), IR(40826, 18), IR(0, 0), IR(135, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertSamplerToUNV, true, true, IR(160, 3), IR(40844, 20), IR(0, 0), IR(135, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToSampledImageNV, true, true, IR(160, 3), IR(40864, 25), IR(0, 0), IR(135, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertSampledImageToUNV, true, true, IR(160, 3), IR(40889, 25), IR(0, 0), IR(135, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSamplerImageAddressingModeNV, false, false, IR(0, 1), IR(40914, 29), IR(0, 0), IR(135, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRawAccessChainNV, true, true, IR(668, 7), IR(40995, 17), IR(0, 0), IR(201, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpRayQueryGetIntersectionSpherePositionNV, true, true, IR(172, 4), IR(41012, 40), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionSphereRadiusNV, true, true, IR(172, 4), IR(41052, 38), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSPositionsNV, true, true, IR(172, 4), IR(41090, 38), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSRadiiNV, true, true, IR(172, 4), IR(41128, 34), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSHitValueNV, true, true, IR(172, 4), IR(41162, 37), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetSpherePositionNV, true, true, IR(160, 3), IR(41199, 29), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetSphereRadiusNV, true, true, IR(160, 3), IR(41228, 27), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetLSSPositionsNV, true, true, IR(160, 3), IR(41255, 27), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetLSSRadiiNV, true, true, IR(160, 3), IR(41282, 23), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsSphereHitNV, true, true, IR(160, 3), IR(41305, 23), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsLSSHitNV, true, true, IR(160, 3), IR(41328, 20), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryIsSphereHitNV, true, true, IR(172, 4), IR(41348, 22), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryIsLSSHitNV, true, true, IR(172, 4), IR(41370, 19), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSubgroupShuffleINTEL, true, true, IR(172, 4), IR(13377, 21), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleDownINTEL, true, true, IR(130, 5), IR(41389, 25), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleUpINTEL, true, true, IR(130, 5), IR(41414, 23), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleXorINTEL, true, true, IR(172, 4), IR(41437, 24), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupBlockReadINTEL, true, true, IR(160, 3), IR(41461, 23), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupBlockWriteINTEL, false, false, IR(36, 2), IR(41484, 24), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageBlockReadINTEL, true, true, IR(172, 4), IR(41508, 28), IR(0, 0), IR(288, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageBlockWriteINTEL, false, false, IR(33, 3), IR(41536, 29), IR(0, 0), IR(288, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageMediaBlockReadINTEL, true, true, IR(215, 6), IR(41565, 33), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageMediaBlockWriteINTEL, false, false, IR(675, 5), IR(41598, 34), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpUCountLeadingZerosINTEL, true, true, IR(160, 3), IR(41632, 24), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUCountTrailingZerosINTEL, true, true, IR(160, 3), IR(41656, 25), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAbsISubINTEL, true, true, IR(172, 4), IR(41681, 13), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAbsUSubINTEL, true, true, IR(172, 4), IR(41694, 13), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAddSatINTEL, true, true, IR(172, 4), IR(41707, 13), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAddSatINTEL, true, true, IR(172, 4), IR(41720, 13), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAverageINTEL, true, true, IR(172, 4), IR(41733, 14), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAverageINTEL, true, true, IR(172, 4), IR(41747, 14), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAverageRoundedINTEL, true, true, IR(172, 4), IR(41761, 21), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAverageRoundedINTEL, true, true, IR(172, 4), IR(41782, 21), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpISubSatINTEL, true, true, IR(172, 4), IR(41803, 13), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUSubSatINTEL, true, true, IR(172, 4), IR(41816, 13), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIMul32x16INTEL, true, true, IR(172, 4), IR(41829, 15), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUMul32x16INTEL, true, true, IR(172, 4), IR(41844, 15), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConstantFunctionPointerINTEL, true, true, IR(160, 3), IR(41859, 29), IR(0, 0), IR(210, 1), IR(107, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFunctionPointerCallINTEL, true, true, IR(107, 3), IR(41888, 25), IR(0, 0), IR(210, 1), IR(107, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmTargetINTEL, true, false, IR(50, 2), IR(41913, 15), IR(0, 0), IR(138, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmINTEL, true, true, IR(680, 6), IR(13595, 9), IR(0, 0), IR(138, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmCallINTEL, true, true, IR(122, 4), IR(41928, 13), IR(0, 0), IR(138, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAtomicFMinEXT, true, true, IR(235, 6), IR(41941, 14), IR(0, 0), IR(291, 4), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicFMaxEXT, true, true, IR(235, 6), IR(41955, 14), IR(0, 0), IR(291, 4), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAssumeTrueKHR, false, false, IR(10, 1), IR(41969, 14), IR(0, 0), IR(295, 1), IR(111, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpExpectKHR, true, true, IR(172, 4), IR(41983, 10), IR(0, 0), IR(295, 1), IR(111, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpDecorateString, false, false, IR(163, 2), IR(41993, 15), IR(185, 1), IR(1, 0), IR(213, 2), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpMemberDecorateString, false, false, IR(165, 3), IR(42029, 21), IR(186, 1), IR(1, 0), IR(213, 2), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpVmeImageINTEL, true, true, IR(172, 4), IR(42077, 14), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeVmeImageINTEL, true, false, IR(87, 2), IR(42091, 18), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImePayloadINTEL, true, false, IR(68, 1), IR(42109, 23), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcRefPayloadINTEL, true, false, IR(68, 1), IR(42132, 23), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcSicPayloadINTEL, true, false, IR(68, 1), IR(42155, 23), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcMcePayloadINTEL, true, false, IR(68, 1), IR(42178, 23), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcMceResultINTEL, true, false, IR(68, 1), IR(42201, 22), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultINTEL, true, false, IR(68, 1), IR(42223, 22), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultSingleReferenceStreamoutINTEL, true, false, IR(68, 1), IR(42245, 46), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultDualReferenceStreamoutINTEL, true, false, IR(68, 1), IR(42291, 44), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeSingleReferenceStreaminINTEL, true, false, IR(68, 1), IR(42335, 39), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeDualReferenceStreaminINTEL, true, false, IR(68, 1), IR(42374, 37), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcRefResultINTEL, true, false, IR(68, 1), IR(42411, 22), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcSicResultINTEL, true, false, IR(68, 1), IR(42433, 22), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL, true, true, IR(172, 4), IR(42455, 60), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL, true, true, IR(172, 4), IR(42515, 53), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterShapePenaltyINTEL, true, true, IR(172, 4), IR(42568, 47), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterShapePenaltyINTEL, true, true, IR(172, 4), IR(42615, 40), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL, true, true, IR(172, 4), IR(42655, 51), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterDirectionPenaltyINTEL, true, true, IR(172, 4), IR(42706, 44), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL, true, true, IR(172, 4), IR(42750, 51), IR(0, 0), IR(297, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL, true, true, IR(172, 4), IR(42801, 56), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL, true, true, IR(39, 2), IR(42857, 50), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL, true, true, IR(39, 2), IR(42907, 52), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL, true, true, IR(39, 2), IR(42959, 49), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetMotionVectorCostFunctionINTEL, true, true, IR(215, 6), IR(43008, 47), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL, true, true, IR(172, 4), IR(43055, 50), IR(0, 0), IR(297, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL, true, true, IR(39, 2), IR(43105, 51), IR(0, 0), IR(297, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL, true, true, IR(39, 2), IR(43156, 56), IR(0, 0), IR(299, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetAcOnlyHaarINTEL, true, true, IR(160, 3), IR(43212, 33), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL, true, true, IR(172, 4), IR(43245, 52), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL, true, true, IR(172, 4), IR(43297, 61), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL, true, true, IR(130, 5), IR(43358, 61), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToImePayloadINTEL, true, true, IR(160, 3), IR(43419, 39), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToImeResultINTEL, true, true, IR(160, 3), IR(43458, 38), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToRefPayloadINTEL, true, true, IR(160, 3), IR(43496, 39), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToRefResultINTEL, true, true, IR(160, 3), IR(43535, 38), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToSicPayloadINTEL, true, true, IR(160, 3), IR(43573, 39), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToSicResultINTEL, true, true, IR(160, 3), IR(43612, 38), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetMotionVectorsINTEL, true, true, IR(160, 3), IR(43650, 36), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterDistortionsINTEL, true, true, IR(160, 3), IR(43686, 39), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetBestInterDistortionsINTEL, true, true, IR(160, 3), IR(43725, 43), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMajorShapeINTEL, true, true, IR(160, 3), IR(43768, 38), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMinorShapeINTEL, true, true, IR(160, 3), IR(43806, 38), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterDirectionsINTEL, true, true, IR(160, 3), IR(43844, 38), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMotionVectorCountINTEL, true, true, IR(160, 3), IR(43882, 45), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterReferenceIdsINTEL, true, true, IR(160, 3), IR(43927, 40), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL, true, true, IR(130, 5), IR(43967, 62), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeInitializeINTEL, true, true, IR(130, 5), IR(44029, 30), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetSingleReferenceINTEL, true, true, IR(130, 5), IR(44059, 38), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetDualReferenceINTEL, true, true, IR(215, 6), IR(44097, 36), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeRefWindowSizeINTEL, true, true, IR(172, 4), IR(44133, 33), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeAdjustRefOffsetINTEL, true, true, IR(215, 6), IR(44166, 35), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(44201, 39), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetMaxMotionVectorCountINTEL, true, true, IR(172, 4), IR(44240, 43), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetUnidirectionalMixDisableINTEL, true, true, IR(160, 3), IR(44283, 47), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetEarlySearchTerminationThresholdINTEL, true, true, IR(172, 4), IR(44330, 54), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetWeightedSadINTEL, true, true, IR(172, 4), IR(44384, 34), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(44418, 47), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(44465, 45), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL, true, true, IR(215, 6), IR(44510, 55), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL, true, true, IR(325, 7), IR(44565, 53), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL, true, true, IR(130, 5), IR(44618, 56), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL, true, true, IR(215, 6), IR(44674, 54), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL, true, true, IR(215, 6), IR(44728, 58), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL, true, true, IR(325, 7), IR(44786, 56), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeConvertToMceResultINTEL, true, true, IR(160, 3), IR(44842, 38), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetSingleReferenceStreaminINTEL, true, true, IR(160, 3), IR(44880, 46), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetDualReferenceStreaminINTEL, true, true, IR(160, 3), IR(44926, 44), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeStripSingleReferenceStreamoutINTEL, true, true, IR(160, 3), IR(44970, 49), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeStripDualReferenceStreamoutINTEL, true, true, IR(160, 3), IR(45019, 47), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL, true, true, IR(172, 4), IR(45066, 70), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL, true, true, IR(172, 4), IR(45136, 68), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL, true, true, IR(172, 4), IR(45204, 69), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL, true, true, IR(130, 5), IR(45273, 68), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL, true, true, IR(130, 5), IR(45341, 66), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL, true, true, IR(130, 5), IR(45407, 67), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetBorderReachedINTEL, true, true, IR(172, 4), IR(45474, 36), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetTruncatedSearchIndicationINTEL, true, true, IR(160, 3), IR(45510, 48), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL, true, true, IR(160, 3), IR(45558, 59), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL, true, true, IR(160, 3), IR(45617, 58), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL, true, true, IR(160, 3), IR(45675, 56), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcFmeInitializeINTEL, true, true, IR(686, 9), IR(45731, 30), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcBmeInitializeINTEL, true, true, IR(695, 10), IR(45761, 30), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(45791, 39), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefSetBidirectionalMixDisableINTEL, true, true, IR(160, 3), IR(45830, 46), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefSetBilinearFilterEnableINTEL, true, true, IR(160, 3), IR(45876, 43), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(45919, 47), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(45966, 45), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithMultiReferenceINTEL, true, true, IR(130, 5), IR(46011, 46), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL, true, true, IR(215, 6), IR(46057, 56), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefConvertToMceResultINTEL, true, true, IR(160, 3), IR(46113, 38), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicInitializeINTEL, true, true, IR(160, 3), IR(46151, 30), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureSkcINTEL, true, true, IR(288, 8), IR(46181, 32), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureIpeLumaINTEL, true, true, IR(695, 10), IR(46213, 36), IR(0, 0), IR(297, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureIpeLumaChromaINTEL, true, true, IR(705, 13), IR(46249, 42), IR(0, 0), IR(299, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetMotionVectorMaskINTEL, true, true, IR(172, 4), IR(46291, 39), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(46330, 39), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraLumaShapePenaltyINTEL, true, true, IR(172, 4), IR(46369, 44), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraLumaModeCostFunctionINTEL, true, true, IR(215, 6), IR(46413, 48), IR(0, 0), IR(297, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraChromaModeCostFunctionINTEL, true, true, IR(172, 4), IR(46461, 50), IR(0, 0), IR(299, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetBilinearFilterEnableINTEL, true, true, IR(160, 3), IR(46511, 43), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetSkcForwardTransformEnableINTEL, true, true, IR(172, 4), IR(46554, 48), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetBlockBasedRawSkipSadINTEL, true, true, IR(172, 4), IR(46602, 43), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateIpeINTEL, true, true, IR(172, 4), IR(46645, 31), IR(0, 0), IR(297, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(46676, 47), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(46723, 45), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithMultiReferenceINTEL, true, true, IR(130, 5), IR(46768, 46), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL, true, true, IR(215, 6), IR(46814, 56), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConvertToMceResultINTEL, true, true, IR(160, 3), IR(46870, 38), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetIpeLumaShapeINTEL, true, true, IR(160, 3), IR(46908, 35), IR(0, 0), IR(297, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetBestIpeLumaDistortionINTEL, true, true, IR(160, 3), IR(46943, 44), IR(0, 0), IR(297, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetBestIpeChromaDistortionINTEL, true, true, IR(160, 3), IR(46987, 46), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedIpeLumaModesINTEL, true, true, IR(160, 3), IR(47033, 41), IR(0, 0), IR(297, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetIpeChromaModeINTEL, true, true, IR(160, 3), IR(47074, 36), IR(0, 0), IR(299, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL, true, true, IR(160, 3), IR(47110, 50), IR(0, 0), IR(297, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL, true, true, IR(160, 3), IR(47160, 48), IR(0, 0), IR(297, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetInterRawSadsINTEL, true, true, IR(160, 3), IR(47208, 35), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpVariableLengthArrayINTEL, true, true, IR(160, 3), IR(13833, 25), IR(0, 0), IR(301, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpSaveMemoryINTEL, true, true, IR(39, 2), IR(47243, 16), IR(0, 0), IR(301, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpRestoreMemoryINTEL, false, false, IR(10, 1), IR(47259, 19), IR(0, 0), IR(301, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpArbitraryFloatSinCosPiALTERA, true, true, IR(718, 8), IR(47278, 29), IR(187, 1), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastALTERA, true, true, IR(718, 8), IR(47335, 25), IR(188, 1), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastFromIntALTERA, true, true, IR(718, 8), IR(47384, 32), IR(189, 1), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastToIntALTERA, true, true, IR(718, 8), IR(47447, 30), IR(190, 1), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatAddALTERA, true, true, IR(726, 10), IR(47506, 24), IR(191, 1), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSubALTERA, true, true, IR(726, 10), IR(47553, 24), IR(192, 1), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatMulALTERA, true, true, IR(726, 10), IR(47600, 24), IR(193, 1), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatDivALTERA, true, true, IR(726, 10), IR(47647, 24), IR(194, 1), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatGTALTERA, true, true, IR(736, 6), IR(47694, 23), IR(195, 1), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatGEALTERA, true, true, IR(736, 6), IR(47739, 23), IR(196, 1), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLTALTERA, true, true, IR(736, 6), IR(47784, 23), IR(197, 1), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLEALTERA, true, true, IR(736, 6), IR(47829, 23), IR(198, 1), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatEQALTERA, true, true, IR(736, 6), IR(47874, 23), IR(199, 1), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatRecipALTERA, true, true, IR(718, 8), IR(47919, 26), IR(200, 1), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatRSqrtALTERA, true, true, IR(718, 8), IR(47970, 26), IR(201, 1), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCbrtALTERA, true, true, IR(718, 8), IR(48021, 25), IR(202, 1), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatHypotALTERA, true, true, IR(726, 10), IR(48070, 26), IR(203, 1), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSqrtALTERA, true, true, IR(718, 8), IR(48121, 25), IR(204, 1), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLogINTEL, true, true, IR(718, 8), IR(48170, 23), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog2INTEL, true, true, IR(718, 8), IR(48193, 24), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog10INTEL, true, true, IR(718, 8), IR(48217, 25), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog1pINTEL, true, true, IR(718, 8), IR(48242, 25), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExpINTEL, true, true, IR(718, 8), IR(48267, 23), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExp2INTEL, true, true, IR(718, 8), IR(48290, 24), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExp10INTEL, true, true, IR(718, 8), IR(48314, 25), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExpm1INTEL, true, true, IR(718, 8), IR(48339, 25), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinINTEL, true, true, IR(718, 8), IR(48364, 23), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCosINTEL, true, true, IR(718, 8), IR(48387, 23), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinCosINTEL, true, true, IR(718, 8), IR(48410, 26), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinPiINTEL, true, true, IR(718, 8), IR(48436, 25), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCosPiINTEL, true, true, IR(718, 8), IR(48461, 25), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatASinINTEL, true, true, IR(718, 8), IR(48486, 24), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatASinPiINTEL, true, true, IR(718, 8), IR(48510, 26), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatACosINTEL, true, true, IR(718, 8), IR(48536, 24), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatACosPiINTEL, true, true, IR(718, 8), IR(48560, 26), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATanINTEL, true, true, IR(718, 8), IR(48586, 24), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATanPiINTEL, true, true, IR(718, 8), IR(48610, 26), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATan2INTEL, true, true, IR(726, 10), IR(48636, 25), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowINTEL, true, true, IR(726, 10), IR(48661, 23), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowRINTEL, true, true, IR(726, 10), IR(48684, 24), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowNINTEL, true, true, IR(726, 10), IR(48708, 24), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpLoopControlINTEL, false, false, IR(18, 1), IR(48732, 17), IR(0, 0), IR(303, 1), IR(121, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAliasDomainDeclINTEL, true, false, IR(742, 2), IR(48749, 21), IR(0, 0), IR(144, 1), IR(133, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAliasScopeDeclINTEL, true, false, IR(744, 3), IR(48770, 20), IR(0, 0), IR(144, 1), IR(133, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAliasScopeListDeclINTEL, true, false, IR(92, 2), IR(48790, 24), IR(0, 0), IR(144, 1), IR(133, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSqrtALTERA, true, true, IR(718, 8), IR(48814, 16), IR(205, 1), IR(200, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedRecipALTERA, true, true, IR(718, 8), IR(48845, 17), IR(206, 1), IR(200, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedRsqrtALTERA, true, true, IR(718, 8), IR(48878, 17), IR(207, 1), IR(200, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinALTERA, true, true, IR(718, 8), IR(48911, 15), IR(208, 1), IR(200, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedCosALTERA, true, true, IR(718, 8), IR(48940, 15), IR(209, 1), IR(200, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinCosALTERA, true, true, IR(718, 8), IR(48969, 18), IR(210, 1), IR(200, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinPiALTERA, true, true, IR(718, 8), IR(49004, 17), IR(211, 1), IR(200, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedCosPiALTERA, true, true, IR(718, 8), IR(49037, 17), IR(212, 1), IR(200, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinCosPiALTERA, true, true, IR(718, 8), IR(49070, 20), IR(213, 1), IR(200, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedLogALTERA, true, true, IR(718, 8), IR(49109, 15), IR(214, 1), IR(200, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedExpALTERA, true, true, IR(718, 8), IR(49138, 15), IR(215, 1), IR(200, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpPtrCastToCrossWorkgroupALTERA, true, true, IR(160, 3), IR(49167, 30), IR(216, 1), IR(211, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpCrossWorkgroupCastToPtrALTERA, true, true, IR(160, 3), IR(49226, 30), IR(217, 1), IR(211, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpReadPipeBlockingALTERA, false, false, IR(296, 4), IR(49285, 23), IR(218, 1), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpWritePipeBlockingALTERA, false, false, IR(296, 4), IR(49330, 24), IR(219, 1), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFPGARegALTERA, true, true, IR(160, 3), IR(14791, 14), IR(63, 1), IR(305, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpRayQueryGetRayTMinKHR, true, true, IR(160, 3), IR(49377, 22), IR(0, 0), IR(204, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetRayFlagsKHR, true, true, IR(160, 3), IR(49399, 23), IR(0, 0), IR(204, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTKHR, true, true, IR(172, 4), IR(49422, 28), IR(0, 0), IR(204, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceCustomIndexKHR, true, true, IR(172, 4), IR(49450, 46), IR(0, 0), IR(204, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceIdKHR, true, true, IR(172, 4), IR(49496, 37), IR(0, 0), IR(204, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR, true, true, IR(172, 4), IR(49533, 65), IR(0, 0), IR(204, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionGeometryIndexKHR, true, true, IR(172, 4), IR(49598, 40), IR(0, 0), IR(204, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionPrimitiveIndexKHR, true, true, IR(172, 4), IR(49638, 41), IR(0, 0), IR(204, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionBarycentricsKHR, true, true, IR(172, 4), IR(49679, 39), IR(0, 0), IR(204, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionFrontFaceKHR, true, true, IR(172, 4), IR(49718, 36), IR(0, 0), IR(204, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionCandidateAABBOpaqueKHR, true, true, IR(160, 3), IR(49754, 46), IR(0, 0), IR(204, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectRayDirectionKHR, true, true, IR(172, 4), IR(49800, 45), IR(0, 0), IR(204, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectRayOriginKHR, true, true, IR(172, 4), IR(49845, 42), IR(0, 0), IR(204, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetWorldRayDirectionKHR, true, true, IR(160, 3), IR(49887, 32), IR(0, 0), IR(204, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetWorldRayOriginKHR, true, true, IR(160, 3), IR(49919, 29), IR(0, 0), IR(204, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectToWorldKHR, true, true, IR(172, 4), IR(49948, 40), IR(0, 0), IR(204, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionWorldToObjectKHR, true, true, IR(172, 4), IR(49988, 40), IR(0, 0), IR(204, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAtomicFAddEXT, true, true, IR(235, 6), IR(50028, 14), IR(0, 0), IR(306, 4), IR(158, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpTypeBufferSurfaceINTEL, true, false, IR(100, 2), IR(50042, 23), IR(0, 0), IR(136, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeStructContinuedINTEL, false, false, IR(747, 1), IR(50065, 25), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantCompositeContinuedINTEL, false, false, IR(747, 1), IR(50090, 32), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCompositeContinuedINTEL, false, false, IR(747, 1), IR(50122, 36), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpCompositeConstructContinuedINTEL, false, false, IR(747, 1), IR(50158, 33), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpConvertFToBF16INTEL, true, true, IR(160, 3), IR(50191, 20), IR(0, 0), IR(311, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertBF16ToFINTEL, true, true, IR(160, 3), IR(50211, 20), IR(0, 0), IR(311, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpControlBarrierArriveEXT, false, false, IR(221, 3), IR(50231, 24), IR(220, 1), IR(312, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpControlBarrierWaitEXT, false, false, IR(221, 3), IR(50281, 22), IR(221, 1), IR(312, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpArithmeticFenceEXT, true, true, IR(160, 3), IR(15302, 19), IR(0, 0), IR(313, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpTaskSequenceCreateALTERA, true, true, IR(748, 7), IR(50327, 25), IR(222, 1), IR(314, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTaskSequenceAsyncALTERA, false, false, IR(168, 2), IR(50376, 24), IR(223, 1), IR(314, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTaskSequenceGetALTERA, true, true, IR(160, 3), IR(50423, 22), IR(224, 1), IR(314, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTaskSequenceReleaseALTERA, false, false, IR(10, 1), IR(50466, 26), IR(225, 1), IR(314, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeTaskSequenceALTERA, true, false, IR(68, 1), IR(50517, 23), IR(226, 1), IR(314, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupBlockPrefetchINTEL, false, false, IR(139, 3), IR(50562, 27), IR(0, 0), IR(315, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadINTEL, false, false, IR(755, 10), IR(50589, 25), IR(0, 0), IR(112, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadTransformINTEL, false, false, IR(755, 10), IR(50614, 34), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadTransposeINTEL, false, false, IR(755, 10), IR(50648, 34), IR(0, 0), IR(317, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockPrefetchINTEL, false, false, IR(765, 9), IR(50682, 29), IR(0, 0), IR(112, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockStoreINTEL, false, false, IR(755, 10), IR(50711, 26), IR(0, 0), IR(112, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupMatrixMultiplyAccumulateINTEL, true, true, IR(774, 7), IR(15779, 38), IR(0, 0), IR(318, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpBitwiseFunctionINTEL, true, true, IR(215, 6), IR(50799, 21), IR(0, 0), IR(319, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpUntypedVariableLengthArrayINTEL, true, true, IR(172, 4), IR(15845, 32), IR(0, 0), IR(320, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpConditionalExtensionINTEL, false, false, IR(45, 2), IR(50820, 26), IR(0, 0), IR(115, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpConditionalEntryPointINTEL, false, false, IR(781, 5), IR(50846, 27), IR(0, 0), IR(115, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpConditionalCapabilityINTEL, false, false, IR(786, 2), IR(50873, 27), IR(0, 0), IR(115, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpSpecConstantTargetINTEL, true, true, IR(788, 4), IR(50900, 24), IR(0, 0), IR(321, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantArchitectureINTEL, true, true, IR(792, 6), IR(50924, 30), IR(0, 0), IR(321, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCapabilitiesINTEL, true, true, IR(798, 3), IR(50991, 30), IR(0, 0), IR(321, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConditionalCopyObjectINTEL, true, true, IR(107, 3), IR(51021, 27), IR(0, 0), IR(115, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpPredicatedLoadINTEL, true, true, IR(636, 6), IR(51048, 20), IR(0, 0), IR(322, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPredicatedStoreINTEL, false, false, IR(589, 4), IR(51068, 21), IR(0, 0), IR(322, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpGroupIMulKHR, true, true, IR(283, 5), IR(51089, 13), IR(0, 0), IR(323, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMulKHR, true, true, IR(283, 5), IR(51102, 13), IR(0, 0), IR(323, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseAndKHR, true, true, IR(283, 5), IR(51115, 19), IR(0, 0), IR(323, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseOrKHR, true, true, IR(283, 5), IR(51134, 18), IR(0, 0), IR(323, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseXorKHR, true, true, IR(283, 5), IR(51152, 19), IR(0, 0), IR(323, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalAndKHR, true, true, IR(283, 5), IR(51171, 19), IR(0, 0), IR(323, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalOrKHR, true, true, IR(283, 5), IR(51190, 18), IR(0, 0), IR(323, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalXorKHR, true, true, IR(283, 5), IR(51208, 19), IR(0, 0), IR(323, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpRoundFToTF32INTEL, true, true, IR(160, 3), IR(51227, 18), IR(0, 0), IR(324, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpMaskedGatherINTEL, true, true, IR(801, 6), IR(51245, 18), IR(0, 0), IR(325, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpMaskedScatterINTEL, false, false, IR(807, 4), IR(51263, 19), IR(0, 0), IR(325, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpConvertHandleToImageINTEL, true, true, IR(160, 3), IR(51282, 26), IR(0, 0), IR(326, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertHandleToSamplerINTEL, true, true, IR(160, 3), IR(51308, 28), IR(0, 0), IR(326, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertHandleToSampledImageINTEL, true, true, IR(160, 3), IR(51336, 33), IR(0, 0), IR(326, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpFDot2MixAcc32VALVE, true, true, IR(130, 5), IR(51369, 19), IR(0, 0), IR(327, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFDot2MixAcc16VALVE, true, true, IR(130, 5), IR(51388, 19), IR(0, 0), IR(329, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFDot4MixAcc32VALVE, true, true, IR(130, 5), IR(51407, 19), IR(0, 0), IR(331, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
}};

// Opcode strings (without the 'Op' prefix) and opcode values, ordered by name.
// The fields in order are:
//   name, either the primary name or an alias, indexing into kStrings
//   index into kInstructionDesc
static const std::array<NameIndex, 928> kInstructionNames{{
  {IR(11244, 9), 438}, // 0 AbortKHR
  {IR(41681, 13), 600}, // 1 AbsISubINTEL
  {IR(41694, 13), 601}, // 2 AbsUSubINTEL
  {IR(30270, 12), 58}, // 3 AccessChain
  {IR(48749, 21), 786}, // 4 AliasDomainDeclINTEL
  {IR(48770, 20), 787}, // 5 AliasScopeDeclINTEL
  {IR(48790, 24), 788}, // 6 AliasScopeListDeclINTEL
  {IR(31567, 4), 143}, // 7 All
  {IR(36946, 25), 426}, // 8 AllocateNodePayloadsAMDX
  {IR(31563, 4), 142}, // 9 Any
  {IR(48536, 24), 777}, // 10 ArbitraryFloatACosINTEL
  {IR(48560, 26), 778}, // 11 ArbitraryFloatACosPiINTEL
  {IR(48486, 24), 775}, // 12 ArbitraryFloatASinINTEL
  {IR(48510, 26), 776}, // 13 ArbitraryFloatASinPiINTEL
  {IR(48636, 25), 781}, // 14 ArbitraryFloatATan2INTEL
  {IR(48586, 24), 779}, // 15 ArbitraryFloatATanINTEL
  {IR(48610, 26), 780}, // 16 ArbitraryFloatATanPiINTEL
  {IR(47506, 24), 748}, // 17 ArbitraryFloatAddALTERA
  {IR(47530, 23), 748}, // 18 ArbitraryFloatAddINTEL
  {IR(47335, 25), 745}, // 19 ArbitraryFloatCastALTERA
  {IR(47384, 32), 746}, // 20 ArbitraryFloatCastFromIntALTERA
  {IR(47416, 31), 746}, // 21 ArbitraryFloatCastFromIntINTEL
  {IR(47360, 24), 745}, // 22 ArbitraryFloatCastINTEL
  {IR(47447, 30), 747}, // 23 ArbitraryFloatCastToIntALTERA
  {IR(47477, 29), 747}, // 24 ArbitraryFloatCastToIntINTEL
  {IR(48021, 25), 759}, // 25 ArbitraryFloatCbrtALTERA
  {IR(48046, 24), 759}, // 26 ArbitraryFloatCbrtINTEL
  {IR(48387, 23), 771}, // 27 ArbitraryFloatCosINTEL
  {IR(48461, 25), 774}, // 28 ArbitraryFloatCosPiINTEL
  {IR(47647, 24), 751}, // 29 ArbitraryFloatDivALTERA
  {IR(47671, 23), 751}, // 30 ArbitraryFloatDivINTEL
  {IR(47874, 23), 756}, // 31 ArbitraryFloatEQALTERA
  {IR(47897, 22), 756}, // 32 ArbitraryFloatEQINTEL
  {IR(48314, 25), 768}, // 33 ArbitraryFloatExp10INTEL
  {IR(48290, 24), 767}, // 34 ArbitraryFloatExp2INTEL
  {IR(48267, 23), 766}, // 35 ArbitraryFloatExpINTEL
  {IR(48339, 25), 769}, // 36 ArbitraryFloatExpm1INTEL
  {IR(47739, 23), 753}, // 37 ArbitraryFloatGEALTERA
  {IR(47762, 22), 753}, // 38 ArbitraryFloatGEINTEL
  {IR(47694, 23), 752}, // 39 ArbitraryFloatGTALTERA
  {IR(47717, 22), 752}, // 40 ArbitraryFloatGTINTEL
  {IR(48070, 26), 760}, // 41 ArbitraryFloatHypotALTERA
  {IR(48096, 25), 760}, // 42 ArbitraryFloatHypotINTEL
  {IR(47829, 23), 755}, // 43 ArbitraryFloatLEALTERA
  {IR(47852, 22), 755}, // 44 ArbitraryFloatLEINTEL
  {IR(47784, 23), 754}, // 45 ArbitraryFloatLTALTERA
  {IR(47807, 22), 754}, // 46 ArbitraryFloatLTINTEL
  {IR(48217, 25), 764}, // 47 ArbitraryFloatLog10INTEL
  {IR(48242, 25), 765}, // 48 ArbitraryFloatLog1pINTEL
  {IR(48193, 24), 763}, // 49 ArbitraryFloatLog2INTEL
  {IR(48170, 23), 762}, // 50 ArbitraryFloatLogINTEL
  {IR(47600, 24), 750}, // 51 ArbitraryFloatMulALTERA
  {IR(47624, 23), 750}, // 52 ArbitraryFloatMulINTEL
  {IR(48661, 23), 782}, // 53 ArbitraryFloatPowINTEL
  {IR(48708, 24), 784}, // 54 ArbitraryFloatPowNINTEL
  {IR(48684, 24), 783}, // 55 ArbitraryFloatPowRINTEL
  {IR(47970, 26), 758}, // 56 ArbitraryFloatRSqrtALTERA
  {IR(47996, 25), 758}, // 57 ArbitraryFloatRSqrtINTEL
  {IR(47919, 26), 757}, // 58 ArbitraryFloatRecipALTERA
  {IR(47945, 25), 757}, // 59 ArbitraryFloatRecipINTEL
  {IR(48410, 26), 772}, // 60 ArbitraryFloatSinCosINTEL
  {IR(47278, 29), 744}, // 61 ArbitraryFloatSinCosPiALTERA
  {IR(47307, 28), 744}, // 62 ArbitraryFloatSinCosPiINTEL
  {IR(48364, 23), 770}, // 63 ArbitraryFloatSinINTEL
  {IR(48436, 25), 773}, // 64 ArbitraryFloatSinPiINTEL
  {IR(48121, 25), 761}, // 65 ArbitraryFloatSqrtALTERA
  {IR(48146, 24), 761}, // 66 ArbitraryFloatSqrtINTEL
  {IR(47553, 24), 749}, // 67 ArbitraryFloatSubALTERA
  {IR(47577, 23), 749}, // 68 ArbitraryFloatSubINTEL
  {IR(15302, 19), 832}, // 69 ArithmeticFenceEXT
  {IR(30317, 12), 61}, // 70 ArrayLength
  {IR(41928, 13), 616}, // 71 AsmCallINTEL
  {IR(13595, 9), 615}, // 72 AsmINTEL
  {IR(41913, 15), 614}, // 73 AsmTargetINTEL
  {IR(41969, 14), 619}, // 74 AssumeTrueKHR
  {IR(32589, 10), 220}, // 75 AtomicAnd
  {IR(32441, 22), 210}, // 76 AtomicCompareExchange
  {IR(32463, 26), 211}, // 77 AtomicCompareExchangeWeak
  {IR(32426, 15), 209}, // 78 AtomicExchange
  {IR(50028, 14), 822}, // 79 AtomicFAddEXT
  {IR(41955, 14), 618}, // 80 AtomicFMaxEXT
  {IR(41941, 14), 617}, // 81 AtomicFMinEXT
  {IR(33974, 16), 292}, // 82 AtomicFlagClear
  {IR(33953, 21), 291}, // 83 AtomicFlagTestAndSet
  {IR(32523, 11), 214}, // 84 AtomicIAdd
  {IR(32506, 17), 213}, // 85 AtomicIDecrement
  {IR(32489, 17), 212}, // 86 AtomicIIncrement
  {IR(32534, 11), 215}, // 87 AtomicISub
  {IR(32403, 11), 207}, // 88 AtomicLoad
  {IR(32599, 9), 221}, // 89 AtomicOr
  {IR(32567, 11), 218}, // 90 AtomicSMax
  {IR(32545, 11), 216}, // 91 AtomicSMin
  {IR(32414, 12), 208}, // 92 AtomicStore
  {IR(32578, 11), 219}, // 93 AtomicUMax
  {IR(32556, 11), 217}, // 94 AtomicUMin
  {IR(32608, 10), 222}, // 95 AtomicXor
  {IR(40177, 28), 546}, // 96 BeginInvocationInterlockEXT
  {IR(36500, 17), 407}, // 97 BitCastArrayQCOM
  {IR(32187, 9), 191}, // 98 BitCount
  {IR(32127, 15), 187}, // 99 BitFieldInsert
  {IR(32142, 17), 188}, // 100 BitFieldSExtract
  {IR(32159, 17), 189}, // 101 BitFieldUExtract
  {IR(32176, 11), 190}, // 102 BitReverse
  {IR(31315, 8), 114}, // 103 Bitcast
  {IR(32112, 11), 185}, // 104 BitwiseAnd
  {IR(50799, 21), 845}, // 105 BitwiseFunctionINTEL
  {IR(32091, 10), 183}, // 106 BitwiseOr
  {IR(32101, 11), 184}, // 107 BitwiseXor
  {IR(32718, 7), 227}, // 108 Branch
  {IR(32725, 18), 228}, // 109 BranchConditional
  {IR(37207, 17), 437}, // 110 BufferPointerEXT
  {IR(33586, 13), 277}, // 111 BuildNDRange
  {IR(29331, 11), 15}, // 112 Capability
  {IR(33544, 26), 275}, // 113 CaptureEventProfilingInfo
  {IR(35050, 23), 344}, // 114 ColorAttachmentReadEXT
  {IR(33136, 15), 255}, // 115 CommitReadPipe
  {IR(33151, 16), 256}, // 116 CommitWritePipe
  {IR(30577, 19), 72}, // 117 CompositeConstruct
  {IR(50158, 33), 827}, // 118 CompositeConstructContinuedINTEL
  {IR(36633, 30), 412}, // 119 CompositeConstructCoopMatQCOM
  {IR(36208, 31), 395}, // 120 CompositeConstructReplicateEXT
  {IR(30596, 17), 73}, // 121 CompositeExtract
  {IR(36663, 28), 413}, // 122 CompositeExtractCoopMatQCOM
  {IR(30613, 16), 74}, // 123 CompositeInsert
  {IR(50873, 27), 849}, // 124 ConditionalCapabilityINTEL
  {IR(51021, 27), 853}, // 125 ConditionalCopyObjectINTEL
  {IR(50846, 27), 848}, // 126 ConditionalEntryPointINTEL
  {IR(50820, 26), 847}, // 127 ConditionalExtensionINTEL
  {IR(17601, 9), 39}, // 128 Constant
  {IR(29837, 18), 40}, // 129 ConstantComposite
  {IR(50090, 32), 825}, // 130 ConstantCompositeContinuedINTEL
  {IR(36144, 30), 393}, // 131 ConstantCompositeReplicateEXT
  {IR(11253, 16), 442}, // 132 ConstantDataKHR
  {IR(29785, 14), 38}, // 133 ConstantFalse
  {IR(41859, 29), 612}, // 134 ConstantFunctionPointerINTEL
  {IR(29949, 13), 42}, // 135 ConstantNull
  {IR(34029, 20), 296}, // 136 ConstantPipeStorage
  {IR(29933, 16), 41}, // 137 ConstantSampler
  {IR(37272, 18), 441}, // 138 ConstantSizeOfEXT
  {IR(37099, 19), 432}, // 139 ConstantStringAMDX
  {IR(29772, 13), 37}, // 140 ConstantTrue
  {IR(32374, 15), 205}, // 141 ControlBarrier
  {IR(50231, 24), 830}, // 142 ControlBarrierArriveEXT
  {IR(50255, 26), 830}, // 143 ControlBarrierArriveINTEL
  {IR(50281, 22), 831}, // 144 ControlBarrierWaitEXT
  {IR(50303, 24), 831}, // 145 ControlBarrierWaitINTEL
  {IR(50211, 20), 829}, // 146 ConvertBF16ToFINTEL
  {IR(50191, 20), 828}, // 147 ConvertFToBF16INTEL
  {IR(31121, 12), 100}, // 148 ConvertFToS
  {IR(31109, 12), 99}, // 149 ConvertFToU
  {IR(51282, 26), 867}, // 150 ConvertHandleToImageINTEL
  {IR(51336, 33), 869}, // 151 ConvertHandleToSampledImageINTEL
  {IR(51308, 28), 868}, // 152 ConvertHandleToSamplerINTEL
  {IR(40826, 18), 569}, // 153 ConvertImageToUNV
  {IR(31198, 14), 107}, // 154 ConvertPtrToU
  {IR(31133, 12), 101}, // 155 ConvertSToF
  {IR(40889, 25), 572}, // 156 ConvertSampledImageToUNV
  {IR(40844, 20), 570}, // 157 ConvertSamplerToUNV
  {IR(35722, 35), 379}, // 158 ConvertUToAccelerationStructureKHR
  {IR(31145, 12), 102}, // 159 ConvertUToF
  {IR(40788, 18), 567}, // 160 ConvertUToImageNV
  {IR(31242, 14), 110}, // 161 ConvertUToPtr
  {IR(40864, 25), 571}, // 162 ConvertUToSampledImageNV
  {IR(40806, 20), 568}, // 163 ConvertUToSamplerNV
  {IR(38412, 27), 485}, // 164 CooperativeMatrixConvertNV
  {IR(36117, 27), 392}, // 165 CooperativeMatrixLengthKHR
  {IR(40151, 26), 545}, // 166 CooperativeMatrixLengthNV
  {IR(35985, 25), 389}, // 167 CooperativeMatrixLoadKHR
  {IR(40076, 24), 542}, // 168 CooperativeMatrixLoadNV
  {IR(40375, 30), 549}, // 169 CooperativeMatrixLoadTensorNV
  {IR(36090, 27), 391}, // 170 CooperativeMatrixMulAddKHR
  {IR(40125, 26), 544}, // 171 CooperativeMatrixMulAddNV
  {IR(40436, 32), 551}, // 172 CooperativeMatrixPerElementOpNV
  {IR(40274, 26), 548}, // 173 CooperativeMatrixReduceNV
  {IR(36010, 26), 390}, // 174 CooperativeMatrixStoreKHR
  {IR(40100, 25), 543}, // 175 CooperativeMatrixStoreNV
  {IR(40405, 31), 550}, // 176 CooperativeMatrixStoreTensorNV
  {IR(40759, 29), 566}, // 177 CooperativeMatrixTransposeNV
  {IR(38635, 24), 492}, // 178 CooperativeVectorLoadNV
  {IR(38380, 32), 484}, // 179 CooperativeVectorMatrixMulAddNV
  {IR(38270, 29), 481}, // 180 CooperativeVectorMatrixMulNV
  {IR(38299, 42), 482}, // 181 CooperativeVectorOuterProductAccumulateNV
  {IR(38341, 39), 483}, // 182 CooperativeVectorReduceSumAccumulateNV
  {IR(38659, 25), 493}, // 183 CooperativeVectorStoreNV
  {IR(35009, 12), 340}, // 184 CopyLogical
  {IR(30243, 11), 56}, // 185 CopyMemory
  {IR(30254, 16), 57}, // 186 CopyMemorySized
  {IR(30629, 11), 75}, // 187 CopyObject
  {IR(34049, 26), 297}, // 188 CreatePipeFromPipeStorage
  {IR(40504, 21), 554}, // 189 CreateTensorLayoutNV
  {IR(40624, 19), 559}, // 190 CreateTensorViewNV
  {IR(33496, 16), 272}, // 191 CreateUserEvent
  {IR(49226, 30), 801}, // 192 CrossWorkgroupCastToPtrALTERA
  {IR(49256, 29), 801}, // 193 CrossWorkgroupCastToPtrINTEL
  {IR(32196, 5), 192}, // 194 DPdx
  {IR(32242, 11), 198}, // 195 DPdxCoarse
  {IR(32213, 9), 195}, // 196 DPdxFine
  {IR(32201, 5), 193}, // 197 DPdy
  {IR(32253, 11), 199}, // 198 DPdyCoarse
  {IR(32222, 9), 196}, // 199 DPdyFine
  {IR(30403, 9), 64}, // 200 Decorate
  {IR(34226, 11), 305}, // 201 DecorateId
  {IR(41993, 15), 621}, // 202 DecorateString
  {IR(42008, 21), 621}, // 203 DecorateStringGOOGLE
  {IR(30427, 16), 66}, // 204 DecorationGroup
  {IR(12784, 25), 562}, // 205 DemoteToHelperInvocation
  {IR(12809, 28), 562}, // 206 DemoteToHelperInvocationEXT
  {IR(35073, 23), 345}, // 207 DepthAttachmentReadEXT
  {IR(31512, 4), 137}, // 208 Dot
  {IR(38439, 17), 486}, // 209 EmitMeshTasksEXT
  {IR(32301, 17), 203}, // 210 EmitStreamVertex
  {IR(32277, 11), 201}, // 211 EmitVertex
  {IR(40205, 26), 547}, // 212 EndInvocationInterlockEXT
  {IR(32288, 13), 202}, // 213 EndPrimitive
  {IR(32318, 19), 204}, // 214 EndStreamPrimitive
  {IR(33332, 14), 265}, // 215 EnqueueKernel
  {IR(33318, 14), 264}, // 216 EnqueueMarker
  {IR(36971, 24), 427}, // 217 EnqueueNodePayloadsAMDX
  {IR(29246, 11), 13}, // 218 EntryPoint
  {IR(35703, 19), 378}, // 219 ExecuteCallableKHR
  {IR(39787, 18), 532}, // 220 ExecuteCallableNV
  {IR(29289, 14), 14}, // 221 ExecutionMode
  {IR(34210, 16), 304}, // 222 ExecutionModeId
  {IR(41983, 10), 620}, // 223 ExpectKHR
  {IR(29100, 8), 11}, // 224 ExtInst
  {IR(29040, 14), 10}, // 225 ExtInstImport
  {IR(35640, 26), 375}, // 226 ExtInstWithForwardRefsKHR
  {IR(29030, 10), 9}, // 227 Extension
  {IR(36691, 20), 414}, // 228 ExtractSubArrayQCOM
  {IR(31344, 5), 118}, // 229 FAdd
  {IR(31175, 9), 105}, // 230 FConvert
  {IR(31379, 5), 125}, // 231 FDiv
  {IR(51388, 19), 871}, // 232 FDot2MixAcc16VALVE
  {IR(51369, 19), 870}, // 233 FDot2MixAcc32VALVE
  {IR(51407, 19), 872}, // 234 FDot4MixAcc32VALVE
  {IR(31404, 5), 130}, // 235 FMod
  {IR(31364, 5), 122}, // 236 FMul
  {IR(31331, 8), 116}, // 237 FNegate
  {IR(31841, 10), 168}, // 238 FOrdEqual
  {IR(31919, 16), 174}, // 239 FOrdGreaterThan
  {IR(31991, 21), 178}, // 240 FOrdGreaterThanEqual
  {IR(31891, 13), 172}, // 241 FOrdLessThan
  {IR(31953, 18), 176}, // 242 FOrdLessThanEqual
  {IR(31863, 13), 170}, // 243 FOrdNotEqual
  {IR(14791, 14), 804}, // 244 FPGARegALTERA
  {IR(14805, 13), 804}, // 245 FPGARegINTEL
  {IR(31399, 5), 129}, // 246 FRem
  {IR(31354, 5), 120}, // 247 FSub
  {IR(31851, 12), 169}, // 248 FUnordEqual
  {IR(31935, 18), 175}, // 249 FUnordGreaterThan
  {IR(32012, 23), 179}, // 250 FUnordGreaterThanEqual
  {IR(31904, 15), 173}, // 251 FUnordLessThan
  {IR(31971, 20), 177}, // 252 FUnordLessThanEqual
  {IR(31876, 15), 171}, // 253 FUnordNotEqual
  {IR(38597, 38), 491}, // 254 FetchMicroTriangleVertexBarycentricNV
  {IR(38562, 35), 490}, // 255 FetchMicroTriangleVertexPositionNV
  {IR(37020, 29), 429}, // 256 FinishWritingNodePayloadAMDX
  {IR(48940, 15), 793}, // 257 FixedCosALTERA
  {IR(48955, 14), 793}, // 258 FixedCosINTEL
  {IR(49037, 17), 796}, // 259 FixedCosPiALTERA
  {IR(49054, 16), 796}, // 260 FixedCosPiINTEL
  {IR(49138, 15), 799}, // 261 FixedExpALTERA
  {IR(49153, 14), 799}, // 262 FixedExpINTEL
  {IR(49109, 15), 798}, // 263 FixedLogALTERA
  {IR(49124, 14), 798}, // 264 FixedLogINTEL
  {IR(48845, 17), 790}, // 265 FixedRecipALTERA
  {IR(48862, 16), 790}, // 266 FixedRecipINTEL
  {IR(48878, 17), 791}, // 267 FixedRsqrtALTERA
  {IR(48895, 16), 791}, // 268 FixedRsqrtINTEL
  {IR(48911, 15), 792}, // 269 FixedSinALTERA
  {IR(48969, 18), 794}, // 270 FixedSinCosALTERA
  {IR(48987, 17), 794}, // 271 FixedSinCosINTEL
  {IR(49070, 20), 797}, // 272 FixedSinCosPiALTERA
  {IR(49090, 19), 797}, // 273 FixedSinCosPiINTEL
  {IR(48926, 14), 792}, // 274 FixedSinINTEL
  {IR(49004, 17), 795}, // 275 FixedSinPiALTERA
  {IR(49021, 16), 795}, // 276 FixedSinPiINTEL
  {IR(48814, 16), 789}, // 277 FixedSqrtALTERA
  {IR(48830, 15), 789}, // 278 FixedSqrtINTEL
  {IR(35557, 7), 369}, // 279 FmaKHR
  {IR(36916, 17), 424}, // 280 FragmentFetchAMD
  {IR(36895, 21), 423}, // 281 FragmentMaskFetchAMD
  {IR(37320, 10), 445}, // 282 FreezeKHR
  {IR(28079, 9), 48}, // 283 Function
  {IR(30152, 13), 51}, // 284 FunctionCall
  {IR(30140, 12), 50}, // 285 FunctionEnd
  {IR(30122, 18), 49}, // 286 FunctionParameter
  {IR(41888, 25), 613}, // 287 FunctionPointerCallINTEL
  {IR(32206, 7), 194}, // 288 Fwidth
  {IR(32264, 13), 200}, // 289 FwidthCoarse
  {IR(32231, 11), 197}, // 290 FwidthFine
  {IR(31273, 17), 112}, // 291 GenericCastToPtr
  {IR(31290, 25), 113}, // 292 GenericCastToPtrExplicit
  {IR(30329, 23), 62}, // 293 GenericPtrMemSemantics
  {IR(33570, 16), 276}, // 294 GetDefaultQueue
  {IR(34075, 35), 298}, // 295 GetKernelLocalSizeForSubgroupCount
  {IR(34110, 25), 299}, // 296 GetKernelMaxNumSubgroups
  {IR(33376, 32), 267}, // 297 GetKernelNDrangeMaxSubGroupSize
  {IR(33346, 30), 266}, // 298 GetKernelNDrangeSubGroupCount
  {IR(33431, 40), 269}, // 299 GetKernelPreferredWorkGroupSizeMultiple
  {IR(33408, 23), 268}, // 300 GetKernelWorkGroupSize
  {IR(33202, 18), 259}, // 301 GetMaxPipePackets
  {IR(33184, 18), 258}, // 302 GetNumPipePackets
  {IR(10167, 9), 353}, // 303 GraphARM
  {IR(35225, 17), 351}, // 304 GraphConstantARM
  {IR(35293, 12), 356}, // 305 GraphEndARM
  {IR(35242, 19), 352}, // 306 GraphEntryPointARM
  {IR(35261, 14), 354}, // 307 GraphInputARM
  {IR(35275, 18), 355}, // 308 GraphSetOutputARM
  {IR(32889, 9), 238}, // 309 GroupAll
  {IR(32898, 9), 239}, // 310 GroupAny
  {IR(32858, 15), 236}, // 311 GroupAsyncCopy
  {IR(51115, 19), 858}, // 312 GroupBitwiseAndKHR
  {IR(51134, 18), 859}, // 313 GroupBitwiseOrKHR
  {IR(51152, 19), 860}, // 314 GroupBitwiseXorKHR
  {IR(32907, 15), 240}, // 315 GroupBroadcast
  {IR(33277, 20), 262}, // 316 GroupCommitReadPipe
  {IR(33297, 21), 263}, // 317 GroupCommitWritePipe
  {IR(30443, 14), 67}, // 318 GroupDecorate
  {IR(32965, 10), 242}, // 319 GroupFAdd
  {IR(36734, 23), 416}, // 320 GroupFAddNonUniformAMD
  {IR(33005, 10), 246}, // 321 GroupFMax
  {IR(36826, 23), 420}, // 322 GroupFMaxNonUniformAMD
  {IR(32975, 10), 243}, // 323 GroupFMin
  {IR(36757, 23), 417}, // 324 GroupFMinNonUniformAMD
  {IR(51102, 13), 857}, // 325 GroupFMulKHR
  {IR(32955, 10), 241}, // 326 GroupIAdd
  {IR(36711, 23), 415}, // 327 GroupIAddNonUniformAMD
  {IR(51089, 13), 856}, // 328 GroupIMulKHR
  {IR(51171, 19), 861}, // 329 GroupLogicalAndKHR
  {IR(51190, 18), 862}, // 330 GroupLogicalOrKHR
  {IR(51208, 19), 863}, // 331 GroupLogicalXorKHR
  {IR(30502, 20), 68}, // 332 GroupMemberDecorate
  {IR(34258, 19), 307}, // 333 GroupNonUniformAll
  {IR(34296, 24), 309}, // 334 GroupNonUniformAllEqual
  {IR(34277, 19), 308}, // 335 GroupNonUniformAny
  {IR(6737, 22), 312}, // 336 GroupNonUniformBallot
  {IR(34436, 30), 315}, // 337 GroupNonUniformBallotBitCount
  {IR(34404, 32), 314}, // 338 GroupNonUniformBallotBitExtract
  {IR(34466, 29), 316}, // 339 GroupNonUniformBallotFindLSB
  {IR(34495, 29), 317}, // 340 GroupNonUniformBallotFindMSB
  {IR(34802, 26), 332}, // 341 GroupNonUniformBitwiseAnd
  {IR(34828, 25), 333}, // 342 GroupNonUniformBitwiseOr
  {IR(34853, 26), 334}, // 343 GroupNonUniformBitwiseXor
  {IR(34320, 25), 310}, // 344 GroupNonUniformBroadcast
  {IR(34345, 30), 311}, // 345 GroupNonUniformBroadcastFirst
  {IR(34237, 21), 306}, // 346 GroupNonUniformElect
  {IR(34622, 20), 323}, // 347 GroupNonUniformFAdd
  {IR(34782, 20), 331}, // 348 GroupNonUniformFMax
  {IR(34722, 20), 328}, // 349 GroupNonUniformFMin
  {IR(34662, 20), 325}, // 350 GroupNonUniformFMul
  {IR(34602, 20), 322}, // 351 GroupNonUniformIAdd
  {IR(34642, 20), 324}, // 352 GroupNonUniformIMul
  {IR(34375, 29), 313}, // 353 GroupNonUniformInverseBallot
  {IR(34879, 26), 335}, // 354 GroupNonUniformLogicalAnd
  {IR(34905, 25), 336}, // 355 GroupNonUniformLogicalOr
  {IR(34930, 26), 337}, // 356 GroupNonUniformLogicalXor
  {IR(38474, 28), 488}, // 357 GroupNonUniformPartitionEXT
  {IR(38502, 27), 488}, // 358 GroupNonUniformPartitionNV
  {IR(37141, 26), 434}, // 359 GroupNonUniformQuadAllKHR
  {IR(37167, 26), 435}, // 360 GroupNonUniformQuadAnyKHR
  {IR(34956, 29), 338}, // 361 GroupNonUniformQuadBroadcast
  {IR(34985, 24), 339}, // 362 GroupNonUniformQuadSwap
  {IR(15030, 25), 373}, // 363 GroupNonUniformRotateKHR
  {IR(34742, 20), 329}, // 364 GroupNonUniformSMax
  {IR(34682, 20), 326}, // 365 GroupNonUniformSMin
  {IR(9876, 23), 318}, // 366 GroupNonUniformShuffle
  {IR(34575, 27), 321}, // 367 GroupNonUniformShuffleDown
  {IR(34550, 25), 320}, // 368 GroupNonUniformShuffleUp
  {IR(34524, 26), 319}, // 369 GroupNonUniformShuffleXor
  {IR(34762, 20), 330}, // 370 GroupNonUniformUMax
  {IR(34702, 20), 327}, // 371 GroupNonUniformUMin
  {IR(33220, 28), 260}, // 372 GroupReserveReadPipePackets
  {IR(33248, 29), 261}, // 373 GroupReserveWritePipePackets
  {IR(33025, 10), 248}, // 374 GroupSMax
  {IR(36872, 23), 422}, // 375 GroupSMaxNonUniformAMD
  {IR(32995, 10), 245}, // 376 GroupSMin
  {IR(36803, 23), 419}, // 377 GroupSMinNonUniformAMD
  {IR(33015, 10), 247}, // 378 GroupUMax
  {IR(36849, 23), 421}, // 379 GroupUMaxNonUniformAMD
  {IR(32985, 10), 244}, // 380 GroupUMin
  {IR(36780, 23), 418}, // 381 GroupUMinNonUniformAMD
  {IR(32873, 16), 237}, // 382 GroupWaitEvents
  {IR(39131, 26), 509}, // 383 HitObjectExecuteShaderEXT
  {IR(37765, 25), 461}, // 384 HitObjectExecuteShaderNV
  {IR(39184, 26), 511}, // 385 HitObjectGetAttributesEXT
  {IR(37816, 25), 463}, // 386 HitObjectGetAttributesNV
  {IR(39863, 24), 534}, // 387 HitObjectGetClusterIdNV
  {IR(39157, 27), 510}, // 388 HitObjectGetCurrentTimeEXT
  {IR(37790, 26), 462}, // 389 HitObjectGetCurrentTimeNV
  {IR(39263, 29), 514}, // 390 HitObjectGetGeometryIndexEXT
  {IR(37892, 28), 466}, // 391 HitObjectGetGeometryIndexNV
  {IR(39210, 23), 512}, // 392 HitObjectGetHitKindEXT
  {IR(37841, 22), 464}, // 393 HitObjectGetHitKindNV
  {IR(39318, 35), 516}, // 394 HitObjectGetInstanceCustomIndexEXT
  {IR(37945, 34), 468}, // 395 HitObjectGetInstanceCustomIndexNV
  {IR(39292, 26), 515}, // 396 HitObjectGetInstanceIdEXT
  {IR(37920, 25), 467}, // 397 HitObjectGetInstanceIdNV
  {IR(38764, 51), 497}, // 398 HitObjectGetIntersectionTriangleVertexPositionsEXT
  {IR(41255, 27), 582}, // 399 HitObjectGetLSSPositionsNV
  {IR(41282, 23), 583}, // 400 HitObjectGetLSSRadiiNV
  {IR(39384, 34), 518}, // 401 HitObjectGetObjectRayDirectionEXT
  {IR(37477, 33), 451}, // 402 HitObjectGetObjectRayDirectionNV
  {IR(39353, 31), 517}, // 403 HitObjectGetObjectRayOriginEXT
  {IR(37510, 30), 452}, // 404 HitObjectGetObjectRayOriginNV
  {IR(39481, 29), 521}, // 405 HitObjectGetObjectToWorldEXT
  {IR(37449, 28), 450}, // 406 HitObjectGetObjectToWorldNV
  {IR(39233, 30), 513}, // 407 HitObjectGetPrimitiveIndexEXT
  {IR(37863, 29), 465}, // 408 HitObjectGetPrimitiveIndexNV
  {IR(38815, 24), 498}, // 409 HitObjectGetRayFlagsEXT
  {IR(39539, 23), 523}, // 410 HitObjectGetRayTMaxEXT
  {IR(38040, 22), 471}, // 411 HitObjectGetRayTMaxNV
  {IR(39887, 23), 535}, // 412 HitObjectGetRayTMinEXT
  {IR(38062, 22), 472}, // 413 HitObjectGetRayTMinNV
  {IR(39910, 45), 536}, // 414 HitObjectGetShaderBindingTableRecordIndexEXT
  {IR(37605, 44), 455}, // 415 HitObjectGetShaderBindingTableRecordIndexNV
  {IR(39955, 40), 537}, // 416 HitObjectGetShaderRecordBufferHandleEXT
  {IR(37566, 39), 454}, // 417 HitObjectGetShaderRecordBufferHandleNV
  {IR(41199, 29), 580}, // 418 HitObjectGetSpherePositionNV
  {IR(41228, 27), 581}, // 419 HitObjectGetSphereRadiusNV
  {IR(39418, 33), 519}, // 420 HitObjectGetWorldRayDirectionEXT
  {IR(37979, 32), 469}, // 421 HitObjectGetWorldRayDirectionNV
  {IR(39451, 30), 520}, // 422 HitObjectGetWorldRayOriginEXT
  {IR(38011, 29), 470}, // 423 HitObjectGetWorldRayOriginNV
  {IR(39510, 29), 522}, // 424 HitObjectGetWorldToObjectEXT
  {IR(37421, 28), 449}, // 425 HitObjectGetWorldToObjectNV
  {IR(39995, 20), 538}, // 426 HitObjectIsEmptyEXT
  {IR(38084, 19), 473}, // 427 HitObjectIsEmptyNV
  {IR(40015, 18), 539}, // 428 HitObjectIsHitEXT
  {IR(38103, 17), 474}, // 429 HitObjectIsHitNV
  {IR(41328, 20), 585}, // 430 HitObjectIsLSSHitNV
  {IR(40033, 19), 540}, // 431 HitObjectIsMissEXT
  {IR(38120, 18), 475}, // 432 HitObjectIsMissNV
  {IR(41305, 23), 584}, // 433 HitObjectIsSphereHitNV
  {IR(39107, 24), 508}, // 434 HitObjectRecordEmptyEXT
  {IR(37649, 23), 456}, // 435 HitObjectRecordEmptyNV
  {IR(38684, 28), 494}, // 436 HitObjectRecordFromQueryEXT
  {IR(37330, 27), 446}, // 437 HitObjectRecordHitMotionNV
  {IR(37692, 21), 458}, // 438 HitObjectRecordHitNV
  {IR(37357, 36), 447}, // 439 HitObjectRecordHitWithIndexMotionNV
  {IR(37713, 30), 459}, // 440 HitObjectRecordHitWithIndexNV
  {IR(38712, 23), 495}, // 441 HitObjectRecordMissEXT
  {IR(38735, 29), 496}, // 442 HitObjectRecordMissMotionEXT
  {IR(37393, 28), 448}, // 443 HitObjectRecordMissMotionNV
  {IR(37743, 22), 460}, // 444 HitObjectRecordMissNV
  {IR(38884, 33), 500}, // 445 HitObjectReorderExecuteShaderEXT
  {IR(38839, 45), 499}, // 446 HitObjectSetShaderBindingTableRecordIndexEXT
  {IR(38949, 38), 502}, // 447 HitObjectTraceMotionReorderExecuteEXT
  {IR(39059, 21), 506}, // 448 HitObjectTraceRayEXT
  {IR(39080, 27), 507}, // 449 HitObjectTraceRayMotionEXT
  {IR(37540, 26), 453}, // 450 HitObjectTraceRayMotionNV
  {IR(37672, 20), 457}, // 451 HitObjectTraceRayNV
  {IR(38917, 32), 501}, // 452 HitObjectTraceReorderExecuteEXT
  {IR(31339, 5), 117}, // 453 IAdd
  {IR(31516, 10), 138}, // 454 IAddCarry
  {IR(41707, 13), 602}, // 455 IAddSatINTEL
  {IR(41733, 14), 604}, // 456 IAverageINTEL
  {IR(41761, 21), 606}, // 457 IAverageRoundedINTEL
  {IR(31712, 7), 158}, // 458 IEqual
  {IR(31359, 5), 121}, // 459 IMul
  {IR(41829, 15), 610}, // 460 IMul32x16INTEL
  {IR(31719, 10), 159}, // 461 INotEqual
  {IR(31349, 5), 119}, // 462 ISub
  {IR(31526, 11), 139}, // 463 ISubBorrow
  {IR(41803, 13), 608}, // 464 ISubSatINTEL
  {IR(35757, 22), 380}, // 465 IgnoreIntersectionKHR
  {IR(39605, 21), 525}, // 466 IgnoreIntersectionNV
  {IR(28123, 6), 91}, // 467 Image
  {IR(36604, 29), 411}, // 468 ImageBlockMatchGatherSADQCOM
  {IR(36575, 29), 410}, // 469 ImageBlockMatchGatherSSDQCOM
  {IR(36477, 23), 406}, // 470 ImageBlockMatchSADQCOM
  {IR(36454, 23), 405}, // 471 ImageBlockMatchSSDQCOM
  {IR(36546, 29), 409}, // 472 ImageBlockMatchWindowSADQCOM
  {IR(36517, 29), 408}, // 473 ImageBlockMatchWindowSSDQCOM
  {IR(36435, 19), 404}, // 474 ImageBoxFilterQCOM
  {IR(30957, 16), 88}, // 475 ImageDrefGather
  {IR(30934, 11), 86}, // 476 ImageFetch
  {IR(30945, 12), 87}, // 477 ImageGather
  {IR(30994, 17), 92}, // 478 ImageQueryFormat
  {IR(31074, 17), 97}, // 479 ImageQueryLevels
  {IR(31060, 14), 96}, // 480 ImageQueryLod
  {IR(31011, 16), 93}, // 481 ImageQueryOrder
  {IR(31091, 18), 98}, // 482 ImageQuerySamples
  {IR(31045, 15), 95}, // 483 ImageQuerySize
  {IR(31027, 18), 94}, // 484 ImageQuerySizeLod
  {IR(30973, 10), 89}, // 485 ImageRead
  {IR(30791, 27), 81}, // 486 ImageSampleDrefExplicitLod
  {IR(30764, 27), 80}, // 487 ImageSampleDrefImplicitLod
  {IR(30741, 23), 79}, // 488 ImageSampleExplicitLod
  {IR(38207, 23), 479}, // 489 ImageSampleFootprintNV
  {IR(30695, 23), 78}, // 490 ImageSampleImplicitLod
  {IR(30903, 31), 85}, // 491 ImageSampleProjDrefExplicitLod
  {IR(30872, 31), 84}, // 492 ImageSampleProjDrefImplicitLod
  {IR(30845, 27), 83}, // 493 ImageSampleProjExplicitLod
  {IR(30818, 27), 82}, // 494 ImageSampleProjImplicitLod
  {IR(36411, 24), 403}, // 495 ImageSampleWeightedQCOM
  {IR(33898, 22), 288}, // 496 ImageSparseDrefGather
  {IR(33863, 17), 286}, // 497 ImageSparseFetch
  {IR(33880, 18), 287}, // 498 ImageSparseGather
  {IR(33990, 16), 293}, // 499 ImageSparseRead
  {IR(33690, 33), 281}, // 500 ImageSparseSampleDrefExplicitLod
  {IR(33657, 33), 280}, // 501 ImageSparseSampleDrefImplicitLod
  {IR(33628, 29), 279}, // 502 ImageSparseSampleExplicitLod
  {IR(33599, 29), 278}, // 503 ImageSparseSampleImplicitLod
  {IR(33826, 37), 285}, // 504 ImageSparseSampleProjDrefExplicitLod
  {IR(33789, 37), 284}, // 505 ImageSparseSampleProjDrefImplicitLod
  {IR(33756, 33), 283}, // 506 ImageSparseSampleProjExplicitLod
  {IR(33723, 33), 282}, // 507 ImageSparseSampleProjImplicitLod
  {IR(33920, 26), 289}, // 508 ImageSparseTexelsResident
  {IR(30174, 18), 53}, // 509 ImageTexelPointer
  {IR(30983, 11), 90}, // 510 ImageWrite
  {IR(30282, 20), 59}, // 511 InBoundsAccessChain
  {IR(30352, 23), 63}, // 512 InBoundsPtrAccessChain
  {IR(31583, 9), 146}, // 513 IsFinite
  {IR(40690, 22), 563}, // 514 IsHelperInvocationEXT
  {IR(31577, 6), 145}, // 515 IsInf
  {IR(31571, 6), 144}, // 516 IsNan
  {IR(37076, 23), 431}, // 517 IsNodePayloadValidAMDX
  {IR(31592, 9), 147}, // 518 IsNormal
  {IR(33512, 13), 273}, // 519 IsValidEvent
  {IR(33167, 17), 257}, // 520 IsValidReserveId
  {IR(32795, 5), 230}, // 521 Kill
  {IR(32712, 6), 226}, // 522 Label
  {IR(31612, 14), 149}, // 523 LessOrGreater
  {IR(32831, 14), 234}, // 524 LifetimeStart
  {IR(32845, 13), 235}, // 525 LifetimeStop
  {IR(29025, 5), 8}, // 526 Line
  {IR(30232, 5), 54}, // 527 Load
  {IR(31683, 11), 155}, // 528 LogicalAnd
  {IR(31644, 13), 152}, // 529 LogicalEqual
  {IR(31694, 11), 156}, // 530 LogicalNot
  {IR(31657, 16), 153}, // 531 LogicalNotEqual
  {IR(31673, 10), 154}, // 532 LogicalOr
  {IR(48732, 17), 785}, // 533 LoopControlINTEL
  {IR(32652, 10), 224}, // 534 LoopMerge
  {IR(51245, 18), 865}, // 535 MaskedGatherINTEL
  {IR(51263, 19), 866}, // 536 MaskedScatterINTEL
  {IR(31481, 18), 135}, // 537 MatrixTimesMatrix
  {IR(31427, 18), 132}, // 538 MatrixTimesScalar
  {IR(31463, 18), 134}, // 539 MatrixTimesVector
  {IR(30412, 15), 65}, // 540 MemberDecorate
  {IR(37252, 20), 440}, // 541 MemberDecorateIdEXT
  {IR(42029, 21), 622}, // 542 MemberDecorateString
  {IR(42050, 27), 622}, // 543 MemberDecorateStringGOOGLE
  {IR(29007, 11), 6}, // 544 MemberName
  {IR(32389, 14), 206}, // 545 MemoryBarrier
  {IR(29172, 12), 12}, // 546 MemoryModel
  {IR(34175, 19), 302}, // 547 MemoryNamedBarrier
  {IR(34194, 16), 303}, // 548 ModuleProcessed
  {IR(29002, 5), 5}, // 549 Name
  {IR(34152, 23), 301}, // 550 NamedBarrierInitialize
  {IR(33946, 7), 290}, // 551 NoLine
  {IR(37049, 27), 430}, // 552 NodePayloadArrayLengthAMDX
  {IR(28798, 4), 0}, // 553 Nop
  {IR(32123, 4), 186}, // 554 Not
  {IR(31626, 8), 150}, // 555 Ordered
  {IR(31499, 13), 136}, // 556 OuterProduct
  {IR(32618, 4), 223}, // 557 Phi
  {IR(37310, 10), 444}, // 558 PoisonKHR
  {IR(51048, 20), 854}, // 559 PredicatedLoadINTEL
  {IR(51068, 21), 855}, // 560 PredicatedStoreINTEL
  {IR(30302, 15), 60}, // 561 PtrAccessChain
  {IR(49167, 30), 800}, // 562 PtrCastToCrossWorkgroupALTERA
  {IR(49197, 29), 800}, // 563 PtrCastToCrossWorkgroupINTEL
  {IR(31256, 17), 111}, // 564 PtrCastToGeneric
  {IR(35042, 8), 343}, // 565 PtrDiff
  {IR(35021, 9), 341}, // 566 PtrEqual
  {IR(35030, 12), 342}, // 567 PtrNotEqual
  {IR(31184, 14), 106}, // 568 QuantizeToF16
  {IR(40995, 17), 574}, // 569 RawAccessChainNV
  {IR(36330, 31), 400}, // 570 RayQueryConfirmIntersectionKHR
  {IR(36298, 32), 399}, // 571 RayQueryGenerateIntersectionKHR
  {IR(39840, 23), 533}, // 572 RayQueryGetClusterIdNV
  {IR(49679, 39), 813}, // 573 RayQueryGetIntersectionBarycentricsKHR
  {IR(49754, 46), 815}, // 574 RayQueryGetIntersectionCandidateAABBOpaqueKHR
  {IR(39805, 35), 533}, // 575 RayQueryGetIntersectionClusterIdNV
  {IR(49718, 36), 814}, // 576 RayQueryGetIntersectionFrontFaceKHR
  {IR(49598, 40), 811}, // 577 RayQueryGetIntersectionGeometryIndexKHR
  {IR(49450, 46), 808}, // 578 RayQueryGetIntersectionInstanceCustomIndexKHR
  {IR(49496, 37), 809}, // 579 RayQueryGetIntersectionInstanceIdKHR
  {IR(49533, 65), 810}, // 580 RayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR
  {IR(41162, 37), 579}, // 581 RayQueryGetIntersectionLSSHitValueNV
  {IR(41090, 38), 577}, // 582 RayQueryGetIntersectionLSSPositionsNV
  {IR(41128, 34), 578}, // 583 RayQueryGetIntersectionLSSRadiiNV
  {IR(49800, 45), 816}, // 584 RayQueryGetIntersectionObjectRayDirectionKHR
  {IR(49845, 42), 817}, // 585 RayQueryGetIntersectionObjectRayOriginKHR
  {IR(49948, 40), 820}, // 586 RayQueryGetIntersectionObjectToWorldKHR
  {IR(49638, 41), 812}, // 587 RayQueryGetIntersectionPrimitiveIndexKHR
  {IR(41012, 40), 575}, // 588 RayQueryGetIntersectionSpherePositionNV
  {IR(41052, 38), 576}, // 589 RayQueryGetIntersectionSphereRadiusNV
  {IR(49422, 28), 807}, // 590 RayQueryGetIntersectionTKHR
  {IR(39680, 50), 530}, // 591 RayQueryGetIntersectionTriangleVertexPositionsKHR
  {IR(36380, 31), 402}, // 592 RayQueryGetIntersectionTypeKHR
  {IR(49988, 40), 821}, // 593 RayQueryGetIntersectionWorldToObjectKHR
  {IR(49399, 23), 806}, // 594 RayQueryGetRayFlagsKHR
  {IR(49377, 22), 805}, // 595 RayQueryGetRayTMinKHR
  {IR(49887, 32), 818}, // 596 RayQueryGetWorldRayDirectionKHR
  {IR(49919, 29), 819}, // 597 RayQueryGetWorldRayOriginKHR
  {IR(36255, 22), 397}, // 598 RayQueryInitializeKHR
  {IR(41370, 19), 587}, // 599 RayQueryIsLSSHitNV
  {IR(41348, 22), 586}, // 600 RayQueryIsSphereHitNV
  {IR(36361, 19), 401}, // 601 RayQueryProceedKHR
  {IR(36277, 21), 398}, // 602 RayQueryTerminateKHR
  {IR(36933, 13), 425}, // 603 ReadClockKHR
  {IR(33035, 9), 249}, // 604 ReadPipe
  {IR(49285, 23), 802}, // 605 ReadPipeBlockingALTERA
  {IR(49308, 22), 802}, // 606 ReadPipeBlockingINTEL
  {IR(33483, 13), 271}, // 607 ReleaseEvent
  {IR(39004, 25), 504}, // 608 ReorderThreadWithHintEXT
  {IR(38167, 24), 477}, // 609 ReorderThreadWithHintNV
  {IR(39029, 30), 505}, // 610 ReorderThreadWithHitObjectEXT
  {IR(38138, 29), 476}, // 611 ReorderThreadWithHitObjectNV
  {IR(39562, 22), 524}, // 612 ReportIntersectionKHR
  {IR(39584, 21), 524}, // 613 ReportIntersectionNV
  {IR(33089, 23), 253}, // 614 ReserveReadPipePackets
  {IR(33112, 24), 254}, // 615 ReserveWritePipePackets
  {IR(33054, 17), 251}, // 616 ReservedReadPipe
  {IR(33071, 18), 252}, // 617 ReservedWritePipe
  {IR(47259, 19), 743}, // 618 RestoreMemoryINTEL
  {IR(33471, 12), 270}, // 619 RetainEvent
  {IR(32800, 7), 231}, // 620 Return
  {IR(32807, 12), 232}, // 621 ReturnValue
  {IR(51227, 18), 864}, // 622 RoundFToTF32INTEL
  {IR(31166, 9), 104}, // 623 SConvert
  {IR(31374, 5), 124}, // 624 SDiv
  {IR(35842, 5), 382}, // 625 SDot
  {IR(35883, 11), 385}, // 626 SDotAccSat
  {IR(35894, 14), 385}, // 627 SDotAccSatKHR
  {IR(35847, 8), 382}, // 628 SDotKHR
  {IR(31742, 13), 161}, // 629 SGreaterThan
  {IR(31773, 18), 163}, // 630 SGreaterThanEqual
  {IR(31801, 10), 165}, // 631 SLessThan
  {IR(31826, 15), 167}, // 632 SLessThanEqual
  {IR(31394, 5), 128}, // 633 SMod
  {IR(31550, 13), 141}, // 634 SMulExtended
  {IR(31323, 8), 115}, // 635 SNegate
  {IR(31389, 5), 127}, // 636 SRem
  {IR(35868, 6), 384}, // 637 SUDot
  {IR(35933, 12), 387}, // 638 SUDotAccSat
  {IR(35945, 15), 387}, // 639 SUDotAccSatKHR
  {IR(35874, 9), 384}, // 640 SUDotKHR
  {IR(30650, 13), 77}, // 641 SampledImage
  {IR(40914, 29), 573}, // 642 SamplerImageAddressingModeNV
  {IR(31212, 15), 108}, // 643 SatConvertSToU
  {IR(31227, 15), 109}, // 644 SatConvertUToS
  {IR(47243, 16), 742}, // 645 SaveMemoryINTEL
  {IR(31705, 7), 157}, // 646 Select
  {IR(32697, 15), 225}, // 647 SelectionMerge
  {IR(38456, 18), 487}, // 648 SetMeshOutputsEXT
  {IR(33525, 19), 274}, // 649 SetUserEventStatus
  {IR(32074, 17), 182}, // 650 ShiftLeftLogical
  {IR(32053, 21), 181}, // 651 ShiftRightArithmetic
  {IR(32035, 18), 180}, // 652 ShiftRightLogical
  {IR(31601, 11), 148}, // 653 SignBitSet
  {IR(34006, 7), 294}, // 654 SizeOf
  {IR(28979, 7), 3}, // 655 Source
  {IR(28860, 16), 2}, // 656 SourceContinued
  {IR(28986, 16), 4}, // 657 SourceExtension
  {IR(29997, 13), 45}, // 658 SpecConstant
  {IR(50924, 30), 851}, // 659 SpecConstantArchitectureINTEL
  {IR(50991, 30), 852}, // 660 SpecConstantCapabilitiesINTEL
  {IR(30010, 22), 46}, // 661 SpecConstantComposite
  {IR(50122, 36), 826}, // 662 SpecConstantCompositeContinuedINTEL
  {IR(36174, 34), 394}, // 663 SpecConstantCompositeReplicateEXT
  {IR(37290, 20), 443}, // 664 SpecConstantDataKHR
  {IR(29979, 18), 44}, // 665 SpecConstantFalse
  {IR(30073, 15), 47}, // 666 SpecConstantOp
  {IR(37118, 23), 433}, // 667 SpecConstantStringAMDX
  {IR(50900, 24), 850}, // 668 SpecConstantTargetINTEL
  {IR(29962, 17), 43}, // 669 SpecConstantTrue
  {IR(35096, 25), 346}, // 670 StencilAttachmentReadEXT
  {IR(30237, 6), 55}, // 671 Store
  {IR(29018, 7), 7}, // 672 String
  {IR(50589, 25), 839}, // 673 Subgroup2DBlockLoadINTEL
  {IR(50614, 34), 840}, // 674 Subgroup2DBlockLoadTransformINTEL
  {IR(50648, 34), 841}, // 675 Subgroup2DBlockLoadTransposeINTEL
  {IR(50682, 29), 842}, // 676 Subgroup2DBlockPrefetchINTEL
  {IR(50711, 26), 843}, // 677 Subgroup2DBlockStoreINTEL
  {IR(35594, 20), 372}, // 678 SubgroupAllEqualKHR
  {IR(35564, 15), 370}, // 679 SubgroupAllKHR
  {IR(35579, 15), 371}, // 680 SubgroupAnyKHR
  {IR(45761, 30), 706}, // 681 SubgroupAvcBmeInitializeINTEL
  {IR(45731, 30), 705}, // 682 SubgroupAvcFmeInitializeINTEL
  {IR(44166, 35), 675}, // 683 SubgroupAvcImeAdjustRefOffsetINTEL
  {IR(44201, 39), 676}, // 684 SubgroupAvcImeConvertToMcePayloadINTEL
  {IR(44842, 38), 689}, // 685 SubgroupAvcImeConvertToMceResultINTEL
  {IR(44465, 45), 682}, // 686 SubgroupAvcImeEvaluateWithDualReferenceINTEL
  {IR(44565, 53), 684}, // 687 SubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL
  {IR(44786, 56), 688}, // 688 SubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL
  {IR(44674, 54), 686}, // 689 SubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL
  {IR(44418, 47), 681}, // 690 SubgroupAvcImeEvaluateWithSingleReferenceINTEL
  {IR(44510, 55), 683}, // 691 SubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL
  {IR(44728, 58), 687}, // 692 SubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL
  {IR(44618, 56), 685}, // 693 SubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL
  {IR(45474, 36), 700}, // 694 SubgroupAvcImeGetBorderReachedINTEL
  {IR(44926, 44), 691}, // 695 SubgroupAvcImeGetDualReferenceStreaminINTEL
  {IR(44880, 46), 690}, // 696 SubgroupAvcImeGetSingleReferenceStreaminINTEL
  {IR(45341, 66), 698}, // 697 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL
  {IR(45273, 68), 697}, // 698 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL
  {IR(45407, 67), 699}, // 699 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL
  {IR(45136, 68), 695}, // 700 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL
  {IR(45066, 70), 694}, // 701 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL
  {IR(45204, 69), 696}, // 702 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL
  {IR(45510, 48), 701}, // 703 SubgroupAvcImeGetTruncatedSearchIndicationINTEL
  {IR(45558, 59), 702}, // 704 SubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL
  {IR(45675, 56), 704}, // 705 SubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL
  {IR(45617, 58), 703}, // 706 SubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL
  {IR(44029, 30), 671}, // 707 SubgroupAvcImeInitializeINTEL
  {IR(44133, 33), 674}, // 708 SubgroupAvcImeRefWindowSizeINTEL
  {IR(44097, 36), 673}, // 709 SubgroupAvcImeSetDualReferenceINTEL
  {IR(44330, 54), 679}, // 710 SubgroupAvcImeSetEarlySearchTerminationThresholdINTEL
  {IR(44240, 43), 677}, // 711 SubgroupAvcImeSetMaxMotionVectorCountINTEL
  {IR(44059, 38), 672}, // 712 SubgroupAvcImeSetSingleReferenceINTEL
  {IR(44283, 47), 678}, // 713 SubgroupAvcImeSetUnidirectionalMixDisableINTEL
  {IR(44384, 34), 680}, // 714 SubgroupAvcImeSetWeightedSadINTEL
  {IR(45019, 47), 693}, // 715 SubgroupAvcImeStripDualReferenceStreamoutINTEL
  {IR(44970, 49), 692}, // 716 SubgroupAvcImeStripSingleReferenceStreamoutINTEL
  {IR(43419, 39), 656}, // 717 SubgroupAvcMceConvertToImePayloadINTEL
  {IR(43458, 38), 657}, // 718 SubgroupAvcMceConvertToImeResultINTEL
  {IR(43496, 39), 658}, // 719 SubgroupAvcMceConvertToRefPayloadINTEL
  {IR(43535, 38), 659}, // 720 SubgroupAvcMceConvertToRefResultINTEL
  {IR(43573, 39), 660}, // 721 SubgroupAvcMceConvertToSicPayloadINTEL
  {IR(43612, 38), 661}, // 722 SubgroupAvcMceConvertToSicResultINTEL
  {IR(43725, 43), 664}, // 723 SubgroupAvcMceGetBestInterDistortionsINTEL
  {IR(42857, 50), 645}, // 724 SubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL
  {IR(42455, 60), 637}, // 725 SubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL
  {IR(42655, 51), 641}, // 726 SubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL
  {IR(42801, 56), 644}, // 727 SubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL
  {IR(42568, 47), 639}, // 728 SubgroupAvcMceGetDefaultInterShapePenaltyINTEL
  {IR(43156, 56), 651}, // 729 SubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL
  {IR(43055, 50), 649}, // 730 SubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL
  {IR(42750, 51), 643}, // 731 SubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL
  {IR(42959, 49), 647}, // 732 SubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL
  {IR(42907, 52), 646}, // 733 SubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL
  {IR(43105, 51), 650}, // 734 SubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL
  {IR(43844, 38), 667}, // 735 SubgroupAvcMceGetInterDirectionsINTEL
  {IR(43686, 39), 663}, // 736 SubgroupAvcMceGetInterDistortionsINTEL
  {IR(43768, 38), 665}, // 737 SubgroupAvcMceGetInterMajorShapeINTEL
  {IR(43806, 38), 666}, // 738 SubgroupAvcMceGetInterMinorShapeINTEL
  {IR(43882, 45), 668}, // 739 SubgroupAvcMceGetInterMotionVectorCountINTEL
  {IR(43927, 40), 669}, // 740 SubgroupAvcMceGetInterReferenceIdsINTEL
  {IR(43967, 62), 670}, // 741 SubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL
  {IR(43650, 36), 662}, // 742 SubgroupAvcMceGetMotionVectorsINTEL
  {IR(43212, 33), 652}, // 743 SubgroupAvcMceSetAcOnlyHaarINTEL
  {IR(43358, 61), 655}, // 744 SubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL
  {IR(42515, 53), 638}, // 745 SubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL
  {IR(42706, 44), 642}, // 746 SubgroupAvcMceSetInterDirectionPenaltyINTEL
  {IR(42615, 40), 640}, // 747 SubgroupAvcMceSetInterShapePenaltyINTEL
  {IR(43008, 47), 648}, // 748 SubgroupAvcMceSetMotionVectorCostFunctionINTEL
  {IR(43297, 61), 654}, // 749 SubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL
  {IR(43245, 52), 653}, // 750 SubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL
  {IR(45791, 39), 707}, // 751 SubgroupAvcRefConvertToMcePayloadINTEL
  {IR(46113, 38), 714}, // 752 SubgroupAvcRefConvertToMceResultINTEL
  {IR(45966, 45), 711}, // 753 SubgroupAvcRefEvaluateWithDualReferenceINTEL
  {IR(46011, 46), 712}, // 754 SubgroupAvcRefEvaluateWithMultiReferenceINTEL
  {IR(46057, 56), 713}, // 755 SubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL
  {IR(45919, 47), 710}, // 756 SubgroupAvcRefEvaluateWithSingleReferenceINTEL
  {IR(45830, 46), 708}, // 757 SubgroupAvcRefSetBidirectionalMixDisableINTEL
  {IR(45876, 43), 709}, // 758 SubgroupAvcRefSetBilinearFilterEnableINTEL
  {IR(46249, 42), 718}, // 759 SubgroupAvcSicConfigureIpeLumaChromaINTEL
  {IR(46213, 36), 717}, // 760 SubgroupAvcSicConfigureIpeLumaINTEL
  {IR(46181, 32), 716}, // 761 SubgroupAvcSicConfigureSkcINTEL
  {IR(46330, 39), 720}, // 762 SubgroupAvcSicConvertToMcePayloadINTEL
  {IR(46870, 38), 732}, // 763 SubgroupAvcSicConvertToMceResultINTEL
  {IR(46645, 31), 727}, // 764 SubgroupAvcSicEvaluateIpeINTEL
  {IR(46723, 45), 729}, // 765 SubgroupAvcSicEvaluateWithDualReferenceINTEL
  {IR(46768, 46), 730}, // 766 SubgroupAvcSicEvaluateWithMultiReferenceINTEL
  {IR(46814, 56), 731}, // 767 SubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL
  {IR(46676, 47), 728}, // 768 SubgroupAvcSicEvaluateWithSingleReferenceINTEL
  {IR(46987, 46), 735}, // 769 SubgroupAvcSicGetBestIpeChromaDistortionINTEL
  {IR(46943, 44), 734}, // 770 SubgroupAvcSicGetBestIpeLumaDistortionINTEL
  {IR(47208, 35), 740}, // 771 SubgroupAvcSicGetInterRawSadsINTEL
  {IR(47074, 36), 737}, // 772 SubgroupAvcSicGetIpeChromaModeINTEL
  {IR(46908, 35), 733}, // 773 SubgroupAvcSicGetIpeLumaShapeINTEL
  {IR(46291, 39), 719}, // 774 SubgroupAvcSicGetMotionVectorMaskINTEL
  {IR(47033, 41), 736}, // 775 SubgroupAvcSicGetPackedIpeLumaModesINTEL
  {IR(47110, 50), 738}, // 776 SubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL
  {IR(47160, 48), 739}, // 777 SubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL
  {IR(46151, 30), 715}, // 778 SubgroupAvcSicInitializeINTEL
  {IR(46511, 43), 724}, // 779 SubgroupAvcSicSetBilinearFilterEnableINTEL
  {IR(46602, 43), 726}, // 780 SubgroupAvcSicSetBlockBasedRawSkipSadINTEL
  {IR(46461, 50), 723}, // 781 SubgroupAvcSicSetIntraChromaModeCostFunctionINTEL
  {IR(46413, 48), 722}, // 782 SubgroupAvcSicSetIntraLumaModeCostFunctionINTEL
  {IR(46369, 44), 721}, // 783 SubgroupAvcSicSetIntraLumaShapePenaltyINTEL
  {IR(46554, 48), 725}, // 784 SubgroupAvcSicSetSkcForwardTransformEnableINTEL
  {IR(6498, 18), 363}, // 785 SubgroupBallotKHR
  {IR(50562, 27), 838}, // 786 SubgroupBlockPrefetchINTEL
  {IR(41461, 23), 592}, // 787 SubgroupBlockReadINTEL
  {IR(41484, 24), 593}, // 788 SubgroupBlockWriteINTEL
  {IR(35431, 27), 364}, // 789 SubgroupFirstInvocationKHR
  {IR(41508, 28), 594}, // 790 SubgroupImageBlockReadINTEL
  {IR(41536, 29), 595}, // 791 SubgroupImageBlockWriteINTEL
  {IR(41565, 33), 596}, // 792 SubgroupImageMediaBlockReadINTEL
  {IR(41598, 34), 597}, // 793 SubgroupImageMediaBlockWriteINTEL
  {IR(15779, 38), 844}, // 794 SubgroupMatrixMultiplyAccumulateINTEL
  {IR(35614, 26), 374}, // 795 SubgroupReadInvocationKHR
  {IR(41389, 25), 589}, // 796 SubgroupShuffleDownINTEL
  {IR(13377, 21), 588}, // 797 SubgroupShuffleINTEL
  {IR(41414, 23), 590}, // 798 SubgroupShuffleUpINTEL
  {IR(41437, 24), 591}, // 799 SubgroupShuffleXorINTEL
  {IR(32788, 7), 229}, // 800 Switch
  {IR(50376, 24), 834}, // 801 TaskSequenceAsyncALTERA
  {IR(50400, 23), 834}, // 802 TaskSequenceAsyncINTEL
  {IR(50327, 25), 833}, // 803 TaskSequenceCreateALTERA
  {IR(50352, 24), 833}, // 804 TaskSequenceCreateINTEL
  {IR(50423, 22), 835}, // 805 TaskSequenceGetALTERA
  {IR(50445, 21), 835}, // 806 TaskSequenceGetINTEL
  {IR(50466, 26), 836}, // 807 TaskSequenceReleaseALTERA
  {IR(50492, 25), 836}, // 808 TaskSequenceReleaseINTEL
  {IR(40732, 27), 565}, // 809 TensorLayoutSetBlockSizeNV
  {IR(40596, 28), 558}, // 810 TensorLayoutSetClampValueNV
  {IR(40525, 27), 555}, // 811 TensorLayoutSetDimensionNV
  {IR(40552, 24), 556}, // 812 TensorLayoutSetStrideNV
  {IR(40576, 20), 557}, // 813 TensorLayoutSliceNV
  {IR(35206, 19), 350}, // 814 TensorQuerySizeARM
  {IR(35177, 14), 348}, // 815 TensorReadARM
  {IR(40712, 20), 564}, // 816 TensorViewSetClipNV
  {IR(40643, 25), 560}, // 817 TensorViewSetDimensionNV
  {IR(40668, 22), 561}, // 818 TensorViewSetStrideNV
  {IR(35191, 15), 349}, // 819 TensorWriteARM
  {IR(35318, 20), 358}, // 820 TerminateInvocation
  {IR(35779, 16), 381}, // 821 TerminateRayKHR
  {IR(39626, 15), 526}, // 822 TerminateRayNV
  {IR(39649, 14), 528}, // 823 TraceMotionNV
  {IR(39641, 8), 527}, // 824 TraceNV
  {IR(35691, 12), 377}, // 825 TraceRayKHR
  {IR(39663, 17), 529}, // 826 TraceRayMotionNV
  {IR(30640, 10), 76}, // 827 Transpose
  {IR(39730, 29), 531}, // 828 TypeAccelerationStructureKHR
  {IR(39759, 28), 531}, // 829 TypeAccelerationStructureNV
  {IR(29589, 10), 25}, // 830 TypeArray
  {IR(42374, 37), 634}, // 831 TypeAvcImeDualReferenceStreaminINTEL
  {IR(42109, 23), 625}, // 832 TypeAvcImePayloadINTEL
  {IR(42291, 44), 632}, // 833 TypeAvcImeResultDualReferenceStreamoutINTEL
  {IR(42223, 22), 630}, // 834 TypeAvcImeResultINTEL
  {IR(42245, 46), 631}, // 835 TypeAvcImeResultSingleReferenceStreamoutINTEL
  {IR(42335, 39), 633}, // 836 TypeAvcImeSingleReferenceStreaminINTEL
  {IR(42178, 23), 628}, // 837 TypeAvcMcePayloadINTEL
  {IR(42201, 22), 629}, // 838 TypeAvcMceResultINTEL
  {IR(42132, 23), 626}, // 839 TypeAvcRefPayloadINTEL
  {IR(42411, 22), 635}, // 840 TypeAvcRefResultINTEL
  {IR(42155, 23), 627}, // 841 TypeAvcSicPayloadINTEL
  {IR(42433, 22), 636}, // 842 TypeAvcSicResultINTEL
  {IR(29351, 9), 17}, // 843 TypeBool
  {IR(37193, 14), 436}, // 844 TypeBufferEXT
  {IR(50042, 23), 823}, // 845 TypeBufferSurfaceINTEL
  {IR(35960, 25), 388}, // 846 TypeCooperativeMatrixKHR
  {IR(40052, 24), 541}, // 847 TypeCooperativeMatrixNV
  {IR(38246, 24), 480}, // 848 TypeCooperativeVectorNV
  {IR(29704, 16), 32}, // 849 TypeDeviceEvent
  {IR(29694, 10), 31}, // 850 TypeEvent
  {IR(29405, 10), 19}, // 851 TypeFloat
  {IR(29753, 19), 36}, // 852 TypeForwardPointer
  {IR(29681, 13), 30}, // 853 TypeFunction
  {IR(35305, 13), 357}, // 854 TypeGraphARM
  {IR(38987, 17), 503}, // 855 TypeHitObjectEXT
  {IR(38191, 16), 478}, // 856 TypeHitObjectNV
  {IR(29550, 10), 22}, // 857 TypeImage
  {IR(29360, 8), 18}, // 858 TypeInt
  {IR(29426, 11), 21}, // 859 TypeMatrix
  {IR(34135, 17), 300}, // 860 TypeNamedBarrier
  {IR(36995, 25), 428}, // 861 TypeNodePayloadArrayAMDX
  {IR(29627, 11), 28}, // 862 TypeOpaque
  {IR(29744, 9), 35}, // 863 TypePipe
  {IR(34013, 16), 295}, // 864 TypePipeStorage
  {IR(29669, 12), 29}, // 865 TypePointer
  {IR(29734, 10), 34}, // 866 TypeQueue
  {IR(36239, 16), 396}, // 867 TypeRayQueryKHR
  {IR(29720, 14), 33}, // 868 TypeReserveId
  {IR(29599, 17), 26}, // 869 TypeRuntimeArray
  {IR(29572, 17), 24}, // 870 TypeSampledImage
  {IR(29560, 12), 23}, // 871 TypeSampler
  {IR(29616, 11), 27}, // 872 TypeStruct
  {IR(50065, 25), 824}, // 873 TypeStructContinuedINTEL
  {IR(50517, 23), 837}, // 874 TypeTaskSequenceALTERA
  {IR(50540, 22), 837}, // 875 TypeTaskSequenceINTEL
  {IR(35121, 14), 347}, // 876 TypeTensorARM
  {IR(40468, 19), 552}, // 877 TypeTensorLayoutNV
  {IR(40487, 17), 553}, // 878 TypeTensorViewNV
  {IR(35338, 22), 359}, // 879 TypeUntypedPointerKHR
  {IR(29415, 11), 20}, // 880 TypeVector
  {IR(38230, 16), 480}, // 881 TypeVectorIdEXT
  {IR(42091, 18), 624}, // 882 TypeVmeImageINTEL
  {IR(29342, 9), 16}, // 883 TypeVoid
  {IR(41720, 13), 603}, // 884 UAddSatINTEL
  {IR(41747, 14), 605}, // 885 UAverageINTEL
  {IR(41782, 21), 607}, // 886 UAverageRoundedINTEL
  {IR(31157, 9), 103}, // 887 UConvert
  {IR(41632, 24), 598}, // 888 UCountLeadingZerosINTEL
  {IR(41656, 25), 599}, // 889 UCountTrailingZerosINTEL
  {IR(31369, 5), 123}, // 890 UDiv
  {IR(35855, 5), 383}, // 891 UDot
  {IR(35908, 11), 386}, // 892 UDotAccSat
  {IR(35919, 14), 386}, // 893 UDotAccSatKHR
  {IR(35860, 8), 383}, // 894 UDotKHR
  {IR(31729, 13), 160}, // 895 UGreaterThan
  {IR(31755, 18), 162}, // 896 UGreaterThanEqual
  {IR(31791, 10), 164}, // 897 ULessThan
  {IR(31811, 15), 166}, // 898 ULessThanEqual
  {IR(31384, 5), 126}, // 899 UMod
  {IR(41844, 15), 611}, // 900 UMul32x16INTEL
  {IR(31537, 13), 140}, // 901 UMulExtended
  {IR(41816, 13), 609}, // 902 USubSatINTEL
  {IR(28854, 6), 1}, // 903 Undef
  {IR(31634, 10), 151}, // 904 Unordered
  {IR(32819, 12), 233}, // 905 Unreachable
  {IR(35379, 22), 361}, // 906 UntypedAccessChainKHR
  {IR(35516, 22), 367}, // 907 UntypedArrayLengthKHR
  {IR(35666, 25), 376}, // 908 UntypedGroupAsyncCopyKHR
  {IR(37224, 28), 439}, // 909 UntypedImageTexelPointerEXT
  {IR(35401, 30), 362}, // 910 UntypedInBoundsAccessChainKHR
  {IR(35483, 33), 366}, // 911 UntypedInBoundsPtrAccessChainKHR
  {IR(35538, 19), 368}, // 912 UntypedPrefetchKHR
  {IR(35458, 25), 365}, // 913 UntypedPtrAccessChainKHR
  {IR(35360, 19), 360}, // 914 UntypedVariableKHR
  {IR(15845, 32), 846}, // 915 UntypedVariableLengthArrayINTEL
  {IR(30165, 9), 52}, // 916 Variable
  {IR(13833, 25), 741}, // 917 VariableLengthArrayINTEL
  {IR(30522, 21), 69}, // 918 VectorExtractDynamic
  {IR(30543, 20), 70}, // 919 VectorInsertDynamic
  {IR(30563, 14), 71}, // 920 VectorShuffle
  {IR(31445, 18), 133}, // 921 VectorTimesMatrix
  {IR(31409, 18), 131}, // 922 VectorTimesScalar
  {IR(42077, 14), 623}, // 923 VmeImageINTEL
  {IR(38529, 33), 489}, // 924 WritePackedPrimitiveIndices4x8NV
  {IR(33044, 10), 250}, // 925 WritePipe
  {IR(49330, 24), 803}, // 926 WritePipeBlockingALTERA
  {IR(49354, 23), 803}, // 927 WritePipeBlockingINTEL
}};

// Extended instruction descriptions, ordered by (extinst enum, opcode value).
// The fields in order are:
//   enum value
//   operands, an IndexRange into kOperandSpans
//   name, a character-counting IndexRange into kStrings
//   capabilities, an IndexRange into kCapabilitySpans
static const std::array<ExtInstDesc, 425> kExtInstByValue{{
    {0,IR(0, 0),IR(51426, 14),IR(1, 0)}, // DebugInfoNone in debuginfo
    {1,IR(52, 3),IR(51440, 21),IR(1, 0)}, // DebugCompilationUnit in debuginfo
    {2,IR(811, 3),IR(51513, 15),IR(1, 0)}, // DebugTypeBasic in debuginfo
    {3,IR(814, 3),IR(51562, 17),IR(1, 0)}, // DebugTypePointer in debuginfo
    {4,IR(817, 2),IR(51617, 19),IR(1, 0)}, // DebugTypeQualifier in debuginfo
    {5,IR(168, 2),IR(51636, 15),IR(1, 0)}, // DebugTypeArray in debuginfo
    {6,IR(261, 2),IR(51651, 16),IR(1, 0)}, // DebugTypeVector in debuginfo
    {7,IR(819, 6),IR(51667, 13),IR(1, 0)}, // DebugTypedef in debuginfo
    {8,IR(168, 2),IR(51680, 18),IR(1, 0)}, // DebugTypeFunction in debuginfo
    {9,IR(825, 9),IR(51698, 14),IR(1, 0)}, // DebugTypeEnum in debuginfo
    {10,IR(834, 9),IR(51750, 19),IR(1, 0)}, // DebugTypeComposite in debuginfo
    {11,IR(843, 10),IR(51769, 16),IR(1, 0)}, // DebugTypeMember in debuginfo
    {12,IR(853, 5),IR(51785, 21),IR(1, 0)}, // DebugTypeInheritance in debuginfo
    {13,IR(36, 2),IR(51806, 21),IR(1, 0)}, // DebugTypePtrToMember in debuginfo
    {14,IR(168, 2),IR(51827, 18),IR(1, 0)}, // DebugTypeTemplate in debuginfo
    {15,IR(858, 6),IR(51845, 27),IR(1, 0)}, // DebugTypeTemplateParameter in debuginfo
    {16,IR(864, 5),IR(51872, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in debuginfo
    {17,IR(869, 5),IR(51907, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in debuginfo
    {18,IR(843, 10),IR(51938, 20),IR(1, 0)}, // DebugGlobalVariable in debuginfo
    {19,IR(874, 8),IR(51958, 25),IR(1, 0)}, // DebugFunctionDeclaration in debuginfo
    {20,IR(882, 11),IR(51983, 14),IR(1, 0)}, // DebugFunction in debuginfo
    {21,IR(893, 5),IR(51997, 18),IR(1, 0)}, // DebugLexicalBlock in debuginfo
    {22,IR(898, 3),IR(52015, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in debuginfo
    {23,IR(901, 2),IR(52046, 11),IR(1, 0)}, // DebugScope in debuginfo
    {24,IR(0, 0),IR(52057, 13),IR(1, 0)}, // DebugNoScope in debuginfo
    {25,IR(903, 3),IR(52070, 15),IR(1, 0)}, // DebugInlinedAt in debuginfo
    {26,IR(906, 7),IR(52127, 19),IR(1, 0)}, // DebugLocalVariable in debuginfo
    {27,IR(36, 2),IR(52146, 21),IR(1, 0)}, // DebugInlinedVariable in debuginfo
    {28,IR(33, 3),IR(52167, 13),IR(1, 0)}, // DebugDeclare in debuginfo
    {29,IR(375, 3),IR(52180, 11),IR(1, 0)}, // DebugValue in debuginfo
    {30,IR(913, 2),IR(52224, 15),IR(1, 0)}, // DebugOperation in debuginfo
    {31,IR(747, 1),IR(52239, 16),IR(1, 0)}, // DebugExpression in debuginfo
    {32,IR(915, 4),IR(52255, 14),IR(1, 0)}, // DebugMacroDef in debuginfo
    {33,IR(898, 3),IR(52269, 16),IR(1, 0)}, // DebugMacroUndef in debuginfo
    {1,IR(10, 1),IR(52285, 6),IR(1, 0)}, // Round in glsl_std_450
    {2,IR(10, 1),IR(52291, 10),IR(1, 0)}, // RoundEven in glsl_std_450
    {3,IR(10, 1),IR(52301, 6),IR(1, 0)}, // Trunc in glsl_std_450
    {4,IR(10, 1),IR(52307, 5),IR(1, 0)}, // FAbs in glsl_std_450
    {5,IR(10, 1),IR(52312, 5),IR(1, 0)}, // SAbs in glsl_std_450
    {6,IR(10, 1),IR(52317, 6),IR(1, 0)}, // FSign in glsl_std_450
    {7,IR(10, 1),IR(52323, 6),IR(1, 0)}, // SSign in glsl_std_450
    {8,IR(10, 1),IR(52329, 6),IR(1, 0)}, // Floor in glsl_std_450
    {9,IR(10, 1),IR(52335, 5),IR(1, 0)}, // Ceil in glsl_std_450
    {10,IR(10, 1),IR(52340, 6),IR(1, 0)}, // Fract in glsl_std_450
    {11,IR(10, 1),IR(52346, 8),IR(1, 0)}, // Radians in glsl_std_450
    {12,IR(10, 1),IR(52354, 8),IR(1, 0)}, // Degrees in glsl_std_450
    {13,IR(10, 1),IR(52362, 4),IR(1, 0)}, // Sin in glsl_std_450
    {14,IR(10, 1),IR(52366, 4),IR(1, 0)}, // Cos in glsl_std_450
    {15,IR(10, 1),IR(52370, 4),IR(1, 0)}, // Tan in glsl_std_450
    {16,IR(10, 1),IR(52374, 5),IR(1, 0)}, // Asin in glsl_std_450
    {17,IR(10, 1),IR(52379, 5),IR(1, 0)}, // Acos in glsl_std_450
    {18,IR(10, 1),IR(52384, 5),IR(1, 0)}, // Atan in glsl_std_450
    {19,IR(10, 1),IR(52389, 5),IR(1, 0)}, // Sinh in glsl_std_450
    {20,IR(10, 1),IR(52394, 5),IR(1, 0)}, // Cosh in glsl_std_450
    {21,IR(10, 1),IR(52399, 5),IR(1, 0)}, // Tanh in glsl_std_450
    {22,IR(10, 1),IR(52404, 6),IR(1, 0)}, // Asinh in glsl_std_450
    {23,IR(10, 1),IR(52410, 6),IR(1, 0)}, // Acosh in glsl_std_450
    {24,IR(10, 1),IR(52416, 6),IR(1, 0)}, // Atanh in glsl_std_450
    {25,IR(36, 2),IR(52422, 6),IR(1, 0)}, // Atan2 in glsl_std_450
    {26,IR(36, 2),IR(52428, 4),IR(1, 0)}, // Pow in glsl_std_450
    {27,IR(10, 1),IR(52432, 4),IR(1, 0)}, // Exp in glsl_std_450
    {28,IR(10, 1),IR(52436, 4),IR(1, 0)}, // Log in glsl_std_450
    {29,IR(10, 1),IR(52440, 5),IR(1, 0)}, // Exp2 in glsl_std_450
    {30,IR(10, 1),IR(52445, 5),IR(1, 0)}, // Log2 in glsl_std_450
    {31,IR(10, 1),IR(52450, 5),IR(1, 0)}, // Sqrt in glsl_std_450
    {32,IR(10, 1),IR(52455, 12),IR(1, 0)}, // InverseSqrt in glsl_std_450
    {33,IR(10, 1),IR(52467, 12),IR(1, 0)}, // Determinant in glsl_std_450
    {34,IR(10, 1),IR(52479, 14),IR(1, 0)}, // MatrixInverse in glsl_std_450
    {35,IR(36, 2),IR(52493, 5),IR(1, 0)}, // Modf in glsl_std_450
    {36,IR(10, 1),IR(52498, 11),IR(1, 0)}, // ModfStruct in glsl_std_450
    {37,IR(36, 2),IR(52509, 5),IR(1, 0)}, // FMin in glsl_std_450
    {38,IR(36, 2),IR(52514, 5),IR(1, 0)}, // UMin in glsl_std_450
    {39,IR(36, 2),IR(52519, 5),IR(1, 0)}, // SMin in glsl_std_450
    {40,IR(36, 2),IR(52524, 5),IR(1, 0)}, // FMax in glsl_std_450
    {41,IR(36, 2),IR(52529, 5),IR(1, 0)}, // UMax in glsl_std_450
    {42,IR(36, 2),IR(52534, 5),IR(1, 0)}, // SMax in glsl_std_450
    {43,IR(33, 3),IR(52539, 7),IR(1, 0)}, // FClamp in glsl_std_450
    {44,IR(33, 3),IR(52546, 7),IR(1, 0)}, // UClamp in glsl_std_450
    {45,IR(33, 3),IR(52553, 7),IR(1, 0)}, // SClamp in glsl_std_450
    {46,IR(33, 3),IR(52560, 5),IR(1, 0)}, // FMix in glsl_std_450
    {47,IR(33, 3),IR(52565, 5),IR(1, 0)}, // IMix in glsl_std_450
    {48,IR(36, 2),IR(52570, 5),IR(1, 0)}, // Step in glsl_std_450
    {49,IR(33, 3),IR(52575, 11),IR(1, 0)}, // SmoothStep in glsl_std_450
    {50,IR(33, 3),IR(52586, 4),IR(1, 0)}, // Fma in glsl_std_450
    {51,IR(36, 2),IR(52590, 6),IR(1, 0)}, // Frexp in glsl_std_450
    {52,IR(10, 1),IR(52596, 12),IR(1, 0)}, // FrexpStruct in glsl_std_450
    {53,IR(36, 2),IR(52608, 6),IR(1, 0)}, // Ldexp in glsl_std_450
    {54,IR(10, 1),IR(52614, 13),IR(1, 0)}, // PackSnorm4x8 in glsl_std_450
    {55,IR(10, 1),IR(52627, 13),IR(1, 0)}, // PackUnorm4x8 in glsl_std_450
    {56,IR(10, 1),IR(52640, 14),IR(1, 0)}, // PackSnorm2x16 in glsl_std_450
    {57,IR(10, 1),IR(52654, 14),IR(1, 0)}, // PackUnorm2x16 in glsl_std_450
    {58,IR(10, 1),IR(52668, 13),IR(1, 0)}, // PackHalf2x16 in glsl_std_450
    {59,IR(10, 1),IR(52681, 15),IR(332, 1)}, // PackDouble2x32 in glsl_std_450
    {60,IR(10, 1),IR(52696, 16),IR(1, 0)}, // UnpackSnorm2x16 in glsl_std_450
    {61,IR(10, 1),IR(52712, 16),IR(1, 0)}, // UnpackUnorm2x16 in glsl_std_450
    {62,IR(10, 1),IR(52728, 15),IR(1, 0)}, // UnpackHalf2x16 in glsl_std_450
    {63,IR(10, 1),IR(52743, 15),IR(1, 0)}, // UnpackSnorm4x8 in glsl_std_450
    {64,IR(10, 1),IR(52758, 15),IR(1, 0)}, // UnpackUnorm4x8 in glsl_std_450
    {65,IR(10, 1),IR(52773, 17),IR(332, 1)}, // UnpackDouble2x32 in glsl_std_450
    {66,IR(10, 1),IR(52790, 7),IR(1, 0)}, // Length in glsl_std_450
    {67,IR(36, 2),IR(52797, 9),IR(1, 0)}, // Distance in glsl_std_450
    {68,IR(36, 2),IR(52806, 6),IR(1, 0)}, // Cross in glsl_std_450
    {69,IR(10, 1),IR(52812, 10),IR(1, 0)}, // Normalize in glsl_std_450
    {70,IR(33, 3),IR(52822, 12),IR(1, 0)}, // FaceForward in glsl_std_450
    {71,IR(36, 2),IR(52834, 8),IR(1, 0)}, // Reflect in glsl_std_450
    {72,IR(33, 3),IR(52842, 8),IR(1, 0)}, // Refract in glsl_std_450
    {73,IR(10, 1),IR(52850, 9),IR(1, 0)}, // FindILsb in glsl_std_450
    {74,IR(10, 1),IR(52859, 9),IR(1, 0)}, // FindSMsb in glsl_std_450
    {75,IR(10, 1),IR(52868, 9),IR(1, 0)}, // FindUMsb in glsl_std_450
    {76,IR(10, 1),IR(52877, 22),IR(333, 1)}, // InterpolateAtCentroid in glsl_std_450
    {77,IR(36, 2),IR(52899, 20),IR(333, 1)}, // InterpolateAtSample in glsl_std_450
    {78,IR(36, 2),IR(52919, 20),IR(333, 1)}, // InterpolateAtOffset in glsl_std_450
    {79,IR(36, 2),IR(52939, 5),IR(1, 0)}, // NMin in glsl_std_450
    {80,IR(36, 2),IR(52944, 5),IR(1, 0)}, // NMax in glsl_std_450
    {81,IR(33, 3),IR(52949, 7),IR(1, 0)}, // NClamp in glsl_std_450
    {1,IR(399, 5),IR(5717, 7),IR(1, 0)}, // Kernel in nonsemantic_clspvreflection
    {2,IR(919, 5),IR(52956, 13),IR(1, 0)}, // ArgumentInfo in nonsemantic_clspvreflection
    {3,IR(593, 5),IR(52969, 22),IR(1, 0)}, // ArgumentStorageBuffer in nonsemantic_clspvreflection
    {4,IR(593, 5),IR(52991, 16),IR(1, 0)}, // ArgumentUniform in nonsemantic_clspvreflection
    {5,IR(557, 7),IR(53007, 25),IR(1, 0)}, // ArgumentPodStorageBuffer in nonsemantic_clspvreflection
    {6,IR(557, 7),IR(53032, 19),IR(1, 0)}, // ArgumentPodUniform in nonsemantic_clspvreflection
    {7,IR(593, 5),IR(53051, 24),IR(1, 0)}, // ArgumentPodPushConstant in nonsemantic_clspvreflection
    {8,IR(593, 5),IR(53075, 21),IR(1, 0)}, // ArgumentSampledImage in nonsemantic_clspvreflection
    {9,IR(593, 5),IR(53096, 21),IR(1, 0)}, // ArgumentStorageImage in nonsemantic_clspvreflection
    {10,IR(593, 5),IR(53117, 16),IR(1, 0)}, // ArgumentSampler in nonsemantic_clspvreflection
    {11,IR(593, 5),IR(53133, 18),IR(1, 0)}, // ArgumentWorkgroup in nonsemantic_clspvreflection
    {12,IR(33, 3),IR(53151, 26),IR(1, 0)}, // SpecConstantWorkgroupSize in nonsemantic_clspvreflection
    {13,IR(33, 3),IR(53177, 25),IR(1, 0)}, // SpecConstantGlobalOffset in nonsemantic_clspvreflection
    {14,IR(10, 1),IR(53202, 20),IR(1, 0)}, // SpecConstantWorkDim in nonsemantic_clspvreflection
    {15,IR(36, 2),IR(53222, 25),IR(1, 0)}, // PushConstantGlobalOffset in nonsemantic_clspvreflection
    {16,IR(36, 2),IR(53247, 30),IR(1, 0)}, // PushConstantEnqueuedLocalSize in nonsemantic_clspvreflection
    {17,IR(36, 2),IR(53277, 23),IR(1, 0)}, // PushConstantGlobalSize in nonsemantic_clspvreflection
    {18,IR(36, 2),IR(53300, 25),IR(1, 0)}, // PushConstantRegionOffset in nonsemantic_clspvreflection
    {19,IR(36, 2),IR(53325, 26),IR(1, 0)}, // PushConstantNumWorkgroups in nonsemantic_clspvreflection
    {20,IR(36, 2),IR(53351, 30),IR(1, 0)}, // PushConstantRegionGroupOffset in nonsemantic_clspvreflection
    {21,IR(33, 3),IR(53381, 26),IR(1, 0)}, // ConstantDataStorageBuffer in nonsemantic_clspvreflection
    {22,IR(33, 3),IR(53407, 20),IR(1, 0)}, // ConstantDataUniform in nonsemantic_clspvreflection
    {23,IR(33, 3),IR(9191, 15),IR(1, 0)}, // LiteralSampler in nonsemantic_clspvreflection
    {24,IR(296, 4),IR(53427, 30),IR(1, 0)}, // PropertyRequiredWorkgroupSize in nonsemantic_clspvreflection
    {25,IR(10, 1),IR(53457, 28),IR(1, 0)}, // SpecConstantSubgroupMaxSize in nonsemantic_clspvreflection
    {26,IR(593, 5),IR(53485, 28),IR(1, 0)}, // ArgumentPointerPushConstant in nonsemantic_clspvreflection
    {27,IR(557, 7),IR(53513, 23),IR(1, 0)}, // ArgumentPointerUniform in nonsemantic_clspvreflection
    {28,IR(33, 3),IR(53536, 35),IR(1, 0)}, // ProgramScopeVariablesStorageBuffer in nonsemantic_clspvreflection
    {29,IR(33, 3),IR(53571, 38),IR(1, 0)}, // ProgramScopeVariablePointerRelocation in nonsemantic_clspvreflection
    {30,IR(296, 4),IR(53609, 42),IR(1, 0)}, // ImageArgumentInfoChannelOrderPushConstant in nonsemantic_clspvreflection
    {31,IR(296, 4),IR(53651, 45),IR(1, 0)}, // ImageArgumentInfoChannelDataTypePushConstant in nonsemantic_clspvreflection
    {32,IR(528, 6),IR(53696, 37),IR(1, 0)}, // ImageArgumentInfoChannelOrderUniform in nonsemantic_clspvreflection
    {33,IR(528, 6),IR(53733, 40),IR(1, 0)}, // ImageArgumentInfoChannelDataTypeUniform in nonsemantic_clspvreflection
    {34,IR(593, 5),IR(53773, 27),IR(1, 0)}, // ArgumentStorageTexelBuffer in nonsemantic_clspvreflection
    {35,IR(593, 5),IR(53800, 27),IR(1, 0)}, // ArgumentUniformTexelBuffer in nonsemantic_clspvreflection
    {36,IR(33, 3),IR(53827, 32),IR(1, 0)}, // ConstantDataPointerPushConstant in nonsemantic_clspvreflection
    {37,IR(33, 3),IR(53859, 40),IR(1, 0)}, // ProgramScopeVariablePointerPushConstant in nonsemantic_clspvreflection
    {38,IR(375, 3),IR(53899, 11),IR(1, 0)}, // PrintfInfo in nonsemantic_clspvreflection
    {39,IR(33, 3),IR(53910, 26),IR(1, 0)}, // PrintfBufferStorageBuffer in nonsemantic_clspvreflection
    {40,IR(33, 3),IR(53936, 32),IR(1, 0)}, // PrintfBufferPointerPushConstant in nonsemantic_clspvreflection
    {41,IR(296, 4),IR(53968, 34),IR(1, 0)}, // NormalizedSamplerMaskPushConstant in nonsemantic_clspvreflection
    {42,IR(36, 2),IR(54002, 22),IR(1, 0)}, // WorkgroupVariableSize in nonsemantic_clspvreflection
    {0,IR(0, 0),IR(51426, 14),IR(1, 0)}, // DebugInfoNone in nonsemantic_shader_debuginfo_100
    {1,IR(296, 4),IR(51440, 21),IR(1, 0)}, // DebugCompilationUnit in nonsemantic_shader_debuginfo_100
    {2,IR(296, 4),IR(51513, 15),IR(1, 0)}, // DebugTypeBasic in nonsemantic_shader_debuginfo_100
    {3,IR(33, 3),IR(51562, 17),IR(1, 0)}, // DebugTypePointer in nonsemantic_shader_debuginfo_100
    {4,IR(36, 2),IR(51617, 19),IR(1, 0)}, // DebugTypeQualifier in nonsemantic_shader_debuginfo_100
    {5,IR(168, 2),IR(51636, 15),IR(1, 0)}, // DebugTypeArray in nonsemantic_shader_debuginfo_100
    {6,IR(36, 2),IR(51651, 16),IR(1, 0)}, // DebugTypeVector in nonsemantic_shader_debuginfo_100
    {7,IR(528, 6),IR(51667, 13),IR(1, 0)}, // DebugTypedef in nonsemantic_shader_debuginfo_100
    {8,IR(375, 3),IR(51680, 18),IR(1, 0)}, // DebugTypeFunction in nonsemantic_shader_debuginfo_100
    {9,IR(924, 9),IR(51698, 14),IR(1, 0)}, // DebugTypeEnum in nonsemantic_shader_debuginfo_100
    {10,IR(933, 10),IR(51750, 19),IR(1, 0)}, // DebugTypeComposite in nonsemantic_shader_debuginfo_100
    {11,IR(943, 9),IR(51769, 16),IR(1, 0)}, // DebugTypeMember in nonsemantic_shader_debuginfo_100
    {12,IR(296, 4),IR(51785, 21),IR(1, 0)}, // DebugTypeInheritance in nonsemantic_shader_debuginfo_100
    {13,IR(36, 2),IR(51806, 21),IR(1, 0)}, // DebugTypePtrToMember in nonsemantic_shader_debuginfo_100
    {14,IR(168, 2),IR(51827, 18),IR(1, 0)}, // DebugTypeTemplate in nonsemantic_shader_debuginfo_100
    {15,IR(528, 6),IR(51845, 27),IR(1, 0)}, // DebugTypeTemplateParameter in nonsemantic_shader_debuginfo_100
    {16,IR(675, 5),IR(51872, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in nonsemantic_shader_debuginfo_100
    {17,IR(952, 5),IR(51907, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in nonsemantic_shader_debuginfo_100
    {18,IR(957, 10),IR(51938, 20),IR(1, 0)}, // DebugGlobalVariable in nonsemantic_shader_debuginfo_100
    {19,IR(471, 8),IR(51958, 25),IR(1, 0)}, // DebugFunctionDeclaration in nonsemantic_shader_debuginfo_100
    {20,IR(957, 10),IR(51983, 14),IR(1, 0)}, // DebugFunction in nonsemantic_shader_debuginfo_100
    {21,IR(593, 5),IR(51997, 18),IR(1, 0)}, // DebugLexicalBlock in nonsemantic_shader_debuginfo_100
    {22,IR(33, 3),IR(52015, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in nonsemantic_shader_debuginfo_100
    {23,IR(901, 2),IR(52046, 11),IR(1, 0)}, // DebugScope in nonsemantic_shader_debuginfo_100
    {24,IR(0, 0),IR(52057, 13),IR(1, 0)}, // DebugNoScope in nonsemantic_shader_debuginfo_100
    {25,IR(967, 3),IR(52070, 15),IR(1, 0)}, // DebugInlinedAt in nonsemantic_shader_debuginfo_100
    {26,IR(970, 8),IR(52127, 19),IR(1, 0)}, // DebugLocalVariable in nonsemantic_shader_debuginfo_100
    {27,IR(36, 2),IR(52146, 21),IR(1, 0)}, // DebugInlinedVariable in nonsemantic_shader_debuginfo_100
    {28,IR(978, 4),IR(52167, 13),IR(1, 0)}, // DebugDeclare in nonsemantic_shader_debuginfo_100
    {29,IR(978, 4),IR(52180, 11),IR(1, 0)}, // DebugValue in nonsemantic_shader_debuginfo_100
    {30,IR(168, 2),IR(52224, 15),IR(1, 0)}, // DebugOperation in nonsemantic_shader_debuginfo_100
    {31,IR(747, 1),IR(52239, 16),IR(1, 0)}, // DebugExpression in nonsemantic_shader_debuginfo_100
    {32,IR(580, 4),IR(52255, 14),IR(1, 0)}, // DebugMacroDef in nonsemantic_shader_debuginfo_100
    {33,IR(33, 3),IR(52269, 16),IR(1, 0)}, // DebugMacroUndef in nonsemantic_shader_debuginfo_100
    {34,IR(509, 7),IR(54024, 20),IR(1, 0)}, // DebugImportedEntity in nonsemantic_shader_debuginfo_100
    {35,IR(901, 2),IR(54044, 12),IR(1, 0)}, // DebugSource in nonsemantic_shader_debuginfo_100
    {101,IR(36, 2),IR(54056, 24),IR(1, 0)}, // DebugFunctionDefinition in nonsemantic_shader_debuginfo_100
    {102,IR(10, 1),IR(54080, 21),IR(1, 0)}, // DebugSourceContinued in nonsemantic_shader_debuginfo_100
    {103,IR(675, 5),IR(54101, 10),IR(1, 0)}, // DebugLine in nonsemantic_shader_debuginfo_100
    {104,IR(0, 0),IR(54111, 12),IR(1, 0)}, // DebugNoLine in nonsemantic_shader_debuginfo_100
    {105,IR(36, 2),IR(54123, 21),IR(1, 0)}, // DebugBuildIdentifier in nonsemantic_shader_debuginfo_100
    {106,IR(10, 1),IR(54144, 17),IR(1, 0)}, // DebugStoragePath in nonsemantic_shader_debuginfo_100
    {107,IR(296, 4),IR(54161, 16),IR(1, 0)}, // DebugEntryPoint in nonsemantic_shader_debuginfo_100
    {108,IR(33, 3),IR(54177, 16),IR(1, 0)}, // DebugTypeMatrix in nonsemantic_shader_debuginfo_100
    {1,IR(765, 9),IR(54193, 14),IR(1, 0)}, // Configuration in nonsemantic_vkspreflection
    {2,IR(10, 1),IR(54207, 13),IR(1, 0)}, // StartCounter in nonsemantic_vkspreflection
    {3,IR(10, 1),IR(54220, 12),IR(1, 0)}, // StopCounter in nonsemantic_vkspreflection
    {4,IR(296, 4),IR(54232, 14),IR(1, 0)}, // PushConstants in nonsemantic_vkspreflection
    {5,IR(33, 3),IR(54246, 23),IR(1, 0)}, // SpecializationMapEntry in nonsemantic_vkspreflection
    {6,IR(982, 15),IR(54269, 20),IR(1, 0)}, // DescriptorSetBuffer in nonsemantic_vkspreflection
    {7,IR(997, 33),IR(54289, 19),IR(1, 0)}, // DescriptorSetImage in nonsemantic_vkspreflection
    {8,IR(1030, 19),IR(54308, 21),IR(1, 0)}, // DescriptorSetSampler in nonsemantic_vkspreflection
    {0,IR(0, 0),IR(51426, 14),IR(1, 0)}, // DebugInfoNone in opencl_debuginfo_100
    {1,IR(1049, 4),IR(51440, 21),IR(1, 0)}, // DebugCompilationUnit in opencl_debuginfo_100
    {2,IR(1053, 3),IR(51513, 15),IR(1, 0)}, // DebugTypeBasic in opencl_debuginfo_100
    {3,IR(1056, 3),IR(51562, 17),IR(1, 0)}, // DebugTypePointer in opencl_debuginfo_100
    {4,IR(1059, 2),IR(51617, 19),IR(1, 0)}, // DebugTypeQualifier in opencl_debuginfo_100
    {5,IR(168, 2),IR(51636, 15),IR(1, 0)}, // DebugTypeArray in opencl_debuginfo_100
    {6,IR(261, 2),IR(51651, 16),IR(1, 0)}, // DebugTypeVector in opencl_debuginfo_100
    {7,IR(819, 6),IR(51667, 13),IR(1, 0)}, // DebugTypedef in opencl_debuginfo_100
    {8,IR(1061, 3),IR(51680, 18),IR(1, 0)}, // DebugTypeFunction in opencl_debuginfo_100
    {9,IR(1064, 9),IR(51698, 14),IR(1, 0)}, // DebugTypeEnum in opencl_debuginfo_100
    {10,IR(1073, 10),IR(51750, 19),IR(1, 0)}, // DebugTypeComposite in opencl_debuginfo_100
    {11,IR(1083, 10),IR(51769, 16),IR(1, 0)}, // DebugTypeMember in opencl_debuginfo_100
    {12,IR(1093, 5),IR(51785, 21),IR(1, 0)}, // DebugTypeInheritance in opencl_debuginfo_100
    {13,IR(36, 2),IR(51806, 21),IR(1, 0)}, // DebugTypePtrToMember in opencl_debuginfo_100
    {14,IR(168, 2),IR(51827, 18),IR(1, 0)}, // DebugTypeTemplate in opencl_debuginfo_100
    {15,IR(858, 6),IR(51845, 27),IR(1, 0)}, // DebugTypeTemplateParameter in opencl_debuginfo_100
    {16,IR(864, 5),IR(51872, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in opencl_debuginfo_100
    {17,IR(869, 5),IR(51907, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in opencl_debuginfo_100
    {18,IR(1083, 10),IR(51938, 20),IR(1, 0)}, // DebugGlobalVariable in opencl_debuginfo_100
    {19,IR(1098, 8),IR(51958, 25),IR(1, 0)}, // DebugFunctionDeclaration in opencl_debuginfo_100
    {20,IR(1106, 11),IR(51983, 14),IR(1, 0)}, // DebugFunction in opencl_debuginfo_100
    {21,IR(893, 5),IR(51997, 18),IR(1, 0)}, // DebugLexicalBlock in opencl_debuginfo_100
    {22,IR(898, 3),IR(52015, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in opencl_debuginfo_100
    {23,IR(901, 2),IR(52046, 11),IR(1, 0)}, // DebugScope in opencl_debuginfo_100
    {24,IR(0, 0),IR(52057, 13),IR(1, 0)}, // DebugNoScope in opencl_debuginfo_100
    {25,IR(903, 3),IR(52070, 15),IR(1, 0)}, // DebugInlinedAt in opencl_debuginfo_100
    {26,IR(1117, 8),IR(52127, 19),IR(1, 0)}, // DebugLocalVariable in opencl_debuginfo_100
    {27,IR(36, 2),IR(52146, 21),IR(1, 0)}, // DebugInlinedVariable in opencl_debuginfo_100
    {28,IR(33, 3),IR(52167, 13),IR(1, 0)}, // DebugDeclare in opencl_debuginfo_100
    {29,IR(978, 4),IR(52180, 11),IR(1, 0)}, // DebugValue in opencl_debuginfo_100
    {30,IR(1125, 2),IR(52224, 15),IR(1, 0)}, // DebugOperation in opencl_debuginfo_100
    {31,IR(747, 1),IR(52239, 16),IR(1, 0)}, // DebugExpression in opencl_debuginfo_100
    {32,IR(915, 4),IR(52255, 14),IR(1, 0)}, // DebugMacroDef in opencl_debuginfo_100
    {33,IR(898, 3),IR(52269, 16),IR(1, 0)}, // DebugMacroUndef in opencl_debuginfo_100
    {34,IR(1127, 7),IR(54024, 20),IR(1, 0)}, // DebugImportedEntity in opencl_debuginfo_100
    {35,IR(901, 2),IR(54044, 12),IR(1, 0)}, // DebugSource in opencl_debuginfo_100
    {36,IR(1134, 8),IR(54629, 17),IR(1, 0)}, // DebugModuleINTEL in opencl_debuginfo_100
    {0,IR(10, 1),IR(54646, 5),IR(1, 0)}, // acos in opencl_std_100
    {1,IR(10, 1),IR(54651, 6),IR(1, 0)}, // acosh in opencl_std_100
    {2,IR(10, 1),IR(54657, 7),IR(1, 0)}, // acospi in opencl_std_100
    {3,IR(10, 1),IR(54664, 5),IR(1, 0)}, // asin in opencl_std_100
    {4,IR(10, 1),IR(54669, 6),IR(1, 0)}, // asinh in opencl_std_100
    {5,IR(10, 1),IR(54675, 7),IR(1, 0)}, // asinpi in opencl_std_100
    {6,IR(10, 1),IR(54682, 5),IR(1, 0)}, // atan in opencl_std_100
    {7,IR(36, 2),IR(54687, 6),IR(1, 0)}, // atan2 in opencl_std_100
    {8,IR(10, 1),IR(54693, 6),IR(1, 0)}, // atanh in opencl_std_100
    {9,IR(10, 1),IR(54699, 7),IR(1, 0)}, // atanpi in opencl_std_100
    {10,IR(36, 2),IR(54706, 8),IR(1, 0)}, // atan2pi in opencl_std_100
    {11,IR(10, 1),IR(54714, 5),IR(1, 0)}, // cbrt in opencl_std_100
    {12,IR(10, 1),IR(54719, 5),IR(1, 0)}, // ceil in opencl_std_100
    {13,IR(36, 2),IR(54724, 9),IR(1, 0)}, // copysign in opencl_std_100
    {14,IR(10, 1),IR(54733, 4),IR(1, 0)}, // cos in opencl_std_100
    {15,IR(10, 1),IR(54737, 5),IR(1, 0)}, // cosh in opencl_std_100
    {16,IR(10, 1),IR(54742, 6),IR(1, 0)}, // cospi in opencl_std_100
    {17,IR(10, 1),IR(54748, 5),IR(1, 0)}, // erfc in opencl_std_100
    {18,IR(10, 1),IR(54753, 4),IR(1, 0)}, // erf in opencl_std_100
    {19,IR(10, 1),IR(54757, 4),IR(1, 0)}, // exp in opencl_std_100
    {20,IR(10, 1),IR(54761, 5),IR(1, 0)}, // exp2 in opencl_std_100
    {21,IR(10, 1),IR(54766, 6),IR(1, 0)}, // exp10 in opencl_std_100
    {22,IR(10, 1),IR(54772, 6),IR(1, 0)}, // expm1 in opencl_std_100
    {23,IR(10, 1),IR(54778, 5),IR(1, 0)}, // fabs in opencl_std_100
    {24,IR(36, 2),IR(54783, 5),IR(1, 0)}, // fdim in opencl_std_100
    {25,IR(10, 1),IR(54788, 6),IR(1, 0)}, // floor in opencl_std_100
    {26,IR(33, 3),IR(54794, 4),IR(1, 0)}, // fma in opencl_std_100
    {27,IR(36, 2),IR(54798, 5),IR(1, 0)}, // fmax in opencl_std_100
    {28,IR(36, 2),IR(54803, 5),IR(1, 0)}, // fmin in opencl_std_100
    {29,IR(36, 2),IR(54808, 5),IR(1, 0)}, // fmod in opencl_std_100
    {30,IR(36, 2),IR(54813, 6),IR(1, 0)}, // fract in opencl_std_100
    {31,IR(36, 2),IR(54819, 6),IR(1, 0)}, // frexp in opencl_std_100
    {32,IR(36, 2),IR(54825, 6),IR(1, 0)}, // hypot in opencl_std_100
    {33,IR(10, 1),IR(54831, 6),IR(1, 0)}, // ilogb in opencl_std_100
    {34,IR(36, 2),IR(54837, 6),IR(1, 0)}, // ldexp in opencl_std_100
    {35,IR(10, 1),IR(54843, 7),IR(1, 0)}, // lgamma in opencl_std_100
    {36,IR(36, 2),IR(54850, 9),IR(1, 0)}, // lgamma_r in opencl_std_100
    {37,IR(10, 1),IR(54859, 4),IR(1, 0)}, // log in opencl_std_100
    {38,IR(10, 1),IR(54863, 5),IR(1, 0)}, // log2 in opencl_std_100
    {39,IR(10, 1),IR(54868, 6),IR(1, 0)}, // log10 in opencl_std_100
    {40,IR(10, 1),IR(54874, 6),IR(1, 0)}, // log1p in opencl_std_100
    {41,IR(10, 1),IR(54880, 5),IR(1, 0)}, // logb in opencl_std_100
    {42,IR(33, 3),IR(54885, 4),IR(1, 0)}, // mad in opencl_std_100
    {43,IR(36, 2),IR(54889, 7),IR(1, 0)}, // maxmag in opencl_std_100
    {44,IR(36, 2),IR(54896, 7),IR(1, 0)}, // minmag in opencl_std_100
    {45,IR(36, 2),IR(54903, 5),IR(1, 0)}, // modf in opencl_std_100
    {46,IR(10, 1),IR(54908, 4),IR(1, 0)}, // nan in opencl_std_100
    {47,IR(36, 2),IR(54912, 10),IR(1, 0)}, // nextafter in opencl_std_100
    {48,IR(36, 2),IR(54922, 4),IR(1, 0)}, // pow in opencl_std_100
    {49,IR(36, 2),IR(54926, 5),IR(1, 0)}, // pown in opencl_std_100
    {50,IR(36, 2),IR(54931, 5),IR(1, 0)}, // powr in opencl_std_100
    {51,IR(36, 2),IR(54936, 10),IR(1, 0)}, // remainder in opencl_std_100
    {52,IR(33, 3),IR(54946, 7),IR(1, 0)}, // remquo in opencl_std_100
    {53,IR(10, 1),IR(54953, 5),IR(1, 0)}, // rint in opencl_std_100
    {54,IR(36, 2),IR(54958, 6),IR(1, 0)}, // rootn in opencl_std_100
    {55,IR(10, 1),IR(54964, 6),IR(1, 0)}, // round in opencl_std_100
    {56,IR(10, 1),IR(54970, 6),IR(1, 0)}, // rsqrt in opencl_std_100
    {57,IR(10, 1),IR(54976, 4),IR(1, 0)}, // sin in opencl_std_100
    {58,IR(36, 2),IR(54980, 7),IR(1, 0)}, // sincos in opencl_std_100
    {59,IR(10, 1),IR(54987, 5),IR(1, 0)}, // sinh in opencl_std_100
    {60,IR(10, 1),IR(54992, 6),IR(1, 0)}, // sinpi in opencl_std_100
    {61,IR(10, 1),IR(54998, 5),IR(1, 0)}, // sqrt in opencl_std_100
    {62,IR(10, 1),IR(55003, 4),IR(1, 0)}, // tan in opencl_std_100
    {63,IR(10, 1),IR(55007, 5),IR(1, 0)}, // tanh in opencl_std_100
    {64,IR(10, 1),IR(55012, 6),IR(1, 0)}, // tanpi in opencl_std_100
    {65,IR(10, 1),IR(55018, 7),IR(1, 0)}, // tgamma in opencl_std_100
    {66,IR(10, 1),IR(55025, 6),IR(1, 0)}, // trunc in opencl_std_100
    {67,IR(10, 1),IR(55031, 9),IR(1, 0)}, // half_cos in opencl_std_100
    {68,IR(36, 2),IR(55040, 12),IR(1, 0)}, // half_divide in opencl_std_100
    {69,IR(10, 1),IR(55052, 9),IR(1, 0)}, // half_exp in opencl_std_100
    {70,IR(10, 1),IR(55061, 10),IR(1, 0)}, // half_exp2 in opencl_std_100
    {71,IR(10, 1),IR(55071, 11),IR(1, 0)}, // half_exp10 in opencl_std_100
    {72,IR(10, 1),IR(55082, 9),IR(1, 0)}, // half_log in opencl_std_100
    {73,IR(10, 1),IR(55091, 10),IR(1, 0)}, // half_log2 in opencl_std_100
    {74,IR(10, 1),IR(55101, 11),IR(1, 0)}, // half_log10 in opencl_std_100
    {75,IR(36, 2),IR(55112, 10),IR(1, 0)}, // half_powr in opencl_std_100
    {76,IR(10, 1),IR(55122, 11),IR(1, 0)}, // half_recip in opencl_std_100
    {77,IR(10, 1),IR(55133, 11),IR(1, 0)}, // half_rsqrt in opencl_std_100
    {78,IR(10, 1),IR(55144, 9),IR(1, 0)}, // half_sin in opencl_std_100
    {79,IR(10, 1),IR(55153, 10),IR(1, 0)}, // half_sqrt in opencl_std_100
    {80,IR(10, 1),IR(55163, 9),IR(1, 0)}, // half_tan in opencl_std_100
    {81,IR(10, 1),IR(55172, 11),IR(1, 0)}, // native_cos in opencl_std_100
    {82,IR(36, 2),IR(55183, 14),IR(1, 0)}, // native_divide in opencl_std_100
    {83,IR(10, 1),IR(55197, 11),IR(1, 0)}, // native_exp in opencl_std_100
    {84,IR(10, 1),IR(55208, 12),IR(1, 0)}, // native_exp2 in opencl_std_100
    {85,IR(10, 1),IR(55220, 13),IR(1, 0)}, // native_exp10 in opencl_std_100
    {86,IR(10, 1),IR(55233, 11),IR(1, 0)}, // native_log in opencl_std_100
    {87,IR(10, 1),IR(55244, 12),IR(1, 0)}, // native_log2 in opencl_std_100
    {88,IR(10, 1),IR(55256, 13),IR(1, 0)}, // native_log10 in opencl_std_100
    {89,IR(36, 2),IR(55269, 12),IR(1, 0)}, // native_powr in opencl_std_100
    {90,IR(10, 1),IR(55281, 13),IR(1, 0)}, // native_recip in opencl_std_100
    {91,IR(10, 1),IR(55294, 13),IR(1, 0)}, // native_rsqrt in opencl_std_100
    {92,IR(10, 1),IR(55307, 11),IR(1, 0)}, // native_sin in opencl_std_100
    {93,IR(10, 1),IR(55318, 12),IR(1, 0)}, // native_sqrt in opencl_std_100
    {94,IR(10, 1),IR(55330, 11),IR(1, 0)}, // native_tan in opencl_std_100
    {95,IR(33, 3),IR(55341, 7),IR(1, 0)}, // fclamp in opencl_std_100
    {96,IR(10, 1),IR(55348, 8),IR(1, 0)}, // degrees in opencl_std_100
    {97,IR(36, 2),IR(55356, 12),IR(1, 0)}, // fmax_common in opencl_std_100
    {98,IR(36, 2),IR(55368, 12),IR(1, 0)}, // fmin_common in opencl_std_100
    {99,IR(33, 3),IR(55380, 4),IR(1, 0)}, // mix in opencl_std_100
    {100,IR(10, 1),IR(55384, 8),IR(1, 0)}, // radians in opencl_std_100
    {101,IR(36, 2),IR(55392, 5),IR(1, 0)}, // step in opencl_std_100
    {102,IR(33, 3),IR(55397, 11),IR(1, 0)}, // smoothstep in opencl_std_100
    {103,IR(10, 1),IR(55408, 5),IR(1, 0)}, // sign in opencl_std_100
    {104,IR(36, 2),IR(55413, 6),IR(1, 0)}, // cross in opencl_std_100
    {105,IR(36, 2),IR(55419, 9),IR(1, 0)}, // distance in opencl_std_100
    {106,IR(10, 1),IR(55428, 7),IR(1, 0)}, // length in opencl_std_100
    {107,IR(10, 1),IR(55435, 10),IR(1, 0)}, // normalize in opencl_std_100
    {108,IR(36, 2),IR(55445, 14),IR(1, 0)}, // fast_distance in opencl_std_100
    {109,IR(10, 1),IR(55459, 12),IR(1, 0)}, // fast_length in opencl_std_100
    {110,IR(10, 1),IR(55471, 15),IR(1, 0)}, // fast_normalize in opencl_std_100
    {141,IR(10, 1),IR(55486, 6),IR(1, 0)}, // s_abs in opencl_std_100
    {142,IR(36, 2),IR(55492, 11),IR(1, 0)}, // s_abs_diff in opencl_std_100
    {143,IR(36, 2),IR(55503, 10),IR(1, 0)}, // s_add_sat in opencl_std_100
    {144,IR(36, 2),IR(55513, 10),IR(1, 0)}, // u_add_sat in opencl_std_100
    {145,IR(36, 2),IR(55523, 7),IR(1, 0)}, // s_hadd in opencl_std_100
    {146,IR(36, 2),IR(55530, 7),IR(1, 0)}, // u_hadd in opencl_std_100
    {147,IR(36, 2),IR(55537, 8),IR(1, 0)}, // s_rhadd in opencl_std_100
    {148,IR(36, 2),IR(55545, 8),IR(1, 0)}, // u_rhadd in opencl_std_100
    {149,IR(33, 3),IR(55553, 8),IR(1, 0)}, // s_clamp in opencl_std_100
    {150,IR(33, 3),IR(55561, 8),IR(1, 0)}, // u_clamp in opencl_std_100
    {151,IR(10, 1),IR(55569, 4),IR(1, 0)}, // clz in opencl_std_100
    {152,IR(10, 1),IR(55573, 4),IR(1, 0)}, // ctz in opencl_std_100
    {153,IR(33, 3),IR(55577, 9),IR(1, 0)}, // s_mad_hi in opencl_std_100
    {154,IR(33, 3),IR(55586, 10),IR(1, 0)}, // u_mad_sat in opencl_std_100
    {155,IR(33, 3),IR(55596, 10),IR(1, 0)}, // s_mad_sat in opencl_std_100
    {156,IR(36, 2),IR(55606, 6),IR(1, 0)}, // s_max in opencl_std_100
    {157,IR(36, 2),IR(55612, 6),IR(1, 0)}, // u_max in opencl_std_100
    {158,IR(36, 2),IR(55618, 6),IR(1, 0)}, // s_min in opencl_std_100
    {159,IR(36, 2),IR(55624, 6),IR(1, 0)}, // u_min in opencl_std_100
    {160,IR(36, 2),IR(55630, 9),IR(1, 0)}, // s_mul_hi in opencl_std_100
    {161,IR(36, 2),IR(55639, 7),IR(1, 0)}, // rotate in opencl_std_100
    {162,IR(36, 2),IR(55646, 10),IR(1, 0)}, // s_sub_sat in opencl_std_100
    {163,IR(36, 2),IR(55656, 10),IR(1, 0)}, // u_sub_sat in opencl_std_100
    {164,IR(36, 2),IR(55666, 11),IR(1, 0)}, // u_upsample in opencl_std_100
    {165,IR(36, 2),IR(55677, 11),IR(1, 0)}, // s_upsample in opencl_std_100
    {166,IR(10, 1),IR(55688, 9),IR(1, 0)}, // popcount in opencl_std_100
    {167,IR(33, 3),IR(55697, 8),IR(1, 0)}, // s_mad24 in opencl_std_100
    {168,IR(33, 3),IR(55705, 8),IR(1, 0)}, // u_mad24 in opencl_std_100
    {169,IR(36, 2),IR(55713, 8),IR(1, 0)}, // s_mul24 in opencl_std_100
    {170,IR(36, 2),IR(55721, 8),IR(1, 0)}, // u_mul24 in opencl_std_100
    {171,IR(1142, 3),IR(55729, 7),IR(1, 0)}, // vloadn in opencl_std_100
    {172,IR(33, 3),IR(55736, 8),IR(1, 0)}, // vstoren in opencl_std_100
    {173,IR(36, 2),IR(55744, 11),IR(1, 0)}, // vload_half in opencl_std_100
    {174,IR(1142, 3),IR(55755, 12),IR(1, 0)}, // vload_halfn in opencl_std_100
    {175,IR(33, 3),IR(55767, 12),IR(1, 0)}, // vstore_half in opencl_std_100
    {176,IR(1145, 4),IR(55779, 14),IR(1, 0)}, // vstore_half_r in opencl_std_100
    {177,IR(33, 3),IR(55793, 13),IR(1, 0)}, // vstore_halfn in opencl_std_100
    {178,IR(1145, 4),IR(55806, 15),IR(1, 0)}, // vstore_halfn_r in opencl_std_100
    {179,IR(1142, 3),IR(55821, 13),IR(1, 0)}, // vloada_halfn in opencl_std_100
    {180,IR(33, 3),IR(55834, 14),IR(1, 0)}, // vstorea_halfn in opencl_std_100
    {181,IR(1145, 4),IR(55848, 16),IR(1, 0)}, // vstorea_halfn_r in opencl_std_100
    {182,IR(36, 2),IR(55864, 8),IR(1, 0)}, // shuffle in opencl_std_100
    {183,IR(33, 3),IR(55872, 9),IR(1, 0)}, // shuffle2 in opencl_std_100
    {184,IR(168, 2),IR(55881, 7),IR(1, 0)}, // printf in opencl_std_100
    {185,IR(36, 2),IR(55888, 9),IR(1, 0)}, // prefetch in opencl_std_100
    {186,IR(33, 3),IR(55897, 10),IR(1, 0)}, // bitselect in opencl_std_100
    {187,IR(33, 3),IR(55907, 7),IR(1, 0)}, // select in opencl_std_100
    {201,IR(10, 1),IR(55914, 6),IR(1, 0)}, // u_abs in opencl_std_100
    {202,IR(36, 2),IR(55920, 11),IR(1, 0)}, // u_abs_diff in opencl_std_100
    {203,IR(36, 2),IR(55931, 9),IR(1, 0)}, // u_mul_hi in opencl_std_100
    {204,IR(33, 3),IR(55940, 9),IR(1, 0)}, // u_mad_hi in opencl_std_100
    {1,IR(10, 1),IR(55949, 17),IR(1, 0)}, // CubeFaceIndexAMD in spv_amd_gcn_shader
    {2,IR(10, 1),IR(55966, 17),IR(1, 0)}, // CubeFaceCoordAMD in spv_amd_gcn_shader
    {3,IR(0, 0),IR(55983, 8),IR(1, 0)}, // TimeAMD in spv_amd_gcn_shader
    {1,IR(36, 2),IR(55991, 22),IR(1, 0)}, // SwizzleInvocationsAMD in spv_amd_shader_ballot
    {2,IR(36, 2),IR(56013, 28),IR(1, 0)}, // SwizzleInvocationsMaskedAMD in spv_amd_shader_ballot
    {3,IR(33, 3),IR(56041, 19),IR(1, 0)}, // WriteInvocationAMD in spv_amd_shader_ballot
    {4,IR(10, 1),IR(56060, 9),IR(1, 0)}, // MbcntAMD in spv_amd_shader_ballot
    {1,IR(36, 2),IR(56069, 23),IR(1, 0)}, // InterpolateAtVertexAMD in spv_amd_shader_explicit_vertex_parameter
    {1,IR(33, 3),IR(56092, 9),IR(1, 0)}, // FMin3AMD in spv_amd_shader_trinary_minmax
    {2,IR(33, 3),IR(56101, 9),IR(1, 0)}, // UMin3AMD in spv_amd_shader_trinary_minmax
    {3,IR(33, 3),IR(56110, 9),IR(1, 0)}, // SMin3AMD in spv_amd_shader_trinary_minmax
    {4,IR(33, 3),IR(56119, 9),IR(1, 0)}, // FMax3AMD in spv_amd_shader_trinary_minmax
    {5,IR(33, 3),IR(56128, 9),IR(1, 0)}, // UMax3AMD in spv_amd_shader_trinary_minmax
    {6,IR(33, 3),IR(56137, 9),IR(1, 0)}, // SMax3AMD in spv_amd_shader_trinary_minmax
    {7,IR(33, 3),IR(56146, 9),IR(1, 0)}, // FMid3AMD in spv_amd_shader_trinary_minmax
    {8,IR(33, 3),IR(56155, 9),IR(1, 0)}, // UMid3AMD in spv_amd_shader_trinary_minmax
    {9,IR(33, 3),IR(56164, 9),IR(1, 0)}, // SMid3AMD in spv_amd_shader_trinary_minmax
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
    {IR(51440, 21), 1}, // DebugCompilationUnit in debuginfo
    {IR(52167, 13), 28}, // DebugDeclare in debuginfo
    {IR(52239, 16), 31}, // DebugExpression in debuginfo
    {IR(51983, 14), 20}, // DebugFunction in debuginfo
    {IR(51958, 25), 19}, // DebugFunctionDeclaration in debuginfo
    {IR(51938, 20), 18}, // DebugGlobalVariable in debuginfo
    {IR(51426, 14), 0}, // DebugInfoNone in debuginfo
    {IR(52070, 15), 25}, // DebugInlinedAt in debuginfo
    {IR(52146, 21), 27}, // DebugInlinedVariable in debuginfo
    {IR(51997, 18), 21}, // DebugLexicalBlock in debuginfo
    {IR(52015, 31), 22}, // DebugLexicalBlockDiscriminator in debuginfo
    {IR(52127, 19), 26}, // DebugLocalVariable in debuginfo
    {IR(52255, 14), 32}, // DebugMacroDef in debuginfo
    {IR(52269, 16), 33}, // DebugMacroUndef in debuginfo
    {IR(52057, 13), 24}, // DebugNoScope in debuginfo
    {IR(52224, 15), 30}, // DebugOperation in debuginfo
    {IR(52046, 11), 23}, // DebugScope in debuginfo
    {IR(51636, 15), 5}, // DebugTypeArray in debuginfo
    {IR(51513, 15), 2}, // DebugTypeBasic in debuginfo
    {IR(51750, 19), 10}, // DebugTypeComposite in debuginfo
    {IR(51698, 14), 9}, // DebugTypeEnum in debuginfo
    {IR(51680, 18), 8}, // DebugTypeFunction in debuginfo
    {IR(51785, 21), 12}, // DebugTypeInheritance in debuginfo
    {IR(51769, 16), 11}, // DebugTypeMember in debuginfo
    {IR(51562, 17), 3}, // DebugTypePointer in debuginfo
    {IR(51806, 21), 13}, // DebugTypePtrToMember in debuginfo
    {IR(51617, 19), 4}, // DebugTypeQualifier in debuginfo
    {IR(51827, 18), 14}, // DebugTypeTemplate in debuginfo
    {IR(51845, 27), 15}, // DebugTypeTemplateParameter in debuginfo
    {IR(51907, 31), 17}, // DebugTypeTemplateParameterPack in debuginfo
    {IR(51872, 35), 16}, // DebugTypeTemplateTemplateParameter in debuginfo
    {IR(51651, 16), 6}, // DebugTypeVector in debuginfo
    {IR(51667, 13), 7}, // DebugTypedef in debuginfo
    {IR(52180, 11), 29}, // DebugValue in debuginfo
    {IR(52379, 5), 50}, // Acos in glsl_std_450
    {IR(52410, 6), 56}, // Acosh in glsl_std_450
    {IR(52374, 5), 49}, // Asin in glsl_std_450
    {IR(52404, 6), 55}, // Asinh in glsl_std_450
    {IR(52384, 5), 51}, // Atan in glsl_std_450
    {IR(52422, 6), 58}, // Atan2 in glsl_std_450
    {IR(52416, 6), 57}, // Atanh in glsl_std_450
    {IR(52335, 5), 42}, // Ceil in glsl_std_450
    {IR(52366, 4), 47}, // Cos in glsl_std_450
    {IR(52394, 5), 53}, // Cosh in glsl_std_450
    {IR(52806, 6), 101}, // Cross in glsl_std_450
    {IR(52354, 8), 45}, // Degrees in glsl_std_450
    {IR(52467, 12), 66}, // Determinant in glsl_std_450
    {IR(52797, 9), 100}, // Distance in glsl_std_450
    {IR(52432, 4), 60}, // Exp in glsl_std_450
    {IR(52440, 5), 62}, // Exp2 in glsl_std_450
    {IR(52307, 5), 37}, // FAbs in glsl_std_450
    {IR(52539, 7), 76}, // FClamp in glsl_std_450
    {IR(52524, 5), 73}, // FMax in glsl_std_450
    {IR(52509, 5), 70}, // FMin in glsl_std_450
    {IR(52560, 5), 79}, // FMix in glsl_std_450
    {IR(52317, 6), 39}, // FSign in glsl_std_450
    {IR(52822, 12), 103}, // FaceForward in glsl_std_450
    {IR(52850, 9), 106}, // FindILsb in glsl_std_450
    {IR(52859, 9), 107}, // FindSMsb in glsl_std_450
    {IR(52868, 9), 108}, // FindUMsb in glsl_std_450
    {IR(52329, 6), 41}, // Floor in glsl_std_450
    {IR(52586, 4), 83}, // Fma in glsl_std_450
    {IR(52340, 6), 43}, // Fract in glsl_std_450
    {IR(52590, 6), 84}, // Frexp in glsl_std_450
    {IR(52596, 12), 85}, // FrexpStruct in glsl_std_450
    {IR(52565, 5), 80}, // IMix in glsl_std_450
    {IR(52877, 22), 109}, // InterpolateAtCentroid in glsl_std_450
    {IR(52919, 20), 111}, // InterpolateAtOffset in glsl_std_450
    {IR(52899, 20), 110}, // InterpolateAtSample in glsl_std_450
    {IR(52455, 12), 65}, // InverseSqrt in glsl_std_450
    {IR(52608, 6), 86}, // Ldexp in glsl_std_450
    {IR(52790, 7), 99}, // Length in glsl_std_450
    {IR(52436, 4), 61}, // Log in glsl_std_450
    {IR(52445, 5), 63}, // Log2 in glsl_std_450
    {IR(52479, 14), 67}, // MatrixInverse in glsl_std_450
    {IR(52493, 5), 68}, // Modf in glsl_std_450
    {IR(52498, 11), 69}, // ModfStruct in glsl_std_450
    {IR(52949, 7), 114}, // NClamp in glsl_std_450
    {IR(52944, 5), 113}, // NMax in glsl_std_450
    {IR(52939, 5), 112}, // NMin in glsl_std_450
    {IR(52812, 10), 102}, // Normalize in glsl_std_450
    {IR(52681, 15), 92}, // PackDouble2x32 in glsl_std_450
    {IR(52668, 13), 91}, // PackHalf2x16 in glsl_std_450
    {IR(52640, 14), 89}, // PackSnorm2x16 in glsl_std_450
    {IR(52614, 13), 87}, // PackSnorm4x8 in glsl_std_450
    {IR(52654, 14), 90}, // PackUnorm2x16 in glsl_std_450
    {IR(52627, 13), 88}, // PackUnorm4x8 in glsl_std_450
    {IR(52428, 4), 59}, // Pow in glsl_std_450
    {IR(52346, 8), 44}, // Radians in glsl_std_450
    {IR(52834, 8), 104}, // Reflect in glsl_std_450
    {IR(52842, 8), 105}, // Refract in glsl_std_450
    {IR(52285, 6), 34}, // Round in glsl_std_450
    {IR(52291, 10), 35}, // RoundEven in glsl_std_450
    {IR(52312, 5), 38}, // SAbs in glsl_std_450
    {IR(52553, 7), 78}, // SClamp in glsl_std_450
    {IR(52534, 5), 75}, // SMax in glsl_std_450
    {IR(52519, 5), 72}, // SMin in glsl_std_450
    {IR(52323, 6), 40}, // SSign in glsl_std_450
    {IR(52362, 4), 46}, // Sin in glsl_std_450
    {IR(52389, 5), 52}, // Sinh in glsl_std_450
    {IR(52575, 11), 82}, // SmoothStep in glsl_std_450
    {IR(52450, 5), 64}, // Sqrt in glsl_std_450
    {IR(52570, 5), 81}, // Step in glsl_std_450
    {IR(52370, 4), 48}, // Tan in glsl_std_450
    {IR(52399, 5), 54}, // Tanh in glsl_std_450
    {IR(52301, 6), 36}, // Trunc in glsl_std_450
    {IR(52546, 7), 77}, // UClamp in glsl_std_450
    {IR(52529, 5), 74}, // UMax in glsl_std_450
    {IR(52514, 5), 71}, // UMin in glsl_std_450
    {IR(52773, 17), 98}, // UnpackDouble2x32 in glsl_std_450
    {IR(52728, 15), 95}, // UnpackHalf2x16 in glsl_std_450
    {IR(52696, 16), 93}, // UnpackSnorm2x16 in glsl_std_450
    {IR(52743, 15), 96}, // UnpackSnorm4x8 in glsl_std_450
    {IR(52712, 16), 94}, // UnpackUnorm2x16 in glsl_std_450
    {IR(52758, 15), 97}, // UnpackUnorm4x8 in glsl_std_450
    {IR(52956, 13), 116}, // ArgumentInfo in nonsemantic_clspvreflection
    {IR(53051, 24), 121}, // ArgumentPodPushConstant in nonsemantic_clspvreflection
    {IR(53007, 25), 119}, // ArgumentPodStorageBuffer in nonsemantic_clspvreflection
    {IR(53032, 19), 120}, // ArgumentPodUniform in nonsemantic_clspvreflection
    {IR(53485, 28), 140}, // ArgumentPointerPushConstant in nonsemantic_clspvreflection
    {IR(53513, 23), 141}, // ArgumentPointerUniform in nonsemantic_clspvreflection
    {IR(53075, 21), 122}, // ArgumentSampledImage in nonsemantic_clspvreflection
    {IR(53117, 16), 124}, // ArgumentSampler in nonsemantic_clspvreflection
    {IR(52969, 22), 117}, // ArgumentStorageBuffer in nonsemantic_clspvreflection
    {IR(53096, 21), 123}, // ArgumentStorageImage in nonsemantic_clspvreflection
    {IR(53773, 27), 148}, // ArgumentStorageTexelBuffer in nonsemantic_clspvreflection
    {IR(52991, 16), 118}, // ArgumentUniform in nonsemantic_clspvreflection
    {IR(53800, 27), 149}, // ArgumentUniformTexelBuffer in nonsemantic_clspvreflection
    {IR(53133, 18), 125}, // ArgumentWorkgroup in nonsemantic_clspvreflection
    {IR(53827, 32), 150}, // ConstantDataPointerPushConstant in nonsemantic_clspvreflection
    {IR(53381, 26), 135}, // ConstantDataStorageBuffer in nonsemantic_clspvreflection
    {IR(53407, 20), 136}, // ConstantDataUniform in nonsemantic_clspvreflection
    {IR(53651, 45), 145}, // ImageArgumentInfoChannelDataTypePushConstant in nonsemantic_clspvreflection
    {IR(53733, 40), 147}, // ImageArgumentInfoChannelDataTypeUniform in nonsemantic_clspvreflection
    {IR(53609, 42), 144}, // ImageArgumentInfoChannelOrderPushConstant in nonsemantic_clspvreflection
    {IR(53696, 37), 146}, // ImageArgumentInfoChannelOrderUniform in nonsemantic_clspvreflection
    {IR(5717, 7), 115}, // Kernel in nonsemantic_clspvreflection
    {IR(9191, 15), 137}, // LiteralSampler in nonsemantic_clspvreflection
    {IR(53968, 34), 155}, // NormalizedSamplerMaskPushConstant in nonsemantic_clspvreflection
    {IR(53936, 32), 154}, // PrintfBufferPointerPushConstant in nonsemantic_clspvreflection
    {IR(53910, 26), 153}, // PrintfBufferStorageBuffer in nonsemantic_clspvreflection
    {IR(53899, 11), 152}, // PrintfInfo in nonsemantic_clspvreflection
    {IR(53859, 40), 151}, // ProgramScopeVariablePointerPushConstant in nonsemantic_clspvreflection
    {IR(53571, 38), 143}, // ProgramScopeVariablePointerRelocation in nonsemantic_clspvreflection
    {IR(53536, 35), 142}, // ProgramScopeVariablesStorageBuffer in nonsemantic_clspvreflection
    {IR(53427, 30), 138}, // PropertyRequiredWorkgroupSize in nonsemantic_clspvreflection
    {IR(53247, 30), 130}, // PushConstantEnqueuedLocalSize in nonsemantic_clspvreflection
    {IR(53222, 25), 129}, // PushConstantGlobalOffset in nonsemantic_clspvreflection
    {IR(53277, 23), 131}, // PushConstantGlobalSize in nonsemantic_clspvreflection
    {IR(53325, 26), 133}, // PushConstantNumWorkgroups in nonsemantic_clspvreflection
    {IR(53351, 30), 134}, // PushConstantRegionGroupOffset in nonsemantic_clspvreflection
    {IR(53300, 25), 132}, // PushConstantRegionOffset in nonsemantic_clspvreflection
    {IR(53177, 25), 127}, // SpecConstantGlobalOffset in nonsemantic_clspvreflection
    {IR(53457, 28), 139}, // SpecConstantSubgroupMaxSize in nonsemantic_clspvreflection
    {IR(53202, 20), 128}, // SpecConstantWorkDim in nonsemantic_clspvreflection
    {IR(53151, 26), 126}, // SpecConstantWorkgroupSize in nonsemantic_clspvreflection
    {IR(54002, 22), 156}, // WorkgroupVariableSize in nonsemantic_clspvreflection
    {IR(54123, 21), 197}, // DebugBuildIdentifier in nonsemantic_shader_debuginfo_100
    {IR(51440, 21), 158}, // DebugCompilationUnit in nonsemantic_shader_debuginfo_100
    {IR(52167, 13), 185}, // DebugDeclare in nonsemantic_shader_debuginfo_100
    {IR(54161, 16), 199}, // DebugEntryPoint in nonsemantic_shader_debuginfo_100
    {IR(52239, 16), 188}, // DebugExpression in nonsemantic_shader_debuginfo_100
    {IR(51983, 14), 177}, // DebugFunction in nonsemantic_shader_debuginfo_100
    {IR(51958, 25), 176}, // DebugFunctionDeclaration in nonsemantic_shader_debuginfo_100
    {IR(54056, 24), 193}, // DebugFunctionDefinition in nonsemantic_shader_debuginfo_100
    {IR(51938, 20), 175}, // DebugGlobalVariable in nonsemantic_shader_debuginfo_100
    {IR(54024, 20), 191}, // DebugImportedEntity in nonsemantic_shader_debuginfo_100
    {IR(51426, 14), 157}, // DebugInfoNone in nonsemantic_shader_debuginfo_100
    {IR(52070, 15), 182}, // DebugInlinedAt in nonsemantic_shader_debuginfo_100
    {IR(52146, 21), 184}, // DebugInlinedVariable in nonsemantic_shader_debuginfo_100
    {IR(51997, 18), 178}, // DebugLexicalBlock in nonsemantic_shader_debuginfo_100
    {IR(52015, 31), 179}, // DebugLexicalBlockDiscriminator in nonsemantic_shader_debuginfo_100
    {IR(54101, 10), 195}, // DebugLine in nonsemantic_shader_debuginfo_100
    {IR(52127, 19), 183}, // DebugLocalVariable in nonsemantic_shader_debuginfo_100
    {IR(52255, 14), 189}, // DebugMacroDef in nonsemantic_shader_debuginfo_100
    {IR(52269, 16), 190}, // DebugMacroUndef in nonsemantic_shader_debuginfo_100
    {IR(54111, 12), 196}, // DebugNoLine in nonsemantic_shader_debuginfo_100
    {IR(52057, 13), 181}, // DebugNoScope in nonsemantic_shader_debuginfo_100
    {IR(52224, 15), 187}, // DebugOperation in nonsemantic_shader_debuginfo_100
    {IR(52046, 11), 180}, // DebugScope in nonsemantic_shader_debuginfo_100
    {IR(54044, 12), 192}, // DebugSource in nonsemantic_shader_debuginfo_100
    {IR(54080, 21), 194}, // DebugSourceContinued in nonsemantic_shader_debuginfo_100
    {IR(54144, 17), 198}, // DebugStoragePath in nonsemantic_shader_debuginfo_100
    {IR(51636, 15), 162}, // DebugTypeArray in nonsemantic_shader_debuginfo_100
    {IR(51513, 15), 159}, // DebugTypeBasic in nonsemantic_shader_debuginfo_100
    {IR(51750, 19), 167}, // DebugTypeComposite in nonsemantic_shader_debuginfo_100
    {IR(51698, 14), 166}, // DebugTypeEnum in nonsemantic_shader_debuginfo_100
    {IR(51680, 18), 165}, // DebugTypeFunction in nonsemantic_shader_debuginfo_100
    {IR(51785, 21), 169}, // DebugTypeInheritance in nonsemantic_shader_debuginfo_100
    {IR(54177, 16), 200}, // DebugTypeMatrix in nonsemantic_shader_debuginfo_100
    {IR(51769, 16), 168}, // DebugTypeMember in nonsemantic_shader_debuginfo_100
    {IR(51562, 17), 160}, // DebugTypePointer in nonsemantic_shader_debuginfo_100
    {IR(51806, 21), 170}, // DebugTypePtrToMember in nonsemantic_shader_debuginfo_100
    {IR(51617, 19), 161}, // DebugTypeQualifier in nonsemantic_shader_debuginfo_100
    {IR(51827, 18), 171}, // DebugTypeTemplate in nonsemantic_shader_debuginfo_100
    {IR(51845, 27), 172}, // DebugTypeTemplateParameter in nonsemantic_shader_debuginfo_100
    {IR(51907, 31), 174}, // DebugTypeTemplateParameterPack in nonsemantic_shader_debuginfo_100
    {IR(51872, 35), 173}, // DebugTypeTemplateTemplateParameter in nonsemantic_shader_debuginfo_100
    {IR(51651, 16), 163}, // DebugTypeVector in nonsemantic_shader_debuginfo_100
    {IR(51667, 13), 164}, // DebugTypedef in nonsemantic_shader_debuginfo_100
    {IR(52180, 11), 186}, // DebugValue in nonsemantic_shader_debuginfo_100
    {IR(54193, 14), 201}, // Configuration in nonsemantic_vkspreflection
    {IR(54269, 20), 206}, // DescriptorSetBuffer in nonsemantic_vkspreflection
    {IR(54289, 19), 207}, // DescriptorSetImage in nonsemantic_vkspreflection
    {IR(54308, 21), 208}, // DescriptorSetSampler in nonsemantic_vkspreflection
    {IR(54232, 14), 204}, // PushConstants in nonsemantic_vkspreflection
    {IR(54246, 23), 205}, // SpecializationMapEntry in nonsemantic_vkspreflection
    {IR(54207, 13), 202}, // StartCounter in nonsemantic_vkspreflection
    {IR(54220, 12), 203}, // StopCounter in nonsemantic_vkspreflection
    {IR(51440, 21), 210}, // DebugCompilationUnit in opencl_debuginfo_100
    {IR(52167, 13), 237}, // DebugDeclare in opencl_debuginfo_100
    {IR(52239, 16), 240}, // DebugExpression in opencl_debuginfo_100
    {IR(51983, 14), 229}, // DebugFunction in opencl_debuginfo_100
    {IR(51958, 25), 228}, // DebugFunctionDeclaration in opencl_debuginfo_100
    {IR(51938, 20), 227}, // DebugGlobalVariable in opencl_debuginfo_100
    {IR(54024, 20), 243}, // DebugImportedEntity in opencl_debuginfo_100
    {IR(51426, 14), 209}, // DebugInfoNone in opencl_debuginfo_100
    {IR(52070, 15), 234}, // DebugInlinedAt in opencl_debuginfo_100
    {IR(52146, 21), 236}, // DebugInlinedVariable in opencl_debuginfo_100
    {IR(51997, 18), 230}, // DebugLexicalBlock in opencl_debuginfo_100
    {IR(52015, 31), 231}, // DebugLexicalBlockDiscriminator in opencl_debuginfo_100
    {IR(52127, 19), 235}, // DebugLocalVariable in opencl_debuginfo_100
    {IR(52255, 14), 241}, // DebugMacroDef in opencl_debuginfo_100
    {IR(52269, 16), 242}, // DebugMacroUndef in opencl_debuginfo_100
    {IR(54629, 17), 245}, // DebugModuleINTEL in opencl_debuginfo_100
    {IR(52057, 13), 233}, // DebugNoScope in opencl_debuginfo_100
    {IR(52224, 15), 239}, // DebugOperation in opencl_debuginfo_100
    {IR(52046, 11), 232}, // DebugScope in opencl_debuginfo_100
    {IR(54044, 12), 244}, // DebugSource in opencl_debuginfo_100
    {IR(51636, 15), 214}, // DebugTypeArray in opencl_debuginfo_100
    {IR(51513, 15), 211}, // DebugTypeBasic in opencl_debuginfo_100
    {IR(51750, 19), 219}, // DebugTypeComposite in opencl_debuginfo_100
    {IR(51698, 14), 218}, // DebugTypeEnum in opencl_debuginfo_100
    {IR(51680, 18), 217}, // DebugTypeFunction in opencl_debuginfo_100
    {IR(51785, 21), 221}, // DebugTypeInheritance in opencl_debuginfo_100
    {IR(51769, 16), 220}, // DebugTypeMember in opencl_debuginfo_100
    {IR(51562, 17), 212}, // DebugTypePointer in opencl_debuginfo_100
    {IR(51806, 21), 222}, // DebugTypePtrToMember in opencl_debuginfo_100
    {IR(51617, 19), 213}, // DebugTypeQualifier in opencl_debuginfo_100
    {IR(51827, 18), 223}, // DebugTypeTemplate in opencl_debuginfo_100
    {IR(51845, 27), 224}, // DebugTypeTemplateParameter in opencl_debuginfo_100
    {IR(51907, 31), 226}, // DebugTypeTemplateParameterPack in opencl_debuginfo_100
    {IR(51872, 35), 225}, // DebugTypeTemplateTemplateParameter in opencl_debuginfo_100
    {IR(51651, 16), 215}, // DebugTypeVector in opencl_debuginfo_100
    {IR(51667, 13), 216}, // DebugTypedef in opencl_debuginfo_100
    {IR(52180, 11), 238}, // DebugValue in opencl_debuginfo_100
    {IR(54646, 5), 246}, // acos in opencl_std_100
    {IR(54651, 6), 247}, // acosh in opencl_std_100
    {IR(54657, 7), 248}, // acospi in opencl_std_100
    {IR(54664, 5), 249}, // asin in opencl_std_100
    {IR(54669, 6), 250}, // asinh in opencl_std_100
    {IR(54675, 7), 251}, // asinpi in opencl_std_100
    {IR(54682, 5), 252}, // atan in opencl_std_100
    {IR(54687, 6), 253}, // atan2 in opencl_std_100
    {IR(54706, 8), 256}, // atan2pi in opencl_std_100
    {IR(54693, 6), 254}, // atanh in opencl_std_100
    {IR(54699, 7), 255}, // atanpi in opencl_std_100
    {IR(55897, 10), 402}, // bitselect in opencl_std_100
    {IR(54714, 5), 257}, // cbrt in opencl_std_100
    {IR(54719, 5), 258}, // ceil in opencl_std_100
    {IR(55569, 4), 367}, // clz in opencl_std_100
    {IR(54724, 9), 259}, // copysign in opencl_std_100
    {IR(54733, 4), 260}, // cos in opencl_std_100
    {IR(54737, 5), 261}, // cosh in opencl_std_100
    {IR(54742, 6), 262}, // cospi in opencl_std_100
    {IR(55413, 6), 350}, // cross in opencl_std_100
    {IR(55573, 4), 368}, // ctz in opencl_std_100
    {IR(55348, 8), 342}, // degrees in opencl_std_100
    {IR(55419, 9), 351}, // distance in opencl_std_100
    {IR(54753, 4), 264}, // erf in opencl_std_100
    {IR(54748, 5), 263}, // erfc in opencl_std_100
    {IR(54757, 4), 265}, // exp in opencl_std_100
    {IR(54766, 6), 267}, // exp10 in opencl_std_100
    {IR(54761, 5), 266}, // exp2 in opencl_std_100
    {IR(54772, 6), 268}, // expm1 in opencl_std_100
    {IR(54778, 5), 269}, // fabs in opencl_std_100
    {IR(55445, 14), 354}, // fast_distance in opencl_std_100
    {IR(55459, 12), 355}, // fast_length in opencl_std_100
    {IR(55471, 15), 356}, // fast_normalize in opencl_std_100
    {IR(55341, 7), 341}, // fclamp in opencl_std_100
    {IR(54783, 5), 270}, // fdim in opencl_std_100
    {IR(54788, 6), 271}, // floor in opencl_std_100
    {IR(54794, 4), 272}, // fma in opencl_std_100
    {IR(54798, 5), 273}, // fmax in opencl_std_100
    {IR(55356, 12), 343}, // fmax_common in opencl_std_100
    {IR(54803, 5), 274}, // fmin in opencl_std_100
    {IR(55368, 12), 344}, // fmin_common in opencl_std_100
    {IR(54808, 5), 275}, // fmod in opencl_std_100
    {IR(54813, 6), 276}, // fract in opencl_std_100
    {IR(54819, 6), 277}, // frexp in opencl_std_100
    {IR(55031, 9), 313}, // half_cos in opencl_std_100
    {IR(55040, 12), 314}, // half_divide in opencl_std_100
    {IR(55052, 9), 315}, // half_exp in opencl_std_100
    {IR(55071, 11), 317}, // half_exp10 in opencl_std_100
    {IR(55061, 10), 316}, // half_exp2 in opencl_std_100
    {IR(55082, 9), 318}, // half_log in opencl_std_100
    {IR(55101, 11), 320}, // half_log10 in opencl_std_100
    {IR(55091, 10), 319}, // half_log2 in opencl_std_100
    {IR(55112, 10), 321}, // half_powr in opencl_std_100
    {IR(55122, 11), 322}, // half_recip in opencl_std_100
    {IR(55133, 11), 323}, // half_rsqrt in opencl_std_100
    {IR(55144, 9), 324}, // half_sin in opencl_std_100
    {IR(55153, 10), 325}, // half_sqrt in opencl_std_100
    {IR(55163, 9), 326}, // half_tan in opencl_std_100
    {IR(54825, 6), 278}, // hypot in opencl_std_100
    {IR(54831, 6), 279}, // ilogb in opencl_std_100
    {IR(54837, 6), 280}, // ldexp in opencl_std_100
    {IR(55428, 7), 352}, // length in opencl_std_100
    {IR(54843, 7), 281}, // lgamma in opencl_std_100
    {IR(54850, 9), 282}, // lgamma_r in opencl_std_100
    {IR(54859, 4), 283}, // log in opencl_std_100
    {IR(54868, 6), 285}, // log10 in opencl_std_100
    {IR(54874, 6), 286}, // log1p in opencl_std_100
    {IR(54863, 5), 284}, // log2 in opencl_std_100
    {IR(54880, 5), 287}, // logb in opencl_std_100
    {IR(54885, 4), 288}, // mad in opencl_std_100
    {IR(54889, 7), 289}, // maxmag in opencl_std_100
    {IR(54896, 7), 290}, // minmag in opencl_std_100
    {IR(55380, 4), 345}, // mix in opencl_std_100
    {IR(54903, 5), 291}, // modf in opencl_std_100
    {IR(54908, 4), 292}, // nan in opencl_std_100
    {IR(55172, 11), 327}, // native_cos in opencl_std_100
    {IR(55183, 14), 328}, // native_divide in opencl_std_100
    {IR(55197, 11), 329}, // native_exp in opencl_std_100
    {IR(55220, 13), 331}, // native_exp10 in opencl_std_100
    {IR(55208, 12), 330}, // native_exp2 in opencl_std_100
    {IR(55233, 11), 332}, // native_log in opencl_std_100
    {IR(55256, 13), 334}, // native_log10 in opencl_std_100
    {IR(55244, 12), 333}, // native_log2 in opencl_std_100
    {IR(55269, 12), 335}, // native_powr in opencl_std_100
    {IR(55281, 13), 336}, // native_recip in opencl_std_100
    {IR(55294, 13), 337}, // native_rsqrt in opencl_std_100
    {IR(55307, 11), 338}, // native_sin in opencl_std_100
    {IR(55318, 12), 339}, // native_sqrt in opencl_std_100
    {IR(55330, 11), 340}, // native_tan in opencl_std_100
    {IR(54912, 10), 293}, // nextafter in opencl_std_100
    {IR(55435, 10), 353}, // normalize in opencl_std_100
    {IR(55688, 9), 382}, // popcount in opencl_std_100
    {IR(54922, 4), 294}, // pow in opencl_std_100
    {IR(54926, 5), 295}, // pown in opencl_std_100
    {IR(54931, 5), 296}, // powr in opencl_std_100
    {IR(55888, 9), 401}, // prefetch in opencl_std_100
    {IR(55881, 7), 400}, // printf in opencl_std_100
    {IR(55384, 8), 346}, // radians in opencl_std_100
    {IR(54936, 10), 297}, // remainder in opencl_std_100
    {IR(54946, 7), 298}, // remquo in opencl_std_100
    {IR(54953, 5), 299}, // rint in opencl_std_100
    {IR(54958, 6), 300}, // rootn in opencl_std_100
    {IR(55639, 7), 377}, // rotate in opencl_std_100
    {IR(54964, 6), 301}, // round in opencl_std_100
    {IR(54970, 6), 302}, // rsqrt in opencl_std_100
    {IR(55486, 6), 357}, // s_abs in opencl_std_100
    {IR(55492, 11), 358}, // s_abs_diff in opencl_std_100
    {IR(55503, 10), 359}, // s_add_sat in opencl_std_100
    {IR(55553, 8), 365}, // s_clamp in opencl_std_100
    {IR(55523, 7), 361}, // s_hadd in opencl_std_100
    {IR(55697, 8), 383}, // s_mad24 in opencl_std_100
    {IR(55577, 9), 369}, // s_mad_hi in opencl_std_100
    {IR(55596, 10), 371}, // s_mad_sat in opencl_std_100
    {IR(55606, 6), 372}, // s_max in opencl_std_100
    {IR(55618, 6), 374}, // s_min in opencl_std_100
    {IR(55713, 8), 385}, // s_mul24 in opencl_std_100
    {IR(55630, 9), 376}, // s_mul_hi in opencl_std_100
    {IR(55537, 8), 363}, // s_rhadd in opencl_std_100
    {IR(55646, 10), 378}, // s_sub_sat in opencl_std_100
    {IR(55677, 11), 381}, // s_upsample in opencl_std_100
    {IR(55907, 7), 403}, // select in opencl_std_100
    {IR(55864, 8), 398}, // shuffle in opencl_std_100
    {IR(55872, 9), 399}, // shuffle2 in opencl_std_100
    {IR(55408, 5), 349}, // sign in opencl_std_100
    {IR(54976, 4), 303}, // sin in opencl_std_100
    {IR(54980, 7), 304}, // sincos in opencl_std_100
    {IR(54987, 5), 305}, // sinh in opencl_std_100
    {IR(54992, 6), 306}, // sinpi in opencl_std_100
    {IR(55397, 11), 348}, // smoothstep in opencl_std_100
    {IR(54998, 5), 307}, // sqrt in opencl_std_100
    {IR(55392, 5), 347}, // step in opencl_std_100
    {IR(55003, 4), 308}, // tan in opencl_std_100
    {IR(55007, 5), 309}, // tanh in opencl_std_100
    {IR(55012, 6), 310}, // tanpi in opencl_std_100
    {IR(55018, 7), 311}, // tgamma in opencl_std_100
    {IR(55025, 6), 312}, // trunc in opencl_std_100
    {IR(55914, 6), 404}, // u_abs in opencl_std_100
    {IR(55920, 11), 405}, // u_abs_diff in opencl_std_100
    {IR(55513, 10), 360}, // u_add_sat in opencl_std_100
    {IR(55561, 8), 366}, // u_clamp in opencl_std_100
    {IR(55530, 7), 362}, // u_hadd in opencl_std_100
    {IR(55705, 8), 384}, // u_mad24 in opencl_std_100
    {IR(55940, 9), 407}, // u_mad_hi in opencl_std_100
    {IR(55586, 10), 370}, // u_mad_sat in opencl_std_100
    {IR(55612, 6), 373}, // u_max in opencl_std_100
    {IR(55624, 6), 375}, // u_min in opencl_std_100
    {IR(55721, 8), 386}, // u_mul24 in opencl_std_100
    {IR(55931, 9), 406}, // u_mul_hi in opencl_std_100
    {IR(55545, 8), 364}, // u_rhadd in opencl_std_100
    {IR(55656, 10), 379}, // u_sub_sat in opencl_std_100
    {IR(55666, 11), 380}, // u_upsample in opencl_std_100
    {IR(55744, 11), 389}, // vload_half in opencl_std_100
    {IR(55755, 12), 390}, // vload_halfn in opencl_std_100
    {IR(55821, 13), 395}, // vloada_halfn in opencl_std_100
    {IR(55729, 7), 387}, // vloadn in opencl_std_100
    {IR(55767, 12), 391}, // vstore_half in opencl_std_100
    {IR(55779, 14), 392}, // vstore_half_r in opencl_std_100
    {IR(55793, 13), 393}, // vstore_halfn in opencl_std_100
    {IR(55806, 15), 394}, // vstore_halfn_r in opencl_std_100
    {IR(55834, 14), 396}, // vstorea_halfn in opencl_std_100
    {IR(55848, 16), 397}, // vstorea_halfn_r in opencl_std_100
    {IR(55736, 8), 388}, // vstoren in opencl_std_100
    {IR(55966, 17), 409}, // CubeFaceCoordAMD in spv_amd_gcn_shader
    {IR(55949, 17), 408}, // CubeFaceIndexAMD in spv_amd_gcn_shader
    {IR(55983, 8), 410}, // TimeAMD in spv_amd_gcn_shader
    {IR(56060, 9), 414}, // MbcntAMD in spv_amd_shader_ballot
    {IR(55991, 22), 411}, // SwizzleInvocationsAMD in spv_amd_shader_ballot
    {IR(56013, 28), 412}, // SwizzleInvocationsMaskedAMD in spv_amd_shader_ballot
    {IR(56041, 19), 413}, // WriteInvocationAMD in spv_amd_shader_ballot
    {IR(56069, 23), 415}, // InterpolateAtVertexAMD in spv_amd_shader_explicit_vertex_parameter
    {IR(56119, 9), 419}, // FMax3AMD in spv_amd_shader_trinary_minmax
    {IR(56146, 9), 422}, // FMid3AMD in spv_amd_shader_trinary_minmax
    {IR(56092, 9), 416}, // FMin3AMD in spv_amd_shader_trinary_minmax
    {IR(56137, 9), 421}, // SMax3AMD in spv_amd_shader_trinary_minmax
    {IR(56164, 9), 424}, // SMid3AMD in spv_amd_shader_trinary_minmax
    {IR(56110, 9), 418}, // SMin3AMD in spv_amd_shader_trinary_minmax
    {IR(56128, 9), 420}, // UMax3AMD in spv_amd_shader_trinary_minmax
    {IR(56155, 9), 423}, // UMid3AMD in spv_amd_shader_trinary_minmax
    {IR(56101, 9), 417}, // UMin3AMD in spv_amd_shader_trinary_minmax
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
  "SPV_EXT_demote_to_helper_invocation\0" // IR(1153, 36)
  "SPV_EXT_descriptor_heap\0" // IR(1189, 24)
  "SPV_EXT_descriptor_indexing\0" // IR(1213, 28)
  "SPV_EXT_float8\0" // IR(1241, 15)
  "SPV_EXT_fragment_fully_covered\0" // IR(1256, 31)
  "SPV_EXT_fragment_invocation_density\0" // IR(1287, 36)
  "SPV_EXT_fragment_shader_interlock\0" // IR(1323, 34)
  "SPV_EXT_long_vector\0" // IR(1357, 20)
  "SPV_EXT_mesh_shader\0" // IR(1377, 20)
  "SPV_EXT_opacity_micromap\0" // IR(1397, 25)
  "SPV_EXT_optnone\0" // IR(1422, 16)
  "SPV_EXT_physical_storage_buffer\0" // IR(1438, 32)
  "SPV_EXT_relaxed_printf_string_address_space\0" // IR(1470, 44)
  "SPV_EXT_replicated_composites\0" // IR(1514, 30)
  "SPV_EXT_shader_64bit_indexing\0" // IR(1544, 30)
  "SPV_EXT_shader_atomic_float16_add\0" // IR(1574, 34)
  "SPV_EXT_shader_atomic_float_add\0" // IR(1608, 32)
  "SPV_EXT_shader_atomic_float_min_max\0" // IR(1640, 36)
  "SPV_EXT_shader_image_int64\0" // IR(1676, 27)
  "SPV_EXT_shader_invocation_reorder\0" // IR(1703, 34)
  "SPV_EXT_shader_stencil_export\0" // IR(1737, 30)
  "SPV_EXT_shader_subgroup_partitioned\0" // IR(1767, 36)
  "SPV_EXT_shader_tile_image\0" // IR(1803, 26)
  "SPV_EXT_shader_viewport_index_layer\0" // IR(1829, 36)
  "SPV_EXT_split_barrier\0" // IR(1865, 22)
  "SPV_GOOGLE_decorate_string\0" // IR(1887, 27)
  "SPV_GOOGLE_hlsl_functionality1\0" // IR(1914, 31)
  "SPV_GOOGLE_user_type\0" // IR(1945, 21)
  "SPV_INTEL_2d_block_io\0" // IR(1966, 22)
  "SPV_INTEL_arbitrary_precision_fixed_point\0" // IR(1988, 42)
  "SPV_INTEL_arbitrary_precision_floating_point\0" // IR(2030, 45)
  "SPV_INTEL_arbitrary_precision_integers\0" // IR(2075, 39)
  "SPV_INTEL_bfloat16_conversion\0" // IR(2114, 30)
  "SPV_INTEL_bindless_images\0" // IR(2144, 26)
  "SPV_INTEL_blocking_pipes\0" // IR(2170, 25)
  "SPV_INTEL_cache_controls\0" // IR(2195, 25)
  "SPV_INTEL_debug_module\0" // IR(2220, 23)
  "SPV_INTEL_device_side_avc_motion_estimation\0" // IR(2243, 44)
  "SPV_INTEL_float_controls2\0" // IR(2287, 26)
  "SPV_INTEL_fp_fast_math_mode\0" // IR(2313, 28)
  "SPV_INTEL_fp_max_error\0" // IR(2341, 23)
  "SPV_INTEL_fpga_argument_interfaces\0" // IR(2364, 35)
  "SPV_INTEL_fpga_buffer_location\0" // IR(2399, 31)
  "SPV_INTEL_fpga_cluster_attributes\0" // IR(2430, 34)
  "SPV_INTEL_fpga_dsp_control\0" // IR(2464, 27)
  "SPV_INTEL_fpga_invocation_pipelining_attributes\0" // IR(2491, 48)
  "SPV_INTEL_fpga_latency_control\0" // IR(2539, 31)
  "SPV_INTEL_fpga_loop_controls\0" // IR(2570, 29)
  "SPV_INTEL_fpga_memory_accesses\0" // IR(2599, 31)
  "SPV_INTEL_fpga_memory_attributes\0" // IR(2630, 33)
  "SPV_INTEL_fpga_reg\0" // IR(2663, 19)
  "SPV_INTEL_function_pointers\0" // IR(2682, 28)
  "SPV_INTEL_function_variants\0" // IR(2710, 28)
  "SPV_INTEL_global_variable_fpga_decorations\0" // IR(2738, 43)
  "SPV_INTEL_global_variable_host_access\0" // IR(2781, 38)
  "SPV_INTEL_inline_assembly\0" // IR(2819, 26)
  "SPV_INTEL_int4\0" // IR(2845, 15)
  "SPV_INTEL_io_pipes\0" // IR(2860, 19)
  "SPV_INTEL_kernel_attributes\0" // IR(2879, 28)
  "SPV_INTEL_long_composites\0" // IR(2907, 26)
  "SPV_INTEL_loop_fuse\0" // IR(2933, 20)
  "SPV_INTEL_masked_gather_scatter\0" // IR(2953, 32)
  "SPV_INTEL_maximum_registers\0" // IR(2985, 28)
  "SPV_INTEL_media_block_io\0" // IR(3013, 25)
  "SPV_INTEL_memory_access_aliasing\0" // IR(3038, 33)
  "SPV_INTEL_optnone\0" // IR(3071, 18)
  "SPV_INTEL_predicated_io\0" // IR(3089, 24)
  "SPV_INTEL_rounded_divide_sqrt\0" // IR(3113, 30)
  "SPV_INTEL_runtime_aligned\0" // IR(3143, 26)
  "SPV_INTEL_shader_integer_functions2\0" // IR(3169, 36)
  "SPV_INTEL_split_barrier\0" // IR(3205, 24)
  "SPV_INTEL_subgroup_buffer_prefetch\0" // IR(3229, 35)
  "SPV_INTEL_subgroup_matrix_multiply_accumulate\0" // IR(3264, 46)
  "SPV_INTEL_subgroups\0" // IR(3310, 20)
  "SPV_INTEL_task_sequence\0" // IR(3330, 24)
  "SPV_INTEL_tensor_float32_conversion\0" // IR(3354, 36)
  "SPV_INTEL_ternary_bitwise_function\0" // IR(3390, 35)
  "SPV_INTEL_unstructured_loop_controls\0" // IR(3425, 37)
  "SPV_INTEL_usm_storage_classes\0" // IR(3462, 30)
  "SPV_INTEL_variable_length_array\0" // IR(3492, 32)
  "SPV_INTEL_vector_compute\0" // IR(3524, 25)
  "SPV_KHR_16bit_storage\0" // IR(3549, 22)
  "SPV_KHR_8bit_storage\0" // IR(3571, 21)
  "SPV_KHR_abort\0" // IR(3592, 14)
  "SPV_KHR_bfloat16\0" // IR(3606, 17)
  "SPV_KHR_bit_instructions\0" // IR(3623, 25)
  "SPV_KHR_compute_shader_derivatives\0" // IR(3648, 35)
  "SPV_KHR_constant_data\0" // IR(3683, 22)
  "SPV_KHR_cooperative_matrix\0" // IR(3705, 27)
  "SPV_KHR_device_group\0" // IR(3732, 21)
  "SPV_KHR_expect_assume\0" // IR(3753, 22)
  "SPV_KHR_float_controls\0" // IR(3775, 23)
  "SPV_KHR_float_controls2\0" // IR(3798, 24)
  "SPV_KHR_fma\0" // IR(3822, 12)
  "SPV_KHR_fragment_shader_barycentric\0" // IR(3834, 36)
  "SPV_KHR_fragment_shading_rate\0" // IR(3870, 30)
  "SPV_KHR_integer_dot_product\0" // IR(3900, 28)
  "SPV_KHR_linkonce_odr\0" // IR(3928, 21)
  "SPV_KHR_maximal_reconvergence\0" // IR(3949, 30)
  "SPV_KHR_multiview\0" // IR(3979, 18)
  "SPV_KHR_no_integer_wrap_decoration\0" // IR(3997, 35)
  "SPV_KHR_non_semantic_info\0" // IR(4032, 26)
  "SPV_KHR_opacity_micromap\0" // IR(4058, 25)
  "SPV_KHR_physical_storage_buffer\0" // IR(4083, 32)
  "SPV_KHR_poison_freeze\0" // IR(4115, 22)
  "SPV_KHR_post_depth_coverage\0" // IR(4137, 28)
  "SPV_KHR_quad_control\0" // IR(4165, 21)
  "SPV_KHR_ray_cull_mask\0" // IR(4186, 22)
  "SPV_KHR_ray_query\0" // IR(4208, 18)
  "SPV_KHR_ray_tracing\0" // IR(4226, 20)
  "SPV_KHR_ray_tracing_position_fetch\0" // IR(4246, 35)
  "SPV_KHR_relaxed_extended_instruction\0" // IR(4281, 37)
  "SPV_KHR_shader_atomic_counter_ops\0" // IR(4318, 34)
  "SPV_KHR_shader_ballot\0" // IR(4352, 22)
  "SPV_KHR_shader_clock\0" // IR(4374, 21)
  "SPV_KHR_shader_draw_parameters\0" // IR(4395, 31)
  "SPV_KHR_storage_buffer_storage_class\0" // IR(4426, 37)
  "SPV_KHR_subgroup_rotate\0" // IR(4463, 24)
  "SPV_KHR_subgroup_uniform_control_flow\0" // IR(4487, 38)
  "SPV_KHR_subgroup_vote\0" // IR(4525, 22)
  "SPV_KHR_terminate_invocation\0" // IR(4547, 29)
  "SPV_KHR_uniform_group_instructions\0" // IR(4576, 35)
  "SPV_KHR_untyped_pointers\0" // IR(4611, 25)
  "SPV_KHR_variable_pointers\0" // IR(4636, 26)
  "SPV_KHR_vulkan_memory_model\0" // IR(4662, 28)
  "SPV_KHR_workgroup_memory_explicit_layout\0" // IR(4690, 41)
  "SPV_NVX_multiview_per_view_attributes\0" // IR(4731, 38)
  "SPV_NV_bindless_texture\0" // IR(4769, 24)
  "SPV_NV_cluster_acceleration_structure\0" // IR(4793, 38)
  "SPV_NV_compute_shader_derivatives\0" // IR(4831, 34)
  "SPV_NV_cooperative_matrix\0" // IR(4865, 26)
  "SPV_NV_cooperative_matrix2\0" // IR(4891, 27)
  "SPV_NV_cooperative_matrix_decode_vector\0" // IR(4918, 40)
  "SPV_NV_cooperative_vector\0" // IR(4958, 26)
  "SPV_NV_displacement_micromap\0" // IR(4984, 29)
  "SPV_NV_fragment_shader_barycentric\0" // IR(5013, 35)
  "SPV_NV_geometry_shader_passthrough\0" // IR(5048, 35)
  "SPV_NV_linear_swept_spheres\0" // IR(5083, 28)
  "SPV_NV_mesh_shader\0" // IR(5111, 19)
  "SPV_NV_push_constant_bank\0" // IR(5130, 26)
  "SPV_NV_raw_access_chains\0" // IR(5156, 25)
  "SPV_NV_ray_tracing\0" // IR(5181, 19)
  "SPV_NV_ray_tracing_motion_blur\0" // IR(5200, 31)
  "SPV_NV_sample_mask_override_coverage\0" // IR(5231, 37)
  "SPV_NV_shader_atomic_fp16_vector\0" // IR(5268, 33)
  "SPV_NV_shader_image_footprint\0" // IR(5301, 30)
  "SPV_NV_shader_invocation_reorder\0" // IR(5331, 33)
  "SPV_NV_shader_sm_builtins\0" // IR(5364, 26)
  "SPV_NV_shader_subgroup_partitioned\0" // IR(5390, 35)
  "SPV_NV_shading_rate\0" // IR(5425, 20)
  "SPV_NV_stereo_view_rendering\0" // IR(5445, 29)
  "SPV_NV_tensor_addressing\0" // IR(5474, 25)
  "SPV_NV_viewport_array2\0" // IR(5499, 23)
  "SPV_QCOM_cooperative_matrix_conversion\0" // IR(5522, 39)
  "SPV_QCOM_image_processing\0" // IR(5561, 26)
  "SPV_QCOM_image_processing2\0" // IR(5587, 27)
  "SPV_QCOM_tile_shading\0" // IR(5614, 22)
  "SPV_VALIDATOR_ignore_type_decl_unique\0" // IR(5636, 38)
  "SPV_VALVE_mixed_float_dot_product\0" // IR(5674, 34)
  "ReadOnly\0" // IR(5708, 9)
  "Kernel\0" // IR(5717, 7)
  "WriteOnly\0" // IR(5724, 10)
  "ReadWrite\0" // IR(5734, 10)
  "Logical\0" // IR(5744, 8)
  "Physical32\0" // IR(5752, 11)
  "Addresses\0" // IR(5763, 10)
  "Physical64\0" // IR(5773, 11)
  "PhysicalStorageBuffer64\0" // IR(5784, 24)
  "PhysicalStorageBuffer64EXT\0" // IR(5808, 27)
  "PhysicalStorageBufferAddresses\0" // IR(5835, 31)
  "Position\0" // IR(5866, 9)
  "Shader\0" // IR(5875, 7)
  "PointSize\0" // IR(5882, 10)
  "ClipDistance\0" // IR(5892, 13)
  "CullDistance\0" // IR(5905, 13)
  "VertexId\0" // IR(5918, 9)
  "InstanceId\0" // IR(5927, 11)
  "PrimitiveId\0" // IR(5938, 12)
  "Geometry\0" // IR(5950, 9)
  "Tessellation\0" // IR(5959, 13)
  "RayTracingNV\0" // IR(5972, 13)
  "RayTracingKHR\0" // IR(5985, 14)
  "MeshShadingNV\0" // IR(5999, 14)
  "MeshShadingEXT\0" // IR(6013, 15)
  "InvocationId\0" // IR(6028, 13)
  "Layer\0" // IR(6041, 6)
  "ShaderLayer\0" // IR(6047, 12)
  "ShaderViewportIndexLayerEXT\0" // IR(6059, 28)
  "ViewportIndex\0" // IR(6087, 14)
  "MultiViewport\0" // IR(6101, 14)
  "ShaderViewportIndex\0" // IR(6115, 20)
  "TessLevelOuter\0" // IR(6135, 15)
  "TessLevelInner\0" // IR(6150, 15)
  "TessCoord\0" // IR(6165, 10)
  "PatchVertices\0" // IR(6175, 14)
  "FragCoord\0" // IR(6189, 10)
  "PointCoord\0" // IR(6199, 11)
  "FrontFacing\0" // IR(6210, 12)
  "SampleId\0" // IR(6222, 9)
  "SampleRateShading\0" // IR(6231, 18)
  "SamplePosition\0" // IR(6249, 15)
  "SampleMask\0" // IR(6264, 11)
  "FragDepth\0" // IR(6275, 10)
  "HelperInvocation\0" // IR(6285, 17)
  "NumWorkgroups\0" // IR(6302, 14)
  "WorkgroupSize\0" // IR(6316, 14)
  "WorkgroupId\0" // IR(6330, 12)
  "LocalInvocationId\0" // IR(6342, 18)
  "GlobalInvocationId\0" // IR(6360, 19)
  "LocalInvocationIndex\0" // IR(6379, 21)
  "WorkDim\0" // IR(6400, 8)
  "GlobalSize\0" // IR(6408, 11)
  "EnqueuedWorkgroupSize\0" // IR(6419, 22)
  "GlobalOffset\0" // IR(6441, 13)
  "GlobalLinearId\0" // IR(6454, 15)
  "SubgroupSize\0" // IR(6469, 13)
  "GroupNonUniform\0" // IR(6482, 16)
  "SubgroupBallotKHR\0" // IR(6498, 18)
  "SubgroupMaxSize\0" // IR(6516, 16)
  "NumSubgroups\0" // IR(6532, 13)
  "NumEnqueuedSubgroups\0" // IR(6545, 21)
  "SubgroupId\0" // IR(6566, 11)
  "SubgroupLocalInvocationId\0" // IR(6577, 26)
  "VertexIndex\0" // IR(6603, 12)
  "InstanceIndex\0" // IR(6615, 14)
  "CoreIDARM\0" // IR(6629, 10)
  "CoreBuiltinsARM\0" // IR(6639, 16)
  "CoreCountARM\0" // IR(6655, 13)
  "CoreMaxIDARM\0" // IR(6668, 13)
  "WarpIDARM\0" // IR(6681, 10)
  "WarpMaxIDARM\0" // IR(6691, 13)
  "SubgroupEqMask\0" // IR(6704, 15)
  "SubgroupEqMaskKHR\0" // IR(6719, 18)
  "GroupNonUniformBallot\0" // IR(6737, 22)
  "SubgroupGeMask\0" // IR(6759, 15)
  "SubgroupGeMaskKHR\0" // IR(6774, 18)
  "SubgroupGtMask\0" // IR(6792, 15)
  "SubgroupGtMaskKHR\0" // IR(6807, 18)
  "SubgroupLeMask\0" // IR(6825, 15)
  "SubgroupLeMaskKHR\0" // IR(6840, 18)
  "SubgroupLtMask\0" // IR(6858, 15)
  "SubgroupLtMaskKHR\0" // IR(6873, 18)
  "BaseVertex\0" // IR(6891, 11)
  "DrawParameters\0" // IR(6902, 15)
  "BaseInstance\0" // IR(6917, 13)
  "DrawIndex\0" // IR(6930, 10)
  "PrimitiveShadingRateKHR\0" // IR(6940, 24)
  "FragmentShadingRateKHR\0" // IR(6964, 23)
  "DeviceIndex\0" // IR(6987, 12)
  "DeviceGroup\0" // IR(6999, 12)
  "ViewIndex\0" // IR(7011, 10)
  "MultiView\0" // IR(7021, 10)
  "ShadingRateKHR\0" // IR(7031, 15)
  "TileOffsetQCOM\0" // IR(7046, 15)
  "TileShadingQCOM\0" // IR(7061, 16)
  "TileDimensionQCOM\0" // IR(7077, 18)
  "TileApronSizeQCOM\0" // IR(7095, 18)
  "BaryCoordNoPerspAMD\0" // IR(7113, 20)
  "BaryCoordNoPerspCentroidAMD\0" // IR(7133, 28)
  "BaryCoordNoPerspSampleAMD\0" // IR(7161, 26)
  "BaryCoordSmoothAMD\0" // IR(7187, 19)
  "BaryCoordSmoothCentroidAMD\0" // IR(7206, 27)
  "BaryCoordSmoothSampleAMD\0" // IR(7233, 25)
  "BaryCoordPullModelAMD\0" // IR(7258, 22)
  "FragStencilRefEXT\0" // IR(7280, 18)
  "StencilExportEXT\0" // IR(7298, 17)
  "RemainingRecursionLevelsAMDX\0" // IR(7315, 29)
  "ShaderEnqueueAMDX\0" // IR(7344, 18)
  "ShaderIndexAMDX\0" // IR(7362, 16)
  "SamplerHeapEXT\0" // IR(7378, 15)
  "DescriptorHeapEXT\0" // IR(7393, 18)
  "ResourceHeapEXT\0" // IR(7411, 16)
  "ViewportMaskNV\0" // IR(7427, 15)
  "ShaderViewportMaskNV\0" // IR(7442, 21)
  "SecondaryPositionNV\0" // IR(7463, 20)
  "ShaderStereoViewNV\0" // IR(7483, 19)
  "SecondaryViewportMaskNV\0" // IR(7502, 24)
  "PositionPerViewNV\0" // IR(7526, 18)
  "PerViewAttributesNV\0" // IR(7544, 20)
  "ViewportMaskPerViewNV\0" // IR(7564, 22)
  "FullyCoveredEXT\0" // IR(7586, 16)
  "FragmentFullyCoveredEXT\0" // IR(7602, 24)
  "TaskCountNV\0" // IR(7626, 12)
  "PrimitiveCountNV\0" // IR(7638, 17)
  "PrimitiveIndicesNV\0" // IR(7655, 19)
  "ClipDistancePerViewNV\0" // IR(7674, 22)
  "CullDistancePerViewNV\0" // IR(7696, 22)
  "LayerPerViewNV\0" // IR(7718, 15)
  "MeshViewCountNV\0" // IR(7733, 16)
  "MeshViewIndicesNV\0" // IR(7749, 18)
  "BaryCoordKHR\0" // IR(7767, 13)
  "BaryCoordNV\0" // IR(7780, 12)
  "FragmentBarycentricKHR\0" // IR(7792, 23)
  "BaryCoordNoPerspKHR\0" // IR(7815, 20)
  "BaryCoordNoPerspNV\0" // IR(7835, 19)
  "FragSizeEXT\0" // IR(7854, 12)
  "FragmentSizeNV\0" // IR(7866, 15)
  "FragmentDensityEXT\0" // IR(7881, 19)
  "FragInvocationCountEXT\0" // IR(7900, 23)
  "InvocationsPerPixelNV\0" // IR(7923, 22)
  "PrimitivePointIndicesEXT\0" // IR(7945, 25)
  "PrimitiveLineIndicesEXT\0" // IR(7970, 24)
  "PrimitiveTriangleIndicesEXT\0" // IR(7994, 28)
  "CullPrimitiveEXT\0" // IR(8022, 17)
  "LaunchIdKHR\0" // IR(8039, 12)
  "LaunchIdNV\0" // IR(8051, 11)
  "LaunchSizeKHR\0" // IR(8062, 14)
  "LaunchSizeNV\0" // IR(8076, 13)
  "WorldRayOriginKHR\0" // IR(8089, 18)
  "WorldRayOriginNV\0" // IR(8107, 17)
  "WorldRayDirectionKHR\0" // IR(8124, 21)
  "WorldRayDirectionNV\0" // IR(8145, 20)
  "ObjectRayOriginKHR\0" // IR(8165, 19)
  "ObjectRayOriginNV\0" // IR(8184, 18)
  "ObjectRayDirectionKHR\0" // IR(8202, 22)
  "ObjectRayDirectionNV\0" // IR(8224, 21)
  "RayTminKHR\0" // IR(8245, 11)
  "RayTminNV\0" // IR(8256, 10)
  "RayTmaxKHR\0" // IR(8266, 11)
  "RayTmaxNV\0" // IR(8277, 10)
  "InstanceCustomIndexKHR\0" // IR(8287, 23)
  "InstanceCustomIndexNV\0" // IR(8310, 22)
  "ObjectToWorldKHR\0" // IR(8332, 17)
  "ObjectToWorldNV\0" // IR(8349, 16)
  "WorldToObjectKHR\0" // IR(8365, 17)
  "WorldToObjectNV\0" // IR(8382, 16)
  "HitTNV\0" // IR(8398, 7)
  "HitKindKHR\0" // IR(8405, 11)
  "HitKindNV\0" // IR(8416, 10)
  "CurrentRayTimeNV\0" // IR(8426, 17)
  "RayTracingMotionBlurNV\0" // IR(8443, 23)
  "HitTriangleVertexPositionsKHR\0" // IR(8466, 30)
  "RayTracingPositionFetchKHR\0" // IR(8496, 27)
  "HitMicroTriangleVertexPositionsNV\0" // IR(8523, 34)
  "RayTracingDisplacementMicromapNV\0" // IR(8557, 33)
  "HitMicroTriangleVertexBarycentricsNV\0" // IR(8590, 37)
  "IncomingRayFlagsKHR\0" // IR(8627, 20)
  "IncomingRayFlagsNV\0" // IR(8647, 19)
  "RayGeometryIndexKHR\0" // IR(8666, 20)
  "HitIsSphereNV\0" // IR(8686, 14)
  "RayTracingSpheresGeometryNV\0" // IR(8700, 28)
  "HitIsLSSNV\0" // IR(8728, 11)
  "RayTracingLinearSweptSpheresGeometryNV\0" // IR(8739, 39)
  "HitSpherePositionNV\0" // IR(8778, 20)
  "WarpsPerSMNV\0" // IR(8798, 13)
  "ShaderSMBuiltinsNV\0" // IR(8811, 19)
  "SMCountNV\0" // IR(8830, 10)
  "WarpIDNV\0" // IR(8840, 9)
  "SMIDNV\0" // IR(8849, 7)
  "HitLSSPositionsNV\0" // IR(8856, 18)
  "HitKindFrontFacingMicroTriangleNV\0" // IR(8874, 34)
  "HitKindBackFacingMicroTriangleNV\0" // IR(8908, 33)
  "HitSphereRadiusNV\0" // IR(8941, 18)
  "HitLSSRadiiNV\0" // IR(8959, 14)
  "ClusterIDNV\0" // IR(8973, 12)
  "RayTracingClusterAccelerationStructureNV\0" // IR(8985, 41)
  "CullMaskKHR\0" // IR(9026, 12)
  "RayCullMaskKHR\0" // IR(9038, 15)
  "Matrix\0" // IR(9053, 7)
  "Linkage\0" // IR(9060, 8)
  "Vector16\0" // IR(9068, 9)
  "Float16Buffer\0" // IR(9077, 14)
  "Float16\0" // IR(9091, 8)
  "Float64\0" // IR(9099, 8)
  "Int64\0" // IR(9107, 6)
  "Int64Atomics\0" // IR(9113, 13)
  "ImageBasic\0" // IR(9126, 11)
  "ImageReadWrite\0" // IR(9137, 15)
  "ImageMipmap\0" // IR(9152, 12)
  "Pipes\0" // IR(9164, 6)
  "Groups\0" // IR(9170, 7)
  "DeviceEnqueue\0" // IR(9177, 14)
  "LiteralSampler\0" // IR(9191, 15)
  "AtomicStorage\0" // IR(9206, 14)
  "Int16\0" // IR(9220, 6)
  "TessellationPointSize\0" // IR(9226, 22)
  "GeometryPointSize\0" // IR(9248, 18)
  "ImageGatherExtended\0" // IR(9266, 20)
  "StorageImageMultisample\0" // IR(9286, 24)
  "UniformBufferArrayDynamicIndexing\0" // IR(9310, 34)
  "SampledImageArrayDynamicIndexing\0" // IR(9344, 33)
  "StorageBufferArrayDynamicIndexing\0" // IR(9377, 34)
  "StorageImageArrayDynamicIndexing\0" // IR(9411, 33)
  "ImageCubeArray\0" // IR(9444, 15)
  "SampledCubeArray\0" // IR(9459, 17)
  "ImageRect\0" // IR(9476, 10)
  "SampledRect\0" // IR(9486, 12)
  "GenericPointer\0" // IR(9498, 15)
  "Int8\0" // IR(9513, 5)
  "InputAttachment\0" // IR(9518, 16)
  "SparseResidency\0" // IR(9534, 16)
  "MinLod\0" // IR(9550, 7)
  "Sampled1D\0" // IR(9557, 10)
  "Image1D\0" // IR(9567, 8)
  "SampledBuffer\0" // IR(9575, 14)
  "ImageBuffer\0" // IR(9589, 12)
  "ImageMSArray\0" // IR(9601, 13)
  "StorageImageExtendedFormats\0" // IR(9614, 28)
  "ImageQuery\0" // IR(9642, 11)
  "DerivativeControl\0" // IR(9653, 18)
  "InterpolationFunction\0" // IR(9671, 22)
  "TransformFeedback\0" // IR(9693, 18)
  "GeometryStreams\0" // IR(9711, 16)
  "StorageImageReadWithoutFormat\0" // IR(9727, 30)
  "StorageImageWriteWithoutFormat\0" // IR(9757, 31)
  "SubgroupDispatch\0" // IR(9788, 17)
  "NamedBarrier\0" // IR(9805, 13)
  "PipeStorage\0" // IR(9818, 12)
  "GroupNonUniformVote\0" // IR(9830, 20)
  "GroupNonUniformArithmetic\0" // IR(9850, 26)
  "GroupNonUniformShuffle\0" // IR(9876, 23)
  "GroupNonUniformShuffleRelative\0" // IR(9899, 31)
  "GroupNonUniformClustered\0" // IR(9930, 25)
  "GroupNonUniformQuad\0" // IR(9955, 20)
  "UniformDecoration\0" // IR(9975, 18)
  "TileImageColorReadAccessEXT\0" // IR(9993, 28)
  "TileImageDepthReadAccessEXT\0" // IR(10021, 28)
  "TileImageStencilReadAccessEXT\0" // IR(10049, 30)
  "TensorsARM\0" // IR(10079, 11)
  "StorageTensorArrayDynamicIndexingARM\0" // IR(10090, 37)
  "StorageTensorArrayNonUniformIndexingARM\0" // IR(10127, 40)
  "GraphARM\0" // IR(10167, 9)
  "CooperativeMatrixLayoutsARM\0" // IR(10176, 28)
  "Float8EXT\0" // IR(10204, 10)
  "Float8CooperativeMatrixEXT\0" // IR(10214, 27)
  "CooperativeMatrixKHR\0" // IR(10241, 21)
  "WorkgroupMemoryExplicitLayoutKHR\0" // IR(10262, 33)
  "WorkgroupMemoryExplicitLayout8BitAccessKHR\0" // IR(10295, 43)
  "WorkgroupMemoryExplicitLayout16BitAccessKHR\0" // IR(10338, 44)
  "SubgroupVoteKHR\0" // IR(10382, 16)
  "StorageBuffer16BitAccess\0" // IR(10398, 25)
  "StorageUniformBufferBlock16\0" // IR(10423, 28)
  "UniformAndStorageBuffer16BitAccess\0" // IR(10451, 35)
  "StorageUniform16\0" // IR(10486, 17)
  "StoragePushConstant16\0" // IR(10503, 22)
  "StorageInputOutput16\0" // IR(10525, 21)
  "VariablePointersStorageBuffer\0" // IR(10546, 30)
  "VariablePointers\0" // IR(10576, 17)
  "AtomicStorageOps\0" // IR(10593, 17)
  "SampleMaskPostDepthCoverage\0" // IR(10610, 28)
  "StorageBuffer8BitAccess\0" // IR(10638, 24)
  "UniformAndStorageBuffer8BitAccess\0" // IR(10662, 34)
  "StoragePushConstant8\0" // IR(10696, 21)
  "DenormPreserve\0" // IR(10717, 15)
  "DenormFlushToZero\0" // IR(10732, 18)
  "SignedZeroInfNanPreserve\0" // IR(10750, 25)
  "RoundingModeRTE\0" // IR(10775, 16)
  "RoundingModeRTZ\0" // IR(10791, 16)
  "RayQueryProvisionalKHR\0" // IR(10807, 23)
  "RayQueryKHR\0" // IR(10830, 12)
  "UntypedPointersKHR\0" // IR(10842, 19)
  "RayTraversalPrimitiveCullingKHR\0" // IR(10861, 32)
  "TextureSampleWeightedQCOM\0" // IR(10893, 26)
  "TextureBoxFilterQCOM\0" // IR(10919, 21)
  "TextureBlockMatchQCOM\0" // IR(10940, 22)
  "CooperativeMatrixConversionQCOM\0" // IR(10962, 32)
  "TextureBlockMatch2QCOM\0" // IR(10994, 23)
  "Float16ImageAMD\0" // IR(11017, 16)
  "ImageGatherBiasLodAMD\0" // IR(11033, 22)
  "FragmentMaskAMD\0" // IR(11055, 16)
  "ImageReadWriteLodAMD\0" // IR(11071, 21)
  "Int64ImageEXT\0" // IR(11092, 14)
  "ShaderClockKHR\0" // IR(11106, 15)
  "QuadControlKHR\0" // IR(11121, 15)
  "Int4TypeINTEL\0" // IR(11136, 14)
  "Int4CooperativeMatrixINTEL\0" // IR(11150, 27)
  "BFloat16TypeKHR\0" // IR(11177, 16)
  "BFloat16DotProductKHR\0" // IR(11193, 22)
  "BFloat16CooperativeMatrixKHR\0" // IR(11215, 29)
  "AbortKHR\0" // IR(11244, 9)
  "ConstantDataKHR\0" // IR(11253, 16)
  "PoisonFreezeKHR\0" // IR(11269, 16)
  "WeakLinkageAMD\0" // IR(11285, 15)
  "SampleMaskOverrideCoverageNV\0" // IR(11300, 29)
  "GeometryShaderPassthroughNV\0" // IR(11329, 28)
  "ShaderViewportIndexLayerNV\0" // IR(11357, 27)
  "ImageFootprintNV\0" // IR(11384, 17)
  "FragmentBarycentricNV\0" // IR(11401, 22)
  "ComputeDerivativeGroupQuadsKHR\0" // IR(11423, 31)
  "ComputeDerivativeGroupQuadsNV\0" // IR(11454, 30)
  "ShadingRateNV\0" // IR(11484, 14)
  "GroupNonUniformPartitionedEXT\0" // IR(11498, 30)
  "GroupNonUniformPartitionedNV\0" // IR(11528, 29)
  "ShaderNonUniform\0" // IR(11557, 17)
  "ShaderNonUniformEXT\0" // IR(11574, 20)
  "RuntimeDescriptorArray\0" // IR(11594, 23)
  "RuntimeDescriptorArrayEXT\0" // IR(11617, 26)
  "InputAttachmentArrayDynamicIndexing\0" // IR(11643, 36)
  "InputAttachmentArrayDynamicIndexingEXT\0" // IR(11679, 39)
  "UniformTexelBufferArrayDynamicIndexing\0" // IR(11718, 39)
  "UniformTexelBufferArrayDynamicIndexingEXT\0" // IR(11757, 42)
  "StorageTexelBufferArrayDynamicIndexing\0" // IR(11799, 39)
  "StorageTexelBufferArrayDynamicIndexingEXT\0" // IR(11838, 42)
  "UniformBufferArrayNonUniformIndexing\0" // IR(11880, 37)
  "UniformBufferArrayNonUniformIndexingEXT\0" // IR(11917, 40)
  "SampledImageArrayNonUniformIndexing\0" // IR(11957, 36)
  "SampledImageArrayNonUniformIndexingEXT\0" // IR(11993, 39)
  "StorageBufferArrayNonUniformIndexing\0" // IR(12032, 37)
  "StorageBufferArrayNonUniformIndexingEXT\0" // IR(12069, 40)
  "StorageImageArrayNonUniformIndexing\0" // IR(12109, 36)
  "StorageImageArrayNonUniformIndexingEXT\0" // IR(12145, 39)
  "InputAttachmentArrayNonUniformIndexing\0" // IR(12184, 39)
  "InputAttachmentArrayNonUniformIndexingEXT\0" // IR(12223, 42)
  "UniformTexelBufferArrayNonUniformIndexing\0" // IR(12265, 42)
  "UniformTexelBufferArrayNonUniformIndexingEXT\0" // IR(12307, 45)
  "StorageTexelBufferArrayNonUniformIndexing\0" // IR(12352, 42)
  "StorageTexelBufferArrayNonUniformIndexingEXT\0" // IR(12394, 45)
  "VulkanMemoryModel\0" // IR(12439, 18)
  "VulkanMemoryModelKHR\0" // IR(12457, 21)
  "VulkanMemoryModelDeviceScope\0" // IR(12478, 29)
  "VulkanMemoryModelDeviceScopeKHR\0" // IR(12507, 32)
  "PhysicalStorageBufferAddressesEXT\0" // IR(12539, 34)
  "ComputeDerivativeGroupLinearKHR\0" // IR(12573, 32)
  "ComputeDerivativeGroupLinearNV\0" // IR(12605, 31)
  "RayTracingProvisionalKHR\0" // IR(12636, 25)
  "CooperativeMatrixNV\0" // IR(12661, 20)
  "FragmentShaderSampleInterlockEXT\0" // IR(12681, 33)
  "FragmentShaderShadingRateInterlockEXT\0" // IR(12714, 38)
  "FragmentShaderPixelInterlockEXT\0" // IR(12752, 32)
  "DemoteToHelperInvocation\0" // IR(12784, 25)
  "DemoteToHelperInvocationEXT\0" // IR(12809, 28)
  "DisplacementMicromapNV\0" // IR(12837, 23)
  "RayTracingOpacityMicromapKHR\0" // IR(12860, 29)
  "RayTracingOpacityMicromapEXT\0" // IR(12889, 29)
  "ShaderInvocationReorderNV\0" // IR(12918, 26)
  "ShaderInvocationReorderEXT\0" // IR(12944, 27)
  "BindlessTextureNV\0" // IR(12971, 18)
  "RayQueryPositionFetchKHR\0" // IR(12989, 25)
  "CooperativeVectorNV\0" // IR(13014, 20)
  "AtomicFloat16VectorNV\0" // IR(13034, 22)
  "RawAccessChainsNV\0" // IR(13056, 18)
  "PushConstantBanksNV\0" // IR(13074, 20)
  "LongVectorEXT\0" // IR(13094, 14)
  "Shader64BitIndexingEXT\0" // IR(13108, 23)
  "CooperativeMatrixReductionsNV\0" // IR(13131, 30)
  "CooperativeMatrixConversionsNV\0" // IR(13161, 31)
  "CooperativeMatrixPerElementOperationsNV\0" // IR(13192, 40)
  "CooperativeMatrixTensorAddressingNV\0" // IR(13232, 36)
  "CooperativeMatrixBlockLoadsNV\0" // IR(13268, 30)
  "CooperativeVectorTrainingNV\0" // IR(13298, 28)
  "TensorAddressingNV\0" // IR(13326, 19)
  "CooperativeMatrixDecodeVectorNV\0" // IR(13345, 32)
  "SubgroupShuffleINTEL\0" // IR(13377, 21)
  "SubgroupBufferBlockIOINTEL\0" // IR(13398, 27)
  "SubgroupImageBlockIOINTEL\0" // IR(13425, 26)
  "SubgroupImageMediaBlockIOINTEL\0" // IR(13451, 31)
  "RoundToInfinityINTEL\0" // IR(13482, 21)
  "FloatingPointModeINTEL\0" // IR(13503, 23)
  "IntegerFunctions2INTEL\0" // IR(13526, 23)
  "FunctionPointersINTEL\0" // IR(13549, 22)
  "IndirectReferencesINTEL\0" // IR(13571, 24)
  "AsmINTEL\0" // IR(13595, 9)
  "AtomicFloat32MinMaxEXT\0" // IR(13604, 23)
  "AtomicFloat64MinMaxEXT\0" // IR(13627, 23)
  "AtomicFloat16MinMaxEXT\0" // IR(13650, 23)
  "VectorComputeINTEL\0" // IR(13673, 19)
  "VectorAnyINTEL\0" // IR(13692, 15)
  "ExpectAssumeKHR\0" // IR(13707, 16)
  "SubgroupAvcMotionEstimationINTEL\0" // IR(13723, 33)
  "SubgroupAvcMotionEstimationIntraINTEL\0" // IR(13756, 38)
  "SubgroupAvcMotionEstimationChromaINTEL\0" // IR(13794, 39)
  "VariableLengthArrayINTEL\0" // IR(13833, 25)
  "FunctionFloatControlINTEL\0" // IR(13858, 26)
  "FPGAMemoryAttributesALTERA\0" // IR(13884, 27)
  "FPGAMemoryAttributesINTEL\0" // IR(13911, 26)
  "FPFastMathModeINTEL\0" // IR(13937, 20)
  "ArbitraryPrecisionIntegersALTERA\0" // IR(13957, 33)
  "ArbitraryPrecisionIntegersINTEL\0" // IR(13990, 32)
  "ArbitraryPrecisionFloatingPointALTERA\0" // IR(14022, 38)
  "ArbitraryPrecisionFloatingPointINTEL\0" // IR(14060, 37)
  "UnstructuredLoopControlsINTEL\0" // IR(14097, 30)
  "FPGALoopControlsALTERA\0" // IR(14127, 23)
  "FPGALoopControlsINTEL\0" // IR(14150, 22)
  "KernelAttributesINTEL\0" // IR(14172, 22)
  "FPGAKernelAttributesINTEL\0" // IR(14194, 26)
  "FPGAMemoryAccessesALTERA\0" // IR(14220, 25)
  "FPGAMemoryAccessesINTEL\0" // IR(14245, 24)
  "FPGAClusterAttributesALTERA\0" // IR(14269, 28)
  "FPGAClusterAttributesINTEL\0" // IR(14297, 27)
  "LoopFuseALTERA\0" // IR(14324, 15)
  "LoopFuseINTEL\0" // IR(14339, 14)
  "FPGADSPControlALTERA\0" // IR(14353, 21)
  "FPGADSPControlINTEL\0" // IR(14374, 20)
  "MemoryAccessAliasingINTEL\0" // IR(14394, 26)
  "FPGAInvocationPipeliningAttributesALTERA\0" // IR(14420, 41)
  "FPGAInvocationPipeliningAttributesINTEL\0" // IR(14461, 40)
  "FPGABufferLocationALTERA\0" // IR(14501, 25)
  "FPGABufferLocationINTEL\0" // IR(14526, 24)
  "ArbitraryPrecisionFixedPointALTERA\0" // IR(14550, 35)
  "ArbitraryPrecisionFixedPointINTEL\0" // IR(14585, 34)
  "USMStorageClassesALTERA\0" // IR(14619, 24)
  "USMStorageClassesINTEL\0" // IR(14643, 23)
  "RuntimeAlignedAttributeALTERA\0" // IR(14666, 30)
  "RuntimeAlignedAttributeINTEL\0" // IR(14696, 29)
  "IOPipesALTERA\0" // IR(14725, 14)
  "IOPipesINTEL\0" // IR(14739, 13)
  "BlockingPipesALTERA\0" // IR(14752, 20)
  "BlockingPipesINTEL\0" // IR(14772, 19)
  "FPGARegALTERA\0" // IR(14791, 14)
  "FPGARegINTEL\0" // IR(14805, 13)
  "DotProductInputAll\0" // IR(14818, 19)
  "DotProductInputAllKHR\0" // IR(14837, 22)
  "DotProductInput4x8Bit\0" // IR(14859, 22)
  "DotProductInput4x8BitKHR\0" // IR(14881, 25)
  "DotProductInput4x8BitPacked\0" // IR(14906, 28)
  "DotProductInput4x8BitPackedKHR\0" // IR(14934, 31)
  "DotProduct\0" // IR(14965, 11)
  "DotProductKHR\0" // IR(14976, 14)
  "ReplicatedCompositesEXT\0" // IR(14990, 24)
  "BitInstructions\0" // IR(15014, 16)
  "GroupNonUniformRotateKHR\0" // IR(15030, 25)
  "FloatControls2\0" // IR(15055, 15)
  "FMAKHR\0" // IR(15070, 7)
  "RayTracingOpacityMicromapExecutionModeKHR\0" // IR(15077, 42)
  "AtomicFloat32AddEXT\0" // IR(15119, 20)
  "AtomicFloat64AddEXT\0" // IR(15139, 20)
  "LongCompositesINTEL\0" // IR(15159, 20)
  "OptNoneEXT\0" // IR(15179, 11)
  "OptNoneINTEL\0" // IR(15190, 13)
  "AtomicFloat16AddEXT\0" // IR(15203, 20)
  "DebugInfoModuleINTEL\0" // IR(15223, 21)
  "BFloat16ConversionINTEL\0" // IR(15244, 24)
  "SplitBarrierEXT\0" // IR(15268, 16)
  "SplitBarrierINTEL\0" // IR(15284, 18)
  "ArithmeticFenceEXT\0" // IR(15302, 19)
  "FPGAClusterAttributesV2ALTERA\0" // IR(15321, 30)
  "FPGAClusterAttributesV2INTEL\0" // IR(15351, 29)
  "FPGAKernelAttributesv2INTEL\0" // IR(15380, 28)
  "TaskSequenceALTERA\0" // IR(15408, 19)
  "TaskSequenceINTEL\0" // IR(15427, 18)
  "FPMaxErrorINTEL\0" // IR(15445, 16)
  "FPGALatencyControlALTERA\0" // IR(15461, 25)
  "FPGALatencyControlINTEL\0" // IR(15486, 24)
  "FPGAArgumentInterfacesALTERA\0" // IR(15510, 29)
  "FPGAArgumentInterfacesINTEL\0" // IR(15539, 28)
  "GlobalVariableHostAccessINTEL\0" // IR(15567, 30)
  "GlobalVariableFPGADecorationsALTERA\0" // IR(15597, 36)
  "GlobalVariableFPGADecorationsINTEL\0" // IR(15633, 35)
  "SubgroupBufferPrefetchINTEL\0" // IR(15668, 28)
  "Subgroup2DBlockIOINTEL\0" // IR(15696, 23)
  "Subgroup2DBlockTransformINTEL\0" // IR(15719, 30)
  "Subgroup2DBlockTransposeINTEL\0" // IR(15749, 30)
  "SubgroupMatrixMultiplyAccumulateINTEL\0" // IR(15779, 38)
  "TernaryBitwiseFunctionINTEL\0" // IR(15817, 28)
  "UntypedVariableLengthArrayINTEL\0" // IR(15845, 32)
  "SpecConditionalINTEL\0" // IR(15877, 21)
  "FunctionVariantsINTEL\0" // IR(15898, 22)
  "PredicatedIOINTEL\0" // IR(15920, 18)
  "RoundedDivideSqrtINTEL\0" // IR(15938, 23)
  "GroupUniformArithmeticKHR\0" // IR(15961, 26)
  "TensorFloat32RoundingINTEL\0" // IR(15987, 27)
  "MaskedGatherScatterINTEL\0" // IR(16014, 25)
  "CacheControlsINTEL\0" // IR(16039, 19)
  "RegisterLimitsINTEL\0" // IR(16058, 20)
  "BindlessImagesINTEL\0" // IR(16078, 20)
  "DotProductFloat16AccFloat32VALVE\0" // IR(16098, 33)
  "DotProductFloat16AccFloat16VALVE\0" // IR(16131, 33)
  "DotProductBFloat16AccVALVE\0" // IR(16164, 27)
  "DotProductFloat8AccFloat32VALVE\0" // IR(16191, 32)
  "Unspecified\0" // IR(16223, 12)
  "Address\0" // IR(16235, 8)
  "Boolean\0" // IR(16243, 8)
  "Float\0" // IR(16251, 6)
  "Signed\0" // IR(16257, 7)
  "SignedChar\0" // IR(16264, 11)
  "Unsigned\0" // IR(16275, 9)
  "UnsignedChar\0" // IR(16284, 13)
  "Class\0" // IR(16297, 6)
  "Structure\0" // IR(16303, 10)
  "Union\0" // IR(16313, 6)
  "ImportedModule\0" // IR(16319, 15)
  "ImportedDeclaration\0" // IR(16334, 20)
  "None\0" // IR(16354, 5)
  "FlagIsProtected\0" // IR(16359, 16)
  "FlagIsPrivate\0" // IR(16375, 14)
  "FlagIsPublic\0" // IR(16389, 13)
  "FlagIsLocal\0" // IR(16402, 12)
  "FlagIsDefinition\0" // IR(16414, 17)
  "FlagFwdDecl\0" // IR(16431, 12)
  "FlagArtificial\0" // IR(16443, 15)
  "FlagExplicit\0" // IR(16458, 13)
  "FlagPrototyped\0" // IR(16471, 15)
  "FlagObjectPointer\0" // IR(16486, 18)
  "FlagStaticMember\0" // IR(16504, 17)
  "FlagIndirectVariable\0" // IR(16521, 21)
  "FlagLValueReference\0" // IR(16542, 20)
  "FlagRValueReference\0" // IR(16562, 20)
  "FlagIsOptimized\0" // IR(16582, 16)
  "FlagIsEnumClass\0" // IR(16598, 16)
  "FlagTypePassByValue\0" // IR(16614, 20)
  "FlagTypePassByReference\0" // IR(16634, 24)
  "Deref\0" // IR(16658, 6)
  "Plus\0" // IR(16664, 5)
  "Minus\0" // IR(16669, 6)
  "SPV_OPERAND_TYPE_LITERAL_INTEGER\0" // IR(16675, 33)
  "PlusUconst\0" // IR(16708, 11)
  "BitPiece\0" // IR(16719, 9)
  "Swap\0" // IR(16728, 5)
  "Xderef\0" // IR(16733, 7)
  "StackValue\0" // IR(16740, 11)
  "Constu\0" // IR(16751, 7)
  "Fragment\0" // IR(16758, 9)
  "ConstType\0" // IR(16767, 10)
  "VolatileType\0" // IR(16777, 13)
  "RestrictType\0" // IR(16790, 13)
  "AtomicType\0" // IR(16803, 11)
  "Float16NV\0" // IR(16814, 10)
  "Float32NV\0" // IR(16824, 10)
  "Float64NV\0" // IR(16834, 10)
  "SignedInt8NV\0" // IR(16844, 13)
  "SignedInt16NV\0" // IR(16857, 14)
  "SignedInt32NV\0" // IR(16871, 14)
  "SignedInt64NV\0" // IR(16885, 14)
  "UnsignedInt8NV\0" // IR(16899, 15)
  "UnsignedInt16NV\0" // IR(16914, 16)
  "UnsignedInt32NV\0" // IR(16930, 16)
  "UnsignedInt64NV\0" // IR(16946, 16)
  "SignedInt8PackedNV\0" // IR(16962, 19)
  "UnsignedInt8PackedNV\0" // IR(16981, 21)
  "FloatE4M3NV\0" // IR(17002, 12)
  "FloatE5M2NV\0" // IR(17014, 12)
  "RowMajorKHR\0" // IR(17026, 12)
  "ColumnMajorKHR\0" // IR(17038, 15)
  "RowBlockedInterleavedARM\0" // IR(17053, 25)
  "ColumnBlockedInterleavedARM\0" // IR(17078, 28)
  "NoneKHR\0" // IR(17106, 8)
  "MatrixASignedComponentsKHR\0" // IR(17114, 27)
  "MatrixBSignedComponentsKHR\0" // IR(17141, 27)
  "MatrixCSignedComponentsKHR\0" // IR(17168, 27)
  "MatrixResultSignedComponentsKHR\0" // IR(17195, 32)
  "SaturatingAccumulationKHR\0" // IR(17227, 26)
  "Row\0" // IR(17253, 4)
  "Column\0" // IR(17257, 7)
  "2x2\0" // IR(17264, 4)
  "MatrixAKHR\0" // IR(17268, 11)
  "MatrixBKHR\0" // IR(17279, 11)
  "MatrixAccumulatorKHR\0" // IR(17290, 21)
  "RowMajorNV\0" // IR(17311, 11)
  "ColumnMajorNV\0" // IR(17322, 14)
  "InferencingOptimalNV\0" // IR(17336, 21)
  "TrainingOptimalNV\0" // IR(17357, 18)
  "RelaxedPrecision\0" // IR(17375, 17)
  "SpecId\0" // IR(17392, 7)
  "Block\0" // IR(17399, 6)
  "BufferBlock\0" // IR(17405, 12)
  "RowMajor\0" // IR(17417, 9)
  "ColMajor\0" // IR(17426, 9)
  "ArrayStride\0" // IR(17435, 12)
  "MatrixStride\0" // IR(17447, 13)
  "GLSLShared\0" // IR(17460, 11)
  "GLSLPacked\0" // IR(17471, 11)
  "CPacked\0" // IR(17482, 8)
  "SPV_OPERAND_TYPE_BUILT_IN\0" // IR(17490, 26)
  "BuiltIn\0" // IR(17516, 8)
  "NoPerspective\0" // IR(17524, 14)
  "Flat\0" // IR(17538, 5)
  "Patch\0" // IR(17543, 6)
  "Centroid\0" // IR(17549, 9)
  "Sample\0" // IR(17558, 7)
  "Invariant\0" // IR(17565, 10)
  "Restrict\0" // IR(17575, 9)
  "Aliased\0" // IR(17584, 8)
  "Volatile\0" // IR(17592, 9)
  "Constant\0" // IR(17601, 9)
  "Coherent\0" // IR(17610, 9)
  "NonWritable\0" // IR(17619, 12)
  "NonReadable\0" // IR(17631, 12)
  "Uniform\0" // IR(17643, 8)
  "SPV_OPERAND_TYPE_SCOPE_ID\0" // IR(17651, 26)
  "UniformId\0" // IR(17677, 10)
  "SaturatedConversion\0" // IR(17687, 20)
  "Stream\0" // IR(17707, 7)
  "Location\0" // IR(17714, 9)
  "Component\0" // IR(17723, 10)
  "Index\0" // IR(17733, 6)
  "Binding\0" // IR(17739, 8)
  "DescriptorSet\0" // IR(17747, 14)
  "Offset\0" // IR(17761, 7)
  "XfbBuffer\0" // IR(17768, 10)
  "XfbStride\0" // IR(17778, 10)
  "SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE\0" // IR(17788, 46)
  "FuncParamAttr\0" // IR(17834, 14)
  "SPV_OPERAND_TYPE_FP_ROUNDING_MODE\0" // IR(17848, 34)
  "FPRoundingMode\0" // IR(17882, 15)
  "SPV_OPERAND_TYPE_FP_FAST_MATH_MODE\0" // IR(17897, 35)
  "FPFastMathMode\0" // IR(17932, 15)
  "SPV_OPERAND_TYPE_LITERAL_STRING\0" // IR(17947, 32)
  "SPV_OPERAND_TYPE_LINKAGE_TYPE\0" // IR(17979, 30)
  "LinkageAttributes\0" // IR(18009, 18)
  "NoContraction\0" // IR(18027, 14)
  "InputAttachmentIndex\0" // IR(18041, 21)
  "Alignment\0" // IR(18062, 10)
  "MaxByteOffset\0" // IR(18072, 14)
  "SPV_OPERAND_TYPE_ID\0" // IR(18086, 20)
  "AlignmentId\0" // IR(18106, 12)
  "MaxByteOffsetId\0" // IR(18118, 16)
  "SaturatedToLargestFloat8NormalConversionEXT\0" // IR(18134, 44)
  "NoSignedWrap\0" // IR(18178, 13)
  "NoUnsignedWrap\0" // IR(18191, 15)
  "WeightTextureQCOM\0" // IR(18206, 18)
  "BlockMatchTextureQCOM\0" // IR(18224, 22)
  "BlockMatchSamplerQCOM\0" // IR(18246, 22)
  "ExplicitInterpAMD\0" // IR(18268, 18)
  "NodeSharesPayloadLimitsWithAMDX\0" // IR(18286, 32)
  "NodeMaxPayloadsAMDX\0" // IR(18318, 20)
  "TrackFinishWritingAMDX\0" // IR(18338, 23)
  "PayloadNodeNameAMDX\0" // IR(18361, 20)
  "PayloadNodeBaseIndexAMDX\0" // IR(18381, 25)
  "PayloadNodeSparseArrayAMDX\0" // IR(18406, 27)
  "PayloadNodeArraySizeAMDX\0" // IR(18433, 25)
  "PayloadDispatchIndirectAMDX\0" // IR(18458, 28)
  "ArrayStrideIdEXT\0" // IR(18486, 17)
  "OffsetIdEXT\0" // IR(18503, 12)
  "UTFEncodedKHR\0" // IR(18515, 14)
  "OverrideCoverageNV\0" // IR(18529, 19)
  "PassthroughNV\0" // IR(18548, 14)
  "ViewportRelativeNV\0" // IR(18562, 19)
  "SecondaryViewportRelativeNV\0" // IR(18581, 28)
  "PerPrimitiveEXT\0" // IR(18609, 16)
  "PerPrimitiveNV\0" // IR(18625, 15)
  "PerViewNV\0" // IR(18640, 10)
  "PerTaskNV\0" // IR(18650, 10)
  "PerVertexKHR\0" // IR(18660, 13)
  "PerVertexNV\0" // IR(18673, 12)
  "NonUniform\0" // IR(18685, 11)
  "NonUniformEXT\0" // IR(18696, 14)
  "RestrictPointer\0" // IR(18710, 16)
  "RestrictPointerEXT\0" // IR(18726, 19)
  "AliasedPointer\0" // IR(18745, 15)
  "AliasedPointerEXT\0" // IR(18760, 18)
  "MemberOffsetNV\0" // IR(18778, 15)
  "HitObjectShaderRecordBufferNV\0" // IR(18793, 30)
  "HitObjectShaderRecordBufferEXT\0" // IR(18823, 31)
  "BankNV\0" // IR(18854, 7)
  "BindlessSamplerNV\0" // IR(18861, 18)
  "BindlessImageNV\0" // IR(18879, 16)
  "BoundSamplerNV\0" // IR(18895, 15)
  "BoundImageNV\0" // IR(18910, 13)
  "SIMTCallINTEL\0" // IR(18923, 14)
  "ReferencedIndirectlyINTEL\0" // IR(18937, 26)
  "ClobberINTEL\0" // IR(18963, 13)
  "SideEffectsINTEL\0" // IR(18976, 17)
  "VectorComputeVariableINTEL\0" // IR(18993, 27)
  "FuncParamIOKindINTEL\0" // IR(19020, 21)
  "VectorComputeFunctionINTEL\0" // IR(19041, 27)
  "StackCallINTEL\0" // IR(19068, 15)
  "GlobalVariableOffsetINTEL\0" // IR(19083, 26)
  "CounterBuffer\0" // IR(19109, 14)
  "HlslCounterBufferGOOGLE\0" // IR(19123, 24)
  "UserSemantic\0" // IR(19147, 13)
  "HlslSemanticGOOGLE\0" // IR(19160, 19)
  "UserTypeGOOGLE\0" // IR(19179, 15)
  "FunctionRoundingModeINTEL\0" // IR(19194, 26)
  "SPV_OPERAND_TYPE_FPDENORM_MODE\0" // IR(19220, 31)
  "FunctionDenormModeINTEL\0" // IR(19251, 24)
  "RegisterALTERA\0" // IR(19275, 15)
  "RegisterINTEL\0" // IR(19290, 14)
  "MemoryALTERA\0" // IR(19304, 13)
  "MemoryINTEL\0" // IR(19317, 12)
  "NumbanksALTERA\0" // IR(19329, 15)
  "NumbanksINTEL\0" // IR(19344, 14)
  "BankwidthALTERA\0" // IR(19358, 16)
  "BankwidthINTEL\0" // IR(19374, 15)
  "MaxPrivateCopiesALTERA\0" // IR(19389, 23)
  "MaxPrivateCopiesINTEL\0" // IR(19412, 22)
  "SinglepumpALTERA\0" // IR(19434, 17)
  "SinglepumpINTEL\0" // IR(19451, 16)
  "DoublepumpALTERA\0" // IR(19467, 17)
  "DoublepumpINTEL\0" // IR(19484, 16)
  "MaxReplicatesALTERA\0" // IR(19500, 20)
  "MaxReplicatesINTEL\0" // IR(19520, 19)
  "SimpleDualPortALTERA\0" // IR(19539, 21)
  "SimpleDualPortINTEL\0" // IR(19560, 20)
  "MergeALTERA\0" // IR(19580, 12)
  "MergeINTEL\0" // IR(19592, 11)
  "SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER\0" // IR(19603, 42)
  "BankBitsALTERA\0" // IR(19645, 15)
  "BankBitsINTEL\0" // IR(19660, 14)
  "ForcePow2DepthALTERA\0" // IR(19674, 21)
  "ForcePow2DepthINTEL\0" // IR(19695, 20)
  "StridesizeALTERA\0" // IR(19715, 17)
  "StridesizeINTEL\0" // IR(19732, 16)
  "WordsizeALTERA\0" // IR(19748, 15)
  "WordsizeINTEL\0" // IR(19763, 14)
  "TrueDualPortALTERA\0" // IR(19777, 19)
  "TrueDualPortINTEL\0" // IR(19796, 18)
  "BurstCoalesceALTERA\0" // IR(19814, 20)
  "BurstCoalesceINTEL\0" // IR(19834, 19)
  "CacheSizeALTERA\0" // IR(19853, 16)
  "CacheSizeINTEL\0" // IR(19869, 15)
  "DontStaticallyCoalesceALTERA\0" // IR(19884, 29)
  "DontStaticallyCoalesceINTEL\0" // IR(19913, 28)
  "PrefetchALTERA\0" // IR(19941, 15)
  "PrefetchINTEL\0" // IR(19956, 14)
  "StallEnableALTERA\0" // IR(19970, 18)
  "StallEnableINTEL\0" // IR(19988, 17)
  "FuseLoopsInFunctionALTERA\0" // IR(20005, 26)
  "FuseLoopsInFunctionINTEL\0" // IR(20031, 25)
  "MathOpDSPModeALTERA\0" // IR(20056, 20)
  "MathOpDSPModeINTEL\0" // IR(20076, 19)
  "AliasScopeINTEL\0" // IR(20095, 16)
  "NoAliasINTEL\0" // IR(20111, 13)
  "InitiationIntervalALTERA\0" // IR(20124, 25)
  "InitiationIntervalINTEL\0" // IR(20149, 24)
  "MaxConcurrencyALTERA\0" // IR(20173, 21)
  "MaxConcurrencyINTEL\0" // IR(20194, 20)
  "PipelineEnableALTERA\0" // IR(20214, 21)
  "PipelineEnableINTEL\0" // IR(20235, 20)
  "BufferLocationALTERA\0" // IR(20255, 21)
  "BufferLocationINTEL\0" // IR(20276, 20)
  "IOPipeStorageALTERA\0" // IR(20296, 20)
  "IOPipeStorageINTEL\0" // IR(20316, 19)
  "SPV_OPERAND_TYPE_FPOPERATION_MODE\0" // IR(20335, 34)
  "FunctionFloatingPointModeINTEL\0" // IR(20369, 31)
  "SingleElementVectorINTEL\0" // IR(20400, 25)
  "VectorComputeCallableFunctionINTEL\0" // IR(20425, 35)
  "MediaBlockIOINTEL\0" // IR(20460, 18)
  "StallFreeALTERA\0" // IR(20478, 16)
  "StallFreeINTEL\0" // IR(20494, 15)
  "SPV_OPERAND_TYPE_LITERAL_FLOAT\0" // IR(20509, 31)
  "FPMaxErrorDecorationINTEL\0" // IR(20540, 26)
  "LatencyControlLabelALTERA\0" // IR(20566, 26)
  "LatencyControlLabelINTEL\0" // IR(20592, 25)
  "LatencyControlConstraintALTERA\0" // IR(20617, 31)
  "LatencyControlConstraintINTEL\0" // IR(20648, 30)
  "ConduitKernelArgumentALTERA\0" // IR(20678, 28)
  "ConduitKernelArgumentINTEL\0" // IR(20706, 27)
  "RegisterMapKernelArgumentALTERA\0" // IR(20733, 32)
  "RegisterMapKernelArgumentINTEL\0" // IR(20765, 31)
  "MMHostInterfaceAddressWidthALTERA\0" // IR(20796, 34)
  "MMHostInterfaceAddressWidthINTEL\0" // IR(20830, 33)
  "MMHostInterfaceDataWidthALTERA\0" // IR(20863, 31)
  "MMHostInterfaceDataWidthINTEL\0" // IR(20894, 30)
  "MMHostInterfaceLatencyALTERA\0" // IR(20924, 29)
  "MMHostInterfaceLatencyINTEL\0" // IR(20953, 28)
  "SPV_OPERAND_TYPE_ACCESS_QUALIFIER\0" // IR(20981, 34)
  "MMHostInterfaceReadWriteModeALTERA\0" // IR(21015, 35)
  "MMHostInterfaceReadWriteModeINTEL\0" // IR(21050, 34)
  "MMHostInterfaceMaxBurstALTERA\0" // IR(21084, 30)
  "MMHostInterfaceMaxBurstINTEL\0" // IR(21114, 29)
  "MMHostInterfaceWaitRequestALTERA\0" // IR(21143, 33)
  "MMHostInterfaceWaitRequestINTEL\0" // IR(21176, 32)
  "StableKernelArgumentALTERA\0" // IR(21208, 27)
  "StableKernelArgumentINTEL\0" // IR(21235, 26)
  "SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER\0" // IR(21261, 39)
  "HostAccessINTEL\0" // IR(21300, 16)
  "SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER\0" // IR(21316, 47)
  "InitModeALTERA\0" // IR(21363, 15)
  "InitModeINTEL\0" // IR(21378, 14)
  "ImplementInRegisterMapALTERA\0" // IR(21392, 29)
  "ImplementInRegisterMapINTEL\0" // IR(21421, 28)
  "ConditionalINTEL\0" // IR(21449, 17)
  "SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL\0" // IR(21466, 36)
  "CacheControlLoadINTEL\0" // IR(21502, 22)
  "SPV_OPERAND_TYPE_STORE_CACHE_CONTROL\0" // IR(21524, 37)
  "CacheControlStoreINTEL\0" // IR(21561, 23)
  "1D\0" // IR(21584, 3)
  "2D\0" // IR(21587, 3)
  "3D\0" // IR(21590, 3)
  "Cube\0" // IR(21593, 5)
  "Rect\0" // IR(21598, 5)
  "Buffer\0" // IR(21603, 7)
  "SubpassData\0" // IR(21610, 12)
  "TileImageDataEXT\0" // IR(21622, 17)
  "Invocations\0" // IR(21639, 12)
  "SpacingEqual\0" // IR(21651, 13)
  "SpacingFractionalEven\0" // IR(21664, 22)
  "SpacingFractionalOdd\0" // IR(21686, 21)
  "VertexOrderCw\0" // IR(21707, 14)
  "VertexOrderCcw\0" // IR(21721, 15)
  "PixelCenterInteger\0" // IR(21736, 19)
  "OriginUpperLeft\0" // IR(21755, 16)
  "OriginLowerLeft\0" // IR(21771, 16)
  "EarlyFragmentTests\0" // IR(21787, 19)
  "PointMode\0" // IR(21806, 10)
  "Xfb\0" // IR(21816, 4)
  "DepthReplacing\0" // IR(21820, 15)
  "DepthGreater\0" // IR(21835, 13)
  "DepthLess\0" // IR(21848, 10)
  "DepthUnchanged\0" // IR(21858, 15)
  "LocalSize\0" // IR(21873, 10)
  "LocalSizeHint\0" // IR(21883, 14)
  "InputPoints\0" // IR(21897, 12)
  "InputLines\0" // IR(21909, 11)
  "InputLinesAdjacency\0" // IR(21920, 20)
  "Triangles\0" // IR(21940, 10)
  "InputTrianglesAdjacency\0" // IR(21950, 24)
  "Quads\0" // IR(21974, 6)
  "Isolines\0" // IR(21980, 9)
  "OutputVertices\0" // IR(21989, 15)
  "OutputPoints\0" // IR(22004, 13)
  "OutputLineStrip\0" // IR(22017, 16)
  "OutputTriangleStrip\0" // IR(22033, 20)
  "VecTypeHint\0" // IR(22053, 12)
  "ContractionOff\0" // IR(22065, 15)
  "Initializer\0" // IR(22080, 12)
  "Finalizer\0" // IR(22092, 10)
  "SubgroupsPerWorkgroup\0" // IR(22102, 22)
  "SubgroupsPerWorkgroupId\0" // IR(22124, 24)
  "LocalSizeId\0" // IR(22148, 12)
  "LocalSizeHintId\0" // IR(22160, 16)
  "NonCoherentColorAttachmentReadEXT\0" // IR(22176, 34)
  "NonCoherentDepthAttachmentReadEXT\0" // IR(22210, 34)
  "NonCoherentStencilAttachmentReadEXT\0" // IR(22244, 36)
  "SubgroupUniformControlFlowKHR\0" // IR(22280, 30)
  "PostDepthCoverage\0" // IR(22310, 18)
  "NonCoherentTileAttachmentReadQCOM\0" // IR(22328, 34)
  "TileShadingRateQCOM\0" // IR(22362, 20)
  "EarlyAndLateFragmentTestsAMD\0" // IR(22382, 29)
  "StencilRefReplacingEXT\0" // IR(22411, 23)
  "CoalescingAMDX\0" // IR(22434, 15)
  "IsApiEntryAMDX\0" // IR(22449, 15)
  "MaxNodeRecursionAMDX\0" // IR(22464, 21)
  "StaticNumWorkgroupsAMDX\0" // IR(22485, 24)
  "MaxNumWorkgroupsAMDX\0" // IR(22509, 21)
  "StencilRefUnchangedFrontAMD\0" // IR(22530, 28)
  "StencilRefGreaterFrontAMD\0" // IR(22558, 26)
  "StencilRefLessFrontAMD\0" // IR(22584, 23)
  "StencilRefUnchangedBackAMD\0" // IR(22607, 27)
  "StencilRefGreaterBackAMD\0" // IR(22634, 25)
  "StencilRefLessBackAMD\0" // IR(22659, 22)
  "QuadDerivativesKHR\0" // IR(22681, 19)
  "RequireFullQuadsKHR\0" // IR(22700, 20)
  "SharesInputWithAMDX\0" // IR(22720, 20)
  "ArithmeticPoisonKHR\0" // IR(22740, 20)
  "OutputLinesEXT\0" // IR(22760, 15)
  "OutputLinesNV\0" // IR(22775, 14)
  "OutputPrimitivesEXT\0" // IR(22789, 20)
  "OutputPrimitivesNV\0" // IR(22809, 19)
  "DerivativeGroupQuadsKHR\0" // IR(22828, 24)
  "DerivativeGroupQuadsNV\0" // IR(22852, 23)
  "DerivativeGroupLinearKHR\0" // IR(22875, 25)
  "DerivativeGroupLinearNV\0" // IR(22900, 24)
  "OutputTrianglesEXT\0" // IR(22924, 19)
  "OutputTrianglesNV\0" // IR(22943, 18)
  "PixelInterlockOrderedEXT\0" // IR(22961, 25)
  "PixelInterlockUnorderedEXT\0" // IR(22986, 27)
  "SampleInterlockOrderedEXT\0" // IR(23013, 26)
  "SampleInterlockUnorderedEXT\0" // IR(23039, 28)
  "ShadingRateInterlockOrderedEXT\0" // IR(23067, 31)
  "ShadingRateInterlockUnorderedEXT\0" // IR(23098, 33)
  "SharedLocalMemorySizeINTEL\0" // IR(23131, 27)
  "RoundingModeRTPINTEL\0" // IR(23158, 21)
  "RoundingModeRTNINTEL\0" // IR(23179, 21)
  "FloatingPointModeALTINTEL\0" // IR(23200, 26)
  "FloatingPointModeIEEEINTEL\0" // IR(23226, 27)
  "MaxWorkgroupSizeINTEL\0" // IR(23253, 22)
  "MaxWorkDimINTEL\0" // IR(23275, 16)
  "NoGlobalOffsetINTEL\0" // IR(23291, 20)
  "NumSIMDWorkitemsINTEL\0" // IR(23311, 22)
  "SchedulerTargetFmaxMhzINTEL\0" // IR(23333, 28)
  "MaximallyReconvergesKHR\0" // IR(23361, 24)
  "FPFastMathDefault\0" // IR(23385, 18)
  "OpacityMicromapIdKHR\0" // IR(23403, 21)
  "StreamingInterfaceINTEL\0" // IR(23424, 24)
  "RegisterMapInterfaceINTEL\0" // IR(23448, 26)
  "NamedBarrierCountINTEL\0" // IR(23474, 23)
  "MaximumRegistersINTEL\0" // IR(23497, 22)
  "MaximumRegistersIdINTEL\0" // IR(23519, 24)
  "SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS\0" // IR(23543, 51)
  "NamedMaximumRegistersINTEL\0" // IR(23594, 27)
  "Vertex\0" // IR(23621, 7)
  "TessellationControl\0" // IR(23628, 20)
  "TessellationEvaluation\0" // IR(23648, 23)
  "GLCompute\0" // IR(23671, 10)
  "TaskNV\0" // IR(23681, 7)
  "MeshNV\0" // IR(23688, 7)
  "RayGenerationKHR\0" // IR(23695, 17)
  "RayGenerationNV\0" // IR(23712, 16)
  "IntersectionKHR\0" // IR(23728, 16)
  "IntersectionNV\0" // IR(23744, 15)
  "AnyHitKHR\0" // IR(23759, 10)
  "AnyHitNV\0" // IR(23769, 9)
  "ClosestHitKHR\0" // IR(23778, 14)
  "ClosestHitNV\0" // IR(23792, 13)
  "MissKHR\0" // IR(23805, 8)
  "MissNV\0" // IR(23813, 7)
  "CallableKHR\0" // IR(23820, 12)
  "CallableNV\0" // IR(23832, 11)
  "TaskEXT\0" // IR(23843, 8)
  "MeshEXT\0" // IR(23851, 8)
  "Preserve\0" // IR(23859, 9)
  "FlushToZero\0" // IR(23868, 12)
  "BFloat16KHR\0" // IR(23880, 12)
  "Float8E4M3EXT\0" // IR(23892, 14)
  "Float8E5M2EXT\0" // IR(23906, 14)
  "IEEE\0" // IR(23920, 5)
  "ALT\0" // IR(23925, 4)
  "NotNaN\0" // IR(23929, 7)
  "NotInf\0" // IR(23936, 7)
  "NSZ\0" // IR(23943, 4)
  "AllowRecip\0" // IR(23947, 11)
  "Fast\0" // IR(23958, 5)
  "AllowContract\0" // IR(23963, 14)
  "AllowContractFastINTEL\0" // IR(23977, 23)
  "AllowReassoc\0" // IR(24000, 13)
  "AllowReassocINTEL\0" // IR(24013, 18)
  "AllowTransform\0" // IR(24031, 15)
  "RTE\0" // IR(24046, 4)
  "RTZ\0" // IR(24050, 4)
  "RTP\0" // IR(24054, 4)
  "RTN\0" // IR(24058, 4)
  "Vertical2Pixels\0" // IR(24062, 16)
  "Vertical4Pixels\0" // IR(24078, 16)
  "Horizontal2Pixels\0" // IR(24094, 18)
  "Horizontal4Pixels\0" // IR(24112, 18)
  "Inline\0" // IR(24130, 7)
  "DontInline\0" // IR(24137, 11)
  "Pure\0" // IR(24148, 5)
  "Const\0" // IR(24153, 6)
  "Zext\0" // IR(24159, 5)
  "Sext\0" // IR(24164, 5)
  "ByVal\0" // IR(24169, 6)
  "Sret\0" // IR(24175, 5)
  "NoAlias\0" // IR(24180, 8)
  "NoCapture\0" // IR(24188, 10)
  "NoWrite\0" // IR(24198, 8)
  "NoReadWrite\0" // IR(24206, 12)
  "RuntimeAlignedALTERA\0" // IR(24218, 21)
  "RuntimeAlignedINTEL\0" // IR(24239, 20)
  "Reduce\0" // IR(24259, 7)
  "InclusiveScan\0" // IR(24266, 14)
  "ExclusiveScan\0" // IR(24280, 14)
  "ClusteredReduce\0" // IR(24294, 16)
  "PartitionedReduceEXT\0" // IR(24310, 21)
  "PartitionedReduceNV\0" // IR(24331, 20)
  "PartitionedInclusiveScanEXT\0" // IR(24351, 28)
  "PartitionedInclusiveScanNV\0" // IR(24379, 27)
  "PartitionedExclusiveScanEXT\0" // IR(24406, 28)
  "PartitionedExclusiveScanNV\0" // IR(24434, 27)
  "NoneINTEL\0" // IR(24461, 10)
  "ReadINTEL\0" // IR(24471, 10)
  "WriteINTEL\0" // IR(24481, 11)
  "ReadWriteINTEL\0" // IR(24492, 15)
  "Bias\0" // IR(24507, 5)
  "Lod\0" // IR(24512, 4)
  "Grad\0" // IR(24516, 5)
  "ConstOffset\0" // IR(24521, 12)
  "ConstOffsets\0" // IR(24533, 13)
  "MakeTexelAvailable\0" // IR(24546, 19)
  "MakeTexelAvailableKHR\0" // IR(24565, 22)
  "MakeTexelVisible\0" // IR(24587, 17)
  "MakeTexelVisibleKHR\0" // IR(24604, 20)
  "NonPrivateTexel\0" // IR(24624, 16)
  "NonPrivateTexelKHR\0" // IR(24640, 19)
  "VolatileTexel\0" // IR(24659, 14)
  "VolatileTexelKHR\0" // IR(24673, 17)
  "SignExtend\0" // IR(24690, 11)
  "ZeroExtend\0" // IR(24701, 11)
  "Nontemporal\0" // IR(24712, 12)
  "Offsets\0" // IR(24724, 8)
  "SnormInt8\0" // IR(24732, 10)
  "SnormInt16\0" // IR(24742, 11)
  "UnormInt8\0" // IR(24753, 10)
  "UnormInt16\0" // IR(24763, 11)
  "UnormShort565\0" // IR(24774, 14)
  "UnormShort555\0" // IR(24788, 14)
  "UnormInt101010\0" // IR(24802, 15)
  "SignedInt8\0" // IR(24817, 11)
  "SignedInt16\0" // IR(24828, 12)
  "SignedInt32\0" // IR(24840, 12)
  "UnsignedInt8\0" // IR(24852, 13)
  "UnsignedInt16\0" // IR(24865, 14)
  "UnsignedInt32\0" // IR(24879, 14)
  "HalfFloat\0" // IR(24893, 10)
  "UnormInt24\0" // IR(24903, 11)
  "UnormInt101010_2\0" // IR(24914, 17)
  "UnormInt10X6EXT\0" // IR(24931, 16)
  "UnsignedIntRaw10EXT\0" // IR(24947, 20)
  "UnsignedIntRaw12EXT\0" // IR(24967, 20)
  "UnormInt2_101010EXT\0" // IR(24987, 20)
  "UnsignedInt10X6EXT\0" // IR(25007, 19)
  "UnsignedInt12X4EXT\0" // IR(25026, 19)
  "UnsignedInt14X2EXT\0" // IR(25045, 19)
  "UnormInt12X4EXT\0" // IR(25064, 16)
  "UnormInt14X2EXT\0" // IR(25080, 16)
  "R\0" // IR(25096, 2)
  "A\0" // IR(25098, 2)
  "RG\0" // IR(25100, 3)
  "RA\0" // IR(25103, 3)
  "RGB\0" // IR(25106, 4)
  "RGBA\0" // IR(25110, 5)
  "BGRA\0" // IR(25115, 5)
  "ARGB\0" // IR(25120, 5)
  "Intensity\0" // IR(25125, 10)
  "Luminance\0" // IR(25135, 10)
  "Rx\0" // IR(25145, 3)
  "RGx\0" // IR(25148, 4)
  "RGBx\0" // IR(25152, 5)
  "Depth\0" // IR(25157, 6)
  "DepthStencil\0" // IR(25163, 13)
  "sRGB\0" // IR(25176, 5)
  "sRGBx\0" // IR(25181, 6)
  "sRGBA\0" // IR(25187, 6)
  "sBGRA\0" // IR(25193, 6)
  "ABGR\0" // IR(25199, 5)
  "InitOnDeviceReprogramALTERA\0" // IR(25204, 28)
  "InitOnDeviceReprogramINTEL\0" // IR(25232, 27)
  "InitOnDeviceResetALTERA\0" // IR(25259, 24)
  "InitOnDeviceResetINTEL\0" // IR(25283, 23)
  "NoWait\0" // IR(25306, 7)
  "WaitKernel\0" // IR(25313, 11)
  "WaitWorkGroup\0" // IR(25324, 14)
  "CmdExecTime\0" // IR(25338, 12)
  "MayUsePrintf\0" // IR(25350, 13)
  "Export\0" // IR(25363, 7)
  "Import\0" // IR(25370, 7)
  "LinkOnceODR\0" // IR(25377, 12)
  "WeakAMD\0" // IR(25389, 8)
  "UncachedINTEL\0" // IR(25397, 14)
  "CachedINTEL\0" // IR(25411, 12)
  "StreamingINTEL\0" // IR(25423, 15)
  "InvalidateAfterReadINTEL\0" // IR(25438, 25)
  "ConstCachedINTEL\0" // IR(25463, 17)
  "Unroll\0" // IR(25480, 7)
  "DontUnroll\0" // IR(25487, 11)
  "DependencyInfinite\0" // IR(25498, 19)
  "DependencyLength\0" // IR(25517, 17)
  "MinIterations\0" // IR(25534, 14)
  "MaxIterations\0" // IR(25548, 14)
  "IterationMultiple\0" // IR(25562, 18)
  "PeelCount\0" // IR(25580, 10)
  "PartialCount\0" // IR(25590, 13)
  "DependencyArrayALTERA\0" // IR(25603, 22)
  "DependencyArrayINTEL\0" // IR(25625, 21)
  "LoopCoalesceALTERA\0" // IR(25646, 19)
  "LoopCoalesceINTEL\0" // IR(25665, 18)
  "MaxInterleavingALTERA\0" // IR(25683, 22)
  "MaxInterleavingINTEL\0" // IR(25705, 21)
  "SpeculatedIterationsALTERA\0" // IR(25726, 27)
  "SpeculatedIterationsINTEL\0" // IR(25753, 26)
  "NoFusionALTERA\0" // IR(25779, 15)
  "NoFusionINTEL\0" // IR(25794, 14)
  "LoopCountALTERA\0" // IR(25808, 16)
  "LoopCountINTEL\0" // IR(25824, 15)
  "MaxReinvocationDelayALTERA\0" // IR(25839, 27)
  "MaxReinvocationDelayINTEL\0" // IR(25866, 26)
  "MatrixASignedComponentsINTEL\0" // IR(25892, 29)
  "MatrixBSignedComponentsINTEL\0" // IR(25921, 29)
  "MatrixCBFloat16INTEL\0" // IR(25950, 21)
  "MatrixResultBFloat16INTEL\0" // IR(25971, 26)
  "MatrixAPackedInt8INTEL\0" // IR(25997, 23)
  "MatrixBPackedInt8INTEL\0" // IR(26020, 23)
  "MatrixAPackedInt4INTEL\0" // IR(26043, 23)
  "MatrixBPackedInt4INTEL\0" // IR(26066, 23)
  "MatrixATF32INTEL\0" // IR(26089, 17)
  "MatrixBTF32INTEL\0" // IR(26106, 17)
  "MatrixAPackedFloat16INTEL\0" // IR(26123, 26)
  "MatrixBPackedFloat16INTEL\0" // IR(26149, 26)
  "MatrixAPackedBFloat16INTEL\0" // IR(26175, 27)
  "MatrixBPackedBFloat16INTEL\0" // IR(26202, 27)
  "Aligned\0" // IR(26229, 8)
  "MakePointerAvailable\0" // IR(26237, 21)
  "MakePointerAvailableKHR\0" // IR(26258, 24)
  "MakePointerVisible\0" // IR(26282, 19)
  "MakePointerVisibleKHR\0" // IR(26301, 22)
  "NonPrivatePointer\0" // IR(26323, 18)
  "NonPrivatePointerKHR\0" // IR(26341, 21)
  "AliasScopeINTELMask\0" // IR(26362, 20)
  "NoAliasINTELMask\0" // IR(26382, 17)
  "Simple\0" // IR(26399, 7)
  "GLSL450\0" // IR(26406, 8)
  "OpenCL\0" // IR(26414, 7)
  "Vulkan\0" // IR(26421, 7)
  "VulkanKHR\0" // IR(26428, 10)
  "Relaxed\0" // IR(26438, 8)
  "Acquire\0" // IR(26446, 8)
  "Release\0" // IR(26454, 8)
  "AcquireRelease\0" // IR(26462, 15)
  "SequentiallyConsistent\0" // IR(26477, 23)
  "UniformMemory\0" // IR(26500, 14)
  "SubgroupMemory\0" // IR(26514, 15)
  "WorkgroupMemory\0" // IR(26529, 16)
  "CrossWorkgroupMemory\0" // IR(26545, 21)
  "AtomicCounterMemory\0" // IR(26566, 20)
  "ImageMemory\0" // IR(26586, 12)
  "OutputMemory\0" // IR(26598, 13)
  "OutputMemoryKHR\0" // IR(26611, 16)
  "MakeAvailable\0" // IR(26627, 14)
  "MakeAvailableKHR\0" // IR(26641, 17)
  "MakeVisible\0" // IR(26658, 12)
  "MakeVisibleKHR\0" // IR(26670, 15)
  "AutoINTEL\0" // IR(26685, 10)
  "WRAP\0" // IR(26695, 5)
  "SAT\0" // IR(26700, 4)
  "SAT_ZERO\0" // IR(26704, 9)
  "SAT_SYM\0" // IR(26713, 8)
  "PackedVectorFormat4x8Bit\0" // IR(26721, 25)
  "PackedVectorFormat4x8BitKHR\0" // IR(26746, 28)
  "TRN\0" // IR(26774, 4)
  "TRN_ZERO\0" // IR(26778, 9)
  "RND\0" // IR(26787, 4)
  "RND_ZERO\0" // IR(26791, 9)
  "RND_INF\0" // IR(26800, 8)
  "RND_MIN_INF\0" // IR(26808, 12)
  "RND_CONV\0" // IR(26820, 9)
  "RND_CONV_ODD\0" // IR(26829, 13)
  "RobustnessPerComponentNV\0" // IR(26842, 25)
  "RobustnessPerElementNV\0" // IR(26867, 23)
  "OpaqueKHR\0" // IR(26890, 10)
  "NoOpaqueKHR\0" // IR(26900, 12)
  "TerminateOnFirstHitKHR\0" // IR(26912, 23)
  "SkipClosestHitShaderKHR\0" // IR(26935, 24)
  "CullBackFacingTrianglesKHR\0" // IR(26959, 27)
  "CullFrontFacingTrianglesKHR\0" // IR(26986, 28)
  "CullOpaqueKHR\0" // IR(27014, 14)
  "CullNoOpaqueKHR\0" // IR(27028, 16)
  "SkipTrianglesKHR\0" // IR(27044, 17)
  "SkipBuiltinPrimitivesNV\0" // IR(27061, 24)
  "SkipAABBsKHR\0" // IR(27085, 13)
  "ForceOpacityMicromap2StateKHR\0" // IR(27098, 30)
  "ForceOpacityMicromap2StateEXT\0" // IR(27128, 30)
  "RayQueryCandidateIntersectionTriangleKHR\0" // IR(27158, 41)
  "RayQueryCandidateIntersectionAABBKHR\0" // IR(27199, 37)
  "RayQueryCommittedIntersectionNoneKHR\0" // IR(27236, 37)
  "RayQueryCommittedIntersectionTriangleKHR\0" // IR(27273, 41)
  "RayQueryCommittedIntersectionGeneratedKHR\0" // IR(27314, 42)
  "RayQueryCandidateIntersectionKHR\0" // IR(27356, 33)
  "RayQueryCommittedIntersectionKHR\0" // IR(27389, 33)
  "ClampToEdge\0" // IR(27422, 12)
  "Clamp\0" // IR(27434, 6)
  "Repeat\0" // IR(27440, 7)
  "RepeatMirrored\0" // IR(27447, 15)
  "Nearest\0" // IR(27462, 8)
  "Linear\0" // IR(27470, 7)
  "Unknown\0" // IR(27477, 8)
  "Rgba32f\0" // IR(27485, 8)
  "Rgba16f\0" // IR(27493, 8)
  "R32f\0" // IR(27501, 5)
  "Rgba8\0" // IR(27506, 6)
  "Rgba8Snorm\0" // IR(27512, 11)
  "Rg32f\0" // IR(27523, 6)
  "Rg16f\0" // IR(27529, 6)
  "R11fG11fB10f\0" // IR(27535, 13)
  "R16f\0" // IR(27548, 5)
  "Rgba16\0" // IR(27553, 7)
  "Rgb10A2\0" // IR(27560, 8)
  "Rg16\0" // IR(27568, 5)
  "Rg8\0" // IR(27573, 4)
  "R16\0" // IR(27577, 4)
  "R8\0" // IR(27581, 3)
  "Rgba16Snorm\0" // IR(27584, 12)
  "Rg16Snorm\0" // IR(27596, 10)
  "Rg8Snorm\0" // IR(27606, 9)
  "R16Snorm\0" // IR(27615, 9)
  "R8Snorm\0" // IR(27624, 8)
  "Rgba32i\0" // IR(27632, 8)
  "Rgba16i\0" // IR(27640, 8)
  "Rgba8i\0" // IR(27648, 7)
  "R32i\0" // IR(27655, 5)
  "Rg32i\0" // IR(27660, 6)
  "Rg16i\0" // IR(27666, 6)
  "Rg8i\0" // IR(27672, 5)
  "R16i\0" // IR(27677, 5)
  "R8i\0" // IR(27682, 4)
  "Rgba32ui\0" // IR(27686, 9)
  "Rgba16ui\0" // IR(27695, 9)
  "Rgba8ui\0" // IR(27704, 8)
  "R32ui\0" // IR(27712, 6)
  "Rgb10a2ui\0" // IR(27718, 10)
  "Rg32ui\0" // IR(27728, 7)
  "Rg16ui\0" // IR(27735, 7)
  "Rg8ui\0" // IR(27742, 6)
  "R16ui\0" // IR(27748, 6)
  "R8ui\0" // IR(27754, 5)
  "R64ui\0" // IR(27759, 6)
  "R64i\0" // IR(27765, 5)
  "CrossDevice\0" // IR(27770, 12)
  "Device\0" // IR(27782, 7)
  "Workgroup\0" // IR(27789, 10)
  "Subgroup\0" // IR(27799, 9)
  "Invocation\0" // IR(27808, 11)
  "QueueFamily\0" // IR(27819, 12)
  "QueueFamilyKHR\0" // IR(27831, 15)
  "ShaderCallKHR\0" // IR(27846, 14)
  "Flatten\0" // IR(27860, 8)
  "DontFlatten\0" // IR(27868, 12)
  "IdentifierPossibleDuplicates\0" // IR(27880, 29)
  "FlagUnknownPhysicalLayout\0" // IR(27909, 26)
  "ESSL\0" // IR(27935, 5)
  "GLSL\0" // IR(27940, 5)
  "OpenCL_C\0" // IR(27945, 9)
  "OpenCL_CPP\0" // IR(27954, 11)
  "HLSL\0" // IR(27965, 5)
  "CPP_for_OpenCL\0" // IR(27970, 15)
  "SYCL\0" // IR(27985, 5)
  "HERO_C\0" // IR(27990, 7)
  "NZSL\0" // IR(27997, 5)
  "WGSL\0" // IR(28002, 5)
  "Slang\0" // IR(28007, 6)
  "Zig\0" // IR(28013, 4)
  "Rust\0" // IR(28017, 5)
  "Pred\0" // IR(28022, 5)
  "UniformConstant\0" // IR(28027, 16)
  "Input\0" // IR(28043, 6)
  "Output\0" // IR(28049, 7)
  "CrossWorkgroup\0" // IR(28056, 15)
  "Private\0" // IR(28071, 8)
  "Function\0" // IR(28079, 9)
  "Generic\0" // IR(28088, 8)
  "PushConstant\0" // IR(28096, 13)
  "AtomicCounter\0" // IR(28109, 14)
  "Image\0" // IR(28123, 6)
  "StorageBuffer\0" // IR(28129, 14)
  "TileImageEXT\0" // IR(28143, 13)
  "TileAttachmentQCOM\0" // IR(28156, 19)
  "NodePayloadAMDX\0" // IR(28175, 16)
  "CallableDataKHR\0" // IR(28191, 16)
  "CallableDataNV\0" // IR(28207, 15)
  "IncomingCallableDataKHR\0" // IR(28222, 24)
  "IncomingCallableDataNV\0" // IR(28246, 23)
  "RayPayloadKHR\0" // IR(28269, 14)
  "RayPayloadNV\0" // IR(28283, 13)
  "HitAttributeKHR\0" // IR(28296, 16)
  "HitAttributeNV\0" // IR(28312, 15)
  "IncomingRayPayloadKHR\0" // IR(28327, 22)
  "IncomingRayPayloadNV\0" // IR(28349, 21)
  "ShaderRecordBufferKHR\0" // IR(28370, 22)
  "ShaderRecordBufferNV\0" // IR(28392, 21)
  "PhysicalStorageBuffer\0" // IR(28413, 22)
  "PhysicalStorageBufferEXT\0" // IR(28435, 25)
  "HitObjectAttributeNV\0" // IR(28460, 21)
  "TaskPayloadWorkgroupEXT\0" // IR(28481, 24)
  "HitObjectAttributeEXT\0" // IR(28505, 22)
  "CodeSectionINTEL\0" // IR(28527, 17)
  "DeviceOnlyALTERA\0" // IR(28544, 17)
  "DeviceOnlyINTEL\0" // IR(28561, 16)
  "HostOnlyALTERA\0" // IR(28577, 15)
  "HostOnlyINTEL\0" // IR(28592, 14)
  "WriteThroughINTEL\0" // IR(28606, 18)
  "WriteBackINTEL\0" // IR(28624, 15)
  "TensorView\0" // IR(28639, 11)
  "DecodeFunc\0" // IR(28650, 11)
  "DecodeVectorFunc\0" // IR(28661, 17)
  "Undefined\0" // IR(28678, 10)
  "NoneARM\0" // IR(28688, 8)
  "NontemporalARM\0" // IR(28696, 15)
  "OutOfBoundsValueARM\0" // IR(28711, 20)
  "MakeElementAvailableARM\0" // IR(28731, 24)
  "MakeElementVisibleARM\0" // IR(28755, 22)
  "NonPrivateElementARM\0" // IR(28777, 21)
  "Nop\0" // IR(28798, 4)
  "SPV_OPERAND_TYPE_TYPE_ID\0" // IR(28802, 25)
  "SPV_OPERAND_TYPE_RESULT_ID\0" // IR(28827, 27)
  "Undef\0" // IR(28854, 6)
  "SourceContinued\0" // IR(28860, 16)
  "SPV_OPERAND_TYPE_SOURCE_LANGUAGE\0" // IR(28876, 33)
  "SPV_OPERAND_TYPE_OPTIONAL_ID\0" // IR(28909, 29)
  "SPV_OPERAND_TYPE_OPTIONAL_LITERAL_STRING\0" // IR(28938, 41)
  "Source\0" // IR(28979, 7)
  "SourceExtension\0" // IR(28986, 16)
  "Name\0" // IR(29002, 5)
  "MemberName\0" // IR(29007, 11)
  "String\0" // IR(29018, 7)
  "Line\0" // IR(29025, 5)
  "Extension\0" // IR(29030, 10)
  "ExtInstImport\0" // IR(29040, 14)
  "SPV_OPERAND_TYPE_EXTENSION_INSTRUCTION_NUMBER\0" // IR(29054, 46)
  "ExtInst\0" // IR(29100, 8)
  "SPV_OPERAND_TYPE_ADDRESSING_MODEL\0" // IR(29108, 34)
  "SPV_OPERAND_TYPE_MEMORY_MODEL\0" // IR(29142, 30)
  "MemoryModel\0" // IR(29172, 12)
  "SPV_OPERAND_TYPE_EXECUTION_MODEL\0" // IR(29184, 33)
  "SPV_OPERAND_TYPE_VARIABLE_ID\0" // IR(29217, 29)
  "EntryPoint\0" // IR(29246, 11)
  "SPV_OPERAND_TYPE_EXECUTION_MODE\0" // IR(29257, 32)
  "ExecutionMode\0" // IR(29289, 14)
  "SPV_OPERAND_TYPE_CAPABILITY\0" // IR(29303, 28)
  "Capability\0" // IR(29331, 11)
  "TypeVoid\0" // IR(29342, 9)
  "TypeBool\0" // IR(29351, 9)
  "TypeInt\0" // IR(29360, 8)
  "SPV_OPERAND_TYPE_OPTIONAL_FPENCODING\0" // IR(29368, 37)
  "TypeFloat\0" // IR(29405, 10)
  "TypeVector\0" // IR(29415, 11)
  "TypeMatrix\0" // IR(29426, 11)
  "SPV_OPERAND_TYPE_DIMENSIONALITY\0" // IR(29437, 32)
  "SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT\0" // IR(29469, 38)
  "SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER\0" // IR(29507, 43)
  "TypeImage\0" // IR(29550, 10)
  "TypeSampler\0" // IR(29560, 12)
  "TypeSampledImage\0" // IR(29572, 17)
  "TypeArray\0" // IR(29589, 10)
  "TypeRuntimeArray\0" // IR(29599, 17)
  "TypeStruct\0" // IR(29616, 11)
  "TypeOpaque\0" // IR(29627, 11)
  "SPV_OPERAND_TYPE_STORAGE_CLASS\0" // IR(29638, 31)
  "TypePointer\0" // IR(29669, 12)
  "TypeFunction\0" // IR(29681, 13)
  "TypeEvent\0" // IR(29694, 10)
  "TypeDeviceEvent\0" // IR(29704, 16)
  "TypeReserveId\0" // IR(29720, 14)
  "TypeQueue\0" // IR(29734, 10)
  "TypePipe\0" // IR(29744, 9)
  "TypeForwardPointer\0" // IR(29753, 19)
  "ConstantTrue\0" // IR(29772, 13)
  "ConstantFalse\0" // IR(29785, 14)
  "SPV_OPERAND_TYPE_TYPED_LITERAL_NUMBER\0" // IR(29799, 38)
  "ConstantComposite\0" // IR(29837, 18)
  "SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE\0" // IR(29855, 41)
  "SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE\0" // IR(29896, 37)
  "ConstantSampler\0" // IR(29933, 16)
  "ConstantNull\0" // IR(29949, 13)
  "SpecConstantTrue\0" // IR(29962, 17)
  "SpecConstantFalse\0" // IR(29979, 18)
  "SpecConstant\0" // IR(29997, 13)
  "SpecConstantComposite\0" // IR(30010, 22)
  "SPV_OPERAND_TYPE_SPEC_CONSTANT_OP_NUMBER\0" // IR(30032, 41)
  "SpecConstantOp\0" // IR(30073, 15)
  "SPV_OPERAND_TYPE_FUNCTION_CONTROL\0" // IR(30088, 34)
  "FunctionParameter\0" // IR(30122, 18)
  "FunctionEnd\0" // IR(30140, 12)
  "FunctionCall\0" // IR(30152, 13)
  "Variable\0" // IR(30165, 9)
  "ImageTexelPointer\0" // IR(30174, 18)
  "SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS\0" // IR(30192, 40)
  "Load\0" // IR(30232, 5)
  "Store\0" // IR(30237, 6)
  "CopyMemory\0" // IR(30243, 11)
  "CopyMemorySized\0" // IR(30254, 16)
  "AccessChain\0" // IR(30270, 12)
  "InBoundsAccessChain\0" // IR(30282, 20)
  "PtrAccessChain\0" // IR(30302, 15)
  "ArrayLength\0" // IR(30317, 12)
  "GenericPtrMemSemantics\0" // IR(30329, 23)
  "InBoundsPtrAccessChain\0" // IR(30352, 23)
  "SPV_OPERAND_TYPE_DECORATION\0" // IR(30375, 28)
  "Decorate\0" // IR(30403, 9)
  "MemberDecorate\0" // IR(30412, 15)
  "DecorationGroup\0" // IR(30427, 16)
  "GroupDecorate\0" // IR(30443, 14)
  "SPV_OPERAND_TYPE_VARIABLE_ID_LITERAL_INTEGER\0" // IR(30457, 45)
  "GroupMemberDecorate\0" // IR(30502, 20)
  "VectorExtractDynamic\0" // IR(30522, 21)
  "VectorInsertDynamic\0" // IR(30543, 20)
  "VectorShuffle\0" // IR(30563, 14)
  "CompositeConstruct\0" // IR(30577, 19)
  "CompositeExtract\0" // IR(30596, 17)
  "CompositeInsert\0" // IR(30613, 16)
  "CopyObject\0" // IR(30629, 11)
  "Transpose\0" // IR(30640, 10)
  "SampledImage\0" // IR(30650, 13)
  "SPV_OPERAND_TYPE_OPTIONAL_IMAGE\0" // IR(30663, 32)
  "ImageSampleImplicitLod\0" // IR(30695, 23)
  "SPV_OPERAND_TYPE_IMAGE\0" // IR(30718, 23)
  "ImageSampleExplicitLod\0" // IR(30741, 23)
  "ImageSampleDrefImplicitLod\0" // IR(30764, 27)
  "ImageSampleDrefExplicitLod\0" // IR(30791, 27)
  "ImageSampleProjImplicitLod\0" // IR(30818, 27)
  "ImageSampleProjExplicitLod\0" // IR(30845, 27)
  "ImageSampleProjDrefImplicitLod\0" // IR(30872, 31)
  "ImageSampleProjDrefExplicitLod\0" // IR(30903, 31)
  "ImageFetch\0" // IR(30934, 11)
  "ImageGather\0" // IR(30945, 12)
  "ImageDrefGather\0" // IR(30957, 16)
  "ImageRead\0" // IR(30973, 10)
  "ImageWrite\0" // IR(30983, 11)
  "ImageQueryFormat\0" // IR(30994, 17)
  "ImageQueryOrder\0" // IR(31011, 16)
  "ImageQuerySizeLod\0" // IR(31027, 18)
  "ImageQuerySize\0" // IR(31045, 15)
  "ImageQueryLod\0" // IR(31060, 14)
  "ImageQueryLevels\0" // IR(31074, 17)
  "ImageQuerySamples\0" // IR(31091, 18)
  "ConvertFToU\0" // IR(31109, 12)
  "ConvertFToS\0" // IR(31121, 12)
  "ConvertSToF\0" // IR(31133, 12)
  "ConvertUToF\0" // IR(31145, 12)
  "UConvert\0" // IR(31157, 9)
  "SConvert\0" // IR(31166, 9)
  "FConvert\0" // IR(31175, 9)
  "QuantizeToF16\0" // IR(31184, 14)
  "ConvertPtrToU\0" // IR(31198, 14)
  "SatConvertSToU\0" // IR(31212, 15)
  "SatConvertUToS\0" // IR(31227, 15)
  "ConvertUToPtr\0" // IR(31242, 14)
  "PtrCastToGeneric\0" // IR(31256, 17)
  "GenericCastToPtr\0" // IR(31273, 17)
  "GenericCastToPtrExplicit\0" // IR(31290, 25)
  "Bitcast\0" // IR(31315, 8)
  "SNegate\0" // IR(31323, 8)
  "FNegate\0" // IR(31331, 8)
  "IAdd\0" // IR(31339, 5)
  "FAdd\0" // IR(31344, 5)
  "ISub\0" // IR(31349, 5)
  "FSub\0" // IR(31354, 5)
  "IMul\0" // IR(31359, 5)
  "FMul\0" // IR(31364, 5)
  "UDiv\0" // IR(31369, 5)
  "SDiv\0" // IR(31374, 5)
  "FDiv\0" // IR(31379, 5)
  "UMod\0" // IR(31384, 5)
  "SRem\0" // IR(31389, 5)
  "SMod\0" // IR(31394, 5)
  "FRem\0" // IR(31399, 5)
  "FMod\0" // IR(31404, 5)
  "VectorTimesScalar\0" // IR(31409, 18)
  "MatrixTimesScalar\0" // IR(31427, 18)
  "VectorTimesMatrix\0" // IR(31445, 18)
  "MatrixTimesVector\0" // IR(31463, 18)
  "MatrixTimesMatrix\0" // IR(31481, 18)
  "OuterProduct\0" // IR(31499, 13)
  "Dot\0" // IR(31512, 4)
  "IAddCarry\0" // IR(31516, 10)
  "ISubBorrow\0" // IR(31526, 11)
  "UMulExtended\0" // IR(31537, 13)
  "SMulExtended\0" // IR(31550, 13)
  "Any\0" // IR(31563, 4)
  "All\0" // IR(31567, 4)
  "IsNan\0" // IR(31571, 6)
  "IsInf\0" // IR(31577, 6)
  "IsFinite\0" // IR(31583, 9)
  "IsNormal\0" // IR(31592, 9)
  "SignBitSet\0" // IR(31601, 11)
  "LessOrGreater\0" // IR(31612, 14)
  "Ordered\0" // IR(31626, 8)
  "Unordered\0" // IR(31634, 10)
  "LogicalEqual\0" // IR(31644, 13)
  "LogicalNotEqual\0" // IR(31657, 16)
  "LogicalOr\0" // IR(31673, 10)
  "LogicalAnd\0" // IR(31683, 11)
  "LogicalNot\0" // IR(31694, 11)
  "Select\0" // IR(31705, 7)
  "IEqual\0" // IR(31712, 7)
  "INotEqual\0" // IR(31719, 10)
  "UGreaterThan\0" // IR(31729, 13)
  "SGreaterThan\0" // IR(31742, 13)
  "UGreaterThanEqual\0" // IR(31755, 18)
  "SGreaterThanEqual\0" // IR(31773, 18)
  "ULessThan\0" // IR(31791, 10)
  "SLessThan\0" // IR(31801, 10)
  "ULessThanEqual\0" // IR(31811, 15)
  "SLessThanEqual\0" // IR(31826, 15)
  "FOrdEqual\0" // IR(31841, 10)
  "FUnordEqual\0" // IR(31851, 12)
  "FOrdNotEqual\0" // IR(31863, 13)
  "FUnordNotEqual\0" // IR(31876, 15)
  "FOrdLessThan\0" // IR(31891, 13)
  "FUnordLessThan\0" // IR(31904, 15)
  "FOrdGreaterThan\0" // IR(31919, 16)
  "FUnordGreaterThan\0" // IR(31935, 18)
  "FOrdLessThanEqual\0" // IR(31953, 18)
  "FUnordLessThanEqual\0" // IR(31971, 20)
  "FOrdGreaterThanEqual\0" // IR(31991, 21)
  "FUnordGreaterThanEqual\0" // IR(32012, 23)
  "ShiftRightLogical\0" // IR(32035, 18)
  "ShiftRightArithmetic\0" // IR(32053, 21)
  "ShiftLeftLogical\0" // IR(32074, 17)
  "BitwiseOr\0" // IR(32091, 10)
  "BitwiseXor\0" // IR(32101, 11)
  "BitwiseAnd\0" // IR(32112, 11)
  "Not\0" // IR(32123, 4)
  "BitFieldInsert\0" // IR(32127, 15)
  "BitFieldSExtract\0" // IR(32142, 17)
  "BitFieldUExtract\0" // IR(32159, 17)
  "BitReverse\0" // IR(32176, 11)
  "BitCount\0" // IR(32187, 9)
  "DPdx\0" // IR(32196, 5)
  "DPdy\0" // IR(32201, 5)
  "Fwidth\0" // IR(32206, 7)
  "DPdxFine\0" // IR(32213, 9)
  "DPdyFine\0" // IR(32222, 9)
  "FwidthFine\0" // IR(32231, 11)
  "DPdxCoarse\0" // IR(32242, 11)
  "DPdyCoarse\0" // IR(32253, 11)
  "FwidthCoarse\0" // IR(32264, 13)
  "EmitVertex\0" // IR(32277, 11)
  "EndPrimitive\0" // IR(32288, 13)
  "EmitStreamVertex\0" // IR(32301, 17)
  "EndStreamPrimitive\0" // IR(32318, 19)
  "SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID\0" // IR(32337, 37)
  "ControlBarrier\0" // IR(32374, 15)
  "MemoryBarrier\0" // IR(32389, 14)
  "AtomicLoad\0" // IR(32403, 11)
  "AtomicStore\0" // IR(32414, 12)
  "AtomicExchange\0" // IR(32426, 15)
  "AtomicCompareExchange\0" // IR(32441, 22)
  "AtomicCompareExchangeWeak\0" // IR(32463, 26)
  "AtomicIIncrement\0" // IR(32489, 17)
  "AtomicIDecrement\0" // IR(32506, 17)
  "AtomicIAdd\0" // IR(32523, 11)
  "AtomicISub\0" // IR(32534, 11)
  "AtomicSMin\0" // IR(32545, 11)
  "AtomicUMin\0" // IR(32556, 11)
  "AtomicSMax\0" // IR(32567, 11)
  "AtomicUMax\0" // IR(32578, 11)
  "AtomicAnd\0" // IR(32589, 10)
  "AtomicOr\0" // IR(32599, 9)
  "AtomicXor\0" // IR(32608, 10)
  "Phi\0" // IR(32618, 4)
  "SPV_OPERAND_TYPE_LOOP_CONTROL\0" // IR(32622, 30)
  "LoopMerge\0" // IR(32652, 10)
  "SPV_OPERAND_TYPE_SELECTION_CONTROL\0" // IR(32662, 35)
  "SelectionMerge\0" // IR(32697, 15)
  "Label\0" // IR(32712, 6)
  "Branch\0" // IR(32718, 7)
  "BranchConditional\0" // IR(32725, 18)
  "SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER_ID\0" // IR(32743, 45)
  "Switch\0" // IR(32788, 7)
  "Kill\0" // IR(32795, 5)
  "Return\0" // IR(32800, 7)
  "ReturnValue\0" // IR(32807, 12)
  "Unreachable\0" // IR(32819, 12)
  "LifetimeStart\0" // IR(32831, 14)
  "LifetimeStop\0" // IR(32845, 13)
  "GroupAsyncCopy\0" // IR(32858, 15)
  "GroupWaitEvents\0" // IR(32873, 16)
  "GroupAll\0" // IR(32889, 9)
  "GroupAny\0" // IR(32898, 9)
  "GroupBroadcast\0" // IR(32907, 15)
  "SPV_OPERAND_TYPE_GROUP_OPERATION\0" // IR(32922, 33)
  "GroupIAdd\0" // IR(32955, 10)
  "GroupFAdd\0" // IR(32965, 10)
  "GroupFMin\0" // IR(32975, 10)
  "GroupUMin\0" // IR(32985, 10)
  "GroupSMin\0" // IR(32995, 10)
  "GroupFMax\0" // IR(33005, 10)
  "GroupUMax\0" // IR(33015, 10)
  "GroupSMax\0" // IR(33025, 10)
  "ReadPipe\0" // IR(33035, 9)
  "WritePipe\0" // IR(33044, 10)
  "ReservedReadPipe\0" // IR(33054, 17)
  "ReservedWritePipe\0" // IR(33071, 18)
  "ReserveReadPipePackets\0" // IR(33089, 23)
  "ReserveWritePipePackets\0" // IR(33112, 24)
  "CommitReadPipe\0" // IR(33136, 15)
  "CommitWritePipe\0" // IR(33151, 16)
  "IsValidReserveId\0" // IR(33167, 17)
  "GetNumPipePackets\0" // IR(33184, 18)
  "GetMaxPipePackets\0" // IR(33202, 18)
  "GroupReserveReadPipePackets\0" // IR(33220, 28)
  "GroupReserveWritePipePackets\0" // IR(33248, 29)
  "GroupCommitReadPipe\0" // IR(33277, 20)
  "GroupCommitWritePipe\0" // IR(33297, 21)
  "EnqueueMarker\0" // IR(33318, 14)
  "EnqueueKernel\0" // IR(33332, 14)
  "GetKernelNDrangeSubGroupCount\0" // IR(33346, 30)
  "GetKernelNDrangeMaxSubGroupSize\0" // IR(33376, 32)
  "GetKernelWorkGroupSize\0" // IR(33408, 23)
  "GetKernelPreferredWorkGroupSizeMultiple\0" // IR(33431, 40)
  "RetainEvent\0" // IR(33471, 12)
  "ReleaseEvent\0" // IR(33483, 13)
  "CreateUserEvent\0" // IR(33496, 16)
  "IsValidEvent\0" // IR(33512, 13)
  "SetUserEventStatus\0" // IR(33525, 19)
  "CaptureEventProfilingInfo\0" // IR(33544, 26)
  "GetDefaultQueue\0" // IR(33570, 16)
  "BuildNDRange\0" // IR(33586, 13)
  "ImageSparseSampleImplicitLod\0" // IR(33599, 29)
  "ImageSparseSampleExplicitLod\0" // IR(33628, 29)
  "ImageSparseSampleDrefImplicitLod\0" // IR(33657, 33)
  "ImageSparseSampleDrefExplicitLod\0" // IR(33690, 33)
  "ImageSparseSampleProjImplicitLod\0" // IR(33723, 33)
  "ImageSparseSampleProjExplicitLod\0" // IR(33756, 33)
  "ImageSparseSampleProjDrefImplicitLod\0" // IR(33789, 37)
  "ImageSparseSampleProjDrefExplicitLod\0" // IR(33826, 37)
  "ImageSparseFetch\0" // IR(33863, 17)
  "ImageSparseGather\0" // IR(33880, 18)
  "ImageSparseDrefGather\0" // IR(33898, 22)
  "ImageSparseTexelsResident\0" // IR(33920, 26)
  "NoLine\0" // IR(33946, 7)
  "AtomicFlagTestAndSet\0" // IR(33953, 21)
  "AtomicFlagClear\0" // IR(33974, 16)
  "ImageSparseRead\0" // IR(33990, 16)
  "SizeOf\0" // IR(34006, 7)
  "TypePipeStorage\0" // IR(34013, 16)
  "ConstantPipeStorage\0" // IR(34029, 20)
  "CreatePipeFromPipeStorage\0" // IR(34049, 26)
  "GetKernelLocalSizeForSubgroupCount\0" // IR(34075, 35)
  "GetKernelMaxNumSubgroups\0" // IR(34110, 25)
  "TypeNamedBarrier\0" // IR(34135, 17)
  "NamedBarrierInitialize\0" // IR(34152, 23)
  "MemoryNamedBarrier\0" // IR(34175, 19)
  "ModuleProcessed\0" // IR(34194, 16)
  "ExecutionModeId\0" // IR(34210, 16)
  "DecorateId\0" // IR(34226, 11)
  "GroupNonUniformElect\0" // IR(34237, 21)
  "GroupNonUniformAll\0" // IR(34258, 19)
  "GroupNonUniformAny\0" // IR(34277, 19)
  "GroupNonUniformAllEqual\0" // IR(34296, 24)
  "GroupNonUniformBroadcast\0" // IR(34320, 25)
  "GroupNonUniformBroadcastFirst\0" // IR(34345, 30)
  "GroupNonUniformInverseBallot\0" // IR(34375, 29)
  "GroupNonUniformBallotBitExtract\0" // IR(34404, 32)
  "GroupNonUniformBallotBitCount\0" // IR(34436, 30)
  "GroupNonUniformBallotFindLSB\0" // IR(34466, 29)
  "GroupNonUniformBallotFindMSB\0" // IR(34495, 29)
  "GroupNonUniformShuffleXor\0" // IR(34524, 26)
  "GroupNonUniformShuffleUp\0" // IR(34550, 25)
  "GroupNonUniformShuffleDown\0" // IR(34575, 27)
  "GroupNonUniformIAdd\0" // IR(34602, 20)
  "GroupNonUniformFAdd\0" // IR(34622, 20)
  "GroupNonUniformIMul\0" // IR(34642, 20)
  "GroupNonUniformFMul\0" // IR(34662, 20)
  "GroupNonUniformSMin\0" // IR(34682, 20)
  "GroupNonUniformUMin\0" // IR(34702, 20)
  "GroupNonUniformFMin\0" // IR(34722, 20)
  "GroupNonUniformSMax\0" // IR(34742, 20)
  "GroupNonUniformUMax\0" // IR(34762, 20)
  "GroupNonUniformFMax\0" // IR(34782, 20)
  "GroupNonUniformBitwiseAnd\0" // IR(34802, 26)
  "GroupNonUniformBitwiseOr\0" // IR(34828, 25)
  "GroupNonUniformBitwiseXor\0" // IR(34853, 26)
  "GroupNonUniformLogicalAnd\0" // IR(34879, 26)
  "GroupNonUniformLogicalOr\0" // IR(34905, 25)
  "GroupNonUniformLogicalXor\0" // IR(34930, 26)
  "GroupNonUniformQuadBroadcast\0" // IR(34956, 29)
  "GroupNonUniformQuadSwap\0" // IR(34985, 24)
  "CopyLogical\0" // IR(35009, 12)
  "PtrEqual\0" // IR(35021, 9)
  "PtrNotEqual\0" // IR(35030, 12)
  "PtrDiff\0" // IR(35042, 8)
  "ColorAttachmentReadEXT\0" // IR(35050, 23)
  "DepthAttachmentReadEXT\0" // IR(35073, 23)
  "StencilAttachmentReadEXT\0" // IR(35096, 25)
  "TypeTensorARM\0" // IR(35121, 14)
  "SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS\0" // IR(35135, 42)
  "TensorReadARM\0" // IR(35177, 14)
  "TensorWriteARM\0" // IR(35191, 15)
  "TensorQuerySizeARM\0" // IR(35206, 19)
  "GraphConstantARM\0" // IR(35225, 17)
  "GraphEntryPointARM\0" // IR(35242, 19)
  "GraphInputARM\0" // IR(35261, 14)
  "GraphSetOutputARM\0" // IR(35275, 18)
  "GraphEndARM\0" // IR(35293, 12)
  "TypeGraphARM\0" // IR(35305, 13)
  "TerminateInvocation\0" // IR(35318, 20)
  "TypeUntypedPointerKHR\0" // IR(35338, 22)
  "UntypedVariableKHR\0" // IR(35360, 19)
  "UntypedAccessChainKHR\0" // IR(35379, 22)
  "UntypedInBoundsAccessChainKHR\0" // IR(35401, 30)
  "SubgroupFirstInvocationKHR\0" // IR(35431, 27)
  "UntypedPtrAccessChainKHR\0" // IR(35458, 25)
  "UntypedInBoundsPtrAccessChainKHR\0" // IR(35483, 33)
  "UntypedArrayLengthKHR\0" // IR(35516, 22)
  "UntypedPrefetchKHR\0" // IR(35538, 19)
  "FmaKHR\0" // IR(35557, 7)
  "SubgroupAllKHR\0" // IR(35564, 15)
  "SubgroupAnyKHR\0" // IR(35579, 15)
  "SubgroupAllEqualKHR\0" // IR(35594, 20)
  "SubgroupReadInvocationKHR\0" // IR(35614, 26)
  "ExtInstWithForwardRefsKHR\0" // IR(35640, 26)
  "UntypedGroupAsyncCopyKHR\0" // IR(35666, 25)
  "TraceRayKHR\0" // IR(35691, 12)
  "ExecuteCallableKHR\0" // IR(35703, 19)
  "ConvertUToAccelerationStructureKHR\0" // IR(35722, 35)
  "IgnoreIntersectionKHR\0" // IR(35757, 22)
  "TerminateRayKHR\0" // IR(35779, 16)
  "SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT\0" // IR(35795, 47)
  "SDot\0" // IR(35842, 5)
  "SDotKHR\0" // IR(35847, 8)
  "UDot\0" // IR(35855, 5)
  "UDotKHR\0" // IR(35860, 8)
  "SUDot\0" // IR(35868, 6)
  "SUDotKHR\0" // IR(35874, 9)
  "SDotAccSat\0" // IR(35883, 11)
  "SDotAccSatKHR\0" // IR(35894, 14)
  "UDotAccSat\0" // IR(35908, 11)
  "UDotAccSatKHR\0" // IR(35919, 14)
  "SUDotAccSat\0" // IR(35933, 12)
  "SUDotAccSatKHR\0" // IR(35945, 15)
  "TypeCooperativeMatrixKHR\0" // IR(35960, 25)
  "CooperativeMatrixLoadKHR\0" // IR(35985, 25)
  "CooperativeMatrixStoreKHR\0" // IR(36010, 26)
  "SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS\0" // IR(36036, 54)
  "CooperativeMatrixMulAddKHR\0" // IR(36090, 27)
  "CooperativeMatrixLengthKHR\0" // IR(36117, 27)
  "ConstantCompositeReplicateEXT\0" // IR(36144, 30)
  "SpecConstantCompositeReplicateEXT\0" // IR(36174, 34)
  "CompositeConstructReplicateEXT\0" // IR(36208, 31)
  "TypeRayQueryKHR\0" // IR(36239, 16)
  "RayQueryInitializeKHR\0" // IR(36255, 22)
  "RayQueryTerminateKHR\0" // IR(36277, 21)
  "RayQueryGenerateIntersectionKHR\0" // IR(36298, 32)
  "RayQueryConfirmIntersectionKHR\0" // IR(36330, 31)
  "RayQueryProceedKHR\0" // IR(36361, 19)
  "RayQueryGetIntersectionTypeKHR\0" // IR(36380, 31)
  "ImageSampleWeightedQCOM\0" // IR(36411, 24)
  "ImageBoxFilterQCOM\0" // IR(36435, 19)
  "ImageBlockMatchSSDQCOM\0" // IR(36454, 23)
  "ImageBlockMatchSADQCOM\0" // IR(36477, 23)
  "BitCastArrayQCOM\0" // IR(36500, 17)
  "ImageBlockMatchWindowSSDQCOM\0" // IR(36517, 29)
  "ImageBlockMatchWindowSADQCOM\0" // IR(36546, 29)
  "ImageBlockMatchGatherSSDQCOM\0" // IR(36575, 29)
  "ImageBlockMatchGatherSADQCOM\0" // IR(36604, 29)
  "CompositeConstructCoopMatQCOM\0" // IR(36633, 30)
  "CompositeExtractCoopMatQCOM\0" // IR(36663, 28)
  "ExtractSubArrayQCOM\0" // IR(36691, 20)
  "GroupIAddNonUniformAMD\0" // IR(36711, 23)
  "GroupFAddNonUniformAMD\0" // IR(36734, 23)
  "GroupFMinNonUniformAMD\0" // IR(36757, 23)
  "GroupUMinNonUniformAMD\0" // IR(36780, 23)
  "GroupSMinNonUniformAMD\0" // IR(36803, 23)
  "GroupFMaxNonUniformAMD\0" // IR(36826, 23)
  "GroupUMaxNonUniformAMD\0" // IR(36849, 23)
  "GroupSMaxNonUniformAMD\0" // IR(36872, 23)
  "FragmentMaskFetchAMD\0" // IR(36895, 21)
  "FragmentFetchAMD\0" // IR(36916, 17)
  "ReadClockKHR\0" // IR(36933, 13)
  "AllocateNodePayloadsAMDX\0" // IR(36946, 25)
  "EnqueueNodePayloadsAMDX\0" // IR(36971, 24)
  "TypeNodePayloadArrayAMDX\0" // IR(36995, 25)
  "FinishWritingNodePayloadAMDX\0" // IR(37020, 29)
  "NodePayloadArrayLengthAMDX\0" // IR(37049, 27)
  "IsNodePayloadValidAMDX\0" // IR(37076, 23)
  "ConstantStringAMDX\0" // IR(37099, 19)
  "SpecConstantStringAMDX\0" // IR(37118, 23)
  "GroupNonUniformQuadAllKHR\0" // IR(37141, 26)
  "GroupNonUniformQuadAnyKHR\0" // IR(37167, 26)
  "TypeBufferEXT\0" // IR(37193, 14)
  "BufferPointerEXT\0" // IR(37207, 17)
  "UntypedImageTexelPointerEXT\0" // IR(37224, 28)
  "MemberDecorateIdEXT\0" // IR(37252, 20)
  "ConstantSizeOfEXT\0" // IR(37272, 18)
  "SpecConstantDataKHR\0" // IR(37290, 20)
  "PoisonKHR\0" // IR(37310, 10)
  "FreezeKHR\0" // IR(37320, 10)
  "HitObjectRecordHitMotionNV\0" // IR(37330, 27)
  "HitObjectRecordHitWithIndexMotionNV\0" // IR(37357, 36)
  "HitObjectRecordMissMotionNV\0" // IR(37393, 28)
  "HitObjectGetWorldToObjectNV\0" // IR(37421, 28)
  "HitObjectGetObjectToWorldNV\0" // IR(37449, 28)
  "HitObjectGetObjectRayDirectionNV\0" // IR(37477, 33)
  "HitObjectGetObjectRayOriginNV\0" // IR(37510, 30)
  "HitObjectTraceRayMotionNV\0" // IR(37540, 26)
  "HitObjectGetShaderRecordBufferHandleNV\0" // IR(37566, 39)
  "HitObjectGetShaderBindingTableRecordIndexNV\0" // IR(37605, 44)
  "HitObjectRecordEmptyNV\0" // IR(37649, 23)
  "HitObjectTraceRayNV\0" // IR(37672, 20)
  "HitObjectRecordHitNV\0" // IR(37692, 21)
  "HitObjectRecordHitWithIndexNV\0" // IR(37713, 30)
  "HitObjectRecordMissNV\0" // IR(37743, 22)
  "HitObjectExecuteShaderNV\0" // IR(37765, 25)
  "HitObjectGetCurrentTimeNV\0" // IR(37790, 26)
  "HitObjectGetAttributesNV\0" // IR(37816, 25)
  "HitObjectGetHitKindNV\0" // IR(37841, 22)
  "HitObjectGetPrimitiveIndexNV\0" // IR(37863, 29)
  "HitObjectGetGeometryIndexNV\0" // IR(37892, 28)
  "HitObjectGetInstanceIdNV\0" // IR(37920, 25)
  "HitObjectGetInstanceCustomIndexNV\0" // IR(37945, 34)
  "HitObjectGetWorldRayDirectionNV\0" // IR(37979, 32)
  "HitObjectGetWorldRayOriginNV\0" // IR(38011, 29)
  "HitObjectGetRayTMaxNV\0" // IR(38040, 22)
  "HitObjectGetRayTMinNV\0" // IR(38062, 22)
  "HitObjectIsEmptyNV\0" // IR(38084, 19)
  "HitObjectIsHitNV\0" // IR(38103, 17)
  "HitObjectIsMissNV\0" // IR(38120, 18)
  "ReorderThreadWithHitObjectNV\0" // IR(38138, 29)
  "ReorderThreadWithHintNV\0" // IR(38167, 24)
  "TypeHitObjectNV\0" // IR(38191, 16)
  "ImageSampleFootprintNV\0" // IR(38207, 23)
  "TypeVectorIdEXT\0" // IR(38230, 16)
  "TypeCooperativeVectorNV\0" // IR(38246, 24)
  "CooperativeVectorMatrixMulNV\0" // IR(38270, 29)
  "CooperativeVectorOuterProductAccumulateNV\0" // IR(38299, 42)
  "CooperativeVectorReduceSumAccumulateNV\0" // IR(38341, 39)
  "CooperativeVectorMatrixMulAddNV\0" // IR(38380, 32)
  "CooperativeMatrixConvertNV\0" // IR(38412, 27)
  "EmitMeshTasksEXT\0" // IR(38439, 17)
  "SetMeshOutputsEXT\0" // IR(38456, 18)
  "GroupNonUniformPartitionEXT\0" // IR(38474, 28)
  "GroupNonUniformPartitionNV\0" // IR(38502, 27)
  "WritePackedPrimitiveIndices4x8NV\0" // IR(38529, 33)
  "FetchMicroTriangleVertexPositionNV\0" // IR(38562, 35)
  "FetchMicroTriangleVertexBarycentricNV\0" // IR(38597, 38)
  "CooperativeVectorLoadNV\0" // IR(38635, 24)
  "CooperativeVectorStoreNV\0" // IR(38659, 25)
  "HitObjectRecordFromQueryEXT\0" // IR(38684, 28)
  "HitObjectRecordMissEXT\0" // IR(38712, 23)
  "HitObjectRecordMissMotionEXT\0" // IR(38735, 29)
  "HitObjectGetIntersectionTriangleVertexPositionsEXT\0" // IR(38764, 51)
  "HitObjectGetRayFlagsEXT\0" // IR(38815, 24)
  "HitObjectSetShaderBindingTableRecordIndexEXT\0" // IR(38839, 45)
  "HitObjectReorderExecuteShaderEXT\0" // IR(38884, 33)
  "HitObjectTraceReorderExecuteEXT\0" // IR(38917, 32)
  "HitObjectTraceMotionReorderExecuteEXT\0" // IR(38949, 38)
  "TypeHitObjectEXT\0" // IR(38987, 17)
  "ReorderThreadWithHintEXT\0" // IR(39004, 25)
  "ReorderThreadWithHitObjectEXT\0" // IR(39029, 30)
  "HitObjectTraceRayEXT\0" // IR(39059, 21)
  "HitObjectTraceRayMotionEXT\0" // IR(39080, 27)
  "HitObjectRecordEmptyEXT\0" // IR(39107, 24)
  "HitObjectExecuteShaderEXT\0" // IR(39131, 26)
  "HitObjectGetCurrentTimeEXT\0" // IR(39157, 27)
  "HitObjectGetAttributesEXT\0" // IR(39184, 26)
  "HitObjectGetHitKindEXT\0" // IR(39210, 23)
  "HitObjectGetPrimitiveIndexEXT\0" // IR(39233, 30)
  "HitObjectGetGeometryIndexEXT\0" // IR(39263, 29)
  "HitObjectGetInstanceIdEXT\0" // IR(39292, 26)
  "HitObjectGetInstanceCustomIndexEXT\0" // IR(39318, 35)
  "HitObjectGetObjectRayOriginEXT\0" // IR(39353, 31)
  "HitObjectGetObjectRayDirectionEXT\0" // IR(39384, 34)
  "HitObjectGetWorldRayDirectionEXT\0" // IR(39418, 33)
  "HitObjectGetWorldRayOriginEXT\0" // IR(39451, 30)
  "HitObjectGetObjectToWorldEXT\0" // IR(39481, 29)
  "HitObjectGetWorldToObjectEXT\0" // IR(39510, 29)
  "HitObjectGetRayTMaxEXT\0" // IR(39539, 23)
  "ReportIntersectionKHR\0" // IR(39562, 22)
  "ReportIntersectionNV\0" // IR(39584, 21)
  "IgnoreIntersectionNV\0" // IR(39605, 21)
  "TerminateRayNV\0" // IR(39626, 15)
  "TraceNV\0" // IR(39641, 8)
  "TraceMotionNV\0" // IR(39649, 14)
  "TraceRayMotionNV\0" // IR(39663, 17)
  "RayQueryGetIntersectionTriangleVertexPositionsKHR\0" // IR(39680, 50)
  "TypeAccelerationStructureKHR\0" // IR(39730, 29)
  "TypeAccelerationStructureNV\0" // IR(39759, 28)
  "ExecuteCallableNV\0" // IR(39787, 18)
  "RayQueryGetIntersectionClusterIdNV\0" // IR(39805, 35)
  "RayQueryGetClusterIdNV\0" // IR(39840, 23)
  "HitObjectGetClusterIdNV\0" // IR(39863, 24)
  "HitObjectGetRayTMinEXT\0" // IR(39887, 23)
  "HitObjectGetShaderBindingTableRecordIndexEXT\0" // IR(39910, 45)
  "HitObjectGetShaderRecordBufferHandleEXT\0" // IR(39955, 40)
  "HitObjectIsEmptyEXT\0" // IR(39995, 20)
  "HitObjectIsHitEXT\0" // IR(40015, 18)
  "HitObjectIsMissEXT\0" // IR(40033, 19)
  "TypeCooperativeMatrixNV\0" // IR(40052, 24)
  "CooperativeMatrixLoadNV\0" // IR(40076, 24)
  "CooperativeMatrixStoreNV\0" // IR(40100, 25)
  "CooperativeMatrixMulAddNV\0" // IR(40125, 26)
  "CooperativeMatrixLengthNV\0" // IR(40151, 26)
  "BeginInvocationInterlockEXT\0" // IR(40177, 28)
  "EndInvocationInterlockEXT\0" // IR(40205, 26)
  "SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE\0" // IR(40231, 43)
  "CooperativeMatrixReduceNV\0" // IR(40274, 26)
  "SPV_OPERAND_TYPE_MEMORY_ACCESS\0" // IR(40300, 31)
  "SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS\0" // IR(40331, 44)
  "CooperativeMatrixLoadTensorNV\0" // IR(40375, 30)
  "CooperativeMatrixStoreTensorNV\0" // IR(40405, 31)
  "CooperativeMatrixPerElementOpNV\0" // IR(40436, 32)
  "TypeTensorLayoutNV\0" // IR(40468, 19)
  "TypeTensorViewNV\0" // IR(40487, 17)
  "CreateTensorLayoutNV\0" // IR(40504, 21)
  "TensorLayoutSetDimensionNV\0" // IR(40525, 27)
  "TensorLayoutSetStrideNV\0" // IR(40552, 24)
  "TensorLayoutSliceNV\0" // IR(40576, 20)
  "TensorLayoutSetClampValueNV\0" // IR(40596, 28)
  "CreateTensorViewNV\0" // IR(40624, 19)
  "TensorViewSetDimensionNV\0" // IR(40643, 25)
  "TensorViewSetStrideNV\0" // IR(40668, 22)
  "IsHelperInvocationEXT\0" // IR(40690, 22)
  "TensorViewSetClipNV\0" // IR(40712, 20)
  "TensorLayoutSetBlockSizeNV\0" // IR(40732, 27)
  "CooperativeMatrixTransposeNV\0" // IR(40759, 29)
  "ConvertUToImageNV\0" // IR(40788, 18)
  "ConvertUToSamplerNV\0" // IR(40806, 20)
  "ConvertImageToUNV\0" // IR(40826, 18)
  "ConvertSamplerToUNV\0" // IR(40844, 20)
  "ConvertUToSampledImageNV\0" // IR(40864, 25)
  "ConvertSampledImageToUNV\0" // IR(40889, 25)
  "SamplerImageAddressingModeNV\0" // IR(40914, 29)
  "SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS\0" // IR(40943, 52)
  "RawAccessChainNV\0" // IR(40995, 17)
  "RayQueryGetIntersectionSpherePositionNV\0" // IR(41012, 40)
  "RayQueryGetIntersectionSphereRadiusNV\0" // IR(41052, 38)
  "RayQueryGetIntersectionLSSPositionsNV\0" // IR(41090, 38)
  "RayQueryGetIntersectionLSSRadiiNV\0" // IR(41128, 34)
  "RayQueryGetIntersectionLSSHitValueNV\0" // IR(41162, 37)
  "HitObjectGetSpherePositionNV\0" // IR(41199, 29)
  "HitObjectGetSphereRadiusNV\0" // IR(41228, 27)
  "HitObjectGetLSSPositionsNV\0" // IR(41255, 27)
  "HitObjectGetLSSRadiiNV\0" // IR(41282, 23)
  "HitObjectIsSphereHitNV\0" // IR(41305, 23)
  "HitObjectIsLSSHitNV\0" // IR(41328, 20)
  "RayQueryIsSphereHitNV\0" // IR(41348, 22)
  "RayQueryIsLSSHitNV\0" // IR(41370, 19)
  "SubgroupShuffleDownINTEL\0" // IR(41389, 25)
  "SubgroupShuffleUpINTEL\0" // IR(41414, 23)
  "SubgroupShuffleXorINTEL\0" // IR(41437, 24)
  "SubgroupBlockReadINTEL\0" // IR(41461, 23)
  "SubgroupBlockWriteINTEL\0" // IR(41484, 24)
  "SubgroupImageBlockReadINTEL\0" // IR(41508, 28)
  "SubgroupImageBlockWriteINTEL\0" // IR(41536, 29)
  "SubgroupImageMediaBlockReadINTEL\0" // IR(41565, 33)
  "SubgroupImageMediaBlockWriteINTEL\0" // IR(41598, 34)
  "UCountLeadingZerosINTEL\0" // IR(41632, 24)
  "UCountTrailingZerosINTEL\0" // IR(41656, 25)
  "AbsISubINTEL\0" // IR(41681, 13)
  "AbsUSubINTEL\0" // IR(41694, 13)
  "IAddSatINTEL\0" // IR(41707, 13)
  "UAddSatINTEL\0" // IR(41720, 13)
  "IAverageINTEL\0" // IR(41733, 14)
  "UAverageINTEL\0" // IR(41747, 14)
  "IAverageRoundedINTEL\0" // IR(41761, 21)
  "UAverageRoundedINTEL\0" // IR(41782, 21)
  "ISubSatINTEL\0" // IR(41803, 13)
  "USubSatINTEL\0" // IR(41816, 13)
  "IMul32x16INTEL\0" // IR(41829, 15)
  "UMul32x16INTEL\0" // IR(41844, 15)
  "ConstantFunctionPointerINTEL\0" // IR(41859, 29)
  "FunctionPointerCallINTEL\0" // IR(41888, 25)
  "AsmTargetINTEL\0" // IR(41913, 15)
  "AsmCallINTEL\0" // IR(41928, 13)
  "AtomicFMinEXT\0" // IR(41941, 14)
  "AtomicFMaxEXT\0" // IR(41955, 14)
  "AssumeTrueKHR\0" // IR(41969, 14)
  "ExpectKHR\0" // IR(41983, 10)
  "DecorateString\0" // IR(41993, 15)
  "DecorateStringGOOGLE\0" // IR(42008, 21)
  "MemberDecorateString\0" // IR(42029, 21)
  "MemberDecorateStringGOOGLE\0" // IR(42050, 27)
  "VmeImageINTEL\0" // IR(42077, 14)
  "TypeVmeImageINTEL\0" // IR(42091, 18)
  "TypeAvcImePayloadINTEL\0" // IR(42109, 23)
  "TypeAvcRefPayloadINTEL\0" // IR(42132, 23)
  "TypeAvcSicPayloadINTEL\0" // IR(42155, 23)
  "TypeAvcMcePayloadINTEL\0" // IR(42178, 23)
  "TypeAvcMceResultINTEL\0" // IR(42201, 22)
  "TypeAvcImeResultINTEL\0" // IR(42223, 22)
  "TypeAvcImeResultSingleReferenceStreamoutINTEL\0" // IR(42245, 46)
  "TypeAvcImeResultDualReferenceStreamoutINTEL\0" // IR(42291, 44)
  "TypeAvcImeSingleReferenceStreaminINTEL\0" // IR(42335, 39)
  "TypeAvcImeDualReferenceStreaminINTEL\0" // IR(42374, 37)
  "TypeAvcRefResultINTEL\0" // IR(42411, 22)
  "TypeAvcSicResultINTEL\0" // IR(42433, 22)
  "SubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL\0" // IR(42455, 60)
  "SubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL\0" // IR(42515, 53)
  "SubgroupAvcMceGetDefaultInterShapePenaltyINTEL\0" // IR(42568, 47)
  "SubgroupAvcMceSetInterShapePenaltyINTEL\0" // IR(42615, 40)
  "SubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL\0" // IR(42655, 51)
  "SubgroupAvcMceSetInterDirectionPenaltyINTEL\0" // IR(42706, 44)
  "SubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL\0" // IR(42750, 51)
  "SubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL\0" // IR(42801, 56)
  "SubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL\0" // IR(42857, 50)
  "SubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL\0" // IR(42907, 52)
  "SubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL\0" // IR(42959, 49)
  "SubgroupAvcMceSetMotionVectorCostFunctionINTEL\0" // IR(43008, 47)
  "SubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL\0" // IR(43055, 50)
  "SubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL\0" // IR(43105, 51)
  "SubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL\0" // IR(43156, 56)
  "SubgroupAvcMceSetAcOnlyHaarINTEL\0" // IR(43212, 33)
  "SubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL\0" // IR(43245, 52)
  "SubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL\0" // IR(43297, 61)
  "SubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL\0" // IR(43358, 61)
  "SubgroupAvcMceConvertToImePayloadINTEL\0" // IR(43419, 39)
  "SubgroupAvcMceConvertToImeResultINTEL\0" // IR(43458, 38)
  "SubgroupAvcMceConvertToRefPayloadINTEL\0" // IR(43496, 39)
  "SubgroupAvcMceConvertToRefResultINTEL\0" // IR(43535, 38)
  "SubgroupAvcMceConvertToSicPayloadINTEL\0" // IR(43573, 39)
  "SubgroupAvcMceConvertToSicResultINTEL\0" // IR(43612, 38)
  "SubgroupAvcMceGetMotionVectorsINTEL\0" // IR(43650, 36)
  "SubgroupAvcMceGetInterDistortionsINTEL\0" // IR(43686, 39)
  "SubgroupAvcMceGetBestInterDistortionsINTEL\0" // IR(43725, 43)
  "SubgroupAvcMceGetInterMajorShapeINTEL\0" // IR(43768, 38)
  "SubgroupAvcMceGetInterMinorShapeINTEL\0" // IR(43806, 38)
  "SubgroupAvcMceGetInterDirectionsINTEL\0" // IR(43844, 38)
  "SubgroupAvcMceGetInterMotionVectorCountINTEL\0" // IR(43882, 45)
  "SubgroupAvcMceGetInterReferenceIdsINTEL\0" // IR(43927, 40)
  "SubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL\0" // IR(43967, 62)
  "SubgroupAvcImeInitializeINTEL\0" // IR(44029, 30)
  "SubgroupAvcImeSetSingleReferenceINTEL\0" // IR(44059, 38)
  "SubgroupAvcImeSetDualReferenceINTEL\0" // IR(44097, 36)
  "SubgroupAvcImeRefWindowSizeINTEL\0" // IR(44133, 33)
  "SubgroupAvcImeAdjustRefOffsetINTEL\0" // IR(44166, 35)
  "SubgroupAvcImeConvertToMcePayloadINTEL\0" // IR(44201, 39)
  "SubgroupAvcImeSetMaxMotionVectorCountINTEL\0" // IR(44240, 43)
  "SubgroupAvcImeSetUnidirectionalMixDisableINTEL\0" // IR(44283, 47)
  "SubgroupAvcImeSetEarlySearchTerminationThresholdINTEL\0" // IR(44330, 54)
  "SubgroupAvcImeSetWeightedSadINTEL\0" // IR(44384, 34)
  "SubgroupAvcImeEvaluateWithSingleReferenceINTEL\0" // IR(44418, 47)
  "SubgroupAvcImeEvaluateWithDualReferenceINTEL\0" // IR(44465, 45)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL\0" // IR(44510, 55)
  "SubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL\0" // IR(44565, 53)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL\0" // IR(44618, 56)
  "SubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL\0" // IR(44674, 54)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL\0" // IR(44728, 58)
  "SubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL\0" // IR(44786, 56)
  "SubgroupAvcImeConvertToMceResultINTEL\0" // IR(44842, 38)
  "SubgroupAvcImeGetSingleReferenceStreaminINTEL\0" // IR(44880, 46)
  "SubgroupAvcImeGetDualReferenceStreaminINTEL\0" // IR(44926, 44)
  "SubgroupAvcImeStripSingleReferenceStreamoutINTEL\0" // IR(44970, 49)
  "SubgroupAvcImeStripDualReferenceStreamoutINTEL\0" // IR(45019, 47)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL\0" // IR(45066, 70)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL\0" // IR(45136, 68)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL\0" // IR(45204, 69)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL\0" // IR(45273, 68)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL\0" // IR(45341, 66)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL\0" // IR(45407, 67)
  "SubgroupAvcImeGetBorderReachedINTEL\0" // IR(45474, 36)
  "SubgroupAvcImeGetTruncatedSearchIndicationINTEL\0" // IR(45510, 48)
  "SubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL\0" // IR(45558, 59)
  "SubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL\0" // IR(45617, 58)
  "SubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL\0" // IR(45675, 56)
  "SubgroupAvcFmeInitializeINTEL\0" // IR(45731, 30)
  "SubgroupAvcBmeInitializeINTEL\0" // IR(45761, 30)
  "SubgroupAvcRefConvertToMcePayloadINTEL\0" // IR(45791, 39)
  "SubgroupAvcRefSetBidirectionalMixDisableINTEL\0" // IR(45830, 46)
  "SubgroupAvcRefSetBilinearFilterEnableINTEL\0" // IR(45876, 43)
  "SubgroupAvcRefEvaluateWithSingleReferenceINTEL\0" // IR(45919, 47)
  "SubgroupAvcRefEvaluateWithDualReferenceINTEL\0" // IR(45966, 45)
  "SubgroupAvcRefEvaluateWithMultiReferenceINTEL\0" // IR(46011, 46)
  "SubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL\0" // IR(46057, 56)
  "SubgroupAvcRefConvertToMceResultINTEL\0" // IR(46113, 38)
  "SubgroupAvcSicInitializeINTEL\0" // IR(46151, 30)
  "SubgroupAvcSicConfigureSkcINTEL\0" // IR(46181, 32)
  "SubgroupAvcSicConfigureIpeLumaINTEL\0" // IR(46213, 36)
  "SubgroupAvcSicConfigureIpeLumaChromaINTEL\0" // IR(46249, 42)
  "SubgroupAvcSicGetMotionVectorMaskINTEL\0" // IR(46291, 39)
  "SubgroupAvcSicConvertToMcePayloadINTEL\0" // IR(46330, 39)
  "SubgroupAvcSicSetIntraLumaShapePenaltyINTEL\0" // IR(46369, 44)
  "SubgroupAvcSicSetIntraLumaModeCostFunctionINTEL\0" // IR(46413, 48)
  "SubgroupAvcSicSetIntraChromaModeCostFunctionINTEL\0" // IR(46461, 50)
  "SubgroupAvcSicSetBilinearFilterEnableINTEL\0" // IR(46511, 43)
  "SubgroupAvcSicSetSkcForwardTransformEnableINTEL\0" // IR(46554, 48)
  "SubgroupAvcSicSetBlockBasedRawSkipSadINTEL\0" // IR(46602, 43)
  "SubgroupAvcSicEvaluateIpeINTEL\0" // IR(46645, 31)
  "SubgroupAvcSicEvaluateWithSingleReferenceINTEL\0" // IR(46676, 47)
  "SubgroupAvcSicEvaluateWithDualReferenceINTEL\0" // IR(46723, 45)
  "SubgroupAvcSicEvaluateWithMultiReferenceINTEL\0" // IR(46768, 46)
  "SubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL\0" // IR(46814, 56)
  "SubgroupAvcSicConvertToMceResultINTEL\0" // IR(46870, 38)
  "SubgroupAvcSicGetIpeLumaShapeINTEL\0" // IR(46908, 35)
  "SubgroupAvcSicGetBestIpeLumaDistortionINTEL\0" // IR(46943, 44)
  "SubgroupAvcSicGetBestIpeChromaDistortionINTEL\0" // IR(46987, 46)
  "SubgroupAvcSicGetPackedIpeLumaModesINTEL\0" // IR(47033, 41)
  "SubgroupAvcSicGetIpeChromaModeINTEL\0" // IR(47074, 36)
  "SubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL\0" // IR(47110, 50)
  "SubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL\0" // IR(47160, 48)
  "SubgroupAvcSicGetInterRawSadsINTEL\0" // IR(47208, 35)
  "SaveMemoryINTEL\0" // IR(47243, 16)
  "RestoreMemoryINTEL\0" // IR(47259, 19)
  "ArbitraryFloatSinCosPiALTERA\0" // IR(47278, 29)
  "ArbitraryFloatSinCosPiINTEL\0" // IR(47307, 28)
  "ArbitraryFloatCastALTERA\0" // IR(47335, 25)
  "ArbitraryFloatCastINTEL\0" // IR(47360, 24)
  "ArbitraryFloatCastFromIntALTERA\0" // IR(47384, 32)
  "ArbitraryFloatCastFromIntINTEL\0" // IR(47416, 31)
  "ArbitraryFloatCastToIntALTERA\0" // IR(47447, 30)
  "ArbitraryFloatCastToIntINTEL\0" // IR(47477, 29)
  "ArbitraryFloatAddALTERA\0" // IR(47506, 24)
  "ArbitraryFloatAddINTEL\0" // IR(47530, 23)
  "ArbitraryFloatSubALTERA\0" // IR(47553, 24)
  "ArbitraryFloatSubINTEL\0" // IR(47577, 23)
  "ArbitraryFloatMulALTERA\0" // IR(47600, 24)
  "ArbitraryFloatMulINTEL\0" // IR(47624, 23)
  "ArbitraryFloatDivALTERA\0" // IR(47647, 24)
  "ArbitraryFloatDivINTEL\0" // IR(47671, 23)
  "ArbitraryFloatGTALTERA\0" // IR(47694, 23)
  "ArbitraryFloatGTINTEL\0" // IR(47717, 22)
  "ArbitraryFloatGEALTERA\0" // IR(47739, 23)
  "ArbitraryFloatGEINTEL\0" // IR(47762, 22)
  "ArbitraryFloatLTALTERA\0" // IR(47784, 23)
  "ArbitraryFloatLTINTEL\0" // IR(47807, 22)
  "ArbitraryFloatLEALTERA\0" // IR(47829, 23)
  "ArbitraryFloatLEINTEL\0" // IR(47852, 22)
  "ArbitraryFloatEQALTERA\0" // IR(47874, 23)
  "ArbitraryFloatEQINTEL\0" // IR(47897, 22)
  "ArbitraryFloatRecipALTERA\0" // IR(47919, 26)
  "ArbitraryFloatRecipINTEL\0" // IR(47945, 25)
  "ArbitraryFloatRSqrtALTERA\0" // IR(47970, 26)
  "ArbitraryFloatRSqrtINTEL\0" // IR(47996, 25)
  "ArbitraryFloatCbrtALTERA\0" // IR(48021, 25)
  "ArbitraryFloatCbrtINTEL\0" // IR(48046, 24)
  "ArbitraryFloatHypotALTERA\0" // IR(48070, 26)
  "ArbitraryFloatHypotINTEL\0" // IR(48096, 25)
  "ArbitraryFloatSqrtALTERA\0" // IR(48121, 25)
  "ArbitraryFloatSqrtINTEL\0" // IR(48146, 24)
  "ArbitraryFloatLogINTEL\0" // IR(48170, 23)
  "ArbitraryFloatLog2INTEL\0" // IR(48193, 24)
  "ArbitraryFloatLog10INTEL\0" // IR(48217, 25)
  "ArbitraryFloatLog1pINTEL\0" // IR(48242, 25)
  "ArbitraryFloatExpINTEL\0" // IR(48267, 23)
  "ArbitraryFloatExp2INTEL\0" // IR(48290, 24)
  "ArbitraryFloatExp10INTEL\0" // IR(48314, 25)
  "ArbitraryFloatExpm1INTEL\0" // IR(48339, 25)
  "ArbitraryFloatSinINTEL\0" // IR(48364, 23)
  "ArbitraryFloatCosINTEL\0" // IR(48387, 23)
  "ArbitraryFloatSinCosINTEL\0" // IR(48410, 26)
  "ArbitraryFloatSinPiINTEL\0" // IR(48436, 25)
  "ArbitraryFloatCosPiINTEL\0" // IR(48461, 25)
  "ArbitraryFloatASinINTEL\0" // IR(48486, 24)
  "ArbitraryFloatASinPiINTEL\0" // IR(48510, 26)
  "ArbitraryFloatACosINTEL\0" // IR(48536, 24)
  "ArbitraryFloatACosPiINTEL\0" // IR(48560, 26)
  "ArbitraryFloatATanINTEL\0" // IR(48586, 24)
  "ArbitraryFloatATanPiINTEL\0" // IR(48610, 26)
  "ArbitraryFloatATan2INTEL\0" // IR(48636, 25)
  "ArbitraryFloatPowINTEL\0" // IR(48661, 23)
  "ArbitraryFloatPowRINTEL\0" // IR(48684, 24)
  "ArbitraryFloatPowNINTEL\0" // IR(48708, 24)
  "LoopControlINTEL\0" // IR(48732, 17)
  "AliasDomainDeclINTEL\0" // IR(48749, 21)
  "AliasScopeDeclINTEL\0" // IR(48770, 20)
  "AliasScopeListDeclINTEL\0" // IR(48790, 24)
  "FixedSqrtALTERA\0" // IR(48814, 16)
  "FixedSqrtINTEL\0" // IR(48830, 15)
  "FixedRecipALTERA\0" // IR(48845, 17)
  "FixedRecipINTEL\0" // IR(48862, 16)
  "FixedRsqrtALTERA\0" // IR(48878, 17)
  "FixedRsqrtINTEL\0" // IR(48895, 16)
  "FixedSinALTERA\0" // IR(48911, 15)
  "FixedSinINTEL\0" // IR(48926, 14)
  "FixedCosALTERA\0" // IR(48940, 15)
  "FixedCosINTEL\0" // IR(48955, 14)
  "FixedSinCosALTERA\0" // IR(48969, 18)
  "FixedSinCosINTEL\0" // IR(48987, 17)
  "FixedSinPiALTERA\0" // IR(49004, 17)
  "FixedSinPiINTEL\0" // IR(49021, 16)
  "FixedCosPiALTERA\0" // IR(49037, 17)
  "FixedCosPiINTEL\0" // IR(49054, 16)
  "FixedSinCosPiALTERA\0" // IR(49070, 20)
  "FixedSinCosPiINTEL\0" // IR(49090, 19)
  "FixedLogALTERA\0" // IR(49109, 15)
  "FixedLogINTEL\0" // IR(49124, 14)
  "FixedExpALTERA\0" // IR(49138, 15)
  "FixedExpINTEL\0" // IR(49153, 14)
  "PtrCastToCrossWorkgroupALTERA\0" // IR(49167, 30)
  "PtrCastToCrossWorkgroupINTEL\0" // IR(49197, 29)
  "CrossWorkgroupCastToPtrALTERA\0" // IR(49226, 30)
  "CrossWorkgroupCastToPtrINTEL\0" // IR(49256, 29)
  "ReadPipeBlockingALTERA\0" // IR(49285, 23)
  "ReadPipeBlockingINTEL\0" // IR(49308, 22)
  "WritePipeBlockingALTERA\0" // IR(49330, 24)
  "WritePipeBlockingINTEL\0" // IR(49354, 23)
  "RayQueryGetRayTMinKHR\0" // IR(49377, 22)
  "RayQueryGetRayFlagsKHR\0" // IR(49399, 23)
  "RayQueryGetIntersectionTKHR\0" // IR(49422, 28)
  "RayQueryGetIntersectionInstanceCustomIndexKHR\0" // IR(49450, 46)
  "RayQueryGetIntersectionInstanceIdKHR\0" // IR(49496, 37)
  "RayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR\0" // IR(49533, 65)
  "RayQueryGetIntersectionGeometryIndexKHR\0" // IR(49598, 40)
  "RayQueryGetIntersectionPrimitiveIndexKHR\0" // IR(49638, 41)
  "RayQueryGetIntersectionBarycentricsKHR\0" // IR(49679, 39)
  "RayQueryGetIntersectionFrontFaceKHR\0" // IR(49718, 36)
  "RayQueryGetIntersectionCandidateAABBOpaqueKHR\0" // IR(49754, 46)
  "RayQueryGetIntersectionObjectRayDirectionKHR\0" // IR(49800, 45)
  "RayQueryGetIntersectionObjectRayOriginKHR\0" // IR(49845, 42)
  "RayQueryGetWorldRayDirectionKHR\0" // IR(49887, 32)
  "RayQueryGetWorldRayOriginKHR\0" // IR(49919, 29)
  "RayQueryGetIntersectionObjectToWorldKHR\0" // IR(49948, 40)
  "RayQueryGetIntersectionWorldToObjectKHR\0" // IR(49988, 40)
  "AtomicFAddEXT\0" // IR(50028, 14)
  "TypeBufferSurfaceINTEL\0" // IR(50042, 23)
  "TypeStructContinuedINTEL\0" // IR(50065, 25)
  "ConstantCompositeContinuedINTEL\0" // IR(50090, 32)
  "SpecConstantCompositeContinuedINTEL\0" // IR(50122, 36)
  "CompositeConstructContinuedINTEL\0" // IR(50158, 33)
  "ConvertFToBF16INTEL\0" // IR(50191, 20)
  "ConvertBF16ToFINTEL\0" // IR(50211, 20)
  "ControlBarrierArriveEXT\0" // IR(50231, 24)
  "ControlBarrierArriveINTEL\0" // IR(50255, 26)
  "ControlBarrierWaitEXT\0" // IR(50281, 22)
  "ControlBarrierWaitINTEL\0" // IR(50303, 24)
  "TaskSequenceCreateALTERA\0" // IR(50327, 25)
  "TaskSequenceCreateINTEL\0" // IR(50352, 24)
  "TaskSequenceAsyncALTERA\0" // IR(50376, 24)
  "TaskSequenceAsyncINTEL\0" // IR(50400, 23)
  "TaskSequenceGetALTERA\0" // IR(50423, 22)
  "TaskSequenceGetINTEL\0" // IR(50445, 21)
  "TaskSequenceReleaseALTERA\0" // IR(50466, 26)
  "TaskSequenceReleaseINTEL\0" // IR(50492, 25)
  "TypeTaskSequenceALTERA\0" // IR(50517, 23)
  "TypeTaskSequenceINTEL\0" // IR(50540, 22)
  "SubgroupBlockPrefetchINTEL\0" // IR(50562, 27)
  "Subgroup2DBlockLoadINTEL\0" // IR(50589, 25)
  "Subgroup2DBlockLoadTransformINTEL\0" // IR(50614, 34)
  "Subgroup2DBlockLoadTransposeINTEL\0" // IR(50648, 34)
  "Subgroup2DBlockPrefetchINTEL\0" // IR(50682, 29)
  "Subgroup2DBlockStoreINTEL\0" // IR(50711, 26)
  "SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS\0" // IR(50737, 62)
  "BitwiseFunctionINTEL\0" // IR(50799, 21)
  "ConditionalExtensionINTEL\0" // IR(50820, 26)
  "ConditionalEntryPointINTEL\0" // IR(50846, 27)
  "ConditionalCapabilityINTEL\0" // IR(50873, 27)
  "SpecConstantTargetINTEL\0" // IR(50900, 24)
  "SpecConstantArchitectureINTEL\0" // IR(50924, 30)
  "SPV_OPERAND_TYPE_VARIABLE_CAPABILITY\0" // IR(50954, 37)
  "SpecConstantCapabilitiesINTEL\0" // IR(50991, 30)
  "ConditionalCopyObjectINTEL\0" // IR(51021, 27)
  "PredicatedLoadINTEL\0" // IR(51048, 20)
  "PredicatedStoreINTEL\0" // IR(51068, 21)
  "GroupIMulKHR\0" // IR(51089, 13)
  "GroupFMulKHR\0" // IR(51102, 13)
  "GroupBitwiseAndKHR\0" // IR(51115, 19)
  "GroupBitwiseOrKHR\0" // IR(51134, 18)
  "GroupBitwiseXorKHR\0" // IR(51152, 19)
  "GroupLogicalAndKHR\0" // IR(51171, 19)
  "GroupLogicalOrKHR\0" // IR(51190, 18)
  "GroupLogicalXorKHR\0" // IR(51208, 19)
  "RoundFToTF32INTEL\0" // IR(51227, 18)
  "MaskedGatherINTEL\0" // IR(51245, 18)
  "MaskedScatterINTEL\0" // IR(51263, 19)
  "ConvertHandleToImageINTEL\0" // IR(51282, 26)
  "ConvertHandleToSamplerINTEL\0" // IR(51308, 28)
  "ConvertHandleToSampledImageINTEL\0" // IR(51336, 33)
  "FDot2MixAcc32VALVE\0" // IR(51369, 19)
  "FDot2MixAcc16VALVE\0" // IR(51388, 19)
  "FDot4MixAcc32VALVE\0" // IR(51407, 19)
  "DebugInfoNone\0" // IR(51426, 14)
  "DebugCompilationUnit\0" // IR(51440, 21)
  "SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING\0" // IR(51461, 52)
  "DebugTypeBasic\0" // IR(51513, 15)
  "SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS\0" // IR(51528, 34)
  "DebugTypePointer\0" // IR(51562, 17)
  "SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER\0" // IR(51579, 38)
  "DebugTypeQualifier\0" // IR(51617, 19)
  "DebugTypeArray\0" // IR(51636, 15)
  "DebugTypeVector\0" // IR(51651, 16)
  "DebugTypedef\0" // IR(51667, 13)
  "DebugTypeFunction\0" // IR(51680, 18)
  "DebugTypeEnum\0" // IR(51698, 14)
  "SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE\0" // IR(51712, 38)
  "DebugTypeComposite\0" // IR(51750, 19)
  "DebugTypeMember\0" // IR(51769, 16)
  "DebugTypeInheritance\0" // IR(51785, 21)
  "DebugTypePtrToMember\0" // IR(51806, 21)
  "DebugTypeTemplate\0" // IR(51827, 18)
  "DebugTypeTemplateParameter\0" // IR(51845, 27)
  "DebugTypeTemplateTemplateParameter\0" // IR(51872, 35)
  "DebugTypeTemplateParameterPack\0" // IR(51907, 31)
  "DebugGlobalVariable\0" // IR(51938, 20)
  "DebugFunctionDeclaration\0" // IR(51958, 25)
  "DebugFunction\0" // IR(51983, 14)
  "DebugLexicalBlock\0" // IR(51997, 18)
  "DebugLexicalBlockDiscriminator\0" // IR(52015, 31)
  "DebugScope\0" // IR(52046, 11)
  "DebugNoScope\0" // IR(52057, 13)
  "DebugInlinedAt\0" // IR(52070, 15)
  "SPV_OPERAND_TYPE_OPTIONAL_LITERAL_INTEGER\0" // IR(52085, 42)
  "DebugLocalVariable\0" // IR(52127, 19)
  "DebugInlinedVariable\0" // IR(52146, 21)
  "DebugDeclare\0" // IR(52167, 13)
  "DebugValue\0" // IR(52180, 11)
  "SPV_OPERAND_TYPE_DEBUG_OPERATION\0" // IR(52191, 33)
  "DebugOperation\0" // IR(52224, 15)
  "DebugExpression\0" // IR(52239, 16)
  "DebugMacroDef\0" // IR(52255, 14)
  "DebugMacroUndef\0" // IR(52269, 16)
  "Round\0" // IR(52285, 6)
  "RoundEven\0" // IR(52291, 10)
  "Trunc\0" // IR(52301, 6)
  "FAbs\0" // IR(52307, 5)
  "SAbs\0" // IR(52312, 5)
  "FSign\0" // IR(52317, 6)
  "SSign\0" // IR(52323, 6)
  "Floor\0" // IR(52329, 6)
  "Ceil\0" // IR(52335, 5)
  "Fract\0" // IR(52340, 6)
  "Radians\0" // IR(52346, 8)
  "Degrees\0" // IR(52354, 8)
  "Sin\0" // IR(52362, 4)
  "Cos\0" // IR(52366, 4)
  "Tan\0" // IR(52370, 4)
  "Asin\0" // IR(52374, 5)
  "Acos\0" // IR(52379, 5)
  "Atan\0" // IR(52384, 5)
  "Sinh\0" // IR(52389, 5)
  "Cosh\0" // IR(52394, 5)
  "Tanh\0" // IR(52399, 5)
  "Asinh\0" // IR(52404, 6)
  "Acosh\0" // IR(52410, 6)
  "Atanh\0" // IR(52416, 6)
  "Atan2\0" // IR(52422, 6)
  "Pow\0" // IR(52428, 4)
  "Exp\0" // IR(52432, 4)
  "Log\0" // IR(52436, 4)
  "Exp2\0" // IR(52440, 5)
  "Log2\0" // IR(52445, 5)
  "Sqrt\0" // IR(52450, 5)
  "InverseSqrt\0" // IR(52455, 12)
  "Determinant\0" // IR(52467, 12)
  "MatrixInverse\0" // IR(52479, 14)
  "Modf\0" // IR(52493, 5)
  "ModfStruct\0" // IR(52498, 11)
  "FMin\0" // IR(52509, 5)
  "UMin\0" // IR(52514, 5)
  "SMin\0" // IR(52519, 5)
  "FMax\0" // IR(52524, 5)
  "UMax\0" // IR(52529, 5)
  "SMax\0" // IR(52534, 5)
  "FClamp\0" // IR(52539, 7)
  "UClamp\0" // IR(52546, 7)
  "SClamp\0" // IR(52553, 7)
  "FMix\0" // IR(52560, 5)
  "IMix\0" // IR(52565, 5)
  "Step\0" // IR(52570, 5)
  "SmoothStep\0" // IR(52575, 11)
  "Fma\0" // IR(52586, 4)
  "Frexp\0" // IR(52590, 6)
  "FrexpStruct\0" // IR(52596, 12)
  "Ldexp\0" // IR(52608, 6)
  "PackSnorm4x8\0" // IR(52614, 13)
  "PackUnorm4x8\0" // IR(52627, 13)
  "PackSnorm2x16\0" // IR(52640, 14)
  "PackUnorm2x16\0" // IR(52654, 14)
  "PackHalf2x16\0" // IR(52668, 13)
  "PackDouble2x32\0" // IR(52681, 15)
  "UnpackSnorm2x16\0" // IR(52696, 16)
  "UnpackUnorm2x16\0" // IR(52712, 16)
  "UnpackHalf2x16\0" // IR(52728, 15)
  "UnpackSnorm4x8\0" // IR(52743, 15)
  "UnpackUnorm4x8\0" // IR(52758, 15)
  "UnpackDouble2x32\0" // IR(52773, 17)
  "Length\0" // IR(52790, 7)
  "Distance\0" // IR(52797, 9)
  "Cross\0" // IR(52806, 6)
  "Normalize\0" // IR(52812, 10)
  "FaceForward\0" // IR(52822, 12)
  "Reflect\0" // IR(52834, 8)
  "Refract\0" // IR(52842, 8)
  "FindILsb\0" // IR(52850, 9)
  "FindSMsb\0" // IR(52859, 9)
  "FindUMsb\0" // IR(52868, 9)
  "InterpolateAtCentroid\0" // IR(52877, 22)
  "InterpolateAtSample\0" // IR(52899, 20)
  "InterpolateAtOffset\0" // IR(52919, 20)
  "NMin\0" // IR(52939, 5)
  "NMax\0" // IR(52944, 5)
  "NClamp\0" // IR(52949, 7)
  "ArgumentInfo\0" // IR(52956, 13)
  "ArgumentStorageBuffer\0" // IR(52969, 22)
  "ArgumentUniform\0" // IR(52991, 16)
  "ArgumentPodStorageBuffer\0" // IR(53007, 25)
  "ArgumentPodUniform\0" // IR(53032, 19)
  "ArgumentPodPushConstant\0" // IR(53051, 24)
  "ArgumentSampledImage\0" // IR(53075, 21)
  "ArgumentStorageImage\0" // IR(53096, 21)
  "ArgumentSampler\0" // IR(53117, 16)
  "ArgumentWorkgroup\0" // IR(53133, 18)
  "SpecConstantWorkgroupSize\0" // IR(53151, 26)
  "SpecConstantGlobalOffset\0" // IR(53177, 25)
  "SpecConstantWorkDim\0" // IR(53202, 20)
  "PushConstantGlobalOffset\0" // IR(53222, 25)
  "PushConstantEnqueuedLocalSize\0" // IR(53247, 30)
  "PushConstantGlobalSize\0" // IR(53277, 23)
  "PushConstantRegionOffset\0" // IR(53300, 25)
  "PushConstantNumWorkgroups\0" // IR(53325, 26)
  "PushConstantRegionGroupOffset\0" // IR(53351, 30)
  "ConstantDataStorageBuffer\0" // IR(53381, 26)
  "ConstantDataUniform\0" // IR(53407, 20)
  "PropertyRequiredWorkgroupSize\0" // IR(53427, 30)
  "SpecConstantSubgroupMaxSize\0" // IR(53457, 28)
  "ArgumentPointerPushConstant\0" // IR(53485, 28)
  "ArgumentPointerUniform\0" // IR(53513, 23)
  "ProgramScopeVariablesStorageBuffer\0" // IR(53536, 35)
  "ProgramScopeVariablePointerRelocation\0" // IR(53571, 38)
  "ImageArgumentInfoChannelOrderPushConstant\0" // IR(53609, 42)
  "ImageArgumentInfoChannelDataTypePushConstant\0" // IR(53651, 45)
  "ImageArgumentInfoChannelOrderUniform\0" // IR(53696, 37)
  "ImageArgumentInfoChannelDataTypeUniform\0" // IR(53733, 40)
  "ArgumentStorageTexelBuffer\0" // IR(53773, 27)
  "ArgumentUniformTexelBuffer\0" // IR(53800, 27)
  "ConstantDataPointerPushConstant\0" // IR(53827, 32)
  "ProgramScopeVariablePointerPushConstant\0" // IR(53859, 40)
  "PrintfInfo\0" // IR(53899, 11)
  "PrintfBufferStorageBuffer\0" // IR(53910, 26)
  "PrintfBufferPointerPushConstant\0" // IR(53936, 32)
  "NormalizedSamplerMaskPushConstant\0" // IR(53968, 34)
  "WorkgroupVariableSize\0" // IR(54002, 22)
  "DebugImportedEntity\0" // IR(54024, 20)
  "DebugSource\0" // IR(54044, 12)
  "DebugFunctionDefinition\0" // IR(54056, 24)
  "DebugSourceContinued\0" // IR(54080, 21)
  "DebugLine\0" // IR(54101, 10)
  "DebugNoLine\0" // IR(54111, 12)
  "DebugBuildIdentifier\0" // IR(54123, 21)
  "DebugStoragePath\0" // IR(54144, 17)
  "DebugEntryPoint\0" // IR(54161, 16)
  "DebugTypeMatrix\0" // IR(54177, 16)
  "Configuration\0" // IR(54193, 14)
  "StartCounter\0" // IR(54207, 13)
  "StopCounter\0" // IR(54220, 12)
  "PushConstants\0" // IR(54232, 14)
  "SpecializationMapEntry\0" // IR(54246, 23)
  "DescriptorSetBuffer\0" // IR(54269, 20)
  "DescriptorSetImage\0" // IR(54289, 19)
  "DescriptorSetSampler\0" // IR(54308, 21)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING\0" // IR(54329, 63)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS\0" // IR(54392, 45)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER\0" // IR(54437, 49)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE\0" // IR(54486, 49)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION\0" // IR(54535, 44)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY\0" // IR(54579, 50)
  "DebugModuleINTEL\0" // IR(54629, 17)
  "acos\0" // IR(54646, 5)
  "acosh\0" // IR(54651, 6)
  "acospi\0" // IR(54657, 7)
  "asin\0" // IR(54664, 5)
  "asinh\0" // IR(54669, 6)
  "asinpi\0" // IR(54675, 7)
  "atan\0" // IR(54682, 5)
  "atan2\0" // IR(54687, 6)
  "atanh\0" // IR(54693, 6)
  "atanpi\0" // IR(54699, 7)
  "atan2pi\0" // IR(54706, 8)
  "cbrt\0" // IR(54714, 5)
  "ceil\0" // IR(54719, 5)
  "copysign\0" // IR(54724, 9)
  "cos\0" // IR(54733, 4)
  "cosh\0" // IR(54737, 5)
  "cospi\0" // IR(54742, 6)
  "erfc\0" // IR(54748, 5)
  "erf\0" // IR(54753, 4)
  "exp\0" // IR(54757, 4)
  "exp2\0" // IR(54761, 5)
  "exp10\0" // IR(54766, 6)
  "expm1\0" // IR(54772, 6)
  "fabs\0" // IR(54778, 5)
  "fdim\0" // IR(54783, 5)
  "floor\0" // IR(54788, 6)
  "fma\0" // IR(54794, 4)
  "fmax\0" // IR(54798, 5)
  "fmin\0" // IR(54803, 5)
  "fmod\0" // IR(54808, 5)
  "fract\0" // IR(54813, 6)
  "frexp\0" // IR(54819, 6)
  "hypot\0" // IR(54825, 6)
  "ilogb\0" // IR(54831, 6)
  "ldexp\0" // IR(54837, 6)
  "lgamma\0" // IR(54843, 7)
  "lgamma_r\0" // IR(54850, 9)
  "log\0" // IR(54859, 4)
  "log2\0" // IR(54863, 5)
  "log10\0" // IR(54868, 6)
  "log1p\0" // IR(54874, 6)
  "logb\0" // IR(54880, 5)
  "mad\0" // IR(54885, 4)
  "maxmag\0" // IR(54889, 7)
  "minmag\0" // IR(54896, 7)
  "modf\0" // IR(54903, 5)
  "nan\0" // IR(54908, 4)
  "nextafter\0" // IR(54912, 10)
  "pow\0" // IR(54922, 4)
  "pown\0" // IR(54926, 5)
  "powr\0" // IR(54931, 5)
  "remainder\0" // IR(54936, 10)
  "remquo\0" // IR(54946, 7)
  "rint\0" // IR(54953, 5)
  "rootn\0" // IR(54958, 6)
  "round\0" // IR(54964, 6)
  "rsqrt\0" // IR(54970, 6)
  "sin\0" // IR(54976, 4)
  "sincos\0" // IR(54980, 7)
  "sinh\0" // IR(54987, 5)
  "sinpi\0" // IR(54992, 6)
  "sqrt\0" // IR(54998, 5)
  "tan\0" // IR(55003, 4)
  "tanh\0" // IR(55007, 5)
  "tanpi\0" // IR(55012, 6)
  "tgamma\0" // IR(55018, 7)
  "trunc\0" // IR(55025, 6)
  "half_cos\0" // IR(55031, 9)
  "half_divide\0" // IR(55040, 12)
  "half_exp\0" // IR(55052, 9)
  "half_exp2\0" // IR(55061, 10)
  "half_exp10\0" // IR(55071, 11)
  "half_log\0" // IR(55082, 9)
  "half_log2\0" // IR(55091, 10)
  "half_log10\0" // IR(55101, 11)
  "half_powr\0" // IR(55112, 10)
  "half_recip\0" // IR(55122, 11)
  "half_rsqrt\0" // IR(55133, 11)
  "half_sin\0" // IR(55144, 9)
  "half_sqrt\0" // IR(55153, 10)
  "half_tan\0" // IR(55163, 9)
  "native_cos\0" // IR(55172, 11)
  "native_divide\0" // IR(55183, 14)
  "native_exp\0" // IR(55197, 11)
  "native_exp2\0" // IR(55208, 12)
  "native_exp10\0" // IR(55220, 13)
  "native_log\0" // IR(55233, 11)
  "native_log2\0" // IR(55244, 12)
  "native_log10\0" // IR(55256, 13)
  "native_powr\0" // IR(55269, 12)
  "native_recip\0" // IR(55281, 13)
  "native_rsqrt\0" // IR(55294, 13)
  "native_sin\0" // IR(55307, 11)
  "native_sqrt\0" // IR(55318, 12)
  "native_tan\0" // IR(55330, 11)
  "fclamp\0" // IR(55341, 7)
  "degrees\0" // IR(55348, 8)
  "fmax_common\0" // IR(55356, 12)
  "fmin_common\0" // IR(55368, 12)
  "mix\0" // IR(55380, 4)
  "radians\0" // IR(55384, 8)
  "step\0" // IR(55392, 5)
  "smoothstep\0" // IR(55397, 11)
  "sign\0" // IR(55408, 5)
  "cross\0" // IR(55413, 6)
  "distance\0" // IR(55419, 9)
  "length\0" // IR(55428, 7)
  "normalize\0" // IR(55435, 10)
  "fast_distance\0" // IR(55445, 14)
  "fast_length\0" // IR(55459, 12)
  "fast_normalize\0" // IR(55471, 15)
  "s_abs\0" // IR(55486, 6)
  "s_abs_diff\0" // IR(55492, 11)
  "s_add_sat\0" // IR(55503, 10)
  "u_add_sat\0" // IR(55513, 10)
  "s_hadd\0" // IR(55523, 7)
  "u_hadd\0" // IR(55530, 7)
  "s_rhadd\0" // IR(55537, 8)
  "u_rhadd\0" // IR(55545, 8)
  "s_clamp\0" // IR(55553, 8)
  "u_clamp\0" // IR(55561, 8)
  "clz\0" // IR(55569, 4)
  "ctz\0" // IR(55573, 4)
  "s_mad_hi\0" // IR(55577, 9)
  "u_mad_sat\0" // IR(55586, 10)
  "s_mad_sat\0" // IR(55596, 10)
  "s_max\0" // IR(55606, 6)
  "u_max\0" // IR(55612, 6)
  "s_min\0" // IR(55618, 6)
  "u_min\0" // IR(55624, 6)
  "s_mul_hi\0" // IR(55630, 9)
  "rotate\0" // IR(55639, 7)
  "s_sub_sat\0" // IR(55646, 10)
  "u_sub_sat\0" // IR(55656, 10)
  "u_upsample\0" // IR(55666, 11)
  "s_upsample\0" // IR(55677, 11)
  "popcount\0" // IR(55688, 9)
  "s_mad24\0" // IR(55697, 8)
  "u_mad24\0" // IR(55705, 8)
  "s_mul24\0" // IR(55713, 8)
  "u_mul24\0" // IR(55721, 8)
  "vloadn\0" // IR(55729, 7)
  "vstoren\0" // IR(55736, 8)
  "vload_half\0" // IR(55744, 11)
  "vload_halfn\0" // IR(55755, 12)
  "vstore_half\0" // IR(55767, 12)
  "vstore_half_r\0" // IR(55779, 14)
  "vstore_halfn\0" // IR(55793, 13)
  "vstore_halfn_r\0" // IR(55806, 15)
  "vloada_halfn\0" // IR(55821, 13)
  "vstorea_halfn\0" // IR(55834, 14)
  "vstorea_halfn_r\0" // IR(55848, 16)
  "shuffle\0" // IR(55864, 8)
  "shuffle2\0" // IR(55872, 9)
  "printf\0" // IR(55881, 7)
  "prefetch\0" // IR(55888, 9)
  "bitselect\0" // IR(55897, 10)
  "select\0" // IR(55907, 7)
  "u_abs\0" // IR(55914, 6)
  "u_abs_diff\0" // IR(55920, 11)
  "u_mul_hi\0" // IR(55931, 9)
  "u_mad_hi\0" // IR(55940, 9)
  "CubeFaceIndexAMD\0" // IR(55949, 17)
  "CubeFaceCoordAMD\0" // IR(55966, 17)
  "TimeAMD\0" // IR(55983, 8)
  "SwizzleInvocationsAMD\0" // IR(55991, 22)
  "SwizzleInvocationsMaskedAMD\0" // IR(56013, 28)
  "WriteInvocationAMD\0" // IR(56041, 19)
  "MbcntAMD\0" // IR(56060, 9)
  "InterpolateAtVertexAMD\0" // IR(56069, 23)
  "FMin3AMD\0" // IR(56092, 9)
  "UMin3AMD\0" // IR(56101, 9)
  "SMin3AMD\0" // IR(56110, 9)
  "FMax3AMD\0" // IR(56119, 9)
  "UMax3AMD\0" // IR(56128, 9)
  "SMax3AMD\0" // IR(56137, 9)
  "FMid3AMD\0" // IR(56146, 9)
  "UMid3AMD\0" // IR(56155, 9)
  "SMid3AMD\0" // IR(56164, 9)
;

// Array of IndexRanges, where each represents a string by referencing
// the kStrings table.
// This array contains all sequences of alias strings used in the grammar.
// This table is referenced by an IndexRange elsewhere, i.e. by the 'aliases'
// field of an instruction or operand description.
static const IndexRange kAliasSpans[] = {
  IR(5808, 27), // 0 PhysicalStorageBuffer64EXT
  IR(6719, 18), // 1 SubgroupEqMaskKHR
  IR(6774, 18), // 2 SubgroupGeMaskKHR
  IR(6807, 18), // 3 SubgroupGtMaskKHR
  IR(6840, 18), // 4 SubgroupLeMaskKHR
  IR(6873, 18), // 5 SubgroupLtMaskKHR
  IR(7780, 12), // 6 BaryCoordNV
  IR(7835, 19), // 7 BaryCoordNoPerspNV
  IR(7866, 15), // 8 FragmentSizeNV
  IR(7923, 22), // 9 InvocationsPerPixelNV
  IR(8051, 11), // 10 LaunchIdNV
  IR(8076, 13), // 11 LaunchSizeNV
  IR(8107, 17), // 12 WorldRayOriginNV
  IR(8145, 20), // 13 WorldRayDirectionNV
  IR(8184, 18), // 14 ObjectRayOriginNV
  IR(8224, 21), // 15 ObjectRayDirectionNV
  IR(8256, 10), // 16 RayTminNV
  IR(8277, 10), // 17 RayTmaxNV
  IR(8310, 22), // 18 InstanceCustomIndexNV
  IR(8349, 16), // 19 ObjectToWorldNV
  IR(8382, 16), // 20 WorldToObjectNV
  IR(8416, 10), // 21 HitKindNV
  IR(8647, 19), // 22 IncomingRayFlagsNV
  IR(10423, 28), // 23 StorageUniformBufferBlock16
  IR(10486, 17), // 24 StorageUniform16
  IR(11357, 27), // 25 ShaderViewportIndexLayerNV
  IR(11401, 22), // 26 FragmentBarycentricNV
  IR(11454, 30), // 27 ComputeDerivativeGroupQuadsNV
  IR(11484, 14), // 28 ShadingRateNV
  IR(11528, 29), // 29 GroupNonUniformPartitionedNV
  IR(11574, 20), // 30 ShaderNonUniformEXT
  IR(11617, 26), // 31 RuntimeDescriptorArrayEXT
  IR(11679, 39), // 32 InputAttachmentArrayDynamicIndexingEXT
  IR(11757, 42), // 33 UniformTexelBufferArrayDynamicIndexingEXT
  IR(11838, 42), // 34 StorageTexelBufferArrayDynamicIndexingEXT
  IR(11917, 40), // 35 UniformBufferArrayNonUniformIndexingEXT
  IR(11993, 39), // 36 SampledImageArrayNonUniformIndexingEXT
  IR(12069, 40), // 37 StorageBufferArrayNonUniformIndexingEXT
  IR(12145, 39), // 38 StorageImageArrayNonUniformIndexingEXT
  IR(12223, 42), // 39 InputAttachmentArrayNonUniformIndexingEXT
  IR(12307, 45), // 40 UniformTexelBufferArrayNonUniformIndexingEXT
  IR(12394, 45), // 41 StorageTexelBufferArrayNonUniformIndexingEXT
  IR(12457, 21), // 42 VulkanMemoryModelKHR
  IR(12507, 32), // 43 VulkanMemoryModelDeviceScopeKHR
  IR(12539, 34), // 44 PhysicalStorageBufferAddressesEXT
  IR(12605, 31), // 45 ComputeDerivativeGroupLinearNV
  IR(12809, 28), // 46 DemoteToHelperInvocationEXT
  IR(12889, 29), // 47 RayTracingOpacityMicromapEXT
  IR(13911, 26), // 48 FPGAMemoryAttributesINTEL
  IR(13990, 32), // 49 ArbitraryPrecisionIntegersINTEL
  IR(14060, 37), // 50 ArbitraryPrecisionFloatingPointINTEL
  IR(14150, 22), // 51 FPGALoopControlsINTEL
  IR(14245, 24), // 52 FPGAMemoryAccessesINTEL
  IR(14297, 27), // 53 FPGAClusterAttributesINTEL
  IR(14339, 14), // 54 LoopFuseINTEL
  IR(14374, 20), // 55 FPGADSPControlINTEL
  IR(14461, 40), // 56 FPGAInvocationPipeliningAttributesINTEL
  IR(14526, 24), // 57 FPGABufferLocationINTEL
  IR(14585, 34), // 58 ArbitraryPrecisionFixedPointINTEL
  IR(14643, 23), // 59 USMStorageClassesINTEL
  IR(14696, 29), // 60 RuntimeAlignedAttributeINTEL
  IR(14739, 13), // 61 IOPipesINTEL
  IR(14772, 19), // 62 BlockingPipesINTEL
  IR(14805, 13), // 63 FPGARegINTEL
  IR(14837, 22), // 64 DotProductInputAllKHR
  IR(14881, 25), // 65 DotProductInput4x8BitKHR
  IR(14934, 31), // 66 DotProductInput4x8BitPackedKHR
  IR(14976, 14), // 67 DotProductKHR
  IR(15190, 13), // 68 OptNoneINTEL
  IR(15284, 18), // 69 SplitBarrierINTEL
  IR(15351, 29), // 70 FPGAClusterAttributesV2INTEL
  IR(15427, 18), // 71 TaskSequenceINTEL
  IR(15486, 24), // 72 FPGALatencyControlINTEL
  IR(15539, 28), // 73 FPGAArgumentInterfacesINTEL
  IR(15633, 35), // 74 GlobalVariableFPGADecorationsINTEL
  IR(18625, 15), // 75 PerPrimitiveNV
  IR(18673, 12), // 76 PerVertexNV
  IR(18696, 14), // 77 NonUniformEXT
  IR(18726, 19), // 78 RestrictPointerEXT
  IR(18760, 18), // 79 AliasedPointerEXT
  IR(19123, 24), // 80 HlslCounterBufferGOOGLE
  IR(19160, 19), // 81 HlslSemanticGOOGLE
  IR(19290, 14), // 82 RegisterINTEL
  IR(19317, 12), // 83 MemoryINTEL
  IR(19344, 14), // 84 NumbanksINTEL
  IR(19374, 15), // 85 BankwidthINTEL
  IR(19412, 22), // 86 MaxPrivateCopiesINTEL
  IR(19451, 16), // 87 SinglepumpINTEL
  IR(19484, 16), // 88 DoublepumpINTEL
  IR(19520, 19), // 89 MaxReplicatesINTEL
  IR(19560, 20), // 90 SimpleDualPortINTEL
  IR(19592, 11), // 91 MergeINTEL
  IR(19660, 14), // 92 BankBitsINTEL
  IR(19695, 20), // 93 ForcePow2DepthINTEL
  IR(19732, 16), // 94 StridesizeINTEL
  IR(19763, 14), // 95 WordsizeINTEL
  IR(19796, 18), // 96 TrueDualPortINTEL
  IR(19834, 19), // 97 BurstCoalesceINTEL
  IR(19869, 15), // 98 CacheSizeINTEL
  IR(19913, 28), // 99 DontStaticallyCoalesceINTEL
  IR(19956, 14), // 100 PrefetchINTEL
  IR(19988, 17), // 101 StallEnableINTEL
  IR(20031, 25), // 102 FuseLoopsInFunctionINTEL
  IR(20076, 19), // 103 MathOpDSPModeINTEL
  IR(20149, 24), // 104 InitiationIntervalINTEL
  IR(20194, 20), // 105 MaxConcurrencyINTEL
  IR(20235, 20), // 106 PipelineEnableINTEL
  IR(20276, 20), // 107 BufferLocationINTEL
  IR(20316, 19), // 108 IOPipeStorageINTEL
  IR(20494, 15), // 109 StallFreeINTEL
  IR(20592, 25), // 110 LatencyControlLabelINTEL
  IR(20648, 30), // 111 LatencyControlConstraintINTEL
  IR(20706, 27), // 112 ConduitKernelArgumentINTEL
  IR(20765, 31), // 113 RegisterMapKernelArgumentINTEL
  IR(20830, 33), // 114 MMHostInterfaceAddressWidthINTEL
  IR(20894, 30), // 115 MMHostInterfaceDataWidthINTEL
  IR(20953, 28), // 116 MMHostInterfaceLatencyINTEL
  IR(21050, 34), // 117 MMHostInterfaceReadWriteModeINTEL
  IR(21114, 29), // 118 MMHostInterfaceMaxBurstINTEL
  IR(21176, 32), // 119 MMHostInterfaceWaitRequestINTEL
  IR(21235, 26), // 120 StableKernelArgumentINTEL
  IR(21378, 14), // 121 InitModeINTEL
  IR(21421, 28), // 122 ImplementInRegisterMapINTEL
  IR(22775, 14), // 123 OutputLinesNV
  IR(22809, 19), // 124 OutputPrimitivesNV
  IR(22852, 23), // 125 DerivativeGroupQuadsNV
  IR(22900, 24), // 126 DerivativeGroupLinearNV
  IR(22943, 18), // 127 OutputTrianglesNV
  IR(23712, 16), // 128 RayGenerationNV
  IR(23744, 15), // 129 IntersectionNV
  IR(23769, 9), // 130 AnyHitNV
  IR(23792, 13), // 131 ClosestHitNV
  IR(23813, 7), // 132 MissNV
  IR(23832, 11), // 133 CallableNV
  IR(23977, 23), // 134 AllowContractFastINTEL
  IR(24013, 18), // 135 AllowReassocINTEL
  IR(24239, 20), // 136 RuntimeAlignedINTEL
  IR(24331, 20), // 137 PartitionedReduceNV
  IR(24379, 27), // 138 PartitionedInclusiveScanNV
  IR(24434, 27), // 139 PartitionedExclusiveScanNV
  IR(24565, 22), // 140 MakeTexelAvailableKHR
  IR(24604, 20), // 141 MakeTexelVisibleKHR
  IR(24640, 19), // 142 NonPrivateTexelKHR
  IR(24673, 17), // 143 VolatileTexelKHR
  IR(25232, 27), // 144 InitOnDeviceReprogramINTEL
  IR(25283, 23), // 145 InitOnDeviceResetINTEL
  IR(25625, 21), // 146 DependencyArrayINTEL
  IR(25665, 18), // 147 LoopCoalesceINTEL
  IR(25705, 21), // 148 MaxInterleavingINTEL
  IR(25753, 26), // 149 SpeculatedIterationsINTEL
  IR(25794, 14), // 150 NoFusionINTEL
  IR(25824, 15), // 151 LoopCountINTEL
  IR(25866, 26), // 152 MaxReinvocationDelayINTEL
  IR(26258, 24), // 153 MakePointerAvailableKHR
  IR(26301, 22), // 154 MakePointerVisibleKHR
  IR(26341, 21), // 155 NonPrivatePointerKHR
  IR(26428, 10), // 156 VulkanKHR
  IR(16354, 5), // 157 None
  IR(26611, 16), // 158 OutputMemoryKHR
  IR(26641, 17), // 159 MakeAvailableKHR
  IR(26670, 15), // 160 MakeVisibleKHR
  IR(26746, 28), // 161 PackedVectorFormat4x8BitKHR
  IR(27061, 24), // 162 SkipBuiltinPrimitivesNV
  IR(27128, 30), // 163 ForceOpacityMicromap2StateEXT
  IR(27831, 15), // 164 QueueFamilyKHR
  IR(28207, 15), // 165 CallableDataNV
  IR(28246, 23), // 166 IncomingCallableDataNV
  IR(28283, 13), // 167 RayPayloadNV
  IR(28312, 15), // 168 HitAttributeNV
  IR(28349, 21), // 169 IncomingRayPayloadNV
  IR(28392, 21), // 170 ShaderRecordBufferNV
  IR(28435, 25), // 171 PhysicalStorageBufferEXT
  IR(28561, 16), // 172 DeviceOnlyINTEL
  IR(28592, 14), // 173 HostOnlyINTEL
  IR(35847, 8), // 174 SDotKHR
  IR(35860, 8), // 175 UDotKHR
  IR(35874, 9), // 176 SUDotKHR
  IR(35894, 14), // 177 SDotAccSatKHR
  IR(35919, 14), // 178 UDotAccSatKHR
  IR(35945, 15), // 179 SUDotAccSatKHR
  IR(38246, 24), // 180 TypeCooperativeVectorNV
  IR(38502, 27), // 181 GroupNonUniformPartitionNV
  IR(39584, 21), // 182 ReportIntersectionNV
  IR(39759, 28), // 183 TypeAccelerationStructureNV
  IR(39840, 23), // 184 RayQueryGetClusterIdNV
  IR(42008, 21), // 185 DecorateStringGOOGLE
  IR(42050, 27), // 186 MemberDecorateStringGOOGLE
  IR(47307, 28), // 187 ArbitraryFloatSinCosPiINTEL
  IR(47360, 24), // 188 ArbitraryFloatCastINTEL
  IR(47416, 31), // 189 ArbitraryFloatCastFromIntINTEL
  IR(47477, 29), // 190 ArbitraryFloatCastToIntINTEL
  IR(47530, 23), // 191 ArbitraryFloatAddINTEL
  IR(47577, 23), // 192 ArbitraryFloatSubINTEL
  IR(47624, 23), // 193 ArbitraryFloatMulINTEL
  IR(47671, 23), // 194 ArbitraryFloatDivINTEL
  IR(47717, 22), // 195 ArbitraryFloatGTINTEL
  IR(47762, 22), // 196 ArbitraryFloatGEINTEL
  IR(47807, 22), // 197 ArbitraryFloatLTINTEL
  IR(47852, 22), // 198 ArbitraryFloatLEINTEL
  IR(47897, 22), // 199 ArbitraryFloatEQINTEL
  IR(47945, 25), // 200 ArbitraryFloatRecipINTEL
  IR(47996, 25), // 201 ArbitraryFloatRSqrtINTEL
  IR(48046, 24), // 202 ArbitraryFloatCbrtINTEL
  IR(48096, 25), // 203 ArbitraryFloatHypotINTEL
  IR(48146, 24), // 204 ArbitraryFloatSqrtINTEL
  IR(48830, 15), // 205 FixedSqrtINTEL
  IR(48862, 16), // 206 FixedRecipINTEL
  IR(48895, 16), // 207 FixedRsqrtINTEL
  IR(48926, 14), // 208 FixedSinINTEL
  IR(48955, 14), // 209 FixedCosINTEL
  IR(48987, 17), // 210 FixedSinCosINTEL
  IR(49021, 16), // 211 FixedSinPiINTEL
  IR(49054, 16), // 212 FixedCosPiINTEL
  IR(49090, 19), // 213 FixedSinCosPiINTEL
  IR(49124, 14), // 214 FixedLogINTEL
  IR(49153, 14), // 215 FixedExpINTEL
  IR(49197, 29), // 216 PtrCastToCrossWorkgroupINTEL
  IR(49256, 29), // 217 CrossWorkgroupCastToPtrINTEL
  IR(49308, 22), // 218 ReadPipeBlockingINTEL
  IR(49354, 23), // 219 WritePipeBlockingINTEL
  IR(50255, 26), // 220 ControlBarrierArriveINTEL
  IR(50303, 24), // 221 ControlBarrierWaitINTEL
  IR(50352, 24), // 222 TaskSequenceCreateINTEL
  IR(50400, 23), // 223 TaskSequenceAsyncINTEL
  IR(50445, 21), // 224 TaskSequenceGetINTEL
  IR(50492, 25), // 225 TaskSequenceReleaseINTEL
  IR(50540, 22), // 226 TypeTaskSequenceINTEL
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
  spv::Capability::VectorComputeINTEL, // 136
  spv::Capability::IndirectReferencesINTEL, // 137
  spv::Capability::AsmINTEL, // 138
  spv::Capability::FunctionFloatControlINTEL, // 139
  spv::Capability::FPGAMemoryAttributesALTERA, // 140
  spv::Capability::FPGAMemoryAccessesALTERA, // 141
  spv::Capability::LoopFuseALTERA, // 142
  spv::Capability::FPGADSPControlALTERA, // 143
  spv::Capability::MemoryAccessAliasingINTEL, // 144
  spv::Capability::FPGAInvocationPipeliningAttributesALTERA, // 145
  spv::Capability::FPGABufferLocationALTERA, // 146
  spv::Capability::IOPipesALTERA, // 147
  spv::Capability::FPGAClusterAttributesV2ALTERA, // 148
  spv::Capability::FPMaxErrorINTEL, // 149
  spv::Capability::FPGALatencyControlALTERA, // 150
  spv::Capability::FPGAArgumentInterfacesALTERA, // 151
  spv::Capability::GlobalVariableHostAccessINTEL, // 152
  spv::Capability::GlobalVariableFPGADecorationsALTERA, // 153
  spv::Capability::CacheControlsINTEL, // 154
  spv::Capability::TileImageColorReadAccessEXT, // 155
  spv::Capability::Geometry, // 156
  spv::Capability::Tessellation, // 157
  spv::Capability::MeshShadingNV, // 158
  spv::Capability::MeshShadingEXT, // 159
  spv::Capability::Geometry, // 160
  spv::Capability::MeshShadingNV, // 161
  spv::Capability::MeshShadingEXT, // 162
  spv::Capability::SubgroupDispatch, // 163
  spv::Capability::TileImageDepthReadAccessEXT, // 164
  spv::Capability::TileImageStencilReadAccessEXT, // 165
  spv::Capability::SampleMaskPostDepthCoverage, // 166
  spv::Capability::DenormPreserve, // 167
  spv::Capability::DenormFlushToZero, // 168
  spv::Capability::SignedZeroInfNanPreserve, // 169
  spv::Capability::RoundingModeRTE, // 170
  spv::Capability::RoundingModeRTZ, // 171
  spv::Capability::QuadControlKHR, // 172
  spv::Capability::PoisonFreezeKHR, // 173
  spv::Capability::ComputeDerivativeGroupQuadsKHR, // 174
  spv::Capability::ComputeDerivativeGroupLinearKHR, // 175
  spv::Capability::FragmentShaderPixelInterlockEXT, // 176
  spv::Capability::FragmentShaderSampleInterlockEXT, // 177
  spv::Capability::FragmentShaderShadingRateInterlockEXT, // 178
  spv::Capability::Shader64BitIndexingEXT, // 179
  spv::Capability::RoundToInfinityINTEL, // 180
  spv::Capability::KernelAttributesINTEL, // 181
  spv::Capability::FloatControls2, // 182
  spv::Capability::RayTracingOpacityMicromapExecutionModeKHR, // 183
  spv::Capability::FPGAKernelAttributesv2INTEL, // 184
  spv::Capability::RegisterLimitsINTEL, // 185
  spv::Capability::FloatControls2, // 186
  spv::Capability::FPFastMathModeINTEL, // 187
  spv::Capability::OptNoneEXT, // 188
  spv::Capability::RuntimeAlignedAttributeALTERA, // 189
  spv::Capability::Kernel, // 190
  spv::Capability::GroupNonUniformArithmetic, // 191
  spv::Capability::GroupNonUniformBallot, // 192
  spv::Capability::GroupNonUniformClustered, // 193
  spv::Capability::GroupNonUniformPartitionedEXT, // 194
  spv::Capability::ImageGatherExtended, // 195
  spv::Capability::MinLod, // 196
  spv::Capability::VulkanMemoryModel, // 197
  spv::Capability::WeakLinkageAMD, // 198
  spv::Capability::FPGALoopControlsALTERA, // 199
  spv::Capability::ArbitraryPrecisionFixedPointALTERA, // 200
  spv::Capability::RawAccessChainsNV, // 201
  spv::Capability::RayTraversalPrimitiveCullingKHR, // 202
  spv::Capability::RayTracingOpacityMicromapKHR, // 203
  spv::Capability::RayQueryKHR, // 204
  spv::Capability::StorageImageExtendedFormats, // 205
  spv::Capability::Int64ImageEXT, // 206
  spv::Capability::Shader, // 207
  spv::Capability::VectorComputeINTEL, // 208
  spv::Capability::GenericPointer, // 209
  spv::Capability::FunctionPointersINTEL, // 210
  spv::Capability::USMStorageClassesALTERA, // 211
  spv::Capability::CooperativeMatrixTensorAddressingNV, // 212
  spv::Capability::CooperativeMatrixDecodeVectorNV, // 213
  spv::Capability::TensorsARM, // 214
  spv::Capability::Addresses, // 215
  spv::Capability::PhysicalStorageBufferAddresses, // 216
  spv::Capability::LiteralSampler, // 217
  spv::Capability::Addresses, // 218
  spv::Capability::UntypedPointersKHR, // 219
  spv::Capability::Addresses, // 220
  spv::Capability::VariablePointers, // 221
  spv::Capability::VariablePointersStorageBuffer, // 222
  spv::Capability::PhysicalStorageBufferAddresses, // 223
  spv::Capability::Kernel, // 224
  spv::Capability::ImageQuery, // 225
  spv::Capability::ImageQuery, // 226
  spv::Capability::Shader, // 227
  spv::Capability::BitInstructions, // 228
  spv::Capability::DerivativeControl, // 229
  spv::Capability::Groups, // 230
  spv::Capability::SparseResidency, // 231
  spv::Capability::PipeStorage, // 232
  spv::Capability::NamedBarrier, // 233
  spv::Capability::GroupNonUniformVote, // 234
  spv::Capability::GroupNonUniformBallot, // 235
  spv::Capability::GroupNonUniformShuffle, // 236
  spv::Capability::GroupNonUniformShuffleRelative, // 237
  spv::Capability::GroupNonUniformArithmetic, // 238
  spv::Capability::GroupNonUniformClustered, // 239
  spv::Capability::GroupNonUniformPartitionedEXT, // 240
  spv::Capability::GroupNonUniformQuad, // 241
  spv::Capability::Addresses, // 242
  spv::Capability::VariablePointers, // 243
  spv::Capability::VariablePointersStorageBuffer, // 244
  spv::Capability::GraphARM, // 245
  spv::Capability::SubgroupBallotKHR, // 246
  spv::Capability::FMAKHR, // 247
  spv::Capability::SubgroupVoteKHR, // 248
  spv::Capability::GroupNonUniformRotateKHR, // 249
  spv::Capability::RayTracingKHR, // 250
  spv::Capability::RayQueryKHR, // 251
  spv::Capability::DotProduct, // 252
  spv::Capability::ReplicatedCompositesEXT, // 253
  spv::Capability::TextureSampleWeightedQCOM, // 254
  spv::Capability::TextureBoxFilterQCOM, // 255
  spv::Capability::TextureBlockMatchQCOM, // 256
  spv::Capability::CooperativeMatrixConversionQCOM, // 257
  spv::Capability::TextureBlockMatch2QCOM, // 258
  spv::Capability::FragmentMaskAMD, // 259
  spv::Capability::ShaderClockKHR, // 260
  spv::Capability::AbortKHR, // 261
  spv::Capability::ShaderInvocationReorderNV, // 262
  spv::Capability::RayTracingMotionBlurNV, // 263
  spv::Capability::ImageFootprintNV, // 264
  spv::Capability::CooperativeVectorNV, // 265
  spv::Capability::LongVectorEXT, // 266
  spv::Capability::CooperativeVectorNV, // 267
  spv::Capability::CooperativeVectorTrainingNV, // 268
  spv::Capability::CooperativeMatrixConversionsNV, // 269
  spv::Capability::DisplacementMicromapNV, // 270
  spv::Capability::ShaderInvocationReorderEXT, // 271
  spv::Capability::RayTracingMotionBlurNV, // 272
  spv::Capability::RayQueryPositionFetchKHR, // 273
  spv::Capability::RayTracingNV, // 274
  spv::Capability::RayTracingKHR, // 275
  spv::Capability::RayQueryKHR, // 276
  spv::Capability::DisplacementMicromapNV, // 277
  spv::Capability::CooperativeMatrixNV, // 278
  spv::Capability::FragmentShaderSampleInterlockEXT, // 279
  spv::Capability::FragmentShaderPixelInterlockEXT, // 280
  spv::Capability::FragmentShaderShadingRateInterlockEXT, // 281
  spv::Capability::CooperativeMatrixReductionsNV, // 282
  spv::Capability::CooperativeMatrixPerElementOperationsNV, // 283
  spv::Capability::TensorAddressingNV, // 284
  spv::Capability::DemoteToHelperInvocation, // 285
  spv::Capability::SubgroupShuffleINTEL, // 286
  spv::Capability::SubgroupBufferBlockIOINTEL, // 287
  spv::Capability::SubgroupImageBlockIOINTEL, // 288
  spv::Capability::SubgroupImageMediaBlockIOINTEL, // 289
  spv::Capability::IntegerFunctions2INTEL, // 290
  spv::Capability::AtomicFloat16MinMaxEXT, // 291
  spv::Capability::AtomicFloat32MinMaxEXT, // 292
  spv::Capability::AtomicFloat64MinMaxEXT, // 293
  spv::Capability::AtomicFloat16VectorNV, // 294
  spv::Capability::ExpectAssumeKHR, // 295
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 296
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 297
  spv::Capability::SubgroupAvcMotionEstimationIntraINTEL, // 298
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 299
  spv::Capability::SubgroupAvcMotionEstimationChromaINTEL, // 300
  spv::Capability::VariableLengthArrayINTEL, // 301
  spv::Capability::ArbitraryPrecisionFloatingPointALTERA, // 302
  spv::Capability::UnstructuredLoopControlsINTEL, // 303
  spv::Capability::BlockingPipesALTERA, // 304
  spv::Capability::FPGARegALTERA, // 305
  spv::Capability::AtomicFloat16AddEXT, // 306
  spv::Capability::AtomicFloat32AddEXT, // 307
  spv::Capability::AtomicFloat64AddEXT, // 308
  spv::Capability::AtomicFloat16VectorNV, // 309
  spv::Capability::LongCompositesINTEL, // 310
  spv::Capability::BFloat16ConversionINTEL, // 311
  spv::Capability::SplitBarrierEXT, // 312
  spv::Capability::ArithmeticFenceEXT, // 313
  spv::Capability::TaskSequenceALTERA, // 314
  spv::Capability::SubgroupBufferPrefetchINTEL, // 315
  spv::Capability::Subgroup2DBlockTransformINTEL, // 316
  spv::Capability::Subgroup2DBlockTransposeINTEL, // 317
  spv::Capability::SubgroupMatrixMultiplyAccumulateINTEL, // 318
  spv::Capability::TernaryBitwiseFunctionINTEL, // 319
  spv::Capability::UntypedVariableLengthArrayINTEL, // 320
  spv::Capability::FunctionVariantsINTEL, // 321
  spv::Capability::PredicatedIOINTEL, // 322
  spv::Capability::GroupUniformArithmeticKHR, // 323
  spv::Capability::TensorFloat32RoundingINTEL, // 324
  spv::Capability::MaskedGatherScatterINTEL, // 325
  spv::Capability::BindlessImagesINTEL, // 326
  spv::Capability::DotProductFloat16AccFloat32VALVE, // 327
  spv::Capability::DotProductBFloat16AccVALVE, // 328
  spv::Capability::DotProductFloat16AccFloat16VALVE, // 329
  spv::Capability::DotProductBFloat16AccVALVE, // 330
  spv::Capability::DotProductFloat8AccFloat32VALVE, // 331
  spv::Capability::Float64, // 332
  spv::Capability::InterpolationFunction, // 333
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
  spvtools::Extension::kSPV_KHR_abort, // 66
  spvtools::Extension::kSPV_EXT_descriptor_heap, // 67
  spvtools::Extension::kSPV_KHR_constant_data, // 68
  spvtools::Extension::kSPV_KHR_poison_freeze, // 69
  spvtools::Extension::kSPV_AMD_weak_linkage, // 70
  spvtools::Extension::kSPV_NV_sample_mask_override_coverage, // 71
  spvtools::Extension::kSPV_NV_geometry_shader_passthrough, // 72
  spvtools::Extension::kSPV_EXT_shader_viewport_index_layer, // 73
  spvtools::Extension::kSPV_NV_viewport_array2, // 74
  spvtools::Extension::kSPV_NV_viewport_array2, // 75
  spvtools::Extension::kSPV_NVX_multiview_per_view_attributes, // 76
  spvtools::Extension::kSPV_NV_shader_image_footprint, // 77
  spvtools::Extension::kSPV_NV_compute_shader_derivatives, // 78
  spvtools::Extension::kSPV_KHR_compute_shader_derivatives, // 79
  spvtools::Extension::kSPV_NV_shader_subgroup_partitioned, // 80
  spvtools::Extension::kSPV_EXT_shader_subgroup_partitioned, // 81
  spvtools::Extension::kSPV_EXT_descriptor_indexing, // 82
  spvtools::Extension::kSPV_KHR_ray_tracing_position_fetch, // 83
  spvtools::Extension::kSPV_KHR_vulkan_memory_model, // 84
  spvtools::Extension::kSPV_NV_cooperative_matrix, // 85
  spvtools::Extension::kSPV_EXT_fragment_shader_interlock, // 86
  spvtools::Extension::kSPV_EXT_demote_to_helper_invocation, // 87
  spvtools::Extension::kSPV_NV_displacement_micromap, // 88
  spvtools::Extension::kSPV_KHR_opacity_micromap, // 89
  spvtools::Extension::kSPV_EXT_opacity_micromap, // 90
  spvtools::Extension::kSPV_NV_shader_invocation_reorder, // 91
  spvtools::Extension::kSPV_EXT_shader_invocation_reorder, // 92
  spvtools::Extension::kSPV_NV_bindless_texture, // 93
  spvtools::Extension::kSPV_NV_cooperative_vector, // 94
  spvtools::Extension::kSPV_NV_shader_atomic_fp16_vector, // 95
  spvtools::Extension::kSPV_NV_raw_access_chains, // 96
  spvtools::Extension::kSPV_NV_push_constant_bank, // 97
  spvtools::Extension::kSPV_EXT_long_vector, // 98
  spvtools::Extension::kSPV_EXT_shader_64bit_indexing, // 99
  spvtools::Extension::kSPV_NV_cooperative_matrix2, // 100
  spvtools::Extension::kSPV_NV_tensor_addressing, // 101
  spvtools::Extension::kSPV_NV_cooperative_matrix_decode_vector, // 102
  spvtools::Extension::kSPV_INTEL_subgroups, // 103
  spvtools::Extension::kSPV_INTEL_media_block_io, // 104
  spvtools::Extension::kSPV_INTEL_float_controls2, // 105
  spvtools::Extension::kSPV_INTEL_shader_integer_functions2, // 106
  spvtools::Extension::kSPV_INTEL_function_pointers, // 107
  spvtools::Extension::kSPV_INTEL_inline_assembly, // 108
  spvtools::Extension::kSPV_EXT_shader_atomic_float_min_max, // 109
  spvtools::Extension::kSPV_INTEL_vector_compute, // 110
  spvtools::Extension::kSPV_KHR_expect_assume, // 111
  spvtools::Extension::kSPV_INTEL_device_side_avc_motion_estimation, // 112
  spvtools::Extension::kSPV_INTEL_variable_length_array, // 113
  spvtools::Extension::kSPV_ALTERA_fpga_memory_attributes, // 114
  spvtools::Extension::kSPV_INTEL_fpga_memory_attributes, // 115
  spvtools::Extension::kSPV_INTEL_fp_fast_math_mode, // 116
  spvtools::Extension::kSPV_ALTERA_arbitrary_precision_integers, // 117
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_integers, // 118
  spvtools::Extension::kSPV_ALTERA_arbitrary_precision_floating_point, // 119
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_floating_point, // 120
  spvtools::Extension::kSPV_INTEL_unstructured_loop_controls, // 121
  spvtools::Extension::kSPV_ALTERA_fpga_loop_controls, // 122
  spvtools::Extension::kSPV_INTEL_fpga_loop_controls, // 123
  spvtools::Extension::kSPV_INTEL_kernel_attributes, // 124
  spvtools::Extension::kSPV_ALTERA_fpga_memory_accesses, // 125
  spvtools::Extension::kSPV_INTEL_fpga_memory_accesses, // 126
  spvtools::Extension::kSPV_ALTERA_fpga_cluster_attributes, // 127
  spvtools::Extension::kSPV_INTEL_fpga_cluster_attributes, // 128
  spvtools::Extension::kSPV_ALTERA_loop_fuse, // 129
  spvtools::Extension::kSPV_INTEL_loop_fuse, // 130
  spvtools::Extension::kSPV_ALTERA_fpga_dsp_control, // 131
  spvtools::Extension::kSPV_INTEL_fpga_dsp_control, // 132
  spvtools::Extension::kSPV_INTEL_memory_access_aliasing, // 133
  spvtools::Extension::kSPV_ALTERA_fpga_invocation_pipelining_attributes, // 134
  spvtools::Extension::kSPV_INTEL_fpga_invocation_pipelining_attributes, // 135
  spvtools::Extension::kSPV_ALTERA_fpga_buffer_location, // 136
  spvtools::Extension::kSPV_INTEL_fpga_buffer_location, // 137
  spvtools::Extension::kSPV_ALTERA_arbitrary_precision_fixed_point, // 138
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_fixed_point, // 139
  spvtools::Extension::kSPV_ALTERA_usm_storage_classes, // 140
  spvtools::Extension::kSPV_INTEL_usm_storage_classes, // 141
  spvtools::Extension::kSPV_ALTERA_runtime_aligned, // 142
  spvtools::Extension::kSPV_INTEL_runtime_aligned, // 143
  spvtools::Extension::kSPV_ALTERA_io_pipes, // 144
  spvtools::Extension::kSPV_INTEL_io_pipes, // 145
  spvtools::Extension::kSPV_ALTERA_blocking_pipes, // 146
  spvtools::Extension::kSPV_INTEL_blocking_pipes, // 147
  spvtools::Extension::kSPV_ALTERA_fpga_reg, // 148
  spvtools::Extension::kSPV_INTEL_fpga_reg, // 149
  spvtools::Extension::kSPV_KHR_integer_dot_product, // 150
  spvtools::Extension::kSPV_KHR_cooperative_matrix, // 151
  spvtools::Extension::kSPV_EXT_replicated_composites, // 152
  spvtools::Extension::kSPV_KHR_bit_instructions, // 153
  spvtools::Extension::kSPV_KHR_subgroup_rotate, // 154
  spvtools::Extension::kSPV_KHR_float_controls2, // 155
  spvtools::Extension::kSPV_KHR_fma, // 156
  spvtools::Extension::kSPV_KHR_opacity_micromap, // 157
  spvtools::Extension::kSPV_EXT_shader_atomic_float_add, // 158
  spvtools::Extension::kSPV_INTEL_long_composites, // 159
  spvtools::Extension::kSPV_EXT_optnone, // 160
  spvtools::Extension::kSPV_INTEL_optnone, // 161
  spvtools::Extension::kSPV_EXT_shader_atomic_float16_add, // 162
  spvtools::Extension::kSPV_INTEL_debug_module, // 163
  spvtools::Extension::kSPV_INTEL_bfloat16_conversion, // 164
  spvtools::Extension::kSPV_EXT_split_barrier, // 165
  spvtools::Extension::kSPV_INTEL_split_barrier, // 166
  spvtools::Extension::kSPV_EXT_arithmetic_fence, // 167
  spvtools::Extension::kSPV_ALTERA_task_sequence, // 168
  spvtools::Extension::kSPV_INTEL_task_sequence, // 169
  spvtools::Extension::kSPV_INTEL_fp_max_error, // 170
  spvtools::Extension::kSPV_ALTERA_fpga_latency_control, // 171
  spvtools::Extension::kSPV_INTEL_fpga_latency_control, // 172
  spvtools::Extension::kSPV_ALTERA_fpga_argument_interfaces, // 173
  spvtools::Extension::kSPV_INTEL_fpga_argument_interfaces, // 174
  spvtools::Extension::kSPV_INTEL_global_variable_host_access, // 175
  spvtools::Extension::kSPV_ALTERA_global_variable_fpga_decorations, // 176
  spvtools::Extension::kSPV_INTEL_global_variable_fpga_decorations, // 177
  spvtools::Extension::kSPV_INTEL_subgroup_buffer_prefetch, // 178
  spvtools::Extension::kSPV_INTEL_2d_block_io, // 179
  spvtools::Extension::kSPV_INTEL_subgroup_matrix_multiply_accumulate, // 180
  spvtools::Extension::kSPV_INTEL_ternary_bitwise_function, // 181
  spvtools::Extension::kSPV_INTEL_function_variants, // 182
  spvtools::Extension::kSPV_INTEL_predicated_io, // 183
  spvtools::Extension::kSPV_INTEL_rounded_divide_sqrt, // 184
  spvtools::Extension::kSPV_KHR_uniform_group_instructions, // 185
  spvtools::Extension::kSPV_INTEL_tensor_float32_conversion, // 186
  spvtools::Extension::kSPV_INTEL_masked_gather_scatter, // 187
  spvtools::Extension::kSPV_INTEL_cache_controls, // 188
  spvtools::Extension::kSPV_INTEL_maximum_registers, // 189
  spvtools::Extension::kSPV_INTEL_bindless_images, // 190
  spvtools::Extension::kSPV_VALVE_mixed_float_dot_product, // 191
  spvtools::Extension::kSPV_KHR_no_integer_wrap_decoration, // 192
  spvtools::Extension::kSPV_NV_mesh_shader, // 193
  spvtools::Extension::kSPV_EXT_mesh_shader, // 194
  spvtools::Extension::kSPV_GOOGLE_hlsl_functionality1, // 195
  spvtools::Extension::kSPV_GOOGLE_user_type, // 196
  spvtools::Extension::kSPV_KHR_subgroup_uniform_control_flow, // 197
  spvtools::Extension::kSPV_AMD_shader_early_and_late_fragment_tests, // 198
  spvtools::Extension::kSPV_AMD_shader_early_and_late_fragment_tests, // 199
  spvtools::Extension::kSPV_EXT_shader_stencil_export, // 200
  spvtools::Extension::kSPV_KHR_maximal_reconvergence, // 201
  spvtools::Extension::kSPV_KHR_linkonce_odr, // 202
  spvtools::Extension::kSPV_KHR_storage_buffer_storage_class, // 203
  spvtools::Extension::kSPV_KHR_variable_pointers, // 204
  spvtools::Extension::kSPV_KHR_terminate_invocation, // 205
  spvtools::Extension::kSPV_KHR_relaxed_extended_instruction, // 206
  spvtools::Extension::kSPV_KHR_ray_tracing, // 207
  spvtools::Extension::kSPV_KHR_ray_query, // 208
  spvtools::Extension::kSPV_NV_ray_tracing, // 209
  spvtools::Extension::kSPV_KHR_ray_tracing, // 210
  spvtools::Extension::kSPV_KHR_ray_query, // 211
  spvtools::Extension::kSPV_NV_displacement_micromap, // 212
  spvtools::Extension::kSPV_GOOGLE_decorate_string, // 213
  spvtools::Extension::kSPV_GOOGLE_hlsl_functionality1, // 214
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
  SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER, // 481
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
  SPV_OPERAND_TYPE_ID, // 532
  SPV_OPERAND_TYPE_ID, // 533
  SPV_OPERAND_TYPE_ID, // 534
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 535
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 536
  SPV_OPERAND_TYPE_TYPE_ID, // 537
  SPV_OPERAND_TYPE_RESULT_ID, // 538
  SPV_OPERAND_TYPE_ID, // 539
  SPV_OPERAND_TYPE_ID, // 540
  SPV_OPERAND_TYPE_ID, // 541
  SPV_OPERAND_TYPE_ID, // 542
  SPV_OPERAND_TYPE_OPTIONAL_IMAGE, // 543
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
