-- Copyright 2019 云风 https://github.com/cloudwu . All rights reserved.
-- License (the same with bgfx) : https://github.com/bkaradzic/bgfx/blob/master/LICENSE

local codegen = require "codegen"
local idl = codegen.idl "bgfx.idl"

local func_actions = {

	c99              = "\n",
	c99decl          = "\n",
	cppdecl          = "\n",
	interface_struct = "\n\t",
	interface_import = ",\n\t\t\t",
	c99_interface    = "\n",
	cpp_interface    = "\n",
	c99_functionid   = "\n\t",
	cpp_functionid   = "\n\t\t",
}

local type_actions = {

	cflags    = "\n",
	enums     = "\n",
	cenums    = "\n",
	structs   = "\n",
	cstructs  = "\n",
	handles   = "\n",
	chandles  = "\n",
	funcptrs  = "\n",
	cfuncptrs = "\n",
}

local function cfunc(f)
	return function(func)
		if not func.cpponly then
			return f(func)
		end
	end
end

local funcgen = {}

local functemp = {}

functemp.interface_struct = "$CRET (*$CFUNCNAME)($CARGS);"
functemp.interface_import = "bgfx_$CFUNCNAME"
functemp.c99_interface = [[
BGFX_C_API $CRET bgfx_$CFUNCNAME($CARGS)
{
	$CONVERSIONCTOC
	$PRERETCTOCg_interface->$CFUNCNAME($CALLARGS);
	$POSTRETCTOC
}
]]
functemp.c99_functionid = "BGFX_FUNCTION_ID_$CFUNCNAMEUPPER,"
functemp.cpp_functionid = "$CFUNCNAMECAML,"

for action,temp in pairs(functemp) do
	funcgen[action] = cfunc(function(func)
		return codegen.apply_functemp(func, temp)
	end)
end

funcgen.cpp_interface= cfunc(function(func)
	if not func.cfunc and not func.conly then
		return codegen.apply_functemp(func, [[
$RET $CLASSNAME$FUNCNAME($CPPARGS)$CONST
{
	$CONVERSIONCTOCPP
	$PRERETCPPTOCg_interface->$CFUNCNAME($CALLARGSCPPTOC);
	$POSTRETCPPTOC
}
]])
	end
end)

funcgen.c99 = cfunc(function(func)
	local temp
	if func.cfunc then
		temp = "/* BGFX_C_API $CRET bgfx_$CFUNCNAME($CARGS) */\n"
	else
		temp = [[
BGFX_C_API $CRET bgfx_$CFUNCNAME($CARGS)
{
	$CONVERSION
	$PRERET$CPPFUNC($CALLARGSCTOCPP);
	$POSTRET
}
]]
	end
	return codegen.apply_functemp(func, temp)
end)

local function cppdecl(func)
	local doc = func.comments
	if not doc and func.comment then
		doc = { func.comment }
	end
	if doc then
		local cname
		if not func.cpponly then
			if func.multicfunc then
				cname = {}
				for _, name in ipairs(func.multicfunc) do
					cname[#cname+1] = "bgfx_" .. name
				end
			else
				cname = "bgfx_" .. func.cname
			end
		end
		doc = codegen.doxygen_type(doc, func, cname)
	end
	local funcdecl = codegen.apply_functemp(func, "$RET $FUNCNAME($ARGS)$CONST;\n")
	if doc then
		return doc .. "\n" .. funcdecl
	else
		return funcdecl
	end
end

function funcgen.cppdecl(func)
	-- Don't generate member functions here
	if not func.class and not func.conly then
		return cppdecl(func)
	end
end

funcgen.c99decl = cfunc(function(func)
	local doc = func.comments
	if not doc and func.comment then
		doc = { func.comment }
	end
	if doc then
		doc = codegen.doxygen_ctype(doc, func)
	end
	local funcdecl = codegen.apply_functemp(func, "BGFX_C_API $CRET bgfx_$CFUNCNAME($CARGS);")
	if doc then
		return "\n" .. doc .. "\n" .. funcdecl
	else
		return funcdecl
	end
end)

local typegen = {}

local function add_doxygen(typedef, define, cstyle, cname)
		local func = cstyle and codegen.doxygen_ctype or codegen.doxygen_type
		local doc = func(typedef.comments, typedef, cname or typedef.cname)
		if doc then
			return doc .. "\n" .. define
		else
			return define
		end
end

function typegen.enums(typedef)
	if typedef.enum then
		return add_doxygen(typedef, codegen.gen_enum_define(typedef), false, "bgfx_" .. typedef.cname)
	end
end

function typegen.cenums(typedef)
	if typedef.enum then
		return add_doxygen(typedef, codegen.gen_enum_cdefine(typedef), true)
	end
end

function typegen.cflags(typedef)
	if typedef.flag then
		return add_doxygen(typedef, codegen.gen_flag_cdefine(typedef), true)
	end
end

function typegen.structs(typedef)
	if typedef.struct and not typedef.namespace then
		local methods = typedef.methods
		if methods then
			local m = {}
			for _, func in ipairs(methods) do
				m[#m+1] = cppdecl(func)
			end
			methods = m
		end
		return add_doxygen(typedef, codegen.gen_struct_define(typedef, methods))
	end
end

function typegen.cstructs(typedef)
	if typedef.struct then
		return add_doxygen(typedef, codegen.gen_struct_cdefine(typedef), true)
	end
end

function typegen.handles(typedef)
	if typedef.handle then
		return codegen.gen_handle(typedef)
	end
end

function typegen.chandles(typedef)
	if typedef.handle then
		return codegen.gen_chandle(typedef)
	end
end

function typegen.funcptrs(typedef)
	if typedef.args then
		return add_doxygen(typedef, codegen.gen_funcptr(typedef))
	end
end

function typegen.cfuncptrs(typedef)
	if typedef.args then
		return add_doxygen(typedef, codegen.gen_cfuncptr(typedef), true)
	end
end

local function codes()
	local temp = {}
	for k in pairs(func_actions) do
		temp[k] = {}
	end

	for k in pairs(type_actions) do
		temp[k] = {}
	end

	-- call actions with func
	for _, f in ipairs(idl.funcs) do
		for k in pairs(func_actions) do
			local funcgen = funcgen[k]
			if funcgen then
				table.insert(temp[k], (funcgen(f)))
			end
		end
	end

	-- call actions with type

	for _, typedef in ipairs(idl.types) do
		for k in pairs(type_actions) do
			local typegen = typegen[k]
			if typegen then
				table.insert(temp[k], (typegen(typedef)))
			end
		end
	end

	for k, indent in pairs(func_actions) do
		temp[k] = table.concat(temp[k], indent)
	end
	for k, indent in pairs(type_actions) do
		temp[k] = table.concat(temp[k], indent)
	end

	temp.version = string.format("#define BGFX_API_VERSION UINT32_C(%d)", idl._version or 0)

	return temp
end

local codes_tbl = codes()

local function add_path(filename)
	local path
	if type(paths) == "string" then
		path = paths
	else
		path = assert(paths[filename])
	end
	return path .. "/" .. filename
end

local function change_indent(str, indent)
	if indent == "\t" then
		-- strip trailing space only
		return (str:gsub("(.-)\n", function (line)
			return line:gsub("([ \t]*)$","\n") end))
	else
		return (str:gsub("(.-)\n", function (line)
			return line:gsub("^(\t*)(.-)[ \t]*$",
				function (tabs, content)
					return indent:rep(#tabs) .. content .. "\n"
				end)
		end))
	end
end

local gen = {}

function gen.apply(tempfile)
	local f = assert(io.open(tempfile, "rb"))
	local temp = f:read "a"
	f:close()
	codes_tbl.source = tempfile
	return (temp:gsub("$([%l%d_]+)", codes_tbl))
end

function gen.format(codes, f)
	return change_indent(codes, f.indent)
end

function gen.changed(codes, outputfile)
	local out = io.open(outputfile, "rb")
	if out then
		local origin = out:read "a"
		out:close()
		return origin ~= codes
	end
	return true
end

function gen.write(codes, outputfile)
	local out = assert(io.open(outputfile, "wb"))
	out:write(codes)
	out:close()
end

function gen.gen(tempfile, outputfile, indent)
	print ("Generate", outputfile, "from", tempfile)
	local codes = gen.apply(tempfile)
	codes = change_indent(codes, indent)

	if not gen.changed(codes, outputfile) then
		print("No change")
	end

	gen.write(codes, outputfile)
end

return gen
