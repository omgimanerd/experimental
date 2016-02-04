/**
 * This class keeps track of the user input in global variables.
 * @author Alvin Lin (alvin.lin.dev@gmail.com)
 */

/**
 * Empty constructor for the Input object.
 * @constructor
 */
function Input() {}

Input.LEFT_CLICK = false;
Input.RIGHT_CLICK = false;
Input.MOUSE = {};

Input.LEFT = false;
Input.UP = false;
Input.RIGHT = false;
Input.DOWN = false;
Input.MISC_KEYS = {};

Input.onMouseDown = function(e) {
  if (e.which == 1) {
    Input.LEFT_CLICK = true;
  } else if (e.which == 3) {
    Input.RIGHT_CLICK = true;
  }
};

Input.onMouseUp = function(e) {
  if (e.which == 1) {
    Input.LEFT_CLICK = false;
  } else if (e.which == 3) {
    Input.RIGHT_CLICK = false;
  }
};

Input.onKeyDown = function(e) {
  switch (e.keyCode) {
  case 37:
  case 65:
    Input.LEFT = true;
    break;
  case 38:
  case 87:
    Input.UP = true;
    break;
  case 39:
  case 68:
    Input.RIGHT = true;
    break;
  case 40:
  case 83:
    Input.DOWN = true;
    break;
  default:
    Input.MISC_KEYS[e.keyCode] = true;
    break;
  };
};

Input.onKeyUp = function(e) {
  switch (e.keyCode) {
    case 37:
    case 65:
      Input.LEFT = false;
      break;
    case 38:
    case 87:
      Input.UP = false;
      break;
    case 39:
    case 68:
      Input.RIGHT = false;
      break;
    case 40:
    case 83:
      Input.DOWN = false;
      break;
    default:
      Input.MISC_KEYS[e.keyCode] = false;
  };
};

/**
 * This should be called during initialization to allow the Input
 * class to track user input.
 */
Input.applyEventHandlers = function() {
  window.addEventListener("touchstart", Input.onTouchStart);
  window.addEventListener("touchend", Input.onTouchEnd);
  window.addEventListener("mousedown", Input.onMouseDown);
  window.addEventListener("mouseup", Input.onMouseUp);
  window.addEventListener("keyup", Input.onKeyUp);
  window.addEventListener("keydown", Input.onKeyDown);
};

/**
 * This should be called any time an element needs to track mouse coordinates
 * over it.
 * @param {Element} element The element to apply the event listener to.
 * @param {string} identifier A unique identifier which the mouse coordinates
 *   will be stored with. This identifier should be a global constant since it
 *   will be used to access the mouse coordinates.
 */
Input.addMouseTracker = function(element, identifier) {
  if (Input.MOUSE[identifier]) {
    throw new Exception("Non-unique identifier used!");
  }
  element.addEventListener("mousemove", function(event) {
    var boundingRect = element.getBoundingClientRect();
    Input.MOUSE[identifier] = [event.pageX - boundingRect.left,
                               event.pageY - boundingRect.top];
  });
};
