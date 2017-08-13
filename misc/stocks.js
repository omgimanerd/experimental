const Canvas = require('drawille');
const Table = require('cli-table2');

const _ = require('lodash');
const colors = require('colors');
const moment = require('moment');
const request = require('request');

request({
  url: 'https://www.alphavantage.co/query',
  qs: {
    'function': 'TIME_SERIES_DAILY',
    'symbol': 'MSFT',
    'apikey': 'demo'
  },
  json: true,
}, function(error, response, body) {
  console.log(error, body);
  var m = new Map();
  var series = body['Time Series (Daily)'];
  var dates = _.keys(series).sort();
  for (var date of dates) {
    m.set(date, _.mapKeys(series[date], (v, k) => k.split(' ')[1]))
  }
  console.log(m);
});

var canvas = new Canvas(40, 40);

for (var i = 0; i < 100; ++i) {
  var x = Math.floor(Math.random() * 40);
  var y = Math.floor(Math.random() * 40);
  canvas.toggle(x, y);
}

var table = new Table({
  head: ['There be dots']
});
table.push([
  canvas.frame().red
]);

console.log(table.toString());
