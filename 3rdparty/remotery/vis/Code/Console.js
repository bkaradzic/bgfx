
Console = (function()
{
	var BORDER = 10;
	var HEIGHT = 200;


	function Console(wm, server)
	{
		// Create the window and its controls
		this.Window = wm.AddWindow("Console", 10, 10, 100, 100);
		this.PageContainer = this.Window.AddControlNew(new WM.Container(10, 10, 400, 160));
		DOM.Node.AddClass(this.PageContainer.Node, "ConsoleText");
		this.AppContainer = this.Window.AddControlNew(new WM.Container(10, 10, 400, 160));
		DOM.Node.AddClass(this.AppContainer.Node, "ConsoleText");
		this.UserInput = this.Window.AddControlNew(new WM.EditBox(10, 5, 400, 30, "Input", ""));
		this.UserInput.SetChangeHandler(Bind(ProcessInput, this));
		this.Window.ShowNoAnim();

		// This accumulates log text as fast as is required
		this.PageTextBuffer = "";
		this.LastPageTextBufferLen = 0;
		this.AppTextBuffer = "";
		this.LastAppTextBufferLen = 0;

		// Setup command history control
		this.CommandHistory = LocalStore.Get("App", "Global", "CommandHistory", [ ]);
		this.CommandIndex = 0;
		this.MaxNbCommands = 200;
		DOM.Event.AddHandler(this.UserInput.EditNode, "keydown", Bind(OnKeyPress, this));
		DOM.Event.AddHandler(this.UserInput.EditNode, "focus", Bind(OnFocus, this));

		// At a much lower frequency this will update the console window
		window.setInterval(Bind(UpdateHTML, this), 500);

		// Setup log requests from the server
		this.Server = server;
		server.SetConsole(this);
		server.AddMessageHandler("LOGM", Bind(OnLog, this));
	}


	Console.prototype.Log = function(text)
	{
		this.PageTextBuffer = LogText(this.PageTextBuffer, text);
	}


	Console.prototype.WindowResized = function(width, height)
	{
		// Place window
		this.Window.SetPosition(BORDER, height - BORDER - 200);
		this.Window.SetSize(width - 2 * BORDER, HEIGHT);

		// Place controls
		var parent_size = this.Window.Size;
		var mid_w = parent_size[0] / 3;
		this.UserInput.SetPosition(BORDER, parent_size[1] - 2 * BORDER - 30);
		this.UserInput.SetSize(parent_size[0] - 100, 18);
		var output_height = this.UserInput.Position[1] - 2 * BORDER;
		this.PageContainer.SetPosition(BORDER, BORDER);
		this.PageContainer.SetSize(mid_w - 2 * BORDER, output_height);
		this.AppContainer.SetPosition(mid_w, BORDER);
		this.AppContainer.SetSize(parent_size[0] - mid_w - BORDER, output_height);
	}


	function OnLog(self, socket, data_view)
	{
	    var data_view_reader = new DataViewReader(data_view, 4);
	    var text = data_view_reader.GetString();
	    self.AppTextBuffer = LogText(self.AppTextBuffer, text);
	}


	function LogText(existing_text, new_text)
	{
		// Filter the text a little to make it safer
		if (new_text == null)
			new_text = "NULL";

		// Find and convert any HTML entities, ensuring the browser doesn't parse any embedded HTML code
		// This also allows the log to contain arbitrary C++ code (e.g. assert comparison operators)
		new_text = Convert.string_to_html_entities(new_text);

		// Prefix date and end with new line
		var d = new Date();
		new_text = "[" + d.toLocaleTimeString() + "] " + new_text + "<br>";

		// Append to local text buffer and ensure clip the oldest text to ensure a max size
		existing_text = existing_text + new_text;
		var max_len = 10 * 1024;
		var len = existing_text.length;
		if (len > max_len)
			existing_text = existing_text.substr(len - max_len, max_len);

		return existing_text;
	}


	function UpdateHTML(self)
	{
		// Reset the current text buffer as html

		if (self.LastPageTextBufferLen != self.PageTextBuffer.length)
		{
			var page_node = self.PageContainer.Node;
			page_node.innerHTML = self.PageTextBuffer;
			page_node.scrollTop = page_node.scrollHeight;
			self.LastPageTextBufferLen = self.PageTextBuffer.length;
		}

		if (self.LastAppTextBufferLen != self.AppTextBuffer.length)
		{		
			var app_node = self.AppContainer.Node;
			app_node.innerHTML = self.AppTextBuffer;
			app_node.scrollTop = app_node.scrollHeight;
			self.LastAppTextBufferLen = self.AppTextBuffer.length;
		}
	}


	function ProcessInput(self, node)
	{
		// Send the message exactly
		var msg = node.value;
		self.Server.Send("CONI" + msg);

		// Emit to console and clear
		self.Log("> " + msg);
		self.UserInput.SetValue("");

		// Keep track of recently issued commands, with an upper bound
		self.CommandHistory.push(msg);
		var extra_commands = self.CommandHistory.length - self.MaxNbCommands;
		if (extra_commands > 0)
			self.CommandHistory.splice(0, extra_commands);

		// Set command history index to the most recent command
		self.CommandIndex = self.CommandHistory.length;

		// Backup to local store
		LocalStore.Set("App", "Global", "CommandHistory", self.CommandHistory);

		// Keep focus with the edit box
		return true;
	}


	function OnKeyPress(self, evt)
	{
		evt = DOM.Event.Get(evt);

		if (evt.keyCode == Keyboard.Codes.UP)
		{
			if (self.CommandHistory.length > 0)
			{
				// Cycle backwards through the command history
				self.CommandIndex--;
				if (self.CommandIndex < 0)
					self.CommandIndex = self.CommandHistory.length - 1;
				var command = self.CommandHistory[self.CommandIndex];
				self.UserInput.SetValue(command);
			}

			// Stops default behaviour of moving cursor to the beginning
			DOM.Event.StopDefaultAction(evt);
		}

		else if (evt.keyCode == Keyboard.Codes.DOWN)
		{
			if (self.CommandHistory.length > 0)
			{
				// Cycle fowards through the command history
				self.CommandIndex = (self.CommandIndex + 1) % self.CommandHistory.length;
				var command = self.CommandHistory[self.CommandIndex];
				self.UserInput.SetValue(command);
			}

			// Stops default behaviour of moving cursor to the end
			DOM.Event.StopDefaultAction(evt);
		}
	}


	function OnFocus(self)
	{
		// Reset command index on focus
		self.CommandIndex = self.CommandHistory.length;
	}


	return Console;
})();
