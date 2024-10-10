local codegen = require "codegen"
local idl = codegen.idl "bgfx.idl"

local template = [[
/+
+ ┌==============================┐
+ │ AUTO GENERATED! DO NOT EDIT! │
+ └==============================┘
+/
module bgfx;

import bindbc.bgfx.config;

import bindbc.common.types: c_int64, c_uint64, va_list;
static import bgfx.fakeenum;

$version

alias ViewID = ushort;

enum invalidHandle(T) = T(ushort.max);

alias ReleaseFn = void function(void* ptr, void* userData);

$types
pragma(inline,true) nothrow @nogc pure @safe{
	StateBlend_ blendFuncSeparate(StateBlend_ srcRGB, StateBlend_ dstRGB, StateBlend_ srcA, StateBlend_ dstA){
		return (srcRGB | ((dstRGB) << 4)) | ((srcA | (dstA << 4)) << 8);
	}
	
	///Blend equation separate.
	StateBlendEquation_ blendEquationSeparate(StateBlendEquation_ equationRGB, StateBlendEquation_ equationA){
		return equationRGB | (equationA << 3);
	}
	
	///Blend function.
	StateBlend_ blendFunc(StateBlend_ src, StateBlend_ dst){ return blendFuncSeparate(src, dst, src, dst); }
	
	///Blend equation.
	StateBlendEquation_ blendEquation(StateBlendEquation_ equation){ return blendEquationSeparate(equation, equation); }
	
	///Utility predefined blend modes.
	enum StateBlendFunc: StateBlend_{
		///Additive blending.
		add = blendFunc(StateBlend.one, StateBlend.one),
		
		///Alpha blend.
		alpha = blendFunc(StateBlend.srcAlpha, StateBlend.invSrcAlpha),
		
		///Selects darker color of blend.
		darken = blendFunc(StateBlend.one, StateBlend.one) | blendEquation(StateBlendEquation.min),
		
		///Selects lighter color of blend.
		lighten = blendFunc(StateBlend.one, StateBlend.one) | blendEquation(StateBlendEquation.max),
		
		///Multiplies colors.
		multiply = blendFunc(StateBlend.dstColor, StateBlend.zero),
		
		///Opaque pixels will cover the pixels directly below them without any math or algorithm applied to them.
		normal = blendFunc(StateBlend.one, StateBlend.invSrcAlpha),
		
		///Multiplies the inverse of the blend and base colors.
		screen = blendFunc(StateBlend.one, StateBlend.invSrcColor),
		
		///Decreases the brightness of the base color based on the value of the blend color.
		linearBurn = blendFunc(StateBlend.dstColor, StateBlend.invDstColor) | blendEquation(StateBlendEquation.sub),
	}
	
	StateBlend_ blendFuncRTx(StateBlend_ src, StateBlend_ dst){
		return cast(uint)(src >> StateBlend.shift) | (cast(uint)(dst >> StateBlend.shift) << 4);
	}
	
	StateBlend_ blendFuncRTxE(StateBlend_ src, StateBlend_ dst, StateBlendEquation_ equation){
		return blendFuncRTx(src, dst) | (cast(uint)(equation >> StateBlendEquation.shift) << 8);
	}
	
	StateBlend_ blendFuncRT1(StateBlend_ src, StateBlend_ dst){ return blendFuncRTx(src, dst) <<  0; }
	StateBlend_ blendFuncRT2(StateBlend_ src, StateBlend_ dst){ return blendFuncRTx(src, dst) << 11; }
	StateBlend_ blendFuncRT3(StateBlend_ src, StateBlend_ dst){ return blendFuncRTx(src, dst) << 22; }
	
	StateBlend_ blendFuncRT1E(StateBlend_ src, StateBlend_ dst, StateBlendEquation_ equation){
		return blendFuncRTxE(src, dst, equation) <<  0;
	}
	StateBlend_ blendFuncRT2E(StateBlend_ src, StateBlend_ dst, StateBlendEquation_ equation){
		return blendFuncRTxE(src, dst, equation) << 11;
	}
	StateBlend_ blendFuncRT3E(StateBlend_ src, StateBlend_ dst, StateBlendEquation_ equation){
		return blendFuncRTxE(src, dst, equation) << 22;
	}
}

$structs
mixin(joinFnBinds((){
	FnBind[] ret = [
		$funcs
	];
	return ret;
}(), $membersWithFns));

static if(!staticBinding):
import bindbc.loader;

debug{
	mixin(makeDynloadFns("Bgfx", makeLibPaths(["bgfx-shared-libDebug", "bgfxDebug", "bgfx"]), [__MODULE__]));
}else{
	mixin(makeDynloadFns("Bgfx", makeLibPaths(["bgfx-shared-libRelease", "bgfxRelease", "bgfx"]), [__MODULE__]));
}
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

local enumTypes = {}
local membersWithFns = ""

local capsWords = {"Mip", "Id", "Rw", "Vb", "Ib", "Cb", "Rt", "Pci", "Srgb", "Pt", "Ccw", "2d", "3d", "Msaa"}
local capsRepl = {
	hidpi = "hiDPI", lineaa = "lineAA", maxanisotropy = "maxAnisotropy",
	notequal = "notEqual", gequal = "gEqual", Lequal = "LEqual", lequal = "lEqual",
	decrsat = "decrSat", incrsat = "incrSat", revsub = "revSub",
	linestrip = "lineStrip", tristrip = "triStrip",
	bstencil = "bStencil", fstencil = "fStencil",
	Rmask = "RMask",
}

local function abbrevsToUpper(name)
	if name:len() >= 3 then
		for _, abbrev in pairs(capsWords) do
			name = name:gsub(abbrev, function(s0)
				return s0:upper()
			end)
		end
		for from, to in pairs(capsRepl) do
			name =  name:gsub(from, to)
		end
	end
	return name
end

local function toCamelCase(name)
	if name:len() >= 3 then
		name = name:sub(0, 1) .. name:sub(2, -2):gsub("_", "") .. name:sub(-1)
	end
	if name:find("%u%u+%l") then
		name = name:gsub("(%u-)(%u%l)", function(s0, s1)
			return s0:lower() .. s1
		end)
	else
		name = (name:gsub("^([^%l]*)(%l?)", function(s0, s1)
			if s1 ~= nil then
				return s0:lower() .. s1
			end
			return s0:lower()
		end))
	end
	return abbrevsToUpper(name)
end

-- local function toPascalCase(name)
-- 	return (name:gsub("^%l", string.upper))
-- end

local usEnSubs = {
	color = "colour", Color = "Colour",
	rasterize = "rasterise", Rasterize = "Rasterise",
	initialize = "initialise", Initialize = "Initialise",
	normalize = "normalise", Normalize = "Normalise",
	normalized = "normalised", Normalized = "Normalised",
	ccw = "acw", CCW = "ACW",
}
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

-- Unconditionally convert
local function toIntlEnUncond(name)
	local newName = toIntlEn(name)
	if newName ~= nil then
		return newName
	end
	return name
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
	{"uint32_t",  "uint"},     {"int32_t", "int"},
	{"uint16_t",  "ushort"},   {"int16_t", "short"},
	{"uint64_t",  "c_uint64"}, {"int64_t", "c_int64"},
	{"uint8_t",   "ubyte"},    {"int8_t",  "byte"},
	{"uintptr_t", "size_t"}
}
local function convSomeType(arg, isFnArg)
	local type = arg.fulltype
	if type == "bx::AllocatorI*" or type == "CallbackI*" then
		type = "void*"
	else
		for _, item in ipairs(typeSubs) do
			if type:find(item[1]) then
				type = type:gsub(item[1], item[2])
				break
			end
		end
		type = type:gsub("::Enum", "") --fix enums
		type = type:gsub("%s+%*", "*") --remove spacing before `*`

		if isFnArg then
			for _, enum in pairs(enumTypes) do --fix C++ linkage errors
				if type == enum then
					type = string.format("bgfx.fakeenum.%s.Enum", enum)
				else
					type = (type:gsub("(" .. enum .. ")([^A-Za-z0-9_])", function(s0, s1)
						return string.format("bgfx.fakeenum.%s.Enum", enum) .. s1
					end))
				end
			end
			type = type:gsub("([^&]-)%s?&", "ref %1") --change `&` suffix to `ref` prefix
			if arg.array ~= nil then
				type = type .. "*" --append *
			end
		else
			type = type:gsub("([^&]-)%s?&", "%1*") --change `&` to `*`
			if arg.array ~= nil then
				type = type .. convArray(arg.array) --append [n]
			end
		end
		type = type:gsub("const%s+([A-Za-z_][A-Za-z0-9_]*)%s*%*", "const(%1)*") --change `const x*` to `const(x)*`
		type = abbrevsToUpper(type)
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
	UINT8_MAX = "ubyte.max",
	UINT16_MAX = "ushort.max",
	UINT32_MAX = "uint.max",
	
	BGFX_INVALID_HANDLE = "invalidHandle",
	
	BGFX_DISCARD_ALL = "Discard.all",
	BGFX_BUFFER_NONE = "Buffer.none",
	BGFX_STENCIL_NONE = "Stencil.none",
	BGFX_TEXTURE_NONE = "Texture.none",
	BGFX_SAMPLER_NONE = "Sampler.none",
	BGFX_RESET_NONE = "Reset.none",
	BGFX_SAMPLER_U_CLAMP = "SamplerU.clamp",
	BGFX_SAMPLER_V_CLAMP = "SamplerV.clamp",
	BGFX_RESOLVE_AUTO_GEN_MIPS = "Resolve.autoGenMIPs",
	["ViewMode::Default"] = "ViewMode.default_",
}
local function convVal(arg, type)
	local val = string.format("%s", arg)
	for from, to in pairs(valSubs) do
		if val:find(from) then
			if from == "BGFX_INVALID_HANDLE" then
				val = val:gsub(from, to .. "!" .. type)
			else
				val = val:gsub(from, to)
			end
		end
	end
	if val:find("INT32_MAX") then
		val = val:gsub("INT32_MAX", "int.max")
	end
	val = convArray(val)
	
	return val
end

local function convStructType(arg)
	return convType(arg)
end

local function convName(name)
	name = abbrevsToUpper(name)
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
	if func.class ~= nil and func.conly == nil and func.cppinline == nil then
		local st = allStructs[func.class]
		local attribs = ""
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
					table.insert(st.fns, "\t" .. toIntlEnUncond(convName(arg.name:sub(2))) .. " = " .. arg.comment[1])
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
				def = string.format("=%s", convVal(arg.default, convFnArgType(arg)))
			end
			if arg.fulltype == "..." then
				table.insert(args, "..." .. def)
			else
				table.insert(args, convFnArgType(arg) .. " " .. toIntlEnUncond(convName(arg.name:sub(2))) .. def)
			end
		end
		
		if func.const ~= nil then
			attribs = "const"
		end
		if attribs ~= "" then
			attribs = ", memAttr: q{" .. attribs .. "}"
		end
		
		table.insert(st.fns, string.format("{q{%s}, q{%s}, q{%s}, ext: `C++`%s},", convType(func.ret), func.name, table.concat(args, ", "), attribs))
	end
end

local converter = {}
local yield = coroutine.yield
local gen = {}

gen.fakeEnumFile = [[
/+
+ ┌==============================┐
+ │ AUTO GENERATED! DO NOT EDIT! │
+ └==============================┘
+/
module bgfx.fakeenum;

//NOTE: Do NOT use this module! Use the enums with the same names in `bgfx/package.d` instead.
package:
]]

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
			for _, object in ipairs(idl["types"]) do
				if object.struct ~= nil and object.namespace == nil then
					local co = coroutine.create(converter[what])
					local any
					while true do
						local ok, v = coroutine.resume(co, allStructs[object.name], object.name, true, indent:len())
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
		elseif what == "membersWithFns" then
			table.insert(tmp, "\"" .. membersWithFns .. "\"")
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

function converter.structs(st, name, topLvl)
	for _, line in ipairs(st.comments) do
		yield(line)
	end
	
	if topLvl then
		yield("extern(C++, \"bgfx\") struct " .. name .. "{")
	else
		yield("extern(C++) struct " .. name .. "{")
	end
	
	local subN = 0
	for _, subStruct in ipairs(st.subs) do
		subN = subN + 1
		local co = coroutine.create(converter.structs)
		while true do
			local ok, v = coroutine.resume(co, subStruct, subStruct.name, false)
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
		membersWithFns = membersWithFns .. name .. ", "
		yield("\textern(D) mixin(joinFnBinds((){")
		yield("\t\tFnBind[] ret = [")
		for _, line in ipairs(st.fns) do
			yield("\t\t\t" .. line)
		end
		yield("\t\t];")
		yield("\t\treturn ret;")
		yield("\t}()));")
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
				yield(comment)
			end
			yield("*/")
		end
	end
	
	if typ.handle then ---hnadle
		yield("extern(C++, \"bgfx\") struct " .. typ.name .. "{")
		yield("\tushort idx;")
		yield("}")
		--yield(typ.name .. " invalidHandle(){ return " .. typ.name .. "(ushort.max); }")
	
	-- For some reason, this has never worked, so I'm commenting it out just in case it does start working suddenly. :P
	--[[
	elseif typ.funcptr then
		local args = {}
		for _, arg in ipairs(typ.args) do
			if arg.fulltype == "..." then
				table.insert(args, "..." .. def)
			else
				table.insert(args, convFnArgType(arg) .. " " .. convName(arg.name:sub(2)) .. def)
			end
		end
		
		yield(string.format("alias %s = extern(C++) %s function(%s);", typ.name, convType(typ.ret), table.concat(args, ", ")))
	--]]
	elseif typ.enum then
		local typeName = abbrevsToUpper(typ.name:gsub("::Enum", ""))
		local otherName = string.format("bgfx.fakeenum.%s.Enum", typ.name:gsub("::Enum", ""))
		
		yield("enum " .. typeName .. ": " .. otherName .. "{")
		table.insert(enumTypes, typeName)
		
		local vals = ""
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
			yield("\t" .. name .. " = " .. otherName .. "." .. name .. ",")
			vals = vals .. name .. ","
			
			local intlName = toIntlEn(enum.name)
			if intlName ~= nil then
				yield("\t" .. convName(toCamelCase(intlName)) .. " = " .. otherName .. "." .. name .. ",")
			end
		end
		
		gen.fakeEnumFile = gen.fakeEnumFile .. string.format([[
extern(C++, "bgfx") package final abstract class %s{
	enum Enum{
		%scount
	}
}
]], typeName, vals)
		
		yield("\t" .. "count = " .. otherName .. ".count,")
		yield("}")
		
	elseif typ.bits ~= nil then
		local typeName = convName(typ.name)
		if typeName == "Caps" then
			typeName = "CapFlags"
		end
		
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
		
		local function getValOr(name)
			local t = typeName
			if typeName == "State" then
				if hasPrefix(name, "Write") then
					t = t .. name:sub(1, 5)
					name = name:sub(6)
				elseif hasPrefix(name, "DepthTest") then
					t = t .. name:sub(1, 9)
					name = name:sub(10)
				elseif hasPrefix(name, "Cull") then
					t = t .. name:sub(1, 4)
					name = name:sub(5)
				end
			elseif typeName == "Sampler" then
				if hasPrefix(name, "Min") then
					t = t .. name:sub(1, 3)
					name = name:sub(4)
				elseif hasPrefix(name, "Mag") then
					t = t .. name:sub(1, 3)
					name = name:sub(4)
				elseif hasPrefix(name, "Mip") then
					t = t .. name:sub(1, 3)
					name = name:sub(4)
				elseif hasPrefix(name, "U") then
					t = t .. name:sub(1, 1)
					name = name:sub(2)
				elseif hasPrefix(name, "V") then
					t = t .. name:sub(1, 1)
					name = name:sub(2)
				elseif hasPrefix(name, "W") then
					t = t .. name:sub(1, 1)
					name = name:sub(2)
				elseif hasPrefix(name, "Compare") then
					t = t .. name:sub(1, 7)
					name = name:sub(8)
				end
			end
			return abbrevsToUpper(t) .. "." .. convName(toCamelCase(name))
		end
		
		for idx, flag in ipairs(typ.flag) do
			local value = flag.value
			if value ~= nil then
				value = hexStr(value, typ.bits)
			else
				for _, name in ipairs(flag) do
					if value ~= nil then
						value = value .. " | " .. getValOr(name)
					else
						value = getValOr(name)
					end
				end
			end
			
			local comments = ""
			if flag.comment ~= nil then
				if #flag.comment == 1 then
					comments = " ///" .. flag.comment[1]
				else
					yield("\t/**")
					for _, comment in ipairs(flag.comment) do
						yield("\t" .. comment)
					end
					yield("\t*/")
				end
			end
			
			local name = convName(toCamelCase(flag.name))
			yield("\t" .. name .. string.rep(" ", maxLen+2 - name:len()) .. "= " .. value .. "," .. comments)
			
			local intlName = toIntlEn(name)
			if intlName ~= nil then
				intlName = intlName
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
				"%s_ to%s(%s v) nothrow @nogc pure @safe{ return (v << %s) & %s; }",
				typeName,
				typeName,
				enumType,
				(typeName .. ".shift"),
				(typeName .. ".mask")))
			if intlName ~= nil then
				yield("alias to" .. intlName .. " = to" .. typeName .. ";")
			end
		end
	elseif typ.struct ~= nil then
		local st = {name = typ.name, comments = {}, fields = {}, fns = {}, subs = {}}
		
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
		
		if typ.ctor ~= nil and typ.name ~= "PlatformData" then
			table.insert(st.fns, "{q{void}, q{this}, q{}, ext: `C++`},")
		end
		
		if typ.namespace ~= nil then --if this is a sub-struct
			if allStructs[typ.namespace] ~= nil then
				table.insert(allStructs[typ.namespace].subs, st)
			else
				allStructs[typ.namespace] = {subs = {st}}
			end
		else --otherwise it's top-level
			if allStructs[typ.name] ~= nil then
				st.subs = allStructs[typ.name].subs
			end
			allStructs[typ.name] = st
		end
	end
end

function converter.funcs(func)
	if func.class == nil and func.conly == nil and func.cppinline == nil then
		local extern = "C++, \"bgfx\""
		local attribs = ""
		if func.cfunc ~= nil and func.name ~= "init" then --what the is "cfunc" even meant to mean?
			return
		end
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
					yield("\t" .. toIntlEnUncond(convName(arg.name:sub(2))) .. " = " .. arg.comment[1])
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
				def = string.format("=%s", convVal(arg.default, convFnArgType(arg)))
			end
			if arg.fulltype == "..." then
				table.insert(args, "..." .. def)
			else
				table.insert(args, convFnArgType(arg) .. " " .. toIntlEnUncond(convName(arg.name:sub(2))) .. def)
			end
		end
		
		if attribs ~= "" then
			attribs = ", memAttr: q{" .. attribs .. "}"
		end
		
		yield(string.format("{q{%s}, q{%s}, q{%s}, ext: `%s`%s},", convType(func.ret), func.name, table.concat(args, ", "), extern, attribs))
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
