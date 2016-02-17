var winio = require('win-io');
var five = require('johnny-five');

var board = new five.Board( {
    io: new winio(),
	repl: false
});

board.on("ready", function() {
  var led = new five.Led(5);
  led.blink(500);
});