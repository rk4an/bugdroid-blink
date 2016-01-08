var express = require('express');
var app = express();
var serialport = require('serialport');
var serialPortName = "/dev/ttyUSB0"

var stop = false;
var client;

app.get('/cmd', function (req, res) {
  console.log("GET " + req.query.cmd);

  if(!stop) {
     stop = true;
     client = res;
     serialPort.write(req.query.cmd+"\n", function(err, results) {
         console.log("results: " + results)
      });
   }
   else {
     console.log("Server busy");
     res.send("Server busy");
     res.end();
   }
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
   client.send(data);
   console.log('data received: ' + data);
   stop = false;
});

serialPort.on("open", function () {
   console.log('Serial open');
});
