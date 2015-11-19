
TitleWindow = (function()
{
	function TitleWindow(wm, settings, server, connection_address)
	{
		this.Settings = settings;

		this.Window = wm.AddWindow("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Remotery", 10, 10, 100, 100);
		this.Window.ShowNoAnim();

		this.PingContainer = this.Window.AddControlNew(new WM.Container(4, -13, 10, 10));
		DOM.Node.AddClass(this.PingContainer.Node, "PingContainer");

		this.EditBox = this.Window.AddControlNew(new WM.EditBox(10, 5, 300, 18, "Connection Address", connection_address));

		// Setup pause button
		this.PauseButton = this.Window.AddControlNew(new WM.Button("Pause", 5, 5, { toggle: true }));
		this.PauseButton.SetOnClick(Bind(OnPausePressed, this));

		server.AddMessageHandler("PING", Bind(OnPing, this));
	}


	TitleWindow.prototype.SetConnectionAddressChanged = function(handler)
	{
		this.EditBox.SetChangeHandler(handler);
	}


	TitleWindow.prototype.WindowResized = function(width, height)
	{
		this.Window.SetSize(width - 2 * 10, 50);
		this.PauseButton.SetPosition(width - 80, 5);
	}


	function OnPausePressed(self)
	{
		self.Settings.IsPaused = self.PauseButton.IsPressed();
		if (self.Settings.IsPaused)
			self.PauseButton.SetText("Paused");
		else
			self.PauseButton.SetText("Pause");
	}


	function OnPing(self, server)
	{
		// Set the ping container as active and take it off half a second later
		DOM.Node.AddClass(self.PingContainer.Node, "PingContainerActive");
		window.setTimeout(Bind(function(self)
		{
			DOM.Node.RemoveClass(self.PingContainer.Node, "PingContainerActive");
		}, self), 500);
	}


	return TitleWindow;
})();