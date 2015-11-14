
namespace("WM");


WM.Window = (function()
{
	var template_html = "																								\
		<div class='Window'>																							\
			<div class='WindowTitleBar'>																				\
				<div class='WindowTitleBarText notextsel' style='float:left'>Window Title Bar</div>						\
				<div class='WindowTitleBarClose notextsel' style='float:right'>O</div>									\
			</div>																										\
			<div class='WindowBody'>																					\
			</div>																										\
		</div>";


	function Window(manager, title, x, y, width, height, parent_node)
	{
		this.Manager = manager;
		this.ParentNode = parent_node || document.body;
		this.OnMove = null;
		this.Visible = false;
		this.AnimatedShow = false;

		// Clone the window template and locate key nodes within it
		this.Node = DOM.Node.CreateHTML(template_html);
		this.TitleBarNode = DOM.Node.FindWithClass(this.Node, "WindowTitleBar");
		this.TitleBarTextNode = DOM.Node.FindWithClass(this.Node, "WindowTitleBarText");
		this.TitleBarCloseNode = DOM.Node.FindWithClass(this.Node, "WindowTitleBarClose");
		this.BodyNode = DOM.Node.FindWithClass(this.Node, "WindowBody");

		// Setup the position and dimensions of the window
		this.SetPosition(x, y);
		this.SetSize(width, height);

		// Set the title text
		this.TitleBarTextNode.innerHTML = title;

		// Hook up event handlers
		DOM.Event.AddHandler(this.Node, "mousedown", Bind(this, "SetTop"));
		DOM.Event.AddHandler(this.TitleBarNode, "mousedown", Bind(this, "BeginMove"));
		DOM.Event.AddHandler(this.TitleBarCloseNode, "mousedown", Bind(this, "Hide"));

		// Create delegates for removable handlers
		this.MoveDelegate = Bind(this, "Move");
		this.EndMoveDelegate = Bind(this, "EndMove");		
	}


	Window.prototype.SetOnMove = function(on_move)
	{
		this.OnMove = on_move;
	}


	Window.prototype.Show = function()
	{
		if (this.Node.parentNode != this.ParentNode)
		{
			this.ShowNoAnim();
			Anim.Animate(Bind(this, "OpenAnimation"), 0, 1, 1);
		}
	}


	Window.prototype.ShowNoAnim = function()
	{
		// Add to the document
		this.ParentNode.appendChild(this.Node);
		this.AnimatedShow = false;
		this.Visible = true;
	}


	Window.prototype.Hide = function()
	{
		if (this.Node.parentNode == this.ParentNode)
		{
			if (this.AnimatedShow)
			{
				// Trigger animation that ends with removing the window from the document
				Anim.Animate(
					Bind(this, "CloseAnimation"),
					0, 1, 0.25,
					Bind(this, "HideNoAnim"));
			}
			else
			{
				this.HideNoAnim();
			}
		}
	}

	
	Window.prototype.HideNoAnim = function()
	{
		// Remove node
		this.ParentNode.removeChild(this.Node);
		this.Visible = false;
	}


	Window.prototype.SetTop = function()
	{
		this.Manager.SetTopWindow(this);
	}



	Window.prototype.SetTitle = function(title)
	{
		this.TitleBarTextNode.innerHTML = title;
	}


	// TODO: Update this
	Window.prototype.AddControl = function(control)
	{
		// Get all arguments to this function and replace the first with this window node
		var args = [].slice.call(arguments);
		args[0] = this.BodyNode;

		// Create the control and call its Init method with the modified arguments
		var instance = new control();
		instance.Init.apply(instance, args);

		return instance;
	}


	Window.prototype.AddControlNew = function(control)
	{
		control.ParentNode = this.BodyNode;
		this.BodyNode.appendChild(control.Node);
		return control;
	}


	Window.prototype.Scale = function(t)
	{
		// Calculate window bounds centre/extents
		var ext_x = this.Size[0] / 2;
		var ext_y = this.Size[1] / 2;
		var mid_x = this.Position[0] + ext_x;
		var mid_y = this.Position[1] + ext_y;

		// Scale from the mid-point
		DOM.Node.SetPosition(this.Node, [ mid_x - ext_x * t, mid_y - ext_y * t ]);
		DOM.Node.SetSize(this.Node, [ this.Size[0] * t, this.Size[1] * t ]);
	}


	Window.prototype.OpenAnimation = function(val)
	{
		// Power ease in
		var t = 1 - Math.pow(1 - val, 8);
		this.Scale(t);
		DOM.Node.SetOpacity(this.Node, 1 - Math.pow(1 - val, 8));
		this.AnimatedShow = true;
	}


	Window.prototype.CloseAnimation = function(val)
	{
		// Power ease out
		var t = 1 - Math.pow(val, 4);
		this.Scale(t);
		DOM.Node.SetOpacity(this.Node, t);
	}


	Window.prototype.NotifyChange = function()
	{
		if (this.OnMove)
		{
			var pos = DOM.Node.GetPosition(this.Node);
			this.OnMove(this, pos);
		}
	}


	Window.prototype.BeginMove = function(evt)
	{
		// Calculate offset of the window from the mouse down position
		var mouse_pos = DOM.Event.GetMousePosition(evt);
		this.Offset = [ mouse_pos[0] - this.Position[0], mouse_pos[1] - this.Position[1] ];

		// Dynamically add handlers for movement and release
		DOM.Event.AddHandler(document, "mousemove", this.MoveDelegate);
		DOM.Event.AddHandler(document, "mouseup", this.EndMoveDelegate);

		DOM.Event.StopDefaultAction(evt);
	}


	Window.prototype.Move = function(evt)
	{
		// Use the offset at the beginning of movement to drag the window around
		var mouse_pos = DOM.Event.GetMousePosition(evt);
		var offset = this.Offset;
		var pos = [ mouse_pos[0] - offset[0], mouse_pos[1] - offset[1] ];
		this.SetPosition(pos[0], pos[1]);

		if (this.OnMove)
			this.OnMove(this, pos);

		DOM.Event.StopDefaultAction(evt);
	}


	Window.prototype.EndMove = function(evt)
	{
		// Remove handlers added during mouse down
		DOM.Event.RemoveHandler(document, "mousemove", this.MoveDelegate);
		DOM.Event.RemoveHandler(document, "mouseup", this.EndMoveDelegate);

		DOM.Event.StopDefaultAction(evt);
	}


	Window.prototype.SetPosition = function(x, y)
	{
		this.Position = [ x, y ];
		DOM.Node.SetPosition(this.Node, this.Position);
	}


	Window.prototype.SetSize = function(w, h)
	{
		this.Size = [ w, h ];
		DOM.Node.SetSize(this.Node, this.Size);
	}


	Window.prototype.GetZIndex = function()
	{
		return parseInt(this.Node.style.zIndex);
	}


	return Window;
})();