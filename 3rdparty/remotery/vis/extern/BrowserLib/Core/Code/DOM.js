
namespace("DOM.Node");
namespace("DOM.Event");
namespace("DOM.Applet");



//
// =====================================================================================================================
// ----- DOCUMENT NODE/ELEMENT EXTENSIONS ------------------------------------------------------------------------------
// =====================================================================================================================
//



DOM.Node.Get = function(id)
{
	return document.getElementById(id);
}


//
// Set node position
//
DOM.Node.SetPosition = function(node, position)
{
	node.style.left = position[0];
	node.style.top = position[1];
}
DOM.Node.SetX = function(node, x)
{
	node.style.left = x;
}
DOM.Node.SetY = function(node, y)
{
	node.style.top = y;
}


//
// Get the absolute position of a HTML element on the page
//
DOM.Node.GetPosition = function(element, account_for_scroll)
{
	// Recurse up through parents, summing offsets from their parent
	var x = 0, y = 0;
	for (var node = element; node != null; node = node.offsetParent)
	{
		x += node.offsetLeft;
		y += node.offsetTop;
	}

	if (account_for_scroll)
	{
		// Walk up the hierarchy subtracting away any scrolling
		for (var node = element; node != document.body; node = node.parentNode)
		{
			x -= node.scrollLeft;
			y -= node.scrollTop;
		}
	}

	return [x, y];
}


//
// Set node size
//
DOM.Node.SetSize = function(node, size)
{
	node.style.width = size[0];
	node.style.height = size[1];
}
DOM.Node.SetWidth = function(node, width)
{
	node.style.width = width;
}
DOM.Node.SetHeight = function(node, height)
{
	node.style.height = height;
}


//
// Get node OFFSET size:
//    clientX includes padding
//    offsetX includes padding and borders
//    scrollX includes padding, borders and size of contained node
//
DOM.Node.GetSize = function(node)
{
	return [ node.offsetWidth, node.offsetHeight ];
}
DOM.Node.GetWidth = function(node)
{
	return node.offsetWidth;
}
DOM.Node.GetHeight = function(node)
{
	return node.offsetHeight;
}


//
// Set node opacity
//
DOM.Node.SetOpacity = function(node, value)
{
	node.style.opacity = value;
}


DOM.Node.SetColour = function(node, colour)
{
	node.style.color = colour;
}


//
// Hide a node by completely disabling its rendering (it no longer contributes to document layout)
//
DOM.Node.Hide = function(node)
{
	node.style.display = "none";
}


//
// Show a node by restoring its influcen in document layout
//
DOM.Node.Show = function(node)
{
	node.style.display = "block";
}


//
// Add a CSS class to a HTML element, specified last
//
DOM.Node.AddClass = function(node, class_name)
{
	// Ensure the class hasn't already been added
	DOM.Node.RemoveClass(node, class_name);
	node.className += " " + class_name;
}


//
// Remove a CSS class from a HTML element
//
DOM.Node.RemoveClass = function(node, class_name)
{
	// Remove all variations of where the class name can be in the string list
	var regexp = new RegExp("\\b" + class_name + "\\b");
	node.className = node.className.replace(regexp, "");
}



//
// Check to see if a HTML element contains a class
//
DOM.Node.HasClass = function(node, class_name)
{
	var regexp = new RegExp("\\b" + class_name + "\\b");
	return regexp.test(node.className);
}


//
// Recursively search for a node with the given class name
//
DOM.Node.FindWithClass = function(parent_node, class_name, index)
{
	// Search the children looking for a node with the given class name
	for (var i in parent_node.childNodes)
	{
		var node = parent_node.childNodes[i];
		if (DOM.Node.HasClass(node, class_name))
		{
			if (index === undefined || index-- == 0)
				return node;
		}

		// Recurse into children
		node = DOM.Node.FindWithClass(node, class_name);
		if (node != null)
			return node;
	}

	return null;
}


//
// Check to see if one node logically contains another
//
DOM.Node.Contains = function(node, container_node)
{
	while (node != null && node != container_node)
		node = node.parentNode;
	return node != null;
}


//
// Create the HTML nodes specified in the text passed in
// Assumes there is only one root node in the text
//
DOM.Node.CreateHTML = function(html)
{
	var div = document.createElement("div");
	div.innerHTML = html;

	// First child may be a text node, followed by the created HTML
	var child = div.firstChild;
	if (child != null && child.nodeType == 3)
		child = child.nextSibling;
	return child;
}


//
// Make a copy of a HTML element, making it visible and clearing its ID to ensure it's not a duplicate
//
DOM.Node.Clone = function(name)
{
	// Get the template element and clone it, making sure it's renderable
	var node = DOM.Node.Get(name);
	node = node.cloneNode(true);
	node.id = null;
	node.style.display = "block";
	return node;
}


//
// Append an arbitrary block of HTML to an existing node
//
DOM.Node.AppendHTML = function(node, html)
{
	var child = DOM.Node.CreateHTML(html);
	node.appendChild(child);
	return child;
}


//
// Append a div that clears the float style
//
DOM.Node.AppendClearFloat = function(node)
{
	var div = document.createElement("div");
	div.style.clear = "both";
	node.appendChild(div);
}


//
// Check to see that the object passed in is an instance of a DOM node
//
DOM.Node.IsNode = function(object)
{
	return object instanceof Element;
}


//
// Create an "iframe shim" so that elements within it render over a Java Applet
// http://web.archive.org/web/20110707212850/http://www.oratransplant.nl/2007/10/26/using-iframe-shim-to-partly-cover-a-java-applet/
//
DOM.Node.CreateShim = function(parent)
{
	var shimmer = document.createElement("iframe");

	// Position the shimmer so that it's the same location/size as its parent
	shimmer.style.position = "fixed";
	shimmer.style.left = parent.style.left;
	shimmer.style.top = parent.style.top;
	shimmer.style.width = parent.offsetWidth;
	shimmer.style.height = parent.offsetHeight;

	// We want the shimmer to be one level below its contents
	shimmer.style.zIndex = parent.style.zIndex - 1;

	// Ensure its empty
	shimmer.setAttribute("frameborder", "0");
	shimmer.setAttribute("src", "");

	// Add to the document and the parent
	document.body.appendChild(shimmer);
	parent.Shimmer = shimmer;
	return shimmer;
}



//
// =====================================================================================================================
// ----- EVENT HANDLING EXTENSIONS -------------------------------------------------------------------------------------
// =====================================================================================================================
//



//
// Retrieves the event from the first parameter passed into an HTML event
//
DOM.Event.Get = function(evt)
{
	// Internet explorer doesn't pass the event
	return window.event || evt;
}


//
// Retrieves the element that triggered an event from the event object
//
DOM.Event.GetNode = function(evt)
{
	evt = DOM.Event.Get(evt);

	// Get the target element
	var element;
	if (evt.target)
		element = evt.target;
	else if (e.srcElement)
		element = evt.srcElement;

	// Default Safari bug
	if (element.nodeType == 3)
		element = element.parentNode;

	return element;
}


//
// Stop default action for an event
//
DOM.Event.StopDefaultAction = function(evt)
{
	if (evt && evt.preventDefault)
		evt.preventDefault();
	else if (window.event && window.event.returnValue)
		window.event.returnValue = false;
}


//
// Stops events bubbling up to parent event handlers
//
DOM.Event.StopPropagation = function(evt)
{
	evt = DOM.Event.Get(evt);
	if (evt)
	{
		evt.cancelBubble = true;
		if (evt.stopPropagation)
			evt.stopPropagation();
	}
}


//
// Stop both event default action and propagation
//
DOM.Event.StopAll = function(evt)
{
	DOM.Event.StopDefaultAction(evt);
	DOM.Event.StopPropagation(evt);
}


//
// Adds an event handler to an event
//
DOM.Event.AddHandler = function(obj, evt, func)
{
	if (obj)
	{
		if (obj.addEventListener)
			obj.addEventListener(evt, func, false);
		else if (obj.attachEvent)
			obj.attachEvent("on" + evt, func);
	}
}


//
// Removes an event handler from an event
//
DOM.Event.RemoveHandler = function(obj, evt, func)
{
	if (obj)
	{
		if (obj.removeEventListener)
			obj.removeEventListener(evt, func, false);
		else if (obj.detachEvent)
			obj.detachEvent("on" + evt, func);
	}
}


//
// Get the position of the mouse cursor, page relative
//
DOM.Event.GetMousePosition = function(evt)
{
	evt = DOM.Event.Get(evt);

	var px = 0;
	var py = 0;
	if (evt.pageX || evt.pageY)
	{
		px = evt.pageX;
		py = evt.pageY;
	}
	else if (evt.clientX || evt.clientY)
	{
		px = e.clientX + document.body.scrollLeft + document.documentElement.scrollLeft;
		py = e.clientY + document.body.scrollTop + document.documentElement.scrollTop;
	}

	return [px, py];
}



//
// =====================================================================================================================
// ----- JAVA APPLET EXTENSIONS ----------------------------------------------------------------------------------------
// =====================================================================================================================
//



//
// Create an applet element for loading a Java applet, attaching it to the specified node
//
DOM.Applet.Load = function(dest_id, id, code, archive)
{
	// Lookup the applet destination
	var dest = DOM.Node.Get(dest_id);
	if (!dest)
		return;

	// Construct the applet element and add it to the destination
	Debug.Log("Injecting applet DOM code");
	var applet = "<applet id='" + id + "' code='" + code + "' archive='" + archive + "'";
	applet += " width='" + dest.offsetWidth + "' height='" + dest.offsetHeight + "'>";
	applet += "</applet>";
	dest.innerHTML = applet;
}


//
// Moves and resizes a named applet so that it fits in the destination div element.
// The applet must be contained by a div element itself. This container div is moved along
// with the applet.
//
DOM.Applet.Move = function(dest_div, applet, z_index, hide)
{
	if (!applet || !dest_div)
		return;

	// Before modifying any location information, hide the applet so that it doesn't render over
	// any newly visible elements that appear while the location information is being modified.
	if (hide)
		applet.style.visibility = "hidden";

	// Get its view rect
	var pos = DOM.Node.GetPosition(dest_div);
	var w = dest_div.offsetWidth;
	var h = dest_div.offsetHeight;

	// It needs to be embedded in a <div> for correct scale/position adjustment
	var container = applet.parentNode;
	if (!container || container.localName != "div")
	{
		Debug.Log("ERROR: Couldn't find source applet's div container");
		return;
	}

	// Reposition and resize the containing div element
	container.style.left = pos[0];
	container.style.top = pos[1];
	container.style.width = w;
	container.style.height = h;
	container.style.zIndex = z_index;

	// Resize the applet itself
	applet.style.width = w;
	applet.style.height = h;

	// Everything modified, safe to show
	applet.style.visibility = "visible";
}
