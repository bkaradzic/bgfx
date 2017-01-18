
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
	// crack the url and get the parameter we want
	var getUrlParameter = function getUrlParameter( search_param) 
	{
		var page_url = decodeURIComponent( window.location.search.substring(1) ),
						url_vars = page_url.split('&'),
						param_name,
						i;

		for (i = 0; i < url_vars.length; i++) 
		{
			param_name = url_vars[i].split('=');

			if (param_name[0] === search_param) 
			{
				return param_name[1] === undefined ? true : param_name[1];
			}
		}
	};

	function Remotery()
	{
		this.WindowManager = new WM.WindowManager();
		this.Settings = new Settings();

		// "addr" param is ip:port and will override the local store version if passed in the URL
		var addr = getUrlParameter( "addr" );
		if ( addr != null )
			this.ConnectionAddress = "ws://" + addr + "/rmt";
		else
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
		this.NameMap = { };

		this.Server.AddMessageHandler("SMPL", Bind(OnSamples, this));
		this.Server.AddMessageHandler("SSMP", Bind(OnSampleName, this));

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
	}


	function OnAddressChanged(self, node)
	{
		// Update and disconnect, relying on auto-connect to reconnect
		self.ConnectionAddress = node.value;
		self.Server.Disconnect();

		// Give input focus away
		return false;
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
        // TODO: Expose as config variable because high refresh rate is great when using a separate viewiing machine
		if ((self.DisplayFrame % 10) == 0)
			self.TimelineWindow.DrawAllRows();

		self.DisplayFrame++;
	}


	function DecodeSample(self, data_view_reader)
	{
	    var sample = {};

        // Get name hash and lookup name it map
	    sample.name_hash = data_view_reader.GetUInt32();
	    sample.name = self.NameMap[sample.name_hash];

        // If the name doesn't exist in the map yet, request it from the server
	    if (sample.name == undefined)
	    {
            // Meanwhile, store the hash as the name
	        sample.name = sample.name_hash;
	        self.Server.Send("GSMP" + sample.name);
	    }

        // Get the rest of the sample data
	    sample.id = data_view_reader.GetUInt32();
	    sample.colour = data_view_reader.GetStringOfLength(7);
	    sample.us_start = data_view_reader.GetUInt64();
	    sample.us_length = data_view_reader.GetUInt64();

        // Recurse into children
	    sample.children = [];
	    DecodeSampleArray(self, data_view_reader, sample.children);

	    return sample;
	}


	function DecodeSampleArray(self, data_view_reader, samples)
	{
	    var nb_samples = data_view_reader.GetUInt32();
	    for (var i = 0; i < nb_samples; i++)
	    {
	        var sample = DecodeSample(self, data_view_reader);
            samples.push(sample)
	    }
	}


	function DecodeSamples(self, data_view_reader)
	{
        // Message-specific header
	    var message = { };
	    message.thread_name = data_view_reader.GetString();
	    message.nb_samples = data_view_reader.GetUInt32();
	    message.sample_digest = data_view_reader.GetUInt32();

        // Read samples
	    message.samples = [];
	    message.samples.push(DecodeSample(self, data_view_reader));

	    return message;
	}


	function OnSamples(self, socket, data_view)
	{
		// Discard any new samples while paused
		if (self.Settings.IsPaused)
		    return;

        // Binary decode incoming sample data
		var message = DecodeSamples(self, new DataViewReader(data_view, 8));
		var name = message.thread_name;

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


	function OnSampleName(self, socket, data_view)
	{
        // Add any names sent by the server to the local map
	    var data_view_reader = new DataViewReader(data_view, 4);
	    var name_hash = data_view_reader.GetUInt32();
	    var name = data_view_reader.GetString();
	    self.NameMap[name_hash] = name;
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