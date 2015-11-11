
namespace("WM");


WM.GridRows = (function()
{
	function GridRows(parent_object)
	{
		this.ParentObject = parent_object;

		// Array of rows in the order they were added
		this.Rows = [ ];

		// Collection of custom row indexes for fast lookup
		this.Indexes = { };
	}


	GridRows.prototype.AddIndex = function(cell_field_name)
	{
		var index = { };

		// Go through existing rows and add to the index
		for (var i in this.Rows)
		{
			var row = this.Rows[i];
			if (cell_field_name in row.CellData)
			{
				var cell_field = row.CellData[cell_field_name];
				index[cell_field] = row;
			}
		}

		this.Indexes[cell_field_name] = index;
	}


	GridRows.prototype.ClearIndex = function(index_name)
	{
		this.Indexes[index_name] = { };
	}

	GridRows.prototype.AddRowToIndex = function(index_name, cell_data, row)
	{
		this.Indexes[index_name][cell_data] = row;
	}


	GridRows.prototype.Add = function(cell_data, row_classes, cell_classes)
	{
		var row = new WM.GridRow(this.ParentObject, cell_data, row_classes, cell_classes);
		this.Rows.push(row);
		return row;
	}


	GridRows.prototype.GetBy = function(cell_field_name, cell_data)
	{
		var index = this.Indexes[cell_field_name];
		return index[cell_data];
	}


	GridRows.prototype.Clear = function()
	{
		// Remove all node references from the parent
		for (var i in this.Rows)
		{
			var row = this.Rows[i];
			row.Parent.BodyNode.removeChild(row.Node);
		}

		// Clear all indexes
		for (var i in this.Indexes)
			this.Indexes[i] = { };

		this.Rows = [ ];
	}


	return GridRows;
})();


WM.GridRow = (function()
{
	var template_html = "<div class='GridRow'></div>";


	//
	// 'cell_data' is an object with a variable number of fields.
	// Any fields prefixed with an underscore are hidden.
	//
	function GridRow(parent, cell_data, row_classes, cell_classes)
	{
		// Setup data
		this.Parent = parent;
		this.IsOpen = true;
		this.AnimHandle = null;
		this.Rows = new WM.GridRows(this);
		this.CellData = cell_data;
		this.CellNodes = { }

		// Create the main row node
		this.Node = DOM.Node.CreateHTML(template_html);
		if (row_classes)
			DOM.Node.AddClass(this.Node, row_classes);

		// Embed a pointer to the row in the root node so that it can be clicked
		this.Node.GridRow = this;

		// Create nodes for each required cell
		for (var attr in this.CellData)
		{
			if (this.CellData.hasOwnProperty(attr))
			{
				var data = this.CellData[attr];

				// Update any grid row index references
				if (attr in parent.Rows.Indexes)
					parent.Rows.AddRowToIndex(attr, data, this);

				// Hide any cells with underscore prefixes
				if (attr[0] == "_")
					continue;

				// Create a node for the cell and add any custom classes
				var node = DOM.Node.AppendHTML(this.Node, "<div class='GridRowCell'></div>");
				if (cell_classes && attr in cell_classes)
					DOM.Node.AddClass(node, cell_classes[attr]);
				this.CellNodes[attr] = node;

				// If this is a Window Control, add its node to the cell
				if (data instanceof Object && "Node" in data && DOM.Node.IsNode(data.Node))
				{
					data.ParentNode = node;
					node.appendChild(data.Node);
				}

				else
				{
					// Otherwise just assign the data as text
					node.innerHTML = data;
				}
			}
		}

		// Add the body node for any children
		DOM.Node.AppendClearFloat(this.Node);
		this.BodyNode = DOM.Node.AppendHTML(this.Node, "<div class='GridRowBody'></div>");

		// Add the row to the parent
		this.Parent.BodyNode.appendChild(this.Node);
	}


	GridRow.prototype.Open = function()
	{
		// Don't allow open while animating
		if (this.AnimHandle == null || this.AnimHandle.Complete)
		{
			this.IsOpen = true;

			// Kick off open animation
			var node = this.BodyNode;
			this.AnimHandle = Anim.Animate(
				function (val) { DOM.Node.SetHeight(node, val) },
				0, this.Height, 0.2);
		}
	}


	GridRow.prototype.Close = function()
	{
		// Don't allow close while animating
		if (this.AnimHandle == null || this.AnimHandle.Complete)
		{
			this.IsOpen = false;

			// Record height for the next open request
			this.Height = this.BodyNode.offsetHeight;

			// Kick off close animation
			var node = this.BodyNode;
			this.AnimHandle = Anim.Animate(
				function (val) { DOM.Node.SetHeight(node, val) },
				this.Height, 0, 0.2);
		}
	}


	GridRow.prototype.Toggle = function()
	{
		if (this.IsOpen)
			this.Close();
		else
			this.Open();
	}


	return GridRow;
})();


WM.Grid = (function()
{
	var template_html = "					\
		<div class='Grid'>					\
			<div class='GridBody'></div>	\
		</div>";


	function Grid(x, y, width, height)
	{
		this.Rows = new WM.GridRows(this);

		this.Node = DOM.Node.CreateHTML(template_html);
		this.BodyNode = DOM.Node.FindWithClass(this.Node, "GridBody");

		DOM.Node.SetPosition(this.Node, [ x, y ]);
		DOM.Node.SetSize(this.Node, [ width, height ]);

		DOM.Event.AddHandler(this.Node, "dblclick", OnDblClick);

		var mouse_wheel_event = (/Firefox/i.test(navigator.userAgent)) ? "DOMMouseScroll" : "mousewheel";
		DOM.Event.AddHandler(this.Node, mouse_wheel_event, Bind(OnMouseScroll, this));
	}


	function OnDblClick(evt)
	{
		// Clicked on a header?
		var node = DOM.Event.GetNode(evt);
		if (DOM.Node.HasClass(node, "GridRowName"))
		{
			// Toggle rows open/close
			var row = node.parentNode.GridRow;
			if (row)
				row.Toggle();
		}
	}


	function OnMouseScroll(self, evt)
	{
		var mouse_state = new Mouse.State(evt);
		self.Node.scrollTop -= mouse_state.WheelDelta * 20;
	}


	return Grid;
})();
