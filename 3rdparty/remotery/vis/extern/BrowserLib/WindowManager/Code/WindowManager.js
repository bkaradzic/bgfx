
namespace("WM");


WM.WindowManager = (function()
{
	function WindowManager()
	{
		// An empty list of windows under window manager control
		this.Windows = [ ];
	}


	WindowManager.prototype.AddWindow = function(title, x, y, width, height, parent_node)
	{
		// Create the window and add it to the list of windows
		var wnd = new WM.Window(this, title, x, y, width, height, parent_node);
		this.Windows.push(wnd);

		// Always bring to the top on creation
		wnd.SetTop();

		return wnd;
	}


	WindowManager.prototype.SetTopWindow = function(top_wnd)
	{
		// Bring the window to the top of the window list
		var top_wnd_index = this.Windows.indexOf(top_wnd);
		if (top_wnd_index != -1)
			this.Windows.splice(top_wnd_index, 1);
		this.Windows.push(top_wnd);

		// Set a CSS z-index for each visible window from the bottom up
		for (var i in this.Windows)
		{
			var wnd = this.Windows[i];
			if (!wnd.Visible)
				continue;

			// Ensure there's space between each window for the elements inside to be sorted
			var z = (parseInt(i) + 1) * 10;
			wnd.Node.style.zIndex = z;

			// Notify window that its z-order has changed
			wnd.NotifyChange();
		}
	}


	return WindowManager;

})();