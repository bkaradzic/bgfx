
namespace("WM");


WM.Treeview = (function()
{
	var Margin = 10;


	var tree_template_html = "																							\
		<div class='Treeview'>																							\
			<div class='TreeviewItemChildren' style='width:90%;float:left'></div>										\
			<div class='TreeviewScrollbarInset'>																		\
				<div class='TreeviewScrollbar'></div>																	\
			</div>																										\
			<div style='clear:both'></div>																				\
		</div>";


	var item_template_html = "																							\
		<div class='TreeViewItem basicfont notextsel'>																	\
			<img src='' class='TreeviewItemImage'>																		\
			<div class='TreeviewItemText'></div>																		\
			<div style='clear:both'></div>																				\
			<div class='TreeviewItemChildren'></div>																	\
			<div style='clear:both'></div>																				\
		</div>";


	// TODO: Remove parent_node (required for stuff that doesn't use the WM yet)
	function Treeview(x, y, width, height, parent_node)
	{
		// Cache initialisation options
		this.ParentNode = parent_node;
		this.Position = [ x, y ];
		this.Size = [ width, height ];

		this.Node = null;
		this.ScrollbarNode = null;
		this.SelectedItem = null;
		this.ContentsNode = null;

		// Setup options
		this.HighlightOnHover = false;
		this.EnableScrollbar = true;
		this.HorizontalLayoutDepth = 1;

		// Generate an empty tree
		this.Clear();
	}


	Treeview.prototype.SetHighlightOnHover = function(highlight)
	{
		this.HighlightOnHover = highlight;
	}


	Treeview.prototype.SetEnableScrollbar = function(enable)
	{
		this.EnableScrollbar = enable;
	}


	Treeview.prototype.SetHorizontalLayoutDepth = function(depth)
	{
		this.HorizontalLayoutDepth = depth;
	}


	Treeview.prototype.SetNodeSelectedHandler = function(handler)
	{
		this.NodeSelectedHandler = handler;
	}


	Treeview.prototype.Clear = function()
	{
		this.RootItem = new WM.TreeviewItem(this, null, null, null, null);
		this.GenerateHTML();
	}


	Treeview.prototype.Root = function()
	{
		return this.RootItem;
	}


	Treeview.prototype.ClearSelection = function()
	{
		if (this.SelectedItem != null)
		{
			DOM.Node.RemoveClass(this.SelectedItem.Node, "TreeviewItemSelected");
			this.SelectedItem = null;
		}
	}


	Treeview.prototype.SelectItem = function(item, mouse_pos)
	{
		// Notify the select handler
		if (this.NodeSelectedHandler)
			this.NodeSelectedHandler(item.Node, this.SelectedItem, item, mouse_pos);

		// Remove highlight from the old selection
		this.ClearSelection();

		// Swap in new selection and apply highlight
		this.SelectedItem = item;
		DOM.Node.AddClass(this.SelectedItem.Node, "TreeviewItemSelected");
	}


	Treeview.prototype.GenerateHTML = function()
	{
		// Clone the template and locate important nodes
		var old_node = this.Node;
		this.Node = DOM.Node.CreateHTML(tree_template_html);
		this.ChildrenNode = DOM.Node.FindWithClass(this.Node, "TreeviewItemChildren");
		this.ScrollbarNode = DOM.Node.FindWithClass(this.Node, "TreeviewScrollbar");

		DOM.Node.SetPosition(this.Node, this.Position);
		DOM.Node.SetSize(this.Node, this.Size);

		// Generate the contents of the treeview
		GenerateTree(this, this.ChildrenNode, this.RootItem.Children, 0);

		// Cross-browser (?) means of adding a mouse wheel handler
		var mouse_wheel_event = (/Firefox/i.test(navigator.userAgent)) ? "DOMMouseScroll" : "mousewheel";
		DOM.Event.AddHandler(this.Node, mouse_wheel_event, Bind(OnMouseScroll, this));

		DOM.Event.AddHandler(this.Node, "dblclick", Bind(OnMouseDoubleClick, this));
		DOM.Event.AddHandler(this.Node, "mousedown", Bind(OnMouseDown, this));
		DOM.Event.AddHandler(this.Node, "mouseup", OnMouseUp);

		// Swap in the newly generated control node if it's already been attached to a parent
		if (old_node && old_node.parentNode)
		{
			old_node.parentNode.removeChild(old_node);
			this.ParentNode.appendChild(this.Node);
		}

		if (this.EnableScrollbar)
		{
			this.UpdateScrollbar();
			DOM.Event.AddHandler(this.ScrollbarNode, "mousedown", Bind(OnMouseDown_Scrollbar, this));
			DOM.Event.AddHandler(this.ScrollbarNode, "mouseup", Bind(OnMouseUp_Scrollbar, this));
			DOM.Event.AddHandler(this.ScrollbarNode, "mouseout", Bind(OnMouseUp_Scrollbar, this));
			DOM.Event.AddHandler(this.ScrollbarNode, "mousemove", Bind(OnMouseMove_Scrollbar, this));
		}

		else
		{
			DOM.Node.Hide(DOM.Node.FindWithClass(this.Node, "TreeviewScrollbarInset"));
		}
	}

	
	Treeview.prototype.UpdateScrollbar = function()
	{
		if (!this.EnableScrollbar)
			return;

		var scrollbar_scale = Math.min((this.Node.offsetHeight - Margin * 2) / this.ChildrenNode.offsetHeight, 1);
		this.ScrollbarNode.style.height = parseInt(scrollbar_scale * 100) + "%";

		// Shift the scrollbar container along with the parent window
		this.ScrollbarNode.parentNode.style.top = this.Node.scrollTop;

		var scroll_fraction = this.Node.scrollTop / (this.Node.scrollHeight - this.Node.offsetHeight);
		var max_height = this.Node.offsetHeight - Margin;
		var max_scrollbar_offset = max_height - this.ScrollbarNode.offsetHeight;
		var scrollbar_offset = scroll_fraction * max_scrollbar_offset;
		this.ScrollbarNode.style.top = scrollbar_offset;
	}


	function GenerateTree(self, parent_node, items, depth)
	{
		if (items.length == 0)
			return null;

		for (var i in items)
		{
			var item = items[i];

			// Create the node for this item and locate important nodes
			var node = DOM.Node.CreateHTML(item_template_html);
			var img = DOM.Node.FindWithClass(node, "TreeviewItemImage");
			var text = DOM.Node.FindWithClass(node, "TreeviewItemText");
			var children = DOM.Node.FindWithClass(node, "TreeviewItemChildren");

			// Attach the item to the node
			node.TreeviewItem = item;
			item.Node = node;

			// Add the class which highlights selection on hover
			if (self.HighlightOnHover)
				DOM.Node.AddClass(node, "TreeviewItemHover");

			// Instruct the children to wrap around
			if (depth >= self.HorizontalLayoutDepth)
				node.style.cssFloat = "left";

			if (item.OpenImage == null || item.CloseImage == null)
			{
				// If there no images, remove the image node
				node.removeChild(img);
			}
			else
			{
				// Set the image source to open
				img.src = item.OpenImage.src;
				img.style.width = item.OpenImage.width;
				img.style.height = item.OpenImage.height;
				item.ImageNode = img;
			}

			// Setup the text to display
			text.innerHTML = item.Label;

			// Add the div to the parent and recurse into children
			parent_node.appendChild(node);
			GenerateTree(self, children, item.Children, depth + 1);
			item.ChildrenNode = children;
		}

		// Clear the wrap-around
		if (depth >= self.HorizontalLayoutDepth)
			DOM.Node.AppendClearFloat(parent_node.parentNode);
	}


	function OnMouseScroll(self, evt)
	{
		// Get mouse wheel movement
		var delta = evt.detail ? evt.detail * -1 : evt.wheelDelta;
		delta *= 8;

		// Scroll the main window with wheel movement and clamp
		self.Node.scrollTop -= delta;
		self.Node.scrollTop = Math.min(self.Node.scrollTop, (self.ChildrenNode.offsetHeight - self.Node.offsetHeight) + Margin * 2);

		self.UpdateScrollbar();
	}


	function OnMouseDoubleClick(self, evt)
	{
		DOM.Event.StopDefaultAction(evt);

		// Get the tree view item being clicked, if any
		var node = DOM.Event.GetNode(evt);
		var tvitem = GetTreeviewItemFromNode(self, node);
		if (tvitem == null)
			return;

		if (tvitem.Children.length)
			tvitem.Toggle();
	}


	function OnMouseDown(self, evt)
	{
		DOM.Event.StopDefaultAction(evt);

		// Get the tree view item being clicked, if any
		var node = DOM.Event.GetNode(evt);
		var tvitem = GetTreeviewItemFromNode(self, node);
		if (tvitem == null)
			return;

		// If clicking on the image, expand any children
		if (node.tagName == "IMG" && tvitem.Children.length)
		{
			tvitem.Toggle();
		}

		else
		{
			var mouse_pos = DOM.Event.GetMousePosition(evt);
			self.SelectItem(tvitem, mouse_pos);
		}
	}


	function OnMouseUp(evt)
	{
		// Event handler used merely to stop events bubbling up to containers
		DOM.Event.StopPropagation(evt);
	}


	function OnMouseDown_Scrollbar(self, evt)
	{
		self.ScrollbarHeld = true;

		// Cache the mouse height relative to the scrollbar
		self.LastY = evt.clientY;
		self.ScrollY = self.Node.scrollTop;

		DOM.Node.AddClass(self.ScrollbarNode, "TreeviewScrollbarHeld");
		DOM.Event.StopDefaultAction(evt);
	}


	function OnMouseUp_Scrollbar(self, evt)
	{
		self.ScrollbarHeld = false;
		DOM.Node.RemoveClass(self.ScrollbarNode, "TreeviewScrollbarHeld");
	}


	function OnMouseMove_Scrollbar(self, evt)
	{
		if (self.ScrollbarHeld)
		{
			var delta_y = evt.clientY - self.LastY;
			self.LastY = evt.clientY;

			var max_height = self.Node.offsetHeight - Margin;
			var max_scrollbar_offset = max_height - self.ScrollbarNode.offsetHeight;
			var max_contents_scroll = self.Node.scrollHeight - self.Node.offsetHeight;
			var scale = max_contents_scroll / max_scrollbar_offset;

			// Increment the local float variable and assign, as scrollTop is of type int
			self.ScrollY += delta_y * scale;			
			self.Node.scrollTop = self.ScrollY;
			self.Node.scrollTop = Math.min(self.Node.scrollTop, (self.ChildrenNode.offsetHeight - self.Node.offsetHeight) + Margin * 2);

			self.UpdateScrollbar();
		}
	}


	function GetTreeviewItemFromNode(self, node)
	{
		// Walk up toward the tree view node looking for this first item
		while (node && node != self.Node)
		{
			if ("TreeviewItem" in node)
				return node.TreeviewItem;

			node = node.parentNode;
		}

		return null;
	}

	return Treeview;
})();
