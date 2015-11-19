
namespace("WM");


WM.Container = (function()
{
	var template_html = "<div class='Container'></div>";


	function Container(x, y, w, h)
	{
		// Create a simple container node
		this.Node = DOM.Node.CreateHTML(template_html);
		this.SetPosition(x, y);
		this.SetSize(w, h);
	}


	Container.prototype.SetPosition = function(x, y)
	{
		this.Position = [ x, y ];
		DOM.Node.SetPosition(this.Node, this.Position);
	}


	Container.prototype.SetSize = function(w, h)
	{
		this.Size = [ w, h ];
		DOM.Node.SetSize(this.Node, this.Size);
	}


	return Container;
})();