var express = require('express');
var app = express();
var serialport = require('serialport');
var serialPortName = "/dev/ttyUSB0"

var resc;

app.get('/cmd', function (req, res) {
  console.log("GET " + req.query.cmd);

  resc = res;
  serialPort.write(req.query.cmd+"\n", function(err, results) {
      console.log("results: " + results)
  });

});


var server = app.listen(3000, function () {

  var host = server.address().address;
  var port = server.address().port;

  console.log('Bugdroid app listening at http://%s:%s', host, port);
});

var serialPort = new serialport.SerialPort(serialPortName,{
    parser: serialport.parsers.readline('\n')
});

serialPort.on('data', function(data) {
   resc.send(data);
   console.log('data received: ' + data);
});

serialPort.on("open", function () {
   console.log('Serial open');
});


