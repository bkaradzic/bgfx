local codegen = require "codegen"
local idl = codegen.idl "bgfx.idl"

local csharp_template = [[
using System;
using System.Runtime.InteropServices;
using System.Security;

internal struct bgfx
{
	$types

	$funcs

#if DEBUG
	const string DllName = "bgfx_debug.dll";
#else
	const string DllName = "bgfx.dll";
#endif
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
	elseif arg.ctype == "const char*" then
		return "[MarshalAs(UnmanagedType.LPStr)] string"
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

local function convert_ret_type(arg)
	local ctype = convert_type(arg)
	if hasPrefix(ctype, "[MarshalAs(UnmanagedType.LPStr)]") then
		return "string"
	end

	return ctype
end

local converter = {}
local yield = coroutine.yield

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
			if any then
				table.insert(tmp, "")
			end
		end
		return table.concat(tmp, "\n\t")
	end)
	return r
end

local combined = { "State", "Stencil", "Buffer", "Texture", "Sampler", "Reset" }

for _, v in ipairs(combined) do
	combined[v] = {}
end

local lastCombinedFlag

local function FlagBlock(typ)
	if typ == nil then
		return
	end

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

	for _, flag in ipairs(typ.flag) do
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
		FlagBlock(combined[lastCombinedFlag])
		lastCombinedFlag = nil
	end
end

function converter.types(typ)
	if typ.handle then
		lastCombinedFlagBlock()

		yield("public struct " .. typ.name .. "{ public ushort idx; }")
	elseif hasSuffix(typ.name, "::Enum") then
		lastCombinedFlagBlock()

		yield("public enum " .. typ.typename)
		yield("{")
		for _, enum in ipairs(typ.enum) do
			yield("\t" .. enum.name .. ",")
		end
		yield("}")
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
				})
			end
			if typ.shift then
				table.insert(flags, {
					name = name .. "Shift",
					value = typ.shift,
					format = "%d",
				})
			end
			if typ.mask then
				-- generate Mask
				table.insert(flags, {
					name = name .. "Mask",
					value = typ.mask,
				})
				lookup[name .. "Mask"] = typ.mask
			end
		else
			FlagBlock(typ)
		end
	elseif typ.struct ~= nil then

		if typ.namespace ~= nil then
			yield("public unsafe struct " .. typ.namespace .. typ.name)
		else
			yield("public unsafe struct " .. typ.name)
		end

		yield("{")

		for _, member in ipairs(typ.struct) do
			yield(
				"\tpublic " .. convert_type(member) .. " " .. member.name .. ";"
				)
		end

		yield("}")
	end
end

function converter.funcs(func)
	yield("[DllImport(DllName, EntryPoint=\"bgfx_" .. func.cname .. "\", CallingConvention = CallingConvention.Cdecl)]")

	if func.ret.cpptype == "bool" then
		yield("[return: MarshalAs(UnmanagedType.I1)]")
	elseif func.ret.cpptype == "const char*" then
		yield("[return: MarshalAs(UnmanagedType.LPStr)]")
	end

	local first = ""
	local args  = "("

	if func.this ~= nil then

		local thisType = func.this:gsub("const ", "")
		if thisType == "bgfx_encoder_t*" then
			thisType = "Encoder*"
		elseif thisType == "bgfx_attachment_t*" then
			thisType = "Attachment*"
		elseif thisType == "bgfx_vertex_decl_t*" then
			thisType = "VertexDecl*"
		end

		args = args .. thisType .. " " .. "_this"
		first = ", "
	end

	for _, arg in ipairs(func.args) do

		local argtype = convert_type(arg)

		args = args .. first .. argtype .. " " .. arg.name
		first = ", "
	end

	yield("internal static extern unsafe " .. convert_ret_type(func.ret) .. " " .. func.cname .. args .. ");")
end

-- printtable("idl types", idl.types)
-- printtable("idl funcs", idl.funcs)

function gen.write(codes, outputfile)
	local out = assert(io.open(outputfile, "wb"))
	out:write(codes)
	out:close()
end

return gen
