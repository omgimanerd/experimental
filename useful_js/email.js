var email = require('emailjs');

var server = email.server.connect({
  user: 'omgimanerd1998',
  password: 'C0git0erg0$um',
  host: 'smtp.gmail.com',
  ssl: true
});

server.send({
  text: 'test',
  from: 'alvin@bob.com',
  to: 'alvin.lin.dev@gmail.com',
}, function(err, message) {
  console.log(err);
  console.log(message);
});
