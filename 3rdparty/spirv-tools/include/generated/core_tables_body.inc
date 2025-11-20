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
    case Extension::kSPV_EXT_mesh_shader: return IR(1312, 20);
    case Extension::kSPV_EXT_opacity_micromap: return IR(1332, 25);
    case Extension::kSPV_EXT_optnone: return IR(1357, 16);
    case Extension::kSPV_EXT_physical_storage_buffer: return IR(1373, 32);
    case Extension::kSPV_EXT_relaxed_printf_string_address_space: return IR(1405, 44);
    case Extension::kSPV_EXT_replicated_composites: return IR(1449, 30);
    case Extension::kSPV_EXT_shader_64bit_indexing: return IR(1479, 30);
    case Extension::kSPV_EXT_shader_atomic_float16_add: return IR(1509, 34);
    case Extension::kSPV_EXT_shader_atomic_float_add: return IR(1543, 32);
    case Extension::kSPV_EXT_shader_atomic_float_min_max: return IR(1575, 36);
    case Extension::kSPV_EXT_shader_image_int64: return IR(1611, 27);
    case Extension::kSPV_EXT_shader_invocation_reorder: return IR(1638, 34);
    case Extension::kSPV_EXT_shader_stencil_export: return IR(1672, 30);
    case Extension::kSPV_EXT_shader_tile_image: return IR(1702, 26);
    case Extension::kSPV_EXT_shader_viewport_index_layer: return IR(1728, 36);
    case Extension::kSPV_GOOGLE_decorate_string: return IR(1764, 27);
    case Extension::kSPV_GOOGLE_hlsl_functionality1: return IR(1791, 31);
    case Extension::kSPV_GOOGLE_user_type: return IR(1822, 21);
    case Extension::kSPV_INTEL_2d_block_io: return IR(1843, 22);
    case Extension::kSPV_INTEL_arbitrary_precision_fixed_point: return IR(1865, 42);
    case Extension::kSPV_INTEL_arbitrary_precision_floating_point: return IR(1907, 45);
    case Extension::kSPV_INTEL_arbitrary_precision_integers: return IR(1952, 39);
    case Extension::kSPV_INTEL_bfloat16_conversion: return IR(1991, 30);
    case Extension::kSPV_INTEL_bindless_images: return IR(2021, 26);
    case Extension::kSPV_INTEL_blocking_pipes: return IR(2047, 25);
    case Extension::kSPV_INTEL_cache_controls: return IR(2072, 25);
    case Extension::kSPV_INTEL_debug_module: return IR(2097, 23);
    case Extension::kSPV_INTEL_device_side_avc_motion_estimation: return IR(2120, 44);
    case Extension::kSPV_INTEL_float_controls2: return IR(2164, 26);
    case Extension::kSPV_INTEL_fp_fast_math_mode: return IR(2190, 28);
    case Extension::kSPV_INTEL_fp_max_error: return IR(2218, 23);
    case Extension::kSPV_INTEL_fpga_argument_interfaces: return IR(2241, 35);
    case Extension::kSPV_INTEL_fpga_buffer_location: return IR(2276, 31);
    case Extension::kSPV_INTEL_fpga_cluster_attributes: return IR(2307, 34);
    case Extension::kSPV_INTEL_fpga_dsp_control: return IR(2341, 27);
    case Extension::kSPV_INTEL_fpga_invocation_pipelining_attributes: return IR(2368, 48);
    case Extension::kSPV_INTEL_fpga_latency_control: return IR(2416, 31);
    case Extension::kSPV_INTEL_fpga_loop_controls: return IR(2447, 29);
    case Extension::kSPV_INTEL_fpga_memory_accesses: return IR(2476, 31);
    case Extension::kSPV_INTEL_fpga_memory_attributes: return IR(2507, 33);
    case Extension::kSPV_INTEL_fpga_reg: return IR(2540, 19);
    case Extension::kSPV_INTEL_function_pointers: return IR(2559, 28);
    case Extension::kSPV_INTEL_function_variants: return IR(2587, 28);
    case Extension::kSPV_INTEL_global_variable_fpga_decorations: return IR(2615, 43);
    case Extension::kSPV_INTEL_global_variable_host_access: return IR(2658, 38);
    case Extension::kSPV_INTEL_inline_assembly: return IR(2696, 26);
    case Extension::kSPV_INTEL_int4: return IR(2722, 15);
    case Extension::kSPV_INTEL_io_pipes: return IR(2737, 19);
    case Extension::kSPV_INTEL_kernel_attributes: return IR(2756, 28);
    case Extension::kSPV_INTEL_long_composites: return IR(2784, 26);
    case Extension::kSPV_INTEL_loop_fuse: return IR(2810, 20);
    case Extension::kSPV_INTEL_masked_gather_scatter: return IR(2830, 32);
    case Extension::kSPV_INTEL_maximum_registers: return IR(2862, 28);
    case Extension::kSPV_INTEL_media_block_io: return IR(2890, 25);
    case Extension::kSPV_INTEL_memory_access_aliasing: return IR(2915, 33);
    case Extension::kSPV_INTEL_optnone: return IR(2948, 18);
    case Extension::kSPV_INTEL_runtime_aligned: return IR(2966, 26);
    case Extension::kSPV_INTEL_shader_integer_functions2: return IR(2992, 36);
    case Extension::kSPV_INTEL_split_barrier: return IR(3028, 24);
    case Extension::kSPV_INTEL_subgroup_buffer_prefetch: return IR(3052, 35);
    case Extension::kSPV_INTEL_subgroup_matrix_multiply_accumulate: return IR(3087, 46);
    case Extension::kSPV_INTEL_subgroups: return IR(3133, 20);
    case Extension::kSPV_INTEL_task_sequence: return IR(3153, 24);
    case Extension::kSPV_INTEL_tensor_float32_conversion: return IR(3177, 36);
    case Extension::kSPV_INTEL_ternary_bitwise_function: return IR(3213, 35);
    case Extension::kSPV_INTEL_unstructured_loop_controls: return IR(3248, 37);
    case Extension::kSPV_INTEL_usm_storage_classes: return IR(3285, 30);
    case Extension::kSPV_INTEL_variable_length_array: return IR(3315, 32);
    case Extension::kSPV_INTEL_vector_compute: return IR(3347, 25);
    case Extension::kSPV_KHR_16bit_storage: return IR(3372, 22);
    case Extension::kSPV_KHR_8bit_storage: return IR(3394, 21);
    case Extension::kSPV_KHR_bfloat16: return IR(3415, 17);
    case Extension::kSPV_KHR_bit_instructions: return IR(3432, 25);
    case Extension::kSPV_KHR_compute_shader_derivatives: return IR(3457, 35);
    case Extension::kSPV_KHR_cooperative_matrix: return IR(3492, 27);
    case Extension::kSPV_KHR_device_group: return IR(3519, 21);
    case Extension::kSPV_KHR_expect_assume: return IR(3540, 22);
    case Extension::kSPV_KHR_float_controls: return IR(3562, 23);
    case Extension::kSPV_KHR_float_controls2: return IR(3585, 24);
    case Extension::kSPV_KHR_fma: return IR(3609, 12);
    case Extension::kSPV_KHR_fragment_shader_barycentric: return IR(3621, 36);
    case Extension::kSPV_KHR_fragment_shading_rate: return IR(3657, 30);
    case Extension::kSPV_KHR_integer_dot_product: return IR(3687, 28);
    case Extension::kSPV_KHR_linkonce_odr: return IR(3715, 21);
    case Extension::kSPV_KHR_maximal_reconvergence: return IR(3736, 30);
    case Extension::kSPV_KHR_multiview: return IR(3766, 18);
    case Extension::kSPV_KHR_no_integer_wrap_decoration: return IR(3784, 35);
    case Extension::kSPV_KHR_non_semantic_info: return IR(3819, 26);
    case Extension::kSPV_KHR_physical_storage_buffer: return IR(3845, 32);
    case Extension::kSPV_KHR_post_depth_coverage: return IR(3877, 28);
    case Extension::kSPV_KHR_quad_control: return IR(3905, 21);
    case Extension::kSPV_KHR_ray_cull_mask: return IR(3926, 22);
    case Extension::kSPV_KHR_ray_query: return IR(3948, 18);
    case Extension::kSPV_KHR_ray_tracing: return IR(3966, 20);
    case Extension::kSPV_KHR_ray_tracing_position_fetch: return IR(3986, 35);
    case Extension::kSPV_KHR_relaxed_extended_instruction: return IR(4021, 37);
    case Extension::kSPV_KHR_shader_atomic_counter_ops: return IR(4058, 34);
    case Extension::kSPV_KHR_shader_ballot: return IR(4092, 22);
    case Extension::kSPV_KHR_shader_clock: return IR(4114, 21);
    case Extension::kSPV_KHR_shader_draw_parameters: return IR(4135, 31);
    case Extension::kSPV_KHR_storage_buffer_storage_class: return IR(4166, 37);
    case Extension::kSPV_KHR_subgroup_rotate: return IR(4203, 24);
    case Extension::kSPV_KHR_subgroup_uniform_control_flow: return IR(4227, 38);
    case Extension::kSPV_KHR_subgroup_vote: return IR(4265, 22);
    case Extension::kSPV_KHR_terminate_invocation: return IR(4287, 29);
    case Extension::kSPV_KHR_uniform_group_instructions: return IR(4316, 35);
    case Extension::kSPV_KHR_untyped_pointers: return IR(4351, 25);
    case Extension::kSPV_KHR_variable_pointers: return IR(4376, 26);
    case Extension::kSPV_KHR_vulkan_memory_model: return IR(4402, 28);
    case Extension::kSPV_KHR_workgroup_memory_explicit_layout: return IR(4430, 41);
    case Extension::kSPV_NVX_multiview_per_view_attributes: return IR(4471, 38);
    case Extension::kSPV_NV_bindless_texture: return IR(4509, 24);
    case Extension::kSPV_NV_cluster_acceleration_structure: return IR(4533, 38);
    case Extension::kSPV_NV_compute_shader_derivatives: return IR(4571, 34);
    case Extension::kSPV_NV_cooperative_matrix: return IR(4605, 26);
    case Extension::kSPV_NV_cooperative_matrix2: return IR(4631, 27);
    case Extension::kSPV_NV_cooperative_vector: return IR(4658, 26);
    case Extension::kSPV_NV_displacement_micromap: return IR(4684, 29);
    case Extension::kSPV_NV_fragment_shader_barycentric: return IR(4713, 35);
    case Extension::kSPV_NV_geometry_shader_passthrough: return IR(4748, 35);
    case Extension::kSPV_NV_linear_swept_spheres: return IR(4783, 28);
    case Extension::kSPV_NV_mesh_shader: return IR(4811, 19);
    case Extension::kSPV_NV_raw_access_chains: return IR(4830, 25);
    case Extension::kSPV_NV_ray_tracing: return IR(4855, 19);
    case Extension::kSPV_NV_ray_tracing_motion_blur: return IR(4874, 31);
    case Extension::kSPV_NV_sample_mask_override_coverage: return IR(4905, 37);
    case Extension::kSPV_NV_shader_atomic_fp16_vector: return IR(4942, 33);
    case Extension::kSPV_NV_shader_image_footprint: return IR(4975, 30);
    case Extension::kSPV_NV_shader_invocation_reorder: return IR(5005, 33);
    case Extension::kSPV_NV_shader_sm_builtins: return IR(5038, 26);
    case Extension::kSPV_NV_shader_subgroup_partitioned: return IR(5064, 35);
    case Extension::kSPV_NV_shading_rate: return IR(5099, 20);
    case Extension::kSPV_NV_stereo_view_rendering: return IR(5119, 29);
    case Extension::kSPV_NV_tensor_addressing: return IR(5148, 25);
    case Extension::kSPV_NV_viewport_array2: return IR(5173, 23);
    case Extension::kSPV_QCOM_cooperative_matrix_conversion: return IR(5196, 39);
    case Extension::kSPV_QCOM_image_processing: return IR(5235, 26);
    case Extension::kSPV_QCOM_image_processing2: return IR(5261, 27);
    case Extension::kSPV_QCOM_tile_shading: return IR(5288, 22);
    case Extension::kSPV_VALIDATOR_ignore_type_decl_unique: return IR(5310, 38);
    default: break;
  }
  return {};
}

// Extension names and values, ordered by name
// The fields in order are:
//   name, indexing into kStrings
//   enum value
static const std::array<NameValue,183> kExtensionNames{{
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
    {IR(1312, 20), static_cast<uint32_t>(kSPV_EXT_mesh_shader)},
    {IR(1332, 25), static_cast<uint32_t>(kSPV_EXT_opacity_micromap)},
    {IR(1357, 16), static_cast<uint32_t>(kSPV_EXT_optnone)},
    {IR(1373, 32), static_cast<uint32_t>(kSPV_EXT_physical_storage_buffer)},
    {IR(1405, 44), static_cast<uint32_t>(kSPV_EXT_relaxed_printf_string_address_space)},
    {IR(1449, 30), static_cast<uint32_t>(kSPV_EXT_replicated_composites)},
    {IR(1479, 30), static_cast<uint32_t>(kSPV_EXT_shader_64bit_indexing)},
    {IR(1509, 34), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float16_add)},
    {IR(1543, 32), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float_add)},
    {IR(1575, 36), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float_min_max)},
    {IR(1611, 27), static_cast<uint32_t>(kSPV_EXT_shader_image_int64)},
    {IR(1638, 34), static_cast<uint32_t>(kSPV_EXT_shader_invocation_reorder)},
    {IR(1672, 30), static_cast<uint32_t>(kSPV_EXT_shader_stencil_export)},
    {IR(1702, 26), static_cast<uint32_t>(kSPV_EXT_shader_tile_image)},
    {IR(1728, 36), static_cast<uint32_t>(kSPV_EXT_shader_viewport_index_layer)},
    {IR(1764, 27), static_cast<uint32_t>(kSPV_GOOGLE_decorate_string)},
    {IR(1791, 31), static_cast<uint32_t>(kSPV_GOOGLE_hlsl_functionality1)},
    {IR(1822, 21), static_cast<uint32_t>(kSPV_GOOGLE_user_type)},
    {IR(1843, 22), static_cast<uint32_t>(kSPV_INTEL_2d_block_io)},
    {IR(1865, 42), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_fixed_point)},
    {IR(1907, 45), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_floating_point)},
    {IR(1952, 39), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_integers)},
    {IR(1991, 30), static_cast<uint32_t>(kSPV_INTEL_bfloat16_conversion)},
    {IR(2021, 26), static_cast<uint32_t>(kSPV_INTEL_bindless_images)},
    {IR(2047, 25), static_cast<uint32_t>(kSPV_INTEL_blocking_pipes)},
    {IR(2072, 25), static_cast<uint32_t>(kSPV_INTEL_cache_controls)},
    {IR(2097, 23), static_cast<uint32_t>(kSPV_INTEL_debug_module)},
    {IR(2120, 44), static_cast<uint32_t>(kSPV_INTEL_device_side_avc_motion_estimation)},
    {IR(2164, 26), static_cast<uint32_t>(kSPV_INTEL_float_controls2)},
    {IR(2190, 28), static_cast<uint32_t>(kSPV_INTEL_fp_fast_math_mode)},
    {IR(2218, 23), static_cast<uint32_t>(kSPV_INTEL_fp_max_error)},
    {IR(2241, 35), static_cast<uint32_t>(kSPV_INTEL_fpga_argument_interfaces)},
    {IR(2276, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_buffer_location)},
    {IR(2307, 34), static_cast<uint32_t>(kSPV_INTEL_fpga_cluster_attributes)},
    {IR(2341, 27), static_cast<uint32_t>(kSPV_INTEL_fpga_dsp_control)},
    {IR(2368, 48), static_cast<uint32_t>(kSPV_INTEL_fpga_invocation_pipelining_attributes)},
    {IR(2416, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_latency_control)},
    {IR(2447, 29), static_cast<uint32_t>(kSPV_INTEL_fpga_loop_controls)},
    {IR(2476, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_memory_accesses)},
    {IR(2507, 33), static_cast<uint32_t>(kSPV_INTEL_fpga_memory_attributes)},
    {IR(2540, 19), static_cast<uint32_t>(kSPV_INTEL_fpga_reg)},
    {IR(2559, 28), static_cast<uint32_t>(kSPV_INTEL_function_pointers)},
    {IR(2587, 28), static_cast<uint32_t>(kSPV_INTEL_function_variants)},
    {IR(2615, 43), static_cast<uint32_t>(kSPV_INTEL_global_variable_fpga_decorations)},
    {IR(2658, 38), static_cast<uint32_t>(kSPV_INTEL_global_variable_host_access)},
    {IR(2696, 26), static_cast<uint32_t>(kSPV_INTEL_inline_assembly)},
    {IR(2722, 15), static_cast<uint32_t>(kSPV_INTEL_int4)},
    {IR(2737, 19), static_cast<uint32_t>(kSPV_INTEL_io_pipes)},
    {IR(2756, 28), static_cast<uint32_t>(kSPV_INTEL_kernel_attributes)},
    {IR(2784, 26), static_cast<uint32_t>(kSPV_INTEL_long_composites)},
    {IR(2810, 20), static_cast<uint32_t>(kSPV_INTEL_loop_fuse)},
    {IR(2830, 32), static_cast<uint32_t>(kSPV_INTEL_masked_gather_scatter)},
    {IR(2862, 28), static_cast<uint32_t>(kSPV_INTEL_maximum_registers)},
    {IR(2890, 25), static_cast<uint32_t>(kSPV_INTEL_media_block_io)},
    {IR(2915, 33), static_cast<uint32_t>(kSPV_INTEL_memory_access_aliasing)},
    {IR(2948, 18), static_cast<uint32_t>(kSPV_INTEL_optnone)},
    {IR(2966, 26), static_cast<uint32_t>(kSPV_INTEL_runtime_aligned)},
    {IR(2992, 36), static_cast<uint32_t>(kSPV_INTEL_shader_integer_functions2)},
    {IR(3028, 24), static_cast<uint32_t>(kSPV_INTEL_split_barrier)},
    {IR(3052, 35), static_cast<uint32_t>(kSPV_INTEL_subgroup_buffer_prefetch)},
    {IR(3087, 46), static_cast<uint32_t>(kSPV_INTEL_subgroup_matrix_multiply_accumulate)},
    {IR(3133, 20), static_cast<uint32_t>(kSPV_INTEL_subgroups)},
    {IR(3153, 24), static_cast<uint32_t>(kSPV_INTEL_task_sequence)},
    {IR(3177, 36), static_cast<uint32_t>(kSPV_INTEL_tensor_float32_conversion)},
    {IR(3213, 35), static_cast<uint32_t>(kSPV_INTEL_ternary_bitwise_function)},
    {IR(3248, 37), static_cast<uint32_t>(kSPV_INTEL_unstructured_loop_controls)},
    {IR(3285, 30), static_cast<uint32_t>(kSPV_INTEL_usm_storage_classes)},
    {IR(3315, 32), static_cast<uint32_t>(kSPV_INTEL_variable_length_array)},
    {IR(3347, 25), static_cast<uint32_t>(kSPV_INTEL_vector_compute)},
    {IR(3372, 22), static_cast<uint32_t>(kSPV_KHR_16bit_storage)},
    {IR(3394, 21), static_cast<uint32_t>(kSPV_KHR_8bit_storage)},
    {IR(3415, 17), static_cast<uint32_t>(kSPV_KHR_bfloat16)},
    {IR(3432, 25), static_cast<uint32_t>(kSPV_KHR_bit_instructions)},
    {IR(3457, 35), static_cast<uint32_t>(kSPV_KHR_compute_shader_derivatives)},
    {IR(3492, 27), static_cast<uint32_t>(kSPV_KHR_cooperative_matrix)},
    {IR(3519, 21), static_cast<uint32_t>(kSPV_KHR_device_group)},
    {IR(3540, 22), static_cast<uint32_t>(kSPV_KHR_expect_assume)},
    {IR(3562, 23), static_cast<uint32_t>(kSPV_KHR_float_controls)},
    {IR(3585, 24), static_cast<uint32_t>(kSPV_KHR_float_controls2)},
    {IR(3609, 12), static_cast<uint32_t>(kSPV_KHR_fma)},
    {IR(3621, 36), static_cast<uint32_t>(kSPV_KHR_fragment_shader_barycentric)},
    {IR(3657, 30), static_cast<uint32_t>(kSPV_KHR_fragment_shading_rate)},
    {IR(3687, 28), static_cast<uint32_t>(kSPV_KHR_integer_dot_product)},
    {IR(3715, 21), static_cast<uint32_t>(kSPV_KHR_linkonce_odr)},
    {IR(3736, 30), static_cast<uint32_t>(kSPV_KHR_maximal_reconvergence)},
    {IR(3766, 18), static_cast<uint32_t>(kSPV_KHR_multiview)},
    {IR(3784, 35), static_cast<uint32_t>(kSPV_KHR_no_integer_wrap_decoration)},
    {IR(3819, 26), static_cast<uint32_t>(kSPV_KHR_non_semantic_info)},
    {IR(3845, 32), static_cast<uint32_t>(kSPV_KHR_physical_storage_buffer)},
    {IR(3877, 28), static_cast<uint32_t>(kSPV_KHR_post_depth_coverage)},
    {IR(3905, 21), static_cast<uint32_t>(kSPV_KHR_quad_control)},
    {IR(3926, 22), static_cast<uint32_t>(kSPV_KHR_ray_cull_mask)},
    {IR(3948, 18), static_cast<uint32_t>(kSPV_KHR_ray_query)},
    {IR(3966, 20), static_cast<uint32_t>(kSPV_KHR_ray_tracing)},
    {IR(3986, 35), static_cast<uint32_t>(kSPV_KHR_ray_tracing_position_fetch)},
    {IR(4021, 37), static_cast<uint32_t>(kSPV_KHR_relaxed_extended_instruction)},
    {IR(4058, 34), static_cast<uint32_t>(kSPV_KHR_shader_atomic_counter_ops)},
    {IR(4092, 22), static_cast<uint32_t>(kSPV_KHR_shader_ballot)},
    {IR(4114, 21), static_cast<uint32_t>(kSPV_KHR_shader_clock)},
    {IR(4135, 31), static_cast<uint32_t>(kSPV_KHR_shader_draw_parameters)},
    {IR(4166, 37), static_cast<uint32_t>(kSPV_KHR_storage_buffer_storage_class)},
    {IR(4203, 24), static_cast<uint32_t>(kSPV_KHR_subgroup_rotate)},
    {IR(4227, 38), static_cast<uint32_t>(kSPV_KHR_subgroup_uniform_control_flow)},
    {IR(4265, 22), static_cast<uint32_t>(kSPV_KHR_subgroup_vote)},
    {IR(4287, 29), static_cast<uint32_t>(kSPV_KHR_terminate_invocation)},
    {IR(4316, 35), static_cast<uint32_t>(kSPV_KHR_uniform_group_instructions)},
    {IR(4351, 25), static_cast<uint32_t>(kSPV_KHR_untyped_pointers)},
    {IR(4376, 26), static_cast<uint32_t>(kSPV_KHR_variable_pointers)},
    {IR(4402, 28), static_cast<uint32_t>(kSPV_KHR_vulkan_memory_model)},
    {IR(4430, 41), static_cast<uint32_t>(kSPV_KHR_workgroup_memory_explicit_layout)},
    {IR(4471, 38), static_cast<uint32_t>(kSPV_NVX_multiview_per_view_attributes)},
    {IR(4509, 24), static_cast<uint32_t>(kSPV_NV_bindless_texture)},
    {IR(4533, 38), static_cast<uint32_t>(kSPV_NV_cluster_acceleration_structure)},
    {IR(4571, 34), static_cast<uint32_t>(kSPV_NV_compute_shader_derivatives)},
    {IR(4605, 26), static_cast<uint32_t>(kSPV_NV_cooperative_matrix)},
    {IR(4631, 27), static_cast<uint32_t>(kSPV_NV_cooperative_matrix2)},
    {IR(4658, 26), static_cast<uint32_t>(kSPV_NV_cooperative_vector)},
    {IR(4684, 29), static_cast<uint32_t>(kSPV_NV_displacement_micromap)},
    {IR(4713, 35), static_cast<uint32_t>(kSPV_NV_fragment_shader_barycentric)},
    {IR(4748, 35), static_cast<uint32_t>(kSPV_NV_geometry_shader_passthrough)},
    {IR(4783, 28), static_cast<uint32_t>(kSPV_NV_linear_swept_spheres)},
    {IR(4811, 19), static_cast<uint32_t>(kSPV_NV_mesh_shader)},
    {IR(4830, 25), static_cast<uint32_t>(kSPV_NV_raw_access_chains)},
    {IR(4855, 19), static_cast<uint32_t>(kSPV_NV_ray_tracing)},
    {IR(4874, 31), static_cast<uint32_t>(kSPV_NV_ray_tracing_motion_blur)},
    {IR(4905, 37), static_cast<uint32_t>(kSPV_NV_sample_mask_override_coverage)},
    {IR(4942, 33), static_cast<uint32_t>(kSPV_NV_shader_atomic_fp16_vector)},
    {IR(4975, 30), static_cast<uint32_t>(kSPV_NV_shader_image_footprint)},
    {IR(5005, 33), static_cast<uint32_t>(kSPV_NV_shader_invocation_reorder)},
    {IR(5038, 26), static_cast<uint32_t>(kSPV_NV_shader_sm_builtins)},
    {IR(5064, 35), static_cast<uint32_t>(kSPV_NV_shader_subgroup_partitioned)},
    {IR(5099, 20), static_cast<uint32_t>(kSPV_NV_shading_rate)},
    {IR(5119, 29), static_cast<uint32_t>(kSPV_NV_stereo_view_rendering)},
    {IR(5148, 25), static_cast<uint32_t>(kSPV_NV_tensor_addressing)},
    {IR(5173, 23), static_cast<uint32_t>(kSPV_NV_viewport_array2)},
    {IR(5196, 39), static_cast<uint32_t>(kSPV_QCOM_cooperative_matrix_conversion)},
    {IR(5235, 26), static_cast<uint32_t>(kSPV_QCOM_image_processing)},
    {IR(5261, 27), static_cast<uint32_t>(kSPV_QCOM_image_processing2)},
    {IR(5288, 22), static_cast<uint32_t>(kSPV_QCOM_tile_shading)},
    {IR(5310, 38), static_cast<uint32_t>(kSPV_VALIDATOR_ignore_type_decl_unique)},
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
static const std::array<OperandDesc, 1194> kOperandsByValue{{
  {0,IR(0, 0),IR(5348, 9)/* ReadOnly */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {1,IR(0, 0),IR(5364, 10)/* WriteOnly */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {2,IR(0, 0),IR(5374, 10)/* ReadWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {0,IR(0, 0),IR(5384, 8)/* Logical */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {1,IR(0, 0),IR(5392, 11)/* Physical32 */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {2,IR(0, 0),IR(5413, 11)/* Physical64 */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {5348,IR(0, 0),IR(5424, 24)/* PhysicalStorageBuffer64 */,IR(0, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {0,IR(0, 0),IR(5506, 9)/* Position */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {1,IR(0, 0),IR(5522, 10)/* PointSize */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {3,IR(0, 0),IR(5532, 13)/* ClipDistance */,IR(0, 0),IR(4, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4,IR(0, 0),IR(5545, 13)/* CullDistance */,IR(0, 0),IR(5, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5,IR(0, 0),IR(5558, 9)/* VertexId */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {6,IR(0, 0),IR(5567, 11)/* InstanceId */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {7,IR(0, 0),IR(5578, 12)/* PrimitiveId */,IR(0, 0),IR(6, 6),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {8,IR(0, 0),IR(5668, 13)/* InvocationId */,IR(0, 0),IR(12, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {9,IR(0, 0),IR(5681, 6)/* Layer */,IR(0, 0),IR(14, 5),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {10,IR(0, 0),IR(5727, 14)/* ViewportIndex */,IR(0, 0),IR(19, 5),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {11,IR(0, 0),IR(5775, 15)/* TessLevelOuter */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {12,IR(0, 0),IR(5790, 15)/* TessLevelInner */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {13,IR(0, 0),IR(5805, 10)/* TessCoord */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {14,IR(0, 0),IR(5815, 14)/* PatchVertices */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {15,IR(0, 0),IR(5829, 10)/* FragCoord */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {16,IR(0, 0),IR(5839, 11)/* PointCoord */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {17,IR(0, 0),IR(5850, 12)/* FrontFacing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {18,IR(0, 0),IR(5862, 9)/* SampleId */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {19,IR(0, 0),IR(5889, 15)/* SamplePosition */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {20,IR(0, 0),IR(5904, 11)/* SampleMask */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {22,IR(0, 0),IR(5915, 10)/* FragDepth */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {23,IR(0, 0),IR(5925, 17)/* HelperInvocation */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {24,IR(0, 0),IR(5942, 14)/* NumWorkgroups */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {25,IR(0, 0),IR(5956, 14)/* WorkgroupSize */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {26,IR(0, 0),IR(5970, 12)/* WorkgroupId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {27,IR(0, 0),IR(5982, 18)/* LocalInvocationId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {28,IR(0, 0),IR(6000, 19)/* GlobalInvocationId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {29,IR(0, 0),IR(6019, 21)/* LocalInvocationIndex */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {30,IR(0, 0),IR(6040, 8)/* WorkDim */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {31,IR(0, 0),IR(6048, 11)/* GlobalSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {32,IR(0, 0),IR(6059, 22)/* EnqueuedWorkgroupSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {33,IR(0, 0),IR(6081, 13)/* GlobalOffset */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {34,IR(0, 0),IR(6094, 15)/* GlobalLinearId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {36,IR(0, 0),IR(6109, 13)/* SubgroupSize */,IR(0, 0),IR(26, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {37,IR(0, 0),IR(6156, 16)/* SubgroupMaxSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {38,IR(0, 0),IR(6172, 13)/* NumSubgroups */,IR(0, 0),IR(29, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {39,IR(0, 0),IR(6185, 21)/* NumEnqueuedSubgroups */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {40,IR(0, 0),IR(6206, 11)/* SubgroupId */,IR(0, 0),IR(29, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {41,IR(0, 0),IR(6217, 26)/* SubgroupLocalInvocationId */,IR(0, 0),IR(26, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {42,IR(0, 0),IR(6243, 12)/* VertexIndex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {43,IR(0, 0),IR(6255, 14)/* InstanceIndex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4160,IR(0, 0),IR(6269, 10)/* CoreIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4161,IR(0, 0),IR(6295, 13)/* CoreCountARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4162,IR(0, 0),IR(6308, 13)/* CoreMaxIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4163,IR(0, 0),IR(6321, 10)/* WarpIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4164,IR(0, 0),IR(6331, 13)/* WarpMaxIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4416,IR(0, 0),IR(6344, 15)/* SubgroupEqMask */,IR(1, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4417,IR(0, 0),IR(6399, 15)/* SubgroupGeMask */,IR(2, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4418,IR(0, 0),IR(6432, 15)/* SubgroupGtMask */,IR(3, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4419,IR(0, 0),IR(6465, 15)/* SubgroupLeMask */,IR(4, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4420,IR(0, 0),IR(6498, 15)/* SubgroupLtMask */,IR(5, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4424,IR(0, 0),IR(6531, 11)/* BaseVertex */,IR(0, 0),IR(34, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4425,IR(0, 0),IR(6557, 13)/* BaseInstance */,IR(0, 0),IR(34, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4426,IR(0, 0),IR(6570, 10)/* DrawIndex */,IR(0, 0),IR(35, 3),IR(4, 3),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4432,IR(0, 0),IR(6580, 24)/* PrimitiveShadingRateKHR */,IR(0, 0),IR(38, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4438,IR(0, 0),IR(6627, 12)/* DeviceIndex */,IR(0, 0),IR(39, 1),IR(8, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4440,IR(0, 0),IR(6651, 10)/* ViewIndex */,IR(0, 0),IR(40, 1),IR(9, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4444,IR(0, 0),IR(6671, 15)/* ShadingRateKHR */,IR(0, 0),IR(38, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4492,IR(0, 0),IR(6686, 15)/* TileOffsetQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4493,IR(0, 0),IR(6717, 18)/* TileDimensionQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4494,IR(0, 0),IR(6735, 18)/* TileApronSizeQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4992,IR(0, 0),IR(6753, 20)/* BaryCoordNoPerspAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4993,IR(0, 0),IR(6773, 28)/* BaryCoordNoPerspCentroidAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4994,IR(0, 0),IR(6801, 26)/* BaryCoordNoPerspSampleAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4995,IR(0, 0),IR(6827, 19)/* BaryCoordSmoothAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4996,IR(0, 0),IR(6846, 27)/* BaryCoordSmoothCentroidAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4997,IR(0, 0),IR(6873, 25)/* BaryCoordSmoothSampleAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4998,IR(0, 0),IR(6898, 22)/* BaryCoordPullModelAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5014,IR(0, 0),IR(6920, 18)/* FragStencilRefEXT */,IR(0, 0),IR(42, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5021,IR(0, 0),IR(6955, 29)/* RemainingRecursionLevelsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5073,IR(0, 0),IR(7002, 16)/* ShaderIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5253,IR(0, 0),IR(7018, 15)/* ViewportMaskNV */,IR(0, 0),IR(44, 2),IR(12, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5257,IR(0, 0),IR(7054, 20)/* SecondaryPositionNV */,IR(0, 0),IR(46, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5258,IR(0, 0),IR(7093, 24)/* SecondaryViewportMaskNV */,IR(0, 0),IR(46, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5261,IR(0, 0),IR(7117, 18)/* PositionPerViewNV */,IR(0, 0),IR(47, 2),IR(15, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5262,IR(0, 0),IR(7155, 22)/* ViewportMaskPerViewNV */,IR(0, 0),IR(47, 2),IR(15, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5264,IR(0, 0),IR(7177, 16)/* FullyCoveredEXT */,IR(0, 0),IR(49, 1),IR(17, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5274,IR(0, 0),IR(7217, 12)/* TaskCountNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5275,IR(0, 0),IR(7229, 17)/* PrimitiveCountNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5276,IR(0, 0),IR(7246, 19)/* PrimitiveIndicesNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5277,IR(0, 0),IR(7265, 22)/* ClipDistancePerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5278,IR(0, 0),IR(7287, 22)/* CullDistancePerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5279,IR(0, 0),IR(7309, 15)/* LayerPerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5280,IR(0, 0),IR(7324, 16)/* MeshViewCountNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5281,IR(0, 0),IR(7340, 18)/* MeshViewIndicesNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5286,IR(0, 0),IR(7358, 13)/* BaryCoordKHR */,IR(6, 1),IR(51, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5287,IR(0, 0),IR(7406, 20)/* BaryCoordNoPerspKHR */,IR(7, 1),IR(51, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5292,IR(0, 0),IR(7445, 12)/* FragSizeEXT */,IR(8, 1),IR(52, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5293,IR(0, 0),IR(7491, 23)/* FragInvocationCountEXT */,IR(9, 1),IR(52, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5294,IR(0, 0),IR(7536, 25)/* PrimitivePointIndicesEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5295,IR(0, 0),IR(7561, 24)/* PrimitiveLineIndicesEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5296,IR(0, 0),IR(7585, 28)/* PrimitiveTriangleIndicesEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5299,IR(0, 0),IR(7613, 17)/* CullPrimitiveEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5319,IR(0, 0),IR(7630, 12)/* LaunchIdKHR */,IR(10, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5320,IR(0, 0),IR(7653, 14)/* LaunchSizeKHR */,IR(11, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5321,IR(0, 0),IR(7680, 18)/* WorldRayOriginKHR */,IR(12, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5322,IR(0, 0),IR(7715, 21)/* WorldRayDirectionKHR */,IR(13, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5323,IR(0, 0),IR(7756, 19)/* ObjectRayOriginKHR */,IR(14, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5324,IR(0, 0),IR(7793, 22)/* ObjectRayDirectionKHR */,IR(15, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5325,IR(0, 0),IR(7836, 11)/* RayTminKHR */,IR(16, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5326,IR(0, 0),IR(7857, 11)/* RayTmaxKHR */,IR(17, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5327,IR(0, 0),IR(7878, 23)/* InstanceCustomIndexKHR */,IR(18, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5330,IR(0, 0),IR(7923, 17)/* ObjectToWorldKHR */,IR(19, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5331,IR(0, 0),IR(7956, 17)/* WorldToObjectKHR */,IR(20, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5332,IR(0, 0),IR(7989, 7)/* HitTNV */,IR(0, 0),IR(56, 1),IR(26, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5333,IR(0, 0),IR(7996, 11)/* HitKindKHR */,IR(21, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5334,IR(0, 0),IR(8017, 17)/* CurrentRayTimeNV */,IR(0, 0),IR(57, 1),IR(27, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5335,IR(0, 0),IR(8057, 30)/* HitTriangleVertexPositionsKHR */,IR(0, 0),IR(58, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5337,IR(0, 0),IR(8114, 34)/* HitMicroTriangleVertexPositionsNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5344,IR(0, 0),IR(8181, 37)/* HitMicroTriangleVertexBarycentricsNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5351,IR(0, 0),IR(8218, 20)/* IncomingRayFlagsKHR */,IR(22, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5352,IR(0, 0),IR(8257, 20)/* RayGeometryIndexKHR */,IR(0, 0),IR(60, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5359,IR(0, 0),IR(8277, 14)/* HitIsSphereNV */,IR(0, 0),IR(61, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5360,IR(0, 0),IR(8319, 11)/* HitIsLSSNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5361,IR(0, 0),IR(8369, 20)/* HitSpherePositionNV */,IR(0, 0),IR(61, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5374,IR(0, 0),IR(8389, 13)/* WarpsPerSMNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5375,IR(0, 0),IR(8421, 10)/* SMCountNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5376,IR(0, 0),IR(8431, 9)/* WarpIDNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5377,IR(0, 0),IR(8440, 7)/* SMIDNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5396,IR(0, 0),IR(8447, 18)/* HitLSSPositionsNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5405,IR(0, 0),IR(8465, 34)/* HitKindFrontFacingMicroTriangleNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5406,IR(0, 0),IR(8499, 33)/* HitKindBackFacingMicroTriangleNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5420,IR(0, 0),IR(8532, 18)/* HitSphereRadiusNV */,IR(0, 0),IR(61, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5421,IR(0, 0),IR(8550, 14)/* HitLSSRadiiNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5436,IR(0, 0),IR(8564, 12)/* ClusterIDNV */,IR(0, 0),IR(64, 1),IR(31, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {6021,IR(0, 0),IR(8617, 12)/* CullMaskKHR */,IR(0, 0),IR(65, 1),IR(32, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {0,IR(0, 0),IR(8644, 7)/* Matrix */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {1,IR(0, 0),IR(5515, 7)/* Shader */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {2,IR(0, 0),IR(5590, 9)/* Geometry */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {3,IR(0, 0),IR(5599, 13)/* Tessellation */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4,IR(0, 0),IR(5403, 10)/* Addresses */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5,IR(0, 0),IR(8651, 8)/* Linkage */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6,IR(0, 0),IR(5357, 7)/* Kernel */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {7,IR(0, 0),IR(8659, 9)/* Vector16 */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {8,IR(0, 0),IR(8668, 14)/* Float16Buffer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {9,IR(0, 0),IR(8682, 8)/* Float16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {10,IR(0, 0),IR(8690, 8)/* Float64 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {11,IR(0, 0),IR(8698, 6)/* Int64 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {12,IR(0, 0),IR(8704, 13)/* Int64Atomics */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {13,IR(0, 0),IR(8717, 11)/* ImageBasic */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {14,IR(0, 0),IR(8728, 15)/* ImageReadWrite */,IR(0, 0),IR(68, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {15,IR(0, 0),IR(8743, 12)/* ImageMipmap */,IR(0, 0),IR(68, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {17,IR(0, 0),IR(8755, 6)/* Pipes */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {18,IR(0, 0),IR(8761, 7)/* Groups */,IR(0, 0),IR(1, 0),IR(33, 1),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {19,IR(0, 0),IR(8768, 14)/* DeviceEnqueue */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {20,IR(0, 0),IR(8782, 15)/* LiteralSampler */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {21,IR(0, 0),IR(8797, 14)/* AtomicStorage */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {22,IR(0, 0),IR(8811, 6)/* Int16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {23,IR(0, 0),IR(8817, 22)/* TessellationPointSize */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {24,IR(0, 0),IR(8839, 18)/* GeometryPointSize */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {25,IR(0, 0),IR(8857, 20)/* ImageGatherExtended */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {27,IR(0, 0),IR(8877, 24)/* StorageImageMultisample */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {28,IR(0, 0),IR(8901, 34)/* UniformBufferArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {29,IR(0, 0),IR(8935, 33)/* SampledImageArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {30,IR(0, 0),IR(8968, 34)/* StorageBufferArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {31,IR(0, 0),IR(9002, 33)/* StorageImageArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {32,IR(0, 0),IR(5532, 13)/* ClipDistance */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {33,IR(0, 0),IR(5545, 13)/* CullDistance */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {34,IR(0, 0),IR(9035, 15)/* ImageCubeArray */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {35,IR(0, 0),IR(5871, 18)/* SampleRateShading */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {36,IR(0, 0),IR(9067, 10)/* ImageRect */,IR(0, 0),IR(71, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {37,IR(0, 0),IR(9077, 12)/* SampledRect */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {38,IR(0, 0),IR(9089, 15)/* GenericPointer */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {39,IR(0, 0),IR(9104, 5)/* Int8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {40,IR(0, 0),IR(9109, 16)/* InputAttachment */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {41,IR(0, 0),IR(9125, 16)/* SparseResidency */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {42,IR(0, 0),IR(9141, 7)/* MinLod */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {43,IR(0, 0),IR(9148, 10)/* Sampled1D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {44,IR(0, 0),IR(9158, 8)/* Image1D */,IR(0, 0),IR(72, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {45,IR(0, 0),IR(9050, 17)/* SampledCubeArray */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {46,IR(0, 0),IR(9166, 14)/* SampledBuffer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {47,IR(0, 0),IR(9180, 12)/* ImageBuffer */,IR(0, 0),IR(73, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {48,IR(0, 0),IR(9192, 13)/* ImageMSArray */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {49,IR(0, 0),IR(9205, 28)/* StorageImageExtendedFormats */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {50,IR(0, 0),IR(9233, 11)/* ImageQuery */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {51,IR(0, 0),IR(9244, 18)/* DerivativeControl */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {52,IR(0, 0),IR(9262, 22)/* InterpolationFunction */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {53,IR(0, 0),IR(9284, 18)/* TransformFeedback */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {54,IR(0, 0),IR(9302, 16)/* GeometryStreams */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {55,IR(0, 0),IR(9318, 30)/* StorageImageReadWithoutFormat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {56,IR(0, 0),IR(9348, 31)/* StorageImageWriteWithoutFormat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {57,IR(0, 0),IR(5741, 14)/* MultiViewport */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {58,IR(0, 0),IR(9379, 17)/* SubgroupDispatch */,IR(0, 0),IR(74, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {59,IR(0, 0),IR(9396, 13)/* NamedBarrier */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {60,IR(0, 0),IR(9409, 12)/* PipeStorage */,IR(0, 0),IR(75, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {61,IR(0, 0),IR(6122, 16)/* GroupNonUniform */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {62,IR(0, 0),IR(9421, 20)/* GroupNonUniformVote */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {63,IR(0, 0),IR(9441, 26)/* GroupNonUniformArithmetic */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {64,IR(0, 0),IR(6377, 22)/* GroupNonUniformBallot */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {65,IR(0, 0),IR(9467, 23)/* GroupNonUniformShuffle */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {66,IR(0, 0),IR(9490, 31)/* GroupNonUniformShuffleRelative */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {67,IR(0, 0),IR(9521, 25)/* GroupNonUniformClustered */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {68,IR(0, 0),IR(9546, 20)/* GroupNonUniformQuad */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {69,IR(0, 0),IR(5687, 12)/* ShaderLayer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {70,IR(0, 0),IR(5755, 20)/* ShaderViewportIndex */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {71,IR(0, 0),IR(9566, 18)/* UniformDecoration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4165,IR(0, 0),IR(6279, 16)/* CoreBuiltinsARM */,IR(0, 0),IR(1, 0),IR(34, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4166,IR(0, 0),IR(9584, 28)/* TileImageColorReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4167,IR(0, 0),IR(9612, 28)/* TileImageDepthReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4168,IR(0, 0),IR(9640, 30)/* TileImageStencilReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4174,IR(0, 0),IR(9670, 11)/* TensorsARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4175,IR(0, 0),IR(9681, 37)/* StorageTensorArrayDynamicIndexingARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4176,IR(0, 0),IR(9718, 40)/* StorageTensorArrayNonUniformIndexingARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4191,IR(0, 0),IR(9758, 9)/* GraphARM */,IR(0, 0),IR(1, 0),IR(37, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4201,IR(0, 0),IR(9767, 28)/* CooperativeMatrixLayoutsARM */,IR(0, 0),IR(1, 0),IR(38, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4212,IR(0, 0),IR(9795, 10)/* Float8EXT */,IR(0, 0),IR(1, 0),IR(39, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4213,IR(0, 0),IR(9805, 27)/* Float8CooperativeMatrixEXT */,IR(0, 0),IR(77, 2),IR(39, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4422,IR(0, 0),IR(6604, 23)/* FragmentShadingRateKHR */,IR(0, 0),IR(3, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4423,IR(0, 0),IR(6138, 18)/* SubgroupBallotKHR */,IR(0, 0),IR(1, 0),IR(2, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4427,IR(0, 0),IR(6542, 15)/* DrawParameters */,IR(0, 0),IR(3, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4428,IR(0, 0),IR(9853, 33)/* WorkgroupMemoryExplicitLayoutKHR */,IR(0, 0),IR(3, 1),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4429,IR(0, 0),IR(9886, 43)/* WorkgroupMemoryExplicitLayout8BitAccessKHR */,IR(0, 0),IR(79, 1),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4430,IR(0, 0),IR(9929, 44)/* WorkgroupMemoryExplicitLayout16BitAccessKHR */,IR(0, 0),IR(79, 1),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4431,IR(0, 0),IR(9973, 16)/* SubgroupVoteKHR */,IR(0, 0),IR(1, 0),IR(41, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4433,IR(0, 0),IR(9989, 25)/* StorageBuffer16BitAccess */,IR(23, 1),IR(1, 0),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4434,IR(0, 0),IR(10042, 35)/* UniformAndStorageBuffer16BitAccess */,IR(24, 1),IR(80, 1),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4435,IR(0, 0),IR(10094, 22)/* StoragePushConstant16 */,IR(0, 0),IR(1, 0),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4436,IR(0, 0),IR(10116, 21)/* StorageInputOutput16 */,IR(0, 0),IR(1, 0),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4437,IR(0, 0),IR(6639, 12)/* DeviceGroup */,IR(0, 0),IR(1, 0),IR(8, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4439,IR(0, 0),IR(6661, 10)/* MultiView */,IR(0, 0),IR(3, 1),IR(9, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4441,IR(0, 0),IR(10137, 30)/* VariablePointersStorageBuffer */,IR(0, 0),IR(3, 1),IR(43, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4442,IR(0, 0),IR(10167, 17)/* VariablePointers */,IR(0, 0),IR(81, 1),IR(43, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4445,IR(0, 0),IR(10184, 17)/* AtomicStorageOps */,IR(0, 0),IR(82, 1),IR(44, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4447,IR(0, 0),IR(10201, 28)/* SampleMaskPostDepthCoverage */,IR(0, 0),IR(1, 0),IR(45, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4448,IR(0, 0),IR(10229, 24)/* StorageBuffer8BitAccess */,IR(0, 0),IR(1, 0),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4449,IR(0, 0),IR(10253, 34)/* UniformAndStorageBuffer8BitAccess */,IR(0, 0),IR(83, 1),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4450,IR(0, 0),IR(10287, 21)/* StoragePushConstant8 */,IR(0, 0),IR(1, 0),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4464,IR(0, 0),IR(10308, 15)/* DenormPreserve */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4465,IR(0, 0),IR(10323, 18)/* DenormFlushToZero */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4466,IR(0, 0),IR(10341, 25)/* SignedZeroInfNanPreserve */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4467,IR(0, 0),IR(10366, 16)/* RoundingModeRTE */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4468,IR(0, 0),IR(10382, 16)/* RoundingModeRTZ */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4471,IR(0, 0),IR(10398, 23)/* RayQueryProvisionalKHR */,IR(0, 0),IR(3, 1),IR(48, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4472,IR(0, 0),IR(10421, 12)/* RayQueryKHR */,IR(0, 0),IR(3, 1),IR(48, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4473,IR(0, 0),IR(10433, 19)/* UntypedPointersKHR */,IR(0, 0),IR(1, 0),IR(49, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4478,IR(0, 0),IR(10452, 32)/* RayTraversalPrimitiveCullingKHR */,IR(0, 0),IR(84, 2),IR(50, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4479,IR(0, 0),IR(5625, 14)/* RayTracingKHR */,IR(0, 0),IR(3, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4484,IR(0, 0),IR(10484, 26)/* TextureSampleWeightedQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4485,IR(0, 0),IR(10510, 21)/* TextureBoxFilterQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4486,IR(0, 0),IR(10531, 22)/* TextureBlockMatchQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4495,IR(0, 0),IR(6701, 16)/* TileShadingQCOM */,IR(0, 0),IR(3, 1),IR(53, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4496,IR(0, 0),IR(10553, 32)/* CooperativeMatrixConversionQCOM */,IR(0, 0),IR(86, 1),IR(54, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4498,IR(0, 0),IR(10585, 23)/* TextureBlockMatch2QCOM */,IR(0, 0),IR(1, 0),IR(55, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5008,IR(0, 0),IR(10608, 16)/* Float16ImageAMD */,IR(0, 0),IR(3, 1),IR(56, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5009,IR(0, 0),IR(10624, 22)/* ImageGatherBiasLodAMD */,IR(0, 0),IR(3, 1),IR(57, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5010,IR(0, 0),IR(10646, 16)/* FragmentMaskAMD */,IR(0, 0),IR(3, 1),IR(58, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5013,IR(0, 0),IR(6938, 17)/* StencilExportEXT */,IR(0, 0),IR(3, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5015,IR(0, 0),IR(10662, 21)/* ImageReadWriteLodAMD */,IR(0, 0),IR(3, 1),IR(59, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5016,IR(0, 0),IR(10683, 14)/* Int64ImageEXT */,IR(0, 0),IR(3, 1),IR(60, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5055,IR(0, 0),IR(10697, 15)/* ShaderClockKHR */,IR(0, 0),IR(1, 0),IR(61, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5067,IR(0, 0),IR(6984, 18)/* ShaderEnqueueAMDX */,IR(0, 0),IR(3, 1),IR(62, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5087,IR(0, 0),IR(10712, 15)/* QuadControlKHR */,IR(0, 0),IR(1, 0),IR(63, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5112,IR(0, 0),IR(10727, 14)/* Int4TypeINTEL */,IR(0, 0),IR(1, 0),IR(64, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5114,IR(0, 0),IR(10741, 27)/* Int4CooperativeMatrixINTEL */,IR(0, 0),IR(87, 2),IR(64, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5116,IR(0, 0),IR(10768, 16)/* BFloat16TypeKHR */,IR(0, 0),IR(1, 0),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5117,IR(0, 0),IR(10784, 22)/* BFloat16DotProductKHR */,IR(0, 0),IR(89, 1),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5118,IR(0, 0),IR(10806, 29)/* BFloat16CooperativeMatrixKHR */,IR(0, 0),IR(90, 2),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5249,IR(0, 0),IR(10835, 29)/* SampleMaskOverrideCoverageNV */,IR(0, 0),IR(25, 1),IR(66, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5251,IR(0, 0),IR(10864, 28)/* GeometryShaderPassthroughNV */,IR(0, 0),IR(69, 1),IR(67, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5254,IR(0, 0),IR(5699, 28)/* ShaderViewportIndexLayerEXT */,IR(25, 1),IR(92, 1),IR(68, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5255,IR(0, 0),IR(7033, 21)/* ShaderViewportMaskNV */,IR(0, 0),IR(93, 1),IR(70, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5259,IR(0, 0),IR(7074, 19)/* ShaderStereoViewNV */,IR(0, 0),IR(94, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5260,IR(0, 0),IR(7135, 20)/* PerViewAttributesNV */,IR(0, 0),IR(40, 1),IR(71, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5265,IR(0, 0),IR(7193, 24)/* FragmentFullyCoveredEXT */,IR(0, 0),IR(3, 1),IR(17, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5266,IR(0, 0),IR(5639, 14)/* MeshShadingNV */,IR(0, 0),IR(3, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5282,IR(0, 0),IR(10919, 17)/* ImageFootprintNV */,IR(0, 0),IR(1, 0),IR(72, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5283,IR(0, 0),IR(5653, 15)/* MeshShadingEXT */,IR(0, 0),IR(3, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5284,IR(0, 0),IR(7383, 23)/* FragmentBarycentricKHR */,IR(26, 1),IR(1, 0),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5288,IR(0, 0),IR(10958, 31)/* ComputeDerivativeGroupQuadsKHR */,IR(27, 1),IR(3, 1),IR(73, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5291,IR(0, 0),IR(7472, 19)/* FragmentDensityEXT */,IR(28, 1),IR(3, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5297,IR(0, 0),IR(11033, 29)/* GroupNonUniformPartitionedNV */,IR(0, 0),IR(1, 0),IR(75, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5301,IR(0, 0),IR(11062, 17)/* ShaderNonUniform */,IR(29, 1),IR(3, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5302,IR(0, 0),IR(11099, 23)/* RuntimeDescriptorArray */,IR(30, 1),IR(3, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5303,IR(0, 0),IR(11148, 36)/* InputAttachmentArrayDynamicIndexing */,IR(31, 1),IR(95, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5304,IR(0, 0),IR(11223, 39)/* UniformTexelBufferArrayDynamicIndexing */,IR(32, 1),IR(73, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5305,IR(0, 0),IR(11304, 39)/* StorageTexelBufferArrayDynamicIndexing */,IR(33, 1),IR(96, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5306,IR(0, 0),IR(11385, 37)/* UniformBufferArrayNonUniformIndexing */,IR(34, 1),IR(97, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5307,IR(0, 0),IR(11462, 36)/* SampledImageArrayNonUniformIndexing */,IR(35, 1),IR(97, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5308,IR(0, 0),IR(11537, 37)/* StorageBufferArrayNonUniformIndexing */,IR(36, 1),IR(97, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5309,IR(0, 0),IR(11614, 36)/* StorageImageArrayNonUniformIndexing */,IR(37, 1),IR(97, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5310,IR(0, 0),IR(11689, 39)/* InputAttachmentArrayNonUniformIndexing */,IR(38, 1),IR(98, 2),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5311,IR(0, 0),IR(11770, 42)/* UniformTexelBufferArrayNonUniformIndexing */,IR(39, 1),IR(100, 2),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5312,IR(0, 0),IR(11857, 42)/* StorageTexelBufferArrayNonUniformIndexing */,IR(40, 1),IR(102, 2),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5336,IR(0, 0),IR(8087, 27)/* RayTracingPositionFetchKHR */,IR(0, 0),IR(3, 1),IR(77, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5340,IR(0, 0),IR(5612, 13)/* RayTracingNV */,IR(0, 0),IR(3, 1),IR(26, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5341,IR(0, 0),IR(8034, 23)/* RayTracingMotionBlurNV */,IR(0, 0),IR(3, 1),IR(27, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5345,IR(0, 0),IR(11944, 18)/* VulkanMemoryModel */,IR(41, 1),IR(1, 0),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5346,IR(0, 0),IR(11983, 29)/* VulkanMemoryModelDeviceScope */,IR(42, 1),IR(1, 0),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5347,IR(0, 0),IR(5475, 31)/* PhysicalStorageBufferAddresses */,IR(43, 1),IR(3, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5350,IR(0, 0),IR(12078, 32)/* ComputeDerivativeGroupLinearKHR */,IR(44, 1),IR(3, 1),IR(73, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5353,IR(0, 0),IR(12141, 25)/* RayTracingProvisionalKHR */,IR(0, 0),IR(3, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5357,IR(0, 0),IR(12166, 20)/* CooperativeMatrixNV */,IR(0, 0),IR(3, 1),IR(79, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5363,IR(0, 0),IR(12186, 33)/* FragmentShaderSampleInterlockEXT */,IR(0, 0),IR(3, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5372,IR(0, 0),IR(12219, 38)/* FragmentShaderShadingRateInterlockEXT */,IR(0, 0),IR(3, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5373,IR(0, 0),IR(8402, 19)/* ShaderSMBuiltinsNV */,IR(0, 0),IR(3, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5378,IR(0, 0),IR(12257, 32)/* FragmentShaderPixelInterlockEXT */,IR(0, 0),IR(3, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5379,IR(0, 0),IR(12289, 25)/* DemoteToHelperInvocation */,IR(45, 1),IR(3, 1),IR(81, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5380,IR(0, 0),IR(12342, 23)/* DisplacementMicromapNV */,IR(0, 0),IR(3, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5381,IR(0, 0),IR(12365, 29)/* RayTracingOpacityMicromapEXT */,IR(0, 0),IR(3, 1),IR(83, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5383,IR(0, 0),IR(12394, 26)/* ShaderInvocationReorderNV */,IR(0, 0),IR(60, 1),IR(84, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5388,IR(0, 0),IR(12420, 27)/* ShaderInvocationReorderEXT */,IR(0, 0),IR(60, 1),IR(85, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5390,IR(0, 0),IR(12447, 18)/* BindlessTextureNV */,IR(0, 0),IR(1, 0),IR(86, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5391,IR(0, 0),IR(12465, 25)/* RayQueryPositionFetchKHR */,IR(0, 0),IR(3, 1),IR(77, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5394,IR(0, 0),IR(12490, 20)/* CooperativeVectorNV */,IR(0, 0),IR(1, 0),IR(87, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5404,IR(0, 0),IR(12510, 22)/* AtomicFloat16VectorNV */,IR(0, 0),IR(1, 0),IR(88, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5409,IR(0, 0),IR(8148, 33)/* RayTracingDisplacementMicromapNV */,IR(0, 0),IR(60, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5414,IR(0, 0),IR(12532, 18)/* RawAccessChainsNV */,IR(0, 0),IR(1, 0),IR(89, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5418,IR(0, 0),IR(8291, 28)/* RayTracingSpheresGeometryNV */,IR(0, 0),IR(1, 0),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5419,IR(0, 0),IR(8330, 39)/* RayTracingLinearSweptSpheresGeometryNV */,IR(0, 0),IR(1, 0),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5426,IR(0, 0),IR(12550, 23)/* Shader64BitIndexingEXT */,IR(0, 0),IR(1, 0),IR(90, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5430,IR(0, 0),IR(12573, 30)/* CooperativeMatrixReductionsNV */,IR(0, 0),IR(1, 0),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5431,IR(0, 0),IR(12603, 31)/* CooperativeMatrixConversionsNV */,IR(0, 0),IR(1, 0),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5432,IR(0, 0),IR(12634, 40)/* CooperativeMatrixPerElementOperationsNV */,IR(0, 0),IR(1, 0),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5433,IR(0, 0),IR(12674, 36)/* CooperativeMatrixTensorAddressingNV */,IR(0, 0),IR(1, 0),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5434,IR(0, 0),IR(12710, 30)/* CooperativeMatrixBlockLoadsNV */,IR(0, 0),IR(1, 0),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5435,IR(0, 0),IR(12740, 28)/* CooperativeVectorTrainingNV */,IR(0, 0),IR(1, 0),IR(87, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5437,IR(0, 0),IR(8576, 41)/* RayTracingClusterAccelerationStructureNV */,IR(0, 0),IR(60, 1),IR(31, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5439,IR(0, 0),IR(12768, 19)/* TensorAddressingNV */,IR(0, 0),IR(1, 0),IR(92, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5568,IR(0, 0),IR(12787, 21)/* SubgroupShuffleINTEL */,IR(0, 0),IR(1, 0),IR(93, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5569,IR(0, 0),IR(12808, 27)/* SubgroupBufferBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(93, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5570,IR(0, 0),IR(12835, 26)/* SubgroupImageBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(93, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5579,IR(0, 0),IR(12861, 31)/* SubgroupImageMediaBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(94, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5582,IR(0, 0),IR(12892, 21)/* RoundToInfinityINTEL */,IR(0, 0),IR(1, 0),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5583,IR(0, 0),IR(12913, 23)/* FloatingPointModeINTEL */,IR(0, 0),IR(1, 0),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5584,IR(0, 0),IR(12936, 23)/* IntegerFunctions2INTEL */,IR(0, 0),IR(1, 0),IR(96, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5603,IR(0, 0),IR(12959, 22)/* FunctionPointersINTEL */,IR(0, 0),IR(1, 0),IR(97, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5604,IR(0, 0),IR(12981, 24)/* IndirectReferencesINTEL */,IR(0, 0),IR(1, 0),IR(97, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5606,IR(0, 0),IR(13005, 9)/* AsmINTEL */,IR(0, 0),IR(1, 0),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5612,IR(0, 0),IR(13014, 23)/* AtomicFloat32MinMaxEXT */,IR(0, 0),IR(1, 0),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5613,IR(0, 0),IR(13037, 23)/* AtomicFloat64MinMaxEXT */,IR(0, 0),IR(1, 0),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5616,IR(0, 0),IR(13060, 23)/* AtomicFloat16MinMaxEXT */,IR(0, 0),IR(1, 0),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5617,IR(0, 0),IR(13083, 19)/* VectorComputeINTEL */,IR(0, 0),IR(104, 1),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5619,IR(0, 0),IR(13102, 15)/* VectorAnyINTEL */,IR(0, 0),IR(1, 0),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5629,IR(0, 0),IR(13117, 16)/* ExpectAssumeKHR */,IR(0, 0),IR(1, 0),IR(101, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5696,IR(0, 0),IR(13133, 33)/* SubgroupAvcMotionEstimationINTEL */,IR(0, 0),IR(1, 0),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5697,IR(0, 0),IR(13166, 38)/* SubgroupAvcMotionEstimationIntraINTEL */,IR(0, 0),IR(1, 0),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5698,IR(0, 0),IR(13204, 39)/* SubgroupAvcMotionEstimationChromaINTEL */,IR(0, 0),IR(1, 0),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5817,IR(0, 0),IR(13243, 25)/* VariableLengthArrayINTEL */,IR(0, 0),IR(1, 0),IR(103, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5821,IR(0, 0),IR(13268, 26)/* FunctionFloatControlINTEL */,IR(0, 0),IR(1, 0),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5824,IR(0, 0),IR(13294, 27)/* FPGAMemoryAttributesALTERA */,IR(46, 1),IR(1, 0),IR(104, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5837,IR(0, 0),IR(13347, 20)/* FPFastMathModeINTEL */,IR(0, 0),IR(0, 1),IR(106, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5844,IR(0, 0),IR(13367, 33)/* ArbitraryPrecisionIntegersALTERA */,IR(47, 1),IR(1, 0),IR(107, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5845,IR(0, 0),IR(13432, 38)/* ArbitraryPrecisionFloatingPointALTERA */,IR(48, 1),IR(1, 0),IR(109, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5886,IR(0, 0),IR(13507, 30)/* UnstructuredLoopControlsINTEL */,IR(0, 0),IR(1, 0),IR(111, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5888,IR(0, 0),IR(13537, 23)/* FPGALoopControlsALTERA */,IR(49, 1),IR(1, 0),IR(112, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5892,IR(0, 0),IR(13582, 22)/* KernelAttributesINTEL */,IR(0, 0),IR(1, 0),IR(114, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5897,IR(0, 0),IR(13604, 26)/* FPGAKernelAttributesINTEL */,IR(0, 0),IR(1, 0),IR(114, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5898,IR(0, 0),IR(13630, 25)/* FPGAMemoryAccessesALTERA */,IR(50, 1),IR(1, 0),IR(115, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5904,IR(0, 0),IR(13679, 28)/* FPGAClusterAttributesALTERA */,IR(51, 1),IR(1, 0),IR(117, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5906,IR(0, 0),IR(13734, 15)/* LoopFuseALTERA */,IR(52, 1),IR(1, 0),IR(119, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5908,IR(0, 0),IR(13763, 21)/* FPGADSPControlALTERA */,IR(53, 1),IR(1, 0),IR(121, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5910,IR(0, 0),IR(13804, 26)/* MemoryAccessAliasingINTEL */,IR(0, 0),IR(1, 0),IR(123, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5916,IR(0, 0),IR(13830, 41)/* FPGAInvocationPipeliningAttributesALTERA */,IR(54, 1),IR(1, 0),IR(124, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5920,IR(0, 0),IR(13911, 25)/* FPGABufferLocationALTERA */,IR(55, 1),IR(1, 0),IR(126, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5922,IR(0, 0),IR(13960, 35)/* ArbitraryPrecisionFixedPointALTERA */,IR(56, 1),IR(1, 0),IR(128, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5935,IR(0, 0),IR(14029, 24)/* USMStorageClassesALTERA */,IR(57, 1),IR(1, 0),IR(130, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5939,IR(0, 0),IR(14076, 30)/* RuntimeAlignedAttributeALTERA */,IR(58, 1),IR(1, 0),IR(132, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5943,IR(0, 0),IR(14135, 14)/* IOPipesALTERA */,IR(59, 1),IR(1, 0),IR(134, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5945,IR(0, 0),IR(14162, 20)/* BlockingPipesALTERA */,IR(60, 1),IR(1, 0),IR(136, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5948,IR(0, 0),IR(14201, 14)/* FPGARegALTERA */,IR(61, 1),IR(1, 0),IR(138, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6016,IR(0, 0),IR(14228, 19)/* DotProductInputAll */,IR(62, 1),IR(1, 0),IR(140, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6017,IR(0, 0),IR(14269, 22)/* DotProductInput4x8Bit */,IR(63, 1),IR(105, 1),IR(140, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6018,IR(0, 0),IR(14316, 28)/* DotProductInput4x8BitPacked */,IR(64, 1),IR(1, 0),IR(140, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6019,IR(0, 0),IR(14375, 11)/* DotProduct */,IR(65, 1),IR(1, 0),IR(140, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6020,IR(0, 0),IR(8629, 15)/* RayCullMaskKHR */,IR(0, 0),IR(1, 0),IR(32, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6022,IR(0, 0),IR(9832, 21)/* CooperativeMatrixKHR */,IR(0, 0),IR(1, 0),IR(141, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6024,IR(0, 0),IR(14400, 24)/* ReplicatedCompositesEXT */,IR(0, 0),IR(1, 0),IR(142, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6025,IR(0, 0),IR(14424, 16)/* BitInstructions */,IR(0, 0),IR(1, 0),IR(143, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6026,IR(0, 0),IR(14440, 25)/* GroupNonUniformRotateKHR */,IR(0, 0),IR(76, 1),IR(144, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6029,IR(0, 0),IR(14465, 15)/* FloatControls2 */,IR(0, 0),IR(1, 0),IR(145, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6030,IR(0, 0),IR(14480, 7)/* FMAKHR */,IR(0, 0),IR(1, 0),IR(146, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6033,IR(0, 0),IR(14487, 20)/* AtomicFloat32AddEXT */,IR(0, 0),IR(1, 0),IR(147, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6034,IR(0, 0),IR(14507, 20)/* AtomicFloat64AddEXT */,IR(0, 0),IR(1, 0),IR(147, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6089,IR(0, 0),IR(14527, 20)/* LongCompositesINTEL */,IR(0, 0),IR(1, 0),IR(148, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6094,IR(0, 0),IR(14547, 11)/* OptNoneEXT */,IR(66, 1),IR(1, 0),IR(149, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6095,IR(0, 0),IR(14571, 20)/* AtomicFloat16AddEXT */,IR(0, 0),IR(1, 0),IR(151, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6114,IR(0, 0),IR(14591, 21)/* DebugInfoModuleINTEL */,IR(0, 0),IR(1, 0),IR(152, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6115,IR(0, 0),IR(14612, 24)/* BFloat16ConversionINTEL */,IR(0, 0),IR(1, 0),IR(153, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6141,IR(0, 0),IR(14636, 18)/* SplitBarrierINTEL */,IR(0, 0),IR(1, 0),IR(154, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6144,IR(0, 0),IR(14654, 19)/* ArithmeticFenceEXT */,IR(0, 0),IR(1, 0),IR(155, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6150,IR(0, 0),IR(14673, 30)/* FPGAClusterAttributesV2ALTERA */,IR(67, 1),IR(106, 1),IR(117, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6161,IR(0, 0),IR(14732, 28)/* FPGAKernelAttributesv2INTEL */,IR(0, 0),IR(107, 1),IR(114, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6162,IR(0, 0),IR(14760, 19)/* TaskSequenceALTERA */,IR(68, 1),IR(1, 0),IR(156, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6169,IR(0, 0),IR(14797, 16)/* FPMaxErrorINTEL */,IR(0, 0),IR(1, 0),IR(158, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6171,IR(0, 0),IR(14813, 25)/* FPGALatencyControlALTERA */,IR(69, 1),IR(1, 0),IR(159, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6174,IR(0, 0),IR(14862, 29)/* FPGAArgumentInterfacesALTERA */,IR(70, 1),IR(1, 0),IR(161, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6187,IR(0, 0),IR(14919, 30)/* GlobalVariableHostAccessINTEL */,IR(0, 0),IR(1, 0),IR(163, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6189,IR(0, 0),IR(14949, 36)/* GlobalVariableFPGADecorationsALTERA */,IR(71, 1),IR(1, 0),IR(164, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6220,IR(0, 0),IR(15020, 28)/* SubgroupBufferPrefetchINTEL */,IR(0, 0),IR(1, 0),IR(166, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6228,IR(0, 0),IR(15048, 23)/* Subgroup2DBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(167, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6229,IR(0, 0),IR(15071, 30)/* Subgroup2DBlockTransformINTEL */,IR(0, 0),IR(108, 1),IR(167, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6230,IR(0, 0),IR(15101, 30)/* Subgroup2DBlockTransposeINTEL */,IR(0, 0),IR(108, 1),IR(167, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6236,IR(0, 0),IR(15131, 38)/* SubgroupMatrixMultiplyAccumulateINTEL */,IR(0, 0),IR(1, 0),IR(168, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6241,IR(0, 0),IR(15169, 28)/* TernaryBitwiseFunctionINTEL */,IR(0, 0),IR(1, 0),IR(169, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6243,IR(0, 0),IR(15197, 32)/* UntypedVariableLengthArrayINTEL */,IR(0, 0),IR(109, 2),IR(103, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6245,IR(0, 0),IR(15229, 21)/* SpecConditionalINTEL */,IR(0, 0),IR(1, 0),IR(170, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6246,IR(0, 0),IR(15250, 22)/* FunctionVariantsINTEL */,IR(0, 0),IR(111, 1),IR(170, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6400,IR(0, 0),IR(15272, 26)/* GroupUniformArithmeticKHR */,IR(0, 0),IR(1, 0),IR(171, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6425,IR(0, 0),IR(15298, 27)/* TensorFloat32RoundingINTEL */,IR(0, 0),IR(1, 0),IR(172, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6427,IR(0, 0),IR(15325, 25)/* MaskedGatherScatterINTEL */,IR(0, 0),IR(1, 0),IR(173, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6441,IR(0, 0),IR(15350, 19)/* CacheControlsINTEL */,IR(0, 0),IR(1, 0),IR(174, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6460,IR(0, 0),IR(15369, 20)/* RegisterLimitsINTEL */,IR(0, 0),IR(1, 0),IR(175, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6528,IR(0, 0),IR(15389, 20)/* BindlessImagesINTEL */,IR(0, 0),IR(1, 0),IR(176, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {0,IR(0, 0),IR(15409, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(15421, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(15429, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {3,IR(0, 0),IR(15437, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(15443, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(15450, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(15461, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(15470, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(15483, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(15489, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(15499, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(15505, 15)/* ImportedModule */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {1,IR(0, 0),IR(15520, 20)/* ImportedDeclaration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {0,IR(0, 0),IR(15540, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(15545, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(15561, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(15575, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(15588, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(15600, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(15617, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(15629, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(15644, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(15657, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(15672, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(15690, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(15707, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(15728, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(15748, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(15768, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {16384,IR(0, 0),IR(15784, 16)/* FlagIsEnumClass */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {32768,IR(0, 0),IR(15800, 20)/* FlagTypePassByValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {65536,IR(0, 0),IR(15820, 24)/* FlagTypePassByReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(15844, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {1,IR(0, 0),IR(15850, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {2,IR(0, 0),IR(15855, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {3,IR(0, 1),IR(15894, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {4,IR(1, 2),IR(15905, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {5,IR(0, 0),IR(15914, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {6,IR(0, 0),IR(15919, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {7,IR(0, 0),IR(15926, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {8,IR(0, 1),IR(15937, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {9,IR(1, 2),IR(15944, 9)/* Fragment */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {0,IR(0, 0),IR(15953, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(15963, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(15976, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {3,IR(0, 0),IR(15989, 11)/* AtomicType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(16000, 10)/* Float16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1,IR(0, 0),IR(16010, 10)/* Float32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {2,IR(0, 0),IR(16020, 10)/* Float64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {3,IR(0, 0),IR(16030, 13)/* SignedInt8NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {4,IR(0, 0),IR(16043, 14)/* SignedInt16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {5,IR(0, 0),IR(16057, 14)/* SignedInt32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {6,IR(0, 0),IR(16071, 14)/* SignedInt64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {7,IR(0, 0),IR(16085, 15)/* UnsignedInt8NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {8,IR(0, 0),IR(16100, 16)/* UnsignedInt16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {9,IR(0, 0),IR(16116, 16)/* UnsignedInt32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {10,IR(0, 0),IR(16132, 16)/* UnsignedInt64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491000,IR(0, 0),IR(16148, 19)/* SignedInt8PackedNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491001,IR(0, 0),IR(16167, 21)/* UnsignedInt8PackedNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491002,IR(0, 0),IR(16188, 12)/* FloatE4M3NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491003,IR(0, 0),IR(16200, 12)/* FloatE5M2NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {0,IR(0, 0),IR(16212, 12)/* RowMajorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {1,IR(0, 0),IR(16224, 15)/* ColumnMajorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {4202,IR(0, 0),IR(16239, 25)/* RowBlockedInterleavedARM */,IR(0, 0),IR(112, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {4203,IR(0, 0),IR(16264, 28)/* ColumnBlockedInterleavedARM */,IR(0, 0),IR(112, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {0,IR(0, 0),IR(16292, 8)/* NoneKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {1,IR(0, 0),IR(16300, 27)/* MatrixASignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {2,IR(0, 0),IR(16327, 27)/* MatrixBSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {4,IR(0, 0),IR(16354, 27)/* MatrixCSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {8,IR(0, 0),IR(16381, 32)/* MatrixResultSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {16,IR(0, 0),IR(16413, 26)/* SaturatingAccumulationKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {1,IR(0, 0),IR(16439, 4)/* Row */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {2,IR(0, 0),IR(16443, 7)/* Column */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {4,IR(0, 0),IR(16450, 4)/* 2x2 */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {0,IR(0, 0),IR(16454, 11)/* MatrixAKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {1,IR(0, 0),IR(16465, 11)/* MatrixBKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {2,IR(0, 0),IR(16476, 21)/* MatrixAccumulatorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {0,IR(0, 0),IR(16497, 11)/* RowMajorNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {1,IR(0, 0),IR(16508, 14)/* ColumnMajorNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {2,IR(0, 0),IR(16522, 21)/* InferencingOptimalNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {3,IR(0, 0),IR(16543, 18)/* TrainingOptimalNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {0,IR(0, 0),IR(15409, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(15421, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(15429, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(15437, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(15443, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(15450, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(15461, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {8,IR(0, 0),IR(15470, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(15483, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(15489, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(15499, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(15540, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(15545, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(15561, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(15575, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(15588, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(15600, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(15617, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(15629, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(15644, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(15657, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(15672, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(15690, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(15707, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(15728, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(15748, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(15768, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(15844, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {1,IR(0, 0),IR(15850, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {2,IR(0, 0),IR(15855, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {3,IR(0, 1),IR(15894, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {4,IR(1, 2),IR(15905, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {5,IR(0, 0),IR(15914, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {6,IR(0, 0),IR(15919, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {7,IR(0, 0),IR(15926, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {8,IR(0, 1),IR(15937, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {0,IR(0, 0),IR(15953, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(15963, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(15976, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(16561, 17)/* RelaxedPrecision */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {1,IR(0, 1),IR(16578, 7)/* SpecId */,IR(0, 0),IR(113, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {2,IR(0, 0),IR(16585, 6)/* Block */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {3,IR(0, 0),IR(16591, 12)/* BufferBlock */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),SPV_SPIRV_VERSION_WORD(1,3)}, // SPV_OPERAND_TYPE_DECORATION
  {4,IR(0, 0),IR(16603, 9)/* RowMajor */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5,IR(0, 0),IR(16612, 9)/* ColMajor */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6,IR(0, 1),IR(16621, 12)/* ArrayStride */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {7,IR(0, 1),IR(16633, 13)/* MatrixStride */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {8,IR(0, 0),IR(16646, 11)/* GLSLShared */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {9,IR(0, 0),IR(16657, 11)/* GLSLPacked */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {10,IR(0, 0),IR(16668, 8)/* CPacked */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {11,IR(3, 1),IR(16702, 8)/* BuiltIn */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {13,IR(0, 0),IR(16710, 14)/* NoPerspective */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {14,IR(0, 0),IR(16724, 5)/* Flat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {15,IR(0, 0),IR(16729, 6)/* Patch */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {16,IR(0, 0),IR(16735, 9)/* Centroid */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {17,IR(0, 0),IR(16744, 7)/* Sample */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {18,IR(0, 0),IR(16751, 10)/* Invariant */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {19,IR(0, 0),IR(16761, 9)/* Restrict */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {20,IR(0, 0),IR(16770, 8)/* Aliased */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {21,IR(0, 0),IR(16778, 9)/* Volatile */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {22,IR(0, 0),IR(16787, 9)/* Constant */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {23,IR(0, 0),IR(16796, 9)/* Coherent */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {24,IR(0, 0),IR(16805, 12)/* NonWritable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {25,IR(0, 0),IR(16817, 12)/* NonReadable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {26,IR(0, 0),IR(16829, 8)/* Uniform */,IR(0, 0),IR(115, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {27,IR(4, 1),IR(16863, 10)/* UniformId */,IR(0, 0),IR(115, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {28,IR(0, 0),IR(16873, 20)/* SaturatedConversion */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {29,IR(0, 1),IR(16893, 7)/* Stream */,IR(0, 0),IR(117, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {30,IR(0, 1),IR(16900, 9)/* Location */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {31,IR(0, 1),IR(16909, 10)/* Component */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {32,IR(0, 1),IR(16919, 6)/* Index */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {33,IR(0, 1),IR(16925, 8)/* Binding */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {34,IR(0, 1),IR(16933, 14)/* DescriptorSet */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {35,IR(0, 1),IR(16947, 7)/* Offset */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {36,IR(0, 1),IR(16954, 10)/* XfbBuffer */,IR(0, 0),IR(118, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {37,IR(0, 1),IR(16964, 10)/* XfbStride */,IR(0, 0),IR(118, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {38,IR(5, 1),IR(17020, 14)/* FuncParamAttr */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {39,IR(6, 1),IR(17068, 15)/* FPRoundingMode */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {40,IR(7, 1),IR(17118, 15)/* FPFastMathMode */,IR(0, 0),IR(119, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {41,IR(8, 2),IR(17195, 18)/* LinkageAttributes */,IR(0, 0),IR(121, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {42,IR(0, 0),IR(17213, 14)/* NoContraction */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {43,IR(0, 1),IR(17227, 21)/* InputAttachmentIndex */,IR(0, 0),IR(95, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {44,IR(0, 1),IR(17248, 10)/* Alignment */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {45,IR(0, 1),IR(17258, 14)/* MaxByteOffset */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {46,IR(10, 1),IR(17292, 12)/* AlignmentId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {47,IR(10, 1),IR(17304, 16)/* MaxByteOffsetId */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4216,IR(0, 0),IR(17320, 44)/* SaturatedToLargestFloat8NormalConversionEXT */,IR(0, 0),IR(122, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4469,IR(0, 0),IR(17364, 13)/* NoSignedWrap */,IR(0, 0),IR(1, 0),IR(177, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4470,IR(0, 0),IR(17377, 15)/* NoUnsignedWrap */,IR(0, 0),IR(1, 0),IR(177, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4487,IR(0, 0),IR(17392, 18)/* WeightTextureQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4488,IR(0, 0),IR(17410, 22)/* BlockMatchTextureQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4499,IR(0, 0),IR(17432, 22)/* BlockMatchSamplerQCOM */,IR(0, 0),IR(1, 0),IR(55, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4999,IR(0, 0),IR(17454, 18)/* ExplicitInterpAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5019,IR(10, 1),IR(17472, 32)/* NodeSharesPayloadLimitsWithAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5020,IR(10, 1),IR(17504, 20)/* NodeMaxPayloadsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5078,IR(0, 0),IR(17524, 23)/* TrackFinishWritingAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5091,IR(10, 1),IR(17547, 20)/* PayloadNodeNameAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5098,IR(10, 1),IR(17567, 25)/* PayloadNodeBaseIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5099,IR(0, 0),IR(17592, 27)/* PayloadNodeSparseArrayAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5100,IR(10, 1),IR(17619, 25)/* PayloadNodeArraySizeAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5105,IR(0, 0),IR(17644, 28)/* PayloadDispatchIndirectAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5248,IR(0, 0),IR(17672, 19)/* OverrideCoverageNV */,IR(0, 0),IR(123, 1),IR(66, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5250,IR(0, 0),IR(17691, 14)/* PassthroughNV */,IR(0, 0),IR(124, 1),IR(67, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5252,IR(0, 0),IR(17705, 19)/* ViewportRelativeNV */,IR(0, 0),IR(94, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5256,IR(0, 1),IR(17724, 28)/* SecondaryViewportRelativeNV */,IR(0, 0),IR(46, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5271,IR(0, 0),IR(17752, 16)/* PerPrimitiveEXT */,IR(72, 1),IR(125, 2),IR(178, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5272,IR(0, 0),IR(17783, 10)/* PerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5273,IR(0, 0),IR(17793, 10)/* PerTaskNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5285,IR(0, 0),IR(17803, 13)/* PerVertexKHR */,IR(73, 1),IR(51, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5300,IR(0, 0),IR(17828, 11)/* NonUniform */,IR(74, 1),IR(97, 1),IR(76, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5355,IR(0, 0),IR(17853, 16)/* RestrictPointer */,IR(75, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5356,IR(0, 0),IR(17888, 15)/* AliasedPointer */,IR(76, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5386,IR(0, 0),IR(17921, 30)/* HitObjectShaderRecordBufferNV */,IR(0, 0),IR(127, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5389,IR(0, 0),IR(17951, 31)/* HitObjectShaderRecordBufferEXT */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5398,IR(0, 0),IR(17982, 18)/* BindlessSamplerNV */,IR(0, 0),IR(129, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5399,IR(0, 0),IR(18000, 16)/* BindlessImageNV */,IR(0, 0),IR(129, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5400,IR(0, 0),IR(18016, 15)/* BoundSamplerNV */,IR(0, 0),IR(129, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5401,IR(0, 0),IR(18031, 13)/* BoundImageNV */,IR(0, 0),IR(129, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5599,IR(0, 1),IR(18044, 14)/* SIMTCallINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5602,IR(0, 0),IR(18058, 26)/* ReferencedIndirectlyINTEL */,IR(0, 0),IR(131, 1),IR(97, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5607,IR(11, 1),IR(18084, 13)/* ClobberINTEL */,IR(0, 0),IR(132, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5608,IR(0, 0),IR(18097, 17)/* SideEffectsINTEL */,IR(0, 0),IR(132, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5624,IR(0, 0),IR(18114, 27)/* VectorComputeVariableINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5625,IR(0, 1),IR(18141, 21)/* FuncParamIOKindINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5626,IR(0, 0),IR(18162, 27)/* VectorComputeFunctionINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5627,IR(0, 0),IR(18189, 15)/* StackCallINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5628,IR(0, 1),IR(18204, 26)/* GlobalVariableOffsetINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5634,IR(10, 1),IR(18230, 14)/* CounterBuffer */,IR(77, 1),IR(1, 0),IR(180, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5635,IR(11, 1),IR(18268, 13)/* UserSemantic */,IR(78, 1),IR(1, 0),IR(180, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5636,IR(11, 1),IR(18300, 15)/* UserTypeGOOGLE */,IR(0, 0),IR(1, 0),IR(181, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5822,IR(12, 2),IR(18315, 26)/* FunctionRoundingModeINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5823,IR(14, 2),IR(18372, 24)/* FunctionDenormModeINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5825,IR(0, 0),IR(18396, 15)/* RegisterALTERA */,IR(79, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5826,IR(11, 1),IR(18425, 13)/* MemoryALTERA */,IR(80, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5827,IR(0, 1),IR(18450, 15)/* NumbanksALTERA */,IR(81, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5828,IR(0, 1),IR(18479, 16)/* BankwidthALTERA */,IR(82, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5829,IR(0, 1),IR(18510, 23)/* MaxPrivateCopiesALTERA */,IR(83, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5830,IR(0, 0),IR(18555, 17)/* SinglepumpALTERA */,IR(84, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5831,IR(0, 0),IR(18588, 17)/* DoublepumpALTERA */,IR(85, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5832,IR(0, 1),IR(18621, 20)/* MaxReplicatesALTERA */,IR(86, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5833,IR(0, 0),IR(18660, 21)/* SimpleDualPortALTERA */,IR(87, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5834,IR(16, 2),IR(18701, 12)/* MergeALTERA */,IR(88, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5835,IR(18, 1),IR(18766, 15)/* BankBitsALTERA */,IR(89, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5836,IR(0, 1),IR(18795, 21)/* ForcePow2DepthALTERA */,IR(90, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5883,IR(0, 1),IR(18836, 17)/* StridesizeALTERA */,IR(91, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5884,IR(0, 1),IR(18869, 15)/* WordsizeALTERA */,IR(92, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5885,IR(0, 0),IR(18898, 19)/* TrueDualPortALTERA */,IR(93, 1),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5899,IR(0, 0),IR(18935, 20)/* BurstCoalesceALTERA */,IR(94, 1),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5900,IR(0, 1),IR(18974, 16)/* CacheSizeALTERA */,IR(95, 1),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5901,IR(0, 0),IR(19005, 29)/* DontStaticallyCoalesceALTERA */,IR(96, 1),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5902,IR(0, 1),IR(19062, 15)/* PrefetchALTERA */,IR(97, 1),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5905,IR(0, 0),IR(19091, 18)/* StallEnableALTERA */,IR(98, 1),IR(106, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5907,IR(0, 0),IR(19126, 26)/* FuseLoopsInFunctionALTERA */,IR(99, 1),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5909,IR(1, 2),IR(19177, 20)/* MathOpDSPModeALTERA */,IR(100, 1),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5914,IR(10, 1),IR(19216, 16)/* AliasScopeINTEL */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5915,IR(10, 1),IR(19232, 13)/* NoAliasINTEL */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5917,IR(0, 1),IR(19245, 25)/* InitiationIntervalALTERA */,IR(101, 1),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5918,IR(0, 1),IR(19294, 21)/* MaxConcurrencyALTERA */,IR(102, 1),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5919,IR(0, 1),IR(19335, 21)/* PipelineEnableALTERA */,IR(103, 1),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5921,IR(0, 1),IR(19376, 21)/* BufferLocationALTERA */,IR(104, 1),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5944,IR(0, 1),IR(19417, 20)/* IOPipeStorageALTERA */,IR(105, 1),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6080,IR(19, 2),IR(19490, 31)/* FunctionFloatingPointModeINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6085,IR(0, 0),IR(19521, 25)/* SingleElementVectorINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6087,IR(0, 0),IR(19546, 35)/* VectorComputeCallableFunctionINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6140,IR(0, 0),IR(19581, 18)/* MediaBlockIOINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6151,IR(0, 0),IR(19599, 16)/* StallFreeALTERA */,IR(106, 1),IR(142, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6170,IR(21, 1),IR(19661, 26)/* FPMaxErrorDecorationINTEL */,IR(0, 0),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6172,IR(0, 1),IR(19687, 26)/* LatencyControlLabelALTERA */,IR(107, 1),IR(144, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6173,IR(22, 3),IR(19738, 31)/* LatencyControlConstraintALTERA */,IR(108, 1),IR(144, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6175,IR(0, 0),IR(19799, 28)/* ConduitKernelArgumentALTERA */,IR(109, 1),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6176,IR(0, 0),IR(19854, 32)/* RegisterMapKernelArgumentALTERA */,IR(110, 1),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6177,IR(0, 1),IR(19917, 34)/* MMHostInterfaceAddressWidthALTERA */,IR(111, 1),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6178,IR(0, 1),IR(19984, 31)/* MMHostInterfaceDataWidthALTERA */,IR(112, 1),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6179,IR(0, 1),IR(20045, 29)/* MMHostInterfaceLatencyALTERA */,IR(113, 1),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6180,IR(25, 1),IR(20136, 35)/* MMHostInterfaceReadWriteModeALTERA */,IR(114, 1),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6181,IR(0, 1),IR(20205, 30)/* MMHostInterfaceMaxBurstALTERA */,IR(115, 1),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6182,IR(0, 1),IR(20264, 33)/* MMHostInterfaceWaitRequestALTERA */,IR(116, 1),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6183,IR(0, 0),IR(20329, 27)/* StableKernelArgumentALTERA */,IR(117, 1),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6188,IR(26, 2),IR(20421, 16)/* HostAccessINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6190,IR(28, 1),IR(20484, 15)/* InitModeALTERA */,IR(118, 1),IR(147, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6191,IR(0, 1),IR(20513, 29)/* ImplementInRegisterMapALTERA */,IR(119, 1),IR(147, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6247,IR(10, 1),IR(20570, 17)/* ConditionalINTEL */,IR(0, 0),IR(111, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6442,IR(29, 2),IR(20623, 22)/* CacheControlLoadINTEL */,IR(0, 0),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6443,IR(31, 2),IR(20682, 23)/* CacheControlStoreINTEL */,IR(0, 0),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {0,IR(0, 0),IR(20705, 3)/* 1D */,IR(0, 0),IR(72, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {1,IR(0, 0),IR(20708, 3)/* 2D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {2,IR(0, 0),IR(20711, 3)/* 3D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {3,IR(0, 0),IR(20714, 5)/* Cube */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {4,IR(0, 0),IR(20719, 5)/* Rect */,IR(0, 0),IR(71, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {5,IR(0, 0),IR(20724, 7)/* Buffer */,IR(0, 0),IR(73, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {6,IR(0, 0),IR(20731, 12)/* SubpassData */,IR(0, 0),IR(95, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {4173,IR(0, 0),IR(20743, 17)/* TileImageDataEXT */,IR(0, 0),IR(149, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {0,IR(0, 1),IR(20760, 12)/* Invocations */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {1,IR(0, 0),IR(20772, 13)/* SpacingEqual */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {2,IR(0, 0),IR(20785, 22)/* SpacingFractionalEven */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {3,IR(0, 0),IR(20807, 21)/* SpacingFractionalOdd */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4,IR(0, 0),IR(20828, 14)/* VertexOrderCw */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5,IR(0, 0),IR(20842, 15)/* VertexOrderCcw */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6,IR(0, 0),IR(20857, 19)/* PixelCenterInteger */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {7,IR(0, 0),IR(20876, 16)/* OriginUpperLeft */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {8,IR(0, 0),IR(20892, 16)/* OriginLowerLeft */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {9,IR(0, 0),IR(20908, 19)/* EarlyFragmentTests */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {10,IR(0, 0),IR(20927, 10)/* PointMode */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {11,IR(0, 0),IR(20937, 4)/* Xfb */,IR(0, 0),IR(118, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {12,IR(0, 0),IR(20941, 15)/* DepthReplacing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {14,IR(0, 0),IR(20956, 13)/* DepthGreater */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {15,IR(0, 0),IR(20969, 10)/* DepthLess */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {16,IR(0, 0),IR(20979, 15)/* DepthUnchanged */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {17,IR(22, 3),IR(20994, 10)/* LocalSize */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {18,IR(22, 3),IR(21004, 14)/* LocalSizeHint */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {19,IR(0, 0),IR(21018, 12)/* InputPoints */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {20,IR(0, 0),IR(21030, 11)/* InputLines */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {21,IR(0, 0),IR(21041, 20)/* InputLinesAdjacency */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {22,IR(0, 0),IR(21061, 10)/* Triangles */,IR(0, 0),IR(12, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {23,IR(0, 0),IR(21071, 24)/* InputTrianglesAdjacency */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {24,IR(0, 0),IR(21095, 6)/* Quads */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {25,IR(0, 0),IR(21101, 9)/* Isolines */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {26,IR(0, 1),IR(21110, 15)/* OutputVertices */,IR(0, 0),IR(150, 4),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {27,IR(0, 0),IR(21125, 13)/* OutputPoints */,IR(0, 0),IR(154, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {28,IR(0, 0),IR(21138, 16)/* OutputLineStrip */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {29,IR(0, 0),IR(21154, 20)/* OutputTriangleStrip */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {30,IR(0, 1),IR(21174, 12)/* VecTypeHint */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {31,IR(0, 0),IR(21186, 15)/* ContractionOff */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {33,IR(0, 0),IR(21201, 12)/* Initializer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {34,IR(0, 0),IR(21213, 10)/* Finalizer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {35,IR(0, 1),IR(6109, 13)/* SubgroupSize */,IR(0, 0),IR(157, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {36,IR(0, 1),IR(21223, 22)/* SubgroupsPerWorkgroup */,IR(0, 0),IR(157, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {37,IR(10, 1),IR(21245, 24)/* SubgroupsPerWorkgroupId */,IR(0, 0),IR(157, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {38,IR(33, 3),IR(21269, 12)/* LocalSizeId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {39,IR(33, 3),IR(21281, 16)/* LocalSizeHintId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4169,IR(0, 0),IR(21297, 34)/* NonCoherentColorAttachmentReadEXT */,IR(0, 0),IR(149, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4170,IR(0, 0),IR(21331, 34)/* NonCoherentDepthAttachmentReadEXT */,IR(0, 0),IR(158, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4171,IR(0, 0),IR(21365, 36)/* NonCoherentStencilAttachmentReadEXT */,IR(0, 0),IR(159, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4421,IR(0, 0),IR(21401, 30)/* SubgroupUniformControlFlowKHR */,IR(0, 0),IR(3, 1),IR(182, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4446,IR(0, 0),IR(21431, 18)/* PostDepthCoverage */,IR(0, 0),IR(160, 1),IR(45, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4459,IR(0, 1),IR(10308, 15)/* DenormPreserve */,IR(0, 0),IR(161, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4460,IR(0, 1),IR(10323, 18)/* DenormFlushToZero */,IR(0, 0),IR(162, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4461,IR(0, 1),IR(10341, 25)/* SignedZeroInfNanPreserve */,IR(0, 0),IR(163, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4462,IR(0, 1),IR(10366, 16)/* RoundingModeRTE */,IR(0, 0),IR(164, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4463,IR(0, 1),IR(10382, 16)/* RoundingModeRTZ */,IR(0, 0),IR(165, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4489,IR(0, 0),IR(21449, 34)/* NonCoherentTileAttachmentReadQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4490,IR(22, 3),IR(21483, 20)/* TileShadingRateQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5017,IR(0, 0),IR(21503, 29)/* EarlyAndLateFragmentTestsAMD */,IR(0, 0),IR(3, 1),IR(183, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5027,IR(0, 0),IR(21532, 23)/* StencilRefReplacingEXT */,IR(0, 0),IR(42, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5069,IR(0, 0),IR(21555, 15)/* CoalescingAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5070,IR(10, 1),IR(21570, 15)/* IsApiEntryAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5071,IR(10, 1),IR(21585, 21)/* MaxNodeRecursionAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5072,IR(33, 3),IR(21606, 24)/* StaticNumWorkgroupsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5073,IR(10, 1),IR(7002, 16)/* ShaderIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5077,IR(33, 3),IR(21630, 21)/* MaxNumWorkgroupsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5079,IR(0, 0),IR(21651, 28)/* StencilRefUnchangedFrontAMD */,IR(0, 0),IR(42, 1),IR(184, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5080,IR(0, 0),IR(21679, 26)/* StencilRefGreaterFrontAMD */,IR(0, 0),IR(42, 1),IR(184, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5081,IR(0, 0),IR(21705, 23)/* StencilRefLessFrontAMD */,IR(0, 0),IR(42, 1),IR(184, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5082,IR(0, 0),IR(21728, 27)/* StencilRefUnchangedBackAMD */,IR(0, 0),IR(42, 1),IR(184, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5083,IR(0, 0),IR(21755, 25)/* StencilRefGreaterBackAMD */,IR(0, 0),IR(42, 1),IR(184, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5084,IR(0, 0),IR(21780, 22)/* StencilRefLessBackAMD */,IR(0, 0),IR(42, 1),IR(184, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5088,IR(0, 0),IR(21802, 19)/* QuadDerivativesKHR */,IR(0, 0),IR(166, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5089,IR(0, 0),IR(21821, 20)/* RequireFullQuadsKHR */,IR(0, 0),IR(166, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5102,IR(36, 2),IR(21841, 20)/* SharesInputWithAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5269,IR(0, 0),IR(21861, 15)/* OutputLinesEXT */,IR(120, 1),IR(125, 2),IR(178, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5270,IR(0, 1),IR(21890, 20)/* OutputPrimitivesEXT */,IR(121, 1),IR(125, 2),IR(178, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5289,IR(0, 0),IR(21929, 24)/* DerivativeGroupQuadsKHR */,IR(122, 1),IR(167, 1),IR(73, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5290,IR(0, 0),IR(21976, 25)/* DerivativeGroupLinearKHR */,IR(123, 1),IR(168, 1),IR(73, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5298,IR(0, 0),IR(22025, 19)/* OutputTrianglesEXT */,IR(124, 1),IR(125, 2),IR(178, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5366,IR(0, 0),IR(22062, 25)/* PixelInterlockOrderedEXT */,IR(0, 0),IR(169, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5367,IR(0, 0),IR(22087, 27)/* PixelInterlockUnorderedEXT */,IR(0, 0),IR(169, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5368,IR(0, 0),IR(22114, 26)/* SampleInterlockOrderedEXT */,IR(0, 0),IR(170, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5369,IR(0, 0),IR(22140, 28)/* SampleInterlockUnorderedEXT */,IR(0, 0),IR(170, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5370,IR(0, 0),IR(22168, 31)/* ShadingRateInterlockOrderedEXT */,IR(0, 0),IR(171, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5371,IR(0, 0),IR(22199, 33)/* ShadingRateInterlockUnorderedEXT */,IR(0, 0),IR(171, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5427,IR(0, 0),IR(12550, 23)/* Shader64BitIndexingEXT */,IR(0, 0),IR(172, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5618,IR(0, 1),IR(22232, 27)/* SharedLocalMemorySizeINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5620,IR(0, 1),IR(22259, 21)/* RoundingModeRTPINTEL */,IR(0, 0),IR(173, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5621,IR(0, 1),IR(22280, 21)/* RoundingModeRTNINTEL */,IR(0, 0),IR(173, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5622,IR(0, 1),IR(22301, 26)/* FloatingPointModeALTINTEL */,IR(0, 0),IR(173, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5623,IR(0, 1),IR(22327, 27)/* FloatingPointModeIEEEINTEL */,IR(0, 0),IR(173, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5893,IR(22, 3),IR(22354, 22)/* MaxWorkgroupSizeINTEL */,IR(0, 0),IR(174, 1),IR(114, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5894,IR(0, 1),IR(22376, 16)/* MaxWorkDimINTEL */,IR(0, 0),IR(174, 1),IR(114, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5895,IR(0, 0),IR(22392, 20)/* NoGlobalOffsetINTEL */,IR(0, 0),IR(174, 1),IR(114, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5896,IR(0, 1),IR(22412, 22)/* NumSIMDWorkitemsINTEL */,IR(0, 0),IR(107, 1),IR(114, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5903,IR(0, 1),IR(22434, 28)/* SchedulerTargetFmaxMhzINTEL */,IR(0, 0),IR(107, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6023,IR(0, 0),IR(22462, 24)/* MaximallyReconvergesKHR */,IR(0, 0),IR(3, 1),IR(186, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6028,IR(36, 2),IR(22486, 18)/* FPFastMathDefault */,IR(0, 0),IR(175, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6154,IR(0, 1),IR(22504, 24)/* StreamingInterfaceINTEL */,IR(0, 0),IR(107, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6160,IR(0, 1),IR(22528, 26)/* RegisterMapInterfaceINTEL */,IR(0, 0),IR(176, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6417,IR(0, 1),IR(22554, 23)/* NamedBarrierCountINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6461,IR(0, 1),IR(22577, 22)/* MaximumRegistersINTEL */,IR(0, 0),IR(177, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6462,IR(10, 1),IR(22599, 24)/* MaximumRegistersIdINTEL */,IR(0, 0),IR(177, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6463,IR(38, 1),IR(22674, 27)/* NamedMaximumRegistersINTEL */,IR(0, 0),IR(177, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {0,IR(0, 0),IR(22701, 7)/* Vertex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {1,IR(0, 0),IR(22708, 20)/* TessellationControl */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {2,IR(0, 0),IR(22728, 23)/* TessellationEvaluation */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {3,IR(0, 0),IR(5590, 9)/* Geometry */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {4,IR(0, 0),IR(15944, 9)/* Fragment */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5,IR(0, 0),IR(22751, 10)/* GLCompute */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {6,IR(0, 0),IR(5357, 7)/* Kernel */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5267,IR(0, 0),IR(22761, 7)/* TaskNV */,IR(0, 0),IR(50, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5268,IR(0, 0),IR(22768, 7)/* MeshNV */,IR(0, 0),IR(50, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5313,IR(0, 0),IR(22775, 17)/* RayGenerationKHR */,IR(125, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5314,IR(0, 0),IR(22808, 16)/* IntersectionKHR */,IR(126, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5315,IR(0, 0),IR(22839, 10)/* AnyHitKHR */,IR(127, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5316,IR(0, 0),IR(22858, 14)/* ClosestHitKHR */,IR(128, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5317,IR(0, 0),IR(22885, 8)/* MissKHR */,IR(129, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5318,IR(0, 0),IR(22900, 12)/* CallableKHR */,IR(130, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5364,IR(0, 0),IR(22923, 8)/* TaskEXT */,IR(0, 0),IR(53, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5365,IR(0, 0),IR(22931, 8)/* MeshEXT */,IR(0, 0),IR(53, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {0,IR(0, 0),IR(22939, 9)/* Preserve */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPDENORM_MODE
  {1,IR(0, 0),IR(22948, 12)/* FlushToZero */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPDENORM_MODE
  {0,IR(0, 0),IR(22960, 12)/* BFloat16KHR */,IR(0, 0),IR(89, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {4214,IR(0, 0),IR(22972, 14)/* Float8E4M3EXT */,IR(0, 0),IR(122, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {4215,IR(0, 0),IR(22986, 14)/* Float8E5M2EXT */,IR(0, 0),IR(122, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {0,IR(0, 0),IR(23000, 5)/* IEEE */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPOPERATION_MODE
  {1,IR(0, 0),IR(23005, 4)/* ALT */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPOPERATION_MODE
  {0,IR(0, 0),IR(15540, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {1,IR(0, 0),IR(23009, 7)/* NotNaN */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {2,IR(0, 0),IR(23016, 7)/* NotInf */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {4,IR(0, 0),IR(23023, 4)/* NSZ */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {8,IR(0, 0),IR(23027, 11)/* AllowRecip */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {16,IR(0, 0),IR(23038, 5)/* Fast */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {65536,IR(0, 0),IR(23043, 14)/* AllowContract */,IR(131, 1),IR(178, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {131072,IR(0, 0),IR(23080, 13)/* AllowReassoc */,IR(132, 1),IR(178, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {262144,IR(0, 0),IR(23111, 15)/* AllowTransform */,IR(0, 0),IR(175, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {0,IR(0, 0),IR(23126, 4)/* RTE */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {1,IR(0, 0),IR(23130, 4)/* RTZ */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {2,IR(0, 0),IR(23134, 4)/* RTP */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {3,IR(0, 0),IR(23138, 4)/* RTN */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {1,IR(0, 0),IR(23142, 16)/* Vertical2Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {2,IR(0, 0),IR(23158, 16)/* Vertical4Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {4,IR(0, 0),IR(23174, 18)/* Horizontal2Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {8,IR(0, 0),IR(23192, 18)/* Horizontal4Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {0,IR(0, 0),IR(15540, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {1,IR(0, 0),IR(23210, 7)/* Inline */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {2,IR(0, 0),IR(23217, 11)/* DontInline */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {4,IR(0, 0),IR(23228, 5)/* Pure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {8,IR(0, 0),IR(23233, 6)/* Const */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {65536,IR(0, 0),IR(14547, 11)/* OptNoneEXT */,IR(66, 1),IR(180, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {0,IR(0, 0),IR(23239, 5)/* Zext */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {1,IR(0, 0),IR(23244, 5)/* Sext */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {2,IR(0, 0),IR(23249, 6)/* ByVal */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {3,IR(0, 0),IR(23255, 5)/* Sret */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {4,IR(0, 0),IR(23260, 8)/* NoAlias */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {5,IR(0, 0),IR(23268, 10)/* NoCapture */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {6,IR(0, 0),IR(23278, 8)/* NoWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {7,IR(0, 0),IR(23286, 12)/* NoReadWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {5940,IR(0, 0),IR(23298, 21)/* RuntimeAlignedALTERA */,IR(133, 1),IR(181, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {0,IR(0, 0),IR(23339, 7)/* Reduce */,IR(0, 0),IR(182, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {1,IR(0, 0),IR(23346, 14)/* InclusiveScan */,IR(0, 0),IR(182, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {2,IR(0, 0),IR(23360, 14)/* ExclusiveScan */,IR(0, 0),IR(182, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {3,IR(0, 0),IR(23374, 16)/* ClusteredReduce */,IR(0, 0),IR(185, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {6,IR(0, 0),IR(23390, 20)/* PartitionedReduceNV */,IR(0, 0),IR(186, 1),IR(75, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {7,IR(0, 0),IR(23410, 27)/* PartitionedInclusiveScanNV */,IR(0, 0),IR(186, 1),IR(75, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {8,IR(0, 0),IR(23437, 27)/* PartitionedExclusiveScanNV */,IR(0, 0),IR(186, 1),IR(75, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {0,IR(0, 0),IR(23464, 10)/* NoneINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {1,IR(0, 0),IR(23474, 10)/* ReadINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {2,IR(0, 0),IR(23484, 11)/* WriteINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {3,IR(0, 0),IR(23495, 15)/* ReadWriteINTEL */,IR(0, 0),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {0,IR(0, 0),IR(15540, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {1,IR(10, 1),IR(23510, 5)/* Bias */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {2,IR(10, 1),IR(23515, 4)/* Lod */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {4,IR(36, 2),IR(23519, 5)/* Grad */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {8,IR(10, 1),IR(23524, 12)/* ConstOffset */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {16,IR(10, 1),IR(16947, 7)/* Offset */,IR(0, 0),IR(187, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {32,IR(10, 1),IR(23536, 13)/* ConstOffsets */,IR(0, 0),IR(187, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {64,IR(10, 1),IR(16744, 7)/* Sample */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {128,IR(10, 1),IR(9141, 7)/* MinLod */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {256,IR(4, 1),IR(23549, 19)/* MakeTexelAvailable */,IR(134, 1),IR(189, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {512,IR(4, 1),IR(23590, 17)/* MakeTexelVisible */,IR(135, 1),IR(189, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {1024,IR(0, 0),IR(23627, 16)/* NonPrivateTexel */,IR(136, 1),IR(189, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {2048,IR(0, 0),IR(23662, 14)/* VolatileTexel */,IR(137, 1),IR(189, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {4096,IR(0, 0),IR(23693, 11)/* SignExtend */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {8192,IR(0, 0),IR(23704, 11)/* ZeroExtend */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {16384,IR(0, 0),IR(23715, 12)/* Nontemporal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {65536,IR(10, 1),IR(23727, 8)/* Offsets */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {0,IR(0, 0),IR(23735, 10)/* SnormInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {1,IR(0, 0),IR(23745, 11)/* SnormInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {2,IR(0, 0),IR(23756, 10)/* UnormInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {3,IR(0, 0),IR(23766, 11)/* UnormInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {4,IR(0, 0),IR(23777, 14)/* UnormShort565 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {5,IR(0, 0),IR(23791, 14)/* UnormShort555 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {6,IR(0, 0),IR(23805, 15)/* UnormInt101010 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {7,IR(0, 0),IR(23820, 11)/* SignedInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {8,IR(0, 0),IR(23831, 12)/* SignedInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {9,IR(0, 0),IR(23843, 12)/* SignedInt32 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {10,IR(0, 0),IR(23855, 13)/* UnsignedInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {11,IR(0, 0),IR(23868, 14)/* UnsignedInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {12,IR(0, 0),IR(23882, 14)/* UnsignedInt32 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {13,IR(0, 0),IR(23896, 10)/* HalfFloat */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {14,IR(0, 0),IR(15437, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {15,IR(0, 0),IR(23906, 11)/* UnormInt24 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {16,IR(0, 0),IR(23917, 17)/* UnormInt101010_2 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {17,IR(0, 0),IR(23934, 16)/* UnormInt10X6EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {19,IR(0, 0),IR(23950, 20)/* UnsignedIntRaw10EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {20,IR(0, 0),IR(23970, 20)/* UnsignedIntRaw12EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {21,IR(0, 0),IR(23990, 20)/* UnormInt2_101010EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {22,IR(0, 0),IR(24010, 19)/* UnsignedInt10X6EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {23,IR(0, 0),IR(24029, 19)/* UnsignedInt12X4EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {24,IR(0, 0),IR(24048, 19)/* UnsignedInt14X2EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {25,IR(0, 0),IR(24067, 16)/* UnormInt12X4EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {26,IR(0, 0),IR(24083, 16)/* UnormInt14X2EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {0,IR(0, 0),IR(24099, 2)/* R */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {1,IR(0, 0),IR(24101, 2)/* A */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {2,IR(0, 0),IR(24103, 3)/* RG */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {3,IR(0, 0),IR(24106, 3)/* RA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {4,IR(0, 0),IR(24109, 4)/* RGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {5,IR(0, 0),IR(24113, 5)/* RGBA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {6,IR(0, 0),IR(24118, 5)/* BGRA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {7,IR(0, 0),IR(24123, 5)/* ARGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {8,IR(0, 0),IR(24128, 10)/* Intensity */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {9,IR(0, 0),IR(24138, 10)/* Luminance */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {10,IR(0, 0),IR(24148, 3)/* Rx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {11,IR(0, 0),IR(24151, 4)/* RGx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {12,IR(0, 0),IR(24155, 5)/* RGBx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {13,IR(0, 0),IR(24160, 6)/* Depth */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {14,IR(0, 0),IR(24166, 13)/* DepthStencil */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {15,IR(0, 0),IR(24179, 5)/* sRGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {16,IR(0, 0),IR(24184, 6)/* sRGBx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {17,IR(0, 0),IR(24190, 6)/* sRGBA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {18,IR(0, 0),IR(24196, 6)/* sBGRA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {19,IR(0, 0),IR(24202, 5)/* ABGR */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {0,IR(0, 0),IR(24207, 28)/* InitOnDeviceReprogramALTERA */,IR(138, 1),IR(147, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {1,IR(0, 0),IR(24262, 24)/* InitOnDeviceResetALTERA */,IR(139, 1),IR(147, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {0,IR(0, 0),IR(24309, 7)/* NoWait */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {1,IR(0, 0),IR(24316, 11)/* WaitKernel */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {2,IR(0, 0),IR(24327, 14)/* WaitWorkGroup */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {0,IR(0, 0),IR(15540, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {1,IR(0, 0),IR(24341, 12)/* CmdExecTime */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {0,IR(0, 0),IR(15540, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {1,IR(0, 0),IR(24353, 13)/* MayUsePrintf */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {0,IR(0, 0),IR(24366, 7)/* Export */,IR(0, 0),IR(121, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {1,IR(0, 0),IR(24373, 7)/* Import */,IR(0, 0),IR(121, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {2,IR(0, 0),IR(24380, 12)/* LinkOnceODR */,IR(0, 0),IR(121, 1),IR(187, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {0,IR(0, 0),IR(24392, 14)/* UncachedINTEL */,IR(0, 0),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {1,IR(0, 0),IR(24406, 12)/* CachedINTEL */,IR(0, 0),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {2,IR(0, 0),IR(24418, 15)/* StreamingINTEL */,IR(0, 0),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {3,IR(0, 0),IR(24433, 25)/* InvalidateAfterReadINTEL */,IR(0, 0),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {4,IR(0, 0),IR(24458, 17)/* ConstCachedINTEL */,IR(0, 0),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {0,IR(0, 0),IR(15540, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {1,IR(0, 0),IR(24475, 7)/* Unroll */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {2,IR(0, 0),IR(24482, 11)/* DontUnroll */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {4,IR(0, 0),IR(24493, 19)/* DependencyInfinite */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {8,IR(0, 1),IR(24512, 17)/* DependencyLength */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {16,IR(0, 1),IR(24529, 14)/* MinIterations */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {32,IR(0, 1),IR(24543, 14)/* MaxIterations */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {64,IR(0, 1),IR(24557, 18)/* IterationMultiple */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {128,IR(0, 1),IR(24575, 10)/* PeelCount */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {256,IR(0, 1),IR(24585, 13)/* PartialCount */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {65536,IR(0, 1),IR(19245, 25)/* InitiationIntervalALTERA */,IR(101, 1),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {131072,IR(0, 1),IR(19294, 21)/* MaxConcurrencyALTERA */,IR(102, 1),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {262144,IR(0, 1),IR(24598, 22)/* DependencyArrayALTERA */,IR(140, 1),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {524288,IR(0, 1),IR(19335, 21)/* PipelineEnableALTERA */,IR(103, 1),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {1048576,IR(0, 1),IR(24641, 19)/* LoopCoalesceALTERA */,IR(141, 1),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {2097152,IR(0, 1),IR(24678, 22)/* MaxInterleavingALTERA */,IR(142, 1),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {4194304,IR(0, 1),IR(24721, 27)/* SpeculatedIterationsALTERA */,IR(143, 1),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {8388608,IR(0, 0),IR(24774, 15)/* NoFusionALTERA */,IR(144, 1),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {16777216,IR(0, 1),IR(24803, 16)/* LoopCountALTERA */,IR(145, 1),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {33554432,IR(0, 1),IR(24834, 27)/* MaxReinvocationDelayALTERA */,IR(146, 1),IR(190, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {0,IR(0, 0),IR(15540, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {1,IR(0, 0),IR(24887, 29)/* MatrixASignedComponentsINTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {2,IR(0, 0),IR(24916, 29)/* MatrixBSignedComponentsINTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {4,IR(0, 0),IR(24945, 21)/* MatrixCBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {8,IR(0, 0),IR(24966, 26)/* MatrixResultBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {16,IR(0, 0),IR(24992, 23)/* MatrixAPackedInt8INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {32,IR(0, 0),IR(25015, 23)/* MatrixBPackedInt8INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {64,IR(0, 0),IR(25038, 23)/* MatrixAPackedInt4INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {128,IR(0, 0),IR(25061, 23)/* MatrixBPackedInt4INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {256,IR(0, 0),IR(25084, 17)/* MatrixATF32INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {512,IR(0, 0),IR(25101, 17)/* MatrixBTF32INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {1024,IR(0, 0),IR(25118, 26)/* MatrixAPackedFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {2048,IR(0, 0),IR(25144, 26)/* MatrixBPackedFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {4096,IR(0, 0),IR(25170, 27)/* MatrixAPackedBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {8192,IR(0, 0),IR(25197, 27)/* MatrixBPackedBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {0,IR(0, 0),IR(15540, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {1,IR(0, 0),IR(16778, 9)/* Volatile */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {2,IR(0, 1),IR(25224, 8)/* Aligned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {4,IR(0, 0),IR(23715, 12)/* Nontemporal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {8,IR(4, 1),IR(25232, 21)/* MakePointerAvailable */,IR(147, 1),IR(189, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {16,IR(4, 1),IR(25277, 19)/* MakePointerVisible */,IR(148, 1),IR(189, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {32,IR(0, 0),IR(25318, 18)/* NonPrivatePointer */,IR(149, 1),IR(189, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {65536,IR(10, 1),IR(25357, 20)/* AliasScopeINTELMask */,IR(0, 0),IR(138, 1),IR(123, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {131072,IR(10, 1),IR(25377, 17)/* NoAliasINTELMask */,IR(0, 0),IR(138, 1),IR(123, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {0,IR(0, 0),IR(25394, 7)/* Simple */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {1,IR(0, 0),IR(25401, 8)/* GLSL450 */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {2,IR(0, 0),IR(25409, 7)/* OpenCL */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {3,IR(0, 0),IR(25416, 7)/* Vulkan */,IR(150, 1),IR(189, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {0,IR(0, 0),IR(25433, 8)/* Relaxed */,IR(151, 1),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {2,IR(0, 0),IR(25441, 8)/* Acquire */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {4,IR(0, 0),IR(25449, 8)/* Release */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {8,IR(0, 0),IR(25457, 15)/* AcquireRelease */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {16,IR(0, 0),IR(25472, 23)/* SequentiallyConsistent */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {64,IR(0, 0),IR(25495, 14)/* UniformMemory */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {128,IR(0, 0),IR(25509, 15)/* SubgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {256,IR(0, 0),IR(25524, 16)/* WorkgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {512,IR(0, 0),IR(25540, 21)/* CrossWorkgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {1024,IR(0, 0),IR(25561, 20)/* AtomicCounterMemory */,IR(0, 0),IR(82, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {2048,IR(0, 0),IR(25581, 12)/* ImageMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {4096,IR(0, 0),IR(25593, 13)/* OutputMemory */,IR(152, 1),IR(189, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {8192,IR(0, 0),IR(25622, 14)/* MakeAvailable */,IR(153, 1),IR(189, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {16384,IR(0, 0),IR(25653, 12)/* MakeVisible */,IR(154, 1),IR(189, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {32768,IR(0, 0),IR(16778, 9)/* Volatile */,IR(0, 0),IR(189, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {0,IR(0, 0),IR(25680, 10)/* AutoINTEL */,IR(0, 0),IR(177, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS
  {0,IR(0, 0),IR(25690, 5)/* WRAP */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {1,IR(0, 0),IR(25695, 4)/* SAT */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {2,IR(0, 0),IR(25699, 9)/* SAT_ZERO */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {3,IR(0, 0),IR(25708, 8)/* SAT_SYM */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {0,IR(0, 0),IR(25716, 25)/* PackedVectorFormat4x8Bit */,IR(155, 1),IR(1, 0),IR(140, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {0,IR(0, 0),IR(25769, 4)/* TRN */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {1,IR(0, 0),IR(25773, 9)/* TRN_ZERO */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {2,IR(0, 0),IR(25782, 4)/* RND */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {3,IR(0, 0),IR(25786, 9)/* RND_ZERO */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {4,IR(0, 0),IR(25795, 8)/* RND_INF */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {5,IR(0, 0),IR(25803, 12)/* RND_MIN_INF */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {6,IR(0, 0),IR(25815, 9)/* RND_CONV */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {7,IR(0, 0),IR(25824, 13)/* RND_CONV_ODD */,IR(0, 0),IR(191, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {0,IR(0, 0),IR(15540, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {1,IR(0, 0),IR(25837, 25)/* RobustnessPerComponentNV */,IR(0, 0),IR(192, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {2,IR(0, 0),IR(25862, 23)/* RobustnessPerElementNV */,IR(0, 0),IR(192, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {0,IR(0, 0),IR(16292, 8)/* NoneKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {1,IR(0, 0),IR(25885, 10)/* OpaqueKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {2,IR(0, 0),IR(25895, 12)/* NoOpaqueKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {4,IR(0, 0),IR(25907, 23)/* TerminateOnFirstHitKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {8,IR(0, 0),IR(25930, 24)/* SkipClosestHitShaderKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {16,IR(0, 0),IR(25954, 27)/* CullBackFacingTrianglesKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {32,IR(0, 0),IR(25981, 28)/* CullFrontFacingTrianglesKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {64,IR(0, 0),IR(26009, 14)/* CullOpaqueKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {128,IR(0, 0),IR(26023, 16)/* CullNoOpaqueKHR */,IR(0, 0),IR(84, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {256,IR(0, 0),IR(26039, 17)/* SkipTrianglesKHR */,IR(156, 1),IR(193, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {512,IR(0, 0),IR(26080, 13)/* SkipAABBsKHR */,IR(0, 0),IR(193, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {1024,IR(0, 0),IR(26093, 30)/* ForceOpacityMicromap2StateEXT */,IR(0, 0),IR(194, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {0,IR(0, 0),IR(26123, 41)/* RayQueryCandidateIntersectionTriangleKHR */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {1,IR(0, 0),IR(26164, 37)/* RayQueryCandidateIntersectionAABBKHR */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {0,IR(0, 0),IR(26201, 37)/* RayQueryCommittedIntersectionNoneKHR */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {1,IR(0, 0),IR(26238, 41)/* RayQueryCommittedIntersectionTriangleKHR */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {2,IR(0, 0),IR(26279, 42)/* RayQueryCommittedIntersectionGeneratedKHR */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {0,IR(0, 0),IR(26321, 33)/* RayQueryCandidateIntersectionKHR */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {1,IR(0, 0),IR(26354, 33)/* RayQueryCommittedIntersectionKHR */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {0,IR(0, 0),IR(15540, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {1,IR(0, 0),IR(26387, 12)/* ClampToEdge */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {2,IR(0, 0),IR(26399, 6)/* Clamp */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {3,IR(0, 0),IR(26405, 7)/* Repeat */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {4,IR(0, 0),IR(26412, 15)/* RepeatMirrored */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {0,IR(0, 0),IR(26427, 8)/* Nearest */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {1,IR(0, 0),IR(26435, 7)/* Linear */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {0,IR(0, 0),IR(26442, 8)/* Unknown */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {1,IR(0, 0),IR(26450, 8)/* Rgba32f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {2,IR(0, 0),IR(26458, 8)/* Rgba16f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {3,IR(0, 0),IR(26466, 5)/* R32f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {4,IR(0, 0),IR(26471, 6)/* Rgba8 */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {5,IR(0, 0),IR(26477, 11)/* Rgba8Snorm */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {6,IR(0, 0),IR(26488, 6)/* Rg32f */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {7,IR(0, 0),IR(26494, 6)/* Rg16f */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {8,IR(0, 0),IR(26500, 13)/* R11fG11fB10f */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {9,IR(0, 0),IR(26513, 5)/* R16f */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {10,IR(0, 0),IR(26518, 7)/* Rgba16 */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {11,IR(0, 0),IR(26525, 8)/* Rgb10A2 */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {12,IR(0, 0),IR(26533, 5)/* Rg16 */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {13,IR(0, 0),IR(26538, 4)/* Rg8 */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {14,IR(0, 0),IR(26542, 4)/* R16 */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {15,IR(0, 0),IR(26546, 3)/* R8 */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {16,IR(0, 0),IR(26549, 12)/* Rgba16Snorm */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {17,IR(0, 0),IR(26561, 10)/* Rg16Snorm */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {18,IR(0, 0),IR(26571, 9)/* Rg8Snorm */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {19,IR(0, 0),IR(26580, 9)/* R16Snorm */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {20,IR(0, 0),IR(26589, 8)/* R8Snorm */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {21,IR(0, 0),IR(26597, 8)/* Rgba32i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {22,IR(0, 0),IR(26605, 8)/* Rgba16i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {23,IR(0, 0),IR(26613, 7)/* Rgba8i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {24,IR(0, 0),IR(26620, 5)/* R32i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {25,IR(0, 0),IR(26625, 6)/* Rg32i */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {26,IR(0, 0),IR(26631, 6)/* Rg16i */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {27,IR(0, 0),IR(26637, 5)/* Rg8i */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {28,IR(0, 0),IR(26642, 5)/* R16i */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {29,IR(0, 0),IR(26647, 4)/* R8i */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {30,IR(0, 0),IR(26651, 9)/* Rgba32ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {31,IR(0, 0),IR(26660, 9)/* Rgba16ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {32,IR(0, 0),IR(26669, 8)/* Rgba8ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {33,IR(0, 0),IR(26677, 6)/* R32ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {34,IR(0, 0),IR(26683, 10)/* Rgb10a2ui */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {35,IR(0, 0),IR(26693, 7)/* Rg32ui */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {36,IR(0, 0),IR(26700, 7)/* Rg16ui */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {37,IR(0, 0),IR(26707, 6)/* Rg8ui */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {38,IR(0, 0),IR(26713, 6)/* R16ui */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {39,IR(0, 0),IR(26719, 5)/* R8ui */,IR(0, 0),IR(196, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {40,IR(0, 0),IR(26724, 6)/* R64ui */,IR(0, 0),IR(197, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {41,IR(0, 0),IR(26730, 5)/* R64i */,IR(0, 0),IR(197, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {0,IR(0, 0),IR(26735, 12)/* CrossDevice */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {1,IR(0, 0),IR(26747, 7)/* Device */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {2,IR(0, 0),IR(26754, 10)/* Workgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {3,IR(0, 0),IR(26764, 9)/* Subgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {4,IR(0, 0),IR(26773, 11)/* Invocation */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {5,IR(0, 0),IR(26784, 12)/* QueueFamily */,IR(157, 1),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {6,IR(0, 0),IR(26811, 14)/* ShaderCallKHR */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {0,IR(0, 0),IR(15540, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {1,IR(0, 0),IR(26825, 8)/* Flatten */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {2,IR(0, 0),IR(26833, 12)/* DontFlatten */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {1,IR(0, 0),IR(26845, 29)/* IdentifierPossibleDuplicates */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS
  {0,IR(0, 0),IR(15409, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(15421, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(15429, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {3,IR(0, 0),IR(15437, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(15443, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(15450, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(15461, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(15470, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(15483, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(15489, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(15499, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(15505, 15)/* ImportedModule */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {1,IR(0, 0),IR(15520, 20)/* ImportedDeclaration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {0,IR(0, 0),IR(15540, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(15545, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(15561, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(15575, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(15588, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(15600, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(15617, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(15629, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(15644, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(15657, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(15672, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(15690, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(15707, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(15728, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(15748, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(15768, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {16384,IR(0, 0),IR(15784, 16)/* FlagIsEnumClass */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {32768,IR(0, 0),IR(15800, 20)/* FlagTypePassByValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {65536,IR(0, 0),IR(15820, 24)/* FlagTypePassByReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {131072,IR(0, 0),IR(26874, 26)/* FlagUnknownPhysicalLayout */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(15844, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {1,IR(0, 0),IR(15850, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {2,IR(0, 0),IR(15855, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {3,IR(10, 1),IR(15894, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {4,IR(36, 2),IR(15905, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {5,IR(0, 0),IR(15914, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {6,IR(0, 0),IR(15919, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {7,IR(0, 0),IR(15926, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {8,IR(10, 1),IR(15937, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {9,IR(36, 2),IR(15944, 9)/* Fragment */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {0,IR(0, 0),IR(15953, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(15963, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(15976, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {3,IR(0, 0),IR(15989, 11)/* AtomicType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(26442, 8)/* Unknown */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {1,IR(0, 0),IR(26900, 5)/* ESSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {2,IR(0, 0),IR(26905, 5)/* GLSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {3,IR(0, 0),IR(26910, 9)/* OpenCL_C */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {4,IR(0, 0),IR(26919, 11)/* OpenCL_CPP */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {5,IR(0, 0),IR(26930, 5)/* HLSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {6,IR(0, 0),IR(26935, 15)/* CPP_for_OpenCL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {7,IR(0, 0),IR(26950, 5)/* SYCL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {8,IR(0, 0),IR(26955, 7)/* HERO_C */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {9,IR(0, 0),IR(26962, 5)/* NZSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {10,IR(0, 0),IR(26967, 5)/* WGSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {11,IR(0, 0),IR(26972, 6)/* Slang */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {12,IR(0, 0),IR(26978, 4)/* Zig */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {13,IR(0, 0),IR(26982, 5)/* Rust */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {0,IR(0, 0),IR(26987, 16)/* UniformConstant */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {1,IR(0, 0),IR(27003, 6)/* Input */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {2,IR(0, 0),IR(16829, 8)/* Uniform */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {3,IR(0, 0),IR(27009, 7)/* Output */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4,IR(0, 0),IR(26754, 10)/* Workgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5,IR(0, 0),IR(27016, 15)/* CrossWorkgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {6,IR(0, 0),IR(27031, 8)/* Private */,IR(0, 0),IR(198, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {7,IR(0, 0),IR(27039, 9)/* Function */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {8,IR(0, 0),IR(27048, 8)/* Generic */,IR(0, 0),IR(200, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {9,IR(0, 0),IR(27056, 13)/* PushConstant */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {10,IR(0, 0),IR(27069, 14)/* AtomicCounter */,IR(0, 0),IR(82, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {11,IR(0, 0),IR(27083, 6)/* Image */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {12,IR(0, 0),IR(27089, 14)/* StorageBuffer */,IR(0, 0),IR(3, 1),IR(188, 2),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4172,IR(0, 0),IR(27103, 13)/* TileImageEXT */,IR(0, 0),IR(149, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4491,IR(0, 0),IR(27116, 19)/* TileAttachmentQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5068,IR(0, 0),IR(27135, 16)/* NodePayloadAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5328,IR(0, 0),IR(27151, 16)/* CallableDataKHR */,IR(158, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5329,IR(0, 0),IR(27182, 24)/* IncomingCallableDataKHR */,IR(159, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5338,IR(0, 0),IR(27229, 14)/* RayPayloadKHR */,IR(160, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5339,IR(0, 0),IR(27256, 16)/* HitAttributeKHR */,IR(161, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5342,IR(0, 0),IR(27287, 22)/* IncomingRayPayloadKHR */,IR(162, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5343,IR(0, 0),IR(27330, 22)/* ShaderRecordBufferKHR */,IR(163, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5349,IR(0, 0),IR(27373, 22)/* PhysicalStorageBuffer */,IR(164, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5385,IR(0, 0),IR(27420, 21)/* HitObjectAttributeNV */,IR(0, 0),IR(127, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5402,IR(0, 0),IR(27441, 24)/* TaskPayloadWorkgroupEXT */,IR(0, 0),IR(53, 1),IR(23, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5411,IR(0, 0),IR(27465, 22)/* HitObjectAttributeEXT */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5605,IR(0, 0),IR(27487, 17)/* CodeSectionINTEL */,IR(0, 0),IR(201, 1),IR(97, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5936,IR(0, 0),IR(27504, 17)/* DeviceOnlyALTERA */,IR(165, 1),IR(202, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5937,IR(0, 0),IR(27537, 15)/* HostOnlyALTERA */,IR(166, 1),IR(202, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {0,IR(0, 0),IR(24392, 14)/* UncachedINTEL */,IR(0, 0),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {1,IR(0, 0),IR(27566, 18)/* WriteThroughINTEL */,IR(0, 0),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {2,IR(0, 0),IR(27584, 15)/* WriteBackINTEL */,IR(0, 0),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {3,IR(0, 0),IR(24418, 15)/* StreamingINTEL */,IR(0, 0),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {0,IR(0, 0),IR(15540, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {1,IR(10, 1),IR(27599, 11)/* TensorView */,IR(0, 0),IR(203, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {2,IR(10, 1),IR(27610, 11)/* DecodeFunc */,IR(0, 0),IR(204, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {0,IR(0, 0),IR(27621, 10)/* Undefined */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {1,IR(0, 0),IR(16787, 9)/* Constant */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {2,IR(0, 0),IR(26387, 12)/* ClampToEdge */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {3,IR(0, 0),IR(26405, 7)/* Repeat */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {4,IR(0, 0),IR(26412, 15)/* RepeatMirrored */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {0,IR(0, 0),IR(27631, 8)/* NoneARM */,IR(0, 0),IR(205, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {1,IR(0, 0),IR(27639, 15)/* NontemporalARM */,IR(0, 0),IR(205, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {2,IR(10, 1),IR(27654, 20)/* OutOfBoundsValueARM */,IR(0, 0),IR(205, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {4,IR(10, 1),IR(27674, 24)/* MakeElementAvailableARM */,IR(0, 0),IR(205, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {8,IR(10, 1),IR(27698, 22)/* MakeElementVisibleARM */,IR(0, 0),IR(205, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {16,IR(0, 0),IR(27720, 21)/* NonPrivateElementARM */,IR(0, 0),IR(205, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
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
    case SPV_OPERAND_TYPE_CAPABILITY: return IR(133, 277);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(410, 8);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(418, 3);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(421, 2);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS: return IR(423, 19);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION: return IR(442, 10);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(452, 4);
    case SPV_OPERAND_TYPE_COMPONENT_TYPE: return IR(456, 15);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT: return IR(471, 4);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS: return IR(475, 6);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE: return IR(481, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE: return IR(484, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT: return IR(487, 4);
    case SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(491, 8);
    case SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE: return IR(499, 3);
    case SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS: return IR(502, 16);
    case SPV_OPERAND_TYPE_DEBUG_OPERATION: return IR(518, 9);
    case SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER: return IR(527, 3);
    case SPV_OPERAND_TYPE_DECORATION: return IR(530, 145);
    case SPV_OPERAND_TYPE_DIMENSIONALITY: return IR(675, 8);
    case SPV_OPERAND_TYPE_EXECUTION_MODE: return IR(683, 97);
    case SPV_OPERAND_TYPE_EXECUTION_MODEL: return IR(780, 17);
    case SPV_OPERAND_TYPE_FPDENORM_MODE: return IR(797, 2);
    case SPV_OPERAND_TYPE_FPENCODING: return IR(799, 3);
    case SPV_OPERAND_TYPE_FPOPERATION_MODE: return IR(802, 2);
    case SPV_OPERAND_TYPE_FP_FAST_MATH_MODE: return IR(804, 9);
    case SPV_OPERAND_TYPE_FP_ROUNDING_MODE: return IR(813, 4);
    case SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE: return IR(817, 4);
    case SPV_OPERAND_TYPE_FUNCTION_CONTROL: return IR(821, 6);
    case SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE: return IR(827, 9);
    case SPV_OPERAND_TYPE_GROUP_OPERATION: return IR(836, 7);
    case SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER: return IR(843, 4);
    case SPV_OPERAND_TYPE_IMAGE: return IR(847, 17);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE: return IR(864, 26);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER: return IR(890, 20);
    case SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER: return IR(910, 2);
    case SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS: return IR(912, 3);
    case SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO: return IR(915, 2);
    case SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS: return IR(917, 2);
    case SPV_OPERAND_TYPE_LINKAGE_TYPE: return IR(919, 3);
    case SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL: return IR(922, 5);
    case SPV_OPERAND_TYPE_LOOP_CONTROL: return IR(927, 20);
    case SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(947, 15);
    case SPV_OPERAND_TYPE_MEMORY_ACCESS: return IR(962, 9);
    case SPV_OPERAND_TYPE_MEMORY_MODEL: return IR(971, 4);
    case SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID: return IR(975, 15);
    case SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS: return IR(990, 1);
    case SPV_OPERAND_TYPE_OVERFLOW_MODES: return IR(991, 4);
    case SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT: return IR(995, 1);
    case SPV_OPERAND_TYPE_QUANTIZATION_MODES: return IR(996, 8);
    case SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS: return IR(1004, 3);
    case SPV_OPERAND_TYPE_RAY_FLAGS: return IR(1007, 12);
    case SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE: return IR(1019, 2);
    case SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE: return IR(1021, 3);
    case SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION: return IR(1024, 2);
    case SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE: return IR(1026, 5);
    case SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE: return IR(1031, 2);
    case SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT: return IR(1033, 42);
    case SPV_OPERAND_TYPE_SCOPE_ID: return IR(1075, 7);
    case SPV_OPERAND_TYPE_SELECTION_CONTROL: return IR(1082, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS: return IR(1085, 1);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(1086, 8);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(1094, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(1097, 2);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS: return IR(1099, 20);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION: return IR(1119, 10);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(1129, 4);
    case SPV_OPERAND_TYPE_SOURCE_LANGUAGE: return IR(1133, 14);
    case SPV_OPERAND_TYPE_STORAGE_CLASS: return IR(1147, 29);
    case SPV_OPERAND_TYPE_STORE_CACHE_CONTROL: return IR(1176, 4);
    case SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS: return IR(1180, 3);
    case SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE: return IR(1183, 5);
    case SPV_OPERAND_TYPE_TENSOR_OPERANDS: return IR(1188, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_IMAGE: return IR(847, 17);
    case SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS: return IR(962, 9);
    case SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT: return IR(995, 1);
    case SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS: return IR(475, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(947, 15);
    case SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS: return IR(1004, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_FPENCODING: return IR(799, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS: return IR(1188, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_CAPABILITY: return IR(133, 277);
    default: break;
  }
  return IR(0,0);
}

// Operand names and index into kOperandsByValue, ordered by (operand kind, name)
// The fields in order are:
//   name, either the primary name or an alias, indexing into kStrings
//   index into the kOperandsByValue array
static const std::array<NameIndex, 1365> kOperandNames{{
  {IR(5348, 9), 0}, // 0 ReadOnly in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(5374, 10), 2}, // 1 ReadWrite in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(5364, 10), 1}, // 2 WriteOnly in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(5384, 8), 3}, // 3 Logical in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5392, 11), 4}, // 4 Physical32 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5413, 11), 5}, // 5 Physical64 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5424, 24), 6}, // 6 PhysicalStorageBuffer64 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5448, 27), 6}, // 7 PhysicalStorageBuffer64EXT in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(7358, 13), 92}, // 8 BaryCoordKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7371, 12), 92}, // 9 BaryCoordNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6753, 20), 68}, // 10 BaryCoordNoPerspAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6773, 28), 69}, // 11 BaryCoordNoPerspCentroidAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7406, 20), 93}, // 12 BaryCoordNoPerspKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7426, 19), 93}, // 13 BaryCoordNoPerspNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6801, 26), 70}, // 14 BaryCoordNoPerspSampleAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6898, 22), 74}, // 15 BaryCoordPullModelAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6827, 19), 71}, // 16 BaryCoordSmoothAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6846, 27), 72}, // 17 BaryCoordSmoothCentroidAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6873, 25), 73}, // 18 BaryCoordSmoothSampleAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6557, 13), 59}, // 19 BaseInstance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6531, 11), 58}, // 20 BaseVertex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5532, 13), 9}, // 21 ClipDistance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7265, 22), 87}, // 22 ClipDistancePerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8564, 12), 131}, // 23 ClusterIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6295, 13), 49}, // 24 CoreCountARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6269, 10), 48}, // 25 CoreIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6308, 13), 50}, // 26 CoreMaxIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5545, 13), 10}, // 27 CullDistance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7287, 22), 88}, // 28 CullDistancePerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8617, 12), 132}, // 29 CullMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7613, 17), 99}, // 30 CullPrimitiveEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8017, 17), 113}, // 31 CurrentRayTimeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6627, 12), 62}, // 32 DeviceIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6570, 10), 60}, // 33 DrawIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6059, 22), 37}, // 34 EnqueuedWorkgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5829, 10), 21}, // 35 FragCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5915, 10), 27}, // 36 FragDepth in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7491, 23), 95}, // 37 FragInvocationCountEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7445, 12), 94}, // 38 FragSizeEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6920, 18), 75}, // 39 FragStencilRefEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7457, 15), 94}, // 40 FragmentSizeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5850, 12), 23}, // 41 FrontFacing in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7177, 16), 83}, // 42 FullyCoveredEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6000, 19), 33}, // 43 GlobalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6094, 15), 39}, // 44 GlobalLinearId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6081, 13), 38}, // 45 GlobalOffset in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6048, 11), 36}, // 46 GlobalSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5925, 17), 28}, // 47 HelperInvocation in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8319, 11), 120}, // 48 HitIsLSSNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8277, 14), 119}, // 49 HitIsSphereNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8499, 33), 128}, // 50 HitKindBackFacingMicroTriangleNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8465, 34), 127}, // 51 HitKindFrontFacingMicroTriangleNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7996, 11), 112}, // 52 HitKindKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8007, 10), 112}, // 53 HitKindNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8447, 18), 126}, // 54 HitLSSPositionsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8550, 14), 130}, // 55 HitLSSRadiiNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8181, 37), 116}, // 56 HitMicroTriangleVertexBarycentricsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8114, 34), 115}, // 57 HitMicroTriangleVertexPositionsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8369, 20), 121}, // 58 HitSpherePositionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8532, 18), 129}, // 59 HitSphereRadiusNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7989, 7), 111}, // 60 HitTNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8057, 30), 114}, // 61 HitTriangleVertexPositionsKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8218, 20), 117}, // 62 IncomingRayFlagsKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8238, 19), 117}, // 63 IncomingRayFlagsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7878, 23), 108}, // 64 InstanceCustomIndexKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7901, 22), 108}, // 65 InstanceCustomIndexNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5567, 11), 12}, // 66 InstanceId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6255, 14), 47}, // 67 InstanceIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5668, 13), 14}, // 68 InvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7514, 22), 95}, // 69 InvocationsPerPixelNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7630, 12), 100}, // 70 LaunchIdKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7642, 11), 100}, // 71 LaunchIdNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7653, 14), 101}, // 72 LaunchSizeKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7667, 13), 101}, // 73 LaunchSizeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5681, 6), 15}, // 74 Layer in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7309, 15), 89}, // 75 LayerPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5982, 18), 32}, // 76 LocalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6019, 21), 34}, // 77 LocalInvocationIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7324, 16), 90}, // 78 MeshViewCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7340, 18), 91}, // 79 MeshViewIndicesNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6185, 21), 43}, // 80 NumEnqueuedSubgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6172, 13), 42}, // 81 NumSubgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5942, 14), 29}, // 82 NumWorkgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7793, 22), 105}, // 83 ObjectRayDirectionKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7815, 21), 105}, // 84 ObjectRayDirectionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7756, 19), 104}, // 85 ObjectRayOriginKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7775, 18), 104}, // 86 ObjectRayOriginNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7923, 17), 109}, // 87 ObjectToWorldKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7940, 16), 109}, // 88 ObjectToWorldNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5815, 14), 20}, // 89 PatchVertices in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5839, 11), 22}, // 90 PointCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5522, 10), 8}, // 91 PointSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5506, 9), 7}, // 92 Position in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7117, 18), 81}, // 93 PositionPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7229, 17), 85}, // 94 PrimitiveCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5578, 12), 13}, // 95 PrimitiveId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7246, 19), 86}, // 96 PrimitiveIndicesNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7561, 24), 97}, // 97 PrimitiveLineIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7536, 25), 96}, // 98 PrimitivePointIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6580, 24), 61}, // 99 PrimitiveShadingRateKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7585, 28), 98}, // 100 PrimitiveTriangleIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8257, 20), 118}, // 101 RayGeometryIndexKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7857, 11), 107}, // 102 RayTmaxKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7868, 10), 107}, // 103 RayTmaxNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7836, 11), 106}, // 104 RayTminKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7847, 10), 106}, // 105 RayTminNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6955, 29), 76}, // 106 RemainingRecursionLevelsAMDX in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8421, 10), 123}, // 107 SMCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8440, 7), 125}, // 108 SMIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5862, 9), 24}, // 109 SampleId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5904, 11), 26}, // 110 SampleMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5889, 15), 25}, // 111 SamplePosition in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7054, 20), 79}, // 112 SecondaryPositionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7093, 24), 80}, // 113 SecondaryViewportMaskNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7002, 16), 77}, // 114 ShaderIndexAMDX in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6671, 15), 64}, // 115 ShadingRateKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6344, 15), 53}, // 116 SubgroupEqMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6359, 18), 53}, // 117 SubgroupEqMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6399, 15), 54}, // 118 SubgroupGeMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6414, 18), 54}, // 119 SubgroupGeMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6432, 15), 55}, // 120 SubgroupGtMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6447, 18), 55}, // 121 SubgroupGtMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6206, 11), 44}, // 122 SubgroupId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6465, 15), 56}, // 123 SubgroupLeMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6480, 18), 56}, // 124 SubgroupLeMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6217, 26), 45}, // 125 SubgroupLocalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6498, 15), 57}, // 126 SubgroupLtMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6513, 18), 57}, // 127 SubgroupLtMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6156, 16), 41}, // 128 SubgroupMaxSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6109, 13), 40}, // 129 SubgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7217, 12), 84}, // 130 TaskCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5805, 10), 19}, // 131 TessCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5790, 15), 18}, // 132 TessLevelInner in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5775, 15), 17}, // 133 TessLevelOuter in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6735, 18), 67}, // 134 TileApronSizeQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6717, 18), 66}, // 135 TileDimensionQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6686, 15), 65}, // 136 TileOffsetQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5558, 9), 11}, // 137 VertexId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6243, 12), 46}, // 138 VertexIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6651, 10), 63}, // 139 ViewIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5727, 14), 16}, // 140 ViewportIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7018, 15), 78}, // 141 ViewportMaskNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7155, 22), 82}, // 142 ViewportMaskPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6321, 10), 51}, // 143 WarpIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8431, 9), 124}, // 144 WarpIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6331, 13), 52}, // 145 WarpMaxIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8389, 13), 122}, // 146 WarpsPerSMNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6040, 8), 35}, // 147 WorkDim in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5970, 12), 31}, // 148 WorkgroupId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5956, 14), 30}, // 149 WorkgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7715, 21), 103}, // 150 WorldRayDirectionKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7736, 20), 103}, // 151 WorldRayDirectionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7680, 18), 102}, // 152 WorldRayOriginKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7698, 17), 102}, // 153 WorldRayOriginNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7956, 17), 110}, // 154 WorldToObjectKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7973, 16), 110}, // 155 WorldToObjectNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5403, 10), 137}, // 156 Addresses in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13960, 35), 361}, // 157 ArbitraryPrecisionFixedPointALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13995, 34), 361}, // 158 ArbitraryPrecisionFixedPointINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13432, 38), 349}, // 159 ArbitraryPrecisionFloatingPointALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13470, 37), 349}, // 160 ArbitraryPrecisionFloatingPointINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13367, 33), 348}, // 161 ArbitraryPrecisionIntegersALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13400, 32), 348}, // 162 ArbitraryPrecisionIntegersINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14654, 19), 386}, // 163 ArithmeticFenceEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13005, 9), 334}, // 164 AsmINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14571, 20), 382}, // 165 AtomicFloat16AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13060, 23), 337}, // 166 AtomicFloat16MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12510, 22), 311}, // 167 AtomicFloat16VectorNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14487, 20), 378}, // 168 AtomicFloat32AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13014, 23), 335}, // 169 AtomicFloat32MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14507, 20), 379}, // 170 AtomicFloat64AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13037, 23), 336}, // 171 AtomicFloat64MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8797, 14), 153}, // 172 AtomicStorage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10184, 17), 229}, // 173 AtomicStorageOps in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14612, 24), 384}, // 174 BFloat16ConversionINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10806, 29), 263}, // 175 BFloat16CooperativeMatrixKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10784, 22), 262}, // 176 BFloat16DotProductKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10768, 16), 261}, // 177 BFloat16TypeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15389, 20), 409}, // 178 BindlessImagesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12447, 18), 308}, // 179 BindlessTextureNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14424, 16), 374}, // 180 BitInstructions in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14162, 20), 365}, // 181 BlockingPipesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14182, 19), 365}, // 182 BlockingPipesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15350, 19), 407}, // 183 CacheControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5532, 13), 163}, // 184 ClipDistance in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12078, 32), 296}, // 185 ComputeDerivativeGroupLinearKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12110, 31), 296}, // 186 ComputeDerivativeGroupLinearNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10958, 31), 275}, // 187 ComputeDerivativeGroupQuadsKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10989, 30), 275}, // 188 ComputeDerivativeGroupQuadsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12710, 30), 321}, // 189 CooperativeMatrixBlockLoadsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10553, 32), 248}, // 190 CooperativeMatrixConversionQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12603, 31), 318}, // 191 CooperativeMatrixConversionsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9832, 21), 372}, // 192 CooperativeMatrixKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9767, 28), 211}, // 193 CooperativeMatrixLayoutsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12166, 20), 298}, // 194 CooperativeMatrixNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12634, 40), 319}, // 195 CooperativeMatrixPerElementOperationsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12573, 30), 317}, // 196 CooperativeMatrixReductionsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12674, 36), 320}, // 197 CooperativeMatrixTensorAddressingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12490, 20), 310}, // 198 CooperativeVectorNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12740, 28), 322}, // 199 CooperativeVectorTrainingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6279, 16), 203}, // 200 CoreBuiltinsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5545, 13), 164}, // 201 CullDistance in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14591, 21), 383}, // 202 DebugInfoModuleINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12289, 25), 303}, // 203 DemoteToHelperInvocation in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12314, 28), 303}, // 204 DemoteToHelperInvocationEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10323, 18), 235}, // 205 DenormFlushToZero in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10308, 15), 234}, // 206 DenormPreserve in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9244, 18), 182}, // 207 DerivativeControl in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8768, 14), 151}, // 208 DeviceEnqueue in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6639, 12), 225}, // 209 DeviceGroup in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12342, 23), 304}, // 210 DisplacementMicromapNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14375, 11), 370}, // 211 DotProduct in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14269, 22), 368}, // 212 DotProductInput4x8Bit in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14291, 25), 368}, // 213 DotProductInput4x8BitKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14316, 28), 369}, // 214 DotProductInput4x8BitPacked in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14344, 31), 369}, // 215 DotProductInput4x8BitPackedKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14228, 19), 367}, // 216 DotProductInputAll in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14247, 22), 367}, // 217 DotProductInputAllKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14386, 14), 370}, // 218 DotProductKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6542, 15), 216}, // 219 DrawParameters in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13117, 16), 340}, // 220 ExpectAssumeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14480, 7), 377}, // 221 FMAKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13347, 20), 347}, // 222 FPFastMathModeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14862, 29), 392}, // 223 FPGAArgumentInterfacesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14891, 28), 392}, // 224 FPGAArgumentInterfacesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13911, 25), 360}, // 225 FPGABufferLocationALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13936, 24), 360}, // 226 FPGABufferLocationINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13679, 28), 355}, // 227 FPGAClusterAttributesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13707, 27), 355}, // 228 FPGAClusterAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14673, 30), 387}, // 229 FPGAClusterAttributesV2ALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14703, 29), 387}, // 230 FPGAClusterAttributesV2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13763, 21), 357}, // 231 FPGADSPControlALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13784, 20), 357}, // 232 FPGADSPControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13830, 41), 359}, // 233 FPGAInvocationPipeliningAttributesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13871, 40), 359}, // 234 FPGAInvocationPipeliningAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13604, 26), 353}, // 235 FPGAKernelAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14732, 28), 388}, // 236 FPGAKernelAttributesv2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14813, 25), 391}, // 237 FPGALatencyControlALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14838, 24), 391}, // 238 FPGALatencyControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13537, 23), 351}, // 239 FPGALoopControlsALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13560, 22), 351}, // 240 FPGALoopControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13630, 25), 354}, // 241 FPGAMemoryAccessesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13655, 24), 354}, // 242 FPGAMemoryAccessesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13294, 27), 346}, // 243 FPGAMemoryAttributesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13321, 26), 346}, // 244 FPGAMemoryAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14201, 14), 366}, // 245 FPGARegALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14215, 13), 366}, // 246 FPGARegINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14797, 16), 390}, // 247 FPMaxErrorINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8682, 8), 142}, // 248 Float16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8668, 14), 141}, // 249 Float16Buffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10608, 16), 250}, // 250 Float16ImageAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8690, 8), 143}, // 251 Float64 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9805, 27), 213}, // 252 Float8CooperativeMatrixEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9795, 10), 212}, // 253 Float8EXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14465, 15), 376}, // 254 FloatControls2 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12913, 23), 330}, // 255 FloatingPointModeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7383, 23), 274}, // 256 FragmentBarycentricKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10936, 22), 274}, // 257 FragmentBarycentricNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7472, 19), 276}, // 258 FragmentDensityEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7193, 24), 270}, // 259 FragmentFullyCoveredEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10646, 16), 252}, // 260 FragmentMaskAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12257, 32), 302}, // 261 FragmentShaderPixelInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12186, 33), 299}, // 262 FragmentShaderSampleInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12219, 38), 300}, // 263 FragmentShaderShadingRateInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6604, 23), 214}, // 264 FragmentShadingRateKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13268, 26), 345}, // 265 FunctionFloatControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12959, 22), 332}, // 266 FunctionPointersINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15250, 22), 403}, // 267 FunctionVariantsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9089, 15), 169}, // 268 GenericPointer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5590, 9), 135}, // 269 Geometry in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8839, 18), 156}, // 270 GeometryPointSize in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10864, 28), 265}, // 271 GeometryShaderPassthroughNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9302, 16), 185}, // 272 GeometryStreams in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14949, 36), 394}, // 273 GlobalVariableFPGADecorationsALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14985, 35), 394}, // 274 GlobalVariableFPGADecorationsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14919, 30), 393}, // 275 GlobalVariableHostAccessINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9758, 9), 210}, // 276 GraphARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6122, 16), 192}, // 277 GroupNonUniform in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9441, 26), 194}, // 278 GroupNonUniformArithmetic in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6377, 22), 195}, // 279 GroupNonUniformBallot in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9521, 25), 198}, // 280 GroupNonUniformClustered in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11033, 29), 277}, // 281 GroupNonUniformPartitionedNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9546, 20), 199}, // 282 GroupNonUniformQuad in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14440, 25), 375}, // 283 GroupNonUniformRotateKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9467, 23), 196}, // 284 GroupNonUniformShuffle in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9490, 31), 197}, // 285 GroupNonUniformShuffleRelative in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9421, 20), 193}, // 286 GroupNonUniformVote in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15272, 26), 404}, // 287 GroupUniformArithmeticKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8761, 7), 150}, // 288 Groups in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14135, 14), 364}, // 289 IOPipesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14149, 13), 364}, // 290 IOPipesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9158, 8), 175}, // 291 Image1D in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8717, 11), 146}, // 292 ImageBasic in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9180, 12), 178}, // 293 ImageBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9035, 15), 165}, // 294 ImageCubeArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10919, 17), 272}, // 295 ImageFootprintNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10624, 22), 251}, // 296 ImageGatherBiasLodAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8857, 20), 157}, // 297 ImageGatherExtended in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9192, 13), 179}, // 298 ImageMSArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8743, 12), 148}, // 299 ImageMipmap in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9233, 11), 181}, // 300 ImageQuery in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8728, 15), 147}, // 301 ImageReadWrite in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10662, 21), 254}, // 302 ImageReadWriteLodAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9067, 10), 167}, // 303 ImageRect in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12981, 24), 333}, // 304 IndirectReferencesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9109, 16), 171}, // 305 InputAttachment in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11148, 36), 280}, // 306 InputAttachmentArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11184, 39), 280}, // 307 InputAttachmentArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11689, 39), 287}, // 308 InputAttachmentArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11728, 42), 287}, // 309 InputAttachmentArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8811, 6), 154}, // 310 Int16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10741, 27), 260}, // 311 Int4CooperativeMatrixINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10727, 14), 259}, // 312 Int4TypeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8698, 6), 144}, // 313 Int64 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8704, 13), 145}, // 314 Int64Atomics in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10683, 14), 255}, // 315 Int64ImageEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9104, 5), 170}, // 316 Int8 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12936, 23), 331}, // 317 IntegerFunctions2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9262, 22), 183}, // 318 InterpolationFunction in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5357, 7), 139}, // 319 Kernel in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13582, 22), 352}, // 320 KernelAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8651, 8), 138}, // 321 Linkage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8782, 15), 152}, // 322 LiteralSampler in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14527, 20), 380}, // 323 LongCompositesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13734, 15), 356}, // 324 LoopFuseALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13749, 14), 356}, // 325 LoopFuseINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15325, 25), 406}, // 326 MaskedGatherScatterINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8644, 7), 133}, // 327 Matrix in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13804, 26), 358}, // 328 MemoryAccessAliasingINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5653, 15), 273}, // 329 MeshShadingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5639, 14), 271}, // 330 MeshShadingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9141, 7), 173}, // 331 MinLod in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6661, 10), 226}, // 332 MultiView in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5741, 14), 188}, // 333 MultiViewport in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9396, 13), 190}, // 334 NamedBarrier in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14547, 11), 381}, // 335 OptNoneEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14558, 13), 381}, // 336 OptNoneINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7135, 20), 269}, // 337 PerViewAttributesNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5475, 31), 295}, // 338 PhysicalStorageBufferAddresses in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12044, 34), 295}, // 339 PhysicalStorageBufferAddressesEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9409, 12), 191}, // 340 PipeStorage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8755, 6), 149}, // 341 Pipes in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10712, 15), 258}, // 342 QuadControlKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12532, 18), 313}, // 343 RawAccessChainsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8629, 15), 371}, // 344 RayCullMaskKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10421, 12), 240}, // 345 RayQueryKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12465, 25), 309}, // 346 RayQueryPositionFetchKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10398, 23), 239}, // 347 RayQueryProvisionalKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8576, 41), 323}, // 348 RayTracingClusterAccelerationStructureNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8148, 33), 312}, // 349 RayTracingDisplacementMicromapNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5625, 14), 243}, // 350 RayTracingKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8330, 39), 315}, // 351 RayTracingLinearSweptSpheresGeometryNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8034, 23), 292}, // 352 RayTracingMotionBlurNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5612, 13), 291}, // 353 RayTracingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12365, 29), 305}, // 354 RayTracingOpacityMicromapEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8087, 27), 290}, // 355 RayTracingPositionFetchKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12141, 25), 297}, // 356 RayTracingProvisionalKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8291, 28), 314}, // 357 RayTracingSpheresGeometryNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10452, 32), 242}, // 358 RayTraversalPrimitiveCullingKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15369, 20), 408}, // 359 RegisterLimitsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14400, 24), 373}, // 360 ReplicatedCompositesEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12892, 21), 329}, // 361 RoundToInfinityINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10366, 16), 237}, // 362 RoundingModeRTE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10382, 16), 238}, // 363 RoundingModeRTZ in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14076, 30), 363}, // 364 RuntimeAlignedAttributeALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14106, 29), 363}, // 365 RuntimeAlignedAttributeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11099, 23), 279}, // 366 RuntimeDescriptorArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11122, 26), 279}, // 367 RuntimeDescriptorArrayEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10835, 29), 264}, // 368 SampleMaskOverrideCoverageNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10201, 28), 230}, // 369 SampleMaskPostDepthCoverage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5871, 18), 166}, // 370 SampleRateShading in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9148, 10), 174}, // 371 Sampled1D in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9166, 14), 177}, // 372 SampledBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9050, 17), 176}, // 373 SampledCubeArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8935, 33), 160}, // 374 SampledImageArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11462, 36), 284}, // 375 SampledImageArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11498, 39), 284}, // 376 SampledImageArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9077, 12), 168}, // 377 SampledRect in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5515, 7), 134}, // 378 Shader in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12550, 23), 316}, // 379 Shader64BitIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10697, 15), 256}, // 380 ShaderClockKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6984, 18), 257}, // 381 ShaderEnqueueAMDX in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12420, 27), 307}, // 382 ShaderInvocationReorderEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12394, 26), 306}, // 383 ShaderInvocationReorderNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5687, 12), 200}, // 384 ShaderLayer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11062, 17), 278}, // 385 ShaderNonUniform in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11079, 20), 278}, // 386 ShaderNonUniformEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8402, 19), 301}, // 387 ShaderSMBuiltinsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7074, 19), 268}, // 388 ShaderStereoViewNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5755, 20), 201}, // 389 ShaderViewportIndex in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5699, 28), 266}, // 390 ShaderViewportIndexLayerEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10892, 27), 266}, // 391 ShaderViewportIndexLayerNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7033, 21), 267}, // 392 ShaderViewportMaskNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11019, 14), 276}, // 393 ShadingRateNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10341, 25), 236}, // 394 SignedZeroInfNanPreserve in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9125, 16), 172}, // 395 SparseResidency in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15229, 21), 402}, // 396 SpecConditionalINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14636, 18), 385}, // 397 SplitBarrierINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6938, 17), 253}, // 398 StencilExportEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9989, 25), 221}, // 399 StorageBuffer16BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10229, 24), 231}, // 400 StorageBuffer8BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8968, 34), 161}, // 401 StorageBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11537, 37), 285}, // 402 StorageBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11574, 40), 285}, // 403 StorageBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9002, 33), 162}, // 404 StorageImageArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11614, 36), 286}, // 405 StorageImageArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11650, 39), 286}, // 406 StorageImageArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9205, 28), 180}, // 407 StorageImageExtendedFormats in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8877, 24), 158}, // 408 StorageImageMultisample in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9318, 30), 186}, // 409 StorageImageReadWithoutFormat in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9348, 31), 187}, // 410 StorageImageWriteWithoutFormat in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10116, 21), 224}, // 411 StorageInputOutput16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10094, 22), 223}, // 412 StoragePushConstant16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10287, 21), 233}, // 413 StoragePushConstant8 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9681, 37), 208}, // 414 StorageTensorArrayDynamicIndexingARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9718, 40), 209}, // 415 StorageTensorArrayNonUniformIndexingARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11304, 39), 282}, // 416 StorageTexelBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11343, 42), 282}, // 417 StorageTexelBufferArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11857, 42), 289}, // 418 StorageTexelBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11899, 45), 289}, // 419 StorageTexelBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10077, 17), 222}, // 420 StorageUniform16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10014, 28), 221}, // 421 StorageUniformBufferBlock16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15048, 23), 396}, // 422 Subgroup2DBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15071, 30), 397}, // 423 Subgroup2DBlockTransformINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15101, 30), 398}, // 424 Subgroup2DBlockTransposeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13204, 39), 343}, // 425 SubgroupAvcMotionEstimationChromaINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13133, 33), 341}, // 426 SubgroupAvcMotionEstimationINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13166, 38), 342}, // 427 SubgroupAvcMotionEstimationIntraINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6138, 18), 215}, // 428 SubgroupBallotKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12808, 27), 326}, // 429 SubgroupBufferBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15020, 28), 395}, // 430 SubgroupBufferPrefetchINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9379, 17), 189}, // 431 SubgroupDispatch in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12835, 26), 327}, // 432 SubgroupImageBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12861, 31), 328}, // 433 SubgroupImageMediaBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15131, 38), 399}, // 434 SubgroupMatrixMultiplyAccumulateINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12787, 21), 325}, // 435 SubgroupShuffleINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9973, 16), 220}, // 436 SubgroupVoteKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14760, 19), 389}, // 437 TaskSequenceALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14779, 18), 389}, // 438 TaskSequenceINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12768, 19), 324}, // 439 TensorAddressingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15298, 27), 405}, // 440 TensorFloat32RoundingINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9670, 11), 207}, // 441 TensorsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15169, 28), 400}, // 442 TernaryBitwiseFunctionINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5599, 13), 136}, // 443 Tessellation in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8817, 22), 155}, // 444 TessellationPointSize in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10585, 23), 249}, // 445 TextureBlockMatch2QCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10531, 22), 246}, // 446 TextureBlockMatchQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10510, 21), 245}, // 447 TextureBoxFilterQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10484, 26), 244}, // 448 TextureSampleWeightedQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9584, 28), 204}, // 449 TileImageColorReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9612, 28), 205}, // 450 TileImageDepthReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9640, 30), 206}, // 451 TileImageStencilReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6701, 16), 247}, // 452 TileShadingQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9284, 18), 184}, // 453 TransformFeedback in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14029, 24), 362}, // 454 USMStorageClassesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14053, 23), 362}, // 455 USMStorageClassesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10042, 35), 222}, // 456 UniformAndStorageBuffer16BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10253, 34), 232}, // 457 UniformAndStorageBuffer8BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8901, 34), 159}, // 458 UniformBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11385, 37), 283}, // 459 UniformBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11422, 40), 283}, // 460 UniformBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9566, 18), 202}, // 461 UniformDecoration in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11223, 39), 281}, // 462 UniformTexelBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11262, 42), 281}, // 463 UniformTexelBufferArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11770, 42), 288}, // 464 UniformTexelBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11812, 45), 288}, // 465 UniformTexelBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13507, 30), 350}, // 466 UnstructuredLoopControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10433, 19), 241}, // 467 UntypedPointersKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15197, 32), 401}, // 468 UntypedVariableLengthArrayINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13243, 25), 344}, // 469 VariableLengthArrayINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10167, 17), 228}, // 470 VariablePointers in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10137, 30), 227}, // 471 VariablePointersStorageBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8659, 9), 140}, // 472 Vector16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13102, 15), 339}, // 473 VectorAnyINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13083, 19), 338}, // 474 VectorComputeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11944, 18), 293}, // 475 VulkanMemoryModel in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11983, 29), 294}, // 476 VulkanMemoryModelDeviceScope in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12012, 32), 294}, // 477 VulkanMemoryModelDeviceScopeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11962, 21), 293}, // 478 VulkanMemoryModelKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9929, 44), 219}, // 479 WorkgroupMemoryExplicitLayout16BitAccessKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9886, 43), 218}, // 480 WorkgroupMemoryExplicitLayout8BitAccessKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9853, 33), 217}, // 481 WorkgroupMemoryExplicitLayoutKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15421, 8), 411}, // 482 Address in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15429, 8), 412}, // 483 Boolean in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15437, 6), 413}, // 484 Float in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15443, 7), 414}, // 485 Signed in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15450, 11), 415}, // 486 SignedChar in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15461, 9), 416}, // 487 Unsigned in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15470, 13), 417}, // 488 UnsignedChar in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15409, 12), 410}, // 489 Unspecified in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15483, 6), 418}, // 490 Class in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15489, 10), 419}, // 491 Structure in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15499, 6), 420}, // 492 Union in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15520, 20), 422}, // 493 ImportedDeclaration in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(15505, 15), 421}, // 494 ImportedModule in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(15629, 15), 430}, // 495 FlagArtificial in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15644, 13), 431}, // 496 FlagExplicit in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15617, 12), 429}, // 497 FlagFwdDecl in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15707, 21), 435}, // 498 FlagIndirectVariable in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15600, 17), 428}, // 499 FlagIsDefinition in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15784, 16), 439}, // 500 FlagIsEnumClass in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15588, 12), 427}, // 501 FlagIsLocal in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15768, 16), 438}, // 502 FlagIsOptimized in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15561, 14), 425}, // 503 FlagIsPrivate in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15545, 16), 424}, // 504 FlagIsProtected in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15575, 13), 426}, // 505 FlagIsPublic in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15728, 20), 436}, // 506 FlagLValueReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15672, 18), 433}, // 507 FlagObjectPointer in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15657, 15), 432}, // 508 FlagPrototyped in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15748, 20), 437}, // 509 FlagRValueReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15690, 17), 434}, // 510 FlagStaticMember in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15820, 24), 441}, // 511 FlagTypePassByReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15800, 20), 440}, // 512 FlagTypePassByValue in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15540, 5), 423}, // 513 None in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(15905, 9), 446}, // 514 BitPiece in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(15937, 7), 450}, // 515 Constu in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(15844, 6), 442}, // 516 Deref in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(15944, 9), 451}, // 517 Fragment in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(15855, 6), 444}, // 518 Minus in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(15850, 5), 443}, // 519 Plus in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(15894, 11), 445}, // 520 PlusUconst in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(15926, 11), 449}, // 521 StackValue in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(15914, 5), 447}, // 522 Swap in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(15919, 7), 448}, // 523 Xderef in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(15989, 11), 455}, // 524 AtomicType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(15953, 10), 452}, // 525 ConstType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(15976, 13), 454}, // 526 RestrictType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(15963, 13), 453}, // 527 VolatileType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16000, 10), 456}, // 528 Float16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16010, 10), 457}, // 529 Float32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16020, 10), 458}, // 530 Float64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16188, 12), 469}, // 531 FloatE4M3NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16200, 12), 470}, // 532 FloatE5M2NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16043, 14), 460}, // 533 SignedInt16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16057, 14), 461}, // 534 SignedInt32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16071, 14), 462}, // 535 SignedInt64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16030, 13), 459}, // 536 SignedInt8NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16148, 19), 467}, // 537 SignedInt8PackedNV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16100, 16), 464}, // 538 UnsignedInt16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16116, 16), 465}, // 539 UnsignedInt32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16132, 16), 466}, // 540 UnsignedInt64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16085, 15), 463}, // 541 UnsignedInt8NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16167, 21), 468}, // 542 UnsignedInt8PackedNV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16264, 28), 474}, // 543 ColumnBlockedInterleavedARM in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(16224, 15), 472}, // 544 ColumnMajorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(16239, 25), 473}, // 545 RowBlockedInterleavedARM in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(16212, 12), 471}, // 546 RowMajorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(16300, 27), 476}, // 547 MatrixASignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16327, 27), 477}, // 548 MatrixBSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16354, 27), 478}, // 549 MatrixCSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16381, 32), 479}, // 550 MatrixResultSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16292, 8), 475}, // 551 NoneKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16413, 26), 480}, // 552 SaturatingAccumulationKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16450, 4), 483}, // 553 2x2 in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(16443, 7), 482}, // 554 Column in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(16439, 4), 481}, // 555 Row in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(16454, 11), 484}, // 556 MatrixAKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(16476, 21), 486}, // 557 MatrixAccumulatorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(16465, 11), 485}, // 558 MatrixBKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(16508, 14), 488}, // 559 ColumnMajorNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(16522, 21), 489}, // 560 InferencingOptimalNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(16497, 11), 487}, // 561 RowMajorNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(16543, 18), 490}, // 562 TrainingOptimalNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(15421, 8), 492}, // 563 Address in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15429, 8), 493}, // 564 Boolean in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15437, 6), 494}, // 565 Float in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15443, 7), 495}, // 566 Signed in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15450, 11), 496}, // 567 SignedChar in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15461, 9), 497}, // 568 Unsigned in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15470, 13), 498}, // 569 UnsignedChar in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15409, 12), 491}, // 570 Unspecified in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15483, 6), 499}, // 571 Class in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(15489, 10), 500}, // 572 Structure in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(15499, 6), 501}, // 573 Union in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(15629, 15), 509}, // 574 FlagArtificial in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15644, 13), 510}, // 575 FlagExplicit in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15617, 12), 508}, // 576 FlagFwdDecl in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15707, 21), 514}, // 577 FlagIndirectVariable in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15600, 17), 507}, // 578 FlagIsDefinition in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15588, 12), 506}, // 579 FlagIsLocal in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15768, 16), 517}, // 580 FlagIsOptimized in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15561, 14), 504}, // 581 FlagIsPrivate in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15545, 16), 503}, // 582 FlagIsProtected in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15575, 13), 505}, // 583 FlagIsPublic in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15728, 20), 515}, // 584 FlagLValueReference in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15672, 18), 512}, // 585 FlagObjectPointer in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15657, 15), 511}, // 586 FlagPrototyped in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15748, 20), 516}, // 587 FlagRValueReference in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15690, 17), 513}, // 588 FlagStaticMember in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15540, 5), 502}, // 589 None in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(15905, 9), 522}, // 590 BitPiece in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(15937, 7), 526}, // 591 Constu in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(15844, 6), 518}, // 592 Deref in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(15855, 6), 520}, // 593 Minus in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(15850, 5), 519}, // 594 Plus in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(15894, 11), 521}, // 595 PlusUconst in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(15926, 11), 525}, // 596 StackValue in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(15914, 5), 523}, // 597 Swap in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(15919, 7), 524}, // 598 Xderef in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(15953, 10), 527}, // 599 ConstType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(15976, 13), 529}, // 600 RestrictType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(15963, 13), 528}, // 601 VolatileType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(19216, 16), 645}, // 602 AliasScopeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16770, 8), 549}, // 603 Aliased in SPV_OPERAND_TYPE_DECORATION
  {IR(17888, 15), 602}, // 604 AliasedPointer in SPV_OPERAND_TYPE_DECORATION
  {IR(17903, 18), 602}, // 605 AliasedPointerEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(17248, 10), 573}, // 606 Alignment in SPV_OPERAND_TYPE_DECORATION
  {IR(17292, 12), 575}, // 607 AlignmentId in SPV_OPERAND_TYPE_DECORATION
  {IR(16621, 12), 536}, // 608 ArrayStride in SPV_OPERAND_TYPE_DECORATION
  {IR(18766, 15), 633}, // 609 BankBitsALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18781, 14), 633}, // 610 BankBitsINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18479, 16), 626}, // 611 BankwidthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18495, 15), 626}, // 612 BankwidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16925, 8), 562}, // 613 Binding in SPV_OPERAND_TYPE_DECORATION
  {IR(18000, 16), 606}, // 614 BindlessImageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17982, 18), 605}, // 615 BindlessSamplerNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16585, 6), 532}, // 616 Block in SPV_OPERAND_TYPE_DECORATION
  {IR(17432, 22), 582}, // 617 BlockMatchSamplerQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(17410, 22), 581}, // 618 BlockMatchTextureQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(18031, 13), 608}, // 619 BoundImageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18016, 15), 607}, // 620 BoundSamplerNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16591, 12), 533}, // 621 BufferBlock in SPV_OPERAND_TYPE_DECORATION
  {IR(19376, 21), 650}, // 622 BufferLocationALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19397, 20), 650}, // 623 BufferLocationINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16702, 8), 541}, // 624 BuiltIn in SPV_OPERAND_TYPE_DECORATION
  {IR(18935, 20), 638}, // 625 BurstCoalesceALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18955, 19), 638}, // 626 BurstCoalesceINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16668, 8), 540}, // 627 CPacked in SPV_OPERAND_TYPE_DECORATION
  {IR(20623, 22), 673}, // 628 CacheControlLoadINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20682, 23), 674}, // 629 CacheControlStoreINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18974, 16), 639}, // 630 CacheSizeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18990, 15), 639}, // 631 CacheSizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16735, 9), 545}, // 632 Centroid in SPV_OPERAND_TYPE_DECORATION
  {IR(18084, 13), 611}, // 633 ClobberINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16796, 9), 552}, // 634 Coherent in SPV_OPERAND_TYPE_DECORATION
  {IR(16612, 9), 535}, // 635 ColMajor in SPV_OPERAND_TYPE_DECORATION
  {IR(16909, 10), 560}, // 636 Component in SPV_OPERAND_TYPE_DECORATION
  {IR(20570, 17), 672}, // 637 ConditionalINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19799, 28), 660}, // 638 ConduitKernelArgumentALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19827, 27), 660}, // 639 ConduitKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16787, 9), 551}, // 640 Constant in SPV_OPERAND_TYPE_DECORATION
  {IR(18230, 14), 618}, // 641 CounterBuffer in SPV_OPERAND_TYPE_DECORATION
  {IR(16933, 14), 563}, // 642 DescriptorSet in SPV_OPERAND_TYPE_DECORATION
  {IR(19005, 29), 640}, // 643 DontStaticallyCoalesceALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19034, 28), 640}, // 644 DontStaticallyCoalesceINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18588, 17), 629}, // 645 DoublepumpALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18605, 16), 629}, // 646 DoublepumpINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17454, 18), 583}, // 647 ExplicitInterpAMD in SPV_OPERAND_TYPE_DECORATION
  {IR(17118, 15), 569}, // 648 FPFastMathMode in SPV_OPERAND_TYPE_DECORATION
  {IR(19661, 26), 657}, // 649 FPMaxErrorDecorationINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17068, 15), 568}, // 650 FPRoundingMode in SPV_OPERAND_TYPE_DECORATION
  {IR(16724, 5), 543}, // 651 Flat in SPV_OPERAND_TYPE_DECORATION
  {IR(18795, 21), 634}, // 652 ForcePow2DepthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18816, 20), 634}, // 653 ForcePow2DepthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17020, 14), 567}, // 654 FuncParamAttr in SPV_OPERAND_TYPE_DECORATION
  {IR(18141, 21), 614}, // 655 FuncParamIOKindINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18372, 24), 622}, // 656 FunctionDenormModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19490, 31), 652}, // 657 FunctionFloatingPointModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18315, 26), 621}, // 658 FunctionRoundingModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19126, 26), 643}, // 659 FuseLoopsInFunctionALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19152, 25), 643}, // 660 FuseLoopsInFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16657, 11), 539}, // 661 GLSLPacked in SPV_OPERAND_TYPE_DECORATION
  {IR(16646, 11), 538}, // 662 GLSLShared in SPV_OPERAND_TYPE_DECORATION
  {IR(18204, 26), 617}, // 663 GlobalVariableOffsetINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17951, 31), 604}, // 664 HitObjectShaderRecordBufferEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(17921, 30), 603}, // 665 HitObjectShaderRecordBufferNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18244, 24), 618}, // 666 HlslCounterBufferGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(18281, 19), 619}, // 667 HlslSemanticGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(20421, 16), 669}, // 668 HostAccessINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19417, 20), 651}, // 669 IOPipeStorageALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19437, 19), 651}, // 670 IOPipeStorageINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20513, 29), 671}, // 671 ImplementInRegisterMapALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20542, 28), 671}, // 672 ImplementInRegisterMapINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16919, 6), 561}, // 673 Index in SPV_OPERAND_TYPE_DECORATION
  {IR(20484, 15), 670}, // 674 InitModeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20499, 14), 670}, // 675 InitModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19245, 25), 647}, // 676 InitiationIntervalALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19270, 24), 647}, // 677 InitiationIntervalINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17227, 21), 572}, // 678 InputAttachmentIndex in SPV_OPERAND_TYPE_DECORATION
  {IR(16751, 10), 547}, // 679 Invariant in SPV_OPERAND_TYPE_DECORATION
  {IR(19738, 31), 659}, // 680 LatencyControlConstraintALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19769, 30), 659}, // 681 LatencyControlConstraintINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19687, 26), 658}, // 682 LatencyControlLabelALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19713, 25), 658}, // 683 LatencyControlLabelINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17195, 18), 570}, // 684 LinkageAttributes in SPV_OPERAND_TYPE_DECORATION
  {IR(16900, 9), 559}, // 685 Location in SPV_OPERAND_TYPE_DECORATION
  {IR(19917, 34), 662}, // 686 MMHostInterfaceAddressWidthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19951, 33), 662}, // 687 MMHostInterfaceAddressWidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19984, 31), 663}, // 688 MMHostInterfaceDataWidthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20015, 30), 663}, // 689 MMHostInterfaceDataWidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20045, 29), 664}, // 690 MMHostInterfaceLatencyALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20074, 28), 664}, // 691 MMHostInterfaceLatencyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20205, 30), 666}, // 692 MMHostInterfaceMaxBurstALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20235, 29), 666}, // 693 MMHostInterfaceMaxBurstINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20136, 35), 665}, // 694 MMHostInterfaceReadWriteModeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20171, 34), 665}, // 695 MMHostInterfaceReadWriteModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20264, 33), 667}, // 696 MMHostInterfaceWaitRequestALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20297, 32), 667}, // 697 MMHostInterfaceWaitRequestINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19177, 20), 644}, // 698 MathOpDSPModeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19197, 19), 644}, // 699 MathOpDSPModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16633, 13), 537}, // 700 MatrixStride in SPV_OPERAND_TYPE_DECORATION
  {IR(17258, 14), 574}, // 701 MaxByteOffset in SPV_OPERAND_TYPE_DECORATION
  {IR(17304, 16), 576}, // 702 MaxByteOffsetId in SPV_OPERAND_TYPE_DECORATION
  {IR(19294, 21), 648}, // 703 MaxConcurrencyALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19315, 20), 648}, // 704 MaxConcurrencyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18510, 23), 627}, // 705 MaxPrivateCopiesALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18533, 22), 627}, // 706 MaxPrivateCopiesINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18621, 20), 630}, // 707 MaxReplicatesALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18641, 19), 630}, // 708 MaxReplicatesINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19581, 18), 655}, // 709 MediaBlockIOINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18425, 13), 624}, // 710 MemoryALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18438, 12), 624}, // 711 MemoryINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18701, 12), 632}, // 712 MergeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18713, 11), 632}, // 713 MergeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19232, 13), 646}, // 714 NoAliasINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17213, 14), 571}, // 715 NoContraction in SPV_OPERAND_TYPE_DECORATION
  {IR(16710, 14), 542}, // 716 NoPerspective in SPV_OPERAND_TYPE_DECORATION
  {IR(17364, 13), 578}, // 717 NoSignedWrap in SPV_OPERAND_TYPE_DECORATION
  {IR(17377, 15), 579}, // 718 NoUnsignedWrap in SPV_OPERAND_TYPE_DECORATION
  {IR(17504, 20), 585}, // 719 NodeMaxPayloadsAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17472, 32), 584}, // 720 NodeSharesPayloadLimitsWithAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(16817, 12), 554}, // 721 NonReadable in SPV_OPERAND_TYPE_DECORATION
  {IR(17828, 11), 600}, // 722 NonUniform in SPV_OPERAND_TYPE_DECORATION
  {IR(17839, 14), 600}, // 723 NonUniformEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(16805, 12), 553}, // 724 NonWritable in SPV_OPERAND_TYPE_DECORATION
  {IR(18450, 15), 625}, // 725 NumbanksALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18465, 14), 625}, // 726 NumbanksINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16947, 7), 564}, // 727 Offset in SPV_OPERAND_TYPE_DECORATION
  {IR(17672, 19), 592}, // 728 OverrideCoverageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17691, 14), 593}, // 729 PassthroughNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16729, 6), 544}, // 730 Patch in SPV_OPERAND_TYPE_DECORATION
  {IR(17644, 28), 591}, // 731 PayloadDispatchIndirectAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17619, 25), 590}, // 732 PayloadNodeArraySizeAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17567, 25), 588}, // 733 PayloadNodeBaseIndexAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17547, 20), 587}, // 734 PayloadNodeNameAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17592, 27), 589}, // 735 PayloadNodeSparseArrayAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17752, 16), 596}, // 736 PerPrimitiveEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(17768, 15), 596}, // 737 PerPrimitiveNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17793, 10), 598}, // 738 PerTaskNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17803, 13), 599}, // 739 PerVertexKHR in SPV_OPERAND_TYPE_DECORATION
  {IR(17816, 12), 599}, // 740 PerVertexNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17783, 10), 597}, // 741 PerViewNV in SPV_OPERAND_TYPE_DECORATION
  {IR(19335, 21), 649}, // 742 PipelineEnableALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19356, 20), 649}, // 743 PipelineEnableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19062, 15), 641}, // 744 PrefetchALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19077, 14), 641}, // 745 PrefetchINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18058, 26), 610}, // 746 ReferencedIndirectlyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18396, 15), 623}, // 747 RegisterALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18411, 14), 623}, // 748 RegisterINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19854, 32), 661}, // 749 RegisterMapKernelArgumentALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19886, 31), 661}, // 750 RegisterMapKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16561, 17), 530}, // 751 RelaxedPrecision in SPV_OPERAND_TYPE_DECORATION
  {IR(16761, 9), 548}, // 752 Restrict in SPV_OPERAND_TYPE_DECORATION
  {IR(17853, 16), 601}, // 753 RestrictPointer in SPV_OPERAND_TYPE_DECORATION
  {IR(17869, 19), 601}, // 754 RestrictPointerEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(16603, 9), 534}, // 755 RowMajor in SPV_OPERAND_TYPE_DECORATION
  {IR(18044, 14), 609}, // 756 SIMTCallINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16744, 7), 546}, // 757 Sample in SPV_OPERAND_TYPE_DECORATION
  {IR(16873, 20), 557}, // 758 SaturatedConversion in SPV_OPERAND_TYPE_DECORATION
  {IR(17320, 44), 577}, // 759 SaturatedToLargestFloat8NormalConversionEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(17724, 28), 595}, // 760 SecondaryViewportRelativeNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18097, 17), 612}, // 761 SideEffectsINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18660, 21), 631}, // 762 SimpleDualPortALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18681, 20), 631}, // 763 SimpleDualPortINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19521, 25), 653}, // 764 SingleElementVectorINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18555, 17), 628}, // 765 SinglepumpALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18572, 16), 628}, // 766 SinglepumpINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16578, 7), 531}, // 767 SpecId in SPV_OPERAND_TYPE_DECORATION
  {IR(20329, 27), 668}, // 768 StableKernelArgumentALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20356, 26), 668}, // 769 StableKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18189, 15), 616}, // 770 StackCallINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19091, 18), 642}, // 771 StallEnableALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19109, 17), 642}, // 772 StallEnableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19599, 16), 656}, // 773 StallFreeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19615, 15), 656}, // 774 StallFreeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16893, 7), 558}, // 775 Stream in SPV_OPERAND_TYPE_DECORATION
  {IR(18836, 17), 635}, // 776 StridesizeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18853, 16), 635}, // 777 StridesizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17524, 23), 586}, // 778 TrackFinishWritingAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(18898, 19), 637}, // 779 TrueDualPortALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18917, 18), 637}, // 780 TrueDualPortINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16829, 8), 555}, // 781 Uniform in SPV_OPERAND_TYPE_DECORATION
  {IR(16863, 10), 556}, // 782 UniformId in SPV_OPERAND_TYPE_DECORATION
  {IR(18268, 13), 619}, // 783 UserSemantic in SPV_OPERAND_TYPE_DECORATION
  {IR(18300, 15), 620}, // 784 UserTypeGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(19546, 35), 654}, // 785 VectorComputeCallableFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18162, 27), 615}, // 786 VectorComputeFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18114, 27), 613}, // 787 VectorComputeVariableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17705, 19), 594}, // 788 ViewportRelativeNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16778, 9), 550}, // 789 Volatile in SPV_OPERAND_TYPE_DECORATION
  {IR(17392, 18), 580}, // 790 WeightTextureQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(18869, 15), 636}, // 791 WordsizeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18884, 14), 636}, // 792 WordsizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16954, 10), 565}, // 793 XfbBuffer in SPV_OPERAND_TYPE_DECORATION
  {IR(16964, 10), 566}, // 794 XfbStride in SPV_OPERAND_TYPE_DECORATION
  {IR(20705, 3), 675}, // 795 1D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(20708, 3), 676}, // 796 2D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(20711, 3), 677}, // 797 3D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(20724, 7), 680}, // 798 Buffer in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(20714, 5), 678}, // 799 Cube in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(20719, 5), 679}, // 800 Rect in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(20731, 12), 681}, // 801 SubpassData in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(20743, 17), 682}, // 802 TileImageDataEXT in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21555, 15), 735}, // 803 CoalescingAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21186, 15), 713}, // 804 ContractionOff in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10323, 18), 727}, // 805 DenormFlushToZero in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10308, 15), 726}, // 806 DenormPreserve in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20956, 13), 696}, // 807 DepthGreater in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20969, 10), 697}, // 808 DepthLess in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20941, 15), 695}, // 809 DepthReplacing in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20979, 15), 698}, // 810 DepthUnchanged in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21976, 25), 753}, // 811 DerivativeGroupLinearKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22001, 24), 753}, // 812 DerivativeGroupLinearNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21929, 24), 752}, // 813 DerivativeGroupQuadsKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21953, 23), 752}, // 814 DerivativeGroupQuadsNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21503, 29), 733}, // 815 EarlyAndLateFragmentTestsAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20908, 19), 692}, // 816 EarlyFragmentTests in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22486, 18), 773}, // 817 FPFastMathDefault in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21213, 10), 715}, // 818 Finalizer in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22301, 26), 765}, // 819 FloatingPointModeALTINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22327, 27), 766}, // 820 FloatingPointModeIEEEINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21201, 12), 714}, // 821 Initializer in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21030, 11), 702}, // 822 InputLines in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21041, 20), 703}, // 823 InputLinesAdjacency in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21018, 12), 701}, // 824 InputPoints in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21071, 24), 705}, // 825 InputTrianglesAdjacency in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20760, 12), 683}, // 826 Invocations in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21570, 15), 736}, // 827 IsApiEntryAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21101, 9), 707}, // 828 Isolines in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20994, 10), 699}, // 829 LocalSize in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21004, 14), 700}, // 830 LocalSizeHint in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21281, 16), 720}, // 831 LocalSizeHintId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21269, 12), 719}, // 832 LocalSizeId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21585, 21), 737}, // 833 MaxNodeRecursionAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21630, 21), 740}, // 834 MaxNumWorkgroupsAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22376, 16), 768}, // 835 MaxWorkDimINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22354, 22), 767}, // 836 MaxWorkgroupSizeINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22462, 24), 772}, // 837 MaximallyReconvergesKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22577, 22), 777}, // 838 MaximumRegistersINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22599, 24), 778}, // 839 MaximumRegistersIdINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22554, 23), 776}, // 840 NamedBarrierCountINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22674, 27), 779}, // 841 NamedMaximumRegistersINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22392, 20), 769}, // 842 NoGlobalOffsetINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21297, 34), 721}, // 843 NonCoherentColorAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21331, 34), 722}, // 844 NonCoherentDepthAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21365, 36), 723}, // 845 NonCoherentStencilAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21449, 34), 731}, // 846 NonCoherentTileAttachmentReadQCOM in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22412, 22), 770}, // 847 NumSIMDWorkitemsINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20892, 16), 691}, // 848 OriginLowerLeft in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20876, 16), 690}, // 849 OriginUpperLeft in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21138, 16), 710}, // 850 OutputLineStrip in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21861, 15), 750}, // 851 OutputLinesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21876, 14), 750}, // 852 OutputLinesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21125, 13), 709}, // 853 OutputPoints in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21890, 20), 751}, // 854 OutputPrimitivesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21910, 19), 751}, // 855 OutputPrimitivesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21154, 20), 711}, // 856 OutputTriangleStrip in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22025, 19), 754}, // 857 OutputTrianglesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22044, 18), 754}, // 858 OutputTrianglesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21110, 15), 708}, // 859 OutputVertices in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20857, 19), 689}, // 860 PixelCenterInteger in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22062, 25), 755}, // 861 PixelInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22087, 27), 756}, // 862 PixelInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20927, 10), 693}, // 863 PointMode in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21431, 18), 725}, // 864 PostDepthCoverage in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21802, 19), 747}, // 865 QuadDerivativesKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21095, 6), 706}, // 866 Quads in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22528, 26), 775}, // 867 RegisterMapInterfaceINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21821, 20), 748}, // 868 RequireFullQuadsKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10366, 16), 729}, // 869 RoundingModeRTE in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22280, 21), 764}, // 870 RoundingModeRTNINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22259, 21), 763}, // 871 RoundingModeRTPINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10382, 16), 730}, // 872 RoundingModeRTZ in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22114, 26), 757}, // 873 SampleInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22140, 28), 758}, // 874 SampleInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22434, 28), 771}, // 875 SchedulerTargetFmaxMhzINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(12550, 23), 761}, // 876 Shader64BitIndexingEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(7002, 16), 739}, // 877 ShaderIndexAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22168, 31), 759}, // 878 ShadingRateInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22199, 33), 760}, // 879 ShadingRateInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22232, 27), 762}, // 880 SharedLocalMemorySizeINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21841, 20), 749}, // 881 SharesInputWithAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10341, 25), 728}, // 882 SignedZeroInfNanPreserve in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20772, 13), 684}, // 883 SpacingEqual in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20785, 22), 685}, // 884 SpacingFractionalEven in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20807, 21), 686}, // 885 SpacingFractionalOdd in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21606, 24), 738}, // 886 StaticNumWorkgroupsAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21755, 25), 745}, // 887 StencilRefGreaterBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21679, 26), 742}, // 888 StencilRefGreaterFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21780, 22), 746}, // 889 StencilRefLessBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21705, 23), 743}, // 890 StencilRefLessFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21532, 23), 734}, // 891 StencilRefReplacingEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21728, 27), 744}, // 892 StencilRefUnchangedBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21651, 28), 741}, // 893 StencilRefUnchangedFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22504, 24), 774}, // 894 StreamingInterfaceINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(6109, 13), 716}, // 895 SubgroupSize in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21401, 30), 724}, // 896 SubgroupUniformControlFlowKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21223, 22), 717}, // 897 SubgroupsPerWorkgroup in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21245, 24), 718}, // 898 SubgroupsPerWorkgroupId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21483, 20), 732}, // 899 TileShadingRateQCOM in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21061, 10), 704}, // 900 Triangles in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21174, 12), 712}, // 901 VecTypeHint in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20842, 15), 688}, // 902 VertexOrderCcw in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20828, 14), 687}, // 903 VertexOrderCw in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20937, 4), 694}, // 904 Xfb in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22839, 10), 791}, // 905 AnyHitKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22849, 9), 791}, // 906 AnyHitNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22900, 12), 794}, // 907 CallableKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22912, 11), 794}, // 908 CallableNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22858, 14), 792}, // 909 ClosestHitKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22872, 13), 792}, // 910 ClosestHitNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(15944, 9), 784}, // 911 Fragment in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22751, 10), 785}, // 912 GLCompute in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(5590, 9), 783}, // 913 Geometry in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22808, 16), 790}, // 914 IntersectionKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22824, 15), 790}, // 915 IntersectionNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(5357, 7), 786}, // 916 Kernel in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22931, 8), 796}, // 917 MeshEXT in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22768, 7), 788}, // 918 MeshNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22885, 8), 793}, // 919 MissKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22893, 7), 793}, // 920 MissNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22775, 17), 789}, // 921 RayGenerationKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22792, 16), 789}, // 922 RayGenerationNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22923, 8), 795}, // 923 TaskEXT in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22761, 7), 787}, // 924 TaskNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22708, 20), 781}, // 925 TessellationControl in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22728, 23), 782}, // 926 TessellationEvaluation in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22701, 7), 780}, // 927 Vertex in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(22948, 12), 798}, // 928 FlushToZero in SPV_OPERAND_TYPE_FPDENORM_MODE
  {IR(22939, 9), 797}, // 929 Preserve in SPV_OPERAND_TYPE_FPDENORM_MODE
  {IR(22960, 12), 799}, // 930 BFloat16KHR in SPV_OPERAND_TYPE_FPENCODING
  {IR(22972, 14), 800}, // 931 Float8E4M3EXT in SPV_OPERAND_TYPE_FPENCODING
  {IR(22986, 14), 801}, // 932 Float8E5M2EXT in SPV_OPERAND_TYPE_FPENCODING
  {IR(23005, 4), 803}, // 933 ALT in SPV_OPERAND_TYPE_FPOPERATION_MODE
  {IR(23000, 5), 802}, // 934 IEEE in SPV_OPERAND_TYPE_FPOPERATION_MODE
  {IR(23043, 14), 810}, // 935 AllowContract in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23057, 23), 810}, // 936 AllowContractFastINTEL in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23080, 13), 811}, // 937 AllowReassoc in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23093, 18), 811}, // 938 AllowReassocINTEL in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23027, 11), 808}, // 939 AllowRecip in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23111, 15), 812}, // 940 AllowTransform in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23038, 5), 809}, // 941 Fast in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23023, 4), 807}, // 942 NSZ in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(15540, 5), 804}, // 943 None in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23016, 7), 806}, // 944 NotInf in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23009, 7), 805}, // 945 NotNaN in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23126, 4), 813}, // 946 RTE in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(23138, 4), 816}, // 947 RTN in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(23134, 4), 815}, // 948 RTP in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(23130, 4), 814}, // 949 RTZ in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(23174, 18), 819}, // 950 Horizontal2Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(23192, 18), 820}, // 951 Horizontal4Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(23142, 16), 817}, // 952 Vertical2Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(23158, 16), 818}, // 953 Vertical4Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(23233, 6), 825}, // 954 Const in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(23217, 11), 823}, // 955 DontInline in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(23210, 7), 822}, // 956 Inline in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(15540, 5), 821}, // 957 None in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(14547, 11), 826}, // 958 OptNoneEXT in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(14558, 13), 826}, // 959 OptNoneINTEL in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(23228, 5), 824}, // 960 Pure in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(23249, 6), 829}, // 961 ByVal in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23260, 8), 831}, // 962 NoAlias in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23268, 10), 832}, // 963 NoCapture in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23286, 12), 834}, // 964 NoReadWrite in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23278, 8), 833}, // 965 NoWrite in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23298, 21), 835}, // 966 RuntimeAlignedALTERA in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23319, 20), 835}, // 967 RuntimeAlignedINTEL in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23244, 5), 828}, // 968 Sext in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23255, 5), 830}, // 969 Sret in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23239, 5), 827}, // 970 Zext in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23374, 16), 839}, // 971 ClusteredReduce in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23360, 14), 838}, // 972 ExclusiveScan in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23346, 14), 837}, // 973 InclusiveScan in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23437, 27), 842}, // 974 PartitionedExclusiveScanNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23410, 27), 841}, // 975 PartitionedInclusiveScanNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23390, 20), 840}, // 976 PartitionedReduceNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23339, 7), 836}, // 977 Reduce in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23464, 10), 843}, // 978 NoneINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(23474, 10), 844}, // 979 ReadINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(23495, 15), 846}, // 980 ReadWriteINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(23484, 11), 845}, // 981 WriteINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(23510, 5), 848}, // 982 Bias in SPV_OPERAND_TYPE_IMAGE
  {IR(23524, 12), 851}, // 983 ConstOffset in SPV_OPERAND_TYPE_IMAGE
  {IR(23536, 13), 853}, // 984 ConstOffsets in SPV_OPERAND_TYPE_IMAGE
  {IR(23519, 5), 850}, // 985 Grad in SPV_OPERAND_TYPE_IMAGE
  {IR(23515, 4), 849}, // 986 Lod in SPV_OPERAND_TYPE_IMAGE
  {IR(23549, 19), 856}, // 987 MakeTexelAvailable in SPV_OPERAND_TYPE_IMAGE
  {IR(23568, 22), 856}, // 988 MakeTexelAvailableKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(23590, 17), 857}, // 989 MakeTexelVisible in SPV_OPERAND_TYPE_IMAGE
  {IR(23607, 20), 857}, // 990 MakeTexelVisibleKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(9141, 7), 855}, // 991 MinLod in SPV_OPERAND_TYPE_IMAGE
  {IR(23627, 16), 858}, // 992 NonPrivateTexel in SPV_OPERAND_TYPE_IMAGE
  {IR(23643, 19), 858}, // 993 NonPrivateTexelKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(15540, 5), 847}, // 994 None in SPV_OPERAND_TYPE_IMAGE
  {IR(23715, 12), 862}, // 995 Nontemporal in SPV_OPERAND_TYPE_IMAGE
  {IR(16947, 7), 852}, // 996 Offset in SPV_OPERAND_TYPE_IMAGE
  {IR(23727, 8), 863}, // 997 Offsets in SPV_OPERAND_TYPE_IMAGE
  {IR(16744, 7), 854}, // 998 Sample in SPV_OPERAND_TYPE_IMAGE
  {IR(23693, 11), 860}, // 999 SignExtend in SPV_OPERAND_TYPE_IMAGE
  {IR(23662, 14), 859}, // 1000 VolatileTexel in SPV_OPERAND_TYPE_IMAGE
  {IR(23676, 17), 859}, // 1001 VolatileTexelKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(23704, 11), 861}, // 1002 ZeroExtend in SPV_OPERAND_TYPE_IMAGE
  {IR(15437, 6), 878}, // 1003 Float in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23896, 10), 877}, // 1004 HalfFloat in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23831, 12), 872}, // 1005 SignedInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23843, 12), 873}, // 1006 SignedInt32 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23820, 11), 871}, // 1007 SignedInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23745, 11), 865}, // 1008 SnormInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23735, 10), 864}, // 1009 SnormInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23805, 15), 870}, // 1010 UnormInt101010 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23917, 17), 880}, // 1011 UnormInt101010_2 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23934, 16), 881}, // 1012 UnormInt10X6EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24067, 16), 888}, // 1013 UnormInt12X4EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24083, 16), 889}, // 1014 UnormInt14X2EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23766, 11), 867}, // 1015 UnormInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23906, 11), 879}, // 1016 UnormInt24 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23990, 20), 884}, // 1017 UnormInt2_101010EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23756, 10), 866}, // 1018 UnormInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23791, 14), 869}, // 1019 UnormShort555 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23777, 14), 868}, // 1020 UnormShort565 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24010, 19), 885}, // 1021 UnsignedInt10X6EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24029, 19), 886}, // 1022 UnsignedInt12X4EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24048, 19), 887}, // 1023 UnsignedInt14X2EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23868, 14), 875}, // 1024 UnsignedInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23882, 14), 876}, // 1025 UnsignedInt32 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23855, 13), 874}, // 1026 UnsignedInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23950, 20), 882}, // 1027 UnsignedIntRaw10EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(23970, 20), 883}, // 1028 UnsignedIntRaw12EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24101, 2), 891}, // 1029 A in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24202, 5), 909}, // 1030 ABGR in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24123, 5), 897}, // 1031 ARGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24118, 5), 896}, // 1032 BGRA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24160, 6), 903}, // 1033 Depth in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24166, 13), 904}, // 1034 DepthStencil in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24128, 10), 898}, // 1035 Intensity in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24138, 10), 899}, // 1036 Luminance in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24099, 2), 890}, // 1037 R in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24106, 3), 893}, // 1038 RA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24103, 3), 892}, // 1039 RG in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24109, 4), 894}, // 1040 RGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24113, 5), 895}, // 1041 RGBA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24155, 5), 902}, // 1042 RGBx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24151, 4), 901}, // 1043 RGx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24148, 3), 900}, // 1044 Rx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24196, 6), 908}, // 1045 sBGRA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24179, 5), 905}, // 1046 sRGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24190, 6), 907}, // 1047 sRGBA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24184, 6), 906}, // 1048 sRGBx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24207, 28), 910}, // 1049 InitOnDeviceReprogramALTERA in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(24235, 27), 910}, // 1050 InitOnDeviceReprogramINTEL in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(24262, 24), 911}, // 1051 InitOnDeviceResetALTERA in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(24286, 23), 911}, // 1052 InitOnDeviceResetINTEL in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(24309, 7), 912}, // 1053 NoWait in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(24316, 11), 913}, // 1054 WaitKernel in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(24327, 14), 914}, // 1055 WaitWorkGroup in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(24341, 12), 916}, // 1056 CmdExecTime in SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {IR(15540, 5), 915}, // 1057 None in SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {IR(24353, 13), 918}, // 1058 MayUsePrintf in SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {IR(15540, 5), 917}, // 1059 None in SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {IR(24366, 7), 919}, // 1060 Export in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(24373, 7), 920}, // 1061 Import in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(24380, 12), 921}, // 1062 LinkOnceODR in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(24406, 12), 923}, // 1063 CachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(24458, 17), 926}, // 1064 ConstCachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(24433, 25), 925}, // 1065 InvalidateAfterReadINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(24418, 15), 924}, // 1066 StreamingINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(24392, 14), 922}, // 1067 UncachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(24598, 22), 939}, // 1068 DependencyArrayALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24620, 21), 939}, // 1069 DependencyArrayINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24493, 19), 930}, // 1070 DependencyInfinite in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24512, 17), 931}, // 1071 DependencyLength in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24482, 11), 929}, // 1072 DontUnroll in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19245, 25), 937}, // 1073 InitiationIntervalALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19270, 24), 937}, // 1074 InitiationIntervalINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24557, 18), 934}, // 1075 IterationMultiple in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24641, 19), 941}, // 1076 LoopCoalesceALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24660, 18), 941}, // 1077 LoopCoalesceINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24803, 16), 945}, // 1078 LoopCountALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24819, 15), 945}, // 1079 LoopCountINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19294, 21), 938}, // 1080 MaxConcurrencyALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19315, 20), 938}, // 1081 MaxConcurrencyINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24678, 22), 942}, // 1082 MaxInterleavingALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24700, 21), 942}, // 1083 MaxInterleavingINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24543, 14), 933}, // 1084 MaxIterations in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24834, 27), 946}, // 1085 MaxReinvocationDelayALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24861, 26), 946}, // 1086 MaxReinvocationDelayINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24529, 14), 932}, // 1087 MinIterations in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24774, 15), 944}, // 1088 NoFusionALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24789, 14), 944}, // 1089 NoFusionINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(15540, 5), 927}, // 1090 None in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24585, 13), 936}, // 1091 PartialCount in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24575, 10), 935}, // 1092 PeelCount in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19335, 21), 940}, // 1093 PipelineEnableALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19356, 20), 940}, // 1094 PipelineEnableINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24721, 27), 943}, // 1095 SpeculatedIterationsALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24748, 26), 943}, // 1096 SpeculatedIterationsINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(24475, 7), 928}, // 1097 Unroll in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25170, 27), 960}, // 1098 MatrixAPackedBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25118, 26), 958}, // 1099 MatrixAPackedFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25038, 23), 954}, // 1100 MatrixAPackedInt4INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(24992, 23), 952}, // 1101 MatrixAPackedInt8INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(24887, 29), 948}, // 1102 MatrixASignedComponentsINTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25084, 17), 956}, // 1103 MatrixATF32INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25197, 27), 961}, // 1104 MatrixBPackedBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25144, 26), 959}, // 1105 MatrixBPackedFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25061, 23), 955}, // 1106 MatrixBPackedInt4INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25015, 23), 953}, // 1107 MatrixBPackedInt8INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(24916, 29), 949}, // 1108 MatrixBSignedComponentsINTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25101, 17), 957}, // 1109 MatrixBTF32INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(24945, 21), 950}, // 1110 MatrixCBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(24966, 26), 951}, // 1111 MatrixResultBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(15540, 5), 947}, // 1112 None in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25357, 20), 969}, // 1113 AliasScopeINTELMask in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25224, 8), 964}, // 1114 Aligned in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25232, 21), 966}, // 1115 MakePointerAvailable in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25253, 24), 966}, // 1116 MakePointerAvailableKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25277, 19), 967}, // 1117 MakePointerVisible in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25296, 22), 967}, // 1118 MakePointerVisibleKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25377, 17), 970}, // 1119 NoAliasINTELMask in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25318, 18), 968}, // 1120 NonPrivatePointer in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25336, 21), 968}, // 1121 NonPrivatePointerKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(15540, 5), 962}, // 1122 None in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(23715, 12), 965}, // 1123 Nontemporal in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(16778, 9), 963}, // 1124 Volatile in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25401, 8), 972}, // 1125 GLSL450 in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(25409, 7), 973}, // 1126 OpenCL in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(25394, 7), 971}, // 1127 Simple in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(25416, 7), 974}, // 1128 Vulkan in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(25423, 10), 974}, // 1129 VulkanKHR in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(25441, 8), 976}, // 1130 Acquire in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25457, 15), 978}, // 1131 AcquireRelease in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25561, 20), 984}, // 1132 AtomicCounterMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25540, 21), 983}, // 1133 CrossWorkgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25581, 12), 985}, // 1134 ImageMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25622, 14), 987}, // 1135 MakeAvailable in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25636, 17), 987}, // 1136 MakeAvailableKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25653, 12), 988}, // 1137 MakeVisible in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25665, 15), 988}, // 1138 MakeVisibleKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(15540, 5), 975}, // 1139 None in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25593, 13), 986}, // 1140 OutputMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25606, 16), 986}, // 1141 OutputMemoryKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25433, 8), 975}, // 1142 Relaxed in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25449, 8), 977}, // 1143 Release in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25472, 23), 979}, // 1144 SequentiallyConsistent in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25509, 15), 981}, // 1145 SubgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25495, 14), 980}, // 1146 UniformMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(16778, 9), 989}, // 1147 Volatile in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25524, 16), 982}, // 1148 WorkgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(25680, 10), 990}, // 1149 AutoINTEL in SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS
  {IR(25695, 4), 992}, // 1150 SAT in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(25708, 8), 994}, // 1151 SAT_SYM in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(25699, 9), 993}, // 1152 SAT_ZERO in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(25690, 5), 991}, // 1153 WRAP in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(25716, 25), 995}, // 1154 PackedVectorFormat4x8Bit in SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {IR(25741, 28), 995}, // 1155 PackedVectorFormat4x8BitKHR in SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {IR(25782, 4), 998}, // 1156 RND in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(25815, 9), 1002}, // 1157 RND_CONV in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(25824, 13), 1003}, // 1158 RND_CONV_ODD in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(25795, 8), 1000}, // 1159 RND_INF in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(25803, 12), 1001}, // 1160 RND_MIN_INF in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(25786, 9), 999}, // 1161 RND_ZERO in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(25769, 4), 996}, // 1162 TRN in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(25773, 9), 997}, // 1163 TRN_ZERO in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(15540, 5), 1004}, // 1164 None in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(25837, 25), 1005}, // 1165 RobustnessPerComponentNV in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(25862, 23), 1006}, // 1166 RobustnessPerElementNV in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(25954, 27), 1012}, // 1167 CullBackFacingTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(25981, 28), 1013}, // 1168 CullFrontFacingTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26023, 16), 1015}, // 1169 CullNoOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26009, 14), 1014}, // 1170 CullOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26093, 30), 1018}, // 1171 ForceOpacityMicromap2StateEXT in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(25895, 12), 1009}, // 1172 NoOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(16292, 8), 1007}, // 1173 NoneKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(25885, 10), 1008}, // 1174 OpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26080, 13), 1017}, // 1175 SkipAABBsKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26056, 24), 1016}, // 1176 SkipBuiltinPrimitivesNV in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(25930, 24), 1011}, // 1177 SkipClosestHitShaderKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26039, 17), 1016}, // 1178 SkipTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(25907, 23), 1010}, // 1179 TerminateOnFirstHitKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26164, 37), 1020}, // 1180 RayQueryCandidateIntersectionAABBKHR in SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {IR(26123, 41), 1019}, // 1181 RayQueryCandidateIntersectionTriangleKHR in SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {IR(26279, 42), 1023}, // 1182 RayQueryCommittedIntersectionGeneratedKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(26201, 37), 1021}, // 1183 RayQueryCommittedIntersectionNoneKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(26238, 41), 1022}, // 1184 RayQueryCommittedIntersectionTriangleKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(26321, 33), 1024}, // 1185 RayQueryCandidateIntersectionKHR in SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {IR(26354, 33), 1025}, // 1186 RayQueryCommittedIntersectionKHR in SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {IR(26399, 6), 1028}, // 1187 Clamp in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(26387, 12), 1027}, // 1188 ClampToEdge in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(15540, 5), 1026}, // 1189 None in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(26405, 7), 1029}, // 1190 Repeat in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(26412, 15), 1030}, // 1191 RepeatMirrored in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(26435, 7), 1032}, // 1192 Linear in SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {IR(26427, 8), 1031}, // 1193 Nearest in SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {IR(26500, 13), 1041}, // 1194 R11fG11fB10f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26542, 4), 1047}, // 1195 R16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26580, 9), 1052}, // 1196 R16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26513, 5), 1042}, // 1197 R16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26642, 5), 1061}, // 1198 R16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26713, 6), 1071}, // 1199 R16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26466, 5), 1036}, // 1200 R32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26620, 5), 1057}, // 1201 R32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26677, 6), 1066}, // 1202 R32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26730, 5), 1074}, // 1203 R64i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26724, 6), 1073}, // 1204 R64ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26546, 3), 1048}, // 1205 R8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26589, 8), 1053}, // 1206 R8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26647, 4), 1062}, // 1207 R8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26719, 5), 1072}, // 1208 R8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26533, 5), 1045}, // 1209 Rg16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26561, 10), 1050}, // 1210 Rg16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26494, 6), 1040}, // 1211 Rg16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26631, 6), 1059}, // 1212 Rg16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26700, 7), 1069}, // 1213 Rg16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26488, 6), 1039}, // 1214 Rg32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26625, 6), 1058}, // 1215 Rg32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26693, 7), 1068}, // 1216 Rg32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26538, 4), 1046}, // 1217 Rg8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26571, 9), 1051}, // 1218 Rg8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26637, 5), 1060}, // 1219 Rg8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26707, 6), 1070}, // 1220 Rg8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26525, 8), 1044}, // 1221 Rgb10A2 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26683, 10), 1067}, // 1222 Rgb10a2ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26518, 7), 1043}, // 1223 Rgba16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26549, 12), 1049}, // 1224 Rgba16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26458, 8), 1035}, // 1225 Rgba16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26605, 8), 1055}, // 1226 Rgba16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26660, 9), 1064}, // 1227 Rgba16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26450, 8), 1034}, // 1228 Rgba32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26597, 8), 1054}, // 1229 Rgba32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26651, 9), 1063}, // 1230 Rgba32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26471, 6), 1037}, // 1231 Rgba8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26477, 11), 1038}, // 1232 Rgba8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26613, 7), 1056}, // 1233 Rgba8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26669, 8), 1065}, // 1234 Rgba8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26442, 8), 1033}, // 1235 Unknown in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(26735, 12), 1075}, // 1236 CrossDevice in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(26747, 7), 1076}, // 1237 Device in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(26773, 11), 1079}, // 1238 Invocation in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(26784, 12), 1080}, // 1239 QueueFamily in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(26796, 15), 1080}, // 1240 QueueFamilyKHR in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(26811, 14), 1081}, // 1241 ShaderCallKHR in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(26764, 9), 1078}, // 1242 Subgroup in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(26754, 10), 1077}, // 1243 Workgroup in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(26833, 12), 1084}, // 1244 DontFlatten in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(26825, 8), 1083}, // 1245 Flatten in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(15540, 5), 1082}, // 1246 None in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(26845, 29), 1085}, // 1247 IdentifierPossibleDuplicates in SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS
  {IR(15421, 8), 1087}, // 1248 Address in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15429, 8), 1088}, // 1249 Boolean in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15437, 6), 1089}, // 1250 Float in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15443, 7), 1090}, // 1251 Signed in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15450, 11), 1091}, // 1252 SignedChar in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15461, 9), 1092}, // 1253 Unsigned in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15470, 13), 1093}, // 1254 UnsignedChar in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15409, 12), 1086}, // 1255 Unspecified in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15483, 6), 1094}, // 1256 Class in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15489, 10), 1095}, // 1257 Structure in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15499, 6), 1096}, // 1258 Union in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15520, 20), 1098}, // 1259 ImportedDeclaration in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(15505, 15), 1097}, // 1260 ImportedModule in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(15629, 15), 1106}, // 1261 FlagArtificial in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15644, 13), 1107}, // 1262 FlagExplicit in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15617, 12), 1105}, // 1263 FlagFwdDecl in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15707, 21), 1111}, // 1264 FlagIndirectVariable in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15600, 17), 1104}, // 1265 FlagIsDefinition in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15784, 16), 1115}, // 1266 FlagIsEnumClass in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15588, 12), 1103}, // 1267 FlagIsLocal in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15768, 16), 1114}, // 1268 FlagIsOptimized in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15561, 14), 1101}, // 1269 FlagIsPrivate in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15545, 16), 1100}, // 1270 FlagIsProtected in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15575, 13), 1102}, // 1271 FlagIsPublic in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15728, 20), 1112}, // 1272 FlagLValueReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15672, 18), 1109}, // 1273 FlagObjectPointer in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15657, 15), 1108}, // 1274 FlagPrototyped in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15748, 20), 1113}, // 1275 FlagRValueReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15690, 17), 1110}, // 1276 FlagStaticMember in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15820, 24), 1117}, // 1277 FlagTypePassByReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15800, 20), 1116}, // 1278 FlagTypePassByValue in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(26874, 26), 1118}, // 1279 FlagUnknownPhysicalLayout in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15540, 5), 1099}, // 1280 None in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(15905, 9), 1123}, // 1281 BitPiece in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(15937, 7), 1127}, // 1282 Constu in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(15844, 6), 1119}, // 1283 Deref in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(15944, 9), 1128}, // 1284 Fragment in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(15855, 6), 1121}, // 1285 Minus in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(15850, 5), 1120}, // 1286 Plus in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(15894, 11), 1122}, // 1287 PlusUconst in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(15926, 11), 1126}, // 1288 StackValue in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(15914, 5), 1124}, // 1289 Swap in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(15919, 7), 1125}, // 1290 Xderef in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(15989, 11), 1132}, // 1291 AtomicType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(15953, 10), 1129}, // 1292 ConstType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(15976, 13), 1131}, // 1293 RestrictType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(15963, 13), 1130}, // 1294 VolatileType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(26935, 15), 1139}, // 1295 CPP_for_OpenCL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(26900, 5), 1134}, // 1296 ESSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(26905, 5), 1135}, // 1297 GLSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(26955, 7), 1141}, // 1298 HERO_C in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(26930, 5), 1138}, // 1299 HLSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(26962, 5), 1142}, // 1300 NZSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(26910, 9), 1136}, // 1301 OpenCL_C in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(26919, 11), 1137}, // 1302 OpenCL_CPP in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(26982, 5), 1146}, // 1303 Rust in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(26950, 5), 1140}, // 1304 SYCL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(26972, 6), 1144}, // 1305 Slang in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(26442, 8), 1133}, // 1306 Unknown in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(26967, 5), 1143}, // 1307 WGSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(26978, 4), 1145}, // 1308 Zig in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27069, 14), 1157}, // 1309 AtomicCounter in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27151, 16), 1163}, // 1310 CallableDataKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27167, 15), 1163}, // 1311 CallableDataNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27487, 17), 1173}, // 1312 CodeSectionINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27016, 15), 1152}, // 1313 CrossWorkgroup in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27504, 17), 1174}, // 1314 DeviceOnlyALTERA in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27521, 16), 1174}, // 1315 DeviceOnlyINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27039, 9), 1154}, // 1316 Function in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27048, 8), 1155}, // 1317 Generic in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27256, 16), 1166}, // 1318 HitAttributeKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27272, 15), 1166}, // 1319 HitAttributeNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27465, 22), 1172}, // 1320 HitObjectAttributeEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27420, 21), 1170}, // 1321 HitObjectAttributeNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27537, 15), 1175}, // 1322 HostOnlyALTERA in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27552, 14), 1175}, // 1323 HostOnlyINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27083, 6), 1158}, // 1324 Image in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27182, 24), 1164}, // 1325 IncomingCallableDataKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27206, 23), 1164}, // 1326 IncomingCallableDataNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27287, 22), 1167}, // 1327 IncomingRayPayloadKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27309, 21), 1167}, // 1328 IncomingRayPayloadNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27003, 6), 1148}, // 1329 Input in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27135, 16), 1162}, // 1330 NodePayloadAMDX in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27009, 7), 1150}, // 1331 Output in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27373, 22), 1169}, // 1332 PhysicalStorageBuffer in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27395, 25), 1169}, // 1333 PhysicalStorageBufferEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27031, 8), 1153}, // 1334 Private in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27056, 13), 1156}, // 1335 PushConstant in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27229, 14), 1165}, // 1336 RayPayloadKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27243, 13), 1165}, // 1337 RayPayloadNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27330, 22), 1168}, // 1338 ShaderRecordBufferKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27352, 21), 1168}, // 1339 ShaderRecordBufferNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27089, 14), 1159}, // 1340 StorageBuffer in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27441, 24), 1171}, // 1341 TaskPayloadWorkgroupEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27116, 19), 1161}, // 1342 TileAttachmentQCOM in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27103, 13), 1160}, // 1343 TileImageEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(16829, 8), 1149}, // 1344 Uniform in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(26987, 16), 1147}, // 1345 UniformConstant in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(26754, 10), 1151}, // 1346 Workgroup in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24418, 15), 1179}, // 1347 StreamingINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(24392, 14), 1176}, // 1348 UncachedINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(27584, 15), 1178}, // 1349 WriteBackINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(27566, 18), 1177}, // 1350 WriteThroughINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(27610, 11), 1182}, // 1351 DecodeFunc in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(15540, 5), 1180}, // 1352 None in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(27599, 11), 1181}, // 1353 TensorView in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(26387, 12), 1185}, // 1354 ClampToEdge in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(16787, 9), 1184}, // 1355 Constant in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(26405, 7), 1186}, // 1356 Repeat in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(26412, 15), 1187}, // 1357 RepeatMirrored in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(27621, 10), 1183}, // 1358 Undefined in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(27674, 24), 1191}, // 1359 MakeElementAvailableARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(27698, 22), 1192}, // 1360 MakeElementVisibleARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(27720, 21), 1193}, // 1361 NonPrivateElementARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(27631, 8), 1188}, // 1362 NoneARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(27639, 15), 1189}, // 1363 NontemporalARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(27654, 20), 1190}, // 1364 OutOfBoundsValueARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
}};

IndexRange OperandNameRangeForKind(spv_operand_type_t type) {
  switch(type) {
    case SPV_OPERAND_TYPE_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_ADDRESSING_MODEL: return IR(3, 5);
    case SPV_OPERAND_TYPE_BUILT_IN: return IR(8, 148);
    case SPV_OPERAND_TYPE_CAPABILITY: return IR(156, 326);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(482, 8);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(490, 3);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(493, 2);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS: return IR(495, 19);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION: return IR(514, 10);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(524, 4);
    case SPV_OPERAND_TYPE_COMPONENT_TYPE: return IR(528, 15);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT: return IR(543, 4);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS: return IR(547, 6);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE: return IR(553, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE: return IR(556, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT: return IR(559, 4);
    case SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(563, 8);
    case SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE: return IR(571, 3);
    case SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS: return IR(574, 16);
    case SPV_OPERAND_TYPE_DEBUG_OPERATION: return IR(590, 9);
    case SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER: return IR(599, 3);
    case SPV_OPERAND_TYPE_DECORATION: return IR(602, 193);
    case SPV_OPERAND_TYPE_DIMENSIONALITY: return IR(795, 8);
    case SPV_OPERAND_TYPE_EXECUTION_MODE: return IR(803, 102);
    case SPV_OPERAND_TYPE_EXECUTION_MODEL: return IR(905, 23);
    case SPV_OPERAND_TYPE_FPDENORM_MODE: return IR(928, 2);
    case SPV_OPERAND_TYPE_FPENCODING: return IR(930, 3);
    case SPV_OPERAND_TYPE_FPOPERATION_MODE: return IR(933, 2);
    case SPV_OPERAND_TYPE_FP_FAST_MATH_MODE: return IR(935, 11);
    case SPV_OPERAND_TYPE_FP_ROUNDING_MODE: return IR(946, 4);
    case SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE: return IR(950, 4);
    case SPV_OPERAND_TYPE_FUNCTION_CONTROL: return IR(954, 7);
    case SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE: return IR(961, 10);
    case SPV_OPERAND_TYPE_GROUP_OPERATION: return IR(971, 7);
    case SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER: return IR(978, 4);
    case SPV_OPERAND_TYPE_IMAGE: return IR(982, 21);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE: return IR(1003, 26);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER: return IR(1029, 20);
    case SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER: return IR(1049, 4);
    case SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS: return IR(1053, 3);
    case SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO: return IR(1056, 2);
    case SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS: return IR(1058, 2);
    case SPV_OPERAND_TYPE_LINKAGE_TYPE: return IR(1060, 3);
    case SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL: return IR(1063, 5);
    case SPV_OPERAND_TYPE_LOOP_CONTROL: return IR(1068, 30);
    case SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(1098, 15);
    case SPV_OPERAND_TYPE_MEMORY_ACCESS: return IR(1113, 12);
    case SPV_OPERAND_TYPE_MEMORY_MODEL: return IR(1125, 5);
    case SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID: return IR(1130, 19);
    case SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS: return IR(1149, 1);
    case SPV_OPERAND_TYPE_OVERFLOW_MODES: return IR(1150, 4);
    case SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT: return IR(1154, 2);
    case SPV_OPERAND_TYPE_QUANTIZATION_MODES: return IR(1156, 8);
    case SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS: return IR(1164, 3);
    case SPV_OPERAND_TYPE_RAY_FLAGS: return IR(1167, 13);
    case SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE: return IR(1180, 2);
    case SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE: return IR(1182, 3);
    case SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION: return IR(1185, 2);
    case SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE: return IR(1187, 5);
    case SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE: return IR(1192, 2);
    case SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT: return IR(1194, 42);
    case SPV_OPERAND_TYPE_SCOPE_ID: return IR(1236, 8);
    case SPV_OPERAND_TYPE_SELECTION_CONTROL: return IR(1244, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS: return IR(1247, 1);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(1248, 8);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(1256, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(1259, 2);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS: return IR(1261, 20);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION: return IR(1281, 10);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(1291, 4);
    case SPV_OPERAND_TYPE_SOURCE_LANGUAGE: return IR(1295, 14);
    case SPV_OPERAND_TYPE_STORAGE_CLASS: return IR(1309, 38);
    case SPV_OPERAND_TYPE_STORE_CACHE_CONTROL: return IR(1347, 4);
    case SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS: return IR(1351, 3);
    case SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE: return IR(1354, 5);
    case SPV_OPERAND_TYPE_TENSOR_OPERANDS: return IR(1359, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_IMAGE: return IR(982, 21);
    case SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS: return IR(1113, 12);
    case SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT: return IR(1154, 2);
    case SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS: return IR(547, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(1098, 15);
    case SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS: return IR(1164, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_FPENCODING: return IR(930, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS: return IR(1359, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_CAPABILITY: return IR(156, 326);
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
  {spv::Op::OpNop, false, false, IR(0, 0), IR(27741, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpUndef, true, true, IR(39, 2), IR(27797, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpSourceContinued, false, false, IR(11, 1), IR(27803, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpSource, false, false, IR(41, 4), IR(27922, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpSourceExtension, false, false, IR(11, 1), IR(27929, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpName, false, false, IR(45, 2), IR(27945, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpMemberName, false, false, IR(47, 3), IR(27950, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpString, true, false, IR(50, 2), IR(27961, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpLine, false, false, IR(52, 3), IR(27968, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpExtension, false, false, IR(11, 1), IR(27973, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpExtInstImport, true, false, IR(50, 2), IR(27983, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpExtInst, true, true, IR(55, 4), IR(28043, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpMemoryModel, false, false, IR(59, 2), IR(28115, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpEntryPoint, false, false, IR(61, 4), IR(28189, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpExecutionMode, false, false, IR(65, 2), IR(28232, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpCapability, false, false, IR(67, 1), IR(28274, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpTypeVoid, true, false, IR(68, 1), IR(28285, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeBool, true, false, IR(68, 1), IR(28294, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeInt, true, false, IR(69, 3), IR(28303, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeFloat, true, false, IR(72, 3), IR(28348, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeVector, true, false, IR(75, 3), IR(28358, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeMatrix, true, false, IR(75, 3), IR(28369, 11), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeImage, true, false, IR(78, 9), IR(28493, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeSampler, true, false, IR(68, 1), IR(28503, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeSampledImage, true, false, IR(87, 2), IR(28515, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeArray, true, false, IR(89, 3), IR(28532, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeRuntimeArray, true, false, IR(87, 2), IR(28542, 17), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeStruct, true, false, IR(92, 2), IR(28559, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeOpaque, true, false, IR(50, 2), IR(28570, 11), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypePointer, true, false, IR(94, 3), IR(28612, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeFunction, true, false, IR(97, 3), IR(28624, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeEvent, true, false, IR(68, 1), IR(28637, 10), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeDeviceEvent, true, false, IR(68, 1), IR(28647, 16), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeReserveId, true, false, IR(68, 1), IR(28663, 14), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeQueue, true, false, IR(68, 1), IR(28677, 10), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypePipe, true, false, IR(100, 2), IR(28687, 9), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeForwardPointer, false, false, IR(102, 2), IR(28696, 19), IR(0, 0), IR(206, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantTrue, true, true, IR(39, 2), IR(28715, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantFalse, true, true, IR(39, 2), IR(28728, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstant, true, true, IR(104, 3), IR(16787, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantComposite, true, true, IR(107, 3), IR(28780, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantSampler, true, true, IR(110, 5), IR(28876, 16), IR(0, 0), IR(208, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantNull, true, true, IR(39, 2), IR(28892, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantTrue, true, true, IR(39, 2), IR(28905, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantFalse, true, true, IR(39, 2), IR(28922, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstant, true, true, IR(104, 3), IR(28940, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantComposite, true, true, IR(107, 3), IR(28953, 22), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantOp, true, true, IR(115, 3), IR(29016, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpFunction, true, true, IR(118, 4), IR(27039, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionParameter, true, true, IR(39, 2), IR(29065, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionEnd, false, false, IR(0, 0), IR(29083, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionCall, true, true, IR(122, 4), IR(29095, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpVariable, true, true, IR(126, 4), IR(29108, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpImageTexelPointer, true, true, IR(130, 5), IR(29117, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpLoad, true, true, IR(135, 4), IR(29175, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpStore, false, false, IR(139, 3), IR(29180, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCopyMemory, false, false, IR(142, 4), IR(29186, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCopyMemorySized, false, false, IR(146, 5), IR(29197, 16), IR(0, 0), IR(209, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpAccessChain, true, true, IR(122, 4), IR(29213, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpInBoundsAccessChain, true, true, IR(122, 4), IR(29225, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrAccessChain, true, true, IR(151, 5), IR(29245, 15), IR(0, 0), IR(211, 4), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpArrayLength, true, true, IR(156, 4), IR(29260, 12), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpGenericPtrMemSemantics, true, true, IR(160, 3), IR(29272, 23), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpInBoundsPtrAccessChain, true, true, IR(151, 5), IR(29295, 23), IR(0, 0), IR(1, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpDecorate, false, false, IR(163, 2), IR(29346, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpMemberDecorate, false, false, IR(165, 3), IR(29355, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpDecorationGroup, true, false, IR(68, 1), IR(29370, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupDecorate, false, false, IR(168, 2), IR(29386, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupMemberDecorate, false, false, IR(170, 2), IR(29445, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpVectorExtractDynamic, true, true, IR(172, 4), IR(29465, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpVectorInsertDynamic, true, true, IR(130, 5), IR(29486, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpVectorShuffle, true, true, IR(176, 5), IR(29506, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeConstruct, true, true, IR(107, 3), IR(29520, 19), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeExtract, true, true, IR(181, 4), IR(29539, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeInsert, true, true, IR(176, 5), IR(29556, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCopyObject, true, true, IR(160, 3), IR(29572, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpTranspose, true, true, IR(160, 3), IR(29583, 10), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpSampledImage, true, true, IR(172, 4), IR(29593, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleImplicitLod, true, true, IR(185, 5), IR(29638, 23), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleExplicitLod, true, true, IR(190, 5), IR(29684, 23), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleDrefImplicitLod, true, true, IR(195, 6), IR(29707, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleDrefExplicitLod, true, true, IR(201, 6), IR(29734, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjImplicitLod, true, true, IR(185, 5), IR(29761, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjExplicitLod, true, true, IR(190, 5), IR(29788, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjDrefImplicitLod, true, true, IR(195, 6), IR(29815, 31), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjDrefExplicitLod, true, true, IR(201, 6), IR(29846, 31), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageFetch, true, true, IR(185, 5), IR(29877, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageGather, true, true, IR(195, 6), IR(29888, 12), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageDrefGather, true, true, IR(195, 6), IR(29900, 16), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageRead, true, true, IR(185, 5), IR(29916, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageWrite, false, false, IR(207, 4), IR(29926, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImage, true, true, IR(160, 3), IR(27083, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryFormat, true, true, IR(160, 3), IR(29937, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryOrder, true, true, IR(160, 3), IR(29954, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySizeLod, true, true, IR(172, 4), IR(29970, 18), IR(0, 0), IR(215, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySize, true, true, IR(160, 3), IR(29988, 15), IR(0, 0), IR(215, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryLod, true, true, IR(172, 4), IR(30003, 14), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryLevels, true, true, IR(160, 3), IR(30017, 17), IR(0, 0), IR(215, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySamples, true, true, IR(160, 3), IR(30034, 18), IR(0, 0), IR(215, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertFToU, true, true, IR(160, 3), IR(30052, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertFToS, true, true, IR(160, 3), IR(30064, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertSToF, true, true, IR(160, 3), IR(30076, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToF, true, true, IR(160, 3), IR(30088, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpUConvert, true, true, IR(160, 3), IR(30100, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSConvert, true, true, IR(160, 3), IR(30109, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpFConvert, true, true, IR(160, 3), IR(30118, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpQuantizeToF16, true, true, IR(160, 3), IR(30127, 14), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertPtrToU, true, true, IR(160, 3), IR(30141, 14), IR(0, 0), IR(206, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSatConvertSToU, true, true, IR(160, 3), IR(30155, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSatConvertUToS, true, true, IR(160, 3), IR(30170, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToPtr, true, true, IR(160, 3), IR(30185, 14), IR(0, 0), IR(206, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpPtrCastToGeneric, true, true, IR(160, 3), IR(30199, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpGenericCastToPtr, true, true, IR(160, 3), IR(30216, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpGenericCastToPtrExplicit, true, true, IR(211, 4), IR(30233, 25), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpBitcast, true, true, IR(160, 3), IR(30258, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSNegate, true, true, IR(160, 3), IR(30266, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFNegate, true, true, IR(160, 3), IR(30274, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIAdd, true, true, IR(172, 4), IR(30282, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFAdd, true, true, IR(172, 4), IR(30287, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpISub, true, true, IR(172, 4), IR(30292, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFSub, true, true, IR(172, 4), IR(30297, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIMul, true, true, IR(172, 4), IR(30302, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFMul, true, true, IR(172, 4), IR(30307, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDiv, true, true, IR(172, 4), IR(30312, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSDiv, true, true, IR(172, 4), IR(30317, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFDiv, true, true, IR(172, 4), IR(30322, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUMod, true, true, IR(172, 4), IR(30327, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSRem, true, true, IR(172, 4), IR(30332, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSMod, true, true, IR(172, 4), IR(30337, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFRem, true, true, IR(172, 4), IR(30342, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFMod, true, true, IR(172, 4), IR(30347, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpVectorTimesScalar, true, true, IR(172, 4), IR(30352, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesScalar, true, true, IR(172, 4), IR(30370, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpVectorTimesMatrix, true, true, IR(172, 4), IR(30388, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesVector, true, true, IR(172, 4), IR(30406, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesMatrix, true, true, IR(172, 4), IR(30424, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpOuterProduct, true, true, IR(172, 4), IR(30442, 13), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpDot, true, true, IR(172, 4), IR(30455, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIAddCarry, true, true, IR(172, 4), IR(30459, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpISubBorrow, true, true, IR(172, 4), IR(30469, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUMulExtended, true, true, IR(172, 4), IR(30480, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSMulExtended, true, true, IR(172, 4), IR(30493, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpAny, true, true, IR(160, 3), IR(30506, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpAll, true, true, IR(160, 3), IR(30510, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsNan, true, true, IR(160, 3), IR(30514, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsInf, true, true, IR(160, 3), IR(30520, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsFinite, true, true, IR(160, 3), IR(30526, 9), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsNormal, true, true, IR(160, 3), IR(30535, 9), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSignBitSet, true, true, IR(160, 3), IR(30544, 11), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLessOrGreater, true, true, IR(172, 4), IR(30555, 14), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), SPV_SPIRV_VERSION_WORD(1,5), PrintingClass::kRelational_and_Logical},
  {spv::Op::OpOrdered, true, true, IR(172, 4), IR(30569, 8), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUnordered, true, true, IR(172, 4), IR(30577, 10), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalEqual, true, true, IR(172, 4), IR(30587, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalNotEqual, true, true, IR(172, 4), IR(30600, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalOr, true, true, IR(172, 4), IR(30616, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalAnd, true, true, IR(172, 4), IR(30626, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalNot, true, true, IR(160, 3), IR(30637, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSelect, true, true, IR(130, 5), IR(30648, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIEqual, true, true, IR(172, 4), IR(30655, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpINotEqual, true, true, IR(172, 4), IR(30662, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUGreaterThan, true, true, IR(172, 4), IR(30672, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSGreaterThan, true, true, IR(172, 4), IR(30685, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUGreaterThanEqual, true, true, IR(172, 4), IR(30698, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSGreaterThanEqual, true, true, IR(172, 4), IR(30716, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpULessThan, true, true, IR(172, 4), IR(30734, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSLessThan, true, true, IR(172, 4), IR(30744, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpULessThanEqual, true, true, IR(172, 4), IR(30754, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSLessThanEqual, true, true, IR(172, 4), IR(30769, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdEqual, true, true, IR(172, 4), IR(30784, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordEqual, true, true, IR(172, 4), IR(30794, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdNotEqual, true, true, IR(172, 4), IR(30806, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordNotEqual, true, true, IR(172, 4), IR(30819, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdLessThan, true, true, IR(172, 4), IR(30834, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordLessThan, true, true, IR(172, 4), IR(30847, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdGreaterThan, true, true, IR(172, 4), IR(30862, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordGreaterThan, true, true, IR(172, 4), IR(30878, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdLessThanEqual, true, true, IR(172, 4), IR(30896, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordLessThanEqual, true, true, IR(172, 4), IR(30914, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdGreaterThanEqual, true, true, IR(172, 4), IR(30934, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordGreaterThanEqual, true, true, IR(172, 4), IR(30955, 23), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpShiftRightLogical, true, true, IR(172, 4), IR(30978, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpShiftRightArithmetic, true, true, IR(172, 4), IR(30996, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpShiftLeftLogical, true, true, IR(172, 4), IR(31017, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseOr, true, true, IR(172, 4), IR(31034, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseXor, true, true, IR(172, 4), IR(31044, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseAnd, true, true, IR(172, 4), IR(31055, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpNot, true, true, IR(160, 3), IR(31066, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldInsert, true, true, IR(215, 6), IR(31070, 15), IR(0, 0), IR(218, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldSExtract, true, true, IR(130, 5), IR(31085, 17), IR(0, 0), IR(218, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldUExtract, true, true, IR(130, 5), IR(31102, 17), IR(0, 0), IR(218, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitReverse, true, true, IR(160, 3), IR(31119, 11), IR(0, 0), IR(218, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitCount, true, true, IR(160, 3), IR(31130, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpDPdx, true, true, IR(160, 3), IR(31139, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdy, true, true, IR(160, 3), IR(31144, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidth, true, true, IR(160, 3), IR(31149, 7), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdxFine, true, true, IR(160, 3), IR(31156, 9), IR(0, 0), IR(220, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdyFine, true, true, IR(160, 3), IR(31165, 9), IR(0, 0), IR(220, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidthFine, true, true, IR(160, 3), IR(31174, 11), IR(0, 0), IR(220, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdxCoarse, true, true, IR(160, 3), IR(31185, 11), IR(0, 0), IR(220, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdyCoarse, true, true, IR(160, 3), IR(31196, 11), IR(0, 0), IR(220, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidthCoarse, true, true, IR(160, 3), IR(31207, 13), IR(0, 0), IR(220, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpEmitVertex, false, false, IR(0, 0), IR(31220, 11), IR(0, 0), IR(69, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEndPrimitive, false, false, IR(0, 0), IR(31231, 13), IR(0, 0), IR(69, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEmitStreamVertex, false, false, IR(10, 1), IR(31244, 17), IR(0, 0), IR(117, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEndStreamPrimitive, false, false, IR(10, 1), IR(31261, 19), IR(0, 0), IR(117, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpControlBarrier, false, false, IR(221, 3), IR(31317, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpMemoryBarrier, false, false, IR(224, 2), IR(31332, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpAtomicLoad, true, true, IR(226, 5), IR(31346, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicStore, false, false, IR(231, 4), IR(31357, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicExchange, true, true, IR(235, 6), IR(31369, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicCompareExchange, true, true, IR(241, 8), IR(31384, 22), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicCompareExchangeWeak, true, true, IR(241, 8), IR(31406, 26), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), SPV_SPIRV_VERSION_WORD(1,3), PrintingClass::kAtomic},
  {spv::Op::OpAtomicIIncrement, true, true, IR(226, 5), IR(31432, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicIDecrement, true, true, IR(226, 5), IR(31449, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicIAdd, true, true, IR(235, 6), IR(31466, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicISub, true, true, IR(235, 6), IR(31477, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicSMin, true, true, IR(235, 6), IR(31488, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicUMin, true, true, IR(235, 6), IR(31499, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicSMax, true, true, IR(235, 6), IR(31510, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicUMax, true, true, IR(235, 6), IR(31521, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicAnd, true, true, IR(235, 6), IR(31532, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicOr, true, true, IR(235, 6), IR(31542, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicXor, true, true, IR(235, 6), IR(31551, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpPhi, true, true, IR(107, 3), IR(31561, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLoopMerge, false, false, IR(249, 3), IR(31595, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpSelectionMerge, false, false, IR(252, 2), IR(31640, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLabel, true, false, IR(68, 1), IR(31655, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpBranch, false, false, IR(10, 1), IR(31661, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpBranchConditional, false, false, IR(254, 4), IR(31668, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpSwitch, false, false, IR(258, 3), IR(31731, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpKill, false, false, IR(0, 0), IR(31738, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpReturn, false, false, IR(0, 0), IR(31743, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpReturnValue, false, false, IR(10, 1), IR(31750, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpUnreachable, false, false, IR(0, 0), IR(31762, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLifetimeStart, false, false, IR(261, 2), IR(31774, 14), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLifetimeStop, false, false, IR(261, 2), IR(31788, 13), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpGroupAsyncCopy, true, true, IR(263, 8), IR(31801, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupWaitEvents, false, false, IR(271, 3), IR(31816, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupAll, true, true, IR(274, 4), IR(31832, 9), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupAny, true, true, IR(274, 4), IR(31841, 9), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBroadcast, true, true, IR(278, 5), IR(31850, 15), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupIAdd, true, true, IR(283, 5), IR(31898, 10), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFAdd, true, true, IR(283, 5), IR(31908, 10), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMin, true, true, IR(283, 5), IR(31918, 10), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMin, true, true, IR(283, 5), IR(31928, 10), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMin, true, true, IR(283, 5), IR(31938, 10), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMax, true, true, IR(283, 5), IR(31948, 10), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMax, true, true, IR(283, 5), IR(31958, 10), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMax, true, true, IR(283, 5), IR(31968, 10), IR(0, 0), IR(221, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpReadPipe, true, true, IR(215, 6), IR(31978, 9), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpWritePipe, true, true, IR(215, 6), IR(31987, 10), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReservedReadPipe, true, true, IR(288, 8), IR(31997, 17), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReservedWritePipe, true, true, IR(288, 8), IR(32014, 18), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReserveReadPipePackets, true, true, IR(215, 6), IR(32032, 23), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReserveWritePipePackets, true, true, IR(215, 6), IR(32055, 24), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCommitReadPipe, false, false, IR(296, 4), IR(32079, 15), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCommitWritePipe, false, false, IR(296, 4), IR(32094, 16), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpIsValidReserveId, true, true, IR(160, 3), IR(32110, 17), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetNumPipePackets, true, true, IR(130, 5), IR(32127, 18), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetMaxPipePackets, true, true, IR(130, 5), IR(32145, 18), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupReserveReadPipePackets, true, true, IR(300, 7), IR(32163, 28), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupReserveWritePipePackets, true, true, IR(300, 7), IR(32191, 29), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupCommitReadPipe, false, false, IR(307, 5), IR(32220, 20), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupCommitWritePipe, false, false, IR(307, 5), IR(32240, 21), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpEnqueueMarker, true, true, IR(215, 6), IR(32261, 14), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpEnqueueKernel, true, true, IR(312, 13), IR(32275, 14), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelNDrangeSubGroupCount, true, true, IR(325, 7), IR(32289, 30), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelNDrangeMaxSubGroupSize, true, true, IR(325, 7), IR(32319, 32), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelWorkGroupSize, true, true, IR(215, 6), IR(32351, 23), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelPreferredWorkGroupSizeMultiple, true, true, IR(215, 6), IR(32374, 40), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpRetainEvent, false, false, IR(10, 1), IR(32414, 12), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpReleaseEvent, false, false, IR(10, 1), IR(32426, 13), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpCreateUserEvent, true, true, IR(39, 2), IR(32439, 16), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpIsValidEvent, true, true, IR(160, 3), IR(32455, 13), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpSetUserEventStatus, false, false, IR(36, 2), IR(32468, 19), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpCaptureEventProfilingInfo, false, false, IR(33, 3), IR(32487, 26), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetDefaultQueue, true, true, IR(39, 2), IR(32513, 16), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpBuildNDRange, true, true, IR(130, 5), IR(32529, 13), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpImageSparseSampleImplicitLod, true, true, IR(185, 5), IR(32542, 29), IR(0, 0), IR(222, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleExplicitLod, true, true, IR(190, 5), IR(32571, 29), IR(0, 0), IR(222, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleDrefImplicitLod, true, true, IR(195, 6), IR(32600, 33), IR(0, 0), IR(222, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleDrefExplicitLod, true, true, IR(201, 6), IR(32633, 33), IR(0, 0), IR(222, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjImplicitLod, true, true, IR(185, 5), IR(32666, 33), IR(0, 0), IR(222, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjExplicitLod, true, true, IR(190, 5), IR(32699, 33), IR(0, 0), IR(222, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjDrefImplicitLod, true, true, IR(195, 6), IR(32732, 37), IR(0, 0), IR(222, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjDrefExplicitLod, true, true, IR(201, 6), IR(32769, 37), IR(0, 0), IR(222, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseFetch, true, true, IR(185, 5), IR(32806, 17), IR(0, 0), IR(222, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseGather, true, true, IR(195, 6), IR(32823, 18), IR(0, 0), IR(222, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseDrefGather, true, true, IR(195, 6), IR(32841, 22), IR(0, 0), IR(222, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseTexelsResident, true, true, IR(160, 3), IR(32863, 26), IR(0, 0), IR(222, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpNoLine, false, false, IR(0, 0), IR(32889, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpAtomicFlagTestAndSet, true, true, IR(226, 5), IR(32896, 21), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicFlagClear, false, false, IR(332, 3), IR(32917, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpImageSparseRead, true, true, IR(185, 5), IR(32933, 16), IR(0, 0), IR(222, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpSizeOf, true, true, IR(160, 3), IR(32949, 7), IR(0, 0), IR(1, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpTypePipeStorage, true, false, IR(68, 1), IR(32956, 16), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantPipeStorage, true, true, IR(335, 5), IR(32972, 20), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCreatePipeFromPipeStorage, true, true, IR(160, 3), IR(32992, 26), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetKernelLocalSizeForSubgroupCount, true, true, IR(325, 7), IR(33018, 35), IR(0, 0), IR(157, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelMaxNumSubgroups, true, true, IR(215, 6), IR(33053, 25), IR(0, 0), IR(157, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpTypeNamedBarrier, true, false, IR(68, 1), IR(33078, 17), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpNamedBarrierInitialize, true, true, IR(160, 3), IR(33095, 23), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpMemoryNamedBarrier, false, false, IR(332, 3), IR(33118, 19), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpModuleProcessed, false, false, IR(11, 1), IR(33137, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpExecutionModeId, false, false, IR(65, 2), IR(33153, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,2), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpDecorateId, false, false, IR(163, 2), IR(33169, 11), IR(0, 0), IR(1, 0), IR(180, 1), SPV_SPIRV_VERSION_WORD(1,2), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupNonUniformElect, true, true, IR(340, 3), IR(33180, 21), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAll, true, true, IR(274, 4), IR(33201, 19), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAny, true, true, IR(274, 4), IR(33220, 19), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAllEqual, true, true, IR(274, 4), IR(33239, 24), IR(0, 0), IR(225, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBroadcast, true, true, IR(278, 5), IR(33263, 25), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBroadcastFirst, true, true, IR(274, 4), IR(33288, 30), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallot, true, true, IR(274, 4), IR(6377, 22), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformInverseBallot, true, true, IR(274, 4), IR(33318, 29), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotBitExtract, true, true, IR(278, 5), IR(33347, 32), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotBitCount, true, true, IR(283, 5), IR(33379, 30), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotFindLSB, true, true, IR(274, 4), IR(33409, 29), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotFindMSB, true, true, IR(274, 4), IR(33438, 29), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffle, true, true, IR(278, 5), IR(9467, 23), IR(0, 0), IR(227, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleXor, true, true, IR(278, 5), IR(33467, 26), IR(0, 0), IR(227, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleUp, true, true, IR(278, 5), IR(33493, 25), IR(0, 0), IR(228, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleDown, true, true, IR(278, 5), IR(33518, 27), IR(0, 0), IR(228, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformIAdd, true, true, IR(343, 6), IR(33545, 20), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFAdd, true, true, IR(343, 6), IR(33565, 20), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformIMul, true, true, IR(343, 6), IR(33585, 20), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMul, true, true, IR(343, 6), IR(33605, 20), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformSMin, true, true, IR(343, 6), IR(33625, 20), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformUMin, true, true, IR(343, 6), IR(33645, 20), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMin, true, true, IR(343, 6), IR(33665, 20), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformSMax, true, true, IR(343, 6), IR(33685, 20), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformUMax, true, true, IR(343, 6), IR(33705, 20), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMax, true, true, IR(343, 6), IR(33725, 20), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseAnd, true, true, IR(343, 6), IR(33745, 26), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseOr, true, true, IR(343, 6), IR(33771, 25), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseXor, true, true, IR(343, 6), IR(33796, 26), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalAnd, true, true, IR(343, 6), IR(33822, 26), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalOr, true, true, IR(343, 6), IR(33848, 25), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalXor, true, true, IR(343, 6), IR(33873, 26), IR(0, 0), IR(229, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadBroadcast, true, true, IR(278, 5), IR(33899, 29), IR(0, 0), IR(232, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadSwap, true, true, IR(278, 5), IR(33928, 24), IR(0, 0), IR(232, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpCopyLogical, true, true, IR(160, 3), IR(33952, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpPtrEqual, true, true, IR(172, 4), IR(33964, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrNotEqual, true, true, IR(172, 4), IR(33973, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrDiff, true, true, IR(172, 4), IR(33985, 8), IR(0, 0), IR(233, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpColorAttachmentReadEXT, true, true, IR(349, 4), IR(33993, 23), IR(0, 0), IR(149, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpDepthAttachmentReadEXT, true, true, IR(353, 3), IR(34016, 23), IR(0, 0), IR(158, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpStencilAttachmentReadEXT, true, true, IR(353, 3), IR(34039, 25), IR(0, 0), IR(159, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpTypeTensorARM, true, false, IR(356, 4), IR(34064, 14), IR(0, 0), IR(205, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTensorReadARM, true, true, IR(360, 5), IR(34120, 14), IR(0, 0), IR(205, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpTensorWriteARM, false, false, IR(365, 4), IR(34134, 15), IR(0, 0), IR(205, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpTensorQuerySizeARM, true, true, IR(172, 4), IR(34149, 19), IR(0, 0), IR(205, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpGraphConstantARM, true, true, IR(369, 3), IR(34168, 17), IR(0, 0), IR(236, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphEntryPointARM, false, false, IR(372, 3), IR(34185, 19), IR(0, 0), IR(236, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphARM, true, true, IR(39, 2), IR(9758, 9), IR(0, 0), IR(236, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphInputARM, true, true, IR(122, 4), IR(34204, 14), IR(0, 0), IR(236, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphSetOutputARM, false, false, IR(375, 3), IR(34218, 18), IR(0, 0), IR(236, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphEndARM, false, false, IR(0, 0), IR(34236, 12), IR(0, 0), IR(236, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpTypeGraphARM, true, false, IR(378, 3), IR(34248, 13), IR(0, 0), IR(236, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTerminateInvocation, false, false, IR(0, 0), IR(34261, 20), IR(0, 0), IR(3, 1), IR(190, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpTypeUntypedPointerKHR, true, false, IR(381, 2), IR(34281, 22), IR(0, 0), IR(237, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpUntypedVariableKHR, true, true, IR(383, 5), IR(34303, 19), IR(0, 0), IR(237, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedAccessChainKHR, true, true, IR(151, 5), IR(34322, 22), IR(0, 0), IR(237, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedInBoundsAccessChainKHR, true, true, IR(151, 5), IR(34344, 30), IR(0, 0), IR(237, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpSubgroupBallotKHR, true, true, IR(160, 3), IR(6138, 18), IR(0, 0), IR(238, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupFirstInvocationKHR, true, true, IR(160, 3), IR(34374, 27), IR(0, 0), IR(238, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpUntypedPtrAccessChainKHR, true, true, IR(388, 6), IR(34401, 25), IR(0, 0), IR(237, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedInBoundsPtrAccessChainKHR, true, true, IR(388, 6), IR(34426, 33), IR(0, 0), IR(237, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedArrayLengthKHR, true, true, IR(394, 5), IR(34459, 22), IR(0, 0), IR(237, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedPrefetchKHR, false, false, IR(399, 5), IR(34481, 19), IR(0, 0), IR(237, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpFmaKHR, true, true, IR(130, 5), IR(34500, 7), IR(0, 0), IR(239, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSubgroupAllKHR, true, true, IR(160, 3), IR(34507, 15), IR(0, 0), IR(240, 1), IR(41, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupAnyKHR, true, true, IR(160, 3), IR(34522, 15), IR(0, 0), IR(240, 1), IR(41, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupAllEqualKHR, true, true, IR(160, 3), IR(34537, 20), IR(0, 0), IR(240, 1), IR(41, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupNonUniformRotateKHR, true, true, IR(404, 6), IR(14440, 25), IR(0, 0), IR(241, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupReadInvocationKHR, true, true, IR(172, 4), IR(34557, 26), IR(0, 0), IR(238, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpExtInstWithForwardRefsKHR, true, true, IR(410, 5), IR(34583, 26), IR(0, 0), IR(1, 0), IR(191, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpUntypedGroupAsyncCopyKHR, true, true, IR(415, 11), IR(34609, 25), IR(0, 0), IR(237, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpTraceRayKHR, false, false, IR(426, 11), IR(34634, 12), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpExecuteCallableKHR, false, false, IR(36, 2), IR(34646, 19), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToAccelerationStructureKHR, true, true, IR(160, 3), IR(34665, 35), IR(0, 0), IR(242, 2), IR(192, 2), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIgnoreIntersectionKHR, false, false, IR(0, 0), IR(34700, 22), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTerminateRayKHR, false, false, IR(0, 0), IR(34722, 16), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSDot, true, true, IR(437, 5), IR(34785, 5), IR(167, 1), IR(244, 1), IR(140, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDot, true, true, IR(437, 5), IR(34798, 5), IR(168, 1), IR(244, 1), IR(140, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSUDot, true, true, IR(437, 5), IR(34811, 6), IR(169, 1), IR(244, 1), IR(140, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSDotAccSat, true, true, IR(442, 6), IR(34826, 11), IR(170, 1), IR(244, 1), IR(140, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDotAccSat, true, true, IR(442, 6), IR(34851, 11), IR(171, 1), IR(244, 1), IR(140, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSUDotAccSat, true, true, IR(442, 6), IR(34876, 12), IR(172, 1), IR(244, 1), IR(140, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpTypeCooperativeMatrixKHR, true, false, IR(448, 6), IR(34903, 25), IR(0, 0), IR(86, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeMatrixLoadKHR, true, true, IR(454, 6), IR(34928, 25), IR(0, 0), IR(86, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixStoreKHR, false, false, IR(460, 5), IR(34953, 26), IR(0, 0), IR(86, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixMulAddKHR, true, true, IR(465, 6), IR(35033, 27), IR(0, 0), IR(86, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpCooperativeMatrixLengthKHR, true, true, IR(160, 3), IR(35060, 27), IR(0, 0), IR(86, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpConstantCompositeReplicateEXT, true, true, IR(160, 3), IR(35087, 30), IR(0, 0), IR(245, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCompositeReplicateEXT, true, true, IR(160, 3), IR(35117, 34), IR(0, 0), IR(245, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpCompositeConstructReplicateEXT, true, true, IR(160, 3), IR(35151, 31), IR(0, 0), IR(245, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpTypeRayQueryKHR, true, false, IR(68, 1), IR(35182, 16), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpRayQueryInitializeKHR, false, false, IR(471, 8), IR(35198, 22), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryTerminateKHR, false, false, IR(10, 1), IR(35220, 21), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGenerateIntersectionKHR, false, false, IR(36, 2), IR(35241, 32), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryConfirmIntersectionKHR, false, false, IR(10, 1), IR(35273, 31), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryProceedKHR, true, true, IR(160, 3), IR(35304, 19), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTypeKHR, true, true, IR(172, 4), IR(35323, 31), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpImageSampleWeightedQCOM, true, true, IR(130, 5), IR(35354, 24), IR(0, 0), IR(246, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBoxFilterQCOM, true, true, IR(130, 5), IR(35378, 19), IR(0, 0), IR(247, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchSSDQCOM, true, true, IR(325, 7), IR(35397, 23), IR(0, 0), IR(248, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchSADQCOM, true, true, IR(325, 7), IR(35420, 23), IR(0, 0), IR(248, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpBitCastArrayQCOM, true, true, IR(160, 3), IR(35443, 17), IR(0, 0), IR(249, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpImageBlockMatchWindowSSDQCOM, true, true, IR(325, 7), IR(35460, 29), IR(0, 0), IR(250, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchWindowSADQCOM, true, true, IR(325, 7), IR(35489, 29), IR(0, 0), IR(250, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchGatherSSDQCOM, true, true, IR(325, 7), IR(35518, 29), IR(0, 0), IR(250, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchGatherSADQCOM, true, true, IR(325, 7), IR(35547, 29), IR(0, 0), IR(250, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpCompositeConstructCoopMatQCOM, true, true, IR(160, 3), IR(35576, 30), IR(0, 0), IR(249, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeExtractCoopMatQCOM, true, true, IR(160, 3), IR(35606, 28), IR(0, 0), IR(249, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpExtractSubArrayQCOM, true, true, IR(172, 4), IR(35634, 20), IR(0, 0), IR(249, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpGroupIAddNonUniformAMD, true, true, IR(283, 5), IR(35654, 23), IR(0, 0), IR(221, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFAddNonUniformAMD, true, true, IR(283, 5), IR(35677, 23), IR(0, 0), IR(221, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMinNonUniformAMD, true, true, IR(283, 5), IR(35700, 23), IR(0, 0), IR(221, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMinNonUniformAMD, true, true, IR(283, 5), IR(35723, 23), IR(0, 0), IR(221, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMinNonUniformAMD, true, true, IR(283, 5), IR(35746, 23), IR(0, 0), IR(221, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMaxNonUniformAMD, true, true, IR(283, 5), IR(35769, 23), IR(0, 0), IR(221, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMaxNonUniformAMD, true, true, IR(283, 5), IR(35792, 23), IR(0, 0), IR(221, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMaxNonUniformAMD, true, true, IR(283, 5), IR(35815, 23), IR(0, 0), IR(221, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpFragmentMaskFetchAMD, true, true, IR(172, 4), IR(35838, 21), IR(0, 0), IR(251, 1), IR(58, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFragmentFetchAMD, true, true, IR(130, 5), IR(35859, 17), IR(0, 0), IR(251, 1), IR(58, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReadClockKHR, true, true, IR(340, 3), IR(35876, 13), IR(0, 0), IR(252, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAllocateNodePayloadsAMDX, true, true, IR(278, 5), IR(35889, 25), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpEnqueueNodePayloadsAMDX, false, false, IR(10, 1), IR(35914, 24), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeNodePayloadArrayAMDX, true, false, IR(87, 2), IR(35938, 25), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFinishWritingNodePayloadAMDX, true, true, IR(160, 3), IR(35963, 29), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpNodePayloadArrayLengthAMDX, true, true, IR(160, 3), IR(35992, 27), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIsNodePayloadValidAMDX, true, true, IR(172, 4), IR(36019, 23), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConstantStringAMDX, true, false, IR(50, 2), IR(36042, 19), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSpecConstantStringAMDX, true, false, IR(50, 2), IR(36061, 23), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpGroupNonUniformQuadAllKHR, true, true, IR(160, 3), IR(36084, 26), IR(0, 0), IR(166, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadAnyKHR, true, true, IR(160, 3), IR(36110, 26), IR(0, 0), IR(166, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpHitObjectRecordHitMotionNV, false, false, IR(479, 14), IR(36136, 27), IR(0, 0), IR(253, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitWithIndexMotionNV, false, false, IR(493, 13), IR(36163, 36), IR(0, 0), IR(253, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissMotionNV, false, false, IR(506, 7), IR(36199, 28), IR(0, 0), IR(253, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldToObjectNV, true, true, IR(160, 3), IR(36227, 28), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectToWorldNV, true, true, IR(160, 3), IR(36255, 28), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayDirectionNV, true, true, IR(160, 3), IR(36283, 33), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayOriginNV, true, true, IR(160, 3), IR(36316, 30), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayMotionNV, false, false, IR(493, 13), IR(36346, 26), IR(0, 0), IR(253, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderRecordBufferHandleNV, true, true, IR(160, 3), IR(36372, 39), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderBindingTableRecordIndexNV, true, true, IR(160, 3), IR(36411, 44), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordEmptyNV, false, false, IR(10, 1), IR(36455, 23), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayNV, false, false, IR(513, 12), IR(36478, 20), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitNV, false, false, IR(493, 13), IR(36498, 21), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitWithIndexNV, false, false, IR(513, 12), IR(36519, 30), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissNV, false, false, IR(525, 6), IR(36549, 22), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectExecuteShaderNV, false, false, IR(36, 2), IR(36571, 25), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetCurrentTimeNV, true, true, IR(160, 3), IR(36596, 26), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetAttributesNV, false, false, IR(36, 2), IR(36622, 25), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetHitKindNV, true, true, IR(160, 3), IR(36647, 22), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetPrimitiveIndexNV, true, true, IR(160, 3), IR(36669, 29), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetGeometryIndexNV, true, true, IR(160, 3), IR(36698, 28), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceIdNV, true, true, IR(160, 3), IR(36726, 25), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceCustomIndexNV, true, true, IR(160, 3), IR(36751, 34), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayDirectionNV, true, true, IR(160, 3), IR(36785, 32), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayOriginNV, true, true, IR(160, 3), IR(36817, 29), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMaxNV, true, true, IR(160, 3), IR(36846, 22), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMinNV, true, true, IR(160, 3), IR(36868, 22), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsEmptyNV, true, true, IR(160, 3), IR(36890, 19), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsHitNV, true, true, IR(160, 3), IR(36909, 17), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsMissNV, true, true, IR(160, 3), IR(36926, 18), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHitObjectNV, false, false, IR(531, 3), IR(36944, 29), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHintNV, false, false, IR(36, 2), IR(36973, 24), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeHitObjectNV, true, false, IR(68, 1), IR(36997, 16), IR(0, 0), IR(127, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpImageSampleFootprintNV, true, true, IR(534, 7), IR(37013, 23), IR(0, 0), IR(255, 1), IR(72, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpTypeCooperativeVectorNV, true, false, IR(89, 3), IR(37036, 24), IR(0, 0), IR(256, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeVectorMatrixMulNV, true, true, IR(541, 13), IR(37060, 29), IR(0, 0), IR(256, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorOuterProductAccumulateNV, false, false, IR(554, 7), IR(37089, 42), IR(0, 0), IR(257, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorReduceSumAccumulateNV, false, false, IR(33, 3), IR(37131, 39), IR(0, 0), IR(257, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorMatrixMulAddNV, true, true, IR(561, 16), IR(37170, 32), IR(0, 0), IR(256, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixConvertNV, true, true, IR(160, 3), IR(37202, 27), IR(0, 0), IR(258, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpEmitMeshTasksEXT, false, false, IR(577, 4), IR(37229, 17), IR(0, 0), IR(53, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSetMeshOutputsEXT, false, false, IR(36, 2), IR(37246, 18), IR(0, 0), IR(53, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpGroupNonUniformPartitionNV, true, true, IR(160, 3), IR(37264, 27), IR(0, 0), IR(186, 1), IR(75, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpWritePackedPrimitiveIndices4x8NV, false, false, IR(36, 2), IR(37291, 33), IR(0, 0), IR(50, 1), IR(18, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFetchMicroTriangleVertexPositionNV, true, true, IR(325, 7), IR(37324, 35), IR(0, 0), IR(259, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFetchMicroTriangleVertexBarycentricNV, true, true, IR(325, 7), IR(37359, 38), IR(0, 0), IR(259, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorLoadNV, true, true, IR(581, 5), IR(37397, 24), IR(0, 0), IR(256, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeVectorStoreNV, false, false, IR(586, 4), IR(37421, 25), IR(0, 0), IR(256, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpHitObjectRecordFromQueryEXT, false, false, IR(296, 4), IR(37446, 28), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissEXT, false, false, IR(506, 7), IR(37474, 23), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissMotionEXT, false, false, IR(471, 8), IR(37497, 29), IR(0, 0), IR(260, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetIntersectionTriangleVertexPositionsEXT, true, true, IR(160, 3), IR(37526, 51), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayFlagsEXT, true, true, IR(160, 3), IR(37577, 24), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectSetShaderBindingTableRecordIndexEXT, false, false, IR(36, 2), IR(37601, 45), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectReorderExecuteShaderEXT, false, false, IR(590, 4), IR(37646, 33), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceReorderExecuteEXT, false, false, IR(594, 14), IR(37679, 32), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceMotionReorderExecuteEXT, false, false, IR(608, 15), IR(37711, 38), IR(0, 0), IR(260, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeHitObjectEXT, true, false, IR(68, 1), IR(37749, 17), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpReorderThreadWithHintEXT, false, false, IR(36, 2), IR(37766, 25), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHitObjectEXT, false, false, IR(531, 3), IR(37791, 30), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayEXT, false, false, IR(513, 12), IR(37821, 21), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayMotionEXT, false, false, IR(493, 13), IR(37842, 27), IR(0, 0), IR(260, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordEmptyEXT, false, false, IR(10, 1), IR(37869, 24), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectExecuteShaderEXT, false, false, IR(36, 2), IR(37893, 26), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetCurrentTimeEXT, true, true, IR(160, 3), IR(37919, 27), IR(0, 0), IR(260, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetAttributesEXT, false, false, IR(36, 2), IR(37946, 26), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetHitKindEXT, true, true, IR(160, 3), IR(37972, 23), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetPrimitiveIndexEXT, true, true, IR(160, 3), IR(37995, 30), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetGeometryIndexEXT, true, true, IR(160, 3), IR(38025, 29), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceIdEXT, true, true, IR(160, 3), IR(38054, 26), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceCustomIndexEXT, true, true, IR(160, 3), IR(38080, 35), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayOriginEXT, true, true, IR(160, 3), IR(38115, 31), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayDirectionEXT, true, true, IR(160, 3), IR(38146, 34), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayDirectionEXT, true, true, IR(160, 3), IR(38180, 33), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayOriginEXT, true, true, IR(160, 3), IR(38213, 30), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectToWorldEXT, true, true, IR(160, 3), IR(38243, 29), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldToObjectEXT, true, true, IR(160, 3), IR(38272, 29), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMaxEXT, true, true, IR(160, 3), IR(38301, 23), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReportIntersectionKHR, true, true, IR(172, 4), IR(38324, 22), IR(173, 1), IR(54, 2), IR(24, 2), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIgnoreIntersectionNV, false, false, IR(0, 0), IR(38367, 21), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTerminateRayNV, false, false, IR(0, 0), IR(38388, 15), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceNV, false, false, IR(426, 11), IR(38403, 8), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceMotionNV, false, false, IR(513, 12), IR(38411, 14), IR(0, 0), IR(57, 1), IR(27, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceRayMotionNV, false, false, IR(513, 12), IR(38425, 17), IR(0, 0), IR(57, 1), IR(27, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTriangleVertexPositionsKHR, true, true, IR(172, 4), IR(38442, 50), IR(0, 0), IR(262, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeAccelerationStructureKHR, true, false, IR(68, 1), IR(38492, 29), IR(174, 1), IR(263, 4), IR(194, 4), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpExecuteCallableNV, false, false, IR(36, 2), IR(38549, 18), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionClusterIdNV, true, true, IR(172, 4), IR(38567, 35), IR(175, 1), IR(64, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetClusterIdNV, true, true, IR(160, 3), IR(38625, 24), IR(0, 0), IR(64, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMinEXT, true, true, IR(160, 3), IR(38649, 23), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderBindingTableRecordIndexEXT, true, true, IR(160, 3), IR(38672, 45), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderRecordBufferHandleEXT, true, true, IR(160, 3), IR(38717, 40), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsEmptyEXT, true, true, IR(160, 3), IR(38757, 20), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsHitEXT, true, true, IR(160, 3), IR(38777, 18), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsMissEXT, true, true, IR(160, 3), IR(38795, 19), IR(0, 0), IR(128, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeCooperativeMatrixNV, true, false, IR(623, 5), IR(38814, 24), IR(0, 0), IR(267, 1), IR(79, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeMatrixLoadNV, true, true, IR(628, 6), IR(38838, 24), IR(0, 0), IR(267, 1), IR(79, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixStoreNV, false, false, IR(634, 5), IR(38862, 25), IR(0, 0), IR(267, 1), IR(79, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixMulAddNV, true, true, IR(130, 5), IR(38887, 26), IR(0, 0), IR(267, 1), IR(79, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixLengthNV, true, true, IR(160, 3), IR(38913, 26), IR(0, 0), IR(267, 1), IR(79, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpBeginInvocationInterlockEXT, false, false, IR(0, 0), IR(38939, 28), IR(0, 0), IR(268, 3), IR(80, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpEndInvocationInterlockEXT, false, false, IR(0, 0), IR(38967, 26), IR(0, 0), IR(268, 3), IR(80, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixReduceNV, true, true, IR(639, 5), IR(39036, 26), IR(0, 0), IR(271, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpCooperativeMatrixLoadTensorNV, true, true, IR(644, 7), IR(39137, 30), IR(0, 0), IR(203, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixStoreTensorNV, false, false, IR(651, 5), IR(39167, 31), IR(0, 0), IR(203, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixPerElementOpNV, true, true, IR(151, 5), IR(39198, 32), IR(0, 0), IR(272, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpTypeTensorLayoutNV, true, false, IR(89, 3), IR(39230, 19), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeTensorViewNV, true, false, IR(656, 4), IR(39249, 17), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCreateTensorLayoutNV, true, true, IR(39, 2), IR(39266, 21), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetDimensionNV, true, true, IR(122, 4), IR(39287, 27), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetStrideNV, true, true, IR(122, 4), IR(39314, 24), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSliceNV, true, true, IR(122, 4), IR(39338, 20), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetClampValueNV, true, true, IR(172, 4), IR(39358, 28), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCreateTensorViewNV, true, true, IR(39, 2), IR(39386, 19), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetDimensionNV, true, true, IR(122, 4), IR(39405, 25), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetStrideNV, true, true, IR(122, 4), IR(39430, 22), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpDemoteToHelperInvocation, false, false, IR(0, 0), IR(12289, 25), IR(45, 1), IR(274, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpIsHelperInvocationEXT, true, true, IR(39, 2), IR(39452, 22), IR(0, 0), IR(274, 1), IR(81, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetClipNV, true, true, IR(325, 7), IR(39474, 20), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetBlockSizeNV, true, true, IR(122, 4), IR(39494, 27), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixTransposeNV, true, true, IR(160, 3), IR(39521, 29), IR(0, 0), IR(258, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToImageNV, true, true, IR(160, 3), IR(39550, 18), IR(0, 0), IR(129, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToSamplerNV, true, true, IR(160, 3), IR(39568, 20), IR(0, 0), IR(129, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertImageToUNV, true, true, IR(160, 3), IR(39588, 18), IR(0, 0), IR(129, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertSamplerToUNV, true, true, IR(160, 3), IR(39606, 20), IR(0, 0), IR(129, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToSampledImageNV, true, true, IR(160, 3), IR(39626, 25), IR(0, 0), IR(129, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertSampledImageToUNV, true, true, IR(160, 3), IR(39651, 25), IR(0, 0), IR(129, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSamplerImageAddressingModeNV, false, false, IR(0, 1), IR(39676, 29), IR(0, 0), IR(129, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRawAccessChainNV, true, true, IR(660, 7), IR(39757, 17), IR(0, 0), IR(192, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpRayQueryGetIntersectionSpherePositionNV, true, true, IR(172, 4), IR(39774, 40), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionSphereRadiusNV, true, true, IR(172, 4), IR(39814, 38), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSPositionsNV, true, true, IR(172, 4), IR(39852, 38), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSRadiiNV, true, true, IR(172, 4), IR(39890, 34), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSHitValueNV, true, true, IR(172, 4), IR(39924, 37), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetSpherePositionNV, true, true, IR(160, 3), IR(39961, 29), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetSphereRadiusNV, true, true, IR(160, 3), IR(39990, 27), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetLSSPositionsNV, true, true, IR(160, 3), IR(40017, 27), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetLSSRadiiNV, true, true, IR(160, 3), IR(40044, 23), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsSphereHitNV, true, true, IR(160, 3), IR(40067, 23), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsLSSHitNV, true, true, IR(160, 3), IR(40090, 20), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryIsSphereHitNV, true, true, IR(172, 4), IR(40110, 22), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryIsLSSHitNV, true, true, IR(172, 4), IR(40132, 19), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSubgroupShuffleINTEL, true, true, IR(172, 4), IR(12787, 21), IR(0, 0), IR(275, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleDownINTEL, true, true, IR(130, 5), IR(40151, 25), IR(0, 0), IR(275, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleUpINTEL, true, true, IR(130, 5), IR(40176, 23), IR(0, 0), IR(275, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleXorINTEL, true, true, IR(172, 4), IR(40199, 24), IR(0, 0), IR(275, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupBlockReadINTEL, true, true, IR(160, 3), IR(40223, 23), IR(0, 0), IR(276, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupBlockWriteINTEL, false, false, IR(36, 2), IR(40246, 24), IR(0, 0), IR(276, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageBlockReadINTEL, true, true, IR(172, 4), IR(40270, 28), IR(0, 0), IR(277, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageBlockWriteINTEL, false, false, IR(33, 3), IR(40298, 29), IR(0, 0), IR(277, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageMediaBlockReadINTEL, true, true, IR(215, 6), IR(40327, 33), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageMediaBlockWriteINTEL, false, false, IR(667, 5), IR(40360, 34), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpUCountLeadingZerosINTEL, true, true, IR(160, 3), IR(40394, 24), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUCountTrailingZerosINTEL, true, true, IR(160, 3), IR(40418, 25), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAbsISubINTEL, true, true, IR(172, 4), IR(40443, 13), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAbsUSubINTEL, true, true, IR(172, 4), IR(40456, 13), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAddSatINTEL, true, true, IR(172, 4), IR(40469, 13), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAddSatINTEL, true, true, IR(172, 4), IR(40482, 13), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAverageINTEL, true, true, IR(172, 4), IR(40495, 14), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAverageINTEL, true, true, IR(172, 4), IR(40509, 14), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAverageRoundedINTEL, true, true, IR(172, 4), IR(40523, 21), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAverageRoundedINTEL, true, true, IR(172, 4), IR(40544, 21), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpISubSatINTEL, true, true, IR(172, 4), IR(40565, 13), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUSubSatINTEL, true, true, IR(172, 4), IR(40578, 13), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIMul32x16INTEL, true, true, IR(172, 4), IR(40591, 15), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUMul32x16INTEL, true, true, IR(172, 4), IR(40606, 15), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConstantFunctionPointerINTEL, true, true, IR(160, 3), IR(40621, 29), IR(0, 0), IR(201, 1), IR(97, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFunctionPointerCallINTEL, true, true, IR(107, 3), IR(40650, 25), IR(0, 0), IR(201, 1), IR(97, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmTargetINTEL, true, false, IR(50, 2), IR(40675, 15), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmINTEL, true, true, IR(672, 6), IR(13005, 9), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmCallINTEL, true, true, IR(122, 4), IR(40690, 13), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAtomicFMinEXT, true, true, IR(235, 6), IR(40703, 14), IR(0, 0), IR(280, 4), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicFMaxEXT, true, true, IR(235, 6), IR(40717, 14), IR(0, 0), IR(280, 4), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAssumeTrueKHR, false, false, IR(10, 1), IR(40731, 14), IR(0, 0), IR(284, 1), IR(101, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpExpectKHR, true, true, IR(172, 4), IR(40745, 10), IR(0, 0), IR(284, 1), IR(101, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpDecorateString, false, false, IR(163, 2), IR(40755, 15), IR(176, 1), IR(1, 0), IR(198, 2), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpMemberDecorateString, false, false, IR(165, 3), IR(40791, 21), IR(177, 1), IR(1, 0), IR(198, 2), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpVmeImageINTEL, true, true, IR(172, 4), IR(40839, 14), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeVmeImageINTEL, true, false, IR(87, 2), IR(40853, 18), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImePayloadINTEL, true, false, IR(68, 1), IR(40871, 23), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcRefPayloadINTEL, true, false, IR(68, 1), IR(40894, 23), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcSicPayloadINTEL, true, false, IR(68, 1), IR(40917, 23), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcMcePayloadINTEL, true, false, IR(68, 1), IR(40940, 23), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcMceResultINTEL, true, false, IR(68, 1), IR(40963, 22), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultINTEL, true, false, IR(68, 1), IR(40985, 22), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultSingleReferenceStreamoutINTEL, true, false, IR(68, 1), IR(41007, 46), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultDualReferenceStreamoutINTEL, true, false, IR(68, 1), IR(41053, 44), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeSingleReferenceStreaminINTEL, true, false, IR(68, 1), IR(41097, 39), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeDualReferenceStreaminINTEL, true, false, IR(68, 1), IR(41136, 37), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcRefResultINTEL, true, false, IR(68, 1), IR(41173, 22), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcSicResultINTEL, true, false, IR(68, 1), IR(41195, 22), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL, true, true, IR(172, 4), IR(41217, 60), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL, true, true, IR(172, 4), IR(41277, 53), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterShapePenaltyINTEL, true, true, IR(172, 4), IR(41330, 47), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterShapePenaltyINTEL, true, true, IR(172, 4), IR(41377, 40), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL, true, true, IR(172, 4), IR(41417, 51), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterDirectionPenaltyINTEL, true, true, IR(172, 4), IR(41468, 44), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL, true, true, IR(172, 4), IR(41512, 51), IR(0, 0), IR(286, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL, true, true, IR(172, 4), IR(41563, 56), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL, true, true, IR(39, 2), IR(41619, 50), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL, true, true, IR(39, 2), IR(41669, 52), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL, true, true, IR(39, 2), IR(41721, 49), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetMotionVectorCostFunctionINTEL, true, true, IR(215, 6), IR(41770, 47), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL, true, true, IR(172, 4), IR(41817, 50), IR(0, 0), IR(286, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL, true, true, IR(39, 2), IR(41867, 51), IR(0, 0), IR(286, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL, true, true, IR(39, 2), IR(41918, 56), IR(0, 0), IR(288, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetAcOnlyHaarINTEL, true, true, IR(160, 3), IR(41974, 33), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL, true, true, IR(172, 4), IR(42007, 52), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL, true, true, IR(172, 4), IR(42059, 61), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL, true, true, IR(130, 5), IR(42120, 61), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToImePayloadINTEL, true, true, IR(160, 3), IR(42181, 39), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToImeResultINTEL, true, true, IR(160, 3), IR(42220, 38), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToRefPayloadINTEL, true, true, IR(160, 3), IR(42258, 39), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToRefResultINTEL, true, true, IR(160, 3), IR(42297, 38), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToSicPayloadINTEL, true, true, IR(160, 3), IR(42335, 39), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToSicResultINTEL, true, true, IR(160, 3), IR(42374, 38), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetMotionVectorsINTEL, true, true, IR(160, 3), IR(42412, 36), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterDistortionsINTEL, true, true, IR(160, 3), IR(42448, 39), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetBestInterDistortionsINTEL, true, true, IR(160, 3), IR(42487, 43), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMajorShapeINTEL, true, true, IR(160, 3), IR(42530, 38), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMinorShapeINTEL, true, true, IR(160, 3), IR(42568, 38), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterDirectionsINTEL, true, true, IR(160, 3), IR(42606, 38), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMotionVectorCountINTEL, true, true, IR(160, 3), IR(42644, 45), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterReferenceIdsINTEL, true, true, IR(160, 3), IR(42689, 40), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL, true, true, IR(130, 5), IR(42729, 62), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeInitializeINTEL, true, true, IR(130, 5), IR(42791, 30), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetSingleReferenceINTEL, true, true, IR(130, 5), IR(42821, 38), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetDualReferenceINTEL, true, true, IR(215, 6), IR(42859, 36), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeRefWindowSizeINTEL, true, true, IR(172, 4), IR(42895, 33), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeAdjustRefOffsetINTEL, true, true, IR(215, 6), IR(42928, 35), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(42963, 39), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetMaxMotionVectorCountINTEL, true, true, IR(172, 4), IR(43002, 43), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetUnidirectionalMixDisableINTEL, true, true, IR(160, 3), IR(43045, 47), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetEarlySearchTerminationThresholdINTEL, true, true, IR(172, 4), IR(43092, 54), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetWeightedSadINTEL, true, true, IR(172, 4), IR(43146, 34), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(43180, 47), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(43227, 45), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL, true, true, IR(215, 6), IR(43272, 55), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL, true, true, IR(325, 7), IR(43327, 53), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL, true, true, IR(130, 5), IR(43380, 56), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL, true, true, IR(215, 6), IR(43436, 54), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL, true, true, IR(215, 6), IR(43490, 58), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL, true, true, IR(325, 7), IR(43548, 56), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeConvertToMceResultINTEL, true, true, IR(160, 3), IR(43604, 38), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetSingleReferenceStreaminINTEL, true, true, IR(160, 3), IR(43642, 46), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetDualReferenceStreaminINTEL, true, true, IR(160, 3), IR(43688, 44), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeStripSingleReferenceStreamoutINTEL, true, true, IR(160, 3), IR(43732, 49), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeStripDualReferenceStreamoutINTEL, true, true, IR(160, 3), IR(43781, 47), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL, true, true, IR(172, 4), IR(43828, 70), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL, true, true, IR(172, 4), IR(43898, 68), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL, true, true, IR(172, 4), IR(43966, 69), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL, true, true, IR(130, 5), IR(44035, 68), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL, true, true, IR(130, 5), IR(44103, 66), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL, true, true, IR(130, 5), IR(44169, 67), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetBorderReachedINTEL, true, true, IR(172, 4), IR(44236, 36), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetTruncatedSearchIndicationINTEL, true, true, IR(160, 3), IR(44272, 48), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL, true, true, IR(160, 3), IR(44320, 59), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL, true, true, IR(160, 3), IR(44379, 58), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL, true, true, IR(160, 3), IR(44437, 56), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcFmeInitializeINTEL, true, true, IR(678, 9), IR(44493, 30), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcBmeInitializeINTEL, true, true, IR(687, 10), IR(44523, 30), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(44553, 39), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefSetBidirectionalMixDisableINTEL, true, true, IR(160, 3), IR(44592, 46), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefSetBilinearFilterEnableINTEL, true, true, IR(160, 3), IR(44638, 43), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(44681, 47), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(44728, 45), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithMultiReferenceINTEL, true, true, IR(130, 5), IR(44773, 46), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL, true, true, IR(215, 6), IR(44819, 56), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefConvertToMceResultINTEL, true, true, IR(160, 3), IR(44875, 38), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicInitializeINTEL, true, true, IR(160, 3), IR(44913, 30), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureSkcINTEL, true, true, IR(288, 8), IR(44943, 32), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureIpeLumaINTEL, true, true, IR(687, 10), IR(44975, 36), IR(0, 0), IR(286, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureIpeLumaChromaINTEL, true, true, IR(697, 13), IR(45011, 42), IR(0, 0), IR(288, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetMotionVectorMaskINTEL, true, true, IR(172, 4), IR(45053, 39), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(45092, 39), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraLumaShapePenaltyINTEL, true, true, IR(172, 4), IR(45131, 44), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraLumaModeCostFunctionINTEL, true, true, IR(215, 6), IR(45175, 48), IR(0, 0), IR(286, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraChromaModeCostFunctionINTEL, true, true, IR(172, 4), IR(45223, 50), IR(0, 0), IR(288, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetBilinearFilterEnableINTEL, true, true, IR(160, 3), IR(45273, 43), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetSkcForwardTransformEnableINTEL, true, true, IR(172, 4), IR(45316, 48), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetBlockBasedRawSkipSadINTEL, true, true, IR(172, 4), IR(45364, 43), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateIpeINTEL, true, true, IR(172, 4), IR(45407, 31), IR(0, 0), IR(286, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(45438, 47), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(45485, 45), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithMultiReferenceINTEL, true, true, IR(130, 5), IR(45530, 46), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL, true, true, IR(215, 6), IR(45576, 56), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConvertToMceResultINTEL, true, true, IR(160, 3), IR(45632, 38), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetIpeLumaShapeINTEL, true, true, IR(160, 3), IR(45670, 35), IR(0, 0), IR(286, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetBestIpeLumaDistortionINTEL, true, true, IR(160, 3), IR(45705, 44), IR(0, 0), IR(286, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetBestIpeChromaDistortionINTEL, true, true, IR(160, 3), IR(45749, 46), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedIpeLumaModesINTEL, true, true, IR(160, 3), IR(45795, 41), IR(0, 0), IR(286, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetIpeChromaModeINTEL, true, true, IR(160, 3), IR(45836, 36), IR(0, 0), IR(288, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL, true, true, IR(160, 3), IR(45872, 50), IR(0, 0), IR(286, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL, true, true, IR(160, 3), IR(45922, 48), IR(0, 0), IR(286, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetInterRawSadsINTEL, true, true, IR(160, 3), IR(45970, 35), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpVariableLengthArrayINTEL, true, true, IR(160, 3), IR(13243, 25), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpSaveMemoryINTEL, true, true, IR(39, 2), IR(46005, 16), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpRestoreMemoryINTEL, false, false, IR(10, 1), IR(46021, 19), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpArbitraryFloatSinCosPiALTERA, true, true, IR(710, 8), IR(46040, 29), IR(178, 1), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastALTERA, true, true, IR(710, 8), IR(46097, 25), IR(179, 1), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastFromIntALTERA, true, true, IR(710, 8), IR(46146, 32), IR(180, 1), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastToIntALTERA, true, true, IR(710, 8), IR(46209, 30), IR(181, 1), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatAddALTERA, true, true, IR(718, 10), IR(46268, 24), IR(182, 1), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSubALTERA, true, true, IR(718, 10), IR(46315, 24), IR(183, 1), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatMulALTERA, true, true, IR(718, 10), IR(46362, 24), IR(184, 1), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatDivALTERA, true, true, IR(718, 10), IR(46409, 24), IR(185, 1), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatGTALTERA, true, true, IR(728, 6), IR(46456, 23), IR(186, 1), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatGEALTERA, true, true, IR(728, 6), IR(46501, 23), IR(187, 1), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLTALTERA, true, true, IR(728, 6), IR(46546, 23), IR(188, 1), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLEALTERA, true, true, IR(728, 6), IR(46591, 23), IR(189, 1), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatEQALTERA, true, true, IR(728, 6), IR(46636, 23), IR(190, 1), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatRecipALTERA, true, true, IR(710, 8), IR(46681, 26), IR(191, 1), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatRSqrtALTERA, true, true, IR(710, 8), IR(46732, 26), IR(192, 1), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCbrtALTERA, true, true, IR(710, 8), IR(46783, 25), IR(193, 1), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatHypotALTERA, true, true, IR(718, 10), IR(46832, 26), IR(194, 1), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSqrtALTERA, true, true, IR(710, 8), IR(46883, 25), IR(195, 1), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLogINTEL, true, true, IR(710, 8), IR(46932, 23), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog2INTEL, true, true, IR(710, 8), IR(46955, 24), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog10INTEL, true, true, IR(710, 8), IR(46979, 25), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog1pINTEL, true, true, IR(710, 8), IR(47004, 25), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExpINTEL, true, true, IR(710, 8), IR(47029, 23), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExp2INTEL, true, true, IR(710, 8), IR(47052, 24), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExp10INTEL, true, true, IR(710, 8), IR(47076, 25), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExpm1INTEL, true, true, IR(710, 8), IR(47101, 25), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinINTEL, true, true, IR(710, 8), IR(47126, 23), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCosINTEL, true, true, IR(710, 8), IR(47149, 23), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinCosINTEL, true, true, IR(710, 8), IR(47172, 26), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinPiINTEL, true, true, IR(710, 8), IR(47198, 25), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCosPiINTEL, true, true, IR(710, 8), IR(47223, 25), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatASinINTEL, true, true, IR(710, 8), IR(47248, 24), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatASinPiINTEL, true, true, IR(710, 8), IR(47272, 26), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatACosINTEL, true, true, IR(710, 8), IR(47298, 24), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatACosPiINTEL, true, true, IR(710, 8), IR(47322, 26), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATanINTEL, true, true, IR(710, 8), IR(47348, 24), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATanPiINTEL, true, true, IR(710, 8), IR(47372, 26), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATan2INTEL, true, true, IR(718, 10), IR(47398, 25), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowINTEL, true, true, IR(718, 10), IR(47423, 23), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowRINTEL, true, true, IR(718, 10), IR(47446, 24), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowNINTEL, true, true, IR(718, 10), IR(47470, 24), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpLoopControlINTEL, false, false, IR(18, 1), IR(47494, 17), IR(0, 0), IR(292, 1), IR(111, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAliasDomainDeclINTEL, true, false, IR(734, 2), IR(47511, 21), IR(0, 0), IR(138, 1), IR(123, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAliasScopeDeclINTEL, true, false, IR(736, 3), IR(47532, 20), IR(0, 0), IR(138, 1), IR(123, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAliasScopeListDeclINTEL, true, false, IR(92, 2), IR(47552, 24), IR(0, 0), IR(138, 1), IR(123, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSqrtALTERA, true, true, IR(710, 8), IR(47576, 16), IR(196, 1), IR(191, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedRecipALTERA, true, true, IR(710, 8), IR(47607, 17), IR(197, 1), IR(191, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedRsqrtALTERA, true, true, IR(710, 8), IR(47640, 17), IR(198, 1), IR(191, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinALTERA, true, true, IR(710, 8), IR(47673, 15), IR(199, 1), IR(191, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedCosALTERA, true, true, IR(710, 8), IR(47702, 15), IR(200, 1), IR(191, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinCosALTERA, true, true, IR(710, 8), IR(47731, 18), IR(201, 1), IR(191, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinPiALTERA, true, true, IR(710, 8), IR(47766, 17), IR(202, 1), IR(191, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedCosPiALTERA, true, true, IR(710, 8), IR(47799, 17), IR(203, 1), IR(191, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinCosPiALTERA, true, true, IR(710, 8), IR(47832, 20), IR(204, 1), IR(191, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedLogALTERA, true, true, IR(710, 8), IR(47871, 15), IR(205, 1), IR(191, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedExpALTERA, true, true, IR(710, 8), IR(47900, 15), IR(206, 1), IR(191, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpPtrCastToCrossWorkgroupALTERA, true, true, IR(160, 3), IR(47929, 30), IR(207, 1), IR(202, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpCrossWorkgroupCastToPtrALTERA, true, true, IR(160, 3), IR(47988, 30), IR(208, 1), IR(202, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpReadPipeBlockingALTERA, true, true, IR(172, 4), IR(48047, 23), IR(209, 1), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpWritePipeBlockingALTERA, true, true, IR(172, 4), IR(48092, 24), IR(210, 1), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFPGARegALTERA, true, true, IR(160, 3), IR(14201, 14), IR(61, 1), IR(294, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpRayQueryGetRayTMinKHR, true, true, IR(160, 3), IR(48139, 22), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetRayFlagsKHR, true, true, IR(160, 3), IR(48161, 23), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTKHR, true, true, IR(172, 4), IR(48184, 28), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceCustomIndexKHR, true, true, IR(172, 4), IR(48212, 46), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceIdKHR, true, true, IR(172, 4), IR(48258, 37), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR, true, true, IR(172, 4), IR(48295, 65), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionGeometryIndexKHR, true, true, IR(172, 4), IR(48360, 40), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionPrimitiveIndexKHR, true, true, IR(172, 4), IR(48400, 41), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionBarycentricsKHR, true, true, IR(172, 4), IR(48441, 39), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionFrontFaceKHR, true, true, IR(172, 4), IR(48480, 36), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionCandidateAABBOpaqueKHR, true, true, IR(160, 3), IR(48516, 46), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectRayDirectionKHR, true, true, IR(172, 4), IR(48562, 45), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectRayOriginKHR, true, true, IR(172, 4), IR(48607, 42), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetWorldRayDirectionKHR, true, true, IR(160, 3), IR(48649, 32), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetWorldRayOriginKHR, true, true, IR(160, 3), IR(48681, 29), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectToWorldKHR, true, true, IR(172, 4), IR(48710, 40), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionWorldToObjectKHR, true, true, IR(172, 4), IR(48750, 40), IR(0, 0), IR(195, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAtomicFAddEXT, true, true, IR(235, 6), IR(48790, 14), IR(0, 0), IR(295, 4), IR(147, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpTypeBufferSurfaceINTEL, true, false, IR(100, 2), IR(48804, 23), IR(0, 0), IR(130, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeStructContinuedINTEL, false, false, IR(739, 1), IR(48827, 25), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantCompositeContinuedINTEL, false, false, IR(739, 1), IR(48852, 32), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCompositeContinuedINTEL, false, false, IR(739, 1), IR(48884, 36), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpCompositeConstructContinuedINTEL, true, true, IR(107, 3), IR(48920, 33), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpConvertFToBF16INTEL, true, true, IR(160, 3), IR(48953, 20), IR(0, 0), IR(300, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertBF16ToFINTEL, true, true, IR(160, 3), IR(48973, 20), IR(0, 0), IR(300, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpControlBarrierArriveINTEL, false, false, IR(221, 3), IR(48993, 26), IR(0, 0), IR(301, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpControlBarrierWaitINTEL, false, false, IR(221, 3), IR(49019, 24), IR(0, 0), IR(301, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpArithmeticFenceEXT, true, true, IR(160, 3), IR(14654, 19), IR(0, 0), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpTaskSequenceCreateALTERA, true, true, IR(740, 7), IR(49043, 25), IR(211, 1), IR(303, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTaskSequenceAsyncALTERA, false, false, IR(168, 2), IR(49092, 24), IR(212, 1), IR(303, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTaskSequenceGetALTERA, true, true, IR(160, 3), IR(49139, 22), IR(213, 1), IR(303, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTaskSequenceReleaseALTERA, false, false, IR(10, 1), IR(49182, 26), IR(214, 1), IR(303, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeTaskSequenceALTERA, true, false, IR(68, 1), IR(49233, 23), IR(215, 1), IR(303, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupBlockPrefetchINTEL, false, false, IR(139, 3), IR(49278, 27), IR(0, 0), IR(304, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadINTEL, false, false, IR(747, 10), IR(49305, 25), IR(0, 0), IR(108, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadTransformINTEL, false, false, IR(747, 10), IR(49330, 34), IR(0, 0), IR(305, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadTransposeINTEL, false, false, IR(747, 10), IR(49364, 34), IR(0, 0), IR(306, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockPrefetchINTEL, false, false, IR(757, 9), IR(49398, 29), IR(0, 0), IR(108, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockStoreINTEL, false, false, IR(747, 10), IR(49427, 26), IR(0, 0), IR(108, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupMatrixMultiplyAccumulateINTEL, true, true, IR(766, 7), IR(15131, 38), IR(0, 0), IR(307, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpBitwiseFunctionINTEL, true, true, IR(215, 6), IR(49515, 21), IR(0, 0), IR(308, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpUntypedVariableLengthArrayINTEL, true, true, IR(172, 4), IR(15197, 32), IR(0, 0), IR(309, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpConditionalExtensionINTEL, false, false, IR(45, 2), IR(49536, 26), IR(0, 0), IR(111, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpConditionalEntryPointINTEL, false, false, IR(773, 5), IR(49562, 27), IR(0, 0), IR(111, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpConditionalCapabilityINTEL, false, false, IR(778, 2), IR(49589, 27), IR(0, 0), IR(111, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpSpecConstantTargetINTEL, true, true, IR(780, 4), IR(49616, 24), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantArchitectureINTEL, true, true, IR(784, 6), IR(49640, 30), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCapabilitiesINTEL, true, true, IR(790, 3), IR(49707, 30), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConditionalCopyObjectINTEL, true, true, IR(107, 3), IR(49737, 27), IR(0, 0), IR(111, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpGroupIMulKHR, true, true, IR(283, 5), IR(49764, 13), IR(0, 0), IR(311, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMulKHR, true, true, IR(283, 5), IR(49777, 13), IR(0, 0), IR(311, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseAndKHR, true, true, IR(283, 5), IR(49790, 19), IR(0, 0), IR(311, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseOrKHR, true, true, IR(283, 5), IR(49809, 18), IR(0, 0), IR(311, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseXorKHR, true, true, IR(283, 5), IR(49827, 19), IR(0, 0), IR(311, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalAndKHR, true, true, IR(283, 5), IR(49846, 19), IR(0, 0), IR(311, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalOrKHR, true, true, IR(283, 5), IR(49865, 18), IR(0, 0), IR(311, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalXorKHR, true, true, IR(283, 5), IR(49883, 19), IR(0, 0), IR(311, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpRoundFToTF32INTEL, true, true, IR(160, 3), IR(49902, 18), IR(0, 0), IR(312, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpMaskedGatherINTEL, true, true, IR(793, 6), IR(49920, 18), IR(0, 0), IR(313, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpMaskedScatterINTEL, false, false, IR(799, 4), IR(49938, 19), IR(0, 0), IR(313, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpConvertHandleToImageINTEL, true, true, IR(160, 3), IR(49957, 26), IR(0, 0), IR(314, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertHandleToSamplerINTEL, true, true, IR(160, 3), IR(49983, 28), IR(0, 0), IR(314, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertHandleToSampledImageINTEL, true, true, IR(160, 3), IR(50011, 33), IR(0, 0), IR(314, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
}};

// Opcode strings (without the 'Op' prefix) and opcode values, ordered by name.
// The fields in order are:
//   name, either the primary name or an alias, indexing into kStrings
//   index into kInstructionDesc
static const std::array<NameIndex, 909> kInstructionNames{{
  {IR(40443, 13), 590}, // 0 AbsISubINTEL
  {IR(40456, 13), 591}, // 1 AbsUSubINTEL
  {IR(29213, 12), 58}, // 2 AccessChain
  {IR(47511, 21), 776}, // 3 AliasDomainDeclINTEL
  {IR(47532, 20), 777}, // 4 AliasScopeDeclINTEL
  {IR(47552, 24), 778}, // 5 AliasScopeListDeclINTEL
  {IR(30510, 4), 143}, // 6 All
  {IR(35889, 25), 426}, // 7 AllocateNodePayloadsAMDX
  {IR(30506, 4), 142}, // 8 Any
  {IR(47298, 24), 767}, // 9 ArbitraryFloatACosINTEL
  {IR(47322, 26), 768}, // 10 ArbitraryFloatACosPiINTEL
  {IR(47248, 24), 765}, // 11 ArbitraryFloatASinINTEL
  {IR(47272, 26), 766}, // 12 ArbitraryFloatASinPiINTEL
  {IR(47398, 25), 771}, // 13 ArbitraryFloatATan2INTEL
  {IR(47348, 24), 769}, // 14 ArbitraryFloatATanINTEL
  {IR(47372, 26), 770}, // 15 ArbitraryFloatATanPiINTEL
  {IR(46268, 24), 738}, // 16 ArbitraryFloatAddALTERA
  {IR(46292, 23), 738}, // 17 ArbitraryFloatAddINTEL
  {IR(46097, 25), 735}, // 18 ArbitraryFloatCastALTERA
  {IR(46146, 32), 736}, // 19 ArbitraryFloatCastFromIntALTERA
  {IR(46178, 31), 736}, // 20 ArbitraryFloatCastFromIntINTEL
  {IR(46122, 24), 735}, // 21 ArbitraryFloatCastINTEL
  {IR(46209, 30), 737}, // 22 ArbitraryFloatCastToIntALTERA
  {IR(46239, 29), 737}, // 23 ArbitraryFloatCastToIntINTEL
  {IR(46783, 25), 749}, // 24 ArbitraryFloatCbrtALTERA
  {IR(46808, 24), 749}, // 25 ArbitraryFloatCbrtINTEL
  {IR(47149, 23), 761}, // 26 ArbitraryFloatCosINTEL
  {IR(47223, 25), 764}, // 27 ArbitraryFloatCosPiINTEL
  {IR(46409, 24), 741}, // 28 ArbitraryFloatDivALTERA
  {IR(46433, 23), 741}, // 29 ArbitraryFloatDivINTEL
  {IR(46636, 23), 746}, // 30 ArbitraryFloatEQALTERA
  {IR(46659, 22), 746}, // 31 ArbitraryFloatEQINTEL
  {IR(47076, 25), 758}, // 32 ArbitraryFloatExp10INTEL
  {IR(47052, 24), 757}, // 33 ArbitraryFloatExp2INTEL
  {IR(47029, 23), 756}, // 34 ArbitraryFloatExpINTEL
  {IR(47101, 25), 759}, // 35 ArbitraryFloatExpm1INTEL
  {IR(46501, 23), 743}, // 36 ArbitraryFloatGEALTERA
  {IR(46524, 22), 743}, // 37 ArbitraryFloatGEINTEL
  {IR(46456, 23), 742}, // 38 ArbitraryFloatGTALTERA
  {IR(46479, 22), 742}, // 39 ArbitraryFloatGTINTEL
  {IR(46832, 26), 750}, // 40 ArbitraryFloatHypotALTERA
  {IR(46858, 25), 750}, // 41 ArbitraryFloatHypotINTEL
  {IR(46591, 23), 745}, // 42 ArbitraryFloatLEALTERA
  {IR(46614, 22), 745}, // 43 ArbitraryFloatLEINTEL
  {IR(46546, 23), 744}, // 44 ArbitraryFloatLTALTERA
  {IR(46569, 22), 744}, // 45 ArbitraryFloatLTINTEL
  {IR(46979, 25), 754}, // 46 ArbitraryFloatLog10INTEL
  {IR(47004, 25), 755}, // 47 ArbitraryFloatLog1pINTEL
  {IR(46955, 24), 753}, // 48 ArbitraryFloatLog2INTEL
  {IR(46932, 23), 752}, // 49 ArbitraryFloatLogINTEL
  {IR(46362, 24), 740}, // 50 ArbitraryFloatMulALTERA
  {IR(46386, 23), 740}, // 51 ArbitraryFloatMulINTEL
  {IR(47423, 23), 772}, // 52 ArbitraryFloatPowINTEL
  {IR(47470, 24), 774}, // 53 ArbitraryFloatPowNINTEL
  {IR(47446, 24), 773}, // 54 ArbitraryFloatPowRINTEL
  {IR(46732, 26), 748}, // 55 ArbitraryFloatRSqrtALTERA
  {IR(46758, 25), 748}, // 56 ArbitraryFloatRSqrtINTEL
  {IR(46681, 26), 747}, // 57 ArbitraryFloatRecipALTERA
  {IR(46707, 25), 747}, // 58 ArbitraryFloatRecipINTEL
  {IR(47172, 26), 762}, // 59 ArbitraryFloatSinCosINTEL
  {IR(46040, 29), 734}, // 60 ArbitraryFloatSinCosPiALTERA
  {IR(46069, 28), 734}, // 61 ArbitraryFloatSinCosPiINTEL
  {IR(47126, 23), 760}, // 62 ArbitraryFloatSinINTEL
  {IR(47198, 25), 763}, // 63 ArbitraryFloatSinPiINTEL
  {IR(46883, 25), 751}, // 64 ArbitraryFloatSqrtALTERA
  {IR(46908, 24), 751}, // 65 ArbitraryFloatSqrtINTEL
  {IR(46315, 24), 739}, // 66 ArbitraryFloatSubALTERA
  {IR(46339, 23), 739}, // 67 ArbitraryFloatSubINTEL
  {IR(14654, 19), 822}, // 68 ArithmeticFenceEXT
  {IR(29260, 12), 61}, // 69 ArrayLength
  {IR(40690, 13), 606}, // 70 AsmCallINTEL
  {IR(13005, 9), 605}, // 71 AsmINTEL
  {IR(40675, 15), 604}, // 72 AsmTargetINTEL
  {IR(40731, 14), 609}, // 73 AssumeTrueKHR
  {IR(31532, 10), 220}, // 74 AtomicAnd
  {IR(31384, 22), 210}, // 75 AtomicCompareExchange
  {IR(31406, 26), 211}, // 76 AtomicCompareExchangeWeak
  {IR(31369, 15), 209}, // 77 AtomicExchange
  {IR(48790, 14), 812}, // 78 AtomicFAddEXT
  {IR(40717, 14), 608}, // 79 AtomicFMaxEXT
  {IR(40703, 14), 607}, // 80 AtomicFMinEXT
  {IR(32917, 16), 292}, // 81 AtomicFlagClear
  {IR(32896, 21), 291}, // 82 AtomicFlagTestAndSet
  {IR(31466, 11), 214}, // 83 AtomicIAdd
  {IR(31449, 17), 213}, // 84 AtomicIDecrement
  {IR(31432, 17), 212}, // 85 AtomicIIncrement
  {IR(31477, 11), 215}, // 86 AtomicISub
  {IR(31346, 11), 207}, // 87 AtomicLoad
  {IR(31542, 9), 221}, // 88 AtomicOr
  {IR(31510, 11), 218}, // 89 AtomicSMax
  {IR(31488, 11), 216}, // 90 AtomicSMin
  {IR(31357, 12), 208}, // 91 AtomicStore
  {IR(31521, 11), 219}, // 92 AtomicUMax
  {IR(31499, 11), 217}, // 93 AtomicUMin
  {IR(31551, 10), 222}, // 94 AtomicXor
  {IR(38939, 28), 536}, // 95 BeginInvocationInterlockEXT
  {IR(35443, 17), 407}, // 96 BitCastArrayQCOM
  {IR(31130, 9), 191}, // 97 BitCount
  {IR(31070, 15), 187}, // 98 BitFieldInsert
  {IR(31085, 17), 188}, // 99 BitFieldSExtract
  {IR(31102, 17), 189}, // 100 BitFieldUExtract
  {IR(31119, 11), 190}, // 101 BitReverse
  {IR(30258, 8), 114}, // 102 Bitcast
  {IR(31055, 11), 185}, // 103 BitwiseAnd
  {IR(49515, 21), 835}, // 104 BitwiseFunctionINTEL
  {IR(31034, 10), 183}, // 105 BitwiseOr
  {IR(31044, 11), 184}, // 106 BitwiseXor
  {IR(31661, 7), 227}, // 107 Branch
  {IR(31668, 18), 228}, // 108 BranchConditional
  {IR(32529, 13), 277}, // 109 BuildNDRange
  {IR(28274, 11), 15}, // 110 Capability
  {IR(32487, 26), 275}, // 111 CaptureEventProfilingInfo
  {IR(33993, 23), 344}, // 112 ColorAttachmentReadEXT
  {IR(32079, 15), 255}, // 113 CommitReadPipe
  {IR(32094, 16), 256}, // 114 CommitWritePipe
  {IR(29520, 19), 72}, // 115 CompositeConstruct
  {IR(48920, 33), 817}, // 116 CompositeConstructContinuedINTEL
  {IR(35576, 30), 412}, // 117 CompositeConstructCoopMatQCOM
  {IR(35151, 31), 395}, // 118 CompositeConstructReplicateEXT
  {IR(29539, 17), 73}, // 119 CompositeExtract
  {IR(35606, 28), 413}, // 120 CompositeExtractCoopMatQCOM
  {IR(29556, 16), 74}, // 121 CompositeInsert
  {IR(49589, 27), 839}, // 122 ConditionalCapabilityINTEL
  {IR(49737, 27), 843}, // 123 ConditionalCopyObjectINTEL
  {IR(49562, 27), 838}, // 124 ConditionalEntryPointINTEL
  {IR(49536, 26), 837}, // 125 ConditionalExtensionINTEL
  {IR(16787, 9), 39}, // 126 Constant
  {IR(28780, 18), 40}, // 127 ConstantComposite
  {IR(48852, 32), 815}, // 128 ConstantCompositeContinuedINTEL
  {IR(35087, 30), 393}, // 129 ConstantCompositeReplicateEXT
  {IR(28728, 14), 38}, // 130 ConstantFalse
  {IR(40621, 29), 602}, // 131 ConstantFunctionPointerINTEL
  {IR(28892, 13), 42}, // 132 ConstantNull
  {IR(32972, 20), 296}, // 133 ConstantPipeStorage
  {IR(28876, 16), 41}, // 134 ConstantSampler
  {IR(36042, 19), 432}, // 135 ConstantStringAMDX
  {IR(28715, 13), 37}, // 136 ConstantTrue
  {IR(31317, 15), 205}, // 137 ControlBarrier
  {IR(48993, 26), 820}, // 138 ControlBarrierArriveINTEL
  {IR(49019, 24), 821}, // 139 ControlBarrierWaitINTEL
  {IR(48973, 20), 819}, // 140 ConvertBF16ToFINTEL
  {IR(48953, 20), 818}, // 141 ConvertFToBF16INTEL
  {IR(30064, 12), 100}, // 142 ConvertFToS
  {IR(30052, 12), 99}, // 143 ConvertFToU
  {IR(49957, 26), 855}, // 144 ConvertHandleToImageINTEL
  {IR(50011, 33), 857}, // 145 ConvertHandleToSampledImageINTEL
  {IR(49983, 28), 856}, // 146 ConvertHandleToSamplerINTEL
  {IR(39588, 18), 559}, // 147 ConvertImageToUNV
  {IR(30141, 14), 107}, // 148 ConvertPtrToU
  {IR(30076, 12), 101}, // 149 ConvertSToF
  {IR(39651, 25), 562}, // 150 ConvertSampledImageToUNV
  {IR(39606, 20), 560}, // 151 ConvertSamplerToUNV
  {IR(34665, 35), 379}, // 152 ConvertUToAccelerationStructureKHR
  {IR(30088, 12), 102}, // 153 ConvertUToF
  {IR(39550, 18), 557}, // 154 ConvertUToImageNV
  {IR(30185, 14), 110}, // 155 ConvertUToPtr
  {IR(39626, 25), 561}, // 156 ConvertUToSampledImageNV
  {IR(39568, 20), 558}, // 157 ConvertUToSamplerNV
  {IR(37202, 27), 475}, // 158 CooperativeMatrixConvertNV
  {IR(35060, 27), 392}, // 159 CooperativeMatrixLengthKHR
  {IR(38913, 26), 535}, // 160 CooperativeMatrixLengthNV
  {IR(34928, 25), 389}, // 161 CooperativeMatrixLoadKHR
  {IR(38838, 24), 532}, // 162 CooperativeMatrixLoadNV
  {IR(39137, 30), 539}, // 163 CooperativeMatrixLoadTensorNV
  {IR(35033, 27), 391}, // 164 CooperativeMatrixMulAddKHR
  {IR(38887, 26), 534}, // 165 CooperativeMatrixMulAddNV
  {IR(39198, 32), 541}, // 166 CooperativeMatrixPerElementOpNV
  {IR(39036, 26), 538}, // 167 CooperativeMatrixReduceNV
  {IR(34953, 26), 390}, // 168 CooperativeMatrixStoreKHR
  {IR(38862, 25), 533}, // 169 CooperativeMatrixStoreNV
  {IR(39167, 31), 540}, // 170 CooperativeMatrixStoreTensorNV
  {IR(39521, 29), 556}, // 171 CooperativeMatrixTransposeNV
  {IR(37397, 24), 482}, // 172 CooperativeVectorLoadNV
  {IR(37170, 32), 474}, // 173 CooperativeVectorMatrixMulAddNV
  {IR(37060, 29), 471}, // 174 CooperativeVectorMatrixMulNV
  {IR(37089, 42), 472}, // 175 CooperativeVectorOuterProductAccumulateNV
  {IR(37131, 39), 473}, // 176 CooperativeVectorReduceSumAccumulateNV
  {IR(37421, 25), 483}, // 177 CooperativeVectorStoreNV
  {IR(33952, 12), 340}, // 178 CopyLogical
  {IR(29186, 11), 56}, // 179 CopyMemory
  {IR(29197, 16), 57}, // 180 CopyMemorySized
  {IR(29572, 11), 75}, // 181 CopyObject
  {IR(32992, 26), 297}, // 182 CreatePipeFromPipeStorage
  {IR(39266, 21), 544}, // 183 CreateTensorLayoutNV
  {IR(39386, 19), 549}, // 184 CreateTensorViewNV
  {IR(32439, 16), 272}, // 185 CreateUserEvent
  {IR(47988, 30), 791}, // 186 CrossWorkgroupCastToPtrALTERA
  {IR(48018, 29), 791}, // 187 CrossWorkgroupCastToPtrINTEL
  {IR(31139, 5), 192}, // 188 DPdx
  {IR(31185, 11), 198}, // 189 DPdxCoarse
  {IR(31156, 9), 195}, // 190 DPdxFine
  {IR(31144, 5), 193}, // 191 DPdy
  {IR(31196, 11), 199}, // 192 DPdyCoarse
  {IR(31165, 9), 196}, // 193 DPdyFine
  {IR(29346, 9), 64}, // 194 Decorate
  {IR(33169, 11), 305}, // 195 DecorateId
  {IR(40755, 15), 611}, // 196 DecorateString
  {IR(40770, 21), 611}, // 197 DecorateStringGOOGLE
  {IR(29370, 16), 66}, // 198 DecorationGroup
  {IR(12289, 25), 552}, // 199 DemoteToHelperInvocation
  {IR(12314, 28), 552}, // 200 DemoteToHelperInvocationEXT
  {IR(34016, 23), 345}, // 201 DepthAttachmentReadEXT
  {IR(30455, 4), 137}, // 202 Dot
  {IR(37229, 17), 476}, // 203 EmitMeshTasksEXT
  {IR(31244, 17), 203}, // 204 EmitStreamVertex
  {IR(31220, 11), 201}, // 205 EmitVertex
  {IR(38967, 26), 537}, // 206 EndInvocationInterlockEXT
  {IR(31231, 13), 202}, // 207 EndPrimitive
  {IR(31261, 19), 204}, // 208 EndStreamPrimitive
  {IR(32275, 14), 265}, // 209 EnqueueKernel
  {IR(32261, 14), 264}, // 210 EnqueueMarker
  {IR(35914, 24), 427}, // 211 EnqueueNodePayloadsAMDX
  {IR(28189, 11), 13}, // 212 EntryPoint
  {IR(34646, 19), 378}, // 213 ExecuteCallableKHR
  {IR(38549, 18), 522}, // 214 ExecuteCallableNV
  {IR(28232, 14), 14}, // 215 ExecutionMode
  {IR(33153, 16), 304}, // 216 ExecutionModeId
  {IR(40745, 10), 610}, // 217 ExpectKHR
  {IR(28043, 8), 11}, // 218 ExtInst
  {IR(27983, 14), 10}, // 219 ExtInstImport
  {IR(34583, 26), 375}, // 220 ExtInstWithForwardRefsKHR
  {IR(27973, 10), 9}, // 221 Extension
  {IR(35634, 20), 414}, // 222 ExtractSubArrayQCOM
  {IR(30287, 5), 118}, // 223 FAdd
  {IR(30118, 9), 105}, // 224 FConvert
  {IR(30322, 5), 125}, // 225 FDiv
  {IR(30347, 5), 130}, // 226 FMod
  {IR(30307, 5), 122}, // 227 FMul
  {IR(30274, 8), 116}, // 228 FNegate
  {IR(30784, 10), 168}, // 229 FOrdEqual
  {IR(30862, 16), 174}, // 230 FOrdGreaterThan
  {IR(30934, 21), 178}, // 231 FOrdGreaterThanEqual
  {IR(30834, 13), 172}, // 232 FOrdLessThan
  {IR(30896, 18), 176}, // 233 FOrdLessThanEqual
  {IR(30806, 13), 170}, // 234 FOrdNotEqual
  {IR(14201, 14), 794}, // 235 FPGARegALTERA
  {IR(14215, 13), 794}, // 236 FPGARegINTEL
  {IR(30342, 5), 129}, // 237 FRem
  {IR(30297, 5), 120}, // 238 FSub
  {IR(30794, 12), 169}, // 239 FUnordEqual
  {IR(30878, 18), 175}, // 240 FUnordGreaterThan
  {IR(30955, 23), 179}, // 241 FUnordGreaterThanEqual
  {IR(30847, 15), 173}, // 242 FUnordLessThan
  {IR(30914, 20), 177}, // 243 FUnordLessThanEqual
  {IR(30819, 15), 171}, // 244 FUnordNotEqual
  {IR(37359, 38), 481}, // 245 FetchMicroTriangleVertexBarycentricNV
  {IR(37324, 35), 480}, // 246 FetchMicroTriangleVertexPositionNV
  {IR(35963, 29), 429}, // 247 FinishWritingNodePayloadAMDX
  {IR(47702, 15), 783}, // 248 FixedCosALTERA
  {IR(47717, 14), 783}, // 249 FixedCosINTEL
  {IR(47799, 17), 786}, // 250 FixedCosPiALTERA
  {IR(47816, 16), 786}, // 251 FixedCosPiINTEL
  {IR(47900, 15), 789}, // 252 FixedExpALTERA
  {IR(47915, 14), 789}, // 253 FixedExpINTEL
  {IR(47871, 15), 788}, // 254 FixedLogALTERA
  {IR(47886, 14), 788}, // 255 FixedLogINTEL
  {IR(47607, 17), 780}, // 256 FixedRecipALTERA
  {IR(47624, 16), 780}, // 257 FixedRecipINTEL
  {IR(47640, 17), 781}, // 258 FixedRsqrtALTERA
  {IR(47657, 16), 781}, // 259 FixedRsqrtINTEL
  {IR(47673, 15), 782}, // 260 FixedSinALTERA
  {IR(47731, 18), 784}, // 261 FixedSinCosALTERA
  {IR(47749, 17), 784}, // 262 FixedSinCosINTEL
  {IR(47832, 20), 787}, // 263 FixedSinCosPiALTERA
  {IR(47852, 19), 787}, // 264 FixedSinCosPiINTEL
  {IR(47688, 14), 782}, // 265 FixedSinINTEL
  {IR(47766, 17), 785}, // 266 FixedSinPiALTERA
  {IR(47783, 16), 785}, // 267 FixedSinPiINTEL
  {IR(47576, 16), 779}, // 268 FixedSqrtALTERA
  {IR(47592, 15), 779}, // 269 FixedSqrtINTEL
  {IR(34500, 7), 369}, // 270 FmaKHR
  {IR(35859, 17), 424}, // 271 FragmentFetchAMD
  {IR(35838, 21), 423}, // 272 FragmentMaskFetchAMD
  {IR(27039, 9), 48}, // 273 Function
  {IR(29095, 13), 51}, // 274 FunctionCall
  {IR(29083, 12), 50}, // 275 FunctionEnd
  {IR(29065, 18), 49}, // 276 FunctionParameter
  {IR(40650, 25), 603}, // 277 FunctionPointerCallINTEL
  {IR(31149, 7), 194}, // 278 Fwidth
  {IR(31207, 13), 200}, // 279 FwidthCoarse
  {IR(31174, 11), 197}, // 280 FwidthFine
  {IR(30216, 17), 112}, // 281 GenericCastToPtr
  {IR(30233, 25), 113}, // 282 GenericCastToPtrExplicit
  {IR(29272, 23), 62}, // 283 GenericPtrMemSemantics
  {IR(32513, 16), 276}, // 284 GetDefaultQueue
  {IR(33018, 35), 298}, // 285 GetKernelLocalSizeForSubgroupCount
  {IR(33053, 25), 299}, // 286 GetKernelMaxNumSubgroups
  {IR(32319, 32), 267}, // 287 GetKernelNDrangeMaxSubGroupSize
  {IR(32289, 30), 266}, // 288 GetKernelNDrangeSubGroupCount
  {IR(32374, 40), 269}, // 289 GetKernelPreferredWorkGroupSizeMultiple
  {IR(32351, 23), 268}, // 290 GetKernelWorkGroupSize
  {IR(32145, 18), 259}, // 291 GetMaxPipePackets
  {IR(32127, 18), 258}, // 292 GetNumPipePackets
  {IR(9758, 9), 353}, // 293 GraphARM
  {IR(34168, 17), 351}, // 294 GraphConstantARM
  {IR(34236, 12), 356}, // 295 GraphEndARM
  {IR(34185, 19), 352}, // 296 GraphEntryPointARM
  {IR(34204, 14), 354}, // 297 GraphInputARM
  {IR(34218, 18), 355}, // 298 GraphSetOutputARM
  {IR(31832, 9), 238}, // 299 GroupAll
  {IR(31841, 9), 239}, // 300 GroupAny
  {IR(31801, 15), 236}, // 301 GroupAsyncCopy
  {IR(49790, 19), 846}, // 302 GroupBitwiseAndKHR
  {IR(49809, 18), 847}, // 303 GroupBitwiseOrKHR
  {IR(49827, 19), 848}, // 304 GroupBitwiseXorKHR
  {IR(31850, 15), 240}, // 305 GroupBroadcast
  {IR(32220, 20), 262}, // 306 GroupCommitReadPipe
  {IR(32240, 21), 263}, // 307 GroupCommitWritePipe
  {IR(29386, 14), 67}, // 308 GroupDecorate
  {IR(31908, 10), 242}, // 309 GroupFAdd
  {IR(35677, 23), 416}, // 310 GroupFAddNonUniformAMD
  {IR(31948, 10), 246}, // 311 GroupFMax
  {IR(35769, 23), 420}, // 312 GroupFMaxNonUniformAMD
  {IR(31918, 10), 243}, // 313 GroupFMin
  {IR(35700, 23), 417}, // 314 GroupFMinNonUniformAMD
  {IR(49777, 13), 845}, // 315 GroupFMulKHR
  {IR(31898, 10), 241}, // 316 GroupIAdd
  {IR(35654, 23), 415}, // 317 GroupIAddNonUniformAMD
  {IR(49764, 13), 844}, // 318 GroupIMulKHR
  {IR(49846, 19), 849}, // 319 GroupLogicalAndKHR
  {IR(49865, 18), 850}, // 320 GroupLogicalOrKHR
  {IR(49883, 19), 851}, // 321 GroupLogicalXorKHR
  {IR(29445, 20), 68}, // 322 GroupMemberDecorate
  {IR(33201, 19), 307}, // 323 GroupNonUniformAll
  {IR(33239, 24), 309}, // 324 GroupNonUniformAllEqual
  {IR(33220, 19), 308}, // 325 GroupNonUniformAny
  {IR(6377, 22), 312}, // 326 GroupNonUniformBallot
  {IR(33379, 30), 315}, // 327 GroupNonUniformBallotBitCount
  {IR(33347, 32), 314}, // 328 GroupNonUniformBallotBitExtract
  {IR(33409, 29), 316}, // 329 GroupNonUniformBallotFindLSB
  {IR(33438, 29), 317}, // 330 GroupNonUniformBallotFindMSB
  {IR(33745, 26), 332}, // 331 GroupNonUniformBitwiseAnd
  {IR(33771, 25), 333}, // 332 GroupNonUniformBitwiseOr
  {IR(33796, 26), 334}, // 333 GroupNonUniformBitwiseXor
  {IR(33263, 25), 310}, // 334 GroupNonUniformBroadcast
  {IR(33288, 30), 311}, // 335 GroupNonUniformBroadcastFirst
  {IR(33180, 21), 306}, // 336 GroupNonUniformElect
  {IR(33565, 20), 323}, // 337 GroupNonUniformFAdd
  {IR(33725, 20), 331}, // 338 GroupNonUniformFMax
  {IR(33665, 20), 328}, // 339 GroupNonUniformFMin
  {IR(33605, 20), 325}, // 340 GroupNonUniformFMul
  {IR(33545, 20), 322}, // 341 GroupNonUniformIAdd
  {IR(33585, 20), 324}, // 342 GroupNonUniformIMul
  {IR(33318, 29), 313}, // 343 GroupNonUniformInverseBallot
  {IR(33822, 26), 335}, // 344 GroupNonUniformLogicalAnd
  {IR(33848, 25), 336}, // 345 GroupNonUniformLogicalOr
  {IR(33873, 26), 337}, // 346 GroupNonUniformLogicalXor
  {IR(37264, 27), 478}, // 347 GroupNonUniformPartitionNV
  {IR(36084, 26), 434}, // 348 GroupNonUniformQuadAllKHR
  {IR(36110, 26), 435}, // 349 GroupNonUniformQuadAnyKHR
  {IR(33899, 29), 338}, // 350 GroupNonUniformQuadBroadcast
  {IR(33928, 24), 339}, // 351 GroupNonUniformQuadSwap
  {IR(14440, 25), 373}, // 352 GroupNonUniformRotateKHR
  {IR(33685, 20), 329}, // 353 GroupNonUniformSMax
  {IR(33625, 20), 326}, // 354 GroupNonUniformSMin
  {IR(9467, 23), 318}, // 355 GroupNonUniformShuffle
  {IR(33518, 27), 321}, // 356 GroupNonUniformShuffleDown
  {IR(33493, 25), 320}, // 357 GroupNonUniformShuffleUp
  {IR(33467, 26), 319}, // 358 GroupNonUniformShuffleXor
  {IR(33705, 20), 330}, // 359 GroupNonUniformUMax
  {IR(33645, 20), 327}, // 360 GroupNonUniformUMin
  {IR(32163, 28), 260}, // 361 GroupReserveReadPipePackets
  {IR(32191, 29), 261}, // 362 GroupReserveWritePipePackets
  {IR(31968, 10), 248}, // 363 GroupSMax
  {IR(35815, 23), 422}, // 364 GroupSMaxNonUniformAMD
  {IR(31938, 10), 245}, // 365 GroupSMin
  {IR(35746, 23), 419}, // 366 GroupSMinNonUniformAMD
  {IR(31958, 10), 247}, // 367 GroupUMax
  {IR(35792, 23), 421}, // 368 GroupUMaxNonUniformAMD
  {IR(31928, 10), 244}, // 369 GroupUMin
  {IR(35723, 23), 418}, // 370 GroupUMinNonUniformAMD
  {IR(31816, 16), 237}, // 371 GroupWaitEvents
  {IR(37893, 26), 499}, // 372 HitObjectExecuteShaderEXT
  {IR(36571, 25), 451}, // 373 HitObjectExecuteShaderNV
  {IR(37946, 26), 501}, // 374 HitObjectGetAttributesEXT
  {IR(36622, 25), 453}, // 375 HitObjectGetAttributesNV
  {IR(38625, 24), 524}, // 376 HitObjectGetClusterIdNV
  {IR(37919, 27), 500}, // 377 HitObjectGetCurrentTimeEXT
  {IR(36596, 26), 452}, // 378 HitObjectGetCurrentTimeNV
  {IR(38025, 29), 504}, // 379 HitObjectGetGeometryIndexEXT
  {IR(36698, 28), 456}, // 380 HitObjectGetGeometryIndexNV
  {IR(37972, 23), 502}, // 381 HitObjectGetHitKindEXT
  {IR(36647, 22), 454}, // 382 HitObjectGetHitKindNV
  {IR(38080, 35), 506}, // 383 HitObjectGetInstanceCustomIndexEXT
  {IR(36751, 34), 458}, // 384 HitObjectGetInstanceCustomIndexNV
  {IR(38054, 26), 505}, // 385 HitObjectGetInstanceIdEXT
  {IR(36726, 25), 457}, // 386 HitObjectGetInstanceIdNV
  {IR(37526, 51), 487}, // 387 HitObjectGetIntersectionTriangleVertexPositionsEXT
  {IR(40017, 27), 572}, // 388 HitObjectGetLSSPositionsNV
  {IR(40044, 23), 573}, // 389 HitObjectGetLSSRadiiNV
  {IR(38146, 34), 508}, // 390 HitObjectGetObjectRayDirectionEXT
  {IR(36283, 33), 441}, // 391 HitObjectGetObjectRayDirectionNV
  {IR(38115, 31), 507}, // 392 HitObjectGetObjectRayOriginEXT
  {IR(36316, 30), 442}, // 393 HitObjectGetObjectRayOriginNV
  {IR(38243, 29), 511}, // 394 HitObjectGetObjectToWorldEXT
  {IR(36255, 28), 440}, // 395 HitObjectGetObjectToWorldNV
  {IR(37995, 30), 503}, // 396 HitObjectGetPrimitiveIndexEXT
  {IR(36669, 29), 455}, // 397 HitObjectGetPrimitiveIndexNV
  {IR(37577, 24), 488}, // 398 HitObjectGetRayFlagsEXT
  {IR(38301, 23), 513}, // 399 HitObjectGetRayTMaxEXT
  {IR(36846, 22), 461}, // 400 HitObjectGetRayTMaxNV
  {IR(38649, 23), 525}, // 401 HitObjectGetRayTMinEXT
  {IR(36868, 22), 462}, // 402 HitObjectGetRayTMinNV
  {IR(38672, 45), 526}, // 403 HitObjectGetShaderBindingTableRecordIndexEXT
  {IR(36411, 44), 445}, // 404 HitObjectGetShaderBindingTableRecordIndexNV
  {IR(38717, 40), 527}, // 405 HitObjectGetShaderRecordBufferHandleEXT
  {IR(36372, 39), 444}, // 406 HitObjectGetShaderRecordBufferHandleNV
  {IR(39961, 29), 570}, // 407 HitObjectGetSpherePositionNV
  {IR(39990, 27), 571}, // 408 HitObjectGetSphereRadiusNV
  {IR(38180, 33), 509}, // 409 HitObjectGetWorldRayDirectionEXT
  {IR(36785, 32), 459}, // 410 HitObjectGetWorldRayDirectionNV
  {IR(38213, 30), 510}, // 411 HitObjectGetWorldRayOriginEXT
  {IR(36817, 29), 460}, // 412 HitObjectGetWorldRayOriginNV
  {IR(38272, 29), 512}, // 413 HitObjectGetWorldToObjectEXT
  {IR(36227, 28), 439}, // 414 HitObjectGetWorldToObjectNV
  {IR(38757, 20), 528}, // 415 HitObjectIsEmptyEXT
  {IR(36890, 19), 463}, // 416 HitObjectIsEmptyNV
  {IR(38777, 18), 529}, // 417 HitObjectIsHitEXT
  {IR(36909, 17), 464}, // 418 HitObjectIsHitNV
  {IR(40090, 20), 575}, // 419 HitObjectIsLSSHitNV
  {IR(38795, 19), 530}, // 420 HitObjectIsMissEXT
  {IR(36926, 18), 465}, // 421 HitObjectIsMissNV
  {IR(40067, 23), 574}, // 422 HitObjectIsSphereHitNV
  {IR(37869, 24), 498}, // 423 HitObjectRecordEmptyEXT
  {IR(36455, 23), 446}, // 424 HitObjectRecordEmptyNV
  {IR(37446, 28), 484}, // 425 HitObjectRecordFromQueryEXT
  {IR(36136, 27), 436}, // 426 HitObjectRecordHitMotionNV
  {IR(36498, 21), 448}, // 427 HitObjectRecordHitNV
  {IR(36163, 36), 437}, // 428 HitObjectRecordHitWithIndexMotionNV
  {IR(36519, 30), 449}, // 429 HitObjectRecordHitWithIndexNV
  {IR(37474, 23), 485}, // 430 HitObjectRecordMissEXT
  {IR(37497, 29), 486}, // 431 HitObjectRecordMissMotionEXT
  {IR(36199, 28), 438}, // 432 HitObjectRecordMissMotionNV
  {IR(36549, 22), 450}, // 433 HitObjectRecordMissNV
  {IR(37646, 33), 490}, // 434 HitObjectReorderExecuteShaderEXT
  {IR(37601, 45), 489}, // 435 HitObjectSetShaderBindingTableRecordIndexEXT
  {IR(37711, 38), 492}, // 436 HitObjectTraceMotionReorderExecuteEXT
  {IR(37821, 21), 496}, // 437 HitObjectTraceRayEXT
  {IR(37842, 27), 497}, // 438 HitObjectTraceRayMotionEXT
  {IR(36346, 26), 443}, // 439 HitObjectTraceRayMotionNV
  {IR(36478, 20), 447}, // 440 HitObjectTraceRayNV
  {IR(37679, 32), 491}, // 441 HitObjectTraceReorderExecuteEXT
  {IR(30282, 5), 117}, // 442 IAdd
  {IR(30459, 10), 138}, // 443 IAddCarry
  {IR(40469, 13), 592}, // 444 IAddSatINTEL
  {IR(40495, 14), 594}, // 445 IAverageINTEL
  {IR(40523, 21), 596}, // 446 IAverageRoundedINTEL
  {IR(30655, 7), 158}, // 447 IEqual
  {IR(30302, 5), 121}, // 448 IMul
  {IR(40591, 15), 600}, // 449 IMul32x16INTEL
  {IR(30662, 10), 159}, // 450 INotEqual
  {IR(30292, 5), 119}, // 451 ISub
  {IR(30469, 11), 139}, // 452 ISubBorrow
  {IR(40565, 13), 598}, // 453 ISubSatINTEL
  {IR(34700, 22), 380}, // 454 IgnoreIntersectionKHR
  {IR(38367, 21), 515}, // 455 IgnoreIntersectionNV
  {IR(27083, 6), 91}, // 456 Image
  {IR(35547, 29), 411}, // 457 ImageBlockMatchGatherSADQCOM
  {IR(35518, 29), 410}, // 458 ImageBlockMatchGatherSSDQCOM
  {IR(35420, 23), 406}, // 459 ImageBlockMatchSADQCOM
  {IR(35397, 23), 405}, // 460 ImageBlockMatchSSDQCOM
  {IR(35489, 29), 409}, // 461 ImageBlockMatchWindowSADQCOM
  {IR(35460, 29), 408}, // 462 ImageBlockMatchWindowSSDQCOM
  {IR(35378, 19), 404}, // 463 ImageBoxFilterQCOM
  {IR(29900, 16), 88}, // 464 ImageDrefGather
  {IR(29877, 11), 86}, // 465 ImageFetch
  {IR(29888, 12), 87}, // 466 ImageGather
  {IR(29937, 17), 92}, // 467 ImageQueryFormat
  {IR(30017, 17), 97}, // 468 ImageQueryLevels
  {IR(30003, 14), 96}, // 469 ImageQueryLod
  {IR(29954, 16), 93}, // 470 ImageQueryOrder
  {IR(30034, 18), 98}, // 471 ImageQuerySamples
  {IR(29988, 15), 95}, // 472 ImageQuerySize
  {IR(29970, 18), 94}, // 473 ImageQuerySizeLod
  {IR(29916, 10), 89}, // 474 ImageRead
  {IR(29734, 27), 81}, // 475 ImageSampleDrefExplicitLod
  {IR(29707, 27), 80}, // 476 ImageSampleDrefImplicitLod
  {IR(29684, 23), 79}, // 477 ImageSampleExplicitLod
  {IR(37013, 23), 469}, // 478 ImageSampleFootprintNV
  {IR(29638, 23), 78}, // 479 ImageSampleImplicitLod
  {IR(29846, 31), 85}, // 480 ImageSampleProjDrefExplicitLod
  {IR(29815, 31), 84}, // 481 ImageSampleProjDrefImplicitLod
  {IR(29788, 27), 83}, // 482 ImageSampleProjExplicitLod
  {IR(29761, 27), 82}, // 483 ImageSampleProjImplicitLod
  {IR(35354, 24), 403}, // 484 ImageSampleWeightedQCOM
  {IR(32841, 22), 288}, // 485 ImageSparseDrefGather
  {IR(32806, 17), 286}, // 486 ImageSparseFetch
  {IR(32823, 18), 287}, // 487 ImageSparseGather
  {IR(32933, 16), 293}, // 488 ImageSparseRead
  {IR(32633, 33), 281}, // 489 ImageSparseSampleDrefExplicitLod
  {IR(32600, 33), 280}, // 490 ImageSparseSampleDrefImplicitLod
  {IR(32571, 29), 279}, // 491 ImageSparseSampleExplicitLod
  {IR(32542, 29), 278}, // 492 ImageSparseSampleImplicitLod
  {IR(32769, 37), 285}, // 493 ImageSparseSampleProjDrefExplicitLod
  {IR(32732, 37), 284}, // 494 ImageSparseSampleProjDrefImplicitLod
  {IR(32699, 33), 283}, // 495 ImageSparseSampleProjExplicitLod
  {IR(32666, 33), 282}, // 496 ImageSparseSampleProjImplicitLod
  {IR(32863, 26), 289}, // 497 ImageSparseTexelsResident
  {IR(29117, 18), 53}, // 498 ImageTexelPointer
  {IR(29926, 11), 90}, // 499 ImageWrite
  {IR(29225, 20), 59}, // 500 InBoundsAccessChain
  {IR(29295, 23), 63}, // 501 InBoundsPtrAccessChain
  {IR(30526, 9), 146}, // 502 IsFinite
  {IR(39452, 22), 553}, // 503 IsHelperInvocationEXT
  {IR(30520, 6), 145}, // 504 IsInf
  {IR(30514, 6), 144}, // 505 IsNan
  {IR(36019, 23), 431}, // 506 IsNodePayloadValidAMDX
  {IR(30535, 9), 147}, // 507 IsNormal
  {IR(32455, 13), 273}, // 508 IsValidEvent
  {IR(32110, 17), 257}, // 509 IsValidReserveId
  {IR(31738, 5), 230}, // 510 Kill
  {IR(31655, 6), 226}, // 511 Label
  {IR(30555, 14), 149}, // 512 LessOrGreater
  {IR(31774, 14), 234}, // 513 LifetimeStart
  {IR(31788, 13), 235}, // 514 LifetimeStop
  {IR(27968, 5), 8}, // 515 Line
  {IR(29175, 5), 54}, // 516 Load
  {IR(30626, 11), 155}, // 517 LogicalAnd
  {IR(30587, 13), 152}, // 518 LogicalEqual
  {IR(30637, 11), 156}, // 519 LogicalNot
  {IR(30600, 16), 153}, // 520 LogicalNotEqual
  {IR(30616, 10), 154}, // 521 LogicalOr
  {IR(47494, 17), 775}, // 522 LoopControlINTEL
  {IR(31595, 10), 224}, // 523 LoopMerge
  {IR(49920, 18), 853}, // 524 MaskedGatherINTEL
  {IR(49938, 19), 854}, // 525 MaskedScatterINTEL
  {IR(30424, 18), 135}, // 526 MatrixTimesMatrix
  {IR(30370, 18), 132}, // 527 MatrixTimesScalar
  {IR(30406, 18), 134}, // 528 MatrixTimesVector
  {IR(29355, 15), 65}, // 529 MemberDecorate
  {IR(40791, 21), 612}, // 530 MemberDecorateString
  {IR(40812, 27), 612}, // 531 MemberDecorateStringGOOGLE
  {IR(27950, 11), 6}, // 532 MemberName
  {IR(31332, 14), 206}, // 533 MemoryBarrier
  {IR(28115, 12), 12}, // 534 MemoryModel
  {IR(33118, 19), 302}, // 535 MemoryNamedBarrier
  {IR(33137, 16), 303}, // 536 ModuleProcessed
  {IR(27945, 5), 5}, // 537 Name
  {IR(33095, 23), 301}, // 538 NamedBarrierInitialize
  {IR(32889, 7), 290}, // 539 NoLine
  {IR(35992, 27), 430}, // 540 NodePayloadArrayLengthAMDX
  {IR(27741, 4), 0}, // 541 Nop
  {IR(31066, 4), 186}, // 542 Not
  {IR(30569, 8), 150}, // 543 Ordered
  {IR(30442, 13), 136}, // 544 OuterProduct
  {IR(31561, 4), 223}, // 545 Phi
  {IR(29245, 15), 60}, // 546 PtrAccessChain
  {IR(47929, 30), 790}, // 547 PtrCastToCrossWorkgroupALTERA
  {IR(47959, 29), 790}, // 548 PtrCastToCrossWorkgroupINTEL
  {IR(30199, 17), 111}, // 549 PtrCastToGeneric
  {IR(33985, 8), 343}, // 550 PtrDiff
  {IR(33964, 9), 341}, // 551 PtrEqual
  {IR(33973, 12), 342}, // 552 PtrNotEqual
  {IR(30127, 14), 106}, // 553 QuantizeToF16
  {IR(39757, 17), 564}, // 554 RawAccessChainNV
  {IR(35273, 31), 400}, // 555 RayQueryConfirmIntersectionKHR
  {IR(35241, 32), 399}, // 556 RayQueryGenerateIntersectionKHR
  {IR(38602, 23), 523}, // 557 RayQueryGetClusterIdNV
  {IR(48441, 39), 803}, // 558 RayQueryGetIntersectionBarycentricsKHR
  {IR(48516, 46), 805}, // 559 RayQueryGetIntersectionCandidateAABBOpaqueKHR
  {IR(38567, 35), 523}, // 560 RayQueryGetIntersectionClusterIdNV
  {IR(48480, 36), 804}, // 561 RayQueryGetIntersectionFrontFaceKHR
  {IR(48360, 40), 801}, // 562 RayQueryGetIntersectionGeometryIndexKHR
  {IR(48212, 46), 798}, // 563 RayQueryGetIntersectionInstanceCustomIndexKHR
  {IR(48258, 37), 799}, // 564 RayQueryGetIntersectionInstanceIdKHR
  {IR(48295, 65), 800}, // 565 RayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR
  {IR(39924, 37), 569}, // 566 RayQueryGetIntersectionLSSHitValueNV
  {IR(39852, 38), 567}, // 567 RayQueryGetIntersectionLSSPositionsNV
  {IR(39890, 34), 568}, // 568 RayQueryGetIntersectionLSSRadiiNV
  {IR(48562, 45), 806}, // 569 RayQueryGetIntersectionObjectRayDirectionKHR
  {IR(48607, 42), 807}, // 570 RayQueryGetIntersectionObjectRayOriginKHR
  {IR(48710, 40), 810}, // 571 RayQueryGetIntersectionObjectToWorldKHR
  {IR(48400, 41), 802}, // 572 RayQueryGetIntersectionPrimitiveIndexKHR
  {IR(39774, 40), 565}, // 573 RayQueryGetIntersectionSpherePositionNV
  {IR(39814, 38), 566}, // 574 RayQueryGetIntersectionSphereRadiusNV
  {IR(48184, 28), 797}, // 575 RayQueryGetIntersectionTKHR
  {IR(38442, 50), 520}, // 576 RayQueryGetIntersectionTriangleVertexPositionsKHR
  {IR(35323, 31), 402}, // 577 RayQueryGetIntersectionTypeKHR
  {IR(48750, 40), 811}, // 578 RayQueryGetIntersectionWorldToObjectKHR
  {IR(48161, 23), 796}, // 579 RayQueryGetRayFlagsKHR
  {IR(48139, 22), 795}, // 580 RayQueryGetRayTMinKHR
  {IR(48649, 32), 808}, // 581 RayQueryGetWorldRayDirectionKHR
  {IR(48681, 29), 809}, // 582 RayQueryGetWorldRayOriginKHR
  {IR(35198, 22), 397}, // 583 RayQueryInitializeKHR
  {IR(40132, 19), 577}, // 584 RayQueryIsLSSHitNV
  {IR(40110, 22), 576}, // 585 RayQueryIsSphereHitNV
  {IR(35304, 19), 401}, // 586 RayQueryProceedKHR
  {IR(35220, 21), 398}, // 587 RayQueryTerminateKHR
  {IR(35876, 13), 425}, // 588 ReadClockKHR
  {IR(31978, 9), 249}, // 589 ReadPipe
  {IR(48047, 23), 792}, // 590 ReadPipeBlockingALTERA
  {IR(48070, 22), 792}, // 591 ReadPipeBlockingINTEL
  {IR(32426, 13), 271}, // 592 ReleaseEvent
  {IR(37766, 25), 494}, // 593 ReorderThreadWithHintEXT
  {IR(36973, 24), 467}, // 594 ReorderThreadWithHintNV
  {IR(37791, 30), 495}, // 595 ReorderThreadWithHitObjectEXT
  {IR(36944, 29), 466}, // 596 ReorderThreadWithHitObjectNV
  {IR(38324, 22), 514}, // 597 ReportIntersectionKHR
  {IR(38346, 21), 514}, // 598 ReportIntersectionNV
  {IR(32032, 23), 253}, // 599 ReserveReadPipePackets
  {IR(32055, 24), 254}, // 600 ReserveWritePipePackets
  {IR(31997, 17), 251}, // 601 ReservedReadPipe
  {IR(32014, 18), 252}, // 602 ReservedWritePipe
  {IR(46021, 19), 733}, // 603 RestoreMemoryINTEL
  {IR(32414, 12), 270}, // 604 RetainEvent
  {IR(31743, 7), 231}, // 605 Return
  {IR(31750, 12), 232}, // 606 ReturnValue
  {IR(49902, 18), 852}, // 607 RoundFToTF32INTEL
  {IR(30109, 9), 104}, // 608 SConvert
  {IR(30317, 5), 124}, // 609 SDiv
  {IR(34785, 5), 382}, // 610 SDot
  {IR(34826, 11), 385}, // 611 SDotAccSat
  {IR(34837, 14), 385}, // 612 SDotAccSatKHR
  {IR(34790, 8), 382}, // 613 SDotKHR
  {IR(30685, 13), 161}, // 614 SGreaterThan
  {IR(30716, 18), 163}, // 615 SGreaterThanEqual
  {IR(30744, 10), 165}, // 616 SLessThan
  {IR(30769, 15), 167}, // 617 SLessThanEqual
  {IR(30337, 5), 128}, // 618 SMod
  {IR(30493, 13), 141}, // 619 SMulExtended
  {IR(30266, 8), 115}, // 620 SNegate
  {IR(30332, 5), 127}, // 621 SRem
  {IR(34811, 6), 384}, // 622 SUDot
  {IR(34876, 12), 387}, // 623 SUDotAccSat
  {IR(34888, 15), 387}, // 624 SUDotAccSatKHR
  {IR(34817, 9), 384}, // 625 SUDotKHR
  {IR(29593, 13), 77}, // 626 SampledImage
  {IR(39676, 29), 563}, // 627 SamplerImageAddressingModeNV
  {IR(30155, 15), 108}, // 628 SatConvertSToU
  {IR(30170, 15), 109}, // 629 SatConvertUToS
  {IR(46005, 16), 732}, // 630 SaveMemoryINTEL
  {IR(30648, 7), 157}, // 631 Select
  {IR(31640, 15), 225}, // 632 SelectionMerge
  {IR(37246, 18), 477}, // 633 SetMeshOutputsEXT
  {IR(32468, 19), 274}, // 634 SetUserEventStatus
  {IR(31017, 17), 182}, // 635 ShiftLeftLogical
  {IR(30996, 21), 181}, // 636 ShiftRightArithmetic
  {IR(30978, 18), 180}, // 637 ShiftRightLogical
  {IR(30544, 11), 148}, // 638 SignBitSet
  {IR(32949, 7), 294}, // 639 SizeOf
  {IR(27922, 7), 3}, // 640 Source
  {IR(27803, 16), 2}, // 641 SourceContinued
  {IR(27929, 16), 4}, // 642 SourceExtension
  {IR(28940, 13), 45}, // 643 SpecConstant
  {IR(49640, 30), 841}, // 644 SpecConstantArchitectureINTEL
  {IR(49707, 30), 842}, // 645 SpecConstantCapabilitiesINTEL
  {IR(28953, 22), 46}, // 646 SpecConstantComposite
  {IR(48884, 36), 816}, // 647 SpecConstantCompositeContinuedINTEL
  {IR(35117, 34), 394}, // 648 SpecConstantCompositeReplicateEXT
  {IR(28922, 18), 44}, // 649 SpecConstantFalse
  {IR(29016, 15), 47}, // 650 SpecConstantOp
  {IR(36061, 23), 433}, // 651 SpecConstantStringAMDX
  {IR(49616, 24), 840}, // 652 SpecConstantTargetINTEL
  {IR(28905, 17), 43}, // 653 SpecConstantTrue
  {IR(34039, 25), 346}, // 654 StencilAttachmentReadEXT
  {IR(29180, 6), 55}, // 655 Store
  {IR(27961, 7), 7}, // 656 String
  {IR(49305, 25), 829}, // 657 Subgroup2DBlockLoadINTEL
  {IR(49330, 34), 830}, // 658 Subgroup2DBlockLoadTransformINTEL
  {IR(49364, 34), 831}, // 659 Subgroup2DBlockLoadTransposeINTEL
  {IR(49398, 29), 832}, // 660 Subgroup2DBlockPrefetchINTEL
  {IR(49427, 26), 833}, // 661 Subgroup2DBlockStoreINTEL
  {IR(34537, 20), 372}, // 662 SubgroupAllEqualKHR
  {IR(34507, 15), 370}, // 663 SubgroupAllKHR
  {IR(34522, 15), 371}, // 664 SubgroupAnyKHR
  {IR(44523, 30), 696}, // 665 SubgroupAvcBmeInitializeINTEL
  {IR(44493, 30), 695}, // 666 SubgroupAvcFmeInitializeINTEL
  {IR(42928, 35), 665}, // 667 SubgroupAvcImeAdjustRefOffsetINTEL
  {IR(42963, 39), 666}, // 668 SubgroupAvcImeConvertToMcePayloadINTEL
  {IR(43604, 38), 679}, // 669 SubgroupAvcImeConvertToMceResultINTEL
  {IR(43227, 45), 672}, // 670 SubgroupAvcImeEvaluateWithDualReferenceINTEL
  {IR(43327, 53), 674}, // 671 SubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL
  {IR(43548, 56), 678}, // 672 SubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL
  {IR(43436, 54), 676}, // 673 SubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL
  {IR(43180, 47), 671}, // 674 SubgroupAvcImeEvaluateWithSingleReferenceINTEL
  {IR(43272, 55), 673}, // 675 SubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL
  {IR(43490, 58), 677}, // 676 SubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL
  {IR(43380, 56), 675}, // 677 SubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL
  {IR(44236, 36), 690}, // 678 SubgroupAvcImeGetBorderReachedINTEL
  {IR(43688, 44), 681}, // 679 SubgroupAvcImeGetDualReferenceStreaminINTEL
  {IR(43642, 46), 680}, // 680 SubgroupAvcImeGetSingleReferenceStreaminINTEL
  {IR(44103, 66), 688}, // 681 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL
  {IR(44035, 68), 687}, // 682 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL
  {IR(44169, 67), 689}, // 683 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL
  {IR(43898, 68), 685}, // 684 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL
  {IR(43828, 70), 684}, // 685 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL
  {IR(43966, 69), 686}, // 686 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL
  {IR(44272, 48), 691}, // 687 SubgroupAvcImeGetTruncatedSearchIndicationINTEL
  {IR(44320, 59), 692}, // 688 SubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL
  {IR(44437, 56), 694}, // 689 SubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL
  {IR(44379, 58), 693}, // 690 SubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL
  {IR(42791, 30), 661}, // 691 SubgroupAvcImeInitializeINTEL
  {IR(42895, 33), 664}, // 692 SubgroupAvcImeRefWindowSizeINTEL
  {IR(42859, 36), 663}, // 693 SubgroupAvcImeSetDualReferenceINTEL
  {IR(43092, 54), 669}, // 694 SubgroupAvcImeSetEarlySearchTerminationThresholdINTEL
  {IR(43002, 43), 667}, // 695 SubgroupAvcImeSetMaxMotionVectorCountINTEL
  {IR(42821, 38), 662}, // 696 SubgroupAvcImeSetSingleReferenceINTEL
  {IR(43045, 47), 668}, // 697 SubgroupAvcImeSetUnidirectionalMixDisableINTEL
  {IR(43146, 34), 670}, // 698 SubgroupAvcImeSetWeightedSadINTEL
  {IR(43781, 47), 683}, // 699 SubgroupAvcImeStripDualReferenceStreamoutINTEL
  {IR(43732, 49), 682}, // 700 SubgroupAvcImeStripSingleReferenceStreamoutINTEL
  {IR(42181, 39), 646}, // 701 SubgroupAvcMceConvertToImePayloadINTEL
  {IR(42220, 38), 647}, // 702 SubgroupAvcMceConvertToImeResultINTEL
  {IR(42258, 39), 648}, // 703 SubgroupAvcMceConvertToRefPayloadINTEL
  {IR(42297, 38), 649}, // 704 SubgroupAvcMceConvertToRefResultINTEL
  {IR(42335, 39), 650}, // 705 SubgroupAvcMceConvertToSicPayloadINTEL
  {IR(42374, 38), 651}, // 706 SubgroupAvcMceConvertToSicResultINTEL
  {IR(42487, 43), 654}, // 707 SubgroupAvcMceGetBestInterDistortionsINTEL
  {IR(41619, 50), 635}, // 708 SubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL
  {IR(41217, 60), 627}, // 709 SubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL
  {IR(41417, 51), 631}, // 710 SubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL
  {IR(41563, 56), 634}, // 711 SubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL
  {IR(41330, 47), 629}, // 712 SubgroupAvcMceGetDefaultInterShapePenaltyINTEL
  {IR(41918, 56), 641}, // 713 SubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL
  {IR(41817, 50), 639}, // 714 SubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL
  {IR(41512, 51), 633}, // 715 SubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL
  {IR(41721, 49), 637}, // 716 SubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL
  {IR(41669, 52), 636}, // 717 SubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL
  {IR(41867, 51), 640}, // 718 SubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL
  {IR(42606, 38), 657}, // 719 SubgroupAvcMceGetInterDirectionsINTEL
  {IR(42448, 39), 653}, // 720 SubgroupAvcMceGetInterDistortionsINTEL
  {IR(42530, 38), 655}, // 721 SubgroupAvcMceGetInterMajorShapeINTEL
  {IR(42568, 38), 656}, // 722 SubgroupAvcMceGetInterMinorShapeINTEL
  {IR(42644, 45), 658}, // 723 SubgroupAvcMceGetInterMotionVectorCountINTEL
  {IR(42689, 40), 659}, // 724 SubgroupAvcMceGetInterReferenceIdsINTEL
  {IR(42729, 62), 660}, // 725 SubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL
  {IR(42412, 36), 652}, // 726 SubgroupAvcMceGetMotionVectorsINTEL
  {IR(41974, 33), 642}, // 727 SubgroupAvcMceSetAcOnlyHaarINTEL
  {IR(42120, 61), 645}, // 728 SubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL
  {IR(41277, 53), 628}, // 729 SubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL
  {IR(41468, 44), 632}, // 730 SubgroupAvcMceSetInterDirectionPenaltyINTEL
  {IR(41377, 40), 630}, // 731 SubgroupAvcMceSetInterShapePenaltyINTEL
  {IR(41770, 47), 638}, // 732 SubgroupAvcMceSetMotionVectorCostFunctionINTEL
  {IR(42059, 61), 644}, // 733 SubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL
  {IR(42007, 52), 643}, // 734 SubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL
  {IR(44553, 39), 697}, // 735 SubgroupAvcRefConvertToMcePayloadINTEL
  {IR(44875, 38), 704}, // 736 SubgroupAvcRefConvertToMceResultINTEL
  {IR(44728, 45), 701}, // 737 SubgroupAvcRefEvaluateWithDualReferenceINTEL
  {IR(44773, 46), 702}, // 738 SubgroupAvcRefEvaluateWithMultiReferenceINTEL
  {IR(44819, 56), 703}, // 739 SubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL
  {IR(44681, 47), 700}, // 740 SubgroupAvcRefEvaluateWithSingleReferenceINTEL
  {IR(44592, 46), 698}, // 741 SubgroupAvcRefSetBidirectionalMixDisableINTEL
  {IR(44638, 43), 699}, // 742 SubgroupAvcRefSetBilinearFilterEnableINTEL
  {IR(45011, 42), 708}, // 743 SubgroupAvcSicConfigureIpeLumaChromaINTEL
  {IR(44975, 36), 707}, // 744 SubgroupAvcSicConfigureIpeLumaINTEL
  {IR(44943, 32), 706}, // 745 SubgroupAvcSicConfigureSkcINTEL
  {IR(45092, 39), 710}, // 746 SubgroupAvcSicConvertToMcePayloadINTEL
  {IR(45632, 38), 722}, // 747 SubgroupAvcSicConvertToMceResultINTEL
  {IR(45407, 31), 717}, // 748 SubgroupAvcSicEvaluateIpeINTEL
  {IR(45485, 45), 719}, // 749 SubgroupAvcSicEvaluateWithDualReferenceINTEL
  {IR(45530, 46), 720}, // 750 SubgroupAvcSicEvaluateWithMultiReferenceINTEL
  {IR(45576, 56), 721}, // 751 SubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL
  {IR(45438, 47), 718}, // 752 SubgroupAvcSicEvaluateWithSingleReferenceINTEL
  {IR(45749, 46), 725}, // 753 SubgroupAvcSicGetBestIpeChromaDistortionINTEL
  {IR(45705, 44), 724}, // 754 SubgroupAvcSicGetBestIpeLumaDistortionINTEL
  {IR(45970, 35), 730}, // 755 SubgroupAvcSicGetInterRawSadsINTEL
  {IR(45836, 36), 727}, // 756 SubgroupAvcSicGetIpeChromaModeINTEL
  {IR(45670, 35), 723}, // 757 SubgroupAvcSicGetIpeLumaShapeINTEL
  {IR(45053, 39), 709}, // 758 SubgroupAvcSicGetMotionVectorMaskINTEL
  {IR(45795, 41), 726}, // 759 SubgroupAvcSicGetPackedIpeLumaModesINTEL
  {IR(45872, 50), 728}, // 760 SubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL
  {IR(45922, 48), 729}, // 761 SubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL
  {IR(44913, 30), 705}, // 762 SubgroupAvcSicInitializeINTEL
  {IR(45273, 43), 714}, // 763 SubgroupAvcSicSetBilinearFilterEnableINTEL
  {IR(45364, 43), 716}, // 764 SubgroupAvcSicSetBlockBasedRawSkipSadINTEL
  {IR(45223, 50), 713}, // 765 SubgroupAvcSicSetIntraChromaModeCostFunctionINTEL
  {IR(45175, 48), 712}, // 766 SubgroupAvcSicSetIntraLumaModeCostFunctionINTEL
  {IR(45131, 44), 711}, // 767 SubgroupAvcSicSetIntraLumaShapePenaltyINTEL
  {IR(45316, 48), 715}, // 768 SubgroupAvcSicSetSkcForwardTransformEnableINTEL
  {IR(6138, 18), 363}, // 769 SubgroupBallotKHR
  {IR(49278, 27), 828}, // 770 SubgroupBlockPrefetchINTEL
  {IR(40223, 23), 582}, // 771 SubgroupBlockReadINTEL
  {IR(40246, 24), 583}, // 772 SubgroupBlockWriteINTEL
  {IR(34374, 27), 364}, // 773 SubgroupFirstInvocationKHR
  {IR(40270, 28), 584}, // 774 SubgroupImageBlockReadINTEL
  {IR(40298, 29), 585}, // 775 SubgroupImageBlockWriteINTEL
  {IR(40327, 33), 586}, // 776 SubgroupImageMediaBlockReadINTEL
  {IR(40360, 34), 587}, // 777 SubgroupImageMediaBlockWriteINTEL
  {IR(15131, 38), 834}, // 778 SubgroupMatrixMultiplyAccumulateINTEL
  {IR(34557, 26), 374}, // 779 SubgroupReadInvocationKHR
  {IR(40151, 25), 579}, // 780 SubgroupShuffleDownINTEL
  {IR(12787, 21), 578}, // 781 SubgroupShuffleINTEL
  {IR(40176, 23), 580}, // 782 SubgroupShuffleUpINTEL
  {IR(40199, 24), 581}, // 783 SubgroupShuffleXorINTEL
  {IR(31731, 7), 229}, // 784 Switch
  {IR(49092, 24), 824}, // 785 TaskSequenceAsyncALTERA
  {IR(49116, 23), 824}, // 786 TaskSequenceAsyncINTEL
  {IR(49043, 25), 823}, // 787 TaskSequenceCreateALTERA
  {IR(49068, 24), 823}, // 788 TaskSequenceCreateINTEL
  {IR(49139, 22), 825}, // 789 TaskSequenceGetALTERA
  {IR(49161, 21), 825}, // 790 TaskSequenceGetINTEL
  {IR(49182, 26), 826}, // 791 TaskSequenceReleaseALTERA
  {IR(49208, 25), 826}, // 792 TaskSequenceReleaseINTEL
  {IR(39494, 27), 555}, // 793 TensorLayoutSetBlockSizeNV
  {IR(39358, 28), 548}, // 794 TensorLayoutSetClampValueNV
  {IR(39287, 27), 545}, // 795 TensorLayoutSetDimensionNV
  {IR(39314, 24), 546}, // 796 TensorLayoutSetStrideNV
  {IR(39338, 20), 547}, // 797 TensorLayoutSliceNV
  {IR(34149, 19), 350}, // 798 TensorQuerySizeARM
  {IR(34120, 14), 348}, // 799 TensorReadARM
  {IR(39474, 20), 554}, // 800 TensorViewSetClipNV
  {IR(39405, 25), 550}, // 801 TensorViewSetDimensionNV
  {IR(39430, 22), 551}, // 802 TensorViewSetStrideNV
  {IR(34134, 15), 349}, // 803 TensorWriteARM
  {IR(34261, 20), 358}, // 804 TerminateInvocation
  {IR(34722, 16), 381}, // 805 TerminateRayKHR
  {IR(38388, 15), 516}, // 806 TerminateRayNV
  {IR(38411, 14), 518}, // 807 TraceMotionNV
  {IR(38403, 8), 517}, // 808 TraceNV
  {IR(34634, 12), 377}, // 809 TraceRayKHR
  {IR(38425, 17), 519}, // 810 TraceRayMotionNV
  {IR(29583, 10), 76}, // 811 Transpose
  {IR(38492, 29), 521}, // 812 TypeAccelerationStructureKHR
  {IR(38521, 28), 521}, // 813 TypeAccelerationStructureNV
  {IR(28532, 10), 25}, // 814 TypeArray
  {IR(41136, 37), 624}, // 815 TypeAvcImeDualReferenceStreaminINTEL
  {IR(40871, 23), 615}, // 816 TypeAvcImePayloadINTEL
  {IR(41053, 44), 622}, // 817 TypeAvcImeResultDualReferenceStreamoutINTEL
  {IR(40985, 22), 620}, // 818 TypeAvcImeResultINTEL
  {IR(41007, 46), 621}, // 819 TypeAvcImeResultSingleReferenceStreamoutINTEL
  {IR(41097, 39), 623}, // 820 TypeAvcImeSingleReferenceStreaminINTEL
  {IR(40940, 23), 618}, // 821 TypeAvcMcePayloadINTEL
  {IR(40963, 22), 619}, // 822 TypeAvcMceResultINTEL
  {IR(40894, 23), 616}, // 823 TypeAvcRefPayloadINTEL
  {IR(41173, 22), 625}, // 824 TypeAvcRefResultINTEL
  {IR(40917, 23), 617}, // 825 TypeAvcSicPayloadINTEL
  {IR(41195, 22), 626}, // 826 TypeAvcSicResultINTEL
  {IR(28294, 9), 17}, // 827 TypeBool
  {IR(48804, 23), 813}, // 828 TypeBufferSurfaceINTEL
  {IR(34903, 25), 388}, // 829 TypeCooperativeMatrixKHR
  {IR(38814, 24), 531}, // 830 TypeCooperativeMatrixNV
  {IR(37036, 24), 470}, // 831 TypeCooperativeVectorNV
  {IR(28647, 16), 32}, // 832 TypeDeviceEvent
  {IR(28637, 10), 31}, // 833 TypeEvent
  {IR(28348, 10), 19}, // 834 TypeFloat
  {IR(28696, 19), 36}, // 835 TypeForwardPointer
  {IR(28624, 13), 30}, // 836 TypeFunction
  {IR(34248, 13), 357}, // 837 TypeGraphARM
  {IR(37749, 17), 493}, // 838 TypeHitObjectEXT
  {IR(36997, 16), 468}, // 839 TypeHitObjectNV
  {IR(28493, 10), 22}, // 840 TypeImage
  {IR(28303, 8), 18}, // 841 TypeInt
  {IR(28369, 11), 21}, // 842 TypeMatrix
  {IR(33078, 17), 300}, // 843 TypeNamedBarrier
  {IR(35938, 25), 428}, // 844 TypeNodePayloadArrayAMDX
  {IR(28570, 11), 28}, // 845 TypeOpaque
  {IR(28687, 9), 35}, // 846 TypePipe
  {IR(32956, 16), 295}, // 847 TypePipeStorage
  {IR(28612, 12), 29}, // 848 TypePointer
  {IR(28677, 10), 34}, // 849 TypeQueue
  {IR(35182, 16), 396}, // 850 TypeRayQueryKHR
  {IR(28663, 14), 33}, // 851 TypeReserveId
  {IR(28542, 17), 26}, // 852 TypeRuntimeArray
  {IR(28515, 17), 24}, // 853 TypeSampledImage
  {IR(28503, 12), 23}, // 854 TypeSampler
  {IR(28559, 11), 27}, // 855 TypeStruct
  {IR(48827, 25), 814}, // 856 TypeStructContinuedINTEL
  {IR(49233, 23), 827}, // 857 TypeTaskSequenceALTERA
  {IR(49256, 22), 827}, // 858 TypeTaskSequenceINTEL
  {IR(34064, 14), 347}, // 859 TypeTensorARM
  {IR(39230, 19), 542}, // 860 TypeTensorLayoutNV
  {IR(39249, 17), 543}, // 861 TypeTensorViewNV
  {IR(34281, 22), 359}, // 862 TypeUntypedPointerKHR
  {IR(28358, 11), 20}, // 863 TypeVector
  {IR(40853, 18), 614}, // 864 TypeVmeImageINTEL
  {IR(28285, 9), 16}, // 865 TypeVoid
  {IR(40482, 13), 593}, // 866 UAddSatINTEL
  {IR(40509, 14), 595}, // 867 UAverageINTEL
  {IR(40544, 21), 597}, // 868 UAverageRoundedINTEL
  {IR(30100, 9), 103}, // 869 UConvert
  {IR(40394, 24), 588}, // 870 UCountLeadingZerosINTEL
  {IR(40418, 25), 589}, // 871 UCountTrailingZerosINTEL
  {IR(30312, 5), 123}, // 872 UDiv
  {IR(34798, 5), 383}, // 873 UDot
  {IR(34851, 11), 386}, // 874 UDotAccSat
  {IR(34862, 14), 386}, // 875 UDotAccSatKHR
  {IR(34803, 8), 383}, // 876 UDotKHR
  {IR(30672, 13), 160}, // 877 UGreaterThan
  {IR(30698, 18), 162}, // 878 UGreaterThanEqual
  {IR(30734, 10), 164}, // 879 ULessThan
  {IR(30754, 15), 166}, // 880 ULessThanEqual
  {IR(30327, 5), 126}, // 881 UMod
  {IR(40606, 15), 601}, // 882 UMul32x16INTEL
  {IR(30480, 13), 140}, // 883 UMulExtended
  {IR(40578, 13), 599}, // 884 USubSatINTEL
  {IR(27797, 6), 1}, // 885 Undef
  {IR(30577, 10), 151}, // 886 Unordered
  {IR(31762, 12), 233}, // 887 Unreachable
  {IR(34322, 22), 361}, // 888 UntypedAccessChainKHR
  {IR(34459, 22), 367}, // 889 UntypedArrayLengthKHR
  {IR(34609, 25), 376}, // 890 UntypedGroupAsyncCopyKHR
  {IR(34344, 30), 362}, // 891 UntypedInBoundsAccessChainKHR
  {IR(34426, 33), 366}, // 892 UntypedInBoundsPtrAccessChainKHR
  {IR(34481, 19), 368}, // 893 UntypedPrefetchKHR
  {IR(34401, 25), 365}, // 894 UntypedPtrAccessChainKHR
  {IR(34303, 19), 360}, // 895 UntypedVariableKHR
  {IR(15197, 32), 836}, // 896 UntypedVariableLengthArrayINTEL
  {IR(29108, 9), 52}, // 897 Variable
  {IR(13243, 25), 731}, // 898 VariableLengthArrayINTEL
  {IR(29465, 21), 69}, // 899 VectorExtractDynamic
  {IR(29486, 20), 70}, // 900 VectorInsertDynamic
  {IR(29506, 14), 71}, // 901 VectorShuffle
  {IR(30388, 18), 133}, // 902 VectorTimesMatrix
  {IR(30352, 18), 131}, // 903 VectorTimesScalar
  {IR(40839, 14), 613}, // 904 VmeImageINTEL
  {IR(37291, 33), 479}, // 905 WritePackedPrimitiveIndices4x8NV
  {IR(31987, 10), 250}, // 906 WritePipe
  {IR(48092, 24), 793}, // 907 WritePipeBlockingALTERA
  {IR(48116, 23), 793}, // 908 WritePipeBlockingINTEL
}};

// Extended instruction descriptions, ordered by (extinst enum, opcode value).
// The fields in order are:
//   enum value
//   operands, an IndexRange into kOperandSpans
//   name, a character-counting IndexRange into kStrings
//   capabilities, an IndexRange into kCapabilitySpans
static const std::array<ExtInstDesc, 425> kExtInstByValue{{
    {0,IR(0, 0),IR(50044, 14),IR(1, 0)}, // DebugInfoNone in debuginfo
    {1,IR(52, 3),IR(50058, 21),IR(1, 0)}, // DebugCompilationUnit in debuginfo
    {2,IR(803, 3),IR(50131, 15),IR(1, 0)}, // DebugTypeBasic in debuginfo
    {3,IR(806, 3),IR(50180, 17),IR(1, 0)}, // DebugTypePointer in debuginfo
    {4,IR(809, 2),IR(50235, 19),IR(1, 0)}, // DebugTypeQualifier in debuginfo
    {5,IR(168, 2),IR(50254, 15),IR(1, 0)}, // DebugTypeArray in debuginfo
    {6,IR(261, 2),IR(50269, 16),IR(1, 0)}, // DebugTypeVector in debuginfo
    {7,IR(811, 6),IR(50285, 13),IR(1, 0)}, // DebugTypedef in debuginfo
    {8,IR(168, 2),IR(50298, 18),IR(1, 0)}, // DebugTypeFunction in debuginfo
    {9,IR(817, 9),IR(50316, 14),IR(1, 0)}, // DebugTypeEnum in debuginfo
    {10,IR(826, 9),IR(50368, 19),IR(1, 0)}, // DebugTypeComposite in debuginfo
    {11,IR(835, 10),IR(50387, 16),IR(1, 0)}, // DebugTypeMember in debuginfo
    {12,IR(845, 5),IR(50403, 21),IR(1, 0)}, // DebugTypeInheritance in debuginfo
    {13,IR(36, 2),IR(50424, 21),IR(1, 0)}, // DebugTypePtrToMember in debuginfo
    {14,IR(168, 2),IR(50445, 18),IR(1, 0)}, // DebugTypeTemplate in debuginfo
    {15,IR(850, 6),IR(50463, 27),IR(1, 0)}, // DebugTypeTemplateParameter in debuginfo
    {16,IR(856, 5),IR(50490, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in debuginfo
    {17,IR(861, 5),IR(50525, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in debuginfo
    {18,IR(835, 10),IR(50556, 20),IR(1, 0)}, // DebugGlobalVariable in debuginfo
    {19,IR(866, 8),IR(50576, 25),IR(1, 0)}, // DebugFunctionDeclaration in debuginfo
    {20,IR(874, 11),IR(50601, 14),IR(1, 0)}, // DebugFunction in debuginfo
    {21,IR(885, 5),IR(50615, 18),IR(1, 0)}, // DebugLexicalBlock in debuginfo
    {22,IR(890, 3),IR(50633, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in debuginfo
    {23,IR(893, 2),IR(50664, 11),IR(1, 0)}, // DebugScope in debuginfo
    {24,IR(0, 0),IR(50675, 13),IR(1, 0)}, // DebugNoScope in debuginfo
    {25,IR(895, 3),IR(50688, 15),IR(1, 0)}, // DebugInlinedAt in debuginfo
    {26,IR(898, 7),IR(50745, 19),IR(1, 0)}, // DebugLocalVariable in debuginfo
    {27,IR(36, 2),IR(50764, 21),IR(1, 0)}, // DebugInlinedVariable in debuginfo
    {28,IR(33, 3),IR(50785, 13),IR(1, 0)}, // DebugDeclare in debuginfo
    {29,IR(375, 3),IR(50798, 11),IR(1, 0)}, // DebugValue in debuginfo
    {30,IR(905, 2),IR(50842, 15),IR(1, 0)}, // DebugOperation in debuginfo
    {31,IR(739, 1),IR(50857, 16),IR(1, 0)}, // DebugExpression in debuginfo
    {32,IR(907, 4),IR(50873, 14),IR(1, 0)}, // DebugMacroDef in debuginfo
    {33,IR(890, 3),IR(50887, 16),IR(1, 0)}, // DebugMacroUndef in debuginfo
    {1,IR(10, 1),IR(50903, 6),IR(1, 0)}, // Round in glsl_std_450
    {2,IR(10, 1),IR(50909, 10),IR(1, 0)}, // RoundEven in glsl_std_450
    {3,IR(10, 1),IR(50919, 6),IR(1, 0)}, // Trunc in glsl_std_450
    {4,IR(10, 1),IR(50925, 5),IR(1, 0)}, // FAbs in glsl_std_450
    {5,IR(10, 1),IR(50930, 5),IR(1, 0)}, // SAbs in glsl_std_450
    {6,IR(10, 1),IR(50935, 6),IR(1, 0)}, // FSign in glsl_std_450
    {7,IR(10, 1),IR(50941, 6),IR(1, 0)}, // SSign in glsl_std_450
    {8,IR(10, 1),IR(50947, 6),IR(1, 0)}, // Floor in glsl_std_450
    {9,IR(10, 1),IR(50953, 5),IR(1, 0)}, // Ceil in glsl_std_450
    {10,IR(10, 1),IR(50958, 6),IR(1, 0)}, // Fract in glsl_std_450
    {11,IR(10, 1),IR(50964, 8),IR(1, 0)}, // Radians in glsl_std_450
    {12,IR(10, 1),IR(50972, 8),IR(1, 0)}, // Degrees in glsl_std_450
    {13,IR(10, 1),IR(50980, 4),IR(1, 0)}, // Sin in glsl_std_450
    {14,IR(10, 1),IR(50984, 4),IR(1, 0)}, // Cos in glsl_std_450
    {15,IR(10, 1),IR(50988, 4),IR(1, 0)}, // Tan in glsl_std_450
    {16,IR(10, 1),IR(50992, 5),IR(1, 0)}, // Asin in glsl_std_450
    {17,IR(10, 1),IR(50997, 5),IR(1, 0)}, // Acos in glsl_std_450
    {18,IR(10, 1),IR(51002, 5),IR(1, 0)}, // Atan in glsl_std_450
    {19,IR(10, 1),IR(51007, 5),IR(1, 0)}, // Sinh in glsl_std_450
    {20,IR(10, 1),IR(51012, 5),IR(1, 0)}, // Cosh in glsl_std_450
    {21,IR(10, 1),IR(51017, 5),IR(1, 0)}, // Tanh in glsl_std_450
    {22,IR(10, 1),IR(51022, 6),IR(1, 0)}, // Asinh in glsl_std_450
    {23,IR(10, 1),IR(51028, 6),IR(1, 0)}, // Acosh in glsl_std_450
    {24,IR(10, 1),IR(51034, 6),IR(1, 0)}, // Atanh in glsl_std_450
    {25,IR(36, 2),IR(51040, 6),IR(1, 0)}, // Atan2 in glsl_std_450
    {26,IR(36, 2),IR(51046, 4),IR(1, 0)}, // Pow in glsl_std_450
    {27,IR(10, 1),IR(51050, 4),IR(1, 0)}, // Exp in glsl_std_450
    {28,IR(10, 1),IR(51054, 4),IR(1, 0)}, // Log in glsl_std_450
    {29,IR(10, 1),IR(51058, 5),IR(1, 0)}, // Exp2 in glsl_std_450
    {30,IR(10, 1),IR(51063, 5),IR(1, 0)}, // Log2 in glsl_std_450
    {31,IR(10, 1),IR(51068, 5),IR(1, 0)}, // Sqrt in glsl_std_450
    {32,IR(10, 1),IR(51073, 12),IR(1, 0)}, // InverseSqrt in glsl_std_450
    {33,IR(10, 1),IR(51085, 12),IR(1, 0)}, // Determinant in glsl_std_450
    {34,IR(10, 1),IR(51097, 14),IR(1, 0)}, // MatrixInverse in glsl_std_450
    {35,IR(36, 2),IR(51111, 5),IR(1, 0)}, // Modf in glsl_std_450
    {36,IR(10, 1),IR(51116, 11),IR(1, 0)}, // ModfStruct in glsl_std_450
    {37,IR(36, 2),IR(51127, 5),IR(1, 0)}, // FMin in glsl_std_450
    {38,IR(36, 2),IR(51132, 5),IR(1, 0)}, // UMin in glsl_std_450
    {39,IR(36, 2),IR(51137, 5),IR(1, 0)}, // SMin in glsl_std_450
    {40,IR(36, 2),IR(51142, 5),IR(1, 0)}, // FMax in glsl_std_450
    {41,IR(36, 2),IR(51147, 5),IR(1, 0)}, // UMax in glsl_std_450
    {42,IR(36, 2),IR(51152, 5),IR(1, 0)}, // SMax in glsl_std_450
    {43,IR(33, 3),IR(51157, 7),IR(1, 0)}, // FClamp in glsl_std_450
    {44,IR(33, 3),IR(51164, 7),IR(1, 0)}, // UClamp in glsl_std_450
    {45,IR(33, 3),IR(51171, 7),IR(1, 0)}, // SClamp in glsl_std_450
    {46,IR(33, 3),IR(51178, 5),IR(1, 0)}, // FMix in glsl_std_450
    {47,IR(33, 3),IR(51183, 5),IR(1, 0)}, // IMix in glsl_std_450
    {48,IR(36, 2),IR(51188, 5),IR(1, 0)}, // Step in glsl_std_450
    {49,IR(33, 3),IR(51193, 11),IR(1, 0)}, // SmoothStep in glsl_std_450
    {50,IR(33, 3),IR(51204, 4),IR(1, 0)}, // Fma in glsl_std_450
    {51,IR(36, 2),IR(51208, 6),IR(1, 0)}, // Frexp in glsl_std_450
    {52,IR(10, 1),IR(51214, 12),IR(1, 0)}, // FrexpStruct in glsl_std_450
    {53,IR(36, 2),IR(51226, 6),IR(1, 0)}, // Ldexp in glsl_std_450
    {54,IR(10, 1),IR(51232, 13),IR(1, 0)}, // PackSnorm4x8 in glsl_std_450
    {55,IR(10, 1),IR(51245, 13),IR(1, 0)}, // PackUnorm4x8 in glsl_std_450
    {56,IR(10, 1),IR(51258, 14),IR(1, 0)}, // PackSnorm2x16 in glsl_std_450
    {57,IR(10, 1),IR(51272, 14),IR(1, 0)}, // PackUnorm2x16 in glsl_std_450
    {58,IR(10, 1),IR(51286, 13),IR(1, 0)}, // PackHalf2x16 in glsl_std_450
    {59,IR(10, 1),IR(51299, 15),IR(315, 1)}, // PackDouble2x32 in glsl_std_450
    {60,IR(10, 1),IR(51314, 16),IR(1, 0)}, // UnpackSnorm2x16 in glsl_std_450
    {61,IR(10, 1),IR(51330, 16),IR(1, 0)}, // UnpackUnorm2x16 in glsl_std_450
    {62,IR(10, 1),IR(51346, 15),IR(1, 0)}, // UnpackHalf2x16 in glsl_std_450
    {63,IR(10, 1),IR(51361, 15),IR(1, 0)}, // UnpackSnorm4x8 in glsl_std_450
    {64,IR(10, 1),IR(51376, 15),IR(1, 0)}, // UnpackUnorm4x8 in glsl_std_450
    {65,IR(10, 1),IR(51391, 17),IR(315, 1)}, // UnpackDouble2x32 in glsl_std_450
    {66,IR(10, 1),IR(51408, 7),IR(1, 0)}, // Length in glsl_std_450
    {67,IR(36, 2),IR(51415, 9),IR(1, 0)}, // Distance in glsl_std_450
    {68,IR(36, 2),IR(51424, 6),IR(1, 0)}, // Cross in glsl_std_450
    {69,IR(10, 1),IR(51430, 10),IR(1, 0)}, // Normalize in glsl_std_450
    {70,IR(33, 3),IR(51440, 12),IR(1, 0)}, // FaceForward in glsl_std_450
    {71,IR(36, 2),IR(51452, 8),IR(1, 0)}, // Reflect in glsl_std_450
    {72,IR(33, 3),IR(51460, 8),IR(1, 0)}, // Refract in glsl_std_450
    {73,IR(10, 1),IR(51468, 9),IR(1, 0)}, // FindILsb in glsl_std_450
    {74,IR(10, 1),IR(51477, 9),IR(1, 0)}, // FindSMsb in glsl_std_450
    {75,IR(10, 1),IR(51486, 9),IR(1, 0)}, // FindUMsb in glsl_std_450
    {76,IR(10, 1),IR(51495, 22),IR(316, 1)}, // InterpolateAtCentroid in glsl_std_450
    {77,IR(36, 2),IR(51517, 20),IR(316, 1)}, // InterpolateAtSample in glsl_std_450
    {78,IR(36, 2),IR(51537, 20),IR(316, 1)}, // InterpolateAtOffset in glsl_std_450
    {79,IR(36, 2),IR(51557, 5),IR(1, 0)}, // NMin in glsl_std_450
    {80,IR(36, 2),IR(51562, 5),IR(1, 0)}, // NMax in glsl_std_450
    {81,IR(33, 3),IR(51567, 7),IR(1, 0)}, // NClamp in glsl_std_450
    {1,IR(399, 5),IR(5357, 7),IR(1, 0)}, // Kernel in nonsemantic_clspvreflection
    {2,IR(911, 5),IR(51574, 13),IR(1, 0)}, // ArgumentInfo in nonsemantic_clspvreflection
    {3,IR(916, 5),IR(51587, 22),IR(1, 0)}, // ArgumentStorageBuffer in nonsemantic_clspvreflection
    {4,IR(916, 5),IR(51609, 16),IR(1, 0)}, // ArgumentUniform in nonsemantic_clspvreflection
    {5,IR(554, 7),IR(51625, 25),IR(1, 0)}, // ArgumentPodStorageBuffer in nonsemantic_clspvreflection
    {6,IR(554, 7),IR(51650, 19),IR(1, 0)}, // ArgumentPodUniform in nonsemantic_clspvreflection
    {7,IR(916, 5),IR(51669, 24),IR(1, 0)}, // ArgumentPodPushConstant in nonsemantic_clspvreflection
    {8,IR(916, 5),IR(51693, 21),IR(1, 0)}, // ArgumentSampledImage in nonsemantic_clspvreflection
    {9,IR(916, 5),IR(51714, 21),IR(1, 0)}, // ArgumentStorageImage in nonsemantic_clspvreflection
    {10,IR(916, 5),IR(51735, 16),IR(1, 0)}, // ArgumentSampler in nonsemantic_clspvreflection
    {11,IR(916, 5),IR(51751, 18),IR(1, 0)}, // ArgumentWorkgroup in nonsemantic_clspvreflection
    {12,IR(33, 3),IR(51769, 26),IR(1, 0)}, // SpecConstantWorkgroupSize in nonsemantic_clspvreflection
    {13,IR(33, 3),IR(51795, 25),IR(1, 0)}, // SpecConstantGlobalOffset in nonsemantic_clspvreflection
    {14,IR(10, 1),IR(51820, 20),IR(1, 0)}, // SpecConstantWorkDim in nonsemantic_clspvreflection
    {15,IR(36, 2),IR(51840, 25),IR(1, 0)}, // PushConstantGlobalOffset in nonsemantic_clspvreflection
    {16,IR(36, 2),IR(51865, 30),IR(1, 0)}, // PushConstantEnqueuedLocalSize in nonsemantic_clspvreflection
    {17,IR(36, 2),IR(51895, 23),IR(1, 0)}, // PushConstantGlobalSize in nonsemantic_clspvreflection
    {18,IR(36, 2),IR(51918, 25),IR(1, 0)}, // PushConstantRegionOffset in nonsemantic_clspvreflection
    {19,IR(36, 2),IR(51943, 26),IR(1, 0)}, // PushConstantNumWorkgroups in nonsemantic_clspvreflection
    {20,IR(36, 2),IR(51969, 30),IR(1, 0)}, // PushConstantRegionGroupOffset in nonsemantic_clspvreflection
    {21,IR(33, 3),IR(51999, 26),IR(1, 0)}, // ConstantDataStorageBuffer in nonsemantic_clspvreflection
    {22,IR(33, 3),IR(52025, 20),IR(1, 0)}, // ConstantDataUniform in nonsemantic_clspvreflection
    {23,IR(33, 3),IR(8782, 15),IR(1, 0)}, // LiteralSampler in nonsemantic_clspvreflection
    {24,IR(296, 4),IR(52045, 30),IR(1, 0)}, // PropertyRequiredWorkgroupSize in nonsemantic_clspvreflection
    {25,IR(10, 1),IR(52075, 28),IR(1, 0)}, // SpecConstantSubgroupMaxSize in nonsemantic_clspvreflection
    {26,IR(916, 5),IR(52103, 28),IR(1, 0)}, // ArgumentPointerPushConstant in nonsemantic_clspvreflection
    {27,IR(554, 7),IR(52131, 23),IR(1, 0)}, // ArgumentPointerUniform in nonsemantic_clspvreflection
    {28,IR(33, 3),IR(52154, 35),IR(1, 0)}, // ProgramScopeVariablesStorageBuffer in nonsemantic_clspvreflection
    {29,IR(33, 3),IR(52189, 38),IR(1, 0)}, // ProgramScopeVariablePointerRelocation in nonsemantic_clspvreflection
    {30,IR(296, 4),IR(52227, 42),IR(1, 0)}, // ImageArgumentInfoChannelOrderPushConstant in nonsemantic_clspvreflection
    {31,IR(296, 4),IR(52269, 45),IR(1, 0)}, // ImageArgumentInfoChannelDataTypePushConstant in nonsemantic_clspvreflection
    {32,IR(525, 6),IR(52314, 37),IR(1, 0)}, // ImageArgumentInfoChannelOrderUniform in nonsemantic_clspvreflection
    {33,IR(525, 6),IR(52351, 40),IR(1, 0)}, // ImageArgumentInfoChannelDataTypeUniform in nonsemantic_clspvreflection
    {34,IR(916, 5),IR(52391, 27),IR(1, 0)}, // ArgumentStorageTexelBuffer in nonsemantic_clspvreflection
    {35,IR(916, 5),IR(52418, 27),IR(1, 0)}, // ArgumentUniformTexelBuffer in nonsemantic_clspvreflection
    {36,IR(33, 3),IR(52445, 32),IR(1, 0)}, // ConstantDataPointerPushConstant in nonsemantic_clspvreflection
    {37,IR(33, 3),IR(52477, 40),IR(1, 0)}, // ProgramScopeVariablePointerPushConstant in nonsemantic_clspvreflection
    {38,IR(375, 3),IR(52517, 11),IR(1, 0)}, // PrintfInfo in nonsemantic_clspvreflection
    {39,IR(33, 3),IR(52528, 26),IR(1, 0)}, // PrintfBufferStorageBuffer in nonsemantic_clspvreflection
    {40,IR(33, 3),IR(52554, 32),IR(1, 0)}, // PrintfBufferPointerPushConstant in nonsemantic_clspvreflection
    {41,IR(296, 4),IR(52586, 34),IR(1, 0)}, // NormalizedSamplerMaskPushConstant in nonsemantic_clspvreflection
    {42,IR(36, 2),IR(52620, 22),IR(1, 0)}, // WorkgroupVariableSize in nonsemantic_clspvreflection
    {0,IR(0, 0),IR(50044, 14),IR(1, 0)}, // DebugInfoNone in nonsemantic_shader_debuginfo_100
    {1,IR(296, 4),IR(50058, 21),IR(1, 0)}, // DebugCompilationUnit in nonsemantic_shader_debuginfo_100
    {2,IR(296, 4),IR(50131, 15),IR(1, 0)}, // DebugTypeBasic in nonsemantic_shader_debuginfo_100
    {3,IR(33, 3),IR(50180, 17),IR(1, 0)}, // DebugTypePointer in nonsemantic_shader_debuginfo_100
    {4,IR(36, 2),IR(50235, 19),IR(1, 0)}, // DebugTypeQualifier in nonsemantic_shader_debuginfo_100
    {5,IR(168, 2),IR(50254, 15),IR(1, 0)}, // DebugTypeArray in nonsemantic_shader_debuginfo_100
    {6,IR(36, 2),IR(50269, 16),IR(1, 0)}, // DebugTypeVector in nonsemantic_shader_debuginfo_100
    {7,IR(525, 6),IR(50285, 13),IR(1, 0)}, // DebugTypedef in nonsemantic_shader_debuginfo_100
    {8,IR(375, 3),IR(50298, 18),IR(1, 0)}, // DebugTypeFunction in nonsemantic_shader_debuginfo_100
    {9,IR(921, 9),IR(50316, 14),IR(1, 0)}, // DebugTypeEnum in nonsemantic_shader_debuginfo_100
    {10,IR(930, 10),IR(50368, 19),IR(1, 0)}, // DebugTypeComposite in nonsemantic_shader_debuginfo_100
    {11,IR(940, 9),IR(50387, 16),IR(1, 0)}, // DebugTypeMember in nonsemantic_shader_debuginfo_100
    {12,IR(296, 4),IR(50403, 21),IR(1, 0)}, // DebugTypeInheritance in nonsemantic_shader_debuginfo_100
    {13,IR(36, 2),IR(50424, 21),IR(1, 0)}, // DebugTypePtrToMember in nonsemantic_shader_debuginfo_100
    {14,IR(168, 2),IR(50445, 18),IR(1, 0)}, // DebugTypeTemplate in nonsemantic_shader_debuginfo_100
    {15,IR(525, 6),IR(50463, 27),IR(1, 0)}, // DebugTypeTemplateParameter in nonsemantic_shader_debuginfo_100
    {16,IR(667, 5),IR(50490, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in nonsemantic_shader_debuginfo_100
    {17,IR(949, 5),IR(50525, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in nonsemantic_shader_debuginfo_100
    {18,IR(954, 10),IR(50556, 20),IR(1, 0)}, // DebugGlobalVariable in nonsemantic_shader_debuginfo_100
    {19,IR(471, 8),IR(50576, 25),IR(1, 0)}, // DebugFunctionDeclaration in nonsemantic_shader_debuginfo_100
    {20,IR(954, 10),IR(50601, 14),IR(1, 0)}, // DebugFunction in nonsemantic_shader_debuginfo_100
    {21,IR(916, 5),IR(50615, 18),IR(1, 0)}, // DebugLexicalBlock in nonsemantic_shader_debuginfo_100
    {22,IR(33, 3),IR(50633, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in nonsemantic_shader_debuginfo_100
    {23,IR(893, 2),IR(50664, 11),IR(1, 0)}, // DebugScope in nonsemantic_shader_debuginfo_100
    {24,IR(0, 0),IR(50675, 13),IR(1, 0)}, // DebugNoScope in nonsemantic_shader_debuginfo_100
    {25,IR(964, 3),IR(50688, 15),IR(1, 0)}, // DebugInlinedAt in nonsemantic_shader_debuginfo_100
    {26,IR(967, 8),IR(50745, 19),IR(1, 0)}, // DebugLocalVariable in nonsemantic_shader_debuginfo_100
    {27,IR(36, 2),IR(50764, 21),IR(1, 0)}, // DebugInlinedVariable in nonsemantic_shader_debuginfo_100
    {28,IR(975, 4),IR(50785, 13),IR(1, 0)}, // DebugDeclare in nonsemantic_shader_debuginfo_100
    {29,IR(975, 4),IR(50798, 11),IR(1, 0)}, // DebugValue in nonsemantic_shader_debuginfo_100
    {30,IR(168, 2),IR(50842, 15),IR(1, 0)}, // DebugOperation in nonsemantic_shader_debuginfo_100
    {31,IR(739, 1),IR(50857, 16),IR(1, 0)}, // DebugExpression in nonsemantic_shader_debuginfo_100
    {32,IR(577, 4),IR(50873, 14),IR(1, 0)}, // DebugMacroDef in nonsemantic_shader_debuginfo_100
    {33,IR(33, 3),IR(50887, 16),IR(1, 0)}, // DebugMacroUndef in nonsemantic_shader_debuginfo_100
    {34,IR(506, 7),IR(52642, 20),IR(1, 0)}, // DebugImportedEntity in nonsemantic_shader_debuginfo_100
    {35,IR(893, 2),IR(52662, 12),IR(1, 0)}, // DebugSource in nonsemantic_shader_debuginfo_100
    {101,IR(36, 2),IR(52674, 24),IR(1, 0)}, // DebugFunctionDefinition in nonsemantic_shader_debuginfo_100
    {102,IR(10, 1),IR(52698, 21),IR(1, 0)}, // DebugSourceContinued in nonsemantic_shader_debuginfo_100
    {103,IR(667, 5),IR(52719, 10),IR(1, 0)}, // DebugLine in nonsemantic_shader_debuginfo_100
    {104,IR(0, 0),IR(52729, 12),IR(1, 0)}, // DebugNoLine in nonsemantic_shader_debuginfo_100
    {105,IR(36, 2),IR(52741, 21),IR(1, 0)}, // DebugBuildIdentifier in nonsemantic_shader_debuginfo_100
    {106,IR(10, 1),IR(52762, 17),IR(1, 0)}, // DebugStoragePath in nonsemantic_shader_debuginfo_100
    {107,IR(296, 4),IR(52779, 16),IR(1, 0)}, // DebugEntryPoint in nonsemantic_shader_debuginfo_100
    {108,IR(33, 3),IR(52795, 16),IR(1, 0)}, // DebugTypeMatrix in nonsemantic_shader_debuginfo_100
    {1,IR(757, 9),IR(52811, 14),IR(1, 0)}, // Configuration in nonsemantic_vkspreflection
    {2,IR(10, 1),IR(52825, 13),IR(1, 0)}, // StartCounter in nonsemantic_vkspreflection
    {3,IR(10, 1),IR(52838, 12),IR(1, 0)}, // StopCounter in nonsemantic_vkspreflection
    {4,IR(296, 4),IR(52850, 14),IR(1, 0)}, // PushConstants in nonsemantic_vkspreflection
    {5,IR(33, 3),IR(52864, 23),IR(1, 0)}, // SpecializationMapEntry in nonsemantic_vkspreflection
    {6,IR(979, 15),IR(52887, 20),IR(1, 0)}, // DescriptorSetBuffer in nonsemantic_vkspreflection
    {7,IR(994, 33),IR(52907, 19),IR(1, 0)}, // DescriptorSetImage in nonsemantic_vkspreflection
    {8,IR(1027, 19),IR(52926, 21),IR(1, 0)}, // DescriptorSetSampler in nonsemantic_vkspreflection
    {0,IR(0, 0),IR(50044, 14),IR(1, 0)}, // DebugInfoNone in opencl_debuginfo_100
    {1,IR(1046, 4),IR(50058, 21),IR(1, 0)}, // DebugCompilationUnit in opencl_debuginfo_100
    {2,IR(1050, 3),IR(50131, 15),IR(1, 0)}, // DebugTypeBasic in opencl_debuginfo_100
    {3,IR(1053, 3),IR(50180, 17),IR(1, 0)}, // DebugTypePointer in opencl_debuginfo_100
    {4,IR(1056, 2),IR(50235, 19),IR(1, 0)}, // DebugTypeQualifier in opencl_debuginfo_100
    {5,IR(168, 2),IR(50254, 15),IR(1, 0)}, // DebugTypeArray in opencl_debuginfo_100
    {6,IR(261, 2),IR(50269, 16),IR(1, 0)}, // DebugTypeVector in opencl_debuginfo_100
    {7,IR(811, 6),IR(50285, 13),IR(1, 0)}, // DebugTypedef in opencl_debuginfo_100
    {8,IR(1058, 3),IR(50298, 18),IR(1, 0)}, // DebugTypeFunction in opencl_debuginfo_100
    {9,IR(1061, 9),IR(50316, 14),IR(1, 0)}, // DebugTypeEnum in opencl_debuginfo_100
    {10,IR(1070, 10),IR(50368, 19),IR(1, 0)}, // DebugTypeComposite in opencl_debuginfo_100
    {11,IR(1080, 10),IR(50387, 16),IR(1, 0)}, // DebugTypeMember in opencl_debuginfo_100
    {12,IR(1090, 5),IR(50403, 21),IR(1, 0)}, // DebugTypeInheritance in opencl_debuginfo_100
    {13,IR(36, 2),IR(50424, 21),IR(1, 0)}, // DebugTypePtrToMember in opencl_debuginfo_100
    {14,IR(168, 2),IR(50445, 18),IR(1, 0)}, // DebugTypeTemplate in opencl_debuginfo_100
    {15,IR(850, 6),IR(50463, 27),IR(1, 0)}, // DebugTypeTemplateParameter in opencl_debuginfo_100
    {16,IR(856, 5),IR(50490, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in opencl_debuginfo_100
    {17,IR(861, 5),IR(50525, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in opencl_debuginfo_100
    {18,IR(1080, 10),IR(50556, 20),IR(1, 0)}, // DebugGlobalVariable in opencl_debuginfo_100
    {19,IR(1095, 8),IR(50576, 25),IR(1, 0)}, // DebugFunctionDeclaration in opencl_debuginfo_100
    {20,IR(1103, 11),IR(50601, 14),IR(1, 0)}, // DebugFunction in opencl_debuginfo_100
    {21,IR(885, 5),IR(50615, 18),IR(1, 0)}, // DebugLexicalBlock in opencl_debuginfo_100
    {22,IR(890, 3),IR(50633, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in opencl_debuginfo_100
    {23,IR(893, 2),IR(50664, 11),IR(1, 0)}, // DebugScope in opencl_debuginfo_100
    {24,IR(0, 0),IR(50675, 13),IR(1, 0)}, // DebugNoScope in opencl_debuginfo_100
    {25,IR(895, 3),IR(50688, 15),IR(1, 0)}, // DebugInlinedAt in opencl_debuginfo_100
    {26,IR(1114, 8),IR(50745, 19),IR(1, 0)}, // DebugLocalVariable in opencl_debuginfo_100
    {27,IR(36, 2),IR(50764, 21),IR(1, 0)}, // DebugInlinedVariable in opencl_debuginfo_100
    {28,IR(33, 3),IR(50785, 13),IR(1, 0)}, // DebugDeclare in opencl_debuginfo_100
    {29,IR(975, 4),IR(50798, 11),IR(1, 0)}, // DebugValue in opencl_debuginfo_100
    {30,IR(1122, 2),IR(50842, 15),IR(1, 0)}, // DebugOperation in opencl_debuginfo_100
    {31,IR(739, 1),IR(50857, 16),IR(1, 0)}, // DebugExpression in opencl_debuginfo_100
    {32,IR(907, 4),IR(50873, 14),IR(1, 0)}, // DebugMacroDef in opencl_debuginfo_100
    {33,IR(890, 3),IR(50887, 16),IR(1, 0)}, // DebugMacroUndef in opencl_debuginfo_100
    {34,IR(1124, 7),IR(52642, 20),IR(1, 0)}, // DebugImportedEntity in opencl_debuginfo_100
    {35,IR(893, 2),IR(52662, 12),IR(1, 0)}, // DebugSource in opencl_debuginfo_100
    {36,IR(1131, 8),IR(53247, 17),IR(1, 0)}, // DebugModuleINTEL in opencl_debuginfo_100
    {0,IR(10, 1),IR(53264, 5),IR(1, 0)}, // acos in opencl_std_100
    {1,IR(10, 1),IR(53269, 6),IR(1, 0)}, // acosh in opencl_std_100
    {2,IR(10, 1),IR(53275, 7),IR(1, 0)}, // acospi in opencl_std_100
    {3,IR(10, 1),IR(53282, 5),IR(1, 0)}, // asin in opencl_std_100
    {4,IR(10, 1),IR(53287, 6),IR(1, 0)}, // asinh in opencl_std_100
    {5,IR(10, 1),IR(53293, 7),IR(1, 0)}, // asinpi in opencl_std_100
    {6,IR(10, 1),IR(53300, 5),IR(1, 0)}, // atan in opencl_std_100
    {7,IR(36, 2),IR(53305, 6),IR(1, 0)}, // atan2 in opencl_std_100
    {8,IR(10, 1),IR(53311, 6),IR(1, 0)}, // atanh in opencl_std_100
    {9,IR(10, 1),IR(53317, 7),IR(1, 0)}, // atanpi in opencl_std_100
    {10,IR(36, 2),IR(53324, 8),IR(1, 0)}, // atan2pi in opencl_std_100
    {11,IR(10, 1),IR(53332, 5),IR(1, 0)}, // cbrt in opencl_std_100
    {12,IR(10, 1),IR(53337, 5),IR(1, 0)}, // ceil in opencl_std_100
    {13,IR(36, 2),IR(53342, 9),IR(1, 0)}, // copysign in opencl_std_100
    {14,IR(10, 1),IR(53351, 4),IR(1, 0)}, // cos in opencl_std_100
    {15,IR(10, 1),IR(53355, 5),IR(1, 0)}, // cosh in opencl_std_100
    {16,IR(10, 1),IR(53360, 6),IR(1, 0)}, // cospi in opencl_std_100
    {17,IR(10, 1),IR(53366, 5),IR(1, 0)}, // erfc in opencl_std_100
    {18,IR(10, 1),IR(53371, 4),IR(1, 0)}, // erf in opencl_std_100
    {19,IR(10, 1),IR(53375, 4),IR(1, 0)}, // exp in opencl_std_100
    {20,IR(10, 1),IR(53379, 5),IR(1, 0)}, // exp2 in opencl_std_100
    {21,IR(10, 1),IR(53384, 6),IR(1, 0)}, // exp10 in opencl_std_100
    {22,IR(10, 1),IR(53390, 6),IR(1, 0)}, // expm1 in opencl_std_100
    {23,IR(10, 1),IR(53396, 5),IR(1, 0)}, // fabs in opencl_std_100
    {24,IR(36, 2),IR(53401, 5),IR(1, 0)}, // fdim in opencl_std_100
    {25,IR(10, 1),IR(53406, 6),IR(1, 0)}, // floor in opencl_std_100
    {26,IR(33, 3),IR(53412, 4),IR(1, 0)}, // fma in opencl_std_100
    {27,IR(36, 2),IR(53416, 5),IR(1, 0)}, // fmax in opencl_std_100
    {28,IR(36, 2),IR(53421, 5),IR(1, 0)}, // fmin in opencl_std_100
    {29,IR(36, 2),IR(53426, 5),IR(1, 0)}, // fmod in opencl_std_100
    {30,IR(36, 2),IR(53431, 6),IR(1, 0)}, // fract in opencl_std_100
    {31,IR(36, 2),IR(53437, 6),IR(1, 0)}, // frexp in opencl_std_100
    {32,IR(36, 2),IR(53443, 6),IR(1, 0)}, // hypot in opencl_std_100
    {33,IR(10, 1),IR(53449, 6),IR(1, 0)}, // ilogb in opencl_std_100
    {34,IR(36, 2),IR(53455, 6),IR(1, 0)}, // ldexp in opencl_std_100
    {35,IR(10, 1),IR(53461, 7),IR(1, 0)}, // lgamma in opencl_std_100
    {36,IR(36, 2),IR(53468, 9),IR(1, 0)}, // lgamma_r in opencl_std_100
    {37,IR(10, 1),IR(53477, 4),IR(1, 0)}, // log in opencl_std_100
    {38,IR(10, 1),IR(53481, 5),IR(1, 0)}, // log2 in opencl_std_100
    {39,IR(10, 1),IR(53486, 6),IR(1, 0)}, // log10 in opencl_std_100
    {40,IR(10, 1),IR(53492, 6),IR(1, 0)}, // log1p in opencl_std_100
    {41,IR(10, 1),IR(53498, 5),IR(1, 0)}, // logb in opencl_std_100
    {42,IR(33, 3),IR(53503, 4),IR(1, 0)}, // mad in opencl_std_100
    {43,IR(36, 2),IR(53507, 7),IR(1, 0)}, // maxmag in opencl_std_100
    {44,IR(36, 2),IR(53514, 7),IR(1, 0)}, // minmag in opencl_std_100
    {45,IR(36, 2),IR(53521, 5),IR(1, 0)}, // modf in opencl_std_100
    {46,IR(10, 1),IR(53526, 4),IR(1, 0)}, // nan in opencl_std_100
    {47,IR(36, 2),IR(53530, 10),IR(1, 0)}, // nextafter in opencl_std_100
    {48,IR(36, 2),IR(53540, 4),IR(1, 0)}, // pow in opencl_std_100
    {49,IR(36, 2),IR(53544, 5),IR(1, 0)}, // pown in opencl_std_100
    {50,IR(36, 2),IR(53549, 5),IR(1, 0)}, // powr in opencl_std_100
    {51,IR(36, 2),IR(53554, 10),IR(1, 0)}, // remainder in opencl_std_100
    {52,IR(33, 3),IR(53564, 7),IR(1, 0)}, // remquo in opencl_std_100
    {53,IR(10, 1),IR(53571, 5),IR(1, 0)}, // rint in opencl_std_100
    {54,IR(36, 2),IR(53576, 6),IR(1, 0)}, // rootn in opencl_std_100
    {55,IR(10, 1),IR(53582, 6),IR(1, 0)}, // round in opencl_std_100
    {56,IR(10, 1),IR(53588, 6),IR(1, 0)}, // rsqrt in opencl_std_100
    {57,IR(10, 1),IR(53594, 4),IR(1, 0)}, // sin in opencl_std_100
    {58,IR(36, 2),IR(53598, 7),IR(1, 0)}, // sincos in opencl_std_100
    {59,IR(10, 1),IR(53605, 5),IR(1, 0)}, // sinh in opencl_std_100
    {60,IR(10, 1),IR(53610, 6),IR(1, 0)}, // sinpi in opencl_std_100
    {61,IR(10, 1),IR(53616, 5),IR(1, 0)}, // sqrt in opencl_std_100
    {62,IR(10, 1),IR(53621, 4),IR(1, 0)}, // tan in opencl_std_100
    {63,IR(10, 1),IR(53625, 5),IR(1, 0)}, // tanh in opencl_std_100
    {64,IR(10, 1),IR(53630, 6),IR(1, 0)}, // tanpi in opencl_std_100
    {65,IR(10, 1),IR(53636, 7),IR(1, 0)}, // tgamma in opencl_std_100
    {66,IR(10, 1),IR(53643, 6),IR(1, 0)}, // trunc in opencl_std_100
    {67,IR(10, 1),IR(53649, 9),IR(1, 0)}, // half_cos in opencl_std_100
    {68,IR(36, 2),IR(53658, 12),IR(1, 0)}, // half_divide in opencl_std_100
    {69,IR(10, 1),IR(53670, 9),IR(1, 0)}, // half_exp in opencl_std_100
    {70,IR(10, 1),IR(53679, 10),IR(1, 0)}, // half_exp2 in opencl_std_100
    {71,IR(10, 1),IR(53689, 11),IR(1, 0)}, // half_exp10 in opencl_std_100
    {72,IR(10, 1),IR(53700, 9),IR(1, 0)}, // half_log in opencl_std_100
    {73,IR(10, 1),IR(53709, 10),IR(1, 0)}, // half_log2 in opencl_std_100
    {74,IR(10, 1),IR(53719, 11),IR(1, 0)}, // half_log10 in opencl_std_100
    {75,IR(36, 2),IR(53730, 10),IR(1, 0)}, // half_powr in opencl_std_100
    {76,IR(10, 1),IR(53740, 11),IR(1, 0)}, // half_recip in opencl_std_100
    {77,IR(10, 1),IR(53751, 11),IR(1, 0)}, // half_rsqrt in opencl_std_100
    {78,IR(10, 1),IR(53762, 9),IR(1, 0)}, // half_sin in opencl_std_100
    {79,IR(10, 1),IR(53771, 10),IR(1, 0)}, // half_sqrt in opencl_std_100
    {80,IR(10, 1),IR(53781, 9),IR(1, 0)}, // half_tan in opencl_std_100
    {81,IR(10, 1),IR(53790, 11),IR(1, 0)}, // native_cos in opencl_std_100
    {82,IR(36, 2),IR(53801, 14),IR(1, 0)}, // native_divide in opencl_std_100
    {83,IR(10, 1),IR(53815, 11),IR(1, 0)}, // native_exp in opencl_std_100
    {84,IR(10, 1),IR(53826, 12),IR(1, 0)}, // native_exp2 in opencl_std_100
    {85,IR(10, 1),IR(53838, 13),IR(1, 0)}, // native_exp10 in opencl_std_100
    {86,IR(10, 1),IR(53851, 11),IR(1, 0)}, // native_log in opencl_std_100
    {87,IR(10, 1),IR(53862, 12),IR(1, 0)}, // native_log2 in opencl_std_100
    {88,IR(10, 1),IR(53874, 13),IR(1, 0)}, // native_log10 in opencl_std_100
    {89,IR(36, 2),IR(53887, 12),IR(1, 0)}, // native_powr in opencl_std_100
    {90,IR(10, 1),IR(53899, 13),IR(1, 0)}, // native_recip in opencl_std_100
    {91,IR(10, 1),IR(53912, 13),IR(1, 0)}, // native_rsqrt in opencl_std_100
    {92,IR(10, 1),IR(53925, 11),IR(1, 0)}, // native_sin in opencl_std_100
    {93,IR(10, 1),IR(53936, 12),IR(1, 0)}, // native_sqrt in opencl_std_100
    {94,IR(10, 1),IR(53948, 11),IR(1, 0)}, // native_tan in opencl_std_100
    {95,IR(33, 3),IR(53959, 7),IR(1, 0)}, // fclamp in opencl_std_100
    {96,IR(10, 1),IR(53966, 8),IR(1, 0)}, // degrees in opencl_std_100
    {97,IR(36, 2),IR(53974, 12),IR(1, 0)}, // fmax_common in opencl_std_100
    {98,IR(36, 2),IR(53986, 12),IR(1, 0)}, // fmin_common in opencl_std_100
    {99,IR(33, 3),IR(53998, 4),IR(1, 0)}, // mix in opencl_std_100
    {100,IR(10, 1),IR(54002, 8),IR(1, 0)}, // radians in opencl_std_100
    {101,IR(36, 2),IR(54010, 5),IR(1, 0)}, // step in opencl_std_100
    {102,IR(33, 3),IR(54015, 11),IR(1, 0)}, // smoothstep in opencl_std_100
    {103,IR(10, 1),IR(54026, 5),IR(1, 0)}, // sign in opencl_std_100
    {104,IR(36, 2),IR(54031, 6),IR(1, 0)}, // cross in opencl_std_100
    {105,IR(36, 2),IR(54037, 9),IR(1, 0)}, // distance in opencl_std_100
    {106,IR(10, 1),IR(54046, 7),IR(1, 0)}, // length in opencl_std_100
    {107,IR(10, 1),IR(54053, 10),IR(1, 0)}, // normalize in opencl_std_100
    {108,IR(36, 2),IR(54063, 14),IR(1, 0)}, // fast_distance in opencl_std_100
    {109,IR(10, 1),IR(54077, 12),IR(1, 0)}, // fast_length in opencl_std_100
    {110,IR(10, 1),IR(54089, 15),IR(1, 0)}, // fast_normalize in opencl_std_100
    {141,IR(10, 1),IR(54104, 6),IR(1, 0)}, // s_abs in opencl_std_100
    {142,IR(36, 2),IR(54110, 11),IR(1, 0)}, // s_abs_diff in opencl_std_100
    {143,IR(36, 2),IR(54121, 10),IR(1, 0)}, // s_add_sat in opencl_std_100
    {144,IR(36, 2),IR(54131, 10),IR(1, 0)}, // u_add_sat in opencl_std_100
    {145,IR(36, 2),IR(54141, 7),IR(1, 0)}, // s_hadd in opencl_std_100
    {146,IR(36, 2),IR(54148, 7),IR(1, 0)}, // u_hadd in opencl_std_100
    {147,IR(36, 2),IR(54155, 8),IR(1, 0)}, // s_rhadd in opencl_std_100
    {148,IR(36, 2),IR(54163, 8),IR(1, 0)}, // u_rhadd in opencl_std_100
    {149,IR(33, 3),IR(54171, 8),IR(1, 0)}, // s_clamp in opencl_std_100
    {150,IR(33, 3),IR(54179, 8),IR(1, 0)}, // u_clamp in opencl_std_100
    {151,IR(10, 1),IR(54187, 4),IR(1, 0)}, // clz in opencl_std_100
    {152,IR(10, 1),IR(54191, 4),IR(1, 0)}, // ctz in opencl_std_100
    {153,IR(33, 3),IR(54195, 9),IR(1, 0)}, // s_mad_hi in opencl_std_100
    {154,IR(33, 3),IR(54204, 10),IR(1, 0)}, // u_mad_sat in opencl_std_100
    {155,IR(33, 3),IR(54214, 10),IR(1, 0)}, // s_mad_sat in opencl_std_100
    {156,IR(36, 2),IR(54224, 6),IR(1, 0)}, // s_max in opencl_std_100
    {157,IR(36, 2),IR(54230, 6),IR(1, 0)}, // u_max in opencl_std_100
    {158,IR(36, 2),IR(54236, 6),IR(1, 0)}, // s_min in opencl_std_100
    {159,IR(36, 2),IR(54242, 6),IR(1, 0)}, // u_min in opencl_std_100
    {160,IR(36, 2),IR(54248, 9),IR(1, 0)}, // s_mul_hi in opencl_std_100
    {161,IR(36, 2),IR(54257, 7),IR(1, 0)}, // rotate in opencl_std_100
    {162,IR(36, 2),IR(54264, 10),IR(1, 0)}, // s_sub_sat in opencl_std_100
    {163,IR(36, 2),IR(54274, 10),IR(1, 0)}, // u_sub_sat in opencl_std_100
    {164,IR(36, 2),IR(54284, 11),IR(1, 0)}, // u_upsample in opencl_std_100
    {165,IR(36, 2),IR(54295, 11),IR(1, 0)}, // s_upsample in opencl_std_100
    {166,IR(10, 1),IR(54306, 9),IR(1, 0)}, // popcount in opencl_std_100
    {167,IR(33, 3),IR(54315, 8),IR(1, 0)}, // s_mad24 in opencl_std_100
    {168,IR(33, 3),IR(54323, 8),IR(1, 0)}, // u_mad24 in opencl_std_100
    {169,IR(36, 2),IR(54331, 8),IR(1, 0)}, // s_mul24 in opencl_std_100
    {170,IR(36, 2),IR(54339, 8),IR(1, 0)}, // u_mul24 in opencl_std_100
    {171,IR(1139, 3),IR(54347, 7),IR(1, 0)}, // vloadn in opencl_std_100
    {172,IR(33, 3),IR(54354, 8),IR(1, 0)}, // vstoren in opencl_std_100
    {173,IR(36, 2),IR(54362, 11),IR(1, 0)}, // vload_half in opencl_std_100
    {174,IR(1139, 3),IR(54373, 12),IR(1, 0)}, // vload_halfn in opencl_std_100
    {175,IR(33, 3),IR(54385, 12),IR(1, 0)}, // vstore_half in opencl_std_100
    {176,IR(1142, 4),IR(54397, 14),IR(1, 0)}, // vstore_half_r in opencl_std_100
    {177,IR(33, 3),IR(54411, 13),IR(1, 0)}, // vstore_halfn in opencl_std_100
    {178,IR(1142, 4),IR(54424, 15),IR(1, 0)}, // vstore_halfn_r in opencl_std_100
    {179,IR(1139, 3),IR(54439, 13),IR(1, 0)}, // vloada_halfn in opencl_std_100
    {180,IR(33, 3),IR(54452, 14),IR(1, 0)}, // vstorea_halfn in opencl_std_100
    {181,IR(1142, 4),IR(54466, 16),IR(1, 0)}, // vstorea_halfn_r in opencl_std_100
    {182,IR(36, 2),IR(54482, 8),IR(1, 0)}, // shuffle in opencl_std_100
    {183,IR(33, 3),IR(54490, 9),IR(1, 0)}, // shuffle2 in opencl_std_100
    {184,IR(168, 2),IR(54499, 7),IR(1, 0)}, // printf in opencl_std_100
    {185,IR(36, 2),IR(54506, 9),IR(1, 0)}, // prefetch in opencl_std_100
    {186,IR(33, 3),IR(54515, 10),IR(1, 0)}, // bitselect in opencl_std_100
    {187,IR(33, 3),IR(54525, 7),IR(1, 0)}, // select in opencl_std_100
    {201,IR(10, 1),IR(54532, 6),IR(1, 0)}, // u_abs in opencl_std_100
    {202,IR(36, 2),IR(54538, 11),IR(1, 0)}, // u_abs_diff in opencl_std_100
    {203,IR(36, 2),IR(54549, 9),IR(1, 0)}, // u_mul_hi in opencl_std_100
    {204,IR(33, 3),IR(54558, 9),IR(1, 0)}, // u_mad_hi in opencl_std_100
    {1,IR(10, 1),IR(54567, 17),IR(1, 0)}, // CubeFaceIndexAMD in spv_amd_gcn_shader
    {2,IR(10, 1),IR(54584, 17),IR(1, 0)}, // CubeFaceCoordAMD in spv_amd_gcn_shader
    {3,IR(0, 0),IR(54601, 8),IR(1, 0)}, // TimeAMD in spv_amd_gcn_shader
    {1,IR(36, 2),IR(54609, 22),IR(1, 0)}, // SwizzleInvocationsAMD in spv_amd_shader_ballot
    {2,IR(36, 2),IR(54631, 28),IR(1, 0)}, // SwizzleInvocationsMaskedAMD in spv_amd_shader_ballot
    {3,IR(33, 3),IR(54659, 19),IR(1, 0)}, // WriteInvocationAMD in spv_amd_shader_ballot
    {4,IR(10, 1),IR(54678, 9),IR(1, 0)}, // MbcntAMD in spv_amd_shader_ballot
    {1,IR(36, 2),IR(54687, 23),IR(1, 0)}, // InterpolateAtVertexAMD in spv_amd_shader_explicit_vertex_parameter
    {1,IR(33, 3),IR(54710, 9),IR(1, 0)}, // FMin3AMD in spv_amd_shader_trinary_minmax
    {2,IR(33, 3),IR(54719, 9),IR(1, 0)}, // UMin3AMD in spv_amd_shader_trinary_minmax
    {3,IR(33, 3),IR(54728, 9),IR(1, 0)}, // SMin3AMD in spv_amd_shader_trinary_minmax
    {4,IR(33, 3),IR(54737, 9),IR(1, 0)}, // FMax3AMD in spv_amd_shader_trinary_minmax
    {5,IR(33, 3),IR(54746, 9),IR(1, 0)}, // UMax3AMD in spv_amd_shader_trinary_minmax
    {6,IR(33, 3),IR(54755, 9),IR(1, 0)}, // SMax3AMD in spv_amd_shader_trinary_minmax
    {7,IR(33, 3),IR(54764, 9),IR(1, 0)}, // FMid3AMD in spv_amd_shader_trinary_minmax
    {8,IR(33, 3),IR(54773, 9),IR(1, 0)}, // UMid3AMD in spv_amd_shader_trinary_minmax
    {9,IR(33, 3),IR(54782, 9),IR(1, 0)}, // SMid3AMD in spv_amd_shader_trinary_minmax
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
    {IR(50058, 21), 1}, // DebugCompilationUnit in debuginfo
    {IR(50785, 13), 28}, // DebugDeclare in debuginfo
    {IR(50857, 16), 31}, // DebugExpression in debuginfo
    {IR(50601, 14), 20}, // DebugFunction in debuginfo
    {IR(50576, 25), 19}, // DebugFunctionDeclaration in debuginfo
    {IR(50556, 20), 18}, // DebugGlobalVariable in debuginfo
    {IR(50044, 14), 0}, // DebugInfoNone in debuginfo
    {IR(50688, 15), 25}, // DebugInlinedAt in debuginfo
    {IR(50764, 21), 27}, // DebugInlinedVariable in debuginfo
    {IR(50615, 18), 21}, // DebugLexicalBlock in debuginfo
    {IR(50633, 31), 22}, // DebugLexicalBlockDiscriminator in debuginfo
    {IR(50745, 19), 26}, // DebugLocalVariable in debuginfo
    {IR(50873, 14), 32}, // DebugMacroDef in debuginfo
    {IR(50887, 16), 33}, // DebugMacroUndef in debuginfo
    {IR(50675, 13), 24}, // DebugNoScope in debuginfo
    {IR(50842, 15), 30}, // DebugOperation in debuginfo
    {IR(50664, 11), 23}, // DebugScope in debuginfo
    {IR(50254, 15), 5}, // DebugTypeArray in debuginfo
    {IR(50131, 15), 2}, // DebugTypeBasic in debuginfo
    {IR(50368, 19), 10}, // DebugTypeComposite in debuginfo
    {IR(50316, 14), 9}, // DebugTypeEnum in debuginfo
    {IR(50298, 18), 8}, // DebugTypeFunction in debuginfo
    {IR(50403, 21), 12}, // DebugTypeInheritance in debuginfo
    {IR(50387, 16), 11}, // DebugTypeMember in debuginfo
    {IR(50180, 17), 3}, // DebugTypePointer in debuginfo
    {IR(50424, 21), 13}, // DebugTypePtrToMember in debuginfo
    {IR(50235, 19), 4}, // DebugTypeQualifier in debuginfo
    {IR(50445, 18), 14}, // DebugTypeTemplate in debuginfo
    {IR(50463, 27), 15}, // DebugTypeTemplateParameter in debuginfo
    {IR(50525, 31), 17}, // DebugTypeTemplateParameterPack in debuginfo
    {IR(50490, 35), 16}, // DebugTypeTemplateTemplateParameter in debuginfo
    {IR(50269, 16), 6}, // DebugTypeVector in debuginfo
    {IR(50285, 13), 7}, // DebugTypedef in debuginfo
    {IR(50798, 11), 29}, // DebugValue in debuginfo
    {IR(50997, 5), 50}, // Acos in glsl_std_450
    {IR(51028, 6), 56}, // Acosh in glsl_std_450
    {IR(50992, 5), 49}, // Asin in glsl_std_450
    {IR(51022, 6), 55}, // Asinh in glsl_std_450
    {IR(51002, 5), 51}, // Atan in glsl_std_450
    {IR(51040, 6), 58}, // Atan2 in glsl_std_450
    {IR(51034, 6), 57}, // Atanh in glsl_std_450
    {IR(50953, 5), 42}, // Ceil in glsl_std_450
    {IR(50984, 4), 47}, // Cos in glsl_std_450
    {IR(51012, 5), 53}, // Cosh in glsl_std_450
    {IR(51424, 6), 101}, // Cross in glsl_std_450
    {IR(50972, 8), 45}, // Degrees in glsl_std_450
    {IR(51085, 12), 66}, // Determinant in glsl_std_450
    {IR(51415, 9), 100}, // Distance in glsl_std_450
    {IR(51050, 4), 60}, // Exp in glsl_std_450
    {IR(51058, 5), 62}, // Exp2 in glsl_std_450
    {IR(50925, 5), 37}, // FAbs in glsl_std_450
    {IR(51157, 7), 76}, // FClamp in glsl_std_450
    {IR(51142, 5), 73}, // FMax in glsl_std_450
    {IR(51127, 5), 70}, // FMin in glsl_std_450
    {IR(51178, 5), 79}, // FMix in glsl_std_450
    {IR(50935, 6), 39}, // FSign in glsl_std_450
    {IR(51440, 12), 103}, // FaceForward in glsl_std_450
    {IR(51468, 9), 106}, // FindILsb in glsl_std_450
    {IR(51477, 9), 107}, // FindSMsb in glsl_std_450
    {IR(51486, 9), 108}, // FindUMsb in glsl_std_450
    {IR(50947, 6), 41}, // Floor in glsl_std_450
    {IR(51204, 4), 83}, // Fma in glsl_std_450
    {IR(50958, 6), 43}, // Fract in glsl_std_450
    {IR(51208, 6), 84}, // Frexp in glsl_std_450
    {IR(51214, 12), 85}, // FrexpStruct in glsl_std_450
    {IR(51183, 5), 80}, // IMix in glsl_std_450
    {IR(51495, 22), 109}, // InterpolateAtCentroid in glsl_std_450
    {IR(51537, 20), 111}, // InterpolateAtOffset in glsl_std_450
    {IR(51517, 20), 110}, // InterpolateAtSample in glsl_std_450
    {IR(51073, 12), 65}, // InverseSqrt in glsl_std_450
    {IR(51226, 6), 86}, // Ldexp in glsl_std_450
    {IR(51408, 7), 99}, // Length in glsl_std_450
    {IR(51054, 4), 61}, // Log in glsl_std_450
    {IR(51063, 5), 63}, // Log2 in glsl_std_450
    {IR(51097, 14), 67}, // MatrixInverse in glsl_std_450
    {IR(51111, 5), 68}, // Modf in glsl_std_450
    {IR(51116, 11), 69}, // ModfStruct in glsl_std_450
    {IR(51567, 7), 114}, // NClamp in glsl_std_450
    {IR(51562, 5), 113}, // NMax in glsl_std_450
    {IR(51557, 5), 112}, // NMin in glsl_std_450
    {IR(51430, 10), 102}, // Normalize in glsl_std_450
    {IR(51299, 15), 92}, // PackDouble2x32 in glsl_std_450
    {IR(51286, 13), 91}, // PackHalf2x16 in glsl_std_450
    {IR(51258, 14), 89}, // PackSnorm2x16 in glsl_std_450
    {IR(51232, 13), 87}, // PackSnorm4x8 in glsl_std_450
    {IR(51272, 14), 90}, // PackUnorm2x16 in glsl_std_450
    {IR(51245, 13), 88}, // PackUnorm4x8 in glsl_std_450
    {IR(51046, 4), 59}, // Pow in glsl_std_450
    {IR(50964, 8), 44}, // Radians in glsl_std_450
    {IR(51452, 8), 104}, // Reflect in glsl_std_450
    {IR(51460, 8), 105}, // Refract in glsl_std_450
    {IR(50903, 6), 34}, // Round in glsl_std_450
    {IR(50909, 10), 35}, // RoundEven in glsl_std_450
    {IR(50930, 5), 38}, // SAbs in glsl_std_450
    {IR(51171, 7), 78}, // SClamp in glsl_std_450
    {IR(51152, 5), 75}, // SMax in glsl_std_450
    {IR(51137, 5), 72}, // SMin in glsl_std_450
    {IR(50941, 6), 40}, // SSign in glsl_std_450
    {IR(50980, 4), 46}, // Sin in glsl_std_450
    {IR(51007, 5), 52}, // Sinh in glsl_std_450
    {IR(51193, 11), 82}, // SmoothStep in glsl_std_450
    {IR(51068, 5), 64}, // Sqrt in glsl_std_450
    {IR(51188, 5), 81}, // Step in glsl_std_450
    {IR(50988, 4), 48}, // Tan in glsl_std_450
    {IR(51017, 5), 54}, // Tanh in glsl_std_450
    {IR(50919, 6), 36}, // Trunc in glsl_std_450
    {IR(51164, 7), 77}, // UClamp in glsl_std_450
    {IR(51147, 5), 74}, // UMax in glsl_std_450
    {IR(51132, 5), 71}, // UMin in glsl_std_450
    {IR(51391, 17), 98}, // UnpackDouble2x32 in glsl_std_450
    {IR(51346, 15), 95}, // UnpackHalf2x16 in glsl_std_450
    {IR(51314, 16), 93}, // UnpackSnorm2x16 in glsl_std_450
    {IR(51361, 15), 96}, // UnpackSnorm4x8 in glsl_std_450
    {IR(51330, 16), 94}, // UnpackUnorm2x16 in glsl_std_450
    {IR(51376, 15), 97}, // UnpackUnorm4x8 in glsl_std_450
    {IR(51574, 13), 116}, // ArgumentInfo in nonsemantic_clspvreflection
    {IR(51669, 24), 121}, // ArgumentPodPushConstant in nonsemantic_clspvreflection
    {IR(51625, 25), 119}, // ArgumentPodStorageBuffer in nonsemantic_clspvreflection
    {IR(51650, 19), 120}, // ArgumentPodUniform in nonsemantic_clspvreflection
    {IR(52103, 28), 140}, // ArgumentPointerPushConstant in nonsemantic_clspvreflection
    {IR(52131, 23), 141}, // ArgumentPointerUniform in nonsemantic_clspvreflection
    {IR(51693, 21), 122}, // ArgumentSampledImage in nonsemantic_clspvreflection
    {IR(51735, 16), 124}, // ArgumentSampler in nonsemantic_clspvreflection
    {IR(51587, 22), 117}, // ArgumentStorageBuffer in nonsemantic_clspvreflection
    {IR(51714, 21), 123}, // ArgumentStorageImage in nonsemantic_clspvreflection
    {IR(52391, 27), 148}, // ArgumentStorageTexelBuffer in nonsemantic_clspvreflection
    {IR(51609, 16), 118}, // ArgumentUniform in nonsemantic_clspvreflection
    {IR(52418, 27), 149}, // ArgumentUniformTexelBuffer in nonsemantic_clspvreflection
    {IR(51751, 18), 125}, // ArgumentWorkgroup in nonsemantic_clspvreflection
    {IR(52445, 32), 150}, // ConstantDataPointerPushConstant in nonsemantic_clspvreflection
    {IR(51999, 26), 135}, // ConstantDataStorageBuffer in nonsemantic_clspvreflection
    {IR(52025, 20), 136}, // ConstantDataUniform in nonsemantic_clspvreflection
    {IR(52269, 45), 145}, // ImageArgumentInfoChannelDataTypePushConstant in nonsemantic_clspvreflection
    {IR(52351, 40), 147}, // ImageArgumentInfoChannelDataTypeUniform in nonsemantic_clspvreflection
    {IR(52227, 42), 144}, // ImageArgumentInfoChannelOrderPushConstant in nonsemantic_clspvreflection
    {IR(52314, 37), 146}, // ImageArgumentInfoChannelOrderUniform in nonsemantic_clspvreflection
    {IR(5357, 7), 115}, // Kernel in nonsemantic_clspvreflection
    {IR(8782, 15), 137}, // LiteralSampler in nonsemantic_clspvreflection
    {IR(52586, 34), 155}, // NormalizedSamplerMaskPushConstant in nonsemantic_clspvreflection
    {IR(52554, 32), 154}, // PrintfBufferPointerPushConstant in nonsemantic_clspvreflection
    {IR(52528, 26), 153}, // PrintfBufferStorageBuffer in nonsemantic_clspvreflection
    {IR(52517, 11), 152}, // PrintfInfo in nonsemantic_clspvreflection
    {IR(52477, 40), 151}, // ProgramScopeVariablePointerPushConstant in nonsemantic_clspvreflection
    {IR(52189, 38), 143}, // ProgramScopeVariablePointerRelocation in nonsemantic_clspvreflection
    {IR(52154, 35), 142}, // ProgramScopeVariablesStorageBuffer in nonsemantic_clspvreflection
    {IR(52045, 30), 138}, // PropertyRequiredWorkgroupSize in nonsemantic_clspvreflection
    {IR(51865, 30), 130}, // PushConstantEnqueuedLocalSize in nonsemantic_clspvreflection
    {IR(51840, 25), 129}, // PushConstantGlobalOffset in nonsemantic_clspvreflection
    {IR(51895, 23), 131}, // PushConstantGlobalSize in nonsemantic_clspvreflection
    {IR(51943, 26), 133}, // PushConstantNumWorkgroups in nonsemantic_clspvreflection
    {IR(51969, 30), 134}, // PushConstantRegionGroupOffset in nonsemantic_clspvreflection
    {IR(51918, 25), 132}, // PushConstantRegionOffset in nonsemantic_clspvreflection
    {IR(51795, 25), 127}, // SpecConstantGlobalOffset in nonsemantic_clspvreflection
    {IR(52075, 28), 139}, // SpecConstantSubgroupMaxSize in nonsemantic_clspvreflection
    {IR(51820, 20), 128}, // SpecConstantWorkDim in nonsemantic_clspvreflection
    {IR(51769, 26), 126}, // SpecConstantWorkgroupSize in nonsemantic_clspvreflection
    {IR(52620, 22), 156}, // WorkgroupVariableSize in nonsemantic_clspvreflection
    {IR(52741, 21), 197}, // DebugBuildIdentifier in nonsemantic_shader_debuginfo_100
    {IR(50058, 21), 158}, // DebugCompilationUnit in nonsemantic_shader_debuginfo_100
    {IR(50785, 13), 185}, // DebugDeclare in nonsemantic_shader_debuginfo_100
    {IR(52779, 16), 199}, // DebugEntryPoint in nonsemantic_shader_debuginfo_100
    {IR(50857, 16), 188}, // DebugExpression in nonsemantic_shader_debuginfo_100
    {IR(50601, 14), 177}, // DebugFunction in nonsemantic_shader_debuginfo_100
    {IR(50576, 25), 176}, // DebugFunctionDeclaration in nonsemantic_shader_debuginfo_100
    {IR(52674, 24), 193}, // DebugFunctionDefinition in nonsemantic_shader_debuginfo_100
    {IR(50556, 20), 175}, // DebugGlobalVariable in nonsemantic_shader_debuginfo_100
    {IR(52642, 20), 191}, // DebugImportedEntity in nonsemantic_shader_debuginfo_100
    {IR(50044, 14), 157}, // DebugInfoNone in nonsemantic_shader_debuginfo_100
    {IR(50688, 15), 182}, // DebugInlinedAt in nonsemantic_shader_debuginfo_100
    {IR(50764, 21), 184}, // DebugInlinedVariable in nonsemantic_shader_debuginfo_100
    {IR(50615, 18), 178}, // DebugLexicalBlock in nonsemantic_shader_debuginfo_100
    {IR(50633, 31), 179}, // DebugLexicalBlockDiscriminator in nonsemantic_shader_debuginfo_100
    {IR(52719, 10), 195}, // DebugLine in nonsemantic_shader_debuginfo_100
    {IR(50745, 19), 183}, // DebugLocalVariable in nonsemantic_shader_debuginfo_100
    {IR(50873, 14), 189}, // DebugMacroDef in nonsemantic_shader_debuginfo_100
    {IR(50887, 16), 190}, // DebugMacroUndef in nonsemantic_shader_debuginfo_100
    {IR(52729, 12), 196}, // DebugNoLine in nonsemantic_shader_debuginfo_100
    {IR(50675, 13), 181}, // DebugNoScope in nonsemantic_shader_debuginfo_100
    {IR(50842, 15), 187}, // DebugOperation in nonsemantic_shader_debuginfo_100
    {IR(50664, 11), 180}, // DebugScope in nonsemantic_shader_debuginfo_100
    {IR(52662, 12), 192}, // DebugSource in nonsemantic_shader_debuginfo_100
    {IR(52698, 21), 194}, // DebugSourceContinued in nonsemantic_shader_debuginfo_100
    {IR(52762, 17), 198}, // DebugStoragePath in nonsemantic_shader_debuginfo_100
    {IR(50254, 15), 162}, // DebugTypeArray in nonsemantic_shader_debuginfo_100
    {IR(50131, 15), 159}, // DebugTypeBasic in nonsemantic_shader_debuginfo_100
    {IR(50368, 19), 167}, // DebugTypeComposite in nonsemantic_shader_debuginfo_100
    {IR(50316, 14), 166}, // DebugTypeEnum in nonsemantic_shader_debuginfo_100
    {IR(50298, 18), 165}, // DebugTypeFunction in nonsemantic_shader_debuginfo_100
    {IR(50403, 21), 169}, // DebugTypeInheritance in nonsemantic_shader_debuginfo_100
    {IR(52795, 16), 200}, // DebugTypeMatrix in nonsemantic_shader_debuginfo_100
    {IR(50387, 16), 168}, // DebugTypeMember in nonsemantic_shader_debuginfo_100
    {IR(50180, 17), 160}, // DebugTypePointer in nonsemantic_shader_debuginfo_100
    {IR(50424, 21), 170}, // DebugTypePtrToMember in nonsemantic_shader_debuginfo_100
    {IR(50235, 19), 161}, // DebugTypeQualifier in nonsemantic_shader_debuginfo_100
    {IR(50445, 18), 171}, // DebugTypeTemplate in nonsemantic_shader_debuginfo_100
    {IR(50463, 27), 172}, // DebugTypeTemplateParameter in nonsemantic_shader_debuginfo_100
    {IR(50525, 31), 174}, // DebugTypeTemplateParameterPack in nonsemantic_shader_debuginfo_100
    {IR(50490, 35), 173}, // DebugTypeTemplateTemplateParameter in nonsemantic_shader_debuginfo_100
    {IR(50269, 16), 163}, // DebugTypeVector in nonsemantic_shader_debuginfo_100
    {IR(50285, 13), 164}, // DebugTypedef in nonsemantic_shader_debuginfo_100
    {IR(50798, 11), 186}, // DebugValue in nonsemantic_shader_debuginfo_100
    {IR(52811, 14), 201}, // Configuration in nonsemantic_vkspreflection
    {IR(52887, 20), 206}, // DescriptorSetBuffer in nonsemantic_vkspreflection
    {IR(52907, 19), 207}, // DescriptorSetImage in nonsemantic_vkspreflection
    {IR(52926, 21), 208}, // DescriptorSetSampler in nonsemantic_vkspreflection
    {IR(52850, 14), 204}, // PushConstants in nonsemantic_vkspreflection
    {IR(52864, 23), 205}, // SpecializationMapEntry in nonsemantic_vkspreflection
    {IR(52825, 13), 202}, // StartCounter in nonsemantic_vkspreflection
    {IR(52838, 12), 203}, // StopCounter in nonsemantic_vkspreflection
    {IR(50058, 21), 210}, // DebugCompilationUnit in opencl_debuginfo_100
    {IR(50785, 13), 237}, // DebugDeclare in opencl_debuginfo_100
    {IR(50857, 16), 240}, // DebugExpression in opencl_debuginfo_100
    {IR(50601, 14), 229}, // DebugFunction in opencl_debuginfo_100
    {IR(50576, 25), 228}, // DebugFunctionDeclaration in opencl_debuginfo_100
    {IR(50556, 20), 227}, // DebugGlobalVariable in opencl_debuginfo_100
    {IR(52642, 20), 243}, // DebugImportedEntity in opencl_debuginfo_100
    {IR(50044, 14), 209}, // DebugInfoNone in opencl_debuginfo_100
    {IR(50688, 15), 234}, // DebugInlinedAt in opencl_debuginfo_100
    {IR(50764, 21), 236}, // DebugInlinedVariable in opencl_debuginfo_100
    {IR(50615, 18), 230}, // DebugLexicalBlock in opencl_debuginfo_100
    {IR(50633, 31), 231}, // DebugLexicalBlockDiscriminator in opencl_debuginfo_100
    {IR(50745, 19), 235}, // DebugLocalVariable in opencl_debuginfo_100
    {IR(50873, 14), 241}, // DebugMacroDef in opencl_debuginfo_100
    {IR(50887, 16), 242}, // DebugMacroUndef in opencl_debuginfo_100
    {IR(53247, 17), 245}, // DebugModuleINTEL in opencl_debuginfo_100
    {IR(50675, 13), 233}, // DebugNoScope in opencl_debuginfo_100
    {IR(50842, 15), 239}, // DebugOperation in opencl_debuginfo_100
    {IR(50664, 11), 232}, // DebugScope in opencl_debuginfo_100
    {IR(52662, 12), 244}, // DebugSource in opencl_debuginfo_100
    {IR(50254, 15), 214}, // DebugTypeArray in opencl_debuginfo_100
    {IR(50131, 15), 211}, // DebugTypeBasic in opencl_debuginfo_100
    {IR(50368, 19), 219}, // DebugTypeComposite in opencl_debuginfo_100
    {IR(50316, 14), 218}, // DebugTypeEnum in opencl_debuginfo_100
    {IR(50298, 18), 217}, // DebugTypeFunction in opencl_debuginfo_100
    {IR(50403, 21), 221}, // DebugTypeInheritance in opencl_debuginfo_100
    {IR(50387, 16), 220}, // DebugTypeMember in opencl_debuginfo_100
    {IR(50180, 17), 212}, // DebugTypePointer in opencl_debuginfo_100
    {IR(50424, 21), 222}, // DebugTypePtrToMember in opencl_debuginfo_100
    {IR(50235, 19), 213}, // DebugTypeQualifier in opencl_debuginfo_100
    {IR(50445, 18), 223}, // DebugTypeTemplate in opencl_debuginfo_100
    {IR(50463, 27), 224}, // DebugTypeTemplateParameter in opencl_debuginfo_100
    {IR(50525, 31), 226}, // DebugTypeTemplateParameterPack in opencl_debuginfo_100
    {IR(50490, 35), 225}, // DebugTypeTemplateTemplateParameter in opencl_debuginfo_100
    {IR(50269, 16), 215}, // DebugTypeVector in opencl_debuginfo_100
    {IR(50285, 13), 216}, // DebugTypedef in opencl_debuginfo_100
    {IR(50798, 11), 238}, // DebugValue in opencl_debuginfo_100
    {IR(53264, 5), 246}, // acos in opencl_std_100
    {IR(53269, 6), 247}, // acosh in opencl_std_100
    {IR(53275, 7), 248}, // acospi in opencl_std_100
    {IR(53282, 5), 249}, // asin in opencl_std_100
    {IR(53287, 6), 250}, // asinh in opencl_std_100
    {IR(53293, 7), 251}, // asinpi in opencl_std_100
    {IR(53300, 5), 252}, // atan in opencl_std_100
    {IR(53305, 6), 253}, // atan2 in opencl_std_100
    {IR(53324, 8), 256}, // atan2pi in opencl_std_100
    {IR(53311, 6), 254}, // atanh in opencl_std_100
    {IR(53317, 7), 255}, // atanpi in opencl_std_100
    {IR(54515, 10), 402}, // bitselect in opencl_std_100
    {IR(53332, 5), 257}, // cbrt in opencl_std_100
    {IR(53337, 5), 258}, // ceil in opencl_std_100
    {IR(54187, 4), 367}, // clz in opencl_std_100
    {IR(53342, 9), 259}, // copysign in opencl_std_100
    {IR(53351, 4), 260}, // cos in opencl_std_100
    {IR(53355, 5), 261}, // cosh in opencl_std_100
    {IR(53360, 6), 262}, // cospi in opencl_std_100
    {IR(54031, 6), 350}, // cross in opencl_std_100
    {IR(54191, 4), 368}, // ctz in opencl_std_100
    {IR(53966, 8), 342}, // degrees in opencl_std_100
    {IR(54037, 9), 351}, // distance in opencl_std_100
    {IR(53371, 4), 264}, // erf in opencl_std_100
    {IR(53366, 5), 263}, // erfc in opencl_std_100
    {IR(53375, 4), 265}, // exp in opencl_std_100
    {IR(53384, 6), 267}, // exp10 in opencl_std_100
    {IR(53379, 5), 266}, // exp2 in opencl_std_100
    {IR(53390, 6), 268}, // expm1 in opencl_std_100
    {IR(53396, 5), 269}, // fabs in opencl_std_100
    {IR(54063, 14), 354}, // fast_distance in opencl_std_100
    {IR(54077, 12), 355}, // fast_length in opencl_std_100
    {IR(54089, 15), 356}, // fast_normalize in opencl_std_100
    {IR(53959, 7), 341}, // fclamp in opencl_std_100
    {IR(53401, 5), 270}, // fdim in opencl_std_100
    {IR(53406, 6), 271}, // floor in opencl_std_100
    {IR(53412, 4), 272}, // fma in opencl_std_100
    {IR(53416, 5), 273}, // fmax in opencl_std_100
    {IR(53974, 12), 343}, // fmax_common in opencl_std_100
    {IR(53421, 5), 274}, // fmin in opencl_std_100
    {IR(53986, 12), 344}, // fmin_common in opencl_std_100
    {IR(53426, 5), 275}, // fmod in opencl_std_100
    {IR(53431, 6), 276}, // fract in opencl_std_100
    {IR(53437, 6), 277}, // frexp in opencl_std_100
    {IR(53649, 9), 313}, // half_cos in opencl_std_100
    {IR(53658, 12), 314}, // half_divide in opencl_std_100
    {IR(53670, 9), 315}, // half_exp in opencl_std_100
    {IR(53689, 11), 317}, // half_exp10 in opencl_std_100
    {IR(53679, 10), 316}, // half_exp2 in opencl_std_100
    {IR(53700, 9), 318}, // half_log in opencl_std_100
    {IR(53719, 11), 320}, // half_log10 in opencl_std_100
    {IR(53709, 10), 319}, // half_log2 in opencl_std_100
    {IR(53730, 10), 321}, // half_powr in opencl_std_100
    {IR(53740, 11), 322}, // half_recip in opencl_std_100
    {IR(53751, 11), 323}, // half_rsqrt in opencl_std_100
    {IR(53762, 9), 324}, // half_sin in opencl_std_100
    {IR(53771, 10), 325}, // half_sqrt in opencl_std_100
    {IR(53781, 9), 326}, // half_tan in opencl_std_100
    {IR(53443, 6), 278}, // hypot in opencl_std_100
    {IR(53449, 6), 279}, // ilogb in opencl_std_100
    {IR(53455, 6), 280}, // ldexp in opencl_std_100
    {IR(54046, 7), 352}, // length in opencl_std_100
    {IR(53461, 7), 281}, // lgamma in opencl_std_100
    {IR(53468, 9), 282}, // lgamma_r in opencl_std_100
    {IR(53477, 4), 283}, // log in opencl_std_100
    {IR(53486, 6), 285}, // log10 in opencl_std_100
    {IR(53492, 6), 286}, // log1p in opencl_std_100
    {IR(53481, 5), 284}, // log2 in opencl_std_100
    {IR(53498, 5), 287}, // logb in opencl_std_100
    {IR(53503, 4), 288}, // mad in opencl_std_100
    {IR(53507, 7), 289}, // maxmag in opencl_std_100
    {IR(53514, 7), 290}, // minmag in opencl_std_100
    {IR(53998, 4), 345}, // mix in opencl_std_100
    {IR(53521, 5), 291}, // modf in opencl_std_100
    {IR(53526, 4), 292}, // nan in opencl_std_100
    {IR(53790, 11), 327}, // native_cos in opencl_std_100
    {IR(53801, 14), 328}, // native_divide in opencl_std_100
    {IR(53815, 11), 329}, // native_exp in opencl_std_100
    {IR(53838, 13), 331}, // native_exp10 in opencl_std_100
    {IR(53826, 12), 330}, // native_exp2 in opencl_std_100
    {IR(53851, 11), 332}, // native_log in opencl_std_100
    {IR(53874, 13), 334}, // native_log10 in opencl_std_100
    {IR(53862, 12), 333}, // native_log2 in opencl_std_100
    {IR(53887, 12), 335}, // native_powr in opencl_std_100
    {IR(53899, 13), 336}, // native_recip in opencl_std_100
    {IR(53912, 13), 337}, // native_rsqrt in opencl_std_100
    {IR(53925, 11), 338}, // native_sin in opencl_std_100
    {IR(53936, 12), 339}, // native_sqrt in opencl_std_100
    {IR(53948, 11), 340}, // native_tan in opencl_std_100
    {IR(53530, 10), 293}, // nextafter in opencl_std_100
    {IR(54053, 10), 353}, // normalize in opencl_std_100
    {IR(54306, 9), 382}, // popcount in opencl_std_100
    {IR(53540, 4), 294}, // pow in opencl_std_100
    {IR(53544, 5), 295}, // pown in opencl_std_100
    {IR(53549, 5), 296}, // powr in opencl_std_100
    {IR(54506, 9), 401}, // prefetch in opencl_std_100
    {IR(54499, 7), 400}, // printf in opencl_std_100
    {IR(54002, 8), 346}, // radians in opencl_std_100
    {IR(53554, 10), 297}, // remainder in opencl_std_100
    {IR(53564, 7), 298}, // remquo in opencl_std_100
    {IR(53571, 5), 299}, // rint in opencl_std_100
    {IR(53576, 6), 300}, // rootn in opencl_std_100
    {IR(54257, 7), 377}, // rotate in opencl_std_100
    {IR(53582, 6), 301}, // round in opencl_std_100
    {IR(53588, 6), 302}, // rsqrt in opencl_std_100
    {IR(54104, 6), 357}, // s_abs in opencl_std_100
    {IR(54110, 11), 358}, // s_abs_diff in opencl_std_100
    {IR(54121, 10), 359}, // s_add_sat in opencl_std_100
    {IR(54171, 8), 365}, // s_clamp in opencl_std_100
    {IR(54141, 7), 361}, // s_hadd in opencl_std_100
    {IR(54315, 8), 383}, // s_mad24 in opencl_std_100
    {IR(54195, 9), 369}, // s_mad_hi in opencl_std_100
    {IR(54214, 10), 371}, // s_mad_sat in opencl_std_100
    {IR(54224, 6), 372}, // s_max in opencl_std_100
    {IR(54236, 6), 374}, // s_min in opencl_std_100
    {IR(54331, 8), 385}, // s_mul24 in opencl_std_100
    {IR(54248, 9), 376}, // s_mul_hi in opencl_std_100
    {IR(54155, 8), 363}, // s_rhadd in opencl_std_100
    {IR(54264, 10), 378}, // s_sub_sat in opencl_std_100
    {IR(54295, 11), 381}, // s_upsample in opencl_std_100
    {IR(54525, 7), 403}, // select in opencl_std_100
    {IR(54482, 8), 398}, // shuffle in opencl_std_100
    {IR(54490, 9), 399}, // shuffle2 in opencl_std_100
    {IR(54026, 5), 349}, // sign in opencl_std_100
    {IR(53594, 4), 303}, // sin in opencl_std_100
    {IR(53598, 7), 304}, // sincos in opencl_std_100
    {IR(53605, 5), 305}, // sinh in opencl_std_100
    {IR(53610, 6), 306}, // sinpi in opencl_std_100
    {IR(54015, 11), 348}, // smoothstep in opencl_std_100
    {IR(53616, 5), 307}, // sqrt in opencl_std_100
    {IR(54010, 5), 347}, // step in opencl_std_100
    {IR(53621, 4), 308}, // tan in opencl_std_100
    {IR(53625, 5), 309}, // tanh in opencl_std_100
    {IR(53630, 6), 310}, // tanpi in opencl_std_100
    {IR(53636, 7), 311}, // tgamma in opencl_std_100
    {IR(53643, 6), 312}, // trunc in opencl_std_100
    {IR(54532, 6), 404}, // u_abs in opencl_std_100
    {IR(54538, 11), 405}, // u_abs_diff in opencl_std_100
    {IR(54131, 10), 360}, // u_add_sat in opencl_std_100
    {IR(54179, 8), 366}, // u_clamp in opencl_std_100
    {IR(54148, 7), 362}, // u_hadd in opencl_std_100
    {IR(54323, 8), 384}, // u_mad24 in opencl_std_100
    {IR(54558, 9), 407}, // u_mad_hi in opencl_std_100
    {IR(54204, 10), 370}, // u_mad_sat in opencl_std_100
    {IR(54230, 6), 373}, // u_max in opencl_std_100
    {IR(54242, 6), 375}, // u_min in opencl_std_100
    {IR(54339, 8), 386}, // u_mul24 in opencl_std_100
    {IR(54549, 9), 406}, // u_mul_hi in opencl_std_100
    {IR(54163, 8), 364}, // u_rhadd in opencl_std_100
    {IR(54274, 10), 379}, // u_sub_sat in opencl_std_100
    {IR(54284, 11), 380}, // u_upsample in opencl_std_100
    {IR(54362, 11), 389}, // vload_half in opencl_std_100
    {IR(54373, 12), 390}, // vload_halfn in opencl_std_100
    {IR(54439, 13), 395}, // vloada_halfn in opencl_std_100
    {IR(54347, 7), 387}, // vloadn in opencl_std_100
    {IR(54385, 12), 391}, // vstore_half in opencl_std_100
    {IR(54397, 14), 392}, // vstore_half_r in opencl_std_100
    {IR(54411, 13), 393}, // vstore_halfn in opencl_std_100
    {IR(54424, 15), 394}, // vstore_halfn_r in opencl_std_100
    {IR(54452, 14), 396}, // vstorea_halfn in opencl_std_100
    {IR(54466, 16), 397}, // vstorea_halfn_r in opencl_std_100
    {IR(54354, 8), 388}, // vstoren in opencl_std_100
    {IR(54584, 17), 409}, // CubeFaceCoordAMD in spv_amd_gcn_shader
    {IR(54567, 17), 408}, // CubeFaceIndexAMD in spv_amd_gcn_shader
    {IR(54601, 8), 410}, // TimeAMD in spv_amd_gcn_shader
    {IR(54678, 9), 414}, // MbcntAMD in spv_amd_shader_ballot
    {IR(54609, 22), 411}, // SwizzleInvocationsAMD in spv_amd_shader_ballot
    {IR(54631, 28), 412}, // SwizzleInvocationsMaskedAMD in spv_amd_shader_ballot
    {IR(54659, 19), 413}, // WriteInvocationAMD in spv_amd_shader_ballot
    {IR(54687, 23), 415}, // InterpolateAtVertexAMD in spv_amd_shader_explicit_vertex_parameter
    {IR(54737, 9), 419}, // FMax3AMD in spv_amd_shader_trinary_minmax
    {IR(54764, 9), 422}, // FMid3AMD in spv_amd_shader_trinary_minmax
    {IR(54710, 9), 416}, // FMin3AMD in spv_amd_shader_trinary_minmax
    {IR(54755, 9), 421}, // SMax3AMD in spv_amd_shader_trinary_minmax
    {IR(54782, 9), 424}, // SMid3AMD in spv_amd_shader_trinary_minmax
    {IR(54728, 9), 418}, // SMin3AMD in spv_amd_shader_trinary_minmax
    {IR(54746, 9), 420}, // UMax3AMD in spv_amd_shader_trinary_minmax
    {IR(54773, 9), 423}, // UMid3AMD in spv_amd_shader_trinary_minmax
    {IR(54719, 9), 417}, // UMin3AMD in spv_amd_shader_trinary_minmax
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
  "SPV_EXT_mesh_shader\0" // IR(1312, 20)
  "SPV_EXT_opacity_micromap\0" // IR(1332, 25)
  "SPV_EXT_optnone\0" // IR(1357, 16)
  "SPV_EXT_physical_storage_buffer\0" // IR(1373, 32)
  "SPV_EXT_relaxed_printf_string_address_space\0" // IR(1405, 44)
  "SPV_EXT_replicated_composites\0" // IR(1449, 30)
  "SPV_EXT_shader_64bit_indexing\0" // IR(1479, 30)
  "SPV_EXT_shader_atomic_float16_add\0" // IR(1509, 34)
  "SPV_EXT_shader_atomic_float_add\0" // IR(1543, 32)
  "SPV_EXT_shader_atomic_float_min_max\0" // IR(1575, 36)
  "SPV_EXT_shader_image_int64\0" // IR(1611, 27)
  "SPV_EXT_shader_invocation_reorder\0" // IR(1638, 34)
  "SPV_EXT_shader_stencil_export\0" // IR(1672, 30)
  "SPV_EXT_shader_tile_image\0" // IR(1702, 26)
  "SPV_EXT_shader_viewport_index_layer\0" // IR(1728, 36)
  "SPV_GOOGLE_decorate_string\0" // IR(1764, 27)
  "SPV_GOOGLE_hlsl_functionality1\0" // IR(1791, 31)
  "SPV_GOOGLE_user_type\0" // IR(1822, 21)
  "SPV_INTEL_2d_block_io\0" // IR(1843, 22)
  "SPV_INTEL_arbitrary_precision_fixed_point\0" // IR(1865, 42)
  "SPV_INTEL_arbitrary_precision_floating_point\0" // IR(1907, 45)
  "SPV_INTEL_arbitrary_precision_integers\0" // IR(1952, 39)
  "SPV_INTEL_bfloat16_conversion\0" // IR(1991, 30)
  "SPV_INTEL_bindless_images\0" // IR(2021, 26)
  "SPV_INTEL_blocking_pipes\0" // IR(2047, 25)
  "SPV_INTEL_cache_controls\0" // IR(2072, 25)
  "SPV_INTEL_debug_module\0" // IR(2097, 23)
  "SPV_INTEL_device_side_avc_motion_estimation\0" // IR(2120, 44)
  "SPV_INTEL_float_controls2\0" // IR(2164, 26)
  "SPV_INTEL_fp_fast_math_mode\0" // IR(2190, 28)
  "SPV_INTEL_fp_max_error\0" // IR(2218, 23)
  "SPV_INTEL_fpga_argument_interfaces\0" // IR(2241, 35)
  "SPV_INTEL_fpga_buffer_location\0" // IR(2276, 31)
  "SPV_INTEL_fpga_cluster_attributes\0" // IR(2307, 34)
  "SPV_INTEL_fpga_dsp_control\0" // IR(2341, 27)
  "SPV_INTEL_fpga_invocation_pipelining_attributes\0" // IR(2368, 48)
  "SPV_INTEL_fpga_latency_control\0" // IR(2416, 31)
  "SPV_INTEL_fpga_loop_controls\0" // IR(2447, 29)
  "SPV_INTEL_fpga_memory_accesses\0" // IR(2476, 31)
  "SPV_INTEL_fpga_memory_attributes\0" // IR(2507, 33)
  "SPV_INTEL_fpga_reg\0" // IR(2540, 19)
  "SPV_INTEL_function_pointers\0" // IR(2559, 28)
  "SPV_INTEL_function_variants\0" // IR(2587, 28)
  "SPV_INTEL_global_variable_fpga_decorations\0" // IR(2615, 43)
  "SPV_INTEL_global_variable_host_access\0" // IR(2658, 38)
  "SPV_INTEL_inline_assembly\0" // IR(2696, 26)
  "SPV_INTEL_int4\0" // IR(2722, 15)
  "SPV_INTEL_io_pipes\0" // IR(2737, 19)
  "SPV_INTEL_kernel_attributes\0" // IR(2756, 28)
  "SPV_INTEL_long_composites\0" // IR(2784, 26)
  "SPV_INTEL_loop_fuse\0" // IR(2810, 20)
  "SPV_INTEL_masked_gather_scatter\0" // IR(2830, 32)
  "SPV_INTEL_maximum_registers\0" // IR(2862, 28)
  "SPV_INTEL_media_block_io\0" // IR(2890, 25)
  "SPV_INTEL_memory_access_aliasing\0" // IR(2915, 33)
  "SPV_INTEL_optnone\0" // IR(2948, 18)
  "SPV_INTEL_runtime_aligned\0" // IR(2966, 26)
  "SPV_INTEL_shader_integer_functions2\0" // IR(2992, 36)
  "SPV_INTEL_split_barrier\0" // IR(3028, 24)
  "SPV_INTEL_subgroup_buffer_prefetch\0" // IR(3052, 35)
  "SPV_INTEL_subgroup_matrix_multiply_accumulate\0" // IR(3087, 46)
  "SPV_INTEL_subgroups\0" // IR(3133, 20)
  "SPV_INTEL_task_sequence\0" // IR(3153, 24)
  "SPV_INTEL_tensor_float32_conversion\0" // IR(3177, 36)
  "SPV_INTEL_ternary_bitwise_function\0" // IR(3213, 35)
  "SPV_INTEL_unstructured_loop_controls\0" // IR(3248, 37)
  "SPV_INTEL_usm_storage_classes\0" // IR(3285, 30)
  "SPV_INTEL_variable_length_array\0" // IR(3315, 32)
  "SPV_INTEL_vector_compute\0" // IR(3347, 25)
  "SPV_KHR_16bit_storage\0" // IR(3372, 22)
  "SPV_KHR_8bit_storage\0" // IR(3394, 21)
  "SPV_KHR_bfloat16\0" // IR(3415, 17)
  "SPV_KHR_bit_instructions\0" // IR(3432, 25)
  "SPV_KHR_compute_shader_derivatives\0" // IR(3457, 35)
  "SPV_KHR_cooperative_matrix\0" // IR(3492, 27)
  "SPV_KHR_device_group\0" // IR(3519, 21)
  "SPV_KHR_expect_assume\0" // IR(3540, 22)
  "SPV_KHR_float_controls\0" // IR(3562, 23)
  "SPV_KHR_float_controls2\0" // IR(3585, 24)
  "SPV_KHR_fma\0" // IR(3609, 12)
  "SPV_KHR_fragment_shader_barycentric\0" // IR(3621, 36)
  "SPV_KHR_fragment_shading_rate\0" // IR(3657, 30)
  "SPV_KHR_integer_dot_product\0" // IR(3687, 28)
  "SPV_KHR_linkonce_odr\0" // IR(3715, 21)
  "SPV_KHR_maximal_reconvergence\0" // IR(3736, 30)
  "SPV_KHR_multiview\0" // IR(3766, 18)
  "SPV_KHR_no_integer_wrap_decoration\0" // IR(3784, 35)
  "SPV_KHR_non_semantic_info\0" // IR(3819, 26)
  "SPV_KHR_physical_storage_buffer\0" // IR(3845, 32)
  "SPV_KHR_post_depth_coverage\0" // IR(3877, 28)
  "SPV_KHR_quad_control\0" // IR(3905, 21)
  "SPV_KHR_ray_cull_mask\0" // IR(3926, 22)
  "SPV_KHR_ray_query\0" // IR(3948, 18)
  "SPV_KHR_ray_tracing\0" // IR(3966, 20)
  "SPV_KHR_ray_tracing_position_fetch\0" // IR(3986, 35)
  "SPV_KHR_relaxed_extended_instruction\0" // IR(4021, 37)
  "SPV_KHR_shader_atomic_counter_ops\0" // IR(4058, 34)
  "SPV_KHR_shader_ballot\0" // IR(4092, 22)
  "SPV_KHR_shader_clock\0" // IR(4114, 21)
  "SPV_KHR_shader_draw_parameters\0" // IR(4135, 31)
  "SPV_KHR_storage_buffer_storage_class\0" // IR(4166, 37)
  "SPV_KHR_subgroup_rotate\0" // IR(4203, 24)
  "SPV_KHR_subgroup_uniform_control_flow\0" // IR(4227, 38)
  "SPV_KHR_subgroup_vote\0" // IR(4265, 22)
  "SPV_KHR_terminate_invocation\0" // IR(4287, 29)
  "SPV_KHR_uniform_group_instructions\0" // IR(4316, 35)
  "SPV_KHR_untyped_pointers\0" // IR(4351, 25)
  "SPV_KHR_variable_pointers\0" // IR(4376, 26)
  "SPV_KHR_vulkan_memory_model\0" // IR(4402, 28)
  "SPV_KHR_workgroup_memory_explicit_layout\0" // IR(4430, 41)
  "SPV_NVX_multiview_per_view_attributes\0" // IR(4471, 38)
  "SPV_NV_bindless_texture\0" // IR(4509, 24)
  "SPV_NV_cluster_acceleration_structure\0" // IR(4533, 38)
  "SPV_NV_compute_shader_derivatives\0" // IR(4571, 34)
  "SPV_NV_cooperative_matrix\0" // IR(4605, 26)
  "SPV_NV_cooperative_matrix2\0" // IR(4631, 27)
  "SPV_NV_cooperative_vector\0" // IR(4658, 26)
  "SPV_NV_displacement_micromap\0" // IR(4684, 29)
  "SPV_NV_fragment_shader_barycentric\0" // IR(4713, 35)
  "SPV_NV_geometry_shader_passthrough\0" // IR(4748, 35)
  "SPV_NV_linear_swept_spheres\0" // IR(4783, 28)
  "SPV_NV_mesh_shader\0" // IR(4811, 19)
  "SPV_NV_raw_access_chains\0" // IR(4830, 25)
  "SPV_NV_ray_tracing\0" // IR(4855, 19)
  "SPV_NV_ray_tracing_motion_blur\0" // IR(4874, 31)
  "SPV_NV_sample_mask_override_coverage\0" // IR(4905, 37)
  "SPV_NV_shader_atomic_fp16_vector\0" // IR(4942, 33)
  "SPV_NV_shader_image_footprint\0" // IR(4975, 30)
  "SPV_NV_shader_invocation_reorder\0" // IR(5005, 33)
  "SPV_NV_shader_sm_builtins\0" // IR(5038, 26)
  "SPV_NV_shader_subgroup_partitioned\0" // IR(5064, 35)
  "SPV_NV_shading_rate\0" // IR(5099, 20)
  "SPV_NV_stereo_view_rendering\0" // IR(5119, 29)
  "SPV_NV_tensor_addressing\0" // IR(5148, 25)
  "SPV_NV_viewport_array2\0" // IR(5173, 23)
  "SPV_QCOM_cooperative_matrix_conversion\0" // IR(5196, 39)
  "SPV_QCOM_image_processing\0" // IR(5235, 26)
  "SPV_QCOM_image_processing2\0" // IR(5261, 27)
  "SPV_QCOM_tile_shading\0" // IR(5288, 22)
  "SPV_VALIDATOR_ignore_type_decl_unique\0" // IR(5310, 38)
  "ReadOnly\0" // IR(5348, 9)
  "Kernel\0" // IR(5357, 7)
  "WriteOnly\0" // IR(5364, 10)
  "ReadWrite\0" // IR(5374, 10)
  "Logical\0" // IR(5384, 8)
  "Physical32\0" // IR(5392, 11)
  "Addresses\0" // IR(5403, 10)
  "Physical64\0" // IR(5413, 11)
  "PhysicalStorageBuffer64\0" // IR(5424, 24)
  "PhysicalStorageBuffer64EXT\0" // IR(5448, 27)
  "PhysicalStorageBufferAddresses\0" // IR(5475, 31)
  "Position\0" // IR(5506, 9)
  "Shader\0" // IR(5515, 7)
  "PointSize\0" // IR(5522, 10)
  "ClipDistance\0" // IR(5532, 13)
  "CullDistance\0" // IR(5545, 13)
  "VertexId\0" // IR(5558, 9)
  "InstanceId\0" // IR(5567, 11)
  "PrimitiveId\0" // IR(5578, 12)
  "Geometry\0" // IR(5590, 9)
  "Tessellation\0" // IR(5599, 13)
  "RayTracingNV\0" // IR(5612, 13)
  "RayTracingKHR\0" // IR(5625, 14)
  "MeshShadingNV\0" // IR(5639, 14)
  "MeshShadingEXT\0" // IR(5653, 15)
  "InvocationId\0" // IR(5668, 13)
  "Layer\0" // IR(5681, 6)
  "ShaderLayer\0" // IR(5687, 12)
  "ShaderViewportIndexLayerEXT\0" // IR(5699, 28)
  "ViewportIndex\0" // IR(5727, 14)
  "MultiViewport\0" // IR(5741, 14)
  "ShaderViewportIndex\0" // IR(5755, 20)
  "TessLevelOuter\0" // IR(5775, 15)
  "TessLevelInner\0" // IR(5790, 15)
  "TessCoord\0" // IR(5805, 10)
  "PatchVertices\0" // IR(5815, 14)
  "FragCoord\0" // IR(5829, 10)
  "PointCoord\0" // IR(5839, 11)
  "FrontFacing\0" // IR(5850, 12)
  "SampleId\0" // IR(5862, 9)
  "SampleRateShading\0" // IR(5871, 18)
  "SamplePosition\0" // IR(5889, 15)
  "SampleMask\0" // IR(5904, 11)
  "FragDepth\0" // IR(5915, 10)
  "HelperInvocation\0" // IR(5925, 17)
  "NumWorkgroups\0" // IR(5942, 14)
  "WorkgroupSize\0" // IR(5956, 14)
  "WorkgroupId\0" // IR(5970, 12)
  "LocalInvocationId\0" // IR(5982, 18)
  "GlobalInvocationId\0" // IR(6000, 19)
  "LocalInvocationIndex\0" // IR(6019, 21)
  "WorkDim\0" // IR(6040, 8)
  "GlobalSize\0" // IR(6048, 11)
  "EnqueuedWorkgroupSize\0" // IR(6059, 22)
  "GlobalOffset\0" // IR(6081, 13)
  "GlobalLinearId\0" // IR(6094, 15)
  "SubgroupSize\0" // IR(6109, 13)
  "GroupNonUniform\0" // IR(6122, 16)
  "SubgroupBallotKHR\0" // IR(6138, 18)
  "SubgroupMaxSize\0" // IR(6156, 16)
  "NumSubgroups\0" // IR(6172, 13)
  "NumEnqueuedSubgroups\0" // IR(6185, 21)
  "SubgroupId\0" // IR(6206, 11)
  "SubgroupLocalInvocationId\0" // IR(6217, 26)
  "VertexIndex\0" // IR(6243, 12)
  "InstanceIndex\0" // IR(6255, 14)
  "CoreIDARM\0" // IR(6269, 10)
  "CoreBuiltinsARM\0" // IR(6279, 16)
  "CoreCountARM\0" // IR(6295, 13)
  "CoreMaxIDARM\0" // IR(6308, 13)
  "WarpIDARM\0" // IR(6321, 10)
  "WarpMaxIDARM\0" // IR(6331, 13)
  "SubgroupEqMask\0" // IR(6344, 15)
  "SubgroupEqMaskKHR\0" // IR(6359, 18)
  "GroupNonUniformBallot\0" // IR(6377, 22)
  "SubgroupGeMask\0" // IR(6399, 15)
  "SubgroupGeMaskKHR\0" // IR(6414, 18)
  "SubgroupGtMask\0" // IR(6432, 15)
  "SubgroupGtMaskKHR\0" // IR(6447, 18)
  "SubgroupLeMask\0" // IR(6465, 15)
  "SubgroupLeMaskKHR\0" // IR(6480, 18)
  "SubgroupLtMask\0" // IR(6498, 15)
  "SubgroupLtMaskKHR\0" // IR(6513, 18)
  "BaseVertex\0" // IR(6531, 11)
  "DrawParameters\0" // IR(6542, 15)
  "BaseInstance\0" // IR(6557, 13)
  "DrawIndex\0" // IR(6570, 10)
  "PrimitiveShadingRateKHR\0" // IR(6580, 24)
  "FragmentShadingRateKHR\0" // IR(6604, 23)
  "DeviceIndex\0" // IR(6627, 12)
  "DeviceGroup\0" // IR(6639, 12)
  "ViewIndex\0" // IR(6651, 10)
  "MultiView\0" // IR(6661, 10)
  "ShadingRateKHR\0" // IR(6671, 15)
  "TileOffsetQCOM\0" // IR(6686, 15)
  "TileShadingQCOM\0" // IR(6701, 16)
  "TileDimensionQCOM\0" // IR(6717, 18)
  "TileApronSizeQCOM\0" // IR(6735, 18)
  "BaryCoordNoPerspAMD\0" // IR(6753, 20)
  "BaryCoordNoPerspCentroidAMD\0" // IR(6773, 28)
  "BaryCoordNoPerspSampleAMD\0" // IR(6801, 26)
  "BaryCoordSmoothAMD\0" // IR(6827, 19)
  "BaryCoordSmoothCentroidAMD\0" // IR(6846, 27)
  "BaryCoordSmoothSampleAMD\0" // IR(6873, 25)
  "BaryCoordPullModelAMD\0" // IR(6898, 22)
  "FragStencilRefEXT\0" // IR(6920, 18)
  "StencilExportEXT\0" // IR(6938, 17)
  "RemainingRecursionLevelsAMDX\0" // IR(6955, 29)
  "ShaderEnqueueAMDX\0" // IR(6984, 18)
  "ShaderIndexAMDX\0" // IR(7002, 16)
  "ViewportMaskNV\0" // IR(7018, 15)
  "ShaderViewportMaskNV\0" // IR(7033, 21)
  "SecondaryPositionNV\0" // IR(7054, 20)
  "ShaderStereoViewNV\0" // IR(7074, 19)
  "SecondaryViewportMaskNV\0" // IR(7093, 24)
  "PositionPerViewNV\0" // IR(7117, 18)
  "PerViewAttributesNV\0" // IR(7135, 20)
  "ViewportMaskPerViewNV\0" // IR(7155, 22)
  "FullyCoveredEXT\0" // IR(7177, 16)
  "FragmentFullyCoveredEXT\0" // IR(7193, 24)
  "TaskCountNV\0" // IR(7217, 12)
  "PrimitiveCountNV\0" // IR(7229, 17)
  "PrimitiveIndicesNV\0" // IR(7246, 19)
  "ClipDistancePerViewNV\0" // IR(7265, 22)
  "CullDistancePerViewNV\0" // IR(7287, 22)
  "LayerPerViewNV\0" // IR(7309, 15)
  "MeshViewCountNV\0" // IR(7324, 16)
  "MeshViewIndicesNV\0" // IR(7340, 18)
  "BaryCoordKHR\0" // IR(7358, 13)
  "BaryCoordNV\0" // IR(7371, 12)
  "FragmentBarycentricKHR\0" // IR(7383, 23)
  "BaryCoordNoPerspKHR\0" // IR(7406, 20)
  "BaryCoordNoPerspNV\0" // IR(7426, 19)
  "FragSizeEXT\0" // IR(7445, 12)
  "FragmentSizeNV\0" // IR(7457, 15)
  "FragmentDensityEXT\0" // IR(7472, 19)
  "FragInvocationCountEXT\0" // IR(7491, 23)
  "InvocationsPerPixelNV\0" // IR(7514, 22)
  "PrimitivePointIndicesEXT\0" // IR(7536, 25)
  "PrimitiveLineIndicesEXT\0" // IR(7561, 24)
  "PrimitiveTriangleIndicesEXT\0" // IR(7585, 28)
  "CullPrimitiveEXT\0" // IR(7613, 17)
  "LaunchIdKHR\0" // IR(7630, 12)
  "LaunchIdNV\0" // IR(7642, 11)
  "LaunchSizeKHR\0" // IR(7653, 14)
  "LaunchSizeNV\0" // IR(7667, 13)
  "WorldRayOriginKHR\0" // IR(7680, 18)
  "WorldRayOriginNV\0" // IR(7698, 17)
  "WorldRayDirectionKHR\0" // IR(7715, 21)
  "WorldRayDirectionNV\0" // IR(7736, 20)
  "ObjectRayOriginKHR\0" // IR(7756, 19)
  "ObjectRayOriginNV\0" // IR(7775, 18)
  "ObjectRayDirectionKHR\0" // IR(7793, 22)
  "ObjectRayDirectionNV\0" // IR(7815, 21)
  "RayTminKHR\0" // IR(7836, 11)
  "RayTminNV\0" // IR(7847, 10)
  "RayTmaxKHR\0" // IR(7857, 11)
  "RayTmaxNV\0" // IR(7868, 10)
  "InstanceCustomIndexKHR\0" // IR(7878, 23)
  "InstanceCustomIndexNV\0" // IR(7901, 22)
  "ObjectToWorldKHR\0" // IR(7923, 17)
  "ObjectToWorldNV\0" // IR(7940, 16)
  "WorldToObjectKHR\0" // IR(7956, 17)
  "WorldToObjectNV\0" // IR(7973, 16)
  "HitTNV\0" // IR(7989, 7)
  "HitKindKHR\0" // IR(7996, 11)
  "HitKindNV\0" // IR(8007, 10)
  "CurrentRayTimeNV\0" // IR(8017, 17)
  "RayTracingMotionBlurNV\0" // IR(8034, 23)
  "HitTriangleVertexPositionsKHR\0" // IR(8057, 30)
  "RayTracingPositionFetchKHR\0" // IR(8087, 27)
  "HitMicroTriangleVertexPositionsNV\0" // IR(8114, 34)
  "RayTracingDisplacementMicromapNV\0" // IR(8148, 33)
  "HitMicroTriangleVertexBarycentricsNV\0" // IR(8181, 37)
  "IncomingRayFlagsKHR\0" // IR(8218, 20)
  "IncomingRayFlagsNV\0" // IR(8238, 19)
  "RayGeometryIndexKHR\0" // IR(8257, 20)
  "HitIsSphereNV\0" // IR(8277, 14)
  "RayTracingSpheresGeometryNV\0" // IR(8291, 28)
  "HitIsLSSNV\0" // IR(8319, 11)
  "RayTracingLinearSweptSpheresGeometryNV\0" // IR(8330, 39)
  "HitSpherePositionNV\0" // IR(8369, 20)
  "WarpsPerSMNV\0" // IR(8389, 13)
  "ShaderSMBuiltinsNV\0" // IR(8402, 19)
  "SMCountNV\0" // IR(8421, 10)
  "WarpIDNV\0" // IR(8431, 9)
  "SMIDNV\0" // IR(8440, 7)
  "HitLSSPositionsNV\0" // IR(8447, 18)
  "HitKindFrontFacingMicroTriangleNV\0" // IR(8465, 34)
  "HitKindBackFacingMicroTriangleNV\0" // IR(8499, 33)
  "HitSphereRadiusNV\0" // IR(8532, 18)
  "HitLSSRadiiNV\0" // IR(8550, 14)
  "ClusterIDNV\0" // IR(8564, 12)
  "RayTracingClusterAccelerationStructureNV\0" // IR(8576, 41)
  "CullMaskKHR\0" // IR(8617, 12)
  "RayCullMaskKHR\0" // IR(8629, 15)
  "Matrix\0" // IR(8644, 7)
  "Linkage\0" // IR(8651, 8)
  "Vector16\0" // IR(8659, 9)
  "Float16Buffer\0" // IR(8668, 14)
  "Float16\0" // IR(8682, 8)
  "Float64\0" // IR(8690, 8)
  "Int64\0" // IR(8698, 6)
  "Int64Atomics\0" // IR(8704, 13)
  "ImageBasic\0" // IR(8717, 11)
  "ImageReadWrite\0" // IR(8728, 15)
  "ImageMipmap\0" // IR(8743, 12)
  "Pipes\0" // IR(8755, 6)
  "Groups\0" // IR(8761, 7)
  "DeviceEnqueue\0" // IR(8768, 14)
  "LiteralSampler\0" // IR(8782, 15)
  "AtomicStorage\0" // IR(8797, 14)
  "Int16\0" // IR(8811, 6)
  "TessellationPointSize\0" // IR(8817, 22)
  "GeometryPointSize\0" // IR(8839, 18)
  "ImageGatherExtended\0" // IR(8857, 20)
  "StorageImageMultisample\0" // IR(8877, 24)
  "UniformBufferArrayDynamicIndexing\0" // IR(8901, 34)
  "SampledImageArrayDynamicIndexing\0" // IR(8935, 33)
  "StorageBufferArrayDynamicIndexing\0" // IR(8968, 34)
  "StorageImageArrayDynamicIndexing\0" // IR(9002, 33)
  "ImageCubeArray\0" // IR(9035, 15)
  "SampledCubeArray\0" // IR(9050, 17)
  "ImageRect\0" // IR(9067, 10)
  "SampledRect\0" // IR(9077, 12)
  "GenericPointer\0" // IR(9089, 15)
  "Int8\0" // IR(9104, 5)
  "InputAttachment\0" // IR(9109, 16)
  "SparseResidency\0" // IR(9125, 16)
  "MinLod\0" // IR(9141, 7)
  "Sampled1D\0" // IR(9148, 10)
  "Image1D\0" // IR(9158, 8)
  "SampledBuffer\0" // IR(9166, 14)
  "ImageBuffer\0" // IR(9180, 12)
  "ImageMSArray\0" // IR(9192, 13)
  "StorageImageExtendedFormats\0" // IR(9205, 28)
  "ImageQuery\0" // IR(9233, 11)
  "DerivativeControl\0" // IR(9244, 18)
  "InterpolationFunction\0" // IR(9262, 22)
  "TransformFeedback\0" // IR(9284, 18)
  "GeometryStreams\0" // IR(9302, 16)
  "StorageImageReadWithoutFormat\0" // IR(9318, 30)
  "StorageImageWriteWithoutFormat\0" // IR(9348, 31)
  "SubgroupDispatch\0" // IR(9379, 17)
  "NamedBarrier\0" // IR(9396, 13)
  "PipeStorage\0" // IR(9409, 12)
  "GroupNonUniformVote\0" // IR(9421, 20)
  "GroupNonUniformArithmetic\0" // IR(9441, 26)
  "GroupNonUniformShuffle\0" // IR(9467, 23)
  "GroupNonUniformShuffleRelative\0" // IR(9490, 31)
  "GroupNonUniformClustered\0" // IR(9521, 25)
  "GroupNonUniformQuad\0" // IR(9546, 20)
  "UniformDecoration\0" // IR(9566, 18)
  "TileImageColorReadAccessEXT\0" // IR(9584, 28)
  "TileImageDepthReadAccessEXT\0" // IR(9612, 28)
  "TileImageStencilReadAccessEXT\0" // IR(9640, 30)
  "TensorsARM\0" // IR(9670, 11)
  "StorageTensorArrayDynamicIndexingARM\0" // IR(9681, 37)
  "StorageTensorArrayNonUniformIndexingARM\0" // IR(9718, 40)
  "GraphARM\0" // IR(9758, 9)
  "CooperativeMatrixLayoutsARM\0" // IR(9767, 28)
  "Float8EXT\0" // IR(9795, 10)
  "Float8CooperativeMatrixEXT\0" // IR(9805, 27)
  "CooperativeMatrixKHR\0" // IR(9832, 21)
  "WorkgroupMemoryExplicitLayoutKHR\0" // IR(9853, 33)
  "WorkgroupMemoryExplicitLayout8BitAccessKHR\0" // IR(9886, 43)
  "WorkgroupMemoryExplicitLayout16BitAccessKHR\0" // IR(9929, 44)
  "SubgroupVoteKHR\0" // IR(9973, 16)
  "StorageBuffer16BitAccess\0" // IR(9989, 25)
  "StorageUniformBufferBlock16\0" // IR(10014, 28)
  "UniformAndStorageBuffer16BitAccess\0" // IR(10042, 35)
  "StorageUniform16\0" // IR(10077, 17)
  "StoragePushConstant16\0" // IR(10094, 22)
  "StorageInputOutput16\0" // IR(10116, 21)
  "VariablePointersStorageBuffer\0" // IR(10137, 30)
  "VariablePointers\0" // IR(10167, 17)
  "AtomicStorageOps\0" // IR(10184, 17)
  "SampleMaskPostDepthCoverage\0" // IR(10201, 28)
  "StorageBuffer8BitAccess\0" // IR(10229, 24)
  "UniformAndStorageBuffer8BitAccess\0" // IR(10253, 34)
  "StoragePushConstant8\0" // IR(10287, 21)
  "DenormPreserve\0" // IR(10308, 15)
  "DenormFlushToZero\0" // IR(10323, 18)
  "SignedZeroInfNanPreserve\0" // IR(10341, 25)
  "RoundingModeRTE\0" // IR(10366, 16)
  "RoundingModeRTZ\0" // IR(10382, 16)
  "RayQueryProvisionalKHR\0" // IR(10398, 23)
  "RayQueryKHR\0" // IR(10421, 12)
  "UntypedPointersKHR\0" // IR(10433, 19)
  "RayTraversalPrimitiveCullingKHR\0" // IR(10452, 32)
  "TextureSampleWeightedQCOM\0" // IR(10484, 26)
  "TextureBoxFilterQCOM\0" // IR(10510, 21)
  "TextureBlockMatchQCOM\0" // IR(10531, 22)
  "CooperativeMatrixConversionQCOM\0" // IR(10553, 32)
  "TextureBlockMatch2QCOM\0" // IR(10585, 23)
  "Float16ImageAMD\0" // IR(10608, 16)
  "ImageGatherBiasLodAMD\0" // IR(10624, 22)
  "FragmentMaskAMD\0" // IR(10646, 16)
  "ImageReadWriteLodAMD\0" // IR(10662, 21)
  "Int64ImageEXT\0" // IR(10683, 14)
  "ShaderClockKHR\0" // IR(10697, 15)
  "QuadControlKHR\0" // IR(10712, 15)
  "Int4TypeINTEL\0" // IR(10727, 14)
  "Int4CooperativeMatrixINTEL\0" // IR(10741, 27)
  "BFloat16TypeKHR\0" // IR(10768, 16)
  "BFloat16DotProductKHR\0" // IR(10784, 22)
  "BFloat16CooperativeMatrixKHR\0" // IR(10806, 29)
  "SampleMaskOverrideCoverageNV\0" // IR(10835, 29)
  "GeometryShaderPassthroughNV\0" // IR(10864, 28)
  "ShaderViewportIndexLayerNV\0" // IR(10892, 27)
  "ImageFootprintNV\0" // IR(10919, 17)
  "FragmentBarycentricNV\0" // IR(10936, 22)
  "ComputeDerivativeGroupQuadsKHR\0" // IR(10958, 31)
  "ComputeDerivativeGroupQuadsNV\0" // IR(10989, 30)
  "ShadingRateNV\0" // IR(11019, 14)
  "GroupNonUniformPartitionedNV\0" // IR(11033, 29)
  "ShaderNonUniform\0" // IR(11062, 17)
  "ShaderNonUniformEXT\0" // IR(11079, 20)
  "RuntimeDescriptorArray\0" // IR(11099, 23)
  "RuntimeDescriptorArrayEXT\0" // IR(11122, 26)
  "InputAttachmentArrayDynamicIndexing\0" // IR(11148, 36)
  "InputAttachmentArrayDynamicIndexingEXT\0" // IR(11184, 39)
  "UniformTexelBufferArrayDynamicIndexing\0" // IR(11223, 39)
  "UniformTexelBufferArrayDynamicIndexingEXT\0" // IR(11262, 42)
  "StorageTexelBufferArrayDynamicIndexing\0" // IR(11304, 39)
  "StorageTexelBufferArrayDynamicIndexingEXT\0" // IR(11343, 42)
  "UniformBufferArrayNonUniformIndexing\0" // IR(11385, 37)
  "UniformBufferArrayNonUniformIndexingEXT\0" // IR(11422, 40)
  "SampledImageArrayNonUniformIndexing\0" // IR(11462, 36)
  "SampledImageArrayNonUniformIndexingEXT\0" // IR(11498, 39)
  "StorageBufferArrayNonUniformIndexing\0" // IR(11537, 37)
  "StorageBufferArrayNonUniformIndexingEXT\0" // IR(11574, 40)
  "StorageImageArrayNonUniformIndexing\0" // IR(11614, 36)
  "StorageImageArrayNonUniformIndexingEXT\0" // IR(11650, 39)
  "InputAttachmentArrayNonUniformIndexing\0" // IR(11689, 39)
  "InputAttachmentArrayNonUniformIndexingEXT\0" // IR(11728, 42)
  "UniformTexelBufferArrayNonUniformIndexing\0" // IR(11770, 42)
  "UniformTexelBufferArrayNonUniformIndexingEXT\0" // IR(11812, 45)
  "StorageTexelBufferArrayNonUniformIndexing\0" // IR(11857, 42)
  "StorageTexelBufferArrayNonUniformIndexingEXT\0" // IR(11899, 45)
  "VulkanMemoryModel\0" // IR(11944, 18)
  "VulkanMemoryModelKHR\0" // IR(11962, 21)
  "VulkanMemoryModelDeviceScope\0" // IR(11983, 29)
  "VulkanMemoryModelDeviceScopeKHR\0" // IR(12012, 32)
  "PhysicalStorageBufferAddressesEXT\0" // IR(12044, 34)
  "ComputeDerivativeGroupLinearKHR\0" // IR(12078, 32)
  "ComputeDerivativeGroupLinearNV\0" // IR(12110, 31)
  "RayTracingProvisionalKHR\0" // IR(12141, 25)
  "CooperativeMatrixNV\0" // IR(12166, 20)
  "FragmentShaderSampleInterlockEXT\0" // IR(12186, 33)
  "FragmentShaderShadingRateInterlockEXT\0" // IR(12219, 38)
  "FragmentShaderPixelInterlockEXT\0" // IR(12257, 32)
  "DemoteToHelperInvocation\0" // IR(12289, 25)
  "DemoteToHelperInvocationEXT\0" // IR(12314, 28)
  "DisplacementMicromapNV\0" // IR(12342, 23)
  "RayTracingOpacityMicromapEXT\0" // IR(12365, 29)
  "ShaderInvocationReorderNV\0" // IR(12394, 26)
  "ShaderInvocationReorderEXT\0" // IR(12420, 27)
  "BindlessTextureNV\0" // IR(12447, 18)
  "RayQueryPositionFetchKHR\0" // IR(12465, 25)
  "CooperativeVectorNV\0" // IR(12490, 20)
  "AtomicFloat16VectorNV\0" // IR(12510, 22)
  "RawAccessChainsNV\0" // IR(12532, 18)
  "Shader64BitIndexingEXT\0" // IR(12550, 23)
  "CooperativeMatrixReductionsNV\0" // IR(12573, 30)
  "CooperativeMatrixConversionsNV\0" // IR(12603, 31)
  "CooperativeMatrixPerElementOperationsNV\0" // IR(12634, 40)
  "CooperativeMatrixTensorAddressingNV\0" // IR(12674, 36)
  "CooperativeMatrixBlockLoadsNV\0" // IR(12710, 30)
  "CooperativeVectorTrainingNV\0" // IR(12740, 28)
  "TensorAddressingNV\0" // IR(12768, 19)
  "SubgroupShuffleINTEL\0" // IR(12787, 21)
  "SubgroupBufferBlockIOINTEL\0" // IR(12808, 27)
  "SubgroupImageBlockIOINTEL\0" // IR(12835, 26)
  "SubgroupImageMediaBlockIOINTEL\0" // IR(12861, 31)
  "RoundToInfinityINTEL\0" // IR(12892, 21)
  "FloatingPointModeINTEL\0" // IR(12913, 23)
  "IntegerFunctions2INTEL\0" // IR(12936, 23)
  "FunctionPointersINTEL\0" // IR(12959, 22)
  "IndirectReferencesINTEL\0" // IR(12981, 24)
  "AsmINTEL\0" // IR(13005, 9)
  "AtomicFloat32MinMaxEXT\0" // IR(13014, 23)
  "AtomicFloat64MinMaxEXT\0" // IR(13037, 23)
  "AtomicFloat16MinMaxEXT\0" // IR(13060, 23)
  "VectorComputeINTEL\0" // IR(13083, 19)
  "VectorAnyINTEL\0" // IR(13102, 15)
  "ExpectAssumeKHR\0" // IR(13117, 16)
  "SubgroupAvcMotionEstimationINTEL\0" // IR(13133, 33)
  "SubgroupAvcMotionEstimationIntraINTEL\0" // IR(13166, 38)
  "SubgroupAvcMotionEstimationChromaINTEL\0" // IR(13204, 39)
  "VariableLengthArrayINTEL\0" // IR(13243, 25)
  "FunctionFloatControlINTEL\0" // IR(13268, 26)
  "FPGAMemoryAttributesALTERA\0" // IR(13294, 27)
  "FPGAMemoryAttributesINTEL\0" // IR(13321, 26)
  "FPFastMathModeINTEL\0" // IR(13347, 20)
  "ArbitraryPrecisionIntegersALTERA\0" // IR(13367, 33)
  "ArbitraryPrecisionIntegersINTEL\0" // IR(13400, 32)
  "ArbitraryPrecisionFloatingPointALTERA\0" // IR(13432, 38)
  "ArbitraryPrecisionFloatingPointINTEL\0" // IR(13470, 37)
  "UnstructuredLoopControlsINTEL\0" // IR(13507, 30)
  "FPGALoopControlsALTERA\0" // IR(13537, 23)
  "FPGALoopControlsINTEL\0" // IR(13560, 22)
  "KernelAttributesINTEL\0" // IR(13582, 22)
  "FPGAKernelAttributesINTEL\0" // IR(13604, 26)
  "FPGAMemoryAccessesALTERA\0" // IR(13630, 25)
  "FPGAMemoryAccessesINTEL\0" // IR(13655, 24)
  "FPGAClusterAttributesALTERA\0" // IR(13679, 28)
  "FPGAClusterAttributesINTEL\0" // IR(13707, 27)
  "LoopFuseALTERA\0" // IR(13734, 15)
  "LoopFuseINTEL\0" // IR(13749, 14)
  "FPGADSPControlALTERA\0" // IR(13763, 21)
  "FPGADSPControlINTEL\0" // IR(13784, 20)
  "MemoryAccessAliasingINTEL\0" // IR(13804, 26)
  "FPGAInvocationPipeliningAttributesALTERA\0" // IR(13830, 41)
  "FPGAInvocationPipeliningAttributesINTEL\0" // IR(13871, 40)
  "FPGABufferLocationALTERA\0" // IR(13911, 25)
  "FPGABufferLocationINTEL\0" // IR(13936, 24)
  "ArbitraryPrecisionFixedPointALTERA\0" // IR(13960, 35)
  "ArbitraryPrecisionFixedPointINTEL\0" // IR(13995, 34)
  "USMStorageClassesALTERA\0" // IR(14029, 24)
  "USMStorageClassesINTEL\0" // IR(14053, 23)
  "RuntimeAlignedAttributeALTERA\0" // IR(14076, 30)
  "RuntimeAlignedAttributeINTEL\0" // IR(14106, 29)
  "IOPipesALTERA\0" // IR(14135, 14)
  "IOPipesINTEL\0" // IR(14149, 13)
  "BlockingPipesALTERA\0" // IR(14162, 20)
  "BlockingPipesINTEL\0" // IR(14182, 19)
  "FPGARegALTERA\0" // IR(14201, 14)
  "FPGARegINTEL\0" // IR(14215, 13)
  "DotProductInputAll\0" // IR(14228, 19)
  "DotProductInputAllKHR\0" // IR(14247, 22)
  "DotProductInput4x8Bit\0" // IR(14269, 22)
  "DotProductInput4x8BitKHR\0" // IR(14291, 25)
  "DotProductInput4x8BitPacked\0" // IR(14316, 28)
  "DotProductInput4x8BitPackedKHR\0" // IR(14344, 31)
  "DotProduct\0" // IR(14375, 11)
  "DotProductKHR\0" // IR(14386, 14)
  "ReplicatedCompositesEXT\0" // IR(14400, 24)
  "BitInstructions\0" // IR(14424, 16)
  "GroupNonUniformRotateKHR\0" // IR(14440, 25)
  "FloatControls2\0" // IR(14465, 15)
  "FMAKHR\0" // IR(14480, 7)
  "AtomicFloat32AddEXT\0" // IR(14487, 20)
  "AtomicFloat64AddEXT\0" // IR(14507, 20)
  "LongCompositesINTEL\0" // IR(14527, 20)
  "OptNoneEXT\0" // IR(14547, 11)
  "OptNoneINTEL\0" // IR(14558, 13)
  "AtomicFloat16AddEXT\0" // IR(14571, 20)
  "DebugInfoModuleINTEL\0" // IR(14591, 21)
  "BFloat16ConversionINTEL\0" // IR(14612, 24)
  "SplitBarrierINTEL\0" // IR(14636, 18)
  "ArithmeticFenceEXT\0" // IR(14654, 19)
  "FPGAClusterAttributesV2ALTERA\0" // IR(14673, 30)
  "FPGAClusterAttributesV2INTEL\0" // IR(14703, 29)
  "FPGAKernelAttributesv2INTEL\0" // IR(14732, 28)
  "TaskSequenceALTERA\0" // IR(14760, 19)
  "TaskSequenceINTEL\0" // IR(14779, 18)
  "FPMaxErrorINTEL\0" // IR(14797, 16)
  "FPGALatencyControlALTERA\0" // IR(14813, 25)
  "FPGALatencyControlINTEL\0" // IR(14838, 24)
  "FPGAArgumentInterfacesALTERA\0" // IR(14862, 29)
  "FPGAArgumentInterfacesINTEL\0" // IR(14891, 28)
  "GlobalVariableHostAccessINTEL\0" // IR(14919, 30)
  "GlobalVariableFPGADecorationsALTERA\0" // IR(14949, 36)
  "GlobalVariableFPGADecorationsINTEL\0" // IR(14985, 35)
  "SubgroupBufferPrefetchINTEL\0" // IR(15020, 28)
  "Subgroup2DBlockIOINTEL\0" // IR(15048, 23)
  "Subgroup2DBlockTransformINTEL\0" // IR(15071, 30)
  "Subgroup2DBlockTransposeINTEL\0" // IR(15101, 30)
  "SubgroupMatrixMultiplyAccumulateINTEL\0" // IR(15131, 38)
  "TernaryBitwiseFunctionINTEL\0" // IR(15169, 28)
  "UntypedVariableLengthArrayINTEL\0" // IR(15197, 32)
  "SpecConditionalINTEL\0" // IR(15229, 21)
  "FunctionVariantsINTEL\0" // IR(15250, 22)
  "GroupUniformArithmeticKHR\0" // IR(15272, 26)
  "TensorFloat32RoundingINTEL\0" // IR(15298, 27)
  "MaskedGatherScatterINTEL\0" // IR(15325, 25)
  "CacheControlsINTEL\0" // IR(15350, 19)
  "RegisterLimitsINTEL\0" // IR(15369, 20)
  "BindlessImagesINTEL\0" // IR(15389, 20)
  "Unspecified\0" // IR(15409, 12)
  "Address\0" // IR(15421, 8)
  "Boolean\0" // IR(15429, 8)
  "Float\0" // IR(15437, 6)
  "Signed\0" // IR(15443, 7)
  "SignedChar\0" // IR(15450, 11)
  "Unsigned\0" // IR(15461, 9)
  "UnsignedChar\0" // IR(15470, 13)
  "Class\0" // IR(15483, 6)
  "Structure\0" // IR(15489, 10)
  "Union\0" // IR(15499, 6)
  "ImportedModule\0" // IR(15505, 15)
  "ImportedDeclaration\0" // IR(15520, 20)
  "None\0" // IR(15540, 5)
  "FlagIsProtected\0" // IR(15545, 16)
  "FlagIsPrivate\0" // IR(15561, 14)
  "FlagIsPublic\0" // IR(15575, 13)
  "FlagIsLocal\0" // IR(15588, 12)
  "FlagIsDefinition\0" // IR(15600, 17)
  "FlagFwdDecl\0" // IR(15617, 12)
  "FlagArtificial\0" // IR(15629, 15)
  "FlagExplicit\0" // IR(15644, 13)
  "FlagPrototyped\0" // IR(15657, 15)
  "FlagObjectPointer\0" // IR(15672, 18)
  "FlagStaticMember\0" // IR(15690, 17)
  "FlagIndirectVariable\0" // IR(15707, 21)
  "FlagLValueReference\0" // IR(15728, 20)
  "FlagRValueReference\0" // IR(15748, 20)
  "FlagIsOptimized\0" // IR(15768, 16)
  "FlagIsEnumClass\0" // IR(15784, 16)
  "FlagTypePassByValue\0" // IR(15800, 20)
  "FlagTypePassByReference\0" // IR(15820, 24)
  "Deref\0" // IR(15844, 6)
  "Plus\0" // IR(15850, 5)
  "Minus\0" // IR(15855, 6)
  "SPV_OPERAND_TYPE_LITERAL_INTEGER\0" // IR(15861, 33)
  "PlusUconst\0" // IR(15894, 11)
  "BitPiece\0" // IR(15905, 9)
  "Swap\0" // IR(15914, 5)
  "Xderef\0" // IR(15919, 7)
  "StackValue\0" // IR(15926, 11)
  "Constu\0" // IR(15937, 7)
  "Fragment\0" // IR(15944, 9)
  "ConstType\0" // IR(15953, 10)
  "VolatileType\0" // IR(15963, 13)
  "RestrictType\0" // IR(15976, 13)
  "AtomicType\0" // IR(15989, 11)
  "Float16NV\0" // IR(16000, 10)
  "Float32NV\0" // IR(16010, 10)
  "Float64NV\0" // IR(16020, 10)
  "SignedInt8NV\0" // IR(16030, 13)
  "SignedInt16NV\0" // IR(16043, 14)
  "SignedInt32NV\0" // IR(16057, 14)
  "SignedInt64NV\0" // IR(16071, 14)
  "UnsignedInt8NV\0" // IR(16085, 15)
  "UnsignedInt16NV\0" // IR(16100, 16)
  "UnsignedInt32NV\0" // IR(16116, 16)
  "UnsignedInt64NV\0" // IR(16132, 16)
  "SignedInt8PackedNV\0" // IR(16148, 19)
  "UnsignedInt8PackedNV\0" // IR(16167, 21)
  "FloatE4M3NV\0" // IR(16188, 12)
  "FloatE5M2NV\0" // IR(16200, 12)
  "RowMajorKHR\0" // IR(16212, 12)
  "ColumnMajorKHR\0" // IR(16224, 15)
  "RowBlockedInterleavedARM\0" // IR(16239, 25)
  "ColumnBlockedInterleavedARM\0" // IR(16264, 28)
  "NoneKHR\0" // IR(16292, 8)
  "MatrixASignedComponentsKHR\0" // IR(16300, 27)
  "MatrixBSignedComponentsKHR\0" // IR(16327, 27)
  "MatrixCSignedComponentsKHR\0" // IR(16354, 27)
  "MatrixResultSignedComponentsKHR\0" // IR(16381, 32)
  "SaturatingAccumulationKHR\0" // IR(16413, 26)
  "Row\0" // IR(16439, 4)
  "Column\0" // IR(16443, 7)
  "2x2\0" // IR(16450, 4)
  "MatrixAKHR\0" // IR(16454, 11)
  "MatrixBKHR\0" // IR(16465, 11)
  "MatrixAccumulatorKHR\0" // IR(16476, 21)
  "RowMajorNV\0" // IR(16497, 11)
  "ColumnMajorNV\0" // IR(16508, 14)
  "InferencingOptimalNV\0" // IR(16522, 21)
  "TrainingOptimalNV\0" // IR(16543, 18)
  "RelaxedPrecision\0" // IR(16561, 17)
  "SpecId\0" // IR(16578, 7)
  "Block\0" // IR(16585, 6)
  "BufferBlock\0" // IR(16591, 12)
  "RowMajor\0" // IR(16603, 9)
  "ColMajor\0" // IR(16612, 9)
  "ArrayStride\0" // IR(16621, 12)
  "MatrixStride\0" // IR(16633, 13)
  "GLSLShared\0" // IR(16646, 11)
  "GLSLPacked\0" // IR(16657, 11)
  "CPacked\0" // IR(16668, 8)
  "SPV_OPERAND_TYPE_BUILT_IN\0" // IR(16676, 26)
  "BuiltIn\0" // IR(16702, 8)
  "NoPerspective\0" // IR(16710, 14)
  "Flat\0" // IR(16724, 5)
  "Patch\0" // IR(16729, 6)
  "Centroid\0" // IR(16735, 9)
  "Sample\0" // IR(16744, 7)
  "Invariant\0" // IR(16751, 10)
  "Restrict\0" // IR(16761, 9)
  "Aliased\0" // IR(16770, 8)
  "Volatile\0" // IR(16778, 9)
  "Constant\0" // IR(16787, 9)
  "Coherent\0" // IR(16796, 9)
  "NonWritable\0" // IR(16805, 12)
  "NonReadable\0" // IR(16817, 12)
  "Uniform\0" // IR(16829, 8)
  "SPV_OPERAND_TYPE_SCOPE_ID\0" // IR(16837, 26)
  "UniformId\0" // IR(16863, 10)
  "SaturatedConversion\0" // IR(16873, 20)
  "Stream\0" // IR(16893, 7)
  "Location\0" // IR(16900, 9)
  "Component\0" // IR(16909, 10)
  "Index\0" // IR(16919, 6)
  "Binding\0" // IR(16925, 8)
  "DescriptorSet\0" // IR(16933, 14)
  "Offset\0" // IR(16947, 7)
  "XfbBuffer\0" // IR(16954, 10)
  "XfbStride\0" // IR(16964, 10)
  "SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE\0" // IR(16974, 46)
  "FuncParamAttr\0" // IR(17020, 14)
  "SPV_OPERAND_TYPE_FP_ROUNDING_MODE\0" // IR(17034, 34)
  "FPRoundingMode\0" // IR(17068, 15)
  "SPV_OPERAND_TYPE_FP_FAST_MATH_MODE\0" // IR(17083, 35)
  "FPFastMathMode\0" // IR(17118, 15)
  "SPV_OPERAND_TYPE_LITERAL_STRING\0" // IR(17133, 32)
  "SPV_OPERAND_TYPE_LINKAGE_TYPE\0" // IR(17165, 30)
  "LinkageAttributes\0" // IR(17195, 18)
  "NoContraction\0" // IR(17213, 14)
  "InputAttachmentIndex\0" // IR(17227, 21)
  "Alignment\0" // IR(17248, 10)
  "MaxByteOffset\0" // IR(17258, 14)
  "SPV_OPERAND_TYPE_ID\0" // IR(17272, 20)
  "AlignmentId\0" // IR(17292, 12)
  "MaxByteOffsetId\0" // IR(17304, 16)
  "SaturatedToLargestFloat8NormalConversionEXT\0" // IR(17320, 44)
  "NoSignedWrap\0" // IR(17364, 13)
  "NoUnsignedWrap\0" // IR(17377, 15)
  "WeightTextureQCOM\0" // IR(17392, 18)
  "BlockMatchTextureQCOM\0" // IR(17410, 22)
  "BlockMatchSamplerQCOM\0" // IR(17432, 22)
  "ExplicitInterpAMD\0" // IR(17454, 18)
  "NodeSharesPayloadLimitsWithAMDX\0" // IR(17472, 32)
  "NodeMaxPayloadsAMDX\0" // IR(17504, 20)
  "TrackFinishWritingAMDX\0" // IR(17524, 23)
  "PayloadNodeNameAMDX\0" // IR(17547, 20)
  "PayloadNodeBaseIndexAMDX\0" // IR(17567, 25)
  "PayloadNodeSparseArrayAMDX\0" // IR(17592, 27)
  "PayloadNodeArraySizeAMDX\0" // IR(17619, 25)
  "PayloadDispatchIndirectAMDX\0" // IR(17644, 28)
  "OverrideCoverageNV\0" // IR(17672, 19)
  "PassthroughNV\0" // IR(17691, 14)
  "ViewportRelativeNV\0" // IR(17705, 19)
  "SecondaryViewportRelativeNV\0" // IR(17724, 28)
  "PerPrimitiveEXT\0" // IR(17752, 16)
  "PerPrimitiveNV\0" // IR(17768, 15)
  "PerViewNV\0" // IR(17783, 10)
  "PerTaskNV\0" // IR(17793, 10)
  "PerVertexKHR\0" // IR(17803, 13)
  "PerVertexNV\0" // IR(17816, 12)
  "NonUniform\0" // IR(17828, 11)
  "NonUniformEXT\0" // IR(17839, 14)
  "RestrictPointer\0" // IR(17853, 16)
  "RestrictPointerEXT\0" // IR(17869, 19)
  "AliasedPointer\0" // IR(17888, 15)
  "AliasedPointerEXT\0" // IR(17903, 18)
  "HitObjectShaderRecordBufferNV\0" // IR(17921, 30)
  "HitObjectShaderRecordBufferEXT\0" // IR(17951, 31)
  "BindlessSamplerNV\0" // IR(17982, 18)
  "BindlessImageNV\0" // IR(18000, 16)
  "BoundSamplerNV\0" // IR(18016, 15)
  "BoundImageNV\0" // IR(18031, 13)
  "SIMTCallINTEL\0" // IR(18044, 14)
  "ReferencedIndirectlyINTEL\0" // IR(18058, 26)
  "ClobberINTEL\0" // IR(18084, 13)
  "SideEffectsINTEL\0" // IR(18097, 17)
  "VectorComputeVariableINTEL\0" // IR(18114, 27)
  "FuncParamIOKindINTEL\0" // IR(18141, 21)
  "VectorComputeFunctionINTEL\0" // IR(18162, 27)
  "StackCallINTEL\0" // IR(18189, 15)
  "GlobalVariableOffsetINTEL\0" // IR(18204, 26)
  "CounterBuffer\0" // IR(18230, 14)
  "HlslCounterBufferGOOGLE\0" // IR(18244, 24)
  "UserSemantic\0" // IR(18268, 13)
  "HlslSemanticGOOGLE\0" // IR(18281, 19)
  "UserTypeGOOGLE\0" // IR(18300, 15)
  "FunctionRoundingModeINTEL\0" // IR(18315, 26)
  "SPV_OPERAND_TYPE_FPDENORM_MODE\0" // IR(18341, 31)
  "FunctionDenormModeINTEL\0" // IR(18372, 24)
  "RegisterALTERA\0" // IR(18396, 15)
  "RegisterINTEL\0" // IR(18411, 14)
  "MemoryALTERA\0" // IR(18425, 13)
  "MemoryINTEL\0" // IR(18438, 12)
  "NumbanksALTERA\0" // IR(18450, 15)
  "NumbanksINTEL\0" // IR(18465, 14)
  "BankwidthALTERA\0" // IR(18479, 16)
  "BankwidthINTEL\0" // IR(18495, 15)
  "MaxPrivateCopiesALTERA\0" // IR(18510, 23)
  "MaxPrivateCopiesINTEL\0" // IR(18533, 22)
  "SinglepumpALTERA\0" // IR(18555, 17)
  "SinglepumpINTEL\0" // IR(18572, 16)
  "DoublepumpALTERA\0" // IR(18588, 17)
  "DoublepumpINTEL\0" // IR(18605, 16)
  "MaxReplicatesALTERA\0" // IR(18621, 20)
  "MaxReplicatesINTEL\0" // IR(18641, 19)
  "SimpleDualPortALTERA\0" // IR(18660, 21)
  "SimpleDualPortINTEL\0" // IR(18681, 20)
  "MergeALTERA\0" // IR(18701, 12)
  "MergeINTEL\0" // IR(18713, 11)
  "SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER\0" // IR(18724, 42)
  "BankBitsALTERA\0" // IR(18766, 15)
  "BankBitsINTEL\0" // IR(18781, 14)
  "ForcePow2DepthALTERA\0" // IR(18795, 21)
  "ForcePow2DepthINTEL\0" // IR(18816, 20)
  "StridesizeALTERA\0" // IR(18836, 17)
  "StridesizeINTEL\0" // IR(18853, 16)
  "WordsizeALTERA\0" // IR(18869, 15)
  "WordsizeINTEL\0" // IR(18884, 14)
  "TrueDualPortALTERA\0" // IR(18898, 19)
  "TrueDualPortINTEL\0" // IR(18917, 18)
  "BurstCoalesceALTERA\0" // IR(18935, 20)
  "BurstCoalesceINTEL\0" // IR(18955, 19)
  "CacheSizeALTERA\0" // IR(18974, 16)
  "CacheSizeINTEL\0" // IR(18990, 15)
  "DontStaticallyCoalesceALTERA\0" // IR(19005, 29)
  "DontStaticallyCoalesceINTEL\0" // IR(19034, 28)
  "PrefetchALTERA\0" // IR(19062, 15)
  "PrefetchINTEL\0" // IR(19077, 14)
  "StallEnableALTERA\0" // IR(19091, 18)
  "StallEnableINTEL\0" // IR(19109, 17)
  "FuseLoopsInFunctionALTERA\0" // IR(19126, 26)
  "FuseLoopsInFunctionINTEL\0" // IR(19152, 25)
  "MathOpDSPModeALTERA\0" // IR(19177, 20)
  "MathOpDSPModeINTEL\0" // IR(19197, 19)
  "AliasScopeINTEL\0" // IR(19216, 16)
  "NoAliasINTEL\0" // IR(19232, 13)
  "InitiationIntervalALTERA\0" // IR(19245, 25)
  "InitiationIntervalINTEL\0" // IR(19270, 24)
  "MaxConcurrencyALTERA\0" // IR(19294, 21)
  "MaxConcurrencyINTEL\0" // IR(19315, 20)
  "PipelineEnableALTERA\0" // IR(19335, 21)
  "PipelineEnableINTEL\0" // IR(19356, 20)
  "BufferLocationALTERA\0" // IR(19376, 21)
  "BufferLocationINTEL\0" // IR(19397, 20)
  "IOPipeStorageALTERA\0" // IR(19417, 20)
  "IOPipeStorageINTEL\0" // IR(19437, 19)
  "SPV_OPERAND_TYPE_FPOPERATION_MODE\0" // IR(19456, 34)
  "FunctionFloatingPointModeINTEL\0" // IR(19490, 31)
  "SingleElementVectorINTEL\0" // IR(19521, 25)
  "VectorComputeCallableFunctionINTEL\0" // IR(19546, 35)
  "MediaBlockIOINTEL\0" // IR(19581, 18)
  "StallFreeALTERA\0" // IR(19599, 16)
  "StallFreeINTEL\0" // IR(19615, 15)
  "SPV_OPERAND_TYPE_LITERAL_FLOAT\0" // IR(19630, 31)
  "FPMaxErrorDecorationINTEL\0" // IR(19661, 26)
  "LatencyControlLabelALTERA\0" // IR(19687, 26)
  "LatencyControlLabelINTEL\0" // IR(19713, 25)
  "LatencyControlConstraintALTERA\0" // IR(19738, 31)
  "LatencyControlConstraintINTEL\0" // IR(19769, 30)
  "ConduitKernelArgumentALTERA\0" // IR(19799, 28)
  "ConduitKernelArgumentINTEL\0" // IR(19827, 27)
  "RegisterMapKernelArgumentALTERA\0" // IR(19854, 32)
  "RegisterMapKernelArgumentINTEL\0" // IR(19886, 31)
  "MMHostInterfaceAddressWidthALTERA\0" // IR(19917, 34)
  "MMHostInterfaceAddressWidthINTEL\0" // IR(19951, 33)
  "MMHostInterfaceDataWidthALTERA\0" // IR(19984, 31)
  "MMHostInterfaceDataWidthINTEL\0" // IR(20015, 30)
  "MMHostInterfaceLatencyALTERA\0" // IR(20045, 29)
  "MMHostInterfaceLatencyINTEL\0" // IR(20074, 28)
  "SPV_OPERAND_TYPE_ACCESS_QUALIFIER\0" // IR(20102, 34)
  "MMHostInterfaceReadWriteModeALTERA\0" // IR(20136, 35)
  "MMHostInterfaceReadWriteModeINTEL\0" // IR(20171, 34)
  "MMHostInterfaceMaxBurstALTERA\0" // IR(20205, 30)
  "MMHostInterfaceMaxBurstINTEL\0" // IR(20235, 29)
  "MMHostInterfaceWaitRequestALTERA\0" // IR(20264, 33)
  "MMHostInterfaceWaitRequestINTEL\0" // IR(20297, 32)
  "StableKernelArgumentALTERA\0" // IR(20329, 27)
  "StableKernelArgumentINTEL\0" // IR(20356, 26)
  "SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER\0" // IR(20382, 39)
  "HostAccessINTEL\0" // IR(20421, 16)
  "SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER\0" // IR(20437, 47)
  "InitModeALTERA\0" // IR(20484, 15)
  "InitModeINTEL\0" // IR(20499, 14)
  "ImplementInRegisterMapALTERA\0" // IR(20513, 29)
  "ImplementInRegisterMapINTEL\0" // IR(20542, 28)
  "ConditionalINTEL\0" // IR(20570, 17)
  "SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL\0" // IR(20587, 36)
  "CacheControlLoadINTEL\0" // IR(20623, 22)
  "SPV_OPERAND_TYPE_STORE_CACHE_CONTROL\0" // IR(20645, 37)
  "CacheControlStoreINTEL\0" // IR(20682, 23)
  "1D\0" // IR(20705, 3)
  "2D\0" // IR(20708, 3)
  "3D\0" // IR(20711, 3)
  "Cube\0" // IR(20714, 5)
  "Rect\0" // IR(20719, 5)
  "Buffer\0" // IR(20724, 7)
  "SubpassData\0" // IR(20731, 12)
  "TileImageDataEXT\0" // IR(20743, 17)
  "Invocations\0" // IR(20760, 12)
  "SpacingEqual\0" // IR(20772, 13)
  "SpacingFractionalEven\0" // IR(20785, 22)
  "SpacingFractionalOdd\0" // IR(20807, 21)
  "VertexOrderCw\0" // IR(20828, 14)
  "VertexOrderCcw\0" // IR(20842, 15)
  "PixelCenterInteger\0" // IR(20857, 19)
  "OriginUpperLeft\0" // IR(20876, 16)
  "OriginLowerLeft\0" // IR(20892, 16)
  "EarlyFragmentTests\0" // IR(20908, 19)
  "PointMode\0" // IR(20927, 10)
  "Xfb\0" // IR(20937, 4)
  "DepthReplacing\0" // IR(20941, 15)
  "DepthGreater\0" // IR(20956, 13)
  "DepthLess\0" // IR(20969, 10)
  "DepthUnchanged\0" // IR(20979, 15)
  "LocalSize\0" // IR(20994, 10)
  "LocalSizeHint\0" // IR(21004, 14)
  "InputPoints\0" // IR(21018, 12)
  "InputLines\0" // IR(21030, 11)
  "InputLinesAdjacency\0" // IR(21041, 20)
  "Triangles\0" // IR(21061, 10)
  "InputTrianglesAdjacency\0" // IR(21071, 24)
  "Quads\0" // IR(21095, 6)
  "Isolines\0" // IR(21101, 9)
  "OutputVertices\0" // IR(21110, 15)
  "OutputPoints\0" // IR(21125, 13)
  "OutputLineStrip\0" // IR(21138, 16)
  "OutputTriangleStrip\0" // IR(21154, 20)
  "VecTypeHint\0" // IR(21174, 12)
  "ContractionOff\0" // IR(21186, 15)
  "Initializer\0" // IR(21201, 12)
  "Finalizer\0" // IR(21213, 10)
  "SubgroupsPerWorkgroup\0" // IR(21223, 22)
  "SubgroupsPerWorkgroupId\0" // IR(21245, 24)
  "LocalSizeId\0" // IR(21269, 12)
  "LocalSizeHintId\0" // IR(21281, 16)
  "NonCoherentColorAttachmentReadEXT\0" // IR(21297, 34)
  "NonCoherentDepthAttachmentReadEXT\0" // IR(21331, 34)
  "NonCoherentStencilAttachmentReadEXT\0" // IR(21365, 36)
  "SubgroupUniformControlFlowKHR\0" // IR(21401, 30)
  "PostDepthCoverage\0" // IR(21431, 18)
  "NonCoherentTileAttachmentReadQCOM\0" // IR(21449, 34)
  "TileShadingRateQCOM\0" // IR(21483, 20)
  "EarlyAndLateFragmentTestsAMD\0" // IR(21503, 29)
  "StencilRefReplacingEXT\0" // IR(21532, 23)
  "CoalescingAMDX\0" // IR(21555, 15)
  "IsApiEntryAMDX\0" // IR(21570, 15)
  "MaxNodeRecursionAMDX\0" // IR(21585, 21)
  "StaticNumWorkgroupsAMDX\0" // IR(21606, 24)
  "MaxNumWorkgroupsAMDX\0" // IR(21630, 21)
  "StencilRefUnchangedFrontAMD\0" // IR(21651, 28)
  "StencilRefGreaterFrontAMD\0" // IR(21679, 26)
  "StencilRefLessFrontAMD\0" // IR(21705, 23)
  "StencilRefUnchangedBackAMD\0" // IR(21728, 27)
  "StencilRefGreaterBackAMD\0" // IR(21755, 25)
  "StencilRefLessBackAMD\0" // IR(21780, 22)
  "QuadDerivativesKHR\0" // IR(21802, 19)
  "RequireFullQuadsKHR\0" // IR(21821, 20)
  "SharesInputWithAMDX\0" // IR(21841, 20)
  "OutputLinesEXT\0" // IR(21861, 15)
  "OutputLinesNV\0" // IR(21876, 14)
  "OutputPrimitivesEXT\0" // IR(21890, 20)
  "OutputPrimitivesNV\0" // IR(21910, 19)
  "DerivativeGroupQuadsKHR\0" // IR(21929, 24)
  "DerivativeGroupQuadsNV\0" // IR(21953, 23)
  "DerivativeGroupLinearKHR\0" // IR(21976, 25)
  "DerivativeGroupLinearNV\0" // IR(22001, 24)
  "OutputTrianglesEXT\0" // IR(22025, 19)
  "OutputTrianglesNV\0" // IR(22044, 18)
  "PixelInterlockOrderedEXT\0" // IR(22062, 25)
  "PixelInterlockUnorderedEXT\0" // IR(22087, 27)
  "SampleInterlockOrderedEXT\0" // IR(22114, 26)
  "SampleInterlockUnorderedEXT\0" // IR(22140, 28)
  "ShadingRateInterlockOrderedEXT\0" // IR(22168, 31)
  "ShadingRateInterlockUnorderedEXT\0" // IR(22199, 33)
  "SharedLocalMemorySizeINTEL\0" // IR(22232, 27)
  "RoundingModeRTPINTEL\0" // IR(22259, 21)
  "RoundingModeRTNINTEL\0" // IR(22280, 21)
  "FloatingPointModeALTINTEL\0" // IR(22301, 26)
  "FloatingPointModeIEEEINTEL\0" // IR(22327, 27)
  "MaxWorkgroupSizeINTEL\0" // IR(22354, 22)
  "MaxWorkDimINTEL\0" // IR(22376, 16)
  "NoGlobalOffsetINTEL\0" // IR(22392, 20)
  "NumSIMDWorkitemsINTEL\0" // IR(22412, 22)
  "SchedulerTargetFmaxMhzINTEL\0" // IR(22434, 28)
  "MaximallyReconvergesKHR\0" // IR(22462, 24)
  "FPFastMathDefault\0" // IR(22486, 18)
  "StreamingInterfaceINTEL\0" // IR(22504, 24)
  "RegisterMapInterfaceINTEL\0" // IR(22528, 26)
  "NamedBarrierCountINTEL\0" // IR(22554, 23)
  "MaximumRegistersINTEL\0" // IR(22577, 22)
  "MaximumRegistersIdINTEL\0" // IR(22599, 24)
  "SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS\0" // IR(22623, 51)
  "NamedMaximumRegistersINTEL\0" // IR(22674, 27)
  "Vertex\0" // IR(22701, 7)
  "TessellationControl\0" // IR(22708, 20)
  "TessellationEvaluation\0" // IR(22728, 23)
  "GLCompute\0" // IR(22751, 10)
  "TaskNV\0" // IR(22761, 7)
  "MeshNV\0" // IR(22768, 7)
  "RayGenerationKHR\0" // IR(22775, 17)
  "RayGenerationNV\0" // IR(22792, 16)
  "IntersectionKHR\0" // IR(22808, 16)
  "IntersectionNV\0" // IR(22824, 15)
  "AnyHitKHR\0" // IR(22839, 10)
  "AnyHitNV\0" // IR(22849, 9)
  "ClosestHitKHR\0" // IR(22858, 14)
  "ClosestHitNV\0" // IR(22872, 13)
  "MissKHR\0" // IR(22885, 8)
  "MissNV\0" // IR(22893, 7)
  "CallableKHR\0" // IR(22900, 12)
  "CallableNV\0" // IR(22912, 11)
  "TaskEXT\0" // IR(22923, 8)
  "MeshEXT\0" // IR(22931, 8)
  "Preserve\0" // IR(22939, 9)
  "FlushToZero\0" // IR(22948, 12)
  "BFloat16KHR\0" // IR(22960, 12)
  "Float8E4M3EXT\0" // IR(22972, 14)
  "Float8E5M2EXT\0" // IR(22986, 14)
  "IEEE\0" // IR(23000, 5)
  "ALT\0" // IR(23005, 4)
  "NotNaN\0" // IR(23009, 7)
  "NotInf\0" // IR(23016, 7)
  "NSZ\0" // IR(23023, 4)
  "AllowRecip\0" // IR(23027, 11)
  "Fast\0" // IR(23038, 5)
  "AllowContract\0" // IR(23043, 14)
  "AllowContractFastINTEL\0" // IR(23057, 23)
  "AllowReassoc\0" // IR(23080, 13)
  "AllowReassocINTEL\0" // IR(23093, 18)
  "AllowTransform\0" // IR(23111, 15)
  "RTE\0" // IR(23126, 4)
  "RTZ\0" // IR(23130, 4)
  "RTP\0" // IR(23134, 4)
  "RTN\0" // IR(23138, 4)
  "Vertical2Pixels\0" // IR(23142, 16)
  "Vertical4Pixels\0" // IR(23158, 16)
  "Horizontal2Pixels\0" // IR(23174, 18)
  "Horizontal4Pixels\0" // IR(23192, 18)
  "Inline\0" // IR(23210, 7)
  "DontInline\0" // IR(23217, 11)
  "Pure\0" // IR(23228, 5)
  "Const\0" // IR(23233, 6)
  "Zext\0" // IR(23239, 5)
  "Sext\0" // IR(23244, 5)
  "ByVal\0" // IR(23249, 6)
  "Sret\0" // IR(23255, 5)
  "NoAlias\0" // IR(23260, 8)
  "NoCapture\0" // IR(23268, 10)
  "NoWrite\0" // IR(23278, 8)
  "NoReadWrite\0" // IR(23286, 12)
  "RuntimeAlignedALTERA\0" // IR(23298, 21)
  "RuntimeAlignedINTEL\0" // IR(23319, 20)
  "Reduce\0" // IR(23339, 7)
  "InclusiveScan\0" // IR(23346, 14)
  "ExclusiveScan\0" // IR(23360, 14)
  "ClusteredReduce\0" // IR(23374, 16)
  "PartitionedReduceNV\0" // IR(23390, 20)
  "PartitionedInclusiveScanNV\0" // IR(23410, 27)
  "PartitionedExclusiveScanNV\0" // IR(23437, 27)
  "NoneINTEL\0" // IR(23464, 10)
  "ReadINTEL\0" // IR(23474, 10)
  "WriteINTEL\0" // IR(23484, 11)
  "ReadWriteINTEL\0" // IR(23495, 15)
  "Bias\0" // IR(23510, 5)
  "Lod\0" // IR(23515, 4)
  "Grad\0" // IR(23519, 5)
  "ConstOffset\0" // IR(23524, 12)
  "ConstOffsets\0" // IR(23536, 13)
  "MakeTexelAvailable\0" // IR(23549, 19)
  "MakeTexelAvailableKHR\0" // IR(23568, 22)
  "MakeTexelVisible\0" // IR(23590, 17)
  "MakeTexelVisibleKHR\0" // IR(23607, 20)
  "NonPrivateTexel\0" // IR(23627, 16)
  "NonPrivateTexelKHR\0" // IR(23643, 19)
  "VolatileTexel\0" // IR(23662, 14)
  "VolatileTexelKHR\0" // IR(23676, 17)
  "SignExtend\0" // IR(23693, 11)
  "ZeroExtend\0" // IR(23704, 11)
  "Nontemporal\0" // IR(23715, 12)
  "Offsets\0" // IR(23727, 8)
  "SnormInt8\0" // IR(23735, 10)
  "SnormInt16\0" // IR(23745, 11)
  "UnormInt8\0" // IR(23756, 10)
  "UnormInt16\0" // IR(23766, 11)
  "UnormShort565\0" // IR(23777, 14)
  "UnormShort555\0" // IR(23791, 14)
  "UnormInt101010\0" // IR(23805, 15)
  "SignedInt8\0" // IR(23820, 11)
  "SignedInt16\0" // IR(23831, 12)
  "SignedInt32\0" // IR(23843, 12)
  "UnsignedInt8\0" // IR(23855, 13)
  "UnsignedInt16\0" // IR(23868, 14)
  "UnsignedInt32\0" // IR(23882, 14)
  "HalfFloat\0" // IR(23896, 10)
  "UnormInt24\0" // IR(23906, 11)
  "UnormInt101010_2\0" // IR(23917, 17)
  "UnormInt10X6EXT\0" // IR(23934, 16)
  "UnsignedIntRaw10EXT\0" // IR(23950, 20)
  "UnsignedIntRaw12EXT\0" // IR(23970, 20)
  "UnormInt2_101010EXT\0" // IR(23990, 20)
  "UnsignedInt10X6EXT\0" // IR(24010, 19)
  "UnsignedInt12X4EXT\0" // IR(24029, 19)
  "UnsignedInt14X2EXT\0" // IR(24048, 19)
  "UnormInt12X4EXT\0" // IR(24067, 16)
  "UnormInt14X2EXT\0" // IR(24083, 16)
  "R\0" // IR(24099, 2)
  "A\0" // IR(24101, 2)
  "RG\0" // IR(24103, 3)
  "RA\0" // IR(24106, 3)
  "RGB\0" // IR(24109, 4)
  "RGBA\0" // IR(24113, 5)
  "BGRA\0" // IR(24118, 5)
  "ARGB\0" // IR(24123, 5)
  "Intensity\0" // IR(24128, 10)
  "Luminance\0" // IR(24138, 10)
  "Rx\0" // IR(24148, 3)
  "RGx\0" // IR(24151, 4)
  "RGBx\0" // IR(24155, 5)
  "Depth\0" // IR(24160, 6)
  "DepthStencil\0" // IR(24166, 13)
  "sRGB\0" // IR(24179, 5)
  "sRGBx\0" // IR(24184, 6)
  "sRGBA\0" // IR(24190, 6)
  "sBGRA\0" // IR(24196, 6)
  "ABGR\0" // IR(24202, 5)
  "InitOnDeviceReprogramALTERA\0" // IR(24207, 28)
  "InitOnDeviceReprogramINTEL\0" // IR(24235, 27)
  "InitOnDeviceResetALTERA\0" // IR(24262, 24)
  "InitOnDeviceResetINTEL\0" // IR(24286, 23)
  "NoWait\0" // IR(24309, 7)
  "WaitKernel\0" // IR(24316, 11)
  "WaitWorkGroup\0" // IR(24327, 14)
  "CmdExecTime\0" // IR(24341, 12)
  "MayUsePrintf\0" // IR(24353, 13)
  "Export\0" // IR(24366, 7)
  "Import\0" // IR(24373, 7)
  "LinkOnceODR\0" // IR(24380, 12)
  "UncachedINTEL\0" // IR(24392, 14)
  "CachedINTEL\0" // IR(24406, 12)
  "StreamingINTEL\0" // IR(24418, 15)
  "InvalidateAfterReadINTEL\0" // IR(24433, 25)
  "ConstCachedINTEL\0" // IR(24458, 17)
  "Unroll\0" // IR(24475, 7)
  "DontUnroll\0" // IR(24482, 11)
  "DependencyInfinite\0" // IR(24493, 19)
  "DependencyLength\0" // IR(24512, 17)
  "MinIterations\0" // IR(24529, 14)
  "MaxIterations\0" // IR(24543, 14)
  "IterationMultiple\0" // IR(24557, 18)
  "PeelCount\0" // IR(24575, 10)
  "PartialCount\0" // IR(24585, 13)
  "DependencyArrayALTERA\0" // IR(24598, 22)
  "DependencyArrayINTEL\0" // IR(24620, 21)
  "LoopCoalesceALTERA\0" // IR(24641, 19)
  "LoopCoalesceINTEL\0" // IR(24660, 18)
  "MaxInterleavingALTERA\0" // IR(24678, 22)
  "MaxInterleavingINTEL\0" // IR(24700, 21)
  "SpeculatedIterationsALTERA\0" // IR(24721, 27)
  "SpeculatedIterationsINTEL\0" // IR(24748, 26)
  "NoFusionALTERA\0" // IR(24774, 15)
  "NoFusionINTEL\0" // IR(24789, 14)
  "LoopCountALTERA\0" // IR(24803, 16)
  "LoopCountINTEL\0" // IR(24819, 15)
  "MaxReinvocationDelayALTERA\0" // IR(24834, 27)
  "MaxReinvocationDelayINTEL\0" // IR(24861, 26)
  "MatrixASignedComponentsINTEL\0" // IR(24887, 29)
  "MatrixBSignedComponentsINTEL\0" // IR(24916, 29)
  "MatrixCBFloat16INTEL\0" // IR(24945, 21)
  "MatrixResultBFloat16INTEL\0" // IR(24966, 26)
  "MatrixAPackedInt8INTEL\0" // IR(24992, 23)
  "MatrixBPackedInt8INTEL\0" // IR(25015, 23)
  "MatrixAPackedInt4INTEL\0" // IR(25038, 23)
  "MatrixBPackedInt4INTEL\0" // IR(25061, 23)
  "MatrixATF32INTEL\0" // IR(25084, 17)
  "MatrixBTF32INTEL\0" // IR(25101, 17)
  "MatrixAPackedFloat16INTEL\0" // IR(25118, 26)
  "MatrixBPackedFloat16INTEL\0" // IR(25144, 26)
  "MatrixAPackedBFloat16INTEL\0" // IR(25170, 27)
  "MatrixBPackedBFloat16INTEL\0" // IR(25197, 27)
  "Aligned\0" // IR(25224, 8)
  "MakePointerAvailable\0" // IR(25232, 21)
  "MakePointerAvailableKHR\0" // IR(25253, 24)
  "MakePointerVisible\0" // IR(25277, 19)
  "MakePointerVisibleKHR\0" // IR(25296, 22)
  "NonPrivatePointer\0" // IR(25318, 18)
  "NonPrivatePointerKHR\0" // IR(25336, 21)
  "AliasScopeINTELMask\0" // IR(25357, 20)
  "NoAliasINTELMask\0" // IR(25377, 17)
  "Simple\0" // IR(25394, 7)
  "GLSL450\0" // IR(25401, 8)
  "OpenCL\0" // IR(25409, 7)
  "Vulkan\0" // IR(25416, 7)
  "VulkanKHR\0" // IR(25423, 10)
  "Relaxed\0" // IR(25433, 8)
  "Acquire\0" // IR(25441, 8)
  "Release\0" // IR(25449, 8)
  "AcquireRelease\0" // IR(25457, 15)
  "SequentiallyConsistent\0" // IR(25472, 23)
  "UniformMemory\0" // IR(25495, 14)
  "SubgroupMemory\0" // IR(25509, 15)
  "WorkgroupMemory\0" // IR(25524, 16)
  "CrossWorkgroupMemory\0" // IR(25540, 21)
  "AtomicCounterMemory\0" // IR(25561, 20)
  "ImageMemory\0" // IR(25581, 12)
  "OutputMemory\0" // IR(25593, 13)
  "OutputMemoryKHR\0" // IR(25606, 16)
  "MakeAvailable\0" // IR(25622, 14)
  "MakeAvailableKHR\0" // IR(25636, 17)
  "MakeVisible\0" // IR(25653, 12)
  "MakeVisibleKHR\0" // IR(25665, 15)
  "AutoINTEL\0" // IR(25680, 10)
  "WRAP\0" // IR(25690, 5)
  "SAT\0" // IR(25695, 4)
  "SAT_ZERO\0" // IR(25699, 9)
  "SAT_SYM\0" // IR(25708, 8)
  "PackedVectorFormat4x8Bit\0" // IR(25716, 25)
  "PackedVectorFormat4x8BitKHR\0" // IR(25741, 28)
  "TRN\0" // IR(25769, 4)
  "TRN_ZERO\0" // IR(25773, 9)
  "RND\0" // IR(25782, 4)
  "RND_ZERO\0" // IR(25786, 9)
  "RND_INF\0" // IR(25795, 8)
  "RND_MIN_INF\0" // IR(25803, 12)
  "RND_CONV\0" // IR(25815, 9)
  "RND_CONV_ODD\0" // IR(25824, 13)
  "RobustnessPerComponentNV\0" // IR(25837, 25)
  "RobustnessPerElementNV\0" // IR(25862, 23)
  "OpaqueKHR\0" // IR(25885, 10)
  "NoOpaqueKHR\0" // IR(25895, 12)
  "TerminateOnFirstHitKHR\0" // IR(25907, 23)
  "SkipClosestHitShaderKHR\0" // IR(25930, 24)
  "CullBackFacingTrianglesKHR\0" // IR(25954, 27)
  "CullFrontFacingTrianglesKHR\0" // IR(25981, 28)
  "CullOpaqueKHR\0" // IR(26009, 14)
  "CullNoOpaqueKHR\0" // IR(26023, 16)
  "SkipTrianglesKHR\0" // IR(26039, 17)
  "SkipBuiltinPrimitivesNV\0" // IR(26056, 24)
  "SkipAABBsKHR\0" // IR(26080, 13)
  "ForceOpacityMicromap2StateEXT\0" // IR(26093, 30)
  "RayQueryCandidateIntersectionTriangleKHR\0" // IR(26123, 41)
  "RayQueryCandidateIntersectionAABBKHR\0" // IR(26164, 37)
  "RayQueryCommittedIntersectionNoneKHR\0" // IR(26201, 37)
  "RayQueryCommittedIntersectionTriangleKHR\0" // IR(26238, 41)
  "RayQueryCommittedIntersectionGeneratedKHR\0" // IR(26279, 42)
  "RayQueryCandidateIntersectionKHR\0" // IR(26321, 33)
  "RayQueryCommittedIntersectionKHR\0" // IR(26354, 33)
  "ClampToEdge\0" // IR(26387, 12)
  "Clamp\0" // IR(26399, 6)
  "Repeat\0" // IR(26405, 7)
  "RepeatMirrored\0" // IR(26412, 15)
  "Nearest\0" // IR(26427, 8)
  "Linear\0" // IR(26435, 7)
  "Unknown\0" // IR(26442, 8)
  "Rgba32f\0" // IR(26450, 8)
  "Rgba16f\0" // IR(26458, 8)
  "R32f\0" // IR(26466, 5)
  "Rgba8\0" // IR(26471, 6)
  "Rgba8Snorm\0" // IR(26477, 11)
  "Rg32f\0" // IR(26488, 6)
  "Rg16f\0" // IR(26494, 6)
  "R11fG11fB10f\0" // IR(26500, 13)
  "R16f\0" // IR(26513, 5)
  "Rgba16\0" // IR(26518, 7)
  "Rgb10A2\0" // IR(26525, 8)
  "Rg16\0" // IR(26533, 5)
  "Rg8\0" // IR(26538, 4)
  "R16\0" // IR(26542, 4)
  "R8\0" // IR(26546, 3)
  "Rgba16Snorm\0" // IR(26549, 12)
  "Rg16Snorm\0" // IR(26561, 10)
  "Rg8Snorm\0" // IR(26571, 9)
  "R16Snorm\0" // IR(26580, 9)
  "R8Snorm\0" // IR(26589, 8)
  "Rgba32i\0" // IR(26597, 8)
  "Rgba16i\0" // IR(26605, 8)
  "Rgba8i\0" // IR(26613, 7)
  "R32i\0" // IR(26620, 5)
  "Rg32i\0" // IR(26625, 6)
  "Rg16i\0" // IR(26631, 6)
  "Rg8i\0" // IR(26637, 5)
  "R16i\0" // IR(26642, 5)
  "R8i\0" // IR(26647, 4)
  "Rgba32ui\0" // IR(26651, 9)
  "Rgba16ui\0" // IR(26660, 9)
  "Rgba8ui\0" // IR(26669, 8)
  "R32ui\0" // IR(26677, 6)
  "Rgb10a2ui\0" // IR(26683, 10)
  "Rg32ui\0" // IR(26693, 7)
  "Rg16ui\0" // IR(26700, 7)
  "Rg8ui\0" // IR(26707, 6)
  "R16ui\0" // IR(26713, 6)
  "R8ui\0" // IR(26719, 5)
  "R64ui\0" // IR(26724, 6)
  "R64i\0" // IR(26730, 5)
  "CrossDevice\0" // IR(26735, 12)
  "Device\0" // IR(26747, 7)
  "Workgroup\0" // IR(26754, 10)
  "Subgroup\0" // IR(26764, 9)
  "Invocation\0" // IR(26773, 11)
  "QueueFamily\0" // IR(26784, 12)
  "QueueFamilyKHR\0" // IR(26796, 15)
  "ShaderCallKHR\0" // IR(26811, 14)
  "Flatten\0" // IR(26825, 8)
  "DontFlatten\0" // IR(26833, 12)
  "IdentifierPossibleDuplicates\0" // IR(26845, 29)
  "FlagUnknownPhysicalLayout\0" // IR(26874, 26)
  "ESSL\0" // IR(26900, 5)
  "GLSL\0" // IR(26905, 5)
  "OpenCL_C\0" // IR(26910, 9)
  "OpenCL_CPP\0" // IR(26919, 11)
  "HLSL\0" // IR(26930, 5)
  "CPP_for_OpenCL\0" // IR(26935, 15)
  "SYCL\0" // IR(26950, 5)
  "HERO_C\0" // IR(26955, 7)
  "NZSL\0" // IR(26962, 5)
  "WGSL\0" // IR(26967, 5)
  "Slang\0" // IR(26972, 6)
  "Zig\0" // IR(26978, 4)
  "Rust\0" // IR(26982, 5)
  "UniformConstant\0" // IR(26987, 16)
  "Input\0" // IR(27003, 6)
  "Output\0" // IR(27009, 7)
  "CrossWorkgroup\0" // IR(27016, 15)
  "Private\0" // IR(27031, 8)
  "Function\0" // IR(27039, 9)
  "Generic\0" // IR(27048, 8)
  "PushConstant\0" // IR(27056, 13)
  "AtomicCounter\0" // IR(27069, 14)
  "Image\0" // IR(27083, 6)
  "StorageBuffer\0" // IR(27089, 14)
  "TileImageEXT\0" // IR(27103, 13)
  "TileAttachmentQCOM\0" // IR(27116, 19)
  "NodePayloadAMDX\0" // IR(27135, 16)
  "CallableDataKHR\0" // IR(27151, 16)
  "CallableDataNV\0" // IR(27167, 15)
  "IncomingCallableDataKHR\0" // IR(27182, 24)
  "IncomingCallableDataNV\0" // IR(27206, 23)
  "RayPayloadKHR\0" // IR(27229, 14)
  "RayPayloadNV\0" // IR(27243, 13)
  "HitAttributeKHR\0" // IR(27256, 16)
  "HitAttributeNV\0" // IR(27272, 15)
  "IncomingRayPayloadKHR\0" // IR(27287, 22)
  "IncomingRayPayloadNV\0" // IR(27309, 21)
  "ShaderRecordBufferKHR\0" // IR(27330, 22)
  "ShaderRecordBufferNV\0" // IR(27352, 21)
  "PhysicalStorageBuffer\0" // IR(27373, 22)
  "PhysicalStorageBufferEXT\0" // IR(27395, 25)
  "HitObjectAttributeNV\0" // IR(27420, 21)
  "TaskPayloadWorkgroupEXT\0" // IR(27441, 24)
  "HitObjectAttributeEXT\0" // IR(27465, 22)
  "CodeSectionINTEL\0" // IR(27487, 17)
  "DeviceOnlyALTERA\0" // IR(27504, 17)
  "DeviceOnlyINTEL\0" // IR(27521, 16)
  "HostOnlyALTERA\0" // IR(27537, 15)
  "HostOnlyINTEL\0" // IR(27552, 14)
  "WriteThroughINTEL\0" // IR(27566, 18)
  "WriteBackINTEL\0" // IR(27584, 15)
  "TensorView\0" // IR(27599, 11)
  "DecodeFunc\0" // IR(27610, 11)
  "Undefined\0" // IR(27621, 10)
  "NoneARM\0" // IR(27631, 8)
  "NontemporalARM\0" // IR(27639, 15)
  "OutOfBoundsValueARM\0" // IR(27654, 20)
  "MakeElementAvailableARM\0" // IR(27674, 24)
  "MakeElementVisibleARM\0" // IR(27698, 22)
  "NonPrivateElementARM\0" // IR(27720, 21)
  "Nop\0" // IR(27741, 4)
  "SPV_OPERAND_TYPE_TYPE_ID\0" // IR(27745, 25)
  "SPV_OPERAND_TYPE_RESULT_ID\0" // IR(27770, 27)
  "Undef\0" // IR(27797, 6)
  "SourceContinued\0" // IR(27803, 16)
  "SPV_OPERAND_TYPE_SOURCE_LANGUAGE\0" // IR(27819, 33)
  "SPV_OPERAND_TYPE_OPTIONAL_ID\0" // IR(27852, 29)
  "SPV_OPERAND_TYPE_OPTIONAL_LITERAL_STRING\0" // IR(27881, 41)
  "Source\0" // IR(27922, 7)
  "SourceExtension\0" // IR(27929, 16)
  "Name\0" // IR(27945, 5)
  "MemberName\0" // IR(27950, 11)
  "String\0" // IR(27961, 7)
  "Line\0" // IR(27968, 5)
  "Extension\0" // IR(27973, 10)
  "ExtInstImport\0" // IR(27983, 14)
  "SPV_OPERAND_TYPE_EXTENSION_INSTRUCTION_NUMBER\0" // IR(27997, 46)
  "ExtInst\0" // IR(28043, 8)
  "SPV_OPERAND_TYPE_ADDRESSING_MODEL\0" // IR(28051, 34)
  "SPV_OPERAND_TYPE_MEMORY_MODEL\0" // IR(28085, 30)
  "MemoryModel\0" // IR(28115, 12)
  "SPV_OPERAND_TYPE_EXECUTION_MODEL\0" // IR(28127, 33)
  "SPV_OPERAND_TYPE_VARIABLE_ID\0" // IR(28160, 29)
  "EntryPoint\0" // IR(28189, 11)
  "SPV_OPERAND_TYPE_EXECUTION_MODE\0" // IR(28200, 32)
  "ExecutionMode\0" // IR(28232, 14)
  "SPV_OPERAND_TYPE_CAPABILITY\0" // IR(28246, 28)
  "Capability\0" // IR(28274, 11)
  "TypeVoid\0" // IR(28285, 9)
  "TypeBool\0" // IR(28294, 9)
  "TypeInt\0" // IR(28303, 8)
  "SPV_OPERAND_TYPE_OPTIONAL_FPENCODING\0" // IR(28311, 37)
  "TypeFloat\0" // IR(28348, 10)
  "TypeVector\0" // IR(28358, 11)
  "TypeMatrix\0" // IR(28369, 11)
  "SPV_OPERAND_TYPE_DIMENSIONALITY\0" // IR(28380, 32)
  "SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT\0" // IR(28412, 38)
  "SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER\0" // IR(28450, 43)
  "TypeImage\0" // IR(28493, 10)
  "TypeSampler\0" // IR(28503, 12)
  "TypeSampledImage\0" // IR(28515, 17)
  "TypeArray\0" // IR(28532, 10)
  "TypeRuntimeArray\0" // IR(28542, 17)
  "TypeStruct\0" // IR(28559, 11)
  "TypeOpaque\0" // IR(28570, 11)
  "SPV_OPERAND_TYPE_STORAGE_CLASS\0" // IR(28581, 31)
  "TypePointer\0" // IR(28612, 12)
  "TypeFunction\0" // IR(28624, 13)
  "TypeEvent\0" // IR(28637, 10)
  "TypeDeviceEvent\0" // IR(28647, 16)
  "TypeReserveId\0" // IR(28663, 14)
  "TypeQueue\0" // IR(28677, 10)
  "TypePipe\0" // IR(28687, 9)
  "TypeForwardPointer\0" // IR(28696, 19)
  "ConstantTrue\0" // IR(28715, 13)
  "ConstantFalse\0" // IR(28728, 14)
  "SPV_OPERAND_TYPE_TYPED_LITERAL_NUMBER\0" // IR(28742, 38)
  "ConstantComposite\0" // IR(28780, 18)
  "SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE\0" // IR(28798, 41)
  "SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE\0" // IR(28839, 37)
  "ConstantSampler\0" // IR(28876, 16)
  "ConstantNull\0" // IR(28892, 13)
  "SpecConstantTrue\0" // IR(28905, 17)
  "SpecConstantFalse\0" // IR(28922, 18)
  "SpecConstant\0" // IR(28940, 13)
  "SpecConstantComposite\0" // IR(28953, 22)
  "SPV_OPERAND_TYPE_SPEC_CONSTANT_OP_NUMBER\0" // IR(28975, 41)
  "SpecConstantOp\0" // IR(29016, 15)
  "SPV_OPERAND_TYPE_FUNCTION_CONTROL\0" // IR(29031, 34)
  "FunctionParameter\0" // IR(29065, 18)
  "FunctionEnd\0" // IR(29083, 12)
  "FunctionCall\0" // IR(29095, 13)
  "Variable\0" // IR(29108, 9)
  "ImageTexelPointer\0" // IR(29117, 18)
  "SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS\0" // IR(29135, 40)
  "Load\0" // IR(29175, 5)
  "Store\0" // IR(29180, 6)
  "CopyMemory\0" // IR(29186, 11)
  "CopyMemorySized\0" // IR(29197, 16)
  "AccessChain\0" // IR(29213, 12)
  "InBoundsAccessChain\0" // IR(29225, 20)
  "PtrAccessChain\0" // IR(29245, 15)
  "ArrayLength\0" // IR(29260, 12)
  "GenericPtrMemSemantics\0" // IR(29272, 23)
  "InBoundsPtrAccessChain\0" // IR(29295, 23)
  "SPV_OPERAND_TYPE_DECORATION\0" // IR(29318, 28)
  "Decorate\0" // IR(29346, 9)
  "MemberDecorate\0" // IR(29355, 15)
  "DecorationGroup\0" // IR(29370, 16)
  "GroupDecorate\0" // IR(29386, 14)
  "SPV_OPERAND_TYPE_VARIABLE_ID_LITERAL_INTEGER\0" // IR(29400, 45)
  "GroupMemberDecorate\0" // IR(29445, 20)
  "VectorExtractDynamic\0" // IR(29465, 21)
  "VectorInsertDynamic\0" // IR(29486, 20)
  "VectorShuffle\0" // IR(29506, 14)
  "CompositeConstruct\0" // IR(29520, 19)
  "CompositeExtract\0" // IR(29539, 17)
  "CompositeInsert\0" // IR(29556, 16)
  "CopyObject\0" // IR(29572, 11)
  "Transpose\0" // IR(29583, 10)
  "SampledImage\0" // IR(29593, 13)
  "SPV_OPERAND_TYPE_OPTIONAL_IMAGE\0" // IR(29606, 32)
  "ImageSampleImplicitLod\0" // IR(29638, 23)
  "SPV_OPERAND_TYPE_IMAGE\0" // IR(29661, 23)
  "ImageSampleExplicitLod\0" // IR(29684, 23)
  "ImageSampleDrefImplicitLod\0" // IR(29707, 27)
  "ImageSampleDrefExplicitLod\0" // IR(29734, 27)
  "ImageSampleProjImplicitLod\0" // IR(29761, 27)
  "ImageSampleProjExplicitLod\0" // IR(29788, 27)
  "ImageSampleProjDrefImplicitLod\0" // IR(29815, 31)
  "ImageSampleProjDrefExplicitLod\0" // IR(29846, 31)
  "ImageFetch\0" // IR(29877, 11)
  "ImageGather\0" // IR(29888, 12)
  "ImageDrefGather\0" // IR(29900, 16)
  "ImageRead\0" // IR(29916, 10)
  "ImageWrite\0" // IR(29926, 11)
  "ImageQueryFormat\0" // IR(29937, 17)
  "ImageQueryOrder\0" // IR(29954, 16)
  "ImageQuerySizeLod\0" // IR(29970, 18)
  "ImageQuerySize\0" // IR(29988, 15)
  "ImageQueryLod\0" // IR(30003, 14)
  "ImageQueryLevels\0" // IR(30017, 17)
  "ImageQuerySamples\0" // IR(30034, 18)
  "ConvertFToU\0" // IR(30052, 12)
  "ConvertFToS\0" // IR(30064, 12)
  "ConvertSToF\0" // IR(30076, 12)
  "ConvertUToF\0" // IR(30088, 12)
  "UConvert\0" // IR(30100, 9)
  "SConvert\0" // IR(30109, 9)
  "FConvert\0" // IR(30118, 9)
  "QuantizeToF16\0" // IR(30127, 14)
  "ConvertPtrToU\0" // IR(30141, 14)
  "SatConvertSToU\0" // IR(30155, 15)
  "SatConvertUToS\0" // IR(30170, 15)
  "ConvertUToPtr\0" // IR(30185, 14)
  "PtrCastToGeneric\0" // IR(30199, 17)
  "GenericCastToPtr\0" // IR(30216, 17)
  "GenericCastToPtrExplicit\0" // IR(30233, 25)
  "Bitcast\0" // IR(30258, 8)
  "SNegate\0" // IR(30266, 8)
  "FNegate\0" // IR(30274, 8)
  "IAdd\0" // IR(30282, 5)
  "FAdd\0" // IR(30287, 5)
  "ISub\0" // IR(30292, 5)
  "FSub\0" // IR(30297, 5)
  "IMul\0" // IR(30302, 5)
  "FMul\0" // IR(30307, 5)
  "UDiv\0" // IR(30312, 5)
  "SDiv\0" // IR(30317, 5)
  "FDiv\0" // IR(30322, 5)
  "UMod\0" // IR(30327, 5)
  "SRem\0" // IR(30332, 5)
  "SMod\0" // IR(30337, 5)
  "FRem\0" // IR(30342, 5)
  "FMod\0" // IR(30347, 5)
  "VectorTimesScalar\0" // IR(30352, 18)
  "MatrixTimesScalar\0" // IR(30370, 18)
  "VectorTimesMatrix\0" // IR(30388, 18)
  "MatrixTimesVector\0" // IR(30406, 18)
  "MatrixTimesMatrix\0" // IR(30424, 18)
  "OuterProduct\0" // IR(30442, 13)
  "Dot\0" // IR(30455, 4)
  "IAddCarry\0" // IR(30459, 10)
  "ISubBorrow\0" // IR(30469, 11)
  "UMulExtended\0" // IR(30480, 13)
  "SMulExtended\0" // IR(30493, 13)
  "Any\0" // IR(30506, 4)
  "All\0" // IR(30510, 4)
  "IsNan\0" // IR(30514, 6)
  "IsInf\0" // IR(30520, 6)
  "IsFinite\0" // IR(30526, 9)
  "IsNormal\0" // IR(30535, 9)
  "SignBitSet\0" // IR(30544, 11)
  "LessOrGreater\0" // IR(30555, 14)
  "Ordered\0" // IR(30569, 8)
  "Unordered\0" // IR(30577, 10)
  "LogicalEqual\0" // IR(30587, 13)
  "LogicalNotEqual\0" // IR(30600, 16)
  "LogicalOr\0" // IR(30616, 10)
  "LogicalAnd\0" // IR(30626, 11)
  "LogicalNot\0" // IR(30637, 11)
  "Select\0" // IR(30648, 7)
  "IEqual\0" // IR(30655, 7)
  "INotEqual\0" // IR(30662, 10)
  "UGreaterThan\0" // IR(30672, 13)
  "SGreaterThan\0" // IR(30685, 13)
  "UGreaterThanEqual\0" // IR(30698, 18)
  "SGreaterThanEqual\0" // IR(30716, 18)
  "ULessThan\0" // IR(30734, 10)
  "SLessThan\0" // IR(30744, 10)
  "ULessThanEqual\0" // IR(30754, 15)
  "SLessThanEqual\0" // IR(30769, 15)
  "FOrdEqual\0" // IR(30784, 10)
  "FUnordEqual\0" // IR(30794, 12)
  "FOrdNotEqual\0" // IR(30806, 13)
  "FUnordNotEqual\0" // IR(30819, 15)
  "FOrdLessThan\0" // IR(30834, 13)
  "FUnordLessThan\0" // IR(30847, 15)
  "FOrdGreaterThan\0" // IR(30862, 16)
  "FUnordGreaterThan\0" // IR(30878, 18)
  "FOrdLessThanEqual\0" // IR(30896, 18)
  "FUnordLessThanEqual\0" // IR(30914, 20)
  "FOrdGreaterThanEqual\0" // IR(30934, 21)
  "FUnordGreaterThanEqual\0" // IR(30955, 23)
  "ShiftRightLogical\0" // IR(30978, 18)
  "ShiftRightArithmetic\0" // IR(30996, 21)
  "ShiftLeftLogical\0" // IR(31017, 17)
  "BitwiseOr\0" // IR(31034, 10)
  "BitwiseXor\0" // IR(31044, 11)
  "BitwiseAnd\0" // IR(31055, 11)
  "Not\0" // IR(31066, 4)
  "BitFieldInsert\0" // IR(31070, 15)
  "BitFieldSExtract\0" // IR(31085, 17)
  "BitFieldUExtract\0" // IR(31102, 17)
  "BitReverse\0" // IR(31119, 11)
  "BitCount\0" // IR(31130, 9)
  "DPdx\0" // IR(31139, 5)
  "DPdy\0" // IR(31144, 5)
  "Fwidth\0" // IR(31149, 7)
  "DPdxFine\0" // IR(31156, 9)
  "DPdyFine\0" // IR(31165, 9)
  "FwidthFine\0" // IR(31174, 11)
  "DPdxCoarse\0" // IR(31185, 11)
  "DPdyCoarse\0" // IR(31196, 11)
  "FwidthCoarse\0" // IR(31207, 13)
  "EmitVertex\0" // IR(31220, 11)
  "EndPrimitive\0" // IR(31231, 13)
  "EmitStreamVertex\0" // IR(31244, 17)
  "EndStreamPrimitive\0" // IR(31261, 19)
  "SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID\0" // IR(31280, 37)
  "ControlBarrier\0" // IR(31317, 15)
  "MemoryBarrier\0" // IR(31332, 14)
  "AtomicLoad\0" // IR(31346, 11)
  "AtomicStore\0" // IR(31357, 12)
  "AtomicExchange\0" // IR(31369, 15)
  "AtomicCompareExchange\0" // IR(31384, 22)
  "AtomicCompareExchangeWeak\0" // IR(31406, 26)
  "AtomicIIncrement\0" // IR(31432, 17)
  "AtomicIDecrement\0" // IR(31449, 17)
  "AtomicIAdd\0" // IR(31466, 11)
  "AtomicISub\0" // IR(31477, 11)
  "AtomicSMin\0" // IR(31488, 11)
  "AtomicUMin\0" // IR(31499, 11)
  "AtomicSMax\0" // IR(31510, 11)
  "AtomicUMax\0" // IR(31521, 11)
  "AtomicAnd\0" // IR(31532, 10)
  "AtomicOr\0" // IR(31542, 9)
  "AtomicXor\0" // IR(31551, 10)
  "Phi\0" // IR(31561, 4)
  "SPV_OPERAND_TYPE_LOOP_CONTROL\0" // IR(31565, 30)
  "LoopMerge\0" // IR(31595, 10)
  "SPV_OPERAND_TYPE_SELECTION_CONTROL\0" // IR(31605, 35)
  "SelectionMerge\0" // IR(31640, 15)
  "Label\0" // IR(31655, 6)
  "Branch\0" // IR(31661, 7)
  "BranchConditional\0" // IR(31668, 18)
  "SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER_ID\0" // IR(31686, 45)
  "Switch\0" // IR(31731, 7)
  "Kill\0" // IR(31738, 5)
  "Return\0" // IR(31743, 7)
  "ReturnValue\0" // IR(31750, 12)
  "Unreachable\0" // IR(31762, 12)
  "LifetimeStart\0" // IR(31774, 14)
  "LifetimeStop\0" // IR(31788, 13)
  "GroupAsyncCopy\0" // IR(31801, 15)
  "GroupWaitEvents\0" // IR(31816, 16)
  "GroupAll\0" // IR(31832, 9)
  "GroupAny\0" // IR(31841, 9)
  "GroupBroadcast\0" // IR(31850, 15)
  "SPV_OPERAND_TYPE_GROUP_OPERATION\0" // IR(31865, 33)
  "GroupIAdd\0" // IR(31898, 10)
  "GroupFAdd\0" // IR(31908, 10)
  "GroupFMin\0" // IR(31918, 10)
  "GroupUMin\0" // IR(31928, 10)
  "GroupSMin\0" // IR(31938, 10)
  "GroupFMax\0" // IR(31948, 10)
  "GroupUMax\0" // IR(31958, 10)
  "GroupSMax\0" // IR(31968, 10)
  "ReadPipe\0" // IR(31978, 9)
  "WritePipe\0" // IR(31987, 10)
  "ReservedReadPipe\0" // IR(31997, 17)
  "ReservedWritePipe\0" // IR(32014, 18)
  "ReserveReadPipePackets\0" // IR(32032, 23)
  "ReserveWritePipePackets\0" // IR(32055, 24)
  "CommitReadPipe\0" // IR(32079, 15)
  "CommitWritePipe\0" // IR(32094, 16)
  "IsValidReserveId\0" // IR(32110, 17)
  "GetNumPipePackets\0" // IR(32127, 18)
  "GetMaxPipePackets\0" // IR(32145, 18)
  "GroupReserveReadPipePackets\0" // IR(32163, 28)
  "GroupReserveWritePipePackets\0" // IR(32191, 29)
  "GroupCommitReadPipe\0" // IR(32220, 20)
  "GroupCommitWritePipe\0" // IR(32240, 21)
  "EnqueueMarker\0" // IR(32261, 14)
  "EnqueueKernel\0" // IR(32275, 14)
  "GetKernelNDrangeSubGroupCount\0" // IR(32289, 30)
  "GetKernelNDrangeMaxSubGroupSize\0" // IR(32319, 32)
  "GetKernelWorkGroupSize\0" // IR(32351, 23)
  "GetKernelPreferredWorkGroupSizeMultiple\0" // IR(32374, 40)
  "RetainEvent\0" // IR(32414, 12)
  "ReleaseEvent\0" // IR(32426, 13)
  "CreateUserEvent\0" // IR(32439, 16)
  "IsValidEvent\0" // IR(32455, 13)
  "SetUserEventStatus\0" // IR(32468, 19)
  "CaptureEventProfilingInfo\0" // IR(32487, 26)
  "GetDefaultQueue\0" // IR(32513, 16)
  "BuildNDRange\0" // IR(32529, 13)
  "ImageSparseSampleImplicitLod\0" // IR(32542, 29)
  "ImageSparseSampleExplicitLod\0" // IR(32571, 29)
  "ImageSparseSampleDrefImplicitLod\0" // IR(32600, 33)
  "ImageSparseSampleDrefExplicitLod\0" // IR(32633, 33)
  "ImageSparseSampleProjImplicitLod\0" // IR(32666, 33)
  "ImageSparseSampleProjExplicitLod\0" // IR(32699, 33)
  "ImageSparseSampleProjDrefImplicitLod\0" // IR(32732, 37)
  "ImageSparseSampleProjDrefExplicitLod\0" // IR(32769, 37)
  "ImageSparseFetch\0" // IR(32806, 17)
  "ImageSparseGather\0" // IR(32823, 18)
  "ImageSparseDrefGather\0" // IR(32841, 22)
  "ImageSparseTexelsResident\0" // IR(32863, 26)
  "NoLine\0" // IR(32889, 7)
  "AtomicFlagTestAndSet\0" // IR(32896, 21)
  "AtomicFlagClear\0" // IR(32917, 16)
  "ImageSparseRead\0" // IR(32933, 16)
  "SizeOf\0" // IR(32949, 7)
  "TypePipeStorage\0" // IR(32956, 16)
  "ConstantPipeStorage\0" // IR(32972, 20)
  "CreatePipeFromPipeStorage\0" // IR(32992, 26)
  "GetKernelLocalSizeForSubgroupCount\0" // IR(33018, 35)
  "GetKernelMaxNumSubgroups\0" // IR(33053, 25)
  "TypeNamedBarrier\0" // IR(33078, 17)
  "NamedBarrierInitialize\0" // IR(33095, 23)
  "MemoryNamedBarrier\0" // IR(33118, 19)
  "ModuleProcessed\0" // IR(33137, 16)
  "ExecutionModeId\0" // IR(33153, 16)
  "DecorateId\0" // IR(33169, 11)
  "GroupNonUniformElect\0" // IR(33180, 21)
  "GroupNonUniformAll\0" // IR(33201, 19)
  "GroupNonUniformAny\0" // IR(33220, 19)
  "GroupNonUniformAllEqual\0" // IR(33239, 24)
  "GroupNonUniformBroadcast\0" // IR(33263, 25)
  "GroupNonUniformBroadcastFirst\0" // IR(33288, 30)
  "GroupNonUniformInverseBallot\0" // IR(33318, 29)
  "GroupNonUniformBallotBitExtract\0" // IR(33347, 32)
  "GroupNonUniformBallotBitCount\0" // IR(33379, 30)
  "GroupNonUniformBallotFindLSB\0" // IR(33409, 29)
  "GroupNonUniformBallotFindMSB\0" // IR(33438, 29)
  "GroupNonUniformShuffleXor\0" // IR(33467, 26)
  "GroupNonUniformShuffleUp\0" // IR(33493, 25)
  "GroupNonUniformShuffleDown\0" // IR(33518, 27)
  "GroupNonUniformIAdd\0" // IR(33545, 20)
  "GroupNonUniformFAdd\0" // IR(33565, 20)
  "GroupNonUniformIMul\0" // IR(33585, 20)
  "GroupNonUniformFMul\0" // IR(33605, 20)
  "GroupNonUniformSMin\0" // IR(33625, 20)
  "GroupNonUniformUMin\0" // IR(33645, 20)
  "GroupNonUniformFMin\0" // IR(33665, 20)
  "GroupNonUniformSMax\0" // IR(33685, 20)
  "GroupNonUniformUMax\0" // IR(33705, 20)
  "GroupNonUniformFMax\0" // IR(33725, 20)
  "GroupNonUniformBitwiseAnd\0" // IR(33745, 26)
  "GroupNonUniformBitwiseOr\0" // IR(33771, 25)
  "GroupNonUniformBitwiseXor\0" // IR(33796, 26)
  "GroupNonUniformLogicalAnd\0" // IR(33822, 26)
  "GroupNonUniformLogicalOr\0" // IR(33848, 25)
  "GroupNonUniformLogicalXor\0" // IR(33873, 26)
  "GroupNonUniformQuadBroadcast\0" // IR(33899, 29)
  "GroupNonUniformQuadSwap\0" // IR(33928, 24)
  "CopyLogical\0" // IR(33952, 12)
  "PtrEqual\0" // IR(33964, 9)
  "PtrNotEqual\0" // IR(33973, 12)
  "PtrDiff\0" // IR(33985, 8)
  "ColorAttachmentReadEXT\0" // IR(33993, 23)
  "DepthAttachmentReadEXT\0" // IR(34016, 23)
  "StencilAttachmentReadEXT\0" // IR(34039, 25)
  "TypeTensorARM\0" // IR(34064, 14)
  "SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS\0" // IR(34078, 42)
  "TensorReadARM\0" // IR(34120, 14)
  "TensorWriteARM\0" // IR(34134, 15)
  "TensorQuerySizeARM\0" // IR(34149, 19)
  "GraphConstantARM\0" // IR(34168, 17)
  "GraphEntryPointARM\0" // IR(34185, 19)
  "GraphInputARM\0" // IR(34204, 14)
  "GraphSetOutputARM\0" // IR(34218, 18)
  "GraphEndARM\0" // IR(34236, 12)
  "TypeGraphARM\0" // IR(34248, 13)
  "TerminateInvocation\0" // IR(34261, 20)
  "TypeUntypedPointerKHR\0" // IR(34281, 22)
  "UntypedVariableKHR\0" // IR(34303, 19)
  "UntypedAccessChainKHR\0" // IR(34322, 22)
  "UntypedInBoundsAccessChainKHR\0" // IR(34344, 30)
  "SubgroupFirstInvocationKHR\0" // IR(34374, 27)
  "UntypedPtrAccessChainKHR\0" // IR(34401, 25)
  "UntypedInBoundsPtrAccessChainKHR\0" // IR(34426, 33)
  "UntypedArrayLengthKHR\0" // IR(34459, 22)
  "UntypedPrefetchKHR\0" // IR(34481, 19)
  "FmaKHR\0" // IR(34500, 7)
  "SubgroupAllKHR\0" // IR(34507, 15)
  "SubgroupAnyKHR\0" // IR(34522, 15)
  "SubgroupAllEqualKHR\0" // IR(34537, 20)
  "SubgroupReadInvocationKHR\0" // IR(34557, 26)
  "ExtInstWithForwardRefsKHR\0" // IR(34583, 26)
  "UntypedGroupAsyncCopyKHR\0" // IR(34609, 25)
  "TraceRayKHR\0" // IR(34634, 12)
  "ExecuteCallableKHR\0" // IR(34646, 19)
  "ConvertUToAccelerationStructureKHR\0" // IR(34665, 35)
  "IgnoreIntersectionKHR\0" // IR(34700, 22)
  "TerminateRayKHR\0" // IR(34722, 16)
  "SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT\0" // IR(34738, 47)
  "SDot\0" // IR(34785, 5)
  "SDotKHR\0" // IR(34790, 8)
  "UDot\0" // IR(34798, 5)
  "UDotKHR\0" // IR(34803, 8)
  "SUDot\0" // IR(34811, 6)
  "SUDotKHR\0" // IR(34817, 9)
  "SDotAccSat\0" // IR(34826, 11)
  "SDotAccSatKHR\0" // IR(34837, 14)
  "UDotAccSat\0" // IR(34851, 11)
  "UDotAccSatKHR\0" // IR(34862, 14)
  "SUDotAccSat\0" // IR(34876, 12)
  "SUDotAccSatKHR\0" // IR(34888, 15)
  "TypeCooperativeMatrixKHR\0" // IR(34903, 25)
  "CooperativeMatrixLoadKHR\0" // IR(34928, 25)
  "CooperativeMatrixStoreKHR\0" // IR(34953, 26)
  "SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS\0" // IR(34979, 54)
  "CooperativeMatrixMulAddKHR\0" // IR(35033, 27)
  "CooperativeMatrixLengthKHR\0" // IR(35060, 27)
  "ConstantCompositeReplicateEXT\0" // IR(35087, 30)
  "SpecConstantCompositeReplicateEXT\0" // IR(35117, 34)
  "CompositeConstructReplicateEXT\0" // IR(35151, 31)
  "TypeRayQueryKHR\0" // IR(35182, 16)
  "RayQueryInitializeKHR\0" // IR(35198, 22)
  "RayQueryTerminateKHR\0" // IR(35220, 21)
  "RayQueryGenerateIntersectionKHR\0" // IR(35241, 32)
  "RayQueryConfirmIntersectionKHR\0" // IR(35273, 31)
  "RayQueryProceedKHR\0" // IR(35304, 19)
  "RayQueryGetIntersectionTypeKHR\0" // IR(35323, 31)
  "ImageSampleWeightedQCOM\0" // IR(35354, 24)
  "ImageBoxFilterQCOM\0" // IR(35378, 19)
  "ImageBlockMatchSSDQCOM\0" // IR(35397, 23)
  "ImageBlockMatchSADQCOM\0" // IR(35420, 23)
  "BitCastArrayQCOM\0" // IR(35443, 17)
  "ImageBlockMatchWindowSSDQCOM\0" // IR(35460, 29)
  "ImageBlockMatchWindowSADQCOM\0" // IR(35489, 29)
  "ImageBlockMatchGatherSSDQCOM\0" // IR(35518, 29)
  "ImageBlockMatchGatherSADQCOM\0" // IR(35547, 29)
  "CompositeConstructCoopMatQCOM\0" // IR(35576, 30)
  "CompositeExtractCoopMatQCOM\0" // IR(35606, 28)
  "ExtractSubArrayQCOM\0" // IR(35634, 20)
  "GroupIAddNonUniformAMD\0" // IR(35654, 23)
  "GroupFAddNonUniformAMD\0" // IR(35677, 23)
  "GroupFMinNonUniformAMD\0" // IR(35700, 23)
  "GroupUMinNonUniformAMD\0" // IR(35723, 23)
  "GroupSMinNonUniformAMD\0" // IR(35746, 23)
  "GroupFMaxNonUniformAMD\0" // IR(35769, 23)
  "GroupUMaxNonUniformAMD\0" // IR(35792, 23)
  "GroupSMaxNonUniformAMD\0" // IR(35815, 23)
  "FragmentMaskFetchAMD\0" // IR(35838, 21)
  "FragmentFetchAMD\0" // IR(35859, 17)
  "ReadClockKHR\0" // IR(35876, 13)
  "AllocateNodePayloadsAMDX\0" // IR(35889, 25)
  "EnqueueNodePayloadsAMDX\0" // IR(35914, 24)
  "TypeNodePayloadArrayAMDX\0" // IR(35938, 25)
  "FinishWritingNodePayloadAMDX\0" // IR(35963, 29)
  "NodePayloadArrayLengthAMDX\0" // IR(35992, 27)
  "IsNodePayloadValidAMDX\0" // IR(36019, 23)
  "ConstantStringAMDX\0" // IR(36042, 19)
  "SpecConstantStringAMDX\0" // IR(36061, 23)
  "GroupNonUniformQuadAllKHR\0" // IR(36084, 26)
  "GroupNonUniformQuadAnyKHR\0" // IR(36110, 26)
  "HitObjectRecordHitMotionNV\0" // IR(36136, 27)
  "HitObjectRecordHitWithIndexMotionNV\0" // IR(36163, 36)
  "HitObjectRecordMissMotionNV\0" // IR(36199, 28)
  "HitObjectGetWorldToObjectNV\0" // IR(36227, 28)
  "HitObjectGetObjectToWorldNV\0" // IR(36255, 28)
  "HitObjectGetObjectRayDirectionNV\0" // IR(36283, 33)
  "HitObjectGetObjectRayOriginNV\0" // IR(36316, 30)
  "HitObjectTraceRayMotionNV\0" // IR(36346, 26)
  "HitObjectGetShaderRecordBufferHandleNV\0" // IR(36372, 39)
  "HitObjectGetShaderBindingTableRecordIndexNV\0" // IR(36411, 44)
  "HitObjectRecordEmptyNV\0" // IR(36455, 23)
  "HitObjectTraceRayNV\0" // IR(36478, 20)
  "HitObjectRecordHitNV\0" // IR(36498, 21)
  "HitObjectRecordHitWithIndexNV\0" // IR(36519, 30)
  "HitObjectRecordMissNV\0" // IR(36549, 22)
  "HitObjectExecuteShaderNV\0" // IR(36571, 25)
  "HitObjectGetCurrentTimeNV\0" // IR(36596, 26)
  "HitObjectGetAttributesNV\0" // IR(36622, 25)
  "HitObjectGetHitKindNV\0" // IR(36647, 22)
  "HitObjectGetPrimitiveIndexNV\0" // IR(36669, 29)
  "HitObjectGetGeometryIndexNV\0" // IR(36698, 28)
  "HitObjectGetInstanceIdNV\0" // IR(36726, 25)
  "HitObjectGetInstanceCustomIndexNV\0" // IR(36751, 34)
  "HitObjectGetWorldRayDirectionNV\0" // IR(36785, 32)
  "HitObjectGetWorldRayOriginNV\0" // IR(36817, 29)
  "HitObjectGetRayTMaxNV\0" // IR(36846, 22)
  "HitObjectGetRayTMinNV\0" // IR(36868, 22)
  "HitObjectIsEmptyNV\0" // IR(36890, 19)
  "HitObjectIsHitNV\0" // IR(36909, 17)
  "HitObjectIsMissNV\0" // IR(36926, 18)
  "ReorderThreadWithHitObjectNV\0" // IR(36944, 29)
  "ReorderThreadWithHintNV\0" // IR(36973, 24)
  "TypeHitObjectNV\0" // IR(36997, 16)
  "ImageSampleFootprintNV\0" // IR(37013, 23)
  "TypeCooperativeVectorNV\0" // IR(37036, 24)
  "CooperativeVectorMatrixMulNV\0" // IR(37060, 29)
  "CooperativeVectorOuterProductAccumulateNV\0" // IR(37089, 42)
  "CooperativeVectorReduceSumAccumulateNV\0" // IR(37131, 39)
  "CooperativeVectorMatrixMulAddNV\0" // IR(37170, 32)
  "CooperativeMatrixConvertNV\0" // IR(37202, 27)
  "EmitMeshTasksEXT\0" // IR(37229, 17)
  "SetMeshOutputsEXT\0" // IR(37246, 18)
  "GroupNonUniformPartitionNV\0" // IR(37264, 27)
  "WritePackedPrimitiveIndices4x8NV\0" // IR(37291, 33)
  "FetchMicroTriangleVertexPositionNV\0" // IR(37324, 35)
  "FetchMicroTriangleVertexBarycentricNV\0" // IR(37359, 38)
  "CooperativeVectorLoadNV\0" // IR(37397, 24)
  "CooperativeVectorStoreNV\0" // IR(37421, 25)
  "HitObjectRecordFromQueryEXT\0" // IR(37446, 28)
  "HitObjectRecordMissEXT\0" // IR(37474, 23)
  "HitObjectRecordMissMotionEXT\0" // IR(37497, 29)
  "HitObjectGetIntersectionTriangleVertexPositionsEXT\0" // IR(37526, 51)
  "HitObjectGetRayFlagsEXT\0" // IR(37577, 24)
  "HitObjectSetShaderBindingTableRecordIndexEXT\0" // IR(37601, 45)
  "HitObjectReorderExecuteShaderEXT\0" // IR(37646, 33)
  "HitObjectTraceReorderExecuteEXT\0" // IR(37679, 32)
  "HitObjectTraceMotionReorderExecuteEXT\0" // IR(37711, 38)
  "TypeHitObjectEXT\0" // IR(37749, 17)
  "ReorderThreadWithHintEXT\0" // IR(37766, 25)
  "ReorderThreadWithHitObjectEXT\0" // IR(37791, 30)
  "HitObjectTraceRayEXT\0" // IR(37821, 21)
  "HitObjectTraceRayMotionEXT\0" // IR(37842, 27)
  "HitObjectRecordEmptyEXT\0" // IR(37869, 24)
  "HitObjectExecuteShaderEXT\0" // IR(37893, 26)
  "HitObjectGetCurrentTimeEXT\0" // IR(37919, 27)
  "HitObjectGetAttributesEXT\0" // IR(37946, 26)
  "HitObjectGetHitKindEXT\0" // IR(37972, 23)
  "HitObjectGetPrimitiveIndexEXT\0" // IR(37995, 30)
  "HitObjectGetGeometryIndexEXT\0" // IR(38025, 29)
  "HitObjectGetInstanceIdEXT\0" // IR(38054, 26)
  "HitObjectGetInstanceCustomIndexEXT\0" // IR(38080, 35)
  "HitObjectGetObjectRayOriginEXT\0" // IR(38115, 31)
  "HitObjectGetObjectRayDirectionEXT\0" // IR(38146, 34)
  "HitObjectGetWorldRayDirectionEXT\0" // IR(38180, 33)
  "HitObjectGetWorldRayOriginEXT\0" // IR(38213, 30)
  "HitObjectGetObjectToWorldEXT\0" // IR(38243, 29)
  "HitObjectGetWorldToObjectEXT\0" // IR(38272, 29)
  "HitObjectGetRayTMaxEXT\0" // IR(38301, 23)
  "ReportIntersectionKHR\0" // IR(38324, 22)
  "ReportIntersectionNV\0" // IR(38346, 21)
  "IgnoreIntersectionNV\0" // IR(38367, 21)
  "TerminateRayNV\0" // IR(38388, 15)
  "TraceNV\0" // IR(38403, 8)
  "TraceMotionNV\0" // IR(38411, 14)
  "TraceRayMotionNV\0" // IR(38425, 17)
  "RayQueryGetIntersectionTriangleVertexPositionsKHR\0" // IR(38442, 50)
  "TypeAccelerationStructureKHR\0" // IR(38492, 29)
  "TypeAccelerationStructureNV\0" // IR(38521, 28)
  "ExecuteCallableNV\0" // IR(38549, 18)
  "RayQueryGetIntersectionClusterIdNV\0" // IR(38567, 35)
  "RayQueryGetClusterIdNV\0" // IR(38602, 23)
  "HitObjectGetClusterIdNV\0" // IR(38625, 24)
  "HitObjectGetRayTMinEXT\0" // IR(38649, 23)
  "HitObjectGetShaderBindingTableRecordIndexEXT\0" // IR(38672, 45)
  "HitObjectGetShaderRecordBufferHandleEXT\0" // IR(38717, 40)
  "HitObjectIsEmptyEXT\0" // IR(38757, 20)
  "HitObjectIsHitEXT\0" // IR(38777, 18)
  "HitObjectIsMissEXT\0" // IR(38795, 19)
  "TypeCooperativeMatrixNV\0" // IR(38814, 24)
  "CooperativeMatrixLoadNV\0" // IR(38838, 24)
  "CooperativeMatrixStoreNV\0" // IR(38862, 25)
  "CooperativeMatrixMulAddNV\0" // IR(38887, 26)
  "CooperativeMatrixLengthNV\0" // IR(38913, 26)
  "BeginInvocationInterlockEXT\0" // IR(38939, 28)
  "EndInvocationInterlockEXT\0" // IR(38967, 26)
  "SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE\0" // IR(38993, 43)
  "CooperativeMatrixReduceNV\0" // IR(39036, 26)
  "SPV_OPERAND_TYPE_MEMORY_ACCESS\0" // IR(39062, 31)
  "SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS\0" // IR(39093, 44)
  "CooperativeMatrixLoadTensorNV\0" // IR(39137, 30)
  "CooperativeMatrixStoreTensorNV\0" // IR(39167, 31)
  "CooperativeMatrixPerElementOpNV\0" // IR(39198, 32)
  "TypeTensorLayoutNV\0" // IR(39230, 19)
  "TypeTensorViewNV\0" // IR(39249, 17)
  "CreateTensorLayoutNV\0" // IR(39266, 21)
  "TensorLayoutSetDimensionNV\0" // IR(39287, 27)
  "TensorLayoutSetStrideNV\0" // IR(39314, 24)
  "TensorLayoutSliceNV\0" // IR(39338, 20)
  "TensorLayoutSetClampValueNV\0" // IR(39358, 28)
  "CreateTensorViewNV\0" // IR(39386, 19)
  "TensorViewSetDimensionNV\0" // IR(39405, 25)
  "TensorViewSetStrideNV\0" // IR(39430, 22)
  "IsHelperInvocationEXT\0" // IR(39452, 22)
  "TensorViewSetClipNV\0" // IR(39474, 20)
  "TensorLayoutSetBlockSizeNV\0" // IR(39494, 27)
  "CooperativeMatrixTransposeNV\0" // IR(39521, 29)
  "ConvertUToImageNV\0" // IR(39550, 18)
  "ConvertUToSamplerNV\0" // IR(39568, 20)
  "ConvertImageToUNV\0" // IR(39588, 18)
  "ConvertSamplerToUNV\0" // IR(39606, 20)
  "ConvertUToSampledImageNV\0" // IR(39626, 25)
  "ConvertSampledImageToUNV\0" // IR(39651, 25)
  "SamplerImageAddressingModeNV\0" // IR(39676, 29)
  "SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS\0" // IR(39705, 52)
  "RawAccessChainNV\0" // IR(39757, 17)
  "RayQueryGetIntersectionSpherePositionNV\0" // IR(39774, 40)
  "RayQueryGetIntersectionSphereRadiusNV\0" // IR(39814, 38)
  "RayQueryGetIntersectionLSSPositionsNV\0" // IR(39852, 38)
  "RayQueryGetIntersectionLSSRadiiNV\0" // IR(39890, 34)
  "RayQueryGetIntersectionLSSHitValueNV\0" // IR(39924, 37)
  "HitObjectGetSpherePositionNV\0" // IR(39961, 29)
  "HitObjectGetSphereRadiusNV\0" // IR(39990, 27)
  "HitObjectGetLSSPositionsNV\0" // IR(40017, 27)
  "HitObjectGetLSSRadiiNV\0" // IR(40044, 23)
  "HitObjectIsSphereHitNV\0" // IR(40067, 23)
  "HitObjectIsLSSHitNV\0" // IR(40090, 20)
  "RayQueryIsSphereHitNV\0" // IR(40110, 22)
  "RayQueryIsLSSHitNV\0" // IR(40132, 19)
  "SubgroupShuffleDownINTEL\0" // IR(40151, 25)
  "SubgroupShuffleUpINTEL\0" // IR(40176, 23)
  "SubgroupShuffleXorINTEL\0" // IR(40199, 24)
  "SubgroupBlockReadINTEL\0" // IR(40223, 23)
  "SubgroupBlockWriteINTEL\0" // IR(40246, 24)
  "SubgroupImageBlockReadINTEL\0" // IR(40270, 28)
  "SubgroupImageBlockWriteINTEL\0" // IR(40298, 29)
  "SubgroupImageMediaBlockReadINTEL\0" // IR(40327, 33)
  "SubgroupImageMediaBlockWriteINTEL\0" // IR(40360, 34)
  "UCountLeadingZerosINTEL\0" // IR(40394, 24)
  "UCountTrailingZerosINTEL\0" // IR(40418, 25)
  "AbsISubINTEL\0" // IR(40443, 13)
  "AbsUSubINTEL\0" // IR(40456, 13)
  "IAddSatINTEL\0" // IR(40469, 13)
  "UAddSatINTEL\0" // IR(40482, 13)
  "IAverageINTEL\0" // IR(40495, 14)
  "UAverageINTEL\0" // IR(40509, 14)
  "IAverageRoundedINTEL\0" // IR(40523, 21)
  "UAverageRoundedINTEL\0" // IR(40544, 21)
  "ISubSatINTEL\0" // IR(40565, 13)
  "USubSatINTEL\0" // IR(40578, 13)
  "IMul32x16INTEL\0" // IR(40591, 15)
  "UMul32x16INTEL\0" // IR(40606, 15)
  "ConstantFunctionPointerINTEL\0" // IR(40621, 29)
  "FunctionPointerCallINTEL\0" // IR(40650, 25)
  "AsmTargetINTEL\0" // IR(40675, 15)
  "AsmCallINTEL\0" // IR(40690, 13)
  "AtomicFMinEXT\0" // IR(40703, 14)
  "AtomicFMaxEXT\0" // IR(40717, 14)
  "AssumeTrueKHR\0" // IR(40731, 14)
  "ExpectKHR\0" // IR(40745, 10)
  "DecorateString\0" // IR(40755, 15)
  "DecorateStringGOOGLE\0" // IR(40770, 21)
  "MemberDecorateString\0" // IR(40791, 21)
  "MemberDecorateStringGOOGLE\0" // IR(40812, 27)
  "VmeImageINTEL\0" // IR(40839, 14)
  "TypeVmeImageINTEL\0" // IR(40853, 18)
  "TypeAvcImePayloadINTEL\0" // IR(40871, 23)
  "TypeAvcRefPayloadINTEL\0" // IR(40894, 23)
  "TypeAvcSicPayloadINTEL\0" // IR(40917, 23)
  "TypeAvcMcePayloadINTEL\0" // IR(40940, 23)
  "TypeAvcMceResultINTEL\0" // IR(40963, 22)
  "TypeAvcImeResultINTEL\0" // IR(40985, 22)
  "TypeAvcImeResultSingleReferenceStreamoutINTEL\0" // IR(41007, 46)
  "TypeAvcImeResultDualReferenceStreamoutINTEL\0" // IR(41053, 44)
  "TypeAvcImeSingleReferenceStreaminINTEL\0" // IR(41097, 39)
  "TypeAvcImeDualReferenceStreaminINTEL\0" // IR(41136, 37)
  "TypeAvcRefResultINTEL\0" // IR(41173, 22)
  "TypeAvcSicResultINTEL\0" // IR(41195, 22)
  "SubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL\0" // IR(41217, 60)
  "SubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL\0" // IR(41277, 53)
  "SubgroupAvcMceGetDefaultInterShapePenaltyINTEL\0" // IR(41330, 47)
  "SubgroupAvcMceSetInterShapePenaltyINTEL\0" // IR(41377, 40)
  "SubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL\0" // IR(41417, 51)
  "SubgroupAvcMceSetInterDirectionPenaltyINTEL\0" // IR(41468, 44)
  "SubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL\0" // IR(41512, 51)
  "SubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL\0" // IR(41563, 56)
  "SubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL\0" // IR(41619, 50)
  "SubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL\0" // IR(41669, 52)
  "SubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL\0" // IR(41721, 49)
  "SubgroupAvcMceSetMotionVectorCostFunctionINTEL\0" // IR(41770, 47)
  "SubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL\0" // IR(41817, 50)
  "SubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL\0" // IR(41867, 51)
  "SubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL\0" // IR(41918, 56)
  "SubgroupAvcMceSetAcOnlyHaarINTEL\0" // IR(41974, 33)
  "SubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL\0" // IR(42007, 52)
  "SubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL\0" // IR(42059, 61)
  "SubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL\0" // IR(42120, 61)
  "SubgroupAvcMceConvertToImePayloadINTEL\0" // IR(42181, 39)
  "SubgroupAvcMceConvertToImeResultINTEL\0" // IR(42220, 38)
  "SubgroupAvcMceConvertToRefPayloadINTEL\0" // IR(42258, 39)
  "SubgroupAvcMceConvertToRefResultINTEL\0" // IR(42297, 38)
  "SubgroupAvcMceConvertToSicPayloadINTEL\0" // IR(42335, 39)
  "SubgroupAvcMceConvertToSicResultINTEL\0" // IR(42374, 38)
  "SubgroupAvcMceGetMotionVectorsINTEL\0" // IR(42412, 36)
  "SubgroupAvcMceGetInterDistortionsINTEL\0" // IR(42448, 39)
  "SubgroupAvcMceGetBestInterDistortionsINTEL\0" // IR(42487, 43)
  "SubgroupAvcMceGetInterMajorShapeINTEL\0" // IR(42530, 38)
  "SubgroupAvcMceGetInterMinorShapeINTEL\0" // IR(42568, 38)
  "SubgroupAvcMceGetInterDirectionsINTEL\0" // IR(42606, 38)
  "SubgroupAvcMceGetInterMotionVectorCountINTEL\0" // IR(42644, 45)
  "SubgroupAvcMceGetInterReferenceIdsINTEL\0" // IR(42689, 40)
  "SubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL\0" // IR(42729, 62)
  "SubgroupAvcImeInitializeINTEL\0" // IR(42791, 30)
  "SubgroupAvcImeSetSingleReferenceINTEL\0" // IR(42821, 38)
  "SubgroupAvcImeSetDualReferenceINTEL\0" // IR(42859, 36)
  "SubgroupAvcImeRefWindowSizeINTEL\0" // IR(42895, 33)
  "SubgroupAvcImeAdjustRefOffsetINTEL\0" // IR(42928, 35)
  "SubgroupAvcImeConvertToMcePayloadINTEL\0" // IR(42963, 39)
  "SubgroupAvcImeSetMaxMotionVectorCountINTEL\0" // IR(43002, 43)
  "SubgroupAvcImeSetUnidirectionalMixDisableINTEL\0" // IR(43045, 47)
  "SubgroupAvcImeSetEarlySearchTerminationThresholdINTEL\0" // IR(43092, 54)
  "SubgroupAvcImeSetWeightedSadINTEL\0" // IR(43146, 34)
  "SubgroupAvcImeEvaluateWithSingleReferenceINTEL\0" // IR(43180, 47)
  "SubgroupAvcImeEvaluateWithDualReferenceINTEL\0" // IR(43227, 45)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL\0" // IR(43272, 55)
  "SubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL\0" // IR(43327, 53)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL\0" // IR(43380, 56)
  "SubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL\0" // IR(43436, 54)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL\0" // IR(43490, 58)
  "SubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL\0" // IR(43548, 56)
  "SubgroupAvcImeConvertToMceResultINTEL\0" // IR(43604, 38)
  "SubgroupAvcImeGetSingleReferenceStreaminINTEL\0" // IR(43642, 46)
  "SubgroupAvcImeGetDualReferenceStreaminINTEL\0" // IR(43688, 44)
  "SubgroupAvcImeStripSingleReferenceStreamoutINTEL\0" // IR(43732, 49)
  "SubgroupAvcImeStripDualReferenceStreamoutINTEL\0" // IR(43781, 47)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL\0" // IR(43828, 70)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL\0" // IR(43898, 68)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL\0" // IR(43966, 69)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL\0" // IR(44035, 68)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL\0" // IR(44103, 66)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL\0" // IR(44169, 67)
  "SubgroupAvcImeGetBorderReachedINTEL\0" // IR(44236, 36)
  "SubgroupAvcImeGetTruncatedSearchIndicationINTEL\0" // IR(44272, 48)
  "SubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL\0" // IR(44320, 59)
  "SubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL\0" // IR(44379, 58)
  "SubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL\0" // IR(44437, 56)
  "SubgroupAvcFmeInitializeINTEL\0" // IR(44493, 30)
  "SubgroupAvcBmeInitializeINTEL\0" // IR(44523, 30)
  "SubgroupAvcRefConvertToMcePayloadINTEL\0" // IR(44553, 39)
  "SubgroupAvcRefSetBidirectionalMixDisableINTEL\0" // IR(44592, 46)
  "SubgroupAvcRefSetBilinearFilterEnableINTEL\0" // IR(44638, 43)
  "SubgroupAvcRefEvaluateWithSingleReferenceINTEL\0" // IR(44681, 47)
  "SubgroupAvcRefEvaluateWithDualReferenceINTEL\0" // IR(44728, 45)
  "SubgroupAvcRefEvaluateWithMultiReferenceINTEL\0" // IR(44773, 46)
  "SubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL\0" // IR(44819, 56)
  "SubgroupAvcRefConvertToMceResultINTEL\0" // IR(44875, 38)
  "SubgroupAvcSicInitializeINTEL\0" // IR(44913, 30)
  "SubgroupAvcSicConfigureSkcINTEL\0" // IR(44943, 32)
  "SubgroupAvcSicConfigureIpeLumaINTEL\0" // IR(44975, 36)
  "SubgroupAvcSicConfigureIpeLumaChromaINTEL\0" // IR(45011, 42)
  "SubgroupAvcSicGetMotionVectorMaskINTEL\0" // IR(45053, 39)
  "SubgroupAvcSicConvertToMcePayloadINTEL\0" // IR(45092, 39)
  "SubgroupAvcSicSetIntraLumaShapePenaltyINTEL\0" // IR(45131, 44)
  "SubgroupAvcSicSetIntraLumaModeCostFunctionINTEL\0" // IR(45175, 48)
  "SubgroupAvcSicSetIntraChromaModeCostFunctionINTEL\0" // IR(45223, 50)
  "SubgroupAvcSicSetBilinearFilterEnableINTEL\0" // IR(45273, 43)
  "SubgroupAvcSicSetSkcForwardTransformEnableINTEL\0" // IR(45316, 48)
  "SubgroupAvcSicSetBlockBasedRawSkipSadINTEL\0" // IR(45364, 43)
  "SubgroupAvcSicEvaluateIpeINTEL\0" // IR(45407, 31)
  "SubgroupAvcSicEvaluateWithSingleReferenceINTEL\0" // IR(45438, 47)
  "SubgroupAvcSicEvaluateWithDualReferenceINTEL\0" // IR(45485, 45)
  "SubgroupAvcSicEvaluateWithMultiReferenceINTEL\0" // IR(45530, 46)
  "SubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL\0" // IR(45576, 56)
  "SubgroupAvcSicConvertToMceResultINTEL\0" // IR(45632, 38)
  "SubgroupAvcSicGetIpeLumaShapeINTEL\0" // IR(45670, 35)
  "SubgroupAvcSicGetBestIpeLumaDistortionINTEL\0" // IR(45705, 44)
  "SubgroupAvcSicGetBestIpeChromaDistortionINTEL\0" // IR(45749, 46)
  "SubgroupAvcSicGetPackedIpeLumaModesINTEL\0" // IR(45795, 41)
  "SubgroupAvcSicGetIpeChromaModeINTEL\0" // IR(45836, 36)
  "SubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL\0" // IR(45872, 50)
  "SubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL\0" // IR(45922, 48)
  "SubgroupAvcSicGetInterRawSadsINTEL\0" // IR(45970, 35)
  "SaveMemoryINTEL\0" // IR(46005, 16)
  "RestoreMemoryINTEL\0" // IR(46021, 19)
  "ArbitraryFloatSinCosPiALTERA\0" // IR(46040, 29)
  "ArbitraryFloatSinCosPiINTEL\0" // IR(46069, 28)
  "ArbitraryFloatCastALTERA\0" // IR(46097, 25)
  "ArbitraryFloatCastINTEL\0" // IR(46122, 24)
  "ArbitraryFloatCastFromIntALTERA\0" // IR(46146, 32)
  "ArbitraryFloatCastFromIntINTEL\0" // IR(46178, 31)
  "ArbitraryFloatCastToIntALTERA\0" // IR(46209, 30)
  "ArbitraryFloatCastToIntINTEL\0" // IR(46239, 29)
  "ArbitraryFloatAddALTERA\0" // IR(46268, 24)
  "ArbitraryFloatAddINTEL\0" // IR(46292, 23)
  "ArbitraryFloatSubALTERA\0" // IR(46315, 24)
  "ArbitraryFloatSubINTEL\0" // IR(46339, 23)
  "ArbitraryFloatMulALTERA\0" // IR(46362, 24)
  "ArbitraryFloatMulINTEL\0" // IR(46386, 23)
  "ArbitraryFloatDivALTERA\0" // IR(46409, 24)
  "ArbitraryFloatDivINTEL\0" // IR(46433, 23)
  "ArbitraryFloatGTALTERA\0" // IR(46456, 23)
  "ArbitraryFloatGTINTEL\0" // IR(46479, 22)
  "ArbitraryFloatGEALTERA\0" // IR(46501, 23)
  "ArbitraryFloatGEINTEL\0" // IR(46524, 22)
  "ArbitraryFloatLTALTERA\0" // IR(46546, 23)
  "ArbitraryFloatLTINTEL\0" // IR(46569, 22)
  "ArbitraryFloatLEALTERA\0" // IR(46591, 23)
  "ArbitraryFloatLEINTEL\0" // IR(46614, 22)
  "ArbitraryFloatEQALTERA\0" // IR(46636, 23)
  "ArbitraryFloatEQINTEL\0" // IR(46659, 22)
  "ArbitraryFloatRecipALTERA\0" // IR(46681, 26)
  "ArbitraryFloatRecipINTEL\0" // IR(46707, 25)
  "ArbitraryFloatRSqrtALTERA\0" // IR(46732, 26)
  "ArbitraryFloatRSqrtINTEL\0" // IR(46758, 25)
  "ArbitraryFloatCbrtALTERA\0" // IR(46783, 25)
  "ArbitraryFloatCbrtINTEL\0" // IR(46808, 24)
  "ArbitraryFloatHypotALTERA\0" // IR(46832, 26)
  "ArbitraryFloatHypotINTEL\0" // IR(46858, 25)
  "ArbitraryFloatSqrtALTERA\0" // IR(46883, 25)
  "ArbitraryFloatSqrtINTEL\0" // IR(46908, 24)
  "ArbitraryFloatLogINTEL\0" // IR(46932, 23)
  "ArbitraryFloatLog2INTEL\0" // IR(46955, 24)
  "ArbitraryFloatLog10INTEL\0" // IR(46979, 25)
  "ArbitraryFloatLog1pINTEL\0" // IR(47004, 25)
  "ArbitraryFloatExpINTEL\0" // IR(47029, 23)
  "ArbitraryFloatExp2INTEL\0" // IR(47052, 24)
  "ArbitraryFloatExp10INTEL\0" // IR(47076, 25)
  "ArbitraryFloatExpm1INTEL\0" // IR(47101, 25)
  "ArbitraryFloatSinINTEL\0" // IR(47126, 23)
  "ArbitraryFloatCosINTEL\0" // IR(47149, 23)
  "ArbitraryFloatSinCosINTEL\0" // IR(47172, 26)
  "ArbitraryFloatSinPiINTEL\0" // IR(47198, 25)
  "ArbitraryFloatCosPiINTEL\0" // IR(47223, 25)
  "ArbitraryFloatASinINTEL\0" // IR(47248, 24)
  "ArbitraryFloatASinPiINTEL\0" // IR(47272, 26)
  "ArbitraryFloatACosINTEL\0" // IR(47298, 24)
  "ArbitraryFloatACosPiINTEL\0" // IR(47322, 26)
  "ArbitraryFloatATanINTEL\0" // IR(47348, 24)
  "ArbitraryFloatATanPiINTEL\0" // IR(47372, 26)
  "ArbitraryFloatATan2INTEL\0" // IR(47398, 25)
  "ArbitraryFloatPowINTEL\0" // IR(47423, 23)
  "ArbitraryFloatPowRINTEL\0" // IR(47446, 24)
  "ArbitraryFloatPowNINTEL\0" // IR(47470, 24)
  "LoopControlINTEL\0" // IR(47494, 17)
  "AliasDomainDeclINTEL\0" // IR(47511, 21)
  "AliasScopeDeclINTEL\0" // IR(47532, 20)
  "AliasScopeListDeclINTEL\0" // IR(47552, 24)
  "FixedSqrtALTERA\0" // IR(47576, 16)
  "FixedSqrtINTEL\0" // IR(47592, 15)
  "FixedRecipALTERA\0" // IR(47607, 17)
  "FixedRecipINTEL\0" // IR(47624, 16)
  "FixedRsqrtALTERA\0" // IR(47640, 17)
  "FixedRsqrtINTEL\0" // IR(47657, 16)
  "FixedSinALTERA\0" // IR(47673, 15)
  "FixedSinINTEL\0" // IR(47688, 14)
  "FixedCosALTERA\0" // IR(47702, 15)
  "FixedCosINTEL\0" // IR(47717, 14)
  "FixedSinCosALTERA\0" // IR(47731, 18)
  "FixedSinCosINTEL\0" // IR(47749, 17)
  "FixedSinPiALTERA\0" // IR(47766, 17)
  "FixedSinPiINTEL\0" // IR(47783, 16)
  "FixedCosPiALTERA\0" // IR(47799, 17)
  "FixedCosPiINTEL\0" // IR(47816, 16)
  "FixedSinCosPiALTERA\0" // IR(47832, 20)
  "FixedSinCosPiINTEL\0" // IR(47852, 19)
  "FixedLogALTERA\0" // IR(47871, 15)
  "FixedLogINTEL\0" // IR(47886, 14)
  "FixedExpALTERA\0" // IR(47900, 15)
  "FixedExpINTEL\0" // IR(47915, 14)
  "PtrCastToCrossWorkgroupALTERA\0" // IR(47929, 30)
  "PtrCastToCrossWorkgroupINTEL\0" // IR(47959, 29)
  "CrossWorkgroupCastToPtrALTERA\0" // IR(47988, 30)
  "CrossWorkgroupCastToPtrINTEL\0" // IR(48018, 29)
  "ReadPipeBlockingALTERA\0" // IR(48047, 23)
  "ReadPipeBlockingINTEL\0" // IR(48070, 22)
  "WritePipeBlockingALTERA\0" // IR(48092, 24)
  "WritePipeBlockingINTEL\0" // IR(48116, 23)
  "RayQueryGetRayTMinKHR\0" // IR(48139, 22)
  "RayQueryGetRayFlagsKHR\0" // IR(48161, 23)
  "RayQueryGetIntersectionTKHR\0" // IR(48184, 28)
  "RayQueryGetIntersectionInstanceCustomIndexKHR\0" // IR(48212, 46)
  "RayQueryGetIntersectionInstanceIdKHR\0" // IR(48258, 37)
  "RayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR\0" // IR(48295, 65)
  "RayQueryGetIntersectionGeometryIndexKHR\0" // IR(48360, 40)
  "RayQueryGetIntersectionPrimitiveIndexKHR\0" // IR(48400, 41)
  "RayQueryGetIntersectionBarycentricsKHR\0" // IR(48441, 39)
  "RayQueryGetIntersectionFrontFaceKHR\0" // IR(48480, 36)
  "RayQueryGetIntersectionCandidateAABBOpaqueKHR\0" // IR(48516, 46)
  "RayQueryGetIntersectionObjectRayDirectionKHR\0" // IR(48562, 45)
  "RayQueryGetIntersectionObjectRayOriginKHR\0" // IR(48607, 42)
  "RayQueryGetWorldRayDirectionKHR\0" // IR(48649, 32)
  "RayQueryGetWorldRayOriginKHR\0" // IR(48681, 29)
  "RayQueryGetIntersectionObjectToWorldKHR\0" // IR(48710, 40)
  "RayQueryGetIntersectionWorldToObjectKHR\0" // IR(48750, 40)
  "AtomicFAddEXT\0" // IR(48790, 14)
  "TypeBufferSurfaceINTEL\0" // IR(48804, 23)
  "TypeStructContinuedINTEL\0" // IR(48827, 25)
  "ConstantCompositeContinuedINTEL\0" // IR(48852, 32)
  "SpecConstantCompositeContinuedINTEL\0" // IR(48884, 36)
  "CompositeConstructContinuedINTEL\0" // IR(48920, 33)
  "ConvertFToBF16INTEL\0" // IR(48953, 20)
  "ConvertBF16ToFINTEL\0" // IR(48973, 20)
  "ControlBarrierArriveINTEL\0" // IR(48993, 26)
  "ControlBarrierWaitINTEL\0" // IR(49019, 24)
  "TaskSequenceCreateALTERA\0" // IR(49043, 25)
  "TaskSequenceCreateINTEL\0" // IR(49068, 24)
  "TaskSequenceAsyncALTERA\0" // IR(49092, 24)
  "TaskSequenceAsyncINTEL\0" // IR(49116, 23)
  "TaskSequenceGetALTERA\0" // IR(49139, 22)
  "TaskSequenceGetINTEL\0" // IR(49161, 21)
  "TaskSequenceReleaseALTERA\0" // IR(49182, 26)
  "TaskSequenceReleaseINTEL\0" // IR(49208, 25)
  "TypeTaskSequenceALTERA\0" // IR(49233, 23)
  "TypeTaskSequenceINTEL\0" // IR(49256, 22)
  "SubgroupBlockPrefetchINTEL\0" // IR(49278, 27)
  "Subgroup2DBlockLoadINTEL\0" // IR(49305, 25)
  "Subgroup2DBlockLoadTransformINTEL\0" // IR(49330, 34)
  "Subgroup2DBlockLoadTransposeINTEL\0" // IR(49364, 34)
  "Subgroup2DBlockPrefetchINTEL\0" // IR(49398, 29)
  "Subgroup2DBlockStoreINTEL\0" // IR(49427, 26)
  "SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS\0" // IR(49453, 62)
  "BitwiseFunctionINTEL\0" // IR(49515, 21)
  "ConditionalExtensionINTEL\0" // IR(49536, 26)
  "ConditionalEntryPointINTEL\0" // IR(49562, 27)
  "ConditionalCapabilityINTEL\0" // IR(49589, 27)
  "SpecConstantTargetINTEL\0" // IR(49616, 24)
  "SpecConstantArchitectureINTEL\0" // IR(49640, 30)
  "SPV_OPERAND_TYPE_VARIABLE_CAPABILITY\0" // IR(49670, 37)
  "SpecConstantCapabilitiesINTEL\0" // IR(49707, 30)
  "ConditionalCopyObjectINTEL\0" // IR(49737, 27)
  "GroupIMulKHR\0" // IR(49764, 13)
  "GroupFMulKHR\0" // IR(49777, 13)
  "GroupBitwiseAndKHR\0" // IR(49790, 19)
  "GroupBitwiseOrKHR\0" // IR(49809, 18)
  "GroupBitwiseXorKHR\0" // IR(49827, 19)
  "GroupLogicalAndKHR\0" // IR(49846, 19)
  "GroupLogicalOrKHR\0" // IR(49865, 18)
  "GroupLogicalXorKHR\0" // IR(49883, 19)
  "RoundFToTF32INTEL\0" // IR(49902, 18)
  "MaskedGatherINTEL\0" // IR(49920, 18)
  "MaskedScatterINTEL\0" // IR(49938, 19)
  "ConvertHandleToImageINTEL\0" // IR(49957, 26)
  "ConvertHandleToSamplerINTEL\0" // IR(49983, 28)
  "ConvertHandleToSampledImageINTEL\0" // IR(50011, 33)
  "DebugInfoNone\0" // IR(50044, 14)
  "DebugCompilationUnit\0" // IR(50058, 21)
  "SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING\0" // IR(50079, 52)
  "DebugTypeBasic\0" // IR(50131, 15)
  "SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS\0" // IR(50146, 34)
  "DebugTypePointer\0" // IR(50180, 17)
  "SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER\0" // IR(50197, 38)
  "DebugTypeQualifier\0" // IR(50235, 19)
  "DebugTypeArray\0" // IR(50254, 15)
  "DebugTypeVector\0" // IR(50269, 16)
  "DebugTypedef\0" // IR(50285, 13)
  "DebugTypeFunction\0" // IR(50298, 18)
  "DebugTypeEnum\0" // IR(50316, 14)
  "SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE\0" // IR(50330, 38)
  "DebugTypeComposite\0" // IR(50368, 19)
  "DebugTypeMember\0" // IR(50387, 16)
  "DebugTypeInheritance\0" // IR(50403, 21)
  "DebugTypePtrToMember\0" // IR(50424, 21)
  "DebugTypeTemplate\0" // IR(50445, 18)
  "DebugTypeTemplateParameter\0" // IR(50463, 27)
  "DebugTypeTemplateTemplateParameter\0" // IR(50490, 35)
  "DebugTypeTemplateParameterPack\0" // IR(50525, 31)
  "DebugGlobalVariable\0" // IR(50556, 20)
  "DebugFunctionDeclaration\0" // IR(50576, 25)
  "DebugFunction\0" // IR(50601, 14)
  "DebugLexicalBlock\0" // IR(50615, 18)
  "DebugLexicalBlockDiscriminator\0" // IR(50633, 31)
  "DebugScope\0" // IR(50664, 11)
  "DebugNoScope\0" // IR(50675, 13)
  "DebugInlinedAt\0" // IR(50688, 15)
  "SPV_OPERAND_TYPE_OPTIONAL_LITERAL_INTEGER\0" // IR(50703, 42)
  "DebugLocalVariable\0" // IR(50745, 19)
  "DebugInlinedVariable\0" // IR(50764, 21)
  "DebugDeclare\0" // IR(50785, 13)
  "DebugValue\0" // IR(50798, 11)
  "SPV_OPERAND_TYPE_DEBUG_OPERATION\0" // IR(50809, 33)
  "DebugOperation\0" // IR(50842, 15)
  "DebugExpression\0" // IR(50857, 16)
  "DebugMacroDef\0" // IR(50873, 14)
  "DebugMacroUndef\0" // IR(50887, 16)
  "Round\0" // IR(50903, 6)
  "RoundEven\0" // IR(50909, 10)
  "Trunc\0" // IR(50919, 6)
  "FAbs\0" // IR(50925, 5)
  "SAbs\0" // IR(50930, 5)
  "FSign\0" // IR(50935, 6)
  "SSign\0" // IR(50941, 6)
  "Floor\0" // IR(50947, 6)
  "Ceil\0" // IR(50953, 5)
  "Fract\0" // IR(50958, 6)
  "Radians\0" // IR(50964, 8)
  "Degrees\0" // IR(50972, 8)
  "Sin\0" // IR(50980, 4)
  "Cos\0" // IR(50984, 4)
  "Tan\0" // IR(50988, 4)
  "Asin\0" // IR(50992, 5)
  "Acos\0" // IR(50997, 5)
  "Atan\0" // IR(51002, 5)
  "Sinh\0" // IR(51007, 5)
  "Cosh\0" // IR(51012, 5)
  "Tanh\0" // IR(51017, 5)
  "Asinh\0" // IR(51022, 6)
  "Acosh\0" // IR(51028, 6)
  "Atanh\0" // IR(51034, 6)
  "Atan2\0" // IR(51040, 6)
  "Pow\0" // IR(51046, 4)
  "Exp\0" // IR(51050, 4)
  "Log\0" // IR(51054, 4)
  "Exp2\0" // IR(51058, 5)
  "Log2\0" // IR(51063, 5)
  "Sqrt\0" // IR(51068, 5)
  "InverseSqrt\0" // IR(51073, 12)
  "Determinant\0" // IR(51085, 12)
  "MatrixInverse\0" // IR(51097, 14)
  "Modf\0" // IR(51111, 5)
  "ModfStruct\0" // IR(51116, 11)
  "FMin\0" // IR(51127, 5)
  "UMin\0" // IR(51132, 5)
  "SMin\0" // IR(51137, 5)
  "FMax\0" // IR(51142, 5)
  "UMax\0" // IR(51147, 5)
  "SMax\0" // IR(51152, 5)
  "FClamp\0" // IR(51157, 7)
  "UClamp\0" // IR(51164, 7)
  "SClamp\0" // IR(51171, 7)
  "FMix\0" // IR(51178, 5)
  "IMix\0" // IR(51183, 5)
  "Step\0" // IR(51188, 5)
  "SmoothStep\0" // IR(51193, 11)
  "Fma\0" // IR(51204, 4)
  "Frexp\0" // IR(51208, 6)
  "FrexpStruct\0" // IR(51214, 12)
  "Ldexp\0" // IR(51226, 6)
  "PackSnorm4x8\0" // IR(51232, 13)
  "PackUnorm4x8\0" // IR(51245, 13)
  "PackSnorm2x16\0" // IR(51258, 14)
  "PackUnorm2x16\0" // IR(51272, 14)
  "PackHalf2x16\0" // IR(51286, 13)
  "PackDouble2x32\0" // IR(51299, 15)
  "UnpackSnorm2x16\0" // IR(51314, 16)
  "UnpackUnorm2x16\0" // IR(51330, 16)
  "UnpackHalf2x16\0" // IR(51346, 15)
  "UnpackSnorm4x8\0" // IR(51361, 15)
  "UnpackUnorm4x8\0" // IR(51376, 15)
  "UnpackDouble2x32\0" // IR(51391, 17)
  "Length\0" // IR(51408, 7)
  "Distance\0" // IR(51415, 9)
  "Cross\0" // IR(51424, 6)
  "Normalize\0" // IR(51430, 10)
  "FaceForward\0" // IR(51440, 12)
  "Reflect\0" // IR(51452, 8)
  "Refract\0" // IR(51460, 8)
  "FindILsb\0" // IR(51468, 9)
  "FindSMsb\0" // IR(51477, 9)
  "FindUMsb\0" // IR(51486, 9)
  "InterpolateAtCentroid\0" // IR(51495, 22)
  "InterpolateAtSample\0" // IR(51517, 20)
  "InterpolateAtOffset\0" // IR(51537, 20)
  "NMin\0" // IR(51557, 5)
  "NMax\0" // IR(51562, 5)
  "NClamp\0" // IR(51567, 7)
  "ArgumentInfo\0" // IR(51574, 13)
  "ArgumentStorageBuffer\0" // IR(51587, 22)
  "ArgumentUniform\0" // IR(51609, 16)
  "ArgumentPodStorageBuffer\0" // IR(51625, 25)
  "ArgumentPodUniform\0" // IR(51650, 19)
  "ArgumentPodPushConstant\0" // IR(51669, 24)
  "ArgumentSampledImage\0" // IR(51693, 21)
  "ArgumentStorageImage\0" // IR(51714, 21)
  "ArgumentSampler\0" // IR(51735, 16)
  "ArgumentWorkgroup\0" // IR(51751, 18)
  "SpecConstantWorkgroupSize\0" // IR(51769, 26)
  "SpecConstantGlobalOffset\0" // IR(51795, 25)
  "SpecConstantWorkDim\0" // IR(51820, 20)
  "PushConstantGlobalOffset\0" // IR(51840, 25)
  "PushConstantEnqueuedLocalSize\0" // IR(51865, 30)
  "PushConstantGlobalSize\0" // IR(51895, 23)
  "PushConstantRegionOffset\0" // IR(51918, 25)
  "PushConstantNumWorkgroups\0" // IR(51943, 26)
  "PushConstantRegionGroupOffset\0" // IR(51969, 30)
  "ConstantDataStorageBuffer\0" // IR(51999, 26)
  "ConstantDataUniform\0" // IR(52025, 20)
  "PropertyRequiredWorkgroupSize\0" // IR(52045, 30)
  "SpecConstantSubgroupMaxSize\0" // IR(52075, 28)
  "ArgumentPointerPushConstant\0" // IR(52103, 28)
  "ArgumentPointerUniform\0" // IR(52131, 23)
  "ProgramScopeVariablesStorageBuffer\0" // IR(52154, 35)
  "ProgramScopeVariablePointerRelocation\0" // IR(52189, 38)
  "ImageArgumentInfoChannelOrderPushConstant\0" // IR(52227, 42)
  "ImageArgumentInfoChannelDataTypePushConstant\0" // IR(52269, 45)
  "ImageArgumentInfoChannelOrderUniform\0" // IR(52314, 37)
  "ImageArgumentInfoChannelDataTypeUniform\0" // IR(52351, 40)
  "ArgumentStorageTexelBuffer\0" // IR(52391, 27)
  "ArgumentUniformTexelBuffer\0" // IR(52418, 27)
  "ConstantDataPointerPushConstant\0" // IR(52445, 32)
  "ProgramScopeVariablePointerPushConstant\0" // IR(52477, 40)
  "PrintfInfo\0" // IR(52517, 11)
  "PrintfBufferStorageBuffer\0" // IR(52528, 26)
  "PrintfBufferPointerPushConstant\0" // IR(52554, 32)
  "NormalizedSamplerMaskPushConstant\0" // IR(52586, 34)
  "WorkgroupVariableSize\0" // IR(52620, 22)
  "DebugImportedEntity\0" // IR(52642, 20)
  "DebugSource\0" // IR(52662, 12)
  "DebugFunctionDefinition\0" // IR(52674, 24)
  "DebugSourceContinued\0" // IR(52698, 21)
  "DebugLine\0" // IR(52719, 10)
  "DebugNoLine\0" // IR(52729, 12)
  "DebugBuildIdentifier\0" // IR(52741, 21)
  "DebugStoragePath\0" // IR(52762, 17)
  "DebugEntryPoint\0" // IR(52779, 16)
  "DebugTypeMatrix\0" // IR(52795, 16)
  "Configuration\0" // IR(52811, 14)
  "StartCounter\0" // IR(52825, 13)
  "StopCounter\0" // IR(52838, 12)
  "PushConstants\0" // IR(52850, 14)
  "SpecializationMapEntry\0" // IR(52864, 23)
  "DescriptorSetBuffer\0" // IR(52887, 20)
  "DescriptorSetImage\0" // IR(52907, 19)
  "DescriptorSetSampler\0" // IR(52926, 21)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING\0" // IR(52947, 63)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS\0" // IR(53010, 45)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER\0" // IR(53055, 49)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE\0" // IR(53104, 49)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION\0" // IR(53153, 44)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY\0" // IR(53197, 50)
  "DebugModuleINTEL\0" // IR(53247, 17)
  "acos\0" // IR(53264, 5)
  "acosh\0" // IR(53269, 6)
  "acospi\0" // IR(53275, 7)
  "asin\0" // IR(53282, 5)
  "asinh\0" // IR(53287, 6)
  "asinpi\0" // IR(53293, 7)
  "atan\0" // IR(53300, 5)
  "atan2\0" // IR(53305, 6)
  "atanh\0" // IR(53311, 6)
  "atanpi\0" // IR(53317, 7)
  "atan2pi\0" // IR(53324, 8)
  "cbrt\0" // IR(53332, 5)
  "ceil\0" // IR(53337, 5)
  "copysign\0" // IR(53342, 9)
  "cos\0" // IR(53351, 4)
  "cosh\0" // IR(53355, 5)
  "cospi\0" // IR(53360, 6)
  "erfc\0" // IR(53366, 5)
  "erf\0" // IR(53371, 4)
  "exp\0" // IR(53375, 4)
  "exp2\0" // IR(53379, 5)
  "exp10\0" // IR(53384, 6)
  "expm1\0" // IR(53390, 6)
  "fabs\0" // IR(53396, 5)
  "fdim\0" // IR(53401, 5)
  "floor\0" // IR(53406, 6)
  "fma\0" // IR(53412, 4)
  "fmax\0" // IR(53416, 5)
  "fmin\0" // IR(53421, 5)
  "fmod\0" // IR(53426, 5)
  "fract\0" // IR(53431, 6)
  "frexp\0" // IR(53437, 6)
  "hypot\0" // IR(53443, 6)
  "ilogb\0" // IR(53449, 6)
  "ldexp\0" // IR(53455, 6)
  "lgamma\0" // IR(53461, 7)
  "lgamma_r\0" // IR(53468, 9)
  "log\0" // IR(53477, 4)
  "log2\0" // IR(53481, 5)
  "log10\0" // IR(53486, 6)
  "log1p\0" // IR(53492, 6)
  "logb\0" // IR(53498, 5)
  "mad\0" // IR(53503, 4)
  "maxmag\0" // IR(53507, 7)
  "minmag\0" // IR(53514, 7)
  "modf\0" // IR(53521, 5)
  "nan\0" // IR(53526, 4)
  "nextafter\0" // IR(53530, 10)
  "pow\0" // IR(53540, 4)
  "pown\0" // IR(53544, 5)
  "powr\0" // IR(53549, 5)
  "remainder\0" // IR(53554, 10)
  "remquo\0" // IR(53564, 7)
  "rint\0" // IR(53571, 5)
  "rootn\0" // IR(53576, 6)
  "round\0" // IR(53582, 6)
  "rsqrt\0" // IR(53588, 6)
  "sin\0" // IR(53594, 4)
  "sincos\0" // IR(53598, 7)
  "sinh\0" // IR(53605, 5)
  "sinpi\0" // IR(53610, 6)
  "sqrt\0" // IR(53616, 5)
  "tan\0" // IR(53621, 4)
  "tanh\0" // IR(53625, 5)
  "tanpi\0" // IR(53630, 6)
  "tgamma\0" // IR(53636, 7)
  "trunc\0" // IR(53643, 6)
  "half_cos\0" // IR(53649, 9)
  "half_divide\0" // IR(53658, 12)
  "half_exp\0" // IR(53670, 9)
  "half_exp2\0" // IR(53679, 10)
  "half_exp10\0" // IR(53689, 11)
  "half_log\0" // IR(53700, 9)
  "half_log2\0" // IR(53709, 10)
  "half_log10\0" // IR(53719, 11)
  "half_powr\0" // IR(53730, 10)
  "half_recip\0" // IR(53740, 11)
  "half_rsqrt\0" // IR(53751, 11)
  "half_sin\0" // IR(53762, 9)
  "half_sqrt\0" // IR(53771, 10)
  "half_tan\0" // IR(53781, 9)
  "native_cos\0" // IR(53790, 11)
  "native_divide\0" // IR(53801, 14)
  "native_exp\0" // IR(53815, 11)
  "native_exp2\0" // IR(53826, 12)
  "native_exp10\0" // IR(53838, 13)
  "native_log\0" // IR(53851, 11)
  "native_log2\0" // IR(53862, 12)
  "native_log10\0" // IR(53874, 13)
  "native_powr\0" // IR(53887, 12)
  "native_recip\0" // IR(53899, 13)
  "native_rsqrt\0" // IR(53912, 13)
  "native_sin\0" // IR(53925, 11)
  "native_sqrt\0" // IR(53936, 12)
  "native_tan\0" // IR(53948, 11)
  "fclamp\0" // IR(53959, 7)
  "degrees\0" // IR(53966, 8)
  "fmax_common\0" // IR(53974, 12)
  "fmin_common\0" // IR(53986, 12)
  "mix\0" // IR(53998, 4)
  "radians\0" // IR(54002, 8)
  "step\0" // IR(54010, 5)
  "smoothstep\0" // IR(54015, 11)
  "sign\0" // IR(54026, 5)
  "cross\0" // IR(54031, 6)
  "distance\0" // IR(54037, 9)
  "length\0" // IR(54046, 7)
  "normalize\0" // IR(54053, 10)
  "fast_distance\0" // IR(54063, 14)
  "fast_length\0" // IR(54077, 12)
  "fast_normalize\0" // IR(54089, 15)
  "s_abs\0" // IR(54104, 6)
  "s_abs_diff\0" // IR(54110, 11)
  "s_add_sat\0" // IR(54121, 10)
  "u_add_sat\0" // IR(54131, 10)
  "s_hadd\0" // IR(54141, 7)
  "u_hadd\0" // IR(54148, 7)
  "s_rhadd\0" // IR(54155, 8)
  "u_rhadd\0" // IR(54163, 8)
  "s_clamp\0" // IR(54171, 8)
  "u_clamp\0" // IR(54179, 8)
  "clz\0" // IR(54187, 4)
  "ctz\0" // IR(54191, 4)
  "s_mad_hi\0" // IR(54195, 9)
  "u_mad_sat\0" // IR(54204, 10)
  "s_mad_sat\0" // IR(54214, 10)
  "s_max\0" // IR(54224, 6)
  "u_max\0" // IR(54230, 6)
  "s_min\0" // IR(54236, 6)
  "u_min\0" // IR(54242, 6)
  "s_mul_hi\0" // IR(54248, 9)
  "rotate\0" // IR(54257, 7)
  "s_sub_sat\0" // IR(54264, 10)
  "u_sub_sat\0" // IR(54274, 10)
  "u_upsample\0" // IR(54284, 11)
  "s_upsample\0" // IR(54295, 11)
  "popcount\0" // IR(54306, 9)
  "s_mad24\0" // IR(54315, 8)
  "u_mad24\0" // IR(54323, 8)
  "s_mul24\0" // IR(54331, 8)
  "u_mul24\0" // IR(54339, 8)
  "vloadn\0" // IR(54347, 7)
  "vstoren\0" // IR(54354, 8)
  "vload_half\0" // IR(54362, 11)
  "vload_halfn\0" // IR(54373, 12)
  "vstore_half\0" // IR(54385, 12)
  "vstore_half_r\0" // IR(54397, 14)
  "vstore_halfn\0" // IR(54411, 13)
  "vstore_halfn_r\0" // IR(54424, 15)
  "vloada_halfn\0" // IR(54439, 13)
  "vstorea_halfn\0" // IR(54452, 14)
  "vstorea_halfn_r\0" // IR(54466, 16)
  "shuffle\0" // IR(54482, 8)
  "shuffle2\0" // IR(54490, 9)
  "printf\0" // IR(54499, 7)
  "prefetch\0" // IR(54506, 9)
  "bitselect\0" // IR(54515, 10)
  "select\0" // IR(54525, 7)
  "u_abs\0" // IR(54532, 6)
  "u_abs_diff\0" // IR(54538, 11)
  "u_mul_hi\0" // IR(54549, 9)
  "u_mad_hi\0" // IR(54558, 9)
  "CubeFaceIndexAMD\0" // IR(54567, 17)
  "CubeFaceCoordAMD\0" // IR(54584, 17)
  "TimeAMD\0" // IR(54601, 8)
  "SwizzleInvocationsAMD\0" // IR(54609, 22)
  "SwizzleInvocationsMaskedAMD\0" // IR(54631, 28)
  "WriteInvocationAMD\0" // IR(54659, 19)
  "MbcntAMD\0" // IR(54678, 9)
  "InterpolateAtVertexAMD\0" // IR(54687, 23)
  "FMin3AMD\0" // IR(54710, 9)
  "UMin3AMD\0" // IR(54719, 9)
  "SMin3AMD\0" // IR(54728, 9)
  "FMax3AMD\0" // IR(54737, 9)
  "UMax3AMD\0" // IR(54746, 9)
  "SMax3AMD\0" // IR(54755, 9)
  "FMid3AMD\0" // IR(54764, 9)
  "UMid3AMD\0" // IR(54773, 9)
  "SMid3AMD\0" // IR(54782, 9)
;

// Array of IndexRanges, where each represents a string by referencing
// the kStrings table.
// This array contains all sequences of alias strings used in the grammar.
// This table is referenced by an IndexRange elsewhere, i.e. by the 'aliases'
// field of an instruction or operand description.
static const IndexRange kAliasSpans[] = {
  IR(5448, 27), // 0 PhysicalStorageBuffer64EXT
  IR(6359, 18), // 1 SubgroupEqMaskKHR
  IR(6414, 18), // 2 SubgroupGeMaskKHR
  IR(6447, 18), // 3 SubgroupGtMaskKHR
  IR(6480, 18), // 4 SubgroupLeMaskKHR
  IR(6513, 18), // 5 SubgroupLtMaskKHR
  IR(7371, 12), // 6 BaryCoordNV
  IR(7426, 19), // 7 BaryCoordNoPerspNV
  IR(7457, 15), // 8 FragmentSizeNV
  IR(7514, 22), // 9 InvocationsPerPixelNV
  IR(7642, 11), // 10 LaunchIdNV
  IR(7667, 13), // 11 LaunchSizeNV
  IR(7698, 17), // 12 WorldRayOriginNV
  IR(7736, 20), // 13 WorldRayDirectionNV
  IR(7775, 18), // 14 ObjectRayOriginNV
  IR(7815, 21), // 15 ObjectRayDirectionNV
  IR(7847, 10), // 16 RayTminNV
  IR(7868, 10), // 17 RayTmaxNV
  IR(7901, 22), // 18 InstanceCustomIndexNV
  IR(7940, 16), // 19 ObjectToWorldNV
  IR(7973, 16), // 20 WorldToObjectNV
  IR(8007, 10), // 21 HitKindNV
  IR(8238, 19), // 22 IncomingRayFlagsNV
  IR(10014, 28), // 23 StorageUniformBufferBlock16
  IR(10077, 17), // 24 StorageUniform16
  IR(10892, 27), // 25 ShaderViewportIndexLayerNV
  IR(10936, 22), // 26 FragmentBarycentricNV
  IR(10989, 30), // 27 ComputeDerivativeGroupQuadsNV
  IR(11019, 14), // 28 ShadingRateNV
  IR(11079, 20), // 29 ShaderNonUniformEXT
  IR(11122, 26), // 30 RuntimeDescriptorArrayEXT
  IR(11184, 39), // 31 InputAttachmentArrayDynamicIndexingEXT
  IR(11262, 42), // 32 UniformTexelBufferArrayDynamicIndexingEXT
  IR(11343, 42), // 33 StorageTexelBufferArrayDynamicIndexingEXT
  IR(11422, 40), // 34 UniformBufferArrayNonUniformIndexingEXT
  IR(11498, 39), // 35 SampledImageArrayNonUniformIndexingEXT
  IR(11574, 40), // 36 StorageBufferArrayNonUniformIndexingEXT
  IR(11650, 39), // 37 StorageImageArrayNonUniformIndexingEXT
  IR(11728, 42), // 38 InputAttachmentArrayNonUniformIndexingEXT
  IR(11812, 45), // 39 UniformTexelBufferArrayNonUniformIndexingEXT
  IR(11899, 45), // 40 StorageTexelBufferArrayNonUniformIndexingEXT
  IR(11962, 21), // 41 VulkanMemoryModelKHR
  IR(12012, 32), // 42 VulkanMemoryModelDeviceScopeKHR
  IR(12044, 34), // 43 PhysicalStorageBufferAddressesEXT
  IR(12110, 31), // 44 ComputeDerivativeGroupLinearNV
  IR(12314, 28), // 45 DemoteToHelperInvocationEXT
  IR(13321, 26), // 46 FPGAMemoryAttributesINTEL
  IR(13400, 32), // 47 ArbitraryPrecisionIntegersINTEL
  IR(13470, 37), // 48 ArbitraryPrecisionFloatingPointINTEL
  IR(13560, 22), // 49 FPGALoopControlsINTEL
  IR(13655, 24), // 50 FPGAMemoryAccessesINTEL
  IR(13707, 27), // 51 FPGAClusterAttributesINTEL
  IR(13749, 14), // 52 LoopFuseINTEL
  IR(13784, 20), // 53 FPGADSPControlINTEL
  IR(13871, 40), // 54 FPGAInvocationPipeliningAttributesINTEL
  IR(13936, 24), // 55 FPGABufferLocationINTEL
  IR(13995, 34), // 56 ArbitraryPrecisionFixedPointINTEL
  IR(14053, 23), // 57 USMStorageClassesINTEL
  IR(14106, 29), // 58 RuntimeAlignedAttributeINTEL
  IR(14149, 13), // 59 IOPipesINTEL
  IR(14182, 19), // 60 BlockingPipesINTEL
  IR(14215, 13), // 61 FPGARegINTEL
  IR(14247, 22), // 62 DotProductInputAllKHR
  IR(14291, 25), // 63 DotProductInput4x8BitKHR
  IR(14344, 31), // 64 DotProductInput4x8BitPackedKHR
  IR(14386, 14), // 65 DotProductKHR
  IR(14558, 13), // 66 OptNoneINTEL
  IR(14703, 29), // 67 FPGAClusterAttributesV2INTEL
  IR(14779, 18), // 68 TaskSequenceINTEL
  IR(14838, 24), // 69 FPGALatencyControlINTEL
  IR(14891, 28), // 70 FPGAArgumentInterfacesINTEL
  IR(14985, 35), // 71 GlobalVariableFPGADecorationsINTEL
  IR(17768, 15), // 72 PerPrimitiveNV
  IR(17816, 12), // 73 PerVertexNV
  IR(17839, 14), // 74 NonUniformEXT
  IR(17869, 19), // 75 RestrictPointerEXT
  IR(17903, 18), // 76 AliasedPointerEXT
  IR(18244, 24), // 77 HlslCounterBufferGOOGLE
  IR(18281, 19), // 78 HlslSemanticGOOGLE
  IR(18411, 14), // 79 RegisterINTEL
  IR(18438, 12), // 80 MemoryINTEL
  IR(18465, 14), // 81 NumbanksINTEL
  IR(18495, 15), // 82 BankwidthINTEL
  IR(18533, 22), // 83 MaxPrivateCopiesINTEL
  IR(18572, 16), // 84 SinglepumpINTEL
  IR(18605, 16), // 85 DoublepumpINTEL
  IR(18641, 19), // 86 MaxReplicatesINTEL
  IR(18681, 20), // 87 SimpleDualPortINTEL
  IR(18713, 11), // 88 MergeINTEL
  IR(18781, 14), // 89 BankBitsINTEL
  IR(18816, 20), // 90 ForcePow2DepthINTEL
  IR(18853, 16), // 91 StridesizeINTEL
  IR(18884, 14), // 92 WordsizeINTEL
  IR(18917, 18), // 93 TrueDualPortINTEL
  IR(18955, 19), // 94 BurstCoalesceINTEL
  IR(18990, 15), // 95 CacheSizeINTEL
  IR(19034, 28), // 96 DontStaticallyCoalesceINTEL
  IR(19077, 14), // 97 PrefetchINTEL
  IR(19109, 17), // 98 StallEnableINTEL
  IR(19152, 25), // 99 FuseLoopsInFunctionINTEL
  IR(19197, 19), // 100 MathOpDSPModeINTEL
  IR(19270, 24), // 101 InitiationIntervalINTEL
  IR(19315, 20), // 102 MaxConcurrencyINTEL
  IR(19356, 20), // 103 PipelineEnableINTEL
  IR(19397, 20), // 104 BufferLocationINTEL
  IR(19437, 19), // 105 IOPipeStorageINTEL
  IR(19615, 15), // 106 StallFreeINTEL
  IR(19713, 25), // 107 LatencyControlLabelINTEL
  IR(19769, 30), // 108 LatencyControlConstraintINTEL
  IR(19827, 27), // 109 ConduitKernelArgumentINTEL
  IR(19886, 31), // 110 RegisterMapKernelArgumentINTEL
  IR(19951, 33), // 111 MMHostInterfaceAddressWidthINTEL
  IR(20015, 30), // 112 MMHostInterfaceDataWidthINTEL
  IR(20074, 28), // 113 MMHostInterfaceLatencyINTEL
  IR(20171, 34), // 114 MMHostInterfaceReadWriteModeINTEL
  IR(20235, 29), // 115 MMHostInterfaceMaxBurstINTEL
  IR(20297, 32), // 116 MMHostInterfaceWaitRequestINTEL
  IR(20356, 26), // 117 StableKernelArgumentINTEL
  IR(20499, 14), // 118 InitModeINTEL
  IR(20542, 28), // 119 ImplementInRegisterMapINTEL
  IR(21876, 14), // 120 OutputLinesNV
  IR(21910, 19), // 121 OutputPrimitivesNV
  IR(21953, 23), // 122 DerivativeGroupQuadsNV
  IR(22001, 24), // 123 DerivativeGroupLinearNV
  IR(22044, 18), // 124 OutputTrianglesNV
  IR(22792, 16), // 125 RayGenerationNV
  IR(22824, 15), // 126 IntersectionNV
  IR(22849, 9), // 127 AnyHitNV
  IR(22872, 13), // 128 ClosestHitNV
  IR(22893, 7), // 129 MissNV
  IR(22912, 11), // 130 CallableNV
  IR(23057, 23), // 131 AllowContractFastINTEL
  IR(23093, 18), // 132 AllowReassocINTEL
  IR(23319, 20), // 133 RuntimeAlignedINTEL
  IR(23568, 22), // 134 MakeTexelAvailableKHR
  IR(23607, 20), // 135 MakeTexelVisibleKHR
  IR(23643, 19), // 136 NonPrivateTexelKHR
  IR(23676, 17), // 137 VolatileTexelKHR
  IR(24235, 27), // 138 InitOnDeviceReprogramINTEL
  IR(24286, 23), // 139 InitOnDeviceResetINTEL
  IR(24620, 21), // 140 DependencyArrayINTEL
  IR(24660, 18), // 141 LoopCoalesceINTEL
  IR(24700, 21), // 142 MaxInterleavingINTEL
  IR(24748, 26), // 143 SpeculatedIterationsINTEL
  IR(24789, 14), // 144 NoFusionINTEL
  IR(24819, 15), // 145 LoopCountINTEL
  IR(24861, 26), // 146 MaxReinvocationDelayINTEL
  IR(25253, 24), // 147 MakePointerAvailableKHR
  IR(25296, 22), // 148 MakePointerVisibleKHR
  IR(25336, 21), // 149 NonPrivatePointerKHR
  IR(25423, 10), // 150 VulkanKHR
  IR(15540, 5), // 151 None
  IR(25606, 16), // 152 OutputMemoryKHR
  IR(25636, 17), // 153 MakeAvailableKHR
  IR(25665, 15), // 154 MakeVisibleKHR
  IR(25741, 28), // 155 PackedVectorFormat4x8BitKHR
  IR(26056, 24), // 156 SkipBuiltinPrimitivesNV
  IR(26796, 15), // 157 QueueFamilyKHR
  IR(27167, 15), // 158 CallableDataNV
  IR(27206, 23), // 159 IncomingCallableDataNV
  IR(27243, 13), // 160 RayPayloadNV
  IR(27272, 15), // 161 HitAttributeNV
  IR(27309, 21), // 162 IncomingRayPayloadNV
  IR(27352, 21), // 163 ShaderRecordBufferNV
  IR(27395, 25), // 164 PhysicalStorageBufferEXT
  IR(27521, 16), // 165 DeviceOnlyINTEL
  IR(27552, 14), // 166 HostOnlyINTEL
  IR(34790, 8), // 167 SDotKHR
  IR(34803, 8), // 168 UDotKHR
  IR(34817, 9), // 169 SUDotKHR
  IR(34837, 14), // 170 SDotAccSatKHR
  IR(34862, 14), // 171 UDotAccSatKHR
  IR(34888, 15), // 172 SUDotAccSatKHR
  IR(38346, 21), // 173 ReportIntersectionNV
  IR(38521, 28), // 174 TypeAccelerationStructureNV
  IR(38602, 23), // 175 RayQueryGetClusterIdNV
  IR(40770, 21), // 176 DecorateStringGOOGLE
  IR(40812, 27), // 177 MemberDecorateStringGOOGLE
  IR(46069, 28), // 178 ArbitraryFloatSinCosPiINTEL
  IR(46122, 24), // 179 ArbitraryFloatCastINTEL
  IR(46178, 31), // 180 ArbitraryFloatCastFromIntINTEL
  IR(46239, 29), // 181 ArbitraryFloatCastToIntINTEL
  IR(46292, 23), // 182 ArbitraryFloatAddINTEL
  IR(46339, 23), // 183 ArbitraryFloatSubINTEL
  IR(46386, 23), // 184 ArbitraryFloatMulINTEL
  IR(46433, 23), // 185 ArbitraryFloatDivINTEL
  IR(46479, 22), // 186 ArbitraryFloatGTINTEL
  IR(46524, 22), // 187 ArbitraryFloatGEINTEL
  IR(46569, 22), // 188 ArbitraryFloatLTINTEL
  IR(46614, 22), // 189 ArbitraryFloatLEINTEL
  IR(46659, 22), // 190 ArbitraryFloatEQINTEL
  IR(46707, 25), // 191 ArbitraryFloatRecipINTEL
  IR(46758, 25), // 192 ArbitraryFloatRSqrtINTEL
  IR(46808, 24), // 193 ArbitraryFloatCbrtINTEL
  IR(46858, 25), // 194 ArbitraryFloatHypotINTEL
  IR(46908, 24), // 195 ArbitraryFloatSqrtINTEL
  IR(47592, 15), // 196 FixedSqrtINTEL
  IR(47624, 16), // 197 FixedRecipINTEL
  IR(47657, 16), // 198 FixedRsqrtINTEL
  IR(47688, 14), // 199 FixedSinINTEL
  IR(47717, 14), // 200 FixedCosINTEL
  IR(47749, 17), // 201 FixedSinCosINTEL
  IR(47783, 16), // 202 FixedSinPiINTEL
  IR(47816, 16), // 203 FixedCosPiINTEL
  IR(47852, 19), // 204 FixedSinCosPiINTEL
  IR(47886, 14), // 205 FixedLogINTEL
  IR(47915, 14), // 206 FixedExpINTEL
  IR(47959, 29), // 207 PtrCastToCrossWorkgroupINTEL
  IR(48018, 29), // 208 CrossWorkgroupCastToPtrINTEL
  IR(48070, 22), // 209 ReadPipeBlockingINTEL
  IR(48116, 23), // 210 WritePipeBlockingINTEL
  IR(49068, 24), // 211 TaskSequenceCreateINTEL
  IR(49116, 23), // 212 TaskSequenceAsyncINTEL
  IR(49161, 21), // 213 TaskSequenceGetINTEL
  IR(49208, 25), // 214 TaskSequenceReleaseINTEL
  IR(49256, 22), // 215 TypeTaskSequenceINTEL
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
  spv::Capability::CooperativeVectorTrainingNV, // 257
  spv::Capability::CooperativeMatrixConversionsNV, // 258
  spv::Capability::DisplacementMicromapNV, // 259
  spv::Capability::ShaderInvocationReorderEXT, // 260
  spv::Capability::RayTracingMotionBlurNV, // 261
  spv::Capability::RayQueryPositionFetchKHR, // 262
  spv::Capability::RayTracingNV, // 263
  spv::Capability::RayTracingKHR, // 264
  spv::Capability::RayQueryKHR, // 265
  spv::Capability::DisplacementMicromapNV, // 266
  spv::Capability::CooperativeMatrixNV, // 267
  spv::Capability::FragmentShaderSampleInterlockEXT, // 268
  spv::Capability::FragmentShaderPixelInterlockEXT, // 269
  spv::Capability::FragmentShaderShadingRateInterlockEXT, // 270
  spv::Capability::CooperativeMatrixReductionsNV, // 271
  spv::Capability::CooperativeMatrixPerElementOperationsNV, // 272
  spv::Capability::TensorAddressingNV, // 273
  spv::Capability::DemoteToHelperInvocation, // 274
  spv::Capability::SubgroupShuffleINTEL, // 275
  spv::Capability::SubgroupBufferBlockIOINTEL, // 276
  spv::Capability::SubgroupImageBlockIOINTEL, // 277
  spv::Capability::SubgroupImageMediaBlockIOINTEL, // 278
  spv::Capability::IntegerFunctions2INTEL, // 279
  spv::Capability::AtomicFloat16MinMaxEXT, // 280
  spv::Capability::AtomicFloat32MinMaxEXT, // 281
  spv::Capability::AtomicFloat64MinMaxEXT, // 282
  spv::Capability::AtomicFloat16VectorNV, // 283
  spv::Capability::ExpectAssumeKHR, // 284
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 285
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 286
  spv::Capability::SubgroupAvcMotionEstimationIntraINTEL, // 287
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 288
  spv::Capability::SubgroupAvcMotionEstimationChromaINTEL, // 289
  spv::Capability::VariableLengthArrayINTEL, // 290
  spv::Capability::ArbitraryPrecisionFloatingPointALTERA, // 291
  spv::Capability::UnstructuredLoopControlsINTEL, // 292
  spv::Capability::BlockingPipesALTERA, // 293
  spv::Capability::FPGARegALTERA, // 294
  spv::Capability::AtomicFloat16AddEXT, // 295
  spv::Capability::AtomicFloat32AddEXT, // 296
  spv::Capability::AtomicFloat64AddEXT, // 297
  spv::Capability::AtomicFloat16VectorNV, // 298
  spv::Capability::LongCompositesINTEL, // 299
  spv::Capability::BFloat16ConversionINTEL, // 300
  spv::Capability::SplitBarrierINTEL, // 301
  spv::Capability::ArithmeticFenceEXT, // 302
  spv::Capability::TaskSequenceALTERA, // 303
  spv::Capability::SubgroupBufferPrefetchINTEL, // 304
  spv::Capability::Subgroup2DBlockTransformINTEL, // 305
  spv::Capability::Subgroup2DBlockTransposeINTEL, // 306
  spv::Capability::SubgroupMatrixMultiplyAccumulateINTEL, // 307
  spv::Capability::TernaryBitwiseFunctionINTEL, // 308
  spv::Capability::UntypedVariableLengthArrayINTEL, // 309
  spv::Capability::FunctionVariantsINTEL, // 310
  spv::Capability::GroupUniformArithmeticKHR, // 311
  spv::Capability::TensorFloat32RoundingINTEL, // 312
  spv::Capability::MaskedGatherScatterINTEL, // 313
  spv::Capability::BindlessImagesINTEL, // 314
  spv::Capability::Float64, // 315
  spv::Capability::InterpolationFunction, // 316
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
  spvtools::Extension::kSPV_EXT_shader_64bit_indexing, // 90
  spvtools::Extension::kSPV_NV_cooperative_matrix2, // 91
  spvtools::Extension::kSPV_NV_tensor_addressing, // 92
  spvtools::Extension::kSPV_INTEL_subgroups, // 93
  spvtools::Extension::kSPV_INTEL_media_block_io, // 94
  spvtools::Extension::kSPV_INTEL_float_controls2, // 95
  spvtools::Extension::kSPV_INTEL_shader_integer_functions2, // 96
  spvtools::Extension::kSPV_INTEL_function_pointers, // 97
  spvtools::Extension::kSPV_INTEL_inline_assembly, // 98
  spvtools::Extension::kSPV_EXT_shader_atomic_float_min_max, // 99
  spvtools::Extension::kSPV_INTEL_vector_compute, // 100
  spvtools::Extension::kSPV_KHR_expect_assume, // 101
  spvtools::Extension::kSPV_INTEL_device_side_avc_motion_estimation, // 102
  spvtools::Extension::kSPV_INTEL_variable_length_array, // 103
  spvtools::Extension::kSPV_ALTERA_fpga_memory_attributes, // 104
  spvtools::Extension::kSPV_INTEL_fpga_memory_attributes, // 105
  spvtools::Extension::kSPV_INTEL_fp_fast_math_mode, // 106
  spvtools::Extension::kSPV_ALTERA_arbitrary_precision_integers, // 107
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_integers, // 108
  spvtools::Extension::kSPV_ALTERA_arbitrary_precision_floating_point, // 109
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_floating_point, // 110
  spvtools::Extension::kSPV_INTEL_unstructured_loop_controls, // 111
  spvtools::Extension::kSPV_ALTERA_fpga_loop_controls, // 112
  spvtools::Extension::kSPV_INTEL_fpga_loop_controls, // 113
  spvtools::Extension::kSPV_INTEL_kernel_attributes, // 114
  spvtools::Extension::kSPV_ALTERA_fpga_memory_accesses, // 115
  spvtools::Extension::kSPV_INTEL_fpga_memory_accesses, // 116
  spvtools::Extension::kSPV_ALTERA_fpga_cluster_attributes, // 117
  spvtools::Extension::kSPV_INTEL_fpga_cluster_attributes, // 118
  spvtools::Extension::kSPV_ALTERA_loop_fuse, // 119
  spvtools::Extension::kSPV_INTEL_loop_fuse, // 120
  spvtools::Extension::kSPV_ALTERA_fpga_dsp_control, // 121
  spvtools::Extension::kSPV_INTEL_fpga_dsp_control, // 122
  spvtools::Extension::kSPV_INTEL_memory_access_aliasing, // 123
  spvtools::Extension::kSPV_ALTERA_fpga_invocation_pipelining_attributes, // 124
  spvtools::Extension::kSPV_INTEL_fpga_invocation_pipelining_attributes, // 125
  spvtools::Extension::kSPV_ALTERA_fpga_buffer_location, // 126
  spvtools::Extension::kSPV_INTEL_fpga_buffer_location, // 127
  spvtools::Extension::kSPV_ALTERA_arbitrary_precision_fixed_point, // 128
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_fixed_point, // 129
  spvtools::Extension::kSPV_ALTERA_usm_storage_classes, // 130
  spvtools::Extension::kSPV_INTEL_usm_storage_classes, // 131
  spvtools::Extension::kSPV_ALTERA_runtime_aligned, // 132
  spvtools::Extension::kSPV_INTEL_runtime_aligned, // 133
  spvtools::Extension::kSPV_ALTERA_io_pipes, // 134
  spvtools::Extension::kSPV_INTEL_io_pipes, // 135
  spvtools::Extension::kSPV_ALTERA_blocking_pipes, // 136
  spvtools::Extension::kSPV_INTEL_blocking_pipes, // 137
  spvtools::Extension::kSPV_ALTERA_fpga_reg, // 138
  spvtools::Extension::kSPV_INTEL_fpga_reg, // 139
  spvtools::Extension::kSPV_KHR_integer_dot_product, // 140
  spvtools::Extension::kSPV_KHR_cooperative_matrix, // 141
  spvtools::Extension::kSPV_EXT_replicated_composites, // 142
  spvtools::Extension::kSPV_KHR_bit_instructions, // 143
  spvtools::Extension::kSPV_KHR_subgroup_rotate, // 144
  spvtools::Extension::kSPV_KHR_float_controls2, // 145
  spvtools::Extension::kSPV_KHR_fma, // 146
  spvtools::Extension::kSPV_EXT_shader_atomic_float_add, // 147
  spvtools::Extension::kSPV_INTEL_long_composites, // 148
  spvtools::Extension::kSPV_EXT_optnone, // 149
  spvtools::Extension::kSPV_INTEL_optnone, // 150
  spvtools::Extension::kSPV_EXT_shader_atomic_float16_add, // 151
  spvtools::Extension::kSPV_INTEL_debug_module, // 152
  spvtools::Extension::kSPV_INTEL_bfloat16_conversion, // 153
  spvtools::Extension::kSPV_INTEL_split_barrier, // 154
  spvtools::Extension::kSPV_EXT_arithmetic_fence, // 155
  spvtools::Extension::kSPV_ALTERA_task_sequence, // 156
  spvtools::Extension::kSPV_INTEL_task_sequence, // 157
  spvtools::Extension::kSPV_INTEL_fp_max_error, // 158
  spvtools::Extension::kSPV_ALTERA_fpga_latency_control, // 159
  spvtools::Extension::kSPV_INTEL_fpga_latency_control, // 160
  spvtools::Extension::kSPV_ALTERA_fpga_argument_interfaces, // 161
  spvtools::Extension::kSPV_INTEL_fpga_argument_interfaces, // 162
  spvtools::Extension::kSPV_INTEL_global_variable_host_access, // 163
  spvtools::Extension::kSPV_ALTERA_global_variable_fpga_decorations, // 164
  spvtools::Extension::kSPV_INTEL_global_variable_fpga_decorations, // 165
  spvtools::Extension::kSPV_INTEL_subgroup_buffer_prefetch, // 166
  spvtools::Extension::kSPV_INTEL_2d_block_io, // 167
  spvtools::Extension::kSPV_INTEL_subgroup_matrix_multiply_accumulate, // 168
  spvtools::Extension::kSPV_INTEL_ternary_bitwise_function, // 169
  spvtools::Extension::kSPV_INTEL_function_variants, // 170
  spvtools::Extension::kSPV_KHR_uniform_group_instructions, // 171
  spvtools::Extension::kSPV_INTEL_tensor_float32_conversion, // 172
  spvtools::Extension::kSPV_INTEL_masked_gather_scatter, // 173
  spvtools::Extension::kSPV_INTEL_cache_controls, // 174
  spvtools::Extension::kSPV_INTEL_maximum_registers, // 175
  spvtools::Extension::kSPV_INTEL_bindless_images, // 176
  spvtools::Extension::kSPV_KHR_no_integer_wrap_decoration, // 177
  spvtools::Extension::kSPV_NV_mesh_shader, // 178
  spvtools::Extension::kSPV_EXT_mesh_shader, // 179
  spvtools::Extension::kSPV_GOOGLE_hlsl_functionality1, // 180
  spvtools::Extension::kSPV_GOOGLE_user_type, // 181
  spvtools::Extension::kSPV_KHR_subgroup_uniform_control_flow, // 182
  spvtools::Extension::kSPV_AMD_shader_early_and_late_fragment_tests, // 183
  spvtools::Extension::kSPV_AMD_shader_early_and_late_fragment_tests, // 184
  spvtools::Extension::kSPV_EXT_shader_stencil_export, // 185
  spvtools::Extension::kSPV_KHR_maximal_reconvergence, // 186
  spvtools::Extension::kSPV_KHR_linkonce_odr, // 187
  spvtools::Extension::kSPV_KHR_storage_buffer_storage_class, // 188
  spvtools::Extension::kSPV_KHR_variable_pointers, // 189
  spvtools::Extension::kSPV_KHR_terminate_invocation, // 190
  spvtools::Extension::kSPV_KHR_relaxed_extended_instruction, // 191
  spvtools::Extension::kSPV_KHR_ray_tracing, // 192
  spvtools::Extension::kSPV_KHR_ray_query, // 193
  spvtools::Extension::kSPV_NV_ray_tracing, // 194
  spvtools::Extension::kSPV_KHR_ray_tracing, // 195
  spvtools::Extension::kSPV_KHR_ray_query, // 196
  spvtools::Extension::kSPV_NV_displacement_micromap, // 197
  spvtools::Extension::kSPV_GOOGLE_decorate_string, // 198
  spvtools::Extension::kSPV_GOOGLE_hlsl_functionality1, // 199
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
