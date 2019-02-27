-- Copyright 2019 云风 https://github.com/cloudwu . All rights reserved.
-- License (the same with bgfx) : https://github.com/bkaradzic/bgfx/blob/master/LICENSE

local idl     = require "idl"
local codegen = require "codegen"

assert(loadfile("bgfx.idl" , "t", idl))()

codegen.nameconversion(idl.types, idl.funcs)

local code_temp_include = [[
/*
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

/*
 *
 * AUTO GENERATED! DO NOT EDIT!
 *
 */

$c99decl
/**/
typedef struct bgfx_interface_vtbl
{
	$interface_struct
} bgfx_interface_vtbl_t;
]]

local code_temp_impl = [[
/*
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

/*
 *
 * AUTO GENERATED! DO NOT EDIT!
 *
 */

$c99
/**/
BGFX_C_API bgfx_interface_vtbl_t* bgfx_get_interface(uint32_t _version)
{
	if (_version == BGFX_API_VERSION)
	{
		static bgfx_interface_vtbl_t s_bgfx_interface =
		{
			$interface_import
		};

		return &s_bgfx_interface;
	}

	return NULL;
}
]]

local function codes()
	local temp = {}
	local action = {
		c99 = "\n",
		c99decl = "\n",
		interface_struct = "\n\t",
		interface_import = ",\n\t\t\t",
	}
	for k in pairs(action) do
		temp[k] = {}
	end
	for _, f in ipairs(idl.funcs) do
		for k in pairs(action) do
			table.insert(temp[k], (codegen["gen_"..k](f)))
		end
	end

	for k, ident in pairs(action) do
		temp[k] = table.concat(temp[k], ident)
	end

	return temp
end

local codes_tbl = codes()

for filename, temp in pairs {
	["../include/bgfx/c99/bgfx.idl.h"] = code_temp_include ,
	["../src/bgfx.idl.inl"] = code_temp_impl } do

	print ("Generate " .. filename)
	local out = io.open(filename, "wb")
	out:write((temp:gsub("$([%l%d_]+)", codes_tbl)))
	out:close()
end
