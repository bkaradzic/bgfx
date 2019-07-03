local idl = require "idl"

do
	local doxygen = require "doxygen"
	local source = doxygen.load "bgfx.idl"
	local f = assert(load(source, "bgfx.idl" , "t", idl))
	f()

	local codegen = require "codegen"
	codegen.nameconversion(idl.types, idl.funcs)
end

local csharp_template = [[
using System;
using System.Runtime.InteropServices;
using System.Security;

internal struct NativeFunctions
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

	if arg.ctype == "uint64_t" then
		return "ulong"
	elseif arg.ctype == "uint32_t" then
		return "uint"
	elseif arg.ctype == "uint16_t" then
		return "ushort"
	elseif arg.ctype == "uint8_t" then
		return "byte"
	elseif arg.ctype == "const char*" then
		return "[MarshalAs(UnmanagedType.LPStr)] string"
	elseif hasSuffix(arg.fulltype, "Handle") then
		return arg.fulltype
	elseif hasSuffix(arg.fulltype, "::Enum") then
		return arg.fulltype:gsub("::Enum", "")
	end

	return arg.ctype
end

local function convert_type(arg)
	local ctype = convert_type_0(arg)
	return ctype:gsub("const ", "")
end

local converter = {}
local yield = coroutine.yield

local function gen()
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

local lastCombinedIdx = -1

local combined = { "State", "Stencil", "Buffer", "Texture", "Sampler", "Reset" }

local function isCombinedBlock(str)
	for idx, prefix in ipairs(combined) do
		if hasPrefix(str, prefix) then
			return idx
		end
	end

	return -1
end

local function endCombinedBlock()
	if lastCombinedIdx ~= -1 then
		yield("}")
	end

	lastCombinedIdx = -1
end

function converter.types(typ)
	if typ.handle then
		endCombinedBlock()

		yield("public struct " .. typ.name .. "{ public ushort idx; }")
	elseif hasSuffix(typ.name, "::Enum") then
		endCombinedBlock()

		yield("public enum " .. typ.typename)
		yield("{")
		for _, enum in ipairs(typ.enum) do
			yield("\t" .. enum.name .. ",")
		end
		yield("}")
	elseif typ.bits ~= nil then

		local idx = isCombinedBlock(typ.name)

		if idx ~= lastCombinedIdx then
			endCombinedBlock()
		end

		local format = "0x%08x"
		local enumType = ""
		if typ.bits == 64 then
			format = "0x%016x"
			enumType = " : ulong"
		elseif typ.bits == 16 then
			format = "0x%04x"
			enumType = " : ushort"
		end

		if lastCombinedIdx == -1 then
			yield("[Flags]")
			if idx ~= -1 then
				yield("public enum " .. combined[idx] .. enumType)
			else
				yield("public enum " .. typ.name .. enumType)
			end

			lastCombinedIdx = idx
			yield("{")
		end

		for _, flag in ipairs(typ.flag) do
			if flag.value then
				yield("\t"
					.. flag.name
					.. string.rep(" ", 22 - #(flag.name))
					.. " = "
					.. string.format(format, flag.value)
					.. ","
					)
			else
				yield("\t// Combined: "
					.. flag.name
					.. " = "
					.. table.concat(flag, " | ")
					)
			end
		end

		if lastCombinedIdx == -1 then
			yield("}")
		end
	end
end

function converter.funcs(func)
	yield("[DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]")

	if func.ret.cpptype == "bool" then
		yield("[return: MarshalAs(UnmanagedType:I1)]")
	end

	local first = ""
	local args  = "("

	for _, arg in ipairs(func.args) do

		local argtype = convert_type(arg)

		args = args .. first .. argtype .. " " .. arg.name
		first = ", "
	end

	yield("internal static extern unsafe " .. convert_type(func.ret) .. " bgfx_" .. func.cname .. args .. ");")
end

print(gen())

-- printtable("idl types", idl.types)
-- printtable("idl funcs", idl.funcs)
