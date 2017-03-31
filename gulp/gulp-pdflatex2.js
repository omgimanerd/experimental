/**
 * @author alvin@omgimanerd.tech
 */
 
const child_process = require('child_process');
const gutil = require('gulp-util');
const path = require('path');
const through = require('through2');
const tmp = require('tmp');

var error = function(message) {
  message = 'gulp-pdflatex2: ' + message;
  return new gutil.PluginError('gulp-pdflatex2', message, {
    showStack: true
  });
}

var pdflatex2 = function(options) {
  return through.obj(function(file, encoding, callback) {
    var filePath = path.parse(file.path);
    if (file.isNull()) {
      this.emit('error', error('Null file ${filePath.base} received!'));
      return callback(null, file);
    }
    
    this.emit('error', error('fuck'));
    return callback(null, file);
  });
}

// Exporting the plugin main function
module.exports = pdflatex2;