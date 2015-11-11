
namespace("WM");


WM.EditBox = (function()
{
	var template_html = "							\
		<div class='EditBoxContainer'>				\
			<div class='EditBoxLabel'>Label</div>	\
			<input class='EditBox'>					\
		</div>";


	function EditBox(x, y, w, h, label, text)
	{
		this.ChangeHandler = null;

		// Create node and locate its internal nodes
		this.Node = DOM.Node.CreateHTML(template_html);
		this.LabelNode = DOM.Node.FindWithClass(this.Node, "EditBoxLabel");
		this.EditNode = DOM.Node.FindWithClass(this.Node, "EditBox");

		// Set label and value
		this.LabelNode.innerHTML = label;
		this.SetValue(text);

		this.SetPosition(x, y);
		this.SetSize(w, h);

		// Hook up the event handlers
		DOM.Event.AddHandler(this.EditNode, "focus", Bind(OnFocus, this));
		DOM.Event.AddHandler(this.EditNode, "keypress", Bind(OnKeyPress, this));
		DOM.Event.AddHandler(this.EditNode, "keydown", Bind(OnKeyDown, this));
		DOM.Event.AddHandler(this.EditNode, "change", Bind(OnChange, this));
	}


	EditBox.prototype.SetPosition = function(x, y)
	{
		this.Position = [ x, y ];
		DOM.Node.SetPosition(this.Node, this.Position);
	}


	EditBox.prototype.SetSize = function(w, h)
	{
		this.Size = [ w, h ];
		DOM.Node.SetSize(this.EditNode, this.Size);
	}


	EditBox.prototype.SetChangeHandler = function(handler)
	{
		this.ChangeHandler = handler;
	}


	EditBox.prototype.SetValue = function(value)
	{
		if (this.EditNode)
			this.EditNode.value = value;
	}


	EditBox.prototype.GetValue = function()
	{
		if (this.EditNode)
			return this.EditNode.value;
		
		return null;
	}


	EditBox.prototype.LoseFocus = function()
	{
		if (this.EditNode)
			this.EditNode.blur();
	}


	function OnFocus(self, evt)
	{
		// Backup on focus
		self.PreviousValue = self.EditNode.value;
	}


	function OnKeyPress(self, evt)
	{
		// Allow enter to confirm the text only when there's data
		if (evt.keyCode == 13 && self.EditNode.value != "")
		{
			self.EditNode.blur();
		}
	}


	function OnKeyDown(self, evt)
	{
		// Allow escape to cancel any text changes
		if (evt.keyCode == 27)
		{
			self.EditNode.value = self.PreviousValue;
			self.EditNode.blur();
		}
	}


	function OnChange(self, evt)
	{
		if (self.ChangeHandler)
			self.ChangeHandler(self.EditNode);
	}


	return EditBox;
})();
