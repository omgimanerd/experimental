var PORT_NUMBER = 8000;

var express = require('express');
var app = express();

app.get('/', function(req, res) {
  res.sendFile(__dirname + '/public/index.html');
  console.log('Sending to homepage by default');
});
app.get('/*', function(req, res) {
  res.sendFile(__dirname + '/public/' + req.params[0]);
});

var server = app.listen(PORT_NUMBER, function() {
  console.log("Listening to port " + PORT_NUMBER);
});
