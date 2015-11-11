
namespace("LocalStore");


LocalStore.Set = function(class_name, class_id, variable_id, data)
{
	if (typeof(Storage) != "undefined")
	{
		var name = class_name + "_" + class_id + "_" + variable_id;
		localStorage[name] = JSON.stringify(data);
	}
}


LocalStore.Get = function(class_name, class_id, variable_id, default_data)
{
	if (typeof(Storage) != "undefined")
	{
		var name = class_name + "_" + class_id + "_" + variable_id;
		var data = localStorage[name]
		if (data)
			return JSON.parse(data);
	}

	return default_data;
}