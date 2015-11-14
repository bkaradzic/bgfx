

TimelineRow = (function()
{
	var row_template = function(){/*
		<div class='TimelineRow'>
			<div class='TimelineRowCheck TimelineBox'>
				<input class='TimelineRowCheckbox' type='checkbox' />
			</div>
			<div class='TimelineRowExpand TimelineBox NoSelect'>
				<div class='TimelineRowExpandButton'>+</div>
			</div>
			<div class='TimelineRowExpand TimelineBox NoSelect'>
				<div class='TimelineRowExpandButton'>-</div>
			</div>
			<div class='TimelineRowLabel TimelineBox'></div>
			<canvas class='TimelineRowCanvas'></canvas>
			<div style="clear:left"></div>
		</div>
*/}.toString().split(/\n/).slice(1, -1).join("\n");


	var CANVAS_Y_OFFSET = 0;
	var CANVAS_BORDER = 1;
	var SAMPLE_HEIGHT = 16;
	var SAMPLE_BORDER = 1;
	var SAMPLE_Y_SPACING = SAMPLE_HEIGHT + SAMPLE_BORDER * 2;
	var SAMPLE_Y_OFFSET = CANVAS_Y_OFFSET + CANVAS_BORDER + 1;


	function TimelineRow(name, width, parent_node, frame_history, check_handler)
	{
		this.Name = name;

		// Create the row HTML and add to the parent
		this.ContainerNode = DOM.Node.CreateHTML(row_template);
		this.Node = DOM.Node.FindWithClass(this.ContainerNode, "TimelineRowData");
		this.LabelNode = DOM.Node.FindWithClass(this.ContainerNode, "TimelineRowLabel");
		this.LabelNode.innerHTML = name;
		this.CheckboxNode = DOM.Node.FindWithClass(this.ContainerNode, "TimelineRowCheckbox");
		var expand_node_0 = DOM.Node.FindWithClass(this.ContainerNode, "TimelineRowExpand", 0);
		var expand_node_1 = DOM.Node.FindWithClass(this.ContainerNode, "TimelineRowExpand", 1);
		this.IncNode = DOM.Node.FindWithClass(expand_node_0, "TimelineRowExpandButton");
		this.DecNode = DOM.Node.FindWithClass(expand_node_1, "TimelineRowExpandButton");
		this.CanvasNode = DOM.Node.FindWithClass(this.ContainerNode, "TimelineRowCanvas");
		parent_node.appendChild(this.ContainerNode);

		// All sample view windows visible by default
		this.CheckboxNode.checked = true;
		DOM.Event.AddHandler(this.CheckboxNode, "change", function(evt) { check_handler(name, evt); });

		// Manually hook-up events to simulate div:active
		// I can't get the equivalent CSS to work in Firefox, so...
		DOM.Event.AddHandler(this.IncNode, "mousedown", ExpandButtonDown);
		DOM.Event.AddHandler(this.IncNode, "mouseup", ExpandButtonUp);
		DOM.Event.AddHandler(this.IncNode, "mouseleave", ExpandButtonUp);
		DOM.Event.AddHandler(this.DecNode, "mousedown", ExpandButtonDown);
		DOM.Event.AddHandler(this.DecNode, "mouseup", ExpandButtonUp);
		DOM.Event.AddHandler(this.DecNode, "mouseleave", ExpandButtonUp);

		// Pressing +/i increases/decreases depth
		DOM.Event.AddHandler(this.IncNode, "click", Bind(IncDepth, this));
		DOM.Event.AddHandler(this.DecNode, "click", Bind(DecDepth, this));

		// Setup the canvas
		this.Depth = 1;
		this.Ctx = this.CanvasNode.getContext("2d");
		this.SetSize(width);
		this.Clear();

		// Frame index to start at when looking for first visible sample
		this.StartFrameIndex = 0;

		this.FrameHistory = frame_history;
		this.VisibleFrames = [ ];
		this.VisibleTimeRange = null;

		// Sample the mouse is currently hovering over
		this.HoverSample = null;
		this.HoverSampleDepth = 0;

		// Currently selected sample
		this.SelectedSample = null;
		this.SelectedSampleDepth = 0;
	}


	TimelineRow.prototype.SetSize = function(width)
	{
		// Must ALWAYS set the width/height properties together. Setting one on its own has weird side-effects.
		this.CanvasNode.width = width;
		this.CanvasNode.height = CANVAS_BORDER + SAMPLE_BORDER + SAMPLE_Y_SPACING * this.Depth;
		this.Draw(true);
	}


	TimelineRow.prototype.Clear = function()
	{
		// Fill box that shows the boundary between thread rows
		this.Ctx.fillStyle = "#666"
		var b = CANVAS_BORDER;
		this.Ctx.fillRect(b, b, this.CanvasNode.width - b * 2, this.CanvasNode.height - b * 2);
	}


	TimelineRow.prototype.SetVisibleFrames = function(time_range)
	{
		// Clear previous visible list
		this.VisibleFrames = [ ];
		if (this.FrameHistory.length == 0)
			return;

		// Store a copy of the visible time range rather than referencing it
		// This prevents external modifications to the time range from affecting rendering/selection
		time_range = time_range.Clone();
		this.VisibleTimeRange = time_range;

		// The frame history can be reset outside this class
		// This also catches the overflow to the end of the frame list below when a thread stops sending samples
		var max_frame = Math.max(this.FrameHistory.length - 1, 0);
		var start_frame_index = Math.min(this.StartFrameIndex, max_frame);

		// First do a back-track in case the time range moves negatively
		while (start_frame_index > 0)
		{
			var frame = this.FrameHistory[start_frame_index];
			if (time_range.Start_us > frame.StartTime_us)
				break;
			start_frame_index--;
		}

		// Then search from this point for the first visible frame
		while (start_frame_index < this.FrameHistory.length)
		{
			var frame = this.FrameHistory[start_frame_index];
			if (frame.EndTime_us > time_range.Start_us)
				break;
			start_frame_index++;
		}

		// Gather all frames up to the end point
		this.StartFrameIndex = start_frame_index;
		for (var i = start_frame_index; i < this.FrameHistory.length; i++)
		{
			var frame = this.FrameHistory[i];
			if (frame.StartTime_us > time_range.End_us)
				break;
			this.VisibleFrames.push(frame);
		}
	}


	TimelineRow.prototype.Draw = function(draw_text)
	{
		this.Clear();

		// Draw all root samples in the visible frame set
		for (var i in this.VisibleFrames)
		{
			var frame = this.VisibleFrames[i];
			DrawSamples(this, frame.Samples, 1, draw_text);
		}
	}


	function DrawSamples(self, samples, depth, draw_text)
	{
		for (var i in samples)
		{
			var sample = samples[i];
			DrawSample(self, sample, depth, draw_text);

			if (depth < self.Depth && sample.children != null)
				DrawSamples(self, sample.children, depth + 1, draw_text);
		}
	}


	TimelineRow.prototype.UpdateHoverSample = function(mouse_state, x_offset)
	{
		var hover = GetSampleAtPosition(this, mouse_state, x_offset);
		if (hover)
			this.SetHoverSample(hover[1], hover[2]);
		return hover;
	}


	TimelineRow.prototype.UpdateSelectedSample = function(mouse_state, x_offset)
	{
		var select = GetSampleAtPosition(this, mouse_state, x_offset);
		if (select)
			this.SetSelectedSample(select[1], select[2]);
		return select;
	}


	TimelineRow.prototype.SetHoverSample = function(sample, sample_depth)
	{
		if (sample != this.HoverSample)
		{
			// Discard old highlight
			// TODO: When zoomed right out, tiny samples are anti-aliased and this becomes inaccurate
			var old_sample = this.HoverSample;
			var old_sample_depth = this.HoverSampleDepth;
			this.HoverSample = null;
			this.HoverSampleDepth = 0;
			DrawSample(this, old_sample, old_sample_depth, true);

			// Add new highlight
			this.HoverSample = sample;
			this.HoverSampleDepth = sample_depth;
			DrawSample(this, sample, sample_depth, true);
		}
	}


	TimelineRow.prototype.SetSelectedSample = function(sample, sample_depth)
	{
		if (sample != this.SelectedSample)
		{
			// Discard old highlight
			// TODO: When zoomed right out, tiny samples are anti-aliased and this becomes inaccurate
			var old_sample = this.SelectedSample;
			var old_sample_depth = this.SelectedSampleDepth;
			this.SelectedSample = null;
			this.SelectedSampleDepth = 0;
			DrawSample(this, old_sample, old_sample_depth, true);

			// Add new highlight
			this.SelectedSample = sample;
			this.SelectedSampleDepth = sample_depth;
			DrawSample(this, sample, sample_depth, true);
		}
	}


	function ExpandButtonDown(evt)
	{
		var node = DOM.Event.GetNode(evt);
		DOM.Node.AddClass(node, "TimelineRowExpandButtonActive");
	}


	function ExpandButtonUp(evt)
	{
		var node = DOM.Event.GetNode(evt);
		DOM.Node.RemoveClass(node, "TimelineRowExpandButtonActive");
	}


	function IncDepth(self)
	{
		self.Depth++;
		self.SetSize(self.CanvasNode.width);
	}


	function DecDepth(self)
	{
		if (self.Depth > 1)
		{
			self.Depth--;
			self.SetSize(self.CanvasNode.width);
		}
	}


	function GetSampleAtPosition(self, mouse_state, x_offset)
	{
		// Mouse movement can occur before any data is sent to a timeline row
		var time_range = self.VisibleTimeRange;
		if (time_range == null)
			return;

		// Get the time the mouse is over
		var x = mouse_state.Position[0] - x_offset;
		var time_us = time_range.Start_us + x / time_range.usPerPixel;

		var canvas_y_offset = DOM.Node.GetPosition(self.CanvasNode)[1];
		var mouse_y_offset = mouse_state.Position[1] - canvas_y_offset;
		mouse_y_offset = Math.min(Math.max(mouse_y_offset, 0), self.CanvasNode.height);
		var depth = Math.floor(mouse_y_offset / SAMPLE_Y_SPACING) + 1;
		
		// Search for the first frame to intersect this time
		for (var i in self.VisibleFrames)
		{
			var frame = self.VisibleFrames[i];
			if (time_us >= frame.StartTime_us && time_us < frame.EndTime_us)
			{
				var found_sample = FindSample(self, frame.Samples, time_us, depth, 1);
				if (found_sample != null)
					return [ frame, found_sample[0], found_sample[1] ];
			}
		}

		return null;
	}


	function FindSample(self, samples, time_us, target_depth, depth)
	{
		for (var i in samples)
		{
			var sample = samples[i];
			if (depth == target_depth)
			{
				if (time_us >= sample.us_start && time_us < sample.us_start + sample.us_length)
					return [ sample, depth ];
			}

			else if (depth < target_depth && sample.children != null)
			{
				var found_sample = FindSample(self, sample.children, time_us, target_depth, depth + 1);
				if (found_sample != null)
					return found_sample;
			}
		}

		return null;
	}


	function DrawSample(self, sample, depth, draw_text)
	{
		if (sample == null)
			return;

		// Determine pixel range of the sample
		var time_range = self.VisibleTimeRange;
		var x0 = time_range.PixelOffset(sample.us_start);
		var x1 = x0 + time_range.PixelSize(sample.us_length);

		// Clip to padded timeline row
		var min_x = 3;
		var max_x = self.CanvasNode.width - 5;
		x0 = Math.min(Math.max(x0, min_x), max_x);
		x1 = Math.min(Math.max(x1, min_x), max_x);

		var offset_x = x0;
		var offset_y = SAMPLE_Y_OFFSET + (depth - 1) * SAMPLE_Y_SPACING;
		var size_x = x1 - x0;
		var size_y = SAMPLE_HEIGHT;

		// Normal rendering
		var ctx = self.Ctx;
		ctx.fillStyle = sample.colour;
		ctx.fillRect(offset_x, offset_y, size_x, size_y);

		// Highlight rendering
		var b = (sample == self.HoverSample) ? 255 : 0;
		var r = (sample == self.SelectedSample) ? 255 : 0;
		if (b + r > 0)
		{
			ctx.lineWidth = 1;
			ctx.strokeStyle = "rgb(" + r + ", 0, " + b + ")";
			ctx.strokeRect(offset_x + 0.5, offset_y + 0.5, size_x - 1, size_y - 1);
		}

		// Draw sample names clipped to the bounds of the sample
		if (draw_text)
		{
			ctx.save();
			ctx.beginPath();
			ctx.rect(offset_x + 2.5, offset_y + 1.5, size_x - 5, size_y - 3);
			ctx.clip();
			ctx.font = "9px verdana";
			ctx.fillStyle = "black";
			ctx.fillText(sample.name, offset_x + 5.5, offset_y + 1.5 + 9);
			ctx.restore();
		}
	}


	return TimelineRow;
})();
