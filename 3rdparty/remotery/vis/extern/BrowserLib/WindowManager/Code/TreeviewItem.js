
namespace("WM");


WM.TreeviewItem = (function()
{
	function TreeviewItem(treeview, name, data, open_image, close_image)
	{
		// Assign members
		this.Treeview = treeview;
		this.Label = name;
		this.Data = data;
		this.OpenImage = open_image;
		this.CloseImage = close_image;

		this.Children = [ ];

		// The HTML node wrapping the item and its children
		this.Node = null;

		// The HTML node storing the image for the open/close state feedback
		this.ImageNode = null;

		// The HTML node storing just the children
		this.ChildrenNode = null;

		// Animation handle for opening and closing the child nodes, only used
		// if the tree view item as children
		this.AnimHandle = null;

		// Open state of the item
		this.IsOpen = true;
	}


	TreeviewItem.prototype.AddItem = function(name, data, open_image, close_image)
	{
		var item = new WM.TreeviewItem(this.Treeview, name, data, open_image, close_image);
		this.Children.push(item);
		return item;
	}


	TreeviewItem.prototype.Open = function()
	{
		if (this.AnimHandle == null || this.AnimHandle.Complete)
		{
			// Swap to the open state
			this.IsOpen = true;
			if (this.ImageNode != null && this.OpenImage != null)
				this.ImageNode.src = this.OpenImage.src;
			
			// Cache for closure binding
			var child_node = this.ChildrenNode;
			var end_height = this.StartHeight;
			var treeview = this.Treeview;

			// Reveal the children and animate their height to max
			this.ChildrenNode.style.display = "block";
			this.AnimHandle = Anim.Animate(
				function (val) { DOM.Node.SetHeight(child_node, val) },
				0, end_height, 0.2,
				function() { treeview.UpdateScrollbar(); });

			// Fade the children in
			Anim.Animate(function(val) { DOM.Node.SetOpacity(child_node, val) }, 0, 1, 0.2);
		}
	}


	TreeviewItem.prototype.Close = function()
	{
		if (this.AnimHandle == null || this.AnimHandle.Complete)
		{
			// Swap to the close state
			this.IsOpen = false;
			if (this.ImageNode != null && this.CloseImage != null)
				this.ImageNode.src = this.CloseImage.src;

			// Cache for closure binding
			var child_node = this.ChildrenNode;
			var treeview = this.Treeview;

			// Mark the height of the item for reload later
			this.StartHeight = child_node.offsetHeight;

			// Shrink the height of the children and hide them upon completion
			this.AnimHandle = Anim.Animate(
				function (val) { DOM.Node.SetHeight(child_node, val) },
				this.ChildrenNode.offsetHeight, 0, 0.2,
				function() { child_node.style.display = "none"; treeview.UpdateScrollbar(); });

			// Fade the children out
			Anim.Animate(function(val) { DOM.Node.SetOpacity(child_node, val) }, 1, 0, 0.2);
		}
	}


	TreeviewItem.prototype.Toggle = function()
	{
		if (this.IsOpen)
			this.Close();
		else
			this.Open();
	}


	return TreeviewItem;
})();
