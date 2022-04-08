local codegen = require "codegen"
local idl = codegen.idl "bgfx.idl"

local zig_template = [[
// Copyright 2011-2022 Branimir Karadzic. All rights reserved.
// License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE


//
// AUTO GENERATED! DO NOT EDIT!
//


const std = @import("std");

pub const ViewId = u16;

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

local enum = { }

local function convert_array(member)
	if string.find(member.array, "::") then
		return string.format("[%s]", enum[member.array])
	else
		return member.array
	end
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
	elseif hasPrefix(arg.ctype, "uint8_t") then
		return arg.ctype:gsub("uint8_t", "u8")
	elseif hasPrefix(arg.ctype, "uintptr_t") then
		return arg.ctype:gsub("uintptr_t", "usize")
	elseif hasPrefix(arg.ctype, "float") then
		return arg.ctype:gsub("float", "f32")
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
	ctype = ctype:gsub("const void%*", "?*const anyopaque")
	ctype = ctype:gsub("Encoder%*", "?*Encoder")

	if hasSuffix(ctype, "void*") then
		ctype = ctype:gsub("void%*", "?*anyopaque");
	elseif hasSuffix(ctype, "*") then
		ctype = "[*c]" .. ctype:gsub("*", "")
	end

	if arg.array ~= nil then
		ctype = ctype:gsub("const ", "")
		ctype = convert_array(arg) .. ctype
	end

	return ctype
end

local function convert_struct_type(arg)
	return convert_type(arg)
end

local function convert_ret_type(arg)
	return convert_type(arg)
end

local converter = {}
local yield = coroutine.yield
local gen = {}

local indent = ""

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

local combined = { "State", "Stencil", "Buffer", "Texture", "Sampler", "Reset" }

for _, v in ipairs(combined) do
	combined[v] = {}
end

local lastCombinedFlag
local function FlagBlock(typ)
	local format = "0x%08x"
	local enumType = "u32"
	if typ.bits == 64 then
		format = "0x%016x"
		enumType = "u64"
	elseif typ.bits == 16 then
		format = "0x%04x"
		enumType = "u16"
	end

	local name = typ.name .. "Flags"
	yield("pub const " .. name .. " = " .. enumType .. ";")

	for idx, flag in ipairs(typ.flag) do
		if flag.comment ~= nil then
			if idx ~= 1 then
				yield("")
			end

			for _, comment in ipairs(flag.comment) do
				yield("/// " .. comment)
			end
		end

		local flagName = flag.name:gsub("_", "")
		yield("pub const " .. name .. "_"
			.. flagName
			.. ": "
			.. name
			.. string.rep(" ", 22 - #(flagName))
			.. " = "
			.. string.format(flag.format or format, flag.value)
			.. ";"
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

local function convert_struct_member(member)
	return member.name .. ": " .. convert_struct_type(member)
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
				namespace = typ.namespace
				indent = "    "
			end
		elseif namespace ~= "" then
			indent = "    "
			namespace = ""
			skip = true
		end

		if not skip then
			if typ.name ~= "Encoder" then
				yield(indent .. "pub const " .. typ.name .. " = extern struct {")
			else
				yield(indent .. "pub const " .. typ.name .. " = opaque {")
			end
		end

		for _, member in ipairs(typ.struct) do
			yield(indent .. indent .. convert_struct_member(member) .. ",")
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
		local ptr = "[*c]"
		if func.const ~= nil then
			ptr = ptr .. "const "
		end

		if func.this_type.type == "Encoder" then
			ptr = "?*"
		end
		args[1] = "self: " .. ptr .. func.this_type.type
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
	yield("pub extern fn bgfx_" .. func.cname .. "(" .. table.concat(args, ", ") .. ") " .. convert_ret_type(func.ret) .. ";")
end

function gen.write(codes, outputfile)
	local out = assert(io.open(outputfile, "wb"))
	out:write(codes)
	out:close()
	print("Generating: " .. outputfile)
end

if (...) == nil then
	-- run `lua bindings-zig.lua` in command line
	print(gen.gen())
end

return gen
