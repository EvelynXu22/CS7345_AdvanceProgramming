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

