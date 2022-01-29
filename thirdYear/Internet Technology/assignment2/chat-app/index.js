const app = require("express")();
const http = require("http").Server(app);
const io = require("socket.io")(http, {
  cors: {
    origin: "http://192.168.43.218:3000",
  },
});
const port = process.env.PORT || 3075;
const cors = require("cors");

app.use(cors());

const eventNames = {
  registerUser: "REGISTER_USER",
  registrationSuccessful: "USER_REGISTRATION_SUCCESSFUL",
};

var users = [];

app.get("/", (req, res) => {
  res.sendFile(__dirname + "/index.html");
});

io.on("connection", (socket) => {
  socket.on("chat message", (msg) => {
    io.emit("chat message", msg);
  });

  socket.on(eventNames.registerUser, (uName) => {
    users.push({
      name: uName,
      id: socket.id,
    });
    console.log(users);
    socket.emit(eventNames.registrationSuccessful, true);
  });
});

http.listen(port, () => {
  console.log(`Socket.IO server running at http://localhost:${port}/`);
});
