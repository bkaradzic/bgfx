local codegen = require "codegen"
local idl = codegen.idl "bgfx.idl"

local zig_template = [[
// Copyright 2011-2022 Branimir Karadzic. All rights reserved.
// License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE


//
// AUTO GENERATED! DO NOT EDIT!
//


const std = @import("std");

$types

$funcs

]]

local function isempty(s)
	return s == nil or s == ''
end

local function hasPrefix(str, prefix)
	return prefix == "" or str:sub(1, #prefix) == prefix
end

local function hasSuffix(str, suffix)
	return suffix == "" or str:sub(- #suffix) == suffix
end

local function convert_type_0(arg)

	if hasPrefix(arg.ctype, "uint64_t") then
		return arg.ctype:gsub("uint64_t", "u64")
	elseif hasPrefix(arg.ctype, "int64_t") then
		return arg.ctype:gsub("int64_t", "i64")
	elseif hasPrefix(arg.ctype, "uint32_t") then
		return arg.ctype:gsub("uint32_t", "u32")
	elseif hasPrefix(arg.ctype, "int32_t") then
		return arg.ctype:gsub("int32_t", "i32")
	elseif hasPrefix(arg.ctype, "uint16_t") then
		return arg.ctype:gsub("uint16_t", "u16")
	elseif hasPrefix(arg.ctype, "bgfx_view_id_t") then
		return arg.ctype:gsub("bgfx_view_id_t", "u16")
	elseif hasPrefix(arg.ctype, "uint8_t") then
		return arg.ctype:gsub("uint8_t", "u8")
	elseif hasPrefix(arg.ctype, "uintptr_t") then
		return arg.ctype:gsub("uintptr_t", "usize")
	elseif hasPrefix(arg.ctype, "float") then
		return arg.ctype:gsub("float", "f32")
		-- elseif arg.ctype == "bgfx_caps_gpu_t" then
		--     return arg.ctype:gsub("bgfx_caps_gpu_t", "u32")
	elseif arg.ctype == "const char*" then
	   return "[*c]const u8"
	elseif hasPrefix(arg.ctype, "char") then
		return arg.ctype:gsub("char", "u8")
	elseif hasSuffix(arg.fulltype, "Handle") then
		return arg.fulltype
	elseif arg.ctype == "..." then
		return "..."
	elseif arg.ctype == "va_list"
		or arg.fulltype == "bx::AllocatorI*"
		or arg.fulltype == "CallbackI*"
		or arg.fulltype == "ReleaseFn" then
		return "?*anyopaque"
	elseif arg.fulltype == "const ViewId*" then
		return "[*c]c_ushort"
	end

	return arg.fulltype
end

local function convert_type(arg)
	local ctype = convert_type_0(arg)
	ctype = ctype:gsub("::Enum", "")
	ctype = ctype:gsub(" &", "*")
	ctype = ctype:gsub("&", "*")
	ctype = ctype:gsub("char", "u8")
	ctype = ctype:gsub("float", "f32")
	if hasPrefix(ctype, "const ") then
		ctype = ctype:gsub("const ", "")
	end
	if hasSuffix(ctype, "void*") then
		ctype = ctype:gsub("void%*", "?*anyopaque");
	elseif hasSuffix(ctype, "*") then
		ctype = "[*c]" .. ctype:gsub("*", "")
	end

	return ctype
end

local function convert_struct_type(arg)
	local ctype = convert_type(arg)
	if hasPrefix(arg.ctype, "bool") then
		ctype = ctype:gsub("bool", "bool")
	end
	return ctype
end

local function convert_ret_type(arg)
	return convert_type(arg)
end

local converter = {}
local yield = coroutine.yield
local indent = ""

local gen = {}

function gen.gen()
	local r = zig_template:gsub("$(%l+)", function(what)
		local tmp = {}
		for _, object in ipairs(idl[what]) do
			local co = coroutine.create(converter[what])
			local any
			while true do
				local ok, v = coroutine.resume(co, object)
				assert(ok, debug.traceback(co, v))
				if not v then
					break
				end
				table.insert(tmp, v)
				any = true
			end
			if any and tmp[#tmp] ~= "" then
				table.insert(tmp, "")
			end
		end
		return table.concat(tmp, "\n")
	end)
	return r
end

-- function gen.gen_dllname()
-- 	return csharp_dllname_template
-- end

local combined = { "State", "Stencil", "Buffer", "Texture", "Sampler", "Reset" }

for _, v in ipairs(combined) do
	combined[v] = {}
end

local lastCombinedFlag

local function FlagBlock(typ)
	local format = "0x%08x"
	local enumType = "c_uint"
	if typ.bits == 64 then
		format = "0x%016x"
		enumType = "c_ulong"
	elseif typ.bits == 16 then
		format = "0x%04x"
		enumType = "c_ushort"
	end

	yield("pub const " .. typ.name .. "Flags = enum(" .. enumType .. ") {")

	for idx, flag in ipairs(typ.flag) do

		if flag.comment ~= nil then
			if idx ~= 1 then
				yield("")
			end

			for _, comment in ipairs(flag.comment) do
				yield("    /// " .. comment)
			end
		end

		local flagName = flag.name:gsub("_", "")
		yield("    "
			.. flagName
			.. string.rep(" ", 22 - #(flagName))
			.. " = "
			.. string.format(flag.format or format, flag.value)
			.. ","
		)
	end

	if typ.shift then
		yield("    "
			.. "Shift"
			.. string.rep(" ", 22 - #("Shift"))
			.. " = "
			.. flag.shift
		)
	end

	-- generate Mask
	if typ.mask then
		yield("    "
			.. "Mask"
			.. string.rep(" ", 22 - #("Mask"))
			.. " = "
			.. string.format(format, flag.mask)
		)
	end

	yield("};")
end

local function lastCombinedFlagBlock()
	if lastCombinedFlag then
		local typ = combined[lastCombinedFlag]
		if typ then
			FlagBlock(combined[lastCombinedFlag])
			yield("")
		end
		lastCombinedFlag = nil
	end
end

local enum = {}

local function convert_array(member)
	if string.find(member.array, "::") then
		return string.format("[%d]", enum[member.array])
	else
		return member.array
	end
end

local function convert_struct_member(member)
	if member.array then
		return member.name .. ": " .. convert_array(member) .. convert_struct_type(member)
	else
		return member.name .. ": " .. convert_struct_type(member)
	end
end

local namespace = ""

function converter.types(typ)
	if typ.handle then
		lastCombinedFlagBlock()

		yield("pub const " .. typ.name .. " = extern struct {")
		yield("    idx: c_ushort,")
		yield("};")
	elseif hasSuffix(typ.name, "::Enum") then
		lastCombinedFlagBlock()

		yield("pub const " .. typ.typename .. " = enum(c_int) {")
		for idx, enum in ipairs(typ.enum) do

			if enum.comment ~= nil then
				if idx ~= 1 then
					yield("")
				end

				for _, comment in ipairs(enum.comment) do
					yield("    /// " .. comment)
				end
			end

			yield("    " .. enum.name .. ",")
		end
		yield("");
		yield("    Count")
		yield("};")

		enum["[" .. typ.typename .. "::Count]"] = #typ.enum

	elseif typ.bits ~= nil then
		local prefix, name = typ.name:match "(%u%l+)(.*)"
		if prefix ~= lastCombinedFlag then
			lastCombinedFlagBlock()
			lastCombinedFlag = prefix
		end
		local combinedFlag = combined[prefix]
		if combinedFlag then
			combinedFlag.bits = typ.bits
			combinedFlag.name = prefix
			local flags = combinedFlag.flag or {}
			combinedFlag.flag = flags
			local lookup = combinedFlag.lookup or {}
			combinedFlag.lookup = lookup
			for _, flag in ipairs(typ.flag) do
				local flagName = name .. flag.name:gsub("_", "")
				local value = flag.value
				if value == nil then
					-- It's a combined flag
					value = 0
					for _, v in ipairs(flag) do
						value = value | assert(lookup[name .. v], v .. " is not defined for " .. flagName)
					end
				end
				lookup[flagName] = value
				table.insert(flags, {
					name = flagName,
					value = value,
					comment = flag.comment,
				})
			end

			if typ.shift then
				table.insert(flags, {
					name = name .. "Shift",
					value = typ.shift,
					format = "%d",
					comment = typ.comment,
				})
			end

			if typ.mask then
				-- generate Mask
				table.insert(flags, {
					name = name .. "Mask",
					value = typ.mask,
					comment = typ.comment,
				})
				lookup[name .. "Mask"] = typ.mask
			end
		else
			FlagBlock(typ)
		end
	elseif typ.struct ~= nil then

		local skip = false

		if typ.namespace ~= nil then
			if namespace ~= typ.namespace then
				yield("pub const " .. typ.namespace .. " = extern struct {")
				-- yield("{")
				namespace = typ.namespace
				indent = "    "
			end
		elseif namespace ~= "" then
			indent = "    "
			namespace = ""
			skip = true
		end

		if not skip then
			yield(indent .. "pub const " .. typ.name .. " = extern struct {")
			-- yield(indent .. "{")
		end

		for _, member in ipairs(typ.struct) do
			yield(
			indent .. indent .. convert_struct_member(member) .. ","
			)
		end

		yield(indent .. "};")
	end
end

function converter.funcs(func)

	if func.cpponly then
		return
	end

	if func.comments ~= nil then
		for _, line in ipairs(func.comments) do
			yield("/// " .. line)
		end

		local hasParams = false

		for _, arg in ipairs(func.args) do
			if arg.comment ~= nil then
				local comment = table.concat(arg.comment, " ")

				yield("/// <param name=\""
					.. arg.name
					.. "\">"
					.. comment
					.. "</param>"
				)

				hasParams = true
			end
		end
	end

	local args = {}
	if func.this ~= nil then
		args[1] = "self: [*c]" .. func.this_type.type
	end
	for _, arg in ipairs(func.args) do
		local argName = arg.name:gsub("_", "")
		argName = argName:gsub("enum", "enumeration")
		if not isempty(argName) then
			table.insert(args, argName .. ": " .. convert_type(arg))
		else
			table.insert(args, convert_type(arg))
		end
	end
	yield("pub extern fn bgfx_" .. func.cname .. "(" .. table.concat(args, ", ") .. ") callconv(.C) " .. convert_ret_type(func.ret) .. ";")
end

-- printtable("idl types", idl.types)
-- printtable("idl funcs", idl.funcs)

function gen.write(codes, outputfile)
	local out = assert(io.open(outputfile, "wb"))
	out:write(codes)
	out:close()
	print("Generating: " .. outputfile)
end

if (...) == nil then
	-- run `lua bindings-cs.lua` in command line
	print(gen.gen())
end

return gen
