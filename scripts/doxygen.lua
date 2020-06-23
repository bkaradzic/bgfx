local doxygen = {}

function doxygen.load(filename)
	local lines = {}
	for line in io.lines(filename) do
		local code, comment = line:match "(.-)%-%-%-[ \t](.*)"
		if code then
			if code == "" then
				line = string.format("comment [[%s]]", comment)
			else
				line = string.format("%s [[%s]]", code, comment)
			end
		end
		lines[#lines+1] = line
	end
	return table.concat(lines, "\n")
end

return doxygen
