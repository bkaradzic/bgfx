-- Copyright 2019 云风 https://github.com/cloudwu . All rights reserved.
-- License (the same with bgfx) : https://github.com/bkaradzic/bgfx/blob/master/LICENSE

local idl = {}

local all_types = {}

local function typedef(_, typename)
	assert(all_types[typename] == nil, "Duplicate type")
	local t = {}
	all_types[typename] = t
	local function type_attrib(attrib)
		assert(type(attrib) == "table", "type attrib should be a table")
		for _, a in ipairs(attrib) do
			t[a] = true
		end
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

local all_funcs = {}

local function duplicate_arg_name(name)
	error ("Duplicate arg name " .. name)
end

local function funcdef(_, funcname)
	local f = { name = funcname , args = {} }
	all_funcs[#all_funcs+1] = f
	local args
	local function args_desc(obj, args_name)
		obj[args_name] = duplicate_arg_name
		return function (fulltype)
			local arg = {
				name = "_" .. args_name,
				fulltype = fulltype,
			}
			f.args[#f.args+1] = arg
			local function arg_attrib(_, attrib )
				assert(type(attrib) == "table", "Arg attributes should be a table")
				for _, a in ipairs(attrib) do
					arg[a] = true
				end
				return args
			end
			return setmetatable( {} , {
				__index = function(_, name)
					return args_desc(obj, name)
				end
				, __call = arg_attrib } )
		end
	end
	args = setmetatable({}, { __index = args_desc })
	local function rettype(value)
		assert(type(value) == "string", "Need return type")
		f.ret = { fulltype = value }
		return args
	end

	local function funcdef(value)
		if type(value) == "table" then
			for k,v in pairs(value) do
				if type(k) == "number" then
					f[v] = true
				else
					f[k] = v
				end
			end
			return rettype
		end
		return rettype(value)
	end

	local function classfunc(_, methodname)
		f.class = f.name
		f.name = methodname
		return funcdef
	end

	return setmetatable({} , { __index = classfunc, __call = function(_, value) return funcdef(value) end })
end

idl.func = setmetatable({}, { __index = funcdef })
idl.funcs = all_funcs

idl.handle = "handle"
idl.enum = "enum"
idl.out = "out"
idl.const = "const"

return setmetatable(idl , { __index = function (_, keyword)
	error (tostring(keyword) .. " is invalid")
	end})
