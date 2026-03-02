local codegen = require "codegen"

local gen = {}

local function to_underscorecase(name)
	local tmp = {}
	for v in name:gmatch "[_%u][%l%d]*" do
		if v:byte() == 95 then -- '_'
			v = v:sub(2)
		end
		tmp[#tmp+1] = v
	end
	return table.concat(tmp, "_")
end

function gen.gen()
	local idl = codegen.idl()

	-- Count C++ name occurrences for overload detection
	-- Only count non-conly, non-class functions (free functions)
	local cpp_name_count = {}
	for _, f in ipairs(idl.funcs) do
		if not f.conly and not f.class then
			cpp_name_count[f.name] = (cpp_name_count[f.name] or 0) + 1
		end
	end

	-- Collect section items by section id from declarations
	local section_items = {}

	for _, t in ipairs(idl.types) do
		if t.section then
			if not section_items[t.section] then
				section_items[t.section] = {}
			end
			local kind
			if t.flag then
				kind = "flag"
			elseif t.struct or t.enum then
				kind = "struct"
			end
			if kind then
				table.insert(section_items[t.section], {
					kind = kind,
					item = t,
					order = t._order or 0,
				})
			end
		end
	end

	for _, f in ipairs(idl.funcs) do
		if f.section and not f.conly and not f.class then
			if not section_items[f.section] then
				section_items[f.section] = {}
			end
			table.insert(section_items[f.section], {
				kind = "func",
				item = f,
				order = f._order or 0,
			})
		end
	end

	for _, items in pairs(section_items) do
		table.sort(items, function(a, b) return a.order < b.order end)
	end

	-- Build C++ function signature
	local function build_signature(f)
		local parts = {}
		for _, arg in ipairs(f.args) do
			local s = arg.fulltype .. " " .. arg.name
			if arg.array then
				s = s .. arg.array
			end
			if arg.default then
				s = s .. " = " .. arg.default
			end
			parts[#parts+1] = s
		end
		return table.concat(parts, ", ")
	end

	-- Get BGFX_ define name for a flag item
	local function get_define_name(flag_type, flag_item)
		local prefix = "BGFX_" .. (flag_type.cname or to_underscorecase(flag_type.name):upper())
		local suffix
		if flag_item.cname then
			suffix = flag_item.cname
		else
			suffix = to_underscorecase(flag_item.name):upper()
		end
		return prefix .. "_" .. suffix
	end

	local underlines = {
		[0] = "=",
		[1] = "-",
		[2] = "~",
		[3] = "*",
		[4] = '"',
	}

	local r = {}
	local function emit(s)
		r[#r+1] = s or ""
	end

	-- Determine leaf sections and build parent paths for item lookup.
	-- A leaf section is one not immediately followed by a deeper-level section.
	-- The path is "parent_title/title" (used to disambiguate duplicate titles).
	local parent_at_level = {}
	for i, sec in ipairs(idl.sections) do
		parent_at_level[sec.level] = sec.title
		local parent = parent_at_level[sec.level - 1]
		sec._path = parent and (parent .. "/" .. sec.title) or sec.title
		sec._is_leaf = true
		if i > 1 then
			local prev = idl.sections[i - 1]
			if prev.level < sec.level then
				prev._is_leaf = false
			end
		end
	end

	for _, sec in ipairs(idl.sections) do
		if sec.level > 0 then
			emit()
		end

		-- Section header
		emit(sec.title)
		emit(string.rep(underlines[sec.level], #sec.title))

		-- Description (skip first line if it matches the section title)
		if sec.desc then
			local start_idx = 1
			if sec.desc[1] == sec.title then
				start_idx = 2
			end
			-- Skip leading empty lines
			while start_idx <= #sec.desc and sec.desc[start_idx] == "" do
				start_idx = start_idx + 1
			end
			if start_idx <= #sec.desc then
				emit()
				local in_note = false
				for i = start_idx, #sec.desc do
					local line = sec.desc[i]
					local remarks_text = line:match "^@remarks%s+(.*)"
					if remarks_text then
						emit(".. note::")
						emit()
						emit("    " .. remarks_text)
						in_note = true
					elseif in_note then
						if line == "" then
							emit()
						else
							emit("    " .. line)
						end
					else
						emit(line)
					end
				end
			end
		end

		-- Items (only for leaf sections)
		if sec._is_leaf then
			local items = section_items[sec._path] or section_items[sec.title] or {}
			local prev_kind = nil

			for _, entry in ipairs(items) do
				if entry.kind == "func" then
					local f = entry.item
					local count = cpp_name_count[f.name] or 0
					if prev_kind ~= "func" then
						emit()
					end
					if count > 1 then
						emit(".. doxygenfunction:: bgfx::" .. f.name .. "(" .. build_signature(f) .. ")")
					else
						emit(".. doxygenfunction:: bgfx::" .. f.name)
					end
					prev_kind = "func"
				elseif entry.kind == "struct" then
					local t = entry.item
					emit()
					emit(".. doxygenstruct:: bgfx::" .. (t.typename or t.name))
					emit("    :members:")
					prev_kind = "struct"
				elseif entry.kind == "flag" then
					local t = entry.item
					emit()
					if t.label then
						emit("**" .. t.label .. "**")
						emit()
					end
					for _, fitem in ipairs(t.flag) do
						emit(".. doxygendefine:: " .. get_define_name(t, fitem))
					end
					prev_kind = "flag"
				end
			end
		end
	end

	emit()

	return table.concat(r, "\n") .. "\n"
end

function gen.write(codes, outputfile)
	local out = assert(io.open(outputfile, "wb"))
	out:write(codes)
	out:close()
	print("Generating: " .. outputfile)
end

if (...) == nil then
	-- run `lua docs-rst.lua` in command line
	print(gen.gen())
end

return gen
