local codegen = require "codegen"
local idl = codegen.idl "bgfx.idl"

local gen = {}

local function has_suffix(str, suffix)
	return suffix == "" or str:sub(-#suffix) == suffix
end

local function py_ident(name)
	name = name:gsub("[^%w_]", "_")
	if name:match("^%d") then
		name = "_" .. name
	end

	local keywords = {
		["False"] = true, ["None"] = true, ["True"] = true,
		["and"] = true, ["as"] = true, ["assert"] = true, ["async"] = true,
		["await"] = true, ["break"] = true, ["class"] = true, ["continue"] = true,
		["def"] = true, ["del"] = true, ["elif"] = true, ["else"] = true,
		["except"] = true, ["finally"] = true, ["for"] = true, ["from"] = true,
		["global"] = true, ["if"] = true, ["import"] = true, ["in"] = true,
		["is"] = true, ["lambda"] = true, ["nonlocal"] = true, ["not"] = true,
		["or"] = true, ["pass"] = true, ["raise"] = true, ["return"] = true,
		["try"] = true, ["while"] = true, ["with"] = true, ["yield"] = true,
	}

	if keywords[name] then
		name = name .. "_"
	end
	return name
end

local function python_type_name(typ)
	if typ.enum then
		return py_ident(typ.typename)
	elseif typ.namespace then
		return py_ident(typ.namespace .. typ.name)
	else
		return py_ident(typ.name:gsub("::Enum$", ""))
	end
end

local function append(out, ...)
	for _, value in ipairs({...}) do
		out[#out + 1] = value
	end
end

local ctype_map = {
	["bool"] = "ctypes.c_bool",
	["char"] = "ctypes.c_char",
	["float"] = "ctypes.c_float",
	["int8_t"] = "ctypes.c_int8",
	["int16_t"] = "ctypes.c_int16",
	["int32_t"] = "ctypes.c_int32",
	["int64_t"] = "ctypes.c_int64",
	["uint8_t"] = "ctypes.c_uint8",
	["uint16_t"] = "ctypes.c_uint16",
	["uint32_t"] = "ctypes.c_uint32",
	["uint64_t"] = "ctypes.c_uint64",
	["uintptr_t"] = "ctypes.c_size_t",
	["bgfx_view_id_t"] = "ctypes.c_uint16",
	["va_list"] = "ctypes.c_void_p",
}

local opaque_types = {
	["bgfx_allocator_interface_t"] = true,
	["bgfx_callback_interface_t"] = true,
}

local enum_counts = {}

local stub_primitive_map = {
	["bool"] = "bool",
	["char"] = "bytes",
	["float"] = "float",
	["int8_t"] = "int",
	["int16_t"] = "int",
	["int32_t"] = "int",
	["int64_t"] = "int",
	["uint8_t"] = "int",
	["uint16_t"] = "int",
	["uint32_t"] = "int",
	["uint64_t"] = "int",
	["uintptr_t"] = "int",
	["bgfx_view_id_t"] = "int",
	["va_list"] = "Any",
}

local stub_type_info = {}

for _, typ in ipairs(idl.types) do
	if typ.enum then
		ctype_map[typ.cname] = "ctypes.c_int"
		enum_counts[typ.typename] = #typ.enum
		stub_type_info[typ.cname] = { kind = "enum", name = python_type_name(typ) }
	elseif typ.handle then
		ctype_map[typ.cname] = python_type_name(typ)
		stub_type_info[typ.cname] = { kind = "handle", name = python_type_name(typ) }
	elseif typ.struct then
		ctype_map[typ.cname] = python_type_name(typ)
		stub_type_info[typ.cname] = { kind = "struct", name = python_type_name(typ) }
	elseif typ.args and typ.ret then
		ctype_map[typ.cname] = python_type_name(typ)
		stub_type_info[typ.cname] = { kind = "funcptr", name = python_type_name(typ) }
	end
end

local function normalize_ctype(ctype)
	ctype = ctype:gsub("%s+", " ")
	ctype = ctype:gsub("%s*%*%s*", "*")
	ctype = ctype:match("^%s*(.-)%s*$")
	return ctype
end

local function convert_ctype(arg, array_as_pointer)
	if arg.ctype == "..." then
		return nil
	end

	local ctype = normalize_ctype(arg.ctype)
	local is_const = ctype:match("^const ") ~= nil
	ctype = ctype:gsub("^const%s+", "")

	local pointer_count = 0
	while ctype:sub(-1) == "*" do
		pointer_count = pointer_count + 1
		ctype = ctype:sub(1, -2)
	end

	if arg.array and array_as_pointer then
		pointer_count = pointer_count + 1
	end

	if ctype == "void" then
		if pointer_count == 0 then
			return "None"
		end

		local result = "ctypes.c_void_p"
		for _ = 2, pointer_count do
			result = "ctypes.POINTER(" .. result .. ")"
		end
		return result
	end

	if ctype == "char" and pointer_count == 1 and is_const then
		return "ctypes.c_char_p"
	end

	if opaque_types[ctype] and pointer_count > 0 then
		local result = "ctypes.c_void_p"
		for _ = 2, pointer_count do
			result = "ctypes.POINTER(" .. result .. ")"
		end
		return result
	end

	local result = ctype_map[ctype]
	assert(result, "Unsupported C type: " .. arg.ctype)

	for _ = 1, pointer_count do
		result = "ctypes.POINTER(" .. result .. ")"
	end

	return result
end

local function convert_stub_type(arg, array_as_pointer, context)
	if arg.ctype == "..." then
		return "Any"
	end

	local ctype = normalize_ctype(arg.ctype)
	local is_const = ctype:match("^const ") ~= nil
	ctype = ctype:gsub("^const%s+", "")

	local pointer_count = 0
	while ctype:sub(-1) == "*" do
		pointer_count = pointer_count + 1
		ctype = ctype:sub(1, -2)
	end

	if arg.array and array_as_pointer then
		pointer_count = pointer_count + 1
	end

	if ctype == "void" then
		if pointer_count == 0 then
			return "None"
		end
		return "Any"
	end

	if ctype == "char" and pointer_count == 1 and is_const then
		return "Optional[bytes]"
	end

	local info = stub_type_info[ctype]
	if pointer_count > 0 then
		if pointer_count == 1 and info and (info.kind == "struct" or info.kind == "handle") then
			if context == "arg" then
				return "Optional[Union[" .. info.name .. ", _Pointer[" .. info.name .. "], ctypes.Array]]"
			end
			return "_Pointer[" .. info.name .. "]"
		end
		return "Any"
	end

	if info then
		if info.kind == "enum" then
			if context == "arg" then
				return "Union[" .. info.name .. ", int]"
			end
			return "int"
		elseif info.kind == "funcptr" then
			return "Any"
		end
		return info.name
	end

	return assert(stub_primitive_map[ctype], "Unsupported Python stub type: " .. arg.ctype)
end

local function convert_stub_field(member)
	if member.array then
		local ctype = normalize_ctype(member.ctype):gsub("^const%s+", "")
		if ctype == "char" then
			return "bytes"
		end
		return "ctypes.Array"
	end
	return convert_stub_type(member, false, "field")
end

local function array_length(member)
	local number = member.array:match("^%[%s*(%d+)%s*%]$")
	if number then
		return tonumber(number)
	end

	local enum_name, enum_item = member.array:match("^%[%s*([%w_]+)::([%w_]+)%s*%]$")
	assert(enum_name and enum_item == "Count", "Unsupported array expression: " .. member.array)

	local count = enum_counts[enum_name]
	assert(count, "Unknown enum in array expression: " .. enum_name)
	return count
end

local function comment_lines(out, comments, indent)
	if comments == nil then
		return
	end
	indent = indent or ""
	for _, line in ipairs(comments) do
		append(out, indent .. "# " .. line)
	end
end

local function gen_enums(out, comments)
 	for _, typ in ipairs(idl.types) do
 		if typ.enum then
			if comments then
				comment_lines(out, typ.comments)
			end
			append(out, "class " .. python_type_name(typ) .. "(enum.IntEnum):")

			for index, item in ipairs(typ.enum) do
				if comments then
					comment_lines(out, item.comment, "\t")
				end
 				append(out, string.format("\t%s = %d", py_ident(item.name), index - 1))
 			end
			append(out, string.format("\tCount = %d", #typ.enum), "")
 		end
	end
end

local combined_names = {
	State = true,
	Stencil = true,
	Buffer = true,
	Texture = true,
	Sampler = true,
	Reset = true,
}

local function flag_value(item, lookup)
	if item.value ~= nil then
		return item.value
	end

	local value = 0
	for _, name in ipairs(item) do
		local part = assert(lookup[name], "Undefined combined flag " .. name)
		value = value | part
	end
	return value
end

local function emit_flag_class(out, name, items, comments)
 	append(out, "class " .. py_ident(name) .. "(enum.IntFlag):")

 	if #items == 0 then
 		append(out, "\tpass", "")
 		return
 	end

 	for _, item in ipairs(items) do
		if comments then
			comment_lines(out, item.comment, "\t")
		end
 		append(out, string.format("\t%s = 0x%x", py_ident(item.name), item.value))
 	end

 	append(out, "")
 end

local function gen_flags(out, comments)
	local combined = {}
	local standalone = {}

	for name in pairs(combined_names) do
		combined[name] = { lookup = {}, items = {} }
	end

	for _, typ in ipairs(idl.types) do
		if typ.flag then
			local prefix, suffix = typ.name:match("^(%u%l+)(.*)$")
			local target = prefix and combined[prefix] or nil

			if target then
				for _, item in ipairs(typ.flag) do
					local member_name = suffix .. item.name:gsub("_", "")
					local value = item.value
					if value == nil then
						value = 0
						for _, part in ipairs(item) do
							value = value | assert(target.lookup[suffix .. part],
								part .. " is not defined for " .. member_name)
						end
					end

					target.lookup[member_name] = value
					target.items[#target.items + 1] = {
						name = member_name,
						value = value,
						comment = item.comment,
					}
				end

				if typ.shift ~= nil then
					local name = suffix .. "Shift"
					target.lookup[name] = typ.shift
					target.items[#target.items + 1] = {
						name = name,
						value = typ.shift,
						comment = typ.comments,
					}
				end

				if typ.mask ~= nil then
					local name = suffix .. "Mask"
					target.lookup[name] = typ.mask
					target.items[#target.items + 1] = {
						name = name,
						value = typ.mask,
						comment = typ.comments,
					}
				end
			else
				local lookup = {}
				local items = {}

				for _, item in ipairs(typ.flag) do
					local value = flag_value(item, lookup)
					lookup[item.name] = value
					items[#items + 1] = {
						name = item.name,
						value = value,
						comment = item.comment,
					}
				end

				if typ.shift ~= nil then
					items[#items + 1] = {
						name = "Shift",
						value = typ.shift,
						comment = typ.comments,
					}
				end

				if typ.mask ~= nil then
					items[#items + 1] = {
						name = "Mask",
						value = typ.mask,
						comment = typ.comments,
					}
				end

				standalone[#standalone + 1] = {
					name = typ.name .. "Flags",
					items = items,
				}
			end
		end
	end

	for _, name in ipairs({ "State", "Stencil", "Buffer", "Texture", "Sampler", "Reset" }) do
		emit_flag_class(out, name .. "Flags", combined[name].items, comments)
 	end

 	for _, flag in ipairs(standalone) do
		emit_flag_class(out, flag.name, flag.items, comments)
 	end
end

local function gen_struct_declarations(out, comments)
	for _, typ in ipairs(idl.types) do
		if typ.handle then
			append(out,
				"class " .. python_type_name(typ) .. "(ctypes.Structure):",
				typ.tagged
					and "\t_fields_ = [(\"idx\", ctypes.c_uint16), (\"type\", ctypes.c_uint16)]"
					or  "\t_fields_ = [(\"idx\", ctypes.c_uint16)]",
				"",
				"\t@property",
				"\tdef valid(self):",
				"\t\treturn self.idx != 0xffff",
				""
			)
 		elseif typ.struct then
			if comments then
				comment_lines(out, typ.comments)
			end
 			append(out, "class " .. python_type_name(typ) .. "(ctypes.Structure):", "\tpass", "")
 		end
 	end
 end

local function gen_funcptrs(out)
	for _, typ in ipairs(idl.types) do
		if typ.args and typ.ret then
			local args = {}
			for _, arg in ipairs(typ.args) do
				if arg.ctype ~= "..." then
					args[#args + 1] = convert_ctype(arg, true)
				end
			end

			local ret = convert_ctype(typ.ret, true)
			local params = ""
			if #args > 0 then
				params = ", " .. table.concat(args, ", ")
			end

			append(out,
				python_type_name(typ) .. " = ctypes.CFUNCTYPE(" .. ret .. params .. ")",
				""
			)
		end
	end
end

local function gen_struct_fields(out)
	for _, typ in ipairs(idl.types) do
		if typ.struct and #typ.struct > 0 then
			append(out, python_type_name(typ) .. "._fields_ = [")

			for _, member in ipairs(typ.struct) do
				local ctype = convert_ctype(member, false)
				if member.array then
					ctype = "(" .. ctype .. " * " .. array_length(member) .. ")"
				end

				append(out, string.format("\t(%q, %s),", member.name, ctype))
			end

			append(out, "]", "")
		end
	end
end

local function gen_stub_structs(out)
	for _, typ in ipairs(idl.types) do
		if typ.handle then
			append(out,
				"class " .. python_type_name(typ) .. "(ctypes.Structure):",
				"\tidx: int"
			)

			if typ.tagged then
				append(out, "\ttype: int")
			end

			append(out,
				"",
				"\t@property",
				"\tdef valid(self) -> bool: ...",
				""
			)

		elseif typ.struct then
			comment_lines(out, typ.comments)
			append(out, "class " .. python_type_name(typ) .. "(ctypes.Structure):")

			if #typ.struct == 0 then
				append(out, "\tpass")
			else
				for _, member in ipairs(typ.struct) do
					comment_lines(out, member.comment, "\t")
					append(
						out,
						"\t" .. py_ident(member.name) .. ": "
							.. convert_stub_field(member)
					)
				end
			end

			append(out, "")
		end
	end
end

local function gen_stub_funcptrs(out)
	for _, typ in ipairs(idl.types) do
		if typ.args and typ.ret then
			comment_lines(out, typ.comments)
			append(out, python_type_name(typ) .. ": Any", "")
		end
	end
end

local function should_emit_function(func)
	if func.cpponly then
		return false
	end
	if func.cppinline and not func.conly then
		return false
	end
	return true
end

local function gen_functions(out)
	append(out,
		"_lib = None",
		"",
		"def load(path):",
		"\tglobal _lib",
		"\t_lib = ctypes.CDLL(path)",
		"\t_bind(_lib)",
		"\treturn _lib",
		"",
		"def _bind(lib):"
	)

	local any = false
	for _, func in ipairs(idl.funcs) do
		if should_emit_function(func) and not func.vararg then
			any = true

			local args = {}
			if func.this ~= nil then
				args[#args + 1] = convert_ctype(func.this_type, true)
			end

			for _, arg in ipairs(func.args) do
				if arg.ctype ~= "..." then
					args[#args + 1] = convert_ctype(arg, true)
				end
			end

			local restype = convert_ctype(func.ret, true)
			local name = "bgfx_" .. func.cname

			append(out,
				"\tglobal " .. name,
				"\t" .. name .. " = lib." .. name,
				"\t" .. name .. ".argtypes = [" .. table.concat(args, ", ") .. "]",
				"\t" .. name .. ".restype = " .. restype
			)
		end
	end

	if not any then
		append(out, "\tpass")
	end

	append(out, "")
end

local function stub_signature(out, name, args, restype)
	if #args == 0 then
		append(out, "def " .. name .. "() -> " .. restype .. ": ...")
	elseif #args <= 5 then
		append(out, "def " .. name .. "(" .. table.concat(args, ", ") .. ", /) -> " .. restype .. ": ...")
	else
		append(out, "def " .. name .. "(")
		for _, arg in ipairs(args) do
			append(out, "\t" .. arg .. ",")
		end
		append(out, "\t/,", ") -> " .. restype .. ": ...")
	end
end

local function gen_stub_functions(out)
	append(out,
		"def load(path: Union[str, bytes]) -> ctypes.CDLL: ...",
		""
	)

	for _, func in ipairs(idl.funcs) do
		if should_emit_function(func) and not func.vararg then
			local args = {}
			if func.this ~= nil then
				args[#args + 1] = "_this: " .. convert_stub_type(func.this_type, true, "arg")
			end

			for _, arg in ipairs(func.args) do
				if arg.ctype ~= "..." then
					args[#args + 1] = py_ident(arg.name) .. ": " .. convert_stub_type(arg, true, "arg")
				end
			end

			comment_lines(out, func.comments)
			stub_signature(out, "bgfx_" .. func.cname, args, convert_stub_type(func.ret, true, "return"))
			append(out, "")
		end
	end
end

function gen.gen()
	local out = {
		"# Copyright 2011-2026 Branimir Karadzic. All rights reserved.",
		"# License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE",
		"",
		"#",
		"# AUTO GENERATED! DO NOT EDIT!",
		"#",
		"",
		"import ctypes",
		"import enum",
		"",
		"ViewId = ctypes.c_uint16",
		"",
	}

	gen_enums(out, false)
	gen_flags(out, false)
	gen_struct_declarations(out, false)
	gen_funcptrs(out)
	gen_struct_fields(out)
	gen_functions(out)

	return table.concat(out, "\n")
end

function gen.gen_pyi()
	local out = {
		"# Copyright 2011-2026 Branimir Karadzic. All rights reserved.",
		"# License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE",
		"",
		"#",
		"# AUTO GENERATED! DO NOT EDIT!",
		"#",
		"",
		"import ctypes",
		"import enum",
		"from typing import Any, Optional, Protocol, TypeVar, Union",
		"",
		"ViewId = ctypes.c_uint16",
		"",
		"_T = TypeVar(\"_T\", covariant=True)",
		"",
		"class _Pointer(Protocol[_T]):",
		"\t@property",
		"\tdef contents(self) -> _T: ...",
		"",
	}

	gen_enums(out, true)
	gen_flags(out, true)
	gen_stub_structs(out)
	gen_stub_funcptrs(out)
	gen_stub_functions(out)

	return table.concat(out, "\n")
end

function gen.write(codes, outputfile)
	local out = assert(io.open(outputfile, "wb"))
	out:write(codes)
	out:close()
	print("Generating: " .. outputfile)
end

if (...) == nil then
	print(gen.gen())
end

return gen
