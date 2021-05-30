var five = require("johnny-five");
var board = new five.Board({port:'COM8'});
 
board.on("ready", function() {
 
  // Create an Led on pin 13 and strobe it on/off
  // Optionally set the speed; defaults to 100ms
  //(new five.Led(13)).strobe();
  var led = five.Led(13);
  this.repl.inject({led: led});
});
