
SampleWindow = (function()
{
	function SampleWindow(wm, name, offset)
	{
		// Sample digest for checking if grid needs to be repopulated
		this.NbSamples = 0;
		this.SampleDigest = null;

		this.XPos = 10 + offset * 410;
		this.Window = wm.AddWindow(name, 100, 100, 100, 100);
		this.Window.Show();
		this.Visible = true;

		// Create a grid that's indexed by the unique sample ID
		this.Grid = this.Window.AddControlNew(new WM.Grid(0, 0, 380, 400));
		this.RootRow = this.Grid.Rows.Add({ "Name": "Samples" }, "GridGroup", { "Name": "GridGroup" });
		this.RootRow.Rows.AddIndex("_ID");
	}


	SampleWindow.prototype.SetXPos = function(xpos, top_window, bottom_window)
	{
		Anim.Animate(
			Bind(AnimatedMove, this, top_window, bottom_window),
			this.XPos, 10 + xpos * 410, 0.25);
	}


	function AnimatedMove(self, top_window, bottom_window, val)
	{
		self.XPos = val;
		self.WindowResized(top_window, bottom_window);
	}


	SampleWindow.prototype.SetVisible = function(visible)
	{
		if (visible != this.Visible)
		{
			if (visible == true)
				this.Window.Show();
			else
				this.Window.Hide();

			this.Visible = visible;
		}
	}


	SampleWindow.prototype.WindowResized = function(top_window, bottom_window)
	{
		var top = top_window.Position[1] + top_window.Size[1] + 10;
		this.Window.SetPosition(this.XPos, top_window.Position[1] + top_window.Size[1] + 10);
		this.Window.SetSize(400, bottom_window.Position[1] - 10 - top);
	}


	SampleWindow.prototype.OnSamples = function(nb_samples, sample_digest, samples)
	{
		if (!this.Visible)
			return;

		// Recreate all the HTML if the number of samples gets bigger
		if (nb_samples > this.NbSamples)
		{
			GrowGrid(this.RootRow, nb_samples);
			this.NbSamples = nb_samples;
		}

		// If the content of the samples changes from previous update, update them all
		if (this.SampleDigest != sample_digest)
		{
			this.RootRow.Rows.ClearIndex("_ID");
			var index = UpdateSamples(this.RootRow, samples, 0, "");
			this.SampleDigest = sample_digest;

			// Clear out any left-over rows
			for (var i = index; i < this.RootRow.Rows.Rows.length; i++)
			{
				var row = this.RootRow.Rows.Rows[i];
				DOM.Node.Hide(row.Node);
			}
		}

		else if (this.Visible)
		{
			// Otherwise just update the existing sample times
			UpdateSampleTimes(this.RootRow, samples);
		}
	}


	function GrowGrid(parent_row, nb_samples)
	{
		parent_row.Rows.Clear();

		for (var i = 0; i < nb_samples; i++)
		{
			var cell_data =
			{
				_ID: i,
				Name: "",
				Control: new WM.Label()
			};

			var cell_classes =
			{
				Name: "SampleNameCell",
			};

			parent_row.Rows.Add(cell_data, null, cell_classes);
		}
	}


	function UpdateSamples(parent_row, samples, index, indent)
	{
		for (var i in samples)
		{
			var sample = samples[i];

			// Match row allocation in GrowGrid
			var row = parent_row.Rows.Rows[index++];

			// Sample row may have been hidden previously
			DOM.Node.Show(row.Node);
			
			// Assign unique ID so that the common fast path of updating sample times only
			// can lookup target samples in the grid
			row.CellData._ID = sample.id;
			parent_row.Rows.AddRowToIndex("_ID", sample.id, row);

			// Set sample name and colour
			var name_node = row.CellNodes["Name"];
			name_node.innerHTML = indent + sample.name;
			DOM.Node.SetColour(name_node, sample.colour);

			row.CellData.Control.SetText(sample.us_length);

			index = UpdateSamples(parent_row, sample.children, index, indent + "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");
		}

		return index;
	}


	function UpdateSampleTimes(parent_row, samples)
	{
		for (var i in samples)
		{
			var sample = samples[i];

			var row = parent_row.Rows.GetBy("_ID", sample.id);
			if (row)
				row.CellData.Control.SetText(sample.us_length);

			UpdateSampleTimes(parent_row, sample.children);
		}
	}


	return SampleWindow;
})();