/**
 * Javascript Task Runner
 * @author Alvin Lin (alvin.lin.dev@gmail.com)
 */

var gulp = require('gulp');

var closureCompiler = require('google-closure-compiler').gulp();
var gjslint = require('gulp-gjslint');

gulp.task('default', ['js-lint', 'js-advanced']);

gulp.task('js-lint', function() {
  return gulp.src(['./src/*.js'])
    .pipe(gjslint({
      flags: ['--jslint_error blank_lines_at_top_level',
              '--jslint_error indentation',
              '--jslint_error well_formed_author',
              '--jslint_error braces_around_type',
              '--jslint_error unused_private_members',
              '--jsdoc',
              '--max_line_length 80',
              '--error_trace'
             ]
    }))
    .pipe(gjslint.reporter('console'));
});

gulp.task('js-simple', function() {
  return gulp.src(['./src/*.js'])
    .pipe(closureCompiler({
      warning_level: 'VERBOSE',
      compilation_level: 'SIMPLE_OPTIMIZATIONS',
      js_output_file: 'simple.min.js'
    }))
    .pipe(gulp.dest('./compiled'));
});

gulp.task('js-advanced', function() {
  return gulp.src(['./src/*.js'])
    .pipe(closureCompiler({
      compilation_level: 'ADVANCED_OPTIMIZATIONS',
      js_output_file: 'advanced.min.js'
    }))
    .pipe(gulp.dest('./compiled'));
});
