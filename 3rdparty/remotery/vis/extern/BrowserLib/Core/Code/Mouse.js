
namespace("Mouse");


Mouse.State =(function()
{
	function State(event)
	{
		// Get button press states
		if (typeof event.buttons != "undefined")
		{
			// Firefox
			this.Left = (event.buttons & 1) != 0;
			this.Right = (event.buttons & 2) != 0;
			this.Middle = (event.buttons & 4) != 0;
		}
		else
		{
			// Chrome
			this.Left = (event.button == 0);
			this.Middle = (event.button == 1);
			this.Right = (event.button == 2);
		}

		// Get page-relative mouse position
		this.Position = DOM.Event.GetMousePosition(event);

		// Get wheel delta
		var delta = 0;
		if (event.wheelDelta)
			delta = event.wheelDelta / 120;		// IE/Opera
		else if (event.detail)
			delta = -event.detail / 3;			// Mozilla
		this.WheelDelta = delta;

		// Get the mouse position delta
		// Requires Pointer Lock API support
		this.PositionDelta = [
			event.movementX || event.mozMovementX || event.webkitMovementX || 0,
			event.movementY || event.mozMovementY || event.webkitMovementY || 0
		];
	}

	return State;
})();


//
// Basic Pointer Lock API support
// https://developer.mozilla.org/en-US/docs/WebAPI/Pointer_Lock
// http://www.chromium.org/developers/design-documents/mouse-lock
//
// Note that API has not been standardised yet so browsers can implement functions with prefixes
//


Mouse.PointerLockSupported = function()
{
	return 'pointerLockElement' in document || 'mozPointerLockElement' in document || 'webkitPointerLockElement' in document;
}


Mouse.RequestPointerLock = function(element)
{
	element.requestPointerLock = element.requestPointerLock || element.mozRequestPointerLock || element.webkitRequestPointerLock;
	if (element.requestPointerLock)
		element.requestPointerLock();
}


Mouse.ExitPointerLock = function()
{
	document.exitPointerLock = document.exitPointerLock || document.mozExitPointerLock || document.webkitExitPointerLock;
	if (document.exitPointerLock)
		document.exitPointerLock();
}


// Can use this element to detect whether pointer lock is enabled (returns non-null)
Mouse.PointerLockElement = function()
{
	return document.pointerLockElement || document.mozPointerLockElement || document.webkitPointerLockElement;
}
