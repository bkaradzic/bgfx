
//
// TODO: Use WebGL and instancing for quicker renders
//


TimelineWindow = (function()
{
	var BORDER = 10;

	var ROW_START_SIZE = 210;

	var ROW_END_SIZE = 20;  // make room for scrollbar

	var box_template = "<div class='TimelineBox'></div>";


	function TimelineWindow(wm, settings, server, check_handler)
	{
		this.Settings = settings;

		// Ordered list of thread rows on the timeline
		this.ThreadRows = [ ];

		// Create window and containers
		this.Window = wm.AddWindow("Timeline", 10, 20, 100, 100);
		this.Window.ShowNoAnim();
		this.TimelineContainer = this.Window.AddControlNew(new WM.Container(10, 10, 800, 160));
		DOM.Node.AddClass(this.TimelineContainer.Node, "TimelineContainer");

		var mouse_wheel_event = (/Firefox/i.test(navigator.userAgent)) ? "DOMMouseScroll" : "mousewheel";
		DOM.Event.AddHandler(this.TimelineContainer.Node, mouse_wheel_event, Bind(OnMouseScroll, this));

		// Setup timeline manipulation
		this.MouseDown = false;
		this.TimelineMoved = false;
		this.OnHoverHandler = null;
		this.OnSelectedHandler = null;
		DOM.Event.AddHandler(this.TimelineContainer.Node, "mousedown", Bind(OnMouseDown, this));
		DOM.Event.AddHandler(this.TimelineContainer.Node, "mouseup", Bind(OnMouseUp, this));
		DOM.Event.AddHandler(this.TimelineContainer.Node, "mousemove", Bind(OnMouseMove, this));		

		// Set time range AFTER the window has been created, as it uses the window to determine pixel coverage
		this.TimeRange = new PixelTimeRange(0, 200 * 1000, RowWidth(this));

		this.CheckHandler = check_handler;
	}


	TimelineWindow.prototype.SetOnHover = function(handler)
	{
		this.OnHoverHandler = handler;
	}


	TimelineWindow.prototype.SetOnSelected = function(handler)
	{
		this.OnSelectedHandler = handler;
	}


	TimelineWindow.prototype.WindowResized = function(width, height, top_window)
	{
		// Resize window
		var top = top_window.Position[1] + top_window.Size[1] + 10;
		this.Window.SetPosition(10, top);
		this.Window.SetSize(width - 2 * 10, 200);

		// Resize controls
		var parent_size = this.Window.Size;
		this.TimelineContainer.SetPosition(BORDER, 10);
		this.TimelineContainer.SetSize(parent_size[0] - 2 * BORDER, 160);

		// Resize rows
		var row_width = RowWidth(this);
		for (var i in this.ThreadRows)
		{
			var row = this.ThreadRows[i];
			row.SetSize(row_width);
		}

		// Adjust time range to new width
		this.TimeRange.SetPixelSpan(row_width);
		this.DrawAllRows();
	}


	TimelineWindow.prototype.ResetTimeRange = function()
	{
		this.TimeRange.SetStart(0);
	}


	TimelineWindow.prototype.OnSamples = function(thread_name, frame_history)
	{
		// Shift the timeline to the last entry on this thread
		// As multiple threads come through here with different end frames, only do this for the latest
		var last_frame = frame_history[frame_history.length - 1];
		if (last_frame.EndTime_us > this.TimeRange.End_us)
			this.TimeRange.SetEnd(last_frame.EndTime_us);

		// Search for the index of this thread
		var thread_index = -1;
		for (var i in this.ThreadRows)
		{
			if (this.ThreadRows[i].Name == thread_name)
			{
				thread_index = i;
				break;
			}
		}

		// If this thread has not been seen before, add a new row to the list and re-sort
		if (thread_index == -1)
		{
			var row = new TimelineRow(thread_name, RowWidth(this), this.TimelineContainer.Node, frame_history, this.CheckHandler);
			this.ThreadRows.push(row);
			this.ThreadRows.sort(function(a, b) { return b.Name.localeCompare(a.Name); });
		}
	}


	TimelineWindow.prototype.DrawAllRows = function()
	{
		var time_range = this.TimeRange;
		var draw_text = this.Settings.IsPaused;
		for (var i in this.ThreadRows)
		{
			var thread_row = this.ThreadRows[i];
			thread_row.SetVisibleFrames(time_range);
			thread_row.Draw(draw_text);
		}
	}


	function RowXOffset(self)
	{
		// Add sizing of the label
		// TODO: Use computed size
		return DOM.Node.GetPosition(self.TimelineContainer.Node)[0] + ROW_START_SIZE;
	}


	function RowWidth(self)
	{
		// Subtract sizing of the label
		// TODO: Use computed size
		return self.TimelineContainer.Size[0] - (ROW_START_SIZE + ROW_END_SIZE);
	}


	function OnMouseScroll(self, evt)
	{
		var mouse_state = new Mouse.State(evt);
		var scale = 1.11;
			if (mouse_state.WheelDelta > 0)
				scale = 1 / scale;

		// What time is the mouse hovering over?
		var x = mouse_state.Position[0] - RowXOffset(self);
		var time_us = self.TimeRange.Start_us + x / self.TimeRange.usPerPixel;

		// Calculate start time relative to the mouse hover position
		var time_start_us = self.TimeRange.Start_us - time_us;

		// Scale and offset back to the hover time
		self.TimeRange.Set(time_start_us * scale + time_us, self.TimeRange.Span_us * scale);
		self.DrawAllRows();

		// Prevent vertical scrolling on mouse-wheel
		DOM.Event.StopDefaultAction(evt);
	}


	function OnMouseDown(self, evt)
	{
		// Only manipulate the timelime when paused
		if (!self.Settings.IsPaused)
			return;

		self.MouseDown = true;
		self.TimelineMoved = false;
		DOM.Event.StopDefaultAction(evt);
	}


	function OnMouseUp(self, evt)
	{
		// Only manipulate the timelime when paused
		if (!self.Settings.IsPaused)
			return;

		var mouse_state = new Mouse.State(evt);

		self.MouseDown = false;

		if (!self.TimelineMoved)
		{
			// Search for the row being clicked and update its selection
			var row_node = DOM.Event.GetNode(evt);
			for (var i in self.ThreadRows)
			{
				var thread_row = self.ThreadRows[i];
				if (thread_row.CanvasNode == row_node)
				{
					var select = thread_row.UpdateSelectedSample(mouse_state, RowXOffset(self));

					// Call any selection handlers
					if (self.OnSelectedHandler)
						self.OnSelectedHandler(thread_row.Name, select);

					break;
				}
			}
		}
	}


	function OnMouseMove(self, evt)
	{
		// Only manipulate the timelime when paused
		if (!self.Settings.IsPaused)
			return;

		var mouse_state = new Mouse.State(evt);

		if (self.MouseDown)
		{
			// Get the time the mouse is over
			var x = mouse_state.Position[0] - RowXOffset(self);
			var time_us = self.TimeRange.Start_us + x / self.TimeRange.usPerPixel;

			// Shift the visible time range with mouse movement
			var time_offset_us = mouse_state.PositionDelta[0] / self.TimeRange.usPerPixel;
			if (time_offset_us)
			{
				self.TimeRange.SetStart(self.TimeRange.Start_us - time_offset_us);
				self.DrawAllRows();
				self.TimelineMoved = true;
			}
		}

		else
		{
			// Highlight any samples the mouse moves over
			var row_node = DOM.Event.GetNode(evt);
			for (var i in self.ThreadRows)
			{
				var thread_row = self.ThreadRows[i];
				if (thread_row.CanvasNode == row_node)
				{
					var hover = thread_row.UpdateHoverSample(mouse_state, RowXOffset(self));

					if (self.OnHoverHandler)
						self.OnHoverHandler(thread_row.Name, hover);
				}
				else
				{
					thread_row.SetHoverSample(null, 0);
					if (self.OnHoverHandler)
						self.OnHoverHandler(thread_row.Name, null);
				}
			}
		}
	}


	return TimelineWindow;
})();

