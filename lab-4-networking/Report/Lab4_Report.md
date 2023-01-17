# Lab4 Report

Yiwen Xu (48377645)

## Document API

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

### Networking Architecture

The code base of this project is coming from a simple chat demo. As the screenshots shows below.

<img src="https://tva1.sinaimg.cn/large/008vxvgGgy1h86k9695avj30wc0lotcf.jpg" alt="image-20221113114722849" style="zoom:50%;" />



<img src="https://tva1.sinaimg.cn/large/008vxvgGgy1h86nhs86gtj30wc0lon0v.jpg" alt="image-20221113114839132" style="zoom:50%;" />

<img src="https://tva1.sinaimg.cn/large/008vxvgGgy1h86k9cd3lfj30x80lnwh4.jpg" alt="image-20221113114922937" style="zoom:50%;" />

To meet the requirements, I modified it to implement a part of producer-consumer model which just like Lab3. In this case, each client is represents a machine and sever is represents a factory which can coordinate the work that being processed by machines. When the client connects to the server, it will start working. After each round of work, it will send messages and data to the server. The server will check if the target number of data has been reached, or let the client continue working.

<img src="https://tva1.sinaimg.cn/large/008vxvgGgy1h86kjhd1xsj30ke0lgq3y.jpg" alt="image-20221115134926121" style="zoom:50%;" />

*The networking architecture*

As the sequence diagram shows below, we can see the flow logic of this project and how a server actually coordinates the work process.



<img src="https://tva1.sinaimg.cn/large/008vxvgGgy1h86kjjl78gj30v90u0401.jpg" alt="image-20221114132552614" style="zoom:50%;" />



## Demonstration

### Server

The server is implemented with JavaScript using node server. It also using Express.js, which is a web application framework for Node.js, enables you to build server applications in Node.js. And the logs of message and progress will be printed during runtime.

<img src="https://tva1.sinaimg.cn/large/008vxvgGgy1h86kjqx1yqj312q0quwh4.jpg" alt="image-20221113114633049" style="zoom:50%;" />

<img src="https://tva1.sinaimg.cn/large/008vxvgGgy1h86kjmli4oj30u011q0vu.jpg" alt="image-20221113192217288" style="zoom:50%;" />

<img src="https://tva1.sinaimg.cn/large/008vxvgGgy1h86kk2ictkj30u011qgow.jpg" alt="image-20221113192229565" style="zoom:50%;" />

### Client

#### C++

The native comparison application is written in C++ code using Emscripten C++ WebSockets API. It can be run in the browser, but the output will be displayed in the console. 

<img src="https://tva1.sinaimg.cn/large/008vxvgGgy1h86n9161h7j31g00n448r.jpg" alt="image-20221113204658408" style="zoom:50%;" />



#### JavaScript

The comparison version for test application is written in JavaScript. In can be run in the browser, and display the performance data on the page.

![image-20221113203719667](https://tva1.sinaimg.cn/large/008vxvgGgy1h8em88e0usj312j0nijzt.jpg)

## Timing Analysis Comparison

In this case, I set the code to loop 40 times and automatically outputting a running log to reflect the functionality achieved by the program and recording all of the execution time.

### Native vs. JavaScript

To compare the performance of native code base and comparison version (JavaScript). I run both of them with four clients and same end termination condition.

I put all of the execution time data into `Data/ExecutionTime.xlsx` and calculate the 95% confidence interval. The obtained results are displayed below:

- For the native application results: 
  - The 95% confidence interval is [8.326792312, 8.593776383], the average execution time is 8.460284347 s.
- For the comparison application results:
  - The 95% confidence interval is [3.382596286, 3.453225991], the average execution time is 3.417911139 s.

We can plot these confidence intervals on a figure to compare them.



<img src="https://tva1.sinaimg.cn/large/008vxvgGgy1h86n94ullgj314h0u0q4m.jpg" alt="CI_js_wasm" style="zoom: 33%;" />

As we can see in the plot, the results of native application are much higher than comparison version. And the lower confidence intervals of native application is higher than the upper confidence interval of comparison application. Therefore, we can learn that the results are statistically significant, which means the run speed of native application is slower than comparison application that transpiled from C++.

### Different number of clients (JS)

For the work logic of one server with multi-client is similar to how the main thread controlled worker threads. I am curious about the performance of this application with different number of clients.

I set the code to loop 40 times with open different number of clients (1 client, 2 clients, 4 clients, 8 clients, 20 clients).

I put all of the execution time data into `Data/ExecutionTime.xlsx` and calculate the 95% confidence interval. The obtained results are displayed below:

- The results of the native application with 1 client: 
  - The 95% confidence interval is [26.30179803, 26.07560145], the average execution time is 26.18869974 s.
- The results of the native application with 2 client:
  - The 95% confidence interval is [13.52318919, 13.72795211], the average execution time is 13.62557065 s.
- The results of the native application with 4 client:
  - The 95% confidence interval is [8.32679231, 8.59377638], the average execution time is 8.46028435 s.
- The results of the native application with 8 client:
  - The 95% confidence interval is [8.79380625, 8.95787786], the average execution time is 8.87584205 s.
- The results of the native application with 20 client:
  - The 95% confidence interval is [9.89321460, 10.35209640], the average execution time is 10.12265550 s.

I plot these confidence intervals on a line plot to see the trend of execution time change with the number of clients.

<img src="https://tva1.sinaimg.cn/large/008vxvgGgy1h86n9auncjj318u0u0jtn.jpg" alt="LinePlot_5c" style="zoom: 33%;" />

As the plot shown before, we can see that the execution time decreases as the number of clients increases at first. However, after the number of clients is four, the execution time increases as the number of clients increases. 

The reason of the line going down at first is multiple clients working at the same time, which reduced the amount of work time that needed to be spent on getting the same target, and server wait time. But the more clients, the less the bonus, because more clients means we need to spend more time on client connections and sending messages. Finally, the disadvantages outweigh the benefits, and the execution time increases as the number of clients increases.

To better analyze the results with number 2,4,8,20 clients, I plot these confidence intervals on a figure to compare them. As the results, we can considered all of them are statistically significant for the same reason was mentioned before.

<img src="https://tva1.sinaimg.cn/large/008vxvgGgy1h86n9dcg0zj312u0u0ac9.jpg" alt="CI_4c_js" style="zoom:33%;" />



