
// TODO: requires function for checking existence of dependencies


function namespace(name)
{
	// Ensure all nested namespaces are created only once
	
	var ns_list = name.split(".");
	var parent_ns = window;

	for (var i in ns_list)
	{
		var ns_name = ns_list[i];
		if (!(ns_name in parent_ns))
			parent_ns[ns_name] = { };

		parent_ns = parent_ns[ns_name];
	}
}