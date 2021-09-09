-- Copyright 2019 云风 https://github.com/cloudwu . All rights reserved.
-- License (the same with bgfx) : https://github.com/bkaradzic/bgfx/blob/master/LICENSE

local codegen = {}

local DEFAULT_NAME_ALIGN = 20
local DEFINE_NAME_ALIGN  = 41

local function namealign(name, align)
	align = align or DEFAULT_NAME_ALIGN
	return string.rep(" ", align - #name)
end

local function camelcase_to_underscorecase(name)
	local tmp = {}
	for v in name:gmatch "[%u%d]+%l*" do
		tmp[#tmp+1] = v:lower()
	end
	return table.concat(tmp, "_")
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

local function underscorecase_to_camelcase(name)
	local tmp = {}
	for v in name:gmatch "[^_]+" do
		tmp[#tmp+1] = v:sub(1,1):upper() .. v:sub(2)
	end
	return table.concat(tmp)
end

local function convert_funcname(name)
	name = name:gsub("^%l", string.upper)	-- Change to upper CamlCase
	return camelcase_to_underscorecase(name)
end

local function convert_arg(all_types, arg, namespace)
	local fulltype, array = arg.fulltype:match "(.-)%s*(%[%s*[%d%a_:]*%s*%])"
	if array then
		arg.fulltype = fulltype
		arg.array = array
		local enum, value = array:match "%[%s*([%a%d]+)::([%a%d]+)%]"
		if enum then
			local typedef = all_types[ enum .. "::Enum" ]
			if typedef == nil then
				error ("Unknown Enum " .. enum)
			end
			arg.carray = "[BGFX_" .. camelcase_to_underscorecase(enum):upper() .. "_" .. value:upper() .. "]"
		end
	end
	local t, postfix = arg.fulltype:match "(%a[%a%d_:]*)%s*([*&]+)%s*$"
	if t then
		arg.type = t
		if postfix == "&" then
			arg.ref = true
		end
	else
		local prefix, t = arg.fulltype:match "^%s*(%a+)%s+(%S+)"
		if prefix then
			arg.type = t
		else
			arg.type = arg.fulltype
		end
	end
	local ctype
	local substruct = namespace.substruct
	if substruct then
		ctype = substruct[arg.type]
	end
	if not ctype then
		ctype = all_types[arg.type]
	end
	if not ctype then
		error ("Undefined type " .. arg.fulltype .. " in " .. namespace.name)
	end
	arg.ctype = arg.fulltype:gsub(arg.type, ctype.cname):gsub("&", "*")
	if ctype.cname ~= arg.type then
		arg.cpptype = arg.fulltype:gsub(arg.type, "bgfx::"..arg.type)
	else
		arg.cpptype = arg.fulltype
	end
	if arg.ref then
		arg.ptype = arg.cpptype:gsub("&", "*")
	end
end

local function alternative_name(name)
	if name:sub(1,1) == "_" then
		return name:sub(2)
	else
		return name .. "_"
	end
end

local function gen_arg_conversion(all_types, arg)
	if arg.ctype == arg.fulltype then
		-- do not need conversion
		return
	end
	local ctype = all_types[arg.type]
	if ctype.handle and arg.type == arg.fulltype then
		local aname = alternative_name(arg.name)
		arg.aname = aname .. ".cpp"
		arg.aname_cpp2c = aname .. ".c"
		arg.conversion = string.format(
			"union { %s c; bgfx::%s cpp; } %s = { %s };" ,
			ctype.cname, arg.type, aname, arg.name)
		arg.conversion_back = string.format(
			"union { bgfx::%s cpp; %s c; } %s = { %s };" ,
			arg.type, ctype.cname, aname, arg.name)
	elseif arg.ref then
		if ctype.cname == arg.type then
			arg.aname = "*" .. arg.name
			arg.aname_cpp2c = "&" .. arg.name
		elseif arg.out and ctype.enum then
			local aname = alternative_name(arg.name)
			local cpptype = arg.cpptype:match "(.-)%s*&"	-- remove &
			local c99type = arg.ctype:match "(.-)%s*%*"	-- remove *
			arg.aname = aname
			arg.aname_cpp2c = "&" .. aname
			arg.conversion = string.format("%s %s;", cpptype, aname)
			arg.conversion_back = string.format("%s %s;", c99type, aname);
			arg.out_conversion = string.format("*%s = (%s)%s;", arg.name, ctype.cname, aname)
			arg.out_conversion_back = string.format("%s = (%s)%s;", arg.name, c99type, aname)
		else
			arg.aname = alternative_name(arg.name)
			arg.aname_cpp2c = string.format("(%s)&%s" , arg.ctype , arg.name)
			arg.conversion = string.format(
				"%s %s = *(%s)%s;",
				arg.cpptype, arg.aname, arg.ptype, arg.name)
		end
	else
		local cpptype = arg.cpptype
		local ctype = arg.ctype
		if arg.array then
			cpptype = cpptype .. "*"
			ctype = ctype .. "*"
		end
		arg.aname = string.format(
			"(%s)%s",
			cpptype, arg.name)
		arg.aname_cpp2c = string.format(
			"(%s)%s",
			ctype, arg.name)
	end
end

local function gen_ret_conversion(all_types, func)
	local postfix = { func.vararg and "va_end(argList);" }
	local postfix_cpp2c = { postfix[1] }
	func.ret_postfix = postfix
	func.ret_postfix_cpp2c = postfix_cpp2c

	for _, arg in ipairs(func.args) do
		if arg.out_conversion then
			postfix[#postfix+1] = arg.out_conversion
			postfix_cpp2c[#postfix_cpp2c+1] = arg.out_conversion_back
		end
	end

	local ctype = all_types[func.ret.type]
	if ctype.handle then
		func.ret_conversion = string.format(
			"union { %s c; bgfx::%s cpp; } handle_ret;" ,
			ctype.cname, ctype.name)
		func.ret_conversion_cpp2c = string.format(
			"union { bgfx::%s cpp; %s c; } handle_ret;" ,
			ctype.name, ctype.cname)
		func.ret_prefix = "handle_ret.cpp = "
		func.ret_prefix_cpp2c = "handle_ret.c = "
		postfix[#postfix+1] = "return handle_ret.c;"
		postfix_cpp2c[#postfix_cpp2c+1] = "return handle_ret.cpp;"
	elseif func.ret.fulltype ~= "void" then
		local ctype_conversion = ""
		local conversion_back = ""
		if ctype.name ~= ctype.cname then
			if func.ret.ref then
				ctype_conversion =  "(" ..  func.ret.ctype .. ")&"
				conversion_back = "*(" ..  func.ret.ptype .. ")"
			else
				ctype_conversion = "(" ..  func.ret.ctype .. ")"
				conversion_back = "(" ..  func.ret.cpptype .. ")"
			end
		end
		if #postfix > 0 then
			func.ret_prefix = string.format("%s retValue = %s", func.ret.ctype , ctype_conversion)
			func.ret_prefix_cpp2c = string.format("%s retValue = %s", func.ret.cpptype , conversion_back)
			local ret = "return retValue;"
			postfix[#postfix+1] = ret
			postfix_cpp2c[#postfix_cpp2c+1] = ret
		else
			func.ret_prefix = string.format("return %s", ctype_conversion)
			func.ret_prefix_cpp2c = string.format("return %s", conversion_back)
		end
	end
end

local function convert_vararg(v)
	if v.vararg then
		local args = v.args
		local vararg = {
			name = "",
			fulltype = "...",
			type = "...",
			ctype = "...",
			aname = "argList",
			conversion = string.format(
				"va_list argList;\n\tva_start(argList, %s);",
				args[#args].name),
		}
		args[#args + 1] = vararg
		v.alter_name = v.vararg
	end
end

local function calc_flag_values(flag)
	local shift = flag.shift
	local base = flag.base or 0
	local cap = 1 << (flag.range or 0)

	if flag.range then
		if flag.range == 64 then
			flag.mask = 0xffffffffffffffff
		else
			flag.mask = ((1 << flag.range) - 1) << shift
		end
	end

	local values = {}
	for index, item in ipairs(flag.flag) do
		local value = item.value
		if flag.const then
			-- use value directly
		elseif shift then
			if value then
				if value > 0 then
					value = value - 1
				end
			else
				value = index + base - 1
			end
			if value >= cap then
				error (string.format("Out of range for %s.%s (%d/%d)", flag.name, item.name, value, cap))
			end
			value = value << shift
		elseif #item == 0 then
			if value then
				if value > 0 then
					value = 1 << (value - 1)
				end
			else
				local s = index + base - 2
				if s >= 0 then
					value = 1 << s
				else
					value = 0
				end
			end
		end
		if not value then
			-- It's a combine flags
			value = 0
			for _, name in ipairs(item) do
				local v = values[name]
				if v then
					value = value | v
				else
					-- todo : it's a undefined flag
					value = nil
					break
				end
			end
		end
		item.value = value
		values[item.name] = value
	end
end

function codegen.nameconversion(all_types, all_funcs)
	for _,v in ipairs(all_types) do
		local name = v.name
		local cname = v.cname
		if cname == nil then
			if name:match "^%u" then
				cname = camelcase_to_underscorecase(name)
			elseif not v.flag then
				v.cname = name
			end
		end
		if cname and not v.flag then
			if v.namespace then
				cname = camelcase_to_underscorecase(v.namespace) .. "_" .. cname
			end
			v.cname = "bgfx_".. cname .. "_t"
		end
		if v.enum then
			v.typename = v.name
			v.name = v.name .. "::Enum"
		end
		if v.flag then
			calc_flag_values(v)
		end
	end

	-- make index
	for _,v in ipairs(all_types) do
		if not v.namespace then
			if all_types[v.name] then
				error ("Duplicate type " .. v.name)
			elseif not v.flag then
				all_types[v.name] = v
			end
		end
	end

	-- make sub struct index
	for _,v in ipairs(all_types) do
		if v.namespace then
			local super = all_types[v.namespace]
			if not super then
				error ("Define " .. v.namespace .. " first")
			end
			local substruct = super.substruct
			if not substruct then
				substruct = {}
				super.substruct = substruct
			end
			if substruct[v.name] then
				error ( "Duplicate sub struct " .. v.name .. " in " .. v.namespace)
			end
			v.parent_class = super
			substruct[#substruct+1] = v
			substruct[v.name] = v
		end
	end

	for _,v in ipairs(all_types) do
		if v.struct then
			for _, item in ipairs(v.struct) do
				convert_arg(all_types, item, v)
			end
		elseif v.args then
			-- funcptr
			for _, arg in ipairs(v.args) do
				convert_arg(all_types, arg, v)
			end
			convert_vararg(v)
			convert_arg(all_types, v.ret, v)
		end
	end

	local funcs = {}
	local funcs_conly = {}
	local funcs_alter = {}

	for _,v in ipairs(all_funcs) do
		if v.cname == nil then
			v.cname = convert_funcname(v.name)
		end
		if v.class then
			v.cname = convert_funcname(v.class) .. "_" .. v.cname
			local classtype = all_types[v.class]
			if classtype then
				local methods = classtype.methods
				if not methods then
					methods = {}
					classtype.methods = methods
				end
				methods[#methods+1] = v
			end
		elseif not v.conly then
			funcs[v.name] = v
		end

		if v.conly then
			table.insert(funcs_conly, v)
		end

		for _, arg in ipairs(v.args) do
			convert_arg(all_types, arg, v)
			gen_arg_conversion(all_types, arg)
		end
		convert_vararg(v)
		if v.alter_name then
			funcs_alter[#funcs_alter+1] = v
		end
		convert_arg(all_types, v.ret, v)
		gen_ret_conversion(all_types, v)
		local namespace = v.class
		if namespace then
			local classname = namespace
			if v.const then
				classname = "const " .. classname
			end
			local classtype = { fulltype = classname .. "*" }
			convert_arg(all_types, classtype, v)
			v.this = classtype.ctype
			v.this_type = classtype
			v.this_conversion = string.format( "%s This = (%s)_this;", classtype.cpptype, classtype.cpptype)
			v.this_to_c = string.format("(%s)this", classtype.ctype)
		end
	end

	for _, v in ipairs(funcs_conly) do
		local func = funcs[v.name]
		if func then
			func.multicfunc = func.multicfunc or { func.cname }
			table.insert(func.multicfunc, v.cname)
		end
	end

	for _, v in ipairs(funcs_alter) do
		local func = funcs[v.alter_name]
		v.alter_cname = func.cname
	end
end

local function lines(tbl)
	if not tbl or #tbl == 0 then
		return "//EMPTYLINE"
	else
		return table.concat(tbl, "\n\t")
	end
end

local function remove_emptylines(txt)
	return (txt:gsub("\t//EMPTYLINE\n", ""))
end

local function codetemp(func)
	local conversion = {}
	local conversion_c2cpp = {}
	local args = {}
	local cargs = {}
	local callargs_conversion = {}
	local callargs_conversion_back = {}
	local callargs = {}
	local cppfunc
	local classname

	if func.class then
		-- It's a member function
		cargs[1] = func.this .. " _this"
		conversion[1] = func.this_conversion
		cppfunc = "This->" .. func.name
		callargs[1] = "_this"
		callargs_conversion_back[1] = func.this_to_c
		classname = func.class .. "::"
	else
		cppfunc = "bgfx::" .. tostring(func.alter_name or func.name)
		classname = ""
	end
	for _, arg in ipairs(func.args) do
		conversion[#conversion+1] = arg.conversion
		conversion_c2cpp[#conversion_c2cpp+1] = arg.conversion_back
		local cname = arg.ctype .. " " .. arg.name
		if arg.array then
			cname = cname .. (arg.carray or arg.array)
		end
		local name = arg.fulltype .. " " .. arg.name
		if arg.array then
			name = name .. arg.array
		end
		if arg.default ~= nil then
			name = name .. " = " .. tostring(arg.default)
		end
		cargs[#cargs+1] = cname
		args[#args+1] = name
		callargs_conversion[#callargs_conversion+1] = arg.aname or arg.name
		callargs_conversion_back[#callargs_conversion_back+1] = arg.aname_cpp2c or arg.name
		callargs[#callargs+1] = arg.name
	end
	conversion[#conversion+1] = func.ret_conversion
	conversion_c2cpp[#conversion_c2cpp+1] = func.ret_conversion_cpp2c

	local ARGS
	local args_n = #args
	if args_n == 0 then
		ARGS = ""
	elseif args_n == 1 then
		ARGS = args[1]
	else
		ARGS = "\n\t  " .. table.concat(args, "\n\t, ") .. "\n\t"
	end

	local preret_c2c
	local postret_c2c = {}
	local conversion_c2c = {}
	local callfunc_c2c

	if func.vararg then
		postret_c2c[1] = "va_end(argList);"
		local vararg = func.args[#func.args]
		callargs[#callargs] = vararg.aname
		callargs_conversion_back[#callargs_conversion_back] = vararg.aname
		conversion_c2c[1] = vararg.conversion
		conversion_c2cpp[1] = vararg.conversion

		if func.ret.fulltype == "void" then
			preret_c2c = ""
		else
			preret_c2c = func.ret.ctype .. " retValue = "
			postret_c2c[#postret_c2c+1] = "return retValue;"
		end
		callfunc_c2c = func.alter_cname or func.cname
	else
		if func.ret.fulltype == "void" then
			preret_c2c = ""
		else
			preret_c2c = "return "
		end
		callfunc_c2c = func.cname
	end

	outCargs = table.concat(cargs, ", ")
	if outCargs == "" then
		outCargs = "void"
	end

	return {
		RET = func.ret.fulltype,
		CRET = func.ret.ctype,
		CFUNCNAME = func.cname,
		CFUNCNAMEUPPER = func.cname:upper(),
		CFUNCNAMECAML = underscorecase_to_camelcase(func.cname),
		FUNCNAME = func.name,
		CARGS = outCargs,
		CPPARGS = table.concat(args, ", "),
		ARGS = ARGS,
		CONVERSION = lines(conversion),
		CONVERSIONCTOC = lines(conversion_c2c),
		CONVERSIONCTOCPP = lines(conversion_c2cpp),
		PRERET = func.ret_prefix or "",
		PRERETCPPTOC = func.ret_prefix_cpp2c or "",
		CPPFUNC = cppfunc,
		CALLFUNCCTOC = callfunc_c2c,
		CALLARGSCTOCPP = table.concat(callargs_conversion, ", "),
		CALLARGSCPPTOC = table.concat(callargs_conversion_back, ", "),
		CALLARGS = table.concat(callargs, ", "),
		POSTRET = lines(func.ret_postfix),
		POSTRETCPPTOC = lines(func.ret_postfix_cpp2c),
		PRERETCTOC = preret_c2c,
		POSTRETCTOC = lines(postret_c2c),
		CLASSNAME = classname,
		CONST = func.const and " const" or "",
	}
end

local function apply_template(func, temp)
	func.codetemp = func.codetemp or codetemp(func)
	return (temp:gsub("$(%u+)", func.codetemp))
end

function codegen.apply_functemp(func, temp)
		return remove_emptylines(apply_template(func, temp))
end

function codegen.gen_funcptr(funcptr)
	return apply_template(funcptr, "typedef $RET (*$FUNCNAME)($ARGS);")
end

function codegen.gen_cfuncptr(funcptr)
	return apply_template(funcptr, "typedef $CRET (*$CFUNCNAME)($CARGS);")
end

local function doxygen_funcret(r, func, prefix)
	if not func or func.ret.fulltype == "void" or func.ret.comment == nil then
		return
	end
	r[#r+1] = prefix
	r[#r+1] = string.format("%s @returns %s", prefix, func.ret.comment[1])
	for i = 2,#func.ret.comment do
		r[#r+1] = string.format("%s  %s", prefix, func.ret.comment[i])
	end
	return r
end

local function doxygen_func(r, func, prefix)
	if not func or not func.args or #func.args == 0 then
		return
	end
	r[#r+1] = prefix
	for _, arg in ipairs(func.args) do
		local inout
		if arg.out then
			inout = "out"
		elseif arg.inout then
			inout = "inout"
		else
			inout = "in"
		end
		local comment = string.format("%s @param[%s] %s", prefix, inout, arg.name)
		if arg.comment then
			r[#r+1] = comment .. " " .. arg.comment[1]
			for i = 2,#arg.comment do
				r[#r+1] = string.format("%s  %s", prefix, arg.comment[i])
			end
		else
			r[#r+1] = comment
		end
	end
	doxygen_funcret(r, func, prefix)
	return r
end

function codegen.doxygen_type(doxygen, func, cname)
	if doxygen == nil then
		return
	end
	local result = {}
	for _, line in ipairs(doxygen) do
		result[#result+1] = "/// " .. line
	end
	doxygen_func(result, func, "///")
	if cname then
		result[#result+1] = "///"
		if type(cname) == "string" then
			result[#result+1] = string.format("/// @attention C99 equivalent is `%s`.", cname)
		else
			local names = {}
			for _, v in ipairs(cname) do
				names[#names+1] = "`" .. v .. "`"
			end
			result[#result+1] = string.format("/// @attention C99 equivalent are %s.", table.concat(names, ","))
		end
	end
	result[#result+1] = "///"
	return table.concat(result, "\n")
end

function codegen.doxygen_ctype(doxygen, func)
	if doxygen == nil then
		return
	end
	local result = {
		"/**",
	}
	for _, line in ipairs(doxygen) do
		result[#result+1] = " * " .. line
	end
	doxygen_func(result, func, " *")
	result[#result+1] = " *"
	result[#result+1] = " */"
	return table.concat(result, "\n")
end

local enum_temp = [[
struct $NAME
{
	$COMMENT
	enum Enum
	{
		$ITEMS

		Count
	};
};
]]

function codegen.gen_enum_define(enum)
	assert(type(enum.enum) == "table", "Not an enum")
	local items = {}
	for _, item in ipairs(enum.enum) do
		local text
		if not item.comment then
			text = item.name .. ","
		else
			local comment = table.concat(item.comment, " ")
			text = string.format("%s,%s //!< %s",
				item.name, namealign(item.name), comment)
		end
		items[#items+1] = text
	end
	local comment = ""
	if enum.comment then
		comment = "/// " .. enum.comment
	end
	local temp = {
		NAME = enum.typename,
		COMMENT = comment,
		ITEMS = table.concat(items, "\n\t\t"),
	}
	return (enum_temp:gsub("$(%u+)", temp))
end

local cenum_temp = [[
typedef enum $NAME
{
	$ITEMS

	$COUNT

} $NAME_t;
]]
function codegen.gen_enum_cdefine(enum)
	assert(type(enum.enum) == "table", "Not an enum")
	local cname = enum.cname:match "(.-)_t$"
	local uname = cname:upper()
	local items = {}
	for index , item in ipairs(enum.enum) do
		local comment = ""
		if item.comment then
			comment = table.concat(item.comment, " ")
		end
		local ename = item.cname
		if not ename then
			if enum.underscore then
				ename = camelcase_to_underscorecase(item.name)
			else
				ename = item.name
			end
			ename = ename:upper()
		end
		local name = uname .. "_" .. ename
		items[#items+1] = string.format("%s,%s /** (%2d) %s%s */",
			name,
			namealign(name, 40),
			index - 1,
			comment,
			namealign(comment, 30))
	end

	local temp = {
		NAME = cname,
		COUNT = uname .. "_COUNT",
		ITEMS = table.concat(items, "\n\t"),
	}

	return (cenum_temp:gsub("$(%u+)", temp))
end

local function flag_format(flag)
	if not flag.format then
		flag.format = "%0" .. (flag.bits // 4) .. "x"
	end
end

function codegen.gen_flag_cdefine(flag)
	assert(type(flag.flag) == "table", "Not a flag")
	flag_format(flag)
	local cname = "BGFX_" .. (flag.cname or to_underscorecase(flag.name):upper())
	local s = {}
	local shift = flag.shift
	for index, item in ipairs(flag.flag) do
		local name
		if item.cname then
			name = cname .. "_" .. item.cname
		else
			name = cname .. "_" .. to_underscorecase(item.name):upper()
		end
		local value = item.value

		-- combine flags
		if #item > 0 then
			if item.comment then
				for _, c in ipairs(item.comment) do
					s[#s+1] = "/// " .. c
				end
			end
			local sets = { "" }
			for _, v in ipairs(item) do
				sets[#sets+1] = cname .. "_" .. to_underscorecase(v):upper()
			end
			s[#s+1] = string.format("#define %s (0%s \\\n\t)\n", name, table.concat(sets, " \\\n\t| "))
		else
			local comment = ""
			if item.comment then
				if #item.comment > 1 then
					s[#s+1] = ""
					for _, c in ipairs(item.comment) do
						s[#s+1] = "/// " .. c
					end
				else
					comment = " //!< " .. item.comment[1]
				end
			end
			value = string.format(flag.format, value)
			local code = string.format("#define %s %sUINT%d_C(0x%s)%s",
				name, namealign(name, DEFINE_NAME_ALIGN), flag.bits, value, comment)
			s[#s+1] = code
		end
	end

	local mask
	if flag.mask then
		mask = string.format(flag.format, flag.mask)
		mask = string.format("UINT%d_C(0x%s)", flag.bits, mask)
	end

	if shift then
		local name = cname .. "_SHIFT"
		local comment = flag.desc or ""
		local shift_align = tostring(shift)
		shift_align = shift_align .. namealign(shift_align, #mask)
		local comment = ""
		if flag.desc then
			comment = string.format(" //!< %s bit shift", flag.desc)
		end
		local code = string.format("#define %s %s%s%s", name, namealign(name, DEFINE_NAME_ALIGN), shift_align, comment)
		s[#s+1] = code
	end
	if flag.range then
		local name = cname .. "_MASK"
		local comment = ""
		if flag.desc then
			comment = string.format(" //!< %s bit mask", flag.desc)
		end
		local code = string.format("#define %s %s%s%s", name, namealign(name, DEFINE_NAME_ALIGN), mask, comment)
		s[#s+1] = code
	end

	if flag.helper then
		s[#s+1] = string.format(
			"#define %s(v) ( ( (uint%d_t)(v)<<%s )&%s)",
			cname,
			flag.bits,
			(cname .. "_SHIFT"),
			(cname .. "_MASK"))
	end

	s[#s+1] = ""

	return table.concat(s, "\n")
end

local function text_with_comments(items, item, cstyle, is_classmember)
	local name = item.name
	if item.array then
		if cstyle then
			name = name .. (item.carray or item.array)
		else
			name = name .. item.array
		end
	end
	local typename
	if cstyle then
		typename = item.ctype
	else
		typename = item.fulltype
	end
	if is_classmember then
		name = "m_" .. name
	end
	local text = string.format("%s%s %s;", typename, namealign(typename), name)
	if item.comment then
		if #item.comment > 1 then
			table.insert(items, "")
			if cstyle then
				table.insert(items, "/**")
				for _, c in ipairs(item.comment) do
					table.insert(items, " * " .. c)
				end
				table.insert(items, " */")
			else
				for _, c in ipairs(item.comment) do
					table.insert(items, "/// " .. c)
				end
			end
		else
			text = string.format(
				cstyle and "%s %s/** %s%s */" or "%s %s//!< %s",
				text, namealign(text, 40),  item.comment[1], namealign(item.comment[1], 40))
		end
	end
	items[#items+1] = text
end

local struct_temp = [[
struct $NAME
{
	$METHODS
	$SUBSTRUCTS
	$ITEMS
};
]]

function codegen.gen_struct_define(struct, methods)
	assert(type(struct.struct) == "table", "Not a struct")
	local items = {}
	for _, item in ipairs(struct.struct) do
		text_with_comments(items, item, false, methods ~= nil and not struct.shortname)
	end
	local ctor = {}
	if struct.ctor then
		ctor[1] = struct.name .. "();"
		ctor[2] = ""
	end
	if methods then
		for _, m in ipairs(methods) do
			if m:sub(-1) ~= "\n" then
				m = m .. "\n"
			end
			for line in m:gmatch "(.-)\n" do
				ctor[#ctor+1] = line
			end
			ctor[#ctor+1] = ""
		end
	end
	local subs = {}
	if struct.substruct then
		for _, v in ipairs(struct.substruct) do
			local s = codegen.gen_struct_define(v)
			s = s:gsub("\n", "\n\t")
			subs[#subs+1] = s
		end
	end

	local temp = {
		NAME = struct.name,
		SUBSTRUCTS = lines(subs),
		ITEMS = table.concat(items, "\n\t"),
		METHODS = lines(ctor),
	}
	return remove_emptylines(struct_temp:gsub("$(%u+)", temp))
end

local cstruct_temp = [[
typedef struct $NAME_s
{
	$ITEMS

} $NAME_t;
]]
local cstruct_empty_temp = [[
struct $NAME_s;
typedef struct $NAME_s $NAME_t;
]]
function codegen.gen_struct_cdefine(struct)
	assert(type(struct.struct) == "table", "Not a struct")
	local cname = struct.cname:match "(.-)_t$"
	local items = {}
	for _, item in ipairs(struct.struct) do
		text_with_comments(items, item, true)
	end
	local temp = {
		NAME = cname,
		ITEMS = table.concat(items, "\n\t"),
	}
	local codetemp = #struct.struct == 0 and cstruct_empty_temp or cstruct_temp
	return (codetemp:gsub("$(%u+)", temp))
end

local chandle_temp = [[
typedef struct $NAME_s { uint16_t idx; } $NAME_t;
]]
function codegen.gen_chandle(handle)
	assert(handle.handle, "Not a handle")
	return (chandle_temp:gsub("$(%u+)", { NAME = handle.cname:match "(.-)_t$" }))
end

local handle_temp = [[
struct $NAME { uint16_t idx; };
inline bool isValid($NAME _handle) { return bgfx::kInvalidHandle != _handle.idx; }
]]
function codegen.gen_handle(handle)
	assert(handle.handle, "Not a handle")
	return (handle_temp:gsub("$(%u+)", { NAME = handle.name }))
end

local idl = require "idl"
local doxygen = require "doxygen"
local conversion
local idlfile = {}

function codegen.load(filename)
	assert(conversion == nil, "Don't call codegen.load() after codegen.idl()")
	assert(idlfile[filename] == nil, "Duplicate load " .. filename)
	local source = doxygen.load(filename)

	local f = assert(load(source, filename , "t", idl))
	f()
	idlfile[filename] = true
end

function codegen.idl(filename)
	if conversion == nil then
		if filename and not idlfile[filename] then
			codegen.load(filename)
		end
		assert(next(idlfile), "call codegen.load() first")
		conversion = true
		codegen.nameconversion(idl.types, idl.funcs)
	end
	return idl
end

return codegen
