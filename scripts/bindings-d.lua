local codegen = require "codegen"
local idl = codegen.idl "bgfx.idl"

local d_types_template = [[
/*
 *
 * AUTO GENERATED! DO NOT EDIT!
 *
 */

module bindbc.bgfx.types;

public import core.stdc.stdarg : va_list;

extern(C) @nogc nothrow:

$version

alias bgfx_view_id_t = ushort;

$types
]]

local d_funcs_template = [[
/*
 *
 * AUTO GENERATED! DO NOT EDIT!
 *
 */

module bindbc.bgfx.funcs;

private import bindbc.bgfx.types;

extern(C) @nogc nothrow:

version(BindBgfx_Static)
{
	$funcs_static
}
else
{
	__gshared
	{
		$funcs_dynamic
	}
}
]]

local function hasPrefix(str, prefix)
	return prefix == "" or str:sub(1, #prefix) == prefix
end

local function hasSuffix(str, suffix)
	return suffix == "" or str:sub(-#suffix) == suffix
end

local function to_underscorecase(name)
	local tmp = {}
	for v in name:gmatch "[_%u][%l%d]*" do
		if v:byte() == 95 then	-- '_'
			v = v:sub(2)	-- remove _
		end
		tmp[#tmp+1] = v
	end
	return table.concat(tmp, "_")
end

local function convert_array(member)
	if string.find(member.array, "::") then
		local name = "bgfx_" .. to_underscorecase(string.gsub(member.array, "::.*", "")):lower() .. "_t"
		return "[" .. name .. ".BGFX_" .. to_underscorecase(member.array):upper() .. "]"
	else
		return member.array
	end
end

local function convert_type(arg)
	local ctype = arg.ctype:gsub("%s%*", "*")
	if arg.fulltype == "bx::AllocatorI*" or arg.fulltype == "CallbackI*" or arg.fulltype == "ReleaseFn" then
		ctype = "void*"
	elseif hasPrefix(ctype, "uint64_t") then
		ctype = ctype:gsub("uint64_t", "ulong")
	elseif hasPrefix(ctype, "int64_t") then
		ctype = ctype:gsub("int64_t", "long")
	elseif hasPrefix(ctype, "uint32_t") then
		ctype = ctype:gsub("uint32_t", "uint")
	elseif hasPrefix(ctype, "int32_t") then
		ctype = ctype:gsub("int32_t", "int")
	elseif hasPrefix(ctype, "uint16_t") then
		ctype = ctype:gsub("uint16_t", "ushort")
	elseif hasPrefix(ctype, "uint8_t") then
		ctype = ctype:gsub("uint8_t", "byte")
	elseif hasPrefix(ctype, "uintptr_t") then
		ctype = ctype:gsub("uintptr_t", "ulong")
	elseif hasPrefix(ctype, "const ") and hasSuffix(ctype, "*") then
		ctype = "const(" .. string.sub(ctype:gsub("const ", "", 1), 1, -2) .. ")*"
	end

	if arg.array ~= nil then
		ctype = ctype .. convert_array(arg)
	end

	return ctype
end

local function convert_struct_type(arg)
	return convert_type(arg)
end

local function convert_ret_type(arg)
	return convert_type(arg)
end

local function convert_name(arg)
	if arg == "debug" then
		return arg .. "_"
	end
	return arg
end

local function convert_struct_member(member)
	return convert_struct_type(member) .. " " .. convert_name(member.name)
end

local function gen_version()
	return "enum uint BGFX_API_VERSION = " .. (idl._version or 0) .. ";"
end

local converter = {}
local yield = coroutine.yield
local gen = {}

function gen.gen(template)
	local indent = ""
	local idx = 1;
	local r = template:gsub("$([a-zA-Z_]+)", function(what)
		local tmp = {}

		local ind_end = template:find("$"..what, idx, true)
		local ind_start = ind_end
		for j = 1, ind_end-1 do
			local i = 1+ind_end-1-j
			local c = string.sub(template, i, i)
			if c ~= ' ' and c ~= '\t' then
				ind_start = i
				break
			end
		end

		indent = string.sub(template, ind_start+1, ind_end-1)

		local what_idl = what:gsub("funcs_dynamic", "funcs"):gsub("funcs_static", "funcs")

		if (what == "version") then
			return gen_version()
		end

		for _, object in ipairs(idl[what_idl]) do
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
		return table.concat(tmp, "\n" .. indent)
	end)
	return r
end

function gen.gen_types()
	return gen.gen(d_types_template)
end

function gen.gen_funcs()
	return gen.gen(d_funcs_template)
end

function converter.types(typ)
	if typ.comments ~= nil then
		if #typ.comments == 1 then
			yield("/// " .. typ.comments[1])
		else
			yield("/**")
			for _, comment in ipairs(typ.comments) do
				yield(" * " .. comment)
			end
			yield(" */")
		end
	end

	if typ.handle then
		yield("struct " .. typ.cname .. " { ushort idx; }")
	elseif typ.enum then
		local prefix = "BGFX_" .. to_underscorecase(string.gsub(typ.name, "::Enum", "")):upper()
		yield("enum " .. typ.cname)
		yield("{")
		for idx, enum in ipairs(typ.enum) do
			local comments = ""
			if enum.comment ~= nil then
				if #enum.comment == 1 then
					comments = " /// " .. enum.comment[1];
				else
					yield("\t/**")
					for _, comment in ipairs(enum.comment) do
						yield("\t * " .. comment)
					end
					yield("\t */")
				end
			end

			local enumname
			if enum.underscore then
				enumname = to_underscorecase(enum.name):upper()
			else
				enumname = enum.name:upper()
			end

			yield("\t" .. prefix .. "_" .. enumname .. "," .. comments)
		end
		yield("");
		--yield("\t" .. prefix .. "_COUNT = " .. #typ.enum)
		yield("\t" .. prefix .. "_COUNT")
		yield("}")

	elseif typ.bits ~= nil then
		local prefix = "BGFX_" .. to_underscorecase(typ.name):upper()
		local enumType = "uint"
		format = "%u"
		if typ.bits == 64 then
			format = "0x%016x"
			enumType = "ulong"
		elseif typ.bits == 32 then
			format = "0x%08x"
			enumType = "uint"
		elseif typ.bits == 16 then
			format = "0x%04x"
			enumType = "ushort"
		elseif typ.bits == 8 then
			format = "0x%02x"
			enumType = "ubyte"
		end

		for idx, flag in ipairs(typ.flag) do
			local value = flag.value
			if value ~= nil then
				value = string.format(flag.format or format, value)
			else
				for _, name in ipairs(flag) do
					local fixedname = prefix .. "_" .. to_underscorecase(name):upper()
					if value ~= nil then
						value = value .. " | " .. fixedname
					else
						value = fixedname
					end
				end
			end
			local comments = ""
			if flag.comment ~= nil then
				if #flag.comment == 1 then
					comments = " /// " .. flag.comment[1]
				else
					yield("/**")
					for _, comment in ipairs(flag.comment) do
						yield(" * " .. comment)
					end
					yield(" */")
				end
			end
			yield("enum " .. enumType .. " " .. prefix .. "_" .. to_underscorecase(flag.name):upper() .. " = " .. value .. ";" .. comments)
		end

		if typ.shift then
			local name = prefix .. "_SHIFT"
			local value = typ.shift
			local comments = ""
			if typ.desc then
				comments = string.format(" /// %s bit shift", typ.desc)
			end
			yield("enum " .. enumType .. " " .. name .. " = " .. value .. ";" .. comments)
		end
		if typ.range then
			local name = prefix .. "_MASK"
			local value = string.format(format, typ.mask)
			local comments = ""
			if typ.desc then
				comments = string.format(" /// %s bit mask", typ.desc)
			end
			yield("enum " .. enumType .. " " .. name .. " = " .. value .. ";" .. comments)
		end

		if typ.helper then
			yield(string.format(
				"%s %s (%s v) { return (v << %s) & %s; }",
				enumType,
				prefix,
				enumType,
				(prefix .. "_SHIFT"),
				(prefix .. "_MASK")))
		end
	elseif typ.struct ~= nil then
		yield("struct " .. typ.cname)
		yield("{")

		for _, member in ipairs(typ.struct) do
			local comments = ""
			if member.comment ~= nil then
				if #member.comment == 1 then
					comments = " /// " .. member.comment[1]
				else
					yield("\n\t/**")
					for _, comment in ipairs(member.comment) do
						yield("\t * " .. comment)
					end
					yield("\t */")
				end
			end
			yield("\t" .. convert_struct_member(member) .. ";" .. comments)
		end

		yield("}")
	end
end

function converter.funcs_static(func)
	return converter.funcs(func, true)
end

function converter.funcs_dynamic(func)
	return converter.funcs(func, false)
end

function converter.funcs(func, static)
	if func.cpponly then
		return
	end

	if func.comments ~= nil then
		yield("/**")
		for _, line in ipairs(func.comments) do
			local line = line:gsub("@remarks", "Remarks:")
			line = line:gsub("@remark", "Remarks:")
			line = line:gsub("@(%l)(%l+)", function(a, b) return a:upper()..b..":" end)
			yield(" * " .. line)
		end

		local hasParamsComments = false
		for _, arg in ipairs(func.args) do
			if arg.comment ~= nil then
				hasParamsComments = true
				break
			end
		end

		if hasParamsComments then
			yield(" * Params:")
		end

		for _, arg in ipairs(func.args) do
			if arg.comment ~= nil then
				yield(" * " .. convert_name(arg.name) .. " = " .. arg.comment[1])
				for i, comment in ipairs(arg.comment) do
					if (i > 1) then
						yield(" * " .. comment)
					end
				end
			end
		end

		yield(" */")
	end

	local args = {}
	if func.this ~= nil then
		args[1] = convert_type(func.this_type) .. " _this"
	end
	for _, arg in ipairs(func.args) do
		table.insert(args, convert_type(arg) .. " " .. convert_name(arg.name))
	end

	if static then
		yield(convert_ret_type(func.ret) .. " bgfx_" .. func.cname .. "(" .. table.concat(args, ", ") .. ");")
	else
		yield("alias da_bgfx_" .. func.cname .. " = " .. convert_ret_type(func.ret) .. " function(" .. table.concat(args, ", ") .. ");")
		yield("da_bgfx_" .. func.cname .. " bgfx_" .. func.cname .. ";")
	end
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
	-- run `lua bindings-d.lua` in command line
	print(gen.gen_types())
	print(gen.gen_funcs())
end

return gen
