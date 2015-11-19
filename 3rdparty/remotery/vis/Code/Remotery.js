
//
// TODO: Window resizing needs finer-grain control
// TODO: Take into account where user has moved the windows
// TODO: Controls need automatic resizing within their parent windows
//


Settings = (function()
{
	function Settings()
	{
		this.IsPaused = false;
	}

	return Settings;

})();


Remotery = (function()
{
	function Remotery()
	{
		this.WindowManager = new WM.WindowManager();
		this.Settings = new Settings();

		this.ConnectionAddress = LocalStore.Get("App", "Global", "ConnectionAddress", "ws://127.0.0.1:17815/rmt");
		this.Server = new WebSocketConnection();
		this.Server.AddConnectHandler(Bind(OnConnect, this));

		// Create the console up front as everything reports to it
		this.Console = new Console(this.WindowManager, this.Server);

		// Create required windows
		this.TitleWindow = new TitleWindow(this.WindowManager, this.Settings, this.Server, this.ConnectionAddress);
		this.TitleWindow.SetConnectionAddressChanged(Bind(OnAddressChanged, this));
		this.TimelineWindow = new TimelineWindow(this.WindowManager, this.Settings, this.Server, Bind(OnTimelineCheck, this));
		this.TimelineWindow.SetOnHover(Bind(OnSampleHover, this));
		this.TimelineWindow.SetOnSelected(Bind(OnSampleSelected, this));

		this.NbSampleWindows = 0;
		this.SampleWindows = { };
		this.FrameHistory = { };
		this.SelectedFrames = { };

		this.Server.AddMessageHandler("SAMPLES", Bind(OnSamples, this));

		// Kick-off the auto-connect loop
		AutoConnect(this);

		// Hook up resize event handler
		DOM.Event.AddHandler(window, "resize", Bind(OnResizeWindow, this));
		OnResizeWindow(this);

		// Hook up browser-native canvas refresh
		this.DisplayFrame = 0;
		this.LastKnownPause = this.Settings.IsPaused;
		var self = this;
		(function display_loop()
		{
			window.requestAnimationFrame(display_loop);
			DrawTimeline(self);
		})();
	}


	function AutoConnect(self)
	{
		// Only attempt to connect if there isn't already a connection or an attempt to connect
		if (!self.Server.Connected())
			self.Server.Connect(self.ConnectionAddress);

		// Always schedule another check
		window.setTimeout(Bind(AutoConnect, self), 2000);
	}


	function OnConnect(self)
	{
		// Connection address has been validated
		LocalStore.Set("App", "Global", "ConnectionAddress", self.ConnectionAddress);

		self.TimelineWindow.ResetTimeRange();
		self.FrameHistory = { };
		self.SelectedFrames = { };
	}


	function OnAddressChanged(self, node)
	{
		// Update and disconnect, relying on auto-connect to reconnect
		self.ConnectionAddress = node.value;
		self.Server.Disconnect();
	}


	function DrawTimeline(self)
	{
		// Has pause state changed?
		if (self.Settings.IsPaused != self.LastKnownPaused)
		{
			// When switching TO paused, draw one last frame to ensure the sample text gets drawn
			self.LastKnownPaused = self.Settings.IsPaused;
			self.TimelineWindow.DrawAllRows();
			return;
		}

		// Don't waste time drawing the timeline when paused
		if (self.Settings.IsPaused)
			return;

		// requestAnimationFrame can run up to 60hz which is way too much for drawing the timeline
		// Assume it's running at 60hz and skip frames to achieve 10hz instead
		// Doing this instead of using setTimeout because it's better for browser rendering (or; will be once WebGL is in use)
		if ((self.DisplayFrame % 10) == 0)
			self.TimelineWindow.DrawAllRows();

		self.DisplayFrame++;
	}


	function OnSamples(self, socket, message)
	{
		var name = message.thread_name;

		// Discard any new samples while paused
		if (self.Settings.IsPaused)
			return;

		// Add to frame history for this thread
		var thread_frame = new ThreadFrame(message);
		if (!(name in self.FrameHistory))
			self.FrameHistory[name] = [ ];
		var frame_history = self.FrameHistory[name];
		frame_history.push(thread_frame);

		// Discard old frames to keep memory-use constant
		var max_nb_frames = 10000;
		var extra_frames = frame_history.length - max_nb_frames;
		if (extra_frames > 0)
			frame_history.splice(0, extra_frames);

		// Create sample windows on-demand
		if (!(name in self.SampleWindows))
		{
			self.SampleWindows[name] = new SampleWindow(self.WindowManager, name, self.NbSampleWindows);
			self.SampleWindows[name].WindowResized(self.TimelineWindow.Window, self.Console.Window);
			self.NbSampleWindows++;
			MoveSampleWindows(this);
		}

		// Set on the window and timeline
		self.SampleWindows[name].OnSamples(message.nb_samples, message.sample_digest, message.samples);
		self.TimelineWindow.OnSamples(name, frame_history);
	}


	function OnTimelineCheck(self, name, evt)
	{
		// Show/hide the equivalent sample window and move all the others to occupy any left-over space
		var target = DOM.Event.GetNode(evt);
		self.SampleWindows[name].SetVisible(target.checked);
		MoveSampleWindows(self);
	}


	function MoveSampleWindows(self)
	{
		// Stack all windows next to each other
		var xpos = 0;
		for (var i in self.SampleWindows)
		{
			var sample_window = self.SampleWindows[i];
			if (sample_window.Visible)
				sample_window.SetXPos(xpos++, self.TimelineWindow.Window, self.Console.Window);
		}
	}


	function OnSampleHover(self, thread_name, hover)
	{
		// Hover only changes sample window contents when paused
		var sample_window = self.SampleWindows[thread_name];
		if (sample_window && self.Settings.IsPaused)
		{
			if (hover == null)
			{
				// When there's no hover, go back to the selected frame
				if (self.SelectedFrames[thread_name])
				{
					var frame = self.SelectedFrames[thread_name];
					sample_window.OnSamples(frame.NbSamples, frame.SampleDigest, frame.Samples);
				}
			}

			else
			{
				// Populate with sample under hover
				var frame = hover[0];
				sample_window.OnSamples(frame.NbSamples, frame.SampleDigest, frame.Samples);
			}
		}
	}


	function OnSampleSelected(self, thread_name, select)
	{
		// Lookup sample window set the frame samples on it
		if (select && thread_name in self.SampleWindows)
		{
			var sample_window = self.SampleWindows[thread_name];
			var frame = select[0];
			self.SelectedFrames[thread_name] = frame;
			sample_window.OnSamples(frame.NbSamples, frame.SampleDigest, frame.Samples);
		}
	}


	function OnResizeWindow(self)
	{
		// Resize windows
		var w = window.innerWidth;
		var h = window.innerHeight;
		self.Console.WindowResized(w, h);
		self.TitleWindow.WindowResized(w, h);
		self.TimelineWindow.WindowResized(w, h, self.TitleWindow.Window);
		for (var i in self.SampleWindows)
			self.SampleWindows[i].WindowResized(self.TimelineWindow.Window, self.Console.Window);
	}


	return Remotery;
})();