function test(...)
	return "Arguments given are "..table.concat({ ... }, ", ")
end