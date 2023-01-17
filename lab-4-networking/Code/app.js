var express = require('express')
  , http = require('http')
  , path = require('path');

var app = express();
var server = http.createServer(app);
var WebSocketServer = require('ws').Server;
var wss = new WebSocketServer({ server: server });

var colors = ['red', 'green', 'blue', 'magenta', 'purple', 'plum', 'orange'];
colors.sort(function (a, b) { return Math.random() > 0.5; });
var clients = [];
var userID = 0;

const TARGET_DATA = 350;
var receivedData = 0;

var startTime = [];
var endTime;
var execTimes = [];

wss.on('connection', function (ws) {
  startTime.push(performance.now());
  clients.push(ws);
  userID += 1;
  var userName = userID;
  var userColor = colors.shift();
  ws.send(JSON.stringify({ type: 'color', data: {color: userColor, author: userName} }));
  console.log(userName + ' login');

  ws.on('message', function (msg) {

    console.log(userName + ' say: ' + msg);
    msg = String(msg);
    userName = String(userName);
    var obj = {
      time: (new Date()).getTime(),
      text: msg,
      author: userName,
      color: userColor
    };
    var json = JSON.stringify({ type: 'message', data: obj });
    for (var i = 0; i < clients.length; i++) {
      clients[i].send(json);
    }

    // ------------------------------------------------------
    if(msg == 'Done' && receivedData < TARGET_DATA){
      receivedData += 1;
      console.log('ReceivedData: ', receivedData);
      var obj = {
        time: (new Date()).getTime(),
        text: 'Keep Working',
        author: userName,
        color: userColor
      };
      var json = JSON.stringify({ type: 'message', data: obj });
      ws.send(json);
    }
    else if(receivedData >= TARGET_DATA){
      for (var i = 0; i < clients.length; i++) {
        clients[i].close();
      }

      endTime = performance.now();
      var execTime = (endTime - startTime[0])/1000;
      
      console.log('Execution Time:', execTime);
      execTimes.push(execTime);
      console.log('All Execution Time:');

      for(var i = 0; i < execTimes.length; i++){
        console.log(execTimes[i]);
      }

      startTime = [];
      userID = 0;
      receivedData = 0;
    }

  });
  ws.on('close', function () {
    var index = clients.indexOf(ws);
    clients.splice(index, 1);
    if (userName !== false && userColor != false) {
      colors.push(userColor);
    }
  });

});

app.configure(function () {
  app.set('port', process.env.PORT || 3000);
  app.set('views', __dirname + '/views');
  app.use(express.favicon());
  app.use(express.logger('dev'));
  app.use(express.bodyParser());
  app.use(express.methodOverride());
  app.use(app.router);
  app.use(express.static(path.join(__dirname, 'public')));
});

app.configure('development', function () {
  app.use(express.errorHandler());
});

app.get('/', function (req, res) {
  res.sendFile('chat.html');

  // res.sendFile('chat_comparison.html');
  // res.sendFile('public/comparison/example.wasm');
  // res.sendFile('public/comparison/mian.cpp');
  // res.sendFile('public/comparison/json.hpp');
});

server.listen(app.get('port'), function () {
  console.log("Express server listening on port " + app.get('port'));
});
