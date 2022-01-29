import { Box, Button, Grid } from "@mui/material";
import React, { Component } from "react";
import MessageTextField from "./component/message_text_field";

class MessageRootScreen extends Component {
  state = {
    userStorage: [
      {
        user: {
          name: "uName",
          id: "socket.id",
        },
        hasNewMessage:false,
        messages:[
          {
            sentByMyself:false,
            text:"hi bro!",
            image:"https://picsum.photos/237/400/400"
          }
        ]
      },
    ],
  };
  render() {
    return (
      <div style={{ height: "100vh", width: "100wh", position: "relative" }}>
        <Grid container></Grid>
        <Box
          padding={2}
          bgcolor={"#07eb97"}
          style={{ position: "absolute", bottom: "-5px", width: "100%" }}
        >
          <MessageTextField />
        </Box>
      </div>
    );
  }
}

export default MessageRootScreen;
