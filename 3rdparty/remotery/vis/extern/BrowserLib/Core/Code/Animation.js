
// 
// Very basic linear value animation system, for now.
//


namespace("Anim");


Anim.Animation = (function()
{
	var anim_hz = 60;

	
	function Animation(anim_func, start_value, end_value, time, end_callback)
	{
		// Setup initial parameters
		this.StartValue = start_value;
		this.EndValue = end_value;
		this.ValueInc = (end_value - start_value) / (time * anim_hz);
		this.Value = start_value;
		this.Complete = false;
		this.EndCallback = end_callback;

		// Cache the update function to prevent recreating the closure
		var self = this;
		this.AnimFunc = anim_func;
		this.AnimUpdate = function() { Update(self); }

		// Call for the start value
		this.AnimUpdate();
	}


	function Update(self)
	{
		// Queue up the next frame immediately
		var id = window.setTimeout(self.AnimUpdate, 1000 / anim_hz);

		// Linear step the value and check for completion
		self.Value += self.ValueInc;
		if (Math.abs(self.Value - self.EndValue) < 0.01)
		{
			self.Value = self.EndValue;
			self.Complete = true;

			if (self.EndCallback)
				self.EndCallback();

			window.clearTimeout(id);
		}

		// Pass to the animation function
		self.AnimFunc(self.Value);
	}


	return Animation;
})();


Anim.Animate = function(anim_func, start_value, end_value, time, end_callback)
{
	return new Anim.Animation(anim_func, start_value, end_value, time, end_callback);
}
