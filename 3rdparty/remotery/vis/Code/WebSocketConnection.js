
WebSocketConnection = (function()
{
	function WebSocketConnection()
	{
		this.MessageHandlers = { };
		this.Socket = null;
		this.Console = null;
	}


	WebSocketConnection.prototype.SetConsole = function(console)
	{
		this.Console = console;
	}


	WebSocketConnection.prototype.Connected = function()
	{
		// Will return true if the socket is also in the process of connecting
		return this.Socket != null;
	}


	WebSocketConnection.prototype.AddConnectHandler = function(handler)
	{
		this.AddMessageHandler("__OnConnect__", handler);
	}


	WebSocketConnection.prototype.AddDisconnectHandler = function(handler)
	{
		this.AddMessageHandler("__OnDisconnect__", handler);
	}


	WebSocketConnection.prototype.AddMessageHandler = function(message_name, handler)
	{
		// Create the message handler array on-demand
		if (!(message_name in this.MessageHandlers))
			this.MessageHandlers[message_name] = [ ];
		this.MessageHandlers[message_name].push(handler);
	}


	WebSocketConnection.prototype.Connect = function(address)
	{
		// Disconnect if already connected
		if (this.Connected())
			this.Disconnect();

		Log(this, "Connecting to " + address);

		this.Socket = new WebSocket(address);
		this.Socket.onopen = Bind(OnOpen, this);
		this.Socket.onmessage = Bind(OnMessage, this);
		this.Socket.onclose = Bind(OnClose, this);
		this.Socket.onerror = Bind(OnError, this);
	}


	WebSocketConnection.prototype.Disconnect = function()
	{
		Log(this, "Disconnecting");
		if (this.Connected())
			this.Socket.close();
	}


	WebSocketConnection.prototype.Send = function(msg)
	{
		if (this.Connected())
			this.Socket.send(msg);
	}


	function Log(self, message)
	{
		self.Console.Log(message);
	}


	function CallMessageHandlers(self, message_name, message)
	{
		if (message_name in self.MessageHandlers)
		{
			var handlers = self.MessageHandlers[message_name];
			for (var i in handlers)
				handlers[i](self, message);
		}
	}


	function OnOpen(self, event)
	{
		Log(self, "Connected");
		CallMessageHandlers(self, "__OnConnect__");
	}


	function OnClose(self, event)
	{
		// Clear all references
		self.Socket.onopen = null;
		self.Socket.onmessage = null;
		self.Socket.onclose = null;
		self.Socket.onerror = null;
		self.Socket = null;

		Log(self, "Disconnected");
		CallMessageHandlers(self, "__OnDisconnect__");
	}


	function OnError(self, event)
	{
		Log(self, "Connection Error ");
	}


	function OnMessage(self, event)
	{
		var message = JSON.parse(event.data);
		if ("id" in message)
			CallMessageHandlers(self, message.id, message);
	}


	return WebSocketConnection;
})();
