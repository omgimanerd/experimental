/**
 * @fileoverview This class encapsulates a button.
 * @author alvin.lin.dev@gmail.com (Alvin Lin)
 */

/**
 * @constructor
 */
function Button(parent, id, class) {
  this.parent = parent;
  this.id = id;
  this.class = class;

  this.element = document.createElement('button');
  this.setId(id);
  this.setClass(class);
}

/**
 *
 */
Button.prototype.getElement = function() {
  return this.element;
};

/**
 *
 */
Button.prototype.setId = function(id) {
  this.id = id;
  if (id) {
    this.element.setAttribute('id', id);
  }
};

/**
 *
 */
Button.prototype.getId = function() {
  return this.id;
};

/**
 *
 */
Button.prototype.setClass = function(class) {
  this.class = class;
  if (class) {
    this.element.setAttribute('class', class);
  }
}

/**
 *
 */
Button.prototype.getClass = function() {
  return this.class;
};
