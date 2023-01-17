# Lab5 Report

Yiwen Xu (48377645)

## Computer Environment

Operating system: macOS Ventura Version 13.0.1

Processor: 2.3 GHz Quad-Core Intel Core i7

Memory: 16 GB 3733 MHz LPDDR4X

IDE: Visual Studio Code

## Setup Electron

To begin developing an Electron app, we need to install the Node.js runtime and its bundled npm package manager onto our system. To check that Node.js was installed correctly, we can use the following commands.

```shell
node -v
npm -v
```

This is the version I used:

<img src="https://tva1.sinaimg.cn/large/008vxvgGgy1h8o4ahq15lj312q0quq46.jpg" alt="image-20221130000433688" style="zoom: 50%;" />

Note that users do not need to install Node.js themselves as a prerequisite to running this Electron app.

In this project, I used Lab4 (Networking) as code base. Therefore, I enter the code base folder and initializing an npm package within it with `npm init`. 

<img src="https://tva1.sinaimg.cn/large/008vxvgGgy1h8o4ahtzdlj312q0quq46.jpg" alt="image-20221130112534163" style="zoom:50%;" />

Then install Electron into my app's devDependencies with `npm install electron --save-dev`.  Also, for packaging this project, I'll packaging this app with [Electron Forge](https://www.electronforge.io/). I install Electron Forge's CLI in my project's devDependencies and import my existing project with a handy conversion script.

```shell
npm install --save-dev @electron-forge/cli
npx electron-forge import
```

Now we get a `package.json` file, a `forge.config.js` file and a `package-lock.json` file:

<img src="https://tva1.sinaimg.cn/large/008vxvgGgy1h8o4ajedoaj30ta0wkjw3.jpg" alt="image-20221130162519921" style="zoom:50%;" />

## Code Base

### Building Electron App

The `main` script I defined in `package.json` is the entry point of any Electron application. So I created a `mian.js` file in root folder of my project. Now we can load my web page `chat.html` into an Electron BrowserWindow with the following simple code.

```js
const { app, BrowserWindow } = require('electron')

const createWindow = () => {
  const win = new BrowserWindow({
    width: 800,
    height: 600,
  })

  win.loadFile('chat.html')
};

app.whenReady().then(() => {
  createWindow();
});

app.on('activate', () => {
  // Can open most 3 clients
  if (BrowserWindow.getAllWindows().length < 3) {
    createWindow();
  }
});

app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') {
      app.quit();
    }
  });
```

 ### Adding New Feature

I added a notification function to my project. It will notified user when a new client is setup.

<img src="https://tva1.sinaimg.cn/large/008vxvgGgy1h8o4ao3q4xj30ku05c3yl.jpg" alt="image-20221130165258912" style="zoom:50%;" />

To implement this for the renderer process, Electron conveniently allows us to send notifications with the HTML5 Notification API, using the currently running operating system's native notification APIs to display it.

```js
    connection.onopen = function () {
        const NOTIFICATION_TITLE ='New Client'
        const NOTIFICATION_BODY = 'New client connected to server'
        new Notification(NOTIFICATION_TITLE, { body: NOTIFICATION_BODY })
        
        connection.send('Start Working');
        work();
    };
```

## Packaging Application

To create a distributable, use this project's new `make` script (already applied in [Setup Electron](#Setup Electron) part), which runs the `electron-forge make` command.

```shell
npm run make
```

After the script runs, I get an `out` folder containing both the distributable and a folder containing the packaged application code.

<img src="https://tva1.sinaimg.cn/large/008vxvgGgy1h8o93snpqtj30b609o0t6.jpg" alt="image-20221130233545393" style="zoom:50%;" />

The distributable in the `out/make` folder should be ready to launch.

## Demonstration

Before we can start running this project, we need to set up a local server to perform its functions well.

### Server

The server is implemented with JavaScript using node server. It also using Express.js, which is a web application framework for Node.js, enables you to build server applications in Node.js. And the logs of message and progress will be printed during runtime.

```shell
supervisor app.js
# or
node app.js
```



<img src="https://tva1.sinaimg.cn/large/008vxvgGgy1h86kjqx1yqj312q0quwh4.jpg" alt="image-20221113114633049" style="zoom:50%;" /><img src="https://tva1.sinaimg.cn/large/008vxvgGgy1h86kk2ictkj30u011qgow.jpg" alt="image-20221113192229565" style="zoom:50%;" />

### Client

The first to run the project, you need to run `npm install`, which is used to download the dependencies and create the `node_modules` file. After that, all project files should look like this.

<img src="https://tva1.sinaimg.cn/large/008vxvgGgy1h8o969nvryj30b60hagmd.jpg" alt="image-20221130233809706" style="zoom:50%;" />

To start a new client, we can use this command:

```shell
npm run start
```

Also, we can open it with the packaged Electron applications by simply double click it.

![demo](https://tva1.sinaimg.cn/large/008vxvgGgy1h8o4ayehcfg30tu0ku4qr.gif)

However, it may not work on a different device because I haven't signed my code as I have not gotten the certification.

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

To meet the requirements, I modified it to implement a part of producer-consumer model which just like Lab3. In this case, each client is represents a machine and sever is represents a factory which can coordinate the work that being processed by machines. When the client connects to the server, it will start working. After each round of work, it will send messages and data to the server. The server will check if the target number of data has been reached, or let the client continue working.

<img src="https://tva1.sinaimg.cn/large/008vxvgGgy1h86kjhd1xsj30ke0lgq3y.jpg" alt="image-20221115134926121" style="zoom:50%;" />

*The networking architecture*

As the sequence diagram shows below, we can see the flow logic of this project and how a server actually coordinates the work process.

<img src="https://tva1.sinaimg.cn/large/008vxvgGgy1h86kjjl78gj30v90u0401.jpg" alt="image-20221114132552614" style="zoom:50%;" />

