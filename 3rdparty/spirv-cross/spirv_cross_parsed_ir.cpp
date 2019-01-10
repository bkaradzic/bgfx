/*
 * Copyright 2018-2019 Arm Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "spirv_cross_parsed_ir.hpp"
#include <assert.h>

using namespace std;
using namespace spv;

namespace spirv_cross
{
void ParsedIR::set_id_bounds(uint32_t bounds)
{
	ids.resize(bounds);
	meta.resize(bounds);
	block_meta.resize(bounds);
}

static string ensure_valid_identifier(const string &name, bool member)
{
	// Functions in glslangValidator are mangled with name(<mangled> stuff.
	// Normally, we would never see '(' in any legal identifiers, so just strip them out.
	auto str = name.substr(0, name.find('('));

	for (uint32_t i = 0; i < str.size(); i++)
	{
		auto &c = str[i];

		if (member)
		{
			// _m<num> variables are reserved by the internal implementation,
			// otherwise, make sure the name is a valid identifier.
			if (i == 0)
				c = isalpha(c) ? c : '_';
			else if (i == 2 && str[0] == '_' && str[1] == 'm')
				c = isalpha(c) ? c : '_';
			else
				c = isalnum(c) ? c : '_';
		}
		else
		{
			// _<num> variables are reserved by the internal implementation,
			// otherwise, make sure the name is a valid identifier.
			if (i == 0 || (str[0] == '_' && i == 1))
				c = isalpha(c) ? c : '_';
			else
				c = isalnum(c) ? c : '_';
		}
	}
	return str;
}

const string &ParsedIR::get_name(uint32_t id) const
{
	return meta[id].decoration.alias;
}

const string &ParsedIR::get_member_name(uint32_t id, uint32_t index) const
{
	auto &m = meta[id];
	if (index >= m.members.size())
	{
		static string empty;
		return empty;
	}

	return m.members[index].alias;
}

void ParsedIR::set_name(uint32_t id, const string &name)
{
	auto &str = meta[id].decoration.alias;
	str.clear();

	if (name.empty())
		return;

	// Reserved for temporaries.
	if (name[0] == '_' && name.size() >= 2 && isdigit(name[1]))
		return;

	str = ensure_valid_identifier(name, false);
}

void ParsedIR::set_member_name(uint32_t id, uint32_t index, const string &name)
{
	meta[id].members.resize(max(meta[id].members.size(), size_t(index) + 1));

	auto &str = meta[id].members[index].alias;
	str.clear();
	if (name.empty())
		return;

	// Reserved for unnamed members.
	if (name[0] == '_' && name.size() >= 3 && name[1] == 'm' && isdigit(name[2]))
		return;

	str = ensure_valid_identifier(name, true);
}

void ParsedIR::set_decoration_string(uint32_t id, Decoration decoration, const string &argument)
{
	auto &dec = meta[id].decoration;
	dec.decoration_flags.set(decoration);

	switch (decoration)
	{
	case DecorationHlslSemanticGOOGLE:
		dec.hlsl_semantic = argument;
		break;

	default:
		break;
	}
}

void ParsedIR::set_decoration(uint32_t id, Decoration decoration, uint32_t argument)
{
	auto &dec = meta[id].decoration;
	dec.decoration_flags.set(decoration);

	switch (decoration)
	{
	case DecorationBuiltIn:
		dec.builtin = true;
		dec.builtin_type = static_cast<BuiltIn>(argument);
		break;

	case DecorationLocation:
		dec.location = argument;
		break;

	case DecorationComponent:
		dec.component = argument;
		break;

	case DecorationOffset:
		dec.offset = argument;
		break;

	case DecorationArrayStride:
		dec.array_stride = argument;
		break;

	case DecorationMatrixStride:
		dec.matrix_stride = argument;
		break;

	case DecorationBinding:
		dec.binding = argument;
		break;

	case DecorationDescriptorSet:
		dec.set = argument;
		break;

	case DecorationInputAttachmentIndex:
		dec.input_attachment = argument;
		break;

	case DecorationSpecId:
		dec.spec_id = argument;
		break;

	case DecorationIndex:
		dec.index = argument;
		break;

	case DecorationHlslCounterBufferGOOGLE:
		meta[id].hlsl_magic_counter_buffer = argument;
		meta[argument].hlsl_is_magic_counter_buffer = true;
		break;

	case DecorationFPRoundingMode:
		dec.fp_rounding_mode = static_cast<FPRoundingMode>(argument);
		break;

	default:
		break;
	}
}

void ParsedIR::set_member_decoration(uint32_t id, uint32_t index, Decoration decoration, uint32_t argument)
{
	meta[id].members.resize(max(meta[id].members.size(), size_t(index) + 1));
	auto &dec = meta[id].members[index];
	dec.decoration_flags.set(decoration);

	switch (decoration)
	{
	case DecorationBuiltIn:
		dec.builtin = true;
		dec.builtin_type = static_cast<BuiltIn>(argument);
		break;

	case DecorationLocation:
		dec.location = argument;
		break;

	case DecorationComponent:
		dec.component = argument;
		break;

	case DecorationBinding:
		dec.binding = argument;
		break;

	case DecorationOffset:
		dec.offset = argument;
		break;

	case DecorationSpecId:
		dec.spec_id = argument;
		break;

	case DecorationMatrixStride:
		dec.matrix_stride = argument;
		break;

	case DecorationIndex:
		dec.index = argument;
		break;

	default:
		break;
	}
}

// Recursively marks any constants referenced by the specified constant instruction as being used
// as an array length. The id must be a constant instruction (SPIRConstant or SPIRConstantOp).
void ParsedIR::mark_used_as_array_length(uint32_t id)
{
	switch (ids[id].get_type())
	{
	case TypeConstant:
		get<SPIRConstant>(id).is_used_as_array_length = true;
		break;

	case TypeConstantOp:
	{
		auto &cop = get<SPIRConstantOp>(id);
		for (uint32_t arg_id : cop.arguments)
			mark_used_as_array_length(arg_id);
		break;
	}

	case TypeUndef:
		break;

	default:
		assert(0);
	}
}

Bitset ParsedIR::get_buffer_block_flags(const SPIRVariable &var) const
{
	auto &type = get<SPIRType>(var.basetype);
	assert(type.basetype == SPIRType::Struct);

	// Some flags like non-writable, non-readable are actually found
	// as member decorations. If all members have a decoration set, propagate
	// the decoration up as a regular variable decoration.
	Bitset base_flags = meta[var.self].decoration.decoration_flags;

	if (type.member_types.empty())
		return base_flags;

	Bitset all_members_flags = get_member_decoration_bitset(type.self, 0);
	for (uint32_t i = 1; i < uint32_t(type.member_types.size()); i++)
		all_members_flags.merge_and(get_member_decoration_bitset(type.self, i));

	base_flags.merge_or(all_members_flags);
	return base_flags;
}

const Bitset &ParsedIR::get_member_decoration_bitset(uint32_t id, uint32_t index) const
{
	auto &m = meta[id];
	if (index >= m.members.size())
	{
		static const Bitset cleared = {};
		return cleared;
	}

	return m.members[index].decoration_flags;
}

bool ParsedIR::has_decoration(uint32_t id, Decoration decoration) const
{
	return get_decoration_bitset(id).get(decoration);
}

uint32_t ParsedIR::get_decoration(uint32_t id, Decoration decoration) const
{
	auto &dec = meta[id].decoration;
	if (!dec.decoration_flags.get(decoration))
		return 0;

	switch (decoration)
	{
	case DecorationBuiltIn:
		return dec.builtin_type;
	case DecorationLocation:
		return dec.location;
	case DecorationComponent:
		return dec.component;
	case DecorationOffset:
		return dec.offset;
	case DecorationBinding:
		return dec.binding;
	case DecorationDescriptorSet:
		return dec.set;
	case DecorationInputAttachmentIndex:
		return dec.input_attachment;
	case DecorationSpecId:
		return dec.spec_id;
	case DecorationArrayStride:
		return dec.array_stride;
	case DecorationMatrixStride:
		return dec.matrix_stride;
	case DecorationIndex:
		return dec.index;
	case DecorationFPRoundingMode:
		return dec.fp_rounding_mode;
	default:
		return 1;
	}
}

const string &ParsedIR::get_decoration_string(uint32_t id, Decoration decoration) const
{
	auto &dec = meta[id].decoration;
	static const string empty;

	if (!dec.decoration_flags.get(decoration))
		return empty;

	switch (decoration)
	{
	case DecorationHlslSemanticGOOGLE:
		return dec.hlsl_semantic;

	default:
		return empty;
	}
}

void ParsedIR::unset_decoration(uint32_t id, Decoration decoration)
{
	auto &dec = meta[id].decoration;
	dec.decoration_flags.clear(decoration);
	switch (decoration)
	{
	case DecorationBuiltIn:
		dec.builtin = false;
		break;

	case DecorationLocation:
		dec.location = 0;
		break;

	case DecorationComponent:
		dec.component = 0;
		break;

	case DecorationOffset:
		dec.offset = 0;
		break;

	case DecorationBinding:
		dec.binding = 0;
		break;

	case DecorationDescriptorSet:
		dec.set = 0;
		break;

	case DecorationInputAttachmentIndex:
		dec.input_attachment = 0;
		break;

	case DecorationSpecId:
		dec.spec_id = 0;
		break;

	case DecorationHlslSemanticGOOGLE:
		dec.hlsl_semantic.clear();
		break;

	case DecorationFPRoundingMode:
		dec.fp_rounding_mode = FPRoundingModeMax;
		break;

	case DecorationHlslCounterBufferGOOGLE:
	{
		auto &counter = meta[id].hlsl_magic_counter_buffer;
		if (counter)
		{
			meta[counter].hlsl_is_magic_counter_buffer = false;
			counter = 0;
		}
		break;
	}

	default:
		break;
	}
}

bool ParsedIR::has_member_decoration(uint32_t id, uint32_t index, Decoration decoration) const
{
	return get_member_decoration_bitset(id, index).get(decoration);
}

uint32_t ParsedIR::get_member_decoration(uint32_t id, uint32_t index, Decoration decoration) const
{
	auto &m = meta[id];
	if (index >= m.members.size())
		return 0;

	auto &dec = m.members[index];
	if (!dec.decoration_flags.get(decoration))
		return 0;

	switch (decoration)
	{
	case DecorationBuiltIn:
		return dec.builtin_type;
	case DecorationLocation:
		return dec.location;
	case DecorationComponent:
		return dec.component;
	case DecorationBinding:
		return dec.binding;
	case DecorationOffset:
		return dec.offset;
	case DecorationSpecId:
		return dec.spec_id;
	case DecorationIndex:
		return dec.index;
	default:
		return 1;
	}
}

const Bitset &ParsedIR::get_decoration_bitset(uint32_t id) const
{
	auto &dec = meta[id].decoration;
	return dec.decoration_flags;
}

void ParsedIR::set_member_decoration_string(uint32_t id, uint32_t index, Decoration decoration, const string &argument)
{
	meta[id].members.resize(max(meta[id].members.size(), size_t(index) + 1));
	auto &dec = meta[id].members[index];
	dec.decoration_flags.set(decoration);

	switch (decoration)
	{
	case DecorationHlslSemanticGOOGLE:
		dec.hlsl_semantic = argument;
		break;

	default:
		break;
	}
}

const string &ParsedIR::get_member_decoration_string(uint32_t id, uint32_t index, Decoration decoration) const
{
	static const string empty;
	auto &m = meta[id];

	if (!has_member_decoration(id, index, decoration))
		return empty;

	auto &dec = m.members[index];

	switch (decoration)
	{
	case DecorationHlslSemanticGOOGLE:
		return dec.hlsl_semantic;

	default:
		return empty;
	}
}

void ParsedIR::unset_member_decoration(uint32_t id, uint32_t index, Decoration decoration)
{
	auto &m = meta[id];
	if (index >= m.members.size())
		return;

	auto &dec = m.members[index];

	dec.decoration_flags.clear(decoration);
	switch (decoration)
	{
	case DecorationBuiltIn:
		dec.builtin = false;
		break;

	case DecorationLocation:
		dec.location = 0;
		break;

	case DecorationComponent:
		dec.component = 0;
		break;

	case DecorationOffset:
		dec.offset = 0;
		break;

	case DecorationSpecId:
		dec.spec_id = 0;
		break;

	case DecorationHlslSemanticGOOGLE:
		dec.hlsl_semantic.clear();
		break;

	default:
		break;
	}
}

uint32_t ParsedIR::increase_bound_by(uint32_t incr_amount)
{
	auto curr_bound = ids.size();
	auto new_bound = curr_bound + incr_amount;
	ids.resize(new_bound);
	meta.resize(new_bound);
	block_meta.resize(new_bound);
	return uint32_t(curr_bound);
}

} // namespace spirv_cross
