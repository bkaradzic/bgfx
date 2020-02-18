local codegen = require "codegen"
local idl = codegen.idl "bgfx.idl"

local csharp_template = [[
/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

/*
 *
 * AUTO GENERATED! DO NOT EDIT!
 *
 */

using System;
using System.Runtime.InteropServices;

namespace Bgfx
{
public static partial class bgfx
{
	$types

	$funcs
}
}
]]

local csharp_dllname_template = [[
/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

/*
 *
 * AUTO GENERATED! DO NOT EDIT!
 *
 * Include this file in your build if you want to use the default DllImport
 * names of bgfx.dll and bgfx_debug.dll.  Otherwise, define your own
 * partial class like the below with a const DllName for your use.
 *
 */

namespace Bgfx
{
public static partial class bgfx
{
#if DEBUG
       const string DllName = "bgfx_debug.dll";
#else
       const string DllName = "bgfx.dll";
#endif
}
}
]]

local function hasPrefix(str, prefix)
	return prefix == "" or str:sub(1, #prefix) == prefix
end

local function hasSuffix(str, suffix)
	return suffix == "" or str:sub(-#suffix) == suffix
end

local function convert_type_0(arg)

	if hasPrefix(arg.ctype, "uint64_t") then
		return arg.ctype:gsub("uint64_t", "ulong")
	elseif hasPrefix(arg.ctype, "int64_t") then
		return arg.ctype:gsub("int64_t", "long")
	elseif hasPrefix(arg.ctype, "uint32_t") then
		return arg.ctype:gsub("uint32_t", "uint")
	elseif hasPrefix(arg.ctype, "int32_t") then
		return arg.ctype:gsub("int32_t", "int")
	elseif hasPrefix(arg.ctype, "uint16_t") then
		return arg.ctype:gsub("uint16_t", "ushort")
	elseif hasPrefix(arg.ctype, "bgfx_view_id_t") then
		return arg.ctype:gsub("bgfx_view_id_t", "ushort")
	elseif hasPrefix(arg.ctype, "uint8_t") then
		return arg.ctype:gsub("uint8_t", "byte")
	elseif hasPrefix(arg.ctype, "uintptr_t") then
		return arg.ctype:gsub("uintptr_t", "UIntPtr")
	elseif arg.ctype == "bgfx_caps_gpu_t" then
	    return arg.ctype:gsub("bgfx_caps_gpu_t", "uint")
	elseif arg.ctype == "const char*" then
		return "[MarshalAs(UnmanagedType.LPStr)] string"
	elseif hasPrefix(arg.ctype, "char") then
		return arg.ctype:gsub("char", "byte")
	elseif hasSuffix(arg.fulltype, "Handle") then
		return arg.fulltype
	elseif arg.ctype == "..." then
		return "[MarshalAs(UnmanagedType.LPStr)] string args"
	elseif arg.ctype == "va_list"
		or arg.fulltype == "bx::AllocatorI*"
		or arg.fulltype == "CallbackI*"
		or arg.fulltype == "ReleaseFn" then
		return "IntPtr"
	elseif arg.fulltype == "const ViewId*" then
		return "ushort*"
	end

	return arg.fulltype
end

local function convert_type(arg)
	local ctype = convert_type_0(arg)
	ctype = ctype:gsub("::Enum", "")
	ctype = ctype:gsub("const ", "")
	ctype = ctype:gsub(" &", "*")
	ctype = ctype:gsub("&", "*")
	return ctype
end

local function convert_struct_type(arg)
	local ctype = convert_type(arg)
	if hasPrefix(arg.ctype, "bool") then
		ctype = ctype:gsub("bool", "byte")
	end
	return ctype
end

local function convert_ret_type(arg)
	local ctype = convert_type(arg)
	if hasPrefix(ctype, "[MarshalAs(UnmanagedType.LPStr)]") then
		return "IntPtr"
	end
	return ctype
end

local converter = {}
local yield = coroutine.yield
local indent = ""

local gen = {}

function gen.gen()
	local r = csharp_template:gsub("$(%l+)", function(what)
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
		return table.concat(tmp, "\n\t")
	end)
	return r
end

function gen.gen_dllname()
	return csharp_dllname_template
end

local combined = { "State", "Stencil", "Buffer", "Texture", "Sampler", "Reset" }

for _, v in ipairs(combined) do
	combined[v] = {}
end

local lastCombinedFlag

local function FlagBlock(typ)
	local format = "0x%08x"
	local enumType = " : uint"
	if typ.bits == 64 then
		format = "0x%016x"
		enumType = " : ulong"
	elseif typ.bits == 16 then
		format = "0x%04x"
		enumType = " : ushort"
	end

	yield("[Flags]")
	yield("public enum " .. typ.name .. "Flags" .. enumType)
	yield("{")

	for idx, flag in ipairs(typ.flag) do

		if flag.comment ~= nil then
			if idx ~= 1 then
				yield("")
			end

			yield("\t/// <summary>")
			for _, comment in ipairs(flag.comment) do
				yield("\t/// " .. comment)
			end
			yield("\t/// </summary>")
		end

		local flagName = flag.name:gsub("_", "")
		yield("\t"
			.. flagName
			.. string.rep(" ", 22 - #(flagName))
			.. " = "
			.. string.format(flag.format or format, flag.value)
			.. ","
			)
	end

	if typ.shift then
		yield("\t"
			.. "Shift"
			.. string.rep(" ", 22 - #("Shift"))
			.. " = "
			.. flag.shift
			)
	end

	-- generate Mask
	if typ.mask then
		yield("\t"
			.. "Mask"
			.. string.rep(" ", 22 - #("Mask"))
			.. " = "
			.. string.format(format, flag.mask)
			)
	end

	yield("}")
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
		return "fixed " .. convert_struct_type(member) .. " " .. member.name .. convert_array(member)
	else
		return convert_struct_type(member) .. " " .. member.name
	end
end

local namespace = ""

function converter.types(typ)
	if typ.handle then
		lastCombinedFlagBlock()

		yield("public struct " .. typ.name .. " {")
        yield("    public ushort idx;")
        yield("    public bool Valid => idx != UInt16.MaxValue;")
        yield("}")
	elseif hasSuffix(typ.name, "::Enum") then
		lastCombinedFlagBlock()

		yield("public enum " .. typ.typename)
		yield("{")
		for idx, enum in ipairs(typ.enum) do

			if enum.comment ~= nil then
				if idx ~= 1 then
					yield("")
				end

				yield("\t/// <summary>")
				for _, comment in ipairs(enum.comment) do
					yield("\t/// " .. comment)
				end
				yield("\t/// </summary>")
			end

			yield("\t" .. enum.name .. ",")
		end
		yield("");
		yield("\tCount")
		yield("}")

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
				yield("public unsafe struct " .. typ.namespace)
				yield("{")
				namespace = typ.namespace
				indent = "\t"
			end
		elseif namespace ~= "" then
			indent = ""
			namespace = ""
			skip = true
		end

		if not skip then
			yield(indent .. "public unsafe struct " .. typ.name)
			yield(indent .. "{")
		end

		for _, member in ipairs(typ.struct) do
			yield(
				indent .. "\tpublic " .. convert_struct_member(member) .. ";"
				)
		end

		yield(indent .. "}")
	end
end

function converter.funcs(func)

	if func.cpponly then
		return
	end

	if func.comments ~= nil then
		yield("/// <summary>")
		for _, line in ipairs(func.comments) do
			yield("/// " .. line)
		end
		yield("/// </summary>")
		yield("///")

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

		if hasParams then
			yield("///")
		end
	end

	yield("[DllImport(DllName, EntryPoint=\"bgfx_" .. func.cname .. "\", CallingConvention = CallingConvention.Cdecl)]")

	if func.ret.cpptype == "bool" then
		yield("[return: MarshalAs(UnmanagedType.I1)]")
	end

	local args = {}
	if func.this ~= nil then
		args[1] = func.this_type.type .. "* _this"
	end
	for _, arg in ipairs(func.args) do
		table.insert(args, convert_type(arg) .. " " .. arg.name)
	end
	yield("public static extern unsafe " .. convert_ret_type(func.ret) .. " " .. func.cname
		.. "(" .. table.concat(args, ", ") .. ");")
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
