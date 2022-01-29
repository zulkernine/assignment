import { Box, Tab, Tabs, Typography } from "@mui/material";
import React, { Component } from "react";
import MessageList from "./component/message_list";
import MessageTextField from "./component/message_text_field";
import RoomIcon from "@mui/icons-material/Room";
import socket from "../data/socket";
import EventNames from "../data/event_names";
import { toast } from "react-toastify";
import { getAllUsers } from "../data/api_calls";

class MessageRootScreen extends Component {
  state = {
    currentIndex: 0,
    userStorage: [
      {
        user: {
          name: "uName3",
          id: "sockersdfsd",
        },
        hasNewMessage: false,
        messages: [
          {
            sentByMyself: false,
            text: "d fsgdshi bgfds gds",
          },
          {
            sentByMyself: true,
            text: "t45regd fgbc fg dfs gsdf43 43 fd gds",
          },
          {
            sentByMyself: false,
            text: "dg dfsgsdfgdsf dfsffds43 43 fd gds",
          },
          {
            sentByMyself: true,
            image: "https://picsum.photos/800",
          },
          {
            sentByMyself: false,
            text: "fdhery54ertg fgh eryer er5 fg",
          },
        ],
      },
    ],
  };

  componentDidMount() {
    this.fetchAllUsers();

    socket.on(EventNames.newUser, (user) => {
      if (user.id == socket.id) return;

      toast.info(`New user: ${user.name} joined`);

      let storage = [...this.state.userStorage];
      storage.push({
        user: user,
        hasNewMessage: false,
        messages: [],
      });

      this.setState({ userStorage: storage });
    });

    socket.on(EventNames.userLeft, (user) => {
      toast.warning(`User: ${user.name} left`);

      let storage = [...this.state.userStorage];
      const index = storage.findIndex(({ user: u }) => {
        return user.id == u.id;
      });
      if (index > -1) {
        storage.splice(index, 1); // 2nd parameter means remove one item only
      }

      this.setState({ userStorage: storage });
    });

    socket.on(EventNames.recieveMessage, ({ id, text }) => {
      let storage = [...this.state.userStorage];
      const index = storage.findIndex(({ user: u }) => {
        return id == u.id;
      });
      if (index > -1) {
        if (this.state.currentIndex != index)
          storage[index].hasNewMessage = true;
        storage[index].messages.push({
          sentByMyself: false,
          text,
        });
      }

      this.setState({ userStorage: storage });
    });
  }

  async fetchAllUsers() {
    const us = await getAllUsers();
    let storage = [...this.state.userStorage];
    us.map((user) => {
      if (user.id != socket.id)
        storage.push({
          user: user,
          hasNewMessage: false,
          messages: [],
        });
    });

    this.setState({ userStorage: storage });
  }

  componentWillUnmount() {
    socket.off(EventNames.newUser);
    socket.off(EventNames.userLeft);
    socket.off(EventNames.recieveMessage);
  }

  async handleSend(index, text) {
    socket.emit(EventNames.sendMessage, {
      id: this.state.userStorage[index].user.id,
      text,
    });

    let storage = [...this.state.userStorage];
    if (index > -1) {
      storage[index].messages.push({
        sentByMyself: true,
        text,
      });
    }

    this.setState({ userStorage: storage });
  }

  render() {
    const { currentIndex, userStorage } = this.state;

    return (
      <div style={{ height: "90vh", paddingTop: "20px", width: "100wh" }}>
        <Box
          sx={{
            flexGrow: 1,
            bgcolor: "background.paper",
            display: window.innerWidth > 600 ? "flex" : "block",
            maxHeight: "90vh",
          }}
        >
          <Tabs
            orientation={window.innerWidth > 600 ? "vertical" : "horizontal"}
            variant="scrollable"
            value={currentIndex}
            onChange={(e, i) => {
              let storage = [...userStorage];
              storage[i].hasNewMessage = false;
              this.setState({ currentIndex: i, userStorage: storage });
            }}
            sx={{ borderRight: 1, borderColor: "divider" }}
          >
            {userStorage.map((e) => (
              <Tab
                label={e.user.name}
                icon={e.hasNewMessage ? <RoomIcon /> : null}
                iconPosition="end"
              />
            ))}
          </Tabs>
          <Box sx={{ width: window.innerWidth > 600 ? "90%" : "100%" }}>
            <MessageList messages={userStorage[currentIndex].messages} />
          </Box>
        </Box>

        <Box
          padding={2}
          bgcolor={"#07eb97"}
          style={{ position: "fixed", bottom: "0px", width: "100%" }}
        >
          <MessageTextField
            handleSent={(text) => this.handleSend(currentIndex, text)}
          />
        </Box>
      </div>
    );
  }
}

export default MessageRootScreen;
