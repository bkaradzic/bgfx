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
    case Extension::kSPV_EXT_fragment_fully_covered: return IR(531, 31);
    case Extension::kSPV_EXT_fragment_invocation_density: return IR(562, 36);
    case Extension::kSPV_EXT_fragment_shader_interlock: return IR(598, 34);
    case Extension::kSPV_EXT_mesh_shader: return IR(632, 20);
    case Extension::kSPV_EXT_opacity_micromap: return IR(652, 25);
    case Extension::kSPV_EXT_optnone: return IR(677, 16);
    case Extension::kSPV_EXT_physical_storage_buffer: return IR(693, 32);
    case Extension::kSPV_EXT_relaxed_printf_string_address_space: return IR(725, 44);
    case Extension::kSPV_EXT_replicated_composites: return IR(769, 30);
    case Extension::kSPV_EXT_shader_atomic_float16_add: return IR(799, 34);
    case Extension::kSPV_EXT_shader_atomic_float_add: return IR(833, 32);
    case Extension::kSPV_EXT_shader_atomic_float_min_max: return IR(865, 36);
    case Extension::kSPV_EXT_shader_image_int64: return IR(901, 27);
    case Extension::kSPV_EXT_shader_stencil_export: return IR(928, 30);
    case Extension::kSPV_EXT_shader_tile_image: return IR(958, 26);
    case Extension::kSPV_EXT_shader_viewport_index_layer: return IR(984, 36);
    case Extension::kSPV_GOOGLE_decorate_string: return IR(1020, 27);
    case Extension::kSPV_GOOGLE_hlsl_functionality1: return IR(1047, 31);
    case Extension::kSPV_GOOGLE_user_type: return IR(1078, 21);
    case Extension::kSPV_INTEL_2d_block_io: return IR(1099, 22);
    case Extension::kSPV_INTEL_arbitrary_precision_fixed_point: return IR(1121, 42);
    case Extension::kSPV_INTEL_arbitrary_precision_floating_point: return IR(1163, 45);
    case Extension::kSPV_INTEL_arbitrary_precision_integers: return IR(1208, 39);
    case Extension::kSPV_INTEL_bfloat16_conversion: return IR(1247, 30);
    case Extension::kSPV_INTEL_blocking_pipes: return IR(1277, 25);
    case Extension::kSPV_INTEL_cache_controls: return IR(1302, 25);
    case Extension::kSPV_INTEL_debug_module: return IR(1327, 23);
    case Extension::kSPV_INTEL_device_side_avc_motion_estimation: return IR(1350, 44);
    case Extension::kSPV_INTEL_float_controls2: return IR(1394, 26);
    case Extension::kSPV_INTEL_fp_fast_math_mode: return IR(1420, 28);
    case Extension::kSPV_INTEL_fp_max_error: return IR(1448, 23);
    case Extension::kSPV_INTEL_fpga_argument_interfaces: return IR(1471, 35);
    case Extension::kSPV_INTEL_fpga_buffer_location: return IR(1506, 31);
    case Extension::kSPV_INTEL_fpga_cluster_attributes: return IR(1537, 34);
    case Extension::kSPV_INTEL_fpga_dsp_control: return IR(1571, 27);
    case Extension::kSPV_INTEL_fpga_invocation_pipelining_attributes: return IR(1598, 48);
    case Extension::kSPV_INTEL_fpga_latency_control: return IR(1646, 31);
    case Extension::kSPV_INTEL_fpga_loop_controls: return IR(1677, 29);
    case Extension::kSPV_INTEL_fpga_memory_accesses: return IR(1706, 31);
    case Extension::kSPV_INTEL_fpga_memory_attributes: return IR(1737, 33);
    case Extension::kSPV_INTEL_fpga_reg: return IR(1770, 19);
    case Extension::kSPV_INTEL_function_pointers: return IR(1789, 28);
    case Extension::kSPV_INTEL_global_variable_fpga_decorations: return IR(1817, 43);
    case Extension::kSPV_INTEL_global_variable_host_access: return IR(1860, 38);
    case Extension::kSPV_INTEL_inline_assembly: return IR(1898, 26);
    case Extension::kSPV_INTEL_int4: return IR(1924, 15);
    case Extension::kSPV_INTEL_io_pipes: return IR(1939, 19);
    case Extension::kSPV_INTEL_kernel_attributes: return IR(1958, 28);
    case Extension::kSPV_INTEL_long_composites: return IR(1986, 26);
    case Extension::kSPV_INTEL_loop_fuse: return IR(2012, 20);
    case Extension::kSPV_INTEL_masked_gather_scatter: return IR(2032, 32);
    case Extension::kSPV_INTEL_maximum_registers: return IR(2064, 28);
    case Extension::kSPV_INTEL_media_block_io: return IR(2092, 25);
    case Extension::kSPV_INTEL_memory_access_aliasing: return IR(2117, 33);
    case Extension::kSPV_INTEL_optnone: return IR(2150, 18);
    case Extension::kSPV_INTEL_runtime_aligned: return IR(2168, 26);
    case Extension::kSPV_INTEL_shader_integer_functions2: return IR(2194, 36);
    case Extension::kSPV_INTEL_split_barrier: return IR(2230, 24);
    case Extension::kSPV_INTEL_subgroup_buffer_prefetch: return IR(2254, 35);
    case Extension::kSPV_INTEL_subgroup_matrix_multiply_accumulate: return IR(2289, 46);
    case Extension::kSPV_INTEL_subgroups: return IR(2335, 20);
    case Extension::kSPV_INTEL_task_sequence: return IR(2355, 24);
    case Extension::kSPV_INTEL_tensor_float32_conversion: return IR(2379, 36);
    case Extension::kSPV_INTEL_ternary_bitwise_function: return IR(2415, 35);
    case Extension::kSPV_INTEL_unstructured_loop_controls: return IR(2450, 37);
    case Extension::kSPV_INTEL_usm_storage_classes: return IR(2487, 30);
    case Extension::kSPV_INTEL_variable_length_array: return IR(2517, 32);
    case Extension::kSPV_INTEL_vector_compute: return IR(2549, 25);
    case Extension::kSPV_KHR_16bit_storage: return IR(2574, 22);
    case Extension::kSPV_KHR_8bit_storage: return IR(2596, 21);
    case Extension::kSPV_KHR_bfloat16: return IR(2617, 17);
    case Extension::kSPV_KHR_bit_instructions: return IR(2634, 25);
    case Extension::kSPV_KHR_compute_shader_derivatives: return IR(2659, 35);
    case Extension::kSPV_KHR_cooperative_matrix: return IR(2694, 27);
    case Extension::kSPV_KHR_device_group: return IR(2721, 21);
    case Extension::kSPV_KHR_expect_assume: return IR(2742, 22);
    case Extension::kSPV_KHR_float_controls: return IR(2764, 23);
    case Extension::kSPV_KHR_float_controls2: return IR(2787, 24);
    case Extension::kSPV_KHR_fragment_shader_barycentric: return IR(2811, 36);
    case Extension::kSPV_KHR_fragment_shading_rate: return IR(2847, 30);
    case Extension::kSPV_KHR_integer_dot_product: return IR(2877, 28);
    case Extension::kSPV_KHR_linkonce_odr: return IR(2905, 21);
    case Extension::kSPV_KHR_maximal_reconvergence: return IR(2926, 30);
    case Extension::kSPV_KHR_multiview: return IR(2956, 18);
    case Extension::kSPV_KHR_no_integer_wrap_decoration: return IR(2974, 35);
    case Extension::kSPV_KHR_non_semantic_info: return IR(3009, 26);
    case Extension::kSPV_KHR_physical_storage_buffer: return IR(3035, 32);
    case Extension::kSPV_KHR_post_depth_coverage: return IR(3067, 28);
    case Extension::kSPV_KHR_quad_control: return IR(3095, 21);
    case Extension::kSPV_KHR_ray_cull_mask: return IR(3116, 22);
    case Extension::kSPV_KHR_ray_query: return IR(3138, 18);
    case Extension::kSPV_KHR_ray_tracing: return IR(3156, 20);
    case Extension::kSPV_KHR_ray_tracing_position_fetch: return IR(3176, 35);
    case Extension::kSPV_KHR_relaxed_extended_instruction: return IR(3211, 37);
    case Extension::kSPV_KHR_shader_atomic_counter_ops: return IR(3248, 34);
    case Extension::kSPV_KHR_shader_ballot: return IR(3282, 22);
    case Extension::kSPV_KHR_shader_clock: return IR(3304, 21);
    case Extension::kSPV_KHR_shader_draw_parameters: return IR(3325, 31);
    case Extension::kSPV_KHR_storage_buffer_storage_class: return IR(3356, 37);
    case Extension::kSPV_KHR_subgroup_rotate: return IR(3393, 24);
    case Extension::kSPV_KHR_subgroup_uniform_control_flow: return IR(3417, 38);
    case Extension::kSPV_KHR_subgroup_vote: return IR(3455, 22);
    case Extension::kSPV_KHR_terminate_invocation: return IR(3477, 29);
    case Extension::kSPV_KHR_uniform_group_instructions: return IR(3506, 35);
    case Extension::kSPV_KHR_untyped_pointers: return IR(3541, 25);
    case Extension::kSPV_KHR_variable_pointers: return IR(3566, 26);
    case Extension::kSPV_KHR_vulkan_memory_model: return IR(3592, 28);
    case Extension::kSPV_KHR_workgroup_memory_explicit_layout: return IR(3620, 41);
    case Extension::kSPV_NVX_multiview_per_view_attributes: return IR(3661, 38);
    case Extension::kSPV_NV_bindless_texture: return IR(3699, 24);
    case Extension::kSPV_NV_cluster_acceleration_structure: return IR(3723, 38);
    case Extension::kSPV_NV_compute_shader_derivatives: return IR(3761, 34);
    case Extension::kSPV_NV_cooperative_matrix: return IR(3795, 26);
    case Extension::kSPV_NV_cooperative_matrix2: return IR(3821, 27);
    case Extension::kSPV_NV_cooperative_vector: return IR(3848, 26);
    case Extension::kSPV_NV_displacement_micromap: return IR(3874, 29);
    case Extension::kSPV_NV_fragment_shader_barycentric: return IR(3903, 35);
    case Extension::kSPV_NV_geometry_shader_passthrough: return IR(3938, 35);
    case Extension::kSPV_NV_linear_swept_spheres: return IR(3973, 28);
    case Extension::kSPV_NV_mesh_shader: return IR(4001, 19);
    case Extension::kSPV_NV_raw_access_chains: return IR(4020, 25);
    case Extension::kSPV_NV_ray_tracing: return IR(4045, 19);
    case Extension::kSPV_NV_ray_tracing_motion_blur: return IR(4064, 31);
    case Extension::kSPV_NV_sample_mask_override_coverage: return IR(4095, 37);
    case Extension::kSPV_NV_shader_atomic_fp16_vector: return IR(4132, 33);
    case Extension::kSPV_NV_shader_image_footprint: return IR(4165, 30);
    case Extension::kSPV_NV_shader_invocation_reorder: return IR(4195, 33);
    case Extension::kSPV_NV_shader_sm_builtins: return IR(4228, 26);
    case Extension::kSPV_NV_shader_subgroup_partitioned: return IR(4254, 35);
    case Extension::kSPV_NV_shading_rate: return IR(4289, 20);
    case Extension::kSPV_NV_stereo_view_rendering: return IR(4309, 29);
    case Extension::kSPV_NV_tensor_addressing: return IR(4338, 25);
    case Extension::kSPV_NV_viewport_array2: return IR(4363, 23);
    case Extension::kSPV_QCOM_image_processing: return IR(4386, 26);
    case Extension::kSPV_QCOM_image_processing2: return IR(4412, 27);
    case Extension::kSPV_QCOM_tile_shading: return IR(4439, 22);
    case Extension::kSPV_VALIDATOR_ignore_type_decl_unique: return IR(4461, 38);
    default: break;
  }
  return {};
}

// Extension names and values, ordered by name
// The fields in order are:
//   name, indexing into kStrings
//   enum value
static const std::array<NameValue,155> kExtensionNames{{
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
    {IR(531, 31), static_cast<uint32_t>(kSPV_EXT_fragment_fully_covered)},
    {IR(562, 36), static_cast<uint32_t>(kSPV_EXT_fragment_invocation_density)},
    {IR(598, 34), static_cast<uint32_t>(kSPV_EXT_fragment_shader_interlock)},
    {IR(632, 20), static_cast<uint32_t>(kSPV_EXT_mesh_shader)},
    {IR(652, 25), static_cast<uint32_t>(kSPV_EXT_opacity_micromap)},
    {IR(677, 16), static_cast<uint32_t>(kSPV_EXT_optnone)},
    {IR(693, 32), static_cast<uint32_t>(kSPV_EXT_physical_storage_buffer)},
    {IR(725, 44), static_cast<uint32_t>(kSPV_EXT_relaxed_printf_string_address_space)},
    {IR(769, 30), static_cast<uint32_t>(kSPV_EXT_replicated_composites)},
    {IR(799, 34), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float16_add)},
    {IR(833, 32), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float_add)},
    {IR(865, 36), static_cast<uint32_t>(kSPV_EXT_shader_atomic_float_min_max)},
    {IR(901, 27), static_cast<uint32_t>(kSPV_EXT_shader_image_int64)},
    {IR(928, 30), static_cast<uint32_t>(kSPV_EXT_shader_stencil_export)},
    {IR(958, 26), static_cast<uint32_t>(kSPV_EXT_shader_tile_image)},
    {IR(984, 36), static_cast<uint32_t>(kSPV_EXT_shader_viewport_index_layer)},
    {IR(1020, 27), static_cast<uint32_t>(kSPV_GOOGLE_decorate_string)},
    {IR(1047, 31), static_cast<uint32_t>(kSPV_GOOGLE_hlsl_functionality1)},
    {IR(1078, 21), static_cast<uint32_t>(kSPV_GOOGLE_user_type)},
    {IR(1099, 22), static_cast<uint32_t>(kSPV_INTEL_2d_block_io)},
    {IR(1121, 42), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_fixed_point)},
    {IR(1163, 45), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_floating_point)},
    {IR(1208, 39), static_cast<uint32_t>(kSPV_INTEL_arbitrary_precision_integers)},
    {IR(1247, 30), static_cast<uint32_t>(kSPV_INTEL_bfloat16_conversion)},
    {IR(1277, 25), static_cast<uint32_t>(kSPV_INTEL_blocking_pipes)},
    {IR(1302, 25), static_cast<uint32_t>(kSPV_INTEL_cache_controls)},
    {IR(1327, 23), static_cast<uint32_t>(kSPV_INTEL_debug_module)},
    {IR(1350, 44), static_cast<uint32_t>(kSPV_INTEL_device_side_avc_motion_estimation)},
    {IR(1394, 26), static_cast<uint32_t>(kSPV_INTEL_float_controls2)},
    {IR(1420, 28), static_cast<uint32_t>(kSPV_INTEL_fp_fast_math_mode)},
    {IR(1448, 23), static_cast<uint32_t>(kSPV_INTEL_fp_max_error)},
    {IR(1471, 35), static_cast<uint32_t>(kSPV_INTEL_fpga_argument_interfaces)},
    {IR(1506, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_buffer_location)},
    {IR(1537, 34), static_cast<uint32_t>(kSPV_INTEL_fpga_cluster_attributes)},
    {IR(1571, 27), static_cast<uint32_t>(kSPV_INTEL_fpga_dsp_control)},
    {IR(1598, 48), static_cast<uint32_t>(kSPV_INTEL_fpga_invocation_pipelining_attributes)},
    {IR(1646, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_latency_control)},
    {IR(1677, 29), static_cast<uint32_t>(kSPV_INTEL_fpga_loop_controls)},
    {IR(1706, 31), static_cast<uint32_t>(kSPV_INTEL_fpga_memory_accesses)},
    {IR(1737, 33), static_cast<uint32_t>(kSPV_INTEL_fpga_memory_attributes)},
    {IR(1770, 19), static_cast<uint32_t>(kSPV_INTEL_fpga_reg)},
    {IR(1789, 28), static_cast<uint32_t>(kSPV_INTEL_function_pointers)},
    {IR(1817, 43), static_cast<uint32_t>(kSPV_INTEL_global_variable_fpga_decorations)},
    {IR(1860, 38), static_cast<uint32_t>(kSPV_INTEL_global_variable_host_access)},
    {IR(1898, 26), static_cast<uint32_t>(kSPV_INTEL_inline_assembly)},
    {IR(1924, 15), static_cast<uint32_t>(kSPV_INTEL_int4)},
    {IR(1939, 19), static_cast<uint32_t>(kSPV_INTEL_io_pipes)},
    {IR(1958, 28), static_cast<uint32_t>(kSPV_INTEL_kernel_attributes)},
    {IR(1986, 26), static_cast<uint32_t>(kSPV_INTEL_long_composites)},
    {IR(2012, 20), static_cast<uint32_t>(kSPV_INTEL_loop_fuse)},
    {IR(2032, 32), static_cast<uint32_t>(kSPV_INTEL_masked_gather_scatter)},
    {IR(2064, 28), static_cast<uint32_t>(kSPV_INTEL_maximum_registers)},
    {IR(2092, 25), static_cast<uint32_t>(kSPV_INTEL_media_block_io)},
    {IR(2117, 33), static_cast<uint32_t>(kSPV_INTEL_memory_access_aliasing)},
    {IR(2150, 18), static_cast<uint32_t>(kSPV_INTEL_optnone)},
    {IR(2168, 26), static_cast<uint32_t>(kSPV_INTEL_runtime_aligned)},
    {IR(2194, 36), static_cast<uint32_t>(kSPV_INTEL_shader_integer_functions2)},
    {IR(2230, 24), static_cast<uint32_t>(kSPV_INTEL_split_barrier)},
    {IR(2254, 35), static_cast<uint32_t>(kSPV_INTEL_subgroup_buffer_prefetch)},
    {IR(2289, 46), static_cast<uint32_t>(kSPV_INTEL_subgroup_matrix_multiply_accumulate)},
    {IR(2335, 20), static_cast<uint32_t>(kSPV_INTEL_subgroups)},
    {IR(2355, 24), static_cast<uint32_t>(kSPV_INTEL_task_sequence)},
    {IR(2379, 36), static_cast<uint32_t>(kSPV_INTEL_tensor_float32_conversion)},
    {IR(2415, 35), static_cast<uint32_t>(kSPV_INTEL_ternary_bitwise_function)},
    {IR(2450, 37), static_cast<uint32_t>(kSPV_INTEL_unstructured_loop_controls)},
    {IR(2487, 30), static_cast<uint32_t>(kSPV_INTEL_usm_storage_classes)},
    {IR(2517, 32), static_cast<uint32_t>(kSPV_INTEL_variable_length_array)},
    {IR(2549, 25), static_cast<uint32_t>(kSPV_INTEL_vector_compute)},
    {IR(2574, 22), static_cast<uint32_t>(kSPV_KHR_16bit_storage)},
    {IR(2596, 21), static_cast<uint32_t>(kSPV_KHR_8bit_storage)},
    {IR(2617, 17), static_cast<uint32_t>(kSPV_KHR_bfloat16)},
    {IR(2634, 25), static_cast<uint32_t>(kSPV_KHR_bit_instructions)},
    {IR(2659, 35), static_cast<uint32_t>(kSPV_KHR_compute_shader_derivatives)},
    {IR(2694, 27), static_cast<uint32_t>(kSPV_KHR_cooperative_matrix)},
    {IR(2721, 21), static_cast<uint32_t>(kSPV_KHR_device_group)},
    {IR(2742, 22), static_cast<uint32_t>(kSPV_KHR_expect_assume)},
    {IR(2764, 23), static_cast<uint32_t>(kSPV_KHR_float_controls)},
    {IR(2787, 24), static_cast<uint32_t>(kSPV_KHR_float_controls2)},
    {IR(2811, 36), static_cast<uint32_t>(kSPV_KHR_fragment_shader_barycentric)},
    {IR(2847, 30), static_cast<uint32_t>(kSPV_KHR_fragment_shading_rate)},
    {IR(2877, 28), static_cast<uint32_t>(kSPV_KHR_integer_dot_product)},
    {IR(2905, 21), static_cast<uint32_t>(kSPV_KHR_linkonce_odr)},
    {IR(2926, 30), static_cast<uint32_t>(kSPV_KHR_maximal_reconvergence)},
    {IR(2956, 18), static_cast<uint32_t>(kSPV_KHR_multiview)},
    {IR(2974, 35), static_cast<uint32_t>(kSPV_KHR_no_integer_wrap_decoration)},
    {IR(3009, 26), static_cast<uint32_t>(kSPV_KHR_non_semantic_info)},
    {IR(3035, 32), static_cast<uint32_t>(kSPV_KHR_physical_storage_buffer)},
    {IR(3067, 28), static_cast<uint32_t>(kSPV_KHR_post_depth_coverage)},
    {IR(3095, 21), static_cast<uint32_t>(kSPV_KHR_quad_control)},
    {IR(3116, 22), static_cast<uint32_t>(kSPV_KHR_ray_cull_mask)},
    {IR(3138, 18), static_cast<uint32_t>(kSPV_KHR_ray_query)},
    {IR(3156, 20), static_cast<uint32_t>(kSPV_KHR_ray_tracing)},
    {IR(3176, 35), static_cast<uint32_t>(kSPV_KHR_ray_tracing_position_fetch)},
    {IR(3211, 37), static_cast<uint32_t>(kSPV_KHR_relaxed_extended_instruction)},
    {IR(3248, 34), static_cast<uint32_t>(kSPV_KHR_shader_atomic_counter_ops)},
    {IR(3282, 22), static_cast<uint32_t>(kSPV_KHR_shader_ballot)},
    {IR(3304, 21), static_cast<uint32_t>(kSPV_KHR_shader_clock)},
    {IR(3325, 31), static_cast<uint32_t>(kSPV_KHR_shader_draw_parameters)},
    {IR(3356, 37), static_cast<uint32_t>(kSPV_KHR_storage_buffer_storage_class)},
    {IR(3393, 24), static_cast<uint32_t>(kSPV_KHR_subgroup_rotate)},
    {IR(3417, 38), static_cast<uint32_t>(kSPV_KHR_subgroup_uniform_control_flow)},
    {IR(3455, 22), static_cast<uint32_t>(kSPV_KHR_subgroup_vote)},
    {IR(3477, 29), static_cast<uint32_t>(kSPV_KHR_terminate_invocation)},
    {IR(3506, 35), static_cast<uint32_t>(kSPV_KHR_uniform_group_instructions)},
    {IR(3541, 25), static_cast<uint32_t>(kSPV_KHR_untyped_pointers)},
    {IR(3566, 26), static_cast<uint32_t>(kSPV_KHR_variable_pointers)},
    {IR(3592, 28), static_cast<uint32_t>(kSPV_KHR_vulkan_memory_model)},
    {IR(3620, 41), static_cast<uint32_t>(kSPV_KHR_workgroup_memory_explicit_layout)},
    {IR(3661, 38), static_cast<uint32_t>(kSPV_NVX_multiview_per_view_attributes)},
    {IR(3699, 24), static_cast<uint32_t>(kSPV_NV_bindless_texture)},
    {IR(3723, 38), static_cast<uint32_t>(kSPV_NV_cluster_acceleration_structure)},
    {IR(3761, 34), static_cast<uint32_t>(kSPV_NV_compute_shader_derivatives)},
    {IR(3795, 26), static_cast<uint32_t>(kSPV_NV_cooperative_matrix)},
    {IR(3821, 27), static_cast<uint32_t>(kSPV_NV_cooperative_matrix2)},
    {IR(3848, 26), static_cast<uint32_t>(kSPV_NV_cooperative_vector)},
    {IR(3874, 29), static_cast<uint32_t>(kSPV_NV_displacement_micromap)},
    {IR(3903, 35), static_cast<uint32_t>(kSPV_NV_fragment_shader_barycentric)},
    {IR(3938, 35), static_cast<uint32_t>(kSPV_NV_geometry_shader_passthrough)},
    {IR(3973, 28), static_cast<uint32_t>(kSPV_NV_linear_swept_spheres)},
    {IR(4001, 19), static_cast<uint32_t>(kSPV_NV_mesh_shader)},
    {IR(4020, 25), static_cast<uint32_t>(kSPV_NV_raw_access_chains)},
    {IR(4045, 19), static_cast<uint32_t>(kSPV_NV_ray_tracing)},
    {IR(4064, 31), static_cast<uint32_t>(kSPV_NV_ray_tracing_motion_blur)},
    {IR(4095, 37), static_cast<uint32_t>(kSPV_NV_sample_mask_override_coverage)},
    {IR(4132, 33), static_cast<uint32_t>(kSPV_NV_shader_atomic_fp16_vector)},
    {IR(4165, 30), static_cast<uint32_t>(kSPV_NV_shader_image_footprint)},
    {IR(4195, 33), static_cast<uint32_t>(kSPV_NV_shader_invocation_reorder)},
    {IR(4228, 26), static_cast<uint32_t>(kSPV_NV_shader_sm_builtins)},
    {IR(4254, 35), static_cast<uint32_t>(kSPV_NV_shader_subgroup_partitioned)},
    {IR(4289, 20), static_cast<uint32_t>(kSPV_NV_shading_rate)},
    {IR(4309, 29), static_cast<uint32_t>(kSPV_NV_stereo_view_rendering)},
    {IR(4338, 25), static_cast<uint32_t>(kSPV_NV_tensor_addressing)},
    {IR(4363, 23), static_cast<uint32_t>(kSPV_NV_viewport_array2)},
    {IR(4386, 26), static_cast<uint32_t>(kSPV_QCOM_image_processing)},
    {IR(4412, 27), static_cast<uint32_t>(kSPV_QCOM_image_processing2)},
    {IR(4439, 22), static_cast<uint32_t>(kSPV_QCOM_tile_shading)},
    {IR(4461, 38), static_cast<uint32_t>(kSPV_VALIDATOR_ignore_type_decl_unique)},
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
static const std::array<OperandDesc, 1176> kOperandsByValue{{
  {0,IR(0, 0),IR(4499, 9)/* ReadOnly */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {1,IR(0, 0),IR(4515, 10)/* WriteOnly */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {2,IR(0, 0),IR(4525, 10)/* ReadWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {0,IR(0, 0),IR(4535, 8)/* Logical */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {1,IR(0, 0),IR(4543, 11)/* Physical32 */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {2,IR(0, 0),IR(4564, 11)/* Physical64 */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {5348,IR(0, 0),IR(4575, 24)/* PhysicalStorageBuffer64 */,IR(0, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {0,IR(0, 0),IR(4657, 9)/* Position */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {1,IR(0, 0),IR(4673, 10)/* PointSize */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {3,IR(0, 0),IR(4683, 13)/* ClipDistance */,IR(0, 0),IR(4, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4,IR(0, 0),IR(4696, 13)/* CullDistance */,IR(0, 0),IR(5, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5,IR(0, 0),IR(4709, 9)/* VertexId */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {6,IR(0, 0),IR(4718, 11)/* InstanceId */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {7,IR(0, 0),IR(4729, 12)/* PrimitiveId */,IR(0, 0),IR(6, 6),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {8,IR(0, 0),IR(4819, 13)/* InvocationId */,IR(0, 0),IR(12, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {9,IR(0, 0),IR(4832, 6)/* Layer */,IR(0, 0),IR(14, 5),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {10,IR(0, 0),IR(4878, 14)/* ViewportIndex */,IR(0, 0),IR(19, 5),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {11,IR(0, 0),IR(4926, 15)/* TessLevelOuter */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {12,IR(0, 0),IR(4941, 15)/* TessLevelInner */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {13,IR(0, 0),IR(4956, 10)/* TessCoord */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {14,IR(0, 0),IR(4966, 14)/* PatchVertices */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {15,IR(0, 0),IR(4980, 10)/* FragCoord */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {16,IR(0, 0),IR(4990, 11)/* PointCoord */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {17,IR(0, 0),IR(5001, 12)/* FrontFacing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {18,IR(0, 0),IR(5013, 9)/* SampleId */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {19,IR(0, 0),IR(5040, 15)/* SamplePosition */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {20,IR(0, 0),IR(5055, 11)/* SampleMask */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {22,IR(0, 0),IR(5066, 10)/* FragDepth */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {23,IR(0, 0),IR(5076, 17)/* HelperInvocation */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {24,IR(0, 0),IR(5093, 14)/* NumWorkgroups */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {25,IR(0, 0),IR(5107, 14)/* WorkgroupSize */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {26,IR(0, 0),IR(5121, 12)/* WorkgroupId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {27,IR(0, 0),IR(5133, 18)/* LocalInvocationId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {28,IR(0, 0),IR(5151, 19)/* GlobalInvocationId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {29,IR(0, 0),IR(5170, 21)/* LocalInvocationIndex */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {30,IR(0, 0),IR(5191, 8)/* WorkDim */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {31,IR(0, 0),IR(5199, 11)/* GlobalSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {32,IR(0, 0),IR(5210, 22)/* EnqueuedWorkgroupSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {33,IR(0, 0),IR(5232, 13)/* GlobalOffset */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {34,IR(0, 0),IR(5245, 15)/* GlobalLinearId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {36,IR(0, 0),IR(5260, 13)/* SubgroupSize */,IR(0, 0),IR(26, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {37,IR(0, 0),IR(5307, 16)/* SubgroupMaxSize */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {38,IR(0, 0),IR(5323, 13)/* NumSubgroups */,IR(0, 0),IR(29, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {39,IR(0, 0),IR(5336, 21)/* NumEnqueuedSubgroups */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {40,IR(0, 0),IR(5357, 11)/* SubgroupId */,IR(0, 0),IR(29, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {41,IR(0, 0),IR(5368, 26)/* SubgroupLocalInvocationId */,IR(0, 0),IR(26, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {42,IR(0, 0),IR(5394, 12)/* VertexIndex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {43,IR(0, 0),IR(5406, 14)/* InstanceIndex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4160,IR(0, 0),IR(5420, 10)/* CoreIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4161,IR(0, 0),IR(5446, 13)/* CoreCountARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4162,IR(0, 0),IR(5459, 13)/* CoreMaxIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4163,IR(0, 0),IR(5472, 10)/* WarpIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4164,IR(0, 0),IR(5482, 13)/* WarpMaxIDARM */,IR(0, 0),IR(31, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4416,IR(0, 0),IR(5495, 15)/* SubgroupEqMask */,IR(1, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4417,IR(0, 0),IR(5550, 15)/* SubgroupGeMask */,IR(2, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4418,IR(0, 0),IR(5583, 15)/* SubgroupGtMask */,IR(3, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4419,IR(0, 0),IR(5616, 15)/* SubgroupLeMask */,IR(4, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4420,IR(0, 0),IR(5649, 15)/* SubgroupLtMask */,IR(5, 1),IR(32, 2),IR(2, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4424,IR(0, 0),IR(5682, 11)/* BaseVertex */,IR(0, 0),IR(34, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4425,IR(0, 0),IR(5708, 13)/* BaseInstance */,IR(0, 0),IR(34, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4426,IR(0, 0),IR(5721, 10)/* DrawIndex */,IR(0, 0),IR(35, 3),IR(4, 3),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4432,IR(0, 0),IR(5731, 24)/* PrimitiveShadingRateKHR */,IR(0, 0),IR(38, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4438,IR(0, 0),IR(5778, 12)/* DeviceIndex */,IR(0, 0),IR(39, 1),IR(8, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4440,IR(0, 0),IR(5802, 10)/* ViewIndex */,IR(0, 0),IR(40, 1),IR(9, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4444,IR(0, 0),IR(5822, 15)/* ShadingRateKHR */,IR(0, 0),IR(38, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4492,IR(0, 0),IR(5837, 15)/* TileOffsetQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4493,IR(0, 0),IR(5868, 18)/* TileDimensionQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4494,IR(0, 0),IR(5886, 18)/* TileApronSizeQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4992,IR(0, 0),IR(5904, 20)/* BaryCoordNoPerspAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4993,IR(0, 0),IR(5924, 28)/* BaryCoordNoPerspCentroidAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4994,IR(0, 0),IR(5952, 26)/* BaryCoordNoPerspSampleAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4995,IR(0, 0),IR(5978, 19)/* BaryCoordSmoothAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4996,IR(0, 0),IR(5997, 27)/* BaryCoordSmoothCentroidAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4997,IR(0, 0),IR(6024, 25)/* BaryCoordSmoothSampleAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {4998,IR(0, 0),IR(6049, 22)/* BaryCoordPullModelAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5014,IR(0, 0),IR(6071, 18)/* FragStencilRefEXT */,IR(0, 0),IR(42, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5021,IR(0, 0),IR(6106, 29)/* RemainingRecursionLevelsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5073,IR(0, 0),IR(6153, 16)/* ShaderIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5253,IR(0, 0),IR(6169, 15)/* ViewportMaskNV */,IR(0, 0),IR(44, 2),IR(12, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5257,IR(0, 0),IR(6205, 20)/* SecondaryPositionNV */,IR(0, 0),IR(46, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5258,IR(0, 0),IR(6244, 24)/* SecondaryViewportMaskNV */,IR(0, 0),IR(46, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5261,IR(0, 0),IR(6268, 18)/* PositionPerViewNV */,IR(0, 0),IR(47, 2),IR(15, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5262,IR(0, 0),IR(6306, 22)/* ViewportMaskPerViewNV */,IR(0, 0),IR(47, 2),IR(15, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5264,IR(0, 0),IR(6328, 16)/* FullyCoveredEXT */,IR(0, 0),IR(49, 1),IR(17, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5274,IR(0, 0),IR(6368, 12)/* TaskCountNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5275,IR(0, 0),IR(6380, 17)/* PrimitiveCountNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5276,IR(0, 0),IR(6397, 19)/* PrimitiveIndicesNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5277,IR(0, 0),IR(6416, 22)/* ClipDistancePerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5278,IR(0, 0),IR(6438, 22)/* CullDistancePerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5279,IR(0, 0),IR(6460, 15)/* LayerPerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5280,IR(0, 0),IR(6475, 16)/* MeshViewCountNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5281,IR(0, 0),IR(6491, 18)/* MeshViewIndicesNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5286,IR(0, 0),IR(6509, 13)/* BaryCoordKHR */,IR(6, 1),IR(51, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5287,IR(0, 0),IR(6557, 20)/* BaryCoordNoPerspKHR */,IR(7, 1),IR(51, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5292,IR(0, 0),IR(6596, 12)/* FragSizeEXT */,IR(8, 1),IR(52, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5293,IR(0, 0),IR(6642, 23)/* FragInvocationCountEXT */,IR(9, 1),IR(52, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5294,IR(0, 0),IR(6687, 25)/* PrimitivePointIndicesEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5295,IR(0, 0),IR(6712, 24)/* PrimitiveLineIndicesEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5296,IR(0, 0),IR(6736, 28)/* PrimitiveTriangleIndicesEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5299,IR(0, 0),IR(6764, 17)/* CullPrimitiveEXT */,IR(0, 0),IR(53, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5319,IR(0, 0),IR(6781, 12)/* LaunchIdKHR */,IR(10, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5320,IR(0, 0),IR(6804, 14)/* LaunchSizeKHR */,IR(11, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5321,IR(0, 0),IR(6831, 18)/* WorldRayOriginKHR */,IR(12, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5322,IR(0, 0),IR(6866, 21)/* WorldRayDirectionKHR */,IR(13, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5323,IR(0, 0),IR(6907, 19)/* ObjectRayOriginKHR */,IR(14, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5324,IR(0, 0),IR(6944, 22)/* ObjectRayDirectionKHR */,IR(15, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5325,IR(0, 0),IR(6987, 11)/* RayTminKHR */,IR(16, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5326,IR(0, 0),IR(7008, 11)/* RayTmaxKHR */,IR(17, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5327,IR(0, 0),IR(7029, 23)/* InstanceCustomIndexKHR */,IR(18, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5330,IR(0, 0),IR(7074, 17)/* ObjectToWorldKHR */,IR(19, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5331,IR(0, 0),IR(7107, 17)/* WorldToObjectKHR */,IR(20, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5332,IR(0, 0),IR(7140, 7)/* HitTNV */,IR(0, 0),IR(56, 1),IR(26, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5333,IR(0, 0),IR(7147, 11)/* HitKindKHR */,IR(21, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5334,IR(0, 0),IR(7168, 17)/* CurrentRayTimeNV */,IR(0, 0),IR(57, 1),IR(27, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5335,IR(0, 0),IR(7208, 30)/* HitTriangleVertexPositionsKHR */,IR(0, 0),IR(58, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5337,IR(0, 0),IR(7265, 34)/* HitMicroTriangleVertexPositionsNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5344,IR(0, 0),IR(7332, 37)/* HitMicroTriangleVertexBarycentricsNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5351,IR(0, 0),IR(7369, 20)/* IncomingRayFlagsKHR */,IR(22, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5352,IR(0, 0),IR(7408, 20)/* RayGeometryIndexKHR */,IR(0, 0),IR(60, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5359,IR(0, 0),IR(7428, 14)/* HitIsSphereNV */,IR(0, 0),IR(61, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5360,IR(0, 0),IR(7470, 11)/* HitIsLSSNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5361,IR(0, 0),IR(7520, 20)/* HitSpherePositionNV */,IR(0, 0),IR(61, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5374,IR(0, 0),IR(7540, 13)/* WarpsPerSMNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5375,IR(0, 0),IR(7572, 10)/* SMCountNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5376,IR(0, 0),IR(7582, 9)/* WarpIDNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5377,IR(0, 0),IR(7591, 7)/* SMIDNV */,IR(0, 0),IR(63, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5396,IR(0, 0),IR(7598, 18)/* HitLSSPositionsNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5405,IR(0, 0),IR(7616, 34)/* HitKindFrontFacingMicroTriangleNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5406,IR(0, 0),IR(7650, 33)/* HitKindBackFacingMicroTriangleNV */,IR(0, 0),IR(59, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5420,IR(0, 0),IR(7683, 18)/* HitSphereRadiusNV */,IR(0, 0),IR(61, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5421,IR(0, 0),IR(7701, 14)/* HitLSSRadiiNV */,IR(0, 0),IR(62, 1),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {5436,IR(0, 0),IR(7715, 12)/* ClusterIDNV */,IR(0, 0),IR(64, 1),IR(31, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {6021,IR(0, 0),IR(7768, 12)/* CullMaskKHR */,IR(0, 0),IR(65, 1),IR(32, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_BUILT_IN
  {0,IR(0, 0),IR(7795, 7)/* Matrix */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {1,IR(0, 0),IR(4666, 7)/* Shader */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {2,IR(0, 0),IR(4741, 9)/* Geometry */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {3,IR(0, 0),IR(4750, 13)/* Tessellation */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4,IR(0, 0),IR(4554, 10)/* Addresses */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5,IR(0, 0),IR(7802, 8)/* Linkage */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6,IR(0, 0),IR(4508, 7)/* Kernel */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {7,IR(0, 0),IR(7810, 9)/* Vector16 */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {8,IR(0, 0),IR(7819, 14)/* Float16Buffer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {9,IR(0, 0),IR(7833, 8)/* Float16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {10,IR(0, 0),IR(7841, 8)/* Float64 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {11,IR(0, 0),IR(7849, 6)/* Int64 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {12,IR(0, 0),IR(7855, 13)/* Int64Atomics */,IR(0, 0),IR(67, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {13,IR(0, 0),IR(7868, 11)/* ImageBasic */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {14,IR(0, 0),IR(7879, 15)/* ImageReadWrite */,IR(0, 0),IR(68, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {15,IR(0, 0),IR(7894, 12)/* ImageMipmap */,IR(0, 0),IR(68, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {17,IR(0, 0),IR(7906, 6)/* Pipes */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {18,IR(0, 0),IR(7912, 7)/* Groups */,IR(0, 0),IR(1, 0),IR(33, 1),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {19,IR(0, 0),IR(7919, 14)/* DeviceEnqueue */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {20,IR(0, 0),IR(7933, 15)/* LiteralSampler */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {21,IR(0, 0),IR(7948, 14)/* AtomicStorage */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {22,IR(0, 0),IR(7962, 6)/* Int16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {23,IR(0, 0),IR(7968, 22)/* TessellationPointSize */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {24,IR(0, 0),IR(7990, 18)/* GeometryPointSize */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {25,IR(0, 0),IR(8008, 20)/* ImageGatherExtended */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {27,IR(0, 0),IR(8028, 24)/* StorageImageMultisample */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {28,IR(0, 0),IR(8052, 34)/* UniformBufferArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {29,IR(0, 0),IR(8086, 33)/* SampledImageArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {30,IR(0, 0),IR(8119, 34)/* StorageBufferArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {31,IR(0, 0),IR(8153, 33)/* StorageImageArrayDynamicIndexing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {32,IR(0, 0),IR(4683, 13)/* ClipDistance */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {33,IR(0, 0),IR(4696, 13)/* CullDistance */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {34,IR(0, 0),IR(8186, 15)/* ImageCubeArray */,IR(0, 0),IR(70, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {35,IR(0, 0),IR(5022, 18)/* SampleRateShading */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {36,IR(0, 0),IR(8218, 10)/* ImageRect */,IR(0, 0),IR(71, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {37,IR(0, 0),IR(8228, 12)/* SampledRect */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {38,IR(0, 0),IR(8240, 15)/* GenericPointer */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {39,IR(0, 0),IR(8255, 5)/* Int8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {40,IR(0, 0),IR(8260, 16)/* InputAttachment */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {41,IR(0, 0),IR(8276, 16)/* SparseResidency */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {42,IR(0, 0),IR(8292, 7)/* MinLod */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {43,IR(0, 0),IR(8299, 10)/* Sampled1D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {44,IR(0, 0),IR(8309, 8)/* Image1D */,IR(0, 0),IR(72, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {45,IR(0, 0),IR(8201, 17)/* SampledCubeArray */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {46,IR(0, 0),IR(8317, 14)/* SampledBuffer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {47,IR(0, 0),IR(8331, 12)/* ImageBuffer */,IR(0, 0),IR(73, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {48,IR(0, 0),IR(8343, 13)/* ImageMSArray */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {49,IR(0, 0),IR(8356, 28)/* StorageImageExtendedFormats */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {50,IR(0, 0),IR(8384, 11)/* ImageQuery */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {51,IR(0, 0),IR(8395, 18)/* DerivativeControl */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {52,IR(0, 0),IR(8413, 22)/* InterpolationFunction */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {53,IR(0, 0),IR(8435, 18)/* TransformFeedback */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {54,IR(0, 0),IR(8453, 16)/* GeometryStreams */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {55,IR(0, 0),IR(8469, 30)/* StorageImageReadWithoutFormat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {56,IR(0, 0),IR(8499, 31)/* StorageImageWriteWithoutFormat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {57,IR(0, 0),IR(4892, 14)/* MultiViewport */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {58,IR(0, 0),IR(8530, 17)/* SubgroupDispatch */,IR(0, 0),IR(74, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {59,IR(0, 0),IR(8547, 13)/* NamedBarrier */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {60,IR(0, 0),IR(8560, 12)/* PipeStorage */,IR(0, 0),IR(75, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {61,IR(0, 0),IR(5273, 16)/* GroupNonUniform */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {62,IR(0, 0),IR(8572, 20)/* GroupNonUniformVote */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {63,IR(0, 0),IR(8592, 26)/* GroupNonUniformArithmetic */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {64,IR(0, 0),IR(5528, 22)/* GroupNonUniformBallot */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {65,IR(0, 0),IR(8618, 23)/* GroupNonUniformShuffle */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {66,IR(0, 0),IR(8641, 31)/* GroupNonUniformShuffleRelative */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {67,IR(0, 0),IR(8672, 25)/* GroupNonUniformClustered */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {68,IR(0, 0),IR(8697, 20)/* GroupNonUniformQuad */,IR(0, 0),IR(76, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {69,IR(0, 0),IR(4838, 12)/* ShaderLayer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {70,IR(0, 0),IR(4906, 20)/* ShaderViewportIndex */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {71,IR(0, 0),IR(8717, 18)/* UniformDecoration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4165,IR(0, 0),IR(5430, 16)/* CoreBuiltinsARM */,IR(0, 0),IR(1, 0),IR(34, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4166,IR(0, 0),IR(8735, 28)/* TileImageColorReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4167,IR(0, 0),IR(8763, 28)/* TileImageDepthReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4168,IR(0, 0),IR(8791, 30)/* TileImageStencilReadAccessEXT */,IR(0, 0),IR(1, 0),IR(35, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4174,IR(0, 0),IR(8821, 11)/* TensorsARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4175,IR(0, 0),IR(8832, 37)/* StorageTensorArrayDynamicIndexingARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4176,IR(0, 0),IR(8869, 40)/* StorageTensorArrayNonUniformIndexingARM */,IR(0, 0),IR(1, 0),IR(36, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4201,IR(0, 0),IR(8909, 28)/* CooperativeMatrixLayoutsARM */,IR(0, 0),IR(1, 0),IR(37, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4422,IR(0, 0),IR(5755, 23)/* FragmentShadingRateKHR */,IR(0, 0),IR(3, 1),IR(7, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4423,IR(0, 0),IR(5289, 18)/* SubgroupBallotKHR */,IR(0, 0),IR(1, 0),IR(2, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4427,IR(0, 0),IR(5693, 15)/* DrawParameters */,IR(0, 0),IR(3, 1),IR(3, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4428,IR(0, 0),IR(8937, 33)/* WorkgroupMemoryExplicitLayoutKHR */,IR(0, 0),IR(3, 1),IR(38, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4429,IR(0, 0),IR(8970, 43)/* WorkgroupMemoryExplicitLayout8BitAccessKHR */,IR(0, 0),IR(77, 1),IR(38, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4430,IR(0, 0),IR(9013, 44)/* WorkgroupMemoryExplicitLayout16BitAccessKHR */,IR(0, 0),IR(77, 1),IR(38, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4431,IR(0, 0),IR(9057, 16)/* SubgroupVoteKHR */,IR(0, 0),IR(1, 0),IR(39, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4433,IR(0, 0),IR(9073, 25)/* StorageBuffer16BitAccess */,IR(23, 1),IR(1, 0),IR(40, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4434,IR(0, 0),IR(9126, 35)/* UniformAndStorageBuffer16BitAccess */,IR(24, 1),IR(78, 1),IR(40, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4435,IR(0, 0),IR(9178, 22)/* StoragePushConstant16 */,IR(0, 0),IR(1, 0),IR(40, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4436,IR(0, 0),IR(9200, 21)/* StorageInputOutput16 */,IR(0, 0),IR(1, 0),IR(40, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4437,IR(0, 0),IR(5790, 12)/* DeviceGroup */,IR(0, 0),IR(1, 0),IR(8, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4439,IR(0, 0),IR(5812, 10)/* MultiView */,IR(0, 0),IR(3, 1),IR(9, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4441,IR(0, 0),IR(9221, 30)/* VariablePointersStorageBuffer */,IR(0, 0),IR(3, 1),IR(41, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4442,IR(0, 0),IR(9251, 17)/* VariablePointers */,IR(0, 0),IR(79, 1),IR(41, 1),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4445,IR(0, 0),IR(9268, 17)/* AtomicStorageOps */,IR(0, 0),IR(80, 1),IR(42, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4447,IR(0, 0),IR(9285, 28)/* SampleMaskPostDepthCoverage */,IR(0, 0),IR(1, 0),IR(43, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4448,IR(0, 0),IR(9313, 24)/* StorageBuffer8BitAccess */,IR(0, 0),IR(1, 0),IR(44, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4449,IR(0, 0),IR(9337, 34)/* UniformAndStorageBuffer8BitAccess */,IR(0, 0),IR(81, 1),IR(44, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4450,IR(0, 0),IR(9371, 21)/* StoragePushConstant8 */,IR(0, 0),IR(1, 0),IR(44, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4464,IR(0, 0),IR(9392, 15)/* DenormPreserve */,IR(0, 0),IR(1, 0),IR(45, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4465,IR(0, 0),IR(9407, 18)/* DenormFlushToZero */,IR(0, 0),IR(1, 0),IR(45, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4466,IR(0, 0),IR(9425, 25)/* SignedZeroInfNanPreserve */,IR(0, 0),IR(1, 0),IR(45, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4467,IR(0, 0),IR(9450, 16)/* RoundingModeRTE */,IR(0, 0),IR(1, 0),IR(45, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4468,IR(0, 0),IR(9466, 16)/* RoundingModeRTZ */,IR(0, 0),IR(1, 0),IR(45, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4471,IR(0, 0),IR(9482, 23)/* RayQueryProvisionalKHR */,IR(0, 0),IR(3, 1),IR(46, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4472,IR(0, 0),IR(9505, 12)/* RayQueryKHR */,IR(0, 0),IR(3, 1),IR(46, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4473,IR(0, 0),IR(9517, 19)/* UntypedPointersKHR */,IR(0, 0),IR(1, 0),IR(47, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4478,IR(0, 0),IR(9536, 32)/* RayTraversalPrimitiveCullingKHR */,IR(0, 0),IR(82, 2),IR(48, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4479,IR(0, 0),IR(4776, 14)/* RayTracingKHR */,IR(0, 0),IR(3, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4484,IR(0, 0),IR(9568, 26)/* TextureSampleWeightedQCOM */,IR(0, 0),IR(1, 0),IR(50, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4485,IR(0, 0),IR(9594, 21)/* TextureBoxFilterQCOM */,IR(0, 0),IR(1, 0),IR(50, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4486,IR(0, 0),IR(9615, 22)/* TextureBlockMatchQCOM */,IR(0, 0),IR(1, 0),IR(50, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4495,IR(0, 0),IR(5852, 16)/* TileShadingQCOM */,IR(0, 0),IR(3, 1),IR(51, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {4498,IR(0, 0),IR(9637, 23)/* TextureBlockMatch2QCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5008,IR(0, 0),IR(9660, 16)/* Float16ImageAMD */,IR(0, 0),IR(3, 1),IR(53, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5009,IR(0, 0),IR(9676, 22)/* ImageGatherBiasLodAMD */,IR(0, 0),IR(3, 1),IR(54, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5010,IR(0, 0),IR(9698, 16)/* FragmentMaskAMD */,IR(0, 0),IR(3, 1),IR(55, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5013,IR(0, 0),IR(6089, 17)/* StencilExportEXT */,IR(0, 0),IR(3, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5015,IR(0, 0),IR(9714, 21)/* ImageReadWriteLodAMD */,IR(0, 0),IR(3, 1),IR(56, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5016,IR(0, 0),IR(9735, 14)/* Int64ImageEXT */,IR(0, 0),IR(3, 1),IR(57, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5055,IR(0, 0),IR(9749, 15)/* ShaderClockKHR */,IR(0, 0),IR(1, 0),IR(58, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5067,IR(0, 0),IR(6135, 18)/* ShaderEnqueueAMDX */,IR(0, 0),IR(3, 1),IR(59, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5087,IR(0, 0),IR(9764, 15)/* QuadControlKHR */,IR(0, 0),IR(1, 0),IR(60, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5112,IR(0, 0),IR(9779, 14)/* Int4TypeINTEL */,IR(0, 0),IR(1, 0),IR(61, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5114,IR(0, 0),IR(9793, 27)/* Int4CooperativeMatrixINTEL */,IR(0, 0),IR(84, 2),IR(61, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5116,IR(0, 0),IR(9841, 16)/* BFloat16TypeKHR */,IR(0, 0),IR(1, 0),IR(62, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5117,IR(0, 0),IR(9857, 22)/* BFloat16DotProductKHR */,IR(0, 0),IR(86, 1),IR(62, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5118,IR(0, 0),IR(9879, 29)/* BFloat16CooperativeMatrixKHR */,IR(0, 0),IR(87, 2),IR(62, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5249,IR(0, 0),IR(9908, 29)/* SampleMaskOverrideCoverageNV */,IR(0, 0),IR(25, 1),IR(63, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5251,IR(0, 0),IR(9937, 28)/* GeometryShaderPassthroughNV */,IR(0, 0),IR(69, 1),IR(64, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5254,IR(0, 0),IR(4850, 28)/* ShaderViewportIndexLayerEXT */,IR(25, 1),IR(89, 1),IR(65, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5255,IR(0, 0),IR(6184, 21)/* ShaderViewportMaskNV */,IR(0, 0),IR(90, 1),IR(67, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5259,IR(0, 0),IR(6225, 19)/* ShaderStereoViewNV */,IR(0, 0),IR(91, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5260,IR(0, 0),IR(6286, 20)/* PerViewAttributesNV */,IR(0, 0),IR(40, 1),IR(68, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5265,IR(0, 0),IR(6344, 24)/* FragmentFullyCoveredEXT */,IR(0, 0),IR(3, 1),IR(17, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5266,IR(0, 0),IR(4790, 14)/* MeshShadingNV */,IR(0, 0),IR(3, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5282,IR(0, 0),IR(9992, 17)/* ImageFootprintNV */,IR(0, 0),IR(1, 0),IR(69, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5283,IR(0, 0),IR(4804, 15)/* MeshShadingEXT */,IR(0, 0),IR(3, 1),IR(23, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5284,IR(0, 0),IR(6534, 23)/* FragmentBarycentricKHR */,IR(26, 1),IR(1, 0),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5288,IR(0, 0),IR(10031, 31)/* ComputeDerivativeGroupQuadsKHR */,IR(27, 1),IR(3, 1),IR(70, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5291,IR(0, 0),IR(6623, 19)/* FragmentDensityEXT */,IR(28, 1),IR(3, 1),IR(21, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5297,IR(0, 0),IR(10106, 29)/* GroupNonUniformPartitionedNV */,IR(0, 0),IR(1, 0),IR(72, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5301,IR(0, 0),IR(10135, 17)/* ShaderNonUniform */,IR(29, 1),IR(3, 1),IR(73, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5302,IR(0, 0),IR(10172, 23)/* RuntimeDescriptorArray */,IR(30, 1),IR(3, 1),IR(73, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5303,IR(0, 0),IR(10221, 36)/* InputAttachmentArrayDynamicIndexing */,IR(31, 1),IR(92, 1),IR(73, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5304,IR(0, 0),IR(10296, 39)/* UniformTexelBufferArrayDynamicIndexing */,IR(32, 1),IR(73, 1),IR(73, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5305,IR(0, 0),IR(10377, 39)/* StorageTexelBufferArrayDynamicIndexing */,IR(33, 1),IR(93, 1),IR(73, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5306,IR(0, 0),IR(10458, 37)/* UniformBufferArrayNonUniformIndexing */,IR(34, 1),IR(94, 1),IR(73, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5307,IR(0, 0),IR(10535, 36)/* SampledImageArrayNonUniformIndexing */,IR(35, 1),IR(94, 1),IR(73, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5308,IR(0, 0),IR(10610, 37)/* StorageBufferArrayNonUniformIndexing */,IR(36, 1),IR(94, 1),IR(73, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5309,IR(0, 0),IR(10687, 36)/* StorageImageArrayNonUniformIndexing */,IR(37, 1),IR(94, 1),IR(73, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5310,IR(0, 0),IR(10762, 39)/* InputAttachmentArrayNonUniformIndexing */,IR(38, 1),IR(95, 2),IR(73, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5311,IR(0, 0),IR(10843, 42)/* UniformTexelBufferArrayNonUniformIndexing */,IR(39, 1),IR(97, 2),IR(73, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5312,IR(0, 0),IR(10930, 42)/* StorageTexelBufferArrayNonUniformIndexing */,IR(40, 1),IR(99, 2),IR(73, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5336,IR(0, 0),IR(7238, 27)/* RayTracingPositionFetchKHR */,IR(0, 0),IR(3, 1),IR(74, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5340,IR(0, 0),IR(4763, 13)/* RayTracingNV */,IR(0, 0),IR(3, 1),IR(26, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5341,IR(0, 0),IR(7185, 23)/* RayTracingMotionBlurNV */,IR(0, 0),IR(3, 1),IR(27, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5345,IR(0, 0),IR(11017, 18)/* VulkanMemoryModel */,IR(41, 1),IR(1, 0),IR(75, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5346,IR(0, 0),IR(11056, 29)/* VulkanMemoryModelDeviceScope */,IR(42, 1),IR(1, 0),IR(75, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5347,IR(0, 0),IR(4626, 31)/* PhysicalStorageBufferAddresses */,IR(43, 1),IR(3, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5350,IR(0, 0),IR(11151, 32)/* ComputeDerivativeGroupLinearKHR */,IR(44, 1),IR(3, 1),IR(70, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5353,IR(0, 0),IR(11214, 25)/* RayTracingProvisionalKHR */,IR(0, 0),IR(3, 1),IR(28, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5357,IR(0, 0),IR(11239, 20)/* CooperativeMatrixNV */,IR(0, 0),IR(3, 1),IR(76, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5363,IR(0, 0),IR(11259, 33)/* FragmentShaderSampleInterlockEXT */,IR(0, 0),IR(3, 1),IR(77, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5372,IR(0, 0),IR(11292, 38)/* FragmentShaderShadingRateInterlockEXT */,IR(0, 0),IR(3, 1),IR(77, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5373,IR(0, 0),IR(7553, 19)/* ShaderSMBuiltinsNV */,IR(0, 0),IR(3, 1),IR(30, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5378,IR(0, 0),IR(11330, 32)/* FragmentShaderPixelInterlockEXT */,IR(0, 0),IR(3, 1),IR(77, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5379,IR(0, 0),IR(11362, 25)/* DemoteToHelperInvocation */,IR(45, 1),IR(3, 1),IR(78, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5380,IR(0, 0),IR(11415, 23)/* DisplacementMicromapNV */,IR(0, 0),IR(3, 1),IR(79, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5381,IR(0, 0),IR(11438, 29)/* RayTracingOpacityMicromapEXT */,IR(0, 0),IR(3, 1),IR(80, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5383,IR(0, 0),IR(11467, 26)/* ShaderInvocationReorderNV */,IR(0, 0),IR(60, 1),IR(81, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5390,IR(0, 0),IR(11493, 18)/* BindlessTextureNV */,IR(0, 0),IR(1, 0),IR(82, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5391,IR(0, 0),IR(11511, 25)/* RayQueryPositionFetchKHR */,IR(0, 0),IR(3, 1),IR(74, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5394,IR(0, 0),IR(11536, 20)/* CooperativeVectorNV */,IR(0, 0),IR(1, 0),IR(83, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5404,IR(0, 0),IR(11556, 22)/* AtomicFloat16VectorNV */,IR(0, 0),IR(1, 0),IR(84, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5409,IR(0, 0),IR(7299, 33)/* RayTracingDisplacementMicromapNV */,IR(0, 0),IR(60, 1),IR(79, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5414,IR(0, 0),IR(11578, 18)/* RawAccessChainsNV */,IR(0, 0),IR(1, 0),IR(85, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5418,IR(0, 0),IR(7442, 28)/* RayTracingSpheresGeometryNV */,IR(0, 0),IR(1, 0),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5419,IR(0, 0),IR(7481, 39)/* RayTracingLinearSweptSpheresGeometryNV */,IR(0, 0),IR(1, 0),IR(29, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5430,IR(0, 0),IR(11596, 30)/* CooperativeMatrixReductionsNV */,IR(0, 0),IR(1, 0),IR(86, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5431,IR(0, 0),IR(11626, 31)/* CooperativeMatrixConversionsNV */,IR(0, 0),IR(1, 0),IR(86, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5432,IR(0, 0),IR(11657, 40)/* CooperativeMatrixPerElementOperationsNV */,IR(0, 0),IR(1, 0),IR(86, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5433,IR(0, 0),IR(11697, 36)/* CooperativeMatrixTensorAddressingNV */,IR(0, 0),IR(1, 0),IR(86, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5434,IR(0, 0),IR(11733, 30)/* CooperativeMatrixBlockLoadsNV */,IR(0, 0),IR(1, 0),IR(86, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5435,IR(0, 0),IR(11763, 28)/* CooperativeVectorTrainingNV */,IR(0, 0),IR(1, 0),IR(83, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5437,IR(0, 0),IR(7727, 41)/* RayTracingClusterAccelerationStructureNV */,IR(0, 0),IR(60, 1),IR(31, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5439,IR(0, 0),IR(11791, 19)/* TensorAddressingNV */,IR(0, 0),IR(1, 0),IR(87, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5568,IR(0, 0),IR(11810, 21)/* SubgroupShuffleINTEL */,IR(0, 0),IR(1, 0),IR(88, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5569,IR(0, 0),IR(11831, 27)/* SubgroupBufferBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(88, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5570,IR(0, 0),IR(11858, 26)/* SubgroupImageBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(88, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5579,IR(0, 0),IR(11884, 31)/* SubgroupImageMediaBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(89, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5582,IR(0, 0),IR(11915, 21)/* RoundToInfinityINTEL */,IR(0, 0),IR(1, 0),IR(90, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5583,IR(0, 0),IR(11936, 23)/* FloatingPointModeINTEL */,IR(0, 0),IR(1, 0),IR(90, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5584,IR(0, 0),IR(11959, 23)/* IntegerFunctions2INTEL */,IR(0, 0),IR(1, 0),IR(91, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5603,IR(0, 0),IR(11982, 22)/* FunctionPointersINTEL */,IR(0, 0),IR(1, 0),IR(92, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5604,IR(0, 0),IR(12004, 24)/* IndirectReferencesINTEL */,IR(0, 0),IR(1, 0),IR(92, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5606,IR(0, 0),IR(12028, 9)/* AsmINTEL */,IR(0, 0),IR(1, 0),IR(93, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5612,IR(0, 0),IR(12037, 23)/* AtomicFloat32MinMaxEXT */,IR(0, 0),IR(1, 0),IR(94, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5613,IR(0, 0),IR(12060, 23)/* AtomicFloat64MinMaxEXT */,IR(0, 0),IR(1, 0),IR(94, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5616,IR(0, 0),IR(12083, 23)/* AtomicFloat16MinMaxEXT */,IR(0, 0),IR(1, 0),IR(94, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5617,IR(0, 0),IR(12106, 19)/* VectorComputeINTEL */,IR(0, 0),IR(101, 1),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5619,IR(0, 0),IR(12125, 15)/* VectorAnyINTEL */,IR(0, 0),IR(1, 0),IR(95, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5629,IR(0, 0),IR(12140, 16)/* ExpectAssumeKHR */,IR(0, 0),IR(1, 0),IR(96, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5696,IR(0, 0),IR(12156, 33)/* SubgroupAvcMotionEstimationINTEL */,IR(0, 0),IR(1, 0),IR(97, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5697,IR(0, 0),IR(12189, 38)/* SubgroupAvcMotionEstimationIntraINTEL */,IR(0, 0),IR(1, 0),IR(97, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5698,IR(0, 0),IR(12227, 39)/* SubgroupAvcMotionEstimationChromaINTEL */,IR(0, 0),IR(1, 0),IR(97, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5817,IR(0, 0),IR(12266, 25)/* VariableLengthArrayINTEL */,IR(0, 0),IR(1, 0),IR(98, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5821,IR(0, 0),IR(12291, 26)/* FunctionFloatControlINTEL */,IR(0, 0),IR(1, 0),IR(90, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5824,IR(0, 0),IR(12317, 26)/* FPGAMemoryAttributesINTEL */,IR(0, 0),IR(1, 0),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5837,IR(0, 0),IR(12343, 20)/* FPFastMathModeINTEL */,IR(0, 0),IR(0, 1),IR(100, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5844,IR(0, 0),IR(12363, 32)/* ArbitraryPrecisionIntegersINTEL */,IR(0, 0),IR(1, 0),IR(101, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5845,IR(0, 0),IR(12395, 37)/* ArbitraryPrecisionFloatingPointINTEL */,IR(0, 0),IR(1, 0),IR(102, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5886,IR(0, 0),IR(12432, 30)/* UnstructuredLoopControlsINTEL */,IR(0, 0),IR(1, 0),IR(103, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5888,IR(0, 0),IR(12462, 22)/* FPGALoopControlsINTEL */,IR(0, 0),IR(1, 0),IR(104, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5892,IR(0, 0),IR(12484, 22)/* KernelAttributesINTEL */,IR(0, 0),IR(1, 0),IR(105, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5897,IR(0, 0),IR(12506, 26)/* FPGAKernelAttributesINTEL */,IR(0, 0),IR(1, 0),IR(105, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5898,IR(0, 0),IR(12532, 24)/* FPGAMemoryAccessesINTEL */,IR(0, 0),IR(1, 0),IR(106, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5904,IR(0, 0),IR(12556, 27)/* FPGAClusterAttributesINTEL */,IR(0, 0),IR(1, 0),IR(107, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5906,IR(0, 0),IR(12583, 14)/* LoopFuseINTEL */,IR(0, 0),IR(1, 0),IR(108, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5908,IR(0, 0),IR(12597, 20)/* FPGADSPControlINTEL */,IR(0, 0),IR(1, 0),IR(109, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5910,IR(0, 0),IR(12617, 26)/* MemoryAccessAliasingINTEL */,IR(0, 0),IR(1, 0),IR(110, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5916,IR(0, 0),IR(12643, 40)/* FPGAInvocationPipeliningAttributesINTEL */,IR(0, 0),IR(1, 0),IR(111, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5920,IR(0, 0),IR(12683, 24)/* FPGABufferLocationINTEL */,IR(0, 0),IR(1, 0),IR(112, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5922,IR(0, 0),IR(12707, 34)/* ArbitraryPrecisionFixedPointINTEL */,IR(0, 0),IR(1, 0),IR(113, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5935,IR(0, 0),IR(12741, 23)/* USMStorageClassesINTEL */,IR(0, 0),IR(1, 0),IR(114, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5939,IR(0, 0),IR(12764, 29)/* RuntimeAlignedAttributeINTEL */,IR(0, 0),IR(1, 0),IR(115, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5943,IR(0, 0),IR(12793, 13)/* IOPipesINTEL */,IR(0, 0),IR(1, 0),IR(116, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5945,IR(0, 0),IR(12806, 19)/* BlockingPipesINTEL */,IR(0, 0),IR(1, 0),IR(117, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {5948,IR(0, 0),IR(12825, 13)/* FPGARegINTEL */,IR(0, 0),IR(1, 0),IR(118, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6016,IR(0, 0),IR(12838, 19)/* DotProductInputAll */,IR(46, 1),IR(1, 0),IR(119, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6017,IR(0, 0),IR(12879, 22)/* DotProductInput4x8Bit */,IR(47, 1),IR(102, 1),IR(119, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6018,IR(0, 0),IR(12926, 28)/* DotProductInput4x8BitPacked */,IR(48, 1),IR(1, 0),IR(119, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6019,IR(0, 0),IR(12985, 11)/* DotProduct */,IR(49, 1),IR(1, 0),IR(119, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6020,IR(0, 0),IR(7780, 15)/* RayCullMaskKHR */,IR(0, 0),IR(1, 0),IR(32, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6022,IR(0, 0),IR(9820, 21)/* CooperativeMatrixKHR */,IR(0, 0),IR(1, 0),IR(120, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6024,IR(0, 0),IR(13010, 24)/* ReplicatedCompositesEXT */,IR(0, 0),IR(1, 0),IR(121, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6025,IR(0, 0),IR(13034, 16)/* BitInstructions */,IR(0, 0),IR(1, 0),IR(122, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6026,IR(0, 0),IR(13050, 25)/* GroupNonUniformRotateKHR */,IR(0, 0),IR(76, 1),IR(123, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6029,IR(0, 0),IR(13075, 15)/* FloatControls2 */,IR(0, 0),IR(1, 0),IR(124, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6033,IR(0, 0),IR(13090, 20)/* AtomicFloat32AddEXT */,IR(0, 0),IR(1, 0),IR(125, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6034,IR(0, 0),IR(13110, 20)/* AtomicFloat64AddEXT */,IR(0, 0),IR(1, 0),IR(125, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6089,IR(0, 0),IR(13130, 20)/* LongCompositesINTEL */,IR(0, 0),IR(1, 0),IR(126, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6094,IR(0, 0),IR(13150, 11)/* OptNoneEXT */,IR(50, 1),IR(1, 0),IR(127, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6095,IR(0, 0),IR(13174, 20)/* AtomicFloat16AddEXT */,IR(0, 0),IR(1, 0),IR(129, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6114,IR(0, 0),IR(13194, 21)/* DebugInfoModuleINTEL */,IR(0, 0),IR(1, 0),IR(130, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6115,IR(0, 0),IR(13215, 24)/* BFloat16ConversionINTEL */,IR(0, 0),IR(1, 0),IR(131, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6141,IR(0, 0),IR(13239, 18)/* SplitBarrierINTEL */,IR(0, 0),IR(1, 0),IR(132, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6144,IR(0, 0),IR(13257, 19)/* ArithmeticFenceEXT */,IR(0, 0),IR(1, 0),IR(133, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6150,IR(0, 0),IR(13276, 29)/* FPGAClusterAttributesV2INTEL */,IR(0, 0),IR(103, 1),IR(107, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6161,IR(0, 0),IR(13305, 28)/* FPGAKernelAttributesv2INTEL */,IR(0, 0),IR(104, 1),IR(105, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6162,IR(0, 0),IR(13333, 18)/* TaskSequenceINTEL */,IR(0, 0),IR(1, 0),IR(134, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6169,IR(0, 0),IR(13351, 16)/* FPMaxErrorINTEL */,IR(0, 0),IR(1, 0),IR(135, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6171,IR(0, 0),IR(13367, 24)/* FPGALatencyControlINTEL */,IR(0, 0),IR(1, 0),IR(136, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6174,IR(0, 0),IR(13391, 28)/* FPGAArgumentInterfacesINTEL */,IR(0, 0),IR(1, 0),IR(137, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6187,IR(0, 0),IR(13419, 30)/* GlobalVariableHostAccessINTEL */,IR(0, 0),IR(1, 0),IR(138, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6189,IR(0, 0),IR(13449, 35)/* GlobalVariableFPGADecorationsINTEL */,IR(0, 0),IR(1, 0),IR(139, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6220,IR(0, 0),IR(13484, 28)/* SubgroupBufferPrefetchINTEL */,IR(0, 0),IR(1, 0),IR(140, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6228,IR(0, 0),IR(13512, 23)/* Subgroup2DBlockIOINTEL */,IR(0, 0),IR(1, 0),IR(141, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6229,IR(0, 0),IR(13535, 30)/* Subgroup2DBlockTransformINTEL */,IR(0, 0),IR(105, 1),IR(141, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6230,IR(0, 0),IR(13565, 30)/* Subgroup2DBlockTransposeINTEL */,IR(0, 0),IR(105, 1),IR(141, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6236,IR(0, 0),IR(13595, 38)/* SubgroupMatrixMultiplyAccumulateINTEL */,IR(0, 0),IR(1, 0),IR(142, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6241,IR(0, 0),IR(13633, 28)/* TernaryBitwiseFunctionINTEL */,IR(0, 0),IR(1, 0),IR(143, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6400,IR(0, 0),IR(13661, 26)/* GroupUniformArithmeticKHR */,IR(0, 0),IR(1, 0),IR(144, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6425,IR(0, 0),IR(13687, 27)/* TensorFloat32RoundingINTEL */,IR(0, 0),IR(1, 0),IR(145, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6427,IR(0, 0),IR(13714, 25)/* MaskedGatherScatterINTEL */,IR(0, 0),IR(1, 0),IR(146, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6441,IR(0, 0),IR(13739, 19)/* CacheControlsINTEL */,IR(0, 0),IR(1, 0),IR(147, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {6460,IR(0, 0),IR(13758, 20)/* RegisterLimitsINTEL */,IR(0, 0),IR(1, 0),IR(148, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_CAPABILITY
  {0,IR(0, 0),IR(13778, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(13790, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(13798, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {3,IR(0, 0),IR(13806, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(13812, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(13819, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(13830, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(13839, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(13852, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(13858, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(13868, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(13874, 15)/* ImportedModule */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {1,IR(0, 0),IR(13889, 20)/* ImportedDeclaration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {0,IR(0, 0),IR(13909, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(13914, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(13930, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(13944, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(13957, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(13969, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(13986, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(13998, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(14013, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(14026, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(14041, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(14059, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(14076, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(14097, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(14117, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(14137, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {16384,IR(0, 0),IR(14153, 16)/* FlagIsEnumClass */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {32768,IR(0, 0),IR(14169, 20)/* FlagTypePassByValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {65536,IR(0, 0),IR(14189, 24)/* FlagTypePassByReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(14213, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {1,IR(0, 0),IR(14219, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {2,IR(0, 0),IR(14224, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {3,IR(0, 1),IR(14263, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {4,IR(1, 2),IR(14274, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {5,IR(0, 0),IR(14283, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {6,IR(0, 0),IR(14288, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {7,IR(0, 0),IR(14295, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {8,IR(0, 1),IR(14306, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {9,IR(1, 2),IR(14313, 9)/* Fragment */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {0,IR(0, 0),IR(14322, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(14332, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(14345, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {3,IR(0, 0),IR(14358, 11)/* AtomicType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(14369, 10)/* Float16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1,IR(0, 0),IR(14379, 10)/* Float32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {2,IR(0, 0),IR(14389, 10)/* Float64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {3,IR(0, 0),IR(14399, 13)/* SignedInt8NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {4,IR(0, 0),IR(14412, 14)/* SignedInt16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {5,IR(0, 0),IR(14426, 14)/* SignedInt32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {6,IR(0, 0),IR(14440, 14)/* SignedInt64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {7,IR(0, 0),IR(14454, 15)/* UnsignedInt8NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {8,IR(0, 0),IR(14469, 16)/* UnsignedInt16NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {9,IR(0, 0),IR(14485, 16)/* UnsignedInt32NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {10,IR(0, 0),IR(14501, 16)/* UnsignedInt64NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491000,IR(0, 0),IR(14517, 19)/* SignedInt8PackedNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491001,IR(0, 0),IR(14536, 21)/* UnsignedInt8PackedNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491002,IR(0, 0),IR(14557, 12)/* FloatE4M3NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {1000491003,IR(0, 0),IR(14569, 12)/* FloatE5M2NV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COMPONENT_TYPE
  {0,IR(0, 0),IR(14581, 12)/* RowMajorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {1,IR(0, 0),IR(14593, 15)/* ColumnMajorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {4202,IR(0, 0),IR(14608, 25)/* RowBlockedInterleavedARM */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {4203,IR(0, 0),IR(14633, 28)/* ColumnBlockedInterleavedARM */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {0,IR(0, 0),IR(14661, 8)/* NoneKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {1,IR(0, 0),IR(14669, 27)/* MatrixASignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {2,IR(0, 0),IR(14696, 27)/* MatrixBSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {4,IR(0, 0),IR(14723, 27)/* MatrixCSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {8,IR(0, 0),IR(14750, 32)/* MatrixResultSignedComponentsKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {16,IR(0, 0),IR(14782, 26)/* SaturatingAccumulationKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {1,IR(0, 0),IR(14808, 4)/* Row */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {2,IR(0, 0),IR(14812, 7)/* Column */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {4,IR(0, 0),IR(14819, 4)/* 2x2 */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {0,IR(0, 0),IR(14823, 11)/* MatrixAKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {1,IR(0, 0),IR(14834, 11)/* MatrixBKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {2,IR(0, 0),IR(14845, 21)/* MatrixAccumulatorKHR */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {0,IR(0, 0),IR(14866, 11)/* RowMajorNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {1,IR(0, 0),IR(14877, 14)/* ColumnMajorNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {2,IR(0, 0),IR(14891, 21)/* InferencingOptimalNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {3,IR(0, 0),IR(14912, 18)/* TrainingOptimalNV */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {0,IR(0, 0),IR(13778, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(13790, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(13798, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(13806, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(13812, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(13819, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(13830, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {8,IR(0, 0),IR(13839, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(13852, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(13858, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(13868, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(13909, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(13914, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(13930, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(13944, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(13957, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(13969, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(13986, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(13998, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(14013, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(14026, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(14041, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(14059, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(14076, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(14097, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(14117, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(14137, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(14213, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {1,IR(0, 0),IR(14219, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {2,IR(0, 0),IR(14224, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {3,IR(0, 1),IR(14263, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {4,IR(1, 2),IR(14274, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {5,IR(0, 0),IR(14283, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {6,IR(0, 0),IR(14288, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {7,IR(0, 0),IR(14295, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {8,IR(0, 1),IR(14306, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_OPERATION
  {0,IR(0, 0),IR(14322, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(14332, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(14345, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(14930, 17)/* RelaxedPrecision */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {1,IR(0, 1),IR(14947, 7)/* SpecId */,IR(0, 0),IR(106, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {2,IR(0, 0),IR(14954, 6)/* Block */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {3,IR(0, 0),IR(14960, 12)/* BufferBlock */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),SPV_SPIRV_VERSION_WORD(1,3)}, // SPV_OPERAND_TYPE_DECORATION
  {4,IR(0, 0),IR(14972, 9)/* RowMajor */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5,IR(0, 0),IR(14981, 9)/* ColMajor */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6,IR(0, 1),IR(14990, 12)/* ArrayStride */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {7,IR(0, 1),IR(15002, 13)/* MatrixStride */,IR(0, 0),IR(66, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {8,IR(0, 0),IR(15015, 11)/* GLSLShared */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {9,IR(0, 0),IR(15026, 11)/* GLSLPacked */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {10,IR(0, 0),IR(15037, 8)/* CPacked */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {11,IR(3, 1),IR(15071, 8)/* BuiltIn */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {13,IR(0, 0),IR(15079, 14)/* NoPerspective */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {14,IR(0, 0),IR(15093, 5)/* Flat */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {15,IR(0, 0),IR(15098, 6)/* Patch */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {16,IR(0, 0),IR(15104, 9)/* Centroid */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {17,IR(0, 0),IR(15113, 7)/* Sample */,IR(0, 0),IR(25, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {18,IR(0, 0),IR(15120, 10)/* Invariant */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {19,IR(0, 0),IR(15130, 9)/* Restrict */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {20,IR(0, 0),IR(15139, 8)/* Aliased */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {21,IR(0, 0),IR(15147, 9)/* Volatile */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {22,IR(0, 0),IR(15156, 9)/* Constant */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {23,IR(0, 0),IR(15165, 9)/* Coherent */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {24,IR(0, 0),IR(15174, 12)/* NonWritable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {25,IR(0, 0),IR(15186, 12)/* NonReadable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {26,IR(0, 0),IR(15198, 8)/* Uniform */,IR(0, 0),IR(108, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {27,IR(4, 1),IR(15232, 10)/* UniformId */,IR(0, 0),IR(108, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {28,IR(0, 0),IR(15242, 20)/* SaturatedConversion */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {29,IR(0, 1),IR(15262, 7)/* Stream */,IR(0, 0),IR(110, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {30,IR(0, 1),IR(15269, 9)/* Location */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {31,IR(0, 1),IR(15278, 10)/* Component */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {32,IR(0, 1),IR(15288, 6)/* Index */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {33,IR(0, 1),IR(15294, 8)/* Binding */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {34,IR(0, 1),IR(15302, 14)/* DescriptorSet */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {35,IR(0, 1),IR(15316, 7)/* Offset */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {36,IR(0, 1),IR(15323, 10)/* XfbBuffer */,IR(0, 0),IR(111, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {37,IR(0, 1),IR(15333, 10)/* XfbStride */,IR(0, 0),IR(111, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {38,IR(5, 1),IR(15389, 14)/* FuncParamAttr */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {39,IR(6, 1),IR(15437, 15)/* FPRoundingMode */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {40,IR(7, 1),IR(15487, 15)/* FPFastMathMode */,IR(0, 0),IR(112, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {41,IR(8, 2),IR(15564, 18)/* LinkageAttributes */,IR(0, 0),IR(114, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {42,IR(0, 0),IR(15582, 14)/* NoContraction */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {43,IR(0, 1),IR(15596, 21)/* InputAttachmentIndex */,IR(0, 0),IR(92, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {44,IR(0, 1),IR(15617, 10)/* Alignment */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {45,IR(0, 1),IR(15627, 14)/* MaxByteOffset */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {46,IR(10, 1),IR(15661, 12)/* AlignmentId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {47,IR(10, 1),IR(15673, 16)/* MaxByteOffsetId */,IR(0, 0),IR(1, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4469,IR(0, 0),IR(15689, 13)/* NoSignedWrap */,IR(0, 0),IR(1, 0),IR(149, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4470,IR(0, 0),IR(15702, 15)/* NoUnsignedWrap */,IR(0, 0),IR(1, 0),IR(149, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4487,IR(0, 0),IR(15717, 18)/* WeightTextureQCOM */,IR(0, 0),IR(1, 0),IR(50, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4488,IR(0, 0),IR(15735, 22)/* BlockMatchTextureQCOM */,IR(0, 0),IR(1, 0),IR(50, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4499,IR(0, 0),IR(15757, 22)/* BlockMatchSamplerQCOM */,IR(0, 0),IR(1, 0),IR(52, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {4999,IR(0, 0),IR(15779, 18)/* ExplicitInterpAMD */,IR(0, 0),IR(1, 0),IR(10, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5019,IR(10, 1),IR(15797, 32)/* NodeSharesPayloadLimitsWithAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5020,IR(10, 1),IR(15829, 20)/* NodeMaxPayloadsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5078,IR(0, 0),IR(15849, 23)/* TrackFinishWritingAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5091,IR(10, 1),IR(15872, 20)/* PayloadNodeNameAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5098,IR(10, 1),IR(15892, 25)/* PayloadNodeBaseIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5099,IR(0, 0),IR(15917, 27)/* PayloadNodeSparseArrayAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5100,IR(10, 1),IR(15944, 25)/* PayloadNodeArraySizeAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5105,IR(0, 0),IR(15969, 28)/* PayloadDispatchIndirectAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5248,IR(0, 0),IR(15997, 19)/* OverrideCoverageNV */,IR(0, 0),IR(115, 1),IR(63, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5250,IR(0, 0),IR(16016, 14)/* PassthroughNV */,IR(0, 0),IR(116, 1),IR(64, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5252,IR(0, 0),IR(16030, 19)/* ViewportRelativeNV */,IR(0, 0),IR(91, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5256,IR(0, 1),IR(16049, 28)/* SecondaryViewportRelativeNV */,IR(0, 0),IR(46, 1),IR(14, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5271,IR(0, 0),IR(16077, 16)/* PerPrimitiveEXT */,IR(51, 1),IR(117, 2),IR(150, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5272,IR(0, 0),IR(16108, 10)/* PerViewNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5273,IR(0, 0),IR(16118, 10)/* PerTaskNV */,IR(0, 0),IR(50, 1),IR(18, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5285,IR(0, 0),IR(16128, 13)/* PerVertexKHR */,IR(52, 1),IR(51, 1),IR(19, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5300,IR(0, 0),IR(16153, 11)/* NonUniform */,IR(53, 1),IR(94, 1),IR(73, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5355,IR(0, 0),IR(16178, 16)/* RestrictPointer */,IR(54, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5356,IR(0, 0),IR(16213, 15)/* AliasedPointer */,IR(55, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5386,IR(0, 0),IR(16246, 30)/* HitObjectShaderRecordBufferNV */,IR(0, 0),IR(119, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5398,IR(0, 0),IR(16276, 18)/* BindlessSamplerNV */,IR(0, 0),IR(120, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5399,IR(0, 0),IR(16294, 16)/* BindlessImageNV */,IR(0, 0),IR(120, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5400,IR(0, 0),IR(16310, 15)/* BoundSamplerNV */,IR(0, 0),IR(120, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5401,IR(0, 0),IR(16325, 13)/* BoundImageNV */,IR(0, 0),IR(120, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5599,IR(0, 1),IR(16338, 14)/* SIMTCallINTEL */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5602,IR(0, 0),IR(16352, 26)/* ReferencedIndirectlyINTEL */,IR(0, 0),IR(122, 1),IR(92, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5607,IR(11, 1),IR(16378, 13)/* ClobberINTEL */,IR(0, 0),IR(123, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5608,IR(0, 0),IR(16391, 17)/* SideEffectsINTEL */,IR(0, 0),IR(123, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5624,IR(0, 0),IR(16408, 27)/* VectorComputeVariableINTEL */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5625,IR(0, 1),IR(16435, 21)/* FuncParamIOKindINTEL */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5626,IR(0, 0),IR(16456, 27)/* VectorComputeFunctionINTEL */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5627,IR(0, 0),IR(16483, 15)/* StackCallINTEL */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5628,IR(0, 1),IR(16498, 26)/* GlobalVariableOffsetINTEL */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5634,IR(10, 1),IR(16524, 14)/* CounterBuffer */,IR(56, 1),IR(1, 0),IR(152, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5635,IR(11, 1),IR(16562, 13)/* UserSemantic */,IR(57, 1),IR(1, 0),IR(152, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5636,IR(11, 1),IR(16594, 15)/* UserTypeGOOGLE */,IR(0, 0),IR(1, 0),IR(153, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5822,IR(12, 2),IR(16609, 26)/* FunctionRoundingModeINTEL */,IR(0, 0),IR(124, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5823,IR(14, 2),IR(16666, 24)/* FunctionDenormModeINTEL */,IR(0, 0),IR(124, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5825,IR(0, 0),IR(16690, 14)/* RegisterINTEL */,IR(0, 0),IR(125, 1),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5826,IR(11, 1),IR(16704, 12)/* MemoryINTEL */,IR(0, 0),IR(125, 1),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5827,IR(0, 1),IR(16716, 14)/* NumbanksINTEL */,IR(0, 0),IR(125, 1),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5828,IR(0, 1),IR(16730, 15)/* BankwidthINTEL */,IR(0, 0),IR(125, 1),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5829,IR(0, 1),IR(16745, 22)/* MaxPrivateCopiesINTEL */,IR(0, 0),IR(125, 1),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5830,IR(0, 0),IR(16767, 16)/* SinglepumpINTEL */,IR(0, 0),IR(125, 1),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5831,IR(0, 0),IR(16783, 16)/* DoublepumpINTEL */,IR(0, 0),IR(125, 1),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5832,IR(0, 1),IR(16799, 19)/* MaxReplicatesINTEL */,IR(0, 0),IR(125, 1),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5833,IR(0, 0),IR(16818, 20)/* SimpleDualPortINTEL */,IR(0, 0),IR(125, 1),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5834,IR(16, 2),IR(16838, 11)/* MergeINTEL */,IR(0, 0),IR(125, 1),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5835,IR(18, 1),IR(16891, 14)/* BankBitsINTEL */,IR(0, 0),IR(125, 1),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5836,IR(0, 1),IR(16905, 20)/* ForcePow2DepthINTEL */,IR(0, 0),IR(125, 1),IR(99, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5883,IR(0, 1),IR(16925, 16)/* StridesizeINTEL */,IR(0, 0),IR(125, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5884,IR(0, 1),IR(16941, 14)/* WordsizeINTEL */,IR(0, 0),IR(125, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5885,IR(0, 0),IR(16955, 18)/* TrueDualPortINTEL */,IR(0, 0),IR(125, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5899,IR(0, 0),IR(16973, 19)/* BurstCoalesceINTEL */,IR(0, 0),IR(126, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5900,IR(0, 1),IR(16992, 15)/* CacheSizeINTEL */,IR(0, 0),IR(126, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5901,IR(0, 0),IR(17007, 28)/* DontStaticallyCoalesceINTEL */,IR(0, 0),IR(126, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5902,IR(0, 1),IR(17035, 14)/* PrefetchINTEL */,IR(0, 0),IR(126, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5905,IR(0, 0),IR(17049, 17)/* StallEnableINTEL */,IR(0, 0),IR(103, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5907,IR(0, 0),IR(17066, 25)/* FuseLoopsInFunctionINTEL */,IR(0, 0),IR(127, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5909,IR(1, 2),IR(17091, 19)/* MathOpDSPModeINTEL */,IR(0, 0),IR(128, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5914,IR(10, 1),IR(17110, 16)/* AliasScopeINTEL */,IR(0, 0),IR(129, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5915,IR(10, 1),IR(17126, 13)/* NoAliasINTEL */,IR(0, 0),IR(129, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5917,IR(0, 1),IR(17139, 24)/* InitiationIntervalINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5918,IR(0, 1),IR(17163, 20)/* MaxConcurrencyINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5919,IR(0, 1),IR(17183, 20)/* PipelineEnableINTEL */,IR(0, 0),IR(130, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5921,IR(0, 1),IR(17203, 20)/* BufferLocationINTEL */,IR(0, 0),IR(131, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {5944,IR(0, 1),IR(17223, 19)/* IOPipeStorageINTEL */,IR(0, 0),IR(132, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6080,IR(19, 2),IR(17276, 31)/* FunctionFloatingPointModeINTEL */,IR(0, 0),IR(124, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6085,IR(0, 0),IR(17307, 25)/* SingleElementVectorINTEL */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6087,IR(0, 0),IR(17332, 35)/* VectorComputeCallableFunctionINTEL */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6140,IR(0, 0),IR(17367, 18)/* MediaBlockIOINTEL */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6151,IR(0, 0),IR(17385, 15)/* StallFreeINTEL */,IR(0, 0),IR(133, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6170,IR(21, 1),IR(17431, 26)/* FPMaxErrorDecorationINTEL */,IR(0, 0),IR(134, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6172,IR(0, 1),IR(17457, 25)/* LatencyControlLabelINTEL */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6173,IR(22, 3),IR(17482, 30)/* LatencyControlConstraintINTEL */,IR(0, 0),IR(135, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6175,IR(0, 0),IR(17512, 27)/* ConduitKernelArgumentINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6176,IR(0, 0),IR(17539, 31)/* RegisterMapKernelArgumentINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6177,IR(0, 1),IR(17570, 33)/* MMHostInterfaceAddressWidthINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6178,IR(0, 1),IR(17603, 30)/* MMHostInterfaceDataWidthINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6179,IR(0, 1),IR(17633, 28)/* MMHostInterfaceLatencyINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6180,IR(25, 1),IR(17695, 34)/* MMHostInterfaceReadWriteModeINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6181,IR(0, 1),IR(17729, 29)/* MMHostInterfaceMaxBurstINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6182,IR(0, 1),IR(17758, 32)/* MMHostInterfaceWaitRequestINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6183,IR(0, 0),IR(17790, 26)/* StableKernelArgumentINTEL */,IR(0, 0),IR(136, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6188,IR(26, 2),IR(17855, 16)/* HostAccessINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6190,IR(28, 1),IR(17918, 14)/* InitModeINTEL */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6191,IR(0, 1),IR(17932, 28)/* ImplementInRegisterMapINTEL */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6442,IR(29, 2),IR(17996, 22)/* CacheControlLoadINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {6443,IR(31, 2),IR(18055, 23)/* CacheControlStoreINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DECORATION
  {0,IR(0, 0),IR(18078, 3)/* 1D */,IR(0, 0),IR(72, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {1,IR(0, 0),IR(18081, 3)/* 2D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {2,IR(0, 0),IR(18084, 3)/* 3D */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {3,IR(0, 0),IR(18087, 5)/* Cube */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {4,IR(0, 0),IR(18092, 5)/* Rect */,IR(0, 0),IR(71, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {5,IR(0, 0),IR(18097, 7)/* Buffer */,IR(0, 0),IR(73, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {6,IR(0, 0),IR(18104, 12)/* SubpassData */,IR(0, 0),IR(92, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {4173,IR(0, 0),IR(18116, 17)/* TileImageDataEXT */,IR(0, 0),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_DIMENSIONALITY
  {0,IR(0, 1),IR(18133, 12)/* Invocations */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {1,IR(0, 0),IR(18145, 13)/* SpacingEqual */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {2,IR(0, 0),IR(18158, 22)/* SpacingFractionalEven */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {3,IR(0, 0),IR(18180, 21)/* SpacingFractionalOdd */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4,IR(0, 0),IR(18201, 14)/* VertexOrderCw */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5,IR(0, 0),IR(18215, 15)/* VertexOrderCcw */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6,IR(0, 0),IR(18230, 19)/* PixelCenterInteger */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {7,IR(0, 0),IR(18249, 16)/* OriginUpperLeft */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {8,IR(0, 0),IR(18265, 16)/* OriginLowerLeft */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {9,IR(0, 0),IR(18281, 19)/* EarlyFragmentTests */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {10,IR(0, 0),IR(18300, 10)/* PointMode */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {11,IR(0, 0),IR(18310, 4)/* Xfb */,IR(0, 0),IR(111, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {12,IR(0, 0),IR(18314, 15)/* DepthReplacing */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {14,IR(0, 0),IR(18329, 13)/* DepthGreater */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {15,IR(0, 0),IR(18342, 10)/* DepthLess */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {16,IR(0, 0),IR(18352, 15)/* DepthUnchanged */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {17,IR(22, 3),IR(18367, 10)/* LocalSize */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {18,IR(22, 3),IR(18377, 14)/* LocalSizeHint */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {19,IR(0, 0),IR(18391, 12)/* InputPoints */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {20,IR(0, 0),IR(18403, 11)/* InputLines */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {21,IR(0, 0),IR(18414, 20)/* InputLinesAdjacency */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {22,IR(0, 0),IR(18434, 10)/* Triangles */,IR(0, 0),IR(12, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {23,IR(0, 0),IR(18444, 24)/* InputTrianglesAdjacency */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {24,IR(0, 0),IR(18468, 6)/* Quads */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {25,IR(0, 0),IR(18474, 9)/* Isolines */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {26,IR(0, 1),IR(18483, 15)/* OutputVertices */,IR(0, 0),IR(141, 4),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {27,IR(0, 0),IR(18498, 13)/* OutputPoints */,IR(0, 0),IR(145, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {28,IR(0, 0),IR(18511, 16)/* OutputLineStrip */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {29,IR(0, 0),IR(18527, 20)/* OutputTriangleStrip */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {30,IR(0, 1),IR(18547, 12)/* VecTypeHint */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {31,IR(0, 0),IR(18559, 15)/* ContractionOff */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {33,IR(0, 0),IR(18574, 12)/* Initializer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {34,IR(0, 0),IR(18586, 10)/* Finalizer */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {35,IR(0, 1),IR(5260, 13)/* SubgroupSize */,IR(0, 0),IR(148, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {36,IR(0, 1),IR(18596, 22)/* SubgroupsPerWorkgroup */,IR(0, 0),IR(148, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {37,IR(10, 1),IR(18618, 24)/* SubgroupsPerWorkgroupId */,IR(0, 0),IR(148, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {38,IR(33, 3),IR(18642, 12)/* LocalSizeId */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {39,IR(33, 3),IR(18654, 16)/* LocalSizeHintId */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,2),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4169,IR(0, 0),IR(18670, 34)/* NonCoherentColorAttachmentReadEXT */,IR(0, 0),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4170,IR(0, 0),IR(18704, 34)/* NonCoherentDepthAttachmentReadEXT */,IR(0, 0),IR(149, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4171,IR(0, 0),IR(18738, 36)/* NonCoherentStencilAttachmentReadEXT */,IR(0, 0),IR(150, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4421,IR(0, 0),IR(18774, 30)/* SubgroupUniformControlFlowKHR */,IR(0, 0),IR(3, 1),IR(154, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4446,IR(0, 0),IR(18804, 18)/* PostDepthCoverage */,IR(0, 0),IR(151, 1),IR(43, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4459,IR(0, 1),IR(9392, 15)/* DenormPreserve */,IR(0, 0),IR(152, 1),IR(45, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4460,IR(0, 1),IR(9407, 18)/* DenormFlushToZero */,IR(0, 0),IR(153, 1),IR(45, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4461,IR(0, 1),IR(9425, 25)/* SignedZeroInfNanPreserve */,IR(0, 0),IR(154, 1),IR(45, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4462,IR(0, 1),IR(9450, 16)/* RoundingModeRTE */,IR(0, 0),IR(155, 1),IR(45, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4463,IR(0, 1),IR(9466, 16)/* RoundingModeRTZ */,IR(0, 0),IR(156, 1),IR(45, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4489,IR(0, 0),IR(18822, 34)/* NonCoherentTileAttachmentReadQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {4490,IR(22, 3),IR(18856, 20)/* TileShadingRateQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5017,IR(0, 0),IR(18876, 29)/* EarlyAndLateFragmentTestsAMD */,IR(0, 0),IR(3, 1),IR(155, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5027,IR(0, 0),IR(18905, 23)/* StencilRefReplacingEXT */,IR(0, 0),IR(42, 1),IR(11, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5069,IR(0, 0),IR(18928, 15)/* CoalescingAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5070,IR(10, 1),IR(18943, 15)/* IsApiEntryAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5071,IR(10, 1),IR(18958, 21)/* MaxNodeRecursionAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5072,IR(33, 3),IR(18979, 24)/* StaticNumWorkgroupsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5073,IR(10, 1),IR(6153, 16)/* ShaderIndexAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5077,IR(33, 3),IR(19003, 21)/* MaxNumWorkgroupsAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5079,IR(0, 0),IR(19024, 28)/* StencilRefUnchangedFrontAMD */,IR(0, 0),IR(42, 1),IR(156, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5080,IR(0, 0),IR(19052, 26)/* StencilRefGreaterFrontAMD */,IR(0, 0),IR(42, 1),IR(156, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5081,IR(0, 0),IR(19078, 23)/* StencilRefLessFrontAMD */,IR(0, 0),IR(42, 1),IR(156, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5082,IR(0, 0),IR(19101, 27)/* StencilRefUnchangedBackAMD */,IR(0, 0),IR(42, 1),IR(156, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5083,IR(0, 0),IR(19128, 25)/* StencilRefGreaterBackAMD */,IR(0, 0),IR(42, 1),IR(156, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5084,IR(0, 0),IR(19153, 22)/* StencilRefLessBackAMD */,IR(0, 0),IR(42, 1),IR(156, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5088,IR(0, 0),IR(19175, 19)/* QuadDerivativesKHR */,IR(0, 0),IR(157, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5089,IR(0, 0),IR(19194, 20)/* RequireFullQuadsKHR */,IR(0, 0),IR(157, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5102,IR(36, 2),IR(19214, 20)/* SharesInputWithAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5269,IR(0, 0),IR(19234, 15)/* OutputLinesEXT */,IR(58, 1),IR(117, 2),IR(150, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5270,IR(0, 1),IR(19263, 20)/* OutputPrimitivesEXT */,IR(59, 1),IR(117, 2),IR(150, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5289,IR(0, 0),IR(19302, 24)/* DerivativeGroupQuadsKHR */,IR(60, 1),IR(158, 2),IR(70, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5290,IR(0, 0),IR(19349, 25)/* DerivativeGroupLinearKHR */,IR(61, 1),IR(160, 2),IR(70, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5298,IR(0, 0),IR(19398, 19)/* OutputTrianglesEXT */,IR(62, 1),IR(117, 2),IR(150, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5366,IR(0, 0),IR(19435, 25)/* PixelInterlockOrderedEXT */,IR(0, 0),IR(162, 1),IR(77, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5367,IR(0, 0),IR(19460, 27)/* PixelInterlockUnorderedEXT */,IR(0, 0),IR(162, 1),IR(77, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5368,IR(0, 0),IR(19487, 26)/* SampleInterlockOrderedEXT */,IR(0, 0),IR(163, 1),IR(77, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5369,IR(0, 0),IR(19513, 28)/* SampleInterlockUnorderedEXT */,IR(0, 0),IR(163, 1),IR(77, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5370,IR(0, 0),IR(19541, 31)/* ShadingRateInterlockOrderedEXT */,IR(0, 0),IR(164, 1),IR(77, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5371,IR(0, 0),IR(19572, 33)/* ShadingRateInterlockUnorderedEXT */,IR(0, 0),IR(164, 1),IR(77, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5618,IR(0, 1),IR(19605, 27)/* SharedLocalMemorySizeINTEL */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5620,IR(0, 1),IR(19632, 21)/* RoundingModeRTPINTEL */,IR(0, 0),IR(165, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5621,IR(0, 1),IR(19653, 21)/* RoundingModeRTNINTEL */,IR(0, 0),IR(165, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5622,IR(0, 1),IR(19674, 26)/* FloatingPointModeALTINTEL */,IR(0, 0),IR(165, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5623,IR(0, 1),IR(19700, 27)/* FloatingPointModeIEEEINTEL */,IR(0, 0),IR(165, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5893,IR(22, 3),IR(19727, 22)/* MaxWorkgroupSizeINTEL */,IR(0, 0),IR(166, 1),IR(105, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5894,IR(0, 1),IR(19749, 16)/* MaxWorkDimINTEL */,IR(0, 0),IR(166, 1),IR(105, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5895,IR(0, 0),IR(19765, 20)/* NoGlobalOffsetINTEL */,IR(0, 0),IR(166, 1),IR(105, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5896,IR(0, 1),IR(19785, 22)/* NumSIMDWorkitemsINTEL */,IR(0, 0),IR(104, 1),IR(105, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {5903,IR(0, 1),IR(19807, 28)/* SchedulerTargetFmaxMhzINTEL */,IR(0, 0),IR(104, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6023,IR(0, 0),IR(19835, 24)/* MaximallyReconvergesKHR */,IR(0, 0),IR(3, 1),IR(158, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6028,IR(36, 2),IR(19859, 18)/* FPFastMathDefault */,IR(0, 0),IR(167, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6154,IR(0, 1),IR(19877, 24)/* StreamingInterfaceINTEL */,IR(0, 0),IR(104, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6160,IR(0, 1),IR(19901, 26)/* RegisterMapInterfaceINTEL */,IR(0, 0),IR(168, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6417,IR(0, 1),IR(19927, 23)/* NamedBarrierCountINTEL */,IR(0, 0),IR(121, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6461,IR(0, 1),IR(19950, 22)/* MaximumRegistersINTEL */,IR(0, 0),IR(169, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6462,IR(10, 1),IR(19972, 24)/* MaximumRegistersIdINTEL */,IR(0, 0),IR(169, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {6463,IR(38, 1),IR(20047, 27)/* NamedMaximumRegistersINTEL */,IR(0, 0),IR(169, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODE
  {0,IR(0, 0),IR(20074, 7)/* Vertex */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {1,IR(0, 0),IR(20081, 20)/* TessellationControl */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {2,IR(0, 0),IR(20101, 23)/* TessellationEvaluation */,IR(0, 0),IR(24, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {3,IR(0, 0),IR(4741, 9)/* Geometry */,IR(0, 0),IR(69, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {4,IR(0, 0),IR(14313, 9)/* Fragment */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5,IR(0, 0),IR(20124, 10)/* GLCompute */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {6,IR(0, 0),IR(4508, 7)/* Kernel */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5267,IR(0, 0),IR(20134, 7)/* TaskNV */,IR(0, 0),IR(50, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5268,IR(0, 0),IR(20141, 7)/* MeshNV */,IR(0, 0),IR(50, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5313,IR(0, 0),IR(20148, 17)/* RayGenerationKHR */,IR(63, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5314,IR(0, 0),IR(20181, 16)/* IntersectionKHR */,IR(64, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5315,IR(0, 0),IR(20212, 10)/* AnyHitKHR */,IR(65, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5316,IR(0, 0),IR(20231, 14)/* ClosestHitKHR */,IR(66, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5317,IR(0, 0),IR(20258, 8)/* MissKHR */,IR(67, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5318,IR(0, 0),IR(20273, 12)/* CallableKHR */,IR(68, 1),IR(54, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5364,IR(0, 0),IR(20296, 8)/* TaskEXT */,IR(0, 0),IR(53, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {5365,IR(0, 0),IR(20304, 8)/* MeshEXT */,IR(0, 0),IR(53, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_EXECUTION_MODEL
  {0,IR(0, 0),IR(20312, 9)/* Preserve */,IR(0, 0),IR(124, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPDENORM_MODE
  {1,IR(0, 0),IR(20321, 12)/* FlushToZero */,IR(0, 0),IR(124, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPDENORM_MODE
  {0,IR(0, 0),IR(20333, 12)/* BFloat16KHR */,IR(0, 0),IR(86, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPENCODING
  {0,IR(0, 0),IR(20345, 5)/* IEEE */,IR(0, 0),IR(124, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPOPERATION_MODE
  {1,IR(0, 0),IR(20350, 4)/* ALT */,IR(0, 0),IR(124, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FPOPERATION_MODE
  {0,IR(0, 0),IR(13909, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {1,IR(0, 0),IR(20354, 7)/* NotNaN */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {2,IR(0, 0),IR(20361, 7)/* NotInf */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {4,IR(0, 0),IR(20368, 4)/* NSZ */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {8,IR(0, 0),IR(20372, 11)/* AllowRecip */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {16,IR(0, 0),IR(20383, 5)/* Fast */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {65536,IR(0, 0),IR(20388, 14)/* AllowContract */,IR(69, 1),IR(170, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {131072,IR(0, 0),IR(20425, 13)/* AllowReassoc */,IR(70, 1),IR(170, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {262144,IR(0, 0),IR(20456, 15)/* AllowTransform */,IR(0, 0),IR(167, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {0,IR(0, 0),IR(20471, 4)/* RTE */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {1,IR(0, 0),IR(20475, 4)/* RTZ */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {2,IR(0, 0),IR(20479, 4)/* RTP */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {3,IR(0, 0),IR(20483, 4)/* RTN */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {1,IR(0, 0),IR(20487, 16)/* Vertical2Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {2,IR(0, 0),IR(20503, 16)/* Vertical4Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {4,IR(0, 0),IR(20519, 18)/* Horizontal2Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {8,IR(0, 0),IR(20537, 18)/* Horizontal4Pixels */,IR(0, 0),IR(38, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {0,IR(0, 0),IR(13909, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {1,IR(0, 0),IR(20555, 7)/* Inline */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {2,IR(0, 0),IR(20562, 11)/* DontInline */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {4,IR(0, 0),IR(20573, 5)/* Pure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {8,IR(0, 0),IR(20578, 6)/* Const */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {65536,IR(0, 0),IR(13150, 11)/* OptNoneEXT */,IR(50, 1),IR(172, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {0,IR(0, 0),IR(20584, 5)/* Zext */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {1,IR(0, 0),IR(20589, 5)/* Sext */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {2,IR(0, 0),IR(20594, 6)/* ByVal */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {3,IR(0, 0),IR(20600, 5)/* Sret */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {4,IR(0, 0),IR(20605, 8)/* NoAlias */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {5,IR(0, 0),IR(20613, 10)/* NoCapture */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {6,IR(0, 0),IR(20623, 8)/* NoWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {7,IR(0, 0),IR(20631, 12)/* NoReadWrite */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {5940,IR(0, 0),IR(20643, 20)/* RuntimeAlignedINTEL */,IR(0, 0),IR(173, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {0,IR(0, 0),IR(20663, 7)/* Reduce */,IR(0, 0),IR(174, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {1,IR(0, 0),IR(20670, 14)/* InclusiveScan */,IR(0, 0),IR(174, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {2,IR(0, 0),IR(20684, 14)/* ExclusiveScan */,IR(0, 0),IR(174, 3),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {3,IR(0, 0),IR(20698, 16)/* ClusteredReduce */,IR(0, 0),IR(177, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {6,IR(0, 0),IR(20714, 20)/* PartitionedReduceNV */,IR(0, 0),IR(178, 1),IR(72, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {7,IR(0, 0),IR(20734, 27)/* PartitionedInclusiveScanNV */,IR(0, 0),IR(178, 1),IR(72, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {8,IR(0, 0),IR(20761, 27)/* PartitionedExclusiveScanNV */,IR(0, 0),IR(178, 1),IR(72, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_GROUP_OPERATION
  {0,IR(0, 0),IR(20788, 10)/* NoneINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {1,IR(0, 0),IR(20798, 10)/* ReadINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {2,IR(0, 0),IR(20808, 11)/* WriteINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {3,IR(0, 0),IR(20819, 15)/* ReadWriteINTEL */,IR(0, 0),IR(137, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {0,IR(0, 0),IR(13909, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {1,IR(10, 1),IR(20834, 5)/* Bias */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {2,IR(10, 1),IR(20839, 4)/* Lod */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {4,IR(36, 2),IR(20843, 5)/* Grad */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {8,IR(10, 1),IR(20848, 12)/* ConstOffset */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {16,IR(10, 1),IR(15316, 7)/* Offset */,IR(0, 0),IR(179, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {32,IR(10, 1),IR(20860, 13)/* ConstOffsets */,IR(0, 0),IR(179, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {64,IR(10, 1),IR(15113, 7)/* Sample */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {128,IR(10, 1),IR(8292, 7)/* MinLod */,IR(0, 0),IR(180, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {256,IR(4, 1),IR(20873, 19)/* MakeTexelAvailable */,IR(71, 1),IR(181, 1),IR(75, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {512,IR(4, 1),IR(20914, 17)/* MakeTexelVisible */,IR(72, 1),IR(181, 1),IR(75, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {1024,IR(0, 0),IR(20951, 16)/* NonPrivateTexel */,IR(73, 1),IR(181, 1),IR(75, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {2048,IR(0, 0),IR(20986, 14)/* VolatileTexel */,IR(74, 1),IR(181, 1),IR(75, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {4096,IR(0, 0),IR(21017, 11)/* SignExtend */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {8192,IR(0, 0),IR(21028, 11)/* ZeroExtend */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {16384,IR(0, 0),IR(21039, 12)/* Nontemporal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {65536,IR(10, 1),IR(21051, 8)/* Offsets */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE
  {0,IR(0, 0),IR(21059, 10)/* SnormInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {1,IR(0, 0),IR(21069, 11)/* SnormInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {2,IR(0, 0),IR(21080, 10)/* UnormInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {3,IR(0, 0),IR(21090, 11)/* UnormInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {4,IR(0, 0),IR(21101, 14)/* UnormShort565 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {5,IR(0, 0),IR(21115, 14)/* UnormShort555 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {6,IR(0, 0),IR(21129, 15)/* UnormInt101010 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {7,IR(0, 0),IR(21144, 11)/* SignedInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {8,IR(0, 0),IR(21155, 12)/* SignedInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {9,IR(0, 0),IR(21167, 12)/* SignedInt32 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {10,IR(0, 0),IR(21179, 13)/* UnsignedInt8 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {11,IR(0, 0),IR(21192, 14)/* UnsignedInt16 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {12,IR(0, 0),IR(21206, 14)/* UnsignedInt32 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {13,IR(0, 0),IR(21220, 10)/* HalfFloat */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {14,IR(0, 0),IR(13806, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {15,IR(0, 0),IR(21230, 11)/* UnormInt24 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {16,IR(0, 0),IR(21241, 17)/* UnormInt101010_2 */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {17,IR(0, 0),IR(21258, 16)/* UnormInt10X6EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {19,IR(0, 0),IR(21274, 20)/* UnsignedIntRaw10EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {20,IR(0, 0),IR(21294, 20)/* UnsignedIntRaw12EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {21,IR(0, 0),IR(21314, 20)/* UnormInt2_101010EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {22,IR(0, 0),IR(21334, 19)/* UnsignedInt10X6EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {23,IR(0, 0),IR(21353, 19)/* UnsignedInt12X4EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {24,IR(0, 0),IR(21372, 19)/* UnsignedInt14X2EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {25,IR(0, 0),IR(21391, 16)/* UnormInt12X4EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {26,IR(0, 0),IR(21407, 16)/* UnormInt14X2EXT */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {0,IR(0, 0),IR(21423, 2)/* R */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {1,IR(0, 0),IR(21425, 2)/* A */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {2,IR(0, 0),IR(21427, 3)/* RG */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {3,IR(0, 0),IR(21430, 3)/* RA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {4,IR(0, 0),IR(21433, 4)/* RGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {5,IR(0, 0),IR(21437, 5)/* RGBA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {6,IR(0, 0),IR(21442, 5)/* BGRA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {7,IR(0, 0),IR(21447, 5)/* ARGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {8,IR(0, 0),IR(21452, 10)/* Intensity */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {9,IR(0, 0),IR(21462, 10)/* Luminance */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {10,IR(0, 0),IR(21472, 3)/* Rx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {11,IR(0, 0),IR(21475, 4)/* RGx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {12,IR(0, 0),IR(21479, 5)/* RGBx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {13,IR(0, 0),IR(21484, 6)/* Depth */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {14,IR(0, 0),IR(21490, 13)/* DepthStencil */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {15,IR(0, 0),IR(21503, 5)/* sRGB */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {16,IR(0, 0),IR(21508, 6)/* sRGBx */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {17,IR(0, 0),IR(21514, 6)/* sRGBA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {18,IR(0, 0),IR(21520, 6)/* sBGRA */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {19,IR(0, 0),IR(21526, 5)/* ABGR */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {0,IR(0, 0),IR(21531, 27)/* InitOnDeviceReprogramINTEL */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {1,IR(0, 0),IR(21558, 23)/* InitOnDeviceResetINTEL */,IR(0, 0),IR(138, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {0,IR(0, 0),IR(21581, 7)/* NoWait */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {1,IR(0, 0),IR(21588, 11)/* WaitKernel */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {2,IR(0, 0),IR(21599, 14)/* WaitWorkGroup */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {0,IR(0, 0),IR(13909, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {1,IR(0, 0),IR(21613, 12)/* CmdExecTime */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {0,IR(0, 0),IR(13909, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {1,IR(0, 0),IR(21625, 13)/* MayUsePrintf */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {0,IR(0, 0),IR(21638, 7)/* Export */,IR(0, 0),IR(114, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {1,IR(0, 0),IR(21645, 7)/* Import */,IR(0, 0),IR(114, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {2,IR(0, 0),IR(21652, 12)/* LinkOnceODR */,IR(0, 0),IR(114, 1),IR(159, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LINKAGE_TYPE
  {0,IR(0, 0),IR(21664, 14)/* UncachedINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {1,IR(0, 0),IR(21678, 12)/* CachedINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {2,IR(0, 0),IR(21690, 15)/* StreamingINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {3,IR(0, 0),IR(21705, 25)/* InvalidateAfterReadINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {4,IR(0, 0),IR(21730, 17)/* ConstCachedINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {0,IR(0, 0),IR(13909, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {1,IR(0, 0),IR(21747, 7)/* Unroll */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {2,IR(0, 0),IR(21754, 11)/* DontUnroll */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {4,IR(0, 0),IR(21765, 19)/* DependencyInfinite */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {8,IR(0, 1),IR(21784, 17)/* DependencyLength */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,1),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {16,IR(0, 1),IR(21801, 14)/* MinIterations */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {32,IR(0, 1),IR(21815, 14)/* MaxIterations */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {64,IR(0, 1),IR(21829, 18)/* IterationMultiple */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {128,IR(0, 1),IR(21847, 10)/* PeelCount */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {256,IR(0, 1),IR(21857, 13)/* PartialCount */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {65536,IR(0, 1),IR(17139, 24)/* InitiationIntervalINTEL */,IR(0, 0),IR(182, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {131072,IR(0, 1),IR(17163, 20)/* MaxConcurrencyINTEL */,IR(0, 0),IR(182, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {262144,IR(0, 1),IR(21870, 21)/* DependencyArrayINTEL */,IR(0, 0),IR(182, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {524288,IR(0, 1),IR(17183, 20)/* PipelineEnableINTEL */,IR(0, 0),IR(182, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {1048576,IR(0, 1),IR(21891, 18)/* LoopCoalesceINTEL */,IR(0, 0),IR(182, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {2097152,IR(0, 1),IR(21909, 21)/* MaxInterleavingINTEL */,IR(0, 0),IR(182, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {4194304,IR(0, 1),IR(21930, 26)/* SpeculatedIterationsINTEL */,IR(0, 0),IR(182, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {8388608,IR(0, 0),IR(21956, 14)/* NoFusionINTEL */,IR(0, 0),IR(182, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {16777216,IR(0, 1),IR(21970, 15)/* LoopCountINTEL */,IR(0, 0),IR(182, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {33554432,IR(0, 1),IR(21985, 26)/* MaxReinvocationDelayINTEL */,IR(0, 0),IR(182, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_LOOP_CONTROL
  {0,IR(0, 0),IR(13909, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {1,IR(0, 0),IR(22011, 29)/* MatrixASignedComponentsINTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {2,IR(0, 0),IR(22040, 29)/* MatrixBSignedComponentsINTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {4,IR(0, 0),IR(22069, 21)/* MatrixCBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {8,IR(0, 0),IR(22090, 26)/* MatrixResultBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {16,IR(0, 0),IR(22116, 23)/* MatrixAPackedInt8INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {32,IR(0, 0),IR(22139, 23)/* MatrixBPackedInt8INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {64,IR(0, 0),IR(22162, 23)/* MatrixAPackedInt4INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {128,IR(0, 0),IR(22185, 23)/* MatrixBPackedInt4INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {256,IR(0, 0),IR(22208, 17)/* MatrixATF32INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {512,IR(0, 0),IR(22225, 17)/* MatrixBTF32INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {1024,IR(0, 0),IR(22242, 26)/* MatrixAPackedFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {2048,IR(0, 0),IR(22268, 26)/* MatrixBPackedFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {4096,IR(0, 0),IR(22294, 27)/* MatrixAPackedBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {8192,IR(0, 0),IR(22321, 27)/* MatrixBPackedBFloat16INTEL */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {0,IR(0, 0),IR(13909, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {1,IR(0, 0),IR(15147, 9)/* Volatile */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {2,IR(0, 1),IR(22348, 8)/* Aligned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {4,IR(0, 0),IR(21039, 12)/* Nontemporal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {8,IR(4, 1),IR(22356, 21)/* MakePointerAvailable */,IR(75, 1),IR(181, 1),IR(75, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {16,IR(4, 1),IR(22401, 19)/* MakePointerVisible */,IR(76, 1),IR(181, 1),IR(75, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {32,IR(0, 0),IR(22442, 18)/* NonPrivatePointer */,IR(77, 1),IR(181, 1),IR(75, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {65536,IR(10, 1),IR(22481, 20)/* AliasScopeINTELMask */,IR(0, 0),IR(129, 1),IR(110, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {131072,IR(10, 1),IR(22501, 17)/* NoAliasINTELMask */,IR(0, 0),IR(129, 1),IR(110, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_ACCESS
  {0,IR(0, 0),IR(22518, 7)/* Simple */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {1,IR(0, 0),IR(22525, 8)/* GLSL450 */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {2,IR(0, 0),IR(22533, 7)/* OpenCL */,IR(0, 0),IR(0, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {3,IR(0, 0),IR(22540, 7)/* Vulkan */,IR(78, 1),IR(181, 1),IR(75, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_MODEL
  {0,IR(0, 0),IR(22557, 8)/* Relaxed */,IR(79, 1),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {2,IR(0, 0),IR(22565, 8)/* Acquire */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {4,IR(0, 0),IR(22573, 8)/* Release */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {8,IR(0, 0),IR(22581, 15)/* AcquireRelease */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {16,IR(0, 0),IR(22596, 23)/* SequentiallyConsistent */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {64,IR(0, 0),IR(22619, 14)/* UniformMemory */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {128,IR(0, 0),IR(22633, 15)/* SubgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {256,IR(0, 0),IR(22648, 16)/* WorkgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {512,IR(0, 0),IR(22664, 21)/* CrossWorkgroupMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {1024,IR(0, 0),IR(22685, 20)/* AtomicCounterMemory */,IR(0, 0),IR(80, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {2048,IR(0, 0),IR(22705, 12)/* ImageMemory */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {4096,IR(0, 0),IR(22717, 13)/* OutputMemory */,IR(80, 1),IR(181, 1),IR(75, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {8192,IR(0, 0),IR(22746, 14)/* MakeAvailable */,IR(81, 1),IR(181, 1),IR(75, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {16384,IR(0, 0),IR(22777, 12)/* MakeVisible */,IR(82, 1),IR(181, 1),IR(75, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {32768,IR(0, 0),IR(15147, 9)/* Volatile */,IR(0, 0),IR(181, 1),IR(75, 1),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {0,IR(0, 0),IR(22804, 10)/* AutoINTEL */,IR(0, 0),IR(169, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS
  {0,IR(0, 0),IR(22814, 5)/* WRAP */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {1,IR(0, 0),IR(22819, 4)/* SAT */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {2,IR(0, 0),IR(22823, 9)/* SAT_ZERO */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {3,IR(0, 0),IR(22832, 8)/* SAT_SYM */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_OVERFLOW_MODES
  {0,IR(0, 0),IR(22840, 25)/* PackedVectorFormat4x8Bit */,IR(83, 1),IR(1, 0),IR(119, 1),SPV_SPIRV_VERSION_WORD(1,6),0xffffffffu}, // SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {0,IR(0, 0),IR(22893, 4)/* TRN */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {1,IR(0, 0),IR(22897, 9)/* TRN_ZERO */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {2,IR(0, 0),IR(22906, 4)/* RND */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {3,IR(0, 0),IR(22910, 9)/* RND_ZERO */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {4,IR(0, 0),IR(22919, 8)/* RND_INF */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {5,IR(0, 0),IR(22927, 12)/* RND_MIN_INF */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {6,IR(0, 0),IR(22939, 9)/* RND_CONV */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {7,IR(0, 0),IR(22948, 13)/* RND_CONV_ODD */,IR(0, 0),IR(183, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {0,IR(0, 0),IR(13909, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {1,IR(0, 0),IR(22961, 25)/* RobustnessPerComponentNV */,IR(0, 0),IR(184, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {2,IR(0, 0),IR(22986, 23)/* RobustnessPerElementNV */,IR(0, 0),IR(184, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {0,IR(0, 0),IR(14661, 8)/* NoneKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {1,IR(0, 0),IR(23009, 10)/* OpaqueKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {2,IR(0, 0),IR(23019, 12)/* NoOpaqueKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {4,IR(0, 0),IR(23031, 23)/* TerminateOnFirstHitKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {8,IR(0, 0),IR(23054, 24)/* SkipClosestHitShaderKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {16,IR(0, 0),IR(23078, 27)/* CullBackFacingTrianglesKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {32,IR(0, 0),IR(23105, 28)/* CullFrontFacingTrianglesKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {64,IR(0, 0),IR(23133, 14)/* CullOpaqueKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {128,IR(0, 0),IR(23147, 16)/* CullNoOpaqueKHR */,IR(0, 0),IR(82, 2),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {256,IR(0, 0),IR(23163, 17)/* SkipTrianglesKHR */,IR(84, 1),IR(185, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {512,IR(0, 0),IR(23204, 13)/* SkipAABBsKHR */,IR(0, 0),IR(185, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {1024,IR(0, 0),IR(23217, 30)/* ForceOpacityMicromap2StateEXT */,IR(0, 0),IR(186, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_FLAGS
  {0,IR(0, 0),IR(23247, 41)/* RayQueryCandidateIntersectionTriangleKHR */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {1,IR(0, 0),IR(23288, 37)/* RayQueryCandidateIntersectionAABBKHR */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {0,IR(0, 0),IR(23325, 37)/* RayQueryCommittedIntersectionNoneKHR */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {1,IR(0, 0),IR(23362, 41)/* RayQueryCommittedIntersectionTriangleKHR */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {2,IR(0, 0),IR(23403, 42)/* RayQueryCommittedIntersectionGeneratedKHR */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {0,IR(0, 0),IR(23445, 33)/* RayQueryCandidateIntersectionKHR */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {1,IR(0, 0),IR(23478, 33)/* RayQueryCommittedIntersectionKHR */,IR(0, 0),IR(187, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {0,IR(0, 0),IR(13909, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {1,IR(0, 0),IR(23511, 12)/* ClampToEdge */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {2,IR(0, 0),IR(23523, 6)/* Clamp */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {3,IR(0, 0),IR(23529, 7)/* Repeat */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {4,IR(0, 0),IR(23536, 15)/* RepeatMirrored */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {0,IR(0, 0),IR(23551, 8)/* Nearest */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {1,IR(0, 0),IR(23559, 7)/* Linear */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {0,IR(0, 0),IR(23566, 8)/* Unknown */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {1,IR(0, 0),IR(23574, 8)/* Rgba32f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {2,IR(0, 0),IR(23582, 8)/* Rgba16f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {3,IR(0, 0),IR(23590, 5)/* R32f */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {4,IR(0, 0),IR(23595, 6)/* Rgba8 */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {5,IR(0, 0),IR(23601, 11)/* Rgba8Snorm */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {6,IR(0, 0),IR(23612, 6)/* Rg32f */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {7,IR(0, 0),IR(23618, 6)/* Rg16f */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {8,IR(0, 0),IR(23624, 13)/* R11fG11fB10f */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {9,IR(0, 0),IR(23637, 5)/* R16f */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {10,IR(0, 0),IR(23642, 7)/* Rgba16 */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {11,IR(0, 0),IR(23649, 8)/* Rgb10A2 */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {12,IR(0, 0),IR(23657, 5)/* Rg16 */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {13,IR(0, 0),IR(23662, 4)/* Rg8 */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {14,IR(0, 0),IR(23666, 4)/* R16 */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {15,IR(0, 0),IR(23670, 3)/* R8 */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {16,IR(0, 0),IR(23673, 12)/* Rgba16Snorm */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {17,IR(0, 0),IR(23685, 10)/* Rg16Snorm */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {18,IR(0, 0),IR(23695, 9)/* Rg8Snorm */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {19,IR(0, 0),IR(23704, 9)/* R16Snorm */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {20,IR(0, 0),IR(23713, 8)/* R8Snorm */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {21,IR(0, 0),IR(23721, 8)/* Rgba32i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {22,IR(0, 0),IR(23729, 8)/* Rgba16i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {23,IR(0, 0),IR(23737, 7)/* Rgba8i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {24,IR(0, 0),IR(23744, 5)/* R32i */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {25,IR(0, 0),IR(23749, 6)/* Rg32i */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {26,IR(0, 0),IR(23755, 6)/* Rg16i */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {27,IR(0, 0),IR(23761, 5)/* Rg8i */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {28,IR(0, 0),IR(23766, 5)/* R16i */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {29,IR(0, 0),IR(23771, 4)/* R8i */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {30,IR(0, 0),IR(23775, 9)/* Rgba32ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {31,IR(0, 0),IR(23784, 9)/* Rgba16ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {32,IR(0, 0),IR(23793, 8)/* Rgba8ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {33,IR(0, 0),IR(23801, 6)/* R32ui */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {34,IR(0, 0),IR(23807, 10)/* Rgb10a2ui */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {35,IR(0, 0),IR(23817, 7)/* Rg32ui */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {36,IR(0, 0),IR(23824, 7)/* Rg16ui */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {37,IR(0, 0),IR(23831, 6)/* Rg8ui */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {38,IR(0, 0),IR(23837, 6)/* R16ui */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {39,IR(0, 0),IR(23843, 5)/* R8ui */,IR(0, 0),IR(188, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {40,IR(0, 0),IR(23848, 6)/* R64ui */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {41,IR(0, 0),IR(23854, 5)/* R64i */,IR(0, 0),IR(189, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {0,IR(0, 0),IR(23859, 12)/* CrossDevice */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {1,IR(0, 0),IR(23871, 7)/* Device */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {2,IR(0, 0),IR(23878, 10)/* Workgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {3,IR(0, 0),IR(23888, 9)/* Subgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {4,IR(0, 0),IR(23897, 11)/* Invocation */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {5,IR(0, 0),IR(23908, 12)/* QueueFamily */,IR(85, 1),IR(181, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {6,IR(0, 0),IR(23935, 14)/* ShaderCallKHR */,IR(0, 0),IR(60, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_SCOPE_ID
  {0,IR(0, 0),IR(13909, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {1,IR(0, 0),IR(23949, 8)/* Flatten */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {2,IR(0, 0),IR(23957, 12)/* DontFlatten */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SELECTION_CONTROL
  {1,IR(0, 0),IR(23969, 29)/* IdentifierPossibleDuplicates */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS
  {0,IR(0, 0),IR(13778, 12)/* Unspecified */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {1,IR(0, 0),IR(13790, 8)/* Address */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {2,IR(0, 0),IR(13798, 8)/* Boolean */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {3,IR(0, 0),IR(13806, 6)/* Float */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {4,IR(0, 0),IR(13812, 7)/* Signed */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {5,IR(0, 0),IR(13819, 11)/* SignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {6,IR(0, 0),IR(13830, 9)/* Unsigned */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {7,IR(0, 0),IR(13839, 13)/* UnsignedChar */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {0,IR(0, 0),IR(13852, 6)/* Class */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {1,IR(0, 0),IR(13858, 10)/* Structure */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {2,IR(0, 0),IR(13868, 6)/* Union */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {0,IR(0, 0),IR(13874, 15)/* ImportedModule */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {1,IR(0, 0),IR(13889, 20)/* ImportedDeclaration */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {0,IR(0, 0),IR(13909, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {1,IR(0, 0),IR(13914, 16)/* FlagIsProtected */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {2,IR(0, 0),IR(13930, 14)/* FlagIsPrivate */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {3,IR(0, 0),IR(13944, 13)/* FlagIsPublic */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {4,IR(0, 0),IR(13957, 12)/* FlagIsLocal */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {8,IR(0, 0),IR(13969, 17)/* FlagIsDefinition */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {16,IR(0, 0),IR(13986, 12)/* FlagFwdDecl */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {32,IR(0, 0),IR(13998, 15)/* FlagArtificial */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {64,IR(0, 0),IR(14013, 13)/* FlagExplicit */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {128,IR(0, 0),IR(14026, 15)/* FlagPrototyped */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {256,IR(0, 0),IR(14041, 18)/* FlagObjectPointer */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {512,IR(0, 0),IR(14059, 17)/* FlagStaticMember */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {1024,IR(0, 0),IR(14076, 21)/* FlagIndirectVariable */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {2048,IR(0, 0),IR(14097, 20)/* FlagLValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {4096,IR(0, 0),IR(14117, 20)/* FlagRValueReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {8192,IR(0, 0),IR(14137, 16)/* FlagIsOptimized */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {16384,IR(0, 0),IR(14153, 16)/* FlagIsEnumClass */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {32768,IR(0, 0),IR(14169, 20)/* FlagTypePassByValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {65536,IR(0, 0),IR(14189, 24)/* FlagTypePassByReference */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {131072,IR(0, 0),IR(23998, 26)/* FlagUnknownPhysicalLayout */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {0,IR(0, 0),IR(14213, 6)/* Deref */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {1,IR(0, 0),IR(14219, 5)/* Plus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {2,IR(0, 0),IR(14224, 6)/* Minus */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {3,IR(10, 1),IR(14263, 11)/* PlusUconst */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {4,IR(36, 2),IR(14274, 9)/* BitPiece */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {5,IR(0, 0),IR(14283, 5)/* Swap */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {6,IR(0, 0),IR(14288, 7)/* Xderef */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {7,IR(0, 0),IR(14295, 11)/* StackValue */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {8,IR(10, 1),IR(14306, 7)/* Constu */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {9,IR(36, 2),IR(14313, 9)/* Fragment */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {0,IR(0, 0),IR(14322, 10)/* ConstType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {1,IR(0, 0),IR(14332, 13)/* VolatileType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {2,IR(0, 0),IR(14345, 13)/* RestrictType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {3,IR(0, 0),IR(14358, 11)/* AtomicType */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1, 0),0xffffffffu}, // SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {0,IR(0, 0),IR(23566, 8)/* Unknown */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {1,IR(0, 0),IR(24024, 5)/* ESSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {2,IR(0, 0),IR(24029, 5)/* GLSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {3,IR(0, 0),IR(24034, 9)/* OpenCL_C */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {4,IR(0, 0),IR(24043, 11)/* OpenCL_CPP */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {5,IR(0, 0),IR(24054, 5)/* HLSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {6,IR(0, 0),IR(24059, 15)/* CPP_for_OpenCL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {7,IR(0, 0),IR(24074, 5)/* SYCL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {8,IR(0, 0),IR(24079, 7)/* HERO_C */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {9,IR(0, 0),IR(24086, 5)/* NZSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {10,IR(0, 0),IR(24091, 5)/* WGSL */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {11,IR(0, 0),IR(24096, 6)/* Slang */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {12,IR(0, 0),IR(24102, 4)/* Zig */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {13,IR(0, 0),IR(24106, 5)/* Rust */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {0,IR(0, 0),IR(24111, 16)/* UniformConstant */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {1,IR(0, 0),IR(24127, 6)/* Input */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {2,IR(0, 0),IR(15198, 8)/* Uniform */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {3,IR(0, 0),IR(24133, 7)/* Output */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4,IR(0, 0),IR(23878, 10)/* Workgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5,IR(0, 0),IR(24140, 15)/* CrossWorkgroup */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {6,IR(0, 0),IR(24155, 8)/* Private */,IR(0, 0),IR(190, 2),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {7,IR(0, 0),IR(24163, 9)/* Function */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {8,IR(0, 0),IR(24172, 8)/* Generic */,IR(0, 0),IR(192, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {9,IR(0, 0),IR(24180, 13)/* PushConstant */,IR(0, 0),IR(3, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {10,IR(0, 0),IR(24193, 14)/* AtomicCounter */,IR(0, 0),IR(80, 1),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {11,IR(0, 0),IR(24207, 6)/* Image */,IR(0, 0),IR(1, 0),IR(0, 0),SPV_SPIRV_VERSION_WORD(1,0),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {12,IR(0, 0),IR(24213, 14)/* StorageBuffer */,IR(0, 0),IR(3, 1),IR(160, 2),SPV_SPIRV_VERSION_WORD(1,3),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4172,IR(0, 0),IR(24227, 13)/* TileImageEXT */,IR(0, 0),IR(140, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {4491,IR(0, 0),IR(24240, 19)/* TileAttachmentQCOM */,IR(0, 0),IR(41, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5068,IR(0, 0),IR(24259, 16)/* NodePayloadAMDX */,IR(0, 0),IR(43, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5328,IR(0, 0),IR(24275, 16)/* CallableDataKHR */,IR(86, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5329,IR(0, 0),IR(24306, 24)/* IncomingCallableDataKHR */,IR(87, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5338,IR(0, 0),IR(24353, 14)/* RayPayloadKHR */,IR(88, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5339,IR(0, 0),IR(24380, 16)/* HitAttributeKHR */,IR(89, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5342,IR(0, 0),IR(24411, 22)/* IncomingRayPayloadKHR */,IR(90, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5343,IR(0, 0),IR(24454, 22)/* ShaderRecordBufferKHR */,IR(91, 1),IR(54, 2),IR(24, 2),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5349,IR(0, 0),IR(24497, 22)/* PhysicalStorageBuffer */,IR(92, 1),IR(2, 1),IR(0, 2),SPV_SPIRV_VERSION_WORD(1,5),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5385,IR(0, 0),IR(24544, 21)/* HitObjectAttributeNV */,IR(0, 0),IR(119, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5402,IR(0, 0),IR(24565, 24)/* TaskPayloadWorkgroupEXT */,IR(0, 0),IR(53, 1),IR(23, 1),SPV_SPIRV_VERSION_WORD(1,4),0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5605,IR(0, 0),IR(24589, 17)/* CodeSectionINTEL */,IR(0, 0),IR(193, 1),IR(92, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5936,IR(0, 0),IR(24606, 16)/* DeviceOnlyINTEL */,IR(0, 0),IR(194, 1),IR(114, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {5937,IR(0, 0),IR(24622, 14)/* HostOnlyINTEL */,IR(0, 0),IR(194, 1),IR(114, 1),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORAGE_CLASS
  {0,IR(0, 0),IR(21664, 14)/* UncachedINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {1,IR(0, 0),IR(24636, 18)/* WriteThroughINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {2,IR(0, 0),IR(24654, 15)/* WriteBackINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {3,IR(0, 0),IR(21690, 15)/* StreamingINTEL */,IR(0, 0),IR(139, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {0,IR(0, 0),IR(13909, 5)/* None */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {1,IR(10, 1),IR(24669, 11)/* TensorView */,IR(0, 0),IR(195, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {2,IR(10, 1),IR(24680, 11)/* DecodeFunc */,IR(0, 0),IR(196, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {0,IR(0, 0),IR(24691, 10)/* Undefined */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {1,IR(0, 0),IR(15156, 9)/* Constant */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {2,IR(0, 0),IR(23511, 12)/* ClampToEdge */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {3,IR(0, 0),IR(23529, 7)/* Repeat */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {4,IR(0, 0),IR(23536, 15)/* RepeatMirrored */,IR(0, 0),IR(1, 0),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {0,IR(0, 0),IR(24701, 8)/* NoneARM */,IR(0, 0),IR(197, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {1,IR(0, 0),IR(24709, 15)/* NontemporalARM */,IR(0, 0),IR(197, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {2,IR(10, 1),IR(24724, 20)/* OutOfBoundsValueARM */,IR(0, 0),IR(197, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {4,IR(10, 1),IR(24744, 24)/* MakeElementAvailableARM */,IR(0, 0),IR(197, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {8,IR(10, 1),IR(24768, 22)/* MakeElementVisibleARM */,IR(0, 0),IR(197, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {16,IR(0, 0),IR(24790, 21)/* NonPrivateElementARM */,IR(0, 0),IR(197, 1),IR(0, 0),0xffffffffu,0xffffffffu}, // SPV_OPERAND_TYPE_TENSOR_OPERANDS
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
    case SPV_OPERAND_TYPE_CAPABILITY: return IR(133, 266);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(399, 8);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(407, 3);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(410, 2);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS: return IR(412, 19);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION: return IR(431, 10);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(441, 4);
    case SPV_OPERAND_TYPE_COMPONENT_TYPE: return IR(445, 15);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT: return IR(460, 4);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS: return IR(464, 6);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE: return IR(470, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE: return IR(473, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT: return IR(476, 4);
    case SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(480, 8);
    case SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE: return IR(488, 3);
    case SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS: return IR(491, 16);
    case SPV_OPERAND_TYPE_DEBUG_OPERATION: return IR(507, 9);
    case SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER: return IR(516, 3);
    case SPV_OPERAND_TYPE_DECORATION: return IR(519, 142);
    case SPV_OPERAND_TYPE_DIMENSIONALITY: return IR(661, 8);
    case SPV_OPERAND_TYPE_EXECUTION_MODE: return IR(669, 96);
    case SPV_OPERAND_TYPE_EXECUTION_MODEL: return IR(765, 17);
    case SPV_OPERAND_TYPE_FPDENORM_MODE: return IR(782, 2);
    case SPV_OPERAND_TYPE_FPENCODING: return IR(784, 1);
    case SPV_OPERAND_TYPE_FPOPERATION_MODE: return IR(785, 2);
    case SPV_OPERAND_TYPE_FP_FAST_MATH_MODE: return IR(787, 9);
    case SPV_OPERAND_TYPE_FP_ROUNDING_MODE: return IR(796, 4);
    case SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE: return IR(800, 4);
    case SPV_OPERAND_TYPE_FUNCTION_CONTROL: return IR(804, 6);
    case SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE: return IR(810, 9);
    case SPV_OPERAND_TYPE_GROUP_OPERATION: return IR(819, 7);
    case SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER: return IR(826, 4);
    case SPV_OPERAND_TYPE_IMAGE: return IR(830, 17);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE: return IR(847, 26);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER: return IR(873, 20);
    case SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER: return IR(893, 2);
    case SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS: return IR(895, 3);
    case SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO: return IR(898, 2);
    case SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS: return IR(900, 2);
    case SPV_OPERAND_TYPE_LINKAGE_TYPE: return IR(902, 3);
    case SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL: return IR(905, 5);
    case SPV_OPERAND_TYPE_LOOP_CONTROL: return IR(910, 20);
    case SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(930, 15);
    case SPV_OPERAND_TYPE_MEMORY_ACCESS: return IR(945, 9);
    case SPV_OPERAND_TYPE_MEMORY_MODEL: return IR(954, 4);
    case SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID: return IR(958, 15);
    case SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS: return IR(973, 1);
    case SPV_OPERAND_TYPE_OVERFLOW_MODES: return IR(974, 4);
    case SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT: return IR(978, 1);
    case SPV_OPERAND_TYPE_QUANTIZATION_MODES: return IR(979, 8);
    case SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS: return IR(987, 3);
    case SPV_OPERAND_TYPE_RAY_FLAGS: return IR(990, 12);
    case SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE: return IR(1002, 2);
    case SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE: return IR(1004, 3);
    case SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION: return IR(1007, 2);
    case SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE: return IR(1009, 5);
    case SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE: return IR(1014, 2);
    case SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT: return IR(1016, 42);
    case SPV_OPERAND_TYPE_SCOPE_ID: return IR(1058, 7);
    case SPV_OPERAND_TYPE_SELECTION_CONTROL: return IR(1065, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS: return IR(1068, 1);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(1069, 8);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(1077, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(1080, 2);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS: return IR(1082, 20);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION: return IR(1102, 10);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(1112, 4);
    case SPV_OPERAND_TYPE_SOURCE_LANGUAGE: return IR(1116, 14);
    case SPV_OPERAND_TYPE_STORAGE_CLASS: return IR(1130, 28);
    case SPV_OPERAND_TYPE_STORE_CACHE_CONTROL: return IR(1158, 4);
    case SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS: return IR(1162, 3);
    case SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE: return IR(1165, 5);
    case SPV_OPERAND_TYPE_TENSOR_OPERANDS: return IR(1170, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_IMAGE: return IR(830, 17);
    case SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS: return IR(945, 9);
    case SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT: return IR(978, 1);
    case SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS: return IR(464, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(930, 15);
    case SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS: return IR(987, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_FPENCODING: return IR(784, 1);
    case SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS: return IR(1170, 6);
    default: break;
  }
  return IR(0,0);
}

// Operand names and index into kOperandsByValue, ordered by (operand kind, name)
// The fields in order are:
//   name, either the primary name or an alias, indexing into kStrings
//   index into the kOperandsByValue array
static const std::array<NameIndex, 1270> kOperandNames{{
  {IR(4499, 9), 0}, // 0 ReadOnly in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(4525, 10), 2}, // 1 ReadWrite in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(4515, 10), 1}, // 2 WriteOnly in SPV_OPERAND_TYPE_ACCESS_QUALIFIER
  {IR(4535, 8), 3}, // 3 Logical in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(4543, 11), 4}, // 4 Physical32 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(4564, 11), 5}, // 5 Physical64 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(4575, 24), 6}, // 6 PhysicalStorageBuffer64 in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(4599, 27), 6}, // 7 PhysicalStorageBuffer64EXT in SPV_OPERAND_TYPE_ADDRESSING_MODEL
  {IR(6509, 13), 92}, // 8 BaryCoordKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6522, 12), 92}, // 9 BaryCoordNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5904, 20), 68}, // 10 BaryCoordNoPerspAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5924, 28), 69}, // 11 BaryCoordNoPerspCentroidAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6557, 20), 93}, // 12 BaryCoordNoPerspKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6577, 19), 93}, // 13 BaryCoordNoPerspNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5952, 26), 70}, // 14 BaryCoordNoPerspSampleAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6049, 22), 74}, // 15 BaryCoordPullModelAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5978, 19), 71}, // 16 BaryCoordSmoothAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5997, 27), 72}, // 17 BaryCoordSmoothCentroidAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6024, 25), 73}, // 18 BaryCoordSmoothSampleAMD in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5708, 13), 59}, // 19 BaseInstance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5682, 11), 58}, // 20 BaseVertex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4683, 13), 9}, // 21 ClipDistance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6416, 22), 87}, // 22 ClipDistancePerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7715, 12), 131}, // 23 ClusterIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5446, 13), 49}, // 24 CoreCountARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5420, 10), 48}, // 25 CoreIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5459, 13), 50}, // 26 CoreMaxIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4696, 13), 10}, // 27 CullDistance in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6438, 22), 88}, // 28 CullDistancePerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7768, 12), 132}, // 29 CullMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6764, 17), 99}, // 30 CullPrimitiveEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7168, 17), 113}, // 31 CurrentRayTimeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5778, 12), 62}, // 32 DeviceIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5721, 10), 60}, // 33 DrawIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5210, 22), 37}, // 34 EnqueuedWorkgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4980, 10), 21}, // 35 FragCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5066, 10), 27}, // 36 FragDepth in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6642, 23), 95}, // 37 FragInvocationCountEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6596, 12), 94}, // 38 FragSizeEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6071, 18), 75}, // 39 FragStencilRefEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6608, 15), 94}, // 40 FragmentSizeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5001, 12), 23}, // 41 FrontFacing in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6328, 16), 83}, // 42 FullyCoveredEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5151, 19), 33}, // 43 GlobalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5245, 15), 39}, // 44 GlobalLinearId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5232, 13), 38}, // 45 GlobalOffset in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5199, 11), 36}, // 46 GlobalSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5076, 17), 28}, // 47 HelperInvocation in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7470, 11), 120}, // 48 HitIsLSSNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7428, 14), 119}, // 49 HitIsSphereNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7650, 33), 128}, // 50 HitKindBackFacingMicroTriangleNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7616, 34), 127}, // 51 HitKindFrontFacingMicroTriangleNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7147, 11), 112}, // 52 HitKindKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7158, 10), 112}, // 53 HitKindNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7598, 18), 126}, // 54 HitLSSPositionsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7701, 14), 130}, // 55 HitLSSRadiiNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7332, 37), 116}, // 56 HitMicroTriangleVertexBarycentricsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7265, 34), 115}, // 57 HitMicroTriangleVertexPositionsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7520, 20), 121}, // 58 HitSpherePositionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7683, 18), 129}, // 59 HitSphereRadiusNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7140, 7), 111}, // 60 HitTNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7208, 30), 114}, // 61 HitTriangleVertexPositionsKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7369, 20), 117}, // 62 IncomingRayFlagsKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7389, 19), 117}, // 63 IncomingRayFlagsNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7029, 23), 108}, // 64 InstanceCustomIndexKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7052, 22), 108}, // 65 InstanceCustomIndexNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4718, 11), 12}, // 66 InstanceId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5406, 14), 47}, // 67 InstanceIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4819, 13), 14}, // 68 InvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6665, 22), 95}, // 69 InvocationsPerPixelNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6781, 12), 100}, // 70 LaunchIdKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6793, 11), 100}, // 71 LaunchIdNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6804, 14), 101}, // 72 LaunchSizeKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6818, 13), 101}, // 73 LaunchSizeNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4832, 6), 15}, // 74 Layer in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6460, 15), 89}, // 75 LayerPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5133, 18), 32}, // 76 LocalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5170, 21), 34}, // 77 LocalInvocationIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6475, 16), 90}, // 78 MeshViewCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6491, 18), 91}, // 79 MeshViewIndicesNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5336, 21), 43}, // 80 NumEnqueuedSubgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5323, 13), 42}, // 81 NumSubgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5093, 14), 29}, // 82 NumWorkgroups in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6944, 22), 105}, // 83 ObjectRayDirectionKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6966, 21), 105}, // 84 ObjectRayDirectionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6907, 19), 104}, // 85 ObjectRayOriginKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6926, 18), 104}, // 86 ObjectRayOriginNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7074, 17), 109}, // 87 ObjectToWorldKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7091, 16), 109}, // 88 ObjectToWorldNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4966, 14), 20}, // 89 PatchVertices in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4990, 11), 22}, // 90 PointCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4673, 10), 8}, // 91 PointSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4657, 9), 7}, // 92 Position in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6268, 18), 81}, // 93 PositionPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6380, 17), 85}, // 94 PrimitiveCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4729, 12), 13}, // 95 PrimitiveId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6397, 19), 86}, // 96 PrimitiveIndicesNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6712, 24), 97}, // 97 PrimitiveLineIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6687, 25), 96}, // 98 PrimitivePointIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5731, 24), 61}, // 99 PrimitiveShadingRateKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6736, 28), 98}, // 100 PrimitiveTriangleIndicesEXT in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7408, 20), 118}, // 101 RayGeometryIndexKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7008, 11), 107}, // 102 RayTmaxKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7019, 10), 107}, // 103 RayTmaxNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6987, 11), 106}, // 104 RayTminKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6998, 10), 106}, // 105 RayTminNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6106, 29), 76}, // 106 RemainingRecursionLevelsAMDX in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7572, 10), 123}, // 107 SMCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7591, 7), 125}, // 108 SMIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5013, 9), 24}, // 109 SampleId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5055, 11), 26}, // 110 SampleMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5040, 15), 25}, // 111 SamplePosition in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6205, 20), 79}, // 112 SecondaryPositionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6244, 24), 80}, // 113 SecondaryViewportMaskNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6153, 16), 77}, // 114 ShaderIndexAMDX in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5822, 15), 64}, // 115 ShadingRateKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5495, 15), 53}, // 116 SubgroupEqMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5510, 18), 53}, // 117 SubgroupEqMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5550, 15), 54}, // 118 SubgroupGeMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5565, 18), 54}, // 119 SubgroupGeMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5583, 15), 55}, // 120 SubgroupGtMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5598, 18), 55}, // 121 SubgroupGtMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5357, 11), 44}, // 122 SubgroupId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5616, 15), 56}, // 123 SubgroupLeMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5631, 18), 56}, // 124 SubgroupLeMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5368, 26), 45}, // 125 SubgroupLocalInvocationId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5649, 15), 57}, // 126 SubgroupLtMask in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5664, 18), 57}, // 127 SubgroupLtMaskKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5307, 16), 41}, // 128 SubgroupMaxSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5260, 13), 40}, // 129 SubgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6368, 12), 84}, // 130 TaskCountNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4956, 10), 19}, // 131 TessCoord in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4941, 15), 18}, // 132 TessLevelInner in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4926, 15), 17}, // 133 TessLevelOuter in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5886, 18), 67}, // 134 TileApronSizeQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5868, 18), 66}, // 135 TileDimensionQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5837, 15), 65}, // 136 TileOffsetQCOM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4709, 9), 11}, // 137 VertexId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5394, 12), 46}, // 138 VertexIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5802, 10), 63}, // 139 ViewIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4878, 14), 16}, // 140 ViewportIndex in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6169, 15), 78}, // 141 ViewportMaskNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6306, 22), 82}, // 142 ViewportMaskPerViewNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5472, 10), 51}, // 143 WarpIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7582, 9), 124}, // 144 WarpIDNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5482, 13), 52}, // 145 WarpMaxIDARM in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7540, 13), 122}, // 146 WarpsPerSMNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5191, 8), 35}, // 147 WorkDim in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5121, 12), 31}, // 148 WorkgroupId in SPV_OPERAND_TYPE_BUILT_IN
  {IR(5107, 14), 30}, // 149 WorkgroupSize in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6866, 21), 103}, // 150 WorldRayDirectionKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6887, 20), 103}, // 151 WorldRayDirectionNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6831, 18), 102}, // 152 WorldRayOriginKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(6849, 17), 102}, // 153 WorldRayOriginNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7107, 17), 110}, // 154 WorldToObjectKHR in SPV_OPERAND_TYPE_BUILT_IN
  {IR(7124, 16), 110}, // 155 WorldToObjectNV in SPV_OPERAND_TYPE_BUILT_IN
  {IR(4554, 10), 137}, // 156 Addresses in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12707, 34), 355}, // 157 ArbitraryPrecisionFixedPointINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12395, 37), 343}, // 158 ArbitraryPrecisionFloatingPointINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12363, 32), 342}, // 159 ArbitraryPrecisionIntegersINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13257, 19), 379}, // 160 ArithmeticFenceEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12028, 9), 328}, // 161 AsmINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13174, 20), 375}, // 162 AtomicFloat16AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12083, 23), 331}, // 163 AtomicFloat16MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11556, 22), 306}, // 164 AtomicFloat16VectorNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13090, 20), 371}, // 165 AtomicFloat32AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12037, 23), 329}, // 166 AtomicFloat32MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13110, 20), 372}, // 167 AtomicFloat64AddEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12060, 23), 330}, // 168 AtomicFloat64MinMaxEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7948, 14), 153}, // 169 AtomicStorage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9268, 17), 226}, // 170 AtomicStorageOps in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13215, 24), 377}, // 171 BFloat16ConversionINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9879, 29), 259}, // 172 BFloat16CooperativeMatrixKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9857, 22), 258}, // 173 BFloat16DotProductKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9841, 16), 257}, // 174 BFloat16TypeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11493, 18), 303}, // 175 BindlessTextureNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13034, 16), 368}, // 176 BitInstructions in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12806, 19), 359}, // 177 BlockingPipesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13739, 19), 397}, // 178 CacheControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4683, 13), 163}, // 179 ClipDistance in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11151, 32), 292}, // 180 ComputeDerivativeGroupLinearKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11183, 31), 292}, // 181 ComputeDerivativeGroupLinearNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10031, 31), 271}, // 182 ComputeDerivativeGroupQuadsKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10062, 30), 271}, // 183 ComputeDerivativeGroupQuadsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11733, 30), 315}, // 184 CooperativeMatrixBlockLoadsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11626, 31), 312}, // 185 CooperativeMatrixConversionsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9820, 21), 366}, // 186 CooperativeMatrixKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8909, 28), 210}, // 187 CooperativeMatrixLayoutsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11239, 20), 294}, // 188 CooperativeMatrixNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11657, 40), 313}, // 189 CooperativeMatrixPerElementOperationsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11596, 30), 311}, // 190 CooperativeMatrixReductionsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11697, 36), 314}, // 191 CooperativeMatrixTensorAddressingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11536, 20), 305}, // 192 CooperativeVectorNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11763, 28), 316}, // 193 CooperativeVectorTrainingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5430, 16), 203}, // 194 CoreBuiltinsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4696, 13), 164}, // 195 CullDistance in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13194, 21), 376}, // 196 DebugInfoModuleINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11362, 25), 299}, // 197 DemoteToHelperInvocation in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11387, 28), 299}, // 198 DemoteToHelperInvocationEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9407, 18), 232}, // 199 DenormFlushToZero in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9392, 15), 231}, // 200 DenormPreserve in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8395, 18), 182}, // 201 DerivativeControl in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7919, 14), 151}, // 202 DeviceEnqueue in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5790, 12), 222}, // 203 DeviceGroup in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11415, 23), 300}, // 204 DisplacementMicromapNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12985, 11), 364}, // 205 DotProduct in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12879, 22), 362}, // 206 DotProductInput4x8Bit in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12901, 25), 362}, // 207 DotProductInput4x8BitKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12926, 28), 363}, // 208 DotProductInput4x8BitPacked in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12954, 31), 363}, // 209 DotProductInput4x8BitPackedKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12838, 19), 361}, // 210 DotProductInputAll in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12857, 22), 361}, // 211 DotProductInputAllKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12996, 14), 364}, // 212 DotProductKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5693, 15), 213}, // 213 DrawParameters in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12140, 16), 334}, // 214 ExpectAssumeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12343, 20), 341}, // 215 FPFastMathModeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13391, 28), 385}, // 216 FPGAArgumentInterfacesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12683, 24), 354}, // 217 FPGABufferLocationINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12556, 27), 349}, // 218 FPGAClusterAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13276, 29), 380}, // 219 FPGAClusterAttributesV2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12597, 20), 351}, // 220 FPGADSPControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12643, 40), 353}, // 221 FPGAInvocationPipeliningAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12506, 26), 347}, // 222 FPGAKernelAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13305, 28), 381}, // 223 FPGAKernelAttributesv2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13367, 24), 384}, // 224 FPGALatencyControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12462, 22), 345}, // 225 FPGALoopControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12532, 24), 348}, // 226 FPGAMemoryAccessesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12317, 26), 340}, // 227 FPGAMemoryAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12825, 13), 360}, // 228 FPGARegINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13351, 16), 383}, // 229 FPMaxErrorINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7833, 8), 142}, // 230 Float16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7819, 14), 141}, // 231 Float16Buffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9660, 16), 246}, // 232 Float16ImageAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7841, 8), 143}, // 233 Float64 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13075, 15), 370}, // 234 FloatControls2 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11936, 23), 324}, // 235 FloatingPointModeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6534, 23), 270}, // 236 FragmentBarycentricKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10009, 22), 270}, // 237 FragmentBarycentricNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6623, 19), 272}, // 238 FragmentDensityEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6344, 24), 266}, // 239 FragmentFullyCoveredEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9698, 16), 248}, // 240 FragmentMaskAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11330, 32), 298}, // 241 FragmentShaderPixelInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11259, 33), 295}, // 242 FragmentShaderSampleInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11292, 38), 296}, // 243 FragmentShaderShadingRateInterlockEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5755, 23), 211}, // 244 FragmentShadingRateKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12291, 26), 339}, // 245 FunctionFloatControlINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11982, 22), 326}, // 246 FunctionPointersINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8240, 15), 169}, // 247 GenericPointer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4741, 9), 135}, // 248 Geometry in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7990, 18), 156}, // 249 GeometryPointSize in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9937, 28), 261}, // 250 GeometryShaderPassthroughNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8453, 16), 185}, // 251 GeometryStreams in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13449, 35), 387}, // 252 GlobalVariableFPGADecorationsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13419, 30), 386}, // 253 GlobalVariableHostAccessINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5273, 16), 192}, // 254 GroupNonUniform in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8592, 26), 194}, // 255 GroupNonUniformArithmetic in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5528, 22), 195}, // 256 GroupNonUniformBallot in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8672, 25), 198}, // 257 GroupNonUniformClustered in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10106, 29), 273}, // 258 GroupNonUniformPartitionedNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8697, 20), 199}, // 259 GroupNonUniformQuad in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13050, 25), 369}, // 260 GroupNonUniformRotateKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8618, 23), 196}, // 261 GroupNonUniformShuffle in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8641, 31), 197}, // 262 GroupNonUniformShuffleRelative in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8572, 20), 193}, // 263 GroupNonUniformVote in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13661, 26), 394}, // 264 GroupUniformArithmeticKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7912, 7), 150}, // 265 Groups in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12793, 13), 358}, // 266 IOPipesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8309, 8), 175}, // 267 Image1D in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7868, 11), 146}, // 268 ImageBasic in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8331, 12), 178}, // 269 ImageBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8186, 15), 165}, // 270 ImageCubeArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9992, 17), 268}, // 271 ImageFootprintNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9676, 22), 247}, // 272 ImageGatherBiasLodAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8008, 20), 157}, // 273 ImageGatherExtended in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8343, 13), 179}, // 274 ImageMSArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7894, 12), 148}, // 275 ImageMipmap in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8384, 11), 181}, // 276 ImageQuery in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7879, 15), 147}, // 277 ImageReadWrite in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9714, 21), 250}, // 278 ImageReadWriteLodAMD in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8218, 10), 167}, // 279 ImageRect in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12004, 24), 327}, // 280 IndirectReferencesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8260, 16), 171}, // 281 InputAttachment in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10221, 36), 276}, // 282 InputAttachmentArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10257, 39), 276}, // 283 InputAttachmentArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10762, 39), 283}, // 284 InputAttachmentArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10801, 42), 283}, // 285 InputAttachmentArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7962, 6), 154}, // 286 Int16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9793, 27), 256}, // 287 Int4CooperativeMatrixINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9779, 14), 255}, // 288 Int4TypeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7849, 6), 144}, // 289 Int64 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7855, 13), 145}, // 290 Int64Atomics in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9735, 14), 251}, // 291 Int64ImageEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8255, 5), 170}, // 292 Int8 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11959, 23), 325}, // 293 IntegerFunctions2INTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8413, 22), 183}, // 294 InterpolationFunction in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4508, 7), 139}, // 295 Kernel in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12484, 22), 346}, // 296 KernelAttributesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7802, 8), 138}, // 297 Linkage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7933, 15), 152}, // 298 LiteralSampler in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13130, 20), 373}, // 299 LongCompositesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12583, 14), 350}, // 300 LoopFuseINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13714, 25), 396}, // 301 MaskedGatherScatterINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7795, 7), 133}, // 302 Matrix in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12617, 26), 352}, // 303 MemoryAccessAliasingINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4804, 15), 269}, // 304 MeshShadingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4790, 14), 267}, // 305 MeshShadingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8292, 7), 173}, // 306 MinLod in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5812, 10), 223}, // 307 MultiView in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4892, 14), 188}, // 308 MultiViewport in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8547, 13), 190}, // 309 NamedBarrier in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13150, 11), 374}, // 310 OptNoneEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13161, 13), 374}, // 311 OptNoneINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6286, 20), 265}, // 312 PerViewAttributesNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4626, 31), 291}, // 313 PhysicalStorageBufferAddresses in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11117, 34), 291}, // 314 PhysicalStorageBufferAddressesEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8560, 12), 191}, // 315 PipeStorage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7906, 6), 149}, // 316 Pipes in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9764, 15), 254}, // 317 QuadControlKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11578, 18), 308}, // 318 RawAccessChainsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7780, 15), 365}, // 319 RayCullMaskKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9505, 12), 237}, // 320 RayQueryKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11511, 25), 304}, // 321 RayQueryPositionFetchKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9482, 23), 236}, // 322 RayQueryProvisionalKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7727, 41), 317}, // 323 RayTracingClusterAccelerationStructureNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7299, 33), 307}, // 324 RayTracingDisplacementMicromapNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4776, 14), 240}, // 325 RayTracingKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7481, 39), 310}, // 326 RayTracingLinearSweptSpheresGeometryNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7185, 23), 288}, // 327 RayTracingMotionBlurNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4763, 13), 287}, // 328 RayTracingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11438, 29), 301}, // 329 RayTracingOpacityMicromapEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7238, 27), 286}, // 330 RayTracingPositionFetchKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11214, 25), 293}, // 331 RayTracingProvisionalKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7442, 28), 309}, // 332 RayTracingSpheresGeometryNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9536, 32), 239}, // 333 RayTraversalPrimitiveCullingKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13758, 20), 398}, // 334 RegisterLimitsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13010, 24), 367}, // 335 ReplicatedCompositesEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11915, 21), 323}, // 336 RoundToInfinityINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9450, 16), 234}, // 337 RoundingModeRTE in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9466, 16), 235}, // 338 RoundingModeRTZ in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12764, 29), 357}, // 339 RuntimeAlignedAttributeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10172, 23), 275}, // 340 RuntimeDescriptorArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10195, 26), 275}, // 341 RuntimeDescriptorArrayEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9908, 29), 260}, // 342 SampleMaskOverrideCoverageNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9285, 28), 227}, // 343 SampleMaskPostDepthCoverage in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5022, 18), 166}, // 344 SampleRateShading in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8299, 10), 174}, // 345 Sampled1D in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8317, 14), 177}, // 346 SampledBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8201, 17), 176}, // 347 SampledCubeArray in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8086, 33), 160}, // 348 SampledImageArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10535, 36), 280}, // 349 SampledImageArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10571, 39), 280}, // 350 SampledImageArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8228, 12), 168}, // 351 SampledRect in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4666, 7), 134}, // 352 Shader in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9749, 15), 252}, // 353 ShaderClockKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6135, 18), 253}, // 354 ShaderEnqueueAMDX in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11467, 26), 302}, // 355 ShaderInvocationReorderNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4838, 12), 200}, // 356 ShaderLayer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10135, 17), 274}, // 357 ShaderNonUniform in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10152, 20), 274}, // 358 ShaderNonUniformEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7553, 19), 297}, // 359 ShaderSMBuiltinsNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6225, 19), 264}, // 360 ShaderStereoViewNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4906, 20), 201}, // 361 ShaderViewportIndex in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4850, 28), 262}, // 362 ShaderViewportIndexLayerEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9965, 27), 262}, // 363 ShaderViewportIndexLayerNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6184, 21), 263}, // 364 ShaderViewportMaskNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10092, 14), 272}, // 365 ShadingRateNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9425, 25), 233}, // 366 SignedZeroInfNanPreserve in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8276, 16), 172}, // 367 SparseResidency in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13239, 18), 378}, // 368 SplitBarrierINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(6089, 17), 249}, // 369 StencilExportEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9073, 25), 218}, // 370 StorageBuffer16BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9313, 24), 228}, // 371 StorageBuffer8BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8119, 34), 161}, // 372 StorageBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10610, 37), 281}, // 373 StorageBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10647, 40), 281}, // 374 StorageBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8153, 33), 162}, // 375 StorageImageArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10687, 36), 282}, // 376 StorageImageArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10723, 39), 282}, // 377 StorageImageArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8356, 28), 180}, // 378 StorageImageExtendedFormats in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8028, 24), 158}, // 379 StorageImageMultisample in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8469, 30), 186}, // 380 StorageImageReadWithoutFormat in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8499, 31), 187}, // 381 StorageImageWriteWithoutFormat in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9200, 21), 221}, // 382 StorageInputOutput16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9178, 22), 220}, // 383 StoragePushConstant16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9371, 21), 230}, // 384 StoragePushConstant8 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8832, 37), 208}, // 385 StorageTensorArrayDynamicIndexingARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8869, 40), 209}, // 386 StorageTensorArrayNonUniformIndexingARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10377, 39), 278}, // 387 StorageTexelBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10416, 42), 278}, // 388 StorageTexelBufferArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10930, 42), 285}, // 389 StorageTexelBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10972, 45), 285}, // 390 StorageTexelBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9161, 17), 219}, // 391 StorageUniform16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9098, 28), 218}, // 392 StorageUniformBufferBlock16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13512, 23), 389}, // 393 Subgroup2DBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13535, 30), 390}, // 394 Subgroup2DBlockTransformINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13565, 30), 391}, // 395 Subgroup2DBlockTransposeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12227, 39), 337}, // 396 SubgroupAvcMotionEstimationChromaINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12156, 33), 335}, // 397 SubgroupAvcMotionEstimationINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12189, 38), 336}, // 398 SubgroupAvcMotionEstimationIntraINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5289, 18), 212}, // 399 SubgroupBallotKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11831, 27), 320}, // 400 SubgroupBufferBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13484, 28), 388}, // 401 SubgroupBufferPrefetchINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8530, 17), 189}, // 402 SubgroupDispatch in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11858, 26), 321}, // 403 SubgroupImageBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11884, 31), 322}, // 404 SubgroupImageMediaBlockIOINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13595, 38), 392}, // 405 SubgroupMatrixMultiplyAccumulateINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11810, 21), 319}, // 406 SubgroupShuffleINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9057, 16), 217}, // 407 SubgroupVoteKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13333, 18), 382}, // 408 TaskSequenceINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11791, 19), 318}, // 409 TensorAddressingNV in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13687, 27), 395}, // 410 TensorFloat32RoundingINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8821, 11), 207}, // 411 TensorsARM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13633, 28), 393}, // 412 TernaryBitwiseFunctionINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(4750, 13), 136}, // 413 Tessellation in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7968, 22), 155}, // 414 TessellationPointSize in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9637, 23), 245}, // 415 TextureBlockMatch2QCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9615, 22), 243}, // 416 TextureBlockMatchQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9594, 21), 242}, // 417 TextureBoxFilterQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9568, 26), 241}, // 418 TextureSampleWeightedQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8735, 28), 204}, // 419 TileImageColorReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8763, 28), 205}, // 420 TileImageDepthReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8791, 30), 206}, // 421 TileImageStencilReadAccessEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(5852, 16), 244}, // 422 TileShadingQCOM in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8435, 18), 184}, // 423 TransformFeedback in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12741, 23), 356}, // 424 USMStorageClassesINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9126, 35), 219}, // 425 UniformAndStorageBuffer16BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9337, 34), 229}, // 426 UniformAndStorageBuffer8BitAccess in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8052, 34), 159}, // 427 UniformBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10458, 37), 279}, // 428 UniformBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10495, 40), 279}, // 429 UniformBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8717, 18), 202}, // 430 UniformDecoration in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10296, 39), 277}, // 431 UniformTexelBufferArrayDynamicIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10335, 42), 277}, // 432 UniformTexelBufferArrayDynamicIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10843, 42), 284}, // 433 UniformTexelBufferArrayNonUniformIndexing in SPV_OPERAND_TYPE_CAPABILITY
  {IR(10885, 45), 284}, // 434 UniformTexelBufferArrayNonUniformIndexingEXT in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12432, 30), 344}, // 435 UnstructuredLoopControlsINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9517, 19), 238}, // 436 UntypedPointersKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12266, 25), 338}, // 437 VariableLengthArrayINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9251, 17), 225}, // 438 VariablePointers in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9221, 30), 224}, // 439 VariablePointersStorageBuffer in SPV_OPERAND_TYPE_CAPABILITY
  {IR(7810, 9), 140}, // 440 Vector16 in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12125, 15), 333}, // 441 VectorAnyINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(12106, 19), 332}, // 442 VectorComputeINTEL in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11017, 18), 289}, // 443 VulkanMemoryModel in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11056, 29), 290}, // 444 VulkanMemoryModelDeviceScope in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11085, 32), 290}, // 445 VulkanMemoryModelDeviceScopeKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(11035, 21), 289}, // 446 VulkanMemoryModelKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(9013, 44), 216}, // 447 WorkgroupMemoryExplicitLayout16BitAccessKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8970, 43), 215}, // 448 WorkgroupMemoryExplicitLayout8BitAccessKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(8937, 33), 214}, // 449 WorkgroupMemoryExplicitLayoutKHR in SPV_OPERAND_TYPE_CAPABILITY
  {IR(13790, 8), 400}, // 450 Address in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13798, 8), 401}, // 451 Boolean in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13806, 6), 402}, // 452 Float in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13812, 7), 403}, // 453 Signed in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13819, 11), 404}, // 454 SignedChar in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13830, 9), 405}, // 455 Unsigned in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13839, 13), 406}, // 456 UnsignedChar in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13778, 12), 399}, // 457 Unspecified in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13852, 6), 407}, // 458 Class in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(13858, 10), 408}, // 459 Structure in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(13868, 6), 409}, // 460 Union in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(13889, 20), 411}, // 461 ImportedDeclaration in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(13874, 15), 410}, // 462 ImportedModule in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(13998, 15), 419}, // 463 FlagArtificial in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14013, 13), 420}, // 464 FlagExplicit in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(13986, 12), 418}, // 465 FlagFwdDecl in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14076, 21), 424}, // 466 FlagIndirectVariable in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(13969, 17), 417}, // 467 FlagIsDefinition in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14153, 16), 428}, // 468 FlagIsEnumClass in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(13957, 12), 416}, // 469 FlagIsLocal in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14137, 16), 427}, // 470 FlagIsOptimized in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(13930, 14), 414}, // 471 FlagIsPrivate in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(13914, 16), 413}, // 472 FlagIsProtected in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(13944, 13), 415}, // 473 FlagIsPublic in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14097, 20), 425}, // 474 FlagLValueReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14041, 18), 422}, // 475 FlagObjectPointer in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14026, 15), 421}, // 476 FlagPrototyped in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14117, 20), 426}, // 477 FlagRValueReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14059, 17), 423}, // 478 FlagStaticMember in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14189, 24), 430}, // 479 FlagTypePassByReference in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14169, 20), 429}, // 480 FlagTypePassByValue in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(13909, 5), 412}, // 481 None in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS
  {IR(14274, 9), 435}, // 482 BitPiece in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14306, 7), 439}, // 483 Constu in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14213, 6), 431}, // 484 Deref in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14313, 9), 440}, // 485 Fragment in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14224, 6), 433}, // 486 Minus in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14219, 5), 432}, // 487 Plus in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14263, 11), 434}, // 488 PlusUconst in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14295, 11), 438}, // 489 StackValue in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14283, 5), 436}, // 490 Swap in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14288, 7), 437}, // 491 Xderef in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION
  {IR(14358, 11), 444}, // 492 AtomicType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14322, 10), 441}, // 493 ConstType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14345, 13), 443}, // 494 RestrictType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14332, 13), 442}, // 495 VolatileType in SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14369, 10), 445}, // 496 Float16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14379, 10), 446}, // 497 Float32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14389, 10), 447}, // 498 Float64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14557, 12), 458}, // 499 FloatE4M3NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14569, 12), 459}, // 500 FloatE5M2NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14412, 14), 449}, // 501 SignedInt16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14426, 14), 450}, // 502 SignedInt32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14440, 14), 451}, // 503 SignedInt64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14399, 13), 448}, // 504 SignedInt8NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14517, 19), 456}, // 505 SignedInt8PackedNV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14469, 16), 453}, // 506 UnsignedInt16NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14485, 16), 454}, // 507 UnsignedInt32NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14501, 16), 455}, // 508 UnsignedInt64NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14454, 15), 452}, // 509 UnsignedInt8NV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14536, 21), 457}, // 510 UnsignedInt8PackedNV in SPV_OPERAND_TYPE_COMPONENT_TYPE
  {IR(14633, 28), 463}, // 511 ColumnBlockedInterleavedARM in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(14593, 15), 461}, // 512 ColumnMajorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(14608, 25), 462}, // 513 RowBlockedInterleavedARM in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(14581, 12), 460}, // 514 RowMajorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT
  {IR(14669, 27), 465}, // 515 MatrixASignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(14696, 27), 466}, // 516 MatrixBSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(14723, 27), 467}, // 517 MatrixCSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(14750, 32), 468}, // 518 MatrixResultSignedComponentsKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(14661, 8), 464}, // 519 NoneKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(14782, 26), 469}, // 520 SaturatingAccumulationKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS
  {IR(14819, 4), 472}, // 521 2x2 in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(14812, 7), 471}, // 522 Column in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(14808, 4), 470}, // 523 Row in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE
  {IR(14823, 11), 473}, // 524 MatrixAKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(14845, 21), 475}, // 525 MatrixAccumulatorKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(14834, 11), 474}, // 526 MatrixBKHR in SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE
  {IR(14877, 14), 477}, // 527 ColumnMajorNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(14891, 21), 478}, // 528 InferencingOptimalNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(14866, 11), 476}, // 529 RowMajorNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(14912, 18), 479}, // 530 TrainingOptimalNV in SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT
  {IR(13790, 8), 481}, // 531 Address in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13798, 8), 482}, // 532 Boolean in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13806, 6), 483}, // 533 Float in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13812, 7), 484}, // 534 Signed in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13819, 11), 485}, // 535 SignedChar in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13830, 9), 486}, // 536 Unsigned in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13839, 13), 487}, // 537 UnsignedChar in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13778, 12), 480}, // 538 Unspecified in SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13852, 6), 488}, // 539 Class in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(13858, 10), 489}, // 540 Structure in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(13868, 6), 490}, // 541 Union in SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE
  {IR(13998, 15), 498}, // 542 FlagArtificial in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14013, 13), 499}, // 543 FlagExplicit in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(13986, 12), 497}, // 544 FlagFwdDecl in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14076, 21), 503}, // 545 FlagIndirectVariable in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(13969, 17), 496}, // 546 FlagIsDefinition in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(13957, 12), 495}, // 547 FlagIsLocal in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14137, 16), 506}, // 548 FlagIsOptimized in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(13930, 14), 493}, // 549 FlagIsPrivate in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(13914, 16), 492}, // 550 FlagIsProtected in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(13944, 13), 494}, // 551 FlagIsPublic in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14097, 20), 504}, // 552 FlagLValueReference in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14041, 18), 501}, // 553 FlagObjectPointer in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14026, 15), 500}, // 554 FlagPrototyped in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14117, 20), 505}, // 555 FlagRValueReference in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14059, 17), 502}, // 556 FlagStaticMember in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(13909, 5), 491}, // 557 None in SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS
  {IR(14274, 9), 511}, // 558 BitPiece in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14306, 7), 515}, // 559 Constu in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14213, 6), 507}, // 560 Deref in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14224, 6), 509}, // 561 Minus in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14219, 5), 508}, // 562 Plus in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14263, 11), 510}, // 563 PlusUconst in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14295, 11), 514}, // 564 StackValue in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14283, 5), 512}, // 565 Swap in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14288, 7), 513}, // 566 Xderef in SPV_OPERAND_TYPE_DEBUG_OPERATION
  {IR(14322, 10), 516}, // 567 ConstType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(14345, 13), 518}, // 568 RestrictType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(14332, 13), 517}, // 569 VolatileType in SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER
  {IR(17110, 16), 632}, // 570 AliasScopeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15139, 8), 538}, // 571 Aliased in SPV_OPERAND_TYPE_DECORATION
  {IR(16213, 15), 590}, // 572 AliasedPointer in SPV_OPERAND_TYPE_DECORATION
  {IR(16228, 18), 590}, // 573 AliasedPointerEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(15617, 10), 562}, // 574 Alignment in SPV_OPERAND_TYPE_DECORATION
  {IR(15661, 12), 564}, // 575 AlignmentId in SPV_OPERAND_TYPE_DECORATION
  {IR(14990, 12), 525}, // 576 ArrayStride in SPV_OPERAND_TYPE_DECORATION
  {IR(16891, 14), 620}, // 577 BankBitsINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16730, 15), 613}, // 578 BankwidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15294, 8), 551}, // 579 Binding in SPV_OPERAND_TYPE_DECORATION
  {IR(16294, 16), 593}, // 580 BindlessImageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16276, 18), 592}, // 581 BindlessSamplerNV in SPV_OPERAND_TYPE_DECORATION
  {IR(14954, 6), 521}, // 582 Block in SPV_OPERAND_TYPE_DECORATION
  {IR(15757, 22), 570}, // 583 BlockMatchSamplerQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(15735, 22), 569}, // 584 BlockMatchTextureQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(16325, 13), 595}, // 585 BoundImageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16310, 15), 594}, // 586 BoundSamplerNV in SPV_OPERAND_TYPE_DECORATION
  {IR(14960, 12), 522}, // 587 BufferBlock in SPV_OPERAND_TYPE_DECORATION
  {IR(17203, 20), 637}, // 588 BufferLocationINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15071, 8), 530}, // 589 BuiltIn in SPV_OPERAND_TYPE_DECORATION
  {IR(16973, 19), 625}, // 590 BurstCoalesceINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15037, 8), 529}, // 591 CPacked in SPV_OPERAND_TYPE_DECORATION
  {IR(17996, 22), 659}, // 592 CacheControlLoadINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(18055, 23), 660}, // 593 CacheControlStoreINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16992, 15), 626}, // 594 CacheSizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15104, 9), 534}, // 595 Centroid in SPV_OPERAND_TYPE_DECORATION
  {IR(16378, 13), 598}, // 596 ClobberINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15165, 9), 541}, // 597 Coherent in SPV_OPERAND_TYPE_DECORATION
  {IR(14981, 9), 524}, // 598 ColMajor in SPV_OPERAND_TYPE_DECORATION
  {IR(15278, 10), 549}, // 599 Component in SPV_OPERAND_TYPE_DECORATION
  {IR(17512, 27), 647}, // 600 ConduitKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15156, 9), 540}, // 601 Constant in SPV_OPERAND_TYPE_DECORATION
  {IR(16524, 14), 605}, // 602 CounterBuffer in SPV_OPERAND_TYPE_DECORATION
  {IR(15302, 14), 552}, // 603 DescriptorSet in SPV_OPERAND_TYPE_DECORATION
  {IR(17007, 28), 627}, // 604 DontStaticallyCoalesceINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16783, 16), 616}, // 605 DoublepumpINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15779, 18), 571}, // 606 ExplicitInterpAMD in SPV_OPERAND_TYPE_DECORATION
  {IR(15487, 15), 558}, // 607 FPFastMathMode in SPV_OPERAND_TYPE_DECORATION
  {IR(17431, 26), 644}, // 608 FPMaxErrorDecorationINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15437, 15), 557}, // 609 FPRoundingMode in SPV_OPERAND_TYPE_DECORATION
  {IR(15093, 5), 532}, // 610 Flat in SPV_OPERAND_TYPE_DECORATION
  {IR(16905, 20), 621}, // 611 ForcePow2DepthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15389, 14), 556}, // 612 FuncParamAttr in SPV_OPERAND_TYPE_DECORATION
  {IR(16435, 21), 601}, // 613 FuncParamIOKindINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16666, 24), 609}, // 614 FunctionDenormModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17276, 31), 639}, // 615 FunctionFloatingPointModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16609, 26), 608}, // 616 FunctionRoundingModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17066, 25), 630}, // 617 FuseLoopsInFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15026, 11), 528}, // 618 GLSLPacked in SPV_OPERAND_TYPE_DECORATION
  {IR(15015, 11), 527}, // 619 GLSLShared in SPV_OPERAND_TYPE_DECORATION
  {IR(16498, 26), 604}, // 620 GlobalVariableOffsetINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16246, 30), 591}, // 621 HitObjectShaderRecordBufferNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16538, 24), 605}, // 622 HlslCounterBufferGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(16575, 19), 606}, // 623 HlslSemanticGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(17855, 16), 656}, // 624 HostAccessINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17223, 19), 638}, // 625 IOPipeStorageINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17932, 28), 658}, // 626 ImplementInRegisterMapINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15288, 6), 550}, // 627 Index in SPV_OPERAND_TYPE_DECORATION
  {IR(17918, 14), 657}, // 628 InitModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17139, 24), 634}, // 629 InitiationIntervalINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15596, 21), 561}, // 630 InputAttachmentIndex in SPV_OPERAND_TYPE_DECORATION
  {IR(15120, 10), 536}, // 631 Invariant in SPV_OPERAND_TYPE_DECORATION
  {IR(17482, 30), 646}, // 632 LatencyControlConstraintINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17457, 25), 645}, // 633 LatencyControlLabelINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15564, 18), 559}, // 634 LinkageAttributes in SPV_OPERAND_TYPE_DECORATION
  {IR(15269, 9), 548}, // 635 Location in SPV_OPERAND_TYPE_DECORATION
  {IR(17570, 33), 649}, // 636 MMHostInterfaceAddressWidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17603, 30), 650}, // 637 MMHostInterfaceDataWidthINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17633, 28), 651}, // 638 MMHostInterfaceLatencyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17729, 29), 653}, // 639 MMHostInterfaceMaxBurstINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17695, 34), 652}, // 640 MMHostInterfaceReadWriteModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17758, 32), 654}, // 641 MMHostInterfaceWaitRequestINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17091, 19), 631}, // 642 MathOpDSPModeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15002, 13), 526}, // 643 MatrixStride in SPV_OPERAND_TYPE_DECORATION
  {IR(15627, 14), 563}, // 644 MaxByteOffset in SPV_OPERAND_TYPE_DECORATION
  {IR(15673, 16), 565}, // 645 MaxByteOffsetId in SPV_OPERAND_TYPE_DECORATION
  {IR(17163, 20), 635}, // 646 MaxConcurrencyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16745, 22), 614}, // 647 MaxPrivateCopiesINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16799, 19), 617}, // 648 MaxReplicatesINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17367, 18), 642}, // 649 MediaBlockIOINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16704, 12), 611}, // 650 MemoryINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16838, 11), 619}, // 651 MergeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17126, 13), 633}, // 652 NoAliasINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15582, 14), 560}, // 653 NoContraction in SPV_OPERAND_TYPE_DECORATION
  {IR(15079, 14), 531}, // 654 NoPerspective in SPV_OPERAND_TYPE_DECORATION
  {IR(15689, 13), 566}, // 655 NoSignedWrap in SPV_OPERAND_TYPE_DECORATION
  {IR(15702, 15), 567}, // 656 NoUnsignedWrap in SPV_OPERAND_TYPE_DECORATION
  {IR(15829, 20), 573}, // 657 NodeMaxPayloadsAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(15797, 32), 572}, // 658 NodeSharesPayloadLimitsWithAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(15186, 12), 543}, // 659 NonReadable in SPV_OPERAND_TYPE_DECORATION
  {IR(16153, 11), 588}, // 660 NonUniform in SPV_OPERAND_TYPE_DECORATION
  {IR(16164, 14), 588}, // 661 NonUniformEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(15174, 12), 542}, // 662 NonWritable in SPV_OPERAND_TYPE_DECORATION
  {IR(16716, 14), 612}, // 663 NumbanksINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15316, 7), 553}, // 664 Offset in SPV_OPERAND_TYPE_DECORATION
  {IR(15997, 19), 580}, // 665 OverrideCoverageNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16016, 14), 581}, // 666 PassthroughNV in SPV_OPERAND_TYPE_DECORATION
  {IR(15098, 6), 533}, // 667 Patch in SPV_OPERAND_TYPE_DECORATION
  {IR(15969, 28), 579}, // 668 PayloadDispatchIndirectAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(15944, 25), 578}, // 669 PayloadNodeArraySizeAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(15892, 25), 576}, // 670 PayloadNodeBaseIndexAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(15872, 20), 575}, // 671 PayloadNodeNameAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(15917, 27), 577}, // 672 PayloadNodeSparseArrayAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(16077, 16), 584}, // 673 PerPrimitiveEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(16093, 15), 584}, // 674 PerPrimitiveNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16118, 10), 586}, // 675 PerTaskNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16128, 13), 587}, // 676 PerVertexKHR in SPV_OPERAND_TYPE_DECORATION
  {IR(16141, 12), 587}, // 677 PerVertexNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16108, 10), 585}, // 678 PerViewNV in SPV_OPERAND_TYPE_DECORATION
  {IR(17183, 20), 636}, // 679 PipelineEnableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17035, 14), 628}, // 680 PrefetchINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16352, 26), 597}, // 681 ReferencedIndirectlyINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16690, 14), 610}, // 682 RegisterINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17539, 31), 648}, // 683 RegisterMapKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(14930, 17), 519}, // 684 RelaxedPrecision in SPV_OPERAND_TYPE_DECORATION
  {IR(15130, 9), 537}, // 685 Restrict in SPV_OPERAND_TYPE_DECORATION
  {IR(16178, 16), 589}, // 686 RestrictPointer in SPV_OPERAND_TYPE_DECORATION
  {IR(16194, 19), 589}, // 687 RestrictPointerEXT in SPV_OPERAND_TYPE_DECORATION
  {IR(14972, 9), 523}, // 688 RowMajor in SPV_OPERAND_TYPE_DECORATION
  {IR(16338, 14), 596}, // 689 SIMTCallINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15113, 7), 535}, // 690 Sample in SPV_OPERAND_TYPE_DECORATION
  {IR(15242, 20), 546}, // 691 SaturatedConversion in SPV_OPERAND_TYPE_DECORATION
  {IR(16049, 28), 583}, // 692 SecondaryViewportRelativeNV in SPV_OPERAND_TYPE_DECORATION
  {IR(16391, 17), 599}, // 693 SideEffectsINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16818, 20), 618}, // 694 SimpleDualPortINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17307, 25), 640}, // 695 SingleElementVectorINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16767, 16), 615}, // 696 SinglepumpINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(14947, 7), 520}, // 697 SpecId in SPV_OPERAND_TYPE_DECORATION
  {IR(17790, 26), 655}, // 698 StableKernelArgumentINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16483, 15), 603}, // 699 StackCallINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17049, 17), 629}, // 700 StallEnableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(17385, 15), 643}, // 701 StallFreeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15262, 7), 547}, // 702 Stream in SPV_OPERAND_TYPE_DECORATION
  {IR(16925, 16), 622}, // 703 StridesizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15849, 23), 574}, // 704 TrackFinishWritingAMDX in SPV_OPERAND_TYPE_DECORATION
  {IR(16955, 18), 624}, // 705 TrueDualPortINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15198, 8), 544}, // 706 Uniform in SPV_OPERAND_TYPE_DECORATION
  {IR(15232, 10), 545}, // 707 UniformId in SPV_OPERAND_TYPE_DECORATION
  {IR(16562, 13), 606}, // 708 UserSemantic in SPV_OPERAND_TYPE_DECORATION
  {IR(16594, 15), 607}, // 709 UserTypeGOOGLE in SPV_OPERAND_TYPE_DECORATION
  {IR(17332, 35), 641}, // 710 VectorComputeCallableFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16456, 27), 602}, // 711 VectorComputeFunctionINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16408, 27), 600}, // 712 VectorComputeVariableINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(16030, 19), 582}, // 713 ViewportRelativeNV in SPV_OPERAND_TYPE_DECORATION
  {IR(15147, 9), 539}, // 714 Volatile in SPV_OPERAND_TYPE_DECORATION
  {IR(15717, 18), 568}, // 715 WeightTextureQCOM in SPV_OPERAND_TYPE_DECORATION
  {IR(16941, 14), 623}, // 716 WordsizeINTEL in SPV_OPERAND_TYPE_DECORATION
  {IR(15323, 10), 554}, // 717 XfbBuffer in SPV_OPERAND_TYPE_DECORATION
  {IR(15333, 10), 555}, // 718 XfbStride in SPV_OPERAND_TYPE_DECORATION
  {IR(18078, 3), 661}, // 719 1D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18081, 3), 662}, // 720 2D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18084, 3), 663}, // 721 3D in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18097, 7), 666}, // 722 Buffer in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18087, 5), 664}, // 723 Cube in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18092, 5), 665}, // 724 Rect in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18104, 12), 667}, // 725 SubpassData in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18116, 17), 668}, // 726 TileImageDataEXT in SPV_OPERAND_TYPE_DIMENSIONALITY
  {IR(18928, 15), 721}, // 727 CoalescingAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18559, 15), 699}, // 728 ContractionOff in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(9407, 18), 713}, // 729 DenormFlushToZero in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(9392, 15), 712}, // 730 DenormPreserve in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18329, 13), 682}, // 731 DepthGreater in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18342, 10), 683}, // 732 DepthLess in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18314, 15), 681}, // 733 DepthReplacing in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18352, 15), 684}, // 734 DepthUnchanged in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19349, 25), 739}, // 735 DerivativeGroupLinearKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19374, 24), 739}, // 736 DerivativeGroupLinearNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19302, 24), 738}, // 737 DerivativeGroupQuadsKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19326, 23), 738}, // 738 DerivativeGroupQuadsNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18876, 29), 719}, // 739 EarlyAndLateFragmentTestsAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18281, 19), 678}, // 740 EarlyFragmentTests in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19859, 18), 758}, // 741 FPFastMathDefault in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18586, 10), 701}, // 742 Finalizer in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19674, 26), 750}, // 743 FloatingPointModeALTINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19700, 27), 751}, // 744 FloatingPointModeIEEEINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18574, 12), 700}, // 745 Initializer in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18403, 11), 688}, // 746 InputLines in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18414, 20), 689}, // 747 InputLinesAdjacency in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18391, 12), 687}, // 748 InputPoints in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18444, 24), 691}, // 749 InputTrianglesAdjacency in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18133, 12), 669}, // 750 Invocations in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18943, 15), 722}, // 751 IsApiEntryAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18474, 9), 693}, // 752 Isolines in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18367, 10), 685}, // 753 LocalSize in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18377, 14), 686}, // 754 LocalSizeHint in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18654, 16), 706}, // 755 LocalSizeHintId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18642, 12), 705}, // 756 LocalSizeId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18958, 21), 723}, // 757 MaxNodeRecursionAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19003, 21), 726}, // 758 MaxNumWorkgroupsAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19749, 16), 753}, // 759 MaxWorkDimINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19727, 22), 752}, // 760 MaxWorkgroupSizeINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19835, 24), 757}, // 761 MaximallyReconvergesKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19950, 22), 762}, // 762 MaximumRegistersINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19972, 24), 763}, // 763 MaximumRegistersIdINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19927, 23), 761}, // 764 NamedBarrierCountINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20047, 27), 764}, // 765 NamedMaximumRegistersINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19765, 20), 754}, // 766 NoGlobalOffsetINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18670, 34), 707}, // 767 NonCoherentColorAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18704, 34), 708}, // 768 NonCoherentDepthAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18738, 36), 709}, // 769 NonCoherentStencilAttachmentReadEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18822, 34), 717}, // 770 NonCoherentTileAttachmentReadQCOM in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19785, 22), 755}, // 771 NumSIMDWorkitemsINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18265, 16), 677}, // 772 OriginLowerLeft in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18249, 16), 676}, // 773 OriginUpperLeft in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18511, 16), 696}, // 774 OutputLineStrip in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19234, 15), 736}, // 775 OutputLinesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19249, 14), 736}, // 776 OutputLinesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18498, 13), 695}, // 777 OutputPoints in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19263, 20), 737}, // 778 OutputPrimitivesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19283, 19), 737}, // 779 OutputPrimitivesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18527, 20), 697}, // 780 OutputTriangleStrip in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19398, 19), 740}, // 781 OutputTrianglesEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19417, 18), 740}, // 782 OutputTrianglesNV in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18483, 15), 694}, // 783 OutputVertices in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18230, 19), 675}, // 784 PixelCenterInteger in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19435, 25), 741}, // 785 PixelInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19460, 27), 742}, // 786 PixelInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18300, 10), 679}, // 787 PointMode in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18804, 18), 711}, // 788 PostDepthCoverage in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19175, 19), 733}, // 789 QuadDerivativesKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18468, 6), 692}, // 790 Quads in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19901, 26), 760}, // 791 RegisterMapInterfaceINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19194, 20), 734}, // 792 RequireFullQuadsKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(9450, 16), 715}, // 793 RoundingModeRTE in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19653, 21), 749}, // 794 RoundingModeRTNINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19632, 21), 748}, // 795 RoundingModeRTPINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(9466, 16), 716}, // 796 RoundingModeRTZ in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19487, 26), 743}, // 797 SampleInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19513, 28), 744}, // 798 SampleInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19807, 28), 756}, // 799 SchedulerTargetFmaxMhzINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(6153, 16), 725}, // 800 ShaderIndexAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19541, 31), 745}, // 801 ShadingRateInterlockOrderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19572, 33), 746}, // 802 ShadingRateInterlockUnorderedEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19605, 27), 747}, // 803 SharedLocalMemorySizeINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19214, 20), 735}, // 804 SharesInputWithAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(9425, 25), 714}, // 805 SignedZeroInfNanPreserve in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18145, 13), 670}, // 806 SpacingEqual in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18158, 22), 671}, // 807 SpacingFractionalEven in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18180, 21), 672}, // 808 SpacingFractionalOdd in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18979, 24), 724}, // 809 StaticNumWorkgroupsAMDX in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19128, 25), 731}, // 810 StencilRefGreaterBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19052, 26), 728}, // 811 StencilRefGreaterFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19153, 22), 732}, // 812 StencilRefLessBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19078, 23), 729}, // 813 StencilRefLessFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18905, 23), 720}, // 814 StencilRefReplacingEXT in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19101, 27), 730}, // 815 StencilRefUnchangedBackAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19024, 28), 727}, // 816 StencilRefUnchangedFrontAMD in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(19877, 24), 759}, // 817 StreamingInterfaceINTEL in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(5260, 13), 702}, // 818 SubgroupSize in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18774, 30), 710}, // 819 SubgroupUniformControlFlowKHR in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18596, 22), 703}, // 820 SubgroupsPerWorkgroup in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18618, 24), 704}, // 821 SubgroupsPerWorkgroupId in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18856, 20), 718}, // 822 TileShadingRateQCOM in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18434, 10), 690}, // 823 Triangles in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18547, 12), 698}, // 824 VecTypeHint in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18215, 15), 674}, // 825 VertexOrderCcw in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18201, 14), 673}, // 826 VertexOrderCw in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(18310, 4), 680}, // 827 Xfb in SPV_OPERAND_TYPE_EXECUTION_MODE
  {IR(20212, 10), 776}, // 828 AnyHitKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20222, 9), 776}, // 829 AnyHitNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20273, 12), 779}, // 830 CallableKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20285, 11), 779}, // 831 CallableNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20231, 14), 777}, // 832 ClosestHitKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20245, 13), 777}, // 833 ClosestHitNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(14313, 9), 769}, // 834 Fragment in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20124, 10), 770}, // 835 GLCompute in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(4741, 9), 768}, // 836 Geometry in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20181, 16), 775}, // 837 IntersectionKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20197, 15), 775}, // 838 IntersectionNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(4508, 7), 771}, // 839 Kernel in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20304, 8), 781}, // 840 MeshEXT in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20141, 7), 773}, // 841 MeshNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20258, 8), 778}, // 842 MissKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20266, 7), 778}, // 843 MissNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20148, 17), 774}, // 844 RayGenerationKHR in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20165, 16), 774}, // 845 RayGenerationNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20296, 8), 780}, // 846 TaskEXT in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20134, 7), 772}, // 847 TaskNV in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20081, 20), 766}, // 848 TessellationControl in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20101, 23), 767}, // 849 TessellationEvaluation in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20074, 7), 765}, // 850 Vertex in SPV_OPERAND_TYPE_EXECUTION_MODEL
  {IR(20321, 12), 783}, // 851 FlushToZero in SPV_OPERAND_TYPE_FPDENORM_MODE
  {IR(20312, 9), 782}, // 852 Preserve in SPV_OPERAND_TYPE_FPDENORM_MODE
  {IR(20333, 12), 784}, // 853 BFloat16KHR in SPV_OPERAND_TYPE_FPENCODING
  {IR(20350, 4), 786}, // 854 ALT in SPV_OPERAND_TYPE_FPOPERATION_MODE
  {IR(20345, 5), 785}, // 855 IEEE in SPV_OPERAND_TYPE_FPOPERATION_MODE
  {IR(20388, 14), 793}, // 856 AllowContract in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20402, 23), 793}, // 857 AllowContractFastINTEL in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20425, 13), 794}, // 858 AllowReassoc in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20438, 18), 794}, // 859 AllowReassocINTEL in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20372, 11), 791}, // 860 AllowRecip in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20456, 15), 795}, // 861 AllowTransform in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20383, 5), 792}, // 862 Fast in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20368, 4), 790}, // 863 NSZ in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(13909, 5), 787}, // 864 None in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20361, 7), 789}, // 865 NotInf in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20354, 7), 788}, // 866 NotNaN in SPV_OPERAND_TYPE_FP_FAST_MATH_MODE
  {IR(20471, 4), 796}, // 867 RTE in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(20483, 4), 799}, // 868 RTN in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(20479, 4), 798}, // 869 RTP in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(20475, 4), 797}, // 870 RTZ in SPV_OPERAND_TYPE_FP_ROUNDING_MODE
  {IR(20519, 18), 802}, // 871 Horizontal2Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(20537, 18), 803}, // 872 Horizontal4Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(20487, 16), 800}, // 873 Vertical2Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(20503, 16), 801}, // 874 Vertical4Pixels in SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE
  {IR(20578, 6), 808}, // 875 Const in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(20562, 11), 806}, // 876 DontInline in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(20555, 7), 805}, // 877 Inline in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(13909, 5), 804}, // 878 None in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(13150, 11), 809}, // 879 OptNoneEXT in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(13161, 13), 809}, // 880 OptNoneINTEL in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(20573, 5), 807}, // 881 Pure in SPV_OPERAND_TYPE_FUNCTION_CONTROL
  {IR(20594, 6), 812}, // 882 ByVal in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20605, 8), 814}, // 883 NoAlias in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20613, 10), 815}, // 884 NoCapture in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20631, 12), 817}, // 885 NoReadWrite in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20623, 8), 816}, // 886 NoWrite in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20643, 20), 818}, // 887 RuntimeAlignedINTEL in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20589, 5), 811}, // 888 Sext in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20600, 5), 813}, // 889 Sret in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20584, 5), 810}, // 890 Zext in SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE
  {IR(20698, 16), 822}, // 891 ClusteredReduce in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(20684, 14), 821}, // 892 ExclusiveScan in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(20670, 14), 820}, // 893 InclusiveScan in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(20761, 27), 825}, // 894 PartitionedExclusiveScanNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(20734, 27), 824}, // 895 PartitionedInclusiveScanNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(20714, 20), 823}, // 896 PartitionedReduceNV in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(20663, 7), 819}, // 897 Reduce in SPV_OPERAND_TYPE_GROUP_OPERATION
  {IR(20788, 10), 826}, // 898 NoneINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(20798, 10), 827}, // 899 ReadINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(20819, 15), 829}, // 900 ReadWriteINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(20808, 11), 828}, // 901 WriteINTEL in SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER
  {IR(20834, 5), 831}, // 902 Bias in SPV_OPERAND_TYPE_IMAGE
  {IR(20848, 12), 834}, // 903 ConstOffset in SPV_OPERAND_TYPE_IMAGE
  {IR(20860, 13), 836}, // 904 ConstOffsets in SPV_OPERAND_TYPE_IMAGE
  {IR(20843, 5), 833}, // 905 Grad in SPV_OPERAND_TYPE_IMAGE
  {IR(20839, 4), 832}, // 906 Lod in SPV_OPERAND_TYPE_IMAGE
  {IR(20873, 19), 839}, // 907 MakeTexelAvailable in SPV_OPERAND_TYPE_IMAGE
  {IR(20892, 22), 839}, // 908 MakeTexelAvailableKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(20914, 17), 840}, // 909 MakeTexelVisible in SPV_OPERAND_TYPE_IMAGE
  {IR(20931, 20), 840}, // 910 MakeTexelVisibleKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(8292, 7), 838}, // 911 MinLod in SPV_OPERAND_TYPE_IMAGE
  {IR(20951, 16), 841}, // 912 NonPrivateTexel in SPV_OPERAND_TYPE_IMAGE
  {IR(20967, 19), 841}, // 913 NonPrivateTexelKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(13909, 5), 830}, // 914 None in SPV_OPERAND_TYPE_IMAGE
  {IR(21039, 12), 845}, // 915 Nontemporal in SPV_OPERAND_TYPE_IMAGE
  {IR(15316, 7), 835}, // 916 Offset in SPV_OPERAND_TYPE_IMAGE
  {IR(21051, 8), 846}, // 917 Offsets in SPV_OPERAND_TYPE_IMAGE
  {IR(15113, 7), 837}, // 918 Sample in SPV_OPERAND_TYPE_IMAGE
  {IR(21017, 11), 843}, // 919 SignExtend in SPV_OPERAND_TYPE_IMAGE
  {IR(20986, 14), 842}, // 920 VolatileTexel in SPV_OPERAND_TYPE_IMAGE
  {IR(21000, 17), 842}, // 921 VolatileTexelKHR in SPV_OPERAND_TYPE_IMAGE
  {IR(21028, 11), 844}, // 922 ZeroExtend in SPV_OPERAND_TYPE_IMAGE
  {IR(13806, 6), 861}, // 923 Float in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21220, 10), 860}, // 924 HalfFloat in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21155, 12), 855}, // 925 SignedInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21167, 12), 856}, // 926 SignedInt32 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21144, 11), 854}, // 927 SignedInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21069, 11), 848}, // 928 SnormInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21059, 10), 847}, // 929 SnormInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21129, 15), 853}, // 930 UnormInt101010 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21241, 17), 863}, // 931 UnormInt101010_2 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21258, 16), 864}, // 932 UnormInt10X6EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21391, 16), 871}, // 933 UnormInt12X4EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21407, 16), 872}, // 934 UnormInt14X2EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21090, 11), 850}, // 935 UnormInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21230, 11), 862}, // 936 UnormInt24 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21314, 20), 867}, // 937 UnormInt2_101010EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21080, 10), 849}, // 938 UnormInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21115, 14), 852}, // 939 UnormShort555 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21101, 14), 851}, // 940 UnormShort565 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21334, 19), 868}, // 941 UnsignedInt10X6EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21353, 19), 869}, // 942 UnsignedInt12X4EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21372, 19), 870}, // 943 UnsignedInt14X2EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21192, 14), 858}, // 944 UnsignedInt16 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21206, 14), 859}, // 945 UnsignedInt32 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21179, 13), 857}, // 946 UnsignedInt8 in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21274, 20), 865}, // 947 UnsignedIntRaw10EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21294, 20), 866}, // 948 UnsignedIntRaw12EXT in SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE
  {IR(21425, 2), 874}, // 949 A in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21526, 5), 892}, // 950 ABGR in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21447, 5), 880}, // 951 ARGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21442, 5), 879}, // 952 BGRA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21484, 6), 886}, // 953 Depth in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21490, 13), 887}, // 954 DepthStencil in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21452, 10), 881}, // 955 Intensity in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21462, 10), 882}, // 956 Luminance in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21423, 2), 873}, // 957 R in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21430, 3), 876}, // 958 RA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21427, 3), 875}, // 959 RG in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21433, 4), 877}, // 960 RGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21437, 5), 878}, // 961 RGBA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21479, 5), 885}, // 962 RGBx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21475, 4), 884}, // 963 RGx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21472, 3), 883}, // 964 Rx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21520, 6), 891}, // 965 sBGRA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21503, 5), 888}, // 966 sRGB in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21514, 6), 890}, // 967 sRGBA in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21508, 6), 889}, // 968 sRGBx in SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER
  {IR(21531, 27), 893}, // 969 InitOnDeviceReprogramINTEL in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(21558, 23), 894}, // 970 InitOnDeviceResetINTEL in SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER
  {IR(21581, 7), 895}, // 971 NoWait in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(21588, 11), 896}, // 972 WaitKernel in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(21599, 14), 897}, // 973 WaitWorkGroup in SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS
  {IR(21613, 12), 899}, // 974 CmdExecTime in SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {IR(13909, 5), 898}, // 975 None in SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO
  {IR(21625, 13), 901}, // 976 MayUsePrintf in SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {IR(13909, 5), 900}, // 977 None in SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS
  {IR(21638, 7), 902}, // 978 Export in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(21645, 7), 903}, // 979 Import in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(21652, 12), 904}, // 980 LinkOnceODR in SPV_OPERAND_TYPE_LINKAGE_TYPE
  {IR(21678, 12), 906}, // 981 CachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(21730, 17), 909}, // 982 ConstCachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(21705, 25), 908}, // 983 InvalidateAfterReadINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(21690, 15), 907}, // 984 StreamingINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(21664, 14), 905}, // 985 UncachedINTEL in SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL
  {IR(21870, 21), 922}, // 986 DependencyArrayINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21765, 19), 913}, // 987 DependencyInfinite in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21784, 17), 914}, // 988 DependencyLength in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21754, 11), 912}, // 989 DontUnroll in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(17139, 24), 920}, // 990 InitiationIntervalINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21829, 18), 917}, // 991 IterationMultiple in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21891, 18), 924}, // 992 LoopCoalesceINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21970, 15), 928}, // 993 LoopCountINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(17163, 20), 921}, // 994 MaxConcurrencyINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21909, 21), 925}, // 995 MaxInterleavingINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21815, 14), 916}, // 996 MaxIterations in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21985, 26), 929}, // 997 MaxReinvocationDelayINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21801, 14), 915}, // 998 MinIterations in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21956, 14), 927}, // 999 NoFusionINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(13909, 5), 910}, // 1000 None in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21857, 13), 919}, // 1001 PartialCount in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21847, 10), 918}, // 1002 PeelCount in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(17183, 20), 923}, // 1003 PipelineEnableINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21930, 26), 926}, // 1004 SpeculatedIterationsINTEL in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(21747, 7), 911}, // 1005 Unroll in SPV_OPERAND_TYPE_LOOP_CONTROL
  {IR(22294, 27), 943}, // 1006 MatrixAPackedBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22242, 26), 941}, // 1007 MatrixAPackedFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22162, 23), 937}, // 1008 MatrixAPackedInt4INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22116, 23), 935}, // 1009 MatrixAPackedInt8INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22011, 29), 931}, // 1010 MatrixASignedComponentsINTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22208, 17), 939}, // 1011 MatrixATF32INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22321, 27), 944}, // 1012 MatrixBPackedBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22268, 26), 942}, // 1013 MatrixBPackedFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22185, 23), 938}, // 1014 MatrixBPackedInt4INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22139, 23), 936}, // 1015 MatrixBPackedInt8INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22040, 29), 932}, // 1016 MatrixBSignedComponentsINTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22225, 17), 940}, // 1017 MatrixBTF32INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22069, 21), 933}, // 1018 MatrixCBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22090, 26), 934}, // 1019 MatrixResultBFloat16INTEL in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(13909, 5), 930}, // 1020 None in SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS
  {IR(22481, 20), 952}, // 1021 AliasScopeINTELMask in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22348, 8), 947}, // 1022 Aligned in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22356, 21), 949}, // 1023 MakePointerAvailable in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22377, 24), 949}, // 1024 MakePointerAvailableKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22401, 19), 950}, // 1025 MakePointerVisible in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22420, 22), 950}, // 1026 MakePointerVisibleKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22501, 17), 953}, // 1027 NoAliasINTELMask in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22442, 18), 951}, // 1028 NonPrivatePointer in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22460, 21), 951}, // 1029 NonPrivatePointerKHR in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(13909, 5), 945}, // 1030 None in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(21039, 12), 948}, // 1031 Nontemporal in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(15147, 9), 946}, // 1032 Volatile in SPV_OPERAND_TYPE_MEMORY_ACCESS
  {IR(22525, 8), 955}, // 1033 GLSL450 in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(22533, 7), 956}, // 1034 OpenCL in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(22518, 7), 954}, // 1035 Simple in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(22540, 7), 957}, // 1036 Vulkan in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(22547, 10), 957}, // 1037 VulkanKHR in SPV_OPERAND_TYPE_MEMORY_MODEL
  {IR(22565, 8), 959}, // 1038 Acquire in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22581, 15), 961}, // 1039 AcquireRelease in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22685, 20), 967}, // 1040 AtomicCounterMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22664, 21), 966}, // 1041 CrossWorkgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22705, 12), 968}, // 1042 ImageMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22746, 14), 970}, // 1043 MakeAvailable in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22760, 17), 970}, // 1044 MakeAvailableKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22777, 12), 971}, // 1045 MakeVisible in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22789, 15), 971}, // 1046 MakeVisibleKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(13909, 5), 958}, // 1047 None in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22717, 13), 969}, // 1048 OutputMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22730, 16), 969}, // 1049 OutputMemoryKHR in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22557, 8), 958}, // 1050 Relaxed in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22573, 8), 960}, // 1051 Release in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22596, 23), 962}, // 1052 SequentiallyConsistent in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22633, 15), 964}, // 1053 SubgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22619, 14), 963}, // 1054 UniformMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(15147, 9), 972}, // 1055 Volatile in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22648, 16), 965}, // 1056 WorkgroupMemory in SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID
  {IR(22804, 10), 973}, // 1057 AutoINTEL in SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS
  {IR(22819, 4), 975}, // 1058 SAT in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(22832, 8), 977}, // 1059 SAT_SYM in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(22823, 9), 976}, // 1060 SAT_ZERO in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(22814, 5), 974}, // 1061 WRAP in SPV_OPERAND_TYPE_OVERFLOW_MODES
  {IR(22840, 25), 978}, // 1062 PackedVectorFormat4x8Bit in SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {IR(22865, 28), 978}, // 1063 PackedVectorFormat4x8BitKHR in SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT
  {IR(22906, 4), 981}, // 1064 RND in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(22939, 9), 985}, // 1065 RND_CONV in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(22948, 13), 986}, // 1066 RND_CONV_ODD in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(22919, 8), 983}, // 1067 RND_INF in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(22927, 12), 984}, // 1068 RND_MIN_INF in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(22910, 9), 982}, // 1069 RND_ZERO in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(22893, 4), 979}, // 1070 TRN in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(22897, 9), 980}, // 1071 TRN_ZERO in SPV_OPERAND_TYPE_QUANTIZATION_MODES
  {IR(13909, 5), 987}, // 1072 None in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(22961, 25), 988}, // 1073 RobustnessPerComponentNV in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(22986, 23), 989}, // 1074 RobustnessPerElementNV in SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS
  {IR(23078, 27), 995}, // 1075 CullBackFacingTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23105, 28), 996}, // 1076 CullFrontFacingTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23147, 16), 998}, // 1077 CullNoOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23133, 14), 997}, // 1078 CullOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23217, 30), 1001}, // 1079 ForceOpacityMicromap2StateEXT in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23019, 12), 992}, // 1080 NoOpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(14661, 8), 990}, // 1081 NoneKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23009, 10), 991}, // 1082 OpaqueKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23204, 13), 1000}, // 1083 SkipAABBsKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23180, 24), 999}, // 1084 SkipBuiltinPrimitivesNV in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23054, 24), 994}, // 1085 SkipClosestHitShaderKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23163, 17), 999}, // 1086 SkipTrianglesKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23031, 23), 993}, // 1087 TerminateOnFirstHitKHR in SPV_OPERAND_TYPE_RAY_FLAGS
  {IR(23288, 37), 1003}, // 1088 RayQueryCandidateIntersectionAABBKHR in SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {IR(23247, 41), 1002}, // 1089 RayQueryCandidateIntersectionTriangleKHR in SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE
  {IR(23403, 42), 1006}, // 1090 RayQueryCommittedIntersectionGeneratedKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(23325, 37), 1004}, // 1091 RayQueryCommittedIntersectionNoneKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(23362, 41), 1005}, // 1092 RayQueryCommittedIntersectionTriangleKHR in SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE
  {IR(23445, 33), 1007}, // 1093 RayQueryCandidateIntersectionKHR in SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {IR(23478, 33), 1008}, // 1094 RayQueryCommittedIntersectionKHR in SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION
  {IR(23523, 6), 1011}, // 1095 Clamp in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(23511, 12), 1010}, // 1096 ClampToEdge in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(13909, 5), 1009}, // 1097 None in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(23529, 7), 1012}, // 1098 Repeat in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(23536, 15), 1013}, // 1099 RepeatMirrored in SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE
  {IR(23559, 7), 1015}, // 1100 Linear in SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {IR(23551, 8), 1014}, // 1101 Nearest in SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE
  {IR(23624, 13), 1024}, // 1102 R11fG11fB10f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23666, 4), 1030}, // 1103 R16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23704, 9), 1035}, // 1104 R16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23637, 5), 1025}, // 1105 R16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23766, 5), 1044}, // 1106 R16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23837, 6), 1054}, // 1107 R16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23590, 5), 1019}, // 1108 R32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23744, 5), 1040}, // 1109 R32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23801, 6), 1049}, // 1110 R32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23854, 5), 1057}, // 1111 R64i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23848, 6), 1056}, // 1112 R64ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23670, 3), 1031}, // 1113 R8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23713, 8), 1036}, // 1114 R8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23771, 4), 1045}, // 1115 R8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23843, 5), 1055}, // 1116 R8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23657, 5), 1028}, // 1117 Rg16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23685, 10), 1033}, // 1118 Rg16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23618, 6), 1023}, // 1119 Rg16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23755, 6), 1042}, // 1120 Rg16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23824, 7), 1052}, // 1121 Rg16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23612, 6), 1022}, // 1122 Rg32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23749, 6), 1041}, // 1123 Rg32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23817, 7), 1051}, // 1124 Rg32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23662, 4), 1029}, // 1125 Rg8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23695, 9), 1034}, // 1126 Rg8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23761, 5), 1043}, // 1127 Rg8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23831, 6), 1053}, // 1128 Rg8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23649, 8), 1027}, // 1129 Rgb10A2 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23807, 10), 1050}, // 1130 Rgb10a2ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23642, 7), 1026}, // 1131 Rgba16 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23673, 12), 1032}, // 1132 Rgba16Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23582, 8), 1018}, // 1133 Rgba16f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23729, 8), 1038}, // 1134 Rgba16i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23784, 9), 1047}, // 1135 Rgba16ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23574, 8), 1017}, // 1136 Rgba32f in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23721, 8), 1037}, // 1137 Rgba32i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23775, 9), 1046}, // 1138 Rgba32ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23595, 6), 1020}, // 1139 Rgba8 in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23601, 11), 1021}, // 1140 Rgba8Snorm in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23737, 7), 1039}, // 1141 Rgba8i in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23793, 8), 1048}, // 1142 Rgba8ui in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23566, 8), 1016}, // 1143 Unknown in SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT
  {IR(23859, 12), 1058}, // 1144 CrossDevice in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(23871, 7), 1059}, // 1145 Device in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(23897, 11), 1062}, // 1146 Invocation in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(23908, 12), 1063}, // 1147 QueueFamily in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(23920, 15), 1063}, // 1148 QueueFamilyKHR in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(23935, 14), 1064}, // 1149 ShaderCallKHR in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(23888, 9), 1061}, // 1150 Subgroup in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(23878, 10), 1060}, // 1151 Workgroup in SPV_OPERAND_TYPE_SCOPE_ID
  {IR(23957, 12), 1067}, // 1152 DontFlatten in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(23949, 8), 1066}, // 1153 Flatten in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(13909, 5), 1065}, // 1154 None in SPV_OPERAND_TYPE_SELECTION_CONTROL
  {IR(23969, 29), 1068}, // 1155 IdentifierPossibleDuplicates in SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS
  {IR(13790, 8), 1070}, // 1156 Address in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13798, 8), 1071}, // 1157 Boolean in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13806, 6), 1072}, // 1158 Float in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13812, 7), 1073}, // 1159 Signed in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13819, 11), 1074}, // 1160 SignedChar in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13830, 9), 1075}, // 1161 Unsigned in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13839, 13), 1076}, // 1162 UnsignedChar in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13778, 12), 1069}, // 1163 Unspecified in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING
  {IR(13852, 6), 1077}, // 1164 Class in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(13858, 10), 1078}, // 1165 Structure in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(13868, 6), 1079}, // 1166 Union in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE
  {IR(13889, 20), 1081}, // 1167 ImportedDeclaration in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(13874, 15), 1080}, // 1168 ImportedModule in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY
  {IR(13998, 15), 1089}, // 1169 FlagArtificial in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14013, 13), 1090}, // 1170 FlagExplicit in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(13986, 12), 1088}, // 1171 FlagFwdDecl in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14076, 21), 1094}, // 1172 FlagIndirectVariable in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(13969, 17), 1087}, // 1173 FlagIsDefinition in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14153, 16), 1098}, // 1174 FlagIsEnumClass in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(13957, 12), 1086}, // 1175 FlagIsLocal in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14137, 16), 1097}, // 1176 FlagIsOptimized in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(13930, 14), 1084}, // 1177 FlagIsPrivate in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(13914, 16), 1083}, // 1178 FlagIsProtected in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(13944, 13), 1085}, // 1179 FlagIsPublic in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14097, 20), 1095}, // 1180 FlagLValueReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14041, 18), 1092}, // 1181 FlagObjectPointer in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14026, 15), 1091}, // 1182 FlagPrototyped in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14117, 20), 1096}, // 1183 FlagRValueReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14059, 17), 1093}, // 1184 FlagStaticMember in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14189, 24), 1100}, // 1185 FlagTypePassByReference in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14169, 20), 1099}, // 1186 FlagTypePassByValue in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(23998, 26), 1101}, // 1187 FlagUnknownPhysicalLayout in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(13909, 5), 1082}, // 1188 None in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS
  {IR(14274, 9), 1106}, // 1189 BitPiece in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14306, 7), 1110}, // 1190 Constu in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14213, 6), 1102}, // 1191 Deref in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14313, 9), 1111}, // 1192 Fragment in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14224, 6), 1104}, // 1193 Minus in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14219, 5), 1103}, // 1194 Plus in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14263, 11), 1105}, // 1195 PlusUconst in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14295, 11), 1109}, // 1196 StackValue in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14283, 5), 1107}, // 1197 Swap in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14288, 7), 1108}, // 1198 Xderef in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION
  {IR(14358, 11), 1115}, // 1199 AtomicType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14322, 10), 1112}, // 1200 ConstType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14345, 13), 1114}, // 1201 RestrictType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(14332, 13), 1113}, // 1202 VolatileType in SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER
  {IR(24059, 15), 1122}, // 1203 CPP_for_OpenCL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24024, 5), 1117}, // 1204 ESSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24029, 5), 1118}, // 1205 GLSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24079, 7), 1124}, // 1206 HERO_C in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24054, 5), 1121}, // 1207 HLSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24086, 5), 1125}, // 1208 NZSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24034, 9), 1119}, // 1209 OpenCL_C in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24043, 11), 1120}, // 1210 OpenCL_CPP in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24106, 5), 1129}, // 1211 Rust in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24074, 5), 1123}, // 1212 SYCL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24096, 6), 1127}, // 1213 Slang in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(23566, 8), 1116}, // 1214 Unknown in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24091, 5), 1126}, // 1215 WGSL in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24102, 4), 1128}, // 1216 Zig in SPV_OPERAND_TYPE_SOURCE_LANGUAGE
  {IR(24193, 14), 1140}, // 1217 AtomicCounter in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24275, 16), 1146}, // 1218 CallableDataKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24291, 15), 1146}, // 1219 CallableDataNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24589, 17), 1155}, // 1220 CodeSectionINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24140, 15), 1135}, // 1221 CrossWorkgroup in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24606, 16), 1156}, // 1222 DeviceOnlyINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24163, 9), 1137}, // 1223 Function in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24172, 8), 1138}, // 1224 Generic in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24380, 16), 1149}, // 1225 HitAttributeKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24396, 15), 1149}, // 1226 HitAttributeNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24544, 21), 1153}, // 1227 HitObjectAttributeNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24622, 14), 1157}, // 1228 HostOnlyINTEL in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24207, 6), 1141}, // 1229 Image in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24306, 24), 1147}, // 1230 IncomingCallableDataKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24330, 23), 1147}, // 1231 IncomingCallableDataNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24411, 22), 1150}, // 1232 IncomingRayPayloadKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24433, 21), 1150}, // 1233 IncomingRayPayloadNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24127, 6), 1131}, // 1234 Input in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24259, 16), 1145}, // 1235 NodePayloadAMDX in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24133, 7), 1133}, // 1236 Output in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24497, 22), 1152}, // 1237 PhysicalStorageBuffer in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24519, 25), 1152}, // 1238 PhysicalStorageBufferEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24155, 8), 1136}, // 1239 Private in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24180, 13), 1139}, // 1240 PushConstant in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24353, 14), 1148}, // 1241 RayPayloadKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24367, 13), 1148}, // 1242 RayPayloadNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24454, 22), 1151}, // 1243 ShaderRecordBufferKHR in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24476, 21), 1151}, // 1244 ShaderRecordBufferNV in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24213, 14), 1142}, // 1245 StorageBuffer in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24565, 24), 1154}, // 1246 TaskPayloadWorkgroupEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24240, 19), 1144}, // 1247 TileAttachmentQCOM in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24227, 13), 1143}, // 1248 TileImageEXT in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(15198, 8), 1132}, // 1249 Uniform in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(24111, 16), 1130}, // 1250 UniformConstant in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(23878, 10), 1134}, // 1251 Workgroup in SPV_OPERAND_TYPE_STORAGE_CLASS
  {IR(21690, 15), 1161}, // 1252 StreamingINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(21664, 14), 1158}, // 1253 UncachedINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(24654, 15), 1160}, // 1254 WriteBackINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(24636, 18), 1159}, // 1255 WriteThroughINTEL in SPV_OPERAND_TYPE_STORE_CACHE_CONTROL
  {IR(24680, 11), 1164}, // 1256 DecodeFunc in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(13909, 5), 1162}, // 1257 None in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(24669, 11), 1163}, // 1258 TensorView in SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS
  {IR(23511, 12), 1167}, // 1259 ClampToEdge in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(15156, 9), 1166}, // 1260 Constant in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(23529, 7), 1168}, // 1261 Repeat in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(23536, 15), 1169}, // 1262 RepeatMirrored in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(24691, 10), 1165}, // 1263 Undefined in SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE
  {IR(24744, 24), 1173}, // 1264 MakeElementAvailableARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(24768, 22), 1174}, // 1265 MakeElementVisibleARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(24790, 21), 1175}, // 1266 NonPrivateElementARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(24701, 8), 1170}, // 1267 NoneARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(24709, 15), 1171}, // 1268 NontemporalARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
  {IR(24724, 20), 1172}, // 1269 OutOfBoundsValueARM in SPV_OPERAND_TYPE_TENSOR_OPERANDS
}};

IndexRange OperandNameRangeForKind(spv_operand_type_t type) {
  switch(type) {
    case SPV_OPERAND_TYPE_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_ADDRESSING_MODEL: return IR(3, 5);
    case SPV_OPERAND_TYPE_BUILT_IN: return IR(8, 148);
    case SPV_OPERAND_TYPE_CAPABILITY: return IR(156, 294);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(450, 8);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(458, 3);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(461, 2);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS: return IR(463, 19);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION: return IR(482, 10);
    case SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(492, 4);
    case SPV_OPERAND_TYPE_COMPONENT_TYPE: return IR(496, 15);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_LAYOUT: return IR(511, 4);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_OPERANDS: return IR(515, 6);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE: return IR(521, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_USE: return IR(524, 3);
    case SPV_OPERAND_TYPE_COOPERATIVE_VECTOR_MATRIX_LAYOUT: return IR(527, 4);
    case SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(531, 8);
    case SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE: return IR(539, 3);
    case SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS: return IR(542, 16);
    case SPV_OPERAND_TYPE_DEBUG_OPERATION: return IR(558, 9);
    case SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER: return IR(567, 3);
    case SPV_OPERAND_TYPE_DECORATION: return IR(570, 149);
    case SPV_OPERAND_TYPE_DIMENSIONALITY: return IR(719, 8);
    case SPV_OPERAND_TYPE_EXECUTION_MODE: return IR(727, 101);
    case SPV_OPERAND_TYPE_EXECUTION_MODEL: return IR(828, 23);
    case SPV_OPERAND_TYPE_FPDENORM_MODE: return IR(851, 2);
    case SPV_OPERAND_TYPE_FPENCODING: return IR(853, 1);
    case SPV_OPERAND_TYPE_FPOPERATION_MODE: return IR(854, 2);
    case SPV_OPERAND_TYPE_FP_FAST_MATH_MODE: return IR(856, 11);
    case SPV_OPERAND_TYPE_FP_ROUNDING_MODE: return IR(867, 4);
    case SPV_OPERAND_TYPE_FRAGMENT_SHADING_RATE: return IR(871, 4);
    case SPV_OPERAND_TYPE_FUNCTION_CONTROL: return IR(875, 7);
    case SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE: return IR(882, 9);
    case SPV_OPERAND_TYPE_GROUP_OPERATION: return IR(891, 7);
    case SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER: return IR(898, 4);
    case SPV_OPERAND_TYPE_IMAGE: return IR(902, 21);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE: return IR(923, 26);
    case SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER: return IR(949, 20);
    case SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER: return IR(969, 2);
    case SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS: return IR(971, 3);
    case SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO: return IR(974, 2);
    case SPV_OPERAND_TYPE_KERNEL_PROPERTY_FLAGS: return IR(976, 2);
    case SPV_OPERAND_TYPE_LINKAGE_TYPE: return IR(978, 3);
    case SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL: return IR(981, 5);
    case SPV_OPERAND_TYPE_LOOP_CONTROL: return IR(986, 20);
    case SPV_OPERAND_TYPE_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(1006, 15);
    case SPV_OPERAND_TYPE_MEMORY_ACCESS: return IR(1021, 12);
    case SPV_OPERAND_TYPE_MEMORY_MODEL: return IR(1033, 5);
    case SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID: return IR(1038, 19);
    case SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS: return IR(1057, 1);
    case SPV_OPERAND_TYPE_OVERFLOW_MODES: return IR(1058, 4);
    case SPV_OPERAND_TYPE_PACKED_VECTOR_FORMAT: return IR(1062, 2);
    case SPV_OPERAND_TYPE_QUANTIZATION_MODES: return IR(1064, 8);
    case SPV_OPERAND_TYPE_RAW_ACCESS_CHAIN_OPERANDS: return IR(1072, 3);
    case SPV_OPERAND_TYPE_RAY_FLAGS: return IR(1075, 13);
    case SPV_OPERAND_TYPE_RAY_QUERY_CANDIDATE_INTERSECTION_TYPE: return IR(1088, 2);
    case SPV_OPERAND_TYPE_RAY_QUERY_COMMITTED_INTERSECTION_TYPE: return IR(1090, 3);
    case SPV_OPERAND_TYPE_RAY_QUERY_INTERSECTION: return IR(1093, 2);
    case SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE: return IR(1095, 5);
    case SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE: return IR(1100, 2);
    case SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT: return IR(1102, 42);
    case SPV_OPERAND_TYPE_SCOPE_ID: return IR(1144, 8);
    case SPV_OPERAND_TYPE_SELECTION_CONTROL: return IR(1152, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_BUILD_IDENTIFIER_FLAGS: return IR(1155, 1);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING: return IR(1156, 8);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_COMPOSITE_TYPE: return IR(1164, 3);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_IMPORTED_ENTITY: return IR(1167, 2);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_INFO_FLAGS: return IR(1169, 20);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_OPERATION: return IR(1189, 10);
    case SPV_OPERAND_TYPE_SHDEBUG100_DEBUG_TYPE_QUALIFIER: return IR(1199, 4);
    case SPV_OPERAND_TYPE_SOURCE_LANGUAGE: return IR(1203, 14);
    case SPV_OPERAND_TYPE_STORAGE_CLASS: return IR(1217, 35);
    case SPV_OPERAND_TYPE_STORE_CACHE_CONTROL: return IR(1252, 4);
    case SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS: return IR(1256, 3);
    case SPV_OPERAND_TYPE_TENSOR_CLAMP_MODE: return IR(1259, 5);
    case SPV_OPERAND_TYPE_TENSOR_OPERANDS: return IR(1264, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_IMAGE: return IR(902, 21);
    case SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER: return IR(0, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS: return IR(1021, 12);
    case SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT: return IR(1062, 2);
    case SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS: return IR(515, 6);
    case SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS: return IR(1006, 15);
    case SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS: return IR(1072, 3);
    case SPV_OPERAND_TYPE_OPTIONAL_FPENCODING: return IR(853, 1);
    case SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS: return IR(1264, 6);
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
static const std::array<InstructionDesc, 798> kInstructionDesc{{
  {spv::Op::OpNop, false, false, IR(0, 0), IR(24811, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpUndef, true, true, IR(39, 2), IR(24867, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpSourceContinued, false, false, IR(11, 1), IR(24873, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpSource, false, false, IR(41, 4), IR(24992, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpSourceExtension, false, false, IR(11, 1), IR(24999, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpName, false, false, IR(45, 2), IR(25015, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpMemberName, false, false, IR(47, 3), IR(25020, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpString, true, false, IR(50, 2), IR(25031, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpLine, false, false, IR(52, 3), IR(25038, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpExtension, false, false, IR(11, 1), IR(25043, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpExtInstImport, true, false, IR(50, 2), IR(25053, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpExtInst, true, true, IR(55, 4), IR(25113, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpMemoryModel, false, false, IR(59, 2), IR(25185, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpEntryPoint, false, false, IR(61, 4), IR(25259, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpExecutionMode, false, false, IR(65, 2), IR(25302, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpCapability, false, false, IR(67, 1), IR(25344, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpTypeVoid, true, false, IR(68, 1), IR(25355, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeBool, true, false, IR(68, 1), IR(25364, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeInt, true, false, IR(69, 3), IR(25373, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeFloat, true, false, IR(72, 3), IR(25418, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeVector, true, false, IR(75, 3), IR(25428, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeMatrix, true, false, IR(75, 3), IR(25439, 11), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeImage, true, false, IR(78, 9), IR(25563, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeSampler, true, false, IR(68, 1), IR(25573, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeSampledImage, true, false, IR(87, 2), IR(25585, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeArray, true, false, IR(89, 3), IR(25602, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeRuntimeArray, true, false, IR(87, 2), IR(25612, 17), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeStruct, true, false, IR(92, 2), IR(25629, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeOpaque, true, false, IR(50, 2), IR(25640, 11), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypePointer, true, false, IR(94, 3), IR(25682, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeFunction, true, false, IR(97, 3), IR(25694, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeEvent, true, false, IR(68, 1), IR(25707, 10), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeDeviceEvent, true, false, IR(68, 1), IR(25717, 16), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeReserveId, true, false, IR(68, 1), IR(25733, 14), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeQueue, true, false, IR(68, 1), IR(25747, 10), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypePipe, true, false, IR(100, 2), IR(25757, 9), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeForwardPointer, false, false, IR(102, 2), IR(25766, 19), IR(0, 0), IR(198, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantTrue, true, true, IR(39, 2), IR(25785, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantFalse, true, true, IR(39, 2), IR(25798, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstant, true, true, IR(104, 3), IR(15156, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantComposite, true, true, IR(107, 3), IR(25850, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantSampler, true, true, IR(110, 5), IR(25946, 16), IR(0, 0), IR(200, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpConstantNull, true, true, IR(39, 2), IR(25962, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantTrue, true, true, IR(39, 2), IR(25975, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantFalse, true, true, IR(39, 2), IR(25992, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstant, true, true, IR(104, 3), IR(26010, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantComposite, true, true, IR(107, 3), IR(26023, 22), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantOp, true, true, IR(115, 3), IR(26086, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpFunction, true, true, IR(118, 4), IR(24163, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionParameter, true, true, IR(39, 2), IR(26135, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionEnd, false, false, IR(0, 0), IR(26153, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpFunctionCall, true, true, IR(122, 4), IR(26165, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpVariable, true, true, IR(126, 4), IR(26178, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpImageTexelPointer, true, true, IR(130, 5), IR(26187, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpLoad, true, true, IR(135, 4), IR(26245, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpStore, false, false, IR(139, 3), IR(26250, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCopyMemory, false, false, IR(142, 4), IR(26256, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCopyMemorySized, false, false, IR(146, 5), IR(26267, 16), IR(0, 0), IR(201, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpAccessChain, true, true, IR(122, 4), IR(26283, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpInBoundsAccessChain, true, true, IR(122, 4), IR(26295, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrAccessChain, true, true, IR(151, 5), IR(26315, 15), IR(0, 0), IR(203, 4), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpArrayLength, true, true, IR(156, 4), IR(26330, 12), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpGenericPtrMemSemantics, true, true, IR(160, 3), IR(26342, 23), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpInBoundsPtrAccessChain, true, true, IR(151, 5), IR(26365, 23), IR(0, 0), IR(1, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpDecorate, false, false, IR(163, 2), IR(26416, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpMemberDecorate, false, false, IR(165, 3), IR(26425, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpDecorationGroup, true, false, IR(68, 1), IR(26440, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupDecorate, false, false, IR(168, 2), IR(26456, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupMemberDecorate, false, false, IR(170, 2), IR(26515, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpVectorExtractDynamic, true, true, IR(172, 4), IR(26535, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpVectorInsertDynamic, true, true, IR(130, 5), IR(26556, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpVectorShuffle, true, true, IR(176, 5), IR(26576, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeConstruct, true, true, IR(107, 3), IR(26590, 19), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeExtract, true, true, IR(181, 4), IR(26609, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCompositeInsert, true, true, IR(176, 5), IR(26626, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpCopyObject, true, true, IR(160, 3), IR(26642, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpTranspose, true, true, IR(160, 3), IR(26653, 10), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpSampledImage, true, true, IR(172, 4), IR(26663, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleImplicitLod, true, true, IR(185, 5), IR(26708, 23), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleExplicitLod, true, true, IR(190, 5), IR(26754, 23), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleDrefImplicitLod, true, true, IR(195, 6), IR(26777, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleDrefExplicitLod, true, true, IR(201, 6), IR(26804, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjImplicitLod, true, true, IR(185, 5), IR(26831, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjExplicitLod, true, true, IR(190, 5), IR(26858, 27), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjDrefImplicitLod, true, true, IR(195, 6), IR(26885, 31), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSampleProjDrefExplicitLod, true, true, IR(201, 6), IR(26916, 31), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageFetch, true, true, IR(185, 5), IR(26947, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageGather, true, true, IR(195, 6), IR(26958, 12), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageDrefGather, true, true, IR(195, 6), IR(26970, 16), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageRead, true, true, IR(185, 5), IR(26986, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageWrite, false, false, IR(207, 4), IR(26996, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImage, true, true, IR(160, 3), IR(24207, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryFormat, true, true, IR(160, 3), IR(27007, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryOrder, true, true, IR(160, 3), IR(27024, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySizeLod, true, true, IR(172, 4), IR(27040, 18), IR(0, 0), IR(207, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySize, true, true, IR(160, 3), IR(27058, 15), IR(0, 0), IR(207, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryLod, true, true, IR(172, 4), IR(27073, 14), IR(0, 0), IR(209, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQueryLevels, true, true, IR(160, 3), IR(27087, 17), IR(0, 0), IR(207, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageQuerySamples, true, true, IR(160, 3), IR(27104, 18), IR(0, 0), IR(207, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpConvertFToU, true, true, IR(160, 3), IR(27122, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertFToS, true, true, IR(160, 3), IR(27134, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertSToF, true, true, IR(160, 3), IR(27146, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToF, true, true, IR(160, 3), IR(27158, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpUConvert, true, true, IR(160, 3), IR(27170, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSConvert, true, true, IR(160, 3), IR(27179, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpFConvert, true, true, IR(160, 3), IR(27188, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpQuantizeToF16, true, true, IR(160, 3), IR(27197, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertPtrToU, true, true, IR(160, 3), IR(27211, 14), IR(0, 0), IR(198, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSatConvertSToU, true, true, IR(160, 3), IR(27225, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSatConvertUToS, true, true, IR(160, 3), IR(27240, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToPtr, true, true, IR(160, 3), IR(27255, 14), IR(0, 0), IR(198, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpPtrCastToGeneric, true, true, IR(160, 3), IR(27269, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpGenericCastToPtr, true, true, IR(160, 3), IR(27286, 17), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpGenericCastToPtrExplicit, true, true, IR(211, 4), IR(27303, 25), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpBitcast, true, true, IR(160, 3), IR(27328, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpSNegate, true, true, IR(160, 3), IR(27336, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFNegate, true, true, IR(160, 3), IR(27344, 8), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIAdd, true, true, IR(172, 4), IR(27352, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFAdd, true, true, IR(172, 4), IR(27357, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpISub, true, true, IR(172, 4), IR(27362, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFSub, true, true, IR(172, 4), IR(27367, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIMul, true, true, IR(172, 4), IR(27372, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFMul, true, true, IR(172, 4), IR(27377, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDiv, true, true, IR(172, 4), IR(27382, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSDiv, true, true, IR(172, 4), IR(27387, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFDiv, true, true, IR(172, 4), IR(27392, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUMod, true, true, IR(172, 4), IR(27397, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSRem, true, true, IR(172, 4), IR(27402, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSMod, true, true, IR(172, 4), IR(27407, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFRem, true, true, IR(172, 4), IR(27412, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpFMod, true, true, IR(172, 4), IR(27417, 5), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpVectorTimesScalar, true, true, IR(172, 4), IR(27422, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesScalar, true, true, IR(172, 4), IR(27440, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpVectorTimesMatrix, true, true, IR(172, 4), IR(27458, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesVector, true, true, IR(172, 4), IR(27476, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpMatrixTimesMatrix, true, true, IR(172, 4), IR(27494, 18), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpOuterProduct, true, true, IR(172, 4), IR(27512, 13), IR(0, 0), IR(66, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpDot, true, true, IR(172, 4), IR(27525, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpIAddCarry, true, true, IR(172, 4), IR(27529, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpISubBorrow, true, true, IR(172, 4), IR(27539, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUMulExtended, true, true, IR(172, 4), IR(27550, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSMulExtended, true, true, IR(172, 4), IR(27563, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpAny, true, true, IR(160, 3), IR(27576, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpAll, true, true, IR(160, 3), IR(27580, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsNan, true, true, IR(160, 3), IR(27584, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsInf, true, true, IR(160, 3), IR(27590, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsFinite, true, true, IR(160, 3), IR(27596, 9), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIsNormal, true, true, IR(160, 3), IR(27605, 9), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSignBitSet, true, true, IR(160, 3), IR(27614, 11), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLessOrGreater, true, true, IR(172, 4), IR(27625, 14), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), SPV_SPIRV_VERSION_WORD(1,5), PrintingClass::kRelational_and_Logical},
  {spv::Op::OpOrdered, true, true, IR(172, 4), IR(27639, 8), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUnordered, true, true, IR(172, 4), IR(27647, 10), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalEqual, true, true, IR(172, 4), IR(27657, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalNotEqual, true, true, IR(172, 4), IR(27670, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalOr, true, true, IR(172, 4), IR(27686, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalAnd, true, true, IR(172, 4), IR(27696, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpLogicalNot, true, true, IR(160, 3), IR(27707, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSelect, true, true, IR(130, 5), IR(27718, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpIEqual, true, true, IR(172, 4), IR(27725, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpINotEqual, true, true, IR(172, 4), IR(27732, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUGreaterThan, true, true, IR(172, 4), IR(27742, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSGreaterThan, true, true, IR(172, 4), IR(27755, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpUGreaterThanEqual, true, true, IR(172, 4), IR(27768, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSGreaterThanEqual, true, true, IR(172, 4), IR(27786, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpULessThan, true, true, IR(172, 4), IR(27804, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSLessThan, true, true, IR(172, 4), IR(27814, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpULessThanEqual, true, true, IR(172, 4), IR(27824, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpSLessThanEqual, true, true, IR(172, 4), IR(27839, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdEqual, true, true, IR(172, 4), IR(27854, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordEqual, true, true, IR(172, 4), IR(27864, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdNotEqual, true, true, IR(172, 4), IR(27876, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordNotEqual, true, true, IR(172, 4), IR(27889, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdLessThan, true, true, IR(172, 4), IR(27904, 13), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordLessThan, true, true, IR(172, 4), IR(27917, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdGreaterThan, true, true, IR(172, 4), IR(27932, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordGreaterThan, true, true, IR(172, 4), IR(27948, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdLessThanEqual, true, true, IR(172, 4), IR(27966, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordLessThanEqual, true, true, IR(172, 4), IR(27984, 20), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFOrdGreaterThanEqual, true, true, IR(172, 4), IR(28004, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpFUnordGreaterThanEqual, true, true, IR(172, 4), IR(28025, 23), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kRelational_and_Logical},
  {spv::Op::OpShiftRightLogical, true, true, IR(172, 4), IR(28048, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpShiftRightArithmetic, true, true, IR(172, 4), IR(28066, 21), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpShiftLeftLogical, true, true, IR(172, 4), IR(28087, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseOr, true, true, IR(172, 4), IR(28104, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseXor, true, true, IR(172, 4), IR(28114, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitwiseAnd, true, true, IR(172, 4), IR(28125, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpNot, true, true, IR(160, 3), IR(28136, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldInsert, true, true, IR(215, 6), IR(28140, 15), IR(0, 0), IR(210, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldSExtract, true, true, IR(130, 5), IR(28155, 17), IR(0, 0), IR(210, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitFieldUExtract, true, true, IR(130, 5), IR(28172, 17), IR(0, 0), IR(210, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitReverse, true, true, IR(160, 3), IR(28189, 11), IR(0, 0), IR(210, 2), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpBitCount, true, true, IR(160, 3), IR(28200, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpDPdx, true, true, IR(160, 3), IR(28209, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdy, true, true, IR(160, 3), IR(28214, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidth, true, true, IR(160, 3), IR(28219, 7), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdxFine, true, true, IR(160, 3), IR(28226, 9), IR(0, 0), IR(212, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdyFine, true, true, IR(160, 3), IR(28235, 9), IR(0, 0), IR(212, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidthFine, true, true, IR(160, 3), IR(28244, 11), IR(0, 0), IR(212, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdxCoarse, true, true, IR(160, 3), IR(28255, 11), IR(0, 0), IR(212, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpDPdyCoarse, true, true, IR(160, 3), IR(28266, 11), IR(0, 0), IR(212, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpFwidthCoarse, true, true, IR(160, 3), IR(28277, 13), IR(0, 0), IR(212, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDerivative},
  {spv::Op::OpEmitVertex, false, false, IR(0, 0), IR(28290, 11), IR(0, 0), IR(69, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEndPrimitive, false, false, IR(0, 0), IR(28301, 13), IR(0, 0), IR(69, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEmitStreamVertex, false, false, IR(10, 1), IR(28314, 17), IR(0, 0), IR(110, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpEndStreamPrimitive, false, false, IR(10, 1), IR(28331, 19), IR(0, 0), IR(110, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPrimitive},
  {spv::Op::OpControlBarrier, false, false, IR(221, 3), IR(28387, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpMemoryBarrier, false, false, IR(224, 2), IR(28402, 14), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpAtomicLoad, true, true, IR(226, 5), IR(28416, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicStore, false, false, IR(231, 4), IR(28427, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicExchange, true, true, IR(235, 6), IR(28439, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicCompareExchange, true, true, IR(241, 8), IR(28454, 22), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicCompareExchangeWeak, true, true, IR(241, 8), IR(28476, 26), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), SPV_SPIRV_VERSION_WORD(1,3), PrintingClass::kAtomic},
  {spv::Op::OpAtomicIIncrement, true, true, IR(226, 5), IR(28502, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicIDecrement, true, true, IR(226, 5), IR(28519, 17), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicIAdd, true, true, IR(235, 6), IR(28536, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicISub, true, true, IR(235, 6), IR(28547, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicSMin, true, true, IR(235, 6), IR(28558, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicUMin, true, true, IR(235, 6), IR(28569, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicSMax, true, true, IR(235, 6), IR(28580, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicUMax, true, true, IR(235, 6), IR(28591, 11), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicAnd, true, true, IR(235, 6), IR(28602, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicOr, true, true, IR(235, 6), IR(28612, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicXor, true, true, IR(235, 6), IR(28621, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpPhi, true, true, IR(107, 3), IR(28631, 4), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLoopMerge, false, false, IR(249, 3), IR(28665, 10), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpSelectionMerge, false, false, IR(252, 2), IR(28710, 15), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLabel, true, false, IR(68, 1), IR(28725, 6), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpBranch, false, false, IR(10, 1), IR(28731, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpBranchConditional, false, false, IR(254, 4), IR(28738, 18), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpSwitch, false, false, IR(258, 3), IR(28801, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpKill, false, false, IR(0, 0), IR(28808, 5), IR(0, 0), IR(3, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpReturn, false, false, IR(0, 0), IR(28813, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpReturnValue, false, false, IR(10, 1), IR(28820, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpUnreachable, false, false, IR(0, 0), IR(28832, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLifetimeStart, false, false, IR(261, 2), IR(28844, 14), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpLifetimeStop, false, false, IR(261, 2), IR(28858, 13), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpGroupAsyncCopy, true, true, IR(263, 8), IR(28871, 15), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupWaitEvents, false, false, IR(271, 3), IR(28886, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupAll, true, true, IR(274, 4), IR(28902, 9), IR(0, 0), IR(213, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupAny, true, true, IR(274, 4), IR(28911, 9), IR(0, 0), IR(213, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBroadcast, true, true, IR(278, 5), IR(28920, 15), IR(0, 0), IR(213, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupIAdd, true, true, IR(283, 5), IR(28968, 10), IR(0, 0), IR(213, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFAdd, true, true, IR(283, 5), IR(28978, 10), IR(0, 0), IR(213, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMin, true, true, IR(283, 5), IR(28988, 10), IR(0, 0), IR(213, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMin, true, true, IR(283, 5), IR(28998, 10), IR(0, 0), IR(213, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMin, true, true, IR(283, 5), IR(29008, 10), IR(0, 0), IR(213, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMax, true, true, IR(283, 5), IR(29018, 10), IR(0, 0), IR(213, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMax, true, true, IR(283, 5), IR(29028, 10), IR(0, 0), IR(213, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMax, true, true, IR(283, 5), IR(29038, 10), IR(0, 0), IR(213, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpReadPipe, true, true, IR(215, 6), IR(29048, 9), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpWritePipe, true, true, IR(215, 6), IR(29057, 10), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReservedReadPipe, true, true, IR(288, 8), IR(29067, 17), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReservedWritePipe, true, true, IR(288, 8), IR(29084, 18), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReserveReadPipePackets, true, true, IR(215, 6), IR(29102, 23), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpReserveWritePipePackets, true, true, IR(215, 6), IR(29125, 24), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCommitReadPipe, false, false, IR(296, 4), IR(29149, 15), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCommitWritePipe, false, false, IR(296, 4), IR(29164, 16), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpIsValidReserveId, true, true, IR(160, 3), IR(29180, 17), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetNumPipePackets, true, true, IR(130, 5), IR(29197, 18), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetMaxPipePackets, true, true, IR(130, 5), IR(29215, 18), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupReserveReadPipePackets, true, true, IR(300, 7), IR(29233, 28), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupReserveWritePipePackets, true, true, IR(300, 7), IR(29261, 29), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupCommitReadPipe, false, false, IR(307, 5), IR(29290, 20), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGroupCommitWritePipe, false, false, IR(307, 5), IR(29310, 21), IR(0, 0), IR(75, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpEnqueueMarker, true, true, IR(215, 6), IR(29331, 14), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpEnqueueKernel, true, true, IR(312, 13), IR(29345, 14), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelNDrangeSubGroupCount, true, true, IR(325, 7), IR(29359, 30), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelNDrangeMaxSubGroupSize, true, true, IR(325, 7), IR(29389, 32), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelWorkGroupSize, true, true, IR(215, 6), IR(29421, 23), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelPreferredWorkGroupSizeMultiple, true, true, IR(215, 6), IR(29444, 40), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpRetainEvent, false, false, IR(10, 1), IR(29484, 12), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpReleaseEvent, false, false, IR(10, 1), IR(29496, 13), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpCreateUserEvent, true, true, IR(39, 2), IR(29509, 16), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpIsValidEvent, true, true, IR(160, 3), IR(29525, 13), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpSetUserEventStatus, false, false, IR(36, 2), IR(29538, 19), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpCaptureEventProfilingInfo, false, false, IR(33, 3), IR(29557, 26), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetDefaultQueue, true, true, IR(39, 2), IR(29583, 16), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpBuildNDRange, true, true, IR(130, 5), IR(29599, 13), IR(0, 0), IR(74, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpImageSparseSampleImplicitLod, true, true, IR(185, 5), IR(29612, 29), IR(0, 0), IR(214, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleExplicitLod, true, true, IR(190, 5), IR(29641, 29), IR(0, 0), IR(214, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleDrefImplicitLod, true, true, IR(195, 6), IR(29670, 33), IR(0, 0), IR(214, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleDrefExplicitLod, true, true, IR(201, 6), IR(29703, 33), IR(0, 0), IR(214, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjImplicitLod, true, true, IR(185, 5), IR(29736, 33), IR(0, 0), IR(214, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjExplicitLod, true, true, IR(190, 5), IR(29769, 33), IR(0, 0), IR(214, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjDrefImplicitLod, true, true, IR(195, 6), IR(29802, 37), IR(0, 0), IR(214, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseSampleProjDrefExplicitLod, true, true, IR(201, 6), IR(29839, 37), IR(0, 0), IR(214, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseFetch, true, true, IR(185, 5), IR(29876, 17), IR(0, 0), IR(214, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseGather, true, true, IR(195, 6), IR(29893, 18), IR(0, 0), IR(214, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseDrefGather, true, true, IR(195, 6), IR(29911, 22), IR(0, 0), IR(214, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageSparseTexelsResident, true, true, IR(160, 3), IR(29933, 26), IR(0, 0), IR(214, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpNoLine, false, false, IR(0, 0), IR(29959, 7), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpAtomicFlagTestAndSet, true, true, IR(226, 5), IR(29966, 21), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicFlagClear, false, false, IR(332, 3), IR(29987, 16), IR(0, 0), IR(0, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpImageSparseRead, true, true, IR(185, 5), IR(30003, 16), IR(0, 0), IR(214, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,0), 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpSizeOf, true, true, IR(160, 3), IR(30019, 7), IR(0, 0), IR(1, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpTypePipeStorage, true, false, IR(68, 1), IR(30026, 16), IR(0, 0), IR(215, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantPipeStorage, true, true, IR(335, 5), IR(30042, 20), IR(0, 0), IR(215, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpCreatePipeFromPipeStorage, true, true, IR(160, 3), IR(30062, 26), IR(0, 0), IR(215, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpGetKernelLocalSizeForSubgroupCount, true, true, IR(325, 7), IR(30088, 35), IR(0, 0), IR(148, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpGetKernelMaxNumSubgroups, true, true, IR(215, 6), IR(30123, 25), IR(0, 0), IR(148, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDevice_Side_Enqueue},
  {spv::Op::OpTypeNamedBarrier, true, false, IR(68, 1), IR(30148, 17), IR(0, 0), IR(216, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpNamedBarrierInitialize, true, true, IR(160, 3), IR(30165, 23), IR(0, 0), IR(216, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpMemoryNamedBarrier, false, false, IR(332, 3), IR(30188, 19), IR(0, 0), IR(216, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpModuleProcessed, false, false, IR(11, 1), IR(30207, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,1), 0xffffffffu, PrintingClass::kDebug},
  {spv::Op::OpExecutionModeId, false, false, IR(65, 2), IR(30223, 16), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,2), 0xffffffffu, PrintingClass::kMode_Setting},
  {spv::Op::OpDecorateId, false, false, IR(163, 2), IR(30239, 11), IR(0, 0), IR(1, 0), IR(152, 1), SPV_SPIRV_VERSION_WORD(1,2), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpGroupNonUniformElect, true, true, IR(340, 3), IR(30250, 21), IR(0, 0), IR(76, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAll, true, true, IR(274, 4), IR(30271, 19), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAny, true, true, IR(274, 4), IR(30290, 19), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformAllEqual, true, true, IR(274, 4), IR(30309, 24), IR(0, 0), IR(217, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBroadcast, true, true, IR(278, 5), IR(30333, 25), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBroadcastFirst, true, true, IR(274, 4), IR(30358, 30), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallot, true, true, IR(274, 4), IR(5528, 22), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformInverseBallot, true, true, IR(274, 4), IR(30388, 29), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotBitExtract, true, true, IR(278, 5), IR(30417, 32), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotBitCount, true, true, IR(283, 5), IR(30449, 30), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotFindLSB, true, true, IR(274, 4), IR(30479, 29), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBallotFindMSB, true, true, IR(274, 4), IR(30508, 29), IR(0, 0), IR(218, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffle, true, true, IR(278, 5), IR(8618, 23), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleXor, true, true, IR(278, 5), IR(30537, 26), IR(0, 0), IR(219, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleUp, true, true, IR(278, 5), IR(30563, 25), IR(0, 0), IR(220, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformShuffleDown, true, true, IR(278, 5), IR(30588, 27), IR(0, 0), IR(220, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformIAdd, true, true, IR(343, 6), IR(30615, 20), IR(0, 0), IR(221, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFAdd, true, true, IR(343, 6), IR(30635, 20), IR(0, 0), IR(221, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformIMul, true, true, IR(343, 6), IR(30655, 20), IR(0, 0), IR(221, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMul, true, true, IR(343, 6), IR(30675, 20), IR(0, 0), IR(221, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformSMin, true, true, IR(343, 6), IR(30695, 20), IR(0, 0), IR(221, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformUMin, true, true, IR(343, 6), IR(30715, 20), IR(0, 0), IR(221, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMin, true, true, IR(343, 6), IR(30735, 20), IR(0, 0), IR(221, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformSMax, true, true, IR(343, 6), IR(30755, 20), IR(0, 0), IR(221, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformUMax, true, true, IR(343, 6), IR(30775, 20), IR(0, 0), IR(221, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformFMax, true, true, IR(343, 6), IR(30795, 20), IR(0, 0), IR(221, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseAnd, true, true, IR(343, 6), IR(30815, 26), IR(0, 0), IR(221, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseOr, true, true, IR(343, 6), IR(30841, 25), IR(0, 0), IR(221, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformBitwiseXor, true, true, IR(343, 6), IR(30866, 26), IR(0, 0), IR(221, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalAnd, true, true, IR(343, 6), IR(30892, 26), IR(0, 0), IR(221, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalOr, true, true, IR(343, 6), IR(30918, 25), IR(0, 0), IR(221, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformLogicalXor, true, true, IR(343, 6), IR(30943, 26), IR(0, 0), IR(221, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadBroadcast, true, true, IR(278, 5), IR(30969, 29), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadSwap, true, true, IR(278, 5), IR(30998, 24), IR(0, 0), IR(224, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,3), 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpCopyLogical, true, true, IR(160, 3), IR(31022, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpPtrEqual, true, true, IR(172, 4), IR(31034, 9), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrNotEqual, true, true, IR(172, 4), IR(31043, 12), IR(0, 0), IR(1, 0), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpPtrDiff, true, true, IR(172, 4), IR(31055, 8), IR(0, 0), IR(225, 3), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpColorAttachmentReadEXT, true, true, IR(349, 4), IR(31063, 23), IR(0, 0), IR(140, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpDepthAttachmentReadEXT, true, true, IR(353, 3), IR(31086, 23), IR(0, 0), IR(149, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpStencilAttachmentReadEXT, true, true, IR(353, 3), IR(31109, 25), IR(0, 0), IR(150, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpTypeTensorARM, true, false, IR(356, 4), IR(31134, 14), IR(0, 0), IR(197, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTensorReadARM, true, true, IR(360, 5), IR(31190, 14), IR(0, 0), IR(197, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpTensorWriteARM, false, false, IR(365, 4), IR(31204, 15), IR(0, 0), IR(197, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpTensorQuerySizeARM, true, true, IR(172, 4), IR(31219, 19), IR(0, 0), IR(197, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kTensor},
  {spv::Op::OpTerminateInvocation, false, false, IR(0, 0), IR(31238, 20), IR(0, 0), IR(3, 1), IR(162, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpTypeUntypedPointerKHR, true, false, IR(369, 2), IR(31258, 22), IR(0, 0), IR(228, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpUntypedVariableKHR, true, true, IR(371, 5), IR(31280, 19), IR(0, 0), IR(228, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedAccessChainKHR, true, true, IR(151, 5), IR(31299, 22), IR(0, 0), IR(228, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedInBoundsAccessChainKHR, true, true, IR(151, 5), IR(31321, 30), IR(0, 0), IR(228, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpSubgroupBallotKHR, true, true, IR(160, 3), IR(5289, 18), IR(0, 0), IR(229, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupFirstInvocationKHR, true, true, IR(160, 3), IR(31351, 27), IR(0, 0), IR(229, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpUntypedPtrAccessChainKHR, true, true, IR(376, 6), IR(31378, 25), IR(0, 0), IR(228, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedInBoundsPtrAccessChainKHR, true, true, IR(376, 6), IR(31403, 33), IR(0, 0), IR(228, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedArrayLengthKHR, true, true, IR(382, 5), IR(31436, 22), IR(0, 0), IR(228, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpUntypedPrefetchKHR, false, false, IR(387, 5), IR(31458, 19), IR(0, 0), IR(228, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpSubgroupAllKHR, true, true, IR(160, 3), IR(31477, 15), IR(0, 0), IR(230, 1), IR(39, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupAnyKHR, true, true, IR(160, 3), IR(31492, 15), IR(0, 0), IR(230, 1), IR(39, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupAllEqualKHR, true, true, IR(160, 3), IR(31507, 20), IR(0, 0), IR(230, 1), IR(39, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupNonUniformRotateKHR, true, true, IR(392, 6), IR(13050, 25), IR(0, 0), IR(231, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupReadInvocationKHR, true, true, IR(172, 4), IR(31527, 26), IR(0, 0), IR(229, 1), IR(2, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpExtInstWithForwardRefsKHR, true, true, IR(398, 5), IR(31553, 26), IR(0, 0), IR(1, 0), IR(163, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kExtension},
  {spv::Op::OpTraceRayKHR, false, false, IR(403, 11), IR(31579, 12), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpExecuteCallableKHR, false, false, IR(36, 2), IR(31591, 19), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToAccelerationStructureKHR, true, true, IR(160, 3), IR(31610, 35), IR(0, 0), IR(232, 2), IR(164, 2), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIgnoreIntersectionKHR, false, false, IR(0, 0), IR(31645, 22), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTerminateRayKHR, false, false, IR(0, 0), IR(31667, 16), IR(0, 0), IR(60, 1), IR(28, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSDot, true, true, IR(414, 5), IR(31730, 5), IR(93, 1), IR(234, 1), IR(119, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDot, true, true, IR(414, 5), IR(31743, 5), IR(94, 1), IR(234, 1), IR(119, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSUDot, true, true, IR(414, 5), IR(31756, 6), IR(95, 1), IR(234, 1), IR(119, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSDotAccSat, true, true, IR(419, 6), IR(31771, 11), IR(96, 1), IR(234, 1), IR(119, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpUDotAccSat, true, true, IR(419, 6), IR(31796, 11), IR(97, 1), IR(234, 1), IR(119, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpSUDotAccSat, true, true, IR(419, 6), IR(31821, 12), IR(98, 1), IR(234, 1), IR(119, 1), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpTypeCooperativeMatrixKHR, true, false, IR(425, 6), IR(31848, 25), IR(0, 0), IR(235, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeMatrixLoadKHR, true, true, IR(431, 6), IR(31873, 25), IR(0, 0), IR(235, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixStoreKHR, false, false, IR(437, 5), IR(31898, 26), IR(0, 0), IR(235, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixMulAddKHR, true, true, IR(442, 6), IR(31978, 27), IR(0, 0), IR(235, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpCooperativeMatrixLengthKHR, true, true, IR(160, 3), IR(32005, 27), IR(0, 0), IR(235, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpConstantCompositeReplicateEXT, true, true, IR(160, 3), IR(32032, 30), IR(0, 0), IR(236, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCompositeReplicateEXT, true, true, IR(160, 3), IR(32062, 34), IR(0, 0), IR(236, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpCompositeConstructReplicateEXT, true, true, IR(160, 3), IR(32096, 31), IR(0, 0), IR(236, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpTypeRayQueryKHR, true, false, IR(68, 1), IR(32127, 16), IR(0, 0), IR(187, 1), IR(46, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpRayQueryInitializeKHR, false, false, IR(448, 8), IR(32143, 22), IR(0, 0), IR(187, 1), IR(46, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryTerminateKHR, false, false, IR(10, 1), IR(32165, 21), IR(0, 0), IR(187, 1), IR(46, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGenerateIntersectionKHR, false, false, IR(36, 2), IR(32186, 32), IR(0, 0), IR(187, 1), IR(46, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryConfirmIntersectionKHR, false, false, IR(10, 1), IR(32218, 31), IR(0, 0), IR(187, 1), IR(46, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryProceedKHR, true, true, IR(160, 3), IR(32249, 19), IR(0, 0), IR(187, 1), IR(46, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTypeKHR, true, true, IR(172, 4), IR(32268, 31), IR(0, 0), IR(187, 1), IR(46, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpImageSampleWeightedQCOM, true, true, IR(130, 5), IR(32299, 24), IR(0, 0), IR(237, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBoxFilterQCOM, true, true, IR(130, 5), IR(32323, 19), IR(0, 0), IR(238, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchSSDQCOM, true, true, IR(325, 7), IR(32342, 23), IR(0, 0), IR(239, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchSADQCOM, true, true, IR(325, 7), IR(32365, 23), IR(0, 0), IR(239, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchWindowSSDQCOM, true, true, IR(325, 7), IR(32388, 29), IR(0, 0), IR(240, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchWindowSADQCOM, true, true, IR(325, 7), IR(32417, 29), IR(0, 0), IR(240, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchGatherSSDQCOM, true, true, IR(325, 7), IR(32446, 29), IR(0, 0), IR(240, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpImageBlockMatchGatherSADQCOM, true, true, IR(325, 7), IR(32475, 29), IR(0, 0), IR(240, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpGroupIAddNonUniformAMD, true, true, IR(283, 5), IR(32504, 23), IR(0, 0), IR(213, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFAddNonUniformAMD, true, true, IR(283, 5), IR(32527, 23), IR(0, 0), IR(213, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMinNonUniformAMD, true, true, IR(283, 5), IR(32550, 23), IR(0, 0), IR(213, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMinNonUniformAMD, true, true, IR(283, 5), IR(32573, 23), IR(0, 0), IR(213, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMinNonUniformAMD, true, true, IR(283, 5), IR(32596, 23), IR(0, 0), IR(213, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMaxNonUniformAMD, true, true, IR(283, 5), IR(32619, 23), IR(0, 0), IR(213, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupUMaxNonUniformAMD, true, true, IR(283, 5), IR(32642, 23), IR(0, 0), IR(213, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupSMaxNonUniformAMD, true, true, IR(283, 5), IR(32665, 23), IR(0, 0), IR(213, 1), IR(33, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpFragmentMaskFetchAMD, true, true, IR(172, 4), IR(32688, 21), IR(0, 0), IR(241, 1), IR(55, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFragmentFetchAMD, true, true, IR(130, 5), IR(32709, 17), IR(0, 0), IR(241, 1), IR(55, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReadClockKHR, true, true, IR(340, 3), IR(32726, 13), IR(0, 0), IR(242, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAllocateNodePayloadsAMDX, true, true, IR(278, 5), IR(32739, 25), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpEnqueueNodePayloadsAMDX, false, false, IR(10, 1), IR(32764, 24), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeNodePayloadArrayAMDX, true, false, IR(87, 2), IR(32788, 25), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFinishWritingNodePayloadAMDX, true, true, IR(160, 3), IR(32813, 29), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpNodePayloadArrayLengthAMDX, true, true, IR(160, 3), IR(32842, 27), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIsNodePayloadValidAMDX, true, true, IR(172, 4), IR(32869, 23), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConstantStringAMDX, true, false, IR(50, 2), IR(32892, 19), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSpecConstantStringAMDX, true, false, IR(50, 2), IR(32911, 23), IR(0, 0), IR(43, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpGroupNonUniformQuadAllKHR, true, true, IR(160, 3), IR(32934, 26), IR(0, 0), IR(157, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpGroupNonUniformQuadAnyKHR, true, true, IR(160, 3), IR(32960, 26), IR(0, 0), IR(157, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpHitObjectRecordHitMotionNV, false, false, IR(456, 14), IR(32986, 27), IR(0, 0), IR(243, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitWithIndexMotionNV, false, false, IR(470, 13), IR(33013, 36), IR(0, 0), IR(243, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissMotionNV, false, false, IR(483, 7), IR(33049, 28), IR(0, 0), IR(243, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldToObjectNV, true, true, IR(160, 3), IR(33077, 28), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectToWorldNV, true, true, IR(160, 3), IR(33105, 28), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayDirectionNV, true, true, IR(160, 3), IR(33133, 33), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetObjectRayOriginNV, true, true, IR(160, 3), IR(33166, 30), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayMotionNV, false, false, IR(470, 13), IR(33196, 26), IR(0, 0), IR(243, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderRecordBufferHandleNV, true, true, IR(160, 3), IR(33222, 39), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetShaderBindingTableRecordIndexNV, true, true, IR(160, 3), IR(33261, 44), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordEmptyNV, false, false, IR(10, 1), IR(33305, 23), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectTraceRayNV, false, false, IR(490, 12), IR(33328, 20), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitNV, false, false, IR(470, 13), IR(33348, 21), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordHitWithIndexNV, false, false, IR(490, 12), IR(33369, 30), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectRecordMissNV, false, false, IR(502, 6), IR(33399, 22), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectExecuteShaderNV, false, false, IR(36, 2), IR(33421, 25), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetCurrentTimeNV, true, true, IR(160, 3), IR(33446, 26), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetAttributesNV, false, false, IR(36, 2), IR(33472, 25), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetHitKindNV, true, true, IR(160, 3), IR(33497, 22), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetPrimitiveIndexNV, true, true, IR(160, 3), IR(33519, 29), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetGeometryIndexNV, true, true, IR(160, 3), IR(33548, 28), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceIdNV, true, true, IR(160, 3), IR(33576, 25), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetInstanceCustomIndexNV, true, true, IR(160, 3), IR(33601, 34), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayDirectionNV, true, true, IR(160, 3), IR(33635, 32), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetWorldRayOriginNV, true, true, IR(160, 3), IR(33667, 29), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMaxNV, true, true, IR(160, 3), IR(33696, 22), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetRayTMinNV, true, true, IR(160, 3), IR(33718, 22), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsEmptyNV, true, true, IR(160, 3), IR(33740, 19), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsHitNV, true, true, IR(160, 3), IR(33759, 17), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsMissNV, true, true, IR(160, 3), IR(33776, 18), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHitObjectNV, false, false, IR(508, 3), IR(33794, 29), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpReorderThreadWithHintNV, false, false, IR(36, 2), IR(33823, 24), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeHitObjectNV, true, false, IR(68, 1), IR(33847, 16), IR(0, 0), IR(119, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpImageSampleFootprintNV, true, true, IR(511, 7), IR(33863, 23), IR(0, 0), IR(245, 1), IR(69, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kImage},
  {spv::Op::OpTypeCooperativeVectorNV, true, false, IR(89, 3), IR(33886, 24), IR(0, 0), IR(246, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeVectorMatrixMulNV, true, true, IR(518, 13), IR(33910, 29), IR(0, 0), IR(246, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorOuterProductAccumulateNV, false, false, IR(531, 7), IR(33939, 42), IR(0, 0), IR(247, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorReduceSumAccumulateNV, false, false, IR(33, 3), IR(33981, 39), IR(0, 0), IR(247, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorMatrixMulAddNV, true, true, IR(538, 16), IR(34020, 32), IR(0, 0), IR(246, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixConvertNV, true, true, IR(160, 3), IR(34052, 27), IR(0, 0), IR(248, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpEmitMeshTasksEXT, false, false, IR(554, 4), IR(34079, 17), IR(0, 0), IR(53, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSetMeshOutputsEXT, false, false, IR(36, 2), IR(34096, 18), IR(0, 0), IR(53, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpGroupNonUniformPartitionNV, true, true, IR(160, 3), IR(34114, 27), IR(0, 0), IR(178, 1), IR(72, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kNon_Uniform},
  {spv::Op::OpWritePackedPrimitiveIndices4x8NV, false, false, IR(36, 2), IR(34141, 33), IR(0, 0), IR(50, 1), IR(18, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFetchMicroTriangleVertexPositionNV, true, true, IR(325, 7), IR(34174, 35), IR(0, 0), IR(249, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpFetchMicroTriangleVertexBarycentricNV, true, true, IR(325, 7), IR(34209, 38), IR(0, 0), IR(249, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeVectorLoadNV, true, true, IR(558, 5), IR(34247, 24), IR(0, 0), IR(246, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeVectorStoreNV, false, false, IR(563, 4), IR(34271, 25), IR(0, 0), IR(246, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpReportIntersectionKHR, true, true, IR(172, 4), IR(34296, 22), IR(99, 1), IR(54, 2), IR(24, 2), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIgnoreIntersectionNV, false, false, IR(0, 0), IR(34339, 21), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTerminateRayNV, false, false, IR(0, 0), IR(34360, 15), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceNV, false, false, IR(403, 11), IR(34375, 8), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceMotionNV, false, false, IR(490, 12), IR(34383, 14), IR(0, 0), IR(57, 1), IR(27, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTraceRayMotionNV, false, false, IR(490, 12), IR(34397, 17), IR(0, 0), IR(57, 1), IR(27, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTriangleVertexPositionsKHR, true, true, IR(172, 4), IR(34414, 50), IR(0, 0), IR(250, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeAccelerationStructureKHR, true, false, IR(68, 1), IR(34464, 29), IR(100, 1), IR(251, 4), IR(166, 4), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpExecuteCallableNV, false, false, IR(36, 2), IR(34521, 18), IR(0, 0), IR(56, 1), IR(26, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetClusterIdNV, true, true, IR(172, 4), IR(34539, 23), IR(0, 0), IR(64, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetClusterIdNV, true, true, IR(160, 3), IR(34562, 24), IR(0, 0), IR(64, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeCooperativeMatrixNV, true, false, IR(567, 5), IR(34586, 24), IR(0, 0), IR(255, 1), IR(76, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCooperativeMatrixLoadNV, true, true, IR(572, 6), IR(34610, 24), IR(0, 0), IR(255, 1), IR(76, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixStoreNV, false, false, IR(578, 5), IR(34634, 25), IR(0, 0), IR(255, 1), IR(76, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixMulAddNV, true, true, IR(130, 5), IR(34659, 26), IR(0, 0), IR(255, 1), IR(76, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixLengthNV, true, true, IR(160, 3), IR(34685, 26), IR(0, 0), IR(255, 1), IR(76, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpBeginInvocationInterlockEXT, false, false, IR(0, 0), IR(34711, 28), IR(0, 0), IR(256, 3), IR(77, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpEndInvocationInterlockEXT, false, false, IR(0, 0), IR(34739, 26), IR(0, 0), IR(256, 3), IR(77, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixReduceNV, true, true, IR(583, 5), IR(34808, 26), IR(0, 0), IR(259, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kArithmetic},
  {spv::Op::OpCooperativeMatrixLoadTensorNV, true, true, IR(588, 7), IR(34909, 30), IR(0, 0), IR(195, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixStoreTensorNV, false, false, IR(595, 5), IR(34939, 31), IR(0, 0), IR(195, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpCooperativeMatrixPerElementOpNV, true, true, IR(151, 5), IR(34970, 32), IR(0, 0), IR(260, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kFunction},
  {spv::Op::OpTypeTensorLayoutNV, true, false, IR(89, 3), IR(35002, 19), IR(0, 0), IR(261, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeTensorViewNV, true, false, IR(600, 4), IR(35021, 17), IR(0, 0), IR(261, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpCreateTensorLayoutNV, true, true, IR(39, 2), IR(35038, 21), IR(0, 0), IR(261, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetDimensionNV, true, true, IR(122, 4), IR(35059, 27), IR(0, 0), IR(261, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetStrideNV, true, true, IR(122, 4), IR(35086, 24), IR(0, 0), IR(261, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSliceNV, true, true, IR(122, 4), IR(35110, 20), IR(0, 0), IR(261, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetClampValueNV, true, true, IR(172, 4), IR(35130, 28), IR(0, 0), IR(261, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCreateTensorViewNV, true, true, IR(39, 2), IR(35158, 19), IR(0, 0), IR(261, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetDimensionNV, true, true, IR(122, 4), IR(35177, 25), IR(0, 0), IR(261, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetStrideNV, true, true, IR(122, 4), IR(35202, 22), IR(0, 0), IR(261, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpDemoteToHelperInvocation, false, false, IR(0, 0), IR(11362, 25), IR(45, 1), IR(262, 1), IR(0, 0), SPV_SPIRV_VERSION_WORD(1,6), 0xffffffffu, PrintingClass::kControl_Flow},
  {spv::Op::OpIsHelperInvocationEXT, true, true, IR(39, 2), IR(35224, 22), IR(0, 0), IR(262, 1), IR(78, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorViewSetClipNV, true, true, IR(325, 7), IR(35246, 20), IR(0, 0), IR(261, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTensorLayoutSetBlockSizeNV, true, true, IR(122, 4), IR(35266, 27), IR(0, 0), IR(261, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpCooperativeMatrixTransposeNV, true, true, IR(160, 3), IR(35293, 29), IR(0, 0), IR(248, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertUToImageNV, true, true, IR(160, 3), IR(35322, 18), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToSamplerNV, true, true, IR(160, 3), IR(35340, 20), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertImageToUNV, true, true, IR(160, 3), IR(35360, 18), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertSamplerToUNV, true, true, IR(160, 3), IR(35378, 20), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertUToSampledImageNV, true, true, IR(160, 3), IR(35398, 25), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConvertSampledImageToUNV, true, true, IR(160, 3), IR(35423, 25), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSamplerImageAddressingModeNV, false, false, IR(0, 1), IR(35448, 29), IR(0, 0), IR(120, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRawAccessChainNV, true, true, IR(604, 7), IR(35529, 17), IR(0, 0), IR(184, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpRayQueryGetIntersectionSpherePositionNV, true, true, IR(172, 4), IR(35546, 40), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionSphereRadiusNV, true, true, IR(172, 4), IR(35586, 38), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSPositionsNV, true, true, IR(172, 4), IR(35624, 38), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSRadiiNV, true, true, IR(172, 4), IR(35662, 34), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionLSSHitValueNV, true, true, IR(172, 4), IR(35696, 37), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetSpherePositionNV, true, true, IR(160, 3), IR(35733, 29), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetSphereRadiusNV, true, true, IR(160, 3), IR(35762, 27), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetLSSPositionsNV, true, true, IR(160, 3), IR(35789, 27), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectGetLSSRadiiNV, true, true, IR(160, 3), IR(35816, 23), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsSphereHitNV, true, true, IR(160, 3), IR(35839, 23), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpHitObjectIsLSSHitNV, true, true, IR(160, 3), IR(35862, 20), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryIsSphereHitNV, true, true, IR(172, 4), IR(35882, 22), IR(0, 0), IR(61, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryIsLSSHitNV, true, true, IR(172, 4), IR(35904, 19), IR(0, 0), IR(62, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpSubgroupShuffleINTEL, true, true, IR(172, 4), IR(11810, 21), IR(0, 0), IR(263, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleDownINTEL, true, true, IR(130, 5), IR(35923, 25), IR(0, 0), IR(263, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleUpINTEL, true, true, IR(130, 5), IR(35948, 23), IR(0, 0), IR(263, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupShuffleXorINTEL, true, true, IR(172, 4), IR(35971, 24), IR(0, 0), IR(263, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupBlockReadINTEL, true, true, IR(160, 3), IR(35995, 23), IR(0, 0), IR(264, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupBlockWriteINTEL, false, false, IR(36, 2), IR(36018, 24), IR(0, 0), IR(264, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageBlockReadINTEL, true, true, IR(172, 4), IR(36042, 28), IR(0, 0), IR(265, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageBlockWriteINTEL, false, false, IR(33, 3), IR(36070, 29), IR(0, 0), IR(265, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageMediaBlockReadINTEL, true, true, IR(215, 6), IR(36099, 33), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupImageMediaBlockWriteINTEL, false, false, IR(611, 5), IR(36132, 34), IR(0, 0), IR(266, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpUCountLeadingZerosINTEL, true, true, IR(160, 3), IR(36166, 24), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUCountTrailingZerosINTEL, true, true, IR(160, 3), IR(36190, 25), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAbsISubINTEL, true, true, IR(172, 4), IR(36215, 13), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAbsUSubINTEL, true, true, IR(172, 4), IR(36228, 13), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAddSatINTEL, true, true, IR(172, 4), IR(36241, 13), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAddSatINTEL, true, true, IR(172, 4), IR(36254, 13), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAverageINTEL, true, true, IR(172, 4), IR(36267, 14), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAverageINTEL, true, true, IR(172, 4), IR(36281, 14), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIAverageRoundedINTEL, true, true, IR(172, 4), IR(36295, 21), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUAverageRoundedINTEL, true, true, IR(172, 4), IR(36316, 21), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpISubSatINTEL, true, true, IR(172, 4), IR(36337, 13), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUSubSatINTEL, true, true, IR(172, 4), IR(36350, 13), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpIMul32x16INTEL, true, true, IR(172, 4), IR(36363, 15), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpUMul32x16INTEL, true, true, IR(172, 4), IR(36378, 15), IR(0, 0), IR(267, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpConstantFunctionPointerINTEL, true, true, IR(160, 3), IR(36393, 29), IR(0, 0), IR(193, 1), IR(92, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFunctionPointerCallINTEL, true, true, IR(107, 3), IR(36422, 25), IR(0, 0), IR(193, 1), IR(92, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmTargetINTEL, true, false, IR(50, 2), IR(36447, 15), IR(0, 0), IR(123, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmINTEL, true, true, IR(616, 6), IR(12028, 9), IR(0, 0), IR(123, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAsmCallINTEL, true, true, IR(122, 4), IR(36462, 13), IR(0, 0), IR(123, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAtomicFMinEXT, true, true, IR(235, 6), IR(36475, 14), IR(0, 0), IR(268, 4), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAtomicFMaxEXT, true, true, IR(235, 6), IR(36489, 14), IR(0, 0), IR(268, 4), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpAssumeTrueKHR, false, false, IR(10, 1), IR(36503, 14), IR(0, 0), IR(272, 1), IR(96, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpExpectKHR, true, true, IR(172, 4), IR(36517, 10), IR(0, 0), IR(272, 1), IR(96, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpDecorateString, false, false, IR(163, 2), IR(36527, 15), IR(101, 1), IR(1, 0), IR(170, 2), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpMemberDecorateString, false, false, IR(165, 3), IR(36563, 21), IR(102, 1), IR(1, 0), IR(170, 2), SPV_SPIRV_VERSION_WORD(1,4), 0xffffffffu, PrintingClass::kAnnotation},
  {spv::Op::OpVmeImageINTEL, true, true, IR(172, 4), IR(36611, 14), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeVmeImageINTEL, true, false, IR(87, 2), IR(36625, 18), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImePayloadINTEL, true, false, IR(68, 1), IR(36643, 23), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcRefPayloadINTEL, true, false, IR(68, 1), IR(36666, 23), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcSicPayloadINTEL, true, false, IR(68, 1), IR(36689, 23), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcMcePayloadINTEL, true, false, IR(68, 1), IR(36712, 23), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcMceResultINTEL, true, false, IR(68, 1), IR(36735, 22), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultINTEL, true, false, IR(68, 1), IR(36757, 22), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultSingleReferenceStreamoutINTEL, true, false, IR(68, 1), IR(36779, 46), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeResultDualReferenceStreamoutINTEL, true, false, IR(68, 1), IR(36825, 44), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeSingleReferenceStreaminINTEL, true, false, IR(68, 1), IR(36869, 39), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcImeDualReferenceStreaminINTEL, true, false, IR(68, 1), IR(36908, 37), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcRefResultINTEL, true, false, IR(68, 1), IR(36945, 22), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpTypeAvcSicResultINTEL, true, false, IR(68, 1), IR(36967, 22), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL, true, true, IR(172, 4), IR(36989, 60), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL, true, true, IR(172, 4), IR(37049, 53), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterShapePenaltyINTEL, true, true, IR(172, 4), IR(37102, 47), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterShapePenaltyINTEL, true, true, IR(172, 4), IR(37149, 40), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL, true, true, IR(172, 4), IR(37189, 51), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetInterDirectionPenaltyINTEL, true, true, IR(172, 4), IR(37240, 44), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL, true, true, IR(172, 4), IR(37284, 51), IR(0, 0), IR(274, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL, true, true, IR(172, 4), IR(37335, 56), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL, true, true, IR(39, 2), IR(37391, 50), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL, true, true, IR(39, 2), IR(37441, 52), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL, true, true, IR(39, 2), IR(37493, 49), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetMotionVectorCostFunctionINTEL, true, true, IR(215, 6), IR(37542, 47), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL, true, true, IR(172, 4), IR(37589, 50), IR(0, 0), IR(274, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL, true, true, IR(39, 2), IR(37639, 51), IR(0, 0), IR(274, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL, true, true, IR(39, 2), IR(37690, 56), IR(0, 0), IR(276, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetAcOnlyHaarINTEL, true, true, IR(160, 3), IR(37746, 33), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL, true, true, IR(172, 4), IR(37779, 52), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL, true, true, IR(172, 4), IR(37831, 61), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL, true, true, IR(130, 5), IR(37892, 61), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToImePayloadINTEL, true, true, IR(160, 3), IR(37953, 39), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToImeResultINTEL, true, true, IR(160, 3), IR(37992, 38), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToRefPayloadINTEL, true, true, IR(160, 3), IR(38030, 39), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToRefResultINTEL, true, true, IR(160, 3), IR(38069, 38), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToSicPayloadINTEL, true, true, IR(160, 3), IR(38107, 39), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceConvertToSicResultINTEL, true, true, IR(160, 3), IR(38146, 38), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetMotionVectorsINTEL, true, true, IR(160, 3), IR(38184, 36), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterDistortionsINTEL, true, true, IR(160, 3), IR(38220, 39), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetBestInterDistortionsINTEL, true, true, IR(160, 3), IR(38259, 43), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMajorShapeINTEL, true, true, IR(160, 3), IR(38302, 38), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMinorShapeINTEL, true, true, IR(160, 3), IR(38340, 38), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterDirectionsINTEL, true, true, IR(160, 3), IR(38378, 38), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterMotionVectorCountINTEL, true, true, IR(160, 3), IR(38416, 45), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterReferenceIdsINTEL, true, true, IR(160, 3), IR(38461, 40), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL, true, true, IR(130, 5), IR(38501, 62), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeInitializeINTEL, true, true, IR(130, 5), IR(38563, 30), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetSingleReferenceINTEL, true, true, IR(130, 5), IR(38593, 38), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetDualReferenceINTEL, true, true, IR(215, 6), IR(38631, 36), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeRefWindowSizeINTEL, true, true, IR(172, 4), IR(38667, 33), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeAdjustRefOffsetINTEL, true, true, IR(215, 6), IR(38700, 35), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(38735, 39), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetMaxMotionVectorCountINTEL, true, true, IR(172, 4), IR(38774, 43), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetUnidirectionalMixDisableINTEL, true, true, IR(160, 3), IR(38817, 47), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetEarlySearchTerminationThresholdINTEL, true, true, IR(172, 4), IR(38864, 54), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeSetWeightedSadINTEL, true, true, IR(172, 4), IR(38918, 34), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(38952, 47), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(38999, 45), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL, true, true, IR(215, 6), IR(39044, 55), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL, true, true, IR(325, 7), IR(39099, 53), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL, true, true, IR(130, 5), IR(39152, 56), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL, true, true, IR(215, 6), IR(39208, 54), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL, true, true, IR(215, 6), IR(39262, 58), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL, true, true, IR(325, 7), IR(39320, 56), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeConvertToMceResultINTEL, true, true, IR(160, 3), IR(39376, 38), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetSingleReferenceStreaminINTEL, true, true, IR(160, 3), IR(39414, 46), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetDualReferenceStreaminINTEL, true, true, IR(160, 3), IR(39460, 44), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeStripSingleReferenceStreamoutINTEL, true, true, IR(160, 3), IR(39504, 49), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeStripDualReferenceStreamoutINTEL, true, true, IR(160, 3), IR(39553, 47), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL, true, true, IR(172, 4), IR(39600, 70), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL, true, true, IR(172, 4), IR(39670, 68), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL, true, true, IR(172, 4), IR(39738, 69), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL, true, true, IR(130, 5), IR(39807, 68), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL, true, true, IR(130, 5), IR(39875, 66), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL, true, true, IR(130, 5), IR(39941, 67), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetBorderReachedINTEL, true, true, IR(172, 4), IR(40008, 36), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetTruncatedSearchIndicationINTEL, true, true, IR(160, 3), IR(40044, 48), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL, true, true, IR(160, 3), IR(40092, 59), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL, true, true, IR(160, 3), IR(40151, 58), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL, true, true, IR(160, 3), IR(40209, 56), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcFmeInitializeINTEL, true, true, IR(622, 9), IR(40265, 30), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcBmeInitializeINTEL, true, true, IR(631, 10), IR(40295, 30), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(40325, 39), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefSetBidirectionalMixDisableINTEL, true, true, IR(160, 3), IR(40364, 46), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefSetBilinearFilterEnableINTEL, true, true, IR(160, 3), IR(40410, 43), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(40453, 47), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(40500, 45), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithMultiReferenceINTEL, true, true, IR(130, 5), IR(40545, 46), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL, true, true, IR(215, 6), IR(40591, 56), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcRefConvertToMceResultINTEL, true, true, IR(160, 3), IR(40647, 38), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicInitializeINTEL, true, true, IR(160, 3), IR(40685, 30), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureSkcINTEL, true, true, IR(288, 8), IR(40715, 32), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureIpeLumaINTEL, true, true, IR(631, 10), IR(40747, 36), IR(0, 0), IR(274, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConfigureIpeLumaChromaINTEL, true, true, IR(641, 13), IR(40783, 42), IR(0, 0), IR(276, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetMotionVectorMaskINTEL, true, true, IR(172, 4), IR(40825, 39), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConvertToMcePayloadINTEL, true, true, IR(160, 3), IR(40864, 39), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraLumaShapePenaltyINTEL, true, true, IR(172, 4), IR(40903, 44), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraLumaModeCostFunctionINTEL, true, true, IR(215, 6), IR(40947, 48), IR(0, 0), IR(274, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetIntraChromaModeCostFunctionINTEL, true, true, IR(172, 4), IR(40995, 50), IR(0, 0), IR(276, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetBilinearFilterEnableINTEL, true, true, IR(160, 3), IR(41045, 43), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetSkcForwardTransformEnableINTEL, true, true, IR(172, 4), IR(41088, 48), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicSetBlockBasedRawSkipSadINTEL, true, true, IR(172, 4), IR(41136, 43), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateIpeINTEL, true, true, IR(172, 4), IR(41179, 31), IR(0, 0), IR(274, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithSingleReferenceINTEL, true, true, IR(130, 5), IR(41210, 47), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithDualReferenceINTEL, true, true, IR(215, 6), IR(41257, 45), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithMultiReferenceINTEL, true, true, IR(130, 5), IR(41302, 46), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL, true, true, IR(215, 6), IR(41348, 56), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicConvertToMceResultINTEL, true, true, IR(160, 3), IR(41404, 38), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetIpeLumaShapeINTEL, true, true, IR(160, 3), IR(41442, 35), IR(0, 0), IR(274, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetBestIpeLumaDistortionINTEL, true, true, IR(160, 3), IR(41477, 44), IR(0, 0), IR(274, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetBestIpeChromaDistortionINTEL, true, true, IR(160, 3), IR(41521, 46), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedIpeLumaModesINTEL, true, true, IR(160, 3), IR(41567, 41), IR(0, 0), IR(274, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetIpeChromaModeINTEL, true, true, IR(160, 3), IR(41608, 36), IR(0, 0), IR(276, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL, true, true, IR(160, 3), IR(41644, 50), IR(0, 0), IR(274, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL, true, true, IR(160, 3), IR(41694, 48), IR(0, 0), IR(274, 2), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSubgroupAvcSicGetInterRawSadsINTEL, true, true, IR(160, 3), IR(41742, 35), IR(0, 0), IR(273, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpVariableLengthArrayINTEL, true, true, IR(160, 3), IR(12266, 25), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpSaveMemoryINTEL, true, true, IR(39, 2), IR(41777, 16), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpRestoreMemoryINTEL, false, false, IR(10, 1), IR(41793, 19), IR(0, 0), IR(278, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinCosPiINTEL, true, true, IR(654, 8), IR(41812, 28), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastINTEL, true, true, IR(654, 8), IR(41840, 24), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastFromIntINTEL, true, true, IR(654, 8), IR(41864, 31), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCastToIntINTEL, true, true, IR(654, 8), IR(41895, 29), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatAddINTEL, true, true, IR(662, 10), IR(41924, 23), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSubINTEL, true, true, IR(662, 10), IR(41947, 23), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatMulINTEL, true, true, IR(662, 10), IR(41970, 23), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatDivINTEL, true, true, IR(662, 10), IR(41993, 23), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatGTINTEL, true, true, IR(672, 6), IR(42016, 22), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatGEINTEL, true, true, IR(672, 6), IR(42038, 22), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLTINTEL, true, true, IR(672, 6), IR(42060, 22), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLEINTEL, true, true, IR(672, 6), IR(42082, 22), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatEQINTEL, true, true, IR(672, 6), IR(42104, 22), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatRecipINTEL, true, true, IR(654, 8), IR(42126, 25), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatRSqrtINTEL, true, true, IR(654, 8), IR(42151, 25), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCbrtINTEL, true, true, IR(654, 8), IR(42176, 24), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatHypotINTEL, true, true, IR(662, 10), IR(42200, 25), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSqrtINTEL, true, true, IR(654, 8), IR(42225, 24), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLogINTEL, true, true, IR(654, 8), IR(42249, 23), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog2INTEL, true, true, IR(654, 8), IR(42272, 24), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog10INTEL, true, true, IR(654, 8), IR(42296, 25), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatLog1pINTEL, true, true, IR(654, 8), IR(42321, 25), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExpINTEL, true, true, IR(654, 8), IR(42346, 23), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExp2INTEL, true, true, IR(654, 8), IR(42369, 24), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExp10INTEL, true, true, IR(654, 8), IR(42393, 25), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatExpm1INTEL, true, true, IR(654, 8), IR(42418, 25), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinINTEL, true, true, IR(654, 8), IR(42443, 23), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCosINTEL, true, true, IR(654, 8), IR(42466, 23), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinCosINTEL, true, true, IR(654, 8), IR(42489, 26), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatSinPiINTEL, true, true, IR(654, 8), IR(42515, 25), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatCosPiINTEL, true, true, IR(654, 8), IR(42540, 25), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatASinINTEL, true, true, IR(654, 8), IR(42565, 24), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatASinPiINTEL, true, true, IR(654, 8), IR(42589, 26), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatACosINTEL, true, true, IR(654, 8), IR(42615, 24), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatACosPiINTEL, true, true, IR(654, 8), IR(42639, 26), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATanINTEL, true, true, IR(654, 8), IR(42665, 24), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATanPiINTEL, true, true, IR(654, 8), IR(42689, 26), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatATan2INTEL, true, true, IR(662, 10), IR(42715, 25), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowINTEL, true, true, IR(662, 10), IR(42740, 23), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowRINTEL, true, true, IR(662, 10), IR(42763, 24), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpArbitraryFloatPowNINTEL, true, true, IR(662, 10), IR(42787, 24), IR(0, 0), IR(279, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpLoopControlINTEL, false, false, IR(18, 1), IR(42811, 17), IR(0, 0), IR(280, 1), IR(103, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAliasDomainDeclINTEL, true, false, IR(678, 2), IR(42828, 21), IR(0, 0), IR(129, 1), IR(110, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAliasScopeDeclINTEL, true, false, IR(680, 3), IR(42849, 20), IR(0, 0), IR(129, 1), IR(110, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpAliasScopeListDeclINTEL, true, false, IR(92, 2), IR(42869, 24), IR(0, 0), IR(129, 1), IR(110, 1), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSqrtINTEL, true, true, IR(654, 8), IR(42893, 15), IR(0, 0), IR(183, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedRecipINTEL, true, true, IR(654, 8), IR(42908, 16), IR(0, 0), IR(183, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedRsqrtINTEL, true, true, IR(654, 8), IR(42924, 16), IR(0, 0), IR(183, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinINTEL, true, true, IR(654, 8), IR(42940, 14), IR(0, 0), IR(183, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedCosINTEL, true, true, IR(654, 8), IR(42954, 14), IR(0, 0), IR(183, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinCosINTEL, true, true, IR(654, 8), IR(42968, 17), IR(0, 0), IR(183, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinPiINTEL, true, true, IR(654, 8), IR(42985, 16), IR(0, 0), IR(183, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedCosPiINTEL, true, true, IR(654, 8), IR(43001, 16), IR(0, 0), IR(183, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedSinCosPiINTEL, true, true, IR(654, 8), IR(43017, 19), IR(0, 0), IR(183, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedLogINTEL, true, true, IR(654, 8), IR(43036, 14), IR(0, 0), IR(183, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpFixedExpINTEL, true, true, IR(654, 8), IR(43050, 14), IR(0, 0), IR(183, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpPtrCastToCrossWorkgroupINTEL, true, true, IR(160, 3), IR(43064, 29), IR(0, 0), IR(194, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpCrossWorkgroupCastToPtrINTEL, true, true, IR(160, 3), IR(43093, 29), IR(0, 0), IR(194, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::k_exclude},
  {spv::Op::OpReadPipeBlockingINTEL, true, true, IR(172, 4), IR(43122, 22), IR(0, 0), IR(281, 1), IR(117, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpWritePipeBlockingINTEL, true, true, IR(172, 4), IR(43144, 23), IR(0, 0), IR(281, 1), IR(117, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kPipe},
  {spv::Op::OpFPGARegINTEL, true, true, IR(160, 3), IR(12825, 13), IR(0, 0), IR(282, 1), IR(118, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetRayTMinKHR, true, true, IR(160, 3), IR(43167, 22), IR(0, 0), IR(187, 1), IR(46, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetRayFlagsKHR, true, true, IR(160, 3), IR(43189, 23), IR(0, 0), IR(187, 1), IR(46, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionTKHR, true, true, IR(172, 4), IR(43212, 28), IR(0, 0), IR(187, 1), IR(46, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceCustomIndexKHR, true, true, IR(172, 4), IR(43240, 46), IR(0, 0), IR(187, 1), IR(46, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceIdKHR, true, true, IR(172, 4), IR(43286, 37), IR(0, 0), IR(187, 1), IR(46, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR, true, true, IR(172, 4), IR(43323, 65), IR(0, 0), IR(187, 1), IR(46, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionGeometryIndexKHR, true, true, IR(172, 4), IR(43388, 40), IR(0, 0), IR(187, 1), IR(46, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionPrimitiveIndexKHR, true, true, IR(172, 4), IR(43428, 41), IR(0, 0), IR(187, 1), IR(46, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionBarycentricsKHR, true, true, IR(172, 4), IR(43469, 39), IR(0, 0), IR(187, 1), IR(46, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionFrontFaceKHR, true, true, IR(172, 4), IR(43508, 36), IR(0, 0), IR(187, 1), IR(46, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionCandidateAABBOpaqueKHR, true, true, IR(160, 3), IR(43544, 46), IR(0, 0), IR(187, 1), IR(46, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectRayDirectionKHR, true, true, IR(172, 4), IR(43590, 45), IR(0, 0), IR(187, 1), IR(46, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectRayOriginKHR, true, true, IR(172, 4), IR(43635, 42), IR(0, 0), IR(187, 1), IR(46, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetWorldRayDirectionKHR, true, true, IR(160, 3), IR(43677, 32), IR(0, 0), IR(187, 1), IR(46, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetWorldRayOriginKHR, true, true, IR(160, 3), IR(43709, 29), IR(0, 0), IR(187, 1), IR(46, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionObjectToWorldKHR, true, true, IR(172, 4), IR(43738, 40), IR(0, 0), IR(187, 1), IR(46, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpRayQueryGetIntersectionWorldToObjectKHR, true, true, IR(172, 4), IR(43778, 40), IR(0, 0), IR(187, 1), IR(46, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpAtomicFAddEXT, true, true, IR(235, 6), IR(43818, 14), IR(0, 0), IR(283, 4), IR(125, 1), 0xffffffffu, 0xffffffffu, PrintingClass::kAtomic},
  {spv::Op::OpTypeBufferSurfaceINTEL, true, false, IR(100, 2), IR(43832, 23), IR(0, 0), IR(121, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpTypeStructContinuedINTEL, false, false, IR(683, 1), IR(43855, 25), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpConstantCompositeContinuedINTEL, false, false, IR(683, 1), IR(43880, 32), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpSpecConstantCompositeContinuedINTEL, false, false, IR(683, 1), IR(43912, 36), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConstant_Creation},
  {spv::Op::OpCompositeConstructContinuedINTEL, true, true, IR(107, 3), IR(43948, 33), IR(0, 0), IR(287, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kComposite},
  {spv::Op::OpConvertFToBF16INTEL, true, true, IR(160, 3), IR(43981, 20), IR(0, 0), IR(288, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpConvertBF16ToFINTEL, true, true, IR(160, 3), IR(44001, 20), IR(0, 0), IR(288, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpControlBarrierArriveINTEL, false, false, IR(221, 3), IR(44021, 26), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpControlBarrierWaitINTEL, false, false, IR(221, 3), IR(44047, 24), IR(0, 0), IR(289, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBarrier},
  {spv::Op::OpArithmeticFenceEXT, true, true, IR(160, 3), IR(13257, 19), IR(0, 0), IR(290, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMiscellaneous},
  {spv::Op::OpTaskSequenceCreateINTEL, true, true, IR(684, 7), IR(44071, 24), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTaskSequenceAsyncINTEL, false, false, IR(168, 2), IR(44095, 23), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTaskSequenceGetINTEL, true, true, IR(160, 3), IR(44118, 21), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTaskSequenceReleaseINTEL, false, false, IR(10, 1), IR(44139, 25), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kReserved},
  {spv::Op::OpTypeTaskSequenceINTEL, true, false, IR(68, 1), IR(44164, 22), IR(0, 0), IR(291, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kType_Declaration},
  {spv::Op::OpSubgroupBlockPrefetchINTEL, false, false, IR(139, 3), IR(44186, 27), IR(0, 0), IR(292, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadINTEL, false, false, IR(691, 10), IR(44213, 25), IR(0, 0), IR(105, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadTransformINTEL, false, false, IR(691, 10), IR(44238, 34), IR(0, 0), IR(293, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockLoadTransposeINTEL, false, false, IR(691, 10), IR(44272, 34), IR(0, 0), IR(294, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockPrefetchINTEL, false, false, IR(701, 9), IR(44306, 29), IR(0, 0), IR(105, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroup2DBlockStoreINTEL, false, false, IR(691, 10), IR(44335, 26), IR(0, 0), IR(105, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpSubgroupMatrixMultiplyAccumulateINTEL, true, true, IR(710, 7), IR(13595, 38), IR(0, 0), IR(295, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpBitwiseFunctionINTEL, true, true, IR(215, 6), IR(44423, 21), IR(0, 0), IR(296, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kBit},
  {spv::Op::OpGroupIMulKHR, true, true, IR(283, 5), IR(44444, 13), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupFMulKHR, true, true, IR(283, 5), IR(44457, 13), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseAndKHR, true, true, IR(283, 5), IR(44470, 19), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseOrKHR, true, true, IR(283, 5), IR(44489, 18), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupBitwiseXorKHR, true, true, IR(283, 5), IR(44507, 19), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalAndKHR, true, true, IR(283, 5), IR(44526, 19), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalOrKHR, true, true, IR(283, 5), IR(44545, 18), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpGroupLogicalXorKHR, true, true, IR(283, 5), IR(44563, 19), IR(0, 0), IR(297, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kGroup},
  {spv::Op::OpRoundFToTF32INTEL, true, true, IR(160, 3), IR(44582, 18), IR(0, 0), IR(298, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kConversion},
  {spv::Op::OpMaskedGatherINTEL, true, true, IR(717, 6), IR(44600, 18), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
  {spv::Op::OpMaskedScatterINTEL, false, false, IR(723, 4), IR(44618, 19), IR(0, 0), IR(299, 1), IR(0, 0), 0xffffffffu, 0xffffffffu, PrintingClass::kMemory},
}};

// Opcode strings (without the 'Op' prefix) and opcode values, ordered by name.
// The fields in order are:
//   name, either the primary name or an alias, indexing into kStrings
//   index into kInstructionDesc
static const std::array<NameIndex, 809> kInstructionNames{{
  {IR(36215, 13), 541}, // 0 AbsISubINTEL
  {IR(36228, 13), 542}, // 1 AbsUSubINTEL
  {IR(26283, 12), 58}, // 2 AccessChain
  {IR(42828, 21), 727}, // 3 AliasDomainDeclINTEL
  {IR(42849, 20), 728}, // 4 AliasScopeDeclINTEL
  {IR(42869, 24), 729}, // 5 AliasScopeListDeclINTEL
  {IR(27580, 4), 143}, // 6 All
  {IR(32739, 25), 413}, // 7 AllocateNodePayloadsAMDX
  {IR(27576, 4), 142}, // 8 Any
  {IR(42615, 24), 718}, // 9 ArbitraryFloatACosINTEL
  {IR(42639, 26), 719}, // 10 ArbitraryFloatACosPiINTEL
  {IR(42565, 24), 716}, // 11 ArbitraryFloatASinINTEL
  {IR(42589, 26), 717}, // 12 ArbitraryFloatASinPiINTEL
  {IR(42715, 25), 722}, // 13 ArbitraryFloatATan2INTEL
  {IR(42665, 24), 720}, // 14 ArbitraryFloatATanINTEL
  {IR(42689, 26), 721}, // 15 ArbitraryFloatATanPiINTEL
  {IR(41924, 23), 689}, // 16 ArbitraryFloatAddINTEL
  {IR(41864, 31), 687}, // 17 ArbitraryFloatCastFromIntINTEL
  {IR(41840, 24), 686}, // 18 ArbitraryFloatCastINTEL
  {IR(41895, 29), 688}, // 19 ArbitraryFloatCastToIntINTEL
  {IR(42176, 24), 700}, // 20 ArbitraryFloatCbrtINTEL
  {IR(42466, 23), 712}, // 21 ArbitraryFloatCosINTEL
  {IR(42540, 25), 715}, // 22 ArbitraryFloatCosPiINTEL
  {IR(41993, 23), 692}, // 23 ArbitraryFloatDivINTEL
  {IR(42104, 22), 697}, // 24 ArbitraryFloatEQINTEL
  {IR(42393, 25), 709}, // 25 ArbitraryFloatExp10INTEL
  {IR(42369, 24), 708}, // 26 ArbitraryFloatExp2INTEL
  {IR(42346, 23), 707}, // 27 ArbitraryFloatExpINTEL
  {IR(42418, 25), 710}, // 28 ArbitraryFloatExpm1INTEL
  {IR(42038, 22), 694}, // 29 ArbitraryFloatGEINTEL
  {IR(42016, 22), 693}, // 30 ArbitraryFloatGTINTEL
  {IR(42200, 25), 701}, // 31 ArbitraryFloatHypotINTEL
  {IR(42082, 22), 696}, // 32 ArbitraryFloatLEINTEL
  {IR(42060, 22), 695}, // 33 ArbitraryFloatLTINTEL
  {IR(42296, 25), 705}, // 34 ArbitraryFloatLog10INTEL
  {IR(42321, 25), 706}, // 35 ArbitraryFloatLog1pINTEL
  {IR(42272, 24), 704}, // 36 ArbitraryFloatLog2INTEL
  {IR(42249, 23), 703}, // 37 ArbitraryFloatLogINTEL
  {IR(41970, 23), 691}, // 38 ArbitraryFloatMulINTEL
  {IR(42740, 23), 723}, // 39 ArbitraryFloatPowINTEL
  {IR(42787, 24), 725}, // 40 ArbitraryFloatPowNINTEL
  {IR(42763, 24), 724}, // 41 ArbitraryFloatPowRINTEL
  {IR(42151, 25), 699}, // 42 ArbitraryFloatRSqrtINTEL
  {IR(42126, 25), 698}, // 43 ArbitraryFloatRecipINTEL
  {IR(42489, 26), 713}, // 44 ArbitraryFloatSinCosINTEL
  {IR(41812, 28), 685}, // 45 ArbitraryFloatSinCosPiINTEL
  {IR(42443, 23), 711}, // 46 ArbitraryFloatSinINTEL
  {IR(42515, 25), 714}, // 47 ArbitraryFloatSinPiINTEL
  {IR(42225, 24), 702}, // 48 ArbitraryFloatSqrtINTEL
  {IR(41947, 23), 690}, // 49 ArbitraryFloatSubINTEL
  {IR(13257, 19), 773}, // 50 ArithmeticFenceEXT
  {IR(26330, 12), 61}, // 51 ArrayLength
  {IR(36462, 13), 557}, // 52 AsmCallINTEL
  {IR(12028, 9), 556}, // 53 AsmINTEL
  {IR(36447, 15), 555}, // 54 AsmTargetINTEL
  {IR(36503, 14), 560}, // 55 AssumeTrueKHR
  {IR(28602, 10), 220}, // 56 AtomicAnd
  {IR(28454, 22), 210}, // 57 AtomicCompareExchange
  {IR(28476, 26), 211}, // 58 AtomicCompareExchangeWeak
  {IR(28439, 15), 209}, // 59 AtomicExchange
  {IR(43818, 14), 763}, // 60 AtomicFAddEXT
  {IR(36489, 14), 559}, // 61 AtomicFMaxEXT
  {IR(36475, 14), 558}, // 62 AtomicFMinEXT
  {IR(29987, 16), 292}, // 63 AtomicFlagClear
  {IR(29966, 21), 291}, // 64 AtomicFlagTestAndSet
  {IR(28536, 11), 214}, // 65 AtomicIAdd
  {IR(28519, 17), 213}, // 66 AtomicIDecrement
  {IR(28502, 17), 212}, // 67 AtomicIIncrement
  {IR(28547, 11), 215}, // 68 AtomicISub
  {IR(28416, 11), 207}, // 69 AtomicLoad
  {IR(28612, 9), 221}, // 70 AtomicOr
  {IR(28580, 11), 218}, // 71 AtomicSMax
  {IR(28558, 11), 216}, // 72 AtomicSMin
  {IR(28427, 12), 208}, // 73 AtomicStore
  {IR(28591, 11), 219}, // 74 AtomicUMax
  {IR(28569, 11), 217}, // 75 AtomicUMin
  {IR(28621, 10), 222}, // 76 AtomicXor
  {IR(34711, 28), 487}, // 77 BeginInvocationInterlockEXT
  {IR(28200, 9), 191}, // 78 BitCount
  {IR(28140, 15), 187}, // 79 BitFieldInsert
  {IR(28155, 17), 188}, // 80 BitFieldSExtract
  {IR(28172, 17), 189}, // 81 BitFieldUExtract
  {IR(28189, 11), 190}, // 82 BitReverse
  {IR(27328, 8), 114}, // 83 Bitcast
  {IR(28125, 11), 185}, // 84 BitwiseAnd
  {IR(44423, 21), 786}, // 85 BitwiseFunctionINTEL
  {IR(28104, 10), 183}, // 86 BitwiseOr
  {IR(28114, 11), 184}, // 87 BitwiseXor
  {IR(28731, 7), 227}, // 88 Branch
  {IR(28738, 18), 228}, // 89 BranchConditional
  {IR(29599, 13), 277}, // 90 BuildNDRange
  {IR(25344, 11), 15}, // 91 Capability
  {IR(29557, 26), 275}, // 92 CaptureEventProfilingInfo
  {IR(31063, 23), 344}, // 93 ColorAttachmentReadEXT
  {IR(29149, 15), 255}, // 94 CommitReadPipe
  {IR(29164, 16), 256}, // 95 CommitWritePipe
  {IR(26590, 19), 72}, // 96 CompositeConstruct
  {IR(43948, 33), 768}, // 97 CompositeConstructContinuedINTEL
  {IR(32096, 31), 386}, // 98 CompositeConstructReplicateEXT
  {IR(26609, 17), 73}, // 99 CompositeExtract
  {IR(26626, 16), 74}, // 100 CompositeInsert
  {IR(15156, 9), 39}, // 101 Constant
  {IR(25850, 18), 40}, // 102 ConstantComposite
  {IR(43880, 32), 766}, // 103 ConstantCompositeContinuedINTEL
  {IR(32032, 30), 384}, // 104 ConstantCompositeReplicateEXT
  {IR(25798, 14), 38}, // 105 ConstantFalse
  {IR(36393, 29), 553}, // 106 ConstantFunctionPointerINTEL
  {IR(25962, 13), 42}, // 107 ConstantNull
  {IR(30042, 20), 296}, // 108 ConstantPipeStorage
  {IR(25946, 16), 41}, // 109 ConstantSampler
  {IR(32892, 19), 419}, // 110 ConstantStringAMDX
  {IR(25785, 13), 37}, // 111 ConstantTrue
  {IR(28387, 15), 205}, // 112 ControlBarrier
  {IR(44021, 26), 771}, // 113 ControlBarrierArriveINTEL
  {IR(44047, 24), 772}, // 114 ControlBarrierWaitINTEL
  {IR(44001, 20), 770}, // 115 ConvertBF16ToFINTEL
  {IR(43981, 20), 769}, // 116 ConvertFToBF16INTEL
  {IR(27134, 12), 100}, // 117 ConvertFToS
  {IR(27122, 12), 99}, // 118 ConvertFToU
  {IR(35360, 18), 510}, // 119 ConvertImageToUNV
  {IR(27211, 14), 107}, // 120 ConvertPtrToU
  {IR(27146, 12), 101}, // 121 ConvertSToF
  {IR(35423, 25), 513}, // 122 ConvertSampledImageToUNV
  {IR(35378, 20), 511}, // 123 ConvertSamplerToUNV
  {IR(31610, 35), 370}, // 124 ConvertUToAccelerationStructureKHR
  {IR(27158, 12), 102}, // 125 ConvertUToF
  {IR(35322, 18), 508}, // 126 ConvertUToImageNV
  {IR(27255, 14), 110}, // 127 ConvertUToPtr
  {IR(35398, 25), 512}, // 128 ConvertUToSampledImageNV
  {IR(35340, 20), 509}, // 129 ConvertUToSamplerNV
  {IR(34052, 27), 462}, // 130 CooperativeMatrixConvertNV
  {IR(32005, 27), 383}, // 131 CooperativeMatrixLengthKHR
  {IR(34685, 26), 486}, // 132 CooperativeMatrixLengthNV
  {IR(31873, 25), 380}, // 133 CooperativeMatrixLoadKHR
  {IR(34610, 24), 483}, // 134 CooperativeMatrixLoadNV
  {IR(34909, 30), 490}, // 135 CooperativeMatrixLoadTensorNV
  {IR(31978, 27), 382}, // 136 CooperativeMatrixMulAddKHR
  {IR(34659, 26), 485}, // 137 CooperativeMatrixMulAddNV
  {IR(34970, 32), 492}, // 138 CooperativeMatrixPerElementOpNV
  {IR(34808, 26), 489}, // 139 CooperativeMatrixReduceNV
  {IR(31898, 26), 381}, // 140 CooperativeMatrixStoreKHR
  {IR(34634, 25), 484}, // 141 CooperativeMatrixStoreNV
  {IR(34939, 31), 491}, // 142 CooperativeMatrixStoreTensorNV
  {IR(35293, 29), 507}, // 143 CooperativeMatrixTransposeNV
  {IR(34247, 24), 469}, // 144 CooperativeVectorLoadNV
  {IR(34020, 32), 461}, // 145 CooperativeVectorMatrixMulAddNV
  {IR(33910, 29), 458}, // 146 CooperativeVectorMatrixMulNV
  {IR(33939, 42), 459}, // 147 CooperativeVectorOuterProductAccumulateNV
  {IR(33981, 39), 460}, // 148 CooperativeVectorReduceSumAccumulateNV
  {IR(34271, 25), 470}, // 149 CooperativeVectorStoreNV
  {IR(31022, 12), 340}, // 150 CopyLogical
  {IR(26256, 11), 56}, // 151 CopyMemory
  {IR(26267, 16), 57}, // 152 CopyMemorySized
  {IR(26642, 11), 75}, // 153 CopyObject
  {IR(30062, 26), 297}, // 154 CreatePipeFromPipeStorage
  {IR(35038, 21), 495}, // 155 CreateTensorLayoutNV
  {IR(35158, 19), 500}, // 156 CreateTensorViewNV
  {IR(29509, 16), 272}, // 157 CreateUserEvent
  {IR(43093, 29), 742}, // 158 CrossWorkgroupCastToPtrINTEL
  {IR(28209, 5), 192}, // 159 DPdx
  {IR(28255, 11), 198}, // 160 DPdxCoarse
  {IR(28226, 9), 195}, // 161 DPdxFine
  {IR(28214, 5), 193}, // 162 DPdy
  {IR(28266, 11), 199}, // 163 DPdyCoarse
  {IR(28235, 9), 196}, // 164 DPdyFine
  {IR(26416, 9), 64}, // 165 Decorate
  {IR(30239, 11), 305}, // 166 DecorateId
  {IR(36527, 15), 562}, // 167 DecorateString
  {IR(36542, 21), 562}, // 168 DecorateStringGOOGLE
  {IR(26440, 16), 66}, // 169 DecorationGroup
  {IR(11362, 25), 503}, // 170 DemoteToHelperInvocation
  {IR(11387, 28), 503}, // 171 DemoteToHelperInvocationEXT
  {IR(31086, 23), 345}, // 172 DepthAttachmentReadEXT
  {IR(27525, 4), 137}, // 173 Dot
  {IR(34079, 17), 463}, // 174 EmitMeshTasksEXT
  {IR(28314, 17), 203}, // 175 EmitStreamVertex
  {IR(28290, 11), 201}, // 176 EmitVertex
  {IR(34739, 26), 488}, // 177 EndInvocationInterlockEXT
  {IR(28301, 13), 202}, // 178 EndPrimitive
  {IR(28331, 19), 204}, // 179 EndStreamPrimitive
  {IR(29345, 14), 265}, // 180 EnqueueKernel
  {IR(29331, 14), 264}, // 181 EnqueueMarker
  {IR(32764, 24), 414}, // 182 EnqueueNodePayloadsAMDX
  {IR(25259, 11), 13}, // 183 EntryPoint
  {IR(31591, 19), 369}, // 184 ExecuteCallableKHR
  {IR(34521, 18), 479}, // 185 ExecuteCallableNV
  {IR(25302, 14), 14}, // 186 ExecutionMode
  {IR(30223, 16), 304}, // 187 ExecutionModeId
  {IR(36517, 10), 561}, // 188 ExpectKHR
  {IR(25113, 8), 11}, // 189 ExtInst
  {IR(25053, 14), 10}, // 190 ExtInstImport
  {IR(31553, 26), 367}, // 191 ExtInstWithForwardRefsKHR
  {IR(25043, 10), 9}, // 192 Extension
  {IR(27357, 5), 118}, // 193 FAdd
  {IR(27188, 9), 105}, // 194 FConvert
  {IR(27392, 5), 125}, // 195 FDiv
  {IR(27417, 5), 130}, // 196 FMod
  {IR(27377, 5), 122}, // 197 FMul
  {IR(27344, 8), 116}, // 198 FNegate
  {IR(27854, 10), 168}, // 199 FOrdEqual
  {IR(27932, 16), 174}, // 200 FOrdGreaterThan
  {IR(28004, 21), 178}, // 201 FOrdGreaterThanEqual
  {IR(27904, 13), 172}, // 202 FOrdLessThan
  {IR(27966, 18), 176}, // 203 FOrdLessThanEqual
  {IR(27876, 13), 170}, // 204 FOrdNotEqual
  {IR(12825, 13), 745}, // 205 FPGARegINTEL
  {IR(27412, 5), 129}, // 206 FRem
  {IR(27367, 5), 120}, // 207 FSub
  {IR(27864, 12), 169}, // 208 FUnordEqual
  {IR(27948, 18), 175}, // 209 FUnordGreaterThan
  {IR(28025, 23), 179}, // 210 FUnordGreaterThanEqual
  {IR(27917, 15), 173}, // 211 FUnordLessThan
  {IR(27984, 20), 177}, // 212 FUnordLessThanEqual
  {IR(27889, 15), 171}, // 213 FUnordNotEqual
  {IR(34209, 38), 468}, // 214 FetchMicroTriangleVertexBarycentricNV
  {IR(34174, 35), 467}, // 215 FetchMicroTriangleVertexPositionNV
  {IR(32813, 29), 416}, // 216 FinishWritingNodePayloadAMDX
  {IR(42954, 14), 734}, // 217 FixedCosINTEL
  {IR(43001, 16), 737}, // 218 FixedCosPiINTEL
  {IR(43050, 14), 740}, // 219 FixedExpINTEL
  {IR(43036, 14), 739}, // 220 FixedLogINTEL
  {IR(42908, 16), 731}, // 221 FixedRecipINTEL
  {IR(42924, 16), 732}, // 222 FixedRsqrtINTEL
  {IR(42968, 17), 735}, // 223 FixedSinCosINTEL
  {IR(43017, 19), 738}, // 224 FixedSinCosPiINTEL
  {IR(42940, 14), 733}, // 225 FixedSinINTEL
  {IR(42985, 16), 736}, // 226 FixedSinPiINTEL
  {IR(42893, 15), 730}, // 227 FixedSqrtINTEL
  {IR(32709, 17), 411}, // 228 FragmentFetchAMD
  {IR(32688, 21), 410}, // 229 FragmentMaskFetchAMD
  {IR(24163, 9), 48}, // 230 Function
  {IR(26165, 13), 51}, // 231 FunctionCall
  {IR(26153, 12), 50}, // 232 FunctionEnd
  {IR(26135, 18), 49}, // 233 FunctionParameter
  {IR(36422, 25), 554}, // 234 FunctionPointerCallINTEL
  {IR(28219, 7), 194}, // 235 Fwidth
  {IR(28277, 13), 200}, // 236 FwidthCoarse
  {IR(28244, 11), 197}, // 237 FwidthFine
  {IR(27286, 17), 112}, // 238 GenericCastToPtr
  {IR(27303, 25), 113}, // 239 GenericCastToPtrExplicit
  {IR(26342, 23), 62}, // 240 GenericPtrMemSemantics
  {IR(29583, 16), 276}, // 241 GetDefaultQueue
  {IR(30088, 35), 298}, // 242 GetKernelLocalSizeForSubgroupCount
  {IR(30123, 25), 299}, // 243 GetKernelMaxNumSubgroups
  {IR(29389, 32), 267}, // 244 GetKernelNDrangeMaxSubGroupSize
  {IR(29359, 30), 266}, // 245 GetKernelNDrangeSubGroupCount
  {IR(29444, 40), 269}, // 246 GetKernelPreferredWorkGroupSizeMultiple
  {IR(29421, 23), 268}, // 247 GetKernelWorkGroupSize
  {IR(29215, 18), 259}, // 248 GetMaxPipePackets
  {IR(29197, 18), 258}, // 249 GetNumPipePackets
  {IR(28902, 9), 238}, // 250 GroupAll
  {IR(28911, 9), 239}, // 251 GroupAny
  {IR(28871, 15), 236}, // 252 GroupAsyncCopy
  {IR(44470, 19), 789}, // 253 GroupBitwiseAndKHR
  {IR(44489, 18), 790}, // 254 GroupBitwiseOrKHR
  {IR(44507, 19), 791}, // 255 GroupBitwiseXorKHR
  {IR(28920, 15), 240}, // 256 GroupBroadcast
  {IR(29290, 20), 262}, // 257 GroupCommitReadPipe
  {IR(29310, 21), 263}, // 258 GroupCommitWritePipe
  {IR(26456, 14), 67}, // 259 GroupDecorate
  {IR(28978, 10), 242}, // 260 GroupFAdd
  {IR(32527, 23), 403}, // 261 GroupFAddNonUniformAMD
  {IR(29018, 10), 246}, // 262 GroupFMax
  {IR(32619, 23), 407}, // 263 GroupFMaxNonUniformAMD
  {IR(28988, 10), 243}, // 264 GroupFMin
  {IR(32550, 23), 404}, // 265 GroupFMinNonUniformAMD
  {IR(44457, 13), 788}, // 266 GroupFMulKHR
  {IR(28968, 10), 241}, // 267 GroupIAdd
  {IR(32504, 23), 402}, // 268 GroupIAddNonUniformAMD
  {IR(44444, 13), 787}, // 269 GroupIMulKHR
  {IR(44526, 19), 792}, // 270 GroupLogicalAndKHR
  {IR(44545, 18), 793}, // 271 GroupLogicalOrKHR
  {IR(44563, 19), 794}, // 272 GroupLogicalXorKHR
  {IR(26515, 20), 68}, // 273 GroupMemberDecorate
  {IR(30271, 19), 307}, // 274 GroupNonUniformAll
  {IR(30309, 24), 309}, // 275 GroupNonUniformAllEqual
  {IR(30290, 19), 308}, // 276 GroupNonUniformAny
  {IR(5528, 22), 312}, // 277 GroupNonUniformBallot
  {IR(30449, 30), 315}, // 278 GroupNonUniformBallotBitCount
  {IR(30417, 32), 314}, // 279 GroupNonUniformBallotBitExtract
  {IR(30479, 29), 316}, // 280 GroupNonUniformBallotFindLSB
  {IR(30508, 29), 317}, // 281 GroupNonUniformBallotFindMSB
  {IR(30815, 26), 332}, // 282 GroupNonUniformBitwiseAnd
  {IR(30841, 25), 333}, // 283 GroupNonUniformBitwiseOr
  {IR(30866, 26), 334}, // 284 GroupNonUniformBitwiseXor
  {IR(30333, 25), 310}, // 285 GroupNonUniformBroadcast
  {IR(30358, 30), 311}, // 286 GroupNonUniformBroadcastFirst
  {IR(30250, 21), 306}, // 287 GroupNonUniformElect
  {IR(30635, 20), 323}, // 288 GroupNonUniformFAdd
  {IR(30795, 20), 331}, // 289 GroupNonUniformFMax
  {IR(30735, 20), 328}, // 290 GroupNonUniformFMin
  {IR(30675, 20), 325}, // 291 GroupNonUniformFMul
  {IR(30615, 20), 322}, // 292 GroupNonUniformIAdd
  {IR(30655, 20), 324}, // 293 GroupNonUniformIMul
  {IR(30388, 29), 313}, // 294 GroupNonUniformInverseBallot
  {IR(30892, 26), 335}, // 295 GroupNonUniformLogicalAnd
  {IR(30918, 25), 336}, // 296 GroupNonUniformLogicalOr
  {IR(30943, 26), 337}, // 297 GroupNonUniformLogicalXor
  {IR(34114, 27), 465}, // 298 GroupNonUniformPartitionNV
  {IR(32934, 26), 421}, // 299 GroupNonUniformQuadAllKHR
  {IR(32960, 26), 422}, // 300 GroupNonUniformQuadAnyKHR
  {IR(30969, 29), 338}, // 301 GroupNonUniformQuadBroadcast
  {IR(30998, 24), 339}, // 302 GroupNonUniformQuadSwap
  {IR(13050, 25), 365}, // 303 GroupNonUniformRotateKHR
  {IR(30755, 20), 329}, // 304 GroupNonUniformSMax
  {IR(30695, 20), 326}, // 305 GroupNonUniformSMin
  {IR(8618, 23), 318}, // 306 GroupNonUniformShuffle
  {IR(30588, 27), 321}, // 307 GroupNonUniformShuffleDown
  {IR(30563, 25), 320}, // 308 GroupNonUniformShuffleUp
  {IR(30537, 26), 319}, // 309 GroupNonUniformShuffleXor
  {IR(30775, 20), 330}, // 310 GroupNonUniformUMax
  {IR(30715, 20), 327}, // 311 GroupNonUniformUMin
  {IR(29233, 28), 260}, // 312 GroupReserveReadPipePackets
  {IR(29261, 29), 261}, // 313 GroupReserveWritePipePackets
  {IR(29038, 10), 248}, // 314 GroupSMax
  {IR(32665, 23), 409}, // 315 GroupSMaxNonUniformAMD
  {IR(29008, 10), 245}, // 316 GroupSMin
  {IR(32596, 23), 406}, // 317 GroupSMinNonUniformAMD
  {IR(29028, 10), 247}, // 318 GroupUMax
  {IR(32642, 23), 408}, // 319 GroupUMaxNonUniformAMD
  {IR(28998, 10), 244}, // 320 GroupUMin
  {IR(32573, 23), 405}, // 321 GroupUMinNonUniformAMD
  {IR(28886, 16), 237}, // 322 GroupWaitEvents
  {IR(33421, 25), 438}, // 323 HitObjectExecuteShaderNV
  {IR(33472, 25), 440}, // 324 HitObjectGetAttributesNV
  {IR(34562, 24), 481}, // 325 HitObjectGetClusterIdNV
  {IR(33446, 26), 439}, // 326 HitObjectGetCurrentTimeNV
  {IR(33548, 28), 443}, // 327 HitObjectGetGeometryIndexNV
  {IR(33497, 22), 441}, // 328 HitObjectGetHitKindNV
  {IR(33601, 34), 445}, // 329 HitObjectGetInstanceCustomIndexNV
  {IR(33576, 25), 444}, // 330 HitObjectGetInstanceIdNV
  {IR(35789, 27), 523}, // 331 HitObjectGetLSSPositionsNV
  {IR(35816, 23), 524}, // 332 HitObjectGetLSSRadiiNV
  {IR(33133, 33), 428}, // 333 HitObjectGetObjectRayDirectionNV
  {IR(33166, 30), 429}, // 334 HitObjectGetObjectRayOriginNV
  {IR(33105, 28), 427}, // 335 HitObjectGetObjectToWorldNV
  {IR(33519, 29), 442}, // 336 HitObjectGetPrimitiveIndexNV
  {IR(33696, 22), 448}, // 337 HitObjectGetRayTMaxNV
  {IR(33718, 22), 449}, // 338 HitObjectGetRayTMinNV
  {IR(33261, 44), 432}, // 339 HitObjectGetShaderBindingTableRecordIndexNV
  {IR(33222, 39), 431}, // 340 HitObjectGetShaderRecordBufferHandleNV
  {IR(35733, 29), 521}, // 341 HitObjectGetSpherePositionNV
  {IR(35762, 27), 522}, // 342 HitObjectGetSphereRadiusNV
  {IR(33635, 32), 446}, // 343 HitObjectGetWorldRayDirectionNV
  {IR(33667, 29), 447}, // 344 HitObjectGetWorldRayOriginNV
  {IR(33077, 28), 426}, // 345 HitObjectGetWorldToObjectNV
  {IR(33740, 19), 450}, // 346 HitObjectIsEmptyNV
  {IR(33759, 17), 451}, // 347 HitObjectIsHitNV
  {IR(35862, 20), 526}, // 348 HitObjectIsLSSHitNV
  {IR(33776, 18), 452}, // 349 HitObjectIsMissNV
  {IR(35839, 23), 525}, // 350 HitObjectIsSphereHitNV
  {IR(33305, 23), 433}, // 351 HitObjectRecordEmptyNV
  {IR(32986, 27), 423}, // 352 HitObjectRecordHitMotionNV
  {IR(33348, 21), 435}, // 353 HitObjectRecordHitNV
  {IR(33013, 36), 424}, // 354 HitObjectRecordHitWithIndexMotionNV
  {IR(33369, 30), 436}, // 355 HitObjectRecordHitWithIndexNV
  {IR(33049, 28), 425}, // 356 HitObjectRecordMissMotionNV
  {IR(33399, 22), 437}, // 357 HitObjectRecordMissNV
  {IR(33196, 26), 430}, // 358 HitObjectTraceRayMotionNV
  {IR(33328, 20), 434}, // 359 HitObjectTraceRayNV
  {IR(27352, 5), 117}, // 360 IAdd
  {IR(27529, 10), 138}, // 361 IAddCarry
  {IR(36241, 13), 543}, // 362 IAddSatINTEL
  {IR(36267, 14), 545}, // 363 IAverageINTEL
  {IR(36295, 21), 547}, // 364 IAverageRoundedINTEL
  {IR(27725, 7), 158}, // 365 IEqual
  {IR(27372, 5), 121}, // 366 IMul
  {IR(36363, 15), 551}, // 367 IMul32x16INTEL
  {IR(27732, 10), 159}, // 368 INotEqual
  {IR(27362, 5), 119}, // 369 ISub
  {IR(27539, 11), 139}, // 370 ISubBorrow
  {IR(36337, 13), 549}, // 371 ISubSatINTEL
  {IR(31645, 22), 371}, // 372 IgnoreIntersectionKHR
  {IR(34339, 21), 472}, // 373 IgnoreIntersectionNV
  {IR(24207, 6), 91}, // 374 Image
  {IR(32475, 29), 401}, // 375 ImageBlockMatchGatherSADQCOM
  {IR(32446, 29), 400}, // 376 ImageBlockMatchGatherSSDQCOM
  {IR(32365, 23), 397}, // 377 ImageBlockMatchSADQCOM
  {IR(32342, 23), 396}, // 378 ImageBlockMatchSSDQCOM
  {IR(32417, 29), 399}, // 379 ImageBlockMatchWindowSADQCOM
  {IR(32388, 29), 398}, // 380 ImageBlockMatchWindowSSDQCOM
  {IR(32323, 19), 395}, // 381 ImageBoxFilterQCOM
  {IR(26970, 16), 88}, // 382 ImageDrefGather
  {IR(26947, 11), 86}, // 383 ImageFetch
  {IR(26958, 12), 87}, // 384 ImageGather
  {IR(27007, 17), 92}, // 385 ImageQueryFormat
  {IR(27087, 17), 97}, // 386 ImageQueryLevels
  {IR(27073, 14), 96}, // 387 ImageQueryLod
  {IR(27024, 16), 93}, // 388 ImageQueryOrder
  {IR(27104, 18), 98}, // 389 ImageQuerySamples
  {IR(27058, 15), 95}, // 390 ImageQuerySize
  {IR(27040, 18), 94}, // 391 ImageQuerySizeLod
  {IR(26986, 10), 89}, // 392 ImageRead
  {IR(26804, 27), 81}, // 393 ImageSampleDrefExplicitLod
  {IR(26777, 27), 80}, // 394 ImageSampleDrefImplicitLod
  {IR(26754, 23), 79}, // 395 ImageSampleExplicitLod
  {IR(33863, 23), 456}, // 396 ImageSampleFootprintNV
  {IR(26708, 23), 78}, // 397 ImageSampleImplicitLod
  {IR(26916, 31), 85}, // 398 ImageSampleProjDrefExplicitLod
  {IR(26885, 31), 84}, // 399 ImageSampleProjDrefImplicitLod
  {IR(26858, 27), 83}, // 400 ImageSampleProjExplicitLod
  {IR(26831, 27), 82}, // 401 ImageSampleProjImplicitLod
  {IR(32299, 24), 394}, // 402 ImageSampleWeightedQCOM
  {IR(29911, 22), 288}, // 403 ImageSparseDrefGather
  {IR(29876, 17), 286}, // 404 ImageSparseFetch
  {IR(29893, 18), 287}, // 405 ImageSparseGather
  {IR(30003, 16), 293}, // 406 ImageSparseRead
  {IR(29703, 33), 281}, // 407 ImageSparseSampleDrefExplicitLod
  {IR(29670, 33), 280}, // 408 ImageSparseSampleDrefImplicitLod
  {IR(29641, 29), 279}, // 409 ImageSparseSampleExplicitLod
  {IR(29612, 29), 278}, // 410 ImageSparseSampleImplicitLod
  {IR(29839, 37), 285}, // 411 ImageSparseSampleProjDrefExplicitLod
  {IR(29802, 37), 284}, // 412 ImageSparseSampleProjDrefImplicitLod
  {IR(29769, 33), 283}, // 413 ImageSparseSampleProjExplicitLod
  {IR(29736, 33), 282}, // 414 ImageSparseSampleProjImplicitLod
  {IR(29933, 26), 289}, // 415 ImageSparseTexelsResident
  {IR(26187, 18), 53}, // 416 ImageTexelPointer
  {IR(26996, 11), 90}, // 417 ImageWrite
  {IR(26295, 20), 59}, // 418 InBoundsAccessChain
  {IR(26365, 23), 63}, // 419 InBoundsPtrAccessChain
  {IR(27596, 9), 146}, // 420 IsFinite
  {IR(35224, 22), 504}, // 421 IsHelperInvocationEXT
  {IR(27590, 6), 145}, // 422 IsInf
  {IR(27584, 6), 144}, // 423 IsNan
  {IR(32869, 23), 418}, // 424 IsNodePayloadValidAMDX
  {IR(27605, 9), 147}, // 425 IsNormal
  {IR(29525, 13), 273}, // 426 IsValidEvent
  {IR(29180, 17), 257}, // 427 IsValidReserveId
  {IR(28808, 5), 230}, // 428 Kill
  {IR(28725, 6), 226}, // 429 Label
  {IR(27625, 14), 149}, // 430 LessOrGreater
  {IR(28844, 14), 234}, // 431 LifetimeStart
  {IR(28858, 13), 235}, // 432 LifetimeStop
  {IR(25038, 5), 8}, // 433 Line
  {IR(26245, 5), 54}, // 434 Load
  {IR(27696, 11), 155}, // 435 LogicalAnd
  {IR(27657, 13), 152}, // 436 LogicalEqual
  {IR(27707, 11), 156}, // 437 LogicalNot
  {IR(27670, 16), 153}, // 438 LogicalNotEqual
  {IR(27686, 10), 154}, // 439 LogicalOr
  {IR(42811, 17), 726}, // 440 LoopControlINTEL
  {IR(28665, 10), 224}, // 441 LoopMerge
  {IR(44600, 18), 796}, // 442 MaskedGatherINTEL
  {IR(44618, 19), 797}, // 443 MaskedScatterINTEL
  {IR(27494, 18), 135}, // 444 MatrixTimesMatrix
  {IR(27440, 18), 132}, // 445 MatrixTimesScalar
  {IR(27476, 18), 134}, // 446 MatrixTimesVector
  {IR(26425, 15), 65}, // 447 MemberDecorate
  {IR(36563, 21), 563}, // 448 MemberDecorateString
  {IR(36584, 27), 563}, // 449 MemberDecorateStringGOOGLE
  {IR(25020, 11), 6}, // 450 MemberName
  {IR(28402, 14), 206}, // 451 MemoryBarrier
  {IR(25185, 12), 12}, // 452 MemoryModel
  {IR(30188, 19), 302}, // 453 MemoryNamedBarrier
  {IR(30207, 16), 303}, // 454 ModuleProcessed
  {IR(25015, 5), 5}, // 455 Name
  {IR(30165, 23), 301}, // 456 NamedBarrierInitialize
  {IR(29959, 7), 290}, // 457 NoLine
  {IR(32842, 27), 417}, // 458 NodePayloadArrayLengthAMDX
  {IR(24811, 4), 0}, // 459 Nop
  {IR(28136, 4), 186}, // 460 Not
  {IR(27639, 8), 150}, // 461 Ordered
  {IR(27512, 13), 136}, // 462 OuterProduct
  {IR(28631, 4), 223}, // 463 Phi
  {IR(26315, 15), 60}, // 464 PtrAccessChain
  {IR(43064, 29), 741}, // 465 PtrCastToCrossWorkgroupINTEL
  {IR(27269, 17), 111}, // 466 PtrCastToGeneric
  {IR(31055, 8), 343}, // 467 PtrDiff
  {IR(31034, 9), 341}, // 468 PtrEqual
  {IR(31043, 12), 342}, // 469 PtrNotEqual
  {IR(27197, 14), 106}, // 470 QuantizeToF16
  {IR(35529, 17), 515}, // 471 RawAccessChainNV
  {IR(32218, 31), 391}, // 472 RayQueryConfirmIntersectionKHR
  {IR(32186, 32), 390}, // 473 RayQueryGenerateIntersectionKHR
  {IR(34539, 23), 480}, // 474 RayQueryGetClusterIdNV
  {IR(43469, 39), 754}, // 475 RayQueryGetIntersectionBarycentricsKHR
  {IR(43544, 46), 756}, // 476 RayQueryGetIntersectionCandidateAABBOpaqueKHR
  {IR(43508, 36), 755}, // 477 RayQueryGetIntersectionFrontFaceKHR
  {IR(43388, 40), 752}, // 478 RayQueryGetIntersectionGeometryIndexKHR
  {IR(43240, 46), 749}, // 479 RayQueryGetIntersectionInstanceCustomIndexKHR
  {IR(43286, 37), 750}, // 480 RayQueryGetIntersectionInstanceIdKHR
  {IR(43323, 65), 751}, // 481 RayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR
  {IR(35696, 37), 520}, // 482 RayQueryGetIntersectionLSSHitValueNV
  {IR(35624, 38), 518}, // 483 RayQueryGetIntersectionLSSPositionsNV
  {IR(35662, 34), 519}, // 484 RayQueryGetIntersectionLSSRadiiNV
  {IR(43590, 45), 757}, // 485 RayQueryGetIntersectionObjectRayDirectionKHR
  {IR(43635, 42), 758}, // 486 RayQueryGetIntersectionObjectRayOriginKHR
  {IR(43738, 40), 761}, // 487 RayQueryGetIntersectionObjectToWorldKHR
  {IR(43428, 41), 753}, // 488 RayQueryGetIntersectionPrimitiveIndexKHR
  {IR(35546, 40), 516}, // 489 RayQueryGetIntersectionSpherePositionNV
  {IR(35586, 38), 517}, // 490 RayQueryGetIntersectionSphereRadiusNV
  {IR(43212, 28), 748}, // 491 RayQueryGetIntersectionTKHR
  {IR(34414, 50), 477}, // 492 RayQueryGetIntersectionTriangleVertexPositionsKHR
  {IR(32268, 31), 393}, // 493 RayQueryGetIntersectionTypeKHR
  {IR(43778, 40), 762}, // 494 RayQueryGetIntersectionWorldToObjectKHR
  {IR(43189, 23), 747}, // 495 RayQueryGetRayFlagsKHR
  {IR(43167, 22), 746}, // 496 RayQueryGetRayTMinKHR
  {IR(43677, 32), 759}, // 497 RayQueryGetWorldRayDirectionKHR
  {IR(43709, 29), 760}, // 498 RayQueryGetWorldRayOriginKHR
  {IR(32143, 22), 388}, // 499 RayQueryInitializeKHR
  {IR(35904, 19), 528}, // 500 RayQueryIsLSSHitNV
  {IR(35882, 22), 527}, // 501 RayQueryIsSphereHitNV
  {IR(32249, 19), 392}, // 502 RayQueryProceedKHR
  {IR(32165, 21), 389}, // 503 RayQueryTerminateKHR
  {IR(32726, 13), 412}, // 504 ReadClockKHR
  {IR(29048, 9), 249}, // 505 ReadPipe
  {IR(43122, 22), 743}, // 506 ReadPipeBlockingINTEL
  {IR(29496, 13), 271}, // 507 ReleaseEvent
  {IR(33823, 24), 454}, // 508 ReorderThreadWithHintNV
  {IR(33794, 29), 453}, // 509 ReorderThreadWithHitObjectNV
  {IR(34296, 22), 471}, // 510 ReportIntersectionKHR
  {IR(34318, 21), 471}, // 511 ReportIntersectionNV
  {IR(29102, 23), 253}, // 512 ReserveReadPipePackets
  {IR(29125, 24), 254}, // 513 ReserveWritePipePackets
  {IR(29067, 17), 251}, // 514 ReservedReadPipe
  {IR(29084, 18), 252}, // 515 ReservedWritePipe
  {IR(41793, 19), 684}, // 516 RestoreMemoryINTEL
  {IR(29484, 12), 270}, // 517 RetainEvent
  {IR(28813, 7), 231}, // 518 Return
  {IR(28820, 12), 232}, // 519 ReturnValue
  {IR(44582, 18), 795}, // 520 RoundFToTF32INTEL
  {IR(27179, 9), 104}, // 521 SConvert
  {IR(27387, 5), 124}, // 522 SDiv
  {IR(31730, 5), 373}, // 523 SDot
  {IR(31771, 11), 376}, // 524 SDotAccSat
  {IR(31782, 14), 376}, // 525 SDotAccSatKHR
  {IR(31735, 8), 373}, // 526 SDotKHR
  {IR(27755, 13), 161}, // 527 SGreaterThan
  {IR(27786, 18), 163}, // 528 SGreaterThanEqual
  {IR(27814, 10), 165}, // 529 SLessThan
  {IR(27839, 15), 167}, // 530 SLessThanEqual
  {IR(27407, 5), 128}, // 531 SMod
  {IR(27563, 13), 141}, // 532 SMulExtended
  {IR(27336, 8), 115}, // 533 SNegate
  {IR(27402, 5), 127}, // 534 SRem
  {IR(31756, 6), 375}, // 535 SUDot
  {IR(31821, 12), 378}, // 536 SUDotAccSat
  {IR(31833, 15), 378}, // 537 SUDotAccSatKHR
  {IR(31762, 9), 375}, // 538 SUDotKHR
  {IR(26663, 13), 77}, // 539 SampledImage
  {IR(35448, 29), 514}, // 540 SamplerImageAddressingModeNV
  {IR(27225, 15), 108}, // 541 SatConvertSToU
  {IR(27240, 15), 109}, // 542 SatConvertUToS
  {IR(41777, 16), 683}, // 543 SaveMemoryINTEL
  {IR(27718, 7), 157}, // 544 Select
  {IR(28710, 15), 225}, // 545 SelectionMerge
  {IR(34096, 18), 464}, // 546 SetMeshOutputsEXT
  {IR(29538, 19), 274}, // 547 SetUserEventStatus
  {IR(28087, 17), 182}, // 548 ShiftLeftLogical
  {IR(28066, 21), 181}, // 549 ShiftRightArithmetic
  {IR(28048, 18), 180}, // 550 ShiftRightLogical
  {IR(27614, 11), 148}, // 551 SignBitSet
  {IR(30019, 7), 294}, // 552 SizeOf
  {IR(24992, 7), 3}, // 553 Source
  {IR(24873, 16), 2}, // 554 SourceContinued
  {IR(24999, 16), 4}, // 555 SourceExtension
  {IR(26010, 13), 45}, // 556 SpecConstant
  {IR(26023, 22), 46}, // 557 SpecConstantComposite
  {IR(43912, 36), 767}, // 558 SpecConstantCompositeContinuedINTEL
  {IR(32062, 34), 385}, // 559 SpecConstantCompositeReplicateEXT
  {IR(25992, 18), 44}, // 560 SpecConstantFalse
  {IR(26086, 15), 47}, // 561 SpecConstantOp
  {IR(32911, 23), 420}, // 562 SpecConstantStringAMDX
  {IR(25975, 17), 43}, // 563 SpecConstantTrue
  {IR(31109, 25), 346}, // 564 StencilAttachmentReadEXT
  {IR(26250, 6), 55}, // 565 Store
  {IR(25031, 7), 7}, // 566 String
  {IR(44213, 25), 780}, // 567 Subgroup2DBlockLoadINTEL
  {IR(44238, 34), 781}, // 568 Subgroup2DBlockLoadTransformINTEL
  {IR(44272, 34), 782}, // 569 Subgroup2DBlockLoadTransposeINTEL
  {IR(44306, 29), 783}, // 570 Subgroup2DBlockPrefetchINTEL
  {IR(44335, 26), 784}, // 571 Subgroup2DBlockStoreINTEL
  {IR(31507, 20), 364}, // 572 SubgroupAllEqualKHR
  {IR(31477, 15), 362}, // 573 SubgroupAllKHR
  {IR(31492, 15), 363}, // 574 SubgroupAnyKHR
  {IR(40295, 30), 647}, // 575 SubgroupAvcBmeInitializeINTEL
  {IR(40265, 30), 646}, // 576 SubgroupAvcFmeInitializeINTEL
  {IR(38700, 35), 616}, // 577 SubgroupAvcImeAdjustRefOffsetINTEL
  {IR(38735, 39), 617}, // 578 SubgroupAvcImeConvertToMcePayloadINTEL
  {IR(39376, 38), 630}, // 579 SubgroupAvcImeConvertToMceResultINTEL
  {IR(38999, 45), 623}, // 580 SubgroupAvcImeEvaluateWithDualReferenceINTEL
  {IR(39099, 53), 625}, // 581 SubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL
  {IR(39320, 56), 629}, // 582 SubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL
  {IR(39208, 54), 627}, // 583 SubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL
  {IR(38952, 47), 622}, // 584 SubgroupAvcImeEvaluateWithSingleReferenceINTEL
  {IR(39044, 55), 624}, // 585 SubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL
  {IR(39262, 58), 628}, // 586 SubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL
  {IR(39152, 56), 626}, // 587 SubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL
  {IR(40008, 36), 641}, // 588 SubgroupAvcImeGetBorderReachedINTEL
  {IR(39460, 44), 632}, // 589 SubgroupAvcImeGetDualReferenceStreaminINTEL
  {IR(39414, 46), 631}, // 590 SubgroupAvcImeGetSingleReferenceStreaminINTEL
  {IR(39875, 66), 639}, // 591 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL
  {IR(39807, 68), 638}, // 592 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL
  {IR(39941, 67), 640}, // 593 SubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL
  {IR(39670, 68), 636}, // 594 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL
  {IR(39600, 70), 635}, // 595 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL
  {IR(39738, 69), 637}, // 596 SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL
  {IR(40044, 48), 642}, // 597 SubgroupAvcImeGetTruncatedSearchIndicationINTEL
  {IR(40092, 59), 643}, // 598 SubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL
  {IR(40209, 56), 645}, // 599 SubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL
  {IR(40151, 58), 644}, // 600 SubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL
  {IR(38563, 30), 612}, // 601 SubgroupAvcImeInitializeINTEL
  {IR(38667, 33), 615}, // 602 SubgroupAvcImeRefWindowSizeINTEL
  {IR(38631, 36), 614}, // 603 SubgroupAvcImeSetDualReferenceINTEL
  {IR(38864, 54), 620}, // 604 SubgroupAvcImeSetEarlySearchTerminationThresholdINTEL
  {IR(38774, 43), 618}, // 605 SubgroupAvcImeSetMaxMotionVectorCountINTEL
  {IR(38593, 38), 613}, // 606 SubgroupAvcImeSetSingleReferenceINTEL
  {IR(38817, 47), 619}, // 607 SubgroupAvcImeSetUnidirectionalMixDisableINTEL
  {IR(38918, 34), 621}, // 608 SubgroupAvcImeSetWeightedSadINTEL
  {IR(39553, 47), 634}, // 609 SubgroupAvcImeStripDualReferenceStreamoutINTEL
  {IR(39504, 49), 633}, // 610 SubgroupAvcImeStripSingleReferenceStreamoutINTEL
  {IR(37953, 39), 597}, // 611 SubgroupAvcMceConvertToImePayloadINTEL
  {IR(37992, 38), 598}, // 612 SubgroupAvcMceConvertToImeResultINTEL
  {IR(38030, 39), 599}, // 613 SubgroupAvcMceConvertToRefPayloadINTEL
  {IR(38069, 38), 600}, // 614 SubgroupAvcMceConvertToRefResultINTEL
  {IR(38107, 39), 601}, // 615 SubgroupAvcMceConvertToSicPayloadINTEL
  {IR(38146, 38), 602}, // 616 SubgroupAvcMceConvertToSicResultINTEL
  {IR(38259, 43), 605}, // 617 SubgroupAvcMceGetBestInterDistortionsINTEL
  {IR(37391, 50), 586}, // 618 SubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL
  {IR(36989, 60), 578}, // 619 SubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL
  {IR(37189, 51), 582}, // 620 SubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL
  {IR(37335, 56), 585}, // 621 SubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL
  {IR(37102, 47), 580}, // 622 SubgroupAvcMceGetDefaultInterShapePenaltyINTEL
  {IR(37690, 56), 592}, // 623 SubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL
  {IR(37589, 50), 590}, // 624 SubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL
  {IR(37284, 51), 584}, // 625 SubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL
  {IR(37493, 49), 588}, // 626 SubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL
  {IR(37441, 52), 587}, // 627 SubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL
  {IR(37639, 51), 591}, // 628 SubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL
  {IR(38378, 38), 608}, // 629 SubgroupAvcMceGetInterDirectionsINTEL
  {IR(38220, 39), 604}, // 630 SubgroupAvcMceGetInterDistortionsINTEL
  {IR(38302, 38), 606}, // 631 SubgroupAvcMceGetInterMajorShapeINTEL
  {IR(38340, 38), 607}, // 632 SubgroupAvcMceGetInterMinorShapeINTEL
  {IR(38416, 45), 609}, // 633 SubgroupAvcMceGetInterMotionVectorCountINTEL
  {IR(38461, 40), 610}, // 634 SubgroupAvcMceGetInterReferenceIdsINTEL
  {IR(38501, 62), 611}, // 635 SubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL
  {IR(38184, 36), 603}, // 636 SubgroupAvcMceGetMotionVectorsINTEL
  {IR(37746, 33), 593}, // 637 SubgroupAvcMceSetAcOnlyHaarINTEL
  {IR(37892, 61), 596}, // 638 SubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL
  {IR(37049, 53), 579}, // 639 SubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL
  {IR(37240, 44), 583}, // 640 SubgroupAvcMceSetInterDirectionPenaltyINTEL
  {IR(37149, 40), 581}, // 641 SubgroupAvcMceSetInterShapePenaltyINTEL
  {IR(37542, 47), 589}, // 642 SubgroupAvcMceSetMotionVectorCostFunctionINTEL
  {IR(37831, 61), 595}, // 643 SubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL
  {IR(37779, 52), 594}, // 644 SubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL
  {IR(40325, 39), 648}, // 645 SubgroupAvcRefConvertToMcePayloadINTEL
  {IR(40647, 38), 655}, // 646 SubgroupAvcRefConvertToMceResultINTEL
  {IR(40500, 45), 652}, // 647 SubgroupAvcRefEvaluateWithDualReferenceINTEL
  {IR(40545, 46), 653}, // 648 SubgroupAvcRefEvaluateWithMultiReferenceINTEL
  {IR(40591, 56), 654}, // 649 SubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL
  {IR(40453, 47), 651}, // 650 SubgroupAvcRefEvaluateWithSingleReferenceINTEL
  {IR(40364, 46), 649}, // 651 SubgroupAvcRefSetBidirectionalMixDisableINTEL
  {IR(40410, 43), 650}, // 652 SubgroupAvcRefSetBilinearFilterEnableINTEL
  {IR(40783, 42), 659}, // 653 SubgroupAvcSicConfigureIpeLumaChromaINTEL
  {IR(40747, 36), 658}, // 654 SubgroupAvcSicConfigureIpeLumaINTEL
  {IR(40715, 32), 657}, // 655 SubgroupAvcSicConfigureSkcINTEL
  {IR(40864, 39), 661}, // 656 SubgroupAvcSicConvertToMcePayloadINTEL
  {IR(41404, 38), 673}, // 657 SubgroupAvcSicConvertToMceResultINTEL
  {IR(41179, 31), 668}, // 658 SubgroupAvcSicEvaluateIpeINTEL
  {IR(41257, 45), 670}, // 659 SubgroupAvcSicEvaluateWithDualReferenceINTEL
  {IR(41302, 46), 671}, // 660 SubgroupAvcSicEvaluateWithMultiReferenceINTEL
  {IR(41348, 56), 672}, // 661 SubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL
  {IR(41210, 47), 669}, // 662 SubgroupAvcSicEvaluateWithSingleReferenceINTEL
  {IR(41521, 46), 676}, // 663 SubgroupAvcSicGetBestIpeChromaDistortionINTEL
  {IR(41477, 44), 675}, // 664 SubgroupAvcSicGetBestIpeLumaDistortionINTEL
  {IR(41742, 35), 681}, // 665 SubgroupAvcSicGetInterRawSadsINTEL
  {IR(41608, 36), 678}, // 666 SubgroupAvcSicGetIpeChromaModeINTEL
  {IR(41442, 35), 674}, // 667 SubgroupAvcSicGetIpeLumaShapeINTEL
  {IR(40825, 39), 660}, // 668 SubgroupAvcSicGetMotionVectorMaskINTEL
  {IR(41567, 41), 677}, // 669 SubgroupAvcSicGetPackedIpeLumaModesINTEL
  {IR(41644, 50), 679}, // 670 SubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL
  {IR(41694, 48), 680}, // 671 SubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL
  {IR(40685, 30), 656}, // 672 SubgroupAvcSicInitializeINTEL
  {IR(41045, 43), 665}, // 673 SubgroupAvcSicSetBilinearFilterEnableINTEL
  {IR(41136, 43), 667}, // 674 SubgroupAvcSicSetBlockBasedRawSkipSadINTEL
  {IR(40995, 50), 664}, // 675 SubgroupAvcSicSetIntraChromaModeCostFunctionINTEL
  {IR(40947, 48), 663}, // 676 SubgroupAvcSicSetIntraLumaModeCostFunctionINTEL
  {IR(40903, 44), 662}, // 677 SubgroupAvcSicSetIntraLumaShapePenaltyINTEL
  {IR(41088, 48), 666}, // 678 SubgroupAvcSicSetSkcForwardTransformEnableINTEL
  {IR(5289, 18), 356}, // 679 SubgroupBallotKHR
  {IR(44186, 27), 779}, // 680 SubgroupBlockPrefetchINTEL
  {IR(35995, 23), 533}, // 681 SubgroupBlockReadINTEL
  {IR(36018, 24), 534}, // 682 SubgroupBlockWriteINTEL
  {IR(31351, 27), 357}, // 683 SubgroupFirstInvocationKHR
  {IR(36042, 28), 535}, // 684 SubgroupImageBlockReadINTEL
  {IR(36070, 29), 536}, // 685 SubgroupImageBlockWriteINTEL
  {IR(36099, 33), 537}, // 686 SubgroupImageMediaBlockReadINTEL
  {IR(36132, 34), 538}, // 687 SubgroupImageMediaBlockWriteINTEL
  {IR(13595, 38), 785}, // 688 SubgroupMatrixMultiplyAccumulateINTEL
  {IR(31527, 26), 366}, // 689 SubgroupReadInvocationKHR
  {IR(35923, 25), 530}, // 690 SubgroupShuffleDownINTEL
  {IR(11810, 21), 529}, // 691 SubgroupShuffleINTEL
  {IR(35948, 23), 531}, // 692 SubgroupShuffleUpINTEL
  {IR(35971, 24), 532}, // 693 SubgroupShuffleXorINTEL
  {IR(28801, 7), 229}, // 694 Switch
  {IR(44095, 23), 775}, // 695 TaskSequenceAsyncINTEL
  {IR(44071, 24), 774}, // 696 TaskSequenceCreateINTEL
  {IR(44118, 21), 776}, // 697 TaskSequenceGetINTEL
  {IR(44139, 25), 777}, // 698 TaskSequenceReleaseINTEL
  {IR(35266, 27), 506}, // 699 TensorLayoutSetBlockSizeNV
  {IR(35130, 28), 499}, // 700 TensorLayoutSetClampValueNV
  {IR(35059, 27), 496}, // 701 TensorLayoutSetDimensionNV
  {IR(35086, 24), 497}, // 702 TensorLayoutSetStrideNV
  {IR(35110, 20), 498}, // 703 TensorLayoutSliceNV
  {IR(31219, 19), 350}, // 704 TensorQuerySizeARM
  {IR(31190, 14), 348}, // 705 TensorReadARM
  {IR(35246, 20), 505}, // 706 TensorViewSetClipNV
  {IR(35177, 25), 501}, // 707 TensorViewSetDimensionNV
  {IR(35202, 22), 502}, // 708 TensorViewSetStrideNV
  {IR(31204, 15), 349}, // 709 TensorWriteARM
  {IR(31238, 20), 351}, // 710 TerminateInvocation
  {IR(31667, 16), 372}, // 711 TerminateRayKHR
  {IR(34360, 15), 473}, // 712 TerminateRayNV
  {IR(34383, 14), 475}, // 713 TraceMotionNV
  {IR(34375, 8), 474}, // 714 TraceNV
  {IR(31579, 12), 368}, // 715 TraceRayKHR
  {IR(34397, 17), 476}, // 716 TraceRayMotionNV
  {IR(26653, 10), 76}, // 717 Transpose
  {IR(34464, 29), 478}, // 718 TypeAccelerationStructureKHR
  {IR(34493, 28), 478}, // 719 TypeAccelerationStructureNV
  {IR(25602, 10), 25}, // 720 TypeArray
  {IR(36908, 37), 575}, // 721 TypeAvcImeDualReferenceStreaminINTEL
  {IR(36643, 23), 566}, // 722 TypeAvcImePayloadINTEL
  {IR(36825, 44), 573}, // 723 TypeAvcImeResultDualReferenceStreamoutINTEL
  {IR(36757, 22), 571}, // 724 TypeAvcImeResultINTEL
  {IR(36779, 46), 572}, // 725 TypeAvcImeResultSingleReferenceStreamoutINTEL
  {IR(36869, 39), 574}, // 726 TypeAvcImeSingleReferenceStreaminINTEL
  {IR(36712, 23), 569}, // 727 TypeAvcMcePayloadINTEL
  {IR(36735, 22), 570}, // 728 TypeAvcMceResultINTEL
  {IR(36666, 23), 567}, // 729 TypeAvcRefPayloadINTEL
  {IR(36945, 22), 576}, // 730 TypeAvcRefResultINTEL
  {IR(36689, 23), 568}, // 731 TypeAvcSicPayloadINTEL
  {IR(36967, 22), 577}, // 732 TypeAvcSicResultINTEL
  {IR(25364, 9), 17}, // 733 TypeBool
  {IR(43832, 23), 764}, // 734 TypeBufferSurfaceINTEL
  {IR(31848, 25), 379}, // 735 TypeCooperativeMatrixKHR
  {IR(34586, 24), 482}, // 736 TypeCooperativeMatrixNV
  {IR(33886, 24), 457}, // 737 TypeCooperativeVectorNV
  {IR(25717, 16), 32}, // 738 TypeDeviceEvent
  {IR(25707, 10), 31}, // 739 TypeEvent
  {IR(25418, 10), 19}, // 740 TypeFloat
  {IR(25766, 19), 36}, // 741 TypeForwardPointer
  {IR(25694, 13), 30}, // 742 TypeFunction
  {IR(33847, 16), 455}, // 743 TypeHitObjectNV
  {IR(25563, 10), 22}, // 744 TypeImage
  {IR(25373, 8), 18}, // 745 TypeInt
  {IR(25439, 11), 21}, // 746 TypeMatrix
  {IR(30148, 17), 300}, // 747 TypeNamedBarrier
  {IR(32788, 25), 415}, // 748 TypeNodePayloadArrayAMDX
  {IR(25640, 11), 28}, // 749 TypeOpaque
  {IR(25757, 9), 35}, // 750 TypePipe
  {IR(30026, 16), 295}, // 751 TypePipeStorage
  {IR(25682, 12), 29}, // 752 TypePointer
  {IR(25747, 10), 34}, // 753 TypeQueue
  {IR(32127, 16), 387}, // 754 TypeRayQueryKHR
  {IR(25733, 14), 33}, // 755 TypeReserveId
  {IR(25612, 17), 26}, // 756 TypeRuntimeArray
  {IR(25585, 17), 24}, // 757 TypeSampledImage
  {IR(25573, 12), 23}, // 758 TypeSampler
  {IR(25629, 11), 27}, // 759 TypeStruct
  {IR(43855, 25), 765}, // 760 TypeStructContinuedINTEL
  {IR(44164, 22), 778}, // 761 TypeTaskSequenceINTEL
  {IR(31134, 14), 347}, // 762 TypeTensorARM
  {IR(35002, 19), 493}, // 763 TypeTensorLayoutNV
  {IR(35021, 17), 494}, // 764 TypeTensorViewNV
  {IR(31258, 22), 352}, // 765 TypeUntypedPointerKHR
  {IR(25428, 11), 20}, // 766 TypeVector
  {IR(36625, 18), 565}, // 767 TypeVmeImageINTEL
  {IR(25355, 9), 16}, // 768 TypeVoid
  {IR(36254, 13), 544}, // 769 UAddSatINTEL
  {IR(36281, 14), 546}, // 770 UAverageINTEL
  {IR(36316, 21), 548}, // 771 UAverageRoundedINTEL
  {IR(27170, 9), 103}, // 772 UConvert
  {IR(36166, 24), 539}, // 773 UCountLeadingZerosINTEL
  {IR(36190, 25), 540}, // 774 UCountTrailingZerosINTEL
  {IR(27382, 5), 123}, // 775 UDiv
  {IR(31743, 5), 374}, // 776 UDot
  {IR(31796, 11), 377}, // 777 UDotAccSat
  {IR(31807, 14), 377}, // 778 UDotAccSatKHR
  {IR(31748, 8), 374}, // 779 UDotKHR
  {IR(27742, 13), 160}, // 780 UGreaterThan
  {IR(27768, 18), 162}, // 781 UGreaterThanEqual
  {IR(27804, 10), 164}, // 782 ULessThan
  {IR(27824, 15), 166}, // 783 ULessThanEqual
  {IR(27397, 5), 126}, // 784 UMod
  {IR(36378, 15), 552}, // 785 UMul32x16INTEL
  {IR(27550, 13), 140}, // 786 UMulExtended
  {IR(36350, 13), 550}, // 787 USubSatINTEL
  {IR(24867, 6), 1}, // 788 Undef
  {IR(27647, 10), 151}, // 789 Unordered
  {IR(28832, 12), 233}, // 790 Unreachable
  {IR(31299, 22), 354}, // 791 UntypedAccessChainKHR
  {IR(31436, 22), 360}, // 792 UntypedArrayLengthKHR
  {IR(31321, 30), 355}, // 793 UntypedInBoundsAccessChainKHR
  {IR(31403, 33), 359}, // 794 UntypedInBoundsPtrAccessChainKHR
  {IR(31458, 19), 361}, // 795 UntypedPrefetchKHR
  {IR(31378, 25), 358}, // 796 UntypedPtrAccessChainKHR
  {IR(31280, 19), 353}, // 797 UntypedVariableKHR
  {IR(26178, 9), 52}, // 798 Variable
  {IR(12266, 25), 682}, // 799 VariableLengthArrayINTEL
  {IR(26535, 21), 69}, // 800 VectorExtractDynamic
  {IR(26556, 20), 70}, // 801 VectorInsertDynamic
  {IR(26576, 14), 71}, // 802 VectorShuffle
  {IR(27458, 18), 133}, // 803 VectorTimesMatrix
  {IR(27422, 18), 131}, // 804 VectorTimesScalar
  {IR(36611, 14), 564}, // 805 VmeImageINTEL
  {IR(34141, 33), 466}, // 806 WritePackedPrimitiveIndices4x8NV
  {IR(29057, 10), 250}, // 807 WritePipe
  {IR(43144, 23), 744}, // 808 WritePipeBlockingINTEL
}};

// Extended instruction descriptions, ordered by (extinst enum, opcode value).
// The fields in order are:
//   enum value
//   operands, an IndexRange into kOperandSpans
//   name, a character-counting IndexRange into kStrings
//   capabilities, an IndexRange into kCapabilitySpans
static const std::array<ExtInstDesc, 425> kExtInstByValue{{
    {0,IR(0, 0),IR(44637, 14),IR(1, 0)}, // DebugInfoNone in debuginfo
    {1,IR(52, 3),IR(44651, 21),IR(1, 0)}, // DebugCompilationUnit in debuginfo
    {2,IR(727, 3),IR(44724, 15),IR(1, 0)}, // DebugTypeBasic in debuginfo
    {3,IR(730, 3),IR(44773, 17),IR(1, 0)}, // DebugTypePointer in debuginfo
    {4,IR(733, 2),IR(44828, 19),IR(1, 0)}, // DebugTypeQualifier in debuginfo
    {5,IR(168, 2),IR(44847, 15),IR(1, 0)}, // DebugTypeArray in debuginfo
    {6,IR(261, 2),IR(44862, 16),IR(1, 0)}, // DebugTypeVector in debuginfo
    {7,IR(735, 6),IR(44878, 13),IR(1, 0)}, // DebugTypedef in debuginfo
    {8,IR(168, 2),IR(44891, 18),IR(1, 0)}, // DebugTypeFunction in debuginfo
    {9,IR(741, 9),IR(44909, 14),IR(1, 0)}, // DebugTypeEnum in debuginfo
    {10,IR(750, 9),IR(44961, 19),IR(1, 0)}, // DebugTypeComposite in debuginfo
    {11,IR(759, 10),IR(44980, 16),IR(1, 0)}, // DebugTypeMember in debuginfo
    {12,IR(769, 5),IR(44996, 21),IR(1, 0)}, // DebugTypeInheritance in debuginfo
    {13,IR(36, 2),IR(45017, 21),IR(1, 0)}, // DebugTypePtrToMember in debuginfo
    {14,IR(168, 2),IR(45038, 18),IR(1, 0)}, // DebugTypeTemplate in debuginfo
    {15,IR(774, 6),IR(45056, 27),IR(1, 0)}, // DebugTypeTemplateParameter in debuginfo
    {16,IR(780, 5),IR(45083, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in debuginfo
    {17,IR(785, 5),IR(45118, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in debuginfo
    {18,IR(759, 10),IR(45149, 20),IR(1, 0)}, // DebugGlobalVariable in debuginfo
    {19,IR(790, 8),IR(45169, 25),IR(1, 0)}, // DebugFunctionDeclaration in debuginfo
    {20,IR(798, 11),IR(45194, 14),IR(1, 0)}, // DebugFunction in debuginfo
    {21,IR(809, 5),IR(45208, 18),IR(1, 0)}, // DebugLexicalBlock in debuginfo
    {22,IR(814, 3),IR(45226, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in debuginfo
    {23,IR(817, 2),IR(45257, 11),IR(1, 0)}, // DebugScope in debuginfo
    {24,IR(0, 0),IR(45268, 13),IR(1, 0)}, // DebugNoScope in debuginfo
    {25,IR(819, 3),IR(45281, 15),IR(1, 0)}, // DebugInlinedAt in debuginfo
    {26,IR(822, 7),IR(45338, 19),IR(1, 0)}, // DebugLocalVariable in debuginfo
    {27,IR(36, 2),IR(45357, 21),IR(1, 0)}, // DebugInlinedVariable in debuginfo
    {28,IR(33, 3),IR(45378, 13),IR(1, 0)}, // DebugDeclare in debuginfo
    {29,IR(829, 3),IR(45391, 11),IR(1, 0)}, // DebugValue in debuginfo
    {30,IR(832, 2),IR(45435, 15),IR(1, 0)}, // DebugOperation in debuginfo
    {31,IR(683, 1),IR(45450, 16),IR(1, 0)}, // DebugExpression in debuginfo
    {32,IR(834, 4),IR(45466, 14),IR(1, 0)}, // DebugMacroDef in debuginfo
    {33,IR(814, 3),IR(45480, 16),IR(1, 0)}, // DebugMacroUndef in debuginfo
    {1,IR(10, 1),IR(45496, 6),IR(1, 0)}, // Round in glsl_std_450
    {2,IR(10, 1),IR(45502, 10),IR(1, 0)}, // RoundEven in glsl_std_450
    {3,IR(10, 1),IR(45512, 6),IR(1, 0)}, // Trunc in glsl_std_450
    {4,IR(10, 1),IR(45518, 5),IR(1, 0)}, // FAbs in glsl_std_450
    {5,IR(10, 1),IR(45523, 5),IR(1, 0)}, // SAbs in glsl_std_450
    {6,IR(10, 1),IR(45528, 6),IR(1, 0)}, // FSign in glsl_std_450
    {7,IR(10, 1),IR(45534, 6),IR(1, 0)}, // SSign in glsl_std_450
    {8,IR(10, 1),IR(45540, 6),IR(1, 0)}, // Floor in glsl_std_450
    {9,IR(10, 1),IR(45546, 5),IR(1, 0)}, // Ceil in glsl_std_450
    {10,IR(10, 1),IR(45551, 6),IR(1, 0)}, // Fract in glsl_std_450
    {11,IR(10, 1),IR(45557, 8),IR(1, 0)}, // Radians in glsl_std_450
    {12,IR(10, 1),IR(45565, 8),IR(1, 0)}, // Degrees in glsl_std_450
    {13,IR(10, 1),IR(45573, 4),IR(1, 0)}, // Sin in glsl_std_450
    {14,IR(10, 1),IR(45577, 4),IR(1, 0)}, // Cos in glsl_std_450
    {15,IR(10, 1),IR(45581, 4),IR(1, 0)}, // Tan in glsl_std_450
    {16,IR(10, 1),IR(45585, 5),IR(1, 0)}, // Asin in glsl_std_450
    {17,IR(10, 1),IR(45590, 5),IR(1, 0)}, // Acos in glsl_std_450
    {18,IR(10, 1),IR(45595, 5),IR(1, 0)}, // Atan in glsl_std_450
    {19,IR(10, 1),IR(45600, 5),IR(1, 0)}, // Sinh in glsl_std_450
    {20,IR(10, 1),IR(45605, 5),IR(1, 0)}, // Cosh in glsl_std_450
    {21,IR(10, 1),IR(45610, 5),IR(1, 0)}, // Tanh in glsl_std_450
    {22,IR(10, 1),IR(45615, 6),IR(1, 0)}, // Asinh in glsl_std_450
    {23,IR(10, 1),IR(45621, 6),IR(1, 0)}, // Acosh in glsl_std_450
    {24,IR(10, 1),IR(45627, 6),IR(1, 0)}, // Atanh in glsl_std_450
    {25,IR(36, 2),IR(45633, 6),IR(1, 0)}, // Atan2 in glsl_std_450
    {26,IR(36, 2),IR(45639, 4),IR(1, 0)}, // Pow in glsl_std_450
    {27,IR(10, 1),IR(45643, 4),IR(1, 0)}, // Exp in glsl_std_450
    {28,IR(10, 1),IR(45647, 4),IR(1, 0)}, // Log in glsl_std_450
    {29,IR(10, 1),IR(45651, 5),IR(1, 0)}, // Exp2 in glsl_std_450
    {30,IR(10, 1),IR(45656, 5),IR(1, 0)}, // Log2 in glsl_std_450
    {31,IR(10, 1),IR(45661, 5),IR(1, 0)}, // Sqrt in glsl_std_450
    {32,IR(10, 1),IR(45666, 12),IR(1, 0)}, // InverseSqrt in glsl_std_450
    {33,IR(10, 1),IR(45678, 12),IR(1, 0)}, // Determinant in glsl_std_450
    {34,IR(10, 1),IR(45690, 14),IR(1, 0)}, // MatrixInverse in glsl_std_450
    {35,IR(36, 2),IR(45704, 5),IR(1, 0)}, // Modf in glsl_std_450
    {36,IR(10, 1),IR(45709, 11),IR(1, 0)}, // ModfStruct in glsl_std_450
    {37,IR(36, 2),IR(45720, 5),IR(1, 0)}, // FMin in glsl_std_450
    {38,IR(36, 2),IR(45725, 5),IR(1, 0)}, // UMin in glsl_std_450
    {39,IR(36, 2),IR(45730, 5),IR(1, 0)}, // SMin in glsl_std_450
    {40,IR(36, 2),IR(45735, 5),IR(1, 0)}, // FMax in glsl_std_450
    {41,IR(36, 2),IR(45740, 5),IR(1, 0)}, // UMax in glsl_std_450
    {42,IR(36, 2),IR(45745, 5),IR(1, 0)}, // SMax in glsl_std_450
    {43,IR(33, 3),IR(45750, 7),IR(1, 0)}, // FClamp in glsl_std_450
    {44,IR(33, 3),IR(45757, 7),IR(1, 0)}, // UClamp in glsl_std_450
    {45,IR(33, 3),IR(45764, 7),IR(1, 0)}, // SClamp in glsl_std_450
    {46,IR(33, 3),IR(45771, 5),IR(1, 0)}, // FMix in glsl_std_450
    {47,IR(33, 3),IR(45776, 5),IR(1, 0)}, // IMix in glsl_std_450
    {48,IR(36, 2),IR(45781, 5),IR(1, 0)}, // Step in glsl_std_450
    {49,IR(33, 3),IR(45786, 11),IR(1, 0)}, // SmoothStep in glsl_std_450
    {50,IR(33, 3),IR(45797, 4),IR(1, 0)}, // Fma in glsl_std_450
    {51,IR(36, 2),IR(45801, 6),IR(1, 0)}, // Frexp in glsl_std_450
    {52,IR(10, 1),IR(45807, 12),IR(1, 0)}, // FrexpStruct in glsl_std_450
    {53,IR(36, 2),IR(45819, 6),IR(1, 0)}, // Ldexp in glsl_std_450
    {54,IR(10, 1),IR(45825, 13),IR(1, 0)}, // PackSnorm4x8 in glsl_std_450
    {55,IR(10, 1),IR(45838, 13),IR(1, 0)}, // PackUnorm4x8 in glsl_std_450
    {56,IR(10, 1),IR(45851, 14),IR(1, 0)}, // PackSnorm2x16 in glsl_std_450
    {57,IR(10, 1),IR(45865, 14),IR(1, 0)}, // PackUnorm2x16 in glsl_std_450
    {58,IR(10, 1),IR(45879, 13),IR(1, 0)}, // PackHalf2x16 in glsl_std_450
    {59,IR(10, 1),IR(45892, 15),IR(300, 1)}, // PackDouble2x32 in glsl_std_450
    {60,IR(10, 1),IR(45907, 16),IR(1, 0)}, // UnpackSnorm2x16 in glsl_std_450
    {61,IR(10, 1),IR(45923, 16),IR(1, 0)}, // UnpackUnorm2x16 in glsl_std_450
    {62,IR(10, 1),IR(45939, 15),IR(1, 0)}, // UnpackHalf2x16 in glsl_std_450
    {63,IR(10, 1),IR(45954, 15),IR(1, 0)}, // UnpackSnorm4x8 in glsl_std_450
    {64,IR(10, 1),IR(45969, 15),IR(1, 0)}, // UnpackUnorm4x8 in glsl_std_450
    {65,IR(10, 1),IR(45984, 17),IR(300, 1)}, // UnpackDouble2x32 in glsl_std_450
    {66,IR(10, 1),IR(46001, 7),IR(1, 0)}, // Length in glsl_std_450
    {67,IR(36, 2),IR(46008, 9),IR(1, 0)}, // Distance in glsl_std_450
    {68,IR(36, 2),IR(46017, 6),IR(1, 0)}, // Cross in glsl_std_450
    {69,IR(10, 1),IR(46023, 10),IR(1, 0)}, // Normalize in glsl_std_450
    {70,IR(33, 3),IR(46033, 12),IR(1, 0)}, // FaceForward in glsl_std_450
    {71,IR(36, 2),IR(46045, 8),IR(1, 0)}, // Reflect in glsl_std_450
    {72,IR(33, 3),IR(46053, 8),IR(1, 0)}, // Refract in glsl_std_450
    {73,IR(10, 1),IR(46061, 9),IR(1, 0)}, // FindILsb in glsl_std_450
    {74,IR(10, 1),IR(46070, 9),IR(1, 0)}, // FindSMsb in glsl_std_450
    {75,IR(10, 1),IR(46079, 9),IR(1, 0)}, // FindUMsb in glsl_std_450
    {76,IR(10, 1),IR(46088, 22),IR(301, 1)}, // InterpolateAtCentroid in glsl_std_450
    {77,IR(36, 2),IR(46110, 20),IR(301, 1)}, // InterpolateAtSample in glsl_std_450
    {78,IR(36, 2),IR(46130, 20),IR(301, 1)}, // InterpolateAtOffset in glsl_std_450
    {79,IR(36, 2),IR(46150, 5),IR(1, 0)}, // NMin in glsl_std_450
    {80,IR(36, 2),IR(46155, 5),IR(1, 0)}, // NMax in glsl_std_450
    {81,IR(33, 3),IR(46160, 7),IR(1, 0)}, // NClamp in glsl_std_450
    {1,IR(387, 5),IR(4508, 7),IR(1, 0)}, // Kernel in nonsemantic_clspvreflection
    {2,IR(838, 5),IR(46167, 13),IR(1, 0)}, // ArgumentInfo in nonsemantic_clspvreflection
    {3,IR(843, 5),IR(46180, 22),IR(1, 0)}, // ArgumentStorageBuffer in nonsemantic_clspvreflection
    {4,IR(843, 5),IR(46202, 16),IR(1, 0)}, // ArgumentUniform in nonsemantic_clspvreflection
    {5,IR(531, 7),IR(46218, 25),IR(1, 0)}, // ArgumentPodStorageBuffer in nonsemantic_clspvreflection
    {6,IR(531, 7),IR(46243, 19),IR(1, 0)}, // ArgumentPodUniform in nonsemantic_clspvreflection
    {7,IR(843, 5),IR(46262, 24),IR(1, 0)}, // ArgumentPodPushConstant in nonsemantic_clspvreflection
    {8,IR(843, 5),IR(46286, 21),IR(1, 0)}, // ArgumentSampledImage in nonsemantic_clspvreflection
    {9,IR(843, 5),IR(46307, 21),IR(1, 0)}, // ArgumentStorageImage in nonsemantic_clspvreflection
    {10,IR(843, 5),IR(46328, 16),IR(1, 0)}, // ArgumentSampler in nonsemantic_clspvreflection
    {11,IR(843, 5),IR(46344, 18),IR(1, 0)}, // ArgumentWorkgroup in nonsemantic_clspvreflection
    {12,IR(33, 3),IR(46362, 26),IR(1, 0)}, // SpecConstantWorkgroupSize in nonsemantic_clspvreflection
    {13,IR(33, 3),IR(46388, 25),IR(1, 0)}, // SpecConstantGlobalOffset in nonsemantic_clspvreflection
    {14,IR(10, 1),IR(46413, 20),IR(1, 0)}, // SpecConstantWorkDim in nonsemantic_clspvreflection
    {15,IR(36, 2),IR(46433, 25),IR(1, 0)}, // PushConstantGlobalOffset in nonsemantic_clspvreflection
    {16,IR(36, 2),IR(46458, 30),IR(1, 0)}, // PushConstantEnqueuedLocalSize in nonsemantic_clspvreflection
    {17,IR(36, 2),IR(46488, 23),IR(1, 0)}, // PushConstantGlobalSize in nonsemantic_clspvreflection
    {18,IR(36, 2),IR(46511, 25),IR(1, 0)}, // PushConstantRegionOffset in nonsemantic_clspvreflection
    {19,IR(36, 2),IR(46536, 26),IR(1, 0)}, // PushConstantNumWorkgroups in nonsemantic_clspvreflection
    {20,IR(36, 2),IR(46562, 30),IR(1, 0)}, // PushConstantRegionGroupOffset in nonsemantic_clspvreflection
    {21,IR(33, 3),IR(46592, 26),IR(1, 0)}, // ConstantDataStorageBuffer in nonsemantic_clspvreflection
    {22,IR(33, 3),IR(46618, 20),IR(1, 0)}, // ConstantDataUniform in nonsemantic_clspvreflection
    {23,IR(33, 3),IR(7933, 15),IR(1, 0)}, // LiteralSampler in nonsemantic_clspvreflection
    {24,IR(296, 4),IR(46638, 30),IR(1, 0)}, // PropertyRequiredWorkgroupSize in nonsemantic_clspvreflection
    {25,IR(10, 1),IR(46668, 28),IR(1, 0)}, // SpecConstantSubgroupMaxSize in nonsemantic_clspvreflection
    {26,IR(843, 5),IR(46696, 28),IR(1, 0)}, // ArgumentPointerPushConstant in nonsemantic_clspvreflection
    {27,IR(531, 7),IR(46724, 23),IR(1, 0)}, // ArgumentPointerUniform in nonsemantic_clspvreflection
    {28,IR(33, 3),IR(46747, 35),IR(1, 0)}, // ProgramScopeVariablesStorageBuffer in nonsemantic_clspvreflection
    {29,IR(33, 3),IR(46782, 38),IR(1, 0)}, // ProgramScopeVariablePointerRelocation in nonsemantic_clspvreflection
    {30,IR(296, 4),IR(46820, 42),IR(1, 0)}, // ImageArgumentInfoChannelOrderPushConstant in nonsemantic_clspvreflection
    {31,IR(296, 4),IR(46862, 45),IR(1, 0)}, // ImageArgumentInfoChannelDataTypePushConstant in nonsemantic_clspvreflection
    {32,IR(502, 6),IR(46907, 37),IR(1, 0)}, // ImageArgumentInfoChannelOrderUniform in nonsemantic_clspvreflection
    {33,IR(502, 6),IR(46944, 40),IR(1, 0)}, // ImageArgumentInfoChannelDataTypeUniform in nonsemantic_clspvreflection
    {34,IR(843, 5),IR(46984, 27),IR(1, 0)}, // ArgumentStorageTexelBuffer in nonsemantic_clspvreflection
    {35,IR(843, 5),IR(47011, 27),IR(1, 0)}, // ArgumentUniformTexelBuffer in nonsemantic_clspvreflection
    {36,IR(33, 3),IR(47038, 32),IR(1, 0)}, // ConstantDataPointerPushConstant in nonsemantic_clspvreflection
    {37,IR(33, 3),IR(47070, 40),IR(1, 0)}, // ProgramScopeVariablePointerPushConstant in nonsemantic_clspvreflection
    {38,IR(829, 3),IR(47110, 11),IR(1, 0)}, // PrintfInfo in nonsemantic_clspvreflection
    {39,IR(33, 3),IR(47121, 26),IR(1, 0)}, // PrintfBufferStorageBuffer in nonsemantic_clspvreflection
    {40,IR(33, 3),IR(47147, 32),IR(1, 0)}, // PrintfBufferPointerPushConstant in nonsemantic_clspvreflection
    {41,IR(296, 4),IR(47179, 34),IR(1, 0)}, // NormalizedSamplerMaskPushConstant in nonsemantic_clspvreflection
    {42,IR(36, 2),IR(47213, 22),IR(1, 0)}, // WorkgroupVariableSize in nonsemantic_clspvreflection
    {0,IR(0, 0),IR(44637, 14),IR(1, 0)}, // DebugInfoNone in nonsemantic_shader_debuginfo_100
    {1,IR(296, 4),IR(44651, 21),IR(1, 0)}, // DebugCompilationUnit in nonsemantic_shader_debuginfo_100
    {2,IR(296, 4),IR(44724, 15),IR(1, 0)}, // DebugTypeBasic in nonsemantic_shader_debuginfo_100
    {3,IR(33, 3),IR(44773, 17),IR(1, 0)}, // DebugTypePointer in nonsemantic_shader_debuginfo_100
    {4,IR(36, 2),IR(44828, 19),IR(1, 0)}, // DebugTypeQualifier in nonsemantic_shader_debuginfo_100
    {5,IR(168, 2),IR(44847, 15),IR(1, 0)}, // DebugTypeArray in nonsemantic_shader_debuginfo_100
    {6,IR(36, 2),IR(44862, 16),IR(1, 0)}, // DebugTypeVector in nonsemantic_shader_debuginfo_100
    {7,IR(502, 6),IR(44878, 13),IR(1, 0)}, // DebugTypedef in nonsemantic_shader_debuginfo_100
    {8,IR(829, 3),IR(44891, 18),IR(1, 0)}, // DebugTypeFunction in nonsemantic_shader_debuginfo_100
    {9,IR(848, 9),IR(44909, 14),IR(1, 0)}, // DebugTypeEnum in nonsemantic_shader_debuginfo_100
    {10,IR(857, 10),IR(44961, 19),IR(1, 0)}, // DebugTypeComposite in nonsemantic_shader_debuginfo_100
    {11,IR(867, 9),IR(44980, 16),IR(1, 0)}, // DebugTypeMember in nonsemantic_shader_debuginfo_100
    {12,IR(296, 4),IR(44996, 21),IR(1, 0)}, // DebugTypeInheritance in nonsemantic_shader_debuginfo_100
    {13,IR(36, 2),IR(45017, 21),IR(1, 0)}, // DebugTypePtrToMember in nonsemantic_shader_debuginfo_100
    {14,IR(168, 2),IR(45038, 18),IR(1, 0)}, // DebugTypeTemplate in nonsemantic_shader_debuginfo_100
    {15,IR(502, 6),IR(45056, 27),IR(1, 0)}, // DebugTypeTemplateParameter in nonsemantic_shader_debuginfo_100
    {16,IR(611, 5),IR(45083, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in nonsemantic_shader_debuginfo_100
    {17,IR(876, 5),IR(45118, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in nonsemantic_shader_debuginfo_100
    {18,IR(881, 10),IR(45149, 20),IR(1, 0)}, // DebugGlobalVariable in nonsemantic_shader_debuginfo_100
    {19,IR(448, 8),IR(45169, 25),IR(1, 0)}, // DebugFunctionDeclaration in nonsemantic_shader_debuginfo_100
    {20,IR(881, 10),IR(45194, 14),IR(1, 0)}, // DebugFunction in nonsemantic_shader_debuginfo_100
    {21,IR(843, 5),IR(45208, 18),IR(1, 0)}, // DebugLexicalBlock in nonsemantic_shader_debuginfo_100
    {22,IR(33, 3),IR(45226, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in nonsemantic_shader_debuginfo_100
    {23,IR(817, 2),IR(45257, 11),IR(1, 0)}, // DebugScope in nonsemantic_shader_debuginfo_100
    {24,IR(0, 0),IR(45268, 13),IR(1, 0)}, // DebugNoScope in nonsemantic_shader_debuginfo_100
    {25,IR(891, 3),IR(45281, 15),IR(1, 0)}, // DebugInlinedAt in nonsemantic_shader_debuginfo_100
    {26,IR(894, 8),IR(45338, 19),IR(1, 0)}, // DebugLocalVariable in nonsemantic_shader_debuginfo_100
    {27,IR(36, 2),IR(45357, 21),IR(1, 0)}, // DebugInlinedVariable in nonsemantic_shader_debuginfo_100
    {28,IR(902, 4),IR(45378, 13),IR(1, 0)}, // DebugDeclare in nonsemantic_shader_debuginfo_100
    {29,IR(902, 4),IR(45391, 11),IR(1, 0)}, // DebugValue in nonsemantic_shader_debuginfo_100
    {30,IR(168, 2),IR(45435, 15),IR(1, 0)}, // DebugOperation in nonsemantic_shader_debuginfo_100
    {31,IR(683, 1),IR(45450, 16),IR(1, 0)}, // DebugExpression in nonsemantic_shader_debuginfo_100
    {32,IR(554, 4),IR(45466, 14),IR(1, 0)}, // DebugMacroDef in nonsemantic_shader_debuginfo_100
    {33,IR(33, 3),IR(45480, 16),IR(1, 0)}, // DebugMacroUndef in nonsemantic_shader_debuginfo_100
    {34,IR(483, 7),IR(47235, 20),IR(1, 0)}, // DebugImportedEntity in nonsemantic_shader_debuginfo_100
    {35,IR(817, 2),IR(47255, 12),IR(1, 0)}, // DebugSource in nonsemantic_shader_debuginfo_100
    {101,IR(36, 2),IR(47267, 24),IR(1, 0)}, // DebugFunctionDefinition in nonsemantic_shader_debuginfo_100
    {102,IR(10, 1),IR(47291, 21),IR(1, 0)}, // DebugSourceContinued in nonsemantic_shader_debuginfo_100
    {103,IR(611, 5),IR(47312, 10),IR(1, 0)}, // DebugLine in nonsemantic_shader_debuginfo_100
    {104,IR(0, 0),IR(47322, 12),IR(1, 0)}, // DebugNoLine in nonsemantic_shader_debuginfo_100
    {105,IR(36, 2),IR(47334, 21),IR(1, 0)}, // DebugBuildIdentifier in nonsemantic_shader_debuginfo_100
    {106,IR(10, 1),IR(47355, 17),IR(1, 0)}, // DebugStoragePath in nonsemantic_shader_debuginfo_100
    {107,IR(296, 4),IR(47372, 16),IR(1, 0)}, // DebugEntryPoint in nonsemantic_shader_debuginfo_100
    {108,IR(33, 3),IR(47388, 16),IR(1, 0)}, // DebugTypeMatrix in nonsemantic_shader_debuginfo_100
    {1,IR(701, 9),IR(47404, 14),IR(1, 0)}, // Configuration in nonsemantic_vkspreflection
    {2,IR(10, 1),IR(47418, 13),IR(1, 0)}, // StartCounter in nonsemantic_vkspreflection
    {3,IR(10, 1),IR(47431, 12),IR(1, 0)}, // StopCounter in nonsemantic_vkspreflection
    {4,IR(296, 4),IR(47443, 14),IR(1, 0)}, // PushConstants in nonsemantic_vkspreflection
    {5,IR(33, 3),IR(47457, 23),IR(1, 0)}, // SpecializationMapEntry in nonsemantic_vkspreflection
    {6,IR(906, 15),IR(47480, 20),IR(1, 0)}, // DescriptorSetBuffer in nonsemantic_vkspreflection
    {7,IR(921, 33),IR(47500, 19),IR(1, 0)}, // DescriptorSetImage in nonsemantic_vkspreflection
    {8,IR(954, 19),IR(47519, 21),IR(1, 0)}, // DescriptorSetSampler in nonsemantic_vkspreflection
    {0,IR(0, 0),IR(44637, 14),IR(1, 0)}, // DebugInfoNone in opencl_debuginfo_100
    {1,IR(973, 4),IR(44651, 21),IR(1, 0)}, // DebugCompilationUnit in opencl_debuginfo_100
    {2,IR(977, 3),IR(44724, 15),IR(1, 0)}, // DebugTypeBasic in opencl_debuginfo_100
    {3,IR(980, 3),IR(44773, 17),IR(1, 0)}, // DebugTypePointer in opencl_debuginfo_100
    {4,IR(983, 2),IR(44828, 19),IR(1, 0)}, // DebugTypeQualifier in opencl_debuginfo_100
    {5,IR(168, 2),IR(44847, 15),IR(1, 0)}, // DebugTypeArray in opencl_debuginfo_100
    {6,IR(261, 2),IR(44862, 16),IR(1, 0)}, // DebugTypeVector in opencl_debuginfo_100
    {7,IR(735, 6),IR(44878, 13),IR(1, 0)}, // DebugTypedef in opencl_debuginfo_100
    {8,IR(985, 3),IR(44891, 18),IR(1, 0)}, // DebugTypeFunction in opencl_debuginfo_100
    {9,IR(988, 9),IR(44909, 14),IR(1, 0)}, // DebugTypeEnum in opencl_debuginfo_100
    {10,IR(997, 10),IR(44961, 19),IR(1, 0)}, // DebugTypeComposite in opencl_debuginfo_100
    {11,IR(1007, 10),IR(44980, 16),IR(1, 0)}, // DebugTypeMember in opencl_debuginfo_100
    {12,IR(1017, 5),IR(44996, 21),IR(1, 0)}, // DebugTypeInheritance in opencl_debuginfo_100
    {13,IR(36, 2),IR(45017, 21),IR(1, 0)}, // DebugTypePtrToMember in opencl_debuginfo_100
    {14,IR(168, 2),IR(45038, 18),IR(1, 0)}, // DebugTypeTemplate in opencl_debuginfo_100
    {15,IR(774, 6),IR(45056, 27),IR(1, 0)}, // DebugTypeTemplateParameter in opencl_debuginfo_100
    {16,IR(780, 5),IR(45083, 35),IR(1, 0)}, // DebugTypeTemplateTemplateParameter in opencl_debuginfo_100
    {17,IR(785, 5),IR(45118, 31),IR(1, 0)}, // DebugTypeTemplateParameterPack in opencl_debuginfo_100
    {18,IR(1007, 10),IR(45149, 20),IR(1, 0)}, // DebugGlobalVariable in opencl_debuginfo_100
    {19,IR(1022, 8),IR(45169, 25),IR(1, 0)}, // DebugFunctionDeclaration in opencl_debuginfo_100
    {20,IR(1030, 11),IR(45194, 14),IR(1, 0)}, // DebugFunction in opencl_debuginfo_100
    {21,IR(809, 5),IR(45208, 18),IR(1, 0)}, // DebugLexicalBlock in opencl_debuginfo_100
    {22,IR(814, 3),IR(45226, 31),IR(1, 0)}, // DebugLexicalBlockDiscriminator in opencl_debuginfo_100
    {23,IR(817, 2),IR(45257, 11),IR(1, 0)}, // DebugScope in opencl_debuginfo_100
    {24,IR(0, 0),IR(45268, 13),IR(1, 0)}, // DebugNoScope in opencl_debuginfo_100
    {25,IR(819, 3),IR(45281, 15),IR(1, 0)}, // DebugInlinedAt in opencl_debuginfo_100
    {26,IR(1041, 8),IR(45338, 19),IR(1, 0)}, // DebugLocalVariable in opencl_debuginfo_100
    {27,IR(36, 2),IR(45357, 21),IR(1, 0)}, // DebugInlinedVariable in opencl_debuginfo_100
    {28,IR(33, 3),IR(45378, 13),IR(1, 0)}, // DebugDeclare in opencl_debuginfo_100
    {29,IR(902, 4),IR(45391, 11),IR(1, 0)}, // DebugValue in opencl_debuginfo_100
    {30,IR(1049, 2),IR(45435, 15),IR(1, 0)}, // DebugOperation in opencl_debuginfo_100
    {31,IR(683, 1),IR(45450, 16),IR(1, 0)}, // DebugExpression in opencl_debuginfo_100
    {32,IR(834, 4),IR(45466, 14),IR(1, 0)}, // DebugMacroDef in opencl_debuginfo_100
    {33,IR(814, 3),IR(45480, 16),IR(1, 0)}, // DebugMacroUndef in opencl_debuginfo_100
    {34,IR(1051, 7),IR(47235, 20),IR(1, 0)}, // DebugImportedEntity in opencl_debuginfo_100
    {35,IR(817, 2),IR(47255, 12),IR(1, 0)}, // DebugSource in opencl_debuginfo_100
    {36,IR(1058, 8),IR(47840, 17),IR(1, 0)}, // DebugModuleINTEL in opencl_debuginfo_100
    {0,IR(10, 1),IR(47857, 5),IR(1, 0)}, // acos in opencl_std_100
    {1,IR(10, 1),IR(47862, 6),IR(1, 0)}, // acosh in opencl_std_100
    {2,IR(10, 1),IR(47868, 7),IR(1, 0)}, // acospi in opencl_std_100
    {3,IR(10, 1),IR(47875, 5),IR(1, 0)}, // asin in opencl_std_100
    {4,IR(10, 1),IR(47880, 6),IR(1, 0)}, // asinh in opencl_std_100
    {5,IR(10, 1),IR(47886, 7),IR(1, 0)}, // asinpi in opencl_std_100
    {6,IR(10, 1),IR(47893, 5),IR(1, 0)}, // atan in opencl_std_100
    {7,IR(36, 2),IR(47898, 6),IR(1, 0)}, // atan2 in opencl_std_100
    {8,IR(10, 1),IR(47904, 6),IR(1, 0)}, // atanh in opencl_std_100
    {9,IR(10, 1),IR(47910, 7),IR(1, 0)}, // atanpi in opencl_std_100
    {10,IR(36, 2),IR(47917, 8),IR(1, 0)}, // atan2pi in opencl_std_100
    {11,IR(10, 1),IR(47925, 5),IR(1, 0)}, // cbrt in opencl_std_100
    {12,IR(10, 1),IR(47930, 5),IR(1, 0)}, // ceil in opencl_std_100
    {13,IR(36, 2),IR(47935, 9),IR(1, 0)}, // copysign in opencl_std_100
    {14,IR(10, 1),IR(47944, 4),IR(1, 0)}, // cos in opencl_std_100
    {15,IR(10, 1),IR(47948, 5),IR(1, 0)}, // cosh in opencl_std_100
    {16,IR(10, 1),IR(47953, 6),IR(1, 0)}, // cospi in opencl_std_100
    {17,IR(10, 1),IR(47959, 5),IR(1, 0)}, // erfc in opencl_std_100
    {18,IR(10, 1),IR(47964, 4),IR(1, 0)}, // erf in opencl_std_100
    {19,IR(10, 1),IR(47968, 4),IR(1, 0)}, // exp in opencl_std_100
    {20,IR(10, 1),IR(47972, 5),IR(1, 0)}, // exp2 in opencl_std_100
    {21,IR(10, 1),IR(47977, 6),IR(1, 0)}, // exp10 in opencl_std_100
    {22,IR(10, 1),IR(47983, 6),IR(1, 0)}, // expm1 in opencl_std_100
    {23,IR(10, 1),IR(47989, 5),IR(1, 0)}, // fabs in opencl_std_100
    {24,IR(36, 2),IR(47994, 5),IR(1, 0)}, // fdim in opencl_std_100
    {25,IR(10, 1),IR(47999, 6),IR(1, 0)}, // floor in opencl_std_100
    {26,IR(33, 3),IR(48005, 4),IR(1, 0)}, // fma in opencl_std_100
    {27,IR(36, 2),IR(48009, 5),IR(1, 0)}, // fmax in opencl_std_100
    {28,IR(36, 2),IR(48014, 5),IR(1, 0)}, // fmin in opencl_std_100
    {29,IR(36, 2),IR(48019, 5),IR(1, 0)}, // fmod in opencl_std_100
    {30,IR(36, 2),IR(48024, 6),IR(1, 0)}, // fract in opencl_std_100
    {31,IR(36, 2),IR(48030, 6),IR(1, 0)}, // frexp in opencl_std_100
    {32,IR(36, 2),IR(48036, 6),IR(1, 0)}, // hypot in opencl_std_100
    {33,IR(10, 1),IR(48042, 6),IR(1, 0)}, // ilogb in opencl_std_100
    {34,IR(36, 2),IR(48048, 6),IR(1, 0)}, // ldexp in opencl_std_100
    {35,IR(10, 1),IR(48054, 7),IR(1, 0)}, // lgamma in opencl_std_100
    {36,IR(36, 2),IR(48061, 9),IR(1, 0)}, // lgamma_r in opencl_std_100
    {37,IR(10, 1),IR(48070, 4),IR(1, 0)}, // log in opencl_std_100
    {38,IR(10, 1),IR(48074, 5),IR(1, 0)}, // log2 in opencl_std_100
    {39,IR(10, 1),IR(48079, 6),IR(1, 0)}, // log10 in opencl_std_100
    {40,IR(10, 1),IR(48085, 6),IR(1, 0)}, // log1p in opencl_std_100
    {41,IR(10, 1),IR(48091, 5),IR(1, 0)}, // logb in opencl_std_100
    {42,IR(33, 3),IR(48096, 4),IR(1, 0)}, // mad in opencl_std_100
    {43,IR(36, 2),IR(48100, 7),IR(1, 0)}, // maxmag in opencl_std_100
    {44,IR(36, 2),IR(48107, 7),IR(1, 0)}, // minmag in opencl_std_100
    {45,IR(36, 2),IR(48114, 5),IR(1, 0)}, // modf in opencl_std_100
    {46,IR(10, 1),IR(48119, 4),IR(1, 0)}, // nan in opencl_std_100
    {47,IR(36, 2),IR(48123, 10),IR(1, 0)}, // nextafter in opencl_std_100
    {48,IR(36, 2),IR(48133, 4),IR(1, 0)}, // pow in opencl_std_100
    {49,IR(36, 2),IR(48137, 5),IR(1, 0)}, // pown in opencl_std_100
    {50,IR(36, 2),IR(48142, 5),IR(1, 0)}, // powr in opencl_std_100
    {51,IR(36, 2),IR(48147, 10),IR(1, 0)}, // remainder in opencl_std_100
    {52,IR(33, 3),IR(48157, 7),IR(1, 0)}, // remquo in opencl_std_100
    {53,IR(10, 1),IR(48164, 5),IR(1, 0)}, // rint in opencl_std_100
    {54,IR(36, 2),IR(48169, 6),IR(1, 0)}, // rootn in opencl_std_100
    {55,IR(10, 1),IR(48175, 6),IR(1, 0)}, // round in opencl_std_100
    {56,IR(10, 1),IR(48181, 6),IR(1, 0)}, // rsqrt in opencl_std_100
    {57,IR(10, 1),IR(48187, 4),IR(1, 0)}, // sin in opencl_std_100
    {58,IR(36, 2),IR(48191, 7),IR(1, 0)}, // sincos in opencl_std_100
    {59,IR(10, 1),IR(48198, 5),IR(1, 0)}, // sinh in opencl_std_100
    {60,IR(10, 1),IR(48203, 6),IR(1, 0)}, // sinpi in opencl_std_100
    {61,IR(10, 1),IR(48209, 5),IR(1, 0)}, // sqrt in opencl_std_100
    {62,IR(10, 1),IR(48214, 4),IR(1, 0)}, // tan in opencl_std_100
    {63,IR(10, 1),IR(48218, 5),IR(1, 0)}, // tanh in opencl_std_100
    {64,IR(10, 1),IR(48223, 6),IR(1, 0)}, // tanpi in opencl_std_100
    {65,IR(10, 1),IR(48229, 7),IR(1, 0)}, // tgamma in opencl_std_100
    {66,IR(10, 1),IR(48236, 6),IR(1, 0)}, // trunc in opencl_std_100
    {67,IR(10, 1),IR(48242, 9),IR(1, 0)}, // half_cos in opencl_std_100
    {68,IR(36, 2),IR(48251, 12),IR(1, 0)}, // half_divide in opencl_std_100
    {69,IR(10, 1),IR(48263, 9),IR(1, 0)}, // half_exp in opencl_std_100
    {70,IR(10, 1),IR(48272, 10),IR(1, 0)}, // half_exp2 in opencl_std_100
    {71,IR(10, 1),IR(48282, 11),IR(1, 0)}, // half_exp10 in opencl_std_100
    {72,IR(10, 1),IR(48293, 9),IR(1, 0)}, // half_log in opencl_std_100
    {73,IR(10, 1),IR(48302, 10),IR(1, 0)}, // half_log2 in opencl_std_100
    {74,IR(10, 1),IR(48312, 11),IR(1, 0)}, // half_log10 in opencl_std_100
    {75,IR(36, 2),IR(48323, 10),IR(1, 0)}, // half_powr in opencl_std_100
    {76,IR(10, 1),IR(48333, 11),IR(1, 0)}, // half_recip in opencl_std_100
    {77,IR(10, 1),IR(48344, 11),IR(1, 0)}, // half_rsqrt in opencl_std_100
    {78,IR(10, 1),IR(48355, 9),IR(1, 0)}, // half_sin in opencl_std_100
    {79,IR(10, 1),IR(48364, 10),IR(1, 0)}, // half_sqrt in opencl_std_100
    {80,IR(10, 1),IR(48374, 9),IR(1, 0)}, // half_tan in opencl_std_100
    {81,IR(10, 1),IR(48383, 11),IR(1, 0)}, // native_cos in opencl_std_100
    {82,IR(36, 2),IR(48394, 14),IR(1, 0)}, // native_divide in opencl_std_100
    {83,IR(10, 1),IR(48408, 11),IR(1, 0)}, // native_exp in opencl_std_100
    {84,IR(10, 1),IR(48419, 12),IR(1, 0)}, // native_exp2 in opencl_std_100
    {85,IR(10, 1),IR(48431, 13),IR(1, 0)}, // native_exp10 in opencl_std_100
    {86,IR(10, 1),IR(48444, 11),IR(1, 0)}, // native_log in opencl_std_100
    {87,IR(10, 1),IR(48455, 12),IR(1, 0)}, // native_log2 in opencl_std_100
    {88,IR(10, 1),IR(48467, 13),IR(1, 0)}, // native_log10 in opencl_std_100
    {89,IR(36, 2),IR(48480, 12),IR(1, 0)}, // native_powr in opencl_std_100
    {90,IR(10, 1),IR(48492, 13),IR(1, 0)}, // native_recip in opencl_std_100
    {91,IR(10, 1),IR(48505, 13),IR(1, 0)}, // native_rsqrt in opencl_std_100
    {92,IR(10, 1),IR(48518, 11),IR(1, 0)}, // native_sin in opencl_std_100
    {93,IR(10, 1),IR(48529, 12),IR(1, 0)}, // native_sqrt in opencl_std_100
    {94,IR(10, 1),IR(48541, 11),IR(1, 0)}, // native_tan in opencl_std_100
    {95,IR(33, 3),IR(48552, 7),IR(1, 0)}, // fclamp in opencl_std_100
    {96,IR(10, 1),IR(48559, 8),IR(1, 0)}, // degrees in opencl_std_100
    {97,IR(36, 2),IR(48567, 12),IR(1, 0)}, // fmax_common in opencl_std_100
    {98,IR(36, 2),IR(48579, 12),IR(1, 0)}, // fmin_common in opencl_std_100
    {99,IR(33, 3),IR(48591, 4),IR(1, 0)}, // mix in opencl_std_100
    {100,IR(10, 1),IR(48595, 8),IR(1, 0)}, // radians in opencl_std_100
    {101,IR(36, 2),IR(48603, 5),IR(1, 0)}, // step in opencl_std_100
    {102,IR(33, 3),IR(48608, 11),IR(1, 0)}, // smoothstep in opencl_std_100
    {103,IR(10, 1),IR(48619, 5),IR(1, 0)}, // sign in opencl_std_100
    {104,IR(36, 2),IR(48624, 6),IR(1, 0)}, // cross in opencl_std_100
    {105,IR(36, 2),IR(48630, 9),IR(1, 0)}, // distance in opencl_std_100
    {106,IR(10, 1),IR(48639, 7),IR(1, 0)}, // length in opencl_std_100
    {107,IR(10, 1),IR(48646, 10),IR(1, 0)}, // normalize in opencl_std_100
    {108,IR(36, 2),IR(48656, 14),IR(1, 0)}, // fast_distance in opencl_std_100
    {109,IR(10, 1),IR(48670, 12),IR(1, 0)}, // fast_length in opencl_std_100
    {110,IR(10, 1),IR(48682, 15),IR(1, 0)}, // fast_normalize in opencl_std_100
    {141,IR(10, 1),IR(48697, 6),IR(1, 0)}, // s_abs in opencl_std_100
    {142,IR(36, 2),IR(48703, 11),IR(1, 0)}, // s_abs_diff in opencl_std_100
    {143,IR(36, 2),IR(48714, 10),IR(1, 0)}, // s_add_sat in opencl_std_100
    {144,IR(36, 2),IR(48724, 10),IR(1, 0)}, // u_add_sat in opencl_std_100
    {145,IR(36, 2),IR(48734, 7),IR(1, 0)}, // s_hadd in opencl_std_100
    {146,IR(36, 2),IR(48741, 7),IR(1, 0)}, // u_hadd in opencl_std_100
    {147,IR(36, 2),IR(48748, 8),IR(1, 0)}, // s_rhadd in opencl_std_100
    {148,IR(36, 2),IR(48756, 8),IR(1, 0)}, // u_rhadd in opencl_std_100
    {149,IR(33, 3),IR(48764, 8),IR(1, 0)}, // s_clamp in opencl_std_100
    {150,IR(33, 3),IR(48772, 8),IR(1, 0)}, // u_clamp in opencl_std_100
    {151,IR(10, 1),IR(48780, 4),IR(1, 0)}, // clz in opencl_std_100
    {152,IR(10, 1),IR(48784, 4),IR(1, 0)}, // ctz in opencl_std_100
    {153,IR(33, 3),IR(48788, 9),IR(1, 0)}, // s_mad_hi in opencl_std_100
    {154,IR(33, 3),IR(48797, 10),IR(1, 0)}, // u_mad_sat in opencl_std_100
    {155,IR(33, 3),IR(48807, 10),IR(1, 0)}, // s_mad_sat in opencl_std_100
    {156,IR(36, 2),IR(48817, 6),IR(1, 0)}, // s_max in opencl_std_100
    {157,IR(36, 2),IR(48823, 6),IR(1, 0)}, // u_max in opencl_std_100
    {158,IR(36, 2),IR(48829, 6),IR(1, 0)}, // s_min in opencl_std_100
    {159,IR(36, 2),IR(48835, 6),IR(1, 0)}, // u_min in opencl_std_100
    {160,IR(36, 2),IR(48841, 9),IR(1, 0)}, // s_mul_hi in opencl_std_100
    {161,IR(36, 2),IR(48850, 7),IR(1, 0)}, // rotate in opencl_std_100
    {162,IR(36, 2),IR(48857, 10),IR(1, 0)}, // s_sub_sat in opencl_std_100
    {163,IR(36, 2),IR(48867, 10),IR(1, 0)}, // u_sub_sat in opencl_std_100
    {164,IR(36, 2),IR(48877, 11),IR(1, 0)}, // u_upsample in opencl_std_100
    {165,IR(36, 2),IR(48888, 11),IR(1, 0)}, // s_upsample in opencl_std_100
    {166,IR(10, 1),IR(48899, 9),IR(1, 0)}, // popcount in opencl_std_100
    {167,IR(33, 3),IR(48908, 8),IR(1, 0)}, // s_mad24 in opencl_std_100
    {168,IR(33, 3),IR(48916, 8),IR(1, 0)}, // u_mad24 in opencl_std_100
    {169,IR(36, 2),IR(48924, 8),IR(1, 0)}, // s_mul24 in opencl_std_100
    {170,IR(36, 2),IR(48932, 8),IR(1, 0)}, // u_mul24 in opencl_std_100
    {171,IR(1066, 3),IR(48940, 7),IR(1, 0)}, // vloadn in opencl_std_100
    {172,IR(33, 3),IR(48947, 8),IR(1, 0)}, // vstoren in opencl_std_100
    {173,IR(36, 2),IR(48955, 11),IR(1, 0)}, // vload_half in opencl_std_100
    {174,IR(1066, 3),IR(48966, 12),IR(1, 0)}, // vload_halfn in opencl_std_100
    {175,IR(33, 3),IR(48978, 12),IR(1, 0)}, // vstore_half in opencl_std_100
    {176,IR(1069, 4),IR(48990, 14),IR(1, 0)}, // vstore_half_r in opencl_std_100
    {177,IR(33, 3),IR(49004, 13),IR(1, 0)}, // vstore_halfn in opencl_std_100
    {178,IR(1069, 4),IR(49017, 15),IR(1, 0)}, // vstore_halfn_r in opencl_std_100
    {179,IR(1066, 3),IR(49032, 13),IR(1, 0)}, // vloada_halfn in opencl_std_100
    {180,IR(33, 3),IR(49045, 14),IR(1, 0)}, // vstorea_halfn in opencl_std_100
    {181,IR(1069, 4),IR(49059, 16),IR(1, 0)}, // vstorea_halfn_r in opencl_std_100
    {182,IR(36, 2),IR(49075, 8),IR(1, 0)}, // shuffle in opencl_std_100
    {183,IR(33, 3),IR(49083, 9),IR(1, 0)}, // shuffle2 in opencl_std_100
    {184,IR(168, 2),IR(49092, 7),IR(1, 0)}, // printf in opencl_std_100
    {185,IR(36, 2),IR(49099, 9),IR(1, 0)}, // prefetch in opencl_std_100
    {186,IR(33, 3),IR(49108, 10),IR(1, 0)}, // bitselect in opencl_std_100
    {187,IR(33, 3),IR(49118, 7),IR(1, 0)}, // select in opencl_std_100
    {201,IR(10, 1),IR(49125, 6),IR(1, 0)}, // u_abs in opencl_std_100
    {202,IR(36, 2),IR(49131, 11),IR(1, 0)}, // u_abs_diff in opencl_std_100
    {203,IR(36, 2),IR(49142, 9),IR(1, 0)}, // u_mul_hi in opencl_std_100
    {204,IR(33, 3),IR(49151, 9),IR(1, 0)}, // u_mad_hi in opencl_std_100
    {1,IR(10, 1),IR(49160, 17),IR(1, 0)}, // CubeFaceIndexAMD in spv_amd_gcn_shader
    {2,IR(10, 1),IR(49177, 17),IR(1, 0)}, // CubeFaceCoordAMD in spv_amd_gcn_shader
    {3,IR(0, 0),IR(49194, 8),IR(1, 0)}, // TimeAMD in spv_amd_gcn_shader
    {1,IR(36, 2),IR(49202, 22),IR(1, 0)}, // SwizzleInvocationsAMD in spv_amd_shader_ballot
    {2,IR(36, 2),IR(49224, 28),IR(1, 0)}, // SwizzleInvocationsMaskedAMD in spv_amd_shader_ballot
    {3,IR(33, 3),IR(49252, 19),IR(1, 0)}, // WriteInvocationAMD in spv_amd_shader_ballot
    {4,IR(10, 1),IR(49271, 9),IR(1, 0)}, // MbcntAMD in spv_amd_shader_ballot
    {1,IR(36, 2),IR(49280, 23),IR(1, 0)}, // InterpolateAtVertexAMD in spv_amd_shader_explicit_vertex_parameter
    {1,IR(33, 3),IR(49303, 9),IR(1, 0)}, // FMin3AMD in spv_amd_shader_trinary_minmax
    {2,IR(33, 3),IR(49312, 9),IR(1, 0)}, // UMin3AMD in spv_amd_shader_trinary_minmax
    {3,IR(33, 3),IR(49321, 9),IR(1, 0)}, // SMin3AMD in spv_amd_shader_trinary_minmax
    {4,IR(33, 3),IR(49330, 9),IR(1, 0)}, // FMax3AMD in spv_amd_shader_trinary_minmax
    {5,IR(33, 3),IR(49339, 9),IR(1, 0)}, // UMax3AMD in spv_amd_shader_trinary_minmax
    {6,IR(33, 3),IR(49348, 9),IR(1, 0)}, // SMax3AMD in spv_amd_shader_trinary_minmax
    {7,IR(33, 3),IR(49357, 9),IR(1, 0)}, // FMid3AMD in spv_amd_shader_trinary_minmax
    {8,IR(33, 3),IR(49366, 9),IR(1, 0)}, // UMid3AMD in spv_amd_shader_trinary_minmax
    {9,IR(33, 3),IR(49375, 9),IR(1, 0)}, // SMid3AMD in spv_amd_shader_trinary_minmax
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
    {IR(44651, 21), 1}, // DebugCompilationUnit in debuginfo
    {IR(45378, 13), 28}, // DebugDeclare in debuginfo
    {IR(45450, 16), 31}, // DebugExpression in debuginfo
    {IR(45194, 14), 20}, // DebugFunction in debuginfo
    {IR(45169, 25), 19}, // DebugFunctionDeclaration in debuginfo
    {IR(45149, 20), 18}, // DebugGlobalVariable in debuginfo
    {IR(44637, 14), 0}, // DebugInfoNone in debuginfo
    {IR(45281, 15), 25}, // DebugInlinedAt in debuginfo
    {IR(45357, 21), 27}, // DebugInlinedVariable in debuginfo
    {IR(45208, 18), 21}, // DebugLexicalBlock in debuginfo
    {IR(45226, 31), 22}, // DebugLexicalBlockDiscriminator in debuginfo
    {IR(45338, 19), 26}, // DebugLocalVariable in debuginfo
    {IR(45466, 14), 32}, // DebugMacroDef in debuginfo
    {IR(45480, 16), 33}, // DebugMacroUndef in debuginfo
    {IR(45268, 13), 24}, // DebugNoScope in debuginfo
    {IR(45435, 15), 30}, // DebugOperation in debuginfo
    {IR(45257, 11), 23}, // DebugScope in debuginfo
    {IR(44847, 15), 5}, // DebugTypeArray in debuginfo
    {IR(44724, 15), 2}, // DebugTypeBasic in debuginfo
    {IR(44961, 19), 10}, // DebugTypeComposite in debuginfo
    {IR(44909, 14), 9}, // DebugTypeEnum in debuginfo
    {IR(44891, 18), 8}, // DebugTypeFunction in debuginfo
    {IR(44996, 21), 12}, // DebugTypeInheritance in debuginfo
    {IR(44980, 16), 11}, // DebugTypeMember in debuginfo
    {IR(44773, 17), 3}, // DebugTypePointer in debuginfo
    {IR(45017, 21), 13}, // DebugTypePtrToMember in debuginfo
    {IR(44828, 19), 4}, // DebugTypeQualifier in debuginfo
    {IR(45038, 18), 14}, // DebugTypeTemplate in debuginfo
    {IR(45056, 27), 15}, // DebugTypeTemplateParameter in debuginfo
    {IR(45118, 31), 17}, // DebugTypeTemplateParameterPack in debuginfo
    {IR(45083, 35), 16}, // DebugTypeTemplateTemplateParameter in debuginfo
    {IR(44862, 16), 6}, // DebugTypeVector in debuginfo
    {IR(44878, 13), 7}, // DebugTypedef in debuginfo
    {IR(45391, 11), 29}, // DebugValue in debuginfo
    {IR(45590, 5), 50}, // Acos in glsl_std_450
    {IR(45621, 6), 56}, // Acosh in glsl_std_450
    {IR(45585, 5), 49}, // Asin in glsl_std_450
    {IR(45615, 6), 55}, // Asinh in glsl_std_450
    {IR(45595, 5), 51}, // Atan in glsl_std_450
    {IR(45633, 6), 58}, // Atan2 in glsl_std_450
    {IR(45627, 6), 57}, // Atanh in glsl_std_450
    {IR(45546, 5), 42}, // Ceil in glsl_std_450
    {IR(45577, 4), 47}, // Cos in glsl_std_450
    {IR(45605, 5), 53}, // Cosh in glsl_std_450
    {IR(46017, 6), 101}, // Cross in glsl_std_450
    {IR(45565, 8), 45}, // Degrees in glsl_std_450
    {IR(45678, 12), 66}, // Determinant in glsl_std_450
    {IR(46008, 9), 100}, // Distance in glsl_std_450
    {IR(45643, 4), 60}, // Exp in glsl_std_450
    {IR(45651, 5), 62}, // Exp2 in glsl_std_450
    {IR(45518, 5), 37}, // FAbs in glsl_std_450
    {IR(45750, 7), 76}, // FClamp in glsl_std_450
    {IR(45735, 5), 73}, // FMax in glsl_std_450
    {IR(45720, 5), 70}, // FMin in glsl_std_450
    {IR(45771, 5), 79}, // FMix in glsl_std_450
    {IR(45528, 6), 39}, // FSign in glsl_std_450
    {IR(46033, 12), 103}, // FaceForward in glsl_std_450
    {IR(46061, 9), 106}, // FindILsb in glsl_std_450
    {IR(46070, 9), 107}, // FindSMsb in glsl_std_450
    {IR(46079, 9), 108}, // FindUMsb in glsl_std_450
    {IR(45540, 6), 41}, // Floor in glsl_std_450
    {IR(45797, 4), 83}, // Fma in glsl_std_450
    {IR(45551, 6), 43}, // Fract in glsl_std_450
    {IR(45801, 6), 84}, // Frexp in glsl_std_450
    {IR(45807, 12), 85}, // FrexpStruct in glsl_std_450
    {IR(45776, 5), 80}, // IMix in glsl_std_450
    {IR(46088, 22), 109}, // InterpolateAtCentroid in glsl_std_450
    {IR(46130, 20), 111}, // InterpolateAtOffset in glsl_std_450
    {IR(46110, 20), 110}, // InterpolateAtSample in glsl_std_450
    {IR(45666, 12), 65}, // InverseSqrt in glsl_std_450
    {IR(45819, 6), 86}, // Ldexp in glsl_std_450
    {IR(46001, 7), 99}, // Length in glsl_std_450
    {IR(45647, 4), 61}, // Log in glsl_std_450
    {IR(45656, 5), 63}, // Log2 in glsl_std_450
    {IR(45690, 14), 67}, // MatrixInverse in glsl_std_450
    {IR(45704, 5), 68}, // Modf in glsl_std_450
    {IR(45709, 11), 69}, // ModfStruct in glsl_std_450
    {IR(46160, 7), 114}, // NClamp in glsl_std_450
    {IR(46155, 5), 113}, // NMax in glsl_std_450
    {IR(46150, 5), 112}, // NMin in glsl_std_450
    {IR(46023, 10), 102}, // Normalize in glsl_std_450
    {IR(45892, 15), 92}, // PackDouble2x32 in glsl_std_450
    {IR(45879, 13), 91}, // PackHalf2x16 in glsl_std_450
    {IR(45851, 14), 89}, // PackSnorm2x16 in glsl_std_450
    {IR(45825, 13), 87}, // PackSnorm4x8 in glsl_std_450
    {IR(45865, 14), 90}, // PackUnorm2x16 in glsl_std_450
    {IR(45838, 13), 88}, // PackUnorm4x8 in glsl_std_450
    {IR(45639, 4), 59}, // Pow in glsl_std_450
    {IR(45557, 8), 44}, // Radians in glsl_std_450
    {IR(46045, 8), 104}, // Reflect in glsl_std_450
    {IR(46053, 8), 105}, // Refract in glsl_std_450
    {IR(45496, 6), 34}, // Round in glsl_std_450
    {IR(45502, 10), 35}, // RoundEven in glsl_std_450
    {IR(45523, 5), 38}, // SAbs in glsl_std_450
    {IR(45764, 7), 78}, // SClamp in glsl_std_450
    {IR(45745, 5), 75}, // SMax in glsl_std_450
    {IR(45730, 5), 72}, // SMin in glsl_std_450
    {IR(45534, 6), 40}, // SSign in glsl_std_450
    {IR(45573, 4), 46}, // Sin in glsl_std_450
    {IR(45600, 5), 52}, // Sinh in glsl_std_450
    {IR(45786, 11), 82}, // SmoothStep in glsl_std_450
    {IR(45661, 5), 64}, // Sqrt in glsl_std_450
    {IR(45781, 5), 81}, // Step in glsl_std_450
    {IR(45581, 4), 48}, // Tan in glsl_std_450
    {IR(45610, 5), 54}, // Tanh in glsl_std_450
    {IR(45512, 6), 36}, // Trunc in glsl_std_450
    {IR(45757, 7), 77}, // UClamp in glsl_std_450
    {IR(45740, 5), 74}, // UMax in glsl_std_450
    {IR(45725, 5), 71}, // UMin in glsl_std_450
    {IR(45984, 17), 98}, // UnpackDouble2x32 in glsl_std_450
    {IR(45939, 15), 95}, // UnpackHalf2x16 in glsl_std_450
    {IR(45907, 16), 93}, // UnpackSnorm2x16 in glsl_std_450
    {IR(45954, 15), 96}, // UnpackSnorm4x8 in glsl_std_450
    {IR(45923, 16), 94}, // UnpackUnorm2x16 in glsl_std_450
    {IR(45969, 15), 97}, // UnpackUnorm4x8 in glsl_std_450
    {IR(46167, 13), 116}, // ArgumentInfo in nonsemantic_clspvreflection
    {IR(46262, 24), 121}, // ArgumentPodPushConstant in nonsemantic_clspvreflection
    {IR(46218, 25), 119}, // ArgumentPodStorageBuffer in nonsemantic_clspvreflection
    {IR(46243, 19), 120}, // ArgumentPodUniform in nonsemantic_clspvreflection
    {IR(46696, 28), 140}, // ArgumentPointerPushConstant in nonsemantic_clspvreflection
    {IR(46724, 23), 141}, // ArgumentPointerUniform in nonsemantic_clspvreflection
    {IR(46286, 21), 122}, // ArgumentSampledImage in nonsemantic_clspvreflection
    {IR(46328, 16), 124}, // ArgumentSampler in nonsemantic_clspvreflection
    {IR(46180, 22), 117}, // ArgumentStorageBuffer in nonsemantic_clspvreflection
    {IR(46307, 21), 123}, // ArgumentStorageImage in nonsemantic_clspvreflection
    {IR(46984, 27), 148}, // ArgumentStorageTexelBuffer in nonsemantic_clspvreflection
    {IR(46202, 16), 118}, // ArgumentUniform in nonsemantic_clspvreflection
    {IR(47011, 27), 149}, // ArgumentUniformTexelBuffer in nonsemantic_clspvreflection
    {IR(46344, 18), 125}, // ArgumentWorkgroup in nonsemantic_clspvreflection
    {IR(47038, 32), 150}, // ConstantDataPointerPushConstant in nonsemantic_clspvreflection
    {IR(46592, 26), 135}, // ConstantDataStorageBuffer in nonsemantic_clspvreflection
    {IR(46618, 20), 136}, // ConstantDataUniform in nonsemantic_clspvreflection
    {IR(46862, 45), 145}, // ImageArgumentInfoChannelDataTypePushConstant in nonsemantic_clspvreflection
    {IR(46944, 40), 147}, // ImageArgumentInfoChannelDataTypeUniform in nonsemantic_clspvreflection
    {IR(46820, 42), 144}, // ImageArgumentInfoChannelOrderPushConstant in nonsemantic_clspvreflection
    {IR(46907, 37), 146}, // ImageArgumentInfoChannelOrderUniform in nonsemantic_clspvreflection
    {IR(4508, 7), 115}, // Kernel in nonsemantic_clspvreflection
    {IR(7933, 15), 137}, // LiteralSampler in nonsemantic_clspvreflection
    {IR(47179, 34), 155}, // NormalizedSamplerMaskPushConstant in nonsemantic_clspvreflection
    {IR(47147, 32), 154}, // PrintfBufferPointerPushConstant in nonsemantic_clspvreflection
    {IR(47121, 26), 153}, // PrintfBufferStorageBuffer in nonsemantic_clspvreflection
    {IR(47110, 11), 152}, // PrintfInfo in nonsemantic_clspvreflection
    {IR(47070, 40), 151}, // ProgramScopeVariablePointerPushConstant in nonsemantic_clspvreflection
    {IR(46782, 38), 143}, // ProgramScopeVariablePointerRelocation in nonsemantic_clspvreflection
    {IR(46747, 35), 142}, // ProgramScopeVariablesStorageBuffer in nonsemantic_clspvreflection
    {IR(46638, 30), 138}, // PropertyRequiredWorkgroupSize in nonsemantic_clspvreflection
    {IR(46458, 30), 130}, // PushConstantEnqueuedLocalSize in nonsemantic_clspvreflection
    {IR(46433, 25), 129}, // PushConstantGlobalOffset in nonsemantic_clspvreflection
    {IR(46488, 23), 131}, // PushConstantGlobalSize in nonsemantic_clspvreflection
    {IR(46536, 26), 133}, // PushConstantNumWorkgroups in nonsemantic_clspvreflection
    {IR(46562, 30), 134}, // PushConstantRegionGroupOffset in nonsemantic_clspvreflection
    {IR(46511, 25), 132}, // PushConstantRegionOffset in nonsemantic_clspvreflection
    {IR(46388, 25), 127}, // SpecConstantGlobalOffset in nonsemantic_clspvreflection
    {IR(46668, 28), 139}, // SpecConstantSubgroupMaxSize in nonsemantic_clspvreflection
    {IR(46413, 20), 128}, // SpecConstantWorkDim in nonsemantic_clspvreflection
    {IR(46362, 26), 126}, // SpecConstantWorkgroupSize in nonsemantic_clspvreflection
    {IR(47213, 22), 156}, // WorkgroupVariableSize in nonsemantic_clspvreflection
    {IR(47334, 21), 197}, // DebugBuildIdentifier in nonsemantic_shader_debuginfo_100
    {IR(44651, 21), 158}, // DebugCompilationUnit in nonsemantic_shader_debuginfo_100
    {IR(45378, 13), 185}, // DebugDeclare in nonsemantic_shader_debuginfo_100
    {IR(47372, 16), 199}, // DebugEntryPoint in nonsemantic_shader_debuginfo_100
    {IR(45450, 16), 188}, // DebugExpression in nonsemantic_shader_debuginfo_100
    {IR(45194, 14), 177}, // DebugFunction in nonsemantic_shader_debuginfo_100
    {IR(45169, 25), 176}, // DebugFunctionDeclaration in nonsemantic_shader_debuginfo_100
    {IR(47267, 24), 193}, // DebugFunctionDefinition in nonsemantic_shader_debuginfo_100
    {IR(45149, 20), 175}, // DebugGlobalVariable in nonsemantic_shader_debuginfo_100
    {IR(47235, 20), 191}, // DebugImportedEntity in nonsemantic_shader_debuginfo_100
    {IR(44637, 14), 157}, // DebugInfoNone in nonsemantic_shader_debuginfo_100
    {IR(45281, 15), 182}, // DebugInlinedAt in nonsemantic_shader_debuginfo_100
    {IR(45357, 21), 184}, // DebugInlinedVariable in nonsemantic_shader_debuginfo_100
    {IR(45208, 18), 178}, // DebugLexicalBlock in nonsemantic_shader_debuginfo_100
    {IR(45226, 31), 179}, // DebugLexicalBlockDiscriminator in nonsemantic_shader_debuginfo_100
    {IR(47312, 10), 195}, // DebugLine in nonsemantic_shader_debuginfo_100
    {IR(45338, 19), 183}, // DebugLocalVariable in nonsemantic_shader_debuginfo_100
    {IR(45466, 14), 189}, // DebugMacroDef in nonsemantic_shader_debuginfo_100
    {IR(45480, 16), 190}, // DebugMacroUndef in nonsemantic_shader_debuginfo_100
    {IR(47322, 12), 196}, // DebugNoLine in nonsemantic_shader_debuginfo_100
    {IR(45268, 13), 181}, // DebugNoScope in nonsemantic_shader_debuginfo_100
    {IR(45435, 15), 187}, // DebugOperation in nonsemantic_shader_debuginfo_100
    {IR(45257, 11), 180}, // DebugScope in nonsemantic_shader_debuginfo_100
    {IR(47255, 12), 192}, // DebugSource in nonsemantic_shader_debuginfo_100
    {IR(47291, 21), 194}, // DebugSourceContinued in nonsemantic_shader_debuginfo_100
    {IR(47355, 17), 198}, // DebugStoragePath in nonsemantic_shader_debuginfo_100
    {IR(44847, 15), 162}, // DebugTypeArray in nonsemantic_shader_debuginfo_100
    {IR(44724, 15), 159}, // DebugTypeBasic in nonsemantic_shader_debuginfo_100
    {IR(44961, 19), 167}, // DebugTypeComposite in nonsemantic_shader_debuginfo_100
    {IR(44909, 14), 166}, // DebugTypeEnum in nonsemantic_shader_debuginfo_100
    {IR(44891, 18), 165}, // DebugTypeFunction in nonsemantic_shader_debuginfo_100
    {IR(44996, 21), 169}, // DebugTypeInheritance in nonsemantic_shader_debuginfo_100
    {IR(47388, 16), 200}, // DebugTypeMatrix in nonsemantic_shader_debuginfo_100
    {IR(44980, 16), 168}, // DebugTypeMember in nonsemantic_shader_debuginfo_100
    {IR(44773, 17), 160}, // DebugTypePointer in nonsemantic_shader_debuginfo_100
    {IR(45017, 21), 170}, // DebugTypePtrToMember in nonsemantic_shader_debuginfo_100
    {IR(44828, 19), 161}, // DebugTypeQualifier in nonsemantic_shader_debuginfo_100
    {IR(45038, 18), 171}, // DebugTypeTemplate in nonsemantic_shader_debuginfo_100
    {IR(45056, 27), 172}, // DebugTypeTemplateParameter in nonsemantic_shader_debuginfo_100
    {IR(45118, 31), 174}, // DebugTypeTemplateParameterPack in nonsemantic_shader_debuginfo_100
    {IR(45083, 35), 173}, // DebugTypeTemplateTemplateParameter in nonsemantic_shader_debuginfo_100
    {IR(44862, 16), 163}, // DebugTypeVector in nonsemantic_shader_debuginfo_100
    {IR(44878, 13), 164}, // DebugTypedef in nonsemantic_shader_debuginfo_100
    {IR(45391, 11), 186}, // DebugValue in nonsemantic_shader_debuginfo_100
    {IR(47404, 14), 201}, // Configuration in nonsemantic_vkspreflection
    {IR(47480, 20), 206}, // DescriptorSetBuffer in nonsemantic_vkspreflection
    {IR(47500, 19), 207}, // DescriptorSetImage in nonsemantic_vkspreflection
    {IR(47519, 21), 208}, // DescriptorSetSampler in nonsemantic_vkspreflection
    {IR(47443, 14), 204}, // PushConstants in nonsemantic_vkspreflection
    {IR(47457, 23), 205}, // SpecializationMapEntry in nonsemantic_vkspreflection
    {IR(47418, 13), 202}, // StartCounter in nonsemantic_vkspreflection
    {IR(47431, 12), 203}, // StopCounter in nonsemantic_vkspreflection
    {IR(44651, 21), 210}, // DebugCompilationUnit in opencl_debuginfo_100
    {IR(45378, 13), 237}, // DebugDeclare in opencl_debuginfo_100
    {IR(45450, 16), 240}, // DebugExpression in opencl_debuginfo_100
    {IR(45194, 14), 229}, // DebugFunction in opencl_debuginfo_100
    {IR(45169, 25), 228}, // DebugFunctionDeclaration in opencl_debuginfo_100
    {IR(45149, 20), 227}, // DebugGlobalVariable in opencl_debuginfo_100
    {IR(47235, 20), 243}, // DebugImportedEntity in opencl_debuginfo_100
    {IR(44637, 14), 209}, // DebugInfoNone in opencl_debuginfo_100
    {IR(45281, 15), 234}, // DebugInlinedAt in opencl_debuginfo_100
    {IR(45357, 21), 236}, // DebugInlinedVariable in opencl_debuginfo_100
    {IR(45208, 18), 230}, // DebugLexicalBlock in opencl_debuginfo_100
    {IR(45226, 31), 231}, // DebugLexicalBlockDiscriminator in opencl_debuginfo_100
    {IR(45338, 19), 235}, // DebugLocalVariable in opencl_debuginfo_100
    {IR(45466, 14), 241}, // DebugMacroDef in opencl_debuginfo_100
    {IR(45480, 16), 242}, // DebugMacroUndef in opencl_debuginfo_100
    {IR(47840, 17), 245}, // DebugModuleINTEL in opencl_debuginfo_100
    {IR(45268, 13), 233}, // DebugNoScope in opencl_debuginfo_100
    {IR(45435, 15), 239}, // DebugOperation in opencl_debuginfo_100
    {IR(45257, 11), 232}, // DebugScope in opencl_debuginfo_100
    {IR(47255, 12), 244}, // DebugSource in opencl_debuginfo_100
    {IR(44847, 15), 214}, // DebugTypeArray in opencl_debuginfo_100
    {IR(44724, 15), 211}, // DebugTypeBasic in opencl_debuginfo_100
    {IR(44961, 19), 219}, // DebugTypeComposite in opencl_debuginfo_100
    {IR(44909, 14), 218}, // DebugTypeEnum in opencl_debuginfo_100
    {IR(44891, 18), 217}, // DebugTypeFunction in opencl_debuginfo_100
    {IR(44996, 21), 221}, // DebugTypeInheritance in opencl_debuginfo_100
    {IR(44980, 16), 220}, // DebugTypeMember in opencl_debuginfo_100
    {IR(44773, 17), 212}, // DebugTypePointer in opencl_debuginfo_100
    {IR(45017, 21), 222}, // DebugTypePtrToMember in opencl_debuginfo_100
    {IR(44828, 19), 213}, // DebugTypeQualifier in opencl_debuginfo_100
    {IR(45038, 18), 223}, // DebugTypeTemplate in opencl_debuginfo_100
    {IR(45056, 27), 224}, // DebugTypeTemplateParameter in opencl_debuginfo_100
    {IR(45118, 31), 226}, // DebugTypeTemplateParameterPack in opencl_debuginfo_100
    {IR(45083, 35), 225}, // DebugTypeTemplateTemplateParameter in opencl_debuginfo_100
    {IR(44862, 16), 215}, // DebugTypeVector in opencl_debuginfo_100
    {IR(44878, 13), 216}, // DebugTypedef in opencl_debuginfo_100
    {IR(45391, 11), 238}, // DebugValue in opencl_debuginfo_100
    {IR(47857, 5), 246}, // acos in opencl_std_100
    {IR(47862, 6), 247}, // acosh in opencl_std_100
    {IR(47868, 7), 248}, // acospi in opencl_std_100
    {IR(47875, 5), 249}, // asin in opencl_std_100
    {IR(47880, 6), 250}, // asinh in opencl_std_100
    {IR(47886, 7), 251}, // asinpi in opencl_std_100
    {IR(47893, 5), 252}, // atan in opencl_std_100
    {IR(47898, 6), 253}, // atan2 in opencl_std_100
    {IR(47917, 8), 256}, // atan2pi in opencl_std_100
    {IR(47904, 6), 254}, // atanh in opencl_std_100
    {IR(47910, 7), 255}, // atanpi in opencl_std_100
    {IR(49108, 10), 402}, // bitselect in opencl_std_100
    {IR(47925, 5), 257}, // cbrt in opencl_std_100
    {IR(47930, 5), 258}, // ceil in opencl_std_100
    {IR(48780, 4), 367}, // clz in opencl_std_100
    {IR(47935, 9), 259}, // copysign in opencl_std_100
    {IR(47944, 4), 260}, // cos in opencl_std_100
    {IR(47948, 5), 261}, // cosh in opencl_std_100
    {IR(47953, 6), 262}, // cospi in opencl_std_100
    {IR(48624, 6), 350}, // cross in opencl_std_100
    {IR(48784, 4), 368}, // ctz in opencl_std_100
    {IR(48559, 8), 342}, // degrees in opencl_std_100
    {IR(48630, 9), 351}, // distance in opencl_std_100
    {IR(47964, 4), 264}, // erf in opencl_std_100
    {IR(47959, 5), 263}, // erfc in opencl_std_100
    {IR(47968, 4), 265}, // exp in opencl_std_100
    {IR(47977, 6), 267}, // exp10 in opencl_std_100
    {IR(47972, 5), 266}, // exp2 in opencl_std_100
    {IR(47983, 6), 268}, // expm1 in opencl_std_100
    {IR(47989, 5), 269}, // fabs in opencl_std_100
    {IR(48656, 14), 354}, // fast_distance in opencl_std_100
    {IR(48670, 12), 355}, // fast_length in opencl_std_100
    {IR(48682, 15), 356}, // fast_normalize in opencl_std_100
    {IR(48552, 7), 341}, // fclamp in opencl_std_100
    {IR(47994, 5), 270}, // fdim in opencl_std_100
    {IR(47999, 6), 271}, // floor in opencl_std_100
    {IR(48005, 4), 272}, // fma in opencl_std_100
    {IR(48009, 5), 273}, // fmax in opencl_std_100
    {IR(48567, 12), 343}, // fmax_common in opencl_std_100
    {IR(48014, 5), 274}, // fmin in opencl_std_100
    {IR(48579, 12), 344}, // fmin_common in opencl_std_100
    {IR(48019, 5), 275}, // fmod in opencl_std_100
    {IR(48024, 6), 276}, // fract in opencl_std_100
    {IR(48030, 6), 277}, // frexp in opencl_std_100
    {IR(48242, 9), 313}, // half_cos in opencl_std_100
    {IR(48251, 12), 314}, // half_divide in opencl_std_100
    {IR(48263, 9), 315}, // half_exp in opencl_std_100
    {IR(48282, 11), 317}, // half_exp10 in opencl_std_100
    {IR(48272, 10), 316}, // half_exp2 in opencl_std_100
    {IR(48293, 9), 318}, // half_log in opencl_std_100
    {IR(48312, 11), 320}, // half_log10 in opencl_std_100
    {IR(48302, 10), 319}, // half_log2 in opencl_std_100
    {IR(48323, 10), 321}, // half_powr in opencl_std_100
    {IR(48333, 11), 322}, // half_recip in opencl_std_100
    {IR(48344, 11), 323}, // half_rsqrt in opencl_std_100
    {IR(48355, 9), 324}, // half_sin in opencl_std_100
    {IR(48364, 10), 325}, // half_sqrt in opencl_std_100
    {IR(48374, 9), 326}, // half_tan in opencl_std_100
    {IR(48036, 6), 278}, // hypot in opencl_std_100
    {IR(48042, 6), 279}, // ilogb in opencl_std_100
    {IR(48048, 6), 280}, // ldexp in opencl_std_100
    {IR(48639, 7), 352}, // length in opencl_std_100
    {IR(48054, 7), 281}, // lgamma in opencl_std_100
    {IR(48061, 9), 282}, // lgamma_r in opencl_std_100
    {IR(48070, 4), 283}, // log in opencl_std_100
    {IR(48079, 6), 285}, // log10 in opencl_std_100
    {IR(48085, 6), 286}, // log1p in opencl_std_100
    {IR(48074, 5), 284}, // log2 in opencl_std_100
    {IR(48091, 5), 287}, // logb in opencl_std_100
    {IR(48096, 4), 288}, // mad in opencl_std_100
    {IR(48100, 7), 289}, // maxmag in opencl_std_100
    {IR(48107, 7), 290}, // minmag in opencl_std_100
    {IR(48591, 4), 345}, // mix in opencl_std_100
    {IR(48114, 5), 291}, // modf in opencl_std_100
    {IR(48119, 4), 292}, // nan in opencl_std_100
    {IR(48383, 11), 327}, // native_cos in opencl_std_100
    {IR(48394, 14), 328}, // native_divide in opencl_std_100
    {IR(48408, 11), 329}, // native_exp in opencl_std_100
    {IR(48431, 13), 331}, // native_exp10 in opencl_std_100
    {IR(48419, 12), 330}, // native_exp2 in opencl_std_100
    {IR(48444, 11), 332}, // native_log in opencl_std_100
    {IR(48467, 13), 334}, // native_log10 in opencl_std_100
    {IR(48455, 12), 333}, // native_log2 in opencl_std_100
    {IR(48480, 12), 335}, // native_powr in opencl_std_100
    {IR(48492, 13), 336}, // native_recip in opencl_std_100
    {IR(48505, 13), 337}, // native_rsqrt in opencl_std_100
    {IR(48518, 11), 338}, // native_sin in opencl_std_100
    {IR(48529, 12), 339}, // native_sqrt in opencl_std_100
    {IR(48541, 11), 340}, // native_tan in opencl_std_100
    {IR(48123, 10), 293}, // nextafter in opencl_std_100
    {IR(48646, 10), 353}, // normalize in opencl_std_100
    {IR(48899, 9), 382}, // popcount in opencl_std_100
    {IR(48133, 4), 294}, // pow in opencl_std_100
    {IR(48137, 5), 295}, // pown in opencl_std_100
    {IR(48142, 5), 296}, // powr in opencl_std_100
    {IR(49099, 9), 401}, // prefetch in opencl_std_100
    {IR(49092, 7), 400}, // printf in opencl_std_100
    {IR(48595, 8), 346}, // radians in opencl_std_100
    {IR(48147, 10), 297}, // remainder in opencl_std_100
    {IR(48157, 7), 298}, // remquo in opencl_std_100
    {IR(48164, 5), 299}, // rint in opencl_std_100
    {IR(48169, 6), 300}, // rootn in opencl_std_100
    {IR(48850, 7), 377}, // rotate in opencl_std_100
    {IR(48175, 6), 301}, // round in opencl_std_100
    {IR(48181, 6), 302}, // rsqrt in opencl_std_100
    {IR(48697, 6), 357}, // s_abs in opencl_std_100
    {IR(48703, 11), 358}, // s_abs_diff in opencl_std_100
    {IR(48714, 10), 359}, // s_add_sat in opencl_std_100
    {IR(48764, 8), 365}, // s_clamp in opencl_std_100
    {IR(48734, 7), 361}, // s_hadd in opencl_std_100
    {IR(48908, 8), 383}, // s_mad24 in opencl_std_100
    {IR(48788, 9), 369}, // s_mad_hi in opencl_std_100
    {IR(48807, 10), 371}, // s_mad_sat in opencl_std_100
    {IR(48817, 6), 372}, // s_max in opencl_std_100
    {IR(48829, 6), 374}, // s_min in opencl_std_100
    {IR(48924, 8), 385}, // s_mul24 in opencl_std_100
    {IR(48841, 9), 376}, // s_mul_hi in opencl_std_100
    {IR(48748, 8), 363}, // s_rhadd in opencl_std_100
    {IR(48857, 10), 378}, // s_sub_sat in opencl_std_100
    {IR(48888, 11), 381}, // s_upsample in opencl_std_100
    {IR(49118, 7), 403}, // select in opencl_std_100
    {IR(49075, 8), 398}, // shuffle in opencl_std_100
    {IR(49083, 9), 399}, // shuffle2 in opencl_std_100
    {IR(48619, 5), 349}, // sign in opencl_std_100
    {IR(48187, 4), 303}, // sin in opencl_std_100
    {IR(48191, 7), 304}, // sincos in opencl_std_100
    {IR(48198, 5), 305}, // sinh in opencl_std_100
    {IR(48203, 6), 306}, // sinpi in opencl_std_100
    {IR(48608, 11), 348}, // smoothstep in opencl_std_100
    {IR(48209, 5), 307}, // sqrt in opencl_std_100
    {IR(48603, 5), 347}, // step in opencl_std_100
    {IR(48214, 4), 308}, // tan in opencl_std_100
    {IR(48218, 5), 309}, // tanh in opencl_std_100
    {IR(48223, 6), 310}, // tanpi in opencl_std_100
    {IR(48229, 7), 311}, // tgamma in opencl_std_100
    {IR(48236, 6), 312}, // trunc in opencl_std_100
    {IR(49125, 6), 404}, // u_abs in opencl_std_100
    {IR(49131, 11), 405}, // u_abs_diff in opencl_std_100
    {IR(48724, 10), 360}, // u_add_sat in opencl_std_100
    {IR(48772, 8), 366}, // u_clamp in opencl_std_100
    {IR(48741, 7), 362}, // u_hadd in opencl_std_100
    {IR(48916, 8), 384}, // u_mad24 in opencl_std_100
    {IR(49151, 9), 407}, // u_mad_hi in opencl_std_100
    {IR(48797, 10), 370}, // u_mad_sat in opencl_std_100
    {IR(48823, 6), 373}, // u_max in opencl_std_100
    {IR(48835, 6), 375}, // u_min in opencl_std_100
    {IR(48932, 8), 386}, // u_mul24 in opencl_std_100
    {IR(49142, 9), 406}, // u_mul_hi in opencl_std_100
    {IR(48756, 8), 364}, // u_rhadd in opencl_std_100
    {IR(48867, 10), 379}, // u_sub_sat in opencl_std_100
    {IR(48877, 11), 380}, // u_upsample in opencl_std_100
    {IR(48955, 11), 389}, // vload_half in opencl_std_100
    {IR(48966, 12), 390}, // vload_halfn in opencl_std_100
    {IR(49032, 13), 395}, // vloada_halfn in opencl_std_100
    {IR(48940, 7), 387}, // vloadn in opencl_std_100
    {IR(48978, 12), 391}, // vstore_half in opencl_std_100
    {IR(48990, 14), 392}, // vstore_half_r in opencl_std_100
    {IR(49004, 13), 393}, // vstore_halfn in opencl_std_100
    {IR(49017, 15), 394}, // vstore_halfn_r in opencl_std_100
    {IR(49045, 14), 396}, // vstorea_halfn in opencl_std_100
    {IR(49059, 16), 397}, // vstorea_halfn_r in opencl_std_100
    {IR(48947, 8), 388}, // vstoren in opencl_std_100
    {IR(49177, 17), 409}, // CubeFaceCoordAMD in spv_amd_gcn_shader
    {IR(49160, 17), 408}, // CubeFaceIndexAMD in spv_amd_gcn_shader
    {IR(49194, 8), 410}, // TimeAMD in spv_amd_gcn_shader
    {IR(49271, 9), 414}, // MbcntAMD in spv_amd_shader_ballot
    {IR(49202, 22), 411}, // SwizzleInvocationsAMD in spv_amd_shader_ballot
    {IR(49224, 28), 412}, // SwizzleInvocationsMaskedAMD in spv_amd_shader_ballot
    {IR(49252, 19), 413}, // WriteInvocationAMD in spv_amd_shader_ballot
    {IR(49280, 23), 415}, // InterpolateAtVertexAMD in spv_amd_shader_explicit_vertex_parameter
    {IR(49330, 9), 419}, // FMax3AMD in spv_amd_shader_trinary_minmax
    {IR(49357, 9), 422}, // FMid3AMD in spv_amd_shader_trinary_minmax
    {IR(49303, 9), 416}, // FMin3AMD in spv_amd_shader_trinary_minmax
    {IR(49348, 9), 421}, // SMax3AMD in spv_amd_shader_trinary_minmax
    {IR(49375, 9), 424}, // SMid3AMD in spv_amd_shader_trinary_minmax
    {IR(49321, 9), 418}, // SMin3AMD in spv_amd_shader_trinary_minmax
    {IR(49339, 9), 420}, // UMax3AMD in spv_amd_shader_trinary_minmax
    {IR(49366, 9), 423}, // UMid3AMD in spv_amd_shader_trinary_minmax
    {IR(49312, 9), 417}, // UMin3AMD in spv_amd_shader_trinary_minmax
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
  "SPV_EXT_fragment_fully_covered\0" // IR(531, 31)
  "SPV_EXT_fragment_invocation_density\0" // IR(562, 36)
  "SPV_EXT_fragment_shader_interlock\0" // IR(598, 34)
  "SPV_EXT_mesh_shader\0" // IR(632, 20)
  "SPV_EXT_opacity_micromap\0" // IR(652, 25)
  "SPV_EXT_optnone\0" // IR(677, 16)
  "SPV_EXT_physical_storage_buffer\0" // IR(693, 32)
  "SPV_EXT_relaxed_printf_string_address_space\0" // IR(725, 44)
  "SPV_EXT_replicated_composites\0" // IR(769, 30)
  "SPV_EXT_shader_atomic_float16_add\0" // IR(799, 34)
  "SPV_EXT_shader_atomic_float_add\0" // IR(833, 32)
  "SPV_EXT_shader_atomic_float_min_max\0" // IR(865, 36)
  "SPV_EXT_shader_image_int64\0" // IR(901, 27)
  "SPV_EXT_shader_stencil_export\0" // IR(928, 30)
  "SPV_EXT_shader_tile_image\0" // IR(958, 26)
  "SPV_EXT_shader_viewport_index_layer\0" // IR(984, 36)
  "SPV_GOOGLE_decorate_string\0" // IR(1020, 27)
  "SPV_GOOGLE_hlsl_functionality1\0" // IR(1047, 31)
  "SPV_GOOGLE_user_type\0" // IR(1078, 21)
  "SPV_INTEL_2d_block_io\0" // IR(1099, 22)
  "SPV_INTEL_arbitrary_precision_fixed_point\0" // IR(1121, 42)
  "SPV_INTEL_arbitrary_precision_floating_point\0" // IR(1163, 45)
  "SPV_INTEL_arbitrary_precision_integers\0" // IR(1208, 39)
  "SPV_INTEL_bfloat16_conversion\0" // IR(1247, 30)
  "SPV_INTEL_blocking_pipes\0" // IR(1277, 25)
  "SPV_INTEL_cache_controls\0" // IR(1302, 25)
  "SPV_INTEL_debug_module\0" // IR(1327, 23)
  "SPV_INTEL_device_side_avc_motion_estimation\0" // IR(1350, 44)
  "SPV_INTEL_float_controls2\0" // IR(1394, 26)
  "SPV_INTEL_fp_fast_math_mode\0" // IR(1420, 28)
  "SPV_INTEL_fp_max_error\0" // IR(1448, 23)
  "SPV_INTEL_fpga_argument_interfaces\0" // IR(1471, 35)
  "SPV_INTEL_fpga_buffer_location\0" // IR(1506, 31)
  "SPV_INTEL_fpga_cluster_attributes\0" // IR(1537, 34)
  "SPV_INTEL_fpga_dsp_control\0" // IR(1571, 27)
  "SPV_INTEL_fpga_invocation_pipelining_attributes\0" // IR(1598, 48)
  "SPV_INTEL_fpga_latency_control\0" // IR(1646, 31)
  "SPV_INTEL_fpga_loop_controls\0" // IR(1677, 29)
  "SPV_INTEL_fpga_memory_accesses\0" // IR(1706, 31)
  "SPV_INTEL_fpga_memory_attributes\0" // IR(1737, 33)
  "SPV_INTEL_fpga_reg\0" // IR(1770, 19)
  "SPV_INTEL_function_pointers\0" // IR(1789, 28)
  "SPV_INTEL_global_variable_fpga_decorations\0" // IR(1817, 43)
  "SPV_INTEL_global_variable_host_access\0" // IR(1860, 38)
  "SPV_INTEL_inline_assembly\0" // IR(1898, 26)
  "SPV_INTEL_int4\0" // IR(1924, 15)
  "SPV_INTEL_io_pipes\0" // IR(1939, 19)
  "SPV_INTEL_kernel_attributes\0" // IR(1958, 28)
  "SPV_INTEL_long_composites\0" // IR(1986, 26)
  "SPV_INTEL_loop_fuse\0" // IR(2012, 20)
  "SPV_INTEL_masked_gather_scatter\0" // IR(2032, 32)
  "SPV_INTEL_maximum_registers\0" // IR(2064, 28)
  "SPV_INTEL_media_block_io\0" // IR(2092, 25)
  "SPV_INTEL_memory_access_aliasing\0" // IR(2117, 33)
  "SPV_INTEL_optnone\0" // IR(2150, 18)
  "SPV_INTEL_runtime_aligned\0" // IR(2168, 26)
  "SPV_INTEL_shader_integer_functions2\0" // IR(2194, 36)
  "SPV_INTEL_split_barrier\0" // IR(2230, 24)
  "SPV_INTEL_subgroup_buffer_prefetch\0" // IR(2254, 35)
  "SPV_INTEL_subgroup_matrix_multiply_accumulate\0" // IR(2289, 46)
  "SPV_INTEL_subgroups\0" // IR(2335, 20)
  "SPV_INTEL_task_sequence\0" // IR(2355, 24)
  "SPV_INTEL_tensor_float32_conversion\0" // IR(2379, 36)
  "SPV_INTEL_ternary_bitwise_function\0" // IR(2415, 35)
  "SPV_INTEL_unstructured_loop_controls\0" // IR(2450, 37)
  "SPV_INTEL_usm_storage_classes\0" // IR(2487, 30)
  "SPV_INTEL_variable_length_array\0" // IR(2517, 32)
  "SPV_INTEL_vector_compute\0" // IR(2549, 25)
  "SPV_KHR_16bit_storage\0" // IR(2574, 22)
  "SPV_KHR_8bit_storage\0" // IR(2596, 21)
  "SPV_KHR_bfloat16\0" // IR(2617, 17)
  "SPV_KHR_bit_instructions\0" // IR(2634, 25)
  "SPV_KHR_compute_shader_derivatives\0" // IR(2659, 35)
  "SPV_KHR_cooperative_matrix\0" // IR(2694, 27)
  "SPV_KHR_device_group\0" // IR(2721, 21)
  "SPV_KHR_expect_assume\0" // IR(2742, 22)
  "SPV_KHR_float_controls\0" // IR(2764, 23)
  "SPV_KHR_float_controls2\0" // IR(2787, 24)
  "SPV_KHR_fragment_shader_barycentric\0" // IR(2811, 36)
  "SPV_KHR_fragment_shading_rate\0" // IR(2847, 30)
  "SPV_KHR_integer_dot_product\0" // IR(2877, 28)
  "SPV_KHR_linkonce_odr\0" // IR(2905, 21)
  "SPV_KHR_maximal_reconvergence\0" // IR(2926, 30)
  "SPV_KHR_multiview\0" // IR(2956, 18)
  "SPV_KHR_no_integer_wrap_decoration\0" // IR(2974, 35)
  "SPV_KHR_non_semantic_info\0" // IR(3009, 26)
  "SPV_KHR_physical_storage_buffer\0" // IR(3035, 32)
  "SPV_KHR_post_depth_coverage\0" // IR(3067, 28)
  "SPV_KHR_quad_control\0" // IR(3095, 21)
  "SPV_KHR_ray_cull_mask\0" // IR(3116, 22)
  "SPV_KHR_ray_query\0" // IR(3138, 18)
  "SPV_KHR_ray_tracing\0" // IR(3156, 20)
  "SPV_KHR_ray_tracing_position_fetch\0" // IR(3176, 35)
  "SPV_KHR_relaxed_extended_instruction\0" // IR(3211, 37)
  "SPV_KHR_shader_atomic_counter_ops\0" // IR(3248, 34)
  "SPV_KHR_shader_ballot\0" // IR(3282, 22)
  "SPV_KHR_shader_clock\0" // IR(3304, 21)
  "SPV_KHR_shader_draw_parameters\0" // IR(3325, 31)
  "SPV_KHR_storage_buffer_storage_class\0" // IR(3356, 37)
  "SPV_KHR_subgroup_rotate\0" // IR(3393, 24)
  "SPV_KHR_subgroup_uniform_control_flow\0" // IR(3417, 38)
  "SPV_KHR_subgroup_vote\0" // IR(3455, 22)
  "SPV_KHR_terminate_invocation\0" // IR(3477, 29)
  "SPV_KHR_uniform_group_instructions\0" // IR(3506, 35)
  "SPV_KHR_untyped_pointers\0" // IR(3541, 25)
  "SPV_KHR_variable_pointers\0" // IR(3566, 26)
  "SPV_KHR_vulkan_memory_model\0" // IR(3592, 28)
  "SPV_KHR_workgroup_memory_explicit_layout\0" // IR(3620, 41)
  "SPV_NVX_multiview_per_view_attributes\0" // IR(3661, 38)
  "SPV_NV_bindless_texture\0" // IR(3699, 24)
  "SPV_NV_cluster_acceleration_structure\0" // IR(3723, 38)
  "SPV_NV_compute_shader_derivatives\0" // IR(3761, 34)
  "SPV_NV_cooperative_matrix\0" // IR(3795, 26)
  "SPV_NV_cooperative_matrix2\0" // IR(3821, 27)
  "SPV_NV_cooperative_vector\0" // IR(3848, 26)
  "SPV_NV_displacement_micromap\0" // IR(3874, 29)
  "SPV_NV_fragment_shader_barycentric\0" // IR(3903, 35)
  "SPV_NV_geometry_shader_passthrough\0" // IR(3938, 35)
  "SPV_NV_linear_swept_spheres\0" // IR(3973, 28)
  "SPV_NV_mesh_shader\0" // IR(4001, 19)
  "SPV_NV_raw_access_chains\0" // IR(4020, 25)
  "SPV_NV_ray_tracing\0" // IR(4045, 19)
  "SPV_NV_ray_tracing_motion_blur\0" // IR(4064, 31)
  "SPV_NV_sample_mask_override_coverage\0" // IR(4095, 37)
  "SPV_NV_shader_atomic_fp16_vector\0" // IR(4132, 33)
  "SPV_NV_shader_image_footprint\0" // IR(4165, 30)
  "SPV_NV_shader_invocation_reorder\0" // IR(4195, 33)
  "SPV_NV_shader_sm_builtins\0" // IR(4228, 26)
  "SPV_NV_shader_subgroup_partitioned\0" // IR(4254, 35)
  "SPV_NV_shading_rate\0" // IR(4289, 20)
  "SPV_NV_stereo_view_rendering\0" // IR(4309, 29)
  "SPV_NV_tensor_addressing\0" // IR(4338, 25)
  "SPV_NV_viewport_array2\0" // IR(4363, 23)
  "SPV_QCOM_image_processing\0" // IR(4386, 26)
  "SPV_QCOM_image_processing2\0" // IR(4412, 27)
  "SPV_QCOM_tile_shading\0" // IR(4439, 22)
  "SPV_VALIDATOR_ignore_type_decl_unique\0" // IR(4461, 38)
  "ReadOnly\0" // IR(4499, 9)
  "Kernel\0" // IR(4508, 7)
  "WriteOnly\0" // IR(4515, 10)
  "ReadWrite\0" // IR(4525, 10)
  "Logical\0" // IR(4535, 8)
  "Physical32\0" // IR(4543, 11)
  "Addresses\0" // IR(4554, 10)
  "Physical64\0" // IR(4564, 11)
  "PhysicalStorageBuffer64\0" // IR(4575, 24)
  "PhysicalStorageBuffer64EXT\0" // IR(4599, 27)
  "PhysicalStorageBufferAddresses\0" // IR(4626, 31)
  "Position\0" // IR(4657, 9)
  "Shader\0" // IR(4666, 7)
  "PointSize\0" // IR(4673, 10)
  "ClipDistance\0" // IR(4683, 13)
  "CullDistance\0" // IR(4696, 13)
  "VertexId\0" // IR(4709, 9)
  "InstanceId\0" // IR(4718, 11)
  "PrimitiveId\0" // IR(4729, 12)
  "Geometry\0" // IR(4741, 9)
  "Tessellation\0" // IR(4750, 13)
  "RayTracingNV\0" // IR(4763, 13)
  "RayTracingKHR\0" // IR(4776, 14)
  "MeshShadingNV\0" // IR(4790, 14)
  "MeshShadingEXT\0" // IR(4804, 15)
  "InvocationId\0" // IR(4819, 13)
  "Layer\0" // IR(4832, 6)
  "ShaderLayer\0" // IR(4838, 12)
  "ShaderViewportIndexLayerEXT\0" // IR(4850, 28)
  "ViewportIndex\0" // IR(4878, 14)
  "MultiViewport\0" // IR(4892, 14)
  "ShaderViewportIndex\0" // IR(4906, 20)
  "TessLevelOuter\0" // IR(4926, 15)
  "TessLevelInner\0" // IR(4941, 15)
  "TessCoord\0" // IR(4956, 10)
  "PatchVertices\0" // IR(4966, 14)
  "FragCoord\0" // IR(4980, 10)
  "PointCoord\0" // IR(4990, 11)
  "FrontFacing\0" // IR(5001, 12)
  "SampleId\0" // IR(5013, 9)
  "SampleRateShading\0" // IR(5022, 18)
  "SamplePosition\0" // IR(5040, 15)
  "SampleMask\0" // IR(5055, 11)
  "FragDepth\0" // IR(5066, 10)
  "HelperInvocation\0" // IR(5076, 17)
  "NumWorkgroups\0" // IR(5093, 14)
  "WorkgroupSize\0" // IR(5107, 14)
  "WorkgroupId\0" // IR(5121, 12)
  "LocalInvocationId\0" // IR(5133, 18)
  "GlobalInvocationId\0" // IR(5151, 19)
  "LocalInvocationIndex\0" // IR(5170, 21)
  "WorkDim\0" // IR(5191, 8)
  "GlobalSize\0" // IR(5199, 11)
  "EnqueuedWorkgroupSize\0" // IR(5210, 22)
  "GlobalOffset\0" // IR(5232, 13)
  "GlobalLinearId\0" // IR(5245, 15)
  "SubgroupSize\0" // IR(5260, 13)
  "GroupNonUniform\0" // IR(5273, 16)
  "SubgroupBallotKHR\0" // IR(5289, 18)
  "SubgroupMaxSize\0" // IR(5307, 16)
  "NumSubgroups\0" // IR(5323, 13)
  "NumEnqueuedSubgroups\0" // IR(5336, 21)
  "SubgroupId\0" // IR(5357, 11)
  "SubgroupLocalInvocationId\0" // IR(5368, 26)
  "VertexIndex\0" // IR(5394, 12)
  "InstanceIndex\0" // IR(5406, 14)
  "CoreIDARM\0" // IR(5420, 10)
  "CoreBuiltinsARM\0" // IR(5430, 16)
  "CoreCountARM\0" // IR(5446, 13)
  "CoreMaxIDARM\0" // IR(5459, 13)
  "WarpIDARM\0" // IR(5472, 10)
  "WarpMaxIDARM\0" // IR(5482, 13)
  "SubgroupEqMask\0" // IR(5495, 15)
  "SubgroupEqMaskKHR\0" // IR(5510, 18)
  "GroupNonUniformBallot\0" // IR(5528, 22)
  "SubgroupGeMask\0" // IR(5550, 15)
  "SubgroupGeMaskKHR\0" // IR(5565, 18)
  "SubgroupGtMask\0" // IR(5583, 15)
  "SubgroupGtMaskKHR\0" // IR(5598, 18)
  "SubgroupLeMask\0" // IR(5616, 15)
  "SubgroupLeMaskKHR\0" // IR(5631, 18)
  "SubgroupLtMask\0" // IR(5649, 15)
  "SubgroupLtMaskKHR\0" // IR(5664, 18)
  "BaseVertex\0" // IR(5682, 11)
  "DrawParameters\0" // IR(5693, 15)
  "BaseInstance\0" // IR(5708, 13)
  "DrawIndex\0" // IR(5721, 10)
  "PrimitiveShadingRateKHR\0" // IR(5731, 24)
  "FragmentShadingRateKHR\0" // IR(5755, 23)
  "DeviceIndex\0" // IR(5778, 12)
  "DeviceGroup\0" // IR(5790, 12)
  "ViewIndex\0" // IR(5802, 10)
  "MultiView\0" // IR(5812, 10)
  "ShadingRateKHR\0" // IR(5822, 15)
  "TileOffsetQCOM\0" // IR(5837, 15)
  "TileShadingQCOM\0" // IR(5852, 16)
  "TileDimensionQCOM\0" // IR(5868, 18)
  "TileApronSizeQCOM\0" // IR(5886, 18)
  "BaryCoordNoPerspAMD\0" // IR(5904, 20)
  "BaryCoordNoPerspCentroidAMD\0" // IR(5924, 28)
  "BaryCoordNoPerspSampleAMD\0" // IR(5952, 26)
  "BaryCoordSmoothAMD\0" // IR(5978, 19)
  "BaryCoordSmoothCentroidAMD\0" // IR(5997, 27)
  "BaryCoordSmoothSampleAMD\0" // IR(6024, 25)
  "BaryCoordPullModelAMD\0" // IR(6049, 22)
  "FragStencilRefEXT\0" // IR(6071, 18)
  "StencilExportEXT\0" // IR(6089, 17)
  "RemainingRecursionLevelsAMDX\0" // IR(6106, 29)
  "ShaderEnqueueAMDX\0" // IR(6135, 18)
  "ShaderIndexAMDX\0" // IR(6153, 16)
  "ViewportMaskNV\0" // IR(6169, 15)
  "ShaderViewportMaskNV\0" // IR(6184, 21)
  "SecondaryPositionNV\0" // IR(6205, 20)
  "ShaderStereoViewNV\0" // IR(6225, 19)
  "SecondaryViewportMaskNV\0" // IR(6244, 24)
  "PositionPerViewNV\0" // IR(6268, 18)
  "PerViewAttributesNV\0" // IR(6286, 20)
  "ViewportMaskPerViewNV\0" // IR(6306, 22)
  "FullyCoveredEXT\0" // IR(6328, 16)
  "FragmentFullyCoveredEXT\0" // IR(6344, 24)
  "TaskCountNV\0" // IR(6368, 12)
  "PrimitiveCountNV\0" // IR(6380, 17)
  "PrimitiveIndicesNV\0" // IR(6397, 19)
  "ClipDistancePerViewNV\0" // IR(6416, 22)
  "CullDistancePerViewNV\0" // IR(6438, 22)
  "LayerPerViewNV\0" // IR(6460, 15)
  "MeshViewCountNV\0" // IR(6475, 16)
  "MeshViewIndicesNV\0" // IR(6491, 18)
  "BaryCoordKHR\0" // IR(6509, 13)
  "BaryCoordNV\0" // IR(6522, 12)
  "FragmentBarycentricKHR\0" // IR(6534, 23)
  "BaryCoordNoPerspKHR\0" // IR(6557, 20)
  "BaryCoordNoPerspNV\0" // IR(6577, 19)
  "FragSizeEXT\0" // IR(6596, 12)
  "FragmentSizeNV\0" // IR(6608, 15)
  "FragmentDensityEXT\0" // IR(6623, 19)
  "FragInvocationCountEXT\0" // IR(6642, 23)
  "InvocationsPerPixelNV\0" // IR(6665, 22)
  "PrimitivePointIndicesEXT\0" // IR(6687, 25)
  "PrimitiveLineIndicesEXT\0" // IR(6712, 24)
  "PrimitiveTriangleIndicesEXT\0" // IR(6736, 28)
  "CullPrimitiveEXT\0" // IR(6764, 17)
  "LaunchIdKHR\0" // IR(6781, 12)
  "LaunchIdNV\0" // IR(6793, 11)
  "LaunchSizeKHR\0" // IR(6804, 14)
  "LaunchSizeNV\0" // IR(6818, 13)
  "WorldRayOriginKHR\0" // IR(6831, 18)
  "WorldRayOriginNV\0" // IR(6849, 17)
  "WorldRayDirectionKHR\0" // IR(6866, 21)
  "WorldRayDirectionNV\0" // IR(6887, 20)
  "ObjectRayOriginKHR\0" // IR(6907, 19)
  "ObjectRayOriginNV\0" // IR(6926, 18)
  "ObjectRayDirectionKHR\0" // IR(6944, 22)
  "ObjectRayDirectionNV\0" // IR(6966, 21)
  "RayTminKHR\0" // IR(6987, 11)
  "RayTminNV\0" // IR(6998, 10)
  "RayTmaxKHR\0" // IR(7008, 11)
  "RayTmaxNV\0" // IR(7019, 10)
  "InstanceCustomIndexKHR\0" // IR(7029, 23)
  "InstanceCustomIndexNV\0" // IR(7052, 22)
  "ObjectToWorldKHR\0" // IR(7074, 17)
  "ObjectToWorldNV\0" // IR(7091, 16)
  "WorldToObjectKHR\0" // IR(7107, 17)
  "WorldToObjectNV\0" // IR(7124, 16)
  "HitTNV\0" // IR(7140, 7)
  "HitKindKHR\0" // IR(7147, 11)
  "HitKindNV\0" // IR(7158, 10)
  "CurrentRayTimeNV\0" // IR(7168, 17)
  "RayTracingMotionBlurNV\0" // IR(7185, 23)
  "HitTriangleVertexPositionsKHR\0" // IR(7208, 30)
  "RayTracingPositionFetchKHR\0" // IR(7238, 27)
  "HitMicroTriangleVertexPositionsNV\0" // IR(7265, 34)
  "RayTracingDisplacementMicromapNV\0" // IR(7299, 33)
  "HitMicroTriangleVertexBarycentricsNV\0" // IR(7332, 37)
  "IncomingRayFlagsKHR\0" // IR(7369, 20)
  "IncomingRayFlagsNV\0" // IR(7389, 19)
  "RayGeometryIndexKHR\0" // IR(7408, 20)
  "HitIsSphereNV\0" // IR(7428, 14)
  "RayTracingSpheresGeometryNV\0" // IR(7442, 28)
  "HitIsLSSNV\0" // IR(7470, 11)
  "RayTracingLinearSweptSpheresGeometryNV\0" // IR(7481, 39)
  "HitSpherePositionNV\0" // IR(7520, 20)
  "WarpsPerSMNV\0" // IR(7540, 13)
  "ShaderSMBuiltinsNV\0" // IR(7553, 19)
  "SMCountNV\0" // IR(7572, 10)
  "WarpIDNV\0" // IR(7582, 9)
  "SMIDNV\0" // IR(7591, 7)
  "HitLSSPositionsNV\0" // IR(7598, 18)
  "HitKindFrontFacingMicroTriangleNV\0" // IR(7616, 34)
  "HitKindBackFacingMicroTriangleNV\0" // IR(7650, 33)
  "HitSphereRadiusNV\0" // IR(7683, 18)
  "HitLSSRadiiNV\0" // IR(7701, 14)
  "ClusterIDNV\0" // IR(7715, 12)
  "RayTracingClusterAccelerationStructureNV\0" // IR(7727, 41)
  "CullMaskKHR\0" // IR(7768, 12)
  "RayCullMaskKHR\0" // IR(7780, 15)
  "Matrix\0" // IR(7795, 7)
  "Linkage\0" // IR(7802, 8)
  "Vector16\0" // IR(7810, 9)
  "Float16Buffer\0" // IR(7819, 14)
  "Float16\0" // IR(7833, 8)
  "Float64\0" // IR(7841, 8)
  "Int64\0" // IR(7849, 6)
  "Int64Atomics\0" // IR(7855, 13)
  "ImageBasic\0" // IR(7868, 11)
  "ImageReadWrite\0" // IR(7879, 15)
  "ImageMipmap\0" // IR(7894, 12)
  "Pipes\0" // IR(7906, 6)
  "Groups\0" // IR(7912, 7)
  "DeviceEnqueue\0" // IR(7919, 14)
  "LiteralSampler\0" // IR(7933, 15)
  "AtomicStorage\0" // IR(7948, 14)
  "Int16\0" // IR(7962, 6)
  "TessellationPointSize\0" // IR(7968, 22)
  "GeometryPointSize\0" // IR(7990, 18)
  "ImageGatherExtended\0" // IR(8008, 20)
  "StorageImageMultisample\0" // IR(8028, 24)
  "UniformBufferArrayDynamicIndexing\0" // IR(8052, 34)
  "SampledImageArrayDynamicIndexing\0" // IR(8086, 33)
  "StorageBufferArrayDynamicIndexing\0" // IR(8119, 34)
  "StorageImageArrayDynamicIndexing\0" // IR(8153, 33)
  "ImageCubeArray\0" // IR(8186, 15)
  "SampledCubeArray\0" // IR(8201, 17)
  "ImageRect\0" // IR(8218, 10)
  "SampledRect\0" // IR(8228, 12)
  "GenericPointer\0" // IR(8240, 15)
  "Int8\0" // IR(8255, 5)
  "InputAttachment\0" // IR(8260, 16)
  "SparseResidency\0" // IR(8276, 16)
  "MinLod\0" // IR(8292, 7)
  "Sampled1D\0" // IR(8299, 10)
  "Image1D\0" // IR(8309, 8)
  "SampledBuffer\0" // IR(8317, 14)
  "ImageBuffer\0" // IR(8331, 12)
  "ImageMSArray\0" // IR(8343, 13)
  "StorageImageExtendedFormats\0" // IR(8356, 28)
  "ImageQuery\0" // IR(8384, 11)
  "DerivativeControl\0" // IR(8395, 18)
  "InterpolationFunction\0" // IR(8413, 22)
  "TransformFeedback\0" // IR(8435, 18)
  "GeometryStreams\0" // IR(8453, 16)
  "StorageImageReadWithoutFormat\0" // IR(8469, 30)
  "StorageImageWriteWithoutFormat\0" // IR(8499, 31)
  "SubgroupDispatch\0" // IR(8530, 17)
  "NamedBarrier\0" // IR(8547, 13)
  "PipeStorage\0" // IR(8560, 12)
  "GroupNonUniformVote\0" // IR(8572, 20)
  "GroupNonUniformArithmetic\0" // IR(8592, 26)
  "GroupNonUniformShuffle\0" // IR(8618, 23)
  "GroupNonUniformShuffleRelative\0" // IR(8641, 31)
  "GroupNonUniformClustered\0" // IR(8672, 25)
  "GroupNonUniformQuad\0" // IR(8697, 20)
  "UniformDecoration\0" // IR(8717, 18)
  "TileImageColorReadAccessEXT\0" // IR(8735, 28)
  "TileImageDepthReadAccessEXT\0" // IR(8763, 28)
  "TileImageStencilReadAccessEXT\0" // IR(8791, 30)
  "TensorsARM\0" // IR(8821, 11)
  "StorageTensorArrayDynamicIndexingARM\0" // IR(8832, 37)
  "StorageTensorArrayNonUniformIndexingARM\0" // IR(8869, 40)
  "CooperativeMatrixLayoutsARM\0" // IR(8909, 28)
  "WorkgroupMemoryExplicitLayoutKHR\0" // IR(8937, 33)
  "WorkgroupMemoryExplicitLayout8BitAccessKHR\0" // IR(8970, 43)
  "WorkgroupMemoryExplicitLayout16BitAccessKHR\0" // IR(9013, 44)
  "SubgroupVoteKHR\0" // IR(9057, 16)
  "StorageBuffer16BitAccess\0" // IR(9073, 25)
  "StorageUniformBufferBlock16\0" // IR(9098, 28)
  "UniformAndStorageBuffer16BitAccess\0" // IR(9126, 35)
  "StorageUniform16\0" // IR(9161, 17)
  "StoragePushConstant16\0" // IR(9178, 22)
  "StorageInputOutput16\0" // IR(9200, 21)
  "VariablePointersStorageBuffer\0" // IR(9221, 30)
  "VariablePointers\0" // IR(9251, 17)
  "AtomicStorageOps\0" // IR(9268, 17)
  "SampleMaskPostDepthCoverage\0" // IR(9285, 28)
  "StorageBuffer8BitAccess\0" // IR(9313, 24)
  "UniformAndStorageBuffer8BitAccess\0" // IR(9337, 34)
  "StoragePushConstant8\0" // IR(9371, 21)
  "DenormPreserve\0" // IR(9392, 15)
  "DenormFlushToZero\0" // IR(9407, 18)
  "SignedZeroInfNanPreserve\0" // IR(9425, 25)
  "RoundingModeRTE\0" // IR(9450, 16)
  "RoundingModeRTZ\0" // IR(9466, 16)
  "RayQueryProvisionalKHR\0" // IR(9482, 23)
  "RayQueryKHR\0" // IR(9505, 12)
  "UntypedPointersKHR\0" // IR(9517, 19)
  "RayTraversalPrimitiveCullingKHR\0" // IR(9536, 32)
  "TextureSampleWeightedQCOM\0" // IR(9568, 26)
  "TextureBoxFilterQCOM\0" // IR(9594, 21)
  "TextureBlockMatchQCOM\0" // IR(9615, 22)
  "TextureBlockMatch2QCOM\0" // IR(9637, 23)
  "Float16ImageAMD\0" // IR(9660, 16)
  "ImageGatherBiasLodAMD\0" // IR(9676, 22)
  "FragmentMaskAMD\0" // IR(9698, 16)
  "ImageReadWriteLodAMD\0" // IR(9714, 21)
  "Int64ImageEXT\0" // IR(9735, 14)
  "ShaderClockKHR\0" // IR(9749, 15)
  "QuadControlKHR\0" // IR(9764, 15)
  "Int4TypeINTEL\0" // IR(9779, 14)
  "Int4CooperativeMatrixINTEL\0" // IR(9793, 27)
  "CooperativeMatrixKHR\0" // IR(9820, 21)
  "BFloat16TypeKHR\0" // IR(9841, 16)
  "BFloat16DotProductKHR\0" // IR(9857, 22)
  "BFloat16CooperativeMatrixKHR\0" // IR(9879, 29)
  "SampleMaskOverrideCoverageNV\0" // IR(9908, 29)
  "GeometryShaderPassthroughNV\0" // IR(9937, 28)
  "ShaderViewportIndexLayerNV\0" // IR(9965, 27)
  "ImageFootprintNV\0" // IR(9992, 17)
  "FragmentBarycentricNV\0" // IR(10009, 22)
  "ComputeDerivativeGroupQuadsKHR\0" // IR(10031, 31)
  "ComputeDerivativeGroupQuadsNV\0" // IR(10062, 30)
  "ShadingRateNV\0" // IR(10092, 14)
  "GroupNonUniformPartitionedNV\0" // IR(10106, 29)
  "ShaderNonUniform\0" // IR(10135, 17)
  "ShaderNonUniformEXT\0" // IR(10152, 20)
  "RuntimeDescriptorArray\0" // IR(10172, 23)
  "RuntimeDescriptorArrayEXT\0" // IR(10195, 26)
  "InputAttachmentArrayDynamicIndexing\0" // IR(10221, 36)
  "InputAttachmentArrayDynamicIndexingEXT\0" // IR(10257, 39)
  "UniformTexelBufferArrayDynamicIndexing\0" // IR(10296, 39)
  "UniformTexelBufferArrayDynamicIndexingEXT\0" // IR(10335, 42)
  "StorageTexelBufferArrayDynamicIndexing\0" // IR(10377, 39)
  "StorageTexelBufferArrayDynamicIndexingEXT\0" // IR(10416, 42)
  "UniformBufferArrayNonUniformIndexing\0" // IR(10458, 37)
  "UniformBufferArrayNonUniformIndexingEXT\0" // IR(10495, 40)
  "SampledImageArrayNonUniformIndexing\0" // IR(10535, 36)
  "SampledImageArrayNonUniformIndexingEXT\0" // IR(10571, 39)
  "StorageBufferArrayNonUniformIndexing\0" // IR(10610, 37)
  "StorageBufferArrayNonUniformIndexingEXT\0" // IR(10647, 40)
  "StorageImageArrayNonUniformIndexing\0" // IR(10687, 36)
  "StorageImageArrayNonUniformIndexingEXT\0" // IR(10723, 39)
  "InputAttachmentArrayNonUniformIndexing\0" // IR(10762, 39)
  "InputAttachmentArrayNonUniformIndexingEXT\0" // IR(10801, 42)
  "UniformTexelBufferArrayNonUniformIndexing\0" // IR(10843, 42)
  "UniformTexelBufferArrayNonUniformIndexingEXT\0" // IR(10885, 45)
  "StorageTexelBufferArrayNonUniformIndexing\0" // IR(10930, 42)
  "StorageTexelBufferArrayNonUniformIndexingEXT\0" // IR(10972, 45)
  "VulkanMemoryModel\0" // IR(11017, 18)
  "VulkanMemoryModelKHR\0" // IR(11035, 21)
  "VulkanMemoryModelDeviceScope\0" // IR(11056, 29)
  "VulkanMemoryModelDeviceScopeKHR\0" // IR(11085, 32)
  "PhysicalStorageBufferAddressesEXT\0" // IR(11117, 34)
  "ComputeDerivativeGroupLinearKHR\0" // IR(11151, 32)
  "ComputeDerivativeGroupLinearNV\0" // IR(11183, 31)
  "RayTracingProvisionalKHR\0" // IR(11214, 25)
  "CooperativeMatrixNV\0" // IR(11239, 20)
  "FragmentShaderSampleInterlockEXT\0" // IR(11259, 33)
  "FragmentShaderShadingRateInterlockEXT\0" // IR(11292, 38)
  "FragmentShaderPixelInterlockEXT\0" // IR(11330, 32)
  "DemoteToHelperInvocation\0" // IR(11362, 25)
  "DemoteToHelperInvocationEXT\0" // IR(11387, 28)
  "DisplacementMicromapNV\0" // IR(11415, 23)
  "RayTracingOpacityMicromapEXT\0" // IR(11438, 29)
  "ShaderInvocationReorderNV\0" // IR(11467, 26)
  "BindlessTextureNV\0" // IR(11493, 18)
  "RayQueryPositionFetchKHR\0" // IR(11511, 25)
  "CooperativeVectorNV\0" // IR(11536, 20)
  "AtomicFloat16VectorNV\0" // IR(11556, 22)
  "RawAccessChainsNV\0" // IR(11578, 18)
  "CooperativeMatrixReductionsNV\0" // IR(11596, 30)
  "CooperativeMatrixConversionsNV\0" // IR(11626, 31)
  "CooperativeMatrixPerElementOperationsNV\0" // IR(11657, 40)
  "CooperativeMatrixTensorAddressingNV\0" // IR(11697, 36)
  "CooperativeMatrixBlockLoadsNV\0" // IR(11733, 30)
  "CooperativeVectorTrainingNV\0" // IR(11763, 28)
  "TensorAddressingNV\0" // IR(11791, 19)
  "SubgroupShuffleINTEL\0" // IR(11810, 21)
  "SubgroupBufferBlockIOINTEL\0" // IR(11831, 27)
  "SubgroupImageBlockIOINTEL\0" // IR(11858, 26)
  "SubgroupImageMediaBlockIOINTEL\0" // IR(11884, 31)
  "RoundToInfinityINTEL\0" // IR(11915, 21)
  "FloatingPointModeINTEL\0" // IR(11936, 23)
  "IntegerFunctions2INTEL\0" // IR(11959, 23)
  "FunctionPointersINTEL\0" // IR(11982, 22)
  "IndirectReferencesINTEL\0" // IR(12004, 24)
  "AsmINTEL\0" // IR(12028, 9)
  "AtomicFloat32MinMaxEXT\0" // IR(12037, 23)
  "AtomicFloat64MinMaxEXT\0" // IR(12060, 23)
  "AtomicFloat16MinMaxEXT\0" // IR(12083, 23)
  "VectorComputeINTEL\0" // IR(12106, 19)
  "VectorAnyINTEL\0" // IR(12125, 15)
  "ExpectAssumeKHR\0" // IR(12140, 16)
  "SubgroupAvcMotionEstimationINTEL\0" // IR(12156, 33)
  "SubgroupAvcMotionEstimationIntraINTEL\0" // IR(12189, 38)
  "SubgroupAvcMotionEstimationChromaINTEL\0" // IR(12227, 39)
  "VariableLengthArrayINTEL\0" // IR(12266, 25)
  "FunctionFloatControlINTEL\0" // IR(12291, 26)
  "FPGAMemoryAttributesINTEL\0" // IR(12317, 26)
  "FPFastMathModeINTEL\0" // IR(12343, 20)
  "ArbitraryPrecisionIntegersINTEL\0" // IR(12363, 32)
  "ArbitraryPrecisionFloatingPointINTEL\0" // IR(12395, 37)
  "UnstructuredLoopControlsINTEL\0" // IR(12432, 30)
  "FPGALoopControlsINTEL\0" // IR(12462, 22)
  "KernelAttributesINTEL\0" // IR(12484, 22)
  "FPGAKernelAttributesINTEL\0" // IR(12506, 26)
  "FPGAMemoryAccessesINTEL\0" // IR(12532, 24)
  "FPGAClusterAttributesINTEL\0" // IR(12556, 27)
  "LoopFuseINTEL\0" // IR(12583, 14)
  "FPGADSPControlINTEL\0" // IR(12597, 20)
  "MemoryAccessAliasingINTEL\0" // IR(12617, 26)
  "FPGAInvocationPipeliningAttributesINTEL\0" // IR(12643, 40)
  "FPGABufferLocationINTEL\0" // IR(12683, 24)
  "ArbitraryPrecisionFixedPointINTEL\0" // IR(12707, 34)
  "USMStorageClassesINTEL\0" // IR(12741, 23)
  "RuntimeAlignedAttributeINTEL\0" // IR(12764, 29)
  "IOPipesINTEL\0" // IR(12793, 13)
  "BlockingPipesINTEL\0" // IR(12806, 19)
  "FPGARegINTEL\0" // IR(12825, 13)
  "DotProductInputAll\0" // IR(12838, 19)
  "DotProductInputAllKHR\0" // IR(12857, 22)
  "DotProductInput4x8Bit\0" // IR(12879, 22)
  "DotProductInput4x8BitKHR\0" // IR(12901, 25)
  "DotProductInput4x8BitPacked\0" // IR(12926, 28)
  "DotProductInput4x8BitPackedKHR\0" // IR(12954, 31)
  "DotProduct\0" // IR(12985, 11)
  "DotProductKHR\0" // IR(12996, 14)
  "ReplicatedCompositesEXT\0" // IR(13010, 24)
  "BitInstructions\0" // IR(13034, 16)
  "GroupNonUniformRotateKHR\0" // IR(13050, 25)
  "FloatControls2\0" // IR(13075, 15)
  "AtomicFloat32AddEXT\0" // IR(13090, 20)
  "AtomicFloat64AddEXT\0" // IR(13110, 20)
  "LongCompositesINTEL\0" // IR(13130, 20)
  "OptNoneEXT\0" // IR(13150, 11)
  "OptNoneINTEL\0" // IR(13161, 13)
  "AtomicFloat16AddEXT\0" // IR(13174, 20)
  "DebugInfoModuleINTEL\0" // IR(13194, 21)
  "BFloat16ConversionINTEL\0" // IR(13215, 24)
  "SplitBarrierINTEL\0" // IR(13239, 18)
  "ArithmeticFenceEXT\0" // IR(13257, 19)
  "FPGAClusterAttributesV2INTEL\0" // IR(13276, 29)
  "FPGAKernelAttributesv2INTEL\0" // IR(13305, 28)
  "TaskSequenceINTEL\0" // IR(13333, 18)
  "FPMaxErrorINTEL\0" // IR(13351, 16)
  "FPGALatencyControlINTEL\0" // IR(13367, 24)
  "FPGAArgumentInterfacesINTEL\0" // IR(13391, 28)
  "GlobalVariableHostAccessINTEL\0" // IR(13419, 30)
  "GlobalVariableFPGADecorationsINTEL\0" // IR(13449, 35)
  "SubgroupBufferPrefetchINTEL\0" // IR(13484, 28)
  "Subgroup2DBlockIOINTEL\0" // IR(13512, 23)
  "Subgroup2DBlockTransformINTEL\0" // IR(13535, 30)
  "Subgroup2DBlockTransposeINTEL\0" // IR(13565, 30)
  "SubgroupMatrixMultiplyAccumulateINTEL\0" // IR(13595, 38)
  "TernaryBitwiseFunctionINTEL\0" // IR(13633, 28)
  "GroupUniformArithmeticKHR\0" // IR(13661, 26)
  "TensorFloat32RoundingINTEL\0" // IR(13687, 27)
  "MaskedGatherScatterINTEL\0" // IR(13714, 25)
  "CacheControlsINTEL\0" // IR(13739, 19)
  "RegisterLimitsINTEL\0" // IR(13758, 20)
  "Unspecified\0" // IR(13778, 12)
  "Address\0" // IR(13790, 8)
  "Boolean\0" // IR(13798, 8)
  "Float\0" // IR(13806, 6)
  "Signed\0" // IR(13812, 7)
  "SignedChar\0" // IR(13819, 11)
  "Unsigned\0" // IR(13830, 9)
  "UnsignedChar\0" // IR(13839, 13)
  "Class\0" // IR(13852, 6)
  "Structure\0" // IR(13858, 10)
  "Union\0" // IR(13868, 6)
  "ImportedModule\0" // IR(13874, 15)
  "ImportedDeclaration\0" // IR(13889, 20)
  "None\0" // IR(13909, 5)
  "FlagIsProtected\0" // IR(13914, 16)
  "FlagIsPrivate\0" // IR(13930, 14)
  "FlagIsPublic\0" // IR(13944, 13)
  "FlagIsLocal\0" // IR(13957, 12)
  "FlagIsDefinition\0" // IR(13969, 17)
  "FlagFwdDecl\0" // IR(13986, 12)
  "FlagArtificial\0" // IR(13998, 15)
  "FlagExplicit\0" // IR(14013, 13)
  "FlagPrototyped\0" // IR(14026, 15)
  "FlagObjectPointer\0" // IR(14041, 18)
  "FlagStaticMember\0" // IR(14059, 17)
  "FlagIndirectVariable\0" // IR(14076, 21)
  "FlagLValueReference\0" // IR(14097, 20)
  "FlagRValueReference\0" // IR(14117, 20)
  "FlagIsOptimized\0" // IR(14137, 16)
  "FlagIsEnumClass\0" // IR(14153, 16)
  "FlagTypePassByValue\0" // IR(14169, 20)
  "FlagTypePassByReference\0" // IR(14189, 24)
  "Deref\0" // IR(14213, 6)
  "Plus\0" // IR(14219, 5)
  "Minus\0" // IR(14224, 6)
  "SPV_OPERAND_TYPE_LITERAL_INTEGER\0" // IR(14230, 33)
  "PlusUconst\0" // IR(14263, 11)
  "BitPiece\0" // IR(14274, 9)
  "Swap\0" // IR(14283, 5)
  "Xderef\0" // IR(14288, 7)
  "StackValue\0" // IR(14295, 11)
  "Constu\0" // IR(14306, 7)
  "Fragment\0" // IR(14313, 9)
  "ConstType\0" // IR(14322, 10)
  "VolatileType\0" // IR(14332, 13)
  "RestrictType\0" // IR(14345, 13)
  "AtomicType\0" // IR(14358, 11)
  "Float16NV\0" // IR(14369, 10)
  "Float32NV\0" // IR(14379, 10)
  "Float64NV\0" // IR(14389, 10)
  "SignedInt8NV\0" // IR(14399, 13)
  "SignedInt16NV\0" // IR(14412, 14)
  "SignedInt32NV\0" // IR(14426, 14)
  "SignedInt64NV\0" // IR(14440, 14)
  "UnsignedInt8NV\0" // IR(14454, 15)
  "UnsignedInt16NV\0" // IR(14469, 16)
  "UnsignedInt32NV\0" // IR(14485, 16)
  "UnsignedInt64NV\0" // IR(14501, 16)
  "SignedInt8PackedNV\0" // IR(14517, 19)
  "UnsignedInt8PackedNV\0" // IR(14536, 21)
  "FloatE4M3NV\0" // IR(14557, 12)
  "FloatE5M2NV\0" // IR(14569, 12)
  "RowMajorKHR\0" // IR(14581, 12)
  "ColumnMajorKHR\0" // IR(14593, 15)
  "RowBlockedInterleavedARM\0" // IR(14608, 25)
  "ColumnBlockedInterleavedARM\0" // IR(14633, 28)
  "NoneKHR\0" // IR(14661, 8)
  "MatrixASignedComponentsKHR\0" // IR(14669, 27)
  "MatrixBSignedComponentsKHR\0" // IR(14696, 27)
  "MatrixCSignedComponentsKHR\0" // IR(14723, 27)
  "MatrixResultSignedComponentsKHR\0" // IR(14750, 32)
  "SaturatingAccumulationKHR\0" // IR(14782, 26)
  "Row\0" // IR(14808, 4)
  "Column\0" // IR(14812, 7)
  "2x2\0" // IR(14819, 4)
  "MatrixAKHR\0" // IR(14823, 11)
  "MatrixBKHR\0" // IR(14834, 11)
  "MatrixAccumulatorKHR\0" // IR(14845, 21)
  "RowMajorNV\0" // IR(14866, 11)
  "ColumnMajorNV\0" // IR(14877, 14)
  "InferencingOptimalNV\0" // IR(14891, 21)
  "TrainingOptimalNV\0" // IR(14912, 18)
  "RelaxedPrecision\0" // IR(14930, 17)
  "SpecId\0" // IR(14947, 7)
  "Block\0" // IR(14954, 6)
  "BufferBlock\0" // IR(14960, 12)
  "RowMajor\0" // IR(14972, 9)
  "ColMajor\0" // IR(14981, 9)
  "ArrayStride\0" // IR(14990, 12)
  "MatrixStride\0" // IR(15002, 13)
  "GLSLShared\0" // IR(15015, 11)
  "GLSLPacked\0" // IR(15026, 11)
  "CPacked\0" // IR(15037, 8)
  "SPV_OPERAND_TYPE_BUILT_IN\0" // IR(15045, 26)
  "BuiltIn\0" // IR(15071, 8)
  "NoPerspective\0" // IR(15079, 14)
  "Flat\0" // IR(15093, 5)
  "Patch\0" // IR(15098, 6)
  "Centroid\0" // IR(15104, 9)
  "Sample\0" // IR(15113, 7)
  "Invariant\0" // IR(15120, 10)
  "Restrict\0" // IR(15130, 9)
  "Aliased\0" // IR(15139, 8)
  "Volatile\0" // IR(15147, 9)
  "Constant\0" // IR(15156, 9)
  "Coherent\0" // IR(15165, 9)
  "NonWritable\0" // IR(15174, 12)
  "NonReadable\0" // IR(15186, 12)
  "Uniform\0" // IR(15198, 8)
  "SPV_OPERAND_TYPE_SCOPE_ID\0" // IR(15206, 26)
  "UniformId\0" // IR(15232, 10)
  "SaturatedConversion\0" // IR(15242, 20)
  "Stream\0" // IR(15262, 7)
  "Location\0" // IR(15269, 9)
  "Component\0" // IR(15278, 10)
  "Index\0" // IR(15288, 6)
  "Binding\0" // IR(15294, 8)
  "DescriptorSet\0" // IR(15302, 14)
  "Offset\0" // IR(15316, 7)
  "XfbBuffer\0" // IR(15323, 10)
  "XfbStride\0" // IR(15333, 10)
  "SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE\0" // IR(15343, 46)
  "FuncParamAttr\0" // IR(15389, 14)
  "SPV_OPERAND_TYPE_FP_ROUNDING_MODE\0" // IR(15403, 34)
  "FPRoundingMode\0" // IR(15437, 15)
  "SPV_OPERAND_TYPE_FP_FAST_MATH_MODE\0" // IR(15452, 35)
  "FPFastMathMode\0" // IR(15487, 15)
  "SPV_OPERAND_TYPE_LITERAL_STRING\0" // IR(15502, 32)
  "SPV_OPERAND_TYPE_LINKAGE_TYPE\0" // IR(15534, 30)
  "LinkageAttributes\0" // IR(15564, 18)
  "NoContraction\0" // IR(15582, 14)
  "InputAttachmentIndex\0" // IR(15596, 21)
  "Alignment\0" // IR(15617, 10)
  "MaxByteOffset\0" // IR(15627, 14)
  "SPV_OPERAND_TYPE_ID\0" // IR(15641, 20)
  "AlignmentId\0" // IR(15661, 12)
  "MaxByteOffsetId\0" // IR(15673, 16)
  "NoSignedWrap\0" // IR(15689, 13)
  "NoUnsignedWrap\0" // IR(15702, 15)
  "WeightTextureQCOM\0" // IR(15717, 18)
  "BlockMatchTextureQCOM\0" // IR(15735, 22)
  "BlockMatchSamplerQCOM\0" // IR(15757, 22)
  "ExplicitInterpAMD\0" // IR(15779, 18)
  "NodeSharesPayloadLimitsWithAMDX\0" // IR(15797, 32)
  "NodeMaxPayloadsAMDX\0" // IR(15829, 20)
  "TrackFinishWritingAMDX\0" // IR(15849, 23)
  "PayloadNodeNameAMDX\0" // IR(15872, 20)
  "PayloadNodeBaseIndexAMDX\0" // IR(15892, 25)
  "PayloadNodeSparseArrayAMDX\0" // IR(15917, 27)
  "PayloadNodeArraySizeAMDX\0" // IR(15944, 25)
  "PayloadDispatchIndirectAMDX\0" // IR(15969, 28)
  "OverrideCoverageNV\0" // IR(15997, 19)
  "PassthroughNV\0" // IR(16016, 14)
  "ViewportRelativeNV\0" // IR(16030, 19)
  "SecondaryViewportRelativeNV\0" // IR(16049, 28)
  "PerPrimitiveEXT\0" // IR(16077, 16)
  "PerPrimitiveNV\0" // IR(16093, 15)
  "PerViewNV\0" // IR(16108, 10)
  "PerTaskNV\0" // IR(16118, 10)
  "PerVertexKHR\0" // IR(16128, 13)
  "PerVertexNV\0" // IR(16141, 12)
  "NonUniform\0" // IR(16153, 11)
  "NonUniformEXT\0" // IR(16164, 14)
  "RestrictPointer\0" // IR(16178, 16)
  "RestrictPointerEXT\0" // IR(16194, 19)
  "AliasedPointer\0" // IR(16213, 15)
  "AliasedPointerEXT\0" // IR(16228, 18)
  "HitObjectShaderRecordBufferNV\0" // IR(16246, 30)
  "BindlessSamplerNV\0" // IR(16276, 18)
  "BindlessImageNV\0" // IR(16294, 16)
  "BoundSamplerNV\0" // IR(16310, 15)
  "BoundImageNV\0" // IR(16325, 13)
  "SIMTCallINTEL\0" // IR(16338, 14)
  "ReferencedIndirectlyINTEL\0" // IR(16352, 26)
  "ClobberINTEL\0" // IR(16378, 13)
  "SideEffectsINTEL\0" // IR(16391, 17)
  "VectorComputeVariableINTEL\0" // IR(16408, 27)
  "FuncParamIOKindINTEL\0" // IR(16435, 21)
  "VectorComputeFunctionINTEL\0" // IR(16456, 27)
  "StackCallINTEL\0" // IR(16483, 15)
  "GlobalVariableOffsetINTEL\0" // IR(16498, 26)
  "CounterBuffer\0" // IR(16524, 14)
  "HlslCounterBufferGOOGLE\0" // IR(16538, 24)
  "UserSemantic\0" // IR(16562, 13)
  "HlslSemanticGOOGLE\0" // IR(16575, 19)
  "UserTypeGOOGLE\0" // IR(16594, 15)
  "FunctionRoundingModeINTEL\0" // IR(16609, 26)
  "SPV_OPERAND_TYPE_FPDENORM_MODE\0" // IR(16635, 31)
  "FunctionDenormModeINTEL\0" // IR(16666, 24)
  "RegisterINTEL\0" // IR(16690, 14)
  "MemoryINTEL\0" // IR(16704, 12)
  "NumbanksINTEL\0" // IR(16716, 14)
  "BankwidthINTEL\0" // IR(16730, 15)
  "MaxPrivateCopiesINTEL\0" // IR(16745, 22)
  "SinglepumpINTEL\0" // IR(16767, 16)
  "DoublepumpINTEL\0" // IR(16783, 16)
  "MaxReplicatesINTEL\0" // IR(16799, 19)
  "SimpleDualPortINTEL\0" // IR(16818, 20)
  "MergeINTEL\0" // IR(16838, 11)
  "SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER\0" // IR(16849, 42)
  "BankBitsINTEL\0" // IR(16891, 14)
  "ForcePow2DepthINTEL\0" // IR(16905, 20)
  "StridesizeINTEL\0" // IR(16925, 16)
  "WordsizeINTEL\0" // IR(16941, 14)
  "TrueDualPortINTEL\0" // IR(16955, 18)
  "BurstCoalesceINTEL\0" // IR(16973, 19)
  "CacheSizeINTEL\0" // IR(16992, 15)
  "DontStaticallyCoalesceINTEL\0" // IR(17007, 28)
  "PrefetchINTEL\0" // IR(17035, 14)
  "StallEnableINTEL\0" // IR(17049, 17)
  "FuseLoopsInFunctionINTEL\0" // IR(17066, 25)
  "MathOpDSPModeINTEL\0" // IR(17091, 19)
  "AliasScopeINTEL\0" // IR(17110, 16)
  "NoAliasINTEL\0" // IR(17126, 13)
  "InitiationIntervalINTEL\0" // IR(17139, 24)
  "MaxConcurrencyINTEL\0" // IR(17163, 20)
  "PipelineEnableINTEL\0" // IR(17183, 20)
  "BufferLocationINTEL\0" // IR(17203, 20)
  "IOPipeStorageINTEL\0" // IR(17223, 19)
  "SPV_OPERAND_TYPE_FPOPERATION_MODE\0" // IR(17242, 34)
  "FunctionFloatingPointModeINTEL\0" // IR(17276, 31)
  "SingleElementVectorINTEL\0" // IR(17307, 25)
  "VectorComputeCallableFunctionINTEL\0" // IR(17332, 35)
  "MediaBlockIOINTEL\0" // IR(17367, 18)
  "StallFreeINTEL\0" // IR(17385, 15)
  "SPV_OPERAND_TYPE_LITERAL_FLOAT\0" // IR(17400, 31)
  "FPMaxErrorDecorationINTEL\0" // IR(17431, 26)
  "LatencyControlLabelINTEL\0" // IR(17457, 25)
  "LatencyControlConstraintINTEL\0" // IR(17482, 30)
  "ConduitKernelArgumentINTEL\0" // IR(17512, 27)
  "RegisterMapKernelArgumentINTEL\0" // IR(17539, 31)
  "MMHostInterfaceAddressWidthINTEL\0" // IR(17570, 33)
  "MMHostInterfaceDataWidthINTEL\0" // IR(17603, 30)
  "MMHostInterfaceLatencyINTEL\0" // IR(17633, 28)
  "SPV_OPERAND_TYPE_ACCESS_QUALIFIER\0" // IR(17661, 34)
  "MMHostInterfaceReadWriteModeINTEL\0" // IR(17695, 34)
  "MMHostInterfaceMaxBurstINTEL\0" // IR(17729, 29)
  "MMHostInterfaceWaitRequestINTEL\0" // IR(17758, 32)
  "StableKernelArgumentINTEL\0" // IR(17790, 26)
  "SPV_OPERAND_TYPE_HOST_ACCESS_QUALIFIER\0" // IR(17816, 39)
  "HostAccessINTEL\0" // IR(17855, 16)
  "SPV_OPERAND_TYPE_INITIALIZATION_MODE_QUALIFIER\0" // IR(17871, 47)
  "InitModeINTEL\0" // IR(17918, 14)
  "ImplementInRegisterMapINTEL\0" // IR(17932, 28)
  "SPV_OPERAND_TYPE_LOAD_CACHE_CONTROL\0" // IR(17960, 36)
  "CacheControlLoadINTEL\0" // IR(17996, 22)
  "SPV_OPERAND_TYPE_STORE_CACHE_CONTROL\0" // IR(18018, 37)
  "CacheControlStoreINTEL\0" // IR(18055, 23)
  "1D\0" // IR(18078, 3)
  "2D\0" // IR(18081, 3)
  "3D\0" // IR(18084, 3)
  "Cube\0" // IR(18087, 5)
  "Rect\0" // IR(18092, 5)
  "Buffer\0" // IR(18097, 7)
  "SubpassData\0" // IR(18104, 12)
  "TileImageDataEXT\0" // IR(18116, 17)
  "Invocations\0" // IR(18133, 12)
  "SpacingEqual\0" // IR(18145, 13)
  "SpacingFractionalEven\0" // IR(18158, 22)
  "SpacingFractionalOdd\0" // IR(18180, 21)
  "VertexOrderCw\0" // IR(18201, 14)
  "VertexOrderCcw\0" // IR(18215, 15)
  "PixelCenterInteger\0" // IR(18230, 19)
  "OriginUpperLeft\0" // IR(18249, 16)
  "OriginLowerLeft\0" // IR(18265, 16)
  "EarlyFragmentTests\0" // IR(18281, 19)
  "PointMode\0" // IR(18300, 10)
  "Xfb\0" // IR(18310, 4)
  "DepthReplacing\0" // IR(18314, 15)
  "DepthGreater\0" // IR(18329, 13)
  "DepthLess\0" // IR(18342, 10)
  "DepthUnchanged\0" // IR(18352, 15)
  "LocalSize\0" // IR(18367, 10)
  "LocalSizeHint\0" // IR(18377, 14)
  "InputPoints\0" // IR(18391, 12)
  "InputLines\0" // IR(18403, 11)
  "InputLinesAdjacency\0" // IR(18414, 20)
  "Triangles\0" // IR(18434, 10)
  "InputTrianglesAdjacency\0" // IR(18444, 24)
  "Quads\0" // IR(18468, 6)
  "Isolines\0" // IR(18474, 9)
  "OutputVertices\0" // IR(18483, 15)
  "OutputPoints\0" // IR(18498, 13)
  "OutputLineStrip\0" // IR(18511, 16)
  "OutputTriangleStrip\0" // IR(18527, 20)
  "VecTypeHint\0" // IR(18547, 12)
  "ContractionOff\0" // IR(18559, 15)
  "Initializer\0" // IR(18574, 12)
  "Finalizer\0" // IR(18586, 10)
  "SubgroupsPerWorkgroup\0" // IR(18596, 22)
  "SubgroupsPerWorkgroupId\0" // IR(18618, 24)
  "LocalSizeId\0" // IR(18642, 12)
  "LocalSizeHintId\0" // IR(18654, 16)
  "NonCoherentColorAttachmentReadEXT\0" // IR(18670, 34)
  "NonCoherentDepthAttachmentReadEXT\0" // IR(18704, 34)
  "NonCoherentStencilAttachmentReadEXT\0" // IR(18738, 36)
  "SubgroupUniformControlFlowKHR\0" // IR(18774, 30)
  "PostDepthCoverage\0" // IR(18804, 18)
  "NonCoherentTileAttachmentReadQCOM\0" // IR(18822, 34)
  "TileShadingRateQCOM\0" // IR(18856, 20)
  "EarlyAndLateFragmentTestsAMD\0" // IR(18876, 29)
  "StencilRefReplacingEXT\0" // IR(18905, 23)
  "CoalescingAMDX\0" // IR(18928, 15)
  "IsApiEntryAMDX\0" // IR(18943, 15)
  "MaxNodeRecursionAMDX\0" // IR(18958, 21)
  "StaticNumWorkgroupsAMDX\0" // IR(18979, 24)
  "MaxNumWorkgroupsAMDX\0" // IR(19003, 21)
  "StencilRefUnchangedFrontAMD\0" // IR(19024, 28)
  "StencilRefGreaterFrontAMD\0" // IR(19052, 26)
  "StencilRefLessFrontAMD\0" // IR(19078, 23)
  "StencilRefUnchangedBackAMD\0" // IR(19101, 27)
  "StencilRefGreaterBackAMD\0" // IR(19128, 25)
  "StencilRefLessBackAMD\0" // IR(19153, 22)
  "QuadDerivativesKHR\0" // IR(19175, 19)
  "RequireFullQuadsKHR\0" // IR(19194, 20)
  "SharesInputWithAMDX\0" // IR(19214, 20)
  "OutputLinesEXT\0" // IR(19234, 15)
  "OutputLinesNV\0" // IR(19249, 14)
  "OutputPrimitivesEXT\0" // IR(19263, 20)
  "OutputPrimitivesNV\0" // IR(19283, 19)
  "DerivativeGroupQuadsKHR\0" // IR(19302, 24)
  "DerivativeGroupQuadsNV\0" // IR(19326, 23)
  "DerivativeGroupLinearKHR\0" // IR(19349, 25)
  "DerivativeGroupLinearNV\0" // IR(19374, 24)
  "OutputTrianglesEXT\0" // IR(19398, 19)
  "OutputTrianglesNV\0" // IR(19417, 18)
  "PixelInterlockOrderedEXT\0" // IR(19435, 25)
  "PixelInterlockUnorderedEXT\0" // IR(19460, 27)
  "SampleInterlockOrderedEXT\0" // IR(19487, 26)
  "SampleInterlockUnorderedEXT\0" // IR(19513, 28)
  "ShadingRateInterlockOrderedEXT\0" // IR(19541, 31)
  "ShadingRateInterlockUnorderedEXT\0" // IR(19572, 33)
  "SharedLocalMemorySizeINTEL\0" // IR(19605, 27)
  "RoundingModeRTPINTEL\0" // IR(19632, 21)
  "RoundingModeRTNINTEL\0" // IR(19653, 21)
  "FloatingPointModeALTINTEL\0" // IR(19674, 26)
  "FloatingPointModeIEEEINTEL\0" // IR(19700, 27)
  "MaxWorkgroupSizeINTEL\0" // IR(19727, 22)
  "MaxWorkDimINTEL\0" // IR(19749, 16)
  "NoGlobalOffsetINTEL\0" // IR(19765, 20)
  "NumSIMDWorkitemsINTEL\0" // IR(19785, 22)
  "SchedulerTargetFmaxMhzINTEL\0" // IR(19807, 28)
  "MaximallyReconvergesKHR\0" // IR(19835, 24)
  "FPFastMathDefault\0" // IR(19859, 18)
  "StreamingInterfaceINTEL\0" // IR(19877, 24)
  "RegisterMapInterfaceINTEL\0" // IR(19901, 26)
  "NamedBarrierCountINTEL\0" // IR(19927, 23)
  "MaximumRegistersINTEL\0" // IR(19950, 22)
  "MaximumRegistersIdINTEL\0" // IR(19972, 24)
  "SPV_OPERAND_TYPE_NAMED_MAXIMUM_NUMBER_OF_REGISTERS\0" // IR(19996, 51)
  "NamedMaximumRegistersINTEL\0" // IR(20047, 27)
  "Vertex\0" // IR(20074, 7)
  "TessellationControl\0" // IR(20081, 20)
  "TessellationEvaluation\0" // IR(20101, 23)
  "GLCompute\0" // IR(20124, 10)
  "TaskNV\0" // IR(20134, 7)
  "MeshNV\0" // IR(20141, 7)
  "RayGenerationKHR\0" // IR(20148, 17)
  "RayGenerationNV\0" // IR(20165, 16)
  "IntersectionKHR\0" // IR(20181, 16)
  "IntersectionNV\0" // IR(20197, 15)
  "AnyHitKHR\0" // IR(20212, 10)
  "AnyHitNV\0" // IR(20222, 9)
  "ClosestHitKHR\0" // IR(20231, 14)
  "ClosestHitNV\0" // IR(20245, 13)
  "MissKHR\0" // IR(20258, 8)
  "MissNV\0" // IR(20266, 7)
  "CallableKHR\0" // IR(20273, 12)
  "CallableNV\0" // IR(20285, 11)
  "TaskEXT\0" // IR(20296, 8)
  "MeshEXT\0" // IR(20304, 8)
  "Preserve\0" // IR(20312, 9)
  "FlushToZero\0" // IR(20321, 12)
  "BFloat16KHR\0" // IR(20333, 12)
  "IEEE\0" // IR(20345, 5)
  "ALT\0" // IR(20350, 4)
  "NotNaN\0" // IR(20354, 7)
  "NotInf\0" // IR(20361, 7)
  "NSZ\0" // IR(20368, 4)
  "AllowRecip\0" // IR(20372, 11)
  "Fast\0" // IR(20383, 5)
  "AllowContract\0" // IR(20388, 14)
  "AllowContractFastINTEL\0" // IR(20402, 23)
  "AllowReassoc\0" // IR(20425, 13)
  "AllowReassocINTEL\0" // IR(20438, 18)
  "AllowTransform\0" // IR(20456, 15)
  "RTE\0" // IR(20471, 4)
  "RTZ\0" // IR(20475, 4)
  "RTP\0" // IR(20479, 4)
  "RTN\0" // IR(20483, 4)
  "Vertical2Pixels\0" // IR(20487, 16)
  "Vertical4Pixels\0" // IR(20503, 16)
  "Horizontal2Pixels\0" // IR(20519, 18)
  "Horizontal4Pixels\0" // IR(20537, 18)
  "Inline\0" // IR(20555, 7)
  "DontInline\0" // IR(20562, 11)
  "Pure\0" // IR(20573, 5)
  "Const\0" // IR(20578, 6)
  "Zext\0" // IR(20584, 5)
  "Sext\0" // IR(20589, 5)
  "ByVal\0" // IR(20594, 6)
  "Sret\0" // IR(20600, 5)
  "NoAlias\0" // IR(20605, 8)
  "NoCapture\0" // IR(20613, 10)
  "NoWrite\0" // IR(20623, 8)
  "NoReadWrite\0" // IR(20631, 12)
  "RuntimeAlignedINTEL\0" // IR(20643, 20)
  "Reduce\0" // IR(20663, 7)
  "InclusiveScan\0" // IR(20670, 14)
  "ExclusiveScan\0" // IR(20684, 14)
  "ClusteredReduce\0" // IR(20698, 16)
  "PartitionedReduceNV\0" // IR(20714, 20)
  "PartitionedInclusiveScanNV\0" // IR(20734, 27)
  "PartitionedExclusiveScanNV\0" // IR(20761, 27)
  "NoneINTEL\0" // IR(20788, 10)
  "ReadINTEL\0" // IR(20798, 10)
  "WriteINTEL\0" // IR(20808, 11)
  "ReadWriteINTEL\0" // IR(20819, 15)
  "Bias\0" // IR(20834, 5)
  "Lod\0" // IR(20839, 4)
  "Grad\0" // IR(20843, 5)
  "ConstOffset\0" // IR(20848, 12)
  "ConstOffsets\0" // IR(20860, 13)
  "MakeTexelAvailable\0" // IR(20873, 19)
  "MakeTexelAvailableKHR\0" // IR(20892, 22)
  "MakeTexelVisible\0" // IR(20914, 17)
  "MakeTexelVisibleKHR\0" // IR(20931, 20)
  "NonPrivateTexel\0" // IR(20951, 16)
  "NonPrivateTexelKHR\0" // IR(20967, 19)
  "VolatileTexel\0" // IR(20986, 14)
  "VolatileTexelKHR\0" // IR(21000, 17)
  "SignExtend\0" // IR(21017, 11)
  "ZeroExtend\0" // IR(21028, 11)
  "Nontemporal\0" // IR(21039, 12)
  "Offsets\0" // IR(21051, 8)
  "SnormInt8\0" // IR(21059, 10)
  "SnormInt16\0" // IR(21069, 11)
  "UnormInt8\0" // IR(21080, 10)
  "UnormInt16\0" // IR(21090, 11)
  "UnormShort565\0" // IR(21101, 14)
  "UnormShort555\0" // IR(21115, 14)
  "UnormInt101010\0" // IR(21129, 15)
  "SignedInt8\0" // IR(21144, 11)
  "SignedInt16\0" // IR(21155, 12)
  "SignedInt32\0" // IR(21167, 12)
  "UnsignedInt8\0" // IR(21179, 13)
  "UnsignedInt16\0" // IR(21192, 14)
  "UnsignedInt32\0" // IR(21206, 14)
  "HalfFloat\0" // IR(21220, 10)
  "UnormInt24\0" // IR(21230, 11)
  "UnormInt101010_2\0" // IR(21241, 17)
  "UnormInt10X6EXT\0" // IR(21258, 16)
  "UnsignedIntRaw10EXT\0" // IR(21274, 20)
  "UnsignedIntRaw12EXT\0" // IR(21294, 20)
  "UnormInt2_101010EXT\0" // IR(21314, 20)
  "UnsignedInt10X6EXT\0" // IR(21334, 19)
  "UnsignedInt12X4EXT\0" // IR(21353, 19)
  "UnsignedInt14X2EXT\0" // IR(21372, 19)
  "UnormInt12X4EXT\0" // IR(21391, 16)
  "UnormInt14X2EXT\0" // IR(21407, 16)
  "R\0" // IR(21423, 2)
  "A\0" // IR(21425, 2)
  "RG\0" // IR(21427, 3)
  "RA\0" // IR(21430, 3)
  "RGB\0" // IR(21433, 4)
  "RGBA\0" // IR(21437, 5)
  "BGRA\0" // IR(21442, 5)
  "ARGB\0" // IR(21447, 5)
  "Intensity\0" // IR(21452, 10)
  "Luminance\0" // IR(21462, 10)
  "Rx\0" // IR(21472, 3)
  "RGx\0" // IR(21475, 4)
  "RGBx\0" // IR(21479, 5)
  "Depth\0" // IR(21484, 6)
  "DepthStencil\0" // IR(21490, 13)
  "sRGB\0" // IR(21503, 5)
  "sRGBx\0" // IR(21508, 6)
  "sRGBA\0" // IR(21514, 6)
  "sBGRA\0" // IR(21520, 6)
  "ABGR\0" // IR(21526, 5)
  "InitOnDeviceReprogramINTEL\0" // IR(21531, 27)
  "InitOnDeviceResetINTEL\0" // IR(21558, 23)
  "NoWait\0" // IR(21581, 7)
  "WaitKernel\0" // IR(21588, 11)
  "WaitWorkGroup\0" // IR(21599, 14)
  "CmdExecTime\0" // IR(21613, 12)
  "MayUsePrintf\0" // IR(21625, 13)
  "Export\0" // IR(21638, 7)
  "Import\0" // IR(21645, 7)
  "LinkOnceODR\0" // IR(21652, 12)
  "UncachedINTEL\0" // IR(21664, 14)
  "CachedINTEL\0" // IR(21678, 12)
  "StreamingINTEL\0" // IR(21690, 15)
  "InvalidateAfterReadINTEL\0" // IR(21705, 25)
  "ConstCachedINTEL\0" // IR(21730, 17)
  "Unroll\0" // IR(21747, 7)
  "DontUnroll\0" // IR(21754, 11)
  "DependencyInfinite\0" // IR(21765, 19)
  "DependencyLength\0" // IR(21784, 17)
  "MinIterations\0" // IR(21801, 14)
  "MaxIterations\0" // IR(21815, 14)
  "IterationMultiple\0" // IR(21829, 18)
  "PeelCount\0" // IR(21847, 10)
  "PartialCount\0" // IR(21857, 13)
  "DependencyArrayINTEL\0" // IR(21870, 21)
  "LoopCoalesceINTEL\0" // IR(21891, 18)
  "MaxInterleavingINTEL\0" // IR(21909, 21)
  "SpeculatedIterationsINTEL\0" // IR(21930, 26)
  "NoFusionINTEL\0" // IR(21956, 14)
  "LoopCountINTEL\0" // IR(21970, 15)
  "MaxReinvocationDelayINTEL\0" // IR(21985, 26)
  "MatrixASignedComponentsINTEL\0" // IR(22011, 29)
  "MatrixBSignedComponentsINTEL\0" // IR(22040, 29)
  "MatrixCBFloat16INTEL\0" // IR(22069, 21)
  "MatrixResultBFloat16INTEL\0" // IR(22090, 26)
  "MatrixAPackedInt8INTEL\0" // IR(22116, 23)
  "MatrixBPackedInt8INTEL\0" // IR(22139, 23)
  "MatrixAPackedInt4INTEL\0" // IR(22162, 23)
  "MatrixBPackedInt4INTEL\0" // IR(22185, 23)
  "MatrixATF32INTEL\0" // IR(22208, 17)
  "MatrixBTF32INTEL\0" // IR(22225, 17)
  "MatrixAPackedFloat16INTEL\0" // IR(22242, 26)
  "MatrixBPackedFloat16INTEL\0" // IR(22268, 26)
  "MatrixAPackedBFloat16INTEL\0" // IR(22294, 27)
  "MatrixBPackedBFloat16INTEL\0" // IR(22321, 27)
  "Aligned\0" // IR(22348, 8)
  "MakePointerAvailable\0" // IR(22356, 21)
  "MakePointerAvailableKHR\0" // IR(22377, 24)
  "MakePointerVisible\0" // IR(22401, 19)
  "MakePointerVisibleKHR\0" // IR(22420, 22)
  "NonPrivatePointer\0" // IR(22442, 18)
  "NonPrivatePointerKHR\0" // IR(22460, 21)
  "AliasScopeINTELMask\0" // IR(22481, 20)
  "NoAliasINTELMask\0" // IR(22501, 17)
  "Simple\0" // IR(22518, 7)
  "GLSL450\0" // IR(22525, 8)
  "OpenCL\0" // IR(22533, 7)
  "Vulkan\0" // IR(22540, 7)
  "VulkanKHR\0" // IR(22547, 10)
  "Relaxed\0" // IR(22557, 8)
  "Acquire\0" // IR(22565, 8)
  "Release\0" // IR(22573, 8)
  "AcquireRelease\0" // IR(22581, 15)
  "SequentiallyConsistent\0" // IR(22596, 23)
  "UniformMemory\0" // IR(22619, 14)
  "SubgroupMemory\0" // IR(22633, 15)
  "WorkgroupMemory\0" // IR(22648, 16)
  "CrossWorkgroupMemory\0" // IR(22664, 21)
  "AtomicCounterMemory\0" // IR(22685, 20)
  "ImageMemory\0" // IR(22705, 12)
  "OutputMemory\0" // IR(22717, 13)
  "OutputMemoryKHR\0" // IR(22730, 16)
  "MakeAvailable\0" // IR(22746, 14)
  "MakeAvailableKHR\0" // IR(22760, 17)
  "MakeVisible\0" // IR(22777, 12)
  "MakeVisibleKHR\0" // IR(22789, 15)
  "AutoINTEL\0" // IR(22804, 10)
  "WRAP\0" // IR(22814, 5)
  "SAT\0" // IR(22819, 4)
  "SAT_ZERO\0" // IR(22823, 9)
  "SAT_SYM\0" // IR(22832, 8)
  "PackedVectorFormat4x8Bit\0" // IR(22840, 25)
  "PackedVectorFormat4x8BitKHR\0" // IR(22865, 28)
  "TRN\0" // IR(22893, 4)
  "TRN_ZERO\0" // IR(22897, 9)
  "RND\0" // IR(22906, 4)
  "RND_ZERO\0" // IR(22910, 9)
  "RND_INF\0" // IR(22919, 8)
  "RND_MIN_INF\0" // IR(22927, 12)
  "RND_CONV\0" // IR(22939, 9)
  "RND_CONV_ODD\0" // IR(22948, 13)
  "RobustnessPerComponentNV\0" // IR(22961, 25)
  "RobustnessPerElementNV\0" // IR(22986, 23)
  "OpaqueKHR\0" // IR(23009, 10)
  "NoOpaqueKHR\0" // IR(23019, 12)
  "TerminateOnFirstHitKHR\0" // IR(23031, 23)
  "SkipClosestHitShaderKHR\0" // IR(23054, 24)
  "CullBackFacingTrianglesKHR\0" // IR(23078, 27)
  "CullFrontFacingTrianglesKHR\0" // IR(23105, 28)
  "CullOpaqueKHR\0" // IR(23133, 14)
  "CullNoOpaqueKHR\0" // IR(23147, 16)
  "SkipTrianglesKHR\0" // IR(23163, 17)
  "SkipBuiltinPrimitivesNV\0" // IR(23180, 24)
  "SkipAABBsKHR\0" // IR(23204, 13)
  "ForceOpacityMicromap2StateEXT\0" // IR(23217, 30)
  "RayQueryCandidateIntersectionTriangleKHR\0" // IR(23247, 41)
  "RayQueryCandidateIntersectionAABBKHR\0" // IR(23288, 37)
  "RayQueryCommittedIntersectionNoneKHR\0" // IR(23325, 37)
  "RayQueryCommittedIntersectionTriangleKHR\0" // IR(23362, 41)
  "RayQueryCommittedIntersectionGeneratedKHR\0" // IR(23403, 42)
  "RayQueryCandidateIntersectionKHR\0" // IR(23445, 33)
  "RayQueryCommittedIntersectionKHR\0" // IR(23478, 33)
  "ClampToEdge\0" // IR(23511, 12)
  "Clamp\0" // IR(23523, 6)
  "Repeat\0" // IR(23529, 7)
  "RepeatMirrored\0" // IR(23536, 15)
  "Nearest\0" // IR(23551, 8)
  "Linear\0" // IR(23559, 7)
  "Unknown\0" // IR(23566, 8)
  "Rgba32f\0" // IR(23574, 8)
  "Rgba16f\0" // IR(23582, 8)
  "R32f\0" // IR(23590, 5)
  "Rgba8\0" // IR(23595, 6)
  "Rgba8Snorm\0" // IR(23601, 11)
  "Rg32f\0" // IR(23612, 6)
  "Rg16f\0" // IR(23618, 6)
  "R11fG11fB10f\0" // IR(23624, 13)
  "R16f\0" // IR(23637, 5)
  "Rgba16\0" // IR(23642, 7)
  "Rgb10A2\0" // IR(23649, 8)
  "Rg16\0" // IR(23657, 5)
  "Rg8\0" // IR(23662, 4)
  "R16\0" // IR(23666, 4)
  "R8\0" // IR(23670, 3)
  "Rgba16Snorm\0" // IR(23673, 12)
  "Rg16Snorm\0" // IR(23685, 10)
  "Rg8Snorm\0" // IR(23695, 9)
  "R16Snorm\0" // IR(23704, 9)
  "R8Snorm\0" // IR(23713, 8)
  "Rgba32i\0" // IR(23721, 8)
  "Rgba16i\0" // IR(23729, 8)
  "Rgba8i\0" // IR(23737, 7)
  "R32i\0" // IR(23744, 5)
  "Rg32i\0" // IR(23749, 6)
  "Rg16i\0" // IR(23755, 6)
  "Rg8i\0" // IR(23761, 5)
  "R16i\0" // IR(23766, 5)
  "R8i\0" // IR(23771, 4)
  "Rgba32ui\0" // IR(23775, 9)
  "Rgba16ui\0" // IR(23784, 9)
  "Rgba8ui\0" // IR(23793, 8)
  "R32ui\0" // IR(23801, 6)
  "Rgb10a2ui\0" // IR(23807, 10)
  "Rg32ui\0" // IR(23817, 7)
  "Rg16ui\0" // IR(23824, 7)
  "Rg8ui\0" // IR(23831, 6)
  "R16ui\0" // IR(23837, 6)
  "R8ui\0" // IR(23843, 5)
  "R64ui\0" // IR(23848, 6)
  "R64i\0" // IR(23854, 5)
  "CrossDevice\0" // IR(23859, 12)
  "Device\0" // IR(23871, 7)
  "Workgroup\0" // IR(23878, 10)
  "Subgroup\0" // IR(23888, 9)
  "Invocation\0" // IR(23897, 11)
  "QueueFamily\0" // IR(23908, 12)
  "QueueFamilyKHR\0" // IR(23920, 15)
  "ShaderCallKHR\0" // IR(23935, 14)
  "Flatten\0" // IR(23949, 8)
  "DontFlatten\0" // IR(23957, 12)
  "IdentifierPossibleDuplicates\0" // IR(23969, 29)
  "FlagUnknownPhysicalLayout\0" // IR(23998, 26)
  "ESSL\0" // IR(24024, 5)
  "GLSL\0" // IR(24029, 5)
  "OpenCL_C\0" // IR(24034, 9)
  "OpenCL_CPP\0" // IR(24043, 11)
  "HLSL\0" // IR(24054, 5)
  "CPP_for_OpenCL\0" // IR(24059, 15)
  "SYCL\0" // IR(24074, 5)
  "HERO_C\0" // IR(24079, 7)
  "NZSL\0" // IR(24086, 5)
  "WGSL\0" // IR(24091, 5)
  "Slang\0" // IR(24096, 6)
  "Zig\0" // IR(24102, 4)
  "Rust\0" // IR(24106, 5)
  "UniformConstant\0" // IR(24111, 16)
  "Input\0" // IR(24127, 6)
  "Output\0" // IR(24133, 7)
  "CrossWorkgroup\0" // IR(24140, 15)
  "Private\0" // IR(24155, 8)
  "Function\0" // IR(24163, 9)
  "Generic\0" // IR(24172, 8)
  "PushConstant\0" // IR(24180, 13)
  "AtomicCounter\0" // IR(24193, 14)
  "Image\0" // IR(24207, 6)
  "StorageBuffer\0" // IR(24213, 14)
  "TileImageEXT\0" // IR(24227, 13)
  "TileAttachmentQCOM\0" // IR(24240, 19)
  "NodePayloadAMDX\0" // IR(24259, 16)
  "CallableDataKHR\0" // IR(24275, 16)
  "CallableDataNV\0" // IR(24291, 15)
  "IncomingCallableDataKHR\0" // IR(24306, 24)
  "IncomingCallableDataNV\0" // IR(24330, 23)
  "RayPayloadKHR\0" // IR(24353, 14)
  "RayPayloadNV\0" // IR(24367, 13)
  "HitAttributeKHR\0" // IR(24380, 16)
  "HitAttributeNV\0" // IR(24396, 15)
  "IncomingRayPayloadKHR\0" // IR(24411, 22)
  "IncomingRayPayloadNV\0" // IR(24433, 21)
  "ShaderRecordBufferKHR\0" // IR(24454, 22)
  "ShaderRecordBufferNV\0" // IR(24476, 21)
  "PhysicalStorageBuffer\0" // IR(24497, 22)
  "PhysicalStorageBufferEXT\0" // IR(24519, 25)
  "HitObjectAttributeNV\0" // IR(24544, 21)
  "TaskPayloadWorkgroupEXT\0" // IR(24565, 24)
  "CodeSectionINTEL\0" // IR(24589, 17)
  "DeviceOnlyINTEL\0" // IR(24606, 16)
  "HostOnlyINTEL\0" // IR(24622, 14)
  "WriteThroughINTEL\0" // IR(24636, 18)
  "WriteBackINTEL\0" // IR(24654, 15)
  "TensorView\0" // IR(24669, 11)
  "DecodeFunc\0" // IR(24680, 11)
  "Undefined\0" // IR(24691, 10)
  "NoneARM\0" // IR(24701, 8)
  "NontemporalARM\0" // IR(24709, 15)
  "OutOfBoundsValueARM\0" // IR(24724, 20)
  "MakeElementAvailableARM\0" // IR(24744, 24)
  "MakeElementVisibleARM\0" // IR(24768, 22)
  "NonPrivateElementARM\0" // IR(24790, 21)
  "Nop\0" // IR(24811, 4)
  "SPV_OPERAND_TYPE_TYPE_ID\0" // IR(24815, 25)
  "SPV_OPERAND_TYPE_RESULT_ID\0" // IR(24840, 27)
  "Undef\0" // IR(24867, 6)
  "SourceContinued\0" // IR(24873, 16)
  "SPV_OPERAND_TYPE_SOURCE_LANGUAGE\0" // IR(24889, 33)
  "SPV_OPERAND_TYPE_OPTIONAL_ID\0" // IR(24922, 29)
  "SPV_OPERAND_TYPE_OPTIONAL_LITERAL_STRING\0" // IR(24951, 41)
  "Source\0" // IR(24992, 7)
  "SourceExtension\0" // IR(24999, 16)
  "Name\0" // IR(25015, 5)
  "MemberName\0" // IR(25020, 11)
  "String\0" // IR(25031, 7)
  "Line\0" // IR(25038, 5)
  "Extension\0" // IR(25043, 10)
  "ExtInstImport\0" // IR(25053, 14)
  "SPV_OPERAND_TYPE_EXTENSION_INSTRUCTION_NUMBER\0" // IR(25067, 46)
  "ExtInst\0" // IR(25113, 8)
  "SPV_OPERAND_TYPE_ADDRESSING_MODEL\0" // IR(25121, 34)
  "SPV_OPERAND_TYPE_MEMORY_MODEL\0" // IR(25155, 30)
  "MemoryModel\0" // IR(25185, 12)
  "SPV_OPERAND_TYPE_EXECUTION_MODEL\0" // IR(25197, 33)
  "SPV_OPERAND_TYPE_VARIABLE_ID\0" // IR(25230, 29)
  "EntryPoint\0" // IR(25259, 11)
  "SPV_OPERAND_TYPE_EXECUTION_MODE\0" // IR(25270, 32)
  "ExecutionMode\0" // IR(25302, 14)
  "SPV_OPERAND_TYPE_CAPABILITY\0" // IR(25316, 28)
  "Capability\0" // IR(25344, 11)
  "TypeVoid\0" // IR(25355, 9)
  "TypeBool\0" // IR(25364, 9)
  "TypeInt\0" // IR(25373, 8)
  "SPV_OPERAND_TYPE_OPTIONAL_FPENCODING\0" // IR(25381, 37)
  "TypeFloat\0" // IR(25418, 10)
  "TypeVector\0" // IR(25428, 11)
  "TypeMatrix\0" // IR(25439, 11)
  "SPV_OPERAND_TYPE_DIMENSIONALITY\0" // IR(25450, 32)
  "SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT\0" // IR(25482, 38)
  "SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER\0" // IR(25520, 43)
  "TypeImage\0" // IR(25563, 10)
  "TypeSampler\0" // IR(25573, 12)
  "TypeSampledImage\0" // IR(25585, 17)
  "TypeArray\0" // IR(25602, 10)
  "TypeRuntimeArray\0" // IR(25612, 17)
  "TypeStruct\0" // IR(25629, 11)
  "TypeOpaque\0" // IR(25640, 11)
  "SPV_OPERAND_TYPE_STORAGE_CLASS\0" // IR(25651, 31)
  "TypePointer\0" // IR(25682, 12)
  "TypeFunction\0" // IR(25694, 13)
  "TypeEvent\0" // IR(25707, 10)
  "TypeDeviceEvent\0" // IR(25717, 16)
  "TypeReserveId\0" // IR(25733, 14)
  "TypeQueue\0" // IR(25747, 10)
  "TypePipe\0" // IR(25757, 9)
  "TypeForwardPointer\0" // IR(25766, 19)
  "ConstantTrue\0" // IR(25785, 13)
  "ConstantFalse\0" // IR(25798, 14)
  "SPV_OPERAND_TYPE_TYPED_LITERAL_NUMBER\0" // IR(25812, 38)
  "ConstantComposite\0" // IR(25850, 18)
  "SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE\0" // IR(25868, 41)
  "SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE\0" // IR(25909, 37)
  "ConstantSampler\0" // IR(25946, 16)
  "ConstantNull\0" // IR(25962, 13)
  "SpecConstantTrue\0" // IR(25975, 17)
  "SpecConstantFalse\0" // IR(25992, 18)
  "SpecConstant\0" // IR(26010, 13)
  "SpecConstantComposite\0" // IR(26023, 22)
  "SPV_OPERAND_TYPE_SPEC_CONSTANT_OP_NUMBER\0" // IR(26045, 41)
  "SpecConstantOp\0" // IR(26086, 15)
  "SPV_OPERAND_TYPE_FUNCTION_CONTROL\0" // IR(26101, 34)
  "FunctionParameter\0" // IR(26135, 18)
  "FunctionEnd\0" // IR(26153, 12)
  "FunctionCall\0" // IR(26165, 13)
  "Variable\0" // IR(26178, 9)
  "ImageTexelPointer\0" // IR(26187, 18)
  "SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS\0" // IR(26205, 40)
  "Load\0" // IR(26245, 5)
  "Store\0" // IR(26250, 6)
  "CopyMemory\0" // IR(26256, 11)
  "CopyMemorySized\0" // IR(26267, 16)
  "AccessChain\0" // IR(26283, 12)
  "InBoundsAccessChain\0" // IR(26295, 20)
  "PtrAccessChain\0" // IR(26315, 15)
  "ArrayLength\0" // IR(26330, 12)
  "GenericPtrMemSemantics\0" // IR(26342, 23)
  "InBoundsPtrAccessChain\0" // IR(26365, 23)
  "SPV_OPERAND_TYPE_DECORATION\0" // IR(26388, 28)
  "Decorate\0" // IR(26416, 9)
  "MemberDecorate\0" // IR(26425, 15)
  "DecorationGroup\0" // IR(26440, 16)
  "GroupDecorate\0" // IR(26456, 14)
  "SPV_OPERAND_TYPE_VARIABLE_ID_LITERAL_INTEGER\0" // IR(26470, 45)
  "GroupMemberDecorate\0" // IR(26515, 20)
  "VectorExtractDynamic\0" // IR(26535, 21)
  "VectorInsertDynamic\0" // IR(26556, 20)
  "VectorShuffle\0" // IR(26576, 14)
  "CompositeConstruct\0" // IR(26590, 19)
  "CompositeExtract\0" // IR(26609, 17)
  "CompositeInsert\0" // IR(26626, 16)
  "CopyObject\0" // IR(26642, 11)
  "Transpose\0" // IR(26653, 10)
  "SampledImage\0" // IR(26663, 13)
  "SPV_OPERAND_TYPE_OPTIONAL_IMAGE\0" // IR(26676, 32)
  "ImageSampleImplicitLod\0" // IR(26708, 23)
  "SPV_OPERAND_TYPE_IMAGE\0" // IR(26731, 23)
  "ImageSampleExplicitLod\0" // IR(26754, 23)
  "ImageSampleDrefImplicitLod\0" // IR(26777, 27)
  "ImageSampleDrefExplicitLod\0" // IR(26804, 27)
  "ImageSampleProjImplicitLod\0" // IR(26831, 27)
  "ImageSampleProjExplicitLod\0" // IR(26858, 27)
  "ImageSampleProjDrefImplicitLod\0" // IR(26885, 31)
  "ImageSampleProjDrefExplicitLod\0" // IR(26916, 31)
  "ImageFetch\0" // IR(26947, 11)
  "ImageGather\0" // IR(26958, 12)
  "ImageDrefGather\0" // IR(26970, 16)
  "ImageRead\0" // IR(26986, 10)
  "ImageWrite\0" // IR(26996, 11)
  "ImageQueryFormat\0" // IR(27007, 17)
  "ImageQueryOrder\0" // IR(27024, 16)
  "ImageQuerySizeLod\0" // IR(27040, 18)
  "ImageQuerySize\0" // IR(27058, 15)
  "ImageQueryLod\0" // IR(27073, 14)
  "ImageQueryLevels\0" // IR(27087, 17)
  "ImageQuerySamples\0" // IR(27104, 18)
  "ConvertFToU\0" // IR(27122, 12)
  "ConvertFToS\0" // IR(27134, 12)
  "ConvertSToF\0" // IR(27146, 12)
  "ConvertUToF\0" // IR(27158, 12)
  "UConvert\0" // IR(27170, 9)
  "SConvert\0" // IR(27179, 9)
  "FConvert\0" // IR(27188, 9)
  "QuantizeToF16\0" // IR(27197, 14)
  "ConvertPtrToU\0" // IR(27211, 14)
  "SatConvertSToU\0" // IR(27225, 15)
  "SatConvertUToS\0" // IR(27240, 15)
  "ConvertUToPtr\0" // IR(27255, 14)
  "PtrCastToGeneric\0" // IR(27269, 17)
  "GenericCastToPtr\0" // IR(27286, 17)
  "GenericCastToPtrExplicit\0" // IR(27303, 25)
  "Bitcast\0" // IR(27328, 8)
  "SNegate\0" // IR(27336, 8)
  "FNegate\0" // IR(27344, 8)
  "IAdd\0" // IR(27352, 5)
  "FAdd\0" // IR(27357, 5)
  "ISub\0" // IR(27362, 5)
  "FSub\0" // IR(27367, 5)
  "IMul\0" // IR(27372, 5)
  "FMul\0" // IR(27377, 5)
  "UDiv\0" // IR(27382, 5)
  "SDiv\0" // IR(27387, 5)
  "FDiv\0" // IR(27392, 5)
  "UMod\0" // IR(27397, 5)
  "SRem\0" // IR(27402, 5)
  "SMod\0" // IR(27407, 5)
  "FRem\0" // IR(27412, 5)
  "FMod\0" // IR(27417, 5)
  "VectorTimesScalar\0" // IR(27422, 18)
  "MatrixTimesScalar\0" // IR(27440, 18)
  "VectorTimesMatrix\0" // IR(27458, 18)
  "MatrixTimesVector\0" // IR(27476, 18)
  "MatrixTimesMatrix\0" // IR(27494, 18)
  "OuterProduct\0" // IR(27512, 13)
  "Dot\0" // IR(27525, 4)
  "IAddCarry\0" // IR(27529, 10)
  "ISubBorrow\0" // IR(27539, 11)
  "UMulExtended\0" // IR(27550, 13)
  "SMulExtended\0" // IR(27563, 13)
  "Any\0" // IR(27576, 4)
  "All\0" // IR(27580, 4)
  "IsNan\0" // IR(27584, 6)
  "IsInf\0" // IR(27590, 6)
  "IsFinite\0" // IR(27596, 9)
  "IsNormal\0" // IR(27605, 9)
  "SignBitSet\0" // IR(27614, 11)
  "LessOrGreater\0" // IR(27625, 14)
  "Ordered\0" // IR(27639, 8)
  "Unordered\0" // IR(27647, 10)
  "LogicalEqual\0" // IR(27657, 13)
  "LogicalNotEqual\0" // IR(27670, 16)
  "LogicalOr\0" // IR(27686, 10)
  "LogicalAnd\0" // IR(27696, 11)
  "LogicalNot\0" // IR(27707, 11)
  "Select\0" // IR(27718, 7)
  "IEqual\0" // IR(27725, 7)
  "INotEqual\0" // IR(27732, 10)
  "UGreaterThan\0" // IR(27742, 13)
  "SGreaterThan\0" // IR(27755, 13)
  "UGreaterThanEqual\0" // IR(27768, 18)
  "SGreaterThanEqual\0" // IR(27786, 18)
  "ULessThan\0" // IR(27804, 10)
  "SLessThan\0" // IR(27814, 10)
  "ULessThanEqual\0" // IR(27824, 15)
  "SLessThanEqual\0" // IR(27839, 15)
  "FOrdEqual\0" // IR(27854, 10)
  "FUnordEqual\0" // IR(27864, 12)
  "FOrdNotEqual\0" // IR(27876, 13)
  "FUnordNotEqual\0" // IR(27889, 15)
  "FOrdLessThan\0" // IR(27904, 13)
  "FUnordLessThan\0" // IR(27917, 15)
  "FOrdGreaterThan\0" // IR(27932, 16)
  "FUnordGreaterThan\0" // IR(27948, 18)
  "FOrdLessThanEqual\0" // IR(27966, 18)
  "FUnordLessThanEqual\0" // IR(27984, 20)
  "FOrdGreaterThanEqual\0" // IR(28004, 21)
  "FUnordGreaterThanEqual\0" // IR(28025, 23)
  "ShiftRightLogical\0" // IR(28048, 18)
  "ShiftRightArithmetic\0" // IR(28066, 21)
  "ShiftLeftLogical\0" // IR(28087, 17)
  "BitwiseOr\0" // IR(28104, 10)
  "BitwiseXor\0" // IR(28114, 11)
  "BitwiseAnd\0" // IR(28125, 11)
  "Not\0" // IR(28136, 4)
  "BitFieldInsert\0" // IR(28140, 15)
  "BitFieldSExtract\0" // IR(28155, 17)
  "BitFieldUExtract\0" // IR(28172, 17)
  "BitReverse\0" // IR(28189, 11)
  "BitCount\0" // IR(28200, 9)
  "DPdx\0" // IR(28209, 5)
  "DPdy\0" // IR(28214, 5)
  "Fwidth\0" // IR(28219, 7)
  "DPdxFine\0" // IR(28226, 9)
  "DPdyFine\0" // IR(28235, 9)
  "FwidthFine\0" // IR(28244, 11)
  "DPdxCoarse\0" // IR(28255, 11)
  "DPdyCoarse\0" // IR(28266, 11)
  "FwidthCoarse\0" // IR(28277, 13)
  "EmitVertex\0" // IR(28290, 11)
  "EndPrimitive\0" // IR(28301, 13)
  "EmitStreamVertex\0" // IR(28314, 17)
  "EndStreamPrimitive\0" // IR(28331, 19)
  "SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID\0" // IR(28350, 37)
  "ControlBarrier\0" // IR(28387, 15)
  "MemoryBarrier\0" // IR(28402, 14)
  "AtomicLoad\0" // IR(28416, 11)
  "AtomicStore\0" // IR(28427, 12)
  "AtomicExchange\0" // IR(28439, 15)
  "AtomicCompareExchange\0" // IR(28454, 22)
  "AtomicCompareExchangeWeak\0" // IR(28476, 26)
  "AtomicIIncrement\0" // IR(28502, 17)
  "AtomicIDecrement\0" // IR(28519, 17)
  "AtomicIAdd\0" // IR(28536, 11)
  "AtomicISub\0" // IR(28547, 11)
  "AtomicSMin\0" // IR(28558, 11)
  "AtomicUMin\0" // IR(28569, 11)
  "AtomicSMax\0" // IR(28580, 11)
  "AtomicUMax\0" // IR(28591, 11)
  "AtomicAnd\0" // IR(28602, 10)
  "AtomicOr\0" // IR(28612, 9)
  "AtomicXor\0" // IR(28621, 10)
  "Phi\0" // IR(28631, 4)
  "SPV_OPERAND_TYPE_LOOP_CONTROL\0" // IR(28635, 30)
  "LoopMerge\0" // IR(28665, 10)
  "SPV_OPERAND_TYPE_SELECTION_CONTROL\0" // IR(28675, 35)
  "SelectionMerge\0" // IR(28710, 15)
  "Label\0" // IR(28725, 6)
  "Branch\0" // IR(28731, 7)
  "BranchConditional\0" // IR(28738, 18)
  "SPV_OPERAND_TYPE_VARIABLE_LITERAL_INTEGER_ID\0" // IR(28756, 45)
  "Switch\0" // IR(28801, 7)
  "Kill\0" // IR(28808, 5)
  "Return\0" // IR(28813, 7)
  "ReturnValue\0" // IR(28820, 12)
  "Unreachable\0" // IR(28832, 12)
  "LifetimeStart\0" // IR(28844, 14)
  "LifetimeStop\0" // IR(28858, 13)
  "GroupAsyncCopy\0" // IR(28871, 15)
  "GroupWaitEvents\0" // IR(28886, 16)
  "GroupAll\0" // IR(28902, 9)
  "GroupAny\0" // IR(28911, 9)
  "GroupBroadcast\0" // IR(28920, 15)
  "SPV_OPERAND_TYPE_GROUP_OPERATION\0" // IR(28935, 33)
  "GroupIAdd\0" // IR(28968, 10)
  "GroupFAdd\0" // IR(28978, 10)
  "GroupFMin\0" // IR(28988, 10)
  "GroupUMin\0" // IR(28998, 10)
  "GroupSMin\0" // IR(29008, 10)
  "GroupFMax\0" // IR(29018, 10)
  "GroupUMax\0" // IR(29028, 10)
  "GroupSMax\0" // IR(29038, 10)
  "ReadPipe\0" // IR(29048, 9)
  "WritePipe\0" // IR(29057, 10)
  "ReservedReadPipe\0" // IR(29067, 17)
  "ReservedWritePipe\0" // IR(29084, 18)
  "ReserveReadPipePackets\0" // IR(29102, 23)
  "ReserveWritePipePackets\0" // IR(29125, 24)
  "CommitReadPipe\0" // IR(29149, 15)
  "CommitWritePipe\0" // IR(29164, 16)
  "IsValidReserveId\0" // IR(29180, 17)
  "GetNumPipePackets\0" // IR(29197, 18)
  "GetMaxPipePackets\0" // IR(29215, 18)
  "GroupReserveReadPipePackets\0" // IR(29233, 28)
  "GroupReserveWritePipePackets\0" // IR(29261, 29)
  "GroupCommitReadPipe\0" // IR(29290, 20)
  "GroupCommitWritePipe\0" // IR(29310, 21)
  "EnqueueMarker\0" // IR(29331, 14)
  "EnqueueKernel\0" // IR(29345, 14)
  "GetKernelNDrangeSubGroupCount\0" // IR(29359, 30)
  "GetKernelNDrangeMaxSubGroupSize\0" // IR(29389, 32)
  "GetKernelWorkGroupSize\0" // IR(29421, 23)
  "GetKernelPreferredWorkGroupSizeMultiple\0" // IR(29444, 40)
  "RetainEvent\0" // IR(29484, 12)
  "ReleaseEvent\0" // IR(29496, 13)
  "CreateUserEvent\0" // IR(29509, 16)
  "IsValidEvent\0" // IR(29525, 13)
  "SetUserEventStatus\0" // IR(29538, 19)
  "CaptureEventProfilingInfo\0" // IR(29557, 26)
  "GetDefaultQueue\0" // IR(29583, 16)
  "BuildNDRange\0" // IR(29599, 13)
  "ImageSparseSampleImplicitLod\0" // IR(29612, 29)
  "ImageSparseSampleExplicitLod\0" // IR(29641, 29)
  "ImageSparseSampleDrefImplicitLod\0" // IR(29670, 33)
  "ImageSparseSampleDrefExplicitLod\0" // IR(29703, 33)
  "ImageSparseSampleProjImplicitLod\0" // IR(29736, 33)
  "ImageSparseSampleProjExplicitLod\0" // IR(29769, 33)
  "ImageSparseSampleProjDrefImplicitLod\0" // IR(29802, 37)
  "ImageSparseSampleProjDrefExplicitLod\0" // IR(29839, 37)
  "ImageSparseFetch\0" // IR(29876, 17)
  "ImageSparseGather\0" // IR(29893, 18)
  "ImageSparseDrefGather\0" // IR(29911, 22)
  "ImageSparseTexelsResident\0" // IR(29933, 26)
  "NoLine\0" // IR(29959, 7)
  "AtomicFlagTestAndSet\0" // IR(29966, 21)
  "AtomicFlagClear\0" // IR(29987, 16)
  "ImageSparseRead\0" // IR(30003, 16)
  "SizeOf\0" // IR(30019, 7)
  "TypePipeStorage\0" // IR(30026, 16)
  "ConstantPipeStorage\0" // IR(30042, 20)
  "CreatePipeFromPipeStorage\0" // IR(30062, 26)
  "GetKernelLocalSizeForSubgroupCount\0" // IR(30088, 35)
  "GetKernelMaxNumSubgroups\0" // IR(30123, 25)
  "TypeNamedBarrier\0" // IR(30148, 17)
  "NamedBarrierInitialize\0" // IR(30165, 23)
  "MemoryNamedBarrier\0" // IR(30188, 19)
  "ModuleProcessed\0" // IR(30207, 16)
  "ExecutionModeId\0" // IR(30223, 16)
  "DecorateId\0" // IR(30239, 11)
  "GroupNonUniformElect\0" // IR(30250, 21)
  "GroupNonUniformAll\0" // IR(30271, 19)
  "GroupNonUniformAny\0" // IR(30290, 19)
  "GroupNonUniformAllEqual\0" // IR(30309, 24)
  "GroupNonUniformBroadcast\0" // IR(30333, 25)
  "GroupNonUniformBroadcastFirst\0" // IR(30358, 30)
  "GroupNonUniformInverseBallot\0" // IR(30388, 29)
  "GroupNonUniformBallotBitExtract\0" // IR(30417, 32)
  "GroupNonUniformBallotBitCount\0" // IR(30449, 30)
  "GroupNonUniformBallotFindLSB\0" // IR(30479, 29)
  "GroupNonUniformBallotFindMSB\0" // IR(30508, 29)
  "GroupNonUniformShuffleXor\0" // IR(30537, 26)
  "GroupNonUniformShuffleUp\0" // IR(30563, 25)
  "GroupNonUniformShuffleDown\0" // IR(30588, 27)
  "GroupNonUniformIAdd\0" // IR(30615, 20)
  "GroupNonUniformFAdd\0" // IR(30635, 20)
  "GroupNonUniformIMul\0" // IR(30655, 20)
  "GroupNonUniformFMul\0" // IR(30675, 20)
  "GroupNonUniformSMin\0" // IR(30695, 20)
  "GroupNonUniformUMin\0" // IR(30715, 20)
  "GroupNonUniformFMin\0" // IR(30735, 20)
  "GroupNonUniformSMax\0" // IR(30755, 20)
  "GroupNonUniformUMax\0" // IR(30775, 20)
  "GroupNonUniformFMax\0" // IR(30795, 20)
  "GroupNonUniformBitwiseAnd\0" // IR(30815, 26)
  "GroupNonUniformBitwiseOr\0" // IR(30841, 25)
  "GroupNonUniformBitwiseXor\0" // IR(30866, 26)
  "GroupNonUniformLogicalAnd\0" // IR(30892, 26)
  "GroupNonUniformLogicalOr\0" // IR(30918, 25)
  "GroupNonUniformLogicalXor\0" // IR(30943, 26)
  "GroupNonUniformQuadBroadcast\0" // IR(30969, 29)
  "GroupNonUniformQuadSwap\0" // IR(30998, 24)
  "CopyLogical\0" // IR(31022, 12)
  "PtrEqual\0" // IR(31034, 9)
  "PtrNotEqual\0" // IR(31043, 12)
  "PtrDiff\0" // IR(31055, 8)
  "ColorAttachmentReadEXT\0" // IR(31063, 23)
  "DepthAttachmentReadEXT\0" // IR(31086, 23)
  "StencilAttachmentReadEXT\0" // IR(31109, 25)
  "TypeTensorARM\0" // IR(31134, 14)
  "SPV_OPERAND_TYPE_OPTIONAL_TENSOR_OPERANDS\0" // IR(31148, 42)
  "TensorReadARM\0" // IR(31190, 14)
  "TensorWriteARM\0" // IR(31204, 15)
  "TensorQuerySizeARM\0" // IR(31219, 19)
  "TerminateInvocation\0" // IR(31238, 20)
  "TypeUntypedPointerKHR\0" // IR(31258, 22)
  "UntypedVariableKHR\0" // IR(31280, 19)
  "UntypedAccessChainKHR\0" // IR(31299, 22)
  "UntypedInBoundsAccessChainKHR\0" // IR(31321, 30)
  "SubgroupFirstInvocationKHR\0" // IR(31351, 27)
  "UntypedPtrAccessChainKHR\0" // IR(31378, 25)
  "UntypedInBoundsPtrAccessChainKHR\0" // IR(31403, 33)
  "UntypedArrayLengthKHR\0" // IR(31436, 22)
  "UntypedPrefetchKHR\0" // IR(31458, 19)
  "SubgroupAllKHR\0" // IR(31477, 15)
  "SubgroupAnyKHR\0" // IR(31492, 15)
  "SubgroupAllEqualKHR\0" // IR(31507, 20)
  "SubgroupReadInvocationKHR\0" // IR(31527, 26)
  "ExtInstWithForwardRefsKHR\0" // IR(31553, 26)
  "TraceRayKHR\0" // IR(31579, 12)
  "ExecuteCallableKHR\0" // IR(31591, 19)
  "ConvertUToAccelerationStructureKHR\0" // IR(31610, 35)
  "IgnoreIntersectionKHR\0" // IR(31645, 22)
  "TerminateRayKHR\0" // IR(31667, 16)
  "SPV_OPERAND_TYPE_OPTIONAL_PACKED_VECTOR_FORMAT\0" // IR(31683, 47)
  "SDot\0" // IR(31730, 5)
  "SDotKHR\0" // IR(31735, 8)
  "UDot\0" // IR(31743, 5)
  "UDotKHR\0" // IR(31748, 8)
  "SUDot\0" // IR(31756, 6)
  "SUDotKHR\0" // IR(31762, 9)
  "SDotAccSat\0" // IR(31771, 11)
  "SDotAccSatKHR\0" // IR(31782, 14)
  "UDotAccSat\0" // IR(31796, 11)
  "UDotAccSatKHR\0" // IR(31807, 14)
  "SUDotAccSat\0" // IR(31821, 12)
  "SUDotAccSatKHR\0" // IR(31833, 15)
  "TypeCooperativeMatrixKHR\0" // IR(31848, 25)
  "CooperativeMatrixLoadKHR\0" // IR(31873, 25)
  "CooperativeMatrixStoreKHR\0" // IR(31898, 26)
  "SPV_OPERAND_TYPE_OPTIONAL_COOPERATIVE_MATRIX_OPERANDS\0" // IR(31924, 54)
  "CooperativeMatrixMulAddKHR\0" // IR(31978, 27)
  "CooperativeMatrixLengthKHR\0" // IR(32005, 27)
  "ConstantCompositeReplicateEXT\0" // IR(32032, 30)
  "SpecConstantCompositeReplicateEXT\0" // IR(32062, 34)
  "CompositeConstructReplicateEXT\0" // IR(32096, 31)
  "TypeRayQueryKHR\0" // IR(32127, 16)
  "RayQueryInitializeKHR\0" // IR(32143, 22)
  "RayQueryTerminateKHR\0" // IR(32165, 21)
  "RayQueryGenerateIntersectionKHR\0" // IR(32186, 32)
  "RayQueryConfirmIntersectionKHR\0" // IR(32218, 31)
  "RayQueryProceedKHR\0" // IR(32249, 19)
  "RayQueryGetIntersectionTypeKHR\0" // IR(32268, 31)
  "ImageSampleWeightedQCOM\0" // IR(32299, 24)
  "ImageBoxFilterQCOM\0" // IR(32323, 19)
  "ImageBlockMatchSSDQCOM\0" // IR(32342, 23)
  "ImageBlockMatchSADQCOM\0" // IR(32365, 23)
  "ImageBlockMatchWindowSSDQCOM\0" // IR(32388, 29)
  "ImageBlockMatchWindowSADQCOM\0" // IR(32417, 29)
  "ImageBlockMatchGatherSSDQCOM\0" // IR(32446, 29)
  "ImageBlockMatchGatherSADQCOM\0" // IR(32475, 29)
  "GroupIAddNonUniformAMD\0" // IR(32504, 23)
  "GroupFAddNonUniformAMD\0" // IR(32527, 23)
  "GroupFMinNonUniformAMD\0" // IR(32550, 23)
  "GroupUMinNonUniformAMD\0" // IR(32573, 23)
  "GroupSMinNonUniformAMD\0" // IR(32596, 23)
  "GroupFMaxNonUniformAMD\0" // IR(32619, 23)
  "GroupUMaxNonUniformAMD\0" // IR(32642, 23)
  "GroupSMaxNonUniformAMD\0" // IR(32665, 23)
  "FragmentMaskFetchAMD\0" // IR(32688, 21)
  "FragmentFetchAMD\0" // IR(32709, 17)
  "ReadClockKHR\0" // IR(32726, 13)
  "AllocateNodePayloadsAMDX\0" // IR(32739, 25)
  "EnqueueNodePayloadsAMDX\0" // IR(32764, 24)
  "TypeNodePayloadArrayAMDX\0" // IR(32788, 25)
  "FinishWritingNodePayloadAMDX\0" // IR(32813, 29)
  "NodePayloadArrayLengthAMDX\0" // IR(32842, 27)
  "IsNodePayloadValidAMDX\0" // IR(32869, 23)
  "ConstantStringAMDX\0" // IR(32892, 19)
  "SpecConstantStringAMDX\0" // IR(32911, 23)
  "GroupNonUniformQuadAllKHR\0" // IR(32934, 26)
  "GroupNonUniformQuadAnyKHR\0" // IR(32960, 26)
  "HitObjectRecordHitMotionNV\0" // IR(32986, 27)
  "HitObjectRecordHitWithIndexMotionNV\0" // IR(33013, 36)
  "HitObjectRecordMissMotionNV\0" // IR(33049, 28)
  "HitObjectGetWorldToObjectNV\0" // IR(33077, 28)
  "HitObjectGetObjectToWorldNV\0" // IR(33105, 28)
  "HitObjectGetObjectRayDirectionNV\0" // IR(33133, 33)
  "HitObjectGetObjectRayOriginNV\0" // IR(33166, 30)
  "HitObjectTraceRayMotionNV\0" // IR(33196, 26)
  "HitObjectGetShaderRecordBufferHandleNV\0" // IR(33222, 39)
  "HitObjectGetShaderBindingTableRecordIndexNV\0" // IR(33261, 44)
  "HitObjectRecordEmptyNV\0" // IR(33305, 23)
  "HitObjectTraceRayNV\0" // IR(33328, 20)
  "HitObjectRecordHitNV\0" // IR(33348, 21)
  "HitObjectRecordHitWithIndexNV\0" // IR(33369, 30)
  "HitObjectRecordMissNV\0" // IR(33399, 22)
  "HitObjectExecuteShaderNV\0" // IR(33421, 25)
  "HitObjectGetCurrentTimeNV\0" // IR(33446, 26)
  "HitObjectGetAttributesNV\0" // IR(33472, 25)
  "HitObjectGetHitKindNV\0" // IR(33497, 22)
  "HitObjectGetPrimitiveIndexNV\0" // IR(33519, 29)
  "HitObjectGetGeometryIndexNV\0" // IR(33548, 28)
  "HitObjectGetInstanceIdNV\0" // IR(33576, 25)
  "HitObjectGetInstanceCustomIndexNV\0" // IR(33601, 34)
  "HitObjectGetWorldRayDirectionNV\0" // IR(33635, 32)
  "HitObjectGetWorldRayOriginNV\0" // IR(33667, 29)
  "HitObjectGetRayTMaxNV\0" // IR(33696, 22)
  "HitObjectGetRayTMinNV\0" // IR(33718, 22)
  "HitObjectIsEmptyNV\0" // IR(33740, 19)
  "HitObjectIsHitNV\0" // IR(33759, 17)
  "HitObjectIsMissNV\0" // IR(33776, 18)
  "ReorderThreadWithHitObjectNV\0" // IR(33794, 29)
  "ReorderThreadWithHintNV\0" // IR(33823, 24)
  "TypeHitObjectNV\0" // IR(33847, 16)
  "ImageSampleFootprintNV\0" // IR(33863, 23)
  "TypeCooperativeVectorNV\0" // IR(33886, 24)
  "CooperativeVectorMatrixMulNV\0" // IR(33910, 29)
  "CooperativeVectorOuterProductAccumulateNV\0" // IR(33939, 42)
  "CooperativeVectorReduceSumAccumulateNV\0" // IR(33981, 39)
  "CooperativeVectorMatrixMulAddNV\0" // IR(34020, 32)
  "CooperativeMatrixConvertNV\0" // IR(34052, 27)
  "EmitMeshTasksEXT\0" // IR(34079, 17)
  "SetMeshOutputsEXT\0" // IR(34096, 18)
  "GroupNonUniformPartitionNV\0" // IR(34114, 27)
  "WritePackedPrimitiveIndices4x8NV\0" // IR(34141, 33)
  "FetchMicroTriangleVertexPositionNV\0" // IR(34174, 35)
  "FetchMicroTriangleVertexBarycentricNV\0" // IR(34209, 38)
  "CooperativeVectorLoadNV\0" // IR(34247, 24)
  "CooperativeVectorStoreNV\0" // IR(34271, 25)
  "ReportIntersectionKHR\0" // IR(34296, 22)
  "ReportIntersectionNV\0" // IR(34318, 21)
  "IgnoreIntersectionNV\0" // IR(34339, 21)
  "TerminateRayNV\0" // IR(34360, 15)
  "TraceNV\0" // IR(34375, 8)
  "TraceMotionNV\0" // IR(34383, 14)
  "TraceRayMotionNV\0" // IR(34397, 17)
  "RayQueryGetIntersectionTriangleVertexPositionsKHR\0" // IR(34414, 50)
  "TypeAccelerationStructureKHR\0" // IR(34464, 29)
  "TypeAccelerationStructureNV\0" // IR(34493, 28)
  "ExecuteCallableNV\0" // IR(34521, 18)
  "RayQueryGetClusterIdNV\0" // IR(34539, 23)
  "HitObjectGetClusterIdNV\0" // IR(34562, 24)
  "TypeCooperativeMatrixNV\0" // IR(34586, 24)
  "CooperativeMatrixLoadNV\0" // IR(34610, 24)
  "CooperativeMatrixStoreNV\0" // IR(34634, 25)
  "CooperativeMatrixMulAddNV\0" // IR(34659, 26)
  "CooperativeMatrixLengthNV\0" // IR(34685, 26)
  "BeginInvocationInterlockEXT\0" // IR(34711, 28)
  "EndInvocationInterlockEXT\0" // IR(34739, 26)
  "SPV_OPERAND_TYPE_COOPERATIVE_MATRIX_REDUCE\0" // IR(34765, 43)
  "CooperativeMatrixReduceNV\0" // IR(34808, 26)
  "SPV_OPERAND_TYPE_MEMORY_ACCESS\0" // IR(34834, 31)
  "SPV_OPERAND_TYPE_TENSOR_ADDRESSING_OPERANDS\0" // IR(34865, 44)
  "CooperativeMatrixLoadTensorNV\0" // IR(34909, 30)
  "CooperativeMatrixStoreTensorNV\0" // IR(34939, 31)
  "CooperativeMatrixPerElementOpNV\0" // IR(34970, 32)
  "TypeTensorLayoutNV\0" // IR(35002, 19)
  "TypeTensorViewNV\0" // IR(35021, 17)
  "CreateTensorLayoutNV\0" // IR(35038, 21)
  "TensorLayoutSetDimensionNV\0" // IR(35059, 27)
  "TensorLayoutSetStrideNV\0" // IR(35086, 24)
  "TensorLayoutSliceNV\0" // IR(35110, 20)
  "TensorLayoutSetClampValueNV\0" // IR(35130, 28)
  "CreateTensorViewNV\0" // IR(35158, 19)
  "TensorViewSetDimensionNV\0" // IR(35177, 25)
  "TensorViewSetStrideNV\0" // IR(35202, 22)
  "IsHelperInvocationEXT\0" // IR(35224, 22)
  "TensorViewSetClipNV\0" // IR(35246, 20)
  "TensorLayoutSetBlockSizeNV\0" // IR(35266, 27)
  "CooperativeMatrixTransposeNV\0" // IR(35293, 29)
  "ConvertUToImageNV\0" // IR(35322, 18)
  "ConvertUToSamplerNV\0" // IR(35340, 20)
  "ConvertImageToUNV\0" // IR(35360, 18)
  "ConvertSamplerToUNV\0" // IR(35378, 20)
  "ConvertUToSampledImageNV\0" // IR(35398, 25)
  "ConvertSampledImageToUNV\0" // IR(35423, 25)
  "SamplerImageAddressingModeNV\0" // IR(35448, 29)
  "SPV_OPERAND_TYPE_OPTIONAL_RAW_ACCESS_CHAIN_OPERANDS\0" // IR(35477, 52)
  "RawAccessChainNV\0" // IR(35529, 17)
  "RayQueryGetIntersectionSpherePositionNV\0" // IR(35546, 40)
  "RayQueryGetIntersectionSphereRadiusNV\0" // IR(35586, 38)
  "RayQueryGetIntersectionLSSPositionsNV\0" // IR(35624, 38)
  "RayQueryGetIntersectionLSSRadiiNV\0" // IR(35662, 34)
  "RayQueryGetIntersectionLSSHitValueNV\0" // IR(35696, 37)
  "HitObjectGetSpherePositionNV\0" // IR(35733, 29)
  "HitObjectGetSphereRadiusNV\0" // IR(35762, 27)
  "HitObjectGetLSSPositionsNV\0" // IR(35789, 27)
  "HitObjectGetLSSRadiiNV\0" // IR(35816, 23)
  "HitObjectIsSphereHitNV\0" // IR(35839, 23)
  "HitObjectIsLSSHitNV\0" // IR(35862, 20)
  "RayQueryIsSphereHitNV\0" // IR(35882, 22)
  "RayQueryIsLSSHitNV\0" // IR(35904, 19)
  "SubgroupShuffleDownINTEL\0" // IR(35923, 25)
  "SubgroupShuffleUpINTEL\0" // IR(35948, 23)
  "SubgroupShuffleXorINTEL\0" // IR(35971, 24)
  "SubgroupBlockReadINTEL\0" // IR(35995, 23)
  "SubgroupBlockWriteINTEL\0" // IR(36018, 24)
  "SubgroupImageBlockReadINTEL\0" // IR(36042, 28)
  "SubgroupImageBlockWriteINTEL\0" // IR(36070, 29)
  "SubgroupImageMediaBlockReadINTEL\0" // IR(36099, 33)
  "SubgroupImageMediaBlockWriteINTEL\0" // IR(36132, 34)
  "UCountLeadingZerosINTEL\0" // IR(36166, 24)
  "UCountTrailingZerosINTEL\0" // IR(36190, 25)
  "AbsISubINTEL\0" // IR(36215, 13)
  "AbsUSubINTEL\0" // IR(36228, 13)
  "IAddSatINTEL\0" // IR(36241, 13)
  "UAddSatINTEL\0" // IR(36254, 13)
  "IAverageINTEL\0" // IR(36267, 14)
  "UAverageINTEL\0" // IR(36281, 14)
  "IAverageRoundedINTEL\0" // IR(36295, 21)
  "UAverageRoundedINTEL\0" // IR(36316, 21)
  "ISubSatINTEL\0" // IR(36337, 13)
  "USubSatINTEL\0" // IR(36350, 13)
  "IMul32x16INTEL\0" // IR(36363, 15)
  "UMul32x16INTEL\0" // IR(36378, 15)
  "ConstantFunctionPointerINTEL\0" // IR(36393, 29)
  "FunctionPointerCallINTEL\0" // IR(36422, 25)
  "AsmTargetINTEL\0" // IR(36447, 15)
  "AsmCallINTEL\0" // IR(36462, 13)
  "AtomicFMinEXT\0" // IR(36475, 14)
  "AtomicFMaxEXT\0" // IR(36489, 14)
  "AssumeTrueKHR\0" // IR(36503, 14)
  "ExpectKHR\0" // IR(36517, 10)
  "DecorateString\0" // IR(36527, 15)
  "DecorateStringGOOGLE\0" // IR(36542, 21)
  "MemberDecorateString\0" // IR(36563, 21)
  "MemberDecorateStringGOOGLE\0" // IR(36584, 27)
  "VmeImageINTEL\0" // IR(36611, 14)
  "TypeVmeImageINTEL\0" // IR(36625, 18)
  "TypeAvcImePayloadINTEL\0" // IR(36643, 23)
  "TypeAvcRefPayloadINTEL\0" // IR(36666, 23)
  "TypeAvcSicPayloadINTEL\0" // IR(36689, 23)
  "TypeAvcMcePayloadINTEL\0" // IR(36712, 23)
  "TypeAvcMceResultINTEL\0" // IR(36735, 22)
  "TypeAvcImeResultINTEL\0" // IR(36757, 22)
  "TypeAvcImeResultSingleReferenceStreamoutINTEL\0" // IR(36779, 46)
  "TypeAvcImeResultDualReferenceStreamoutINTEL\0" // IR(36825, 44)
  "TypeAvcImeSingleReferenceStreaminINTEL\0" // IR(36869, 39)
  "TypeAvcImeDualReferenceStreaminINTEL\0" // IR(36908, 37)
  "TypeAvcRefResultINTEL\0" // IR(36945, 22)
  "TypeAvcSicResultINTEL\0" // IR(36967, 22)
  "SubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL\0" // IR(36989, 60)
  "SubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL\0" // IR(37049, 53)
  "SubgroupAvcMceGetDefaultInterShapePenaltyINTEL\0" // IR(37102, 47)
  "SubgroupAvcMceSetInterShapePenaltyINTEL\0" // IR(37149, 40)
  "SubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL\0" // IR(37189, 51)
  "SubgroupAvcMceSetInterDirectionPenaltyINTEL\0" // IR(37240, 44)
  "SubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL\0" // IR(37284, 51)
  "SubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL\0" // IR(37335, 56)
  "SubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL\0" // IR(37391, 50)
  "SubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL\0" // IR(37441, 52)
  "SubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL\0" // IR(37493, 49)
  "SubgroupAvcMceSetMotionVectorCostFunctionINTEL\0" // IR(37542, 47)
  "SubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL\0" // IR(37589, 50)
  "SubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL\0" // IR(37639, 51)
  "SubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL\0" // IR(37690, 56)
  "SubgroupAvcMceSetAcOnlyHaarINTEL\0" // IR(37746, 33)
  "SubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL\0" // IR(37779, 52)
  "SubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL\0" // IR(37831, 61)
  "SubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL\0" // IR(37892, 61)
  "SubgroupAvcMceConvertToImePayloadINTEL\0" // IR(37953, 39)
  "SubgroupAvcMceConvertToImeResultINTEL\0" // IR(37992, 38)
  "SubgroupAvcMceConvertToRefPayloadINTEL\0" // IR(38030, 39)
  "SubgroupAvcMceConvertToRefResultINTEL\0" // IR(38069, 38)
  "SubgroupAvcMceConvertToSicPayloadINTEL\0" // IR(38107, 39)
  "SubgroupAvcMceConvertToSicResultINTEL\0" // IR(38146, 38)
  "SubgroupAvcMceGetMotionVectorsINTEL\0" // IR(38184, 36)
  "SubgroupAvcMceGetInterDistortionsINTEL\0" // IR(38220, 39)
  "SubgroupAvcMceGetBestInterDistortionsINTEL\0" // IR(38259, 43)
  "SubgroupAvcMceGetInterMajorShapeINTEL\0" // IR(38302, 38)
  "SubgroupAvcMceGetInterMinorShapeINTEL\0" // IR(38340, 38)
  "SubgroupAvcMceGetInterDirectionsINTEL\0" // IR(38378, 38)
  "SubgroupAvcMceGetInterMotionVectorCountINTEL\0" // IR(38416, 45)
  "SubgroupAvcMceGetInterReferenceIdsINTEL\0" // IR(38461, 40)
  "SubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL\0" // IR(38501, 62)
  "SubgroupAvcImeInitializeINTEL\0" // IR(38563, 30)
  "SubgroupAvcImeSetSingleReferenceINTEL\0" // IR(38593, 38)
  "SubgroupAvcImeSetDualReferenceINTEL\0" // IR(38631, 36)
  "SubgroupAvcImeRefWindowSizeINTEL\0" // IR(38667, 33)
  "SubgroupAvcImeAdjustRefOffsetINTEL\0" // IR(38700, 35)
  "SubgroupAvcImeConvertToMcePayloadINTEL\0" // IR(38735, 39)
  "SubgroupAvcImeSetMaxMotionVectorCountINTEL\0" // IR(38774, 43)
  "SubgroupAvcImeSetUnidirectionalMixDisableINTEL\0" // IR(38817, 47)
  "SubgroupAvcImeSetEarlySearchTerminationThresholdINTEL\0" // IR(38864, 54)
  "SubgroupAvcImeSetWeightedSadINTEL\0" // IR(38918, 34)
  "SubgroupAvcImeEvaluateWithSingleReferenceINTEL\0" // IR(38952, 47)
  "SubgroupAvcImeEvaluateWithDualReferenceINTEL\0" // IR(38999, 45)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL\0" // IR(39044, 55)
  "SubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL\0" // IR(39099, 53)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL\0" // IR(39152, 56)
  "SubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL\0" // IR(39208, 54)
  "SubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL\0" // IR(39262, 58)
  "SubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL\0" // IR(39320, 56)
  "SubgroupAvcImeConvertToMceResultINTEL\0" // IR(39376, 38)
  "SubgroupAvcImeGetSingleReferenceStreaminINTEL\0" // IR(39414, 46)
  "SubgroupAvcImeGetDualReferenceStreaminINTEL\0" // IR(39460, 44)
  "SubgroupAvcImeStripSingleReferenceStreamoutINTEL\0" // IR(39504, 49)
  "SubgroupAvcImeStripDualReferenceStreamoutINTEL\0" // IR(39553, 47)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL\0" // IR(39600, 70)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL\0" // IR(39670, 68)
  "SubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL\0" // IR(39738, 69)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL\0" // IR(39807, 68)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL\0" // IR(39875, 66)
  "SubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL\0" // IR(39941, 67)
  "SubgroupAvcImeGetBorderReachedINTEL\0" // IR(40008, 36)
  "SubgroupAvcImeGetTruncatedSearchIndicationINTEL\0" // IR(40044, 48)
  "SubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL\0" // IR(40092, 59)
  "SubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL\0" // IR(40151, 58)
  "SubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL\0" // IR(40209, 56)
  "SubgroupAvcFmeInitializeINTEL\0" // IR(40265, 30)
  "SubgroupAvcBmeInitializeINTEL\0" // IR(40295, 30)
  "SubgroupAvcRefConvertToMcePayloadINTEL\0" // IR(40325, 39)
  "SubgroupAvcRefSetBidirectionalMixDisableINTEL\0" // IR(40364, 46)
  "SubgroupAvcRefSetBilinearFilterEnableINTEL\0" // IR(40410, 43)
  "SubgroupAvcRefEvaluateWithSingleReferenceINTEL\0" // IR(40453, 47)
  "SubgroupAvcRefEvaluateWithDualReferenceINTEL\0" // IR(40500, 45)
  "SubgroupAvcRefEvaluateWithMultiReferenceINTEL\0" // IR(40545, 46)
  "SubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL\0" // IR(40591, 56)
  "SubgroupAvcRefConvertToMceResultINTEL\0" // IR(40647, 38)
  "SubgroupAvcSicInitializeINTEL\0" // IR(40685, 30)
  "SubgroupAvcSicConfigureSkcINTEL\0" // IR(40715, 32)
  "SubgroupAvcSicConfigureIpeLumaINTEL\0" // IR(40747, 36)
  "SubgroupAvcSicConfigureIpeLumaChromaINTEL\0" // IR(40783, 42)
  "SubgroupAvcSicGetMotionVectorMaskINTEL\0" // IR(40825, 39)
  "SubgroupAvcSicConvertToMcePayloadINTEL\0" // IR(40864, 39)
  "SubgroupAvcSicSetIntraLumaShapePenaltyINTEL\0" // IR(40903, 44)
  "SubgroupAvcSicSetIntraLumaModeCostFunctionINTEL\0" // IR(40947, 48)
  "SubgroupAvcSicSetIntraChromaModeCostFunctionINTEL\0" // IR(40995, 50)
  "SubgroupAvcSicSetBilinearFilterEnableINTEL\0" // IR(41045, 43)
  "SubgroupAvcSicSetSkcForwardTransformEnableINTEL\0" // IR(41088, 48)
  "SubgroupAvcSicSetBlockBasedRawSkipSadINTEL\0" // IR(41136, 43)
  "SubgroupAvcSicEvaluateIpeINTEL\0" // IR(41179, 31)
  "SubgroupAvcSicEvaluateWithSingleReferenceINTEL\0" // IR(41210, 47)
  "SubgroupAvcSicEvaluateWithDualReferenceINTEL\0" // IR(41257, 45)
  "SubgroupAvcSicEvaluateWithMultiReferenceINTEL\0" // IR(41302, 46)
  "SubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL\0" // IR(41348, 56)
  "SubgroupAvcSicConvertToMceResultINTEL\0" // IR(41404, 38)
  "SubgroupAvcSicGetIpeLumaShapeINTEL\0" // IR(41442, 35)
  "SubgroupAvcSicGetBestIpeLumaDistortionINTEL\0" // IR(41477, 44)
  "SubgroupAvcSicGetBestIpeChromaDistortionINTEL\0" // IR(41521, 46)
  "SubgroupAvcSicGetPackedIpeLumaModesINTEL\0" // IR(41567, 41)
  "SubgroupAvcSicGetIpeChromaModeINTEL\0" // IR(41608, 36)
  "SubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL\0" // IR(41644, 50)
  "SubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL\0" // IR(41694, 48)
  "SubgroupAvcSicGetInterRawSadsINTEL\0" // IR(41742, 35)
  "SaveMemoryINTEL\0" // IR(41777, 16)
  "RestoreMemoryINTEL\0" // IR(41793, 19)
  "ArbitraryFloatSinCosPiINTEL\0" // IR(41812, 28)
  "ArbitraryFloatCastINTEL\0" // IR(41840, 24)
  "ArbitraryFloatCastFromIntINTEL\0" // IR(41864, 31)
  "ArbitraryFloatCastToIntINTEL\0" // IR(41895, 29)
  "ArbitraryFloatAddINTEL\0" // IR(41924, 23)
  "ArbitraryFloatSubINTEL\0" // IR(41947, 23)
  "ArbitraryFloatMulINTEL\0" // IR(41970, 23)
  "ArbitraryFloatDivINTEL\0" // IR(41993, 23)
  "ArbitraryFloatGTINTEL\0" // IR(42016, 22)
  "ArbitraryFloatGEINTEL\0" // IR(42038, 22)
  "ArbitraryFloatLTINTEL\0" // IR(42060, 22)
  "ArbitraryFloatLEINTEL\0" // IR(42082, 22)
  "ArbitraryFloatEQINTEL\0" // IR(42104, 22)
  "ArbitraryFloatRecipINTEL\0" // IR(42126, 25)
  "ArbitraryFloatRSqrtINTEL\0" // IR(42151, 25)
  "ArbitraryFloatCbrtINTEL\0" // IR(42176, 24)
  "ArbitraryFloatHypotINTEL\0" // IR(42200, 25)
  "ArbitraryFloatSqrtINTEL\0" // IR(42225, 24)
  "ArbitraryFloatLogINTEL\0" // IR(42249, 23)
  "ArbitraryFloatLog2INTEL\0" // IR(42272, 24)
  "ArbitraryFloatLog10INTEL\0" // IR(42296, 25)
  "ArbitraryFloatLog1pINTEL\0" // IR(42321, 25)
  "ArbitraryFloatExpINTEL\0" // IR(42346, 23)
  "ArbitraryFloatExp2INTEL\0" // IR(42369, 24)
  "ArbitraryFloatExp10INTEL\0" // IR(42393, 25)
  "ArbitraryFloatExpm1INTEL\0" // IR(42418, 25)
  "ArbitraryFloatSinINTEL\0" // IR(42443, 23)
  "ArbitraryFloatCosINTEL\0" // IR(42466, 23)
  "ArbitraryFloatSinCosINTEL\0" // IR(42489, 26)
  "ArbitraryFloatSinPiINTEL\0" // IR(42515, 25)
  "ArbitraryFloatCosPiINTEL\0" // IR(42540, 25)
  "ArbitraryFloatASinINTEL\0" // IR(42565, 24)
  "ArbitraryFloatASinPiINTEL\0" // IR(42589, 26)
  "ArbitraryFloatACosINTEL\0" // IR(42615, 24)
  "ArbitraryFloatACosPiINTEL\0" // IR(42639, 26)
  "ArbitraryFloatATanINTEL\0" // IR(42665, 24)
  "ArbitraryFloatATanPiINTEL\0" // IR(42689, 26)
  "ArbitraryFloatATan2INTEL\0" // IR(42715, 25)
  "ArbitraryFloatPowINTEL\0" // IR(42740, 23)
  "ArbitraryFloatPowRINTEL\0" // IR(42763, 24)
  "ArbitraryFloatPowNINTEL\0" // IR(42787, 24)
  "LoopControlINTEL\0" // IR(42811, 17)
  "AliasDomainDeclINTEL\0" // IR(42828, 21)
  "AliasScopeDeclINTEL\0" // IR(42849, 20)
  "AliasScopeListDeclINTEL\0" // IR(42869, 24)
  "FixedSqrtINTEL\0" // IR(42893, 15)
  "FixedRecipINTEL\0" // IR(42908, 16)
  "FixedRsqrtINTEL\0" // IR(42924, 16)
  "FixedSinINTEL\0" // IR(42940, 14)
  "FixedCosINTEL\0" // IR(42954, 14)
  "FixedSinCosINTEL\0" // IR(42968, 17)
  "FixedSinPiINTEL\0" // IR(42985, 16)
  "FixedCosPiINTEL\0" // IR(43001, 16)
  "FixedSinCosPiINTEL\0" // IR(43017, 19)
  "FixedLogINTEL\0" // IR(43036, 14)
  "FixedExpINTEL\0" // IR(43050, 14)
  "PtrCastToCrossWorkgroupINTEL\0" // IR(43064, 29)
  "CrossWorkgroupCastToPtrINTEL\0" // IR(43093, 29)
  "ReadPipeBlockingINTEL\0" // IR(43122, 22)
  "WritePipeBlockingINTEL\0" // IR(43144, 23)
  "RayQueryGetRayTMinKHR\0" // IR(43167, 22)
  "RayQueryGetRayFlagsKHR\0" // IR(43189, 23)
  "RayQueryGetIntersectionTKHR\0" // IR(43212, 28)
  "RayQueryGetIntersectionInstanceCustomIndexKHR\0" // IR(43240, 46)
  "RayQueryGetIntersectionInstanceIdKHR\0" // IR(43286, 37)
  "RayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR\0" // IR(43323, 65)
  "RayQueryGetIntersectionGeometryIndexKHR\0" // IR(43388, 40)
  "RayQueryGetIntersectionPrimitiveIndexKHR\0" // IR(43428, 41)
  "RayQueryGetIntersectionBarycentricsKHR\0" // IR(43469, 39)
  "RayQueryGetIntersectionFrontFaceKHR\0" // IR(43508, 36)
  "RayQueryGetIntersectionCandidateAABBOpaqueKHR\0" // IR(43544, 46)
  "RayQueryGetIntersectionObjectRayDirectionKHR\0" // IR(43590, 45)
  "RayQueryGetIntersectionObjectRayOriginKHR\0" // IR(43635, 42)
  "RayQueryGetWorldRayDirectionKHR\0" // IR(43677, 32)
  "RayQueryGetWorldRayOriginKHR\0" // IR(43709, 29)
  "RayQueryGetIntersectionObjectToWorldKHR\0" // IR(43738, 40)
  "RayQueryGetIntersectionWorldToObjectKHR\0" // IR(43778, 40)
  "AtomicFAddEXT\0" // IR(43818, 14)
  "TypeBufferSurfaceINTEL\0" // IR(43832, 23)
  "TypeStructContinuedINTEL\0" // IR(43855, 25)
  "ConstantCompositeContinuedINTEL\0" // IR(43880, 32)
  "SpecConstantCompositeContinuedINTEL\0" // IR(43912, 36)
  "CompositeConstructContinuedINTEL\0" // IR(43948, 33)
  "ConvertFToBF16INTEL\0" // IR(43981, 20)
  "ConvertBF16ToFINTEL\0" // IR(44001, 20)
  "ControlBarrierArriveINTEL\0" // IR(44021, 26)
  "ControlBarrierWaitINTEL\0" // IR(44047, 24)
  "TaskSequenceCreateINTEL\0" // IR(44071, 24)
  "TaskSequenceAsyncINTEL\0" // IR(44095, 23)
  "TaskSequenceGetINTEL\0" // IR(44118, 21)
  "TaskSequenceReleaseINTEL\0" // IR(44139, 25)
  "TypeTaskSequenceINTEL\0" // IR(44164, 22)
  "SubgroupBlockPrefetchINTEL\0" // IR(44186, 27)
  "Subgroup2DBlockLoadINTEL\0" // IR(44213, 25)
  "Subgroup2DBlockLoadTransformINTEL\0" // IR(44238, 34)
  "Subgroup2DBlockLoadTransposeINTEL\0" // IR(44272, 34)
  "Subgroup2DBlockPrefetchINTEL\0" // IR(44306, 29)
  "Subgroup2DBlockStoreINTEL\0" // IR(44335, 26)
  "SPV_OPERAND_TYPE_OPTIONAL_MATRIX_MULTIPLY_ACCUMULATE_OPERANDS\0" // IR(44361, 62)
  "BitwiseFunctionINTEL\0" // IR(44423, 21)
  "GroupIMulKHR\0" // IR(44444, 13)
  "GroupFMulKHR\0" // IR(44457, 13)
  "GroupBitwiseAndKHR\0" // IR(44470, 19)
  "GroupBitwiseOrKHR\0" // IR(44489, 18)
  "GroupBitwiseXorKHR\0" // IR(44507, 19)
  "GroupLogicalAndKHR\0" // IR(44526, 19)
  "GroupLogicalOrKHR\0" // IR(44545, 18)
  "GroupLogicalXorKHR\0" // IR(44563, 19)
  "RoundFToTF32INTEL\0" // IR(44582, 18)
  "MaskedGatherINTEL\0" // IR(44600, 18)
  "MaskedScatterINTEL\0" // IR(44618, 19)
  "DebugInfoNone\0" // IR(44637, 14)
  "DebugCompilationUnit\0" // IR(44651, 21)
  "SPV_OPERAND_TYPE_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING\0" // IR(44672, 52)
  "DebugTypeBasic\0" // IR(44724, 15)
  "SPV_OPERAND_TYPE_DEBUG_INFO_FLAGS\0" // IR(44739, 34)
  "DebugTypePointer\0" // IR(44773, 17)
  "SPV_OPERAND_TYPE_DEBUG_TYPE_QUALIFIER\0" // IR(44790, 38)
  "DebugTypeQualifier\0" // IR(44828, 19)
  "DebugTypeArray\0" // IR(44847, 15)
  "DebugTypeVector\0" // IR(44862, 16)
  "DebugTypedef\0" // IR(44878, 13)
  "DebugTypeFunction\0" // IR(44891, 18)
  "DebugTypeEnum\0" // IR(44909, 14)
  "SPV_OPERAND_TYPE_DEBUG_COMPOSITE_TYPE\0" // IR(44923, 38)
  "DebugTypeComposite\0" // IR(44961, 19)
  "DebugTypeMember\0" // IR(44980, 16)
  "DebugTypeInheritance\0" // IR(44996, 21)
  "DebugTypePtrToMember\0" // IR(45017, 21)
  "DebugTypeTemplate\0" // IR(45038, 18)
  "DebugTypeTemplateParameter\0" // IR(45056, 27)
  "DebugTypeTemplateTemplateParameter\0" // IR(45083, 35)
  "DebugTypeTemplateParameterPack\0" // IR(45118, 31)
  "DebugGlobalVariable\0" // IR(45149, 20)
  "DebugFunctionDeclaration\0" // IR(45169, 25)
  "DebugFunction\0" // IR(45194, 14)
  "DebugLexicalBlock\0" // IR(45208, 18)
  "DebugLexicalBlockDiscriminator\0" // IR(45226, 31)
  "DebugScope\0" // IR(45257, 11)
  "DebugNoScope\0" // IR(45268, 13)
  "DebugInlinedAt\0" // IR(45281, 15)
  "SPV_OPERAND_TYPE_OPTIONAL_LITERAL_INTEGER\0" // IR(45296, 42)
  "DebugLocalVariable\0" // IR(45338, 19)
  "DebugInlinedVariable\0" // IR(45357, 21)
  "DebugDeclare\0" // IR(45378, 13)
  "DebugValue\0" // IR(45391, 11)
  "SPV_OPERAND_TYPE_DEBUG_OPERATION\0" // IR(45402, 33)
  "DebugOperation\0" // IR(45435, 15)
  "DebugExpression\0" // IR(45450, 16)
  "DebugMacroDef\0" // IR(45466, 14)
  "DebugMacroUndef\0" // IR(45480, 16)
  "Round\0" // IR(45496, 6)
  "RoundEven\0" // IR(45502, 10)
  "Trunc\0" // IR(45512, 6)
  "FAbs\0" // IR(45518, 5)
  "SAbs\0" // IR(45523, 5)
  "FSign\0" // IR(45528, 6)
  "SSign\0" // IR(45534, 6)
  "Floor\0" // IR(45540, 6)
  "Ceil\0" // IR(45546, 5)
  "Fract\0" // IR(45551, 6)
  "Radians\0" // IR(45557, 8)
  "Degrees\0" // IR(45565, 8)
  "Sin\0" // IR(45573, 4)
  "Cos\0" // IR(45577, 4)
  "Tan\0" // IR(45581, 4)
  "Asin\0" // IR(45585, 5)
  "Acos\0" // IR(45590, 5)
  "Atan\0" // IR(45595, 5)
  "Sinh\0" // IR(45600, 5)
  "Cosh\0" // IR(45605, 5)
  "Tanh\0" // IR(45610, 5)
  "Asinh\0" // IR(45615, 6)
  "Acosh\0" // IR(45621, 6)
  "Atanh\0" // IR(45627, 6)
  "Atan2\0" // IR(45633, 6)
  "Pow\0" // IR(45639, 4)
  "Exp\0" // IR(45643, 4)
  "Log\0" // IR(45647, 4)
  "Exp2\0" // IR(45651, 5)
  "Log2\0" // IR(45656, 5)
  "Sqrt\0" // IR(45661, 5)
  "InverseSqrt\0" // IR(45666, 12)
  "Determinant\0" // IR(45678, 12)
  "MatrixInverse\0" // IR(45690, 14)
  "Modf\0" // IR(45704, 5)
  "ModfStruct\0" // IR(45709, 11)
  "FMin\0" // IR(45720, 5)
  "UMin\0" // IR(45725, 5)
  "SMin\0" // IR(45730, 5)
  "FMax\0" // IR(45735, 5)
  "UMax\0" // IR(45740, 5)
  "SMax\0" // IR(45745, 5)
  "FClamp\0" // IR(45750, 7)
  "UClamp\0" // IR(45757, 7)
  "SClamp\0" // IR(45764, 7)
  "FMix\0" // IR(45771, 5)
  "IMix\0" // IR(45776, 5)
  "Step\0" // IR(45781, 5)
  "SmoothStep\0" // IR(45786, 11)
  "Fma\0" // IR(45797, 4)
  "Frexp\0" // IR(45801, 6)
  "FrexpStruct\0" // IR(45807, 12)
  "Ldexp\0" // IR(45819, 6)
  "PackSnorm4x8\0" // IR(45825, 13)
  "PackUnorm4x8\0" // IR(45838, 13)
  "PackSnorm2x16\0" // IR(45851, 14)
  "PackUnorm2x16\0" // IR(45865, 14)
  "PackHalf2x16\0" // IR(45879, 13)
  "PackDouble2x32\0" // IR(45892, 15)
  "UnpackSnorm2x16\0" // IR(45907, 16)
  "UnpackUnorm2x16\0" // IR(45923, 16)
  "UnpackHalf2x16\0" // IR(45939, 15)
  "UnpackSnorm4x8\0" // IR(45954, 15)
  "UnpackUnorm4x8\0" // IR(45969, 15)
  "UnpackDouble2x32\0" // IR(45984, 17)
  "Length\0" // IR(46001, 7)
  "Distance\0" // IR(46008, 9)
  "Cross\0" // IR(46017, 6)
  "Normalize\0" // IR(46023, 10)
  "FaceForward\0" // IR(46033, 12)
  "Reflect\0" // IR(46045, 8)
  "Refract\0" // IR(46053, 8)
  "FindILsb\0" // IR(46061, 9)
  "FindSMsb\0" // IR(46070, 9)
  "FindUMsb\0" // IR(46079, 9)
  "InterpolateAtCentroid\0" // IR(46088, 22)
  "InterpolateAtSample\0" // IR(46110, 20)
  "InterpolateAtOffset\0" // IR(46130, 20)
  "NMin\0" // IR(46150, 5)
  "NMax\0" // IR(46155, 5)
  "NClamp\0" // IR(46160, 7)
  "ArgumentInfo\0" // IR(46167, 13)
  "ArgumentStorageBuffer\0" // IR(46180, 22)
  "ArgumentUniform\0" // IR(46202, 16)
  "ArgumentPodStorageBuffer\0" // IR(46218, 25)
  "ArgumentPodUniform\0" // IR(46243, 19)
  "ArgumentPodPushConstant\0" // IR(46262, 24)
  "ArgumentSampledImage\0" // IR(46286, 21)
  "ArgumentStorageImage\0" // IR(46307, 21)
  "ArgumentSampler\0" // IR(46328, 16)
  "ArgumentWorkgroup\0" // IR(46344, 18)
  "SpecConstantWorkgroupSize\0" // IR(46362, 26)
  "SpecConstantGlobalOffset\0" // IR(46388, 25)
  "SpecConstantWorkDim\0" // IR(46413, 20)
  "PushConstantGlobalOffset\0" // IR(46433, 25)
  "PushConstantEnqueuedLocalSize\0" // IR(46458, 30)
  "PushConstantGlobalSize\0" // IR(46488, 23)
  "PushConstantRegionOffset\0" // IR(46511, 25)
  "PushConstantNumWorkgroups\0" // IR(46536, 26)
  "PushConstantRegionGroupOffset\0" // IR(46562, 30)
  "ConstantDataStorageBuffer\0" // IR(46592, 26)
  "ConstantDataUniform\0" // IR(46618, 20)
  "PropertyRequiredWorkgroupSize\0" // IR(46638, 30)
  "SpecConstantSubgroupMaxSize\0" // IR(46668, 28)
  "ArgumentPointerPushConstant\0" // IR(46696, 28)
  "ArgumentPointerUniform\0" // IR(46724, 23)
  "ProgramScopeVariablesStorageBuffer\0" // IR(46747, 35)
  "ProgramScopeVariablePointerRelocation\0" // IR(46782, 38)
  "ImageArgumentInfoChannelOrderPushConstant\0" // IR(46820, 42)
  "ImageArgumentInfoChannelDataTypePushConstant\0" // IR(46862, 45)
  "ImageArgumentInfoChannelOrderUniform\0" // IR(46907, 37)
  "ImageArgumentInfoChannelDataTypeUniform\0" // IR(46944, 40)
  "ArgumentStorageTexelBuffer\0" // IR(46984, 27)
  "ArgumentUniformTexelBuffer\0" // IR(47011, 27)
  "ConstantDataPointerPushConstant\0" // IR(47038, 32)
  "ProgramScopeVariablePointerPushConstant\0" // IR(47070, 40)
  "PrintfInfo\0" // IR(47110, 11)
  "PrintfBufferStorageBuffer\0" // IR(47121, 26)
  "PrintfBufferPointerPushConstant\0" // IR(47147, 32)
  "NormalizedSamplerMaskPushConstant\0" // IR(47179, 34)
  "WorkgroupVariableSize\0" // IR(47213, 22)
  "DebugImportedEntity\0" // IR(47235, 20)
  "DebugSource\0" // IR(47255, 12)
  "DebugFunctionDefinition\0" // IR(47267, 24)
  "DebugSourceContinued\0" // IR(47291, 21)
  "DebugLine\0" // IR(47312, 10)
  "DebugNoLine\0" // IR(47322, 12)
  "DebugBuildIdentifier\0" // IR(47334, 21)
  "DebugStoragePath\0" // IR(47355, 17)
  "DebugEntryPoint\0" // IR(47372, 16)
  "DebugTypeMatrix\0" // IR(47388, 16)
  "Configuration\0" // IR(47404, 14)
  "StartCounter\0" // IR(47418, 13)
  "StopCounter\0" // IR(47431, 12)
  "PushConstants\0" // IR(47443, 14)
  "SpecializationMapEntry\0" // IR(47457, 23)
  "DescriptorSetBuffer\0" // IR(47480, 20)
  "DescriptorSetImage\0" // IR(47500, 19)
  "DescriptorSetSampler\0" // IR(47519, 21)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_BASE_TYPE_ATTRIBUTE_ENCODING\0" // IR(47540, 63)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_INFO_FLAGS\0" // IR(47603, 45)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_TYPE_QUALIFIER\0" // IR(47648, 49)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_COMPOSITE_TYPE\0" // IR(47697, 49)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_OPERATION\0" // IR(47746, 44)
  "SPV_OPERAND_TYPE_CLDEBUG100_DEBUG_IMPORTED_ENTITY\0" // IR(47790, 50)
  "DebugModuleINTEL\0" // IR(47840, 17)
  "acos\0" // IR(47857, 5)
  "acosh\0" // IR(47862, 6)
  "acospi\0" // IR(47868, 7)
  "asin\0" // IR(47875, 5)
  "asinh\0" // IR(47880, 6)
  "asinpi\0" // IR(47886, 7)
  "atan\0" // IR(47893, 5)
  "atan2\0" // IR(47898, 6)
  "atanh\0" // IR(47904, 6)
  "atanpi\0" // IR(47910, 7)
  "atan2pi\0" // IR(47917, 8)
  "cbrt\0" // IR(47925, 5)
  "ceil\0" // IR(47930, 5)
  "copysign\0" // IR(47935, 9)
  "cos\0" // IR(47944, 4)
  "cosh\0" // IR(47948, 5)
  "cospi\0" // IR(47953, 6)
  "erfc\0" // IR(47959, 5)
  "erf\0" // IR(47964, 4)
  "exp\0" // IR(47968, 4)
  "exp2\0" // IR(47972, 5)
  "exp10\0" // IR(47977, 6)
  "expm1\0" // IR(47983, 6)
  "fabs\0" // IR(47989, 5)
  "fdim\0" // IR(47994, 5)
  "floor\0" // IR(47999, 6)
  "fma\0" // IR(48005, 4)
  "fmax\0" // IR(48009, 5)
  "fmin\0" // IR(48014, 5)
  "fmod\0" // IR(48019, 5)
  "fract\0" // IR(48024, 6)
  "frexp\0" // IR(48030, 6)
  "hypot\0" // IR(48036, 6)
  "ilogb\0" // IR(48042, 6)
  "ldexp\0" // IR(48048, 6)
  "lgamma\0" // IR(48054, 7)
  "lgamma_r\0" // IR(48061, 9)
  "log\0" // IR(48070, 4)
  "log2\0" // IR(48074, 5)
  "log10\0" // IR(48079, 6)
  "log1p\0" // IR(48085, 6)
  "logb\0" // IR(48091, 5)
  "mad\0" // IR(48096, 4)
  "maxmag\0" // IR(48100, 7)
  "minmag\0" // IR(48107, 7)
  "modf\0" // IR(48114, 5)
  "nan\0" // IR(48119, 4)
  "nextafter\0" // IR(48123, 10)
  "pow\0" // IR(48133, 4)
  "pown\0" // IR(48137, 5)
  "powr\0" // IR(48142, 5)
  "remainder\0" // IR(48147, 10)
  "remquo\0" // IR(48157, 7)
  "rint\0" // IR(48164, 5)
  "rootn\0" // IR(48169, 6)
  "round\0" // IR(48175, 6)
  "rsqrt\0" // IR(48181, 6)
  "sin\0" // IR(48187, 4)
  "sincos\0" // IR(48191, 7)
  "sinh\0" // IR(48198, 5)
  "sinpi\0" // IR(48203, 6)
  "sqrt\0" // IR(48209, 5)
  "tan\0" // IR(48214, 4)
  "tanh\0" // IR(48218, 5)
  "tanpi\0" // IR(48223, 6)
  "tgamma\0" // IR(48229, 7)
  "trunc\0" // IR(48236, 6)
  "half_cos\0" // IR(48242, 9)
  "half_divide\0" // IR(48251, 12)
  "half_exp\0" // IR(48263, 9)
  "half_exp2\0" // IR(48272, 10)
  "half_exp10\0" // IR(48282, 11)
  "half_log\0" // IR(48293, 9)
  "half_log2\0" // IR(48302, 10)
  "half_log10\0" // IR(48312, 11)
  "half_powr\0" // IR(48323, 10)
  "half_recip\0" // IR(48333, 11)
  "half_rsqrt\0" // IR(48344, 11)
  "half_sin\0" // IR(48355, 9)
  "half_sqrt\0" // IR(48364, 10)
  "half_tan\0" // IR(48374, 9)
  "native_cos\0" // IR(48383, 11)
  "native_divide\0" // IR(48394, 14)
  "native_exp\0" // IR(48408, 11)
  "native_exp2\0" // IR(48419, 12)
  "native_exp10\0" // IR(48431, 13)
  "native_log\0" // IR(48444, 11)
  "native_log2\0" // IR(48455, 12)
  "native_log10\0" // IR(48467, 13)
  "native_powr\0" // IR(48480, 12)
  "native_recip\0" // IR(48492, 13)
  "native_rsqrt\0" // IR(48505, 13)
  "native_sin\0" // IR(48518, 11)
  "native_sqrt\0" // IR(48529, 12)
  "native_tan\0" // IR(48541, 11)
  "fclamp\0" // IR(48552, 7)
  "degrees\0" // IR(48559, 8)
  "fmax_common\0" // IR(48567, 12)
  "fmin_common\0" // IR(48579, 12)
  "mix\0" // IR(48591, 4)
  "radians\0" // IR(48595, 8)
  "step\0" // IR(48603, 5)
  "smoothstep\0" // IR(48608, 11)
  "sign\0" // IR(48619, 5)
  "cross\0" // IR(48624, 6)
  "distance\0" // IR(48630, 9)
  "length\0" // IR(48639, 7)
  "normalize\0" // IR(48646, 10)
  "fast_distance\0" // IR(48656, 14)
  "fast_length\0" // IR(48670, 12)
  "fast_normalize\0" // IR(48682, 15)
  "s_abs\0" // IR(48697, 6)
  "s_abs_diff\0" // IR(48703, 11)
  "s_add_sat\0" // IR(48714, 10)
  "u_add_sat\0" // IR(48724, 10)
  "s_hadd\0" // IR(48734, 7)
  "u_hadd\0" // IR(48741, 7)
  "s_rhadd\0" // IR(48748, 8)
  "u_rhadd\0" // IR(48756, 8)
  "s_clamp\0" // IR(48764, 8)
  "u_clamp\0" // IR(48772, 8)
  "clz\0" // IR(48780, 4)
  "ctz\0" // IR(48784, 4)
  "s_mad_hi\0" // IR(48788, 9)
  "u_mad_sat\0" // IR(48797, 10)
  "s_mad_sat\0" // IR(48807, 10)
  "s_max\0" // IR(48817, 6)
  "u_max\0" // IR(48823, 6)
  "s_min\0" // IR(48829, 6)
  "u_min\0" // IR(48835, 6)
  "s_mul_hi\0" // IR(48841, 9)
  "rotate\0" // IR(48850, 7)
  "s_sub_sat\0" // IR(48857, 10)
  "u_sub_sat\0" // IR(48867, 10)
  "u_upsample\0" // IR(48877, 11)
  "s_upsample\0" // IR(48888, 11)
  "popcount\0" // IR(48899, 9)
  "s_mad24\0" // IR(48908, 8)
  "u_mad24\0" // IR(48916, 8)
  "s_mul24\0" // IR(48924, 8)
  "u_mul24\0" // IR(48932, 8)
  "vloadn\0" // IR(48940, 7)
  "vstoren\0" // IR(48947, 8)
  "vload_half\0" // IR(48955, 11)
  "vload_halfn\0" // IR(48966, 12)
  "vstore_half\0" // IR(48978, 12)
  "vstore_half_r\0" // IR(48990, 14)
  "vstore_halfn\0" // IR(49004, 13)
  "vstore_halfn_r\0" // IR(49017, 15)
  "vloada_halfn\0" // IR(49032, 13)
  "vstorea_halfn\0" // IR(49045, 14)
  "vstorea_halfn_r\0" // IR(49059, 16)
  "shuffle\0" // IR(49075, 8)
  "shuffle2\0" // IR(49083, 9)
  "printf\0" // IR(49092, 7)
  "prefetch\0" // IR(49099, 9)
  "bitselect\0" // IR(49108, 10)
  "select\0" // IR(49118, 7)
  "u_abs\0" // IR(49125, 6)
  "u_abs_diff\0" // IR(49131, 11)
  "u_mul_hi\0" // IR(49142, 9)
  "u_mad_hi\0" // IR(49151, 9)
  "CubeFaceIndexAMD\0" // IR(49160, 17)
  "CubeFaceCoordAMD\0" // IR(49177, 17)
  "TimeAMD\0" // IR(49194, 8)
  "SwizzleInvocationsAMD\0" // IR(49202, 22)
  "SwizzleInvocationsMaskedAMD\0" // IR(49224, 28)
  "WriteInvocationAMD\0" // IR(49252, 19)
  "MbcntAMD\0" // IR(49271, 9)
  "InterpolateAtVertexAMD\0" // IR(49280, 23)
  "FMin3AMD\0" // IR(49303, 9)
  "UMin3AMD\0" // IR(49312, 9)
  "SMin3AMD\0" // IR(49321, 9)
  "FMax3AMD\0" // IR(49330, 9)
  "UMax3AMD\0" // IR(49339, 9)
  "SMax3AMD\0" // IR(49348, 9)
  "FMid3AMD\0" // IR(49357, 9)
  "UMid3AMD\0" // IR(49366, 9)
  "SMid3AMD\0" // IR(49375, 9)
;

// Array of IndexRanges, where each represents a string by referencing
// the kStrings table.
// This array contains all sequences of alias strings used in the grammar.
// This table is referenced by an IndexRange elsewhere, i.e. by the 'aliases'
// field of an instruction or operand description.
static const IndexRange kAliasSpans[] = {
  IR(4599, 27), // 0 PhysicalStorageBuffer64EXT
  IR(5510, 18), // 1 SubgroupEqMaskKHR
  IR(5565, 18), // 2 SubgroupGeMaskKHR
  IR(5598, 18), // 3 SubgroupGtMaskKHR
  IR(5631, 18), // 4 SubgroupLeMaskKHR
  IR(5664, 18), // 5 SubgroupLtMaskKHR
  IR(6522, 12), // 6 BaryCoordNV
  IR(6577, 19), // 7 BaryCoordNoPerspNV
  IR(6608, 15), // 8 FragmentSizeNV
  IR(6665, 22), // 9 InvocationsPerPixelNV
  IR(6793, 11), // 10 LaunchIdNV
  IR(6818, 13), // 11 LaunchSizeNV
  IR(6849, 17), // 12 WorldRayOriginNV
  IR(6887, 20), // 13 WorldRayDirectionNV
  IR(6926, 18), // 14 ObjectRayOriginNV
  IR(6966, 21), // 15 ObjectRayDirectionNV
  IR(6998, 10), // 16 RayTminNV
  IR(7019, 10), // 17 RayTmaxNV
  IR(7052, 22), // 18 InstanceCustomIndexNV
  IR(7091, 16), // 19 ObjectToWorldNV
  IR(7124, 16), // 20 WorldToObjectNV
  IR(7158, 10), // 21 HitKindNV
  IR(7389, 19), // 22 IncomingRayFlagsNV
  IR(9098, 28), // 23 StorageUniformBufferBlock16
  IR(9161, 17), // 24 StorageUniform16
  IR(9965, 27), // 25 ShaderViewportIndexLayerNV
  IR(10009, 22), // 26 FragmentBarycentricNV
  IR(10062, 30), // 27 ComputeDerivativeGroupQuadsNV
  IR(10092, 14), // 28 ShadingRateNV
  IR(10152, 20), // 29 ShaderNonUniformEXT
  IR(10195, 26), // 30 RuntimeDescriptorArrayEXT
  IR(10257, 39), // 31 InputAttachmentArrayDynamicIndexingEXT
  IR(10335, 42), // 32 UniformTexelBufferArrayDynamicIndexingEXT
  IR(10416, 42), // 33 StorageTexelBufferArrayDynamicIndexingEXT
  IR(10495, 40), // 34 UniformBufferArrayNonUniformIndexingEXT
  IR(10571, 39), // 35 SampledImageArrayNonUniformIndexingEXT
  IR(10647, 40), // 36 StorageBufferArrayNonUniformIndexingEXT
  IR(10723, 39), // 37 StorageImageArrayNonUniformIndexingEXT
  IR(10801, 42), // 38 InputAttachmentArrayNonUniformIndexingEXT
  IR(10885, 45), // 39 UniformTexelBufferArrayNonUniformIndexingEXT
  IR(10972, 45), // 40 StorageTexelBufferArrayNonUniformIndexingEXT
  IR(11035, 21), // 41 VulkanMemoryModelKHR
  IR(11085, 32), // 42 VulkanMemoryModelDeviceScopeKHR
  IR(11117, 34), // 43 PhysicalStorageBufferAddressesEXT
  IR(11183, 31), // 44 ComputeDerivativeGroupLinearNV
  IR(11387, 28), // 45 DemoteToHelperInvocationEXT
  IR(12857, 22), // 46 DotProductInputAllKHR
  IR(12901, 25), // 47 DotProductInput4x8BitKHR
  IR(12954, 31), // 48 DotProductInput4x8BitPackedKHR
  IR(12996, 14), // 49 DotProductKHR
  IR(13161, 13), // 50 OptNoneINTEL
  IR(16093, 15), // 51 PerPrimitiveNV
  IR(16141, 12), // 52 PerVertexNV
  IR(16164, 14), // 53 NonUniformEXT
  IR(16194, 19), // 54 RestrictPointerEXT
  IR(16228, 18), // 55 AliasedPointerEXT
  IR(16538, 24), // 56 HlslCounterBufferGOOGLE
  IR(16575, 19), // 57 HlslSemanticGOOGLE
  IR(19249, 14), // 58 OutputLinesNV
  IR(19283, 19), // 59 OutputPrimitivesNV
  IR(19326, 23), // 60 DerivativeGroupQuadsNV
  IR(19374, 24), // 61 DerivativeGroupLinearNV
  IR(19417, 18), // 62 OutputTrianglesNV
  IR(20165, 16), // 63 RayGenerationNV
  IR(20197, 15), // 64 IntersectionNV
  IR(20222, 9), // 65 AnyHitNV
  IR(20245, 13), // 66 ClosestHitNV
  IR(20266, 7), // 67 MissNV
  IR(20285, 11), // 68 CallableNV
  IR(20402, 23), // 69 AllowContractFastINTEL
  IR(20438, 18), // 70 AllowReassocINTEL
  IR(20892, 22), // 71 MakeTexelAvailableKHR
  IR(20931, 20), // 72 MakeTexelVisibleKHR
  IR(20967, 19), // 73 NonPrivateTexelKHR
  IR(21000, 17), // 74 VolatileTexelKHR
  IR(22377, 24), // 75 MakePointerAvailableKHR
  IR(22420, 22), // 76 MakePointerVisibleKHR
  IR(22460, 21), // 77 NonPrivatePointerKHR
  IR(22547, 10), // 78 VulkanKHR
  IR(13909, 5), // 79 None
  IR(22730, 16), // 80 OutputMemoryKHR
  IR(22760, 17), // 81 MakeAvailableKHR
  IR(22789, 15), // 82 MakeVisibleKHR
  IR(22865, 28), // 83 PackedVectorFormat4x8BitKHR
  IR(23180, 24), // 84 SkipBuiltinPrimitivesNV
  IR(23920, 15), // 85 QueueFamilyKHR
  IR(24291, 15), // 86 CallableDataNV
  IR(24330, 23), // 87 IncomingCallableDataNV
  IR(24367, 13), // 88 RayPayloadNV
  IR(24396, 15), // 89 HitAttributeNV
  IR(24433, 21), // 90 IncomingRayPayloadNV
  IR(24476, 21), // 91 ShaderRecordBufferNV
  IR(24519, 25), // 92 PhysicalStorageBufferEXT
  IR(31735, 8), // 93 SDotKHR
  IR(31748, 8), // 94 UDotKHR
  IR(31762, 9), // 95 SUDotKHR
  IR(31782, 14), // 96 SDotAccSatKHR
  IR(31807, 14), // 97 UDotAccSatKHR
  IR(31833, 15), // 98 SUDotAccSatKHR
  IR(34318, 21), // 99 ReportIntersectionNV
  IR(34493, 28), // 100 TypeAccelerationStructureNV
  IR(36542, 21), // 101 DecorateStringGOOGLE
  IR(36584, 27), // 102 MemberDecorateStringGOOGLE
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
  spv::Capability::TensorsARM, // 197
  spv::Capability::Addresses, // 198
  spv::Capability::PhysicalStorageBufferAddresses, // 199
  spv::Capability::LiteralSampler, // 200
  spv::Capability::Addresses, // 201
  spv::Capability::UntypedPointersKHR, // 202
  spv::Capability::Addresses, // 203
  spv::Capability::VariablePointers, // 204
  spv::Capability::VariablePointersStorageBuffer, // 205
  spv::Capability::PhysicalStorageBufferAddresses, // 206
  spv::Capability::Kernel, // 207
  spv::Capability::ImageQuery, // 208
  spv::Capability::ImageQuery, // 209
  spv::Capability::Shader, // 210
  spv::Capability::BitInstructions, // 211
  spv::Capability::DerivativeControl, // 212
  spv::Capability::Groups, // 213
  spv::Capability::SparseResidency, // 214
  spv::Capability::PipeStorage, // 215
  spv::Capability::NamedBarrier, // 216
  spv::Capability::GroupNonUniformVote, // 217
  spv::Capability::GroupNonUniformBallot, // 218
  spv::Capability::GroupNonUniformShuffle, // 219
  spv::Capability::GroupNonUniformShuffleRelative, // 220
  spv::Capability::GroupNonUniformArithmetic, // 221
  spv::Capability::GroupNonUniformClustered, // 222
  spv::Capability::GroupNonUniformPartitionedNV, // 223
  spv::Capability::GroupNonUniformQuad, // 224
  spv::Capability::Addresses, // 225
  spv::Capability::VariablePointers, // 226
  spv::Capability::VariablePointersStorageBuffer, // 227
  spv::Capability::UntypedPointersKHR, // 228
  spv::Capability::SubgroupBallotKHR, // 229
  spv::Capability::SubgroupVoteKHR, // 230
  spv::Capability::GroupNonUniformRotateKHR, // 231
  spv::Capability::RayTracingKHR, // 232
  spv::Capability::RayQueryKHR, // 233
  spv::Capability::DotProduct, // 234
  spv::Capability::CooperativeMatrixKHR, // 235
  spv::Capability::ReplicatedCompositesEXT, // 236
  spv::Capability::TextureSampleWeightedQCOM, // 237
  spv::Capability::TextureBoxFilterQCOM, // 238
  spv::Capability::TextureBlockMatchQCOM, // 239
  spv::Capability::TextureBlockMatch2QCOM, // 240
  spv::Capability::FragmentMaskAMD, // 241
  spv::Capability::ShaderClockKHR, // 242
  spv::Capability::ShaderInvocationReorderNV, // 243
  spv::Capability::RayTracingMotionBlurNV, // 244
  spv::Capability::ImageFootprintNV, // 245
  spv::Capability::CooperativeVectorNV, // 246
  spv::Capability::CooperativeVectorTrainingNV, // 247
  spv::Capability::CooperativeMatrixConversionsNV, // 248
  spv::Capability::DisplacementMicromapNV, // 249
  spv::Capability::RayQueryPositionFetchKHR, // 250
  spv::Capability::RayTracingNV, // 251
  spv::Capability::RayTracingKHR, // 252
  spv::Capability::RayQueryKHR, // 253
  spv::Capability::DisplacementMicromapNV, // 254
  spv::Capability::CooperativeMatrixNV, // 255
  spv::Capability::FragmentShaderSampleInterlockEXT, // 256
  spv::Capability::FragmentShaderPixelInterlockEXT, // 257
  spv::Capability::FragmentShaderShadingRateInterlockEXT, // 258
  spv::Capability::CooperativeMatrixReductionsNV, // 259
  spv::Capability::CooperativeMatrixPerElementOperationsNV, // 260
  spv::Capability::TensorAddressingNV, // 261
  spv::Capability::DemoteToHelperInvocation, // 262
  spv::Capability::SubgroupShuffleINTEL, // 263
  spv::Capability::SubgroupBufferBlockIOINTEL, // 264
  spv::Capability::SubgroupImageBlockIOINTEL, // 265
  spv::Capability::SubgroupImageMediaBlockIOINTEL, // 266
  spv::Capability::IntegerFunctions2INTEL, // 267
  spv::Capability::AtomicFloat16MinMaxEXT, // 268
  spv::Capability::AtomicFloat32MinMaxEXT, // 269
  spv::Capability::AtomicFloat64MinMaxEXT, // 270
  spv::Capability::AtomicFloat16VectorNV, // 271
  spv::Capability::ExpectAssumeKHR, // 272
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 273
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 274
  spv::Capability::SubgroupAvcMotionEstimationIntraINTEL, // 275
  spv::Capability::SubgroupAvcMotionEstimationINTEL, // 276
  spv::Capability::SubgroupAvcMotionEstimationChromaINTEL, // 277
  spv::Capability::VariableLengthArrayINTEL, // 278
  spv::Capability::ArbitraryPrecisionFloatingPointINTEL, // 279
  spv::Capability::UnstructuredLoopControlsINTEL, // 280
  spv::Capability::BlockingPipesINTEL, // 281
  spv::Capability::FPGARegINTEL, // 282
  spv::Capability::AtomicFloat16AddEXT, // 283
  spv::Capability::AtomicFloat32AddEXT, // 284
  spv::Capability::AtomicFloat64AddEXT, // 285
  spv::Capability::AtomicFloat16VectorNV, // 286
  spv::Capability::LongCompositesINTEL, // 287
  spv::Capability::BFloat16ConversionINTEL, // 288
  spv::Capability::SplitBarrierINTEL, // 289
  spv::Capability::ArithmeticFenceEXT, // 290
  spv::Capability::TaskSequenceINTEL, // 291
  spv::Capability::SubgroupBufferPrefetchINTEL, // 292
  spv::Capability::Subgroup2DBlockTransformINTEL, // 293
  spv::Capability::Subgroup2DBlockTransposeINTEL, // 294
  spv::Capability::SubgroupMatrixMultiplyAccumulateINTEL, // 295
  spv::Capability::TernaryBitwiseFunctionINTEL, // 296
  spv::Capability::GroupUniformArithmeticKHR, // 297
  spv::Capability::TensorFloat32RoundingINTEL, // 298
  spv::Capability::MaskedGatherScatterINTEL, // 299
  spv::Capability::Float64, // 300
  spv::Capability::InterpolationFunction, // 301
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
  spvtools::Extension::kSPV_KHR_workgroup_memory_explicit_layout, // 38
  spvtools::Extension::kSPV_KHR_subgroup_vote, // 39
  spvtools::Extension::kSPV_KHR_16bit_storage, // 40
  spvtools::Extension::kSPV_KHR_variable_pointers, // 41
  spvtools::Extension::kSPV_KHR_shader_atomic_counter_ops, // 42
  spvtools::Extension::kSPV_KHR_post_depth_coverage, // 43
  spvtools::Extension::kSPV_KHR_8bit_storage, // 44
  spvtools::Extension::kSPV_KHR_float_controls, // 45
  spvtools::Extension::kSPV_KHR_ray_query, // 46
  spvtools::Extension::kSPV_KHR_untyped_pointers, // 47
  spvtools::Extension::kSPV_KHR_ray_query, // 48
  spvtools::Extension::kSPV_KHR_ray_tracing, // 49
  spvtools::Extension::kSPV_QCOM_image_processing, // 50
  spvtools::Extension::kSPV_QCOM_tile_shading, // 51
  spvtools::Extension::kSPV_QCOM_image_processing2, // 52
  spvtools::Extension::kSPV_AMD_gpu_shader_half_float_fetch, // 53
  spvtools::Extension::kSPV_AMD_texture_gather_bias_lod, // 54
  spvtools::Extension::kSPV_AMD_shader_fragment_mask, // 55
  spvtools::Extension::kSPV_AMD_shader_image_load_store_lod, // 56
  spvtools::Extension::kSPV_EXT_shader_image_int64, // 57
  spvtools::Extension::kSPV_KHR_shader_clock, // 58
  spvtools::Extension::kSPV_AMDX_shader_enqueue, // 59
  spvtools::Extension::kSPV_KHR_quad_control, // 60
  spvtools::Extension::kSPV_INTEL_int4, // 61
  spvtools::Extension::kSPV_KHR_bfloat16, // 62
  spvtools::Extension::kSPV_NV_sample_mask_override_coverage, // 63
  spvtools::Extension::kSPV_NV_geometry_shader_passthrough, // 64
  spvtools::Extension::kSPV_EXT_shader_viewport_index_layer, // 65
  spvtools::Extension::kSPV_NV_viewport_array2, // 66
  spvtools::Extension::kSPV_NV_viewport_array2, // 67
  spvtools::Extension::kSPV_NVX_multiview_per_view_attributes, // 68
  spvtools::Extension::kSPV_NV_shader_image_footprint, // 69
  spvtools::Extension::kSPV_NV_compute_shader_derivatives, // 70
  spvtools::Extension::kSPV_KHR_compute_shader_derivatives, // 71
  spvtools::Extension::kSPV_NV_shader_subgroup_partitioned, // 72
  spvtools::Extension::kSPV_EXT_descriptor_indexing, // 73
  spvtools::Extension::kSPV_KHR_ray_tracing_position_fetch, // 74
  spvtools::Extension::kSPV_KHR_vulkan_memory_model, // 75
  spvtools::Extension::kSPV_NV_cooperative_matrix, // 76
  spvtools::Extension::kSPV_EXT_fragment_shader_interlock, // 77
  spvtools::Extension::kSPV_EXT_demote_to_helper_invocation, // 78
  spvtools::Extension::kSPV_NV_displacement_micromap, // 79
  spvtools::Extension::kSPV_EXT_opacity_micromap, // 80
  spvtools::Extension::kSPV_NV_shader_invocation_reorder, // 81
  spvtools::Extension::kSPV_NV_bindless_texture, // 82
  spvtools::Extension::kSPV_NV_cooperative_vector, // 83
  spvtools::Extension::kSPV_NV_shader_atomic_fp16_vector, // 84
  spvtools::Extension::kSPV_NV_raw_access_chains, // 85
  spvtools::Extension::kSPV_NV_cooperative_matrix2, // 86
  spvtools::Extension::kSPV_NV_tensor_addressing, // 87
  spvtools::Extension::kSPV_INTEL_subgroups, // 88
  spvtools::Extension::kSPV_INTEL_media_block_io, // 89
  spvtools::Extension::kSPV_INTEL_float_controls2, // 90
  spvtools::Extension::kSPV_INTEL_shader_integer_functions2, // 91
  spvtools::Extension::kSPV_INTEL_function_pointers, // 92
  spvtools::Extension::kSPV_INTEL_inline_assembly, // 93
  spvtools::Extension::kSPV_EXT_shader_atomic_float_min_max, // 94
  spvtools::Extension::kSPV_INTEL_vector_compute, // 95
  spvtools::Extension::kSPV_KHR_expect_assume, // 96
  spvtools::Extension::kSPV_INTEL_device_side_avc_motion_estimation, // 97
  spvtools::Extension::kSPV_INTEL_variable_length_array, // 98
  spvtools::Extension::kSPV_INTEL_fpga_memory_attributes, // 99
  spvtools::Extension::kSPV_INTEL_fp_fast_math_mode, // 100
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_integers, // 101
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_floating_point, // 102
  spvtools::Extension::kSPV_INTEL_unstructured_loop_controls, // 103
  spvtools::Extension::kSPV_INTEL_fpga_loop_controls, // 104
  spvtools::Extension::kSPV_INTEL_kernel_attributes, // 105
  spvtools::Extension::kSPV_INTEL_fpga_memory_accesses, // 106
  spvtools::Extension::kSPV_INTEL_fpga_cluster_attributes, // 107
  spvtools::Extension::kSPV_INTEL_loop_fuse, // 108
  spvtools::Extension::kSPV_INTEL_fpga_dsp_control, // 109
  spvtools::Extension::kSPV_INTEL_memory_access_aliasing, // 110
  spvtools::Extension::kSPV_INTEL_fpga_invocation_pipelining_attributes, // 111
  spvtools::Extension::kSPV_INTEL_fpga_buffer_location, // 112
  spvtools::Extension::kSPV_INTEL_arbitrary_precision_fixed_point, // 113
  spvtools::Extension::kSPV_INTEL_usm_storage_classes, // 114
  spvtools::Extension::kSPV_INTEL_runtime_aligned, // 115
  spvtools::Extension::kSPV_INTEL_io_pipes, // 116
  spvtools::Extension::kSPV_INTEL_blocking_pipes, // 117
  spvtools::Extension::kSPV_INTEL_fpga_reg, // 118
  spvtools::Extension::kSPV_KHR_integer_dot_product, // 119
  spvtools::Extension::kSPV_KHR_cooperative_matrix, // 120
  spvtools::Extension::kSPV_EXT_replicated_composites, // 121
  spvtools::Extension::kSPV_KHR_bit_instructions, // 122
  spvtools::Extension::kSPV_KHR_subgroup_rotate, // 123
  spvtools::Extension::kSPV_KHR_float_controls2, // 124
  spvtools::Extension::kSPV_EXT_shader_atomic_float_add, // 125
  spvtools::Extension::kSPV_INTEL_long_composites, // 126
  spvtools::Extension::kSPV_EXT_optnone, // 127
  spvtools::Extension::kSPV_INTEL_optnone, // 128
  spvtools::Extension::kSPV_EXT_shader_atomic_float16_add, // 129
  spvtools::Extension::kSPV_INTEL_debug_module, // 130
  spvtools::Extension::kSPV_INTEL_bfloat16_conversion, // 131
  spvtools::Extension::kSPV_INTEL_split_barrier, // 132
  spvtools::Extension::kSPV_EXT_arithmetic_fence, // 133
  spvtools::Extension::kSPV_INTEL_task_sequence, // 134
  spvtools::Extension::kSPV_INTEL_fp_max_error, // 135
  spvtools::Extension::kSPV_INTEL_fpga_latency_control, // 136
  spvtools::Extension::kSPV_INTEL_fpga_argument_interfaces, // 137
  spvtools::Extension::kSPV_INTEL_global_variable_host_access, // 138
  spvtools::Extension::kSPV_INTEL_global_variable_fpga_decorations, // 139
  spvtools::Extension::kSPV_INTEL_subgroup_buffer_prefetch, // 140
  spvtools::Extension::kSPV_INTEL_2d_block_io, // 141
  spvtools::Extension::kSPV_INTEL_subgroup_matrix_multiply_accumulate, // 142
  spvtools::Extension::kSPV_INTEL_ternary_bitwise_function, // 143
  spvtools::Extension::kSPV_KHR_uniform_group_instructions, // 144
  spvtools::Extension::kSPV_INTEL_tensor_float32_conversion, // 145
  spvtools::Extension::kSPV_INTEL_masked_gather_scatter, // 146
  spvtools::Extension::kSPV_INTEL_cache_controls, // 147
  spvtools::Extension::kSPV_INTEL_maximum_registers, // 148
  spvtools::Extension::kSPV_KHR_no_integer_wrap_decoration, // 149
  spvtools::Extension::kSPV_NV_mesh_shader, // 150
  spvtools::Extension::kSPV_EXT_mesh_shader, // 151
  spvtools::Extension::kSPV_GOOGLE_hlsl_functionality1, // 152
  spvtools::Extension::kSPV_GOOGLE_user_type, // 153
  spvtools::Extension::kSPV_KHR_subgroup_uniform_control_flow, // 154
  spvtools::Extension::kSPV_AMD_shader_early_and_late_fragment_tests, // 155
  spvtools::Extension::kSPV_AMD_shader_early_and_late_fragment_tests, // 156
  spvtools::Extension::kSPV_EXT_shader_stencil_export, // 157
  spvtools::Extension::kSPV_KHR_maximal_reconvergence, // 158
  spvtools::Extension::kSPV_KHR_linkonce_odr, // 159
  spvtools::Extension::kSPV_KHR_storage_buffer_storage_class, // 160
  spvtools::Extension::kSPV_KHR_variable_pointers, // 161
  spvtools::Extension::kSPV_KHR_terminate_invocation, // 162
  spvtools::Extension::kSPV_KHR_relaxed_extended_instruction, // 163
  spvtools::Extension::kSPV_KHR_ray_tracing, // 164
  spvtools::Extension::kSPV_KHR_ray_query, // 165
  spvtools::Extension::kSPV_NV_ray_tracing, // 166
  spvtools::Extension::kSPV_KHR_ray_tracing, // 167
  spvtools::Extension::kSPV_KHR_ray_query, // 168
  spvtools::Extension::kSPV_NV_displacement_micromap, // 169
  spvtools::Extension::kSPV_GOOGLE_decorate_string, // 170
  spvtools::Extension::kSPV_GOOGLE_hlsl_functionality1, // 171
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
