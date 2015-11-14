
namespace("WM");


WM.Label = (function()
{
	var template_html = "<div class='Label'></div>";


	function Label(x, y, text)
	{
		// Create the node
		this.Node = DOM.Node.CreateHTML(template_html);

		// Allow position to be optional
		if (x != null && y != null)
			DOM.Node.SetPosition(this.Node, [x, y]);

		this.SetText(text);
	}


	Label.prototype.SetText = function(text)
	{
		if (text != null)
			this.Node.innerHTML = text;
	}


	return Label;
})();