-- Copyright 2019 云风 https://github.com/cloudwu . All rights reserved.
-- License (the same with bgfx) : https://github.com/bkaradzic/bgfx/blob/master/LICENSE

local idl = {}

local comments = {}

function idl.comment(c)
	comments[#comments+1] = c
end

local all_types = {}

local function copy_attribs(to, from)
	assert(type(from) == "table", "Attribs should be a table")
	for k, v in pairs(from) do
		if type(k) == "number" then
			to[v] = true
		else
			to[k] = v
		end
	end
end

local function classdef(item, def)
	local function class(_, methodname)
		item.class = item.name
		item.name = methodname
		return def
	end

	return setmetatable({} , { __index = class, __call = function(_, value) return def(value) end })
end

local function new_type(typename)
	local t = { name = typename }
	if #comments > 0 then
		t.comments = comments
		comments = {}
	end
	all_types[#all_types+1] = t
	return t
end

local function typedef(_, typename)
	local t = new_type(typename)

	local function type_attrib(attrib)
		copy_attribs(t, attrib)
	end
	return function(cname)
		local typ = type(cname)
		if typ == "table" then
			type_attrib(cname)
			return
		end
		assert(typ == "string" , "type should be a string")
		t.cname = cname
		return type_attrib
	end
end

idl.typedef = setmetatable({} , { __index = typedef, __call = typedef })
idl.types = all_types

local function add_comment(item, comment)
	-- strip space
	comment = comment:match "(.-)%s*$"
	local last = item.comment
	if last then
		if type(last) == "string" then
			item.comment = { last, comment }
		else
			table.insert(item.comment, comment)
		end
	else
		item.comment = comment
	end
end

local function enumdef(_, typename)
	local t = new_type(typename)
	t.enum = {}

	local function enum_attrib(obj, attribs)
		copy_attribs(t, attribs)
		return obj
	end

	local function new_enum_item(_, itemname)
		local item = { name = itemname }
		t.enum[#t.enum + 1] = item
		local function add_attrib_or_comment(obj , attribs)
			if type(attribs) == "string" then
				add_comment(item, attribs)
			elseif attribs then
				copy_attribs(item, attribs)
			end
			return obj
		end
		return setmetatable({}, { __index = new_enum_item, __call = add_attrib_or_comment })
	end

	return setmetatable({}, { __index = new_enum_item , __call = enum_attrib })
end

idl.enum = setmetatable({} , { __index = enumdef, __call = enumdef })

local function structdef(_, typename)
	local t = new_type(typename)
	t.struct = {}

	local function struct_attrib(obj, attribs)
		copy_attribs(t, attribs)
		return obj
	end

	local function new_struct_item(_, itemname)
		local item = { name = itemname }
		t.struct[#t.struct + 1] = item

		local function item_attrib(obj, attribs)
			if type(attribs) == "string" then
				add_comment(item, attribs)
			else
				copy_attribs(item, attribs)
			end
			return obj
		end

		return function (itemtype)
			item.fulltype = itemtype
			return setmetatable({}, { __index = new_struct_item, __call = item_attrib })
		end
	end

	return setmetatable({}, { __index = new_struct_item , __call = struct_attrib })
end

idl.struct = setmetatable({}, { __index = structdef , __call = structdef })

local function handledef(_, typename)
	local t = new_type(typename)
	t.handle = true

	return function (attribs)
		copy_attribs(t, attribs)
		return obj
	end
end

idl.handle = setmetatable({} , { __index = handledef, __call = handledef })

local all_funcs = {}

local function duplicate_arg_name(_, name)
	error ("Duplicate arg name " .. name)
end

local function attribs_setter(args, arg, args_desc)
	local attribs_setter
	local function arg_attrib_or_comment(_, attrib_or_comment )
		if type(attrib_or_comment) == "string" then
			add_comment(arg, attrib_or_comment)
		else
			copy_attribs(arg, attrib_or_comment)
		end
		return attribs_setter
	end
	-- next field (__index) or attrib/comment (__call)
	attribs_setter = setmetatable( {} , {
		__index = function(_, name)
			return args_desc(args, name)
		end
		, __call = arg_attrib_or_comment } )
	return attribs_setter
end

local function func(sets)
	return function (_, funcname)
		local f = { name = funcname , args = {} }
		if #comments > 0 then
			f.comments = comments
			comments = {}
		end
		sets[#sets+1] = f
		local args
		local function args_desc(_, args_name)
			args[args_name] = duplicate_arg_name
			return function (fulltype)
				local arg = {
					name = "_" .. args_name,
					fulltype = fulltype,
				}
				f.args[#f.args+1] = arg
				return attribs_setter(args, arg, args_desc)
			end
		end
		args = setmetatable({}, { __index = args_desc })
		local function rettype(value)
			assert(type(value) == "string", "Need return type")
			local ret = { fulltype = value }
			f.ret = ret
			return attribs_setter(args, ret, args_desc)
		end

		local function funcdef(value)
			if type(value) == "table" then
				copy_attribs(f, value)
				return rettype
			end
			return rettype(value)
		end

		return classdef(f, funcdef)
	end
end

idl.funcptr = setmetatable({}, { __index = func(all_types) })
idl.func    = setmetatable({}, { __index = func(all_funcs) })
idl.funcs   = all_funcs

idl.vararg     = "vararg"
idl.out        = "out"
idl.inout      = "inout"
idl.const      = "const"
idl.ctor       = "ctor"
idl.cfunc      = "cfunc"
idl.underscore = "underscore"
idl.conly      = "conly"
idl.cpponly    = "cpponly"
idl.shortname  = "shortname"
idl.NULL       = "NULL"
idl.UINT16_MAX = "UINT16_MAX"
idl.INT32_MAX  = "INT32_MAX"
idl.UINT32_MAX = "UINT32_MAX"
idl.UINT8_MAX  = "UINT8_MAX"

return setmetatable(idl , { __index = function (_, keyword)
	error (tostring(keyword) .. " is invalid")
	end})
