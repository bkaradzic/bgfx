
namespace("WM");


WM.Button = (function()
{
	var template_html = "<div class='Button notextsel'></div>";


	function Button(text, x, y, opts)
	{
		this.OnClick = null;
		this.Toggle = opts && opts.toggle;

		this.Node = DOM.Node.CreateHTML(template_html);

		// Set node dimensions
		this.SetPosition(x, y);
		if (opts && opts.w && opts.h)
			this.SetSize(opts.w, opts.h);

		// Override the default class name
		if (opts && opts.class)
			this.Node.className = opts.class;

		this.SetText(text);

		// Create the mouse press event handlers
		DOM.Event.AddHandler(this.Node, "mousedown", Bind(OnMouseDown, this));
		this.OnMouseOutDelegate = Bind(OnMouseUp, this, false);
		this.OnMouseUpDelegate = Bind(OnMouseUp, this, true);
	}


	Button.prototype.SetPosition = function(x, y)
	{
		this.Position = [ x, y ];
		DOM.Node.SetPosition(this.Node, this.Position);
	}


	Button.prototype.SetSize = function(w, h)
	{
		this.Size = [ w, h ];
		DOM.Node.SetSize(this.Node, this.Size);
	}


	Button.prototype.SetText = function(text)
	{
		this.Node.innerHTML = text;
	}


	Button.prototype.SetOnClick = function(on_click)
	{
		this.OnClick = on_click;
	}


	Button.prototype.SetState = function(pressed)
	{
		if (pressed)
			DOM.Node.AddClass(this.Node, "ButtonHeld");
		else
			DOM.Node.RemoveClass(this.Node, "ButtonHeld");
	}


	Button.prototype.ToggleState = function()
	{
		if (DOM.Node.HasClass(this.Node, "ButtonHeld"))
			this.SetState(false);
		else
			this.SetState(true);
	}


	Button.prototype.IsPressed = function()
	{
		return DOM.Node.HasClass(this.Node, "ButtonHeld");
	}


	function OnMouseDown(self, evt)
	{
		// Decide how to set the button state
		if (self.Toggle)
			self.ToggleState();
		else
			self.SetState(true);

		// Activate release handlers
		DOM.Event.AddHandler(self.Node, "mouseout", self.OnMouseOutDelegate);
		DOM.Event.AddHandler(self.Node, "mouseup", self.OnMouseUpDelegate);

		DOM.Event.StopAll(evt);
	}


	function OnMouseUp(self, confirm, evt)
	{
		if (confirm)
		{
			// Only release for non-toggles
			if (!self.Toggle)
				self.SetState(false);
		}
		else
		{
			// Decide how to set the button state
			if (self.Toggle)
				self.ToggleState();
			else
				self.SetState(false);
		}

		// Remove release handlers
		DOM.Event.RemoveHandler(self.Node, "mouseout", self.OnMouseOutDelegate);
		DOM.Event.RemoveHandler(self.Node, "mouseup", self.OnMouseUpDelegate);

		// Call the click handler if this is a button press
		if (confirm && self.OnClick)
			self.OnClick(self);

		DOM.Event.StopAll(evt);
	}


	return Button;
})();