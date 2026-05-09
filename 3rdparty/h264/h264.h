// Minimal cross-platform H264 video parser utility created by Turánszki János for Wicked Engine: https://github.com/turanszkij/WickedEngine
//	This is not using any includes or memory allocations
//	Based on the H264 specification: Rec. ITU-T H.264 (08/2021)
//	The following library was also used as reference: https://github.com/aizvorski/h264bitstream/
//
// What this library does:
//	- extract descriptor structures from a H264 bitstream
//		- NAL headers
//		- Sequence Parameter Set (SPS)
//		- Picture Parameter Set (PPS)
//		- Slices (SliceHeader)
//
// What this library doesn't do:
//	- read from MP4 file
//	- decode video
//	- encode video
//	- display video
//
// How to use:
// 1) Create a bitstream to consume binary data, the data pointer must point to data that contains raw H264 data:
//	Bitstream bs;
//	bs.init(data, size);
//
// 2) Find a NAL header in the bitstream:
//	find_next_nal(&bs);
//
// 2) Read the NAL header from the bitstream:
//	NALHeader nal;
//	read_nal_header(&nal, &bs);
//
// 3) Depending on nal.type, you can extract the important structures from the bitstream:
//	if (nal.type == NAL_UNIT_TYPE_SPS)
//	{
//		PPS pps = {};
//		read_pps(&pps, &bs);
//	}
//	else if (nal.type == NAL_UNIT_TYPE_SPS)
//	{
//		SPS sps = {};
//		read_sps(&sps, &bs);
//	}
//	else if (nal.type == NAL_UNIT_TYPE_CODED_SLICE_IDR || nal.type == NAL_UNIT_TYPE_CODED_SLICE_NON_IDR)
//	{
//		SliceHeader slice_header = {};
//		read_slice_header(&slice_header, &nal, &pps, &sps, &bs);
//	}
//
// 4) repeat until you have extracted all that you require or the data ends
//
// 
//	MIT License (see the end of this file)

#ifndef H264_H
#define H264_H

namespace h264 {

	static constexpr unsigned char nal_start_code[] = { 0,0,1 };

	struct SPS
	{
		int profile_idc;
		int constraint_set0_flag;
		int constraint_set1_flag;
		int constraint_set2_flag;
		int constraint_set3_flag;
		int constraint_set4_flag;
		int constraint_set5_flag;
		int reserved_zero_2bits;
		int level_idc;
		int seq_parameter_set_id;
		int chroma_format_idc;
		int separate_colour_plane_flag;
		int bit_depth_luma_minus8;
		int bit_depth_chroma_minus8;
		int qpprime_y_zero_transform_bypass_flag;
		int seq_scaling_matrix_present_flag;
		int seq_scaling_list_present_flag[8];
		int ScalingList4x4[6][16];
		int UseDefaultScalingMatrix4x4Flag[6];
		int ScalingList8x8[2][64];
		int UseDefaultScalingMatrix8x8Flag[2];
		int log2_max_frame_num_minus4;
		int pic_order_cnt_type;
		int log2_max_pic_order_cnt_lsb_minus4;
		int delta_pic_order_always_zero_flag;
		int offset_for_non_ref_pic;
		int offset_for_top_to_bottom_field;
		int num_ref_frames_in_pic_order_cnt_cycle;
		int offset_for_ref_frame[256];
		int num_ref_frames;
		int gaps_in_frame_num_value_allowed_flag;
		int pic_width_in_mbs_minus1;
		int pic_height_in_map_units_minus1;
		int frame_mbs_only_flag;
		int mb_adaptive_frame_field_flag;
		int direct_8x8_inference_flag;
		int frame_cropping_flag;
		int frame_crop_left_offset;
		int frame_crop_right_offset;
		int frame_crop_top_offset;
		int frame_crop_bottom_offset;
		int vui_parameters_present_flag;

		struct
		{
			int aspect_ratio_info_present_flag;
			int aspect_ratio_idc;
			int sar_width;
			int sar_height;
			int overscan_info_present_flag;
			int overscan_appropriate_flag;
			int video_signal_type_present_flag;
			int video_format;
			int video_full_range_flag;
			int colour_description_present_flag;
			int colour_primaries;
			int transfer_characteristics;
			int matrix_coefficients;
			int chroma_loc_info_present_flag;
			int chroma_sample_loc_type_top_field;
			int chroma_sample_loc_type_bottom_field;
			int timing_info_present_flag;
			int num_units_in_tick;
			int time_scale;
			int fixed_frame_rate_flag;
			int nal_hrd_parameters_present_flag;
			int vcl_hrd_parameters_present_flag;
			int low_delay_hrd_flag;
			int pic_struct_present_flag;
			int bitstream_restriction_flag;
			int motion_vectors_over_pic_boundaries_flag;
			int max_bytes_per_pic_denom;
			int max_bits_per_mb_denom;
			int log2_max_mv_length_horizontal;
			int log2_max_mv_length_vertical;
			int num_reorder_frames;
			int max_dec_frame_buffering;
		} vui;

		struct
		{
			int cpb_cnt_minus1;
			int bit_rate_scale;
			int cpb_size_scale;
			int bit_rate_value_minus1[32];
			int cpb_size_value_minus1[32];
			int cbr_flag[32];
			int initial_cpb_removal_delay_length_minus1;
			int cpb_removal_delay_length_minus1;
			int dpb_output_delay_length_minus1;
			int time_offset_length;
		} hrd;
	};

	struct PPS
	{
		int pic_parameter_set_id;
		int seq_parameter_set_id;
		int entropy_coding_mode_flag;
		int pic_order_present_flag;
		int num_slice_groups_minus1;
		int slice_group_map_type;
		int run_length_minus1[8];
		int top_left[8];
		int bottom_right[8];
		int slice_group_change_direction_flag;
		int slice_group_change_rate_minus1;
		int pic_size_in_map_units_minus1;
		int slice_group_id[256];
		int num_ref_idx_l0_active_minus1;
		int num_ref_idx_l1_active_minus1;
		int weighted_pred_flag;
		int weighted_bipred_idc;
		int pic_init_qp_minus26;
		int pic_init_qs_minus26;
		int chroma_qp_index_offset;
		int deblocking_filter_control_present_flag;
		int constrained_intra_pred_flag;
		int redundant_pic_cnt_present_flag;

		int _more_rbsp_data_present;

		int transform_8x8_mode_flag;
		int pic_scaling_matrix_present_flag;
		int pic_scaling_list_present_flag[8];
		int ScalingList4x4[6][16];
		int UseDefaultScalingMatrix4x4Flag[6];
		int ScalingList8x8[2][64];
		int UseDefaultScalingMatrix8x8Flag[2];
		int second_chroma_qp_index_offset;
	};

	enum SH_SLICE_TYPE
	{
		SH_SLICE_TYPE_P = 0,
		SH_SLICE_TYPE_B = 1,
		SH_SLICE_TYPE_I = 2,
		SH_SLICE_TYPE_SP = 3,
		SH_SLICE_TYPE_SI = 4,

		// The *_ONLY slice types indicate that all other slices in that picture are of the same type
		SH_SLICE_TYPE_P_ONLY = 5,
		SH_SLICE_TYPE_B_ONLY = 6,
		SH_SLICE_TYPE_I_ONLY = 7,
		SH_SLICE_TYPE_SP_ONLY = 8,
		SH_SLICE_TYPE_SI_ONLY = 9,
	};
	struct SliceHeader
	{
		int first_mb_in_slice;
		int slice_type;
		int pic_parameter_set_id;
		int frame_num;
		int field_pic_flag;
		int bottom_field_flag;
		int idr_pic_id;
		int pic_order_cnt_lsb;
		int delta_pic_order_cnt_bottom;
		int delta_pic_order_cnt[2];
		int redundant_pic_cnt;
		int direct_spatial_mv_pred_flag;
		int num_ref_idx_active_override_flag;
		int num_ref_idx_l0_active_minus1;
		int num_ref_idx_l1_active_minus1;
		int cabac_init_idc;
		int slice_qp_delta;
		int sp_for_switch_flag;
		int slice_qs_delta;
		int disable_deblocking_filter_idc;
		int slice_alpha_c0_offset_div2;
		int slice_beta_offset_div2;
		int slice_group_change_cycle;

		struct
		{
			int luma_log2_weight_denom;
			int chroma_log2_weight_denom;
			int luma_weight_l0_flag[64];
			int luma_weight_l0[64];
			int luma_offset_l0[64];
			int chroma_weight_l0_flag[64];
			int chroma_weight_l0[64][2];
			int chroma_offset_l0[64][2];
			int luma_weight_l1_flag[64];
			int luma_weight_l1[64];
			int luma_offset_l1[64];
			int chroma_weight_l1_flag[64];
			int chroma_weight_l1[64][2];
			int chroma_offset_l1[64][2];
		} pwt; // predictive weight table

		struct
		{
			int ref_pic_list_reordering_flag_l0;
			struct
			{
				int reordering_of_pic_nums_idc[64];
				int abs_diff_pic_num_minus1[64];
				int long_term_pic_num[64];
			} reorder_l0;
			int ref_pic_list_reordering_flag_l1;
			struct
			{
				int reordering_of_pic_nums_idc[64];
				int abs_diff_pic_num_minus1[64];
				int long_term_pic_num[64];
			} reorder_l1;
		} rplr; // ref pic list reorder

		struct
		{
			int no_output_of_prior_pics_flag;
			int long_term_reference_flag;
			int adaptive_ref_pic_marking_mode_flag;
			int memory_management_control_operation[64];
			int difference_of_pic_nums_minus1[64];
			int long_term_pic_num[64];
			int long_term_frame_idx[64];
			int max_long_term_frame_idx_plus1[64];
		} drpm; // decoded ref pic marking

	};

	enum NAL_REF_IDC
	{
		NAL_REF_IDC_PRIORITY_HIGHEST = 3,
		NAL_REF_IDC_PRIORITY_HIGH = 2,
		NAL_REF_IDC_PRIORITY_LOW = 1,
		NAL_REF_IDC_PRIORITY_DISPOSABLE = 0,
	};
	enum NAL_UNIT_TYPE
	{
		NAL_UNIT_TYPE_UNSPECIFIED = 0,	// Unspecified
		NAL_UNIT_TYPE_CODED_SLICE_NON_IDR = 1,	// Coded slice of a non-IDR picture
		NAL_UNIT_TYPE_CODED_SLICE_DATA_PARTITION_A = 2,	// Coded slice data partition A
		NAL_UNIT_TYPE_CODED_SLICE_DATA_PARTITION_B = 3,	// Coded slice data partition B
		NAL_UNIT_TYPE_CODED_SLICE_DATA_PARTITION_C = 4,	// Coded slice data partition C
		NAL_UNIT_TYPE_CODED_SLICE_IDR = 5,	// Coded slice of an IDR picture
		NAL_UNIT_TYPE_SEI = 6,	// Supplemental enhancement information (SEI)
		NAL_UNIT_TYPE_SPS = 7,	// Sequence parameter set
		NAL_UNIT_TYPE_PPS = 8,	// Picture parameter set
		NAL_UNIT_TYPE_AUD = 9,	// Access unit delimiter
		NAL_UNIT_TYPE_END_OF_SEQUENCE = 10,	// End of sequence
		NAL_UNIT_TYPE_END_OF_STREAM = 11,	// End of stream
		NAL_UNIT_TYPE_FILLER = 12,	// Filler data
		NAL_UNIT_TYPE_SPS_EXT = 13,	// Sequence parameter set extension
		NAL_UNIT_TYPE_CODED_SLICE_AUX = 19,	// Coded slice of an auxiliary coded picture without partitioning
	};
	struct NALHeader
	{
		NAL_REF_IDC idc;
		NAL_UNIT_TYPE type;
	};

	struct Bitstream
	{
		const unsigned char* start;
		const unsigned char* p;
		const unsigned char* end;
		int bits_left;

		constexpr void init(const unsigned char* buf, unsigned long long size)
		{
			start = buf;
			p = buf;
			end = buf + size;
			bits_left = 8;
		}
		constexpr unsigned long long byte_offset() { return (unsigned long long)(p - start); }
		constexpr bool byte_aligned() { return bits_left == 8; }
		constexpr bool eof() { if (p >= end) { return true; } else { return false; } }
		constexpr void back_1byte()
		{
			bits_left = 8;
			p--;
		}
		constexpr unsigned u1()
		{
			unsigned r = 0;
			bits_left--;
			if (!eof())
			{
				r = ((*(p)) >> bits_left) & 0x01;
			}
			if (bits_left == 0)
			{
				p++;
				bits_left = 8;
			}
			return r;
		}
		constexpr unsigned u(int n)
		{
			unsigned r = 0;
			for (int i = 0; i < n; i++)
			{
				r |= (u1() << (n - i - 1));
			}
			return r;
		}
		constexpr unsigned ue()
		{
			int r = 0;
			int i = 0;

			while ((u1() == 0) && (i < 32) && (!eof()))
			{
				i++;
			}
			r = u(i);
			r += (1 << i) - 1;
			return r;
		}
		constexpr int se()
		{
			int r = ue();
			if (r & 0x01)
			{
				r = (r + 1) / 2;
			}
			else
			{
				r = -(r / 2);
			}
			return r;
		}
	};

	// returns true if a nal header is found, false otherwise
	constexpr bool find_next_nal(Bitstream* b)
	{
		while (!b->eof())
		{
			// Read in 3 byte increments because the nal header is 3 bytes normally:
			const unsigned int b0 = b->u(8);
			const unsigned int b1 = b->u(8);
			const unsigned int b2 = b->u(8);
			if (b0 == 0 && b1 == 0 && b2 == 1)
				return true;
			// step back 2 bytes, so the next iteration has a chance to succeed if extended NAL start code is being used which is 4 bytes:
			b->back_1byte();
			b->back_1byte();
		}
		return false;
	}
	// returns true if a valid nal header was read, false otherwise
	constexpr bool read_nal_header(NALHeader* nal, Bitstream* b)
	{
		unsigned forbidden_zero_bit = b->u(1);
		if (forbidden_zero_bit != 0)
			return false;
		nal->idc = (h264::NAL_REF_IDC)b->u(2);
		nal->type = (h264::NAL_UNIT_TYPE)b->u(5);
		return true;
	}
	constexpr void read_scaling_list(Bitstream* b, int* scalingList, int sizeOfScalingList, int* useDefaultScalingMatrixFlag)
	{
		int lastScale = 8;
		int nextScale = 8;
		int delta_scale = 0;
		for (int j = 0; j < sizeOfScalingList; j++)
		{
			if (nextScale != 0)
			{
				if (0)
				{
					nextScale = scalingList[j];
					if (*useDefaultScalingMatrixFlag) { nextScale = 0; }
					delta_scale = (nextScale - lastScale) % 256;
				}

				delta_scale = b->se();

				if (1)
				{
					nextScale = (lastScale + delta_scale + 256) % 256;
					*useDefaultScalingMatrixFlag = (j == 0 && nextScale == 0);
				}
			}
			if (1)
			{
				scalingList[j] = (nextScale == 0) ? lastScale : nextScale;
			}
			lastScale = scalingList[j];
		}
	}
	constexpr void read_hrd_parameters(SPS* sps, Bitstream* b)
	{
		sps->hrd.cpb_cnt_minus1 = b->ue();
		sps->hrd.bit_rate_scale = b->u(4);
		sps->hrd.cpb_size_scale = b->u(4);
		for (int SchedSelIdx = 0; SchedSelIdx <= sps->hrd.cpb_cnt_minus1; SchedSelIdx++)
		{
			sps->hrd.bit_rate_value_minus1[SchedSelIdx] = b->ue();
			sps->hrd.cpb_size_value_minus1[SchedSelIdx] = b->ue();
			sps->hrd.cbr_flag[SchedSelIdx] = b->u1();
		}
		sps->hrd.initial_cpb_removal_delay_length_minus1 = b->u(5);
		sps->hrd.cpb_removal_delay_length_minus1 = b->u(5);
		sps->hrd.dpb_output_delay_length_minus1 = b->u(5);
		sps->hrd.time_offset_length = b->u(5);
	}
	constexpr void read_rbsp_trailing_bits(Bitstream* b)
	{
		/* rbsp_stop_one_bit */ b->u(1);

		while (!b->byte_aligned())
		{
			/* rbsp_alignment_zero_bit */ b->u(1);
		}
	}
	constexpr void read_vui_parameters(SPS* sps, Bitstream* b)
	{
		sps->vui.aspect_ratio_info_present_flag = b->u1();
		if (sps->vui.aspect_ratio_info_present_flag)
		{
			sps->vui.aspect_ratio_idc = b->u(8);
			if (sps->vui.aspect_ratio_idc == 255) // Extended_SAR
			{
				sps->vui.sar_width = b->u(16);
				sps->vui.sar_height = b->u(16);
			}
		}
		sps->vui.overscan_info_present_flag = b->u1();
		if (sps->vui.overscan_info_present_flag)
		{
			sps->vui.overscan_appropriate_flag = b->u1();
		}
		sps->vui.video_signal_type_present_flag = b->u1();
		if (sps->vui.video_signal_type_present_flag)
		{
			sps->vui.video_format = b->u(3);
			sps->vui.video_full_range_flag = b->u1();
			sps->vui.colour_description_present_flag = b->u1();
			if (sps->vui.colour_description_present_flag)
			{
				sps->vui.colour_primaries = b->u(8);
				sps->vui.transfer_characteristics = b->u(8);
				sps->vui.matrix_coefficients = b->u(8);
			}
		}
		sps->vui.chroma_loc_info_present_flag = b->u1();
		if (sps->vui.chroma_loc_info_present_flag)
		{
			sps->vui.chroma_sample_loc_type_top_field = b->ue();
			sps->vui.chroma_sample_loc_type_bottom_field = b->ue();
		}
		sps->vui.timing_info_present_flag = b->u1();
		if (sps->vui.timing_info_present_flag)
		{
			sps->vui.num_units_in_tick = b->u(32);
			sps->vui.time_scale = b->u(32);
			sps->vui.fixed_frame_rate_flag = b->u1();
		}
		sps->vui.nal_hrd_parameters_present_flag = b->u1();
		if (sps->vui.nal_hrd_parameters_present_flag)
		{
			read_hrd_parameters(sps, b);
		}
		sps->vui.vcl_hrd_parameters_present_flag = b->u1();
		if (sps->vui.vcl_hrd_parameters_present_flag)
		{
			read_hrd_parameters(sps, b);
		}
		if (sps->vui.nal_hrd_parameters_present_flag || sps->vui.vcl_hrd_parameters_present_flag)
		{
			sps->vui.low_delay_hrd_flag = b->u1();
		}
		sps->vui.pic_struct_present_flag = b->u1();
		sps->vui.bitstream_restriction_flag = b->u1();
		if (sps->vui.bitstream_restriction_flag)
		{
			sps->vui.motion_vectors_over_pic_boundaries_flag = b->u1();
			sps->vui.max_bytes_per_pic_denom = b->ue();
			sps->vui.max_bits_per_mb_denom = b->ue();
			sps->vui.log2_max_mv_length_horizontal = b->ue();
			sps->vui.log2_max_mv_length_vertical = b->ue();
			sps->vui.num_reorder_frames = b->ue();
			sps->vui.max_dec_frame_buffering = b->ue();
		}
	}
	constexpr int intlog2(int x)
	{
		int log = 0;
		if (x < 0) { x = 0; }
		while ((x >> log) > 0)
		{
			log++;
		}
		if (log > 0 && x == 1 << (log - 1)) { log--; }
		return log;
	}
	constexpr int more_rbsp_data(Bitstream* b)
	{
		// no more data
		if (b->eof()) { return 0; }

		Bitstream bs_tmp = *b; // make copy

		// no rbsp_stop_bit yet
		if (bs_tmp.u1() == 0) { return 1; }

		while (!bs_tmp.eof())
		{
			// A later bit was 1, it wasn't the rsbp_stop_bit
			if (bs_tmp.u1() == 1) { return 1; }
		}

		// All following bits were 0, it was the rsbp_stop_bit
		return 0;
	}
	constexpr void read_sps(SPS* sps, Bitstream* b)
	{
		sps->profile_idc = b->u(8);
		sps->constraint_set0_flag = b->u1();
		sps->constraint_set1_flag = b->u1();
		sps->constraint_set2_flag = b->u1();
		sps->constraint_set3_flag = b->u1();
		sps->constraint_set4_flag = b->u1();
		sps->constraint_set5_flag = b->u1();
		/* reserved_zero_2bits */ b->u(2);
		sps->level_idc = b->u(8);
		sps->seq_parameter_set_id = b->ue();

		if (sps->profile_idc == 100 || sps->profile_idc == 110 ||
			sps->profile_idc == 122 || sps->profile_idc == 144)
		{
			sps->chroma_format_idc = b->ue();
			if (sps->chroma_format_idc == 3)
			{
				sps->separate_colour_plane_flag = b->u1();
			}
			sps->bit_depth_luma_minus8 = b->ue();
			sps->bit_depth_chroma_minus8 = b->ue();
			sps->qpprime_y_zero_transform_bypass_flag = b->u1();
			sps->seq_scaling_matrix_present_flag = b->u1();
			if (sps->seq_scaling_matrix_present_flag)
			{
				for (int i = 0; i < 8; i++)
				{
					sps->seq_scaling_list_present_flag[i] = b->u1();
					if (sps->seq_scaling_list_present_flag[i])
					{
						if (i < 6)
						{
							read_scaling_list(b, sps->ScalingList4x4[i], 16,
								&(sps->UseDefaultScalingMatrix4x4Flag[i]));
						}
						else
						{
							read_scaling_list(b, sps->ScalingList8x8[i - 6], 64,
								&(sps->UseDefaultScalingMatrix8x8Flag[i - 6]));
						}
					}
				}
			}
		}
		else
		{
			// H.264 spec 7.4.2.1.1: when chroma_format_idc is not present
			// (i.e. Baseline/Main/Extended profile) it shall be inferred
			// to be equal to 1 (4:2:0 chroma format).
			sps->chroma_format_idc = 1;
		}
		sps->log2_max_frame_num_minus4 = b->ue();
		sps->pic_order_cnt_type = b->ue();
		if (sps->pic_order_cnt_type == 0)
		{
			sps->log2_max_pic_order_cnt_lsb_minus4 = b->ue();
		}
		else if (sps->pic_order_cnt_type == 1)
		{
			sps->delta_pic_order_always_zero_flag = b->u1();
			sps->offset_for_non_ref_pic = b->se();
			sps->offset_for_top_to_bottom_field = b->se();
			sps->num_ref_frames_in_pic_order_cnt_cycle = b->ue();
			for (int i = 0; i < sps->num_ref_frames_in_pic_order_cnt_cycle; i++)
			{
				sps->offset_for_ref_frame[i] = b->se();
			}
		}
		sps->num_ref_frames = b->ue();
		sps->gaps_in_frame_num_value_allowed_flag = b->u1();
		sps->pic_width_in_mbs_minus1 = b->ue();
		sps->pic_height_in_map_units_minus1 = b->ue();
		sps->frame_mbs_only_flag = b->u1();
		if (!sps->frame_mbs_only_flag)
		{
			sps->mb_adaptive_frame_field_flag = b->u1();
		}
		sps->direct_8x8_inference_flag = b->u1();
		sps->frame_cropping_flag = b->u1();
		if (sps->frame_cropping_flag)
		{
			sps->frame_crop_left_offset = b->ue();
			sps->frame_crop_right_offset = b->ue();
			sps->frame_crop_top_offset = b->ue();
			sps->frame_crop_bottom_offset = b->ue();
		}
		sps->vui_parameters_present_flag = b->u1();
		if (sps->vui_parameters_present_flag)
		{
			read_vui_parameters(sps, b);
		}
		read_rbsp_trailing_bits(b);
	}
	constexpr void read_pps(PPS* pps, Bitstream* b)
	{
		pps->pic_parameter_set_id = b->ue();
		pps->seq_parameter_set_id = b->ue();
		pps->entropy_coding_mode_flag = b->u1();
		pps->pic_order_present_flag = b->u1();
		pps->num_slice_groups_minus1 = b->ue();

		if (pps->num_slice_groups_minus1 > 0)
		{
			pps->slice_group_map_type = b->ue();
			if (pps->slice_group_map_type == 0)
			{
				for (int i_group = 0; i_group <= pps->num_slice_groups_minus1; i_group++)
				{
					pps->run_length_minus1[i_group] = b->ue();
				}
			}
			else if (pps->slice_group_map_type == 2)
			{
				for (int i_group = 0; i_group < pps->num_slice_groups_minus1; i_group++)
				{
					pps->top_left[i_group] = b->ue();
					pps->bottom_right[i_group] = b->ue();
				}
			}
			else if (pps->slice_group_map_type == 3 ||
				pps->slice_group_map_type == 4 ||
				pps->slice_group_map_type == 5)
			{
				pps->slice_group_change_direction_flag = b->u1();
				pps->slice_group_change_rate_minus1 = b->ue();
			}
			else if (pps->slice_group_map_type == 6)
			{
				pps->pic_size_in_map_units_minus1 = b->ue();
				for (int i = 0; i <= pps->pic_size_in_map_units_minus1; i++)
				{
					int v = intlog2(pps->num_slice_groups_minus1 + 1);
					pps->slice_group_id[i] = b->u(v);
				}
			}
		}
		pps->num_ref_idx_l0_active_minus1 = b->ue();
		pps->num_ref_idx_l1_active_minus1 = b->ue();
		pps->weighted_pred_flag = b->u1();
		pps->weighted_bipred_idc = b->u(2);
		pps->pic_init_qp_minus26 = b->se();
		pps->pic_init_qs_minus26 = b->se();
		pps->chroma_qp_index_offset = b->se();
		pps->deblocking_filter_control_present_flag = b->u1();
		pps->constrained_intra_pred_flag = b->u1();
		pps->redundant_pic_cnt_present_flag = b->u1();

		int have_more_data = 0;
		if (1) { have_more_data = more_rbsp_data(b); }
		if (0)
		{
			have_more_data = (pps->transform_8x8_mode_flag | pps->pic_scaling_matrix_present_flag | pps->second_chroma_qp_index_offset) != 0;
		}

		if (have_more_data)
		{
			pps->transform_8x8_mode_flag = b->u1();
			pps->pic_scaling_matrix_present_flag = b->u1();
			if (pps->pic_scaling_matrix_present_flag)
			{
				for (int i = 0; i < 6 + 2 * pps->transform_8x8_mode_flag; i++)
				{
					pps->pic_scaling_list_present_flag[i] = b->u1();
					if (pps->pic_scaling_list_present_flag[i])
					{
						if (i < 6)
						{
							read_scaling_list(b, pps->ScalingList4x4[i], 16,
								&(pps->UseDefaultScalingMatrix4x4Flag[i]));
						}
						else
						{
							read_scaling_list(b, pps->ScalingList8x8[i - 6], 64,
								&(pps->UseDefaultScalingMatrix8x8Flag[i - 6]));
						}
					}
				}
			}
			pps->second_chroma_qp_index_offset = b->se();
		}
		read_rbsp_trailing_bits(b);
	}
	constexpr int is_slice_type(int slice_type, int cmp_type)
	{
		if (slice_type >= 5) { slice_type -= 5; }
		if (cmp_type >= 5) { cmp_type -= 5; }
		if (slice_type == cmp_type) { return 1; }
		else { return 0; }
	}
	constexpr void read_ref_pic_list_reordering(SliceHeader* sh, Bitstream* b)
	{
		if (!is_slice_type(sh->slice_type, SH_SLICE_TYPE_I) && !is_slice_type(sh->slice_type, SH_SLICE_TYPE_SI))
		{
			sh->rplr.ref_pic_list_reordering_flag_l0 = b->u1();
			if (sh->rplr.ref_pic_list_reordering_flag_l0)
			{
				int n = -1;
				do
				{
					n++;
					sh->rplr.reorder_l0.reordering_of_pic_nums_idc[n] = b->ue();
					if (sh->rplr.reorder_l0.reordering_of_pic_nums_idc[n] == 0 ||
						sh->rplr.reorder_l0.reordering_of_pic_nums_idc[n] == 1)
					{
						sh->rplr.reorder_l0.abs_diff_pic_num_minus1[n] = b->ue();
					}
					else if (sh->rplr.reorder_l0.reordering_of_pic_nums_idc[n] == 2)
					{
						sh->rplr.reorder_l0.long_term_pic_num[n] = b->ue();
					}
				} while (sh->rplr.reorder_l0.reordering_of_pic_nums_idc[n] != 3 && !b->eof());
			}
		}
		if (is_slice_type(sh->slice_type, SH_SLICE_TYPE_B))
		{
			sh->rplr.ref_pic_list_reordering_flag_l1 = b->u1();
			if (sh->rplr.ref_pic_list_reordering_flag_l1)
			{
				int n = -1;
				do
				{
					n++;
					sh->rplr.reorder_l1.reordering_of_pic_nums_idc[n] = b->ue();
					if (sh->rplr.reorder_l1.reordering_of_pic_nums_idc[n] == 0 ||
						sh->rplr.reorder_l1.reordering_of_pic_nums_idc[n] == 1)
					{
						sh->rplr.reorder_l1.abs_diff_pic_num_minus1[n] = b->ue();
					}
					else if (sh->rplr.reorder_l1.reordering_of_pic_nums_idc[n] == 2)
					{
						sh->rplr.reorder_l1.long_term_pic_num[n] = b->ue();
					}
				} while (sh->rplr.reorder_l1.reordering_of_pic_nums_idc[n] != 3 && !b->eof());
			}
		}
	}
	constexpr void read_pred_weight_table(SliceHeader* sh, const SPS* sps, const PPS* pps, Bitstream* b)
	{
		(void)pps;
		sh->pwt.luma_log2_weight_denom = b->ue();
		if (sps->chroma_format_idc != 0)
		{
			sh->pwt.chroma_log2_weight_denom = b->ue();
		}
		for (int i = 0; i <= sh->num_ref_idx_l0_active_minus1; i++)
		{
			sh->pwt.luma_weight_l0_flag[i] = b->u1();
			if (sh->pwt.luma_weight_l0_flag[i])
			{
				sh->pwt.luma_weight_l0[i] = b->se();
				sh->pwt.luma_offset_l0[i] = b->se();
			}
			if (sps->chroma_format_idc != 0)
			{
				sh->pwt.chroma_weight_l0_flag[i] = b->u1();
				if (sh->pwt.chroma_weight_l0_flag[i])
				{
					for (int j = 0; j < 2; j++)
					{
						sh->pwt.chroma_weight_l0[i][j] = b->se();
						sh->pwt.chroma_offset_l0[i][j] = b->se();
					}
				}
			}
		}
		if (is_slice_type(sh->slice_type, SH_SLICE_TYPE_B))
		{
			for (int i = 0; i <= sh->num_ref_idx_l1_active_minus1; i++)
			{
				sh->pwt.luma_weight_l1_flag[i] = b->u1();
				if (sh->pwt.luma_weight_l1_flag[i])
				{
					sh->pwt.luma_weight_l1[i] = b->se();
					sh->pwt.luma_offset_l1[i] = b->se();
				}
				if (sps->chroma_format_idc != 0)
				{
					sh->pwt.chroma_weight_l1_flag[i] = b->u1();
					if (sh->pwt.chroma_weight_l1_flag[i])
					{
						for (int j = 0; j < 2; j++)
						{
							sh->pwt.chroma_weight_l1[i][j] = b->se();
							sh->pwt.chroma_offset_l1[i][j] = b->se();
						}
					}
				}
			}
		}
	}
	constexpr void read_dec_ref_pic_marking(SliceHeader* sh, NALHeader* nal, Bitstream* b)
	{
		if (nal->type == 5)
		{
			sh->drpm.no_output_of_prior_pics_flag = b->u1();
			sh->drpm.long_term_reference_flag = b->u1();
		}
		else
		{
			sh->drpm.adaptive_ref_pic_marking_mode_flag = b->u1();
			if (sh->drpm.adaptive_ref_pic_marking_mode_flag)
			{
				int n = -1;
				do
				{
					n++;
					sh->drpm.memory_management_control_operation[n] = b->ue();
					if (sh->drpm.memory_management_control_operation[n] == 1 ||
						sh->drpm.memory_management_control_operation[n] == 3)
					{
						sh->drpm.difference_of_pic_nums_minus1[n] = b->ue();
					}
					if (sh->drpm.memory_management_control_operation[n] == 2)
					{
						sh->drpm.long_term_pic_num[n] = b->ue();
					}
					if (sh->drpm.memory_management_control_operation[n] == 3 ||
						sh->drpm.memory_management_control_operation[n] == 6)
					{
						sh->drpm.long_term_frame_idx[n] = b->ue();
					}
					if (sh->drpm.memory_management_control_operation[n] == 4)
					{
						sh->drpm.max_long_term_frame_idx_plus1[n] = b->ue();
					}
				} while (sh->drpm.memory_management_control_operation[n] != 0 && !b->eof());
			}
		}
	}
	constexpr void read_slice_header(SliceHeader* sh, NALHeader* nal, const PPS* pps_array, const SPS* sps_array, Bitstream* b)
	{
		sh->first_mb_in_slice = b->ue();
		sh->slice_type = b->ue();
		sh->pic_parameter_set_id = b->ue();

		const PPS* pps = pps_array + sh->pic_parameter_set_id;
		const SPS* sps = sps_array + pps->seq_parameter_set_id;

		sh->frame_num = b->u(sps->log2_max_frame_num_minus4 + 4); // was u(v)
		if (!sps->frame_mbs_only_flag)
		{
			sh->field_pic_flag = b->u1();
			if (sh->field_pic_flag)
			{
				sh->bottom_field_flag = b->u1();
			}
		}
		if (nal->type == 5)
		{
			sh->idr_pic_id = b->ue();
		}
		if (sps->pic_order_cnt_type == 0)
		{
			sh->pic_order_cnt_lsb = b->u(sps->log2_max_pic_order_cnt_lsb_minus4 + 4); // was u(v)
			if (pps->pic_order_present_flag && !sh->field_pic_flag)
			{
				sh->delta_pic_order_cnt_bottom = b->se();
			}
		}
		if (sps->pic_order_cnt_type == 1 && !sps->delta_pic_order_always_zero_flag)
		{
			sh->delta_pic_order_cnt[0] = b->se();
			if (pps->pic_order_present_flag && !sh->field_pic_flag)
			{
				sh->delta_pic_order_cnt[1] = b->se();
			}
		}
		if (pps->redundant_pic_cnt_present_flag)
		{
			sh->redundant_pic_cnt = b->ue();
		}
		if (is_slice_type(sh->slice_type, SH_SLICE_TYPE_B))
		{
			sh->direct_spatial_mv_pred_flag = b->u1();
		}
		if (is_slice_type(sh->slice_type, SH_SLICE_TYPE_P) || is_slice_type(sh->slice_type, SH_SLICE_TYPE_SP) || is_slice_type(sh->slice_type, SH_SLICE_TYPE_B))
		{
			// H.264 spec 7.4.3: when num_ref_idx_active_override_flag is
			// zero, the slice's effective num_ref_idx_l[01]_active_minus1
			// defaults to the PPS num_ref_idx_l[01]_default_active_minus1.
			sh->num_ref_idx_l0_active_minus1 = pps->num_ref_idx_l0_active_minus1;
			sh->num_ref_idx_l1_active_minus1 = pps->num_ref_idx_l1_active_minus1;
			sh->num_ref_idx_active_override_flag = b->u1();
			if (sh->num_ref_idx_active_override_flag)
			{
				sh->num_ref_idx_l0_active_minus1 = b->ue();
				if (is_slice_type(sh->slice_type, SH_SLICE_TYPE_B))
				{
					sh->num_ref_idx_l1_active_minus1 = b->ue();
				}
			}
		}
		read_ref_pic_list_reordering(sh, b);
		if ((pps->weighted_pred_flag && (is_slice_type(sh->slice_type, SH_SLICE_TYPE_P) || is_slice_type(sh->slice_type, SH_SLICE_TYPE_SP))) ||
			(pps->weighted_bipred_idc == 1 && is_slice_type(sh->slice_type, SH_SLICE_TYPE_B)))
		{
			read_pred_weight_table(sh, sps, pps, b);
		}
		if (nal->idc != 0)
		{
			read_dec_ref_pic_marking(sh, nal, b);
		}
		if (pps->entropy_coding_mode_flag && !is_slice_type(sh->slice_type, SH_SLICE_TYPE_I) && !is_slice_type(sh->slice_type, SH_SLICE_TYPE_SI))
		{
			sh->cabac_init_idc = b->ue();
		}
		sh->slice_qp_delta = b->se();
		if (is_slice_type(sh->slice_type, SH_SLICE_TYPE_SP) || is_slice_type(sh->slice_type, SH_SLICE_TYPE_SI))
		{
			if (is_slice_type(sh->slice_type, SH_SLICE_TYPE_SP))
			{
				sh->sp_for_switch_flag = b->u1();
			}
			sh->slice_qs_delta = b->se();
		}
		if (pps->deblocking_filter_control_present_flag)
		{
			sh->disable_deblocking_filter_idc = b->ue();
			if (sh->disable_deblocking_filter_idc != 1)
			{
				sh->slice_alpha_c0_offset_div2 = b->se();
				sh->slice_beta_offset_div2 = b->se();
			}
		}
		if (pps->num_slice_groups_minus1 > 0 &&
			pps->slice_group_map_type >= 3 && pps->slice_group_map_type <= 5)
		{
			const int v = intlog2(pps->pic_size_in_map_units_minus1 + pps->slice_group_change_rate_minus1 + 1);
			sh->slice_group_change_cycle = b->u(v);
		}
	}

}

#endif // H264_H

//Copyright(c) 2025 Turánszki János
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in
//all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//THE SOFTWARE.
