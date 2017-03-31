
var gulp = require('gulp');
var print = require('gulp-print');
var pdflatex = require('./gulp-pdflatex2');

gulp.task('test', function() {
    return gulp.src('./*.txt')
        .pipe(pdflatex())
        .pipe(gulp.dest('./output'));
});