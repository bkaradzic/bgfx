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
$structs
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
	if name:find("%u%u+%l") then
		return name:gsub("(%u-)(%u%l)", function(s0, s1)
			return s0:lower() .. s1
		end)
	end
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

local function convArray(array)
	if string.find(array, "::") then
		return string.gsub(array, "::.*", ".") .. toCamelCase(string.gsub(array, ".-::", ""))
	else
		return array
	end
end

local typeSubs = {
	uint32_t  = "uint",   int32_t = "int",
	uint16_t  = "ushort", int16_t = "short",
	uint64_t  = "ulong",  int64_t = "long",
	uint8_t   = "ubyte",  int8_t  = "byte",
	uintptr_t = "size_t"
}
local function convSomeType(arg, isFnArg)
	local type = arg.fulltype
	if type == "bx::AllocatorI*" or type == "CallbackI*" then
		type = "void*"
	else
		for from, to in pairs(typeSubs) do
			if type:find(from) then
				type = type:gsub(from, to)
				break
			end
		end
		type = type:gsub("::Enum", "") --fix enums
		type = type:gsub("%s+%*", "*") --remove spacing before `*`
		type = type:gsub("([^&]-)%s?&", "ref %1") --change `&` suffix to `ref` prefix
		--if isFnArg then --(not needed at this point)
		--	type = type:gsub("%[[^%]]+%]", "*") --change `[n]` to `*`
		--end
		type = type:gsub("const%s+([A-Za-z_][A-Za-z0-9_]*)%*", "const(%1)*") --change `const x*` to `const(x)*`
	end
	
	if arg.array ~= nil then
		type = type .. convArray(arg.array)
	end
	
	return type
end

local function convType(arg)
	return convSomeType(arg, false)
end

local function convFnArgType(arg)
	return convSomeType(arg, true)
end

local valSubs = {
	NULL = "null",
	UINT16_MAX = "ushort.max",
	UINT32_MAX = "uint.max",
	
	BGFX_INVALID_HANDLE = "invalidHandle",
	
	BGFX_DISCARD_ALL = "Discard.all",
	BGFX_BUFFER_NONE = "Buffer.none",
	BGFX_STENCIL_NONE = "Stencil.none",
	BGFX_TEXTURE_NONE = "Texture.none",
	BGFX_SAMPLER_NONE = "Sampler.none",
	BGFX_SAMPLER_U_CLAMP = "Sampler.uClamp",
	BGFX_SAMPLER_V_CLAMP = "Sampler.vClamp",
	BGFX_RESOLVE_AUTO_GEN_MIPS = "Resolve.autoGenMips",
}
local function convVal(arg)
	local val = string.format("%s", arg)
	
	for from, to in pairs(valSubs) do
		if val:find(from) then
			val = val:gsub(from, to)
		end
	end
	val = convArray(val)
	
	return val
end

local function convStructType(arg)
	return convType(arg)
end

local function convName(name)
	if contains(dKeywords, name) then
		return name .. "_"
	end
	return name
end

local function convStructMember(member)
	return convStructType(member) .. " " .. convName(member.name)
end

local allStructs = {}

local function genVersion()
	return "enum uint apiVersion = " .. (idl._version or 0) .. ";"
end

local function genStructMemberFn(func) --NOTE: this does not work on nested structs
	if func.class ~= nil then
		local st = allStructs[func.class]
		if func.comments ~= nil then
			if #st.fns > 0 then
				table.insert(st.fns, "")
			end
			table.insert(st.fns, "/**")
			for _, line in ipairs(func.comments) do
				local line = line:gsub("@remarks", "Remarks:")
				line = line:gsub("@remark", "Remarks:")
				line = line:gsub("@(%l)(%l+)", function(a, b) return a:upper() .. b .. ":" end)
				table.insert(st.fns, line)
			end
			
			local hasParamsComments = false
			for _, arg in ipairs(func.args) do
				if arg.comment ~= nil then
					hasParamsComments = true
					break
				end
			end
			
			if hasParamsComments then
				table.insert(st.fns, "Params:")
			end
			
			for _, arg in ipairs(func.args) do
				if arg.comment ~= nil then
					table.insert(st.fns, "\t" .. convName(arg.name:sub(2)) .. " = " .. arg.comment[1])
					for i, comment in ipairs(arg.comment) do
						if i > 1 then
							table.insert(st.fns, comment)
						end
					end
				end
			end
			
			table.insert(st.fns, "*/")
		end
		
		local args = {}
		for _, arg in ipairs(func.args) do
			local def = ""
			if arg.default ~= nil then
				def = string.format("=%s", convVal(arg.default))
			end
			table.insert(args, convFnArgType(arg) .. " " .. convName(arg.name:sub(2)) .. def)
		end
		
		table.insert(st.fns, string.format("[q{%s}, q{%s}, q{%s}, `%s`],", convType(func.ret), func.name, table.concat(args, ", "), "C++"))
	end
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
		
		if what == "version" then
			return genVersion()
		elseif what == "structs" then
			for _, fn in ipairs(idl.funcs) do
				genStructMemberFn(fn)
			end
			for name, object in pairs(allStructs) do
				local co = coroutine.create(converter[what])
				local any
				while true do
					local ok, v = coroutine.resume(co, object, name, indent:len())
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
		else
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
		end
		return table.concat(tmp, "\n" .. indent)
	end)
	return r
end

function converter.structs(st, name)
	for _, line in ipairs(st.comments) do
		yield(line)
	end
	
	yield("struct " .. name .. "{")
	
	local subN = 0
	for subName, subStruct in pairs(st.subs) do
		subN = subN + 1
		local co = coroutine.create(converter.structs)
		while true do
			local ok, v = coroutine.resume(co, subStruct, subName)
			assert(ok, debug.traceback(co, v))
			if not v then
				break
			end
			yield("\t" .. v)
		end
	end
	if subN > 0 then
		yield("\t")
	end
	
	for _, line in ipairs(st.fields) do
		yield(line)
	end
	
	if #st.fns > 0 then
		yield("\tmixin(joinFnBinds((){")
		yield("\t\tstring[][] ret;")
		yield("\t\tret ~= makeFnBinds([")
		for _, line in ipairs(st.fns) do
			yield("\t\t\t" .. line)
		end
		yield("\t\t]);")
		yield("\t\treturn ret;")
		yield("\t}())););")
	end
	
	yield("}")
end

function converter.types(typ)
	if typ.comments ~= nil and not typ.struct then
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
		yield(typ.name .. " invalidHandle(){ return " .. typ.name .. "(ushort.max); }")
	
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
						yield("\t" .. comment)
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
						yield(comment)
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
		local st = {comments = {}, fields = {}, fns = {}, subs = {}}
		
		if typ.comments ~= nil then
			if #typ.comments == 1 then
				table.insert(st.comments, "///" .. typ.comments[1])
			else
				table.insert(st.comments, "/**")
				for _, comment in ipairs(typ.comments) do
					table.insert(st.comments, comment)
				end
				table.insert(st.comments, "*/")
			end
		end
		
		for _, member in ipairs(typ.struct) do
			local comments = ""
			if member.comment ~= nil then
				if #member.comment == 1 then
					comments = " ///" .. member.comment[1]
				else
					if #st.fields > 0 then
						table.insert(st.fields, "\t")
					end
					table.insert(st.fields, "\t/**")
					for _, comment in ipairs(member.comment) do
						table.insert(st.fields, "\t" .. comment)
					end
					table.insert(st.fields, "\t*/")
				end
			end
			table.insert(st.fields, "\t" .. convStructMember(member) .. ";" .. comments)
		end
		
		if typ.namespace ~= nil then
			if allStructs[typ.namespace] ~= nil then
				allStructs[typ.namespace].subs[typ.name] = st
			else
				allStructs[typ.namespace] = {subs = {[typ.name] = st}}
			end
		else
			if allStructs[typ.name] ~= nil then
				st.subs = allStructs[typ.name].subs
			end
			allStructs[typ.name] = st
		end
	end
end

function converter.funcs(func)
	if func.class == nil then
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
				yield("Params:")
			end
			
			for _, arg in ipairs(func.args) do
				if arg.comment ~= nil then
					yield("\t" .. convName(arg.name:sub(2)) .. " = " .. arg.comment[1])
					for i, comment in ipairs(arg.comment) do
						if i > 1 then
							yield(comment)
						end
					end
				end
			end
			
			yield("*/")
		end
		
		local args = {}
		for _, arg in ipairs(func.args) do
			local def = ""
			if arg.default ~= nil then
				def = string.format("=%s", convVal(arg.default))
			end
			table.insert(args, convFnArgType(arg) .. " " .. convName(arg.name:sub(2)) .. def)
		end
		
		yield(string.format("[q{%s}, q{%s}, q{%s}, `%s`],", convType(func.ret), func.name, table.concat(args, ", "), "C++"))
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
	print(gen.gen(dTemplate))
end

return gen
