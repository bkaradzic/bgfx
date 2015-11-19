

PixelTimeRange = (function()
{
	function PixelTimeRange(start_us, span_us, span_px)
	{
		this.Span_px = span_px;
		this.Set(start_us, span_us);
	}


	PixelTimeRange.prototype.Set = function(start_us, span_us)
	{
		this.Start_us = start_us;
		this.Span_us = span_us;
		this.End_us = this.Start_us + span_us;
		this.usPerPixel = this.Span_px / this.Span_us;
	}


	PixelTimeRange.prototype.SetStart = function(start_us)
	{
		this.Start_us = start_us;
		this.End_us = start_us + this.Span_us;
	}


	PixelTimeRange.prototype.SetEnd = function(end_us)
	{
		this.End_us = end_us;
		this.Start_us = end_us - this.Span_us;
	}


	PixelTimeRange.prototype.SetPixelSpan = function(span_px)
	{
		this.Span_px = span_px;
		this.usPerPixel = this.Span_px / this.Span_us;
	}


	PixelTimeRange.prototype.PixelOffset = function(time_us)
	{
		return Math.floor((time_us - this.Start_us) * this.usPerPixel);
	}


	PixelTimeRange.prototype.PixelSize = function(time_us)
	{
		return Math.floor(time_us * this.usPerPixel);
	}


	PixelTimeRange.prototype.Clone = function()
	{
		return new PixelTimeRange(this.Start_us, this.Span_us, this.Span_px);
	}


	return PixelTimeRange;
})();
