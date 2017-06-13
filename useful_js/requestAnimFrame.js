/**
 * Allows for a smooth client side game loop, running optimally at 60 FPS.
 * @author alvin.lin.dev@gmail.com (Alvin Lin)
 */

var requestAnimationFrame = (function() {
  var timeoutFn = function(callback, element) {
    window.setTimeout(callback, 1000 / 60);
  };
  return window.requestAnimationFrame ||
    window.webkitRequestAnimationFrame ||
    window.mozRequestAnimationFrame ||
    window.oRequestAnimationFrame ||
    window.msRequestAnimationFrame ||
    timeoutFn;
})();
