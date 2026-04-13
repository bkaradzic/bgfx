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
    case Extension::kSPV_KHR_abort: return IR(3495, 14);
    case Extension::kSPV_KHR_bfloat16: return IR(3509, 17);
    case Extension::kSPV_KHR_bit_instructions: return IR(3526, 25);
    case Extension::kSPV_KHR_compute_shader_derivatives: return IR(3551, 35);
    case Extension::kSPV_KHR_constant_data: return IR(3586, 22);
    case Extension::kSPV_KHR_cooperative_matrix: return IR(3608, 27);
    case Extension::kSPV_KHR_device_group: return IR(3635, 21);
    case Extension::kSPV_KHR_expect_assume: return IR(3656, 22);
    case Extension::kSPV_KHR_float_controls: return IR(3678, 23);
    case Extension::kSPV_KHR_float_controls2: return IR(3701, 24);
    case Extension::kSPV_KHR_fma: return IR(3725, 12);
    case Extension::kSPV_KHR_fragment_shader_barycentric: return IR(3737, 36);
    case Extension::kSPV_KHR_fragment_shading_rate: return IR(3773, 30);
    case Extension::kSPV_KHR_integer_dot_product: return IR(3803, 28);
    case Extension::kSPV_KHR_linkonce_odr: return IR(3831, 21);
    case Extension::kSPV_KHR_maximal_reconvergence: return IR(3852, 30);
    case Extension::kSPV_KHR_multiview: return IR(3882, 18);
    case Extension::kSPV_KHR_no_integer_wrap_decoration: return IR(3900, 35);
    case Extension::kSPV_KHR_non_semantic_info: return IR(3935, 26);
    case Extension::kSPV_KHR_physical_storage_buffer: return IR(3961, 32);
    case Extension::kSPV_KHR_poison_freeze: return IR(3993, 22);
    case Extension::kSPV_KHR_post_depth_coverage: return IR(4015, 28);
    case Extension::kSPV_KHR_quad_control: return IR(4043, 21);
    case Extension::kSPV_KHR_ray_cull_mask: return IR(4064, 22);
    case Extension::kSPV_KHR_ray_query: return IR(4086, 18);
    case Extension::kSPV_KHR_ray_tracing: return IR(4104, 20);
    case Extension::kSPV_KHR_ray_tracing_position_fetch: return IR(4124, 35);
    case Extension::kSPV_KHR_relaxed_extended_instruction: return IR(4159, 37);
    case Extension::kSPV_KHR_shader_atomic_counter_ops: return IR(4196, 34);
    case Extension::kSPV_KHR_shader_ballot: return IR(4230, 22);
    case Extension::kSPV_KHR_shader_clock: return IR(4252, 21);
    case Extension::kSPV_KHR_shader_draw_parameters: return IR(4273, 31);
    case Extension::kSPV_KHR_storage_buffer_storage_class: return IR(4304, 37);
    case Extension::kSPV_KHR_subgroup_rotate: return IR(4341, 24);
    case Extension::kSPV_KHR_subgroup_uniform_control_flow: return IR(4365, 38);
    case Extension::kSPV_KHR_subgroup_vote: return IR(4403, 22);
    case Extension::kSPV_KHR_terminate_invocation: return IR(4425, 29);
    case Extension::kSPV_KHR_uniform_group_instructions: return IR(4454, 35);
    case Extension::kSPV_KHR_untyped_pointers: return IR(4489, 25);
    case Extension::kSPV_KHR_variable_pointers: return IR(4514, 26);
    case Extension::kSPV_KHR_vulkan_memory_model: return IR(4540, 28);
    case Extension::kSPV_KHR_workgroup_memory_explicit_layout: return IR(4568, 41);
    case Extension::kSPV_NVX_multiview_per_view_attributes: return IR(4609, 38);
    case Extension::kSPV_NV_bindless_texture: return IR(4647, 24);
    case Extension::kSPV_NV_cluster_acceleration_structure: return IR(4671, 38);
    case Extension::kSPV_NV_compute_shader_derivatives: return IR(4709, 34);
    case Extension::kSPV_NV_cooperative_matrix: return IR(4743, 26);
    case Extension::kSPV_NV_cooperative_matrix2: return IR(4769, 27);
    case Extension::kSPV_NV_cooperative_vector: return IR(4796, 26);
    case Extension::kSPV_NV_displacement_micromap: return IR(4822, 29);
    case Extension::kSPV_NV_fragment_shader_barycentric: return IR(4851, 35);
    case Extension::kSPV_NV_geometry_shader_passthrough: return IR(4886, 35);
    case Extension::kSPV_NV_linear_swept_spheres: return IR(4921, 28);
    case Extension::kSPV_NV_mesh_shader: return IR(4949, 19);
    case Extension::kSPV_NV_push_constant_bank: return IR(4968, 26);
    case Extension::kSPV_NV_raw_access_chains: return IR(4994, 25);
    case Extension::kSPV_NV_ray_tracing: return IR(5019, 19);
    case Extension::kSPV_NV_ray_tracing_motion_blur: return IR(5038, 31);
    case Extension::kSPV_NV_sample_mask_override_coverage: return IR(5069, 37);
    case Extension::kSPV_NV_shader_atomic_fp16_vector: return IR(5106, 33);
    case Extension::kSPV_NV_shader_image_footprint: return IR(5139, 30);
    case Extension::kSPV_NV_shader_invocation_reorder: return IR(5169, 33);
    case Extension::kSPV_NV_shader_sm_builtins: return IR(5202, 26);
    case Extension::kSPV_NV_shader_subgroup_partitioned: return IR(5228, 35);
    case Extension::kSPV_NV_shading_rate: return IR(5263, 20);
    case Extension::kSPV_NV_stereo_view_rendering: return IR(5283, 29);
    case Extension::kSPV_NV_tensor_addressing: return IR(5312, 25);
    case Extension::kSPV_NV_viewport_array2: return IR(5337, 23);
    case Extension::kSPV_QCOM_cooperative_matrix_conversion: return IR(5360, 39);
    case Extension::kSPV_QCOM_image_processing: return IR(5399, 26);
    case Extension::kSPV_QCOM_image_processing2: return IR(5425, 27);
    case Extension::kSPV_QCOM_tile_shading: return IR(5452, 22);
    case Extension::kSPV_VALIDATOR_ignore_type_decl_unique: return IR(5474, 38);
    case Extension::kSPV_VALVE_mixed_float_dot_product: return IR(5512, 34);
    default: break;
  }
  return {};
}

// Extension names and values, ordered by name
// The fields in order are:
//   name, indexing into kStrings
//   enum value
static const std::array<NameValue,191> kExtensionNames{{
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
    {IR(3495, 14), static_cast<uint32_t>(kSPV_KHR_abort)},
    {IR(3509, 17), static_cast<uint32_t>(kSPV_KHR_bfloat16)},
    {IR(3526, 25), static_cast<uint32_t>(kSPV_KHR_bit_instructions)},
    {IR(3551, 35), static_cast<uint32_t>(kSPV_KHR_compute_shader_derivatives)},
    {IR(3586, 22), static_cast<uint32_t>(kSPV_KHR_constant_data)},
    {IR(3608, 27), static_cast<uint32_t>(kSPV_KHR_cooperative_matrix)},
    {IR(3635, 21), static_cast<uint32_t>(kSPV_KHR_device_group)},
    {IR(3656, 22), static_cast<uint32_t>(kSPV_KHR_expect_assume)},
    {IR(3678, 23), static_cast<uint32_t>(kSPV_KHR_float_controls)},
    {IR(3701, 24), static_cast<uint32_t>(kSPV_KHR_float_controls2)},
    {IR(3725, 12), static_cast<uint32_t>(kSPV_KHR_fma)},
    {IR(3737, 36), static_cast<uint32_t>(kSPV_KHR_fragment_shader_barycentric)},
    {IR(3773, 30), static_cast<uint32_t>(kSPV_KHR_fragment_shading_rate)},
    {IR(3803, 28), static_cast<uint32_t>(kSPV_KHR_integer_dot_product)},
    {IR(3831, 21), static_cast<uint32_t>(kSPV_KHR_linkonce_odr)},
    {IR(3852, 30), static_cast<uint32_t>(kSPV_KHR_maximal_reconvergence)},
    {IR(3882, 18), static_cast<uint32_t>(kSPV_KHR_multiview)},
    {IR(3900, 35), static_cast<uint32_t>(kSPV_KHR_no_integer_wrap_decoration)},
    {IR(3935, 26), static_cast<uint32_t>(kSPV_KHR_non_semantic_info)},
    {IR(3961, 32), static_cast<uint32_t>(kSPV_KHR_physical_storage_buffer)},
    {IR(3993, 22), static_cast<uint32_t>(kSPV_KHR_poison_freeze)},
    {IR(4015, 28), static_cast<uint32_t>(kSPV_KHR_post_depth_coverage)},
    {IR(4043, 21), static_cast<uint32_t>(kSPV_KHR_quad_control)},
    {IR(4064, 22), static_cast<uint32_t>(kSPV_KHR_ray_cull_mask)},
    {IR(4086, 18), static_cast<uint32_t>(kSPV_KHR_ray_query)},
    {IR(4104, 20), static_cast<uint32_t>(kSPV_KHR_ray_tracing)},
    {IR(4124, 35), static_cast<uint32_t>(kSPV_KHR_ray_tracing_position_fetch)},
    {IR(4159, 37), static_cast<uint32_t>(kSPV_KHR_relaxed_extended_instruction)},
    {IR(4196, 34), static_cast<uint32_t>(kSPV_KHR_shader_atomic_counter_ops)},
    {IR(4230, 22), static_cast<uint32_t>(kSPV_KHR_shader_ballot)},
    {IR(4252, 21), static_cast<uint32_t>(kSPV_KHR_shader_clock)},
    {IR(4273, 31), static_cast<uint32_t>(kSPV_KHR_shader_draw_parameters)},
    {IR(4304, 37), static_cast<uint32_t>(kSPV_KHR_storage_buffer_storage_class)},
    {IR(4341, 24), static_cast<uint32_t>(kSPV_KHR_subgroup_rotate)},
    {IR(4365, 38), static_cast<uint32_t>(kSPV_KHR_subgroup_uniform_control_flow)},
    {IR(4403, 22), static_cast<uint32_t>(kSPV_KHR_subgroup_vote)},
    {IR(4425, 29), static_cast<uint32_t>(kSPV_KHR_terminate_invocation)},
    {IR(4454, 35), static_cast<uint32_t>(kSPV_KHR_uniform_group_instructions)},
    {IR(4489, 25), static_cast<uint32_t>(kSPV_KHR_untyped_pointers)},
    {IR(4514, 26), static_cast<uint32_t>(kSPV_KHR_variable_pointers)},
    {IR(4540, 28), static_cast<uint32_t>(kSPV_KHR_vulkan_memory_model)},
    {IR(4568, 41), static_cast<uint32_t>(kSPV_KHR_workgroup_memory_explicit_layout)},
    {IR(4609, 38), static_cast<uint32_t>(kSPV_NVX_multiview_per_view_attributes)},
    {IR(4647, 24), static_cast<uint32_t>(kSPV_NV_bindless_texture)},
    {IR(4671, 38), static_cast<uint32_t>(kSPV_NV_cluster_acceleration_structure)},
    {IR(4709, 34), static_cast<uint32_t>(kSPV_NV_compute_shader_derivatives)},
    {IR(4743, 26), static_cast<uint32_t>(kSPV_NV_cooperative_matrix)},
    {IR(4769, 27), static_cast<uint32_t>(kSPV_NV_cooperative_matrix2)},
    {IR(4796, 26), static_cast<uint32_t>(kSPV_NV_cooperative_vector)},
    {IR(4822, 29), static_cast<uint32_t>(kSPV_NV_displacement_micromap)},
    {IR(4851, 35), static_cast<uint32_t>(kSPV_NV_fragment_shader_barycentric)},
    {IR(4886, 35), static_cast<uint32_t>(kSPV_NV_geometry_shader_passthrough)},
    {IR(4921, 28), static_cast<uint32_t>(kSPV_NV_linear_swept_spheres)},
    {IR(4949, 19), static_cast<uint32_t>(kSPV_NV_mesh_shader)},
    {IR(4968, 26), static_cast<uint32_t>(kSPV_NV_push_constant_bank)},
    {IR(4994, 25), static_cast<uint32_t>(kSPV_NV_raw_access_chains)},
    {IR(5019, 19), static_cast<uint32_t>(kSPV_NV_ray_tracing)},
    {IR(5038, 31), static_cast<uint32_t>(kSPV_NV_ray_tracing_motion_blur)},
    {IR(5069, 37), static_cast<uint32_t>(kSPV_NV_sample_mask_override_coverage)},
    {IR(5106, 33), static_cast<uint32_t>(kSPV_NV_shader_atomic_fp16_vector)},
    {IR(5139, 30), static_cast<uint32_t>(kSPV_NV_shader_image_footprint)},
    {IR(5169, 33), static_cast<uint32_t>(kSPV_NV_shader_invocation_reorder)},
    {IR(5202, 26), static_cast<uint32_t>(kSPV_NV_shader_sm_builtins)},
    {IR(5228, 35), static_cast<uint32_t>(kSPV_NV_shader_subgroup_partitioned)},
    {IR(5263, 20), static_cast<uint32_t>(kSPV_NV_shading_rate)},
    {IR(5283, 29), static_cast<uint32_t>(kSPV_NV_stereo_view_rendering)},
    {IR(5312, 25), static_cast<uint32_t>(kSPV_NV_tensor_addressing)},
    {IR(5337, 23), static_cast<uint32_t>(kSPV_NV_viewport_array2)},
    {IR(5360, 39), static_cast<uint32_t>(kSPV_QCOM_cooperative_matrix_conversion)},
    {IR(5399, 26), static_cast<uint32_t>(kSPV_QCOM_image_processing)},
    {IR(5425, 27), static_cast<uint32_t>(kSPV_QCOM_image_processing2)},
    {IR(5452, 22), static_cast<uint32_t>(kSPV_QCOM_tile_shading)},
    {IR(5474, 38), static_cast<uint32_t>(kSPV_VALIDATOR_ignore_type_decl_unique)},
    {IR(5512, 34), static_cast<uint32_t>(kSPV_VALVE_mixed_float_dot_product)},
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
static const std::array<OperandDesc, 1212> kOperandsByValue{{
  {0,IR(0, 0),IR(5546, 9)/* ReadOnly */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {1,IR(0, 0),IR(5562, 10)/* WriteOnly */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {2,IR(0, 0),IR(5572, 10)/* ReadWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {0,IR(0, 0),IR(5582, 8)/* Logical */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {1,IR(0, 0),IR(5590, 11)/* Physical32 */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {2,IR(0, 0),IR(5611, 11)/* Physical64 */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {5348,IR(0, 0),IR(5622, 24)/* PhysicalStorageBuffer64 */,IR(0, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {0,IR(0, 0),IR(5704, 9)/* Position */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {1,IR(0, 0),IR(5720, 10)/* PointSize */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {3,IR(0, 0),IR(5730, 13)/* ClipDistance */,IR(0, 0),IR(4, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4,IR(0, 0),IR(5743, 13)/* CullDistance */,IR(0, 0),IR(5, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5,IR(0, 0),IR(5756, 9)/* VertexId */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {6,IR(0, 0),IR(5765, 11)/* InstanceId */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {7,IR(0, 0),IR(5776, 12)/* PrimitiveId */,IR(0, 0),IR(6, 6),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {8,IR(0, 0),IR(5866, 13)/* InvocationId */,IR(0, 0),IR(12, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {9,IR(0, 0),IR(5879, 6)/* Layer */,IR(0, 0),IR(14, 5),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {10,IR(0, 0),IR(5925, 14)/* ViewportIndex */,IR(0, 0),IR(19, 5),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {11,IR(0, 0),IR(5973, 15)/* TessLevelOuter */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {12,IR(0, 0),IR(5988, 15)/* TessLevelInner */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {13,IR(0, 0),IR(6003, 10)/* TessCoord */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {14,IR(0, 0),IR(6013, 14)/* PatchVertices */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {15,IR(0, 0),IR(6027, 10)/* FragCoord */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {16,IR(0, 0),IR(6037, 11)/* PointCoord */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {17,IR(0, 0),IR(6048, 12)/* FrontFacing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {18,IR(0, 0),IR(6060, 9)/* SampleId */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {19,IR(0, 0),IR(6087, 15)/* SamplePosition */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {20,IR(0, 0),IR(6102, 11)/* SampleMask */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {22,IR(0, 0),IR(6113, 10)/* FragDepth */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {23,IR(0, 0),IR(6123, 17)/* HelperInvocation */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {24,IR(0, 0),IR(6140, 14)/* NumWorkgroups */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {25,IR(0, 0),IR(6154, 14)/* WorkgroupSize */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {26,IR(0, 0),IR(6168, 12)/* WorkgroupId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {27,IR(0, 0),IR(6180, 18)/* LocalInvocationId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {28,IR(0, 0),IR(6198, 19)/* GlobalInvocationId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {29,IR(0, 0),IR(6217, 21)/* LocalInvocationIndex */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {30,IR(0, 0),IR(6238, 8)/* WorkDim */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {31,IR(0, 0),IR(6246, 11)/* GlobalSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {32,IR(0, 0),IR(6257, 22)/* EnqueuedWorkgroupSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {33,IR(0, 0),IR(6279, 13)/* GlobalOffset */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {34,IR(0, 0),IR(6292, 15)/* GlobalLinearId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {36,IR(0, 0),IR(6307, 13)/* SubgroupSize */,IR(0, 0),IR(26, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {37,IR(0, 0),IR(6354, 16)/* SubgroupMaxSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {38,IR(0, 0),IR(6370, 13)/* NumSubgroups */,IR(0, 0),IR(29, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {39,IR(0, 0),IR(6383, 21)/* NumEnqueuedSubgroups */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {40,IR(0, 0),IR(6404, 11)/* SubgroupId */,IR(0, 0),IR(29, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {41,IR(0, 0),IR(6415, 26)/* SubgroupLocalInvocationId */,IR(0, 0),IR(26, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {42,IR(0, 0),IR(6441, 12)/* VertexIndex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {43,IR(0, 0),IR(6453, 14)/* InstanceIndex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4160,IR(0, 0),IR(6467, 10)/* CoreIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4161,IR(0, 0),IR(6493, 13)/* CoreCountARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4162,IR(0, 0),IR(6506, 13)/* CoreMaxIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4163,IR(0, 0),IR(6519, 10)/* WarpIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4164,IR(0, 0),IR(6529, 13)/* WarpMaxIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4416,IR(0, 0),IR(6542, 15)/* SubgroupEqMask */,IR(1, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4417,IR(0, 0),IR(6597, 15)/* SubgroupGeMask */,IR(2, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4418,IR(0, 0),IR(6630, 15)/* SubgroupGtMask */,IR(3, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4419,IR(0, 0),IR(6663, 15)/* SubgroupLeMask */,IR(4, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4420,IR(0, 0),IR(6696, 15)/* SubgroupLtMask */,IR(5, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4424,IR(0, 0),IR(6729, 11)/* BaseVertex */,IR(0, 0),IR(34, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4425,IR(0, 0),IR(6755, 13)/* BaseInstance */,IR(0, 0),IR(34, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4426,IR(0, 0),IR(6768, 10)/* DrawIndex */,IR(0, 0),IR(35, 3),IR(4, 3),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4432,IR(0, 0),IR(6778, 24)/* PrimitiveShadingRateKHR */,IR(0, 0),IR(38, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4438,IR(0, 0),IR(6825, 12)/* DeviceIndex */,IR(0, 0),IR(39, 1),IR(8, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4440,IR(0, 0),IR(6849, 10)/* ViewIndex */,IR(0, 0),IR(40, 1),IR(9, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4444,IR(0, 0),IR(6869, 15)/* ShadingRateKHR */,IR(0, 0),IR(38, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4492,IR(0, 0),IR(6884, 15)/* TileOffsetQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4493,IR(0, 0),IR(6915, 18)/* TileDimensionQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4494,IR(0, 0),IR(6933, 18)/* TileApronSizeQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4992,IR(0, 0),IR(6951, 20)/* BaryCoordNoPerspAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4993,IR(0, 0),IR(6971, 28)/* BaryCoordNoPerspCentroidAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4994,IR(0, 0),IR(6999, 26)/* BaryCoordNoPerspSampleAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4995,IR(0, 0),IR(7025, 19)/* BaryCoordSmoothAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4996,IR(0, 0),IR(7044, 27)/* BaryCoordSmoothCentroidAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4997,IR(0, 0),IR(7071, 25)/* BaryCoordSmoothSampleAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4998,IR(0, 0),IR(7096, 22)/* BaryCoordPullModelAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5014,IR(0, 0),IR(7118, 18)/* FragStencilRefEXT */,IR(0, 0),IR(42, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5021,IR(0, 0),IR(7153, 29)/* RemainingRecursionLevelsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5073,IR(0, 0),IR(7200, 16)/* ShaderIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5122,IR(0, 0),IR(7216, 15)/* SamplerHeapEXT */,IR(0, 0),IR(44, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5123,IR(0, 0),IR(7249, 16)/* ResourceHeapEXT */,IR(0, 0),IR(44, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5253,IR(0, 0),IR(7265, 15)/* ViewportMaskNV */,IR(0, 0),IR(45, 2),IR(12, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5257,IR(0, 0),IR(7301, 20)/* SecondaryPositionNV */,IR(0, 0),IR(47, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5258,IR(0, 0),IR(7340, 24)/* SecondaryViewportMaskNV */,IR(0, 0),IR(47, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5261,IR(0, 0),IR(7364, 18)/* PositionPerViewNV */,IR(0, 0),IR(48, 2),IR(15, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5262,IR(0, 0),IR(7402, 22)/* ViewportMaskPerViewNV */,IR(0, 0),IR(48, 2),IR(15, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5264,IR(0, 0),IR(7424, 16)/* FullyCoveredEXT */,IR(0, 0),IR(50, 1),IR(17, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5274,IR(0, 0),IR(7464, 12)/* TaskCountNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5275,IR(0, 0),IR(7476, 17)/* PrimitiveCountNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5276,IR(0, 0),IR(7493, 19)/* PrimitiveIndicesNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5277,IR(0, 0),IR(7512, 22)/* ClipDistancePerViewNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5278,IR(0, 0),IR(7534, 22)/* CullDistancePerViewNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5279,IR(0, 0),IR(7556, 15)/* LayerPerViewNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5280,IR(0, 0),IR(7571, 16)/* MeshViewCountNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5281,IR(0, 0),IR(7587, 18)/* MeshViewIndicesNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5286,IR(0, 0),IR(7605, 13)/* BaryCoordKHR */,IR(6, 1),IR(52, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5287,IR(0, 0),IR(7653, 20)/* BaryCoordNoPerspKHR */,IR(7, 1),IR(52, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5292,IR(0, 0),IR(7692, 12)/* FragSizeEXT */,IR(8, 1),IR(53, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5293,IR(0, 0),IR(7738, 23)/* FragInvocationCountEXT */,IR(9, 1),IR(53, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5294,IR(0, 0),IR(7783, 25)/* PrimitivePointIndicesEXT */,IR(0, 0),IR(54, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5295,IR(0, 0),IR(7808, 24)/* PrimitiveLineIndicesEXT */,IR(0, 0),IR(54, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5296,IR(0, 0),IR(7832, 28)/* PrimitiveTriangleIndicesEXT */,IR(0, 0),IR(54, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5299,IR(0, 0),IR(7860, 17)/* CullPrimitiveEXT */,IR(0, 0),IR(54, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5319,IR(0, 0),IR(7877, 12)/* LaunchIdKHR */,IR(10, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5320,IR(0, 0),IR(7900, 14)/* LaunchSizeKHR */,IR(11, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5321,IR(0, 0),IR(7927, 18)/* WorldRayOriginKHR */,IR(12, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5322,IR(0, 0),IR(7962, 21)/* WorldRayDirectionKHR */,IR(13, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5323,IR(0, 0),IR(8003, 19)/* ObjectRayOriginKHR */,IR(14, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5324,IR(0, 0),IR(8040, 22)/* ObjectRayDirectionKHR */,IR(15, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5325,IR(0, 0),IR(8083, 11)/* RayTminKHR */,IR(16, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5326,IR(0, 0),IR(8104, 11)/* RayTmaxKHR */,IR(17, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5327,IR(0, 0),IR(8125, 23)/* InstanceCustomIndexKHR */,IR(18, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5330,IR(0, 0),IR(8170, 17)/* ObjectToWorldKHR */,IR(19, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5331,IR(0, 0),IR(8203, 17)/* WorldToObjectKHR */,IR(20, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5332,IR(0, 0),IR(8236, 7)/* HitTNV */,IR(0, 0),IR(57, 1),IR(26, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5333,IR(0, 0),IR(8243, 11)/* HitKindKHR */,IR(21, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5334,IR(0, 0),IR(8264, 17)/* CurrentRayTimeNV */,IR(0, 0),IR(58, 1),IR(27, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5335,IR(0, 0),IR(8304, 30)/* HitTriangleVertexPositionsKHR */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5337,IR(0, 0),IR(8361, 34)/* HitMicroTriangleVertexPositionsNV */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5344,IR(0, 0),IR(8428, 37)/* HitMicroTriangleVertexBarycentricsNV */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5351,IR(0, 0),IR(8465, 20)/* IncomingRayFlagsKHR */,IR(22, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5352,IR(0, 0),IR(8504, 20)/* RayGeometryIndexKHR */,IR(0, 0),IR(61, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5359,IR(0, 0),IR(8524, 14)/* HitIsSphereNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5360,IR(0, 0),IR(8566, 11)/* HitIsLSSNV */,IR(0, 0),IR(63, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5361,IR(0, 0),IR(8616, 20)/* HitSpherePositionNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5374,IR(0, 0),IR(8636, 13)/* WarpsPerSMNV */,IR(0, 0),IR(64, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5375,IR(0, 0),IR(8668, 10)/* SMCountNV */,IR(0, 0),IR(64, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5376,IR(0, 0),IR(8678, 9)/* WarpIDNV */,IR(0, 0),IR(64, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5377,IR(0, 0),IR(8687, 7)/* SMIDNV */,IR(0, 0),IR(64, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5396,IR(0, 0),IR(8694, 18)/* HitLSSPositionsNV */,IR(0, 0),IR(63, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5405,IR(0, 0),IR(8712, 34)/* HitKindFrontFacingMicroTriangleNV */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5406,IR(0, 0),IR(8746, 33)/* HitKindBackFacingMicroTriangleNV */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5420,IR(0, 0),IR(8779, 18)/* HitSphereRadiusNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5421,IR(0, 0),IR(8797, 14)/* HitLSSRadiiNV */,IR(0, 0),IR(63, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5436,IR(0, 0),IR(8811, 12)/* ClusterIDNV */,IR(0, 0),IR(65, 1),IR(31, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {6021,IR(0, 0),IR(8864, 12)/* CullMaskKHR */,IR(0, 0),IR(66, 1),IR(32, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {0,IR(0, 0),IR(8891, 7)/* Matrix */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {1,IR(0, 0),IR(5713, 7)/* Shader */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {2,IR(0, 0),IR(5788, 9)/* Geometry */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {3,IR(0, 0),IR(5797, 13)/* Tessellation */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4,IR(0, 0),IR(5601, 10)/* Addresses */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5,IR(0, 0),IR(8898, 8)/* Linkage */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6,IR(0, 0),IR(5555, 7)/* Kernel */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {7,IR(0, 0),IR(8906, 9)/* Vector16 */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {8,IR(0, 0),IR(8915, 14)/* Float16Buffer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {9,IR(0, 0),IR(8929, 8)/* Float16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {10,IR(0, 0),IR(8937, 8)/* Float64 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {11,IR(0, 0),IR(8945, 6)/* Int64 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {12,IR(0, 0),IR(8951, 13)/* Int64Atomics */,IR(0, 0),IR(68, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {13,IR(0, 0),IR(8964, 11)/* ImageBasic */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {14,IR(0, 0),IR(8975, 15)/* ImageReadWrite */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {15,IR(0, 0),IR(8990, 12)/* ImageMipmap */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {17,IR(0, 0),IR(9002, 6)/* Pipes */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {18,IR(0, 0),IR(9008, 7)/* Groups */,IR(0, 0),IR(1, 0),IR(33, 1),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {19,IR(0, 0),IR(9015, 14)/* DeviceEnqueue */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {20,IR(0, 0),IR(9029, 15)/* LiteralSampler */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {21,IR(0, 0),IR(9044, 14)/* AtomicStorage */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {22,IR(0, 0),IR(9058, 6)/* Int16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {23,IR(0, 0),IR(9064, 22)/* TessellationPointSize */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {24,IR(0, 0),IR(9086, 18)/* GeometryPointSize */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {25,IR(0, 0),IR(9104, 20)/* ImageGatherExtended */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {27,IR(0, 0),IR(9124, 24)/* StorageImageMultisample */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {28,IR(0, 0),IR(9148, 34)/* UniformBufferArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {29,IR(0, 0),IR(9182, 33)/* SampledImageArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {30,IR(0, 0),IR(9215, 34)/* StorageBufferArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {31,IR(0, 0),IR(9249, 33)/* StorageImageArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {32,IR(0, 0),IR(5730, 13)/* ClipDistance */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {33,IR(0, 0),IR(5743, 13)/* CullDistance */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {34,IR(0, 0),IR(9282, 15)/* ImageCubeArray */,IR(0, 0),IR(71, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {35,IR(0, 0),IR(6069, 18)/* SampleRateShading */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {36,IR(0, 0),IR(9314, 10)/* ImageRect */,IR(0, 0),IR(72, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {37,IR(0, 0),IR(9324, 12)/* SampledRect */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {38,IR(0, 0),IR(9336, 15)/* GenericPointer */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {39,IR(0, 0),IR(9351, 5)/* Int8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {40,IR(0, 0),IR(9356, 16)/* InputAttachment */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {41,IR(0, 0),IR(9372, 16)/* SparseResidency */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {42,IR(0, 0),IR(9388, 7)/* MinLod */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {43,IR(0, 0),IR(9395, 10)/* Sampled1D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {44,IR(0, 0),IR(9405, 8)/* Image1D */,IR(0, 0),IR(73, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {45,IR(0, 0),IR(9297, 17)/* SampledCubeArray */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {46,IR(0, 0),IR(9413, 14)/* SampledBuffer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {47,IR(0, 0),IR(9427, 12)/* ImageBuffer */,IR(0, 0),IR(74, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {48,IR(0, 0),IR(9439, 13)/* ImageMSArray */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {49,IR(0, 0),IR(9452, 28)/* StorageImageExtendedFormats */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {50,IR(0, 0),IR(9480, 11)/* ImageQuery */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {51,IR(0, 0),IR(9491, 18)/* DerivativeControl */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {52,IR(0, 0),IR(9509, 22)/* InterpolationFunction */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {53,IR(0, 0),IR(9531, 18)/* TransformFeedback */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {54,IR(0, 0),IR(9549, 16)/* GeometryStreams */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {55,IR(0, 0),IR(9565, 30)/* StorageImageReadWithoutFormat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {56,IR(0, 0),IR(9595, 31)/* StorageImageWriteWithoutFormat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {57,IR(0, 0),IR(5939, 14)/* MultiViewport */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {58,IR(0, 0),IR(9626, 17)/* SubgroupDispatch */,IR(0, 0),IR(75, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {59,IR(0, 0),IR(9643, 13)/* NamedBarrier */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {60,IR(0, 0),IR(9656, 12)/* PipeStorage */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {61,IR(0, 0),IR(6320, 16)/* GroupNonUniform */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {62,IR(0, 0),IR(9668, 20)/* GroupNonUniformVote */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {63,IR(0, 0),IR(9688, 26)/* GroupNonUniformArithmetic */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {64,IR(0, 0),IR(6575, 22)/* GroupNonUniformBallot */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {65,IR(0, 0),IR(9714, 23)/* GroupNonUniformShuffle */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {66,IR(0, 0),IR(9737, 31)/* GroupNonUniformShuffleRelative */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {67,IR(0, 0),IR(9768, 25)/* GroupNonUniformClustered */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {68,IR(0, 0),IR(9793, 20)/* GroupNonUniformQuad */,IR(0, 0),IR(77, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {69,IR(0, 0),IR(5885, 12)/* ShaderLayer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {70,IR(0, 0),IR(5953, 20)/* ShaderViewportIndex */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {71,IR(0, 0),IR(9813, 18)/* UniformDecoration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4165,IR(0, 0),IR(6477, 16)/* CoreBuiltinsARM */,IR(0, 0),IR(1, 0),IR(34, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4166,IR(0, 0),IR(9831, 28)/* TileImageColorReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4167,IR(0, 0),IR(9859, 28)/* TileImageDepthReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4168,IR(0, 0),IR(9887, 30)/* TileImageStencilReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4174,IR(0, 0),IR(9917, 11)/* TensorsARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4175,IR(0, 0),IR(9928, 37)/* StorageTensorArrayDynamicIndexingARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4176,IR(0, 0),IR(9965, 40)/* StorageTensorArrayNonUniformIndexingARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4191,IR(0, 0),IR(10005, 9)/* GraphARM */,IR(0, 0),IR(1, 0),IR(37, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4201,IR(0, 0),IR(10014, 28)/* CooperativeMatrixLayoutsARM */,IR(0, 0),IR(1, 0),IR(38, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4212,IR(0, 0),IR(10042, 10)/* Float8EXT */,IR(0, 0),IR(1, 0),IR(39, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4213,IR(0, 0),IR(10052, 27)/* Float8CooperativeMatrixEXT */,IR(0, 0),IR(78, 2),IR(39, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4422,IR(0, 0),IR(6802, 23)/* FragmentShadingRateKHR */,IR(0, 0),IR(3, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4423,IR(0, 0),IR(6336, 18)/* SubgroupBallotKHR */,IR(0, 0),IR(1, 0),IR(2, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4427,IR(0, 0),IR(6740, 15)/* DrawParameters */,IR(0, 0),IR(3, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4428,IR(0, 0),IR(10100, 33)/* WorkgroupMemoryExplicitLayoutKHR */,IR(0, 0),IR(3, 1),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4429,IR(0, 0),IR(10133, 43)/* WorkgroupMemoryExplicitLayout8BitAccessKHR */,IR(0, 0),IR(80, 1),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4430,IR(0, 0),IR(10176, 44)/* WorkgroupMemoryExplicitLayout16BitAccessKHR */,IR(0, 0),IR(80, 1),IR(40, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4431,IR(0, 0),IR(10220, 16)/* SubgroupVoteKHR */,IR(0, 0),IR(1, 0),IR(41, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4433,IR(0, 0),IR(10236, 25)/* StorageBuffer16BitAccess */,IR(23, 1),IR(1, 0),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4434,IR(0, 0),IR(10289, 35)/* UniformAndStorageBuffer16BitAccess */,IR(24, 1),IR(81, 1),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4435,IR(0, 0),IR(10341, 22)/* StoragePushConstant16 */,IR(0, 0),IR(1, 0),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4436,IR(0, 0),IR(10363, 21)/* StorageInputOutput16 */,IR(0, 0),IR(1, 0),IR(42, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4437,IR(0, 0),IR(6837, 12)/* DeviceGroup */,IR(0, 0),IR(1, 0),IR(8, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4439,IR(0, 0),IR(6859, 10)/* MultiView */,IR(0, 0),IR(3, 1),IR(9, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4441,IR(0, 0),IR(10384, 30)/* VariablePointersStorageBuffer */,IR(0, 0),IR(3, 1),IR(43, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4442,IR(0, 0),IR(10414, 17)/* VariablePointers */,IR(0, 0),IR(82, 1),IR(43, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4445,IR(0, 0),IR(10431, 17)/* AtomicStorageOps */,IR(0, 0),IR(83, 1),IR(44, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4447,IR(0, 0),IR(10448, 28)/* SampleMaskPostDepthCoverage */,IR(0, 0),IR(1, 0),IR(45, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4448,IR(0, 0),IR(10476, 24)/* StorageBuffer8BitAccess */,IR(0, 0),IR(1, 0),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4449,IR(0, 0),IR(10500, 34)/* UniformAndStorageBuffer8BitAccess */,IR(0, 0),IR(84, 1),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4450,IR(0, 0),IR(10534, 21)/* StoragePushConstant8 */,IR(0, 0),IR(1, 0),IR(46, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4464,IR(0, 0),IR(10555, 15)/* DenormPreserve */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4465,IR(0, 0),IR(10570, 18)/* DenormFlushToZero */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4466,IR(0, 0),IR(10588, 25)/* SignedZeroInfNanPreserve */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4467,IR(0, 0),IR(10613, 16)/* RoundingModeRTE */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4468,IR(0, 0),IR(10629, 16)/* RoundingModeRTZ */,IR(0, 0),IR(1, 0),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4471,IR(0, 0),IR(10645, 23)/* RayQueryProvisionalKHR */,IR(0, 0),IR(3, 1),IR(48, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4472,IR(0, 0),IR(10668, 12)/* RayQueryKHR */,IR(0, 0),IR(3, 1),IR(48, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4473,IR(0, 0),IR(10680, 19)/* UntypedPointersKHR */,IR(0, 0),IR(1, 0),IR(49, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4478,IR(0, 0),IR(10699, 32)/* RayTraversalPrimitiveCullingKHR */,IR(0, 0),IR(85, 2),IR(50, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4479,IR(0, 0),IR(5823, 14)/* RayTracingKHR */,IR(0, 0),IR(3, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4484,IR(0, 0),IR(10731, 26)/* TextureSampleWeightedQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4485,IR(0, 0),IR(10757, 21)/* TextureBoxFilterQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4486,IR(0, 0),IR(10778, 22)/* TextureBlockMatchQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4495,IR(0, 0),IR(6899, 16)/* TileShadingQCOM */,IR(0, 0),IR(3, 1),IR(53, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4496,IR(0, 0),IR(10800, 32)/* CooperativeMatrixConversionQCOM */,IR(0, 0),IR(87, 1),IR(54, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4498,IR(0, 0),IR(10832, 23)/* TextureBlockMatch2QCOM */,IR(0, 0),IR(1, 0),IR(55, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5008,IR(0, 0),IR(10855, 16)/* Float16ImageAMD */,IR(0, 0),IR(3, 1),IR(56, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5009,IR(0, 0),IR(10871, 22)/* ImageGatherBiasLodAMD */,IR(0, 0),IR(3, 1),IR(57, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5010,IR(0, 0),IR(10893, 16)/* FragmentMaskAMD */,IR(0, 0),IR(3, 1),IR(58, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5013,IR(0, 0),IR(7136, 17)/* StencilExportEXT */,IR(0, 0),IR(3, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5015,IR(0, 0),IR(10909, 21)/* ImageReadWriteLodAMD */,IR(0, 0),IR(3, 1),IR(59, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5016,IR(0, 0),IR(10930, 14)/* Int64ImageEXT */,IR(0, 0),IR(3, 1),IR(60, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5055,IR(0, 0),IR(10944, 15)/* ShaderClockKHR */,IR(0, 0),IR(1, 0),IR(61, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5067,IR(0, 0),IR(7182, 18)/* ShaderEnqueueAMDX */,IR(0, 0),IR(3, 1),IR(62, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5087,IR(0, 0),IR(10959, 15)/* QuadControlKHR */,IR(0, 0),IR(1, 0),IR(63, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5112,IR(0, 0),IR(10974, 14)/* Int4TypeINTEL */,IR(0, 0),IR(1, 0),IR(64, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5114,IR(0, 0),IR(10988, 27)/* Int4CooperativeMatrixINTEL */,IR(0, 0),IR(88, 2),IR(64, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5116,IR(0, 0),IR(11015, 16)/* BFloat16TypeKHR */,IR(0, 0),IR(1, 0),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5117,IR(0, 0),IR(11031, 22)/* BFloat16DotProductKHR */,IR(0, 0),IR(90, 1),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5118,IR(0, 0),IR(11053, 29)/* BFloat16CooperativeMatrixKHR */,IR(0, 0),IR(91, 2),IR(65, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5120,IR(0, 0),IR(11082, 9)/* AbortKHR */,IR(0, 0),IR(1, 0),IR(66, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5128,IR(0, 0),IR(7231, 18)/* DescriptorHeapEXT */,IR(0, 0),IR(93, 1),IR(67, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5146,IR(0, 0),IR(11091, 16)/* ConstantDataKHR */,IR(0, 0),IR(1, 0),IR(68, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5156,IR(0, 0),IR(11107, 16)/* PoisonFreezeKHR */,IR(0, 0),IR(1, 0),IR(69, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5249,IR(0, 0),IR(11123, 29)/* SampleMaskOverrideCoverageNV */,IR(0, 0),IR(25, 1),IR(70, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5251,IR(0, 0),IR(11152, 28)/* GeometryShaderPassthroughNV */,IR(0, 0),IR(70, 1),IR(71, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5254,IR(0, 0),IR(5897, 28)/* ShaderViewportIndexLayerEXT */,IR(25, 1),IR(94, 1),IR(72, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5255,IR(0, 0),IR(7280, 21)/* ShaderViewportMaskNV */,IR(0, 0),IR(95, 1),IR(74, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5259,IR(0, 0),IR(7321, 19)/* ShaderStereoViewNV */,IR(0, 0),IR(96, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5260,IR(0, 0),IR(7382, 20)/* PerViewAttributesNV */,IR(0, 0),IR(40, 1),IR(75, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5265,IR(0, 0),IR(7440, 24)/* FragmentFullyCoveredEXT */,IR(0, 0),IR(3, 1),IR(17, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5266,IR(0, 0),IR(5837, 14)/* MeshShadingNV */,IR(0, 0),IR(3, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5282,IR(0, 0),IR(11207, 17)/* ImageFootprintNV */,IR(0, 0),IR(1, 0),IR(76, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5283,IR(0, 0),IR(5851, 15)/* MeshShadingEXT */,IR(0, 0),IR(3, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5284,IR(0, 0),IR(7630, 23)/* FragmentBarycentricKHR */,IR(26, 1),IR(1, 0),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5288,IR(0, 0),IR(11246, 31)/* ComputeDerivativeGroupQuadsKHR */,IR(27, 1),IR(3, 1),IR(77, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5291,IR(0, 0),IR(7719, 19)/* FragmentDensityEXT */,IR(28, 1),IR(3, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5297,IR(0, 0),IR(11321, 30)/* GroupNonUniformPartitionedEXT */,IR(29, 1),IR(1, 0),IR(79, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5301,IR(0, 0),IR(11380, 17)/* ShaderNonUniform */,IR(30, 1),IR(3, 1),IR(81, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5302,IR(0, 0),IR(11417, 23)/* RuntimeDescriptorArray */,IR(31, 1),IR(3, 1),IR(81, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5303,IR(0, 0),IR(11466, 36)/* InputAttachmentArrayDynamicIndexing */,IR(32, 1),IR(97, 1),IR(81, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5304,IR(0, 0),IR(11541, 39)/* UniformTexelBufferArrayDynamicIndexing */,IR(33, 1),IR(74, 1),IR(81, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5305,IR(0, 0),IR(11622, 39)/* StorageTexelBufferArrayDynamicIndexing */,IR(34, 1),IR(98, 1),IR(81, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5306,IR(0, 0),IR(11703, 37)/* UniformBufferArrayNonUniformIndexing */,IR(35, 1),IR(99, 1),IR(81, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5307,IR(0, 0),IR(11780, 36)/* SampledImageArrayNonUniformIndexing */,IR(36, 1),IR(99, 1),IR(81, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5308,IR(0, 0),IR(11855, 37)/* StorageBufferArrayNonUniformIndexing */,IR(37, 1),IR(99, 1),IR(81, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5309,IR(0, 0),IR(11932, 36)/* StorageImageArrayNonUniformIndexing */,IR(38, 1),IR(99, 1),IR(81, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5310,IR(0, 0),IR(12007, 39)/* InputAttachmentArrayNonUniformIndexing */,IR(39, 1),IR(100, 2),IR(81, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5311,IR(0, 0),IR(12088, 42)/* UniformTexelBufferArrayNonUniformIndexing */,IR(40, 1),IR(102, 2),IR(81, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5312,IR(0, 0),IR(12175, 42)/* StorageTexelBufferArrayNonUniformIndexing */,IR(41, 1),IR(104, 2),IR(81, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5336,IR(0, 0),IR(8334, 27)/* RayTracingPositionFetchKHR */,IR(0, 0),IR(3, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5340,IR(0, 0),IR(5810, 13)/* RayTracingNV */,IR(0, 0),IR(3, 1),IR(26, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5341,IR(0, 0),IR(8281, 23)/* RayTracingMotionBlurNV */,IR(0, 0),IR(3, 1),IR(27, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5345,IR(0, 0),IR(12262, 18)/* VulkanMemoryModel */,IR(42, 1),IR(1, 0),IR(83, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5346,IR(0, 0),IR(12301, 29)/* VulkanMemoryModelDeviceScope */,IR(43, 1),IR(1, 0),IR(83, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5347,IR(0, 0),IR(5673, 31)/* PhysicalStorageBufferAddresses */,IR(44, 1),IR(3, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5350,IR(0, 0),IR(12396, 32)/* ComputeDerivativeGroupLinearKHR */,IR(45, 1),IR(3, 1),IR(77, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5353,IR(0, 0),IR(12459, 25)/* RayTracingProvisionalKHR */,IR(0, 0),IR(3, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5357,IR(0, 0),IR(12484, 20)/* CooperativeMatrixNV */,IR(0, 0),IR(3, 1),IR(84, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5363,IR(0, 0),IR(12504, 33)/* FragmentShaderSampleInterlockEXT */,IR(0, 0),IR(3, 1),IR(85, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5372,IR(0, 0),IR(12537, 38)/* FragmentShaderShadingRateInterlockEXT */,IR(0, 0),IR(3, 1),IR(85, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5373,IR(0, 0),IR(8649, 19)/* ShaderSMBuiltinsNV */,IR(0, 0),IR(3, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5378,IR(0, 0),IR(12575, 32)/* FragmentShaderPixelInterlockEXT */,IR(0, 0),IR(3, 1),IR(85, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5379,IR(0, 0),IR(12607, 25)/* DemoteToHelperInvocation */,IR(46, 1),IR(3, 1),IR(86, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5380,IR(0, 0),IR(12660, 23)/* DisplacementMicromapNV */,IR(0, 0),IR(3, 1),IR(87, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5381,IR(0, 0),IR(12683, 29)/* RayTracingOpacityMicromapEXT */,IR(0, 0),IR(3, 1),IR(88, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5383,IR(0, 0),IR(12712, 26)/* ShaderInvocationReorderNV */,IR(0, 0),IR(61, 1),IR(89, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5388,IR(0, 0),IR(12738, 27)/* ShaderInvocationReorderEXT */,IR(0, 0),IR(61, 1),IR(90, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5390,IR(0, 0),IR(12765, 18)/* BindlessTextureNV */,IR(0, 0),IR(1, 0),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5391,IR(0, 0),IR(12783, 25)/* RayQueryPositionFetchKHR */,IR(0, 0),IR(3, 1),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5394,IR(0, 0),IR(12808, 20)/* CooperativeVectorNV */,IR(0, 0),IR(1, 0),IR(92, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5404,IR(0, 0),IR(12828, 22)/* AtomicFloat16VectorNV */,IR(0, 0),IR(1, 0),IR(93, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5409,IR(0, 0),IR(8395, 33)/* RayTracingDisplacementMicromapNV */,IR(0, 0),IR(61, 1),IR(87, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5414,IR(0, 0),IR(12850, 18)/* RawAccessChainsNV */,IR(0, 0),IR(1, 0),IR(94, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5418,IR(0, 0),IR(8538, 28)/* RayTracingSpheresGeometryNV */,IR(0, 0),IR(1, 0),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5419,IR(0, 0),IR(8577, 39)/* RayTracingLinearSweptSpheresGeometryNV */,IR(0, 0),IR(1, 0),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5423,IR(0, 0),IR(12868, 20)/* PushConstantBanksNV */,IR(0, 0),IR(3, 1),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5425,IR(0, 0),IR(12888, 14)/* LongVectorEXT */,IR(0, 0),IR(1, 0),IR(96, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5426,IR(0, 0),IR(12902, 23)/* Shader64BitIndexingEXT */,IR(0, 0),IR(1, 0),IR(97, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5430,IR(0, 0),IR(12925, 30)/* CooperativeMatrixReductionsNV */,IR(0, 0),IR(1, 0),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5431,IR(0, 0),IR(12955, 31)/* CooperativeMatrixConversionsNV */,IR(0, 0),IR(1, 0),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5432,IR(0, 0),IR(12986, 40)/* CooperativeMatrixPerElementOperationsNV */,IR(0, 0),IR(1, 0),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5433,IR(0, 0),IR(13026, 36)/* CooperativeMatrixTensorAddressingNV */,IR(0, 0),IR(1, 0),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5434,IR(0, 0),IR(13062, 30)/* CooperativeMatrixBlockLoadsNV */,IR(0, 0),IR(1, 0),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5435,IR(0, 0),IR(13092, 28)/* CooperativeVectorTrainingNV */,IR(0, 0),IR(1, 0),IR(92, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5437,IR(0, 0),IR(8823, 41)/* RayTracingClusterAccelerationStructureNV */,IR(0, 0),IR(61, 1),IR(31, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5439,IR(0, 0),IR(13120, 19)/* TensorAddressingNV */,IR(0, 0),IR(1, 0),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5568,IR(0, 0),IR(13139, 21)/* SubgroupShuffleINTEL */,IR(0, 0),IR(1, 0),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5569,IR(0, 0),IR(13160, 27)/* SubgroupBufferBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5570,IR(0, 0),IR(13187, 26)/* SubgroupImageBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5579,IR(0, 0),IR(13213, 31)/* SubgroupImageMediaBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(101, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5582,IR(0, 0),IR(13244, 21)/* RoundToInfinityINTEL */,IR(0, 0),IR(1, 0),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5583,IR(0, 0),IR(13265, 23)/* FloatingPointModeINTEL */,IR(0, 0),IR(1, 0),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5584,IR(0, 0),IR(13288, 23)/* IntegerFunctions2INTEL */,IR(0, 0),IR(1, 0),IR(103, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5603,IR(0, 0),IR(13311, 22)/* FunctionPointersINTEL */,IR(0, 0),IR(1, 0),IR(104, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5604,IR(0, 0),IR(13333, 24)/* IndirectReferencesINTEL */,IR(0, 0),IR(1, 0),IR(104, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5606,IR(0, 0),IR(13357, 9)/* AsmINTEL */,IR(0, 0),IR(1, 0),IR(105, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5612,IR(0, 0),IR(13366, 23)/* AtomicFloat32MinMaxEXT */,IR(0, 0),IR(1, 0),IR(106, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5613,IR(0, 0),IR(13389, 23)/* AtomicFloat64MinMaxEXT */,IR(0, 0),IR(1, 0),IR(106, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5616,IR(0, 0),IR(13412, 23)/* AtomicFloat16MinMaxEXT */,IR(0, 0),IR(1, 0),IR(106, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5617,IR(0, 0),IR(13435, 19)/* VectorComputeINTEL */,IR(0, 0),IR(106, 1),IR(107, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5619,IR(0, 0),IR(13454, 15)/* VectorAnyINTEL */,IR(0, 0),IR(1, 0),IR(107, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5629,IR(0, 0),IR(13469, 16)/* ExpectAssumeKHR */,IR(0, 0),IR(1, 0),IR(108, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5696,IR(0, 0),IR(13485, 33)/* SubgroupAvcMotionEstimationINTEL */,IR(0, 0),IR(1, 0),IR(109, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5697,IR(0, 0),IR(13518, 38)/* SubgroupAvcMotionEstimationIntraINTEL */,IR(0, 0),IR(1, 0),IR(109, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5698,IR(0, 0),IR(13556, 39)/* SubgroupAvcMotionEstimationChromaINTEL */,IR(0, 0),IR(1, 0),IR(109, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5817,IR(0, 0),IR(13595, 25)/* VariableLengthArrayINTEL */,IR(0, 0),IR(1, 0),IR(110, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5821,IR(0, 0),IR(13620, 26)/* FunctionFloatControlINTEL */,IR(0, 0),IR(1, 0),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5824,IR(0, 0),IR(13646, 27)/* FPGAMemoryAttributesALTERA */,IR(47, 1),IR(1, 0),IR(111, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5837,IR(0, 0),IR(13699, 20)/* FPFastMathModeINTEL */,IR(0, 0),IR(0, 1),IR(113, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5844,IR(0, 0),IR(13719, 33)/* ArbitraryPrecisionIntegersALTERA */,IR(48, 1),IR(1, 0),IR(114, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5845,IR(0, 0),IR(13784, 38)/* ArbitraryPrecisionFloatingPointALTERA */,IR(49, 1),IR(1, 0),IR(116, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5886,IR(0, 0),IR(13859, 30)/* UnstructuredLoopControlsINTEL */,IR(0, 0),IR(1, 0),IR(118, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5888,IR(0, 0),IR(13889, 23)/* FPGALoopControlsALTERA */,IR(50, 1),IR(1, 0),IR(119, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5892,IR(0, 0),IR(13934, 22)/* KernelAttributesINTEL */,IR(0, 0),IR(1, 0),IR(121, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5897,IR(0, 0),IR(13956, 26)/* FPGAKernelAttributesINTEL */,IR(0, 0),IR(1, 0),IR(121, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5898,IR(0, 0),IR(13982, 25)/* FPGAMemoryAccessesALTERA */,IR(51, 1),IR(1, 0),IR(122, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5904,IR(0, 0),IR(14031, 28)/* FPGAClusterAttributesALTERA */,IR(52, 1),IR(1, 0),IR(124, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5906,IR(0, 0),IR(14086, 15)/* LoopFuseALTERA */,IR(53, 1),IR(1, 0),IR(126, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5908,IR(0, 0),IR(14115, 21)/* FPGADSPControlALTERA */,IR(54, 1),IR(1, 0),IR(128, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5910,IR(0, 0),IR(14156, 26)/* MemoryAccessAliasingINTEL */,IR(0, 0),IR(1, 0),IR(130, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5916,IR(0, 0),IR(14182, 41)/* FPGAInvocationPipeliningAttributesALTERA */,IR(55, 1),IR(1, 0),IR(131, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5920,IR(0, 0),IR(14263, 25)/* FPGABufferLocationALTERA */,IR(56, 1),IR(1, 0),IR(133, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5922,IR(0, 0),IR(14312, 35)/* ArbitraryPrecisionFixedPointALTERA */,IR(57, 1),IR(1, 0),IR(135, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5935,IR(0, 0),IR(14381, 24)/* USMStorageClassesALTERA */,IR(58, 1),IR(1, 0),IR(137, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5939,IR(0, 0),IR(14428, 30)/* RuntimeAlignedAttributeALTERA */,IR(59, 1),IR(1, 0),IR(139, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5943,IR(0, 0),IR(14487, 14)/* IOPipesALTERA */,IR(60, 1),IR(1, 0),IR(141, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5945,IR(0, 0),IR(14514, 20)/* BlockingPipesALTERA */,IR(61, 1),IR(1, 0),IR(143, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5948,IR(0, 0),IR(14553, 14)/* FPGARegALTERA */,IR(62, 1),IR(1, 0),IR(145, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6016,IR(0, 0),IR(14580, 19)/* DotProductInputAll */,IR(63, 1),IR(1, 0),IR(147, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6017,IR(0, 0),IR(14621, 22)/* DotProductInput4x8Bit */,IR(64, 1),IR(107, 1),IR(147, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6018,IR(0, 0),IR(14668, 28)/* DotProductInput4x8BitPacked */,IR(65, 1),IR(1, 0),IR(147, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6019,IR(0, 0),IR(14727, 11)/* DotProduct */,IR(66, 1),IR(1, 0),IR(147, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6020,IR(0, 0),IR(8876, 15)/* RayCullMaskKHR */,IR(0, 0),IR(1, 0),IR(32, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6022,IR(0, 0),IR(10079, 21)/* CooperativeMatrixKHR */,IR(0, 0),IR(1, 0),IR(148, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6024,IR(0, 0),IR(14752, 24)/* ReplicatedCompositesEXT */,IR(0, 0),IR(1, 0),IR(149, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6025,IR(0, 0),IR(14776, 16)/* BitInstructions */,IR(0, 0),IR(1, 0),IR(150, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6026,IR(0, 0),IR(14792, 25)/* GroupNonUniformRotateKHR */,IR(0, 0),IR(77, 1),IR(151, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6029,IR(0, 0),IR(14817, 15)/* FloatControls2 */,IR(0, 0),IR(1, 0),IR(152, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6030,IR(0, 0),IR(14832, 7)/* FMAKHR */,IR(0, 0),IR(1, 0),IR(153, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6033,IR(0, 0),IR(14839, 20)/* AtomicFloat32AddEXT */,IR(0, 0),IR(1, 0),IR(154, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6034,IR(0, 0),IR(14859, 20)/* AtomicFloat64AddEXT */,IR(0, 0),IR(1, 0),IR(154, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6089,IR(0, 0),IR(14879, 20)/* LongCompositesINTEL */,IR(0, 0),IR(1, 0),IR(155, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6094,IR(0, 0),IR(14899, 11)/* OptNoneEXT */,IR(67, 1),IR(1, 0),IR(156, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6095,IR(0, 0),IR(14923, 20)/* AtomicFloat16AddEXT */,IR(0, 0),IR(1, 0),IR(158, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6114,IR(0, 0),IR(14943, 21)/* DebugInfoModuleINTEL */,IR(0, 0),IR(1, 0),IR(159, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6115,IR(0, 0),IR(14964, 24)/* BFloat16ConversionINTEL */,IR(0, 0),IR(1, 0),IR(160, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6141,IR(0, 0),IR(14988, 18)/* SplitBarrierINTEL */,IR(0, 0),IR(1, 0),IR(161, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6144,IR(0, 0),IR(15006, 19)/* ArithmeticFenceEXT */,IR(0, 0),IR(1, 0),IR(162, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6150,IR(0, 0),IR(15025, 30)/* FPGAClusterAttributesV2ALTERA */,IR(68, 1),IR(108, 1),IR(124, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6161,IR(0, 0),IR(15084, 28)/* FPGAKernelAttributesv2INTEL */,IR(0, 0),IR(109, 1),IR(121, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6162,IR(0, 0),IR(15112, 19)/* TaskSequenceALTERA */,IR(69, 1),IR(1, 0),IR(163, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6169,IR(0, 0),IR(15149, 16)/* FPMaxErrorINTEL */,IR(0, 0),IR(1, 0),IR(165, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6171,IR(0, 0),IR(15165, 25)/* FPGALatencyControlALTERA */,IR(70, 1),IR(1, 0),IR(166, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6174,IR(0, 0),IR(15214, 29)/* FPGAArgumentInterfacesALTERA */,IR(71, 1),IR(1, 0),IR(168, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6187,IR(0, 0),IR(15271, 30)/* GlobalVariableHostAccessINTEL */,IR(0, 0),IR(1, 0),IR(170, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6189,IR(0, 0),IR(15301, 36)/* GlobalVariableFPGADecorationsALTERA */,IR(72, 1),IR(1, 0),IR(171, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6220,IR(0, 0),IR(15372, 28)/* SubgroupBufferPrefetchINTEL */,IR(0, 0),IR(1, 0),IR(173, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6228,IR(0, 0),IR(15400, 23)/* Subgroup2DBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(174, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6229,IR(0, 0),IR(15423, 30)/* Subgroup2DBlockTransformINTEL */,IR(0, 0),IR(110, 1),IR(174, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6230,IR(0, 0),IR(15453, 30)/* Subgroup2DBlockTransposeINTEL */,IR(0, 0),IR(110, 1),IR(174, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6236,IR(0, 0),IR(15483, 38)/* SubgroupMatrixMultiplyAccumulateINTEL */,IR(0, 0),IR(1, 0),IR(175, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6241,IR(0, 0),IR(15521, 28)/* TernaryBitwiseFunctionINTEL */,IR(0, 0),IR(1, 0),IR(176, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6243,IR(0, 0),IR(15549, 32)/* UntypedVariableLengthArrayINTEL */,IR(0, 0),IR(111, 2),IR(110, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6245,IR(0, 0),IR(15581, 21)/* SpecConditionalINTEL */,IR(0, 0),IR(1, 0),IR(177, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6246,IR(0, 0),IR(15602, 22)/* FunctionVariantsINTEL */,IR(0, 0),IR(113, 1),IR(177, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6400,IR(0, 0),IR(15624, 26)/* GroupUniformArithmeticKHR */,IR(0, 0),IR(1, 0),IR(178, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6425,IR(0, 0),IR(15650, 27)/* TensorFloat32RoundingINTEL */,IR(0, 0),IR(1, 0),IR(179, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6427,IR(0, 0),IR(15677, 25)/* MaskedGatherScatterINTEL */,IR(0, 0),IR(1, 0),IR(180, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6441,IR(0, 0),IR(15702, 19)/* CacheControlsINTEL */,IR(0, 0),IR(1, 0),IR(181, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6460,IR(0, 0),IR(15721, 20)/* RegisterLimitsINTEL */,IR(0, 0),IR(1, 0),IR(182, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6528,IR(0, 0),IR(15741, 20)/* BindlessImagesINTEL */,IR(0, 0),IR(1, 0),IR(183, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6912,IR(0, 0),IR(15761, 33)/* DotProductFloat16AccFloat32VALVE */,IR(0, 0),IR(114, 1),IR(184, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6913,IR(0, 0),IR(15794, 33)/* DotProductFloat16AccFloat16VALVE */,IR(0, 0),IR(114, 1),IR(184, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6914,IR(0, 0),IR(15827, 27)/* DotProductBFloat16AccVALVE */,IR(0, 0),IR(90, 1),IR(184, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6915,IR(0, 0),IR(15854, 32)/* DotProductFloat8AccFloat32VALVE */,IR(0, 0),IR(115, 1),IR(184, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {0,IR(0, 0),IR(15886, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(15898, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(15906, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {3,IR(0, 0),IR(15914, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(15920, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(15927, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(15938, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(15947, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(15960, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(15966, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(15976, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(15982, 15)/* ImportedModule */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {1,IR(0, 0),IR(15997, 20)/* ImportedDeclaration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {0,IR(0, 0),IR(16017, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(16022, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(16038, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(16052, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(16065, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(16077, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(16094, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(16106, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(16121, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(16134, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(16149, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(16167, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(16184, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(16205, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(16225, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(16245, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {16384,IR(0, 0),IR(16261, 16)/* FlagIsEnumClass */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {32768,IR(0, 0),IR(16277, 20)/* FlagTypePassByValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {65536,IR(0, 0),IR(16297, 24)/* FlagTypePassByReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(16321, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {1,IR(0, 0),IR(16327, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {2,IR(0, 0),IR(16332, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {3,IR(0, 1),IR(16371, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {4,IR(1, 2),IR(16382, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {5,IR(0, 0),IR(16391, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {6,IR(0, 0),IR(16396, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {7,IR(0, 0),IR(16403, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {8,IR(0, 1),IR(16414, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {9,IR(1, 2),IR(16421, 9)/* Fragment */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {0,IR(0, 0),IR(16430, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(16440, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(16453, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {3,IR(0, 0),IR(16466, 11)/* AtomicType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(16477, 10)/* Float16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1,IR(0, 0),IR(16487, 10)/* Float32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {2,IR(0, 0),IR(16497, 10)/* Float64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {3,IR(0, 0),IR(16507, 13)/* SignedInt8NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {4,IR(0, 0),IR(16520, 14)/* SignedInt16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {5,IR(0, 0),IR(16534, 14)/* SignedInt32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {6,IR(0, 0),IR(16548, 14)/* SignedInt64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {7,IR(0, 0),IR(16562, 15)/* UnsignedInt8NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {8,IR(0, 0),IR(16577, 16)/* UnsignedInt16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {9,IR(0, 0),IR(16593, 16)/* UnsignedInt32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {10,IR(0, 0),IR(16609, 16)/* UnsignedInt64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491000,IR(0, 0),IR(16625, 19)/* SignedInt8PackedNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491001,IR(0, 0),IR(16644, 21)/* UnsignedInt8PackedNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491002,IR(0, 0),IR(16665, 12)/* FloatE4M3NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491003,IR(0, 0),IR(16677, 12)/* FloatE5M2NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {0,IR(0, 0),IR(16689, 12)/* RowMajorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {1,IR(0, 0),IR(16701, 15)/* ColumnMajorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {4202,IR(0, 0),IR(16716, 25)/* RowBlockedInterleavedARM */,IR(0, 0),IR(116, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {4203,IR(0, 0),IR(16741, 28)/* ColumnBlockedInterleavedARM */,IR(0, 0),IR(116, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {0,IR(0, 0),IR(16769, 8)/* NoneKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {1,IR(0, 0),IR(16777, 27)/* MatrixASignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {2,IR(0, 0),IR(16804, 27)/* MatrixBSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {4,IR(0, 0),IR(16831, 27)/* MatrixCSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {8,IR(0, 0),IR(16858, 32)/* MatrixResultSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {16,IR(0, 0),IR(16890, 26)/* SaturatingAccumulationKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {1,IR(0, 0),IR(16916, 4)/* Row */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {2,IR(0, 0),IR(16920, 7)/* Column */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {4,IR(0, 0),IR(16927, 4)/* 2x2 */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {0,IR(0, 0),IR(16931, 11)/* MatrixAKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {1,IR(0, 0),IR(16942, 11)/* MatrixBKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {2,IR(0, 0),IR(16953, 21)/* MatrixAccumulatorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {0,IR(0, 0),IR(16974, 11)/* RowMajorNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {1,IR(0, 0),IR(16985, 14)/* ColumnMajorNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {2,IR(0, 0),IR(16999, 21)/* InferencingOptimalNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {3,IR(0, 0),IR(17020, 18)/* TrainingOptimalNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {0,IR(0, 0),IR(15886, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(15898, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(15906, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(15914, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(15920, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(15927, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(15938, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {8,IR(0, 0),IR(15947, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(15960, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(15966, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(15976, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(16017, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(16022, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(16038, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(16052, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(16065, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(16077, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(16094, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(16106, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(16121, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(16134, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(16149, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(16167, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(16184, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(16205, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(16225, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(16245, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(16321, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {1,IR(0, 0),IR(16327, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {2,IR(0, 0),IR(16332, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {3,IR(0, 1),IR(16371, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {4,IR(1, 2),IR(16382, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {5,IR(0, 0),IR(16391, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {6,IR(0, 0),IR(16396, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {7,IR(0, 0),IR(16403, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {8,IR(0, 1),IR(16414, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {0,IR(0, 0),IR(16430, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(16440, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(16453, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(17038, 17)/* RelaxedPrecision */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {1,IR(0, 1),IR(17055, 7)/* SpecId */,IR(0, 0),IR(117, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {2,IR(0, 0),IR(17062, 6)/* Block */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {3,IR(0, 0),IR(17068, 12)/* BufferBlock */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),SPV_SPIRV_VERSION_WORD(1,3)}, // SPV_OPERAND_TYPE_DECORATION
  {4,IR(0, 0),IR(17080, 9)/* RowMajor */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5,IR(0, 0),IR(17089, 9)/* ColMajor */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6,IR(0, 1),IR(17098, 12)/* ArrayStride */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {7,IR(0, 1),IR(17110, 13)/* MatrixStride */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {8,IR(0, 0),IR(17123, 11)/* GLSLShared */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {9,IR(0, 0),IR(17134, 11)/* GLSLPacked */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {10,IR(0, 0),IR(17145, 8)/* CPacked */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {11,IR(3, 1),IR(17179, 8)/* BuiltIn */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {13,IR(0, 0),IR(17187, 14)/* NoPerspective */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {14,IR(0, 0),IR(17201, 5)/* Flat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {15,IR(0, 0),IR(17206, 6)/* Patch */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {16,IR(0, 0),IR(17212, 9)/* Centroid */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {17,IR(0, 0),IR(17221, 7)/* Sample */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {18,IR(0, 0),IR(17228, 10)/* Invariant */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {19,IR(0, 0),IR(17238, 9)/* Restrict */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {20,IR(0, 0),IR(17247, 8)/* Aliased */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {21,IR(0, 0),IR(17255, 9)/* Volatile */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {22,IR(0, 0),IR(17264, 9)/* Constant */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {23,IR(0, 0),IR(17273, 9)/* Coherent */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {24,IR(0, 0),IR(17282, 12)/* NonWritable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {25,IR(0, 0),IR(17294, 12)/* NonReadable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {26,IR(0, 0),IR(17306, 8)/* Uniform */,IR(0, 0),IR(119, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {27,IR(4, 1),IR(17340, 10)/* UniformId */,IR(0, 0),IR(119, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {28,IR(0, 0),IR(17350, 20)/* SaturatedConversion */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {29,IR(0, 1),IR(17370, 7)/* Stream */,IR(0, 0),IR(121, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {30,IR(0, 1),IR(17377, 9)/* Location */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {31,IR(0, 1),IR(17386, 10)/* Component */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {32,IR(0, 1),IR(17396, 6)/* Index */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {33,IR(0, 1),IR(17402, 8)/* Binding */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {34,IR(0, 1),IR(17410, 14)/* DescriptorSet */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {35,IR(0, 1),IR(17424, 7)/* Offset */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {36,IR(0, 1),IR(17431, 10)/* XfbBuffer */,IR(0, 0),IR(122, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {37,IR(0, 1),IR(17441, 10)/* XfbStride */,IR(0, 0),IR(122, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {38,IR(5, 1),IR(17497, 14)/* FuncParamAttr */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {39,IR(6, 1),IR(17545, 15)/* FPRoundingMode */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {40,IR(7, 1),IR(17595, 15)/* FPFastMathMode */,IR(0, 0),IR(123, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {41,IR(8, 2),IR(17672, 18)/* LinkageAttributes */,IR(0, 0),IR(125, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {42,IR(0, 0),IR(17690, 14)/* NoContraction */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {43,IR(0, 1),IR(17704, 21)/* InputAttachmentIndex */,IR(0, 0),IR(97, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {44,IR(0, 1),IR(17725, 10)/* Alignment */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {45,IR(0, 1),IR(17735, 14)/* MaxByteOffset */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {46,IR(10, 1),IR(17769, 12)/* AlignmentId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {47,IR(10, 1),IR(17781, 16)/* MaxByteOffsetId */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4216,IR(0, 0),IR(17797, 44)/* SaturatedToLargestFloat8NormalConversionEXT */,IR(0, 0),IR(115, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4469,IR(0, 0),IR(17841, 13)/* NoSignedWrap */,IR(0, 0),IR(1, 0),IR(185, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4470,IR(0, 0),IR(17854, 15)/* NoUnsignedWrap */,IR(0, 0),IR(1, 0),IR(185, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4487,IR(0, 0),IR(17869, 18)/* WeightTextureQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4488,IR(0, 0),IR(17887, 22)/* BlockMatchTextureQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4499,IR(0, 0),IR(17909, 22)/* BlockMatchSamplerQCOM */,IR(0, 0),IR(1, 0),IR(55, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4999,IR(0, 0),IR(17931, 18)/* ExplicitInterpAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5019,IR(10, 1),IR(17949, 32)/* NodeSharesPayloadLimitsWithAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5020,IR(10, 1),IR(17981, 20)/* NodeMaxPayloadsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5078,IR(0, 0),IR(18001, 23)/* TrackFinishWritingAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5091,IR(10, 1),IR(18024, 20)/* PayloadNodeNameAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5098,IR(10, 1),IR(18044, 25)/* PayloadNodeBaseIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5099,IR(0, 0),IR(18069, 27)/* PayloadNodeSparseArrayAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5100,IR(10, 1),IR(18096, 25)/* PayloadNodeArraySizeAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5105,IR(0, 0),IR(18121, 28)/* PayloadDispatchIndirectAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5124,IR(10, 1),IR(18149, 17)/* ArrayStrideIdEXT */,IR(0, 0),IR(44, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5125,IR(10, 1),IR(18166, 12)/* OffsetIdEXT */,IR(0, 0),IR(44, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5145,IR(0, 0),IR(18178, 14)/* UTFEncodedKHR */,IR(0, 0),IR(126, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5248,IR(0, 0),IR(18192, 19)/* OverrideCoverageNV */,IR(0, 0),IR(127, 1),IR(70, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5250,IR(0, 0),IR(18211, 14)/* PassthroughNV */,IR(0, 0),IR(128, 1),IR(71, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5252,IR(0, 0),IR(18225, 19)/* ViewportRelativeNV */,IR(0, 0),IR(96, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5256,IR(0, 1),IR(18244, 28)/* SecondaryViewportRelativeNV */,IR(0, 0),IR(47, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5271,IR(0, 0),IR(18272, 16)/* PerPrimitiveEXT */,IR(73, 1),IR(129, 2),IR(186, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5272,IR(0, 0),IR(18303, 10)/* PerViewNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5273,IR(0, 0),IR(18313, 10)/* PerTaskNV */,IR(0, 0),IR(51, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5285,IR(0, 0),IR(18323, 13)/* PerVertexKHR */,IR(74, 1),IR(52, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5300,IR(0, 0),IR(18348, 11)/* NonUniform */,IR(75, 1),IR(99, 1),IR(81, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5355,IR(0, 0),IR(18373, 16)/* RestrictPointer */,IR(76, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5356,IR(0, 0),IR(18408, 15)/* AliasedPointer */,IR(77, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5358,IR(0, 1),IR(18441, 15)/* MemberOffsetNV */,IR(0, 0),IR(131, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5386,IR(0, 0),IR(18456, 30)/* HitObjectShaderRecordBufferNV */,IR(0, 0),IR(132, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5389,IR(0, 0),IR(18486, 31)/* HitObjectShaderRecordBufferEXT */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5397,IR(0, 1),IR(18517, 7)/* BankNV */,IR(0, 0),IR(131, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5398,IR(0, 0),IR(18524, 18)/* BindlessSamplerNV */,IR(0, 0),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5399,IR(0, 0),IR(18542, 16)/* BindlessImageNV */,IR(0, 0),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5400,IR(0, 0),IR(18558, 15)/* BoundSamplerNV */,IR(0, 0),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5401,IR(0, 0),IR(18573, 13)/* BoundImageNV */,IR(0, 0),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5599,IR(0, 1),IR(18586, 14)/* SIMTCallINTEL */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5602,IR(0, 0),IR(18600, 26)/* ReferencedIndirectlyINTEL */,IR(0, 0),IR(136, 1),IR(104, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5607,IR(11, 1),IR(18626, 13)/* ClobberINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5608,IR(0, 0),IR(18639, 17)/* SideEffectsINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5624,IR(0, 0),IR(18656, 27)/* VectorComputeVariableINTEL */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5625,IR(0, 1),IR(18683, 21)/* FuncParamIOKindINTEL */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5626,IR(0, 0),IR(18704, 27)/* VectorComputeFunctionINTEL */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5627,IR(0, 0),IR(18731, 15)/* StackCallINTEL */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5628,IR(0, 1),IR(18746, 26)/* GlobalVariableOffsetINTEL */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5634,IR(10, 1),IR(18772, 14)/* CounterBuffer */,IR(78, 1),IR(1, 0),IR(188, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5635,IR(11, 1),IR(18810, 13)/* UserSemantic */,IR(79, 1),IR(1, 0),IR(188, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5636,IR(11, 1),IR(18842, 15)/* UserTypeGOOGLE */,IR(0, 0),IR(1, 0),IR(189, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5822,IR(12, 2),IR(18857, 26)/* FunctionRoundingModeINTEL */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5823,IR(14, 2),IR(18914, 24)/* FunctionDenormModeINTEL */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5825,IR(0, 0),IR(18938, 15)/* RegisterALTERA */,IR(80, 1),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5826,IR(11, 1),IR(18967, 13)/* MemoryALTERA */,IR(81, 1),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5827,IR(0, 1),IR(18992, 15)/* NumbanksALTERA */,IR(82, 1),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5828,IR(0, 1),IR(19021, 16)/* BankwidthALTERA */,IR(83, 1),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5829,IR(0, 1),IR(19052, 23)/* MaxPrivateCopiesALTERA */,IR(84, 1),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5830,IR(0, 0),IR(19097, 17)/* SinglepumpALTERA */,IR(85, 1),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5831,IR(0, 0),IR(19130, 17)/* DoublepumpALTERA */,IR(86, 1),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5832,IR(0, 1),IR(19163, 20)/* MaxReplicatesALTERA */,IR(87, 1),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5833,IR(0, 0),IR(19202, 21)/* SimpleDualPortALTERA */,IR(88, 1),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5834,IR(16, 2),IR(19243, 12)/* MergeALTERA */,IR(89, 1),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5835,IR(18, 1),IR(19308, 15)/* BankBitsALTERA */,IR(90, 1),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5836,IR(0, 1),IR(19337, 21)/* ForcePow2DepthALTERA */,IR(91, 1),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5883,IR(0, 1),IR(19378, 17)/* StridesizeALTERA */,IR(92, 1),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5884,IR(0, 1),IR(19411, 15)/* WordsizeALTERA */,IR(93, 1),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5885,IR(0, 0),IR(19440, 19)/* TrueDualPortALTERA */,IR(94, 1),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5899,IR(0, 0),IR(19477, 20)/* BurstCoalesceALTERA */,IR(95, 1),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5900,IR(0, 1),IR(19516, 16)/* CacheSizeALTERA */,IR(96, 1),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5901,IR(0, 0),IR(19547, 29)/* DontStaticallyCoalesceALTERA */,IR(97, 1),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5902,IR(0, 1),IR(19604, 15)/* PrefetchALTERA */,IR(98, 1),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5905,IR(0, 0),IR(19633, 18)/* StallEnableALTERA */,IR(99, 1),IR(108, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5907,IR(0, 0),IR(19668, 26)/* FuseLoopsInFunctionALTERA */,IR(100, 1),IR(141, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5909,IR(1, 2),IR(19719, 20)/* MathOpDSPModeALTERA */,IR(101, 1),IR(142, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5914,IR(10, 1),IR(19758, 16)/* AliasScopeINTEL */,IR(0, 0),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5915,IR(10, 1),IR(19774, 13)/* NoAliasINTEL */,IR(0, 0),IR(143, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5917,IR(0, 1),IR(19787, 25)/* InitiationIntervalALTERA */,IR(102, 1),IR(144, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5918,IR(0, 1),IR(19836, 21)/* MaxConcurrencyALTERA */,IR(103, 1),IR(144, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5919,IR(0, 1),IR(19877, 21)/* PipelineEnableALTERA */,IR(104, 1),IR(144, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5921,IR(0, 1),IR(19918, 21)/* BufferLocationALTERA */,IR(105, 1),IR(145, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5944,IR(0, 1),IR(19959, 20)/* IOPipeStorageALTERA */,IR(106, 1),IR(146, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6080,IR(19, 2),IR(20032, 31)/* FunctionFloatingPointModeINTEL */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6085,IR(0, 0),IR(20063, 25)/* SingleElementVectorINTEL */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6087,IR(0, 0),IR(20088, 35)/* VectorComputeCallableFunctionINTEL */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6140,IR(0, 0),IR(20123, 18)/* MediaBlockIOINTEL */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6151,IR(0, 0),IR(20141, 16)/* StallFreeALTERA */,IR(107, 1),IR(147, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6170,IR(21, 1),IR(20203, 26)/* FPMaxErrorDecorationINTEL */,IR(0, 0),IR(148, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6172,IR(0, 1),IR(20229, 26)/* LatencyControlLabelALTERA */,IR(108, 1),IR(149, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6173,IR(22, 3),IR(20280, 31)/* LatencyControlConstraintALTERA */,IR(109, 1),IR(149, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6175,IR(0, 0),IR(20341, 28)/* ConduitKernelArgumentALTERA */,IR(110, 1),IR(150, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6176,IR(0, 0),IR(20396, 32)/* RegisterMapKernelArgumentALTERA */,IR(111, 1),IR(150, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6177,IR(0, 1),IR(20459, 34)/* MMHostInterfaceAddressWidthALTERA */,IR(112, 1),IR(150, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6178,IR(0, 1),IR(20526, 31)/* MMHostInterfaceDataWidthALTERA */,IR(113, 1),IR(150, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6179,IR(0, 1),IR(20587, 29)/* MMHostInterfaceLatencyALTERA */,IR(114, 1),IR(150, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6180,IR(25, 1),IR(20678, 35)/* MMHostInterfaceReadWriteModeALTERA */,IR(115, 1),IR(150, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6181,IR(0, 1),IR(20747, 30)/* MMHostInterfaceMaxBurstALTERA */,IR(116, 1),IR(150, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6182,IR(0, 1),IR(20806, 33)/* MMHostInterfaceWaitRequestALTERA */,IR(117, 1),IR(150, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6183,IR(0, 0),IR(20871, 27)/* StableKernelArgumentALTERA */,IR(118, 1),IR(150, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6188,IR(26, 2),IR(20963, 16)/* HostAccessINTEL */,IR(0, 0),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6190,IR(28, 1),IR(21026, 15)/* InitModeALTERA */,IR(119, 1),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6191,IR(0, 1),IR(21055, 29)/* ImplementInRegisterMapALTERA */,IR(120, 1),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6247,IR(10, 1),IR(21112, 17)/* ConditionalINTEL */,IR(0, 0),IR(113, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6442,IR(29, 2),IR(21165, 22)/* CacheControlLoadINTEL */,IR(0, 0),IR(153, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6443,IR(31, 2),IR(21224, 23)/* CacheControlStoreINTEL */,IR(0, 0),IR(153, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {0,IR(0, 0),IR(21247, 3)/* 1D */,IR(0, 0),IR(73, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {1,IR(0, 0),IR(21250, 3)/* 2D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {2,IR(0, 0),IR(21253, 3)/* 3D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {3,IR(0, 0),IR(21256, 5)/* Cube */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {4,IR(0, 0),IR(21261, 5)/* Rect */,IR(0, 0),IR(72, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {5,IR(0, 0),IR(21266, 7)/* Buffer */,IR(0, 0),IR(74, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {6,IR(0, 0),IR(21273, 12)/* SubpassData */,IR(0, 0),IR(97, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {4173,IR(0, 0),IR(21285, 17)/* TileImageDataEXT */,IR(0, 0),IR(154, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {0,IR(0, 1),IR(21302, 12)/* Invocations */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {1,IR(0, 0),IR(21314, 13)/* SpacingEqual */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {2,IR(0, 0),IR(21327, 22)/* SpacingFractionalEven */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {3,IR(0, 0),IR(21349, 21)/* SpacingFractionalOdd */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4,IR(0, 0),IR(21370, 14)/* VertexOrderCw */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5,IR(0, 0),IR(21384, 15)/* VertexOrderCcw */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6,IR(0, 0),IR(21399, 19)/* PixelCenterInteger */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {7,IR(0, 0),IR(21418, 16)/* OriginUpperLeft */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {8,IR(0, 0),IR(21434, 16)/* OriginLowerLeft */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {9,IR(0, 0),IR(21450, 19)/* EarlyFragmentTests */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {10,IR(0, 0),IR(21469, 10)/* PointMode */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {11,IR(0, 0),IR(21479, 4)/* Xfb */,IR(0, 0),IR(122, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {12,IR(0, 0),IR(21483, 15)/* DepthReplacing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {14,IR(0, 0),IR(21498, 13)/* DepthGreater */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {15,IR(0, 0),IR(21511, 10)/* DepthLess */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {16,IR(0, 0),IR(21521, 15)/* DepthUnchanged */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {17,IR(22, 3),IR(21536, 10)/* LocalSize */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {18,IR(22, 3),IR(21546, 14)/* LocalSizeHint */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {19,IR(0, 0),IR(21560, 12)/* InputPoints */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {20,IR(0, 0),IR(21572, 11)/* InputLines */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {21,IR(0, 0),IR(21583, 20)/* InputLinesAdjacency */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {22,IR(0, 0),IR(21603, 10)/* Triangles */,IR(0, 0),IR(12, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {23,IR(0, 0),IR(21613, 24)/* InputTrianglesAdjacency */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {24,IR(0, 0),IR(21637, 6)/* Quads */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {25,IR(0, 0),IR(21643, 9)/* Isolines */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {26,IR(0, 1),IR(21652, 15)/* OutputVertices */,IR(0, 0),IR(155, 4),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {27,IR(0, 0),IR(21667, 13)/* OutputPoints */,IR(0, 0),IR(159, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {28,IR(0, 0),IR(21680, 16)/* OutputLineStrip */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {29,IR(0, 0),IR(21696, 20)/* OutputTriangleStrip */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {30,IR(0, 1),IR(21716, 12)/* VecTypeHint */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {31,IR(0, 0),IR(21728, 15)/* ContractionOff */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {33,IR(0, 0),IR(21743, 12)/* Initializer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {34,IR(0, 0),IR(21755, 10)/* Finalizer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {35,IR(0, 1),IR(6307, 13)/* SubgroupSize */,IR(0, 0),IR(162, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {36,IR(0, 1),IR(21765, 22)/* SubgroupsPerWorkgroup */,IR(0, 0),IR(162, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {37,IR(10, 1),IR(21787, 24)/* SubgroupsPerWorkgroupId */,IR(0, 0),IR(162, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {38,IR(33, 3),IR(21811, 12)/* LocalSizeId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {39,IR(33, 3),IR(21823, 16)/* LocalSizeHintId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4169,IR(0, 0),IR(21839, 34)/* NonCoherentColorAttachmentReadEXT */,IR(0, 0),IR(154, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4170,IR(0, 0),IR(21873, 34)/* NonCoherentDepthAttachmentReadEXT */,IR(0, 0),IR(163, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4171,IR(0, 0),IR(21907, 36)/* NonCoherentStencilAttachmentReadEXT */,IR(0, 0),IR(164, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4421,IR(0, 0),IR(21943, 30)/* SubgroupUniformControlFlowKHR */,IR(0, 0),IR(3, 1),IR(190, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4446,IR(0, 0),IR(21973, 18)/* PostDepthCoverage */,IR(0, 0),IR(165, 1),IR(45, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4459,IR(0, 1),IR(10555, 15)/* DenormPreserve */,IR(0, 0),IR(166, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4460,IR(0, 1),IR(10570, 18)/* DenormFlushToZero */,IR(0, 0),IR(167, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4461,IR(0, 1),IR(10588, 25)/* SignedZeroInfNanPreserve */,IR(0, 0),IR(168, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4462,IR(0, 1),IR(10613, 16)/* RoundingModeRTE */,IR(0, 0),IR(169, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4463,IR(0, 1),IR(10629, 16)/* RoundingModeRTZ */,IR(0, 0),IR(170, 1),IR(47, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4489,IR(0, 0),IR(21991, 34)/* NonCoherentTileAttachmentReadQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4490,IR(22, 3),IR(22025, 20)/* TileShadingRateQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5017,IR(0, 0),IR(22045, 29)/* EarlyAndLateFragmentTestsAMD */,IR(0, 0),IR(3, 1),IR(191, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5027,IR(0, 0),IR(22074, 23)/* StencilRefReplacingEXT */,IR(0, 0),IR(42, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5069,IR(0, 0),IR(22097, 15)/* CoalescingAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5070,IR(10, 1),IR(22112, 15)/* IsApiEntryAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5071,IR(10, 1),IR(22127, 21)/* MaxNodeRecursionAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5072,IR(33, 3),IR(22148, 24)/* StaticNumWorkgroupsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5073,IR(10, 1),IR(7200, 16)/* ShaderIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5077,IR(33, 3),IR(22172, 21)/* MaxNumWorkgroupsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5079,IR(0, 0),IR(22193, 28)/* StencilRefUnchangedFrontAMD */,IR(0, 0),IR(42, 1),IR(192, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5080,IR(0, 0),IR(22221, 26)/* StencilRefGreaterFrontAMD */,IR(0, 0),IR(42, 1),IR(192, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5081,IR(0, 0),IR(22247, 23)/* StencilRefLessFrontAMD */,IR(0, 0),IR(42, 1),IR(192, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5082,IR(0, 0),IR(22270, 27)/* StencilRefUnchangedBackAMD */,IR(0, 0),IR(42, 1),IR(192, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5083,IR(0, 0),IR(22297, 25)/* StencilRefGreaterBackAMD */,IR(0, 0),IR(42, 1),IR(192, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5084,IR(0, 0),IR(22322, 22)/* StencilRefLessBackAMD */,IR(0, 0),IR(42, 1),IR(192, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5088,IR(0, 0),IR(22344, 19)/* QuadDerivativesKHR */,IR(0, 0),IR(171, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5089,IR(0, 0),IR(22363, 20)/* RequireFullQuadsKHR */,IR(0, 0),IR(171, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5102,IR(36, 2),IR(22383, 20)/* SharesInputWithAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5157,IR(0, 0),IR(22403, 20)/* ArithmeticPoisonKHR */,IR(0, 0),IR(172, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5269,IR(0, 0),IR(22423, 15)/* OutputLinesEXT */,IR(121, 1),IR(129, 2),IR(186, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5270,IR(0, 1),IR(22452, 20)/* OutputPrimitivesEXT */,IR(122, 1),IR(129, 2),IR(186, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5289,IR(0, 0),IR(22491, 24)/* DerivativeGroupQuadsKHR */,IR(123, 1),IR(173, 1),IR(77, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5290,IR(0, 0),IR(22538, 25)/* DerivativeGroupLinearKHR */,IR(124, 1),IR(174, 1),IR(77, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5298,IR(0, 0),IR(22587, 19)/* OutputTrianglesEXT */,IR(125, 1),IR(129, 2),IR(186, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5366,IR(0, 0),IR(22624, 25)/* PixelInterlockOrderedEXT */,IR(0, 0),IR(175, 1),IR(85, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5367,IR(0, 0),IR(22649, 27)/* PixelInterlockUnorderedEXT */,IR(0, 0),IR(175, 1),IR(85, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5368,IR(0, 0),IR(22676, 26)/* SampleInterlockOrderedEXT */,IR(0, 0),IR(176, 1),IR(85, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5369,IR(0, 0),IR(22702, 28)/* SampleInterlockUnorderedEXT */,IR(0, 0),IR(176, 1),IR(85, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5370,IR(0, 0),IR(22730, 31)/* ShadingRateInterlockOrderedEXT */,IR(0, 0),IR(177, 1),IR(85, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5371,IR(0, 0),IR(22761, 33)/* ShadingRateInterlockUnorderedEXT */,IR(0, 0),IR(177, 1),IR(85, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5427,IR(0, 0),IR(12902, 23)/* Shader64BitIndexingEXT */,IR(0, 0),IR(178, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5618,IR(0, 1),IR(22794, 27)/* SharedLocalMemorySizeINTEL */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5620,IR(0, 1),IR(22821, 21)/* RoundingModeRTPINTEL */,IR(0, 0),IR(179, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5621,IR(0, 1),IR(22842, 21)/* RoundingModeRTNINTEL */,IR(0, 0),IR(179, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5622,IR(0, 1),IR(22863, 26)/* FloatingPointModeALTINTEL */,IR(0, 0),IR(179, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5623,IR(0, 1),IR(22889, 27)/* FloatingPointModeIEEEINTEL */,IR(0, 0),IR(179, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5893,IR(22, 3),IR(22916, 22)/* MaxWorkgroupSizeINTEL */,IR(0, 0),IR(180, 1),IR(121, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5894,IR(0, 1),IR(22938, 16)/* MaxWorkDimINTEL */,IR(0, 0),IR(180, 1),IR(121, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5895,IR(0, 0),IR(22954, 20)/* NoGlobalOffsetINTEL */,IR(0, 0),IR(180, 1),IR(121, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5896,IR(0, 1),IR(22974, 22)/* NumSIMDWorkitemsINTEL */,IR(0, 0),IR(109, 1),IR(121, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5903,IR(0, 1),IR(22996, 28)/* SchedulerTargetFmaxMhzINTEL */,IR(0, 0),IR(109, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6023,IR(0, 0),IR(23024, 24)/* MaximallyReconvergesKHR */,IR(0, 0),IR(3, 1),IR(194, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6028,IR(36, 2),IR(23048, 18)/* FPFastMathDefault */,IR(0, 0),IR(181, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6154,IR(0, 1),IR(23066, 24)/* StreamingInterfaceINTEL */,IR(0, 0),IR(109, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6160,IR(0, 1),IR(23090, 26)/* RegisterMapInterfaceINTEL */,IR(0, 0),IR(182, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6417,IR(0, 1),IR(23116, 23)/* NamedBarrierCountINTEL */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6461,IR(0, 1),IR(23139, 22)/* MaximumRegistersINTEL */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6462,IR(10, 1),IR(23161, 24)/* MaximumRegistersIdINTEL */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6463,IR(38, 1),IR(23236, 27)/* NamedMaximumRegistersINTEL */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {0,IR(0, 0),IR(23263, 7)/* Vertex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {1,IR(0, 0),IR(23270, 20)/* TessellationControl */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {2,IR(0, 0),IR(23290, 23)/* TessellationEvaluation */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {3,IR(0, 0),IR(5788, 9)/* Geometry */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {4,IR(0, 0),IR(16421, 9)/* Fragment */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5,IR(0, 0),IR(23313, 10)/* GLCompute */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {6,IR(0, 0),IR(5555, 7)/* Kernel */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5267,IR(0, 0),IR(23323, 7)/* TaskNV */,IR(0, 0),IR(51, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5268,IR(0, 0),IR(23330, 7)/* MeshNV */,IR(0, 0),IR(51, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5313,IR(0, 0),IR(23337, 17)/* RayGenerationKHR */,IR(126, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5314,IR(0, 0),IR(23370, 16)/* IntersectionKHR */,IR(127, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5315,IR(0, 0),IR(23401, 10)/* AnyHitKHR */,IR(128, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5316,IR(0, 0),IR(23420, 14)/* ClosestHitKHR */,IR(129, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5317,IR(0, 0),IR(23447, 8)/* MissKHR */,IR(130, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5318,IR(0, 0),IR(23462, 12)/* CallableKHR */,IR(131, 1),IR(55, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5364,IR(0, 0),IR(23485, 8)/* TaskEXT */,IR(0, 0),IR(54, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5365,IR(0, 0),IR(23493, 8)/* MeshEXT */,IR(0, 0),IR(54, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {0,IR(0, 0),IR(23501, 9)/* Preserve */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPDENORM_MODE
  {1,IR(0, 0),IR(23510, 12)/* FlushToZero */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPDENORM_MODE
  {0,IR(0, 0),IR(23522, 12)/* BFloat16KHR */,IR(0, 0),IR(90, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {4214,IR(0, 0),IR(23534, 14)/* Float8E4M3EXT */,IR(0, 0),IR(115, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {4215,IR(0, 0),IR(23548, 14)/* Float8E5M2EXT */,IR(0, 0),IR(115, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {0,IR(0, 0),IR(23562, 5)/* IEEE */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPOPERATION_MODE
  {1,IR(0, 0),IR(23567, 4)/* ALT */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPOPERATION_MODE
  {0,IR(0, 0),IR(16017, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {1,IR(0, 0),IR(23571, 7)/* NotNaN */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {2,IR(0, 0),IR(23578, 7)/* NotInf */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {4,IR(0, 0),IR(23585, 4)/* NSZ */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {8,IR(0, 0),IR(23589, 11)/* AllowRecip */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {16,IR(0, 0),IR(23600, 5)/* Fast */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {65536,IR(0, 0),IR(23605, 14)/* AllowContract */,IR(132, 1),IR(184, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {131072,IR(0, 0),IR(23642, 13)/* AllowReassoc */,IR(133, 1),IR(184, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {262144,IR(0, 0),IR(23673, 15)/* AllowTransform */,IR(0, 0),IR(181, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {0,IR(0, 0),IR(23688, 4)/* RTE */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {1,IR(0, 0),IR(23692, 4)/* RTZ */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {2,IR(0, 0),IR(23696, 4)/* RTP */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {3,IR(0, 0),IR(23700, 4)/* RTN */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {1,IR(0, 0),IR(23704, 16)/* Vertical2Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {2,IR(0, 0),IR(23720, 16)/* Vertical4Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {4,IR(0, 0),IR(23736, 18)/* Horizontal2Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {8,IR(0, 0),IR(23754, 18)/* Horizontal4Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {0,IR(0, 0),IR(16017, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {1,IR(0, 0),IR(23772, 7)/* Inline */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {2,IR(0, 0),IR(23779, 11)/* DontInline */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {4,IR(0, 0),IR(23790, 5)/* Pure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {8,IR(0, 0),IR(23795, 6)/* Const */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {65536,IR(0, 0),IR(14899, 11)/* OptNoneEXT */,IR(67, 1),IR(186, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {0,IR(0, 0),IR(23801, 5)/* Zext */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {1,IR(0, 0),IR(23806, 5)/* Sext */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {2,IR(0, 0),IR(23811, 6)/* ByVal */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {3,IR(0, 0),IR(23817, 5)/* Sret */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {4,IR(0, 0),IR(23822, 8)/* NoAlias */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {5,IR(0, 0),IR(23830, 10)/* NoCapture */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {6,IR(0, 0),IR(23840, 8)/* NoWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {7,IR(0, 0),IR(23848, 12)/* NoReadWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {5940,IR(0, 0),IR(23860, 21)/* RuntimeAlignedALTERA */,IR(134, 1),IR(187, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {0,IR(0, 0),IR(23901, 7)/* Reduce */,IR(0, 0),IR(188, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {1,IR(0, 0),IR(23908, 14)/* InclusiveScan */,IR(0, 0),IR(188, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {2,IR(0, 0),IR(23922, 14)/* ExclusiveScan */,IR(0, 0),IR(188, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {3,IR(0, 0),IR(23936, 16)/* ClusteredReduce */,IR(0, 0),IR(191, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {6,IR(0, 0),IR(23952, 21)/* PartitionedReduceEXT */,IR(135, 1),IR(192, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {7,IR(0, 0),IR(23993, 28)/* PartitionedInclusiveScanEXT */,IR(136, 1),IR(192, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {8,IR(0, 0),IR(24048, 28)/* PartitionedExclusiveScanEXT */,IR(137, 1),IR(192, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {0,IR(0, 0),IR(24103, 10)/* NoneINTEL */,IR(0, 0),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {1,IR(0, 0),IR(24113, 10)/* ReadINTEL */,IR(0, 0),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {2,IR(0, 0),IR(24123, 11)/* WriteINTEL */,IR(0, 0),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {3,IR(0, 0),IR(24134, 15)/* ReadWriteINTEL */,IR(0, 0),IR(151, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {0,IR(0, 0),IR(16017, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {1,IR(10, 1),IR(24149, 5)/* Bias */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {2,IR(10, 1),IR(24154, 4)/* Lod */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {4,IR(36, 2),IR(24158, 5)/* Grad */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {8,IR(10, 1),IR(24163, 12)/* ConstOffset */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {16,IR(10, 1),IR(17424, 7)/* Offset */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {32,IR(10, 1),IR(24175, 13)/* ConstOffsets */,IR(0, 0),IR(193, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {64,IR(10, 1),IR(17221, 7)/* Sample */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {128,IR(10, 1),IR(9388, 7)/* MinLod */,IR(0, 0),IR(194, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {256,IR(4, 1),IR(24188, 19)/* MakeTexelAvailable */,IR(138, 1),IR(195, 1),IR(83, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {512,IR(4, 1),IR(24229, 17)/* MakeTexelVisible */,IR(139, 1),IR(195, 1),IR(83, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {1024,IR(0, 0),IR(24266, 16)/* NonPrivateTexel */,IR(140, 1),IR(195, 1),IR(83, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {2048,IR(0, 0),IR(24301, 14)/* VolatileTexel */,IR(141, 1),IR(195, 1),IR(83, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {4096,IR(0, 0),IR(24332, 11)/* SignExtend */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {8192,IR(0, 0),IR(24343, 11)/* ZeroExtend */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {16384,IR(0, 0),IR(24354, 12)/* Nontemporal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {65536,IR(10, 1),IR(24366, 8)/* Offsets */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {0,IR(0, 0),IR(24374, 10)/* SnormInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {1,IR(0, 0),IR(24384, 11)/* SnormInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {2,IR(0, 0),IR(24395, 10)/* UnormInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {3,IR(0, 0),IR(24405, 11)/* UnormInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {4,IR(0, 0),IR(24416, 14)/* UnormShort565 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {5,IR(0, 0),IR(24430, 14)/* UnormShort555 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {6,IR(0, 0),IR(24444, 15)/* UnormInt101010 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {7,IR(0, 0),IR(24459, 11)/* SignedInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {8,IR(0, 0),IR(24470, 12)/* SignedInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {9,IR(0, 0),IR(24482, 12)/* SignedInt32 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {10,IR(0, 0),IR(24494, 13)/* UnsignedInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {11,IR(0, 0),IR(24507, 14)/* UnsignedInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {12,IR(0, 0),IR(24521, 14)/* UnsignedInt32 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {13,IR(0, 0),IR(24535, 10)/* HalfFloat */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {14,IR(0, 0),IR(15914, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {15,IR(0, 0),IR(24545, 11)/* UnormInt24 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {16,IR(0, 0),IR(24556, 17)/* UnormInt101010_2 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {17,IR(0, 0),IR(24573, 16)/* UnormInt10X6EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {19,IR(0, 0),IR(24589, 20)/* UnsignedIntRaw10EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {20,IR(0, 0),IR(24609, 20)/* UnsignedIntRaw12EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {21,IR(0, 0),IR(24629, 20)/* UnormInt2_101010EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {22,IR(0, 0),IR(24649, 19)/* UnsignedInt10X6EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {23,IR(0, 0),IR(24668, 19)/* UnsignedInt12X4EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {24,IR(0, 0),IR(24687, 19)/* UnsignedInt14X2EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {25,IR(0, 0),IR(24706, 16)/* UnormInt12X4EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {26,IR(0, 0),IR(24722, 16)/* UnormInt14X2EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {0,IR(0, 0),IR(24738, 2)/* R */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {1,IR(0, 0),IR(24740, 2)/* A */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {2,IR(0, 0),IR(24742, 3)/* RG */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {3,IR(0, 0),IR(24745, 3)/* RA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {4,IR(0, 0),IR(24748, 4)/* RGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {5,IR(0, 0),IR(24752, 5)/* RGBA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {6,IR(0, 0),IR(24757, 5)/* BGRA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {7,IR(0, 0),IR(24762, 5)/* ARGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {8,IR(0, 0),IR(24767, 10)/* Intensity */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {9,IR(0, 0),IR(24777, 10)/* Luminance */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {10,IR(0, 0),IR(24787, 3)/* Rx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {11,IR(0, 0),IR(24790, 4)/* RGx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {12,IR(0, 0),IR(24794, 5)/* RGBx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {13,IR(0, 0),IR(24799, 6)/* Depth */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {14,IR(0, 0),IR(24805, 13)/* DepthStencil */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {15,IR(0, 0),IR(24818, 5)/* sRGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {16,IR(0, 0),IR(24823, 6)/* sRGBx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {17,IR(0, 0),IR(24829, 6)/* sRGBA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {18,IR(0, 0),IR(24835, 6)/* sBGRA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {19,IR(0, 0),IR(24841, 5)/* ABGR */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {0,IR(0, 0),IR(24846, 28)/* InitOnDeviceReprogramALTERA */,IR(142, 1),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {1,IR(0, 0),IR(24901, 24)/* InitOnDeviceResetALTERA */,IR(143, 1),IR(152, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {0,IR(0, 0),IR(24948, 7)/* NoWait */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {1,IR(0, 0),IR(24955, 11)/* WaitKernel */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {2,IR(0, 0),IR(24966, 14)/* WaitWorkGroup */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {0,IR(0, 0),IR(16017, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {1,IR(0, 0),IR(24980, 12)/* CmdExecTime */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {0,IR(0, 0),IR(16017, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {1,IR(0, 0),IR(24992, 13)/* MayUsePrintf */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {0,IR(0, 0),IR(25005, 7)/* Export */,IR(0, 0),IR(125, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {1,IR(0, 0),IR(25012, 7)/* Import */,IR(0, 0),IR(125, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {2,IR(0, 0),IR(25019, 12)/* LinkOnceODR */,IR(0, 0),IR(125, 1),IR(195, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {0,IR(0, 0),IR(25031, 14)/* UncachedINTEL */,IR(0, 0),IR(153, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {1,IR(0, 0),IR(25045, 12)/* CachedINTEL */,IR(0, 0),IR(153, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {2,IR(0, 0),IR(25057, 15)/* StreamingINTEL */,IR(0, 0),IR(153, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {3,IR(0, 0),IR(25072, 25)/* InvalidateAfterReadINTEL */,IR(0, 0),IR(153, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {4,IR(0, 0),IR(25097, 17)/* ConstCachedINTEL */,IR(0, 0),IR(153, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {0,IR(0, 0),IR(16017, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {1,IR(0, 0),IR(25114, 7)/* Unroll */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {2,IR(0, 0),IR(25121, 11)/* DontUnroll */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {4,IR(0, 0),IR(25132, 19)/* DependencyInfinite */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {8,IR(0, 1),IR(25151, 17)/* DependencyLength */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {16,IR(0, 1),IR(25168, 14)/* MinIterations */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {32,IR(0, 1),IR(25182, 14)/* MaxIterations */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {64,IR(0, 1),IR(25196, 18)/* IterationMultiple */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {128,IR(0, 1),IR(25214, 10)/* PeelCount */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {256,IR(0, 1),IR(25224, 13)/* PartialCount */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {65536,IR(0, 1),IR(19787, 25)/* InitiationIntervalALTERA */,IR(102, 1),IR(196, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {131072,IR(0, 1),IR(19836, 21)/* MaxConcurrencyALTERA */,IR(103, 1),IR(196, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {262144,IR(0, 1),IR(25237, 22)/* DependencyArrayALTERA */,IR(144, 1),IR(196, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {524288,IR(0, 1),IR(19877, 21)/* PipelineEnableALTERA */,IR(104, 1),IR(196, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {1048576,IR(0, 1),IR(25280, 19)/* LoopCoalesceALTERA */,IR(145, 1),IR(196, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {2097152,IR(0, 1),IR(25317, 22)/* MaxInterleavingALTERA */,IR(146, 1),IR(196, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {4194304,IR(0, 1),IR(25360, 27)/* SpeculatedIterationsALTERA */,IR(147, 1),IR(196, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {8388608,IR(0, 0),IR(25413, 15)/* NoFusionALTERA */,IR(148, 1),IR(196, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {16777216,IR(0, 1),IR(25442, 16)/* LoopCountALTERA */,IR(149, 1),IR(196, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {33554432,IR(0, 1),IR(25473, 27)/* MaxReinvocationDelayALTERA */,IR(150, 1),IR(196, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {0,IR(0, 0),IR(16017, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {1,IR(0, 0),IR(25526, 29)/* MatrixASignedComponentsINTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {2,IR(0, 0),IR(25555, 29)/* MatrixBSignedComponentsINTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {4,IR(0, 0),IR(25584, 21)/* MatrixCBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {8,IR(0, 0),IR(25605, 26)/* MatrixResultBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {16,IR(0, 0),IR(25631, 23)/* MatrixAPackedInt8INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {32,IR(0, 0),IR(25654, 23)/* MatrixBPackedInt8INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {64,IR(0, 0),IR(25677, 23)/* MatrixAPackedInt4INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {128,IR(0, 0),IR(25700, 23)/* MatrixBPackedInt4INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {256,IR(0, 0),IR(25723, 17)/* MatrixATF32INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {512,IR(0, 0),IR(25740, 17)/* MatrixBTF32INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {1024,IR(0, 0),IR(25757, 26)/* MatrixAPackedFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {2048,IR(0, 0),IR(25783, 26)/* MatrixBPackedFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {4096,IR(0, 0),IR(25809, 27)/* MatrixAPackedBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {8192,IR(0, 0),IR(25836, 27)/* MatrixBPackedBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {0,IR(0, 0),IR(16017, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {1,IR(0, 0),IR(17255, 9)/* Volatile */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {2,IR(0, 1),IR(25863, 8)/* Aligned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {4,IR(0, 0),IR(24354, 12)/* Nontemporal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {8,IR(4, 1),IR(25871, 21)/* MakePointerAvailable */,IR(151, 1),IR(195, 1),IR(83, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {16,IR(4, 1),IR(25916, 19)/* MakePointerVisible */,IR(152, 1),IR(195, 1),IR(83, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {32,IR(0, 0),IR(25957, 18)/* NonPrivatePointer */,IR(153, 1),IR(195, 1),IR(83, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {65536,IR(10, 1),IR(25996, 20)/* AliasScopeINTELMask */,IR(0, 0),IR(143, 1),IR(130, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {131072,IR(10, 1),IR(26016, 17)/* NoAliasINTELMask */,IR(0, 0),IR(143, 1),IR(130, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {0,IR(0, 0),IR(26033, 7)/* Simple */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {1,IR(0, 0),IR(26040, 8)/* GLSL450 */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {2,IR(0, 0),IR(26048, 7)/* OpenCL */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {3,IR(0, 0),IR(26055, 7)/* Vulkan */,IR(154, 1),IR(195, 1),IR(83, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {0,IR(0, 0),IR(26072, 8)/* Relaxed */,IR(155, 1),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {2,IR(0, 0),IR(26080, 8)/* Acquire */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {4,IR(0, 0),IR(26088, 8)/* Release */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {8,IR(0, 0),IR(26096, 15)/* AcquireRelease */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {16,IR(0, 0),IR(26111, 23)/* SequentiallyConsistent */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {64,IR(0, 0),IR(26134, 14)/* UniformMemory */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {128,IR(0, 0),IR(26148, 15)/* SubgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {256,IR(0, 0),IR(26163, 16)/* WorkgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {512,IR(0, 0),IR(26179, 21)/* CrossWorkgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {1024,IR(0, 0),IR(26200, 20)/* AtomicCounterMemory */,IR(0, 0),IR(83, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {2048,IR(0, 0),IR(26220, 12)/* ImageMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {4096,IR(0, 0),IR(26232, 13)/* OutputMemory */,IR(156, 1),IR(195, 1),IR(83, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {8192,IR(0, 0),IR(26261, 14)/* MakeAvailable */,IR(157, 1),IR(195, 1),IR(83, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {16384,IR(0, 0),IR(26292, 12)/* MakeVisible */,IR(158, 1),IR(195, 1),IR(83, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {32768,IR(0, 0),IR(17255, 9)/* Volatile */,IR(0, 0),IR(195, 1),IR(83, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {0,IR(0, 0),IR(26319, 10)/* AutoINTEL */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS
  {0,IR(0, 0),IR(26329, 5)/* WRAP */,IR(0, 0),IR(197, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {1,IR(0, 0),IR(26334, 4)/* SAT */,IR(0, 0),IR(197, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {2,IR(0, 0),IR(26338, 9)/* SAT_ZERO */,IR(0, 0),IR(197, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {3,IR(0, 0),IR(26347, 8)/* SAT_SYM */,IR(0, 0),IR(197, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {0,IR(0, 0),IR(26355, 25)/* PackedVectorFormat4x8Bit */,IR(159, 1),IR(1, 0),IR(147, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {0,IR(0, 0),IR(26408, 4)/* TRN */,IR(0, 0),IR(197, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {1,IR(0, 0),IR(26412, 9)/* TRN_ZERO */,IR(0, 0),IR(197, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {2,IR(0, 0),IR(26421, 4)/* RND */,IR(0, 0),IR(197, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {3,IR(0, 0),IR(26425, 9)/* RND_ZERO */,IR(0, 0),IR(197, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {4,IR(0, 0),IR(26434, 8)/* RND_INF */,IR(0, 0),IR(197, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {5,IR(0, 0),IR(26442, 12)/* RND_MIN_INF */,IR(0, 0),IR(197, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {6,IR(0, 0),IR(26454, 9)/* RND_CONV */,IR(0, 0),IR(197, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {7,IR(0, 0),IR(26463, 13)/* RND_CONV_ODD */,IR(0, 0),IR(197, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {0,IR(0, 0),IR(16017, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {1,IR(0, 0),IR(26476, 25)/* RobustnessPerComponentNV */,IR(0, 0),IR(198, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {2,IR(0, 0),IR(26501, 23)/* RobustnessPerElementNV */,IR(0, 0),IR(198, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {0,IR(0, 0),IR(16769, 8)/* NoneKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {1,IR(0, 0),IR(26524, 10)/* OpaqueKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {2,IR(0, 0),IR(26534, 12)/* NoOpaqueKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {4,IR(0, 0),IR(26546, 23)/* TerminateOnFirstHitKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {8,IR(0, 0),IR(26569, 24)/* SkipClosestHitShaderKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {16,IR(0, 0),IR(26593, 27)/* CullBackFacingTrianglesKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {32,IR(0, 0),IR(26620, 28)/* CullFrontFacingTrianglesKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {64,IR(0, 0),IR(26648, 14)/* CullOpaqueKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {128,IR(0, 0),IR(26662, 16)/* CullNoOpaqueKHR */,IR(0, 0),IR(85, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {256,IR(0, 0),IR(26678, 17)/* SkipTrianglesKHR */,IR(160, 1),IR(199, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {512,IR(0, 0),IR(26719, 13)/* SkipAABBsKHR */,IR(0, 0),IR(199, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {1024,IR(0, 0),IR(26732, 30)/* ForceOpacityMicromap2StateEXT */,IR(0, 0),IR(200, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {0,IR(0, 0),IR(26762, 41)/* RayQueryCandidateIntersectionTriangleKHR */,IR(0, 0),IR(201, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {1,IR(0, 0),IR(26803, 37)/* RayQueryCandidateIntersectionAABBKHR */,IR(0, 0),IR(201, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {0,IR(0, 0),IR(26840, 37)/* RayQueryCommittedIntersectionNoneKHR */,IR(0, 0),IR(201, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {1,IR(0, 0),IR(26877, 41)/* RayQueryCommittedIntersectionTriangleKHR */,IR(0, 0),IR(201, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {2,IR(0, 0),IR(26918, 42)/* RayQueryCommittedIntersectionGeneratedKHR */,IR(0, 0),IR(201, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {0,IR(0, 0),IR(26960, 33)/* RayQueryCandidateIntersectionKHR */,IR(0, 0),IR(201, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {1,IR(0, 0),IR(26993, 33)/* RayQueryCommittedIntersectionKHR */,IR(0, 0),IR(201, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {0,IR(0, 0),IR(16017, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {1,IR(0, 0),IR(27026, 12)/* ClampToEdge */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {2,IR(0, 0),IR(27038, 6)/* Clamp */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {3,IR(0, 0),IR(27044, 7)/* Repeat */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {4,IR(0, 0),IR(27051, 15)/* RepeatMirrored */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {0,IR(0, 0),IR(27066, 8)/* Nearest */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {1,IR(0, 0),IR(27074, 7)/* Linear */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {0,IR(0, 0),IR(27081, 8)/* Unknown */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {1,IR(0, 0),IR(27089, 8)/* Rgba32f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {2,IR(0, 0),IR(27097, 8)/* Rgba16f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {3,IR(0, 0),IR(27105, 5)/* R32f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {4,IR(0, 0),IR(27110, 6)/* Rgba8 */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {5,IR(0, 0),IR(27116, 11)/* Rgba8Snorm */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {6,IR(0, 0),IR(27127, 6)/* Rg32f */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {7,IR(0, 0),IR(27133, 6)/* Rg16f */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {8,IR(0, 0),IR(27139, 13)/* R11fG11fB10f */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {9,IR(0, 0),IR(27152, 5)/* R16f */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {10,IR(0, 0),IR(27157, 7)/* Rgba16 */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {11,IR(0, 0),IR(27164, 8)/* Rgb10A2 */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {12,IR(0, 0),IR(27172, 5)/* Rg16 */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {13,IR(0, 0),IR(27177, 4)/* Rg8 */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {14,IR(0, 0),IR(27181, 4)/* R16 */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {15,IR(0, 0),IR(27185, 3)/* R8 */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {16,IR(0, 0),IR(27188, 12)/* Rgba16Snorm */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {17,IR(0, 0),IR(27200, 10)/* Rg16Snorm */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {18,IR(0, 0),IR(27210, 9)/* Rg8Snorm */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {19,IR(0, 0),IR(27219, 9)/* R16Snorm */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {20,IR(0, 0),IR(27228, 8)/* R8Snorm */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {21,IR(0, 0),IR(27236, 8)/* Rgba32i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {22,IR(0, 0),IR(27244, 8)/* Rgba16i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {23,IR(0, 0),IR(27252, 7)/* Rgba8i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {24,IR(0, 0),IR(27259, 5)/* R32i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {25,IR(0, 0),IR(27264, 6)/* Rg32i */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {26,IR(0, 0),IR(27270, 6)/* Rg16i */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {27,IR(0, 0),IR(27276, 5)/* Rg8i */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {28,IR(0, 0),IR(27281, 5)/* R16i */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {29,IR(0, 0),IR(27286, 4)/* R8i */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {30,IR(0, 0),IR(27290, 9)/* Rgba32ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {31,IR(0, 0),IR(27299, 9)/* Rgba16ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {32,IR(0, 0),IR(27308, 8)/* Rgba8ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {33,IR(0, 0),IR(27316, 6)/* R32ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {34,IR(0, 0),IR(27322, 10)/* Rgb10a2ui */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {35,IR(0, 0),IR(27332, 7)/* Rg32ui */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {36,IR(0, 0),IR(27339, 7)/* Rg16ui */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {37,IR(0, 0),IR(27346, 6)/* Rg8ui */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {38,IR(0, 0),IR(27352, 6)/* R16ui */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {39,IR(0, 0),IR(27358, 5)/* R8ui */,IR(0, 0),IR(202, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {40,IR(0, 0),IR(27363, 6)/* R64ui */,IR(0, 0),IR(203, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {41,IR(0, 0),IR(27369, 5)/* R64i */,IR(0, 0),IR(203, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {0,IR(0, 0),IR(27374, 12)/* CrossDevice */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {1,IR(0, 0),IR(27386, 7)/* Device */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {2,IR(0, 0),IR(27393, 10)/* Workgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {3,IR(0, 0),IR(27403, 9)/* Subgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {4,IR(0, 0),IR(27412, 11)/* Invocation */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {5,IR(0, 0),IR(27423, 12)/* QueueFamily */,IR(161, 1),IR(195, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {6,IR(0, 0),IR(27450, 14)/* ShaderCallKHR */,IR(0, 0),IR(61, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {0,IR(0, 0),IR(16017, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {1,IR(0, 0),IR(27464, 8)/* Flatten */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {2,IR(0, 0),IR(27472, 12)/* DontFlatten */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {1,IR(0, 0),IR(27484, 29)/* IdentifierPossibleDuplicates */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS
  {0,IR(0, 0),IR(15886, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(15898, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(15906, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {3,IR(0, 0),IR(15914, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(15920, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(15927, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(15938, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(15947, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(15960, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(15966, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(15976, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(15982, 15)/* ImportedModule */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {1,IR(0, 0),IR(15997, 20)/* ImportedDeclaration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {0,IR(0, 0),IR(16017, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(16022, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(16038, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(16052, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(16065, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(16077, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(16094, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(16106, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(16121, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(16134, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(16149, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(16167, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(16184, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(16205, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(16225, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(16245, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {16384,IR(0, 0),IR(16261, 16)/* FlagIsEnumClass */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {32768,IR(0, 0),IR(16277, 20)/* FlagTypePassByValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {65536,IR(0, 0),IR(16297, 24)/* FlagTypePassByReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {131072,IR(0, 0),IR(27513, 26)/* FlagUnknownPhysicalLayout */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(16321, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {1,IR(0, 0),IR(16327, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {2,IR(0, 0),IR(16332, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {3,IR(10, 1),IR(16371, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {4,IR(36, 2),IR(16382, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {5,IR(0, 0),IR(16391, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {6,IR(0, 0),IR(16396, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {7,IR(0, 0),IR(16403, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {8,IR(10, 1),IR(16414, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {9,IR(36, 2),IR(16421, 9)/* Fragment */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {0,IR(0, 0),IR(16430, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(16440, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(16453, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {3,IR(0, 0),IR(16466, 11)/* AtomicType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(27081, 8)/* Unknown */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {1,IR(0, 0),IR(27539, 5)/* ESSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {2,IR(0, 0),IR(27544, 5)/* GLSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {3,IR(0, 0),IR(27549, 9)/* OpenCL_C */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {4,IR(0, 0),IR(27558, 11)/* OpenCL_CPP */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {5,IR(0, 0),IR(27569, 5)/* HLSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {6,IR(0, 0),IR(27574, 15)/* CPP_for_OpenCL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {7,IR(0, 0),IR(27589, 5)/* SYCL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {8,IR(0, 0),IR(27594, 7)/* HERO_C */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {9,IR(0, 0),IR(27601, 5)/* NZSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {10,IR(0, 0),IR(27606, 5)/* WGSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {11,IR(0, 0),IR(27611, 6)/* Slang */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {12,IR(0, 0),IR(27617, 4)/* Zig */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {13,IR(0, 0),IR(27621, 5)/* Rust */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {0,IR(0, 0),IR(27626, 16)/* UniformConstant */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {1,IR(0, 0),IR(27642, 6)/* Input */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {2,IR(0, 0),IR(17306, 8)/* Uniform */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {3,IR(0, 0),IR(27648, 7)/* Output */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4,IR(0, 0),IR(27393, 10)/* Workgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5,IR(0, 0),IR(27655, 15)/* CrossWorkgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {6,IR(0, 0),IR(27670, 8)/* Private */,IR(0, 0),IR(204, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {7,IR(0, 0),IR(27678, 9)/* Function */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {8,IR(0, 0),IR(27687, 8)/* Generic */,IR(0, 0),IR(206, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {9,IR(0, 0),IR(27695, 13)/* PushConstant */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {10,IR(0, 0),IR(27708, 14)/* AtomicCounter */,IR(0, 0),IR(83, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {11,IR(0, 0),IR(27722, 6)/* Image */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {12,IR(0, 0),IR(27728, 14)/* StorageBuffer */,IR(0, 0),IR(3, 1),IR(196, 2),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4172,IR(0, 0),IR(27742, 13)/* TileImageEXT */,IR(0, 0),IR(154, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4491,IR(0, 0),IR(27755, 19)/* TileAttachmentQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5068,IR(0, 0),IR(27774, 16)/* NodePayloadAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5328,IR(0, 0),IR(27790, 16)/* CallableDataKHR */,IR(162, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5329,IR(0, 0),IR(27821, 24)/* IncomingCallableDataKHR */,IR(163, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5338,IR(0, 0),IR(27868, 14)/* RayPayloadKHR */,IR(164, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5339,IR(0, 0),IR(27895, 16)/* HitAttributeKHR */,IR(165, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5342,IR(0, 0),IR(27926, 22)/* IncomingRayPayloadKHR */,IR(166, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5343,IR(0, 0),IR(27969, 22)/* ShaderRecordBufferKHR */,IR(167, 1),IR(55, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5349,IR(0, 0),IR(28012, 22)/* PhysicalStorageBuffer */,IR(168, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5385,IR(0, 0),IR(28059, 21)/* HitObjectAttributeNV */,IR(0, 0),IR(132, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5402,IR(0, 0),IR(28080, 24)/* TaskPayloadWorkgroupEXT */,IR(0, 0),IR(54, 1),IR(23, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5411,IR(0, 0),IR(28104, 22)/* HitObjectAttributeEXT */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5605,IR(0, 0),IR(28126, 17)/* CodeSectionINTEL */,IR(0, 0),IR(207, 1),IR(104, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5936,IR(0, 0),IR(28143, 17)/* DeviceOnlyALTERA */,IR(169, 1),IR(208, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5937,IR(0, 0),IR(28176, 15)/* HostOnlyALTERA */,IR(170, 1),IR(208, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {0,IR(0, 0),IR(25031, 14)/* UncachedINTEL */,IR(0, 0),IR(153, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {1,IR(0, 0),IR(28205, 18)/* WriteThroughINTEL */,IR(0, 0),IR(153, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {2,IR(0, 0),IR(28223, 15)/* WriteBackINTEL */,IR(0, 0),IR(153, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {3,IR(0, 0),IR(25057, 15)/* StreamingINTEL */,IR(0, 0),IR(153, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {0,IR(0, 0),IR(16017, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {1,IR(10, 1),IR(28238, 11)/* TensorView */,IR(0, 0),IR(209, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {2,IR(10, 1),IR(28249, 11)/* DecodeFunc */,IR(0, 0),IR(210, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {0,IR(0, 0),IR(28260, 10)/* Undefined */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {1,IR(0, 0),IR(17264, 9)/* Constant */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {2,IR(0, 0),IR(27026, 12)/* ClampToEdge */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {3,IR(0, 0),IR(27044, 7)/* Repeat */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {4,IR(0, 0),IR(27051, 15)/* RepeatMirrored */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {0,IR(0, 0),IR(28270, 8)/* NoneARM */,IR(0, 0),IR(211, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {1,IR(0, 0),IR(28278, 15)/* NontemporalARM */,IR(0, 0),IR(211, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {2,IR(10, 1),IR(28293, 20)/* OutOfBoundsValueARM */,IR(0, 0),IR(211, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {4,IR(10, 1),IR(28313, 24)/* MakeElementAvailableARM */,IR(0, 0),IR(211, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {8,IR(10, 1),IR(28337, 22)/* MakeElementVisibleARM */,IR(0, 0),IR(211, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {16,IR(0, 0),IR(28359, 21)/* NonPrivateElementARM */,IR(0, 0),IR(211, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
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
    case SPV_OPERAND_TYPE_CAPABILITY: return IR(135, 287);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(422, 8);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(430, 3);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(433, 2);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS: return IR(435, 19);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION: return IR(454, 10);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(464, 4);
    case SPV_OPERAND_TYPE_COMPONENT_TYPE: return IR(468, 15);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT: return IR(483, 4);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS: return IR(487, 6);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE: return IR(493, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE: return IR(496, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT: return IR(499, 4);
    case SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(503, 8);
    case SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE: return IR(511, 3);
    case SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS: return IR(514, 16);
    case SPV_OPERAND_TYPE_DEBUG_OPERATION: return IR(530, 9);
    case SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER: return IR(539, 3);
    case SPV_OPERAND_TYPE_DECORATION: return IR(542, 150);
    case SPV_OPERAND_TYPE_DIMENSIONALITY: return IR(692, 8);
    case SPV_OPERAND_TYPE_EXECUTION_MODE: return IR(700, 98);
    case SPV_OPERAND_TYPE_EXECUTION_MODEL: return IR(798, 17);
    case SPV_OPERAND_TYPE_FPDENORM_MODE: return IR(815, 2);
    case SPV_OPERAND_TYPE_FPENCODING: return IR(817, 3);
    case SPV_OPERAND_TYPE_FPOPERATION_MODE: return IR(820, 2);
    case SPV_OPERAND_TYPE_FP_FAST_MATH_MODE: return IR(822, 9);
    case SPV_OPERAND_TYPE_FP_ROUNDING_MODE: return IR(831, 4);
    case SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE: return IR(835, 4);
    case SPV_OPERAND_TYPE_FUNCTION_CONTROL: return IR(839, 6);
    case SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE: return IR(845, 9);
    case SPV_OPERAND_TYPE_GROUP_OPERATION: return IR(854, 7);
    case SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER: return IR(861, 4);
    case SPV_OPERAND_TYPE_IMAGE: return IR(865, 17);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE: return IR(882, 26);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER: return IR(908, 20);
    case SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER: return IR(928, 2);
    case SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS: return IR(930, 3);
    case SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO: return IR(933, 2);
    case SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS: return IR(935, 2);
    case SPV_OPERAND_TYPE_LINKAGE_TYPE: return IR(937, 3);
    case SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL: return IR(940, 5);
    case SPV_OPERAND_TYPE_LOOP_CONTROL: return IR(945, 20);
    case SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(965, 15);
    case SPV_OPERAND_TYPE_MEMORY_ACCESS: return IR(980, 9);
    case SPV_OPERAND_TYPE_MEMORY_MODEL: return IR(989, 4);
    case SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID: return IR(993, 15);
    case SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS: return IR(1008, 1);
    case SPV_OPERAND_TYPE_OVERFLOW_MODES: return IR(1009, 4);
    case SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT: return IR(1013, 1);
    case SPV_OPERAND_TYPE_QUANTIZATION_MODES: return IR(1014, 8);
    case SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS: return IR(1022, 3);
    case SPV_OPERAND_TYPE_RAY_FLAGS: return IR(1025, 12);
    case SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE: return IR(1037, 2);
    case SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE: return IR(1039, 3);
    case SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION: return IR(1042, 2);
    case SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE: return IR(1044, 5);
    case SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE: return IR(1049, 2);
    case SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT: return IR(1051, 42);
    case SPV_OPERAND_TYPE_SCOPE_ID: return IR(1093, 7);
    case SPV_OPERAND_TYPE_SELECTION_CONTROL: return IR(1100, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS: return IR(1103, 1);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(1104, 8);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(1112, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(1115, 2);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS: return IR(1117, 20);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION: return IR(1137, 10);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(1147, 4);
    case SPV_OPERAND_TYPE_SOURCE_LANGUAGE: return IR(1151, 14);
    case SPV_OPERAND_TYPE_STORAGE_CLASS: return IR(1165, 29);
    case SPV_OPERAND_TYPE_STORE_CACHE_CONTROL: return IR(1194, 4);
    case SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS: return IR(1198, 3);
    case SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE: return IR(1201, 5);
    case SPV_OPERAND_TYPE_TENSOR_OPERANDS: return IR(1206, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_IMAGE: return IR(865, 17);
    case SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS: return IR(980, 9);
    case SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT: return IR(1013, 1);
    case SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS: return IR(487, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(965, 15);
    case SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS: return IR(1022, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_FPENCODING: return IR(817, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS: return IR(1206, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_CAPABILITY: return IR(135, 287);
    default: break;
  }
  return IR(0,0);
}

// Operand names and index into kOperandsByValue, ordered by (operand kind, name)
// The fields in order are:
//   name, either the primary name or an alias, indexing into kStrings
//   index into the kOperandsByValue array
static const std::array<NameIndex, 1387> kOperandNames{{
  {IR(5546, 9), 0}, // 0 ReadOnly in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(5572, 10), 2}, // 1 ReadWrite in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(5562, 10), 1}, // 2 WriteOnly in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(5582, 8), 3}, // 3 Logical in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5590, 11), 4}, // 4 Physical32 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5611, 11), 5}, // 5 Physical64 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5622, 24), 6}, // 6 PhysicalStorageBuffer64 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(5646, 27), 6}, // 7 PhysicalStorageBuffer64EXT in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(7605, 13), 94}, // 8 BaryCoordKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7618, 12), 94}, // 9 BaryCoordNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6951, 20), 68}, // 10 BaryCoordNoPerspAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6971, 28), 69}, // 11 BaryCoordNoPerspCentroidAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7653, 20), 95}, // 12 BaryCoordNoPerspKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7673, 19), 95}, // 13 BaryCoordNoPerspNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6999, 26), 70}, // 14 BaryCoordNoPerspSampleAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7096, 22), 74}, // 15 BaryCoordPullModelAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7025, 19), 71}, // 16 BaryCoordSmoothAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7044, 27), 72}, // 17 BaryCoordSmoothCentroidAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7071, 25), 73}, // 18 BaryCoordSmoothSampleAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6755, 13), 59}, // 19 BaseInstance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6729, 11), 58}, // 20 BaseVertex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5730, 13), 9}, // 21 ClipDistance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7512, 22), 89}, // 22 ClipDistancePerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8811, 12), 133}, // 23 ClusterIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6493, 13), 49}, // 24 CoreCountARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6467, 10), 48}, // 25 CoreIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6506, 13), 50}, // 26 CoreMaxIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5743, 13), 10}, // 27 CullDistance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7534, 22), 90}, // 28 CullDistancePerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8864, 12), 134}, // 29 CullMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7860, 17), 101}, // 30 CullPrimitiveEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8264, 17), 115}, // 31 CurrentRayTimeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6825, 12), 62}, // 32 DeviceIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6768, 10), 60}, // 33 DrawIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6257, 22), 37}, // 34 EnqueuedWorkgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6027, 10), 21}, // 35 FragCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6113, 10), 27}, // 36 FragDepth in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7738, 23), 97}, // 37 FragInvocationCountEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7692, 12), 96}, // 38 FragSizeEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7118, 18), 75}, // 39 FragStencilRefEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7704, 15), 96}, // 40 FragmentSizeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6048, 12), 23}, // 41 FrontFacing in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7424, 16), 85}, // 42 FullyCoveredEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6198, 19), 33}, // 43 GlobalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6292, 15), 39}, // 44 GlobalLinearId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6279, 13), 38}, // 45 GlobalOffset in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6246, 11), 36}, // 46 GlobalSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6123, 17), 28}, // 47 HelperInvocation in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8566, 11), 122}, // 48 HitIsLSSNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8524, 14), 121}, // 49 HitIsSphereNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8746, 33), 130}, // 50 HitKindBackFacingMicroTriangleNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8712, 34), 129}, // 51 HitKindFrontFacingMicroTriangleNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8243, 11), 114}, // 52 HitKindKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8254, 10), 114}, // 53 HitKindNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8694, 18), 128}, // 54 HitLSSPositionsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8797, 14), 132}, // 55 HitLSSRadiiNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8428, 37), 118}, // 56 HitMicroTriangleVertexBarycentricsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8361, 34), 117}, // 57 HitMicroTriangleVertexPositionsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8616, 20), 123}, // 58 HitSpherePositionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8779, 18), 131}, // 59 HitSphereRadiusNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8236, 7), 113}, // 60 HitTNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8304, 30), 116}, // 61 HitTriangleVertexPositionsKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8465, 20), 119}, // 62 IncomingRayFlagsKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8485, 19), 119}, // 63 IncomingRayFlagsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8125, 23), 110}, // 64 InstanceCustomIndexKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8148, 22), 110}, // 65 InstanceCustomIndexNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5765, 11), 12}, // 66 InstanceId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6453, 14), 47}, // 67 InstanceIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5866, 13), 14}, // 68 InvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7761, 22), 97}, // 69 InvocationsPerPixelNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7877, 12), 102}, // 70 LaunchIdKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7889, 11), 102}, // 71 LaunchIdNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7900, 14), 103}, // 72 LaunchSizeKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7914, 13), 103}, // 73 LaunchSizeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5879, 6), 15}, // 74 Layer in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7556, 15), 91}, // 75 LayerPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6180, 18), 32}, // 76 LocalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6217, 21), 34}, // 77 LocalInvocationIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7571, 16), 92}, // 78 MeshViewCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7587, 18), 93}, // 79 MeshViewIndicesNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6383, 21), 43}, // 80 NumEnqueuedSubgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6370, 13), 42}, // 81 NumSubgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6140, 14), 29}, // 82 NumWorkgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8040, 22), 107}, // 83 ObjectRayDirectionKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8062, 21), 107}, // 84 ObjectRayDirectionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8003, 19), 106}, // 85 ObjectRayOriginKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8022, 18), 106}, // 86 ObjectRayOriginNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8170, 17), 111}, // 87 ObjectToWorldKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8187, 16), 111}, // 88 ObjectToWorldNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6013, 14), 20}, // 89 PatchVertices in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6037, 11), 22}, // 90 PointCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5720, 10), 8}, // 91 PointSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5704, 9), 7}, // 92 Position in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7364, 18), 83}, // 93 PositionPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7476, 17), 87}, // 94 PrimitiveCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5776, 12), 13}, // 95 PrimitiveId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7493, 19), 88}, // 96 PrimitiveIndicesNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7808, 24), 99}, // 97 PrimitiveLineIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7783, 25), 98}, // 98 PrimitivePointIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6778, 24), 61}, // 99 PrimitiveShadingRateKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7832, 28), 100}, // 100 PrimitiveTriangleIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8504, 20), 120}, // 101 RayGeometryIndexKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8104, 11), 109}, // 102 RayTmaxKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8115, 10), 109}, // 103 RayTmaxNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8083, 11), 108}, // 104 RayTminKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8094, 10), 108}, // 105 RayTminNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7153, 29), 76}, // 106 RemainingRecursionLevelsAMDX in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7249, 16), 79}, // 107 ResourceHeapEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8668, 10), 125}, // 108 SMCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8687, 7), 127}, // 109 SMIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6060, 9), 24}, // 110 SampleId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6102, 11), 26}, // 111 SampleMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6087, 15), 25}, // 112 SamplePosition in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7216, 15), 78}, // 113 SamplerHeapEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7301, 20), 81}, // 114 SecondaryPositionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7340, 24), 82}, // 115 SecondaryViewportMaskNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7200, 16), 77}, // 116 ShaderIndexAMDX in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6869, 15), 64}, // 117 ShadingRateKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6542, 15), 53}, // 118 SubgroupEqMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6557, 18), 53}, // 119 SubgroupEqMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6597, 15), 54}, // 120 SubgroupGeMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6612, 18), 54}, // 121 SubgroupGeMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6630, 15), 55}, // 122 SubgroupGtMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6645, 18), 55}, // 123 SubgroupGtMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6404, 11), 44}, // 124 SubgroupId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6663, 15), 56}, // 125 SubgroupLeMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6678, 18), 56}, // 126 SubgroupLeMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6415, 26), 45}, // 127 SubgroupLocalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6696, 15), 57}, // 128 SubgroupLtMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6711, 18), 57}, // 129 SubgroupLtMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6354, 16), 41}, // 130 SubgroupMaxSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6307, 13), 40}, // 131 SubgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7464, 12), 86}, // 132 TaskCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6003, 10), 19}, // 133 TessCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5988, 15), 18}, // 134 TessLevelInner in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5973, 15), 17}, // 135 TessLevelOuter in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6933, 18), 67}, // 136 TileApronSizeQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6915, 18), 66}, // 137 TileDimensionQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6884, 15), 65}, // 138 TileOffsetQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5756, 9), 11}, // 139 VertexId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6441, 12), 46}, // 140 VertexIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6849, 10), 63}, // 141 ViewIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5925, 14), 16}, // 142 ViewportIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7265, 15), 80}, // 143 ViewportMaskNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7402, 22), 84}, // 144 ViewportMaskPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6519, 10), 51}, // 145 WarpIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8678, 9), 126}, // 146 WarpIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6529, 13), 52}, // 147 WarpMaxIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8636, 13), 124}, // 148 WarpsPerSMNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6238, 8), 35}, // 149 WorkDim in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6168, 12), 31}, // 150 WorkgroupId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6154, 14), 30}, // 151 WorkgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7962, 21), 105}, // 152 WorldRayDirectionKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7983, 20), 105}, // 153 WorldRayDirectionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7927, 18), 104}, // 154 WorldRayOriginKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7945, 17), 104}, // 155 WorldRayOriginNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8203, 17), 112}, // 156 WorldToObjectKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(8220, 16), 112}, // 157 WorldToObjectNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(11082, 9), 266}, // 158 AbortKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5601, 10), 139}, // 159 Addresses in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14312, 35), 369}, // 160 ArbitraryPrecisionFixedPointALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14347, 34), 369}, // 161 ArbitraryPrecisionFixedPointINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13784, 38), 357}, // 162 ArbitraryPrecisionFloatingPointALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13822, 37), 357}, // 163 ArbitraryPrecisionFloatingPointINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13719, 33), 356}, // 164 ArbitraryPrecisionIntegersALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13752, 32), 356}, // 165 ArbitraryPrecisionIntegersINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15006, 19), 394}, // 166 ArithmeticFenceEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13357, 9), 342}, // 167 AsmINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14923, 20), 390}, // 168 AtomicFloat16AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13412, 23), 345}, // 169 AtomicFloat16MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12828, 22), 317}, // 170 AtomicFloat16VectorNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14839, 20), 386}, // 171 AtomicFloat32AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13366, 23), 343}, // 172 AtomicFloat32MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14859, 20), 387}, // 173 AtomicFloat64AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13389, 23), 344}, // 174 AtomicFloat64MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9044, 14), 155}, // 175 AtomicStorage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10431, 17), 231}, // 176 AtomicStorageOps in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14964, 24), 392}, // 177 BFloat16ConversionINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11053, 29), 265}, // 178 BFloat16CooperativeMatrixKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11031, 22), 264}, // 179 BFloat16DotProductKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11015, 16), 263}, // 180 BFloat16TypeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15741, 20), 417}, // 181 BindlessImagesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12765, 18), 314}, // 182 BindlessTextureNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14776, 16), 382}, // 183 BitInstructions in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14514, 20), 373}, // 184 BlockingPipesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14534, 19), 373}, // 185 BlockingPipesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15702, 19), 415}, // 186 CacheControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5730, 13), 165}, // 187 ClipDistance in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12396, 32), 302}, // 188 ComputeDerivativeGroupLinearKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12428, 31), 302}, // 189 ComputeDerivativeGroupLinearNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11246, 31), 281}, // 190 ComputeDerivativeGroupQuadsKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11277, 30), 281}, // 191 ComputeDerivativeGroupQuadsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11091, 16), 268}, // 192 ConstantDataKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13062, 30), 329}, // 193 CooperativeMatrixBlockLoadsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10800, 32), 250}, // 194 CooperativeMatrixConversionQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12955, 31), 326}, // 195 CooperativeMatrixConversionsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10079, 21), 380}, // 196 CooperativeMatrixKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10014, 28), 213}, // 197 CooperativeMatrixLayoutsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12484, 20), 304}, // 198 CooperativeMatrixNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12986, 40), 327}, // 199 CooperativeMatrixPerElementOperationsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12925, 30), 325}, // 200 CooperativeMatrixReductionsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13026, 36), 328}, // 201 CooperativeMatrixTensorAddressingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12808, 20), 316}, // 202 CooperativeVectorNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13092, 28), 330}, // 203 CooperativeVectorTrainingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6477, 16), 205}, // 204 CoreBuiltinsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5743, 13), 166}, // 205 CullDistance in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14943, 21), 391}, // 206 DebugInfoModuleINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12607, 25), 309}, // 207 DemoteToHelperInvocation in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12632, 28), 309}, // 208 DemoteToHelperInvocationEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10570, 18), 237}, // 209 DenormFlushToZero in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10555, 15), 236}, // 210 DenormPreserve in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9491, 18), 184}, // 211 DerivativeControl in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7231, 18), 267}, // 212 DescriptorHeapEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9015, 14), 153}, // 213 DeviceEnqueue in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6837, 12), 227}, // 214 DeviceGroup in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12660, 23), 310}, // 215 DisplacementMicromapNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14727, 11), 378}, // 216 DotProduct in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15827, 27), 420}, // 217 DotProductBFloat16AccVALVE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15794, 33), 419}, // 218 DotProductFloat16AccFloat16VALVE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15761, 33), 418}, // 219 DotProductFloat16AccFloat32VALVE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15854, 32), 421}, // 220 DotProductFloat8AccFloat32VALVE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14621, 22), 376}, // 221 DotProductInput4x8Bit in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14643, 25), 376}, // 222 DotProductInput4x8BitKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14668, 28), 377}, // 223 DotProductInput4x8BitPacked in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14696, 31), 377}, // 224 DotProductInput4x8BitPackedKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14580, 19), 375}, // 225 DotProductInputAll in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14599, 22), 375}, // 226 DotProductInputAllKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14738, 14), 378}, // 227 DotProductKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6740, 15), 218}, // 228 DrawParameters in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13469, 16), 348}, // 229 ExpectAssumeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14832, 7), 385}, // 230 FMAKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13699, 20), 355}, // 231 FPFastMathModeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15214, 29), 400}, // 232 FPGAArgumentInterfacesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15243, 28), 400}, // 233 FPGAArgumentInterfacesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14263, 25), 368}, // 234 FPGABufferLocationALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14288, 24), 368}, // 235 FPGABufferLocationINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14031, 28), 363}, // 236 FPGAClusterAttributesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14059, 27), 363}, // 237 FPGAClusterAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15025, 30), 395}, // 238 FPGAClusterAttributesV2ALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15055, 29), 395}, // 239 FPGAClusterAttributesV2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14115, 21), 365}, // 240 FPGADSPControlALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14136, 20), 365}, // 241 FPGADSPControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14182, 41), 367}, // 242 FPGAInvocationPipeliningAttributesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14223, 40), 367}, // 243 FPGAInvocationPipeliningAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13956, 26), 361}, // 244 FPGAKernelAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15084, 28), 396}, // 245 FPGAKernelAttributesv2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15165, 25), 399}, // 246 FPGALatencyControlALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15190, 24), 399}, // 247 FPGALatencyControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13889, 23), 359}, // 248 FPGALoopControlsALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13912, 22), 359}, // 249 FPGALoopControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13982, 25), 362}, // 250 FPGAMemoryAccessesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14007, 24), 362}, // 251 FPGAMemoryAccessesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13646, 27), 354}, // 252 FPGAMemoryAttributesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13673, 26), 354}, // 253 FPGAMemoryAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14553, 14), 374}, // 254 FPGARegALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14567, 13), 374}, // 255 FPGARegINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15149, 16), 398}, // 256 FPMaxErrorINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8929, 8), 144}, // 257 Float16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8915, 14), 143}, // 258 Float16Buffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10855, 16), 252}, // 259 Float16ImageAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8937, 8), 145}, // 260 Float64 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10052, 27), 215}, // 261 Float8CooperativeMatrixEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10042, 10), 214}, // 262 Float8EXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14817, 15), 384}, // 263 FloatControls2 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13265, 23), 338}, // 264 FloatingPointModeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7630, 23), 280}, // 265 FragmentBarycentricKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11224, 22), 280}, // 266 FragmentBarycentricNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7719, 19), 282}, // 267 FragmentDensityEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7440, 24), 276}, // 268 FragmentFullyCoveredEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10893, 16), 254}, // 269 FragmentMaskAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12575, 32), 308}, // 270 FragmentShaderPixelInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12504, 33), 305}, // 271 FragmentShaderSampleInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12537, 38), 306}, // 272 FragmentShaderShadingRateInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6802, 23), 216}, // 273 FragmentShadingRateKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13620, 26), 353}, // 274 FunctionFloatControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13311, 22), 340}, // 275 FunctionPointersINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15602, 22), 411}, // 276 FunctionVariantsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9336, 15), 171}, // 277 GenericPointer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5788, 9), 137}, // 278 Geometry in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9086, 18), 158}, // 279 GeometryPointSize in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11152, 28), 271}, // 280 GeometryShaderPassthroughNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9549, 16), 187}, // 281 GeometryStreams in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15301, 36), 402}, // 282 GlobalVariableFPGADecorationsALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15337, 35), 402}, // 283 GlobalVariableFPGADecorationsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15271, 30), 401}, // 284 GlobalVariableHostAccessINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10005, 9), 212}, // 285 GraphARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6320, 16), 194}, // 286 GroupNonUniform in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9688, 26), 196}, // 287 GroupNonUniformArithmetic in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6575, 22), 197}, // 288 GroupNonUniformBallot in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9768, 25), 200}, // 289 GroupNonUniformClustered in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11321, 30), 283}, // 290 GroupNonUniformPartitionedEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11351, 29), 283}, // 291 GroupNonUniformPartitionedNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9793, 20), 201}, // 292 GroupNonUniformQuad in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14792, 25), 383}, // 293 GroupNonUniformRotateKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9714, 23), 198}, // 294 GroupNonUniformShuffle in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9737, 31), 199}, // 295 GroupNonUniformShuffleRelative in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9668, 20), 195}, // 296 GroupNonUniformVote in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15624, 26), 412}, // 297 GroupUniformArithmeticKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9008, 7), 152}, // 298 Groups in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14487, 14), 372}, // 299 IOPipesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14501, 13), 372}, // 300 IOPipesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9405, 8), 177}, // 301 Image1D in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8964, 11), 148}, // 302 ImageBasic in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9427, 12), 180}, // 303 ImageBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9282, 15), 167}, // 304 ImageCubeArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11207, 17), 278}, // 305 ImageFootprintNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10871, 22), 253}, // 306 ImageGatherBiasLodAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9104, 20), 159}, // 307 ImageGatherExtended in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9439, 13), 181}, // 308 ImageMSArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8990, 12), 150}, // 309 ImageMipmap in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9480, 11), 183}, // 310 ImageQuery in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8975, 15), 149}, // 311 ImageReadWrite in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10909, 21), 256}, // 312 ImageReadWriteLodAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9314, 10), 169}, // 313 ImageRect in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13333, 24), 341}, // 314 IndirectReferencesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9356, 16), 173}, // 315 InputAttachment in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11466, 36), 286}, // 316 InputAttachmentArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11502, 39), 286}, // 317 InputAttachmentArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12007, 39), 293}, // 318 InputAttachmentArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12046, 42), 293}, // 319 InputAttachmentArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9058, 6), 156}, // 320 Int16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10988, 27), 262}, // 321 Int4CooperativeMatrixINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10974, 14), 261}, // 322 Int4TypeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8945, 6), 146}, // 323 Int64 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8951, 13), 147}, // 324 Int64Atomics in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10930, 14), 257}, // 325 Int64ImageEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9351, 5), 172}, // 326 Int8 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13288, 23), 339}, // 327 IntegerFunctions2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9509, 22), 185}, // 328 InterpolationFunction in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5555, 7), 141}, // 329 Kernel in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13934, 22), 360}, // 330 KernelAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8898, 8), 140}, // 331 Linkage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9029, 15), 154}, // 332 LiteralSampler in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14879, 20), 388}, // 333 LongCompositesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12888, 14), 323}, // 334 LongVectorEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14086, 15), 364}, // 335 LoopFuseALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14101, 14), 364}, // 336 LoopFuseINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15677, 25), 414}, // 337 MaskedGatherScatterINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8891, 7), 135}, // 338 Matrix in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14156, 26), 366}, // 339 MemoryAccessAliasingINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5851, 15), 279}, // 340 MeshShadingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5837, 14), 277}, // 341 MeshShadingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9388, 7), 175}, // 342 MinLod in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6859, 10), 228}, // 343 MultiView in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5939, 14), 190}, // 344 MultiViewport in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9643, 13), 192}, // 345 NamedBarrier in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14899, 11), 389}, // 346 OptNoneEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14910, 13), 389}, // 347 OptNoneINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7382, 20), 275}, // 348 PerViewAttributesNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5673, 31), 301}, // 349 PhysicalStorageBufferAddresses in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12362, 34), 301}, // 350 PhysicalStorageBufferAddressesEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9656, 12), 193}, // 351 PipeStorage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9002, 6), 151}, // 352 Pipes in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11107, 16), 269}, // 353 PoisonFreezeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12868, 20), 322}, // 354 PushConstantBanksNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10959, 15), 260}, // 355 QuadControlKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12850, 18), 319}, // 356 RawAccessChainsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8876, 15), 379}, // 357 RayCullMaskKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10668, 12), 242}, // 358 RayQueryKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12783, 25), 315}, // 359 RayQueryPositionFetchKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10645, 23), 241}, // 360 RayQueryProvisionalKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8823, 41), 331}, // 361 RayTracingClusterAccelerationStructureNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8395, 33), 318}, // 362 RayTracingDisplacementMicromapNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5823, 14), 245}, // 363 RayTracingKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8577, 39), 321}, // 364 RayTracingLinearSweptSpheresGeometryNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8281, 23), 298}, // 365 RayTracingMotionBlurNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5810, 13), 297}, // 366 RayTracingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12683, 29), 311}, // 367 RayTracingOpacityMicromapEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8334, 27), 296}, // 368 RayTracingPositionFetchKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12459, 25), 303}, // 369 RayTracingProvisionalKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8538, 28), 320}, // 370 RayTracingSpheresGeometryNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10699, 32), 244}, // 371 RayTraversalPrimitiveCullingKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15721, 20), 416}, // 372 RegisterLimitsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14752, 24), 381}, // 373 ReplicatedCompositesEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13244, 21), 337}, // 374 RoundToInfinityINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10613, 16), 239}, // 375 RoundingModeRTE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10629, 16), 240}, // 376 RoundingModeRTZ in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14428, 30), 371}, // 377 RuntimeAlignedAttributeALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14458, 29), 371}, // 378 RuntimeAlignedAttributeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11417, 23), 285}, // 379 RuntimeDescriptorArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11440, 26), 285}, // 380 RuntimeDescriptorArrayEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11123, 29), 270}, // 381 SampleMaskOverrideCoverageNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10448, 28), 232}, // 382 SampleMaskPostDepthCoverage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6069, 18), 168}, // 383 SampleRateShading in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9395, 10), 176}, // 384 Sampled1D in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9413, 14), 179}, // 385 SampledBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9297, 17), 178}, // 386 SampledCubeArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9182, 33), 162}, // 387 SampledImageArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11780, 36), 290}, // 388 SampledImageArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11816, 39), 290}, // 389 SampledImageArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9324, 12), 170}, // 390 SampledRect in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5713, 7), 136}, // 391 Shader in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12902, 23), 324}, // 392 Shader64BitIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10944, 15), 258}, // 393 ShaderClockKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7182, 18), 259}, // 394 ShaderEnqueueAMDX in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12738, 27), 313}, // 395 ShaderInvocationReorderEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12712, 26), 312}, // 396 ShaderInvocationReorderNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5885, 12), 202}, // 397 ShaderLayer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11380, 17), 284}, // 398 ShaderNonUniform in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11397, 20), 284}, // 399 ShaderNonUniformEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8649, 19), 307}, // 400 ShaderSMBuiltinsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7321, 19), 274}, // 401 ShaderStereoViewNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5953, 20), 203}, // 402 ShaderViewportIndex in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5897, 28), 272}, // 403 ShaderViewportIndexLayerEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11180, 27), 272}, // 404 ShaderViewportIndexLayerNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7280, 21), 273}, // 405 ShaderViewportMaskNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11307, 14), 282}, // 406 ShadingRateNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10588, 25), 238}, // 407 SignedZeroInfNanPreserve in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9372, 16), 174}, // 408 SparseResidency in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15581, 21), 410}, // 409 SpecConditionalINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14988, 18), 393}, // 410 SplitBarrierINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7136, 17), 255}, // 411 StencilExportEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10236, 25), 223}, // 412 StorageBuffer16BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10476, 24), 233}, // 413 StorageBuffer8BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9215, 34), 163}, // 414 StorageBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11855, 37), 291}, // 415 StorageBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11892, 40), 291}, // 416 StorageBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9249, 33), 164}, // 417 StorageImageArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11932, 36), 292}, // 418 StorageImageArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11968, 39), 292}, // 419 StorageImageArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9452, 28), 182}, // 420 StorageImageExtendedFormats in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9124, 24), 160}, // 421 StorageImageMultisample in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9565, 30), 188}, // 422 StorageImageReadWithoutFormat in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9595, 31), 189}, // 423 StorageImageWriteWithoutFormat in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10363, 21), 226}, // 424 StorageInputOutput16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10341, 22), 225}, // 425 StoragePushConstant16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10534, 21), 235}, // 426 StoragePushConstant8 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9928, 37), 210}, // 427 StorageTensorArrayDynamicIndexingARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9965, 40), 211}, // 428 StorageTensorArrayNonUniformIndexingARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11622, 39), 288}, // 429 StorageTexelBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11661, 42), 288}, // 430 StorageTexelBufferArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12175, 42), 295}, // 431 StorageTexelBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12217, 45), 295}, // 432 StorageTexelBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10324, 17), 224}, // 433 StorageUniform16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10261, 28), 223}, // 434 StorageUniformBufferBlock16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15400, 23), 404}, // 435 Subgroup2DBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15423, 30), 405}, // 436 Subgroup2DBlockTransformINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15453, 30), 406}, // 437 Subgroup2DBlockTransposeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13556, 39), 351}, // 438 SubgroupAvcMotionEstimationChromaINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13485, 33), 349}, // 439 SubgroupAvcMotionEstimationINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13518, 38), 350}, // 440 SubgroupAvcMotionEstimationIntraINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6336, 18), 217}, // 441 SubgroupBallotKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13160, 27), 334}, // 442 SubgroupBufferBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15372, 28), 403}, // 443 SubgroupBufferPrefetchINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9626, 17), 191}, // 444 SubgroupDispatch in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13187, 26), 335}, // 445 SubgroupImageBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13213, 31), 336}, // 446 SubgroupImageMediaBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15483, 38), 407}, // 447 SubgroupMatrixMultiplyAccumulateINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13139, 21), 333}, // 448 SubgroupShuffleINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10220, 16), 222}, // 449 SubgroupVoteKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15112, 19), 397}, // 450 TaskSequenceALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15131, 18), 397}, // 451 TaskSequenceINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13120, 19), 332}, // 452 TensorAddressingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15650, 27), 413}, // 453 TensorFloat32RoundingINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9917, 11), 209}, // 454 TensorsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15521, 28), 408}, // 455 TernaryBitwiseFunctionINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5797, 13), 138}, // 456 Tessellation in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9064, 22), 157}, // 457 TessellationPointSize in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10832, 23), 251}, // 458 TextureBlockMatch2QCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10778, 22), 248}, // 459 TextureBlockMatchQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10757, 21), 247}, // 460 TextureBoxFilterQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10731, 26), 246}, // 461 TextureSampleWeightedQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9831, 28), 206}, // 462 TileImageColorReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9859, 28), 207}, // 463 TileImageDepthReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9887, 30), 208}, // 464 TileImageStencilReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6899, 16), 249}, // 465 TileShadingQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9531, 18), 186}, // 466 TransformFeedback in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14381, 24), 370}, // 467 USMStorageClassesALTERA in SPV_OPERAND_TYPE_CAPABILITY
  {IR(14405, 23), 370}, // 468 USMStorageClassesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10289, 35), 224}, // 469 UniformAndStorageBuffer16BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10500, 34), 234}, // 470 UniformAndStorageBuffer8BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9148, 34), 161}, // 471 UniformBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11703, 37), 289}, // 472 UniformBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11740, 40), 289}, // 473 UniformBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9813, 18), 204}, // 474 UniformDecoration in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11541, 39), 287}, // 475 UniformTexelBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11580, 42), 287}, // 476 UniformTexelBufferArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12088, 42), 294}, // 477 UniformTexelBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12130, 45), 294}, // 478 UniformTexelBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13859, 30), 358}, // 479 UnstructuredLoopControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10680, 19), 243}, // 480 UntypedPointersKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15549, 32), 409}, // 481 UntypedVariableLengthArrayINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13595, 25), 352}, // 482 VariableLengthArrayINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10414, 17), 230}, // 483 VariablePointers in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10384, 30), 229}, // 484 VariablePointersStorageBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8906, 9), 142}, // 485 Vector16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13454, 15), 347}, // 486 VectorAnyINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13435, 19), 346}, // 487 VectorComputeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12262, 18), 299}, // 488 VulkanMemoryModel in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12301, 29), 300}, // 489 VulkanMemoryModelDeviceScope in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12330, 32), 300}, // 490 VulkanMemoryModelDeviceScopeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12280, 21), 299}, // 491 VulkanMemoryModelKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10176, 44), 221}, // 492 WorkgroupMemoryExplicitLayout16BitAccessKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10133, 43), 220}, // 493 WorkgroupMemoryExplicitLayout8BitAccessKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10100, 33), 219}, // 494 WorkgroupMemoryExplicitLayoutKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(15898, 8), 423}, // 495 Address in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15906, 8), 424}, // 496 Boolean in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15914, 6), 425}, // 497 Float in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15920, 7), 426}, // 498 Signed in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15927, 11), 427}, // 499 SignedChar in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15938, 9), 428}, // 500 Unsigned in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15947, 13), 429}, // 501 UnsignedChar in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15886, 12), 422}, // 502 Unspecified in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15960, 6), 430}, // 503 Class in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15966, 10), 431}, // 504 Structure in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15976, 6), 432}, // 505 Union in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15997, 20), 434}, // 506 ImportedDeclaration in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(15982, 15), 433}, // 507 ImportedModule in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(16106, 15), 442}, // 508 FlagArtificial in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16121, 13), 443}, // 509 FlagExplicit in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16094, 12), 441}, // 510 FlagFwdDecl in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16184, 21), 447}, // 511 FlagIndirectVariable in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16077, 17), 440}, // 512 FlagIsDefinition in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16261, 16), 451}, // 513 FlagIsEnumClass in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16065, 12), 439}, // 514 FlagIsLocal in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16245, 16), 450}, // 515 FlagIsOptimized in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16038, 14), 437}, // 516 FlagIsPrivate in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16022, 16), 436}, // 517 FlagIsProtected in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16052, 13), 438}, // 518 FlagIsPublic in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16205, 20), 448}, // 519 FlagLValueReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16149, 18), 445}, // 520 FlagObjectPointer in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16134, 15), 444}, // 521 FlagPrototyped in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16225, 20), 449}, // 522 FlagRValueReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16167, 17), 446}, // 523 FlagStaticMember in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16297, 24), 453}, // 524 FlagTypePassByReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16277, 20), 452}, // 525 FlagTypePassByValue in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16017, 5), 435}, // 526 None in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(16382, 9), 458}, // 527 BitPiece in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16414, 7), 462}, // 528 Constu in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16321, 6), 454}, // 529 Deref in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16421, 9), 463}, // 530 Fragment in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16332, 6), 456}, // 531 Minus in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16327, 5), 455}, // 532 Plus in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16371, 11), 457}, // 533 PlusUconst in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16403, 11), 461}, // 534 StackValue in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16391, 5), 459}, // 535 Swap in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16396, 7), 460}, // 536 Xderef in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(16466, 11), 467}, // 537 AtomicType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16430, 10), 464}, // 538 ConstType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16453, 13), 466}, // 539 RestrictType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16440, 13), 465}, // 540 VolatileType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16477, 10), 468}, // 541 Float16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16487, 10), 469}, // 542 Float32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16497, 10), 470}, // 543 Float64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16665, 12), 481}, // 544 FloatE4M3NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16677, 12), 482}, // 545 FloatE5M2NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16520, 14), 472}, // 546 SignedInt16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16534, 14), 473}, // 547 SignedInt32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16548, 14), 474}, // 548 SignedInt64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16507, 13), 471}, // 549 SignedInt8NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16625, 19), 479}, // 550 SignedInt8PackedNV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16577, 16), 476}, // 551 UnsignedInt16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16593, 16), 477}, // 552 UnsignedInt32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16609, 16), 478}, // 553 UnsignedInt64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16562, 15), 475}, // 554 UnsignedInt8NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16644, 21), 480}, // 555 UnsignedInt8PackedNV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(16741, 28), 486}, // 556 ColumnBlockedInterleavedARM in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(16701, 15), 484}, // 557 ColumnMajorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(16716, 25), 485}, // 558 RowBlockedInterleavedARM in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(16689, 12), 483}, // 559 RowMajorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(16777, 27), 488}, // 560 MatrixASignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16804, 27), 489}, // 561 MatrixBSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16831, 27), 490}, // 562 MatrixCSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16858, 32), 491}, // 563 MatrixResultSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16769, 8), 487}, // 564 NoneKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16890, 26), 492}, // 565 SaturatingAccumulationKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(16927, 4), 495}, // 566 2x2 in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(16920, 7), 494}, // 567 Column in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(16916, 4), 493}, // 568 Row in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(16931, 11), 496}, // 569 MatrixAKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(16953, 21), 498}, // 570 MatrixAccumulatorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(16942, 11), 497}, // 571 MatrixBKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(16985, 14), 500}, // 572 ColumnMajorNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(16999, 21), 501}, // 573 InferencingOptimalNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(16974, 11), 499}, // 574 RowMajorNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(17020, 18), 502}, // 575 TrainingOptimalNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(15898, 8), 504}, // 576 Address in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15906, 8), 505}, // 577 Boolean in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15914, 6), 506}, // 578 Float in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15920, 7), 507}, // 579 Signed in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15927, 11), 508}, // 580 SignedChar in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15938, 9), 509}, // 581 Unsigned in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15947, 13), 510}, // 582 UnsignedChar in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15886, 12), 503}, // 583 Unspecified in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15960, 6), 511}, // 584 Class in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(15966, 10), 512}, // 585 Structure in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(15976, 6), 513}, // 586 Union in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(16106, 15), 521}, // 587 FlagArtificial in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16121, 13), 522}, // 588 FlagExplicit in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16094, 12), 520}, // 589 FlagFwdDecl in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16184, 21), 526}, // 590 FlagIndirectVariable in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16077, 17), 519}, // 591 FlagIsDefinition in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16065, 12), 518}, // 592 FlagIsLocal in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16245, 16), 529}, // 593 FlagIsOptimized in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16038, 14), 516}, // 594 FlagIsPrivate in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16022, 16), 515}, // 595 FlagIsProtected in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16052, 13), 517}, // 596 FlagIsPublic in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16205, 20), 527}, // 597 FlagLValueReference in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16149, 18), 524}, // 598 FlagObjectPointer in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16134, 15), 523}, // 599 FlagPrototyped in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16225, 20), 528}, // 600 FlagRValueReference in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16167, 17), 525}, // 601 FlagStaticMember in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16017, 5), 514}, // 602 None in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(16382, 9), 534}, // 603 BitPiece in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16414, 7), 538}, // 604 Constu in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16321, 6), 530}, // 605 Deref in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16332, 6), 532}, // 606 Minus in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16327, 5), 531}, // 607 Plus in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16371, 11), 533}, // 608 PlusUconst in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16403, 11), 537}, // 609 StackValue in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16391, 5), 535}, // 610 Swap in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16396, 7), 536}, // 611 Xderef in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(16430, 10), 539}, // 612 ConstType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(16453, 13), 541}, // 613 RestrictType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(16440, 13), 540}, // 614 VolatileType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(19758, 16), 662}, // 615 AliasScopeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17247, 8), 561}, // 616 Aliased in SPV_OPERAND_TYPE_DECORATION
  {IR(18408, 15), 617}, // 617 AliasedPointer in SPV_OPERAND_TYPE_DECORATION
  {IR(18423, 18), 617}, // 618 AliasedPointerEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(17725, 10), 585}, // 619 Alignment in SPV_OPERAND_TYPE_DECORATION
  {IR(17769, 12), 587}, // 620 AlignmentId in SPV_OPERAND_TYPE_DECORATION
  {IR(17098, 12), 548}, // 621 ArrayStride in SPV_OPERAND_TYPE_DECORATION
  {IR(18149, 17), 604}, // 622 ArrayStrideIdEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(19308, 15), 650}, // 623 BankBitsALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19323, 14), 650}, // 624 BankBitsINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18517, 7), 621}, // 625 BankNV in SPV_OPERAND_TYPE_DECORATION
  {IR(19021, 16), 643}, // 626 BankwidthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19037, 15), 643}, // 627 BankwidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17402, 8), 574}, // 628 Binding in SPV_OPERAND_TYPE_DECORATION
  {IR(18542, 16), 623}, // 629 BindlessImageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18524, 18), 622}, // 630 BindlessSamplerNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17062, 6), 544}, // 631 Block in SPV_OPERAND_TYPE_DECORATION
  {IR(17909, 22), 594}, // 632 BlockMatchSamplerQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(17887, 22), 593}, // 633 BlockMatchTextureQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(18573, 13), 625}, // 634 BoundImageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18558, 15), 624}, // 635 BoundSamplerNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17068, 12), 545}, // 636 BufferBlock in SPV_OPERAND_TYPE_DECORATION
  {IR(19918, 21), 667}, // 637 BufferLocationALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19939, 20), 667}, // 638 BufferLocationINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17179, 8), 553}, // 639 BuiltIn in SPV_OPERAND_TYPE_DECORATION
  {IR(19477, 20), 655}, // 640 BurstCoalesceALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19497, 19), 655}, // 641 BurstCoalesceINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17145, 8), 552}, // 642 CPacked in SPV_OPERAND_TYPE_DECORATION
  {IR(21165, 22), 690}, // 643 CacheControlLoadINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(21224, 23), 691}, // 644 CacheControlStoreINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19516, 16), 656}, // 645 CacheSizeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19532, 15), 656}, // 646 CacheSizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17212, 9), 557}, // 647 Centroid in SPV_OPERAND_TYPE_DECORATION
  {IR(18626, 13), 628}, // 648 ClobberINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17273, 9), 564}, // 649 Coherent in SPV_OPERAND_TYPE_DECORATION
  {IR(17089, 9), 547}, // 650 ColMajor in SPV_OPERAND_TYPE_DECORATION
  {IR(17386, 10), 572}, // 651 Component in SPV_OPERAND_TYPE_DECORATION
  {IR(21112, 17), 689}, // 652 ConditionalINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20341, 28), 677}, // 653 ConduitKernelArgumentALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20369, 27), 677}, // 654 ConduitKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17264, 9), 563}, // 655 Constant in SPV_OPERAND_TYPE_DECORATION
  {IR(18772, 14), 635}, // 656 CounterBuffer in SPV_OPERAND_TYPE_DECORATION
  {IR(17410, 14), 575}, // 657 DescriptorSet in SPV_OPERAND_TYPE_DECORATION
  {IR(19547, 29), 657}, // 658 DontStaticallyCoalesceALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19576, 28), 657}, // 659 DontStaticallyCoalesceINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19130, 17), 646}, // 660 DoublepumpALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19147, 16), 646}, // 661 DoublepumpINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17931, 18), 595}, // 662 ExplicitInterpAMD in SPV_OPERAND_TYPE_DECORATION
  {IR(17595, 15), 581}, // 663 FPFastMathMode in SPV_OPERAND_TYPE_DECORATION
  {IR(20203, 26), 674}, // 664 FPMaxErrorDecorationINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17545, 15), 580}, // 665 FPRoundingMode in SPV_OPERAND_TYPE_DECORATION
  {IR(17201, 5), 555}, // 666 Flat in SPV_OPERAND_TYPE_DECORATION
  {IR(19337, 21), 651}, // 667 ForcePow2DepthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19358, 20), 651}, // 668 ForcePow2DepthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17497, 14), 579}, // 669 FuncParamAttr in SPV_OPERAND_TYPE_DECORATION
  {IR(18683, 21), 631}, // 670 FuncParamIOKindINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18914, 24), 639}, // 671 FunctionDenormModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20032, 31), 669}, // 672 FunctionFloatingPointModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18857, 26), 638}, // 673 FunctionRoundingModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19668, 26), 660}, // 674 FuseLoopsInFunctionALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19694, 25), 660}, // 675 FuseLoopsInFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17134, 11), 551}, // 676 GLSLPacked in SPV_OPERAND_TYPE_DECORATION
  {IR(17123, 11), 550}, // 677 GLSLShared in SPV_OPERAND_TYPE_DECORATION
  {IR(18746, 26), 634}, // 678 GlobalVariableOffsetINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18486, 31), 620}, // 679 HitObjectShaderRecordBufferEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(18456, 30), 619}, // 680 HitObjectShaderRecordBufferNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18786, 24), 635}, // 681 HlslCounterBufferGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(18823, 19), 636}, // 682 HlslSemanticGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(20963, 16), 686}, // 683 HostAccessINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19959, 20), 668}, // 684 IOPipeStorageALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19979, 19), 668}, // 685 IOPipeStorageINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(21055, 29), 688}, // 686 ImplementInRegisterMapALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(21084, 28), 688}, // 687 ImplementInRegisterMapINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17396, 6), 573}, // 688 Index in SPV_OPERAND_TYPE_DECORATION
  {IR(21026, 15), 687}, // 689 InitModeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(21041, 14), 687}, // 690 InitModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19787, 25), 664}, // 691 InitiationIntervalALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19812, 24), 664}, // 692 InitiationIntervalINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17704, 21), 584}, // 693 InputAttachmentIndex in SPV_OPERAND_TYPE_DECORATION
  {IR(17228, 10), 559}, // 694 Invariant in SPV_OPERAND_TYPE_DECORATION
  {IR(20280, 31), 676}, // 695 LatencyControlConstraintALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20311, 30), 676}, // 696 LatencyControlConstraintINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20229, 26), 675}, // 697 LatencyControlLabelALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20255, 25), 675}, // 698 LatencyControlLabelINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17672, 18), 582}, // 699 LinkageAttributes in SPV_OPERAND_TYPE_DECORATION
  {IR(17377, 9), 571}, // 700 Location in SPV_OPERAND_TYPE_DECORATION
  {IR(20459, 34), 679}, // 701 MMHostInterfaceAddressWidthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20493, 33), 679}, // 702 MMHostInterfaceAddressWidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20526, 31), 680}, // 703 MMHostInterfaceDataWidthALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20557, 30), 680}, // 704 MMHostInterfaceDataWidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20587, 29), 681}, // 705 MMHostInterfaceLatencyALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20616, 28), 681}, // 706 MMHostInterfaceLatencyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20747, 30), 683}, // 707 MMHostInterfaceMaxBurstALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20777, 29), 683}, // 708 MMHostInterfaceMaxBurstINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20678, 35), 682}, // 709 MMHostInterfaceReadWriteModeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20713, 34), 682}, // 710 MMHostInterfaceReadWriteModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20806, 33), 684}, // 711 MMHostInterfaceWaitRequestALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20839, 32), 684}, // 712 MMHostInterfaceWaitRequestINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19719, 20), 661}, // 713 MathOpDSPModeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19739, 19), 661}, // 714 MathOpDSPModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17110, 13), 549}, // 715 MatrixStride in SPV_OPERAND_TYPE_DECORATION
  {IR(17735, 14), 586}, // 716 MaxByteOffset in SPV_OPERAND_TYPE_DECORATION
  {IR(17781, 16), 588}, // 717 MaxByteOffsetId in SPV_OPERAND_TYPE_DECORATION
  {IR(19836, 21), 665}, // 718 MaxConcurrencyALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19857, 20), 665}, // 719 MaxConcurrencyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19052, 23), 644}, // 720 MaxPrivateCopiesALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19075, 22), 644}, // 721 MaxPrivateCopiesINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19163, 20), 647}, // 722 MaxReplicatesALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19183, 19), 647}, // 723 MaxReplicatesINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20123, 18), 672}, // 724 MediaBlockIOINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18441, 15), 618}, // 725 MemberOffsetNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18967, 13), 641}, // 726 MemoryALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18980, 12), 641}, // 727 MemoryINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19243, 12), 649}, // 728 MergeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19255, 11), 649}, // 729 MergeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19774, 13), 663}, // 730 NoAliasINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17690, 14), 583}, // 731 NoContraction in SPV_OPERAND_TYPE_DECORATION
  {IR(17187, 14), 554}, // 732 NoPerspective in SPV_OPERAND_TYPE_DECORATION
  {IR(17841, 13), 590}, // 733 NoSignedWrap in SPV_OPERAND_TYPE_DECORATION
  {IR(17854, 15), 591}, // 734 NoUnsignedWrap in SPV_OPERAND_TYPE_DECORATION
  {IR(17981, 20), 597}, // 735 NodeMaxPayloadsAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17949, 32), 596}, // 736 NodeSharesPayloadLimitsWithAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(17294, 12), 566}, // 737 NonReadable in SPV_OPERAND_TYPE_DECORATION
  {IR(18348, 11), 615}, // 738 NonUniform in SPV_OPERAND_TYPE_DECORATION
  {IR(18359, 14), 615}, // 739 NonUniformEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(17282, 12), 565}, // 740 NonWritable in SPV_OPERAND_TYPE_DECORATION
  {IR(18992, 15), 642}, // 741 NumbanksALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19007, 14), 642}, // 742 NumbanksINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17424, 7), 576}, // 743 Offset in SPV_OPERAND_TYPE_DECORATION
  {IR(18166, 12), 605}, // 744 OffsetIdEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(18192, 19), 607}, // 745 OverrideCoverageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18211, 14), 608}, // 746 PassthroughNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17206, 6), 556}, // 747 Patch in SPV_OPERAND_TYPE_DECORATION
  {IR(18121, 28), 603}, // 748 PayloadDispatchIndirectAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(18096, 25), 602}, // 749 PayloadNodeArraySizeAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(18044, 25), 600}, // 750 PayloadNodeBaseIndexAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(18024, 20), 599}, // 751 PayloadNodeNameAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(18069, 27), 601}, // 752 PayloadNodeSparseArrayAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(18272, 16), 611}, // 753 PerPrimitiveEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(18288, 15), 611}, // 754 PerPrimitiveNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18313, 10), 613}, // 755 PerTaskNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18323, 13), 614}, // 756 PerVertexKHR in SPV_OPERAND_TYPE_DECORATION
  {IR(18336, 12), 614}, // 757 PerVertexNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18303, 10), 612}, // 758 PerViewNV in SPV_OPERAND_TYPE_DECORATION
  {IR(19877, 21), 666}, // 759 PipelineEnableALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19898, 20), 666}, // 760 PipelineEnableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19604, 15), 658}, // 761 PrefetchALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19619, 14), 658}, // 762 PrefetchINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18600, 26), 627}, // 763 ReferencedIndirectlyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18938, 15), 640}, // 764 RegisterALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(18953, 14), 640}, // 765 RegisterINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20396, 32), 678}, // 766 RegisterMapKernelArgumentALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20428, 31), 678}, // 767 RegisterMapKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17038, 17), 542}, // 768 RelaxedPrecision in SPV_OPERAND_TYPE_DECORATION
  {IR(17238, 9), 560}, // 769 Restrict in SPV_OPERAND_TYPE_DECORATION
  {IR(18373, 16), 616}, // 770 RestrictPointer in SPV_OPERAND_TYPE_DECORATION
  {IR(18389, 19), 616}, // 771 RestrictPointerEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(17080, 9), 546}, // 772 RowMajor in SPV_OPERAND_TYPE_DECORATION
  {IR(18586, 14), 626}, // 773 SIMTCallINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17221, 7), 558}, // 774 Sample in SPV_OPERAND_TYPE_DECORATION
  {IR(17350, 20), 569}, // 775 SaturatedConversion in SPV_OPERAND_TYPE_DECORATION
  {IR(17797, 44), 589}, // 776 SaturatedToLargestFloat8NormalConversionEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(18244, 28), 610}, // 777 SecondaryViewportRelativeNV in SPV_OPERAND_TYPE_DECORATION
  {IR(18639, 17), 629}, // 778 SideEffectsINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19202, 21), 648}, // 779 SimpleDualPortALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19223, 20), 648}, // 780 SimpleDualPortINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20063, 25), 670}, // 781 SingleElementVectorINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19097, 17), 645}, // 782 SinglepumpALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19114, 16), 645}, // 783 SinglepumpINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17055, 7), 543}, // 784 SpecId in SPV_OPERAND_TYPE_DECORATION
  {IR(20871, 27), 685}, // 785 StableKernelArgumentALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20898, 26), 685}, // 786 StableKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18731, 15), 633}, // 787 StackCallINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(19633, 18), 659}, // 788 StallEnableALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19651, 17), 659}, // 789 StallEnableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(20141, 16), 673}, // 790 StallFreeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(20157, 15), 673}, // 791 StallFreeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17370, 7), 570}, // 792 Stream in SPV_OPERAND_TYPE_DECORATION
  {IR(19378, 17), 652}, // 793 StridesizeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19395, 16), 652}, // 794 StridesizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18001, 23), 598}, // 795 TrackFinishWritingAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(19440, 19), 654}, // 796 TrueDualPortALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19459, 18), 654}, // 797 TrueDualPortINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18178, 14), 606}, // 798 UTFEncodedKHR in SPV_OPERAND_TYPE_DECORATION
  {IR(17306, 8), 567}, // 799 Uniform in SPV_OPERAND_TYPE_DECORATION
  {IR(17340, 10), 568}, // 800 UniformId in SPV_OPERAND_TYPE_DECORATION
  {IR(18810, 13), 636}, // 801 UserSemantic in SPV_OPERAND_TYPE_DECORATION
  {IR(18842, 15), 637}, // 802 UserTypeGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(20088, 35), 671}, // 803 VectorComputeCallableFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18704, 27), 632}, // 804 VectorComputeFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18656, 27), 630}, // 805 VectorComputeVariableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18225, 19), 609}, // 806 ViewportRelativeNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17255, 9), 562}, // 807 Volatile in SPV_OPERAND_TYPE_DECORATION
  {IR(17869, 18), 592}, // 808 WeightTextureQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(19411, 15), 653}, // 809 WordsizeALTERA in SPV_OPERAND_TYPE_DECORATION
  {IR(19426, 14), 653}, // 810 WordsizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17431, 10), 577}, // 811 XfbBuffer in SPV_OPERAND_TYPE_DECORATION
  {IR(17441, 10), 578}, // 812 XfbStride in SPV_OPERAND_TYPE_DECORATION
  {IR(21247, 3), 692}, // 813 1D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21250, 3), 693}, // 814 2D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21253, 3), 694}, // 815 3D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21266, 7), 697}, // 816 Buffer in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21256, 5), 695}, // 817 Cube in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21261, 5), 696}, // 818 Rect in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21273, 12), 698}, // 819 SubpassData in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(21285, 17), 699}, // 820 TileImageDataEXT in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(22403, 20), 767}, // 821 ArithmeticPoisonKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22097, 15), 752}, // 822 CoalescingAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21728, 15), 730}, // 823 ContractionOff in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10570, 18), 744}, // 824 DenormFlushToZero in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10555, 15), 743}, // 825 DenormPreserve in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21498, 13), 713}, // 826 DepthGreater in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21511, 10), 714}, // 827 DepthLess in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21483, 15), 712}, // 828 DepthReplacing in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21521, 15), 715}, // 829 DepthUnchanged in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22538, 25), 771}, // 830 DerivativeGroupLinearKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22563, 24), 771}, // 831 DerivativeGroupLinearNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22491, 24), 770}, // 832 DerivativeGroupQuadsKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22515, 23), 770}, // 833 DerivativeGroupQuadsNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22045, 29), 750}, // 834 EarlyAndLateFragmentTestsAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21450, 19), 709}, // 835 EarlyFragmentTests in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23048, 18), 791}, // 836 FPFastMathDefault in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21755, 10), 732}, // 837 Finalizer in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22863, 26), 783}, // 838 FloatingPointModeALTINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22889, 27), 784}, // 839 FloatingPointModeIEEEINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21743, 12), 731}, // 840 Initializer in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21572, 11), 719}, // 841 InputLines in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21583, 20), 720}, // 842 InputLinesAdjacency in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21560, 12), 718}, // 843 InputPoints in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21613, 24), 722}, // 844 InputTrianglesAdjacency in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21302, 12), 700}, // 845 Invocations in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22112, 15), 753}, // 846 IsApiEntryAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21643, 9), 724}, // 847 Isolines in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21536, 10), 716}, // 848 LocalSize in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21546, 14), 717}, // 849 LocalSizeHint in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21823, 16), 737}, // 850 LocalSizeHintId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21811, 12), 736}, // 851 LocalSizeId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22127, 21), 754}, // 852 MaxNodeRecursionAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22172, 21), 757}, // 853 MaxNumWorkgroupsAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22938, 16), 786}, // 854 MaxWorkDimINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22916, 22), 785}, // 855 MaxWorkgroupSizeINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23024, 24), 790}, // 856 MaximallyReconvergesKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23139, 22), 795}, // 857 MaximumRegistersINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23161, 24), 796}, // 858 MaximumRegistersIdINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23116, 23), 794}, // 859 NamedBarrierCountINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23236, 27), 797}, // 860 NamedMaximumRegistersINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22954, 20), 787}, // 861 NoGlobalOffsetINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21839, 34), 738}, // 862 NonCoherentColorAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21873, 34), 739}, // 863 NonCoherentDepthAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21907, 36), 740}, // 864 NonCoherentStencilAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21991, 34), 748}, // 865 NonCoherentTileAttachmentReadQCOM in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22974, 22), 788}, // 866 NumSIMDWorkitemsINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21434, 16), 708}, // 867 OriginLowerLeft in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21418, 16), 707}, // 868 OriginUpperLeft in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21680, 16), 727}, // 869 OutputLineStrip in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22423, 15), 768}, // 870 OutputLinesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22438, 14), 768}, // 871 OutputLinesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21667, 13), 726}, // 872 OutputPoints in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22452, 20), 769}, // 873 OutputPrimitivesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22472, 19), 769}, // 874 OutputPrimitivesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21696, 20), 728}, // 875 OutputTriangleStrip in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22587, 19), 772}, // 876 OutputTrianglesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22606, 18), 772}, // 877 OutputTrianglesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21652, 15), 725}, // 878 OutputVertices in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21399, 19), 706}, // 879 PixelCenterInteger in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22624, 25), 773}, // 880 PixelInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22649, 27), 774}, // 881 PixelInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21469, 10), 710}, // 882 PointMode in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21973, 18), 742}, // 883 PostDepthCoverage in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22344, 19), 764}, // 884 QuadDerivativesKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21637, 6), 723}, // 885 Quads in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23090, 26), 793}, // 886 RegisterMapInterfaceINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22363, 20), 765}, // 887 RequireFullQuadsKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10613, 16), 746}, // 888 RoundingModeRTE in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22842, 21), 782}, // 889 RoundingModeRTNINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22821, 21), 781}, // 890 RoundingModeRTPINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10629, 16), 747}, // 891 RoundingModeRTZ in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22676, 26), 775}, // 892 SampleInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22702, 28), 776}, // 893 SampleInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22996, 28), 789}, // 894 SchedulerTargetFmaxMhzINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(12902, 23), 779}, // 895 Shader64BitIndexingEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(7200, 16), 756}, // 896 ShaderIndexAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22730, 31), 777}, // 897 ShadingRateInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22761, 33), 778}, // 898 ShadingRateInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22794, 27), 780}, // 899 SharedLocalMemorySizeINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22383, 20), 766}, // 900 SharesInputWithAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(10588, 25), 745}, // 901 SignedZeroInfNanPreserve in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21314, 13), 701}, // 902 SpacingEqual in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21327, 22), 702}, // 903 SpacingFractionalEven in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21349, 21), 703}, // 904 SpacingFractionalOdd in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22148, 24), 755}, // 905 StaticNumWorkgroupsAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22297, 25), 762}, // 906 StencilRefGreaterBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22221, 26), 759}, // 907 StencilRefGreaterFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22322, 22), 763}, // 908 StencilRefLessBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22247, 23), 760}, // 909 StencilRefLessFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22074, 23), 751}, // 910 StencilRefReplacingEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22270, 27), 761}, // 911 StencilRefUnchangedBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22193, 28), 758}, // 912 StencilRefUnchangedFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23066, 24), 792}, // 913 StreamingInterfaceINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(6307, 13), 733}, // 914 SubgroupSize in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21943, 30), 741}, // 915 SubgroupUniformControlFlowKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21765, 22), 734}, // 916 SubgroupsPerWorkgroup in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21787, 24), 735}, // 917 SubgroupsPerWorkgroupId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(22025, 20), 749}, // 918 TileShadingRateQCOM in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21603, 10), 721}, // 919 Triangles in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21716, 12), 729}, // 920 VecTypeHint in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21384, 15), 705}, // 921 VertexOrderCcw in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21370, 14), 704}, // 922 VertexOrderCw in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(21479, 4), 711}, // 923 Xfb in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(23401, 10), 809}, // 924 AnyHitKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23411, 9), 809}, // 925 AnyHitNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23462, 12), 812}, // 926 CallableKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23474, 11), 812}, // 927 CallableNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23420, 14), 810}, // 928 ClosestHitKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23434, 13), 810}, // 929 ClosestHitNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(16421, 9), 802}, // 930 Fragment in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23313, 10), 803}, // 931 GLCompute in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(5788, 9), 801}, // 932 Geometry in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23370, 16), 808}, // 933 IntersectionKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23386, 15), 808}, // 934 IntersectionNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(5555, 7), 804}, // 935 Kernel in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23493, 8), 814}, // 936 MeshEXT in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23330, 7), 806}, // 937 MeshNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23447, 8), 811}, // 938 MissKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23455, 7), 811}, // 939 MissNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23337, 17), 807}, // 940 RayGenerationKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23354, 16), 807}, // 941 RayGenerationNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23485, 8), 813}, // 942 TaskEXT in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23323, 7), 805}, // 943 TaskNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23270, 20), 799}, // 944 TessellationControl in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23290, 23), 800}, // 945 TessellationEvaluation in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23263, 7), 798}, // 946 Vertex in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(23510, 12), 816}, // 947 FlushToZero in SPV_OPERAND_TYPE_FPDENORM_MODE
  {IR(23501, 9), 815}, // 948 Preserve in SPV_OPERAND_TYPE_FPDENORM_MODE
  {IR(23522, 12), 817}, // 949 BFloat16KHR in SPV_OPERAND_TYPE_FPENCODING
  {IR(23534, 14), 818}, // 950 Float8E4M3EXT in SPV_OPERAND_TYPE_FPENCODING
  {IR(23548, 14), 819}, // 951 Float8E5M2EXT in SPV_OPERAND_TYPE_FPENCODING
  {IR(23567, 4), 821}, // 952 ALT in SPV_OPERAND_TYPE_FPOPERATION_MODE
  {IR(23562, 5), 820}, // 953 IEEE in SPV_OPERAND_TYPE_FPOPERATION_MODE
  {IR(23605, 14), 828}, // 954 AllowContract in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23619, 23), 828}, // 955 AllowContractFastINTEL in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23642, 13), 829}, // 956 AllowReassoc in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23655, 18), 829}, // 957 AllowReassocINTEL in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23589, 11), 826}, // 958 AllowRecip in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23673, 15), 830}, // 959 AllowTransform in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23600, 5), 827}, // 960 Fast in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23585, 4), 825}, // 961 NSZ in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(16017, 5), 822}, // 962 None in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23578, 7), 824}, // 963 NotInf in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23571, 7), 823}, // 964 NotNaN in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(23688, 4), 831}, // 965 RTE in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(23700, 4), 834}, // 966 RTN in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(23696, 4), 833}, // 967 RTP in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(23692, 4), 832}, // 968 RTZ in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(23736, 18), 837}, // 969 Horizontal2Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(23754, 18), 838}, // 970 Horizontal4Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(23704, 16), 835}, // 971 Vertical2Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(23720, 16), 836}, // 972 Vertical4Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(23795, 6), 843}, // 973 Const in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(23779, 11), 841}, // 974 DontInline in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(23772, 7), 840}, // 975 Inline in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(16017, 5), 839}, // 976 None in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(14899, 11), 844}, // 977 OptNoneEXT in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(14910, 13), 844}, // 978 OptNoneINTEL in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(23790, 5), 842}, // 979 Pure in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(23811, 6), 847}, // 980 ByVal in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23822, 8), 849}, // 981 NoAlias in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23830, 10), 850}, // 982 NoCapture in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23848, 12), 852}, // 983 NoReadWrite in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23840, 8), 851}, // 984 NoWrite in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23860, 21), 853}, // 985 RuntimeAlignedALTERA in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23881, 20), 853}, // 986 RuntimeAlignedINTEL in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23806, 5), 846}, // 987 Sext in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23817, 5), 848}, // 988 Sret in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23801, 5), 845}, // 989 Zext in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(23936, 16), 857}, // 990 ClusteredReduce in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23922, 14), 856}, // 991 ExclusiveScan in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23908, 14), 855}, // 992 InclusiveScan in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(24048, 28), 860}, // 993 PartitionedExclusiveScanEXT in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(24076, 27), 860}, // 994 PartitionedExclusiveScanNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23993, 28), 859}, // 995 PartitionedInclusiveScanEXT in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(24021, 27), 859}, // 996 PartitionedInclusiveScanNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23952, 21), 858}, // 997 PartitionedReduceEXT in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23973, 20), 858}, // 998 PartitionedReduceNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(23901, 7), 854}, // 999 Reduce in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(24103, 10), 861}, // 1000 NoneINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(24113, 10), 862}, // 1001 ReadINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(24134, 15), 864}, // 1002 ReadWriteINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(24123, 11), 863}, // 1003 WriteINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(24149, 5), 866}, // 1004 Bias in SPV_OPERAND_TYPE_IMAGE
  {IR(24163, 12), 869}, // 1005 ConstOffset in SPV_OPERAND_TYPE_IMAGE
  {IR(24175, 13), 871}, // 1006 ConstOffsets in SPV_OPERAND_TYPE_IMAGE
  {IR(24158, 5), 868}, // 1007 Grad in SPV_OPERAND_TYPE_IMAGE
  {IR(24154, 4), 867}, // 1008 Lod in SPV_OPERAND_TYPE_IMAGE
  {IR(24188, 19), 874}, // 1009 MakeTexelAvailable in SPV_OPERAND_TYPE_IMAGE
  {IR(24207, 22), 874}, // 1010 MakeTexelAvailableKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(24229, 17), 875}, // 1011 MakeTexelVisible in SPV_OPERAND_TYPE_IMAGE
  {IR(24246, 20), 875}, // 1012 MakeTexelVisibleKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(9388, 7), 873}, // 1013 MinLod in SPV_OPERAND_TYPE_IMAGE
  {IR(24266, 16), 876}, // 1014 NonPrivateTexel in SPV_OPERAND_TYPE_IMAGE
  {IR(24282, 19), 876}, // 1015 NonPrivateTexelKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(16017, 5), 865}, // 1016 None in SPV_OPERAND_TYPE_IMAGE
  {IR(24354, 12), 880}, // 1017 Nontemporal in SPV_OPERAND_TYPE_IMAGE
  {IR(17424, 7), 870}, // 1018 Offset in SPV_OPERAND_TYPE_IMAGE
  {IR(24366, 8), 881}, // 1019 Offsets in SPV_OPERAND_TYPE_IMAGE
  {IR(17221, 7), 872}, // 1020 Sample in SPV_OPERAND_TYPE_IMAGE
  {IR(24332, 11), 878}, // 1021 SignExtend in SPV_OPERAND_TYPE_IMAGE
  {IR(24301, 14), 877}, // 1022 VolatileTexel in SPV_OPERAND_TYPE_IMAGE
  {IR(24315, 17), 877}, // 1023 VolatileTexelKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(24343, 11), 879}, // 1024 ZeroExtend in SPV_OPERAND_TYPE_IMAGE
  {IR(15914, 6), 896}, // 1025 Float in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24535, 10), 895}, // 1026 HalfFloat in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24470, 12), 890}, // 1027 SignedInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24482, 12), 891}, // 1028 SignedInt32 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24459, 11), 889}, // 1029 SignedInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24384, 11), 883}, // 1030 SnormInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24374, 10), 882}, // 1031 SnormInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24444, 15), 888}, // 1032 UnormInt101010 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24556, 17), 898}, // 1033 UnormInt101010_2 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24573, 16), 899}, // 1034 UnormInt10X6EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24706, 16), 906}, // 1035 UnormInt12X4EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24722, 16), 907}, // 1036 UnormInt14X2EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24405, 11), 885}, // 1037 UnormInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24545, 11), 897}, // 1038 UnormInt24 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24629, 20), 902}, // 1039 UnormInt2_101010EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24395, 10), 884}, // 1040 UnormInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24430, 14), 887}, // 1041 UnormShort555 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24416, 14), 886}, // 1042 UnormShort565 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24649, 19), 903}, // 1043 UnsignedInt10X6EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24668, 19), 904}, // 1044 UnsignedInt12X4EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24687, 19), 905}, // 1045 UnsignedInt14X2EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24507, 14), 893}, // 1046 UnsignedInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24521, 14), 894}, // 1047 UnsignedInt32 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24494, 13), 892}, // 1048 UnsignedInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24589, 20), 900}, // 1049 UnsignedIntRaw10EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24609, 20), 901}, // 1050 UnsignedIntRaw12EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(24740, 2), 909}, // 1051 A in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24841, 5), 927}, // 1052 ABGR in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24762, 5), 915}, // 1053 ARGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24757, 5), 914}, // 1054 BGRA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24799, 6), 921}, // 1055 Depth in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24805, 13), 922}, // 1056 DepthStencil in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24767, 10), 916}, // 1057 Intensity in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24777, 10), 917}, // 1058 Luminance in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24738, 2), 908}, // 1059 R in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24745, 3), 911}, // 1060 RA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24742, 3), 910}, // 1061 RG in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24748, 4), 912}, // 1062 RGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24752, 5), 913}, // 1063 RGBA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24794, 5), 920}, // 1064 RGBx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24790, 4), 919}, // 1065 RGx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24787, 3), 918}, // 1066 Rx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24835, 6), 926}, // 1067 sBGRA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24818, 5), 923}, // 1068 sRGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24829, 6), 925}, // 1069 sRGBA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24823, 6), 924}, // 1070 sRGBx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(24846, 28), 928}, // 1071 InitOnDeviceReprogramALTERA in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(24874, 27), 928}, // 1072 InitOnDeviceReprogramINTEL in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(24901, 24), 929}, // 1073 InitOnDeviceResetALTERA in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(24925, 23), 929}, // 1074 InitOnDeviceResetINTEL in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(24948, 7), 930}, // 1075 NoWait in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(24955, 11), 931}, // 1076 WaitKernel in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(24966, 14), 932}, // 1077 WaitWorkGroup in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(24980, 12), 934}, // 1078 CmdExecTime in SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {IR(16017, 5), 933}, // 1079 None in SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {IR(24992, 13), 936}, // 1080 MayUsePrintf in SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {IR(16017, 5), 935}, // 1081 None in SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {IR(25005, 7), 937}, // 1082 Export in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(25012, 7), 938}, // 1083 Import in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(25019, 12), 939}, // 1084 LinkOnceODR in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(25045, 12), 941}, // 1085 CachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(25097, 17), 944}, // 1086 ConstCachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(25072, 25), 943}, // 1087 InvalidateAfterReadINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(25057, 15), 942}, // 1088 StreamingINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(25031, 14), 940}, // 1089 UncachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(25237, 22), 957}, // 1090 DependencyArrayALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25259, 21), 957}, // 1091 DependencyArrayINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25132, 19), 948}, // 1092 DependencyInfinite in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25151, 17), 949}, // 1093 DependencyLength in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25121, 11), 947}, // 1094 DontUnroll in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19787, 25), 955}, // 1095 InitiationIntervalALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19812, 24), 955}, // 1096 InitiationIntervalINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25196, 18), 952}, // 1097 IterationMultiple in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25280, 19), 959}, // 1098 LoopCoalesceALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25299, 18), 959}, // 1099 LoopCoalesceINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25442, 16), 963}, // 1100 LoopCountALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25458, 15), 963}, // 1101 LoopCountINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19836, 21), 956}, // 1102 MaxConcurrencyALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19857, 20), 956}, // 1103 MaxConcurrencyINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25317, 22), 960}, // 1104 MaxInterleavingALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25339, 21), 960}, // 1105 MaxInterleavingINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25182, 14), 951}, // 1106 MaxIterations in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25473, 27), 964}, // 1107 MaxReinvocationDelayALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25500, 26), 964}, // 1108 MaxReinvocationDelayINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25168, 14), 950}, // 1109 MinIterations in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25413, 15), 962}, // 1110 NoFusionALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25428, 14), 962}, // 1111 NoFusionINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(16017, 5), 945}, // 1112 None in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25224, 13), 954}, // 1113 PartialCount in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25214, 10), 953}, // 1114 PeelCount in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19877, 21), 958}, // 1115 PipelineEnableALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(19898, 20), 958}, // 1116 PipelineEnableINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25360, 27), 961}, // 1117 SpeculatedIterationsALTERA in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25387, 26), 961}, // 1118 SpeculatedIterationsINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25114, 7), 946}, // 1119 Unroll in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(25809, 27), 978}, // 1120 MatrixAPackedBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25757, 26), 976}, // 1121 MatrixAPackedFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25677, 23), 972}, // 1122 MatrixAPackedInt4INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25631, 23), 970}, // 1123 MatrixAPackedInt8INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25526, 29), 966}, // 1124 MatrixASignedComponentsINTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25723, 17), 974}, // 1125 MatrixATF32INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25836, 27), 979}, // 1126 MatrixBPackedBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25783, 26), 977}, // 1127 MatrixBPackedFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25700, 23), 973}, // 1128 MatrixBPackedInt4INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25654, 23), 971}, // 1129 MatrixBPackedInt8INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25555, 29), 967}, // 1130 MatrixBSignedComponentsINTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25740, 17), 975}, // 1131 MatrixBTF32INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25584, 21), 968}, // 1132 MatrixCBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25605, 26), 969}, // 1133 MatrixResultBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(16017, 5), 965}, // 1134 None in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(25996, 20), 987}, // 1135 AliasScopeINTELMask in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25863, 8), 982}, // 1136 Aligned in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25871, 21), 984}, // 1137 MakePointerAvailable in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25892, 24), 984}, // 1138 MakePointerAvailableKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25916, 19), 985}, // 1139 MakePointerVisible in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25935, 22), 985}, // 1140 MakePointerVisibleKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(26016, 17), 988}, // 1141 NoAliasINTELMask in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25957, 18), 986}, // 1142 NonPrivatePointer in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(25975, 21), 986}, // 1143 NonPrivatePointerKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(16017, 5), 980}, // 1144 None in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(24354, 12), 983}, // 1145 Nontemporal in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(17255, 9), 981}, // 1146 Volatile in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(26040, 8), 990}, // 1147 GLSL450 in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(26048, 7), 991}, // 1148 OpenCL in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(26033, 7), 989}, // 1149 Simple in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(26055, 7), 992}, // 1150 Vulkan in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(26062, 10), 992}, // 1151 VulkanKHR in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(26080, 8), 994}, // 1152 Acquire in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26096, 15), 996}, // 1153 AcquireRelease in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26200, 20), 1002}, // 1154 AtomicCounterMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26179, 21), 1001}, // 1155 CrossWorkgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26220, 12), 1003}, // 1156 ImageMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26261, 14), 1005}, // 1157 MakeAvailable in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26275, 17), 1005}, // 1158 MakeAvailableKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26292, 12), 1006}, // 1159 MakeVisible in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26304, 15), 1006}, // 1160 MakeVisibleKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(16017, 5), 993}, // 1161 None in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26232, 13), 1004}, // 1162 OutputMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26245, 16), 1004}, // 1163 OutputMemoryKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26072, 8), 993}, // 1164 Relaxed in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26088, 8), 995}, // 1165 Release in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26111, 23), 997}, // 1166 SequentiallyConsistent in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26148, 15), 999}, // 1167 SubgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26134, 14), 998}, // 1168 UniformMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(17255, 9), 1007}, // 1169 Volatile in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26163, 16), 1000}, // 1170 WorkgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(26319, 10), 1008}, // 1171 AutoINTEL in SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS
  {IR(26334, 4), 1010}, // 1172 SAT in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(26347, 8), 1012}, // 1173 SAT_SYM in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(26338, 9), 1011}, // 1174 SAT_ZERO in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(26329, 5), 1009}, // 1175 WRAP in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(26355, 25), 1013}, // 1176 PackedVectorFormat4x8Bit in SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {IR(26380, 28), 1013}, // 1177 PackedVectorFormat4x8BitKHR in SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {IR(26421, 4), 1016}, // 1178 RND in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26454, 9), 1020}, // 1179 RND_CONV in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26463, 13), 1021}, // 1180 RND_CONV_ODD in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26434, 8), 1018}, // 1181 RND_INF in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26442, 12), 1019}, // 1182 RND_MIN_INF in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26425, 9), 1017}, // 1183 RND_ZERO in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26408, 4), 1014}, // 1184 TRN in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(26412, 9), 1015}, // 1185 TRN_ZERO in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(16017, 5), 1022}, // 1186 None in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(26476, 25), 1023}, // 1187 RobustnessPerComponentNV in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(26501, 23), 1024}, // 1188 RobustnessPerElementNV in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(26593, 27), 1030}, // 1189 CullBackFacingTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26620, 28), 1031}, // 1190 CullFrontFacingTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26662, 16), 1033}, // 1191 CullNoOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26648, 14), 1032}, // 1192 CullOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26732, 30), 1036}, // 1193 ForceOpacityMicromap2StateEXT in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26534, 12), 1027}, // 1194 NoOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(16769, 8), 1025}, // 1195 NoneKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26524, 10), 1026}, // 1196 OpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26719, 13), 1035}, // 1197 SkipAABBsKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26695, 24), 1034}, // 1198 SkipBuiltinPrimitivesNV in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26569, 24), 1029}, // 1199 SkipClosestHitShaderKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26678, 17), 1034}, // 1200 SkipTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26546, 23), 1028}, // 1201 TerminateOnFirstHitKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(26803, 37), 1038}, // 1202 RayQueryCandidateIntersectionAABBKHR in SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {IR(26762, 41), 1037}, // 1203 RayQueryCandidateIntersectionTriangleKHR in SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {IR(26918, 42), 1041}, // 1204 RayQueryCommittedIntersectionGeneratedKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(26840, 37), 1039}, // 1205 RayQueryCommittedIntersectionNoneKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(26877, 41), 1040}, // 1206 RayQueryCommittedIntersectionTriangleKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(26960, 33), 1042}, // 1207 RayQueryCandidateIntersectionKHR in SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {IR(26993, 33), 1043}, // 1208 RayQueryCommittedIntersectionKHR in SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {IR(27038, 6), 1046}, // 1209 Clamp in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(27026, 12), 1045}, // 1210 ClampToEdge in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(16017, 5), 1044}, // 1211 None in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(27044, 7), 1047}, // 1212 Repeat in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(27051, 15), 1048}, // 1213 RepeatMirrored in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(27074, 7), 1050}, // 1214 Linear in SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {IR(27066, 8), 1049}, // 1215 Nearest in SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {IR(27139, 13), 1059}, // 1216 R11fG11fB10f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27181, 4), 1065}, // 1217 R16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27219, 9), 1070}, // 1218 R16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27152, 5), 1060}, // 1219 R16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27281, 5), 1079}, // 1220 R16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27352, 6), 1089}, // 1221 R16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27105, 5), 1054}, // 1222 R32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27259, 5), 1075}, // 1223 R32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27316, 6), 1084}, // 1224 R32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27369, 5), 1092}, // 1225 R64i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27363, 6), 1091}, // 1226 R64ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27185, 3), 1066}, // 1227 R8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27228, 8), 1071}, // 1228 R8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27286, 4), 1080}, // 1229 R8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27358, 5), 1090}, // 1230 R8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27172, 5), 1063}, // 1231 Rg16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27200, 10), 1068}, // 1232 Rg16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27133, 6), 1058}, // 1233 Rg16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27270, 6), 1077}, // 1234 Rg16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27339, 7), 1087}, // 1235 Rg16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27127, 6), 1057}, // 1236 Rg32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27264, 6), 1076}, // 1237 Rg32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27332, 7), 1086}, // 1238 Rg32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27177, 4), 1064}, // 1239 Rg8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27210, 9), 1069}, // 1240 Rg8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27276, 5), 1078}, // 1241 Rg8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27346, 6), 1088}, // 1242 Rg8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27164, 8), 1062}, // 1243 Rgb10A2 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27322, 10), 1085}, // 1244 Rgb10a2ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27157, 7), 1061}, // 1245 Rgba16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27188, 12), 1067}, // 1246 Rgba16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27097, 8), 1053}, // 1247 Rgba16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27244, 8), 1073}, // 1248 Rgba16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27299, 9), 1082}, // 1249 Rgba16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27089, 8), 1052}, // 1250 Rgba32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27236, 8), 1072}, // 1251 Rgba32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27290, 9), 1081}, // 1252 Rgba32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27110, 6), 1055}, // 1253 Rgba8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27116, 11), 1056}, // 1254 Rgba8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27252, 7), 1074}, // 1255 Rgba8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27308, 8), 1083}, // 1256 Rgba8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27081, 8), 1051}, // 1257 Unknown in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(27374, 12), 1093}, // 1258 CrossDevice in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27386, 7), 1094}, // 1259 Device in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27412, 11), 1097}, // 1260 Invocation in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27423, 12), 1098}, // 1261 QueueFamily in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27435, 15), 1098}, // 1262 QueueFamilyKHR in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27450, 14), 1099}, // 1263 ShaderCallKHR in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27403, 9), 1096}, // 1264 Subgroup in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27393, 10), 1095}, // 1265 Workgroup in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(27472, 12), 1102}, // 1266 DontFlatten in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(27464, 8), 1101}, // 1267 Flatten in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(16017, 5), 1100}, // 1268 None in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(27484, 29), 1103}, // 1269 IdentifierPossibleDuplicates in SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS
  {IR(15898, 8), 1105}, // 1270 Address in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15906, 8), 1106}, // 1271 Boolean in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15914, 6), 1107}, // 1272 Float in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15920, 7), 1108}, // 1273 Signed in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15927, 11), 1109}, // 1274 SignedChar in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15938, 9), 1110}, // 1275 Unsigned in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15947, 13), 1111}, // 1276 UnsignedChar in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15886, 12), 1104}, // 1277 Unspecified in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(15960, 6), 1112}, // 1278 Class in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15966, 10), 1113}, // 1279 Structure in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15976, 6), 1114}, // 1280 Union in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(15997, 20), 1116}, // 1281 ImportedDeclaration in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(15982, 15), 1115}, // 1282 ImportedModule in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(16106, 15), 1124}, // 1283 FlagArtificial in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16121, 13), 1125}, // 1284 FlagExplicit in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16094, 12), 1123}, // 1285 FlagFwdDecl in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16184, 21), 1129}, // 1286 FlagIndirectVariable in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16077, 17), 1122}, // 1287 FlagIsDefinition in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16261, 16), 1133}, // 1288 FlagIsEnumClass in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16065, 12), 1121}, // 1289 FlagIsLocal in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16245, 16), 1132}, // 1290 FlagIsOptimized in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16038, 14), 1119}, // 1291 FlagIsPrivate in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16022, 16), 1118}, // 1292 FlagIsProtected in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16052, 13), 1120}, // 1293 FlagIsPublic in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16205, 20), 1130}, // 1294 FlagLValueReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16149, 18), 1127}, // 1295 FlagObjectPointer in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16134, 15), 1126}, // 1296 FlagPrototyped in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16225, 20), 1131}, // 1297 FlagRValueReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16167, 17), 1128}, // 1298 FlagStaticMember in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16297, 24), 1135}, // 1299 FlagTypePassByReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16277, 20), 1134}, // 1300 FlagTypePassByValue in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(27513, 26), 1136}, // 1301 FlagUnknownPhysicalLayout in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16017, 5), 1117}, // 1302 None in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(16382, 9), 1141}, // 1303 BitPiece in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16414, 7), 1145}, // 1304 Constu in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16321, 6), 1137}, // 1305 Deref in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16421, 9), 1146}, // 1306 Fragment in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16332, 6), 1139}, // 1307 Minus in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16327, 5), 1138}, // 1308 Plus in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16371, 11), 1140}, // 1309 PlusUconst in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16403, 11), 1144}, // 1310 StackValue in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16391, 5), 1142}, // 1311 Swap in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16396, 7), 1143}, // 1312 Xderef in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(16466, 11), 1150}, // 1313 AtomicType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16430, 10), 1147}, // 1314 ConstType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16453, 13), 1149}, // 1315 RestrictType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(16440, 13), 1148}, // 1316 VolatileType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(27574, 15), 1157}, // 1317 CPP_for_OpenCL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27539, 5), 1152}, // 1318 ESSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27544, 5), 1153}, // 1319 GLSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27594, 7), 1159}, // 1320 HERO_C in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27569, 5), 1156}, // 1321 HLSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27601, 5), 1160}, // 1322 NZSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27549, 9), 1154}, // 1323 OpenCL_C in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27558, 11), 1155}, // 1324 OpenCL_CPP in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27621, 5), 1164}, // 1325 Rust in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27589, 5), 1158}, // 1326 SYCL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27611, 6), 1162}, // 1327 Slang in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27081, 8), 1151}, // 1328 Unknown in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27606, 5), 1161}, // 1329 WGSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27617, 4), 1163}, // 1330 Zig in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(27708, 14), 1175}, // 1331 AtomicCounter in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27790, 16), 1181}, // 1332 CallableDataKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27806, 15), 1181}, // 1333 CallableDataNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28126, 17), 1191}, // 1334 CodeSectionINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27655, 15), 1170}, // 1335 CrossWorkgroup in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28143, 17), 1192}, // 1336 DeviceOnlyALTERA in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28160, 16), 1192}, // 1337 DeviceOnlyINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27678, 9), 1172}, // 1338 Function in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27687, 8), 1173}, // 1339 Generic in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27895, 16), 1184}, // 1340 HitAttributeKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27911, 15), 1184}, // 1341 HitAttributeNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28104, 22), 1190}, // 1342 HitObjectAttributeEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28059, 21), 1188}, // 1343 HitObjectAttributeNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28176, 15), 1193}, // 1344 HostOnlyALTERA in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28191, 14), 1193}, // 1345 HostOnlyINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27722, 6), 1176}, // 1346 Image in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27821, 24), 1182}, // 1347 IncomingCallableDataKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27845, 23), 1182}, // 1348 IncomingCallableDataNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27926, 22), 1185}, // 1349 IncomingRayPayloadKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27948, 21), 1185}, // 1350 IncomingRayPayloadNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27642, 6), 1166}, // 1351 Input in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27774, 16), 1180}, // 1352 NodePayloadAMDX in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27648, 7), 1168}, // 1353 Output in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28012, 22), 1187}, // 1354 PhysicalStorageBuffer in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28034, 25), 1187}, // 1355 PhysicalStorageBufferEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27670, 8), 1171}, // 1356 Private in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27695, 13), 1174}, // 1357 PushConstant in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27868, 14), 1183}, // 1358 RayPayloadKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27882, 13), 1183}, // 1359 RayPayloadNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27969, 22), 1186}, // 1360 ShaderRecordBufferKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27991, 21), 1186}, // 1361 ShaderRecordBufferNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27728, 14), 1177}, // 1362 StorageBuffer in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(28080, 24), 1189}, // 1363 TaskPayloadWorkgroupEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27755, 19), 1179}, // 1364 TileAttachmentQCOM in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27742, 13), 1178}, // 1365 TileImageEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(17306, 8), 1167}, // 1366 Uniform in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27626, 16), 1165}, // 1367 UniformConstant in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(27393, 10), 1169}, // 1368 Workgroup in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(25057, 15), 1197}, // 1369 StreamingINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(25031, 14), 1194}, // 1370 UncachedINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(28223, 15), 1196}, // 1371 WriteBackINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(28205, 18), 1195}, // 1372 WriteThroughINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(28249, 11), 1200}, // 1373 DecodeFunc in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(16017, 5), 1198}, // 1374 None in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(28238, 11), 1199}, // 1375 TensorView in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(27026, 12), 1203}, // 1376 ClampToEdge in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(17264, 9), 1202}, // 1377 Constant in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(27044, 7), 1204}, // 1378 Repeat in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(27051, 15), 1205}, // 1379 RepeatMirrored in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(28260, 10), 1201}, // 1380 Undefined in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(28313, 24), 1209}, // 1381 MakeElementAvailableARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(28337, 22), 1210}, // 1382 MakeElementVisibleARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(28359, 21), 1211}, // 1383 NonPrivateElementARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(28270, 8), 1206}, // 1384 NoneARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(28278, 15), 1207}, // 1385 NontemporalARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(28293, 20), 1208}, // 1386 OutOfBoundsValueARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
}};

IndexRange OperandNameRangeForKind(spv_operand_type_t type) {
  switch(type) {
    case SPV_OPERAND_TYPE_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_ADDRESSING_MODEL: return IR(3, 5);
    case SPV_OPERAND_TYPE_BUILT_IN: return IR(8, 150);
    case SPV_OPERAND_TYPE_CAPABILITY: return IR(158, 337);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(495, 8);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(503, 3);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(506, 2);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS: return IR(508, 19);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION: return IR(527, 10);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(537, 4);
    case SPV_OPERAND_TYPE_COMPONENT_TYPE: return IR(541, 15);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT: return IR(556, 4);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS: return IR(560, 6);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE: return IR(566, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE: return IR(569, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT: return IR(572, 4);
    case SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(576, 8);
    case SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE: return IR(584, 3);
    case SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS: return IR(587, 16);
    case SPV_OPERAND_TYPE_DEBUG_OPERATION: return IR(603, 9);
    case SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER: return IR(612, 3);
    case SPV_OPERAND_TYPE_DECORATION: return IR(615, 198);
    case SPV_OPERAND_TYPE_DIMENSIONALITY: return IR(813, 8);
    case SPV_OPERAND_TYPE_EXECUTION_MODE: return IR(821, 103);
    case SPV_OPERAND_TYPE_EXECUTION_MODEL: return IR(924, 23);
    case SPV_OPERAND_TYPE_FPDENORM_MODE: return IR(947, 2);
    case SPV_OPERAND_TYPE_FPENCODING: return IR(949, 3);
    case SPV_OPERAND_TYPE_FPOPERATION_MODE: return IR(952, 2);
    case SPV_OPERAND_TYPE_FP_FAST_MATH_MODE: return IR(954, 11);
    case SPV_OPERAND_TYPE_FP_ROUNDING_MODE: return IR(965, 4);
    case SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE: return IR(969, 4);
    case SPV_OPERAND_TYPE_FUNCTION_CONTROL: return IR(973, 7);
    case SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE: return IR(980, 10);
    case SPV_OPERAND_TYPE_GROUP_OPERATION: return IR(990, 10);
    case SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER: return IR(1000, 4);
    case SPV_OPERAND_TYPE_IMAGE: return IR(1004, 21);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE: return IR(1025, 26);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER: return IR(1051, 20);
    case SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER: return IR(1071, 4);
    case SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS: return IR(1075, 3);
    case SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO: return IR(1078, 2);
    case SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS: return IR(1080, 2);
    case SPV_OPERAND_TYPE_LINKAGE_TYPE: return IR(1082, 3);
    case SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL: return IR(1085, 5);
    case SPV_OPERAND_TYPE_LOOP_CONTROL: return IR(1090, 30);
    case SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(1120, 15);
    case SPV_OPERAND_TYPE_MEMORY_ACCESS: return IR(1135, 12);
    case SPV_OPERAND_TYPE_MEMORY_MODEL: return IR(1147, 5);
    case SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID: return IR(1152, 19);
    case SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS: return IR(1171, 1);
    case SPV_OPERAND_TYPE_OVERFLOW_MODES: return IR(1172, 4);
    case SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT: return IR(1176, 2);
    case SPV_OPERAND_TYPE_QUANTIZATION_MODES: return IR(1178, 8);
    case SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS: return IR(1186, 3);
    case SPV_OPERAND_TYPE_RAY_FLAGS: return IR(1189, 13);
    case SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE: return IR(1202, 2);
    case SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE: return IR(1204, 3);
    case SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION: return IR(1207, 2);
    case SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE: return IR(1209, 5);
    case SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE: return IR(1214, 2);
    case SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT: return IR(1216, 42);
    case SPV_OPERAND_TYPE_SCOPE_ID: return IR(1258, 8);
    case SPV_OPERAND_TYPE_SELECTION_CONTROL: return IR(1266, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS: return IR(1269, 1);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(1270, 8);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(1278, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(1281, 2);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS: return IR(1283, 20);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION: return IR(1303, 10);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(1313, 4);
    case SPV_OPERAND_TYPE_SOURCE_LANGUAGE: return IR(1317, 14);
    case SPV_OPERAND_TYPE_STORAGE_CLASS: return IR(1331, 38);
    case SPV_OPERAND_TYPE_STORE_CACHE_CONTROL: return IR(1369, 4);
    case SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS: return IR(1373, 3);
    case SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE: return IR(1376, 5);
    case SPV_OPERAND_TYPE_TENSOR_OPERANDS: return IR(1381, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_IMAGE: return IR(1004, 21);
    case SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS: return IR(1135, 12);
    case SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT: return IR(1176, 2);
    case SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS: return IR(560, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(1120, 15);
    case SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS: return IR(1186, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_FPENCODING: return IR(949, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS: return IR(1381, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_CAPABILITY: return IR(158, 337);
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
static const std::array<InstructionDesc, 871> kInstructionDesc{{
  {spv::Op::OpNop, false, false, IR(0, 0), IR(28380, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpUndef, true, true, IR(39, 2), IR(28436, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpSourceContinued, false, false, IR(11, 1), IR(28442, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpSource, false, false, IR(41, 4), IR(28561, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpSourceExtension, false, false, IR(11, 1), IR(28568, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpName, false, false, IR(45, 2), IR(28584, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpMemberName, false, false, IR(47, 3), IR(28589, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpString, true, false, IR(50, 2), IR(28600, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpLine, false, false, IR(52, 3), IR(28607, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpExtension, false, false, IR(11, 1), IR(28612, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpExtInstImport, true, false, IR(50, 2), IR(28622, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpExtInst, true, true, IR(55, 4), IR(28682, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpMemoryModel, false, false, IR(59, 2), IR(28754, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpEntryPoint, false, false, IR(61, 4), IR(28828, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpExecutionMode, false, false, IR(65, 2), IR(28871, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpCapability, false, false, IR(67, 1), IR(28913, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpTypeVoid, true, false, IR(68, 1), IR(28924, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeBool, true, false, IR(68, 1), IR(28933, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeInt, true, false, IR(69, 3), IR(28942, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeFloat, true, false, IR(72, 3), IR(28987, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeVector, true, false, IR(75, 3), IR(28997, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeMatrix, true, false, IR(75, 3), IR(29008, 11), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeImage, true, false, IR(78, 9), IR(29132, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeSampler, true, false, IR(68, 1), IR(29142, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeSampledImage, true, false, IR(87, 2), IR(29154, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeArray, true, false, IR(89, 3), IR(29171, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeRuntimeArray, true, false, IR(87, 2), IR(29181, 17), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeStruct, true, false, IR(92, 2), IR(29198, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeOpaque, true, false, IR(50, 2), IR(29209, 11), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypePointer, true, false, IR(94, 3), IR(29251, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeFunction, true, false, IR(97, 3), IR(29263, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeEvent, true, false, IR(68, 1), IR(29276, 10), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeDeviceEvent, true, false, IR(68, 1), IR(29286, 16), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeReserveId, true, false, IR(68, 1), IR(29302, 14), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeQueue, true, false, IR(68, 1), IR(29316, 10), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypePipe, true, false, IR(100, 2), IR(29326, 9), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeForwardPointer, false, false, IR(102, 2), IR(29335, 19), IR(0, 0), IR(212, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantTrue, true, true, IR(39, 2), IR(29354, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantFalse, true, true, IR(39, 2), IR(29367, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstant, true, true, IR(104, 3), IR(17264, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantComposite, true, true, IR(107, 3), IR(29419, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantSampler, true, true, IR(110, 5), IR(29515, 16), IR(0, 0), IR(214, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantNull, true, true, IR(39, 2), IR(29531, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantTrue, true, true, IR(39, 2), IR(29544, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantFalse, true, true, IR(39, 2), IR(29561, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstant, true, true, IR(104, 3), IR(29579, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantComposite, true, true, IR(107, 3), IR(29592, 22), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantOp, true, true, IR(115, 3), IR(29655, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpFunction, true, true, IR(118, 4), IR(27678, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionParameter, true, true, IR(39, 2), IR(29704, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionEnd, false, false, IR(0, 0), IR(29722, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionCall, true, true, IR(122, 4), IR(29734, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpVariable, true, true, IR(126, 4), IR(29747, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpImageTexelPointer, true, true, IR(130, 5), IR(29756, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpLoad, true, true, IR(135, 4), IR(29814, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpStore, false, false, IR(139, 3), IR(29819, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCopyMemory, false, false, IR(142, 4), IR(29825, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCopyMemorySized, false, false, IR(146, 5), IR(29836, 16), IR(0, 0), IR(215, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpAccessChain, true, true, IR(122, 4), IR(29852, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpInBoundsAccessChain, true, true, IR(122, 4), IR(29864, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrAccessChain, true, true, IR(151, 5), IR(29884, 15), IR(0, 0), IR(217, 4), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpArrayLength, true, true, IR(156, 4), IR(29899, 12), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpGenericPtrMemSemantics, true, true, IR(160, 3), IR(29911, 23), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpInBoundsPtrAccessChain, true, true, IR(151, 5), IR(29934, 23), IR(0, 0), IR(1, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpDecorate, false, false, IR(163, 2), IR(29985, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpMemberDecorate, false, false, IR(165, 3), IR(29994, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpDecorationGroup, true, false, IR(68, 1), IR(30009, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupDecorate, false, false, IR(168, 2), IR(30025, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupMemberDecorate, false, false, IR(170, 2), IR(30084, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpVectorExtractDynamic, true, true, IR(172, 4), IR(30104, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpVectorInsertDynamic, true, true, IR(130, 5), IR(30125, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpVectorShuffle, true, true, IR(176, 5), IR(30145, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeConstruct, true, true, IR(107, 3), IR(30159, 19), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeExtract, true, true, IR(181, 4), IR(30178, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeInsert, true, true, IR(176, 5), IR(30195, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCopyObject, true, true, IR(160, 3), IR(30211, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpTranspose, true, true, IR(160, 3), IR(30222, 10), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpSampledImage, true, true, IR(172, 4), IR(30232, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleImplicitLod, true, true, IR(185, 5), IR(30277, 23), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleExplicitLod, true, true, IR(190, 5), IR(30323, 23), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleDrefImplicitLod, true, true, IR(195, 6), IR(30346, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleDrefExplicitLod, true, true, IR(201, 6), IR(30373, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjImplicitLod, true, true, IR(185, 5), IR(30400, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjExplicitLod, true, true, IR(190, 5), IR(30427, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjDrefImplicitLod, true, true, IR(195, 6), IR(30454, 31), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjDrefExplicitLod, true, true, IR(201, 6), IR(30485, 31), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageFetch, true, true, IR(185, 5), IR(30516, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageGather, true, true, IR(195, 6), IR(30527, 12), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageDrefGather, true, true, IR(195, 6), IR(30539, 16), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageRead, true, true, IR(185, 5), IR(30555, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageWrite, false, false, IR(207, 4), IR(30565, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImage, true, true, IR(160, 3), IR(27722, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryFormat, true, true, IR(160, 3), IR(30576, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryOrder, true, true, IR(160, 3), IR(30593, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySizeLod, true, true, IR(172, 4), IR(30609, 18), IR(0, 0), IR(221, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySize, true, true, IR(160, 3), IR(30627, 15), IR(0, 0), IR(221, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryLod, true, true, IR(172, 4), IR(30642, 14), IR(0, 0), IR(223, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryLevels, true, true, IR(160, 3), IR(30656, 17), IR(0, 0), IR(221, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySamples, true, true, IR(160, 3), IR(30673, 18), IR(0, 0), IR(221, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertFToU, true, true, IR(160, 3), IR(30691, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertFToS, true, true, IR(160, 3), IR(30703, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertSToF, true, true, IR(160, 3), IR(30715, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToF, true, true, IR(160, 3), IR(30727, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpUConvert, true, true, IR(160, 3), IR(30739, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSConvert, true, true, IR(160, 3), IR(30748, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpFConvert, true, true, IR(160, 3), IR(30757, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpQuantizeToF16, true, true, IR(160, 3), IR(30766, 14), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertPtrToU, true, true, IR(160, 3), IR(30780, 14), IR(0, 0), IR(212, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSatConvertSToU, true, true, IR(160, 3), IR(30794, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSatConvertUToS, true, true, IR(160, 3), IR(30809, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToPtr, true, true, IR(160, 3), IR(30824, 14), IR(0, 0), IR(212, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpPtrCastToGeneric, true, true, IR(160, 3), IR(30838, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpGenericCastToPtr, true, true, IR(160, 3), IR(30855, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpGenericCastToPtrExplicit, true, true, IR(211, 4), IR(30872, 25), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpBitcast, true, true, IR(160, 3), IR(30897, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSNegate, true, true, IR(160, 3), IR(30905, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFNegate, true, true, IR(160, 3), IR(30913, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIAdd, true, true, IR(172, 4), IR(30921, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFAdd, true, true, IR(172, 4), IR(30926, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpISub, true, true, IR(172, 4), IR(30931, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFSub, true, true, IR(172, 4), IR(30936, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIMul, true, true, IR(172, 4), IR(30941, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFMul, true, true, IR(172, 4), IR(30946, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDiv, true, true, IR(172, 4), IR(30951, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSDiv, true, true, IR(172, 4), IR(30956, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFDiv, true, true, IR(172, 4), IR(30961, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUMod, true, true, IR(172, 4), IR(30966, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSRem, true, true, IR(172, 4), IR(30971, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSMod, true, true, IR(172, 4), IR(30976, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFRem, true, true, IR(172, 4), IR(30981, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFMod, true, true, IR(172, 4), IR(30986, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpVectorTimesScalar, true, true, IR(172, 4), IR(30991, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesScalar, true, true, IR(172, 4), IR(31009, 18), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpVectorTimesMatrix, true, true, IR(172, 4), IR(31027, 18), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesVector, true, true, IR(172, 4), IR(31045, 18), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesMatrix, true, true, IR(172, 4), IR(31063, 18), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpOuterProduct, true, true, IR(172, 4), IR(31081, 13), IR(0, 0), IR(67, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpDot, true, true, IR(172, 4), IR(31094, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIAddCarry, true, true, IR(172, 4), IR(31098, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpISubBorrow, true, true, IR(172, 4), IR(31108, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUMulExtended, true, true, IR(172, 4), IR(31119, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSMulExtended, true, true, IR(172, 4), IR(31132, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpAny, true, true, IR(160, 3), IR(31145, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpAll, true, true, IR(160, 3), IR(31149, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsNan, true, true, IR(160, 3), IR(31153, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsInf, true, true, IR(160, 3), IR(31159, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsFinite, true, true, IR(160, 3), IR(31165, 9), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsNormal, true, true, IR(160, 3), IR(31174, 9), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSignBitSet, true, true, IR(160, 3), IR(31183, 11), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLessOrGreater, true, true, IR(172, 4), IR(31194, 14), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), SPV_SPIRV_VERSION_WORD(1,5), PrintingClass::kRelational_and_Logical},
  {spv::Op::OpOrdered, true, true, IR(172, 4), IR(31208, 8), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUnordered, true, true, IR(172, 4), IR(31216, 10), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalEqual, true, true, IR(172, 4), IR(31226, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalNotEqual, true, true, IR(172, 4), IR(31239, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalOr, true, true, IR(172, 4), IR(31255, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalAnd, true, true, IR(172, 4), IR(31265, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalNot, true, true, IR(160, 3), IR(31276, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSelect, true, true, IR(130, 5), IR(31287, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIEqual, true, true, IR(172, 4), IR(31294, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpINotEqual, true, true, IR(172, 4), IR(31301, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUGreaterThan, true, true, IR(172, 4), IR(31311, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSGreaterThan, true, true, IR(172, 4), IR(31324, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUGreaterThanEqual, true, true, IR(172, 4), IR(31337, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSGreaterThanEqual, true, true, IR(172, 4), IR(31355, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpULessThan, true, true, IR(172, 4), IR(31373, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSLessThan, true, true, IR(172, 4), IR(31383, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpULessThanEqual, true, true, IR(172, 4), IR(31393, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSLessThanEqual, true, true, IR(172, 4), IR(31408, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdEqual, true, true, IR(172, 4), IR(31423, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordEqual, true, true, IR(172, 4), IR(31433, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdNotEqual, true, true, IR(172, 4), IR(31445, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordNotEqual, true, true, IR(172, 4), IR(31458, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdLessThan, true, true, IR(172, 4), IR(31473, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordLessThan, true, true, IR(172, 4), IR(31486, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdGreaterThan, true, true, IR(172, 4), IR(31501, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordGreaterThan, true, true, IR(172, 4), IR(31517, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdLessThanEqual, true, true, IR(172, 4), IR(31535, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordLessThanEqual, true, true, IR(172, 4), IR(31553, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdGreaterThanEqual, true, true, IR(172, 4), IR(31573, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordGreaterThanEqual, true, true, IR(172, 4), IR(31594, 23), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpShiftRightLogical, true, true, IR(172, 4), IR(31617, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpShiftRightArithmetic, true, true, IR(172, 4), IR(31635, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpShiftLeftLogical, true, true, IR(172, 4), IR(31656, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseOr, true, true, IR(172, 4), IR(31673, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseXor, true, true, IR(172, 4), IR(31683, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseAnd, true, true, IR(172, 4), IR(31694, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpNot, true, true, IR(160, 3), IR(31705, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldInsert, true, true, IR(215, 6), IR(31709, 15), IR(0, 0), IR(224, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldSExtract, true, true, IR(130, 5), IR(31724, 17), IR(0, 0), IR(224, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldUExtract, true, true, IR(130, 5), IR(31741, 17), IR(0, 0), IR(224, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitReverse, true, true, IR(160, 3), IR(31758, 11), IR(0, 0), IR(224, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitCount, true, true, IR(160, 3), IR(31769, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpDPdx, true, true, IR(160, 3), IR(31778, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdy, true, true, IR(160, 3), IR(31783, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidth, true, true, IR(160, 3), IR(31788, 7), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdxFine, true, true, IR(160, 3), IR(31795, 9), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdyFine, true, true, IR(160, 3), IR(31804, 9), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidthFine, true, true, IR(160, 3), IR(31813, 11), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdxCoarse, true, true, IR(160, 3), IR(31824, 11), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdyCoarse, true, true, IR(160, 3), IR(31835, 11), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidthCoarse, true, true, IR(160, 3), IR(31846, 13), IR(0, 0), IR(226, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpEmitVertex, false, false, IR(0, 0), IR(31859, 11), IR(0, 0), IR(70, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEndPrimitive, false, false, IR(0, 0), IR(31870, 13), IR(0, 0), IR(70, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEmitStreamVertex, false, false, IR(10, 1), IR(31883, 17), IR(0, 0), IR(121, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEndStreamPrimitive, false, false, IR(10, 1), IR(31900, 19), IR(0, 0), IR(121, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpControlBarrier, false, false, IR(221, 3), IR(31956, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpMemoryBarrier, false, false, IR(224, 2), IR(31971, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpAtomicLoad, true, true, IR(226, 5), IR(31985, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicStore, false, false, IR(231, 4), IR(31996, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicExchange, true, true, IR(235, 6), IR(32008, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicCompareExchange, true, true, IR(241, 8), IR(32023, 22), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicCompareExchangeWeak, true, true, IR(241, 8), IR(32045, 26), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), SPV_SPIRV_VERSION_WORD(1,3), PrintingClass::kAtomic},
  {spv::Op::OpAtomicIIncrement, true, true, IR(226, 5), IR(32071, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicIDecrement, true, true, IR(226, 5), IR(32088, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicIAdd, true, true, IR(235, 6), IR(32105, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicISub, true, true, IR(235, 6), IR(32116, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicSMin, true, true, IR(235, 6), IR(32127, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicUMin, true, true, IR(235, 6), IR(32138, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicSMax, true, true, IR(235, 6), IR(32149, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicUMax, true, true, IR(235, 6), IR(32160, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicAnd, true, true, IR(235, 6), IR(32171, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicOr, true, true, IR(235, 6), IR(32181, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicXor, true, true, IR(235, 6), IR(32190, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpPhi, true, true, IR(107, 3), IR(32200, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLoopMerge, false, false, IR(249, 3), IR(32234, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpSelectionMerge, false, false, IR(252, 2), IR(32279, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLabel, true, false, IR(68, 1), IR(32294, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpBranch, false, false, IR(10, 1), IR(32300, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpBranchConditional, false, false, IR(254, 4), IR(32307, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpSwitch, false, false, IR(258, 3), IR(32370, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpKill, false, false, IR(0, 0), IR(32377, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpReturn, false, false, IR(0, 0), IR(32382, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpReturnValue, false, false, IR(10, 1), IR(32389, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpUnreachable, false, false, IR(0, 0), IR(32401, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLifetimeStart, false, false, IR(261, 2), IR(32413, 14), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLifetimeStop, false, false, IR(261, 2), IR(32427, 13), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpGroupAsyncCopy, true, true, IR(263, 8), IR(32440, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupWaitEvents, false, false, IR(271, 3), IR(32455, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupAll, true, true, IR(274, 4), IR(32471, 9), IR(0, 0), IR(227, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupAny, true, true, IR(274, 4), IR(32480, 9), IR(0, 0), IR(227, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBroadcast, true, true, IR(278, 5), IR(32489, 15), IR(0, 0), IR(227, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupIAdd, true, true, IR(283, 5), IR(32537, 10), IR(0, 0), IR(227, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFAdd, true, true, IR(283, 5), IR(32547, 10), IR(0, 0), IR(227, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMin, true, true, IR(283, 5), IR(32557, 10), IR(0, 0), IR(227, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMin, true, true, IR(283, 5), IR(32567, 10), IR(0, 0), IR(227, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMin, true, true, IR(283, 5), IR(32577, 10), IR(0, 0), IR(227, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMax, true, true, IR(283, 5), IR(32587, 10), IR(0, 0), IR(227, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMax, true, true, IR(283, 5), IR(32597, 10), IR(0, 0), IR(227, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMax, true, true, IR(283, 5), IR(32607, 10), IR(0, 0), IR(227, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpReadPipe, true, true, IR(215, 6), IR(32617, 9), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpWritePipe, true, true, IR(215, 6), IR(32626, 10), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReservedReadPipe, true, true, IR(288, 8), IR(32636, 17), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReservedWritePipe, true, true, IR(288, 8), IR(32653, 18), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReserveReadPipePackets, true, true, IR(215, 6), IR(32671, 23), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReserveWritePipePackets, true, true, IR(215, 6), IR(32694, 24), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCommitReadPipe, false, false, IR(296, 4), IR(32718, 15), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCommitWritePipe, false, false, IR(296, 4), IR(32733, 16), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpIsValidReserveId, true, true, IR(160, 3), IR(32749, 17), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetNumPipePackets, true, true, IR(130, 5), IR(32766, 18), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetMaxPipePackets, true, true, IR(130, 5), IR(32784, 18), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupReserveReadPipePackets, true, true, IR(300, 7), IR(32802, 28), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupReserveWritePipePackets, true, true, IR(300, 7), IR(32830, 29), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupCommitReadPipe, false, false, IR(307, 5), IR(32859, 20), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupCommitWritePipe, false, false, IR(307, 5), IR(32879, 21), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpEnqueueMarker, true, true, IR(215, 6), IR(32900, 14), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpEnqueueKernel, true, true, IR(312, 13), IR(32914, 14), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelNDrangeSubGroupCount, true, true, IR(325, 7), IR(32928, 30), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelNDrangeMaxSubGroupSize, true, true, IR(325, 7), IR(32958, 32), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelWorkGroupSize, true, true, IR(215, 6), IR(32990, 23), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelPreferredWorkGroupSizeMultiple, true, true, IR(215, 6), IR(33013, 40), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpRetainEvent, false, false, IR(10, 1), IR(33053, 12), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpReleaseEvent, false, false, IR(10, 1), IR(33065, 13), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpCreateUserEvent, true, true, IR(39, 2), IR(33078, 16), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpIsValidEvent, true, true, IR(160, 3), IR(33094, 13), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpSetUserEventStatus, false, false, IR(36, 2), IR(33107, 19), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpCaptureEventProfilingInfo, false, false, IR(33, 3), IR(33126, 26), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetDefaultQueue, true, true, IR(39, 2), IR(33152, 16), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpBuildNDRange, true, true, IR(130, 5), IR(33168, 13), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpImageSparseSampleImplicitLod, true, true, IR(185, 5), IR(33181, 29), IR(0, 0), IR(228, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleExplicitLod, true, true, IR(190, 5), IR(33210, 29), IR(0, 0), IR(228, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleDrefImplicitLod, true, true, IR(195, 6), IR(33239, 33), IR(0, 0), IR(228, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleDrefExplicitLod, true, true, IR(201, 6), IR(33272, 33), IR(0, 0), IR(228, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjImplicitLod, true, true, IR(185, 5), IR(33305, 33), IR(0, 0), IR(228, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjExplicitLod, true, true, IR(190, 5), IR(33338, 33), IR(0, 0), IR(228, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjDrefImplicitLod, true, true, IR(195, 6), IR(33371, 37), IR(0, 0), IR(228, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjDrefExplicitLod, true, true, IR(201, 6), IR(33408, 37), IR(0, 0), IR(228, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseFetch, true, true, IR(185, 5), IR(33445, 17), IR(0, 0), IR(228, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseGather, true, true, IR(195, 6), IR(33462, 18), IR(0, 0), IR(228, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseDrefGather, true, true, IR(195, 6), IR(33480, 22), IR(0, 0), IR(228, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseTexelsResident, true, true, IR(160, 3), IR(33502, 26), IR(0, 0), IR(228, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpNoLine, false, false, IR(0, 0), IR(33528, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpAtomicFlagTestAndSet, true, true, IR(226, 5), IR(33535, 21), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicFlagClear, false, false, IR(332, 3), IR(33556, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpImageSparseRead, true, true, IR(185, 5), IR(33572, 16), IR(0, 0), IR(228, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpSizeOf, true, true, IR(160, 3), IR(33588, 7), IR(0, 0), IR(1, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpTypePipeStorage, true, false, IR(68, 1), IR(33595, 16), IR(0, 0), IR(229, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantPipeStorage, true, true, IR(335, 5), IR(33611, 20), IR(0, 0), IR(229, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCreatePipeFromPipeStorage, true, true, IR(160, 3), IR(33631, 26), IR(0, 0), IR(229, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetKernelLocalSizeForSubgroupCount, true, true, IR(325, 7), IR(33657, 35), IR(0, 0), IR(162, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelMaxNumSubgroups, true, true, IR(215, 6), IR(33692, 25), IR(0, 0), IR(162, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpTypeNamedBarrier, true, false, IR(68, 1), IR(33717, 17), IR(0, 0), IR(230, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpNamedBarrierInitialize, true, true, IR(160, 3), IR(33734, 23), IR(0, 0), IR(230, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpMemoryNamedBarrier, false, false, IR(332, 3), IR(33757, 19), IR(0, 0), IR(230, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpModuleProcessed, false, false, IR(11, 1), IR(33776, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpExecutionModeId, false, false, IR(65, 2), IR(33792, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,2), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpDecorateId, false, false, IR(163, 2), IR(33808, 11), IR(0, 0), IR(1, 0), IR(188, 1), SPV_SPIRV_VERSION_WORD(1,2), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupNonUniformElect, true, true, IR(340, 3), IR(33819, 21), IR(0, 0), IR(77, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAll, true, true, IR(274, 4), IR(33840, 19), IR(0, 0), IR(231, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAny, true, true, IR(274, 4), IR(33859, 19), IR(0, 0), IR(231, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAllEqual, true, true, IR(274, 4), IR(33878, 24), IR(0, 0), IR(231, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBroadcast, true, true, IR(278, 5), IR(33902, 25), IR(0, 0), IR(232, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBroadcastFirst, true, true, IR(274, 4), IR(33927, 30), IR(0, 0), IR(232, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallot, true, true, IR(274, 4), IR(6575, 22), IR(0, 0), IR(232, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformInverseBallot, true, true, IR(274, 4), IR(33957, 29), IR(0, 0), IR(232, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotBitExtract, true, true, IR(278, 5), IR(33986, 32), IR(0, 0), IR(232, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotBitCount, true, true, IR(283, 5), IR(34018, 30), IR(0, 0), IR(232, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotFindLSB, true, true, IR(274, 4), IR(34048, 29), IR(0, 0), IR(232, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotFindMSB, true, true, IR(274, 4), IR(34077, 29), IR(0, 0), IR(232, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffle, true, true, IR(278, 5), IR(9714, 23), IR(0, 0), IR(233, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleXor, true, true, IR(278, 5), IR(34106, 26), IR(0, 0), IR(233, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleUp, true, true, IR(278, 5), IR(34132, 25), IR(0, 0), IR(234, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleDown, true, true, IR(278, 5), IR(34157, 27), IR(0, 0), IR(234, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformIAdd, true, true, IR(343, 6), IR(34184, 20), IR(0, 0), IR(235, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFAdd, true, true, IR(343, 6), IR(34204, 20), IR(0, 0), IR(235, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformIMul, true, true, IR(343, 6), IR(34224, 20), IR(0, 0), IR(235, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMul, true, true, IR(343, 6), IR(34244, 20), IR(0, 0), IR(235, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformSMin, true, true, IR(343, 6), IR(34264, 20), IR(0, 0), IR(235, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformUMin, true, true, IR(343, 6), IR(34284, 20), IR(0, 0), IR(235, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMin, true, true, IR(343, 6), IR(34304, 20), IR(0, 0), IR(235, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformSMax, true, true, IR(343, 6), IR(34324, 20), IR(0, 0), IR(235, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformUMax, true, true, IR(343, 6), IR(34344, 20), IR(0, 0), IR(235, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMax, true, true, IR(343, 6), IR(34364, 20), IR(0, 0), IR(235, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseAnd, true, true, IR(343, 6), IR(34384, 26), IR(0, 0), IR(235, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseOr, true, true, IR(343, 6), IR(34410, 25), IR(0, 0), IR(235, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseXor, true, true, IR(343, 6), IR(34435, 26), IR(0, 0), IR(235, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalAnd, true, true, IR(343, 6), IR(34461, 26), IR(0, 0), IR(235, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalOr, true, true, IR(343, 6), IR(34487, 25), IR(0, 0), IR(235, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalXor, true, true, IR(343, 6), IR(34512, 26), IR(0, 0), IR(235, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadBroadcast, true, true, IR(278, 5), IR(34538, 29), IR(0, 0), IR(238, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadSwap, true, true, IR(278, 5), IR(34567, 24), IR(0, 0), IR(238, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpCopyLogical, true, true, IR(160, 3), IR(34591, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpPtrEqual, true, true, IR(172, 4), IR(34603, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrNotEqual, true, true, IR(172, 4), IR(34612, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrDiff, true, true, IR(172, 4), IR(34624, 8), IR(0, 0), IR(239, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpColorAttachmentReadEXT, true, true, IR(349, 4), IR(34632, 23), IR(0, 0), IR(154, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpDepthAttachmentReadEXT, true, true, IR(353, 3), IR(34655, 23), IR(0, 0), IR(163, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpStencilAttachmentReadEXT, true, true, IR(353, 3), IR(34678, 25), IR(0, 0), IR(164, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpTypeTensorARM, true, false, IR(356, 4), IR(34703, 14), IR(0, 0), IR(211, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTensorReadARM, true, true, IR(360, 5), IR(34759, 14), IR(0, 0), IR(211, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpTensorWriteARM, false, false, IR(365, 4), IR(34773, 15), IR(0, 0), IR(211, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpTensorQuerySizeARM, true, true, IR(172, 4), IR(34788, 19), IR(0, 0), IR(211, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpGraphConstantARM, true, true, IR(369, 3), IR(34807, 17), IR(0, 0), IR(242, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphEntryPointARM, false, false, IR(372, 3), IR(34824, 19), IR(0, 0), IR(242, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphARM, true, true, IR(39, 2), IR(10005, 9), IR(0, 0), IR(242, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphInputARM, true, true, IR(122, 4), IR(34843, 14), IR(0, 0), IR(242, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphSetOutputARM, false, false, IR(375, 3), IR(34857, 18), IR(0, 0), IR(242, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpGraphEndARM, false, false, IR(0, 0), IR(34875, 12), IR(0, 0), IR(242, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGraph},
  {spv::Op::OpTypeGraphARM, true, false, IR(378, 3), IR(34887, 13), IR(0, 0), IR(242, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTerminateInvocation, false, false, IR(0, 0), IR(34900, 20), IR(0, 0), IR(3, 1), IR(198, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpTypeUntypedPointerKHR, true, false, IR(381, 2), IR(34920, 22), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpUntypedVariableKHR, true, true, IR(383, 5), IR(34942, 19), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedAccessChainKHR, true, true, IR(151, 5), IR(34961, 22), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedInBoundsAccessChainKHR, true, true, IR(151, 5), IR(34983, 30), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpSubgroupBallotKHR, true, true, IR(160, 3), IR(6336, 18), IR(0, 0), IR(243, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupFirstInvocationKHR, true, true, IR(160, 3), IR(35013, 27), IR(0, 0), IR(243, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpUntypedPtrAccessChainKHR, true, true, IR(388, 6), IR(35040, 25), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedInBoundsPtrAccessChainKHR, true, true, IR(388, 6), IR(35065, 33), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedArrayLengthKHR, true, true, IR(394, 5), IR(35098, 22), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedPrefetchKHR, false, false, IR(399, 5), IR(35120, 19), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpFmaKHR, true, true, IR(130, 5), IR(35139, 7), IR(0, 0), IR(244, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSubgroupAllKHR, true, true, IR(160, 3), IR(35146, 15), IR(0, 0), IR(245, 1), IR(41, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupAnyKHR, true, true, IR(160, 3), IR(35161, 15), IR(0, 0), IR(245, 1), IR(41, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupAllEqualKHR, true, true, IR(160, 3), IR(35176, 20), IR(0, 0), IR(245, 1), IR(41, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupNonUniformRotateKHR, true, true, IR(404, 6), IR(14792, 25), IR(0, 0), IR(246, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupReadInvocationKHR, true, true, IR(172, 4), IR(35196, 26), IR(0, 0), IR(243, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpExtInstWithForwardRefsKHR, true, true, IR(410, 5), IR(35222, 26), IR(0, 0), IR(1, 0), IR(199, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpUntypedGroupAsyncCopyKHR, true, true, IR(415, 11), IR(35248, 25), IR(0, 0), IR(93, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpTraceRayKHR, false, false, IR(426, 11), IR(35273, 12), IR(0, 0), IR(61, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpExecuteCallableKHR, false, false, IR(36, 2), IR(35285, 19), IR(0, 0), IR(61, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToAccelerationStructureKHR, true, true, IR(160, 3), IR(35304, 35), IR(0, 0), IR(247, 2), IR(200, 2), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIgnoreIntersectionKHR, false, false, IR(0, 0), IR(35339, 22), IR(0, 0), IR(61, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTerminateRayKHR, false, false, IR(0, 0), IR(35361, 16), IR(0, 0), IR(61, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSDot, true, true, IR(437, 5), IR(35424, 5), IR(171, 1), IR(249, 1), IR(147, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDot, true, true, IR(437, 5), IR(35437, 5), IR(172, 1), IR(249, 1), IR(147, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSUDot, true, true, IR(437, 5), IR(35450, 6), IR(173, 1), IR(249, 1), IR(147, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSDotAccSat, true, true, IR(442, 6), IR(35465, 11), IR(174, 1), IR(249, 1), IR(147, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDotAccSat, true, true, IR(442, 6), IR(35490, 11), IR(175, 1), IR(249, 1), IR(147, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSUDotAccSat, true, true, IR(442, 6), IR(35515, 12), IR(176, 1), IR(249, 1), IR(147, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpTypeCooperativeMatrixKHR, true, false, IR(448, 6), IR(35542, 25), IR(0, 0), IR(87, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeMatrixLoadKHR, true, true, IR(454, 6), IR(35567, 25), IR(0, 0), IR(87, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixStoreKHR, false, false, IR(460, 5), IR(35592, 26), IR(0, 0), IR(87, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixMulAddKHR, true, true, IR(465, 6), IR(35672, 27), IR(0, 0), IR(87, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpCooperativeMatrixLengthKHR, true, true, IR(160, 3), IR(35699, 27), IR(0, 0), IR(87, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpConstantCompositeReplicateEXT, true, true, IR(160, 3), IR(35726, 30), IR(0, 0), IR(250, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCompositeReplicateEXT, true, true, IR(160, 3), IR(35756, 34), IR(0, 0), IR(250, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpCompositeConstructReplicateEXT, true, true, IR(160, 3), IR(35790, 31), IR(0, 0), IR(250, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpTypeRayQueryKHR, true, false, IR(68, 1), IR(35821, 16), IR(0, 0), IR(201, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpRayQueryInitializeKHR, false, false, IR(471, 8), IR(35837, 22), IR(0, 0), IR(201, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryTerminateKHR, false, false, IR(10, 1), IR(35859, 21), IR(0, 0), IR(201, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGenerateIntersectionKHR, false, false, IR(36, 2), IR(35880, 32), IR(0, 0), IR(201, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryConfirmIntersectionKHR, false, false, IR(10, 1), IR(35912, 31), IR(0, 0), IR(201, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryProceedKHR, true, true, IR(160, 3), IR(35943, 19), IR(0, 0), IR(201, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTypeKHR, true, true, IR(172, 4), IR(35962, 31), IR(0, 0), IR(201, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpImageSampleWeightedQCOM, true, true, IR(130, 5), IR(35993, 24), IR(0, 0), IR(251, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBoxFilterQCOM, true, true, IR(130, 5), IR(36017, 19), IR(0, 0), IR(252, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchSSDQCOM, true, true, IR(325, 7), IR(36036, 23), IR(0, 0), IR(253, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchSADQCOM, true, true, IR(325, 7), IR(36059, 23), IR(0, 0), IR(253, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpBitCastArrayQCOM, true, true, IR(160, 3), IR(36082, 17), IR(0, 0), IR(254, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpImageBlockMatchWindowSSDQCOM, true, true, IR(325, 7), IR(36099, 29), IR(0, 0), IR(255, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchWindowSADQCOM, true, true, IR(325, 7), IR(36128, 29), IR(0, 0), IR(255, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchGatherSSDQCOM, true, true, IR(325, 7), IR(36157, 29), IR(0, 0), IR(255, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchGatherSADQCOM, true, true, IR(325, 7), IR(36186, 29), IR(0, 0), IR(255, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpCompositeConstructCoopMatQCOM, true, true, IR(160, 3), IR(36215, 30), IR(0, 0), IR(254, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeExtractCoopMatQCOM, true, true, IR(160, 3), IR(36245, 28), IR(0, 0), IR(254, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpExtractSubArrayQCOM, true, true, IR(172, 4), IR(36273, 20), IR(0, 0), IR(254, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpGroupIAddNonUniformAMD, true, true, IR(283, 5), IR(36293, 23), IR(0, 0), IR(227, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFAddNonUniformAMD, true, true, IR(283, 5), IR(36316, 23), IR(0, 0), IR(227, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMinNonUniformAMD, true, true, IR(283, 5), IR(36339, 23), IR(0, 0), IR(227, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMinNonUniformAMD, true, true, IR(283, 5), IR(36362, 23), IR(0, 0), IR(227, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMinNonUniformAMD, true, true, IR(283, 5), IR(36385, 23), IR(0, 0), IR(227, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMaxNonUniformAMD, true, true, IR(283, 5), IR(36408, 23), IR(0, 0), IR(227, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMaxNonUniformAMD, true, true, IR(283, 5), IR(36431, 23), IR(0, 0), IR(227, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMaxNonUniformAMD, true, true, IR(283, 5), IR(36454, 23), IR(0, 0), IR(227, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpFragmentMaskFetchAMD, true, true, IR(172, 4), IR(36477, 21), IR(0, 0), IR(256, 1), IR(58, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFragmentFetchAMD, true, true, IR(130, 5), IR(36498, 17), IR(0, 0), IR(256, 1), IR(58, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReadClockKHR, true, true, IR(340, 3), IR(36515, 13), IR(0, 0), IR(257, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAllocateNodePayloadsAMDX, true, true, IR(278, 5), IR(36528, 25), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpEnqueueNodePayloadsAMDX, false, false, IR(10, 1), IR(36553, 24), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeNodePayloadArrayAMDX, true, false, IR(87, 2), IR(36577, 25), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFinishWritingNodePayloadAMDX, true, true, IR(160, 3), IR(36602, 29), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpNodePayloadArrayLengthAMDX, true, true, IR(160, 3), IR(36631, 27), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIsNodePayloadValidAMDX, true, true, IR(172, 4), IR(36658, 23), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConstantStringAMDX, true, false, IR(50, 2), IR(36681, 19), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSpecConstantStringAMDX, true, false, IR(50, 2), IR(36700, 23), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpGroupNonUniformQuadAllKHR, true, true, IR(160, 3), IR(36723, 26), IR(0, 0), IR(171, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadAnyKHR, true, true, IR(160, 3), IR(36749, 26), IR(0, 0), IR(171, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpTypeBufferEXT, true, false, IR(381, 2), IR(36775, 14), IR(0, 0), IR(44, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpBufferPointerEXT, true, true, IR(160, 3), IR(36789, 17), IR(0, 0), IR(44, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpAbortKHR, false, false, IR(36, 2), IR(11082, 9), IR(0, 0), IR(258, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpUntypedImageTexelPointerEXT, true, true, IR(215, 6), IR(36806, 28), IR(0, 0), IR(44, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpMemberDecorateIdEXT, false, false, IR(165, 3), IR(36834, 20), IR(0, 0), IR(44, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpConstantSizeOfEXT, true, true, IR(160, 3), IR(36854, 18), IR(0, 0), IR(44, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantDataKHR, true, true, IR(479, 3), IR(11091, 16), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantDataKHR, true, true, IR(479, 3), IR(36872, 20), IR(0, 0), IR(126, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpPoisonKHR, true, true, IR(39, 2), IR(36892, 10), IR(0, 0), IR(172, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpFreezeKHR, true, true, IR(160, 3), IR(36902, 10), IR(0, 0), IR(172, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpHitObjectRecordHitMotionNV, false, false, IR(482, 14), IR(36912, 27), IR(0, 0), IR(259, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitWithIndexMotionNV, false, false, IR(496, 13), IR(36939, 36), IR(0, 0), IR(259, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissMotionNV, false, false, IR(509, 7), IR(36975, 28), IR(0, 0), IR(259, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldToObjectNV, true, true, IR(160, 3), IR(37003, 28), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectToWorldNV, true, true, IR(160, 3), IR(37031, 28), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayDirectionNV, true, true, IR(160, 3), IR(37059, 33), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayOriginNV, true, true, IR(160, 3), IR(37092, 30), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayMotionNV, false, false, IR(496, 13), IR(37122, 26), IR(0, 0), IR(259, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderRecordBufferHandleNV, true, true, IR(160, 3), IR(37148, 39), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderBindingTableRecordIndexNV, true, true, IR(160, 3), IR(37187, 44), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordEmptyNV, false, false, IR(10, 1), IR(37231, 23), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayNV, false, false, IR(516, 12), IR(37254, 20), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitNV, false, false, IR(496, 13), IR(37274, 21), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitWithIndexNV, false, false, IR(516, 12), IR(37295, 30), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissNV, false, false, IR(528, 6), IR(37325, 22), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectExecuteShaderNV, false, false, IR(36, 2), IR(37347, 25), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetCurrentTimeNV, true, true, IR(160, 3), IR(37372, 26), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetAttributesNV, false, false, IR(36, 2), IR(37398, 25), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetHitKindNV, true, true, IR(160, 3), IR(37423, 22), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetPrimitiveIndexNV, true, true, IR(160, 3), IR(37445, 29), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetGeometryIndexNV, true, true, IR(160, 3), IR(37474, 28), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceIdNV, true, true, IR(160, 3), IR(37502, 25), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceCustomIndexNV, true, true, IR(160, 3), IR(37527, 34), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayDirectionNV, true, true, IR(160, 3), IR(37561, 32), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayOriginNV, true, true, IR(160, 3), IR(37593, 29), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMaxNV, true, true, IR(160, 3), IR(37622, 22), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMinNV, true, true, IR(160, 3), IR(37644, 22), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsEmptyNV, true, true, IR(160, 3), IR(37666, 19), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsHitNV, true, true, IR(160, 3), IR(37685, 17), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsMissNV, true, true, IR(160, 3), IR(37702, 18), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHitObjectNV, false, false, IR(534, 3), IR(37720, 29), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHintNV, false, false, IR(36, 2), IR(37749, 24), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeHitObjectNV, true, false, IR(68, 1), IR(37773, 16), IR(0, 0), IR(132, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpImageSampleFootprintNV, true, true, IR(537, 7), IR(37789, 23), IR(0, 0), IR(261, 1), IR(76, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpTypeVectorIdEXT, true, false, IR(89, 3), IR(37812, 16), IR(177, 1), IR(262, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeVectorMatrixMulNV, true, true, IR(544, 13), IR(37852, 29), IR(0, 0), IR(264, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorOuterProductAccumulateNV, false, false, IR(557, 7), IR(37881, 42), IR(0, 0), IR(265, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorReduceSumAccumulateNV, false, false, IR(33, 3), IR(37923, 39), IR(0, 0), IR(265, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorMatrixMulAddNV, true, true, IR(564, 16), IR(37962, 32), IR(0, 0), IR(264, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixConvertNV, true, true, IR(160, 3), IR(37994, 27), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpEmitMeshTasksEXT, false, false, IR(580, 4), IR(38021, 17), IR(0, 0), IR(54, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSetMeshOutputsEXT, false, false, IR(36, 2), IR(38038, 18), IR(0, 0), IR(54, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpGroupNonUniformPartitionEXT, true, true, IR(160, 3), IR(38056, 28), IR(178, 1), IR(192, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpWritePackedPrimitiveIndices4x8NV, false, false, IR(36, 2), IR(38111, 33), IR(0, 0), IR(51, 1), IR(18, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFetchMicroTriangleVertexPositionNV, true, true, IR(325, 7), IR(38144, 35), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFetchMicroTriangleVertexBarycentricNV, true, true, IR(325, 7), IR(38179, 38), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorLoadNV, true, true, IR(584, 5), IR(38217, 24), IR(0, 0), IR(264, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeVectorStoreNV, false, false, IR(589, 4), IR(38241, 25), IR(0, 0), IR(264, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpHitObjectRecordFromQueryEXT, false, false, IR(296, 4), IR(38266, 28), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissEXT, false, false, IR(509, 7), IR(38294, 23), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissMotionEXT, false, false, IR(471, 8), IR(38317, 29), IR(0, 0), IR(268, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetIntersectionTriangleVertexPositionsEXT, true, true, IR(160, 3), IR(38346, 51), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayFlagsEXT, true, true, IR(160, 3), IR(38397, 24), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectSetShaderBindingTableRecordIndexEXT, false, false, IR(36, 2), IR(38421, 45), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectReorderExecuteShaderEXT, false, false, IR(593, 4), IR(38466, 33), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceReorderExecuteEXT, false, false, IR(597, 14), IR(38499, 32), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceMotionReorderExecuteEXT, false, false, IR(611, 15), IR(38531, 38), IR(0, 0), IR(268, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeHitObjectEXT, true, false, IR(68, 1), IR(38569, 17), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpReorderThreadWithHintEXT, false, false, IR(36, 2), IR(38586, 25), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHitObjectEXT, false, false, IR(534, 3), IR(38611, 30), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayEXT, false, false, IR(516, 12), IR(38641, 21), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayMotionEXT, false, false, IR(496, 13), IR(38662, 27), IR(0, 0), IR(268, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordEmptyEXT, false, false, IR(10, 1), IR(38689, 24), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectExecuteShaderEXT, false, false, IR(36, 2), IR(38713, 26), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetCurrentTimeEXT, true, true, IR(160, 3), IR(38739, 27), IR(0, 0), IR(268, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetAttributesEXT, false, false, IR(36, 2), IR(38766, 26), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetHitKindEXT, true, true, IR(160, 3), IR(38792, 23), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetPrimitiveIndexEXT, true, true, IR(160, 3), IR(38815, 30), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetGeometryIndexEXT, true, true, IR(160, 3), IR(38845, 29), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceIdEXT, true, true, IR(160, 3), IR(38874, 26), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceCustomIndexEXT, true, true, IR(160, 3), IR(38900, 35), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayOriginEXT, true, true, IR(160, 3), IR(38935, 31), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayDirectionEXT, true, true, IR(160, 3), IR(38966, 34), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayDirectionEXT, true, true, IR(160, 3), IR(39000, 33), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayOriginEXT, true, true, IR(160, 3), IR(39033, 30), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectToWorldEXT, true, true, IR(160, 3), IR(39063, 29), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldToObjectEXT, true, true, IR(160, 3), IR(39092, 29), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMaxEXT, true, true, IR(160, 3), IR(39121, 23), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReportIntersectionKHR, true, true, IR(172, 4), IR(39144, 22), IR(179, 1), IR(55, 2), IR(24, 2), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIgnoreIntersectionNV, false, false, IR(0, 0), IR(39187, 21), IR(0, 0), IR(57, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTerminateRayNV, false, false, IR(0, 0), IR(39208, 15), IR(0, 0), IR(57, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceNV, false, false, IR(426, 11), IR(39223, 8), IR(0, 0), IR(57, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceMotionNV, false, false, IR(516, 12), IR(39231, 14), IR(0, 0), IR(58, 1), IR(27, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceRayMotionNV, false, false, IR(516, 12), IR(39245, 17), IR(0, 0), IR(58, 1), IR(27, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTriangleVertexPositionsKHR, true, true, IR(172, 4), IR(39262, 50), IR(0, 0), IR(270, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeAccelerationStructureKHR, true, false, IR(68, 1), IR(39312, 29), IR(180, 1), IR(271, 4), IR(202, 4), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpExecuteCallableNV, false, false, IR(36, 2), IR(39369, 18), IR(0, 0), IR(57, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionClusterIdNV, true, true, IR(172, 4), IR(39387, 35), IR(181, 1), IR(65, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetClusterIdNV, true, true, IR(160, 3), IR(39445, 24), IR(0, 0), IR(65, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMinEXT, true, true, IR(160, 3), IR(39469, 23), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderBindingTableRecordIndexEXT, true, true, IR(160, 3), IR(39492, 45), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderRecordBufferHandleEXT, true, true, IR(160, 3), IR(39537, 40), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsEmptyEXT, true, true, IR(160, 3), IR(39577, 20), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsHitEXT, true, true, IR(160, 3), IR(39597, 18), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsMissEXT, true, true, IR(160, 3), IR(39615, 19), IR(0, 0), IR(133, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeCooperativeMatrixNV, true, false, IR(626, 5), IR(39634, 24), IR(0, 0), IR(275, 1), IR(84, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeMatrixLoadNV, true, true, IR(631, 6), IR(39658, 24), IR(0, 0), IR(275, 1), IR(84, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixStoreNV, false, false, IR(637, 5), IR(39682, 25), IR(0, 0), IR(275, 1), IR(84, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixMulAddNV, true, true, IR(130, 5), IR(39707, 26), IR(0, 0), IR(275, 1), IR(84, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixLengthNV, true, true, IR(160, 3), IR(39733, 26), IR(0, 0), IR(275, 1), IR(84, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpBeginInvocationInterlockEXT, false, false, IR(0, 0), IR(39759, 28), IR(0, 0), IR(276, 3), IR(85, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpEndInvocationInterlockEXT, false, false, IR(0, 0), IR(39787, 26), IR(0, 0), IR(276, 3), IR(85, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixReduceNV, true, true, IR(642, 5), IR(39856, 26), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpCooperativeMatrixLoadTensorNV, true, true, IR(647, 7), IR(39957, 30), IR(0, 0), IR(209, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixStoreTensorNV, false, false, IR(654, 5), IR(39987, 31), IR(0, 0), IR(209, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixPerElementOpNV, true, true, IR(151, 5), IR(40018, 32), IR(0, 0), IR(280, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpTypeTensorLayoutNV, true, false, IR(89, 3), IR(40050, 19), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeTensorViewNV, true, false, IR(659, 4), IR(40069, 17), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCreateTensorLayoutNV, true, true, IR(39, 2), IR(40086, 21), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetDimensionNV, true, true, IR(122, 4), IR(40107, 27), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetStrideNV, true, true, IR(122, 4), IR(40134, 24), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSliceNV, true, true, IR(122, 4), IR(40158, 20), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetClampValueNV, true, true, IR(172, 4), IR(40178, 28), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCreateTensorViewNV, true, true, IR(39, 2), IR(40206, 19), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetDimensionNV, true, true, IR(122, 4), IR(40225, 25), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetStrideNV, true, true, IR(122, 4), IR(40250, 22), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpDemoteToHelperInvocation, false, false, IR(0, 0), IR(12607, 25), IR(46, 1), IR(282, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpIsHelperInvocationEXT, true, true, IR(39, 2), IR(40272, 22), IR(0, 0), IR(282, 1), IR(86, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetClipNV, true, true, IR(325, 7), IR(40294, 20), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetBlockSizeNV, true, true, IR(122, 4), IR(40314, 27), IR(0, 0), IR(281, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixTransposeNV, true, true, IR(160, 3), IR(40341, 29), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToImageNV, true, true, IR(160, 3), IR(40370, 18), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToSamplerNV, true, true, IR(160, 3), IR(40388, 20), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertImageToUNV, true, true, IR(160, 3), IR(40408, 18), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertSamplerToUNV, true, true, IR(160, 3), IR(40426, 20), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToSampledImageNV, true, true, IR(160, 3), IR(40446, 25), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertSampledImageToUNV, true, true, IR(160, 3), IR(40471, 25), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSamplerImageAddressingModeNV, false, false, IR(0, 1), IR(40496, 29), IR(0, 0), IR(134, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRawAccessChainNV, true, true, IR(663, 7), IR(40577, 17), IR(0, 0), IR(198, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpRayQueryGetIntersectionSpherePositionNV, true, true, IR(172, 4), IR(40594, 40), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionSphereRadiusNV, true, true, IR(172, 4), IR(40634, 38), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSPositionsNV, true, true, IR(172, 4), IR(40672, 38), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSRadiiNV, true, true, IR(172, 4), IR(40710, 34), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSHitValueNV, true, true, IR(172, 4), IR(40744, 37), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetSpherePositionNV, true, true, IR(160, 3), IR(40781, 29), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetSphereRadiusNV, true, true, IR(160, 3), IR(40810, 27), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetLSSPositionsNV, true, true, IR(160, 3), IR(40837, 27), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetLSSRadiiNV, true, true, IR(160, 3), IR(40864, 23), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsSphereHitNV, true, true, IR(160, 3), IR(40887, 23), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsLSSHitNV, true, true, IR(160, 3), IR(40910, 20), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryIsSphereHitNV, true, true, IR(172, 4), IR(40930, 22), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryIsLSSHitNV, true, true, IR(172, 4), IR(40952, 19), IR(0, 0), IR(63, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSubgroupShuffleINTEL, true, true, IR(172, 4), IR(13139, 21), IR(0, 0), IR(283, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleDownINTEL, true, true, IR(130, 5), IR(40971, 25), IR(0, 0), IR(283, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleUpINTEL, true, true, IR(130, 5), IR(40996, 23), IR(0, 0), IR(283, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleXorINTEL, true, true, IR(172, 4), IR(41019, 24), IR(0, 0), IR(283, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupBlockReadINTEL, true, true, IR(160, 3), IR(41043, 23), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupBlockWriteINTEL, false, false, IR(36, 2), IR(41066, 24), IR(0, 0), IR(284, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageBlockReadINTEL, true, true, IR(172, 4), IR(41090, 28), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageBlockWriteINTEL, false, false, IR(33, 3), IR(41118, 29), IR(0, 0), IR(285, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageMediaBlockReadINTEL, true, true, IR(215, 6), IR(41147, 33), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageMediaBlockWriteINTEL, false, false, IR(670, 5), IR(41180, 34), IR(0, 0), IR(286, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpUCountLeadingZerosINTEL, true, true, IR(160, 3), IR(41214, 24), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUCountTrailingZerosINTEL, true, true, IR(160, 3), IR(41238, 25), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAbsISubINTEL, true, true, IR(172, 4), IR(41263, 13), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAbsUSubINTEL, true, true, IR(172, 4), IR(41276, 13), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAddSatINTEL, true, true, IR(172, 4), IR(41289, 13), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAddSatINTEL, true, true, IR(172, 4), IR(41302, 13), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAverageINTEL, true, true, IR(172, 4), IR(41315, 14), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAverageINTEL, true, true, IR(172, 4), IR(41329, 14), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAverageRoundedINTEL, true, true, IR(172, 4), IR(41343, 21), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAverageRoundedINTEL, true, true, IR(172, 4), IR(41364, 21), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpISubSatINTEL, true, true, IR(172, 4), IR(41385, 13), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUSubSatINTEL, true, true, IR(172, 4), IR(41398, 13), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIMul32x16INTEL, true, true, IR(172, 4), IR(41411, 15), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUMul32x16INTEL, true, true, IR(172, 4), IR(41426, 15), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConstantFunctionPointerINTEL, true, true, IR(160, 3), IR(41441, 29), IR(0, 0), IR(207, 1), IR(104, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFunctionPointerCallINTEL, true, true, IR(107, 3), IR(41470, 25), IR(0, 0), IR(207, 1), IR(104, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmTargetINTEL, true, false, IR(50, 2), IR(41495, 15), IR(0, 0), IR(137, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmINTEL, true, true, IR(675, 6), IR(13357, 9), IR(0, 0), IR(137, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmCallINTEL, true, true, IR(122, 4), IR(41510, 13), IR(0, 0), IR(137, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAtomicFMinEXT, true, true, IR(235, 6), IR(41523, 14), IR(0, 0), IR(288, 4), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicFMaxEXT, true, true, IR(235, 6), IR(41537, 14), IR(0, 0), IR(288, 4), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAssumeTrueKHR, false, false, IR(10, 1), IR(41551, 14), IR(0, 0), IR(292, 1), IR(108, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpExpectKHR, true, true, IR(172, 4), IR(41565, 10), IR(0, 0), IR(292, 1), IR(108, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpDecorateString, false, false, IR(163, 2), IR(41575, 15), IR(182, 1), IR(1, 0), IR(206, 2), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpMemberDecorateString, false, false, IR(165, 3), IR(41611, 21), IR(183, 1), IR(1, 0), IR(206, 2), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpVmeImageINTEL, true, true, IR(172, 4), IR(41659, 14), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeVmeImageINTEL, true, false, IR(87, 2), IR(41673, 18), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImePayloadINTEL, true, false, IR(68, 1), IR(41691, 23), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcRefPayloadINTEL, true, false, IR(68, 1), IR(41714, 23), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcSicPayloadINTEL, true, false, IR(68, 1), IR(41737, 23), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcMcePayloadINTEL, true, false, IR(68, 1), IR(41760, 23), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcMceResultINTEL, true, false, IR(68, 1), IR(41783, 22), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultINTEL, true, false, IR(68, 1), IR(41805, 22), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultSingleReferenceStreamoutINTEL, true, false, IR(68, 1), IR(41827, 46), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultDualReferenceStreamoutINTEL, true, false, IR(68, 1), IR(41873, 44), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeSingleReferenceStreaminINTEL, true, false, IR(68, 1), IR(41917, 39), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeDualReferenceStreaminINTEL, true, false, IR(68, 1), IR(41956, 37), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcRefResultINTEL, true, false, IR(68, 1), IR(41993, 22), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcSicResultINTEL, true, false, IR(68, 1), IR(42015, 22), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL, true, true, IR(172, 4), IR(42037, 60), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL, true, true, IR(172, 4), IR(42097, 53), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterShapePenaltyINTEL, true, true, IR(172, 4), IR(42150, 47), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterShapePenaltyINTEL, true, true, IR(172, 4), IR(42197, 40), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL, true, true, IR(172, 4), IR(42237, 51), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterDirectionPenaltyINTEL, true, true, IR(172, 4), IR(42288, 44), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL, true, true, IR(172, 4), IR(42332, 51), IR(0, 0), IR(294, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL, true, true, IR(172, 4), IR(42383, 56), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL, true, true, IR(39, 2), IR(42439, 50), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL, true, true, IR(39, 2), IR(42489, 52), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL, true, true, IR(39, 2), IR(42541, 49), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetMotionVectorCostFunctionINTEL, true, true, IR(215, 6), IR(42590, 47), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL, true, true, IR(172, 4), IR(42637, 50), IR(0, 0), IR(294, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL, true, true, IR(39, 2), IR(42687, 51), IR(0, 0), IR(294, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL, true, true, IR(39, 2), IR(42738, 56), IR(0, 0), IR(296, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetAcOnlyHaarINTEL, true, true, IR(160, 3), IR(42794, 33), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL, true, true, IR(172, 4), IR(42827, 52), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL, true, true, IR(172, 4), IR(42879, 61), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL, true, true, IR(130, 5), IR(42940, 61), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToImePayloadINTEL, true, true, IR(160, 3), IR(43001, 39), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToImeResultINTEL, true, true, IR(160, 3), IR(43040, 38), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToRefPayloadINTEL, true, true, IR(160, 3), IR(43078, 39), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToRefResultINTEL, true, true, IR(160, 3), IR(43117, 38), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToSicPayloadINTEL, true, true, IR(160, 3), IR(43155, 39), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToSicResultINTEL, true, true, IR(160, 3), IR(43194, 38), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetMotionVectorsINTEL, true, true, IR(160, 3), IR(43232, 36), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterDistortionsINTEL, true, true, IR(160, 3), IR(43268, 39), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetBestInterDistortionsINTEL, true, true, IR(160, 3), IR(43307, 43), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMajorShapeINTEL, true, true, IR(160, 3), IR(43350, 38), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMinorShapeINTEL, true, true, IR(160, 3), IR(43388, 38), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterDirectionsINTEL, true, true, IR(160, 3), IR(43426, 38), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMotionVectorCountINTEL, true, true, IR(160, 3), IR(43464, 45), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterReferenceIdsINTEL, true, true, IR(160, 3), IR(43509, 40), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL, true, true, IR(130, 5), IR(43549, 62), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeInitializeINTEL, true, true, IR(130, 5), IR(43611, 30), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetSingleReferenceINTEL, true, true, IR(130, 5), IR(43641, 38), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetDualReferenceINTEL, true, true, IR(215, 6), IR(43679, 36), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeRefWindowSizeINTEL, true, true, IR(172, 4), IR(43715, 33), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeAdjustRefOffsetINTEL, true, true, IR(215, 6), IR(43748, 35), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(43783, 39), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetMaxMotionVectorCountINTEL, true, true, IR(172, 4), IR(43822, 43), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetUnidirectionalMixDisableINTEL, true, true, IR(160, 3), IR(43865, 47), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetEarlySearchTerminationThresholdINTEL, true, true, IR(172, 4), IR(43912, 54), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetWeightedSadINTEL, true, true, IR(172, 4), IR(43966, 34), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(44000, 47), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(44047, 45), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL, true, true, IR(215, 6), IR(44092, 55), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL, true, true, IR(325, 7), IR(44147, 53), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL, true, true, IR(130, 5), IR(44200, 56), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL, true, true, IR(215, 6), IR(44256, 54), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL, true, true, IR(215, 6), IR(44310, 58), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL, true, true, IR(325, 7), IR(44368, 56), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeConvertToMceResultINTEL, true, true, IR(160, 3), IR(44424, 38), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetSingleReferenceStreaminINTEL, true, true, IR(160, 3), IR(44462, 46), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetDualReferenceStreaminINTEL, true, true, IR(160, 3), IR(44508, 44), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeStripSingleReferenceStreamoutINTEL, true, true, IR(160, 3), IR(44552, 49), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeStripDualReferenceStreamoutINTEL, true, true, IR(160, 3), IR(44601, 47), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL, true, true, IR(172, 4), IR(44648, 70), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL, true, true, IR(172, 4), IR(44718, 68), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL, true, true, IR(172, 4), IR(44786, 69), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL, true, true, IR(130, 5), IR(44855, 68), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL, true, true, IR(130, 5), IR(44923, 66), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL, true, true, IR(130, 5), IR(44989, 67), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetBorderReachedINTEL, true, true, IR(172, 4), IR(45056, 36), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetTruncatedSearchIndicationINTEL, true, true, IR(160, 3), IR(45092, 48), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL, true, true, IR(160, 3), IR(45140, 59), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL, true, true, IR(160, 3), IR(45199, 58), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL, true, true, IR(160, 3), IR(45257, 56), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcFmeInitializeINTEL, true, true, IR(681, 9), IR(45313, 30), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcBmeInitializeINTEL, true, true, IR(690, 10), IR(45343, 30), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(45373, 39), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefSetBidirectionalMixDisableINTEL, true, true, IR(160, 3), IR(45412, 46), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefSetBilinearFilterEnableINTEL, true, true, IR(160, 3), IR(45458, 43), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(45501, 47), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(45548, 45), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithMultiReferenceINTEL, true, true, IR(130, 5), IR(45593, 46), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL, true, true, IR(215, 6), IR(45639, 56), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefConvertToMceResultINTEL, true, true, IR(160, 3), IR(45695, 38), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicInitializeINTEL, true, true, IR(160, 3), IR(45733, 30), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureSkcINTEL, true, true, IR(288, 8), IR(45763, 32), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureIpeLumaINTEL, true, true, IR(690, 10), IR(45795, 36), IR(0, 0), IR(294, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureIpeLumaChromaINTEL, true, true, IR(700, 13), IR(45831, 42), IR(0, 0), IR(296, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetMotionVectorMaskINTEL, true, true, IR(172, 4), IR(45873, 39), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(45912, 39), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraLumaShapePenaltyINTEL, true, true, IR(172, 4), IR(45951, 44), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraLumaModeCostFunctionINTEL, true, true, IR(215, 6), IR(45995, 48), IR(0, 0), IR(294, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraChromaModeCostFunctionINTEL, true, true, IR(172, 4), IR(46043, 50), IR(0, 0), IR(296, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetBilinearFilterEnableINTEL, true, true, IR(160, 3), IR(46093, 43), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetSkcForwardTransformEnableINTEL, true, true, IR(172, 4), IR(46136, 48), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetBlockBasedRawSkipSadINTEL, true, true, IR(172, 4), IR(46184, 43), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateIpeINTEL, true, true, IR(172, 4), IR(46227, 31), IR(0, 0), IR(294, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(46258, 47), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(46305, 45), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithMultiReferenceINTEL, true, true, IR(130, 5), IR(46350, 46), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL, true, true, IR(215, 6), IR(46396, 56), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConvertToMceResultINTEL, true, true, IR(160, 3), IR(46452, 38), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetIpeLumaShapeINTEL, true, true, IR(160, 3), IR(46490, 35), IR(0, 0), IR(294, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetBestIpeLumaDistortionINTEL, true, true, IR(160, 3), IR(46525, 44), IR(0, 0), IR(294, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetBestIpeChromaDistortionINTEL, true, true, IR(160, 3), IR(46569, 46), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedIpeLumaModesINTEL, true, true, IR(160, 3), IR(46615, 41), IR(0, 0), IR(294, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetIpeChromaModeINTEL, true, true, IR(160, 3), IR(46656, 36), IR(0, 0), IR(296, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL, true, true, IR(160, 3), IR(46692, 50), IR(0, 0), IR(294, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL, true, true, IR(160, 3), IR(46742, 48), IR(0, 0), IR(294, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetInterRawSadsINTEL, true, true, IR(160, 3), IR(46790, 35), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpVariableLengthArrayINTEL, true, true, IR(160, 3), IR(13595, 25), IR(0, 0), IR(298, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpSaveMemoryINTEL, true, true, IR(39, 2), IR(46825, 16), IR(0, 0), IR(298, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpRestoreMemoryINTEL, false, false, IR(10, 1), IR(46841, 19), IR(0, 0), IR(298, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpArbitraryFloatSinCosPiALTERA, true, true, IR(713, 8), IR(46860, 29), IR(184, 1), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastALTERA, true, true, IR(713, 8), IR(46917, 25), IR(185, 1), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastFromIntALTERA, true, true, IR(713, 8), IR(46966, 32), IR(186, 1), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastToIntALTERA, true, true, IR(713, 8), IR(47029, 30), IR(187, 1), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatAddALTERA, true, true, IR(721, 10), IR(47088, 24), IR(188, 1), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSubALTERA, true, true, IR(721, 10), IR(47135, 24), IR(189, 1), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatMulALTERA, true, true, IR(721, 10), IR(47182, 24), IR(190, 1), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatDivALTERA, true, true, IR(721, 10), IR(47229, 24), IR(191, 1), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatGTALTERA, true, true, IR(731, 6), IR(47276, 23), IR(192, 1), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatGEALTERA, true, true, IR(731, 6), IR(47321, 23), IR(193, 1), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLTALTERA, true, true, IR(731, 6), IR(47366, 23), IR(194, 1), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLEALTERA, true, true, IR(731, 6), IR(47411, 23), IR(195, 1), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatEQALTERA, true, true, IR(731, 6), IR(47456, 23), IR(196, 1), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatRecipALTERA, true, true, IR(713, 8), IR(47501, 26), IR(197, 1), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatRSqrtALTERA, true, true, IR(713, 8), IR(47552, 26), IR(198, 1), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCbrtALTERA, true, true, IR(713, 8), IR(47603, 25), IR(199, 1), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatHypotALTERA, true, true, IR(721, 10), IR(47652, 26), IR(200, 1), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSqrtALTERA, true, true, IR(713, 8), IR(47703, 25), IR(201, 1), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLogINTEL, true, true, IR(713, 8), IR(47752, 23), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog2INTEL, true, true, IR(713, 8), IR(47775, 24), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog10INTEL, true, true, IR(713, 8), IR(47799, 25), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog1pINTEL, true, true, IR(713, 8), IR(47824, 25), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExpINTEL, true, true, IR(713, 8), IR(47849, 23), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExp2INTEL, true, true, IR(713, 8), IR(47872, 24), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExp10INTEL, true, true, IR(713, 8), IR(47896, 25), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExpm1INTEL, true, true, IR(713, 8), IR(47921, 25), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinINTEL, true, true, IR(713, 8), IR(47946, 23), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCosINTEL, true, true, IR(713, 8), IR(47969, 23), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinCosINTEL, true, true, IR(713, 8), IR(47992, 26), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinPiINTEL, true, true, IR(713, 8), IR(48018, 25), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCosPiINTEL, true, true, IR(713, 8), IR(48043, 25), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatASinINTEL, true, true, IR(713, 8), IR(48068, 24), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatASinPiINTEL, true, true, IR(713, 8), IR(48092, 26), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatACosINTEL, true, true, IR(713, 8), IR(48118, 24), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatACosPiINTEL, true, true, IR(713, 8), IR(48142, 26), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATanINTEL, true, true, IR(713, 8), IR(48168, 24), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATanPiINTEL, true, true, IR(713, 8), IR(48192, 26), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATan2INTEL, true, true, IR(721, 10), IR(48218, 25), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowINTEL, true, true, IR(721, 10), IR(48243, 23), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowRINTEL, true, true, IR(721, 10), IR(48266, 24), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowNINTEL, true, true, IR(721, 10), IR(48290, 24), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpLoopControlINTEL, false, false, IR(18, 1), IR(48314, 17), IR(0, 0), IR(300, 1), IR(118, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAliasDomainDeclINTEL, true, false, IR(737, 2), IR(48331, 21), IR(0, 0), IR(143, 1), IR(130, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAliasScopeDeclINTEL, true, false, IR(739, 3), IR(48352, 20), IR(0, 0), IR(143, 1), IR(130, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAliasScopeListDeclINTEL, true, false, IR(92, 2), IR(48372, 24), IR(0, 0), IR(143, 1), IR(130, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSqrtALTERA, true, true, IR(713, 8), IR(48396, 16), IR(202, 1), IR(197, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedRecipALTERA, true, true, IR(713, 8), IR(48427, 17), IR(203, 1), IR(197, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedRsqrtALTERA, true, true, IR(713, 8), IR(48460, 17), IR(204, 1), IR(197, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinALTERA, true, true, IR(713, 8), IR(48493, 15), IR(205, 1), IR(197, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedCosALTERA, true, true, IR(713, 8), IR(48522, 15), IR(206, 1), IR(197, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinCosALTERA, true, true, IR(713, 8), IR(48551, 18), IR(207, 1), IR(197, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinPiALTERA, true, true, IR(713, 8), IR(48586, 17), IR(208, 1), IR(197, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedCosPiALTERA, true, true, IR(713, 8), IR(48619, 17), IR(209, 1), IR(197, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinCosPiALTERA, true, true, IR(713, 8), IR(48652, 20), IR(210, 1), IR(197, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedLogALTERA, true, true, IR(713, 8), IR(48691, 15), IR(211, 1), IR(197, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedExpALTERA, true, true, IR(713, 8), IR(48720, 15), IR(212, 1), IR(197, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpPtrCastToCrossWorkgroupALTERA, true, true, IR(160, 3), IR(48749, 30), IR(213, 1), IR(208, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpCrossWorkgroupCastToPtrALTERA, true, true, IR(160, 3), IR(48808, 30), IR(214, 1), IR(208, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpReadPipeBlockingALTERA, true, true, IR(172, 4), IR(48867, 23), IR(215, 1), IR(301, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpWritePipeBlockingALTERA, true, true, IR(172, 4), IR(48912, 24), IR(216, 1), IR(301, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFPGARegALTERA, true, true, IR(160, 3), IR(14553, 14), IR(62, 1), IR(302, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpRayQueryGetRayTMinKHR, true, true, IR(160, 3), IR(48959, 22), IR(0, 0), IR(201, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetRayFlagsKHR, true, true, IR(160, 3), IR(48981, 23), IR(0, 0), IR(201, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTKHR, true, true, IR(172, 4), IR(49004, 28), IR(0, 0), IR(201, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceCustomIndexKHR, true, true, IR(172, 4), IR(49032, 46), IR(0, 0), IR(201, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceIdKHR, true, true, IR(172, 4), IR(49078, 37), IR(0, 0), IR(201, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR, true, true, IR(172, 4), IR(49115, 65), IR(0, 0), IR(201, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionGeometryIndexKHR, true, true, IR(172, 4), IR(49180, 40), IR(0, 0), IR(201, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionPrimitiveIndexKHR, true, true, IR(172, 4), IR(49220, 41), IR(0, 0), IR(201, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionBarycentricsKHR, true, true, IR(172, 4), IR(49261, 39), IR(0, 0), IR(201, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionFrontFaceKHR, true, true, IR(172, 4), IR(49300, 36), IR(0, 0), IR(201, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionCandidateAABBOpaqueKHR, true, true, IR(160, 3), IR(49336, 46), IR(0, 0), IR(201, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectRayDirectionKHR, true, true, IR(172, 4), IR(49382, 45), IR(0, 0), IR(201, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectRayOriginKHR, true, true, IR(172, 4), IR(49427, 42), IR(0, 0), IR(201, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetWorldRayDirectionKHR, true, true, IR(160, 3), IR(49469, 32), IR(0, 0), IR(201, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetWorldRayOriginKHR, true, true, IR(160, 3), IR(49501, 29), IR(0, 0), IR(201, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectToWorldKHR, true, true, IR(172, 4), IR(49530, 40), IR(0, 0), IR(201, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionWorldToObjectKHR, true, true, IR(172, 4), IR(49570, 40), IR(0, 0), IR(201, 1), IR(48, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAtomicFAddEXT, true, true, IR(235, 6), IR(49610, 14), IR(0, 0), IR(303, 4), IR(154, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpTypeBufferSurfaceINTEL, true, false, IR(100, 2), IR(49624, 23), IR(0, 0), IR(135, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeStructContinuedINTEL, false, false, IR(742, 1), IR(49647, 25), IR(0, 0), IR(307, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantCompositeContinuedINTEL, false, false, IR(742, 1), IR(49672, 32), IR(0, 0), IR(307, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCompositeContinuedINTEL, false, false, IR(742, 1), IR(49704, 36), IR(0, 0), IR(307, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpCompositeConstructContinuedINTEL, true, true, IR(107, 3), IR(49740, 33), IR(0, 0), IR(307, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpConvertFToBF16INTEL, true, true, IR(160, 3), IR(49773, 20), IR(0, 0), IR(308, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertBF16ToFINTEL, true, true, IR(160, 3), IR(49793, 20), IR(0, 0), IR(308, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpControlBarrierArriveINTEL, false, false, IR(221, 3), IR(49813, 26), IR(0, 0), IR(309, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpControlBarrierWaitINTEL, false, false, IR(221, 3), IR(49839, 24), IR(0, 0), IR(309, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpArithmeticFenceEXT, true, true, IR(160, 3), IR(15006, 19), IR(0, 0), IR(310, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpTaskSequenceCreateALTERA, true, true, IR(743, 7), IR(49863, 25), IR(217, 1), IR(311, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTaskSequenceAsyncALTERA, false, false, IR(168, 2), IR(49912, 24), IR(218, 1), IR(311, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTaskSequenceGetALTERA, true, true, IR(160, 3), IR(49959, 22), IR(219, 1), IR(311, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTaskSequenceReleaseALTERA, false, false, IR(10, 1), IR(50002, 26), IR(220, 1), IR(311, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeTaskSequenceALTERA, true, false, IR(68, 1), IR(50053, 23), IR(221, 1), IR(311, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupBlockPrefetchINTEL, false, false, IR(139, 3), IR(50098, 27), IR(0, 0), IR(312, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadINTEL, false, false, IR(750, 10), IR(50125, 25), IR(0, 0), IR(110, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadTransformINTEL, false, false, IR(750, 10), IR(50150, 34), IR(0, 0), IR(313, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadTransposeINTEL, false, false, IR(750, 10), IR(50184, 34), IR(0, 0), IR(314, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockPrefetchINTEL, false, false, IR(760, 9), IR(50218, 29), IR(0, 0), IR(110, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockStoreINTEL, false, false, IR(750, 10), IR(50247, 26), IR(0, 0), IR(110, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupMatrixMultiplyAccumulateINTEL, true, true, IR(769, 7), IR(15483, 38), IR(0, 0), IR(315, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpBitwiseFunctionINTEL, true, true, IR(215, 6), IR(50335, 21), IR(0, 0), IR(316, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpUntypedVariableLengthArrayINTEL, true, true, IR(172, 4), IR(15549, 32), IR(0, 0), IR(317, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpConditionalExtensionINTEL, false, false, IR(45, 2), IR(50356, 26), IR(0, 0), IR(113, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpConditionalEntryPointINTEL, false, false, IR(776, 5), IR(50382, 27), IR(0, 0), IR(113, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpConditionalCapabilityINTEL, false, false, IR(781, 2), IR(50409, 27), IR(0, 0), IR(113, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpSpecConstantTargetINTEL, true, true, IR(783, 4), IR(50436, 24), IR(0, 0), IR(318, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantArchitectureINTEL, true, true, IR(787, 6), IR(50460, 30), IR(0, 0), IR(318, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCapabilitiesINTEL, true, true, IR(793, 3), IR(50527, 30), IR(0, 0), IR(318, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConditionalCopyObjectINTEL, true, true, IR(107, 3), IR(50557, 27), IR(0, 0), IR(113, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpGroupIMulKHR, true, true, IR(283, 5), IR(50584, 13), IR(0, 0), IR(319, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMulKHR, true, true, IR(283, 5), IR(50597, 13), IR(0, 0), IR(319, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseAndKHR, true, true, IR(283, 5), IR(50610, 19), IR(0, 0), IR(319, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseOrKHR, true, true, IR(283, 5), IR(50629, 18), IR(0, 0), IR(319, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseXorKHR, true, true, IR(283, 5), IR(50647, 19), IR(0, 0), IR(319, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalAndKHR, true, true, IR(283, 5), IR(50666, 19), IR(0, 0), IR(319, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalOrKHR, true, true, IR(283, 5), IR(50685, 18), IR(0, 0), IR(319, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalXorKHR, true, true, IR(283, 5), IR(50703, 19), IR(0, 0), IR(319, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpRoundFToTF32INTEL, true, true, IR(160, 3), IR(50722, 18), IR(0, 0), IR(320, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpMaskedGatherINTEL, true, true, IR(796, 6), IR(50740, 18), IR(0, 0), IR(321, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpMaskedScatterINTEL, false, false, IR(802, 4), IR(50758, 19), IR(0, 0), IR(321, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpConvertHandleToImageINTEL, true, true, IR(160, 3), IR(50777, 26), IR(0, 0), IR(322, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertHandleToSamplerINTEL, true, true, IR(160, 3), IR(50803, 28), IR(0, 0), IR(322, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertHandleToSampledImageINTEL, true, true, IR(160, 3), IR(50831, 33), IR(0, 0), IR(322, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpFDot2MixAcc32VALVE, true, true, IR(130, 5), IR(50864, 19), IR(0, 0), IR(323, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFDot2MixAcc16VALVE, true, true, IR(130, 5), IR(50883, 19), IR(0, 0), IR(325, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFDot4MixAcc32VALVE, true, true, IR(130, 5), IR(50902, 19), IR(0, 0), IR(327, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
}};

// Opcode strings (without the 'Op' prefix) and opcode values, ordered by name.
// The fields in order are:
//   name, either the primary name or an alias, indexing into kStrings
//   index into kInstructionDesc
static const std::array<NameIndex, 924> kInstructionNames{{
  {IR(11082, 9), 438}, // 0 AbortKHR
  {IR(41263, 13), 600}, // 1 AbsISubINTEL
  {IR(41276, 13), 601}, // 2 AbsUSubINTEL
  {IR(29852, 12), 58}, // 3 AccessChain
  {IR(48331, 21), 786}, // 4 AliasDomainDeclINTEL
  {IR(48352, 20), 787}, // 5 AliasScopeDeclINTEL
  {IR(48372, 24), 788}, // 6 AliasScopeListDeclINTEL
  {IR(31149, 4), 143}, // 7 All
  {IR(36528, 25), 426}, // 8 AllocateNodePayloadsAMDX
  {IR(31145, 4), 142}, // 9 Any
  {IR(48118, 24), 777}, // 10 ArbitraryFloatACosINTEL
  {IR(48142, 26), 778}, // 11 ArbitraryFloatACosPiINTEL
  {IR(48068, 24), 775}, // 12 ArbitraryFloatASinINTEL
  {IR(48092, 26), 776}, // 13 ArbitraryFloatASinPiINTEL
  {IR(48218, 25), 781}, // 14 ArbitraryFloatATan2INTEL
  {IR(48168, 24), 779}, // 15 ArbitraryFloatATanINTEL
  {IR(48192, 26), 780}, // 16 ArbitraryFloatATanPiINTEL
  {IR(47088, 24), 748}, // 17 ArbitraryFloatAddALTERA
  {IR(47112, 23), 748}, // 18 ArbitraryFloatAddINTEL
  {IR(46917, 25), 745}, // 19 ArbitraryFloatCastALTERA
  {IR(46966, 32), 746}, // 20 ArbitraryFloatCastFromIntALTERA
  {IR(46998, 31), 746}, // 21 ArbitraryFloatCastFromIntINTEL
  {IR(46942, 24), 745}, // 22 ArbitraryFloatCastINTEL
  {IR(47029, 30), 747}, // 23 ArbitraryFloatCastToIntALTERA
  {IR(47059, 29), 747}, // 24 ArbitraryFloatCastToIntINTEL
  {IR(47603, 25), 759}, // 25 ArbitraryFloatCbrtALTERA
  {IR(47628, 24), 759}, // 26 ArbitraryFloatCbrtINTEL
  {IR(47969, 23), 771}, // 27 ArbitraryFloatCosINTEL
  {IR(48043, 25), 774}, // 28 ArbitraryFloatCosPiINTEL
  {IR(47229, 24), 751}, // 29 ArbitraryFloatDivALTERA
  {IR(47253, 23), 751}, // 30 ArbitraryFloatDivINTEL
  {IR(47456, 23), 756}, // 31 ArbitraryFloatEQALTERA
  {IR(47479, 22), 756}, // 32 ArbitraryFloatEQINTEL
  {IR(47896, 25), 768}, // 33 ArbitraryFloatExp10INTEL
  {IR(47872, 24), 767}, // 34 ArbitraryFloatExp2INTEL
  {IR(47849, 23), 766}, // 35 ArbitraryFloatExpINTEL
  {IR(47921, 25), 769}, // 36 ArbitraryFloatExpm1INTEL
  {IR(47321, 23), 753}, // 37 ArbitraryFloatGEALTERA
  {IR(47344, 22), 753}, // 38 ArbitraryFloatGEINTEL
  {IR(47276, 23), 752}, // 39 ArbitraryFloatGTALTERA
  {IR(47299, 22), 752}, // 40 ArbitraryFloatGTINTEL
  {IR(47652, 26), 760}, // 41 ArbitraryFloatHypotALTERA
  {IR(47678, 25), 760}, // 42 ArbitraryFloatHypotINTEL
  {IR(47411, 23), 755}, // 43 ArbitraryFloatLEALTERA
  {IR(47434, 22), 755}, // 44 ArbitraryFloatLEINTEL
  {IR(47366, 23), 754}, // 45 ArbitraryFloatLTALTERA
  {IR(47389, 22), 754}, // 46 ArbitraryFloatLTINTEL
  {IR(47799, 25), 764}, // 47 ArbitraryFloatLog10INTEL
  {IR(47824, 25), 765}, // 48 ArbitraryFloatLog1pINTEL
  {IR(47775, 24), 763}, // 49 ArbitraryFloatLog2INTEL
  {IR(47752, 23), 762}, // 50 ArbitraryFloatLogINTEL
  {IR(47182, 24), 750}, // 51 ArbitraryFloatMulALTERA
  {IR(47206, 23), 750}, // 52 ArbitraryFloatMulINTEL
  {IR(48243, 23), 782}, // 53 ArbitraryFloatPowINTEL
  {IR(48290, 24), 784}, // 54 ArbitraryFloatPowNINTEL
  {IR(48266, 24), 783}, // 55 ArbitraryFloatPowRINTEL
  {IR(47552, 26), 758}, // 56 ArbitraryFloatRSqrtALTERA
  {IR(47578, 25), 758}, // 57 ArbitraryFloatRSqrtINTEL
  {IR(47501, 26), 757}, // 58 ArbitraryFloatRecipALTERA
  {IR(47527, 25), 757}, // 59 ArbitraryFloatRecipINTEL
  {IR(47992, 26), 772}, // 60 ArbitraryFloatSinCosINTEL
  {IR(46860, 29), 744}, // 61 ArbitraryFloatSinCosPiALTERA
  {IR(46889, 28), 744}, // 62 ArbitraryFloatSinCosPiINTEL
  {IR(47946, 23), 770}, // 63 ArbitraryFloatSinINTEL
  {IR(48018, 25), 773}, // 64 ArbitraryFloatSinPiINTEL
  {IR(47703, 25), 761}, // 65 ArbitraryFloatSqrtALTERA
  {IR(47728, 24), 761}, // 66 ArbitraryFloatSqrtINTEL
  {IR(47135, 24), 749}, // 67 ArbitraryFloatSubALTERA
  {IR(47159, 23), 749}, // 68 ArbitraryFloatSubINTEL
  {IR(15006, 19), 832}, // 69 ArithmeticFenceEXT
  {IR(29899, 12), 61}, // 70 ArrayLength
  {IR(41510, 13), 616}, // 71 AsmCallINTEL
  {IR(13357, 9), 615}, // 72 AsmINTEL
  {IR(41495, 15), 614}, // 73 AsmTargetINTEL
  {IR(41551, 14), 619}, // 74 AssumeTrueKHR
  {IR(32171, 10), 220}, // 75 AtomicAnd
  {IR(32023, 22), 210}, // 76 AtomicCompareExchange
  {IR(32045, 26), 211}, // 77 AtomicCompareExchangeWeak
  {IR(32008, 15), 209}, // 78 AtomicExchange
  {IR(49610, 14), 822}, // 79 AtomicFAddEXT
  {IR(41537, 14), 618}, // 80 AtomicFMaxEXT
  {IR(41523, 14), 617}, // 81 AtomicFMinEXT
  {IR(33556, 16), 292}, // 82 AtomicFlagClear
  {IR(33535, 21), 291}, // 83 AtomicFlagTestAndSet
  {IR(32105, 11), 214}, // 84 AtomicIAdd
  {IR(32088, 17), 213}, // 85 AtomicIDecrement
  {IR(32071, 17), 212}, // 86 AtomicIIncrement
  {IR(32116, 11), 215}, // 87 AtomicISub
  {IR(31985, 11), 207}, // 88 AtomicLoad
  {IR(32181, 9), 221}, // 89 AtomicOr
  {IR(32149, 11), 218}, // 90 AtomicSMax
  {IR(32127, 11), 216}, // 91 AtomicSMin
  {IR(31996, 12), 208}, // 92 AtomicStore
  {IR(32160, 11), 219}, // 93 AtomicUMax
  {IR(32138, 11), 217}, // 94 AtomicUMin
  {IR(32190, 10), 222}, // 95 AtomicXor
  {IR(39759, 28), 546}, // 96 BeginInvocationInterlockEXT
  {IR(36082, 17), 407}, // 97 BitCastArrayQCOM
  {IR(31769, 9), 191}, // 98 BitCount
  {IR(31709, 15), 187}, // 99 BitFieldInsert
  {IR(31724, 17), 188}, // 100 BitFieldSExtract
  {IR(31741, 17), 189}, // 101 BitFieldUExtract
  {IR(31758, 11), 190}, // 102 BitReverse
  {IR(30897, 8), 114}, // 103 Bitcast
  {IR(31694, 11), 185}, // 104 BitwiseAnd
  {IR(50335, 21), 845}, // 105 BitwiseFunctionINTEL
  {IR(31673, 10), 183}, // 106 BitwiseOr
  {IR(31683, 11), 184}, // 107 BitwiseXor
  {IR(32300, 7), 227}, // 108 Branch
  {IR(32307, 18), 228}, // 109 BranchConditional
  {IR(36789, 17), 437}, // 110 BufferPointerEXT
  {IR(33168, 13), 277}, // 111 BuildNDRange
  {IR(28913, 11), 15}, // 112 Capability
  {IR(33126, 26), 275}, // 113 CaptureEventProfilingInfo
  {IR(34632, 23), 344}, // 114 ColorAttachmentReadEXT
  {IR(32718, 15), 255}, // 115 CommitReadPipe
  {IR(32733, 16), 256}, // 116 CommitWritePipe
  {IR(30159, 19), 72}, // 117 CompositeConstruct
  {IR(49740, 33), 827}, // 118 CompositeConstructContinuedINTEL
  {IR(36215, 30), 412}, // 119 CompositeConstructCoopMatQCOM
  {IR(35790, 31), 395}, // 120 CompositeConstructReplicateEXT
  {IR(30178, 17), 73}, // 121 CompositeExtract
  {IR(36245, 28), 413}, // 122 CompositeExtractCoopMatQCOM
  {IR(30195, 16), 74}, // 123 CompositeInsert
  {IR(50409, 27), 849}, // 124 ConditionalCapabilityINTEL
  {IR(50557, 27), 853}, // 125 ConditionalCopyObjectINTEL
  {IR(50382, 27), 848}, // 126 ConditionalEntryPointINTEL
  {IR(50356, 26), 847}, // 127 ConditionalExtensionINTEL
  {IR(17264, 9), 39}, // 128 Constant
  {IR(29419, 18), 40}, // 129 ConstantComposite
  {IR(49672, 32), 825}, // 130 ConstantCompositeContinuedINTEL
  {IR(35726, 30), 393}, // 131 ConstantCompositeReplicateEXT
  {IR(11091, 16), 442}, // 132 ConstantDataKHR
  {IR(29367, 14), 38}, // 133 ConstantFalse
  {IR(41441, 29), 612}, // 134 ConstantFunctionPointerINTEL
  {IR(29531, 13), 42}, // 135 ConstantNull
  {IR(33611, 20), 296}, // 136 ConstantPipeStorage
  {IR(29515, 16), 41}, // 137 ConstantSampler
  {IR(36854, 18), 441}, // 138 ConstantSizeOfEXT
  {IR(36681, 19), 432}, // 139 ConstantStringAMDX
  {IR(29354, 13), 37}, // 140 ConstantTrue
  {IR(31956, 15), 205}, // 141 ControlBarrier
  {IR(49813, 26), 830}, // 142 ControlBarrierArriveINTEL
  {IR(49839, 24), 831}, // 143 ControlBarrierWaitINTEL
  {IR(49793, 20), 829}, // 144 ConvertBF16ToFINTEL
  {IR(49773, 20), 828}, // 145 ConvertFToBF16INTEL
  {IR(30703, 12), 100}, // 146 ConvertFToS
  {IR(30691, 12), 99}, // 147 ConvertFToU
  {IR(50777, 26), 865}, // 148 ConvertHandleToImageINTEL
  {IR(50831, 33), 867}, // 149 ConvertHandleToSampledImageINTEL
  {IR(50803, 28), 866}, // 150 ConvertHandleToSamplerINTEL
  {IR(40408, 18), 569}, // 151 ConvertImageToUNV
  {IR(30780, 14), 107}, // 152 ConvertPtrToU
  {IR(30715, 12), 101}, // 153 ConvertSToF
  {IR(40471, 25), 572}, // 154 ConvertSampledImageToUNV
  {IR(40426, 20), 570}, // 155 ConvertSamplerToUNV
  {IR(35304, 35), 379}, // 156 ConvertUToAccelerationStructureKHR
  {IR(30727, 12), 102}, // 157 ConvertUToF
  {IR(40370, 18), 567}, // 158 ConvertUToImageNV
  {IR(30824, 14), 110}, // 159 ConvertUToPtr
  {IR(40446, 25), 571}, // 160 ConvertUToSampledImageNV
  {IR(40388, 20), 568}, // 161 ConvertUToSamplerNV
  {IR(37994, 27), 485}, // 162 CooperativeMatrixConvertNV
  {IR(35699, 27), 392}, // 163 CooperativeMatrixLengthKHR
  {IR(39733, 26), 545}, // 164 CooperativeMatrixLengthNV
  {IR(35567, 25), 389}, // 165 CooperativeMatrixLoadKHR
  {IR(39658, 24), 542}, // 166 CooperativeMatrixLoadNV
  {IR(39957, 30), 549}, // 167 CooperativeMatrixLoadTensorNV
  {IR(35672, 27), 391}, // 168 CooperativeMatrixMulAddKHR
  {IR(39707, 26), 544}, // 169 CooperativeMatrixMulAddNV
  {IR(40018, 32), 551}, // 170 CooperativeMatrixPerElementOpNV
  {IR(39856, 26), 548}, // 171 CooperativeMatrixReduceNV
  {IR(35592, 26), 390}, // 172 CooperativeMatrixStoreKHR
  {IR(39682, 25), 543}, // 173 CooperativeMatrixStoreNV
  {IR(39987, 31), 550}, // 174 CooperativeMatrixStoreTensorNV
  {IR(40341, 29), 566}, // 175 CooperativeMatrixTransposeNV
  {IR(38217, 24), 492}, // 176 CooperativeVectorLoadNV
  {IR(37962, 32), 484}, // 177 CooperativeVectorMatrixMulAddNV
  {IR(37852, 29), 481}, // 178 CooperativeVectorMatrixMulNV
  {IR(37881, 42), 482}, // 179 CooperativeVectorOuterProductAccumulateNV
  {IR(37923, 39), 483}, // 180 CooperativeVectorReduceSumAccumulateNV
  {IR(38241, 25), 493}, // 181 CooperativeVectorStoreNV
  {IR(34591, 12), 340}, // 182 CopyLogical
  {IR(29825, 11), 56}, // 183 CopyMemory
  {IR(29836, 16), 57}, // 184 CopyMemorySized
  {IR(30211, 11), 75}, // 185 CopyObject
  {IR(33631, 26), 297}, // 186 CreatePipeFromPipeStorage
  {IR(40086, 21), 554}, // 187 CreateTensorLayoutNV
  {IR(40206, 19), 559}, // 188 CreateTensorViewNV
  {IR(33078, 16), 272}, // 189 CreateUserEvent
  {IR(48808, 30), 801}, // 190 CrossWorkgroupCastToPtrALTERA
  {IR(48838, 29), 801}, // 191 CrossWorkgroupCastToPtrINTEL
  {IR(31778, 5), 192}, // 192 DPdx
  {IR(31824, 11), 198}, // 193 DPdxCoarse
  {IR(31795, 9), 195}, // 194 DPdxFine
  {IR(31783, 5), 193}, // 195 DPdy
  {IR(31835, 11), 199}, // 196 DPdyCoarse
  {IR(31804, 9), 196}, // 197 DPdyFine
  {IR(29985, 9), 64}, // 198 Decorate
  {IR(33808, 11), 305}, // 199 DecorateId
  {IR(41575, 15), 621}, // 200 DecorateString
  {IR(41590, 21), 621}, // 201 DecorateStringGOOGLE
  {IR(30009, 16), 66}, // 202 DecorationGroup
  {IR(12607, 25), 562}, // 203 DemoteToHelperInvocation
  {IR(12632, 28), 562}, // 204 DemoteToHelperInvocationEXT
  {IR(34655, 23), 345}, // 205 DepthAttachmentReadEXT
  {IR(31094, 4), 137}, // 206 Dot
  {IR(38021, 17), 486}, // 207 EmitMeshTasksEXT
  {IR(31883, 17), 203}, // 208 EmitStreamVertex
  {IR(31859, 11), 201}, // 209 EmitVertex
  {IR(39787, 26), 547}, // 210 EndInvocationInterlockEXT
  {IR(31870, 13), 202}, // 211 EndPrimitive
  {IR(31900, 19), 204}, // 212 EndStreamPrimitive
  {IR(32914, 14), 265}, // 213 EnqueueKernel
  {IR(32900, 14), 264}, // 214 EnqueueMarker
  {IR(36553, 24), 427}, // 215 EnqueueNodePayloadsAMDX
  {IR(28828, 11), 13}, // 216 EntryPoint
  {IR(35285, 19), 378}, // 217 ExecuteCallableKHR
  {IR(39369, 18), 532}, // 218 ExecuteCallableNV
  {IR(28871, 14), 14}, // 219 ExecutionMode
  {IR(33792, 16), 304}, // 220 ExecutionModeId
  {IR(41565, 10), 620}, // 221 ExpectKHR
  {IR(28682, 8), 11}, // 222 ExtInst
  {IR(28622, 14), 10}, // 223 ExtInstImport
  {IR(35222, 26), 375}, // 224 ExtInstWithForwardRefsKHR
  {IR(28612, 10), 9}, // 225 Extension
  {IR(36273, 20), 414}, // 226 ExtractSubArrayQCOM
  {IR(30926, 5), 118}, // 227 FAdd
  {IR(30757, 9), 105}, // 228 FConvert
  {IR(30961, 5), 125}, // 229 FDiv
  {IR(50883, 19), 869}, // 230 FDot2MixAcc16VALVE
  {IR(50864, 19), 868}, // 231 FDot2MixAcc32VALVE
  {IR(50902, 19), 870}, // 232 FDot4MixAcc32VALVE
  {IR(30986, 5), 130}, // 233 FMod
  {IR(30946, 5), 122}, // 234 FMul
  {IR(30913, 8), 116}, // 235 FNegate
  {IR(31423, 10), 168}, // 236 FOrdEqual
  {IR(31501, 16), 174}, // 237 FOrdGreaterThan
  {IR(31573, 21), 178}, // 238 FOrdGreaterThanEqual
  {IR(31473, 13), 172}, // 239 FOrdLessThan
  {IR(31535, 18), 176}, // 240 FOrdLessThanEqual
  {IR(31445, 13), 170}, // 241 FOrdNotEqual
  {IR(14553, 14), 804}, // 242 FPGARegALTERA
  {IR(14567, 13), 804}, // 243 FPGARegINTEL
  {IR(30981, 5), 129}, // 244 FRem
  {IR(30936, 5), 120}, // 245 FSub
  {IR(31433, 12), 169}, // 246 FUnordEqual
  {IR(31517, 18), 175}, // 247 FUnordGreaterThan
  {IR(31594, 23), 179}, // 248 FUnordGreaterThanEqual
  {IR(31486, 15), 173}, // 249 FUnordLessThan
  {IR(31553, 20), 177}, // 250 FUnordLessThanEqual
  {IR(31458, 15), 171}, // 251 FUnordNotEqual
  {IR(38179, 38), 491}, // 252 FetchMicroTriangleVertexBarycentricNV
  {IR(38144, 35), 490}, // 253 FetchMicroTriangleVertexPositionNV
  {IR(36602, 29), 429}, // 254 FinishWritingNodePayloadAMDX
  {IR(48522, 15), 793}, // 255 FixedCosALTERA
  {IR(48537, 14), 793}, // 256 FixedCosINTEL
  {IR(48619, 17), 796}, // 257 FixedCosPiALTERA
  {IR(48636, 16), 796}, // 258 FixedCosPiINTEL
  {IR(48720, 15), 799}, // 259 FixedExpALTERA
  {IR(48735, 14), 799}, // 260 FixedExpINTEL
  {IR(48691, 15), 798}, // 261 FixedLogALTERA
  {IR(48706, 14), 798}, // 262 FixedLogINTEL
  {IR(48427, 17), 790}, // 263 FixedRecipALTERA
  {IR(48444, 16), 790}, // 264 FixedRecipINTEL
  {IR(48460, 17), 791}, // 265 FixedRsqrtALTERA
  {IR(48477, 16), 791}, // 266 FixedRsqrtINTEL
  {IR(48493, 15), 792}, // 267 FixedSinALTERA
  {IR(48551, 18), 794}, // 268 FixedSinCosALTERA
  {IR(48569, 17), 794}, // 269 FixedSinCosINTEL
  {IR(48652, 20), 797}, // 270 FixedSinCosPiALTERA
  {IR(48672, 19), 797}, // 271 FixedSinCosPiINTEL
  {IR(48508, 14), 792}, // 272 FixedSinINTEL
  {IR(48586, 17), 795}, // 273 FixedSinPiALTERA
  {IR(48603, 16), 795}, // 274 FixedSinPiINTEL
  {IR(48396, 16), 789}, // 275 FixedSqrtALTERA
  {IR(48412, 15), 789}, // 276 FixedSqrtINTEL
  {IR(35139, 7), 369}, // 277 FmaKHR
  {IR(36498, 17), 424}, // 278 FragmentFetchAMD
  {IR(36477, 21), 423}, // 279 FragmentMaskFetchAMD
  {IR(36902, 10), 445}, // 280 FreezeKHR
  {IR(27678, 9), 48}, // 281 Function
  {IR(29734, 13), 51}, // 282 FunctionCall
  {IR(29722, 12), 50}, // 283 FunctionEnd
  {IR(29704, 18), 49}, // 284 FunctionParameter
  {IR(41470, 25), 613}, // 285 FunctionPointerCallINTEL
  {IR(31788, 7), 194}, // 286 Fwidth
  {IR(31846, 13), 200}, // 287 FwidthCoarse
  {IR(31813, 11), 197}, // 288 FwidthFine
  {IR(30855, 17), 112}, // 289 GenericCastToPtr
  {IR(30872, 25), 113}, // 290 GenericCastToPtrExplicit
  {IR(29911, 23), 62}, // 291 GenericPtrMemSemantics
  {IR(33152, 16), 276}, // 292 GetDefaultQueue
  {IR(33657, 35), 298}, // 293 GetKernelLocalSizeForSubgroupCount
  {IR(33692, 25), 299}, // 294 GetKernelMaxNumSubgroups
  {IR(32958, 32), 267}, // 295 GetKernelNDrangeMaxSubGroupSize
  {IR(32928, 30), 266}, // 296 GetKernelNDrangeSubGroupCount
  {IR(33013, 40), 269}, // 297 GetKernelPreferredWorkGroupSizeMultiple
  {IR(32990, 23), 268}, // 298 GetKernelWorkGroupSize
  {IR(32784, 18), 259}, // 299 GetMaxPipePackets
  {IR(32766, 18), 258}, // 300 GetNumPipePackets
  {IR(10005, 9), 353}, // 301 GraphARM
  {IR(34807, 17), 351}, // 302 GraphConstantARM
  {IR(34875, 12), 356}, // 303 GraphEndARM
  {IR(34824, 19), 352}, // 304 GraphEntryPointARM
  {IR(34843, 14), 354}, // 305 GraphInputARM
  {IR(34857, 18), 355}, // 306 GraphSetOutputARM
  {IR(32471, 9), 238}, // 307 GroupAll
  {IR(32480, 9), 239}, // 308 GroupAny
  {IR(32440, 15), 236}, // 309 GroupAsyncCopy
  {IR(50610, 19), 856}, // 310 GroupBitwiseAndKHR
  {IR(50629, 18), 857}, // 311 GroupBitwiseOrKHR
  {IR(50647, 19), 858}, // 312 GroupBitwiseXorKHR
  {IR(32489, 15), 240}, // 313 GroupBroadcast
  {IR(32859, 20), 262}, // 314 GroupCommitReadPipe
  {IR(32879, 21), 263}, // 315 GroupCommitWritePipe
  {IR(30025, 14), 67}, // 316 GroupDecorate
  {IR(32547, 10), 242}, // 317 GroupFAdd
  {IR(36316, 23), 416}, // 318 GroupFAddNonUniformAMD
  {IR(32587, 10), 246}, // 319 GroupFMax
  {IR(36408, 23), 420}, // 320 GroupFMaxNonUniformAMD
  {IR(32557, 10), 243}, // 321 GroupFMin
  {IR(36339, 23), 417}, // 322 GroupFMinNonUniformAMD
  {IR(50597, 13), 855}, // 323 GroupFMulKHR
  {IR(32537, 10), 241}, // 324 GroupIAdd
  {IR(36293, 23), 415}, // 325 GroupIAddNonUniformAMD
  {IR(50584, 13), 854}, // 326 GroupIMulKHR
  {IR(50666, 19), 859}, // 327 GroupLogicalAndKHR
  {IR(50685, 18), 860}, // 328 GroupLogicalOrKHR
  {IR(50703, 19), 861}, // 329 GroupLogicalXorKHR
  {IR(30084, 20), 68}, // 330 GroupMemberDecorate
  {IR(33840, 19), 307}, // 331 GroupNonUniformAll
  {IR(33878, 24), 309}, // 332 GroupNonUniformAllEqual
  {IR(33859, 19), 308}, // 333 GroupNonUniformAny
  {IR(6575, 22), 312}, // 334 GroupNonUniformBallot
  {IR(34018, 30), 315}, // 335 GroupNonUniformBallotBitCount
  {IR(33986, 32), 314}, // 336 GroupNonUniformBallotBitExtract
  {IR(34048, 29), 316}, // 337 GroupNonUniformBallotFindLSB
  {IR(34077, 29), 317}, // 338 GroupNonUniformBallotFindMSB
  {IR(34384, 26), 332}, // 339 GroupNonUniformBitwiseAnd
  {IR(34410, 25), 333}, // 340 GroupNonUniformBitwiseOr
  {IR(34435, 26), 334}, // 341 GroupNonUniformBitwiseXor
  {IR(33902, 25), 310}, // 342 GroupNonUniformBroadcast
  {IR(33927, 30), 311}, // 343 GroupNonUniformBroadcastFirst
  {IR(33819, 21), 306}, // 344 GroupNonUniformElect
  {IR(34204, 20), 323}, // 345 GroupNonUniformFAdd
  {IR(34364, 20), 331}, // 346 GroupNonUniformFMax
  {IR(34304, 20), 328}, // 347 GroupNonUniformFMin
  {IR(34244, 20), 325}, // 348 GroupNonUniformFMul
  {IR(34184, 20), 322}, // 349 GroupNonUniformIAdd
  {IR(34224, 20), 324}, // 350 GroupNonUniformIMul
  {IR(33957, 29), 313}, // 351 GroupNonUniformInverseBallot
  {IR(34461, 26), 335}, // 352 GroupNonUniformLogicalAnd
  {IR(34487, 25), 336}, // 353 GroupNonUniformLogicalOr
  {IR(34512, 26), 337}, // 354 GroupNonUniformLogicalXor
  {IR(38056, 28), 488}, // 355 GroupNonUniformPartitionEXT
  {IR(38084, 27), 488}, // 356 GroupNonUniformPartitionNV
  {IR(36723, 26), 434}, // 357 GroupNonUniformQuadAllKHR
  {IR(36749, 26), 435}, // 358 GroupNonUniformQuadAnyKHR
  {IR(34538, 29), 338}, // 359 GroupNonUniformQuadBroadcast
  {IR(34567, 24), 339}, // 360 GroupNonUniformQuadSwap
  {IR(14792, 25), 373}, // 361 GroupNonUniformRotateKHR
  {IR(34324, 20), 329}, // 362 GroupNonUniformSMax
  {IR(34264, 20), 326}, // 363 GroupNonUniformSMin
  {IR(9714, 23), 318}, // 364 GroupNonUniformShuffle
  {IR(34157, 27), 321}, // 365 GroupNonUniformShuffleDown
  {IR(34132, 25), 320}, // 366 GroupNonUniformShuffleUp
  {IR(34106, 26), 319}, // 367 GroupNonUniformShuffleXor
  {IR(34344, 20), 330}, // 368 GroupNonUniformUMax
  {IR(34284, 20), 327}, // 369 GroupNonUniformUMin
  {IR(32802, 28), 260}, // 370 GroupReserveReadPipePackets
  {IR(32830, 29), 261}, // 371 GroupReserveWritePipePackets
  {IR(32607, 10), 248}, // 372 GroupSMax
  {IR(36454, 23), 422}, // 373 GroupSMaxNonUniformAMD
  {IR(32577, 10), 245}, // 374 GroupSMin
  {IR(36385, 23), 419}, // 375 GroupSMinNonUniformAMD
  {IR(32597, 10), 247}, // 376 GroupUMax
  {IR(36431, 23), 421}, // 377 GroupUMaxNonUniformAMD
  {IR(32567, 10), 244}, // 378 GroupUMin
  {IR(36362, 23), 418}, // 379 GroupUMinNonUniformAMD
  {IR(32455, 16), 237}, // 380 GroupWaitEvents
  {IR(38713, 26), 509}, // 381 HitObjectExecuteShaderEXT
  {IR(37347, 25), 461}, // 382 HitObjectExecuteShaderNV
  {IR(38766, 26), 511}, // 383 HitObjectGetAttributesEXT
  {IR(37398, 25), 463}, // 384 HitObjectGetAttributesNV
  {IR(39445, 24), 534}, // 385 HitObjectGetClusterIdNV
  {IR(38739, 27), 510}, // 386 HitObjectGetCurrentTimeEXT
  {IR(37372, 26), 462}, // 387 HitObjectGetCurrentTimeNV
  {IR(38845, 29), 514}, // 388 HitObjectGetGeometryIndexEXT
  {IR(37474, 28), 466}, // 389 HitObjectGetGeometryIndexNV
  {IR(38792, 23), 512}, // 390 HitObjectGetHitKindEXT
  {IR(37423, 22), 464}, // 391 HitObjectGetHitKindNV
  {IR(38900, 35), 516}, // 392 HitObjectGetInstanceCustomIndexEXT
  {IR(37527, 34), 468}, // 393 HitObjectGetInstanceCustomIndexNV
  {IR(38874, 26), 515}, // 394 HitObjectGetInstanceIdEXT
  {IR(37502, 25), 467}, // 395 HitObjectGetInstanceIdNV
  {IR(38346, 51), 497}, // 396 HitObjectGetIntersectionTriangleVertexPositionsEXT
  {IR(40837, 27), 582}, // 397 HitObjectGetLSSPositionsNV
  {IR(40864, 23), 583}, // 398 HitObjectGetLSSRadiiNV
  {IR(38966, 34), 518}, // 399 HitObjectGetObjectRayDirectionEXT
  {IR(37059, 33), 451}, // 400 HitObjectGetObjectRayDirectionNV
  {IR(38935, 31), 517}, // 401 HitObjectGetObjectRayOriginEXT
  {IR(37092, 30), 452}, // 402 HitObjectGetObjectRayOriginNV
  {IR(39063, 29), 521}, // 403 HitObjectGetObjectToWorldEXT
  {IR(37031, 28), 450}, // 404 HitObjectGetObjectToWorldNV
  {IR(38815, 30), 513}, // 405 HitObjectGetPrimitiveIndexEXT
  {IR(37445, 29), 465}, // 406 HitObjectGetPrimitiveIndexNV
  {IR(38397, 24), 498}, // 407 HitObjectGetRayFlagsEXT
  {IR(39121, 23), 523}, // 408 HitObjectGetRayTMaxEXT
  {IR(37622, 22), 471}, // 409 HitObjectGetRayTMaxNV
  {IR(39469, 23), 535}, // 410 HitObjectGetRayTMinEXT
  {IR(37644, 22), 472}, // 411 HitObjectGetRayTMinNV
  {IR(39492, 45), 536}, // 412 HitObjectGetShaderBindingTableRecordIndexEXT
  {IR(37187, 44), 455}, // 413 HitObjectGetShaderBindingTableRecordIndexNV
  {IR(39537, 40), 537}, // 414 HitObjectGetShaderRecordBufferHandleEXT
  {IR(37148, 39), 454}, // 415 HitObjectGetShaderRecordBufferHandleNV
  {IR(40781, 29), 580}, // 416 HitObjectGetSpherePositionNV
  {IR(40810, 27), 581}, // 417 HitObjectGetSphereRadiusNV
  {IR(39000, 33), 519}, // 418 HitObjectGetWorldRayDirectionEXT
  {IR(37561, 32), 469}, // 419 HitObjectGetWorldRayDirectionNV
  {IR(39033, 30), 520}, // 420 HitObjectGetWorldRayOriginEXT
  {IR(37593, 29), 470}, // 421 HitObjectGetWorldRayOriginNV
  {IR(39092, 29), 522}, // 422 HitObjectGetWorldToObjectEXT
  {IR(37003, 28), 449}, // 423 HitObjectGetWorldToObjectNV
  {IR(39577, 20), 538}, // 424 HitObjectIsEmptyEXT
  {IR(37666, 19), 473}, // 425 HitObjectIsEmptyNV
  {IR(39597, 18), 539}, // 426 HitObjectIsHitEXT
  {IR(37685, 17), 474}, // 427 HitObjectIsHitNV
  {IR(40910, 20), 585}, // 428 HitObjectIsLSSHitNV
  {IR(39615, 19), 540}, // 429 HitObjectIsMissEXT
  {IR(37702, 18), 475}, // 430 HitObjectIsMissNV
  {IR(40887, 23), 584}, // 431 HitObjectIsSphereHitNV
  {IR(38689, 24), 508}, // 432 HitObjectRecordEmptyEXT
  {IR(37231, 23), 456}, // 433 HitObjectRecordEmptyNV
  {IR(38266, 28), 494}, // 434 HitObjectRecordFromQueryEXT
  {IR(36912, 27), 446}, // 435 HitObjectRecordHitMotionNV
  {IR(37274, 21), 458}, // 436 HitObjectRecordHitNV
  {IR(36939, 36), 447}, // 437 HitObjectRecordHitWithIndexMotionNV
  {IR(37295, 30), 459}, // 438 HitObjectRecordHitWithIndexNV
  {IR(38294, 23), 495}, // 439 HitObjectRecordMissEXT
  {IR(38317, 29), 496}, // 440 HitObjectRecordMissMotionEXT
  {IR(36975, 28), 448}, // 441 HitObjectRecordMissMotionNV
  {IR(37325, 22), 460}, // 442 HitObjectRecordMissNV
  {IR(38466, 33), 500}, // 443 HitObjectReorderExecuteShaderEXT
  {IR(38421, 45), 499}, // 444 HitObjectSetShaderBindingTableRecordIndexEXT
  {IR(38531, 38), 502}, // 445 HitObjectTraceMotionReorderExecuteEXT
  {IR(38641, 21), 506}, // 446 HitObjectTraceRayEXT
  {IR(38662, 27), 507}, // 447 HitObjectTraceRayMotionEXT
  {IR(37122, 26), 453}, // 448 HitObjectTraceRayMotionNV
  {IR(37254, 20), 457}, // 449 HitObjectTraceRayNV
  {IR(38499, 32), 501}, // 450 HitObjectTraceReorderExecuteEXT
  {IR(30921, 5), 117}, // 451 IAdd
  {IR(31098, 10), 138}, // 452 IAddCarry
  {IR(41289, 13), 602}, // 453 IAddSatINTEL
  {IR(41315, 14), 604}, // 454 IAverageINTEL
  {IR(41343, 21), 606}, // 455 IAverageRoundedINTEL
  {IR(31294, 7), 158}, // 456 IEqual
  {IR(30941, 5), 121}, // 457 IMul
  {IR(41411, 15), 610}, // 458 IMul32x16INTEL
  {IR(31301, 10), 159}, // 459 INotEqual
  {IR(30931, 5), 119}, // 460 ISub
  {IR(31108, 11), 139}, // 461 ISubBorrow
  {IR(41385, 13), 608}, // 462 ISubSatINTEL
  {IR(35339, 22), 380}, // 463 IgnoreIntersectionKHR
  {IR(39187, 21), 525}, // 464 IgnoreIntersectionNV
  {IR(27722, 6), 91}, // 465 Image
  {IR(36186, 29), 411}, // 466 ImageBlockMatchGatherSADQCOM
  {IR(36157, 29), 410}, // 467 ImageBlockMatchGatherSSDQCOM
  {IR(36059, 23), 406}, // 468 ImageBlockMatchSADQCOM
  {IR(36036, 23), 405}, // 469 ImageBlockMatchSSDQCOM
  {IR(36128, 29), 409}, // 470 ImageBlockMatchWindowSADQCOM
  {IR(36099, 29), 408}, // 471 ImageBlockMatchWindowSSDQCOM
  {IR(36017, 19), 404}, // 472 ImageBoxFilterQCOM
  {IR(30539, 16), 88}, // 473 ImageDrefGather
  {IR(30516, 11), 86}, // 474 ImageFetch
  {IR(30527, 12), 87}, // 475 ImageGather
  {IR(30576, 17), 92}, // 476 ImageQueryFormat
  {IR(30656, 17), 97}, // 477 ImageQueryLevels
  {IR(30642, 14), 96}, // 478 ImageQueryLod
  {IR(30593, 16), 93}, // 479 ImageQueryOrder
  {IR(30673, 18), 98}, // 480 ImageQuerySamples
  {IR(30627, 15), 95}, // 481 ImageQuerySize
  {IR(30609, 18), 94}, // 482 ImageQuerySizeLod
  {IR(30555, 10), 89}, // 483 ImageRead
  {IR(30373, 27), 81}, // 484 ImageSampleDrefExplicitLod
  {IR(30346, 27), 80}, // 485 ImageSampleDrefImplicitLod
  {IR(30323, 23), 79}, // 486 ImageSampleExplicitLod
  {IR(37789, 23), 479}, // 487 ImageSampleFootprintNV
  {IR(30277, 23), 78}, // 488 ImageSampleImplicitLod
  {IR(30485, 31), 85}, // 489 ImageSampleProjDrefExplicitLod
  {IR(30454, 31), 84}, // 490 ImageSampleProjDrefImplicitLod
  {IR(30427, 27), 83}, // 491 ImageSampleProjExplicitLod
  {IR(30400, 27), 82}, // 492 ImageSampleProjImplicitLod
  {IR(35993, 24), 403}, // 493 ImageSampleWeightedQCOM
  {IR(33480, 22), 288}, // 494 ImageSparseDrefGather
  {IR(33445, 17), 286}, // 495 ImageSparseFetch
  {IR(33462, 18), 287}, // 496 ImageSparseGather
  {IR(33572, 16), 293}, // 497 ImageSparseRead
  {IR(33272, 33), 281}, // 498 ImageSparseSampleDrefExplicitLod
  {IR(33239, 33), 280}, // 499 ImageSparseSampleDrefImplicitLod
  {IR(33210, 29), 279}, // 500 ImageSparseSampleExplicitLod
  {IR(33181, 29), 278}, // 501 ImageSparseSampleImplicitLod
  {IR(33408, 37), 285}, // 502 ImageSparseSampleProjDrefExplicitLod
  {IR(33371, 37), 284}, // 503 ImageSparseSampleProjDrefImplicitLod
  {IR(33338, 33), 283}, // 504 ImageSparseSampleProjExplicitLod
  {IR(33305, 33), 282}, // 505 ImageSparseSampleProjImplicitLod
  {IR(33502, 26), 289}, // 506 ImageSparseTexelsResident
  {IR(29756, 18), 53}, // 507 ImageTexelPointer
  {IR(30565, 11), 90}, // 508 ImageWrite
  {IR(29864, 20), 59}, // 509 InBoundsAccessChain
  {IR(29934, 23), 63}, // 510 InBoundsPtrAccessChain
  {IR(31165, 9), 146}, // 511 IsFinite
  {IR(40272, 22), 563}, // 512 IsHelperInvocationEXT
  {IR(31159, 6), 145}, // 513 IsInf
  {IR(31153, 6), 144}, // 514 IsNan
  {IR(36658, 23), 431}, // 515 IsNodePayloadValidAMDX
  {IR(31174, 9), 147}, // 516 IsNormal
  {IR(33094, 13), 273}, // 517 IsValidEvent
  {IR(32749, 17), 257}, // 518 IsValidReserveId
  {IR(32377, 5), 230}, // 519 Kill
  {IR(32294, 6), 226}, // 520 Label
  {IR(31194, 14), 149}, // 521 LessOrGreater
  {IR(32413, 14), 234}, // 522 LifetimeStart
  {IR(32427, 13), 235}, // 523 LifetimeStop
  {IR(28607, 5), 8}, // 524 Line
  {IR(29814, 5), 54}, // 525 Load
  {IR(31265, 11), 155}, // 526 LogicalAnd
  {IR(31226, 13), 152}, // 527 LogicalEqual
  {IR(31276, 11), 156}, // 528 LogicalNot
  {IR(31239, 16), 153}, // 529 LogicalNotEqual
  {IR(31255, 10), 154}, // 530 LogicalOr
  {IR(48314, 17), 785}, // 531 LoopControlINTEL
  {IR(32234, 10), 224}, // 532 LoopMerge
  {IR(50740, 18), 863}, // 533 MaskedGatherINTEL
  {IR(50758, 19), 864}, // 534 MaskedScatterINTEL
  {IR(31063, 18), 135}, // 535 MatrixTimesMatrix
  {IR(31009, 18), 132}, // 536 MatrixTimesScalar
  {IR(31045, 18), 134}, // 537 MatrixTimesVector
  {IR(29994, 15), 65}, // 538 MemberDecorate
  {IR(36834, 20), 440}, // 539 MemberDecorateIdEXT
  {IR(41611, 21), 622}, // 540 MemberDecorateString
  {IR(41632, 27), 622}, // 541 MemberDecorateStringGOOGLE
  {IR(28589, 11), 6}, // 542 MemberName
  {IR(31971, 14), 206}, // 543 MemoryBarrier
  {IR(28754, 12), 12}, // 544 MemoryModel
  {IR(33757, 19), 302}, // 545 MemoryNamedBarrier
  {IR(33776, 16), 303}, // 546 ModuleProcessed
  {IR(28584, 5), 5}, // 547 Name
  {IR(33734, 23), 301}, // 548 NamedBarrierInitialize
  {IR(33528, 7), 290}, // 549 NoLine
  {IR(36631, 27), 430}, // 550 NodePayloadArrayLengthAMDX
  {IR(28380, 4), 0}, // 551 Nop
  {IR(31705, 4), 186}, // 552 Not
  {IR(31208, 8), 150}, // 553 Ordered
  {IR(31081, 13), 136}, // 554 OuterProduct
  {IR(32200, 4), 223}, // 555 Phi
  {IR(36892, 10), 444}, // 556 PoisonKHR
  {IR(29884, 15), 60}, // 557 PtrAccessChain
  {IR(48749, 30), 800}, // 558 PtrCastToCrossWorkgroupALTERA
  {IR(48779, 29), 800}, // 559 PtrCastToCrossWorkgroupINTEL
  {IR(30838, 17), 111}, // 560 PtrCastToGeneric
  {IR(34624, 8), 343}, // 561 PtrDiff
  {IR(34603, 9), 341}, // 562 PtrEqual
  {IR(34612, 12), 342}, // 563 PtrNotEqual
  {IR(30766, 14), 106}, // 564 QuantizeToF16
  {IR(40577, 17), 574}, // 565 RawAccessChainNV
  {IR(35912, 31), 400}, // 566 RayQueryConfirmIntersectionKHR
  {IR(35880, 32), 399}, // 567 RayQueryGenerateIntersectionKHR
  {IR(39422, 23), 533}, // 568 RayQueryGetClusterIdNV
  {IR(49261, 39), 813}, // 569 RayQueryGetIntersectionBarycentricsKHR
  {IR(49336, 46), 815}, // 570 RayQueryGetIntersectionCandidateAABBOpaqueKHR
  {IR(39387, 35), 533}, // 571 RayQueryGetIntersectionClusterIdNV
  {IR(49300, 36), 814}, // 572 RayQueryGetIntersectionFrontFaceKHR
  {IR(49180, 40), 811}, // 573 RayQueryGetIntersectionGeometryIndexKHR
  {IR(49032, 46), 808}, // 574 RayQueryGetIntersectionInstanceCustomIndexKHR
  {IR(49078, 37), 809}, // 575 RayQueryGetIntersectionInstanceIdKHR
  {IR(49115, 65), 810}, // 576 RayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR
  {IR(40744, 37), 579}, // 577 RayQueryGetIntersectionLSSHitValueNV
  {IR(40672, 38), 577}, // 578 RayQueryGetIntersectionLSSPositionsNV
  {IR(40710, 34), 578}, // 579 RayQueryGetIntersectionLSSRadiiNV
  {IR(49382, 45), 816}, // 580 RayQueryGetIntersectionObjectRayDirectionKHR
  {IR(49427, 42), 817}, // 581 RayQueryGetIntersectionObjectRayOriginKHR
  {IR(49530, 40), 820}, // 582 RayQueryGetIntersectionObjectToWorldKHR
  {IR(49220, 41), 812}, // 583 RayQueryGetIntersectionPrimitiveIndexKHR
  {IR(40594, 40), 575}, // 584 RayQueryGetIntersectionSpherePositionNV
  {IR(40634, 38), 576}, // 585 RayQueryGetIntersectionSphereRadiusNV
  {IR(49004, 28), 807}, // 586 RayQueryGetIntersectionTKHR
  {IR(39262, 50), 530}, // 587 RayQueryGetIntersectionTriangleVertexPositionsKHR
  {IR(35962, 31), 402}, // 588 RayQueryGetIntersectionTypeKHR
  {IR(49570, 40), 821}, // 589 RayQueryGetIntersectionWorldToObjectKHR
  {IR(48981, 23), 806}, // 590 RayQueryGetRayFlagsKHR
  {IR(48959, 22), 805}, // 591 RayQueryGetRayTMinKHR
  {IR(49469, 32), 818}, // 592 RayQueryGetWorldRayDirectionKHR
  {IR(49501, 29), 819}, // 593 RayQueryGetWorldRayOriginKHR
  {IR(35837, 22), 397}, // 594 RayQueryInitializeKHR
  {IR(40952, 19), 587}, // 595 RayQueryIsLSSHitNV
  {IR(40930, 22), 586}, // 596 RayQueryIsSphereHitNV
  {IR(35943, 19), 401}, // 597 RayQueryProceedKHR
  {IR(35859, 21), 398}, // 598 RayQueryTerminateKHR
  {IR(36515, 13), 425}, // 599 ReadClockKHR
  {IR(32617, 9), 249}, // 600 ReadPipe
  {IR(48867, 23), 802}, // 601 ReadPipeBlockingALTERA
  {IR(48890, 22), 802}, // 602 ReadPipeBlockingINTEL
  {IR(33065, 13), 271}, // 603 ReleaseEvent
  {IR(38586, 25), 504}, // 604 ReorderThreadWithHintEXT
  {IR(37749, 24), 477}, // 605 ReorderThreadWithHintNV
  {IR(38611, 30), 505}, // 606 ReorderThreadWithHitObjectEXT
  {IR(37720, 29), 476}, // 607 ReorderThreadWithHitObjectNV
  {IR(39144, 22), 524}, // 608 ReportIntersectionKHR
  {IR(39166, 21), 524}, // 609 ReportIntersectionNV
  {IR(32671, 23), 253}, // 610 ReserveReadPipePackets
  {IR(32694, 24), 254}, // 611 ReserveWritePipePackets
  {IR(32636, 17), 251}, // 612 ReservedReadPipe
  {IR(32653, 18), 252}, // 613 ReservedWritePipe
  {IR(46841, 19), 743}, // 614 RestoreMemoryINTEL
  {IR(33053, 12), 270}, // 615 RetainEvent
  {IR(32382, 7), 231}, // 616 Return
  {IR(32389, 12), 232}, // 617 ReturnValue
  {IR(50722, 18), 862}, // 618 RoundFToTF32INTEL
  {IR(30748, 9), 104}, // 619 SConvert
  {IR(30956, 5), 124}, // 620 SDiv
  {IR(35424, 5), 382}, // 621 SDot
  {IR(35465, 11), 385}, // 622 SDotAccSat
  {IR(35476, 14), 385}, // 623 SDotAccSatKHR
  {IR(35429, 8), 382}, // 624 SDotKHR
  {IR(31324, 13), 161}, // 625 SGreaterThan
  {IR(31355, 18), 163}, // 626 SGreaterThanEqual
  {IR(31383, 10), 165}, // 627 SLessThan
  {IR(31408, 15), 167}, // 628 SLessThanEqual
  {IR(30976, 5), 128}, // 629 SMod
  {IR(31132, 13), 141}, // 630 SMulExtended
  {IR(30905, 8), 115}, // 631 SNegate
  {IR(30971, 5), 127}, // 632 SRem
  {IR(35450, 6), 384}, // 633 SUDot
  {IR(35515, 12), 387}, // 634 SUDotAccSat
  {IR(35527, 15), 387}, // 635 SUDotAccSatKHR
  {IR(35456, 9), 384}, // 636 SUDotKHR
  {IR(30232, 13), 77}, // 637 SampledImage
  {IR(40496, 29), 573}, // 638 SamplerImageAddressingModeNV
  {IR(30794, 15), 108}, // 639 SatConvertSToU
  {IR(30809, 15), 109}, // 640 SatConvertUToS
  {IR(46825, 16), 742}, // 641 SaveMemoryINTEL
  {IR(31287, 7), 157}, // 642 Select
  {IR(32279, 15), 225}, // 643 SelectionMerge
  {IR(38038, 18), 487}, // 644 SetMeshOutputsEXT
  {IR(33107, 19), 274}, // 645 SetUserEventStatus
  {IR(31656, 17), 182}, // 646 ShiftLeftLogical
  {IR(31635, 21), 181}, // 647 ShiftRightArithmetic
  {IR(31617, 18), 180}, // 648 ShiftRightLogical
  {IR(31183, 11), 148}, // 649 SignBitSet
  {IR(33588, 7), 294}, // 650 SizeOf
  {IR(28561, 7), 3}, // 651 Source
  {IR(28442, 16), 2}, // 652 SourceContinued
  {IR(28568, 16), 4}, // 653 SourceExtension
  {IR(29579, 13), 45}, // 654 SpecConstant
  {IR(50460, 30), 851}, // 655 SpecConstantArchitectureINTEL
  {IR(50527, 30), 852}, // 656 SpecConstantCapabilitiesINTEL
  {IR(29592, 22), 46}, // 657 SpecConstantComposite
  {IR(49704, 36), 826}, // 658 SpecConstantCompositeContinuedINTEL
  {IR(35756, 34), 394}, // 659 SpecConstantCompositeReplicateEXT
  {IR(36872, 20), 443}, // 660 SpecConstantDataKHR
  {IR(29561, 18), 44}, // 661 SpecConstantFalse
  {IR(29655, 15), 47}, // 662 SpecConstantOp
  {IR(36700, 23), 433}, // 663 SpecConstantStringAMDX
  {IR(50436, 24), 850}, // 664 SpecConstantTargetINTEL
  {IR(29544, 17), 43}, // 665 SpecConstantTrue
  {IR(34678, 25), 346}, // 666 StencilAttachmentReadEXT
  {IR(29819, 6), 55}, // 667 Store
  {IR(28600, 7), 7}, // 668 String
  {IR(50125, 25), 839}, // 669 Subgroup2DBlockLoadINTEL
  {IR(50150, 34), 840}, // 670 Subgroup2DBlockLoadTransformINTEL
  {IR(50184, 34), 841}, // 671 Subgroup2DBlockLoadTransposeINTEL
  {IR(50218, 29), 842}, // 672 Subgroup2DBlockPrefetchINTEL
  {IR(50247, 26), 843}, // 673 Subgroup2DBlockStoreINTEL
  {IR(35176, 20), 372}, // 674 SubgroupAllEqualKHR
  {IR(35146, 15), 370}, // 675 SubgroupAllKHR
  {IR(35161, 15), 371}, // 676 SubgroupAnyKHR
  {IR(45343, 30), 706}, // 677 SubgroupAvcBmeInitializeINTEL
  {IR(45313, 30), 705}, // 678 SubgroupAvcFmeInitializeINTEL
  {IR(43748, 35), 675}, // 679 SubgroupAvcImeAdjustRefOffsetINTEL
  {IR(43783, 39), 676}, // 680 SubgroupAvcImeConvertToMcePayloadINTEL
  {IR(44424, 38), 689}, // 681 SubgroupAvcImeConvertToMceResultINTEL
  {IR(44047, 45), 682}, // 682 SubgroupAvcImeEvaluateWithDualReferenceINTEL
  {IR(44147, 53), 684}, // 683 SubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL
  {IR(44368, 56), 688}, // 684 SubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL
  {IR(44256, 54), 686}, // 685 SubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL
  {IR(44000, 47), 681}, // 686 SubgroupAvcImeEvaluateWithSingleReferenceINTEL
  {IR(44092, 55), 683}, // 687 SubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL
  {IR(44310, 58), 687}, // 688 SubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL
  {IR(44200, 56), 685}, // 689 SubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL
  {IR(45056, 36), 700}, // 690 SubgroupAvcImeGetBorderReachedINTEL
  {IR(44508, 44), 691}, // 691 SubgroupAvcImeGetDualReferenceStreaminINTEL
  {IR(44462, 46), 690}, // 692 SubgroupAvcImeGetSingleReferenceStreaminINTEL
  {IR(44923, 66), 698}, // 693 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL
  {IR(44855, 68), 697}, // 694 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL
  {IR(44989, 67), 699}, // 695 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL
  {IR(44718, 68), 695}, // 696 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL
  {IR(44648, 70), 694}, // 697 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL
  {IR(44786, 69), 696}, // 698 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL
  {IR(45092, 48), 701}, // 699 SubgroupAvcImeGetTruncatedSearchIndicationINTEL
  {IR(45140, 59), 702}, // 700 SubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL
  {IR(45257, 56), 704}, // 701 SubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL
  {IR(45199, 58), 703}, // 702 SubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL
  {IR(43611, 30), 671}, // 703 SubgroupAvcImeInitializeINTEL
  {IR(43715, 33), 674}, // 704 SubgroupAvcImeRefWindowSizeINTEL
  {IR(43679, 36), 673}, // 705 SubgroupAvcImeSetDualReferenceINTEL
  {IR(43912, 54), 679}, // 706 SubgroupAvcImeSetEarlySearchTerminationThresholdINTEL
  {IR(43822, 43), 677}, // 707 SubgroupAvcImeSetMaxMotionVectorCountINTEL
  {IR(43641, 38), 672}, // 708 SubgroupAvcImeSetSingleReferenceINTEL
  {IR(43865, 47), 678}, // 709 SubgroupAvcImeSetUnidirectionalMixDisableINTEL
  {IR(43966, 34), 680}, // 710 SubgroupAvcImeSetWeightedSadINTEL
  {IR(44601, 47), 693}, // 711 SubgroupAvcImeStripDualReferenceStreamoutINTEL
  {IR(44552, 49), 692}, // 712 SubgroupAvcImeStripSingleReferenceStreamoutINTEL
  {IR(43001, 39), 656}, // 713 SubgroupAvcMceConvertToImePayloadINTEL
  {IR(43040, 38), 657}, // 714 SubgroupAvcMceConvertToImeResultINTEL
  {IR(43078, 39), 658}, // 715 SubgroupAvcMceConvertToRefPayloadINTEL
  {IR(43117, 38), 659}, // 716 SubgroupAvcMceConvertToRefResultINTEL
  {IR(43155, 39), 660}, // 717 SubgroupAvcMceConvertToSicPayloadINTEL
  {IR(43194, 38), 661}, // 718 SubgroupAvcMceConvertToSicResultINTEL
  {IR(43307, 43), 664}, // 719 SubgroupAvcMceGetBestInterDistortionsINTEL
  {IR(42439, 50), 645}, // 720 SubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL
  {IR(42037, 60), 637}, // 721 SubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL
  {IR(42237, 51), 641}, // 722 SubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL
  {IR(42383, 56), 644}, // 723 SubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL
  {IR(42150, 47), 639}, // 724 SubgroupAvcMceGetDefaultInterShapePenaltyINTEL
  {IR(42738, 56), 651}, // 725 SubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL
  {IR(42637, 50), 649}, // 726 SubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL
  {IR(42332, 51), 643}, // 727 SubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL
  {IR(42541, 49), 647}, // 728 SubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL
  {IR(42489, 52), 646}, // 729 SubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL
  {IR(42687, 51), 650}, // 730 SubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL
  {IR(43426, 38), 667}, // 731 SubgroupAvcMceGetInterDirectionsINTEL
  {IR(43268, 39), 663}, // 732 SubgroupAvcMceGetInterDistortionsINTEL
  {IR(43350, 38), 665}, // 733 SubgroupAvcMceGetInterMajorShapeINTEL
  {IR(43388, 38), 666}, // 734 SubgroupAvcMceGetInterMinorShapeINTEL
  {IR(43464, 45), 668}, // 735 SubgroupAvcMceGetInterMotionVectorCountINTEL
  {IR(43509, 40), 669}, // 736 SubgroupAvcMceGetInterReferenceIdsINTEL
  {IR(43549, 62), 670}, // 737 SubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL
  {IR(43232, 36), 662}, // 738 SubgroupAvcMceGetMotionVectorsINTEL
  {IR(42794, 33), 652}, // 739 SubgroupAvcMceSetAcOnlyHaarINTEL
  {IR(42940, 61), 655}, // 740 SubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL
  {IR(42097, 53), 638}, // 741 SubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL
  {IR(42288, 44), 642}, // 742 SubgroupAvcMceSetInterDirectionPenaltyINTEL
  {IR(42197, 40), 640}, // 743 SubgroupAvcMceSetInterShapePenaltyINTEL
  {IR(42590, 47), 648}, // 744 SubgroupAvcMceSetMotionVectorCostFunctionINTEL
  {IR(42879, 61), 654}, // 745 SubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL
  {IR(42827, 52), 653}, // 746 SubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL
  {IR(45373, 39), 707}, // 747 SubgroupAvcRefConvertToMcePayloadINTEL
  {IR(45695, 38), 714}, // 748 SubgroupAvcRefConvertToMceResultINTEL
  {IR(45548, 45), 711}, // 749 SubgroupAvcRefEvaluateWithDualReferenceINTEL
  {IR(45593, 46), 712}, // 750 SubgroupAvcRefEvaluateWithMultiReferenceINTEL
  {IR(45639, 56), 713}, // 751 SubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL
  {IR(45501, 47), 710}, // 752 SubgroupAvcRefEvaluateWithSingleReferenceINTEL
  {IR(45412, 46), 708}, // 753 SubgroupAvcRefSetBidirectionalMixDisableINTEL
  {IR(45458, 43), 709}, // 754 SubgroupAvcRefSetBilinearFilterEnableINTEL
  {IR(45831, 42), 718}, // 755 SubgroupAvcSicConfigureIpeLumaChromaINTEL
  {IR(45795, 36), 717}, // 756 SubgroupAvcSicConfigureIpeLumaINTEL
  {IR(45763, 32), 716}, // 757 SubgroupAvcSicConfigureSkcINTEL
  {IR(45912, 39), 720}, // 758 SubgroupAvcSicConvertToMcePayloadINTEL
  {IR(46452, 38), 732}, // 759 SubgroupAvcSicConvertToMceResultINTEL
  {IR(46227, 31), 727}, // 760 SubgroupAvcSicEvaluateIpeINTEL
  {IR(46305, 45), 729}, // 761 SubgroupAvcSicEvaluateWithDualReferenceINTEL
  {IR(46350, 46), 730}, // 762 SubgroupAvcSicEvaluateWithMultiReferenceINTEL
  {IR(46396, 56), 731}, // 763 SubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL
  {IR(46258, 47), 728}, // 764 SubgroupAvcSicEvaluateWithSingleReferenceINTEL
  {IR(46569, 46), 735}, // 765 SubgroupAvcSicGetBestIpeChromaDistortionINTEL
  {IR(46525, 44), 734}, // 766 SubgroupAvcSicGetBestIpeLumaDistortionINTEL
  {IR(46790, 35), 740}, // 767 SubgroupAvcSicGetInterRawSadsINTEL
  {IR(46656, 36), 737}, // 768 SubgroupAvcSicGetIpeChromaModeINTEL
  {IR(46490, 35), 733}, // 769 SubgroupAvcSicGetIpeLumaShapeINTEL
  {IR(45873, 39), 719}, // 770 SubgroupAvcSicGetMotionVectorMaskINTEL
  {IR(46615, 41), 736}, // 771 SubgroupAvcSicGetPackedIpeLumaModesINTEL
  {IR(46692, 50), 738}, // 772 SubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL
  {IR(46742, 48), 739}, // 773 SubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL
  {IR(45733, 30), 715}, // 774 SubgroupAvcSicInitializeINTEL
  {IR(46093, 43), 724}, // 775 SubgroupAvcSicSetBilinearFilterEnableINTEL
  {IR(46184, 43), 726}, // 776 SubgroupAvcSicSetBlockBasedRawSkipSadINTEL
  {IR(46043, 50), 723}, // 777 SubgroupAvcSicSetIntraChromaModeCostFunctionINTEL
  {IR(45995, 48), 722}, // 778 SubgroupAvcSicSetIntraLumaModeCostFunctionINTEL
  {IR(45951, 44), 721}, // 779 SubgroupAvcSicSetIntraLumaShapePenaltyINTEL
  {IR(46136, 48), 725}, // 780 SubgroupAvcSicSetSkcForwardTransformEnableINTEL
  {IR(6336, 18), 363}, // 781 SubgroupBallotKHR
  {IR(50098, 27), 838}, // 782 SubgroupBlockPrefetchINTEL
  {IR(41043, 23), 592}, // 783 SubgroupBlockReadINTEL
  {IR(41066, 24), 593}, // 784 SubgroupBlockWriteINTEL
  {IR(35013, 27), 364}, // 785 SubgroupFirstInvocationKHR
  {IR(41090, 28), 594}, // 786 SubgroupImageBlockReadINTEL
  {IR(41118, 29), 595}, // 787 SubgroupImageBlockWriteINTEL
  {IR(41147, 33), 596}, // 788 SubgroupImageMediaBlockReadINTEL
  {IR(41180, 34), 597}, // 789 SubgroupImageMediaBlockWriteINTEL
  {IR(15483, 38), 844}, // 790 SubgroupMatrixMultiplyAccumulateINTEL
  {IR(35196, 26), 374}, // 791 SubgroupReadInvocationKHR
  {IR(40971, 25), 589}, // 792 SubgroupShuffleDownINTEL
  {IR(13139, 21), 588}, // 793 SubgroupShuffleINTEL
  {IR(40996, 23), 590}, // 794 SubgroupShuffleUpINTEL
  {IR(41019, 24), 591}, // 795 SubgroupShuffleXorINTEL
  {IR(32370, 7), 229}, // 796 Switch
  {IR(49912, 24), 834}, // 797 TaskSequenceAsyncALTERA
  {IR(49936, 23), 834}, // 798 TaskSequenceAsyncINTEL
  {IR(49863, 25), 833}, // 799 TaskSequenceCreateALTERA
  {IR(49888, 24), 833}, // 800 TaskSequenceCreateINTEL
  {IR(49959, 22), 835}, // 801 TaskSequenceGetALTERA
  {IR(49981, 21), 835}, // 802 TaskSequenceGetINTEL
  {IR(50002, 26), 836}, // 803 TaskSequenceReleaseALTERA
  {IR(50028, 25), 836}, // 804 TaskSequenceReleaseINTEL
  {IR(40314, 27), 565}, // 805 TensorLayoutSetBlockSizeNV
  {IR(40178, 28), 558}, // 806 TensorLayoutSetClampValueNV
  {IR(40107, 27), 555}, // 807 TensorLayoutSetDimensionNV
  {IR(40134, 24), 556}, // 808 TensorLayoutSetStrideNV
  {IR(40158, 20), 557}, // 809 TensorLayoutSliceNV
  {IR(34788, 19), 350}, // 810 TensorQuerySizeARM
  {IR(34759, 14), 348}, // 811 TensorReadARM
  {IR(40294, 20), 564}, // 812 TensorViewSetClipNV
  {IR(40225, 25), 560}, // 813 TensorViewSetDimensionNV
  {IR(40250, 22), 561}, // 814 TensorViewSetStrideNV
  {IR(34773, 15), 349}, // 815 TensorWriteARM
  {IR(34900, 20), 358}, // 816 TerminateInvocation
  {IR(35361, 16), 381}, // 817 TerminateRayKHR
  {IR(39208, 15), 526}, // 818 TerminateRayNV
  {IR(39231, 14), 528}, // 819 TraceMotionNV
  {IR(39223, 8), 527}, // 820 TraceNV
  {IR(35273, 12), 377}, // 821 TraceRayKHR
  {IR(39245, 17), 529}, // 822 TraceRayMotionNV
  {IR(30222, 10), 76}, // 823 Transpose
  {IR(39312, 29), 531}, // 824 TypeAccelerationStructureKHR
  {IR(39341, 28), 531}, // 825 TypeAccelerationStructureNV
  {IR(29171, 10), 25}, // 826 TypeArray
  {IR(41956, 37), 634}, // 827 TypeAvcImeDualReferenceStreaminINTEL
  {IR(41691, 23), 625}, // 828 TypeAvcImePayloadINTEL
  {IR(41873, 44), 632}, // 829 TypeAvcImeResultDualReferenceStreamoutINTEL
  {IR(41805, 22), 630}, // 830 TypeAvcImeResultINTEL
  {IR(41827, 46), 631}, // 831 TypeAvcImeResultSingleReferenceStreamoutINTEL
  {IR(41917, 39), 633}, // 832 TypeAvcImeSingleReferenceStreaminINTEL
  {IR(41760, 23), 628}, // 833 TypeAvcMcePayloadINTEL
  {IR(41783, 22), 629}, // 834 TypeAvcMceResultINTEL
  {IR(41714, 23), 626}, // 835 TypeAvcRefPayloadINTEL
  {IR(41993, 22), 635}, // 836 TypeAvcRefResultINTEL
  {IR(41737, 23), 627}, // 837 TypeAvcSicPayloadINTEL
  {IR(42015, 22), 636}, // 838 TypeAvcSicResultINTEL
  {IR(28933, 9), 17}, // 839 TypeBool
  {IR(36775, 14), 436}, // 840 TypeBufferEXT
  {IR(49624, 23), 823}, // 841 TypeBufferSurfaceINTEL
  {IR(35542, 25), 388}, // 842 TypeCooperativeMatrixKHR
  {IR(39634, 24), 541}, // 843 TypeCooperativeMatrixNV
  {IR(37828, 24), 480}, // 844 TypeCooperativeVectorNV
  {IR(29286, 16), 32}, // 845 TypeDeviceEvent
  {IR(29276, 10), 31}, // 846 TypeEvent
  {IR(28987, 10), 19}, // 847 TypeFloat
  {IR(29335, 19), 36}, // 848 TypeForwardPointer
  {IR(29263, 13), 30}, // 849 TypeFunction
  {IR(34887, 13), 357}, // 850 TypeGraphARM
  {IR(38569, 17), 503}, // 851 TypeHitObjectEXT
  {IR(37773, 16), 478}, // 852 TypeHitObjectNV
  {IR(29132, 10), 22}, // 853 TypeImage
  {IR(28942, 8), 18}, // 854 TypeInt
  {IR(29008, 11), 21}, // 855 TypeMatrix
  {IR(33717, 17), 300}, // 856 TypeNamedBarrier
  {IR(36577, 25), 428}, // 857 TypeNodePayloadArrayAMDX
  {IR(29209, 11), 28}, // 858 TypeOpaque
  {IR(29326, 9), 35}, // 859 TypePipe
  {IR(33595, 16), 295}, // 860 TypePipeStorage
  {IR(29251, 12), 29}, // 861 TypePointer
  {IR(29316, 10), 34}, // 862 TypeQueue
  {IR(35821, 16), 396}, // 863 TypeRayQueryKHR
  {IR(29302, 14), 33}, // 864 TypeReserveId
  {IR(29181, 17), 26}, // 865 TypeRuntimeArray
  {IR(29154, 17), 24}, // 866 TypeSampledImage
  {IR(29142, 12), 23}, // 867 TypeSampler
  {IR(29198, 11), 27}, // 868 TypeStruct
  {IR(49647, 25), 824}, // 869 TypeStructContinuedINTEL
  {IR(50053, 23), 837}, // 870 TypeTaskSequenceALTERA
  {IR(50076, 22), 837}, // 871 TypeTaskSequenceINTEL
  {IR(34703, 14), 347}, // 872 TypeTensorARM
  {IR(40050, 19), 552}, // 873 TypeTensorLayoutNV
  {IR(40069, 17), 553}, // 874 TypeTensorViewNV
  {IR(34920, 22), 359}, // 875 TypeUntypedPointerKHR
  {IR(28997, 11), 20}, // 876 TypeVector
  {IR(37812, 16), 480}, // 877 TypeVectorIdEXT
  {IR(41673, 18), 624}, // 878 TypeVmeImageINTEL
  {IR(28924, 9), 16}, // 879 TypeVoid
  {IR(41302, 13), 603}, // 880 UAddSatINTEL
  {IR(41329, 14), 605}, // 881 UAverageINTEL
  {IR(41364, 21), 607}, // 882 UAverageRoundedINTEL
  {IR(30739, 9), 103}, // 883 UConvert
  {IR(41214, 24), 598}, // 884 UCountLeadingZerosINTEL
  {IR(41238, 25), 599}, // 885 UCountTrailingZerosINTEL
  {IR(30951, 5), 123}, // 886 UDiv
  {IR(35437, 5), 383}, // 887 UDot
  {IR(35490, 11), 386}, // 888 UDotAccSat
  {IR(35501, 14), 386}, // 889 UDotAccSatKHR
  {IR(35442, 8), 383}, // 890 UDotKHR
  {IR(31311, 13), 160}, // 891 UGreaterThan
  {IR(31337, 18), 162}, // 892 UGreaterThanEqual
  {IR(31373, 10), 164}, // 893 ULessThan
  {IR(31393, 15), 166}, // 894 ULessThanEqual
  {IR(30966, 5), 126}, // 895 UMod
  {IR(41426, 15), 611}, // 896 UMul32x16INTEL
  {IR(31119, 13), 140}, // 897 UMulExtended
  {IR(41398, 13), 609}, // 898 USubSatINTEL
  {IR(28436, 6), 1}, // 899 Undef
  {IR(31216, 10), 151}, // 900 Unordered
  {IR(32401, 12), 233}, // 901 Unreachable
  {IR(34961, 22), 361}, // 902 UntypedAccessChainKHR
  {IR(35098, 22), 367}, // 903 UntypedArrayLengthKHR
  {IR(35248, 25), 376}, // 904 UntypedGroupAsyncCopyKHR
  {IR(36806, 28), 439}, // 905 UntypedImageTexelPointerEXT
  {IR(34983, 30), 362}, // 906 UntypedInBoundsAccessChainKHR
  {IR(35065, 33), 366}, // 907 UntypedInBoundsPtrAccessChainKHR
  {IR(35120, 19), 368}, // 908 UntypedPrefetchKHR
  {IR(35040, 25), 365}, // 909 UntypedPtrAccessChainKHR
  {IR(34942, 19), 360}, // 910 UntypedVariableKHR
  {IR(15549, 32), 846}, // 911 UntypedVariableLengthArrayINTEL
  {IR(29747, 9), 52}, // 912 Variable
  {IR(13595, 25), 741}, // 913 VariableLengthArrayINTEL
  {IR(30104, 21), 69}, // 914 VectorExtractDynamic
  {IR(30125, 20), 70}, // 915 VectorInsertDynamic
  {IR(30145, 14), 71}, // 916 VectorShuffle
  {IR(31027, 18), 133}, // 917 VectorTimesMatrix
  {IR(30991, 18), 131}, // 918 VectorTimesScalar
  {IR(41659, 14), 623}, // 919 VmeImageINTEL
  {IR(38111, 33), 489}, // 920 WritePackedPrimitiveIndices4x8NV
  {IR(32626, 10), 250}, // 921 WritePipe
  {IR(48912, 24), 803}, // 922 WritePipeBlockingALTERA
  {IR(48936, 23), 803}, // 923 WritePipeBlockingINTEL
}};

// Extended instruction descriptions, ordered by (extinst enum, opcode value).
// The fields in order are:
//   enum value
//   operands, an IndexRange into kOperandSpans
//   name, a character-counting IndexRange into kStrings
//   capabilities, an IndexRange into kCapabilitySpans
static const std::array<ExtInstDesc, 425> kExtInstByValue{{
    {0,IR(0, 0),IR(50921, 14),IR(1, 0)}, // DebugInfoNone in debuginfo
    {1,IR(52, 3),IR(50935, 21),IR(1, 0)}, // DebugCompilationUnit in debuginfo
    {2,IR(806, 3),IR(51008, 15),IR(1, 0)}, // DebugTypeBasic in debuginfo
    {3,IR(809, 3),IR(51057, 17),IR(1, 0)}, // DebugTypePointer in debuginfo
    {4,IR(812, 2),IR(51112, 19),IR(1, 0)}, // DebugTypeQualifier in debuginfo
    {5,IR(168, 2),IR(51131, 15),IR(1, 0)}, // DebugTypeArray in debuginfo
    {6,IR(261, 2),IR(51146, 16),IR(1, 0)}, // DebugTypeVector in debuginfo
    {7,IR(814, 6),IR(51162, 13),IR(1, 0)}, // DebugTypedef in debuginfo
    {8,IR(168, 2),IR(51175, 18),IR(1, 0)}, // DebugTypeFunction in debuginfo
    {9,IR(820, 9),IR(51193, 14),IR(1, 0)}, // DebugTypeEnum in debuginfo
    {10,IR(829, 9),IR(51245, 19),IR(1, 0)}, // DebugTypeComposite in debuginfo
    {11,IR(838, 10),IR(51264, 16),IR(1, 0)}, // DebugTypeMember in debuginfo
    {12,IR(848, 5),IR(51280, 21),IR(1, 0)}, // DebugTypeInheritance in debuginfo
    {13,IR(36, 2),IR(51301, 21),IR(1, 0)}, // DebugTypePtrToMember in debuginfo
    {14,IR(168, 2),IR(51322, 18),IR(1, 0)}, // DebugTypeTemplate in debuginfo
    {15,IR(853, 6),IR(51340, 27),IR(1, 0)}, // DebugTypeTemplateParameter in debuginfo
    {16,IR(859, 5),IR(51367, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in debuginfo
    {17,IR(864, 5),IR(51402, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in debuginfo
    {18,IR(838, 10),IR(51433, 20),IR(1, 0)}, // DebugGlobalVariable in debuginfo
    {19,IR(869, 8),IR(51453, 25),IR(1, 0)}, // DebugFunctionDeclaration in debuginfo
    {20,IR(877, 11),IR(51478, 14),IR(1, 0)}, // DebugFunction in debuginfo
    {21,IR(888, 5),IR(51492, 18),IR(1, 0)}, // DebugLexicalBlock in debuginfo
    {22,IR(893, 3),IR(51510, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in debuginfo
    {23,IR(896, 2),IR(51541, 11),IR(1, 0)}, // DebugScope in debuginfo
    {24,IR(0, 0),IR(51552, 13),IR(1, 0)}, // DebugNoScope in debuginfo
    {25,IR(898, 3),IR(51565, 15),IR(1, 0)}, // DebugInlinedAt in debuginfo
    {26,IR(901, 7),IR(51622, 19),IR(1, 0)}, // DebugLocalVariable in debuginfo
    {27,IR(36, 2),IR(51641, 21),IR(1, 0)}, // DebugInlinedVariable in debuginfo
    {28,IR(33, 3),IR(51662, 13),IR(1, 0)}, // DebugDeclare in debuginfo
    {29,IR(375, 3),IR(51675, 11),IR(1, 0)}, // DebugValue in debuginfo
    {30,IR(908, 2),IR(51719, 15),IR(1, 0)}, // DebugOperation in debuginfo
    {31,IR(742, 1),IR(51734, 16),IR(1, 0)}, // DebugExpression in debuginfo
    {32,IR(910, 4),IR(51750, 14),IR(1, 0)}, // DebugMacroDef in debuginfo
    {33,IR(893, 3),IR(51764, 16),IR(1, 0)}, // DebugMacroUndef in debuginfo
    {1,IR(10, 1),IR(51780, 6),IR(1, 0)}, // Round in glsl_std_450
    {2,IR(10, 1),IR(51786, 10),IR(1, 0)}, // RoundEven in glsl_std_450
    {3,IR(10, 1),IR(51796, 6),IR(1, 0)}, // Trunc in glsl_std_450
    {4,IR(10, 1),IR(51802, 5),IR(1, 0)}, // FAbs in glsl_std_450
    {5,IR(10, 1),IR(51807, 5),IR(1, 0)}, // SAbs in glsl_std_450
    {6,IR(10, 1),IR(51812, 6),IR(1, 0)}, // FSign in glsl_std_450
    {7,IR(10, 1),IR(51818, 6),IR(1, 0)}, // SSign in glsl_std_450
    {8,IR(10, 1),IR(51824, 6),IR(1, 0)}, // Floor in glsl_std_450
    {9,IR(10, 1),IR(51830, 5),IR(1, 0)}, // Ceil in glsl_std_450
    {10,IR(10, 1),IR(51835, 6),IR(1, 0)}, // Fract in glsl_std_450
    {11,IR(10, 1),IR(51841, 8),IR(1, 0)}, // Radians in glsl_std_450
    {12,IR(10, 1),IR(51849, 8),IR(1, 0)}, // Degrees in glsl_std_450
    {13,IR(10, 1),IR(51857, 4),IR(1, 0)}, // Sin in glsl_std_450
    {14,IR(10, 1),IR(51861, 4),IR(1, 0)}, // Cos in glsl_std_450
    {15,IR(10, 1),IR(51865, 4),IR(1, 0)}, // Tan in glsl_std_450
    {16,IR(10, 1),IR(51869, 5),IR(1, 0)}, // Asin in glsl_std_450
    {17,IR(10, 1),IR(51874, 5),IR(1, 0)}, // Acos in glsl_std_450
    {18,IR(10, 1),IR(51879, 5),IR(1, 0)}, // Atan in glsl_std_450
    {19,IR(10, 1),IR(51884, 5),IR(1, 0)}, // Sinh in glsl_std_450
    {20,IR(10, 1),IR(51889, 5),IR(1, 0)}, // Cosh in glsl_std_450
    {21,IR(10, 1),IR(51894, 5),IR(1, 0)}, // Tanh in glsl_std_450
    {22,IR(10, 1),IR(51899, 6),IR(1, 0)}, // Asinh in glsl_std_450
    {23,IR(10, 1),IR(51905, 6),IR(1, 0)}, // Acosh in glsl_std_450
    {24,IR(10, 1),IR(51911, 6),IR(1, 0)}, // Atanh in glsl_std_450
    {25,IR(36, 2),IR(51917, 6),IR(1, 0)}, // Atan2 in glsl_std_450
    {26,IR(36, 2),IR(51923, 4),IR(1, 0)}, // Pow in glsl_std_450
    {27,IR(10, 1),IR(51927, 4),IR(1, 0)}, // Exp in glsl_std_450
    {28,IR(10, 1),IR(51931, 4),IR(1, 0)}, // Log in glsl_std_450
    {29,IR(10, 1),IR(51935, 5),IR(1, 0)}, // Exp2 in glsl_std_450
    {30,IR(10, 1),IR(51940, 5),IR(1, 0)}, // Log2 in glsl_std_450
    {31,IR(10, 1),IR(51945, 5),IR(1, 0)}, // Sqrt in glsl_std_450
    {32,IR(10, 1),IR(51950, 12),IR(1, 0)}, // InverseSqrt in glsl_std_450
    {33,IR(10, 1),IR(51962, 12),IR(1, 0)}, // Determinant in glsl_std_450
    {34,IR(10, 1),IR(51974, 14),IR(1, 0)}, // MatrixInverse in glsl_std_450
    {35,IR(36, 2),IR(51988, 5),IR(1, 0)}, // Modf in glsl_std_450
    {36,IR(10, 1),IR(51993, 11),IR(1, 0)}, // ModfStruct in glsl_std_450
    {37,IR(36, 2),IR(52004, 5),IR(1, 0)}, // FMin in glsl_std_450
    {38,IR(36, 2),IR(52009, 5),IR(1, 0)}, // UMin in glsl_std_450
    {39,IR(36, 2),IR(52014, 5),IR(1, 0)}, // SMin in glsl_std_450
    {40,IR(36, 2),IR(52019, 5),IR(1, 0)}, // FMax in glsl_std_450
    {41,IR(36, 2),IR(52024, 5),IR(1, 0)}, // UMax in glsl_std_450
    {42,IR(36, 2),IR(52029, 5),IR(1, 0)}, // SMax in glsl_std_450
    {43,IR(33, 3),IR(52034, 7),IR(1, 0)}, // FClamp in glsl_std_450
    {44,IR(33, 3),IR(52041, 7),IR(1, 0)}, // UClamp in glsl_std_450
    {45,IR(33, 3),IR(52048, 7),IR(1, 0)}, // SClamp in glsl_std_450
    {46,IR(33, 3),IR(52055, 5),IR(1, 0)}, // FMix in glsl_std_450
    {47,IR(33, 3),IR(52060, 5),IR(1, 0)}, // IMix in glsl_std_450
    {48,IR(36, 2),IR(52065, 5),IR(1, 0)}, // Step in glsl_std_450
    {49,IR(33, 3),IR(52070, 11),IR(1, 0)}, // SmoothStep in glsl_std_450
    {50,IR(33, 3),IR(52081, 4),IR(1, 0)}, // Fma in glsl_std_450
    {51,IR(36, 2),IR(52085, 6),IR(1, 0)}, // Frexp in glsl_std_450
    {52,IR(10, 1),IR(52091, 12),IR(1, 0)}, // FrexpStruct in glsl_std_450
    {53,IR(36, 2),IR(52103, 6),IR(1, 0)}, // Ldexp in glsl_std_450
    {54,IR(10, 1),IR(52109, 13),IR(1, 0)}, // PackSnorm4x8 in glsl_std_450
    {55,IR(10, 1),IR(52122, 13),IR(1, 0)}, // PackUnorm4x8 in glsl_std_450
    {56,IR(10, 1),IR(52135, 14),IR(1, 0)}, // PackSnorm2x16 in glsl_std_450
    {57,IR(10, 1),IR(52149, 14),IR(1, 0)}, // PackUnorm2x16 in glsl_std_450
    {58,IR(10, 1),IR(52163, 13),IR(1, 0)}, // PackHalf2x16 in glsl_std_450
    {59,IR(10, 1),IR(52176, 15),IR(328, 1)}, // PackDouble2x32 in glsl_std_450
    {60,IR(10, 1),IR(52191, 16),IR(1, 0)}, // UnpackSnorm2x16 in glsl_std_450
    {61,IR(10, 1),IR(52207, 16),IR(1, 0)}, // UnpackUnorm2x16 in glsl_std_450
    {62,IR(10, 1),IR(52223, 15),IR(1, 0)}, // UnpackHalf2x16 in glsl_std_450
    {63,IR(10, 1),IR(52238, 15),IR(1, 0)}, // UnpackSnorm4x8 in glsl_std_450
    {64,IR(10, 1),IR(52253, 15),IR(1, 0)}, // UnpackUnorm4x8 in glsl_std_450
    {65,IR(10, 1),IR(52268, 17),IR(328, 1)}, // UnpackDouble2x32 in glsl_std_450
    {66,IR(10, 1),IR(52285, 7),IR(1, 0)}, // Length in glsl_std_450
    {67,IR(36, 2),IR(52292, 9),IR(1, 0)}, // Distance in glsl_std_450
    {68,IR(36, 2),IR(52301, 6),IR(1, 0)}, // Cross in glsl_std_450
    {69,IR(10, 1),IR(52307, 10),IR(1, 0)}, // Normalize in glsl_std_450
    {70,IR(33, 3),IR(52317, 12),IR(1, 0)}, // FaceForward in glsl_std_450
    {71,IR(36, 2),IR(52329, 8),IR(1, 0)}, // Reflect in glsl_std_450
    {72,IR(33, 3),IR(52337, 8),IR(1, 0)}, // Refract in glsl_std_450
    {73,IR(10, 1),IR(52345, 9),IR(1, 0)}, // FindILsb in glsl_std_450
    {74,IR(10, 1),IR(52354, 9),IR(1, 0)}, // FindSMsb in glsl_std_450
    {75,IR(10, 1),IR(52363, 9),IR(1, 0)}, // FindUMsb in glsl_std_450
    {76,IR(10, 1),IR(52372, 22),IR(329, 1)}, // InterpolateAtCentroid in glsl_std_450
    {77,IR(36, 2),IR(52394, 20),IR(329, 1)}, // InterpolateAtSample in glsl_std_450
    {78,IR(36, 2),IR(52414, 20),IR(329, 1)}, // InterpolateAtOffset in glsl_std_450
    {79,IR(36, 2),IR(52434, 5),IR(1, 0)}, // NMin in glsl_std_450
    {80,IR(36, 2),IR(52439, 5),IR(1, 0)}, // NMax in glsl_std_450
    {81,IR(33, 3),IR(52444, 7),IR(1, 0)}, // NClamp in glsl_std_450
    {1,IR(399, 5),IR(5555, 7),IR(1, 0)}, // Kernel in nonsemantic_clspvreflection
    {2,IR(914, 5),IR(52451, 13),IR(1, 0)}, // ArgumentInfo in nonsemantic_clspvreflection
    {3,IR(919, 5),IR(52464, 22),IR(1, 0)}, // ArgumentStorageBuffer in nonsemantic_clspvreflection
    {4,IR(919, 5),IR(52486, 16),IR(1, 0)}, // ArgumentUniform in nonsemantic_clspvreflection
    {5,IR(557, 7),IR(52502, 25),IR(1, 0)}, // ArgumentPodStorageBuffer in nonsemantic_clspvreflection
    {6,IR(557, 7),IR(52527, 19),IR(1, 0)}, // ArgumentPodUniform in nonsemantic_clspvreflection
    {7,IR(919, 5),IR(52546, 24),IR(1, 0)}, // ArgumentPodPushConstant in nonsemantic_clspvreflection
    {8,IR(919, 5),IR(52570, 21),IR(1, 0)}, // ArgumentSampledImage in nonsemantic_clspvreflection
    {9,IR(919, 5),IR(52591, 21),IR(1, 0)}, // ArgumentStorageImage in nonsemantic_clspvreflection
    {10,IR(919, 5),IR(52612, 16),IR(1, 0)}, // ArgumentSampler in nonsemantic_clspvreflection
    {11,IR(919, 5),IR(52628, 18),IR(1, 0)}, // ArgumentWorkgroup in nonsemantic_clspvreflection
    {12,IR(33, 3),IR(52646, 26),IR(1, 0)}, // SpecConstantWorkgroupSize in nonsemantic_clspvreflection
    {13,IR(33, 3),IR(52672, 25),IR(1, 0)}, // SpecConstantGlobalOffset in nonsemantic_clspvreflection
    {14,IR(10, 1),IR(52697, 20),IR(1, 0)}, // SpecConstantWorkDim in nonsemantic_clspvreflection
    {15,IR(36, 2),IR(52717, 25),IR(1, 0)}, // PushConstantGlobalOffset in nonsemantic_clspvreflection
    {16,IR(36, 2),IR(52742, 30),IR(1, 0)}, // PushConstantEnqueuedLocalSize in nonsemantic_clspvreflection
    {17,IR(36, 2),IR(52772, 23),IR(1, 0)}, // PushConstantGlobalSize in nonsemantic_clspvreflection
    {18,IR(36, 2),IR(52795, 25),IR(1, 0)}, // PushConstantRegionOffset in nonsemantic_clspvreflection
    {19,IR(36, 2),IR(52820, 26),IR(1, 0)}, // PushConstantNumWorkgroups in nonsemantic_clspvreflection
    {20,IR(36, 2),IR(52846, 30),IR(1, 0)}, // PushConstantRegionGroupOffset in nonsemantic_clspvreflection
    {21,IR(33, 3),IR(52876, 26),IR(1, 0)}, // ConstantDataStorageBuffer in nonsemantic_clspvreflection
    {22,IR(33, 3),IR(52902, 20),IR(1, 0)}, // ConstantDataUniform in nonsemantic_clspvreflection
    {23,IR(33, 3),IR(9029, 15),IR(1, 0)}, // LiteralSampler in nonsemantic_clspvreflection
    {24,IR(296, 4),IR(52922, 30),IR(1, 0)}, // PropertyRequiredWorkgroupSize in nonsemantic_clspvreflection
    {25,IR(10, 1),IR(52952, 28),IR(1, 0)}, // SpecConstantSubgroupMaxSize in nonsemantic_clspvreflection
    {26,IR(919, 5),IR(52980, 28),IR(1, 0)}, // ArgumentPointerPushConstant in nonsemantic_clspvreflection
    {27,IR(557, 7),IR(53008, 23),IR(1, 0)}, // ArgumentPointerUniform in nonsemantic_clspvreflection
    {28,IR(33, 3),IR(53031, 35),IR(1, 0)}, // ProgramScopeVariablesStorageBuffer in nonsemantic_clspvreflection
    {29,IR(33, 3),IR(53066, 38),IR(1, 0)}, // ProgramScopeVariablePointerRelocation in nonsemantic_clspvreflection
    {30,IR(296, 4),IR(53104, 42),IR(1, 0)}, // ImageArgumentInfoChannelOrderPushConstant in nonsemantic_clspvreflection
    {31,IR(296, 4),IR(53146, 45),IR(1, 0)}, // ImageArgumentInfoChannelDataTypePushConstant in nonsemantic_clspvreflection
    {32,IR(528, 6),IR(53191, 37),IR(1, 0)}, // ImageArgumentInfoChannelOrderUniform in nonsemantic_clspvreflection
    {33,IR(528, 6),IR(53228, 40),IR(1, 0)}, // ImageArgumentInfoChannelDataTypeUniform in nonsemantic_clspvreflection
    {34,IR(919, 5),IR(53268, 27),IR(1, 0)}, // ArgumentStorageTexelBuffer in nonsemantic_clspvreflection
    {35,IR(919, 5),IR(53295, 27),IR(1, 0)}, // ArgumentUniformTexelBuffer in nonsemantic_clspvreflection
    {36,IR(33, 3),IR(53322, 32),IR(1, 0)}, // ConstantDataPointerPushConstant in nonsemantic_clspvreflection
    {37,IR(33, 3),IR(53354, 40),IR(1, 0)}, // ProgramScopeVariablePointerPushConstant in nonsemantic_clspvreflection
    {38,IR(375, 3),IR(53394, 11),IR(1, 0)}, // PrintfInfo in nonsemantic_clspvreflection
    {39,IR(33, 3),IR(53405, 26),IR(1, 0)}, // PrintfBufferStorageBuffer in nonsemantic_clspvreflection
    {40,IR(33, 3),IR(53431, 32),IR(1, 0)}, // PrintfBufferPointerPushConstant in nonsemantic_clspvreflection
    {41,IR(296, 4),IR(53463, 34),IR(1, 0)}, // NormalizedSamplerMaskPushConstant in nonsemantic_clspvreflection
    {42,IR(36, 2),IR(53497, 22),IR(1, 0)}, // WorkgroupVariableSize in nonsemantic_clspvreflection
    {0,IR(0, 0),IR(50921, 14),IR(1, 0)}, // DebugInfoNone in nonsemantic_shader_debuginfo_100
    {1,IR(296, 4),IR(50935, 21),IR(1, 0)}, // DebugCompilationUnit in nonsemantic_shader_debuginfo_100
    {2,IR(296, 4),IR(51008, 15),IR(1, 0)}, // DebugTypeBasic in nonsemantic_shader_debuginfo_100
    {3,IR(33, 3),IR(51057, 17),IR(1, 0)}, // DebugTypePointer in nonsemantic_shader_debuginfo_100
    {4,IR(36, 2),IR(51112, 19),IR(1, 0)}, // DebugTypeQualifier in nonsemantic_shader_debuginfo_100
    {5,IR(168, 2),IR(51131, 15),IR(1, 0)}, // DebugTypeArray in nonsemantic_shader_debuginfo_100
    {6,IR(36, 2),IR(51146, 16),IR(1, 0)}, // DebugTypeVector in nonsemantic_shader_debuginfo_100
    {7,IR(528, 6),IR(51162, 13),IR(1, 0)}, // DebugTypedef in nonsemantic_shader_debuginfo_100
    {8,IR(375, 3),IR(51175, 18),IR(1, 0)}, // DebugTypeFunction in nonsemantic_shader_debuginfo_100
    {9,IR(924, 9),IR(51193, 14),IR(1, 0)}, // DebugTypeEnum in nonsemantic_shader_debuginfo_100
    {10,IR(933, 10),IR(51245, 19),IR(1, 0)}, // DebugTypeComposite in nonsemantic_shader_debuginfo_100
    {11,IR(943, 9),IR(51264, 16),IR(1, 0)}, // DebugTypeMember in nonsemantic_shader_debuginfo_100
    {12,IR(296, 4),IR(51280, 21),IR(1, 0)}, // DebugTypeInheritance in nonsemantic_shader_debuginfo_100
    {13,IR(36, 2),IR(51301, 21),IR(1, 0)}, // DebugTypePtrToMember in nonsemantic_shader_debuginfo_100
    {14,IR(168, 2),IR(51322, 18),IR(1, 0)}, // DebugTypeTemplate in nonsemantic_shader_debuginfo_100
    {15,IR(528, 6),IR(51340, 27),IR(1, 0)}, // DebugTypeTemplateParameter in nonsemantic_shader_debuginfo_100
    {16,IR(670, 5),IR(51367, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in nonsemantic_shader_debuginfo_100
    {17,IR(952, 5),IR(51402, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in nonsemantic_shader_debuginfo_100
    {18,IR(957, 10),IR(51433, 20),IR(1, 0)}, // DebugGlobalVariable in nonsemantic_shader_debuginfo_100
    {19,IR(471, 8),IR(51453, 25),IR(1, 0)}, // DebugFunctionDeclaration in nonsemantic_shader_debuginfo_100
    {20,IR(957, 10),IR(51478, 14),IR(1, 0)}, // DebugFunction in nonsemantic_shader_debuginfo_100
    {21,IR(919, 5),IR(51492, 18),IR(1, 0)}, // DebugLexicalBlock in nonsemantic_shader_debuginfo_100
    {22,IR(33, 3),IR(51510, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in nonsemantic_shader_debuginfo_100
    {23,IR(896, 2),IR(51541, 11),IR(1, 0)}, // DebugScope in nonsemantic_shader_debuginfo_100
    {24,IR(0, 0),IR(51552, 13),IR(1, 0)}, // DebugNoScope in nonsemantic_shader_debuginfo_100
    {25,IR(967, 3),IR(51565, 15),IR(1, 0)}, // DebugInlinedAt in nonsemantic_shader_debuginfo_100
    {26,IR(970, 8),IR(51622, 19),IR(1, 0)}, // DebugLocalVariable in nonsemantic_shader_debuginfo_100
    {27,IR(36, 2),IR(51641, 21),IR(1, 0)}, // DebugInlinedVariable in nonsemantic_shader_debuginfo_100
    {28,IR(978, 4),IR(51662, 13),IR(1, 0)}, // DebugDeclare in nonsemantic_shader_debuginfo_100
    {29,IR(978, 4),IR(51675, 11),IR(1, 0)}, // DebugValue in nonsemantic_shader_debuginfo_100
    {30,IR(168, 2),IR(51719, 15),IR(1, 0)}, // DebugOperation in nonsemantic_shader_debuginfo_100
    {31,IR(742, 1),IR(51734, 16),IR(1, 0)}, // DebugExpression in nonsemantic_shader_debuginfo_100
    {32,IR(580, 4),IR(51750, 14),IR(1, 0)}, // DebugMacroDef in nonsemantic_shader_debuginfo_100
    {33,IR(33, 3),IR(51764, 16),IR(1, 0)}, // DebugMacroUndef in nonsemantic_shader_debuginfo_100
    {34,IR(509, 7),IR(53519, 20),IR(1, 0)}, // DebugImportedEntity in nonsemantic_shader_debuginfo_100
    {35,IR(896, 2),IR(53539, 12),IR(1, 0)}, // DebugSource in nonsemantic_shader_debuginfo_100
    {101,IR(36, 2),IR(53551, 24),IR(1, 0)}, // DebugFunctionDefinition in nonsemantic_shader_debuginfo_100
    {102,IR(10, 1),IR(53575, 21),IR(1, 0)}, // DebugSourceContinued in nonsemantic_shader_debuginfo_100
    {103,IR(670, 5),IR(53596, 10),IR(1, 0)}, // DebugLine in nonsemantic_shader_debuginfo_100
    {104,IR(0, 0),IR(53606, 12),IR(1, 0)}, // DebugNoLine in nonsemantic_shader_debuginfo_100
    {105,IR(36, 2),IR(53618, 21),IR(1, 0)}, // DebugBuildIdentifier in nonsemantic_shader_debuginfo_100
    {106,IR(10, 1),IR(53639, 17),IR(1, 0)}, // DebugStoragePath in nonsemantic_shader_debuginfo_100
    {107,IR(296, 4),IR(53656, 16),IR(1, 0)}, // DebugEntryPoint in nonsemantic_shader_debuginfo_100
    {108,IR(33, 3),IR(53672, 16),IR(1, 0)}, // DebugTypeMatrix in nonsemantic_shader_debuginfo_100
    {1,IR(760, 9),IR(53688, 14),IR(1, 0)}, // Configuration in nonsemantic_vkspreflection
    {2,IR(10, 1),IR(53702, 13),IR(1, 0)}, // StartCounter in nonsemantic_vkspreflection
    {3,IR(10, 1),IR(53715, 12),IR(1, 0)}, // StopCounter in nonsemantic_vkspreflection
    {4,IR(296, 4),IR(53727, 14),IR(1, 0)}, // PushConstants in nonsemantic_vkspreflection
    {5,IR(33, 3),IR(53741, 23),IR(1, 0)}, // SpecializationMapEntry in nonsemantic_vkspreflection
    {6,IR(982, 15),IR(53764, 20),IR(1, 0)}, // DescriptorSetBuffer in nonsemantic_vkspreflection
    {7,IR(997, 33),IR(53784, 19),IR(1, 0)}, // DescriptorSetImage in nonsemantic_vkspreflection
    {8,IR(1030, 19),IR(53803, 21),IR(1, 0)}, // DescriptorSetSampler in nonsemantic_vkspreflection
    {0,IR(0, 0),IR(50921, 14),IR(1, 0)}, // DebugInfoNone in opencl_debuginfo_100
    {1,IR(1049, 4),IR(50935, 21),IR(1, 0)}, // DebugCompilationUnit in opencl_debuginfo_100
    {2,IR(1053, 3),IR(51008, 15),IR(1, 0)}, // DebugTypeBasic in opencl_debuginfo_100
    {3,IR(1056, 3),IR(51057, 17),IR(1, 0)}, // DebugTypePointer in opencl_debuginfo_100
    {4,IR(1059, 2),IR(51112, 19),IR(1, 0)}, // DebugTypeQualifier in opencl_debuginfo_100
    {5,IR(168, 2),IR(51131, 15),IR(1, 0)}, // DebugTypeArray in opencl_debuginfo_100
    {6,IR(261, 2),IR(51146, 16),IR(1, 0)}, // DebugTypeVector in opencl_debuginfo_100
    {7,IR(814, 6),IR(51162, 13),IR(1, 0)}, // DebugTypedef in opencl_debuginfo_100
    {8,IR(1061, 3),IR(51175, 18),IR(1, 0)}, // DebugTypeFunction in opencl_debuginfo_100
    {9,IR(1064, 9),IR(51193, 14),IR(1, 0)}, // DebugTypeEnum in opencl_debuginfo_100
    {10,IR(1073, 10),IR(51245, 19),IR(1, 0)}, // DebugTypeComposite in opencl_debuginfo_100
    {11,IR(1083, 10),IR(51264, 16),IR(1, 0)}, // DebugTypeMember in opencl_debuginfo_100
    {12,IR(1093, 5),IR(51280, 21),IR(1, 0)}, // DebugTypeInheritance in opencl_debuginfo_100
    {13,IR(36, 2),IR(51301, 21),IR(1, 0)}, // DebugTypePtrToMember in opencl_debuginfo_100
    {14,IR(168, 2),IR(51322, 18),IR(1, 0)}, // DebugTypeTemplate in opencl_debuginfo_100
    {15,IR(853, 6),IR(51340, 27),IR(1, 0)}, // DebugTypeTemplateParameter in opencl_debuginfo_100
    {16,IR(859, 5),IR(51367, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in opencl_debuginfo_100
    {17,IR(864, 5),IR(51402, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in opencl_debuginfo_100
    {18,IR(1083, 10),IR(51433, 20),IR(1, 0)}, // DebugGlobalVariable in opencl_debuginfo_100
    {19,IR(1098, 8),IR(51453, 25),IR(1, 0)}, // DebugFunctionDeclaration in opencl_debuginfo_100
    {20,IR(1106, 11),IR(51478, 14),IR(1, 0)}, // DebugFunction in opencl_debuginfo_100
    {21,IR(888, 5),IR(51492, 18),IR(1, 0)}, // DebugLexicalBlock in opencl_debuginfo_100
    {22,IR(893, 3),IR(51510, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in opencl_debuginfo_100
    {23,IR(896, 2),IR(51541, 11),IR(1, 0)}, // DebugScope in opencl_debuginfo_100
    {24,IR(0, 0),IR(51552, 13),IR(1, 0)}, // DebugNoScope in opencl_debuginfo_100
    {25,IR(898, 3),IR(51565, 15),IR(1, 0)}, // DebugInlinedAt in opencl_debuginfo_100
    {26,IR(1117, 8),IR(51622, 19),IR(1, 0)}, // DebugLocalVariable in opencl_debuginfo_100
    {27,IR(36, 2),IR(51641, 21),IR(1, 0)}, // DebugInlinedVariable in opencl_debuginfo_100
    {28,IR(33, 3),IR(51662, 13),IR(1, 0)}, // DebugDeclare in opencl_debuginfo_100
    {29,IR(978, 4),IR(51675, 11),IR(1, 0)}, // DebugValue in opencl_debuginfo_100
    {30,IR(1125, 2),IR(51719, 15),IR(1, 0)}, // DebugOperation in opencl_debuginfo_100
    {31,IR(742, 1),IR(51734, 16),IR(1, 0)}, // DebugExpression in opencl_debuginfo_100
    {32,IR(910, 4),IR(51750, 14),IR(1, 0)}, // DebugMacroDef in opencl_debuginfo_100
    {33,IR(893, 3),IR(51764, 16),IR(1, 0)}, // DebugMacroUndef in opencl_debuginfo_100
    {34,IR(1127, 7),IR(53519, 20),IR(1, 0)}, // DebugImportedEntity in opencl_debuginfo_100
    {35,IR(896, 2),IR(53539, 12),IR(1, 0)}, // DebugSource in opencl_debuginfo_100
    {36,IR(1134, 8),IR(54124, 17),IR(1, 0)}, // DebugModuleINTEL in opencl_debuginfo_100
    {0,IR(10, 1),IR(54141, 5),IR(1, 0)}, // acos in opencl_std_100
    {1,IR(10, 1),IR(54146, 6),IR(1, 0)}, // acosh in opencl_std_100
    {2,IR(10, 1),IR(54152, 7),IR(1, 0)}, // acospi in opencl_std_100
    {3,IR(10, 1),IR(54159, 5),IR(1, 0)}, // asin in opencl_std_100
    {4,IR(10, 1),IR(54164, 6),IR(1, 0)}, // asinh in opencl_std_100
    {5,IR(10, 1),IR(54170, 7),IR(1, 0)}, // asinpi in opencl_std_100
    {6,IR(10, 1),IR(54177, 5),IR(1, 0)}, // atan in opencl_std_100
    {7,IR(36, 2),IR(54182, 6),IR(1, 0)}, // atan2 in opencl_std_100
    {8,IR(10, 1),IR(54188, 6),IR(1, 0)}, // atanh in opencl_std_100
    {9,IR(10, 1),IR(54194, 7),IR(1, 0)}, // atanpi in opencl_std_100
    {10,IR(36, 2),IR(54201, 8),IR(1, 0)}, // atan2pi in opencl_std_100
    {11,IR(10, 1),IR(54209, 5),IR(1, 0)}, // cbrt in opencl_std_100
    {12,IR(10, 1),IR(54214, 5),IR(1, 0)}, // ceil in opencl_std_100
    {13,IR(36, 2),IR(54219, 9),IR(1, 0)}, // copysign in opencl_std_100
    {14,IR(10, 1),IR(54228, 4),IR(1, 0)}, // cos in opencl_std_100
    {15,IR(10, 1),IR(54232, 5),IR(1, 0)}, // cosh in opencl_std_100
    {16,IR(10, 1),IR(54237, 6),IR(1, 0)}, // cospi in opencl_std_100
    {17,IR(10, 1),IR(54243, 5),IR(1, 0)}, // erfc in opencl_std_100
    {18,IR(10, 1),IR(54248, 4),IR(1, 0)}, // erf in opencl_std_100
    {19,IR(10, 1),IR(54252, 4),IR(1, 0)}, // exp in opencl_std_100
    {20,IR(10, 1),IR(54256, 5),IR(1, 0)}, // exp2 in opencl_std_100
    {21,IR(10, 1),IR(54261, 6),IR(1, 0)}, // exp10 in opencl_std_100
    {22,IR(10, 1),IR(54267, 6),IR(1, 0)}, // expm1 in opencl_std_100
    {23,IR(10, 1),IR(54273, 5),IR(1, 0)}, // fabs in opencl_std_100
    {24,IR(36, 2),IR(54278, 5),IR(1, 0)}, // fdim in opencl_std_100
    {25,IR(10, 1),IR(54283, 6),IR(1, 0)}, // floor in opencl_std_100
    {26,IR(33, 3),IR(54289, 4),IR(1, 0)}, // fma in opencl_std_100
    {27,IR(36, 2),IR(54293, 5),IR(1, 0)}, // fmax in opencl_std_100
    {28,IR(36, 2),IR(54298, 5),IR(1, 0)}, // fmin in opencl_std_100
    {29,IR(36, 2),IR(54303, 5),IR(1, 0)}, // fmod in opencl_std_100
    {30,IR(36, 2),IR(54308, 6),IR(1, 0)}, // fract in opencl_std_100
    {31,IR(36, 2),IR(54314, 6),IR(1, 0)}, // frexp in opencl_std_100
    {32,IR(36, 2),IR(54320, 6),IR(1, 0)}, // hypot in opencl_std_100
    {33,IR(10, 1),IR(54326, 6),IR(1, 0)}, // ilogb in opencl_std_100
    {34,IR(36, 2),IR(54332, 6),IR(1, 0)}, // ldexp in opencl_std_100
    {35,IR(10, 1),IR(54338, 7),IR(1, 0)}, // lgamma in opencl_std_100
    {36,IR(36, 2),IR(54345, 9),IR(1, 0)}, // lgamma_r in opencl_std_100
    {37,IR(10, 1),IR(54354, 4),IR(1, 0)}, // log in opencl_std_100
    {38,IR(10, 1),IR(54358, 5),IR(1, 0)}, // log2 in opencl_std_100
    {39,IR(10, 1),IR(54363, 6),IR(1, 0)}, // log10 in opencl_std_100
    {40,IR(10, 1),IR(54369, 6),IR(1, 0)}, // log1p in opencl_std_100
    {41,IR(10, 1),IR(54375, 5),IR(1, 0)}, // logb in opencl_std_100
    {42,IR(33, 3),IR(54380, 4),IR(1, 0)}, // mad in opencl_std_100
    {43,IR(36, 2),IR(54384, 7),IR(1, 0)}, // maxmag in opencl_std_100
    {44,IR(36, 2),IR(54391, 7),IR(1, 0)}, // minmag in opencl_std_100
    {45,IR(36, 2),IR(54398, 5),IR(1, 0)}, // modf in opencl_std_100
    {46,IR(10, 1),IR(54403, 4),IR(1, 0)}, // nan in opencl_std_100
    {47,IR(36, 2),IR(54407, 10),IR(1, 0)}, // nextafter in opencl_std_100
    {48,IR(36, 2),IR(54417, 4),IR(1, 0)}, // pow in opencl_std_100
    {49,IR(36, 2),IR(54421, 5),IR(1, 0)}, // pown in opencl_std_100
    {50,IR(36, 2),IR(54426, 5),IR(1, 0)}, // powr in opencl_std_100
    {51,IR(36, 2),IR(54431, 10),IR(1, 0)}, // remainder in opencl_std_100
    {52,IR(33, 3),IR(54441, 7),IR(1, 0)}, // remquo in opencl_std_100
    {53,IR(10, 1),IR(54448, 5),IR(1, 0)}, // rint in opencl_std_100
    {54,IR(36, 2),IR(54453, 6),IR(1, 0)}, // rootn in opencl_std_100
    {55,IR(10, 1),IR(54459, 6),IR(1, 0)}, // round in opencl_std_100
    {56,IR(10, 1),IR(54465, 6),IR(1, 0)}, // rsqrt in opencl_std_100
    {57,IR(10, 1),IR(54471, 4),IR(1, 0)}, // sin in opencl_std_100
    {58,IR(36, 2),IR(54475, 7),IR(1, 0)}, // sincos in opencl_std_100
    {59,IR(10, 1),IR(54482, 5),IR(1, 0)}, // sinh in opencl_std_100
    {60,IR(10, 1),IR(54487, 6),IR(1, 0)}, // sinpi in opencl_std_100
    {61,IR(10, 1),IR(54493, 5),IR(1, 0)}, // sqrt in opencl_std_100
    {62,IR(10, 1),IR(54498, 4),IR(1, 0)}, // tan in opencl_std_100
    {63,IR(10, 1),IR(54502, 5),IR(1, 0)}, // tanh in opencl_std_100
    {64,IR(10, 1),IR(54507, 6),IR(1, 0)}, // tanpi in opencl_std_100
    {65,IR(10, 1),IR(54513, 7),IR(1, 0)}, // tgamma in opencl_std_100
    {66,IR(10, 1),IR(54520, 6),IR(1, 0)}, // trunc in opencl_std_100
    {67,IR(10, 1),IR(54526, 9),IR(1, 0)}, // half_cos in opencl_std_100
    {68,IR(36, 2),IR(54535, 12),IR(1, 0)}, // half_divide in opencl_std_100
    {69,IR(10, 1),IR(54547, 9),IR(1, 0)}, // half_exp in opencl_std_100
    {70,IR(10, 1),IR(54556, 10),IR(1, 0)}, // half_exp2 in opencl_std_100
    {71,IR(10, 1),IR(54566, 11),IR(1, 0)}, // half_exp10 in opencl_std_100
    {72,IR(10, 1),IR(54577, 9),IR(1, 0)}, // half_log in opencl_std_100
    {73,IR(10, 1),IR(54586, 10),IR(1, 0)}, // half_log2 in opencl_std_100
    {74,IR(10, 1),IR(54596, 11),IR(1, 0)}, // half_log10 in opencl_std_100
    {75,IR(36, 2),IR(54607, 10),IR(1, 0)}, // half_powr in opencl_std_100
    {76,IR(10, 1),IR(54617, 11),IR(1, 0)}, // half_recip in opencl_std_100
    {77,IR(10, 1),IR(54628, 11),IR(1, 0)}, // half_rsqrt in opencl_std_100
    {78,IR(10, 1),IR(54639, 9),IR(1, 0)}, // half_sin in opencl_std_100
    {79,IR(10, 1),IR(54648, 10),IR(1, 0)}, // half_sqrt in opencl_std_100
    {80,IR(10, 1),IR(54658, 9),IR(1, 0)}, // half_tan in opencl_std_100
    {81,IR(10, 1),IR(54667, 11),IR(1, 0)}, // native_cos in opencl_std_100
    {82,IR(36, 2),IR(54678, 14),IR(1, 0)}, // native_divide in opencl_std_100
    {83,IR(10, 1),IR(54692, 11),IR(1, 0)}, // native_exp in opencl_std_100
    {84,IR(10, 1),IR(54703, 12),IR(1, 0)}, // native_exp2 in opencl_std_100
    {85,IR(10, 1),IR(54715, 13),IR(1, 0)}, // native_exp10 in opencl_std_100
    {86,IR(10, 1),IR(54728, 11),IR(1, 0)}, // native_log in opencl_std_100
    {87,IR(10, 1),IR(54739, 12),IR(1, 0)}, // native_log2 in opencl_std_100
    {88,IR(10, 1),IR(54751, 13),IR(1, 0)}, // native_log10 in opencl_std_100
    {89,IR(36, 2),IR(54764, 12),IR(1, 0)}, // native_powr in opencl_std_100
    {90,IR(10, 1),IR(54776, 13),IR(1, 0)}, // native_recip in opencl_std_100
    {91,IR(10, 1),IR(54789, 13),IR(1, 0)}, // native_rsqrt in opencl_std_100
    {92,IR(10, 1),IR(54802, 11),IR(1, 0)}, // native_sin in opencl_std_100
    {93,IR(10, 1),IR(54813, 12),IR(1, 0)}, // native_sqrt in opencl_std_100
    {94,IR(10, 1),IR(54825, 11),IR(1, 0)}, // native_tan in opencl_std_100
    {95,IR(33, 3),IR(54836, 7),IR(1, 0)}, // fclamp in opencl_std_100
    {96,IR(10, 1),IR(54843, 8),IR(1, 0)}, // degrees in opencl_std_100
    {97,IR(36, 2),IR(54851, 12),IR(1, 0)}, // fmax_common in opencl_std_100
    {98,IR(36, 2),IR(54863, 12),IR(1, 0)}, // fmin_common in opencl_std_100
    {99,IR(33, 3),IR(54875, 4),IR(1, 0)}, // mix in opencl_std_100
    {100,IR(10, 1),IR(54879, 8),IR(1, 0)}, // radians in opencl_std_100
    {101,IR(36, 2),IR(54887, 5),IR(1, 0)}, // step in opencl_std_100
    {102,IR(33, 3),IR(54892, 11),IR(1, 0)}, // smoothstep in opencl_std_100
    {103,IR(10, 1),IR(54903, 5),IR(1, 0)}, // sign in opencl_std_100
    {104,IR(36, 2),IR(54908, 6),IR(1, 0)}, // cross in opencl_std_100
    {105,IR(36, 2),IR(54914, 9),IR(1, 0)}, // distance in opencl_std_100
    {106,IR(10, 1),IR(54923, 7),IR(1, 0)}, // length in opencl_std_100
    {107,IR(10, 1),IR(54930, 10),IR(1, 0)}, // normalize in opencl_std_100
    {108,IR(36, 2),IR(54940, 14),IR(1, 0)}, // fast_distance in opencl_std_100
    {109,IR(10, 1),IR(54954, 12),IR(1, 0)}, // fast_length in opencl_std_100
    {110,IR(10, 1),IR(54966, 15),IR(1, 0)}, // fast_normalize in opencl_std_100
    {141,IR(10, 1),IR(54981, 6),IR(1, 0)}, // s_abs in opencl_std_100
    {142,IR(36, 2),IR(54987, 11),IR(1, 0)}, // s_abs_diff in opencl_std_100
    {143,IR(36, 2),IR(54998, 10),IR(1, 0)}, // s_add_sat in opencl_std_100
    {144,IR(36, 2),IR(55008, 10),IR(1, 0)}, // u_add_sat in opencl_std_100
    {145,IR(36, 2),IR(55018, 7),IR(1, 0)}, // s_hadd in opencl_std_100
    {146,IR(36, 2),IR(55025, 7),IR(1, 0)}, // u_hadd in opencl_std_100
    {147,IR(36, 2),IR(55032, 8),IR(1, 0)}, // s_rhadd in opencl_std_100
    {148,IR(36, 2),IR(55040, 8),IR(1, 0)}, // u_rhadd in opencl_std_100
    {149,IR(33, 3),IR(55048, 8),IR(1, 0)}, // s_clamp in opencl_std_100
    {150,IR(33, 3),IR(55056, 8),IR(1, 0)}, // u_clamp in opencl_std_100
    {151,IR(10, 1),IR(55064, 4),IR(1, 0)}, // clz in opencl_std_100
    {152,IR(10, 1),IR(55068, 4),IR(1, 0)}, // ctz in opencl_std_100
    {153,IR(33, 3),IR(55072, 9),IR(1, 0)}, // s_mad_hi in opencl_std_100
    {154,IR(33, 3),IR(55081, 10),IR(1, 0)}, // u_mad_sat in opencl_std_100
    {155,IR(33, 3),IR(55091, 10),IR(1, 0)}, // s_mad_sat in opencl_std_100
    {156,IR(36, 2),IR(55101, 6),IR(1, 0)}, // s_max in opencl_std_100
    {157,IR(36, 2),IR(55107, 6),IR(1, 0)}, // u_max in opencl_std_100
    {158,IR(36, 2),IR(55113, 6),IR(1, 0)}, // s_min in opencl_std_100
    {159,IR(36, 2),IR(55119, 6),IR(1, 0)}, // u_min in opencl_std_100
    {160,IR(36, 2),IR(55125, 9),IR(1, 0)}, // s_mul_hi in opencl_std_100
    {161,IR(36, 2),IR(55134, 7),IR(1, 0)}, // rotate in opencl_std_100
    {162,IR(36, 2),IR(55141, 10),IR(1, 0)}, // s_sub_sat in opencl_std_100
    {163,IR(36, 2),IR(55151, 10),IR(1, 0)}, // u_sub_sat in opencl_std_100
    {164,IR(36, 2),IR(55161, 11),IR(1, 0)}, // u_upsample in opencl_std_100
    {165,IR(36, 2),IR(55172, 11),IR(1, 0)}, // s_upsample in opencl_std_100
    {166,IR(10, 1),IR(55183, 9),IR(1, 0)}, // popcount in opencl_std_100
    {167,IR(33, 3),IR(55192, 8),IR(1, 0)}, // s_mad24 in opencl_std_100
    {168,IR(33, 3),IR(55200, 8),IR(1, 0)}, // u_mad24 in opencl_std_100
    {169,IR(36, 2),IR(55208, 8),IR(1, 0)}, // s_mul24 in opencl_std_100
    {170,IR(36, 2),IR(55216, 8),IR(1, 0)}, // u_mul24 in opencl_std_100
    {171,IR(1142, 3),IR(55224, 7),IR(1, 0)}, // vloadn in opencl_std_100
    {172,IR(33, 3),IR(55231, 8),IR(1, 0)}, // vstoren in opencl_std_100
    {173,IR(36, 2),IR(55239, 11),IR(1, 0)}, // vload_half in opencl_std_100
    {174,IR(1142, 3),IR(55250, 12),IR(1, 0)}, // vload_halfn in opencl_std_100
    {175,IR(33, 3),IR(55262, 12),IR(1, 0)}, // vstore_half in opencl_std_100
    {176,IR(1145, 4),IR(55274, 14),IR(1, 0)}, // vstore_half_r in opencl_std_100
    {177,IR(33, 3),IR(55288, 13),IR(1, 0)}, // vstore_halfn in opencl_std_100
    {178,IR(1145, 4),IR(55301, 15),IR(1, 0)}, // vstore_halfn_r in opencl_std_100
    {179,IR(1142, 3),IR(55316, 13),IR(1, 0)}, // vloada_halfn in opencl_std_100
    {180,IR(33, 3),IR(55329, 14),IR(1, 0)}, // vstorea_halfn in opencl_std_100
    {181,IR(1145, 4),IR(55343, 16),IR(1, 0)}, // vstorea_halfn_r in opencl_std_100
    {182,IR(36, 2),IR(55359, 8),IR(1, 0)}, // shuffle in opencl_std_100
    {183,IR(33, 3),IR(55367, 9),IR(1, 0)}, // shuffle2 in opencl_std_100
    {184,IR(168, 2),IR(55376, 7),IR(1, 0)}, // printf in opencl_std_100
    {185,IR(36, 2),IR(55383, 9),IR(1, 0)}, // prefetch in opencl_std_100
    {186,IR(33, 3),IR(55392, 10),IR(1, 0)}, // bitselect in opencl_std_100
    {187,IR(33, 3),IR(55402, 7),IR(1, 0)}, // select in opencl_std_100
    {201,IR(10, 1),IR(55409, 6),IR(1, 0)}, // u_abs in opencl_std_100
    {202,IR(36, 2),IR(55415, 11),IR(1, 0)}, // u_abs_diff in opencl_std_100
    {203,IR(36, 2),IR(55426, 9),IR(1, 0)}, // u_mul_hi in opencl_std_100
    {204,IR(33, 3),IR(55435, 9),IR(1, 0)}, // u_mad_hi in opencl_std_100
    {1,IR(10, 1),IR(55444, 17),IR(1, 0)}, // CubeFaceIndexAMD in spv_amd_gcn_shader
    {2,IR(10, 1),IR(55461, 17),IR(1, 0)}, // CubeFaceCoordAMD in spv_amd_gcn_shader
    {3,IR(0, 0),IR(55478, 8),IR(1, 0)}, // TimeAMD in spv_amd_gcn_shader
    {1,IR(36, 2),IR(55486, 22),IR(1, 0)}, // SwizzleInvocationsAMD in spv_amd_shader_ballot
    {2,IR(36, 2),IR(55508, 28),IR(1, 0)}, // SwizzleInvocationsMaskedAMD in spv_amd_shader_ballot
    {3,IR(33, 3),IR(55536, 19),IR(1, 0)}, // WriteInvocationAMD in spv_amd_shader_ballot
    {4,IR(10, 1),IR(55555, 9),IR(1, 0)}, // MbcntAMD in spv_amd_shader_ballot
    {1,IR(36, 2),IR(55564, 23),IR(1, 0)}, // InterpolateAtVertexAMD in spv_amd_shader_explicit_vertex_parameter
    {1,IR(33, 3),IR(55587, 9),IR(1, 0)}, // FMin3AMD in spv_amd_shader_trinary_minmax
    {2,IR(33, 3),IR(55596, 9),IR(1, 0)}, // UMin3AMD in spv_amd_shader_trinary_minmax
    {3,IR(33, 3),IR(55605, 9),IR(1, 0)}, // SMin3AMD in spv_amd_shader_trinary_minmax
    {4,IR(33, 3),IR(55614, 9),IR(1, 0)}, // FMax3AMD in spv_amd_shader_trinary_minmax
    {5,IR(33, 3),IR(55623, 9),IR(1, 0)}, // UMax3AMD in spv_amd_shader_trinary_minmax
    {6,IR(33, 3),IR(55632, 9),IR(1, 0)}, // SMax3AMD in spv_amd_shader_trinary_minmax
    {7,IR(33, 3),IR(55641, 9),IR(1, 0)}, // FMid3AMD in spv_amd_shader_trinary_minmax
    {8,IR(33, 3),IR(55650, 9),IR(1, 0)}, // UMid3AMD in spv_amd_shader_trinary_minmax
    {9,IR(33, 3),IR(55659, 9),IR(1, 0)}, // SMid3AMD in spv_amd_shader_trinary_minmax
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
    {IR(50935, 21), 1}, // DebugCompilationUnit in debuginfo
    {IR(51662, 13), 28}, // DebugDeclare in debuginfo
    {IR(51734, 16), 31}, // DebugExpression in debuginfo
    {IR(51478, 14), 20}, // DebugFunction in debuginfo
    {IR(51453, 25), 19}, // DebugFunctionDeclaration in debuginfo
    {IR(51433, 20), 18}, // DebugGlobalVariable in debuginfo
    {IR(50921, 14), 0}, // DebugInfoNone in debuginfo
    {IR(51565, 15), 25}, // DebugInlinedAt in debuginfo
    {IR(51641, 21), 27}, // DebugInlinedVariable in debuginfo
    {IR(51492, 18), 21}, // DebugLexicalBlock in debuginfo
    {IR(51510, 31), 22}, // DebugLexicalBlockDiscriminator in debuginfo
    {IR(51622, 19), 26}, // DebugLocalVariable in debuginfo
    {IR(51750, 14), 32}, // DebugMacroDef in debuginfo
    {IR(51764, 16), 33}, // DebugMacroUndef in debuginfo
    {IR(51552, 13), 24}, // DebugNoScope in debuginfo
    {IR(51719, 15), 30}, // DebugOperation in debuginfo
    {IR(51541, 11), 23}, // DebugScope in debuginfo
    {IR(51131, 15), 5}, // DebugTypeArray in debuginfo
    {IR(51008, 15), 2}, // DebugTypeBasic in debuginfo
    {IR(51245, 19), 10}, // DebugTypeComposite in debuginfo
    {IR(51193, 14), 9}, // DebugTypeEnum in debuginfo
    {IR(51175, 18), 8}, // DebugTypeFunction in debuginfo
    {IR(51280, 21), 12}, // DebugTypeInheritance in debuginfo
    {IR(51264, 16), 11}, // DebugTypeMember in debuginfo
    {IR(51057, 17), 3}, // DebugTypePointer in debuginfo
    {IR(51301, 21), 13}, // DebugTypePtrToMember in debuginfo
    {IR(51112, 19), 4}, // DebugTypeQualifier in debuginfo
    {IR(51322, 18), 14}, // DebugTypeTemplate in debuginfo
    {IR(51340, 27), 15}, // DebugTypeTemplateParameter in debuginfo
    {IR(51402, 31), 17}, // DebugTypeTemplateParameterPack in debuginfo
    {IR(51367, 35), 16}, // DebugTypeTemplateTemplateParameter in debuginfo
    {IR(51146, 16), 6}, // DebugTypeVector in debuginfo
    {IR(51162, 13), 7}, // DebugTypedef in debuginfo
    {IR(51675, 11), 29}, // DebugValue in debuginfo
    {IR(51874, 5), 50}, // Acos in glsl_std_450
    {IR(51905, 6), 56}, // Acosh in glsl_std_450
    {IR(51869, 5), 49}, // Asin in glsl_std_450
    {IR(51899, 6), 55}, // Asinh in glsl_std_450
    {IR(51879, 5), 51}, // Atan in glsl_std_450
    {IR(51917, 6), 58}, // Atan2 in glsl_std_450
    {IR(51911, 6), 57}, // Atanh in glsl_std_450
    {IR(51830, 5), 42}, // Ceil in glsl_std_450
    {IR(51861, 4), 47}, // Cos in glsl_std_450
    {IR(51889, 5), 53}, // Cosh in glsl_std_450
    {IR(52301, 6), 101}, // Cross in glsl_std_450
    {IR(51849, 8), 45}, // Degrees in glsl_std_450
    {IR(51962, 12), 66}, // Determinant in glsl_std_450
    {IR(52292, 9), 100}, // Distance in glsl_std_450
    {IR(51927, 4), 60}, // Exp in glsl_std_450
    {IR(51935, 5), 62}, // Exp2 in glsl_std_450
    {IR(51802, 5), 37}, // FAbs in glsl_std_450
    {IR(52034, 7), 76}, // FClamp in glsl_std_450
    {IR(52019, 5), 73}, // FMax in glsl_std_450
    {IR(52004, 5), 70}, // FMin in glsl_std_450
    {IR(52055, 5), 79}, // FMix in glsl_std_450
    {IR(51812, 6), 39}, // FSign in glsl_std_450
    {IR(52317, 12), 103}, // FaceForward in glsl_std_450
    {IR(52345, 9), 106}, // FindILsb in glsl_std_450
    {IR(52354, 9), 107}, // FindSMsb in glsl_std_450
    {IR(52363, 9), 108}, // FindUMsb in glsl_std_450
    {IR(51824, 6), 41}, // Floor in glsl_std_450
    {IR(52081, 4), 83}, // Fma in glsl_std_450
    {IR(51835, 6), 43}, // Fract in glsl_std_450
    {IR(52085, 6), 84}, // Frexp in glsl_std_450
    {IR(52091, 12), 85}, // FrexpStruct in glsl_std_450
    {IR(52060, 5), 80}, // IMix in glsl_std_450
    {IR(52372, 22), 109}, // InterpolateAtCentroid in glsl_std_450
    {IR(52414, 20), 111}, // InterpolateAtOffset in glsl_std_450
    {IR(52394, 20), 110}, // InterpolateAtSample in glsl_std_450
    {IR(51950, 12), 65}, // InverseSqrt in glsl_std_450
    {IR(52103, 6), 86}, // Ldexp in glsl_std_450
    {IR(52285, 7), 99}, // Length in glsl_std_450
    {IR(51931, 4), 61}, // Log in glsl_std_450
    {IR(51940, 5), 63}, // Log2 in glsl_std_450
    {IR(51974, 14), 67}, // MatrixInverse in glsl_std_450
    {IR(51988, 5), 68}, // Modf in glsl_std_450
    {IR(51993, 11), 69}, // ModfStruct in glsl_std_450
    {IR(52444, 7), 114}, // NClamp in glsl_std_450
    {IR(52439, 5), 113}, // NMax in glsl_std_450
    {IR(52434, 5), 112}, // NMin in glsl_std_450
    {IR(52307, 10), 102}, // Normalize in glsl_std_450
    {IR(52176, 15), 92}, // PackDouble2x32 in glsl_std_450
    {IR(52163, 13), 91}, // PackHalf2x16 in glsl_std_450
    {IR(52135, 14), 89}, // PackSnorm2x16 in glsl_std_450
    {IR(52109, 13), 87}, // PackSnorm4x8 in glsl_std_450
    {IR(52149, 14), 90}, // PackUnorm2x16 in glsl_std_450
    {IR(52122, 13), 88}, // PackUnorm4x8 in glsl_std_450
    {IR(51923, 4), 59}, // Pow in glsl_std_450
    {IR(51841, 8), 44}, // Radians in glsl_std_450
    {IR(52329, 8), 104}, // Reflect in glsl_std_450
    {IR(52337, 8), 105}, // Refract in glsl_std_450
    {IR(51780, 6), 34}, // Round in glsl_std_450
    {IR(51786, 10), 35}, // RoundEven in glsl_std_450
    {IR(51807, 5), 38}, // SAbs in glsl_std_450
    {IR(52048, 7), 78}, // SClamp in glsl_std_450
    {IR(52029, 5), 75}, // SMax in glsl_std_450
    {IR(52014, 5), 72}, // SMin in glsl_std_450
    {IR(51818, 6), 40}, // SSign in glsl_std_450
    {IR(51857, 4), 46}, // Sin in glsl_std_450
    {IR(51884, 5), 52}, // Sinh in glsl_std_450
    {IR(52070, 11), 82}, // SmoothStep in glsl_std_450
    {IR(51945, 5), 64}, // Sqrt in glsl_std_450
    {IR(52065, 5), 81}, // Step in glsl_std_450
    {IR(51865, 4), 48}, // Tan in glsl_std_450
    {IR(51894, 5), 54}, // Tanh in glsl_std_450
    {IR(51796, 6), 36}, // Trunc in glsl_std_450
    {IR(52041, 7), 77}, // UClamp in glsl_std_450
    {IR(52024, 5), 74}, // UMax in glsl_std_450
    {IR(52009, 5), 71}, // UMin in glsl_std_450
    {IR(52268, 17), 98}, // UnpackDouble2x32 in glsl_std_450
    {IR(52223, 15), 95}, // UnpackHalf2x16 in glsl_std_450
    {IR(52191, 16), 93}, // UnpackSnorm2x16 in glsl_std_450
    {IR(52238, 15), 96}, // UnpackSnorm4x8 in glsl_std_450
    {IR(52207, 16), 94}, // UnpackUnorm2x16 in glsl_std_450
    {IR(52253, 15), 97}, // UnpackUnorm4x8 in glsl_std_450
    {IR(52451, 13), 116}, // ArgumentInfo in nonsemantic_clspvreflection
    {IR(52546, 24), 121}, // ArgumentPodPushConstant in nonsemantic_clspvreflection
    {IR(52502, 25), 119}, // ArgumentPodStorageBuffer in nonsemantic_clspvreflection
    {IR(52527, 19), 120}, // ArgumentPodUniform in nonsemantic_clspvreflection
    {IR(52980, 28), 140}, // ArgumentPointerPushConstant in nonsemantic_clspvreflection
    {IR(53008, 23), 141}, // ArgumentPointerUniform in nonsemantic_clspvreflection
    {IR(52570, 21), 122}, // ArgumentSampledImage in nonsemantic_clspvreflection
    {IR(52612, 16), 124}, // ArgumentSampler in nonsemantic_clspvreflection
    {IR(52464, 22), 117}, // ArgumentStorageBuffer in nonsemantic_clspvreflection
    {IR(52591, 21), 123}, // ArgumentStorageImage in nonsemantic_clspvreflection
    {IR(53268, 27), 148}, // ArgumentStorageTexelBuffer in nonsemantic_clspvreflection
    {IR(52486, 16), 118}, // ArgumentUniform in nonsemantic_clspvreflection
    {IR(53295, 27), 149}, // ArgumentUniformTexelBuffer in nonsemantic_clspvreflection
    {IR(52628, 18), 125}, // ArgumentWorkgroup in nonsemantic_clspvreflection
    {IR(53322, 32), 150}, // ConstantDataPointerPushConstant in nonsemantic_clspvreflection
    {IR(52876, 26), 135}, // ConstantDataStorageBuffer in nonsemantic_clspvreflection
    {IR(52902, 20), 136}, // ConstantDataUniform in nonsemantic_clspvreflection
    {IR(53146, 45), 145}, // ImageArgumentInfoChannelDataTypePushConstant in nonsemantic_clspvreflection
    {IR(53228, 40), 147}, // ImageArgumentInfoChannelDataTypeUniform in nonsemantic_clspvreflection
    {IR(53104, 42), 144}, // ImageArgumentInfoChannelOrderPushConstant in nonsemantic_clspvreflection
    {IR(53191, 37), 146}, // ImageArgumentInfoChannelOrderUniform in nonsemantic_clspvreflection
    {IR(5555, 7), 115}, // Kernel in nonsemantic_clspvreflection
    {IR(9029, 15), 137}, // LiteralSampler in nonsemantic_clspvreflection
    {IR(53463, 34), 155}, // NormalizedSamplerMaskPushConstant in nonsemantic_clspvreflection
    {IR(53431, 32), 154}, // PrintfBufferPointerPushConstant in nonsemantic_clspvreflection
    {IR(53405, 26), 153}, // PrintfBufferStorageBuffer in nonsemantic_clspvreflection
    {IR(53394, 11), 152}, // PrintfInfo in nonsemantic_clspvreflection
    {IR(53354, 40), 151}, // ProgramScopeVariablePointerPushConstant in nonsemantic_clspvreflection
    {IR(53066, 38), 143}, // ProgramScopeVariablePointerRelocation in nonsemantic_clspvreflection
    {IR(53031, 35), 142}, // ProgramScopeVariablesStorageBuffer in nonsemantic_clspvreflection
    {IR(52922, 30), 138}, // PropertyRequiredWorkgroupSize in nonsemantic_clspvreflection
    {IR(52742, 30), 130}, // PushConstantEnqueuedLocalSize in nonsemantic_clspvreflection
    {IR(52717, 25), 129}, // PushConstantGlobalOffset in nonsemantic_clspvreflection
    {IR(52772, 23), 131}, // PushConstantGlobalSize in nonsemantic_clspvreflection
    {IR(52820, 26), 133}, // PushConstantNumWorkgroups in nonsemantic_clspvreflection
    {IR(52846, 30), 134}, // PushConstantRegionGroupOffset in nonsemantic_clspvreflection
    {IR(52795, 25), 132}, // PushConstantRegionOffset in nonsemantic_clspvreflection
    {IR(52672, 25), 127}, // SpecConstantGlobalOffset in nonsemantic_clspvreflection
    {IR(52952, 28), 139}, // SpecConstantSubgroupMaxSize in nonsemantic_clspvreflection
    {IR(52697, 20), 128}, // SpecConstantWorkDim in nonsemantic_clspvreflection
    {IR(52646, 26), 126}, // SpecConstantWorkgroupSize in nonsemantic_clspvreflection
    {IR(53497, 22), 156}, // WorkgroupVariableSize in nonsemantic_clspvreflection
    {IR(53618, 21), 197}, // DebugBuildIdentifier in nonsemantic_shader_debuginfo_100
    {IR(50935, 21), 158}, // DebugCompilationUnit in nonsemantic_shader_debuginfo_100
    {IR(51662, 13), 185}, // DebugDeclare in nonsemantic_shader_debuginfo_100
    {IR(53656, 16), 199}, // DebugEntryPoint in nonsemantic_shader_debuginfo_100
    {IR(51734, 16), 188}, // DebugExpression in nonsemantic_shader_debuginfo_100
    {IR(51478, 14), 177}, // DebugFunction in nonsemantic_shader_debuginfo_100
    {IR(51453, 25), 176}, // DebugFunctionDeclaration in nonsemantic_shader_debuginfo_100
    {IR(53551, 24), 193}, // DebugFunctionDefinition in nonsemantic_shader_debuginfo_100
    {IR(51433, 20), 175}, // DebugGlobalVariable in nonsemantic_shader_debuginfo_100
    {IR(53519, 20), 191}, // DebugImportedEntity in nonsemantic_shader_debuginfo_100
    {IR(50921, 14), 157}, // DebugInfoNone in nonsemantic_shader_debuginfo_100
    {IR(51565, 15), 182}, // DebugInlinedAt in nonsemantic_shader_debuginfo_100
    {IR(51641, 21), 184}, // DebugInlinedVariable in nonsemantic_shader_debuginfo_100
    {IR(51492, 18), 178}, // DebugLexicalBlock in nonsemantic_shader_debuginfo_100
    {IR(51510, 31), 179}, // DebugLexicalBlockDiscriminator in nonsemantic_shader_debuginfo_100
    {IR(53596, 10), 195}, // DebugLine in nonsemantic_shader_debuginfo_100
    {IR(51622, 19), 183}, // DebugLocalVariable in nonsemantic_shader_debuginfo_100
    {IR(51750, 14), 189}, // DebugMacroDef in nonsemantic_shader_debuginfo_100
    {IR(51764, 16), 190}, // DebugMacroUndef in nonsemantic_shader_debuginfo_100
    {IR(53606, 12), 196}, // DebugNoLine in nonsemantic_shader_debuginfo_100
    {IR(51552, 13), 181}, // DebugNoScope in nonsemantic_shader_debuginfo_100
    {IR(51719, 15), 187}, // DebugOperation in nonsemantic_shader_debuginfo_100
    {IR(51541, 11), 180}, // DebugScope in nonsemantic_shader_debuginfo_100
    {IR(53539, 12), 192}, // DebugSource in nonsemantic_shader_debuginfo_100
    {IR(53575, 21), 194}, // DebugSourceContinued in nonsemantic_shader_debuginfo_100
    {IR(53639, 17), 198}, // DebugStoragePath in nonsemantic_shader_debuginfo_100
    {IR(51131, 15), 162}, // DebugTypeArray in nonsemantic_shader_debuginfo_100
    {IR(51008, 15), 159}, // DebugTypeBasic in nonsemantic_shader_debuginfo_100
    {IR(51245, 19), 167}, // DebugTypeComposite in nonsemantic_shader_debuginfo_100
    {IR(51193, 14), 166}, // DebugTypeEnum in nonsemantic_shader_debuginfo_100
    {IR(51175, 18), 165}, // DebugTypeFunction in nonsemantic_shader_debuginfo_100
    {IR(51280, 21), 169}, // DebugTypeInheritance in nonsemantic_shader_debuginfo_100
    {IR(53672, 16), 200}, // DebugTypeMatrix in nonsemantic_shader_debuginfo_100
    {IR(51264, 16), 168}, // DebugTypeMember in nonsemantic_shader_debuginfo_100
    {IR(51057, 17), 160}, // DebugTypePointer in nonsemantic_shader_debuginfo_100
    {IR(51301, 21), 170}, // DebugTypePtrToMember in nonsemantic_shader_debuginfo_100
    {IR(51112, 19), 161}, // DebugTypeQualifier in nonsemantic_shader_debuginfo_100
    {IR(51322, 18), 171}, // DebugTypeTemplate in nonsemantic_shader_debuginfo_100
    {IR(51340, 27), 172}, // DebugTypeTemplateParameter in nonsemantic_shader_debuginfo_100
    {IR(51402, 31), 174}, // DebugTypeTemplateParameterPack in nonsemantic_shader_debuginfo_100
    {IR(51367, 35), 173}, // DebugTypeTemplateTemplateParameter in nonsemantic_shader_debuginfo_100
    {IR(51146, 16), 163}, // DebugTypeVector in nonsemantic_shader_debuginfo_100
    {IR(51162, 13), 164}, // DebugTypedef in nonsemantic_shader_debuginfo_100
    {IR(51675, 11), 186}, // DebugValue in nonsemantic_shader_debuginfo_100
    {IR(53688, 14), 201}, // Configuration in nonsemantic_vkspreflection
    {IR(53764, 20), 206}, // DescriptorSetBuffer in nonsemantic_vkspreflection
    {IR(53784, 19), 207}, // DescriptorSetImage in nonsemantic_vkspreflection
    {IR(53803, 21), 208}, // DescriptorSetSampler in nonsemantic_vkspreflection
    {IR(53727, 14), 204}, // PushConstants in nonsemantic_vkspreflection
    {IR(53741, 23), 205}, // SpecializationMapEntry in nonsemantic_vkspreflection
    {IR(53702, 13), 202}, // StartCounter in nonsemantic_vkspreflection
    {IR(53715, 12), 203}, // StopCounter in nonsemantic_vkspreflection
    {IR(50935, 21), 210}, // DebugCompilationUnit in opencl_debuginfo_100
    {IR(51662, 13), 237}, // DebugDeclare in opencl_debuginfo_100
    {IR(51734, 16), 240}, // DebugExpression in opencl_debuginfo_100
    {IR(51478, 14), 229}, // DebugFunction in opencl_debuginfo_100
    {IR(51453, 25), 228}, // DebugFunctionDeclaration in opencl_debuginfo_100
    {IR(51433, 20), 227}, // DebugGlobalVariable in opencl_debuginfo_100
    {IR(53519, 20), 243}, // DebugImportedEntity in opencl_debuginfo_100
    {IR(50921, 14), 209}, // DebugInfoNone in opencl_debuginfo_100
    {IR(51565, 15), 234}, // DebugInlinedAt in opencl_debuginfo_100
    {IR(51641, 21), 236}, // DebugInlinedVariable in opencl_debuginfo_100
    {IR(51492, 18), 230}, // DebugLexicalBlock in opencl_debuginfo_100
    {IR(51510, 31), 231}, // DebugLexicalBlockDiscriminator in opencl_debuginfo_100
    {IR(51622, 19), 235}, // DebugLocalVariable in opencl_debuginfo_100
    {IR(51750, 14), 241}, // DebugMacroDef in opencl_debuginfo_100
    {IR(51764, 16), 242}, // DebugMacroUndef in opencl_debuginfo_100
    {IR(54124, 17), 245}, // DebugModuleINTEL in opencl_debuginfo_100
    {IR(51552, 13), 233}, // DebugNoScope in opencl_debuginfo_100
    {IR(51719, 15), 239}, // DebugOperation in opencl_debuginfo_100
    {IR(51541, 11), 232}, // DebugScope in opencl_debuginfo_100
    {IR(53539, 12), 244}, // DebugSource in opencl_debuginfo_100
    {IR(51131, 15), 214}, // DebugTypeArray in opencl_debuginfo_100
    {IR(51008, 15), 211}, // DebugTypeBasic in opencl_debuginfo_100
    {IR(51245, 19), 219}, // DebugTypeComposite in opencl_debuginfo_100
    {IR(51193, 14), 218}, // DebugTypeEnum in opencl_debuginfo_100
    {IR(51175, 18), 217}, // DebugTypeFunction in opencl_debuginfo_100
    {IR(51280, 21), 221}, // DebugTypeInheritance in opencl_debuginfo_100
    {IR(51264, 16), 220}, // DebugTypeMember in opencl_debuginfo_100
    {IR(51057, 17), 212}, // DebugTypePointer in opencl_debuginfo_100
    {IR(51301, 21), 222}, // DebugTypePtrToMember in opencl_debuginfo_100
    {IR(51112, 19), 213}, // DebugTypeQualifier in opencl_debuginfo_100
    {IR(51322, 18), 223}, // DebugTypeTemplate in opencl_debuginfo_100
    {IR(51340, 27), 224}, // DebugTypeTemplateParameter in opencl_debuginfo_100
    {IR(51402, 31), 226}, // DebugTypeTemplateParameterPack in opencl_debuginfo_100
    {IR(51367, 35), 225}, // DebugTypeTemplateTemplateParameter in opencl_debuginfo_100
    {IR(51146, 16), 215}, // DebugTypeVector in opencl_debuginfo_100
    {IR(51162, 13), 216}, // DebugTypedef in opencl_debuginfo_100
    {IR(51675, 11), 238}, // DebugValue in opencl_debuginfo_100
    {IR(54141, 5), 246}, // acos in opencl_std_100
    {IR(54146, 6), 247}, // acosh in opencl_std_100
    {IR(54152, 7), 248}, // acospi in opencl_std_100
    {IR(54159, 5), 249}, // asin in opencl_std_100
    {IR(54164, 6), 250}, // asinh in opencl_std_100
    {IR(54170, 7), 251}, // asinpi in opencl_std_100
    {IR(54177, 5), 252}, // atan in opencl_std_100
    {IR(54182, 6), 253}, // atan2 in opencl_std_100
    {IR(54201, 8), 256}, // atan2pi in opencl_std_100
    {IR(54188, 6), 254}, // atanh in opencl_std_100
    {IR(54194, 7), 255}, // atanpi in opencl_std_100
    {IR(55392, 10), 402}, // bitselect in opencl_std_100
    {IR(54209, 5), 257}, // cbrt in opencl_std_100
    {IR(54214, 5), 258}, // ceil in opencl_std_100
    {IR(55064, 4), 367}, // clz in opencl_std_100
    {IR(54219, 9), 259}, // copysign in opencl_std_100
    {IR(54228, 4), 260}, // cos in opencl_std_100
    {IR(54232, 5), 261}, // cosh in opencl_std_100
    {IR(54237, 6), 262}, // cospi in opencl_std_100
    {IR(54908, 6), 350}, // cross in opencl_std_100
    {IR(55068, 4), 368}, // ctz in opencl_std_100
    {IR(54843, 8), 342}, // degrees in opencl_std_100
    {IR(54914, 9), 351}, // distance in opencl_std_100
    {IR(54248, 4), 264}, // erf in opencl_std_100
    {IR(54243, 5), 263}, // erfc in opencl_std_100
    {IR(54252, 4), 265}, // exp in opencl_std_100
    {IR(54261, 6), 267}, // exp10 in opencl_std_100
    {IR(54256, 5), 266}, // exp2 in opencl_std_100
    {IR(54267, 6), 268}, // expm1 in opencl_std_100
    {IR(54273, 5), 269}, // fabs in opencl_std_100
    {IR(54940, 14), 354}, // fast_distance in opencl_std_100
    {IR(54954, 12), 355}, // fast_length in opencl_std_100
    {IR(54966, 15), 356}, // fast_normalize in opencl_std_100
    {IR(54836, 7), 341}, // fclamp in opencl_std_100
    {IR(54278, 5), 270}, // fdim in opencl_std_100
    {IR(54283, 6), 271}, // floor in opencl_std_100
    {IR(54289, 4), 272}, // fma in opencl_std_100
    {IR(54293, 5), 273}, // fmax in opencl_std_100
    {IR(54851, 12), 343}, // fmax_common in opencl_std_100
    {IR(54298, 5), 274}, // fmin in opencl_std_100
    {IR(54863, 12), 344}, // fmin_common in opencl_std_100
    {IR(54303, 5), 275}, // fmod in opencl_std_100
    {IR(54308, 6), 276}, // fract in opencl_std_100
    {IR(54314, 6), 277}, // frexp in opencl_std_100
    {IR(54526, 9), 313}, // half_cos in opencl_std_100
    {IR(54535, 12), 314}, // half_divide in opencl_std_100
    {IR(54547, 9), 315}, // half_exp in opencl_std_100
    {IR(54566, 11), 317}, // half_exp10 in opencl_std_100
    {IR(54556, 10), 316}, // half_exp2 in opencl_std_100
    {IR(54577, 9), 318}, // half_log in opencl_std_100
    {IR(54596, 11), 320}, // half_log10 in opencl_std_100
    {IR(54586, 10), 319}, // half_log2 in opencl_std_100
    {IR(54607, 10), 321}, // half_powr in opencl_std_100
    {IR(54617, 11), 322}, // half_recip in opencl_std_100
    {IR(54628, 11), 323}, // half_rsqrt in opencl_std_100
    {IR(54639, 9), 324}, // half_sin in opencl_std_100
    {IR(54648, 10), 325}, // half_sqrt in opencl_std_100
    {IR(54658, 9), 326}, // half_tan in opencl_std_100
    {IR(54320, 6), 278}, // hypot in opencl_std_100
    {IR(54326, 6), 279}, // ilogb in opencl_std_100
    {IR(54332, 6), 280}, // ldexp in opencl_std_100
    {IR(54923, 7), 352}, // length in opencl_std_100
    {IR(54338, 7), 281}, // lgamma in opencl_std_100
    {IR(54345, 9), 282}, // lgamma_r in opencl_std_100
    {IR(54354, 4), 283}, // log in opencl_std_100
    {IR(54363, 6), 285}, // log10 in opencl_std_100
    {IR(54369, 6), 286}, // log1p in opencl_std_100
    {IR(54358, 5), 284}, // log2 in opencl_std_100
    {IR(54375, 5), 287}, // logb in opencl_std_100
    {IR(54380, 4), 288}, // mad in opencl_std_100
    {IR(54384, 7), 289}, // maxmag in opencl_std_100
    {IR(54391, 7), 290}, // minmag in opencl_std_100
    {IR(54875, 4), 345}, // mix in opencl_std_100
    {IR(54398, 5), 291}, // modf in opencl_std_100
    {IR(54403, 4), 292}, // nan in opencl_std_100
    {IR(54667, 11), 327}, // native_cos in opencl_std_100
    {IR(54678, 14), 328}, // native_divide in opencl_std_100
    {IR(54692, 11), 329}, // native_exp in opencl_std_100
    {IR(54715, 13), 331}, // native_exp10 in opencl_std_100
    {IR(54703, 12), 330}, // native_exp2 in opencl_std_100
    {IR(54728, 11), 332}, // native_log in opencl_std_100
    {IR(54751, 13), 334}, // native_log10 in opencl_std_100
    {IR(54739, 12), 333}, // native_log2 in opencl_std_100
    {IR(54764, 12), 335}, // native_powr in opencl_std_100
    {IR(54776, 13), 336}, // native_recip in opencl_std_100
    {IR(54789, 13), 337}, // native_rsqrt in opencl_std_100
    {IR(54802, 11), 338}, // native_sin in opencl_std_100
    {IR(54813, 12), 339}, // native_sqrt in opencl_std_100
    {IR(54825, 11), 340}, // native_tan in opencl_std_100
    {IR(54407, 10), 293}, // nextafter in opencl_std_100
    {IR(54930, 10), 353}, // normalize in opencl_std_100
    {IR(55183, 9), 382}, // popcount in opencl_std_100
    {IR(54417, 4), 294}, // pow in opencl_std_100
    {IR(54421, 5), 295}, // pown in opencl_std_100
    {IR(54426, 5), 296}, // powr in opencl_std_100
    {IR(55383, 9), 401}, // prefetch in opencl_std_100
    {IR(55376, 7), 400}, // printf in opencl_std_100
    {IR(54879, 8), 346}, // radians in opencl_std_100
    {IR(54431, 10), 297}, // remainder in opencl_std_100
    {IR(54441, 7), 298}, // remquo in opencl_std_100
    {IR(54448, 5), 299}, // rint in opencl_std_100
    {IR(54453, 6), 300}, // rootn in opencl_std_100
    {IR(55134, 7), 377}, // rotate in opencl_std_100
    {IR(54459, 6), 301}, // round in opencl_std_100
    {IR(54465, 6), 302}, // rsqrt in opencl_std_100
    {IR(54981, 6), 357}, // s_abs in opencl_std_100
    {IR(54987, 11), 358}, // s_abs_diff in opencl_std_100
    {IR(54998, 10), 359}, // s_add_sat in opencl_std_100
    {IR(55048, 8), 365}, // s_clamp in opencl_std_100
    {IR(55018, 7), 361}, // s_hadd in opencl_std_100
    {IR(55192, 8), 383}, // s_mad24 in opencl_std_100
    {IR(55072, 9), 369}, // s_mad_hi in opencl_std_100
    {IR(55091, 10), 371}, // s_mad_sat in opencl_std_100
    {IR(55101, 6), 372}, // s_max in opencl_std_100
    {IR(55113, 6), 374}, // s_min in opencl_std_100
    {IR(55208, 8), 385}, // s_mul24 in opencl_std_100
    {IR(55125, 9), 376}, // s_mul_hi in opencl_std_100
    {IR(55032, 8), 363}, // s_rhadd in opencl_std_100
    {IR(55141, 10), 378}, // s_sub_sat in opencl_std_100
    {IR(55172, 11), 381}, // s_upsample in opencl_std_100
    {IR(55402, 7), 403}, // select in opencl_std_100
    {IR(55359, 8), 398}, // shuffle in opencl_std_100
    {IR(55367, 9), 399}, // shuffle2 in opencl_std_100
    {IR(54903, 5), 349}, // sign in opencl_std_100
    {IR(54471, 4), 303}, // sin in opencl_std_100
    {IR(54475, 7), 304}, // sincos in opencl_std_100
    {IR(54482, 5), 305}, // sinh in opencl_std_100
    {IR(54487, 6), 306}, // sinpi in opencl_std_100
    {IR(54892, 11), 348}, // smoothstep in opencl_std_100
    {IR(54493, 5), 307}, // sqrt in opencl_std_100
    {IR(54887, 5), 347}, // step in opencl_std_100
    {IR(54498, 4), 308}, // tan in opencl_std_100
    {IR(54502, 5), 309}, // tanh in opencl_std_100
    {IR(54507, 6), 310}, // tanpi in opencl_std_100
    {IR(54513, 7), 311}, // tgamma in opencl_std_100
    {IR(54520, 6), 312}, // trunc in opencl_std_100
    {IR(55409, 6), 404}, // u_abs in opencl_std_100
    {IR(55415, 11), 405}, // u_abs_diff in opencl_std_100
    {IR(55008, 10), 360}, // u_add_sat in opencl_std_100
    {IR(55056, 8), 366}, // u_clamp in opencl_std_100
    {IR(55025, 7), 362}, // u_hadd in opencl_std_100
    {IR(55200, 8), 384}, // u_mad24 in opencl_std_100
    {IR(55435, 9), 407}, // u_mad_hi in opencl_std_100
    {IR(55081, 10), 370}, // u_mad_sat in opencl_std_100
    {IR(55107, 6), 373}, // u_max in opencl_std_100
    {IR(55119, 6), 375}, // u_min in opencl_std_100
    {IR(55216, 8), 386}, // u_mul24 in opencl_std_100
    {IR(55426, 9), 406}, // u_mul_hi in opencl_std_100
    {IR(55040, 8), 364}, // u_rhadd in opencl_std_100
    {IR(55151, 10), 379}, // u_sub_sat in opencl_std_100
    {IR(55161, 11), 380}, // u_upsample in opencl_std_100
    {IR(55239, 11), 389}, // vload_half in opencl_std_100
    {IR(55250, 12), 390}, // vload_halfn in opencl_std_100
    {IR(55316, 13), 395}, // vloada_halfn in opencl_std_100
    {IR(55224, 7), 387}, // vloadn in opencl_std_100
    {IR(55262, 12), 391}, // vstore_half in opencl_std_100
    {IR(55274, 14), 392}, // vstore_half_r in opencl_std_100
    {IR(55288, 13), 393}, // vstore_halfn in opencl_std_100
    {IR(55301, 15), 394}, // vstore_halfn_r in opencl_std_100
    {IR(55329, 14), 396}, // vstorea_halfn in opencl_std_100
    {IR(55343, 16), 397}, // vstorea_halfn_r in opencl_std_100
    {IR(55231, 8), 388}, // vstoren in opencl_std_100
    {IR(55461, 17), 409}, // CubeFaceCoordAMD in spv_amd_gcn_shader
    {IR(55444, 17), 408}, // CubeFaceIndexAMD in spv_amd_gcn_shader
    {IR(55478, 8), 410}, // TimeAMD in spv_amd_gcn_shader
    {IR(55555, 9), 414}, // MbcntAMD in spv_amd_shader_ballot
    {IR(55486, 22), 411}, // SwizzleInvocationsAMD in spv_amd_shader_ballot
    {IR(55508, 28), 412}, // SwizzleInvocationsMaskedAMD in spv_amd_shader_ballot
    {IR(55536, 19), 413}, // WriteInvocationAMD in spv_amd_shader_ballot
    {IR(55564, 23), 415}, // InterpolateAtVertexAMD in spv_amd_shader_explicit_vertex_parameter
    {IR(55614, 9), 419}, // FMax3AMD in spv_amd_shader_trinary_minmax
    {IR(55641, 9), 422}, // FMid3AMD in spv_amd_shader_trinary_minmax
    {IR(55587, 9), 416}, // FMin3AMD in spv_amd_shader_trinary_minmax
    {IR(55632, 9), 421}, // SMax3AMD in spv_amd_shader_trinary_minmax
    {IR(55659, 9), 424}, // SMid3AMD in spv_amd_shader_trinary_minmax
    {IR(55605, 9), 418}, // SMin3AMD in spv_amd_shader_trinary_minmax
    {IR(55623, 9), 420}, // UMax3AMD in spv_amd_shader_trinary_minmax
    {IR(55650, 9), 423}, // UMid3AMD in spv_amd_shader_trinary_minmax
    {IR(55596, 9), 417}, // UMin3AMD in spv_amd_shader_trinary_minmax
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
  "SPV_KHR_abort\0" // IR(3495, 14)
  "SPV_KHR_bfloat16\0" // IR(3509, 17)
  "SPV_KHR_bit_instructions\0" // IR(3526, 25)
  "SPV_KHR_compute_shader_derivatives\0" // IR(3551, 35)
  "SPV_KHR_constant_data\0" // IR(3586, 22)
  "SPV_KHR_cooperative_matrix\0" // IR(3608, 27)
  "SPV_KHR_device_group\0" // IR(3635, 21)
  "SPV_KHR_expect_assume\0" // IR(3656, 22)
  "SPV_KHR_float_controls\0" // IR(3678, 23)
  "SPV_KHR_float_controls2\0" // IR(3701, 24)
  "SPV_KHR_fma\0" // IR(3725, 12)
  "SPV_KHR_fragment_shader_barycentric\0" // IR(3737, 36)
  "SPV_KHR_fragment_shading_rate\0" // IR(3773, 30)
  "SPV_KHR_integer_dot_product\0" // IR(3803, 28)
  "SPV_KHR_linkonce_odr\0" // IR(3831, 21)
  "SPV_KHR_maximal_reconvergence\0" // IR(3852, 30)
  "SPV_KHR_multiview\0" // IR(3882, 18)
  "SPV_KHR_no_integer_wrap_decoration\0" // IR(3900, 35)
  "SPV_KHR_non_semantic_info\0" // IR(3935, 26)
  "SPV_KHR_physical_storage_buffer\0" // IR(3961, 32)
  "SPV_KHR_poison_freeze\0" // IR(3993, 22)
  "SPV_KHR_post_depth_coverage\0" // IR(4015, 28)
  "SPV_KHR_quad_control\0" // IR(4043, 21)
  "SPV_KHR_ray_cull_mask\0" // IR(4064, 22)
  "SPV_KHR_ray_query\0" // IR(4086, 18)
  "SPV_KHR_ray_tracing\0" // IR(4104, 20)
  "SPV_KHR_ray_tracing_position_fetch\0" // IR(4124, 35)
  "SPV_KHR_relaxed_extended_instruction\0" // IR(4159, 37)
  "SPV_KHR_shader_atomic_counter_ops\0" // IR(4196, 34)
  "SPV_KHR_shader_ballot\0" // IR(4230, 22)
  "SPV_KHR_shader_clock\0" // IR(4252, 21)
  "SPV_KHR_shader_draw_parameters\0" // IR(4273, 31)
  "SPV_KHR_storage_buffer_storage_class\0" // IR(4304, 37)
  "SPV_KHR_subgroup_rotate\0" // IR(4341, 24)
  "SPV_KHR_subgroup_uniform_control_flow\0" // IR(4365, 38)
  "SPV_KHR_subgroup_vote\0" // IR(4403, 22)
  "SPV_KHR_terminate_invocation\0" // IR(4425, 29)
  "SPV_KHR_uniform_group_instructions\0" // IR(4454, 35)
  "SPV_KHR_untyped_pointers\0" // IR(4489, 25)
  "SPV_KHR_variable_pointers\0" // IR(4514, 26)
  "SPV_KHR_vulkan_memory_model\0" // IR(4540, 28)
  "SPV_KHR_workgroup_memory_explicit_layout\0" // IR(4568, 41)
  "SPV_NVX_multiview_per_view_attributes\0" // IR(4609, 38)
  "SPV_NV_bindless_texture\0" // IR(4647, 24)
  "SPV_NV_cluster_acceleration_structure\0" // IR(4671, 38)
  "SPV_NV_compute_shader_derivatives\0" // IR(4709, 34)
  "SPV_NV_cooperative_matrix\0" // IR(4743, 26)
  "SPV_NV_cooperative_matrix2\0" // IR(4769, 27)
  "SPV_NV_cooperative_vector\0" // IR(4796, 26)
  "SPV_NV_displacement_micromap\0" // IR(4822, 29)
  "SPV_NV_fragment_shader_barycentric\0" // IR(4851, 35)
  "SPV_NV_geometry_shader_passthrough\0" // IR(4886, 35)
  "SPV_NV_linear_swept_spheres\0" // IR(4921, 28)
  "SPV_NV_mesh_shader\0" // IR(4949, 19)
  "SPV_NV_push_constant_bank\0" // IR(4968, 26)
  "SPV_NV_raw_access_chains\0" // IR(4994, 25)
  "SPV_NV_ray_tracing\0" // IR(5019, 19)
  "SPV_NV_ray_tracing_motion_blur\0" // IR(5038, 31)
  "SPV_NV_sample_mask_override_coverage\0" // IR(5069, 37)
  "SPV_NV_shader_atomic_fp16_vector\0" // IR(5106, 33)
  "SPV_NV_shader_image_footprint\0" // IR(5139, 30)
  "SPV_NV_shader_invocation_reorder\0" // IR(5169, 33)
  "SPV_NV_shader_sm_builtins\0" // IR(5202, 26)
  "SPV_NV_shader_subgroup_partitioned\0" // IR(5228, 35)
  "SPV_NV_shading_rate\0" // IR(5263, 20)
  "SPV_NV_stereo_view_rendering\0" // IR(5283, 29)
  "SPV_NV_tensor_addressing\0" // IR(5312, 25)
  "SPV_NV_viewport_array2\0" // IR(5337, 23)
  "SPV_QCOM_cooperative_matrix_conversion\0" // IR(5360, 39)
  "SPV_QCOM_image_processing\0" // IR(5399, 26)
  "SPV_QCOM_image_processing2\0" // IR(5425, 27)
  "SPV_QCOM_tile_shading\0" // IR(5452, 22)
  "SPV_VALIDATOR_ignore_type_decl_unique\0" // IR(5474, 38)
  "SPV_VALVE_mixed_float_dot_product\0" // IR(5512, 34)
  "ReadOnly\0" // IR(5546, 9)
  "Kernel\0" // IR(5555, 7)
  "WriteOnly\0" // IR(5562, 10)
  "ReadWrite\0" // IR(5572, 10)
  "Logical\0" // IR(5582, 8)
  "Physical32\0" // IR(5590, 11)
  "Addresses\0" // IR(5601, 10)
  "Physical64\0" // IR(5611, 11)
  "PhysicalStorageBuffer64\0" // IR(5622, 24)
  "PhysicalStorageBuffer64EXT\0" // IR(5646, 27)
  "PhysicalStorageBufferAddresses\0" // IR(5673, 31)
  "Position\0" // IR(5704, 9)
  "Shader\0" // IR(5713, 7)
  "PointSize\0" // IR(5720, 10)
  "ClipDistance\0" // IR(5730, 13)
  "CullDistance\0" // IR(5743, 13)
  "VertexId\0" // IR(5756, 9)
  "InstanceId\0" // IR(5765, 11)
  "PrimitiveId\0" // IR(5776, 12)
  "Geometry\0" // IR(5788, 9)
  "Tessellation\0" // IR(5797, 13)
  "RayTracingNV\0" // IR(5810, 13)
  "RayTracingKHR\0" // IR(5823, 14)
  "MeshShadingNV\0" // IR(5837, 14)
  "MeshShadingEXT\0" // IR(5851, 15)
  "InvocationId\0" // IR(5866, 13)
  "Layer\0" // IR(5879, 6)
  "ShaderLayer\0" // IR(5885, 12)
  "ShaderViewportIndexLayerEXT\0" // IR(5897, 28)
  "ViewportIndex\0" // IR(5925, 14)
  "MultiViewport\0" // IR(5939, 14)
  "ShaderViewportIndex\0" // IR(5953, 20)
  "TessLevelOuter\0" // IR(5973, 15)
  "TessLevelInner\0" // IR(5988, 15)
  "TessCoord\0" // IR(6003, 10)
  "PatchVertices\0" // IR(6013, 14)
  "FragCoord\0" // IR(6027, 10)
  "PointCoord\0" // IR(6037, 11)
  "FrontFacing\0" // IR(6048, 12)
  "SampleId\0" // IR(6060, 9)
  "SampleRateShading\0" // IR(6069, 18)
  "SamplePosition\0" // IR(6087, 15)
  "SampleMask\0" // IR(6102, 11)
  "FragDepth\0" // IR(6113, 10)
  "HelperInvocation\0" // IR(6123, 17)
  "NumWorkgroups\0" // IR(6140, 14)
  "WorkgroupSize\0" // IR(6154, 14)
  "WorkgroupId\0" // IR(6168, 12)
  "LocalInvocationId\0" // IR(6180, 18)
  "GlobalInvocationId\0" // IR(6198, 19)
  "LocalInvocationIndex\0" // IR(6217, 21)
  "WorkDim\0" // IR(6238, 8)
  "GlobalSize\0" // IR(6246, 11)
  "EnqueuedWorkgroupSize\0" // IR(6257, 22)
  "GlobalOffset\0" // IR(6279, 13)
  "GlobalLinearId\0" // IR(6292, 15)
  "SubgroupSize\0" // IR(6307, 13)
  "GroupNonUniform\0" // IR(6320, 16)
  "SubgroupBallotKHR\0" // IR(6336, 18)
  "SubgroupMaxSize\0" // IR(6354, 16)
  "NumSubgroups\0" // IR(6370, 13)
  "NumEnqueuedSubgroups\0" // IR(6383, 21)
  "SubgroupId\0" // IR(6404, 11)
  "SubgroupLocalInvocationId\0" // IR(6415, 26)
  "VertexIndex\0" // IR(6441, 12)
  "InstanceIndex\0" // IR(6453, 14)
  "CoreIDARM\0" // IR(6467, 10)
  "CoreBuiltinsARM\0" // IR(6477, 16)
  "CoreCountARM\0" // IR(6493, 13)
  "CoreMaxIDARM\0" // IR(6506, 13)
  "WarpIDARM\0" // IR(6519, 10)
  "WarpMaxIDARM\0" // IR(6529, 13)
  "SubgroupEqMask\0" // IR(6542, 15)
  "SubgroupEqMaskKHR\0" // IR(6557, 18)
  "GroupNonUniformBallot\0" // IR(6575, 22)
  "SubgroupGeMask\0" // IR(6597, 15)
  "SubgroupGeMaskKHR\0" // IR(6612, 18)
  "SubgroupGtMask\0" // IR(6630, 15)
  "SubgroupGtMaskKHR\0" // IR(6645, 18)
  "SubgroupLeMask\0" // IR(6663, 15)
  "SubgroupLeMaskKHR\0" // IR(6678, 18)
  "SubgroupLtMask\0" // IR(6696, 15)
  "SubgroupLtMaskKHR\0" // IR(6711, 18)
  "BaseVertex\0" // IR(6729, 11)
  "DrawParameters\0" // IR(6740, 15)
  "BaseInstance\0" // IR(6755, 13)
  "DrawIndex\0" // IR(6768, 10)
  "PrimitiveShadingRateKHR\0" // IR(6778, 24)
  "FragmentShadingRateKHR\0" // IR(6802, 23)
  "DeviceIndex\0" // IR(6825, 12)
  "DeviceGroup\0" // IR(6837, 12)
  "ViewIndex\0" // IR(6849, 10)
  "MultiView\0" // IR(6859, 10)
  "ShadingRateKHR\0" // IR(6869, 15)
  "TileOffsetQCOM\0" // IR(6884, 15)
  "TileShadingQCOM\0" // IR(6899, 16)
  "TileDimensionQCOM\0" // IR(6915, 18)
  "TileApronSizeQCOM\0" // IR(6933, 18)
  "BaryCoordNoPerspAMD\0" // IR(6951, 20)
  "BaryCoordNoPerspCentroidAMD\0" // IR(6971, 28)
  "BaryCoordNoPerspSampleAMD\0" // IR(6999, 26)
  "BaryCoordSmoothAMD\0" // IR(7025, 19)
  "BaryCoordSmoothCentroidAMD\0" // IR(7044, 27)
  "BaryCoordSmoothSampleAMD\0" // IR(7071, 25)
  "BaryCoordPullModelAMD\0" // IR(7096, 22)
  "FragStencilRefEXT\0" // IR(7118, 18)
  "StencilExportEXT\0" // IR(7136, 17)
  "RemainingRecursionLevelsAMDX\0" // IR(7153, 29)
  "ShaderEnqueueAMDX\0" // IR(7182, 18)
  "ShaderIndexAMDX\0" // IR(7200, 16)
  "SamplerHeapEXT\0" // IR(7216, 15)
  "DescriptorHeapEXT\0" // IR(7231, 18)
  "ResourceHeapEXT\0" // IR(7249, 16)
  "ViewportMaskNV\0" // IR(7265, 15)
  "ShaderViewportMaskNV\0" // IR(7280, 21)
  "SecondaryPositionNV\0" // IR(7301, 20)
  "ShaderStereoViewNV\0" // IR(7321, 19)
  "SecondaryViewportMaskNV\0" // IR(7340, 24)
  "PositionPerViewNV\0" // IR(7364, 18)
  "PerViewAttributesNV\0" // IR(7382, 20)
  "ViewportMaskPerViewNV\0" // IR(7402, 22)
  "FullyCoveredEXT\0" // IR(7424, 16)
  "FragmentFullyCoveredEXT\0" // IR(7440, 24)
  "TaskCountNV\0" // IR(7464, 12)
  "PrimitiveCountNV\0" // IR(7476, 17)
  "PrimitiveIndicesNV\0" // IR(7493, 19)
  "ClipDistancePerViewNV\0" // IR(7512, 22)
  "CullDistancePerViewNV\0" // IR(7534, 22)
  "LayerPerViewNV\0" // IR(7556, 15)
  "MeshViewCountNV\0" // IR(7571, 16)
  "MeshViewIndicesNV\0" // IR(7587, 18)
  "BaryCoordKHR\0" // IR(7605, 13)
  "BaryCoordNV\0" // IR(7618, 12)
  "FragmentBarycentricKHR\0" // IR(7630, 23)
  "BaryCoordNoPerspKHR\0" // IR(7653, 20)
  "BaryCoordNoPerspNV\0" // IR(7673, 19)
  "FragSizeEXT\0" // IR(7692, 12)
  "FragmentSizeNV\0" // IR(7704, 15)
  "FragmentDensityEXT\0" // IR(7719, 19)
  "FragInvocationCountEXT\0" // IR(7738, 23)
  "InvocationsPerPixelNV\0" // IR(7761, 22)
  "PrimitivePointIndicesEXT\0" // IR(7783, 25)
  "PrimitiveLineIndicesEXT\0" // IR(7808, 24)
  "PrimitiveTriangleIndicesEXT\0" // IR(7832, 28)
  "CullPrimitiveEXT\0" // IR(7860, 17)
  "LaunchIdKHR\0" // IR(7877, 12)
  "LaunchIdNV\0" // IR(7889, 11)
  "LaunchSizeKHR\0" // IR(7900, 14)
  "LaunchSizeNV\0" // IR(7914, 13)
  "WorldRayOriginKHR\0" // IR(7927, 18)
  "WorldRayOriginNV\0" // IR(7945, 17)
  "WorldRayDirectionKHR\0" // IR(7962, 21)
  "WorldRayDirectionNV\0" // IR(7983, 20)
  "ObjectRayOriginKHR\0" // IR(8003, 19)
  "ObjectRayOriginNV\0" // IR(8022, 18)
  "ObjectRayDirectionKHR\0" // IR(8040, 22)
  "ObjectRayDirectionNV\0" // IR(8062, 21)
  "RayTminKHR\0" // IR(8083, 11)
  "RayTminNV\0" // IR(8094, 10)
  "RayTmaxKHR\0" // IR(8104, 11)
  "RayTmaxNV\0" // IR(8115, 10)
  "InstanceCustomIndexKHR\0" // IR(8125, 23)
  "InstanceCustomIndexNV\0" // IR(8148, 22)
  "ObjectToWorldKHR\0" // IR(8170, 17)
  "ObjectToWorldNV\0" // IR(8187, 16)
  "WorldToObjectKHR\0" // IR(8203, 17)
  "WorldToObjectNV\0" // IR(8220, 16)
  "HitTNV\0" // IR(8236, 7)
  "HitKindKHR\0" // IR(8243, 11)
  "HitKindNV\0" // IR(8254, 10)
  "CurrentRayTimeNV\0" // IR(8264, 17)
  "RayTracingMotionBlurNV\0" // IR(8281, 23)
  "HitTriangleVertexPositionsKHR\0" // IR(8304, 30)
  "RayTracingPositionFetchKHR\0" // IR(8334, 27)
  "HitMicroTriangleVertexPositionsNV\0" // IR(8361, 34)
  "RayTracingDisplacementMicromapNV\0" // IR(8395, 33)
  "HitMicroTriangleVertexBarycentricsNV\0" // IR(8428, 37)
  "IncomingRayFlagsKHR\0" // IR(8465, 20)
  "IncomingRayFlagsNV\0" // IR(8485, 19)
  "RayGeometryIndexKHR\0" // IR(8504, 20)
  "HitIsSphereNV\0" // IR(8524, 14)
  "RayTracingSpheresGeometryNV\0" // IR(8538, 28)
  "HitIsLSSNV\0" // IR(8566, 11)
  "RayTracingLinearSweptSpheresGeometryNV\0" // IR(8577, 39)
  "HitSpherePositionNV\0" // IR(8616, 20)
  "WarpsPerSMNV\0" // IR(8636, 13)
  "ShaderSMBuiltinsNV\0" // IR(8649, 19)
  "SMCountNV\0" // IR(8668, 10)
  "WarpIDNV\0" // IR(8678, 9)
  "SMIDNV\0" // IR(8687, 7)
  "HitLSSPositionsNV\0" // IR(8694, 18)
  "HitKindFrontFacingMicroTriangleNV\0" // IR(8712, 34)
  "HitKindBackFacingMicroTriangleNV\0" // IR(8746, 33)
  "HitSphereRadiusNV\0" // IR(8779, 18)
  "HitLSSRadiiNV\0" // IR(8797, 14)
  "ClusterIDNV\0" // IR(8811, 12)
  "RayTracingClusterAccelerationStructureNV\0" // IR(8823, 41)
  "CullMaskKHR\0" // IR(8864, 12)
  "RayCullMaskKHR\0" // IR(8876, 15)
  "Matrix\0" // IR(8891, 7)
  "Linkage\0" // IR(8898, 8)
  "Vector16\0" // IR(8906, 9)
  "Float16Buffer\0" // IR(8915, 14)
  "Float16\0" // IR(8929, 8)
  "Float64\0" // IR(8937, 8)
  "Int64\0" // IR(8945, 6)
  "Int64Atomics\0" // IR(8951, 13)
  "ImageBasic\0" // IR(8964, 11)
  "ImageReadWrite\0" // IR(8975, 15)
  "ImageMipmap\0" // IR(8990, 12)
  "Pipes\0" // IR(9002, 6)
  "Groups\0" // IR(9008, 7)
  "DeviceEnqueue\0" // IR(9015, 14)
  "LiteralSampler\0" // IR(9029, 15)
  "AtomicStorage\0" // IR(9044, 14)
  "Int16\0" // IR(9058, 6)
  "TessellationPointSize\0" // IR(9064, 22)
  "GeometryPointSize\0" // IR(9086, 18)
  "ImageGatherExtended\0" // IR(9104, 20)
  "StorageImageMultisample\0" // IR(9124, 24)
  "UniformBufferArrayDynamicIndexing\0" // IR(9148, 34)
  "SampledImageArrayDynamicIndexing\0" // IR(9182, 33)
  "StorageBufferArrayDynamicIndexing\0" // IR(9215, 34)
  "StorageImageArrayDynamicIndexing\0" // IR(9249, 33)
  "ImageCubeArray\0" // IR(9282, 15)
  "SampledCubeArray\0" // IR(9297, 17)
  "ImageRect\0" // IR(9314, 10)
  "SampledRect\0" // IR(9324, 12)
  "GenericPointer\0" // IR(9336, 15)
  "Int8\0" // IR(9351, 5)
  "InputAttachment\0" // IR(9356, 16)
  "SparseResidency\0" // IR(9372, 16)
  "MinLod\0" // IR(9388, 7)
  "Sampled1D\0" // IR(9395, 10)
  "Image1D\0" // IR(9405, 8)
  "SampledBuffer\0" // IR(9413, 14)
  "ImageBuffer\0" // IR(9427, 12)
  "ImageMSArray\0" // IR(9439, 13)
  "StorageImageExtendedFormats\0" // IR(9452, 28)
  "ImageQuery\0" // IR(9480, 11)
  "DerivativeControl\0" // IR(9491, 18)
  "InterpolationFunction\0" // IR(9509, 22)
  "TransformFeedback\0" // IR(9531, 18)
  "GeometryStreams\0" // IR(9549, 16)
  "StorageImageReadWithoutFormat\0" // IR(9565, 30)
  "StorageImageWriteWithoutFormat\0" // IR(9595, 31)
  "SubgroupDispatch\0" // IR(9626, 17)
  "NamedBarrier\0" // IR(9643, 13)
  "PipeStorage\0" // IR(9656, 12)
  "GroupNonUniformVote\0" // IR(9668, 20)
  "GroupNonUniformArithmetic\0" // IR(9688, 26)
  "GroupNonUniformShuffle\0" // IR(9714, 23)
  "GroupNonUniformShuffleRelative\0" // IR(9737, 31)
  "GroupNonUniformClustered\0" // IR(9768, 25)
  "GroupNonUniformQuad\0" // IR(9793, 20)
  "UniformDecoration\0" // IR(9813, 18)
  "TileImageColorReadAccessEXT\0" // IR(9831, 28)
  "TileImageDepthReadAccessEXT\0" // IR(9859, 28)
  "TileImageStencilReadAccessEXT\0" // IR(9887, 30)
  "TensorsARM\0" // IR(9917, 11)
  "StorageTensorArrayDynamicIndexingARM\0" // IR(9928, 37)
  "StorageTensorArrayNonUniformIndexingARM\0" // IR(9965, 40)
  "GraphARM\0" // IR(10005, 9)
  "CooperativeMatrixLayoutsARM\0" // IR(10014, 28)
  "Float8EXT\0" // IR(10042, 10)
  "Float8CooperativeMatrixEXT\0" // IR(10052, 27)
  "CooperativeMatrixKHR\0" // IR(10079, 21)
  "WorkgroupMemoryExplicitLayoutKHR\0" // IR(10100, 33)
  "WorkgroupMemoryExplicitLayout8BitAccessKHR\0" // IR(10133, 43)
  "WorkgroupMemoryExplicitLayout16BitAccessKHR\0" // IR(10176, 44)
  "SubgroupVoteKHR\0" // IR(10220, 16)
  "StorageBuffer16BitAccess\0" // IR(10236, 25)
  "StorageUniformBufferBlock16\0" // IR(10261, 28)
  "UniformAndStorageBuffer16BitAccess\0" // IR(10289, 35)
  "StorageUniform16\0" // IR(10324, 17)
  "StoragePushConstant16\0" // IR(10341, 22)
  "StorageInputOutput16\0" // IR(10363, 21)
  "VariablePointersStorageBuffer\0" // IR(10384, 30)
  "VariablePointers\0" // IR(10414, 17)
  "AtomicStorageOps\0" // IR(10431, 17)
  "SampleMaskPostDepthCoverage\0" // IR(10448, 28)
  "StorageBuffer8BitAccess\0" // IR(10476, 24)
  "UniformAndStorageBuffer8BitAccess\0" // IR(10500, 34)
  "StoragePushConstant8\0" // IR(10534, 21)
  "DenormPreserve\0" // IR(10555, 15)
  "DenormFlushToZero\0" // IR(10570, 18)
  "SignedZeroInfNanPreserve\0" // IR(10588, 25)
  "RoundingModeRTE\0" // IR(10613, 16)
  "RoundingModeRTZ\0" // IR(10629, 16)
  "RayQueryProvisionalKHR\0" // IR(10645, 23)
  "RayQueryKHR\0" // IR(10668, 12)
  "UntypedPointersKHR\0" // IR(10680, 19)
  "RayTraversalPrimitiveCullingKHR\0" // IR(10699, 32)
  "TextureSampleWeightedQCOM\0" // IR(10731, 26)
  "TextureBoxFilterQCOM\0" // IR(10757, 21)
  "TextureBlockMatchQCOM\0" // IR(10778, 22)
  "CooperativeMatrixConversionQCOM\0" // IR(10800, 32)
  "TextureBlockMatch2QCOM\0" // IR(10832, 23)
  "Float16ImageAMD\0" // IR(10855, 16)
  "ImageGatherBiasLodAMD\0" // IR(10871, 22)
  "FragmentMaskAMD\0" // IR(10893, 16)
  "ImageReadWriteLodAMD\0" // IR(10909, 21)
  "Int64ImageEXT\0" // IR(10930, 14)
  "ShaderClockKHR\0" // IR(10944, 15)
  "QuadControlKHR\0" // IR(10959, 15)
  "Int4TypeINTEL\0" // IR(10974, 14)
  "Int4CooperativeMatrixINTEL\0" // IR(10988, 27)
  "BFloat16TypeKHR\0" // IR(11015, 16)
  "BFloat16DotProductKHR\0" // IR(11031, 22)
  "BFloat16CooperativeMatrixKHR\0" // IR(11053, 29)
  "AbortKHR\0" // IR(11082, 9)
  "ConstantDataKHR\0" // IR(11091, 16)
  "PoisonFreezeKHR\0" // IR(11107, 16)
  "SampleMaskOverrideCoverageNV\0" // IR(11123, 29)
  "GeometryShaderPassthroughNV\0" // IR(11152, 28)
  "ShaderViewportIndexLayerNV\0" // IR(11180, 27)
  "ImageFootprintNV\0" // IR(11207, 17)
  "FragmentBarycentricNV\0" // IR(11224, 22)
  "ComputeDerivativeGroupQuadsKHR\0" // IR(11246, 31)
  "ComputeDerivativeGroupQuadsNV\0" // IR(11277, 30)
  "ShadingRateNV\0" // IR(11307, 14)
  "GroupNonUniformPartitionedEXT\0" // IR(11321, 30)
  "GroupNonUniformPartitionedNV\0" // IR(11351, 29)
  "ShaderNonUniform\0" // IR(11380, 17)
  "ShaderNonUniformEXT\0" // IR(11397, 20)
  "RuntimeDescriptorArray\0" // IR(11417, 23)
  "RuntimeDescriptorArrayEXT\0" // IR(11440, 26)
  "InputAttachmentArrayDynamicIndexing\0" // IR(11466, 36)
  "InputAttachmentArrayDynamicIndexingEXT\0" // IR(11502, 39)
  "UniformTexelBufferArrayDynamicIndexing\0" // IR(11541, 39)
  "UniformTexelBufferArrayDynamicIndexingEXT\0" // IR(11580, 42)
  "StorageTexelBufferArrayDynamicIndexing\0" // IR(11622, 39)
  "StorageTexelBufferArrayDynamicIndexingEXT\0" // IR(11661, 42)
  "UniformBufferArrayNonUniformIndexing\0" // IR(11703, 37)
  "UniformBufferArrayNonUniformIndexingEXT\0" // IR(11740, 40)
  "SampledImageArrayNonUniformIndexing\0" // IR(11780, 36)
  "SampledImageArrayNonUniformIndexingEXT\0" // IR(11816, 39)
  "StorageBufferArrayNonUniformIndexing\0" // IR(11855, 37)
  "StorageBufferArrayNonUniformIndexingEXT\0" // IR(11892, 40)
  "StorageImageArrayNonUniformIndexing\0" // IR(11932, 36)
  "StorageImageArrayNonUniformIndexingEXT\0" // IR(11968, 39)
  "InputAttachmentArrayNonUniformIndexing\0" // IR(12007, 39)
  "InputAttachmentArrayNonUniformIndexingEXT\0" // IR(12046, 42)
  "UniformTexelBufferArrayNonUniformIndexing\0" // IR(12088, 42)
  "UniformTexelBufferArrayNonUniformIndexingEXT\0" // IR(12130, 45)
  "StorageTexelBufferArrayNonUniformIndexing\0" // IR(12175, 42)
  "StorageTexelBufferArrayNonUniformIndexingEXT\0" // IR(12217, 45)
  "VulkanMemoryModel\0" // IR(12262, 18)
  "VulkanMemoryModelKHR\0" // IR(12280, 21)
  "VulkanMemoryModelDeviceScope\0" // IR(12301, 29)
  "VulkanMemoryModelDeviceScopeKHR\0" // IR(12330, 32)
  "PhysicalStorageBufferAddressesEXT\0" // IR(12362, 34)
  "ComputeDerivativeGroupLinearKHR\0" // IR(12396, 32)
  "ComputeDerivativeGroupLinearNV\0" // IR(12428, 31)
  "RayTracingProvisionalKHR\0" // IR(12459, 25)
  "CooperativeMatrixNV\0" // IR(12484, 20)
  "FragmentShaderSampleInterlockEXT\0" // IR(12504, 33)
  "FragmentShaderShadingRateInterlockEXT\0" // IR(12537, 38)
  "FragmentShaderPixelInterlockEXT\0" // IR(12575, 32)
  "DemoteToHelperInvocation\0" // IR(12607, 25)
  "DemoteToHelperInvocationEXT\0" // IR(12632, 28)
  "DisplacementMicromapNV\0" // IR(12660, 23)
  "RayTracingOpacityMicromapEXT\0" // IR(12683, 29)
  "ShaderInvocationReorderNV\0" // IR(12712, 26)
  "ShaderInvocationReorderEXT\0" // IR(12738, 27)
  "BindlessTextureNV\0" // IR(12765, 18)
  "RayQueryPositionFetchKHR\0" // IR(12783, 25)
  "CooperativeVectorNV\0" // IR(12808, 20)
  "AtomicFloat16VectorNV\0" // IR(12828, 22)
  "RawAccessChainsNV\0" // IR(12850, 18)
  "PushConstantBanksNV\0" // IR(12868, 20)
  "LongVectorEXT\0" // IR(12888, 14)
  "Shader64BitIndexingEXT\0" // IR(12902, 23)
  "CooperativeMatrixReductionsNV\0" // IR(12925, 30)
  "CooperativeMatrixConversionsNV\0" // IR(12955, 31)
  "CooperativeMatrixPerElementOperationsNV\0" // IR(12986, 40)
  "CooperativeMatrixTensorAddressingNV\0" // IR(13026, 36)
  "CooperativeMatrixBlockLoadsNV\0" // IR(13062, 30)
  "CooperativeVectorTrainingNV\0" // IR(13092, 28)
  "TensorAddressingNV\0" // IR(13120, 19)
  "SubgroupShuffleINTEL\0" // IR(13139, 21)
  "SubgroupBufferBlockIOINTEL\0" // IR(13160, 27)
  "SubgroupImageBlockIOINTEL\0" // IR(13187, 26)
  "SubgroupImageMediaBlockIOINTEL\0" // IR(13213, 31)
  "RoundToInfinityINTEL\0" // IR(13244, 21)
  "FloatingPointModeINTEL\0" // IR(13265, 23)
  "IntegerFunctions2INTEL\0" // IR(13288, 23)
  "FunctionPointersINTEL\0" // IR(13311, 22)
  "IndirectReferencesINTEL\0" // IR(13333, 24)
  "AsmINTEL\0" // IR(13357, 9)
  "AtomicFloat32MinMaxEXT\0" // IR(13366, 23)
  "AtomicFloat64MinMaxEXT\0" // IR(13389, 23)
  "AtomicFloat16MinMaxEXT\0" // IR(13412, 23)
  "VectorComputeINTEL\0" // IR(13435, 19)
  "VectorAnyINTEL\0" // IR(13454, 15)
  "ExpectAssumeKHR\0" // IR(13469, 16)
  "SubgroupAvcMotionEstimationINTEL\0" // IR(13485, 33)
  "SubgroupAvcMotionEstimationIntraINTEL\0" // IR(13518, 38)
  "SubgroupAvcMotionEstimationChromaINTEL\0" // IR(13556, 39)
  "VariableLengthArrayINTEL\0" // IR(13595, 25)
  "FunctionFloatControlINTEL\0" // IR(13620, 26)
  "FPGAMemoryAttributesALTERA\0" // IR(13646, 27)
  "FPGAMemoryAttributesINTEL\0" // IR(13673, 26)
  "FPFastMathModeINTEL\0" // IR(13699, 20)
  "ArbitraryPrecisionIntegersALTERA\0" // IR(13719, 33)
  "ArbitraryPrecisionIntegersINTEL\0" // IR(13752, 32)
  "ArbitraryPrecisionFloatingPointALTERA\0" // IR(13784, 38)
  "ArbitraryPrecisionFloatingPointINTEL\0" // IR(13822, 37)
  "UnstructuredLoopControlsINTEL\0" // IR(13859, 30)
  "FPGALoopControlsALTERA\0" // IR(13889, 23)
  "FPGALoopControlsINTEL\0" // IR(13912, 22)
  "KernelAttributesINTEL\0" // IR(13934, 22)
  "FPGAKernelAttributesINTEL\0" // IR(13956, 26)
  "FPGAMemoryAccessesALTERA\0" // IR(13982, 25)
  "FPGAMemoryAccessesINTEL\0" // IR(14007, 24)
  "FPGAClusterAttributesALTERA\0" // IR(14031, 28)
  "FPGAClusterAttributesINTEL\0" // IR(14059, 27)
  "LoopFuseALTERA\0" // IR(14086, 15)
  "LoopFuseINTEL\0" // IR(14101, 14)
  "FPGADSPControlALTERA\0" // IR(14115, 21)
  "FPGADSPControlINTEL\0" // IR(14136, 20)
  "MemoryAccessAliasingINTEL\0" // IR(14156, 26)
  "FPGAInvocationPipeliningAttributesALTERA\0" // IR(14182, 41)
  "FPGAInvocationPipeliningAttributesINTEL\0" // IR(14223, 40)
  "FPGABufferLocationALTERA\0" // IR(14263, 25)
  "FPGABufferLocationINTEL\0" // IR(14288, 24)
  "ArbitraryPrecisionFixedPointALTERA\0" // IR(14312, 35)
  "ArbitraryPrecisionFixedPointINTEL\0" // IR(14347, 34)
  "USMStorageClassesALTERA\0" // IR(14381, 24)
  "USMStorageClassesINTEL\0" // IR(14405, 23)
  "RuntimeAlignedAttributeALTERA\0" // IR(14428, 30)
  "RuntimeAlignedAttributeINTEL\0" // IR(14458, 29)
  "IOPipesALTERA\0" // IR(14487, 14)
  "IOPipesINTEL\0" // IR(14501, 13)
  "BlockingPipesALTERA\0" // IR(14514, 20)
  "BlockingPipesINTEL\0" // IR(14534, 19)
  "FPGARegALTERA\0" // IR(14553, 14)
  "FPGARegINTEL\0" // IR(14567, 13)
  "DotProductInputAll\0" // IR(14580, 19)
  "DotProductInputAllKHR\0" // IR(14599, 22)
  "DotProductInput4x8Bit\0" // IR(14621, 22)
  "DotProductInput4x8BitKHR\0" // IR(14643, 25)
  "DotProductInput4x8BitPacked\0" // IR(14668, 28)
  "DotProductInput4x8BitPackedKHR\0" // IR(14696, 31)
  "DotProduct\0" // IR(14727, 11)
  "DotProductKHR\0" // IR(14738, 14)
  "ReplicatedCompositesEXT\0" // IR(14752, 24)
  "BitInstructions\0" // IR(14776, 16)
  "GroupNonUniformRotateKHR\0" // IR(14792, 25)
  "FloatControls2\0" // IR(14817, 15)
  "FMAKHR\0" // IR(14832, 7)
  "AtomicFloat32AddEXT\0" // IR(14839, 20)
  "AtomicFloat64AddEXT\0" // IR(14859, 20)
  "LongCompositesINTEL\0" // IR(14879, 20)
  "OptNoneEXT\0" // IR(14899, 11)
  "OptNoneINTEL\0" // IR(14910, 13)
  "AtomicFloat16AddEXT\0" // IR(14923, 20)
  "DebugInfoModuleINTEL\0" // IR(14943, 21)
  "BFloat16ConversionINTEL\0" // IR(14964, 24)
  "SplitBarrierINTEL\0" // IR(14988, 18)
  "ArithmeticFenceEXT\0" // IR(15006, 19)
  "FPGAClusterAttributesV2ALTERA\0" // IR(15025, 30)
  "FPGAClusterAttributesV2INTEL\0" // IR(15055, 29)
  "FPGAKernelAttributesv2INTEL\0" // IR(15084, 28)
  "TaskSequenceALTERA\0" // IR(15112, 19)
  "TaskSequenceINTEL\0" // IR(15131, 18)
  "FPMaxErrorINTEL\0" // IR(15149, 16)
  "FPGALatencyControlALTERA\0" // IR(15165, 25)
  "FPGALatencyControlINTEL\0" // IR(15190, 24)
  "FPGAArgumentInterfacesALTERA\0" // IR(15214, 29)
  "FPGAArgumentInterfacesINTEL\0" // IR(15243, 28)
  "GlobalVariableHostAccessINTEL\0" // IR(15271, 30)
  "GlobalVariableFPGADecorationsALTERA\0" // IR(15301, 36)
  "GlobalVariableFPGADecorationsINTEL\0" // IR(15337, 35)
  "SubgroupBufferPrefetchINTEL\0" // IR(15372, 28)
  "Subgroup2DBlockIOINTEL\0" // IR(15400, 23)
  "Subgroup2DBlockTransformINTEL\0" // IR(15423, 30)
  "Subgroup2DBlockTransposeINTEL\0" // IR(15453, 30)
  "SubgroupMatrixMultiplyAccumulateINTEL\0" // IR(15483, 38)
  "TernaryBitwiseFunctionINTEL\0" // IR(15521, 28)
  "UntypedVariableLengthArrayINTEL\0" // IR(15549, 32)
  "SpecConditionalINTEL\0" // IR(15581, 21)
  "FunctionVariantsINTEL\0" // IR(15602, 22)
  "GroupUniformArithmeticKHR\0" // IR(15624, 26)
  "TensorFloat32RoundingINTEL\0" // IR(15650, 27)
  "MaskedGatherScatterINTEL\0" // IR(15677, 25)
  "CacheControlsINTEL\0" // IR(15702, 19)
  "RegisterLimitsINTEL\0" // IR(15721, 20)
  "BindlessImagesINTEL\0" // IR(15741, 20)
  "DotProductFloat16AccFloat32VALVE\0" // IR(15761, 33)
  "DotProductFloat16AccFloat16VALVE\0" // IR(15794, 33)
  "DotProductBFloat16AccVALVE\0" // IR(15827, 27)
  "DotProductFloat8AccFloat32VALVE\0" // IR(15854, 32)
  "Unspecified\0" // IR(15886, 12)
  "Address\0" // IR(15898, 8)
  "Boolean\0" // IR(15906, 8)
  "Float\0" // IR(15914, 6)
  "Signed\0" // IR(15920, 7)
  "SignedChar\0" // IR(15927, 11)
  "Unsigned\0" // IR(15938, 9)
  "UnsignedChar\0" // IR(15947, 13)
  "Class\0" // IR(15960, 6)
  "Structure\0" // IR(15966, 10)
  "Union\0" // IR(15976, 6)
  "ImportedModule\0" // IR(15982, 15)
  "ImportedDeclaration\0" // IR(15997, 20)
  "None\0" // IR(16017, 5)
  "FlagIsProtected\0" // IR(16022, 16)
  "FlagIsPrivate\0" // IR(16038, 14)
  "FlagIsPublic\0" // IR(16052, 13)
  "FlagIsLocal\0" // IR(16065, 12)
  "FlagIsDefinition\0" // IR(16077, 17)
  "FlagFwdDecl\0" // IR(16094, 12)
  "FlagArtificial\0" // IR(16106, 15)
  "FlagExplicit\0" // IR(16121, 13)
  "FlagPrototyped\0" // IR(16134, 15)
  "FlagObjectPointer\0" // IR(16149, 18)
  "FlagStaticMember\0" // IR(16167, 17)
  "FlagIndirectVariable\0" // IR(16184, 21)
  "FlagLValueReference\0" // IR(16205, 20)
  "FlagRValueReference\0" // IR(16225, 20)
  "FlagIsOptimized\0" // IR(16245, 16)
  "FlagIsEnumClass\0" // IR(16261, 16)
  "FlagTypePassByValue\0" // IR(16277, 20)
  "FlagTypePassByReference\0" // IR(16297, 24)
  "Deref\0" // IR(16321, 6)
  "Plus\0" // IR(16327, 5)
  "Minus\0" // IR(16332, 6)
  "SPV_OPERAND_TYPE_LITERAL_INTEGER\0" // IR(16338, 33)
  "PlusUconst\0" // IR(16371, 11)
  "BitPiece\0" // IR(16382, 9)
  "Swap\0" // IR(16391, 5)
  "Xderef\0" // IR(16396, 7)
  "StackValue\0" // IR(16403, 11)
  "Constu\0" // IR(16414, 7)
  "Fragment\0" // IR(16421, 9)
  "ConstType\0" // IR(16430, 10)
  "VolatileType\0" // IR(16440, 13)
  "RestrictType\0" // IR(16453, 13)
  "AtomicType\0" // IR(16466, 11)
  "Float16NV\0" // IR(16477, 10)
  "Float32NV\0" // IR(16487, 10)
  "Float64NV\0" // IR(16497, 10)
  "SignedInt8NV\0" // IR(16507, 13)
  "SignedInt16NV\0" // IR(16520, 14)
  "SignedInt32NV\0" // IR(16534, 14)
  "SignedInt64NV\0" // IR(16548, 14)
  "UnsignedInt8NV\0" // IR(16562, 15)
  "UnsignedInt16NV\0" // IR(16577, 16)
  "UnsignedInt32NV\0" // IR(16593, 16)
  "UnsignedInt64NV\0" // IR(16609, 16)
  "SignedInt8PackedNV\0" // IR(16625, 19)
  "UnsignedInt8PackedNV\0" // IR(16644, 21)
  "FloatE4M3NV\0" // IR(16665, 12)
  "FloatE5M2NV\0" // IR(16677, 12)
  "RowMajorKHR\0" // IR(16689, 12)
  "ColumnMajorKHR\0" // IR(16701, 15)
  "RowBlockedInterleavedARM\0" // IR(16716, 25)
  "ColumnBlockedInterleavedARM\0" // IR(16741, 28)
  "NoneKHR\0" // IR(16769, 8)
  "MatrixASignedComponentsKHR\0" // IR(16777, 27)
  "MatrixBSignedComponentsKHR\0" // IR(16804, 27)
  "MatrixCSignedComponentsKHR\0" // IR(16831, 27)
  "MatrixResultSignedComponentsKHR\0" // IR(16858, 32)
  "SaturatingAccumulationKHR\0" // IR(16890, 26)
  "Row\0" // IR(16916, 4)
  "Column\0" // IR(16920, 7)
  "2x2\0" // IR(16927, 4)
  "MatrixAKHR\0" // IR(16931, 11)
  "MatrixBKHR\0" // IR(16942, 11)
  "MatrixAccumulatorKHR\0" // IR(16953, 21)
  "RowMajorNV\0" // IR(16974, 11)
  "ColumnMajorNV\0" // IR(16985, 14)
  "InferencingOptimalNV\0" // IR(16999, 21)
  "TrainingOptimalNV\0" // IR(17020, 18)
  "RelaxedPrecision\0" // IR(17038, 17)
  "SpecId\0" // IR(17055, 7)
  "Block\0" // IR(17062, 6)
  "BufferBlock\0" // IR(17068, 12)
  "RowMajor\0" // IR(17080, 9)
  "ColMajor\0" // IR(17089, 9)
  "ArrayStride\0" // IR(17098, 12)
  "MatrixStride\0" // IR(17110, 13)
  "GLSLShared\0" // IR(17123, 11)
  "GLSLPacked\0" // IR(17134, 11)
  "CPacked\0" // IR(17145, 8)
  "SPV_OPERAND_TYPE_BUILT_IN\0" // IR(17153, 26)
  "BuiltIn\0" // IR(17179, 8)
  "NoPerspective\0" // IR(17187, 14)
  "Flat\0" // IR(17201, 5)
  "Patch\0" // IR(17206, 6)
  "Centroid\0" // IR(17212, 9)
  "Sample\0" // IR(17221, 7)
  "Invariant\0" // IR(17228, 10)
  "Restrict\0" // IR(17238, 9)
  "Aliased\0" // IR(17247, 8)
  "Volatile\0" // IR(17255, 9)
  "Constant\0" // IR(17264, 9)
  "Coherent\0" // IR(17273, 9)
  "NonWritable\0" // IR(17282, 12)
  "NonReadable\0" // IR(17294, 12)
  "Uniform\0" // IR(17306, 8)
  "SPV_OPERAND_TYPE_SCOPE_ID\0" // IR(17314, 26)
  "UniformId\0" // IR(17340, 10)
  "SaturatedConversion\0" // IR(17350, 20)
  "Stream\0" // IR(17370, 7)
  "Location\0" // IR(17377, 9)
  "Component\0" // IR(17386, 10)
  "Index\0" // IR(17396, 6)
  "Binding\0" // IR(17402, 8)
  "DescriptorSet\0" // IR(17410, 14)
  "Offset\0" // IR(17424, 7)
  "XfbBuffer\0" // IR(17431, 10)
  "XfbStride\0" // IR(17441, 10)
  "SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE\0" // IR(17451, 46)
  "FuncParamAttr\0" // IR(17497, 14)
  "SPV_OPERAND_TYPE_FP_ROUNDING_MODE\0" // IR(17511, 34)
  "FPRoundingMode\0" // IR(17545, 15)
  "SPV_OPERAND_TYPE_FP_FAST_MATH_MODE\0" // IR(17560, 35)
  "FPFastMathMode\0" // IR(17595, 15)
  "SPV_OPERAND_TYPE_LITERAL_STRING\0" // IR(17610, 32)
  "SPV_OPERAND_TYPE_LINKAGE_TYPE\0" // IR(17642, 30)
  "LinkageAttributes\0" // IR(17672, 18)
  "NoContraction\0" // IR(17690, 14)
  "InputAttachmentIndex\0" // IR(17704, 21)
  "Alignment\0" // IR(17725, 10)
  "MaxByteOffset\0" // IR(17735, 14)
  "SPV_OPERAND_TYPE_ID\0" // IR(17749, 20)
  "AlignmentId\0" // IR(17769, 12)
  "MaxByteOffsetId\0" // IR(17781, 16)
  "SaturatedToLargestFloat8NormalConversionEXT\0" // IR(17797, 44)
  "NoSignedWrap\0" // IR(17841, 13)
  "NoUnsignedWrap\0" // IR(17854, 15)
  "WeightTextureQCOM\0" // IR(17869, 18)
  "BlockMatchTextureQCOM\0" // IR(17887, 22)
  "BlockMatchSamplerQCOM\0" // IR(17909, 22)
  "ExplicitInterpAMD\0" // IR(17931, 18)
  "NodeSharesPayloadLimitsWithAMDX\0" // IR(17949, 32)
  "NodeMaxPayloadsAMDX\0" // IR(17981, 20)
  "TrackFinishWritingAMDX\0" // IR(18001, 23)
  "PayloadNodeNameAMDX\0" // IR(18024, 20)
  "PayloadNodeBaseIndexAMDX\0" // IR(18044, 25)
  "PayloadNodeSparseArrayAMDX\0" // IR(18069, 27)
  "PayloadNodeArraySizeAMDX\0" // IR(18096, 25)
  "PayloadDispatchIndirectAMDX\0" // IR(18121, 28)
  "ArrayStrideIdEXT\0" // IR(18149, 17)
  "OffsetIdEXT\0" // IR(18166, 12)
  "UTFEncodedKHR\0" // IR(18178, 14)
  "OverrideCoverageNV\0" // IR(18192, 19)
  "PassthroughNV\0" // IR(18211, 14)
  "ViewportRelativeNV\0" // IR(18225, 19)
  "SecondaryViewportRelativeNV\0" // IR(18244, 28)
  "PerPrimitiveEXT\0" // IR(18272, 16)
  "PerPrimitiveNV\0" // IR(18288, 15)
  "PerViewNV\0" // IR(18303, 10)
  "PerTaskNV\0" // IR(18313, 10)
  "PerVertexKHR\0" // IR(18323, 13)
  "PerVertexNV\0" // IR(18336, 12)
  "NonUniform\0" // IR(18348, 11)
  "NonUniformEXT\0" // IR(18359, 14)
  "RestrictPointer\0" // IR(18373, 16)
  "RestrictPointerEXT\0" // IR(18389, 19)
  "AliasedPointer\0" // IR(18408, 15)
  "AliasedPointerEXT\0" // IR(18423, 18)
  "MemberOffsetNV\0" // IR(18441, 15)
  "HitObjectShaderRecordBufferNV\0" // IR(18456, 30)
  "HitObjectShaderRecordBufferEXT\0" // IR(18486, 31)
  "BankNV\0" // IR(18517, 7)
  "BindlessSamplerNV\0" // IR(18524, 18)
  "BindlessImageNV\0" // IR(18542, 16)
  "BoundSamplerNV\0" // IR(18558, 15)
  "BoundImageNV\0" // IR(18573, 13)
  "SIMTCallINTEL\0" // IR(18586, 14)
  "ReferencedIndirectlyINTEL\0" // IR(18600, 26)
  "ClobberINTEL\0" // IR(18626, 13)
  "SideEffectsINTEL\0" // IR(18639, 17)
  "VectorComputeVariableINTEL\0" // IR(18656, 27)
  "FuncParamIOKindINTEL\0" // IR(18683, 21)
  "VectorComputeFunctionINTEL\0" // IR(18704, 27)
  "StackCallINTEL\0" // IR(18731, 15)
  "GlobalVariableOffsetINTEL\0" // IR(18746, 26)
  "CounterBuffer\0" // IR(18772, 14)
  "HlslCounterBufferGOOGLE\0" // IR(18786, 24)
  "UserSemantic\0" // IR(18810, 13)
  "HlslSemanticGOOGLE\0" // IR(18823, 19)
  "UserTypeGOOGLE\0" // IR(18842, 15)
  "FunctionRoundingModeINTEL\0" // IR(18857, 26)
  "SPV_OPERAND_TYPE_FPDENORM_MODE\0" // IR(18883, 31)
  "FunctionDenormModeINTEL\0" // IR(18914, 24)
  "RegisterALTERA\0" // IR(18938, 15)
  "RegisterINTEL\0" // IR(18953, 14)
  "MemoryALTERA\0" // IR(18967, 13)
  "MemoryINTEL\0" // IR(18980, 12)
  "NumbanksALTERA\0" // IR(18992, 15)
  "NumbanksINTEL\0" // IR(19007, 14)
  "BankwidthALTERA\0" // IR(19021, 16)
  "BankwidthINTEL\0" // IR(19037, 15)
  "MaxPrivateCopiesALTERA\0" // IR(19052, 23)
  "MaxPrivateCopiesINTEL\0" // IR(19075, 22)
  "SinglepumpALTERA\0" // IR(19097, 17)
  "SinglepumpINTEL\0" // IR(19114, 16)
  "DoublepumpALTERA\0" // IR(19130, 17)
  "DoublepumpINTEL\0" // IR(19147, 16)
  "MaxReplicatesALTERA\0" // IR(19163, 20)
  "MaxReplicatesINTEL\0" // IR(19183, 19)
  "SimpleDualPortALTERA\0" // IR(19202, 21)
  "SimpleDualPortINTEL\0" // IR(19223, 20)
  "MergeALTERA\0" // IR(19243, 12)
  "MergeINTEL\0" // IR(19255, 11)
  "SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER\0" // IR(19266, 42)
  "BankBitsALTERA\0" // IR(19308, 15)
  "BankBitsINTEL\0" // IR(19323, 14)
  "ForcePow2DepthALTERA\0" // IR(19337, 21)
  "ForcePow2DepthINTEL\0" // IR(19358, 20)
  "StridesizeALTERA\0" // IR(19378, 17)
  "StridesizeINTEL\0" // IR(19395, 16)
  "WordsizeALTERA\0" // IR(19411, 15)
  "WordsizeINTEL\0" // IR(19426, 14)
  "TrueDualPortALTERA\0" // IR(19440, 19)
  "TrueDualPortINTEL\0" // IR(19459, 18)
  "BurstCoalesceALTERA\0" // IR(19477, 20)
  "BurstCoalesceINTEL\0" // IR(19497, 19)
  "CacheSizeALTERA\0" // IR(19516, 16)
  "CacheSizeINTEL\0" // IR(19532, 15)
  "DontStaticallyCoalesceALTERA\0" // IR(19547, 29)
  "DontStaticallyCoalesceINTEL\0" // IR(19576, 28)
  "PrefetchALTERA\0" // IR(19604, 15)
  "PrefetchINTEL\0" // IR(19619, 14)
  "StallEnableALTERA\0" // IR(19633, 18)
  "StallEnableINTEL\0" // IR(19651, 17)
  "FuseLoopsInFunctionALTERA\0" // IR(19668, 26)
  "FuseLoopsInFunctionINTEL\0" // IR(19694, 25)
  "MathOpDSPModeALTERA\0" // IR(19719, 20)
  "MathOpDSPModeINTEL\0" // IR(19739, 19)
  "AliasScopeINTEL\0" // IR(19758, 16)
  "NoAliasINTEL\0" // IR(19774, 13)
  "InitiationIntervalALTERA\0" // IR(19787, 25)
  "InitiationIntervalINTEL\0" // IR(19812, 24)
  "MaxConcurrencyALTERA\0" // IR(19836, 21)
  "MaxConcurrencyINTEL\0" // IR(19857, 20)
  "PipelineEnableALTERA\0" // IR(19877, 21)
  "PipelineEnableINTEL\0" // IR(19898, 20)
  "BufferLocationALTERA\0" // IR(19918, 21)
  "BufferLocationINTEL\0" // IR(19939, 20)
  "IOPipeStorageALTERA\0" // IR(19959, 20)
  "IOPipeStorageINTEL\0" // IR(19979, 19)
  "SPV_OPERAND_TYPE_FPOPERATION_MODE\0" // IR(19998, 34)
  "FunctionFloatingPointModeINTEL\0" // IR(20032, 31)
  "SingleElementVectorINTEL\0" // IR(20063, 25)
  "VectorComputeCallableFunctionINTEL\0" // IR(20088, 35)
  "MediaBlockIOINTEL\0" // IR(20123, 18)
  "StallFreeALTERA\0" // IR(20141, 16)
  "StallFreeINTEL\0" // IR(20157, 15)
  "SPV_OPERAND_TYPE_LITERAL_FLOAT\0" // IR(20172, 31)
  "FPMaxErrorDecorationINTEL\0" // IR(20203, 26)
  "LatencyControlLabelALTERA\0" // IR(20229, 26)
  "LatencyControlLabelINTEL\0" // IR(20255, 25)
  "LatencyControlConstraintALTERA\0" // IR(20280, 31)
  "LatencyControlConstraintINTEL\0" // IR(20311, 30)
  "ConduitKernelArgumentALTERA\0" // IR(20341, 28)
  "ConduitKernelArgumentINTEL\0" // IR(20369, 27)
  "RegisterMapKernelArgumentALTERA\0" // IR(20396, 32)
  "RegisterMapKernelArgumentINTEL\0" // IR(20428, 31)
  "MMHostInterfaceAddressWidthALTERA\0" // IR(20459, 34)
  "MMHostInterfaceAddressWidthINTEL\0" // IR(20493, 33)
  "MMHostInterfaceDataWidthALTERA\0" // IR(20526, 31)
  "MMHostInterfaceDataWidthINTEL\0" // IR(20557, 30)
  "MMHostInterfaceLatencyALTERA\0" // IR(20587, 29)
  "MMHostInterfaceLatencyINTEL\0" // IR(20616, 28)
  "SPV_OPERAND_TYPE_ACCESS_QUALIFIER\0" // IR(20644, 34)
  "MMHostInterfaceReadWriteModeALTERA\0" // IR(20678, 35)
  "MMHostInterfaceReadWriteModeINTEL\0" // IR(20713, 34)
  "MMHostInterfaceMaxBurstALTERA\0" // IR(20747, 30)
  "MMHostInterfaceMaxBurstINTEL\0" // IR(20777, 29)
  "MMHostInterfaceWaitRequestALTERA\0" // IR(20806, 33)
  "MMHostInterfaceWaitRequestINTEL\0" // IR(20839, 32)
  "StableKernelArgumentALTERA\0" // IR(20871, 27)
  "StableKernelArgumentINTEL\0" // IR(20898, 26)
  "SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER\0" // IR(20924, 39)
  "HostAccessINTEL\0" // IR(20963, 16)
  "SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER\0" // IR(20979, 47)
  "InitModeALTERA\0" // IR(21026, 15)
  "InitModeINTEL\0" // IR(21041, 14)
  "ImplementInRegisterMapALTERA\0" // IR(21055, 29)
  "ImplementInRegisterMapINTEL\0" // IR(21084, 28)
  "ConditionalINTEL\0" // IR(21112, 17)
  "SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL\0" // IR(21129, 36)
  "CacheControlLoadINTEL\0" // IR(21165, 22)
  "SPV_OPERAND_TYPE_STORE_CACHE_CONTROL\0" // IR(21187, 37)
  "CacheControlStoreINTEL\0" // IR(21224, 23)
  "1D\0" // IR(21247, 3)
  "2D\0" // IR(21250, 3)
  "3D\0" // IR(21253, 3)
  "Cube\0" // IR(21256, 5)
  "Rect\0" // IR(21261, 5)
  "Buffer\0" // IR(21266, 7)
  "SubpassData\0" // IR(21273, 12)
  "TileImageDataEXT\0" // IR(21285, 17)
  "Invocations\0" // IR(21302, 12)
  "SpacingEqual\0" // IR(21314, 13)
  "SpacingFractionalEven\0" // IR(21327, 22)
  "SpacingFractionalOdd\0" // IR(21349, 21)
  "VertexOrderCw\0" // IR(21370, 14)
  "VertexOrderCcw\0" // IR(21384, 15)
  "PixelCenterInteger\0" // IR(21399, 19)
  "OriginUpperLeft\0" // IR(21418, 16)
  "OriginLowerLeft\0" // IR(21434, 16)
  "EarlyFragmentTests\0" // IR(21450, 19)
  "PointMode\0" // IR(21469, 10)
  "Xfb\0" // IR(21479, 4)
  "DepthReplacing\0" // IR(21483, 15)
  "DepthGreater\0" // IR(21498, 13)
  "DepthLess\0" // IR(21511, 10)
  "DepthUnchanged\0" // IR(21521, 15)
  "LocalSize\0" // IR(21536, 10)
  "LocalSizeHint\0" // IR(21546, 14)
  "InputPoints\0" // IR(21560, 12)
  "InputLines\0" // IR(21572, 11)
  "InputLinesAdjacency\0" // IR(21583, 20)
  "Triangles\0" // IR(21603, 10)
  "InputTrianglesAdjacency\0" // IR(21613, 24)
  "Quads\0" // IR(21637, 6)
  "Isolines\0" // IR(21643, 9)
  "OutputVertices\0" // IR(21652, 15)
  "OutputPoints\0" // IR(21667, 13)
  "OutputLineStrip\0" // IR(21680, 16)
  "OutputTriangleStrip\0" // IR(21696, 20)
  "VecTypeHint\0" // IR(21716, 12)
  "ContractionOff\0" // IR(21728, 15)
  "Initializer\0" // IR(21743, 12)
  "Finalizer\0" // IR(21755, 10)
  "SubgroupsPerWorkgroup\0" // IR(21765, 22)
  "SubgroupsPerWorkgroupId\0" // IR(21787, 24)
  "LocalSizeId\0" // IR(21811, 12)
  "LocalSizeHintId\0" // IR(21823, 16)
  "NonCoherentColorAttachmentReadEXT\0" // IR(21839, 34)
  "NonCoherentDepthAttachmentReadEXT\0" // IR(21873, 34)
  "NonCoherentStencilAttachmentReadEXT\0" // IR(21907, 36)
  "SubgroupUniformControlFlowKHR\0" // IR(21943, 30)
  "PostDepthCoverage\0" // IR(21973, 18)
  "NonCoherentTileAttachmentReadQCOM\0" // IR(21991, 34)
  "TileShadingRateQCOM\0" // IR(22025, 20)
  "EarlyAndLateFragmentTestsAMD\0" // IR(22045, 29)
  "StencilRefReplacingEXT\0" // IR(22074, 23)
  "CoalescingAMDX\0" // IR(22097, 15)
  "IsApiEntryAMDX\0" // IR(22112, 15)
  "MaxNodeRecursionAMDX\0" // IR(22127, 21)
  "StaticNumWorkgroupsAMDX\0" // IR(22148, 24)
  "MaxNumWorkgroupsAMDX\0" // IR(22172, 21)
  "StencilRefUnchangedFrontAMD\0" // IR(22193, 28)
  "StencilRefGreaterFrontAMD\0" // IR(22221, 26)
  "StencilRefLessFrontAMD\0" // IR(22247, 23)
  "StencilRefUnchangedBackAMD\0" // IR(22270, 27)
  "StencilRefGreaterBackAMD\0" // IR(22297, 25)
  "StencilRefLessBackAMD\0" // IR(22322, 22)
  "QuadDerivativesKHR\0" // IR(22344, 19)
  "RequireFullQuadsKHR\0" // IR(22363, 20)
  "SharesInputWithAMDX\0" // IR(22383, 20)
  "ArithmeticPoisonKHR\0" // IR(22403, 20)
  "OutputLinesEXT\0" // IR(22423, 15)
  "OutputLinesNV\0" // IR(22438, 14)
  "OutputPrimitivesEXT\0" // IR(22452, 20)
  "OutputPrimitivesNV\0" // IR(22472, 19)
  "DerivativeGroupQuadsKHR\0" // IR(22491, 24)
  "DerivativeGroupQuadsNV\0" // IR(22515, 23)
  "DerivativeGroupLinearKHR\0" // IR(22538, 25)
  "DerivativeGroupLinearNV\0" // IR(22563, 24)
  "OutputTrianglesEXT\0" // IR(22587, 19)
  "OutputTrianglesNV\0" // IR(22606, 18)
  "PixelInterlockOrderedEXT\0" // IR(22624, 25)
  "PixelInterlockUnorderedEXT\0" // IR(22649, 27)
  "SampleInterlockOrderedEXT\0" // IR(22676, 26)
  "SampleInterlockUnorderedEXT\0" // IR(22702, 28)
  "ShadingRateInterlockOrderedEXT\0" // IR(22730, 31)
  "ShadingRateInterlockUnorderedEXT\0" // IR(22761, 33)
  "SharedLocalMemorySizeINTEL\0" // IR(22794, 27)
  "RoundingModeRTPINTEL\0" // IR(22821, 21)
  "RoundingModeRTNINTEL\0" // IR(22842, 21)
  "FloatingPointModeALTINTEL\0" // IR(22863, 26)
  "FloatingPointModeIEEEINTEL\0" // IR(22889, 27)
  "MaxWorkgroupSizeINTEL\0" // IR(22916, 22)
  "MaxWorkDimINTEL\0" // IR(22938, 16)
  "NoGlobalOffsetINTEL\0" // IR(22954, 20)
  "NumSIMDWorkitemsINTEL\0" // IR(22974, 22)
  "SchedulerTargetFmaxMhzINTEL\0" // IR(22996, 28)
  "MaximallyReconvergesKHR\0" // IR(23024, 24)
  "FPFastMathDefault\0" // IR(23048, 18)
  "StreamingInterfaceINTEL\0" // IR(23066, 24)
  "RegisterMapInterfaceINTEL\0" // IR(23090, 26)
  "NamedBarrierCountINTEL\0" // IR(23116, 23)
  "MaximumRegistersINTEL\0" // IR(23139, 22)
  "MaximumRegistersIdINTEL\0" // IR(23161, 24)
  "SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS\0" // IR(23185, 51)
  "NamedMaximumRegistersINTEL\0" // IR(23236, 27)
  "Vertex\0" // IR(23263, 7)
  "TessellationControl\0" // IR(23270, 20)
  "TessellationEvaluation\0" // IR(23290, 23)
  "GLCompute\0" // IR(23313, 10)
  "TaskNV\0" // IR(23323, 7)
  "MeshNV\0" // IR(23330, 7)
  "RayGenerationKHR\0" // IR(23337, 17)
  "RayGenerationNV\0" // IR(23354, 16)
  "IntersectionKHR\0" // IR(23370, 16)
  "IntersectionNV\0" // IR(23386, 15)
  "AnyHitKHR\0" // IR(23401, 10)
  "AnyHitNV\0" // IR(23411, 9)
  "ClosestHitKHR\0" // IR(23420, 14)
  "ClosestHitNV\0" // IR(23434, 13)
  "MissKHR\0" // IR(23447, 8)
  "MissNV\0" // IR(23455, 7)
  "CallableKHR\0" // IR(23462, 12)
  "CallableNV\0" // IR(23474, 11)
  "TaskEXT\0" // IR(23485, 8)
  "MeshEXT\0" // IR(23493, 8)
  "Preserve\0" // IR(23501, 9)
  "FlushToZero\0" // IR(23510, 12)
  "BFloat16KHR\0" // IR(23522, 12)
  "Float8E4M3EXT\0" // IR(23534, 14)
  "Float8E5M2EXT\0" // IR(23548, 14)
  "IEEE\0" // IR(23562, 5)
  "ALT\0" // IR(23567, 4)
  "NotNaN\0" // IR(23571, 7)
  "NotInf\0" // IR(23578, 7)
  "NSZ\0" // IR(23585, 4)
  "AllowRecip\0" // IR(23589, 11)
  "Fast\0" // IR(23600, 5)
  "AllowContract\0" // IR(23605, 14)
  "AllowContractFastINTEL\0" // IR(23619, 23)
  "AllowReassoc\0" // IR(23642, 13)
  "AllowReassocINTEL\0" // IR(23655, 18)
  "AllowTransform\0" // IR(23673, 15)
  "RTE\0" // IR(23688, 4)
  "RTZ\0" // IR(23692, 4)
  "RTP\0" // IR(23696, 4)
  "RTN\0" // IR(23700, 4)
  "Vertical2Pixels\0" // IR(23704, 16)
  "Vertical4Pixels\0" // IR(23720, 16)
  "Horizontal2Pixels\0" // IR(23736, 18)
  "Horizontal4Pixels\0" // IR(23754, 18)
  "Inline\0" // IR(23772, 7)
  "DontInline\0" // IR(23779, 11)
  "Pure\0" // IR(23790, 5)
  "Const\0" // IR(23795, 6)
  "Zext\0" // IR(23801, 5)
  "Sext\0" // IR(23806, 5)
  "ByVal\0" // IR(23811, 6)
  "Sret\0" // IR(23817, 5)
  "NoAlias\0" // IR(23822, 8)
  "NoCapture\0" // IR(23830, 10)
  "NoWrite\0" // IR(23840, 8)
  "NoReadWrite\0" // IR(23848, 12)
  "RuntimeAlignedALTERA\0" // IR(23860, 21)
  "RuntimeAlignedINTEL\0" // IR(23881, 20)
  "Reduce\0" // IR(23901, 7)
  "InclusiveScan\0" // IR(23908, 14)
  "ExclusiveScan\0" // IR(23922, 14)
  "ClusteredReduce\0" // IR(23936, 16)
  "PartitionedReduceEXT\0" // IR(23952, 21)
  "PartitionedReduceNV\0" // IR(23973, 20)
  "PartitionedInclusiveScanEXT\0" // IR(23993, 28)
  "PartitionedInclusiveScanNV\0" // IR(24021, 27)
  "PartitionedExclusiveScanEXT\0" // IR(24048, 28)
  "PartitionedExclusiveScanNV\0" // IR(24076, 27)
  "NoneINTEL\0" // IR(24103, 10)
  "ReadINTEL\0" // IR(24113, 10)
  "WriteINTEL\0" // IR(24123, 11)
  "ReadWriteINTEL\0" // IR(24134, 15)
  "Bias\0" // IR(24149, 5)
  "Lod\0" // IR(24154, 4)
  "Grad\0" // IR(24158, 5)
  "ConstOffset\0" // IR(24163, 12)
  "ConstOffsets\0" // IR(24175, 13)
  "MakeTexelAvailable\0" // IR(24188, 19)
  "MakeTexelAvailableKHR\0" // IR(24207, 22)
  "MakeTexelVisible\0" // IR(24229, 17)
  "MakeTexelVisibleKHR\0" // IR(24246, 20)
  "NonPrivateTexel\0" // IR(24266, 16)
  "NonPrivateTexelKHR\0" // IR(24282, 19)
  "VolatileTexel\0" // IR(24301, 14)
  "VolatileTexelKHR\0" // IR(24315, 17)
  "SignExtend\0" // IR(24332, 11)
  "ZeroExtend\0" // IR(24343, 11)
  "Nontemporal\0" // IR(24354, 12)
  "Offsets\0" // IR(24366, 8)
  "SnormInt8\0" // IR(24374, 10)
  "SnormInt16\0" // IR(24384, 11)
  "UnormInt8\0" // IR(24395, 10)
  "UnormInt16\0" // IR(24405, 11)
  "UnormShort565\0" // IR(24416, 14)
  "UnormShort555\0" // IR(24430, 14)
  "UnormInt101010\0" // IR(24444, 15)
  "SignedInt8\0" // IR(24459, 11)
  "SignedInt16\0" // IR(24470, 12)
  "SignedInt32\0" // IR(24482, 12)
  "UnsignedInt8\0" // IR(24494, 13)
  "UnsignedInt16\0" // IR(24507, 14)
  "UnsignedInt32\0" // IR(24521, 14)
  "HalfFloat\0" // IR(24535, 10)
  "UnormInt24\0" // IR(24545, 11)
  "UnormInt101010_2\0" // IR(24556, 17)
  "UnormInt10X6EXT\0" // IR(24573, 16)
  "UnsignedIntRaw10EXT\0" // IR(24589, 20)
  "UnsignedIntRaw12EXT\0" // IR(24609, 20)
  "UnormInt2_101010EXT\0" // IR(24629, 20)
  "UnsignedInt10X6EXT\0" // IR(24649, 19)
  "UnsignedInt12X4EXT\0" // IR(24668, 19)
  "UnsignedInt14X2EXT\0" // IR(24687, 19)
  "UnormInt12X4EXT\0" // IR(24706, 16)
  "UnormInt14X2EXT\0" // IR(24722, 16)
  "R\0" // IR(24738, 2)
  "A\0" // IR(24740, 2)
  "RG\0" // IR(24742, 3)
  "RA\0" // IR(24745, 3)
  "RGB\0" // IR(24748, 4)
  "RGBA\0" // IR(24752, 5)
  "BGRA\0" // IR(24757, 5)
  "ARGB\0" // IR(24762, 5)
  "Intensity\0" // IR(24767, 10)
  "Luminance\0" // IR(24777, 10)
  "Rx\0" // IR(24787, 3)
  "RGx\0" // IR(24790, 4)
  "RGBx\0" // IR(24794, 5)
  "Depth\0" // IR(24799, 6)
  "DepthStencil\0" // IR(24805, 13)
  "sRGB\0" // IR(24818, 5)
  "sRGBx\0" // IR(24823, 6)
  "sRGBA\0" // IR(24829, 6)
  "sBGRA\0" // IR(24835, 6)
  "ABGR\0" // IR(24841, 5)
  "InitOnDeviceReprogramALTERA\0" // IR(24846, 28)
  "InitOnDeviceReprogramINTEL\0" // IR(24874, 27)
  "InitOnDeviceResetALTERA\0" // IR(24901, 24)
  "InitOnDeviceResetINTEL\0" // IR(24925, 23)
  "NoWait\0" // IR(24948, 7)
  "WaitKernel\0" // IR(24955, 11)
  "WaitWorkGroup\0" // IR(24966, 14)
  "CmdExecTime\0" // IR(24980, 12)
  "MayUsePrintf\0" // IR(24992, 13)
  "Export\0" // IR(25005, 7)
  "Import\0" // IR(25012, 7)
  "LinkOnceODR\0" // IR(25019, 12)
  "UncachedINTEL\0" // IR(25031, 14)
  "CachedINTEL\0" // IR(25045, 12)
  "StreamingINTEL\0" // IR(25057, 15)
  "InvalidateAfterReadINTEL\0" // IR(25072, 25)
  "ConstCachedINTEL\0" // IR(25097, 17)
  "Unroll\0" // IR(25114, 7)
  "DontUnroll\0" // IR(25121, 11)
  "DependencyInfinite\0" // IR(25132, 19)
  "DependencyLength\0" // IR(25151, 17)
  "MinIterations\0" // IR(25168, 14)
  "MaxIterations\0" // IR(25182, 14)
  "IterationMultiple\0" // IR(25196, 18)
  "PeelCount\0" // IR(25214, 10)
  "PartialCount\0" // IR(25224, 13)
  "DependencyArrayALTERA\0" // IR(25237, 22)
  "DependencyArrayINTEL\0" // IR(25259, 21)
  "LoopCoalesceALTERA\0" // IR(25280, 19)
  "LoopCoalesceINTEL\0" // IR(25299, 18)
  "MaxInterleavingALTERA\0" // IR(25317, 22)
  "MaxInterleavingINTEL\0" // IR(25339, 21)
  "SpeculatedIterationsALTERA\0" // IR(25360, 27)
  "SpeculatedIterationsINTEL\0" // IR(25387, 26)
  "NoFusionALTERA\0" // IR(25413, 15)
  "NoFusionINTEL\0" // IR(25428, 14)
  "LoopCountALTERA\0" // IR(25442, 16)
  "LoopCountINTEL\0" // IR(25458, 15)
  "MaxReinvocationDelayALTERA\0" // IR(25473, 27)
  "MaxReinvocationDelayINTEL\0" // IR(25500, 26)
  "MatrixASignedComponentsINTEL\0" // IR(25526, 29)
  "MatrixBSignedComponentsINTEL\0" // IR(25555, 29)
  "MatrixCBFloat16INTEL\0" // IR(25584, 21)
  "MatrixResultBFloat16INTEL\0" // IR(25605, 26)
  "MatrixAPackedInt8INTEL\0" // IR(25631, 23)
  "MatrixBPackedInt8INTEL\0" // IR(25654, 23)
  "MatrixAPackedInt4INTEL\0" // IR(25677, 23)
  "MatrixBPackedInt4INTEL\0" // IR(25700, 23)
  "MatrixATF32INTEL\0" // IR(25723, 17)
  "MatrixBTF32INTEL\0" // IR(25740, 17)
  "MatrixAPackedFloat16INTEL\0" // IR(25757, 26)
  "MatrixBPackedFloat16INTEL\0" // IR(25783, 26)
  "MatrixAPackedBFloat16INTEL\0" // IR(25809, 27)
  "MatrixBPackedBFloat16INTEL\0" // IR(25836, 27)
  "Aligned\0" // IR(25863, 8)
  "MakePointerAvailable\0" // IR(25871, 21)
  "MakePointerAvailableKHR\0" // IR(25892, 24)
  "MakePointerVisible\0" // IR(25916, 19)
  "MakePointerVisibleKHR\0" // IR(25935, 22)
  "NonPrivatePointer\0" // IR(25957, 18)
  "NonPrivatePointerKHR\0" // IR(25975, 21)
  "AliasScopeINTELMask\0" // IR(25996, 20)
  "NoAliasINTELMask\0" // IR(26016, 17)
  "Simple\0" // IR(26033, 7)
  "GLSL450\0" // IR(26040, 8)
  "OpenCL\0" // IR(26048, 7)
  "Vulkan\0" // IR(26055, 7)
  "VulkanKHR\0" // IR(26062, 10)
  "Relaxed\0" // IR(26072, 8)
  "Acquire\0" // IR(26080, 8)
  "Release\0" // IR(26088, 8)
  "AcquireRelease\0" // IR(26096, 15)
  "SequentiallyConsistent\0" // IR(26111, 23)
  "UniformMemory\0" // IR(26134, 14)
  "SubgroupMemory\0" // IR(26148, 15)
  "WorkgroupMemory\0" // IR(26163, 16)
  "CrossWorkgroupMemory\0" // IR(26179, 21)
  "AtomicCounterMemory\0" // IR(26200, 20)
  "ImageMemory\0" // IR(26220, 12)
  "OutputMemory\0" // IR(26232, 13)
  "OutputMemoryKHR\0" // IR(26245, 16)
  "MakeAvailable\0" // IR(26261, 14)
  "MakeAvailableKHR\0" // IR(26275, 17)
  "MakeVisible\0" // IR(26292, 12)
  "MakeVisibleKHR\0" // IR(26304, 15)
  "AutoINTEL\0" // IR(26319, 10)
  "WRAP\0" // IR(26329, 5)
  "SAT\0" // IR(26334, 4)
  "SAT_ZERO\0" // IR(26338, 9)
  "SAT_SYM\0" // IR(26347, 8)
  "PackedVectorFormat4x8Bit\0" // IR(26355, 25)
  "PackedVectorFormat4x8BitKHR\0" // IR(26380, 28)
  "TRN\0" // IR(26408, 4)
  "TRN_ZERO\0" // IR(26412, 9)
  "RND\0" // IR(26421, 4)
  "RND_ZERO\0" // IR(26425, 9)
  "RND_INF\0" // IR(26434, 8)
  "RND_MIN_INF\0" // IR(26442, 12)
  "RND_CONV\0" // IR(26454, 9)
  "RND_CONV_ODD\0" // IR(26463, 13)
  "RobustnessPerComponentNV\0" // IR(26476, 25)
  "RobustnessPerElementNV\0" // IR(26501, 23)
  "OpaqueKHR\0" // IR(26524, 10)
  "NoOpaqueKHR\0" // IR(26534, 12)
  "TerminateOnFirstHitKHR\0" // IR(26546, 23)
  "SkipClosestHitShaderKHR\0" // IR(26569, 24)
  "CullBackFacingTrianglesKHR\0" // IR(26593, 27)
  "CullFrontFacingTrianglesKHR\0" // IR(26620, 28)
  "CullOpaqueKHR\0" // IR(26648, 14)
  "CullNoOpaqueKHR\0" // IR(26662, 16)
  "SkipTrianglesKHR\0" // IR(26678, 17)
  "SkipBuiltinPrimitivesNV\0" // IR(26695, 24)
  "SkipAABBsKHR\0" // IR(26719, 13)
  "ForceOpacityMicromap2StateEXT\0" // IR(26732, 30)
  "RayQueryCandidateIntersectionTriangleKHR\0" // IR(26762, 41)
  "RayQueryCandidateIntersectionAABBKHR\0" // IR(26803, 37)
  "RayQueryCommittedIntersectionNoneKHR\0" // IR(26840, 37)
  "RayQueryCommittedIntersectionTriangleKHR\0" // IR(26877, 41)
  "RayQueryCommittedIntersectionGeneratedKHR\0" // IR(26918, 42)
  "RayQueryCandidateIntersectionKHR\0" // IR(26960, 33)
  "RayQueryCommittedIntersectionKHR\0" // IR(26993, 33)
  "ClampToEdge\0" // IR(27026, 12)
  "Clamp\0" // IR(27038, 6)
  "Repeat\0" // IR(27044, 7)
  "RepeatMirrored\0" // IR(27051, 15)
  "Nearest\0" // IR(27066, 8)
  "Linear\0" // IR(27074, 7)
  "Unknown\0" // IR(27081, 8)
  "Rgba32f\0" // IR(27089, 8)
  "Rgba16f\0" // IR(27097, 8)
  "R32f\0" // IR(27105, 5)
  "Rgba8\0" // IR(27110, 6)
  "Rgba8Snorm\0" // IR(27116, 11)
  "Rg32f\0" // IR(27127, 6)
  "Rg16f\0" // IR(27133, 6)
  "R11fG11fB10f\0" // IR(27139, 13)
  "R16f\0" // IR(27152, 5)
  "Rgba16\0" // IR(27157, 7)
  "Rgb10A2\0" // IR(27164, 8)
  "Rg16\0" // IR(27172, 5)
  "Rg8\0" // IR(27177, 4)
  "R16\0" // IR(27181, 4)
  "R8\0" // IR(27185, 3)
  "Rgba16Snorm\0" // IR(27188, 12)
  "Rg16Snorm\0" // IR(27200, 10)
  "Rg8Snorm\0" // IR(27210, 9)
  "R16Snorm\0" // IR(27219, 9)
  "R8Snorm\0" // IR(27228, 8)
  "Rgba32i\0" // IR(27236, 8)
  "Rgba16i\0" // IR(27244, 8)
  "Rgba8i\0" // IR(27252, 7)
  "R32i\0" // IR(27259, 5)
  "Rg32i\0" // IR(27264, 6)
  "Rg16i\0" // IR(27270, 6)
  "Rg8i\0" // IR(27276, 5)
  "R16i\0" // IR(27281, 5)
  "R8i\0" // IR(27286, 4)
  "Rgba32ui\0" // IR(27290, 9)
  "Rgba16ui\0" // IR(27299, 9)
  "Rgba8ui\0" // IR(27308, 8)
  "R32ui\0" // IR(27316, 6)
  "Rgb10a2ui\0" // IR(27322, 10)
  "Rg32ui\0" // IR(27332, 7)
  "Rg16ui\0" // IR(27339, 7)
  "Rg8ui\0" // IR(27346, 6)
  "R16ui\0" // IR(27352, 6)
  "R8ui\0" // IR(27358, 5)
  "R64ui\0" // IR(27363, 6)
  "R64i\0" // IR(27369, 5)
  "CrossDevice\0" // IR(27374, 12)
  "Device\0" // IR(27386, 7)
  "Workgroup\0" // IR(27393, 10)
  "Subgroup\0" // IR(27403, 9)
  "Invocation\0" // IR(27412, 11)
  "QueueFamily\0" // IR(27423, 12)
  "QueueFamilyKHR\0" // IR(27435, 15)
  "ShaderCallKHR\0" // IR(27450, 14)
  "Flatten\0" // IR(27464, 8)
  "DontFlatten\0" // IR(27472, 12)
  "IdentifierPossibleDuplicates\0" // IR(27484, 29)
  "FlagUnknownPhysicalLayout\0" // IR(27513, 26)
  "ESSL\0" // IR(27539, 5)
  "GLSL\0" // IR(27544, 5)
  "OpenCL_C\0" // IR(27549, 9)
  "OpenCL_CPP\0" // IR(27558, 11)
  "HLSL\0" // IR(27569, 5)
  "CPP_for_OpenCL\0" // IR(27574, 15)
  "SYCL\0" // IR(27589, 5)
  "HERO_C\0" // IR(27594, 7)
  "NZSL\0" // IR(27601, 5)
  "WGSL\0" // IR(27606, 5)
  "Slang\0" // IR(27611, 6)
  "Zig\0" // IR(27617, 4)
  "Rust\0" // IR(27621, 5)
  "UniformConstant\0" // IR(27626, 16)
  "Input\0" // IR(27642, 6)
  "Output\0" // IR(27648, 7)
  "CrossWorkgroup\0" // IR(27655, 15)
  "Private\0" // IR(27670, 8)
  "Function\0" // IR(27678, 9)
  "Generic\0" // IR(27687, 8)
  "PushConstant\0" // IR(27695, 13)
  "AtomicCounter\0" // IR(27708, 14)
  "Image\0" // IR(27722, 6)
  "StorageBuffer\0" // IR(27728, 14)
  "TileImageEXT\0" // IR(27742, 13)
  "TileAttachmentQCOM\0" // IR(27755, 19)
  "NodePayloadAMDX\0" // IR(27774, 16)
  "CallableDataKHR\0" // IR(27790, 16)
  "CallableDataNV\0" // IR(27806, 15)
  "IncomingCallableDataKHR\0" // IR(27821, 24)
  "IncomingCallableDataNV\0" // IR(27845, 23)
  "RayPayloadKHR\0" // IR(27868, 14)
  "RayPayloadNV\0" // IR(27882, 13)
  "HitAttributeKHR\0" // IR(27895, 16)
  "HitAttributeNV\0" // IR(27911, 15)
  "IncomingRayPayloadKHR\0" // IR(27926, 22)
  "IncomingRayPayloadNV\0" // IR(27948, 21)
  "ShaderRecordBufferKHR\0" // IR(27969, 22)
  "ShaderRecordBufferNV\0" // IR(27991, 21)
  "PhysicalStorageBuffer\0" // IR(28012, 22)
  "PhysicalStorageBufferEXT\0" // IR(28034, 25)
  "HitObjectAttributeNV\0" // IR(28059, 21)
  "TaskPayloadWorkgroupEXT\0" // IR(28080, 24)
  "HitObjectAttributeEXT\0" // IR(28104, 22)
  "CodeSectionINTEL\0" // IR(28126, 17)
  "DeviceOnlyALTERA\0" // IR(28143, 17)
  "DeviceOnlyINTEL\0" // IR(28160, 16)
  "HostOnlyALTERA\0" // IR(28176, 15)
  "HostOnlyINTEL\0" // IR(28191, 14)
  "WriteThroughINTEL\0" // IR(28205, 18)
  "WriteBackINTEL\0" // IR(28223, 15)
  "TensorView\0" // IR(28238, 11)
  "DecodeFunc\0" // IR(28249, 11)
  "Undefined\0" // IR(28260, 10)
  "NoneARM\0" // IR(28270, 8)
  "NontemporalARM\0" // IR(28278, 15)
  "OutOfBoundsValueARM\0" // IR(28293, 20)
  "MakeElementAvailableARM\0" // IR(28313, 24)
  "MakeElementVisibleARM\0" // IR(28337, 22)
  "NonPrivateElementARM\0" // IR(28359, 21)
  "Nop\0" // IR(28380, 4)
  "SPV_OPERAND_TYPE_TYPE_ID\0" // IR(28384, 25)
  "SPV_OPERAND_TYPE_RESULT_ID\0" // IR(28409, 27)
  "Undef\0" // IR(28436, 6)
  "SourceContinued\0" // IR(28442, 16)
  "SPV_OPERAND_TYPE_SOURCE_LANGUAGE\0" // IR(28458, 33)
  "SPV_OPERAND_TYPE_OPTIONAL_ID\0" // IR(28491, 29)
  "SPV_OPERAND_TYPE_OPTIONAL_LITERAL_STRING\0" // IR(28520, 41)
  "Source\0" // IR(28561, 7)
  "SourceExtension\0" // IR(28568, 16)
  "Name\0" // IR(28584, 5)
  "MemberName\0" // IR(28589, 11)
  "String\0" // IR(28600, 7)
  "Line\0" // IR(28607, 5)
  "Extension\0" // IR(28612, 10)
  "ExtInstImport\0" // IR(28622, 14)
  "SPV_OPERAND_TYPE_EXTENSION_INSTRUCTION_NUMBER\0" // IR(28636, 46)
  "ExtInst\0" // IR(28682, 8)
  "SPV_OPERAND_TYPE_ADDRESSING_MODEL\0" // IR(28690, 34)
  "SPV_OPERAND_TYPE_MEMORY_MODEL\0" // IR(28724, 30)
  "MemoryModel\0" // IR(28754, 12)
  "SPV_OPERAND_TYPE_EXECUTION_MODEL\0" // IR(28766, 33)
  "SPV_OPERAND_TYPE_VARIABLE_ID\0" // IR(28799, 29)
  "EntryPoint\0" // IR(28828, 11)
  "SPV_OPERAND_TYPE_EXECUTION_MODE\0" // IR(28839, 32)
  "ExecutionMode\0" // IR(28871, 14)
  "SPV_OPERAND_TYPE_CAPABILITY\0" // IR(28885, 28)
  "Capability\0" // IR(28913, 11)
  "TypeVoid\0" // IR(28924, 9)
  "TypeBool\0" // IR(28933, 9)
  "TypeInt\0" // IR(28942, 8)
  "SPV_OPERAND_TYPE_OPTIONAL_FPENCODING\0" // IR(28950, 37)
  "TypeFloat\0" // IR(28987, 10)
  "TypeVector\0" // IR(28997, 11)
  "TypeMatrix\0" // IR(29008, 11)
  "SPV_OPERAND_TYPE_DIMENSIONALITY\0" // IR(29019, 32)
  "SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT\0" // IR(29051, 38)
  "SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER\0" // IR(29089, 43)
  "TypeImage\0" // IR(29132, 10)
  "TypeSampler\0" // IR(29142, 12)
  "TypeSampledImage\0" // IR(29154, 17)
  "TypeArray\0" // IR(29171, 10)
  "TypeRuntimeArray\0" // IR(29181, 17)
  "TypeStruct\0" // IR(29198, 11)
  "TypeOpaque\0" // IR(29209, 11)
  "SPV_OPERAND_TYPE_STORAGE_CLASS\0" // IR(29220, 31)
  "TypePointer\0" // IR(29251, 12)
  "TypeFunction\0" // IR(29263, 13)
  "TypeEvent\0" // IR(29276, 10)
  "TypeDeviceEvent\0" // IR(29286, 16)
  "TypeReserveId\0" // IR(29302, 14)
  "TypeQueue\0" // IR(29316, 10)
  "TypePipe\0" // IR(29326, 9)
  "TypeForwardPointer\0" // IR(29335, 19)
  "ConstantTrue\0" // IR(29354, 13)
  "ConstantFalse\0" // IR(29367, 14)
  "SPV_OPERAND_TYPE_TYPED_LITERAL_NUMBER\0" // IR(29381, 38)
  "ConstantComposite\0" // IR(29419, 18)
  "SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE\0" // IR(29437, 41)
  "SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE\0" // IR(29478, 37)
  "ConstantSampler\0" // IR(29515, 16)
  "ConstantNull\0" // IR(29531, 13)
  "SpecConstantTrue\0" // IR(29544, 17)
  "SpecConstantFalse\0" // IR(29561, 18)
  "SpecConstant\0" // IR(29579, 13)
  "SpecConstantComposite\0" // IR(29592, 22)
  "SPV_OPERAND_TYPE_SPEC_CONSTANT_OP_NUMBER\0" // IR(29614, 41)
  "SpecConstantOp\0" // IR(29655, 15)
  "SPV_OPERAND_TYPE_FUNCTION_CONTROL\0" // IR(29670, 34)
  "FunctionParameter\0" // IR(29704, 18)
  "FunctionEnd\0" // IR(29722, 12)
  "FunctionCall\0" // IR(29734, 13)
  "Variable\0" // IR(29747, 9)
  "ImageTexelPointer\0" // IR(29756, 18)
  "SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS\0" // IR(29774, 40)
  "Load\0" // IR(29814, 5)
  "Store\0" // IR(29819, 6)
  "CopyMemory\0" // IR(29825, 11)
  "CopyMemorySized\0" // IR(29836, 16)
  "AccessChain\0" // IR(29852, 12)
  "InBoundsAccessChain\0" // IR(29864, 20)
  "PtrAccessChain\0" // IR(29884, 15)
  "ArrayLength\0" // IR(29899, 12)
  "GenericPtrMemSemantics\0" // IR(29911, 23)
  "InBoundsPtrAccessChain\0" // IR(29934, 23)
  "SPV_OPERAND_TYPE_DECORATION\0" // IR(29957, 28)
  "Decorate\0" // IR(29985, 9)
  "MemberDecorate\0" // IR(29994, 15)
  "DecorationGroup\0" // IR(30009, 16)
  "GroupDecorate\0" // IR(30025, 14)
  "SPV_OPERAND_TYPE_VARIABLE_ID_LITERAL_INTEGER\0" // IR(30039, 45)
  "GroupMemberDecorate\0" // IR(30084, 20)
  "VectorExtractDynamic\0" // IR(30104, 21)
  "VectorInsertDynamic\0" // IR(30125, 20)
  "VectorShuffle\0" // IR(30145, 14)
  "CompositeConstruct\0" // IR(30159, 19)
  "CompositeExtract\0" // IR(30178, 17)
  "CompositeInsert\0" // IR(30195, 16)
  "CopyObject\0" // IR(30211, 11)
  "Transpose\0" // IR(30222, 10)
  "SampledImage\0" // IR(30232, 13)
  "SPV_OPERAND_TYPE_OPTIONAL_IMAGE\0" // IR(30245, 32)
  "ImageSampleImplicitLod\0" // IR(30277, 23)
  "SPV_OPERAND_TYPE_IMAGE\0" // IR(30300, 23)
  "ImageSampleExplicitLod\0" // IR(30323, 23)
  "ImageSampleDrefImplicitLod\0" // IR(30346, 27)
  "ImageSampleDrefExplicitLod\0" // IR(30373, 27)
  "ImageSampleProjImplicitLod\0" // IR(30400, 27)
  "ImageSampleProjExplicitLod\0" // IR(30427, 27)
  "ImageSampleProjDrefImplicitLod\0" // IR(30454, 31)
  "ImageSampleProjDrefExplicitLod\0" // IR(30485, 31)
  "ImageFetch\0" // IR(30516, 11)
  "ImageGather\0" // IR(30527, 12)
  "ImageDrefGather\0" // IR(30539, 16)
  "ImageRead\0" // IR(30555, 10)
  "ImageWrite\0" // IR(30565, 11)
  "ImageQueryFormat\0" // IR(30576, 17)
  "ImageQueryOrder\0" // IR(30593, 16)
  "ImageQuerySizeLod\0" // IR(30609, 18)
  "ImageQuerySize\0" // IR(30627, 15)
  "ImageQueryLod\0" // IR(30642, 14)
  "ImageQueryLevels\0" // IR(30656, 17)
  "ImageQuerySamples\0" // IR(30673, 18)
  "ConvertFToU\0" // IR(30691, 12)
  "ConvertFToS\0" // IR(30703, 12)
  "ConvertSToF\0" // IR(30715, 12)
  "ConvertUToF\0" // IR(30727, 12)
  "UConvert\0" // IR(30739, 9)
  "SConvert\0" // IR(30748, 9)
  "FConvert\0" // IR(30757, 9)
  "QuantizeToF16\0" // IR(30766, 14)
  "ConvertPtrToU\0" // IR(30780, 14)
  "SatConvertSToU\0" // IR(30794, 15)
  "SatConvertUToS\0" // IR(30809, 15)
  "ConvertUToPtr\0" // IR(30824, 14)
  "PtrCastToGeneric\0" // IR(30838, 17)
  "GenericCastToPtr\0" // IR(30855, 17)
  "GenericCastToPtrExplicit\0" // IR(30872, 25)
  "Bitcast\0" // IR(30897, 8)
  "SNegate\0" // IR(30905, 8)
  "FNegate\0" // IR(30913, 8)
  "IAdd\0" // IR(30921, 5)
  "FAdd\0" // IR(30926, 5)
  "ISub\0" // IR(30931, 5)
  "FSub\0" // IR(30936, 5)
  "IMul\0" // IR(30941, 5)
  "FMul\0" // IR(30946, 5)
  "UDiv\0" // IR(30951, 5)
  "SDiv\0" // IR(30956, 5)
  "FDiv\0" // IR(30961, 5)
  "UMod\0" // IR(30966, 5)
  "SRem\0" // IR(30971, 5)
  "SMod\0" // IR(30976, 5)
  "FRem\0" // IR(30981, 5)
  "FMod\0" // IR(30986, 5)
  "VectorTimesScalar\0" // IR(30991, 18)
  "MatrixTimesScalar\0" // IR(31009, 18)
  "VectorTimesMatrix\0" // IR(31027, 18)
  "MatrixTimesVector\0" // IR(31045, 18)
  "MatrixTimesMatrix\0" // IR(31063, 18)
  "OuterProduct\0" // IR(31081, 13)
  "Dot\0" // IR(31094, 4)
  "IAddCarry\0" // IR(31098, 10)
  "ISubBorrow\0" // IR(31108, 11)
  "UMulExtended\0" // IR(31119, 13)
  "SMulExtended\0" // IR(31132, 13)
  "Any\0" // IR(31145, 4)
  "All\0" // IR(31149, 4)
  "IsNan\0" // IR(31153, 6)
  "IsInf\0" // IR(31159, 6)
  "IsFinite\0" // IR(31165, 9)
  "IsNormal\0" // IR(31174, 9)
  "SignBitSet\0" // IR(31183, 11)
  "LessOrGreater\0" // IR(31194, 14)
  "Ordered\0" // IR(31208, 8)
  "Unordered\0" // IR(31216, 10)
  "LogicalEqual\0" // IR(31226, 13)
  "LogicalNotEqual\0" // IR(31239, 16)
  "LogicalOr\0" // IR(31255, 10)
  "LogicalAnd\0" // IR(31265, 11)
  "LogicalNot\0" // IR(31276, 11)
  "Select\0" // IR(31287, 7)
  "IEqual\0" // IR(31294, 7)
  "INotEqual\0" // IR(31301, 10)
  "UGreaterThan\0" // IR(31311, 13)
  "SGreaterThan\0" // IR(31324, 13)
  "UGreaterThanEqual\0" // IR(31337, 18)
  "SGreaterThanEqual\0" // IR(31355, 18)
  "ULessThan\0" // IR(31373, 10)
  "SLessThan\0" // IR(31383, 10)
  "ULessThanEqual\0" // IR(31393, 15)
  "SLessThanEqual\0" // IR(31408, 15)
  "FOrdEqual\0" // IR(31423, 10)
  "FUnordEqual\0" // IR(31433, 12)
  "FOrdNotEqual\0" // IR(31445, 13)
  "FUnordNotEqual\0" // IR(31458, 15)
  "FOrdLessThan\0" // IR(31473, 13)
  "FUnordLessThan\0" // IR(31486, 15)
  "FOrdGreaterThan\0" // IR(31501, 16)
  "FUnordGreaterThan\0" // IR(31517, 18)
  "FOrdLessThanEqual\0" // IR(31535, 18)
  "FUnordLessThanEqual\0" // IR(31553, 20)
  "FOrdGreaterThanEqual\0" // IR(31573, 21)
  "FUnordGreaterThanEqual\0" // IR(31594, 23)
  "ShiftRightLogical\0" // IR(31617, 18)
  "ShiftRightArithmetic\0" // IR(31635, 21)
  "ShiftLeftLogical\0" // IR(31656, 17)
  "BitwiseOr\0" // IR(31673, 10)
  "BitwiseXor\0" // IR(31683, 11)
  "BitwiseAnd\0" // IR(31694, 11)
  "Not\0" // IR(31705, 4)
  "BitFieldInsert\0" // IR(31709, 15)
  "BitFieldSExtract\0" // IR(31724, 17)
  "BitFieldUExtract\0" // IR(31741, 17)
  "BitReverse\0" // IR(31758, 11)
  "BitCount\0" // IR(31769, 9)
  "DPdx\0" // IR(31778, 5)
  "DPdy\0" // IR(31783, 5)
  "Fwidth\0" // IR(31788, 7)
  "DPdxFine\0" // IR(31795, 9)
  "DPdyFine\0" // IR(31804, 9)
  "FwidthFine\0" // IR(31813, 11)
  "DPdxCoarse\0" // IR(31824, 11)
  "DPdyCoarse\0" // IR(31835, 11)
  "FwidthCoarse\0" // IR(31846, 13)
  "EmitVertex\0" // IR(31859, 11)
  "EndPrimitive\0" // IR(31870, 13)
  "EmitStreamVertex\0" // IR(31883, 17)
  "EndStreamPrimitive\0" // IR(31900, 19)
  "SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID\0" // IR(31919, 37)
  "ControlBarrier\0" // IR(31956, 15)
  "MemoryBarrier\0" // IR(31971, 14)
  "AtomicLoad\0" // IR(31985, 11)
  "AtomicStore\0" // IR(31996, 12)
  "AtomicExchange\0" // IR(32008, 15)
  "AtomicCompareExchange\0" // IR(32023, 22)
  "AtomicCompareExchangeWeak\0" // IR(32045, 26)
  "AtomicIIncrement\0" // IR(32071, 17)
  "AtomicIDecrement\0" // IR(32088, 17)
  "AtomicIAdd\0" // IR(32105, 11)
  "AtomicISub\0" // IR(32116, 11)
  "AtomicSMin\0" // IR(32127, 11)
  "AtomicUMin\0" // IR(32138, 11)
  "AtomicSMax\0" // IR(32149, 11)
  "AtomicUMax\0" // IR(32160, 11)
  "AtomicAnd\0" // IR(32171, 10)
  "AtomicOr\0" // IR(32181, 9)
  "AtomicXor\0" // IR(32190, 10)
  "Phi\0" // IR(32200, 4)
  "SPV_OPERAND_TYPE_LOOP_CONTROL\0" // IR(32204, 30)
  "LoopMerge\0" // IR(32234, 10)
  "SPV_OPERAND_TYPE_SELECTION_CONTROL\0" // IR(32244, 35)
  "SelectionMerge\0" // IR(32279, 15)
  "Label\0" // IR(32294, 6)
  "Branch\0" // IR(32300, 7)
  "BranchConditional\0" // IR(32307, 18)
  "SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER_ID\0" // IR(32325, 45)
  "Switch\0" // IR(32370, 7)
  "Kill\0" // IR(32377, 5)
  "Return\0" // IR(32382, 7)
  "ReturnValue\0" // IR(32389, 12)
  "Unreachable\0" // IR(32401, 12)
  "LifetimeStart\0" // IR(32413, 14)
  "LifetimeStop\0" // IR(32427, 13)
  "GroupAsyncCopy\0" // IR(32440, 15)
  "GroupWaitEvents\0" // IR(32455, 16)
  "GroupAll\0" // IR(32471, 9)
  "GroupAny\0" // IR(32480, 9)
  "GroupBroadcast\0" // IR(32489, 15)
  "SPV_OPERAND_TYPE_GROUP_OPERATION\0" // IR(32504, 33)
  "GroupIAdd\0" // IR(32537, 10)
  "GroupFAdd\0" // IR(32547, 10)
  "GroupFMin\0" // IR(32557, 10)
  "GroupUMin\0" // IR(32567, 10)
  "GroupSMin\0" // IR(32577, 10)
  "GroupFMax\0" // IR(32587, 10)
  "GroupUMax\0" // IR(32597, 10)
  "GroupSMax\0" // IR(32607, 10)
  "ReadPipe\0" // IR(32617, 9)
  "WritePipe\0" // IR(32626, 10)
  "ReservedReadPipe\0" // IR(32636, 17)
  "ReservedWritePipe\0" // IR(32653, 18)
  "ReserveReadPipePackets\0" // IR(32671, 23)
  "ReserveWritePipePackets\0" // IR(32694, 24)
  "CommitReadPipe\0" // IR(32718, 15)
  "CommitWritePipe\0" // IR(32733, 16)
  "IsValidReserveId\0" // IR(32749, 17)
  "GetNumPipePackets\0" // IR(32766, 18)
  "GetMaxPipePackets\0" // IR(32784, 18)
  "GroupReserveReadPipePackets\0" // IR(32802, 28)
  "GroupReserveWritePipePackets\0" // IR(32830, 29)
  "GroupCommitReadPipe\0" // IR(32859, 20)
  "GroupCommitWritePipe\0" // IR(32879, 21)
  "EnqueueMarker\0" // IR(32900, 14)
  "EnqueueKernel\0" // IR(32914, 14)
  "GetKernelNDrangeSubGroupCount\0" // IR(32928, 30)
  "GetKernelNDrangeMaxSubGroupSize\0" // IR(32958, 32)
  "GetKernelWorkGroupSize\0" // IR(32990, 23)
  "GetKernelPreferredWorkGroupSizeMultiple\0" // IR(33013, 40)
  "RetainEvent\0" // IR(33053, 12)
  "ReleaseEvent\0" // IR(33065, 13)
  "CreateUserEvent\0" // IR(33078, 16)
  "IsValidEvent\0" // IR(33094, 13)
  "SetUserEventStatus\0" // IR(33107, 19)
  "CaptureEventProfilingInfo\0" // IR(33126, 26)
  "GetDefaultQueue\0" // IR(33152, 16)
  "BuildNDRange\0" // IR(33168, 13)
  "ImageSparseSampleImplicitLod\0" // IR(33181, 29)
  "ImageSparseSampleExplicitLod\0" // IR(33210, 29)
  "ImageSparseSampleDrefImplicitLod\0" // IR(33239, 33)
  "ImageSparseSampleDrefExplicitLod\0" // IR(33272, 33)
  "ImageSparseSampleProjImplicitLod\0" // IR(33305, 33)
  "ImageSparseSampleProjExplicitLod\0" // IR(33338, 33)
  "ImageSparseSampleProjDrefImplicitLod\0" // IR(33371, 37)
  "ImageSparseSampleProjDrefExplicitLod\0" // IR(33408, 37)
  "ImageSparseFetch\0" // IR(33445, 17)
  "ImageSparseGather\0" // IR(33462, 18)
  "ImageSparseDrefGather\0" // IR(33480, 22)
  "ImageSparseTexelsResident\0" // IR(33502, 26)
  "NoLine\0" // IR(33528, 7)
  "AtomicFlagTestAndSet\0" // IR(33535, 21)
  "AtomicFlagClear\0" // IR(33556, 16)
  "ImageSparseRead\0" // IR(33572, 16)
  "SizeOf\0" // IR(33588, 7)
  "TypePipeStorage\0" // IR(33595, 16)
  "ConstantPipeStorage\0" // IR(33611, 20)
  "CreatePipeFromPipeStorage\0" // IR(33631, 26)
  "GetKernelLocalSizeForSubgroupCount\0" // IR(33657, 35)
  "GetKernelMaxNumSubgroups\0" // IR(33692, 25)
  "TypeNamedBarrier\0" // IR(33717, 17)
  "NamedBarrierInitialize\0" // IR(33734, 23)
  "MemoryNamedBarrier\0" // IR(33757, 19)
  "ModuleProcessed\0" // IR(33776, 16)
  "ExecutionModeId\0" // IR(33792, 16)
  "DecorateId\0" // IR(33808, 11)
  "GroupNonUniformElect\0" // IR(33819, 21)
  "GroupNonUniformAll\0" // IR(33840, 19)
  "GroupNonUniformAny\0" // IR(33859, 19)
  "GroupNonUniformAllEqual\0" // IR(33878, 24)
  "GroupNonUniformBroadcast\0" // IR(33902, 25)
  "GroupNonUniformBroadcastFirst\0" // IR(33927, 30)
  "GroupNonUniformInverseBallot\0" // IR(33957, 29)
  "GroupNonUniformBallotBitExtract\0" // IR(33986, 32)
  "GroupNonUniformBallotBitCount\0" // IR(34018, 30)
  "GroupNonUniformBallotFindLSB\0" // IR(34048, 29)
  "GroupNonUniformBallotFindMSB\0" // IR(34077, 29)
  "GroupNonUniformShuffleXor\0" // IR(34106, 26)
  "GroupNonUniformShuffleUp\0" // IR(34132, 25)
  "GroupNonUniformShuffleDown\0" // IR(34157, 27)
  "GroupNonUniformIAdd\0" // IR(34184, 20)
  "GroupNonUniformFAdd\0" // IR(34204, 20)
  "GroupNonUniformIMul\0" // IR(34224, 20)
  "GroupNonUniformFMul\0" // IR(34244, 20)
  "GroupNonUniformSMin\0" // IR(34264, 20)
  "GroupNonUniformUMin\0" // IR(34284, 20)
  "GroupNonUniformFMin\0" // IR(34304, 20)
  "GroupNonUniformSMax\0" // IR(34324, 20)
  "GroupNonUniformUMax\0" // IR(34344, 20)
  "GroupNonUniformFMax\0" // IR(34364, 20)
  "GroupNonUniformBitwiseAnd\0" // IR(34384, 26)
  "GroupNonUniformBitwiseOr\0" // IR(34410, 25)
  "GroupNonUniformBitwiseXor\0" // IR(34435, 26)
  "GroupNonUniformLogicalAnd\0" // IR(34461, 26)
  "GroupNonUniformLogicalOr\0" // IR(34487, 25)
  "GroupNonUniformLogicalXor\0" // IR(34512, 26)
  "GroupNonUniformQuadBroadcast\0" // IR(34538, 29)
  "GroupNonUniformQuadSwap\0" // IR(34567, 24)
  "CopyLogical\0" // IR(34591, 12)
  "PtrEqual\0" // IR(34603, 9)
  "PtrNotEqual\0" // IR(34612, 12)
  "PtrDiff\0" // IR(34624, 8)
  "ColorAttachmentReadEXT\0" // IR(34632, 23)
  "DepthAttachmentReadEXT\0" // IR(34655, 23)
  "StencilAttachmentReadEXT\0" // IR(34678, 25)
  "TypeTensorARM\0" // IR(34703, 14)
  "SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS\0" // IR(34717, 42)
  "TensorReadARM\0" // IR(34759, 14)
  "TensorWriteARM\0" // IR(34773, 15)
  "TensorQuerySizeARM\0" // IR(34788, 19)
  "GraphConstantARM\0" // IR(34807, 17)
  "GraphEntryPointARM\0" // IR(34824, 19)
  "GraphInputARM\0" // IR(34843, 14)
  "GraphSetOutputARM\0" // IR(34857, 18)
  "GraphEndARM\0" // IR(34875, 12)
  "TypeGraphARM\0" // IR(34887, 13)
  "TerminateInvocation\0" // IR(34900, 20)
  "TypeUntypedPointerKHR\0" // IR(34920, 22)
  "UntypedVariableKHR\0" // IR(34942, 19)
  "UntypedAccessChainKHR\0" // IR(34961, 22)
  "UntypedInBoundsAccessChainKHR\0" // IR(34983, 30)
  "SubgroupFirstInvocationKHR\0" // IR(35013, 27)
  "UntypedPtrAccessChainKHR\0" // IR(35040, 25)
  "UntypedInBoundsPtrAccessChainKHR\0" // IR(35065, 33)
  "UntypedArrayLengthKHR\0" // IR(35098, 22)
  "UntypedPrefetchKHR\0" // IR(35120, 19)
  "FmaKHR\0" // IR(35139, 7)
  "SubgroupAllKHR\0" // IR(35146, 15)
  "SubgroupAnyKHR\0" // IR(35161, 15)
  "SubgroupAllEqualKHR\0" // IR(35176, 20)
  "SubgroupReadInvocationKHR\0" // IR(35196, 26)
  "ExtInstWithForwardRefsKHR\0" // IR(35222, 26)
  "UntypedGroupAsyncCopyKHR\0" // IR(35248, 25)
  "TraceRayKHR\0" // IR(35273, 12)
  "ExecuteCallableKHR\0" // IR(35285, 19)
  "ConvertUToAccelerationStructureKHR\0" // IR(35304, 35)
  "IgnoreIntersectionKHR\0" // IR(35339, 22)
  "TerminateRayKHR\0" // IR(35361, 16)
  "SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT\0" // IR(35377, 47)
  "SDot\0" // IR(35424, 5)
  "SDotKHR\0" // IR(35429, 8)
  "UDot\0" // IR(35437, 5)
  "UDotKHR\0" // IR(35442, 8)
  "SUDot\0" // IR(35450, 6)
  "SUDotKHR\0" // IR(35456, 9)
  "SDotAccSat\0" // IR(35465, 11)
  "SDotAccSatKHR\0" // IR(35476, 14)
  "UDotAccSat\0" // IR(35490, 11)
  "UDotAccSatKHR\0" // IR(35501, 14)
  "SUDotAccSat\0" // IR(35515, 12)
  "SUDotAccSatKHR\0" // IR(35527, 15)
  "TypeCooperativeMatrixKHR\0" // IR(35542, 25)
  "CooperativeMatrixLoadKHR\0" // IR(35567, 25)
  "CooperativeMatrixStoreKHR\0" // IR(35592, 26)
  "SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS\0" // IR(35618, 54)
  "CooperativeMatrixMulAddKHR\0" // IR(35672, 27)
  "CooperativeMatrixLengthKHR\0" // IR(35699, 27)
  "ConstantCompositeReplicateEXT\0" // IR(35726, 30)
  "SpecConstantCompositeReplicateEXT\0" // IR(35756, 34)
  "CompositeConstructReplicateEXT\0" // IR(35790, 31)
  "TypeRayQueryKHR\0" // IR(35821, 16)
  "RayQueryInitializeKHR\0" // IR(35837, 22)
  "RayQueryTerminateKHR\0" // IR(35859, 21)
  "RayQueryGenerateIntersectionKHR\0" // IR(35880, 32)
  "RayQueryConfirmIntersectionKHR\0" // IR(35912, 31)
  "RayQueryProceedKHR\0" // IR(35943, 19)
  "RayQueryGetIntersectionTypeKHR\0" // IR(35962, 31)
  "ImageSampleWeightedQCOM\0" // IR(35993, 24)
  "ImageBoxFilterQCOM\0" // IR(36017, 19)
  "ImageBlockMatchSSDQCOM\0" // IR(36036, 23)
  "ImageBlockMatchSADQCOM\0" // IR(36059, 23)
  "BitCastArrayQCOM\0" // IR(36082, 17)
  "ImageBlockMatchWindowSSDQCOM\0" // IR(36099, 29)
  "ImageBlockMatchWindowSADQCOM\0" // IR(36128, 29)
  "ImageBlockMatchGatherSSDQCOM\0" // IR(36157, 29)
  "ImageBlockMatchGatherSADQCOM\0" // IR(36186, 29)
  "CompositeConstructCoopMatQCOM\0" // IR(36215, 30)
  "CompositeExtractCoopMatQCOM\0" // IR(36245, 28)
  "ExtractSubArrayQCOM\0" // IR(36273, 20)
  "GroupIAddNonUniformAMD\0" // IR(36293, 23)
  "GroupFAddNonUniformAMD\0" // IR(36316, 23)
  "GroupFMinNonUniformAMD\0" // IR(36339, 23)
  "GroupUMinNonUniformAMD\0" // IR(36362, 23)
  "GroupSMinNonUniformAMD\0" // IR(36385, 23)
  "GroupFMaxNonUniformAMD\0" // IR(36408, 23)
  "GroupUMaxNonUniformAMD\0" // IR(36431, 23)
  "GroupSMaxNonUniformAMD\0" // IR(36454, 23)
  "FragmentMaskFetchAMD\0" // IR(36477, 21)
  "FragmentFetchAMD\0" // IR(36498, 17)
  "ReadClockKHR\0" // IR(36515, 13)
  "AllocateNodePayloadsAMDX\0" // IR(36528, 25)
  "EnqueueNodePayloadsAMDX\0" // IR(36553, 24)
  "TypeNodePayloadArrayAMDX\0" // IR(36577, 25)
  "FinishWritingNodePayloadAMDX\0" // IR(36602, 29)
  "NodePayloadArrayLengthAMDX\0" // IR(36631, 27)
  "IsNodePayloadValidAMDX\0" // IR(36658, 23)
  "ConstantStringAMDX\0" // IR(36681, 19)
  "SpecConstantStringAMDX\0" // IR(36700, 23)
  "GroupNonUniformQuadAllKHR\0" // IR(36723, 26)
  "GroupNonUniformQuadAnyKHR\0" // IR(36749, 26)
  "TypeBufferEXT\0" // IR(36775, 14)
  "BufferPointerEXT\0" // IR(36789, 17)
  "UntypedImageTexelPointerEXT\0" // IR(36806, 28)
  "MemberDecorateIdEXT\0" // IR(36834, 20)
  "ConstantSizeOfEXT\0" // IR(36854, 18)
  "SpecConstantDataKHR\0" // IR(36872, 20)
  "PoisonKHR\0" // IR(36892, 10)
  "FreezeKHR\0" // IR(36902, 10)
  "HitObjectRecordHitMotionNV\0" // IR(36912, 27)
  "HitObjectRecordHitWithIndexMotionNV\0" // IR(36939, 36)
  "HitObjectRecordMissMotionNV\0" // IR(36975, 28)
  "HitObjectGetWorldToObjectNV\0" // IR(37003, 28)
  "HitObjectGetObjectToWorldNV\0" // IR(37031, 28)
  "HitObjectGetObjectRayDirectionNV\0" // IR(37059, 33)
  "HitObjectGetObjectRayOriginNV\0" // IR(37092, 30)
  "HitObjectTraceRayMotionNV\0" // IR(37122, 26)
  "HitObjectGetShaderRecordBufferHandleNV\0" // IR(37148, 39)
  "HitObjectGetShaderBindingTableRecordIndexNV\0" // IR(37187, 44)
  "HitObjectRecordEmptyNV\0" // IR(37231, 23)
  "HitObjectTraceRayNV\0" // IR(37254, 20)
  "HitObjectRecordHitNV\0" // IR(37274, 21)
  "HitObjectRecordHitWithIndexNV\0" // IR(37295, 30)
  "HitObjectRecordMissNV\0" // IR(37325, 22)
  "HitObjectExecuteShaderNV\0" // IR(37347, 25)
  "HitObjectGetCurrentTimeNV\0" // IR(37372, 26)
  "HitObjectGetAttributesNV\0" // IR(37398, 25)
  "HitObjectGetHitKindNV\0" // IR(37423, 22)
  "HitObjectGetPrimitiveIndexNV\0" // IR(37445, 29)
  "HitObjectGetGeometryIndexNV\0" // IR(37474, 28)
  "HitObjectGetInstanceIdNV\0" // IR(37502, 25)
  "HitObjectGetInstanceCustomIndexNV\0" // IR(37527, 34)
  "HitObjectGetWorldRayDirectionNV\0" // IR(37561, 32)
  "HitObjectGetWorldRayOriginNV\0" // IR(37593, 29)
  "HitObjectGetRayTMaxNV\0" // IR(37622, 22)
  "HitObjectGetRayTMinNV\0" // IR(37644, 22)
  "HitObjectIsEmptyNV\0" // IR(37666, 19)
  "HitObjectIsHitNV\0" // IR(37685, 17)
  "HitObjectIsMissNV\0" // IR(37702, 18)
  "ReorderThreadWithHitObjectNV\0" // IR(37720, 29)
  "ReorderThreadWithHintNV\0" // IR(37749, 24)
  "TypeHitObjectNV\0" // IR(37773, 16)
  "ImageSampleFootprintNV\0" // IR(37789, 23)
  "TypeVectorIdEXT\0" // IR(37812, 16)
  "TypeCooperativeVectorNV\0" // IR(37828, 24)
  "CooperativeVectorMatrixMulNV\0" // IR(37852, 29)
  "CooperativeVectorOuterProductAccumulateNV\0" // IR(37881, 42)
  "CooperativeVectorReduceSumAccumulateNV\0" // IR(37923, 39)
  "CooperativeVectorMatrixMulAddNV\0" // IR(37962, 32)
  "CooperativeMatrixConvertNV\0" // IR(37994, 27)
  "EmitMeshTasksEXT\0" // IR(38021, 17)
  "SetMeshOutputsEXT\0" // IR(38038, 18)
  "GroupNonUniformPartitionEXT\0" // IR(38056, 28)
  "GroupNonUniformPartitionNV\0" // IR(38084, 27)
  "WritePackedPrimitiveIndices4x8NV\0" // IR(38111, 33)
  "FetchMicroTriangleVertexPositionNV\0" // IR(38144, 35)
  "FetchMicroTriangleVertexBarycentricNV\0" // IR(38179, 38)
  "CooperativeVectorLoadNV\0" // IR(38217, 24)
  "CooperativeVectorStoreNV\0" // IR(38241, 25)
  "HitObjectRecordFromQueryEXT\0" // IR(38266, 28)
  "HitObjectRecordMissEXT\0" // IR(38294, 23)
  "HitObjectRecordMissMotionEXT\0" // IR(38317, 29)
  "HitObjectGetIntersectionTriangleVertexPositionsEXT\0" // IR(38346, 51)
  "HitObjectGetRayFlagsEXT\0" // IR(38397, 24)
  "HitObjectSetShaderBindingTableRecordIndexEXT\0" // IR(38421, 45)
  "HitObjectReorderExecuteShaderEXT\0" // IR(38466, 33)
  "HitObjectTraceReorderExecuteEXT\0" // IR(38499, 32)
  "HitObjectTraceMotionReorderExecuteEXT\0" // IR(38531, 38)
  "TypeHitObjectEXT\0" // IR(38569, 17)
  "ReorderThreadWithHintEXT\0" // IR(38586, 25)
  "ReorderThreadWithHitObjectEXT\0" // IR(38611, 30)
  "HitObjectTraceRayEXT\0" // IR(38641, 21)
  "HitObjectTraceRayMotionEXT\0" // IR(38662, 27)
  "HitObjectRecordEmptyEXT\0" // IR(38689, 24)
  "HitObjectExecuteShaderEXT\0" // IR(38713, 26)
  "HitObjectGetCurrentTimeEXT\0" // IR(38739, 27)
  "HitObjectGetAttributesEXT\0" // IR(38766, 26)
  "HitObjectGetHitKindEXT\0" // IR(38792, 23)
  "HitObjectGetPrimitiveIndexEXT\0" // IR(38815, 30)
  "HitObjectGetGeometryIndexEXT\0" // IR(38845, 29)
  "HitObjectGetInstanceIdEXT\0" // IR(38874, 26)
  "HitObjectGetInstanceCustomIndexEXT\0" // IR(38900, 35)
  "HitObjectGetObjectRayOriginEXT\0" // IR(38935, 31)
  "HitObjectGetObjectRayDirectionEXT\0" // IR(38966, 34)
  "HitObjectGetWorldRayDirectionEXT\0" // IR(39000, 33)
  "HitObjectGetWorldRayOriginEXT\0" // IR(39033, 30)
  "HitObjectGetObjectToWorldEXT\0" // IR(39063, 29)
  "HitObjectGetWorldToObjectEXT\0" // IR(39092, 29)
  "HitObjectGetRayTMaxEXT\0" // IR(39121, 23)
  "ReportIntersectionKHR\0" // IR(39144, 22)
  "ReportIntersectionNV\0" // IR(39166, 21)
  "IgnoreIntersectionNV\0" // IR(39187, 21)
  "TerminateRayNV\0" // IR(39208, 15)
  "TraceNV\0" // IR(39223, 8)
  "TraceMotionNV\0" // IR(39231, 14)
  "TraceRayMotionNV\0" // IR(39245, 17)
  "RayQueryGetIntersectionTriangleVertexPositionsKHR\0" // IR(39262, 50)
  "TypeAccelerationStructureKHR\0" // IR(39312, 29)
  "TypeAccelerationStructureNV\0" // IR(39341, 28)
  "ExecuteCallableNV\0" // IR(39369, 18)
  "RayQueryGetIntersectionClusterIdNV\0" // IR(39387, 35)
  "RayQueryGetClusterIdNV\0" // IR(39422, 23)
  "HitObjectGetClusterIdNV\0" // IR(39445, 24)
  "HitObjectGetRayTMinEXT\0" // IR(39469, 23)
  "HitObjectGetShaderBindingTableRecordIndexEXT\0" // IR(39492, 45)
  "HitObjectGetShaderRecordBufferHandleEXT\0" // IR(39537, 40)
  "HitObjectIsEmptyEXT\0" // IR(39577, 20)
  "HitObjectIsHitEXT\0" // IR(39597, 18)
  "HitObjectIsMissEXT\0" // IR(39615, 19)
  "TypeCooperativeMatrixNV\0" // IR(39634, 24)
  "CooperativeMatrixLoadNV\0" // IR(39658, 24)
  "CooperativeMatrixStoreNV\0" // IR(39682, 25)
  "CooperativeMatrixMulAddNV\0" // IR(39707, 26)
  "CooperativeMatrixLengthNV\0" // IR(39733, 26)
  "BeginInvocationInterlockEXT\0" // IR(39759, 28)
  "EndInvocationInterlockEXT\0" // IR(39787, 26)
  "SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE\0" // IR(39813, 43)
  "CooperativeMatrixReduceNV\0" // IR(39856, 26)
  "SPV_OPERAND_TYPE_MEMORY_ACCESS\0" // IR(39882, 31)
  "SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS\0" // IR(39913, 44)
  "CooperativeMatrixLoadTensorNV\0" // IR(39957, 30)
  "CooperativeMatrixStoreTensorNV\0" // IR(39987, 31)
  "CooperativeMatrixPerElementOpNV\0" // IR(40018, 32)
  "TypeTensorLayoutNV\0" // IR(40050, 19)
  "TypeTensorViewNV\0" // IR(40069, 17)
  "CreateTensorLayoutNV\0" // IR(40086, 21)
  "TensorLayoutSetDimensionNV\0" // IR(40107, 27)
  "TensorLayoutSetStrideNV\0" // IR(40134, 24)
  "TensorLayoutSliceNV\0" // IR(40158, 20)
  "TensorLayoutSetClampValueNV\0" // IR(40178, 28)
  "CreateTensorViewNV\0" // IR(40206, 19)
  "TensorViewSetDimensionNV\0" // IR(40225, 25)
  "TensorViewSetStrideNV\0" // IR(40250, 22)
  "IsHelperInvocationEXT\0" // IR(40272, 22)
  "TensorViewSetClipNV\0" // IR(40294, 20)
  "TensorLayoutSetBlockSizeNV\0" // IR(40314, 27)
  "CooperativeMatrixTransposeNV\0" // IR(40341, 29)
  "ConvertUToImageNV\0" // IR(40370, 18)
  "ConvertUToSamplerNV\0" // IR(40388, 20)
  "ConvertImageToUNV\0" // IR(40408, 18)
  "ConvertSamplerToUNV\0" // IR(40426, 20)
  "ConvertUToSampledImageNV\0" // IR(40446, 25)
  "ConvertSampledImageToUNV\0" // IR(40471, 25)
  "SamplerImageAddressingModeNV\0" // IR(40496, 29)
  "SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS\0" // IR(40525, 52)
  "RawAccessChainNV\0" // IR(40577, 17)
  "RayQueryGetIntersectionSpherePositionNV\0" // IR(40594, 40)
  "RayQueryGetIntersectionSphereRadiusNV\0" // IR(40634, 38)
  "RayQueryGetIntersectionLSSPositionsNV\0" // IR(40672, 38)
  "RayQueryGetIntersectionLSSRadiiNV\0" // IR(40710, 34)
  "RayQueryGetIntersectionLSSHitValueNV\0" // IR(40744, 37)
  "HitObjectGetSpherePositionNV\0" // IR(40781, 29)
  "HitObjectGetSphereRadiusNV\0" // IR(40810, 27)
  "HitObjectGetLSSPositionsNV\0" // IR(40837, 27)
  "HitObjectGetLSSRadiiNV\0" // IR(40864, 23)
  "HitObjectIsSphereHitNV\0" // IR(40887, 23)
  "HitObjectIsLSSHitNV\0" // IR(40910, 20)
  "RayQueryIsSphereHitNV\0" // IR(40930, 22)
  "RayQueryIsLSSHitNV\0" // IR(40952, 19)
  "SubgroupShuffleDownINTEL\0" // IR(40971, 25)
  "SubgroupShuffleUpINTEL\0" // IR(40996, 23)
  "SubgroupShuffleXorINTEL\0" // IR(41019, 24)
  "SubgroupBlockReadINTEL\0" // IR(41043, 23)
  "SubgroupBlockWriteINTEL\0" // IR(41066, 24)
  "SubgroupImageBlockReadINTEL\0" // IR(41090, 28)
  "SubgroupImageBlockWriteINTEL\0" // IR(41118, 29)
  "SubgroupImageMediaBlockReadINTEL\0" // IR(41147, 33)
  "SubgroupImageMediaBlockWriteINTEL\0" // IR(41180, 34)
  "UCountLeadingZerosINTEL\0" // IR(41214, 24)
  "UCountTrailingZerosINTEL\0" // IR(41238, 25)
  "AbsISubINTEL\0" // IR(41263, 13)
  "AbsUSubINTEL\0" // IR(41276, 13)
  "IAddSatINTEL\0" // IR(41289, 13)
  "UAddSatINTEL\0" // IR(41302, 13)
  "IAverageINTEL\0" // IR(41315, 14)
  "UAverageINTEL\0" // IR(41329, 14)
  "IAverageRoundedINTEL\0" // IR(41343, 21)
  "UAverageRoundedINTEL\0" // IR(41364, 21)
  "ISubSatINTEL\0" // IR(41385, 13)
  "USubSatINTEL\0" // IR(41398, 13)
  "IMul32x16INTEL\0" // IR(41411, 15)
  "UMul32x16INTEL\0" // IR(41426, 15)
  "ConstantFunctionPointerINTEL\0" // IR(41441, 29)
  "FunctionPointerCallINTEL\0" // IR(41470, 25)
  "AsmTargetINTEL\0" // IR(41495, 15)
  "AsmCallINTEL\0" // IR(41510, 13)
  "AtomicFMinEXT\0" // IR(41523, 14)
  "AtomicFMaxEXT\0" // IR(41537, 14)
  "AssumeTrueKHR\0" // IR(41551, 14)
  "ExpectKHR\0" // IR(41565, 10)
  "DecorateString\0" // IR(41575, 15)
  "DecorateStringGOOGLE\0" // IR(41590, 21)
  "MemberDecorateString\0" // IR(41611, 21)
  "MemberDecorateStringGOOGLE\0" // IR(41632, 27)
  "VmeImageINTEL\0" // IR(41659, 14)
  "TypeVmeImageINTEL\0" // IR(41673, 18)
  "TypeAvcImePayloadINTEL\0" // IR(41691, 23)
  "TypeAvcRefPayloadINTEL\0" // IR(41714, 23)
  "TypeAvcSicPayloadINTEL\0" // IR(41737, 23)
  "TypeAvcMcePayloadINTEL\0" // IR(41760, 23)
  "TypeAvcMceResultINTEL\0" // IR(41783, 22)
  "TypeAvcImeResultINTEL\0" // IR(41805, 22)
  "TypeAvcImeResultSingleReferenceStreamoutINTEL\0" // IR(41827, 46)
  "TypeAvcImeResultDualReferenceStreamoutINTEL\0" // IR(41873, 44)
  "TypeAvcImeSingleReferenceStreaminINTEL\0" // IR(41917, 39)
  "TypeAvcImeDualReferenceStreaminINTEL\0" // IR(41956, 37)
  "TypeAvcRefResultINTEL\0" // IR(41993, 22)
  "TypeAvcSicResultINTEL\0" // IR(42015, 22)
  "SubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL\0" // IR(42037, 60)
  "SubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL\0" // IR(42097, 53)
  "SubgroupAvcMceGetDefaultInterShapePenaltyINTEL\0" // IR(42150, 47)
  "SubgroupAvcMceSetInterShapePenaltyINTEL\0" // IR(42197, 40)
  "SubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL\0" // IR(42237, 51)
  "SubgroupAvcMceSetInterDirectionPenaltyINTEL\0" // IR(42288, 44)
  "SubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL\0" // IR(42332, 51)
  "SubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL\0" // IR(42383, 56)
  "SubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL\0" // IR(42439, 50)
  "SubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL\0" // IR(42489, 52)
  "SubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL\0" // IR(42541, 49)
  "SubgroupAvcMceSetMotionVectorCostFunctionINTEL\0" // IR(42590, 47)
  "SubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL\0" // IR(42637, 50)
  "SubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL\0" // IR(42687, 51)
  "SubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL\0" // IR(42738, 56)
  "SubgroupAvcMceSetAcOnlyHaarINTEL\0" // IR(42794, 33)
  "SubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL\0" // IR(42827, 52)
  "SubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL\0" // IR(42879, 61)
  "SubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL\0" // IR(42940, 61)
  "SubgroupAvcMceConvertToImePayloadINTEL\0" // IR(43001, 39)
  "SubgroupAvcMceConvertToImeResultINTEL\0" // IR(43040, 38)
  "SubgroupAvcMceConvertToRefPayloadINTEL\0" // IR(43078, 39)
  "SubgroupAvcMceConvertToRefResultINTEL\0" // IR(43117, 38)
  "SubgroupAvcMceConvertToSicPayloadINTEL\0" // IR(43155, 39)
  "SubgroupAvcMceConvertToSicResultINTEL\0" // IR(43194, 38)
  "SubgroupAvcMceGetMotionVectorsINTEL\0" // IR(43232, 36)
  "SubgroupAvcMceGetInterDistortionsINTEL\0" // IR(43268, 39)
  "SubgroupAvcMceGetBestInterDistortionsINTEL\0" // IR(43307, 43)
  "SubgroupAvcMceGetInterMajorShapeINTEL\0" // IR(43350, 38)
  "SubgroupAvcMceGetInterMinorShapeINTEL\0" // IR(43388, 38)
  "SubgroupAvcMceGetInterDirectionsINTEL\0" // IR(43426, 38)
  "SubgroupAvcMceGetInterMotionVectorCountINTEL\0" // IR(43464, 45)
  "SubgroupAvcMceGetInterReferenceIdsINTEL\0" // IR(43509, 40)
  "SubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL\0" // IR(43549, 62)
  "SubgroupAvcImeInitializeINTEL\0" // IR(43611, 30)
  "SubgroupAvcImeSetSingleReferenceINTEL\0" // IR(43641, 38)
  "SubgroupAvcImeSetDualReferenceINTEL\0" // IR(43679, 36)
  "SubgroupAvcImeRefWindowSizeINTEL\0" // IR(43715, 33)
  "SubgroupAvcImeAdjustRefOffsetINTEL\0" // IR(43748, 35)
  "SubgroupAvcImeConvertToMcePayloadINTEL\0" // IR(43783, 39)
  "SubgroupAvcImeSetMaxMotionVectorCountINTEL\0" // IR(43822, 43)
  "SubgroupAvcImeSetUnidirectionalMixDisableINTEL\0" // IR(43865, 47)
  "SubgroupAvcImeSetEarlySearchTerminationThresholdINTEL\0" // IR(43912, 54)
  "SubgroupAvcImeSetWeightedSadINTEL\0" // IR(43966, 34)
  "SubgroupAvcImeEvaluateWithSingleReferenceINTEL\0" // IR(44000, 47)
  "SubgroupAvcImeEvaluateWithDualReferenceINTEL\0" // IR(44047, 45)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL\0" // IR(44092, 55)
  "SubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL\0" // IR(44147, 53)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL\0" // IR(44200, 56)
  "SubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL\0" // IR(44256, 54)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL\0" // IR(44310, 58)
  "SubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL\0" // IR(44368, 56)
  "SubgroupAvcImeConvertToMceResultINTEL\0" // IR(44424, 38)
  "SubgroupAvcImeGetSingleReferenceStreaminINTEL\0" // IR(44462, 46)
  "SubgroupAvcImeGetDualReferenceStreaminINTEL\0" // IR(44508, 44)
  "SubgroupAvcImeStripSingleReferenceStreamoutINTEL\0" // IR(44552, 49)
  "SubgroupAvcImeStripDualReferenceStreamoutINTEL\0" // IR(44601, 47)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL\0" // IR(44648, 70)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL\0" // IR(44718, 68)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL\0" // IR(44786, 69)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL\0" // IR(44855, 68)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL\0" // IR(44923, 66)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL\0" // IR(44989, 67)
  "SubgroupAvcImeGetBorderReachedINTEL\0" // IR(45056, 36)
  "SubgroupAvcImeGetTruncatedSearchIndicationINTEL\0" // IR(45092, 48)
  "SubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL\0" // IR(45140, 59)
  "SubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL\0" // IR(45199, 58)
  "SubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL\0" // IR(45257, 56)
  "SubgroupAvcFmeInitializeINTEL\0" // IR(45313, 30)
  "SubgroupAvcBmeInitializeINTEL\0" // IR(45343, 30)
  "SubgroupAvcRefConvertToMcePayloadINTEL\0" // IR(45373, 39)
  "SubgroupAvcRefSetBidirectionalMixDisableINTEL\0" // IR(45412, 46)
  "SubgroupAvcRefSetBilinearFilterEnableINTEL\0" // IR(45458, 43)
  "SubgroupAvcRefEvaluateWithSingleReferenceINTEL\0" // IR(45501, 47)
  "SubgroupAvcRefEvaluateWithDualReferenceINTEL\0" // IR(45548, 45)
  "SubgroupAvcRefEvaluateWithMultiReferenceINTEL\0" // IR(45593, 46)
  "SubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL\0" // IR(45639, 56)
  "SubgroupAvcRefConvertToMceResultINTEL\0" // IR(45695, 38)
  "SubgroupAvcSicInitializeINTEL\0" // IR(45733, 30)
  "SubgroupAvcSicConfigureSkcINTEL\0" // IR(45763, 32)
  "SubgroupAvcSicConfigureIpeLumaINTEL\0" // IR(45795, 36)
  "SubgroupAvcSicConfigureIpeLumaChromaINTEL\0" // IR(45831, 42)
  "SubgroupAvcSicGetMotionVectorMaskINTEL\0" // IR(45873, 39)
  "SubgroupAvcSicConvertToMcePayloadINTEL\0" // IR(45912, 39)
  "SubgroupAvcSicSetIntraLumaShapePenaltyINTEL\0" // IR(45951, 44)
  "SubgroupAvcSicSetIntraLumaModeCostFunctionINTEL\0" // IR(45995, 48)
  "SubgroupAvcSicSetIntraChromaModeCostFunctionINTEL\0" // IR(46043, 50)
  "SubgroupAvcSicSetBilinearFilterEnableINTEL\0" // IR(46093, 43)
  "SubgroupAvcSicSetSkcForwardTransformEnableINTEL\0" // IR(46136, 48)
  "SubgroupAvcSicSetBlockBasedRawSkipSadINTEL\0" // IR(46184, 43)
  "SubgroupAvcSicEvaluateIpeINTEL\0" // IR(46227, 31)
  "SubgroupAvcSicEvaluateWithSingleReferenceINTEL\0" // IR(46258, 47)
  "SubgroupAvcSicEvaluateWithDualReferenceINTEL\0" // IR(46305, 45)
  "SubgroupAvcSicEvaluateWithMultiReferenceINTEL\0" // IR(46350, 46)
  "SubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL\0" // IR(46396, 56)
  "SubgroupAvcSicConvertToMceResultINTEL\0" // IR(46452, 38)
  "SubgroupAvcSicGetIpeLumaShapeINTEL\0" // IR(46490, 35)
  "SubgroupAvcSicGetBestIpeLumaDistortionINTEL\0" // IR(46525, 44)
  "SubgroupAvcSicGetBestIpeChromaDistortionINTEL\0" // IR(46569, 46)
  "SubgroupAvcSicGetPackedIpeLumaModesINTEL\0" // IR(46615, 41)
  "SubgroupAvcSicGetIpeChromaModeINTEL\0" // IR(46656, 36)
  "SubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL\0" // IR(46692, 50)
  "SubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL\0" // IR(46742, 48)
  "SubgroupAvcSicGetInterRawSadsINTEL\0" // IR(46790, 35)
  "SaveMemoryINTEL\0" // IR(46825, 16)
  "RestoreMemoryINTEL\0" // IR(46841, 19)
  "ArbitraryFloatSinCosPiALTERA\0" // IR(46860, 29)
  "ArbitraryFloatSinCosPiINTEL\0" // IR(46889, 28)
  "ArbitraryFloatCastALTERA\0" // IR(46917, 25)
  "ArbitraryFloatCastINTEL\0" // IR(46942, 24)
  "ArbitraryFloatCastFromIntALTERA\0" // IR(46966, 32)
  "ArbitraryFloatCastFromIntINTEL\0" // IR(46998, 31)
  "ArbitraryFloatCastToIntALTERA\0" // IR(47029, 30)
  "ArbitraryFloatCastToIntINTEL\0" // IR(47059, 29)
  "ArbitraryFloatAddALTERA\0" // IR(47088, 24)
  "ArbitraryFloatAddINTEL\0" // IR(47112, 23)
  "ArbitraryFloatSubALTERA\0" // IR(47135, 24)
  "ArbitraryFloatSubINTEL\0" // IR(47159, 23)
  "ArbitraryFloatMulALTERA\0" // IR(47182, 24)
  "ArbitraryFloatMulINTEL\0" // IR(47206, 23)
  "ArbitraryFloatDivALTERA\0" // IR(47229, 24)
  "ArbitraryFloatDivINTEL\0" // IR(47253, 23)
  "ArbitraryFloatGTALTERA\0" // IR(47276, 23)
  "ArbitraryFloatGTINTEL\0" // IR(47299, 22)
  "ArbitraryFloatGEALTERA\0" // IR(47321, 23)
  "ArbitraryFloatGEINTEL\0" // IR(47344, 22)
  "ArbitraryFloatLTALTERA\0" // IR(47366, 23)
  "ArbitraryFloatLTINTEL\0" // IR(47389, 22)
  "ArbitraryFloatLEALTERA\0" // IR(47411, 23)
  "ArbitraryFloatLEINTEL\0" // IR(47434, 22)
  "ArbitraryFloatEQALTERA\0" // IR(47456, 23)
  "ArbitraryFloatEQINTEL\0" // IR(47479, 22)
  "ArbitraryFloatRecipALTERA\0" // IR(47501, 26)
  "ArbitraryFloatRecipINTEL\0" // IR(47527, 25)
  "ArbitraryFloatRSqrtALTERA\0" // IR(47552, 26)
  "ArbitraryFloatRSqrtINTEL\0" // IR(47578, 25)
  "ArbitraryFloatCbrtALTERA\0" // IR(47603, 25)
  "ArbitraryFloatCbrtINTEL\0" // IR(47628, 24)
  "ArbitraryFloatHypotALTERA\0" // IR(47652, 26)
  "ArbitraryFloatHypotINTEL\0" // IR(47678, 25)
  "ArbitraryFloatSqrtALTERA\0" // IR(47703, 25)
  "ArbitraryFloatSqrtINTEL\0" // IR(47728, 24)
  "ArbitraryFloatLogINTEL\0" // IR(47752, 23)
  "ArbitraryFloatLog2INTEL\0" // IR(47775, 24)
  "ArbitraryFloatLog10INTEL\0" // IR(47799, 25)
  "ArbitraryFloatLog1pINTEL\0" // IR(47824, 25)
  "ArbitraryFloatExpINTEL\0" // IR(47849, 23)
  "ArbitraryFloatExp2INTEL\0" // IR(47872, 24)
  "ArbitraryFloatExp10INTEL\0" // IR(47896, 25)
  "ArbitraryFloatExpm1INTEL\0" // IR(47921, 25)
  "ArbitraryFloatSinINTEL\0" // IR(47946, 23)
  "ArbitraryFloatCosINTEL\0" // IR(47969, 23)
  "ArbitraryFloatSinCosINTEL\0" // IR(47992, 26)
  "ArbitraryFloatSinPiINTEL\0" // IR(48018, 25)
  "ArbitraryFloatCosPiINTEL\0" // IR(48043, 25)
  "ArbitraryFloatASinINTEL\0" // IR(48068, 24)
  "ArbitraryFloatASinPiINTEL\0" // IR(48092, 26)
  "ArbitraryFloatACosINTEL\0" // IR(48118, 24)
  "ArbitraryFloatACosPiINTEL\0" // IR(48142, 26)
  "ArbitraryFloatATanINTEL\0" // IR(48168, 24)
  "ArbitraryFloatATanPiINTEL\0" // IR(48192, 26)
  "ArbitraryFloatATan2INTEL\0" // IR(48218, 25)
  "ArbitraryFloatPowINTEL\0" // IR(48243, 23)
  "ArbitraryFloatPowRINTEL\0" // IR(48266, 24)
  "ArbitraryFloatPowNINTEL\0" // IR(48290, 24)
  "LoopControlINTEL\0" // IR(48314, 17)
  "AliasDomainDeclINTEL\0" // IR(48331, 21)
  "AliasScopeDeclINTEL\0" // IR(48352, 20)
  "AliasScopeListDeclINTEL\0" // IR(48372, 24)
  "FixedSqrtALTERA\0" // IR(48396, 16)
  "FixedSqrtINTEL\0" // IR(48412, 15)
  "FixedRecipALTERA\0" // IR(48427, 17)
  "FixedRecipINTEL\0" // IR(48444, 16)
  "FixedRsqrtALTERA\0" // IR(48460, 17)
  "FixedRsqrtINTEL\0" // IR(48477, 16)
  "FixedSinALTERA\0" // IR(48493, 15)
  "FixedSinINTEL\0" // IR(48508, 14)
  "FixedCosALTERA\0" // IR(48522, 15)
  "FixedCosINTEL\0" // IR(48537, 14)
  "FixedSinCosALTERA\0" // IR(48551, 18)
  "FixedSinCosINTEL\0" // IR(48569, 17)
  "FixedSinPiALTERA\0" // IR(48586, 17)
  "FixedSinPiINTEL\0" // IR(48603, 16)
  "FixedCosPiALTERA\0" // IR(48619, 17)
  "FixedCosPiINTEL\0" // IR(48636, 16)
  "FixedSinCosPiALTERA\0" // IR(48652, 20)
  "FixedSinCosPiINTEL\0" // IR(48672, 19)
  "FixedLogALTERA\0" // IR(48691, 15)
  "FixedLogINTEL\0" // IR(48706, 14)
  "FixedExpALTERA\0" // IR(48720, 15)
  "FixedExpINTEL\0" // IR(48735, 14)
  "PtrCastToCrossWorkgroupALTERA\0" // IR(48749, 30)
  "PtrCastToCrossWorkgroupINTEL\0" // IR(48779, 29)
  "CrossWorkgroupCastToPtrALTERA\0" // IR(48808, 30)
  "CrossWorkgroupCastToPtrINTEL\0" // IR(48838, 29)
  "ReadPipeBlockingALTERA\0" // IR(48867, 23)
  "ReadPipeBlockingINTEL\0" // IR(48890, 22)
  "WritePipeBlockingALTERA\0" // IR(48912, 24)
  "WritePipeBlockingINTEL\0" // IR(48936, 23)
  "RayQueryGetRayTMinKHR\0" // IR(48959, 22)
  "RayQueryGetRayFlagsKHR\0" // IR(48981, 23)
  "RayQueryGetIntersectionTKHR\0" // IR(49004, 28)
  "RayQueryGetIntersectionInstanceCustomIndexKHR\0" // IR(49032, 46)
  "RayQueryGetIntersectionInstanceIdKHR\0" // IR(49078, 37)
  "RayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR\0" // IR(49115, 65)
  "RayQueryGetIntersectionGeometryIndexKHR\0" // IR(49180, 40)
  "RayQueryGetIntersectionPrimitiveIndexKHR\0" // IR(49220, 41)
  "RayQueryGetIntersectionBarycentricsKHR\0" // IR(49261, 39)
  "RayQueryGetIntersectionFrontFaceKHR\0" // IR(49300, 36)
  "RayQueryGetIntersectionCandidateAABBOpaqueKHR\0" // IR(49336, 46)
  "RayQueryGetIntersectionObjectRayDirectionKHR\0" // IR(49382, 45)
  "RayQueryGetIntersectionObjectRayOriginKHR\0" // IR(49427, 42)
  "RayQueryGetWorldRayDirectionKHR\0" // IR(49469, 32)
  "RayQueryGetWorldRayOriginKHR\0" // IR(49501, 29)
  "RayQueryGetIntersectionObjectToWorldKHR\0" // IR(49530, 40)
  "RayQueryGetIntersectionWorldToObjectKHR\0" // IR(49570, 40)
  "AtomicFAddEXT\0" // IR(49610, 14)
  "TypeBufferSurfaceINTEL\0" // IR(49624, 23)
  "TypeStructContinuedINTEL\0" // IR(49647, 25)
  "ConstantCompositeContinuedINTEL\0" // IR(49672, 32)
  "SpecConstantCompositeContinuedINTEL\0" // IR(49704, 36)
  "CompositeConstructContinuedINTEL\0" // IR(49740, 33)
  "ConvertFToBF16INTEL\0" // IR(49773, 20)
  "ConvertBF16ToFINTEL\0" // IR(49793, 20)
  "ControlBarrierArriveINTEL\0" // IR(49813, 26)
  "ControlBarrierWaitINTEL\0" // IR(49839, 24)
  "TaskSequenceCreateALTERA\0" // IR(49863, 25)
  "TaskSequenceCreateINTEL\0" // IR(49888, 24)
  "TaskSequenceAsyncALTERA\0" // IR(49912, 24)
  "TaskSequenceAsyncINTEL\0" // IR(49936, 23)
  "TaskSequenceGetALTERA\0" // IR(49959, 22)
  "TaskSequenceGetINTEL\0" // IR(49981, 21)
  "TaskSequenceReleaseALTERA\0" // IR(50002, 26)
  "TaskSequenceReleaseINTEL\0" // IR(50028, 25)
  "TypeTaskSequenceALTERA\0" // IR(50053, 23)
  "TypeTaskSequenceINTEL\0" // IR(50076, 22)
  "SubgroupBlockPrefetchINTEL\0" // IR(50098, 27)
  "Subgroup2DBlockLoadINTEL\0" // IR(50125, 25)
  "Subgroup2DBlockLoadTransformINTEL\0" // IR(50150, 34)
  "Subgroup2DBlockLoadTransposeINTEL\0" // IR(50184, 34)
  "Subgroup2DBlockPrefetchINTEL\0" // IR(50218, 29)
  "Subgroup2DBlockStoreINTEL\0" // IR(50247, 26)
  "SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS\0" // IR(50273, 62)
  "BitwiseFunctionINTEL\0" // IR(50335, 21)
  "ConditionalExtensionINTEL\0" // IR(50356, 26)
  "ConditionalEntryPointINTEL\0" // IR(50382, 27)
  "ConditionalCapabilityINTEL\0" // IR(50409, 27)
  "SpecConstantTargetINTEL\0" // IR(50436, 24)
  "SpecConstantArchitectureINTEL\0" // IR(50460, 30)
  "SPV_OPERAND_TYPE_VARIABLE_CAPABILITY\0" // IR(50490, 37)
  "SpecConstantCapabilitiesINTEL\0" // IR(50527, 30)
  "ConditionalCopyObjectINTEL\0" // IR(50557, 27)
  "GroupIMulKHR\0" // IR(50584, 13)
  "GroupFMulKHR\0" // IR(50597, 13)
  "GroupBitwiseAndKHR\0" // IR(50610, 19)
  "GroupBitwiseOrKHR\0" // IR(50629, 18)
  "GroupBitwiseXorKHR\0" // IR(50647, 19)
  "GroupLogicalAndKHR\0" // IR(50666, 19)
  "GroupLogicalOrKHR\0" // IR(50685, 18)
  "GroupLogicalXorKHR\0" // IR(50703, 19)
  "RoundFToTF32INTEL\0" // IR(50722, 18)
  "MaskedGatherINTEL\0" // IR(50740, 18)
  "MaskedScatterINTEL\0" // IR(50758, 19)
  "ConvertHandleToImageINTEL\0" // IR(50777, 26)
  "ConvertHandleToSamplerINTEL\0" // IR(50803, 28)
  "ConvertHandleToSampledImageINTEL\0" // IR(50831, 33)
  "FDot2MixAcc32VALVE\0" // IR(50864, 19)
  "FDot2MixAcc16VALVE\0" // IR(50883, 19)
  "FDot4MixAcc32VALVE\0" // IR(50902, 19)
  "DebugInfoNone\0" // IR(50921, 14)
  "DebugCompilationUnit\0" // IR(50935, 21)
  "SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING\0" // IR(50956, 52)
  "DebugTypeBasic\0" // IR(51008, 15)
  "SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS\0" // IR(51023, 34)
  "DebugTypePointer\0" // IR(51057, 17)
  "SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER\0" // IR(51074, 38)
  "DebugTypeQualifier\0" // IR(51112, 19)
  "DebugTypeArray\0" // IR(51131, 15)
  "DebugTypeVector\0" // IR(51146, 16)
  "DebugTypedef\0" // IR(51162, 13)
  "DebugTypeFunction\0" // IR(51175, 18)
  "DebugTypeEnum\0" // IR(51193, 14)
  "SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE\0" // IR(51207, 38)
  "DebugTypeComposite\0" // IR(51245, 19)
  "DebugTypeMember\0" // IR(51264, 16)
  "DebugTypeInheritance\0" // IR(51280, 21)
  "DebugTypePtrToMember\0" // IR(51301, 21)
  "DebugTypeTemplate\0" // IR(51322, 18)
  "DebugTypeTemplateParameter\0" // IR(51340, 27)
  "DebugTypeTemplateTemplateParameter\0" // IR(51367, 35)
  "DebugTypeTemplateParameterPack\0" // IR(51402, 31)
  "DebugGlobalVariable\0" // IR(51433, 20)
  "DebugFunctionDeclaration\0" // IR(51453, 25)
  "DebugFunction\0" // IR(51478, 14)
  "DebugLexicalBlock\0" // IR(51492, 18)
  "DebugLexicalBlockDiscriminator\0" // IR(51510, 31)
  "DebugScope\0" // IR(51541, 11)
  "DebugNoScope\0" // IR(51552, 13)
  "DebugInlinedAt\0" // IR(51565, 15)
  "SPV_OPERAND_TYPE_OPTIONAL_LITERAL_INTEGER\0" // IR(51580, 42)
  "DebugLocalVariable\0" // IR(51622, 19)
  "DebugInlinedVariable\0" // IR(51641, 21)
  "DebugDeclare\0" // IR(51662, 13)
  "DebugValue\0" // IR(51675, 11)
  "SPV_OPERAND_TYPE_DEBUG_OPERATION\0" // IR(51686, 33)
  "DebugOperation\0" // IR(51719, 15)
  "DebugExpression\0" // IR(51734, 16)
  "DebugMacroDef\0" // IR(51750, 14)
  "DebugMacroUndef\0" // IR(51764, 16)
  "Round\0" // IR(51780, 6)
  "RoundEven\0" // IR(51786, 10)
  "Trunc\0" // IR(51796, 6)
  "FAbs\0" // IR(51802, 5)
  "SAbs\0" // IR(51807, 5)
  "FSign\0" // IR(51812, 6)
  "SSign\0" // IR(51818, 6)
  "Floor\0" // IR(51824, 6)
  "Ceil\0" // IR(51830, 5)
  "Fract\0" // IR(51835, 6)
  "Radians\0" // IR(51841, 8)
  "Degrees\0" // IR(51849, 8)
  "Sin\0" // IR(51857, 4)
  "Cos\0" // IR(51861, 4)
  "Tan\0" // IR(51865, 4)
  "Asin\0" // IR(51869, 5)
  "Acos\0" // IR(51874, 5)
  "Atan\0" // IR(51879, 5)
  "Sinh\0" // IR(51884, 5)
  "Cosh\0" // IR(51889, 5)
  "Tanh\0" // IR(51894, 5)
  "Asinh\0" // IR(51899, 6)
  "Acosh\0" // IR(51905, 6)
  "Atanh\0" // IR(51911, 6)
  "Atan2\0" // IR(51917, 6)
  "Pow\0" // IR(51923, 4)
  "Exp\0" // IR(51927, 4)
  "Log\0" // IR(51931, 4)
  "Exp2\0" // IR(51935, 5)
  "Log2\0" // IR(51940, 5)
  "Sqrt\0" // IR(51945, 5)
  "InverseSqrt\0" // IR(51950, 12)
  "Determinant\0" // IR(51962, 12)
  "MatrixInverse\0" // IR(51974, 14)
  "Modf\0" // IR(51988, 5)
  "ModfStruct\0" // IR(51993, 11)
  "FMin\0" // IR(52004, 5)
  "UMin\0" // IR(52009, 5)
  "SMin\0" // IR(52014, 5)
  "FMax\0" // IR(52019, 5)
  "UMax\0" // IR(52024, 5)
  "SMax\0" // IR(52029, 5)
  "FClamp\0" // IR(52034, 7)
  "UClamp\0" // IR(52041, 7)
  "SClamp\0" // IR(52048, 7)
  "FMix\0" // IR(52055, 5)
  "IMix\0" // IR(52060, 5)
  "Step\0" // IR(52065, 5)
  "SmoothStep\0" // IR(52070, 11)
  "Fma\0" // IR(52081, 4)
  "Frexp\0" // IR(52085, 6)
  "FrexpStruct\0" // IR(52091, 12)
  "Ldexp\0" // IR(52103, 6)
  "PackSnorm4x8\0" // IR(52109, 13)
  "PackUnorm4x8\0" // IR(52122, 13)
  "PackSnorm2x16\0" // IR(52135, 14)
  "PackUnorm2x16\0" // IR(52149, 14)
  "PackHalf2x16\0" // IR(52163, 13)
  "PackDouble2x32\0" // IR(52176, 15)
  "UnpackSnorm2x16\0" // IR(52191, 16)
  "UnpackUnorm2x16\0" // IR(52207, 16)
  "UnpackHalf2x16\0" // IR(52223, 15)
  "UnpackSnorm4x8\0" // IR(52238, 15)
  "UnpackUnorm4x8\0" // IR(52253, 15)
  "UnpackDouble2x32\0" // IR(52268, 17)
  "Length\0" // IR(52285, 7)
  "Distance\0" // IR(52292, 9)
  "Cross\0" // IR(52301, 6)
  "Normalize\0" // IR(52307, 10)
  "FaceForward\0" // IR(52317, 12)
  "Reflect\0" // IR(52329, 8)
  "Refract\0" // IR(52337, 8)
  "FindILsb\0" // IR(52345, 9)
  "FindSMsb\0" // IR(52354, 9)
  "FindUMsb\0" // IR(52363, 9)
  "InterpolateAtCentroid\0" // IR(52372, 22)
  "InterpolateAtSample\0" // IR(52394, 20)
  "InterpolateAtOffset\0" // IR(52414, 20)
  "NMin\0" // IR(52434, 5)
  "NMax\0" // IR(52439, 5)
  "NClamp\0" // IR(52444, 7)
  "ArgumentInfo\0" // IR(52451, 13)
  "ArgumentStorageBuffer\0" // IR(52464, 22)
  "ArgumentUniform\0" // IR(52486, 16)
  "ArgumentPodStorageBuffer\0" // IR(52502, 25)
  "ArgumentPodUniform\0" // IR(52527, 19)
  "ArgumentPodPushConstant\0" // IR(52546, 24)
  "ArgumentSampledImage\0" // IR(52570, 21)
  "ArgumentStorageImage\0" // IR(52591, 21)
  "ArgumentSampler\0" // IR(52612, 16)
  "ArgumentWorkgroup\0" // IR(52628, 18)
  "SpecConstantWorkgroupSize\0" // IR(52646, 26)
  "SpecConstantGlobalOffset\0" // IR(52672, 25)
  "SpecConstantWorkDim\0" // IR(52697, 20)
  "PushConstantGlobalOffset\0" // IR(52717, 25)
  "PushConstantEnqueuedLocalSize\0" // IR(52742, 30)
  "PushConstantGlobalSize\0" // IR(52772, 23)
  "PushConstantRegionOffset\0" // IR(52795, 25)
  "PushConstantNumWorkgroups\0" // IR(52820, 26)
  "PushConstantRegionGroupOffset\0" // IR(52846, 30)
  "ConstantDataStorageBuffer\0" // IR(52876, 26)
  "ConstantDataUniform\0" // IR(52902, 20)
  "PropertyRequiredWorkgroupSize\0" // IR(52922, 30)
  "SpecConstantSubgroupMaxSize\0" // IR(52952, 28)
  "ArgumentPointerPushConstant\0" // IR(52980, 28)
  "ArgumentPointerUniform\0" // IR(53008, 23)
  "ProgramScopeVariablesStorageBuffer\0" // IR(53031, 35)
  "ProgramScopeVariablePointerRelocation\0" // IR(53066, 38)
  "ImageArgumentInfoChannelOrderPushConstant\0" // IR(53104, 42)
  "ImageArgumentInfoChannelDataTypePushConstant\0" // IR(53146, 45)
  "ImageArgumentInfoChannelOrderUniform\0" // IR(53191, 37)
  "ImageArgumentInfoChannelDataTypeUniform\0" // IR(53228, 40)
  "ArgumentStorageTexelBuffer\0" // IR(53268, 27)
  "ArgumentUniformTexelBuffer\0" // IR(53295, 27)
  "ConstantDataPointerPushConstant\0" // IR(53322, 32)
  "ProgramScopeVariablePointerPushConstant\0" // IR(53354, 40)
  "PrintfInfo\0" // IR(53394, 11)
  "PrintfBufferStorageBuffer\0" // IR(53405, 26)
  "PrintfBufferPointerPushConstant\0" // IR(53431, 32)
  "NormalizedSamplerMaskPushConstant\0" // IR(53463, 34)
  "WorkgroupVariableSize\0" // IR(53497, 22)
  "DebugImportedEntity\0" // IR(53519, 20)
  "DebugSource\0" // IR(53539, 12)
  "DebugFunctionDefinition\0" // IR(53551, 24)
  "DebugSourceContinued\0" // IR(53575, 21)
  "DebugLine\0" // IR(53596, 10)
  "DebugNoLine\0" // IR(53606, 12)
  "DebugBuildIdentifier\0" // IR(53618, 21)
  "DebugStoragePath\0" // IR(53639, 17)
  "DebugEntryPoint\0" // IR(53656, 16)
  "DebugTypeMatrix\0" // IR(53672, 16)
  "Configuration\0" // IR(53688, 14)
  "StartCounter\0" // IR(53702, 13)
  "StopCounter\0" // IR(53715, 12)
  "PushConstants\0" // IR(53727, 14)
  "SpecializationMapEntry\0" // IR(53741, 23)
  "DescriptorSetBuffer\0" // IR(53764, 20)
  "DescriptorSetImage\0" // IR(53784, 19)
  "DescriptorSetSampler\0" // IR(53803, 21)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING\0" // IR(53824, 63)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS\0" // IR(53887, 45)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER\0" // IR(53932, 49)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE\0" // IR(53981, 49)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION\0" // IR(54030, 44)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY\0" // IR(54074, 50)
  "DebugModuleINTEL\0" // IR(54124, 17)
  "acos\0" // IR(54141, 5)
  "acosh\0" // IR(54146, 6)
  "acospi\0" // IR(54152, 7)
  "asin\0" // IR(54159, 5)
  "asinh\0" // IR(54164, 6)
  "asinpi\0" // IR(54170, 7)
  "atan\0" // IR(54177, 5)
  "atan2\0" // IR(54182, 6)
  "atanh\0" // IR(54188, 6)
  "atanpi\0" // IR(54194, 7)
  "atan2pi\0" // IR(54201, 8)
  "cbrt\0" // IR(54209, 5)
  "ceil\0" // IR(54214, 5)
  "copysign\0" // IR(54219, 9)
  "cos\0" // IR(54228, 4)
  "cosh\0" // IR(54232, 5)
  "cospi\0" // IR(54237, 6)
  "erfc\0" // IR(54243, 5)
  "erf\0" // IR(54248, 4)
  "exp\0" // IR(54252, 4)
  "exp2\0" // IR(54256, 5)
  "exp10\0" // IR(54261, 6)
  "expm1\0" // IR(54267, 6)
  "fabs\0" // IR(54273, 5)
  "fdim\0" // IR(54278, 5)
  "floor\0" // IR(54283, 6)
  "fma\0" // IR(54289, 4)
  "fmax\0" // IR(54293, 5)
  "fmin\0" // IR(54298, 5)
  "fmod\0" // IR(54303, 5)
  "fract\0" // IR(54308, 6)
  "frexp\0" // IR(54314, 6)
  "hypot\0" // IR(54320, 6)
  "ilogb\0" // IR(54326, 6)
  "ldexp\0" // IR(54332, 6)
  "lgamma\0" // IR(54338, 7)
  "lgamma_r\0" // IR(54345, 9)
  "log\0" // IR(54354, 4)
  "log2\0" // IR(54358, 5)
  "log10\0" // IR(54363, 6)
  "log1p\0" // IR(54369, 6)
  "logb\0" // IR(54375, 5)
  "mad\0" // IR(54380, 4)
  "maxmag\0" // IR(54384, 7)
  "minmag\0" // IR(54391, 7)
  "modf\0" // IR(54398, 5)
  "nan\0" // IR(54403, 4)
  "nextafter\0" // IR(54407, 10)
  "pow\0" // IR(54417, 4)
  "pown\0" // IR(54421, 5)
  "powr\0" // IR(54426, 5)
  "remainder\0" // IR(54431, 10)
  "remquo\0" // IR(54441, 7)
  "rint\0" // IR(54448, 5)
  "rootn\0" // IR(54453, 6)
  "round\0" // IR(54459, 6)
  "rsqrt\0" // IR(54465, 6)
  "sin\0" // IR(54471, 4)
  "sincos\0" // IR(54475, 7)
  "sinh\0" // IR(54482, 5)
  "sinpi\0" // IR(54487, 6)
  "sqrt\0" // IR(54493, 5)
  "tan\0" // IR(54498, 4)
  "tanh\0" // IR(54502, 5)
  "tanpi\0" // IR(54507, 6)
  "tgamma\0" // IR(54513, 7)
  "trunc\0" // IR(54520, 6)
  "half_cos\0" // IR(54526, 9)
  "half_divide\0" // IR(54535, 12)
  "half_exp\0" // IR(54547, 9)
  "half_exp2\0" // IR(54556, 10)
  "half_exp10\0" // IR(54566, 11)
  "half_log\0" // IR(54577, 9)
  "half_log2\0" // IR(54586, 10)
  "half_log10\0" // IR(54596, 11)
  "half_powr\0" // IR(54607, 10)
  "half_recip\0" // IR(54617, 11)
  "half_rsqrt\0" // IR(54628, 11)
  "half_sin\0" // IR(54639, 9)
  "half_sqrt\0" // IR(54648, 10)
  "half_tan\0" // IR(54658, 9)
  "native_cos\0" // IR(54667, 11)
  "native_divide\0" // IR(54678, 14)
  "native_exp\0" // IR(54692, 11)
  "native_exp2\0" // IR(54703, 12)
  "native_exp10\0" // IR(54715, 13)
  "native_log\0" // IR(54728, 11)
  "native_log2\0" // IR(54739, 12)
  "native_log10\0" // IR(54751, 13)
  "native_powr\0" // IR(54764, 12)
  "native_recip\0" // IR(54776, 13)
  "native_rsqrt\0" // IR(54789, 13)
  "native_sin\0" // IR(54802, 11)
  "native_sqrt\0" // IR(54813, 12)
  "native_tan\0" // IR(54825, 11)
  "fclamp\0" // IR(54836, 7)
  "degrees\0" // IR(54843, 8)
  "fmax_common\0" // IR(54851, 12)
  "fmin_common\0" // IR(54863, 12)
  "mix\0" // IR(54875, 4)
  "radians\0" // IR(54879, 8)
  "step\0" // IR(54887, 5)
  "smoothstep\0" // IR(54892, 11)
  "sign\0" // IR(54903, 5)
  "cross\0" // IR(54908, 6)
  "distance\0" // IR(54914, 9)
  "length\0" // IR(54923, 7)
  "normalize\0" // IR(54930, 10)
  "fast_distance\0" // IR(54940, 14)
  "fast_length\0" // IR(54954, 12)
  "fast_normalize\0" // IR(54966, 15)
  "s_abs\0" // IR(54981, 6)
  "s_abs_diff\0" // IR(54987, 11)
  "s_add_sat\0" // IR(54998, 10)
  "u_add_sat\0" // IR(55008, 10)
  "s_hadd\0" // IR(55018, 7)
  "u_hadd\0" // IR(55025, 7)
  "s_rhadd\0" // IR(55032, 8)
  "u_rhadd\0" // IR(55040, 8)
  "s_clamp\0" // IR(55048, 8)
  "u_clamp\0" // IR(55056, 8)
  "clz\0" // IR(55064, 4)
  "ctz\0" // IR(55068, 4)
  "s_mad_hi\0" // IR(55072, 9)
  "u_mad_sat\0" // IR(55081, 10)
  "s_mad_sat\0" // IR(55091, 10)
  "s_max\0" // IR(55101, 6)
  "u_max\0" // IR(55107, 6)
  "s_min\0" // IR(55113, 6)
  "u_min\0" // IR(55119, 6)
  "s_mul_hi\0" // IR(55125, 9)
  "rotate\0" // IR(55134, 7)
  "s_sub_sat\0" // IR(55141, 10)
  "u_sub_sat\0" // IR(55151, 10)
  "u_upsample\0" // IR(55161, 11)
  "s_upsample\0" // IR(55172, 11)
  "popcount\0" // IR(55183, 9)
  "s_mad24\0" // IR(55192, 8)
  "u_mad24\0" // IR(55200, 8)
  "s_mul24\0" // IR(55208, 8)
  "u_mul24\0" // IR(55216, 8)
  "vloadn\0" // IR(55224, 7)
  "vstoren\0" // IR(55231, 8)
  "vload_half\0" // IR(55239, 11)
  "vload_halfn\0" // IR(55250, 12)
  "vstore_half\0" // IR(55262, 12)
  "vstore_half_r\0" // IR(55274, 14)
  "vstore_halfn\0" // IR(55288, 13)
  "vstore_halfn_r\0" // IR(55301, 15)
  "vloada_halfn\0" // IR(55316, 13)
  "vstorea_halfn\0" // IR(55329, 14)
  "vstorea_halfn_r\0" // IR(55343, 16)
  "shuffle\0" // IR(55359, 8)
  "shuffle2\0" // IR(55367, 9)
  "printf\0" // IR(55376, 7)
  "prefetch\0" // IR(55383, 9)
  "bitselect\0" // IR(55392, 10)
  "select\0" // IR(55402, 7)
  "u_abs\0" // IR(55409, 6)
  "u_abs_diff\0" // IR(55415, 11)
  "u_mul_hi\0" // IR(55426, 9)
  "u_mad_hi\0" // IR(55435, 9)
  "CubeFaceIndexAMD\0" // IR(55444, 17)
  "CubeFaceCoordAMD\0" // IR(55461, 17)
  "TimeAMD\0" // IR(55478, 8)
  "SwizzleInvocationsAMD\0" // IR(55486, 22)
  "SwizzleInvocationsMaskedAMD\0" // IR(55508, 28)
  "WriteInvocationAMD\0" // IR(55536, 19)
  "MbcntAMD\0" // IR(55555, 9)
  "InterpolateAtVertexAMD\0" // IR(55564, 23)
  "FMin3AMD\0" // IR(55587, 9)
  "UMin3AMD\0" // IR(55596, 9)
  "SMin3AMD\0" // IR(55605, 9)
  "FMax3AMD\0" // IR(55614, 9)
  "UMax3AMD\0" // IR(55623, 9)
  "SMax3AMD\0" // IR(55632, 9)
  "FMid3AMD\0" // IR(55641, 9)
  "UMid3AMD\0" // IR(55650, 9)
  "SMid3AMD\0" // IR(55659, 9)
;

// Array of IndexRanges, where each represents a string by referencing
// the kStrings table.
// This array contains all sequences of alias strings used in the grammar.
// This table is referenced by an IndexRange elsewhere, i.e. by the 'aliases'
// field of an instruction or operand description.
static const IndexRange kAliasSpans[] = {
  IR(5646, 27), // 0 PhysicalStorageBuffer64EXT
  IR(6557, 18), // 1 SubgroupEqMaskKHR
  IR(6612, 18), // 2 SubgroupGeMaskKHR
  IR(6645, 18), // 3 SubgroupGtMaskKHR
  IR(6678, 18), // 4 SubgroupLeMaskKHR
  IR(6711, 18), // 5 SubgroupLtMaskKHR
  IR(7618, 12), // 6 BaryCoordNV
  IR(7673, 19), // 7 BaryCoordNoPerspNV
  IR(7704, 15), // 8 FragmentSizeNV
  IR(7761, 22), // 9 InvocationsPerPixelNV
  IR(7889, 11), // 10 LaunchIdNV
  IR(7914, 13), // 11 LaunchSizeNV
  IR(7945, 17), // 12 WorldRayOriginNV
  IR(7983, 20), // 13 WorldRayDirectionNV
  IR(8022, 18), // 14 ObjectRayOriginNV
  IR(8062, 21), // 15 ObjectRayDirectionNV
  IR(8094, 10), // 16 RayTminNV
  IR(8115, 10), // 17 RayTmaxNV
  IR(8148, 22), // 18 InstanceCustomIndexNV
  IR(8187, 16), // 19 ObjectToWorldNV
  IR(8220, 16), // 20 WorldToObjectNV
  IR(8254, 10), // 21 HitKindNV
  IR(8485, 19), // 22 IncomingRayFlagsNV
  IR(10261, 28), // 23 StorageUniformBufferBlock16
  IR(10324, 17), // 24 StorageUniform16
  IR(11180, 27), // 25 ShaderViewportIndexLayerNV
  IR(11224, 22), // 26 FragmentBarycentricNV
  IR(11277, 30), // 27 ComputeDerivativeGroupQuadsNV
  IR(11307, 14), // 28 ShadingRateNV
  IR(11351, 29), // 29 GroupNonUniformPartitionedNV
  IR(11397, 20), // 30 ShaderNonUniformEXT
  IR(11440, 26), // 31 RuntimeDescriptorArrayEXT
  IR(11502, 39), // 32 InputAttachmentArrayDynamicIndexingEXT
  IR(11580, 42), // 33 UniformTexelBufferArrayDynamicIndexingEXT
  IR(11661, 42), // 34 StorageTexelBufferArrayDynamicIndexingEXT
  IR(11740, 40), // 35 UniformBufferArrayNonUniformIndexingEXT
  IR(11816, 39), // 36 SampledImageArrayNonUniformIndexingEXT
  IR(11892, 40), // 37 StorageBufferArrayNonUniformIndexingEXT
  IR(11968, 39), // 38 StorageImageArrayNonUniformIndexingEXT
  IR(12046, 42), // 39 InputAttachmentArrayNonUniformIndexingEXT
  IR(12130, 45), // 40 UniformTexelBufferArrayNonUniformIndexingEXT
  IR(12217, 45), // 41 StorageTexelBufferArrayNonUniformIndexingEXT
  IR(12280, 21), // 42 VulkanMemoryModelKHR
  IR(12330, 32), // 43 VulkanMemoryModelDeviceScopeKHR
  IR(12362, 34), // 44 PhysicalStorageBufferAddressesEXT
  IR(12428, 31), // 45 ComputeDerivativeGroupLinearNV
  IR(12632, 28), // 46 DemoteToHelperInvocationEXT
  IR(13673, 26), // 47 FPGAMemoryAttributesINTEL
  IR(13752, 32), // 48 ArbitraryPrecisionIntegersINTEL
  IR(13822, 37), // 49 ArbitraryPrecisionFloatingPointINTEL
  IR(13912, 22), // 50 FPGALoopControlsINTEL
  IR(14007, 24), // 51 FPGAMemoryAccessesINTEL
  IR(14059, 27), // 52 FPGAClusterAttributesINTEL
  IR(14101, 14), // 53 LoopFuseINTEL
  IR(14136, 20), // 54 FPGADSPControlINTEL
  IR(14223, 40), // 55 FPGAInvocationPipeliningAttributesINTEL
  IR(14288, 24), // 56 FPGABufferLocationINTEL
  IR(14347, 34), // 57 ArbitraryPrecisionFixedPointINTEL
  IR(14405, 23), // 58 USMStorageClassesINTEL
  IR(14458, 29), // 59 RuntimeAlignedAttributeINTEL
  IR(14501, 13), // 60 IOPipesINTEL
  IR(14534, 19), // 61 BlockingPipesINTEL
  IR(14567, 13), // 62 FPGARegINTEL
  IR(14599, 22), // 63 DotProductInputAllKHR
  IR(14643, 25), // 64 DotProductInput4x8BitKHR
  IR(14696, 31), // 65 DotProductInput4x8BitPackedKHR
  IR(14738, 14), // 66 DotProductKHR
  IR(14910, 13), // 67 OptNoneINTEL
  IR(15055, 29), // 68 FPGAClusterAttributesV2INTEL
  IR(15131, 18), // 69 TaskSequenceINTEL
  IR(15190, 24), // 70 FPGALatencyControlINTEL
  IR(15243, 28), // 71 FPGAArgumentInterfacesINTEL
  IR(15337, 35), // 72 GlobalVariableFPGADecorationsINTEL
  IR(18288, 15), // 73 PerPrimitiveNV
  IR(18336, 12), // 74 PerVertexNV
  IR(18359, 14), // 75 NonUniformEXT
  IR(18389, 19), // 76 RestrictPointerEXT
  IR(18423, 18), // 77 AliasedPointerEXT
  IR(18786, 24), // 78 HlslCounterBufferGOOGLE
  IR(18823, 19), // 79 HlslSemanticGOOGLE
  IR(18953, 14), // 80 RegisterINTEL
  IR(18980, 12), // 81 MemoryINTEL
  IR(19007, 14), // 82 NumbanksINTEL
  IR(19037, 15), // 83 BankwidthINTEL
  IR(19075, 22), // 84 MaxPrivateCopiesINTEL
  IR(19114, 16), // 85 SinglepumpINTEL
  IR(19147, 16), // 86 DoublepumpINTEL
  IR(19183, 19), // 87 MaxReplicatesINTEL
  IR(19223, 20), // 88 SimpleDualPortINTEL
  IR(19255, 11), // 89 MergeINTEL
  IR(19323, 14), // 90 BankBitsINTEL
  IR(19358, 20), // 91 ForcePow2DepthINTEL
  IR(19395, 16), // 92 StridesizeINTEL
  IR(19426, 14), // 93 WordsizeINTEL
  IR(19459, 18), // 94 TrueDualPortINTEL
  IR(19497, 19), // 95 BurstCoalesceINTEL
  IR(19532, 15), // 96 CacheSizeINTEL
  IR(19576, 28), // 97 DontStaticallyCoalesceINTEL
  IR(19619, 14), // 98 PrefetchINTEL
  IR(19651, 17), // 99 StallEnableINTEL
  IR(19694, 25), // 100 FuseLoopsInFunctionINTEL
  IR(19739, 19), // 101 MathOpDSPModeINTEL
  IR(19812, 24), // 102 InitiationIntervalINTEL
  IR(19857, 20), // 103 MaxConcurrencyINTEL
  IR(19898, 20), // 104 PipelineEnableINTEL
  IR(19939, 20), // 105 BufferLocationINTEL
  IR(19979, 19), // 106 IOPipeStorageINTEL
  IR(20157, 15), // 107 StallFreeINTEL
  IR(20255, 25), // 108 LatencyControlLabelINTEL
  IR(20311, 30), // 109 LatencyControlConstraintINTEL
  IR(20369, 27), // 110 ConduitKernelArgumentINTEL
  IR(20428, 31), // 111 RegisterMapKernelArgumentINTEL
  IR(20493, 33), // 112 MMHostInterfaceAddressWidthINTEL
  IR(20557, 30), // 113 MMHostInterfaceDataWidthINTEL
  IR(20616, 28), // 114 MMHostInterfaceLatencyINTEL
  IR(20713, 34), // 115 MMHostInterfaceReadWriteModeINTEL
  IR(20777, 29), // 116 MMHostInterfaceMaxBurstINTEL
  IR(20839, 32), // 117 MMHostInterfaceWaitRequestINTEL
  IR(20898, 26), // 118 StableKernelArgumentINTEL
  IR(21041, 14), // 119 InitModeINTEL
  IR(21084, 28), // 120 ImplementInRegisterMapINTEL
  IR(22438, 14), // 121 OutputLinesNV
  IR(22472, 19), // 122 OutputPrimitivesNV
  IR(22515, 23), // 123 DerivativeGroupQuadsNV
  IR(22563, 24), // 124 DerivativeGroupLinearNV
  IR(22606, 18), // 125 OutputTrianglesNV
  IR(23354, 16), // 126 RayGenerationNV
  IR(23386, 15), // 127 IntersectionNV
  IR(23411, 9), // 128 AnyHitNV
  IR(23434, 13), // 129 ClosestHitNV
  IR(23455, 7), // 130 MissNV
  IR(23474, 11), // 131 CallableNV
  IR(23619, 23), // 132 AllowContractFastINTEL
  IR(23655, 18), // 133 AllowReassocINTEL
  IR(23881, 20), // 134 RuntimeAlignedINTEL
  IR(23973, 20), // 135 PartitionedReduceNV
  IR(24021, 27), // 136 PartitionedInclusiveScanNV
  IR(24076, 27), // 137 PartitionedExclusiveScanNV
  IR(24207, 22), // 138 MakeTexelAvailableKHR
  IR(24246, 20), // 139 MakeTexelVisibleKHR
  IR(24282, 19), // 140 NonPrivateTexelKHR
  IR(24315, 17), // 141 VolatileTexelKHR
  IR(24874, 27), // 142 InitOnDeviceReprogramINTEL
  IR(24925, 23), // 143 InitOnDeviceResetINTEL
  IR(25259, 21), // 144 DependencyArrayINTEL
  IR(25299, 18), // 145 LoopCoalesceINTEL
  IR(25339, 21), // 146 MaxInterleavingINTEL
  IR(25387, 26), // 147 SpeculatedIterationsINTEL
  IR(25428, 14), // 148 NoFusionINTEL
  IR(25458, 15), // 149 LoopCountINTEL
  IR(25500, 26), // 150 MaxReinvocationDelayINTEL
  IR(25892, 24), // 151 MakePointerAvailableKHR
  IR(25935, 22), // 152 MakePointerVisibleKHR
  IR(25975, 21), // 153 NonPrivatePointerKHR
  IR(26062, 10), // 154 VulkanKHR
  IR(16017, 5), // 155 None
  IR(26245, 16), // 156 OutputMemoryKHR
  IR(26275, 17), // 157 MakeAvailableKHR
  IR(26304, 15), // 158 MakeVisibleKHR
  IR(26380, 28), // 159 PackedVectorFormat4x8BitKHR
  IR(26695, 24), // 160 SkipBuiltinPrimitivesNV
  IR(27435, 15), // 161 QueueFamilyKHR
  IR(27806, 15), // 162 CallableDataNV
  IR(27845, 23), // 163 IncomingCallableDataNV
  IR(27882, 13), // 164 RayPayloadNV
  IR(27911, 15), // 165 HitAttributeNV
  IR(27948, 21), // 166 IncomingRayPayloadNV
  IR(27991, 21), // 167 ShaderRecordBufferNV
  IR(28034, 25), // 168 PhysicalStorageBufferEXT
  IR(28160, 16), // 169 DeviceOnlyINTEL
  IR(28191, 14), // 170 HostOnlyINTEL
  IR(35429, 8), // 171 SDotKHR
  IR(35442, 8), // 172 UDotKHR
  IR(35456, 9), // 173 SUDotKHR
  IR(35476, 14), // 174 SDotAccSatKHR
  IR(35501, 14), // 175 UDotAccSatKHR
  IR(35527, 15), // 176 SUDotAccSatKHR
  IR(37828, 24), // 177 TypeCooperativeVectorNV
  IR(38084, 27), // 178 GroupNonUniformPartitionNV
  IR(39166, 21), // 179 ReportIntersectionNV
  IR(39341, 28), // 180 TypeAccelerationStructureNV
  IR(39422, 23), // 181 RayQueryGetClusterIdNV
  IR(41590, 21), // 182 DecorateStringGOOGLE
  IR(41632, 27), // 183 MemberDecorateStringGOOGLE
  IR(46889, 28), // 184 ArbitraryFloatSinCosPiINTEL
  IR(46942, 24), // 185 ArbitraryFloatCastINTEL
  IR(46998, 31), // 186 ArbitraryFloatCastFromIntINTEL
  IR(47059, 29), // 187 ArbitraryFloatCastToIntINTEL
  IR(47112, 23), // 188 ArbitraryFloatAddINTEL
  IR(47159, 23), // 189 ArbitraryFloatSubINTEL
  IR(47206, 23), // 190 ArbitraryFloatMulINTEL
  IR(47253, 23), // 191 ArbitraryFloatDivINTEL
  IR(47299, 22), // 192 ArbitraryFloatGTINTEL
  IR(47344, 22), // 193 ArbitraryFloatGEINTEL
  IR(47389, 22), // 194 ArbitraryFloatLTINTEL
  IR(47434, 22), // 195 ArbitraryFloatLEINTEL
  IR(47479, 22), // 196 ArbitraryFloatEQINTEL
  IR(47527, 25), // 197 ArbitraryFloatRecipINTEL
  IR(47578, 25), // 198 ArbitraryFloatRSqrtINTEL
  IR(47628, 24), // 199 ArbitraryFloatCbrtINTEL
  IR(47678, 25), // 200 ArbitraryFloatHypotINTEL
  IR(47728, 24), // 201 ArbitraryFloatSqrtINTEL
  IR(48412, 15), // 202 FixedSqrtINTEL
  IR(48444, 16), // 203 FixedRecipINTEL
  IR(48477, 16), // 204 FixedRsqrtINTEL
  IR(48508, 14), // 205 FixedSinINTEL
  IR(48537, 14), // 206 FixedCosINTEL
  IR(48569, 17), // 207 FixedSinCosINTEL
  IR(48603, 16), // 208 FixedSinPiINTEL
  IR(48636, 16), // 209 FixedCosPiINTEL
  IR(48672, 19), // 210 FixedSinCosPiINTEL
  IR(48706, 14), // 211 FixedLogINTEL
  IR(48735, 14), // 212 FixedExpINTEL
  IR(48779, 29), // 213 PtrCastToCrossWorkgroupINTEL
  IR(48838, 29), // 214 CrossWorkgroupCastToPtrINTEL
  IR(48890, 22), // 215 ReadPipeBlockingINTEL
  IR(48936, 23), // 216 WritePipeBlockingINTEL
  IR(49888, 24), // 217 TaskSequenceCreateINTEL
  IR(49936, 23), // 218 TaskSequenceAsyncINTEL
  IR(49981, 21), // 219 TaskSequenceGetINTEL
  IR(50028, 25), // 220 TaskSequenceReleaseINTEL
  IR(50076, 22), // 221 TypeTaskSequenceINTEL
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
  spv::Capability::ConstantDataKHR, // 126
  spv::Capability::SampleMaskOverrideCoverageNV, // 127
  spv::Capability::GeometryShaderPassthroughNV, // 128
  spv::Capability::MeshShadingNV, // 129
  spv::Capability::MeshShadingEXT, // 130
  spv::Capability::PushConstantBanksNV, // 131
  spv::Capability::ShaderInvocationReorderNV, // 132
  spv::Capability::ShaderInvocationReorderEXT, // 133
  spv::Capability::BindlessTextureNV, // 134
  spv::Capability::VectorComputeINTEL, // 135
  spv::Capability::IndirectReferencesINTEL, // 136
  spv::Capability::AsmINTEL, // 137
  spv::Capability::FunctionFloatControlINTEL, // 138
  spv::Capability::FPGAMemoryAttributesALTERA, // 139
  spv::Capability::FPGAMemoryAccessesALTERA, // 140
  spv::Capability::LoopFuseALTERA, // 141
  spv::Capability::FPGADSPControlALTERA, // 142
  spv::Capability::MemoryAccessAliasingINTEL, // 143
  spv::Capability::FPGAInvocationPipeliningAttributesALTERA, // 144
  spv::Capability::FPGABufferLocationALTERA, // 145
  spv::Capability::IOPipesALTERA, // 146
  spv::Capability::FPGAClusterAttributesV2ALTERA, // 147
  spv::Capability::FPMaxErrorINTEL, // 148
  spv::Capability::FPGALatencyControlALTERA, // 149
  spv::Capability::FPGAArgumentInterfacesALTERA, // 150
  spv::Capability::GlobalVariableHostAccessINTEL, // 151
  spv::Capability::GlobalVariableFPGADecorationsALTERA, // 152
  spv::Capability::CacheControlsINTEL, // 153
  spv::Capability::TileImageColorReadAccessEXT, // 154
  spv::Capability::Geometry, // 155
  spv::Capability::Tessellation, // 156
  spv::Capability::MeshShadingNV, // 157
  spv::Capability::MeshShadingEXT, // 158
  spv::Capability::Geometry, // 159
  spv::Capability::MeshShadingNV, // 160
  spv::Capability::MeshShadingEXT, // 161
  spv::Capability::SubgroupDispatch, // 162
  spv::Capability::TileImageDepthReadAccessEXT, // 163
  spv::Capability::TileImageStencilReadAccessEXT, // 164
  spv::Capability::SampleMaskPostDepthCoverage, // 165
  spv::Capability::DenormPreserve, // 166
  spv::Capability::DenormFlushToZero, // 167
  spv::Capability::SignedZeroInfNanPreserve, // 168
  spv::Capability::RoundingModeRTE, // 169
  spv::Capability::RoundingModeRTZ, // 170
  spv::Capability::QuadControlKHR, // 171
  spv::Capability::PoisonFreezeKHR, // 172
  spv::Capability::ComputeDerivativeGroupQuadsKHR, // 173
  spv::Capability::ComputeDerivativeGroupLinearKHR, // 174
  spv::Capability::FragmentShaderPixelInterlockEXT, // 175
  spv::Capability::FragmentShaderSampleInterlockEXT, // 176
  spv::Capability::FragmentShaderShadingRateInterlockEXT, // 177
  spv::Capability::Shader64BitIndexingEXT, // 178
  spv::Capability::RoundToInfinityINTEL, // 179
  spv::Capability::KernelAttributesINTEL, // 180
  spv::Capability::FloatControls2, // 181
  spv::Capability::FPGAKernelAttributesv2INTEL, // 182
  spv::Capability::RegisterLimitsINTEL, // 183
  spv::Capability::FloatControls2, // 184
  spv::Capability::FPFastMathModeINTEL, // 185
  spv::Capability::OptNoneEXT, // 186
  spv::Capability::RuntimeAlignedAttributeALTERA, // 187
  spv::Capability::Kernel, // 188
  spv::Capability::GroupNonUniformArithmetic, // 189
  spv::Capability::GroupNonUniformBallot, // 190
  spv::Capability::GroupNonUniformClustered, // 191
  spv::Capability::GroupNonUniformPartitionedEXT, // 192
  spv::Capability::ImageGatherExtended, // 193
  spv::Capability::MinLod, // 194
  spv::Capability::VulkanMemoryModel, // 195
  spv::Capability::FPGALoopControlsALTERA, // 196
  spv::Capability::ArbitraryPrecisionFixedPointALTERA, // 197
  spv::Capability::RawAccessChainsNV, // 198
  spv::Capability::RayTraversalPrimitiveCullingKHR, // 199
  spv::Capability::RayTracingOpacityMicromapEXT, // 200
  spv::Capability::RayQueryKHR, // 201
  spv::Capability::StorageImageExtendedFormats, // 202
  spv::Capability::Int64ImageEXT, // 203
  spv::Capability::Shader, // 204
  spv::Capability::VectorComputeINTEL, // 205
  spv::Capability::GenericPointer, // 206
  spv::Capability::FunctionPointersINTEL, // 207
  spv::Capability::USMStorageClassesALTERA, // 208
  spv::Capability::CooperativeMatrixTensorAddressingNV, // 209
  spv::Capability::CooperativeMatrixBlockLoadsNV, // 210
  spv::Capability::TensorsARM, // 211
  spv::Capability::Addresses, // 212
  spv::Capability::PhysicalStorageBufferAddresses, // 213
  spv::Capability::LiteralSampler, // 214
  spv::Capability::Addresses, // 215
  spv::Capability::UntypedPointersKHR, // 216
  spv::Capability::Addresses, // 217
  spv::Capability::VariablePointers, // 218
  spv::Capability::VariablePointersStorageBuffer, // 219
  spv::Capability::PhysicalStorageBufferAddresses, // 220
  spv::Capability::Kernel, // 221
  spv::Capability::ImageQuery, // 222
  spv::Capability::ImageQuery, // 223
  spv::Capability::Shader, // 224
  spv::Capability::BitInstructions, // 225
  spv::Capability::DerivativeControl, // 226
  spv::Capability::Groups, // 227
  spv::Capability::SparseResidency, // 228
  spv::Capability::PipeStorage, // 229
  spv::Capability::NamedBarrier, // 230
  spv::Capability::GroupNonUniformVote, // 231
  spv::Capability::GroupNonUniformBallot, // 232
  spv::Capability::GroupNonUniformShuffle, // 233
  spv::Capability::GroupNonUniformShuffleRelative, // 234
  spv::Capability::GroupNonUniformArithmetic, // 235
  spv::Capability::GroupNonUniformClustered, // 236
  spv::Capability::GroupNonUniformPartitionedEXT, // 237
  spv::Capability::GroupNonUniformQuad, // 238
  spv::Capability::Addresses, // 239
  spv::Capability::VariablePointers, // 240
  spv::Capability::VariablePointersStorageBuffer, // 241
  spv::Capability::GraphARM, // 242
  spv::Capability::SubgroupBallotKHR, // 243
  spv::Capability::FMAKHR, // 244
  spv::Capability::SubgroupVoteKHR, // 245
  spv::Capability::GroupNonUniformRotateKHR, // 246
  spv::Capability::RayTracingKHR, // 247
  spv::Capability::RayQueryKHR, // 248
  spv::Capability::DotProduct, // 249
  spv::Capability::ReplicatedCompositesEXT, // 250
  spv::Capability::TextureSampleWeightedQCOM, // 251
  spv::Capability::TextureBoxFilterQCOM, // 252
  spv::Capability::TextureBlockMatchQCOM, // 253
  spv::Capability::CooperativeMatrixConversionQCOM, // 254
  spv::Capability::TextureBlockMatch2QCOM, // 255
  spv::Capability::FragmentMaskAMD, // 256
  spv::Capability::ShaderClockKHR, // 257
  spv::Capability::AbortKHR, // 258
  spv::Capability::ShaderInvocationReorderNV, // 259
  spv::Capability::RayTracingMotionBlurNV, // 260
  spv::Capability::ImageFootprintNV, // 261
  spv::Capability::CooperativeVectorNV, // 262
  spv::Capability::LongVectorEXT, // 263
  spv::Capability::CooperativeVectorNV, // 264
  spv::Capability::CooperativeVectorTrainingNV, // 265
  spv::Capability::CooperativeMatrixConversionsNV, // 266
  spv::Capability::DisplacementMicromapNV, // 267
  spv::Capability::ShaderInvocationReorderEXT, // 268
  spv::Capability::RayTracingMotionBlurNV, // 269
  spv::Capability::RayQueryPositionFetchKHR, // 270
  spv::Capability::RayTracingNV, // 271
  spv::Capability::RayTracingKHR, // 272
  spv::Capability::RayQueryKHR, // 273
  spv::Capability::DisplacementMicromapNV, // 274
  spv::Capability::CooperativeMatrixNV, // 275
  spv::Capability::FragmentShaderSampleInterlockEXT, // 276
  spv::Capability::FragmentShaderPixelInterlockEXT, // 277
  spv::Capability::FragmentShaderShadingRateInterlockEXT, // 278
  spv::Capability::CooperativeMatrixReductionsNV, // 279
  spv::Capability::CooperativeMatrixPerElementOperationsNV, // 280
  spv::Capability::TensorAddressingNV, // 281
  spv::Capability::DemoteToHelperInvocation, // 282
  spv::Capability::SubgroupShuffleINTEL, // 283
  spv::Capability::SubgroupBufferBlockIOINTEL, // 284
  spv::Capability::SubgroupImageBlockIOINTEL, // 285
  spv::Capability::SubgroupImageMediaBlockIOINTEL, // 286
  spv::Capability::IntegerFunctions2INTEL, // 287
  spv::Capability::AtomicFloat16MinMaxEXT, // 288
  spv::Capability::AtomicFloat32MinMaxEXT, // 289
  spv::Capability::AtomicFloat64MinMaxEXT, // 290
  spv::Capability::AtomicFloat16VectorNV, // 291
  spv::Capability::ExpectAssumeKHR, // 292
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 293
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 294
  spv::Capability::SubgroupAvcMotionEstimationIntraINTEL, // 295
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 296
  spv::Capability::SubgroupAvcMotionEstimationChromaINTEL, // 297
  spv::Capability::VariableLengthArrayINTEL, // 298
  spv::Capability::ArbitraryPrecisionFloatingPointALTERA, // 299
  spv::Capability::UnstructuredLoopControlsINTEL, // 300
  spv::Capability::BlockingPipesALTERA, // 301
  spv::Capability::FPGARegALTERA, // 302
  spv::Capability::AtomicFloat16AddEXT, // 303
  spv::Capability::AtomicFloat32AddEXT, // 304
  spv::Capability::AtomicFloat64AddEXT, // 305
  spv::Capability::AtomicFloat16VectorNV, // 306
  spv::Capability::LongCompositesINTEL, // 307
  spv::Capability::BFloat16ConversionINTEL, // 308
  spv::Capability::SplitBarrierINTEL, // 309
  spv::Capability::ArithmeticFenceEXT, // 310
  spv::Capability::TaskSequenceALTERA, // 311
  spv::Capability::SubgroupBufferPrefetchINTEL, // 312
  spv::Capability::Subgroup2DBlockTransformINTEL, // 313
  spv::Capability::Subgroup2DBlockTransposeINTEL, // 314
  spv::Capability::SubgroupMatrixMultiplyAccumulateINTEL, // 315
  spv::Capability::TernaryBitwiseFunctionINTEL, // 316
  spv::Capability::UntypedVariableLengthArrayINTEL, // 317
  spv::Capability::FunctionVariantsINTEL, // 318
  spv::Capability::GroupUniformArithmeticKHR, // 319
  spv::Capability::TensorFloat32RoundingINTEL, // 320
  spv::Capability::MaskedGatherScatterINTEL, // 321
  spv::Capability::BindlessImagesINTEL, // 322
  spv::Capability::DotProductFloat16AccFloat32VALVE, // 323
  spv::Capability::DotProductBFloat16AccVALVE, // 324
  spv::Capability::DotProductFloat16AccFloat16VALVE, // 325
  spv::Capability::DotProductBFloat16AccVALVE, // 326
  spv::Capability::DotProductFloat8AccFloat32VALVE, // 327
  spv::Capability::Float64, // 328
  spv::Capability::InterpolationFunction, // 329
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
  spvtools::Extension::kSPV_NV_sample_mask_override_coverage, // 70
  spvtools::Extension::kSPV_NV_geometry_shader_passthrough, // 71
  spvtools::Extension::kSPV_EXT_shader_viewport_index_layer, // 72
  spvtools::Extension::kSPV_NV_viewport_array2, // 73
  spvtools::Extension::kSPV_NV_viewport_array2, // 74
  spvtools::Extension::kSPV_NVX_multiview_per_view_attributes, // 75
  spvtools::Extension::kSPV_NV_shader_image_footprint, // 76
  spvtools::Extension::kSPV_NV_compute_shader_derivatives, // 77
  spvtools::Extension::kSPV_KHR_compute_shader_derivatives, // 78
  spvtools::Extension::kSPV_NV_shader_subgroup_partitioned, // 79
  spvtools::Extension::kSPV_EXT_shader_subgroup_partitioned, // 80
  spvtools::Extension::kSPV_EXT_descriptor_indexing, // 81
  spvtools::Extension::kSPV_KHR_ray_tracing_position_fetch, // 82
  spvtools::Extension::kSPV_KHR_vulkan_memory_model, // 83
  spvtools::Extension::kSPV_NV_cooperative_matrix, // 84
  spvtools::Extension::kSPV_EXT_fragment_shader_interlock, // 85
  spvtools::Extension::kSPV_EXT_demote_to_helper_invocation, // 86
  spvtools::Extension::kSPV_NV_displacement_micromap, // 87
  spvtools::Extension::kSPV_EXT_opacity_micromap, // 88
  spvtools::Extension::kSPV_NV_shader_invocation_reorder, // 89
  spvtools::Extension::kSPV_EXT_shader_invocation_reorder, // 90
  spvtools::Extension::kSPV_NV_bindless_texture, // 91
  spvtools::Extension::kSPV_NV_cooperative_vector, // 92
  spvtools::Extension::kSPV_NV_shader_atomic_fp16_vector, // 93
  spvtools::Extension::kSPV_NV_raw_access_chains, // 94
  spvtools::Extension::kSPV_NV_push_constant_bank, // 95
  spvtools::Extension::kSPV_EXT_long_vector, // 96
  spvtools::Extension::kSPV_EXT_shader_64bit_indexing, // 97
  spvtools::Extension::kSPV_NV_cooperative_matrix2, // 98
  spvtools::Extension::kSPV_NV_tensor_addressing, // 99
  spvtools::Extension::kSPV_INTEL_subgroups, // 100
  spvtools::Extension::kSPV_INTEL_media_block_io, // 101
  spvtools::Extension::kSPV_INTEL_float_controls2, // 102
  spvtools::Extension::kSPV_INTEL_shader_integer_functions2, // 103
  spvtools::Extension::kSPV_INTEL_function_pointers, // 104
  spvtools::Extension::kSPV_INTEL_inline_assembly, // 105
  spvtools::Extension::kSPV_EXT_shader_atomic_float_min_max, // 106
  spvtools::Extension::kSPV_INTEL_vector_compute, // 107
  spvtools::Extension::kSPV_KHR_expect_assume, // 108
  spvtools::Extension::kSPV_INTEL_device_side_avc_motion_estimation, // 109
  spvtools::Extension::kSPV_INTEL_variable_length_array, // 110
  spvtools::Extension::kSPV_ALTERA_fpga_memory_attributes, // 111
  spvtools::Extension::kSPV_INTEL_fpga_memory_attributes, // 112
  spvtools::Extension::kSPV_INTEL_fp_fast_math_mode, // 113
  spvtools::Extension::kSPV_ALTERA_arbitrary_precision_integers, // 114
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_integers, // 115
  spvtools::Extension::kSPV_ALTERA_arbitrary_precision_floating_point, // 116
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_floating_point, // 117
  spvtools::Extension::kSPV_INTEL_unstructured_loop_controls, // 118
  spvtools::Extension::kSPV_ALTERA_fpga_loop_controls, // 119
  spvtools::Extension::kSPV_INTEL_fpga_loop_controls, // 120
  spvtools::Extension::kSPV_INTEL_kernel_attributes, // 121
  spvtools::Extension::kSPV_ALTERA_fpga_memory_accesses, // 122
  spvtools::Extension::kSPV_INTEL_fpga_memory_accesses, // 123
  spvtools::Extension::kSPV_ALTERA_fpga_cluster_attributes, // 124
  spvtools::Extension::kSPV_INTEL_fpga_cluster_attributes, // 125
  spvtools::Extension::kSPV_ALTERA_loop_fuse, // 126
  spvtools::Extension::kSPV_INTEL_loop_fuse, // 127
  spvtools::Extension::kSPV_ALTERA_fpga_dsp_control, // 128
  spvtools::Extension::kSPV_INTEL_fpga_dsp_control, // 129
  spvtools::Extension::kSPV_INTEL_memory_access_aliasing, // 130
  spvtools::Extension::kSPV_ALTERA_fpga_invocation_pipelining_attributes, // 131
  spvtools::Extension::kSPV_INTEL_fpga_invocation_pipelining_attributes, // 132
  spvtools::Extension::kSPV_ALTERA_fpga_buffer_location, // 133
  spvtools::Extension::kSPV_INTEL_fpga_buffer_location, // 134
  spvtools::Extension::kSPV_ALTERA_arbitrary_precision_fixed_point, // 135
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_fixed_point, // 136
  spvtools::Extension::kSPV_ALTERA_usm_storage_classes, // 137
  spvtools::Extension::kSPV_INTEL_usm_storage_classes, // 138
  spvtools::Extension::kSPV_ALTERA_runtime_aligned, // 139
  spvtools::Extension::kSPV_INTEL_runtime_aligned, // 140
  spvtools::Extension::kSPV_ALTERA_io_pipes, // 141
  spvtools::Extension::kSPV_INTEL_io_pipes, // 142
  spvtools::Extension::kSPV_ALTERA_blocking_pipes, // 143
  spvtools::Extension::kSPV_INTEL_blocking_pipes, // 144
  spvtools::Extension::kSPV_ALTERA_fpga_reg, // 145
  spvtools::Extension::kSPV_INTEL_fpga_reg, // 146
  spvtools::Extension::kSPV_KHR_integer_dot_product, // 147
  spvtools::Extension::kSPV_KHR_cooperative_matrix, // 148
  spvtools::Extension::kSPV_EXT_replicated_composites, // 149
  spvtools::Extension::kSPV_KHR_bit_instructions, // 150
  spvtools::Extension::kSPV_KHR_subgroup_rotate, // 151
  spvtools::Extension::kSPV_KHR_float_controls2, // 152
  spvtools::Extension::kSPV_KHR_fma, // 153
  spvtools::Extension::kSPV_EXT_shader_atomic_float_add, // 154
  spvtools::Extension::kSPV_INTEL_long_composites, // 155
  spvtools::Extension::kSPV_EXT_optnone, // 156
  spvtools::Extension::kSPV_INTEL_optnone, // 157
  spvtools::Extension::kSPV_EXT_shader_atomic_float16_add, // 158
  spvtools::Extension::kSPV_INTEL_debug_module, // 159
  spvtools::Extension::kSPV_INTEL_bfloat16_conversion, // 160
  spvtools::Extension::kSPV_INTEL_split_barrier, // 161
  spvtools::Extension::kSPV_EXT_arithmetic_fence, // 162
  spvtools::Extension::kSPV_ALTERA_task_sequence, // 163
  spvtools::Extension::kSPV_INTEL_task_sequence, // 164
  spvtools::Extension::kSPV_INTEL_fp_max_error, // 165
  spvtools::Extension::kSPV_ALTERA_fpga_latency_control, // 166
  spvtools::Extension::kSPV_INTEL_fpga_latency_control, // 167
  spvtools::Extension::kSPV_ALTERA_fpga_argument_interfaces, // 168
  spvtools::Extension::kSPV_INTEL_fpga_argument_interfaces, // 169
  spvtools::Extension::kSPV_INTEL_global_variable_host_access, // 170
  spvtools::Extension::kSPV_ALTERA_global_variable_fpga_decorations, // 171
  spvtools::Extension::kSPV_INTEL_global_variable_fpga_decorations, // 172
  spvtools::Extension::kSPV_INTEL_subgroup_buffer_prefetch, // 173
  spvtools::Extension::kSPV_INTEL_2d_block_io, // 174
  spvtools::Extension::kSPV_INTEL_subgroup_matrix_multiply_accumulate, // 175
  spvtools::Extension::kSPV_INTEL_ternary_bitwise_function, // 176
  spvtools::Extension::kSPV_INTEL_function_variants, // 177
  spvtools::Extension::kSPV_KHR_uniform_group_instructions, // 178
  spvtools::Extension::kSPV_INTEL_tensor_float32_conversion, // 179
  spvtools::Extension::kSPV_INTEL_masked_gather_scatter, // 180
  spvtools::Extension::kSPV_INTEL_cache_controls, // 181
  spvtools::Extension::kSPV_INTEL_maximum_registers, // 182
  spvtools::Extension::kSPV_INTEL_bindless_images, // 183
  spvtools::Extension::kSPV_VALVE_mixed_float_dot_product, // 184
  spvtools::Extension::kSPV_KHR_no_integer_wrap_decoration, // 185
  spvtools::Extension::kSPV_NV_mesh_shader, // 186
  spvtools::Extension::kSPV_EXT_mesh_shader, // 187
  spvtools::Extension::kSPV_GOOGLE_hlsl_functionality1, // 188
  spvtools::Extension::kSPV_GOOGLE_user_type, // 189
  spvtools::Extension::kSPV_KHR_subgroup_uniform_control_flow, // 190
  spvtools::Extension::kSPV_AMD_shader_early_and_late_fragment_tests, // 191
  spvtools::Extension::kSPV_AMD_shader_early_and_late_fragment_tests, // 192
  spvtools::Extension::kSPV_EXT_shader_stencil_export, // 193
  spvtools::Extension::kSPV_KHR_maximal_reconvergence, // 194
  spvtools::Extension::kSPV_KHR_linkonce_odr, // 195
  spvtools::Extension::kSPV_KHR_storage_buffer_storage_class, // 196
  spvtools::Extension::kSPV_KHR_variable_pointers, // 197
  spvtools::Extension::kSPV_KHR_terminate_invocation, // 198
  spvtools::Extension::kSPV_KHR_relaxed_extended_instruction, // 199
  spvtools::Extension::kSPV_KHR_ray_tracing, // 200
  spvtools::Extension::kSPV_KHR_ray_query, // 201
  spvtools::Extension::kSPV_NV_ray_tracing, // 202
  spvtools::Extension::kSPV_KHR_ray_tracing, // 203
  spvtools::Extension::kSPV_KHR_ray_query, // 204
  spvtools::Extension::kSPV_NV_displacement_micromap, // 205
  spvtools::Extension::kSPV_GOOGLE_decorate_string, // 206
  spvtools::Extension::kSPV_GOOGLE_hlsl_functionality1, // 207
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
  SPV_OPERAND_TYPE_LITERAL_STRING, // 481
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
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 595
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 596
  SPV_OPERAND_TYPE_ID, // 597
  SPV_OPERAND_TYPE_ID, // 598
  SPV_OPERAND_TYPE_ID, // 599
  SPV_OPERAND_TYPE_ID, // 600
  SPV_OPERAND_TYPE_ID, // 601
  SPV_OPERAND_TYPE_ID, // 602
  SPV_OPERAND_TYPE_ID, // 603
  SPV_OPERAND_TYPE_ID, // 604
  SPV_OPERAND_TYPE_ID, // 605
  SPV_OPERAND_TYPE_ID, // 606
  SPV_OPERAND_TYPE_ID, // 607
  SPV_OPERAND_TYPE_ID, // 608
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 609
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 610
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
  SPV_OPERAND_TYPE_ID, // 621
  SPV_OPERAND_TYPE_ID, // 622
  SPV_OPERAND_TYPE_ID, // 623
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 624
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 625
  SPV_OPERAND_TYPE_RESULT_ID, // 626
  SPV_OPERAND_TYPE_ID, // 627
  SPV_OPERAND_TYPE_SCOPE_ID, // 628
  SPV_OPERAND_TYPE_ID, // 629
  SPV_OPERAND_TYPE_ID, // 630
  SPV_OPERAND_TYPE_TYPE_ID, // 631
  SPV_OPERAND_TYPE_RESULT_ID, // 632
  SPV_OPERAND_TYPE_ID, // 633
  SPV_OPERAND_TYPE_ID, // 634
  SPV_OPERAND_TYPE_ID, // 635
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 636
  SPV_OPERAND_TYPE_ID, // 637
  SPV_OPERAND_TYPE_ID, // 638
  SPV_OPERAND_TYPE_ID, // 639
  SPV_OPERAND_TYPE_ID, // 640
  SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, // 641
  SPV_OPERAND_TYPE_TYPE_ID, // 642
  SPV_OPERAND_TYPE_RESULT_ID, // 643
  SPV_OPERAND_TYPE_ID, // 644
  SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE, // 645
  SPV_OPERAND_TYPE_ID, // 646
  SPV_OPERAND_TYPE_TYPE_ID, // 647
  SPV_OPERAND_TYPE_RESULT_ID, // 648
  SPV_OPERAND_TYPE_ID, // 649
  SPV_OPERAND_TYPE_ID, // 650
  SPV_OPERAND_TYPE_ID, // 651
  SPV_OPERAND_TYPE_MEMORY_ACCESS, // 652
  SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS, // 653
  SPV_OPERAND_TYPE_ID, // 654
  SPV_OPERAND_TYPE_ID, // 655
  SPV_OPERAND_TYPE_ID, // 656
  SPV_OPERAND_TYPE_MEMORY_ACCESS, // 657
  SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS, // 658
  SPV_OPERAND_TYPE_RESULT_ID, // 659
  SPV_OPERAND_TYPE_ID, // 660
  SPV_OPERAND_TYPE_ID, // 661
  SPV_OPERAND_TYPE_VARIABLE_ID, // 662
  SPV_OPERAND_TYPE_TYPE_ID, // 663
  SPV_OPERAND_TYPE_RESULT_ID, // 664
  SPV_OPERAND_TYPE_ID, // 665
  SPV_OPERAND_TYPE_ID, // 666
  SPV_OPERAND_TYPE_ID, // 667
  SPV_OPERAND_TYPE_ID, // 668
  SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS, // 669
  SPV_OPERAND_TYPE_ID, // 670
  SPV_OPERAND_TYPE_ID, // 671
  SPV_OPERAND_TYPE_ID, // 672
  SPV_OPERAND_TYPE_ID, // 673
  SPV_OPERAND_TYPE_ID, // 674
  SPV_OPERAND_TYPE_TYPE_ID, // 675
  SPV_OPERAND_TYPE_RESULT_ID, // 676
  SPV_OPERAND_TYPE_ID, // 677
  SPV_OPERAND_TYPE_ID, // 678
  SPV_OPERAND_TYPE_LITERAL_STRING, // 679
  SPV_OPERAND_TYPE_LITERAL_STRING, // 680
  SPV_OPERAND_TYPE_TYPE_ID, // 681
  SPV_OPERAND_TYPE_RESULT_ID, // 682
  SPV_OPERAND_TYPE_ID, // 683
  SPV_OPERAND_TYPE_ID, // 684
  SPV_OPERAND_TYPE_ID, // 685
  SPV_OPERAND_TYPE_ID, // 686
  SPV_OPERAND_TYPE_ID, // 687
  SPV_OPERAND_TYPE_ID, // 688
  SPV_OPERAND_TYPE_ID, // 689
  SPV_OPERAND_TYPE_TYPE_ID, // 690
  SPV_OPERAND_TYPE_RESULT_ID, // 691
  SPV_OPERAND_TYPE_ID, // 692
  SPV_OPERAND_TYPE_ID, // 693
  SPV_OPERAND_TYPE_ID, // 694
  SPV_OPERAND_TYPE_ID, // 695
  SPV_OPERAND_TYPE_ID, // 696
  SPV_OPERAND_TYPE_ID, // 697
  SPV_OPERAND_TYPE_ID, // 698
  SPV_OPERAND_TYPE_ID, // 699
  SPV_OPERAND_TYPE_TYPE_ID, // 700
  SPV_OPERAND_TYPE_RESULT_ID, // 701
  SPV_OPERAND_TYPE_ID, // 702
  SPV_OPERAND_TYPE_ID, // 703
  SPV_OPERAND_TYPE_ID, // 704
  SPV_OPERAND_TYPE_ID, // 705
  SPV_OPERAND_TYPE_ID, // 706
  SPV_OPERAND_TYPE_ID, // 707
  SPV_OPERAND_TYPE_ID, // 708
  SPV_OPERAND_TYPE_ID, // 709
  SPV_OPERAND_TYPE_ID, // 710
  SPV_OPERAND_TYPE_ID, // 711
  SPV_OPERAND_TYPE_ID, // 712
  SPV_OPERAND_TYPE_TYPE_ID, // 713
  SPV_OPERAND_TYPE_RESULT_ID, // 714
  SPV_OPERAND_TYPE_ID, // 715
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 716
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 717
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 718
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 719
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 720
  SPV_OPERAND_TYPE_TYPE_ID, // 721
  SPV_OPERAND_TYPE_RESULT_ID, // 722
  SPV_OPERAND_TYPE_ID, // 723
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 724
  SPV_OPERAND_TYPE_ID, // 725
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 726
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 727
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 728
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 729
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 730
  SPV_OPERAND_TYPE_TYPE_ID, // 731
  SPV_OPERAND_TYPE_RESULT_ID, // 732
  SPV_OPERAND_TYPE_ID, // 733
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 734
  SPV_OPERAND_TYPE_ID, // 735
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 736
  SPV_OPERAND_TYPE_RESULT_ID, // 737
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 738
  SPV_OPERAND_TYPE_RESULT_ID, // 739
  SPV_OPERAND_TYPE_ID, // 740
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 741
  SPV_OPERAND_TYPE_VARIABLE_ID, // 742
  SPV_OPERAND_TYPE_TYPE_ID, // 743
  SPV_OPERAND_TYPE_RESULT_ID, // 744
  SPV_OPERAND_TYPE_ID, // 745
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 746
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 747
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 748
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 749
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
  SPV_OPERAND_TYPE_ID, // 766
  SPV_OPERAND_TYPE_ID, // 767
  SPV_OPERAND_TYPE_ID, // 768
  SPV_OPERAND_TYPE_TYPE_ID, // 769
  SPV_OPERAND_TYPE_RESULT_ID, // 770
  SPV_OPERAND_TYPE_ID, // 771
  SPV_OPERAND_TYPE_ID, // 772
  SPV_OPERAND_TYPE_ID, // 773
  SPV_OPERAND_TYPE_ID, // 774
  SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS, // 775
  SPV_OPERAND_TYPE_ID, // 776
  SPV_OPERAND_TYPE_EXECUTION_MODEL, // 777
  SPV_OPERAND_TYPE_ID, // 778
  SPV_OPERAND_TYPE_LITERAL_STRING, // 779
  SPV_OPERAND_TYPE_VARIABLE_ID, // 780
  SPV_OPERAND_TYPE_ID, // 781
  SPV_OPERAND_TYPE_CAPABILITY, // 782
  SPV_OPERAND_TYPE_TYPE_ID, // 783
  SPV_OPERAND_TYPE_RESULT_ID, // 784
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 785
  SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER, // 786
  SPV_OPERAND_TYPE_TYPE_ID, // 787
  SPV_OPERAND_TYPE_RESULT_ID, // 788
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 789
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 790
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 791
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 792
  SPV_OPERAND_TYPE_TYPE_ID, // 793
  SPV_OPERAND_TYPE_RESULT_ID, // 794
  SPV_OPERAND_TYPE_VARIABLE_CAPABILITY, // 795
  SPV_OPERAND_TYPE_TYPE_ID, // 796
  SPV_OPERAND_TYPE_RESULT_ID, // 797
  SPV_OPERAND_TYPE_ID, // 798
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 799
  SPV_OPERAND_TYPE_ID, // 800
  SPV_OPERAND_TYPE_ID, // 801
  SPV_OPERAND_TYPE_ID, // 802
  SPV_OPERAND_TYPE_ID, // 803
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 804
  SPV_OPERAND_TYPE_ID, // 805
  SPV_OPERAND_TYPE_ID, // 806
  SPV_OPERAND_TYPE_ID, // 807
  SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING, // 808
  SPV_OPERAND_TYPE_ID, // 809
  SPV_OPERAND_TYPE_STORAGE_CLASS, // 810
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 811
  SPV_OPERAND_TYPE_ID, // 812
  SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER, // 813
  SPV_OPERAND_TYPE_ID, // 814
  SPV_OPERAND_TYPE_ID, // 815
  SPV_OPERAND_TYPE_ID, // 816
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 817
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 818
  SPV_OPERAND_TYPE_ID, // 819
  SPV_OPERAND_TYPE_ID, // 820
  SPV_OPERAND_TYPE_ID, // 821
  SPV_OPERAND_TYPE_ID, // 822
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 823
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 824
  SPV_OPERAND_TYPE_ID, // 825
  SPV_OPERAND_TYPE_ID, // 826
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 827
  SPV_OPERAND_TYPE_VARIABLE_ID, // 828
  SPV_OPERAND_TYPE_ID, // 829
  SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE, // 830
  SPV_OPERAND_TYPE_ID, // 831
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 832
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 833
  SPV_OPERAND_TYPE_ID, // 834
  SPV_OPERAND_TYPE_ID, // 835
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 836
  SPV_OPERAND_TYPE_VARIABLE_ID, // 837
  SPV_OPERAND_TYPE_ID, // 838
  SPV_OPERAND_TYPE_ID, // 839
  SPV_OPERAND_TYPE_ID, // 840
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 841
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 842
  SPV_OPERAND_TYPE_ID, // 843
  SPV_OPERAND_TYPE_ID, // 844
  SPV_OPERAND_TYPE_ID, // 845
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 846
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 847
  SPV_OPERAND_TYPE_ID, // 848
  SPV_OPERAND_TYPE_ID, // 849
  SPV_OPERAND_TYPE_ID, // 850
  SPV_OPERAND_TYPE_ID, // 851
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 852
  SPV_OPERAND_TYPE_ID, // 853
  SPV_OPERAND_TYPE_ID, // 854
  SPV_OPERAND_TYPE_ID, // 855
  SPV_OPERAND_TYPE_ID, // 856
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 857
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 858
  SPV_OPERAND_TYPE_ID, // 859
  SPV_OPERAND_TYPE_ID, // 860
  SPV_OPERAND_TYPE_ID, // 861
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 862
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 863
  SPV_OPERAND_TYPE_ID, // 864
  SPV_OPERAND_TYPE_ID, // 865
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 866
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 867
  SPV_OPERAND_TYPE_VARIABLE_ID, // 868
  SPV_OPERAND_TYPE_ID, // 869
  SPV_OPERAND_TYPE_ID, // 870
  SPV_OPERAND_TYPE_ID, // 871
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 872
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 873
  SPV_OPERAND_TYPE_ID, // 874
  SPV_OPERAND_TYPE_ID, // 875
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 876
  SPV_OPERAND_TYPE_ID, // 877
  SPV_OPERAND_TYPE_ID, // 878
  SPV_OPERAND_TYPE_ID, // 879
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 880
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 881
  SPV_OPERAND_TYPE_ID, // 882
  SPV_OPERAND_TYPE_ID, // 883
  SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS, // 884
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 885
  SPV_OPERAND_TYPE_ID, // 886
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 887
  SPV_OPERAND_TYPE_ID, // 888
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 889
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 890
  SPV_OPERAND_TYPE_ID, // 891
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 892
  SPV_OPERAND_TYPE_ID, // 893
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 894
  SPV_OPERAND_TYPE_ID, // 895
  SPV_OPERAND_TYPE_ID, // 896
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 897
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 898
  SPV_OPERAND_TYPE_ID, // 899
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 900
  SPV_OPERAND_TYPE_ID, // 901
  SPV_OPERAND_TYPE_ID, // 902
  SPV_OPERAND_TYPE_ID, // 903
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 904
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 905
  SPV_OPERAND_TYPE_ID, // 906
  SPV_OPERAND_TYPE_OPTIONAL_LITERAL_INTEGER, // 907
  SPV_OPERAND_TYPE_DEBUG_OPERATION, // 908
  SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER, // 909
  SPV_OPERAND_TYPE_ID, // 910
  SPV_OPERAND_TYPE_LITERAL_INTEGER, // 911
  SPV_OPERAND_TYPE_ID, // 912
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 913
  SPV_OPERAND_TYPE_ID, // 914
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 915
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 916
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 917
  SPV_OPERAND_TYPE_OPTIONAL_ID, // 918
  SPV_OPERAND_TYPE_ID, // 919
  SPV_OPERAND_TYPE_ID, // 920
  SPV_OPERAND_TYPE_ID, // 921
  SPV_OPERAND_TYPE_ID, // 922
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
