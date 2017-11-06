var server = require('http').createServer();
var io = require('socket.io')(server);


io.on('connection', function(socket) {
  console.log("Connect from " + socket.id);

  socket.emit("change_status", true);

  socket.on("connected", (data) => {
    console.log(data);
  });

  socket.on('disconnect', () =>  {
    console.log(socket.id + " disconnected");
  });
});

server.listen(3000, () => {
  console.log("Server listen on port 3000");
});