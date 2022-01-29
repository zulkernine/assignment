const app = require("express")();
const http = require("http").Server(app);
const io = require("socket.io")(http, {
  cors: {
    origin: "http://192.168.43.218:3000",
  },
});
const port = process.env.PORT || 5000;
const cors = require("cors");

app.use(cors());

const eventNames = {
  registerUser: "REGISTER_USER",
  registrationSuccessful: "USER_REGISTRATION_SUCCESSFUL",
  newUser: "NEW_USER",
  userLeft: "USER_LEFT",
  sendMessage: "SEND_MESSAGE",
  recieveMessage: "RECIEVE_MESSAGE",
};

var users = {};

app.get("/", (req, res) => {
  res.sendFile(__dirname + "/index.html");
});

app.get("/users", function (req, res) {
  res.json(Object.values(users).map((e) => e.u));
});

io.on("connection", (socket) => {
  //Transfer messages
  socket.on(eventNames.sendMessage, ({ id, text }) => {
    users[id].skt.emit(eventNames.recieveMessage, {
      id: socket.id,
      text,
    });
  });

  // Register user and inform everyone else about new user
  socket.on(eventNames.registerUser, (uName) => {
    users[socket.id] = {
      skt: socket,
      u: {
        name: uName,
        id: socket.id,
      },
    };
    console.log(users);
    socket.emit(eventNames.registrationSuccessful, true);
    io.emit(eventNames.newUser, users[socket.id].u);
  });

  // Delete user and inform others
  socket.on("disconnecting", (reason) => {
    if (users[socket.id]) {
      io.emit(eventNames.userLeft, users[socket.id].u);
      delete users[socket.id];
    }
  });
});

http.listen(port, () => {
  console.log(`Socket.IO server running at http://localhost:${port}/`);
});
