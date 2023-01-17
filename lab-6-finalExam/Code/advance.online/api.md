### app.js

This is a module that contains the implementation to communicate as a server using the WebSocket protocol and to coordinate the work being processed by the client.

#### Attributes

| Name         | Type                       |
| ------------ | -------------------------- |
| app          | Express                    |
| server       | http.Server                |
| wss          | WebSocketServer            |
| ws           | WebSocket.WebSocket        |
| clients      | Array[WebSocket.WebSocket] |
| colors       | Array[String]              |
| userID       | Number                     |
| receivedData | Number                     |
| startTime    | Array[Number]              |
| endTime      | Number                     |
| execTimes    | Array[Number]              |

#### Methods

| Name                               | Description                                                  |
| ---------------------------------- | ------------------------------------------------------------ |
| wss.on('connection', function(ws)) | Used to handle the logic after the client connects to the server. |
| ws.on('message', function(msg))    | Logical processing after receiving the message.              |
| ws.on('close', function())         | Used to handle the logic after the client close the connection with the server. |
| app.configure()                    | Configure Express.                                           |
| app.get('/', (req, res) =>{})      | Set up such a single route with Express.                     |

### browser.js

This is a module that contains the implementation to communicate as a client using the WebSocket protocol and processes the work.

#### Attributes

| Name       | Type      |
| ---------- | --------- |
| myColor    | String    |
| myName     | String    |
| connection | WebSocket |
| data       | Number    |

#### Methods

| Name                | Description                                                  |
| ------------------- | ------------------------------------------------------------ |
| WebSocket.onopen    | The socket's open event listener, used to handle the logic after the socket is successfully opened. |
| WebSocket.onmessage | The socket's message event listener, used to handle logic after receiving a message |
| WebSocket.onclose   | The socket's close event listener, used to handle the logic after the socket is closed. |
| input.keydown       | Event listener for the Enter key. Sends a message to the server when the Enter key is pressed. |
| addMessage          | Compose the received content into div blocks for display on the HTML page. |
| work                | Client's work process.                                       |

### Main.cpp

This is a module that contains the implementation to communicate as a client using the WebSocket protocol and processes the work, which is a comparison version of `browser.js`.

#### Attributes

| Name   | Type                   |
| ------ | ---------------------- |
| myName | string                 |
| socket | EMSCRIPTEN_WEBSOCKET_T |
| data   | double                 |

#### Methods

| Name             | Input                                                        | Output  | Description |
| ---------------- | ------------------------------------------------------------ | ------- | ----------- |
| WebSocketOpen    | eventTypr:int, e:EmscriptenWebSocketOpenEvent\*, userData:void\* | EM_BOOL |             |
| WebSocketClose   | eventTypr:int, e:EmscriptenWebSocketCloseEvent\*, userData:void\* | EM_BOOL |             |
| WebSocketMessage | eventTypr:int, e:EmscriptenWebSocketMessageEvent\*, userData:void\* | EM_BOOL |             |
| work             | Client's work process.                                       | void    |             |