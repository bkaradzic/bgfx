
namespace("WM");


WM.ComboBoxPopup = (function()
{
	var body_template_html = "<div class='ComboBoxPopup'></div>";

	var item_template_html = "																	\
		<div class='ComboBoxPopupItem notextsel'>												\
			<div class='ComboBoxPopupItemText'></div>											\
			<div class='ComboBoxPopupItemIcon'><img src='BrowserLibImages/tick.gif'></div>		\
			<div style='clear:both'></div>														\
		</div>";


	function ComboBoxPopup(combo_box)
	{
		this.ComboBox = combo_box;
		this.ParentNode = combo_box.Node;
		this.ValueNodes = [ ];

		// Create the template node
		this.Node = DOM.Node.CreateHTML(body_template_html);

		DOM.Event.AddHandler(this.Node, "mousedown", Bind(SelectItem, this));
		this.CancelDelegate = Bind(this, "Cancel");
	}


	ComboBoxPopup.prototype.SetValues = function(values)
	{
		// Clear existing values
		this.Node.innerHTML = "";

		// Generate HTML nodes for each value
		this.ValueNodes = [ ];
		for (var i in values)
		{
			var item_node = DOM.Node.CreateHTML(item_template_html);
			var text_node = DOM.Node.FindWithClass(item_node, "ComboBoxPopupItemText");

			item_node.Value = values[i];
			text_node.innerHTML = values[i];

			this.Node.appendChild(item_node);
			this.ValueNodes.push(item_node);
		}
	}


	ComboBoxPopup.prototype.Show = function(selection_index)
	{
		// Initially match the position of the parent node
		var pos = DOM.Node.GetPosition(this.ParentNode);
		DOM.Node.SetPosition(this.Node, pos);

		// Take the width/z-index from the parent node
		this.Node.style.width = this.ParentNode.offsetWidth;
		this.Node.style.zIndex = this.ParentNode.style.zIndex + 1;

		// Setup event handlers
		DOM.Event.AddHandler(document.body, "mousedown", this.CancelDelegate);

		// Show the popup so that the HTML layout engine kicks in before
		// the layout info is used below
		this.ParentNode.appendChild(this.Node);

		// Show/hide the tick image based on which node is selected
		for (var i in this.ValueNodes)
		{
			var node = this.ValueNodes[i];
			var icon_node = DOM.Node.FindWithClass(node, "ComboBoxPopupItemIcon");

			if (i == selection_index)
			{
				icon_node.style.display = "block";

				// Also, shift the popup up so that the mouse is over the selected item and is highlighted
				var item_pos = DOM.Node.GetPosition(this.ValueNodes[selection_index]);
				var diff_pos = [ item_pos[0] - pos[0], item_pos[1] - pos[1] ];
				pos = [ pos[0] - diff_pos[0], pos[1] - diff_pos[1] ];
			}
			else
			{
				icon_node.style.display = "none";
			}
		}

		DOM.Node.SetPosition(this.Node, pos);
	}


	ComboBoxPopup.prototype.Hide = function()
	{
		DOM.Event.RemoveHandler(document.body, "mousedown", this.CancelDelegate);
		this.ParentNode.removeChild(this.Node);
	}


	function SelectItem(self, evt)
	{
		// Search for which item node is being clicked on
		var node = DOM.Event.GetNode(evt);
		for (var i in self.ValueNodes)
		{
			var value_node = self.ValueNodes[i];
			if (DOM.Node.Contains(node, value_node))
			{
				// Set the value on the combo box
				self.ComboBox.SetValue(value_node.Value);
				self.Hide();
				break;
			}
		}
	}


	function Cancel(self, evt)
	{
		// Don't cancel if the mouse up is anywhere on the popup or combo box
		var node = DOM.Event.GetNode(evt);
		if (!DOM.Node.Contains(node, self.Node) &&
			!DOM.Node.Contains(node, self.ParentNode))
		{
			self.Hide();
		}


		DOM.Event.StopAll(evt);
	}


	return ComboBoxPopup;
})();


WM.ComboBox = (function()
{
	var template_html = "																\
		<div class='ComboBox'>															\
			<div class='ComboBoxText notextsel'></div>									\
			<div class='ComboBoxIcon'><img src='BrowserLibImages/up_down.gif'></div>	\
			<div style='clear:both'></div>												\
		</div>";


	function ComboBox()
	{
		this.OnChange = null;

		// Create the template node and locate key nodes
		this.Node = DOM.Node.CreateHTML(template_html);
		this.TextNode = DOM.Node.FindWithClass(this.Node, "ComboBoxText");

		// Create a reusable popup
		this.Popup = new WM.ComboBoxPopup(this);

		// Set an empty set of values
		this.SetValues([]);
		this.SetValue("&lt;empty&gt;");

		// Create the mouse press event handlers
		DOM.Event.AddHandler(this.Node, "mousedown", Bind(OnMouseDown, this));
		this.OnMouseOutDelegate = Bind(OnMouseUp, this, false);
		this.OnMouseUpDelegate = Bind(OnMouseUp, this, true);
	}


	ComboBox.prototype.SetOnChange = function(on_change)
	{
		this.OnChange = on_change;
	}


	ComboBox.prototype.SetValues = function(values)
	{
		this.Values = values;
		this.Popup.SetValues(values);
	}


	ComboBox.prototype.SetValue = function(value)
	{
		// Set the value and its HTML rep
		var old_value = this.Value;
		this.Value = value;
		this.TextNode.innerHTML = value;

		// Call change handler
		if (this.OnChange)
			this.OnChange(value, old_value);
	}


	ComboBox.prototype.GetValue = function()
	{
		return this.Value;
	}


	function OnMouseDown(self, evt)
	{
		// If this check isn't made, the click will trigger from the popup, too
		var node = DOM.Event.GetNode(evt);
		if (DOM.Node.Contains(node, self.Node))
		{
			// Add the depression class and activate release handlers
			DOM.Node.AddClass(self.Node, "ComboBoxPressed");
			DOM.Event.AddHandler(self.Node, "mouseout", self.OnMouseOutDelegate);
			DOM.Event.AddHandler(self.Node, "mouseup", self.OnMouseUpDelegate);

			DOM.Event.StopAll(evt);
		}
	}


	function OnMouseUp(self, confirm, evt)
	{
		// Remove depression class and remove release handlers
		DOM.Node.RemoveClass(self.Node, "ComboBoxPressed");
		DOM.Event.RemoveHandler(self.Node, "mouseout", self.OnMouseOutDelegate);
		DOM.Event.RemoveHandler(self.Node, "mouseup", self.OnMouseUpDelegate);

		// If this is a confirmed press and there are some values in the list, show the popup
		if (confirm && self.Values.length > 0)
		{
			var selection_index = self.Values.indexOf(self.Value);
			self.Popup.Show(selection_index);
		}

		DOM.Event.StopAll(evt);
	}


	return ComboBox;
})();
