
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
		this.AppTextBuffer = "";

		// At a much lower frequency this will update the console window
		window.setInterval(Bind(UpdateHTML, this), 500);

		// Setup log requests from the server
		this.Server = server;
		server.SetConsole(this);
		server.AddMessageHandler("LOG", Bind(OnLog, this));
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


	function OnLog(self, socket, message)
	{
		self.AppTextBuffer = LogText(self.AppTextBuffer, message.text);
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

		var page_node = self.PageContainer.Node;
		page_node.innerHTML = self.PageTextBuffer;
		page_node.scrollTop = page_node.scrollHeight;

		var app_node = self.AppContainer.Node;
		app_node.innerHTML = self.AppTextBuffer;
		app_node.scrollTop = app_node.scrollHeight;
	}


	function ProcessInput(self, node)
	{
		// Send the message exactly
		var msg = node.value;
		self.Server.Send("CONI" + msg);

		// Emit to console and clear
		self.Log("> " + msg);
		self.UserInput.SetValue("");
	}


	return Console;
})();
