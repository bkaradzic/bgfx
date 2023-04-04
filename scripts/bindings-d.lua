local codegen = require "codegen"
local idl = codegen.idl "bgfx.idl"

local template = [[
/+
+ ┌──────────────────────────────┐
+ │ AUTO GENERATED! DO NOT EDIT! │
+ └──────────────────────────────┘
+/
module bgfx;

import bindbc.bgfx.config;

import bindbc.common.types: va_list;

$version

$types
mixin(joinFnBinds((){
	string[][] ret;
	ret ~= makeFnBinds([
		$funcs
	]);
	return ret;
}()));

static if(!staticBinding):
import bindbc.loader;

mixin(makeDynloadFns("Bgfx", makeLibPaths(["bgfx", "bgfxRelease", "bgfxDebug"]), [__MODULE__]));
]]

local dKeywords = {"abstract", "alias", "align", "asm", "assert", "auto", "bool", "break", "byte", "case", "cast", "catch", "char", "class", "const", "continue", "dchar", "debug", "default", "delegate", "deprecated", "do", "double", "else", "enum", "export", "extern", "false", "final", "finally", "float", "for", "foreach", "foreach_reverse", "function", "goto", "if", "immutable", "import", "in", "inout", "int", "interface", "invariant", "is", "lazy", "long", "macro", "mixin", "module", "new", "nothrow", "null", "out", "override", "package", "pragma", "private", "protected", "public", "pure", "real", "ref", "return", "scope", "shared", "short", "static", "struct", "super", "switch", "synchronized", "template", "this", "throw", "true", "try", "typeid", "typeof", "ubyte", "uint", "ulong", "union", "unittest", "ushort", "version", "void", "wchar", "while", "with"}

local function contains(table, val)
	for i=1,#table do
		if table[i] == val then 
			return true
		end
	end
	return false
end

local function hasPrefix(str, prefix)
	return prefix == "" or str:sub(1, #prefix) == prefix
end

local function hasSuffix(str, suffix)
	return suffix == "" or str:sub(-#suffix) == suffix
end

local function toCamelCase(name)
	return (name:gsub("^([^%l]*)(%l?)", function(s0, s1)
		if s1 ~= nil then
			return s0:lower() .. s1
		end
		return s0:lower()
	end))
end

-- local function toPascalCase(name)
-- 	return (name:gsub("^%l", string.upper))
-- end

local usEnSubs = {["Color"] = "Colour", ["Rasterize"] = "Rasterise", ["Initialize"] = "Initialise"}
local function toIntlEn(name)
	local change = false
	for us, intl in pairs(usEnSubs) do
		if name:find(us) then
			name = (name:gsub(us, intl))
			change = true
		end
	end
	if change then
		return name
	else
		return nil
	end
end

local function hexStr(val, bits)
	local digits = bits / 4
	local str = string.format(string.format("%%0%iX", digits), val)
	local i = 4
	while i < str:len() do
		str = str:sub(0, i) .. "_" .. str:sub(i+1)
		i = i + 5
	end
	
	return "0x" .. str
end

local function convArray(member)
	if string.find(member.array, "::") then
		return string.gsub(member.array, "::.*", ".") .. toCamelCase(string.gsub(member.array, ".-::", ""))
	else
		return member.array
	end
end

local function convType(arg)
	local ctype = arg.ctype:gsub("%s%*", "*")
	if arg.fulltype == "bx::AllocatorI*" or arg.fulltype == "CallbackI*" then
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
		ctype = ctype:gsub("uint8_t", "ubyte")
	elseif hasPrefix(ctype, "int8_t") then
		ctype = ctype:gsub("int8_t", "byte")
	elseif hasPrefix(ctype, "uintptr_t") then
		ctype = ctype:gsub("uintptr_t", "size_t")
	elseif hasPrefix(ctype, "const ") and hasSuffix(ctype, "*") then
		ctype = "const(" .. string.sub(ctype:gsub("const ", "", 1), 1, -2) .. ")*"
	end
	
	if arg.array ~= nil then
		ctype = ctype .. convArray(arg)
	end
	
	return ctype
end

local function convStructType(arg)
	return convType(arg)
end

local function convName(arg)
	if contains(dKeywords, arg) then
		return arg .. "_"
	end
	return arg
end

local function convStructMember(member)
	return convStructType(member) .. " " .. convName(member.name)
end

local function genVersion()
	return "enum uint apiVersion = " .. (idl._version or 0) .. ";"
end

local converter = {}
local yield = coroutine.yield
local gen = {}

function gen.gen()
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
		
		if what == "version" then
			return genVersion()
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

function converter.types(typ)
	if typ.comments ~= nil then
		if #typ.comments == 1 then
			yield("///" .. typ.comments[1])
		else
			yield("/**")
			for _, comment in ipairs(typ.comments) do
				yield("* " .. comment)
			end
			yield("*/")
		end
	end
	
	if typ.handle then ---hnadle
		yield("struct " .. typ.name .. "{")
		yield("\tushort idx;")
		yield("}")
	
	elseif typ.enum then
		local typeName = typ.name:gsub("::Enum", "")
		yield("enum " .. typeName .. "{")
		for idx, enum in ipairs(typ.enum) do
			local comments = ""
			if enum.comment ~= nil then
				if #enum.comment == 1 then
					comments = " ///" .. enum.comment[1];
				else
					yield("\t/**")
					for _, comment in ipairs(enum.comment) do
						yield("\t* " .. comment)
					end
					yield("\t*/")
				end
			end
			local name = convName(toCamelCase(enum.name))
			yield("\t" .. name .. "," .. comments)
			
			local intlName = toIntlEn(enum.name)
			if intlName ~= nil then
				yield("\t" .. convName(toCamelCase(intlName)) .. " = " .. name .. ",")
			end
		end
		yield("\t");
		yield("\t" .. "count,")
		yield("}")
	
	elseif typ.bits ~= nil then
		local typeName = convName(typ.name)
		local enumType = "uint"
		if typ.bits == 64 then
			enumType = "ulong"
		elseif typ.bits == 32 then
			enumType = "uint"
		elseif typ.bits == 16 then
			enumType = "ushort"
		elseif typ.bits == 8 then
			enumType = "ubyte"
		end
		
		local maxLen = 0
		if typ.shift then
			maxLen = string.len("shift")
		elseif typ.range then
			maxLen = string.len("mask")
		end
		for _, flag in ipairs(typ.flag) do
			maxLen = math.max(maxLen, flag.name:len())
		end
		
		yield("alias " .. typeName .. "_ = " .. enumType .. ";")
		yield("enum " .. typeName .. ": " .. typeName .. "_{")
		for idx, flag in ipairs(typ.flag) do
			local value = flag.value
			if value ~= nil then
				value = hexStr(value, typ.bits)
			else
				for _, name in ipairs(flag) do
					local fixedName = convName(toCamelCase(name))
					if value ~= nil then
						value = value .. " | " .. fixedName
					else
						value = fixedName
					end
				end
			end
			
			local comments = ""
			if flag.comment ~= nil then
				if #flag.comment == 1 then
					comments = " ///" .. flag.comment[1]
				else
					yield("/**")
					for _, comment in ipairs(flag.comment) do
						yield("* " .. comment)
					end
					yield("*/")
				end
			end
			
			local name = convName(toCamelCase(flag.name))
			yield("\t" .. name .. string.rep(" ", maxLen+2 - name:len()) .. "= " .. value .. "," .. comments)
			
			local intlName = toIntlEn(flag.name)
			if intlName ~= nil then
				intlName = convName(toCamelCase(intlName))
				yield("\t" .. intlName .. string.rep(" ", maxLen+2 - intlName:len()) .. "= " .. name .. ",")
			end
		end
		
		if typ.shift then
			local name = convName("shift")
			local value = typ.shift
			local comments = ""
			if typ.desc then
				comments = string.format(" ///%s bit shift", typ.desc)
			end
			yield("\t" .. name .. string.rep(" ", maxLen+2 - name:len()) .. "= " .. value .. "," .. comments)
		end
		if typ.range then
			local name = convName("mask")
			local value = hexStr(typ.mask, typ.bits)
			local comments = ""
			if typ.desc then
				comments = string.format(" ///%s bit mask", typ.desc)
			end
			yield("\t" .. name .. string.rep(" ", maxLen+2 - name:len()) .. "= " .. value .. "," .. comments)
		end
		yield("}")
		
		local intlName = toIntlEn(typeName)
		if intlName ~= nil then
			yield("alias " .. intlName .. " = " .. typeName .. ";")
		end
		
		if typ.helper then
			yield(string.format(
				"%s_ to%s(%s v){ return (v << %s) & %s; }",
				typeName,
				typeName,
				enumType,
				("shift"),
				("mask")))
			if intlName ~= nil then
				yield("alias to" .. intlName .. " = to" .. typeName .. ";")
			end
		end
	elseif typ.struct ~= nil then
		yield("struct " .. typ.name .. "{")
		
		for _, member in ipairs(typ.struct) do
			local comments = ""
			if member.comment ~= nil then
				if #member.comment == 1 then
					comments = " ///" .. member.comment[1]
				else
					yield("\n\t/**")
					for _, comment in ipairs(member.comment) do
						yield("\t* " .. comment)
					end
					yield("\t*/")
				end
			end
			yield("\t" .. convStructMember(member) .. ";" .. comments)
		end
		
		yield("}")
	end
end

function converter.funcs_static(func)
	return converter.funcs(func)
end

function converter.funcs_dynamic(func)
	return converter.funcs(func)
end

function converter.funcs(func)
	if func.comments ~= nil then
		yield("/**")
		for _, line in ipairs(func.comments) do
			local line = line:gsub("@remarks", "Remarks:")
			line = line:gsub("@remark", "Remarks:")
			line = line:gsub("@(%l)(%l+)", function(a, b) return a:upper() .. b .. ":" end)
			yield("* " .. line)
		end
		
		local hasParamsComments = false
		for _, arg in ipairs(func.args) do
			if arg.comment ~= nil then
				hasParamsComments = true
				break
			end
		end
		
		if hasParamsComments then
			yield("* Params:")
		end
		
		for _, arg in ipairs(func.args) do
			if arg.comment ~= nil then
				yield("* " .. convName(arg.name) .. " = " .. arg.comment[1])
				for i, comment in ipairs(arg.comment) do
					if i > 1 then
						yield("* " .. comment)
					end
				end
			end
		end
		
		yield("*/")
	end
	
	local args = {}
	-- if func.this ~= nil then
		-- args[1] = convType(func.this_type) .. " _this"
	-- end
	for _, arg in ipairs(func.args) do
		table.insert(args, convType(arg) .. " " .. convName(arg.name))
	end
	
	yield(string.format("[q{%s}, q{%s}, q{%s}, `%s`],", convType(func.ret), func.name, table.concat(args, ", "), "C++"))
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
	print(gen.gen(dTemplate))
end

return gen
